<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_flower.c		Flower classअगरier
 *
 * Copyright (c) 2015 Jiri Pirko <jiri@resnulli.us>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/refcount.h>

#समावेश <linux/अगर_ether.h>
#समावेश <linux/in6.h>
#समावेश <linux/ip.h>
#समावेश <linux/mpls.h>

#समावेश <net/sch_generic.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/ip.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/geneve.h>
#समावेश <net/vxlan.h>
#समावेश <net/erspan.h>

#समावेश <net/dst.h>
#समावेश <net/dst_metadata.h>

#समावेश <uapi/linux/netfilter/nf_conntrack_common.h>

#घोषणा TCA_FLOWER_KEY_CT_FLAGS_MAX \
		((__TCA_FLOWER_KEY_CT_FLAGS_MAX - 1) << 1)
#घोषणा TCA_FLOWER_KEY_CT_FLAGS_MASK \
		(TCA_FLOWER_KEY_CT_FLAGS_MAX - 1)

काष्ठा fl_flow_key अणु
	काष्ठा flow_dissector_key_meta meta;
	काष्ठा flow_dissector_key_control control;
	काष्ठा flow_dissector_key_control enc_control;
	काष्ठा flow_dissector_key_basic basic;
	काष्ठा flow_dissector_key_eth_addrs eth;
	काष्ठा flow_dissector_key_vlan vlan;
	काष्ठा flow_dissector_key_vlan cvlan;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_ports tp;
	काष्ठा flow_dissector_key_icmp icmp;
	काष्ठा flow_dissector_key_arp arp;
	काष्ठा flow_dissector_key_keyid enc_key_id;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs enc_ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs enc_ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_ports enc_tp;
	काष्ठा flow_dissector_key_mpls mpls;
	काष्ठा flow_dissector_key_tcp tcp;
	काष्ठा flow_dissector_key_ip ip;
	काष्ठा flow_dissector_key_ip enc_ip;
	काष्ठा flow_dissector_key_enc_opts enc_opts;
	जोड़ अणु
		काष्ठा flow_dissector_key_ports tp;
		काष्ठा अणु
			काष्ठा flow_dissector_key_ports tp_min;
			काष्ठा flow_dissector_key_ports tp_max;
		पूर्ण;
	पूर्ण tp_range;
	काष्ठा flow_dissector_key_ct ct;
	काष्ठा flow_dissector_key_hash hash;
पूर्ण __aligned(BITS_PER_LONG / 8); /* Ensure that we can करो comparisons as दीर्घs. */

काष्ठा fl_flow_mask_range अणु
	अचिन्हित लघु पूर्णांक start;
	अचिन्हित लघु पूर्णांक end;
पूर्ण;

काष्ठा fl_flow_mask अणु
	काष्ठा fl_flow_key key;
	काष्ठा fl_flow_mask_range range;
	u32 flags;
	काष्ठा rhash_head ht_node;
	काष्ठा rhashtable ht;
	काष्ठा rhashtable_params filter_ht_params;
	काष्ठा flow_dissector dissector;
	काष्ठा list_head filters;
	काष्ठा rcu_work rwork;
	काष्ठा list_head list;
	refcount_t refcnt;
पूर्ण;

काष्ठा fl_flow_पंचांगplt अणु
	काष्ठा fl_flow_key dummy_key;
	काष्ठा fl_flow_key mask;
	काष्ठा flow_dissector dissector;
	काष्ठा tcf_chain *chain;
पूर्ण;

काष्ठा cls_fl_head अणु
	काष्ठा rhashtable ht;
	spinlock_t masks_lock; /* Protect masks list */
	काष्ठा list_head masks;
	काष्ठा list_head hw_filters;
	काष्ठा rcu_work rwork;
	काष्ठा idr handle_idr;
पूर्ण;

काष्ठा cls_fl_filter अणु
	काष्ठा fl_flow_mask *mask;
	काष्ठा rhash_head ht_node;
	काष्ठा fl_flow_key mkey;
	काष्ठा tcf_exts exts;
	काष्ठा tcf_result res;
	काष्ठा fl_flow_key key;
	काष्ठा list_head list;
	काष्ठा list_head hw_list;
	u32 handle;
	u32 flags;
	u32 in_hw_count;
	काष्ठा rcu_work rwork;
	काष्ठा net_device *hw_dev;
	/* Flower classअगरier is unlocked, which means that its reference counter
	 * can be changed concurrently without any kind of बाह्यal
	 * synchronization. Use atomic reference counter to be concurrency-safe.
	 */
	refcount_t refcnt;
	bool deleted;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mask_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा fl_flow_mask, key),
	.key_len = माप(काष्ठा fl_flow_key),
	.head_offset = दुरत्व(काष्ठा fl_flow_mask, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल अचिन्हित लघु पूर्णांक fl_mask_range(स्थिर काष्ठा fl_flow_mask *mask)
अणु
	वापस mask->range.end - mask->range.start;
पूर्ण

अटल व्योम fl_mask_update_range(काष्ठा fl_flow_mask *mask)
अणु
	स्थिर u8 *bytes = (स्थिर u8 *) &mask->key;
	माप_प्रकार size = माप(mask->key);
	माप_प्रकार i, first = 0, last;

	क्रम (i = 0; i < size; i++) अणु
		अगर (bytes[i]) अणु
			first = i;
			अवरोध;
		पूर्ण
	पूर्ण
	last = first;
	क्रम (i = size - 1; i != first; i--) अणु
		अगर (bytes[i]) अणु
			last = i;
			अवरोध;
		पूर्ण
	पूर्ण
	mask->range.start = roundकरोwn(first, माप(दीर्घ));
	mask->range.end = roundup(last + 1, माप(दीर्घ));
पूर्ण

अटल व्योम *fl_key_get_start(काष्ठा fl_flow_key *key,
			      स्थिर काष्ठा fl_flow_mask *mask)
अणु
	वापस (u8 *) key + mask->range.start;
पूर्ण

अटल व्योम fl_set_masked_key(काष्ठा fl_flow_key *mkey, काष्ठा fl_flow_key *key,
			      काष्ठा fl_flow_mask *mask)
अणु
	स्थिर दीर्घ *lkey = fl_key_get_start(key, mask);
	स्थिर दीर्घ *lmask = fl_key_get_start(&mask->key, mask);
	दीर्घ *lmkey = fl_key_get_start(mkey, mask);
	पूर्णांक i;

	क्रम (i = 0; i < fl_mask_range(mask); i += माप(दीर्घ))
		*lmkey++ = *lkey++ & *lmask++;
पूर्ण

अटल bool fl_mask_fits_पंचांगplt(काष्ठा fl_flow_पंचांगplt *पंचांगplt,
			       काष्ठा fl_flow_mask *mask)
अणु
	स्थिर दीर्घ *lmask = fl_key_get_start(&mask->key, mask);
	स्थिर दीर्घ *lपंचांगplt;
	पूर्णांक i;

	अगर (!पंचांगplt)
		वापस true;
	lपंचांगplt = fl_key_get_start(&पंचांगplt->mask, mask);
	क्रम (i = 0; i < fl_mask_range(mask); i += माप(दीर्घ)) अणु
		अगर (~*lपंचांगplt++ & *lmask++)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम fl_clear_masked_range(काष्ठा fl_flow_key *key,
				  काष्ठा fl_flow_mask *mask)
अणु
	स_रखो(fl_key_get_start(key, mask), 0, fl_mask_range(mask));
पूर्ण

अटल bool fl_range_port_dst_cmp(काष्ठा cls_fl_filter *filter,
				  काष्ठा fl_flow_key *key,
				  काष्ठा fl_flow_key *mkey)
अणु
	u16 min_mask, max_mask, min_val, max_val;

	min_mask = ntohs(filter->mask->key.tp_range.tp_min.dst);
	max_mask = ntohs(filter->mask->key.tp_range.tp_max.dst);
	min_val = ntohs(filter->key.tp_range.tp_min.dst);
	max_val = ntohs(filter->key.tp_range.tp_max.dst);

	अगर (min_mask && max_mask) अणु
		अगर (ntohs(key->tp_range.tp.dst) < min_val ||
		    ntohs(key->tp_range.tp.dst) > max_val)
			वापस false;

		/* skb करोes not have min and max values */
		mkey->tp_range.tp_min.dst = filter->mkey.tp_range.tp_min.dst;
		mkey->tp_range.tp_max.dst = filter->mkey.tp_range.tp_max.dst;
	पूर्ण
	वापस true;
पूर्ण

अटल bool fl_range_port_src_cmp(काष्ठा cls_fl_filter *filter,
				  काष्ठा fl_flow_key *key,
				  काष्ठा fl_flow_key *mkey)
अणु
	u16 min_mask, max_mask, min_val, max_val;

	min_mask = ntohs(filter->mask->key.tp_range.tp_min.src);
	max_mask = ntohs(filter->mask->key.tp_range.tp_max.src);
	min_val = ntohs(filter->key.tp_range.tp_min.src);
	max_val = ntohs(filter->key.tp_range.tp_max.src);

	अगर (min_mask && max_mask) अणु
		अगर (ntohs(key->tp_range.tp.src) < min_val ||
		    ntohs(key->tp_range.tp.src) > max_val)
			वापस false;

		/* skb करोes not have min and max values */
		mkey->tp_range.tp_min.src = filter->mkey.tp_range.tp_min.src;
		mkey->tp_range.tp_max.src = filter->mkey.tp_range.tp_max.src;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा cls_fl_filter *__fl_lookup(काष्ठा fl_flow_mask *mask,
					 काष्ठा fl_flow_key *mkey)
अणु
	वापस rhashtable_lookup_fast(&mask->ht, fl_key_get_start(mkey, mask),
				      mask->filter_ht_params);
पूर्ण

अटल काष्ठा cls_fl_filter *fl_lookup_range(काष्ठा fl_flow_mask *mask,
					     काष्ठा fl_flow_key *mkey,
					     काष्ठा fl_flow_key *key)
अणु
	काष्ठा cls_fl_filter *filter, *f;

	list_क्रम_each_entry_rcu(filter, &mask->filters, list) अणु
		अगर (!fl_range_port_dst_cmp(filter, key, mkey))
			जारी;

		अगर (!fl_range_port_src_cmp(filter, key, mkey))
			जारी;

		f = __fl_lookup(mask, mkey);
		अगर (f)
			वापस f;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल noअंतरभूत_क्रम_stack
काष्ठा cls_fl_filter *fl_mask_lookup(काष्ठा fl_flow_mask *mask, काष्ठा fl_flow_key *key)
अणु
	काष्ठा fl_flow_key mkey;

	fl_set_masked_key(&mkey, key, mask);
	अगर ((mask->flags & TCA_FLOWER_MASK_FLAGS_RANGE))
		वापस fl_lookup_range(mask, &mkey, key);

	वापस __fl_lookup(mask, &mkey);
पूर्ण

अटल u16 fl_ct_info_to_flower_map[] = अणु
	[IP_CT_ESTABLISHED] =		TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
					TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED,
	[IP_CT_RELATED] =		TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
					TCA_FLOWER_KEY_CT_FLAGS_RELATED,
	[IP_CT_ESTABLISHED_REPLY] =	TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
					TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED |
					TCA_FLOWER_KEY_CT_FLAGS_REPLY,
	[IP_CT_RELATED_REPLY] =		TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
					TCA_FLOWER_KEY_CT_FLAGS_RELATED |
					TCA_FLOWER_KEY_CT_FLAGS_REPLY,
	[IP_CT_NEW] =			TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
					TCA_FLOWER_KEY_CT_FLAGS_NEW,
पूर्ण;

अटल पूर्णांक fl_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
		       काष्ठा tcf_result *res)
अणु
	काष्ठा cls_fl_head *head = rcu_dereference_bh(tp->root);
	bool post_ct = qdisc_skb_cb(skb)->post_ct;
	काष्ठा fl_flow_key skb_key;
	काष्ठा fl_flow_mask *mask;
	काष्ठा cls_fl_filter *f;

	list_क्रम_each_entry_rcu(mask, &head->masks, list) अणु
		flow_dissector_init_keys(&skb_key.control, &skb_key.basic);
		fl_clear_masked_range(&skb_key, mask);

		skb_flow_dissect_meta(skb, &mask->dissector, &skb_key);
		/* skb_flow_dissect() करोes not set n_proto in हाल an unknown
		 * protocol, so करो it rather here.
		 */
		skb_key.basic.n_proto = skb_protocol(skb, false);
		skb_flow_dissect_tunnel_info(skb, &mask->dissector, &skb_key);
		skb_flow_dissect_ct(skb, &mask->dissector, &skb_key,
				    fl_ct_info_to_flower_map,
				    ARRAY_SIZE(fl_ct_info_to_flower_map),
				    post_ct);
		skb_flow_dissect_hash(skb, &mask->dissector, &skb_key);
		skb_flow_dissect(skb, &mask->dissector, &skb_key, 0);

		f = fl_mask_lookup(mask, &skb_key);
		अगर (f && !tc_skip_sw(f->flags)) अणु
			*res = f->res;
			वापस tcf_exts_exec(skb, &f->exts, res);
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक fl_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा cls_fl_head *head;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (!head)
		वापस -ENOBUFS;

	spin_lock_init(&head->masks_lock);
	INIT_LIST_HEAD_RCU(&head->masks);
	INIT_LIST_HEAD(&head->hw_filters);
	rcu_assign_poपूर्णांकer(tp->root, head);
	idr_init(&head->handle_idr);

	वापस rhashtable_init(&head->ht, &mask_ht_params);
पूर्ण

अटल व्योम fl_mask_मुक्त(काष्ठा fl_flow_mask *mask, bool mask_init_करोne)
अणु
	/* temporary masks करोn't have their filters list and ht initialized */
	अगर (mask_init_करोne) अणु
		WARN_ON(!list_empty(&mask->filters));
		rhashtable_destroy(&mask->ht);
	पूर्ण
	kमुक्त(mask);
पूर्ण

अटल व्योम fl_mask_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fl_flow_mask *mask = container_of(to_rcu_work(work),
						 काष्ठा fl_flow_mask, rwork);

	fl_mask_मुक्त(mask, true);
पूर्ण

अटल व्योम fl_uninit_mask_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fl_flow_mask *mask = container_of(to_rcu_work(work),
						 काष्ठा fl_flow_mask, rwork);

	fl_mask_मुक्त(mask, false);
पूर्ण

अटल bool fl_mask_put(काष्ठा cls_fl_head *head, काष्ठा fl_flow_mask *mask)
अणु
	अगर (!refcount_dec_and_test(&mask->refcnt))
		वापस false;

	rhashtable_हटाओ_fast(&head->ht, &mask->ht_node, mask_ht_params);

	spin_lock(&head->masks_lock);
	list_del_rcu(&mask->list);
	spin_unlock(&head->masks_lock);

	tcf_queue_work(&mask->rwork, fl_mask_मुक्त_work);

	वापस true;
पूर्ण

अटल काष्ठा cls_fl_head *fl_head_dereference(काष्ठा tcf_proto *tp)
अणु
	/* Flower classअगरier only changes root poपूर्णांकer during init and destroy.
	 * Users must obtain reference to tcf_proto instance beक्रमe calling its
	 * API, so tp->root poपूर्णांकer is रक्षित from concurrent call to
	 * fl_destroy() by reference counting.
	 */
	वापस rcu_dereference_raw(tp->root);
पूर्ण

अटल व्योम __fl_destroy_filter(काष्ठा cls_fl_filter *f)
अणु
	tcf_exts_destroy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kमुक्त(f);
पूर्ण

अटल व्योम fl_destroy_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cls_fl_filter *f = container_of(to_rcu_work(work),
					काष्ठा cls_fl_filter, rwork);

	__fl_destroy_filter(f);
पूर्ण

अटल व्योम fl_hw_destroy_filter(काष्ठा tcf_proto *tp, काष्ठा cls_fl_filter *f,
				 bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = FLOW_CLS_DESTROY;
	cls_flower.cookie = (अचिन्हित दीर्घ) f;

	tc_setup_cb_destroy(block, tp, TC_SETUP_CLSFLOWER, &cls_flower, false,
			    &f->flags, &f->in_hw_count, rtnl_held);

पूर्ण

अटल पूर्णांक fl_hw_replace_filter(काष्ठा tcf_proto *tp,
				काष्ठा cls_fl_filter *f, bool rtnl_held,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;
	bool skip_sw = tc_skip_sw(f->flags);
	पूर्णांक err = 0;

	cls_flower.rule = flow_rule_alloc(tcf_exts_num_actions(&f->exts));
	अगर (!cls_flower.rule)
		वापस -ENOMEM;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = FLOW_CLS_REPLACE;
	cls_flower.cookie = (अचिन्हित दीर्घ) f;
	cls_flower.rule->match.dissector = &f->mask->dissector;
	cls_flower.rule->match.mask = &f->mask->key;
	cls_flower.rule->match.key = &f->mkey;
	cls_flower.classid = f->res.classid;

	err = tc_setup_flow_action(&cls_flower.rule->action, &f->exts);
	अगर (err) अणु
		kमुक्त(cls_flower.rule);
		अगर (skip_sw) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
			वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	err = tc_setup_cb_add(block, tp, TC_SETUP_CLSFLOWER, &cls_flower,
			      skip_sw, &f->flags, &f->in_hw_count, rtnl_held);
	tc_cleanup_flow_action(&cls_flower.rule->action);
	kमुक्त(cls_flower.rule);

	अगर (err) अणु
		fl_hw_destroy_filter(tp, f, rtnl_held, शून्य);
		वापस err;
	पूर्ण

	अगर (skip_sw && !(f->flags & TCA_CLS_FLAGS_IN_HW))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम fl_hw_update_stats(काष्ठा tcf_proto *tp, काष्ठा cls_fl_filter *f,
			       bool rtnl_held)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, शून्य);
	cls_flower.command = FLOW_CLS_STATS;
	cls_flower.cookie = (अचिन्हित दीर्घ) f;
	cls_flower.classid = f->res.classid;

	tc_setup_cb_call(block, TC_SETUP_CLSFLOWER, &cls_flower, false,
			 rtnl_held);

	tcf_exts_stats_update(&f->exts, cls_flower.stats.bytes,
			      cls_flower.stats.pkts,
			      cls_flower.stats.drops,
			      cls_flower.stats.lastused,
			      cls_flower.stats.used_hw_stats,
			      cls_flower.stats.used_hw_stats_valid);
पूर्ण

अटल व्योम __fl_put(काष्ठा cls_fl_filter *f)
अणु
	अगर (!refcount_dec_and_test(&f->refcnt))
		वापस;

	अगर (tcf_exts_get_net(&f->exts))
		tcf_queue_work(&f->rwork, fl_destroy_filter_work);
	अन्यथा
		__fl_destroy_filter(f);
पूर्ण

अटल काष्ठा cls_fl_filter *__fl_get(काष्ठा cls_fl_head *head, u32 handle)
अणु
	काष्ठा cls_fl_filter *f;

	rcu_पढ़ो_lock();
	f = idr_find(&head->handle_idr, handle);
	अगर (f && !refcount_inc_not_zero(&f->refcnt))
		f = शून्य;
	rcu_पढ़ो_unlock();

	वापस f;
पूर्ण

अटल पूर्णांक __fl_delete(काष्ठा tcf_proto *tp, काष्ठा cls_fl_filter *f,
		       bool *last, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);

	*last = false;

	spin_lock(&tp->lock);
	अगर (f->deleted) अणु
		spin_unlock(&tp->lock);
		वापस -ENOENT;
	पूर्ण

	f->deleted = true;
	rhashtable_हटाओ_fast(&f->mask->ht, &f->ht_node,
			       f->mask->filter_ht_params);
	idr_हटाओ(&head->handle_idr, f->handle);
	list_del_rcu(&f->list);
	spin_unlock(&tp->lock);

	*last = fl_mask_put(head, f->mask);
	अगर (!tc_skip_hw(f->flags))
		fl_hw_destroy_filter(tp, f, rtnl_held, extack);
	tcf_unbind_filter(tp, &f->res);
	__fl_put(f);

	वापस 0;
पूर्ण

अटल व्योम fl_destroy_sleepable(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cls_fl_head *head = container_of(to_rcu_work(work),
						काष्ठा cls_fl_head,
						rwork);

	rhashtable_destroy(&head->ht);
	kमुक्त(head);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम fl_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);
	काष्ठा fl_flow_mask *mask, *next_mask;
	काष्ठा cls_fl_filter *f, *next;
	bool last;

	list_क्रम_each_entry_safe(mask, next_mask, &head->masks, list) अणु
		list_क्रम_each_entry_safe(f, next, &mask->filters, list) अणु
			__fl_delete(tp, f, &last, rtnl_held, extack);
			अगर (last)
				अवरोध;
		पूर्ण
	पूर्ण
	idr_destroy(&head->handle_idr);

	__module_get(THIS_MODULE);
	tcf_queue_work(&head->rwork, fl_destroy_sleepable);
पूर्ण

अटल व्योम fl_put(काष्ठा tcf_proto *tp, व्योम *arg)
अणु
	काष्ठा cls_fl_filter *f = arg;

	__fl_put(f);
पूर्ण

अटल व्योम *fl_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);

	वापस __fl_get(head, handle);
पूर्ण

अटल स्थिर काष्ठा nla_policy fl_policy[TCA_FLOWER_MAX + 1] = अणु
	[TCA_FLOWER_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TCA_FLOWER_CLASSID]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_INDEV]		= अणु .type = NLA_STRING,
					    .len = IFNAMSIZ पूर्ण,
	[TCA_FLOWER_KEY_ETH_DST]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ETH_DST_MASK]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ETH_SRC]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ETH_SRC_MASK]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ETH_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_IP_PROTO]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_IPV4_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_IPV4_SRC_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_IPV4_DST]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_IPV4_DST_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_IPV6_SRC]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_IPV6_SRC_MASK]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_IPV6_DST]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_IPV6_DST_MASK]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_TCP_SRC]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_TCP_DST]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_UDP_SRC]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_UDP_DST]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_VLAN_ID]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_VLAN_PRIO]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_VLAN_ETH_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_KEY_ID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV4_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV4_DST]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV4_DST_MASK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV6_SRC]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK] = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV6_DST]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_ENC_IPV6_DST_MASK] = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_FLOWER_KEY_TCP_SRC_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_TCP_DST_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_UDP_SRC_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_UDP_DST_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_SCTP_SRC_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_SCTP_DST_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_SCTP_SRC]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_SCTP_DST]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_UDP_SRC_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_UDP_DST_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_FLAGS_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV4_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV4_TYPE_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV4_CODE]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV4_CODE_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV6_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV6_TYPE_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV6_CODE]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ICMPV6_CODE_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ARP_SIP]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ARP_SIP_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ARP_TIP]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ARP_TIP_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ARP_OP]		= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ARP_OP_MASK]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ARP_SHA]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ARP_SHA_MASK]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ARP_THA]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_ARP_THA_MASK]	= अणु .len = ETH_ALEN पूर्ण,
	[TCA_FLOWER_KEY_MPLS_TTL]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_BOS]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_TC]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_LABEL]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_OPTS]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOWER_KEY_TCP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_TCP_FLAGS_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_IP_TOS]		= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_IP_TOS_MASK]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_IP_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_IP_TTL_MASK]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_CVLAN_ID]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_CVLAN_PRIO]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_CVLAN_ETH_TYPE]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IP_TOS]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IP_TOS_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IP_TTL]	 = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_IP_TTL_MASK] = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPTS]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPTS_MASK]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOWER_KEY_CT_STATE]	=
		NLA_POLICY_MASK(NLA_U16, TCA_FLOWER_KEY_CT_FLAGS_MASK),
	[TCA_FLOWER_KEY_CT_STATE_MASK]	=
		NLA_POLICY_MASK(NLA_U16, TCA_FLOWER_KEY_CT_FLAGS_MASK),
	[TCA_FLOWER_KEY_CT_ZONE]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_CT_ZONE_MASK]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_CT_MARK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_CT_MARK_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_CT_LABELS]	= अणु .type = NLA_BINARY,
					    .len = 128 / BITS_PER_BYTE पूर्ण,
	[TCA_FLOWER_KEY_CT_LABELS_MASK]	= अणु .type = NLA_BINARY,
					    .len = 128 / BITS_PER_BYTE पूर्ण,
	[TCA_FLOWER_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_HASH]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_HASH_MASK]	= अणु .type = NLA_U32 पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा nla_policy
enc_opts_policy[TCA_FLOWER_KEY_ENC_OPTS_MAX + 1] = अणु
	[TCA_FLOWER_KEY_ENC_OPTS_UNSPEC]        = अणु
		.strict_start_type = TCA_FLOWER_KEY_ENC_OPTS_VXLAN पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPTS_GENEVE]        = अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPTS_VXLAN]         = अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPTS_ERSPAN]        = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
geneve_opt_policy[TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX + 1] = अणु
	[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS]      = अणु .type = NLA_U16 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE]       = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA]       = अणु .type = NLA_BINARY,
						       .len = 128 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
vxlan_opt_policy[TCA_FLOWER_KEY_ENC_OPT_VXLAN_MAX + 1] = अणु
	[TCA_FLOWER_KEY_ENC_OPT_VXLAN_GBP]         = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
erspan_opt_policy[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_MAX + 1] = अणु
	[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_VER]        = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_INDEX]      = अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_सूची]        = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_HWID]       = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
mpls_stack_entry_policy[TCA_FLOWER_KEY_MPLS_OPT_LSE_MAX + 1] = अणु
	[TCA_FLOWER_KEY_MPLS_OPT_LSE_DEPTH]    = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_OPT_LSE_TTL]      = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_OPT_LSE_BOS]      = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_OPT_LSE_TC]       = अणु .type = NLA_U8 पूर्ण,
	[TCA_FLOWER_KEY_MPLS_OPT_LSE_LABEL]    = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम fl_set_key_val(काष्ठा nlattr **tb,
			   व्योम *val, पूर्णांक val_type,
			   व्योम *mask, पूर्णांक mask_type, पूर्णांक len)
अणु
	अगर (!tb[val_type])
		वापस;
	nla_स_नकल(val, tb[val_type], len);
	अगर (mask_type == TCA_FLOWER_UNSPEC || !tb[mask_type])
		स_रखो(mask, 0xff, len);
	अन्यथा
		nla_स_नकल(mask, tb[mask_type], len);
पूर्ण

अटल पूर्णांक fl_set_key_port_range(काष्ठा nlattr **tb, काष्ठा fl_flow_key *key,
				 काष्ठा fl_flow_key *mask,
				 काष्ठा netlink_ext_ack *extack)
अणु
	fl_set_key_val(tb, &key->tp_range.tp_min.dst,
		       TCA_FLOWER_KEY_PORT_DST_MIN, &mask->tp_range.tp_min.dst,
		       TCA_FLOWER_UNSPEC, माप(key->tp_range.tp_min.dst));
	fl_set_key_val(tb, &key->tp_range.tp_max.dst,
		       TCA_FLOWER_KEY_PORT_DST_MAX, &mask->tp_range.tp_max.dst,
		       TCA_FLOWER_UNSPEC, माप(key->tp_range.tp_max.dst));
	fl_set_key_val(tb, &key->tp_range.tp_min.src,
		       TCA_FLOWER_KEY_PORT_SRC_MIN, &mask->tp_range.tp_min.src,
		       TCA_FLOWER_UNSPEC, माप(key->tp_range.tp_min.src));
	fl_set_key_val(tb, &key->tp_range.tp_max.src,
		       TCA_FLOWER_KEY_PORT_SRC_MAX, &mask->tp_range.tp_max.src,
		       TCA_FLOWER_UNSPEC, माप(key->tp_range.tp_max.src));

	अगर (mask->tp_range.tp_min.dst && mask->tp_range.tp_max.dst &&
	    ntohs(key->tp_range.tp_max.dst) <=
	    ntohs(key->tp_range.tp_min.dst)) अणु
		NL_SET_ERR_MSG_ATTR(extack,
				    tb[TCA_FLOWER_KEY_PORT_DST_MIN],
				    "Invalid destination port range (min must be strictly smaller than max)");
		वापस -EINVAL;
	पूर्ण
	अगर (mask->tp_range.tp_min.src && mask->tp_range.tp_max.src &&
	    ntohs(key->tp_range.tp_max.src) <=
	    ntohs(key->tp_range.tp_min.src)) अणु
		NL_SET_ERR_MSG_ATTR(extack,
				    tb[TCA_FLOWER_KEY_PORT_SRC_MIN],
				    "Invalid source port range (min must be strictly smaller than max)");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_set_key_mpls_lse(स्थिर काष्ठा nlattr *nla_lse,
			       काष्ठा flow_dissector_key_mpls *key_val,
			       काष्ठा flow_dissector_key_mpls *key_mask,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_MAX + 1];
	काष्ठा flow_dissector_mpls_lse *lse_mask;
	काष्ठा flow_dissector_mpls_lse *lse_val;
	u8 lse_index;
	u8 depth;
	पूर्णांक err;

	err = nla_parse_nested(tb, TCA_FLOWER_KEY_MPLS_OPT_LSE_MAX, nla_lse,
			       mpls_stack_entry_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_DEPTH]) अणु
		NL_SET_ERR_MSG(extack, "Missing MPLS option \"depth\"");
		वापस -EINVAL;
	पूर्ण

	depth = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_DEPTH]);

	/* LSE depth starts at 1, क्रम consistency with terminology used by
	 * RFC 3031 (section 3.9), where depth 0 refers to unlabeled packets.
	 */
	अगर (depth < 1 || depth > FLOW_DIS_MPLS_MAX) अणु
		NL_SET_ERR_MSG_ATTR(extack,
				    tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_DEPTH],
				    "Invalid MPLS depth");
		वापस -EINVAL;
	पूर्ण
	lse_index = depth - 1;

	dissector_set_mpls_lse(key_val, lse_index);
	dissector_set_mpls_lse(key_mask, lse_index);

	lse_val = &key_val->ls[lse_index];
	lse_mask = &key_mask->ls[lse_index];

	अगर (tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_TTL]) अणु
		lse_val->mpls_ttl = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_TTL]);
		lse_mask->mpls_ttl = MPLS_TTL_MASK;
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_BOS]) अणु
		u8 bos = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_BOS]);

		अगर (bos & ~MPLS_BOS_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_BOS],
					    "Bottom Of Stack (BOS) must be 0 or 1");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_bos = bos;
		lse_mask->mpls_bos = MPLS_BOS_MASK;
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_TC]) अणु
		u8 tc = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_TC]);

		अगर (tc & ~MPLS_TC_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_TC],
					    "Traffic Class (TC) must be between 0 and 7");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_tc = tc;
		lse_mask->mpls_tc = MPLS_TC_MASK;
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_LABEL]) अणु
		u32 label = nla_get_u32(tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_LABEL]);

		अगर (label & ~MPLS_LABEL_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_OPT_LSE_LABEL],
					    "Label must be between 0 and 1048575");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_label = label;
		lse_mask->mpls_label = MPLS_LABEL_MASK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_set_key_mpls_opts(स्थिर काष्ठा nlattr *nla_mpls_opts,
				काष्ठा flow_dissector_key_mpls *key_val,
				काष्ठा flow_dissector_key_mpls *key_mask,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *nla_lse;
	पूर्णांक rem;
	पूर्णांक err;

	अगर (!(nla_mpls_opts->nla_type & NLA_F_NESTED)) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla_mpls_opts,
				    "NLA_F_NESTED is missing");
		वापस -EINVAL;
	पूर्ण

	nla_क्रम_each_nested(nla_lse, nla_mpls_opts, rem) अणु
		अगर (nla_type(nla_lse) != TCA_FLOWER_KEY_MPLS_OPTS_LSE) अणु
			NL_SET_ERR_MSG_ATTR(extack, nla_lse,
					    "Invalid MPLS option type");
			वापस -EINVAL;
		पूर्ण

		err = fl_set_key_mpls_lse(nla_lse, key_val, key_mask, extack);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (rem) अणु
		NL_SET_ERR_MSG(extack,
			       "Bytes leftover after parsing MPLS options");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_set_key_mpls(काष्ठा nlattr **tb,
			   काष्ठा flow_dissector_key_mpls *key_val,
			   काष्ठा flow_dissector_key_mpls *key_mask,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_dissector_mpls_lse *lse_mask;
	काष्ठा flow_dissector_mpls_lse *lse_val;

	अगर (tb[TCA_FLOWER_KEY_MPLS_OPTS]) अणु
		अगर (tb[TCA_FLOWER_KEY_MPLS_TTL] ||
		    tb[TCA_FLOWER_KEY_MPLS_BOS] ||
		    tb[TCA_FLOWER_KEY_MPLS_TC] ||
		    tb[TCA_FLOWER_KEY_MPLS_LABEL]) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_OPTS],
					    "MPLS label, Traffic Class, Bottom Of Stack and Time To Live must be encapsulated in the MPLS options attribute");
			वापस -EBADMSG;
		पूर्ण

		वापस fl_set_key_mpls_opts(tb[TCA_FLOWER_KEY_MPLS_OPTS],
					    key_val, key_mask, extack);
	पूर्ण

	lse_val = &key_val->ls[0];
	lse_mask = &key_mask->ls[0];

	अगर (tb[TCA_FLOWER_KEY_MPLS_TTL]) अणु
		lse_val->mpls_ttl = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_TTL]);
		lse_mask->mpls_ttl = MPLS_TTL_MASK;
		dissector_set_mpls_lse(key_val, 0);
		dissector_set_mpls_lse(key_mask, 0);
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_BOS]) अणु
		u8 bos = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_BOS]);

		अगर (bos & ~MPLS_BOS_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_BOS],
					    "Bottom Of Stack (BOS) must be 0 or 1");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_bos = bos;
		lse_mask->mpls_bos = MPLS_BOS_MASK;
		dissector_set_mpls_lse(key_val, 0);
		dissector_set_mpls_lse(key_mask, 0);
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_TC]) अणु
		u8 tc = nla_get_u8(tb[TCA_FLOWER_KEY_MPLS_TC]);

		अगर (tc & ~MPLS_TC_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_TC],
					    "Traffic Class (TC) must be between 0 and 7");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_tc = tc;
		lse_mask->mpls_tc = MPLS_TC_MASK;
		dissector_set_mpls_lse(key_val, 0);
		dissector_set_mpls_lse(key_mask, 0);
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_MPLS_LABEL]) अणु
		u32 label = nla_get_u32(tb[TCA_FLOWER_KEY_MPLS_LABEL]);

		अगर (label & ~MPLS_LABEL_MASK) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[TCA_FLOWER_KEY_MPLS_LABEL],
					    "Label must be between 0 and 1048575");
			वापस -EINVAL;
		पूर्ण
		lse_val->mpls_label = label;
		lse_mask->mpls_label = MPLS_LABEL_MASK;
		dissector_set_mpls_lse(key_val, 0);
		dissector_set_mpls_lse(key_mask, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fl_set_key_vlan(काष्ठा nlattr **tb,
			    __be16 ethertype,
			    पूर्णांक vlan_id_key, पूर्णांक vlan_prio_key,
			    काष्ठा flow_dissector_key_vlan *key_val,
			    काष्ठा flow_dissector_key_vlan *key_mask)
अणु
#घोषणा VLAN_PRIORITY_MASK	0x7

	अगर (tb[vlan_id_key]) अणु
		key_val->vlan_id =
			nla_get_u16(tb[vlan_id_key]) & VLAN_VID_MASK;
		key_mask->vlan_id = VLAN_VID_MASK;
	पूर्ण
	अगर (tb[vlan_prio_key]) अणु
		key_val->vlan_priority =
			nla_get_u8(tb[vlan_prio_key]) &
			VLAN_PRIORITY_MASK;
		key_mask->vlan_priority = VLAN_PRIORITY_MASK;
	पूर्ण
	key_val->vlan_tpid = ethertype;
	key_mask->vlan_tpid = cpu_to_be16(~0);
पूर्ण

अटल व्योम fl_set_key_flag(u32 flower_key, u32 flower_mask,
			    u32 *dissector_key, u32 *dissector_mask,
			    u32 flower_flag_bit, u32 dissector_flag_bit)
अणु
	अगर (flower_mask & flower_flag_bit) अणु
		*dissector_mask |= dissector_flag_bit;
		अगर (flower_key & flower_flag_bit)
			*dissector_key |= dissector_flag_bit;
	पूर्ण
पूर्ण

अटल पूर्णांक fl_set_key_flags(काष्ठा nlattr **tb, u32 *flags_key,
			    u32 *flags_mask, काष्ठा netlink_ext_ack *extack)
अणु
	u32 key, mask;

	/* mask is mandatory क्रम flags */
	अगर (!tb[TCA_FLOWER_KEY_FLAGS_MASK]) अणु
		NL_SET_ERR_MSG(extack, "Missing flags mask");
		वापस -EINVAL;
	पूर्ण

	key = be32_to_cpu(nla_get_be32(tb[TCA_FLOWER_KEY_FLAGS]));
	mask = be32_to_cpu(nla_get_be32(tb[TCA_FLOWER_KEY_FLAGS_MASK]));

	*flags_key  = 0;
	*flags_mask = 0;

	fl_set_key_flag(key, mask, flags_key, flags_mask,
			TCA_FLOWER_KEY_FLAGS_IS_FRAGMENT, FLOW_DIS_IS_FRAGMENT);
	fl_set_key_flag(key, mask, flags_key, flags_mask,
			TCA_FLOWER_KEY_FLAGS_FRAG_IS_FIRST,
			FLOW_DIS_FIRST_FRAG);

	वापस 0;
पूर्ण

अटल व्योम fl_set_key_ip(काष्ठा nlattr **tb, bool encap,
			  काष्ठा flow_dissector_key_ip *key,
			  काष्ठा flow_dissector_key_ip *mask)
अणु
	पूर्णांक tos_key = encap ? TCA_FLOWER_KEY_ENC_IP_TOS : TCA_FLOWER_KEY_IP_TOS;
	पूर्णांक ttl_key = encap ? TCA_FLOWER_KEY_ENC_IP_TTL : TCA_FLOWER_KEY_IP_TTL;
	पूर्णांक tos_mask = encap ? TCA_FLOWER_KEY_ENC_IP_TOS_MASK : TCA_FLOWER_KEY_IP_TOS_MASK;
	पूर्णांक ttl_mask = encap ? TCA_FLOWER_KEY_ENC_IP_TTL_MASK : TCA_FLOWER_KEY_IP_TTL_MASK;

	fl_set_key_val(tb, &key->tos, tos_key, &mask->tos, tos_mask, माप(key->tos));
	fl_set_key_val(tb, &key->ttl, ttl_key, &mask->ttl, ttl_mask, माप(key->ttl));
पूर्ण

अटल पूर्णांक fl_set_geneve_opt(स्थिर काष्ठा nlattr *nla, काष्ठा fl_flow_key *key,
			     पूर्णांक depth, पूर्णांक option_len,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX + 1];
	काष्ठा nlattr *class = शून्य, *type = शून्य, *data = शून्य;
	काष्ठा geneve_opt *opt;
	पूर्णांक err, data_len = 0;

	अगर (option_len > माप(काष्ठा geneve_opt))
		data_len = option_len - माप(काष्ठा geneve_opt);

	opt = (काष्ठा geneve_opt *)&key->enc_opts.data[key->enc_opts.len];
	स_रखो(opt, 0xff, option_len);
	opt->length = data_len / 4;
	opt->r1 = 0;
	opt->r2 = 0;
	opt->r3 = 0;

	/* If no mask has been proभागed we assume an exact match. */
	अगर (!depth)
		वापस माप(काष्ठा geneve_opt) + data_len;

	अगर (nla_type(nla) != TCA_FLOWER_KEY_ENC_OPTS_GENEVE) अणु
		NL_SET_ERR_MSG(extack, "Non-geneve option type for mask");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb,
					  TCA_FLOWER_KEY_ENC_OPT_GENEVE_MAX,
					  nla, geneve_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	/* We are not allowed to omit any of CLASS, TYPE or DATA
	 * fields from the key.
	 */
	अगर (!option_len &&
	    (!tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS] ||
	     !tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE] ||
	     !tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA])) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key geneve option class, type or data");
		वापस -EINVAL;
	पूर्ण

	/* Omitting any of CLASS, TYPE or DATA fields is allowed
	 * क्रम the mask.
	 */
	अगर (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA]) अणु
		पूर्णांक new_len = key->enc_opts.len;

		data = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA];
		data_len = nla_len(data);
		अगर (data_len < 4) अणु
			NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is less than 4 bytes long");
			वापस -दुस्फल;
		पूर्ण
		अगर (data_len % 4) अणु
			NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is not a multiple of 4 bytes long");
			वापस -दुस्फल;
		पूर्ण

		new_len += माप(काष्ठा geneve_opt) + data_len;
		BUILD_BUG_ON(FLOW_DIS_TUN_OPTS_MAX != IP_TUNNEL_OPTS_MAX);
		अगर (new_len > FLOW_DIS_TUN_OPTS_MAX) अणु
			NL_SET_ERR_MSG(extack, "Tunnel options exceeds max size");
			वापस -दुस्फल;
		पूर्ण
		opt->length = data_len / 4;
		स_नकल(opt->opt_data, nla_data(data), data_len);
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS]) अणु
		class = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS];
		opt->opt_class = nla_get_be16(class);
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE]) अणु
		type = tb[TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE];
		opt->type = nla_get_u8(type);
	पूर्ण

	वापस माप(काष्ठा geneve_opt) + data_len;
पूर्ण

अटल पूर्णांक fl_set_vxlan_opt(स्थिर काष्ठा nlattr *nla, काष्ठा fl_flow_key *key,
			    पूर्णांक depth, पूर्णांक option_len,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_FLOWER_KEY_ENC_OPT_VXLAN_MAX + 1];
	काष्ठा vxlan_metadata *md;
	पूर्णांक err;

	md = (काष्ठा vxlan_metadata *)&key->enc_opts.data[key->enc_opts.len];
	स_रखो(md, 0xff, माप(*md));

	अगर (!depth)
		वापस माप(*md);

	अगर (nla_type(nla) != TCA_FLOWER_KEY_ENC_OPTS_VXLAN) अणु
		NL_SET_ERR_MSG(extack, "Non-vxlan option type for mask");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_FLOWER_KEY_ENC_OPT_VXLAN_MAX, nla,
			       vxlan_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!option_len && !tb[TCA_FLOWER_KEY_ENC_OPT_VXLAN_GBP]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key vxlan option gbp");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_OPT_VXLAN_GBP]) अणु
		md->gbp = nla_get_u32(tb[TCA_FLOWER_KEY_ENC_OPT_VXLAN_GBP]);
		md->gbp &= VXLAN_GBP_MASK;
	पूर्ण

	वापस माप(*md);
पूर्ण

अटल पूर्णांक fl_set_erspan_opt(स्थिर काष्ठा nlattr *nla, काष्ठा fl_flow_key *key,
			     पूर्णांक depth, पूर्णांक option_len,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_MAX + 1];
	काष्ठा erspan_metadata *md;
	पूर्णांक err;

	md = (काष्ठा erspan_metadata *)&key->enc_opts.data[key->enc_opts.len];
	स_रखो(md, 0xff, माप(*md));
	md->version = 1;

	अगर (!depth)
		वापस माप(*md);

	अगर (nla_type(nla) != TCA_FLOWER_KEY_ENC_OPTS_ERSPAN) अणु
		NL_SET_ERR_MSG(extack, "Non-erspan option type for mask");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_FLOWER_KEY_ENC_OPT_ERSPAN_MAX, nla,
			       erspan_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!option_len && !tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_VER]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option ver");
		वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_VER])
		md->version = nla_get_u8(tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_VER]);

	अगर (md->version == 1) अणु
		अगर (!option_len && !tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_INDEX]) अणु
			NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option index");
			वापस -EINVAL;
		पूर्ण
		अगर (tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_INDEX]) अणु
			nla = tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_INDEX];
			स_रखो(&md->u, 0x00, माप(md->u));
			md->u.index = nla_get_be32(nla);
		पूर्ण
	पूर्ण अन्यथा अगर (md->version == 2) अणु
		अगर (!option_len && (!tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_सूची] ||
				    !tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_HWID])) अणु
			NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option dir or hwid");
			वापस -EINVAL;
		पूर्ण
		अगर (tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_सूची]) अणु
			nla = tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_सूची];
			md->u.md2.dir = nla_get_u8(nla);
		पूर्ण
		अगर (tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_HWID]) अणु
			nla = tb[TCA_FLOWER_KEY_ENC_OPT_ERSPAN_HWID];
			set_hwid(&md->u.md2, nla_get_u8(nla));
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Tunnel key erspan option ver is incorrect");
		वापस -EINVAL;
	पूर्ण

	वापस माप(*md);
पूर्ण

अटल पूर्णांक fl_set_enc_opt(काष्ठा nlattr **tb, काष्ठा fl_flow_key *key,
			  काष्ठा fl_flow_key *mask,
			  काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nlattr *nla_enc_key, *nla_opt_key, *nla_opt_msk = शून्य;
	पूर्णांक err, option_len, key_depth, msk_depth = 0;

	err = nla_validate_nested_deprecated(tb[TCA_FLOWER_KEY_ENC_OPTS],
					     TCA_FLOWER_KEY_ENC_OPTS_MAX,
					     enc_opts_policy, extack);
	अगर (err)
		वापस err;

	nla_enc_key = nla_data(tb[TCA_FLOWER_KEY_ENC_OPTS]);

	अगर (tb[TCA_FLOWER_KEY_ENC_OPTS_MASK]) अणु
		err = nla_validate_nested_deprecated(tb[TCA_FLOWER_KEY_ENC_OPTS_MASK],
						     TCA_FLOWER_KEY_ENC_OPTS_MAX,
						     enc_opts_policy, extack);
		अगर (err)
			वापस err;

		nla_opt_msk = nla_data(tb[TCA_FLOWER_KEY_ENC_OPTS_MASK]);
		msk_depth = nla_len(tb[TCA_FLOWER_KEY_ENC_OPTS_MASK]);
		अगर (!nla_ok(nla_opt_msk, msk_depth)) अणु
			NL_SET_ERR_MSG(extack, "Invalid nested attribute for masks");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	nla_क्रम_each_attr(nla_opt_key, nla_enc_key,
			  nla_len(tb[TCA_FLOWER_KEY_ENC_OPTS]), key_depth) अणु
		चयन (nla_type(nla_opt_key)) अणु
		हाल TCA_FLOWER_KEY_ENC_OPTS_GENEVE:
			अगर (key->enc_opts.dst_opt_type &&
			    key->enc_opts.dst_opt_type != TUNNEL_GENEVE_OPT) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for geneve options");
				वापस -EINVAL;
			पूर्ण
			option_len = 0;
			key->enc_opts.dst_opt_type = TUNNEL_GENEVE_OPT;
			option_len = fl_set_geneve_opt(nla_opt_key, key,
						       key_depth, option_len,
						       extack);
			अगर (option_len < 0)
				वापस option_len;

			key->enc_opts.len += option_len;
			/* At the same समय we need to parse through the mask
			 * in order to verअगरy exact and mask attribute lengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEL_GENEVE_OPT;
			option_len = fl_set_geneve_opt(nla_opt_msk, mask,
						       msk_depth, option_len,
						       extack);
			अगर (option_len < 0)
				वापस option_len;

			mask->enc_opts.len += option_len;
			अगर (key->enc_opts.len != mask->enc_opts.len) अणु
				NL_SET_ERR_MSG(extack, "Key and mask miss aligned");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल TCA_FLOWER_KEY_ENC_OPTS_VXLAN:
			अगर (key->enc_opts.dst_opt_type) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for vxlan options");
				वापस -EINVAL;
			पूर्ण
			option_len = 0;
			key->enc_opts.dst_opt_type = TUNNEL_VXLAN_OPT;
			option_len = fl_set_vxlan_opt(nla_opt_key, key,
						      key_depth, option_len,
						      extack);
			अगर (option_len < 0)
				वापस option_len;

			key->enc_opts.len += option_len;
			/* At the same समय we need to parse through the mask
			 * in order to verअगरy exact and mask attribute lengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEL_VXLAN_OPT;
			option_len = fl_set_vxlan_opt(nla_opt_msk, mask,
						      msk_depth, option_len,
						      extack);
			अगर (option_len < 0)
				वापस option_len;

			mask->enc_opts.len += option_len;
			अगर (key->enc_opts.len != mask->enc_opts.len) अणु
				NL_SET_ERR_MSG(extack, "Key and mask miss aligned");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल TCA_FLOWER_KEY_ENC_OPTS_ERSPAN:
			अगर (key->enc_opts.dst_opt_type) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for erspan options");
				वापस -EINVAL;
			पूर्ण
			option_len = 0;
			key->enc_opts.dst_opt_type = TUNNEL_ERSPAN_OPT;
			option_len = fl_set_erspan_opt(nla_opt_key, key,
						       key_depth, option_len,
						       extack);
			अगर (option_len < 0)
				वापस option_len;

			key->enc_opts.len += option_len;
			/* At the same समय we need to parse through the mask
			 * in order to verअगरy exact and mask attribute lengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEL_ERSPAN_OPT;
			option_len = fl_set_erspan_opt(nla_opt_msk, mask,
						       msk_depth, option_len,
						       extack);
			अगर (option_len < 0)
				वापस option_len;

			mask->enc_opts.len += option_len;
			अगर (key->enc_opts.len != mask->enc_opts.len) अणु
				NL_SET_ERR_MSG(extack, "Key and mask miss aligned");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unknown tunnel option type");
			वापस -EINVAL;
		पूर्ण

		अगर (!msk_depth)
			जारी;

		अगर (!nla_ok(nla_opt_msk, msk_depth)) अणु
			NL_SET_ERR_MSG(extack, "A mask attribute is invalid");
			वापस -EINVAL;
		पूर्ण
		nla_opt_msk = nla_next(nla_opt_msk, &msk_depth);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_validate_ct_state(u16 state, काष्ठा nlattr *tb,
				काष्ठा netlink_ext_ack *extack)
अणु
	अगर (state && !(state & TCA_FLOWER_KEY_CT_FLAGS_TRACKED)) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb,
				    "no trk, so no other flag can be set");
		वापस -EINVAL;
	पूर्ण

	अगर (state & TCA_FLOWER_KEY_CT_FLAGS_NEW &&
	    state & TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb,
				    "new and est are mutually exclusive");
		वापस -EINVAL;
	पूर्ण

	अगर (state & TCA_FLOWER_KEY_CT_FLAGS_INVALID &&
	    state & ~(TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
		      TCA_FLOWER_KEY_CT_FLAGS_INVALID)) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb,
				    "when inv is set, only trk may be set");
		वापस -EINVAL;
	पूर्ण

	अगर (state & TCA_FLOWER_KEY_CT_FLAGS_NEW &&
	    state & TCA_FLOWER_KEY_CT_FLAGS_REPLY) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb,
				    "new and rpl are mutually exclusive");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_set_key_ct(काष्ठा nlattr **tb,
			 काष्ठा flow_dissector_key_ct *key,
			 काष्ठा flow_dissector_key_ct *mask,
			 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[TCA_FLOWER_KEY_CT_STATE]) अणु
		पूर्णांक err;

		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK)) अणु
			NL_SET_ERR_MSG(extack, "Conntrack isn't enabled");
			वापस -EOPNOTSUPP;
		पूर्ण
		fl_set_key_val(tb, &key->ct_state, TCA_FLOWER_KEY_CT_STATE,
			       &mask->ct_state, TCA_FLOWER_KEY_CT_STATE_MASK,
			       माप(key->ct_state));

		err = fl_validate_ct_state(key->ct_state & mask->ct_state,
					   tb[TCA_FLOWER_KEY_CT_STATE_MASK],
					   extack);
		अगर (err)
			वापस err;

	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_CT_ZONE]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES)) अणु
			NL_SET_ERR_MSG(extack, "Conntrack zones isn't enabled");
			वापस -EOPNOTSUPP;
		पूर्ण
		fl_set_key_val(tb, &key->ct_zone, TCA_FLOWER_KEY_CT_ZONE,
			       &mask->ct_zone, TCA_FLOWER_KEY_CT_ZONE_MASK,
			       माप(key->ct_zone));
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_CT_MARK]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)) अणु
			NL_SET_ERR_MSG(extack, "Conntrack mark isn't enabled");
			वापस -EOPNOTSUPP;
		पूर्ण
		fl_set_key_val(tb, &key->ct_mark, TCA_FLOWER_KEY_CT_MARK,
			       &mask->ct_mark, TCA_FLOWER_KEY_CT_MARK_MASK,
			       माप(key->ct_mark));
	पूर्ण
	अगर (tb[TCA_FLOWER_KEY_CT_LABELS]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS)) अणु
			NL_SET_ERR_MSG(extack, "Conntrack labels aren't enabled");
			वापस -EOPNOTSUPP;
		पूर्ण
		fl_set_key_val(tb, key->ct_labels, TCA_FLOWER_KEY_CT_LABELS,
			       mask->ct_labels, TCA_FLOWER_KEY_CT_LABELS_MASK,
			       माप(key->ct_labels));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_set_key(काष्ठा net *net, काष्ठा nlattr **tb,
		      काष्ठा fl_flow_key *key, काष्ठा fl_flow_key *mask,
		      काष्ठा netlink_ext_ack *extack)
अणु
	__be16 ethertype;
	पूर्णांक ret = 0;

	अगर (tb[TCA_FLOWER_INDEV]) अणु
		पूर्णांक err = tcf_change_indev(net, tb[TCA_FLOWER_INDEV], extack);
		अगर (err < 0)
			वापस err;
		key->meta.ingress_अगरindex = err;
		mask->meta.ingress_अगरindex = 0xffffffff;
	पूर्ण

	fl_set_key_val(tb, key->eth.dst, TCA_FLOWER_KEY_ETH_DST,
		       mask->eth.dst, TCA_FLOWER_KEY_ETH_DST_MASK,
		       माप(key->eth.dst));
	fl_set_key_val(tb, key->eth.src, TCA_FLOWER_KEY_ETH_SRC,
		       mask->eth.src, TCA_FLOWER_KEY_ETH_SRC_MASK,
		       माप(key->eth.src));

	अगर (tb[TCA_FLOWER_KEY_ETH_TYPE]) अणु
		ethertype = nla_get_be16(tb[TCA_FLOWER_KEY_ETH_TYPE]);

		अगर (eth_type_vlan(ethertype)) अणु
			fl_set_key_vlan(tb, ethertype, TCA_FLOWER_KEY_VLAN_ID,
					TCA_FLOWER_KEY_VLAN_PRIO, &key->vlan,
					&mask->vlan);

			अगर (tb[TCA_FLOWER_KEY_VLAN_ETH_TYPE]) अणु
				ethertype = nla_get_be16(tb[TCA_FLOWER_KEY_VLAN_ETH_TYPE]);
				अगर (eth_type_vlan(ethertype)) अणु
					fl_set_key_vlan(tb, ethertype,
							TCA_FLOWER_KEY_CVLAN_ID,
							TCA_FLOWER_KEY_CVLAN_PRIO,
							&key->cvlan, &mask->cvlan);
					fl_set_key_val(tb, &key->basic.n_proto,
						       TCA_FLOWER_KEY_CVLAN_ETH_TYPE,
						       &mask->basic.n_proto,
						       TCA_FLOWER_UNSPEC,
						       माप(key->basic.n_proto));
				पूर्ण अन्यथा अणु
					key->basic.n_proto = ethertype;
					mask->basic.n_proto = cpu_to_be16(~0);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			key->basic.n_proto = ethertype;
			mask->basic.n_proto = cpu_to_be16(~0);
		पूर्ण
	पूर्ण

	अगर (key->basic.n_proto == htons(ETH_P_IP) ||
	    key->basic.n_proto == htons(ETH_P_IPV6)) अणु
		fl_set_key_val(tb, &key->basic.ip_proto, TCA_FLOWER_KEY_IP_PROTO,
			       &mask->basic.ip_proto, TCA_FLOWER_UNSPEC,
			       माप(key->basic.ip_proto));
		fl_set_key_ip(tb, false, &key->ip, &mask->ip);
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_IPV4_SRC] || tb[TCA_FLOWER_KEY_IPV4_DST]) अणु
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		mask->control.addr_type = ~0;
		fl_set_key_val(tb, &key->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC,
			       &mask->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC_MASK,
			       माप(key->ipv4.src));
		fl_set_key_val(tb, &key->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST,
			       &mask->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST_MASK,
			       माप(key->ipv4.dst));
	पूर्ण अन्यथा अगर (tb[TCA_FLOWER_KEY_IPV6_SRC] || tb[TCA_FLOWER_KEY_IPV6_DST]) अणु
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		mask->control.addr_type = ~0;
		fl_set_key_val(tb, &key->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC,
			       &mask->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC_MASK,
			       माप(key->ipv6.src));
		fl_set_key_val(tb, &key->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST,
			       &mask->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST_MASK,
			       माप(key->ipv6.dst));
	पूर्ण

	अगर (key->basic.ip_proto == IPPROTO_TCP) अणु
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_TCP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_TCP_SRC_MASK,
			       माप(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_TCP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_TCP_DST_MASK,
			       माप(key->tp.dst));
		fl_set_key_val(tb, &key->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS,
			       &mask->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS_MASK,
			       माप(key->tcp.flags));
	पूर्ण अन्यथा अगर (key->basic.ip_proto == IPPROTO_UDP) अणु
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_UDP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_UDP_SRC_MASK,
			       माप(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_UDP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_UDP_DST_MASK,
			       माप(key->tp.dst));
	पूर्ण अन्यथा अगर (key->basic.ip_proto == IPPROTO_SCTP) अणु
		fl_set_key_val(tb, &key->tp.src, TCA_FLOWER_KEY_SCTP_SRC,
			       &mask->tp.src, TCA_FLOWER_KEY_SCTP_SRC_MASK,
			       माप(key->tp.src));
		fl_set_key_val(tb, &key->tp.dst, TCA_FLOWER_KEY_SCTP_DST,
			       &mask->tp.dst, TCA_FLOWER_KEY_SCTP_DST_MASK,
			       माप(key->tp.dst));
	पूर्ण अन्यथा अगर (key->basic.n_proto == htons(ETH_P_IP) &&
		   key->basic.ip_proto == IPPROTO_ICMP) अणु
		fl_set_key_val(tb, &key->icmp.type, TCA_FLOWER_KEY_ICMPV4_TYPE,
			       &mask->icmp.type,
			       TCA_FLOWER_KEY_ICMPV4_TYPE_MASK,
			       माप(key->icmp.type));
		fl_set_key_val(tb, &key->icmp.code, TCA_FLOWER_KEY_ICMPV4_CODE,
			       &mask->icmp.code,
			       TCA_FLOWER_KEY_ICMPV4_CODE_MASK,
			       माप(key->icmp.code));
	पूर्ण अन्यथा अगर (key->basic.n_proto == htons(ETH_P_IPV6) &&
		   key->basic.ip_proto == IPPROTO_ICMPV6) अणु
		fl_set_key_val(tb, &key->icmp.type, TCA_FLOWER_KEY_ICMPV6_TYPE,
			       &mask->icmp.type,
			       TCA_FLOWER_KEY_ICMPV6_TYPE_MASK,
			       माप(key->icmp.type));
		fl_set_key_val(tb, &key->icmp.code, TCA_FLOWER_KEY_ICMPV6_CODE,
			       &mask->icmp.code,
			       TCA_FLOWER_KEY_ICMPV6_CODE_MASK,
			       माप(key->icmp.code));
	पूर्ण अन्यथा अगर (key->basic.n_proto == htons(ETH_P_MPLS_UC) ||
		   key->basic.n_proto == htons(ETH_P_MPLS_MC)) अणु
		ret = fl_set_key_mpls(tb, &key->mpls, &mask->mpls, extack);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (key->basic.n_proto == htons(ETH_P_ARP) ||
		   key->basic.n_proto == htons(ETH_P_RARP)) अणु
		fl_set_key_val(tb, &key->arp.sip, TCA_FLOWER_KEY_ARP_SIP,
			       &mask->arp.sip, TCA_FLOWER_KEY_ARP_SIP_MASK,
			       माप(key->arp.sip));
		fl_set_key_val(tb, &key->arp.tip, TCA_FLOWER_KEY_ARP_TIP,
			       &mask->arp.tip, TCA_FLOWER_KEY_ARP_TIP_MASK,
			       माप(key->arp.tip));
		fl_set_key_val(tb, &key->arp.op, TCA_FLOWER_KEY_ARP_OP,
			       &mask->arp.op, TCA_FLOWER_KEY_ARP_OP_MASK,
			       माप(key->arp.op));
		fl_set_key_val(tb, key->arp.sha, TCA_FLOWER_KEY_ARP_SHA,
			       mask->arp.sha, TCA_FLOWER_KEY_ARP_SHA_MASK,
			       माप(key->arp.sha));
		fl_set_key_val(tb, key->arp.tha, TCA_FLOWER_KEY_ARP_THA,
			       mask->arp.tha, TCA_FLOWER_KEY_ARP_THA_MASK,
			       माप(key->arp.tha));
	पूर्ण

	अगर (key->basic.ip_proto == IPPROTO_TCP ||
	    key->basic.ip_proto == IPPROTO_UDP ||
	    key->basic.ip_proto == IPPROTO_SCTP) अणु
		ret = fl_set_key_port_range(tb, key, mask, extack);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_IPV4_SRC] ||
	    tb[TCA_FLOWER_KEY_ENC_IPV4_DST]) अणु
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		mask->enc_control.addr_type = ~0;
		fl_set_key_val(tb, &key->enc_ipv4.src,
			       TCA_FLOWER_KEY_ENC_IPV4_SRC,
			       &mask->enc_ipv4.src,
			       TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK,
			       माप(key->enc_ipv4.src));
		fl_set_key_val(tb, &key->enc_ipv4.dst,
			       TCA_FLOWER_KEY_ENC_IPV4_DST,
			       &mask->enc_ipv4.dst,
			       TCA_FLOWER_KEY_ENC_IPV4_DST_MASK,
			       माप(key->enc_ipv4.dst));
	पूर्ण

	अगर (tb[TCA_FLOWER_KEY_ENC_IPV6_SRC] ||
	    tb[TCA_FLOWER_KEY_ENC_IPV6_DST]) अणु
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		mask->enc_control.addr_type = ~0;
		fl_set_key_val(tb, &key->enc_ipv6.src,
			       TCA_FLOWER_KEY_ENC_IPV6_SRC,
			       &mask->enc_ipv6.src,
			       TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK,
			       माप(key->enc_ipv6.src));
		fl_set_key_val(tb, &key->enc_ipv6.dst,
			       TCA_FLOWER_KEY_ENC_IPV6_DST,
			       &mask->enc_ipv6.dst,
			       TCA_FLOWER_KEY_ENC_IPV6_DST_MASK,
			       माप(key->enc_ipv6.dst));
	पूर्ण

	fl_set_key_val(tb, &key->enc_key_id.keyid, TCA_FLOWER_KEY_ENC_KEY_ID,
		       &mask->enc_key_id.keyid, TCA_FLOWER_UNSPEC,
		       माप(key->enc_key_id.keyid));

	fl_set_key_val(tb, &key->enc_tp.src, TCA_FLOWER_KEY_ENC_UDP_SRC_PORT,
		       &mask->enc_tp.src, TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK,
		       माप(key->enc_tp.src));

	fl_set_key_val(tb, &key->enc_tp.dst, TCA_FLOWER_KEY_ENC_UDP_DST_PORT,
		       &mask->enc_tp.dst, TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK,
		       माप(key->enc_tp.dst));

	fl_set_key_ip(tb, true, &key->enc_ip, &mask->enc_ip);

	fl_set_key_val(tb, &key->hash.hash, TCA_FLOWER_KEY_HASH,
		       &mask->hash.hash, TCA_FLOWER_KEY_HASH_MASK,
		       माप(key->hash.hash));

	अगर (tb[TCA_FLOWER_KEY_ENC_OPTS]) अणु
		ret = fl_set_enc_opt(tb, key, mask, extack);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = fl_set_key_ct(tb, &key->ct, &mask->ct, extack);
	अगर (ret)
		वापस ret;

	अगर (tb[TCA_FLOWER_KEY_FLAGS])
		ret = fl_set_key_flags(tb, &key->control.flags,
				       &mask->control.flags, extack);

	वापस ret;
पूर्ण

अटल व्योम fl_mask_copy(काष्ठा fl_flow_mask *dst,
			 काष्ठा fl_flow_mask *src)
अणु
	स्थिर व्योम *psrc = fl_key_get_start(&src->key, src);
	व्योम *pdst = fl_key_get_start(&dst->key, src);

	स_नकल(pdst, psrc, fl_mask_range(src));
	dst->range = src->range;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params fl_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा cls_fl_filter, mkey), /* base offset */
	.head_offset = दुरत्व(काष्ठा cls_fl_filter, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल पूर्णांक fl_init_mask_hashtable(काष्ठा fl_flow_mask *mask)
अणु
	mask->filter_ht_params = fl_ht_params;
	mask->filter_ht_params.key_len = fl_mask_range(mask);
	mask->filter_ht_params.key_offset += mask->range.start;

	वापस rhashtable_init(&mask->ht, &mask->filter_ht_params);
पूर्ण

#घोषणा FL_KEY_MEMBER_OFFSET(member) दुरत्व(काष्ठा fl_flow_key, member)
#घोषणा FL_KEY_MEMBER_SIZE(member) माप_field(काष्ठा fl_flow_key, member)

#घोषणा FL_KEY_IS_MASKED(mask, member)						\
	स_प्रथम_inv(((अक्षर *)mask) + FL_KEY_MEMBER_OFFSET(member),		\
		   0, FL_KEY_MEMBER_SIZE(member))				\

#घोषणा FL_KEY_SET(keys, cnt, id, member)					\
	करो अणु									\
		keys[cnt].key_id = id;						\
		keys[cnt].offset = FL_KEY_MEMBER_OFFSET(member);		\
		cnt++;								\
	पूर्ण जबतक(0);

#घोषणा FL_KEY_SET_IF_MASKED(mask, keys, cnt, id, member)			\
	करो अणु									\
		अगर (FL_KEY_IS_MASKED(mask, member))				\
			FL_KEY_SET(keys, cnt, id, member);			\
	पूर्ण जबतक(0);

अटल व्योम fl_init_dissector(काष्ठा flow_dissector *dissector,
			      काष्ठा fl_flow_key *mask)
अणु
	काष्ठा flow_dissector_key keys[FLOW_DISSECTOR_KEY_MAX];
	माप_प्रकार cnt = 0;

	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_META, meta);
	FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_CONTROL, control);
	FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_BASIC, basic);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ETH_ADDRS, eth);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IPV4_ADDRS, ipv4);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IPV6_ADDRS, ipv6);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_PORTS, tp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_PORTS_RANGE, tp_range);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IP, ip);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_TCP, tcp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ICMP, icmp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ARP, arp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_MPLS, mpls);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_VLAN, vlan);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_CVLAN, cvlan);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_KEYID, enc_key_id);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS, enc_ipv4);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS, enc_ipv6);
	अगर (FL_KEY_IS_MASKED(mask, enc_ipv4) ||
	    FL_KEY_IS_MASKED(mask, enc_ipv6))
		FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_ENC_CONTROL,
			   enc_control);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_PORTS, enc_tp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IP, enc_ip);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_OPTS, enc_opts);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_CT, ct);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_HASH, hash);

	skb_flow_dissector_init(dissector, keys, cnt);
पूर्ण

अटल काष्ठा fl_flow_mask *fl_create_new_mask(काष्ठा cls_fl_head *head,
					       काष्ठा fl_flow_mask *mask)
अणु
	काष्ठा fl_flow_mask *newmask;
	पूर्णांक err;

	newmask = kzalloc(माप(*newmask), GFP_KERNEL);
	अगर (!newmask)
		वापस ERR_PTR(-ENOMEM);

	fl_mask_copy(newmask, mask);

	अगर ((newmask->key.tp_range.tp_min.dst &&
	     newmask->key.tp_range.tp_max.dst) ||
	    (newmask->key.tp_range.tp_min.src &&
	     newmask->key.tp_range.tp_max.src))
		newmask->flags |= TCA_FLOWER_MASK_FLAGS_RANGE;

	err = fl_init_mask_hashtable(newmask);
	अगर (err)
		जाओ errout_मुक्त;

	fl_init_dissector(&newmask->dissector, &newmask->key);

	INIT_LIST_HEAD_RCU(&newmask->filters);

	refcount_set(&newmask->refcnt, 1);
	err = rhashtable_replace_fast(&head->ht, &mask->ht_node,
				      &newmask->ht_node, mask_ht_params);
	अगर (err)
		जाओ errout_destroy;

	spin_lock(&head->masks_lock);
	list_add_tail_rcu(&newmask->list, &head->masks);
	spin_unlock(&head->masks_lock);

	वापस newmask;

errout_destroy:
	rhashtable_destroy(&newmask->ht);
errout_मुक्त:
	kमुक्त(newmask);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक fl_check_assign_mask(काष्ठा cls_fl_head *head,
				काष्ठा cls_fl_filter *fnew,
				काष्ठा cls_fl_filter *fold,
				काष्ठा fl_flow_mask *mask)
अणु
	काष्ठा fl_flow_mask *newmask;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();

	/* Insert mask as temporary node to prevent concurrent creation of mask
	 * with same key. Any concurrent lookups with same key will वापस
	 * -EAGAIN because mask's refcnt is zero.
	 */
	fnew->mask = rhashtable_lookup_get_insert_fast(&head->ht,
						       &mask->ht_node,
						       mask_ht_params);
	अगर (!fnew->mask) अणु
		rcu_पढ़ो_unlock();

		अगर (fold) अणु
			ret = -EINVAL;
			जाओ errout_cleanup;
		पूर्ण

		newmask = fl_create_new_mask(head, mask);
		अगर (IS_ERR(newmask)) अणु
			ret = PTR_ERR(newmask);
			जाओ errout_cleanup;
		पूर्ण

		fnew->mask = newmask;
		वापस 0;
	पूर्ण अन्यथा अगर (IS_ERR(fnew->mask)) अणु
		ret = PTR_ERR(fnew->mask);
	पूर्ण अन्यथा अगर (fold && fold->mask != fnew->mask) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (!refcount_inc_not_zero(&fnew->mask->refcnt)) अणु
		/* Mask was deleted concurrently, try again */
		ret = -EAGAIN;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;

errout_cleanup:
	rhashtable_हटाओ_fast(&head->ht, &mask->ht_node,
			       mask_ht_params);
	वापस ret;
पूर्ण

अटल पूर्णांक fl_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			काष्ठा cls_fl_filter *f, काष्ठा fl_flow_mask *mask,
			अचिन्हित दीर्घ base, काष्ठा nlattr **tb,
			काष्ठा nlattr *est, bool ovr,
			काष्ठा fl_flow_पंचांगplt *पंचांगplt, bool rtnl_held,
			काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = tcf_exts_validate(net, tp, tb, est, &f->exts, ovr, rtnl_held,
				extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_FLOWER_CLASSID]) अणु
		f->res.classid = nla_get_u32(tb[TCA_FLOWER_CLASSID]);
		अगर (!rtnl_held)
			rtnl_lock();
		tcf_bind_filter(tp, &f->res, base);
		अगर (!rtnl_held)
			rtnl_unlock();
	पूर्ण

	err = fl_set_key(net, tb, &f->key, &mask->key, extack);
	अगर (err)
		वापस err;

	fl_mask_update_range(mask);
	fl_set_masked_key(&f->mkey, &f->key, mask);

	अगर (!fl_mask_fits_पंचांगplt(पंचांगplt, mask)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Mask does not fit the template");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_ht_insert_unique(काष्ठा cls_fl_filter *fnew,
			       काष्ठा cls_fl_filter *fold,
			       bool *in_ht)
अणु
	काष्ठा fl_flow_mask *mask = fnew->mask;
	पूर्णांक err;

	err = rhashtable_lookup_insert_fast(&mask->ht,
					    &fnew->ht_node,
					    mask->filter_ht_params);
	अगर (err) अणु
		*in_ht = false;
		/* It is okay अगर filter with same key exists when
		 * overwriting.
		 */
		वापस fold && err == -EEXIST ? 0 : err;
	पूर्ण

	*in_ht = true;
	वापस 0;
पूर्ण

अटल पूर्णांक fl_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		     काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		     u32 handle, काष्ठा nlattr **tca,
		     व्योम **arg, bool ovr, bool rtnl_held,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);
	काष्ठा cls_fl_filter *fold = *arg;
	काष्ठा cls_fl_filter *fnew;
	काष्ठा fl_flow_mask *mask;
	काष्ठा nlattr **tb;
	bool in_ht;
	पूर्णांक err;

	अगर (!tca[TCA_OPTIONS]) अणु
		err = -EINVAL;
		जाओ errout_fold;
	पूर्ण

	mask = kzalloc(माप(काष्ठा fl_flow_mask), GFP_KERNEL);
	अगर (!mask) अणु
		err = -ENOBUFS;
		जाओ errout_fold;
	पूर्ण

	tb = kसुस्मृति(TCA_FLOWER_MAX + 1, माप(काष्ठा nlattr *), GFP_KERNEL);
	अगर (!tb) अणु
		err = -ENOBUFS;
		जाओ errout_mask_alloc;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_FLOWER_MAX,
					  tca[TCA_OPTIONS], fl_policy, शून्य);
	अगर (err < 0)
		जाओ errout_tb;

	अगर (fold && handle && fold->handle != handle) अणु
		err = -EINVAL;
		जाओ errout_tb;
	पूर्ण

	fnew = kzalloc(माप(*fnew), GFP_KERNEL);
	अगर (!fnew) अणु
		err = -ENOBUFS;
		जाओ errout_tb;
	पूर्ण
	INIT_LIST_HEAD(&fnew->hw_list);
	refcount_set(&fnew->refcnt, 1);

	err = tcf_exts_init(&fnew->exts, net, TCA_FLOWER_ACT, 0);
	अगर (err < 0)
		जाओ errout;

	अगर (tb[TCA_FLOWER_FLAGS]) अणु
		fnew->flags = nla_get_u32(tb[TCA_FLOWER_FLAGS]);

		अगर (!tc_flags_valid(fnew->flags)) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण
	पूर्ण

	err = fl_set_parms(net, tp, fnew, mask, base, tb, tca[TCA_RATE], ovr,
			   tp->chain->पंचांगplt_priv, rtnl_held, extack);
	अगर (err)
		जाओ errout;

	err = fl_check_assign_mask(head, fnew, fold, mask);
	अगर (err)
		जाओ errout;

	err = fl_ht_insert_unique(fnew, fold, &in_ht);
	अगर (err)
		जाओ errout_mask;

	अगर (!tc_skip_hw(fnew->flags)) अणु
		err = fl_hw_replace_filter(tp, fnew, rtnl_held, extack);
		अगर (err)
			जाओ errout_ht;
	पूर्ण

	अगर (!tc_in_hw(fnew->flags))
		fnew->flags |= TCA_CLS_FLAGS_NOT_IN_HW;

	spin_lock(&tp->lock);

	/* tp was deleted concurrently. -EAGAIN will cause caller to lookup
	 * proto again or create new one, अगर necessary.
	 */
	अगर (tp->deleting) अणु
		err = -EAGAIN;
		जाओ errout_hw;
	पूर्ण

	अगर (fold) अणु
		/* Fold filter was deleted concurrently. Retry lookup. */
		अगर (fold->deleted) अणु
			err = -EAGAIN;
			जाओ errout_hw;
		पूर्ण

		fnew->handle = handle;

		अगर (!in_ht) अणु
			काष्ठा rhashtable_params params =
				fnew->mask->filter_ht_params;

			err = rhashtable_insert_fast(&fnew->mask->ht,
						     &fnew->ht_node,
						     params);
			अगर (err)
				जाओ errout_hw;
			in_ht = true;
		पूर्ण

		refcount_inc(&fnew->refcnt);
		rhashtable_हटाओ_fast(&fold->mask->ht,
				       &fold->ht_node,
				       fold->mask->filter_ht_params);
		idr_replace(&head->handle_idr, fnew, fnew->handle);
		list_replace_rcu(&fold->list, &fnew->list);
		fold->deleted = true;

		spin_unlock(&tp->lock);

		fl_mask_put(head, fold->mask);
		अगर (!tc_skip_hw(fold->flags))
			fl_hw_destroy_filter(tp, fold, rtnl_held, शून्य);
		tcf_unbind_filter(tp, &fold->res);
		/* Caller holds reference to fold, so refcnt is always > 0
		 * after this.
		 */
		refcount_dec(&fold->refcnt);
		__fl_put(fold);
	पूर्ण अन्यथा अणु
		अगर (handle) अणु
			/* user specअगरies a handle and it करोesn't exist */
			err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
					    handle, GFP_ATOMIC);

			/* Filter with specअगरied handle was concurrently
			 * inserted after initial check in cls_api. This is not
			 * necessarily an error अगर NLM_F_EXCL is not set in
			 * message flags. Returning EAGAIN will cause cls_api to
			 * try to update concurrently inserted rule.
			 */
			अगर (err == -ENOSPC)
				err = -EAGAIN;
		पूर्ण अन्यथा अणु
			handle = 1;
			err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
					    पूर्णांक_उच्च, GFP_ATOMIC);
		पूर्ण
		अगर (err)
			जाओ errout_hw;

		refcount_inc(&fnew->refcnt);
		fnew->handle = handle;
		list_add_tail_rcu(&fnew->list, &fnew->mask->filters);
		spin_unlock(&tp->lock);
	पूर्ण

	*arg = fnew;

	kमुक्त(tb);
	tcf_queue_work(&mask->rwork, fl_uninit_mask_मुक्त_work);
	वापस 0;

errout_ht:
	spin_lock(&tp->lock);
errout_hw:
	fnew->deleted = true;
	spin_unlock(&tp->lock);
	अगर (!tc_skip_hw(fnew->flags))
		fl_hw_destroy_filter(tp, fnew, rtnl_held, शून्य);
	अगर (in_ht)
		rhashtable_हटाओ_fast(&fnew->mask->ht, &fnew->ht_node,
				       fnew->mask->filter_ht_params);
errout_mask:
	fl_mask_put(head, fnew->mask);
errout:
	__fl_put(fnew);
errout_tb:
	kमुक्त(tb);
errout_mask_alloc:
	tcf_queue_work(&mask->rwork, fl_uninit_mask_मुक्त_work);
errout_fold:
	अगर (fold)
		__fl_put(fold);
	वापस err;
पूर्ण

अटल पूर्णांक fl_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		     bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);
	काष्ठा cls_fl_filter *f = arg;
	bool last_on_mask;
	पूर्णांक err = 0;

	err = __fl_delete(tp, f, &last_on_mask, rtnl_held, extack);
	*last = list_empty(&head->masks);
	__fl_put(f);

	वापस err;
पूर्ण

अटल व्योम fl_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		    bool rtnl_held)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);
	अचिन्हित दीर्घ id = arg->cookie, पंचांगp;
	काष्ठा cls_fl_filter *f;

	arg->count = arg->skip;

	idr_क्रम_each_entry_जारी_ul(&head->handle_idr, f, पंचांगp, id) अणु
		/* करोn't वापस filters that are being deleted */
		अगर (!refcount_inc_not_zero(&f->refcnt))
			जारी;
		अगर (arg->fn(tp, f, arg) < 0) अणु
			__fl_put(f);
			arg->stop = 1;
			अवरोध;
		पूर्ण
		__fl_put(f);
		arg->count++;
	पूर्ण
	arg->cookie = id;
पूर्ण

अटल काष्ठा cls_fl_filter *
fl_get_next_hw_filter(काष्ठा tcf_proto *tp, काष्ठा cls_fl_filter *f, bool add)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);

	spin_lock(&tp->lock);
	अगर (list_empty(&head->hw_filters)) अणु
		spin_unlock(&tp->lock);
		वापस शून्य;
	पूर्ण

	अगर (!f)
		f = list_entry(&head->hw_filters, काष्ठा cls_fl_filter,
			       hw_list);
	list_क्रम_each_entry_जारी(f, &head->hw_filters, hw_list) अणु
		अगर (!(add && f->deleted) && refcount_inc_not_zero(&f->refcnt)) अणु
			spin_unlock(&tp->lock);
			वापस f;
		पूर्ण
	पूर्ण

	spin_unlock(&tp->lock);
	वापस शून्य;
पूर्ण

अटल पूर्णांक fl_reoffload(काष्ठा tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			व्योम *cb_priv, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;
	काष्ठा cls_fl_filter *f = शून्य;
	पूर्णांक err;

	/* hw_filters list can only be changed by hw offload functions after
	 * obtaining rtnl lock. Make sure it is not changed जबतक reoffload is
	 * iterating it.
	 */
	ASSERT_RTNL();

	जबतक ((f = fl_get_next_hw_filter(tp, f, add))) अणु
		cls_flower.rule =
			flow_rule_alloc(tcf_exts_num_actions(&f->exts));
		अगर (!cls_flower.rule) अणु
			__fl_put(f);
			वापस -ENOMEM;
		पूर्ण

		tc_cls_common_offload_init(&cls_flower.common, tp, f->flags,
					   extack);
		cls_flower.command = add ?
			FLOW_CLS_REPLACE : FLOW_CLS_DESTROY;
		cls_flower.cookie = (अचिन्हित दीर्घ)f;
		cls_flower.rule->match.dissector = &f->mask->dissector;
		cls_flower.rule->match.mask = &f->mask->key;
		cls_flower.rule->match.key = &f->mkey;

		err = tc_setup_flow_action(&cls_flower.rule->action, &f->exts);
		अगर (err) अणु
			kमुक्त(cls_flower.rule);
			अगर (tc_skip_sw(f->flags)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
				__fl_put(f);
				वापस err;
			पूर्ण
			जाओ next_flow;
		पूर्ण

		cls_flower.classid = f->res.classid;

		err = tc_setup_cb_reoffload(block, tp, add, cb,
					    TC_SETUP_CLSFLOWER, &cls_flower,
					    cb_priv, &f->flags,
					    &f->in_hw_count);
		tc_cleanup_flow_action(&cls_flower.rule->action);
		kमुक्त(cls_flower.rule);

		अगर (err) अणु
			__fl_put(f);
			वापस err;
		पूर्ण
next_flow:
		__fl_put(f);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fl_hw_add(काष्ठा tcf_proto *tp, व्योम *type_data)
अणु
	काष्ठा flow_cls_offload *cls_flower = type_data;
	काष्ठा cls_fl_filter *f =
		(काष्ठा cls_fl_filter *) cls_flower->cookie;
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);

	spin_lock(&tp->lock);
	list_add(&f->hw_list, &head->hw_filters);
	spin_unlock(&tp->lock);
पूर्ण

अटल व्योम fl_hw_del(काष्ठा tcf_proto *tp, व्योम *type_data)
अणु
	काष्ठा flow_cls_offload *cls_flower = type_data;
	काष्ठा cls_fl_filter *f =
		(काष्ठा cls_fl_filter *) cls_flower->cookie;

	spin_lock(&tp->lock);
	अगर (!list_empty(&f->hw_list))
		list_del_init(&f->hw_list);
	spin_unlock(&tp->lock);
पूर्ण

अटल पूर्णांक fl_hw_create_पंचांगplt(काष्ठा tcf_chain *chain,
			      काष्ठा fl_flow_पंचांगplt *पंचांगplt)
अणु
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;
	काष्ठा tcf_block *block = chain->block;

	cls_flower.rule = flow_rule_alloc(0);
	अगर (!cls_flower.rule)
		वापस -ENOMEM;

	cls_flower.common.chain_index = chain->index;
	cls_flower.command = FLOW_CLS_TMPLT_CREATE;
	cls_flower.cookie = (अचिन्हित दीर्घ) पंचांगplt;
	cls_flower.rule->match.dissector = &पंचांगplt->dissector;
	cls_flower.rule->match.mask = &पंचांगplt->mask;
	cls_flower.rule->match.key = &पंचांगplt->dummy_key;

	/* We करोn't care अगर driver (any of them) fails to handle this
	 * call. It serves just as a hपूर्णांक क्रम it.
	 */
	tc_setup_cb_call(block, TC_SETUP_CLSFLOWER, &cls_flower, false, true);
	kमुक्त(cls_flower.rule);

	वापस 0;
पूर्ण

अटल व्योम fl_hw_destroy_पंचांगplt(काष्ठा tcf_chain *chain,
				काष्ठा fl_flow_पंचांगplt *पंचांगplt)
अणु
	काष्ठा flow_cls_offload cls_flower = अणुपूर्ण;
	काष्ठा tcf_block *block = chain->block;

	cls_flower.common.chain_index = chain->index;
	cls_flower.command = FLOW_CLS_TMPLT_DESTROY;
	cls_flower.cookie = (अचिन्हित दीर्घ) पंचांगplt;

	tc_setup_cb_call(block, TC_SETUP_CLSFLOWER, &cls_flower, false, true);
पूर्ण

अटल व्योम *fl_पंचांगplt_create(काष्ठा net *net, काष्ठा tcf_chain *chain,
			     काष्ठा nlattr **tca,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fl_flow_पंचांगplt *पंचांगplt;
	काष्ठा nlattr **tb;
	पूर्णांक err;

	अगर (!tca[TCA_OPTIONS])
		वापस ERR_PTR(-EINVAL);

	tb = kसुस्मृति(TCA_FLOWER_MAX + 1, माप(काष्ठा nlattr *), GFP_KERNEL);
	अगर (!tb)
		वापस ERR_PTR(-ENOBUFS);
	err = nla_parse_nested_deprecated(tb, TCA_FLOWER_MAX,
					  tca[TCA_OPTIONS], fl_policy, शून्य);
	अगर (err)
		जाओ errout_tb;

	पंचांगplt = kzalloc(माप(*पंचांगplt), GFP_KERNEL);
	अगर (!पंचांगplt) अणु
		err = -ENOMEM;
		जाओ errout_tb;
	पूर्ण
	पंचांगplt->chain = chain;
	err = fl_set_key(net, tb, &पंचांगplt->dummy_key, &पंचांगplt->mask, extack);
	अगर (err)
		जाओ errout_पंचांगplt;

	fl_init_dissector(&पंचांगplt->dissector, &पंचांगplt->mask);

	err = fl_hw_create_पंचांगplt(chain, पंचांगplt);
	अगर (err)
		जाओ errout_पंचांगplt;

	kमुक्त(tb);
	वापस पंचांगplt;

errout_पंचांगplt:
	kमुक्त(पंचांगplt);
errout_tb:
	kमुक्त(tb);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम fl_पंचांगplt_destroy(व्योम *पंचांगplt_priv)
अणु
	काष्ठा fl_flow_पंचांगplt *पंचांगplt = पंचांगplt_priv;

	fl_hw_destroy_पंचांगplt(पंचांगplt->chain, पंचांगplt);
	kमुक्त(पंचांगplt);
पूर्ण

अटल पूर्णांक fl_dump_key_val(काष्ठा sk_buff *skb,
			   व्योम *val, पूर्णांक val_type,
			   व्योम *mask, पूर्णांक mask_type, पूर्णांक len)
अणु
	पूर्णांक err;

	अगर (!स_प्रथम_inv(mask, 0, len))
		वापस 0;
	err = nla_put(skb, val_type, len, val);
	अगर (err)
		वापस err;
	अगर (mask_type != TCA_FLOWER_UNSPEC) अणु
		err = nla_put(skb, mask_type, len, mask);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fl_dump_key_port_range(काष्ठा sk_buff *skb, काष्ठा fl_flow_key *key,
				  काष्ठा fl_flow_key *mask)
अणु
	अगर (fl_dump_key_val(skb, &key->tp_range.tp_min.dst,
			    TCA_FLOWER_KEY_PORT_DST_MIN,
			    &mask->tp_range.tp_min.dst, TCA_FLOWER_UNSPEC,
			    माप(key->tp_range.tp_min.dst)) ||
	    fl_dump_key_val(skb, &key->tp_range.tp_max.dst,
			    TCA_FLOWER_KEY_PORT_DST_MAX,
			    &mask->tp_range.tp_max.dst, TCA_FLOWER_UNSPEC,
			    माप(key->tp_range.tp_max.dst)) ||
	    fl_dump_key_val(skb, &key->tp_range.tp_min.src,
			    TCA_FLOWER_KEY_PORT_SRC_MIN,
			    &mask->tp_range.tp_min.src, TCA_FLOWER_UNSPEC,
			    माप(key->tp_range.tp_min.src)) ||
	    fl_dump_key_val(skb, &key->tp_range.tp_max.src,
			    TCA_FLOWER_KEY_PORT_SRC_MAX,
			    &mask->tp_range.tp_max.src, TCA_FLOWER_UNSPEC,
			    माप(key->tp_range.tp_max.src)))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक fl_dump_key_mpls_opt_lse(काष्ठा sk_buff *skb,
				    काष्ठा flow_dissector_key_mpls *mpls_key,
				    काष्ठा flow_dissector_key_mpls *mpls_mask,
				    u8 lse_index)
अणु
	काष्ठा flow_dissector_mpls_lse *lse_mask = &mpls_mask->ls[lse_index];
	काष्ठा flow_dissector_mpls_lse *lse_key = &mpls_key->ls[lse_index];
	पूर्णांक err;

	err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_OPT_LSE_DEPTH,
			 lse_index + 1);
	अगर (err)
		वापस err;

	अगर (lse_mask->mpls_ttl) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_OPT_LSE_TTL,
				 lse_key->mpls_ttl);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_bos) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_OPT_LSE_BOS,
				 lse_key->mpls_bos);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_tc) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_OPT_LSE_TC,
				 lse_key->mpls_tc);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_label) अणु
		err = nla_put_u32(skb, TCA_FLOWER_KEY_MPLS_OPT_LSE_LABEL,
				  lse_key->mpls_label);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fl_dump_key_mpls_opts(काष्ठा sk_buff *skb,
				 काष्ठा flow_dissector_key_mpls *mpls_key,
				 काष्ठा flow_dissector_key_mpls *mpls_mask)
अणु
	काष्ठा nlattr *opts;
	काष्ठा nlattr *lse;
	u8 lse_index;
	पूर्णांक err;

	opts = nla_nest_start(skb, TCA_FLOWER_KEY_MPLS_OPTS);
	अगर (!opts)
		वापस -EMSGSIZE;

	क्रम (lse_index = 0; lse_index < FLOW_DIS_MPLS_MAX; lse_index++) अणु
		अगर (!(mpls_mask->used_lses & 1 << lse_index))
			जारी;

		lse = nla_nest_start(skb, TCA_FLOWER_KEY_MPLS_OPTS_LSE);
		अगर (!lse) अणु
			err = -EMSGSIZE;
			जाओ err_opts;
		पूर्ण

		err = fl_dump_key_mpls_opt_lse(skb, mpls_key, mpls_mask,
					       lse_index);
		अगर (err)
			जाओ err_opts_lse;
		nla_nest_end(skb, lse);
	पूर्ण
	nla_nest_end(skb, opts);

	वापस 0;

err_opts_lse:
	nla_nest_cancel(skb, lse);
err_opts:
	nla_nest_cancel(skb, opts);

	वापस err;
पूर्ण

अटल पूर्णांक fl_dump_key_mpls(काष्ठा sk_buff *skb,
			    काष्ठा flow_dissector_key_mpls *mpls_key,
			    काष्ठा flow_dissector_key_mpls *mpls_mask)
अणु
	काष्ठा flow_dissector_mpls_lse *lse_mask;
	काष्ठा flow_dissector_mpls_lse *lse_key;
	पूर्णांक err;

	अगर (!mpls_mask->used_lses)
		वापस 0;

	lse_mask = &mpls_mask->ls[0];
	lse_key = &mpls_key->ls[0];

	/* For backward compatibility, करोn't use the MPLS nested attributes अगर
	 * the rule can be expressed using the old attributes.
	 */
	अगर (mpls_mask->used_lses & ~1 ||
	    (!lse_mask->mpls_ttl && !lse_mask->mpls_bos &&
	     !lse_mask->mpls_tc && !lse_mask->mpls_label))
		वापस fl_dump_key_mpls_opts(skb, mpls_key, mpls_mask);

	अगर (lse_mask->mpls_ttl) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_TTL,
				 lse_key->mpls_ttl);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_tc) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_TC,
				 lse_key->mpls_tc);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_label) अणु
		err = nla_put_u32(skb, TCA_FLOWER_KEY_MPLS_LABEL,
				  lse_key->mpls_label);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (lse_mask->mpls_bos) अणु
		err = nla_put_u8(skb, TCA_FLOWER_KEY_MPLS_BOS,
				 lse_key->mpls_bos);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fl_dump_key_ip(काष्ठा sk_buff *skb, bool encap,
			  काष्ठा flow_dissector_key_ip *key,
			  काष्ठा flow_dissector_key_ip *mask)
अणु
	पूर्णांक tos_key = encap ? TCA_FLOWER_KEY_ENC_IP_TOS : TCA_FLOWER_KEY_IP_TOS;
	पूर्णांक ttl_key = encap ? TCA_FLOWER_KEY_ENC_IP_TTL : TCA_FLOWER_KEY_IP_TTL;
	पूर्णांक tos_mask = encap ? TCA_FLOWER_KEY_ENC_IP_TOS_MASK : TCA_FLOWER_KEY_IP_TOS_MASK;
	पूर्णांक ttl_mask = encap ? TCA_FLOWER_KEY_ENC_IP_TTL_MASK : TCA_FLOWER_KEY_IP_TTL_MASK;

	अगर (fl_dump_key_val(skb, &key->tos, tos_key, &mask->tos, tos_mask, माप(key->tos)) ||
	    fl_dump_key_val(skb, &key->ttl, ttl_key, &mask->ttl, ttl_mask, माप(key->ttl)))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक fl_dump_key_vlan(काष्ठा sk_buff *skb,
			    पूर्णांक vlan_id_key, पूर्णांक vlan_prio_key,
			    काष्ठा flow_dissector_key_vlan *vlan_key,
			    काष्ठा flow_dissector_key_vlan *vlan_mask)
अणु
	पूर्णांक err;

	अगर (!स_प्रथम_inv(vlan_mask, 0, माप(*vlan_mask)))
		वापस 0;
	अगर (vlan_mask->vlan_id) अणु
		err = nla_put_u16(skb, vlan_id_key,
				  vlan_key->vlan_id);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (vlan_mask->vlan_priority) अणु
		err = nla_put_u8(skb, vlan_prio_key,
				 vlan_key->vlan_priority);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fl_get_key_flag(u32 dissector_key, u32 dissector_mask,
			    u32 *flower_key, u32 *flower_mask,
			    u32 flower_flag_bit, u32 dissector_flag_bit)
अणु
	अगर (dissector_mask & dissector_flag_bit) अणु
		*flower_mask |= flower_flag_bit;
		अगर (dissector_key & dissector_flag_bit)
			*flower_key |= flower_flag_bit;
	पूर्ण
पूर्ण

अटल पूर्णांक fl_dump_key_flags(काष्ठा sk_buff *skb, u32 flags_key, u32 flags_mask)
अणु
	u32 key, mask;
	__be32 _key, _mask;
	पूर्णांक err;

	अगर (!स_प्रथम_inv(&flags_mask, 0, माप(flags_mask)))
		वापस 0;

	key = 0;
	mask = 0;

	fl_get_key_flag(flags_key, flags_mask, &key, &mask,
			TCA_FLOWER_KEY_FLAGS_IS_FRAGMENT, FLOW_DIS_IS_FRAGMENT);
	fl_get_key_flag(flags_key, flags_mask, &key, &mask,
			TCA_FLOWER_KEY_FLAGS_FRAG_IS_FIRST,
			FLOW_DIS_FIRST_FRAG);

	_key = cpu_to_be32(key);
	_mask = cpu_to_be32(mask);

	err = nla_put(skb, TCA_FLOWER_KEY_FLAGS, 4, &_key);
	अगर (err)
		वापस err;

	वापस nla_put(skb, TCA_FLOWER_KEY_FLAGS_MASK, 4, &_mask);
पूर्ण

अटल पूर्णांक fl_dump_key_geneve_opt(काष्ठा sk_buff *skb,
				  काष्ठा flow_dissector_key_enc_opts *enc_opts)
अणु
	काष्ठा geneve_opt *opt;
	काष्ठा nlattr *nest;
	पूर्णांक opt_off = 0;

	nest = nla_nest_start_noflag(skb, TCA_FLOWER_KEY_ENC_OPTS_GENEVE);
	अगर (!nest)
		जाओ nla_put_failure;

	जबतक (enc_opts->len > opt_off) अणु
		opt = (काष्ठा geneve_opt *)&enc_opts->data[opt_off];

		अगर (nla_put_be16(skb, TCA_FLOWER_KEY_ENC_OPT_GENEVE_CLASS,
				 opt->opt_class))
			जाओ nla_put_failure;
		अगर (nla_put_u8(skb, TCA_FLOWER_KEY_ENC_OPT_GENEVE_TYPE,
			       opt->type))
			जाओ nla_put_failure;
		अगर (nla_put(skb, TCA_FLOWER_KEY_ENC_OPT_GENEVE_DATA,
			    opt->length * 4, opt->opt_data))
			जाओ nla_put_failure;

		opt_off += माप(काष्ठा geneve_opt) + opt->length * 4;
	पूर्ण
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump_key_vxlan_opt(काष्ठा sk_buff *skb,
				 काष्ठा flow_dissector_key_enc_opts *enc_opts)
अणु
	काष्ठा vxlan_metadata *md;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_FLOWER_KEY_ENC_OPTS_VXLAN);
	अगर (!nest)
		जाओ nla_put_failure;

	md = (काष्ठा vxlan_metadata *)&enc_opts->data[0];
	अगर (nla_put_u32(skb, TCA_FLOWER_KEY_ENC_OPT_VXLAN_GBP, md->gbp))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump_key_erspan_opt(काष्ठा sk_buff *skb,
				  काष्ठा flow_dissector_key_enc_opts *enc_opts)
अणु
	काष्ठा erspan_metadata *md;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_FLOWER_KEY_ENC_OPTS_ERSPAN);
	अगर (!nest)
		जाओ nla_put_failure;

	md = (काष्ठा erspan_metadata *)&enc_opts->data[0];
	अगर (nla_put_u8(skb, TCA_FLOWER_KEY_ENC_OPT_ERSPAN_VER, md->version))
		जाओ nla_put_failure;

	अगर (md->version == 1 &&
	    nla_put_be32(skb, TCA_FLOWER_KEY_ENC_OPT_ERSPAN_INDEX, md->u.index))
		जाओ nla_put_failure;

	अगर (md->version == 2 &&
	    (nla_put_u8(skb, TCA_FLOWER_KEY_ENC_OPT_ERSPAN_सूची,
			md->u.md2.dir) ||
	     nla_put_u8(skb, TCA_FLOWER_KEY_ENC_OPT_ERSPAN_HWID,
			get_hwid(&md->u.md2))))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump_key_ct(काष्ठा sk_buff *skb,
			  काष्ठा flow_dissector_key_ct *key,
			  काष्ठा flow_dissector_key_ct *mask)
अणु
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK) &&
	    fl_dump_key_val(skb, &key->ct_state, TCA_FLOWER_KEY_CT_STATE,
			    &mask->ct_state, TCA_FLOWER_KEY_CT_STATE_MASK,
			    माप(key->ct_state)))
		जाओ nla_put_failure;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    fl_dump_key_val(skb, &key->ct_zone, TCA_FLOWER_KEY_CT_ZONE,
			    &mask->ct_zone, TCA_FLOWER_KEY_CT_ZONE_MASK,
			    माप(key->ct_zone)))
		जाओ nla_put_failure;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    fl_dump_key_val(skb, &key->ct_mark, TCA_FLOWER_KEY_CT_MARK,
			    &mask->ct_mark, TCA_FLOWER_KEY_CT_MARK_MASK,
			    माप(key->ct_mark)))
		जाओ nla_put_failure;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    fl_dump_key_val(skb, &key->ct_labels, TCA_FLOWER_KEY_CT_LABELS,
			    &mask->ct_labels, TCA_FLOWER_KEY_CT_LABELS_MASK,
			    माप(key->ct_labels)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump_key_options(काष्ठा sk_buff *skb, पूर्णांक enc_opt_type,
			       काष्ठा flow_dissector_key_enc_opts *enc_opts)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक err;

	अगर (!enc_opts->len)
		वापस 0;

	nest = nla_nest_start_noflag(skb, enc_opt_type);
	अगर (!nest)
		जाओ nla_put_failure;

	चयन (enc_opts->dst_opt_type) अणु
	हाल TUNNEL_GENEVE_OPT:
		err = fl_dump_key_geneve_opt(skb, enc_opts);
		अगर (err)
			जाओ nla_put_failure;
		अवरोध;
	हाल TUNNEL_VXLAN_OPT:
		err = fl_dump_key_vxlan_opt(skb, enc_opts);
		अगर (err)
			जाओ nla_put_failure;
		अवरोध;
	हाल TUNNEL_ERSPAN_OPT:
		err = fl_dump_key_erspan_opt(skb, enc_opts);
		अगर (err)
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump_key_enc_opt(काष्ठा sk_buff *skb,
			       काष्ठा flow_dissector_key_enc_opts *key_opts,
			       काष्ठा flow_dissector_key_enc_opts *msk_opts)
अणु
	पूर्णांक err;

	err = fl_dump_key_options(skb, TCA_FLOWER_KEY_ENC_OPTS, key_opts);
	अगर (err)
		वापस err;

	वापस fl_dump_key_options(skb, TCA_FLOWER_KEY_ENC_OPTS_MASK, msk_opts);
पूर्ण

अटल पूर्णांक fl_dump_key(काष्ठा sk_buff *skb, काष्ठा net *net,
		       काष्ठा fl_flow_key *key, काष्ठा fl_flow_key *mask)
अणु
	अगर (mask->meta.ingress_अगरindex) अणु
		काष्ठा net_device *dev;

		dev = __dev_get_by_index(net, key->meta.ingress_अगरindex);
		अगर (dev && nla_put_string(skb, TCA_FLOWER_INDEV, dev->name))
			जाओ nla_put_failure;
	पूर्ण

	अगर (fl_dump_key_val(skb, key->eth.dst, TCA_FLOWER_KEY_ETH_DST,
			    mask->eth.dst, TCA_FLOWER_KEY_ETH_DST_MASK,
			    माप(key->eth.dst)) ||
	    fl_dump_key_val(skb, key->eth.src, TCA_FLOWER_KEY_ETH_SRC,
			    mask->eth.src, TCA_FLOWER_KEY_ETH_SRC_MASK,
			    माप(key->eth.src)) ||
	    fl_dump_key_val(skb, &key->basic.n_proto, TCA_FLOWER_KEY_ETH_TYPE,
			    &mask->basic.n_proto, TCA_FLOWER_UNSPEC,
			    माप(key->basic.n_proto)))
		जाओ nla_put_failure;

	अगर (fl_dump_key_mpls(skb, &key->mpls, &mask->mpls))
		जाओ nla_put_failure;

	अगर (fl_dump_key_vlan(skb, TCA_FLOWER_KEY_VLAN_ID,
			     TCA_FLOWER_KEY_VLAN_PRIO, &key->vlan, &mask->vlan))
		जाओ nla_put_failure;

	अगर (fl_dump_key_vlan(skb, TCA_FLOWER_KEY_CVLAN_ID,
			     TCA_FLOWER_KEY_CVLAN_PRIO,
			     &key->cvlan, &mask->cvlan) ||
	    (mask->cvlan.vlan_tpid &&
	     nla_put_be16(skb, TCA_FLOWER_KEY_VLAN_ETH_TYPE,
			  key->cvlan.vlan_tpid)))
		जाओ nla_put_failure;

	अगर (mask->basic.n_proto) अणु
		अगर (mask->cvlan.vlan_tpid) अणु
			अगर (nla_put_be16(skb, TCA_FLOWER_KEY_CVLAN_ETH_TYPE,
					 key->basic.n_proto))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (mask->vlan.vlan_tpid) अणु
			अगर (nla_put_be16(skb, TCA_FLOWER_KEY_VLAN_ETH_TYPE,
					 key->basic.n_proto))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर ((key->basic.n_proto == htons(ETH_P_IP) ||
	     key->basic.n_proto == htons(ETH_P_IPV6)) &&
	    (fl_dump_key_val(skb, &key->basic.ip_proto, TCA_FLOWER_KEY_IP_PROTO,
			    &mask->basic.ip_proto, TCA_FLOWER_UNSPEC,
			    माप(key->basic.ip_proto)) ||
	    fl_dump_key_ip(skb, false, &key->ip, &mask->ip)))
		जाओ nla_put_failure;

	अगर (key->control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS &&
	    (fl_dump_key_val(skb, &key->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC,
			     &mask->ipv4.src, TCA_FLOWER_KEY_IPV4_SRC_MASK,
			     माप(key->ipv4.src)) ||
	     fl_dump_key_val(skb, &key->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST,
			     &mask->ipv4.dst, TCA_FLOWER_KEY_IPV4_DST_MASK,
			     माप(key->ipv4.dst))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS &&
		 (fl_dump_key_val(skb, &key->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC,
				  &mask->ipv6.src, TCA_FLOWER_KEY_IPV6_SRC_MASK,
				  माप(key->ipv6.src)) ||
		  fl_dump_key_val(skb, &key->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST,
				  &mask->ipv6.dst, TCA_FLOWER_KEY_IPV6_DST_MASK,
				  माप(key->ipv6.dst))))
		जाओ nla_put_failure;

	अगर (key->basic.ip_proto == IPPROTO_TCP &&
	    (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_TCP_SRC,
			     &mask->tp.src, TCA_FLOWER_KEY_TCP_SRC_MASK,
			     माप(key->tp.src)) ||
	     fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_TCP_DST,
			     &mask->tp.dst, TCA_FLOWER_KEY_TCP_DST_MASK,
			     माप(key->tp.dst)) ||
	     fl_dump_key_val(skb, &key->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS,
			     &mask->tcp.flags, TCA_FLOWER_KEY_TCP_FLAGS_MASK,
			     माप(key->tcp.flags))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->basic.ip_proto == IPPROTO_UDP &&
		 (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_UDP_SRC,
				  &mask->tp.src, TCA_FLOWER_KEY_UDP_SRC_MASK,
				  माप(key->tp.src)) ||
		  fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_UDP_DST,
				  &mask->tp.dst, TCA_FLOWER_KEY_UDP_DST_MASK,
				  माप(key->tp.dst))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->basic.ip_proto == IPPROTO_SCTP &&
		 (fl_dump_key_val(skb, &key->tp.src, TCA_FLOWER_KEY_SCTP_SRC,
				  &mask->tp.src, TCA_FLOWER_KEY_SCTP_SRC_MASK,
				  माप(key->tp.src)) ||
		  fl_dump_key_val(skb, &key->tp.dst, TCA_FLOWER_KEY_SCTP_DST,
				  &mask->tp.dst, TCA_FLOWER_KEY_SCTP_DST_MASK,
				  माप(key->tp.dst))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->basic.n_proto == htons(ETH_P_IP) &&
		 key->basic.ip_proto == IPPROTO_ICMP &&
		 (fl_dump_key_val(skb, &key->icmp.type,
				  TCA_FLOWER_KEY_ICMPV4_TYPE, &mask->icmp.type,
				  TCA_FLOWER_KEY_ICMPV4_TYPE_MASK,
				  माप(key->icmp.type)) ||
		  fl_dump_key_val(skb, &key->icmp.code,
				  TCA_FLOWER_KEY_ICMPV4_CODE, &mask->icmp.code,
				  TCA_FLOWER_KEY_ICMPV4_CODE_MASK,
				  माप(key->icmp.code))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->basic.n_proto == htons(ETH_P_IPV6) &&
		 key->basic.ip_proto == IPPROTO_ICMPV6 &&
		 (fl_dump_key_val(skb, &key->icmp.type,
				  TCA_FLOWER_KEY_ICMPV6_TYPE, &mask->icmp.type,
				  TCA_FLOWER_KEY_ICMPV6_TYPE_MASK,
				  माप(key->icmp.type)) ||
		  fl_dump_key_val(skb, &key->icmp.code,
				  TCA_FLOWER_KEY_ICMPV6_CODE, &mask->icmp.code,
				  TCA_FLOWER_KEY_ICMPV6_CODE_MASK,
				  माप(key->icmp.code))))
		जाओ nla_put_failure;
	अन्यथा अगर ((key->basic.n_proto == htons(ETH_P_ARP) ||
		  key->basic.n_proto == htons(ETH_P_RARP)) &&
		 (fl_dump_key_val(skb, &key->arp.sip,
				  TCA_FLOWER_KEY_ARP_SIP, &mask->arp.sip,
				  TCA_FLOWER_KEY_ARP_SIP_MASK,
				  माप(key->arp.sip)) ||
		  fl_dump_key_val(skb, &key->arp.tip,
				  TCA_FLOWER_KEY_ARP_TIP, &mask->arp.tip,
				  TCA_FLOWER_KEY_ARP_TIP_MASK,
				  माप(key->arp.tip)) ||
		  fl_dump_key_val(skb, &key->arp.op,
				  TCA_FLOWER_KEY_ARP_OP, &mask->arp.op,
				  TCA_FLOWER_KEY_ARP_OP_MASK,
				  माप(key->arp.op)) ||
		  fl_dump_key_val(skb, key->arp.sha, TCA_FLOWER_KEY_ARP_SHA,
				  mask->arp.sha, TCA_FLOWER_KEY_ARP_SHA_MASK,
				  माप(key->arp.sha)) ||
		  fl_dump_key_val(skb, key->arp.tha, TCA_FLOWER_KEY_ARP_THA,
				  mask->arp.tha, TCA_FLOWER_KEY_ARP_THA_MASK,
				  माप(key->arp.tha))))
		जाओ nla_put_failure;

	अगर ((key->basic.ip_proto == IPPROTO_TCP ||
	     key->basic.ip_proto == IPPROTO_UDP ||
	     key->basic.ip_proto == IPPROTO_SCTP) &&
	     fl_dump_key_port_range(skb, key, mask))
		जाओ nla_put_failure;

	अगर (key->enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS &&
	    (fl_dump_key_val(skb, &key->enc_ipv4.src,
			    TCA_FLOWER_KEY_ENC_IPV4_SRC, &mask->enc_ipv4.src,
			    TCA_FLOWER_KEY_ENC_IPV4_SRC_MASK,
			    माप(key->enc_ipv4.src)) ||
	     fl_dump_key_val(skb, &key->enc_ipv4.dst,
			     TCA_FLOWER_KEY_ENC_IPV4_DST, &mask->enc_ipv4.dst,
			     TCA_FLOWER_KEY_ENC_IPV4_DST_MASK,
			     माप(key->enc_ipv4.dst))))
		जाओ nla_put_failure;
	अन्यथा अगर (key->enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS &&
		 (fl_dump_key_val(skb, &key->enc_ipv6.src,
			    TCA_FLOWER_KEY_ENC_IPV6_SRC, &mask->enc_ipv6.src,
			    TCA_FLOWER_KEY_ENC_IPV6_SRC_MASK,
			    माप(key->enc_ipv6.src)) ||
		 fl_dump_key_val(skb, &key->enc_ipv6.dst,
				 TCA_FLOWER_KEY_ENC_IPV6_DST,
				 &mask->enc_ipv6.dst,
				 TCA_FLOWER_KEY_ENC_IPV6_DST_MASK,
			    माप(key->enc_ipv6.dst))))
		जाओ nla_put_failure;

	अगर (fl_dump_key_val(skb, &key->enc_key_id, TCA_FLOWER_KEY_ENC_KEY_ID,
			    &mask->enc_key_id, TCA_FLOWER_UNSPEC,
			    माप(key->enc_key_id)) ||
	    fl_dump_key_val(skb, &key->enc_tp.src,
			    TCA_FLOWER_KEY_ENC_UDP_SRC_PORT,
			    &mask->enc_tp.src,
			    TCA_FLOWER_KEY_ENC_UDP_SRC_PORT_MASK,
			    माप(key->enc_tp.src)) ||
	    fl_dump_key_val(skb, &key->enc_tp.dst,
			    TCA_FLOWER_KEY_ENC_UDP_DST_PORT,
			    &mask->enc_tp.dst,
			    TCA_FLOWER_KEY_ENC_UDP_DST_PORT_MASK,
			    माप(key->enc_tp.dst)) ||
	    fl_dump_key_ip(skb, true, &key->enc_ip, &mask->enc_ip) ||
	    fl_dump_key_enc_opt(skb, &key->enc_opts, &mask->enc_opts))
		जाओ nla_put_failure;

	अगर (fl_dump_key_ct(skb, &key->ct, &mask->ct))
		जाओ nla_put_failure;

	अगर (fl_dump_key_flags(skb, key->control.flags, mask->control.flags))
		जाओ nla_put_failure;

	अगर (fl_dump_key_val(skb, &key->hash.hash, TCA_FLOWER_KEY_HASH,
			     &mask->hash.hash, TCA_FLOWER_KEY_HASH_MASK,
			     माप(key->hash.hash)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fl_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		   काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा cls_fl_filter *f = fh;
	काष्ठा nlattr *nest;
	काष्ठा fl_flow_key *key, *mask;
	bool skip_hw;

	अगर (!f)
		वापस skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	spin_lock(&tp->lock);

	अगर (f->res.classid &&
	    nla_put_u32(skb, TCA_FLOWER_CLASSID, f->res.classid))
		जाओ nla_put_failure_locked;

	key = &f->key;
	mask = &f->mask->key;
	skip_hw = tc_skip_hw(f->flags);

	अगर (fl_dump_key(skb, net, key, mask))
		जाओ nla_put_failure_locked;

	अगर (f->flags && nla_put_u32(skb, TCA_FLOWER_FLAGS, f->flags))
		जाओ nla_put_failure_locked;

	spin_unlock(&tp->lock);

	अगर (!skip_hw)
		fl_hw_update_stats(tp, f, rtnl_held);

	अगर (nla_put_u32(skb, TCA_FLOWER_IN_HW_COUNT, f->in_hw_count))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure_locked:
	spin_unlock(&tp->lock);
nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक fl_terse_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
			 काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा cls_fl_filter *f = fh;
	काष्ठा nlattr *nest;
	bool skip_hw;

	अगर (!f)
		वापस skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	spin_lock(&tp->lock);

	skip_hw = tc_skip_hw(f->flags);

	अगर (f->flags && nla_put_u32(skb, TCA_FLOWER_FLAGS, f->flags))
		जाओ nla_put_failure_locked;

	spin_unlock(&tp->lock);

	अगर (!skip_hw)
		fl_hw_update_stats(tp, f, rtnl_held);

	अगर (tcf_exts_terse_dump(skb, &f->exts))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	वापस skb->len;

nla_put_failure_locked:
	spin_unlock(&tp->lock);
nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक fl_पंचांगplt_dump(काष्ठा sk_buff *skb, काष्ठा net *net, व्योम *पंचांगplt_priv)
अणु
	काष्ठा fl_flow_पंचांगplt *पंचांगplt = पंचांगplt_priv;
	काष्ठा fl_flow_key *key, *mask;
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (!nest)
		जाओ nla_put_failure;

	key = &पंचांगplt->dummy_key;
	mask = &पंचांगplt->mask;

	अगर (fl_dump_key(skb, net, key, mask))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम fl_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			  अचिन्हित दीर्घ base)
अणु
	काष्ठा cls_fl_filter *f = fh;

	अगर (f && f->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &f->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &f->res);
	पूर्ण
पूर्ण

अटल bool fl_delete_empty(काष्ठा tcf_proto *tp)
अणु
	काष्ठा cls_fl_head *head = fl_head_dereference(tp);

	spin_lock(&tp->lock);
	tp->deleting = idr_is_empty(&head->handle_idr);
	spin_unlock(&tp->lock);

	वापस tp->deleting;
पूर्ण

अटल काष्ठा tcf_proto_ops cls_fl_ops __पढ़ो_mostly = अणु
	.kind		= "flower",
	.classअगरy	= fl_classअगरy,
	.init		= fl_init,
	.destroy	= fl_destroy,
	.get		= fl_get,
	.put		= fl_put,
	.change		= fl_change,
	.delete		= fl_delete,
	.delete_empty	= fl_delete_empty,
	.walk		= fl_walk,
	.reoffload	= fl_reoffload,
	.hw_add		= fl_hw_add,
	.hw_del		= fl_hw_del,
	.dump		= fl_dump,
	.terse_dump	= fl_terse_dump,
	.bind_class	= fl_bind_class,
	.पंचांगplt_create	= fl_पंचांगplt_create,
	.पंचांगplt_destroy	= fl_पंचांगplt_destroy,
	.पंचांगplt_dump	= fl_पंचांगplt_dump,
	.owner		= THIS_MODULE,
	.flags		= TCF_PROTO_OPS_DOIT_UNLOCKED,
पूर्ण;

अटल पूर्णांक __init cls_fl_init(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_fl_ops);
पूर्ण

अटल व्योम __निकास cls_fl_निकास(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_fl_ops);
पूर्ण

module_init(cls_fl_init);
module_निकास(cls_fl_निकास);

MODULE_AUTHOR("Jiri Pirko <jiri@resnulli.us>");
MODULE_DESCRIPTION("Flower classifier");
MODULE_LICENSE("GPL v2");
