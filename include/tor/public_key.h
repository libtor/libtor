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

#ifndef TOR_PUBLIC_KEY_H
#define TOR_PUBLIC_KEY_H

#ifdef PRIVATE
#	include <openssl/pem.h>
#	include <openssl/rsa.h>

	typedef struct TorPublicKey {
		int  references;
		RSA* key;
	} TorPublicKey;
#else
	typedef void TorPublicKey;
#endif

TorPublicKey* tor_public_key_new (void);

TorPublicKey* tor_public_key_clone (TorPublicKey* self);

void tor_public_key_destroy (TorPublicKey* self);

#ifdef PRIVATE
	TorPublicKey* tor_public_key_new_from (RSA* key);

	EVP_PKEY* tor_public_key_to_evp (TorPublicKey* self);
#endif

#endif
