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

#define PRIVATE
#define NO_MAGIC
#include <tor/aes.h>
#undef NO_MAGIC
#undef PRIVATE

#include <stdint.h>
#include <assert.h>
#include <limits.h>

#include <openssl/aes.h>
#include <openssl/modes.h>

TorAES*
tor_aes_new (const void* key, const void* iv)
{
	assert(key);
	assert(iv);

	TorAES* self = malloc(sizeof(TorAES));

	EVP_EncryptInit(&self->context, EVP_aes_128_ctr(), key, iv);

	return self;
}

void
tor_aes_destroy (TorAES* self)
{
	assert(self);

	EVP_CIPHER_CTX_cleanup(&self->context);
	free(self);
}

bool
tor_aes_crypt (TorAES* self, const void* input, size_t length, void* output)
{
	int outl;

	assert(self);
	assert(input);
	assert(length < INT_MAX);

	return EVP_EncryptUpdate(&self->context, (uint8_t*) input, &outl, (uint8_t*) output ? output : input, length);
}
