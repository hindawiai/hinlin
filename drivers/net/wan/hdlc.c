<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 *
 * Copyright (C) 1999 - 2008 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * Currently supported:
 *	* raw IP-in-HDLC
 *	* Cisco HDLC
 *	* Frame Relay with ANSI or CCITT LMI (both user and network side)
 *	* PPP
 *	* X.25
 *
 * Use sethdlc utility to set line parameters, protocol and PVCs
 *
 * How करोes it work:
 * - proto->खोलो(), बंद(), start(), stop() calls are serialized.
 *   The order is: खोलो, [ start, stop ... ] बंद ...
 * - proto->start() and stop() are called with spin_lock_irq held.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hdlc.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>


अटल स्थिर अक्षर* version = "HDLC support module revision 1.22";

#अघोषित DEBUG_LINK

अटल काष्ठा hdlc_proto *first_proto;

अटल पूर्णांक hdlc_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    काष्ठा packet_type *p, काष्ठा net_device *orig_dev)
अणु
	काष्ठा hdlc_device *hdlc;

	/* First make sure "dev" is an HDLC device */
	अगर (!(dev->priv_flags & IFF_WAN_HDLC)) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	hdlc = dev_to_hdlc(dev);

	अगर (!net_eq(dev_net(dev), &init_net)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	BUG_ON(!hdlc->proto->netअगर_rx);
	वापस hdlc->proto->netअगर_rx(skb);
पूर्ण

netdev_tx_t hdlc_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);

	अगर (hdlc->proto->xmit)
		वापस hdlc->proto->xmit(skb, dev);

	वापस hdlc->xmit(skb, dev); /* call hardware driver directly */
पूर्ण

अटल अंतरभूत व्योम hdlc_proto_start(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	अगर (hdlc->proto->start)
		hdlc->proto->start(dev);
पूर्ण



अटल अंतरभूत व्योम hdlc_proto_stop(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	अगर (hdlc->proto->stop)
		hdlc->proto->stop(dev);
पूर्ण



अटल पूर्णांक hdlc_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	hdlc_device *hdlc;
	अचिन्हित दीर्घ flags;
	पूर्णांक on;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (!(dev->priv_flags & IFF_WAN_HDLC))
		वापस NOTIFY_DONE; /* not an HDLC device */

	अगर (event != NETDEV_CHANGE)
		वापस NOTIFY_DONE; /* Only पूर्णांकerested in carrier changes */

	on = netअगर_carrier_ok(dev);

#अगर_घोषित DEBUG_LINK
	prपूर्णांकk(KERN_DEBUG "%s: hdlc_device_event NETDEV_CHANGE, carrier %i\n",
	       dev->name, on);
#पूर्ण_अगर

	hdlc = dev_to_hdlc(dev);
	spin_lock_irqsave(&hdlc->state_lock, flags);

	अगर (hdlc->carrier == on)
		जाओ carrier_निकास; /* no change in DCD line level */

	hdlc->carrier = on;

	अगर (!hdlc->खोलो)
		जाओ carrier_निकास;

	अगर (hdlc->carrier) अणु
		netdev_info(dev, "Carrier detected\n");
		hdlc_proto_start(dev);
	पूर्ण अन्यथा अणु
		netdev_info(dev, "Carrier lost\n");
		hdlc_proto_stop(dev);
	पूर्ण

carrier_निकास:
	spin_unlock_irqrestore(&hdlc->state_lock, flags);
	वापस NOTIFY_DONE;
पूर्ण



/* Must be called by hardware driver when HDLC device is being खोलोed */
पूर्णांक hdlc_खोलो(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
#अगर_घोषित DEBUG_LINK
	prपूर्णांकk(KERN_DEBUG "%s: hdlc_open() carrier %i open %i\n", dev->name,
	       hdlc->carrier, hdlc->खोलो);
#पूर्ण_अगर

	अगर (hdlc->proto == शून्य)
		वापस -ENOSYS;	/* no protocol attached */

	अगर (hdlc->proto->खोलो) अणु
		पूर्णांक result = hdlc->proto->खोलो(dev);
		अगर (result)
			वापस result;
	पूर्ण

	spin_lock_irq(&hdlc->state_lock);

	अगर (hdlc->carrier) अणु
		netdev_info(dev, "Carrier detected\n");
		hdlc_proto_start(dev);
	पूर्ण अन्यथा
		netdev_info(dev, "No carrier\n");

	hdlc->खोलो = 1;

	spin_unlock_irq(&hdlc->state_lock);
	वापस 0;
पूर्ण



/* Must be called by hardware driver when HDLC device is being बंदd */
व्योम hdlc_बंद(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
#अगर_घोषित DEBUG_LINK
	prपूर्णांकk(KERN_DEBUG "%s: hdlc_close() carrier %i open %i\n", dev->name,
	       hdlc->carrier, hdlc->खोलो);
#पूर्ण_अगर

	spin_lock_irq(&hdlc->state_lock);

	hdlc->खोलो = 0;
	अगर (hdlc->carrier)
		hdlc_proto_stop(dev);

	spin_unlock_irq(&hdlc->state_lock);

	अगर (hdlc->proto->बंद)
		hdlc->proto->बंद(dev);
पूर्ण



पूर्णांक hdlc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा hdlc_proto *proto = first_proto;
	पूर्णांक result;

	अगर (cmd != SIOCWANDEV)
		वापस -EINVAL;

	अगर (dev_to_hdlc(dev)->proto) अणु
		result = dev_to_hdlc(dev)->proto->ioctl(dev, अगरr);
		अगर (result != -EINVAL)
			वापस result;
	पूर्ण

	/* Not handled by currently attached protocol (अगर any) */

	जबतक (proto) अणु
		अगर ((result = proto->ioctl(dev, अगरr)) != -EINVAL)
			वापस result;
		proto = proto->next;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा header_ops hdlc_null_ops;

अटल व्योम hdlc_setup_dev(काष्ठा net_device *dev)
अणु
	/* Re-init all variables changed by HDLC protocol drivers,
	 * including ether_setup() called from hdlc_raw_eth.c.
	 */
	dev->flags		 = IFF_POINTOPOINT | IFF_NOARP;
	dev->priv_flags		 = IFF_WAN_HDLC;
	dev->mtu		 = HDLC_MAX_MTU;
	dev->min_mtu		 = 68;
	dev->max_mtu		 = HDLC_MAX_MTU;
	dev->type		 = ARPHRD_RAWHDLC;
	dev->hard_header_len	 = 0;
	dev->needed_headroom	 = 0;
	dev->addr_len		 = 0;
	dev->header_ops		 = &hdlc_null_ops;
पूर्ण

अटल व्योम hdlc_setup(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);

	hdlc_setup_dev(dev);
	hdlc->carrier = 1;
	hdlc->खोलो = 0;
	spin_lock_init(&hdlc->state_lock);
पूर्ण

काष्ठा net_device *alloc_hdlcdev(व्योम *priv)
अणु
	काष्ठा net_device *dev;
	dev = alloc_netdev(माप(काष्ठा hdlc_device), "hdlc%d",
			   NET_NAME_UNKNOWN, hdlc_setup);
	अगर (dev)
		dev_to_hdlc(dev)->priv = priv;
	वापस dev;
पूर्ण

व्योम unरेजिस्टर_hdlc_device(काष्ठा net_device *dev)
अणु
	rtnl_lock();
	detach_hdlc_protocol(dev);
	unरेजिस्टर_netdevice(dev);
	rtnl_unlock();
पूर्ण



पूर्णांक attach_hdlc_protocol(काष्ठा net_device *dev, काष्ठा hdlc_proto *proto,
			 माप_प्रकार size)
अणु
	पूर्णांक err;

	err = detach_hdlc_protocol(dev);
	अगर (err)
		वापस err;

	अगर (!try_module_get(proto->module))
		वापस -ENOSYS;

	अगर (size) अणु
		dev_to_hdlc(dev)->state = kदो_स्मृति(size, GFP_KERNEL);
		अगर (dev_to_hdlc(dev)->state == शून्य) अणु
			module_put(proto->module);
			वापस -ENOBUFS;
		पूर्ण
	पूर्ण
	dev_to_hdlc(dev)->proto = proto;

	वापस 0;
पूर्ण


पूर्णांक detach_hdlc_protocol(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	पूर्णांक err;

	अगर (hdlc->proto) अणु
		err = call_netdevice_notअगरiers(NETDEV_PRE_TYPE_CHANGE, dev);
		err = notअगरier_to_त्रुटि_सं(err);
		अगर (err) अणु
			netdev_err(dev, "Refused to change device type\n");
			वापस err;
		पूर्ण

		अगर (hdlc->proto->detach)
			hdlc->proto->detach(dev);
		module_put(hdlc->proto->module);
		hdlc->proto = शून्य;
	पूर्ण
	kमुक्त(hdlc->state);
	hdlc->state = शून्य;
	hdlc_setup_dev(dev);

	वापस 0;
पूर्ण


व्योम रेजिस्टर_hdlc_protocol(काष्ठा hdlc_proto *proto)
अणु
	rtnl_lock();
	proto->next = first_proto;
	first_proto = proto;
	rtnl_unlock();
पूर्ण


व्योम unरेजिस्टर_hdlc_protocol(काष्ठा hdlc_proto *proto)
अणु
	काष्ठा hdlc_proto **p;

	rtnl_lock();
	p = &first_proto;
	जबतक (*p != proto) अणु
		BUG_ON(!*p);
		p = &((*p)->next);
	पूर्ण
	*p = proto->next;
	rtnl_unlock();
पूर्ण



MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("HDLC support module");
MODULE_LICENSE("GPL v2");

EXPORT_SYMBOL(hdlc_start_xmit);
EXPORT_SYMBOL(hdlc_खोलो);
EXPORT_SYMBOL(hdlc_बंद);
EXPORT_SYMBOL(hdlc_ioctl);
EXPORT_SYMBOL(alloc_hdlcdev);
EXPORT_SYMBOL(unरेजिस्टर_hdlc_device);
EXPORT_SYMBOL(रेजिस्टर_hdlc_protocol);
EXPORT_SYMBOL(unरेजिस्टर_hdlc_protocol);
EXPORT_SYMBOL(attach_hdlc_protocol);
EXPORT_SYMBOL(detach_hdlc_protocol);

अटल काष्ठा packet_type hdlc_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_HDLC),
	.func = hdlc_rcv,
पूर्ण;


अटल काष्ठा notअगरier_block hdlc_notअगरier = अणु
	.notअगरier_call = hdlc_device_event,
पूर्ण;


अटल पूर्णांक __init hdlc_module_init(व्योम)
अणु
	पूर्णांक result;

	pr_info("%s\n", version);
	अगर ((result = रेजिस्टर_netdevice_notअगरier(&hdlc_notअगरier)) != 0)
		वापस result;
	dev_add_pack(&hdlc_packet_type);
	वापस 0;
पूर्ण



अटल व्योम __निकास hdlc_module_निकास(व्योम)
अणु
	dev_हटाओ_pack(&hdlc_packet_type);
	unरेजिस्टर_netdevice_notअगरier(&hdlc_notअगरier);
पूर्ण


module_init(hdlc_module_init);
module_निकास(hdlc_module_निकास);
