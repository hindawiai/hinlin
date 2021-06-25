<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/dsa/dsa.c - Hardware चयन handling
 * Copyright (c) 2008-2009 Marvell Semiconductor
 * Copyright (c) 2013 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/etherdevice.h>

#समावेश "dsa_priv.h"

अटल LIST_HEAD(dsa_tag_drivers_list);
अटल DEFINE_MUTEX(dsa_tag_drivers_lock);

अटल काष्ठा sk_buff *dsa_slave_notag_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	/* Just वापस the original SKB */
	वापस skb;
पूर्ण

अटल स्थिर काष्ठा dsa_device_ops none_ops = अणु
	.name	= "none",
	.proto	= DSA_TAG_PROTO_NONE,
	.xmit	= dsa_slave_notag_xmit,
	.rcv	= शून्य,
पूर्ण;

DSA_TAG_DRIVER(none_ops);

अटल व्योम dsa_tag_driver_रेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver,
				    काष्ठा module *owner)
अणु
	dsa_tag_driver->owner = owner;

	mutex_lock(&dsa_tag_drivers_lock);
	list_add_tail(&dsa_tag_driver->list, &dsa_tag_drivers_list);
	mutex_unlock(&dsa_tag_drivers_lock);
पूर्ण

व्योम dsa_tag_drivers_रेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver_array[],
			      अचिन्हित पूर्णांक count, काष्ठा module *owner)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		dsa_tag_driver_रेजिस्टर(dsa_tag_driver_array[i], owner);
पूर्ण

अटल व्योम dsa_tag_driver_unरेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver)
अणु
	mutex_lock(&dsa_tag_drivers_lock);
	list_del(&dsa_tag_driver->list);
	mutex_unlock(&dsa_tag_drivers_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_tag_drivers_रेजिस्टर);

व्योम dsa_tag_drivers_unरेजिस्टर(काष्ठा dsa_tag_driver *dsa_tag_driver_array[],
				अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		dsa_tag_driver_unरेजिस्टर(dsa_tag_driver_array[i]);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_tag_drivers_unरेजिस्टर);

स्थिर अक्षर *dsa_tag_protocol_to_str(स्थिर काष्ठा dsa_device_ops *ops)
अणु
	वापस ops->name;
पूर्ण;

/* Function takes a reference on the module owning the tagger,
 * so dsa_tag_driver_put must be called afterwards.
 */
स्थिर काष्ठा dsa_device_ops *dsa_find_tagger_by_name(स्थिर अक्षर *buf)
अणु
	स्थिर काष्ठा dsa_device_ops *ops = ERR_PTR(-ENOPROTOOPT);
	काष्ठा dsa_tag_driver *dsa_tag_driver;

	mutex_lock(&dsa_tag_drivers_lock);
	list_क्रम_each_entry(dsa_tag_driver, &dsa_tag_drivers_list, list) अणु
		स्थिर काष्ठा dsa_device_ops *पंचांगp = dsa_tag_driver->ops;

		अगर (!sysfs_streq(buf, पंचांगp->name))
			जारी;

		अगर (!try_module_get(dsa_tag_driver->owner))
			अवरोध;

		ops = पंचांगp;
		अवरोध;
	पूर्ण
	mutex_unlock(&dsa_tag_drivers_lock);

	वापस ops;
पूर्ण

स्थिर काष्ठा dsa_device_ops *dsa_tag_driver_get(पूर्णांक tag_protocol)
अणु
	काष्ठा dsa_tag_driver *dsa_tag_driver;
	स्थिर काष्ठा dsa_device_ops *ops;
	bool found = false;

	request_module("%s%d", DSA_TAG_DRIVER_ALIAS, tag_protocol);

	mutex_lock(&dsa_tag_drivers_lock);
	list_क्रम_each_entry(dsa_tag_driver, &dsa_tag_drivers_list, list) अणु
		ops = dsa_tag_driver->ops;
		अगर (ops->proto == tag_protocol) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		अगर (!try_module_get(dsa_tag_driver->owner))
			ops = ERR_PTR(-ENOPROTOOPT);
	पूर्ण अन्यथा अणु
		ops = ERR_PTR(-ENOPROTOOPT);
	पूर्ण

	mutex_unlock(&dsa_tag_drivers_lock);

	वापस ops;
पूर्ण

व्योम dsa_tag_driver_put(स्थिर काष्ठा dsa_device_ops *ops)
अणु
	काष्ठा dsa_tag_driver *dsa_tag_driver;

	mutex_lock(&dsa_tag_drivers_lock);
	list_क्रम_each_entry(dsa_tag_driver, &dsa_tag_drivers_list, list) अणु
		अगर (dsa_tag_driver->ops == ops) अणु
			module_put(dsa_tag_driver->owner);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&dsa_tag_drivers_lock);
पूर्ण

अटल पूर्णांक dev_is_class(काष्ठा device *dev, व्योम *class)
अणु
	अगर (dev->class != शून्य && !म_भेद(dev->class->name, class))
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा device *dev_find_class(काष्ठा device *parent, अक्षर *class)
अणु
	अगर (dev_is_class(parent, class)) अणु
		get_device(parent);
		वापस parent;
	पूर्ण

	वापस device_find_child(parent, class, dev_is_class);
पूर्ण

काष्ठा net_device *dsa_dev_to_net_device(काष्ठा device *dev)
अणु
	काष्ठा device *d;

	d = dev_find_class(dev, "net");
	अगर (d != शून्य) अणु
		काष्ठा net_device *nd;

		nd = to_net_dev(d);
		dev_hold(nd);
		put_device(d);

		वापस nd;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_dev_to_net_device);

/* Determine अगर we should defer delivery of skb until we have a rx बारtamp.
 *
 * Called from dsa_चयन_rcv. For now, this will only work अगर tagging is
 * enabled on the चयन. Normally the MAC driver would retrieve the hardware
 * बारtamp when it पढ़ोs the packet out of the hardware. However in a DSA
 * चयन, the DSA driver owning the पूर्णांकerface to which the packet is
 * delivered is never notअगरied unless we करो so here.
 */
अटल bool dsa_skb_defer_rx_बारtamp(काष्ठा dsa_slave_priv *p,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा dsa_चयन *ds = p->dp->ds;
	अचिन्हित पूर्णांक type;

	अगर (skb_headroom(skb) < ETH_HLEN)
		वापस false;

	__skb_push(skb, ETH_HLEN);

	type = ptp_classअगरy_raw(skb);

	__skb_pull(skb, ETH_HLEN);

	अगर (type == PTP_CLASS_NONE)
		वापस false;

	अगर (likely(ds->ops->port_rxtstamp))
		वापस ds->ops->port_rxtstamp(ds, p->dp->index, skb, type);

	वापस false;
पूर्ण

अटल पूर्णांक dsa_चयन_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा packet_type *pt, काष्ठा net_device *unused)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	काष्ठा sk_buff *nskb = शून्य;
	काष्ठा dsa_slave_priv *p;

	अगर (unlikely(!cpu_dp)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस 0;

	nskb = cpu_dp->rcv(skb, dev, pt);
	अगर (!nskb) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	skb = nskb;
	skb_push(skb, ETH_HLEN);
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, skb->dev);

	अगर (unlikely(!dsa_slave_dev_check(skb->dev))) अणु
		/* Packet is to be injected directly on an upper
		 * device, e.g. a team/bond, so skip all DSA-port
		 * specअगरic actions.
		 */
		netअगर_rx(skb);
		वापस 0;
	पूर्ण

	p = netdev_priv(skb->dev);

	अगर (unlikely(cpu_dp->ds->untag_bridge_pvid)) अणु
		nskb = dsa_untag_bridge_pvid(skb);
		अगर (!nskb) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
		skb = nskb;
	पूर्ण

	dev_sw_netstats_rx_add(skb->dev, skb->len);

	अगर (dsa_skb_defer_rx_बारtamp(p, skb))
		वापस 0;

	gro_cells_receive(&p->gcells, skb);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool dsa_is_port_initialized(काष्ठा dsa_चयन *ds, पूर्णांक p)
अणु
	स्थिर काष्ठा dsa_port *dp = dsa_to_port(ds, p);

	वापस dp->type == DSA_PORT_TYPE_USER && dp->slave;
पूर्ण

पूर्णांक dsa_चयन_suspend(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक i, ret = 0;

	/* Suspend slave network devices */
	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (!dsa_is_port_initialized(ds, i))
			जारी;

		ret = dsa_slave_suspend(dsa_to_port(ds, i)->slave);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ds->ops->suspend)
		ret = ds->ops->suspend(ds);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_चयन_suspend);

पूर्णांक dsa_चयन_resume(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक i, ret = 0;

	अगर (ds->ops->resume)
		ret = ds->ops->resume(ds);

	अगर (ret)
		वापस ret;

	/* Resume slave network devices */
	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (!dsa_is_port_initialized(ds, i))
			जारी;

		ret = dsa_slave_resume(dsa_to_port(ds, i)->slave);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_चयन_resume);
#पूर्ण_अगर

अटल काष्ठा packet_type dsa_pack_type __पढ़ो_mostly = अणु
	.type	= cpu_to_be16(ETH_P_XDSA),
	.func	= dsa_चयन_rcv,
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *dsa_owq;

bool dsa_schedule_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(dsa_owq, work);
पूर्ण

पूर्णांक dsa_devlink_param_get(काष्ठा devlink *dl, u32 id,
			  काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_param_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_param_get(ds, id, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_param_get);

पूर्णांक dsa_devlink_param_set(काष्ठा devlink *dl, u32 id,
			  काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_param_set)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_param_set(ds, id, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_param_set);

पूर्णांक dsa_devlink_params_रेजिस्टर(काष्ठा dsa_चयन *ds,
				स्थिर काष्ठा devlink_param *params,
				माप_प्रकार params_count)
अणु
	वापस devlink_params_रेजिस्टर(ds->devlink, params, params_count);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_params_रेजिस्टर);

व्योम dsa_devlink_params_unरेजिस्टर(काष्ठा dsa_चयन *ds,
				   स्थिर काष्ठा devlink_param *params,
				   माप_प्रकार params_count)
अणु
	devlink_params_unरेजिस्टर(ds->devlink, params, params_count);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_params_unरेजिस्टर);

पूर्णांक dsa_devlink_resource_रेजिस्टर(काष्ठा dsa_चयन *ds,
				  स्थिर अक्षर *resource_name,
				  u64 resource_size,
				  u64 resource_id,
				  u64 parent_resource_id,
				  स्थिर काष्ठा devlink_resource_size_params *size_params)
अणु
	वापस devlink_resource_रेजिस्टर(ds->devlink, resource_name,
					 resource_size, resource_id,
					 parent_resource_id,
					 size_params);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_resource_रेजिस्टर);

व्योम dsa_devlink_resources_unरेजिस्टर(काष्ठा dsa_चयन *ds)
अणु
	devlink_resources_unरेजिस्टर(ds->devlink, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_resources_unरेजिस्टर);

व्योम dsa_devlink_resource_occ_get_रेजिस्टर(काष्ठा dsa_चयन *ds,
					   u64 resource_id,
					   devlink_resource_occ_get_t *occ_get,
					   व्योम *occ_get_priv)
अणु
	वापस devlink_resource_occ_get_रेजिस्टर(ds->devlink, resource_id,
						 occ_get, occ_get_priv);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_resource_occ_get_रेजिस्टर);

व्योम dsa_devlink_resource_occ_get_unरेजिस्टर(काष्ठा dsa_चयन *ds,
					     u64 resource_id)
अणु
	devlink_resource_occ_get_unरेजिस्टर(ds->devlink, resource_id);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_resource_occ_get_unरेजिस्टर);

काष्ठा devlink_region *
dsa_devlink_region_create(काष्ठा dsa_चयन *ds,
			  स्थिर काष्ठा devlink_region_ops *ops,
			  u32 region_max_snapshots, u64 region_size)
अणु
	वापस devlink_region_create(ds->devlink, ops, region_max_snapshots,
				     region_size);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_region_create);

काष्ठा devlink_region *
dsa_devlink_port_region_create(काष्ठा dsa_चयन *ds,
			       पूर्णांक port,
			       स्थिर काष्ठा devlink_port_region_ops *ops,
			       u32 region_max_snapshots, u64 region_size)
अणु
	काष्ठा dsa_port *dp = dsa_to_port(ds, port);

	वापस devlink_port_region_create(&dp->devlink_port, ops,
					  region_max_snapshots,
					  region_size);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_port_region_create);

व्योम dsa_devlink_region_destroy(काष्ठा devlink_region *region)
अणु
	devlink_region_destroy(region);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_devlink_region_destroy);

काष्ठा dsa_port *dsa_port_from_netdev(काष्ठा net_device *netdev)
अणु
	अगर (!netdev || !dsa_slave_dev_check(netdev))
		वापस ERR_PTR(-ENODEV);

	वापस dsa_slave_to_port(netdev);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_port_from_netdev);

अटल पूर्णांक __init dsa_init_module(व्योम)
अणु
	पूर्णांक rc;

	dsa_owq = alloc_ordered_workqueue("dsa_ordered",
					  WQ_MEM_RECLAIM);
	अगर (!dsa_owq)
		वापस -ENOMEM;

	rc = dsa_slave_रेजिस्टर_notअगरier();
	अगर (rc)
		जाओ रेजिस्टर_notअगरier_fail;

	dev_add_pack(&dsa_pack_type);

	dsa_tag_driver_रेजिस्टर(&DSA_TAG_DRIVER_NAME(none_ops),
				THIS_MODULE);

	वापस 0;

रेजिस्टर_notअगरier_fail:
	destroy_workqueue(dsa_owq);

	वापस rc;
पूर्ण
module_init(dsa_init_module);

अटल व्योम __निकास dsa_cleanup_module(व्योम)
अणु
	dsa_tag_driver_unरेजिस्टर(&DSA_TAG_DRIVER_NAME(none_ops));

	dsa_slave_unरेजिस्टर_notअगरier();
	dev_हटाओ_pack(&dsa_pack_type);
	destroy_workqueue(dsa_owq);
पूर्ण
module_निकास(dsa_cleanup_module);

MODULE_AUTHOR("Lennert Buytenhek <buytenh@wantstofly.org>");
MODULE_DESCRIPTION("Driver for Distributed Switch Architecture switch chips");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dsa");
