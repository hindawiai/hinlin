<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN IPv6 UDP compression according to RFC6282
 *
 *	Authors:
 *	Alexander Aring	<aar@pengutronix.de>
 *
 *	Original written by:
 *	Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 *	Jon Smirl <jonsmirl@gmail.com>
 */

#समावेश "nhc.h"

#घोषणा LOWPAN_NHC_UDP_MASK		0xF8
#घोषणा LOWPAN_NHC_UDP_ID		0xF0
#घोषणा LOWPAN_NHC_UDP_IDLEN		1

#घोषणा LOWPAN_NHC_UDP_4BIT_PORT	0xF0B0
#घोषणा LOWPAN_NHC_UDP_4BIT_MASK	0xFFF0
#घोषणा LOWPAN_NHC_UDP_8BIT_PORT	0xF000
#घोषणा LOWPAN_NHC_UDP_8BIT_MASK	0xFF00

/* values क्रम port compression, _with checksum_ ie bit 5 set to 0 */

/* all अंतरभूत */
#घोषणा LOWPAN_NHC_UDP_CS_P_00	0xF0
/* source 16bit अंतरभूत, dest = 0xF0 + 8 bit अंतरभूत */
#घोषणा LOWPAN_NHC_UDP_CS_P_01	0xF1
/* source = 0xF0 + 8bit अंतरभूत, dest = 16 bit अंतरभूत */
#घोषणा LOWPAN_NHC_UDP_CS_P_10	0xF2
/* source & dest = 0xF0B + 4bit अंतरभूत */
#घोषणा LOWPAN_NHC_UDP_CS_P_11	0xF3
/* checksum elided */
#घोषणा LOWPAN_NHC_UDP_CS_C	0x04

अटल पूर्णांक udp_uncompress(काष्ठा sk_buff *skb, माप_प्रकार needed)
अणु
	u8 पंचांगp = 0, val = 0;
	काष्ठा udphdr uh;
	bool fail;
	पूर्णांक err;

	fail = lowpan_fetch_skb(skb, &पंचांगp, माप(पंचांगp));

	pr_debug("UDP header uncompression\n");
	चयन (पंचांगp & LOWPAN_NHC_UDP_CS_P_11) अणु
	हाल LOWPAN_NHC_UDP_CS_P_00:
		fail |= lowpan_fetch_skb(skb, &uh.source, माप(uh.source));
		fail |= lowpan_fetch_skb(skb, &uh.dest, माप(uh.dest));
		अवरोध;
	हाल LOWPAN_NHC_UDP_CS_P_01:
		fail |= lowpan_fetch_skb(skb, &uh.source, माप(uh.source));
		fail |= lowpan_fetch_skb(skb, &val, माप(val));
		uh.dest = htons(val + LOWPAN_NHC_UDP_8BIT_PORT);
		अवरोध;
	हाल LOWPAN_NHC_UDP_CS_P_10:
		fail |= lowpan_fetch_skb(skb, &val, माप(val));
		uh.source = htons(val + LOWPAN_NHC_UDP_8BIT_PORT);
		fail |= lowpan_fetch_skb(skb, &uh.dest, माप(uh.dest));
		अवरोध;
	हाल LOWPAN_NHC_UDP_CS_P_11:
		fail |= lowpan_fetch_skb(skb, &val, माप(val));
		uh.source = htons(LOWPAN_NHC_UDP_4BIT_PORT + (val >> 4));
		uh.dest = htons(LOWPAN_NHC_UDP_4BIT_PORT + (val & 0x0f));
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	pr_debug("uncompressed UDP ports: src = %d, dst = %d\n",
		 ntohs(uh.source), ntohs(uh.dest));

	/* checksum */
	अगर (पंचांगp & LOWPAN_NHC_UDP_CS_C) अणु
		pr_debug_ratelimited("checksum elided currently not supported\n");
		fail = true;
	पूर्ण अन्यथा अणु
		fail |= lowpan_fetch_skb(skb, &uh.check, माप(uh.check));
	पूर्ण

	अगर (fail)
		वापस -EINVAL;

	/* UDP length needs to be inferred from the lower layers
	 * here, we obtain the hपूर्णांक from the reमुख्यing size of the
	 * frame
	 */
	चयन (lowpan_dev(skb->dev)->lltype) अणु
	हाल LOWPAN_LLTYPE_IEEE802154:
		अगर (lowpan_802154_cb(skb)->d_size)
			uh.len = htons(lowpan_802154_cb(skb)->d_size -
				       माप(काष्ठा ipv6hdr));
		अन्यथा
			uh.len = htons(skb->len + माप(काष्ठा udphdr));
		अवरोध;
	शेष:
		uh.len = htons(skb->len + माप(काष्ठा udphdr));
		अवरोध;
	पूर्ण
	pr_debug("uncompressed UDP length: src = %d", ntohs(uh.len));

	/* replace the compressed UDP head by the uncompressed UDP
	 * header
	 */
	err = skb_cow(skb, needed);
	अगर (unlikely(err))
		वापस err;

	skb_push(skb, माप(काष्ठा udphdr));
	skb_copy_to_linear_data(skb, &uh, माप(काष्ठा udphdr));

	वापस 0;
पूर्ण

अटल पूर्णांक udp_compress(काष्ठा sk_buff *skb, u8 **hc_ptr)
अणु
	स्थिर काष्ठा udphdr *uh = udp_hdr(skb);
	u8 पंचांगp;

	अगर (((ntohs(uh->source) & LOWPAN_NHC_UDP_4BIT_MASK) ==
	     LOWPAN_NHC_UDP_4BIT_PORT) &&
	    ((ntohs(uh->dest) & LOWPAN_NHC_UDP_4BIT_MASK) ==
	     LOWPAN_NHC_UDP_4BIT_PORT)) अणु
		pr_debug("UDP header: both ports compression to 4 bits\n");
		/* compression value */
		पंचांगp = LOWPAN_NHC_UDP_CS_P_11;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
		/* source and destination port */
		पंचांगp = ntohs(uh->dest) - LOWPAN_NHC_UDP_4BIT_PORT +
		      ((ntohs(uh->source) - LOWPAN_NHC_UDP_4BIT_PORT) << 4);
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
	पूर्ण अन्यथा अगर ((ntohs(uh->dest) & LOWPAN_NHC_UDP_8BIT_MASK) ==
			LOWPAN_NHC_UDP_8BIT_PORT) अणु
		pr_debug("UDP header: remove 8 bits of dest\n");
		/* compression value */
		पंचांगp = LOWPAN_NHC_UDP_CS_P_01;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
		/* source port */
		lowpan_push_hc_data(hc_ptr, &uh->source, माप(uh->source));
		/* destination port */
		पंचांगp = ntohs(uh->dest) - LOWPAN_NHC_UDP_8BIT_PORT;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
	पूर्ण अन्यथा अगर ((ntohs(uh->source) & LOWPAN_NHC_UDP_8BIT_MASK) ==
			LOWPAN_NHC_UDP_8BIT_PORT) अणु
		pr_debug("UDP header: remove 8 bits of source\n");
		/* compression value */
		पंचांगp = LOWPAN_NHC_UDP_CS_P_10;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
		/* source port */
		पंचांगp = ntohs(uh->source) - LOWPAN_NHC_UDP_8BIT_PORT;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
		/* destination port */
		lowpan_push_hc_data(hc_ptr, &uh->dest, माप(uh->dest));
	पूर्ण अन्यथा अणु
		pr_debug("UDP header: can't compress\n");
		/* compression value */
		पंचांगp = LOWPAN_NHC_UDP_CS_P_00;
		lowpan_push_hc_data(hc_ptr, &पंचांगp, माप(पंचांगp));
		/* source port */
		lowpan_push_hc_data(hc_ptr, &uh->source, माप(uh->source));
		/* destination port */
		lowpan_push_hc_data(hc_ptr, &uh->dest, माप(uh->dest));
	पूर्ण

	/* checksum is always अंतरभूत */
	lowpan_push_hc_data(hc_ptr, &uh->check, माप(uh->check));

	वापस 0;
पूर्ण

अटल व्योम udp_nhid_setup(काष्ठा lowpan_nhc *nhc)
अणु
	nhc->id[0] = LOWPAN_NHC_UDP_ID;
	nhc->idmask[0] = LOWPAN_NHC_UDP_MASK;
पूर्ण

LOWPAN_NHC(nhc_udp, "RFC6282 UDP", NEXTHDR_UDP, माप(काष्ठा udphdr),
	   udp_nhid_setup, LOWPAN_NHC_UDP_IDLEN, udp_uncompress, udp_compress);

module_lowpan_nhc(nhc_udp);
MODULE_DESCRIPTION("6LoWPAN next header RFC6282 UDP compression");
MODULE_LICENSE("GPL");
