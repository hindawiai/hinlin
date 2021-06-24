<शैली गुरु>
/*
 * net/अगरe/अगरe.c - Inter-FE protocol based on ForCES WG InterFE LFB
 * Copyright (c) 2015 Jamal Hadi Salim <jhs@mojatatu.com>
 * Copyright (c) 2017 Yotam Gigi <yotamg@mellanox.com>
 *
 * Refer to: draft-ietf-क्रमces-पूर्णांकerfelfb-03 and netdev01 paper:
 * "Distributing Linux Traffic Control Classifier-Action Subsystem"
 * Authors: Jamal Hadi Salim and Damascene M. Joachimpillai
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/अगरe.h>

काष्ठा अगरeheadr अणु
	__be16 metalen;
	u8 tlv_data[];
पूर्ण;

व्योम *अगरe_encode(काष्ठा sk_buff *skb, u16 metalen)
अणु
	/* OUTERHDR:TOTMETALEN:अणुTLVHDR:Metadatum:TLVHDR..पूर्ण:ORIGDATA
	 * where ORIGDATA = original ethernet header ...
	 */
	पूर्णांक hdrm = metalen + IFE_METAHDRLEN;
	पूर्णांक total_push = hdrm + skb->dev->hard_header_len;
	काष्ठा अगरeheadr *अगरehdr;
	काष्ठा ethhdr *iethh;	/* inner ether header */
	पूर्णांक skboff = 0;
	पूर्णांक err;

	err = skb_cow_head(skb, total_push);
	अगर (unlikely(err))
		वापस शून्य;

	iethh = (काष्ठा ethhdr *) skb->data;

	__skb_push(skb, total_push);
	स_नकल(skb->data, iethh, skb->dev->hard_header_len);
	skb_reset_mac_header(skb);
	skboff += skb->dev->hard_header_len;

	/* total metadata length */
	अगरehdr = (काष्ठा अगरeheadr *) (skb->data + skboff);
	metalen += IFE_METAHDRLEN;
	अगरehdr->metalen = htons(metalen);

	वापस अगरehdr->tlv_data;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_encode);

व्योम *अगरe_decode(काष्ठा sk_buff *skb, u16 *metalen)
अणु
	काष्ठा अगरeheadr *अगरehdr;
	पूर्णांक total_pull;
	u16 अगरehdrln;

	अगर (!pskb_may_pull(skb, skb->dev->hard_header_len + IFE_METAHDRLEN))
		वापस शून्य;

	अगरehdr = (काष्ठा अगरeheadr *) (skb->data + skb->dev->hard_header_len);
	अगरehdrln = ntohs(अगरehdr->metalen);
	total_pull = skb->dev->hard_header_len + अगरehdrln;

	अगर (unlikely(अगरehdrln < 2))
		वापस शून्य;

	अगर (unlikely(!pskb_may_pull(skb, total_pull)))
		वापस शून्य;

	skb_set_mac_header(skb, total_pull);
	__skb_pull(skb, total_pull);
	*metalen = अगरehdrln - IFE_METAHDRLEN;

	वापस &अगरehdr->tlv_data;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_decode);

काष्ठा meta_tlvhdr अणु
	__be16 type;
	__be16 len;
पूर्ण;

अटल bool __अगरe_tlv_meta_valid(स्थिर अचिन्हित अक्षर *skbdata,
				 स्थिर अचिन्हित अक्षर *अगरehdr_end)
अणु
	स्थिर काष्ठा meta_tlvhdr *tlv;
	u16 tlvlen;

	अगर (unlikely(skbdata + माप(*tlv) > अगरehdr_end))
		वापस false;

	tlv = (स्थिर काष्ठा meta_tlvhdr *)skbdata;
	tlvlen = ntohs(tlv->len);

	/* tlv length field is inc header, check on minimum */
	अगर (tlvlen < NLA_HDRLEN)
		वापस false;

	/* overflow by NLA_ALIGN check */
	अगर (NLA_ALIGN(tlvlen) < tlvlen)
		वापस false;

	अगर (unlikely(skbdata + NLA_ALIGN(tlvlen) > अगरehdr_end))
		वापस false;

	वापस true;
पूर्ण

/* Caller takes care of presenting data in network order
 */
व्योम *अगरe_tlv_meta_decode(व्योम *skbdata, स्थिर व्योम *अगरehdr_end, u16 *attrtype,
			  u16 *dlen, u16 *totlen)
अणु
	काष्ठा meta_tlvhdr *tlv;

	अगर (!__अगरe_tlv_meta_valid(skbdata, अगरehdr_end))
		वापस शून्य;

	tlv = (काष्ठा meta_tlvhdr *)skbdata;
	*dlen = ntohs(tlv->len) - NLA_HDRLEN;
	*attrtype = ntohs(tlv->type);

	अगर (totlen)
		*totlen = nla_total_size(*dlen);

	वापस skbdata + माप(काष्ठा meta_tlvhdr);
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_tlv_meta_decode);

व्योम *अगरe_tlv_meta_next(व्योम *skbdata)
अणु
	काष्ठा meta_tlvhdr *tlv = (काष्ठा meta_tlvhdr *) skbdata;
	u16 tlvlen = ntohs(tlv->len);

	tlvlen = NLA_ALIGN(tlvlen);

	वापस skbdata + tlvlen;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_tlv_meta_next);

/* Caller takes care of presenting data in network order
 */
पूर्णांक अगरe_tlv_meta_encode(व्योम *skbdata, u16 attrtype, u16 dlen, स्थिर व्योम *dval)
अणु
	__be32 *tlv = (__be32 *) (skbdata);
	u16 totlen = nla_total_size(dlen);	/*alignment + hdr */
	अक्षर *dptr = (अक्षर *) tlv + NLA_HDRLEN;
	u32 htlv = attrtype << 16 | (dlen + NLA_HDRLEN);

	*tlv = htonl(htlv);
	स_रखो(dptr, 0, totlen - NLA_HDRLEN);
	स_नकल(dptr, dval, dlen);

	वापस totlen;
पूर्ण
EXPORT_SYMBOL_GPL(अगरe_tlv_meta_encode);

MODULE_AUTHOR("Jamal Hadi Salim <jhs@mojatatu.com>");
MODULE_AUTHOR("Yotam Gigi <yotam.gi@gmail.com>");
MODULE_DESCRIPTION("Inter-FE LFB action");
MODULE_LICENSE("GPL");
