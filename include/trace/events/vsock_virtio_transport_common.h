<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vsock

#अगर !defined(_TRACE_VSOCK_VIRTIO_TRANSPORT_COMMON_H) || \
    defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_VSOCK_VIRTIO_TRANSPORT_COMMON_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(VIRTIO_VSOCK_TYPE_STREAM);

#घोषणा show_type(val) \
	__prपूर्णांक_symbolic(val, अणु VIRTIO_VSOCK_TYPE_STREAM, "STREAM" पूर्ण)

TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_INVALID);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_REQUEST);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_RESPONSE);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_RST);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_SHUTDOWN);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_RW);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_CREDIT_UPDATE);
TRACE_DEFINE_ENUM(VIRTIO_VSOCK_OP_CREDIT_REQUEST);

#घोषणा show_op(val) \
	__prपूर्णांक_symbolic(val, \
			 अणु VIRTIO_VSOCK_OP_INVALID, "INVALID" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_REQUEST, "REQUEST" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_RESPONSE, "RESPONSE" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_RST, "RST" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_SHUTDOWN, "SHUTDOWN" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_RW, "RW" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_CREDIT_UPDATE, "CREDIT_UPDATE" पूर्ण, \
			 अणु VIRTIO_VSOCK_OP_CREDIT_REQUEST, "CREDIT_REQUEST" पूर्ण)

TRACE_EVENT(virtio_transport_alloc_pkt,
	TP_PROTO(
		 __u32 src_cid, __u32 src_port,
		 __u32 dst_cid, __u32 dst_port,
		 __u32 len,
		 __u16 type,
		 __u16 op,
		 __u32 flags
	),
	TP_ARGS(
		src_cid, src_port,
		dst_cid, dst_port,
		len,
		type,
		op,
		flags
	),
	TP_STRUCT__entry(
		__field(__u32, src_cid)
		__field(__u32, src_port)
		__field(__u32, dst_cid)
		__field(__u32, dst_port)
		__field(__u32, len)
		__field(__u16, type)
		__field(__u16, op)
		__field(__u32, flags)
	),
	TP_fast_assign(
		__entry->src_cid = src_cid;
		__entry->src_port = src_port;
		__entry->dst_cid = dst_cid;
		__entry->dst_port = dst_port;
		__entry->len = len;
		__entry->type = type;
		__entry->op = op;
		__entry->flags = flags;
	),
	TP_prपूर्णांकk("%u:%u -> %u:%u len=%u type=%s op=%s flags=%#x",
		  __entry->src_cid, __entry->src_port,
		  __entry->dst_cid, __entry->dst_port,
		  __entry->len,
		  show_type(__entry->type),
		  show_op(__entry->op),
		  __entry->flags)
);

TRACE_EVENT(virtio_transport_recv_pkt,
	TP_PROTO(
		 __u32 src_cid, __u32 src_port,
		 __u32 dst_cid, __u32 dst_port,
		 __u32 len,
		 __u16 type,
		 __u16 op,
		 __u32 flags,
		 __u32 buf_alloc,
		 __u32 fwd_cnt
	),
	TP_ARGS(
		src_cid, src_port,
		dst_cid, dst_port,
		len,
		type,
		op,
		flags,
		buf_alloc,
		fwd_cnt
	),
	TP_STRUCT__entry(
		__field(__u32, src_cid)
		__field(__u32, src_port)
		__field(__u32, dst_cid)
		__field(__u32, dst_port)
		__field(__u32, len)
		__field(__u16, type)
		__field(__u16, op)
		__field(__u32, flags)
		__field(__u32, buf_alloc)
		__field(__u32, fwd_cnt)
	),
	TP_fast_assign(
		__entry->src_cid = src_cid;
		__entry->src_port = src_port;
		__entry->dst_cid = dst_cid;
		__entry->dst_port = dst_port;
		__entry->len = len;
		__entry->type = type;
		__entry->op = op;
		__entry->flags = flags;
		__entry->buf_alloc = buf_alloc;
		__entry->fwd_cnt = fwd_cnt;
	),
	TP_prपूर्णांकk("%u:%u -> %u:%u len=%u type=%s op=%s flags=%#x "
		  "buf_alloc=%u fwd_cnt=%u",
		  __entry->src_cid, __entry->src_port,
		  __entry->dst_cid, __entry->dst_port,
		  __entry->len,
		  show_type(__entry->type),
		  show_op(__entry->op),
		  __entry->flags,
		  __entry->buf_alloc,
		  __entry->fwd_cnt)
);

#पूर्ण_अगर /* _TRACE_VSOCK_VIRTIO_TRANSPORT_COMMON_H */

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता vsock_virtio_transport_common

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
