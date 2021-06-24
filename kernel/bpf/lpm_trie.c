<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Longest prefix match list implementation
 *
 * Copyright (c) 2016,2017 Daniel Mack
 * Copyright (c) 2016 David Herrmann
 */

#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/ipv6.h>
#समावेश <uapi/linux/btf.h>

/* Intermediate node */
#घोषणा LPM_TREE_NODE_FLAG_IM BIT(0)

काष्ठा lpm_trie_node;

काष्ठा lpm_trie_node अणु
	काष्ठा rcu_head rcu;
	काष्ठा lpm_trie_node __rcu	*child[2];
	u32				prefixlen;
	u32				flags;
	u8				data[];
पूर्ण;

काष्ठा lpm_trie अणु
	काष्ठा bpf_map			map;
	काष्ठा lpm_trie_node __rcu	*root;
	माप_प्रकार				n_entries;
	माप_प्रकार				max_prefixlen;
	माप_प्रकार				data_size;
	spinlock_t			lock;
पूर्ण;

/* This trie implements a दीर्घest prefix match algorithm that can be used to
 * match IP addresses to a stored set of ranges.
 *
 * Data stored in @data of काष्ठा bpf_lpm_key and काष्ठा lpm_trie_node is
 * पूर्णांकerpreted as big endian, so data[0] stores the most signअगरicant byte.
 *
 * Match ranges are पूर्णांकernally stored in instances of काष्ठा lpm_trie_node
 * which each contain their prefix length as well as two poपूर्णांकers that may
 * lead to more nodes containing more specअगरic matches. Each node also stores
 * a value that is defined by and वापसed to userspace via the update_elem
 * and lookup functions.
 *
 * For instance, let's start with a trie that was created with a prefix length
 * of 32, so it can be used क्रम IPv4 addresses, and one single element that
 * matches 192.168.0.0/16. The data array would hence contain
 * [0xc0, 0xa8, 0x00, 0x00] in big-endian notation. This करोcumentation will
 * stick to IP-address notation क्रम पढ़ोability though.
 *
 * As the trie is empty initially, the new node (1) will be places as root
 * node, denoted as (R) in the example below. As there are no other node, both
 * child poपूर्णांकers are %शून्य.
 *
 *              +----------------+
 *              |       (1)  (R) |
 *              | 192.168.0.0/16 |
 *              |    value: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *
 * Next, let's add a new node (2) matching 192.168.0.0/24. As there is alपढ़ोy
 * a node with the same data and a smaller prefix (ie, a less specअगरic one),
 * node (2) will become a child of (1). In child index depends on the next bit
 * that is outside of what (1) matches, and that bit is 0, so (2) will be
 * child[0] of (1):
 *
 *              +----------------+
 *              |       (1)  (R) |
 *              | 192.168.0.0/16 |
 *              |    value: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *                   |
 *    +----------------+
 *    |       (2)      |
 *    | 192.168.0.0/24 |
 *    |    value: 2    |
 *    |   [0]    [1]   |
 *    +----------------+
 *
 * The child[1] slot of (1) could be filled with another node which has bit #17
 * (the next bit after the ones that (1) matches on) set to 1. For instance,
 * 192.168.128.0/24:
 *
 *              +----------------+
 *              |       (1)  (R) |
 *              | 192.168.0.0/16 |
 *              |    value: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *                   |      |
 *    +----------------+  +------------------+
 *    |       (2)      |  |        (3)       |
 *    | 192.168.0.0/24 |  | 192.168.128.0/24 |
 *    |    value: 2    |  |     value: 3     |
 *    |   [0]    [1]   |  |    [0]    [1]    |
 *    +----------------+  +------------------+
 *
 * Let's add another node (4) to the game क्रम 192.168.1.0/24. In order to place
 * it, node (1) is looked at first, and because (4) of the semantics laid out
 * above (bit #17 is 0), it would normally be attached to (1) as child[0].
 * However, that slot is alपढ़ोy allocated, so a new node is needed in between.
 * That node करोes not have a value attached to it and it will never be
 * वापसed to users as result of a lookup. It is only there to dअगरferentiate
 * the traversal further. It will get a prefix as wide as necessary to
 * distinguish its two children:
 *
 *                      +----------------+
 *                      |       (1)  (R) |
 *                      | 192.168.0.0/16 |
 *                      |    value: 1    |
 *                      |   [0]    [1]   |
 *                      +----------------+
 *                           |      |
 *            +----------------+  +------------------+
 *            |       (4)  (I) |  |        (3)       |
 *            | 192.168.0.0/23 |  | 192.168.128.0/24 |
 *            |    value: ---  |  |     value: 3     |
 *            |   [0]    [1]   |  |    [0]    [1]    |
 *            +----------------+  +------------------+
 *                 |      |
 *  +----------------+  +----------------+
 *  |       (2)      |  |       (5)      |
 *  | 192.168.0.0/24 |  | 192.168.1.0/24 |
 *  |    value: 2    |  |     value: 5   |
 *  |   [0]    [1]   |  |   [0]    [1]   |
 *  +----------------+  +----------------+
 *
 * 192.168.1.1/32 would be a child of (5) etc.
 *
 * An पूर्णांकermediate node will be turned पूर्णांकo a 'real' node on demand. In the
 * example above, (4) would be re-used अगर 192.168.0.0/23 is added to the trie.
 *
 * A fully populated trie would have a height of 32 nodes, as the trie was
 * created with a prefix length of 32.
 *
 * The lookup starts at the root node. If the current node matches and अगर there
 * is a child that can be used to become more specअगरic, the trie is traversed
 * करोwnwards. The last node in the traversal that is a non-पूर्णांकermediate one is
 * वापसed.
 */

अटल अंतरभूत पूर्णांक extract_bit(स्थिर u8 *data, माप_प्रकार index)
अणु
	वापस !!(data[index / 8] & (1 << (7 - (index % 8))));
पूर्ण

/**
 * दीर्घest_prefix_match() - determine the दीर्घest prefix
 * @trie:	The trie to get पूर्णांकernal sizes from
 * @node:	The node to operate on
 * @key:	The key to compare to @node
 *
 * Determine the दीर्घest prefix of @node that matches the bits in @key.
 */
अटल माप_प्रकार दीर्घest_prefix_match(स्थिर काष्ठा lpm_trie *trie,
				   स्थिर काष्ठा lpm_trie_node *node,
				   स्थिर काष्ठा bpf_lpm_trie_key *key)
अणु
	u32 limit = min(node->prefixlen, key->prefixlen);
	u32 prefixlen = 0, i = 0;

	BUILD_BUG_ON(दुरत्व(काष्ठा lpm_trie_node, data) % माप(u32));
	BUILD_BUG_ON(दुरत्व(काष्ठा bpf_lpm_trie_key, data) % माप(u32));

#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && defined(CONFIG_64BIT)

	/* data_size >= 16 has very small probability.
	 * We करो not use a loop क्रम optimal code generation.
	 */
	अगर (trie->data_size >= 8) अणु
		u64 dअगरf = be64_to_cpu(*(__be64 *)node->data ^
				       *(__be64 *)key->data);

		prefixlen = 64 - fls64(dअगरf);
		अगर (prefixlen >= limit)
			वापस limit;
		अगर (dअगरf)
			वापस prefixlen;
		i = 8;
	पूर्ण
#पूर्ण_अगर

	जबतक (trie->data_size >= i + 4) अणु
		u32 dअगरf = be32_to_cpu(*(__be32 *)&node->data[i] ^
				       *(__be32 *)&key->data[i]);

		prefixlen += 32 - fls(dअगरf);
		अगर (prefixlen >= limit)
			वापस limit;
		अगर (dअगरf)
			वापस prefixlen;
		i += 4;
	पूर्ण

	अगर (trie->data_size >= i + 2) अणु
		u16 dअगरf = be16_to_cpu(*(__be16 *)&node->data[i] ^
				       *(__be16 *)&key->data[i]);

		prefixlen += 16 - fls(dअगरf);
		अगर (prefixlen >= limit)
			वापस limit;
		अगर (dअगरf)
			वापस prefixlen;
		i += 2;
	पूर्ण

	अगर (trie->data_size >= i + 1) अणु
		prefixlen += 8 - fls(node->data[i] ^ key->data[i]);

		अगर (prefixlen >= limit)
			वापस limit;
	पूर्ण

	वापस prefixlen;
पूर्ण

/* Called from syscall or from eBPF program */
अटल व्योम *trie_lookup_elem(काष्ठा bpf_map *map, व्योम *_key)
अणु
	काष्ठा lpm_trie *trie = container_of(map, काष्ठा lpm_trie, map);
	काष्ठा lpm_trie_node *node, *found = शून्य;
	काष्ठा bpf_lpm_trie_key *key = _key;

	/* Start walking the trie from the root node ... */

	क्रम (node = rcu_dereference(trie->root); node;) अणु
		अचिन्हित पूर्णांक next_bit;
		माप_प्रकार matchlen;

		/* Determine the दीर्घest prefix of @node that matches @key.
		 * If it's the maximum possible prefix क्रम this trie, we have
		 * an exact match and can वापस it directly.
		 */
		matchlen = दीर्घest_prefix_match(trie, node, key);
		अगर (matchlen == trie->max_prefixlen) अणु
			found = node;
			अवरोध;
		पूर्ण

		/* If the number of bits that match is smaller than the prefix
		 * length of @node, bail out and वापस the node we have seen
		 * last in the traversal (ie, the parent).
		 */
		अगर (matchlen < node->prefixlen)
			अवरोध;

		/* Consider this node as वापस candidate unless it is an
		 * artअगरicially added पूर्णांकermediate one.
		 */
		अगर (!(node->flags & LPM_TREE_NODE_FLAG_IM))
			found = node;

		/* If the node match is fully satisfied, let's see अगर we can
		 * become more specअगरic. Determine the next bit in the key and
		 * traverse करोwn.
		 */
		next_bit = extract_bit(key->data, node->prefixlen);
		node = rcu_dereference(node->child[next_bit]);
	पूर्ण

	अगर (!found)
		वापस शून्य;

	वापस found->data + trie->data_size;
पूर्ण

अटल काष्ठा lpm_trie_node *lpm_trie_node_alloc(स्थिर काष्ठा lpm_trie *trie,
						 स्थिर व्योम *value)
अणु
	काष्ठा lpm_trie_node *node;
	माप_प्रकार size = माप(काष्ठा lpm_trie_node) + trie->data_size;

	अगर (value)
		size += trie->map.value_size;

	node = bpf_map_kदो_स्मृति_node(&trie->map, size, GFP_ATOMIC | __GFP_NOWARN,
				    trie->map.numa_node);
	अगर (!node)
		वापस शून्य;

	node->flags = 0;

	अगर (value)
		स_नकल(node->data + trie->data_size, value,
		       trie->map.value_size);

	वापस node;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक trie_update_elem(काष्ठा bpf_map *map,
			    व्योम *_key, व्योम *value, u64 flags)
अणु
	काष्ठा lpm_trie *trie = container_of(map, काष्ठा lpm_trie, map);
	काष्ठा lpm_trie_node *node, *im_node = शून्य, *new_node = शून्य;
	काष्ठा lpm_trie_node __rcu **slot;
	काष्ठा bpf_lpm_trie_key *key = _key;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक next_bit;
	माप_प्रकार matchlen = 0;
	पूर्णांक ret = 0;

	अगर (unlikely(flags > BPF_EXIST))
		वापस -EINVAL;

	अगर (key->prefixlen > trie->max_prefixlen)
		वापस -EINVAL;

	spin_lock_irqsave(&trie->lock, irq_flags);

	/* Allocate and fill a new node */

	अगर (trie->n_entries == trie->map.max_entries) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	new_node = lpm_trie_node_alloc(trie, value);
	अगर (!new_node) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	trie->n_entries++;

	new_node->prefixlen = key->prefixlen;
	RCU_INIT_POINTER(new_node->child[0], शून्य);
	RCU_INIT_POINTER(new_node->child[1], शून्य);
	स_नकल(new_node->data, key->data, trie->data_size);

	/* Now find a slot to attach the new node. To करो that, walk the tree
	 * from the root and match as many bits as possible क्रम each node until
	 * we either find an empty slot or a slot that needs to be replaced by
	 * an पूर्णांकermediate node.
	 */
	slot = &trie->root;

	जबतक ((node = rcu_dereference_रक्षित(*slot,
					lockdep_is_held(&trie->lock)))) अणु
		matchlen = दीर्घest_prefix_match(trie, node, key);

		अगर (node->prefixlen != matchlen ||
		    node->prefixlen == key->prefixlen ||
		    node->prefixlen == trie->max_prefixlen)
			अवरोध;

		next_bit = extract_bit(key->data, node->prefixlen);
		slot = &node->child[next_bit];
	पूर्ण

	/* If the slot is empty (a मुक्त child poपूर्णांकer or an empty root),
	 * simply assign the @new_node to that slot and be करोne.
	 */
	अगर (!node) अणु
		rcu_assign_poपूर्णांकer(*slot, new_node);
		जाओ out;
	पूर्ण

	/* If the slot we picked alपढ़ोy exists, replace it with @new_node
	 * which alपढ़ोy has the correct data array set.
	 */
	अगर (node->prefixlen == matchlen) अणु
		new_node->child[0] = node->child[0];
		new_node->child[1] = node->child[1];

		अगर (!(node->flags & LPM_TREE_NODE_FLAG_IM))
			trie->n_entries--;

		rcu_assign_poपूर्णांकer(*slot, new_node);
		kमुक्त_rcu(node, rcu);

		जाओ out;
	पूर्ण

	/* If the new node matches the prefix completely, it must be inserted
	 * as an ancestor. Simply insert it between @node and *@slot.
	 */
	अगर (matchlen == key->prefixlen) अणु
		next_bit = extract_bit(node->data, matchlen);
		rcu_assign_poपूर्णांकer(new_node->child[next_bit], node);
		rcu_assign_poपूर्णांकer(*slot, new_node);
		जाओ out;
	पूर्ण

	im_node = lpm_trie_node_alloc(trie, शून्य);
	अगर (!im_node) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	im_node->prefixlen = matchlen;
	im_node->flags |= LPM_TREE_NODE_FLAG_IM;
	स_नकल(im_node->data, node->data, trie->data_size);

	/* Now determine which child to install in which slot */
	अगर (extract_bit(key->data, matchlen)) अणु
		rcu_assign_poपूर्णांकer(im_node->child[0], node);
		rcu_assign_poपूर्णांकer(im_node->child[1], new_node);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(im_node->child[0], new_node);
		rcu_assign_poपूर्णांकer(im_node->child[1], node);
	पूर्ण

	/* Finally, assign the पूर्णांकermediate node to the determined spot */
	rcu_assign_poपूर्णांकer(*slot, im_node);

out:
	अगर (ret) अणु
		अगर (new_node)
			trie->n_entries--;

		kमुक्त(new_node);
		kमुक्त(im_node);
	पूर्ण

	spin_unlock_irqrestore(&trie->lock, irq_flags);

	वापस ret;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक trie_delete_elem(काष्ठा bpf_map *map, व्योम *_key)
अणु
	काष्ठा lpm_trie *trie = container_of(map, काष्ठा lpm_trie, map);
	काष्ठा bpf_lpm_trie_key *key = _key;
	काष्ठा lpm_trie_node __rcu **trim, **trim2;
	काष्ठा lpm_trie_node *node, *parent;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक next_bit;
	माप_प्रकार matchlen = 0;
	पूर्णांक ret = 0;

	अगर (key->prefixlen > trie->max_prefixlen)
		वापस -EINVAL;

	spin_lock_irqsave(&trie->lock, irq_flags);

	/* Walk the tree looking क्रम an exact key/length match and keeping
	 * track of the path we traverse.  We will need to know the node
	 * we wish to delete, and the slot that poपूर्णांकs to the node we want
	 * to delete.  We may also need to know the nodes parent and the
	 * slot that contains it.
	 */
	trim = &trie->root;
	trim2 = trim;
	parent = शून्य;
	जबतक ((node = rcu_dereference_रक्षित(
		       *trim, lockdep_is_held(&trie->lock)))) अणु
		matchlen = दीर्घest_prefix_match(trie, node, key);

		अगर (node->prefixlen != matchlen ||
		    node->prefixlen == key->prefixlen)
			अवरोध;

		parent = node;
		trim2 = trim;
		next_bit = extract_bit(key->data, node->prefixlen);
		trim = &node->child[next_bit];
	पूर्ण

	अगर (!node || node->prefixlen != key->prefixlen ||
	    node->prefixlen != matchlen ||
	    (node->flags & LPM_TREE_NODE_FLAG_IM)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	trie->n_entries--;

	/* If the node we are removing has two children, simply mark it
	 * as पूर्णांकermediate and we are करोne.
	 */
	अगर (rcu_access_poपूर्णांकer(node->child[0]) &&
	    rcu_access_poपूर्णांकer(node->child[1])) अणु
		node->flags |= LPM_TREE_NODE_FLAG_IM;
		जाओ out;
	पूर्ण

	/* If the parent of the node we are about to delete is an पूर्णांकermediate
	 * node, and the deleted node करोesn't have any children, we can delete
	 * the पूर्णांकermediate parent as well and promote its other child
	 * up the tree.  Doing this मुख्यtains the invariant that all
	 * पूर्णांकermediate nodes have exactly 2 children and that there are no
	 * unnecessary पूर्णांकermediate nodes in the tree.
	 */
	अगर (parent && (parent->flags & LPM_TREE_NODE_FLAG_IM) &&
	    !node->child[0] && !node->child[1]) अणु
		अगर (node == rcu_access_poपूर्णांकer(parent->child[0]))
			rcu_assign_poपूर्णांकer(
				*trim2, rcu_access_poपूर्णांकer(parent->child[1]));
		अन्यथा
			rcu_assign_poपूर्णांकer(
				*trim2, rcu_access_poपूर्णांकer(parent->child[0]));
		kमुक्त_rcu(parent, rcu);
		kमुक्त_rcu(node, rcu);
		जाओ out;
	पूर्ण

	/* The node we are removing has either zero or one child. If there
	 * is a child, move it पूर्णांकo the हटाओd node's slot then delete
	 * the node.  Otherwise just clear the slot and delete the node.
	 */
	अगर (node->child[0])
		rcu_assign_poपूर्णांकer(*trim, rcu_access_poपूर्णांकer(node->child[0]));
	अन्यथा अगर (node->child[1])
		rcu_assign_poपूर्णांकer(*trim, rcu_access_poपूर्णांकer(node->child[1]));
	अन्यथा
		RCU_INIT_POINTER(*trim, शून्य);
	kमुक्त_rcu(node, rcu);

out:
	spin_unlock_irqrestore(&trie->lock, irq_flags);

	वापस ret;
पूर्ण

#घोषणा LPM_DATA_SIZE_MAX	256
#घोषणा LPM_DATA_SIZE_MIN	1

#घोषणा LPM_VAL_SIZE_MAX	(KMALLOC_MAX_SIZE - LPM_DATA_SIZE_MAX - \
				 माप(काष्ठा lpm_trie_node))
#घोषणा LPM_VAL_SIZE_MIN	1

#घोषणा LPM_KEY_SIZE(X)		(माप(काष्ठा bpf_lpm_trie_key) + (X))
#घोषणा LPM_KEY_SIZE_MAX	LPM_KEY_SIZE(LPM_DATA_SIZE_MAX)
#घोषणा LPM_KEY_SIZE_MIN	LPM_KEY_SIZE(LPM_DATA_SIZE_MIN)

#घोषणा LPM_CREATE_FLAG_MASK	(BPF_F_NO_PREALLOC | BPF_F_NUMA_NODE |	\
				 BPF_F_ACCESS_MASK)

अटल काष्ठा bpf_map *trie_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा lpm_trie *trie;

	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	/* check sanity of attributes */
	अगर (attr->max_entries == 0 ||
	    !(attr->map_flags & BPF_F_NO_PREALLOC) ||
	    attr->map_flags & ~LPM_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags) ||
	    attr->key_size < LPM_KEY_SIZE_MIN ||
	    attr->key_size > LPM_KEY_SIZE_MAX ||
	    attr->value_size < LPM_VAL_SIZE_MIN ||
	    attr->value_size > LPM_VAL_SIZE_MAX)
		वापस ERR_PTR(-EINVAL);

	trie = kzalloc(माप(*trie), GFP_USER | __GFP_NOWARN | __GFP_ACCOUNT);
	अगर (!trie)
		वापस ERR_PTR(-ENOMEM);

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&trie->map, attr);
	trie->data_size = attr->key_size -
			  दुरत्व(काष्ठा bpf_lpm_trie_key, data);
	trie->max_prefixlen = trie->data_size * 8;

	spin_lock_init(&trie->lock);

	वापस &trie->map;
पूर्ण

अटल व्योम trie_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा lpm_trie *trie = container_of(map, काष्ठा lpm_trie, map);
	काष्ठा lpm_trie_node __rcu **slot;
	काष्ठा lpm_trie_node *node;

	/* Always start at the root and walk करोwn to a node that has no
	 * children. Then मुक्त that node, nullअगरy its reference in the parent
	 * and start over.
	 */

	क्रम (;;) अणु
		slot = &trie->root;

		क्रम (;;) अणु
			node = rcu_dereference_रक्षित(*slot, 1);
			अगर (!node)
				जाओ out;

			अगर (rcu_access_poपूर्णांकer(node->child[0])) अणु
				slot = &node->child[0];
				जारी;
			पूर्ण

			अगर (rcu_access_poपूर्णांकer(node->child[1])) अणु
				slot = &node->child[1];
				जारी;
			पूर्ण

			kमुक्त(node);
			RCU_INIT_POINTER(*slot, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(trie);
पूर्ण

अटल पूर्णांक trie_get_next_key(काष्ठा bpf_map *map, व्योम *_key, व्योम *_next_key)
अणु
	काष्ठा lpm_trie_node *node, *next_node = शून्य, *parent, *search_root;
	काष्ठा lpm_trie *trie = container_of(map, काष्ठा lpm_trie, map);
	काष्ठा bpf_lpm_trie_key *key = _key, *next_key = _next_key;
	काष्ठा lpm_trie_node **node_stack = शून्य;
	पूर्णांक err = 0, stack_ptr = -1;
	अचिन्हित पूर्णांक next_bit;
	माप_प्रकार matchlen;

	/* The get_next_key follows postorder. For the 4 node example in
	 * the top of this file, the trie_get_next_key() वापसs the following
	 * one after another:
	 *   192.168.0.0/24
	 *   192.168.1.0/24
	 *   192.168.128.0/24
	 *   192.168.0.0/16
	 *
	 * The idea is to वापस more specअगरic keys beक्रमe less specअगरic ones.
	 */

	/* Empty trie */
	search_root = rcu_dereference(trie->root);
	अगर (!search_root)
		वापस -ENOENT;

	/* For invalid key, find the lefपंचांगost node in the trie */
	अगर (!key || key->prefixlen > trie->max_prefixlen)
		जाओ find_lefपंचांगost;

	node_stack = kदो_स्मृति_array(trie->max_prefixlen,
				   माप(काष्ठा lpm_trie_node *),
				   GFP_ATOMIC | __GFP_NOWARN);
	अगर (!node_stack)
		वापस -ENOMEM;

	/* Try to find the exact node क्रम the given key */
	क्रम (node = search_root; node;) अणु
		node_stack[++stack_ptr] = node;
		matchlen = दीर्घest_prefix_match(trie, node, key);
		अगर (node->prefixlen != matchlen ||
		    node->prefixlen == key->prefixlen)
			अवरोध;

		next_bit = extract_bit(key->data, node->prefixlen);
		node = rcu_dereference(node->child[next_bit]);
	पूर्ण
	अगर (!node || node->prefixlen != key->prefixlen ||
	    (node->flags & LPM_TREE_NODE_FLAG_IM))
		जाओ find_lefपंचांगost;

	/* The node with the exactly-matching key has been found,
	 * find the first node in postorder after the matched node.
	 */
	node = node_stack[stack_ptr];
	जबतक (stack_ptr > 0) अणु
		parent = node_stack[stack_ptr - 1];
		अगर (rcu_dereference(parent->child[0]) == node) अणु
			search_root = rcu_dereference(parent->child[1]);
			अगर (search_root)
				जाओ find_lefपंचांगost;
		पूर्ण
		अगर (!(parent->flags & LPM_TREE_NODE_FLAG_IM)) अणु
			next_node = parent;
			जाओ करो_copy;
		पूर्ण

		node = parent;
		stack_ptr--;
	पूर्ण

	/* did not find anything */
	err = -ENOENT;
	जाओ मुक्त_stack;

find_lefपंचांगost:
	/* Find the lefपंचांगost non-पूर्णांकermediate node, all पूर्णांकermediate nodes
	 * have exact two children, so this function will never वापस शून्य.
	 */
	क्रम (node = search_root; node;) अणु
		अगर (node->flags & LPM_TREE_NODE_FLAG_IM) अणु
			node = rcu_dereference(node->child[0]);
		पूर्ण अन्यथा अणु
			next_node = node;
			node = rcu_dereference(node->child[0]);
			अगर (!node)
				node = rcu_dereference(next_node->child[1]);
		पूर्ण
	पूर्ण
करो_copy:
	next_key->prefixlen = next_node->prefixlen;
	स_नकल((व्योम *)next_key + दुरत्व(काष्ठा bpf_lpm_trie_key, data),
	       next_node->data, trie->data_size);
मुक्त_stack:
	kमुक्त(node_stack);
	वापस err;
पूर्ण

अटल पूर्णांक trie_check_btf(स्थिर काष्ठा bpf_map *map,
			  स्थिर काष्ठा btf *btf,
			  स्थिर काष्ठा btf_type *key_type,
			  स्थिर काष्ठा btf_type *value_type)
अणु
	/* Keys must have काष्ठा bpf_lpm_trie_key embedded. */
	वापस BTF_INFO_KIND(key_type->info) != BTF_KIND_STRUCT ?
	       -EINVAL : 0;
पूर्ण

अटल पूर्णांक trie_map_btf_id;
स्थिर काष्ठा bpf_map_ops trie_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = trie_alloc,
	.map_मुक्त = trie_मुक्त,
	.map_get_next_key = trie_get_next_key,
	.map_lookup_elem = trie_lookup_elem,
	.map_update_elem = trie_update_elem,
	.map_delete_elem = trie_delete_elem,
	.map_lookup_batch = generic_map_lookup_batch,
	.map_update_batch = generic_map_update_batch,
	.map_delete_batch = generic_map_delete_batch,
	.map_check_btf = trie_check_btf,
	.map_btf_name = "lpm_trie",
	.map_btf_id = &trie_map_btf_id,
पूर्ण;
