<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2015 Jiri Pirko <jiri@resnulli.us>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>

#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_bpf.h>
#समावेश <net/tc_act/tc_bpf.h>

#घोषणा ACT_BPF_NAME_LEN	256

काष्ठा tcf_bpf_cfg अणु
	काष्ठा bpf_prog *filter;
	काष्ठा sock_filter *bpf_ops;
	स्थिर अक्षर *bpf_name;
	u16 bpf_num_ops;
	bool is_ebpf;
पूर्ण;

अटल अचिन्हित पूर्णांक bpf_net_id;
अटल काष्ठा tc_action_ops act_bpf_ops;

अटल पूर्णांक tcf_bpf_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *act,
		       काष्ठा tcf_result *res)
अणु
	bool at_ingress = skb_at_tc_ingress(skb);
	काष्ठा tcf_bpf *prog = to_bpf(act);
	काष्ठा bpf_prog *filter;
	पूर्णांक action, filter_res;

	tcf_lastuse_update(&prog->tcf_पंचांग);
	bstats_cpu_update(this_cpu_ptr(prog->common.cpu_bstats), skb);

	rcu_पढ़ो_lock();
	filter = rcu_dereference(prog->filter);
	अगर (at_ingress) अणु
		__skb_push(skb, skb->mac_len);
		bpf_compute_data_poपूर्णांकers(skb);
		filter_res = BPF_PROG_RUN(filter, skb);
		__skb_pull(skb, skb->mac_len);
	पूर्ण अन्यथा अणु
		bpf_compute_data_poपूर्णांकers(skb);
		filter_res = BPF_PROG_RUN(filter, skb);
	पूर्ण
	अगर (skb_sk_is_prefetched(skb) && filter_res != TC_ACT_OK)
		skb_orphan(skb);
	rcu_पढ़ो_unlock();

	/* A BPF program may overग_लिखो the शेष action opcode.
	 * Similarly as in cls_bpf, अगर filter_res == -1 we use the
	 * शेष action specअगरied from tc.
	 *
	 * In हाल a dअगरferent well-known TC_ACT opcode has been
	 * वापसed, it will overग_लिखो the शेष one.
	 *
	 * For everything अन्यथा that is unknown, TC_ACT_UNSPEC is
	 * वापसed.
	 */
	चयन (filter_res) अणु
	हाल TC_ACT_PIPE:
	हाल TC_ACT_RECLASSIFY:
	हाल TC_ACT_OK:
	हाल TC_ACT_REसूचीECT:
		action = filter_res;
		अवरोध;
	हाल TC_ACT_SHOT:
		action = filter_res;
		qstats_drop_inc(this_cpu_ptr(prog->common.cpu_qstats));
		अवरोध;
	हाल TC_ACT_UNSPEC:
		action = prog->tcf_action;
		अवरोध;
	शेष:
		action = TC_ACT_UNSPEC;
		अवरोध;
	पूर्ण

	वापस action;
पूर्ण

अटल bool tcf_bpf_is_ebpf(स्थिर काष्ठा tcf_bpf *prog)
अणु
	वापस !prog->bpf_ops;
पूर्ण

अटल पूर्णांक tcf_bpf_dump_bpf_info(स्थिर काष्ठा tcf_bpf *prog,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla;

	अगर (nla_put_u16(skb, TCA_ACT_BPF_OPS_LEN, prog->bpf_num_ops))
		वापस -EMSGSIZE;

	nla = nla_reserve(skb, TCA_ACT_BPF_OPS, prog->bpf_num_ops *
			  माप(काष्ठा sock_filter));
	अगर (nla == शून्य)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), prog->bpf_ops, nla_len(nla));

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_bpf_dump_ebpf_info(स्थिर काष्ठा tcf_bpf *prog,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla;

	अगर (prog->bpf_name &&
	    nla_put_string(skb, TCA_ACT_BPF_NAME, prog->bpf_name))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TCA_ACT_BPF_ID, prog->filter->aux->id))
		वापस -EMSGSIZE;

	nla = nla_reserve(skb, TCA_ACT_BPF_TAG, माप(prog->filter->tag));
	अगर (nla == शून्य)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), prog->filter->tag, nla_len(nla));

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_bpf_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *act,
			पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *tp = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_bpf *prog = to_bpf(act);
	काष्ठा tc_act_bpf opt = अणु
		.index   = prog->tcf_index,
		.refcnt  = refcount_पढ़ो(&prog->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&prog->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t पंचांग;
	पूर्णांक ret;

	spin_lock_bh(&prog->tcf_lock);
	opt.action = prog->tcf_action;
	अगर (nla_put(skb, TCA_ACT_BPF_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर (tcf_bpf_is_ebpf(prog))
		ret = tcf_bpf_dump_ebpf_info(prog, skb);
	अन्यथा
		ret = tcf_bpf_dump_bpf_info(prog, skb);
	अगर (ret)
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&पंचांग, &prog->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_ACT_BPF_TM, माप(पंचांग), &पंचांग,
			  TCA_ACT_BPF_PAD))
		जाओ nla_put_failure;

	spin_unlock_bh(&prog->tcf_lock);
	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&prog->tcf_lock);
	nlmsg_trim(skb, tp);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy act_bpf_policy[TCA_ACT_BPF_MAX + 1] = अणु
	[TCA_ACT_BPF_PARMS]	= अणु .len = माप(काष्ठा tc_act_bpf) पूर्ण,
	[TCA_ACT_BPF_FD]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_ACT_BPF_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len = ACT_BPF_NAME_LEN पूर्ण,
	[TCA_ACT_BPF_OPS_LEN]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_ACT_BPF_OPS]	= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा sock_filter) * BPF_MAXINSNS पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_bpf_init_from_ops(काष्ठा nlattr **tb, काष्ठा tcf_bpf_cfg *cfg)
अणु
	काष्ठा sock_filter *bpf_ops;
	काष्ठा sock_fprog_kern fprog_पंचांगp;
	काष्ठा bpf_prog *fp;
	u16 bpf_size, bpf_num_ops;
	पूर्णांक ret;

	bpf_num_ops = nla_get_u16(tb[TCA_ACT_BPF_OPS_LEN]);
	अगर (bpf_num_ops	> BPF_MAXINSNS || bpf_num_ops == 0)
		वापस -EINVAL;

	bpf_size = bpf_num_ops * माप(*bpf_ops);
	अगर (bpf_size != nla_len(tb[TCA_ACT_BPF_OPS]))
		वापस -EINVAL;

	bpf_ops = kmemdup(nla_data(tb[TCA_ACT_BPF_OPS]), bpf_size, GFP_KERNEL);
	अगर (bpf_ops == शून्य)
		वापस -ENOMEM;

	fprog_पंचांगp.len = bpf_num_ops;
	fprog_पंचांगp.filter = bpf_ops;

	ret = bpf_prog_create(&fp, &fprog_पंचांगp);
	अगर (ret < 0) अणु
		kमुक्त(bpf_ops);
		वापस ret;
	पूर्ण

	cfg->bpf_ops = bpf_ops;
	cfg->bpf_num_ops = bpf_num_ops;
	cfg->filter = fp;
	cfg->is_ebpf = false;

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_bpf_init_from_efd(काष्ठा nlattr **tb, काष्ठा tcf_bpf_cfg *cfg)
अणु
	काष्ठा bpf_prog *fp;
	अक्षर *name = शून्य;
	u32 bpf_fd;

	bpf_fd = nla_get_u32(tb[TCA_ACT_BPF_FD]);

	fp = bpf_prog_get_type(bpf_fd, BPF_PROG_TYPE_SCHED_ACT);
	अगर (IS_ERR(fp))
		वापस PTR_ERR(fp);

	अगर (tb[TCA_ACT_BPF_NAME]) अणु
		name = nla_memdup(tb[TCA_ACT_BPF_NAME], GFP_KERNEL);
		अगर (!name) अणु
			bpf_prog_put(fp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cfg->bpf_name = name;
	cfg->filter = fp;
	cfg->is_ebpf = true;

	वापस 0;
पूर्ण

अटल व्योम tcf_bpf_cfg_cleanup(स्थिर काष्ठा tcf_bpf_cfg *cfg)
अणु
	काष्ठा bpf_prog *filter = cfg->filter;

	अगर (filter) अणु
		अगर (cfg->is_ebpf)
			bpf_prog_put(filter);
		अन्यथा
			bpf_prog_destroy(filter);
	पूर्ण

	kमुक्त(cfg->bpf_ops);
	kमुक्त(cfg->bpf_name);
पूर्ण

अटल व्योम tcf_bpf_prog_fill_cfg(स्थिर काष्ठा tcf_bpf *prog,
				  काष्ठा tcf_bpf_cfg *cfg)
अणु
	cfg->is_ebpf = tcf_bpf_is_ebpf(prog);
	/* updates to prog->filter are prevented, since it's called either
	 * with tcf lock or during final cleanup in rcu callback
	 */
	cfg->filter = rcu_dereference_रक्षित(prog->filter, 1);

	cfg->bpf_ops = prog->bpf_ops;
	cfg->bpf_name = prog->bpf_name;
पूर्ण

अटल पूर्णांक tcf_bpf_init(काष्ठा net *net, काष्ठा nlattr *nla,
			काष्ठा nlattr *est, काष्ठा tc_action **act,
			पूर्णांक replace, पूर्णांक bind, bool rtnl_held,
			काष्ठा tcf_proto *tp, u32 flags,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, bpf_net_id);
	काष्ठा nlattr *tb[TCA_ACT_BPF_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tcf_bpf_cfg cfg, old;
	काष्ठा tc_act_bpf *parm;
	काष्ठा tcf_bpf *prog;
	bool is_bpf, is_ebpf;
	पूर्णांक ret, res = 0;
	u32 index;

	अगर (!nla)
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(tb, TCA_ACT_BPF_MAX, nla,
					  act_bpf_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[TCA_ACT_BPF_PARMS])
		वापस -EINVAL;

	parm = nla_data(tb[TCA_ACT_BPF_PARMS]);
	index = parm->index;
	ret = tcf_idr_check_alloc(tn, &index, act, bind);
	अगर (!ret) अणु
		ret = tcf_idr_create(tn, index, est, act,
				     &act_bpf_ops, bind, true, 0);
		अगर (ret < 0) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		res = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		/* Don't override शेषs. */
		अगर (bind)
			वापस 0;

		अगर (!replace) अणु
			tcf_idr_release(*act, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	ret = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (ret < 0)
		जाओ release_idr;

	is_bpf = tb[TCA_ACT_BPF_OPS_LEN] && tb[TCA_ACT_BPF_OPS];
	is_ebpf = tb[TCA_ACT_BPF_FD];

	अगर ((!is_bpf && !is_ebpf) || (is_bpf && is_ebpf)) अणु
		ret = -EINVAL;
		जाओ put_chain;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));

	ret = is_bpf ? tcf_bpf_init_from_ops(tb, &cfg) :
		       tcf_bpf_init_from_efd(tb, &cfg);
	अगर (ret < 0)
		जाओ put_chain;

	prog = to_bpf(*act);

	spin_lock_bh(&prog->tcf_lock);
	अगर (res != ACT_P_CREATED)
		tcf_bpf_prog_fill_cfg(prog, &old);

	prog->bpf_ops = cfg.bpf_ops;
	prog->bpf_name = cfg.bpf_name;

	अगर (cfg.bpf_num_ops)
		prog->bpf_num_ops = cfg.bpf_num_ops;

	जाओ_ch = tcf_action_set_ctrlact(*act, parm->action, जाओ_ch);
	rcu_assign_poपूर्णांकer(prog->filter, cfg.filter);
	spin_unlock_bh(&prog->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	अगर (res != ACT_P_CREATED) अणु
		/* make sure the program being replaced is no दीर्घer executing */
		synchronize_rcu();
		tcf_bpf_cfg_cleanup(&old);
	पूर्ण

	वापस res;

put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

release_idr:
	tcf_idr_release(*act, bind);
	वापस ret;
पूर्ण

अटल व्योम tcf_bpf_cleanup(काष्ठा tc_action *act)
अणु
	काष्ठा tcf_bpf_cfg पंचांगp;

	tcf_bpf_prog_fill_cfg(to_bpf(act), &पंचांगp);
	tcf_bpf_cfg_cleanup(&पंचांगp);
पूर्ण

अटल पूर्णांक tcf_bpf_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			  काष्ठा netlink_callback *cb, पूर्णांक type,
			  स्थिर काष्ठा tc_action_ops *ops,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, bpf_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_bpf_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, bpf_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_bpf_ops __पढ़ो_mostly = अणु
	.kind		=	"bpf",
	.id		=	TCA_ID_BPF,
	.owner		=	THIS_MODULE,
	.act		=	tcf_bpf_act,
	.dump		=	tcf_bpf_dump,
	.cleanup	=	tcf_bpf_cleanup,
	.init		=	tcf_bpf_init,
	.walk		=	tcf_bpf_walker,
	.lookup		=	tcf_bpf_search,
	.size		=	माप(काष्ठा tcf_bpf),
पूर्ण;

अटल __net_init पूर्णांक bpf_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, bpf_net_id);

	वापस tc_action_net_init(net, tn, &act_bpf_ops);
पूर्ण

अटल व्योम __net_निकास bpf_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, bpf_net_id);
पूर्ण

अटल काष्ठा pernet_operations bpf_net_ops = अणु
	.init = bpf_init_net,
	.निकास_batch = bpf_निकास_net,
	.id   = &bpf_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init bpf_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_bpf_ops, &bpf_net_ops);
पूर्ण

अटल व्योम __निकास bpf_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_bpf_ops, &bpf_net_ops);
पूर्ण

module_init(bpf_init_module);
module_निकास(bpf_cleanup_module);

MODULE_AUTHOR("Jiri Pirko <jiri@resnulli.us>");
MODULE_DESCRIPTION("TC BPF based action");
MODULE_LICENSE("GPL v2");
