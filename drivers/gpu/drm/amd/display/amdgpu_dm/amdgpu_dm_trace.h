<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM amdgpu_dm

#अगर !defined(_AMDGPU_DM_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _AMDGPU_DM_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_atomic.h>

#समावेश "dc/inc/core_types.h"

DECLARE_EVENT_CLASS(amdgpu_dc_reg_ढाँचा,
		    TP_PROTO(अचिन्हित दीर्घ *count, uपूर्णांक32_t reg, uपूर्णांक32_t value),
		    TP_ARGS(count, reg, value),

		    TP_STRUCT__entry(
				     __field(uपूर्णांक32_t, reg)
				     __field(uपूर्णांक32_t, value)
		    ),

		    TP_fast_assign(
				   __entry->reg = reg;
				   __entry->value = value;
				   *count = *count + 1;
		    ),

		    TP_prपूर्णांकk("reg=0x%08lx, value=0x%08lx",
			      (अचिन्हित दीर्घ)__entry->reg,
			      (अचिन्हित दीर्घ)__entry->value)
);

DEFINE_EVENT(amdgpu_dc_reg_ढाँचा, amdgpu_dc_rreg,
	     TP_PROTO(अचिन्हित दीर्घ *count, uपूर्णांक32_t reg, uपूर्णांक32_t value),
	     TP_ARGS(count, reg, value));

DEFINE_EVENT(amdgpu_dc_reg_ढाँचा, amdgpu_dc_wreg,
	     TP_PROTO(अचिन्हित दीर्घ *count, uपूर्णांक32_t reg, uपूर्णांक32_t value),
	     TP_ARGS(count, reg, value));

TRACE_EVENT(amdgpu_dc_perक्रमmance,
	TP_PROTO(अचिन्हित दीर्घ पढ़ो_count, अचिन्हित दीर्घ ग_लिखो_count,
		अचिन्हित दीर्घ *last_पढ़ो, अचिन्हित दीर्घ *last_ग_लिखो,
		स्थिर अक्षर *func, अचिन्हित पूर्णांक line),
	TP_ARGS(पढ़ो_count, ग_लिखो_count, last_पढ़ो, last_ग_लिखो, func, line),
	TP_STRUCT__entry(
			__field(uपूर्णांक32_t, पढ़ोs)
			__field(uपूर्णांक32_t, ग_लिखोs)
			__field(uपूर्णांक32_t, पढ़ो_delta)
			__field(uपूर्णांक32_t, ग_लिखो_delta)
			__string(func, func)
			__field(uपूर्णांक32_t, line)
			),
	TP_fast_assign(
			__entry->पढ़ोs = पढ़ो_count;
			__entry->ग_लिखोs = ग_लिखो_count;
			__entry->पढ़ो_delta = पढ़ो_count - *last_पढ़ो;
			__entry->ग_लिखो_delta = ग_लिखो_count - *last_ग_लिखो;
			__assign_str(func, func);
			__entry->line = line;
			*last_पढ़ो = पढ़ो_count;
			*last_ग_लिखो = ग_लिखो_count;
			),
	TP_prपूर्णांकk("%s:%d reads=%08ld (%08ld total), writes=%08ld (%08ld total)",
			__get_str(func), __entry->line,
			(अचिन्हित दीर्घ)__entry->पढ़ो_delta,
			(अचिन्हित दीर्घ)__entry->पढ़ोs,
			(अचिन्हित दीर्घ)__entry->ग_लिखो_delta,
			(अचिन्हित दीर्घ)__entry->ग_लिखोs)
);

TRACE_EVENT(amdgpu_dm_connector_atomic_check,
	    TP_PROTO(स्थिर काष्ठा drm_connector_state *state),
	    TP_ARGS(state),

	    TP_STRUCT__entry(
			     __field(uपूर्णांक32_t, conn_id)
			     __field(स्थिर काष्ठा drm_connector_state *, conn_state)
			     __field(स्थिर काष्ठा drm_atomic_state *, state)
			     __field(स्थिर काष्ठा drm_crtc_commit *, commit)
			     __field(uपूर्णांक32_t, crtc_id)
			     __field(uपूर्णांक32_t, best_encoder_id)
			     __field(क्रमागत drm_link_status, link_status)
			     __field(bool, self_refresh_aware)
			     __field(क्रमागत hdmi_picture_aspect, picture_aspect_ratio)
			     __field(अचिन्हित पूर्णांक, content_type)
			     __field(अचिन्हित पूर्णांक, hdcp_content_type)
			     __field(अचिन्हित पूर्णांक, content_protection)
			     __field(अचिन्हित पूर्णांक, scaling_mode)
			     __field(u32, colorspace)
			     __field(u8, max_requested_bpc)
			     __field(u8, max_bpc)
	    ),

	    TP_fast_assign(
			   __entry->conn_id = state->connector->base.id;
			   __entry->conn_state = state;
			   __entry->state = state->state;
			   __entry->commit = state->commit;
			   __entry->crtc_id = state->crtc ? state->crtc->base.id : 0;
			   __entry->best_encoder_id = state->best_encoder ?
						      state->best_encoder->base.id : 0;
			   __entry->link_status = state->link_status;
			   __entry->self_refresh_aware = state->self_refresh_aware;
			   __entry->picture_aspect_ratio = state->picture_aspect_ratio;
			   __entry->content_type = state->content_type;
			   __entry->hdcp_content_type = state->hdcp_content_type;
			   __entry->content_protection = state->content_protection;
			   __entry->scaling_mode = state->scaling_mode;
			   __entry->colorspace = state->colorspace;
			   __entry->max_requested_bpc = state->max_requested_bpc;
			   __entry->max_bpc = state->max_bpc;
	    ),

	    TP_prपूर्णांकk("conn_id=%u conn_state=%p state=%p commit=%p crtc_id=%u "
		      "best_encoder_id=%u link_status=%d self_refresh_aware=%d "
		      "picture_aspect_ratio=%d content_type=%u "
		      "hdcp_content_type=%u content_protection=%u scaling_mode=%u "
		      "colorspace=%u max_requested_bpc=%u max_bpc=%u",
		      __entry->conn_id, __entry->conn_state, __entry->state,
		      __entry->commit, __entry->crtc_id, __entry->best_encoder_id,
		      __entry->link_status, __entry->self_refresh_aware,
		      __entry->picture_aspect_ratio, __entry->content_type,
		      __entry->hdcp_content_type, __entry->content_protection,
		      __entry->scaling_mode, __entry->colorspace,
		      __entry->max_requested_bpc, __entry->max_bpc)
);

TRACE_EVENT(amdgpu_dm_crtc_atomic_check,
	    TP_PROTO(स्थिर काष्ठा drm_crtc_state *state),
	    TP_ARGS(state),

	    TP_STRUCT__entry(
			     __field(स्थिर काष्ठा drm_atomic_state *, state)
			     __field(स्थिर काष्ठा drm_crtc_state *, crtc_state)
			     __field(स्थिर काष्ठा drm_crtc_commit *, commit)
			     __field(uपूर्णांक32_t, crtc_id)
			     __field(bool, enable)
			     __field(bool, active)
			     __field(bool, planes_changed)
			     __field(bool, mode_changed)
			     __field(bool, active_changed)
			     __field(bool, connectors_changed)
			     __field(bool, zpos_changed)
			     __field(bool, color_mgmt_changed)
			     __field(bool, no_vblank)
			     __field(bool, async_flip)
			     __field(bool, vrr_enabled)
			     __field(bool, self_refresh_active)
			     __field(u32, plane_mask)
			     __field(u32, connector_mask)
			     __field(u32, encoder_mask)
	    ),

	    TP_fast_assign(
			   __entry->state = state->state;
			   __entry->crtc_state = state;
			   __entry->crtc_id = state->crtc->base.id;
			   __entry->commit = state->commit;
			   __entry->enable = state->enable;
			   __entry->active = state->active;
			   __entry->planes_changed = state->planes_changed;
			   __entry->mode_changed = state->mode_changed;
			   __entry->active_changed = state->active_changed;
			   __entry->connectors_changed = state->connectors_changed;
			   __entry->zpos_changed = state->zpos_changed;
			   __entry->color_mgmt_changed = state->color_mgmt_changed;
			   __entry->no_vblank = state->no_vblank;
			   __entry->async_flip = state->async_flip;
			   __entry->vrr_enabled = state->vrr_enabled;
			   __entry->self_refresh_active = state->self_refresh_active;
			   __entry->plane_mask = state->plane_mask;
			   __entry->connector_mask = state->connector_mask;
			   __entry->encoder_mask = state->encoder_mask;
	    ),

	    TP_prपूर्णांकk("crtc_id=%u crtc_state=%p state=%p commit=%p changed("
		      "planes=%d mode=%d active=%d conn=%d zpos=%d color_mgmt=%d) "
		      "state(enable=%d active=%d async_flip=%d vrr_enabled=%d "
		      "self_refresh_active=%d no_vblank=%d) mask(plane=%x conn=%x "
		      "enc=%x)",
		      __entry->crtc_id, __entry->crtc_state, __entry->state,
		      __entry->commit, __entry->planes_changed,
		      __entry->mode_changed, __entry->active_changed,
		      __entry->connectors_changed, __entry->zpos_changed,
		      __entry->color_mgmt_changed, __entry->enable, __entry->active,
		      __entry->async_flip, __entry->vrr_enabled,
		      __entry->self_refresh_active, __entry->no_vblank,
		      __entry->plane_mask, __entry->connector_mask,
		      __entry->encoder_mask)
);

DECLARE_EVENT_CLASS(amdgpu_dm_plane_state_ढाँचा,
	    TP_PROTO(स्थिर काष्ठा drm_plane_state *state),
	    TP_ARGS(state),
	    TP_STRUCT__entry(
			     __field(uपूर्णांक32_t, plane_id)
			     __field(क्रमागत drm_plane_type, plane_type)
			     __field(स्थिर काष्ठा drm_plane_state *, plane_state)
			     __field(स्थिर काष्ठा drm_atomic_state *, state)
			     __field(uपूर्णांक32_t, crtc_id)
			     __field(uपूर्णांक32_t, fb_id)
			     __field(uपूर्णांक32_t, fb_क्रमmat)
			     __field(uपूर्णांक8_t, fb_planes)
			     __field(uपूर्णांक64_t, fb_modअगरier)
			     __field(स्थिर काष्ठा dma_fence *, fence)
			     __field(पूर्णांक32_t, crtc_x)
			     __field(पूर्णांक32_t, crtc_y)
			     __field(uपूर्णांक32_t, crtc_w)
			     __field(uपूर्णांक32_t, crtc_h)
			     __field(uपूर्णांक32_t, src_x)
			     __field(uपूर्णांक32_t, src_y)
			     __field(uपूर्णांक32_t, src_w)
			     __field(uपूर्णांक32_t, src_h)
			     __field(u32, alpha)
			     __field(uपूर्णांक32_t, pixel_blend_mode)
			     __field(अचिन्हित पूर्णांक, rotation)
			     __field(अचिन्हित पूर्णांक, zpos)
			     __field(अचिन्हित पूर्णांक, normalized_zpos)
			     __field(क्रमागत drm_color_encoding, color_encoding)
			     __field(क्रमागत drm_color_range, color_range)
			     __field(bool, visible)
	    ),

	    TP_fast_assign(
			   __entry->plane_id = state->plane->base.id;
			   __entry->plane_type = state->plane->type;
			   __entry->plane_state = state;
			   __entry->state = state->state;
			   __entry->crtc_id = state->crtc ? state->crtc->base.id : 0;
			   __entry->fb_id = state->fb ? state->fb->base.id : 0;
			   __entry->fb_क्रमmat = state->fb ? state->fb->क्रमmat->क्रमmat : 0;
			   __entry->fb_planes = state->fb ? state->fb->क्रमmat->num_planes : 0;
			   __entry->fb_modअगरier = state->fb ? state->fb->modअगरier : 0;
			   __entry->fence = state->fence;
			   __entry->crtc_x = state->crtc_x;
			   __entry->crtc_y = state->crtc_y;
			   __entry->crtc_w = state->crtc_w;
			   __entry->crtc_h = state->crtc_h;
			   __entry->src_x = state->src_x >> 16;
			   __entry->src_y = state->src_y >> 16;
			   __entry->src_w = state->src_w >> 16;
			   __entry->src_h = state->src_h >> 16;
			   __entry->alpha = state->alpha;
			   __entry->pixel_blend_mode = state->pixel_blend_mode;
			   __entry->rotation = state->rotation;
			   __entry->zpos = state->zpos;
			   __entry->normalized_zpos = state->normalized_zpos;
			   __entry->color_encoding = state->color_encoding;
			   __entry->color_range = state->color_range;
			   __entry->visible = state->visible;
	    ),

	    TP_prपूर्णांकk("plane_id=%u plane_type=%d plane_state=%p state=%p "
		      "crtc_id=%u fb(id=%u fmt=%c%c%c%c planes=%u mod=%llu) "
		      "fence=%p crtc_x=%d crtc_y=%d crtc_w=%u crtc_h=%u "
		      "src_x=%u src_y=%u src_w=%u src_h=%u alpha=%u "
		      "pixel_blend_mode=%u rotation=%u zpos=%u "
		      "normalized_zpos=%u color_encoding=%d color_range=%d "
		      "visible=%d",
		      __entry->plane_id, __entry->plane_type, __entry->plane_state,
		      __entry->state, __entry->crtc_id, __entry->fb_id,
		      (__entry->fb_क्रमmat & 0xff) ? (__entry->fb_क्रमmat & 0xff) : 'N',
		      ((__entry->fb_क्रमmat >> 8) & 0xff) ? ((__entry->fb_क्रमmat >> 8) & 0xff) : 'O',
		      ((__entry->fb_क्रमmat >> 16) & 0xff) ? ((__entry->fb_क्रमmat >> 16) & 0xff) : 'N',
		      ((__entry->fb_क्रमmat >> 24) & 0x7f) ? ((__entry->fb_क्रमmat >> 24) & 0x7f) : 'E',
		      __entry->fb_planes,
		      __entry->fb_modअगरier, __entry->fence, __entry->crtc_x,
		      __entry->crtc_y, __entry->crtc_w, __entry->crtc_h,
		      __entry->src_x, __entry->src_y, __entry->src_w, __entry->src_h,
		      __entry->alpha, __entry->pixel_blend_mode, __entry->rotation,
		      __entry->zpos, __entry->normalized_zpos,
		      __entry->color_encoding, __entry->color_range,
		      __entry->visible)
);

DEFINE_EVENT(amdgpu_dm_plane_state_ढाँचा, amdgpu_dm_plane_atomic_check,
	     TP_PROTO(स्थिर काष्ठा drm_plane_state *state),
	     TP_ARGS(state));

DEFINE_EVENT(amdgpu_dm_plane_state_ढाँचा, amdgpu_dm_atomic_update_cursor,
	     TP_PROTO(स्थिर काष्ठा drm_plane_state *state),
	     TP_ARGS(state));

TRACE_EVENT(amdgpu_dm_atomic_state_ढाँचा,
	    TP_PROTO(स्थिर काष्ठा drm_atomic_state *state),
	    TP_ARGS(state),

	    TP_STRUCT__entry(
			     __field(स्थिर काष्ठा drm_atomic_state *, state)
			     __field(bool, allow_modeset)
			     __field(bool, legacy_cursor_update)
			     __field(bool, async_update)
			     __field(bool, duplicated)
			     __field(पूर्णांक, num_connector)
			     __field(पूर्णांक, num_निजी_objs)
	    ),

	    TP_fast_assign(
			   __entry->state = state;
			   __entry->allow_modeset = state->allow_modeset;
			   __entry->legacy_cursor_update = state->legacy_cursor_update;
			   __entry->async_update = state->async_update;
			   __entry->duplicated = state->duplicated;
			   __entry->num_connector = state->num_connector;
			   __entry->num_निजी_objs = state->num_निजी_objs;
	    ),

	    TP_prपूर्णांकk("state=%p allow_modeset=%d legacy_cursor_update=%d "
		      "async_update=%d duplicated=%d num_connector=%d "
		      "num_private_objs=%d",
		      __entry->state, __entry->allow_modeset, __entry->legacy_cursor_update,
		      __entry->async_update, __entry->duplicated, __entry->num_connector,
		      __entry->num_निजी_objs)
);

DEFINE_EVENT(amdgpu_dm_atomic_state_ढाँचा, amdgpu_dm_atomic_commit_tail_begin,
	     TP_PROTO(स्थिर काष्ठा drm_atomic_state *state),
	     TP_ARGS(state));

DEFINE_EVENT(amdgpu_dm_atomic_state_ढाँचा, amdgpu_dm_atomic_commit_tail_finish,
	     TP_PROTO(स्थिर काष्ठा drm_atomic_state *state),
	     TP_ARGS(state));

DEFINE_EVENT(amdgpu_dm_atomic_state_ढाँचा, amdgpu_dm_atomic_check_begin,
	     TP_PROTO(स्थिर काष्ठा drm_atomic_state *state),
	     TP_ARGS(state));

TRACE_EVENT(amdgpu_dm_atomic_check_finish,
	    TP_PROTO(स्थिर काष्ठा drm_atomic_state *state, पूर्णांक res),
	    TP_ARGS(state, res),

	    TP_STRUCT__entry(
			     __field(स्थिर काष्ठा drm_atomic_state *, state)
			     __field(पूर्णांक, res)
			     __field(bool, async_update)
			     __field(bool, allow_modeset)
	    ),

	    TP_fast_assign(
			   __entry->state = state;
			   __entry->res = res;
			   __entry->async_update = state->async_update;
			   __entry->allow_modeset = state->allow_modeset;
	    ),

	    TP_prपूर्णांकk("state=%p res=%d async_update=%d allow_modeset=%d",
		      __entry->state, __entry->res,
		      __entry->async_update, __entry->allow_modeset)
);

TRACE_EVENT(amdgpu_dm_dc_pipe_state,
	    TP_PROTO(पूर्णांक pipe_idx, स्थिर काष्ठा dc_plane_state *plane_state,
		     स्थिर काष्ठा dc_stream_state *stream,
		     स्थिर काष्ठा plane_resource *plane_res,
		     पूर्णांक update_flags),
	    TP_ARGS(pipe_idx, plane_state, stream, plane_res, update_flags),

	    TP_STRUCT__entry(
			     __field(पूर्णांक, pipe_idx)
			     __field(स्थिर व्योम *, stream)
			     __field(पूर्णांक, stream_w)
			     __field(पूर्णांक, stream_h)
			     __field(पूर्णांक, dst_x)
			     __field(पूर्णांक, dst_y)
			     __field(पूर्णांक, dst_w)
			     __field(पूर्णांक, dst_h)
			     __field(पूर्णांक, src_x)
			     __field(पूर्णांक, src_y)
			     __field(पूर्णांक, src_w)
			     __field(पूर्णांक, src_h)
			     __field(पूर्णांक, clip_x)
			     __field(पूर्णांक, clip_y)
			     __field(पूर्णांक, clip_w)
			     __field(पूर्णांक, clip_h)
			     __field(पूर्णांक, recout_x)
			     __field(पूर्णांक, recout_y)
			     __field(पूर्णांक, recout_w)
			     __field(पूर्णांक, recout_h)
			     __field(पूर्णांक, viewport_x)
			     __field(पूर्णांक, viewport_y)
			     __field(पूर्णांक, viewport_w)
			     __field(पूर्णांक, viewport_h)
			     __field(पूर्णांक, flip_immediate)
			     __field(पूर्णांक, surface_pitch)
			     __field(पूर्णांक, क्रमmat)
			     __field(पूर्णांक, swizzle)
			     __field(अचिन्हित पूर्णांक, update_flags)
	),

	TP_fast_assign(
		       __entry->pipe_idx = pipe_idx;
		       __entry->stream = stream;
		       __entry->stream_w = stream->timing.h_addressable;
		       __entry->stream_h = stream->timing.v_addressable;
		       __entry->dst_x = plane_state->dst_rect.x;
		       __entry->dst_y = plane_state->dst_rect.y;
		       __entry->dst_w = plane_state->dst_rect.width;
		       __entry->dst_h = plane_state->dst_rect.height;
		       __entry->src_x = plane_state->src_rect.x;
		       __entry->src_y = plane_state->src_rect.y;
		       __entry->src_w = plane_state->src_rect.width;
		       __entry->src_h = plane_state->src_rect.height;
		       __entry->clip_x = plane_state->clip_rect.x;
		       __entry->clip_y = plane_state->clip_rect.y;
		       __entry->clip_w = plane_state->clip_rect.width;
		       __entry->clip_h = plane_state->clip_rect.height;
		       __entry->recout_x = plane_res->scl_data.recout.x;
		       __entry->recout_y = plane_res->scl_data.recout.y;
		       __entry->recout_w = plane_res->scl_data.recout.width;
		       __entry->recout_h = plane_res->scl_data.recout.height;
		       __entry->viewport_x = plane_res->scl_data.viewport.x;
		       __entry->viewport_y = plane_res->scl_data.viewport.y;
		       __entry->viewport_w = plane_res->scl_data.viewport.width;
		       __entry->viewport_h = plane_res->scl_data.viewport.height;
		       __entry->flip_immediate = plane_state->flip_immediate;
		       __entry->surface_pitch = plane_state->plane_size.surface_pitch;
		       __entry->क्रमmat = plane_state->क्रमmat;
		       __entry->swizzle = plane_state->tiling_info.gfx9.swizzle;
		       __entry->update_flags = update_flags;
	),
	TP_prपूर्णांकk("pipe_idx=%d stream=%p rct(%d,%d) dst=(%d,%d,%d,%d) "
		  "src=(%d,%d,%d,%d) clip=(%d,%d,%d,%d) recout=(%d,%d,%d,%d) "
		  "viewport=(%d,%d,%d,%d) flip_immediate=%d pitch=%d "
		  "format=%d swizzle=%d update_flags=%x",
		  __entry->pipe_idx,
		  __entry->stream,
		  __entry->stream_w,
		  __entry->stream_h,
		  __entry->dst_x,
		  __entry->dst_y,
		  __entry->dst_w,
		  __entry->dst_h,
		  __entry->src_x,
		  __entry->src_y,
		  __entry->src_w,
		  __entry->src_h,
		  __entry->clip_x,
		  __entry->clip_y,
		  __entry->clip_w,
		  __entry->clip_h,
		  __entry->recout_x,
		  __entry->recout_y,
		  __entry->recout_w,
		  __entry->recout_h,
		  __entry->viewport_x,
		  __entry->viewport_y,
		  __entry->viewport_w,
		  __entry->viewport_h,
		  __entry->flip_immediate,
		  __entry->surface_pitch,
		  __entry->क्रमmat,
		  __entry->swizzle,
		  __entry->update_flags
	)
);

TRACE_EVENT(amdgpu_dm_dc_घड़ीs_state,
	    TP_PROTO(स्थिर काष्ठा dc_घड़ीs *clk),
	    TP_ARGS(clk),

	    TP_STRUCT__entry(
			     __field(पूर्णांक, dispclk_khz)
			     __field(पूर्णांक, dppclk_khz)
			     __field(पूर्णांक, disp_dpp_voltage_level_khz)
			     __field(पूर्णांक, dcfclk_khz)
			     __field(पूर्णांक, socclk_khz)
			     __field(पूर्णांक, dcfclk_deep_sleep_khz)
			     __field(पूर्णांक, fclk_khz)
			     __field(पूर्णांक, phyclk_khz)
			     __field(पूर्णांक, dramclk_khz)
			     __field(पूर्णांक, p_state_change_support)
			     __field(पूर्णांक, prev_p_state_change_support)
			     __field(पूर्णांक, pwr_state)
			     __field(पूर्णांक, dपंचांग_level)
			     __field(पूर्णांक, max_supported_dppclk_khz)
			     __field(पूर्णांक, max_supported_dispclk_khz)
			     __field(पूर्णांक, bw_dppclk_khz)
			     __field(पूर्णांक, bw_dispclk_khz)
	    ),
	    TP_fast_assign(
			   __entry->dispclk_khz = clk->dispclk_khz;
			   __entry->dppclk_khz = clk->dppclk_khz;
			   __entry->dcfclk_khz = clk->dcfclk_khz;
			   __entry->socclk_khz = clk->socclk_khz;
			   __entry->dcfclk_deep_sleep_khz = clk->dcfclk_deep_sleep_khz;
			   __entry->fclk_khz = clk->fclk_khz;
			   __entry->phyclk_khz = clk->phyclk_khz;
			   __entry->dramclk_khz = clk->dramclk_khz;
			   __entry->p_state_change_support = clk->p_state_change_support;
			   __entry->prev_p_state_change_support = clk->prev_p_state_change_support;
			   __entry->pwr_state = clk->pwr_state;
			   __entry->prev_p_state_change_support = clk->prev_p_state_change_support;
			   __entry->dपंचांग_level = clk->dपंचांग_level;
			   __entry->max_supported_dppclk_khz = clk->max_supported_dppclk_khz;
			   __entry->max_supported_dispclk_khz = clk->max_supported_dispclk_khz;
			   __entry->bw_dppclk_khz = clk->bw_dppclk_khz;
			   __entry->bw_dispclk_khz = clk->bw_dispclk_khz;
	    ),
	    TP_prपूर्णांकk("dispclk_khz=%d dppclk_khz=%d disp_dpp_voltage_level_khz=%d dcfclk_khz=%d socclk_khz=%d "
		      "dcfclk_deep_sleep_khz=%d fclk_khz=%d phyclk_khz=%d "
		      "dramclk_khz=%d p_state_change_support=%d "
		      "prev_p_state_change_support=%d pwr_state=%d prev_p_state_change_support=%d "
		      "dtm_level=%d max_supported_dppclk_khz=%d max_supported_dispclk_khz=%d "
		      "bw_dppclk_khz=%d bw_dispclk_khz=%d ",
		      __entry->dispclk_khz,
		      __entry->dppclk_khz,
		      __entry->disp_dpp_voltage_level_khz,
		      __entry->dcfclk_khz,
		      __entry->socclk_khz,
		      __entry->dcfclk_deep_sleep_khz,
		      __entry->fclk_khz,
		      __entry->phyclk_khz,
		      __entry->dramclk_khz,
		      __entry->p_state_change_support,
		      __entry->prev_p_state_change_support,
		      __entry->pwr_state,
		      __entry->prev_p_state_change_support,
		      __entry->dपंचांग_level,
		      __entry->max_supported_dppclk_khz,
		      __entry->max_supported_dispclk_khz,
		      __entry->bw_dppclk_khz,
		      __entry->bw_dispclk_khz
	    )
);

TRACE_EVENT(amdgpu_dm_dce_घड़ीs_state,
	    TP_PROTO(स्थिर काष्ठा dce_bw_output *clk),
	    TP_ARGS(clk),

	    TP_STRUCT__entry(
			     __field(bool, cpuc_state_change_enable)
			     __field(bool, cpup_state_change_enable)
			     __field(bool, stutter_mode_enable)
			     __field(bool, nbp_state_change_enable)
			     __field(bool, all_displays_in_sync)
			     __field(पूर्णांक, sclk_khz)
			     __field(पूर्णांक, sclk_deep_sleep_khz)
			     __field(पूर्णांक, yclk_khz)
			     __field(पूर्णांक, dispclk_khz)
			     __field(पूर्णांक, blackout_recovery_समय_us)
	    ),
	    TP_fast_assign(
			   __entry->cpuc_state_change_enable = clk->cpuc_state_change_enable;
			   __entry->cpup_state_change_enable = clk->cpup_state_change_enable;
			   __entry->stutter_mode_enable = clk->stutter_mode_enable;
			   __entry->nbp_state_change_enable = clk->nbp_state_change_enable;
			   __entry->all_displays_in_sync = clk->all_displays_in_sync;
			   __entry->sclk_khz = clk->sclk_khz;
			   __entry->sclk_deep_sleep_khz = clk->sclk_deep_sleep_khz;
			   __entry->yclk_khz = clk->yclk_khz;
			   __entry->dispclk_khz = clk->dispclk_khz;
			   __entry->blackout_recovery_समय_us = clk->blackout_recovery_समय_us;
	    ),
	    TP_prपूर्णांकk("cpuc_state_change_enable=%d cpup_state_change_enable=%d stutter_mode_enable=%d "
		      "nbp_state_change_enable=%d all_displays_in_sync=%d sclk_khz=%d sclk_deep_sleep_khz=%d "
		      "yclk_khz=%d dispclk_khz=%d blackout_recovery_time_us=%d",
		      __entry->cpuc_state_change_enable,
		      __entry->cpup_state_change_enable,
		      __entry->stutter_mode_enable,
		      __entry->nbp_state_change_enable,
		      __entry->all_displays_in_sync,
		      __entry->sclk_khz,
		      __entry->sclk_deep_sleep_khz,
		      __entry->yclk_khz,
		      __entry->dispclk_khz,
		      __entry->blackout_recovery_समय_us
	    )
);

TRACE_EVENT(amdgpu_dmub_trace_high_irq,
	TP_PROTO(uपूर्णांक32_t trace_code, uपूर्णांक32_t tick_count, uपूर्णांक32_t param0,
		 uपूर्णांक32_t param1),
	TP_ARGS(trace_code, tick_count, param0, param1),
	TP_STRUCT__entry(
		__field(uपूर्णांक32_t, trace_code)
		__field(uपूर्णांक32_t, tick_count)
		__field(uपूर्णांक32_t, param0)
		__field(uपूर्णांक32_t, param1)
		),
	TP_fast_assign(
		__entry->trace_code = trace_code;
		__entry->tick_count = tick_count;
		__entry->param0 = param0;
		__entry->param1 = param1;
	),
	TP_prपूर्णांकk("trace_code=%u tick_count=%u param0=%u param1=%u",
		  __entry->trace_code, __entry->tick_count,
		  __entry->param0, __entry->param1)
);

TRACE_EVENT(amdgpu_refresh_rate_track,
	TP_PROTO(पूर्णांक crtc_index, kसमय_प्रकार refresh_rate_ns, uपूर्णांक32_t refresh_rate_hz),
	TP_ARGS(crtc_index, refresh_rate_ns, refresh_rate_hz),
	TP_STRUCT__entry(
		__field(पूर्णांक, crtc_index)
		__field(kसमय_प्रकार, refresh_rate_ns)
		__field(uपूर्णांक32_t, refresh_rate_hz)
		),
	TP_fast_assign(
		__entry->crtc_index = crtc_index;
		__entry->refresh_rate_ns = refresh_rate_ns;
		__entry->refresh_rate_hz = refresh_rate_hz;
	),
	TP_prपूर्णांकk("crtc_index=%d refresh_rate=%dHz (%lld)",
		  __entry->crtc_index,
		  __entry->refresh_rate_hz,
		  __entry->refresh_rate_ns)
);

#पूर्ण_अगर /* _AMDGPU_DM_TRACE_H_ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता amdgpu_dm_trace
#समावेश <trace/define_trace.h>
