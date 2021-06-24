<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Routing netlink socket पूर्णांकerface: protocol independent part.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 *	Fixes:
 *	Vitaly E. Lavrov		RTA_OK arithmetics was wrong.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/capability.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/bpf.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/arp.h>
#समावेश <net/route.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <net/sock.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/fib_rules.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>

#घोषणा RTNL_MAX_TYPE		50
#घोषणा RTNL_SLAVE_MAX_TYPE	40

काष्ठा rtnl_link अणु
	rtnl_करोit_func		करोit;
	rtnl_dumpit_func	dumpit;
	काष्ठा module		*owner;
	अचिन्हित पूर्णांक		flags;
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल DEFINE_MUTEX(rtnl_mutex);

व्योम rtnl_lock(व्योम)
अणु
	mutex_lock(&rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(rtnl_lock);

पूर्णांक rtnl_lock_समाप्तable(व्योम)
अणु
	वापस mutex_lock_समाप्तable(&rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(rtnl_lock_समाप्तable);

अटल काष्ठा sk_buff *defer_kमुक्त_skb_list;
व्योम rtnl_kमुक्त_skbs(काष्ठा sk_buff *head, काष्ठा sk_buff *tail)
अणु
	अगर (head && tail) अणु
		tail->next = defer_kमुक्त_skb_list;
		defer_kमुक्त_skb_list = head;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtnl_kमुक्त_skbs);

व्योम __rtnl_unlock(व्योम)
अणु
	काष्ठा sk_buff *head = defer_kमुक्त_skb_list;

	defer_kमुक्त_skb_list = शून्य;

	mutex_unlock(&rtnl_mutex);

	जबतक (head) अणु
		काष्ठा sk_buff *next = head->next;

		kमुक्त_skb(head);
		cond_resched();
		head = next;
	पूर्ण
पूर्ण

व्योम rtnl_unlock(व्योम)
अणु
	/* This fellow will unlock it क्रम us. */
	netdev_run_toकरो();
पूर्ण
EXPORT_SYMBOL(rtnl_unlock);

पूर्णांक rtnl_trylock(व्योम)
अणु
	वापस mutex_trylock(&rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(rtnl_trylock);

पूर्णांक rtnl_is_locked(व्योम)
अणु
	वापस mutex_is_locked(&rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(rtnl_is_locked);

bool refcount_dec_and_rtnl_lock(refcount_t *r)
अणु
	वापस refcount_dec_and_mutex_lock(r, &rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(refcount_dec_and_rtnl_lock);

#अगर_घोषित CONFIG_PROVE_LOCKING
bool lockdep_rtnl_is_held(व्योम)
अणु
	वापस lockdep_is_held(&rtnl_mutex);
पूर्ण
EXPORT_SYMBOL(lockdep_rtnl_is_held);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PROVE_LOCKING */

अटल काष्ठा rtnl_link __rcu *__rcu *rtnl_msg_handlers[RTNL_FAMILY_MAX + 1];

अटल अंतरभूत पूर्णांक rपंचांग_msgindex(पूर्णांक msgtype)
अणु
	पूर्णांक msgindex = msgtype - RTM_BASE;

	/*
	 * msgindex < 0 implies someone tried to रेजिस्टर a netlink
	 * control code. msgindex >= RTM_NR_MSGTYPES may indicate that
	 * the message type has not been added to linux/rtnetlink.h
	 */
	BUG_ON(msgindex < 0 || msgindex >= RTM_NR_MSGTYPES);

	वापस msgindex;
पूर्ण

अटल काष्ठा rtnl_link *rtnl_get_link(पूर्णांक protocol, पूर्णांक msgtype)
अणु
	काष्ठा rtnl_link __rcu **tab;

	अगर (protocol >= ARRAY_SIZE(rtnl_msg_handlers))
		protocol = PF_UNSPEC;

	tab = rcu_dereference_rtnl(rtnl_msg_handlers[protocol]);
	अगर (!tab)
		tab = rcu_dereference_rtnl(rtnl_msg_handlers[PF_UNSPEC]);

	वापस rcu_dereference_rtnl(tab[msgtype]);
पूर्ण

अटल पूर्णांक rtnl_रेजिस्टर_पूर्णांकernal(काष्ठा module *owner,
				  पूर्णांक protocol, पूर्णांक msgtype,
				  rtnl_करोit_func करोit, rtnl_dumpit_func dumpit,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rtnl_link *link, *old;
	काष्ठा rtnl_link __rcu **tab;
	पूर्णांक msgindex;
	पूर्णांक ret = -ENOBUFS;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);
	msgindex = rपंचांग_msgindex(msgtype);

	rtnl_lock();
	tab = rtnl_dereference(rtnl_msg_handlers[protocol]);
	अगर (tab == शून्य) अणु
		tab = kसुस्मृति(RTM_NR_MSGTYPES, माप(व्योम *), GFP_KERNEL);
		अगर (!tab)
			जाओ unlock;

		/* ensures we see the 0 stores */
		rcu_assign_poपूर्णांकer(rtnl_msg_handlers[protocol], tab);
	पूर्ण

	old = rtnl_dereference(tab[msgindex]);
	अगर (old) अणु
		link = kmemdup(old, माप(*old), GFP_KERNEL);
		अगर (!link)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		link = kzalloc(माप(*link), GFP_KERNEL);
		अगर (!link)
			जाओ unlock;
	पूर्ण

	WARN_ON(link->owner && link->owner != owner);
	link->owner = owner;

	WARN_ON(करोit && link->करोit && link->करोit != करोit);
	अगर (करोit)
		link->करोit = करोit;
	WARN_ON(dumpit && link->dumpit && link->dumpit != dumpit);
	अगर (dumpit)
		link->dumpit = dumpit;

	link->flags |= flags;

	/* publish protocol:msgtype */
	rcu_assign_poपूर्णांकer(tab[msgindex], link);
	ret = 0;
	अगर (old)
		kमुक्त_rcu(old, rcu);
unlock:
	rtnl_unlock();
	वापस ret;
पूर्ण

/**
 * rtnl_रेजिस्टर_module - Register a rtnetlink message type
 *
 * @owner: module रेजिस्टरing the hook (THIS_MODULE)
 * @protocol: Protocol family or PF_UNSPEC
 * @msgtype: rtnetlink message type
 * @करोit: Function poपूर्णांकer called क्रम each request message
 * @dumpit: Function poपूर्णांकer called क्रम each dump request (NLM_F_DUMP) message
 * @flags: rtnl_link_flags to modअगरiy behaviour of करोit/dumpit functions
 *
 * Like rtnl_रेजिस्टर, but क्रम use by removable modules.
 */
पूर्णांक rtnl_रेजिस्टर_module(काष्ठा module *owner,
			 पूर्णांक protocol, पूर्णांक msgtype,
			 rtnl_करोit_func करोit, rtnl_dumpit_func dumpit,
			 अचिन्हित पूर्णांक flags)
अणु
	वापस rtnl_रेजिस्टर_पूर्णांकernal(owner, protocol, msgtype,
				      करोit, dumpit, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_रेजिस्टर_module);

/**
 * rtnl_रेजिस्टर - Register a rtnetlink message type
 * @protocol: Protocol family or PF_UNSPEC
 * @msgtype: rtnetlink message type
 * @करोit: Function poपूर्णांकer called क्रम each request message
 * @dumpit: Function poपूर्णांकer called क्रम each dump request (NLM_F_DUMP) message
 * @flags: rtnl_link_flags to modअगरiy behaviour of करोit/dumpit functions
 *
 * Registers the specअगरied function poपूर्णांकers (at least one of them has
 * to be non-शून्य) to be called whenever a request message क्रम the
 * specअगरied protocol family and message type is received.
 *
 * The special protocol family PF_UNSPEC may be used to define fallback
 * function poपूर्णांकers क्रम the हाल when no entry क्रम the specअगरic protocol
 * family exists.
 */
व्योम rtnl_रेजिस्टर(पूर्णांक protocol, पूर्णांक msgtype,
		   rtnl_करोit_func करोit, rtnl_dumpit_func dumpit,
		   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	err = rtnl_रेजिस्टर_पूर्णांकernal(शून्य, protocol, msgtype, करोit, dumpit,
				     flags);
	अगर (err)
		pr_err("Unable to register rtnetlink message handler, "
		       "protocol = %d, message type = %d\n", protocol, msgtype);
पूर्ण

/**
 * rtnl_unरेजिस्टर - Unरेजिस्टर a rtnetlink message type
 * @protocol: Protocol family or PF_UNSPEC
 * @msgtype: rtnetlink message type
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक rtnl_unरेजिस्टर(पूर्णांक protocol, पूर्णांक msgtype)
अणु
	काष्ठा rtnl_link __rcu **tab;
	काष्ठा rtnl_link *link;
	पूर्णांक msgindex;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);
	msgindex = rपंचांग_msgindex(msgtype);

	rtnl_lock();
	tab = rtnl_dereference(rtnl_msg_handlers[protocol]);
	अगर (!tab) अणु
		rtnl_unlock();
		वापस -ENOENT;
	पूर्ण

	link = rtnl_dereference(tab[msgindex]);
	rcu_assign_poपूर्णांकer(tab[msgindex], शून्य);
	rtnl_unlock();

	kमुक्त_rcu(link, rcu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_unरेजिस्टर);

/**
 * rtnl_unरेजिस्टर_all - Unरेजिस्टर all rtnetlink message type of a protocol
 * @protocol : Protocol family or PF_UNSPEC
 *
 * Identical to calling rtnl_unregster() क्रम all रेजिस्टरed message types
 * of a certain protocol family.
 */
व्योम rtnl_unरेजिस्टर_all(पूर्णांक protocol)
अणु
	काष्ठा rtnl_link __rcu **tab;
	काष्ठा rtnl_link *link;
	पूर्णांक msgindex;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);

	rtnl_lock();
	tab = rtnl_dereference(rtnl_msg_handlers[protocol]);
	अगर (!tab) अणु
		rtnl_unlock();
		वापस;
	पूर्ण
	RCU_INIT_POINTER(rtnl_msg_handlers[protocol], शून्य);
	क्रम (msgindex = 0; msgindex < RTM_NR_MSGTYPES; msgindex++) अणु
		link = rtnl_dereference(tab[msgindex]);
		अगर (!link)
			जारी;

		rcu_assign_poपूर्णांकer(tab[msgindex], शून्य);
		kमुक्त_rcu(link, rcu);
	पूर्ण
	rtnl_unlock();

	synchronize_net();

	kमुक्त(tab);
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_unरेजिस्टर_all);

अटल LIST_HEAD(link_ops);

अटल स्थिर काष्ठा rtnl_link_ops *rtnl_link_ops_get(स्थिर अक्षर *kind)
अणु
	स्थिर काष्ठा rtnl_link_ops *ops;

	list_क्रम_each_entry(ops, &link_ops, list) अणु
		अगर (!म_भेद(ops->kind, kind))
			वापस ops;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * __rtnl_link_रेजिस्टर - Register rtnl_link_ops with rtnetlink.
 * @ops: काष्ठा rtnl_link_ops * to रेजिस्टर
 *
 * The caller must hold the rtnl_mutex. This function should be used
 * by drivers that create devices during module initialization. It
 * must be called beक्रमe रेजिस्टरing the devices.
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक __rtnl_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	अगर (rtnl_link_ops_get(ops->kind))
		वापस -EEXIST;

	/* The check क्रम setup is here because अगर ops
	 * करोes not have that filled up, it is not possible
	 * to use the ops क्रम creating device. So करो not
	 * fill up dellink as well. That disables rtnl_dellink.
	 */
	अगर (ops->setup && !ops->dellink)
		ops->dellink = unरेजिस्टर_netdevice_queue;

	list_add_tail(&ops->list, &link_ops);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__rtnl_link_रेजिस्टर);

/**
 * rtnl_link_रेजिस्टर - Register rtnl_link_ops with rtnetlink.
 * @ops: काष्ठा rtnl_link_ops * to रेजिस्टर
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक rtnl_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	पूर्णांक err;

	/* Sanity-check max sizes to aव्योम stack buffer overflow. */
	अगर (WARN_ON(ops->maxtype > RTNL_MAX_TYPE ||
		    ops->slave_maxtype > RTNL_SLAVE_MAX_TYPE))
		वापस -EINVAL;

	rtnl_lock();
	err = __rtnl_link_रेजिस्टर(ops);
	rtnl_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_link_रेजिस्टर);

अटल व्योम __rtnl_समाप्त_links(काष्ठा net *net, काष्ठा rtnl_link_ops *ops)
अणु
	काष्ठा net_device *dev;
	LIST_HEAD(list_समाप्त);

	क्रम_each_netdev(net, dev) अणु
		अगर (dev->rtnl_link_ops == ops)
			ops->dellink(dev, &list_समाप्त);
	पूर्ण
	unरेजिस्टर_netdevice_many(&list_समाप्त);
पूर्ण

/**
 * __rtnl_link_unरेजिस्टर - Unरेजिस्टर rtnl_link_ops from rtnetlink.
 * @ops: काष्ठा rtnl_link_ops * to unरेजिस्टर
 *
 * The caller must hold the rtnl_mutex and guarantee net_namespace_list
 * पूर्णांकegrity (hold pernet_ops_rwsem क्रम writing to बंद the race
 * with setup_net() and cleanup_net()).
 */
व्योम __rtnl_link_unरेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	काष्ठा net *net;

	क्रम_each_net(net) अणु
		__rtnl_समाप्त_links(net, ops);
	पूर्ण
	list_del(&ops->list);
पूर्ण
EXPORT_SYMBOL_GPL(__rtnl_link_unरेजिस्टर);

/* Return with the rtnl_lock held when there are no network
 * devices unरेजिस्टरing in any network namespace.
 */
अटल व्योम rtnl_lock_unरेजिस्टरing_all(व्योम)
अणु
	काष्ठा net *net;
	bool unरेजिस्टरing;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(&netdev_unरेजिस्टरing_wq, &रुको);
	क्रम (;;) अणु
		unरेजिस्टरing = false;
		rtnl_lock();
		/* We held ग_लिखो locked pernet_ops_rwsem, and parallel
		 * setup_net() and cleanup_net() are not possible.
		 */
		क्रम_each_net(net) अणु
			अगर (net->dev_unreg_count > 0) अणु
				unरेजिस्टरing = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!unरेजिस्टरing)
			अवरोध;
		__rtnl_unlock();

		रुको_woken(&रुको, TASK_UNINTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(&netdev_unरेजिस्टरing_wq, &रुको);
पूर्ण

/**
 * rtnl_link_unरेजिस्टर - Unरेजिस्टर rtnl_link_ops from rtnetlink.
 * @ops: काष्ठा rtnl_link_ops * to unरेजिस्टर
 */
व्योम rtnl_link_unरेजिस्टर(काष्ठा rtnl_link_ops *ops)
अणु
	/* Close the race with setup_net() and cleanup_net() */
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	rtnl_lock_unरेजिस्टरing_all();
	__rtnl_link_unरेजिस्टर(ops);
	rtnl_unlock();
	up_ग_लिखो(&pernet_ops_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_link_unरेजिस्टर);

अटल माप_प्रकार rtnl_link_get_slave_info_data_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master_dev;
	स्थिर काष्ठा rtnl_link_ops *ops;
	माप_प्रकार size = 0;

	rcu_पढ़ो_lock();

	master_dev = netdev_master_upper_dev_get_rcu((काष्ठा net_device *)dev);
	अगर (!master_dev)
		जाओ out;

	ops = master_dev->rtnl_link_ops;
	अगर (!ops || !ops->get_slave_size)
		जाओ out;
	/* IFLA_INFO_SLAVE_DATA + nested data */
	size = nla_total_size(माप(काष्ठा nlattr)) +
	       ops->get_slave_size(master_dev, dev);

out:
	rcu_पढ़ो_unlock();
	वापस size;
पूर्ण

अटल माप_प्रकार rtnl_link_get_size(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा rtnl_link_ops *ops = dev->rtnl_link_ops;
	माप_प्रकार size;

	अगर (!ops)
		वापस 0;

	size = nla_total_size(माप(काष्ठा nlattr)) + /* IFLA_LINKINFO */
	       nla_total_size(म_माप(ops->kind) + 1);  /* IFLA_INFO_KIND */

	अगर (ops->get_size)
		/* IFLA_INFO_DATA + nested data */
		size += nla_total_size(माप(काष्ठा nlattr)) +
			ops->get_size(dev);

	अगर (ops->get_xstats_size)
		/* IFLA_INFO_XSTATS */
		size += nla_total_size(ops->get_xstats_size(dev));

	size += rtnl_link_get_slave_info_data_size(dev);

	वापस size;
पूर्ण

अटल LIST_HEAD(rtnl_af_ops);

अटल स्थिर काष्ठा rtnl_af_ops *rtnl_af_lookup(स्थिर पूर्णांक family)
अणु
	स्थिर काष्ठा rtnl_af_ops *ops;

	list_क्रम_each_entry_rcu(ops, &rtnl_af_ops, list) अणु
		अगर (ops->family == family)
			वापस ops;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * rtnl_af_रेजिस्टर - Register rtnl_af_ops with rtnetlink.
 * @ops: काष्ठा rtnl_af_ops * to रेजिस्टर
 *
 * Returns 0 on success or a negative error code.
 */
व्योम rtnl_af_रेजिस्टर(काष्ठा rtnl_af_ops *ops)
अणु
	rtnl_lock();
	list_add_tail_rcu(&ops->list, &rtnl_af_ops);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_af_रेजिस्टर);

/**
 * rtnl_af_unरेजिस्टर - Unरेजिस्टर rtnl_af_ops from rtnetlink.
 * @ops: काष्ठा rtnl_af_ops * to unरेजिस्टर
 */
व्योम rtnl_af_unरेजिस्टर(काष्ठा rtnl_af_ops *ops)
अणु
	rtnl_lock();
	list_del_rcu(&ops->list);
	rtnl_unlock();

	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_af_unरेजिस्टर);

अटल माप_प्रकार rtnl_link_get_af_size(स्थिर काष्ठा net_device *dev,
				    u32 ext_filter_mask)
अणु
	काष्ठा rtnl_af_ops *af_ops;
	माप_प्रकार size;

	/* IFLA_AF_SPEC */
	size = nla_total_size(माप(काष्ठा nlattr));

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(af_ops, &rtnl_af_ops, list) अणु
		अगर (af_ops->get_link_af_size) अणु
			/* AF_* + nested data */
			size += nla_total_size(माप(काष्ठा nlattr)) +
				af_ops->get_link_af_size(dev, ext_filter_mask);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस size;
पूर्ण

अटल bool rtnl_have_link_slave_info(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master_dev;
	bool ret = false;

	rcu_पढ़ो_lock();

	master_dev = netdev_master_upper_dev_get_rcu((काष्ठा net_device *)dev);
	अगर (master_dev && master_dev->rtnl_link_ops)
		ret = true;
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक rtnl_link_slave_info_fill(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master_dev;
	स्थिर काष्ठा rtnl_link_ops *ops;
	काष्ठा nlattr *slave_data;
	पूर्णांक err;

	master_dev = netdev_master_upper_dev_get((काष्ठा net_device *) dev);
	अगर (!master_dev)
		वापस 0;
	ops = master_dev->rtnl_link_ops;
	अगर (!ops)
		वापस 0;
	अगर (nla_put_string(skb, IFLA_INFO_SLAVE_KIND, ops->kind) < 0)
		वापस -EMSGSIZE;
	अगर (ops->fill_slave_info) अणु
		slave_data = nla_nest_start_noflag(skb, IFLA_INFO_SLAVE_DATA);
		अगर (!slave_data)
			वापस -EMSGSIZE;
		err = ops->fill_slave_info(skb, master_dev, dev);
		अगर (err < 0)
			जाओ err_cancel_slave_data;
		nla_nest_end(skb, slave_data);
	पूर्ण
	वापस 0;

err_cancel_slave_data:
	nla_nest_cancel(skb, slave_data);
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_link_info_fill(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा rtnl_link_ops *ops = dev->rtnl_link_ops;
	काष्ठा nlattr *data;
	पूर्णांक err;

	अगर (!ops)
		वापस 0;
	अगर (nla_put_string(skb, IFLA_INFO_KIND, ops->kind) < 0)
		वापस -EMSGSIZE;
	अगर (ops->fill_xstats) अणु
		err = ops->fill_xstats(skb, dev);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (ops->fill_info) अणु
		data = nla_nest_start_noflag(skb, IFLA_INFO_DATA);
		अगर (data == शून्य)
			वापस -EMSGSIZE;
		err = ops->fill_info(skb, dev);
		अगर (err < 0)
			जाओ err_cancel_data;
		nla_nest_end(skb, data);
	पूर्ण
	वापस 0;

err_cancel_data:
	nla_nest_cancel(skb, data);
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_link_fill(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *linkinfo;
	पूर्णांक err = -EMSGSIZE;

	linkinfo = nla_nest_start_noflag(skb, IFLA_LINKINFO);
	अगर (linkinfo == शून्य)
		जाओ out;

	err = rtnl_link_info_fill(skb, dev);
	अगर (err < 0)
		जाओ err_cancel_link;

	err = rtnl_link_slave_info_fill(skb, dev);
	अगर (err < 0)
		जाओ err_cancel_link;

	nla_nest_end(skb, linkinfo);
	वापस 0;

err_cancel_link:
	nla_nest_cancel(skb, linkinfo);
out:
	वापस err;
पूर्ण

पूर्णांक rtnetlink_send(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid, अचिन्हित पूर्णांक group, पूर्णांक echo)
अणु
	काष्ठा sock *rtnl = net->rtnl;
	पूर्णांक err = 0;

	NETLINK_CB(skb).dst_group = group;
	अगर (echo)
		refcount_inc(&skb->users);
	netlink_broadcast(rtnl, skb, pid, group, GFP_KERNEL);
	अगर (echo)
		err = netlink_unicast(rtnl, skb, pid, MSG_DONTWAIT);
	वापस err;
पूर्ण

पूर्णांक rtnl_unicast(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid)
अणु
	काष्ठा sock *rtnl = net->rtnl;

	वापस nlmsg_unicast(rtnl, skb, pid);
पूर्ण
EXPORT_SYMBOL(rtnl_unicast);

व्योम rtnl_notअगरy(काष्ठा sk_buff *skb, काष्ठा net *net, u32 pid, u32 group,
		 काष्ठा nlmsghdr *nlh, gfp_t flags)
अणु
	काष्ठा sock *rtnl = net->rtnl;
	पूर्णांक report = 0;

	अगर (nlh)
		report = nlmsg_report(nlh);

	nlmsg_notअगरy(rtnl, skb, pid, group, report, flags);
पूर्ण
EXPORT_SYMBOL(rtnl_notअगरy);

व्योम rtnl_set_sk_err(काष्ठा net *net, u32 group, पूर्णांक error)
अणु
	काष्ठा sock *rtnl = net->rtnl;

	netlink_set_err(rtnl, 0, group, error);
पूर्ण
EXPORT_SYMBOL(rtnl_set_sk_err);

पूर्णांक rtnetlink_put_metrics(काष्ठा sk_buff *skb, u32 *metrics)
अणु
	काष्ठा nlattr *mx;
	पूर्णांक i, valid = 0;

	/* nothing is dumped क्रम dst_शेष_metrics, so just skip the loop */
	अगर (metrics == dst_शेष_metrics.metrics)
		वापस 0;

	mx = nla_nest_start_noflag(skb, RTA_METRICS);
	अगर (mx == शून्य)
		वापस -ENOBUFS;

	क्रम (i = 0; i < RTAX_MAX; i++) अणु
		अगर (metrics[i]) अणु
			अगर (i == RTAX_CC_ALGO - 1) अणु
				अक्षर पंचांगp[TCP_CA_NAME_MAX], *name;

				name = tcp_ca_get_name_by_key(metrics[i], पंचांगp);
				अगर (!name)
					जारी;
				अगर (nla_put_string(skb, i + 1, name))
					जाओ nla_put_failure;
			पूर्ण अन्यथा अगर (i == RTAX_FEATURES - 1) अणु
				u32 user_features = metrics[i] & RTAX_FEATURE_MASK;

				अगर (!user_features)
					जारी;
				BUILD_BUG_ON(RTAX_FEATURE_MASK & DST_FEATURE_MASK);
				अगर (nla_put_u32(skb, i + 1, user_features))
					जाओ nla_put_failure;
			पूर्ण अन्यथा अणु
				अगर (nla_put_u32(skb, i + 1, metrics[i]))
					जाओ nla_put_failure;
			पूर्ण
			valid++;
		पूर्ण
	पूर्ण

	अगर (!valid) अणु
		nla_nest_cancel(skb, mx);
		वापस 0;
	पूर्ण

	वापस nla_nest_end(skb, mx);

nla_put_failure:
	nla_nest_cancel(skb, mx);
	वापस -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL(rtnetlink_put_metrics);

पूर्णांक rtnl_put_cacheinfo(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst, u32 id,
		       दीर्घ expires, u32 error)
अणु
	काष्ठा rta_cacheinfo ci = अणु
		.rta_error = error,
		.rta_id =  id,
	पूर्ण;

	अगर (dst) अणु
		ci.rta_lastuse = jअगरfies_delta_to_घड़ी_प्रकार(jअगरfies - dst->lastuse);
		ci.rta_used = dst->__use;
		ci.rta_clntref = atomic_पढ़ो(&dst->__refcnt);
	पूर्ण
	अगर (expires) अणु
		अचिन्हित दीर्घ घड़ी;

		घड़ी = jअगरfies_to_घड़ी_प्रकार(असल(expires));
		घड़ी = min_t(अचिन्हित दीर्घ, घड़ी, पूर्णांक_उच्च);
		ci.rta_expires = (expires > 0) ? घड़ी : -घड़ी;
	पूर्ण
	वापस nla_put(skb, RTA_CACHEINFO, माप(ci), &ci);
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_put_cacheinfo);

अटल व्योम set_operstate(काष्ठा net_device *dev, अचिन्हित अक्षर transition)
अणु
	अचिन्हित अक्षर operstate = dev->operstate;

	चयन (transition) अणु
	हाल IF_OPER_UP:
		अगर ((operstate == IF_OPER_DORMANT ||
		     operstate == IF_OPER_TESTING ||
		     operstate == IF_OPER_UNKNOWN) &&
		    !netअगर_करोrmant(dev) && !netअगर_testing(dev))
			operstate = IF_OPER_UP;
		अवरोध;

	हाल IF_OPER_TESTING:
		अगर (operstate == IF_OPER_UP ||
		    operstate == IF_OPER_UNKNOWN)
			operstate = IF_OPER_TESTING;
		अवरोध;

	हाल IF_OPER_DORMANT:
		अगर (operstate == IF_OPER_UP ||
		    operstate == IF_OPER_UNKNOWN)
			operstate = IF_OPER_DORMANT;
		अवरोध;
	पूर्ण

	अगर (dev->operstate != operstate) अणु
		ग_लिखो_lock_bh(&dev_base_lock);
		dev->operstate = operstate;
		ग_लिखो_unlock_bh(&dev_base_lock);
		netdev_state_change(dev);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक rtnl_dev_get_flags(स्थिर काष्ठा net_device *dev)
अणु
	वापस (dev->flags & ~(IFF_PROMISC | IFF_ALLMULTI)) |
	       (dev->gflags & (IFF_PROMISC | IFF_ALLMULTI));
पूर्ण

अटल अचिन्हित पूर्णांक rtnl_dev_combine_flags(स्थिर काष्ठा net_device *dev,
					   स्थिर काष्ठा अगरinfomsg *अगरm)
अणु
	अचिन्हित पूर्णांक flags = अगरm->अगरi_flags;

	/* bugwards compatibility: अगरi_change == 0 is treated as ~0 */
	अगर (अगरm->अगरi_change)
		flags = (flags & अगरm->अगरi_change) |
			(rtnl_dev_get_flags(dev) & ~अगरm->अगरi_change);

	वापस flags;
पूर्ण

अटल व्योम copy_rtnl_link_stats(काष्ठा rtnl_link_stats *a,
				 स्थिर काष्ठा rtnl_link_stats64 *b)
अणु
	a->rx_packets = b->rx_packets;
	a->tx_packets = b->tx_packets;
	a->rx_bytes = b->rx_bytes;
	a->tx_bytes = b->tx_bytes;
	a->rx_errors = b->rx_errors;
	a->tx_errors = b->tx_errors;
	a->rx_dropped = b->rx_dropped;
	a->tx_dropped = b->tx_dropped;

	a->multicast = b->multicast;
	a->collisions = b->collisions;

	a->rx_length_errors = b->rx_length_errors;
	a->rx_over_errors = b->rx_over_errors;
	a->rx_crc_errors = b->rx_crc_errors;
	a->rx_frame_errors = b->rx_frame_errors;
	a->rx_fअगरo_errors = b->rx_fअगरo_errors;
	a->rx_missed_errors = b->rx_missed_errors;

	a->tx_पातed_errors = b->tx_पातed_errors;
	a->tx_carrier_errors = b->tx_carrier_errors;
	a->tx_fअगरo_errors = b->tx_fअगरo_errors;
	a->tx_heartbeat_errors = b->tx_heartbeat_errors;
	a->tx_winकरोw_errors = b->tx_winकरोw_errors;

	a->rx_compressed = b->rx_compressed;
	a->tx_compressed = b->tx_compressed;

	a->rx_nohandler = b->rx_nohandler;
पूर्ण

/* All VF info */
अटल अंतरभूत पूर्णांक rtnl_vfinfo_size(स्थिर काष्ठा net_device *dev,
				   u32 ext_filter_mask)
अणु
	अगर (dev->dev.parent && (ext_filter_mask & RTEXT_FILTER_VF)) अणु
		पूर्णांक num_vfs = dev_num_vf(dev->dev.parent);
		माप_प्रकार size = nla_total_size(0);
		size += num_vfs *
			(nla_total_size(0) +
			 nla_total_size(माप(काष्ठा अगरla_vf_mac)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_broadcast)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_vlan)) +
			 nla_total_size(0) + /* nest IFLA_VF_VLAN_LIST */
			 nla_total_size(MAX_VLAN_LIST_LEN *
					माप(काष्ठा अगरla_vf_vlan_info)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_spoofchk)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_tx_rate)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_rate)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_link_state)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_rss_query_en)) +
			 nla_total_size(0) + /* nest IFLA_VF_STATS */
			 /* IFLA_VF_STATS_RX_PACKETS */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_TX_PACKETS */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_RX_BYTES */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_TX_BYTES */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_BROADCAST */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_MULTICAST */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_RX_DROPPED */
			 nla_total_size_64bit(माप(__u64)) +
			 /* IFLA_VF_STATS_TX_DROPPED */
			 nla_total_size_64bit(माप(__u64)) +
			 nla_total_size(माप(काष्ठा अगरla_vf_trust)));
		वापस size;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल माप_प्रकार rtnl_port_size(स्थिर काष्ठा net_device *dev,
			     u32 ext_filter_mask)
अणु
	माप_प्रकार port_size = nla_total_size(4)		/* PORT_VF */
		+ nla_total_size(PORT_PROखाता_MAX)	/* PORT_PROखाता */
		+ nla_total_size(PORT_UUID_MAX)		/* PORT_INSTANCE_UUID */
		+ nla_total_size(PORT_UUID_MAX)		/* PORT_HOST_UUID */
		+ nla_total_size(1)			/* PROT_VDP_REQUEST */
		+ nla_total_size(2);			/* PORT_VDP_RESPONSE */
	माप_प्रकार vf_ports_size = nla_total_size(माप(काष्ठा nlattr));
	माप_प्रकार vf_port_size = nla_total_size(माप(काष्ठा nlattr))
		+ port_size;
	माप_प्रकार port_self_size = nla_total_size(माप(काष्ठा nlattr))
		+ port_size;

	अगर (!dev->netdev_ops->nकरो_get_vf_port || !dev->dev.parent ||
	    !(ext_filter_mask & RTEXT_FILTER_VF))
		वापस 0;
	अगर (dev_num_vf(dev->dev.parent))
		वापस port_self_size + vf_ports_size +
			vf_port_size * dev_num_vf(dev->dev.parent);
	अन्यथा
		वापस port_self_size;
पूर्ण

अटल माप_प्रकार rtnl_xdp_size(व्योम)
अणु
	माप_प्रकार xdp_size = nla_total_size(0) +	/* nest IFLA_XDP */
			  nla_total_size(1) +	/* XDP_ATTACHED */
			  nla_total_size(4) +	/* XDP_PROG_ID (or 1st mode) */
			  nla_total_size(4);	/* XDP_<mode>_PROG_ID */

	वापस xdp_size;
पूर्ण

अटल माप_प्रकार rtnl_prop_list_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा netdev_name_node *name_node;
	माप_प्रकार size;

	अगर (list_empty(&dev->name_node->list))
		वापस 0;
	size = nla_total_size(0);
	list_क्रम_each_entry(name_node, &dev->name_node->list, list)
		size += nla_total_size(ALTIFNAMSIZ);
	वापस size;
पूर्ण

अटल माप_प्रकार rtnl_proto_करोwn_size(स्थिर काष्ठा net_device *dev)
अणु
	माप_प्रकार size = nla_total_size(1);

	अगर (dev->proto_करोwn_reason)
		size += nla_total_size(0) + nla_total_size(4);

	वापस size;
पूर्ण

अटल noअंतरभूत माप_प्रकार अगर_nlmsg_size(स्थिर काष्ठा net_device *dev,
				     u32 ext_filter_mask)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरinfomsg))
	       + nla_total_size(IFNAMSIZ) /* IFLA_IFNAME */
	       + nla_total_size(IFALIASZ) /* IFLA_IFALIAS */
	       + nla_total_size(IFNAMSIZ) /* IFLA_QDISC */
	       + nla_total_size_64bit(माप(काष्ठा rtnl_link_अगरmap))
	       + nla_total_size(माप(काष्ठा rtnl_link_stats))
	       + nla_total_size_64bit(माप(काष्ठा rtnl_link_stats64))
	       + nla_total_size(MAX_ADDR_LEN) /* IFLA_ADDRESS */
	       + nla_total_size(MAX_ADDR_LEN) /* IFLA_BROADCAST */
	       + nla_total_size(4) /* IFLA_TXQLEN */
	       + nla_total_size(4) /* IFLA_WEIGHT */
	       + nla_total_size(4) /* IFLA_MTU */
	       + nla_total_size(4) /* IFLA_LINK */
	       + nla_total_size(4) /* IFLA_MASTER */
	       + nla_total_size(1) /* IFLA_CARRIER */
	       + nla_total_size(4) /* IFLA_PROMISCUITY */
	       + nla_total_size(4) /* IFLA_NUM_TX_QUEUES */
	       + nla_total_size(4) /* IFLA_NUM_RX_QUEUES */
	       + nla_total_size(4) /* IFLA_GSO_MAX_SEGS */
	       + nla_total_size(4) /* IFLA_GSO_MAX_SIZE */
	       + nla_total_size(1) /* IFLA_OPERSTATE */
	       + nla_total_size(1) /* IFLA_LINKMODE */
	       + nla_total_size(4) /* IFLA_CARRIER_CHANGES */
	       + nla_total_size(4) /* IFLA_LINK_NETNSID */
	       + nla_total_size(4) /* IFLA_GROUP */
	       + nla_total_size(ext_filter_mask
			        & RTEXT_FILTER_VF ? 4 : 0) /* IFLA_NUM_VF */
	       + rtnl_vfinfo_size(dev, ext_filter_mask) /* IFLA_VFINFO_LIST */
	       + rtnl_port_size(dev, ext_filter_mask) /* IFLA_VF_PORTS + IFLA_PORT_SELF */
	       + rtnl_link_get_size(dev) /* IFLA_LINKINFO */
	       + rtnl_link_get_af_size(dev, ext_filter_mask) /* IFLA_AF_SPEC */
	       + nla_total_size(MAX_PHYS_ITEM_ID_LEN) /* IFLA_PHYS_PORT_ID */
	       + nla_total_size(MAX_PHYS_ITEM_ID_LEN) /* IFLA_PHYS_SWITCH_ID */
	       + nla_total_size(IFNAMSIZ) /* IFLA_PHYS_PORT_NAME */
	       + rtnl_xdp_size() /* IFLA_XDP */
	       + nla_total_size(4)  /* IFLA_EVENT */
	       + nla_total_size(4)  /* IFLA_NEW_NETNSID */
	       + nla_total_size(4)  /* IFLA_NEW_IFINDEX */
	       + rtnl_proto_करोwn_size(dev)  /* proto करोwn */
	       + nla_total_size(4)  /* IFLA_TARGET_NETNSID */
	       + nla_total_size(4)  /* IFLA_CARRIER_UP_COUNT */
	       + nla_total_size(4)  /* IFLA_CARRIER_DOWN_COUNT */
	       + nla_total_size(4)  /* IFLA_MIN_MTU */
	       + nla_total_size(4)  /* IFLA_MAX_MTU */
	       + rtnl_prop_list_size(dev)
	       + nla_total_size(MAX_ADDR_LEN) /* IFLA_PERM_ADDRESS */
	       + 0;
पूर्ण

अटल पूर्णांक rtnl_vf_ports_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *vf_ports;
	काष्ठा nlattr *vf_port;
	पूर्णांक vf;
	पूर्णांक err;

	vf_ports = nla_nest_start_noflag(skb, IFLA_VF_PORTS);
	अगर (!vf_ports)
		वापस -EMSGSIZE;

	क्रम (vf = 0; vf < dev_num_vf(dev->dev.parent); vf++) अणु
		vf_port = nla_nest_start_noflag(skb, IFLA_VF_PORT);
		अगर (!vf_port)
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_PORT_VF, vf))
			जाओ nla_put_failure;
		err = dev->netdev_ops->nकरो_get_vf_port(dev, vf, skb);
		अगर (err == -EMSGSIZE)
			जाओ nla_put_failure;
		अगर (err) अणु
			nla_nest_cancel(skb, vf_port);
			जारी;
		पूर्ण
		nla_nest_end(skb, vf_port);
	पूर्ण

	nla_nest_end(skb, vf_ports);

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, vf_ports);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक rtnl_port_self_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *port_self;
	पूर्णांक err;

	port_self = nla_nest_start_noflag(skb, IFLA_PORT_SELF);
	अगर (!port_self)
		वापस -EMSGSIZE;

	err = dev->netdev_ops->nकरो_get_vf_port(dev, PORT_SELF_VF, skb);
	अगर (err) अणु
		nla_nest_cancel(skb, port_self);
		वापस (err == -EMSGSIZE) ? err : 0;
	पूर्ण

	nla_nest_end(skb, port_self);

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_port_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  u32 ext_filter_mask)
अणु
	पूर्णांक err;

	अगर (!dev->netdev_ops->nकरो_get_vf_port || !dev->dev.parent ||
	    !(ext_filter_mask & RTEXT_FILTER_VF))
		वापस 0;

	err = rtnl_port_self_fill(skb, dev);
	अगर (err)
		वापस err;

	अगर (dev_num_vf(dev->dev.parent)) अणु
		err = rtnl_vf_ports_fill(skb, dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_phys_port_id_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा netdev_phys_item_id ppid;

	err = dev_get_phys_port_id(dev, &ppid);
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण

	अगर (nla_put(skb, IFLA_PHYS_PORT_ID, ppid.id_len, ppid.id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_phys_port_name_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अक्षर name[IFNAMSIZ];
	पूर्णांक err;

	err = dev_get_phys_port_name(dev, name, माप(name));
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण

	अगर (nla_put_string(skb, IFLA_PHYS_PORT_NAME, name))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_phys_चयन_id_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netdev_phys_item_id ppid = अणु पूर्ण;
	पूर्णांक err;

	err = dev_get_port_parent_id(dev, &ppid, false);
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण

	अगर (nla_put(skb, IFLA_PHYS_SWITCH_ID, ppid.id_len, ppid.id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक rtnl_fill_stats(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev)
अणु
	काष्ठा rtnl_link_stats64 *sp;
	काष्ठा nlattr *attr;

	attr = nla_reserve_64bit(skb, IFLA_STATS64,
				 माप(काष्ठा rtnl_link_stats64), IFLA_PAD);
	अगर (!attr)
		वापस -EMSGSIZE;

	sp = nla_data(attr);
	dev_get_stats(dev, sp);

	attr = nla_reserve(skb, IFLA_STATS,
			   माप(काष्ठा rtnl_link_stats));
	अगर (!attr)
		वापस -EMSGSIZE;

	copy_rtnl_link_stats(nla_data(attr), sp);

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक rtnl_fill_vfinfo(काष्ठा sk_buff *skb,
					       काष्ठा net_device *dev,
					       पूर्णांक vfs_num,
					       काष्ठा nlattr *vfinfo)
अणु
	काष्ठा अगरla_vf_rss_query_en vf_rss_query_en;
	काष्ठा nlattr *vf, *vख_स्थितिs, *vfvlanlist;
	काष्ठा अगरla_vf_link_state vf_linkstate;
	काष्ठा अगरla_vf_vlan_info vf_vlan_info;
	काष्ठा अगरla_vf_spoofchk vf_spoofchk;
	काष्ठा अगरla_vf_tx_rate vf_tx_rate;
	काष्ठा अगरla_vf_stats vf_stats;
	काष्ठा अगरla_vf_trust vf_trust;
	काष्ठा अगरla_vf_vlan vf_vlan;
	काष्ठा अगरla_vf_rate vf_rate;
	काष्ठा अगरla_vf_mac vf_mac;
	काष्ठा अगरla_vf_broadcast vf_broadcast;
	काष्ठा अगरla_vf_info ivi;
	काष्ठा अगरla_vf_guid node_guid;
	काष्ठा अगरla_vf_guid port_guid;

	स_रखो(&ivi, 0, माप(ivi));

	/* Not all SR-IOV capable drivers support the
	 * spoofcheck and "RSS query enable" query.  Preset to
	 * -1 so the user space tool can detect that the driver
	 * didn't report anything.
	 */
	ivi.spoofchk = -1;
	ivi.rss_query_en = -1;
	ivi.trusted = -1;
	/* The शेष value क्रम VF link state is "auto"
	 * IFLA_VF_LINK_STATE_AUTO which equals zero
	 */
	ivi.linkstate = 0;
	/* VLAN Protocol by शेष is 802.1Q */
	ivi.vlan_proto = htons(ETH_P_8021Q);
	अगर (dev->netdev_ops->nकरो_get_vf_config(dev, vfs_num, &ivi))
		वापस 0;

	स_रखो(&vf_vlan_info, 0, माप(vf_vlan_info));
	स_रखो(&node_guid, 0, माप(node_guid));
	स_रखो(&port_guid, 0, माप(port_guid));

	vf_mac.vf =
		vf_vlan.vf =
		vf_vlan_info.vf =
		vf_rate.vf =
		vf_tx_rate.vf =
		vf_spoofchk.vf =
		vf_linkstate.vf =
		vf_rss_query_en.vf =
		vf_trust.vf =
		node_guid.vf =
		port_guid.vf = ivi.vf;

	स_नकल(vf_mac.mac, ivi.mac, माप(ivi.mac));
	स_नकल(vf_broadcast.broadcast, dev->broadcast, dev->addr_len);
	vf_vlan.vlan = ivi.vlan;
	vf_vlan.qos = ivi.qos;
	vf_vlan_info.vlan = ivi.vlan;
	vf_vlan_info.qos = ivi.qos;
	vf_vlan_info.vlan_proto = ivi.vlan_proto;
	vf_tx_rate.rate = ivi.max_tx_rate;
	vf_rate.min_tx_rate = ivi.min_tx_rate;
	vf_rate.max_tx_rate = ivi.max_tx_rate;
	vf_spoofchk.setting = ivi.spoofchk;
	vf_linkstate.link_state = ivi.linkstate;
	vf_rss_query_en.setting = ivi.rss_query_en;
	vf_trust.setting = ivi.trusted;
	vf = nla_nest_start_noflag(skb, IFLA_VF_INFO);
	अगर (!vf)
		जाओ nla_put_vfinfo_failure;
	अगर (nla_put(skb, IFLA_VF_MAC, माप(vf_mac), &vf_mac) ||
	    nla_put(skb, IFLA_VF_BROADCAST, माप(vf_broadcast), &vf_broadcast) ||
	    nla_put(skb, IFLA_VF_VLAN, माप(vf_vlan), &vf_vlan) ||
	    nla_put(skb, IFLA_VF_RATE, माप(vf_rate),
		    &vf_rate) ||
	    nla_put(skb, IFLA_VF_TX_RATE, माप(vf_tx_rate),
		    &vf_tx_rate) ||
	    nla_put(skb, IFLA_VF_SPOOFCHK, माप(vf_spoofchk),
		    &vf_spoofchk) ||
	    nla_put(skb, IFLA_VF_LINK_STATE, माप(vf_linkstate),
		    &vf_linkstate) ||
	    nla_put(skb, IFLA_VF_RSS_QUERY_EN,
		    माप(vf_rss_query_en),
		    &vf_rss_query_en) ||
	    nla_put(skb, IFLA_VF_TRUST,
		    माप(vf_trust), &vf_trust))
		जाओ nla_put_vf_failure;

	अगर (dev->netdev_ops->nकरो_get_vf_guid &&
	    !dev->netdev_ops->nकरो_get_vf_guid(dev, vfs_num, &node_guid,
					      &port_guid)) अणु
		अगर (nla_put(skb, IFLA_VF_IB_NODE_GUID, माप(node_guid),
			    &node_guid) ||
		    nla_put(skb, IFLA_VF_IB_PORT_GUID, माप(port_guid),
			    &port_guid))
			जाओ nla_put_vf_failure;
	पूर्ण
	vfvlanlist = nla_nest_start_noflag(skb, IFLA_VF_VLAN_LIST);
	अगर (!vfvlanlist)
		जाओ nla_put_vf_failure;
	अगर (nla_put(skb, IFLA_VF_VLAN_INFO, माप(vf_vlan_info),
		    &vf_vlan_info)) अणु
		nla_nest_cancel(skb, vfvlanlist);
		जाओ nla_put_vf_failure;
	पूर्ण
	nla_nest_end(skb, vfvlanlist);
	स_रखो(&vf_stats, 0, माप(vf_stats));
	अगर (dev->netdev_ops->nकरो_get_vf_stats)
		dev->netdev_ops->nकरो_get_vf_stats(dev, vfs_num,
						&vf_stats);
	vख_स्थितिs = nla_nest_start_noflag(skb, IFLA_VF_STATS);
	अगर (!vख_स्थितिs)
		जाओ nla_put_vf_failure;
	अगर (nla_put_u64_64bit(skb, IFLA_VF_STATS_RX_PACKETS,
			      vf_stats.rx_packets, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_TX_PACKETS,
			      vf_stats.tx_packets, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_RX_BYTES,
			      vf_stats.rx_bytes, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_TX_BYTES,
			      vf_stats.tx_bytes, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_BROADCAST,
			      vf_stats.broadcast, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_MULTICAST,
			      vf_stats.multicast, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_RX_DROPPED,
			      vf_stats.rx_dropped, IFLA_VF_STATS_PAD) ||
	    nla_put_u64_64bit(skb, IFLA_VF_STATS_TX_DROPPED,
			      vf_stats.tx_dropped, IFLA_VF_STATS_PAD)) अणु
		nla_nest_cancel(skb, vख_स्थितिs);
		जाओ nla_put_vf_failure;
	पूर्ण
	nla_nest_end(skb, vख_स्थितिs);
	nla_nest_end(skb, vf);
	वापस 0;

nla_put_vf_failure:
	nla_nest_cancel(skb, vf);
nla_put_vfinfo_failure:
	nla_nest_cancel(skb, vfinfo);
	वापस -EMSGSIZE;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक rtnl_fill_vf(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev,
					   u32 ext_filter_mask)
अणु
	काष्ठा nlattr *vfinfo;
	पूर्णांक i, num_vfs;

	अगर (!dev->dev.parent || ((ext_filter_mask & RTEXT_FILTER_VF) == 0))
		वापस 0;

	num_vfs = dev_num_vf(dev->dev.parent);
	अगर (nla_put_u32(skb, IFLA_NUM_VF, num_vfs))
		वापस -EMSGSIZE;

	अगर (!dev->netdev_ops->nकरो_get_vf_config)
		वापस 0;

	vfinfo = nla_nest_start_noflag(skb, IFLA_VFINFO_LIST);
	अगर (!vfinfo)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < num_vfs; i++) अणु
		अगर (rtnl_fill_vfinfo(skb, dev, i, vfinfo))
			वापस -EMSGSIZE;
	पूर्ण

	nla_nest_end(skb, vfinfo);
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_fill_link_अगरmap(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा rtnl_link_अगरmap map;

	स_रखो(&map, 0, माप(map));
	map.mem_start   = dev->mem_start;
	map.mem_end     = dev->mem_end;
	map.base_addr   = dev->base_addr;
	map.irq         = dev->irq;
	map.dma         = dev->dma;
	map.port        = dev->अगर_port;

	अगर (nla_put_64bit(skb, IFLA_MAP, माप(map), &map, IFLA_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल u32 rtnl_xdp_prog_skb(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा bpf_prog *generic_xdp_prog;

	ASSERT_RTNL();

	generic_xdp_prog = rtnl_dereference(dev->xdp_prog);
	अगर (!generic_xdp_prog)
		वापस 0;
	वापस generic_xdp_prog->aux->id;
पूर्ण

अटल u32 rtnl_xdp_prog_drv(काष्ठा net_device *dev)
अणु
	वापस dev_xdp_prog_id(dev, XDP_MODE_DRV);
पूर्ण

अटल u32 rtnl_xdp_prog_hw(काष्ठा net_device *dev)
अणु
	वापस dev_xdp_prog_id(dev, XDP_MODE_HW);
पूर्ण

अटल पूर्णांक rtnl_xdp_report_one(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       u32 *prog_id, u8 *mode, u8 tgt_mode, u32 attr,
			       u32 (*get_prog_id)(काष्ठा net_device *dev))
अणु
	u32 curr_id;
	पूर्णांक err;

	curr_id = get_prog_id(dev);
	अगर (!curr_id)
		वापस 0;

	*prog_id = curr_id;
	err = nla_put_u32(skb, attr, curr_id);
	अगर (err)
		वापस err;

	अगर (*mode != XDP_ATTACHED_NONE)
		*mode = XDP_ATTACHED_MULTI;
	अन्यथा
		*mode = tgt_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_xdp_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *xdp;
	u32 prog_id;
	पूर्णांक err;
	u8 mode;

	xdp = nla_nest_start_noflag(skb, IFLA_XDP);
	अगर (!xdp)
		वापस -EMSGSIZE;

	prog_id = 0;
	mode = XDP_ATTACHED_NONE;
	err = rtnl_xdp_report_one(skb, dev, &prog_id, &mode, XDP_ATTACHED_SKB,
				  IFLA_XDP_SKB_PROG_ID, rtnl_xdp_prog_skb);
	अगर (err)
		जाओ err_cancel;
	err = rtnl_xdp_report_one(skb, dev, &prog_id, &mode, XDP_ATTACHED_DRV,
				  IFLA_XDP_DRV_PROG_ID, rtnl_xdp_prog_drv);
	अगर (err)
		जाओ err_cancel;
	err = rtnl_xdp_report_one(skb, dev, &prog_id, &mode, XDP_ATTACHED_HW,
				  IFLA_XDP_HW_PROG_ID, rtnl_xdp_prog_hw);
	अगर (err)
		जाओ err_cancel;

	err = nla_put_u8(skb, IFLA_XDP_ATTACHED, mode);
	अगर (err)
		जाओ err_cancel;

	अगर (prog_id && mode != XDP_ATTACHED_MULTI) अणु
		err = nla_put_u32(skb, IFLA_XDP_PROG_ID, prog_id);
		अगर (err)
			जाओ err_cancel;
	पूर्ण

	nla_nest_end(skb, xdp);
	वापस 0;

err_cancel:
	nla_nest_cancel(skb, xdp);
	वापस err;
पूर्ण

अटल u32 rtnl_get_event(अचिन्हित दीर्घ event)
अणु
	u32 rtnl_event_type = IFLA_EVENT_NONE;

	चयन (event) अणु
	हाल NETDEV_REBOOT:
		rtnl_event_type = IFLA_EVENT_REBOOT;
		अवरोध;
	हाल NETDEV_FEAT_CHANGE:
		rtnl_event_type = IFLA_EVENT_FEATURES;
		अवरोध;
	हाल NETDEV_BONDING_FAILOVER:
		rtnl_event_type = IFLA_EVENT_BONDING_FAILOVER;
		अवरोध;
	हाल NETDEV_NOTIFY_PEERS:
		rtnl_event_type = IFLA_EVENT_NOTIFY_PEERS;
		अवरोध;
	हाल NETDEV_RESEND_IGMP:
		rtnl_event_type = IFLA_EVENT_IGMP_RESEND;
		अवरोध;
	हाल NETDEV_CHANGEINFODATA:
		rtnl_event_type = IFLA_EVENT_BONDING_OPTIONS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rtnl_event_type;
पूर्ण

अटल पूर्णांक put_master_अगरindex(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा net_device *upper_dev;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();

	upper_dev = netdev_master_upper_dev_get_rcu(dev);
	अगर (upper_dev)
		ret = nla_put_u32(skb, IFLA_MASTER, upper_dev->अगरindex);

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक nla_put_अगरlink(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			  bool क्रमce)
अणु
	पूर्णांक अगरindex = dev_get_अगरlink(dev);

	अगर (क्रमce || dev->अगरindex != अगरindex)
		वापस nla_put_u32(skb, IFLA_LINK, अगरindex);

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक nla_put_अगरalias(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev)
अणु
	अक्षर buf[IFALIASZ];
	पूर्णांक ret;

	ret = dev_get_alias(dev, buf, माप(buf));
	वापस ret > 0 ? nla_put_string(skb, IFLA_IFALIAS, buf) : 0;
पूर्ण

अटल पूर्णांक rtnl_fill_link_netnsid(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा net_device *dev,
				  काष्ठा net *src_net, gfp_t gfp)
अणु
	bool put_अगरlink = false;

	अगर (dev->rtnl_link_ops && dev->rtnl_link_ops->get_link_net) अणु
		काष्ठा net *link_net = dev->rtnl_link_ops->get_link_net(dev);

		अगर (!net_eq(dev_net(dev), link_net)) अणु
			पूर्णांक id = peernet2id_alloc(src_net, link_net, gfp);

			अगर (nla_put_s32(skb, IFLA_LINK_NETNSID, id))
				वापस -EMSGSIZE;

			put_अगरlink = true;
		पूर्ण
	पूर्ण

	वापस nla_put_अगरlink(skb, dev, put_अगरlink);
पूर्ण

अटल पूर्णांक rtnl_fill_link_af(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा net_device *dev,
			     u32 ext_filter_mask)
अणु
	स्थिर काष्ठा rtnl_af_ops *af_ops;
	काष्ठा nlattr *af_spec;

	af_spec = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
	अगर (!af_spec)
		वापस -EMSGSIZE;

	list_क्रम_each_entry_rcu(af_ops, &rtnl_af_ops, list) अणु
		काष्ठा nlattr *af;
		पूर्णांक err;

		अगर (!af_ops->fill_link_af)
			जारी;

		af = nla_nest_start_noflag(skb, af_ops->family);
		अगर (!af)
			वापस -EMSGSIZE;

		err = af_ops->fill_link_af(skb, dev, ext_filter_mask);
		/*
		 * Caller may वापस ENODATA to indicate that there
		 * was no data to be dumped. This is not an error, it
		 * means we should trim the attribute header and
		 * जारी.
		 */
		अगर (err == -ENODATA)
			nla_nest_cancel(skb, af);
		अन्यथा अगर (err < 0)
			वापस -EMSGSIZE;

		nla_nest_end(skb, af);
	पूर्ण

	nla_nest_end(skb, af_spec);
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_fill_alt_अगरnames(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा netdev_name_node *name_node;
	पूर्णांक count = 0;

	list_क्रम_each_entry(name_node, &dev->name_node->list, list) अणु
		अगर (nla_put_string(skb, IFLA_ALT_IFNAME, name_node->name))
			वापस -EMSGSIZE;
		count++;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक rtnl_fill_prop_list(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *prop_list;
	पूर्णांक ret;

	prop_list = nla_nest_start(skb, IFLA_PROP_LIST);
	अगर (!prop_list)
		वापस -EMSGSIZE;

	ret = rtnl_fill_alt_अगरnames(skb, dev);
	अगर (ret <= 0)
		जाओ nest_cancel;

	nla_nest_end(skb, prop_list);
	वापस 0;

nest_cancel:
	nla_nest_cancel(skb, prop_list);
	वापस ret;
पूर्ण

अटल पूर्णांक rtnl_fill_proto_करोwn(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा nlattr *pr;
	u32 preason;

	अगर (nla_put_u8(skb, IFLA_PROTO_DOWN, dev->proto_करोwn))
		जाओ nla_put_failure;

	preason = dev->proto_करोwn_reason;
	अगर (!preason)
		वापस 0;

	pr = nla_nest_start(skb, IFLA_PROTO_DOWN_REASON);
	अगर (!pr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, IFLA_PROTO_DOWN_REASON_VALUE, preason)) अणु
		nla_nest_cancel(skb, pr);
		जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(skb, pr);
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक rtnl_fill_अगरinfo(काष्ठा sk_buff *skb,
			    काष्ठा net_device *dev, काष्ठा net *src_net,
			    पूर्णांक type, u32 pid, u32 seq, u32 change,
			    अचिन्हित पूर्णांक flags, u32 ext_filter_mask,
			    u32 event, पूर्णांक *new_nsid, पूर्णांक new_अगरindex,
			    पूर्णांक tgt_netnsid, gfp_t gfp)
अणु
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा nlmsghdr *nlh;

	ASSERT_RTNL();
	nlh = nlmsg_put(skb, pid, seq, type, माप(*अगरm), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरi_family = AF_UNSPEC;
	अगरm->__अगरi_pad = 0;
	अगरm->अगरi_type = dev->type;
	अगरm->अगरi_index = dev->अगरindex;
	अगरm->अगरi_flags = dev_get_flags(dev);
	अगरm->अगरi_change = change;

	अगर (tgt_netnsid >= 0 && nla_put_s32(skb, IFLA_TARGET_NETNSID, tgt_netnsid))
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    nla_put_u32(skb, IFLA_TXQLEN, dev->tx_queue_len) ||
	    nla_put_u8(skb, IFLA_OPERSTATE,
		       netअगर_running(dev) ? dev->operstate : IF_OPER_DOWN) ||
	    nla_put_u8(skb, IFLA_LINKMODE, dev->link_mode) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    nla_put_u32(skb, IFLA_MIN_MTU, dev->min_mtu) ||
	    nla_put_u32(skb, IFLA_MAX_MTU, dev->max_mtu) ||
	    nla_put_u32(skb, IFLA_GROUP, dev->group) ||
	    nla_put_u32(skb, IFLA_PROMISCUITY, dev->promiscuity) ||
	    nla_put_u32(skb, IFLA_NUM_TX_QUEUES, dev->num_tx_queues) ||
	    nla_put_u32(skb, IFLA_GSO_MAX_SEGS, dev->gso_max_segs) ||
	    nla_put_u32(skb, IFLA_GSO_MAX_SIZE, dev->gso_max_size) ||
#अगर_घोषित CONFIG_RPS
	    nla_put_u32(skb, IFLA_NUM_RX_QUEUES, dev->num_rx_queues) ||
#पूर्ण_अगर
	    put_master_अगरindex(skb, dev) ||
	    nla_put_u8(skb, IFLA_CARRIER, netअगर_carrier_ok(dev)) ||
	    (dev->qdisc &&
	     nla_put_string(skb, IFLA_QDISC, dev->qdisc->ops->id)) ||
	    nla_put_अगरalias(skb, dev) ||
	    nla_put_u32(skb, IFLA_CARRIER_CHANGES,
			atomic_पढ़ो(&dev->carrier_up_count) +
			atomic_पढ़ो(&dev->carrier_करोwn_count)) ||
	    nla_put_u32(skb, IFLA_CARRIER_UP_COUNT,
			atomic_पढ़ो(&dev->carrier_up_count)) ||
	    nla_put_u32(skb, IFLA_CARRIER_DOWN_COUNT,
			atomic_पढ़ो(&dev->carrier_करोwn_count)))
		जाओ nla_put_failure;

	अगर (rtnl_fill_proto_करोwn(skb, dev))
		जाओ nla_put_failure;

	अगर (event != IFLA_EVENT_NONE) अणु
		अगर (nla_put_u32(skb, IFLA_EVENT, event))
			जाओ nla_put_failure;
	पूर्ण

	अगर (rtnl_fill_link_अगरmap(skb, dev))
		जाओ nla_put_failure;

	अगर (dev->addr_len) अणु
		अगर (nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr) ||
		    nla_put(skb, IFLA_BROADCAST, dev->addr_len, dev->broadcast))
			जाओ nla_put_failure;
	पूर्ण

	अगर (rtnl_phys_port_id_fill(skb, dev))
		जाओ nla_put_failure;

	अगर (rtnl_phys_port_name_fill(skb, dev))
		जाओ nla_put_failure;

	अगर (rtnl_phys_चयन_id_fill(skb, dev))
		जाओ nla_put_failure;

	अगर (rtnl_fill_stats(skb, dev))
		जाओ nla_put_failure;

	अगर (rtnl_fill_vf(skb, dev, ext_filter_mask))
		जाओ nla_put_failure;

	अगर (rtnl_port_fill(skb, dev, ext_filter_mask))
		जाओ nla_put_failure;

	अगर (rtnl_xdp_fill(skb, dev))
		जाओ nla_put_failure;

	अगर (dev->rtnl_link_ops || rtnl_have_link_slave_info(dev)) अणु
		अगर (rtnl_link_fill(skb, dev) < 0)
			जाओ nla_put_failure;
	पूर्ण

	अगर (rtnl_fill_link_netnsid(skb, dev, src_net, gfp))
		जाओ nla_put_failure;

	अगर (new_nsid &&
	    nla_put_s32(skb, IFLA_NEW_NETNSID, *new_nsid) < 0)
		जाओ nla_put_failure;
	अगर (new_अगरindex &&
	    nla_put_s32(skb, IFLA_NEW_IFINDEX, new_अगरindex) < 0)
		जाओ nla_put_failure;

	अगर (स_प्रथम_inv(dev->perm_addr, '\0', dev->addr_len) &&
	    nla_put(skb, IFLA_PERM_ADDRESS, dev->addr_len, dev->perm_addr))
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();
	अगर (rtnl_fill_link_af(skb, dev, ext_filter_mask))
		जाओ nla_put_failure_rcu;
	rcu_पढ़ो_unlock();

	अगर (rtnl_fill_prop_list(skb, dev))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure_rcu:
	rcu_पढ़ो_unlock();
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy अगरla_policy[IFLA_MAX+1] = अणु
	[IFLA_IFNAME]		= अणु .type = NLA_STRING, .len = IFNAMSIZ-1 पूर्ण,
	[IFLA_ADDRESS]		= अणु .type = NLA_BINARY, .len = MAX_ADDR_LEN पूर्ण,
	[IFLA_BROADCAST]	= अणु .type = NLA_BINARY, .len = MAX_ADDR_LEN पूर्ण,
	[IFLA_MAP]		= अणु .len = माप(काष्ठा rtnl_link_अगरmap) पूर्ण,
	[IFLA_MTU]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_MASTER]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_CARRIER]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_TXQLEN]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_WEIGHT]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_OPERSTATE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_LINKMODE]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_LINKINFO]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_NET_NS_PID]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_NET_NS_FD]	= अणु .type = NLA_U32 पूर्ण,
	/* IFLA_IFALIAS is a string, but policy is set to NLA_BINARY to
	 * allow 0-length string (needed to हटाओ an alias).
	 */
	[IFLA_IFALIAS]	        = अणु .type = NLA_BINARY, .len = IFALIASZ - 1 पूर्ण,
	[IFLA_VFINFO_LIST]	= अणु. type = NLA_NESTED पूर्ण,
	[IFLA_VF_PORTS]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_PORT_SELF]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_AF_SPEC]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_EXT_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_PROMISCUITY]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_NUM_TX_QUEUES]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_NUM_RX_QUEUES]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GSO_MAX_SEGS]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GSO_MAX_SIZE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_PHYS_PORT_ID]	= अणु .type = NLA_BINARY, .len = MAX_PHYS_ITEM_ID_LEN पूर्ण,
	[IFLA_CARRIER_CHANGES]	= अणु .type = NLA_U32 पूर्ण,  /* ignored */
	[IFLA_PHYS_SWITCH_ID]	= अणु .type = NLA_BINARY, .len = MAX_PHYS_ITEM_ID_LEN पूर्ण,
	[IFLA_LINK_NETNSID]	= अणु .type = NLA_S32 पूर्ण,
	[IFLA_PROTO_DOWN]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_XDP]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_EVENT]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_GROUP]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_TARGET_NETNSID]	= अणु .type = NLA_S32 पूर्ण,
	[IFLA_CARRIER_UP_COUNT]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_CARRIER_DOWN_COUNT] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MIN_MTU]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_MAX_MTU]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_PROP_LIST]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_ALT_IFNAME]	= अणु .type = NLA_STRING,
				    .len = ALTIFNAMSIZ - 1 पूर्ण,
	[IFLA_PERM_ADDRESS]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_PROTO_DOWN_REASON] = अणु .type = NLA_NESTED पूर्ण,
	[IFLA_NEW_IFINDEX]	= NLA_POLICY_MIN(NLA_S32, 1),
पूर्ण;

अटल स्थिर काष्ठा nla_policy अगरla_info_policy[IFLA_INFO_MAX+1] = अणु
	[IFLA_INFO_KIND]	= अणु .type = NLA_STRING पूर्ण,
	[IFLA_INFO_DATA]	= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_INFO_SLAVE_KIND]	= अणु .type = NLA_STRING पूर्ण,
	[IFLA_INFO_SLAVE_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy अगरla_vf_policy[IFLA_VF_MAX+1] = अणु
	[IFLA_VF_MAC]		= अणु .len = माप(काष्ठा अगरla_vf_mac) पूर्ण,
	[IFLA_VF_BROADCAST]	= अणु .type = NLA_REJECT पूर्ण,
	[IFLA_VF_VLAN]		= अणु .len = माप(काष्ठा अगरla_vf_vlan) पूर्ण,
	[IFLA_VF_VLAN_LIST]     = अणु .type = NLA_NESTED पूर्ण,
	[IFLA_VF_TX_RATE]	= अणु .len = माप(काष्ठा अगरla_vf_tx_rate) पूर्ण,
	[IFLA_VF_SPOOFCHK]	= अणु .len = माप(काष्ठा अगरla_vf_spoofchk) पूर्ण,
	[IFLA_VF_RATE]		= अणु .len = माप(काष्ठा अगरla_vf_rate) पूर्ण,
	[IFLA_VF_LINK_STATE]	= अणु .len = माप(काष्ठा अगरla_vf_link_state) पूर्ण,
	[IFLA_VF_RSS_QUERY_EN]	= अणु .len = माप(काष्ठा अगरla_vf_rss_query_en) पूर्ण,
	[IFLA_VF_STATS]		= अणु .type = NLA_NESTED पूर्ण,
	[IFLA_VF_TRUST]		= अणु .len = माप(काष्ठा अगरla_vf_trust) पूर्ण,
	[IFLA_VF_IB_NODE_GUID]	= अणु .len = माप(काष्ठा अगरla_vf_guid) पूर्ण,
	[IFLA_VF_IB_PORT_GUID]	= अणु .len = माप(काष्ठा अगरla_vf_guid) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy अगरla_port_policy[IFLA_PORT_MAX+1] = अणु
	[IFLA_PORT_VF]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_PORT_PROखाता]	= अणु .type = NLA_STRING,
				    .len = PORT_PROखाता_MAX पूर्ण,
	[IFLA_PORT_INSTANCE_UUID] = अणु .type = NLA_BINARY,
				      .len = PORT_UUID_MAX पूर्ण,
	[IFLA_PORT_HOST_UUID]	= अणु .type = NLA_STRING,
				    .len = PORT_UUID_MAX पूर्ण,
	[IFLA_PORT_REQUEST]	= अणु .type = NLA_U8, पूर्ण,
	[IFLA_PORT_RESPONSE]	= अणु .type = NLA_U16, पूर्ण,

	/* Unused, but we need to keep it here since user space could
	 * fill it. It's also broken with regard to NLA_BINARY use in
	 * combination with काष्ठाs.
	 */
	[IFLA_PORT_VSI_TYPE]	= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा अगरla_port_vsi) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy अगरla_xdp_policy[IFLA_XDP_MAX + 1] = अणु
	[IFLA_XDP_UNSPEC]	= अणु .strict_start_type = IFLA_XDP_EXPECTED_FD पूर्ण,
	[IFLA_XDP_FD]		= अणु .type = NLA_S32 पूर्ण,
	[IFLA_XDP_EXPECTED_FD]	= अणु .type = NLA_S32 पूर्ण,
	[IFLA_XDP_ATTACHED]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_XDP_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_XDP_PROG_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtnl_link_ops *linkinfo_to_kind_ops(स्थिर काष्ठा nlattr *nla)
अणु
	स्थिर काष्ठा rtnl_link_ops *ops = शून्य;
	काष्ठा nlattr *linfo[IFLA_INFO_MAX + 1];

	अगर (nla_parse_nested_deprecated(linfo, IFLA_INFO_MAX, nla, अगरla_info_policy, शून्य) < 0)
		वापस शून्य;

	अगर (linfo[IFLA_INFO_KIND]) अणु
		अक्षर kind[MODULE_NAME_LEN];

		nla_strscpy(kind, linfo[IFLA_INFO_KIND], माप(kind));
		ops = rtnl_link_ops_get(kind);
	पूर्ण

	वापस ops;
पूर्ण

अटल bool link_master_filtered(काष्ठा net_device *dev, पूर्णांक master_idx)
अणु
	काष्ठा net_device *master;

	अगर (!master_idx)
		वापस false;

	master = netdev_master_upper_dev_get(dev);
	अगर (!master || master->अगरindex != master_idx)
		वापस true;

	वापस false;
पूर्ण

अटल bool link_kind_filtered(स्थिर काष्ठा net_device *dev,
			       स्थिर काष्ठा rtnl_link_ops *kind_ops)
अणु
	अगर (kind_ops && dev->rtnl_link_ops != kind_ops)
		वापस true;

	वापस false;
पूर्ण

अटल bool link_dump_filtered(काष्ठा net_device *dev,
			       पूर्णांक master_idx,
			       स्थिर काष्ठा rtnl_link_ops *kind_ops)
अणु
	अगर (link_master_filtered(dev, master_idx) ||
	    link_kind_filtered(dev, kind_ops))
		वापस true;

	वापस false;
पूर्ण

/**
 * rtnl_get_net_ns_capable - Get netns अगर sufficiently privileged.
 * @sk: netlink socket
 * @netnsid: network namespace identअगरier
 *
 * Returns the network namespace identअगरied by netnsid on success or an error
 * poपूर्णांकer on failure.
 */
काष्ठा net *rtnl_get_net_ns_capable(काष्ठा sock *sk, पूर्णांक netnsid)
अणु
	काष्ठा net *net;

	net = get_net_ns_by_id(sock_net(sk), netnsid);
	अगर (!net)
		वापस ERR_PTR(-EINVAL);

	/* For now, the caller is required to have CAP_NET_ADMIN in
	 * the user namespace owning the target net ns.
	 */
	अगर (!sk_ns_capable(sk, net->user_ns, CAP_NET_ADMIN)) अणु
		put_net(net);
		वापस ERR_PTR(-EACCES);
	पूर्ण
	वापस net;
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_get_net_ns_capable);

अटल पूर्णांक rtnl_valid_dump_अगरinfo_req(स्थिर काष्ठा nlmsghdr *nlh,
				      bool strict_check, काष्ठा nlattr **tb,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक hdrlen;

	अगर (strict_check) अणु
		काष्ठा अगरinfomsg *अगरm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
			NL_SET_ERR_MSG(extack, "Invalid header for link dump");
			वापस -EINVAL;
		पूर्ण

		अगरm = nlmsg_data(nlh);
		अगर (अगरm->__अगरi_pad || अगरm->अगरi_type || अगरm->अगरi_flags ||
		    अगरm->अगरi_change) अणु
			NL_SET_ERR_MSG(extack, "Invalid values in header for link dump request");
			वापस -EINVAL;
		पूर्ण
		अगर (अगरm->अगरi_index) अणु
			NL_SET_ERR_MSG(extack, "Filter by device index not supported for link dumps");
			वापस -EINVAL;
		पूर्ण

		वापस nlmsg_parse_deprecated_strict(nlh, माप(*अगरm), tb,
						     IFLA_MAX, अगरla_policy,
						     extack);
	पूर्ण

	/* A hack to preserve kernel<->userspace पूर्णांकerface.
	 * The correct header is अगरinfomsg. It is consistent with rtnl_getlink.
	 * However, beक्रमe Linux v3.9 the code here assumed rtgenmsg and that's
	 * what iproute2 < v3.9.0 used.
	 * We can detect the old iproute2. Even including the IFLA_EXT_MASK
	 * attribute, its netlink message is लघुer than काष्ठा अगरinfomsg.
	 */
	hdrlen = nlmsg_len(nlh) < माप(काष्ठा अगरinfomsg) ?
		 माप(काष्ठा rtgenmsg) : माप(काष्ठा अगरinfomsg);

	वापस nlmsg_parse_deprecated(nlh, hdrlen, tb, IFLA_MAX, अगरla_policy,
				      extack);
पूर्ण

अटल पूर्णांक rtnl_dump_अगरinfo(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net *tgt_net = net;
	पूर्णांक h, s_h;
	पूर्णांक idx = 0, s_idx;
	काष्ठा net_device *dev;
	काष्ठा hlist_head *head;
	काष्ठा nlattr *tb[IFLA_MAX+1];
	u32 ext_filter_mask = 0;
	स्थिर काष्ठा rtnl_link_ops *kind_ops = शून्य;
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	पूर्णांक master_idx = 0;
	पूर्णांक netnsid = -1;
	पूर्णांक err, i;

	s_h = cb->args[0];
	s_idx = cb->args[1];

	err = rtnl_valid_dump_अगरinfo_req(nlh, cb->strict_check, tb, extack);
	अगर (err < 0) अणु
		अगर (cb->strict_check)
			वापस err;

		जाओ walk_entries;
	पूर्ण

	क्रम (i = 0; i <= IFLA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		/* new attributes should only be added with strict checking */
		चयन (i) अणु
		हाल IFLA_TARGET_NETNSID:
			netnsid = nla_get_s32(tb[i]);
			tgt_net = rtnl_get_net_ns_capable(skb->sk, netnsid);
			अगर (IS_ERR(tgt_net)) अणु
				NL_SET_ERR_MSG(extack, "Invalid target network namespace id");
				वापस PTR_ERR(tgt_net);
			पूर्ण
			अवरोध;
		हाल IFLA_EXT_MASK:
			ext_filter_mask = nla_get_u32(tb[i]);
			अवरोध;
		हाल IFLA_MASTER:
			master_idx = nla_get_u32(tb[i]);
			अवरोध;
		हाल IFLA_LINKINFO:
			kind_ops = linkinfo_to_kind_ops(tb[i]);
			अवरोध;
		शेष:
			अगर (cb->strict_check) अणु
				NL_SET_ERR_MSG(extack, "Unsupported attribute in link dump request");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (master_idx || kind_ops)
		flags |= NLM_F_DUMP_FILTERED;

walk_entries:
	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &tgt_net->dev_index_head[h];
		hlist_क्रम_each_entry(dev, head, index_hlist) अणु
			अगर (link_dump_filtered(dev, master_idx, kind_ops))
				जाओ cont;
			अगर (idx < s_idx)
				जाओ cont;
			err = rtnl_fill_अगरinfo(skb, dev, net,
					       RTM_NEWLINK,
					       NETLINK_CB(cb->skb).portid,
					       nlh->nlmsg_seq, 0, flags,
					       ext_filter_mask, 0, शून्य, 0,
					       netnsid, GFP_KERNEL);

			अगर (err < 0) अणु
				अगर (likely(skb->len))
					जाओ out;

				जाओ out_err;
			पूर्ण
cont:
			idx++;
		पूर्ण
	पूर्ण
out:
	err = skb->len;
out_err:
	cb->args[1] = idx;
	cb->args[0] = h;
	cb->seq = tgt_net->dev_base_seq;
	nl_dump_check_consistent(cb, nlmsg_hdr(skb));
	अगर (netnsid >= 0)
		put_net(tgt_net);

	वापस err;
पूर्ण

पूर्णांक rtnl_nla_parse_अगरla(काष्ठा nlattr **tb, स्थिर काष्ठा nlattr *head, पूर्णांक len,
			काष्ठा netlink_ext_ack *exterr)
अणु
	वापस nla_parse_deprecated(tb, IFLA_MAX, head, len, अगरla_policy,
				    exterr);
पूर्ण
EXPORT_SYMBOL(rtnl_nla_parse_अगरla);

काष्ठा net *rtnl_link_get_net(काष्ठा net *src_net, काष्ठा nlattr *tb[])
अणु
	काष्ठा net *net;
	/* Examine the link attributes and figure out which
	 * network namespace we are talking about.
	 */
	अगर (tb[IFLA_NET_NS_PID])
		net = get_net_ns_by_pid(nla_get_u32(tb[IFLA_NET_NS_PID]));
	अन्यथा अगर (tb[IFLA_NET_NS_FD])
		net = get_net_ns_by_fd(nla_get_u32(tb[IFLA_NET_NS_FD]));
	अन्यथा
		net = get_net(src_net);
	वापस net;
पूर्ण
EXPORT_SYMBOL(rtnl_link_get_net);

/* Figure out which network namespace we are talking about by
 * examining the link attributes in the following order:
 *
 * 1. IFLA_NET_NS_PID
 * 2. IFLA_NET_NS_FD
 * 3. IFLA_TARGET_NETNSID
 */
अटल काष्ठा net *rtnl_link_get_net_by_nlattr(काष्ठा net *src_net,
					       काष्ठा nlattr *tb[])
अणु
	काष्ठा net *net;

	अगर (tb[IFLA_NET_NS_PID] || tb[IFLA_NET_NS_FD])
		वापस rtnl_link_get_net(src_net, tb);

	अगर (!tb[IFLA_TARGET_NETNSID])
		वापस get_net(src_net);

	net = get_net_ns_by_id(src_net, nla_get_u32(tb[IFLA_TARGET_NETNSID]));
	अगर (!net)
		वापस ERR_PTR(-EINVAL);

	वापस net;
पूर्ण

अटल काष्ठा net *rtnl_link_get_net_capable(स्थिर काष्ठा sk_buff *skb,
					     काष्ठा net *src_net,
					     काष्ठा nlattr *tb[], पूर्णांक cap)
अणु
	काष्ठा net *net;

	net = rtnl_link_get_net_by_nlattr(src_net, tb);
	अगर (IS_ERR(net))
		वापस net;

	अगर (!netlink_ns_capable(skb, net->user_ns, cap)) अणु
		put_net(net);
		वापस ERR_PTR(-EPERM);
	पूर्ण

	वापस net;
पूर्ण

/* Verअगरy that rtnetlink requests करो not pass additional properties
 * potentially referring to dअगरferent network namespaces.
 */
अटल पूर्णांक rtnl_ensure_unique_netns(काष्ठा nlattr *tb[],
				    काष्ठा netlink_ext_ack *extack,
				    bool netns_id_only)
अणु

	अगर (netns_id_only) अणु
		अगर (!tb[IFLA_NET_NS_PID] && !tb[IFLA_NET_NS_FD])
			वापस 0;

		NL_SET_ERR_MSG(extack, "specified netns attribute not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[IFLA_TARGET_NETNSID] && (tb[IFLA_NET_NS_PID] || tb[IFLA_NET_NS_FD]))
		जाओ invalid_attr;

	अगर (tb[IFLA_NET_NS_PID] && (tb[IFLA_TARGET_NETNSID] || tb[IFLA_NET_NS_FD]))
		जाओ invalid_attr;

	अगर (tb[IFLA_NET_NS_FD] && (tb[IFLA_TARGET_NETNSID] || tb[IFLA_NET_NS_PID]))
		जाओ invalid_attr;

	वापस 0;

invalid_attr:
	NL_SET_ERR_MSG(extack, "multiple netns identifying attributes specified");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक validate_linkmsg(काष्ठा net_device *dev, काष्ठा nlattr *tb[])
अणु
	अगर (dev) अणु
		अगर (tb[IFLA_ADDRESS] &&
		    nla_len(tb[IFLA_ADDRESS]) < dev->addr_len)
			वापस -EINVAL;

		अगर (tb[IFLA_BROADCAST] &&
		    nla_len(tb[IFLA_BROADCAST]) < dev->addr_len)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[IFLA_AF_SPEC]) अणु
		काष्ठा nlattr *af;
		पूर्णांक rem, err;

		nla_क्रम_each_nested(af, tb[IFLA_AF_SPEC], rem) अणु
			स्थिर काष्ठा rtnl_af_ops *af_ops;

			rcu_पढ़ो_lock();
			af_ops = rtnl_af_lookup(nla_type(af));
			अगर (!af_ops) अणु
				rcu_पढ़ो_unlock();
				वापस -EAFNOSUPPORT;
			पूर्ण

			अगर (!af_ops->set_link_af) अणु
				rcu_पढ़ो_unlock();
				वापस -EOPNOTSUPP;
			पूर्ण

			अगर (af_ops->validate_link_af) अणु
				err = af_ops->validate_link_af(dev, af);
				अगर (err < 0) अणु
					rcu_पढ़ो_unlock();
					वापस err;
				पूर्ण
			पूर्ण

			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक handle_infiniband_guid(काष्ठा net_device *dev, काष्ठा अगरla_vf_guid *ivt,
				  पूर्णांक guid_type)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

	वापस ops->nकरो_set_vf_guid(dev, ivt->vf, ivt->guid, guid_type);
पूर्ण

अटल पूर्णांक handle_vf_guid(काष्ठा net_device *dev, काष्ठा अगरla_vf_guid *ivt, पूर्णांक guid_type)
अणु
	अगर (dev->type != ARPHRD_INFINIBAND)
		वापस -EOPNOTSUPP;

	वापस handle_infiniband_guid(dev, ivt, guid_type);
पूर्ण

अटल पूर्णांक करो_setvfinfo(काष्ठा net_device *dev, काष्ठा nlattr **tb)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक err = -EINVAL;

	अगर (tb[IFLA_VF_MAC]) अणु
		काष्ठा अगरla_vf_mac *ivm = nla_data(tb[IFLA_VF_MAC]);

		अगर (ivm->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_mac)
			err = ops->nकरो_set_vf_mac(dev, ivm->vf,
						  ivm->mac);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_VLAN]) अणु
		काष्ठा अगरla_vf_vlan *ivv = nla_data(tb[IFLA_VF_VLAN]);

		अगर (ivv->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_vlan)
			err = ops->nकरो_set_vf_vlan(dev, ivv->vf, ivv->vlan,
						   ivv->qos,
						   htons(ETH_P_8021Q));
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_VLAN_LIST]) अणु
		काष्ठा अगरla_vf_vlan_info *ivvl[MAX_VLAN_LIST_LEN];
		काष्ठा nlattr *attr;
		पूर्णांक rem, len = 0;

		err = -EOPNOTSUPP;
		अगर (!ops->nकरो_set_vf_vlan)
			वापस err;

		nla_क्रम_each_nested(attr, tb[IFLA_VF_VLAN_LIST], rem) अणु
			अगर (nla_type(attr) != IFLA_VF_VLAN_INFO ||
			    nla_len(attr) < NLA_HDRLEN) अणु
				वापस -EINVAL;
			पूर्ण
			अगर (len >= MAX_VLAN_LIST_LEN)
				वापस -EOPNOTSUPP;
			ivvl[len] = nla_data(attr);

			len++;
		पूर्ण
		अगर (len == 0)
			वापस -EINVAL;

		अगर (ivvl[0]->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = ops->nकरो_set_vf_vlan(dev, ivvl[0]->vf, ivvl[0]->vlan,
					   ivvl[0]->qos, ivvl[0]->vlan_proto);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_TX_RATE]) अणु
		काष्ठा अगरla_vf_tx_rate *ivt = nla_data(tb[IFLA_VF_TX_RATE]);
		काष्ठा अगरla_vf_info ivf;

		अगर (ivt->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_get_vf_config)
			err = ops->nकरो_get_vf_config(dev, ivt->vf, &ivf);
		अगर (err < 0)
			वापस err;

		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_rate)
			err = ops->nकरो_set_vf_rate(dev, ivt->vf,
						   ivf.min_tx_rate,
						   ivt->rate);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_RATE]) अणु
		काष्ठा अगरla_vf_rate *ivt = nla_data(tb[IFLA_VF_RATE]);

		अगर (ivt->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_rate)
			err = ops->nकरो_set_vf_rate(dev, ivt->vf,
						   ivt->min_tx_rate,
						   ivt->max_tx_rate);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_SPOOFCHK]) अणु
		काष्ठा अगरla_vf_spoofchk *ivs = nla_data(tb[IFLA_VF_SPOOFCHK]);

		अगर (ivs->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_spoofchk)
			err = ops->nकरो_set_vf_spoofchk(dev, ivs->vf,
						       ivs->setting);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_LINK_STATE]) अणु
		काष्ठा अगरla_vf_link_state *ivl = nla_data(tb[IFLA_VF_LINK_STATE]);

		अगर (ivl->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_link_state)
			err = ops->nकरो_set_vf_link_state(dev, ivl->vf,
							 ivl->link_state);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_RSS_QUERY_EN]) अणु
		काष्ठा अगरla_vf_rss_query_en *ivrssq_en;

		err = -EOPNOTSUPP;
		ivrssq_en = nla_data(tb[IFLA_VF_RSS_QUERY_EN]);
		अगर (ivrssq_en->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		अगर (ops->nकरो_set_vf_rss_query_en)
			err = ops->nकरो_set_vf_rss_query_en(dev, ivrssq_en->vf,
							   ivrssq_en->setting);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_TRUST]) अणु
		काष्ठा अगरla_vf_trust *ivt = nla_data(tb[IFLA_VF_TRUST]);

		अगर (ivt->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_trust)
			err = ops->nकरो_set_vf_trust(dev, ivt->vf, ivt->setting);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_VF_IB_NODE_GUID]) अणु
		काष्ठा अगरla_vf_guid *ivt = nla_data(tb[IFLA_VF_IB_NODE_GUID]);

		अगर (ivt->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		अगर (!ops->nकरो_set_vf_guid)
			वापस -EOPNOTSUPP;
		वापस handle_vf_guid(dev, ivt, IFLA_VF_IB_NODE_GUID);
	पूर्ण

	अगर (tb[IFLA_VF_IB_PORT_GUID]) अणु
		काष्ठा अगरla_vf_guid *ivt = nla_data(tb[IFLA_VF_IB_PORT_GUID]);

		अगर (ivt->vf >= पूर्णांक_उच्च)
			वापस -EINVAL;
		अगर (!ops->nकरो_set_vf_guid)
			वापस -EOPNOTSUPP;

		वापस handle_vf_guid(dev, ivt, IFLA_VF_IB_PORT_GUID);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक करो_set_master(काष्ठा net_device *dev, पूर्णांक अगरindex,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *upper_dev = netdev_master_upper_dev_get(dev);
	स्थिर काष्ठा net_device_ops *ops;
	पूर्णांक err;

	अगर (upper_dev) अणु
		अगर (upper_dev->अगरindex == अगरindex)
			वापस 0;
		ops = upper_dev->netdev_ops;
		अगर (ops->nकरो_del_slave) अणु
			err = ops->nकरो_del_slave(upper_dev, dev);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (अगरindex) अणु
		upper_dev = __dev_get_by_index(dev_net(dev), अगरindex);
		अगर (!upper_dev)
			वापस -EINVAL;
		ops = upper_dev->netdev_ops;
		अगर (ops->nकरो_add_slave) अणु
			err = ops->nकरो_add_slave(upper_dev, dev, extack);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy अगरla_proto_करोwn_reason_policy[IFLA_PROTO_DOWN_REASON_VALUE + 1] = अणु
	[IFLA_PROTO_DOWN_REASON_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_PROTO_DOWN_REASON_VALUE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक करो_set_proto_करोwn(काष्ठा net_device *dev,
			     काष्ठा nlattr *nl_proto_करोwn,
			     काष्ठा nlattr *nl_proto_करोwn_reason,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *pdreason[IFLA_PROTO_DOWN_REASON_MAX + 1];
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	अचिन्हित दीर्घ mask = 0;
	u32 value;
	bool proto_करोwn;
	पूर्णांक err;

	अगर (!ops->nकरो_change_proto_करोwn) अणु
		NL_SET_ERR_MSG(extack,  "Protodown not supported by device");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (nl_proto_करोwn_reason) अणु
		err = nla_parse_nested_deprecated(pdreason,
						  IFLA_PROTO_DOWN_REASON_MAX,
						  nl_proto_करोwn_reason,
						  अगरla_proto_करोwn_reason_policy,
						  शून्य);
		अगर (err < 0)
			वापस err;

		अगर (!pdreason[IFLA_PROTO_DOWN_REASON_VALUE]) अणु
			NL_SET_ERR_MSG(extack, "Invalid protodown reason value");
			वापस -EINVAL;
		पूर्ण

		value = nla_get_u32(pdreason[IFLA_PROTO_DOWN_REASON_VALUE]);

		अगर (pdreason[IFLA_PROTO_DOWN_REASON_MASK])
			mask = nla_get_u32(pdreason[IFLA_PROTO_DOWN_REASON_MASK]);

		dev_change_proto_करोwn_reason(dev, mask, value);
	पूर्ण

	अगर (nl_proto_करोwn) अणु
		proto_करोwn = nla_get_u8(nl_proto_करोwn);

		/* Dont turn off protoकरोwn अगर there are active reasons */
		अगर (!proto_करोwn && dev->proto_करोwn_reason) अणु
			NL_SET_ERR_MSG(extack, "Cannot clear protodown, active reasons");
			वापस -EBUSY;
		पूर्ण
		err = dev_change_proto_करोwn(dev,
					    proto_करोwn);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DO_SETLINK_MODIFIED	0x01
/* notअगरy flag means notअगरy + modअगरied. */
#घोषणा DO_SETLINK_NOTIFY	0x03
अटल पूर्णांक करो_setlink(स्थिर काष्ठा sk_buff *skb,
		      काष्ठा net_device *dev, काष्ठा अगरinfomsg *अगरm,
		      काष्ठा netlink_ext_ack *extack,
		      काष्ठा nlattr **tb, अक्षर *अगरname, पूर्णांक status)
अणु
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक err;

	err = validate_linkmsg(dev, tb);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_NET_NS_PID] || tb[IFLA_NET_NS_FD] || tb[IFLA_TARGET_NETNSID]) अणु
		काष्ठा net *net;
		पूर्णांक new_अगरindex;

		net = rtnl_link_get_net_capable(skb, dev_net(dev),
						tb, CAP_NET_ADMIN);
		अगर (IS_ERR(net)) अणु
			err = PTR_ERR(net);
			जाओ errout;
		पूर्ण

		अगर (tb[IFLA_NEW_IFINDEX])
			new_अगरindex = nla_get_s32(tb[IFLA_NEW_IFINDEX]);
		अन्यथा
			new_अगरindex = 0;

		err = __dev_change_net_namespace(dev, net, अगरname, new_अगरindex);
		put_net(net);
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_MAP]) अणु
		काष्ठा rtnl_link_अगरmap *u_map;
		काष्ठा अगरmap k_map;

		अगर (!ops->nकरो_set_config) अणु
			err = -EOPNOTSUPP;
			जाओ errout;
		पूर्ण

		अगर (!netअगर_device_present(dev)) अणु
			err = -ENODEV;
			जाओ errout;
		पूर्ण

		u_map = nla_data(tb[IFLA_MAP]);
		k_map.mem_start = (अचिन्हित दीर्घ) u_map->mem_start;
		k_map.mem_end = (अचिन्हित दीर्घ) u_map->mem_end;
		k_map.base_addr = (अचिन्हित लघु) u_map->base_addr;
		k_map.irq = (अचिन्हित अक्षर) u_map->irq;
		k_map.dma = (अचिन्हित अक्षर) u_map->dma;
		k_map.port = (अचिन्हित अक्षर) u_map->port;

		err = ops->nकरो_set_config(dev, &k_map);
		अगर (err < 0)
			जाओ errout;

		status |= DO_SETLINK_NOTIFY;
	पूर्ण

	अगर (tb[IFLA_ADDRESS]) अणु
		काष्ठा sockaddr *sa;
		पूर्णांक len;

		len = माप(sa_family_t) + max_t(माप_प्रकार, dev->addr_len,
						  माप(*sa));
		sa = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!sa) अणु
			err = -ENOMEM;
			जाओ errout;
		पूर्ण
		sa->sa_family = dev->type;
		स_नकल(sa->sa_data, nla_data(tb[IFLA_ADDRESS]),
		       dev->addr_len);
		err = dev_set_mac_address_user(dev, sa, extack);
		kमुक्त(sa);
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_MTU]) अणु
		err = dev_set_mtu_ext(dev, nla_get_u32(tb[IFLA_MTU]), extack);
		अगर (err < 0)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_GROUP]) अणु
		dev_set_group(dev, nla_get_u32(tb[IFLA_GROUP]));
		status |= DO_SETLINK_NOTIFY;
	पूर्ण

	/*
	 * Interface selected by पूर्णांकerface index but पूर्णांकerface
	 * name provided implies that a name change has been
	 * requested.
	 */
	अगर (अगरm->अगरi_index > 0 && अगरname[0]) अणु
		err = dev_change_name(dev, अगरname);
		अगर (err < 0)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_IFALIAS]) अणु
		err = dev_set_alias(dev, nla_data(tb[IFLA_IFALIAS]),
				    nla_len(tb[IFLA_IFALIAS]));
		अगर (err < 0)
			जाओ errout;
		status |= DO_SETLINK_NOTIFY;
	पूर्ण

	अगर (tb[IFLA_BROADCAST]) अणु
		nla_स_नकल(dev->broadcast, tb[IFLA_BROADCAST], dev->addr_len);
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
	पूर्ण

	अगर (अगरm->अगरi_flags || अगरm->अगरi_change) अणु
		err = dev_change_flags(dev, rtnl_dev_combine_flags(dev, अगरm),
				       extack);
		अगर (err < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[IFLA_MASTER]) अणु
		err = करो_set_master(dev, nla_get_u32(tb[IFLA_MASTER]), extack);
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_CARRIER]) अणु
		err = dev_change_carrier(dev, nla_get_u8(tb[IFLA_CARRIER]));
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_TXQLEN]) अणु
		अचिन्हित पूर्णांक value = nla_get_u32(tb[IFLA_TXQLEN]);

		err = dev_change_tx_queue_len(dev, value);
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_MODIFIED;
	पूर्ण

	अगर (tb[IFLA_GSO_MAX_SIZE]) अणु
		u32 max_size = nla_get_u32(tb[IFLA_GSO_MAX_SIZE]);

		अगर (max_size > GSO_MAX_SIZE) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण

		अगर (dev->gso_max_size ^ max_size) अणु
			netअगर_set_gso_max_size(dev, max_size);
			status |= DO_SETLINK_MODIFIED;
		पूर्ण
	पूर्ण

	अगर (tb[IFLA_GSO_MAX_SEGS]) अणु
		u32 max_segs = nla_get_u32(tb[IFLA_GSO_MAX_SEGS]);

		अगर (max_segs > GSO_MAX_SEGS) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण

		अगर (dev->gso_max_segs ^ max_segs) अणु
			dev->gso_max_segs = max_segs;
			status |= DO_SETLINK_MODIFIED;
		पूर्ण
	पूर्ण

	अगर (tb[IFLA_OPERSTATE])
		set_operstate(dev, nla_get_u8(tb[IFLA_OPERSTATE]));

	अगर (tb[IFLA_LINKMODE]) अणु
		अचिन्हित अक्षर value = nla_get_u8(tb[IFLA_LINKMODE]);

		ग_लिखो_lock_bh(&dev_base_lock);
		अगर (dev->link_mode ^ value)
			status |= DO_SETLINK_NOTIFY;
		dev->link_mode = value;
		ग_लिखो_unlock_bh(&dev_base_lock);
	पूर्ण

	अगर (tb[IFLA_VFINFO_LIST]) अणु
		काष्ठा nlattr *vfinfo[IFLA_VF_MAX + 1];
		काष्ठा nlattr *attr;
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, tb[IFLA_VFINFO_LIST], rem) अणु
			अगर (nla_type(attr) != IFLA_VF_INFO ||
			    nla_len(attr) < NLA_HDRLEN) अणु
				err = -EINVAL;
				जाओ errout;
			पूर्ण
			err = nla_parse_nested_deprecated(vfinfo, IFLA_VF_MAX,
							  attr,
							  अगरla_vf_policy,
							  शून्य);
			अगर (err < 0)
				जाओ errout;
			err = करो_setvfinfo(dev, vfinfo);
			अगर (err < 0)
				जाओ errout;
			status |= DO_SETLINK_NOTIFY;
		पूर्ण
	पूर्ण
	err = 0;

	अगर (tb[IFLA_VF_PORTS]) अणु
		काष्ठा nlattr *port[IFLA_PORT_MAX+1];
		काष्ठा nlattr *attr;
		पूर्णांक vf;
		पूर्णांक rem;

		err = -EOPNOTSUPP;
		अगर (!ops->nकरो_set_vf_port)
			जाओ errout;

		nla_क्रम_each_nested(attr, tb[IFLA_VF_PORTS], rem) अणु
			अगर (nla_type(attr) != IFLA_VF_PORT ||
			    nla_len(attr) < NLA_HDRLEN) अणु
				err = -EINVAL;
				जाओ errout;
			पूर्ण
			err = nla_parse_nested_deprecated(port, IFLA_PORT_MAX,
							  attr,
							  अगरla_port_policy,
							  शून्य);
			अगर (err < 0)
				जाओ errout;
			अगर (!port[IFLA_PORT_VF]) अणु
				err = -EOPNOTSUPP;
				जाओ errout;
			पूर्ण
			vf = nla_get_u32(port[IFLA_PORT_VF]);
			err = ops->nकरो_set_vf_port(dev, vf, port);
			अगर (err < 0)
				जाओ errout;
			status |= DO_SETLINK_NOTIFY;
		पूर्ण
	पूर्ण
	err = 0;

	अगर (tb[IFLA_PORT_SELF]) अणु
		काष्ठा nlattr *port[IFLA_PORT_MAX+1];

		err = nla_parse_nested_deprecated(port, IFLA_PORT_MAX,
						  tb[IFLA_PORT_SELF],
						  अगरla_port_policy, शून्य);
		अगर (err < 0)
			जाओ errout;

		err = -EOPNOTSUPP;
		अगर (ops->nकरो_set_vf_port)
			err = ops->nकरो_set_vf_port(dev, PORT_SELF_VF, port);
		अगर (err < 0)
			जाओ errout;
		status |= DO_SETLINK_NOTIFY;
	पूर्ण

	अगर (tb[IFLA_AF_SPEC]) अणु
		काष्ठा nlattr *af;
		पूर्णांक rem;

		nla_क्रम_each_nested(af, tb[IFLA_AF_SPEC], rem) अणु
			स्थिर काष्ठा rtnl_af_ops *af_ops;

			rcu_पढ़ो_lock();

			BUG_ON(!(af_ops = rtnl_af_lookup(nla_type(af))));

			err = af_ops->set_link_af(dev, af, extack);
			अगर (err < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ errout;
			पूर्ण

			rcu_पढ़ो_unlock();
			status |= DO_SETLINK_NOTIFY;
		पूर्ण
	पूर्ण
	err = 0;

	अगर (tb[IFLA_PROTO_DOWN] || tb[IFLA_PROTO_DOWN_REASON]) अणु
		err = करो_set_proto_करोwn(dev, tb[IFLA_PROTO_DOWN],
					tb[IFLA_PROTO_DOWN_REASON], extack);
		अगर (err)
			जाओ errout;
		status |= DO_SETLINK_NOTIFY;
	पूर्ण

	अगर (tb[IFLA_XDP]) अणु
		काष्ठा nlattr *xdp[IFLA_XDP_MAX + 1];
		u32 xdp_flags = 0;

		err = nla_parse_nested_deprecated(xdp, IFLA_XDP_MAX,
						  tb[IFLA_XDP],
						  अगरla_xdp_policy, शून्य);
		अगर (err < 0)
			जाओ errout;

		अगर (xdp[IFLA_XDP_ATTACHED] || xdp[IFLA_XDP_PROG_ID]) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण

		अगर (xdp[IFLA_XDP_FLAGS]) अणु
			xdp_flags = nla_get_u32(xdp[IFLA_XDP_FLAGS]);
			अगर (xdp_flags & ~XDP_FLAGS_MASK) अणु
				err = -EINVAL;
				जाओ errout;
			पूर्ण
			अगर (hweight32(xdp_flags & XDP_FLAGS_MODES) > 1) अणु
				err = -EINVAL;
				जाओ errout;
			पूर्ण
		पूर्ण

		अगर (xdp[IFLA_XDP_FD]) अणु
			पूर्णांक expected_fd = -1;

			अगर (xdp_flags & XDP_FLAGS_REPLACE) अणु
				अगर (!xdp[IFLA_XDP_EXPECTED_FD]) अणु
					err = -EINVAL;
					जाओ errout;
				पूर्ण
				expected_fd =
					nla_get_s32(xdp[IFLA_XDP_EXPECTED_FD]);
			पूर्ण

			err = dev_change_xdp_fd(dev, extack,
						nla_get_s32(xdp[IFLA_XDP_FD]),
						expected_fd,
						xdp_flags);
			अगर (err)
				जाओ errout;
			status |= DO_SETLINK_NOTIFY;
		पूर्ण
	पूर्ण

errout:
	अगर (status & DO_SETLINK_MODIFIED) अणु
		अगर ((status & DO_SETLINK_NOTIFY) == DO_SETLINK_NOTIFY)
			netdev_state_change(dev);

		अगर (err < 0)
			net_warn_ratelimited("A link change request failed with some changes committed already. Interface %s may have been left with an inconsistent configuration, please check.\n",
					     dev->name);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा net_device *rtnl_dev_get(काष्ठा net *net,
				       काष्ठा nlattr *अगरname_attr,
				       काष्ठा nlattr *altअगरname_attr,
				       अक्षर *अगरname)
अणु
	अक्षर buffer[ALTIFNAMSIZ];

	अगर (!अगरname) अणु
		अगरname = buffer;
		अगर (अगरname_attr)
			nla_strscpy(अगरname, अगरname_attr, IFNAMSIZ);
		अन्यथा अगर (altअगरname_attr)
			nla_strscpy(अगरname, altअगरname_attr, ALTIFNAMSIZ);
		अन्यथा
			वापस शून्य;
	पूर्ण

	वापस __dev_get_by_name(net, अगरname);
पूर्ण

अटल पूर्णांक rtnl_setlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा net_device *dev;
	पूर्णांक err;
	काष्ठा nlattr *tb[IFLA_MAX+1];
	अक्षर अगरname[IFNAMSIZ];

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFLA_MAX,
				     अगरla_policy, extack);
	अगर (err < 0)
		जाओ errout;

	err = rtnl_ensure_unique_netns(tb, extack, false);
	अगर (err < 0)
		जाओ errout;

	अगर (tb[IFLA_IFNAME])
		nla_strscpy(अगरname, tb[IFLA_IFNAME], IFNAMSIZ);
	अन्यथा
		अगरname[0] = '\0';

	err = -EINVAL;
	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_index > 0)
		dev = __dev_get_by_index(net, अगरm->अगरi_index);
	अन्यथा अगर (tb[IFLA_IFNAME] || tb[IFLA_ALT_IFNAME])
		dev = rtnl_dev_get(net, शून्य, tb[IFLA_ALT_IFNAME], अगरname);
	अन्यथा
		जाओ errout;

	अगर (dev == शून्य) अणु
		err = -ENODEV;
		जाओ errout;
	पूर्ण

	err = करो_setlink(skb, dev, अगरm, extack, tb, अगरname, 0);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_group_dellink(स्थिर काष्ठा net *net, पूर्णांक group)
अणु
	काष्ठा net_device *dev, *aux;
	LIST_HEAD(list_समाप्त);
	bool found = false;

	अगर (!group)
		वापस -EPERM;

	क्रम_each_netdev(net, dev) अणु
		अगर (dev->group == group) अणु
			स्थिर काष्ठा rtnl_link_ops *ops;

			found = true;
			ops = dev->rtnl_link_ops;
			अगर (!ops || !ops->dellink)
				वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -ENODEV;

	क्रम_each_netdev_safe(net, dev, aux) अणु
		अगर (dev->group == group) अणु
			स्थिर काष्ठा rtnl_link_ops *ops;

			ops = dev->rtnl_link_ops;
			ops->dellink(dev, &list_समाप्त);
		पूर्ण
	पूर्ण
	unरेजिस्टर_netdevice_many(&list_समाप्त);

	वापस 0;
पूर्ण

पूर्णांक rtnl_delete_link(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा rtnl_link_ops *ops;
	LIST_HEAD(list_समाप्त);

	ops = dev->rtnl_link_ops;
	अगर (!ops || !ops->dellink)
		वापस -EOPNOTSUPP;

	ops->dellink(dev, &list_समाप्त);
	unरेजिस्टर_netdevice_many(&list_समाप्त);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtnl_delete_link);

अटल पूर्णांक rtnl_dellink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net *tgt_net = net;
	काष्ठा net_device *dev = शून्य;
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा nlattr *tb[IFLA_MAX+1];
	पूर्णांक err;
	पूर्णांक netnsid = -1;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFLA_MAX,
				     अगरla_policy, extack);
	अगर (err < 0)
		वापस err;

	err = rtnl_ensure_unique_netns(tb, extack, true);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_TARGET_NETNSID]) अणु
		netnsid = nla_get_s32(tb[IFLA_TARGET_NETNSID]);
		tgt_net = rtnl_get_net_ns_capable(NETLINK_CB(skb).sk, netnsid);
		अगर (IS_ERR(tgt_net))
			वापस PTR_ERR(tgt_net);
	पूर्ण

	err = -EINVAL;
	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_index > 0)
		dev = __dev_get_by_index(tgt_net, अगरm->अगरi_index);
	अन्यथा अगर (tb[IFLA_IFNAME] || tb[IFLA_ALT_IFNAME])
		dev = rtnl_dev_get(net, tb[IFLA_IFNAME],
				   tb[IFLA_ALT_IFNAME], शून्य);
	अन्यथा अगर (tb[IFLA_GROUP])
		err = rtnl_group_dellink(tgt_net, nla_get_u32(tb[IFLA_GROUP]));
	अन्यथा
		जाओ out;

	अगर (!dev) अणु
		अगर (tb[IFLA_IFNAME] || अगरm->अगरi_index > 0)
			err = -ENODEV;

		जाओ out;
	पूर्ण

	err = rtnl_delete_link(dev);

out:
	अगर (netnsid >= 0)
		put_net(tgt_net);

	वापस err;
पूर्ण

पूर्णांक rtnl_configure_link(काष्ठा net_device *dev, स्थिर काष्ठा अगरinfomsg *अगरm)
अणु
	अचिन्हित पूर्णांक old_flags;
	पूर्णांक err;

	old_flags = dev->flags;
	अगर (अगरm && (अगरm->अगरi_flags || अगरm->अगरi_change)) अणु
		err = __dev_change_flags(dev, rtnl_dev_combine_flags(dev, अगरm),
					 शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (dev->rtnl_link_state == RTNL_LINK_INITIALIZED) अणु
		__dev_notअगरy_flags(dev, old_flags, (old_flags ^ dev->flags));
	पूर्ण अन्यथा अणु
		dev->rtnl_link_state = RTNL_LINK_INITIALIZED;
		__dev_notअगरy_flags(dev, old_flags, ~0U);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtnl_configure_link);

काष्ठा net_device *rtnl_create_link(काष्ठा net *net, स्थिर अक्षर *अगरname,
				    अचिन्हित अक्षर name_assign_type,
				    स्थिर काष्ठा rtnl_link_ops *ops,
				    काष्ठा nlattr *tb[],
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक num_tx_queues = 1;
	अचिन्हित पूर्णांक num_rx_queues = 1;

	अगर (tb[IFLA_NUM_TX_QUEUES])
		num_tx_queues = nla_get_u32(tb[IFLA_NUM_TX_QUEUES]);
	अन्यथा अगर (ops->get_num_tx_queues)
		num_tx_queues = ops->get_num_tx_queues();

	अगर (tb[IFLA_NUM_RX_QUEUES])
		num_rx_queues = nla_get_u32(tb[IFLA_NUM_RX_QUEUES]);
	अन्यथा अगर (ops->get_num_rx_queues)
		num_rx_queues = ops->get_num_rx_queues();

	अगर (num_tx_queues < 1 || num_tx_queues > 4096) अणु
		NL_SET_ERR_MSG(extack, "Invalid number of transmit queues");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (num_rx_queues < 1 || num_rx_queues > 4096) अणु
		NL_SET_ERR_MSG(extack, "Invalid number of receive queues");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dev = alloc_netdev_mqs(ops->priv_size, अगरname, name_assign_type,
			       ops->setup, num_tx_queues, num_rx_queues);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev_net_set(dev, net);
	dev->rtnl_link_ops = ops;
	dev->rtnl_link_state = RTNL_LINK_INITIALIZING;

	अगर (tb[IFLA_MTU]) अणु
		u32 mtu = nla_get_u32(tb[IFLA_MTU]);
		पूर्णांक err;

		err = dev_validate_mtu(dev, mtu, extack);
		अगर (err) अणु
			मुक्त_netdev(dev);
			वापस ERR_PTR(err);
		पूर्ण
		dev->mtu = mtu;
	पूर्ण
	अगर (tb[IFLA_ADDRESS]) अणु
		स_नकल(dev->dev_addr, nla_data(tb[IFLA_ADDRESS]),
				nla_len(tb[IFLA_ADDRESS]));
		dev->addr_assign_type = NET_ADDR_SET;
	पूर्ण
	अगर (tb[IFLA_BROADCAST])
		स_नकल(dev->broadcast, nla_data(tb[IFLA_BROADCAST]),
				nla_len(tb[IFLA_BROADCAST]));
	अगर (tb[IFLA_TXQLEN])
		dev->tx_queue_len = nla_get_u32(tb[IFLA_TXQLEN]);
	अगर (tb[IFLA_OPERSTATE])
		set_operstate(dev, nla_get_u8(tb[IFLA_OPERSTATE]));
	अगर (tb[IFLA_LINKMODE])
		dev->link_mode = nla_get_u8(tb[IFLA_LINKMODE]);
	अगर (tb[IFLA_GROUP])
		dev_set_group(dev, nla_get_u32(tb[IFLA_GROUP]));
	अगर (tb[IFLA_GSO_MAX_SIZE])
		netअगर_set_gso_max_size(dev, nla_get_u32(tb[IFLA_GSO_MAX_SIZE]));
	अगर (tb[IFLA_GSO_MAX_SEGS])
		dev->gso_max_segs = nla_get_u32(tb[IFLA_GSO_MAX_SEGS]);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(rtnl_create_link);

अटल पूर्णांक rtnl_group_changelink(स्थिर काष्ठा sk_buff *skb,
		काष्ठा net *net, पूर्णांक group,
		काष्ठा अगरinfomsg *अगरm,
		काष्ठा netlink_ext_ack *extack,
		काष्ठा nlattr **tb)
अणु
	काष्ठा net_device *dev, *aux;
	पूर्णांक err;

	क्रम_each_netdev_safe(net, dev, aux) अणु
		अगर (dev->group == group) अणु
			err = करो_setlink(skb, dev, अगरm, extack, tb, शून्य, 0);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __rtnl_newlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा nlattr **attr, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *slave_attr[RTNL_SLAVE_MAX_TYPE + 1];
	अचिन्हित अक्षर name_assign_type = NET_NAME_USER;
	काष्ठा nlattr *linkinfo[IFLA_INFO_MAX + 1];
	स्थिर काष्ठा rtnl_link_ops *m_ops = शून्य;
	काष्ठा net_device *master_dev = शून्य;
	काष्ठा net *net = sock_net(skb->sk);
	स्थिर काष्ठा rtnl_link_ops *ops;
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net *dest_net, *link_net;
	काष्ठा nlattr **slave_data;
	अक्षर kind[MODULE_NAME_LEN];
	काष्ठा net_device *dev;
	काष्ठा अगरinfomsg *अगरm;
	अक्षर अगरname[IFNAMSIZ];
	काष्ठा nlattr **data;
	पूर्णांक err;

#अगर_घोषित CONFIG_MODULES
replay:
#पूर्ण_अगर
	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFLA_MAX,
				     अगरla_policy, extack);
	अगर (err < 0)
		वापस err;

	err = rtnl_ensure_unique_netns(tb, extack, false);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_IFNAME])
		nla_strscpy(अगरname, tb[IFLA_IFNAME], IFNAMSIZ);
	अन्यथा
		अगरname[0] = '\0';

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_index > 0)
		dev = __dev_get_by_index(net, अगरm->अगरi_index);
	अन्यथा अगर (tb[IFLA_IFNAME] || tb[IFLA_ALT_IFNAME])
		dev = rtnl_dev_get(net, शून्य, tb[IFLA_ALT_IFNAME], अगरname);
	अन्यथा
		dev = शून्य;

	अगर (dev) अणु
		master_dev = netdev_master_upper_dev_get(dev);
		अगर (master_dev)
			m_ops = master_dev->rtnl_link_ops;
	पूर्ण

	err = validate_linkmsg(dev, tb);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_LINKINFO]) अणु
		err = nla_parse_nested_deprecated(linkinfo, IFLA_INFO_MAX,
						  tb[IFLA_LINKINFO],
						  अगरla_info_policy, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा
		स_रखो(linkinfo, 0, माप(linkinfo));

	अगर (linkinfo[IFLA_INFO_KIND]) अणु
		nla_strscpy(kind, linkinfo[IFLA_INFO_KIND], माप(kind));
		ops = rtnl_link_ops_get(kind);
	पूर्ण अन्यथा अणु
		kind[0] = '\0';
		ops = शून्य;
	पूर्ण

	data = शून्य;
	अगर (ops) अणु
		अगर (ops->maxtype > RTNL_MAX_TYPE)
			वापस -EINVAL;

		अगर (ops->maxtype && linkinfo[IFLA_INFO_DATA]) अणु
			err = nla_parse_nested_deprecated(attr, ops->maxtype,
							  linkinfo[IFLA_INFO_DATA],
							  ops->policy, extack);
			अगर (err < 0)
				वापस err;
			data = attr;
		पूर्ण
		अगर (ops->validate) अणु
			err = ops->validate(tb, data, extack);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	slave_data = शून्य;
	अगर (m_ops) अणु
		अगर (m_ops->slave_maxtype > RTNL_SLAVE_MAX_TYPE)
			वापस -EINVAL;

		अगर (m_ops->slave_maxtype &&
		    linkinfo[IFLA_INFO_SLAVE_DATA]) अणु
			err = nla_parse_nested_deprecated(slave_attr,
							  m_ops->slave_maxtype,
							  linkinfo[IFLA_INFO_SLAVE_DATA],
							  m_ops->slave_policy,
							  extack);
			अगर (err < 0)
				वापस err;
			slave_data = slave_attr;
		पूर्ण
	पूर्ण

	अगर (dev) अणु
		पूर्णांक status = 0;

		अगर (nlh->nlmsg_flags & NLM_F_EXCL)
			वापस -EEXIST;
		अगर (nlh->nlmsg_flags & NLM_F_REPLACE)
			वापस -EOPNOTSUPP;

		अगर (linkinfo[IFLA_INFO_DATA]) अणु
			अगर (!ops || ops != dev->rtnl_link_ops ||
			    !ops->changelink)
				वापस -EOPNOTSUPP;

			err = ops->changelink(dev, tb, data, extack);
			अगर (err < 0)
				वापस err;
			status |= DO_SETLINK_NOTIFY;
		पूर्ण

		अगर (linkinfo[IFLA_INFO_SLAVE_DATA]) अणु
			अगर (!m_ops || !m_ops->slave_changelink)
				वापस -EOPNOTSUPP;

			err = m_ops->slave_changelink(master_dev, dev, tb,
						      slave_data, extack);
			अगर (err < 0)
				वापस err;
			status |= DO_SETLINK_NOTIFY;
		पूर्ण

		वापस करो_setlink(skb, dev, अगरm, extack, tb, अगरname, status);
	पूर्ण

	अगर (!(nlh->nlmsg_flags & NLM_F_CREATE)) अणु
		अगर (अगरm->अगरi_index == 0 && tb[IFLA_GROUP])
			वापस rtnl_group_changelink(skb, net,
						nla_get_u32(tb[IFLA_GROUP]),
						अगरm, extack, tb);
		वापस -ENODEV;
	पूर्ण

	अगर (tb[IFLA_MAP] || tb[IFLA_PROTINFO])
		वापस -EOPNOTSUPP;

	अगर (!ops) अणु
#अगर_घोषित CONFIG_MODULES
		अगर (kind[0]) अणु
			__rtnl_unlock();
			request_module("rtnl-link-%s", kind);
			rtnl_lock();
			ops = rtnl_link_ops_get(kind);
			अगर (ops)
				जाओ replay;
		पूर्ण
#पूर्ण_अगर
		NL_SET_ERR_MSG(extack, "Unknown device type");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ops->setup)
		वापस -EOPNOTSUPP;

	अगर (!अगरname[0]) अणु
		snम_लिखो(अगरname, IFNAMSIZ, "%s%%d", ops->kind);
		name_assign_type = NET_NAME_ENUM;
	पूर्ण

	dest_net = rtnl_link_get_net_capable(skb, net, tb, CAP_NET_ADMIN);
	अगर (IS_ERR(dest_net))
		वापस PTR_ERR(dest_net);

	अगर (tb[IFLA_LINK_NETNSID]) अणु
		पूर्णांक id = nla_get_s32(tb[IFLA_LINK_NETNSID]);

		link_net = get_net_ns_by_id(dest_net, id);
		अगर (!link_net) अणु
			NL_SET_ERR_MSG(extack, "Unknown network namespace id");
			err =  -EINVAL;
			जाओ out;
		पूर्ण
		err = -EPERM;
		अगर (!netlink_ns_capable(skb, link_net->user_ns, CAP_NET_ADMIN))
			जाओ out;
	पूर्ण अन्यथा अणु
		link_net = शून्य;
	पूर्ण

	dev = rtnl_create_link(link_net ? : dest_net, अगरname,
			       name_assign_type, ops, tb, extack);
	अगर (IS_ERR(dev)) अणु
		err = PTR_ERR(dev);
		जाओ out;
	पूर्ण

	dev->अगरindex = अगरm->अगरi_index;

	अगर (ops->newlink)
		err = ops->newlink(link_net ? : net, dev, tb, data, extack);
	अन्यथा
		err = रेजिस्टर_netdevice(dev);
	अगर (err < 0) अणु
		मुक्त_netdev(dev);
		जाओ out;
	पूर्ण

	err = rtnl_configure_link(dev, अगरm);
	अगर (err < 0)
		जाओ out_unरेजिस्टर;
	अगर (link_net) अणु
		err = dev_change_net_namespace(dev, dest_net, अगरname);
		अगर (err < 0)
			जाओ out_unरेजिस्टर;
	पूर्ण
	अगर (tb[IFLA_MASTER]) अणु
		err = करो_set_master(dev, nla_get_u32(tb[IFLA_MASTER]), extack);
		अगर (err)
			जाओ out_unरेजिस्टर;
	पूर्ण
out:
	अगर (link_net)
		put_net(link_net);
	put_net(dest_net);
	वापस err;
out_unरेजिस्टर:
	अगर (ops->newlink) अणु
		LIST_HEAD(list_समाप्त);

		ops->dellink(dev, &list_समाप्त);
		unरेजिस्टर_netdevice_many(&list_समाप्त);
	पूर्ण अन्यथा अणु
		unरेजिस्टर_netdevice(dev);
	पूर्ण
	जाओ out;
पूर्ण

अटल पूर्णांक rtnl_newlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr **attr;
	पूर्णांक ret;

	attr = kदो_स्मृति_array(RTNL_MAX_TYPE + 1, माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	ret = __rtnl_newlink(skb, nlh, attr, extack);
	kमुक्त(attr);
	वापस ret;
पूर्ण

अटल पूर्णांक rtnl_valid_getlink_req(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nlmsghdr *nlh,
				  काष्ठा nlattr **tb,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरinfomsg *अगरm;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for get link");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFLA_MAX,
					      अगरla_policy, extack);

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->__अगरi_pad || अगरm->अगरi_type || अगरm->अगरi_flags ||
	    अगरm->अगरi_change) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for get link request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*अगरm), tb, IFLA_MAX,
					    अगरla_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= IFLA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल IFLA_IFNAME:
		हाल IFLA_ALT_IFNAME:
		हाल IFLA_EXT_MASK:
		हाल IFLA_TARGET_NETNSID:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in get link request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_getlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net *tgt_net = net;
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा nlattr *tb[IFLA_MAX+1];
	काष्ठा net_device *dev = शून्य;
	काष्ठा sk_buff *nskb;
	पूर्णांक netnsid = -1;
	पूर्णांक err;
	u32 ext_filter_mask = 0;

	err = rtnl_valid_getlink_req(skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;

	err = rtnl_ensure_unique_netns(tb, extack, true);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_TARGET_NETNSID]) अणु
		netnsid = nla_get_s32(tb[IFLA_TARGET_NETNSID]);
		tgt_net = rtnl_get_net_ns_capable(NETLINK_CB(skb).sk, netnsid);
		अगर (IS_ERR(tgt_net))
			वापस PTR_ERR(tgt_net);
	पूर्ण

	अगर (tb[IFLA_EXT_MASK])
		ext_filter_mask = nla_get_u32(tb[IFLA_EXT_MASK]);

	err = -EINVAL;
	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_index > 0)
		dev = __dev_get_by_index(tgt_net, अगरm->अगरi_index);
	अन्यथा अगर (tb[IFLA_IFNAME] || tb[IFLA_ALT_IFNAME])
		dev = rtnl_dev_get(tgt_net, tb[IFLA_IFNAME],
				   tb[IFLA_ALT_IFNAME], शून्य);
	अन्यथा
		जाओ out;

	err = -ENODEV;
	अगर (dev == शून्य)
		जाओ out;

	err = -ENOBUFS;
	nskb = nlmsg_new(अगर_nlmsg_size(dev, ext_filter_mask), GFP_KERNEL);
	अगर (nskb == शून्य)
		जाओ out;

	err = rtnl_fill_अगरinfo(nskb, dev, net,
			       RTM_NEWLINK, NETLINK_CB(skb).portid,
			       nlh->nlmsg_seq, 0, 0, ext_filter_mask,
			       0, शून्य, 0, netnsid, GFP_KERNEL);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in अगर_nlmsg_size */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(nskb);
	पूर्ण अन्यथा
		err = rtnl_unicast(nskb, net, NETLINK_CB(skb).portid);
out:
	अगर (netnsid >= 0)
		put_net(tgt_net);

	वापस err;
पूर्ण

अटल पूर्णांक rtnl_alt_अगरname(पूर्णांक cmd, काष्ठा net_device *dev, काष्ठा nlattr *attr,
			   bool *changed, काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *alt_अगरname;
	पूर्णांक err;

	err = nla_validate(attr, attr->nla_len, IFLA_MAX, अगरla_policy, extack);
	अगर (err)
		वापस err;

	alt_अगरname = nla_strdup(attr, GFP_KERNEL);
	अगर (!alt_अगरname)
		वापस -ENOMEM;

	अगर (cmd == RTM_NEWLINKPROP) अणु
		err = netdev_name_node_alt_create(dev, alt_अगरname);
		अगर (!err)
			alt_अगरname = शून्य;
	पूर्ण अन्यथा अगर (cmd == RTM_DELLINKPROP) अणु
		err = netdev_name_node_alt_destroy(dev, alt_अगरname);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		err = -EINVAL;
	पूर्ण

	kमुक्त(alt_अगरname);
	अगर (!err)
		*changed = true;
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_linkprop(पूर्णांक cmd, काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[IFLA_MAX + 1];
	काष्ठा net_device *dev;
	काष्ठा अगरinfomsg *अगरm;
	bool changed = false;
	काष्ठा nlattr *attr;
	पूर्णांक err, rem;

	err = nlmsg_parse(nlh, माप(*अगरm), tb, IFLA_MAX, अगरla_policy, extack);
	अगर (err)
		वापस err;

	err = rtnl_ensure_unique_netns(tb, extack, true);
	अगर (err)
		वापस err;

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_index > 0)
		dev = __dev_get_by_index(net, अगरm->अगरi_index);
	अन्यथा अगर (tb[IFLA_IFNAME] || tb[IFLA_ALT_IFNAME])
		dev = rtnl_dev_get(net, tb[IFLA_IFNAME],
				   tb[IFLA_ALT_IFNAME], शून्य);
	अन्यथा
		वापस -EINVAL;

	अगर (!dev)
		वापस -ENODEV;

	अगर (!tb[IFLA_PROP_LIST])
		वापस 0;

	nla_क्रम_each_nested(attr, tb[IFLA_PROP_LIST], rem) अणु
		चयन (nla_type(attr)) अणु
		हाल IFLA_ALT_IFNAME:
			err = rtnl_alt_अगरname(cmd, dev, attr, &changed, extack);
			अगर (err)
				वापस err;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (changed)
		netdev_state_change(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_newlinkprop(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस rtnl_linkprop(RTM_NEWLINKPROP, skb, nlh, extack);
पूर्ण

अटल पूर्णांक rtnl_dellinkprop(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस rtnl_linkprop(RTM_DELLINKPROP, skb, nlh, extack);
पूर्ण

अटल u32 rtnl_calcit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	माप_प्रकार min_अगरinfo_dump_size = 0;
	काष्ठा nlattr *tb[IFLA_MAX+1];
	u32 ext_filter_mask = 0;
	काष्ठा net_device *dev;
	पूर्णांक hdrlen;

	/* Same kernel<->userspace पूर्णांकerface hack as in rtnl_dump_अगरinfo. */
	hdrlen = nlmsg_len(nlh) < माप(काष्ठा अगरinfomsg) ?
		 माप(काष्ठा rtgenmsg) : माप(काष्ठा अगरinfomsg);

	अगर (nlmsg_parse_deprecated(nlh, hdrlen, tb, IFLA_MAX, अगरla_policy, शून्य) >= 0) अणु
		अगर (tb[IFLA_EXT_MASK])
			ext_filter_mask = nla_get_u32(tb[IFLA_EXT_MASK]);
	पूर्ण

	अगर (!ext_filter_mask)
		वापस NLMSG_GOODSIZE;
	/*
	 * traverse the list of net devices and compute the minimum
	 * buffer size based upon the filter mask.
	 */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		min_अगरinfo_dump_size = max(min_अगरinfo_dump_size,
					   अगर_nlmsg_size(dev, ext_filter_mask));
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस nlmsg_total_size(min_अगरinfo_dump_size);
पूर्ण

अटल पूर्णांक rtnl_dump_all(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx;
	पूर्णांक s_idx = cb->family;
	पूर्णांक type = cb->nlh->nlmsg_type - RTM_BASE;
	पूर्णांक ret = 0;

	अगर (s_idx == 0)
		s_idx = 1;

	क्रम (idx = 1; idx <= RTNL_FAMILY_MAX; idx++) अणु
		काष्ठा rtnl_link __rcu **tab;
		काष्ठा rtnl_link *link;
		rtnl_dumpit_func dumpit;

		अगर (idx < s_idx || idx == PF_PACKET)
			जारी;

		अगर (type < 0 || type >= RTM_NR_MSGTYPES)
			जारी;

		tab = rcu_dereference_rtnl(rtnl_msg_handlers[idx]);
		अगर (!tab)
			जारी;

		link = rcu_dereference_rtnl(tab[type]);
		अगर (!link)
			जारी;

		dumpit = link->dumpit;
		अगर (!dumpit)
			जारी;

		अगर (idx > s_idx) अणु
			स_रखो(&cb->args[0], 0, माप(cb->args));
			cb->prev_seq = 0;
			cb->seq = 0;
		पूर्ण
		ret = dumpit(skb, cb);
		अगर (ret)
			अवरोध;
	पूर्ण
	cb->family = idx;

	वापस skb->len ? : ret;
पूर्ण

काष्ठा sk_buff *rपंचांगsg_अगरinfo_build_skb(पूर्णांक type, काष्ठा net_device *dev,
				       अचिन्हित पूर्णांक change,
				       u32 event, gfp_t flags, पूर्णांक *new_nsid,
				       पूर्णांक new_अगरindex)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;
	माप_प्रकार अगर_info_size;

	skb = nlmsg_new((अगर_info_size = अगर_nlmsg_size(dev, 0)), flags);
	अगर (skb == शून्य)
		जाओ errout;

	err = rtnl_fill_अगरinfo(skb, dev, dev_net(dev),
			       type, 0, 0, change, 0, 0, event,
			       new_nsid, new_अगरindex, -1, flags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in अगर_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	वापस skb;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_LINK, err);
	वापस शून्य;
पूर्ण

व्योम rपंचांगsg_अगरinfo_send(काष्ठा sk_buff *skb, काष्ठा net_device *dev, gfp_t flags)
अणु
	काष्ठा net *net = dev_net(dev);

	rtnl_notअगरy(skb, net, 0, RTNLGRP_LINK, शून्य, flags);
पूर्ण

अटल व्योम rपंचांगsg_अगरinfo_event(पूर्णांक type, काष्ठा net_device *dev,
			       अचिन्हित पूर्णांक change, u32 event,
			       gfp_t flags, पूर्णांक *new_nsid, पूर्णांक new_अगरindex)
अणु
	काष्ठा sk_buff *skb;

	अगर (dev->reg_state != NETREG_REGISTERED)
		वापस;

	skb = rपंचांगsg_अगरinfo_build_skb(type, dev, change, event, flags, new_nsid,
				     new_अगरindex);
	अगर (skb)
		rपंचांगsg_अगरinfo_send(skb, dev, flags);
पूर्ण

व्योम rपंचांगsg_अगरinfo(पूर्णांक type, काष्ठा net_device *dev, अचिन्हित पूर्णांक change,
		  gfp_t flags)
अणु
	rपंचांगsg_अगरinfo_event(type, dev, change, rtnl_get_event(0), flags,
			   शून्य, 0);
पूर्ण

व्योम rपंचांगsg_अगरinfo_newnet(पूर्णांक type, काष्ठा net_device *dev, अचिन्हित पूर्णांक change,
			 gfp_t flags, पूर्णांक *new_nsid, पूर्णांक new_अगरindex)
अणु
	rपंचांगsg_अगरinfo_event(type, dev, change, rtnl_get_event(0), flags,
			   new_nsid, new_अगरindex);
पूर्ण

अटल पूर्णांक nlmsg_populate_fdb_fill(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev,
				   u8 *addr, u16 vid, u32 pid, u32 seq,
				   पूर्णांक type, अचिन्हित पूर्णांक flags,
				   पूर्णांक nlflags, u16 ndm_state)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*ndm), nlflags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family  = AF_BRIDGE;
	ndm->ndm_pad1	 = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags	 = flags;
	ndm->ndm_type	 = 0;
	ndm->ndm_अगरindex = dev->अगरindex;
	ndm->ndm_state   = ndm_state;

	अगर (nla_put(skb, NDA_LLADDR, ETH_ALEN, addr))
		जाओ nla_put_failure;
	अगर (vid)
		अगर (nla_put(skb, NDA_VLAN, माप(u16), &vid))
			जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल अंतरभूत माप_प्रकार rtnl_fdb_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा ndmsg)) +
	       nla_total_size(ETH_ALEN) +	/* NDA_LLADDR */
	       nla_total_size(माप(u16)) +	/* NDA_VLAN */
	       0;
पूर्ण

अटल व्योम rtnl_fdb_notअगरy(काष्ठा net_device *dev, u8 *addr, u16 vid, पूर्णांक type,
			    u16 ndm_state)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(rtnl_fdb_nlmsg_size(), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = nlmsg_populate_fdb_fill(skb, dev, addr, vid,
				      0, 0, type, NTF_SELF, 0, ndm_state);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_NEIGH, शून्य, GFP_ATOMIC);
	वापस;
errout:
	rtnl_set_sk_err(net, RTNLGRP_NEIGH, err);
पूर्ण

/*
 * nकरो_dflt_fdb_add - शेष netdevice operation to add an FDB entry
 */
पूर्णांक nकरो_dflt_fdb_add(काष्ठा ndmsg *ndm,
		     काष्ठा nlattr *tb[],
		     काष्ठा net_device *dev,
		     स्थिर अचिन्हित अक्षर *addr, u16 vid,
		     u16 flags)
अणु
	पूर्णांक err = -EINVAL;

	/* If aging addresses are supported device will need to
	 * implement its own handler क्रम this.
	 */
	अगर (ndm->ndm_state && !(ndm->ndm_state & NUD_PERMANENT)) अणु
		pr_info("%s: FDB only supports static addresses\n", dev->name);
		वापस err;
	पूर्ण

	अगर (vid) अणु
		pr_info("%s: vlans aren't supported yet for dev_uc|mc_add()\n", dev->name);
		वापस err;
	पूर्ण

	अगर (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr))
		err = dev_uc_add_excl(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_add_excl(dev, addr);

	/* Only वापस duplicate errors अगर NLM_F_EXCL is set */
	अगर (err == -EEXIST && !(flags & NLM_F_EXCL))
		err = 0;

	वापस err;
पूर्ण
EXPORT_SYMBOL(nकरो_dflt_fdb_add);

अटल पूर्णांक fdb_vid_parse(काष्ठा nlattr *vlan_attr, u16 *p_vid,
			 काष्ठा netlink_ext_ack *extack)
अणु
	u16 vid = 0;

	अगर (vlan_attr) अणु
		अगर (nla_len(vlan_attr) != माप(u16)) अणु
			NL_SET_ERR_MSG(extack, "invalid vlan attribute size");
			वापस -EINVAL;
		पूर्ण

		vid = nla_get_u16(vlan_attr);

		अगर (!vid || vid >= VLAN_VID_MASK) अणु
			NL_SET_ERR_MSG(extack, "invalid vlan id");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	*p_vid = vid;
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_fdb_add(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ndmsg *ndm;
	काष्ठा nlattr *tb[NDA_MAX+1];
	काष्ठा net_device *dev;
	u8 *addr;
	u16 vid;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*ndm), tb, NDA_MAX, शून्य,
				     extack);
	अगर (err < 0)
		वापस err;

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_अगरindex == 0) अणु
		NL_SET_ERR_MSG(extack, "invalid ifindex");
		वापस -EINVAL;
	पूर्ण

	dev = __dev_get_by_index(net, ndm->ndm_अगरindex);
	अगर (dev == शून्य) अणु
		NL_SET_ERR_MSG(extack, "unknown ifindex");
		वापस -ENODEV;
	पूर्ण

	अगर (!tb[NDA_LLADDR] || nla_len(tb[NDA_LLADDR]) != ETH_ALEN) अणु
		NL_SET_ERR_MSG(extack, "invalid address");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->type != ARPHRD_ETHER) अणु
		NL_SET_ERR_MSG(extack, "FDB add only supported for Ethernet devices");
		वापस -EINVAL;
	पूर्ण

	addr = nla_data(tb[NDA_LLADDR]);

	err = fdb_vid_parse(tb[NDA_VLAN], &vid, extack);
	अगर (err)
		वापस err;

	err = -EOPNOTSUPP;

	/* Support fdb on master device the net/bridge शेष हाल */
	अगर ((!ndm->ndm_flags || ndm->ndm_flags & NTF_MASTER) &&
	    netअगर_is_bridge_port(dev)) अणु
		काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);
		स्थिर काष्ठा net_device_ops *ops = br_dev->netdev_ops;

		err = ops->nकरो_fdb_add(ndm, tb, dev, addr, vid,
				       nlh->nlmsg_flags, extack);
		अगर (err)
			जाओ out;
		अन्यथा
			ndm->ndm_flags &= ~NTF_MASTER;
	पूर्ण

	/* Embedded bridge, macvlan, and any other device support */
	अगर ((ndm->ndm_flags & NTF_SELF)) अणु
		अगर (dev->netdev_ops->nकरो_fdb_add)
			err = dev->netdev_ops->nकरो_fdb_add(ndm, tb, dev, addr,
							   vid,
							   nlh->nlmsg_flags,
							   extack);
		अन्यथा
			err = nकरो_dflt_fdb_add(ndm, tb, dev, addr, vid,
					       nlh->nlmsg_flags);

		अगर (!err) अणु
			rtnl_fdb_notअगरy(dev, addr, vid, RTM_NEWNEIGH,
					ndm->ndm_state);
			ndm->ndm_flags &= ~NTF_SELF;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * nकरो_dflt_fdb_del - शेष netdevice operation to delete an FDB entry
 */
पूर्णांक nकरो_dflt_fdb_del(काष्ठा ndmsg *ndm,
		     काष्ठा nlattr *tb[],
		     काष्ठा net_device *dev,
		     स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	पूर्णांक err = -EINVAL;

	/* If aging addresses are supported device will need to
	 * implement its own handler क्रम this.
	 */
	अगर (!(ndm->ndm_state & NUD_PERMANENT)) अणु
		pr_info("%s: FDB only supports static addresses\n", dev->name);
		वापस err;
	पूर्ण

	अगर (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr))
		err = dev_uc_del(dev, addr);
	अन्यथा अगर (is_multicast_ether_addr(addr))
		err = dev_mc_del(dev, addr);

	वापस err;
पूर्ण
EXPORT_SYMBOL(nकरो_dflt_fdb_del);

अटल पूर्णांक rtnl_fdb_del(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ndmsg *ndm;
	काष्ठा nlattr *tb[NDA_MAX+1];
	काष्ठा net_device *dev;
	__u8 *addr;
	पूर्णांक err;
	u16 vid;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	err = nlmsg_parse_deprecated(nlh, माप(*ndm), tb, NDA_MAX, शून्य,
				     extack);
	अगर (err < 0)
		वापस err;

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_अगरindex == 0) अणु
		NL_SET_ERR_MSG(extack, "invalid ifindex");
		वापस -EINVAL;
	पूर्ण

	dev = __dev_get_by_index(net, ndm->ndm_अगरindex);
	अगर (dev == शून्य) अणु
		NL_SET_ERR_MSG(extack, "unknown ifindex");
		वापस -ENODEV;
	पूर्ण

	अगर (!tb[NDA_LLADDR] || nla_len(tb[NDA_LLADDR]) != ETH_ALEN) अणु
		NL_SET_ERR_MSG(extack, "invalid address");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->type != ARPHRD_ETHER) अणु
		NL_SET_ERR_MSG(extack, "FDB delete only supported for Ethernet devices");
		वापस -EINVAL;
	पूर्ण

	addr = nla_data(tb[NDA_LLADDR]);

	err = fdb_vid_parse(tb[NDA_VLAN], &vid, extack);
	अगर (err)
		वापस err;

	err = -EOPNOTSUPP;

	/* Support fdb on master device the net/bridge शेष हाल */
	अगर ((!ndm->ndm_flags || ndm->ndm_flags & NTF_MASTER) &&
	    netअगर_is_bridge_port(dev)) अणु
		काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);
		स्थिर काष्ठा net_device_ops *ops = br_dev->netdev_ops;

		अगर (ops->nकरो_fdb_del)
			err = ops->nकरो_fdb_del(ndm, tb, dev, addr, vid);

		अगर (err)
			जाओ out;
		अन्यथा
			ndm->ndm_flags &= ~NTF_MASTER;
	पूर्ण

	/* Embedded bridge, macvlan, and any other device support */
	अगर (ndm->ndm_flags & NTF_SELF) अणु
		अगर (dev->netdev_ops->nकरो_fdb_del)
			err = dev->netdev_ops->nकरो_fdb_del(ndm, tb, dev, addr,
							   vid);
		अन्यथा
			err = nकरो_dflt_fdb_del(ndm, tb, dev, addr, vid);

		अगर (!err) अणु
			rtnl_fdb_notअगरy(dev, addr, vid, RTM_DELNEIGH,
					ndm->ndm_state);
			ndm->ndm_flags &= ~NTF_SELF;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक nlmsg_populate_fdb(काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb,
			      काष्ठा net_device *dev,
			      पूर्णांक *idx,
			      काष्ठा netdev_hw_addr_list *list)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक err;
	u32 portid, seq;

	portid = NETLINK_CB(cb->skb).portid;
	seq = cb->nlh->nlmsg_seq;

	list_क्रम_each_entry(ha, &list->list, list) अणु
		अगर (*idx < cb->args[2])
			जाओ skip;

		err = nlmsg_populate_fdb_fill(skb, dev, ha->addr, 0,
					      portid, seq,
					      RTM_NEWNEIGH, NTF_SELF,
					      NLM_F_MULTI, NUD_PERMANENT);
		अगर (err < 0)
			वापस err;
skip:
		*idx += 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nकरो_dflt_fdb_dump - शेष netdevice operation to dump an FDB table.
 * @skb: socket buffer to store message in
 * @cb: netlink callback
 * @dev: netdevice
 * @filter_dev: ignored
 * @idx: the number of FDB table entries dumped is added to *@idx
 *
 * Default netdevice operation to dump the existing unicast address list.
 * Returns number of addresses from list put in skb.
 */
पूर्णांक nकरो_dflt_fdb_dump(काष्ठा sk_buff *skb,
		      काष्ठा netlink_callback *cb,
		      काष्ठा net_device *dev,
		      काष्ठा net_device *filter_dev,
		      पूर्णांक *idx)
अणु
	पूर्णांक err;

	अगर (dev->type != ARPHRD_ETHER)
		वापस -EINVAL;

	netअगर_addr_lock_bh(dev);
	err = nlmsg_populate_fdb(skb, cb, dev, idx, &dev->uc);
	अगर (err)
		जाओ out;
	err = nlmsg_populate_fdb(skb, cb, dev, idx, &dev->mc);
out:
	netअगर_addr_unlock_bh(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(nकरो_dflt_fdb_dump);

अटल पूर्णांक valid_fdb_dump_strict(स्थिर काष्ठा nlmsghdr *nlh,
				 पूर्णांक *br_idx, पूर्णांक *brport_idx,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[NDA_MAX + 1];
	काष्ठा ndmsg *ndm;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ndm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for fdb dump request");
		वापस -EINVAL;
	पूर्ण

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_flags || ndm->ndm_type) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for fdb dump request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा ndmsg), tb,
					    NDA_MAX, शून्य, extack);
	अगर (err < 0)
		वापस err;

	*brport_idx = ndm->ndm_अगरindex;
	क्रम (i = 0; i <= NDA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NDA_IFINDEX:
			अगर (nla_len(tb[i]) != माप(u32)) अणु
				NL_SET_ERR_MSG(extack, "Invalid IFINDEX attribute in fdb dump request");
				वापस -EINVAL;
			पूर्ण
			*brport_idx = nla_get_u32(tb[NDA_IFINDEX]);
			अवरोध;
		हाल NDA_MASTER:
			अगर (nla_len(tb[i]) != माप(u32)) अणु
				NL_SET_ERR_MSG(extack, "Invalid MASTER attribute in fdb dump request");
				वापस -EINVAL;
			पूर्ण
			*br_idx = nla_get_u32(tb[NDA_MASTER]);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in fdb dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक valid_fdb_dump_legacy(स्थिर काष्ठा nlmsghdr *nlh,
				 पूर्णांक *br_idx, पूर्णांक *brport_idx,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_MAX+1];
	पूर्णांक err;

	/* A hack to preserve kernel<->userspace पूर्णांकerface.
	 * Beक्रमe Linux v4.12 this code accepted ndmsg since iproute2 v3.3.0.
	 * However, ndmsg is लघुer than अगरinfomsg thus nlmsg_parse() bails.
	 * So, check क्रम ndmsg with an optional u32 attribute (not used here).
	 * Fortunately these sizes करोn't conflict with the size of अगरinfomsg
	 * with an optional attribute.
	 */
	अगर (nlmsg_len(nlh) != माप(काष्ठा ndmsg) &&
	    (nlmsg_len(nlh) != माप(काष्ठा ndmsg) +
	     nla_attr_size(माप(u32)))) अणु
		काष्ठा अगरinfomsg *अगरm;

		err = nlmsg_parse_deprecated(nlh, माप(काष्ठा अगरinfomsg),
					     tb, IFLA_MAX, अगरla_policy,
					     extack);
		अगर (err < 0) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (err == 0) अणु
			अगर (tb[IFLA_MASTER])
				*br_idx = nla_get_u32(tb[IFLA_MASTER]);
		पूर्ण

		अगरm = nlmsg_data(nlh);
		*brport_idx = अगरm->अगरi_index;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net_device *dev;
	काष्ठा net_device *br_dev = शून्य;
	स्थिर काष्ठा net_device_ops *ops = शून्य;
	स्थिर काष्ठा net_device_ops *cops = शून्य;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा hlist_head *head;
	पूर्णांक brport_idx = 0;
	पूर्णांक br_idx = 0;
	पूर्णांक h, s_h;
	पूर्णांक idx = 0, s_idx;
	पूर्णांक err = 0;
	पूर्णांक fidx = 0;

	अगर (cb->strict_check)
		err = valid_fdb_dump_strict(cb->nlh, &br_idx, &brport_idx,
					    cb->extack);
	अन्यथा
		err = valid_fdb_dump_legacy(cb->nlh, &br_idx, &brport_idx,
					    cb->extack);
	अगर (err < 0)
		वापस err;

	अगर (br_idx) अणु
		br_dev = __dev_get_by_index(net, br_idx);
		अगर (!br_dev)
			वापस -ENODEV;

		ops = br_dev->netdev_ops;
	पूर्ण

	s_h = cb->args[0];
	s_idx = cb->args[1];

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		hlist_क्रम_each_entry(dev, head, index_hlist) अणु

			अगर (brport_idx && (dev->अगरindex != brport_idx))
				जारी;

			अगर (!br_idx) अणु /* user did not specअगरy a specअगरic bridge */
				अगर (netअगर_is_bridge_port(dev)) अणु
					br_dev = netdev_master_upper_dev_get(dev);
					cops = br_dev->netdev_ops;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (dev != br_dev &&
				    !netअगर_is_bridge_port(dev))
					जारी;

				अगर (br_dev != netdev_master_upper_dev_get(dev) &&
				    !(dev->priv_flags & IFF_EBRIDGE))
					जारी;
				cops = ops;
			पूर्ण

			अगर (idx < s_idx)
				जाओ cont;

			अगर (netअगर_is_bridge_port(dev)) अणु
				अगर (cops && cops->nकरो_fdb_dump) अणु
					err = cops->nकरो_fdb_dump(skb, cb,
								br_dev, dev,
								&fidx);
					अगर (err == -EMSGSIZE)
						जाओ out;
				पूर्ण
			पूर्ण

			अगर (dev->netdev_ops->nकरो_fdb_dump)
				err = dev->netdev_ops->nकरो_fdb_dump(skb, cb,
								    dev, शून्य,
								    &fidx);
			अन्यथा
				err = nकरो_dflt_fdb_dump(skb, cb, dev, शून्य,
							&fidx);
			अगर (err == -EMSGSIZE)
				जाओ out;

			cops = शून्य;

			/* reset fdb offset to 0 क्रम rest of the पूर्णांकerfaces */
			cb->args[2] = 0;
			fidx = 0;
cont:
			idx++;
		पूर्ण
	पूर्ण

out:
	cb->args[0] = h;
	cb->args[1] = idx;
	cb->args[2] = fidx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक valid_fdb_get_strict(स्थिर काष्ठा nlmsghdr *nlh,
				काष्ठा nlattr **tb, u8 *ndm_flags,
				पूर्णांक *br_idx, पूर्णांक *brport_idx, u8 **addr,
				u16 *vid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ndmsg *ndm;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ndm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for fdb get request");
		वापस -EINVAL;
	पूर्ण

	ndm = nlmsg_data(nlh);
	अगर (ndm->ndm_pad1  || ndm->ndm_pad2  || ndm->ndm_state ||
	    ndm->ndm_type) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for fdb get request");
		वापस -EINVAL;
	पूर्ण

	अगर (ndm->ndm_flags & ~(NTF_MASTER | NTF_SELF)) अणु
		NL_SET_ERR_MSG(extack, "Invalid flags in header for fdb get request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा ndmsg), tb,
					    NDA_MAX, nda_policy, extack);
	अगर (err < 0)
		वापस err;

	*ndm_flags = ndm->ndm_flags;
	*brport_idx = ndm->ndm_अगरindex;
	क्रम (i = 0; i <= NDA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NDA_MASTER:
			*br_idx = nla_get_u32(tb[i]);
			अवरोध;
		हाल NDA_LLADDR:
			अगर (nla_len(tb[i]) != ETH_ALEN) अणु
				NL_SET_ERR_MSG(extack, "Invalid address in fdb get request");
				वापस -EINVAL;
			पूर्ण
			*addr = nla_data(tb[i]);
			अवरोध;
		हाल NDA_VLAN:
			err = fdb_vid_parse(tb[i], vid, extack);
			अगर (err)
				वापस err;
			अवरोध;
		हाल NDA_VNI:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in fdb get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_fdb_get(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = शून्य, *br_dev = शून्य;
	स्थिर काष्ठा net_device_ops *ops = शून्य;
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[NDA_MAX + 1];
	काष्ठा sk_buff *skb;
	पूर्णांक brport_idx = 0;
	u8 ndm_flags = 0;
	पूर्णांक br_idx = 0;
	u8 *addr = शून्य;
	u16 vid = 0;
	पूर्णांक err;

	err = valid_fdb_get_strict(nlh, tb, &ndm_flags, &br_idx,
				   &brport_idx, &addr, &vid, extack);
	अगर (err < 0)
		वापस err;

	अगर (!addr) अणु
		NL_SET_ERR_MSG(extack, "Missing lookup address for fdb get request");
		वापस -EINVAL;
	पूर्ण

	अगर (brport_idx) अणु
		dev = __dev_get_by_index(net, brport_idx);
		अगर (!dev) अणु
			NL_SET_ERR_MSG(extack, "Unknown device ifindex");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (br_idx) अणु
		अगर (dev) अणु
			NL_SET_ERR_MSG(extack, "Master and device are mutually exclusive");
			वापस -EINVAL;
		पूर्ण

		br_dev = __dev_get_by_index(net, br_idx);
		अगर (!br_dev) अणु
			NL_SET_ERR_MSG(extack, "Invalid master ifindex");
			वापस -EINVAL;
		पूर्ण
		ops = br_dev->netdev_ops;
	पूर्ण

	अगर (dev) अणु
		अगर (!ndm_flags || (ndm_flags & NTF_MASTER)) अणु
			अगर (!netअगर_is_bridge_port(dev)) अणु
				NL_SET_ERR_MSG(extack, "Device is not a bridge port");
				वापस -EINVAL;
			पूर्ण
			br_dev = netdev_master_upper_dev_get(dev);
			अगर (!br_dev) अणु
				NL_SET_ERR_MSG(extack, "Master of device not found");
				वापस -EINVAL;
			पूर्ण
			ops = br_dev->netdev_ops;
		पूर्ण अन्यथा अणु
			अगर (!(ndm_flags & NTF_SELF)) अणु
				NL_SET_ERR_MSG(extack, "Missing NTF_SELF");
				वापस -EINVAL;
			पूर्ण
			ops = dev->netdev_ops;
		पूर्ण
	पूर्ण

	अगर (!br_dev && !dev) अणु
		NL_SET_ERR_MSG(extack, "No device specified");
		वापस -ENODEV;
	पूर्ण

	अगर (!ops || !ops->nकरो_fdb_get) अणु
		NL_SET_ERR_MSG(extack, "Fdb get operation not supported by device");
		वापस -EOPNOTSUPP;
	पूर्ण

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (br_dev)
		dev = br_dev;
	err = ops->nकरो_fdb_get(skb, tb, dev, addr, vid,
			       NETLINK_CB(in_skb).portid,
			       nlh->nlmsg_seq, extack);
	अगर (err)
		जाओ out;

	वापस rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
out:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक brport_nla_put_flag(काष्ठा sk_buff *skb, u32 flags, u32 mask,
			       अचिन्हित पूर्णांक attrnum, अचिन्हित पूर्णांक flag)
अणु
	अगर (mask & flag)
		वापस nla_put_u8(skb, attrnum, !!(flags & flag));
	वापस 0;
पूर्ण

पूर्णांक nकरो_dflt_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
			    काष्ठा net_device *dev, u16 mode,
			    u32 flags, u32 mask, पूर्णांक nlflags,
			    u32 filter_mask,
			    पूर्णांक (*vlan_fill)(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     u32 filter_mask))
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा nlattr *br_afspec;
	काष्ठा nlattr *protinfo;
	u8 operstate = netअगर_running(dev) ? dev->operstate : IF_OPER_DOWN;
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);
	पूर्णांक err = 0;

	nlh = nlmsg_put(skb, pid, seq, RTM_NEWLINK, माप(*अगरm), nlflags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरi_family = AF_BRIDGE;
	अगरm->__अगरi_pad = 0;
	अगरm->अगरi_type = dev->type;
	अगरm->अगरi_index = dev->अगरindex;
	अगरm->अगरi_flags = dev_get_flags(dev);
	अगरm->अगरi_change = 0;


	अगर (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    nla_put_u8(skb, IFLA_OPERSTATE, operstate) ||
	    (br_dev &&
	     nla_put_u32(skb, IFLA_MASTER, br_dev->अगरindex)) ||
	    (dev->addr_len &&
	     nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr)) ||
	    (dev->अगरindex != dev_get_अगरlink(dev) &&
	     nla_put_u32(skb, IFLA_LINK, dev_get_अगरlink(dev))))
		जाओ nla_put_failure;

	br_afspec = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
	अगर (!br_afspec)
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_BRIDGE_FLAGS, BRIDGE_FLAGS_SELF)) अणु
		nla_nest_cancel(skb, br_afspec);
		जाओ nla_put_failure;
	पूर्ण

	अगर (mode != BRIDGE_MODE_UNDEF) अणु
		अगर (nla_put_u16(skb, IFLA_BRIDGE_MODE, mode)) अणु
			nla_nest_cancel(skb, br_afspec);
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण
	अगर (vlan_fill) अणु
		err = vlan_fill(skb, dev, filter_mask);
		अगर (err) अणु
			nla_nest_cancel(skb, br_afspec);
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण
	nla_nest_end(skb, br_afspec);

	protinfo = nla_nest_start(skb, IFLA_PROTINFO);
	अगर (!protinfo)
		जाओ nla_put_failure;

	अगर (brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_MODE, BR_HAIRPIN_MODE) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_GUARD, BR_BPDU_GUARD) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_FAST_LEAVE,
				BR_MULTICAST_FAST_LEAVE) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_PROTECT, BR_ROOT_BLOCK) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_LEARNING, BR_LEARNING) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_LEARNING_SYNC, BR_LEARNING_SYNC) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_UNICAST_FLOOD, BR_FLOOD) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_PROXYARP, BR_PROXYARP) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_MCAST_FLOOD, BR_MCAST_FLOOD) ||
	    brport_nla_put_flag(skb, flags, mask,
				IFLA_BRPORT_BCAST_FLOOD, BR_BCAST_FLOOD)) अणु
		nla_nest_cancel(skb, protinfo);
		जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(skb, protinfo);

	nlmsg_end(skb, nlh);
	वापस 0;
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस err ? err : -EMSGSIZE;
पूर्ण
EXPORT_SYMBOL_GPL(nकरो_dflt_bridge_getlink);

अटल पूर्णांक valid_bridge_getlink_req(स्थिर काष्ठा nlmsghdr *nlh,
				    bool strict_check, u32 *filter_mask,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFLA_MAX+1];
	पूर्णांक err, i;

	अगर (strict_check) अणु
		काष्ठा अगरinfomsg *अगरm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
			NL_SET_ERR_MSG(extack, "Invalid header for bridge link dump");
			वापस -EINVAL;
		पूर्ण

		अगरm = nlmsg_data(nlh);
		अगर (अगरm->__अगरi_pad || अगरm->अगरi_type || अगरm->अगरi_flags ||
		    अगरm->अगरi_change || अगरm->अगरi_index) अणु
			NL_SET_ERR_MSG(extack, "Invalid values in header for bridge link dump request");
			वापस -EINVAL;
		पूर्ण

		err = nlmsg_parse_deprecated_strict(nlh,
						    माप(काष्ठा अगरinfomsg),
						    tb, IFLA_MAX, अगरla_policy,
						    extack);
	पूर्ण अन्यथा अणु
		err = nlmsg_parse_deprecated(nlh, माप(काष्ठा अगरinfomsg),
					     tb, IFLA_MAX, अगरla_policy,
					     extack);
	पूर्ण
	अगर (err < 0)
		वापस err;

	/* new attributes should only be added with strict checking */
	क्रम (i = 0; i <= IFLA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल IFLA_EXT_MASK:
			*filter_mask = nla_get_u32(tb[i]);
			अवरोध;
		शेष:
			अगर (strict_check) अणु
				NL_SET_ERR_MSG(extack, "Unsupported attribute in bridge link dump request");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_bridge_getlink(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *dev;
	पूर्णांक idx = 0;
	u32 portid = NETLINK_CB(cb->skb).portid;
	u32 seq = nlh->nlmsg_seq;
	u32 filter_mask = 0;
	पूर्णांक err;

	err = valid_bridge_getlink_req(nlh, cb->strict_check, &filter_mask,
				       cb->extack);
	अगर (err < 0 && cb->strict_check)
		वापस err;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
		काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);

		अगर (br_dev && br_dev->netdev_ops->nकरो_bridge_getlink) अणु
			अगर (idx >= cb->args[0]) अणु
				err = br_dev->netdev_ops->nकरो_bridge_getlink(
						skb, portid, seq, dev,
						filter_mask, NLM_F_MULTI);
				अगर (err < 0 && err != -EOPNOTSUPP) अणु
					अगर (likely(skb->len))
						अवरोध;

					जाओ out_err;
				पूर्ण
			पूर्ण
			idx++;
		पूर्ण

		अगर (ops->nकरो_bridge_getlink) अणु
			अगर (idx >= cb->args[0]) अणु
				err = ops->nकरो_bridge_getlink(skb, portid,
							      seq, dev,
							      filter_mask,
							      NLM_F_MULTI);
				अगर (err < 0 && err != -EOPNOTSUPP) अणु
					अगर (likely(skb->len))
						अवरोध;

					जाओ out_err;
				पूर्ण
			पूर्ण
			idx++;
		पूर्ण
	पूर्ण
	err = skb->len;
out_err:
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;

	वापस err;
पूर्ण

अटल अंतरभूत माप_प्रकार bridge_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरinfomsg))
		+ nla_total_size(IFNAMSIZ)	/* IFLA_IFNAME */
		+ nla_total_size(MAX_ADDR_LEN)	/* IFLA_ADDRESS */
		+ nla_total_size(माप(u32))	/* IFLA_MASTER */
		+ nla_total_size(माप(u32))	/* IFLA_MTU */
		+ nla_total_size(माप(u32))	/* IFLA_LINK */
		+ nla_total_size(माप(u32))	/* IFLA_OPERSTATE */
		+ nla_total_size(माप(u8))	/* IFLA_PROTINFO */
		+ nla_total_size(माप(काष्ठा nlattr))	/* IFLA_AF_SPEC */
		+ nla_total_size(माप(u16))	/* IFLA_BRIDGE_FLAGS */
		+ nla_total_size(माप(u16));	/* IFLA_BRIDGE_MODE */
पूर्ण

अटल पूर्णांक rtnl_bridge_notअगरy(काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!dev->netdev_ops->nकरो_bridge_getlink)
		वापस 0;

	skb = nlmsg_new(bridge_nlmsg_size(), GFP_ATOMIC);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	err = dev->netdev_ops->nकरो_bridge_getlink(skb, 0, 0, dev, 0, 0);
	अगर (err < 0)
		जाओ errout;

	/* Notअगरication info is only filled क्रम bridge ports, not the bridge
	 * device itself. Thereक्रमe, a zero notअगरication length is valid and
	 * should not result in an error.
	 */
	अगर (!skb->len)
		जाओ errout;

	rtnl_notअगरy(skb, net, 0, RTNLGRP_LINK, शून्य, GFP_ATOMIC);
	वापस 0;
errout:
	WARN_ON(err == -EMSGSIZE);
	kमुक्त_skb(skb);
	अगर (err)
		rtnl_set_sk_err(net, RTNLGRP_LINK, err);
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_bridge_setlink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा net_device *dev;
	काष्ठा nlattr *br_spec, *attr = शून्य;
	पूर्णांक rem, err = -EOPNOTSUPP;
	u16 flags = 0;
	bool have_flags = false;

	अगर (nlmsg_len(nlh) < माप(*अगरm))
		वापस -EINVAL;

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_family != AF_BRIDGE)
		वापस -EPFNOSUPPORT;

	dev = __dev_get_by_index(net, अगरm->अगरi_index);
	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack, "unknown ifindex");
		वापस -ENODEV;
	पूर्ण

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (br_spec) अणु
		nla_क्रम_each_nested(attr, br_spec, rem) अणु
			अगर (nla_type(attr) == IFLA_BRIDGE_FLAGS) अणु
				अगर (nla_len(attr) < माप(flags))
					वापस -EINVAL;

				have_flags = true;
				flags = nla_get_u16(attr);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!flags || (flags & BRIDGE_FLAGS_MASTER)) अणु
		काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);

		अगर (!br_dev || !br_dev->netdev_ops->nकरो_bridge_setlink) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = br_dev->netdev_ops->nकरो_bridge_setlink(dev, nlh, flags,
							     extack);
		अगर (err)
			जाओ out;

		flags &= ~BRIDGE_FLAGS_MASTER;
	पूर्ण

	अगर ((flags & BRIDGE_FLAGS_SELF)) अणु
		अगर (!dev->netdev_ops->nकरो_bridge_setlink)
			err = -EOPNOTSUPP;
		अन्यथा
			err = dev->netdev_ops->nकरो_bridge_setlink(dev, nlh,
								  flags,
								  extack);
		अगर (!err) अणु
			flags &= ~BRIDGE_FLAGS_SELF;

			/* Generate event to notअगरy upper layer of bridge
			 * change
			 */
			err = rtnl_bridge_notअगरy(dev);
		पूर्ण
	पूर्ण

	अगर (have_flags)
		स_नकल(nla_data(attr), &flags, माप(flags));
out:
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_bridge_dellink(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरinfomsg *अगरm;
	काष्ठा net_device *dev;
	काष्ठा nlattr *br_spec, *attr = शून्य;
	पूर्णांक rem, err = -EOPNOTSUPP;
	u16 flags = 0;
	bool have_flags = false;

	अगर (nlmsg_len(nlh) < माप(*अगरm))
		वापस -EINVAL;

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरi_family != AF_BRIDGE)
		वापस -EPFNOSUPPORT;

	dev = __dev_get_by_index(net, अगरm->अगरi_index);
	अगर (!dev) अणु
		NL_SET_ERR_MSG(extack, "unknown ifindex");
		वापस -ENODEV;
	पूर्ण

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (br_spec) अणु
		nla_क्रम_each_nested(attr, br_spec, rem) अणु
			अगर (nla_type(attr) == IFLA_BRIDGE_FLAGS) अणु
				अगर (nla_len(attr) < माप(flags))
					वापस -EINVAL;

				have_flags = true;
				flags = nla_get_u16(attr);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!flags || (flags & BRIDGE_FLAGS_MASTER)) अणु
		काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);

		अगर (!br_dev || !br_dev->netdev_ops->nकरो_bridge_dellink) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = br_dev->netdev_ops->nकरो_bridge_dellink(dev, nlh, flags);
		अगर (err)
			जाओ out;

		flags &= ~BRIDGE_FLAGS_MASTER;
	पूर्ण

	अगर ((flags & BRIDGE_FLAGS_SELF)) अणु
		अगर (!dev->netdev_ops->nकरो_bridge_dellink)
			err = -EOPNOTSUPP;
		अन्यथा
			err = dev->netdev_ops->nकरो_bridge_dellink(dev, nlh,
								  flags);

		अगर (!err) अणु
			flags &= ~BRIDGE_FLAGS_SELF;

			/* Generate event to notअगरy upper layer of bridge
			 * change
			 */
			err = rtnl_bridge_notअगरy(dev);
		पूर्ण
	पूर्ण

	अगर (have_flags)
		स_नकल(nla_data(attr), &flags, माप(flags));
out:
	वापस err;
पूर्ण

अटल bool stats_attr_valid(अचिन्हित पूर्णांक mask, पूर्णांक attrid, पूर्णांक idxattr)
अणु
	वापस (mask & IFLA_STATS_FILTER_BIT(attrid)) &&
	       (!idxattr || idxattr == attrid);
पूर्ण

#घोषणा IFLA_OFFLOAD_XSTATS_FIRST (IFLA_OFFLOAD_XSTATS_UNSPEC + 1)
अटल पूर्णांक rtnl_get_offload_stats_attr_size(पूर्णांक attr_id)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस माप(काष्ठा rtnl_link_stats64);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_get_offload_stats(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				  पूर्णांक *prividx)
अणु
	काष्ठा nlattr *attr = शून्य;
	पूर्णांक attr_id, size;
	व्योम *attr_data;
	पूर्णांक err;

	अगर (!(dev->netdev_ops && dev->netdev_ops->nकरो_has_offload_stats &&
	      dev->netdev_ops->nकरो_get_offload_stats))
		वापस -ENODATA;

	क्रम (attr_id = IFLA_OFFLOAD_XSTATS_FIRST;
	     attr_id <= IFLA_OFFLOAD_XSTATS_MAX; attr_id++) अणु
		अगर (attr_id < *prividx)
			जारी;

		size = rtnl_get_offload_stats_attr_size(attr_id);
		अगर (!size)
			जारी;

		अगर (!dev->netdev_ops->nकरो_has_offload_stats(dev, attr_id))
			जारी;

		attr = nla_reserve_64bit(skb, attr_id, size,
					 IFLA_OFFLOAD_XSTATS_UNSPEC);
		अगर (!attr)
			जाओ nla_put_failure;

		attr_data = nla_data(attr);
		स_रखो(attr_data, 0, size);
		err = dev->netdev_ops->nकरो_get_offload_stats(attr_id, dev,
							     attr_data);
		अगर (err)
			जाओ get_offload_stats_failure;
	पूर्ण

	अगर (!attr)
		वापस -ENODATA;

	*prividx = 0;
	वापस 0;

nla_put_failure:
	err = -EMSGSIZE;
get_offload_stats_failure:
	*prividx = attr_id;
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_get_offload_stats_size(स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक nla_size = 0;
	पूर्णांक attr_id;
	पूर्णांक size;

	अगर (!(dev->netdev_ops && dev->netdev_ops->nकरो_has_offload_stats &&
	      dev->netdev_ops->nकरो_get_offload_stats))
		वापस 0;

	क्रम (attr_id = IFLA_OFFLOAD_XSTATS_FIRST;
	     attr_id <= IFLA_OFFLOAD_XSTATS_MAX; attr_id++) अणु
		अगर (!dev->netdev_ops->nकरो_has_offload_stats(dev, attr_id))
			जारी;
		size = rtnl_get_offload_stats_attr_size(attr_id);
		nla_size += nla_total_size_64bit(size);
	पूर्ण

	अगर (nla_size != 0)
		nla_size += nla_total_size(0);

	वापस nla_size;
पूर्ण

अटल पूर्णांक rtnl_fill_statsinfo(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       पूर्णांक type, u32 pid, u32 seq, u32 change,
			       अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक filter_mask,
			       पूर्णांक *idxattr, पूर्णांक *prividx)
अणु
	काष्ठा अगर_stats_msg *अगरsm;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlattr *attr;
	पूर्णांक s_prividx = *prividx;
	पूर्णांक err;

	ASSERT_RTNL();

	nlh = nlmsg_put(skb, pid, seq, type, माप(*अगरsm), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगरsm = nlmsg_data(nlh);
	अगरsm->family = PF_UNSPEC;
	अगरsm->pad1 = 0;
	अगरsm->pad2 = 0;
	अगरsm->अगरindex = dev->अगरindex;
	अगरsm->filter_mask = filter_mask;

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_64, *idxattr)) अणु
		काष्ठा rtnl_link_stats64 *sp;

		attr = nla_reserve_64bit(skb, IFLA_STATS_LINK_64,
					 माप(काष्ठा rtnl_link_stats64),
					 IFLA_STATS_UNSPEC);
		अगर (!attr)
			जाओ nla_put_failure;

		sp = nla_data(attr);
		dev_get_stats(dev, sp);
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_XSTATS, *idxattr)) अणु
		स्थिर काष्ठा rtnl_link_ops *ops = dev->rtnl_link_ops;

		अगर (ops && ops->fill_linkxstats) अणु
			*idxattr = IFLA_STATS_LINK_XSTATS;
			attr = nla_nest_start_noflag(skb,
						     IFLA_STATS_LINK_XSTATS);
			अगर (!attr)
				जाओ nla_put_failure;

			err = ops->fill_linkxstats(skb, dev, prividx, *idxattr);
			nla_nest_end(skb, attr);
			अगर (err)
				जाओ nla_put_failure;
			*idxattr = 0;
		पूर्ण
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_XSTATS_SLAVE,
			     *idxattr)) अणु
		स्थिर काष्ठा rtnl_link_ops *ops = शून्य;
		स्थिर काष्ठा net_device *master;

		master = netdev_master_upper_dev_get(dev);
		अगर (master)
			ops = master->rtnl_link_ops;
		अगर (ops && ops->fill_linkxstats) अणु
			*idxattr = IFLA_STATS_LINK_XSTATS_SLAVE;
			attr = nla_nest_start_noflag(skb,
						     IFLA_STATS_LINK_XSTATS_SLAVE);
			अगर (!attr)
				जाओ nla_put_failure;

			err = ops->fill_linkxstats(skb, dev, prividx, *idxattr);
			nla_nest_end(skb, attr);
			अगर (err)
				जाओ nla_put_failure;
			*idxattr = 0;
		पूर्ण
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_OFFLOAD_XSTATS,
			     *idxattr)) अणु
		*idxattr = IFLA_STATS_LINK_OFFLOAD_XSTATS;
		attr = nla_nest_start_noflag(skb,
					     IFLA_STATS_LINK_OFFLOAD_XSTATS);
		अगर (!attr)
			जाओ nla_put_failure;

		err = rtnl_get_offload_stats(skb, dev, prividx);
		अगर (err == -ENODATA)
			nla_nest_cancel(skb, attr);
		अन्यथा
			nla_nest_end(skb, attr);

		अगर (err && err != -ENODATA)
			जाओ nla_put_failure;
		*idxattr = 0;
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_AF_SPEC, *idxattr)) अणु
		काष्ठा rtnl_af_ops *af_ops;

		*idxattr = IFLA_STATS_AF_SPEC;
		attr = nla_nest_start_noflag(skb, IFLA_STATS_AF_SPEC);
		अगर (!attr)
			जाओ nla_put_failure;

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(af_ops, &rtnl_af_ops, list) अणु
			अगर (af_ops->fill_stats_af) अणु
				काष्ठा nlattr *af;
				पूर्णांक err;

				af = nla_nest_start_noflag(skb,
							   af_ops->family);
				अगर (!af) अणु
					rcu_पढ़ो_unlock();
					जाओ nla_put_failure;
				पूर्ण
				err = af_ops->fill_stats_af(skb, dev);

				अगर (err == -ENODATA) अणु
					nla_nest_cancel(skb, af);
				पूर्ण अन्यथा अगर (err < 0) अणु
					rcu_पढ़ो_unlock();
					जाओ nla_put_failure;
				पूर्ण

				nla_nest_end(skb, af);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();

		nla_nest_end(skb, attr);

		*idxattr = 0;
	पूर्ण

	nlmsg_end(skb, nlh);

	वापस 0;

nla_put_failure:
	/* not a multi message or no progress mean a real error */
	अगर (!(flags & NLM_F_MULTI) || s_prividx == *prividx)
		nlmsg_cancel(skb, nlh);
	अन्यथा
		nlmsg_end(skb, nlh);

	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार अगर_nlmsg_stats_size(स्थिर काष्ठा net_device *dev,
				  u32 filter_mask)
अणु
	माप_प्रकार size = 0;

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_64, 0))
		size += nla_total_size_64bit(माप(काष्ठा rtnl_link_stats64));

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_XSTATS, 0)) अणु
		स्थिर काष्ठा rtnl_link_ops *ops = dev->rtnl_link_ops;
		पूर्णांक attr = IFLA_STATS_LINK_XSTATS;

		अगर (ops && ops->get_linkxstats_size) अणु
			size += nla_total_size(ops->get_linkxstats_size(dev,
									attr));
			/* क्रम IFLA_STATS_LINK_XSTATS */
			size += nla_total_size(0);
		पूर्ण
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_XSTATS_SLAVE, 0)) अणु
		काष्ठा net_device *_dev = (काष्ठा net_device *)dev;
		स्थिर काष्ठा rtnl_link_ops *ops = शून्य;
		स्थिर काष्ठा net_device *master;

		/* netdev_master_upper_dev_get can't take स्थिर */
		master = netdev_master_upper_dev_get(_dev);
		अगर (master)
			ops = master->rtnl_link_ops;
		अगर (ops && ops->get_linkxstats_size) अणु
			पूर्णांक attr = IFLA_STATS_LINK_XSTATS_SLAVE;

			size += nla_total_size(ops->get_linkxstats_size(dev,
									attr));
			/* क्रम IFLA_STATS_LINK_XSTATS_SLAVE */
			size += nla_total_size(0);
		पूर्ण
	पूर्ण

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_LINK_OFFLOAD_XSTATS, 0))
		size += rtnl_get_offload_stats_size(dev);

	अगर (stats_attr_valid(filter_mask, IFLA_STATS_AF_SPEC, 0)) अणु
		काष्ठा rtnl_af_ops *af_ops;

		/* क्रम IFLA_STATS_AF_SPEC */
		size += nla_total_size(0);

		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(af_ops, &rtnl_af_ops, list) अणु
			अगर (af_ops->get_stats_af_size) अणु
				size += nla_total_size(
					af_ops->get_stats_af_size(dev));

				/* क्रम AF_* */
				size += nla_total_size(0);
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक rtnl_valid_stats_req(स्थिर काष्ठा nlmsghdr *nlh, bool strict_check,
				bool is_dump, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगर_stats_msg *अगरsm;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरsm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for stats dump");
		वापस -EINVAL;
	पूर्ण

	अगर (!strict_check)
		वापस 0;

	अगरsm = nlmsg_data(nlh);

	/* only requests using strict checks can pass data to influence
	 * the dump. The legacy exception is filter_mask.
	 */
	अगर (अगरsm->pad1 || अगरsm->pad2 || (is_dump && अगरsm->अगरindex)) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for stats dump request");
		वापस -EINVAL;
	पूर्ण
	अगर (nlmsg_attrlen(nlh, माप(*अगरsm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid attributes after stats header");
		वापस -EINVAL;
	पूर्ण
	अगर (अगरsm->filter_mask >= IFLA_STATS_FILTER_BIT(IFLA_STATS_MAX + 1)) अणु
		NL_SET_ERR_MSG(extack, "Invalid stats requested through filter mask");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_stats_get(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *dev = शून्य;
	पूर्णांक idxattr = 0, prividx = 0;
	काष्ठा अगर_stats_msg *अगरsm;
	काष्ठा sk_buff *nskb;
	u32 filter_mask;
	पूर्णांक err;

	err = rtnl_valid_stats_req(nlh, netlink_strict_get_check(skb),
				   false, extack);
	अगर (err)
		वापस err;

	अगरsm = nlmsg_data(nlh);
	अगर (अगरsm->अगरindex > 0)
		dev = __dev_get_by_index(net, अगरsm->अगरindex);
	अन्यथा
		वापस -EINVAL;

	अगर (!dev)
		वापस -ENODEV;

	filter_mask = अगरsm->filter_mask;
	अगर (!filter_mask)
		वापस -EINVAL;

	nskb = nlmsg_new(अगर_nlmsg_stats_size(dev, filter_mask), GFP_KERNEL);
	अगर (!nskb)
		वापस -ENOBUFS;

	err = rtnl_fill_statsinfo(nskb, dev, RTM_NEWSTATS,
				  NETLINK_CB(skb).portid, nlh->nlmsg_seq, 0,
				  0, filter_mask, &idxattr, &prividx);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in अगर_nlmsg_stats_size */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(nskb);
	पूर्ण अन्यथा अणु
		err = rtnl_unicast(nskb, net, NETLINK_CB(skb).portid);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rtnl_stats_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	पूर्णांक h, s_h, err, s_idx, s_idxattr, s_prividx;
	काष्ठा net *net = sock_net(skb->sk);
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	काष्ठा अगर_stats_msg *अगरsm;
	काष्ठा hlist_head *head;
	काष्ठा net_device *dev;
	u32 filter_mask = 0;
	पूर्णांक idx = 0;

	s_h = cb->args[0];
	s_idx = cb->args[1];
	s_idxattr = cb->args[2];
	s_prividx = cb->args[3];

	cb->seq = net->dev_base_seq;

	err = rtnl_valid_stats_req(cb->nlh, cb->strict_check, true, extack);
	अगर (err)
		वापस err;

	अगरsm = nlmsg_data(cb->nlh);
	filter_mask = अगरsm->filter_mask;
	अगर (!filter_mask) अणु
		NL_SET_ERR_MSG(extack, "Filter mask must be set for stats dump");
		वापस -EINVAL;
	पूर्ण

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		hlist_क्रम_each_entry(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			err = rtnl_fill_statsinfo(skb, dev, RTM_NEWSTATS,
						  NETLINK_CB(cb->skb).portid,
						  cb->nlh->nlmsg_seq, 0,
						  flags, filter_mask,
						  &s_idxattr, &s_prividx);
			/* If we ran out of room on the first message,
			 * we're in trouble
			 */
			WARN_ON((err == -EMSGSIZE) && (skb->len == 0));

			अगर (err < 0)
				जाओ out;
			s_prividx = 0;
			s_idxattr = 0;
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
	पूर्ण
out:
	cb->args[3] = s_prividx;
	cb->args[2] = s_idxattr;
	cb->args[1] = idx;
	cb->args[0] = h;

	वापस skb->len;
पूर्ण

/* Process one rtnetlink message. */

अटल पूर्णांक rtnetlink_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा rtnl_link *link;
	काष्ठा module *owner;
	पूर्णांक err = -EOPNOTSUPP;
	rtnl_करोit_func करोit;
	अचिन्हित पूर्णांक flags;
	पूर्णांक kind;
	पूर्णांक family;
	पूर्णांक type;

	type = nlh->nlmsg_type;
	अगर (type > RTM_MAX)
		वापस -EOPNOTSUPP;

	type -= RTM_BASE;

	/* All the messages must have at least 1 byte length */
	अगर (nlmsg_len(nlh) < माप(काष्ठा rtgenmsg))
		वापस 0;

	family = ((काष्ठा rtgenmsg *)nlmsg_data(nlh))->rtgen_family;
	kind = type&3;

	अगर (kind != 2 && !netlink_net_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	rcu_पढ़ो_lock();
	अगर (kind == 2 && nlh->nlmsg_flags&NLM_F_DUMP) अणु
		काष्ठा sock *rtnl;
		rtnl_dumpit_func dumpit;
		u32 min_dump_alloc = 0;

		link = rtnl_get_link(family, type);
		अगर (!link || !link->dumpit) अणु
			family = PF_UNSPEC;
			link = rtnl_get_link(family, type);
			अगर (!link || !link->dumpit)
				जाओ err_unlock;
		पूर्ण
		owner = link->owner;
		dumpit = link->dumpit;

		अगर (type == RTM_GETLINK - RTM_BASE)
			min_dump_alloc = rtnl_calcit(skb, nlh);

		err = 0;
		/* need to करो this beक्रमe rcu_पढ़ो_unlock() */
		अगर (!try_module_get(owner))
			err = -EPROTONOSUPPORT;

		rcu_पढ़ो_unlock();

		rtnl = net->rtnl;
		अगर (err == 0) अणु
			काष्ठा netlink_dump_control c = अणु
				.dump		= dumpit,
				.min_dump_alloc	= min_dump_alloc,
				.module		= owner,
			पूर्ण;
			err = netlink_dump_start(rtnl, skb, nlh, &c);
			/* netlink_dump_start() will keep a reference on
			 * module अगर dump is still in progress.
			 */
			module_put(owner);
		पूर्ण
		वापस err;
	पूर्ण

	link = rtnl_get_link(family, type);
	अगर (!link || !link->करोit) अणु
		family = PF_UNSPEC;
		link = rtnl_get_link(PF_UNSPEC, type);
		अगर (!link || !link->करोit)
			जाओ out_unlock;
	पूर्ण

	owner = link->owner;
	अगर (!try_module_get(owner)) अणु
		err = -EPROTONOSUPPORT;
		जाओ out_unlock;
	पूर्ण

	flags = link->flags;
	अगर (flags & RTNL_FLAG_DOIT_UNLOCKED) अणु
		करोit = link->करोit;
		rcu_पढ़ो_unlock();
		अगर (करोit)
			err = करोit(skb, nlh, extack);
		module_put(owner);
		वापस err;
	पूर्ण
	rcu_पढ़ो_unlock();

	rtnl_lock();
	link = rtnl_get_link(family, type);
	अगर (link && link->करोit)
		err = link->करोit(skb, nlh, extack);
	rtnl_unlock();

	module_put(owner);

	वापस err;

out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;

err_unlock:
	rcu_पढ़ो_unlock();
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम rtnetlink_rcv(काष्ठा sk_buff *skb)
अणु
	netlink_rcv_skb(skb, &rtnetlink_rcv_msg);
पूर्ण

अटल पूर्णांक rtnetlink_bind(काष्ठा net *net, पूर्णांक group)
अणु
	चयन (group) अणु
	हाल RTNLGRP_IPV4_MROUTE_R:
	हाल RTNLGRP_IPV6_MROUTE_R:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtnetlink_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_REBOOT:
	हाल NETDEV_CHANGEMTU:
	हाल NETDEV_CHANGEADDR:
	हाल NETDEV_CHANGENAME:
	हाल NETDEV_FEAT_CHANGE:
	हाल NETDEV_BONDING_FAILOVER:
	हाल NETDEV_POST_TYPE_CHANGE:
	हाल NETDEV_NOTIFY_PEERS:
	हाल NETDEV_CHANGEUPPER:
	हाल NETDEV_RESEND_IGMP:
	हाल NETDEV_CHANGEINFODATA:
	हाल NETDEV_CHANGELOWERSTATE:
	हाल NETDEV_CHANGE_TX_QUEUE_LEN:
		rपंचांगsg_अगरinfo_event(RTM_NEWLINK, dev, 0, rtnl_get_event(event),
				   GFP_KERNEL, शून्य, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rtnetlink_dev_notअगरier = अणु
	.notअगरier_call	= rtnetlink_event,
पूर्ण;


अटल पूर्णांक __net_init rtnetlink_net_init(काष्ठा net *net)
अणु
	काष्ठा sock *sk;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups		= RTNLGRP_MAX,
		.input		= rtnetlink_rcv,
		.cb_mutex	= &rtnl_mutex,
		.flags		= NL_CFG_F_NONROOT_RECV,
		.bind		= rtnetlink_bind,
	पूर्ण;

	sk = netlink_kernel_create(net, NETLINK_ROUTE, &cfg);
	अगर (!sk)
		वापस -ENOMEM;
	net->rtnl = sk;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास rtnetlink_net_निकास(काष्ठा net *net)
अणु
	netlink_kernel_release(net->rtnl);
	net->rtnl = शून्य;
पूर्ण

अटल काष्ठा pernet_operations rtnetlink_net_ops = अणु
	.init = rtnetlink_net_init,
	.निकास = rtnetlink_net_निकास,
पूर्ण;

व्योम __init rtnetlink_init(व्योम)
अणु
	अगर (रेजिस्टर_pernet_subsys(&rtnetlink_net_ops))
		panic("rtnetlink_init: cannot initialize rtnetlink\n");

	रेजिस्टर_netdevice_notअगरier(&rtnetlink_dev_notअगरier);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETLINK, rtnl_getlink,
		      rtnl_dump_अगरinfo, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_SETLINK, rtnl_setlink, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWLINK, rtnl_newlink, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELLINK, rtnl_dellink, शून्य, 0);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETADDR, शून्य, rtnl_dump_all, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETROUTE, शून्य, rtnl_dump_all, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNETCONF, शून्य, rtnl_dump_all, 0);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWLINKPROP, rtnl_newlinkprop, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELLINKPROP, rtnl_dellinkprop, शून्य, 0);

	rtnl_रेजिस्टर(PF_BRIDGE, RTM_NEWNEIGH, rtnl_fdb_add, शून्य, 0);
	rtnl_रेजिस्टर(PF_BRIDGE, RTM_DELNEIGH, rtnl_fdb_del, शून्य, 0);
	rtnl_रेजिस्टर(PF_BRIDGE, RTM_GETNEIGH, rtnl_fdb_get, rtnl_fdb_dump, 0);

	rtnl_रेजिस्टर(PF_BRIDGE, RTM_GETLINK, शून्य, rtnl_bridge_getlink, 0);
	rtnl_रेजिस्टर(PF_BRIDGE, RTM_DELLINK, rtnl_bridge_dellink, शून्य, 0);
	rtnl_रेजिस्टर(PF_BRIDGE, RTM_SETLINK, rtnl_bridge_setlink, शून्य, 0);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETSTATS, rtnl_stats_get, rtnl_stats_dump,
		      0);
पूर्ण
