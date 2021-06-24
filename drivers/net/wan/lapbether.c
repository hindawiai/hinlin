<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	"LAPB via ethernet" driver release 001
 *
 *	This code REQUIRES 2.1.15 or higher/ NET3.038
 *
 *	This is a "pseudo" network driver to allow LAPB over Ethernet.
 *
 *	This driver can use any ethernet destination address, and can be 
 *	limited to accept frames from one dedicated ethernet card only.
 *
 *	History
 *	LAPBETH 001	Jonathan Naylor		Cloned from bpqether.c
 *	2000-10-29	Henner Eisen	lapb_data_indication() वापस status.
 *	2000-11-14	Henner Eisen	dev_hold/put, NETDEV_GOING_DOWN support
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/lapb.h>
#समावेश <linux/init.h>

#समावेश <net/x25device.h>

अटल स्थिर u8 bcast_addr[6] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;

/* If this number is made larger, check that the temporary string buffer
 * in lapbeth_new_device is large enough to store the probe device name.*/
#घोषणा MAXLAPBDEV 100

काष्ठा lapbethdev अणु
	काष्ठा list_head	node;
	काष्ठा net_device	*ethdev;	/* link to ethernet device */
	काष्ठा net_device	*axdev;		/* lapbeth device (lapb#) */
	bool			up;
	spinlock_t		up_lock;	/* Protects "up" */
	काष्ठा sk_buff_head	rx_queue;
	काष्ठा napi_काष्ठा	napi;
पूर्ण;

अटल LIST_HEAD(lapbeth_devices);

अटल व्योम lapbeth_connected(काष्ठा net_device *dev, पूर्णांक reason);
अटल व्योम lapbeth_disconnected(काष्ठा net_device *dev, पूर्णांक reason);

/* ------------------------------------------------------------------------ */

/*
 *	Get the LAPB device क्रम the ethernet device
 */
अटल काष्ठा lapbethdev *lapbeth_get_x25_dev(काष्ठा net_device *dev)
अणु
	काष्ठा lapbethdev *lapbeth;

	list_क्रम_each_entry_rcu(lapbeth, &lapbeth_devices, node, lockdep_rtnl_is_held()) अणु
		अगर (lapbeth->ethdev == dev) 
			वापस lapbeth;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल __अंतरभूत__ पूर्णांक dev_is_ethdev(काष्ठा net_device *dev)
अणु
	वापस dev->type == ARPHRD_ETHER && म_भेदन(dev->name, "dummy", 5);
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lapbeth_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा lapbethdev *lapbeth = container_of(napi, काष्ठा lapbethdev,
						  napi);
	काष्ठा sk_buff *skb;
	पूर्णांक processed = 0;

	क्रम (; processed < budget; ++processed) अणु
		skb = skb_dequeue(&lapbeth->rx_queue);
		अगर (!skb)
			अवरोध;
		netअगर_receive_skb_core(skb);
	पूर्ण

	अगर (processed < budget)
		napi_complete(napi);

	वापस processed;
पूर्ण

/*
 *	Receive a LAPB frame via an ethernet पूर्णांकerface.
 */
अटल पूर्णांक lapbeth_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा packet_type *ptype, काष्ठा net_device *orig_dev)
अणु
	पूर्णांक len, err;
	काष्ठा lapbethdev *lapbeth;

	अगर (dev_net(dev) != &init_net)
		जाओ drop;

	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य)
		वापस NET_RX_DROP;

	अगर (!pskb_may_pull(skb, 2))
		जाओ drop;

	rcu_पढ़ो_lock();
	lapbeth = lapbeth_get_x25_dev(dev);
	अगर (!lapbeth)
		जाओ drop_unlock_rcu;
	spin_lock_bh(&lapbeth->up_lock);
	अगर (!lapbeth->up)
		जाओ drop_unlock;

	len = skb->data[0] + skb->data[1] * 256;
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	skb_pull(skb, 2);	/* Remove the length bytes */
	skb_trim(skb, len);	/* Set the length of the data */

	अगर ((err = lapb_data_received(lapbeth->axdev, skb)) != LAPB_OK) अणु
		prपूर्णांकk(KERN_DEBUG "lapbether: lapb_data_received err - %d\n", err);
		जाओ drop_unlock;
	पूर्ण
out:
	spin_unlock_bh(&lapbeth->up_lock);
	rcu_पढ़ो_unlock();
	वापस 0;
drop_unlock:
	kमुक्त_skb(skb);
	जाओ out;
drop_unlock_rcu:
	rcu_पढ़ो_unlock();
drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक lapbeth_data_indication(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	अचिन्हित अक्षर *ptr;

	अगर (skb_cow(skb, 1)) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	skb_push(skb, 1);

	ptr  = skb->data;
	*ptr = X25_IFACE_DATA;

	skb->protocol = x25_type_trans(skb, dev);

	skb_queue_tail(&lapbeth->rx_queue, skb);
	napi_schedule(&lapbeth->napi);
	वापस NET_RX_SUCCESS;
पूर्ण

/*
 *	Send a LAPB frame via an ethernet पूर्णांकerface
 */
अटल netdev_tx_t lapbeth_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	पूर्णांक err;

	spin_lock_bh(&lapbeth->up_lock);
	अगर (!lapbeth->up)
		जाओ drop;

	/* There should be a pseuकरो header of 1 byte added by upper layers.
	 * Check to make sure it is there beक्रमe पढ़ोing it.
	 */
	अगर (skb->len < 1)
		जाओ drop;

	चयन (skb->data[0]) अणु
	हाल X25_IFACE_DATA:
		अवरोध;
	हाल X25_IFACE_CONNECT:
		err = lapb_connect_request(dev);
		अगर (err == LAPB_CONNECTED)
			lapbeth_connected(dev, LAPB_OK);
		अन्यथा अगर (err != LAPB_OK)
			pr_err("lapb_connect_request error: %d\n", err);
		जाओ drop;
	हाल X25_IFACE_DISCONNECT:
		err = lapb_disconnect_request(dev);
		अगर (err == LAPB_NOTCONNECTED)
			lapbeth_disconnected(dev, LAPB_OK);
		अन्यथा अगर (err != LAPB_OK)
			pr_err("lapb_disconnect_request err: %d\n", err);
		fallthrough;
	शेष:
		जाओ drop;
	पूर्ण

	skb_pull(skb, 1);

	अगर ((err = lapb_data_request(dev, skb)) != LAPB_OK) अणु
		pr_err("lapb_data_request error - %d\n", err);
		जाओ drop;
	पूर्ण
out:
	spin_unlock_bh(&lapbeth->up_lock);
	वापस NETDEV_TX_OK;
drop:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

अटल व्योम lapbeth_data_transmit(काष्ठा net_device *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(ndev);
	अचिन्हित अक्षर *ptr;
	काष्ठा net_device *dev;
	पूर्णांक size = skb->len;

	ptr = skb_push(skb, 2);

	*ptr++ = size % 256;
	*ptr++ = size / 256;

	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += size;

	skb->dev = dev = lapbeth->ethdev;

	skb->protocol = htons(ETH_P_DEC);

	skb_reset_network_header(skb);

	dev_hard_header(skb, dev, ETH_P_DEC, bcast_addr, शून्य, 0);

	dev_queue_xmit(skb);
पूर्ण

अटल व्योम lapbeth_connected(काष्ठा net_device *dev, पूर्णांक reason)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	अचिन्हित अक्षर *ptr;
	काष्ठा sk_buff *skb = __dev_alloc_skb(1, GFP_ATOMIC | __GFP_NOMEMALLOC);

	अगर (!skb) अणु
		pr_err("out of memory\n");
		वापस;
	पूर्ण

	ptr  = skb_put(skb, 1);
	*ptr = X25_IFACE_CONNECT;

	skb->protocol = x25_type_trans(skb, dev);

	skb_queue_tail(&lapbeth->rx_queue, skb);
	napi_schedule(&lapbeth->napi);
पूर्ण

अटल व्योम lapbeth_disconnected(काष्ठा net_device *dev, पूर्णांक reason)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	अचिन्हित अक्षर *ptr;
	काष्ठा sk_buff *skb = __dev_alloc_skb(1, GFP_ATOMIC | __GFP_NOMEMALLOC);

	अगर (!skb) अणु
		pr_err("out of memory\n");
		वापस;
	पूर्ण

	ptr  = skb_put(skb, 1);
	*ptr = X25_IFACE_DISCONNECT;

	skb->protocol = x25_type_trans(skb, dev);

	skb_queue_tail(&lapbeth->rx_queue, skb);
	napi_schedule(&lapbeth->napi);
पूर्ण

/*
 *	Set AX.25 callsign
 */
अटल पूर्णांक lapbeth_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;
	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा lapb_रेजिस्टर_काष्ठा lapbeth_callbacks = अणु
	.connect_confirmation    = lapbeth_connected,
	.connect_indication      = lapbeth_connected,
	.disconnect_confirmation = lapbeth_disconnected,
	.disconnect_indication   = lapbeth_disconnected,
	.data_indication         = lapbeth_data_indication,
	.data_transmit           = lapbeth_data_transmit,
पूर्ण;

/*
 * खोलो/बंद a device
 */
अटल पूर्णांक lapbeth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	पूर्णांक err;

	napi_enable(&lapbeth->napi);

	अगर ((err = lapb_रेजिस्टर(dev, &lapbeth_callbacks)) != LAPB_OK) अणु
		pr_err("lapb_register error: %d\n", err);
		वापस -ENODEV;
	पूर्ण

	spin_lock_bh(&lapbeth->up_lock);
	lapbeth->up = true;
	spin_unlock_bh(&lapbeth->up_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lapbeth_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lapbethdev *lapbeth = netdev_priv(dev);
	पूर्णांक err;

	spin_lock_bh(&lapbeth->up_lock);
	lapbeth->up = false;
	spin_unlock_bh(&lapbeth->up_lock);

	अगर ((err = lapb_unरेजिस्टर(dev)) != LAPB_OK)
		pr_err("lapb_unregister error: %d\n", err);

	napi_disable(&lapbeth->napi);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल स्थिर काष्ठा net_device_ops lapbeth_netdev_ops = अणु
	.nकरो_खोलो	     = lapbeth_खोलो,
	.nकरो_stop	     = lapbeth_बंद,
	.nकरो_start_xmit	     = lapbeth_xmit,
	.nकरो_set_mac_address = lapbeth_set_mac_address,
पूर्ण;

अटल व्योम lapbeth_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops	     = &lapbeth_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->type            = ARPHRD_X25;
	dev->hard_header_len = 0;
	dev->mtu             = 1000;
	dev->addr_len        = 0;
पूर्ण

/*
 *	Setup a new device.
 */
अटल पूर्णांक lapbeth_new_device(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा lapbethdev *lapbeth;
	पूर्णांक rc = -ENOMEM;

	ASSERT_RTNL();

	ndev = alloc_netdev(माप(*lapbeth), "lapb%d", NET_NAME_UNKNOWN,
			    lapbeth_setup);
	अगर (!ndev)
		जाओ out;

	/* When transmitting data:
	 * first this driver हटाओs a pseuकरो header of 1 byte,
	 * then the lapb module prepends an LAPB header of at most 3 bytes,
	 * then this driver prepends a length field of 2 bytes,
	 * then the underlying Ethernet device prepends its own header.
	 */
	ndev->needed_headroom = -1 + 3 + 2 + dev->hard_header_len
					   + dev->needed_headroom;
	ndev->needed_tailroom = dev->needed_tailroom;

	lapbeth = netdev_priv(ndev);
	lapbeth->axdev = ndev;

	dev_hold(dev);
	lapbeth->ethdev = dev;

	lapbeth->up = false;
	spin_lock_init(&lapbeth->up_lock);

	skb_queue_head_init(&lapbeth->rx_queue);
	netअगर_napi_add(ndev, &lapbeth->napi, lapbeth_napi_poll, 16);

	rc = -EIO;
	अगर (रेजिस्टर_netdevice(ndev))
		जाओ fail;

	list_add_rcu(&lapbeth->node, &lapbeth_devices);
	rc = 0;
out:
	वापस rc;
fail:
	dev_put(dev);
	मुक्त_netdev(ndev);
	जाओ out;
पूर्ण

/*
 *	Free a lapb network device.
 */
अटल व्योम lapbeth_मुक्त_device(काष्ठा lapbethdev *lapbeth)
अणु
	dev_put(lapbeth->ethdev);
	list_del_rcu(&lapbeth->node);
	unरेजिस्टर_netdevice(lapbeth->axdev);
पूर्ण

/*
 *	Handle device status changes.
 *
 * Called from notअगरier with RTNL held.
 */
अटल पूर्णांक lapbeth_device_event(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा lapbethdev *lapbeth;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (dev_net(dev) != &init_net)
		वापस NOTIFY_DONE;

	अगर (!dev_is_ethdev(dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		/* New ethernet device -> new LAPB पूर्णांकerface	 */
		अगर (lapbeth_get_x25_dev(dev) == शून्य)
			lapbeth_new_device(dev);
		अवरोध;
	हाल NETDEV_GOING_DOWN:
		/* ethernet device बंदs -> बंद LAPB पूर्णांकerface */
		lapbeth = lapbeth_get_x25_dev(dev);
		अगर (lapbeth) 
			dev_बंद(lapbeth->axdev);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		/* ethernet device disappears -> हटाओ LAPB पूर्णांकerface */
		lapbeth = lapbeth_get_x25_dev(dev);
		अगर (lapbeth)
			lapbeth_मुक्त_device(lapbeth);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल काष्ठा packet_type lapbeth_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_DEC),
	.func = lapbeth_rcv,
पूर्ण;

अटल काष्ठा notअगरier_block lapbeth_dev_notअगरier = अणु
	.notअगरier_call = lapbeth_device_event,
पूर्ण;

अटल स्थिर अक्षर banner[] __initस्थिर =
	KERN_INFO "LAPB Ethernet driver version 0.02\n";

अटल पूर्णांक __init lapbeth_init_driver(व्योम)
अणु
	dev_add_pack(&lapbeth_packet_type);

	रेजिस्टर_netdevice_notअगरier(&lapbeth_dev_notअगरier);

	prपूर्णांकk(banner);

	वापस 0;
पूर्ण
module_init(lapbeth_init_driver);

अटल व्योम __निकास lapbeth_cleanup_driver(व्योम)
अणु
	काष्ठा lapbethdev *lapbeth;
	काष्ठा list_head *entry, *पंचांगp;

	dev_हटाओ_pack(&lapbeth_packet_type);
	unरेजिस्टर_netdevice_notअगरier(&lapbeth_dev_notअगरier);

	rtnl_lock();
	list_क्रम_each_safe(entry, पंचांगp, &lapbeth_devices) अणु
		lapbeth = list_entry(entry, काष्ठा lapbethdev, node);

		dev_put(lapbeth->ethdev);
		unरेजिस्टर_netdevice(lapbeth->axdev);
	पूर्ण
	rtnl_unlock();
पूर्ण
module_निकास(lapbeth_cleanup_driver);

MODULE_AUTHOR("Jonathan Naylor <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The unofficial LAPB over Ethernet driver");
MODULE_LICENSE("GPL");
