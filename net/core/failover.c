<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

/* A common module to handle registrations and notअगरications क्रम paraभव
 * drivers to enable accelerated datapath and support VF live migration.
 *
 * The notअगरier and event handling code is based on netvsc driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <uapi/linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/failover.h>

अटल LIST_HEAD(failover_list);
अटल DEFINE_SPINLOCK(failover_lock);

अटल काष्ठा net_device *failover_get_bymac(u8 *mac, काष्ठा failover_ops **ops)
अणु
	काष्ठा net_device *failover_dev;
	काष्ठा failover *failover;

	spin_lock(&failover_lock);
	list_क्रम_each_entry(failover, &failover_list, list) अणु
		failover_dev = rtnl_dereference(failover->failover_dev);
		अगर (ether_addr_equal(failover_dev->perm_addr, mac)) अणु
			*ops = rtnl_dereference(failover->ops);
			spin_unlock(&failover_lock);
			वापस failover_dev;
		पूर्ण
	पूर्ण
	spin_unlock(&failover_lock);
	वापस शून्य;
पूर्ण

/**
 * failover_slave_रेजिस्टर - Register a slave netdev
 *
 * @slave_dev: slave netdev that is being रेजिस्टरed
 *
 * Registers a slave device to a failover instance. Only ethernet devices
 * are supported.
 */
अटल पूर्णांक failover_slave_रेजिस्टर(काष्ठा net_device *slave_dev)
अणु
	काष्ठा netdev_lag_upper_info lag_upper_info;
	काष्ठा net_device *failover_dev;
	काष्ठा failover_ops *fops;
	पूर्णांक err;

	अगर (slave_dev->type != ARPHRD_ETHER)
		जाओ करोne;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	अगर (!failover_dev)
		जाओ करोne;

	अगर (fops && fops->slave_pre_रेजिस्टर &&
	    fops->slave_pre_रेजिस्टर(slave_dev, failover_dev))
		जाओ करोne;

	err = netdev_rx_handler_रेजिस्टर(slave_dev, fops->slave_handle_frame,
					 failover_dev);
	अगर (err) अणु
		netdev_err(slave_dev, "can not register failover rx handler (err = %d)\n",
			   err);
		जाओ करोne;
	पूर्ण

	lag_upper_info.tx_type = NETDEV_LAG_TX_TYPE_ACTIVEBACKUP;
	err = netdev_master_upper_dev_link(slave_dev, failover_dev, शून्य,
					   &lag_upper_info, शून्य);
	अगर (err) अणु
		netdev_err(slave_dev, "can not set failover device %s (err = %d)\n",
			   failover_dev->name, err);
		जाओ err_upper_link;
	पूर्ण

	slave_dev->priv_flags |= (IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);

	अगर (fops && fops->slave_रेजिस्टर &&
	    !fops->slave_रेजिस्टर(slave_dev, failover_dev))
		वापस NOTIFY_OK;

	netdev_upper_dev_unlink(slave_dev, failover_dev);
	slave_dev->priv_flags &= ~(IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);
err_upper_link:
	netdev_rx_handler_unरेजिस्टर(slave_dev);
करोne:
	वापस NOTIFY_DONE;
पूर्ण

/**
 * failover_slave_unरेजिस्टर - Unरेजिस्टर a slave netdev
 *
 * @slave_dev: slave netdev that is being unरेजिस्टरed
 *
 * Unरेजिस्टरs a slave device from a failover instance.
 */
पूर्णांक failover_slave_unरेजिस्टर(काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_device *failover_dev;
	काष्ठा failover_ops *fops;

	अगर (!netअगर_is_failover_slave(slave_dev))
		जाओ करोne;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	अगर (!failover_dev)
		जाओ करोne;

	अगर (fops && fops->slave_pre_unरेजिस्टर &&
	    fops->slave_pre_unरेजिस्टर(slave_dev, failover_dev))
		जाओ करोne;

	netdev_rx_handler_unरेजिस्टर(slave_dev);
	netdev_upper_dev_unlink(slave_dev, failover_dev);
	slave_dev->priv_flags &= ~(IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);

	अगर (fops && fops->slave_unरेजिस्टर &&
	    !fops->slave_unरेजिस्टर(slave_dev, failover_dev))
		वापस NOTIFY_OK;

करोne:
	वापस NOTIFY_DONE;
पूर्ण
EXPORT_SYMBOL_GPL(failover_slave_unरेजिस्टर);

अटल पूर्णांक failover_slave_link_change(काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_device *failover_dev;
	काष्ठा failover_ops *fops;

	अगर (!netअगर_is_failover_slave(slave_dev))
		जाओ करोne;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	अगर (!failover_dev)
		जाओ करोne;

	अगर (!netअगर_running(failover_dev))
		जाओ करोne;

	अगर (fops && fops->slave_link_change &&
	    !fops->slave_link_change(slave_dev, failover_dev))
		वापस NOTIFY_OK;

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक failover_slave_name_change(काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_device *failover_dev;
	काष्ठा failover_ops *fops;

	अगर (!netअगर_is_failover_slave(slave_dev))
		जाओ करोne;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	अगर (!failover_dev)
		जाओ करोne;

	अगर (!netअगर_running(failover_dev))
		जाओ करोne;

	अगर (fops && fops->slave_name_change &&
	    !fops->slave_name_change(slave_dev, failover_dev))
		वापस NOTIFY_OK;

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
failover_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_dev = netdev_notअगरier_info_to_dev(ptr);

	/* Skip parent events */
	अगर (netअगर_is_failover(event_dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		वापस failover_slave_रेजिस्टर(event_dev);
	हाल NETDEV_UNREGISTER:
		वापस failover_slave_unरेजिस्टर(event_dev);
	हाल NETDEV_UP:
	हाल NETDEV_DOWN:
	हाल NETDEV_CHANGE:
		वापस failover_slave_link_change(event_dev);
	हाल NETDEV_CHANGENAME:
		वापस failover_slave_name_change(event_dev);
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block failover_notअगरier = अणु
	.notअगरier_call = failover_event,
पूर्ण;

अटल व्योम
failover_existing_slave_रेजिस्टर(काष्ठा net_device *failover_dev)
अणु
	काष्ठा net *net = dev_net(failover_dev);
	काष्ठा net_device *dev;

	rtnl_lock();
	क्रम_each_netdev(net, dev) अणु
		अगर (netअगर_is_failover(dev))
			जारी;
		अगर (ether_addr_equal(failover_dev->perm_addr, dev->perm_addr))
			failover_slave_रेजिस्टर(dev);
	पूर्ण
	rtnl_unlock();
पूर्ण

/**
 * failover_रेजिस्टर - Register a failover instance
 *
 * @dev: failover netdev
 * @ops: failover ops
 *
 * Allocate and रेजिस्टर a failover instance क्रम a failover netdev. ops
 * provides handlers क्रम slave device रेजिस्टर/unरेजिस्टर/link change/
 * name change events.
 *
 * Return: poपूर्णांकer to failover instance
 */
काष्ठा failover *failover_रेजिस्टर(काष्ठा net_device *dev,
				   काष्ठा failover_ops *ops)
अणु
	काष्ठा failover *failover;

	अगर (dev->type != ARPHRD_ETHER)
		वापस ERR_PTR(-EINVAL);

	failover = kzalloc(माप(*failover), GFP_KERNEL);
	अगर (!failover)
		वापस ERR_PTR(-ENOMEM);

	rcu_assign_poपूर्णांकer(failover->ops, ops);
	dev_hold(dev);
	dev->priv_flags |= IFF_FAILOVER;
	rcu_assign_poपूर्णांकer(failover->failover_dev, dev);

	spin_lock(&failover_lock);
	list_add_tail(&failover->list, &failover_list);
	spin_unlock(&failover_lock);

	netdev_info(dev, "failover master:%s registered\n", dev->name);

	failover_existing_slave_रेजिस्टर(dev);

	वापस failover;
पूर्ण
EXPORT_SYMBOL_GPL(failover_रेजिस्टर);

/**
 * failover_unरेजिस्टर - Unरेजिस्टर a failover instance
 *
 * @failover: poपूर्णांकer to failover instance
 *
 * Unरेजिस्टरs and मुक्तs a failover instance.
 */
व्योम failover_unरेजिस्टर(काष्ठा failover *failover)
अणु
	काष्ठा net_device *failover_dev;

	failover_dev = rcu_dereference(failover->failover_dev);

	netdev_info(failover_dev, "failover master:%s unregistered\n",
		    failover_dev->name);

	failover_dev->priv_flags &= ~IFF_FAILOVER;
	dev_put(failover_dev);

	spin_lock(&failover_lock);
	list_del(&failover->list);
	spin_unlock(&failover_lock);

	kमुक्त(failover);
पूर्ण
EXPORT_SYMBOL_GPL(failover_unरेजिस्टर);

अटल __init पूर्णांक
failover_init(व्योम)
अणु
	रेजिस्टर_netdevice_notअगरier(&failover_notअगरier);

	वापस 0;
पूर्ण
module_init(failover_init);

अटल __निकास
व्योम failover_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&failover_notअगरier);
पूर्ण
module_निकास(failover_निकास);

MODULE_DESCRIPTION("Generic failover infrastructure/interface");
MODULE_LICENSE("GPL v2");
