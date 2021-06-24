<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Berkeley Packet Filter based traffic classअगरier
 *
 * Might be used to classअगरy traffic through flexible, user-defined and
 * possibly JIT-ed BPF filters क्रम traffic control as an alternative to
 * ematches.
 *
 * (C) 2013 Daniel Borkmann <dborkman@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/idr.h>

#समावेश <net/rtnetlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Borkmann <dborkman@redhat.com>");
MODULE_DESCRIPTION("TC BPF based classifier");

#घोषणा CLS_BPF_NAME_LEN	256
#घोषणा CLS_BPF_SUPPORTED_GEN_FLAGS		\
	(TCA_CLS_FLAGS_SKIP_HW | TCA_CLS_FLAGS_SKIP_SW)

काष्ठा cls_bpf_head अणु
	काष्ठा list_head plist;
	काष्ठा idr handle_idr;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा cls_bpf_prog अणु
	काष्ठा bpf_prog *filter;
	काष्ठा list_head link;
	काष्ठा tcf_result res;
	bool exts_पूर्णांकegrated;
	u32 gen_flags;
	अचिन्हित पूर्णांक in_hw_count;
	काष्ठा tcf_exts exts;
	u32 handle;
	u16 bpf_num_ops;
	काष्ठा sock_filter *bpf_ops;
	स्थिर अक्षर *bpf_name;
	काष्ठा tcf_proto *tp;
	काष्ठा rcu_work rwork;
पूर्ण;

अटल स्थिर काष्ठा nla_policy bpf_policy[TCA_BPF_MAX + 1] = अणु
	[TCA_BPF_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_BPF_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_BPF_FLAGS_GEN]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_BPF_FD]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_BPF_NAME]		= अणु .type = NLA_NUL_STRING,
				    .len = CLS_BPF_NAME_LEN पूर्ण,
	[TCA_BPF_OPS_LEN]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_BPF_OPS]		= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा sock_filter) * BPF_MAXINSNS पूर्ण,
पूर्ण;

अटल पूर्णांक cls_bpf_exec_opcode(पूर्णांक code)
अणु
	चयन (code) अणु
	हाल TC_ACT_OK:
	हाल TC_ACT_SHOT:
	हाल TC_ACT_STOLEN:
	हाल TC_ACT_TRAP:
	हाल TC_ACT_REसूचीECT:
	हाल TC_ACT_UNSPEC:
		वापस code;
	शेष:
		वापस TC_ACT_UNSPEC;
	पूर्ण
पूर्ण

अटल पूर्णांक cls_bpf_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			    काष्ठा tcf_result *res)
अणु
	काष्ठा cls_bpf_head *head = rcu_dereference_bh(tp->root);
	bool at_ingress = skb_at_tc_ingress(skb);
	काष्ठा cls_bpf_prog *prog;
	पूर्णांक ret = -1;

	/* Needed here क्रम accessing maps. */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(prog, &head->plist, link) अणु
		पूर्णांक filter_res;

		qdisc_skb_cb(skb)->tc_classid = prog->res.classid;

		अगर (tc_skip_sw(prog->gen_flags)) अणु
			filter_res = prog->exts_पूर्णांकegrated ? TC_ACT_UNSPEC : 0;
		पूर्ण अन्यथा अगर (at_ingress) अणु
			/* It is safe to push/pull even अगर skb_shared() */
			__skb_push(skb, skb->mac_len);
			bpf_compute_data_poपूर्णांकers(skb);
			filter_res = BPF_PROG_RUN(prog->filter, skb);
			__skb_pull(skb, skb->mac_len);
		पूर्ण अन्यथा अणु
			bpf_compute_data_poपूर्णांकers(skb);
			filter_res = BPF_PROG_RUN(prog->filter, skb);
		पूर्ण

		अगर (prog->exts_पूर्णांकegrated) अणु
			res->class   = 0;
			res->classid = TC_H_MAJ(prog->res.classid) |
				       qdisc_skb_cb(skb)->tc_classid;

			ret = cls_bpf_exec_opcode(filter_res);
			अगर (ret == TC_ACT_UNSPEC)
				जारी;
			अवरोध;
		पूर्ण

		अगर (filter_res == 0)
			जारी;
		अगर (filter_res != -1) अणु
			res->class   = 0;
			res->classid = filter_res;
		पूर्ण अन्यथा अणु
			*res = prog->res;
		पूर्ण

		ret = tcf_exts_exec(skb, &prog->exts, res);
		अगर (ret < 0)
			जारी;

		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल bool cls_bpf_is_ebpf(स्थिर काष्ठा cls_bpf_prog *prog)
अणु
	वापस !prog->bpf_ops;
पूर्ण

अटल पूर्णांक cls_bpf_offload_cmd(काष्ठा tcf_proto *tp, काष्ठा cls_bpf_prog *prog,
			       काष्ठा cls_bpf_prog *oldprog,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_bpf_offload cls_bpf = अणुपूर्ण;
	काष्ठा cls_bpf_prog *obj;
	bool skip_sw;
	पूर्णांक err;

	skip_sw = prog && tc_skip_sw(prog->gen_flags);
	obj = prog ?: oldprog;

	tc_cls_common_offload_init(&cls_bpf.common, tp, obj->gen_flags, extack);
	cls_bpf.command = TC_CLSBPF_OFFLOAD;
	cls_bpf.exts = &obj->exts;
	cls_bpf.prog = prog ? prog->filter : शून्य;
	cls_bpf.oldprog = oldprog ? oldprog->filter : शून्य;
	cls_bpf.name = obj->bpf_name;
	cls_bpf.exts_पूर्णांकegrated = obj->exts_पूर्णांकegrated;

	अगर (oldprog && prog)
		err = tc_setup_cb_replace(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
					  skip_sw, &oldprog->gen_flags,
					  &oldprog->in_hw_count,
					  &prog->gen_flags, &prog->in_hw_count,
					  true);
	अन्यथा अगर (prog)
		err = tc_setup_cb_add(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
				      skip_sw, &prog->gen_flags,
				      &prog->in_hw_count, true);
	अन्यथा
		err = tc_setup_cb_destroy(block, tp, TC_SETUP_CLSBPF, &cls_bpf,
					  skip_sw, &oldprog->gen_flags,
					  &oldprog->in_hw_count, true);

	अगर (prog && err) अणु
		cls_bpf_offload_cmd(tp, oldprog, prog, extack);
		वापस err;
	पूर्ण

	अगर (prog && skip_sw && !(prog->gen_flags & TCA_CLS_FLAGS_IN_HW))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल u32 cls_bpf_flags(u32 flags)
अणु
	वापस flags & CLS_BPF_SUPPORTED_GEN_FLAGS;
पूर्ण

अटल पूर्णांक cls_bpf_offload(काष्ठा tcf_proto *tp, काष्ठा cls_bpf_prog *prog,
			   काष्ठा cls_bpf_prog *oldprog,
			   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (prog && oldprog &&
	    cls_bpf_flags(prog->gen_flags) !=
	    cls_bpf_flags(oldprog->gen_flags))
		वापस -EINVAL;

	अगर (prog && tc_skip_hw(prog->gen_flags))
		prog = शून्य;
	अगर (oldprog && tc_skip_hw(oldprog->gen_flags))
		oldprog = शून्य;
	अगर (!prog && !oldprog)
		वापस 0;

	वापस cls_bpf_offload_cmd(tp, prog, oldprog, extack);
पूर्ण

अटल व्योम cls_bpf_stop_offload(काष्ठा tcf_proto *tp,
				 काष्ठा cls_bpf_prog *prog,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = cls_bpf_offload_cmd(tp, शून्य, prog, extack);
	अगर (err)
		pr_err("Stopping hardware offload failed: %d\n", err);
पूर्ण

अटल व्योम cls_bpf_offload_update_stats(काष्ठा tcf_proto *tp,
					 काष्ठा cls_bpf_prog *prog)
अणु
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_bpf_offload cls_bpf = अणुपूर्ण;

	tc_cls_common_offload_init(&cls_bpf.common, tp, prog->gen_flags, शून्य);
	cls_bpf.command = TC_CLSBPF_STATS;
	cls_bpf.exts = &prog->exts;
	cls_bpf.prog = prog->filter;
	cls_bpf.name = prog->bpf_name;
	cls_bpf.exts_पूर्णांकegrated = prog->exts_पूर्णांकegrated;

	tc_setup_cb_call(block, TC_SETUP_CLSBPF, &cls_bpf, false, true);
पूर्ण

अटल पूर्णांक cls_bpf_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा cls_bpf_head *head;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (head == शून्य)
		वापस -ENOBUFS;

	INIT_LIST_HEAD_RCU(&head->plist);
	idr_init(&head->handle_idr);
	rcu_assign_poपूर्णांकer(tp->root, head);

	वापस 0;
पूर्ण

अटल व्योम cls_bpf_मुक्त_parms(काष्ठा cls_bpf_prog *prog)
अणु
	अगर (cls_bpf_is_ebpf(prog))
		bpf_prog_put(prog->filter);
	अन्यथा
		bpf_prog_destroy(prog->filter);

	kमुक्त(prog->bpf_name);
	kमुक्त(prog->bpf_ops);
पूर्ण

अटल व्योम __cls_bpf_delete_prog(काष्ठा cls_bpf_prog *prog)
अणु
	tcf_exts_destroy(&prog->exts);
	tcf_exts_put_net(&prog->exts);

	cls_bpf_मुक्त_parms(prog);
	kमुक्त(prog);
पूर्ण

अटल व्योम cls_bpf_delete_prog_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cls_bpf_prog *prog = container_of(to_rcu_work(work),
						 काष्ठा cls_bpf_prog,
						 rwork);
	rtnl_lock();
	__cls_bpf_delete_prog(prog);
	rtnl_unlock();
पूर्ण

अटल व्योम __cls_bpf_delete(काष्ठा tcf_proto *tp, काष्ठा cls_bpf_prog *prog,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);

	idr_हटाओ(&head->handle_idr, prog->handle);
	cls_bpf_stop_offload(tp, prog, extack);
	list_del_rcu(&prog->link);
	tcf_unbind_filter(tp, &prog->res);
	अगर (tcf_exts_get_net(&prog->exts))
		tcf_queue_work(&prog->rwork, cls_bpf_delete_prog_work);
	अन्यथा
		__cls_bpf_delete_prog(prog);
पूर्ण

अटल पूर्णांक cls_bpf_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
			  bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);

	__cls_bpf_delete(tp, arg, extack);
	*last = list_empty(&head->plist);
	वापस 0;
पूर्ण

अटल व्योम cls_bpf_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);
	काष्ठा cls_bpf_prog *prog, *पंचांगp;

	list_क्रम_each_entry_safe(prog, पंचांगp, &head->plist, link)
		__cls_bpf_delete(tp, prog, extack);

	idr_destroy(&head->handle_idr);
	kमुक्त_rcu(head, rcu);
पूर्ण

अटल व्योम *cls_bpf_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);
	काष्ठा cls_bpf_prog *prog;

	list_क्रम_each_entry(prog, &head->plist, link) अणु
		अगर (prog->handle == handle)
			वापस prog;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cls_bpf_prog_from_ops(काष्ठा nlattr **tb, काष्ठा cls_bpf_prog *prog)
अणु
	काष्ठा sock_filter *bpf_ops;
	काष्ठा sock_fprog_kern fprog_पंचांगp;
	काष्ठा bpf_prog *fp;
	u16 bpf_size, bpf_num_ops;
	पूर्णांक ret;

	bpf_num_ops = nla_get_u16(tb[TCA_BPF_OPS_LEN]);
	अगर (bpf_num_ops > BPF_MAXINSNS || bpf_num_ops == 0)
		वापस -EINVAL;

	bpf_size = bpf_num_ops * माप(*bpf_ops);
	अगर (bpf_size != nla_len(tb[TCA_BPF_OPS]))
		वापस -EINVAL;

	bpf_ops = kmemdup(nla_data(tb[TCA_BPF_OPS]), bpf_size, GFP_KERNEL);
	अगर (bpf_ops == शून्य)
		वापस -ENOMEM;

	fprog_पंचांगp.len = bpf_num_ops;
	fprog_पंचांगp.filter = bpf_ops;

	ret = bpf_prog_create(&fp, &fprog_पंचांगp);
	अगर (ret < 0) अणु
		kमुक्त(bpf_ops);
		वापस ret;
	पूर्ण

	prog->bpf_ops = bpf_ops;
	prog->bpf_num_ops = bpf_num_ops;
	prog->bpf_name = शून्य;
	prog->filter = fp;

	वापस 0;
पूर्ण

अटल पूर्णांक cls_bpf_prog_from_efd(काष्ठा nlattr **tb, काष्ठा cls_bpf_prog *prog,
				 u32 gen_flags, स्थिर काष्ठा tcf_proto *tp)
अणु
	काष्ठा bpf_prog *fp;
	अक्षर *name = शून्य;
	bool skip_sw;
	u32 bpf_fd;

	bpf_fd = nla_get_u32(tb[TCA_BPF_FD]);
	skip_sw = gen_flags & TCA_CLS_FLAGS_SKIP_SW;

	fp = bpf_prog_get_type_dev(bpf_fd, BPF_PROG_TYPE_SCHED_CLS, skip_sw);
	अगर (IS_ERR(fp))
		वापस PTR_ERR(fp);

	अगर (tb[TCA_BPF_NAME]) अणु
		name = nla_memdup(tb[TCA_BPF_NAME], GFP_KERNEL);
		अगर (!name) अणु
			bpf_prog_put(fp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	prog->bpf_ops = शून्य;
	prog->bpf_name = name;
	prog->filter = fp;

	अगर (fp->dst_needed)
		tcf_block_netअगर_keep_dst(tp->chain->block);

	वापस 0;
पूर्ण

अटल पूर्णांक cls_bpf_set_parms(काष्ठा net *net, काष्ठा tcf_proto *tp,
			     काष्ठा cls_bpf_prog *prog, अचिन्हित दीर्घ base,
			     काष्ठा nlattr **tb, काष्ठा nlattr *est, bool ovr,
			     काष्ठा netlink_ext_ack *extack)
अणु
	bool is_bpf, is_ebpf, have_exts = false;
	u32 gen_flags = 0;
	पूर्णांक ret;

	is_bpf = tb[TCA_BPF_OPS_LEN] && tb[TCA_BPF_OPS];
	is_ebpf = tb[TCA_BPF_FD];
	अगर ((!is_bpf && !is_ebpf) || (is_bpf && is_ebpf))
		वापस -EINVAL;

	ret = tcf_exts_validate(net, tp, tb, est, &prog->exts, ovr, true,
				extack);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[TCA_BPF_FLAGS]) अणु
		u32 bpf_flags = nla_get_u32(tb[TCA_BPF_FLAGS]);

		अगर (bpf_flags & ~TCA_BPF_FLAG_ACT_सूचीECT)
			वापस -EINVAL;

		have_exts = bpf_flags & TCA_BPF_FLAG_ACT_सूचीECT;
	पूर्ण
	अगर (tb[TCA_BPF_FLAGS_GEN]) अणु
		gen_flags = nla_get_u32(tb[TCA_BPF_FLAGS_GEN]);
		अगर (gen_flags & ~CLS_BPF_SUPPORTED_GEN_FLAGS ||
		    !tc_flags_valid(gen_flags))
			वापस -EINVAL;
	पूर्ण

	prog->exts_पूर्णांकegrated = have_exts;
	prog->gen_flags = gen_flags;

	ret = is_bpf ? cls_bpf_prog_from_ops(tb, prog) :
		       cls_bpf_prog_from_efd(tb, prog, gen_flags, tp);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[TCA_BPF_CLASSID]) अणु
		prog->res.classid = nla_get_u32(tb[TCA_BPF_CLASSID]);
		tcf_bind_filter(tp, &prog->res, base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cls_bpf_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
			  काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
			  u32 handle, काष्ठा nlattr **tca,
			  व्योम **arg, bool ovr, bool rtnl_held,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);
	काष्ठा cls_bpf_prog *oldprog = *arg;
	काष्ठा nlattr *tb[TCA_BPF_MAX + 1];
	काष्ठा cls_bpf_prog *prog;
	पूर्णांक ret;

	अगर (tca[TCA_OPTIONS] == शून्य)
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(tb, TCA_BPF_MAX, tca[TCA_OPTIONS],
					  bpf_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	prog = kzalloc(माप(*prog), GFP_KERNEL);
	अगर (!prog)
		वापस -ENOBUFS;

	ret = tcf_exts_init(&prog->exts, net, TCA_BPF_ACT, TCA_BPF_POLICE);
	अगर (ret < 0)
		जाओ errout;

	अगर (oldprog) अणु
		अगर (handle && oldprog->handle != handle) अणु
			ret = -EINVAL;
			जाओ errout;
		पूर्ण
	पूर्ण

	अगर (handle == 0) अणु
		handle = 1;
		ret = idr_alloc_u32(&head->handle_idr, prog, &handle,
				    पूर्णांक_उच्च, GFP_KERNEL);
	पूर्ण अन्यथा अगर (!oldprog) अणु
		ret = idr_alloc_u32(&head->handle_idr, prog, &handle,
				    handle, GFP_KERNEL);
	पूर्ण

	अगर (ret)
		जाओ errout;
	prog->handle = handle;

	ret = cls_bpf_set_parms(net, tp, prog, base, tb, tca[TCA_RATE], ovr,
				extack);
	अगर (ret < 0)
		जाओ errout_idr;

	ret = cls_bpf_offload(tp, prog, oldprog, extack);
	अगर (ret)
		जाओ errout_parms;

	अगर (!tc_in_hw(prog->gen_flags))
		prog->gen_flags |= TCA_CLS_FLAGS_NOT_IN_HW;

	अगर (oldprog) अणु
		idr_replace(&head->handle_idr, prog, handle);
		list_replace_rcu(&oldprog->link, &prog->link);
		tcf_unbind_filter(tp, &oldprog->res);
		tcf_exts_get_net(&oldprog->exts);
		tcf_queue_work(&oldprog->rwork, cls_bpf_delete_prog_work);
	पूर्ण अन्यथा अणु
		list_add_rcu(&prog->link, &head->plist);
	पूर्ण

	*arg = prog;
	वापस 0;

errout_parms:
	cls_bpf_मुक्त_parms(prog);
errout_idr:
	अगर (!oldprog)
		idr_हटाओ(&head->handle_idr, prog->handle);
errout:
	tcf_exts_destroy(&prog->exts);
	kमुक्त(prog);
	वापस ret;
पूर्ण

अटल पूर्णांक cls_bpf_dump_bpf_info(स्थिर काष्ठा cls_bpf_prog *prog,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla;

	अगर (nla_put_u16(skb, TCA_BPF_OPS_LEN, prog->bpf_num_ops))
		वापस -EMSGSIZE;

	nla = nla_reserve(skb, TCA_BPF_OPS, prog->bpf_num_ops *
			  माप(काष्ठा sock_filter));
	अगर (nla == शून्य)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), prog->bpf_ops, nla_len(nla));

	वापस 0;
पूर्ण

अटल पूर्णांक cls_bpf_dump_ebpf_info(स्थिर काष्ठा cls_bpf_prog *prog,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla;

	अगर (prog->bpf_name &&
	    nla_put_string(skb, TCA_BPF_NAME, prog->bpf_name))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TCA_BPF_ID, prog->filter->aux->id))
		वापस -EMSGSIZE;

	nla = nla_reserve(skb, TCA_BPF_TAG, माप(prog->filter->tag));
	अगर (nla == शून्य)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), prog->filter->tag, nla_len(nla));

	वापस 0;
पूर्ण

अटल पूर्णांक cls_bpf_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
			काष्ठा sk_buff *skb, काष्ठा tcmsg *पंचांग, bool rtnl_held)
अणु
	काष्ठा cls_bpf_prog *prog = fh;
	काष्ठा nlattr *nest;
	u32 bpf_flags = 0;
	पूर्णांक ret;

	अगर (prog == शून्य)
		वापस skb->len;

	पंचांग->tcm_handle = prog->handle;

	cls_bpf_offload_update_stats(tp, prog);

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (prog->res.classid &&
	    nla_put_u32(skb, TCA_BPF_CLASSID, prog->res.classid))
		जाओ nla_put_failure;

	अगर (cls_bpf_is_ebpf(prog))
		ret = cls_bpf_dump_ebpf_info(prog, skb);
	अन्यथा
		ret = cls_bpf_dump_bpf_info(prog, skb);
	अगर (ret)
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &prog->exts) < 0)
		जाओ nla_put_failure;

	अगर (prog->exts_पूर्णांकegrated)
		bpf_flags |= TCA_BPF_FLAG_ACT_सूचीECT;
	अगर (bpf_flags && nla_put_u32(skb, TCA_BPF_FLAGS, bpf_flags))
		जाओ nla_put_failure;
	अगर (prog->gen_flags &&
	    nla_put_u32(skb, TCA_BPF_FLAGS_GEN, prog->gen_flags))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &prog->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम cls_bpf_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl,
			       व्योम *q, अचिन्हित दीर्घ base)
अणु
	काष्ठा cls_bpf_prog *prog = fh;

	अगर (prog && prog->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &prog->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &prog->res);
	पूर्ण
पूर्ण

अटल व्योम cls_bpf_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
			 bool rtnl_held)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);
	काष्ठा cls_bpf_prog *prog;

	list_क्रम_each_entry(prog, &head->plist, link) अणु
		अगर (arg->count < arg->skip)
			जाओ skip;
		अगर (arg->fn(tp, prog, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
skip:
		arg->count++;
	पूर्ण
पूर्ण

अटल पूर्णांक cls_bpf_reoffload(काष्ठा tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			     व्योम *cb_priv, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cls_bpf_head *head = rtnl_dereference(tp->root);
	काष्ठा tcf_block *block = tp->chain->block;
	काष्ठा tc_cls_bpf_offload cls_bpf = अणुपूर्ण;
	काष्ठा cls_bpf_prog *prog;
	पूर्णांक err;

	list_क्रम_each_entry(prog, &head->plist, link) अणु
		अगर (tc_skip_hw(prog->gen_flags))
			जारी;

		tc_cls_common_offload_init(&cls_bpf.common, tp, prog->gen_flags,
					   extack);
		cls_bpf.command = TC_CLSBPF_OFFLOAD;
		cls_bpf.exts = &prog->exts;
		cls_bpf.prog = add ? prog->filter : शून्य;
		cls_bpf.oldprog = add ? शून्य : prog->filter;
		cls_bpf.name = prog->bpf_name;
		cls_bpf.exts_पूर्णांकegrated = prog->exts_पूर्णांकegrated;

		err = tc_setup_cb_reoffload(block, tp, add, cb, TC_SETUP_CLSBPF,
					    &cls_bpf, cb_priv, &prog->gen_flags,
					    &prog->in_hw_count);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा tcf_proto_ops cls_bpf_ops __पढ़ो_mostly = अणु
	.kind		=	"bpf",
	.owner		=	THIS_MODULE,
	.classअगरy	=	cls_bpf_classअगरy,
	.init		=	cls_bpf_init,
	.destroy	=	cls_bpf_destroy,
	.get		=	cls_bpf_get,
	.change		=	cls_bpf_change,
	.delete		=	cls_bpf_delete,
	.walk		=	cls_bpf_walk,
	.reoffload	=	cls_bpf_reoffload,
	.dump		=	cls_bpf_dump,
	.bind_class	=	cls_bpf_bind_class,
पूर्ण;

अटल पूर्णांक __init cls_bpf_init_mod(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_bpf_ops);
पूर्ण

अटल व्योम __निकास cls_bpf_निकास_mod(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_bpf_ops);
पूर्ण

module_init(cls_bpf_init_mod);
module_निकास(cls_bpf_निकास_mod);
