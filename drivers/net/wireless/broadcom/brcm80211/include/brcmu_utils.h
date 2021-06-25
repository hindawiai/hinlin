<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	_BRCMU_UTILS_H_
#घोषणा	_BRCMU_UTILS_H_

#समावेश <linux/skbuff.h>

/*
 * Spin at most 'us' microseconds while 'exp' is true.
 * Caller should explicitly test 'exp' when this completes
 * and take appropriate error action अगर 'exp' is still true.
 */
#घोषणा SPINWAIT(exp, us) अणु \
	uपूर्णांक countकरोwn = (us) + 9; \
	जबतक ((exp) && (countकरोwn >= 10)) अणु\
		udelay(10); \
		countकरोwn -= 10; \
	पूर्ण \
पूर्ण

/* osl multi-precedence packet queue */
#घोषणा PKTQ_LEN_DEFAULT        128	/* Max 128 packets */
#घोषणा PKTQ_MAX_PREC           16	/* Maximum precedence levels */

#घोषणा BCME_STRLEN		64	/* Max string length क्रम BCM errors */

/* the largest reasonable packet buffer driver uses क्रम ethernet MTU in bytes */
#घोषणा	PKTBUFSZ	2048

#अगर_अघोषित setbit
#अगर_अघोषित NBBY			/* the BSD family defines NBBY */
#घोषणा	NBBY	8		/* 8 bits per byte */
#पूर्ण_अगर				/* #अगर_अघोषित NBBY */
#घोषणा	setbit(a, i)	(((u8 *)a)[(i)/NBBY] |= 1<<((i)%NBBY))
#घोषणा	clrbit(a, i)	(((u8 *)a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#घोषणा	isset(a, i)	(((स्थिर u8 *)a)[(i)/NBBY] & (1<<((i)%NBBY)))
#घोषणा	isclr(a, i)	((((स्थिर u8 *)a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)
#पूर्ण_अगर				/* setbit */

#घोषणा	NBITS(type)	(माप(type) * 8)
#घोषणा NBITVAL(nbits)	(1 << (nbits))
#घोषणा MAXBITVAL(nbits)	((1 << (nbits)) - 1)
#घोषणा	NBITMASK(nbits)	MAXBITVAL(nbits)
#घोषणा MAXNBVAL(nbyte)	MAXBITVAL((nbyte) * 8)

/* crc defines */
#घोषणा CRC16_INIT_VALUE 0xffff	/* Initial CRC16 checksum value */
#घोषणा CRC16_GOOD_VALUE 0xf0b8	/* Good final CRC16 checksum value */

/* 18-bytes of Ethernet address buffer length */
#घोषणा ETHER_ADDR_STR_LEN	18

काष्ठा pktq_prec अणु
	काष्ठा sk_buff_head skblist;
	u16 max;		/* maximum number of queued packets */
पूर्ण;

/* multi-priority pkt queue */
काष्ठा pktq अणु
	u16 num_prec;	/* number of precedences in use */
	u16 hi_prec;	/* rapid dequeue hपूर्णांक (>= highest non-empty prec) */
	u16 max;	/* total max packets */
	u16 len;	/* total number of packets */
	/*
	 * q array must be last since # of elements can be either
	 * PKTQ_MAX_PREC or 1
	 */
	काष्ठा pktq_prec q[PKTQ_MAX_PREC];
पूर्ण;

/* operations on a specअगरic precedence in packet queue */

अटल अंतरभूत पूर्णांक pktq_plen(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस pq->q[prec].skblist.qlen;
पूर्ण

अटल अंतरभूत पूर्णांक pktq_pavail(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस pq->q[prec].max - pq->q[prec].skblist.qlen;
पूर्ण

अटल अंतरभूत bool pktq_pfull(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस pq->q[prec].skblist.qlen >= pq->q[prec].max;
पूर्ण

अटल अंतरभूत bool pktq_pempty(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस skb_queue_empty(&pq->q[prec].skblist);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pktq_ppeek(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस skb_peek(&pq->q[prec].skblist);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *pktq_ppeek_tail(काष्ठा pktq *pq, पूर्णांक prec)
अणु
	वापस skb_peek_tail(&pq->q[prec].skblist);
पूर्ण

काष्ठा sk_buff *brcmu_pktq_penq(काष्ठा pktq *pq, पूर्णांक prec, काष्ठा sk_buff *p);
काष्ठा sk_buff *brcmu_pktq_penq_head(काष्ठा pktq *pq, पूर्णांक prec,
				     काष्ठा sk_buff *p);
काष्ठा sk_buff *brcmu_pktq_pdeq(काष्ठा pktq *pq, पूर्णांक prec);
काष्ठा sk_buff *brcmu_pktq_pdeq_tail(काष्ठा pktq *pq, पूर्णांक prec);
काष्ठा sk_buff *brcmu_pktq_pdeq_match(काष्ठा pktq *pq, पूर्णांक prec,
				      bool (*match_fn)(काष्ठा sk_buff *p,
						       व्योम *arg),
				      व्योम *arg);

/* packet primitives */
काष्ठा sk_buff *brcmu_pkt_buf_get_skb(uपूर्णांक len);
व्योम brcmu_pkt_buf_मुक्त_skb(काष्ठा sk_buff *skb);

/* Empty the queue at particular precedence level */
/* callback function fn(pkt, arg) वापसs true अगर pkt beदीर्घs to अगर */
व्योम brcmu_pktq_pflush(काष्ठा pktq *pq, पूर्णांक prec, bool dir,
		       bool (*fn)(काष्ठा sk_buff *, व्योम *), व्योम *arg);

/* operations on a set of precedences in packet queue */

पूर्णांक brcmu_pktq_mlen(काष्ठा pktq *pq, uपूर्णांक prec_bmp);
काष्ठा sk_buff *brcmu_pktq_mdeq(काष्ठा pktq *pq, uपूर्णांक prec_bmp, पूर्णांक *prec_out);

/* operations on packet queue as a whole */

अटल अंतरभूत पूर्णांक pktq_len(काष्ठा pktq *pq)
अणु
	वापस (पूर्णांक)pq->len;
पूर्ण

अटल अंतरभूत पूर्णांक pktq_max(काष्ठा pktq *pq)
अणु
	वापस (पूर्णांक)pq->max;
पूर्ण

अटल अंतरभूत पूर्णांक pktq_avail(काष्ठा pktq *pq)
अणु
	वापस (पूर्णांक)(pq->max - pq->len);
पूर्ण

अटल अंतरभूत bool pktq_full(काष्ठा pktq *pq)
अणु
	वापस pq->len >= pq->max;
पूर्ण

अटल अंतरभूत bool pktq_empty(काष्ठा pktq *pq)
अणु
	वापस pq->len == 0;
पूर्ण

व्योम brcmu_pktq_init(काष्ठा pktq *pq, पूर्णांक num_prec, पूर्णांक max_len);
/* prec_out may be शून्य अगर caller is not पूर्णांकerested in वापस value */
काष्ठा sk_buff *brcmu_pktq_peek_tail(काष्ठा pktq *pq, पूर्णांक *prec_out);
व्योम brcmu_pktq_flush(काष्ठा pktq *pq, bool dir,
		      bool (*fn)(काष्ठा sk_buff *, व्योम *), व्योम *arg);

/* बाह्यs */
/* ip address */
काष्ठा ipv4_addr;

/*
 * bitfield macros using masking and shअगरt
 *
 * remark: the mask parameter should be a shअगरted mask.
 */
अटल अंतरभूत व्योम brcmu_maskset32(u32 *var, u32 mask, u8 shअगरt, u32 value)
अणु
	value = (value << shअगरt) & mask;
	*var = (*var & ~mask) | value;
पूर्ण
अटल अंतरभूत u32 brcmu_maskget32(u32 var, u32 mask, u8 shअगरt)
अणु
	वापस (var & mask) >> shअगरt;
पूर्ण
अटल अंतरभूत व्योम brcmu_maskset16(u16 *var, u16 mask, u8 shअगरt, u16 value)
अणु
	value = (value << shअगरt) & mask;
	*var = (*var & ~mask) | value;
पूर्ण
अटल अंतरभूत u16 brcmu_maskget16(u16 var, u16 mask, u8 shअगरt)
अणु
	वापस (var & mask) >> shअगरt;
पूर्ण

/* बाह्यs */
/* क्रमmat/prपूर्णांक */
#अगर_घोषित DEBUG
व्योम brcmu_prpkt(स्थिर अक्षर *msg, काष्ठा sk_buff *p0);
#अन्यथा
#घोषणा brcmu_prpkt(a, b)
#पूर्ण_अगर				/* DEBUG */

#अगर_घोषित DEBUG
__म_लिखो(3, 4)
व्योम brcmu_dbg_hex_dump(स्थिर व्योम *data, माप_प्रकार size, स्थिर अक्षर *fmt, ...);
#अन्यथा
__म_लिखो(3, 4)
अटल अंतरभूत
व्योम brcmu_dbg_hex_dump(स्थिर व्योम *data, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा BRCMU_BOARDREV_LEN	8
#घोषणा BRCMU_DOTREV_LEN	16

अक्षर *brcmu_boardrev_str(u32 brev, अक्षर *buf);
अक्षर *brcmu_करोtrev_str(u32 करोtrev, अक्षर *buf);

#पूर्ण_अगर				/* _BRCMU_UTILS_H_ */
