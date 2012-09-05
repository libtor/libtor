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

#ifndef TOR_CONSTANTS_H
#define TOR_CONSTANTS_H

/**
 * Length of the output of our message digest.
 */
#define TOR_DIGEST_LEN    20

/**
 * Length of the output of our second (improved) message digests.
 */
#define TOR_DIGEST256_LEN 32

/**
 * Length of our symmetric cipher's keys.
 */
#define TOR_CIPHER_KEY_LEN 16

/**
 * Length of our symmetric cipher's IV.
 */
#define TOR_CIPHER_IV_LEN 16

/**
 * Length of our public keys.
 */
#define TOR_PK_BYTES (1024 / 8)

/**
 * Length of our DH keys.
 */
#define TOR_DH_BYTES (1024 / 8)

/**
 * Length of a SHA1 message digest when encoded in base64 with trailing =
 * signs removed.
 */
#define TOR_BASE64_DIGEST_LEN 27

/** Length of a SHA256 message digest when encoded in base64 with trailing =
 * signs removed.
 */
#define TOR_BASE64_DIGEST256_LEN 43

/**
 * Length of encoded public key fingerprints, including space; but not
 * including terminating NULL.
 */
#define TOR_FINGERPRINT_LEN 49

/**
 * Length of hex encoding of SHA1 digest, not including final NULL.
 */
#define TOR_HEX_DIGEST_LEN 40

/**
 * Length of hex encoding of SHA256 digest, not including final NULL.
 */
#define TOR_HEX_DIGEST256_LEN 64

#endif
