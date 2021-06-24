<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007, 2008, 2009 Siemens AG
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>

#समावेश <net/cfg802154.h>
#समावेश <net/rtnetlink.h>

#समावेश "ieee802154.h"
#समावेश "nl802154.h"
#समावेश "sysfs.h"
#समावेश "core.h"

/* name क्रम sysfs, %d is appended */
#घोषणा PHY_NAME "phy"

/* RCU-रक्षित (and RTNL क्रम ग_लिखोrs) */
LIST_HEAD(cfg802154_rdev_list);
पूर्णांक cfg802154_rdev_list_generation;

काष्ठा wpan_phy *wpan_phy_find(स्थिर अक्षर *str)
अणु
	काष्ठा device *dev;

	अगर (WARN_ON(!str))
		वापस शून्य;

	dev = class_find_device_by_name(&wpan_phy_class, str);
	अगर (!dev)
		वापस शून्य;

	वापस container_of(dev, काष्ठा wpan_phy, dev);
पूर्ण
EXPORT_SYMBOL(wpan_phy_find);

काष्ठा wpan_phy_iter_data अणु
	पूर्णांक (*fn)(काष्ठा wpan_phy *phy, व्योम *data);
	व्योम *data;
पूर्ण;

अटल पूर्णांक wpan_phy_iter(काष्ठा device *dev, व्योम *_data)
अणु
	काष्ठा wpan_phy_iter_data *wpid = _data;
	काष्ठा wpan_phy *phy = container_of(dev, काष्ठा wpan_phy, dev);

	वापस wpid->fn(phy, wpid->data);
पूर्ण

पूर्णांक wpan_phy_क्रम_each(पूर्णांक (*fn)(काष्ठा wpan_phy *phy, व्योम *data),
		      व्योम *data)
अणु
	काष्ठा wpan_phy_iter_data wpid = अणु
		.fn = fn,
		.data = data,
	पूर्ण;

	वापस class_क्रम_each_device(&wpan_phy_class, शून्य,
			&wpid, wpan_phy_iter);
पूर्ण
EXPORT_SYMBOL(wpan_phy_क्रम_each);

काष्ठा cfg802154_रेजिस्टरed_device *
cfg802154_rdev_by_wpan_phy_idx(पूर्णांक wpan_phy_idx)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *result = शून्य, *rdev;

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg802154_rdev_list, list) अणु
		अगर (rdev->wpan_phy_idx == wpan_phy_idx) अणु
			result = rdev;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

काष्ठा wpan_phy *wpan_phy_idx_to_wpan_phy(पूर्णांक wpan_phy_idx)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	rdev = cfg802154_rdev_by_wpan_phy_idx(wpan_phy_idx);
	अगर (!rdev)
		वापस शून्य;
	वापस &rdev->wpan_phy;
पूर्ण

काष्ठा wpan_phy *
wpan_phy_new(स्थिर काष्ठा cfg802154_ops *ops, माप_प्रकार priv_size)
अणु
	अटल atomic_t wpan_phy_counter = ATOMIC_INIT(0);
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;
	माप_प्रकार alloc_size;

	alloc_size = माप(*rdev) + priv_size;
	rdev = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!rdev)
		वापस शून्य;

	rdev->ops = ops;

	rdev->wpan_phy_idx = atomic_inc_वापस(&wpan_phy_counter);

	अगर (unlikely(rdev->wpan_phy_idx < 0)) अणु
		/* ugh, wrapped! */
		atomic_dec(&wpan_phy_counter);
		kमुक्त(rdev);
		वापस शून्य;
	पूर्ण

	/* atomic_inc_वापस makes it start at 1, make it start at 0 */
	rdev->wpan_phy_idx--;

	INIT_LIST_HEAD(&rdev->wpan_dev_list);
	device_initialize(&rdev->wpan_phy.dev);
	dev_set_name(&rdev->wpan_phy.dev, PHY_NAME "%d", rdev->wpan_phy_idx);

	rdev->wpan_phy.dev.class = &wpan_phy_class;
	rdev->wpan_phy.dev.platक्रमm_data = rdev;

	wpan_phy_net_set(&rdev->wpan_phy, &init_net);

	init_रुकोqueue_head(&rdev->dev_रुको);

	वापस &rdev->wpan_phy;
पूर्ण
EXPORT_SYMBOL(wpan_phy_new);

पूर्णांक wpan_phy_रेजिस्टर(काष्ठा wpan_phy *phy)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = wpan_phy_to_rdev(phy);
	पूर्णांक ret;

	rtnl_lock();
	ret = device_add(&phy->dev);
	अगर (ret) अणु
		rtnl_unlock();
		वापस ret;
	पूर्ण

	list_add_rcu(&rdev->list, &cfg802154_rdev_list);
	cfg802154_rdev_list_generation++;

	/* TODO phy रेजिस्टरed lock */
	rtnl_unlock();

	/* TODO nl802154 phy notअगरy */

	वापस 0;
पूर्ण
EXPORT_SYMBOL(wpan_phy_रेजिस्टर);

व्योम wpan_phy_unरेजिस्टर(काष्ठा wpan_phy *phy)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = wpan_phy_to_rdev(phy);

	रुको_event(rdev->dev_रुको, (अणु
		पूर्णांक __count;
		rtnl_lock();
		__count = rdev->खोलोcount;
		rtnl_unlock();
		__count == 0; पूर्ण));

	rtnl_lock();
	/* TODO nl802154 phy notअगरy */
	/* TODO phy रेजिस्टरed lock */

	WARN_ON(!list_empty(&rdev->wpan_dev_list));

	/* First हटाओ the hardware from everywhere, this makes
	 * it impossible to find from userspace.
	 */
	list_del_rcu(&rdev->list);
	synchronize_rcu();

	cfg802154_rdev_list_generation++;

	device_del(&phy->dev);

	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(wpan_phy_unरेजिस्टर);

व्योम wpan_phy_मुक्त(काष्ठा wpan_phy *phy)
अणु
	put_device(&phy->dev);
पूर्ण
EXPORT_SYMBOL(wpan_phy_मुक्त);

पूर्णांक cfg802154_चयन_netns(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			   काष्ठा net *net)
अणु
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक err = 0;

	list_क्रम_each_entry(wpan_dev, &rdev->wpan_dev_list, list) अणु
		अगर (!wpan_dev->netdev)
			जारी;
		wpan_dev->netdev->features &= ~NETIF_F_NETNS_LOCAL;
		err = dev_change_net_namespace(wpan_dev->netdev, net, "wpan%d");
		अगर (err)
			अवरोध;
		wpan_dev->netdev->features |= NETIF_F_NETNS_LOCAL;
	पूर्ण

	अगर (err) अणु
		/* failed -- clean up to old netns */
		net = wpan_phy_net(&rdev->wpan_phy);

		list_क्रम_each_entry_जारी_reverse(wpan_dev,
						     &rdev->wpan_dev_list,
						     list) अणु
			अगर (!wpan_dev->netdev)
				जारी;
			wpan_dev->netdev->features &= ~NETIF_F_NETNS_LOCAL;
			err = dev_change_net_namespace(wpan_dev->netdev, net,
						       "wpan%d");
			WARN_ON(err);
			wpan_dev->netdev->features |= NETIF_F_NETNS_LOCAL;
		पूर्ण

		वापस err;
	पूर्ण

	wpan_phy_net_set(&rdev->wpan_phy, net);

	err = device_नाम(&rdev->wpan_phy.dev, dev_name(&rdev->wpan_phy.dev));
	WARN_ON(err);

	वापस 0;
पूर्ण

व्योम cfg802154_dev_मुक्त(काष्ठा cfg802154_रेजिस्टरed_device *rdev)
अणु
	kमुक्त(rdev);
पूर्ण

अटल व्योम
cfg802154_update_अगरace_num(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			   पूर्णांक अगरtype, पूर्णांक num)
अणु
	ASSERT_RTNL();

	rdev->num_running_अगरaces += num;
पूर्ण

अटल पूर्णांक cfg802154_netdev_notअगरier_call(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;

	अगर (!wpan_dev)
		वापस NOTIFY_DONE;

	rdev = wpan_phy_to_rdev(wpan_dev->wpan_phy);

	/* TODO WARN_ON unspec type */

	चयन (state) अणु
		/* TODO NETDEV_DEVTYPE */
	हाल NETDEV_REGISTER:
		dev->features |= NETIF_F_NETNS_LOCAL;
		wpan_dev->identअगरier = ++rdev->wpan_dev_id;
		list_add_rcu(&wpan_dev->list, &rdev->wpan_dev_list);
		rdev->devlist_generation++;

		wpan_dev->netdev = dev;
		अवरोध;
	हाल NETDEV_DOWN:
		cfg802154_update_अगरace_num(rdev, wpan_dev->अगरtype, -1);

		rdev->खोलोcount--;
		wake_up(&rdev->dev_रुको);
		अवरोध;
	हाल NETDEV_UP:
		cfg802154_update_अगरace_num(rdev, wpan_dev->अगरtype, 1);

		rdev->खोलोcount++;
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* It is possible to get NETDEV_UNREGISTER
		 * multiple बार. To detect that, check
		 * that the पूर्णांकerface is still on the list
		 * of रेजिस्टरed पूर्णांकerfaces, and only then
		 * हटाओ and clean it up.
		 */
		अगर (!list_empty(&wpan_dev->list)) अणु
			list_del_rcu(&wpan_dev->list);
			rdev->devlist_generation++;
		पूर्ण
		/* synchronize (so that we won't find this netdev
		 * from other code any more) and then clear the list
		 * head so that the above code can safely check क्रम
		 * !list_empty() to aव्योम द्विगुन-cleanup.
		 */
		synchronize_rcu();
		INIT_LIST_HEAD(&wpan_dev->list);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cfg802154_netdev_notअगरier = अणु
	.notअगरier_call = cfg802154_netdev_notअगरier_call,
पूर्ण;

अटल व्योम __net_निकास cfg802154_pernet_निकास(काष्ठा net *net)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;

	rtnl_lock();
	list_क्रम_each_entry(rdev, &cfg802154_rdev_list, list) अणु
		अगर (net_eq(wpan_phy_net(&rdev->wpan_phy), net))
			WARN_ON(cfg802154_चयन_netns(rdev, &init_net));
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations cfg802154_pernet_ops = अणु
	.निकास = cfg802154_pernet_निकास,
पूर्ण;

अटल पूर्णांक __init wpan_phy_class_init(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_pernet_device(&cfg802154_pernet_ops);
	अगर (rc)
		जाओ err;

	rc = wpan_phy_sysfs_init();
	अगर (rc)
		जाओ err_sysfs;

	rc = रेजिस्टर_netdevice_notअगरier(&cfg802154_netdev_notअगरier);
	अगर (rc)
		जाओ err_nl;

	rc = ieee802154_nl_init();
	अगर (rc)
		जाओ err_notअगरier;

	rc = nl802154_init();
	अगर (rc)
		जाओ err_ieee802154_nl;

	वापस 0;

err_ieee802154_nl:
	ieee802154_nl_निकास();

err_notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&cfg802154_netdev_notअगरier);
err_nl:
	wpan_phy_sysfs_निकास();
err_sysfs:
	unरेजिस्टर_pernet_device(&cfg802154_pernet_ops);
err:
	वापस rc;
पूर्ण
subsys_initcall(wpan_phy_class_init);

अटल व्योम __निकास wpan_phy_class_निकास(व्योम)
अणु
	nl802154_निकास();
	ieee802154_nl_निकास();
	unरेजिस्टर_netdevice_notअगरier(&cfg802154_netdev_notअगरier);
	wpan_phy_sysfs_निकास();
	unरेजिस्टर_pernet_device(&cfg802154_pernet_ops);
पूर्ण
module_निकास(wpan_phy_class_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("IEEE 802.15.4 configuration interface");
MODULE_AUTHOR("Dmitry Eremin-Solenikov");
