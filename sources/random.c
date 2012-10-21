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
#include <tor/random.h>
#undef NO_MAGIC
#undef PRIVATE

#include <tor/common.h>

#include <openssl/rand.h>

bool
tor_random (void* to, size_t length)
{
	assert(to);
	assert(length < INT_MAX);

	return RAND_bytes((uint8_t*) to, length);
}

int
tor_random_int (unsigned int max)
{
	unsigned int value;
	unsigned int cutoff;

	if (max == 0) {
		max = INT_MAX - 1;
	}

	assert(max <= ((unsigned int) INT_MAX) + 1);

	// We ignore any values that are >= 'cutoff,' to avoid biasing the
	// distribution with clipping at the upper end of unsigned int's
	// range.
	cutoff = UINT_MAX - (UINT_MAX % max);

	while (true) {
		tor_random(&value, sizeof(value));

		if (value < cutoff)
			return value % max;
	}
}

uint64_t
crypto_random_uint64(uint64_t max)
{
	uint64_t value;
	uint64_t cutoff;

	if (max == 0) {
		max = UINT64_MAX - 1;
	}

	assert(max < UINT64_MAX);

	// We ignore any values that are >= 'cutoff,' to avoid biasing the
	// distribution with clipping at the upper end of unsigned int's
	// range.
	cutoff = UINT64_MAX - (UINT64_MAX % max);

	while (true) {
		tor_random(&value, sizeof(value));

		if (value < cutoff) {
			return value % max;
		}
	}
}

double
tor_random_double (void)
{
	double value;

	tor_random(&value, sizeof(value));

	return value;
}
