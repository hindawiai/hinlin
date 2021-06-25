<शैली गुरु>
/*
 * Linux ARCnet driver - "raw mode" packet encapsulation (no soft headers)
 *
 * Written 1994-1999 by Avery Pennarun.
 * Derived from skeleton.c by Donald Becker.
 *
 * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)
 *  क्रम sponsoring the further development of this driver.
 *
 * **********************
 *
 * The original copyright of skeleton.c was as follows:
 *
 * skeleton.c Written 1993 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may only be used
 * and distributed according to the terms of the GNU General Public License as
 * modअगरied by SRC, incorporated herein by reference.
 *
 * **********************
 *
 * For more details, see drivers/net/arcnet.c
 *
 * **********************
 */

#घोषणा pr_fmt(fmt) "arcnet:" KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश "arcdevice.h"

/* packet receiver */
अटल व्योम rx(काष्ठा net_device *dev, पूर्णांक bufnum,
	       काष्ठा archdr *pkthdr, पूर्णांक length)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा archdr *pkt = pkthdr;
	पूर्णांक ofs;

	arc_prपूर्णांकk(D_DURING, dev, "it's a raw packet (length=%d)\n", length);

	अगर (length > MTU)
		ofs = 512 - length;
	अन्यथा
		ofs = 256 - length;

	skb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
	अगर (!skb) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb_put(skb, length + ARC_HDR_SIZE);
	skb->dev = dev;

	pkt = (काष्ठा archdr *)skb->data;

	skb_reset_mac_header(skb);
	skb_pull(skb, ARC_HDR_SIZE);

	/* up to माप(pkt->soft) has alपढ़ोy been copied from the card */
	स_नकल(pkt, pkthdr, माप(काष्ठा archdr));
	अगर (length > माप(pkt->soft))
		lp->hw.copy_from_card(dev, bufnum, ofs + माप(pkt->soft),
				      pkt->soft.raw + माप(pkt->soft),
				      length - माप(pkt->soft));

	अगर (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, skb, "rx");

	skb->protocol = cpu_to_be16(ETH_P_ARCNET);
	netअगर_rx(skb);
पूर्ण

/* Create the ARCnet hard/soft headers क्रम raw mode.
 * There aren't any soft headers in raw mode - not even the protocol id.
 */
अटल पूर्णांक build_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			अचिन्हित लघु type, uपूर्णांक8_t daddr)
अणु
	पूर्णांक hdr_size = ARC_HDR_SIZE;
	काष्ठा archdr *pkt = skb_push(skb, hdr_size);

	/* Set the source hardware address.
	 *
	 * This is pretty poपूर्णांकless क्रम most purposes, but it can help in
	 * debugging.  ARCnet करोes not allow us to change the source address
	 * in the actual packet sent.
	 */
	pkt->hard.source = *dev->dev_addr;

	/* see linux/net/ethernet/eth.c to see where I got the following */

	अगर (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) अणु
		/* FIXME: fill in the last byte of the dest ipaddr here
		 * to better comply with RFC1051 in "noarp" mode.
		 */
		pkt->hard.dest = 0;
		वापस hdr_size;
	पूर्ण
	/* otherwise, just fill it in and go! */
	pkt->hard.dest = daddr;

	वापस hdr_size;	/* success */
पूर्ण

अटल पूर्णांक prepare_tx(काष्ठा net_device *dev, काष्ठा archdr *pkt, पूर्णांक length,
		      पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा arc_hardware *hard = &pkt->hard;
	पूर्णांक ofs;

	arc_prपूर्णांकk(D_DURING, dev, "prepare_tx: txbufs=%d/%d/%d\n",
		   lp->next_tx, lp->cur_tx, bufnum);

	/* hard header is not included in packet length */
	length -= ARC_HDR_SIZE;

	अगर (length > XMTU) अणु
		/* should never happen! other people alपढ़ोy check क्रम this. */
		arc_prपूर्णांकk(D_NORMAL, dev, "Bug!  prepare_tx with size %d (> %d)\n",
			   length, XMTU);
		length = XMTU;
	पूर्ण
	अगर (length >= MinTU) अणु
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - length;
	पूर्ण अन्यथा अगर (length > MTU) अणु
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - length - 3;
	पूर्ण अन्यथा अणु
		hard->offset[0] = ofs = 256 - length;
	पूर्ण

	arc_prपूर्णांकk(D_DURING, dev, "prepare_tx: length=%d ofs=%d\n",
		   length, ofs);

	lp->hw.copy_to_card(dev, bufnum, 0, hard, ARC_HDR_SIZE);
	lp->hw.copy_to_card(dev, bufnum, ofs, &pkt->soft, length);

	lp->lastload_dest = hard->dest;

	वापस 1;		/* करोne */
पूर्ण

अटल काष्ठा ArcProto rawmode_proto = अणु
	.suffix		= 'r',
	.mtu		= XMTU,
	.rx		= rx,
	.build_header	= build_header,
	.prepare_tx	= prepare_tx,
	.जारी_tx    = शून्य,
	.ack_tx         = शून्य
पूर्ण;

अटल पूर्णांक __init arcnet_raw_init(व्योम)
अणु
	पूर्णांक count;

	pr_info("raw mode (`r') encapsulation support loaded\n");

	क्रम (count = 0; count < 256; count++)
		अगर (arc_proto_map[count] == arc_proto_शेष)
			arc_proto_map[count] = &rawmode_proto;

	/* क्रम raw mode, we only set the bcast proto अगर there's no better one */
	अगर (arc_bcast_proto == arc_proto_शेष)
		arc_bcast_proto = &rawmode_proto;

	arc_proto_शेष = &rawmode_proto;
	वापस 0;
पूर्ण

अटल व्योम __निकास arcnet_raw_निकास(व्योम)
अणु
	arcnet_unरेजिस्टर_proto(&rawmode_proto);
पूर्ण

module_init(arcnet_raw_init);
module_निकास(arcnet_raw_निकास);

MODULE_LICENSE("GPL");
