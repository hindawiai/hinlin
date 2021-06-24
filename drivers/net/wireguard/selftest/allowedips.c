<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This contains some basic अटल unit tests क्रम the allowedips data काष्ठाure.
 * It also has two additional modes that are disabled and meant to be used by
 * folks directly playing with this file. If you define the macro
 * DEBUG_PRINT_TRIE_GRAPHVIZ to be 1, then every समय there's a full tree in
 * memory, it will be prपूर्णांकed out as KERN_DEBUG in a क्रमmat that can be passed
 * to graphviz (the करोt command) to visualize it. If you define the macro
 * DEBUG_RANDOM_TRIE to be 1, then there will be an extremely costly set of
 * अक्रमomized tests करोne against a trivial implementation, which may take
 * upwards of a half-hour to complete. There's no set of users who should be
 * enabling these, and the only developers that should go anywhere near these
 * nobs are the ones who are पढ़ोing this comment.
 */

#अगर_घोषित DEBUG

#समावेश <linux/siphash.h>

अटल __init व्योम prपूर्णांक_node(काष्ठा allowedips_node *node, u8 bits)
अणु
	अक्षर *fmt_connection = KERN_DEBUG "\t\"%p/%d\" -> \"%p/%d\";\n";
	अक्षर *fmt_declaration = KERN_DEBUG "\t\"%p/%d\"[style=%s, color=\"#%06x\"];\n";
	u8 ip1[16], ip2[16], cidr1, cidr2;
	अक्षर *style = "dotted";
	u32 color = 0;

	अगर (node == शून्य)
		वापस;
	अगर (bits == 32) अणु
		fmt_connection = KERN_DEBUG "\t\"%pI4/%d\" -> \"%pI4/%d\";\n";
		fmt_declaration = KERN_DEBUG "\t\"%pI4/%d\"[style=%s, color=\"#%06x\"];\n";
	पूर्ण अन्यथा अगर (bits == 128) अणु
		fmt_connection = KERN_DEBUG "\t\"%pI6/%d\" -> \"%pI6/%d\";\n";
		fmt_declaration = KERN_DEBUG "\t\"%pI6/%d\"[style=%s, color=\"#%06x\"];\n";
	पूर्ण
	अगर (node->peer) अणु
		hsiphash_key_t key = अणु अणु 0 पूर्ण पूर्ण;

		स_नकल(&key, &node->peer, माप(node->peer));
		color = hsiphash_1u32(0xdeadbeef, &key) % 200 << 16 |
			hsiphash_1u32(0xbabecafe, &key) % 200 << 8 |
			hsiphash_1u32(0xabad1dea, &key) % 200;
		style = "bold";
	पूर्ण
	wg_allowedips_पढ़ो_node(node, ip1, &cidr1);
	prपूर्णांकk(fmt_declaration, ip1, cidr1, style, color);
	अगर (node->bit[0]) अणु
		wg_allowedips_पढ़ो_node(rcu_dereference_raw(node->bit[0]), ip2, &cidr2);
		prपूर्णांकk(fmt_connection, ip1, cidr1, ip2, cidr2);
	पूर्ण
	अगर (node->bit[1]) अणु
		wg_allowedips_पढ़ो_node(rcu_dereference_raw(node->bit[1]), ip2, &cidr2);
		prपूर्णांकk(fmt_connection, ip1, cidr1, ip2, cidr2);
	पूर्ण
	अगर (node->bit[0])
		prपूर्णांक_node(rcu_dereference_raw(node->bit[0]), bits);
	अगर (node->bit[1])
		prपूर्णांक_node(rcu_dereference_raw(node->bit[1]), bits);
पूर्ण

अटल __init व्योम prपूर्णांक_tree(काष्ठा allowedips_node __rcu *top, u8 bits)
अणु
	prपूर्णांकk(KERN_DEBUG "digraph trie {\n");
	prपूर्णांक_node(rcu_dereference_raw(top), bits);
	prपूर्णांकk(KERN_DEBUG "}\n");
पूर्ण

क्रमागत अणु
	NUM_PEERS = 2000,
	NUM_RAND_ROUTES = 400,
	NUM_MUTATED_ROUTES = 100,
	NUM_QUERIES = NUM_RAND_ROUTES * NUM_MUTATED_ROUTES * 30
पूर्ण;

काष्ठा horrible_allowedips अणु
	काष्ठा hlist_head head;
पूर्ण;

काष्ठा horrible_allowedips_node अणु
	काष्ठा hlist_node table;
	जोड़ nf_inet_addr ip;
	जोड़ nf_inet_addr mask;
	u8 ip_version;
	व्योम *value;
पूर्ण;

अटल __init व्योम horrible_allowedips_init(काष्ठा horrible_allowedips *table)
अणु
	INIT_HLIST_HEAD(&table->head);
पूर्ण

अटल __init व्योम horrible_allowedips_मुक्त(काष्ठा horrible_allowedips *table)
अणु
	काष्ठा horrible_allowedips_node *node;
	काष्ठा hlist_node *h;

	hlist_क्रम_each_entry_safe(node, h, &table->head, table) अणु
		hlist_del(&node->table);
		kमुक्त(node);
	पूर्ण
पूर्ण

अटल __init अंतरभूत जोड़ nf_inet_addr horrible_cidr_to_mask(u8 cidr)
अणु
	जोड़ nf_inet_addr mask;

	स_रखो(&mask, 0, माप(mask));
	स_रखो(&mask.all, 0xff, cidr / 8);
	अगर (cidr % 32)
		mask.all[cidr / 32] = (__क्रमce u32)htonl(
			(0xFFFFFFFFUL << (32 - (cidr % 32))) & 0xFFFFFFFFUL);
	वापस mask;
पूर्ण

अटल __init अंतरभूत u8 horrible_mask_to_cidr(जोड़ nf_inet_addr subnet)
अणु
	वापस hweight32(subnet.all[0]) + hweight32(subnet.all[1]) +
	       hweight32(subnet.all[2]) + hweight32(subnet.all[3]);
पूर्ण

अटल __init अंतरभूत व्योम
horrible_mask_self(काष्ठा horrible_allowedips_node *node)
अणु
	अगर (node->ip_version == 4) अणु
		node->ip.ip &= node->mask.ip;
	पूर्ण अन्यथा अगर (node->ip_version == 6) अणु
		node->ip.ip6[0] &= node->mask.ip6[0];
		node->ip.ip6[1] &= node->mask.ip6[1];
		node->ip.ip6[2] &= node->mask.ip6[2];
		node->ip.ip6[3] &= node->mask.ip6[3];
	पूर्ण
पूर्ण

अटल __init अंतरभूत bool
horrible_match_v4(स्थिर काष्ठा horrible_allowedips_node *node, काष्ठा in_addr *ip)
अणु
	वापस (ip->s_addr & node->mask.ip) == node->ip.ip;
पूर्ण

अटल __init अंतरभूत bool
horrible_match_v6(स्थिर काष्ठा horrible_allowedips_node *node, काष्ठा in6_addr *ip)
अणु
	वापस (ip->in6_u.u6_addr32[0] & node->mask.ip6[0]) == node->ip.ip6[0] &&
	       (ip->in6_u.u6_addr32[1] & node->mask.ip6[1]) == node->ip.ip6[1] &&
	       (ip->in6_u.u6_addr32[2] & node->mask.ip6[2]) == node->ip.ip6[2] &&
	       (ip->in6_u.u6_addr32[3] & node->mask.ip6[3]) == node->ip.ip6[3];
पूर्ण

अटल __init व्योम
horrible_insert_ordered(काष्ठा horrible_allowedips *table, काष्ठा horrible_allowedips_node *node)
अणु
	काष्ठा horrible_allowedips_node *other = शून्य, *where = शून्य;
	u8 my_cidr = horrible_mask_to_cidr(node->mask);

	hlist_क्रम_each_entry(other, &table->head, table) अणु
		अगर (other->ip_version == node->ip_version &&
		    !स_भेद(&other->mask, &node->mask, माप(जोड़ nf_inet_addr)) &&
		    !स_भेद(&other->ip, &node->ip, माप(जोड़ nf_inet_addr))) अणु
			other->value = node->value;
			kमुक्त(node);
			वापस;
		पूर्ण
	पूर्ण
	hlist_क्रम_each_entry(other, &table->head, table) अणु
		where = other;
		अगर (horrible_mask_to_cidr(other->mask) <= my_cidr)
			अवरोध;
	पूर्ण
	अगर (!other && !where)
		hlist_add_head(&node->table, &table->head);
	अन्यथा अगर (!other)
		hlist_add_behind(&node->table, &where->table);
	अन्यथा
		hlist_add_beक्रमe(&node->table, &where->table);
पूर्ण

अटल __init पूर्णांक
horrible_allowedips_insert_v4(काष्ठा horrible_allowedips *table,
			      काष्ठा in_addr *ip, u8 cidr, व्योम *value)
अणु
	काष्ठा horrible_allowedips_node *node = kzalloc(माप(*node), GFP_KERNEL);

	अगर (unlikely(!node))
		वापस -ENOMEM;
	node->ip.in = *ip;
	node->mask = horrible_cidr_to_mask(cidr);
	node->ip_version = 4;
	node->value = value;
	horrible_mask_self(node);
	horrible_insert_ordered(table, node);
	वापस 0;
पूर्ण

अटल __init पूर्णांक
horrible_allowedips_insert_v6(काष्ठा horrible_allowedips *table,
			      काष्ठा in6_addr *ip, u8 cidr, व्योम *value)
अणु
	काष्ठा horrible_allowedips_node *node = kzalloc(माप(*node), GFP_KERNEL);

	अगर (unlikely(!node))
		वापस -ENOMEM;
	node->ip.in6 = *ip;
	node->mask = horrible_cidr_to_mask(cidr);
	node->ip_version = 6;
	node->value = value;
	horrible_mask_self(node);
	horrible_insert_ordered(table, node);
	वापस 0;
पूर्ण

अटल __init व्योम *
horrible_allowedips_lookup_v4(काष्ठा horrible_allowedips *table, काष्ठा in_addr *ip)
अणु
	काष्ठा horrible_allowedips_node *node;

	hlist_क्रम_each_entry(node, &table->head, table) अणु
		अगर (node->ip_version == 4 && horrible_match_v4(node, ip))
			वापस node->value;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __init व्योम *
horrible_allowedips_lookup_v6(काष्ठा horrible_allowedips *table, काष्ठा in6_addr *ip)
अणु
	काष्ठा horrible_allowedips_node *node;

	hlist_क्रम_each_entry(node, &table->head, table) अणु
		अगर (node->ip_version == 6 && horrible_match_v6(node, ip))
			वापस node->value;
	पूर्ण
	वापस शून्य;
पूर्ण


अटल __init व्योम
horrible_allowedips_हटाओ_by_value(काष्ठा horrible_allowedips *table, व्योम *value)
अणु
	काष्ठा horrible_allowedips_node *node;
	काष्ठा hlist_node *h;

	hlist_क्रम_each_entry_safe(node, h, &table->head, table) अणु
		अगर (node->value != value)
			जारी;
		hlist_del(&node->table);
		kमुक्त(node);
	पूर्ण

पूर्ण

अटल __init bool अक्रमomized_test(व्योम)
अणु
	अचिन्हित पूर्णांक i, j, k, mutate_amount, cidr;
	u8 ip[16], mutate_mask[16], mutated[16];
	काष्ठा wg_peer **peers, *peer;
	काष्ठा horrible_allowedips h;
	DEFINE_MUTEX(mutex);
	काष्ठा allowedips t;
	bool ret = false;

	mutex_init(&mutex);

	wg_allowedips_init(&t);
	horrible_allowedips_init(&h);

	peers = kसुस्मृति(NUM_PEERS, माप(*peers), GFP_KERNEL);
	अगर (unlikely(!peers)) अणु
		pr_err("allowedips random self-test malloc: FAIL\n");
		जाओ मुक्त;
	पूर्ण
	क्रम (i = 0; i < NUM_PEERS; ++i) अणु
		peers[i] = kzalloc(माप(*peers[i]), GFP_KERNEL);
		अगर (unlikely(!peers[i])) अणु
			pr_err("allowedips random self-test malloc: FAIL\n");
			जाओ मुक्त;
		पूर्ण
		kref_init(&peers[i]->refcount);
		INIT_LIST_HEAD(&peers[i]->allowedips_list);
	पूर्ण

	mutex_lock(&mutex);

	क्रम (i = 0; i < NUM_RAND_ROUTES; ++i) अणु
		pअक्रमom_bytes(ip, 4);
		cidr = pअक्रमom_u32_max(32) + 1;
		peer = peers[pअक्रमom_u32_max(NUM_PEERS)];
		अगर (wg_allowedips_insert_v4(&t, (काष्ठा in_addr *)ip, cidr,
					    peer, &mutex) < 0) अणु
			pr_err("allowedips random self-test malloc: FAIL\n");
			जाओ मुक्त_locked;
		पूर्ण
		अगर (horrible_allowedips_insert_v4(&h, (काष्ठा in_addr *)ip,
						  cidr, peer) < 0) अणु
			pr_err("allowedips random self-test malloc: FAIL\n");
			जाओ मुक्त_locked;
		पूर्ण
		क्रम (j = 0; j < NUM_MUTATED_ROUTES; ++j) अणु
			स_नकल(mutated, ip, 4);
			pअक्रमom_bytes(mutate_mask, 4);
			mutate_amount = pअक्रमom_u32_max(32);
			क्रम (k = 0; k < mutate_amount / 8; ++k)
				mutate_mask[k] = 0xff;
			mutate_mask[k] = 0xff
					 << ((8 - (mutate_amount % 8)) % 8);
			क्रम (; k < 4; ++k)
				mutate_mask[k] = 0;
			क्रम (k = 0; k < 4; ++k)
				mutated[k] = (mutated[k] & mutate_mask[k]) |
					     (~mutate_mask[k] &
					      pअक्रमom_u32_max(256));
			cidr = pअक्रमom_u32_max(32) + 1;
			peer = peers[pअक्रमom_u32_max(NUM_PEERS)];
			अगर (wg_allowedips_insert_v4(&t,
						    (काष्ठा in_addr *)mutated,
						    cidr, peer, &mutex) < 0) अणु
				pr_err("allowedips random self-test malloc: FAIL\n");
				जाओ मुक्त_locked;
			पूर्ण
			अगर (horrible_allowedips_insert_v4(&h,
				(काष्ठा in_addr *)mutated, cidr, peer)) अणु
				pr_err("allowedips random self-test malloc: FAIL\n");
				जाओ मुक्त_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NUM_RAND_ROUTES; ++i) अणु
		pअक्रमom_bytes(ip, 16);
		cidr = pअक्रमom_u32_max(128) + 1;
		peer = peers[pअक्रमom_u32_max(NUM_PEERS)];
		अगर (wg_allowedips_insert_v6(&t, (काष्ठा in6_addr *)ip, cidr,
					    peer, &mutex) < 0) अणु
			pr_err("allowedips random self-test malloc: FAIL\n");
			जाओ मुक्त_locked;
		पूर्ण
		अगर (horrible_allowedips_insert_v6(&h, (काष्ठा in6_addr *)ip,
						  cidr, peer) < 0) अणु
			pr_err("allowedips random self-test malloc: FAIL\n");
			जाओ मुक्त_locked;
		पूर्ण
		क्रम (j = 0; j < NUM_MUTATED_ROUTES; ++j) अणु
			स_नकल(mutated, ip, 16);
			pअक्रमom_bytes(mutate_mask, 16);
			mutate_amount = pअक्रमom_u32_max(128);
			क्रम (k = 0; k < mutate_amount / 8; ++k)
				mutate_mask[k] = 0xff;
			mutate_mask[k] = 0xff
					 << ((8 - (mutate_amount % 8)) % 8);
			क्रम (; k < 4; ++k)
				mutate_mask[k] = 0;
			क्रम (k = 0; k < 4; ++k)
				mutated[k] = (mutated[k] & mutate_mask[k]) |
					     (~mutate_mask[k] &
					      pअक्रमom_u32_max(256));
			cidr = pअक्रमom_u32_max(128) + 1;
			peer = peers[pअक्रमom_u32_max(NUM_PEERS)];
			अगर (wg_allowedips_insert_v6(&t,
						    (काष्ठा in6_addr *)mutated,
						    cidr, peer, &mutex) < 0) अणु
				pr_err("allowedips random self-test malloc: FAIL\n");
				जाओ मुक्त_locked;
			पूर्ण
			अगर (horrible_allowedips_insert_v6(
				    &h, (काष्ठा in6_addr *)mutated, cidr,
				    peer)) अणु
				pr_err("allowedips random self-test malloc: FAIL\n");
				जाओ मुक्त_locked;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&mutex);

	अगर (IS_ENABLED(DEBUG_PRINT_TRIE_GRAPHVIZ)) अणु
		prपूर्णांक_tree(t.root4, 32);
		prपूर्णांक_tree(t.root6, 128);
	पूर्ण

	क्रम (j = 0;; ++j) अणु
		क्रम (i = 0; i < NUM_QUERIES; ++i) अणु
			pअक्रमom_bytes(ip, 4);
			अगर (lookup(t.root4, 32, ip) != horrible_allowedips_lookup_v4(&h, (काष्ठा in_addr *)ip)) अणु
				horrible_allowedips_lookup_v4(&h, (काष्ठा in_addr *)ip);
				pr_err("allowedips random v4 self-test: FAIL\n");
				जाओ मुक्त;
			पूर्ण
			pअक्रमom_bytes(ip, 16);
			अगर (lookup(t.root6, 128, ip) != horrible_allowedips_lookup_v6(&h, (काष्ठा in6_addr *)ip)) अणु
				pr_err("allowedips random v6 self-test: FAIL\n");
				जाओ मुक्त;
			पूर्ण
		पूर्ण
		अगर (j >= NUM_PEERS)
			अवरोध;
		mutex_lock(&mutex);
		wg_allowedips_हटाओ_by_peer(&t, peers[j], &mutex);
		mutex_unlock(&mutex);
		horrible_allowedips_हटाओ_by_value(&h, peers[j]);
	पूर्ण

	अगर (t.root4 || t.root6) अणु
		pr_err("allowedips random self-test removal: FAIL\n");
		जाओ मुक्त;
	पूर्ण

	ret = true;

मुक्त:
	mutex_lock(&mutex);
मुक्त_locked:
	wg_allowedips_मुक्त(&t, &mutex);
	mutex_unlock(&mutex);
	horrible_allowedips_मुक्त(&h);
	अगर (peers) अणु
		क्रम (i = 0; i < NUM_PEERS; ++i)
			kमुक्त(peers[i]);
	पूर्ण
	kमुक्त(peers);
	वापस ret;
पूर्ण

अटल __init अंतरभूत काष्ठा in_addr *ip4(u8 a, u8 b, u8 c, u8 d)
अणु
	अटल काष्ठा in_addr ip;
	u8 *split = (u8 *)&ip;

	split[0] = a;
	split[1] = b;
	split[2] = c;
	split[3] = d;
	वापस &ip;
पूर्ण

अटल __init अंतरभूत काष्ठा in6_addr *ip6(u32 a, u32 b, u32 c, u32 d)
अणु
	अटल काष्ठा in6_addr ip;
	__be32 *split = (__be32 *)&ip;

	split[0] = cpu_to_be32(a);
	split[1] = cpu_to_be32(b);
	split[2] = cpu_to_be32(c);
	split[3] = cpu_to_be32(d);
	वापस &ip;
पूर्ण

अटल __init काष्ठा wg_peer *init_peer(व्योम)
अणु
	काष्ठा wg_peer *peer = kzalloc(माप(*peer), GFP_KERNEL);

	अगर (!peer)
		वापस शून्य;
	kref_init(&peer->refcount);
	INIT_LIST_HEAD(&peer->allowedips_list);
	वापस peer;
पूर्ण

#घोषणा insert(version, mem, ipa, ipb, ipc, ipd, cidr)                       \
	wg_allowedips_insert_v##version(&t, ip##version(ipa, ipb, ipc, ipd), \
					cidr, mem, &mutex)

#घोषणा maybe_fail() करो अणु                                               \
		++i;                                                    \
		अगर (!_s) अणु                                              \
			pr_info("allowedips self-test %zu: FAIL\n", i); \
			success = false;                                \
		पूर्ण                                                       \
	पूर्ण जबतक (0)

#घोषणा test(version, mem, ipa, ipb, ipc, ipd) करो अणु                          \
		bool _s = lookup(t.root##version, (version) == 4 ? 32 : 128, \
				 ip##version(ipa, ipb, ipc, ipd)) == (mem);  \
		maybe_fail();                                                \
	पूर्ण जबतक (0)

#घोषणा test_negative(version, mem, ipa, ipb, ipc, ipd) करो अणु                 \
		bool _s = lookup(t.root##version, (version) == 4 ? 32 : 128, \
				 ip##version(ipa, ipb, ipc, ipd)) != (mem);  \
		maybe_fail();                                                \
	पूर्ण जबतक (0)

#घोषणा test_boolean(cond) करो अणु   \
		bool _s = (cond); \
		maybe_fail();     \
	पूर्ण जबतक (0)

bool __init wg_allowedips_selftest(व्योम)
अणु
	bool found_a = false, found_b = false, found_c = false, found_d = false,
	     found_e = false, found_other = false;
	काष्ठा wg_peer *a = init_peer(), *b = init_peer(), *c = init_peer(),
		       *d = init_peer(), *e = init_peer(), *f = init_peer(),
		       *g = init_peer(), *h = init_peer();
	काष्ठा allowedips_node *iter_node;
	bool success = false;
	काष्ठा allowedips t;
	DEFINE_MUTEX(mutex);
	काष्ठा in6_addr ip;
	माप_प्रकार i = 0, count = 0;
	__be64 part;

	mutex_init(&mutex);
	mutex_lock(&mutex);
	wg_allowedips_init(&t);

	अगर (!a || !b || !c || !d || !e || !f || !g || !h) अणु
		pr_err("allowedips self-test malloc: FAIL\n");
		जाओ मुक्त;
	पूर्ण

	insert(4, a, 192, 168, 4, 0, 24);
	insert(4, b, 192, 168, 4, 4, 32);
	insert(4, c, 192, 168, 0, 0, 16);
	insert(4, d, 192, 95, 5, 64, 27);
	/* replaces previous entry, and maskself is required */
	insert(4, c, 192, 95, 5, 65, 27);
	insert(6, d, 0x26075300, 0x60006b00, 0, 0xc05f0543, 128);
	insert(6, c, 0x26075300, 0x60006b00, 0, 0, 64);
	insert(4, e, 0, 0, 0, 0, 0);
	insert(6, e, 0, 0, 0, 0, 0);
	/* replaces previous entry */
	insert(6, f, 0, 0, 0, 0, 0);
	insert(6, g, 0x24046800, 0, 0, 0, 32);
	/* maskself is required */
	insert(6, h, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef, 64);
	insert(6, a, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef, 128);
	insert(6, c, 0x24446800, 0x40e40800, 0xdeaebeef, 0xdefbeef, 128);
	insert(6, b, 0x24446800, 0xf0e40800, 0xeeaebeef, 0, 98);
	insert(4, g, 64, 15, 112, 0, 20);
	/* maskself is required */
	insert(4, h, 64, 15, 123, 211, 25);
	insert(4, a, 10, 0, 0, 0, 25);
	insert(4, b, 10, 0, 0, 128, 25);
	insert(4, a, 10, 1, 0, 0, 30);
	insert(4, b, 10, 1, 0, 4, 30);
	insert(4, c, 10, 1, 0, 8, 29);
	insert(4, d, 10, 1, 0, 16, 29);

	अगर (IS_ENABLED(DEBUG_PRINT_TRIE_GRAPHVIZ)) अणु
		prपूर्णांक_tree(t.root4, 32);
		prपूर्णांक_tree(t.root6, 128);
	पूर्ण

	success = true;

	test(4, a, 192, 168, 4, 20);
	test(4, a, 192, 168, 4, 0);
	test(4, b, 192, 168, 4, 4);
	test(4, c, 192, 168, 200, 182);
	test(4, c, 192, 95, 5, 68);
	test(4, e, 192, 95, 5, 96);
	test(6, d, 0x26075300, 0x60006b00, 0, 0xc05f0543);
	test(6, c, 0x26075300, 0x60006b00, 0, 0xc02e01ee);
	test(6, f, 0x26075300, 0x60006b01, 0, 0);
	test(6, g, 0x24046800, 0x40040806, 0, 0x1006);
	test(6, g, 0x24046800, 0x40040806, 0x1234, 0x5678);
	test(6, f, 0x240467ff, 0x40040806, 0x1234, 0x5678);
	test(6, f, 0x24046801, 0x40040806, 0x1234, 0x5678);
	test(6, h, 0x24046800, 0x40040800, 0x1234, 0x5678);
	test(6, h, 0x24046800, 0x40040800, 0, 0);
	test(6, h, 0x24046800, 0x40040800, 0x10101010, 0x10101010);
	test(6, a, 0x24046800, 0x40040800, 0xdeadbeef, 0xdeadbeef);
	test(4, g, 64, 15, 116, 26);
	test(4, g, 64, 15, 127, 3);
	test(4, g, 64, 15, 123, 1);
	test(4, h, 64, 15, 123, 128);
	test(4, h, 64, 15, 123, 129);
	test(4, a, 10, 0, 0, 52);
	test(4, b, 10, 0, 0, 220);
	test(4, a, 10, 1, 0, 2);
	test(4, b, 10, 1, 0, 6);
	test(4, c, 10, 1, 0, 10);
	test(4, d, 10, 1, 0, 20);

	insert(4, a, 1, 0, 0, 0, 32);
	insert(4, a, 64, 0, 0, 0, 32);
	insert(4, a, 128, 0, 0, 0, 32);
	insert(4, a, 192, 0, 0, 0, 32);
	insert(4, a, 255, 0, 0, 0, 32);
	wg_allowedips_हटाओ_by_peer(&t, a, &mutex);
	test_negative(4, a, 1, 0, 0, 0);
	test_negative(4, a, 64, 0, 0, 0);
	test_negative(4, a, 128, 0, 0, 0);
	test_negative(4, a, 192, 0, 0, 0);
	test_negative(4, a, 255, 0, 0, 0);

	wg_allowedips_मुक्त(&t, &mutex);
	wg_allowedips_init(&t);
	insert(4, a, 192, 168, 0, 0, 16);
	insert(4, a, 192, 168, 0, 0, 24);
	wg_allowedips_हटाओ_by_peer(&t, a, &mutex);
	test_negative(4, a, 192, 168, 0, 1);

	/* These will hit the WARN_ON(len >= 128) in मुक्त_node अगर something
	 * goes wrong.
	 */
	क्रम (i = 0; i < 128; ++i) अणु
		part = cpu_to_be64(~(1LLU << (i % 64)));
		स_रखो(&ip, 0xff, 16);
		स_नकल((u8 *)&ip + (i < 64) * 8, &part, 8);
		wg_allowedips_insert_v6(&t, &ip, 128, a, &mutex);
	पूर्ण

	wg_allowedips_मुक्त(&t, &mutex);

	wg_allowedips_init(&t);
	insert(4, a, 192, 95, 5, 93, 27);
	insert(6, a, 0x26075300, 0x60006b00, 0, 0xc05f0543, 128);
	insert(4, a, 10, 1, 0, 20, 29);
	insert(6, a, 0x26075300, 0x6d8a6bf8, 0xdab1f1df, 0xc05f1523, 83);
	insert(6, a, 0x26075300, 0x6d8a6bf8, 0xdab1f1df, 0xc05f1523, 21);
	list_क्रम_each_entry(iter_node, &a->allowedips_list, peer_list) अणु
		u8 cidr, ip[16] __aligned(__alignof(u64));
		पूर्णांक family = wg_allowedips_पढ़ो_node(iter_node, ip, &cidr);

		count++;

		अगर (cidr == 27 && family == AF_INET &&
		    !स_भेद(ip, ip4(192, 95, 5, 64), माप(काष्ठा in_addr)))
			found_a = true;
		अन्यथा अगर (cidr == 128 && family == AF_INET6 &&
			 !स_भेद(ip, ip6(0x26075300, 0x60006b00, 0, 0xc05f0543),
				 माप(काष्ठा in6_addr)))
			found_b = true;
		अन्यथा अगर (cidr == 29 && family == AF_INET &&
			 !स_भेद(ip, ip4(10, 1, 0, 16), माप(काष्ठा in_addr)))
			found_c = true;
		अन्यथा अगर (cidr == 83 && family == AF_INET6 &&
			 !स_भेद(ip, ip6(0x26075300, 0x6d8a6bf8, 0xdab1e000, 0),
				 माप(काष्ठा in6_addr)))
			found_d = true;
		अन्यथा अगर (cidr == 21 && family == AF_INET6 &&
			 !स_भेद(ip, ip6(0x26075000, 0, 0, 0),
				 माप(काष्ठा in6_addr)))
			found_e = true;
		अन्यथा
			found_other = true;
	पूर्ण
	test_boolean(count == 5);
	test_boolean(found_a);
	test_boolean(found_b);
	test_boolean(found_c);
	test_boolean(found_d);
	test_boolean(found_e);
	test_boolean(!found_other);

	अगर (IS_ENABLED(DEBUG_RANDOM_TRIE) && success)
		success = अक्रमomized_test();

	अगर (success)
		pr_info("allowedips self-tests: pass\n");

मुक्त:
	wg_allowedips_मुक्त(&t, &mutex);
	kमुक्त(a);
	kमुक्त(b);
	kमुक्त(c);
	kमुक्त(d);
	kमुक्त(e);
	kमुक्त(f);
	kमुक्त(g);
	kमुक्त(h);
	mutex_unlock(&mutex);

	वापस success;
पूर्ण

#अघोषित test_negative
#अघोषित test
#अघोषित हटाओ
#अघोषित insert
#अघोषित init_peer

#पूर्ण_अगर
