<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* I2C message transfer tracepoपूर्णांकs
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM i2c

#अगर !defined(_TRACE_I2C_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_I2C_H

#समावेश <linux/i2c.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * drivers/i2c/i2c-core-base.c
 */
बाह्य पूर्णांक i2c_transfer_trace_reg(व्योम);
बाह्य व्योम i2c_transfer_trace_unreg(व्योम);

/*
 * __i2c_transfer() ग_लिखो request
 */
TRACE_EVENT_FN(i2c_ग_लिखो,
	       TP_PROTO(स्थिर काष्ठा i2c_adapter *adap, स्थिर काष्ठा i2c_msg *msg,
			पूर्णांक num),
	       TP_ARGS(adap, msg, num),
	       TP_STRUCT__entry(
		       __field(पूर्णांक,	adapter_nr		)
		       __field(__u16,	msg_nr			)
		       __field(__u16,	addr			)
		       __field(__u16,	flags			)
		       __field(__u16,	len			)
		       __dynamic_array(__u8, buf, msg->len)	),
	       TP_fast_assign(
		       __entry->adapter_nr = adap->nr;
		       __entry->msg_nr = num;
		       __entry->addr = msg->addr;
		       __entry->flags = msg->flags;
		       __entry->len = msg->len;
		       स_नकल(__get_dynamic_array(buf), msg->buf, msg->len);
			      ),
	       TP_prपूर्णांकk("i2c-%d #%u a=%03x f=%04x l=%u [%*phD]",
			 __entry->adapter_nr,
			 __entry->msg_nr,
			 __entry->addr,
			 __entry->flags,
			 __entry->len,
			 __entry->len, __get_dynamic_array(buf)
			 ),
	       i2c_transfer_trace_reg,
	       i2c_transfer_trace_unreg);

/*
 * __i2c_transfer() पढ़ो request
 */
TRACE_EVENT_FN(i2c_पढ़ो,
	       TP_PROTO(स्थिर काष्ठा i2c_adapter *adap, स्थिर काष्ठा i2c_msg *msg,
			पूर्णांक num),
	       TP_ARGS(adap, msg, num),
	       TP_STRUCT__entry(
		       __field(पूर्णांक,	adapter_nr		)
		       __field(__u16,	msg_nr			)
		       __field(__u16,	addr			)
		       __field(__u16,	flags			)
		       __field(__u16,	len			)
				),
	       TP_fast_assign(
		       __entry->adapter_nr = adap->nr;
		       __entry->msg_nr = num;
		       __entry->addr = msg->addr;
		       __entry->flags = msg->flags;
		       __entry->len = msg->len;
			      ),
	       TP_prपूर्णांकk("i2c-%d #%u a=%03x f=%04x l=%u",
			 __entry->adapter_nr,
			 __entry->msg_nr,
			 __entry->addr,
			 __entry->flags,
			 __entry->len
			 ),
	       i2c_transfer_trace_reg,
		       i2c_transfer_trace_unreg);

/*
 * __i2c_transfer() पढ़ो reply
 */
TRACE_EVENT_FN(i2c_reply,
	       TP_PROTO(स्थिर काष्ठा i2c_adapter *adap, स्थिर काष्ठा i2c_msg *msg,
			पूर्णांक num),
	       TP_ARGS(adap, msg, num),
	       TP_STRUCT__entry(
		       __field(पूर्णांक,	adapter_nr		)
		       __field(__u16,	msg_nr			)
		       __field(__u16,	addr			)
		       __field(__u16,	flags			)
		       __field(__u16,	len			)
		       __dynamic_array(__u8, buf, msg->len)	),
	       TP_fast_assign(
		       __entry->adapter_nr = adap->nr;
		       __entry->msg_nr = num;
		       __entry->addr = msg->addr;
		       __entry->flags = msg->flags;
		       __entry->len = msg->len;
		       स_नकल(__get_dynamic_array(buf), msg->buf, msg->len);
			      ),
	       TP_prपूर्णांकk("i2c-%d #%u a=%03x f=%04x l=%u [%*phD]",
			 __entry->adapter_nr,
			 __entry->msg_nr,
			 __entry->addr,
			 __entry->flags,
			 __entry->len,
			 __entry->len, __get_dynamic_array(buf)
			 ),
	       i2c_transfer_trace_reg,
	       i2c_transfer_trace_unreg);

/*
 * __i2c_transfer() result
 */
TRACE_EVENT_FN(i2c_result,
	       TP_PROTO(स्थिर काष्ठा i2c_adapter *adap, पूर्णांक num, पूर्णांक ret),
	       TP_ARGS(adap, num, ret),
	       TP_STRUCT__entry(
		       __field(पूर्णांक,	adapter_nr		)
		       __field(__u16,	nr_msgs			)
		       __field(__s16,	ret			)
				),
	       TP_fast_assign(
		       __entry->adapter_nr = adap->nr;
		       __entry->nr_msgs = num;
		       __entry->ret = ret;
			      ),
	       TP_prपूर्णांकk("i2c-%d n=%u ret=%d",
			 __entry->adapter_nr,
			 __entry->nr_msgs,
			 __entry->ret
			 ),
	       i2c_transfer_trace_reg,
	       i2c_transfer_trace_unreg);

#पूर्ण_अगर /* _TRACE_I2C_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
