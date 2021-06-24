<शैली गुरु>
/*
 * Copyright 2011, Siemens AG
 * written by Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

/* Based on patches from Jon Smirl <jonsmirl@gmail.com>
 * Copyright (c) 2011 Jon Smirl <jonsmirl@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

/* Jon's code is based on 6lowpan implementation क्रम Contiki which is:
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>

#समावेश <net/6lowpan.h>
#समावेश <net/ipv6.h>

#समावेश "6lowpan_i.h"
#समावेश "nhc.h"

/* Values of fields within the IPHC encoding first byte */
#घोषणा LOWPAN_IPHC_TF_MASK	0x18
#घोषणा LOWPAN_IPHC_TF_00	0x00
#घोषणा LOWPAN_IPHC_TF_01	0x08
#घोषणा LOWPAN_IPHC_TF_10	0x10
#घोषणा LOWPAN_IPHC_TF_11	0x18

#घोषणा LOWPAN_IPHC_NH		0x04

#घोषणा LOWPAN_IPHC_HLIM_MASK	0x03
#घोषणा LOWPAN_IPHC_HLIM_00	0x00
#घोषणा LOWPAN_IPHC_HLIM_01	0x01
#घोषणा LOWPAN_IPHC_HLIM_10	0x02
#घोषणा LOWPAN_IPHC_HLIM_11	0x03

/* Values of fields within the IPHC encoding second byte */
#घोषणा LOWPAN_IPHC_CID		0x80

#घोषणा LOWPAN_IPHC_SAC		0x40

#घोषणा LOWPAN_IPHC_SAM_MASK	0x30
#घोषणा LOWPAN_IPHC_SAM_00	0x00
#घोषणा LOWPAN_IPHC_SAM_01	0x10
#घोषणा LOWPAN_IPHC_SAM_10	0x20
#घोषणा LOWPAN_IPHC_SAM_11	0x30

#घोषणा LOWPAN_IPHC_M		0x08

#घोषणा LOWPAN_IPHC_DAC		0x04

#घोषणा LOWPAN_IPHC_DAM_MASK	0x03
#घोषणा LOWPAN_IPHC_DAM_00	0x00
#घोषणा LOWPAN_IPHC_DAM_01	0x01
#घोषणा LOWPAN_IPHC_DAM_10	0x02
#घोषणा LOWPAN_IPHC_DAM_11	0x03

/* ipv6 address based on mac
 * second bit-flip (Universe/Local) is करोne according RFC2464
 */
#घोषणा is_addr_mac_addr_based(a, m) \
	((((a)->s6_addr[8])  == (((m)[0]) ^ 0x02)) &&	\
	 (((a)->s6_addr[9])  == (m)[1]) &&		\
	 (((a)->s6_addr[10]) == (m)[2]) &&		\
	 (((a)->s6_addr[11]) == (m)[3]) &&		\
	 (((a)->s6_addr[12]) == (m)[4]) &&		\
	 (((a)->s6_addr[13]) == (m)[5]) &&		\
	 (((a)->s6_addr[14]) == (m)[6]) &&		\
	 (((a)->s6_addr[15]) == (m)[7]))

/* check whether we can compress the IID to 16 bits,
 * it's possible क्रम unicast addresses with first 49 bits are zero only.
 */
#घोषणा lowpan_is_iid_16_bit_compressable(a)	\
	((((a)->s6_addr16[4]) == 0) &&		\
	 (((a)->s6_addr[10]) == 0) &&		\
	 (((a)->s6_addr[11]) == 0xff) &&	\
	 (((a)->s6_addr[12]) == 0xfe) &&	\
	 (((a)->s6_addr[13]) == 0))

/* check whether the 112-bit gid of the multicast address is mappable to: */

/* 48 bits, FFXX::00XX:XXXX:XXXX */
#घोषणा lowpan_is_mcast_addr_compressable48(a)	\
	((((a)->s6_addr16[1]) == 0) &&		\
	 (((a)->s6_addr16[2]) == 0) &&		\
	 (((a)->s6_addr16[3]) == 0) &&		\
	 (((a)->s6_addr16[4]) == 0) &&		\
	 (((a)->s6_addr[10]) == 0))

/* 32 bits, FFXX::00XX:XXXX */
#घोषणा lowpan_is_mcast_addr_compressable32(a)	\
	((((a)->s6_addr16[1]) == 0) &&		\
	 (((a)->s6_addr16[2]) == 0) &&		\
	 (((a)->s6_addr16[3]) == 0) &&		\
	 (((a)->s6_addr16[4]) == 0) &&		\
	 (((a)->s6_addr16[5]) == 0) &&		\
	 (((a)->s6_addr[12]) == 0))

/* 8 bits, FF02::00XX */
#घोषणा lowpan_is_mcast_addr_compressable8(a)	\
	((((a)->s6_addr[1])  == 2) &&		\
	 (((a)->s6_addr16[1]) == 0) &&		\
	 (((a)->s6_addr16[2]) == 0) &&		\
	 (((a)->s6_addr16[3]) == 0) &&		\
	 (((a)->s6_addr16[4]) == 0) &&		\
	 (((a)->s6_addr16[5]) == 0) &&		\
	 (((a)->s6_addr16[6]) == 0) &&		\
	 (((a)->s6_addr[14]) == 0))

#घोषणा lowpan_is_linklocal_zero_padded(a)	\
	(!(hdr->saddr.s6_addr[1] & 0x3f) &&	\
	 !hdr->saddr.s6_addr16[1] &&		\
	 !hdr->saddr.s6_addr32[1])

#घोषणा LOWPAN_IPHC_CID_DCI(cid)	(cid & 0x0f)
#घोषणा LOWPAN_IPHC_CID_SCI(cid)	((cid & 0xf0) >> 4)

अटल अंतरभूत व्योम
lowpan_iphc_uncompress_802154_lladdr(काष्ठा in6_addr *ipaddr,
				     स्थिर व्योम *lladdr)
अणु
	स्थिर काष्ठा ieee802154_addr *addr = lladdr;
	u8 eui64[EUI64_ADDR_LEN];

	चयन (addr->mode) अणु
	हाल IEEE802154_ADDR_LONG:
		ieee802154_le64_to_be64(eui64, &addr->extended_addr);
		lowpan_iphc_uncompress_eui64_lladdr(ipaddr, eui64);
		अवरोध;
	हाल IEEE802154_ADDR_SHORT:
		/* fe:80::ff:fe00:XXXX
		 *                \__/
		 *             लघु_addr
		 *
		 * Universe/Local bit is zero.
		 */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		ipaddr->s6_addr[11] = 0xFF;
		ipaddr->s6_addr[12] = 0xFE;
		ieee802154_le16_to_be16(&ipaddr->s6_addr16[7],
					&addr->लघु_addr);
		अवरोध;
	शेष:
		/* should never handled and filtered by 802154 6lowpan */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा lowpan_iphc_ctx *
lowpan_iphc_ctx_get_by_id(स्थिर काष्ठा net_device *dev, u8 id)
अणु
	काष्ठा lowpan_iphc_ctx *ret = &lowpan_dev(dev)->ctx.table[id];

	अगर (!lowpan_iphc_ctx_is_active(ret))
		वापस शून्य;

	वापस ret;
पूर्ण

अटल काष्ठा lowpan_iphc_ctx *
lowpan_iphc_ctx_get_by_addr(स्थिर काष्ठा net_device *dev,
			    स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा lowpan_iphc_ctx *table = lowpan_dev(dev)->ctx.table;
	काष्ठा lowpan_iphc_ctx *ret = शून्य;
	काष्ठा in6_addr addr_pfx;
	u8 addr_plen;
	पूर्णांक i;

	क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++) अणु
		/* Check अगर context is valid. A context that is not valid
		 * MUST NOT be used क्रम compression.
		 */
		अगर (!lowpan_iphc_ctx_is_active(&table[i]) ||
		    !lowpan_iphc_ctx_is_compression(&table[i]))
			जारी;

		ipv6_addr_prefix(&addr_pfx, addr, table[i].plen);

		/* अगर prefix len < 64, the reमुख्यing bits until 64th bit is
		 * zero. Otherwise we use table[i]->plen.
		 */
		अगर (table[i].plen < 64)
			addr_plen = 64;
		अन्यथा
			addr_plen = table[i].plen;

		अगर (ipv6_prefix_equal(&addr_pfx, &table[i].pfx, addr_plen)) अणु
			/* remember first match */
			अगर (!ret) अणु
				ret = &table[i];
				जारी;
			पूर्ण

			/* get the context with दीर्घest prefix len */
			अगर (table[i].plen > ret->plen)
				ret = &table[i];
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा lowpan_iphc_ctx *
lowpan_iphc_ctx_get_by_mcast_addr(स्थिर काष्ठा net_device *dev,
				  स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा lowpan_iphc_ctx *table = lowpan_dev(dev)->ctx.table;
	काष्ठा lowpan_iphc_ctx *ret = शून्य;
	काष्ठा in6_addr addr_mcast, network_pfx = अणुपूर्ण;
	पूर्णांक i;

	/* init mcast address with  */
	स_नकल(&addr_mcast, addr, माप(*addr));

	क्रम (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++) अणु
		/* Check अगर context is valid. A context that is not valid
		 * MUST NOT be used क्रम compression.
		 */
		अगर (!lowpan_iphc_ctx_is_active(&table[i]) ||
		    !lowpan_iphc_ctx_is_compression(&table[i]))
			जारी;

		/* setting plen */
		addr_mcast.s6_addr[3] = table[i].plen;
		/* get network prefix to copy पूर्णांकo multicast address */
		ipv6_addr_prefix(&network_pfx, &table[i].pfx,
				 table[i].plen);
		/* setting network prefix */
		स_नकल(&addr_mcast.s6_addr[4], &network_pfx, 8);

		अगर (ipv6_addr_equal(addr, &addr_mcast)) अणु
			ret = &table[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम lowpan_iphc_uncompress_lladdr(स्थिर काष्ठा net_device *dev,
					  काष्ठा in6_addr *ipaddr,
					  स्थिर व्योम *lladdr)
अणु
	चयन (dev->addr_len) अणु
	हाल ETH_ALEN:
		lowpan_iphc_uncompress_eui48_lladdr(ipaddr, lladdr);
		अवरोध;
	हाल EUI64_ADDR_LEN:
		lowpan_iphc_uncompress_eui64_lladdr(ipaddr, lladdr);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
पूर्ण

/* Uncompress address function क्रम source and
 * destination address(non-multicast).
 *
 * address_mode is the masked value क्रम sam or dam value
 */
अटल पूर्णांक lowpan_iphc_uncompress_addr(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा net_device *dev,
				       काष्ठा in6_addr *ipaddr,
				       u8 address_mode, स्थिर व्योम *lladdr)
अणु
	bool fail;

	चयन (address_mode) अणु
	/* SAM and DAM are the same here */
	हाल LOWPAN_IPHC_DAM_00:
		/* क्रम global link addresses */
		fail = lowpan_fetch_skb(skb, ipaddr->s6_addr, 16);
		अवरोध;
	हाल LOWPAN_IPHC_SAM_01:
	हाल LOWPAN_IPHC_DAM_01:
		/* fe:80::XXXX:XXXX:XXXX:XXXX */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[8], 8);
		अवरोध;
	हाल LOWPAN_IPHC_SAM_10:
	हाल LOWPAN_IPHC_DAM_10:
		/* fe:80::ff:fe00:XXXX */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		ipaddr->s6_addr[11] = 0xFF;
		ipaddr->s6_addr[12] = 0xFE;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[14], 2);
		अवरोध;
	हाल LOWPAN_IPHC_SAM_11:
	हाल LOWPAN_IPHC_DAM_11:
		fail = false;
		चयन (lowpan_dev(dev)->lltype) अणु
		हाल LOWPAN_LLTYPE_IEEE802154:
			lowpan_iphc_uncompress_802154_lladdr(ipaddr, lladdr);
			अवरोध;
		शेष:
			lowpan_iphc_uncompress_lladdr(dev, ipaddr, lladdr);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		pr_debug("Invalid address mode value: 0x%x\n", address_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (fail) अणु
		pr_debug("Failed to fetch skb data\n");
		वापस -EIO;
	पूर्ण

	raw_dump_अंतरभूत(शून्य, "Reconstructed ipv6 addr is",
			ipaddr->s6_addr, 16);

	वापस 0;
पूर्ण

/* Uncompress address function क्रम source context
 * based address(non-multicast).
 */
अटल पूर्णांक lowpan_iphc_uncompress_ctx_addr(काष्ठा sk_buff *skb,
					   स्थिर काष्ठा net_device *dev,
					   स्थिर काष्ठा lowpan_iphc_ctx *ctx,
					   काष्ठा in6_addr *ipaddr,
					   u8 address_mode, स्थिर व्योम *lladdr)
अणु
	bool fail;

	चयन (address_mode) अणु
	/* SAM and DAM are the same here */
	हाल LOWPAN_IPHC_DAM_00:
		fail = false;
		/* SAM_00 -> unspec address ::
		 * Do nothing, address is alपढ़ोy ::
		 *
		 * DAM 00 -> reserved should never occur.
		 */
		अवरोध;
	हाल LOWPAN_IPHC_SAM_01:
	हाल LOWPAN_IPHC_DAM_01:
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[8], 8);
		ipv6_addr_prefix_copy(ipaddr, &ctx->pfx, ctx->plen);
		अवरोध;
	हाल LOWPAN_IPHC_SAM_10:
	हाल LOWPAN_IPHC_DAM_10:
		ipaddr->s6_addr[11] = 0xFF;
		ipaddr->s6_addr[12] = 0xFE;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[14], 2);
		ipv6_addr_prefix_copy(ipaddr, &ctx->pfx, ctx->plen);
		अवरोध;
	हाल LOWPAN_IPHC_SAM_11:
	हाल LOWPAN_IPHC_DAM_11:
		fail = false;
		चयन (lowpan_dev(dev)->lltype) अणु
		हाल LOWPAN_LLTYPE_IEEE802154:
			lowpan_iphc_uncompress_802154_lladdr(ipaddr, lladdr);
			अवरोध;
		शेष:
			lowpan_iphc_uncompress_lladdr(dev, ipaddr, lladdr);
			अवरोध;
		पूर्ण
		ipv6_addr_prefix_copy(ipaddr, &ctx->pfx, ctx->plen);
		अवरोध;
	शेष:
		pr_debug("Invalid sam value: 0x%x\n", address_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (fail) अणु
		pr_debug("Failed to fetch skb data\n");
		वापस -EIO;
	पूर्ण

	raw_dump_अंतरभूत(शून्य,
			"Reconstructed context based ipv6 src addr is",
			ipaddr->s6_addr, 16);

	वापस 0;
पूर्ण

/* Uncompress function क्रम multicast destination address,
 * when M bit is set.
 */
अटल पूर्णांक lowpan_uncompress_multicast_daddr(काष्ठा sk_buff *skb,
					     काष्ठा in6_addr *ipaddr,
					     u8 address_mode)
अणु
	bool fail;

	चयन (address_mode) अणु
	हाल LOWPAN_IPHC_DAM_00:
		/* 00:  128 bits.  The full address
		 * is carried in-line.
		 */
		fail = lowpan_fetch_skb(skb, ipaddr->s6_addr, 16);
		अवरोध;
	हाल LOWPAN_IPHC_DAM_01:
		/* 01:  48 bits.  The address takes
		 * the क्रमm ffXX::00XX:XXXX:XXXX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[1], 1);
		fail |= lowpan_fetch_skb(skb, &ipaddr->s6_addr[11], 5);
		अवरोध;
	हाल LOWPAN_IPHC_DAM_10:
		/* 10:  32 bits.  The address takes
		 * the क्रमm ffXX::00XX:XXXX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[1], 1);
		fail |= lowpan_fetch_skb(skb, &ipaddr->s6_addr[13], 3);
		अवरोध;
	हाल LOWPAN_IPHC_DAM_11:
		/* 11:  8 bits.  The address takes
		 * the क्रमm ff02::00XX.
		 */
		ipaddr->s6_addr[0] = 0xFF;
		ipaddr->s6_addr[1] = 0x02;
		fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[15], 1);
		अवरोध;
	शेष:
		pr_debug("DAM value has a wrong value: 0x%x\n", address_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (fail) अणु
		pr_debug("Failed to fetch skb data\n");
		वापस -EIO;
	पूर्ण

	raw_dump_अंतरभूत(शून्य, "Reconstructed ipv6 multicast addr is",
			ipaddr->s6_addr, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_uncompress_multicast_ctx_daddr(काष्ठा sk_buff *skb,
						 काष्ठा lowpan_iphc_ctx *ctx,
						 काष्ठा in6_addr *ipaddr,
						 u8 address_mode)
अणु
	काष्ठा in6_addr network_pfx = अणुपूर्ण;
	bool fail;

	ipaddr->s6_addr[0] = 0xFF;
	fail = lowpan_fetch_skb(skb, &ipaddr->s6_addr[1], 2);
	fail |= lowpan_fetch_skb(skb, &ipaddr->s6_addr[12], 4);
	अगर (fail)
		वापस -EIO;

	/* take prefix_len and network prefix from the context */
	ipaddr->s6_addr[3] = ctx->plen;
	/* get network prefix to copy पूर्णांकo multicast address */
	ipv6_addr_prefix(&network_pfx, &ctx->pfx, ctx->plen);
	/* setting network prefix */
	स_नकल(&ipaddr->s6_addr[4], &network_pfx, 8);

	वापस 0;
पूर्ण

/* get the ecn values from iphc tf क्रमmat and set it to ipv6hdr */
अटल अंतरभूत व्योम lowpan_iphc_tf_set_ecn(काष्ठा ipv6hdr *hdr, स्थिर u8 *tf)
अणु
	/* get the two higher bits which is ecn */
	u8 ecn = tf[0] & 0xc0;

	/* ECN takes 0x30 in hdr->flow_lbl[0] */
	hdr->flow_lbl[0] |= (ecn >> 2);
पूर्ण

/* get the dscp values from iphc tf क्रमmat and set it to ipv6hdr */
अटल अंतरभूत व्योम lowpan_iphc_tf_set_dscp(काष्ठा ipv6hdr *hdr, स्थिर u8 *tf)
अणु
	/* DSCP is at place after ECN */
	u8 dscp = tf[0] & 0x3f;

	/* The four highest bits need to be set at hdr->priority */
	hdr->priority |= ((dscp & 0x3c) >> 2);
	/* The two lower bits is part of hdr->flow_lbl[0] */
	hdr->flow_lbl[0] |= ((dscp & 0x03) << 6);
पूर्ण

/* get the flow label values from iphc tf क्रमmat and set it to ipv6hdr */
अटल अंतरभूत व्योम lowpan_iphc_tf_set_lbl(काष्ठा ipv6hdr *hdr, स्थिर u8 *lbl)
अणु
	/* flow label is always some array started with lower nibble of
	 * flow_lbl[0] and followed with two bytes afterwards. Inside अंतरभूत
	 * data the flow_lbl position can be dअगरferent, which will be handled
	 * by lbl poपूर्णांकer. E.g. हाल "01" vs "00" the traffic class is 8 bit
	 * shअगरted, the dअगरferent lbl poपूर्णांकer will handle that.
	 *
	 * The flow label will started at lower nibble of flow_lbl[0], the
	 * higher nibbles are part of DSCP + ECN.
	 */
	hdr->flow_lbl[0] |= lbl[0] & 0x0f;
	स_नकल(&hdr->flow_lbl[1], &lbl[1], 2);
पूर्ण

/* lowpan_iphc_tf_decompress - decompress the traffic class.
 *	This function will वापस zero on success, a value lower than zero अगर
 *	failed.
 */
अटल पूर्णांक lowpan_iphc_tf_decompress(काष्ठा sk_buff *skb, काष्ठा ipv6hdr *hdr,
				     u8 val)
अणु
	u8 tf[4];

	/* Traffic Class and Flow Label */
	चयन (val) अणु
	हाल LOWPAN_IPHC_TF_00:
		/* ECN + DSCP + 4-bit Pad + Flow Label (4 bytes) */
		अगर (lowpan_fetch_skb(skb, tf, 4))
			वापस -EINVAL;

		/*                      1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |  rsv  |             Flow Label                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_dscp(hdr, tf);
		lowpan_iphc_tf_set_lbl(hdr, &tf[1]);
		अवरोध;
	हाल LOWPAN_IPHC_TF_01:
		/* ECN + 2-bit Pad + Flow Label (3 bytes), DSCP is elided. */
		अगर (lowpan_fetch_skb(skb, tf, 3))
			वापस -EINVAL;

		/*                     1                   2
		 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|rsv|             Flow Label                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_lbl(hdr, &tf[0]);
		अवरोध;
	हाल LOWPAN_IPHC_TF_10:
		/* ECN + DSCP (1 byte), Flow Label is elided. */
		अगर (lowpan_fetch_skb(skb, tf, 1))
			वापस -EINVAL;

		/*  0 1 2 3 4 5 6 7
		 * +-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |
		 * +-+-+-+-+-+-+-+-+
		 */
		lowpan_iphc_tf_set_ecn(hdr, tf);
		lowpan_iphc_tf_set_dscp(hdr, tf);
		अवरोध;
	हाल LOWPAN_IPHC_TF_11:
		/* Traffic Class and Flow Label are elided */
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* TTL uncompression values */
अटल स्थिर u8 lowpan_ttl_values[] = अणु
	[LOWPAN_IPHC_HLIM_01] = 1,
	[LOWPAN_IPHC_HLIM_10] = 64,
	[LOWPAN_IPHC_HLIM_11] = 255,
पूर्ण;

पूर्णांक lowpan_header_decompress(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			     स्थिर व्योम *daddr, स्थिर व्योम *saddr)
अणु
	काष्ठा ipv6hdr hdr = अणुपूर्ण;
	काष्ठा lowpan_iphc_ctx *ci;
	u8 iphc0, iphc1, cid = 0;
	पूर्णांक err;

	raw_dump_table(__func__, "raw skb data dump uncompressed",
		       skb->data, skb->len);

	अगर (lowpan_fetch_skb(skb, &iphc0, माप(iphc0)) ||
	    lowpan_fetch_skb(skb, &iphc1, माप(iphc1)))
		वापस -EINVAL;

	hdr.version = 6;

	/* शेष CID = 0, another अगर the CID flag is set */
	अगर (iphc1 & LOWPAN_IPHC_CID) अणु
		अगर (lowpan_fetch_skb(skb, &cid, माप(cid)))
			वापस -EINVAL;
	पूर्ण

	err = lowpan_iphc_tf_decompress(skb, &hdr,
					iphc0 & LOWPAN_IPHC_TF_MASK);
	अगर (err < 0)
		वापस err;

	/* Next Header */
	अगर (!(iphc0 & LOWPAN_IPHC_NH)) अणु
		/* Next header is carried अंतरभूत */
		अगर (lowpan_fetch_skb(skb, &hdr.nexthdr, माप(hdr.nexthdr)))
			वापस -EINVAL;

		pr_debug("NH flag is set, next header carried inline: %02x\n",
			 hdr.nexthdr);
	पूर्ण

	/* Hop Limit */
	अगर ((iphc0 & LOWPAN_IPHC_HLIM_MASK) != LOWPAN_IPHC_HLIM_00) अणु
		hdr.hop_limit = lowpan_ttl_values[iphc0 & LOWPAN_IPHC_HLIM_MASK];
	पूर्ण अन्यथा अणु
		अगर (lowpan_fetch_skb(skb, &hdr.hop_limit,
				     माप(hdr.hop_limit)))
			वापस -EINVAL;
	पूर्ण

	अगर (iphc1 & LOWPAN_IPHC_SAC) अणु
		spin_lock_bh(&lowpan_dev(dev)->ctx.lock);
		ci = lowpan_iphc_ctx_get_by_id(dev, LOWPAN_IPHC_CID_SCI(cid));
		अगर (!ci) अणु
			spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
			वापस -EINVAL;
		पूर्ण

		pr_debug("SAC bit is set. Handle context based source address.\n");
		err = lowpan_iphc_uncompress_ctx_addr(skb, dev, ci, &hdr.saddr,
						      iphc1 & LOWPAN_IPHC_SAM_MASK,
						      saddr);
		spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
	पूर्ण अन्यथा अणु
		/* Source address uncompression */
		pr_debug("source address stateless compression\n");
		err = lowpan_iphc_uncompress_addr(skb, dev, &hdr.saddr,
						  iphc1 & LOWPAN_IPHC_SAM_MASK,
						  saddr);
	पूर्ण

	/* Check on error of previous branch */
	अगर (err)
		वापस -EINVAL;

	चयन (iphc1 & (LOWPAN_IPHC_M | LOWPAN_IPHC_DAC)) अणु
	हाल LOWPAN_IPHC_M | LOWPAN_IPHC_DAC:
		skb->pkt_type = PACKET_BROADCAST;

		spin_lock_bh(&lowpan_dev(dev)->ctx.lock);
		ci = lowpan_iphc_ctx_get_by_id(dev, LOWPAN_IPHC_CID_DCI(cid));
		अगर (!ci) अणु
			spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
			वापस -EINVAL;
		पूर्ण

		/* multicast with context */
		pr_debug("dest: context-based mcast compression\n");
		err = lowpan_uncompress_multicast_ctx_daddr(skb, ci,
							    &hdr.daddr,
							    iphc1 & LOWPAN_IPHC_DAM_MASK);
		spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
		अवरोध;
	हाल LOWPAN_IPHC_M:
		skb->pkt_type = PACKET_BROADCAST;

		/* multicast */
		err = lowpan_uncompress_multicast_daddr(skb, &hdr.daddr,
							iphc1 & LOWPAN_IPHC_DAM_MASK);
		अवरोध;
	हाल LOWPAN_IPHC_DAC:
		skb->pkt_type = PACKET_HOST;

		spin_lock_bh(&lowpan_dev(dev)->ctx.lock);
		ci = lowpan_iphc_ctx_get_by_id(dev, LOWPAN_IPHC_CID_DCI(cid));
		अगर (!ci) अणु
			spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
			वापस -EINVAL;
		पूर्ण

		/* Destination address context based uncompression */
		pr_debug("DAC bit is set. Handle context based destination address.\n");
		err = lowpan_iphc_uncompress_ctx_addr(skb, dev, ci, &hdr.daddr,
						      iphc1 & LOWPAN_IPHC_DAM_MASK,
						      daddr);
		spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);
		अवरोध;
	शेष:
		skb->pkt_type = PACKET_HOST;

		err = lowpan_iphc_uncompress_addr(skb, dev, &hdr.daddr,
						  iphc1 & LOWPAN_IPHC_DAM_MASK,
						  daddr);
		pr_debug("dest: stateless compression mode %d dest %pI6c\n",
			 iphc1 & LOWPAN_IPHC_DAM_MASK, &hdr.daddr);
		अवरोध;
	पूर्ण

	अगर (err)
		वापस -EINVAL;

	/* Next header data uncompression */
	अगर (iphc0 & LOWPAN_IPHC_NH) अणु
		err = lowpan_nhc_करो_uncompression(skb, dev, &hdr);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = skb_cow(skb, माप(hdr));
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	चयन (lowpan_dev(dev)->lltype) अणु
	हाल LOWPAN_LLTYPE_IEEE802154:
		अगर (lowpan_802154_cb(skb)->d_size)
			hdr.payload_len = htons(lowpan_802154_cb(skb)->d_size -
						माप(काष्ठा ipv6hdr));
		अन्यथा
			hdr.payload_len = htons(skb->len);
		अवरोध;
	शेष:
		hdr.payload_len = htons(skb->len);
		अवरोध;
	पूर्ण

	pr_debug("skb headroom size = %d, data length = %d\n",
		 skb_headroom(skb), skb->len);

	pr_debug("IPv6 header dump:\n\tversion = %d\n\tlength  = %d\n\t"
		 "nexthdr = 0x%02x\n\thop_lim = %d\n\tdest    = %pI6c\n",
		hdr.version, ntohs(hdr.payload_len), hdr.nexthdr,
		hdr.hop_limit, &hdr.daddr);

	skb_push(skb, माप(hdr));
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_copy_to_linear_data(skb, &hdr, माप(hdr));

	raw_dump_table(__func__, "raw header dump", (u8 *)&hdr, माप(hdr));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lowpan_header_decompress);

अटल स्थिर u8 lowpan_iphc_dam_to_sam_value[] = अणु
	[LOWPAN_IPHC_DAM_00] = LOWPAN_IPHC_SAM_00,
	[LOWPAN_IPHC_DAM_01] = LOWPAN_IPHC_SAM_01,
	[LOWPAN_IPHC_DAM_10] = LOWPAN_IPHC_SAM_10,
	[LOWPAN_IPHC_DAM_11] = LOWPAN_IPHC_SAM_11,
पूर्ण;

अटल अंतरभूत bool
lowpan_iphc_compress_ctx_802154_lladdr(स्थिर काष्ठा in6_addr *ipaddr,
				       स्थिर काष्ठा lowpan_iphc_ctx *ctx,
				       स्थिर व्योम *lladdr)
अणु
	स्थिर काष्ठा ieee802154_addr *addr = lladdr;
	अचिन्हित अक्षर extended_addr[EUI64_ADDR_LEN];
	bool lladdr_compress = false;
	काष्ठा in6_addr पंचांगp = अणुपूर्ण;

	चयन (addr->mode) अणु
	हाल IEEE802154_ADDR_LONG:
		ieee802154_le64_to_be64(&extended_addr, &addr->extended_addr);
		/* check क्रम SAM/DAM = 11 */
		स_नकल(&पंचांगp.s6_addr[8], &extended_addr, EUI64_ADDR_LEN);
		/* second bit-flip (Universe/Local) is करोne according RFC2464 */
		पंचांगp.s6_addr[8] ^= 0x02;
		/* context inक्रमmation are always used */
		ipv6_addr_prefix_copy(&पंचांगp, &ctx->pfx, ctx->plen);
		अगर (ipv6_addr_equal(&पंचांगp, ipaddr))
			lladdr_compress = true;
		अवरोध;
	हाल IEEE802154_ADDR_SHORT:
		पंचांगp.s6_addr[11] = 0xFF;
		पंचांगp.s6_addr[12] = 0xFE;
		ieee802154_le16_to_be16(&पंचांगp.s6_addr16[7],
					&addr->लघु_addr);
		/* context inक्रमmation are always used */
		ipv6_addr_prefix_copy(&पंचांगp, &ctx->pfx, ctx->plen);
		अगर (ipv6_addr_equal(&पंचांगp, ipaddr))
			lladdr_compress = true;
		अवरोध;
	शेष:
		/* should never handled and filtered by 802154 6lowpan */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस lladdr_compress;
पूर्ण

अटल bool lowpan_iphc_addr_equal(स्थिर काष्ठा net_device *dev,
				   स्थिर काष्ठा lowpan_iphc_ctx *ctx,
				   स्थिर काष्ठा in6_addr *ipaddr,
				   स्थिर व्योम *lladdr)
अणु
	काष्ठा in6_addr पंचांगp = अणुपूर्ण;

	lowpan_iphc_uncompress_lladdr(dev, &पंचांगp, lladdr);

	अगर (ctx)
		ipv6_addr_prefix_copy(&पंचांगp, &ctx->pfx, ctx->plen);

	वापस ipv6_addr_equal(&पंचांगp, ipaddr);
पूर्ण

अटल u8 lowpan_compress_ctx_addr(u8 **hc_ptr, स्थिर काष्ठा net_device *dev,
				   स्थिर काष्ठा in6_addr *ipaddr,
				   स्थिर काष्ठा lowpan_iphc_ctx *ctx,
				   स्थिर अचिन्हित अक्षर *lladdr, bool sam)
अणु
	काष्ठा in6_addr पंचांगp = अणुपूर्ण;
	u8 dam;

	चयन (lowpan_dev(dev)->lltype) अणु
	हाल LOWPAN_LLTYPE_IEEE802154:
		अगर (lowpan_iphc_compress_ctx_802154_lladdr(ipaddr, ctx,
							   lladdr)) अणु
			dam = LOWPAN_IPHC_DAM_11;
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		अगर (lowpan_iphc_addr_equal(dev, ctx, ipaddr, lladdr)) अणु
			dam = LOWPAN_IPHC_DAM_11;
			जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	/* check क्रम SAM/DAM = 10 */
	पंचांगp.s6_addr[11] = 0xFF;
	पंचांगp.s6_addr[12] = 0xFE;
	स_नकल(&पंचांगp.s6_addr[14], &ipaddr->s6_addr[14], 2);
	/* context inक्रमmation are always used */
	ipv6_addr_prefix_copy(&पंचांगp, &ctx->pfx, ctx->plen);
	अगर (ipv6_addr_equal(&पंचांगp, ipaddr)) अणु
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[14], 2);
		dam = LOWPAN_IPHC_DAM_10;
		जाओ out;
	पूर्ण

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	/* check क्रम SAM/DAM = 01, should always match */
	स_नकल(&पंचांगp.s6_addr[8], &ipaddr->s6_addr[8], 8);
	/* context inक्रमmation are always used */
	ipv6_addr_prefix_copy(&पंचांगp, &ctx->pfx, ctx->plen);
	अगर (ipv6_addr_equal(&पंचांगp, ipaddr)) अणु
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[8], 8);
		dam = LOWPAN_IPHC_DAM_01;
		जाओ out;
	पूर्ण

	WARN_ONCE(1, "context found but no address mode matched\n");
	वापस LOWPAN_IPHC_DAM_00;
out:

	अगर (sam)
		वापस lowpan_iphc_dam_to_sam_value[dam];
	अन्यथा
		वापस dam;
पूर्ण

अटल अंतरभूत bool
lowpan_iphc_compress_802154_lladdr(स्थिर काष्ठा in6_addr *ipaddr,
				   स्थिर व्योम *lladdr)
अणु
	स्थिर काष्ठा ieee802154_addr *addr = lladdr;
	अचिन्हित अक्षर extended_addr[EUI64_ADDR_LEN];
	bool lladdr_compress = false;
	काष्ठा in6_addr पंचांगp = अणुपूर्ण;

	चयन (addr->mode) अणु
	हाल IEEE802154_ADDR_LONG:
		ieee802154_le64_to_be64(&extended_addr, &addr->extended_addr);
		अगर (is_addr_mac_addr_based(ipaddr, extended_addr))
			lladdr_compress = true;
		अवरोध;
	हाल IEEE802154_ADDR_SHORT:
		/* fe:80::ff:fe00:XXXX
		 *                \__/
		 *             लघु_addr
		 *
		 * Universe/Local bit is zero.
		 */
		पंचांगp.s6_addr[0] = 0xFE;
		पंचांगp.s6_addr[1] = 0x80;
		पंचांगp.s6_addr[11] = 0xFF;
		पंचांगp.s6_addr[12] = 0xFE;
		ieee802154_le16_to_be16(&पंचांगp.s6_addr16[7],
					&addr->लघु_addr);
		अगर (ipv6_addr_equal(&पंचांगp, ipaddr))
			lladdr_compress = true;
		अवरोध;
	शेष:
		/* should never handled and filtered by 802154 6lowpan */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस lladdr_compress;
पूर्ण

अटल u8 lowpan_compress_addr_64(u8 **hc_ptr, स्थिर काष्ठा net_device *dev,
				  स्थिर काष्ठा in6_addr *ipaddr,
				  स्थिर अचिन्हित अक्षर *lladdr, bool sam)
अणु
	u8 dam = LOWPAN_IPHC_DAM_01;

	चयन (lowpan_dev(dev)->lltype) अणु
	हाल LOWPAN_LLTYPE_IEEE802154:
		अगर (lowpan_iphc_compress_802154_lladdr(ipaddr, lladdr)) अणु
			dam = LOWPAN_IPHC_DAM_11; /* 0-bits */
			pr_debug("address compression 0 bits\n");
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		अगर (lowpan_iphc_addr_equal(dev, शून्य, ipaddr, lladdr)) अणु
			dam = LOWPAN_IPHC_DAM_11;
			pr_debug("address compression 0 bits\n");
			जाओ out;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (lowpan_is_iid_16_bit_compressable(ipaddr)) अणु
		/* compress IID to 16 bits xxxx::XXXX */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr16[7], 2);
		dam = LOWPAN_IPHC_DAM_10; /* 16-bits */
		raw_dump_अंतरभूत(शून्य, "Compressed ipv6 addr is (16 bits)",
				*hc_ptr - 2, 2);
		जाओ out;
	पूर्ण

	/* करो not compress IID => xxxx::IID */
	lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr16[4], 8);
	raw_dump_अंतरभूत(शून्य, "Compressed ipv6 addr is (64 bits)",
			*hc_ptr - 8, 8);

out:

	अगर (sam)
		वापस lowpan_iphc_dam_to_sam_value[dam];
	अन्यथा
		वापस dam;
पूर्ण

/* lowpan_iphc_get_tc - get the ECN + DCSP fields in hc क्रमmat */
अटल अंतरभूत u8 lowpan_iphc_get_tc(स्थिर काष्ठा ipv6hdr *hdr)
अणु
	u8 dscp, ecn;

	/* hdr->priority contains the higher bits of dscp, lower are part of
	 * flow_lbl[0]. Note ECN, DCSP is swapped in ipv6 hdr.
	 */
	dscp = (hdr->priority << 2) | ((hdr->flow_lbl[0] & 0xc0) >> 6);
	/* ECN is at the two lower bits from first nibble of flow_lbl[0] */
	ecn = (hdr->flow_lbl[0] & 0x30);
	/* क्रम pretty debug output, also shअगरt ecn to get the ecn value */
	pr_debug("ecn 0x%02x dscp 0x%02x\n", ecn >> 4, dscp);
	/* ECN is at 0x30 now, shअगरt it to have ECN + DCSP */
	वापस (ecn << 2) | dscp;
पूर्ण

/* lowpan_iphc_is_flow_lbl_zero - check अगर flow label is zero */
अटल अंतरभूत bool lowpan_iphc_is_flow_lbl_zero(स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस ((!(hdr->flow_lbl[0] & 0x0f)) &&
		!hdr->flow_lbl[1] && !hdr->flow_lbl[2]);
पूर्ण

/* lowpan_iphc_tf_compress - compress the traffic class which is set by
 *	ipv6hdr. Return the corresponding क्रमmat identअगरier which is used.
 */
अटल u8 lowpan_iphc_tf_compress(u8 **hc_ptr, स्थिर काष्ठा ipv6hdr *hdr)
अणु
	/* get ecn dscp data in a byteक्रमmat as: ECN(hi) + DSCP(lo) */
	u8 tc = lowpan_iphc_get_tc(hdr), tf[4], val;

	/* prपूर्णांकout the traffic class in hc क्रमmat */
	pr_debug("tc 0x%02x\n", tc);

	अगर (lowpan_iphc_is_flow_lbl_zero(hdr)) अणु
		अगर (!tc) अणु
			/* 11:  Traffic Class and Flow Label are elided. */
			val = LOWPAN_IPHC_TF_11;
		पूर्ण अन्यथा अणु
			/* 10:  ECN + DSCP (1 byte), Flow Label is elided.
			 *
			 *  0 1 2 3 4 5 6 7
			 * +-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |
			 * +-+-+-+-+-+-+-+-+
			 */
			lowpan_push_hc_data(hc_ptr, &tc, माप(tc));
			val = LOWPAN_IPHC_TF_10;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check अगर dscp is zero, it's after the first two bit */
		अगर (!(tc & 0x3f)) अणु
			/* 01:  ECN + 2-bit Pad + Flow Label (3 bytes), DSCP is elided
			 *
			 *                     1                   2
			 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|rsv|             Flow Label                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			स_नकल(&tf[0], &hdr->flow_lbl[0], 3);
			/* zero the highest 4-bits, contains DCSP + ECN */
			tf[0] &= ~0xf0;
			/* set ECN */
			tf[0] |= (tc & 0xc0);

			lowpan_push_hc_data(hc_ptr, tf, 3);
			val = LOWPAN_IPHC_TF_01;
		पूर्ण अन्यथा अणु
			/* 00:  ECN + DSCP + 4-bit Pad + Flow Label (4 bytes)
			 *
			 *                      1                   2                   3
			 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |  rsv  |             Flow Label                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			स_नकल(&tf[0], &tc, माप(tc));
			/* highest nibble of flow_lbl[0] is part of DSCP + ECN
			 * which will be the 4-bit pad and will be filled with
			 * zeros afterwards.
			 */
			स_नकल(&tf[1], &hdr->flow_lbl[0], 3);
			/* zero the 4-bit pad, which is reserved */
			tf[1] &= ~0xf0;

			lowpan_push_hc_data(hc_ptr, tf, 4);
			val = LOWPAN_IPHC_TF_00;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल u8 lowpan_iphc_mcast_ctx_addr_compress(u8 **hc_ptr,
					      स्थिर काष्ठा lowpan_iphc_ctx *ctx,
					      स्थिर काष्ठा in6_addr *ipaddr)
अणु
	u8 data[6];

	/* flags/scope, reserved (RIID) */
	स_नकल(data, &ipaddr->s6_addr[1], 2);
	/* group ID */
	स_नकल(&data[1], &ipaddr->s6_addr[11], 4);
	lowpan_push_hc_data(hc_ptr, data, 6);

	वापस LOWPAN_IPHC_DAM_00;
पूर्ण

अटल u8 lowpan_iphc_mcast_addr_compress(u8 **hc_ptr,
					  स्थिर काष्ठा in6_addr *ipaddr)
अणु
	u8 val;

	अगर (lowpan_is_mcast_addr_compressable8(ipaddr)) अणु
		pr_debug("compressed to 1 octet\n");
		/* use last byte */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[15], 1);
		val = LOWPAN_IPHC_DAM_11;
	पूर्ण अन्यथा अगर (lowpan_is_mcast_addr_compressable32(ipaddr)) अणु
		pr_debug("compressed to 4 octets\n");
		/* second byte + the last three */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[1], 1);
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[13], 3);
		val = LOWPAN_IPHC_DAM_10;
	पूर्ण अन्यथा अगर (lowpan_is_mcast_addr_compressable48(ipaddr)) अणु
		pr_debug("compressed to 6 octets\n");
		/* second byte + the last five */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[1], 1);
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[11], 5);
		val = LOWPAN_IPHC_DAM_01;
	पूर्ण अन्यथा अणु
		pr_debug("using full address\n");
		lowpan_push_hc_data(hc_ptr, ipaddr->s6_addr, 16);
		val = LOWPAN_IPHC_DAM_00;
	पूर्ण

	वापस val;
पूर्ण

पूर्णांक lowpan_header_compress(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			   स्थिर व्योम *daddr, स्थिर व्योम *saddr)
अणु
	u8 iphc0, iphc1, *hc_ptr, cid = 0;
	काष्ठा ipv6hdr *hdr;
	u8 head[LOWPAN_IPHC_MAX_HC_BUF_LEN] = अणुपूर्ण;
	काष्ठा lowpan_iphc_ctx *dci, *sci, dci_entry, sci_entry;
	पूर्णांक ret, ipv6_daddr_type, ipv6_saddr_type;

	अगर (skb->protocol != htons(ETH_P_IPV6))
		वापस -EINVAL;

	hdr = ipv6_hdr(skb);
	hc_ptr = head + 2;

	pr_debug("IPv6 header dump:\n\tversion = %d\n\tlength  = %d\n"
		 "\tnexthdr = 0x%02x\n\thop_lim = %d\n\tdest    = %pI6c\n",
		 hdr->version, ntohs(hdr->payload_len), hdr->nexthdr,
		 hdr->hop_limit, &hdr->daddr);

	raw_dump_table(__func__, "raw skb network header dump",
		       skb_network_header(skb), माप(काष्ठा ipv6hdr));

	/* As we copy some bit-length fields, in the IPHC encoding bytes,
	 * we someबार use |=
	 * If the field is 0, and the current bit value in memory is 1,
	 * this करोes not work. We thereक्रमe reset the IPHC encoding here
	 */
	iphc0 = LOWPAN_DISPATCH_IPHC;
	iphc1 = 0;

	raw_dump_table(__func__, "sending raw skb network uncompressed packet",
		       skb->data, skb->len);

	ipv6_daddr_type = ipv6_addr_type(&hdr->daddr);
	spin_lock_bh(&lowpan_dev(dev)->ctx.lock);
	अगर (ipv6_daddr_type & IPV6_ADDR_MULTICAST)
		dci = lowpan_iphc_ctx_get_by_mcast_addr(dev, &hdr->daddr);
	अन्यथा
		dci = lowpan_iphc_ctx_get_by_addr(dev, &hdr->daddr);
	अगर (dci) अणु
		स_नकल(&dci_entry, dci, माप(*dci));
		cid |= dci->id;
	पूर्ण
	spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);

	spin_lock_bh(&lowpan_dev(dev)->ctx.lock);
	sci = lowpan_iphc_ctx_get_by_addr(dev, &hdr->saddr);
	अगर (sci) अणु
		स_नकल(&sci_entry, sci, माप(*sci));
		cid |= (sci->id << 4);
	पूर्ण
	spin_unlock_bh(&lowpan_dev(dev)->ctx.lock);

	/* अगर cid is zero it will be compressed */
	अगर (cid) अणु
		iphc1 |= LOWPAN_IPHC_CID;
		lowpan_push_hc_data(&hc_ptr, &cid, माप(cid));
	पूर्ण

	/* Traffic Class, Flow Label compression */
	iphc0 |= lowpan_iphc_tf_compress(&hc_ptr, hdr);

	/* NOTE: payload length is always compressed */

	/* Check अगर we provide the nhc क्रमmat क्रम nexthdr and compression
	 * functionality. If not nexthdr is handled अंतरभूत and not compressed.
	 */
	ret = lowpan_nhc_check_compression(skb, hdr, &hc_ptr);
	अगर (ret == -ENOENT)
		lowpan_push_hc_data(&hc_ptr, &hdr->nexthdr,
				    माप(hdr->nexthdr));
	अन्यथा
		iphc0 |= LOWPAN_IPHC_NH;

	/* Hop limit
	 * अगर 1:   compress, encoding is 01
	 * अगर 64:  compress, encoding is 10
	 * अगर 255: compress, encoding is 11
	 * अन्यथा करो not compress
	 */
	चयन (hdr->hop_limit) अणु
	हाल 1:
		iphc0 |= LOWPAN_IPHC_HLIM_01;
		अवरोध;
	हाल 64:
		iphc0 |= LOWPAN_IPHC_HLIM_10;
		अवरोध;
	हाल 255:
		iphc0 |= LOWPAN_IPHC_HLIM_11;
		अवरोध;
	शेष:
		lowpan_push_hc_data(&hc_ptr, &hdr->hop_limit,
				    माप(hdr->hop_limit));
	पूर्ण

	ipv6_saddr_type = ipv6_addr_type(&hdr->saddr);
	/* source address compression */
	अगर (ipv6_saddr_type == IPV6_ADDR_ANY) अणु
		pr_debug("source address is unspecified, setting SAC\n");
		iphc1 |= LOWPAN_IPHC_SAC;
	पूर्ण अन्यथा अणु
		अगर (sci) अणु
			iphc1 |= lowpan_compress_ctx_addr(&hc_ptr, dev,
							  &hdr->saddr,
							  &sci_entry, saddr,
							  true);
			iphc1 |= LOWPAN_IPHC_SAC;
		पूर्ण अन्यथा अणु
			अगर (ipv6_saddr_type & IPV6_ADDR_LINKLOCAL &&
			    lowpan_is_linklocal_zero_padded(hdr->saddr)) अणु
				iphc1 |= lowpan_compress_addr_64(&hc_ptr, dev,
								 &hdr->saddr,
								 saddr, true);
				pr_debug("source address unicast link-local %pI6c iphc1 0x%02x\n",
					 &hdr->saddr, iphc1);
			पूर्ण अन्यथा अणु
				pr_debug("send the full source address\n");
				lowpan_push_hc_data(&hc_ptr,
						    hdr->saddr.s6_addr, 16);
			पूर्ण
		पूर्ण
	पूर्ण

	/* destination address compression */
	अगर (ipv6_daddr_type & IPV6_ADDR_MULTICAST) अणु
		pr_debug("destination address is multicast: ");
		iphc1 |= LOWPAN_IPHC_M;
		अगर (dci) अणु
			iphc1 |= lowpan_iphc_mcast_ctx_addr_compress(&hc_ptr,
								     &dci_entry,
								     &hdr->daddr);
			iphc1 |= LOWPAN_IPHC_DAC;
		पूर्ण अन्यथा अणु
			iphc1 |= lowpan_iphc_mcast_addr_compress(&hc_ptr,
								 &hdr->daddr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dci) अणु
			iphc1 |= lowpan_compress_ctx_addr(&hc_ptr, dev,
							  &hdr->daddr,
							  &dci_entry, daddr,
							  false);
			iphc1 |= LOWPAN_IPHC_DAC;
		पूर्ण अन्यथा अणु
			अगर (ipv6_daddr_type & IPV6_ADDR_LINKLOCAL &&
			    lowpan_is_linklocal_zero_padded(hdr->daddr)) अणु
				iphc1 |= lowpan_compress_addr_64(&hc_ptr, dev,
								 &hdr->daddr,
								 daddr, false);
				pr_debug("dest address unicast link-local %pI6c iphc1 0x%02x\n",
					 &hdr->daddr, iphc1);
			पूर्ण अन्यथा अणु
				pr_debug("dest address unicast %pI6c\n",
					 &hdr->daddr);
				lowpan_push_hc_data(&hc_ptr,
						    hdr->daddr.s6_addr, 16);
			पूर्ण
		पूर्ण
	पूर्ण

	/* next header compression */
	अगर (iphc0 & LOWPAN_IPHC_NH) अणु
		ret = lowpan_nhc_करो_compression(skb, hdr, &hc_ptr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	head[0] = iphc0;
	head[1] = iphc1;

	skb_pull(skb, माप(काष्ठा ipv6hdr));
	skb_reset_transport_header(skb);
	स_नकल(skb_push(skb, hc_ptr - head), head, hc_ptr - head);
	skb_reset_network_header(skb);

	pr_debug("header len %d skb %u\n", (पूर्णांक)(hc_ptr - head), skb->len);

	raw_dump_table(__func__, "raw skb data dump compressed",
		       skb->data, skb->len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lowpan_header_compress);
