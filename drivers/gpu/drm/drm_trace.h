<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_DRM_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _DRM_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा drm_file;

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM drm
#घोषणा TRACE_INCLUDE_खाता drm_trace

TRACE_EVENT(drm_vblank_event,
	    TP_PROTO(पूर्णांक crtc, अचिन्हित पूर्णांक seq, kसमय_प्रकार समय, bool high_prec),
	    TP_ARGS(crtc, seq, समय, high_prec),
	    TP_STRUCT__entry(
		    __field(पूर्णांक, crtc)
		    __field(अचिन्हित पूर्णांक, seq)
		    __field(kसमय_प्रकार, समय)
		    __field(bool, high_prec)
		    ),
	    TP_fast_assign(
		    __entry->crtc = crtc;
		    __entry->seq = seq;
		    __entry->समय = समय;
		    __entry->high_prec = high_prec;
			),
	    TP_prपूर्णांकk("crtc=%d, seq=%u, time=%lld, high-prec=%s",
			__entry->crtc, __entry->seq, __entry->समय,
			__entry->high_prec ? "true" : "false")
);

TRACE_EVENT(drm_vblank_event_queued,
	    TP_PROTO(काष्ठा drm_file *file, पूर्णांक crtc, अचिन्हित पूर्णांक seq),
	    TP_ARGS(file, crtc, seq),
	    TP_STRUCT__entry(
		    __field(काष्ठा drm_file *, file)
		    __field(पूर्णांक, crtc)
		    __field(अचिन्हित पूर्णांक, seq)
		    ),
	    TP_fast_assign(
		    __entry->file = file;
		    __entry->crtc = crtc;
		    __entry->seq = seq;
		    ),
	    TP_prपूर्णांकk("file=%p, crtc=%d, seq=%u", __entry->file, __entry->crtc, \
		      __entry->seq)
);

TRACE_EVENT(drm_vblank_event_delivered,
	    TP_PROTO(काष्ठा drm_file *file, पूर्णांक crtc, अचिन्हित पूर्णांक seq),
	    TP_ARGS(file, crtc, seq),
	    TP_STRUCT__entry(
		    __field(काष्ठा drm_file *, file)
		    __field(पूर्णांक, crtc)
		    __field(अचिन्हित पूर्णांक, seq)
		    ),
	    TP_fast_assign(
		    __entry->file = file;
		    __entry->crtc = crtc;
		    __entry->seq = seq;
		    ),
	    TP_prपूर्णांकk("file=%p, crtc=%d, seq=%u", __entry->file, __entry->crtc, \
		      __entry->seq)
);

#पूर्ण_अगर /* _DRM_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm
#समावेश <trace/define_trace.h>
