<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <net/net_namespace.h>

/*
 * Functions to manage BPF programs attached to netns
 */

काष्ठा bpf_netns_link अणु
	काष्ठा bpf_link	link;
	क्रमागत bpf_attach_type type;
	क्रमागत netns_bpf_attach_type netns_type;

	/* We करोn't hold a ref to net in order to स्वतः-detach the link
	 * when netns is going away. Instead we rely on pernet
	 * pre_निकास callback to clear this poपूर्णांकer. Must be accessed
	 * with netns_bpf_mutex held.
	 */
	काष्ठा net *net;
	काष्ठा list_head node; /* node in list of links attached to net */
पूर्ण;

/* Protects updates to netns_bpf */
DEFINE_MUTEX(netns_bpf_mutex);

अटल व्योम netns_bpf_attach_type_unneed(क्रमागत netns_bpf_attach_type type)
अणु
	चयन (type) अणु
#अगर_घोषित CONFIG_INET
	हाल NETNS_BPF_SK_LOOKUP:
		अटल_branch_dec(&bpf_sk_lookup_enabled);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम netns_bpf_attach_type_need(क्रमागत netns_bpf_attach_type type)
अणु
	चयन (type) अणु
#अगर_घोषित CONFIG_INET
	हाल NETNS_BPF_SK_LOOKUP:
		अटल_branch_inc(&bpf_sk_lookup_enabled);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* Must be called with netns_bpf_mutex held. */
अटल व्योम netns_bpf_run_array_detach(काष्ठा net *net,
				       क्रमागत netns_bpf_attach_type type)
अणु
	काष्ठा bpf_prog_array *run_array;

	run_array = rcu_replace_poपूर्णांकer(net->bpf.run_array[type], शून्य,
					lockdep_is_held(&netns_bpf_mutex));
	bpf_prog_array_मुक्त(run_array);
पूर्ण

अटल पूर्णांक link_index(काष्ठा net *net, क्रमागत netns_bpf_attach_type type,
		      काष्ठा bpf_netns_link *link)
अणु
	काष्ठा bpf_netns_link *pos;
	पूर्णांक i = 0;

	list_क्रम_each_entry(pos, &net->bpf.links[type], node) अणु
		अगर (pos == link)
			वापस i;
		i++;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक link_count(काष्ठा net *net, क्रमागत netns_bpf_attach_type type)
अणु
	काष्ठा list_head *pos;
	पूर्णांक i = 0;

	list_क्रम_each(pos, &net->bpf.links[type])
		i++;
	वापस i;
पूर्ण

अटल व्योम fill_prog_array(काष्ठा net *net, क्रमागत netns_bpf_attach_type type,
			    काष्ठा bpf_prog_array *prog_array)
अणु
	काष्ठा bpf_netns_link *pos;
	अचिन्हित पूर्णांक i = 0;

	list_क्रम_each_entry(pos, &net->bpf.links[type], node) अणु
		prog_array->items[i].prog = pos->link.prog;
		i++;
	पूर्ण
पूर्ण

अटल व्योम bpf_netns_link_release(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_netns_link *net_link =
		container_of(link, काष्ठा bpf_netns_link, link);
	क्रमागत netns_bpf_attach_type type = net_link->netns_type;
	काष्ठा bpf_prog_array *old_array, *new_array;
	काष्ठा net *net;
	पूर्णांक cnt, idx;

	mutex_lock(&netns_bpf_mutex);

	/* We can race with cleanup_net, but अगर we see a non-शून्य
	 * काष्ठा net poपूर्णांकer, pre_निकास has not run yet and रुको क्रम
	 * netns_bpf_mutex.
	 */
	net = net_link->net;
	अगर (!net)
		जाओ out_unlock;

	/* Mark attach poपूर्णांक as unused */
	netns_bpf_attach_type_unneed(type);

	/* Remember link position in हाल of safe delete */
	idx = link_index(net, type, net_link);
	list_del(&net_link->node);

	cnt = link_count(net, type);
	अगर (!cnt) अणु
		netns_bpf_run_array_detach(net, type);
		जाओ out_unlock;
	पूर्ण

	old_array = rcu_dereference_रक्षित(net->bpf.run_array[type],
					      lockdep_is_held(&netns_bpf_mutex));
	new_array = bpf_prog_array_alloc(cnt, GFP_KERNEL);
	अगर (!new_array) अणु
		WARN_ON(bpf_prog_array_delete_safe_at(old_array, idx));
		जाओ out_unlock;
	पूर्ण
	fill_prog_array(net, type, new_array);
	rcu_assign_poपूर्णांकer(net->bpf.run_array[type], new_array);
	bpf_prog_array_मुक्त(old_array);

out_unlock:
	net_link->net = शून्य;
	mutex_unlock(&netns_bpf_mutex);
पूर्ण

अटल पूर्णांक bpf_netns_link_detach(काष्ठा bpf_link *link)
अणु
	bpf_netns_link_release(link);
	वापस 0;
पूर्ण

अटल व्योम bpf_netns_link_dealloc(काष्ठा bpf_link *link)
अणु
	काष्ठा bpf_netns_link *net_link =
		container_of(link, काष्ठा bpf_netns_link, link);

	kमुक्त(net_link);
पूर्ण

अटल पूर्णांक bpf_netns_link_update_prog(काष्ठा bpf_link *link,
				      काष्ठा bpf_prog *new_prog,
				      काष्ठा bpf_prog *old_prog)
अणु
	काष्ठा bpf_netns_link *net_link =
		container_of(link, काष्ठा bpf_netns_link, link);
	क्रमागत netns_bpf_attach_type type = net_link->netns_type;
	काष्ठा bpf_prog_array *run_array;
	काष्ठा net *net;
	पूर्णांक idx, ret;

	अगर (old_prog && old_prog != link->prog)
		वापस -EPERM;
	अगर (new_prog->type != link->prog->type)
		वापस -EINVAL;

	mutex_lock(&netns_bpf_mutex);

	net = net_link->net;
	अगर (!net || !check_net(net)) अणु
		/* Link स्वतः-detached or netns dying */
		ret = -ENOLINK;
		जाओ out_unlock;
	पूर्ण

	run_array = rcu_dereference_रक्षित(net->bpf.run_array[type],
					      lockdep_is_held(&netns_bpf_mutex));
	idx = link_index(net, type, net_link);
	ret = bpf_prog_array_update_at(run_array, idx, new_prog);
	अगर (ret)
		जाओ out_unlock;

	old_prog = xchg(&link->prog, new_prog);
	bpf_prog_put(old_prog);

out_unlock:
	mutex_unlock(&netns_bpf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_netns_link_fill_info(स्थिर काष्ठा bpf_link *link,
				    काष्ठा bpf_link_info *info)
अणु
	स्थिर काष्ठा bpf_netns_link *net_link =
		container_of(link, काष्ठा bpf_netns_link, link);
	अचिन्हित पूर्णांक inum = 0;
	काष्ठा net *net;

	mutex_lock(&netns_bpf_mutex);
	net = net_link->net;
	अगर (net && check_net(net))
		inum = net->ns.inum;
	mutex_unlock(&netns_bpf_mutex);

	info->netns.netns_ino = inum;
	info->netns.attach_type = net_link->type;
	वापस 0;
पूर्ण

अटल व्योम bpf_netns_link_show_fdinfo(स्थिर काष्ठा bpf_link *link,
				       काष्ठा seq_file *seq)
अणु
	काष्ठा bpf_link_info info = अणुपूर्ण;

	bpf_netns_link_fill_info(link, &info);
	seq_म_लिखो(seq,
		   "netns_ino:\t%u\n"
		   "attach_type:\t%u\n",
		   info.netns.netns_ino,
		   info.netns.attach_type);
पूर्ण

अटल स्थिर काष्ठा bpf_link_ops bpf_netns_link_ops = अणु
	.release = bpf_netns_link_release,
	.dealloc = bpf_netns_link_dealloc,
	.detach = bpf_netns_link_detach,
	.update_prog = bpf_netns_link_update_prog,
	.fill_link_info = bpf_netns_link_fill_info,
	.show_fdinfo = bpf_netns_link_show_fdinfo,
पूर्ण;

/* Must be called with netns_bpf_mutex held. */
अटल पूर्णांक __netns_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
				  जोड़ bpf_attr __user *uattr,
				  काष्ठा net *net,
				  क्रमागत netns_bpf_attach_type type)
अणु
	__u32 __user *prog_ids = u64_to_user_ptr(attr->query.prog_ids);
	काष्ठा bpf_prog_array *run_array;
	u32 prog_cnt = 0, flags = 0;

	run_array = rcu_dereference_रक्षित(net->bpf.run_array[type],
					      lockdep_is_held(&netns_bpf_mutex));
	अगर (run_array)
		prog_cnt = bpf_prog_array_length(run_array);

	अगर (copy_to_user(&uattr->query.attach_flags, &flags, माप(flags)))
		वापस -EFAULT;
	अगर (copy_to_user(&uattr->query.prog_cnt, &prog_cnt, माप(prog_cnt)))
		वापस -EFAULT;
	अगर (!attr->query.prog_cnt || !prog_ids || !prog_cnt)
		वापस 0;

	वापस bpf_prog_array_copy_to_user(run_array, prog_ids,
					   attr->query.prog_cnt);
पूर्ण

पूर्णांक netns_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
			 जोड़ bpf_attr __user *uattr)
अणु
	क्रमागत netns_bpf_attach_type type;
	काष्ठा net *net;
	पूर्णांक ret;

	अगर (attr->query.query_flags)
		वापस -EINVAL;

	type = to_netns_bpf_attach_type(attr->query.attach_type);
	अगर (type < 0)
		वापस -EINVAL;

	net = get_net_ns_by_fd(attr->query.target_fd);
	अगर (IS_ERR(net))
		वापस PTR_ERR(net);

	mutex_lock(&netns_bpf_mutex);
	ret = __netns_bpf_prog_query(attr, uattr, net, type);
	mutex_unlock(&netns_bpf_mutex);

	put_net(net);
	वापस ret;
पूर्ण

पूर्णांक netns_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_array *run_array;
	क्रमागत netns_bpf_attach_type type;
	काष्ठा bpf_prog *attached;
	काष्ठा net *net;
	पूर्णांक ret;

	अगर (attr->target_fd || attr->attach_flags || attr->replace_bpf_fd)
		वापस -EINVAL;

	type = to_netns_bpf_attach_type(attr->attach_type);
	अगर (type < 0)
		वापस -EINVAL;

	net = current->nsproxy->net_ns;
	mutex_lock(&netns_bpf_mutex);

	/* Attaching prog directly is not compatible with links */
	अगर (!list_empty(&net->bpf.links[type])) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	चयन (type) अणु
	हाल NETNS_BPF_FLOW_DISSECTOR:
		ret = flow_dissector_bpf_prog_attach_check(net, prog);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret)
		जाओ out_unlock;

	attached = net->bpf.progs[type];
	अगर (attached == prog) अणु
		/* The same program cannot be attached twice */
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	run_array = rcu_dereference_रक्षित(net->bpf.run_array[type],
					      lockdep_is_held(&netns_bpf_mutex));
	अगर (run_array) अणु
		WRITE_ONCE(run_array->items[0].prog, prog);
	पूर्ण अन्यथा अणु
		run_array = bpf_prog_array_alloc(1, GFP_KERNEL);
		अगर (!run_array) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		run_array->items[0].prog = prog;
		rcu_assign_poपूर्णांकer(net->bpf.run_array[type], run_array);
	पूर्ण

	net->bpf.progs[type] = prog;
	अगर (attached)
		bpf_prog_put(attached);

out_unlock:
	mutex_unlock(&netns_bpf_mutex);

	वापस ret;
पूर्ण

/* Must be called with netns_bpf_mutex held. */
अटल पूर्णांक __netns_bpf_prog_detach(काष्ठा net *net,
				   क्रमागत netns_bpf_attach_type type,
				   काष्ठा bpf_prog *old)
अणु
	काष्ठा bpf_prog *attached;

	/* Progs attached via links cannot be detached */
	अगर (!list_empty(&net->bpf.links[type]))
		वापस -EINVAL;

	attached = net->bpf.progs[type];
	अगर (!attached || attached != old)
		वापस -ENOENT;
	netns_bpf_run_array_detach(net, type);
	net->bpf.progs[type] = शून्य;
	bpf_prog_put(attached);
	वापस 0;
पूर्ण

पूर्णांक netns_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr, क्रमागत bpf_prog_type ptype)
अणु
	क्रमागत netns_bpf_attach_type type;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	अगर (attr->target_fd)
		वापस -EINVAL;

	type = to_netns_bpf_attach_type(attr->attach_type);
	अगर (type < 0)
		वापस -EINVAL;

	prog = bpf_prog_get_type(attr->attach_bpf_fd, ptype);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	mutex_lock(&netns_bpf_mutex);
	ret = __netns_bpf_prog_detach(current->nsproxy->net_ns, type, prog);
	mutex_unlock(&netns_bpf_mutex);

	bpf_prog_put(prog);

	वापस ret;
पूर्ण

अटल पूर्णांक netns_bpf_max_progs(क्रमागत netns_bpf_attach_type type)
अणु
	चयन (type) अणु
	हाल NETNS_BPF_FLOW_DISSECTOR:
		वापस 1;
	हाल NETNS_BPF_SK_LOOKUP:
		वापस 64;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक netns_bpf_link_attach(काष्ठा net *net, काष्ठा bpf_link *link,
				 क्रमागत netns_bpf_attach_type type)
अणु
	काष्ठा bpf_netns_link *net_link =
		container_of(link, काष्ठा bpf_netns_link, link);
	काष्ठा bpf_prog_array *run_array;
	पूर्णांक cnt, err;

	mutex_lock(&netns_bpf_mutex);

	cnt = link_count(net, type);
	अगर (cnt >= netns_bpf_max_progs(type)) अणु
		err = -E2BIG;
		जाओ out_unlock;
	पूर्ण
	/* Links are not compatible with attaching prog directly */
	अगर (net->bpf.progs[type]) अणु
		err = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	चयन (type) अणु
	हाल NETNS_BPF_FLOW_DISSECTOR:
		err = flow_dissector_bpf_prog_attach_check(net, link->prog);
		अवरोध;
	हाल NETNS_BPF_SK_LOOKUP:
		err = 0; /* nothing to check */
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (err)
		जाओ out_unlock;

	run_array = bpf_prog_array_alloc(cnt + 1, GFP_KERNEL);
	अगर (!run_array) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	list_add_tail(&net_link->node, &net->bpf.links[type]);

	fill_prog_array(net, type, run_array);
	run_array = rcu_replace_poपूर्णांकer(net->bpf.run_array[type], run_array,
					lockdep_is_held(&netns_bpf_mutex));
	bpf_prog_array_मुक्त(run_array);

	/* Mark attach poपूर्णांक as used */
	netns_bpf_attach_type_need(type);

out_unlock:
	mutex_unlock(&netns_bpf_mutex);
	वापस err;
पूर्ण

पूर्णांक netns_bpf_link_create(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	क्रमागत netns_bpf_attach_type netns_type;
	काष्ठा bpf_link_primer link_primer;
	काष्ठा bpf_netns_link *net_link;
	क्रमागत bpf_attach_type type;
	काष्ठा net *net;
	पूर्णांक err;

	अगर (attr->link_create.flags)
		वापस -EINVAL;

	type = attr->link_create.attach_type;
	netns_type = to_netns_bpf_attach_type(type);
	अगर (netns_type < 0)
		वापस -EINVAL;

	net = get_net_ns_by_fd(attr->link_create.target_fd);
	अगर (IS_ERR(net))
		वापस PTR_ERR(net);

	net_link = kzalloc(माप(*net_link), GFP_USER);
	अगर (!net_link) अणु
		err = -ENOMEM;
		जाओ out_put_net;
	पूर्ण
	bpf_link_init(&net_link->link, BPF_LINK_TYPE_NETNS,
		      &bpf_netns_link_ops, prog);
	net_link->net = net;
	net_link->type = type;
	net_link->netns_type = netns_type;

	err = bpf_link_prime(&net_link->link, &link_primer);
	अगर (err) अणु
		kमुक्त(net_link);
		जाओ out_put_net;
	पूर्ण

	err = netns_bpf_link_attach(net, &net_link->link, netns_type);
	अगर (err) अणु
		bpf_link_cleanup(&link_primer);
		जाओ out_put_net;
	पूर्ण

	put_net(net);
	वापस bpf_link_settle(&link_primer);

out_put_net:
	put_net(net);
	वापस err;
पूर्ण

अटल पूर्णांक __net_init netns_bpf_pernet_init(काष्ठा net *net)
अणु
	पूर्णांक type;

	क्रम (type = 0; type < MAX_NETNS_BPF_ATTACH_TYPE; type++)
		INIT_LIST_HEAD(&net->bpf.links[type]);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास netns_bpf_pernet_pre_निकास(काष्ठा net *net)
अणु
	क्रमागत netns_bpf_attach_type type;
	काष्ठा bpf_netns_link *net_link;

	mutex_lock(&netns_bpf_mutex);
	क्रम (type = 0; type < MAX_NETNS_BPF_ATTACH_TYPE; type++) अणु
		netns_bpf_run_array_detach(net, type);
		list_क्रम_each_entry(net_link, &net->bpf.links[type], node) अणु
			net_link->net = शून्य; /* स्वतः-detach link */
			netns_bpf_attach_type_unneed(type);
		पूर्ण
		अगर (net->bpf.progs[type])
			bpf_prog_put(net->bpf.progs[type]);
	पूर्ण
	mutex_unlock(&netns_bpf_mutex);
पूर्ण

अटल काष्ठा pernet_operations netns_bpf_pernet_ops __net_initdata = अणु
	.init = netns_bpf_pernet_init,
	.pre_निकास = netns_bpf_pernet_pre_निकास,
पूर्ण;

अटल पूर्णांक __init netns_bpf_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&netns_bpf_pernet_ops);
पूर्ण

subsys_initcall(netns_bpf_init);
