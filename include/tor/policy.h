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

#ifndef TOR_POLICY_H
#define TOR_POLICY_H

#include <stdbool.h>
#include <stdint.h>

typedef enum TorPolicyRuleType {
	TOR_POLICY_RULE_ACCEPT,
	TOR_POLICY_RULE_REJECT
} TorPolicyRuleType;

typedef struct TorPolicyRule {
	TorPolicyRuleType type;

	char* address;

	uint16_t start;
	uint16_t end;

	struct TorPolicyRule* next;
} TorPolicyRule;

#define TOR_POLICY_RULE_TO_BOOL(r) (r->type == TOR_POLICY_RULE_ACCEPT)

typedef struct TorPolicy {
	TorPolicyRule* rules;

	#ifdef PRIVATE
	TorPolicyRule* last;
	#endif
} TorPolicy;

TorPolicy* tor_policy_new (void);

void tor_policy_destroy (TorPolicy* self);

TorPolicy* tor_policy_accept (TorPolicy* self, const char* address, uint16_t start, uint16_t end);

TorPolicy* tor_policy_reject (TorPolicy* self, const char* address, uint16_t start, uint16_t end);

bool tor_policy_can (TorPolicy* self, const char* address, uint16_t port);

#ifdef PRIVATE
	TorPolicyRule* tor_policy_add_rule (TorPolicy* self, TorPolicyRule* rule);

	TorPolicyRule* tor_policy_remove_rule (TorPolicy* self, TorPolicyRule* rule);
#endif

#ifndef NO_MAGIC
#include <tor/magic.h>

#define tor_policy_accept(self, address, ports...) \
	tor_policy_accept(self, address, ARGS_FIRST_AS(uint16_t, ports), ARGS_SECOND_AS(uint16_t, ports))

#define tor_policy_reject(self, address, ports...) \
	tor_policy_reject(self, address, ARGS_FIRST_AS(uint16_t, ports), ARGS_SECOND_AS(uint16_t, ports))

#endif

bool tor_policy_rule_matches (TorPolicyRule* self, const char* address, uint16_t port);

#ifdef PRIVATE
	TorPolicyRule* tor_policy_rule_new (void);

	TorPolicyRule* tor_policy_rule_new_with (TorPolicyRuleType type, const char* address, uint16_t start, uint16_t end);

	void tor_policy_rule_destroy (TorPolicyRule* self);
#endif

#endif
