<शैली गुरु>
/*
 * net/tipc/trace.h: TIPC tracepoपूर्णांकs
 *
 * Copyright (c) 2018, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "ASIS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tipc

#अगर !defined(_TIPC_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TIPC_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "core.h"
#समावेश "link.h"
#समावेश "socket.h"
#समावेश "node.h"

#घोषणा SKB_LMIN	(100)
#घोषणा SKB_LMAX	(SKB_LMIN * 2)
#घोषणा LIST_LMIN	(SKB_LMIN * 3)
#घोषणा LIST_LMAX	(SKB_LMIN * 11)
#घोषणा SK_LMIN		(SKB_LMIN * 2)
#घोषणा SK_LMAX		(SKB_LMIN * 11)
#घोषणा LINK_LMIN	(SKB_LMIN)
#घोषणा LINK_LMAX	(SKB_LMIN * 16)
#घोषणा NODE_LMIN	(SKB_LMIN)
#घोषणा NODE_LMAX	(SKB_LMIN * 11)

#अगर_अघोषित __TIPC_TRACE_ENUM
#घोषणा __TIPC_TRACE_ENUM
क्रमागत अणु
	TIPC_DUMP_NONE		= 0,

	TIPC_DUMP_TRANSMQ	= 1,
	TIPC_DUMP_BACKLOGQ	= (1 << 1),
	TIPC_DUMP_DEFERDQ	= (1 << 2),
	TIPC_DUMP_INPUTQ	= (1 << 3),
	TIPC_DUMP_WAKEUP        = (1 << 4),

	TIPC_DUMP_SK_SNDQ	= (1 << 8),
	TIPC_DUMP_SK_RCVQ	= (1 << 9),
	TIPC_DUMP_SK_BKLGQ	= (1 << 10),
	TIPC_DUMP_ALL		= 0xffffu
पूर्ण;
#पूर्ण_अगर

/* Link & Node FSM states: */
#घोषणा state_sym(val)							  \
	__prपूर्णांक_symbolic(val,						  \
			अणु(0xe),		"ESTABLISHED"			पूर्ण,\
			अणु(0xe << 4),	"ESTABLISHING"			पूर्ण,\
			अणु(0x1 << 8),	"RESET"				पूर्ण,\
			अणु(0x2 << 12),	"RESETTING"			पूर्ण,\
			अणु(0xd << 16),	"PEER_RESET"			पूर्ण,\
			अणु(0xf << 20),	"FAILINGOVER"			पूर्ण,\
			अणु(0xc << 24),	"SYNCHING"			पूर्ण,\
			अणु(0xdd),	"SELF_DOWN_PEER_DOWN"		पूर्ण,\
			अणु(0xaa),	"SELF_UP_PEER_UP"		पूर्ण,\
			अणु(0xd1),	"SELF_DOWN_PEER_LEAVING"	पूर्ण,\
			अणु(0xac),	"SELF_UP_PEER_COMING"		पूर्ण,\
			अणु(0xca),	"SELF_COMING_PEER_UP"		पूर्ण,\
			अणु(0x1d),	"SELF_LEAVING_PEER_DOWN"	पूर्ण,\
			अणु(0xf0),	"FAILINGOVER"			पूर्ण,\
			अणु(0xcc),	"SYNCHING"			पूर्ण)

/* Link & Node FSM events: */
#घोषणा evt_sym(val)							  \
	__prपूर्णांक_symbolic(val,						  \
			अणु(0xec1ab1e),	"ESTABLISH_EVT"			पूर्ण,\
			अणु(0x9eed0e),	"PEER_RESET_EVT"		पूर्ण,\
			अणु(0xfa110e),	"FAILURE_EVT"			पूर्ण,\
			अणु(0x10ca1d0e),	"RESET_EVT"			पूर्ण,\
			अणु(0xfa110bee),	"FAILOVER_BEGIN_EVT"		पूर्ण,\
			अणु(0xfa110ede),	"FAILOVER_END_EVT"		पूर्ण,\
			अणु(0xc1ccbee),	"SYNCH_BEGIN_EVT"		पूर्ण,\
			अणु(0xc1ccede),	"SYNCH_END_EVT"			पूर्ण,\
			अणु(0xece),	"SELF_ESTABL_CONTACT_EVT"	पूर्ण,\
			अणु(0x1ce),	"SELF_LOST_CONTACT_EVT"		पूर्ण,\
			अणु(0x9ece),	"PEER_ESTABL_CONTACT_EVT"	पूर्ण,\
			अणु(0x91ce),	"PEER_LOST_CONTACT_EVT"		पूर्ण,\
			अणु(0xfbe),	"FAILOVER_BEGIN_EVT"		पूर्ण,\
			अणु(0xfee),	"FAILOVER_END_EVT"		पूर्ण,\
			अणु(0xcbe),	"SYNCH_BEGIN_EVT"		पूर्ण,\
			अणु(0xcee),	"SYNCH_END_EVT"			पूर्ण)

/* Bearer, net device events: */
#घोषणा dev_evt_sym(val)						  \
	__prपूर्णांक_symbolic(val,						  \
			अणु(NETDEV_CHANGE),	"NETDEV_CHANGE"		पूर्ण,\
			अणु(NETDEV_GOING_DOWN),	"NETDEV_GOING_DOWN"	पूर्ण,\
			अणु(NETDEV_UP),		"NETDEV_UP"		पूर्ण,\
			अणु(NETDEV_CHANGEMTU),	"NETDEV_CHANGEMTU"	पूर्ण,\
			अणु(NETDEV_CHANGEADDR),	"NETDEV_CHANGEADDR"	पूर्ण,\
			अणु(NETDEV_UNREGISTER),	"NETDEV_UNREGISTER"	पूर्ण,\
			अणु(NETDEV_CHANGENAME),	"NETDEV_CHANGENAME"	पूर्ण)

बाह्य अचिन्हित दीर्घ sysctl_tipc_sk_filter[5] __पढ़ो_mostly;

पूर्णांक tipc_skb_dump(काष्ठा sk_buff *skb, bool more, अक्षर *buf);
पूर्णांक tipc_list_dump(काष्ठा sk_buff_head *list, bool more, अक्षर *buf);
पूर्णांक tipc_sk_dump(काष्ठा sock *sk, u16 dqueues, अक्षर *buf);
पूर्णांक tipc_link_dump(काष्ठा tipc_link *l, u16 dqueues, अक्षर *buf);
पूर्णांक tipc_node_dump(काष्ठा tipc_node *n, bool more, अक्षर *buf);
bool tipc_sk_filtering(काष्ठा sock *sk);

DECLARE_EVENT_CLASS(tipc_skb_class,

	TP_PROTO(काष्ठा sk_buff *skb, bool more, स्थिर अक्षर *header),

	TP_ARGS(skb, more, header),

	TP_STRUCT__entry(
		__string(header, header)
		__dynamic_array(अक्षर, buf, (more) ? SKB_LMAX : SKB_LMIN)
	),

	TP_fast_assign(
		__assign_str(header, header);
		tipc_skb_dump(skb, more, __get_str(buf));
	),

	TP_prपूर्णांकk("%s\n%s", __get_str(header), __get_str(buf))
)

#घोषणा DEFINE_SKB_EVENT(name) \
DEFINE_EVENT(tipc_skb_class, name, \
	TP_PROTO(काष्ठा sk_buff *skb, bool more, स्थिर अक्षर *header), \
	TP_ARGS(skb, more, header))
DEFINE_SKB_EVENT(tipc_skb_dump);
DEFINE_SKB_EVENT(tipc_proto_build);
DEFINE_SKB_EVENT(tipc_proto_rcv);

DECLARE_EVENT_CLASS(tipc_list_class,

	TP_PROTO(काष्ठा sk_buff_head *list, bool more, स्थिर अक्षर *header),

	TP_ARGS(list, more, header),

	TP_STRUCT__entry(
		__string(header, header)
		__dynamic_array(अक्षर, buf, (more) ? LIST_LMAX : LIST_LMIN)
	),

	TP_fast_assign(
		__assign_str(header, header);
		tipc_list_dump(list, more, __get_str(buf));
	),

	TP_prपूर्णांकk("%s\n%s", __get_str(header), __get_str(buf))
);

#घोषणा DEFINE_LIST_EVENT(name) \
DEFINE_EVENT(tipc_list_class, name, \
	TP_PROTO(काष्ठा sk_buff_head *list, bool more, स्थिर अक्षर *header), \
	TP_ARGS(list, more, header))
DEFINE_LIST_EVENT(tipc_list_dump);

DECLARE_EVENT_CLASS(tipc_sk_class,

	TP_PROTO(काष्ठा sock *sk, काष्ठा sk_buff *skb, u16 dqueues,
		 स्थिर अक्षर *header),

	TP_ARGS(sk, skb, dqueues, header),

	TP_STRUCT__entry(
		__string(header, header)
		__field(u32, portid)
		__dynamic_array(अक्षर, buf, (dqueues) ? SK_LMAX : SK_LMIN)
		__dynamic_array(अक्षर, skb_buf, (skb) ? SKB_LMIN : 1)
	),

	TP_fast_assign(
		__assign_str(header, header);
		__entry->portid = tipc_sock_get_portid(sk);
		tipc_sk_dump(sk, dqueues, __get_str(buf));
		अगर (skb)
			tipc_skb_dump(skb, false, __get_str(skb_buf));
		अन्यथा
			*(__get_str(skb_buf)) = '\0';
	),

	TP_prपूर्णांकk("<%u> %s\n%s%s", __entry->portid, __get_str(header),
		  __get_str(skb_buf), __get_str(buf))
);

#घोषणा DEFINE_SK_EVENT_FILTER(name) \
DEFINE_EVENT_CONDITION(tipc_sk_class, name, \
	TP_PROTO(काष्ठा sock *sk, काष्ठा sk_buff *skb, u16 dqueues, \
		 स्थिर अक्षर *header), \
	TP_ARGS(sk, skb, dqueues, header), \
	TP_CONDITION(tipc_sk_filtering(sk)))
DEFINE_SK_EVENT_FILTER(tipc_sk_dump);
DEFINE_SK_EVENT_FILTER(tipc_sk_create);
DEFINE_SK_EVENT_FILTER(tipc_sk_sendmcast);
DEFINE_SK_EVENT_FILTER(tipc_sk_sendmsg);
DEFINE_SK_EVENT_FILTER(tipc_sk_sendstream);
DEFINE_SK_EVENT_FILTER(tipc_sk_poll);
DEFINE_SK_EVENT_FILTER(tipc_sk_filter_rcv);
DEFINE_SK_EVENT_FILTER(tipc_sk_advance_rx);
DEFINE_SK_EVENT_FILTER(tipc_sk_rej_msg);
DEFINE_SK_EVENT_FILTER(tipc_sk_drop_msg);
DEFINE_SK_EVENT_FILTER(tipc_sk_release);
DEFINE_SK_EVENT_FILTER(tipc_sk_shutकरोwn);

#घोषणा DEFINE_SK_EVENT_FILTER_COND(name, cond) \
DEFINE_EVENT_CONDITION(tipc_sk_class, name, \
	TP_PROTO(काष्ठा sock *sk, काष्ठा sk_buff *skb, u16 dqueues, \
		 स्थिर अक्षर *header), \
	TP_ARGS(sk, skb, dqueues, header), \
	TP_CONDITION(tipc_sk_filtering(sk) && (cond)))
DEFINE_SK_EVENT_FILTER_COND(tipc_sk_overlimit1, tipc_sk_overlimit1(sk, skb));
DEFINE_SK_EVENT_FILTER_COND(tipc_sk_overlimit2, tipc_sk_overlimit2(sk, skb));

DECLARE_EVENT_CLASS(tipc_link_class,

	TP_PROTO(काष्ठा tipc_link *l, u16 dqueues, स्थिर अक्षर *header),

	TP_ARGS(l, dqueues, header),

	TP_STRUCT__entry(
		__string(header, header)
		__array(अक्षर, name, TIPC_MAX_LINK_NAME)
		__dynamic_array(अक्षर, buf, (dqueues) ? LINK_LMAX : LINK_LMIN)
	),

	TP_fast_assign(
		__assign_str(header, header);
		स_नकल(__entry->name, tipc_link_name(l), TIPC_MAX_LINK_NAME);
		tipc_link_dump(l, dqueues, __get_str(buf));
	),

	TP_prपूर्णांकk("<%s> %s\n%s", __entry->name, __get_str(header),
		  __get_str(buf))
);

#घोषणा DEFINE_LINK_EVENT(name) \
DEFINE_EVENT(tipc_link_class, name, \
	TP_PROTO(काष्ठा tipc_link *l, u16 dqueues, स्थिर अक्षर *header), \
	TP_ARGS(l, dqueues, header))
DEFINE_LINK_EVENT(tipc_link_dump);
DEFINE_LINK_EVENT(tipc_link_conges);
DEFINE_LINK_EVENT(tipc_link_समयout);
DEFINE_LINK_EVENT(tipc_link_reset);

#घोषणा DEFINE_LINK_EVENT_COND(name, cond) \
DEFINE_EVENT_CONDITION(tipc_link_class, name, \
	TP_PROTO(काष्ठा tipc_link *l, u16 dqueues, स्थिर अक्षर *header), \
	TP_ARGS(l, dqueues, header), \
	TP_CONDITION(cond))
DEFINE_LINK_EVENT_COND(tipc_link_too_silent, tipc_link_too_silent(l));

DECLARE_EVENT_CLASS(tipc_link_transmq_class,

	TP_PROTO(काष्ठा tipc_link *r, u16 f, u16 t, काष्ठा sk_buff_head *tq),

	TP_ARGS(r, f, t, tq),

	TP_STRUCT__entry(
		__array(अक्षर, name, TIPC_MAX_LINK_NAME)
		__field(u16, from)
		__field(u16, to)
		__field(u32, len)
		__field(u16, fseqno)
		__field(u16, lseqno)
	),

	TP_fast_assign(
		स_नकल(__entry->name, tipc_link_name(r), TIPC_MAX_LINK_NAME);
		__entry->from = f;
		__entry->to = t;
		__entry->len = skb_queue_len(tq);
		__entry->fseqno = __entry->len ?
				  msg_seqno(buf_msg(skb_peek(tq))) : 0;
		__entry->lseqno = __entry->len ?
				  msg_seqno(buf_msg(skb_peek_tail(tq))) : 0;
	),

	TP_prपूर्णांकk("<%s> retrans req: [%u-%u] transmq: %u [%u-%u]\n",
		  __entry->name, __entry->from, __entry->to,
		  __entry->len, __entry->fseqno, __entry->lseqno)
);

DEFINE_EVENT_CONDITION(tipc_link_transmq_class, tipc_link_retrans,
	TP_PROTO(काष्ठा tipc_link *r, u16 f, u16 t, काष्ठा sk_buff_head *tq),
	TP_ARGS(r, f, t, tq),
	TP_CONDITION(less_eq(f, t))
);

DEFINE_EVENT_PRINT(tipc_link_transmq_class, tipc_link_bc_ack,
	TP_PROTO(काष्ठा tipc_link *r, u16 f, u16 t, काष्ठा sk_buff_head *tq),
	TP_ARGS(r, f, t, tq),
	TP_prपूर्णांकk("<%s> acked: %u gap: %u transmq: %u [%u-%u]\n",
		  __entry->name, __entry->from, __entry->to,
		  __entry->len, __entry->fseqno, __entry->lseqno)
);

DECLARE_EVENT_CLASS(tipc_node_class,

	TP_PROTO(काष्ठा tipc_node *n, bool more, स्थिर अक्षर *header),

	TP_ARGS(n, more, header),

	TP_STRUCT__entry(
		__string(header, header)
		__field(u32, addr)
		__dynamic_array(अक्षर, buf, (more) ? NODE_LMAX : NODE_LMIN)
	),

	TP_fast_assign(
		__assign_str(header, header);
		__entry->addr = tipc_node_get_addr(n);
		tipc_node_dump(n, more, __get_str(buf));
	),

	TP_prपूर्णांकk("<%x> %s\n%s", __entry->addr, __get_str(header),
		  __get_str(buf))
);

#घोषणा DEFINE_NODE_EVENT(name) \
DEFINE_EVENT(tipc_node_class, name, \
	TP_PROTO(काष्ठा tipc_node *n, bool more, स्थिर अक्षर *header), \
	TP_ARGS(n, more, header))
DEFINE_NODE_EVENT(tipc_node_dump);
DEFINE_NODE_EVENT(tipc_node_create);
DEFINE_NODE_EVENT(tipc_node_delete);
DEFINE_NODE_EVENT(tipc_node_lost_contact);
DEFINE_NODE_EVENT(tipc_node_समयout);
DEFINE_NODE_EVENT(tipc_node_link_up);
DEFINE_NODE_EVENT(tipc_node_link_करोwn);
DEFINE_NODE_EVENT(tipc_node_reset_links);
DEFINE_NODE_EVENT(tipc_node_check_state);

DECLARE_EVENT_CLASS(tipc_fsm_class,

	TP_PROTO(स्थिर अक्षर *name, u32 os, u32 ns, पूर्णांक evt),

	TP_ARGS(name, os, ns, evt),

	TP_STRUCT__entry(
		__string(name, name)
		__field(u32, os)
		__field(u32, ns)
		__field(u32, evt)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->os = os;
		__entry->ns = ns;
		__entry->evt = evt;
	),

	TP_prपूर्णांकk("<%s> %s--(%s)->%s\n", __get_str(name),
		  state_sym(__entry->os), evt_sym(__entry->evt),
		  state_sym(__entry->ns))
);

#घोषणा DEFINE_FSM_EVENT(fsm_name) \
DEFINE_EVENT(tipc_fsm_class, fsm_name, \
	TP_PROTO(स्थिर अक्षर *name, u32 os, u32 ns, पूर्णांक evt), \
	TP_ARGS(name, os, ns, evt))
DEFINE_FSM_EVENT(tipc_link_fsm);
DEFINE_FSM_EVENT(tipc_node_fsm);

TRACE_EVENT(tipc_l2_device_event,

	TP_PROTO(काष्ठा net_device *dev, काष्ठा tipc_bearer *b,
		 अचिन्हित दीर्घ evt),

	TP_ARGS(dev, b, evt),

	TP_STRUCT__entry(
		__string(dev_name, dev->name)
		__string(b_name, b->name)
		__field(अचिन्हित दीर्घ, evt)
		__field(u8, b_up)
		__field(u8, carrier)
		__field(u8, oper)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev->name);
		__assign_str(b_name, b->name);
		__entry->evt = evt;
		__entry->b_up = test_bit(0, &b->up);
		__entry->carrier = netअगर_carrier_ok(dev);
		__entry->oper = netअगर_oper_up(dev);
	),

	TP_prपूर्णांकk("%s on: <%s>/<%s> oper: %s carrier: %s bearer: %s\n",
		  dev_evt_sym(__entry->evt), __get_str(dev_name),
		  __get_str(b_name), (__entry->oper) ? "up" : "down",
		  (__entry->carrier) ? "ok" : "notok",
		  (__entry->b_up) ? "up" : "down")
);

#पूर्ण_अगर /* _TIPC_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace
#समावेश <trace/define_trace.h>
