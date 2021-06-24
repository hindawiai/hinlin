<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *   Robert Olsson <robert.olsson@its.uu.se> Uppsala Universitet
 *     & Swedish University of Agricultural Sciences.
 *
 *   Jens Laas <jens.laas@data.slu.se> Swedish University of
 *     Agricultural Sciences.
 *
 *   Hans Liss <hans.liss@its.uu.se>  Uppsala Universitet
 *
 * This work is based on the LPC-trie which is originally described in:
 *
 * An experimental study of compression methods क्रम dynamic tries
 * Stefan Nilsson and Matti Tikkanen. Algorithmica, 33(1):19-33, 2002.
 * https://www.csc.kth.se/~snilsson/software/dyntrie2/
 *
 * IP-address lookup using LC-tries. Stefan Nilsson and Gunnar Karlsson
 * IEEE Journal on Selected Areas in Communications, 17(6):1083-1092, June 1999
 *
 * Code from fib_hash has been reused which includes the following header:
 *
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IPv4 FIB: lookup engine and मुख्यtenance routines.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Substantial contributions to this work comes from:
 *
 *		David S. Miller, <davem@davemloft.net>
 *		Stephen Hemminger <shemminger@osdl.org>
 *		Paul E. McKenney <paulmck@us.ibm.com>
 *		Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/cache.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/ip_fib.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <trace/events/fib.h>
#समावेश "fib_lookup.h"

अटल पूर्णांक call_fib_entry_notअगरier(काष्ठा notअगरier_block *nb,
				   क्रमागत fib_event_type event_type, u32 dst,
				   पूर्णांक dst_len, काष्ठा fib_alias *fa,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.dst = dst,
		.dst_len = dst_len,
		.fi = fa->fa_info,
		.tos = fa->fa_tos,
		.type = fa->fa_type,
		.tb_id = fa->tb_id,
	पूर्ण;
	वापस call_fib4_notअगरier(nb, event_type, &info.info);
पूर्ण

अटल पूर्णांक call_fib_entry_notअगरiers(काष्ठा net *net,
				    क्रमागत fib_event_type event_type, u32 dst,
				    पूर्णांक dst_len, काष्ठा fib_alias *fa,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.dst = dst,
		.dst_len = dst_len,
		.fi = fa->fa_info,
		.tos = fa->fa_tos,
		.type = fa->fa_type,
		.tb_id = fa->tb_id,
	पूर्ण;
	वापस call_fib4_notअगरiers(net, event_type, &info.info);
पूर्ण

#घोषणा MAX_STAT_DEPTH 32

#घोषणा KEYLENGTH	(8*माप(t_key))
#घोषणा KEY_MAX		((t_key)~0)

प्रकार अचिन्हित पूर्णांक t_key;

#घोषणा IS_TRIE(n)	((n)->pos >= KEYLENGTH)
#घोषणा IS_TNODE(n)	((n)->bits)
#घोषणा IS_LEAF(n)	(!(n)->bits)

काष्ठा key_vector अणु
	t_key key;
	अचिन्हित अक्षर pos;		/* 2log(KEYLENGTH) bits needed */
	अचिन्हित अक्षर bits;		/* 2log(KEYLENGTH) bits needed */
	अचिन्हित अक्षर slen;
	जोड़ अणु
		/* This list poपूर्णांकer अगर valid अगर (pos | bits) == 0 (LEAF) */
		काष्ठा hlist_head leaf;
		/* This array is valid अगर (pos | bits) > 0 (TNODE) */
		काष्ठा key_vector __rcu *tnode[0];
	पूर्ण;
पूर्ण;

काष्ठा tnode अणु
	काष्ठा rcu_head rcu;
	t_key empty_children;		/* KEYLENGTH bits needed */
	t_key full_children;		/* KEYLENGTH bits needed */
	काष्ठा key_vector __rcu *parent;
	काष्ठा key_vector kv[1];
#घोषणा tn_bits kv[0].bits
पूर्ण;

#घोषणा TNODE_SIZE(n)	दुरत्व(काष्ठा tnode, kv[0].tnode[n])
#घोषणा LEAF_SIZE	TNODE_SIZE(1)

#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
काष्ठा trie_use_stats अणु
	अचिन्हित पूर्णांक माला_लो;
	अचिन्हित पूर्णांक backtrack;
	अचिन्हित पूर्णांक semantic_match_passed;
	अचिन्हित पूर्णांक semantic_match_miss;
	अचिन्हित पूर्णांक null_node_hit;
	अचिन्हित पूर्णांक resize_node_skipped;
पूर्ण;
#पूर्ण_अगर

काष्ठा trie_stat अणु
	अचिन्हित पूर्णांक totdepth;
	अचिन्हित पूर्णांक maxdepth;
	अचिन्हित पूर्णांक tnodes;
	अचिन्हित पूर्णांक leaves;
	अचिन्हित पूर्णांक nullpoपूर्णांकers;
	अचिन्हित पूर्णांक prefixes;
	अचिन्हित पूर्णांक nodesizes[MAX_STAT_DEPTH];
पूर्ण;

काष्ठा trie अणु
	काष्ठा key_vector kv[1];
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	काष्ठा trie_use_stats __percpu *stats;
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा key_vector *resize(काष्ठा trie *t, काष्ठा key_vector *tn);
अटल अचिन्हित पूर्णांक tnode_मुक्त_size;

/*
 * synchronize_rcu after call_rcu क्रम outstanding dirty memory; it should be
 * especially useful beक्रमe resizing the root node with PREEMPT_NONE configs;
 * the value was obtained experimentally, aiming to aव्योम visible slowकरोwn.
 */
अचिन्हित पूर्णांक sysctl_fib_sync_mem = 512 * 1024;
अचिन्हित पूर्णांक sysctl_fib_sync_mem_min = 64 * 1024;
अचिन्हित पूर्णांक sysctl_fib_sync_mem_max = 64 * 1024 * 1024;

अटल काष्ठा kmem_cache *fn_alias_kmem __ro_after_init;
अटल काष्ठा kmem_cache *trie_leaf_kmem __ro_after_init;

अटल अंतरभूत काष्ठा tnode *tn_info(काष्ठा key_vector *kv)
अणु
	वापस container_of(kv, काष्ठा tnode, kv[0]);
पूर्ण

/* caller must hold RTNL */
#घोषणा node_parent(tn) rtnl_dereference(tn_info(tn)->parent)
#घोषणा get_child(tn, i) rtnl_dereference((tn)->tnode[i])

/* caller must hold RCU पढ़ो lock or RTNL */
#घोषणा node_parent_rcu(tn) rcu_dereference_rtnl(tn_info(tn)->parent)
#घोषणा get_child_rcu(tn, i) rcu_dereference_rtnl((tn)->tnode[i])

/* wrapper क्रम rcu_assign_poपूर्णांकer */
अटल अंतरभूत व्योम node_set_parent(काष्ठा key_vector *n, काष्ठा key_vector *tp)
अणु
	अगर (n)
		rcu_assign_poपूर्णांकer(tn_info(n)->parent, tp);
पूर्ण

#घोषणा NODE_INIT_PARENT(n, p) RCU_INIT_POINTER(tn_info(n)->parent, p)

/* This provides us with the number of children in this node, in the हाल of a
 * leaf this will वापस 0 meaning none of the children are accessible.
 */
अटल अंतरभूत अचिन्हित दीर्घ child_length(स्थिर काष्ठा key_vector *tn)
अणु
	वापस (1ul << tn->bits) & ~(1ul);
पूर्ण

#घोषणा get_cindex(key, kv) (((key) ^ (kv)->key) >> (kv)->pos)

अटल अंतरभूत अचिन्हित दीर्घ get_index(t_key key, काष्ठा key_vector *kv)
अणु
	अचिन्हित दीर्घ index = key ^ kv->key;

	अगर ((BITS_PER_LONG <= KEYLENGTH) && (KEYLENGTH == kv->pos))
		वापस 0;

	वापस index >> kv->pos;
पूर्ण

/* To understand this stuff, an understanding of keys and all their bits is
 * necessary. Every node in the trie has a key associated with it, but not
 * all of the bits in that key are signअगरicant.
 *
 * Consider a node 'n' and its parent 'tp'.
 *
 * If n is a leaf, every bit in its key is signअगरicant. Its presence is
 * necessitated by path compression, since during a tree traversal (when
 * searching क्रम a leaf - unless we are करोing an insertion) we will completely
 * ignore all skipped bits we encounter. Thus we need to verअगरy, at the end of
 * a potentially successful search, that we have indeed been walking the
 * correct key path.
 *
 * Note that we can never "miss" the correct key in the tree अगर present by
 * following the wrong path. Path compression ensures that segments of the key
 * that are the same क्रम all keys with a given prefix are skipped, but the
 * skipped part *is* identical क्रम each node in the subtrie below the skipped
 * bit! trie_insert() in this implementation takes care of that.
 *
 * अगर n is an पूर्णांकernal node - a 'tnode' here, the various parts of its key
 * have many dअगरferent meanings.
 *
 * Example:
 * _________________________________________________________________
 * | i | i | i | i | i | i | i | N | N | N | S | S | S | S | S | C |
 * -----------------------------------------------------------------
 *  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16
 *
 * _________________________________________________________________
 * | C | C | C | u | u | u | u | u | u | u | u | u | u | u | u | u |
 * -----------------------------------------------------------------
 *  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1   0
 *
 * tp->pos = 22
 * tp->bits = 3
 * n->pos = 13
 * n->bits = 4
 *
 * First, let's just ignore the bits that come beक्रमe the parent tp, that is
 * the bits from (tp->pos + tp->bits) to 31. They are *known* but at this
 * poपूर्णांक we करो not use them क्रम anything.
 *
 * The bits from (tp->pos) to (tp->pos + tp->bits - 1) - "N", above - are the
 * index पूर्णांकo the parent's child array. That is, they will be used to find
 * 'n' among tp's children.
 *
 * The bits from (n->pos + n->bits) to (tp->pos - 1) - "S" - are skipped bits
 * क्रम the node n.
 *
 * All the bits we have seen so far are signअगरicant to the node n. The rest
 * of the bits are really not needed or indeed known in n->key.
 *
 * The bits from (n->pos) to (n->pos + n->bits - 1) - "C" - are the index पूर्णांकo
 * n's child array, and will of course be dअगरferent क्रम each child.
 *
 * The rest of the bits, from 0 to (n->pos -1) - "u" - are completely unknown
 * at this poपूर्णांक.
 */

अटल स्थिर पूर्णांक halve_threshold = 25;
अटल स्थिर पूर्णांक inflate_threshold = 50;
अटल स्थिर पूर्णांक halve_threshold_root = 15;
अटल स्थिर पूर्णांक inflate_threshold_root = 30;

अटल व्योम __alias_मुक्त_mem(काष्ठा rcu_head *head)
अणु
	काष्ठा fib_alias *fa = container_of(head, काष्ठा fib_alias, rcu);
	kmem_cache_मुक्त(fn_alias_kmem, fa);
पूर्ण

अटल अंतरभूत व्योम alias_मुक्त_mem_rcu(काष्ठा fib_alias *fa)
अणु
	call_rcu(&fa->rcu, __alias_मुक्त_mem);
पूर्ण

#घोषणा TNODE_VMALLOC_MAX \
	ilog2((SIZE_MAX - TNODE_SIZE(0)) / माप(काष्ठा key_vector *))

अटल व्योम __node_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा tnode *n = container_of(head, काष्ठा tnode, rcu);

	अगर (!n->tn_bits)
		kmem_cache_मुक्त(trie_leaf_kmem, n);
	अन्यथा
		kvमुक्त(n);
पूर्ण

#घोषणा node_मुक्त(n) call_rcu(&tn_info(n)->rcu, __node_मुक्त_rcu)

अटल काष्ठा tnode *tnode_alloc(पूर्णांक bits)
अणु
	माप_प्रकार size;

	/* verअगरy bits is within bounds */
	अगर (bits > TNODE_VMALLOC_MAX)
		वापस शून्य;

	/* determine size and verअगरy it is non-zero and didn't overflow */
	size = TNODE_SIZE(1ul << bits);

	अगर (size <= PAGE_SIZE)
		वापस kzalloc(size, GFP_KERNEL);
	अन्यथा
		वापस vzalloc(size);
पूर्ण

अटल अंतरभूत व्योम empty_child_inc(काष्ठा key_vector *n)
अणु
	tn_info(n)->empty_children++;

	अगर (!tn_info(n)->empty_children)
		tn_info(n)->full_children++;
पूर्ण

अटल अंतरभूत व्योम empty_child_dec(काष्ठा key_vector *n)
अणु
	अगर (!tn_info(n)->empty_children)
		tn_info(n)->full_children--;

	tn_info(n)->empty_children--;
पूर्ण

अटल काष्ठा key_vector *leaf_new(t_key key, काष्ठा fib_alias *fa)
अणु
	काष्ठा key_vector *l;
	काष्ठा tnode *kv;

	kv = kmem_cache_alloc(trie_leaf_kmem, GFP_KERNEL);
	अगर (!kv)
		वापस शून्य;

	/* initialize key vector */
	l = kv->kv;
	l->key = key;
	l->pos = 0;
	l->bits = 0;
	l->slen = fa->fa_slen;

	/* link leaf to fib alias */
	INIT_HLIST_HEAD(&l->leaf);
	hlist_add_head(&fa->fa_list, &l->leaf);

	वापस l;
पूर्ण

अटल काष्ठा key_vector *tnode_new(t_key key, पूर्णांक pos, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक shअगरt = pos + bits;
	काष्ठा key_vector *tn;
	काष्ठा tnode *tnode;

	/* verअगरy bits and pos their msb bits clear and values are valid */
	BUG_ON(!bits || (shअगरt > KEYLENGTH));

	tnode = tnode_alloc(bits);
	अगर (!tnode)
		वापस शून्य;

	pr_debug("AT %p s=%zu %zu\n", tnode, TNODE_SIZE(0),
		 माप(काष्ठा key_vector *) << bits);

	अगर (bits == KEYLENGTH)
		tnode->full_children = 1;
	अन्यथा
		tnode->empty_children = 1ul << bits;

	tn = tnode->kv;
	tn->key = (shअगरt < KEYLENGTH) ? (key >> shअगरt) << shअगरt : 0;
	tn->pos = pos;
	tn->bits = bits;
	tn->slen = pos;

	वापस tn;
पूर्ण

/* Check whether a tnode 'n' is "full", i.e. it is an पूर्णांकernal node
 * and no bits are skipped. See discussion in dyntree paper p. 6
 */
अटल अंतरभूत पूर्णांक tnode_full(काष्ठा key_vector *tn, काष्ठा key_vector *n)
अणु
	वापस n && ((n->pos + n->bits) == tn->pos) && IS_TNODE(n);
पूर्ण

/* Add a child at position i overwriting the old value.
 * Update the value of full_children and empty_children.
 */
अटल व्योम put_child(काष्ठा key_vector *tn, अचिन्हित दीर्घ i,
		      काष्ठा key_vector *n)
अणु
	काष्ठा key_vector *chi = get_child(tn, i);
	पूर्णांक isfull, wasfull;

	BUG_ON(i >= child_length(tn));

	/* update emptyChildren, overflow पूर्णांकo fullChildren */
	अगर (!n && chi)
		empty_child_inc(tn);
	अगर (n && !chi)
		empty_child_dec(tn);

	/* update fullChildren */
	wasfull = tnode_full(tn, chi);
	isfull = tnode_full(tn, n);

	अगर (wasfull && !isfull)
		tn_info(tn)->full_children--;
	अन्यथा अगर (!wasfull && isfull)
		tn_info(tn)->full_children++;

	अगर (n && (tn->slen < n->slen))
		tn->slen = n->slen;

	rcu_assign_poपूर्णांकer(tn->tnode[i], n);
पूर्ण

अटल व्योम update_children(काष्ठा key_vector *tn)
अणु
	अचिन्हित दीर्घ i;

	/* update all of the child parent poपूर्णांकers */
	क्रम (i = child_length(tn); i;) अणु
		काष्ठा key_vector *inode = get_child(tn, --i);

		अगर (!inode)
			जारी;

		/* Either update the children of a tnode that
		 * alपढ़ोy beदीर्घs to us or update the child
		 * to poपूर्णांक to ourselves.
		 */
		अगर (node_parent(inode) == tn)
			update_children(inode);
		अन्यथा
			node_set_parent(inode, tn);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम put_child_root(काष्ठा key_vector *tp, t_key key,
				  काष्ठा key_vector *n)
अणु
	अगर (IS_TRIE(tp))
		rcu_assign_poपूर्णांकer(tp->tnode[0], n);
	अन्यथा
		put_child(tp, get_index(key, tp), n);
पूर्ण

अटल अंतरभूत व्योम tnode_मुक्त_init(काष्ठा key_vector *tn)
अणु
	tn_info(tn)->rcu.next = शून्य;
पूर्ण

अटल अंतरभूत व्योम tnode_मुक्त_append(काष्ठा key_vector *tn,
				     काष्ठा key_vector *n)
अणु
	tn_info(n)->rcu.next = tn_info(tn)->rcu.next;
	tn_info(tn)->rcu.next = &tn_info(n)->rcu;
पूर्ण

अटल व्योम tnode_मुक्त(काष्ठा key_vector *tn)
अणु
	काष्ठा callback_head *head = &tn_info(tn)->rcu;

	जबतक (head) अणु
		head = head->next;
		tnode_मुक्त_size += TNODE_SIZE(1ul << tn->bits);
		node_मुक्त(tn);

		tn = container_of(head, काष्ठा tnode, rcu)->kv;
	पूर्ण

	अगर (tnode_मुक्त_size >= sysctl_fib_sync_mem) अणु
		tnode_मुक्त_size = 0;
		synchronize_rcu();
	पूर्ण
पूर्ण

अटल काष्ठा key_vector *replace(काष्ठा trie *t,
				  काष्ठा key_vector *oldtnode,
				  काष्ठा key_vector *tn)
अणु
	काष्ठा key_vector *tp = node_parent(oldtnode);
	अचिन्हित दीर्घ i;

	/* setup the parent poपूर्णांकer out of and back पूर्णांकo this node */
	NODE_INIT_PARENT(tn, tp);
	put_child_root(tp, tn->key, tn);

	/* update all of the child parent poपूर्णांकers */
	update_children(tn);

	/* all poपूर्णांकers should be clean so we are करोne */
	tnode_मुक्त(oldtnode);

	/* resize children now that oldtnode is मुक्तd */
	क्रम (i = child_length(tn); i;) अणु
		काष्ठा key_vector *inode = get_child(tn, --i);

		/* resize child node */
		अगर (tnode_full(tn, inode))
			tn = resize(t, inode);
	पूर्ण

	वापस tp;
पूर्ण

अटल काष्ठा key_vector *inflate(काष्ठा trie *t,
				  काष्ठा key_vector *oldtnode)
अणु
	काष्ठा key_vector *tn;
	अचिन्हित दीर्घ i;
	t_key m;

	pr_debug("In inflate\n");

	tn = tnode_new(oldtnode->key, oldtnode->pos - 1, oldtnode->bits + 1);
	अगर (!tn)
		जाओ notnode;

	/* prepare oldtnode to be मुक्तd */
	tnode_मुक्त_init(oldtnode);

	/* Assemble all of the poपूर्णांकers in our cluster, in this हाल that
	 * represents all of the poपूर्णांकers out of our allocated nodes that
	 * poपूर्णांक to existing tnodes and the links between our allocated
	 * nodes.
	 */
	क्रम (i = child_length(oldtnode), m = 1u << tn->pos; i;) अणु
		काष्ठा key_vector *inode = get_child(oldtnode, --i);
		काष्ठा key_vector *node0, *node1;
		अचिन्हित दीर्घ j, k;

		/* An empty child */
		अगर (!inode)
			जारी;

		/* A leaf or an पूर्णांकernal node with skipped bits */
		अगर (!tnode_full(oldtnode, inode)) अणु
			put_child(tn, get_index(inode->key, tn), inode);
			जारी;
		पूर्ण

		/* drop the node in the old tnode मुक्त list */
		tnode_मुक्त_append(oldtnode, inode);

		/* An पूर्णांकernal node with two children */
		अगर (inode->bits == 1) अणु
			put_child(tn, 2 * i + 1, get_child(inode, 1));
			put_child(tn, 2 * i, get_child(inode, 0));
			जारी;
		पूर्ण

		/* We will replace this node 'inode' with two new
		 * ones, 'node0' and 'node1', each with half of the
		 * original children. The two new nodes will have
		 * a position one bit further करोwn the key and this
		 * means that the "significant" part of their keys
		 * (see the discussion near the top of this file)
		 * will dअगरfer by one bit, which will be "0" in
		 * node0's key and "1" in node1's key. Since we are
		 * moving the key position by one step, the bit that
		 * we are moving away from - the bit at position
		 * (tn->pos) - is the one that will dअगरfer between
		 * node0 and node1. So... we synthesize that bit in the
		 * two new keys.
		 */
		node1 = tnode_new(inode->key | m, inode->pos, inode->bits - 1);
		अगर (!node1)
			जाओ nomem;
		node0 = tnode_new(inode->key, inode->pos, inode->bits - 1);

		tnode_मुक्त_append(tn, node1);
		अगर (!node0)
			जाओ nomem;
		tnode_मुक्त_append(tn, node0);

		/* populate child poपूर्णांकers in new nodes */
		क्रम (k = child_length(inode), j = k / 2; j;) अणु
			put_child(node1, --j, get_child(inode, --k));
			put_child(node0, j, get_child(inode, j));
			put_child(node1, --j, get_child(inode, --k));
			put_child(node0, j, get_child(inode, j));
		पूर्ण

		/* link new nodes to parent */
		NODE_INIT_PARENT(node1, tn);
		NODE_INIT_PARENT(node0, tn);

		/* link parent to nodes */
		put_child(tn, 2 * i + 1, node1);
		put_child(tn, 2 * i, node0);
	पूर्ण

	/* setup the parent poपूर्णांकers पूर्णांकo and out of this node */
	वापस replace(t, oldtnode, tn);
nomem:
	/* all poपूर्णांकers should be clean so we are करोne */
	tnode_मुक्त(tn);
notnode:
	वापस शून्य;
पूर्ण

अटल काष्ठा key_vector *halve(काष्ठा trie *t,
				काष्ठा key_vector *oldtnode)
अणु
	काष्ठा key_vector *tn;
	अचिन्हित दीर्घ i;

	pr_debug("In halve\n");

	tn = tnode_new(oldtnode->key, oldtnode->pos + 1, oldtnode->bits - 1);
	अगर (!tn)
		जाओ notnode;

	/* prepare oldtnode to be मुक्तd */
	tnode_मुक्त_init(oldtnode);

	/* Assemble all of the poपूर्णांकers in our cluster, in this हाल that
	 * represents all of the poपूर्णांकers out of our allocated nodes that
	 * poपूर्णांक to existing tnodes and the links between our allocated
	 * nodes.
	 */
	क्रम (i = child_length(oldtnode); i;) अणु
		काष्ठा key_vector *node1 = get_child(oldtnode, --i);
		काष्ठा key_vector *node0 = get_child(oldtnode, --i);
		काष्ठा key_vector *inode;

		/* At least one of the children is empty */
		अगर (!node1 || !node0) अणु
			put_child(tn, i / 2, node1 ? : node0);
			जारी;
		पूर्ण

		/* Two nonempty children */
		inode = tnode_new(node0->key, oldtnode->pos, 1);
		अगर (!inode)
			जाओ nomem;
		tnode_मुक्त_append(tn, inode);

		/* initialize poपूर्णांकers out of node */
		put_child(inode, 1, node1);
		put_child(inode, 0, node0);
		NODE_INIT_PARENT(inode, tn);

		/* link parent to node */
		put_child(tn, i / 2, inode);
	पूर्ण

	/* setup the parent poपूर्णांकers पूर्णांकo and out of this node */
	वापस replace(t, oldtnode, tn);
nomem:
	/* all poपूर्णांकers should be clean so we are करोne */
	tnode_मुक्त(tn);
notnode:
	वापस शून्य;
पूर्ण

अटल काष्ठा key_vector *collapse(काष्ठा trie *t,
				   काष्ठा key_vector *oldtnode)
अणु
	काष्ठा key_vector *n, *tp;
	अचिन्हित दीर्घ i;

	/* scan the tnode looking क्रम that one child that might still exist */
	क्रम (n = शून्य, i = child_length(oldtnode); !n && i;)
		n = get_child(oldtnode, --i);

	/* compress one level */
	tp = node_parent(oldtnode);
	put_child_root(tp, oldtnode->key, n);
	node_set_parent(n, tp);

	/* drop dead node */
	node_मुक्त(oldtnode);

	वापस tp;
पूर्ण

अटल अचिन्हित अक्षर update_suffix(काष्ठा key_vector *tn)
अणु
	अचिन्हित अक्षर slen = tn->pos;
	अचिन्हित दीर्घ stride, i;
	अचिन्हित अक्षर slen_max;

	/* only vector 0 can have a suffix length greater than or equal to
	 * tn->pos + tn->bits, the second highest node will have a suffix
	 * length at most of tn->pos + tn->bits - 1
	 */
	slen_max = min_t(अचिन्हित अक्षर, tn->pos + tn->bits - 1, tn->slen);

	/* search though the list of children looking क्रम nodes that might
	 * have a suffix greater than the one we currently have.  This is
	 * why we start with a stride of 2 since a stride of 1 would
	 * represent the nodes with suffix length equal to tn->pos
	 */
	क्रम (i = 0, stride = 0x2ul ; i < child_length(tn); i += stride) अणु
		काष्ठा key_vector *n = get_child(tn, i);

		अगर (!n || (n->slen <= slen))
			जारी;

		/* update stride and slen based on new value */
		stride <<= (n->slen - slen);
		slen = n->slen;
		i &= ~(stride - 1);

		/* stop searching अगर we have hit the maximum possible value */
		अगर (slen >= slen_max)
			अवरोध;
	पूर्ण

	tn->slen = slen;

	वापस slen;
पूर्ण

/* From "Implementing a dynamic compressed trie" by Stefan Nilsson of
 * the Helsinki University of Technology and Matti Tikkanen of Nokia
 * Telecommunications, page 6:
 * "A node is द्विगुनd अगर the ratio of non-empty children to all
 * children in the *द्विगुनd* node is at least 'high'."
 *
 * 'high' in this instance is the variable 'inflate_threshold'. It
 * is expressed as a percentage, so we multiply it with
 * child_length() and instead of multiplying by 2 (since the
 * child array will be द्विगुनd by inflate()) and multiplying
 * the left-hand side by 100 (to handle the percentage thing) we
 * multiply the left-hand side by 50.
 *
 * The left-hand side may look a bit weird: child_length(tn)
 * - tn->empty_children is of course the number of non-null children
 * in the current node. tn->full_children is the number of "full"
 * children, that is non-null tnodes with a skip value of 0.
 * All of those will be द्विगुनd in the resulting inflated tnode, so
 * we just count them one extra समय here.
 *
 * A clearer way to ग_लिखो this would be:
 *
 * to_be_द्विगुनd = tn->full_children;
 * not_to_be_द्विगुनd = child_length(tn) - tn->empty_children -
 *     tn->full_children;
 *
 * new_child_length = child_length(tn) * 2;
 *
 * new_fill_factor = 100 * (not_to_be_द्विगुनd + 2*to_be_द्विगुनd) /
 *      new_child_length;
 * अगर (new_fill_factor >= inflate_threshold)
 *
 * ...and so on, tho it would mess up the जबतक () loop.
 *
 * anyway,
 * 100 * (not_to_be_द्विगुनd + 2*to_be_द्विगुनd) / new_child_length >=
 *      inflate_threshold
 *
 * aव्योम a भागision:
 * 100 * (not_to_be_द्विगुनd + 2*to_be_द्विगुनd) >=
 *      inflate_threshold * new_child_length
 *
 * expand not_to_be_द्विगुनd and to_be_द्विगुनd, and लघुen:
 * 100 * (child_length(tn) - tn->empty_children +
 *    tn->full_children) >= inflate_threshold * new_child_length
 *
 * expand new_child_length:
 * 100 * (child_length(tn) - tn->empty_children +
 *    tn->full_children) >=
 *      inflate_threshold * child_length(tn) * 2
 *
 * लघुen again:
 * 50 * (tn->full_children + child_length(tn) -
 *    tn->empty_children) >= inflate_threshold *
 *    child_length(tn)
 *
 */
अटल अंतरभूत bool should_inflate(काष्ठा key_vector *tp, काष्ठा key_vector *tn)
अणु
	अचिन्हित दीर्घ used = child_length(tn);
	अचिन्हित दीर्घ threshold = used;

	/* Keep root node larger */
	threshold *= IS_TRIE(tp) ? inflate_threshold_root : inflate_threshold;
	used -= tn_info(tn)->empty_children;
	used += tn_info(tn)->full_children;

	/* अगर bits == KEYLENGTH then pos = 0, and will fail below */

	वापस (used > 1) && tn->pos && ((50 * used) >= threshold);
पूर्ण

अटल अंतरभूत bool should_halve(काष्ठा key_vector *tp, काष्ठा key_vector *tn)
अणु
	अचिन्हित दीर्घ used = child_length(tn);
	अचिन्हित दीर्घ threshold = used;

	/* Keep root node larger */
	threshold *= IS_TRIE(tp) ? halve_threshold_root : halve_threshold;
	used -= tn_info(tn)->empty_children;

	/* अगर bits == KEYLENGTH then used = 100% on wrap, and will fail below */

	वापस (used > 1) && (tn->bits > 1) && ((100 * used) < threshold);
पूर्ण

अटल अंतरभूत bool should_collapse(काष्ठा key_vector *tn)
अणु
	अचिन्हित दीर्घ used = child_length(tn);

	used -= tn_info(tn)->empty_children;

	/* account क्रम bits == KEYLENGTH हाल */
	अगर ((tn->bits == KEYLENGTH) && tn_info(tn)->full_children)
		used -= KEY_MAX;

	/* One child or none, समय to drop us from the trie */
	वापस used < 2;
पूर्ण

#घोषणा MAX_WORK 10
अटल काष्ठा key_vector *resize(काष्ठा trie *t, काष्ठा key_vector *tn)
अणु
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	काष्ठा trie_use_stats __percpu *stats = t->stats;
#पूर्ण_अगर
	काष्ठा key_vector *tp = node_parent(tn);
	अचिन्हित दीर्घ cindex = get_index(tn->key, tp);
	पूर्णांक max_work = MAX_WORK;

	pr_debug("In tnode_resize %p inflate_threshold=%d threshold=%d\n",
		 tn, inflate_threshold, halve_threshold);

	/* track the tnode via the poपूर्णांकer from the parent instead of
	 * करोing it ourselves.  This way we can let RCU fully करो its
	 * thing without us पूर्णांकerfering
	 */
	BUG_ON(tn != get_child(tp, cindex));

	/* Double as दीर्घ as the resulting node has a number of
	 * nonempty nodes that are above the threshold.
	 */
	जबतक (should_inflate(tp, tn) && max_work) अणु
		tp = inflate(t, tn);
		अगर (!tp) अणु
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->resize_node_skipped);
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		max_work--;
		tn = get_child(tp, cindex);
	पूर्ण

	/* update parent in हाल inflate failed */
	tp = node_parent(tn);

	/* Return अगर at least one inflate is run */
	अगर (max_work != MAX_WORK)
		वापस tp;

	/* Halve as दीर्घ as the number of empty children in this
	 * node is above threshold.
	 */
	जबतक (should_halve(tp, tn) && max_work) अणु
		tp = halve(t, tn);
		अगर (!tp) अणु
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->resize_node_skipped);
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		max_work--;
		tn = get_child(tp, cindex);
	पूर्ण

	/* Only one child reमुख्यs */
	अगर (should_collapse(tn))
		वापस collapse(t, tn);

	/* update parent in हाल halve failed */
	वापस node_parent(tn);
पूर्ण

अटल व्योम node_pull_suffix(काष्ठा key_vector *tn, अचिन्हित अक्षर slen)
अणु
	अचिन्हित अक्षर node_slen = tn->slen;

	जबतक ((node_slen > tn->pos) && (node_slen > slen)) अणु
		slen = update_suffix(tn);
		अगर (node_slen == slen)
			अवरोध;

		tn = node_parent(tn);
		node_slen = tn->slen;
	पूर्ण
पूर्ण

अटल व्योम node_push_suffix(काष्ठा key_vector *tn, अचिन्हित अक्षर slen)
अणु
	जबतक (tn->slen < slen) अणु
		tn->slen = slen;
		tn = node_parent(tn);
	पूर्ण
पूर्ण

/* rcu_पढ़ो_lock needs to be hold by caller from पढ़ोside */
अटल काष्ठा key_vector *fib_find_node(काष्ठा trie *t,
					काष्ठा key_vector **tp, u32 key)
अणु
	काष्ठा key_vector *pn, *n = t->kv;
	अचिन्हित दीर्घ index = 0;

	करो अणु
		pn = n;
		n = get_child_rcu(n, index);

		अगर (!n)
			अवरोध;

		index = get_cindex(key, n);

		/* This bit of code is a bit tricky but it combines multiple
		 * checks पूर्णांकo a single check.  The prefix consists of the
		 * prefix plus zeros क्रम the bits in the cindex. The index
		 * is the dअगरference between the key and this value.  From
		 * this we can actually derive several pieces of data.
		 *   अगर (index >= (1ul << bits))
		 *     we have a mismatch in skip bits and failed
		 *   अन्यथा
		 *     we know the value is cindex
		 *
		 * This check is safe even अगर bits == KEYLENGTH due to the
		 * fact that we can only allocate a node with 32 bits अगर a
		 * दीर्घ is greater than 32 bits.
		 */
		अगर (index >= (1ul << n->bits)) अणु
			n = शून्य;
			अवरोध;
		पूर्ण

		/* keep searching until we find a perfect match leaf or शून्य */
	पूर्ण जबतक (IS_TNODE(n));

	*tp = pn;

	वापस n;
पूर्ण

/* Return the first fib alias matching TOS with
 * priority less than or equal to PRIO.
 * If 'find_first' is set, वापस the first matching
 * fib alias, regardless of TOS and priority.
 */
अटल काष्ठा fib_alias *fib_find_alias(काष्ठा hlist_head *fah, u8 slen,
					u8 tos, u32 prio, u32 tb_id,
					bool find_first)
अणु
	काष्ठा fib_alias *fa;

	अगर (!fah)
		वापस शून्य;

	hlist_क्रम_each_entry(fa, fah, fa_list) अणु
		अगर (fa->fa_slen < slen)
			जारी;
		अगर (fa->fa_slen != slen)
			अवरोध;
		अगर (fa->tb_id > tb_id)
			जारी;
		अगर (fa->tb_id != tb_id)
			अवरोध;
		अगर (find_first)
			वापस fa;
		अगर (fa->fa_tos > tos)
			जारी;
		अगर (fa->fa_info->fib_priority >= prio || fa->fa_tos < tos)
			वापस fa;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा fib_alias *
fib_find_matching_alias(काष्ठा net *net, स्थिर काष्ठा fib_rt_info *fri)
अणु
	u8 slen = KEYLENGTH - fri->dst_len;
	काष्ठा key_vector *l, *tp;
	काष्ठा fib_table *tb;
	काष्ठा fib_alias *fa;
	काष्ठा trie *t;

	tb = fib_get_table(net, fri->tb_id);
	अगर (!tb)
		वापस शून्य;

	t = (काष्ठा trie *)tb->tb_data;
	l = fib_find_node(t, &tp, be32_to_cpu(fri->dst));
	अगर (!l)
		वापस शून्य;

	hlist_क्रम_each_entry_rcu(fa, &l->leaf, fa_list) अणु
		अगर (fa->fa_slen == slen && fa->tb_id == fri->tb_id &&
		    fa->fa_tos == fri->tos && fa->fa_info == fri->fi &&
		    fa->fa_type == fri->type)
			वापस fa;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम fib_alias_hw_flags_set(काष्ठा net *net, स्थिर काष्ठा fib_rt_info *fri)
अणु
	काष्ठा fib_alias *fa_match;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	fa_match = fib_find_matching_alias(net, fri);
	अगर (!fa_match)
		जाओ out;

	अगर (fa_match->offload == fri->offload && fa_match->trap == fri->trap &&
	    fa_match->offload_failed == fri->offload_failed)
		जाओ out;

	fa_match->offload = fri->offload;
	fa_match->trap = fri->trap;

	/* 2 means send notअगरications only अगर offload_failed was changed. */
	अगर (net->ipv4.sysctl_fib_notअगरy_on_flag_change == 2 &&
	    fa_match->offload_failed == fri->offload_failed)
		जाओ out;

	fa_match->offload_failed = fri->offload_failed;

	अगर (!net->ipv4.sysctl_fib_notअगरy_on_flag_change)
		जाओ out;

	skb = nlmsg_new(fib_nlmsg_size(fa_match->fa_info), GFP_ATOMIC);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	err = fib_dump_info(skb, 0, 0, RTM_NEWROUTE, fri, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in fib_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV4_ROUTE, शून्य, GFP_ATOMIC);
	जाओ out;

errout:
	rtnl_set_sk_err(net, RTNLGRP_IPV4_ROUTE, err);
out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(fib_alias_hw_flags_set);

अटल व्योम trie_rebalance(काष्ठा trie *t, काष्ठा key_vector *tn)
अणु
	जबतक (!IS_TRIE(tn))
		tn = resize(t, tn);
पूर्ण

अटल पूर्णांक fib_insert_node(काष्ठा trie *t, काष्ठा key_vector *tp,
			   काष्ठा fib_alias *new, t_key key)
अणु
	काष्ठा key_vector *n, *l;

	l = leaf_new(key, new);
	अगर (!l)
		जाओ noleaf;

	/* retrieve child from parent node */
	n = get_child(tp, get_index(key, tp));

	/* Case 2: n is a LEAF or a TNODE and the key करोesn't match.
	 *
	 *  Add a new tnode here
	 *  first tnode need some special handling
	 *  leaves us in position क्रम handling as हाल 3
	 */
	अगर (n) अणु
		काष्ठा key_vector *tn;

		tn = tnode_new(key, __fls(key ^ n->key), 1);
		अगर (!tn)
			जाओ notnode;

		/* initialize routes out of node */
		NODE_INIT_PARENT(tn, tp);
		put_child(tn, get_index(key, tn) ^ 1, n);

		/* start adding routes पूर्णांकo the node */
		put_child_root(tp, key, tn);
		node_set_parent(n, tn);

		/* parent now has a शून्य spot where the leaf can go */
		tp = tn;
	पूर्ण

	/* Case 3: n is शून्य, and will just insert a new leaf */
	node_push_suffix(tp, new->fa_slen);
	NODE_INIT_PARENT(l, tp);
	put_child_root(tp, key, l);
	trie_rebalance(t, tp);

	वापस 0;
notnode:
	node_मुक्त(l);
noleaf:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक fib_insert_alias(काष्ठा trie *t, काष्ठा key_vector *tp,
			    काष्ठा key_vector *l, काष्ठा fib_alias *new,
			    काष्ठा fib_alias *fa, t_key key)
अणु
	अगर (!l)
		वापस fib_insert_node(t, tp, new, key);

	अगर (fa) अणु
		hlist_add_beक्रमe_rcu(&new->fa_list, &fa->fa_list);
	पूर्ण अन्यथा अणु
		काष्ठा fib_alias *last;

		hlist_क्रम_each_entry(last, &l->leaf, fa_list) अणु
			अगर (new->fa_slen < last->fa_slen)
				अवरोध;
			अगर ((new->fa_slen == last->fa_slen) &&
			    (new->tb_id > last->tb_id))
				अवरोध;
			fa = last;
		पूर्ण

		अगर (fa)
			hlist_add_behind_rcu(&new->fa_list, &fa->fa_list);
		अन्यथा
			hlist_add_head_rcu(&new->fa_list, &l->leaf);
	पूर्ण

	/* अगर we added to the tail node then we need to update slen */
	अगर (l->slen < new->fa_slen) अणु
		l->slen = new->fa_slen;
		node_push_suffix(tp, new->fa_slen);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool fib_valid_key_len(u32 key, u8 plen, काष्ठा netlink_ext_ack *extack)
अणु
	अगर (plen > KEYLENGTH) अणु
		NL_SET_ERR_MSG(extack, "Invalid prefix length");
		वापस false;
	पूर्ण

	अगर ((plen < KEYLENGTH) && (key << plen)) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid prefix for given prefix length");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम fib_हटाओ_alias(काष्ठा trie *t, काष्ठा key_vector *tp,
			     काष्ठा key_vector *l, काष्ठा fib_alias *old);

/* Caller must hold RTNL. */
पूर्णांक fib_table_insert(काष्ठा net *net, काष्ठा fib_table *tb,
		     काष्ठा fib_config *cfg, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा fib_alias *fa, *new_fa;
	काष्ठा key_vector *l, *tp;
	u16 nlflags = NLM_F_EXCL;
	काष्ठा fib_info *fi;
	u8 plen = cfg->fc_dst_len;
	u8 slen = KEYLENGTH - plen;
	u8 tos = cfg->fc_tos;
	u32 key;
	पूर्णांक err;

	key = ntohl(cfg->fc_dst);

	अगर (!fib_valid_key_len(key, plen, extack))
		वापस -EINVAL;

	pr_debug("Insert table=%u %08x/%d\n", tb->tb_id, key, plen);

	fi = fib_create_info(cfg, extack);
	अगर (IS_ERR(fi)) अणु
		err = PTR_ERR(fi);
		जाओ err;
	पूर्ण

	l = fib_find_node(t, &tp, key);
	fa = l ? fib_find_alias(&l->leaf, slen, tos, fi->fib_priority,
				tb->tb_id, false) : शून्य;

	/* Now fa, अगर non-शून्य, poपूर्णांकs to the first fib alias
	 * with the same keys [prefix,tos,priority], अगर such key alपढ़ोy
	 * exists or to the node beक्रमe which we will insert new one.
	 *
	 * If fa is शून्य, we will need to allocate a new one and
	 * insert to the tail of the section matching the suffix length
	 * of the new alias.
	 */

	अगर (fa && fa->fa_tos == tos &&
	    fa->fa_info->fib_priority == fi->fib_priority) अणु
		काष्ठा fib_alias *fa_first, *fa_match;

		err = -EEXIST;
		अगर (cfg->fc_nlflags & NLM_F_EXCL)
			जाओ out;

		nlflags &= ~NLM_F_EXCL;

		/* We have 2 goals:
		 * 1. Find exact match क्रम type, scope, fib_info to aव्योम
		 * duplicate routes
		 * 2. Find next 'fa' (or head), NLM_F_APPEND inserts beक्रमe it
		 */
		fa_match = शून्य;
		fa_first = fa;
		hlist_क्रम_each_entry_from(fa, fa_list) अणु
			अगर ((fa->fa_slen != slen) ||
			    (fa->tb_id != tb->tb_id) ||
			    (fa->fa_tos != tos))
				अवरोध;
			अगर (fa->fa_info->fib_priority != fi->fib_priority)
				अवरोध;
			अगर (fa->fa_type == cfg->fc_type &&
			    fa->fa_info == fi) अणु
				fa_match = fa;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (cfg->fc_nlflags & NLM_F_REPLACE) अणु
			काष्ठा fib_info *fi_drop;
			u8 state;

			nlflags |= NLM_F_REPLACE;
			fa = fa_first;
			अगर (fa_match) अणु
				अगर (fa == fa_match)
					err = 0;
				जाओ out;
			पूर्ण
			err = -ENOBUFS;
			new_fa = kmem_cache_alloc(fn_alias_kmem, GFP_KERNEL);
			अगर (!new_fa)
				जाओ out;

			fi_drop = fa->fa_info;
			new_fa->fa_tos = fa->fa_tos;
			new_fa->fa_info = fi;
			new_fa->fa_type = cfg->fc_type;
			state = fa->fa_state;
			new_fa->fa_state = state & ~FA_S_ACCESSED;
			new_fa->fa_slen = fa->fa_slen;
			new_fa->tb_id = tb->tb_id;
			new_fa->fa_शेष = -1;
			new_fa->offload = 0;
			new_fa->trap = 0;
			new_fa->offload_failed = 0;

			hlist_replace_rcu(&fa->fa_list, &new_fa->fa_list);

			अगर (fib_find_alias(&l->leaf, fa->fa_slen, 0, 0,
					   tb->tb_id, true) == new_fa) अणु
				क्रमागत fib_event_type fib_event;

				fib_event = FIB_EVENT_ENTRY_REPLACE;
				err = call_fib_entry_notअगरiers(net, fib_event,
							       key, plen,
							       new_fa, extack);
				अगर (err) अणु
					hlist_replace_rcu(&new_fa->fa_list,
							  &fa->fa_list);
					जाओ out_मुक्त_new_fa;
				पूर्ण
			पूर्ण

			rपंचांगsg_fib(RTM_NEWROUTE, htonl(key), new_fa, plen,
				  tb->tb_id, &cfg->fc_nlinfo, nlflags);

			alias_मुक्त_mem_rcu(fa);

			fib_release_info(fi_drop);
			अगर (state & FA_S_ACCESSED)
				rt_cache_flush(cfg->fc_nlinfo.nl_net);

			जाओ succeeded;
		पूर्ण
		/* Error अगर we find a perfect match which
		 * uses the same scope, type, and nexthop
		 * inक्रमmation.
		 */
		अगर (fa_match)
			जाओ out;

		अगर (cfg->fc_nlflags & NLM_F_APPEND)
			nlflags |= NLM_F_APPEND;
		अन्यथा
			fa = fa_first;
	पूर्ण
	err = -ENOENT;
	अगर (!(cfg->fc_nlflags & NLM_F_CREATE))
		जाओ out;

	nlflags |= NLM_F_CREATE;
	err = -ENOBUFS;
	new_fa = kmem_cache_alloc(fn_alias_kmem, GFP_KERNEL);
	अगर (!new_fa)
		जाओ out;

	new_fa->fa_info = fi;
	new_fa->fa_tos = tos;
	new_fa->fa_type = cfg->fc_type;
	new_fa->fa_state = 0;
	new_fa->fa_slen = slen;
	new_fa->tb_id = tb->tb_id;
	new_fa->fa_शेष = -1;
	new_fa->offload = 0;
	new_fa->trap = 0;
	new_fa->offload_failed = 0;

	/* Insert new entry to the list. */
	err = fib_insert_alias(t, tp, l, new_fa, fa, key);
	अगर (err)
		जाओ out_मुक्त_new_fa;

	/* The alias was alपढ़ोy inserted, so the node must exist. */
	l = l ? l : fib_find_node(t, &tp, key);
	अगर (WARN_ON_ONCE(!l))
		जाओ out_मुक्त_new_fa;

	अगर (fib_find_alias(&l->leaf, new_fa->fa_slen, 0, 0, tb->tb_id, true) ==
	    new_fa) अणु
		क्रमागत fib_event_type fib_event;

		fib_event = FIB_EVENT_ENTRY_REPLACE;
		err = call_fib_entry_notअगरiers(net, fib_event, key, plen,
					       new_fa, extack);
		अगर (err)
			जाओ out_हटाओ_new_fa;
	पूर्ण

	अगर (!plen)
		tb->tb_num_शेष++;

	rt_cache_flush(cfg->fc_nlinfo.nl_net);
	rपंचांगsg_fib(RTM_NEWROUTE, htonl(key), new_fa, plen, new_fa->tb_id,
		  &cfg->fc_nlinfo, nlflags);
succeeded:
	वापस 0;

out_हटाओ_new_fa:
	fib_हटाओ_alias(t, tp, l, new_fa);
out_मुक्त_new_fa:
	kmem_cache_मुक्त(fn_alias_kmem, new_fa);
out:
	fib_release_info(fi);
err:
	वापस err;
पूर्ण

अटल अंतरभूत t_key prefix_mismatch(t_key key, काष्ठा key_vector *n)
अणु
	t_key prefix = n->key;

	वापस (key ^ prefix) & (prefix | -prefix);
पूर्ण

bool fib_lookup_good_nhc(स्थिर काष्ठा fib_nh_common *nhc, पूर्णांक fib_flags,
			 स्थिर काष्ठा flowi4 *flp)
अणु
	अगर (nhc->nhc_flags & RTNH_F_DEAD)
		वापस false;

	अगर (ip_ignore_linkकरोwn(nhc->nhc_dev) &&
	    nhc->nhc_flags & RTNH_F_LINKDOWN &&
	    !(fib_flags & FIB_LOOKUP_IGNORE_LINKSTATE))
		वापस false;

	अगर (!(flp->flowi4_flags & FLOWI_FLAG_SKIP_NH_OIF)) अणु
		अगर (flp->flowi4_oअगर &&
		    flp->flowi4_oअगर != nhc->nhc_oअगर)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* should be called with rcu_पढ़ो_lock */
पूर्णांक fib_table_lookup(काष्ठा fib_table *tb, स्थिर काष्ठा flowi4 *flp,
		     काष्ठा fib_result *res, पूर्णांक fib_flags)
अणु
	काष्ठा trie *t = (काष्ठा trie *) tb->tb_data;
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	काष्ठा trie_use_stats __percpu *stats = t->stats;
#पूर्ण_अगर
	स्थिर t_key key = ntohl(flp->daddr);
	काष्ठा key_vector *n, *pn;
	काष्ठा fib_alias *fa;
	अचिन्हित दीर्घ index;
	t_key cindex;

	pn = t->kv;
	cindex = 0;

	n = get_child_rcu(pn, cindex);
	अगर (!n) अणु
		trace_fib_table_lookup(tb->tb_id, flp, शून्य, -EAGAIN);
		वापस -EAGAIN;
	पूर्ण

#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	this_cpu_inc(stats->माला_लो);
#पूर्ण_अगर

	/* Step 1: Travel to the दीर्घest prefix match in the trie */
	क्रम (;;) अणु
		index = get_cindex(key, n);

		/* This bit of code is a bit tricky but it combines multiple
		 * checks पूर्णांकo a single check.  The prefix consists of the
		 * prefix plus zeros क्रम the "bits" in the prefix. The index
		 * is the dअगरference between the key and this value.  From
		 * this we can actually derive several pieces of data.
		 *   अगर (index >= (1ul << bits))
		 *     we have a mismatch in skip bits and failed
		 *   अन्यथा
		 *     we know the value is cindex
		 *
		 * This check is safe even अगर bits == KEYLENGTH due to the
		 * fact that we can only allocate a node with 32 bits अगर a
		 * दीर्घ is greater than 32 bits.
		 */
		अगर (index >= (1ul << n->bits))
			अवरोध;

		/* we have found a leaf. Prefixes have alपढ़ोy been compared */
		अगर (IS_LEAF(n))
			जाओ found;

		/* only record pn and cindex अगर we are going to be chopping
		 * bits later.  Otherwise we are just wasting cycles.
		 */
		अगर (n->slen > n->pos) अणु
			pn = n;
			cindex = index;
		पूर्ण

		n = get_child_rcu(n, index);
		अगर (unlikely(!n))
			जाओ backtrace;
	पूर्ण

	/* Step 2: Sort out leaves and begin backtracing क्रम दीर्घest prefix */
	क्रम (;;) अणु
		/* record the poपूर्णांकer where our next node poपूर्णांकer is stored */
		काष्ठा key_vector __rcu **cptr = n->tnode;

		/* This test verअगरies that none of the bits that dअगरfer
		 * between the key and the prefix exist in the region of
		 * the lsb and higher in the prefix.
		 */
		अगर (unlikely(prefix_mismatch(key, n)) || (n->slen == n->pos))
			जाओ backtrace;

		/* निकास out and process leaf */
		अगर (unlikely(IS_LEAF(n)))
			अवरोध;

		/* Don't bother recording parent info.  Since we are in
		 * prefix match mode we will have to come back to wherever
		 * we started this traversal anyway
		 */

		जबतक ((n = rcu_dereference(*cptr)) == शून्य) अणु
backtrace:
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			अगर (!n)
				this_cpu_inc(stats->null_node_hit);
#पूर्ण_अगर
			/* If we are at cindex 0 there are no more bits क्रम
			 * us to strip at this level so we must ascend back
			 * up one level to see अगर there are any more bits to
			 * be stripped there.
			 */
			जबतक (!cindex) अणु
				t_key pkey = pn->key;

				/* If we करोn't have a parent then there is
				 * nothing क्रम us to करो as we करो not have any
				 * further nodes to parse.
				 */
				अगर (IS_TRIE(pn)) अणु
					trace_fib_table_lookup(tb->tb_id, flp,
							       शून्य, -EAGAIN);
					वापस -EAGAIN;
				पूर्ण
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
				this_cpu_inc(stats->backtrack);
#पूर्ण_अगर
				/* Get Child's index */
				pn = node_parent_rcu(pn);
				cindex = get_index(pkey, pn);
			पूर्ण

			/* strip the least signअगरicant bit from the cindex */
			cindex &= cindex - 1;

			/* grab poपूर्णांकer क्रम next child node */
			cptr = &pn->tnode[cindex];
		पूर्ण
	पूर्ण

found:
	/* this line carries क्रमward the xor from earlier in the function */
	index = key ^ n->key;

	/* Step 3: Process the leaf, अगर that fails fall back to backtracing */
	hlist_क्रम_each_entry_rcu(fa, &n->leaf, fa_list) अणु
		काष्ठा fib_info *fi = fa->fa_info;
		काष्ठा fib_nh_common *nhc;
		पूर्णांक nhsel, err;

		अगर ((BITS_PER_LONG > KEYLENGTH) || (fa->fa_slen < KEYLENGTH)) अणु
			अगर (index >= (1ul << fa->fa_slen))
				जारी;
		पूर्ण
		अगर (fa->fa_tos && fa->fa_tos != flp->flowi4_tos)
			जारी;
		अगर (fi->fib_dead)
			जारी;
		अगर (fa->fa_info->fib_scope < flp->flowi4_scope)
			जारी;
		fib_alias_accessed(fa);
		err = fib_props[fa->fa_type].error;
		अगर (unlikely(err < 0)) अणु
out_reject:
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->semantic_match_passed);
#पूर्ण_अगर
			trace_fib_table_lookup(tb->tb_id, flp, शून्य, err);
			वापस err;
		पूर्ण
		अगर (fi->fib_flags & RTNH_F_DEAD)
			जारी;

		अगर (unlikely(fi->nh)) अणु
			अगर (nexthop_is_blackhole(fi->nh)) अणु
				err = fib_props[RTN_BLACKHOLE].error;
				जाओ out_reject;
			पूर्ण

			nhc = nexthop_get_nhc_lookup(fi->nh, fib_flags, flp,
						     &nhsel);
			अगर (nhc)
				जाओ set_result;
			जाओ miss;
		पूर्ण

		क्रम (nhsel = 0; nhsel < fib_info_num_path(fi); nhsel++) अणु
			nhc = fib_info_nhc(fi, nhsel);

			अगर (!fib_lookup_good_nhc(nhc, fib_flags, flp))
				जारी;
set_result:
			अगर (!(fib_flags & FIB_LOOKUP_NOREF))
				refcount_inc(&fi->fib_clntref);

			res->prefix = htonl(n->key);
			res->prefixlen = KEYLENGTH - fa->fa_slen;
			res->nh_sel = nhsel;
			res->nhc = nhc;
			res->type = fa->fa_type;
			res->scope = fi->fib_scope;
			res->fi = fi;
			res->table = tb;
			res->fa_head = &n->leaf;
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			this_cpu_inc(stats->semantic_match_passed);
#पूर्ण_अगर
			trace_fib_table_lookup(tb->tb_id, flp, nhc, err);

			वापस err;
		पूर्ण
	पूर्ण
miss:
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	this_cpu_inc(stats->semantic_match_miss);
#पूर्ण_अगर
	जाओ backtrace;
पूर्ण
EXPORT_SYMBOL_GPL(fib_table_lookup);

अटल व्योम fib_हटाओ_alias(काष्ठा trie *t, काष्ठा key_vector *tp,
			     काष्ठा key_vector *l, काष्ठा fib_alias *old)
अणु
	/* record the location of the previous list_info entry */
	काष्ठा hlist_node **pprev = old->fa_list.pprev;
	काष्ठा fib_alias *fa = hlist_entry(pprev, typeof(*fa), fa_list.next);

	/* हटाओ the fib_alias from the list */
	hlist_del_rcu(&old->fa_list);

	/* अगर we emptied the list this leaf will be मुक्तd and we can sort
	 * out parent suffix lengths as a part of trie_rebalance
	 */
	अगर (hlist_empty(&l->leaf)) अणु
		अगर (tp->slen == l->slen)
			node_pull_suffix(tp, tp->pos);
		put_child_root(tp, l->key, शून्य);
		node_मुक्त(l);
		trie_rebalance(t, tp);
		वापस;
	पूर्ण

	/* only access fa अगर it is poपूर्णांकing at the last valid hlist_node */
	अगर (*pprev)
		वापस;

	/* update the trie with the latest suffix length */
	l->slen = fa->fa_slen;
	node_pull_suffix(tp, fa->fa_slen);
पूर्ण

अटल व्योम fib_notअगरy_alias_delete(काष्ठा net *net, u32 key,
				    काष्ठा hlist_head *fah,
				    काष्ठा fib_alias *fa_to_delete,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_alias *fa_next, *fa_to_notअगरy;
	u32 tb_id = fa_to_delete->tb_id;
	u8 slen = fa_to_delete->fa_slen;
	क्रमागत fib_event_type fib_event;

	/* Do not notअगरy अगर we करो not care about the route. */
	अगर (fib_find_alias(fah, slen, 0, 0, tb_id, true) != fa_to_delete)
		वापस;

	/* Determine अगर the route should be replaced by the next route in the
	 * list.
	 */
	fa_next = hlist_entry_safe(fa_to_delete->fa_list.next,
				   काष्ठा fib_alias, fa_list);
	अगर (fa_next && fa_next->fa_slen == slen && fa_next->tb_id == tb_id) अणु
		fib_event = FIB_EVENT_ENTRY_REPLACE;
		fa_to_notअगरy = fa_next;
	पूर्ण अन्यथा अणु
		fib_event = FIB_EVENT_ENTRY_DEL;
		fa_to_notअगरy = fa_to_delete;
	पूर्ण
	call_fib_entry_notअगरiers(net, fib_event, key, KEYLENGTH - slen,
				 fa_to_notअगरy, extack);
पूर्ण

/* Caller must hold RTNL. */
पूर्णांक fib_table_delete(काष्ठा net *net, काष्ठा fib_table *tb,
		     काष्ठा fib_config *cfg, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा trie *t = (काष्ठा trie *) tb->tb_data;
	काष्ठा fib_alias *fa, *fa_to_delete;
	काष्ठा key_vector *l, *tp;
	u8 plen = cfg->fc_dst_len;
	u8 slen = KEYLENGTH - plen;
	u8 tos = cfg->fc_tos;
	u32 key;

	key = ntohl(cfg->fc_dst);

	अगर (!fib_valid_key_len(key, plen, extack))
		वापस -EINVAL;

	l = fib_find_node(t, &tp, key);
	अगर (!l)
		वापस -ESRCH;

	fa = fib_find_alias(&l->leaf, slen, tos, 0, tb->tb_id, false);
	अगर (!fa)
		वापस -ESRCH;

	pr_debug("Deleting %08x/%d tos=%d t=%p\n", key, plen, tos, t);

	fa_to_delete = शून्य;
	hlist_क्रम_each_entry_from(fa, fa_list) अणु
		काष्ठा fib_info *fi = fa->fa_info;

		अगर ((fa->fa_slen != slen) ||
		    (fa->tb_id != tb->tb_id) ||
		    (fa->fa_tos != tos))
			अवरोध;

		अगर ((!cfg->fc_type || fa->fa_type == cfg->fc_type) &&
		    (cfg->fc_scope == RT_SCOPE_NOWHERE ||
		     fa->fa_info->fib_scope == cfg->fc_scope) &&
		    (!cfg->fc_prefsrc ||
		     fi->fib_prefsrc == cfg->fc_prefsrc) &&
		    (!cfg->fc_protocol ||
		     fi->fib_protocol == cfg->fc_protocol) &&
		    fib_nh_match(net, cfg, fi, extack) == 0 &&
		    fib_metrics_match(cfg, fi)) अणु
			fa_to_delete = fa;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!fa_to_delete)
		वापस -ESRCH;

	fib_notअगरy_alias_delete(net, key, &l->leaf, fa_to_delete, extack);
	rपंचांगsg_fib(RTM_DELROUTE, htonl(key), fa_to_delete, plen, tb->tb_id,
		  &cfg->fc_nlinfo, 0);

	अगर (!plen)
		tb->tb_num_शेष--;

	fib_हटाओ_alias(t, tp, l, fa_to_delete);

	अगर (fa_to_delete->fa_state & FA_S_ACCESSED)
		rt_cache_flush(cfg->fc_nlinfo.nl_net);

	fib_release_info(fa_to_delete->fa_info);
	alias_मुक्त_mem_rcu(fa_to_delete);
	वापस 0;
पूर्ण

/* Scan क्रम the next leaf starting at the provided key value */
अटल काष्ठा key_vector *leaf_walk_rcu(काष्ठा key_vector **tn, t_key key)
अणु
	काष्ठा key_vector *pn, *n = *tn;
	अचिन्हित दीर्घ cindex;

	/* this loop is meant to try and find the key in the trie */
	करो अणु
		/* record parent and next child index */
		pn = n;
		cindex = (key > pn->key) ? get_index(key, pn) : 0;

		अगर (cindex >> pn->bits)
			अवरोध;

		/* descend पूर्णांकo the next child */
		n = get_child_rcu(pn, cindex++);
		अगर (!n)
			अवरोध;

		/* guarantee क्रमward progress on the keys */
		अगर (IS_LEAF(n) && (n->key >= key))
			जाओ found;
	पूर्ण जबतक (IS_TNODE(n));

	/* this loop will search क्रम the next leaf with a greater key */
	जबतक (!IS_TRIE(pn)) अणु
		/* अगर we exhausted the parent node we will need to climb */
		अगर (cindex >= (1ul << pn->bits)) अणु
			t_key pkey = pn->key;

			pn = node_parent_rcu(pn);
			cindex = get_index(pkey, pn) + 1;
			जारी;
		पूर्ण

		/* grab the next available node */
		n = get_child_rcu(pn, cindex++);
		अगर (!n)
			जारी;

		/* no need to compare keys since we bumped the index */
		अगर (IS_LEAF(n))
			जाओ found;

		/* Rescan start scanning in new node */
		pn = n;
		cindex = 0;
	पूर्ण

	*tn = pn;
	वापस शून्य; /* Root of trie */
found:
	/* अगर we are at the limit क्रम keys just वापस शून्य क्रम the tnode */
	*tn = pn;
	वापस n;
पूर्ण

अटल व्योम fib_trie_मुक्त(काष्ठा fib_table *tb)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *pn = t->kv;
	अचिन्हित दीर्घ cindex = 1;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा fib_alias *fa;

	/* walk trie in reverse order and मुक्त everything */
	क्रम (;;) अणु
		काष्ठा key_vector *n;

		अगर (!(cindex--)) अणु
			t_key pkey = pn->key;

			अगर (IS_TRIE(pn))
				अवरोध;

			n = pn;
			pn = node_parent(pn);

			/* drop emptied tnode */
			put_child_root(pn, n->key, शून्य);
			node_मुक्त(n);

			cindex = get_index(pkey, pn);

			जारी;
		पूर्ण

		/* grab the next available node */
		n = get_child(pn, cindex);
		अगर (!n)
			जारी;

		अगर (IS_TNODE(n)) अणु
			/* record pn and cindex क्रम leaf walking */
			pn = n;
			cindex = 1ul << n->bits;

			जारी;
		पूर्ण

		hlist_क्रम_each_entry_safe(fa, पंचांगp, &n->leaf, fa_list) अणु
			hlist_del_rcu(&fa->fa_list);
			alias_मुक्त_mem_rcu(fa);
		पूर्ण

		put_child_root(pn, n->key, शून्य);
		node_मुक्त(n);
	पूर्ण

#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	मुक्त_percpu(t->stats);
#पूर्ण_अगर
	kमुक्त(tb);
पूर्ण

काष्ठा fib_table *fib_trie_unmerge(काष्ठा fib_table *oldtb)
अणु
	काष्ठा trie *ot = (काष्ठा trie *)oldtb->tb_data;
	काष्ठा key_vector *l, *tp = ot->kv;
	काष्ठा fib_table *local_tb;
	काष्ठा fib_alias *fa;
	काष्ठा trie *lt;
	t_key key = 0;

	अगर (oldtb->tb_data == oldtb->__data)
		वापस oldtb;

	local_tb = fib_trie_table(RT_TABLE_LOCAL, शून्य);
	अगर (!local_tb)
		वापस शून्य;

	lt = (काष्ठा trie *)local_tb->tb_data;

	जबतक ((l = leaf_walk_rcu(&tp, key)) != शून्य) अणु
		काष्ठा key_vector *local_l = शून्य, *local_tp;

		hlist_क्रम_each_entry(fa, &l->leaf, fa_list) अणु
			काष्ठा fib_alias *new_fa;

			अगर (local_tb->tb_id != fa->tb_id)
				जारी;

			/* clone fa क्रम new local table */
			new_fa = kmem_cache_alloc(fn_alias_kmem, GFP_KERNEL);
			अगर (!new_fa)
				जाओ out;

			स_नकल(new_fa, fa, माप(*fa));

			/* insert clone पूर्णांकo table */
			अगर (!local_l)
				local_l = fib_find_node(lt, &local_tp, l->key);

			अगर (fib_insert_alias(lt, local_tp, local_l, new_fa,
					     शून्य, l->key)) अणु
				kmem_cache_मुक्त(fn_alias_kmem, new_fa);
				जाओ out;
			पूर्ण
		पूर्ण

		/* stop loop अगर key wrapped back to 0 */
		key = l->key + 1;
		अगर (key < l->key)
			अवरोध;
	पूर्ण

	वापस local_tb;
out:
	fib_trie_मुक्त(local_tb);

	वापस शून्य;
पूर्ण

/* Caller must hold RTNL */
व्योम fib_table_flush_बाह्यal(काष्ठा fib_table *tb)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *pn = t->kv;
	अचिन्हित दीर्घ cindex = 1;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा fib_alias *fa;

	/* walk trie in reverse order */
	क्रम (;;) अणु
		अचिन्हित अक्षर slen = 0;
		काष्ठा key_vector *n;

		अगर (!(cindex--)) अणु
			t_key pkey = pn->key;

			/* cannot resize the trie vector */
			अगर (IS_TRIE(pn))
				अवरोध;

			/* update the suffix to address pulled leaves */
			अगर (pn->slen > pn->pos)
				update_suffix(pn);

			/* resize completed node */
			pn = resize(t, pn);
			cindex = get_index(pkey, pn);

			जारी;
		पूर्ण

		/* grab the next available node */
		n = get_child(pn, cindex);
		अगर (!n)
			जारी;

		अगर (IS_TNODE(n)) अणु
			/* record pn and cindex क्रम leaf walking */
			pn = n;
			cindex = 1ul << n->bits;

			जारी;
		पूर्ण

		hlist_क्रम_each_entry_safe(fa, पंचांगp, &n->leaf, fa_list) अणु
			/* अगर alias was cloned to local then we just
			 * need to हटाओ the local copy from मुख्य
			 */
			अगर (tb->tb_id != fa->tb_id) अणु
				hlist_del_rcu(&fa->fa_list);
				alias_मुक्त_mem_rcu(fa);
				जारी;
			पूर्ण

			/* record local slen */
			slen = fa->fa_slen;
		पूर्ण

		/* update leaf slen */
		n->slen = slen;

		अगर (hlist_empty(&n->leaf)) अणु
			put_child_root(pn, n->key, शून्य);
			node_मुक्त(n);
		पूर्ण
	पूर्ण
पूर्ण

/* Caller must hold RTNL. */
पूर्णांक fib_table_flush(काष्ठा net *net, काष्ठा fib_table *tb, bool flush_all)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *pn = t->kv;
	अचिन्हित दीर्घ cindex = 1;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा fib_alias *fa;
	पूर्णांक found = 0;

	/* walk trie in reverse order */
	क्रम (;;) अणु
		अचिन्हित अक्षर slen = 0;
		काष्ठा key_vector *n;

		अगर (!(cindex--)) अणु
			t_key pkey = pn->key;

			/* cannot resize the trie vector */
			अगर (IS_TRIE(pn))
				अवरोध;

			/* update the suffix to address pulled leaves */
			अगर (pn->slen > pn->pos)
				update_suffix(pn);

			/* resize completed node */
			pn = resize(t, pn);
			cindex = get_index(pkey, pn);

			जारी;
		पूर्ण

		/* grab the next available node */
		n = get_child(pn, cindex);
		अगर (!n)
			जारी;

		अगर (IS_TNODE(n)) अणु
			/* record pn and cindex क्रम leaf walking */
			pn = n;
			cindex = 1ul << n->bits;

			जारी;
		पूर्ण

		hlist_क्रम_each_entry_safe(fa, पंचांगp, &n->leaf, fa_list) अणु
			काष्ठा fib_info *fi = fa->fa_info;

			अगर (!fi || tb->tb_id != fa->tb_id ||
			    (!(fi->fib_flags & RTNH_F_DEAD) &&
			     !fib_props[fa->fa_type].error)) अणु
				slen = fa->fa_slen;
				जारी;
			पूर्ण

			/* Do not flush error routes अगर network namespace is
			 * not being dismantled
			 */
			अगर (!flush_all && fib_props[fa->fa_type].error) अणु
				slen = fa->fa_slen;
				जारी;
			पूर्ण

			fib_notअगरy_alias_delete(net, n->key, &n->leaf, fa,
						शून्य);
			hlist_del_rcu(&fa->fa_list);
			fib_release_info(fa->fa_info);
			alias_मुक्त_mem_rcu(fa);
			found++;
		पूर्ण

		/* update leaf slen */
		n->slen = slen;

		अगर (hlist_empty(&n->leaf)) अणु
			put_child_root(pn, n->key, शून्य);
			node_मुक्त(n);
		पूर्ण
	पूर्ण

	pr_debug("trie_flush found=%d\n", found);
	वापस found;
पूर्ण

/* derived from fib_trie_मुक्त */
अटल व्योम __fib_info_notअगरy_update(काष्ठा net *net, काष्ठा fib_table *tb,
				     काष्ठा nl_info *info)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *pn = t->kv;
	अचिन्हित दीर्घ cindex = 1;
	काष्ठा fib_alias *fa;

	क्रम (;;) अणु
		काष्ठा key_vector *n;

		अगर (!(cindex--)) अणु
			t_key pkey = pn->key;

			अगर (IS_TRIE(pn))
				अवरोध;

			pn = node_parent(pn);
			cindex = get_index(pkey, pn);
			जारी;
		पूर्ण

		/* grab the next available node */
		n = get_child(pn, cindex);
		अगर (!n)
			जारी;

		अगर (IS_TNODE(n)) अणु
			/* record pn and cindex क्रम leaf walking */
			pn = n;
			cindex = 1ul << n->bits;

			जारी;
		पूर्ण

		hlist_क्रम_each_entry(fa, &n->leaf, fa_list) अणु
			काष्ठा fib_info *fi = fa->fa_info;

			अगर (!fi || !fi->nh_updated || fa->tb_id != tb->tb_id)
				जारी;

			rपंचांगsg_fib(RTM_NEWROUTE, htonl(n->key), fa,
				  KEYLENGTH - fa->fa_slen, tb->tb_id,
				  info, NLM_F_REPLACE);
		पूर्ण
	पूर्ण
पूर्ण

व्योम fib_info_notअगरy_update(काष्ठा net *net, काष्ठा nl_info *info)
अणु
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < FIB_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist,
					 lockdep_rtnl_is_held())
			__fib_info_notअगरy_update(net, tb, info);
	पूर्ण
पूर्ण

अटल पूर्णांक fib_leaf_notअगरy(काष्ठा key_vector *l, काष्ठा fib_table *tb,
			   काष्ठा notअगरier_block *nb,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_alias *fa;
	पूर्णांक last_slen = -1;
	पूर्णांक err;

	hlist_क्रम_each_entry_rcu(fa, &l->leaf, fa_list) अणु
		काष्ठा fib_info *fi = fa->fa_info;

		अगर (!fi)
			जारी;

		/* local and मुख्य table can share the same trie,
		 * so करोn't notअगरy twice क्रम the same entry.
		 */
		अगर (tb->tb_id != fa->tb_id)
			जारी;

		अगर (fa->fa_slen == last_slen)
			जारी;

		last_slen = fa->fa_slen;
		err = call_fib_entry_notअगरier(nb, FIB_EVENT_ENTRY_REPLACE,
					      l->key, KEYLENGTH - fa->fa_slen,
					      fa, extack);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fib_table_notअगरy(काष्ठा fib_table *tb, काष्ठा notअगरier_block *nb,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *l, *tp = t->kv;
	t_key key = 0;
	पूर्णांक err;

	जबतक ((l = leaf_walk_rcu(&tp, key)) != शून्य) अणु
		err = fib_leaf_notअगरy(l, tb, nb, extack);
		अगर (err)
			वापस err;

		key = l->key + 1;
		/* stop in हाल of wrap around */
		अगर (key < l->key)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fib_notअगरy(काष्ठा net *net, काष्ठा notअगरier_block *nb,
	       काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक h;
	पूर्णांक err;

	क्रम (h = 0; h < FIB_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist) अणु
			err = fib_table_notअगरy(tb, nb, extack);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __trie_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा fib_table *tb = container_of(head, काष्ठा fib_table, rcu);
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;

	अगर (tb->tb_data == tb->__data)
		मुक्त_percpu(t->stats);
#पूर्ण_अगर /* CONFIG_IP_FIB_TRIE_STATS */
	kमुक्त(tb);
पूर्ण

व्योम fib_मुक्त_table(काष्ठा fib_table *tb)
अणु
	call_rcu(&tb->rcu, __trie_मुक्त_rcu);
पूर्ण

अटल पूर्णांक fn_trie_dump_leaf(काष्ठा key_vector *l, काष्ठा fib_table *tb,
			     काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			     काष्ठा fib_dump_filter *filter)
अणु
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	__be32 xkey = htonl(l->key);
	पूर्णांक i, s_i, i_fa, s_fa, err;
	काष्ठा fib_alias *fa;

	अगर (filter->filter_set ||
	    !filter->dump_exceptions || !filter->dump_routes)
		flags |= NLM_F_DUMP_FILTERED;

	s_i = cb->args[4];
	s_fa = cb->args[5];
	i = 0;

	/* rcu_पढ़ो_lock is hold by caller */
	hlist_क्रम_each_entry_rcu(fa, &l->leaf, fa_list) अणु
		काष्ठा fib_info *fi = fa->fa_info;

		अगर (i < s_i)
			जाओ next;

		i_fa = 0;

		अगर (tb->tb_id != fa->tb_id)
			जाओ next;

		अगर (filter->filter_set) अणु
			अगर (filter->rt_type && fa->fa_type != filter->rt_type)
				जाओ next;

			अगर ((filter->protocol &&
			     fi->fib_protocol != filter->protocol))
				जाओ next;

			अगर (filter->dev &&
			    !fib_info_nh_uses_dev(fi, filter->dev))
				जाओ next;
		पूर्ण

		अगर (filter->dump_routes) अणु
			अगर (!s_fa) अणु
				काष्ठा fib_rt_info fri;

				fri.fi = fi;
				fri.tb_id = tb->tb_id;
				fri.dst = xkey;
				fri.dst_len = KEYLENGTH - fa->fa_slen;
				fri.tos = fa->fa_tos;
				fri.type = fa->fa_type;
				fri.offload = fa->offload;
				fri.trap = fa->trap;
				fri.offload_failed = fa->offload_failed;
				err = fib_dump_info(skb,
						    NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    RTM_NEWROUTE, &fri, flags);
				अगर (err < 0)
					जाओ stop;
			पूर्ण

			i_fa++;
		पूर्ण

		अगर (filter->dump_exceptions) अणु
			err = fib_dump_info_fnhe(skb, cb, tb->tb_id, fi,
						 &i_fa, s_fa, flags);
			अगर (err < 0)
				जाओ stop;
		पूर्ण

next:
		i++;
	पूर्ण

	cb->args[4] = i;
	वापस skb->len;

stop:
	cb->args[4] = i;
	cb->args[5] = i_fa;
	वापस err;
पूर्ण

/* rcu_पढ़ो_lock needs to be hold by caller from पढ़ोside */
पूर्णांक fib_table_dump(काष्ठा fib_table *tb, काष्ठा sk_buff *skb,
		   काष्ठा netlink_callback *cb, काष्ठा fib_dump_filter *filter)
अणु
	काष्ठा trie *t = (काष्ठा trie *)tb->tb_data;
	काष्ठा key_vector *l, *tp = t->kv;
	/* Dump starting at last key.
	 * Note: 0.0.0.0/0 (ie शेष) is first key.
	 */
	पूर्णांक count = cb->args[2];
	t_key key = cb->args[3];

	/* First समय here, count and key are both always 0. Count > 0
	 * and key == 0 means the dump has wrapped around and we are करोne.
	 */
	अगर (count && !key)
		वापस skb->len;

	जबतक ((l = leaf_walk_rcu(&tp, key)) != शून्य) अणु
		पूर्णांक err;

		err = fn_trie_dump_leaf(l, tb, skb, cb, filter);
		अगर (err < 0) अणु
			cb->args[3] = key;
			cb->args[2] = count;
			वापस err;
		पूर्ण

		++count;
		key = l->key + 1;

		स_रखो(&cb->args[4], 0,
		       माप(cb->args) - 4*माप(cb->args[0]));

		/* stop loop अगर key wrapped back to 0 */
		अगर (key < l->key)
			अवरोध;
	पूर्ण

	cb->args[3] = key;
	cb->args[2] = count;

	वापस skb->len;
पूर्ण

व्योम __init fib_trie_init(व्योम)
अणु
	fn_alias_kmem = kmem_cache_create("ip_fib_alias",
					  माप(काष्ठा fib_alias),
					  0, SLAB_PANIC, शून्य);

	trie_leaf_kmem = kmem_cache_create("ip_fib_trie",
					   LEAF_SIZE,
					   0, SLAB_PANIC, शून्य);
पूर्ण

काष्ठा fib_table *fib_trie_table(u32 id, काष्ठा fib_table *alias)
अणु
	काष्ठा fib_table *tb;
	काष्ठा trie *t;
	माप_प्रकार sz = माप(*tb);

	अगर (!alias)
		sz += माप(काष्ठा trie);

	tb = kzalloc(sz, GFP_KERNEL);
	अगर (!tb)
		वापस शून्य;

	tb->tb_id = id;
	tb->tb_num_शेष = 0;
	tb->tb_data = (alias ? alias->__data : tb->__data);

	अगर (alias)
		वापस tb;

	t = (काष्ठा trie *) tb->tb_data;
	t->kv[0].pos = KEYLENGTH;
	t->kv[0].slen = KEYLENGTH;
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
	t->stats = alloc_percpu(काष्ठा trie_use_stats);
	अगर (!t->stats) अणु
		kमुक्त(tb);
		tb = शून्य;
	पूर्ण
#पूर्ण_अगर

	वापस tb;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* Depth first Trie walk iterator */
काष्ठा fib_trie_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा fib_table *tb;
	काष्ठा key_vector *tnode;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक depth;
पूर्ण;

अटल काष्ठा key_vector *fib_trie_get_next(काष्ठा fib_trie_iter *iter)
अणु
	अचिन्हित दीर्घ cindex = iter->index;
	काष्ठा key_vector *pn = iter->tnode;
	t_key pkey;

	pr_debug("get_next iter={node=%p index=%d depth=%d}\n",
		 iter->tnode, iter->index, iter->depth);

	जबतक (!IS_TRIE(pn)) अणु
		जबतक (cindex < child_length(pn)) अणु
			काष्ठा key_vector *n = get_child_rcu(pn, cindex++);

			अगर (!n)
				जारी;

			अगर (IS_LEAF(n)) अणु
				iter->tnode = pn;
				iter->index = cindex;
			पूर्ण अन्यथा अणु
				/* push करोwn one level */
				iter->tnode = n;
				iter->index = 0;
				++iter->depth;
			पूर्ण

			वापस n;
		पूर्ण

		/* Current node exhausted, pop back up */
		pkey = pn->key;
		pn = node_parent_rcu(pn);
		cindex = get_index(pkey, pn) + 1;
		--iter->depth;
	पूर्ण

	/* record root node so further searches know we are करोne */
	iter->tnode = pn;
	iter->index = 0;

	वापस शून्य;
पूर्ण

अटल काष्ठा key_vector *fib_trie_get_first(काष्ठा fib_trie_iter *iter,
					     काष्ठा trie *t)
अणु
	काष्ठा key_vector *n, *pn;

	अगर (!t)
		वापस शून्य;

	pn = t->kv;
	n = rcu_dereference(pn->tnode[0]);
	अगर (!n)
		वापस शून्य;

	अगर (IS_TNODE(n)) अणु
		iter->tnode = n;
		iter->index = 0;
		iter->depth = 1;
	पूर्ण अन्यथा अणु
		iter->tnode = pn;
		iter->index = 0;
		iter->depth = 0;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम trie_collect_stats(काष्ठा trie *t, काष्ठा trie_stat *s)
अणु
	काष्ठा key_vector *n;
	काष्ठा fib_trie_iter iter;

	स_रखो(s, 0, माप(*s));

	rcu_पढ़ो_lock();
	क्रम (n = fib_trie_get_first(&iter, t); n; n = fib_trie_get_next(&iter)) अणु
		अगर (IS_LEAF(n)) अणु
			काष्ठा fib_alias *fa;

			s->leaves++;
			s->totdepth += iter.depth;
			अगर (iter.depth > s->maxdepth)
				s->maxdepth = iter.depth;

			hlist_क्रम_each_entry_rcu(fa, &n->leaf, fa_list)
				++s->prefixes;
		पूर्ण अन्यथा अणु
			s->tnodes++;
			अगर (n->bits < MAX_STAT_DEPTH)
				s->nodesizes[n->bits]++;
			s->nullpoपूर्णांकers += tn_info(n)->empty_children;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 *	This outमाला_दो /proc/net/fib_triestats
 */
अटल व्योम trie_show_stats(काष्ठा seq_file *seq, काष्ठा trie_stat *stat)
अणु
	अचिन्हित पूर्णांक i, max, poपूर्णांकers, bytes, avdepth;

	अगर (stat->leaves)
		avdepth = stat->totdepth*100 / stat->leaves;
	अन्यथा
		avdepth = 0;

	seq_म_लिखो(seq, "\tAver depth:     %u.%02d\n",
		   avdepth / 100, avdepth % 100);
	seq_म_लिखो(seq, "\tMax depth:      %u\n", stat->maxdepth);

	seq_म_लिखो(seq, "\tLeaves:         %u\n", stat->leaves);
	bytes = LEAF_SIZE * stat->leaves;

	seq_म_लिखो(seq, "\tPrefixes:       %u\n", stat->prefixes);
	bytes += माप(काष्ठा fib_alias) * stat->prefixes;

	seq_म_लिखो(seq, "\tInternal nodes: %u\n\t", stat->tnodes);
	bytes += TNODE_SIZE(0) * stat->tnodes;

	max = MAX_STAT_DEPTH;
	जबतक (max > 0 && stat->nodesizes[max-1] == 0)
		max--;

	poपूर्णांकers = 0;
	क्रम (i = 1; i < max; i++)
		अगर (stat->nodesizes[i] != 0) अणु
			seq_म_लिखो(seq, "  %u: %u",  i, stat->nodesizes[i]);
			poपूर्णांकers += (1<<i) * stat->nodesizes[i];
		पूर्ण
	seq_अ_दो(seq, '\n');
	seq_म_लिखो(seq, "\tPointers: %u\n", poपूर्णांकers);

	bytes += माप(काष्ठा key_vector *) * poपूर्णांकers;
	seq_म_लिखो(seq, "Null ptrs: %u\n", stat->nullpoपूर्णांकers);
	seq_म_लिखो(seq, "Total size: %u  kB\n", (bytes + 1023) / 1024);
पूर्ण

#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
अटल व्योम trie_show_usage(काष्ठा seq_file *seq,
			    स्थिर काष्ठा trie_use_stats __percpu *stats)
अणु
	काष्ठा trie_use_stats s = अणु 0 पूर्ण;
	पूर्णांक cpu;

	/* loop through all of the CPUs and gather up the stats */
	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा trie_use_stats *pcpu = per_cpu_ptr(stats, cpu);

		s.माला_लो += pcpu->माला_लो;
		s.backtrack += pcpu->backtrack;
		s.semantic_match_passed += pcpu->semantic_match_passed;
		s.semantic_match_miss += pcpu->semantic_match_miss;
		s.null_node_hit += pcpu->null_node_hit;
		s.resize_node_skipped += pcpu->resize_node_skipped;
	पूर्ण

	seq_म_लिखो(seq, "\nCounters:\n---------\n");
	seq_म_लिखो(seq, "gets = %u\n", s.माला_लो);
	seq_म_लिखो(seq, "backtracks = %u\n", s.backtrack);
	seq_म_लिखो(seq, "semantic match passed = %u\n",
		   s.semantic_match_passed);
	seq_म_लिखो(seq, "semantic match miss = %u\n", s.semantic_match_miss);
	seq_म_लिखो(seq, "null node hit= %u\n", s.null_node_hit);
	seq_म_लिखो(seq, "skipped node resize = %u\n\n", s.resize_node_skipped);
पूर्ण
#पूर्ण_अगर /*  CONFIG_IP_FIB_TRIE_STATS */

अटल व्योम fib_table_prपूर्णांक(काष्ठा seq_file *seq, काष्ठा fib_table *tb)
अणु
	अगर (tb->tb_id == RT_TABLE_LOCAL)
		seq_माला_दो(seq, "Local:\n");
	अन्यथा अगर (tb->tb_id == RT_TABLE_MAIN)
		seq_माला_दो(seq, "Main:\n");
	अन्यथा
		seq_म_लिखो(seq, "Id %d:\n", tb->tb_id);
पूर्ण


अटल पूर्णांक fib_triestat_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net *net = (काष्ठा net *)seq->निजी;
	अचिन्हित पूर्णांक h;

	seq_म_लिखो(seq,
		   "Basic info: size of leaf:"
		   " %zd bytes, size of tnode: %zd bytes.\n",
		   LEAF_SIZE, TNODE_SIZE(0));

	rcu_पढ़ो_lock();
	क्रम (h = 0; h < FIB_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist) अणु
			काष्ठा trie *t = (काष्ठा trie *) tb->tb_data;
			काष्ठा trie_stat stat;

			अगर (!t)
				जारी;

			fib_table_prपूर्णांक(seq, tb);

			trie_collect_stats(t, &stat);
			trie_show_stats(seq, &stat);
#अगर_घोषित CONFIG_IP_FIB_TRIE_STATS
			trie_show_usage(seq, t->stats);
#पूर्ण_अगर
		पूर्ण
		cond_resched_rcu();
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल काष्ठा key_vector *fib_trie_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा fib_trie_iter *iter = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	loff_t idx = 0;
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h < FIB_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		काष्ठा fib_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist) अणु
			काष्ठा key_vector *n;

			क्रम (n = fib_trie_get_first(iter,
						    (काष्ठा trie *) tb->tb_data);
			     n; n = fib_trie_get_next(iter))
				अगर (pos == idx++) अणु
					iter->tb = tb;
					वापस n;
				पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *fib_trie_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस fib_trie_get_idx(seq, *pos);
पूर्ण

अटल व्योम *fib_trie_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा fib_trie_iter *iter = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा fib_table *tb = iter->tb;
	काष्ठा hlist_node *tb_node;
	अचिन्हित पूर्णांक h;
	काष्ठा key_vector *n;

	++*pos;
	/* next node in same table */
	n = fib_trie_get_next(iter);
	अगर (n)
		वापस n;

	/* walk rest of this hash chain */
	h = tb->tb_id & (FIB_TABLE_HASHSZ - 1);
	जबतक ((tb_node = rcu_dereference(hlist_next_rcu(&tb->tb_hlist)))) अणु
		tb = hlist_entry(tb_node, काष्ठा fib_table, tb_hlist);
		n = fib_trie_get_first(iter, (काष्ठा trie *) tb->tb_data);
		अगर (n)
			जाओ found;
	पूर्ण

	/* new hash chain */
	जबतक (++h < FIB_TABLE_HASHSZ) अणु
		काष्ठा hlist_head *head = &net->ipv4.fib_table_hash[h];
		hlist_क्रम_each_entry_rcu(tb, head, tb_hlist) अणु
			n = fib_trie_get_first(iter, (काष्ठा trie *) tb->tb_data);
			अगर (n)
				जाओ found;
		पूर्ण
	पूर्ण
	वापस शून्य;

found:
	iter->tb = tb;
	वापस n;
पूर्ण

अटल व्योम fib_trie_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम seq_indent(काष्ठा seq_file *seq, पूर्णांक n)
अणु
	जबतक (n-- > 0)
		seq_माला_दो(seq, "   ");
पूर्ण

अटल अंतरभूत स्थिर अक्षर *rtn_scope(अक्षर *buf, माप_प्रकार len, क्रमागत rt_scope_t s)
अणु
	चयन (s) अणु
	हाल RT_SCOPE_UNIVERSE: वापस "universe";
	हाल RT_SCOPE_SITE:	वापस "site";
	हाल RT_SCOPE_LINK:	वापस "link";
	हाल RT_SCOPE_HOST:	वापस "host";
	हाल RT_SCOPE_NOWHERE:	वापस "nowhere";
	शेष:
		snम_लिखो(buf, len, "scope=%d", s);
		वापस buf;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *स्थिर rtn_type_names[__RTN_MAX] = अणु
	[RTN_UNSPEC] = "UNSPEC",
	[RTN_UNICAST] = "UNICAST",
	[RTN_LOCAL] = "LOCAL",
	[RTN_BROADCAST] = "BROADCAST",
	[RTN_ANYCAST] = "ANYCAST",
	[RTN_MULTICAST] = "MULTICAST",
	[RTN_BLACKHOLE] = "BLACKHOLE",
	[RTN_UNREACHABLE] = "UNREACHABLE",
	[RTN_PROHIBIT] = "PROHIBIT",
	[RTN_THROW] = "THROW",
	[RTN_NAT] = "NAT",
	[RTN_XRESOLVE] = "XRESOLVE",
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *rtn_type(अक्षर *buf, माप_प्रकार len, अचिन्हित पूर्णांक t)
अणु
	अगर (t < __RTN_MAX && rtn_type_names[t])
		वापस rtn_type_names[t];
	snम_लिखो(buf, len, "type %u", t);
	वापस buf;
पूर्ण

/* Pretty prपूर्णांक the trie */
अटल पूर्णांक fib_trie_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा fib_trie_iter *iter = seq->निजी;
	काष्ठा key_vector *n = v;

	अगर (IS_TRIE(node_parent_rcu(n)))
		fib_table_prपूर्णांक(seq, iter->tb);

	अगर (IS_TNODE(n)) अणु
		__be32 prf = htonl(n->key);

		seq_indent(seq, iter->depth-1);
		seq_म_लिखो(seq, "  +-- %pI4/%zu %u %u %u\n",
			   &prf, KEYLENGTH - n->pos - n->bits, n->bits,
			   tn_info(n)->full_children,
			   tn_info(n)->empty_children);
	पूर्ण अन्यथा अणु
		__be32 val = htonl(n->key);
		काष्ठा fib_alias *fa;

		seq_indent(seq, iter->depth);
		seq_म_लिखो(seq, "  |-- %pI4\n", &val);

		hlist_क्रम_each_entry_rcu(fa, &n->leaf, fa_list) अणु
			अक्षर buf1[32], buf2[32];

			seq_indent(seq, iter->depth + 1);
			seq_म_लिखो(seq, "  /%zu %s %s",
				   KEYLENGTH - fa->fa_slen,
				   rtn_scope(buf1, माप(buf1),
					     fa->fa_info->fib_scope),
				   rtn_type(buf2, माप(buf2),
					    fa->fa_type));
			अगर (fa->fa_tos)
				seq_म_लिखो(seq, " tos=%d", fa->fa_tos);
			seq_अ_दो(seq, '\n');
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fib_trie_seq_ops = अणु
	.start  = fib_trie_seq_start,
	.next   = fib_trie_seq_next,
	.stop   = fib_trie_seq_stop,
	.show   = fib_trie_seq_show,
पूर्ण;

काष्ठा fib_route_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा fib_table *मुख्य_tb;
	काष्ठा key_vector *tnode;
	loff_t	pos;
	t_key	key;
पूर्ण;

अटल काष्ठा key_vector *fib_route_get_idx(काष्ठा fib_route_iter *iter,
					    loff_t pos)
अणु
	काष्ठा key_vector *l, **tp = &iter->tnode;
	t_key key;

	/* use cached location of previously found key */
	अगर (iter->pos > 0 && pos >= iter->pos) अणु
		key = iter->key;
	पूर्ण अन्यथा अणु
		iter->pos = 1;
		key = 0;
	पूर्ण

	pos -= iter->pos;

	जबतक ((l = leaf_walk_rcu(tp, key)) && (pos-- > 0)) अणु
		key = l->key + 1;
		iter->pos++;
		l = शून्य;

		/* handle unlikely हाल of a key wrap */
		अगर (!key)
			अवरोध;
	पूर्ण

	अगर (l)
		iter->key = l->key;	/* remember it */
	अन्यथा
		iter->pos = 0;		/* क्रमget it */

	वापस l;
पूर्ण

अटल व्योम *fib_route_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा fib_route_iter *iter = seq->निजी;
	काष्ठा fib_table *tb;
	काष्ठा trie *t;

	rcu_पढ़ो_lock();

	tb = fib_get_table(seq_file_net(seq), RT_TABLE_MAIN);
	अगर (!tb)
		वापस शून्य;

	iter->मुख्य_tb = tb;
	t = (काष्ठा trie *)tb->tb_data;
	iter->tnode = t->kv;

	अगर (*pos != 0)
		वापस fib_route_get_idx(iter, *pos);

	iter->pos = 0;
	iter->key = KEY_MAX;

	वापस SEQ_START_TOKEN;
पूर्ण

अटल व्योम *fib_route_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा fib_route_iter *iter = seq->निजी;
	काष्ठा key_vector *l = शून्य;
	t_key key = iter->key + 1;

	++*pos;

	/* only allow key of 0 क्रम start of sequence */
	अगर ((v == SEQ_START_TOKEN) || key)
		l = leaf_walk_rcu(&iter->tnode, key);

	अगर (l) अणु
		iter->key = l->key;
		iter->pos++;
	पूर्ण अन्यथा अणु
		iter->pos = 0;
	पूर्ण

	वापस l;
पूर्ण

अटल व्योम fib_route_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल अचिन्हित पूर्णांक fib_flag_trans(पूर्णांक type, __be32 mask, काष्ठा fib_info *fi)
अणु
	अचिन्हित पूर्णांक flags = 0;

	अगर (type == RTN_UNREACHABLE || type == RTN_PROHIBIT)
		flags = RTF_REJECT;
	अगर (fi) अणु
		स्थिर काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, 0);

		अगर (nhc->nhc_gw.ipv4)
			flags |= RTF_GATEWAY;
	पूर्ण
	अगर (mask == htonl(0xFFFFFFFF))
		flags |= RTF_HOST;
	flags |= RTF_UP;
	वापस flags;
पूर्ण

/*
 *	This outमाला_दो /proc/net/route.
 *	The क्रमmat of the file is not supposed to be changed
 *	and needs to be same as fib_hash output to aव्योम अवरोधing
 *	legacy utilities
 */
अटल पूर्णांक fib_route_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा fib_route_iter *iter = seq->निजी;
	काष्ठा fib_table *tb = iter->मुख्य_tb;
	काष्ठा fib_alias *fa;
	काष्ठा key_vector *l = v;
	__be32 prefix;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, "%-127s\n", "Iface\tDestination\tGateway "
			   "\tFlags\tRefCnt\tUse\tMetric\tMask\t\tMTU"
			   "\tWindow\tIRTT");
		वापस 0;
	पूर्ण

	prefix = htonl(l->key);

	hlist_क्रम_each_entry_rcu(fa, &l->leaf, fa_list) अणु
		काष्ठा fib_info *fi = fa->fa_info;
		__be32 mask = inet_make_mask(KEYLENGTH - fa->fa_slen);
		अचिन्हित पूर्णांक flags = fib_flag_trans(fa->fa_type, mask, fi);

		अगर ((fa->fa_type == RTN_BROADCAST) ||
		    (fa->fa_type == RTN_MULTICAST))
			जारी;

		अगर (fa->tb_id != tb->tb_id)
			जारी;

		seq_setwidth(seq, 127);

		अगर (fi) अणु
			काष्ठा fib_nh_common *nhc = fib_info_nhc(fi, 0);
			__be32 gw = 0;

			अगर (nhc->nhc_gw_family == AF_INET)
				gw = nhc->nhc_gw.ipv4;

			seq_म_लिखो(seq,
				   "%s\t%08X\t%08X\t%04X\t%d\t%u\t"
				   "%d\t%08X\t%d\t%u\t%u",
				   nhc->nhc_dev ? nhc->nhc_dev->name : "*",
				   prefix, gw, flags, 0, 0,
				   fi->fib_priority,
				   mask,
				   (fi->fib_advmss ?
				    fi->fib_advmss + 40 : 0),
				   fi->fib_winकरोw,
				   fi->fib_rtt >> 3);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(seq,
				   "*\t%08X\t%08X\t%04X\t%d\t%u\t"
				   "%d\t%08X\t%d\t%u\t%u",
				   prefix, 0, flags, 0, 0, 0,
				   mask, 0, 0, 0);
		पूर्ण
		seq_pad(seq, '\n');
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fib_route_seq_ops = अणु
	.start  = fib_route_seq_start,
	.next   = fib_route_seq_next,
	.stop   = fib_route_seq_stop,
	.show   = fib_route_seq_show,
पूर्ण;

पूर्णांक __net_init fib_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("fib_trie", 0444, net->proc_net, &fib_trie_seq_ops,
			माप(काष्ठा fib_trie_iter)))
		जाओ out1;

	अगर (!proc_create_net_single("fib_triestat", 0444, net->proc_net,
			fib_triestat_seq_show, शून्य))
		जाओ out2;

	अगर (!proc_create_net("route", 0444, net->proc_net, &fib_route_seq_ops,
			माप(काष्ठा fib_route_iter)))
		जाओ out3;

	वापस 0;

out3:
	हटाओ_proc_entry("fib_triestat", net->proc_net);
out2:
	हटाओ_proc_entry("fib_trie", net->proc_net);
out1:
	वापस -ENOMEM;
पूर्ण

व्योम __net_निकास fib_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("fib_trie", net->proc_net);
	हटाओ_proc_entry("fib_triestat", net->proc_net);
	हटाओ_proc_entry("route", net->proc_net);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */
