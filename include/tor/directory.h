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

#ifndef TOR_DIRECTORY_H
#define TOR_DIRECTORY_H

#include <tor/authorities.h>
#include <tor/routers.h>

typedef struct TorDirectory {
	TorAuthorities* authorities;
	TorRouters* routers;
} TorDirectory;

TorDirectory* tor_directory_new (void);

TorDirectory* tor_directory_from_file (const char* path);

TorDirectory* tor_directory_from_fd (int fd);

void tor_directory_destroy (TorDirectory* self);

#ifdef PRIVATE
// private shit goes here
#endif

#endif
