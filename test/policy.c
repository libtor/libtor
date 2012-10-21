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

void
test_policy_creation (void* data)
{
	TorPolicy* policy = tor_policy_new();

	tt_assert(policy);

end:;
}

void
test_policy_matches (void* data)
{
	TorPolicyRule* rule;

	rule = tor_policy_rule_new_with(TOR_POLICY_RULE_ACCEPT, "*", 42, 0);
	tt_assert(tor_policy_rule_matches(rule, "127.0.0.1", 42) == true);
	tt_assert(tor_policy_rule_matches(rule, "127.0.0.1", 23) == false);

end:
	tor_policy_rule_destroy(rule);
}

void
test_policy_can (void* data)
{
	TorPolicy* policy = tor_policy_new();

	tor_policy_accept(policy, "*", 80); // accept *:80
	tor_policy_reject(policy, "*", 43); // reject *:43
	tor_policy_accept(policy, "*");     // accept *:*

	tt_assert(tor_policy_can(policy, "127.0.0.1", 80)   == true);
	tt_assert(tor_policy_can(policy, "127.0.0.1", 43)   == false);
	tt_assert(tor_policy_can(policy, "127.0.0.1", 9001) == true);

end:
	tor_policy_destroy(policy);
}

struct testcase_t policy_tests[] = {
	{ "creation", test_policy_creation },
	{ "matches", test_policy_can },
	{ "can", test_policy_can },

	END_OF_TESTCASES
};
