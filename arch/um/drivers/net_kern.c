<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश <irq_user.h>
#समावेश "mconsole_kern.h"
#समावेश <net_kern.h>
#समावेश <net_user.h>

#घोषणा DRIVER_NAME "uml-netdev"

अटल DEFINE_SPINLOCK(खोलोed_lock);
अटल LIST_HEAD(खोलोed);

/*
 * The drop_skb is used when we can't allocate an skb.  The
 * packet is पढ़ो पूर्णांकo drop_skb in order to get the data off the
 * connection to the host.
 * It is पुनः_स्मृतिated whenever a maximum packet size is seen which is
 * larger than any seen beक्रमe.  update_drop_skb is called from
 * eth_configure when a new पूर्णांकerface is added.
 */
अटल DEFINE_SPINLOCK(drop_lock);
अटल काष्ठा sk_buff *drop_skb;
अटल पूर्णांक drop_max;

अटल पूर्णांक update_drop_skb(पूर्णांक max)
अणु
	काष्ठा sk_buff *new;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&drop_lock, flags);

	अगर (max <= drop_max)
		जाओ out;

	err = -ENOMEM;
	new = dev_alloc_skb(max);
	अगर (new == शून्य)
		जाओ out;

	skb_put(new, max);

	kमुक्त_skb(drop_skb);
	drop_skb = new;
	drop_max = max;
	err = 0;
out:
	spin_unlock_irqrestore(&drop_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक uml_net_rx(काष्ठा net_device *dev)
अणु
	काष्ठा uml_net_निजी *lp = netdev_priv(dev);
	पूर्णांक pkt_len;
	काष्ठा sk_buff *skb;

	/* If we can't allocate memory, try again next round. */
	skb = dev_alloc_skb(lp->max_packet);
	अगर (skb == शून्य) अणु
		drop_skb->dev = dev;
		/* Read a packet पूर्णांकo drop_skb and करोn't करो anything with it. */
		(*lp->पढ़ो)(lp->fd, drop_skb, lp);
		dev->stats.rx_dropped++;
		वापस 0;
	पूर्ण

	skb->dev = dev;
	skb_put(skb, lp->max_packet);
	skb_reset_mac_header(skb);
	pkt_len = (*lp->पढ़ो)(lp->fd, skb, lp);

	अगर (pkt_len > 0) अणु
		skb_trim(skb, pkt_len);
		skb->protocol = (*lp->protocol)(skb);

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;
		netअगर_rx(skb);
		वापस pkt_len;
	पूर्ण

	kमुक्त_skb(skb);
	वापस pkt_len;
पूर्ण

अटल व्योम uml_dev_बंद(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uml_net_निजी *lp =
		container_of(work, काष्ठा uml_net_निजी, work);
	dev_बंद(lp->dev);
पूर्ण

अटल irqवापस_t uml_net_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा uml_net_निजी *lp = netdev_priv(dev);
	पूर्णांक err;

	अगर (!netअगर_running(dev))
		वापस IRQ_NONE;

	spin_lock(&lp->lock);
	जबतक ((err = uml_net_rx(dev)) > 0) ;
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR
		       "Device '%s' read returned %d, shutting it down\n",
		       dev->name, err);
		/* dev_बंद can't be called in पूर्णांकerrupt context, and takes
		 * again lp->lock.
		 * And dev_बंद() can be safely called multiple बार on the
		 * same device, since it tests क्रम (dev->flags & IFF_UP). So
		 * there's no harm in delaying the device shutकरोwn.
		 * Furthermore, the workqueue will not re-enqueue an alपढ़ोy
		 * enqueued work item. */
		schedule_work(&lp->work);
		जाओ out;
	पूर्ण
out:
	spin_unlock(&lp->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uml_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा uml_net_निजी *lp = netdev_priv(dev);
	पूर्णांक err;

	अगर (lp->fd >= 0) अणु
		err = -ENXIO;
		जाओ out;
	पूर्ण

	lp->fd = (*lp->खोलो)(&lp->user);
	अगर (lp->fd < 0) अणु
		err = lp->fd;
		जाओ out;
	पूर्ण

	err = um_request_irq(dev->irq, lp->fd, IRQ_READ, uml_net_पूर्णांकerrupt,
			     IRQF_SHARED, dev->name, dev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "uml_net_open: failed to get irq(%d)\n", err);
		err = -ENETUNREACH;
		जाओ out_बंद;
	पूर्ण

	netअगर_start_queue(dev);

	/* clear buffer - it can happen that the host side of the पूर्णांकerface
	 * is full when we get here.  In this हाल, new data is never queued,
	 * SIGIOs never arrive, and the net never works.
	 */
	जबतक ((err = uml_net_rx(dev)) > 0) ;

	spin_lock(&खोलोed_lock);
	list_add(&lp->list, &खोलोed);
	spin_unlock(&खोलोed_lock);

	वापस 0;
out_बंद:
	अगर (lp->बंद != शून्य) (*lp->बंद)(lp->fd, &lp->user);
	lp->fd = -1;
out:
	वापस err;
पूर्ण

अटल पूर्णांक uml_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा uml_net_निजी *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);

	um_मुक्त_irq(dev->irq, dev);
	अगर (lp->बंद != शून्य)
		(*lp->बंद)(lp->fd, &lp->user);
	lp->fd = -1;

	spin_lock(&खोलोed_lock);
	list_del(&lp->list);
	spin_unlock(&खोलोed_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक uml_net_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा uml_net_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक len;

	netअगर_stop_queue(dev);

	spin_lock_irqsave(&lp->lock, flags);

	len = (*lp->ग_लिखो)(lp->fd, skb, lp);
	skb_tx_बारtamp(skb);

	अगर (len == skb->len) अणु
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
		netअगर_trans_update(dev);
		netअगर_start_queue(dev);

		/* this is normally करोne in the पूर्णांकerrupt when tx finishes */
		netअगर_wake_queue(dev);
	पूर्ण
	अन्यथा अगर (len == 0) अणु
		netअगर_start_queue(dev);
		dev->stats.tx_dropped++;
	पूर्ण
	अन्यथा अणु
		netअगर_start_queue(dev);
		prपूर्णांकk(KERN_ERR "uml_net_start_xmit: failed(%d)\n", len);
	पूर्ण

	spin_unlock_irqrestore(&lp->lock, flags);

	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम uml_net_set_multicast_list(काष्ठा net_device *dev)
अणु
	वापस;
पूर्ण

अटल व्योम uml_net_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम uml_net_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	uml_net_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम uml_net_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops uml_net_ethtool_ops = अणु
	.get_drvinfo	= uml_net_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_ts_info	= ethtool_op_get_ts_info,
पूर्ण;

व्योम uml_net_setup_etheraddr(काष्ठा net_device *dev, अक्षर *str)
अणु
	अचिन्हित अक्षर *addr = dev->dev_addr;
	अक्षर *end;
	पूर्णांक i;

	अगर (str == शून्य)
		जाओ अक्रमom;

	क्रम (i = 0; i < 6; i++) अणु
		addr[i] = simple_म_से_अदीर्घ(str, &end, 16);
		अगर ((end == str) ||
		   ((*end != ':') && (*end != ',') && (*end != '\0'))) अणु
			prपूर्णांकk(KERN_ERR
			       "setup_etheraddr: failed to parse '%s' "
			       "as an ethernet address\n", str);
			जाओ अक्रमom;
		पूर्ण
		str = end + 1;
	पूर्ण
	अगर (is_multicast_ether_addr(addr)) अणु
		prपूर्णांकk(KERN_ERR
		       "Attempt to assign a multicast ethernet address to a "
		       "device disallowed\n");
		जाओ अक्रमom;
	पूर्ण
	अगर (!is_valid_ether_addr(addr)) अणु
		prपूर्णांकk(KERN_ERR
		       "Attempt to assign an invalid ethernet address to a "
		       "device disallowed\n");
		जाओ अक्रमom;
	पूर्ण
	अगर (!is_local_ether_addr(addr)) अणु
		prपूर्णांकk(KERN_WARNING
		       "Warning: Assigning a globally valid ethernet "
		       "address to a device\n");
		prपूर्णांकk(KERN_WARNING "You should set the 2nd rightmost bit in "
		       "the first byte of the MAC,\n");
		prपूर्णांकk(KERN_WARNING "i.e. %02x:%02x:%02x:%02x:%02x:%02x\n",
		       addr[0] | 0x02, addr[1], addr[2], addr[3], addr[4],
		       addr[5]);
	पूर्ण
	वापस;

अक्रमom:
	prपूर्णांकk(KERN_INFO
	       "Choosing a random ethernet address for device %s\n", dev->name);
	eth_hw_addr_अक्रमom(dev);
पूर्ण

अटल DEFINE_SPINLOCK(devices_lock);
अटल LIST_HEAD(devices);

अटल काष्ठा platक्रमm_driver uml_net_driver = अणु
	.driver = अणु
		.name  = DRIVER_NAME,
	पूर्ण,
पूर्ण;

अटल व्योम net_device_release(काष्ठा device *dev)
अणु
	काष्ठा uml_net *device = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = device->dev;
	काष्ठा uml_net_निजी *lp = netdev_priv(netdev);

	अगर (lp->हटाओ != शून्य)
		(*lp->हटाओ)(&lp->user);
	list_del(&device->list);
	kमुक्त(device);
	मुक्त_netdev(netdev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops uml_netdev_ops = अणु
	.nकरो_खोलो 		= uml_net_खोलो,
	.nकरो_stop 		= uml_net_बंद,
	.nकरो_start_xmit 	= uml_net_start_xmit,
	.nकरो_set_rx_mode	= uml_net_set_multicast_list,
	.nकरो_tx_समयout 	= uml_net_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = uml_net_poll_controller,
#पूर्ण_अगर
पूर्ण;

/*
 * Ensures that platक्रमm_driver_रेजिस्टर is called only once by
 * eth_configure.  Will be set in an initcall.
 */
अटल पूर्णांक driver_रेजिस्टरed;

अटल व्योम eth_configure(पूर्णांक n, व्योम *init, अक्षर *mac,
			  काष्ठा transport *transport, gfp_t gfp_mask)
अणु
	काष्ठा uml_net *device;
	काष्ठा net_device *dev;
	काष्ठा uml_net_निजी *lp;
	पूर्णांक err, size;

	size = transport->निजी_size + माप(काष्ठा uml_net_निजी);

	device = kzalloc(माप(*device), gfp_mask);
	अगर (device == शून्य) अणु
		prपूर्णांकk(KERN_ERR "eth_configure failed to allocate struct "
		       "uml_net\n");
		वापस;
	पूर्ण

	dev = alloc_etherdev(size);
	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "eth_configure: failed to allocate struct "
		       "net_device for eth%d\n", n);
		जाओ out_मुक्त_device;
	पूर्ण

	INIT_LIST_HEAD(&device->list);
	device->index = n;

	/* If this name ends up conflicting with an existing रेजिस्टरed
	 * netdevice, that is OK, रेजिस्टर_netdevअणु,iceपूर्ण() will notice this
	 * and fail.
	 */
	snम_लिखो(dev->name, माप(dev->name), "eth%d", n);

	uml_net_setup_etheraddr(dev, mac);

	prपूर्णांकk(KERN_INFO "Netdevice %d (%pM) : ", n, dev->dev_addr);

	lp = netdev_priv(dev);
	/* This poपूर्णांकs to the transport निजी data. It's still clear, but we
	 * must स_रखो it to 0 *now*. Let's help the drivers. */
	स_रखो(lp, 0, size);
	INIT_WORK(&lp->work, uml_dev_बंद);

	/* sysfs रेजिस्टर */
	अगर (!driver_रेजिस्टरed) अणु
		platक्रमm_driver_रेजिस्टर(&uml_net_driver);
		driver_रेजिस्टरed = 1;
	पूर्ण
	device->pdev.id = n;
	device->pdev.name = DRIVER_NAME;
	device->pdev.dev.release = net_device_release;
	dev_set_drvdata(&device->pdev.dev, device);
	अगर (platक्रमm_device_रेजिस्टर(&device->pdev))
		जाओ out_मुक्त_netdev;
	SET_NETDEV_DEV(dev,&device->pdev.dev);

	device->dev = dev;

	/*
	 * These just fill in a data काष्ठाure, so there's no failure
	 * to be worried about.
	 */
	(*transport->kern->init)(dev, init);

	*lp = ((काष्ठा uml_net_निजी)
		अणु .list  		= LIST_HEAD_INIT(lp->list),
		  .dev 			= dev,
		  .fd 			= -1,
		  .mac 			= अणु 0xfe, 0xfd, 0x0, 0x0, 0x0, 0x0पूर्ण,
		  .max_packet		= transport->user->max_packet,
		  .protocol 		= transport->kern->protocol,
		  .खोलो 		= transport->user->खोलो,
		  .बंद 		= transport->user->बंद,
		  .हटाओ 		= transport->user->हटाओ,
		  .पढ़ो 		= transport->kern->पढ़ो,
		  .ग_लिखो 		= transport->kern->ग_लिखो,
		  .add_address 		= transport->user->add_address,
		  .delete_address  	= transport->user->delete_address पूर्ण);

	spin_lock_init(&lp->lock);
	स_नकल(lp->mac, dev->dev_addr, माप(lp->mac));

	अगर ((transport->user->init != शून्य) &&
	    ((*transport->user->init)(&lp->user, dev) != 0))
		जाओ out_unरेजिस्टर;

	dev->mtu = transport->user->mtu;
	dev->netdev_ops = &uml_netdev_ops;
	dev->ethtool_ops = &uml_net_ethtool_ops;
	dev->watchकरोg_समयo = (HZ >> 1);
	dev->irq = UM_ETH_IRQ;

	err = update_drop_skb(lp->max_packet);
	अगर (err)
		जाओ out_unकरो_user_init;

	rtnl_lock();
	err = रेजिस्टर_netdevice(dev);
	rtnl_unlock();
	अगर (err)
		जाओ out_unकरो_user_init;

	spin_lock(&devices_lock);
	list_add(&device->list, &devices);
	spin_unlock(&devices_lock);

	वापस;

out_unकरो_user_init:
	अगर (transport->user->हटाओ != शून्य)
		(*transport->user->हटाओ)(&lp->user);
out_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(&device->pdev);
	वापस; /* platक्रमm_device_unरेजिस्टर मुक्तs dev and device */
out_मुक्त_netdev:
	मुक्त_netdev(dev);
out_मुक्त_device:
	kमुक्त(device);
पूर्ण

अटल काष्ठा uml_net *find_device(पूर्णांक n)
अणु
	काष्ठा uml_net *device;
	काष्ठा list_head *ele;

	spin_lock(&devices_lock);
	list_क्रम_each(ele, &devices) अणु
		device = list_entry(ele, काष्ठा uml_net, list);
		अगर (device->index == n)
			जाओ out;
	पूर्ण
	device = शून्य;
 out:
	spin_unlock(&devices_lock);
	वापस device;
पूर्ण

अटल पूर्णांक eth_parse(अक्षर *str, पूर्णांक *index_out, अक्षर **str_out,
		     अक्षर **error_out)
अणु
	अक्षर *end;
	पूर्णांक n, err = -EINVAL;

	n = simple_म_से_अदीर्घ(str, &end, 0);
	अगर (end == str) अणु
		*error_out = "Bad device number";
		वापस err;
	पूर्ण

	str = end;
	अगर (*str != '=') अणु
		*error_out = "Expected '=' after device number";
		वापस err;
	पूर्ण

	str++;
	अगर (find_device(n)) अणु
		*error_out = "Device already configured";
		वापस err;
	पूर्ण

	*index_out = n;
	*str_out = str;
	वापस 0;
पूर्ण

काष्ठा eth_init अणु
	काष्ठा list_head list;
	अक्षर *init;
	पूर्णांक index;
पूर्ण;

अटल DEFINE_SPINLOCK(transports_lock);
अटल LIST_HEAD(transports);

/* Filled in during early boot */
अटल LIST_HEAD(eth_cmd_line);

अटल पूर्णांक check_transport(काष्ठा transport *transport, अक्षर *eth, पूर्णांक n,
			   व्योम **init_out, अक्षर **mac_out, gfp_t gfp_mask)
अणु
	पूर्णांक len;

	len = म_माप(transport->name);
	अगर (म_भेदन(eth, transport->name, len))
		वापस 0;

	eth += len;
	अगर (*eth == ',')
		eth++;
	अन्यथा अगर (*eth != '\0')
		वापस 0;

	*init_out = kदो_स्मृति(transport->setup_size, gfp_mask);
	अगर (*init_out == शून्य)
		वापस 1;

	अगर (!transport->setup(eth, mac_out, *init_out)) अणु
		kमुक्त(*init_out);
		*init_out = शून्य;
	पूर्ण
	वापस 1;
पूर्ण

व्योम रेजिस्टर_transport(काष्ठा transport *new)
अणु
	काष्ठा list_head *ele, *next;
	काष्ठा eth_init *eth;
	व्योम *init;
	अक्षर *mac = शून्य;
	पूर्णांक match;

	spin_lock(&transports_lock);
	BUG_ON(!list_empty(&new->list));
	list_add(&new->list, &transports);
	spin_unlock(&transports_lock);

	list_क्रम_each_safe(ele, next, &eth_cmd_line) अणु
		eth = list_entry(ele, काष्ठा eth_init, list);
		match = check_transport(new, eth->init, eth->index, &init,
					&mac, GFP_KERNEL);
		अगर (!match)
			जारी;
		अन्यथा अगर (init != शून्य) अणु
			eth_configure(eth->index, init, mac, new, GFP_KERNEL);
			kमुक्त(init);
		पूर्ण
		list_del(&eth->list);
	पूर्ण
पूर्ण

अटल पूर्णांक eth_setup_common(अक्षर *str, पूर्णांक index)
अणु
	काष्ठा list_head *ele;
	काष्ठा transport *transport;
	व्योम *init;
	अक्षर *mac = शून्य;
	पूर्णांक found = 0;

	spin_lock(&transports_lock);
	list_क्रम_each(ele, &transports) अणु
		transport = list_entry(ele, काष्ठा transport, list);
	        अगर (!check_transport(transport, str, index, &init,
					&mac, GFP_ATOMIC))
			जारी;
		अगर (init != शून्य) अणु
			eth_configure(index, init, mac, transport, GFP_ATOMIC);
			kमुक्त(init);
		पूर्ण
		found = 1;
		अवरोध;
	पूर्ण

	spin_unlock(&transports_lock);
	वापस found;
पूर्ण

अटल पूर्णांक __init eth_setup(अक्षर *str)
अणु
	काष्ठा eth_init *new;
	अक्षर *error;
	पूर्णांक n, err;

	err = eth_parse(str, &n, &str, &error);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "eth_setup - Couldn't parse '%s' : %s\n",
		       str, error);
		वापस 1;
	पूर्ण

	new = memblock_alloc(माप(*new), SMP_CACHE_BYTES);
	अगर (!new)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*new));

	INIT_LIST_HEAD(&new->list);
	new->index = n;
	new->init = str;

	list_add_tail(&new->list, &eth_cmd_line);
	वापस 1;
पूर्ण

__setup("eth", eth_setup);
__uml_help(eth_setup,
"eth[0-9]+=<transport>,<options>\n"
"    Configure a network device.\n\n"
);

अटल पूर्णांक net_config(अक्षर *str, अक्षर **error_out)
अणु
	पूर्णांक n, err;

	err = eth_parse(str, &n, &str, error_out);
	अगर (err)
		वापस err;

	/* This string is broken up and the pieces used by the underlying
	 * driver.  So, it is मुक्तd only अगर eth_setup_common fails.
	 */
	str = kstrdup(str, GFP_KERNEL);
	अगर (str == शून्य) अणु
	        *error_out = "net_config failed to strdup string";
		वापस -ENOMEM;
	पूर्ण
	err = !eth_setup_common(str, n);
	अगर (err)
		kमुक्त(str);
	वापस err;
पूर्ण

अटल पूर्णांक net_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out)
अणु
	अक्षर *end;
	पूर्णांक n;

	n = simple_म_से_अदीर्घ(*str, &end, 0);
	अगर ((*end != '\0') || (end == *str))
		वापस -1;

	*start_out = n;
	*end_out = n;
	*str = end;
	वापस n;
पूर्ण

अटल पूर्णांक net_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	काष्ठा uml_net *device;
	काष्ठा net_device *dev;
	काष्ठा uml_net_निजी *lp;

	device = find_device(n);
	अगर (device == शून्य)
		वापस -ENODEV;

	dev = device->dev;
	lp = netdev_priv(dev);
	अगर (lp->fd > 0)
		वापस -EBUSY;
	unरेजिस्टर_netdev(dev);
	platक्रमm_device_unरेजिस्टर(&device->pdev);

	वापस 0;
पूर्ण

अटल काष्ठा mc_device net_mc = अणु
	.list		= LIST_HEAD_INIT(net_mc.list),
	.name		= "eth",
	.config		= net_config,
	.get_config	= शून्य,
	.id		= net_id,
	.हटाओ		= net_हटाओ,
पूर्ण;

#अगर_घोषित CONFIG_INET
अटल पूर्णांक uml_inetaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			      व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा uml_net_निजी *lp;
	व्योम (*proc)(अचिन्हित अक्षर *, अचिन्हित अक्षर *, व्योम *);
	अचिन्हित अक्षर addr_buf[4], neपंचांगask_buf[4];

	अगर (dev->netdev_ops->nकरो_खोलो != uml_net_खोलो)
		वापस NOTIFY_DONE;

	lp = netdev_priv(dev);

	proc = शून्य;
	चयन (event) अणु
	हाल NETDEV_UP:
		proc = lp->add_address;
		अवरोध;
	हाल NETDEV_DOWN:
		proc = lp->delete_address;
		अवरोध;
	पूर्ण
	अगर (proc != शून्य) अणु
		स_नकल(addr_buf, &अगरa->अगरa_address, माप(addr_buf));
		स_नकल(neपंचांगask_buf, &अगरa->अगरa_mask, माप(neपंचांगask_buf));
		(*proc)(addr_buf, neपंचांगask_buf, &lp->user);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/* uml_net_init shouldn't be called twice on two CPUs at the same समय */
अटल काष्ठा notअगरier_block uml_inetaddr_notअगरier = अणु
	.notअगरier_call		= uml_inetaddr_event,
पूर्ण;

अटल व्योम inet_रेजिस्टर(व्योम)
अणु
	काष्ठा list_head *ele;
	काष्ठा uml_net_निजी *lp;
	काष्ठा in_device *ip;
	काष्ठा in_अगरaddr *in;

	रेजिस्टर_inetaddr_notअगरier(&uml_inetaddr_notअगरier);

	/* Devices may have been खोलोed alपढ़ोy, so the uml_inetaddr_notअगरier
	 * didn't get a chance to run क्रम them.  This fakes it so that
	 * addresses which have alपढ़ोy been set up get handled properly.
	 */
	spin_lock(&खोलोed_lock);
	list_क्रम_each(ele, &खोलोed) अणु
		lp = list_entry(ele, काष्ठा uml_net_निजी, list);
		ip = lp->dev->ip_ptr;
		अगर (ip == शून्य)
			जारी;
		in = ip->अगरa_list;
		जबतक (in != शून्य) अणु
			uml_inetaddr_event(शून्य, NETDEV_UP, in);
			in = in->अगरa_next;
		पूर्ण
	पूर्ण
	spin_unlock(&खोलोed_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम inet_रेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uml_net_init(व्योम)
अणु
	mconsole_रेजिस्टर_dev(&net_mc);
	inet_रेजिस्टर();
	वापस 0;
पूर्ण

__initcall(uml_net_init);

अटल व्योम बंद_devices(व्योम)
अणु
	काष्ठा list_head *ele;
	काष्ठा uml_net_निजी *lp;

	spin_lock(&खोलोed_lock);
	list_क्रम_each(ele, &खोलोed) अणु
		lp = list_entry(ele, काष्ठा uml_net_निजी, list);
		um_मुक्त_irq(lp->dev->irq, lp->dev);
		अगर ((lp->बंद != शून्य) && (lp->fd >= 0))
			(*lp->बंद)(lp->fd, &lp->user);
		अगर (lp->हटाओ != शून्य)
			(*lp->हटाओ)(&lp->user);
	पूर्ण
	spin_unlock(&खोलोed_lock);
पूर्ण

__uml_निकासcall(बंद_devices);

व्योम iter_addresses(व्योम *d, व्योम (*cb)(अचिन्हित अक्षर *, अचिन्हित अक्षर *,
					व्योम *),
		    व्योम *arg)
अणु
	काष्ठा net_device *dev = d;
	काष्ठा in_device *ip = dev->ip_ptr;
	काष्ठा in_अगरaddr *in;
	अचिन्हित अक्षर address[4], neपंचांगask[4];

	अगर (ip == शून्य) वापस;
	in = ip->अगरa_list;
	जबतक (in != शून्य) अणु
		स_नकल(address, &in->अगरa_address, माप(address));
		स_नकल(neपंचांगask, &in->अगरa_mask, माप(neपंचांगask));
		(*cb)(address, neपंचांगask, arg);
		in = in->अगरa_next;
	पूर्ण
पूर्ण

पूर्णांक dev_neपंचांगask(व्योम *d, व्योम *m)
अणु
	काष्ठा net_device *dev = d;
	काष्ठा in_device *ip = dev->ip_ptr;
	काष्ठा in_अगरaddr *in;
	__be32 *mask_out = m;

	अगर (ip == शून्य)
		वापस 1;

	in = ip->अगरa_list;
	अगर (in == शून्य)
		वापस 1;

	*mask_out = in->अगरa_mask;
	वापस 0;
पूर्ण

व्योम *get_output_buffer(पूर्णांक *len_out)
अणु
	व्योम *ret;

	ret = (व्योम *) __get_मुक्त_pages(GFP_KERNEL, 0);
	अगर (ret) *len_out = PAGE_SIZE;
	अन्यथा *len_out = 0;
	वापस ret;
पूर्ण

व्योम मुक्त_output_buffer(व्योम *buffer)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) buffer, 0);
पूर्ण

पूर्णांक tap_setup_common(अक्षर *str, अक्षर *type, अक्षर **dev_name, अक्षर **mac_out,
		     अक्षर **gate_addr)
अणु
	अक्षर *reमुख्य;

	reमुख्य = split_अगर_spec(str, dev_name, mac_out, gate_addr, शून्य);
	अगर (reमुख्य != शून्य) अणु
		prपूर्णांकk(KERN_ERR "tap_setup_common - Extra garbage on "
		       "specification : '%s'\n", reमुख्य);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित लघु eth_protocol(काष्ठा sk_buff *skb)
अणु
	वापस eth_type_trans(skb, skb->dev);
पूर्ण
