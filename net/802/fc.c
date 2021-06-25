<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NET3:	Fibre Channel device handling subroutines
 *
 *		Vineet Abraham <vma@iol.unh.edu>
 *		v 1.0 03/22/99
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/fcdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/net.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <net/arp.h>

/*
 *	Put the headers on a Fibre Channel packet.
 */

अटल पूर्णांक fc_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     अचिन्हित लघु type,
		     स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा fch_hdr *fch;
	पूर्णांक hdr_len;

	/*
	 * Add the 802.2 SNAP header अगर IP as the IPv4 code calls
	 * dev->hard_header directly.
	 */
	अगर (type == ETH_P_IP || type == ETH_P_ARP)
	अणु
		काष्ठा fcllc *fcllc;

		hdr_len = माप(काष्ठा fch_hdr) + माप(काष्ठा fcllc);
		fch = skb_push(skb, hdr_len);
		fcllc = (काष्ठा fcllc *)(fch+1);
		fcllc->dsap = fcllc->ssap = EXTENDED_SAP;
		fcllc->llc = UI_CMD;
		fcllc->protid[0] = fcllc->protid[1] = fcllc->protid[2] = 0x00;
		fcllc->ethertype = htons(type);
	पूर्ण
	अन्यथा
	अणु
		hdr_len = माप(काष्ठा fch_hdr);
		fch = skb_push(skb, hdr_len);
	पूर्ण

	अगर(saddr)
		स_नकल(fch->saddr,saddr,dev->addr_len);
	अन्यथा
		स_नकल(fch->saddr,dev->dev_addr,dev->addr_len);

	अगर(daddr)
	अणु
		स_नकल(fch->daddr,daddr,dev->addr_len);
		वापस hdr_len;
	पूर्ण
	वापस -hdr_len;
पूर्ण

अटल स्थिर काष्ठा header_ops fc_header_ops = अणु
	.create	 = fc_header,
पूर्ण;

अटल व्योम fc_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops		= &fc_header_ops;
	dev->type		= ARPHRD_IEEE802;
	dev->hard_header_len	= FC_HLEN;
	dev->mtu		= 2024;
	dev->addr_len		= FC_ALEN;
	dev->tx_queue_len	= 100; /* Long queues on fc */
	dev->flags		= IFF_BROADCAST;

	स_रखो(dev->broadcast, 0xFF, FC_ALEN);
पूर्ण

/**
 * alloc_fcdev - Register fibre channel device
 * @माप_priv: Size of additional driver-निजी काष्ठाure to be allocated
 *	क्रम this fibre channel device
 *
 * Fill in the fields of the device काष्ठाure with fibre channel-generic values.
 *
 * Conकाष्ठाs a new net device, complete with a निजी data area of
 * size @माप_priv.  A 32-byte (not bit) alignment is enक्रमced क्रम
 * this निजी data area.
 */
काष्ठा net_device *alloc_fcdev(पूर्णांक माप_priv)
अणु
	वापस alloc_netdev(माप_priv, "fc%d", NET_NAME_UNKNOWN, fc_setup);
पूर्ण
EXPORT_SYMBOL(alloc_fcdev);
