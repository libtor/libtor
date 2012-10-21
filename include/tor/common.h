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

#ifndef TOR_COMMON
#define TOR_COMMON

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#ifdef __GNUC__
#	define likely(x)   __builtin_expect(!!(x), 1)
#	define unlikely(x) __builtin_expect(!!(x), 0)
#else
#	define likely(x)   (x)
#	define unlikely(x) (x)
#endif

static inline void*
tor_alloc (size_t size)
{
	void* self = malloc(size);

	if (unlikely(self == NULL)) {
		abort();
	}

	return self;
}

static inline void*
tor_new (size_t size)
{
	void* self = tor_alloc(size);

	memset(self, 0, size);

	return self;
}

#define tor_new(what) \
	tor_new(sizeof(what))

static inline void
tor_destroy (void* self)
{
	assert(self);

	free(self);
}

#endif
