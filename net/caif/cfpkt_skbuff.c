<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <net/caअगर/cfpkt.h>

#घोषणा PKT_PREFIX  48
#घोषणा PKT_POSTFIX 2
#घोषणा PKT_LEN_WHEN_EXTENDING 128
#घोषणा PKT_ERROR(pkt, errmsg)		   \
करो अणु					   \
	cfpkt_priv(pkt)->erronous = true;  \
	skb_reset_tail_poपूर्णांकer(&pkt->skb); \
	pr_warn(errmsg);		   \
पूर्ण जबतक (0)

काष्ठा cfpktq अणु
	काष्ठा sk_buff_head head;
	atomic_t count;
	/* Lock protects count updates */
	spinlock_t lock;
पूर्ण;

/*
 * net/caअगर/ is generic and करोes not
 * understand SKB, so we करो this typecast
 */
काष्ठा cfpkt अणु
	काष्ठा sk_buff skb;
पूर्ण;

/* Private data inside SKB */
काष्ठा cfpkt_priv_data अणु
	काष्ठा dev_info dev_info;
	bool erronous;
पूर्ण;

अटल अंतरभूत काष्ठा cfpkt_priv_data *cfpkt_priv(काष्ठा cfpkt *pkt)
अणु
	वापस (काष्ठा cfpkt_priv_data *) pkt->skb.cb;
पूर्ण

अटल अंतरभूत bool is_erronous(काष्ठा cfpkt *pkt)
अणु
	वापस cfpkt_priv(pkt)->erronous;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pkt_to_skb(काष्ठा cfpkt *pkt)
अणु
	वापस &pkt->skb;
पूर्ण

अटल अंतरभूत काष्ठा cfpkt *skb_to_pkt(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा cfpkt *) skb;
पूर्ण

काष्ठा cfpkt *cfpkt_fromnative(क्रमागत caअगर_direction dir, व्योम *nativepkt)
अणु
	काष्ठा cfpkt *pkt = skb_to_pkt(nativepkt);
	cfpkt_priv(pkt)->erronous = false;
	वापस pkt;
पूर्ण
EXPORT_SYMBOL(cfpkt_fromnative);

व्योम *cfpkt_tonative(काष्ठा cfpkt *pkt)
अणु
	वापस (व्योम *) pkt;
पूर्ण
EXPORT_SYMBOL(cfpkt_tonative);

अटल काष्ठा cfpkt *cfpkt_create_pfx(u16 len, u16 pfx)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len + pfx, GFP_ATOMIC);
	अगर (unlikely(skb == शून्य))
		वापस शून्य;

	skb_reserve(skb, pfx);
	वापस skb_to_pkt(skb);
पूर्ण

अंतरभूत काष्ठा cfpkt *cfpkt_create(u16 len)
अणु
	वापस cfpkt_create_pfx(len + PKT_POSTFIX, PKT_PREFIX);
पूर्ण

व्योम cfpkt_destroy(काष्ठा cfpkt *pkt)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	kमुक्त_skb(skb);
पूर्ण

अंतरभूत bool cfpkt_more(काष्ठा cfpkt *pkt)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	वापस skb->len > 0;
पूर्ण

पूर्णांक cfpkt_peek_head(काष्ठा cfpkt *pkt, व्योम *data, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	अगर (skb_headlen(skb) >= len) अणु
		स_नकल(data, skb->data, len);
		वापस 0;
	पूर्ण
	वापस !cfpkt_extr_head(pkt, data, len) &&
	    !cfpkt_add_head(pkt, data, len);
पूर्ण

पूर्णांक cfpkt_extr_head(काष्ठा cfpkt *pkt, व्योम *data, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	u8 *from;
	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;

	अगर (unlikely(len > skb->len)) अणु
		PKT_ERROR(pkt, "read beyond end of packet\n");
		वापस -EPROTO;
	पूर्ण

	अगर (unlikely(len > skb_headlen(skb))) अणु
		अगर (unlikely(skb_linearize(skb) != 0)) अणु
			PKT_ERROR(pkt, "linearize failed\n");
			वापस -EPROTO;
		पूर्ण
	पूर्ण
	from = skb_pull(skb, len);
	from -= len;
	अगर (data)
		स_नकल(data, from, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfpkt_extr_head);

पूर्णांक cfpkt_extr_trail(काष्ठा cfpkt *pkt, व्योम *dta, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	u8 *data = dta;
	u8 *from;
	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;

	अगर (unlikely(skb_linearize(skb) != 0)) अणु
		PKT_ERROR(pkt, "linearize failed\n");
		वापस -EPROTO;
	पूर्ण
	अगर (unlikely(skb->data + len > skb_tail_poपूर्णांकer(skb))) अणु
		PKT_ERROR(pkt, "read beyond end of packet\n");
		वापस -EPROTO;
	पूर्ण
	from = skb_tail_poपूर्णांकer(skb) - len;
	skb_trim(skb, skb->len - len);
	स_नकल(data, from, len);
	वापस 0;
पूर्ण

पूर्णांक cfpkt_pad_trail(काष्ठा cfpkt *pkt, u16 len)
अणु
	वापस cfpkt_add_body(pkt, शून्य, len);
पूर्ण

पूर्णांक cfpkt_add_body(काष्ठा cfpkt *pkt, स्थिर व्योम *data, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	काष्ठा sk_buff *lastskb;
	u8 *to;
	u16 addlen = 0;


	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;

	lastskb = skb;

	/* Check whether we need to add space at the tail */
	अगर (unlikely(skb_tailroom(skb) < len)) अणु
		अगर (likely(len < PKT_LEN_WHEN_EXTENDING))
			addlen = PKT_LEN_WHEN_EXTENDING;
		अन्यथा
			addlen = len;
	पूर्ण

	/* Check whether we need to change the SKB beक्रमe writing to the tail */
	अगर (unlikely((addlen > 0) || skb_cloned(skb) || skb_shared(skb))) अणु

		/* Make sure data is writable */
		अगर (unlikely(skb_cow_data(skb, addlen, &lastskb) < 0)) अणु
			PKT_ERROR(pkt, "cow failed\n");
			वापस -EPROTO;
		पूर्ण
	पूर्ण

	/* All set to put the last SKB and optionally ग_लिखो data there. */
	to = pskb_put(skb, lastskb, len);
	अगर (likely(data))
		स_नकल(to, data, len);
	वापस 0;
पूर्ण

अंतरभूत पूर्णांक cfpkt_addbdy(काष्ठा cfpkt *pkt, u8 data)
अणु
	वापस cfpkt_add_body(pkt, &data, 1);
पूर्ण

पूर्णांक cfpkt_add_head(काष्ठा cfpkt *pkt, स्थिर व्योम *data2, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	काष्ठा sk_buff *lastskb;
	u8 *to;
	स्थिर u8 *data = data2;
	पूर्णांक ret;
	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;
	अगर (unlikely(skb_headroom(skb) < len)) अणु
		PKT_ERROR(pkt, "no headroom\n");
		वापस -EPROTO;
	पूर्ण

	/* Make sure data is writable */
	ret = skb_cow_data(skb, 0, &lastskb);
	अगर (unlikely(ret < 0)) अणु
		PKT_ERROR(pkt, "cow failed\n");
		वापस ret;
	पूर्ण

	to = skb_push(skb, len);
	स_नकल(to, data, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfpkt_add_head);

अंतरभूत पूर्णांक cfpkt_add_trail(काष्ठा cfpkt *pkt, स्थिर व्योम *data, u16 len)
अणु
	वापस cfpkt_add_body(pkt, data, len);
पूर्ण

अंतरभूत u16 cfpkt_getlen(काष्ठा cfpkt *pkt)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	वापस skb->len;
पूर्ण

पूर्णांक cfpkt_iterate(काष्ठा cfpkt *pkt,
		  u16 (*iter_func)(u16, व्योम *, u16),
		  u16 data)
अणु
	/*
	 * Don't care about the perक्रमmance hit of linearizing,
	 * Checksum should not be used on high-speed पूर्णांकerfaces anyway.
	 */
	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;
	अगर (unlikely(skb_linearize(&pkt->skb) != 0)) अणु
		PKT_ERROR(pkt, "linearize failed\n");
		वापस -EPROTO;
	पूर्ण
	वापस iter_func(data, pkt->skb.data, cfpkt_getlen(pkt));
पूर्ण

पूर्णांक cfpkt_setlen(काष्ठा cfpkt *pkt, u16 len)
अणु
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);


	अगर (unlikely(is_erronous(pkt)))
		वापस -EPROTO;

	अगर (likely(len <= skb->len)) अणु
		अगर (unlikely(skb->data_len))
			___pskb_trim(skb, len);
		अन्यथा
			skb_trim(skb, len);

		वापस cfpkt_getlen(pkt);
	पूर्ण

	/* Need to expand SKB */
	अगर (unlikely(!cfpkt_pad_trail(pkt, len - skb->len)))
		PKT_ERROR(pkt, "skb_pad_trail failed\n");

	वापस cfpkt_getlen(pkt);
पूर्ण

काष्ठा cfpkt *cfpkt_append(काष्ठा cfpkt *dstpkt,
			   काष्ठा cfpkt *addpkt,
			   u16 expectlen)
अणु
	काष्ठा sk_buff *dst = pkt_to_skb(dstpkt);
	काष्ठा sk_buff *add = pkt_to_skb(addpkt);
	u16 addlen = skb_headlen(add);
	u16 neededtailspace;
	काष्ठा sk_buff *पंचांगp;
	u16 dstlen;
	u16 createlen;
	अगर (unlikely(is_erronous(dstpkt) || is_erronous(addpkt))) अणु
		वापस dstpkt;
	पूर्ण
	अगर (expectlen > addlen)
		neededtailspace = expectlen;
	अन्यथा
		neededtailspace = addlen;

	अगर (dst->tail + neededtailspace > dst->end) अणु
		/* Create a dumplicate of 'dst' with more tail space */
		काष्ठा cfpkt *पंचांगppkt;
		dstlen = skb_headlen(dst);
		createlen = dstlen + neededtailspace;
		पंचांगppkt = cfpkt_create(createlen + PKT_PREFIX + PKT_POSTFIX);
		अगर (पंचांगppkt == शून्य)
			वापस शून्य;
		पंचांगp = pkt_to_skb(पंचांगppkt);
		skb_put_data(पंचांगp, dst->data, dstlen);
		cfpkt_destroy(dstpkt);
		dst = पंचांगp;
	पूर्ण
	skb_put_data(dst, add->data, skb_headlen(add));
	cfpkt_destroy(addpkt);
	वापस skb_to_pkt(dst);
पूर्ण

काष्ठा cfpkt *cfpkt_split(काष्ठा cfpkt *pkt, u16 pos)
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा sk_buff *skb = pkt_to_skb(pkt);
	काष्ठा cfpkt *पंचांगppkt;
	u8 *split = skb->data + pos;
	u16 len2nd = skb_tail_poपूर्णांकer(skb) - split;

	अगर (unlikely(is_erronous(pkt)))
		वापस शून्य;

	अगर (skb->data + pos > skb_tail_poपूर्णांकer(skb)) अणु
		PKT_ERROR(pkt, "trying to split beyond end of packet\n");
		वापस शून्य;
	पूर्ण

	/* Create a new packet क्रम the second part of the data */
	पंचांगppkt = cfpkt_create_pfx(len2nd + PKT_PREFIX + PKT_POSTFIX,
				  PKT_PREFIX);
	अगर (पंचांगppkt == शून्य)
		वापस शून्य;
	skb2 = pkt_to_skb(पंचांगppkt);


	अगर (skb2 == शून्य)
		वापस शून्य;

	skb_put_data(skb2, split, len2nd);

	/* Reduce the length of the original packet */
	skb_trim(skb, pos);

	skb2->priority = skb->priority;
	वापस skb_to_pkt(skb2);
पूर्ण

bool cfpkt_erroneous(काष्ठा cfpkt *pkt)
अणु
	वापस cfpkt_priv(pkt)->erronous;
पूर्ण

काष्ठा caअगर_payload_info *cfpkt_info(काष्ठा cfpkt *pkt)
अणु
	वापस (काष्ठा caअगर_payload_info *)&pkt_to_skb(pkt)->cb;
पूर्ण
EXPORT_SYMBOL(cfpkt_info);

व्योम cfpkt_set_prio(काष्ठा cfpkt *pkt, पूर्णांक prio)
अणु
	pkt_to_skb(pkt)->priority = prio;
पूर्ण
EXPORT_SYMBOL(cfpkt_set_prio);
