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

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <tor.h>

int
main (int argc, char* argv[])
{
	bool  listening = false;
	bool  stealth   = false;
	short port;

	int opt = 0;
	while ((opt = getopt(argc, argv, "lsp:"))) {
		switch (opt) {
			case 'l':
				listening = true;
				break;

			case 's':
				stealth = true;
				break;

			case 'p':
				port = atoi(optarg);
				break;

			default:
				fprintf(stderr, "Usage: %s [-s] [-l] [-p port]", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	TorHiddenService* service = tor_hidden_service_new();
}
