<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ranकरोmized tests क्रम eBPF दीर्घest-prefix-match maps
 *
 * This program runs अक्रमomized tests against the lpm-bpf-map. It implements a
 * "Trivial Longest Prefix Match" (tlpm) based on simple, linear, singly linked
 * lists. The implementation should be pretty straightक्रमward.
 *
 * Based on tlpm, this inserts अक्रमomized data पूर्णांकo bpf-lpm-maps and verअगरies
 * the trie-based bpf-map implementation behaves the same way as tlpm.
 */

#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/bpf.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <arpa/inet.h>
#समावेश <sys/समय.स>

#समावेश <bpf/bpf.h>

#समावेश "bpf_util.h"
#समावेश "bpf_rlimit.h"

काष्ठा tlpm_node अणु
	काष्ठा tlpm_node *next;
	माप_प्रकार n_bits;
	uपूर्णांक8_t key[];
पूर्ण;

अटल काष्ठा tlpm_node *tlpm_match(काष्ठा tlpm_node *list,
				    स्थिर uपूर्णांक8_t *key,
				    माप_प्रकार n_bits);

अटल काष्ठा tlpm_node *tlpm_add(काष्ठा tlpm_node *list,
				  स्थिर uपूर्णांक8_t *key,
				  माप_प्रकार n_bits)
अणु
	काष्ठा tlpm_node *node;
	माप_प्रकार n;

	n = (n_bits + 7) / 8;

	/* 'overwrite' an equivalent entry अगर one alपढ़ोy exists */
	node = tlpm_match(list, key, n_bits);
	अगर (node && node->n_bits == n_bits) अणु
		स_नकल(node->key, key, n);
		वापस list;
	पूर्ण

	/* add new entry with @key/@n_bits to @list and वापस new head */

	node = दो_स्मृति(माप(*node) + n);
	निश्चित(node);

	node->next = list;
	node->n_bits = n_bits;
	स_नकल(node->key, key, n);

	वापस node;
पूर्ण

अटल व्योम tlpm_clear(काष्ठा tlpm_node *list)
अणु
	काष्ठा tlpm_node *node;

	/* मुक्त all entries in @list */

	जबतक ((node = list)) अणु
		list = list->next;
		मुक्त(node);
	पूर्ण
पूर्ण

अटल काष्ठा tlpm_node *tlpm_match(काष्ठा tlpm_node *list,
				    स्थिर uपूर्णांक8_t *key,
				    माप_प्रकार n_bits)
अणु
	काष्ठा tlpm_node *best = शून्य;
	माप_प्रकार i;

	/* Perक्रमm दीर्घest prefix-match on @key/@n_bits. That is, iterate all
	 * entries and match each prefix against @key. Remember the "best"
	 * entry we find (i.e., the दीर्घest prefix that matches) and वापस it
	 * to the caller when करोne.
	 */

	क्रम ( ; list; list = list->next) अणु
		क्रम (i = 0; i < n_bits && i < list->n_bits; ++i) अणु
			अगर ((key[i / 8] & (1 << (7 - i % 8))) !=
			    (list->key[i / 8] & (1 << (7 - i % 8))))
				अवरोध;
		पूर्ण

		अगर (i >= list->n_bits) अणु
			अगर (!best || i > best->n_bits)
				best = list;
		पूर्ण
	पूर्ण

	वापस best;
पूर्ण

अटल काष्ठा tlpm_node *tlpm_delete(काष्ठा tlpm_node *list,
				     स्थिर uपूर्णांक8_t *key,
				     माप_प्रकार n_bits)
अणु
	काष्ठा tlpm_node *best = tlpm_match(list, key, n_bits);
	काष्ठा tlpm_node *node;

	अगर (!best || best->n_bits != n_bits)
		वापस list;

	अगर (best == list) अणु
		node = best->next;
		मुक्त(best);
		वापस node;
	पूर्ण

	क्रम (node = list; node; node = node->next) अणु
		अगर (node->next == best) अणु
			node->next = best->next;
			मुक्त(best);
			वापस list;
		पूर्ण
	पूर्ण
	/* should never get here */
	निश्चित(0);
	वापस list;
पूर्ण

अटल व्योम test_lpm_basic(व्योम)
अणु
	काष्ठा tlpm_node *list = शून्य, *t1, *t2;

	/* very basic, अटल tests to verअगरy tlpm works as expected */

	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8));

	t1 = list = tlpm_add(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8);
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8));
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 16));
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff, 0x00 पूर्ण, 16));
	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0x7f पूर्ण, 8));
	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0xfe पूर्ण, 8));
	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 7));

	t2 = list = tlpm_add(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 16);
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8));
	निश्चित(t2 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 16));
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 15));
	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0x7f, 0xff पूर्ण, 16));

	list = tlpm_delete(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 16);
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8));
	निश्चित(t1 == tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff, 0xff पूर्ण, 16));

	list = tlpm_delete(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8);
	निश्चित(!tlpm_match(list, (uपूर्णांक8_t[])अणु 0xff पूर्ण, 8));

	tlpm_clear(list);
पूर्ण

अटल व्योम test_lpm_order(व्योम)
अणु
	काष्ठा tlpm_node *t1, *t2, *l1 = शून्य, *l2 = शून्य;
	माप_प्रकार i, j;

	/* Verअगरy the tlpm implementation works correctly regardless of the
	 * order of entries. Insert a अक्रमom set of entries पूर्णांकo @l1, and copy
	 * the same data in reverse order पूर्णांकo @l2. Then verअगरy a lookup of
	 * अक्रमom keys will yield the same result in both sets.
	 */

	क्रम (i = 0; i < (1 << 12); ++i)
		l1 = tlpm_add(l1, (uपूर्णांक8_t[])अणु
					अक्रम() % 0xff,
					अक्रम() % 0xff,
				पूर्ण, अक्रम() % 16 + 1);

	क्रम (t1 = l1; t1; t1 = t1->next)
		l2 = tlpm_add(l2, t1->key, t1->n_bits);

	क्रम (i = 0; i < (1 << 8); ++i) अणु
		uपूर्णांक8_t key[] = अणु अक्रम() % 0xff, अक्रम() % 0xff पूर्ण;

		t1 = tlpm_match(l1, key, 16);
		t2 = tlpm_match(l2, key, 16);

		निश्चित(!t1 == !t2);
		अगर (t1) अणु
			निश्चित(t1->n_bits == t2->n_bits);
			क्रम (j = 0; j < t1->n_bits; ++j)
				निश्चित((t1->key[j / 8] & (1 << (7 - j % 8))) ==
				       (t2->key[j / 8] & (1 << (7 - j % 8))));
		पूर्ण
	पूर्ण

	tlpm_clear(l1);
	tlpm_clear(l2);
पूर्ण

अटल व्योम test_lpm_map(पूर्णांक keysize)
अणु
	माप_प्रकार i, j, n_matches, n_matches_after_delete, n_nodes, n_lookups;
	काष्ठा tlpm_node *t, *list = शून्य;
	काष्ठा bpf_lpm_trie_key *key;
	uपूर्णांक8_t *data, *value;
	पूर्णांक r, map;

	/* Compare behavior of tlpm vs. bpf-lpm. Create a अक्रमomized set of
	 * prefixes and insert it पूर्णांकo both tlpm and bpf-lpm. Then run some
	 * अक्रमomized lookups and verअगरy both maps वापस the same result.
	 */

	n_matches = 0;
	n_matches_after_delete = 0;
	n_nodes = 1 << 8;
	n_lookups = 1 << 16;

	data = alloca(keysize);
	स_रखो(data, 0, keysize);

	value = alloca(keysize + 1);
	स_रखो(value, 0, keysize + 1);

	key = alloca(माप(*key) + keysize);
	स_रखो(key, 0, माप(*key) + keysize);

	map = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
			     माप(*key) + keysize,
			     keysize + 1,
			     4096,
			     BPF_F_NO_PREALLOC);
	निश्चित(map >= 0);

	क्रम (i = 0; i < n_nodes; ++i) अणु
		क्रम (j = 0; j < keysize; ++j)
			value[j] = अक्रम() & 0xff;
		value[keysize] = अक्रम() % (8 * keysize + 1);

		list = tlpm_add(list, value, value[keysize]);

		key->prefixlen = value[keysize];
		स_नकल(key->data, value, keysize);
		r = bpf_map_update_elem(map, key, value, 0);
		निश्चित(!r);
	पूर्ण

	क्रम (i = 0; i < n_lookups; ++i) अणु
		क्रम (j = 0; j < keysize; ++j)
			data[j] = अक्रम() & 0xff;

		t = tlpm_match(list, data, 8 * keysize);

		key->prefixlen = 8 * keysize;
		स_नकल(key->data, data, keysize);
		r = bpf_map_lookup_elem(map, key, value);
		निश्चित(!r || त्रुटि_सं == ENOENT);
		निश्चित(!t == !!r);

		अगर (t) अणु
			++n_matches;
			निश्चित(t->n_bits == value[keysize]);
			क्रम (j = 0; j < t->n_bits; ++j)
				निश्चित((t->key[j / 8] & (1 << (7 - j % 8))) ==
				       (value[j / 8] & (1 << (7 - j % 8))));
		पूर्ण
	पूर्ण

	/* Remove the first half of the elements in the tlpm and the
	 * corresponding nodes from the bpf-lpm.  Then run the same
	 * large number of अक्रमom lookups in both and make sure they match.
	 * Note: we need to count the number of nodes actually inserted
	 * since there may have been duplicates.
	 */
	क्रम (i = 0, t = list; t; i++, t = t->next)
		;
	क्रम (j = 0; j < i / 2; ++j) अणु
		key->prefixlen = list->n_bits;
		स_नकल(key->data, list->key, keysize);
		r = bpf_map_delete_elem(map, key);
		निश्चित(!r);
		list = tlpm_delete(list, list->key, list->n_bits);
		निश्चित(list);
	पूर्ण
	क्रम (i = 0; i < n_lookups; ++i) अणु
		क्रम (j = 0; j < keysize; ++j)
			data[j] = अक्रम() & 0xff;

		t = tlpm_match(list, data, 8 * keysize);

		key->prefixlen = 8 * keysize;
		स_नकल(key->data, data, keysize);
		r = bpf_map_lookup_elem(map, key, value);
		निश्चित(!r || त्रुटि_सं == ENOENT);
		निश्चित(!t == !!r);

		अगर (t) अणु
			++n_matches_after_delete;
			निश्चित(t->n_bits == value[keysize]);
			क्रम (j = 0; j < t->n_bits; ++j)
				निश्चित((t->key[j / 8] & (1 << (7 - j % 8))) ==
				       (value[j / 8] & (1 << (7 - j % 8))));
		पूर्ण
	पूर्ण

	बंद(map);
	tlpm_clear(list);

	/* With 255 अक्रमom nodes in the map, we are pretty likely to match
	 * something on every lookup. For statistics, use this:
	 *
	 *     म_लिखो("          nodes: %zu\n"
	 *            "        lookups: %zu\n"
	 *            "        matches: %zu\n"
	 *            "matches(delete): %zu\n",
	 *            n_nodes, n_lookups, n_matches, n_matches_after_delete);
	 */
पूर्ण

/* Test the implementation with some 'real world' examples */

अटल व्योम test_lpm_ipaddr(व्योम)
अणु
	काष्ठा bpf_lpm_trie_key *key_ipv4;
	काष्ठा bpf_lpm_trie_key *key_ipv6;
	माप_प्रकार key_size_ipv4;
	माप_प्रकार key_size_ipv6;
	पूर्णांक map_fd_ipv4;
	पूर्णांक map_fd_ipv6;
	__u64 value;

	key_size_ipv4 = माप(*key_ipv4) + माप(__u32);
	key_size_ipv6 = माप(*key_ipv6) + माप(__u32) * 4;
	key_ipv4 = alloca(key_size_ipv4);
	key_ipv6 = alloca(key_size_ipv6);

	map_fd_ipv4 = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				     key_size_ipv4, माप(value),
				     100, BPF_F_NO_PREALLOC);
	निश्चित(map_fd_ipv4 >= 0);

	map_fd_ipv6 = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				     key_size_ipv6, माप(value),
				     100, BPF_F_NO_PREALLOC);
	निश्चित(map_fd_ipv6 >= 0);

	/* Fill data some IPv4 and IPv6 address ranges */
	value = 1;
	key_ipv4->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 2;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 3;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key_ipv4->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 5;
	key_ipv4->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key_ipv4->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 4;
	key_ipv4->prefixlen = 23;
	inet_pton(AF_INET, "192.168.0.0", key_ipv4->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv4, key_ipv4, &value, 0) == 0);

	value = 0xdeadbeef;
	key_ipv6->prefixlen = 64;
	inet_pton(AF_INET6, "2a00:1450:4001:814::200e", key_ipv6->data);
	निश्चित(bpf_map_update_elem(map_fd_ipv6, key_ipv6, &value, 0) == 0);

	/* Set tprefixlen to maximum क्रम lookups */
	key_ipv4->prefixlen = 32;
	key_ipv6->prefixlen = 128;

	/* Test some lookups that should come back with a value */
	inet_pton(AF_INET, "192.168.128.23", key_ipv4->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == 0);
	निश्चित(value == 3);

	inet_pton(AF_INET, "192.168.0.1", key_ipv4->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == 0);
	निश्चित(value == 2);

	inet_pton(AF_INET6, "2a00:1450:4001:814::", key_ipv6->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == 0);
	निश्चित(value == 0xdeadbeef);

	inet_pton(AF_INET6, "2a00:1450:4001:814::1", key_ipv6->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == 0);
	निश्चित(value == 0xdeadbeef);

	/* Test some lookups that should not match any entry */
	inet_pton(AF_INET, "10.0.0.1", key_ipv4->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == -1 &&
	       त्रुटि_सं == ENOENT);

	inet_pton(AF_INET, "11.11.11.11", key_ipv4->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv4, key_ipv4, &value) == -1 &&
	       त्रुटि_सं == ENOENT);

	inet_pton(AF_INET6, "2a00:ffff::", key_ipv6->data);
	निश्चित(bpf_map_lookup_elem(map_fd_ipv6, key_ipv6, &value) == -1 &&
	       त्रुटि_सं == ENOENT);

	बंद(map_fd_ipv4);
	बंद(map_fd_ipv6);
पूर्ण

अटल व्योम test_lpm_delete(व्योम)
अणु
	काष्ठा bpf_lpm_trie_key *key;
	माप_प्रकार key_size;
	पूर्णांक map_fd;
	__u64 value;

	key_size = माप(*key) + माप(__u32);
	key = alloca(key_size);

	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE,
				key_size, माप(value),
				100, BPF_F_NO_PREALLOC);
	निश्चित(map_fd >= 0);

	/* Add nodes:
	 * 192.168.0.0/16   (1)
	 * 192.168.0.0/24   (2)
	 * 192.168.128.0/24 (3)
	 * 192.168.1.0/24   (4)
	 *
	 *         (1)
	 *        /   \
         *     (IM)    (3)
	 *    /   \
         *   (2)  (4)
	 */
	value = 1;
	key->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	निश्चित(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 2;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	निश्चित(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 3;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key->data);
	निश्चित(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	value = 4;
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key->data);
	निश्चित(bpf_map_update_elem(map_fd, key, &value, 0) == 0);

	/* हटाओ non-existent node */
	key->prefixlen = 32;
	inet_pton(AF_INET, "10.0.0.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == -1 &&
		त्रुटि_सं == ENOENT);

	key->prefixlen = 30; // unused prefix so far
	inet_pton(AF_INET, "192.255.0.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == -1 &&
		त्रुटि_सं == ENOENT);

	key->prefixlen = 16; // same prefix as the root node
	inet_pton(AF_INET, "192.255.0.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == -1 &&
		त्रुटि_सं == ENOENT);

	/* निश्चित initial lookup */
	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.0.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	निश्चित(value == 2);

	/* हटाओ leaf node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.0.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	निश्चित(value == 1);

	/* हटाओ leaf (and पूर्णांकermediary) node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.1.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	निश्चित(value == 1);

	/* हटाओ root node */
	key->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.128.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == 0);
	निश्चित(value == 3);

	/* हटाओ last node */
	key->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key->data);
	निश्चित(bpf_map_delete_elem(map_fd, key) == 0);

	key->prefixlen = 32;
	inet_pton(AF_INET, "192.168.128.1", key->data);
	निश्चित(bpf_map_lookup_elem(map_fd, key, &value) == -1 &&
		त्रुटि_सं == ENOENT);

	बंद(map_fd);
पूर्ण

अटल व्योम test_lpm_get_next_key(व्योम)
अणु
	काष्ठा bpf_lpm_trie_key *key_p, *next_key_p;
	माप_प्रकार key_size;
	__u32 value = 0;
	पूर्णांक map_fd;

	key_size = माप(*key_p) + माप(__u32);
	key_p = alloca(key_size);
	next_key_p = alloca(key_size);

	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE, key_size, माप(value),
				100, BPF_F_NO_PREALLOC);
	निश्चित(map_fd >= 0);

	/* empty tree. get_next_key should वापस ENOENT */
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* get and verअगरy the first key, get the second one should fail. */
	key_p->prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", key_p->data);
	निश्चित(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	स_रखो(key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 16 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168);

	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* no exact matching key should get the first one in post order. */
	key_p->prefixlen = 8;
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 16 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168);

	/* add one more element (total two) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", key_p->data);
	निश्चित(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	स_रखो(key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 128);

	स_रखो(next_key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Add one more element (total three) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", key_p->data);
	निश्चित(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	स_रखो(key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	स_रखो(next_key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Add one more element (total four) */
	key_p->prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", key_p->data);
	निश्चित(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	स_रखो(key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	स_रखो(next_key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* Add one more element (total five) */
	key_p->prefixlen = 28;
	inet_pton(AF_INET, "192.168.1.128", key_p->data);
	निश्चित(bpf_map_update_elem(map_fd, key_p, &value, 0) == 0);

	स_रखो(key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, शून्य, key_p) == 0);
	निश्चित(key_p->prefixlen == 24 && key_p->data[0] == 192 &&
	       key_p->data[1] == 168 && key_p->data[2] == 0);

	स_रखो(next_key_p, 0, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 28 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1 &&
	       next_key_p->data[3] == 128);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 1);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 128);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 16 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168);

	स_नकल(key_p, next_key_p, key_size);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == -1 &&
	       त्रुटि_सं == ENOENT);

	/* no exact matching key should वापस the first one in post order */
	key_p->prefixlen = 22;
	inet_pton(AF_INET, "192.168.1.0", key_p->data);
	निश्चित(bpf_map_get_next_key(map_fd, key_p, next_key_p) == 0);
	निश्चित(next_key_p->prefixlen == 24 && next_key_p->data[0] == 192 &&
	       next_key_p->data[1] == 168 && next_key_p->data[2] == 0);

	बंद(map_fd);
पूर्ण

#घोषणा MAX_TEST_KEYS	4
काष्ठा lpm_mt_test_info अणु
	पूर्णांक cmd; /* 0: update, 1: delete, 2: lookup, 3: get_next_key */
	पूर्णांक iter;
	पूर्णांक map_fd;
	काष्ठा अणु
		__u32 prefixlen;
		__u32 data;
	पूर्ण key[MAX_TEST_KEYS];
पूर्ण;

अटल व्योम *lpm_test_command(व्योम *arg)
अणु
	पूर्णांक i, j, ret, iter, key_size;
	काष्ठा lpm_mt_test_info *info = arg;
	काष्ठा bpf_lpm_trie_key *key_p;

	key_size = माप(काष्ठा bpf_lpm_trie_key) + माप(__u32);
	key_p = alloca(key_size);
	क्रम (iter = 0; iter < info->iter; iter++)
		क्रम (i = 0; i < MAX_TEST_KEYS; i++) अणु
			/* first half of iterations in क्रमward order,
			 * and second half in backward order.
			 */
			j = (iter < (info->iter / 2)) ? i : MAX_TEST_KEYS - i - 1;
			key_p->prefixlen = info->key[j].prefixlen;
			स_नकल(key_p->data, &info->key[j].data, माप(__u32));
			अगर (info->cmd == 0) अणु
				__u32 value = j;
				/* update must succeed */
				निश्चित(bpf_map_update_elem(info->map_fd, key_p, &value, 0) == 0);
			पूर्ण अन्यथा अगर (info->cmd == 1) अणु
				ret = bpf_map_delete_elem(info->map_fd, key_p);
				निश्चित(ret == 0 || त्रुटि_सं == ENOENT);
			पूर्ण अन्यथा अगर (info->cmd == 2) अणु
				__u32 value;
				ret = bpf_map_lookup_elem(info->map_fd, key_p, &value);
				निश्चित(ret == 0 || त्रुटि_सं == ENOENT);
			पूर्ण अन्यथा अणु
				काष्ठा bpf_lpm_trie_key *next_key_p = alloca(key_size);
				ret = bpf_map_get_next_key(info->map_fd, key_p, next_key_p);
				निश्चित(ret == 0 || त्रुटि_सं == ENOENT || त्रुटि_सं == ENOMEM);
			पूर्ण
		पूर्ण

	// Pass successful निकास info back to the मुख्य thपढ़ो
	pthपढ़ो_निकास((व्योम *)info);
पूर्ण

अटल व्योम setup_lpm_mt_test_info(काष्ठा lpm_mt_test_info *info, पूर्णांक map_fd)
अणु
	info->iter = 2000;
	info->map_fd = map_fd;
	info->key[0].prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", &info->key[0].data);
	info->key[1].prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", &info->key[1].data);
	info->key[2].prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", &info->key[2].data);
	info->key[3].prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", &info->key[3].data);
पूर्ण

अटल व्योम test_lpm_multi_thपढ़ो(व्योम)
अणु
	काष्ठा lpm_mt_test_info info[4];
	माप_प्रकार key_size, value_size;
	pthपढ़ो_t thपढ़ो_id[4];
	पूर्णांक i, map_fd;
	व्योम *ret;

	/* create a trie */
	value_size = माप(__u32);
	key_size = माप(काष्ठा bpf_lpm_trie_key) + value_size;
	map_fd = bpf_create_map(BPF_MAP_TYPE_LPM_TRIE, key_size, value_size,
				100, BPF_F_NO_PREALLOC);

	/* create 4 thपढ़ोs to test update, delete, lookup and get_next_key */
	setup_lpm_mt_test_info(&info[0], map_fd);
	क्रम (i = 0; i < 4; i++) अणु
		अगर (i != 0)
			स_नकल(&info[i], &info[0], माप(info[i]));
		info[i].cmd = i;
		निश्चित(pthपढ़ो_create(&thपढ़ो_id[i], शून्य, &lpm_test_command, &info[i]) == 0);
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		निश्चित(pthपढ़ो_join(thपढ़ो_id[i], &ret) == 0 && ret == (व्योम *)&info[i]);

	बंद(map_fd);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक i;

	/* we want predictable, pseuकरो अक्रमom tests */
	बेक्रम(0xf00ba1);

	test_lpm_basic();
	test_lpm_order();

	/* Test with 8, 16, 24, 32, ... 128 bit prefix length */
	क्रम (i = 1; i <= 16; ++i)
		test_lpm_map(i);

	test_lpm_ipaddr();
	test_lpm_delete();
	test_lpm_get_next_key();
	test_lpm_multi_thपढ़ो();

	म_लिखो("test_lpm: OK\n");
	वापस 0;
पूर्ण
