<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
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
#समावेश <linux/अगर_ether.h>	/* For the statistics काष्ठाure. */
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पन.स>

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ip.h>
#समावेश <net/arp.h>

#समावेश <net/ax25.h>
#समावेश <net/netrom.h>

/*
 *	Only allow IP over NET/ROM frames through अगर the netrom device is up.
 */

पूर्णांक nr_rx_ip(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;

	अगर (!netअगर_running(dev)) अणु
		stats->rx_dropped++;
		वापस 0;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += skb->len;

	skb->protocol = htons(ETH_P_IP);

	/* Spoof incoming device */
	skb->dev      = dev;
	skb->mac_header = skb->network_header;
	skb_reset_network_header(skb);
	skb->pkt_type = PACKET_HOST;

	netअगर_rx(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक nr_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     अचिन्हित लघु type,
		     स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *buff = skb_push(skb, NR_NETWORK_LEN + NR_TRANSPORT_LEN);

	स_नकल(buff, (saddr != शून्य) ? saddr : dev->dev_addr, dev->addr_len);
	buff[6] &= ~AX25_CBIT;
	buff[6] &= ~AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	अगर (daddr != शून्य)
		स_नकल(buff, daddr, dev->addr_len);
	buff[6] &= ~AX25_CBIT;
	buff[6] |= AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	*buff++ = sysctl_netrom_network_ttl_initialiser;

	*buff++ = NR_PROTO_IP;
	*buff++ = NR_PROTO_IP;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = NR_PROTOEXT;

	अगर (daddr != शून्य)
		वापस 37;

	वापस -37;
पूर्ण

अटल पूर्णांक __must_check nr_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;
	पूर्णांक err;

	अगर (!स_भेद(dev->dev_addr, sa->sa_data, dev->addr_len))
		वापस 0;

	अगर (dev->flags & IFF_UP) अणु
		err = ax25_listen_रेजिस्टर((ax25_address *)sa->sa_data, शून्य);
		अगर (err)
			वापस err;

		ax25_listen_release((ax25_address *)dev->dev_addr, शून्य);
	पूर्ण

	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len);

	वापस 0;
पूर्ण

अटल पूर्णांक nr_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	err = ax25_listen_रेजिस्टर((ax25_address *)dev->dev_addr, शून्य);
	अगर (err)
		वापस err;

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nr_बंद(काष्ठा net_device *dev)
अणु
	ax25_listen_release((ax25_address *)dev->dev_addr, शून्य);
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t nr_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	अचिन्हित पूर्णांक len = skb->len;

	अगर (!nr_route_frame(skb, शून्य)) अणु
		kमुक्त_skb(skb);
		stats->tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	stats->tx_packets++;
	stats->tx_bytes += len;

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा header_ops nr_header_ops = अणु
	.create	= nr_header,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops nr_netdev_ops = अणु
	.nकरो_खोलो		= nr_खोलो,
	.nकरो_stop		= nr_बंद,
	.nकरो_start_xmit		= nr_xmit,
	.nकरो_set_mac_address    = nr_set_mac_address,
पूर्ण;

व्योम nr_setup(काष्ठा net_device *dev)
अणु
	dev->mtu		= NR_MAX_PACKET_SIZE;
	dev->netdev_ops		= &nr_netdev_ops;
	dev->header_ops		= &nr_header_ops;
	dev->hard_header_len	= NR_NETWORK_LEN + NR_TRANSPORT_LEN;
	dev->addr_len		= AX25_ADDR_LEN;
	dev->type		= ARPHRD_NETROM;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
पूर्ण
