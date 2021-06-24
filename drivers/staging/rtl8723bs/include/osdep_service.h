<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __OSDEP_SERVICE_H_
#घोषणा __OSDEP_SERVICE_H_


#घोषणा _FAIL		0
#घोषणा _SUCCESS	1
#घोषणा RTW_RX_HANDLED 2

#समावेश <osdep_service_linux.h>

#अगर_अघोषित BIT
	#घोषणा BIT(x)	(1 << (x))
#पूर्ण_अगर

#घोषणा BIT0	0x00000001
#घोषणा BIT1	0x00000002
#घोषणा BIT2	0x00000004
#घोषणा BIT3	0x00000008
#घोषणा BIT4	0x00000010
#घोषणा BIT5	0x00000020
#घोषणा BIT6	0x00000040
#घोषणा BIT7	0x00000080
#घोषणा BIT8	0x00000100
#घोषणा BIT9	0x00000200
#घोषणा BIT10	0x00000400
#घोषणा BIT11	0x00000800
#घोषणा BIT12	0x00001000
#घोषणा BIT13	0x00002000
#घोषणा BIT14	0x00004000
#घोषणा BIT15	0x00008000
#घोषणा BIT16	0x00010000
#घोषणा BIT17	0x00020000
#घोषणा BIT18	0x00040000
#घोषणा BIT19	0x00080000
#घोषणा BIT20	0x00100000
#घोषणा BIT21	0x00200000
#घोषणा BIT22	0x00400000
#घोषणा BIT23	0x00800000
#घोषणा BIT24	0x01000000
#घोषणा BIT25	0x02000000
#घोषणा BIT26	0x04000000
#घोषणा BIT27	0x08000000
#घोषणा BIT28	0x10000000
#घोषणा BIT29	0x20000000
#घोषणा BIT30	0x40000000
#घोषणा BIT31	0x80000000
#घोषणा BIT32	0x0100000000
#घोषणा BIT33	0x0200000000
#घोषणा BIT34	0x0400000000
#घोषणा BIT35	0x0800000000
#घोषणा BIT36	0x1000000000

बाह्य पूर्णांक RTW_STATUS_CODE(पूर्णांक error_code);

व्योम *_rtw_zदो_स्मृति(u32 sz);
व्योम *_rtw_दो_स्मृति(u32 sz);
व्योम _kमुक्त(u8 *pbuf, u32 sz);

काष्ठा sk_buff *_rtw_skb_alloc(u32 sz);
काष्ठा sk_buff *_rtw_skb_copy(स्थिर काष्ठा sk_buff *skb);
पूर्णांक _rtw_netअगर_rx(काष्ठा net_device *ndev, काष्ठा sk_buff *skb);

#घोषणा rtw_दो_स्मृति(sz)			_rtw_दो_स्मृति((sz))
#घोषणा rtw_zदो_स्मृति(sz)			_rtw_zदो_स्मृति((sz))

#घोषणा rtw_skb_alloc(size) _rtw_skb_alloc((size))
#घोषणा rtw_skb_alloc_f(size, mstat_f)	_rtw_skb_alloc((size))
#घोषणा rtw_skb_copy(skb)	_rtw_skb_copy((skb))
#घोषणा rtw_skb_copy_f(skb, mstat_f)	_rtw_skb_copy((skb))
#घोषणा rtw_netअगर_rx(ndev, skb) _rtw_netअगर_rx(ndev, skb)

बाह्य व्योम _rtw_init_queue(काष्ठा __queue	*pqueue);

अटल अंतरभूत व्योम thपढ़ो_enter(अक्षर *name)
अणु
	allow_संकेत(संक_इति);
पूर्ण

अटल अंतरभूत व्योम flush_संकेतs_thपढ़ो(व्योम)
अणु
	अगर (संकेत_pending(current))
	अणु
		flush_संकेतs(current);
	पूर्ण
पूर्ण

#घोषणा rtw_warn_on(condition) WARN_ON(condition)

अटल अंतरभूत पूर्णांक rtw_bug_check(व्योम *parg1, व्योम *parg2, व्योम *parg3, व्योम *parg4)
अणु
	पूर्णांक ret = true;

	वापस ret;

पूर्ण

#घोषणा _RND(sz, r) ((((sz)+((r)-1))/(r))*(r))

#अगर_अघोषित MAC_ARG
#घोषणा MAC_ARG(x) (x)
#पूर्ण_अगर

बाह्य व्योम rtw_मुक्त_netdev(काष्ठा net_device * netdev);

/* Macros क्रम handling unaligned memory accesses */

व्योम rtw_buf_मुक्त(u8 **buf, u32 *buf_len);
व्योम rtw_buf_update(u8 **buf, u32 *buf_len, u8 *src, u32 src_len);

काष्ठा rtw_cbuf अणु
	u32 ग_लिखो;
	u32 पढ़ो;
	u32 size;
	व्योम *bufs[0];
पूर्ण;

bool rtw_cbuf_full(काष्ठा rtw_cbuf *cbuf);
bool rtw_cbuf_empty(काष्ठा rtw_cbuf *cbuf);
bool rtw_cbuf_push(काष्ठा rtw_cbuf *cbuf, व्योम *buf);
व्योम *rtw_cbuf_pop(काष्ठा rtw_cbuf *cbuf);
काष्ठा rtw_cbuf *rtw_cbuf_alloc(u32 size);

/*  String handler */
/*
 * Write क्रमmatted output to sized buffer
 */
#घोषणा rtw_प्र_लिखो(buf, size, क्रमmat, arg...)	snम_लिखो(buf, size, क्रमmat, ##arg)

#पूर्ण_अगर
