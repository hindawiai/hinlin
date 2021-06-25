<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_I915_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _I915_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <drm/drm_drv.h>

#समावेश "display/intel_display_types.h"
#समावेश "gt/intel_engine.h"

#समावेश "i915_drv.h"
#समावेश "i915_irq.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM i915
#घोषणा TRACE_INCLUDE_खाता i915_trace

/* watermark/fअगरo updates */

TRACE_EVENT(पूर्णांकel_pipe_enable,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __array(u32, frame, 3)
			     __array(u32, scanline, 3)
			     __field(क्रमागत pipe, pipe)
			     ),
	    TP_fast_assign(
			   काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
			   काष्ठा पूर्णांकel_crtc *it__;
			   क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, it__) अणु
				   __entry->frame[it__->pipe] = पूर्णांकel_crtc_get_vblank_counter(it__);
				   __entry->scanline[it__->pipe] = पूर्णांकel_get_crtc_scanline(it__);
			   पूर्ण
			   __entry->pipe = crtc->pipe;
			   ),

	    TP_prपूर्णांकk("pipe %c enable, pipe A: frame=%u, scanline=%u, pipe B: frame=%u, scanline=%u, pipe C: frame=%u, scanline=%u",
		      pipe_name(__entry->pipe),
		      __entry->frame[PIPE_A], __entry->scanline[PIPE_A],
		      __entry->frame[PIPE_B], __entry->scanline[PIPE_B],
		      __entry->frame[PIPE_C], __entry->scanline[PIPE_C])
);

TRACE_EVENT(पूर्णांकel_pipe_disable,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __array(u32, frame, 3)
			     __array(u32, scanline, 3)
			     __field(क्रमागत pipe, pipe)
			     ),

	    TP_fast_assign(
			   काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
			   काष्ठा पूर्णांकel_crtc *it__;
			   क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, it__) अणु
				   __entry->frame[it__->pipe] = पूर्णांकel_crtc_get_vblank_counter(it__);
				   __entry->scanline[it__->pipe] = पूर्णांकel_get_crtc_scanline(it__);
			   पूर्ण
			   __entry->pipe = crtc->pipe;
			   ),

	    TP_prपूर्णांकk("pipe %c disable, pipe A: frame=%u, scanline=%u, pipe B: frame=%u, scanline=%u, pipe C: frame=%u, scanline=%u",
		      pipe_name(__entry->pipe),
		      __entry->frame[PIPE_A], __entry->scanline[PIPE_A],
		      __entry->frame[PIPE_B], __entry->scanline[PIPE_B],
		      __entry->frame[PIPE_C], __entry->scanline[PIPE_C])
);

TRACE_EVENT(पूर्णांकel_pipe_crc,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc, स्थिर u32 *crcs),
	    TP_ARGS(crtc, crcs),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __array(u32, crcs, 5)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   स_नकल(__entry->crcs, crcs, माप(__entry->crcs));
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u crc=%08x %08x %08x %08x %08x",
		      pipe_name(__entry->pipe), __entry->frame, __entry->scanline,
		      __entry->crcs[0], __entry->crcs[1], __entry->crcs[2],
		      __entry->crcs[3], __entry->crcs[4])
);

TRACE_EVENT(पूर्णांकel_cpu_fअगरo_underrun,
	    TP_PROTO(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe),
	    TP_ARGS(dev_priv, pipe),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			    काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
			   __entry->pipe = pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe),
		      __entry->frame, __entry->scanline)
);

TRACE_EVENT(पूर्णांकel_pch_fअगरo_underrun,
	    TP_PROTO(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pch_transcoder),
	    TP_ARGS(dev_priv, pch_transcoder),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			   क्रमागत pipe pipe = pch_transcoder;
			   काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
			   __entry->pipe = pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pch transcoder %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe),
		      __entry->frame, __entry->scanline)
);

TRACE_EVENT(पूर्णांकel_memory_cxsr,
	    TP_PROTO(काष्ठा drm_i915_निजी *dev_priv, bool old, bool new),
	    TP_ARGS(dev_priv, old, new),

	    TP_STRUCT__entry(
			     __array(u32, frame, 3)
			     __array(u32, scanline, 3)
			     __field(bool, old)
			     __field(bool, new)
			     ),

	    TP_fast_assign(
			   काष्ठा पूर्णांकel_crtc *crtc;
			   क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
				   __entry->frame[crtc->pipe] = पूर्णांकel_crtc_get_vblank_counter(crtc);
				   __entry->scanline[crtc->pipe] = पूर्णांकel_get_crtc_scanline(crtc);
			   पूर्ण
			   __entry->old = old;
			   __entry->new = new;
			   ),

	    TP_prपूर्णांकk("%s->%s, pipe A: frame=%u, scanline=%u, pipe B: frame=%u, scanline=%u, pipe C: frame=%u, scanline=%u",
		      onoff(__entry->old), onoff(__entry->new),
		      __entry->frame[PIPE_A], __entry->scanline[PIPE_A],
		      __entry->frame[PIPE_B], __entry->scanline[PIPE_B],
		      __entry->frame[PIPE_C], __entry->scanline[PIPE_C])
);

TRACE_EVENT(g4x_wm,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc, स्थिर काष्ठा g4x_wm_values *wm),
	    TP_ARGS(crtc, wm),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __field(u16, primary)
			     __field(u16, sprite)
			     __field(u16, cursor)
			     __field(u16, sr_plane)
			     __field(u16, sr_cursor)
			     __field(u16, sr_fbc)
			     __field(u16, hpll_plane)
			     __field(u16, hpll_cursor)
			     __field(u16, hpll_fbc)
			     __field(bool, cxsr)
			     __field(bool, hpll)
			     __field(bool, fbc)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   __entry->primary = wm->pipe[crtc->pipe].plane[PLANE_PRIMARY];
			   __entry->sprite = wm->pipe[crtc->pipe].plane[PLANE_SPRITE0];
			   __entry->cursor = wm->pipe[crtc->pipe].plane[PLANE_CURSOR];
			   __entry->sr_plane = wm->sr.plane;
			   __entry->sr_cursor = wm->sr.cursor;
			   __entry->sr_fbc = wm->sr.fbc;
			   __entry->hpll_plane = wm->hpll.plane;
			   __entry->hpll_cursor = wm->hpll.cursor;
			   __entry->hpll_fbc = wm->hpll.fbc;
			   __entry->cxsr = wm->cxsr;
			   __entry->hpll = wm->hpll_en;
			   __entry->fbc = wm->fbc_en;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u, wm %d/%d/%d, sr %s/%d/%d/%d, hpll %s/%d/%d/%d, fbc %s",
		      pipe_name(__entry->pipe), __entry->frame, __entry->scanline,
		      __entry->primary, __entry->sprite, __entry->cursor,
		      yesno(__entry->cxsr), __entry->sr_plane, __entry->sr_cursor, __entry->sr_fbc,
		      yesno(__entry->hpll), __entry->hpll_plane, __entry->hpll_cursor, __entry->hpll_fbc,
		      yesno(__entry->fbc))
);

TRACE_EVENT(vlv_wm,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc, स्थिर काष्ठा vlv_wm_values *wm),
	    TP_ARGS(crtc, wm),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __field(u32, level)
			     __field(u32, cxsr)
			     __field(u32, primary)
			     __field(u32, sprite0)
			     __field(u32, sprite1)
			     __field(u32, cursor)
			     __field(u32, sr_plane)
			     __field(u32, sr_cursor)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   __entry->level = wm->level;
			   __entry->cxsr = wm->cxsr;
			   __entry->primary = wm->pipe[crtc->pipe].plane[PLANE_PRIMARY];
			   __entry->sprite0 = wm->pipe[crtc->pipe].plane[PLANE_SPRITE0];
			   __entry->sprite1 = wm->pipe[crtc->pipe].plane[PLANE_SPRITE1];
			   __entry->cursor = wm->pipe[crtc->pipe].plane[PLANE_CURSOR];
			   __entry->sr_plane = wm->sr.plane;
			   __entry->sr_cursor = wm->sr.cursor;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u, level=%d, cxsr=%d, wm %d/%d/%d/%d, sr %d/%d",
		      pipe_name(__entry->pipe), __entry->frame,
		      __entry->scanline, __entry->level, __entry->cxsr,
		      __entry->primary, __entry->sprite0, __entry->sprite1, __entry->cursor,
		      __entry->sr_plane, __entry->sr_cursor)
);

TRACE_EVENT(vlv_fअगरo_size,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc, u32 sprite0_start, u32 sprite1_start, u32 fअगरo_size),
	    TP_ARGS(crtc, sprite0_start, sprite1_start, fअगरo_size),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __field(u32, sprite0_start)
			     __field(u32, sprite1_start)
			     __field(u32, fअगरo_size)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   __entry->sprite0_start = sprite0_start;
			   __entry->sprite1_start = sprite1_start;
			   __entry->fअगरo_size = fअगरo_size;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u, %d/%d/%d",
		      pipe_name(__entry->pipe), __entry->frame,
		      __entry->scanline, __entry->sprite0_start,
		      __entry->sprite1_start, __entry->fअगरo_size)
);

/* plane updates */

TRACE_EVENT(पूर्णांकel_update_plane,
	    TP_PROTO(काष्ठा drm_plane *plane, काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(plane, crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __array(पूर्णांक, src, 4)
			     __array(पूर्णांक, dst, 4)
			     __string(name, plane->name)
			     ),

	    TP_fast_assign(
			   __assign_str(name, plane->name);
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   स_नकल(__entry->src, &plane->state->src, माप(__entry->src));
			   स_नकल(__entry->dst, &plane->state->dst, माप(__entry->dst));
			   ),

	    TP_prपूर्णांकk("pipe %c, plane %s, frame=%u, scanline=%u, " DRM_RECT_FP_FMT " -> " DRM_RECT_FMT,
		      pipe_name(__entry->pipe), __get_str(name),
		      __entry->frame, __entry->scanline,
		      DRM_RECT_FP_ARG((स्थिर काष्ठा drm_rect *)__entry->src),
		      DRM_RECT_ARG((स्थिर काष्ठा drm_rect *)__entry->dst))
);

TRACE_EVENT(पूर्णांकel_disable_plane,
	    TP_PROTO(काष्ठा drm_plane *plane, काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(plane, crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __string(name, plane->name)
			     ),

	    TP_fast_assign(
			   __assign_str(name, plane->name);
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pipe %c, plane %s, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe), __get_str(name),
		      __entry->frame, __entry->scanline)
);

/* fbc */

TRACE_EVENT(पूर्णांकel_fbc_activate,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe), __entry->frame, __entry->scanline)
);

TRACE_EVENT(पूर्णांकel_fbc_deactivate,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe), __entry->frame, __entry->scanline)
);

TRACE_EVENT(पूर्णांकel_fbc_nuke,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe), __entry->frame, __entry->scanline)
);

/* pipe updates */

TRACE_EVENT(पूर्णांकel_pipe_update_start,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __field(u32, min)
			     __field(u32, max)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = पूर्णांकel_crtc_get_vblank_counter(crtc);
			   __entry->scanline = पूर्णांकel_get_crtc_scanline(crtc);
			   __entry->min = crtc->debug.min_vbl;
			   __entry->max = crtc->debug.max_vbl;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u, min=%u, max=%u",
		      pipe_name(__entry->pipe), __entry->frame,
		       __entry->scanline, __entry->min, __entry->max)
);

TRACE_EVENT(पूर्णांकel_pipe_update_vblank_evaded,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc),
	    TP_ARGS(crtc),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     __field(u32, min)
			     __field(u32, max)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = crtc->debug.start_vbl_count;
			   __entry->scanline = crtc->debug.scanline_start;
			   __entry->min = crtc->debug.min_vbl;
			   __entry->max = crtc->debug.max_vbl;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u, min=%u, max=%u",
		      pipe_name(__entry->pipe), __entry->frame,
		       __entry->scanline, __entry->min, __entry->max)
);

TRACE_EVENT(पूर्णांकel_pipe_update_end,
	    TP_PROTO(काष्ठा पूर्णांकel_crtc *crtc, u32 frame, पूर्णांक scanline_end),
	    TP_ARGS(crtc, frame, scanline_end),

	    TP_STRUCT__entry(
			     __field(क्रमागत pipe, pipe)
			     __field(u32, frame)
			     __field(u32, scanline)
			     ),

	    TP_fast_assign(
			   __entry->pipe = crtc->pipe;
			   __entry->frame = frame;
			   __entry->scanline = scanline_end;
			   ),

	    TP_prपूर्णांकk("pipe %c, frame=%u, scanline=%u",
		      pipe_name(__entry->pipe), __entry->frame,
		      __entry->scanline)
);

/* object tracking */

TRACE_EVENT(i915_gem_object_create,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj),
	    TP_ARGS(obj),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(u64, size)
			     ),

	    TP_fast_assign(
			   __entry->obj = obj;
			   __entry->size = obj->base.size;
			   ),

	    TP_prपूर्णांकk("obj=%p, size=0x%llx", __entry->obj, __entry->size)
);

TRACE_EVENT(i915_gem_shrink,
	    TP_PROTO(काष्ठा drm_i915_निजी *i915, अचिन्हित दीर्घ target, अचिन्हित flags),
	    TP_ARGS(i915, target, flags),

	    TP_STRUCT__entry(
			     __field(पूर्णांक, dev)
			     __field(अचिन्हित दीर्घ, target)
			     __field(अचिन्हित, flags)
			     ),

	    TP_fast_assign(
			   __entry->dev = i915->drm.primary->index;
			   __entry->target = target;
			   __entry->flags = flags;
			   ),

	    TP_prपूर्णांकk("dev=%d, target=%lu, flags=%x",
		      __entry->dev, __entry->target, __entry->flags)
);

TRACE_EVENT(i915_vma_bind,
	    TP_PROTO(काष्ठा i915_vma *vma, अचिन्हित flags),
	    TP_ARGS(vma, flags),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(काष्ठा i915_address_space *, vm)
			     __field(u64, offset)
			     __field(u64, size)
			     __field(अचिन्हित, flags)
			     ),

	    TP_fast_assign(
			   __entry->obj = vma->obj;
			   __entry->vm = vma->vm;
			   __entry->offset = vma->node.start;
			   __entry->size = vma->node.size;
			   __entry->flags = flags;
			   ),

	    TP_prपूर्णांकk("obj=%p, offset=0x%016llx size=0x%llx%s vm=%p",
		      __entry->obj, __entry->offset, __entry->size,
		      __entry->flags & PIN_MAPPABLE ? ", mappable" : "",
		      __entry->vm)
);

TRACE_EVENT(i915_vma_unbind,
	    TP_PROTO(काष्ठा i915_vma *vma),
	    TP_ARGS(vma),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(काष्ठा i915_address_space *, vm)
			     __field(u64, offset)
			     __field(u64, size)
			     ),

	    TP_fast_assign(
			   __entry->obj = vma->obj;
			   __entry->vm = vma->vm;
			   __entry->offset = vma->node.start;
			   __entry->size = vma->node.size;
			   ),

	    TP_prपूर्णांकk("obj=%p, offset=0x%016llx size=0x%llx vm=%p",
		      __entry->obj, __entry->offset, __entry->size, __entry->vm)
);

TRACE_EVENT(i915_gem_object_pग_लिखो,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj, u64 offset, u64 len),
	    TP_ARGS(obj, offset, len),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(u64, offset)
			     __field(u64, len)
			     ),

	    TP_fast_assign(
			   __entry->obj = obj;
			   __entry->offset = offset;
			   __entry->len = len;
			   ),

	    TP_prपूर्णांकk("obj=%p, offset=0x%llx, len=0x%llx",
		      __entry->obj, __entry->offset, __entry->len)
);

TRACE_EVENT(i915_gem_object_pपढ़ो,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj, u64 offset, u64 len),
	    TP_ARGS(obj, offset, len),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(u64, offset)
			     __field(u64, len)
			     ),

	    TP_fast_assign(
			   __entry->obj = obj;
			   __entry->offset = offset;
			   __entry->len = len;
			   ),

	    TP_prपूर्णांकk("obj=%p, offset=0x%llx, len=0x%llx",
		      __entry->obj, __entry->offset, __entry->len)
);

TRACE_EVENT(i915_gem_object_fault,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj, u64 index, bool gtt, bool ग_लिखो),
	    TP_ARGS(obj, index, gtt, ग_लिखो),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     __field(u64, index)
			     __field(bool, gtt)
			     __field(bool, ग_लिखो)
			     ),

	    TP_fast_assign(
			   __entry->obj = obj;
			   __entry->index = index;
			   __entry->gtt = gtt;
			   __entry->ग_लिखो = ग_लिखो;
			   ),

	    TP_prपूर्णांकk("obj=%p, %s index=%llu %s",
		      __entry->obj,
		      __entry->gtt ? "GTT" : "CPU",
		      __entry->index,
		      __entry->ग_लिखो ? ", writable" : "")
);

DECLARE_EVENT_CLASS(i915_gem_object,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj),
	    TP_ARGS(obj),

	    TP_STRUCT__entry(
			     __field(काष्ठा drm_i915_gem_object *, obj)
			     ),

	    TP_fast_assign(
			   __entry->obj = obj;
			   ),

	    TP_prपूर्णांकk("obj=%p", __entry->obj)
);

DEFINE_EVENT(i915_gem_object, i915_gem_object_clflush,
	     TP_PROTO(काष्ठा drm_i915_gem_object *obj),
	     TP_ARGS(obj)
);

DEFINE_EVENT(i915_gem_object, i915_gem_object_destroy,
	    TP_PROTO(काष्ठा drm_i915_gem_object *obj),
	    TP_ARGS(obj)
);

TRACE_EVENT(i915_gem_evict,
	    TP_PROTO(काष्ठा i915_address_space *vm, u64 size, u64 align, अचिन्हित पूर्णांक flags),
	    TP_ARGS(vm, size, align, flags),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(काष्ठा i915_address_space *, vm)
			     __field(u64, size)
			     __field(u64, align)
			     __field(अचिन्हित पूर्णांक, flags)
			    ),

	    TP_fast_assign(
			   __entry->dev = vm->i915->drm.primary->index;
			   __entry->vm = vm;
			   __entry->size = size;
			   __entry->align = align;
			   __entry->flags = flags;
			  ),

	    TP_prपूर्णांकk("dev=%d, vm=%p, size=0x%llx, align=0x%llx %s",
		      __entry->dev, __entry->vm, __entry->size, __entry->align,
		      __entry->flags & PIN_MAPPABLE ? ", mappable" : "")
);

TRACE_EVENT(i915_gem_evict_node,
	    TP_PROTO(काष्ठा i915_address_space *vm, काष्ठा drm_mm_node *node, अचिन्हित पूर्णांक flags),
	    TP_ARGS(vm, node, flags),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(काष्ठा i915_address_space *, vm)
			     __field(u64, start)
			     __field(u64, size)
			     __field(अचिन्हित दीर्घ, color)
			     __field(अचिन्हित पूर्णांक, flags)
			    ),

	    TP_fast_assign(
			   __entry->dev = vm->i915->drm.primary->index;
			   __entry->vm = vm;
			   __entry->start = node->start;
			   __entry->size = node->size;
			   __entry->color = node->color;
			   __entry->flags = flags;
			  ),

	    TP_prपूर्णांकk("dev=%d, vm=%p, start=0x%llx size=0x%llx, color=0x%lx, flags=%x",
		      __entry->dev, __entry->vm,
		      __entry->start, __entry->size,
		      __entry->color, __entry->flags)
);

TRACE_EVENT(i915_gem_evict_vm,
	    TP_PROTO(काष्ठा i915_address_space *vm),
	    TP_ARGS(vm),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(काष्ठा i915_address_space *, vm)
			    ),

	    TP_fast_assign(
			   __entry->dev = vm->i915->drm.primary->index;
			   __entry->vm = vm;
			  ),

	    TP_prपूर्णांकk("dev=%d, vm=%p", __entry->dev, __entry->vm)
);

TRACE_EVENT(i915_request_queue,
	    TP_PROTO(काष्ठा i915_request *rq, u32 flags),
	    TP_ARGS(rq, flags),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, ctx)
			     __field(u16, class)
			     __field(u16, instance)
			     __field(u32, seqno)
			     __field(u32, flags)
			     ),

	    TP_fast_assign(
			   __entry->dev = rq->engine->i915->drm.primary->index;
			   __entry->class = rq->engine->uabi_class;
			   __entry->instance = rq->engine->uabi_instance;
			   __entry->ctx = rq->fence.context;
			   __entry->seqno = rq->fence.seqno;
			   __entry->flags = flags;
			   ),

	    TP_prपूर्णांकk("dev=%u, engine=%u:%u, ctx=%llu, seqno=%u, flags=0x%x",
		      __entry->dev, __entry->class, __entry->instance,
		      __entry->ctx, __entry->seqno, __entry->flags)
);

DECLARE_EVENT_CLASS(i915_request,
	    TP_PROTO(काष्ठा i915_request *rq),
	    TP_ARGS(rq),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, ctx)
			     __field(u16, class)
			     __field(u16, instance)
			     __field(u32, seqno)
			     ),

	    TP_fast_assign(
			   __entry->dev = rq->engine->i915->drm.primary->index;
			   __entry->class = rq->engine->uabi_class;
			   __entry->instance = rq->engine->uabi_instance;
			   __entry->ctx = rq->fence.context;
			   __entry->seqno = rq->fence.seqno;
			   ),

	    TP_prपूर्णांकk("dev=%u, engine=%u:%u, ctx=%llu, seqno=%u",
		      __entry->dev, __entry->class, __entry->instance,
		      __entry->ctx, __entry->seqno)
);

DEFINE_EVENT(i915_request, i915_request_add,
	    TP_PROTO(काष्ठा i915_request *rq),
	    TP_ARGS(rq)
);

#अगर defined(CONFIG_DRM_I915_LOW_LEVEL_TRACEPOINTS)
DEFINE_EVENT(i915_request, i915_request_submit,
	     TP_PROTO(काष्ठा i915_request *rq),
	     TP_ARGS(rq)
);

DEFINE_EVENT(i915_request, i915_request_execute,
	     TP_PROTO(काष्ठा i915_request *rq),
	     TP_ARGS(rq)
);

TRACE_EVENT(i915_request_in,
	    TP_PROTO(काष्ठा i915_request *rq, अचिन्हित पूर्णांक port),
	    TP_ARGS(rq, port),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, ctx)
			     __field(u16, class)
			     __field(u16, instance)
			     __field(u32, seqno)
			     __field(u32, port)
			     __field(s32, prio)
			    ),

	    TP_fast_assign(
			   __entry->dev = rq->engine->i915->drm.primary->index;
			   __entry->class = rq->engine->uabi_class;
			   __entry->instance = rq->engine->uabi_instance;
			   __entry->ctx = rq->fence.context;
			   __entry->seqno = rq->fence.seqno;
			   __entry->prio = rq->sched.attr.priority;
			   __entry->port = port;
			   ),

	    TP_prपूर्णांकk("dev=%u, engine=%u:%u, ctx=%llu, seqno=%u, prio=%d, port=%u",
		      __entry->dev, __entry->class, __entry->instance,
		      __entry->ctx, __entry->seqno,
		      __entry->prio, __entry->port)
);

TRACE_EVENT(i915_request_out,
	    TP_PROTO(काष्ठा i915_request *rq),
	    TP_ARGS(rq),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, ctx)
			     __field(u16, class)
			     __field(u16, instance)
			     __field(u32, seqno)
			     __field(u32, completed)
			    ),

	    TP_fast_assign(
			   __entry->dev = rq->engine->i915->drm.primary->index;
			   __entry->class = rq->engine->uabi_class;
			   __entry->instance = rq->engine->uabi_instance;
			   __entry->ctx = rq->fence.context;
			   __entry->seqno = rq->fence.seqno;
			   __entry->completed = i915_request_completed(rq);
			   ),

		    TP_prपूर्णांकk("dev=%u, engine=%u:%u, ctx=%llu, seqno=%u, completed?=%u",
			      __entry->dev, __entry->class, __entry->instance,
			      __entry->ctx, __entry->seqno, __entry->completed)
);

#अन्यथा
#अगर !defined(TRACE_HEADER_MULTI_READ)
अटल अंतरभूत व्योम
trace_i915_request_submit(काष्ठा i915_request *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम
trace_i915_request_execute(काष्ठा i915_request *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम
trace_i915_request_in(काष्ठा i915_request *rq, अचिन्हित पूर्णांक port)
अणु
पूर्ण

अटल अंतरभूत व्योम
trace_i915_request_out(काष्ठा i915_request *rq)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

DEFINE_EVENT(i915_request, i915_request_retire,
	    TP_PROTO(काष्ठा i915_request *rq),
	    TP_ARGS(rq)
);

TRACE_EVENT(i915_request_रुको_begin,
	    TP_PROTO(काष्ठा i915_request *rq, अचिन्हित पूर्णांक flags),
	    TP_ARGS(rq, flags),

	    TP_STRUCT__entry(
			     __field(u32, dev)
			     __field(u64, ctx)
			     __field(u16, class)
			     __field(u16, instance)
			     __field(u32, seqno)
			     __field(अचिन्हित पूर्णांक, flags)
			     ),

	    /* NB: the blocking inक्रमmation is racy since mutex_is_locked
	     * करोesn't check that the current thपढ़ो holds the lock. The only
	     * other option would be to pass the boolean inक्रमmation of whether
	     * or not the class was blocking करोwn through the stack which is
	     * less desirable.
	     */
	    TP_fast_assign(
			   __entry->dev = rq->engine->i915->drm.primary->index;
			   __entry->class = rq->engine->uabi_class;
			   __entry->instance = rq->engine->uabi_instance;
			   __entry->ctx = rq->fence.context;
			   __entry->seqno = rq->fence.seqno;
			   __entry->flags = flags;
			   ),

	    TP_prपूर्णांकk("dev=%u, engine=%u:%u, ctx=%llu, seqno=%u, flags=0x%x",
		      __entry->dev, __entry->class, __entry->instance,
		      __entry->ctx, __entry->seqno,
		      __entry->flags)
);

DEFINE_EVENT(i915_request, i915_request_रुको_end,
	    TP_PROTO(काष्ठा i915_request *rq),
	    TP_ARGS(rq)
);

TRACE_EVENT_CONDITION(i915_reg_rw,
	TP_PROTO(bool ग_लिखो, i915_reg_t reg, u64 val, पूर्णांक len, bool trace),

	TP_ARGS(ग_लिखो, reg, val, len, trace),

	TP_CONDITION(trace),

	TP_STRUCT__entry(
		__field(u64, val)
		__field(u32, reg)
		__field(u16, ग_लिखो)
		__field(u16, len)
		),

	TP_fast_assign(
		__entry->val = (u64)val;
		__entry->reg = i915_mmio_reg_offset(reg);
		__entry->ग_लिखो = ग_लिखो;
		__entry->len = len;
		),

	TP_prपूर्णांकk("%s reg=0x%x, len=%d, val=(0x%x, 0x%x)",
		__entry->ग_लिखो ? "write" : "read",
		__entry->reg, __entry->len,
		(u32)(__entry->val & 0xffffffff),
		(u32)(__entry->val >> 32))
);

TRACE_EVENT(पूर्णांकel_gpu_freq_change,
	    TP_PROTO(u32 freq),
	    TP_ARGS(freq),

	    TP_STRUCT__entry(
			     __field(u32, freq)
			     ),

	    TP_fast_assign(
			   __entry->freq = freq;
			   ),

	    TP_prपूर्णांकk("new_freq=%u", __entry->freq)
);

/**
 * DOC: i915_ppgtt_create and i915_ppgtt_release tracepoपूर्णांकs
 *
 * With full ppgtt enabled each process using drm will allocate at least one
 * translation table. With these traces it is possible to keep track of the
 * allocation and of the lअगरeसमय of the tables; this can be used during
 * testing/debug to verअगरy that we are not leaking ppgtts.
 * These traces identअगरy the ppgtt through the vm poपूर्णांकer, which is also prपूर्णांकed
 * by the i915_vma_bind and i915_vma_unbind tracepoपूर्णांकs.
 */
DECLARE_EVENT_CLASS(i915_ppgtt,
	TP_PROTO(काष्ठा i915_address_space *vm),
	TP_ARGS(vm),

	TP_STRUCT__entry(
			__field(काष्ठा i915_address_space *, vm)
			__field(u32, dev)
	),

	TP_fast_assign(
			__entry->vm = vm;
			__entry->dev = vm->i915->drm.primary->index;
	),

	TP_prपूर्णांकk("dev=%u, vm=%p", __entry->dev, __entry->vm)
)

DEFINE_EVENT(i915_ppgtt, i915_ppgtt_create,
	TP_PROTO(काष्ठा i915_address_space *vm),
	TP_ARGS(vm)
);

DEFINE_EVENT(i915_ppgtt, i915_ppgtt_release,
	TP_PROTO(काष्ठा i915_address_space *vm),
	TP_ARGS(vm)
);

/**
 * DOC: i915_context_create and i915_context_मुक्त tracepoपूर्णांकs
 *
 * These tracepoपूर्णांकs are used to track creation and deletion of contexts.
 * If full ppgtt is enabled, they also prपूर्णांक the address of the vm asचिन्हित to
 * the context.
 */
DECLARE_EVENT_CLASS(i915_context,
	TP_PROTO(काष्ठा i915_gem_context *ctx),
	TP_ARGS(ctx),

	TP_STRUCT__entry(
			__field(u32, dev)
			__field(काष्ठा i915_gem_context *, ctx)
			__field(काष्ठा i915_address_space *, vm)
	),

	TP_fast_assign(
			__entry->dev = ctx->i915->drm.primary->index;
			__entry->ctx = ctx;
			__entry->vm = rcu_access_poपूर्णांकer(ctx->vm);
	),

	TP_prपूर्णांकk("dev=%u, ctx=%p, ctx_vm=%p",
		  __entry->dev, __entry->ctx, __entry->vm)
)

DEFINE_EVENT(i915_context, i915_context_create,
	TP_PROTO(काष्ठा i915_gem_context *ctx),
	TP_ARGS(ctx)
);

DEFINE_EVENT(i915_context, i915_context_मुक्त,
	TP_PROTO(काष्ठा i915_gem_context *ctx),
	TP_ARGS(ctx)
);

#पूर्ण_अगर /* _I915_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/i915
#समावेश <trace/define_trace.h>
