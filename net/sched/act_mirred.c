<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_mirred.c	packet mirroring and redirect actions
 *
 * Authors:	Jamal Hadi Salim (2002-4)
 *
 * TODO: Add ingress support (and socket redirect support)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_mirred.h>

अटल LIST_HEAD(mirred_list);
अटल DEFINE_SPINLOCK(mirred_list_lock);

#घोषणा MIRRED_RECURSION_LIMIT    4
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, mirred_rec_level);

अटल bool tcf_mirred_is_act_redirect(पूर्णांक action)
अणु
	वापस action == TCA_EGRESS_REसूची || action == TCA_INGRESS_REसूची;
पूर्ण

अटल bool tcf_mirred_act_wants_ingress(पूर्णांक action)
अणु
	चयन (action) अणु
	हाल TCA_EGRESS_REसूची:
	हाल TCA_EGRESS_MIRROR:
		वापस false;
	हाल TCA_INGRESS_REसूची:
	हाल TCA_INGRESS_MIRROR:
		वापस true;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल bool tcf_mirred_can_reinsert(पूर्णांक action)
अणु
	चयन (action) अणु
	हाल TC_ACT_SHOT:
	हाल TC_ACT_STOLEN:
	हाल TC_ACT_QUEUED:
	हाल TC_ACT_TRAP:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा net_device *tcf_mirred_dev_dereference(काष्ठा tcf_mirred *m)
अणु
	वापस rcu_dereference_रक्षित(m->tcfm_dev,
					 lockdep_is_held(&m->tcf_lock));
पूर्ण

अटल व्योम tcf_mirred_release(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_mirred *m = to_mirred(a);
	काष्ठा net_device *dev;

	spin_lock(&mirred_list_lock);
	list_del(&m->tcfm_list);
	spin_unlock(&mirred_list_lock);

	/* last reference to action, no need to lock */
	dev = rcu_dereference_रक्षित(m->tcfm_dev, 1);
	अगर (dev)
		dev_put(dev);
पूर्ण

अटल स्थिर काष्ठा nla_policy mirred_policy[TCA_MIRRED_MAX + 1] = अणु
	[TCA_MIRRED_PARMS]	= अणु .len = माप(काष्ठा tc_mirred) पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक mirred_net_id;
अटल काष्ठा tc_action_ops act_mirred_ops;

अटल पूर्णांक tcf_mirred_init(काष्ठा net *net, काष्ठा nlattr *nla,
			   काष्ठा nlattr *est, काष्ठा tc_action **a,
			   पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			   काष्ठा tcf_proto *tp,
			   u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mirred_net_id);
	काष्ठा nlattr *tb[TCA_MIRRED_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	bool mac_header_xmit = false;
	काष्ठा tc_mirred *parm;
	काष्ठा tcf_mirred *m;
	काष्ठा net_device *dev;
	bool exists = false;
	पूर्णांक ret, err;
	u32 index;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "Mirred requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण
	ret = nla_parse_nested_deprecated(tb, TCA_MIRRED_MAX, nla,
					  mirred_policy, extack);
	अगर (ret < 0)
		वापस ret;
	अगर (!tb[TCA_MIRRED_PARMS]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing required mirred parameters");
		वापस -EINVAL;
	पूर्ण
	parm = nla_data(tb[TCA_MIRRED_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	चयन (parm->eaction) अणु
	हाल TCA_EGRESS_MIRROR:
	हाल TCA_EGRESS_REसूची:
	हाल TCA_INGRESS_REसूची:
	हाल TCA_INGRESS_MIRROR:
		अवरोध;
	शेष:
		अगर (exists)
			tcf_idr_release(*a, bind);
		अन्यथा
			tcf_idr_cleanup(tn, index);
		NL_SET_ERR_MSG_MOD(extack, "Unknown mirred option");
		वापस -EINVAL;
	पूर्ण

	अगर (!exists) अणु
		अगर (!parm->अगरindex) अणु
			tcf_idr_cleanup(tn, index);
			NL_SET_ERR_MSG_MOD(extack, "Specified device does not exist");
			वापस -EINVAL;
		पूर्ण
		ret = tcf_idr_create_from_flags(tn, index, est, a,
						&act_mirred_ops, bind, flags);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (!ovr) अणु
		tcf_idr_release(*a, bind);
		वापस -EEXIST;
	पूर्ण

	m = to_mirred(*a);
	अगर (ret == ACT_P_CREATED)
		INIT_LIST_HEAD(&m->tcfm_list);

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	spin_lock_bh(&m->tcf_lock);

	अगर (parm->अगरindex) अणु
		dev = dev_get_by_index(net, parm->अगरindex);
		अगर (!dev) अणु
			spin_unlock_bh(&m->tcf_lock);
			err = -ENODEV;
			जाओ put_chain;
		पूर्ण
		mac_header_xmit = dev_is_mac_header_xmit(dev);
		dev = rcu_replace_poपूर्णांकer(m->tcfm_dev, dev,
					  lockdep_is_held(&m->tcf_lock));
		अगर (dev)
			dev_put(dev);
		m->tcfm_mac_header_xmit = mac_header_xmit;
	पूर्ण
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	m->tcfm_eaction = parm->eaction;
	spin_unlock_bh(&m->tcf_lock);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	अगर (ret == ACT_P_CREATED) अणु
		spin_lock(&mirred_list_lock);
		list_add(&m->tcfm_list, &mirred_list);
		spin_unlock(&mirred_list_lock);
	पूर्ण

	वापस ret;
put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_mirred_क्रमward(bool want_ingress, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	अगर (!want_ingress)
		err = tcf_dev_queue_xmit(skb, dev_queue_xmit);
	अन्यथा
		err = netअगर_receive_skb(skb);

	वापस err;
पूर्ण

अटल पूर्णांक tcf_mirred_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_mirred *m = to_mirred(a);
	काष्ठा sk_buff *skb2 = skb;
	bool m_mac_header_xmit;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक rec_level;
	पूर्णांक retval, err = 0;
	bool use_reinsert;
	bool want_ingress;
	bool is_redirect;
	bool expects_nh;
	पूर्णांक m_eaction;
	पूर्णांक mac_len;
	bool at_nh;

	rec_level = __this_cpu_inc_वापस(mirred_rec_level);
	अगर (unlikely(rec_level > MIRRED_RECURSION_LIMIT)) अणु
		net_warn_ratelimited("Packet exceeded mirred recursion limit on dev %s\n",
				     netdev_name(skb->dev));
		__this_cpu_dec(mirred_rec_level);
		वापस TC_ACT_SHOT;
	पूर्ण

	tcf_lastuse_update(&m->tcf_पंचांग);
	tcf_action_update_bstats(&m->common, skb);

	m_mac_header_xmit = READ_ONCE(m->tcfm_mac_header_xmit);
	m_eaction = READ_ONCE(m->tcfm_eaction);
	retval = READ_ONCE(m->tcf_action);
	dev = rcu_dereference_bh(m->tcfm_dev);
	अगर (unlikely(!dev)) अणु
		pr_notice_once("tc mirred: target device is gone\n");
		जाओ out;
	पूर्ण

	अगर (unlikely(!(dev->flags & IFF_UP))) अणु
		net_notice_ratelimited("tc mirred to Houston: device %s is down\n",
				       dev->name);
		जाओ out;
	पूर्ण

	/* we could easily aव्योम the clone only अगर called by ingress and clsact;
	 * since we can't easily detect the clsact caller, skip clone only क्रम
	 * ingress - that covers the TC S/W datapath.
	 */
	is_redirect = tcf_mirred_is_act_redirect(m_eaction);
	use_reinsert = skb_at_tc_ingress(skb) && is_redirect &&
		       tcf_mirred_can_reinsert(retval);
	अगर (!use_reinsert) अणु
		skb2 = skb_clone(skb, GFP_ATOMIC);
		अगर (!skb2)
			जाओ out;
	पूर्ण

	want_ingress = tcf_mirred_act_wants_ingress(m_eaction);

	expects_nh = want_ingress || !m_mac_header_xmit;
	at_nh = skb->data == skb_network_header(skb);
	अगर (at_nh != expects_nh) अणु
		mac_len = skb_at_tc_ingress(skb) ? skb->mac_len :
			  skb_network_header(skb) - skb_mac_header(skb);
		अगर (expects_nh) अणु
			/* target device/action expect data at nh */
			skb_pull_rcsum(skb2, mac_len);
		पूर्ण अन्यथा अणु
			/* target device/action expect data at mac */
			skb_push_rcsum(skb2, mac_len);
		पूर्ण
	पूर्ण

	skb2->skb_iअगर = skb->dev->अगरindex;
	skb2->dev = dev;

	/* mirror is always swallowed */
	अगर (is_redirect) अणु
		skb_set_redirected(skb2, skb2->tc_at_ingress);

		/* let's the caller reinsert the packet, अगर possible */
		अगर (use_reinsert) अणु
			res->ingress = want_ingress;
			err = tcf_mirred_क्रमward(res->ingress, skb);
			अगर (err)
				tcf_action_inc_overlimit_qstats(&m->common);
			__this_cpu_dec(mirred_rec_level);
			वापस TC_ACT_CONSUMED;
		पूर्ण
	पूर्ण

	err = tcf_mirred_क्रमward(want_ingress, skb2);
	अगर (err) अणु
out:
		tcf_action_inc_overlimit_qstats(&m->common);
		अगर (tcf_mirred_is_act_redirect(m_eaction))
			retval = TC_ACT_SHOT;
	पूर्ण
	__this_cpu_dec(mirred_rec_level);

	वापस retval;
पूर्ण

अटल व्योम tcf_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
			     u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_mirred *m = to_mirred(a);
	काष्ठा tcf_t *पंचांग = &m->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_mirred_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a, पूर्णांक bind,
			   पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_mirred *m = to_mirred(a);
	काष्ठा tc_mirred opt = अणु
		.index   = m->tcf_index,
		.refcnt  = refcount_पढ़ो(&m->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&m->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा net_device *dev;
	काष्ठा tcf_t t;

	spin_lock_bh(&m->tcf_lock);
	opt.action = m->tcf_action;
	opt.eaction = m->tcfm_eaction;
	dev = tcf_mirred_dev_dereference(m);
	अगर (dev)
		opt.अगरindex = dev->अगरindex;

	अगर (nla_put(skb, TCA_MIRRED_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &m->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_MIRRED_TM, माप(t), &t, TCA_MIRRED_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&m->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&m->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_mirred_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb, पूर्णांक type,
			     स्थिर काष्ठा tc_action_ops *ops,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mirred_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_mirred_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mirred_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल पूर्णांक mirred_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा tcf_mirred *m;

	ASSERT_RTNL();
	अगर (event == NETDEV_UNREGISTER) अणु
		spin_lock(&mirred_list_lock);
		list_क्रम_each_entry(m, &mirred_list, tcfm_list) अणु
			spin_lock_bh(&m->tcf_lock);
			अगर (tcf_mirred_dev_dereference(m) == dev) अणु
				dev_put(dev);
				/* Note : no rcu grace period necessary, as
				 * net_device are alपढ़ोy rcu रक्षित.
				 */
				RCU_INIT_POINTER(m->tcfm_dev, शून्य);
			पूर्ण
			spin_unlock_bh(&m->tcf_lock);
		पूर्ण
		spin_unlock(&mirred_list_lock);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block mirred_device_notअगरier = अणु
	.notअगरier_call = mirred_device_event,
पूर्ण;

अटल व्योम tcf_mirred_dev_put(व्योम *priv)
अणु
	काष्ठा net_device *dev = priv;

	dev_put(dev);
पूर्ण

अटल काष्ठा net_device *
tcf_mirred_get_dev(स्थिर काष्ठा tc_action *a,
		   tc_action_priv_deकाष्ठाor *deकाष्ठाor)
अणु
	काष्ठा tcf_mirred *m = to_mirred(a);
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(m->tcfm_dev);
	अगर (dev) अणु
		dev_hold(dev);
		*deकाष्ठाor = tcf_mirred_dev_put;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस dev;
पूर्ण

अटल माप_प्रकार tcf_mirred_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	वापस nla_total_size(माप(काष्ठा tc_mirred));
पूर्ण

अटल काष्ठा tc_action_ops act_mirred_ops = अणु
	.kind		=	"mirred",
	.id		=	TCA_ID_MIRRED,
	.owner		=	THIS_MODULE,
	.act		=	tcf_mirred_act,
	.stats_update	=	tcf_stats_update,
	.dump		=	tcf_mirred_dump,
	.cleanup	=	tcf_mirred_release,
	.init		=	tcf_mirred_init,
	.walk		=	tcf_mirred_walker,
	.lookup		=	tcf_mirred_search,
	.get_fill_size	=	tcf_mirred_get_fill_size,
	.size		=	माप(काष्ठा tcf_mirred),
	.get_dev	=	tcf_mirred_get_dev,
पूर्ण;

अटल __net_init पूर्णांक mirred_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, mirred_net_id);

	वापस tc_action_net_init(net, tn, &act_mirred_ops);
पूर्ण

अटल व्योम __net_निकास mirred_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, mirred_net_id);
पूर्ण

अटल काष्ठा pernet_operations mirred_net_ops = अणु
	.init = mirred_init_net,
	.निकास_batch = mirred_निकास_net,
	.id   = &mirred_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_AUTHOR("Jamal Hadi Salim(2002)");
MODULE_DESCRIPTION("Device Mirror/redirect actions");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init mirred_init_module(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_netdevice_notअगरier(&mirred_device_notअगरier);
	अगर (err)
		वापस err;

	pr_info("Mirror/redirect action on\n");
	err = tcf_रेजिस्टर_action(&act_mirred_ops, &mirred_net_ops);
	अगर (err)
		unरेजिस्टर_netdevice_notअगरier(&mirred_device_notअगरier);

	वापस err;
पूर्ण

अटल व्योम __निकास mirred_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_mirred_ops, &mirred_net_ops);
	unरेजिस्टर_netdevice_notअगरier(&mirred_device_notअगरier);
पूर्ण

module_init(mirred_init_module);
module_निकास(mirred_cleanup_module);
