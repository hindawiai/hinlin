<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/अगरe.c	Inter-FE action based on ForCES WG InterFE LFB
 *
 *		Refer to:
 *		draft-ietf-क्रमces-पूर्णांकerfelfb-03
 *		and
 *		netdev01 paper:
 *		"Distributing Linux Traffic Control Classअगरier-Action
 *		Subप्रणाली"
 *		Authors: Jamal Hadi Salim and Damascene M. Joachimpillai
 *
 * copyright Jamal Hadi Salim (2015)
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <uapi/linux/tc_act/tc_अगरe.h>
#समावेश <net/tc_act/tc_अगरe.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/अगरe.h>

अटल अचिन्हित पूर्णांक अगरe_net_id;
अटल पूर्णांक max_metacnt = IFE_META_MAX + 1;
अटल काष्ठा tc_action_ops act_अगरe_ops;

अटल स्थिर काष्ठा nla_policy अगरe_policy[TCA_IFE_MAX + 1] = अणु
	[TCA_IFE_PARMS] = अणु .len = माप(काष्ठा tc_अगरe)पूर्ण,
	[TCA_IFE_DMAC] = अणु .len = ETH_ALENपूर्ण,
	[TCA_IFE_SMAC] = अणु .len = ETH_ALENपूर्ण,
	[TCA_IFE_TYPE] = अणु .type = NLA_U16पूर्ण,
पूर्ण;

पूर्णांक अगरe_encode_meta_u16(u16 metaval, व्योम *skbdata, काष्ठा tcf_meta_info *mi)
अणु
	u16 edata = 0;

	अगर (mi->metaval)
		edata = *(u16 *)mi->metaval;
	अन्यथा अगर (metaval)
		edata = metaval;

	अगर (!edata) /* will not encode */
		वापस 0;

	edata = htons(edata);
	वापस अगरe_tlv_meta_encode(skbdata, mi->metaid, 2, &edata);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_encode_meta_u16);

पूर्णांक अगरe_get_meta_u32(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *mi)
अणु
	अगर (mi->metaval)
		वापस nla_put_u32(skb, mi->metaid, *(u32 *)mi->metaval);
	अन्यथा
		वापस nla_put(skb, mi->metaid, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_get_meta_u32);

पूर्णांक अगरe_check_meta_u32(u32 metaval, काष्ठा tcf_meta_info *mi)
अणु
	अगर (metaval || mi->metaval)
		वापस 8; /* T+L+V == 2+2+4 */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_check_meta_u32);

पूर्णांक अगरe_check_meta_u16(u16 metaval, काष्ठा tcf_meta_info *mi)
अणु
	अगर (metaval || mi->metaval)
		वापस 8; /* T+L+(V) == 2+2+(2+2bytepad) */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_check_meta_u16);

पूर्णांक अगरe_encode_meta_u32(u32 metaval, व्योम *skbdata, काष्ठा tcf_meta_info *mi)
अणु
	u32 edata = metaval;

	अगर (mi->metaval)
		edata = *(u32 *)mi->metaval;
	अन्यथा अगर (metaval)
		edata = metaval;

	अगर (!edata) /* will not encode */
		वापस 0;

	edata = htonl(edata);
	वापस अगरe_tlv_meta_encode(skbdata, mi->metaid, 4, &edata);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_encode_meta_u32);

पूर्णांक अगरe_get_meta_u16(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *mi)
अणु
	अगर (mi->metaval)
		वापस nla_put_u16(skb, mi->metaid, *(u16 *)mi->metaval);
	अन्यथा
		वापस nla_put(skb, mi->metaid, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_get_meta_u16);

पूर्णांक अगरe_alloc_meta_u32(काष्ठा tcf_meta_info *mi, व्योम *metaval, gfp_t gfp)
अणु
	mi->metaval = kmemdup(metaval, माप(u32), gfp);
	अगर (!mi->metaval)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_alloc_meta_u32);

पूर्णांक अगरe_alloc_meta_u16(काष्ठा tcf_meta_info *mi, व्योम *metaval, gfp_t gfp)
अणु
	mi->metaval = kmemdup(metaval, माप(u16), gfp);
	अगर (!mi->metaval)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_alloc_meta_u16);

व्योम अगरe_release_meta_gen(काष्ठा tcf_meta_info *mi)
अणु
	kमुक्त(mi->metaval);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_release_meta_gen);

पूर्णांक अगरe_validate_meta_u32(व्योम *val, पूर्णांक len)
अणु
	अगर (len == माप(u32))
		वापस 0;

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_validate_meta_u32);

पूर्णांक अगरe_validate_meta_u16(व्योम *val, पूर्णांक len)
अणु
	/* length will not include padding */
	अगर (len == माप(u16))
		वापस 0;

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_validate_meta_u16);

अटल LIST_HEAD(अगरeoplist);
अटल DEFINE_RWLOCK(अगरe_mod_lock);

अटल काष्ठा tcf_meta_ops *find_अगरe_oplist(u16 metaid)
अणु
	काष्ठा tcf_meta_ops *o;

	पढ़ो_lock(&अगरe_mod_lock);
	list_क्रम_each_entry(o, &अगरeoplist, list) अणु
		अगर (o->metaid == metaid) अणु
			अगर (!try_module_get(o->owner))
				o = शून्य;
			पढ़ो_unlock(&अगरe_mod_lock);
			वापस o;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&अगरe_mod_lock);

	वापस शून्य;
पूर्ण

पूर्णांक रेजिस्टर_अगरe_op(काष्ठा tcf_meta_ops *mops)
अणु
	काष्ठा tcf_meta_ops *m;

	अगर (!mops->metaid || !mops->metatype || !mops->name ||
	    !mops->check_presence || !mops->encode || !mops->decode ||
	    !mops->get || !mops->alloc)
		वापस -EINVAL;

	ग_लिखो_lock(&अगरe_mod_lock);

	list_क्रम_each_entry(m, &अगरeoplist, list) अणु
		अगर (m->metaid == mops->metaid ||
		    (म_भेद(mops->name, m->name) == 0)) अणु
			ग_लिखो_unlock(&अगरe_mod_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	अगर (!mops->release)
		mops->release = अगरe_release_meta_gen;

	list_add_tail(&mops->list, &अगरeoplist);
	ग_लिखो_unlock(&अगरe_mod_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_अगरe_op);

पूर्णांक unरेजिस्टर_अगरe_op(काष्ठा tcf_meta_ops *mops)
अणु
	काष्ठा tcf_meta_ops *m;
	पूर्णांक err = -ENOENT;

	ग_लिखो_lock(&अगरe_mod_lock);
	list_क्रम_each_entry(m, &अगरeoplist, list) अणु
		अगर (m->metaid == mops->metaid) अणु
			list_del(&mops->list);
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&अगरe_mod_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_अगरe_op);

अटल पूर्णांक अगरe_validate_metatype(काष्ठा tcf_meta_ops *ops, व्योम *val, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	/* XXX: unक्रमtunately cant use nla_policy at this poपूर्णांक
	* because a length of 0 is valid in the हाल of
	* "allow". "use" semantics करो enक्रमce क्रम proper
	* length and i couldve use nla_policy but it makes it hard
	* to use it just क्रम that..
	*/
	अगर (ops->validate)
		वापस ops->validate(val, len);

	अगर (ops->metatype == NLA_U32)
		ret = अगरe_validate_meta_u32(val, len);
	अन्यथा अगर (ops->metatype == NLA_U16)
		ret = अगरe_validate_meta_u16(val, len);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल स्थिर अक्षर *अगरe_meta_id2name(u32 metaid)
अणु
	चयन (metaid) अणु
	हाल IFE_META_SKBMARK:
		वापस "skbmark";
	हाल IFE_META_PRIO:
		वापस "skbprio";
	हाल IFE_META_TCINDEX:
		वापस "tcindex";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* called when adding new meta inक्रमmation
*/
अटल पूर्णांक load_metaops_and_vet(u32 metaid, व्योम *val, पूर्णांक len, bool rtnl_held)
अणु
	काष्ठा tcf_meta_ops *ops = find_अगरe_oplist(metaid);
	पूर्णांक ret = 0;

	अगर (!ops) अणु
		ret = -ENOENT;
#अगर_घोषित CONFIG_MODULES
		अगर (rtnl_held)
			rtnl_unlock();
		request_module("ife-meta-%s", अगरe_meta_id2name(metaid));
		अगर (rtnl_held)
			rtnl_lock();
		ops = find_अगरe_oplist(metaid);
#पूर्ण_अगर
	पूर्ण

	अगर (ops) अणु
		ret = 0;
		अगर (len)
			ret = अगरe_validate_metatype(ops, val, len);

		module_put(ops->owner);
	पूर्ण

	वापस ret;
पूर्ण

/* called when adding new meta inक्रमmation
*/
अटल पूर्णांक __add_metainfo(स्थिर काष्ठा tcf_meta_ops *ops,
			  काष्ठा tcf_अगरe_info *अगरe, u32 metaid, व्योम *metaval,
			  पूर्णांक len, bool atomic, bool exists)
अणु
	काष्ठा tcf_meta_info *mi = शून्य;
	पूर्णांक ret = 0;

	mi = kzalloc(माप(*mi), atomic ? GFP_ATOMIC : GFP_KERNEL);
	अगर (!mi)
		वापस -ENOMEM;

	mi->metaid = metaid;
	mi->ops = ops;
	अगर (len > 0) अणु
		ret = ops->alloc(mi, metaval, atomic ? GFP_ATOMIC : GFP_KERNEL);
		अगर (ret != 0) अणु
			kमुक्त(mi);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (exists)
		spin_lock_bh(&अगरe->tcf_lock);
	list_add_tail(&mi->metalist, &अगरe->metalist);
	अगर (exists)
		spin_unlock_bh(&अगरe->tcf_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक add_metainfo_and_get_ops(स्थिर काष्ठा tcf_meta_ops *ops,
				    काष्ठा tcf_अगरe_info *अगरe, u32 metaid,
				    bool exists)
अणु
	पूर्णांक ret;

	अगर (!try_module_get(ops->owner))
		वापस -ENOENT;
	ret = __add_metainfo(ops, अगरe, metaid, शून्य, 0, true, exists);
	अगर (ret)
		module_put(ops->owner);
	वापस ret;
पूर्ण

अटल पूर्णांक add_metainfo(काष्ठा tcf_अगरe_info *अगरe, u32 metaid, व्योम *metaval,
			पूर्णांक len, bool exists)
अणु
	स्थिर काष्ठा tcf_meta_ops *ops = find_अगरe_oplist(metaid);
	पूर्णांक ret;

	अगर (!ops)
		वापस -ENOENT;
	ret = __add_metainfo(ops, अगरe, metaid, metaval, len, false, exists);
	अगर (ret)
		/*put back what find_अगरe_oplist took */
		module_put(ops->owner);
	वापस ret;
पूर्ण

अटल पूर्णांक use_all_metadata(काष्ठा tcf_अगरe_info *अगरe, bool exists)
अणु
	काष्ठा tcf_meta_ops *o;
	पूर्णांक rc = 0;
	पूर्णांक installed = 0;

	पढ़ो_lock(&अगरe_mod_lock);
	list_क्रम_each_entry(o, &अगरeoplist, list) अणु
		rc = add_metainfo_and_get_ops(o, अगरe, o->metaid, exists);
		अगर (rc == 0)
			installed += 1;
	पूर्ण
	पढ़ो_unlock(&अगरe_mod_lock);

	अगर (installed)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक dump_metalist(काष्ठा sk_buff *skb, काष्ठा tcf_अगरe_info *अगरe)
अणु
	काष्ठा tcf_meta_info *e;
	काष्ठा nlattr *nest;
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	पूर्णांक total_encoded = 0;

	/*can only happen on decode */
	अगर (list_empty(&अगरe->metalist))
		वापस 0;

	nest = nla_nest_start_noflag(skb, TCA_IFE_METALST);
	अगर (!nest)
		जाओ out_nlmsg_trim;

	list_क्रम_each_entry(e, &अगरe->metalist, metalist) अणु
		अगर (!e->ops->get(skb, e))
			total_encoded += 1;
	पूर्ण

	अगर (!total_encoded)
		जाओ out_nlmsg_trim;

	nla_nest_end(skb, nest);

	वापस 0;

out_nlmsg_trim:
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

/* under अगरe->tcf_lock */
अटल व्योम _tcf_अगरe_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	काष्ठा tcf_meta_info *e, *n;

	list_क्रम_each_entry_safe(e, n, &अगरe->metalist, metalist) अणु
		list_del(&e->metalist);
		अगर (e->metaval) अणु
			अगर (e->ops->release)
				e->ops->release(e);
			अन्यथा
				kमुक्त(e->metaval);
		पूर्ण
		module_put(e->ops->owner);
		kमुक्त(e);
	पूर्ण
पूर्ण

अटल व्योम tcf_अगरe_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	काष्ठा tcf_अगरe_params *p;

	spin_lock_bh(&अगरe->tcf_lock);
	_tcf_अगरe_cleanup(a);
	spin_unlock_bh(&अगरe->tcf_lock);

	p = rcu_dereference_रक्षित(अगरe->params, 1);
	अगर (p)
		kमुक्त_rcu(p, rcu);
पूर्ण

अटल पूर्णांक load_metalist(काष्ठा nlattr **tb, bool rtnl_held)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < max_metacnt; i++) अणु
		अगर (tb[i]) अणु
			व्योम *val = nla_data(tb[i]);
			पूर्णांक len = nla_len(tb[i]);
			पूर्णांक rc;

			rc = load_metaops_and_vet(i, val, len, rtnl_held);
			अगर (rc != 0)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक populate_metalist(काष्ठा tcf_अगरe_info *अगरe, काष्ठा nlattr **tb,
			     bool exists, bool rtnl_held)
अणु
	पूर्णांक len = 0;
	पूर्णांक rc = 0;
	पूर्णांक i = 0;
	व्योम *val;

	क्रम (i = 1; i < max_metacnt; i++) अणु
		अगर (tb[i]) अणु
			val = nla_data(tb[i]);
			len = nla_len(tb[i]);

			rc = add_metainfo(अगरe, i, val, len, exists);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक tcf_अगरe_init(काष्ठा net *net, काष्ठा nlattr *nla,
			काष्ठा nlattr *est, काष्ठा tc_action **a,
			पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			काष्ठा tcf_proto *tp, u32 flags,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, अगरe_net_id);
	काष्ठा nlattr *tb[TCA_IFE_MAX + 1];
	काष्ठा nlattr *tb2[IFE_META_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_अगरe_params *p;
	काष्ठा tcf_अगरe_info *अगरe;
	u16 अगरe_type = ETH_P_IFE;
	काष्ठा tc_अगरe *parm;
	u8 *daddr = शून्य;
	u8 *saddr = शून्य;
	bool exists = false;
	पूर्णांक ret = 0;
	u32 index;
	पूर्णांक err;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "IFE requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_IFE_MAX, nla, अगरe_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_IFE_PARMS])
		वापस -EINVAL;

	parm = nla_data(tb[TCA_IFE_PARMS]);

	/* IFE_DECODE is 0 and indicates the opposite of IFE_ENCODE because
	 * they cannot run as the same समय. Check on all other values which
	 * are not supported right now.
	 */
	अगर (parm->flags & ~IFE_ENCODE)
		वापस -EINVAL;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	अगर (tb[TCA_IFE_METALST]) अणु
		err = nla_parse_nested_deprecated(tb2, IFE_META_MAX,
						  tb[TCA_IFE_METALST], शून्य,
						  शून्य);
		अगर (err) अणु
			kमुक्त(p);
			वापस err;
		पूर्ण
		err = load_metalist(tb2, rtnl_held);
		अगर (err) अणु
			kमुक्त(p);
			वापस err;
		पूर्ण
	पूर्ण

	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0) अणु
		kमुक्त(p);
		वापस err;
	पूर्ण
	exists = err;
	अगर (exists && bind) अणु
		kमुक्त(p);
		वापस 0;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create(tn, index, est, a, &act_अगरe_ops,
				     bind, true, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			kमुक्त(p);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (!ovr) अणु
		tcf_idr_release(*a, bind);
		kमुक्त(p);
		वापस -EEXIST;
	पूर्ण

	अगरe = to_अगरe(*a);
	अगर (ret == ACT_P_CREATED)
		INIT_LIST_HEAD(&अगरe->metalist);

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	p->flags = parm->flags;

	अगर (parm->flags & IFE_ENCODE) अणु
		अगर (tb[TCA_IFE_TYPE])
			अगरe_type = nla_get_u16(tb[TCA_IFE_TYPE]);
		अगर (tb[TCA_IFE_DMAC])
			daddr = nla_data(tb[TCA_IFE_DMAC]);
		अगर (tb[TCA_IFE_SMAC])
			saddr = nla_data(tb[TCA_IFE_SMAC]);
	पूर्ण

	अगर (parm->flags & IFE_ENCODE) अणु
		अगर (daddr)
			ether_addr_copy(p->eth_dst, daddr);
		अन्यथा
			eth_zero_addr(p->eth_dst);

		अगर (saddr)
			ether_addr_copy(p->eth_src, saddr);
		अन्यथा
			eth_zero_addr(p->eth_src);

		p->eth_type = अगरe_type;
	पूर्ण

	अगर (tb[TCA_IFE_METALST]) अणु
		err = populate_metalist(अगरe, tb2, exists, rtnl_held);
		अगर (err)
			जाओ metadata_parse_err;
	पूर्ण अन्यथा अणु
		/* अगर no passed metadata allow list or passed allow-all
		 * then here we process by adding as many supported metadatum
		 * as we can. You better have at least one अन्यथा we are
		 * going to bail out
		 */
		err = use_all_metadata(अगरe, exists);
		अगर (err)
			जाओ metadata_parse_err;
	पूर्ण

	अगर (exists)
		spin_lock_bh(&अगरe->tcf_lock);
	/* रक्षित by tcf_lock when modअगरying existing action */
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	p = rcu_replace_poपूर्णांकer(अगरe->params, p, 1);

	अगर (exists)
		spin_unlock_bh(&अगरe->tcf_lock);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (p)
		kमुक्त_rcu(p, rcu);

	वापस ret;
metadata_parse_err:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	kमुक्त(p);
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_अगरe_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind,
			पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	काष्ठा tcf_अगरe_params *p;
	काष्ठा tc_अगरe opt = अणु
		.index = अगरe->tcf_index,
		.refcnt = refcount_पढ़ो(&अगरe->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&अगरe->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&अगरe->tcf_lock);
	opt.action = अगरe->tcf_action;
	p = rcu_dereference_रक्षित(अगरe->params,
				      lockdep_is_held(&अगरe->tcf_lock));
	opt.flags = p->flags;

	अगर (nla_put(skb, TCA_IFE_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &अगरe->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_IFE_TM, माप(t), &t, TCA_IFE_PAD))
		जाओ nla_put_failure;

	अगर (!is_zero_ether_addr(p->eth_dst)) अणु
		अगर (nla_put(skb, TCA_IFE_DMAC, ETH_ALEN, p->eth_dst))
			जाओ nla_put_failure;
	पूर्ण

	अगर (!is_zero_ether_addr(p->eth_src)) अणु
		अगर (nla_put(skb, TCA_IFE_SMAC, ETH_ALEN, p->eth_src))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(skb, TCA_IFE_TYPE, 2, &p->eth_type))
		जाओ nla_put_failure;

	अगर (dump_metalist(skb, अगरe)) अणु
		/*ignore failure to dump metalist */
		pr_info("Failed to dump metalist\n");
	पूर्ण

	spin_unlock_bh(&अगरe->tcf_lock);
	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&अगरe->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक find_decode_metaid(काष्ठा sk_buff *skb, काष्ठा tcf_अगरe_info *अगरe,
			      u16 metaid, u16 mlen, व्योम *mdata)
अणु
	काष्ठा tcf_meta_info *e;

	/* XXX: use hash to speed up */
	list_क्रम_each_entry(e, &अगरe->metalist, metalist) अणु
		अगर (metaid == e->metaid) अणु
			अगर (e->ops) अणु
				/* We check क्रम decode presence alपढ़ोy */
				वापस e->ops->decode(skb, mdata, mlen);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक tcf_अगरe_decode(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	पूर्णांक action = अगरe->tcf_action;
	u8 *अगरehdr_end;
	u8 *tlv_data;
	u16 metalen;

	bstats_cpu_update(this_cpu_ptr(अगरe->common.cpu_bstats), skb);
	tcf_lastuse_update(&अगरe->tcf_पंचांग);

	अगर (skb_at_tc_ingress(skb))
		skb_push(skb, skb->dev->hard_header_len);

	tlv_data = अगरe_decode(skb, &metalen);
	अगर (unlikely(!tlv_data)) अणु
		qstats_drop_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
		वापस TC_ACT_SHOT;
	पूर्ण

	अगरehdr_end = tlv_data + metalen;
	क्रम (; tlv_data < अगरehdr_end; tlv_data = अगरe_tlv_meta_next(tlv_data)) अणु
		u8 *curr_data;
		u16 mtype;
		u16 dlen;

		curr_data = अगरe_tlv_meta_decode(tlv_data, अगरehdr_end, &mtype,
						&dlen, शून्य);
		अगर (!curr_data) अणु
			qstats_drop_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
			वापस TC_ACT_SHOT;
		पूर्ण

		अगर (find_decode_metaid(skb, अगरe, mtype, dlen, curr_data)) अणु
			/* abuse overlimits to count when we receive metadata
			 * but करोnt have an ops क्रम it
			 */
			pr_info_ratelimited("Unknown metaid %d dlen %d\n",
					    mtype, dlen);
			qstats_overlimit_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
		पूर्ण
	पूर्ण

	अगर (WARN_ON(tlv_data != अगरehdr_end)) अणु
		qstats_drop_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
		वापस TC_ACT_SHOT;
	पूर्ण

	skb->protocol = eth_type_trans(skb, skb->dev);
	skb_reset_network_header(skb);

	वापस action;
पूर्ण

/*XXX: check अगर we can करो this at install समय instead of current
 * send data path
**/
अटल पूर्णांक अगरe_get_sz(काष्ठा sk_buff *skb, काष्ठा tcf_अगरe_info *अगरe)
अणु
	काष्ठा tcf_meta_info *e, *n;
	पूर्णांक tot_run_sz = 0, run_sz = 0;

	list_क्रम_each_entry_safe(e, n, &अगरe->metalist, metalist) अणु
		अगर (e->ops->check_presence) अणु
			run_sz = e->ops->check_presence(skb, e);
			tot_run_sz += run_sz;
		पूर्ण
	पूर्ण

	वापस tot_run_sz;
पूर्ण

अटल पूर्णांक tcf_अगरe_encode(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res, काष्ठा tcf_अगरe_params *p)
अणु
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	पूर्णांक action = अगरe->tcf_action;
	काष्ठा ethhdr *oethh;	/* outer ether header */
	काष्ठा tcf_meta_info *e;
	/*
	   OUTERHDR:TOTMETALEN:अणुTLVHDR:Metadatum:TLVHDR..पूर्ण:ORIGDATA
	   where ORIGDATA = original ethernet header ...
	 */
	u16 metalen = अगरe_get_sz(skb, अगरe);
	पूर्णांक hdrm = metalen + skb->dev->hard_header_len + IFE_METAHDRLEN;
	अचिन्हित पूर्णांक skboff = 0;
	पूर्णांक new_len = skb->len + hdrm;
	bool exceed_mtu = false;
	व्योम *अगरe_meta;
	पूर्णांक err = 0;

	अगर (!skb_at_tc_ingress(skb)) अणु
		अगर (new_len > skb->dev->mtu)
			exceed_mtu = true;
	पूर्ण

	bstats_cpu_update(this_cpu_ptr(अगरe->common.cpu_bstats), skb);
	tcf_lastuse_update(&अगरe->tcf_पंचांग);

	अगर (!metalen) अणु		/* no metadata to send */
		/* abuse overlimits to count when we allow packet
		 * with no metadata
		 */
		qstats_overlimit_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
		वापस action;
	पूर्ण
	/* could be stupid policy setup or mtu config
	 * so lets be conservative.. */
	अगर ((action == TC_ACT_SHOT) || exceed_mtu) अणु
		qstats_drop_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
		वापस TC_ACT_SHOT;
	पूर्ण

	अगर (skb_at_tc_ingress(skb))
		skb_push(skb, skb->dev->hard_header_len);

	अगरe_meta = अगरe_encode(skb, metalen);

	spin_lock(&अगरe->tcf_lock);

	/* XXX: we करोnt have a clever way of telling encode to
	 * not repeat some of the computations that are करोne by
	 * ops->presence_check...
	 */
	list_क्रम_each_entry(e, &अगरe->metalist, metalist) अणु
		अगर (e->ops->encode) अणु
			err = e->ops->encode(skb, (व्योम *)(अगरe_meta + skboff),
					     e);
		पूर्ण
		अगर (err < 0) अणु
			/* too corrupt to keep around अगर overwritten */
			spin_unlock(&अगरe->tcf_lock);
			qstats_drop_inc(this_cpu_ptr(अगरe->common.cpu_qstats));
			वापस TC_ACT_SHOT;
		पूर्ण
		skboff += err;
	पूर्ण
	spin_unlock(&अगरe->tcf_lock);
	oethh = (काष्ठा ethhdr *)skb->data;

	अगर (!is_zero_ether_addr(p->eth_src))
		ether_addr_copy(oethh->h_source, p->eth_src);
	अगर (!is_zero_ether_addr(p->eth_dst))
		ether_addr_copy(oethh->h_dest, p->eth_dst);
	oethh->h_proto = htons(p->eth_type);

	अगर (skb_at_tc_ingress(skb))
		skb_pull(skb, skb->dev->hard_header_len);

	वापस action;
पूर्ण

अटल पूर्णांक tcf_अगरe_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
		       काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_अगरe_info *अगरe = to_अगरe(a);
	काष्ठा tcf_अगरe_params *p;
	पूर्णांक ret;

	p = rcu_dereference_bh(अगरe->params);
	अगर (p->flags & IFE_ENCODE) अणु
		ret = tcf_अगरe_encode(skb, a, res, p);
		वापस ret;
	पूर्ण

	वापस tcf_अगरe_decode(skb, a, res);
पूर्ण

अटल पूर्णांक tcf_अगरe_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			  काष्ठा netlink_callback *cb, पूर्णांक type,
			  स्थिर काष्ठा tc_action_ops *ops,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, अगरe_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_अगरe_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, अगरe_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_अगरe_ops = अणु
	.kind = "ife",
	.id = TCA_ID_IFE,
	.owner = THIS_MODULE,
	.act = tcf_अगरe_act,
	.dump = tcf_अगरe_dump,
	.cleanup = tcf_अगरe_cleanup,
	.init = tcf_अगरe_init,
	.walk = tcf_अगरe_walker,
	.lookup = tcf_अगरe_search,
	.size =	माप(काष्ठा tcf_अगरe_info),
पूर्ण;

अटल __net_init पूर्णांक अगरe_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, अगरe_net_id);

	वापस tc_action_net_init(net, tn, &act_अगरe_ops);
पूर्ण

अटल व्योम __net_निकास अगरe_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, अगरe_net_id);
पूर्ण

अटल काष्ठा pernet_operations अगरe_net_ops = अणु
	.init = अगरe_init_net,
	.निकास_batch = अगरe_निकास_net,
	.id   = &अगरe_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init अगरe_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_अगरe_ops, &अगरe_net_ops);
पूर्ण

अटल व्योम __निकास अगरe_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_अगरe_ops, &अगरe_net_ops);
पूर्ण

module_init(अगरe_init_module);
module_निकास(अगरe_cleanup_module);

MODULE_AUTHOR("Jamal Hadi Salim(2015)");
MODULE_DESCRIPTION("Inter-FE LFB action");
MODULE_LICENSE("GPL");
