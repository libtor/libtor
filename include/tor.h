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

#ifndef TOR_H
#define TOR_H

#include <stdbool.h>

#include <tor/router.h>
#include <tor/directory.h>
#include <tor/circuit.h>
#include <tor/socket.h>
#include <tor/hidden_service.h>

/**
 * Initialize the library, remember to call this function before using
 * any other function.
 */
void tor_init (void);

/**
 * Initialize the library with the passed crypto engine.
 */
void tor_init_with_engine (const char* name, const char* path);

/**
 * Add more entropy to the RNG.
 */
bool tor_add_entropy (void);

/**
 * Cleanup the library when it's not needed anymore.
 */
void tor_cleanup (void);

#ifndef NO_MAGIC
#include <tor/magic.h>

#define tor_init_with_engine(...) \
	tor_init_with_engine(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__))

#endif

#endif
