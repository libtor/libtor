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
#include <tor/policy.h>
#undef NO_MAGIC
#undef PRIVATE

#include <tor/common.h>

TorPolicy*
tor_policy_new (void)
{
	TorPolicy* self = tor_new(TorPolicy);

	self->rules = NULL;
	self->last  = NULL;

	return self;
}

void
tor_policy_destroy (TorPolicy* self)
{
	assert(self);

	TorPolicyRule* current = self->rules;

	while (current) {
		TorPolicyRule* next = current->next;

		tor_policy_rule_destroy(current);

		current = next;
	}

	tor_destroy(self);
}

TorPolicy*
tor_policy_accept (TorPolicy* self, const char* address, uint16_t start, uint16_t end)
{
	assert(self);

	tor_policy_add_rule(self, tor_policy_rule_new_with(
		TOR_POLICY_RULE_ACCEPT, address, start, end));

	return false;
}

TorPolicy*
tor_policy_reject (TorPolicy* self, const char* address, uint16_t start, uint16_t end)
{
	assert(self);

	tor_policy_add_rule(self, tor_policy_rule_new_with(
		TOR_POLICY_RULE_REJECT, address, start, end));

	return self;
}

bool
tor_policy_can (TorPolicy* self, const char* address, uint16_t port)
{
	assert(self);
	assert(address);
	assert(port != 0);

	if (!self->rules) {
		return true;
	}

	TorPolicyRule* current = self->rules;

	while (current) {
		if (tor_policy_rule_matches(current, address, port)) {
			return TOR_POLICY_RULE_TO_BOOL(current);
		}

		current = current->next;
	}

	return true;
}

TorPolicyRule*
tor_policy_add_rule (TorPolicy* self, TorPolicyRule* rule)
{
	assert(self);
	assert(rule);

	if (self->last) {
		self->last->next = rule;
	}
	else {
		self->rules = rule;
	}

	self->last = rule;

	return rule;
}

TorPolicyRule*
tor_policy_remove_rule (TorPolicy* self, TorPolicyRule* rule)
{
	assert(self);
	assert(rule);

	if (!self->rules) {
		return NULL;
	}

	TorPolicyRule* current = self->rules;

	if (current == rule) {
		self->rules = current->next;

		if (!self->rules) {
			self->last = NULL;
		}

		return rule;
	}

	while (current) {
		if (current->next == rule) {
			current->next = current->next->next;

			if (!current->next) {
				self->last = current;
			}

			return rule;
		}

		current = current->next;
	}

	return NULL;
}

TorPolicyRule*
tor_policy_rule_new (void)
{
	return tor_new(TorPolicyRule);
}

TorPolicyRule*
tor_policy_rule_new_with (TorPolicyRuleType type, const char* address, uint16_t start, uint16_t end)
{
	assert(address);

	TorPolicyRule* self = tor_policy_rule_new();

	self->type    = type;
	self->address = (!address || strcmp(address, "*") == 0) ? NULL : strdup(address);
	self->start   = start;
	self->end     = end;

	return self;
}

void
tor_policy_rule_destroy (TorPolicyRule* self)
{
	if (self->address) {
		free(self->address);
	}

	tor_destroy(self);
}

bool
tor_policy_rule_matches (TorPolicyRule* self, const char* address, uint16_t port)
{
	if (self->address) {
		return false; // if it doesn't match
	}

	if (self->end == 0) {
		if (self->start == 0) {
			return true;
		}
		else if (self->start == port) {
			return true;
		}
	}
	else {
		if (port >= self->start && port <= self->end) {
			return true;
		}
	}

	return false;
}
