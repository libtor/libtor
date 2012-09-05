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

#ifndef TOR_RANDOM_H
#define TOR_RANDOM_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

bool tor_random (void* to, size_t length);

int tor_random_int (unsigned int max);

uint64_t tor_random_uint64 (uint64_t max);

#ifndef NO_MAGIC
#include <tor/magic.h>

#define tor_random_int(...) \
	tor_random_int(ARGS_FIRST_AS(int, __VA_ARGS__))

#endif

#endif
