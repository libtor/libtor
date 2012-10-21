/* Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of libtor - https://github.com/libtor/libtor
 *
 * libtor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * libtor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with libtor. If not, see <http://www.gnu.org/licenses/>.
 */

#include <tor/common.h>

#include <uv.h>

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/crypto.h>
#include <openssl/engine.h>
#include <openssl/rand.h>

static bool initialized = false;

static struct {
	uv_mutex_t* item;
	int         length;
} locks;

static void
_locking_callback (int mode, int n, const char* file, int line)
{
	if (locks.length > n) {
		return;
	}

	if (mode & CRYPTO_LOCK) {
		uv_mutex_lock(&locks.item[n]);
	}
	else {
		uv_mutex_unlock(&locks.item[n]);
	}
}

typedef struct CRYPTO_dynlock_value {
	uv_mutex_t* lock;
} CRYPTO_dynlock_value;

static CRYPTO_dynlock_value*
_dynlock_create_callback (const char* file, int line)
{
	CRYPTO_dynlock_value* self = malloc(sizeof(CRYPTO_dynlock_value));
	uv_mutex_t*           lock = malloc(sizeof(uv_mutex_t));

	uv_mutex_init(lock);
	self->lock = lock;

	return self;
}

static void
_dynlock_lock_callback (int mode, CRYPTO_dynlock_value* self, const char* file, int line)
{
	if (mode & CRYPTO_LOCK) {
		uv_mutex_lock(self->lock);
	}
	else {
		uv_mutex_unlock(self->lock);
	}
}

static void
_dynlock_destroy_callback (CRYPTO_dynlock_value* self, const char* file, int line)
{
	uv_mutex_destroy(self->lock);
	free(self);
}

void
tor_init (void)
{
	if (initialized) {
		return;
	}

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();

	// enable proper threading
	locks.length = CRYPTO_num_locks();
	locks.item   = malloc(locks.length * sizeof(uv_mutex_t));

	for (size_t i = 0; i < locks.length; i++) {
		uv_mutex_init(&locks.item[i]);
	}

	CRYPTO_set_locking_callback(_locking_callback);
	CRYPTO_set_id_callback(uv_thread_self);
	CRYPTO_set_dynlock_create_callback(_dynlock_create_callback);
	CRYPTO_set_dynlock_lock_callback(_dynlock_lock_callback);
	CRYPTO_set_dynlock_destroy_callback(_dynlock_destroy_callback);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	initialized = true;
}

void
tor_init_with_engine (const char* name, const char* path)
{
	ENGINE* engine;

	if (initialized) {
		return;
	}

	tor_init();

	if (path == NULL) {
		engine = ENGINE_by_id(name);
	}
	else {
		engine = ENGINE_by_id("dynamic");

		if (!ENGINE_ctrl_cmd_string(engine, "ID", name, 0) ||
		    !ENGINE_ctrl_cmd_string(engine, "DIR_LOAD", "2", 0) ||
		    !ENGINE_ctrl_cmd_string(engine, "DIR_ADD", path, 0) ||
		    !ENGINE_ctrl_cmd_string(engine, "LOAD", NULL, 0)) {
			ENGINE_free(engine);
			engine = NULL;
		}
	}

	if (engine) {
		ENGINE_set_default(engine, ENGINE_METHOD_ALL);
	}
}

bool
tor_add_entropy (void)
{
	return RAND_poll();
}

void
tor_cleanup (void)
{
	if (!initialized) {
		return;
	}

	EVP_cleanup();
	ERR_remove_state(0);
	ERR_free_strings();

	ENGINE_cleanup();

	CONF_modules_unload(1);
	CRYPTO_cleanup_all_ex_data();

	// cleanup multithreading
	for (size_t i = 0; i < locks.length; i++) {
		uv_mutex_destroy(&locks.item[i]);
	}

	free(locks.item);
	locks.length = 0;
}
