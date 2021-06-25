<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: pn_dev.c
 *
 * Phonet network device
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Authors: Sakari Ailus <sakari.ailus@nokia.com>
 *          Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phonet.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/sock.h>
#समावेश <net/netns/generic.h>
#समावेश <net/phonet/pn_dev.h>

काष्ठा phonet_routes अणु
	काष्ठा mutex		lock;
	काष्ठा net_device __rcu	*table[64];
पूर्ण;

काष्ठा phonet_net अणु
	काष्ठा phonet_device_list pndevs;
	काष्ठा phonet_routes routes;
पूर्ण;

अटल अचिन्हित पूर्णांक phonet_net_id __पढ़ो_mostly;

अटल काष्ठा phonet_net *phonet_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, phonet_net_id);
पूर्ण

काष्ठा phonet_device_list *phonet_device_list(काष्ठा net *net)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(net);
	वापस &pnn->pndevs;
पूर्ण

/* Allocate new Phonet device. */
अटल काष्ठा phonet_device *__phonet_device_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd = kदो_स्मृति(माप(*pnd), GFP_ATOMIC);
	अगर (pnd == शून्य)
		वापस शून्य;
	pnd->netdev = dev;
	biपंचांगap_zero(pnd->addrs, 64);

	BUG_ON(!mutex_is_locked(&pndevs->lock));
	list_add_rcu(&pnd->list, &pndevs->list);
	वापस pnd;
पूर्ण

अटल काष्ठा phonet_device *__phonet_get(काष्ठा net_device *dev)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd;

	BUG_ON(!mutex_is_locked(&pndevs->lock));
	list_क्रम_each_entry(pnd, &pndevs->list, list) अणु
		अगर (pnd->netdev == dev)
			वापस pnd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा phonet_device *__phonet_get_rcu(काष्ठा net_device *dev)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd;

	list_क्रम_each_entry_rcu(pnd, &pndevs->list, list) अणु
		अगर (pnd->netdev == dev)
			वापस pnd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम phonet_device_destroy(काष्ठा net_device *dev)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd;

	ASSERT_RTNL();

	mutex_lock(&pndevs->lock);
	pnd = __phonet_get(dev);
	अगर (pnd)
		list_del_rcu(&pnd->list);
	mutex_unlock(&pndevs->lock);

	अगर (pnd) अणु
		u8 addr;

		क्रम_each_set_bit(addr, pnd->addrs, 64)
			phonet_address_notअगरy(RTM_DELADDR, dev, addr);
		kमुक्त(pnd);
	पूर्ण
पूर्ण

काष्ठा net_device *phonet_device_get(काष्ठा net *net)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(net);
	काष्ठा phonet_device *pnd;
	काष्ठा net_device *dev = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pnd, &pndevs->list, list) अणु
		dev = pnd->netdev;
		BUG_ON(!dev);

		अगर ((dev->reg_state == NETREG_REGISTERED) &&
			((pnd->netdev->flags & IFF_UP)) == IFF_UP)
			अवरोध;
		dev = शून्य;
	पूर्ण
	अगर (dev)
		dev_hold(dev);
	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण

पूर्णांक phonet_address_add(काष्ठा net_device *dev, u8 addr)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd;
	पूर्णांक err = 0;

	mutex_lock(&pndevs->lock);
	/* Find or create Phonet-specअगरic device data */
	pnd = __phonet_get(dev);
	अगर (pnd == शून्य)
		pnd = __phonet_device_alloc(dev);
	अगर (unlikely(pnd == शून्य))
		err = -ENOMEM;
	अन्यथा अगर (test_and_set_bit(addr >> 2, pnd->addrs))
		err = -EEXIST;
	mutex_unlock(&pndevs->lock);
	वापस err;
पूर्ण

पूर्णांक phonet_address_del(काष्ठा net_device *dev, u8 addr)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(dev_net(dev));
	काष्ठा phonet_device *pnd;
	पूर्णांक err = 0;

	mutex_lock(&pndevs->lock);
	pnd = __phonet_get(dev);
	अगर (!pnd || !test_and_clear_bit(addr >> 2, pnd->addrs)) अणु
		err = -EADDRNOTAVAIL;
		pnd = शून्य;
	पूर्ण अन्यथा अगर (biपंचांगap_empty(pnd->addrs, 64))
		list_del_rcu(&pnd->list);
	अन्यथा
		pnd = शून्य;
	mutex_unlock(&pndevs->lock);

	अगर (pnd)
		kमुक्त_rcu(pnd, rcu);

	वापस err;
पूर्ण

/* Gets a source address toward a destination, through a पूर्णांकerface. */
u8 phonet_address_get(काष्ठा net_device *dev, u8 daddr)
अणु
	काष्ठा phonet_device *pnd;
	u8 saddr;

	rcu_पढ़ो_lock();
	pnd = __phonet_get_rcu(dev);
	अगर (pnd) अणु
		BUG_ON(biपंचांगap_empty(pnd->addrs, 64));

		/* Use same source address as destination, अगर possible */
		अगर (test_bit(daddr >> 2, pnd->addrs))
			saddr = daddr;
		अन्यथा
			saddr = find_first_bit(pnd->addrs, 64) << 2;
	पूर्ण अन्यथा
		saddr = PN_NO_ADDR;
	rcu_पढ़ो_unlock();

	अगर (saddr == PN_NO_ADDR) अणु
		/* Fallback to another device */
		काष्ठा net_device *def_dev;

		def_dev = phonet_device_get(dev_net(dev));
		अगर (def_dev) अणु
			अगर (def_dev != dev)
				saddr = phonet_address_get(def_dev, daddr);
			dev_put(def_dev);
		पूर्ण
	पूर्ण
	वापस saddr;
पूर्ण

पूर्णांक phonet_address_lookup(काष्ठा net *net, u8 addr)
अणु
	काष्ठा phonet_device_list *pndevs = phonet_device_list(net);
	काष्ठा phonet_device *pnd;
	पूर्णांक err = -EADDRNOTAVAIL;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pnd, &pndevs->list, list) अणु
		/* Don't allow unरेजिस्टरing devices! */
		अगर ((pnd->netdev->reg_state != NETREG_REGISTERED) ||
				((pnd->netdev->flags & IFF_UP)) != IFF_UP)
			जारी;

		अगर (test_bit(addr >> 2, pnd->addrs)) अणु
			err = 0;
			जाओ found;
		पूर्ण
	पूर्ण
found:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* स्वतःmatically configure a Phonet device, अगर supported */
अटल पूर्णांक phonet_device_स्वतःconf(काष्ठा net_device *dev)
अणु
	काष्ठा अगर_phonet_req req;
	पूर्णांक ret;

	अगर (!dev->netdev_ops->nकरो_करो_ioctl)
		वापस -EOPNOTSUPP;

	ret = dev->netdev_ops->nकरो_करो_ioctl(dev, (काष्ठा अगरreq *)&req,
						SIOCPNGAUTOCONF);
	अगर (ret < 0)
		वापस ret;

	ASSERT_RTNL();
	ret = phonet_address_add(dev, req.अगरr_phonet_स्वतःconf.device);
	अगर (ret)
		वापस ret;
	phonet_address_notअगरy(RTM_NEWADDR, dev,
				req.अगरr_phonet_स्वतःconf.device);
	वापस 0;
पूर्ण

अटल व्योम phonet_route_स्वतःdel(काष्ठा net_device *dev)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(dev_net(dev));
	अचिन्हित पूर्णांक i;
	DECLARE_BITMAP(deleted, 64);

	/* Remove left-over Phonet routes */
	biपंचांगap_zero(deleted, 64);
	mutex_lock(&pnn->routes.lock);
	क्रम (i = 0; i < 64; i++)
		अगर (rcu_access_poपूर्णांकer(pnn->routes.table[i]) == dev) अणु
			RCU_INIT_POINTER(pnn->routes.table[i], शून्य);
			set_bit(i, deleted);
		पूर्ण
	mutex_unlock(&pnn->routes.lock);

	अगर (biपंचांगap_empty(deleted, 64))
		वापस; /* लघु-circuit RCU */
	synchronize_rcu();
	क्रम_each_set_bit(i, deleted, 64) अणु
		rपंचांग_phonet_notअगरy(RTM_DELROUTE, dev, i);
		dev_put(dev);
	पूर्ण
पूर्ण

/* notअगरy Phonet of device events */
अटल पूर्णांक phonet_device_notअगरy(काष्ठा notअगरier_block *me, अचिन्हित दीर्घ what,
				व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	चयन (what) अणु
	हाल NETDEV_REGISTER:
		अगर (dev->type == ARPHRD_PHONET)
			phonet_device_स्वतःconf(dev);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		phonet_device_destroy(dev);
		phonet_route_स्वतःdel(dev);
		अवरोध;
	पूर्ण
	वापस 0;

पूर्ण

अटल काष्ठा notअगरier_block phonet_device_notअगरier = अणु
	.notअगरier_call = phonet_device_notअगरy,
	.priority = 0,
पूर्ण;

/* Per-namespace Phonet devices handling */
अटल पूर्णांक __net_init phonet_init_net(काष्ठा net *net)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(net);

	अगर (!proc_create_net("phonet", 0, net->proc_net, &pn_sock_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;

	INIT_LIST_HEAD(&pnn->pndevs.list);
	mutex_init(&pnn->pndevs.lock);
	mutex_init(&pnn->routes.lock);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास phonet_निकास_net(काष्ठा net *net)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(net);

	हटाओ_proc_entry("phonet", net->proc_net);
	WARN_ON_ONCE(!list_empty(&pnn->pndevs.list));
पूर्ण

अटल काष्ठा pernet_operations phonet_net_ops = अणु
	.init = phonet_init_net,
	.निकास = phonet_निकास_net,
	.id   = &phonet_net_id,
	.size = माप(काष्ठा phonet_net),
पूर्ण;

/* Initialize Phonet devices list */
पूर्णांक __init phonet_device_init(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_pernet_subsys(&phonet_net_ops);
	अगर (err)
		वापस err;

	proc_create_net("pnresource", 0, init_net.proc_net, &pn_res_seq_ops,
			माप(काष्ठा seq_net_निजी));
	रेजिस्टर_netdevice_notअगरier(&phonet_device_notअगरier);
	err = phonet_netlink_रेजिस्टर();
	अगर (err)
		phonet_device_निकास();
	वापस err;
पूर्ण

व्योम phonet_device_निकास(व्योम)
अणु
	rtnl_unरेजिस्टर_all(PF_PHONET);
	unरेजिस्टर_netdevice_notअगरier(&phonet_device_notअगरier);
	unरेजिस्टर_pernet_subsys(&phonet_net_ops);
	हटाओ_proc_entry("pnresource", init_net.proc_net);
पूर्ण

पूर्णांक phonet_route_add(काष्ठा net_device *dev, u8 daddr)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(dev_net(dev));
	काष्ठा phonet_routes *routes = &pnn->routes;
	पूर्णांक err = -EEXIST;

	daddr = daddr >> 2;
	mutex_lock(&routes->lock);
	अगर (routes->table[daddr] == शून्य) अणु
		rcu_assign_poपूर्णांकer(routes->table[daddr], dev);
		dev_hold(dev);
		err = 0;
	पूर्ण
	mutex_unlock(&routes->lock);
	वापस err;
पूर्ण

पूर्णांक phonet_route_del(काष्ठा net_device *dev, u8 daddr)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(dev_net(dev));
	काष्ठा phonet_routes *routes = &pnn->routes;

	daddr = daddr >> 2;
	mutex_lock(&routes->lock);
	अगर (rcu_access_poपूर्णांकer(routes->table[daddr]) == dev)
		RCU_INIT_POINTER(routes->table[daddr], शून्य);
	अन्यथा
		dev = शून्य;
	mutex_unlock(&routes->lock);

	अगर (!dev)
		वापस -ENOENT;
	synchronize_rcu();
	dev_put(dev);
	वापस 0;
पूर्ण

काष्ठा net_device *phonet_route_get_rcu(काष्ठा net *net, u8 daddr)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(net);
	काष्ठा phonet_routes *routes = &pnn->routes;
	काष्ठा net_device *dev;

	daddr >>= 2;
	dev = rcu_dereference(routes->table[daddr]);
	वापस dev;
पूर्ण

काष्ठा net_device *phonet_route_output(काष्ठा net *net, u8 daddr)
अणु
	काष्ठा phonet_net *pnn = phonet_pernet(net);
	काष्ठा phonet_routes *routes = &pnn->routes;
	काष्ठा net_device *dev;

	daddr >>= 2;
	rcu_पढ़ो_lock();
	dev = rcu_dereference(routes->table[daddr]);
	अगर (dev)
		dev_hold(dev);
	rcu_पढ़ो_unlock();

	अगर (!dev)
		dev = phonet_device_get(net); /* Default route */
	वापस dev;
पूर्ण
