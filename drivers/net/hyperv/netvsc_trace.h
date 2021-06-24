<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर !defined(_NETVSC_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _NETVSC_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM netvsc
#घोषणा TRACE_INCLUDE_खाता netvsc_trace

TRACE_DEFINE_ENUM(RNDIS_MSG_PACKET);
TRACE_DEFINE_ENUM(RNDIS_MSG_INDICATE);
TRACE_DEFINE_ENUM(RNDIS_MSG_INIT);
TRACE_DEFINE_ENUM(RNDIS_MSG_INIT_C);
TRACE_DEFINE_ENUM(RNDIS_MSG_HALT);
TRACE_DEFINE_ENUM(RNDIS_MSG_QUERY);
TRACE_DEFINE_ENUM(RNDIS_MSG_QUERY_C);
TRACE_DEFINE_ENUM(RNDIS_MSG_SET);
TRACE_DEFINE_ENUM(RNDIS_MSG_SET_C);
TRACE_DEFINE_ENUM(RNDIS_MSG_RESET);
TRACE_DEFINE_ENUM(RNDIS_MSG_RESET_C);
TRACE_DEFINE_ENUM(RNDIS_MSG_KEEPALIVE);
TRACE_DEFINE_ENUM(RNDIS_MSG_KEEPALIVE_C);

#घोषणा show_rndis_type(type)					\
	__prपूर्णांक_symbolic(type,					\
		 अणु RNDIS_MSG_PACKET,	  "PACKET" पूर्ण,		\
		 अणु RNDIS_MSG_INDICATE,	  "INDICATE", पूर्ण,	\
		 अणु RNDIS_MSG_INIT,	  "INIT", पूर्ण,		\
		 अणु RNDIS_MSG_INIT_C,	  "INIT_C", पूर्ण,		\
		 अणु RNDIS_MSG_HALT,	  "HALT", पूर्ण,		\
		 अणु RNDIS_MSG_QUERY,	  "QUERY", पूर्ण,		\
		 अणु RNDIS_MSG_QUERY_C,	  "QUERY_C", पूर्ण,		\
		 अणु RNDIS_MSG_SET,	  "SET", पूर्ण,		\
		 अणु RNDIS_MSG_SET_C,	  "SET_C", पूर्ण,		\
		 अणु RNDIS_MSG_RESET,	  "RESET", पूर्ण,		\
		 अणु RNDIS_MSG_RESET_C,	  "RESET_C", पूर्ण,		\
		 अणु RNDIS_MSG_KEEPALIVE,	  "KEEPALIVE", पूर्ण,	\
		 अणु RNDIS_MSG_KEEPALIVE_C, "KEEPALIVE_C", पूर्ण)

DECLARE_EVENT_CLASS(rndis_msg_class,
       TP_PROTO(स्थिर काष्ठा net_device *ndev, u16 q,
		स्थिर काष्ठा rndis_message *msg),
       TP_ARGS(ndev, q, msg),
       TP_STRUCT__entry(
	       __string( name, ndev->name  )
	       __field(	 u16,  queue	   )
	       __field(	 u32,  req_id	   )
	       __field(	 u32,  msg_type	   )
	       __field(	 u32,  msg_len	   )
       ),
       TP_fast_assign(
	       __assign_str(name, ndev->name);
	       __entry->queue	 = q;
	       __entry->req_id	 = msg->msg.init_req.req_id;
	       __entry->msg_type = msg->ndis_msg_type;
	       __entry->msg_len	 = msg->msg_len;
       ),
       TP_prपूर्णांकk("dev=%s q=%u req=%#x type=%s msg_len=%u",
		 __get_str(name), __entry->queue, __entry->req_id,
		 show_rndis_type(__entry->msg_type), __entry->msg_len)
);

DEFINE_EVENT(rndis_msg_class, rndis_send,
       TP_PROTO(स्थिर काष्ठा net_device *ndev, u16 q,
		स्थिर काष्ठा rndis_message *msg),
       TP_ARGS(ndev, q, msg)
);

DEFINE_EVENT(rndis_msg_class, rndis_recv,
       TP_PROTO(स्थिर काष्ठा net_device *ndev, u16 q,
		स्थिर काष्ठा rndis_message *msg),
       TP_ARGS(ndev, q, msg)
);

TRACE_DEFINE_ENUM(NVSP_MSG_TYPE_INIT);
TRACE_DEFINE_ENUM(NVSP_MSG_TYPE_INIT_COMPLETE);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_NDIS_VER);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_RECV_BUF);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_REVOKE_RECV_BUF);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_SEND_BUF);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_REVOKE_SEND_BUF);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_RNDIS_PKT);
TRACE_DEFINE_ENUM(NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE);
TRACE_DEFINE_ENUM(NVSP_MSG2_TYPE_SEND_NDIS_CONFIG);

TRACE_DEFINE_ENUM(NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION);
TRACE_DEFINE_ENUM(NVSP_MSG4_TYPE_SWITCH_DATA_PATH);

TRACE_DEFINE_ENUM(NVSP_MSG5_TYPE_SUBCHANNEL);
TRACE_DEFINE_ENUM(NVSP_MSG5_TYPE_SEND_INसूचीECTION_TABLE);

#घोषणा show_nvsp_type(type)								\
	__prपूर्णांक_symbolic(type,								\
		  अणु NVSP_MSG_TYPE_INIT,			   "INIT" पूर्ण,			\
		  अणु NVSP_MSG_TYPE_INIT_COMPLETE,	   "INIT_COMPLETE" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_NDIS_VER,	   "SEND_NDIS_VER" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_RECV_BUF,	   "SEND_RECV_BUF" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_RECV_BUF_COMPLETE, "SEND_RECV_BUF_COMPLETE" पूर्ण,	\
		  अणु NVSP_MSG1_TYPE_REVOKE_RECV_BUF,	   "REVOKE_RECV_BUF" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_SEND_BUF,	   "SEND_SEND_BUF" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE, "SEND_SEND_BUF_COMPLETE" पूर्ण,	\
		  अणु NVSP_MSG1_TYPE_REVOKE_SEND_BUF,	   "REVOKE_SEND_BUF" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_RNDIS_PKT,	   "SEND_RNDIS_PKT" पूर्ण,		\
		  अणु NVSP_MSG1_TYPE_SEND_RNDIS_PKT_COMPLETE, "SEND_RNDIS_PKT_COMPLETE" पूर्ण,\
		  अणु NVSP_MSG2_TYPE_SEND_NDIS_CONFIG,	   "SEND_NDIS_CONFIG" पूर्ण,	\
		  अणु NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION,	   "SEND_VF_ASSOCIATION" पूर्ण,	\
		  अणु NVSP_MSG4_TYPE_SWITCH_DATA_PATH,	   "SWITCH_DATA_PATH" पूर्ण,	\
		  अणु NVSP_MSG5_TYPE_SUBCHANNEL,		    "SUBCHANNEL" पूर्ण,		\
		  अणु NVSP_MSG5_TYPE_SEND_INसूचीECTION_TABLE,  "SEND_INDIRECTION_TABLE" पूर्ण)

TRACE_EVENT(nvsp_send,
	TP_PROTO(स्थिर काष्ठा net_device *ndev,
		 स्थिर काष्ठा nvsp_message *msg),
	TP_ARGS(ndev, msg),
	TP_STRUCT__entry(
		__string( name,	ndev->name  )
		__field(  u32,	msg_type    )
	),
	TP_fast_assign(
		__assign_str(name, ndev->name);
		__entry->msg_type = msg->hdr.msg_type;
	),
	TP_prपूर्णांकk("dev=%s type=%s",
		  __get_str(name),
		  show_nvsp_type(__entry->msg_type))
);

TRACE_EVENT(nvsp_send_pkt,
	TP_PROTO(स्थिर काष्ठा net_device *ndev,
		 स्थिर काष्ठा vmbus_channel *chan,
		 स्थिर काष्ठा nvsp_1_message_send_rndis_packet *rpkt),
	TP_ARGS(ndev, chan, rpkt),
	TP_STRUCT__entry(
		__string( name,	ndev->name    )
		__field(  u16,	qid	      )
		__field(  u32,	channel_type  )
		__field(  u32,	section_index )
		__field(  u32,	section_size  )
	),
	TP_fast_assign(
		__assign_str(name, ndev->name);
		__entry->qid = chan->offermsg.offer.sub_channel_index;
		__entry->channel_type = rpkt->channel_type;
		__entry->section_index = rpkt->send_buf_section_index;
		__entry->section_size = rpkt->send_buf_section_size;
	),
	TP_prपूर्णांकk("dev=%s qid=%u type=%s section=%u size=%d",
		  __get_str(name), __entry->qid,
		  __entry->channel_type ? "CONTROL" : "DATA",
		  __entry->section_index, __entry->section_size)
);

TRACE_EVENT(nvsp_recv,
	TP_PROTO(स्थिर काष्ठा net_device *ndev,
		 स्थिर काष्ठा vmbus_channel *chan,
		 स्थिर काष्ठा nvsp_message *msg),
	TP_ARGS(ndev, chan, msg),
	TP_STRUCT__entry(
		__string( name,	ndev->name  )
		__field(  u16,	qid	    )
		__field(  u32,	msg_type    )
	),
	TP_fast_assign(
		__assign_str(name, ndev->name);
		__entry->qid = chan->offermsg.offer.sub_channel_index;
		__entry->msg_type = msg->hdr.msg_type;
	),
	TP_prपूर्णांकk("dev=%s qid=%u type=%s",
		  __get_str(name), __entry->qid,
		  show_nvsp_type(__entry->msg_type))
);

#पूर्ण_अगर /* _NETVSC_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/net/hyperv
#समावेश <trace/define_trace.h>
