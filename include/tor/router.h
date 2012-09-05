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

#ifndef TOR_ROUTER_H
#define TOR_ROUTER_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <tor/public_key.h>
#include <tor/policy.h>

typedef struct TorRouter {
	char* nickname;
	char* address;
	char* platform;

	struct {
		short onion;
		short directory;
	} port;

	struct {
		TorPublicKey* onion;
		TorPublicKey* signing;
	} keys;

	TorPolicy* exit_policy;

	struct {
		uint32_t average;
		uint32_t burst;
		uint32_t capacity;
	} bandwidth;

	struct tm published;
	time_t    uptime;

	bool hibernating;
} TorRouter;

TorRouter* tor_router_new (void);

void tor_router_destroy (TorRouter* self);

#ifdef PRIVATE
// private shit goes here
#endif

#endif
