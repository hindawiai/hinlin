<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nbd

#अगर !defined(_TRACE_NBD_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NBD_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(nbd_transport_event,

	TP_PROTO(काष्ठा request *req, u64 handle),

	TP_ARGS(req, handle),

	TP_STRUCT__entry(
		__field(काष्ठा request *, req)
		__field(u64, handle)
	),

	TP_fast_assign(
		__entry->req = req;
		__entry->handle = handle;
	),

	TP_prपूर्णांकk(
		"nbd transport event: request %p, handle 0x%016llx",
		__entry->req,
		__entry->handle
	)
);

DEFINE_EVENT(nbd_transport_event, nbd_header_sent,

	TP_PROTO(काष्ठा request *req, u64 handle),

	TP_ARGS(req, handle)
);

DEFINE_EVENT(nbd_transport_event, nbd_payload_sent,

	TP_PROTO(काष्ठा request *req, u64 handle),

	TP_ARGS(req, handle)
);

DEFINE_EVENT(nbd_transport_event, nbd_header_received,

	TP_PROTO(काष्ठा request *req, u64 handle),

	TP_ARGS(req, handle)
);

DEFINE_EVENT(nbd_transport_event, nbd_payload_received,

	TP_PROTO(काष्ठा request *req, u64 handle),

	TP_ARGS(req, handle)
);

DECLARE_EVENT_CLASS(nbd_send_request,

	TP_PROTO(काष्ठा nbd_request *nbd_request, पूर्णांक index,
		 काष्ठा request *rq),

	TP_ARGS(nbd_request, index, rq),

	TP_STRUCT__entry(
		__field(काष्ठा nbd_request *, nbd_request)
		__field(u64, dev_index)
		__field(काष्ठा request *, request)
	),

	TP_fast_assign(
		__entry->nbd_request = 0;
		__entry->dev_index = index;
		__entry->request = rq;
	),

	TP_prपूर्णांकk("nbd%lld: request %p", __entry->dev_index, __entry->request)
);

#अगर_घोषित DEFINE_EVENT_WRITABLE
#अघोषित NBD_DEFINE_EVENT
#घोषणा NBD_DEFINE_EVENT(ढाँचा, call, proto, args, size)		\
	DEFINE_EVENT_WRITABLE(ढाँचा, call, PARAMS(proto),		\
			      PARAMS(args), size)
#अन्यथा
#अघोषित NBD_DEFINE_EVENT
#घोषणा NBD_DEFINE_EVENT(ढाँचा, call, proto, args, size)		\
	DEFINE_EVENT(ढाँचा, call, PARAMS(proto), PARAMS(args))
#पूर्ण_अगर

NBD_DEFINE_EVENT(nbd_send_request, nbd_send_request,

	TP_PROTO(काष्ठा nbd_request *nbd_request, पूर्णांक index,
		 काष्ठा request *rq),

	TP_ARGS(nbd_request, index, rq),

	माप(काष्ठा nbd_request)
);

#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
