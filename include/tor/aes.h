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

#ifndef TOR_AES_H
#define TOR_AES_H

#include <string.h>
#include <stdbool.h>

#ifdef PRIVATE
#	include <openssl/evp.h>

	typedef struct TorAES {
		EVP_CIPHER_CTX context;
	} TorAES;
#else
	typedef void TorAES;
#endif

TorAES* tor_aes_new (const void* key, const void* iv);

void tor_aes_destroy (TorAES* self);

bool tor_aes_crypt (TorAES* self, const void* input, size_t length, void* output);

#ifndef NO_MAGIC
#include <tor/magic.h>

#define tor_aes_crypt(...) \
	tor_aes_crypt(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__), ARGS_THIRD(__VA_ARGS__))

#endif

#endif
