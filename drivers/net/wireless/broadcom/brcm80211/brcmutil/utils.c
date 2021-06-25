<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>

#समावेश <brcmu_utils.h>

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom 802.11n wireless LAN driver utilities.");
MODULE_LICENSE("Dual BSD/GPL");

काष्ठा sk_buff *brcmu_pkt_buf_get_skb(uपूर्णांक len)
अणु
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(len);
	अगर (skb) अणु
		skb_put(skb, len);
		skb->priority = 0;
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL(brcmu_pkt_buf_get_skb);

/* Free the driver packet. Free the tag अगर present */
व्योम brcmu_pkt_buf_मुक्त_skb(काष्ठा sk_buff *skb)
अणु
	अगर (!skb)
		वापस;

	WARN_ON(skb->next);
	dev_kमुक्त_skb_any(skb);
पूर्ण
EXPORT_SYMBOL(brcmu_pkt_buf_मुक्त_skb);

/*
 * osl multiple-precedence packet queue
 * hi_prec is always >= the number of the highest non-empty precedence
 */
काष्ठा sk_buff *brcmu_pktq_penq(काष्ठा pktq *pq, पूर्णांक prec,
				      काष्ठा sk_buff *p)
अणु
	काष्ठा sk_buff_head *q;

	अगर (pktq_full(pq) || pktq_pfull(pq, prec))
		वापस शून्य;

	q = &pq->q[prec].skblist;
	skb_queue_tail(q, p);
	pq->len++;

	अगर (pq->hi_prec < prec)
		pq->hi_prec = (u8) prec;

	वापस p;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_penq);

काष्ठा sk_buff *brcmu_pktq_penq_head(काष्ठा pktq *pq, पूर्णांक prec,
					   काष्ठा sk_buff *p)
अणु
	काष्ठा sk_buff_head *q;

	अगर (pktq_full(pq) || pktq_pfull(pq, prec))
		वापस शून्य;

	q = &pq->q[prec].skblist;
	skb_queue_head(q, p);
	pq->len++;

	अगर (pq->hi_prec < prec)
		pq->hi_prec = (u8) prec;

	वापस p;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_penq_head);

काष्ठा sk_buff *brcmu_pktq_pdeq(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	काष्ठा sk_buff_head *q;
	काष्ठा sk_buff *p;

	q = &pq->q[prec].skblist;
	p = skb_dequeue(q);
	अगर (p == शून्य)
		वापस शून्य;

	pq->len--;
	वापस p;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_pdeq);

/*
 * precedence based dequeue with match function. Passing a शून्य poपूर्णांकer
 * क्रम the match function parameter is considered to be a wildcard so
 * any packet on the queue is वापसed. In that हाल it is no dअगरferent
 * from brcmu_pktq_pdeq() above.
 */
काष्ठा sk_buff *brcmu_pktq_pdeq_match(काष्ठा pktq *pq, पूर्णांक prec,
				      bool (*match_fn)(काष्ठा sk_buff *skb,
						       व्योम *arg), व्योम *arg)
अणु
	काष्ठा sk_buff_head *q;
	काष्ठा sk_buff *p, *next;

	q = &pq->q[prec].skblist;
	skb_queue_walk_safe(q, p, next) अणु
		अगर (match_fn == शून्य || match_fn(p, arg)) अणु
			skb_unlink(p, q);
			pq->len--;
			वापस p;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_pdeq_match);

काष्ठा sk_buff *brcmu_pktq_pdeq_tail(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	काष्ठा sk_buff_head *q;
	काष्ठा sk_buff *p;

	q = &pq->q[prec].skblist;
	p = skb_dequeue_tail(q);
	अगर (p == शून्य)
		वापस शून्य;

	pq->len--;
	वापस p;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_pdeq_tail);

व्योम
brcmu_pktq_pflush(काष्ठा pktq *pq, पूर्णांक prec, bool dir,
		  bool (*fn)(काष्ठा sk_buff *, व्योम *), व्योम *arg)
अणु
	काष्ठा sk_buff_head *q;
	काष्ठा sk_buff *p, *next;

	q = &pq->q[prec].skblist;
	skb_queue_walk_safe(q, p, next) अणु
		अगर (fn == शून्य || (*fn) (p, arg)) अणु
			skb_unlink(p, q);
			brcmu_pkt_buf_मुक्त_skb(p);
			pq->len--;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_pflush);

व्योम brcmu_pktq_flush(काष्ठा pktq *pq, bool dir,
		      bool (*fn)(काष्ठा sk_buff *, व्योम *), व्योम *arg)
अणु
	पूर्णांक prec;
	क्रम (prec = 0; prec < pq->num_prec; prec++)
		brcmu_pktq_pflush(pq, prec, dir, fn, arg);
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_flush);

व्योम brcmu_pktq_init(काष्ठा pktq *pq, पूर्णांक num_prec, पूर्णांक max_len)
अणु
	पूर्णांक prec;

	/* pq is variable size; only zero out what's requested */
	स_रखो(pq, 0,
	      दुरत्व(काष्ठा pktq, q) + (माप(काष्ठा pktq_prec) * num_prec));

	pq->num_prec = (u16) num_prec;

	pq->max = (u16) max_len;

	क्रम (prec = 0; prec < num_prec; prec++) अणु
		pq->q[prec].max = pq->max;
		skb_queue_head_init(&pq->q[prec].skblist);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_init);

काष्ठा sk_buff *brcmu_pktq_peek_tail(काष्ठा pktq *pq, पूर्णांक *prec_out)
अणु
	पूर्णांक prec;

	अगर (pq->len == 0)
		वापस शून्य;

	क्रम (prec = 0; prec < pq->hi_prec; prec++)
		अगर (!skb_queue_empty(&pq->q[prec].skblist))
			अवरोध;

	अगर (prec_out)
		*prec_out = prec;

	वापस skb_peek_tail(&pq->q[prec].skblist);
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_peek_tail);

/* Return sum of lengths of a specअगरic set of precedences */
पूर्णांक brcmu_pktq_mlen(काष्ठा pktq *pq, uपूर्णांक prec_bmp)
अणु
	पूर्णांक prec, len;

	len = 0;

	क्रम (prec = 0; prec <= pq->hi_prec; prec++)
		अगर (prec_bmp & (1 << prec))
			len += pq->q[prec].skblist.qlen;

	वापस len;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_mlen);

/* Priority dequeue from a specअगरic set of precedences */
काष्ठा sk_buff *brcmu_pktq_mdeq(काष्ठा pktq *pq, uपूर्णांक prec_bmp,
				      पूर्णांक *prec_out)
अणु
	काष्ठा sk_buff_head *q;
	काष्ठा sk_buff *p;
	पूर्णांक prec;

	अगर (pq->len == 0)
		वापस शून्य;

	जबतक ((prec = pq->hi_prec) > 0 &&
	       skb_queue_empty(&pq->q[prec].skblist))
		pq->hi_prec--;

	जबतक ((prec_bmp & (1 << prec)) == 0 ||
	       skb_queue_empty(&pq->q[prec].skblist))
		अगर (prec-- == 0)
			वापस शून्य;

	q = &pq->q[prec].skblist;
	p = skb_dequeue(q);
	अगर (p == शून्य)
		वापस शून्य;

	pq->len--;

	अगर (prec_out)
		*prec_out = prec;

	वापस p;
पूर्ण
EXPORT_SYMBOL(brcmu_pktq_mdeq);

/* Produce a human-पढ़ोable string क्रम boardrev */
अक्षर *brcmu_boardrev_str(u32 brev, अक्षर *buf)
अणु
	अक्षर c;

	अगर (brev < 0x100) अणु
		snम_लिखो(buf, BRCMU_BOARDREV_LEN, "%d.%d",
			 (brev & 0xf0) >> 4, brev & 0xf);
	पूर्ण अन्यथा अणु
		c = (brev & 0xf000) == 0x1000 ? 'P' : 'A';
		snम_लिखो(buf, BRCMU_BOARDREV_LEN, "%c%03x", c, brev & 0xfff);
	पूर्ण
	वापस buf;
पूर्ण
EXPORT_SYMBOL(brcmu_boardrev_str);

अक्षर *brcmu_करोtrev_str(u32 करोtrev, अक्षर *buf)
अणु
	u8 करोtval[4];

	अगर (!करोtrev) अणु
		snम_लिखो(buf, BRCMU_DOTREV_LEN, "unknown");
		वापस buf;
	पूर्ण
	करोtval[0] = (करोtrev >> 24) & 0xFF;
	करोtval[1] = (करोtrev >> 16) & 0xFF;
	करोtval[2] = (करोtrev >> 8) & 0xFF;
	करोtval[3] = करोtrev & 0xFF;

	अगर (करोtval[3])
		snम_लिखो(buf, BRCMU_DOTREV_LEN, "%d.%d.%d.%d", करोtval[0],
			करोtval[1], करोtval[2], करोtval[3]);
	अन्यथा अगर (करोtval[2])
		snम_लिखो(buf, BRCMU_DOTREV_LEN, "%d.%d.%d", करोtval[0],
			करोtval[1], करोtval[2]);
	अन्यथा
		snम_लिखो(buf, BRCMU_DOTREV_LEN, "%d.%d", करोtval[0],
			करोtval[1]);

	वापस buf;
पूर्ण
EXPORT_SYMBOL(brcmu_करोtrev_str);

#अगर defined(DEBUG)
/* pretty hex prपूर्णांक a pkt buffer chain */
व्योम brcmu_prpkt(स्थिर अक्षर *msg, काष्ठा sk_buff *p0)
अणु
	काष्ठा sk_buff *p;

	अगर (msg && (msg[0] != '\0'))
		pr_debug("%s:\n", msg);

	क्रम (p = p0; p; p = p->next)
		prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_OFFSET, p->data, p->len);
पूर्ण
EXPORT_SYMBOL(brcmu_prpkt);

व्योम brcmu_dbg_hex_dump(स्थिर व्योम *data, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_debug("%pV", &vaf);

	बहु_पूर्ण(args);

	prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_OFFSET, data, size);
पूर्ण
EXPORT_SYMBOL(brcmu_dbg_hex_dump);

#पूर्ण_अगर				/* defined(DEBUG) */
