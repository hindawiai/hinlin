<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_u32.c	Ugly (or Universal) 32bit key Packet Classअगरier.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 *	The filters are packed to hash tables of key nodes
 *	with a set of 32bit key/mask pairs at every node.
 *	Nodes reference next level hash tables etc.
 *
 *	This scheme is the best universal classअगरier I managed to
 *	invent; it is not super-fast, but it is not slow (provided you
 *	program it correctly), and general enough.  And its relative
 *	speed grows as the number of rules becomes larger.
 *
 *	It seems that it represents the best middle poपूर्णांक between
 *	speed and manageability both by human and by machine.
 *
 *	It is especially useful क्रम link sharing combined with QoS;
 *	pure RSVP करोesn't need such a general approach and can use
 *	much simpler (and faster) schemes, sort of cls_rsvp.c.
 *
 *	nfmark match added by Catalin(ux aka Dino) BOIE <catab at umbrella.ro>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/percpu.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hash.h>
#समावेश <net/netlink.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/idr.h>

काष्ठा tc_u_knode अणु
	काष्ठा tc_u_knode __rcu	*next;
	u32			handle;
	काष्ठा tc_u_hnode __rcu	*ht_up;
	काष्ठा tcf_exts		exts;
	पूर्णांक			अगरindex;
	u8			fshअगरt;
	काष्ठा tcf_result	res;
	काष्ठा tc_u_hnode __rcu	*ht_करोwn;
#अगर_घोषित CONFIG_CLS_U32_PERF
	काष्ठा tc_u32_pcnt __percpu *pf;
#पूर्ण_अगर
	u32			flags;
	अचिन्हित पूर्णांक		in_hw_count;
#अगर_घोषित CONFIG_CLS_U32_MARK
	u32			val;
	u32			mask;
	u32 __percpu		*pcpu_success;
#पूर्ण_अगर
	काष्ठा rcu_work		rwork;
	/* The 'sel' field MUST be the last field in काष्ठाure to allow क्रम
	 * tc_u32_keys allocated at end of काष्ठाure.
	 */
	काष्ठा tc_u32_sel	sel;
पूर्ण;

काष्ठा tc_u_hnode अणु
	काष्ठा tc_u_hnode __rcu	*next;
	u32			handle;
	u32			prio;
	पूर्णांक			refcnt;
	अचिन्हित पूर्णांक		भागisor;
	काष्ठा idr		handle_idr;
	bool			is_root;
	काष्ठा rcu_head		rcu;
	u32			flags;
	/* The 'ht' field MUST be the last field in काष्ठाure to allow क्रम
	 * more entries allocated at end of काष्ठाure.
	 */
	काष्ठा tc_u_knode __rcu	*ht[];
पूर्ण;

काष्ठा tc_u_common अणु
	काष्ठा tc_u_hnode __rcu	*hlist;
	व्योम			*ptr;
	पूर्णांक			refcnt;
	काष्ठा idr		handle_idr;
	काष्ठा hlist_node	hnode;
	दीर्घ			knodes;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक u32_hash_fold(__be32 key,
					 स्थिर काष्ठा tc_u32_sel *sel,
					 u8 fshअगरt)
अणु
	अचिन्हित पूर्णांक h = ntohl(key & sel->hmask) >> fshअगरt;

	वापस h;
पूर्ण

अटल पूर्णांक u32_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			काष्ठा tcf_result *res)
अणु
	काष्ठा अणु
		काष्ठा tc_u_knode *knode;
		अचिन्हित पूर्णांक	  off;
	पूर्ण stack[TC_U32_MAXDEPTH];

	काष्ठा tc_u_hnode *ht = rcu_dereference_bh(tp->root);
	अचिन्हित पूर्णांक off = skb_network_offset(skb);
	काष्ठा tc_u_knode *n;
	पूर्णांक sdepth = 0;
	पूर्णांक off2 = 0;
	पूर्णांक sel = 0;
#अगर_घोषित CONFIG_CLS_U32_PERF
	पूर्णांक j;
#पूर्ण_अगर
	पूर्णांक i, r;

next_ht:
	n = rcu_dereference_bh(ht->ht[sel]);

next_knode:
	अगर (n) अणु
		काष्ठा tc_u32_key *key = n->sel.keys;

#अगर_घोषित CONFIG_CLS_U32_PERF
		__this_cpu_inc(n->pf->rcnt);
		j = 0;
#पूर्ण_अगर

		अगर (tc_skip_sw(n->flags)) अणु
			n = rcu_dereference_bh(n->next);
			जाओ next_knode;
		पूर्ण

#अगर_घोषित CONFIG_CLS_U32_MARK
		अगर ((skb->mark & n->mask) != n->val) अणु
			n = rcu_dereference_bh(n->next);
			जाओ next_knode;
		पूर्ण अन्यथा अणु
			__this_cpu_inc(*n->pcpu_success);
		पूर्ण
#पूर्ण_अगर

		क्रम (i = n->sel.nkeys; i > 0; i--, key++) अणु
			पूर्णांक toff = off + key->off + (off2 & key->offmask);
			__be32 *data, hdata;

			अगर (skb_headroom(skb) + toff > पूर्णांक_उच्च)
				जाओ out;

			data = skb_header_poपूर्णांकer(skb, toff, 4, &hdata);
			अगर (!data)
				जाओ out;
			अगर ((*data ^ key->val) & key->mask) अणु
				n = rcu_dereference_bh(n->next);
				जाओ next_knode;
			पूर्ण
#अगर_घोषित CONFIG_CLS_U32_PERF
			__this_cpu_inc(n->pf->kcnts[j]);
			j++;
#पूर्ण_अगर
		पूर्ण

		ht = rcu_dereference_bh(n->ht_करोwn);
		अगर (!ht) अणु
check_terminal:
			अगर (n->sel.flags & TC_U32_TERMINAL) अणु

				*res = n->res;
				अगर (!tcf_match_indev(skb, n->अगरindex)) अणु
					n = rcu_dereference_bh(n->next);
					जाओ next_knode;
				पूर्ण
#अगर_घोषित CONFIG_CLS_U32_PERF
				__this_cpu_inc(n->pf->rhit);
#पूर्ण_अगर
				r = tcf_exts_exec(skb, &n->exts, res);
				अगर (r < 0) अणु
					n = rcu_dereference_bh(n->next);
					जाओ next_knode;
				पूर्ण

				वापस r;
			पूर्ण
			n = rcu_dereference_bh(n->next);
			जाओ next_knode;
		पूर्ण

		/* PUSH */
		अगर (sdepth >= TC_U32_MAXDEPTH)
			जाओ deadloop;
		stack[sdepth].knode = n;
		stack[sdepth].off = off;
		sdepth++;

		ht = rcu_dereference_bh(n->ht_करोwn);
		sel = 0;
		अगर (ht->भागisor) अणु
			__be32 *data, hdata;

			data = skb_header_poपूर्णांकer(skb, off + n->sel.hoff, 4,
						  &hdata);
			अगर (!data)
				जाओ out;
			sel = ht->भागisor & u32_hash_fold(*data, &n->sel,
							  n->fshअगरt);
		पूर्ण
		अगर (!(n->sel.flags & (TC_U32_VAROFFSET | TC_U32_OFFSET | TC_U32_EAT)))
			जाओ next_ht;

		अगर (n->sel.flags & (TC_U32_OFFSET | TC_U32_VAROFFSET)) अणु
			off2 = n->sel.off + 3;
			अगर (n->sel.flags & TC_U32_VAROFFSET) अणु
				__be16 *data, hdata;

				data = skb_header_poपूर्णांकer(skb,
							  off + n->sel.offoff,
							  2, &hdata);
				अगर (!data)
					जाओ out;
				off2 += ntohs(n->sel.offmask & *data) >>
					n->sel.offshअगरt;
			पूर्ण
			off2 &= ~3;
		पूर्ण
		अगर (n->sel.flags & TC_U32_EAT) अणु
			off += off2;
			off2 = 0;
		पूर्ण

		अगर (off < skb->len)
			जाओ next_ht;
	पूर्ण

	/* POP */
	अगर (sdepth--) अणु
		n = stack[sdepth].knode;
		ht = rcu_dereference_bh(n->ht_up);
		off = stack[sdepth].off;
		जाओ check_terminal;
	पूर्ण
out:
	वापस -1;

deadloop:
	net_warn_ratelimited("cls_u32: dead loop\n");
	वापस -1;
पूर्ण

अटल काष्ठा tc_u_hnode *u32_lookup_ht(काष्ठा tc_u_common *tp_c, u32 handle)
अणु
	काष्ठा tc_u_hnode *ht;

	क्रम (ht = rtnl_dereference(tp_c->hlist);
	     ht;
	     ht = rtnl_dereference(ht->next))
		अगर (ht->handle == handle)
			अवरोध;

	वापस ht;
पूर्ण

अटल काष्ठा tc_u_knode *u32_lookup_key(काष्ठा tc_u_hnode *ht, u32 handle)
अणु
	अचिन्हित पूर्णांक sel;
	काष्ठा tc_u_knode *n = शून्य;

	sel = TC_U32_HASH(handle);
	अगर (sel > ht->भागisor)
		जाओ out;

	क्रम (n = rtnl_dereference(ht->ht[sel]);
	     n;
	     n = rtnl_dereference(n->next))
		अगर (n->handle == handle)
			अवरोध;
out:
	वापस n;
पूर्ण


अटल व्योम *u32_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा tc_u_hnode *ht;
	काष्ठा tc_u_common *tp_c = tp->data;

	अगर (TC_U32_HTID(handle) == TC_U32_ROOT)
		ht = rtnl_dereference(tp->root);
	अन्यथा
		ht = u32_lookup_ht(tp_c, TC_U32_HTID(handle));

	अगर (!ht)
		वापस शून्य;

	अगर (TC_U32_KEY(handle) == 0)
		वापस ht;

	वापस u32_lookup_key(ht, handle);
पूर्ण

/* Protected by rtnl lock */
अटल u32 gen_new_htid(काष्ठा tc_u_common *tp_c, काष्ठा tc_u_hnode *ptr)
अणु
	पूर्णांक id = idr_alloc_cyclic(&tp_c->handle_idr, ptr, 1, 0x7FF, GFP_KERNEL);
	अगर (id < 0)
		वापस 0;
	वापस (id | 0x800U) << 20;
पूर्ण

अटल काष्ठा hlist_head *tc_u_common_hash;

#घोषणा U32_HASH_SHIFT 10
#घोषणा U32_HASH_SIZE (1 << U32_HASH_SHIFT)

अटल व्योम *tc_u_common_ptr(स्थिर काष्ठा tcf_proto *tp)
अणु
	काष्ठा tcf_block *block = tp->chain->block;

	/* The block sharing is currently supported only
	 * क्रम classless qdiscs. In that हाल we use block
	 * क्रम tc_u_common identअगरication. In हाल the
	 * block is not shared, block->q is a valid poपूर्णांकer
	 * and we can use that. That works क्रम classful qdiscs.
	 */
	अगर (tcf_block_shared(block))
		वापस block;
	अन्यथा
		वापस block->q;
पूर्ण

अटल काष्ठा hlist_head *tc_u_hash(व्योम *key)
अणु
	वापस tc_u_common_hash + hash_ptr(key, U32_HASH_SHIFT);
पूर्ण

अटल काष्ठा tc_u_common *tc_u_common_find(व्योम *key)
अणु
	काष्ठा tc_u_common *tc;
	hlist_क्रम_each_entry(tc, tc_u_hash(key), hnode) अणु
		अगर (tc->ptr == key)
			वापस tc;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक u32_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा tc_u_hnode *root_ht;
	व्योम *key = tc_u_common_ptr(tp);
	काष्ठा tc_u_common *tp_c = tc_u_common_find(key);

	root_ht = kzalloc(काष्ठा_size(root_ht, ht, 1), GFP_KERNEL);
	अगर (root_ht == शून्य)
		वापस -ENOBUFS;

	root_ht->refcnt++;
	root_ht->handle = tp_c ? gen_new_htid(tp_c, root_ht) : 0x80000000;
	root_ht->prio = tp->prio;
	root_ht->is_root = true;
	idr_init(&root_ht->handle_idr);

	अगर (tp_c == शून्य) अणु
		tp_c = kzalloc(काष्ठा_size(tp_c, hlist->ht, 1), GFP_KERNEL);
		अगर (tp_c == शून्य) अणु
			kमुक्त(root_ht);
			वापस -ENOBUFS;
		पूर्ण
		tp_c->ptr = key;
		INIT_HLIST_NODE(&tp_c->hnode);
		idr_init(&tp_c->handle_idr);

		hlist_add_head(&tp_c->hnode, tc_u_hash(key));
	पूर्ण

	tp_c->refcnt++;
	RCU_INIT_POINTER(root_ht->next, tp_c->hlist);
	rcu_assign_poपूर्णांकer(tp_c->hlist, root_ht);

	root_ht->refcnt++;
	rcu_assign_poपूर्णांकer(tp->root, root_ht);
	tp->data = tp_c;
	वापस 0;
पूर्ण

अटल पूर्णांक u32_destroy_key(काष्ठा tc_u_knode *n, bool मुक्त_pf)
अणु
	काष्ठा tc_u_hnode *ht = rtnl_dereference(n->ht_करोwn);

	tcf_exts_destroy(&n->exts);
	tcf_exts_put_net(&n->exts);
	अगर (ht && --ht->refcnt == 0)
		kमुक्त(ht);
#अगर_घोषित CONFIG_CLS_U32_PERF
	अगर (मुक्त_pf)
		मुक्त_percpu(n->pf);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLS_U32_MARK
	अगर (मुक्त_pf)
		मुक्त_percpu(n->pcpu_success);
#पूर्ण_अगर
	kमुक्त(n);
	वापस 0;
पूर्ण

/* u32_delete_key_rcu should be called when मुक्त'ing a copied
 * version of a tc_u_knode obtained from u32_init_knode(). When
 * copies are obtained from u32_init_knode() the statistics are
 * shared between the old and new copies to allow पढ़ोers to
 * जारी to update the statistics during the copy. To support
 * this the u32_delete_key_rcu variant करोes not मुक्त the percpu
 * statistics.
 */
अटल व्योम u32_delete_key_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tc_u_knode *key = container_of(to_rcu_work(work),
					      काष्ठा tc_u_knode,
					      rwork);
	rtnl_lock();
	u32_destroy_key(key, false);
	rtnl_unlock();
पूर्ण

/* u32_delete_key_मुक्तpf_rcu is the rcu callback variant
 * that मुक्त's the entire काष्ठाure including the statistics
 * percpu variables. Only use this अगर the key is not a copy
 * वापसed by u32_init_knode(). See u32_delete_key_rcu()
 * क्रम the variant that should be used with keys वापस from
 * u32_init_knode()
 */
अटल व्योम u32_delete_key_मुक्तpf_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tc_u_knode *key = container_of(to_rcu_work(work),
					      काष्ठा tc_u_knode,
					      rwork);
	rtnl_lock();
	u32_destroy_key(key, true);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक u32_delete_key(काष्ठा tcf_proto *tp, काष्ठा tc_u_knode *key)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_knode __rcu **kp;
	काष्ठा tc_u_knode *pkp;
	काष्ठा tc_u_hnode *ht = rtnl_dereference(key->ht_up);

	अगर (ht) अणु
		kp = &ht->ht[TC_U32_HASH(key->handle)];
		क्रम (pkp = rtnl_dereference(*kp); pkp;
		     kp = &pkp->next, pkp = rtnl_dereference(*kp)) अणु
			अगर (pkp == key) अणु
				RCU_INIT_POINTER(*kp, key->next);
				tp_c->knodes--;

				tcf_unbind_filter(tp, &key->res);
				idr_हटाओ(&ht->handle_idr, key->handle);
				tcf_exts_get_net(&key->exts);
				tcf_queue_work(&key->rwork, u32_delete_key_मुक्तpf_work);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल व्योम u32_clear_hw_hnode(काष्ठा tcf_proto *tp, काष्ठा tc_u_hnode *h,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_u32.common, tp, h->flags, extack);
	cls_u32.command = TC_CLSU32_DELETE_HNODE;
	cls_u32.hnode.भागisor = h->भागisor;
	cls_u32.hnode.handle = h->handle;
	cls_u32.hnode.prio = h->prio;

	tc_setup_cb_call(block, TC_SETUP_CLSU32, &cls_u32, false, true);
पूर्ण

अटल पूर्णांक u32_replace_hw_hnode(काष्ठा tcf_proto *tp, काष्ठा tc_u_hnode *h,
				u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;
	bool skip_sw = tc_skip_sw(flags);
	bool offloaded = false;
	पूर्णांक err;

	tc_cls_common_offload_init(&cls_u32.common, tp, flags, extack);
	cls_u32.command = TC_CLSU32_NEW_HNODE;
	cls_u32.hnode.भागisor = h->भागisor;
	cls_u32.hnode.handle = h->handle;
	cls_u32.hnode.prio = h->prio;

	err = tc_setup_cb_call(block, TC_SETUP_CLSU32, &cls_u32, skip_sw, true);
	अगर (err < 0) अणु
		u32_clear_hw_hnode(tp, h, शून्य);
		वापस err;
	पूर्ण अन्यथा अगर (err > 0) अणु
		offloaded = true;
	पूर्ण

	अगर (skip_sw && !offloaded)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम u32_हटाओ_hw_knode(काष्ठा tcf_proto *tp, काष्ठा tc_u_knode *n,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_u32.common, tp, n->flags, extack);
	cls_u32.command = TC_CLSU32_DELETE_KNODE;
	cls_u32.knode.handle = n->handle;

	tc_setup_cb_destroy(block, tp, TC_SETUP_CLSU32, &cls_u32, false,
			    &n->flags, &n->in_hw_count, true);
पूर्ण

अटल पूर्णांक u32_replace_hw_knode(काष्ठा tcf_proto *tp, काष्ठा tc_u_knode *n,
				u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_hnode *ht = rtnl_dereference(n->ht_करोwn);
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;
	bool skip_sw = tc_skip_sw(flags);
	पूर्णांक err;

	tc_cls_common_offload_init(&cls_u32.common, tp, flags, extack);
	cls_u32.command = TC_CLSU32_REPLACE_KNODE;
	cls_u32.knode.handle = n->handle;
	cls_u32.knode.fshअगरt = n->fshअगरt;
#अगर_घोषित CONFIG_CLS_U32_MARK
	cls_u32.knode.val = n->val;
	cls_u32.knode.mask = n->mask;
#अन्यथा
	cls_u32.knode.val = 0;
	cls_u32.knode.mask = 0;
#पूर्ण_अगर
	cls_u32.knode.sel = &n->sel;
	cls_u32.knode.res = &n->res;
	cls_u32.knode.exts = &n->exts;
	अगर (n->ht_करोwn)
		cls_u32.knode.link_handle = ht->handle;

	err = tc_setup_cb_add(block, tp, TC_SETUP_CLSU32, &cls_u32, skip_sw,
			      &n->flags, &n->in_hw_count, true);
	अगर (err) अणु
		u32_हटाओ_hw_knode(tp, n, शून्य);
		वापस err;
	पूर्ण

	अगर (skip_sw && !(n->flags & TCA_CLS_FLAGS_IN_HW))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम u32_clear_hnode(काष्ठा tcf_proto *tp, काष्ठा tc_u_hnode *ht,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_knode *n;
	अचिन्हित पूर्णांक h;

	क्रम (h = 0; h <= ht->भागisor; h++) अणु
		जबतक ((n = rtnl_dereference(ht->ht[h])) != शून्य) अणु
			RCU_INIT_POINTER(ht->ht[h],
					 rtnl_dereference(n->next));
			tp_c->knodes--;
			tcf_unbind_filter(tp, &n->res);
			u32_हटाओ_hw_knode(tp, n, extack);
			idr_हटाओ(&ht->handle_idr, n->handle);
			अगर (tcf_exts_get_net(&n->exts))
				tcf_queue_work(&n->rwork, u32_delete_key_मुक्तpf_work);
			अन्यथा
				u32_destroy_key(n, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक u32_destroy_hnode(काष्ठा tcf_proto *tp, काष्ठा tc_u_hnode *ht,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_hnode __rcu **hn;
	काष्ठा tc_u_hnode *phn;

	WARN_ON(--ht->refcnt);

	u32_clear_hnode(tp, ht, extack);

	hn = &tp_c->hlist;
	क्रम (phn = rtnl_dereference(*hn);
	     phn;
	     hn = &phn->next, phn = rtnl_dereference(*hn)) अणु
		अगर (phn == ht) अणु
			u32_clear_hw_hnode(tp, ht, extack);
			idr_destroy(&ht->handle_idr);
			idr_हटाओ(&tp_c->handle_idr, ht->handle);
			RCU_INIT_POINTER(*hn, ht->next);
			kमुक्त_rcu(ht, rcu);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल व्योम u32_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_hnode *root_ht = rtnl_dereference(tp->root);

	WARN_ON(root_ht == शून्य);

	अगर (root_ht && --root_ht->refcnt == 1)
		u32_destroy_hnode(tp, root_ht, extack);

	अगर (--tp_c->refcnt == 0) अणु
		काष्ठा tc_u_hnode *ht;

		hlist_del(&tp_c->hnode);

		जबतक ((ht = rtnl_dereference(tp_c->hlist)) != शून्य) अणु
			u32_clear_hnode(tp, ht, extack);
			RCU_INIT_POINTER(tp_c->hlist, ht->next);

			/* u32_destroy_key() will later मुक्त ht क्रम us, अगर it's
			 * still referenced by some knode
			 */
			अगर (--ht->refcnt == 0)
				kमुक्त_rcu(ht, rcu);
		पूर्ण

		idr_destroy(&tp_c->handle_idr);
		kमुक्त(tp_c);
	पूर्ण

	tp->data = शून्य;
पूर्ण

अटल पूर्णांक u32_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		      bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_hnode *ht = arg;
	काष्ठा tc_u_common *tp_c = tp->data;
	पूर्णांक ret = 0;

	अगर (TC_U32_KEY(ht->handle)) अणु
		u32_हटाओ_hw_knode(tp, (काष्ठा tc_u_knode *)ht, extack);
		ret = u32_delete_key(tp, (काष्ठा tc_u_knode *)ht);
		जाओ out;
	पूर्ण

	अगर (ht->is_root) अणु
		NL_SET_ERR_MSG_MOD(extack, "Not allowed to delete root node");
		वापस -EINVAL;
	पूर्ण

	अगर (ht->refcnt == 1) अणु
		u32_destroy_hnode(tp, ht, extack);
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Can not delete in-use filter");
		वापस -EBUSY;
	पूर्ण

out:
	*last = tp_c->refcnt == 1 && tp_c->knodes == 0;
	वापस ret;
पूर्ण

अटल u32 gen_new_kid(काष्ठा tc_u_hnode *ht, u32 htid)
अणु
	u32 index = htid | 0x800;
	u32 max = htid | 0xFFF;

	अगर (idr_alloc_u32(&ht->handle_idr, शून्य, &index, max, GFP_KERNEL)) अणु
		index = htid + 1;
		अगर (idr_alloc_u32(&ht->handle_idr, शून्य, &index, max,
				 GFP_KERNEL))
			index = max;
	पूर्ण

	वापस index;
पूर्ण

अटल स्थिर काष्ठा nla_policy u32_policy[TCA_U32_MAX + 1] = अणु
	[TCA_U32_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_U32_HASH]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_U32_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_U32_DIVISOR]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_U32_SEL]		= अणु .len = माप(काष्ठा tc_u32_sel) पूर्ण,
	[TCA_U32_INDEV]		= अणु .type = NLA_STRING, .len = IFNAMSIZ पूर्ण,
	[TCA_U32_MARK]		= अणु .len = माप(काष्ठा tc_u32_mark) पूर्ण,
	[TCA_U32_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक u32_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			 अचिन्हित दीर्घ base,
			 काष्ठा tc_u_knode *n, काष्ठा nlattr **tb,
			 काष्ठा nlattr *est, bool ovr,
			 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, est, &n->exts, ovr, true, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_U32_LINK]) अणु
		u32 handle = nla_get_u32(tb[TCA_U32_LINK]);
		काष्ठा tc_u_hnode *ht_करोwn = शून्य, *ht_old;

		अगर (TC_U32_KEY(handle)) अणु
			NL_SET_ERR_MSG_MOD(extack, "u32 Link handle must be a hash table");
			वापस -EINVAL;
		पूर्ण

		अगर (handle) अणु
			ht_करोwn = u32_lookup_ht(tp->data, handle);

			अगर (!ht_करोwn) अणु
				NL_SET_ERR_MSG_MOD(extack, "Link hash table not found");
				वापस -EINVAL;
			पूर्ण
			अगर (ht_करोwn->is_root) अणु
				NL_SET_ERR_MSG_MOD(extack, "Not linking to root node");
				वापस -EINVAL;
			पूर्ण
			ht_करोwn->refcnt++;
		पूर्ण

		ht_old = rtnl_dereference(n->ht_करोwn);
		rcu_assign_poपूर्णांकer(n->ht_करोwn, ht_करोwn);

		अगर (ht_old)
			ht_old->refcnt--;
	पूर्ण
	अगर (tb[TCA_U32_CLASSID]) अणु
		n->res.classid = nla_get_u32(tb[TCA_U32_CLASSID]);
		tcf_bind_filter(tp, &n->res, base);
	पूर्ण

	अगर (tb[TCA_U32_INDEV]) अणु
		पूर्णांक ret;
		ret = tcf_change_indev(net, tb[TCA_U32_INDEV], extack);
		अगर (ret < 0)
			वापस -EINVAL;
		n->अगरindex = ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम u32_replace_knode(काष्ठा tcf_proto *tp, काष्ठा tc_u_common *tp_c,
			      काष्ठा tc_u_knode *n)
अणु
	काष्ठा tc_u_knode __rcu **ins;
	काष्ठा tc_u_knode *pins;
	काष्ठा tc_u_hnode *ht;

	अगर (TC_U32_HTID(n->handle) == TC_U32_ROOT)
		ht = rtnl_dereference(tp->root);
	अन्यथा
		ht = u32_lookup_ht(tp_c, TC_U32_HTID(n->handle));

	ins = &ht->ht[TC_U32_HASH(n->handle)];

	/* The node must always exist क्रम it to be replaced अगर this is not the
	 * हाल then something went very wrong अन्यथाwhere.
	 */
	क्रम (pins = rtnl_dereference(*ins); ;
	     ins = &pins->next, pins = rtnl_dereference(*ins))
		अगर (pins->handle == n->handle)
			अवरोध;

	idr_replace(&ht->handle_idr, n, n->handle);
	RCU_INIT_POINTER(n->next, pins->next);
	rcu_assign_poपूर्णांकer(*ins, n);
पूर्ण

अटल काष्ठा tc_u_knode *u32_init_knode(काष्ठा net *net, काष्ठा tcf_proto *tp,
					 काष्ठा tc_u_knode *n)
अणु
	काष्ठा tc_u_hnode *ht = rtnl_dereference(n->ht_करोwn);
	काष्ठा tc_u32_sel *s = &n->sel;
	काष्ठा tc_u_knode *new;

	new = kzalloc(काष्ठा_size(new, sel.keys, s->nkeys), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	RCU_INIT_POINTER(new->next, n->next);
	new->handle = n->handle;
	RCU_INIT_POINTER(new->ht_up, n->ht_up);

	new->अगरindex = n->अगरindex;
	new->fshअगरt = n->fshअगरt;
	new->res = n->res;
	new->flags = n->flags;
	RCU_INIT_POINTER(new->ht_करोwn, ht);

	/* bump reference count as दीर्घ as we hold poपूर्णांकer to काष्ठाure */
	अगर (ht)
		ht->refcnt++;

#अगर_घोषित CONFIG_CLS_U32_PERF
	/* Statistics may be incremented by पढ़ोers during update
	 * so we must keep them in tact. When the node is later destroyed
	 * a special destroy call must be made to not मुक्त the pf memory.
	 */
	new->pf = n->pf;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CLS_U32_MARK
	new->val = n->val;
	new->mask = n->mask;
	/* Similarly success statistics must be moved as poपूर्णांकers */
	new->pcpu_success = n->pcpu_success;
#पूर्ण_अगर
	स_नकल(&new->sel, s, काष्ठा_size(s, keys, s->nkeys));

	अगर (tcf_exts_init(&new->exts, net, TCA_U32_ACT, TCA_U32_POLICE)) अणु
		kमुक्त(new);
		वापस शून्य;
	पूर्ण

	वापस new;
पूर्ण

अटल पूर्णांक u32_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		      काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base, u32 handle,
		      काष्ठा nlattr **tca, व्योम **arg, bool ovr, bool rtnl_held,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_hnode *ht;
	काष्ठा tc_u_knode *n;
	काष्ठा tc_u32_sel *s;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_U32_MAX + 1];
	u32 htid, flags = 0;
	माप_प्रकार sel_size;
	पूर्णांक err;

	अगर (!opt) अणु
		अगर (handle) अणु
			NL_SET_ERR_MSG_MOD(extack, "Filter handle requires options");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_U32_MAX, opt, u32_policy,
					  extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_U32_FLAGS]) अणु
		flags = nla_get_u32(tb[TCA_U32_FLAGS]);
		अगर (!tc_flags_valid(flags)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid filter flags");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	n = *arg;
	अगर (n) अणु
		काष्ठा tc_u_knode *new;

		अगर (TC_U32_KEY(n->handle) == 0) अणु
			NL_SET_ERR_MSG_MOD(extack, "Key node id cannot be zero");
			वापस -EINVAL;
		पूर्ण

		अगर ((n->flags ^ flags) &
		    ~(TCA_CLS_FLAGS_IN_HW | TCA_CLS_FLAGS_NOT_IN_HW)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Key node flags do not match passed flags");
			वापस -EINVAL;
		पूर्ण

		new = u32_init_knode(net, tp, n);
		अगर (!new)
			वापस -ENOMEM;

		err = u32_set_parms(net, tp, base, new, tb,
				    tca[TCA_RATE], ovr, extack);

		अगर (err) अणु
			u32_destroy_key(new, false);
			वापस err;
		पूर्ण

		err = u32_replace_hw_knode(tp, new, flags, extack);
		अगर (err) अणु
			u32_destroy_key(new, false);
			वापस err;
		पूर्ण

		अगर (!tc_in_hw(new->flags))
			new->flags |= TCA_CLS_FLAGS_NOT_IN_HW;

		u32_replace_knode(tp, tp_c, new);
		tcf_unbind_filter(tp, &n->res);
		tcf_exts_get_net(&n->exts);
		tcf_queue_work(&n->rwork, u32_delete_key_work);
		वापस 0;
	पूर्ण

	अगर (tb[TCA_U32_DIVISOR]) अणु
		अचिन्हित पूर्णांक भागisor = nla_get_u32(tb[TCA_U32_DIVISOR]);

		अगर (!is_घातer_of_2(भागisor)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Divisor is not a power of 2");
			वापस -EINVAL;
		पूर्ण
		अगर (भागisor-- > 0x100) अणु
			NL_SET_ERR_MSG_MOD(extack, "Exceeded maximum 256 hash buckets");
			वापस -EINVAL;
		पूर्ण
		अगर (TC_U32_KEY(handle)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Divisor can only be used on a hash table");
			वापस -EINVAL;
		पूर्ण
		ht = kzalloc(काष्ठा_size(ht, ht, भागisor + 1), GFP_KERNEL);
		अगर (ht == शून्य)
			वापस -ENOBUFS;
		अगर (handle == 0) अणु
			handle = gen_new_htid(tp->data, ht);
			अगर (handle == 0) अणु
				kमुक्त(ht);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = idr_alloc_u32(&tp_c->handle_idr, ht, &handle,
					    handle, GFP_KERNEL);
			अगर (err) अणु
				kमुक्त(ht);
				वापस err;
			पूर्ण
		पूर्ण
		ht->refcnt = 1;
		ht->भागisor = भागisor;
		ht->handle = handle;
		ht->prio = tp->prio;
		idr_init(&ht->handle_idr);
		ht->flags = flags;

		err = u32_replace_hw_hnode(tp, ht, flags, extack);
		अगर (err) अणु
			idr_हटाओ(&tp_c->handle_idr, handle);
			kमुक्त(ht);
			वापस err;
		पूर्ण

		RCU_INIT_POINTER(ht->next, tp_c->hlist);
		rcu_assign_poपूर्णांकer(tp_c->hlist, ht);
		*arg = ht;

		वापस 0;
	पूर्ण

	अगर (tb[TCA_U32_HASH]) अणु
		htid = nla_get_u32(tb[TCA_U32_HASH]);
		अगर (TC_U32_HTID(htid) == TC_U32_ROOT) अणु
			ht = rtnl_dereference(tp->root);
			htid = ht->handle;
		पूर्ण अन्यथा अणु
			ht = u32_lookup_ht(tp->data, TC_U32_HTID(htid));
			अगर (!ht) अणु
				NL_SET_ERR_MSG_MOD(extack, "Specified hash table not found");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ht = rtnl_dereference(tp->root);
		htid = ht->handle;
	पूर्ण

	अगर (ht->भागisor < TC_U32_HASH(htid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Specified hash table buckets exceed configured value");
		वापस -EINVAL;
	पूर्ण

	अगर (handle) अणु
		अगर (TC_U32_HTID(handle) && TC_U32_HTID(handle ^ htid)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Handle specified hash table address mismatch");
			वापस -EINVAL;
		पूर्ण
		handle = htid | TC_U32_NODE(handle);
		err = idr_alloc_u32(&ht->handle_idr, शून्य, &handle, handle,
				    GFP_KERNEL);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		handle = gen_new_kid(ht, htid);

	अगर (tb[TCA_U32_SEL] == शून्य) अणु
		NL_SET_ERR_MSG_MOD(extack, "Selector not specified");
		err = -EINVAL;
		जाओ erridr;
	पूर्ण

	s = nla_data(tb[TCA_U32_SEL]);
	sel_size = काष्ठा_size(s, keys, s->nkeys);
	अगर (nla_len(tb[TCA_U32_SEL]) < sel_size) अणु
		err = -EINVAL;
		जाओ erridr;
	पूर्ण

	n = kzalloc(काष्ठा_size(n, sel.keys, s->nkeys), GFP_KERNEL);
	अगर (n == शून्य) अणु
		err = -ENOBUFS;
		जाओ erridr;
	पूर्ण

#अगर_घोषित CONFIG_CLS_U32_PERF
	n->pf = __alloc_percpu(काष्ठा_size(n->pf, kcnts, s->nkeys),
			       __alignof__(काष्ठा tc_u32_pcnt));
	अगर (!n->pf) अणु
		err = -ENOBUFS;
		जाओ errमुक्त;
	पूर्ण
#पूर्ण_अगर

	स_नकल(&n->sel, s, sel_size);
	RCU_INIT_POINTER(n->ht_up, ht);
	n->handle = handle;
	n->fshअगरt = s->hmask ? ffs(ntohl(s->hmask)) - 1 : 0;
	n->flags = flags;

	err = tcf_exts_init(&n->exts, net, TCA_U32_ACT, TCA_U32_POLICE);
	अगर (err < 0)
		जाओ errout;

#अगर_घोषित CONFIG_CLS_U32_MARK
	n->pcpu_success = alloc_percpu(u32);
	अगर (!n->pcpu_success) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	अगर (tb[TCA_U32_MARK]) अणु
		काष्ठा tc_u32_mark *mark;

		mark = nla_data(tb[TCA_U32_MARK]);
		n->val = mark->val;
		n->mask = mark->mask;
	पूर्ण
#पूर्ण_अगर

	err = u32_set_parms(net, tp, base, n, tb, tca[TCA_RATE], ovr,
			    extack);
	अगर (err == 0) अणु
		काष्ठा tc_u_knode __rcu **ins;
		काष्ठा tc_u_knode *pins;

		err = u32_replace_hw_knode(tp, n, flags, extack);
		अगर (err)
			जाओ errhw;

		अगर (!tc_in_hw(n->flags))
			n->flags |= TCA_CLS_FLAGS_NOT_IN_HW;

		ins = &ht->ht[TC_U32_HASH(handle)];
		क्रम (pins = rtnl_dereference(*ins); pins;
		     ins = &pins->next, pins = rtnl_dereference(*ins))
			अगर (TC_U32_NODE(handle) < TC_U32_NODE(pins->handle))
				अवरोध;

		RCU_INIT_POINTER(n->next, pins);
		rcu_assign_poपूर्णांकer(*ins, n);
		tp_c->knodes++;
		*arg = n;
		वापस 0;
	पूर्ण

errhw:
#अगर_घोषित CONFIG_CLS_U32_MARK
	मुक्त_percpu(n->pcpu_success);
#पूर्ण_अगर

errout:
	tcf_exts_destroy(&n->exts);
#अगर_घोषित CONFIG_CLS_U32_PERF
errमुक्त:
	मुक्त_percpu(n->pf);
#पूर्ण_अगर
	kमुक्त(n);
erridr:
	idr_हटाओ(&ht->handle_idr, handle);
	वापस err;
पूर्ण

अटल व्योम u32_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		     bool rtnl_held)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_hnode *ht;
	काष्ठा tc_u_knode *n;
	अचिन्हित पूर्णांक h;

	अगर (arg->stop)
		वापस;

	क्रम (ht = rtnl_dereference(tp_c->hlist);
	     ht;
	     ht = rtnl_dereference(ht->next)) अणु
		अगर (ht->prio != tp->prio)
			जारी;
		अगर (arg->count >= arg->skip) अणु
			अगर (arg->fn(tp, ht, arg) < 0) अणु
				arg->stop = 1;
				वापस;
			पूर्ण
		पूर्ण
		arg->count++;
		क्रम (h = 0; h <= ht->भागisor; h++) अणु
			क्रम (n = rtnl_dereference(ht->ht[h]);
			     n;
			     n = rtnl_dereference(n->next)) अणु
				अगर (arg->count < arg->skip) अणु
					arg->count++;
					जारी;
				पूर्ण
				अगर (arg->fn(tp, n, arg) < 0) अणु
					arg->stop = 1;
					वापस;
				पूर्ण
				arg->count++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक u32_reoffload_hnode(काष्ठा tcf_proto *tp, काष्ठा tc_u_hnode *ht,
			       bool add, flow_setup_cb_t *cb, व्योम *cb_priv,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;
	पूर्णांक err;

	tc_cls_common_offload_init(&cls_u32.common, tp, ht->flags, extack);
	cls_u32.command = add ? TC_CLSU32_NEW_HNODE : TC_CLSU32_DELETE_HNODE;
	cls_u32.hnode.भागisor = ht->भागisor;
	cls_u32.hnode.handle = ht->handle;
	cls_u32.hnode.prio = ht->prio;

	err = cb(TC_SETUP_CLSU32, &cls_u32, cb_priv);
	अगर (err && add && tc_skip_sw(ht->flags))
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक u32_reoffload_knode(काष्ठा tcf_proto *tp, काष्ठा tc_u_knode *n,
			       bool add, flow_setup_cb_t *cb, व्योम *cb_priv,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_hnode *ht = rtnl_dereference(n->ht_करोwn);
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_u32_offload cls_u32 = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_u32.common, tp, n->flags, extack);
	cls_u32.command = add ?
		TC_CLSU32_REPLACE_KNODE : TC_CLSU32_DELETE_KNODE;
	cls_u32.knode.handle = n->handle;

	अगर (add) अणु
		cls_u32.knode.fshअगरt = n->fshअगरt;
#अगर_घोषित CONFIG_CLS_U32_MARK
		cls_u32.knode.val = n->val;
		cls_u32.knode.mask = n->mask;
#अन्यथा
		cls_u32.knode.val = 0;
		cls_u32.knode.mask = 0;
#पूर्ण_अगर
		cls_u32.knode.sel = &n->sel;
		cls_u32.knode.res = &n->res;
		cls_u32.knode.exts = &n->exts;
		अगर (n->ht_करोwn)
			cls_u32.knode.link_handle = ht->handle;
	पूर्ण

	वापस tc_setup_cb_reoffload(block, tp, add, cb, TC_SETUP_CLSU32,
				     &cls_u32, cb_priv, &n->flags,
				     &n->in_hw_count);
पूर्ण

अटल पूर्णांक u32_reoffload(काष्ठा tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			 व्योम *cb_priv, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u_common *tp_c = tp->data;
	काष्ठा tc_u_hnode *ht;
	काष्ठा tc_u_knode *n;
	अचिन्हित पूर्णांक h;
	पूर्णांक err;

	क्रम (ht = rtnl_dereference(tp_c->hlist);
	     ht;
	     ht = rtnl_dereference(ht->next)) अणु
		अगर (ht->prio != tp->prio)
			जारी;

		/* When adding filters to a new dev, try to offload the
		 * hashtable first. When removing, करो the filters beक्रमe the
		 * hashtable.
		 */
		अगर (add && !tc_skip_hw(ht->flags)) अणु
			err = u32_reoffload_hnode(tp, ht, add, cb, cb_priv,
						  extack);
			अगर (err)
				वापस err;
		पूर्ण

		क्रम (h = 0; h <= ht->भागisor; h++) अणु
			क्रम (n = rtnl_dereference(ht->ht[h]);
			     n;
			     n = rtnl_dereference(n->next)) अणु
				अगर (tc_skip_hw(n->flags))
					जारी;

				err = u32_reoffload_knode(tp, n, add, cb,
							  cb_priv, extack);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण

		अगर (!add && !tc_skip_hw(ht->flags))
			u32_reoffload_hnode(tp, ht, add, cb, cb_priv, extack);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम u32_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			   अचिन्हित दीर्घ base)
अणु
	काष्ठा tc_u_knode *n = fh;

	अगर (n && n->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &n->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &n->res);
	पूर्ण
पूर्ण

अटल पूर्णांक u32_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		    काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा tc_u_knode *n = fh;
	काष्ठा tc_u_hnode *ht_up, *ht_करोwn;
	काष्ठा nlattr *nest;

	अगर (n == शून्य)
		वापस skb->len;

	t->tcm_handle = n->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (TC_U32_KEY(n->handle) == 0) अणु
		काष्ठा tc_u_hnode *ht = fh;
		u32 भागisor = ht->भागisor + 1;

		अगर (nla_put_u32(skb, TCA_U32_DIVISOR, भागisor))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_CLS_U32_PERF
		काष्ठा tc_u32_pcnt *gpf;
		पूर्णांक cpu;
#पूर्ण_अगर

		अगर (nla_put(skb, TCA_U32_SEL, काष्ठा_size(&n->sel, keys, n->sel.nkeys),
			    &n->sel))
			जाओ nla_put_failure;

		ht_up = rtnl_dereference(n->ht_up);
		अगर (ht_up) अणु
			u32 htid = n->handle & 0xFFFFF000;
			अगर (nla_put_u32(skb, TCA_U32_HASH, htid))
				जाओ nla_put_failure;
		पूर्ण
		अगर (n->res.classid &&
		    nla_put_u32(skb, TCA_U32_CLASSID, n->res.classid))
			जाओ nla_put_failure;

		ht_करोwn = rtnl_dereference(n->ht_करोwn);
		अगर (ht_करोwn &&
		    nla_put_u32(skb, TCA_U32_LINK, ht_करोwn->handle))
			जाओ nla_put_failure;

		अगर (n->flags && nla_put_u32(skb, TCA_U32_FLAGS, n->flags))
			जाओ nla_put_failure;

#अगर_घोषित CONFIG_CLS_U32_MARK
		अगर ((n->val || n->mask)) अणु
			काष्ठा tc_u32_mark mark = अणु.val = n->val,
						   .mask = n->mask,
						   .success = 0पूर्ण;
			पूर्णांक cpum;

			क्रम_each_possible_cpu(cpum) अणु
				__u32 cnt = *per_cpu_ptr(n->pcpu_success, cpum);

				mark.success += cnt;
			पूर्ण

			अगर (nla_put(skb, TCA_U32_MARK, माप(mark), &mark))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर

		अगर (tcf_exts_dump(skb, &n->exts) < 0)
			जाओ nla_put_failure;

		अगर (n->अगरindex) अणु
			काष्ठा net_device *dev;
			dev = __dev_get_by_index(net, n->अगरindex);
			अगर (dev && nla_put_string(skb, TCA_U32_INDEV, dev->name))
				जाओ nla_put_failure;
		पूर्ण
#अगर_घोषित CONFIG_CLS_U32_PERF
		gpf = kzalloc(काष्ठा_size(gpf, kcnts, n->sel.nkeys), GFP_KERNEL);
		अगर (!gpf)
			जाओ nla_put_failure;

		क्रम_each_possible_cpu(cpu) अणु
			पूर्णांक i;
			काष्ठा tc_u32_pcnt *pf = per_cpu_ptr(n->pf, cpu);

			gpf->rcnt += pf->rcnt;
			gpf->rhit += pf->rhit;
			क्रम (i = 0; i < n->sel.nkeys; i++)
				gpf->kcnts[i] += pf->kcnts[i];
		पूर्ण

		अगर (nla_put_64bit(skb, TCA_U32_PCNT, काष्ठा_size(gpf, kcnts, n->sel.nkeys),
				  gpf, TCA_U32_PAD)) अणु
			kमुक्त(gpf);
			जाओ nla_put_failure;
		पूर्ण
		kमुक्त(gpf);
#पूर्ण_अगर
	पूर्ण

	nla_nest_end(skb, nest);

	अगर (TC_U32_KEY(n->handle))
		अगर (tcf_exts_dump_stats(skb, &n->exts) < 0)
			जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल काष्ठा tcf_proto_ops cls_u32_ops __पढ़ो_mostly = अणु
	.kind		=	"u32",
	.classअगरy	=	u32_classअगरy,
	.init		=	u32_init,
	.destroy	=	u32_destroy,
	.get		=	u32_get,
	.change		=	u32_change,
	.delete		=	u32_delete,
	.walk		=	u32_walk,
	.reoffload	=	u32_reoffload,
	.dump		=	u32_dump,
	.bind_class	=	u32_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_u32(व्योम)
अणु
	पूर्णांक i, ret;

	pr_info("u32 classifier\n");
#अगर_घोषित CONFIG_CLS_U32_PERF
	pr_info("    Performance counters on\n");
#पूर्ण_अगर
	pr_info("    input device check on\n");
#अगर_घोषित CONFIG_NET_CLS_ACT
	pr_info("    Actions configured\n");
#पूर्ण_अगर
	tc_u_common_hash = kvदो_स्मृति_array(U32_HASH_SIZE,
					  माप(काष्ठा hlist_head),
					  GFP_KERNEL);
	अगर (!tc_u_common_hash)
		वापस -ENOMEM;

	क्रम (i = 0; i < U32_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&tc_u_common_hash[i]);

	ret = रेजिस्टर_tcf_proto_ops(&cls_u32_ops);
	अगर (ret)
		kvमुक्त(tc_u_common_hash);
	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_u32(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_u32_ops);
	kvमुक्त(tc_u_common_hash);
पूर्ण

module_init(init_u32)
module_निकास(निकास_u32)
MODULE_LICENSE("GPL");
