<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		HIPPI-type device handling.
 *
 * Version:	@(#)hippi.c	1.0.0	05/29/97
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Mark Evans, <evansmp@uhura.aston.ac.uk>
 *		Florian  La Roche, <rzsfl@rz.uni-sb.de>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Jes Sorensen, <Jes.Sorensen@cern.ch>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hippidevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/arp.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>

/*
 * Create the HIPPI MAC header क्रम an arbitrary protocol layer
 *
 * saddr=शून्य	means use device source address
 * daddr=शून्य	means leave destination address (eg unresolved arp)
 */

अटल पूर्णांक hippi_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			अचिन्हित लघु type,
			स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hippi_hdr *hip = skb_push(skb, HIPPI_HLEN);
	काष्ठा hippi_cb *hcb = (काष्ठा hippi_cb *) skb->cb;

	अगर (!len)अणु
		len = skb->len - HIPPI_HLEN;
		prपूर्णांकk("hippi_header(): length not supplied\n");
	पूर्ण

	/*
	 * Due to the stupidity of the little endian byte-order we
	 * have to set the fp field this way.
	 */
	hip->fp.fixed		= htonl(0x04800018);
	hip->fp.d2_size		= htonl(len + 8);
	hip->le.fc		= 0;
	hip->le.द्विगुन_wide	= 0;	/* only HIPPI 800 क्रम the समय being */
	hip->le.message_type	= 0;	/* Data PDU */

	hip->le.dest_addr_type	= 2;	/* 12 bit SC address */
	hip->le.src_addr_type	= 2;	/* 12 bit SC address */

	स_नकल(hip->le.src_चयन_addr, dev->dev_addr + 3, 3);
	स_रखो(&hip->le.reserved, 0, 16);

	hip->snap.dsap		= HIPPI_EXTENDED_SAP;
	hip->snap.ssap		= HIPPI_EXTENDED_SAP;
	hip->snap.ctrl		= HIPPI_UI_CMD;
	hip->snap.oui[0]	= 0x00;
	hip->snap.oui[1]	= 0x00;
	hip->snap.oui[2]	= 0x00;
	hip->snap.ethertype	= htons(type);

	अगर (daddr)
	अणु
		स_नकल(hip->le.dest_चयन_addr, daddr + 3, 3);
		स_नकल(&hcb->अगरield, daddr + 2, 4);
		वापस HIPPI_HLEN;
	पूर्ण
	hcb->अगरield = 0;
	वापस -((पूर्णांक)HIPPI_HLEN);
पूर्ण


/*
 *	Determine the packet's protocol ID.
 */

__be16 hippi_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hippi_hdr *hip;

	/*
	 * This is actually wrong ... question is अगर we really should
	 * set the raw address here.
	 */
	skb->dev = dev;
	skb_reset_mac_header(skb);
	hip = (काष्ठा hippi_hdr *)skb_mac_header(skb);
	skb_pull(skb, HIPPI_HLEN);

	/*
	 * No fancy promisc stuff here now.
	 */

	वापस hip->snap.ethertype;
पूर्ण

EXPORT_SYMBOL(hippi_type_trans);

/*
 * For HIPPI we will actually use the lower 4 bytes of the hardware
 * address as the I-FIELD rather than the actual hardware address.
 */
पूर्णांक hippi_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	अगर (netअगर_running(dev))
		वापस -EBUSY;
	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hippi_mac_addr);

पूर्णांक hippi_neigh_setup_dev(काष्ठा net_device *dev, काष्ठा neigh_parms *p)
अणु
	/* Never send broadcast/multicast ARP messages */
	NEIGH_VAR_INIT(p, MCAST_PROBES, 0);

	/* In IPv6 unicast probes are valid even on NBMA,
	* because they are encapsulated in normal IPv6 protocol.
	* Should be a generic flag.
	*/
	अगर (p->tbl->family != AF_INET6)
		NEIGH_VAR_INIT(p, UCAST_PROBES, 0);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hippi_neigh_setup_dev);

अटल स्थिर काष्ठा header_ops hippi_header_ops = अणु
	.create		= hippi_header,
पूर्ण;


अटल व्योम hippi_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops			= &hippi_header_ops;

	/*
	 * We करोn't support HIPPI `ARP' क्रम the समय being, and probably
	 * never will unless someone अन्यथा implements it. However we
	 * still need a fake ARPHRD to make अगरconfig and मित्रs play ball.
	 */
	dev->type		= ARPHRD_HIPPI;
	dev->hard_header_len 	= HIPPI_HLEN;
	dev->mtu		= 65280;
	dev->min_mtu		= 68;
	dev->max_mtu		= 65280;
	dev->addr_len		= HIPPI_ALEN;
	dev->tx_queue_len	= 25 /* 5 */;
	स_रखो(dev->broadcast, 0xFF, HIPPI_ALEN);


	/*
	 * HIPPI करोesn't support broadcast+multicast and we only use
	 * अटल ARP tables. ARP is disabled by hippi_neigh_setup_dev.
	 */
	dev->flags = 0;
पूर्ण

/**
 * alloc_hippi_dev - Register HIPPI device
 * @माप_priv: Size of additional driver-निजी काष्ठाure to be allocated
 *	क्रम this HIPPI device
 *
 * Fill in the fields of the device काष्ठाure with HIPPI-generic values.
 *
 * Conकाष्ठाs a new net device, complete with a निजी data area of
 * size @माप_priv.  A 32-byte (not bit) alignment is enक्रमced क्रम
 * this निजी data area.
 */

काष्ठा net_device *alloc_hippi_dev(पूर्णांक माप_priv)
अणु
	वापस alloc_netdev(माप_priv, "hip%d", NET_NAME_UNKNOWN,
			    hippi_setup);
पूर्ण

EXPORT_SYMBOL(alloc_hippi_dev);
