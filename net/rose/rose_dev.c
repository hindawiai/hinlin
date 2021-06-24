<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ip.h>
#समावेश <net/arp.h>

#समावेश <net/ax25.h>
#समावेश <net/rose.h>

अटल पूर्णांक rose_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       अचिन्हित लघु type,
		       स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *buff = skb_push(skb, ROSE_MIN_LEN + 2);

	अगर (daddr)
		स_नकल(buff + 7, daddr, dev->addr_len);

	*buff++ = ROSE_GFI | ROSE_Q_BIT;
	*buff++ = 0x00;
	*buff++ = ROSE_DATA;
	*buff++ = 0x7F;
	*buff++ = AX25_P_IP;

	अगर (daddr != शून्य)
		वापस 37;

	वापस -37;
पूर्ण

अटल पूर्णांक rose_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;
	पूर्णांक err;

	अगर (!स_भेद(dev->dev_addr, sa->sa_data, dev->addr_len))
		वापस 0;

	अगर (dev->flags & IFF_UP) अणु
		err = rose_add_loopback_node((rose_address *)sa->sa_data);
		अगर (err)
			वापस err;

		rose_del_loopback_node((rose_address *)dev->dev_addr);
	पूर्ण

	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);

	वापस 0;
पूर्ण

अटल पूर्णांक rose_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	err = rose_add_loopback_node((rose_address *)dev->dev_addr);
	अगर (err)
		वापस err;

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rose_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	rose_del_loopback_node((rose_address *)dev->dev_addr);
	वापस 0;
पूर्ण

अटल netdev_tx_t rose_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित पूर्णांक len = skb->len;

	अगर (!netअगर_running(dev)) अणु
		prपूर्णांकk(KERN_ERR "ROSE: rose_xmit - called when iface is down\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (!rose_route_frame(skb, शून्य)) अणु
		dev_kमुक्त_skb(skb);
		stats->tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	stats->tx_packets++;
	stats->tx_bytes += len;
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा header_ops rose_header_ops = अणु
	.create	= rose_header,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops rose_netdev_ops = अणु
	.nकरो_खोलो		= rose_खोलो,
	.nकरो_stop		= rose_बंद,
	.nकरो_start_xmit		= rose_xmit,
	.nकरो_set_mac_address    = rose_set_mac_address,
पूर्ण;

व्योम rose_setup(काष्ठा net_device *dev)
अणु
	dev->mtu		= ROSE_MAX_PACKET_SIZE - 2;
	dev->netdev_ops		= &rose_netdev_ops;

	dev->header_ops		= &rose_header_ops;
	dev->hard_header_len	= AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN;
	dev->addr_len		= ROSE_ADDR_LEN;
	dev->type		= ARPHRD_ROSE;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
पूर्ण
