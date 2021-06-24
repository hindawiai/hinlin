<शैली गुरु>
/*
 * Linux ARCnet driver - "cap mode" packet encapsulation.
 * It adds sequence numbers to packets क्रम communicating between a user space
 * application and the driver. After a transmit it sends a packet with protocol
 * byte 0 back up to the userspace containing the sequence number of the packet
 * plus the transmit-status on the ArcNet.
 *
 * Written 2002-4 by Esben Niअन्यथाn, Vestas Wind Systems A/S
 * Derived from arc-rawmode.c by Avery Pennarun.
 * arc-rawmode was in turned based on skeleton.c, see below.
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
	काष्ठा archdr *pkt;
	अक्षर *pktbuf, *pkthdrbuf;
	पूर्णांक ofs;

	arc_prपूर्णांकk(D_DURING, dev, "it's a raw(cap) packet (length=%d)\n",
		   length);

	अगर (length >= MinTU)
		ofs = 512 - length;
	अन्यथा
		ofs = 256 - length;

	skb = alloc_skb(length + ARC_HDR_SIZE + माप(पूर्णांक), GFP_ATOMIC);
	अगर (!skb) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb_put(skb, length + ARC_HDR_SIZE + माप(पूर्णांक));
	skb->dev = dev;
	skb_reset_mac_header(skb);
	pkt = (काष्ठा archdr *)skb_mac_header(skb);
	skb_pull(skb, ARC_HDR_SIZE);

	/* up to माप(pkt->soft) has alपढ़ोy been copied from the card
	 * squeeze in an पूर्णांक क्रम the cap encapsulation
	 * use these variables to be sure we count in bytes, not in
	 * माप(काष्ठा archdr)
	 */
	pktbuf = (अक्षर *)pkt;
	pkthdrbuf = (अक्षर *)pkthdr;
	स_नकल(pktbuf, pkthdrbuf, ARC_HDR_SIZE + माप(pkt->soft.cap.proto));
	स_नकल(pktbuf + ARC_HDR_SIZE + माप(pkt->soft.cap.proto) + माप(पूर्णांक),
	       pkthdrbuf + ARC_HDR_SIZE + माप(pkt->soft.cap.proto),
	       माप(काष्ठा archdr) - ARC_HDR_SIZE - माप(pkt->soft.cap.proto));

	अगर (length > माप(pkt->soft))
		lp->hw.copy_from_card(dev, bufnum, ofs + माप(pkt->soft),
				      pkt->soft.raw + माप(pkt->soft)
				      + माप(पूर्णांक),
				      length - माप(pkt->soft));

	अगर (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, skb, "rx");

	skb->protocol = cpu_to_be16(ETH_P_ARCNET);
	netअगर_rx(skb);
पूर्ण

/* Create the ARCnet hard/soft headers क्रम cap mode.
 * There aren't any soft headers in cap mode - not even the protocol id.
 */
अटल पूर्णांक build_header(काष्ठा sk_buff *skb,
			काष्ठा net_device *dev,
			अचिन्हित लघु type,
			uपूर्णांक8_t daddr)
अणु
	पूर्णांक hdr_size = ARC_HDR_SIZE;
	काष्ठा archdr *pkt = skb_push(skb, hdr_size);

	arc_prपूर्णांकk(D_PROTO, dev, "Preparing header for cap packet %x.\n",
		   *((पूर्णांक *)&pkt->soft.cap.cookie[0]));

	/* Set the source hardware address.
	 *
	 * This is pretty poपूर्णांकless क्रम most purposes, but it can help in
	 * debugging.  ARCnet करोes not allow us to change the source address in
	 * the actual packet sent)
	 */
	pkt->hard.source = *dev->dev_addr;

	/* see linux/net/ethernet/eth.c to see where I got the following */

	अगर (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) अणु
		/* FIXME: fill in the last byte of the dest ipaddr here to
		 * better comply with RFC1051 in "noarp" mode.
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

	/* hard header is not included in packet length */
	length -= ARC_HDR_SIZE;
	/* And neither is the cookie field */
	length -= माप(पूर्णांक);

	arc_prपूर्णांकk(D_DURING, dev, "prepare_tx: txbufs=%d/%d/%d\n",
		   lp->next_tx, lp->cur_tx, bufnum);

	arc_prपूर्णांकk(D_PROTO, dev, "Sending for cap packet %x.\n",
		   *((पूर्णांक *)&pkt->soft.cap.cookie[0]));

	अगर (length > XMTU) अणु
		/* should never happen! other people alपढ़ोy check क्रम this. */
		arc_prपूर्णांकk(D_NORMAL, dev, "Bug!  prepare_tx with size %d (> %d)\n",
			   length, XMTU);
		length = XMTU;
	पूर्ण
	अगर (length > MinTU) अणु
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

	/* Copy the arcnet-header + the protocol byte करोwn: */
	lp->hw.copy_to_card(dev, bufnum, 0, hard, ARC_HDR_SIZE);
	lp->hw.copy_to_card(dev, bufnum, ofs, &pkt->soft.cap.proto,
			    माप(pkt->soft.cap.proto));

	/* Skip the extra पूर्णांकeger we have written पूर्णांकo it as a cookie
	 * but ग_लिखो the rest of the message:
	 */
	lp->hw.copy_to_card(dev, bufnum, ofs + 1,
			    ((अचिन्हित अक्षर *)&pkt->soft.cap.mes), length - 1);

	lp->lastload_dest = hard->dest;

	वापस 1;	/* करोne */
पूर्ण

अटल पूर्णांक ack_tx(काष्ठा net_device *dev, पूर्णांक acked)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *ackskb;
	काष्ठा archdr *ackpkt;
	पूर्णांक length = माप(काष्ठा arc_cap);

	arc_prपूर्णांकk(D_DURING, dev, "capmode: ack_tx: protocol: %x: result: %d\n",
		   lp->outgoing.skb->protocol, acked);

	अगर (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, lp->outgoing.skb, "ack_tx");

	/* Now alloc a skb to send back up through the layers: */
	ackskb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
	अगर (!ackskb)
		जाओ मुक्त_outskb;

	skb_put(ackskb, length + ARC_HDR_SIZE);
	ackskb->dev = dev;

	skb_reset_mac_header(ackskb);
	ackpkt = (काष्ठा archdr *)skb_mac_header(ackskb);
	/* skb_pull(ackskb, ARC_HDR_SIZE); */

	skb_copy_from_linear_data(lp->outgoing.skb, ackpkt,
				  ARC_HDR_SIZE + माप(काष्ठा arc_cap));
	ackpkt->soft.cap.proto = 0; /* using protocol 0 क्रम acknowledge */
	ackpkt->soft.cap.mes.ack = acked;

	arc_prपूर्णांकk(D_PROTO, dev, "Acknowledge for cap packet %x.\n",
		   *((पूर्णांक *)&ackpkt->soft.cap.cookie[0]));

	ackskb->protocol = cpu_to_be16(ETH_P_ARCNET);

	अगर (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, ackskb, "ack_tx_recv");
	netअगर_rx(ackskb);

मुक्त_outskb:
	dev_kमुक्त_skb_irq(lp->outgoing.skb);
	lp->outgoing.proto = शून्य;
			/* We are always finished when in this protocol */

	वापस 0;
पूर्ण

अटल काष्ठा ArcProto capmode_proto = अणु
	.suffix		= 'r',
	.mtu		= XMTU,
	.rx		= rx,
	.build_header	= build_header,
	.prepare_tx	= prepare_tx,
	.ack_tx		= ack_tx
पूर्ण;

अटल पूर्णांक __init capmode_module_init(व्योम)
अणु
	पूर्णांक count;

	pr_info("cap mode (`c') encapsulation support loaded\n");

	क्रम (count = 1; count <= 8; count++)
		अगर (arc_proto_map[count] == arc_proto_शेष)
			arc_proto_map[count] = &capmode_proto;

	/* क्रम cap mode, we only set the bcast proto अगर there's no better one */
	अगर (arc_bcast_proto == arc_proto_शेष)
		arc_bcast_proto = &capmode_proto;

	arc_proto_शेष = &capmode_proto;
	arc_raw_proto = &capmode_proto;

	वापस 0;
पूर्ण

अटल व्योम __निकास capmode_module_निकास(व्योम)
अणु
	arcnet_unरेजिस्टर_proto(&capmode_proto);
पूर्ण
module_init(capmode_module_init);
module_निकास(capmode_module_निकास);

MODULE_LICENSE("GPL");
