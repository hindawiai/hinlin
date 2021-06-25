<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "allowedips.h"
#समावेश "peer.h"

अटल काष्ठा kmem_cache *node_cache;

अटल व्योम swap_endian(u8 *dst, स्थिर u8 *src, u8 bits)
अणु
	अगर (bits == 32) अणु
		*(u32 *)dst = be32_to_cpu(*(स्थिर __be32 *)src);
	पूर्ण अन्यथा अगर (bits == 128) अणु
		((u64 *)dst)[0] = be64_to_cpu(((स्थिर __be64 *)src)[0]);
		((u64 *)dst)[1] = be64_to_cpu(((स्थिर __be64 *)src)[1]);
	पूर्ण
पूर्ण

अटल व्योम copy_and_assign_cidr(काष्ठा allowedips_node *node, स्थिर u8 *src,
				 u8 cidr, u8 bits)
अणु
	node->cidr = cidr;
	node->bit_at_a = cidr / 8U;
#अगर_घोषित __LITTLE_ENDIAN
	node->bit_at_a ^= (bits / 8U - 1U) % 8U;
#पूर्ण_अगर
	node->bit_at_b = 7U - (cidr % 8U);
	node->bitlen = bits;
	स_नकल(node->bits, src, bits / 8U);
पूर्ण

अटल अंतरभूत u8 choose(काष्ठा allowedips_node *node, स्थिर u8 *key)
अणु
	वापस (key[node->bit_at_a] >> node->bit_at_b) & 1;
पूर्ण

अटल व्योम push_rcu(काष्ठा allowedips_node **stack,
		     काष्ठा allowedips_node __rcu *p, अचिन्हित पूर्णांक *len)
अणु
	अगर (rcu_access_poपूर्णांकer(p)) अणु
		WARN_ON(IS_ENABLED(DEBUG) && *len >= 128);
		stack[(*len)++] = rcu_dereference_raw(p);
	पूर्ण
पूर्ण

अटल व्योम node_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	kmem_cache_मुक्त(node_cache, container_of(rcu, काष्ठा allowedips_node, rcu));
पूर्ण

अटल व्योम root_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा allowedips_node *node, *stack[128] = अणु
		container_of(rcu, काष्ठा allowedips_node, rcu) पूर्ण;
	अचिन्हित पूर्णांक len = 1;

	जबतक (len > 0 && (node = stack[--len])) अणु
		push_rcu(stack, node->bit[0], &len);
		push_rcu(stack, node->bit[1], &len);
		kmem_cache_मुक्त(node_cache, node);
	पूर्ण
पूर्ण

अटल व्योम root_हटाओ_peer_lists(काष्ठा allowedips_node *root)
अणु
	काष्ठा allowedips_node *node, *stack[128] = अणु root पूर्ण;
	अचिन्हित पूर्णांक len = 1;

	जबतक (len > 0 && (node = stack[--len])) अणु
		push_rcu(stack, node->bit[0], &len);
		push_rcu(stack, node->bit[1], &len);
		अगर (rcu_access_poपूर्णांकer(node->peer))
			list_del(&node->peer_list);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक fls128(u64 a, u64 b)
अणु
	वापस a ? fls64(a) + 64U : fls64(b);
पूर्ण

अटल u8 common_bits(स्थिर काष्ठा allowedips_node *node, स्थिर u8 *key,
		      u8 bits)
अणु
	अगर (bits == 32)
		वापस 32U - fls(*(स्थिर u32 *)node->bits ^ *(स्थिर u32 *)key);
	अन्यथा अगर (bits == 128)
		वापस 128U - fls128(
			*(स्थिर u64 *)&node->bits[0] ^ *(स्थिर u64 *)&key[0],
			*(स्थिर u64 *)&node->bits[8] ^ *(स्थिर u64 *)&key[8]);
	वापस 0;
पूर्ण

अटल bool prefix_matches(स्थिर काष्ठा allowedips_node *node, स्थिर u8 *key,
			   u8 bits)
अणु
	/* This could be much faster अगर it actually just compared the common
	 * bits properly, by precomputing a mask bswap(~0 << (32 - cidr)), and
	 * the rest, but it turns out that common_bits is alपढ़ोy super fast on
	 * modern processors, even taking पूर्णांकo account the unक्रमtunate bswap.
	 * So, we just अंतरभूत it like this instead.
	 */
	वापस common_bits(node, key, bits) >= node->cidr;
पूर्ण

अटल काष्ठा allowedips_node *find_node(काष्ठा allowedips_node *trie, u8 bits,
					 स्थिर u8 *key)
अणु
	काष्ठा allowedips_node *node = trie, *found = शून्य;

	जबतक (node && prefix_matches(node, key, bits)) अणु
		अगर (rcu_access_poपूर्णांकer(node->peer))
			found = node;
		अगर (node->cidr == bits)
			अवरोध;
		node = rcu_dereference_bh(node->bit[choose(node, key)]);
	पूर्ण
	वापस found;
पूर्ण

/* Returns a strong reference to a peer */
अटल काष्ठा wg_peer *lookup(काष्ठा allowedips_node __rcu *root, u8 bits,
			      स्थिर व्योम *be_ip)
अणु
	/* Aligned so it can be passed to fls/fls64 */
	u8 ip[16] __aligned(__alignof(u64));
	काष्ठा allowedips_node *node;
	काष्ठा wg_peer *peer = शून्य;

	swap_endian(ip, be_ip, bits);

	rcu_पढ़ो_lock_bh();
retry:
	node = find_node(rcu_dereference_bh(root), bits, ip);
	अगर (node) अणु
		peer = wg_peer_get_maybe_zero(rcu_dereference_bh(node->peer));
		अगर (!peer)
			जाओ retry;
	पूर्ण
	rcu_पढ़ो_unlock_bh();
	वापस peer;
पूर्ण

अटल bool node_placement(काष्ठा allowedips_node __rcu *trie, स्थिर u8 *key,
			   u8 cidr, u8 bits, काष्ठा allowedips_node **rnode,
			   काष्ठा mutex *lock)
अणु
	काष्ठा allowedips_node *node = rcu_dereference_रक्षित(trie, lockdep_is_held(lock));
	काष्ठा allowedips_node *parent = शून्य;
	bool exact = false;

	जबतक (node && node->cidr <= cidr && prefix_matches(node, key, bits)) अणु
		parent = node;
		अगर (parent->cidr == cidr) अणु
			exact = true;
			अवरोध;
		पूर्ण
		node = rcu_dereference_रक्षित(parent->bit[choose(parent, key)], lockdep_is_held(lock));
	पूर्ण
	*rnode = parent;
	वापस exact;
पूर्ण

अटल अंतरभूत व्योम connect_node(काष्ठा allowedips_node **parent, u8 bit, काष्ठा allowedips_node *node)
अणु
	node->parent_bit_packed = (अचिन्हित दीर्घ)parent | bit;
	rcu_assign_poपूर्णांकer(*parent, node);
पूर्ण

अटल अंतरभूत व्योम choose_and_connect_node(काष्ठा allowedips_node *parent, काष्ठा allowedips_node *node)
अणु
	u8 bit = choose(parent, node->bits);
	connect_node(&parent->bit[bit], bit, node);
पूर्ण

अटल पूर्णांक add(काष्ठा allowedips_node __rcu **trie, u8 bits, स्थिर u8 *key,
	       u8 cidr, काष्ठा wg_peer *peer, काष्ठा mutex *lock)
अणु
	काष्ठा allowedips_node *node, *parent, *करोwn, *newnode;

	अगर (unlikely(cidr > bits || !peer))
		वापस -EINVAL;

	अगर (!rcu_access_poपूर्णांकer(*trie)) अणु
		node = kmem_cache_zalloc(node_cache, GFP_KERNEL);
		अगर (unlikely(!node))
			वापस -ENOMEM;
		RCU_INIT_POINTER(node->peer, peer);
		list_add_tail(&node->peer_list, &peer->allowedips_list);
		copy_and_assign_cidr(node, key, cidr, bits);
		connect_node(trie, 2, node);
		वापस 0;
	पूर्ण
	अगर (node_placement(*trie, key, cidr, bits, &node, lock)) अणु
		rcu_assign_poपूर्णांकer(node->peer, peer);
		list_move_tail(&node->peer_list, &peer->allowedips_list);
		वापस 0;
	पूर्ण

	newnode = kmem_cache_zalloc(node_cache, GFP_KERNEL);
	अगर (unlikely(!newnode))
		वापस -ENOMEM;
	RCU_INIT_POINTER(newnode->peer, peer);
	list_add_tail(&newnode->peer_list, &peer->allowedips_list);
	copy_and_assign_cidr(newnode, key, cidr, bits);

	अगर (!node) अणु
		करोwn = rcu_dereference_रक्षित(*trie, lockdep_is_held(lock));
	पूर्ण अन्यथा अणु
		स्थिर u8 bit = choose(node, key);
		करोwn = rcu_dereference_रक्षित(node->bit[bit], lockdep_is_held(lock));
		अगर (!करोwn) अणु
			connect_node(&node->bit[bit], bit, newnode);
			वापस 0;
		पूर्ण
	पूर्ण
	cidr = min(cidr, common_bits(करोwn, key, bits));
	parent = node;

	अगर (newnode->cidr == cidr) अणु
		choose_and_connect_node(newnode, करोwn);
		अगर (!parent)
			connect_node(trie, 2, newnode);
		अन्यथा
			choose_and_connect_node(parent, newnode);
		वापस 0;
	पूर्ण

	node = kmem_cache_zalloc(node_cache, GFP_KERNEL);
	अगर (unlikely(!node)) अणु
		list_del(&newnode->peer_list);
		kmem_cache_मुक्त(node_cache, newnode);
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&node->peer_list);
	copy_and_assign_cidr(node, newnode->bits, cidr, bits);

	choose_and_connect_node(node, करोwn);
	choose_and_connect_node(node, newnode);
	अगर (!parent)
		connect_node(trie, 2, node);
	अन्यथा
		choose_and_connect_node(parent, node);
	वापस 0;
पूर्ण

व्योम wg_allowedips_init(काष्ठा allowedips *table)
अणु
	table->root4 = table->root6 = शून्य;
	table->seq = 1;
पूर्ण

व्योम wg_allowedips_मुक्त(काष्ठा allowedips *table, काष्ठा mutex *lock)
अणु
	काष्ठा allowedips_node __rcu *old4 = table->root4, *old6 = table->root6;

	++table->seq;
	RCU_INIT_POINTER(table->root4, शून्य);
	RCU_INIT_POINTER(table->root6, शून्य);
	अगर (rcu_access_poपूर्णांकer(old4)) अणु
		काष्ठा allowedips_node *node = rcu_dereference_रक्षित(old4,
							lockdep_is_held(lock));

		root_हटाओ_peer_lists(node);
		call_rcu(&node->rcu, root_मुक्त_rcu);
	पूर्ण
	अगर (rcu_access_poपूर्णांकer(old6)) अणु
		काष्ठा allowedips_node *node = rcu_dereference_रक्षित(old6,
							lockdep_is_held(lock));

		root_हटाओ_peer_lists(node);
		call_rcu(&node->rcu, root_मुक्त_rcu);
	पूर्ण
पूर्ण

पूर्णांक wg_allowedips_insert_v4(काष्ठा allowedips *table, स्थिर काष्ठा in_addr *ip,
			    u8 cidr, काष्ठा wg_peer *peer, काष्ठा mutex *lock)
अणु
	/* Aligned so it can be passed to fls */
	u8 key[4] __aligned(__alignof(u32));

	++table->seq;
	swap_endian(key, (स्थिर u8 *)ip, 32);
	वापस add(&table->root4, 32, key, cidr, peer, lock);
पूर्ण

पूर्णांक wg_allowedips_insert_v6(काष्ठा allowedips *table, स्थिर काष्ठा in6_addr *ip,
			    u8 cidr, काष्ठा wg_peer *peer, काष्ठा mutex *lock)
अणु
	/* Aligned so it can be passed to fls64 */
	u8 key[16] __aligned(__alignof(u64));

	++table->seq;
	swap_endian(key, (स्थिर u8 *)ip, 128);
	वापस add(&table->root6, 128, key, cidr, peer, lock);
पूर्ण

व्योम wg_allowedips_हटाओ_by_peer(काष्ठा allowedips *table,
				  काष्ठा wg_peer *peer, काष्ठा mutex *lock)
अणु
	काष्ठा allowedips_node *node, *child, **parent_bit, *parent, *पंचांगp;
	bool मुक्त_parent;

	अगर (list_empty(&peer->allowedips_list))
		वापस;
	++table->seq;
	list_क्रम_each_entry_safe(node, पंचांगp, &peer->allowedips_list, peer_list) अणु
		list_del_init(&node->peer_list);
		RCU_INIT_POINTER(node->peer, शून्य);
		अगर (node->bit[0] && node->bit[1])
			जारी;
		child = rcu_dereference_रक्षित(node->bit[!rcu_access_poपूर्णांकer(node->bit[0])],
						  lockdep_is_held(lock));
		अगर (child)
			child->parent_bit_packed = node->parent_bit_packed;
		parent_bit = (काष्ठा allowedips_node **)(node->parent_bit_packed & ~3UL);
		*parent_bit = child;
		parent = (व्योम *)parent_bit -
			 दुरत्व(काष्ठा allowedips_node, bit[node->parent_bit_packed & 1]);
		मुक्त_parent = !rcu_access_poपूर्णांकer(node->bit[0]) &&
			      !rcu_access_poपूर्णांकer(node->bit[1]) &&
			      (node->parent_bit_packed & 3) <= 1 &&
			      !rcu_access_poपूर्णांकer(parent->peer);
		अगर (मुक्त_parent)
			child = rcu_dereference_रक्षित(
					parent->bit[!(node->parent_bit_packed & 1)],
					lockdep_is_held(lock));
		call_rcu(&node->rcu, node_मुक्त_rcu);
		अगर (!मुक्त_parent)
			जारी;
		अगर (child)
			child->parent_bit_packed = parent->parent_bit_packed;
		*(काष्ठा allowedips_node **)(parent->parent_bit_packed & ~3UL) = child;
		call_rcu(&parent->rcu, node_मुक्त_rcu);
	पूर्ण
पूर्ण

पूर्णांक wg_allowedips_पढ़ो_node(काष्ठा allowedips_node *node, u8 ip[16], u8 *cidr)
अणु
	स्थिर अचिन्हित पूर्णांक cidr_bytes = DIV_ROUND_UP(node->cidr, 8U);
	swap_endian(ip, node->bits, node->bitlen);
	स_रखो(ip + cidr_bytes, 0, node->bitlen / 8U - cidr_bytes);
	अगर (node->cidr)
		ip[cidr_bytes - 1U] &= ~0U << (-node->cidr % 8U);

	*cidr = node->cidr;
	वापस node->bitlen == 32 ? AF_INET : AF_INET6;
पूर्ण

/* Returns a strong reference to a peer */
काष्ठा wg_peer *wg_allowedips_lookup_dst(काष्ठा allowedips *table,
					 काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस lookup(table->root4, 32, &ip_hdr(skb)->daddr);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस lookup(table->root6, 128, &ipv6_hdr(skb)->daddr);
	वापस शून्य;
पूर्ण

/* Returns a strong reference to a peer */
काष्ठा wg_peer *wg_allowedips_lookup_src(काष्ठा allowedips *table,
					 काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP))
		वापस lookup(table->root4, 32, &ip_hdr(skb)->saddr);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस lookup(table->root6, 128, &ipv6_hdr(skb)->saddr);
	वापस शून्य;
पूर्ण

पूर्णांक __init wg_allowedips_slab_init(व्योम)
अणु
	node_cache = KMEM_CACHE(allowedips_node, 0);
	वापस node_cache ? 0 : -ENOMEM;
पूर्ण

व्योम wg_allowedips_slab_uninit(व्योम)
अणु
	rcu_barrier();
	kmem_cache_destroy(node_cache);
पूर्ण

#समावेश "selftest/allowedips.c"
