<शैली गुरु>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/fib_notअगरier.h>

अटल अचिन्हित पूर्णांक fib_notअगरier_net_id;

काष्ठा fib_notअगरier_net अणु
	काष्ठा list_head fib_notअगरier_ops;
	काष्ठा atomic_notअगरier_head fib_chain;
पूर्ण;

पूर्णांक call_fib_notअगरier(काष्ठा notअगरier_block *nb,
		      क्रमागत fib_event_type event_type,
		      काष्ठा fib_notअगरier_info *info)
अणु
	पूर्णांक err;

	err = nb->notअगरier_call(nb, event_type, info);
	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण
EXPORT_SYMBOL(call_fib_notअगरier);

पूर्णांक call_fib_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);
	पूर्णांक err;

	err = atomic_notअगरier_call_chain(&fn_net->fib_chain, event_type, info);
	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण
EXPORT_SYMBOL(call_fib_notअगरiers);

अटल अचिन्हित पूर्णांक fib_seq_sum(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);
	काष्ठा fib_notअगरier_ops *ops;
	अचिन्हित पूर्णांक fib_seq = 0;

	rtnl_lock();
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ops, &fn_net->fib_notअगरier_ops, list) अणु
		अगर (!try_module_get(ops->owner))
			जारी;
		fib_seq += ops->fib_seq_पढ़ो(net);
		module_put(ops->owner);
	पूर्ण
	rcu_पढ़ो_unlock();
	rtnl_unlock();

	वापस fib_seq;
पूर्ण

अटल पूर्णांक fib_net_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);
	काष्ठा fib_notअगरier_ops *ops;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ops, &fn_net->fib_notअगरier_ops, list) अणु
		अगर (!try_module_get(ops->owner))
			जारी;
		err = ops->fib_dump(net, nb, extack);
		module_put(ops->owner);
		अगर (err)
			जाओ unlock;
	पूर्ण

unlock:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल bool fib_dump_is_consistent(काष्ठा net *net, काष्ठा notअगरier_block *nb,
				   व्योम (*cb)(काष्ठा notअगरier_block *nb),
				   अचिन्हित पूर्णांक fib_seq)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);

	atomic_notअगरier_chain_रेजिस्टर(&fn_net->fib_chain, nb);
	अगर (fib_seq == fib_seq_sum(net))
		वापस true;
	atomic_notअगरier_chain_unरेजिस्टर(&fn_net->fib_chain, nb);
	अगर (cb)
		cb(nb);
	वापस false;
पूर्ण

#घोषणा FIB_DUMP_MAX_RETRIES 5
पूर्णांक रेजिस्टर_fib_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			  व्योम (*cb)(काष्ठा notअगरier_block *nb),
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक retries = 0;
	पूर्णांक err;

	करो अणु
		अचिन्हित पूर्णांक fib_seq = fib_seq_sum(net);

		err = fib_net_dump(net, nb, extack);
		अगर (err)
			वापस err;

		अगर (fib_dump_is_consistent(net, nb, cb, fib_seq))
			वापस 0;
	पूर्ण जबतक (++retries < FIB_DUMP_MAX_RETRIES);

	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_fib_notअगरier);

पूर्णांक unरेजिस्टर_fib_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);

	वापस atomic_notअगरier_chain_unरेजिस्टर(&fn_net->fib_chain, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_fib_notअगरier);

अटल पूर्णांक __fib_notअगरier_ops_रेजिस्टर(काष्ठा fib_notअगरier_ops *ops,
				       काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);
	काष्ठा fib_notअगरier_ops *o;

	list_क्रम_each_entry(o, &fn_net->fib_notअगरier_ops, list)
		अगर (ops->family == o->family)
			वापस -EEXIST;
	list_add_tail_rcu(&ops->list, &fn_net->fib_notअगरier_ops);
	वापस 0;
पूर्ण

काष्ठा fib_notअगरier_ops *
fib_notअगरier_ops_रेजिस्टर(स्थिर काष्ठा fib_notअगरier_ops *पंचांगpl, काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_ops *ops;
	पूर्णांक err;

	ops = kmemdup(पंचांगpl, माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस ERR_PTR(-ENOMEM);

	err = __fib_notअगरier_ops_रेजिस्टर(ops, net);
	अगर (err)
		जाओ err_रेजिस्टर;

	वापस ops;

err_रेजिस्टर:
	kमुक्त(ops);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(fib_notअगरier_ops_रेजिस्टर);

व्योम fib_notअगरier_ops_unरेजिस्टर(काष्ठा fib_notअगरier_ops *ops)
अणु
	list_del_rcu(&ops->list);
	kमुक्त_rcu(ops, rcu);
पूर्ण
EXPORT_SYMBOL(fib_notअगरier_ops_unरेजिस्टर);

अटल पूर्णांक __net_init fib_notअगरier_net_init(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);

	INIT_LIST_HEAD(&fn_net->fib_notअगरier_ops);
	ATOMIC_INIT_NOTIFIER_HEAD(&fn_net->fib_chain);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास fib_notअगरier_net_निकास(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_net *fn_net = net_generic(net, fib_notअगरier_net_id);

	WARN_ON_ONCE(!list_empty(&fn_net->fib_notअगरier_ops));
पूर्ण

अटल काष्ठा pernet_operations fib_notअगरier_net_ops = अणु
	.init = fib_notअगरier_net_init,
	.निकास = fib_notअगरier_net_निकास,
	.id = &fib_notअगरier_net_id,
	.size = माप(काष्ठा fib_notअगरier_net),
पूर्ण;

अटल पूर्णांक __init fib_notअगरier_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&fib_notअगरier_net_ops);
पूर्ण

subsys_initcall(fib_notअगरier_init);
