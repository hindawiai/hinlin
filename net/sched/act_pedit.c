<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_pedit.c	Generic packet editor
 *
 * Authors:	Jamal Hadi Salim (2002-4)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <uapi/linux/tc_act/tc_pedit.h>
#समावेश <net/pkt_cls.h>

अटल अचिन्हित पूर्णांक pedit_net_id;
अटल काष्ठा tc_action_ops act_pedit_ops;

अटल स्थिर काष्ठा nla_policy pedit_policy[TCA_PEDIT_MAX + 1] = अणु
	[TCA_PEDIT_PARMS]	= अणु .len = माप(काष्ठा tc_pedit) पूर्ण,
	[TCA_PEDIT_KEYS_EX]   = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy pedit_key_ex_policy[TCA_PEDIT_KEY_EX_MAX + 1] = अणु
	[TCA_PEDIT_KEY_EX_HTYPE]  = अणु .type = NLA_U16 पूर्ण,
	[TCA_PEDIT_KEY_EX_CMD]	  = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल काष्ठा tcf_pedit_key_ex *tcf_pedit_keys_ex_parse(काष्ठा nlattr *nla,
							u8 n)
अणु
	काष्ठा tcf_pedit_key_ex *keys_ex;
	काष्ठा tcf_pedit_key_ex *k;
	स्थिर काष्ठा nlattr *ka;
	पूर्णांक err = -EINVAL;
	पूर्णांक rem;

	अगर (!nla)
		वापस शून्य;

	keys_ex = kसुस्मृति(n, माप(*k), GFP_KERNEL);
	अगर (!keys_ex)
		वापस ERR_PTR(-ENOMEM);

	k = keys_ex;

	nla_क्रम_each_nested(ka, nla, rem) अणु
		काष्ठा nlattr *tb[TCA_PEDIT_KEY_EX_MAX + 1];

		अगर (!n) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
		n--;

		अगर (nla_type(ka) != TCA_PEDIT_KEY_EX) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण

		err = nla_parse_nested_deprecated(tb, TCA_PEDIT_KEY_EX_MAX,
						  ka, pedit_key_ex_policy,
						  शून्य);
		अगर (err)
			जाओ err_out;

		अगर (!tb[TCA_PEDIT_KEY_EX_HTYPE] ||
		    !tb[TCA_PEDIT_KEY_EX_CMD]) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण

		k->htype = nla_get_u16(tb[TCA_PEDIT_KEY_EX_HTYPE]);
		k->cmd = nla_get_u16(tb[TCA_PEDIT_KEY_EX_CMD]);

		अगर (k->htype > TCA_PEDIT_HDR_TYPE_MAX ||
		    k->cmd > TCA_PEDIT_CMD_MAX) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण

		k++;
	पूर्ण

	अगर (n) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	वापस keys_ex;

err_out:
	kमुक्त(keys_ex);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक tcf_pedit_key_ex_dump(काष्ठा sk_buff *skb,
				 काष्ठा tcf_pedit_key_ex *keys_ex, पूर्णांक n)
अणु
	काष्ठा nlattr *keys_start = nla_nest_start_noflag(skb,
							  TCA_PEDIT_KEYS_EX);

	अगर (!keys_start)
		जाओ nla_failure;
	क्रम (; n > 0; n--) अणु
		काष्ठा nlattr *key_start;

		key_start = nla_nest_start_noflag(skb, TCA_PEDIT_KEY_EX);
		अगर (!key_start)
			जाओ nla_failure;

		अगर (nla_put_u16(skb, TCA_PEDIT_KEY_EX_HTYPE, keys_ex->htype) ||
		    nla_put_u16(skb, TCA_PEDIT_KEY_EX_CMD, keys_ex->cmd))
			जाओ nla_failure;

		nla_nest_end(skb, key_start);

		keys_ex++;
	पूर्ण

	nla_nest_end(skb, keys_start);

	वापस 0;
nla_failure:
	nla_nest_cancel(skb, keys_start);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tcf_pedit_init(काष्ठा net *net, काष्ठा nlattr *nla,
			  काष्ठा nlattr *est, काष्ठा tc_action **a,
			  पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			  काष्ठा tcf_proto *tp, u32 flags,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, pedit_net_id);
	काष्ठा nlattr *tb[TCA_PEDIT_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_pedit_key *keys = शून्य;
	काष्ठा tcf_pedit_key_ex *keys_ex;
	काष्ठा tc_pedit *parm;
	काष्ठा nlattr *pattr;
	काष्ठा tcf_pedit *p;
	पूर्णांक ret = 0, err;
	पूर्णांक ksize;
	u32 index;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "Pedit requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_PEDIT_MAX, nla,
					  pedit_policy, शून्य);
	अगर (err < 0)
		वापस err;

	pattr = tb[TCA_PEDIT_PARMS];
	अगर (!pattr)
		pattr = tb[TCA_PEDIT_PARMS_EX];
	अगर (!pattr) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing required TCA_PEDIT_PARMS or TCA_PEDIT_PARMS_EX pedit attribute");
		वापस -EINVAL;
	पूर्ण

	parm = nla_data(pattr);
	अगर (!parm->nkeys) अणु
		NL_SET_ERR_MSG_MOD(extack, "Pedit requires keys to be passed");
		वापस -EINVAL;
	पूर्ण
	ksize = parm->nkeys * माप(काष्ठा tc_pedit_key);
	अगर (nla_len(pattr) < माप(*parm) + ksize) अणु
		NL_SET_ERR_MSG_ATTR(extack, pattr, "Length of TCA_PEDIT_PARMS or TCA_PEDIT_PARMS_EX pedit attribute is invalid");
		वापस -EINVAL;
	पूर्ण

	keys_ex = tcf_pedit_keys_ex_parse(tb[TCA_PEDIT_KEYS_EX], parm->nkeys);
	अगर (IS_ERR(keys_ex))
		वापस PTR_ERR(keys_ex);

	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!err) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_pedit_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			जाओ out_मुक्त;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (err > 0) अणु
		अगर (bind)
			जाओ out_मुक्त;
		अगर (!ovr) अणु
			ret = -EEXIST;
			जाओ out_release;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = err;
		जाओ out_मुक्त;
	पूर्ण

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0) अणु
		ret = err;
		जाओ out_release;
	पूर्ण
	p = to_pedit(*a);
	spin_lock_bh(&p->tcf_lock);

	अगर (ret == ACT_P_CREATED ||
	    (p->tcfp_nkeys && p->tcfp_nkeys != parm->nkeys)) अणु
		keys = kदो_स्मृति(ksize, GFP_ATOMIC);
		अगर (!keys) अणु
			spin_unlock_bh(&p->tcf_lock);
			ret = -ENOMEM;
			जाओ put_chain;
		पूर्ण
		kमुक्त(p->tcfp_keys);
		p->tcfp_keys = keys;
		p->tcfp_nkeys = parm->nkeys;
	पूर्ण
	स_नकल(p->tcfp_keys, parm->keys, ksize);

	p->tcfp_flags = parm->flags;
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);

	kमुक्त(p->tcfp_keys_ex);
	p->tcfp_keys_ex = keys_ex;

	spin_unlock_bh(&p->tcf_lock);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	वापस ret;

put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
out_release:
	tcf_idr_release(*a, bind);
out_मुक्त:
	kमुक्त(keys_ex);
	वापस ret;

पूर्ण

अटल व्योम tcf_pedit_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_pedit *p = to_pedit(a);
	काष्ठा tc_pedit_key *keys = p->tcfp_keys;

	kमुक्त(keys);
	kमुक्त(p->tcfp_keys_ex);
पूर्ण

अटल bool offset_valid(काष्ठा sk_buff *skb, पूर्णांक offset)
अणु
	अगर (offset > 0 && offset > skb->len)
		वापस false;

	अगर  (offset < 0 && -offset > skb_headroom(skb))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक pedit_skb_hdr_offset(काष्ठा sk_buff *skb,
				क्रमागत pedit_header_type htype, पूर्णांक *hoffset)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (htype) अणु
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_ETH:
		अगर (skb_mac_header_was_set(skb)) अणु
			*hoffset = skb_mac_offset(skb);
			ret = 0;
		पूर्ण
		अवरोध;
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK:
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_IP4:
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_IP6:
		*hoffset = skb_network_offset(skb);
		ret = 0;
		अवरोध;
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_TCP:
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_UDP:
		अगर (skb_transport_header_was_set(skb)) अणु
			*hoffset = skb_transport_offset(skb);
			ret = 0;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tcf_pedit_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			 काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_pedit *p = to_pedit(a);
	पूर्णांक i;

	अगर (skb_unclone(skb, GFP_ATOMIC))
		वापस p->tcf_action;

	spin_lock(&p->tcf_lock);

	tcf_lastuse_update(&p->tcf_पंचांग);

	अगर (p->tcfp_nkeys > 0) अणु
		काष्ठा tc_pedit_key *tkey = p->tcfp_keys;
		काष्ठा tcf_pedit_key_ex *tkey_ex = p->tcfp_keys_ex;
		क्रमागत pedit_header_type htype =
			TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK;
		क्रमागत pedit_cmd cmd = TCA_PEDIT_KEY_EX_CMD_SET;

		क्रम (i = p->tcfp_nkeys; i > 0; i--, tkey++) अणु
			u32 *ptr, hdata;
			पूर्णांक offset = tkey->off;
			पूर्णांक hoffset;
			u32 val;
			पूर्णांक rc;

			अगर (tkey_ex) अणु
				htype = tkey_ex->htype;
				cmd = tkey_ex->cmd;

				tkey_ex++;
			पूर्ण

			rc = pedit_skb_hdr_offset(skb, htype, &hoffset);
			अगर (rc) अणु
				pr_info("tc action pedit bad header type specified (0x%x)\n",
					htype);
				जाओ bad;
			पूर्ण

			अगर (tkey->offmask) अणु
				u8 *d, _d;

				अगर (!offset_valid(skb, hoffset + tkey->at)) अणु
					pr_info("tc action pedit 'at' offset %d out of bounds\n",
						hoffset + tkey->at);
					जाओ bad;
				पूर्ण
				d = skb_header_poपूर्णांकer(skb, hoffset + tkey->at,
						       माप(_d), &_d);
				अगर (!d)
					जाओ bad;
				offset += (*d & tkey->offmask) >> tkey->shअगरt;
			पूर्ण

			अगर (offset % 4) अणु
				pr_info("tc action pedit offset must be on 32 bit boundaries\n");
				जाओ bad;
			पूर्ण

			अगर (!offset_valid(skb, hoffset + offset)) अणु
				pr_info("tc action pedit offset %d out of bounds\n",
					hoffset + offset);
				जाओ bad;
			पूर्ण

			ptr = skb_header_poपूर्णांकer(skb, hoffset + offset,
						 माप(hdata), &hdata);
			अगर (!ptr)
				जाओ bad;
			/* just करो it, baby */
			चयन (cmd) अणु
			हाल TCA_PEDIT_KEY_EX_CMD_SET:
				val = tkey->val;
				अवरोध;
			हाल TCA_PEDIT_KEY_EX_CMD_ADD:
				val = (*ptr + tkey->val) & ~tkey->mask;
				अवरोध;
			शेष:
				pr_info("tc action pedit bad command (%d)\n",
					cmd);
				जाओ bad;
			पूर्ण

			*ptr = ((*ptr & tkey->mask) ^ val);
			अगर (ptr == &hdata)
				skb_store_bits(skb, hoffset + offset, ptr, 4);
		पूर्ण

		जाओ करोne;
	पूर्ण अन्यथा अणु
		WARN(1, "pedit BUG: index %d\n", p->tcf_index);
	पूर्ण

bad:
	p->tcf_qstats.overlimits++;
करोne:
	bstats_update(&p->tcf_bstats, skb);
	spin_unlock(&p->tcf_lock);
	वापस p->tcf_action;
पूर्ण

अटल व्योम tcf_pedit_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
				   u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_pedit *d = to_pedit(a);
	काष्ठा tcf_t *पंचांग = &d->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_pedit_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			  पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_pedit *p = to_pedit(a);
	काष्ठा tc_pedit *opt;
	काष्ठा tcf_t t;
	पूर्णांक s;

	s = काष्ठा_size(opt, keys, p->tcfp_nkeys);

	/* netlink spinlocks held above us - must use ATOMIC */
	opt = kzalloc(s, GFP_ATOMIC);
	अगर (unlikely(!opt))
		वापस -ENOBUFS;

	spin_lock_bh(&p->tcf_lock);
	स_नकल(opt->keys, p->tcfp_keys, flex_array_size(opt, keys, p->tcfp_nkeys));
	opt->index = p->tcf_index;
	opt->nkeys = p->tcfp_nkeys;
	opt->flags = p->tcfp_flags;
	opt->action = p->tcf_action;
	opt->refcnt = refcount_पढ़ो(&p->tcf_refcnt) - ref;
	opt->bindcnt = atomic_पढ़ो(&p->tcf_bindcnt) - bind;

	अगर (p->tcfp_keys_ex) अणु
		अगर (tcf_pedit_key_ex_dump(skb,
					  p->tcfp_keys_ex,
					  p->tcfp_nkeys))
			जाओ nla_put_failure;

		अगर (nla_put(skb, TCA_PEDIT_PARMS_EX, s, opt))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		अगर (nla_put(skb, TCA_PEDIT_PARMS, s, opt))
			जाओ nla_put_failure;
	पूर्ण

	tcf_पंचांग_dump(&t, &p->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_PEDIT_TM, माप(t), &t, TCA_PEDIT_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&p->tcf_lock);

	kमुक्त(opt);
	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&p->tcf_lock);
	nlmsg_trim(skb, b);
	kमुक्त(opt);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_pedit_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb, पूर्णांक type,
			    स्थिर काष्ठा tc_action_ops *ops,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, pedit_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_pedit_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, pedit_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_pedit_ops = अणु
	.kind		=	"pedit",
	.id		=	TCA_ID_PEDIT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_pedit_act,
	.stats_update	=	tcf_pedit_stats_update,
	.dump		=	tcf_pedit_dump,
	.cleanup	=	tcf_pedit_cleanup,
	.init		=	tcf_pedit_init,
	.walk		=	tcf_pedit_walker,
	.lookup		=	tcf_pedit_search,
	.size		=	माप(काष्ठा tcf_pedit),
पूर्ण;

अटल __net_init पूर्णांक pedit_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, pedit_net_id);

	वापस tc_action_net_init(net, tn, &act_pedit_ops);
पूर्ण

अटल व्योम __net_निकास pedit_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, pedit_net_id);
पूर्ण

अटल काष्ठा pernet_operations pedit_net_ops = अणु
	.init = pedit_init_net,
	.निकास_batch = pedit_निकास_net,
	.id   = &pedit_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim(2002-4)");
MODULE_DESCRIPTION("Generic Packet Editor actions");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init pedit_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_pedit_ops, &pedit_net_ops);
पूर्ण

अटल व्योम __निकास pedit_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_pedit_ops, &pedit_net_ops);
पूर्ण

module_init(pedit_init_module);
module_निकास(pedit_cleanup_module);
