<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(ARMADA_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा ARMADA_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा drm_crtc;
काष्ठा drm_framebuffer;
काष्ठा drm_plane;

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM armada
#घोषणा TRACE_INCLUDE_खाता armada_trace

TRACE_EVENT(armada_drm_irq,
	TP_PROTO(काष्ठा drm_crtc *crtc, u32 stat),
	TP_ARGS(crtc, stat),
	TP_STRUCT__entry(
		__field(काष्ठा drm_crtc *, crtc)
		__field(u32, stat)
	),
	TP_fast_assign(
		__entry->crtc = crtc;
		__entry->stat = stat;
	),
	TP_prपूर्णांकk("crtc %p stat 0x%08x",
		__entry->crtc, __entry->stat)
);

TRACE_EVENT(armada_ovl_plane_update,
	TP_PROTO(काष्ठा drm_plane *plane, काष्ठा drm_crtc *crtc,
		     काष्ठा drm_framebuffer *fb,
		     पूर्णांक crtc_x, पूर्णांक crtc_y, अचिन्हित crtc_w, अचिन्हित crtc_h,
		     uपूर्णांक32_t src_x, uपूर्णांक32_t src_y, uपूर्णांक32_t src_w, uपूर्णांक32_t src_h),
	TP_ARGS(plane, crtc, fb, crtc_x, crtc_y, crtc_w, crtc_h, src_x, src_y, src_w, src_h),
	TP_STRUCT__entry(
		__field(काष्ठा drm_plane *, plane)
		__field(काष्ठा drm_crtc *, crtc)
		__field(काष्ठा drm_framebuffer *, fb)
		__field(पूर्णांक, crtc_x)
		__field(पूर्णांक, crtc_y)
		__field(अचिन्हित पूर्णांक, crtc_w)
		__field(अचिन्हित पूर्णांक, crtc_h)
		__field(u32, src_x)
		__field(u32, src_y)
		__field(u32, src_w)
		__field(u32, src_h)
	),
	TP_fast_assign(
		__entry->plane = plane;
		__entry->crtc = crtc;
		__entry->fb = fb;
		__entry->crtc_x = crtc_x;
		__entry->crtc_y = crtc_y;
		__entry->crtc_w = crtc_w;
		__entry->crtc_h = crtc_h;
		__entry->src_x = src_x;
		__entry->src_y = src_y;
		__entry->src_w = src_w;
		__entry->src_h = src_h;
	),
	TP_prपूर्णांकk("plane %p crtc %p fb %p crtc @ (%d,%d, %ux%u) src @ (%u,%u, %ux%u)",
		__entry->plane, __entry->crtc, __entry->fb,
		__entry->crtc_x, __entry->crtc_y,
		__entry->crtc_w, __entry->crtc_h,
		__entry->src_x >> 16, __entry->src_y >> 16,
		__entry->src_w >> 16, __entry->src_h >> 16)
);

TRACE_EVENT(armada_ovl_plane_work,
	TP_PROTO(काष्ठा drm_crtc *crtc, काष्ठा drm_plane *plane),
	TP_ARGS(crtc, plane),
	TP_STRUCT__entry(
		__field(काष्ठा drm_plane *, plane)
		__field(काष्ठा drm_crtc *, crtc)
	),
	TP_fast_assign(
		__entry->plane = plane;
		__entry->crtc = crtc;
	),
	TP_prपूर्णांकk("plane %p crtc %p",
		__entry->plane, __entry->crtc)
);

#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/armada
#समावेश <trace/define_trace.h>
