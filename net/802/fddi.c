<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		FDDI-type device handling.
 *
 * Version:	@(#)fddi.c	1.0.0	08/12/96
 *
 * Authors:	Lawrence V. Stefani, <stefani@lkg.dec.com>
 *
 *		fddi.c is based on previous eth.c and tr.c work by
 *			Ross Biro
 *			Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *			Mark Evans, <evansmp@uhura.aston.ac.uk>
 *			Florian La Roche, <rzsfl@rz.uni-sb.de>
 *			Alan Cox, <gw4pts@gw4pts.ampr.org>
 *
 *	Changes
 *		Alan Cox		:	New arp/rebuild header
 *		Maciej W. Rozycki	:	IPv6 support
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
#समावेश <linux/fddidevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/arp.h>
#समावेश <net/sock.h>

/*
 * Create the FDDI MAC header क्रम an arbitrary protocol layer
 *
 * saddr=शून्य	means use device source address
 * daddr=शून्य	means leave destination address (eg unresolved arp)
 */

अटल पूर्णांक fddi_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       अचिन्हित लघु type,
		       स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक hl = FDDI_K_SNAP_HLEN;
	काष्ठा fddihdr *fddi;

	अगर(type != ETH_P_IP && type != ETH_P_IPV6 && type != ETH_P_ARP)
		hl=FDDI_K_8022_HLEN-3;
	fddi = skb_push(skb, hl);
	fddi->fc			 = FDDI_FC_K_ASYNC_LLC_DEF;
	अगर(type == ETH_P_IP || type == ETH_P_IPV6 || type == ETH_P_ARP)
	अणु
		fddi->hdr.llc_snap.dsap		 = FDDI_EXTENDED_SAP;
		fddi->hdr.llc_snap.ssap		 = FDDI_EXTENDED_SAP;
		fddi->hdr.llc_snap.ctrl		 = FDDI_UI_CMD;
		fddi->hdr.llc_snap.oui[0]	 = 0x00;
		fddi->hdr.llc_snap.oui[1]	 = 0x00;
		fddi->hdr.llc_snap.oui[2]	 = 0x00;
		fddi->hdr.llc_snap.ethertype	 = htons(type);
	पूर्ण

	/* Set the source and destination hardware addresses */

	अगर (saddr != शून्य)
		स_नकल(fddi->saddr, saddr, dev->addr_len);
	अन्यथा
		स_नकल(fddi->saddr, dev->dev_addr, dev->addr_len);

	अगर (daddr != शून्य)
	अणु
		स_नकल(fddi->daddr, daddr, dev->addr_len);
		वापस hl;
	पूर्ण

	वापस -hl;
पूर्ण

/*
 * Determine the packet's protocol ID and fill in skb fields.
 * This routine is called beक्रमe an incoming packet is passed
 * up.  It's used to fill in specअगरic skb fields and to set
 * the proper poपूर्णांकer to the start of packet data (skb->data).
 */

__be16 fddi_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fddihdr *fddi = (काष्ठा fddihdr *)skb->data;
	__be16 type;

	/*
	 * Set mac.raw field to poपूर्णांक to FC byte, set data field to poपूर्णांक
	 * to start of packet data.  Assume 802.2 SNAP frames क्रम now.
	 */

	skb->dev = dev;
	skb_reset_mac_header(skb);	/* poपूर्णांक to frame control (FC) */

	अगर(fddi->hdr.llc_8022_1.dsap==0xe0)
	अणु
		skb_pull(skb, FDDI_K_8022_HLEN-3);
		type = htons(ETH_P_802_2);
	पूर्ण
	अन्यथा
	अणु
		skb_pull(skb, FDDI_K_SNAP_HLEN);		/* adjust क्रम 21 byte header */
		type=fddi->hdr.llc_snap.ethertype;
	पूर्ण

	/* Set packet type based on destination address and flag settings */

	अगर (*fddi->daddr & 0x01)
	अणु
		अगर (स_भेद(fddi->daddr, dev->broadcast, FDDI_K_ALEN) == 0)
			skb->pkt_type = PACKET_BROADCAST;
		अन्यथा
			skb->pkt_type = PACKET_MULTICAST;
	पूर्ण

	अन्यथा अगर (dev->flags & IFF_PROMISC)
	अणु
		अगर (स_भेद(fddi->daddr, dev->dev_addr, FDDI_K_ALEN))
			skb->pkt_type = PACKET_OTHERHOST;
	पूर्ण

	/* Assume 802.2 SNAP frames, क्रम now */

	वापस type;
पूर्ण

EXPORT_SYMBOL(fddi_type_trans);

अटल स्थिर काष्ठा header_ops fddi_header_ops = अणु
	.create		= fddi_header,
पूर्ण;


अटल व्योम fddi_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops		= &fddi_header_ops;
	dev->type		= ARPHRD_FDDI;
	dev->hard_header_len	= FDDI_K_SNAP_HLEN+3;	/* Assume 802.2 SNAP hdr len + 3 pad bytes */
	dev->mtu		= FDDI_K_SNAP_DLEN;	/* Assume max payload of 802.2 SNAP frame */
	dev->min_mtu		= FDDI_K_SNAP_HLEN;
	dev->max_mtu		= FDDI_K_SNAP_DLEN;
	dev->addr_len		= FDDI_K_ALEN;
	dev->tx_queue_len	= 100;			/* Long queues on FDDI */
	dev->flags		= IFF_BROADCAST | IFF_MULTICAST;

	स_रखो(dev->broadcast, 0xFF, FDDI_K_ALEN);
पूर्ण

/**
 * alloc_fddidev - Register FDDI device
 * @माप_priv: Size of additional driver-निजी काष्ठाure to be allocated
 *	क्रम this FDDI device
 *
 * Fill in the fields of the device काष्ठाure with FDDI-generic values.
 *
 * Conकाष्ठाs a new net device, complete with a निजी data area of
 * size @माप_priv.  A 32-byte (not bit) alignment is enक्रमced क्रम
 * this निजी data area.
 */
काष्ठा net_device *alloc_fddidev(पूर्णांक माप_priv)
अणु
	वापस alloc_netdev(माप_priv, "fddi%d", NET_NAME_UNKNOWN,
			    fddi_setup);
पूर्ण
EXPORT_SYMBOL(alloc_fddidev);

MODULE_LICENSE("GPL");
