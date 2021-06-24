<शैली गुरु>
/*
 * Linux ARCnet driver - RFC1201 (standard) packet encapsulation
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

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>

#समावेश "arcdevice.h"

MODULE_LICENSE("GPL");

अटल __be16 type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम rx(काष्ठा net_device *dev, पूर्णांक bufnum,
	       काष्ठा archdr *pkthdr, पूर्णांक length);
अटल पूर्णांक build_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			अचिन्हित लघु type, uपूर्णांक8_t daddr);
अटल पूर्णांक prepare_tx(काष्ठा net_device *dev, काष्ठा archdr *pkt, पूर्णांक length,
		      पूर्णांक bufnum);
अटल पूर्णांक जारी_tx(काष्ठा net_device *dev, पूर्णांक bufnum);

अटल काष्ठा ArcProto rfc1201_proto = अणु
	.suffix		= 'a',
	.mtu		= 1500,	/* could be more, but some receivers can't handle it... */
	.is_ip          = 1,    /* This is क्रम sending IP and ARP packages */
	.rx		= rx,
	.build_header	= build_header,
	.prepare_tx	= prepare_tx,
	.जारी_tx	= जारी_tx,
	.ack_tx         = शून्य
पूर्ण;

अटल पूर्णांक __init arcnet_rfc1201_init(व्योम)
अणु
	pr_info("%s\n", "RFC1201 \"standard\" (`a') encapsulation support loaded");

	arc_proto_map[ARC_P_IP]
	    = arc_proto_map[ARC_P_IPV6]
	    = arc_proto_map[ARC_P_ARP]
	    = arc_proto_map[ARC_P_RARP]
	    = arc_proto_map[ARC_P_IPX]
	    = arc_proto_map[ARC_P_NOVELL_EC]
	    = &rfc1201_proto;

	/* अगर someone अन्यथा alपढ़ोy owns the broadcast, we won't take it */
	अगर (arc_bcast_proto == arc_proto_शेष)
		arc_bcast_proto = &rfc1201_proto;

	वापस 0;
पूर्ण

अटल व्योम __निकास arcnet_rfc1201_निकास(व्योम)
अणु
	arcnet_unरेजिस्टर_proto(&rfc1201_proto);
पूर्ण

module_init(arcnet_rfc1201_init);
module_निकास(arcnet_rfc1201_निकास);

/* Determine a packet's protocol ID.
 *
 * With ARCnet we have to convert everything to Ethernet-style stuff.
 */
अटल __be16 type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा archdr *pkt = (काष्ठा archdr *)skb->data;
	काष्ठा arc_rfc1201 *soft = &pkt->soft.rfc1201;
	पूर्णांक hdr_size = ARC_HDR_SIZE + RFC1201_HDR_SIZE;

	/* Pull off the arcnet header. */
	skb_reset_mac_header(skb);
	skb_pull(skb, hdr_size);

	अगर (pkt->hard.dest == 0) अणु
		skb->pkt_type = PACKET_BROADCAST;
	पूर्ण अन्यथा अगर (dev->flags & IFF_PROMISC) अणु
		/* अगर we're not sending to ourselves :) */
		अगर (pkt->hard.dest != dev->dev_addr[0])
			skb->pkt_type = PACKET_OTHERHOST;
	पूर्ण
	/* now वापस the protocol number */
	चयन (soft->proto) अणु
	हाल ARC_P_IP:
		वापस htons(ETH_P_IP);
	हाल ARC_P_IPV6:
		वापस htons(ETH_P_IPV6);
	हाल ARC_P_ARP:
		वापस htons(ETH_P_ARP);
	हाल ARC_P_RARP:
		वापस htons(ETH_P_RARP);

	हाल ARC_P_IPX:
	हाल ARC_P_NOVELL_EC:
		वापस htons(ETH_P_802_3);
	शेष:
		dev->stats.rx_errors++;
		dev->stats.rx_crc_errors++;
		वापस 0;
	पूर्ण

	वापस htons(ETH_P_IP);
पूर्ण

/* packet receiver */
अटल व्योम rx(काष्ठा net_device *dev, पूर्णांक bufnum,
	       काष्ठा archdr *pkthdr, पूर्णांक length)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा archdr *pkt = pkthdr;
	काष्ठा arc_rfc1201 *soft = &pkthdr->soft.rfc1201;
	पूर्णांक saddr = pkt->hard.source, ofs;
	काष्ठा Incoming *in = &lp->rfc1201.incoming[saddr];

	arc_prपूर्णांकk(D_DURING, dev, "it's an RFC1201 packet (length=%d)\n",
		   length);

	अगर (length >= MinTU)
		ofs = 512 - length;
	अन्यथा
		ofs = 256 - length;

	अगर (soft->split_flag == 0xFF) अणु		/* Exception Packet */
		अगर (length >= 4 + RFC1201_HDR_SIZE) अणु
			arc_prपूर्णांकk(D_DURING, dev, "compensating for exception packet\n");
		पूर्ण अन्यथा अणु
			arc_prपूर्णांकk(D_EXTRA, dev, "short RFC1201 exception packet from %02Xh",
				   saddr);
			वापस;
		पूर्ण

		/* skip over 4-byte junkola */
		length -= 4;
		ofs += 4;
		lp->hw.copy_from_card(dev, bufnum, 512 - length,
				      soft, माप(pkt->soft));
	पूर्ण
	अगर (!soft->split_flag) अणु	/* not split */
		arc_prपूर्णांकk(D_RX, dev, "incoming is not split (splitflag=%d)\n",
			   soft->split_flag);

		अगर (in->skb) अणु	/* alपढ़ोy assembling one! */
			arc_prपूर्णांकk(D_EXTRA, dev, "aborting assembly (seq=%d) for unsplit packet (splitflag=%d, seq=%d)\n",
				   in->sequence, soft->split_flag,
				   soft->sequence);
			lp->rfc1201.पातed_seq = soft->sequence;
			dev_kमुक्त_skb_irq(in->skb);
			dev->stats.rx_errors++;
			dev->stats.rx_missed_errors++;
			in->skb = शून्य;
		पूर्ण
		in->sequence = soft->sequence;

		skb = alloc_skb(length + ARC_HDR_SIZE, GFP_ATOMIC);
		अगर (!skb) अणु
			dev->stats.rx_dropped++;
			वापस;
		पूर्ण
		skb_put(skb, length + ARC_HDR_SIZE);
		skb->dev = dev;

		pkt = (काष्ठा archdr *)skb->data;
		soft = &pkt->soft.rfc1201;

		/* up to माप(pkt->soft) has alपढ़ोy
		 * been copied from the card
		 */
		स_नकल(pkt, pkthdr, माप(काष्ठा archdr));
		अगर (length > माप(pkt->soft))
			lp->hw.copy_from_card(dev, bufnum,
					      ofs + माप(pkt->soft),
					      pkt->soft.raw + माप(pkt->soft),
					      length - माप(pkt->soft));

		/* ARP packets have problems when sent from some DOS प्रणालीs:
		 * the source address is always 0!
		 * So we take the hardware source addr (which is impossible
		 * to fumble) and insert it ourselves.
		 */
		अगर (soft->proto == ARC_P_ARP) अणु
			काष्ठा arphdr *arp = (काष्ठा arphdr *)soft->payload;

			/* make sure addresses are the right length */
			अगर (arp->ar_hln == 1 && arp->ar_pln == 4) अणु
				uपूर्णांक8_t *cptr = (uपूर्णांक8_t *)arp + माप(काष्ठा arphdr);

				अगर (!*cptr) अणु	/* is saddr = 00? */
					arc_prपूर्णांकk(D_EXTRA, dev,
						   "ARP source address was 00h, set to %02Xh\n",
						   saddr);
					dev->stats.rx_crc_errors++;
					*cptr = saddr;
				पूर्ण अन्यथा अणु
					arc_prपूर्णांकk(D_DURING, dev, "ARP source address (%Xh) is fine.\n",
						   *cptr);
				पूर्ण
			पूर्ण अन्यथा अणु
				arc_prपूर्णांकk(D_NORMAL, dev, "funny-shaped ARP packet. (%Xh, %Xh)\n",
					   arp->ar_hln, arp->ar_pln);
				dev->stats.rx_errors++;
				dev->stats.rx_crc_errors++;
			पूर्ण
		पूर्ण
		अगर (BUGLVL(D_SKB))
			arcnet_dump_skb(dev, skb, "rx");

		skb->protocol = type_trans(skb, dev);
		netअगर_rx(skb);
	पूर्ण अन्यथा अणु		/* split packet */
		/* NOTE: MSDOS ARP packet correction should only need to
		 * apply to unsplit packets, since ARP packets are so लघु.
		 *
		 * My पूर्णांकerpretation of the RFC1201 करोcument is that अगर a
		 * packet is received out of order, the entire assembly
		 * process should be पातed.
		 *
		 * The RFC also mentions "it is possible क्रम successfully
		 * received packets to be retransmitted." As of 0.40 all
		 * previously received packets are allowed, not just the
		 * most recent one.
		 *
		 * We allow multiple assembly processes, one क्रम each
		 * ARCnet card possible on the network.
		 * Seems rather like a waste of memory, but there's no
		 * other way to be reliable.
		 */

		arc_prपूर्णांकk(D_RX, dev, "packet is split (splitflag=%d, seq=%d)\n",
			   soft->split_flag, in->sequence);

		अगर (in->skb && in->sequence != soft->sequence) अणु
			arc_prपूर्णांकk(D_EXTRA, dev, "wrong seq number (saddr=%d, expected=%d, seq=%d, splitflag=%d)\n",
				   saddr, in->sequence, soft->sequence,
				   soft->split_flag);
			dev_kमुक्त_skb_irq(in->skb);
			in->skb = शून्य;
			dev->stats.rx_errors++;
			dev->stats.rx_missed_errors++;
			in->lastpacket = in->numpackets = 0;
		पूर्ण
		अगर (soft->split_flag & 1) अणु	/* first packet in split */
			arc_prपूर्णांकk(D_RX, dev, "brand new splitpacket (splitflag=%d)\n",
				   soft->split_flag);
			अगर (in->skb) अणु	/* alपढ़ोy assembling one! */
				arc_prपूर्णांकk(D_EXTRA, dev, "aborting previous (seq=%d) assembly (splitflag=%d, seq=%d)\n",
					   in->sequence, soft->split_flag,
					   soft->sequence);
				dev->stats.rx_errors++;
				dev->stats.rx_missed_errors++;
				dev_kमुक्त_skb_irq(in->skb);
			पूर्ण
			in->sequence = soft->sequence;
			in->numpackets = ((अचिन्हित)soft->split_flag >> 1) + 2;
			in->lastpacket = 1;

			अगर (in->numpackets > 16) अणु
				arc_prपूर्णांकk(D_EXTRA, dev, "incoming packet more than 16 segments; dropping. (splitflag=%d)\n",
					   soft->split_flag);
				lp->rfc1201.पातed_seq = soft->sequence;
				dev->stats.rx_errors++;
				dev->stats.rx_length_errors++;
				वापस;
			पूर्ण
			in->skb = skb = alloc_skb(508 * in->numpackets + ARC_HDR_SIZE,
						  GFP_ATOMIC);
			अगर (!skb) अणु
				arc_prपूर्णांकk(D_NORMAL, dev, "(split) memory squeeze, dropping packet.\n");
				lp->rfc1201.पातed_seq = soft->sequence;
				dev->stats.rx_dropped++;
				वापस;
			पूर्ण
			skb->dev = dev;
			pkt = (काष्ठा archdr *)skb->data;
			soft = &pkt->soft.rfc1201;

			स_नकल(pkt, pkthdr, ARC_HDR_SIZE + RFC1201_HDR_SIZE);
			skb_put(skb, ARC_HDR_SIZE + RFC1201_HDR_SIZE);

			soft->split_flag = 0;	/* end result won't be split */
		पूर्ण अन्यथा अणु	/* not first packet */
			पूर्णांक packetnum = ((अचिन्हित)soft->split_flag >> 1) + 1;

			/* अगर we're not assembling, there's no poपूर्णांक trying to
			 * जारी.
			 */
			अगर (!in->skb) अणु
				अगर (lp->rfc1201.पातed_seq != soft->sequence) अणु
					arc_prपूर्णांकk(D_EXTRA, dev, "can't continue split without starting first! (splitflag=%d, seq=%d, aborted=%d)\n",
						   soft->split_flag,
						   soft->sequence,
						   lp->rfc1201.पातed_seq);
					dev->stats.rx_errors++;
					dev->stats.rx_missed_errors++;
				पूर्ण
				वापस;
			पूर्ण
			in->lastpacket++;
			/* अगर not the right flag */
			अगर (packetnum != in->lastpacket) अणु
				/* harmless duplicate? ignore. */
				अगर (packetnum <= in->lastpacket - 1) अणु
					arc_prपूर्णांकk(D_EXTRA, dev, "duplicate splitpacket ignored! (splitflag=%d)\n",
						   soft->split_flag);
					dev->stats.rx_errors++;
					dev->stats.rx_frame_errors++;
					वापस;
				पूर्ण
				/* "bad" duplicate, समाप्त reassembly */
				arc_prपूर्णांकk(D_EXTRA, dev, "out-of-order splitpacket, reassembly (seq=%d) aborted (splitflag=%d, seq=%d)\n",
					   in->sequence, soft->split_flag,
					   soft->sequence);
				lp->rfc1201.पातed_seq = soft->sequence;
				dev_kमुक्त_skb_irq(in->skb);
				in->skb = शून्य;
				dev->stats.rx_errors++;
				dev->stats.rx_missed_errors++;
				in->lastpacket = in->numpackets = 0;
				वापस;
			पूर्ण
			pkt = (काष्ठा archdr *)in->skb->data;
			soft = &pkt->soft.rfc1201;
		पूर्ण

		skb = in->skb;

		lp->hw.copy_from_card(dev, bufnum, ofs + RFC1201_HDR_SIZE,
				      skb->data + skb->len,
				      length - RFC1201_HDR_SIZE);
		skb_put(skb, length - RFC1201_HDR_SIZE);

		/* are we करोne? */
		अगर (in->lastpacket == in->numpackets) अणु
			in->skb = शून्य;
			in->lastpacket = in->numpackets = 0;

			arc_prपूर्णांकk(D_SKB_SIZE, dev, "skb: received %d bytes from %02X (unsplit)\n",
				   skb->len, pkt->hard.source);
			arc_prपूर्णांकk(D_SKB_SIZE, dev, "skb: received %d bytes from %02X (split)\n",
				   skb->len, pkt->hard.source);
			अगर (BUGLVL(D_SKB))
				arcnet_dump_skb(dev, skb, "rx");

			skb->protocol = type_trans(skb, dev);
			netअगर_rx(skb);
		पूर्ण
	पूर्ण
पूर्ण

/* Create the ARCnet hard/soft headers क्रम RFC1201. */
अटल पूर्णांक build_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			अचिन्हित लघु type, uपूर्णांक8_t daddr)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक hdr_size = ARC_HDR_SIZE + RFC1201_HDR_SIZE;
	काष्ठा archdr *pkt = skb_push(skb, hdr_size);
	काष्ठा arc_rfc1201 *soft = &pkt->soft.rfc1201;

	/* set the protocol ID according to RFC1201 */
	चयन (type) अणु
	हाल ETH_P_IP:
		soft->proto = ARC_P_IP;
		अवरोध;
	हाल ETH_P_IPV6:
		soft->proto = ARC_P_IPV6;
		अवरोध;
	हाल ETH_P_ARP:
		soft->proto = ARC_P_ARP;
		अवरोध;
	हाल ETH_P_RARP:
		soft->proto = ARC_P_RARP;
		अवरोध;
	हाल ETH_P_IPX:
	हाल ETH_P_802_3:
	हाल ETH_P_802_2:
		soft->proto = ARC_P_IPX;
		अवरोध;
	हाल ETH_P_ATALK:
		soft->proto = ARC_P_ATALK;
		अवरोध;
	शेष:
		arc_prपूर्णांकk(D_NORMAL, dev, "RFC1201: I don't understand protocol %d (%Xh)\n",
			   type, type);
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
		वापस 0;
	पूर्ण

	/* Set the source hardware address.
	 *
	 * This is pretty poपूर्णांकless क्रम most purposes, but it can help in
	 * debugging.  ARCnet करोes not allow us to change the source address
	 * in the actual packet sent.
	 */
	pkt->hard.source = *dev->dev_addr;

	soft->sequence = htons(lp->rfc1201.sequence++);
	soft->split_flag = 0;	/* split packets are करोne अन्यथाwhere */

	/* see linux/net/ethernet/eth.c to see where I got the following */

	अगर (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) अणु
		/* FIXME: fill in the last byte of the dest ipaddr here
		 * to better comply with RFC1051 in "noarp" mode.
		 * For now, always broadcasting will probably at least get
		 * packets sent out :)
		 */
		pkt->hard.dest = 0;
		वापस hdr_size;
	पूर्ण
	/* otherwise, drop in the dest address */
	pkt->hard.dest = daddr;
	वापस hdr_size;
पूर्ण

अटल व्योम load_pkt(काष्ठा net_device *dev, काष्ठा arc_hardware *hard,
		     काष्ठा arc_rfc1201 *soft, पूर्णांक softlen, पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक ofs;

	/* assume length <= XMTU: someone should have handled that by now. */

	अगर (softlen > MinTU) अणु
		hard->offset[0] = 0;
		hard->offset[1] = ofs = 512 - softlen;
	पूर्ण अन्यथा अगर (softlen > MTU) अणु	/* exception packet - add an extra header */
		काष्ठा arc_rfc1201 excsoft;

		excsoft.proto = soft->proto;
		excsoft.split_flag = 0xff;
		excsoft.sequence = htons(0xffff);

		hard->offset[0] = 0;
		ofs = 512 - softlen;
		hard->offset[1] = ofs - RFC1201_HDR_SIZE;
		lp->hw.copy_to_card(dev, bufnum, ofs - RFC1201_HDR_SIZE,
				    &excsoft, RFC1201_HDR_SIZE);
	पूर्ण अन्यथा अणु
		hard->offset[0] = ofs = 256 - softlen;
	पूर्ण

	lp->hw.copy_to_card(dev, bufnum, 0, hard, ARC_HDR_SIZE);
	lp->hw.copy_to_card(dev, bufnum, ofs, soft, softlen);

	lp->lastload_dest = hard->dest;
पूर्ण

अटल पूर्णांक prepare_tx(काष्ठा net_device *dev, काष्ठा archdr *pkt, पूर्णांक length,
		      पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	स्थिर पूर्णांक maxsegsize = XMTU - RFC1201_HDR_SIZE;
	काष्ठा Outgoing *out;

	arc_prपूर्णांकk(D_DURING, dev, "prepare_tx: txbufs=%d/%d/%d\n",
		   lp->next_tx, lp->cur_tx, bufnum);

	/* hard header is not included in packet length */
	length -= ARC_HDR_SIZE;
	pkt->soft.rfc1201.split_flag = 0;

	/* need to करो a split packet? */
	अगर (length > XMTU) अणु
		out = &lp->outgoing;

		out->length = length - RFC1201_HDR_SIZE;
		out->dataleft = lp->outgoing.length;
		out->numsegs = (out->dataleft + maxsegsize - 1) / maxsegsize;
		out->segnum = 0;

		arc_prपूर्णांकk(D_DURING, dev, "rfc1201 prep_tx: ready for %d-segment split (%d bytes, seq=%d)\n",
			   out->numsegs, out->length,
			   pkt->soft.rfc1201.sequence);

		वापस 0;	/* not करोne */
	पूर्ण
	/* just load the packet पूर्णांकo the buffers and send it off */
	load_pkt(dev, &pkt->hard, &pkt->soft.rfc1201, length, bufnum);

	वापस 1;		/* करोne */
पूर्ण

अटल पूर्णांक जारी_tx(काष्ठा net_device *dev, पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा Outgoing *out = &lp->outgoing;
	काष्ठा arc_hardware *hard = &out->pkt->hard;
	काष्ठा arc_rfc1201 *soft = &out->pkt->soft.rfc1201, *newsoft;
	पूर्णांक maxsegsize = XMTU - RFC1201_HDR_SIZE;
	पूर्णांक seglen;

	arc_prपूर्णांकk(D_DURING, dev,
		   "rfc1201 continue_tx: loading segment %d(+1) of %d (seq=%d)\n",
		   out->segnum, out->numsegs, soft->sequence);

	/* the "new" soft header comes right beक्रमe the data chunk */
	newsoft = (काष्ठा arc_rfc1201 *)
	    (out->pkt->soft.raw + out->length - out->dataleft);

	अगर (!out->segnum)	/* first packet; newsoft == soft */
		newsoft->split_flag = ((out->numsegs - 2) << 1) | 1;
	अन्यथा अणु
		newsoft->split_flag = out->segnum << 1;
		newsoft->proto = soft->proto;
		newsoft->sequence = soft->sequence;
	पूर्ण

	seglen = maxsegsize;
	अगर (seglen > out->dataleft)
		seglen = out->dataleft;
	out->dataleft -= seglen;

	load_pkt(dev, hard, newsoft, seglen + RFC1201_HDR_SIZE, bufnum);

	out->segnum++;
	अगर (out->segnum >= out->numsegs)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
