<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/etherdevice.h>
#समावेश "ipvlan.h"
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_tap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/compat.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/cache.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/fs.h>
#समावेश <linux/uपन.स>

#समावेश <net/net_namespace.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/sock.h>
#समावेश <linux/virtio_net.h>

#घोषणा TUN_OFFLOADS (NETIF_F_HW_CSUM | NETIF_F_TSO_ECN | NETIF_F_TSO | \
		      NETIF_F_TSO6)

अटल dev_t ipvtap_major;
अटल काष्ठा cdev ipvtap_cdev;

अटल स्थिर व्योम *ipvtap_net_namespace(काष्ठा device *d)
अणु
	काष्ठा net_device *dev = to_net_dev(d->parent);
	वापस dev_net(dev);
पूर्ण

अटल काष्ठा class ipvtap_class = अणु
	 .name = "ipvtap",
	 .owner = THIS_MODULE,
	 .ns_type = &net_ns_type_operations,
	 .namespace = ipvtap_net_namespace,
पूर्ण;

काष्ठा ipvtap_dev अणु
	काष्ठा ipvl_dev vlan;
	काष्ठा tap_dev	  tap;
पूर्ण;

अटल व्योम ipvtap_count_tx_dropped(काष्ठा tap_dev *tap)
अणु
	काष्ठा ipvtap_dev *vlantap = container_of(tap, काष्ठा ipvtap_dev, tap);
	काष्ठा ipvl_dev *vlan = &vlantap->vlan;

	this_cpu_inc(vlan->pcpu_stats->tx_drps);
पूर्ण

अटल व्योम ipvtap_count_rx_dropped(काष्ठा tap_dev *tap)
अणु
	काष्ठा ipvtap_dev *vlantap = container_of(tap, काष्ठा ipvtap_dev, tap);
	काष्ठा ipvl_dev *vlan = &vlantap->vlan;

	ipvlan_count_rx(vlan, 0, 0, 0);
पूर्ण

अटल व्योम ipvtap_update_features(काष्ठा tap_dev *tap,
				   netdev_features_t features)
अणु
	काष्ठा ipvtap_dev *vlantap = container_of(tap, काष्ठा ipvtap_dev, tap);
	काष्ठा ipvl_dev *vlan = &vlantap->vlan;

	vlan->sfeatures = features;
	netdev_update_features(vlan->dev);
पूर्ण

अटल पूर्णांक ipvtap_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipvtap_dev *vlantap = netdev_priv(dev);
	पूर्णांक err;

	INIT_LIST_HEAD(&vlantap->tap.queue_list);

	/* Since macvlan supports all offloads by शेष, make
	 * tap support all offloads also.
	 */
	vlantap->tap.tap_features = TUN_OFFLOADS;
	vlantap->tap.count_tx_dropped = ipvtap_count_tx_dropped;
	vlantap->tap.update_features =	ipvtap_update_features;
	vlantap->tap.count_rx_dropped = ipvtap_count_rx_dropped;

	err = netdev_rx_handler_रेजिस्टर(dev, tap_handle_frame, &vlantap->tap);
	अगर (err)
		वापस err;

	/* Don't put anything that may fail after macvlan_common_newlink
	 * because we can't unकरो what it करोes.
	 */
	err =  ipvlan_link_new(src_net, dev, tb, data, extack);
	अगर (err) अणु
		netdev_rx_handler_unरेजिस्टर(dev);
		वापस err;
	पूर्ण

	vlantap->tap.dev = vlantap->vlan.dev;

	वापस err;
पूर्ण

अटल व्योम ipvtap_dellink(काष्ठा net_device *dev,
			   काष्ठा list_head *head)
अणु
	काष्ठा ipvtap_dev *vlan = netdev_priv(dev);

	netdev_rx_handler_unरेजिस्टर(dev);
	tap_del_queues(&vlan->tap);
	ipvlan_link_delete(dev, head);
पूर्ण

अटल व्योम ipvtap_setup(काष्ठा net_device *dev)
अणु
	ipvlan_link_setup(dev);
	dev->tx_queue_len = TUN_READQ_SIZE;
	dev->priv_flags &= ~IFF_NO_QUEUE;
पूर्ण

अटल काष्ठा rtnl_link_ops ipvtap_link_ops __पढ़ो_mostly = अणु
	.kind		= "ipvtap",
	.setup		= ipvtap_setup,
	.newlink	= ipvtap_newlink,
	.dellink	= ipvtap_dellink,
	.priv_size	= माप(काष्ठा ipvtap_dev),
पूर्ण;

अटल पूर्णांक ipvtap_device_event(काष्ठा notअगरier_block *unused,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ipvtap_dev *vlantap;
	काष्ठा device *classdev;
	dev_t devt;
	पूर्णांक err;
	अक्षर tap_name[IFNAMSIZ];

	अगर (dev->rtnl_link_ops != &ipvtap_link_ops)
		वापस NOTIFY_DONE;

	snम_लिखो(tap_name, IFNAMSIZ, "tap%d", dev->अगरindex);
	vlantap = netdev_priv(dev);

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		/* Create the device node here after the network device has
		 * been रेजिस्टरed but beक्रमe रेजिस्टर_netdevice has
		 * finished running.
		 */
		err = tap_get_minor(ipvtap_major, &vlantap->tap);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);

		devt = MKDEV(MAJOR(ipvtap_major), vlantap->tap.minor);
		classdev = device_create(&ipvtap_class, &dev->dev, devt,
					 dev, tap_name);
		अगर (IS_ERR(classdev)) अणु
			tap_मुक्त_minor(ipvtap_major, &vlantap->tap);
			वापस notअगरier_from_त्रुटि_सं(PTR_ERR(classdev));
		पूर्ण
		err = sysfs_create_link(&dev->dev.kobj, &classdev->kobj,
					tap_name);
		अगर (err)
			वापस notअगरier_from_त्रुटि_सं(err);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* vlan->minor == 0 अगर NETDEV_REGISTER above failed */
		अगर (vlantap->tap.minor == 0)
			अवरोध;
		sysfs_हटाओ_link(&dev->dev.kobj, tap_name);
		devt = MKDEV(MAJOR(ipvtap_major), vlantap->tap.minor);
		device_destroy(&ipvtap_class, devt);
		tap_मुक्त_minor(ipvtap_major, &vlantap->tap);
		अवरोध;
	हाल NETDEV_CHANGE_TX_QUEUE_LEN:
		अगर (tap_queue_resize(&vlantap->tap))
			वापस NOTIFY_BAD;
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ipvtap_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call	= ipvtap_device_event,
पूर्ण;

अटल पूर्णांक ipvtap_init(व्योम)
अणु
	पूर्णांक err;

	err = tap_create_cdev(&ipvtap_cdev, &ipvtap_major, "ipvtap",
			      THIS_MODULE);
	अगर (err)
		जाओ out1;

	err = class_रेजिस्टर(&ipvtap_class);
	अगर (err)
		जाओ out2;

	err = रेजिस्टर_netdevice_notअगरier(&ipvtap_notअगरier_block);
	अगर (err)
		जाओ out3;

	err = ipvlan_link_रेजिस्टर(&ipvtap_link_ops);
	अगर (err)
		जाओ out4;

	वापस 0;

out4:
	unरेजिस्टर_netdevice_notअगरier(&ipvtap_notअगरier_block);
out3:
	class_unरेजिस्टर(&ipvtap_class);
out2:
	tap_destroy_cdev(ipvtap_major, &ipvtap_cdev);
out1:
	वापस err;
पूर्ण
module_init(ipvtap_init);

अटल व्योम ipvtap_निकास(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ipvtap_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&ipvtap_notअगरier_block);
	class_unरेजिस्टर(&ipvtap_class);
	tap_destroy_cdev(ipvtap_major, &ipvtap_cdev);
पूर्ण
module_निकास(ipvtap_निकास);
MODULE_ALIAS_RTNL_LINK("ipvtap");
MODULE_AUTHOR("Sainath Grandhi <sainath.grandhi@intel.com>");
MODULE_LICENSE("GPL");
