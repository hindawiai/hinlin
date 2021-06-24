<शैली गुरु>
/*
 * Copyright 2011, Siemens AG
 * written by Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

/*
 * Based on patches from Jon Smirl <jonsmirl@gmail.com>
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
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA.
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

#अगर_अघोषित __6LOWPAN_H__
#घोषणा __6LOWPAN_H__

#समावेश <linux/debugfs.h>

#समावेश <net/ipv6.h>
#समावेश <net/net_namespace.h>

/* special link-layer handling */
#समावेश <net/mac802154.h>

#घोषणा EUI64_ADDR_LEN		8

#घोषणा LOWPAN_NHC_MAX_ID_LEN	1
/* Maximum next header compression length which we currently support inclusive
 * possible अंतरभूत data.
 */
#घोषणा LOWPAN_NHC_MAX_HDR_LEN	(माप(काष्ठा udphdr))
/* Max IPHC Header len without IPv6 hdr specअगरic अंतरभूत data.
 * Useful क्रम getting the "extra" bytes we need at worst हाल compression.
 *
 * LOWPAN_IPHC + CID + LOWPAN_NHC_MAX_ID_LEN
 */
#घोषणा LOWPAN_IPHC_MAX_HEADER_LEN	(2 + 1 + LOWPAN_NHC_MAX_ID_LEN)
/* Maximum worst हाल IPHC header buffer size */
#घोषणा LOWPAN_IPHC_MAX_HC_BUF_LEN	(माप(काष्ठा ipv6hdr) +	\
					 LOWPAN_IPHC_MAX_HEADER_LEN +	\
					 LOWPAN_NHC_MAX_HDR_LEN)
/* SCI/DCI is 4 bit width, so we have maximum 16 entries */
#घोषणा LOWPAN_IPHC_CTX_TABLE_SIZE	(1 << 4)

#घोषणा LOWPAN_DISPATCH_IPV6		0x41 /* 01000001 = 65 */
#घोषणा LOWPAN_DISPATCH_IPHC		0x60 /* 011xxxxx = ... */
#घोषणा LOWPAN_DISPATCH_IPHC_MASK	0xe0

अटल अंतरभूत bool lowpan_is_ipv6(u8 dispatch)
अणु
	वापस dispatch == LOWPAN_DISPATCH_IPV6;
पूर्ण

अटल अंतरभूत bool lowpan_is_iphc(u8 dispatch)
अणु
	वापस (dispatch & LOWPAN_DISPATCH_IPHC_MASK) == LOWPAN_DISPATCH_IPHC;
पूर्ण

#घोषणा LOWPAN_PRIV_SIZE(llpriv_size)	\
	(माप(काष्ठा lowpan_dev) + llpriv_size)

क्रमागत lowpan_lltypes अणु
	LOWPAN_LLTYPE_BTLE,
	LOWPAN_LLTYPE_IEEE802154,
पूर्ण;

क्रमागत lowpan_iphc_ctx_flags अणु
	LOWPAN_IPHC_CTX_FLAG_ACTIVE,
	LOWPAN_IPHC_CTX_FLAG_COMPRESSION,
पूर्ण;

काष्ठा lowpan_iphc_ctx अणु
	u8 id;
	काष्ठा in6_addr pfx;
	u8 plen;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा lowpan_iphc_ctx_table अणु
	spinlock_t lock;
	स्थिर काष्ठा lowpan_iphc_ctx_ops *ops;
	काष्ठा lowpan_iphc_ctx table[LOWPAN_IPHC_CTX_TABLE_SIZE];
पूर्ण;

अटल अंतरभूत bool lowpan_iphc_ctx_is_active(स्थिर काष्ठा lowpan_iphc_ctx *ctx)
अणु
	वापस test_bit(LOWPAN_IPHC_CTX_FLAG_ACTIVE, &ctx->flags);
पूर्ण

अटल अंतरभूत bool
lowpan_iphc_ctx_is_compression(स्थिर काष्ठा lowpan_iphc_ctx *ctx)
अणु
	वापस test_bit(LOWPAN_IPHC_CTX_FLAG_COMPRESSION, &ctx->flags);
पूर्ण

काष्ठा lowpan_dev अणु
	क्रमागत lowpan_lltypes lltype;
	काष्ठा dentry *अगरace_debugfs;
	काष्ठा lowpan_iphc_ctx_table ctx;

	/* must be last */
	u8 priv[] __aligned(माप(व्योम *));
पूर्ण;

काष्ठा lowpan_802154_neigh अणु
	__le16 लघु_addr;
पूर्ण;

अटल अंतरभूत
काष्ठा lowpan_802154_neigh *lowpan_802154_neigh(व्योम *neigh_priv)
अणु
	वापस neigh_priv;
पूर्ण

अटल अंतरभूत
काष्ठा lowpan_dev *lowpan_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

/* निजी device info */
काष्ठा lowpan_802154_dev अणु
	काष्ठा net_device	*wdev; /* wpan device ptr */
	u16			fragment_tag;
पूर्ण;

अटल अंतरभूत काष्ठा
lowpan_802154_dev *lowpan_802154_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस (काष्ठा lowpan_802154_dev *)lowpan_dev(dev)->priv;
पूर्ण

काष्ठा lowpan_802154_cb अणु
	u16 d_tag;
	अचिन्हित पूर्णांक d_size;
	u8 d_offset;
पूर्ण;

अटल अंतरभूत
काष्ठा lowpan_802154_cb *lowpan_802154_cb(स्थिर काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा lowpan_802154_cb) > माप(skb->cb));
	वापस (काष्ठा lowpan_802154_cb *)skb->cb;
पूर्ण

अटल अंतरभूत व्योम lowpan_iphc_uncompress_eui64_lladdr(काष्ठा in6_addr *ipaddr,
						       स्थिर व्योम *lladdr)
अणु
	/* fe:80::XXXX:XXXX:XXXX:XXXX
	 *        \_________________/
	 *              hwaddr
	 */
	ipaddr->s6_addr[0] = 0xFE;
	ipaddr->s6_addr[1] = 0x80;
	स_नकल(&ipaddr->s6_addr[8], lladdr, EUI64_ADDR_LEN);
	/* second bit-flip (Universe/Local)
	 * is करोne according RFC2464
	 */
	ipaddr->s6_addr[8] ^= 0x02;
पूर्ण

अटल अंतरभूत व्योम lowpan_iphc_uncompress_eui48_lladdr(काष्ठा in6_addr *ipaddr,
						       स्थिर व्योम *lladdr)
अणु
	/* fe:80::XXXX:XXff:feXX:XXXX
	 *        \_________________/
	 *              hwaddr
	 */
	ipaddr->s6_addr[0] = 0xFE;
	ipaddr->s6_addr[1] = 0x80;
	स_नकल(&ipaddr->s6_addr[8], lladdr, 3);
	ipaddr->s6_addr[11] = 0xFF;
	ipaddr->s6_addr[12] = 0xFE;
	स_नकल(&ipaddr->s6_addr[13], lladdr + 3, 3);
पूर्ण

#अगर_घोषित DEBUG
/* prपूर्णांक data in line */
अटल अंतरभूत व्योम raw_dump_अंतरभूत(स्थिर अक्षर *caller, अक्षर *msg,
				   स्थिर अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	अगर (msg)
		pr_debug("%s():%s: ", caller, msg);

	prपूर्णांक_hex_dump_debug("", DUMP_PREFIX_NONE, 16, 1, buf, len, false);
पूर्ण

/* prपूर्णांक data in a table क्रमmat:
 *
 * addr: xx xx xx xx xx xx
 * addr: xx xx xx xx xx xx
 * ...
 */
अटल अंतरभूत व्योम raw_dump_table(स्थिर अक्षर *caller, अक्षर *msg,
				  स्थिर अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	अगर (msg)
		pr_debug("%s():%s:\n", caller, msg);

	prपूर्णांक_hex_dump_debug("\t", DUMP_PREFIX_OFFSET, 16, 1, buf, len, false);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम raw_dump_table(स्थिर अक्षर *caller, अक्षर *msg,
				  स्थिर अचिन्हित अक्षर *buf, पूर्णांक len) अणु पूर्ण
अटल अंतरभूत व्योम raw_dump_अंतरभूत(स्थिर अक्षर *caller, अक्षर *msg,
				   स्थिर अचिन्हित अक्षर *buf, पूर्णांक len) अणु पूर्ण
#पूर्ण_अगर

/**
 * lowpan_fetch_skb - getting अंतरभूत data from 6LoWPAN header
 *
 * This function will pull data from sk buffer and put it पूर्णांकo data to
 * हटाओ the 6LoWPAN अंतरभूत data. This function वापसs true अगर the
 * sk buffer is too small to pull the amount of data which is specअगरied
 * by len.
 *
 * @skb: the buffer where the अंतरभूत data should be pulled from.
 * @data: destination buffer क्रम the अंतरभूत data.
 * @len: amount of data which should be pulled in bytes.
 */
अटल अंतरभूत bool lowpan_fetch_skb(काष्ठा sk_buff *skb, व्योम *data,
				    अचिन्हित पूर्णांक len)
अणु
	अगर (unlikely(!pskb_may_pull(skb, len)))
		वापस true;

	skb_copy_from_linear_data(skb, data, len);
	skb_pull(skb, len);

	वापस false;
पूर्ण

अटल अंतरभूत bool lowpan_802154_is_valid_src_लघु_addr(__le16 addr)
अणु
	/* First bit of addr is multicast, reserved or 802.15.4 specअगरic */
	वापस !(addr & cpu_to_le16(0x8000));
पूर्ण

अटल अंतरभूत व्योम lowpan_push_hc_data(u8 **hc_ptr, स्थिर व्योम *data,
				       स्थिर माप_प्रकार len)
अणु
	स_नकल(*hc_ptr, data, len);
	*hc_ptr += len;
पूर्ण

पूर्णांक lowpan_रेजिस्टर_netdevice(काष्ठा net_device *dev,
			      क्रमागत lowpan_lltypes lltype);
पूर्णांक lowpan_रेजिस्टर_netdev(काष्ठा net_device *dev,
			   क्रमागत lowpan_lltypes lltype);
व्योम lowpan_unरेजिस्टर_netdevice(काष्ठा net_device *dev);
व्योम lowpan_unरेजिस्टर_netdev(काष्ठा net_device *dev);

/**
 * lowpan_header_decompress - replace 6LoWPAN header with IPv6 header
 *
 * This function replaces the IPHC 6LoWPAN header which should be poपूर्णांकed at
 * skb->data and skb_network_header, with the IPv6 header.
 * It would be nice that the caller have the necessary headroom of IPv6 header
 * and greatest Transport layer header, this would reduce the overhead क्रम
 * पुनः_स्मृतिate headroom.
 *
 * @skb: the buffer which should be manipulate.
 * @dev: the lowpan net device poपूर्णांकer.
 * @daddr: destination lladdr of mac header which is used क्रम compression
 *	methods.
 * @saddr: source lladdr of mac header which is used क्रम compression
 *	methods.
 */
पूर्णांक lowpan_header_decompress(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			     स्थिर व्योम *daddr, स्थिर व्योम *saddr);

/**
 * lowpan_header_compress - replace IPv6 header with 6LoWPAN header
 *
 * This function replaces the IPv6 header which should be poपूर्णांकed at
 * skb->data and skb_network_header, with the IPHC 6LoWPAN header.
 * The caller need to be sure that the sk buffer is not shared and at have
 * at least a headroom which is smaller or equal LOWPAN_IPHC_MAX_HEADER_LEN,
 * which is the IPHC "more bytes than IPv6 header" at worst हाल.
 *
 * @skb: the buffer which should be manipulate.
 * @dev: the lowpan net device poपूर्णांकer.
 * @daddr: destination lladdr of mac header which is used क्रम compression
 *	methods.
 * @saddr: source lladdr of mac header which is used क्रम compression
 *	methods.
 */
पूर्णांक lowpan_header_compress(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			   स्थिर व्योम *daddr, स्थिर व्योम *saddr);

#पूर्ण_अगर /* __6LOWPAN_H__ */
