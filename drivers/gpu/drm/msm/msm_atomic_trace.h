<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_MSM_GPU_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MSM_GPU_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM drm_msm_atomic
#घोषणा TRACE_INCLUDE_खाता msm_atomic_trace

TRACE_EVENT(msm_atomic_commit_tail_start,
	    TP_PROTO(bool async, अचिन्हित crtc_mask),
	    TP_ARGS(async, crtc_mask),
	    TP_STRUCT__entry(
		    __field(bool, async)
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->async = async;
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("async=%d crtc_mask=%x",
		    __entry->async, __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_commit_tail_finish,
	    TP_PROTO(bool async, अचिन्हित crtc_mask),
	    TP_ARGS(async, crtc_mask),
	    TP_STRUCT__entry(
		    __field(bool, async)
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->async = async;
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("async=%d crtc_mask=%x",
		    __entry->async, __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_async_commit_start,
	    TP_PROTO(अचिन्हित crtc_mask),
	    TP_ARGS(crtc_mask),
	    TP_STRUCT__entry(
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("crtc_mask=%x",
		    __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_async_commit_finish,
	    TP_PROTO(अचिन्हित crtc_mask),
	    TP_ARGS(crtc_mask),
	    TP_STRUCT__entry(
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("crtc_mask=%x",
		    __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_रुको_flush_start,
	    TP_PROTO(अचिन्हित crtc_mask),
	    TP_ARGS(crtc_mask),
	    TP_STRUCT__entry(
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("crtc_mask=%x",
		    __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_रुको_flush_finish,
	    TP_PROTO(अचिन्हित crtc_mask),
	    TP_ARGS(crtc_mask),
	    TP_STRUCT__entry(
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("crtc_mask=%x",
		    __entry->crtc_mask)
);

TRACE_EVENT(msm_atomic_flush_commit,
	    TP_PROTO(अचिन्हित crtc_mask),
	    TP_ARGS(crtc_mask),
	    TP_STRUCT__entry(
		    __field(u32, crtc_mask)
		    ),
	    TP_fast_assign(
		    __entry->crtc_mask = crtc_mask;
		    ),
	    TP_prपूर्णांकk("crtc_mask=%x",
		    __entry->crtc_mask)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/msm
#समावेश <trace/define_trace.h>
