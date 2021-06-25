<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * DOC: atomic plane helpers
 *
 * The functions here are used by the atomic plane helper functions to
 * implement legacy plane updates (i.e., drm_plane->update_plane() and
 * drm_plane->disable_plane()).  This allows plane updates to use the
 * atomic state infraकाष्ठाure and perक्रमm plane updates as separate
 * prepare/check/commit/cleanup steps.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "i915_trace.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_display_types.h"
#समावेश "intel_pm.h"
#समावेश "intel_sprite.h"

अटल व्योम पूर्णांकel_plane_state_reset(काष्ठा पूर्णांकel_plane_state *plane_state,
				    काष्ठा पूर्णांकel_plane *plane)
अणु
	स_रखो(plane_state, 0, माप(*plane_state));

	__drm_atomic_helper_plane_state_reset(&plane_state->uapi, &plane->base);

	plane_state->scaler_id = -1;
पूर्ण

काष्ठा पूर्णांकel_plane *पूर्णांकel_plane_alloc(व्योम)
अणु
	काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	plane_state = kzalloc(माप(*plane_state), GFP_KERNEL);
	अगर (!plane_state) अणु
		kमुक्त(plane);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	पूर्णांकel_plane_state_reset(plane_state, plane);

	plane->base.state = &plane_state->uapi;

	वापस plane;
पूर्ण

व्योम पूर्णांकel_plane_मुक्त(काष्ठा पूर्णांकel_plane *plane)
अणु
	पूर्णांकel_plane_destroy_state(&plane->base, plane->base.state);
	kमुक्त(plane);
पूर्ण

/**
 * पूर्णांकel_plane_duplicate_state - duplicate plane state
 * @plane: drm plane
 *
 * Allocates and वापसs a copy of the plane state (both common and
 * Intel-specअगरic) क्रम the specअगरied plane.
 *
 * Returns: The newly allocated plane state, or शून्य on failure.
 */
काष्ठा drm_plane_state *
पूर्णांकel_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा पूर्णांकel_plane_state *पूर्णांकel_state;

	पूर्णांकel_state = to_पूर्णांकel_plane_state(plane->state);
	पूर्णांकel_state = kmemdup(पूर्णांकel_state, माप(*पूर्णांकel_state), GFP_KERNEL);

	अगर (!पूर्णांकel_state)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &पूर्णांकel_state->uapi);

	पूर्णांकel_state->vma = शून्य;
	पूर्णांकel_state->flags = 0;

	/* add reference to fb */
	अगर (पूर्णांकel_state->hw.fb)
		drm_framebuffer_get(पूर्णांकel_state->hw.fb);

	वापस &पूर्णांकel_state->uapi;
पूर्ण

/**
 * पूर्णांकel_plane_destroy_state - destroy plane state
 * @plane: drm plane
 * @state: state object to destroy
 *
 * Destroys the plane state (both common and Intel-specअगरic) क्रम the
 * specअगरied plane.
 */
व्योम
पूर्णांकel_plane_destroy_state(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *state)
अणु
	काष्ठा पूर्णांकel_plane_state *plane_state = to_पूर्णांकel_plane_state(state);
	drm_WARN_ON(plane->dev, plane_state->vma);

	__drm_atomic_helper_plane_destroy_state(&plane_state->uapi);
	अगर (plane_state->hw.fb)
		drm_framebuffer_put(plane_state->hw.fb);
	kमुक्त(plane_state);
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_plane_pixel_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक src_w, src_h, dst_w, dst_h;
	अचिन्हित पूर्णांक pixel_rate = crtc_state->pixel_rate;

	src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	dst_w = drm_rect_width(&plane_state->uapi.dst);
	dst_h = drm_rect_height(&plane_state->uapi.dst);

	/* Downscaling limits the maximum pixel rate */
	dst_w = min(src_w, dst_w);
	dst_h = min(src_h, dst_h);

	वापस DIV_ROUND_UP_ULL(mul_u32_u32(pixel_rate, src_w * src_h),
				dst_w * dst_h);
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_plane_data_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp;
	अचिन्हित पूर्णांक pixel_rate;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	pixel_rate = पूर्णांकel_plane_pixel_rate(crtc_state, plane_state);

	cpp = fb->क्रमmat->cpp[0];

	/*
	 * Based on HSD#:1408715493
	 * NV12 cpp == 4, P010 cpp == 8
	 *
	 * FIXME what is the logic behind this?
	 */
	अगर (fb->क्रमmat->is_yuv && fb->क्रमmat->num_planes > 1)
		cpp *= 4;

	वापस pixel_rate * cpp;
पूर्ण

पूर्णांक पूर्णांकel_plane_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_plane *plane,
			       bool *need_cdclk_calc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
		पूर्णांकel_atomic_get_new_plane_state(state, plane);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(plane_state->hw.crtc);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *cdclk_state;
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state;
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;

	अगर (!plane_state->uapi.visible || !plane->min_cdclk)
		वापस 0;

	old_crtc_state = पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	new_crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	new_crtc_state->min_cdclk[plane->id] =
		plane->min_cdclk(new_crtc_state, plane_state);

	/*
	 * No need to check against the cdclk state अगर
	 * the min cdclk क्रम the plane करोesn't increase.
	 *
	 * Ie. we only ever increase the cdclk due to plane
	 * requirements. This can reduce back and क्रमth
	 * display blinking due to स्थिरant cdclk changes.
	 */
	अगर (new_crtc_state->min_cdclk[plane->id] <=
	    old_crtc_state->min_cdclk[plane->id])
		वापस 0;

	cdclk_state = पूर्णांकel_atomic_get_cdclk_state(state);
	अगर (IS_ERR(cdclk_state))
		वापस PTR_ERR(cdclk_state);

	/*
	 * No need to recalculate the cdclk state अगर
	 * the min cdclk क्रम the pipe करोesn't increase.
	 *
	 * Ie. we only ever increase the cdclk due to plane
	 * requirements. This can reduce back and क्रमth
	 * display blinking due to स्थिरant cdclk changes.
	 */
	अगर (new_crtc_state->min_cdclk[plane->id] <=
	    cdclk_state->min_cdclk[crtc->pipe])
		वापस 0;

	drm_dbg_kms(&dev_priv->drm,
		    "[PLANE:%d:%s] min cdclk (%d kHz) > [CRTC:%d:%s] min cdclk (%d kHz)\n",
		    plane->base.base.id, plane->base.name,
		    new_crtc_state->min_cdclk[plane->id],
		    crtc->base.base.id, crtc->base.name,
		    cdclk_state->min_cdclk[crtc->pipe]);
	*need_cdclk_calc = true;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_plane_clear_hw_state(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अगर (plane_state->hw.fb)
		drm_framebuffer_put(plane_state->hw.fb);

	स_रखो(&plane_state->hw, 0, माप(plane_state->hw));
पूर्ण

व्योम पूर्णांकel_plane_copy_uapi_to_hw_state(काष्ठा पूर्णांकel_plane_state *plane_state,
				       स्थिर काष्ठा पूर्णांकel_plane_state *from_plane_state,
				       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	पूर्णांकel_plane_clear_hw_state(plane_state);

	/*
	 * For the bigjoiner slave uapi.crtc will poपूर्णांक at
	 * the master crtc. So we explicitly assign the right
	 * slave crtc to hw.crtc. uapi.crtc!=शून्य simply indicates
	 * the plane is logically enabled on the uapi level.
	 */
	plane_state->hw.crtc = from_plane_state->uapi.crtc ? &crtc->base : शून्य;

	plane_state->hw.fb = from_plane_state->uapi.fb;
	अगर (plane_state->hw.fb)
		drm_framebuffer_get(plane_state->hw.fb);

	plane_state->hw.alpha = from_plane_state->uapi.alpha;
	plane_state->hw.pixel_blend_mode =
		from_plane_state->uapi.pixel_blend_mode;
	plane_state->hw.rotation = from_plane_state->uapi.rotation;
	plane_state->hw.color_encoding = from_plane_state->uapi.color_encoding;
	plane_state->hw.color_range = from_plane_state->uapi.color_range;
	plane_state->hw.scaling_filter = from_plane_state->uapi.scaling_filter;

	plane_state->uapi.src = drm_plane_state_src(&from_plane_state->uapi);
	plane_state->uapi.dst = drm_plane_state_dest(&from_plane_state->uapi);
पूर्ण

व्योम पूर्णांकel_plane_copy_hw_state(काष्ठा पूर्णांकel_plane_state *plane_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *from_plane_state)
अणु
	पूर्णांकel_plane_clear_hw_state(plane_state);

	स_नकल(&plane_state->hw, &from_plane_state->hw,
	       माप(plane_state->hw));

	अगर (plane_state->hw.fb)
		drm_framebuffer_get(plane_state->hw.fb);
पूर्ण

व्योम पूर्णांकel_plane_set_invisible(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);

	crtc_state->active_planes &= ~BIT(plane->id);
	crtc_state->nv12_planes &= ~BIT(plane->id);
	crtc_state->c8_planes &= ~BIT(plane->id);
	crtc_state->data_rate[plane->id] = 0;
	crtc_state->min_cdclk[plane->id] = 0;

	plane_state->uapi.visible = false;
पूर्ण

पूर्णांक पूर्णांकel_plane_atomic_check_with_state(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
					काष्ठा पूर्णांकel_crtc_state *new_crtc_state,
					स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state,
					काष्ठा पूर्णांकel_plane_state *new_plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(new_plane_state->uapi.plane);
	स्थिर काष्ठा drm_framebuffer *fb = new_plane_state->hw.fb;
	पूर्णांक ret;

	पूर्णांकel_plane_set_invisible(new_crtc_state, new_plane_state);
	new_crtc_state->enabled_planes &= ~BIT(plane->id);

	अगर (!new_plane_state->hw.crtc && !old_plane_state->hw.crtc)
		वापस 0;

	ret = plane->check_plane(new_crtc_state, new_plane_state);
	अगर (ret)
		वापस ret;

	अगर (fb)
		new_crtc_state->enabled_planes |= BIT(plane->id);

	/* FIXME pre-g4x करोn't work like this */
	अगर (new_plane_state->uapi.visible)
		new_crtc_state->active_planes |= BIT(plane->id);

	अगर (new_plane_state->uapi.visible &&
	    पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier))
		new_crtc_state->nv12_planes |= BIT(plane->id);

	अगर (new_plane_state->uapi.visible &&
	    fb->क्रमmat->क्रमmat == DRM_FORMAT_C8)
		new_crtc_state->c8_planes |= BIT(plane->id);

	अगर (new_plane_state->uapi.visible || old_plane_state->uapi.visible)
		new_crtc_state->update_planes |= BIT(plane->id);

	new_crtc_state->data_rate[plane->id] =
		पूर्णांकel_plane_data_rate(new_crtc_state, new_plane_state);

	वापस पूर्णांकel_plane_atomic_calc_changes(old_crtc_state, new_crtc_state,
					       old_plane_state, new_plane_state);
पूर्ण

अटल काष्ठा पूर्णांकel_plane *
पूर्णांकel_crtc_get_plane(काष्ठा पूर्णांकel_crtc *crtc, क्रमागत plane_id plane_id)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&i915->drm, crtc, plane) अणु
		अगर (plane->id == plane_id)
			वापस plane;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक पूर्णांकel_plane_atomic_check(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_plane_state *new_plane_state =
		पूर्णांकel_atomic_get_new_plane_state(state, plane);
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state =
		पूर्णांकel_atomic_get_old_plane_state(state, plane);
	स्थिर काष्ठा पूर्णांकel_plane_state *new_master_plane_state;
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(i915, plane->pipe);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (new_crtc_state && new_crtc_state->bigjoiner_slave) अणु
		काष्ठा पूर्णांकel_plane *master_plane =
			पूर्णांकel_crtc_get_plane(new_crtc_state->bigjoiner_linked_crtc,
					     plane->id);

		new_master_plane_state =
			पूर्णांकel_atomic_get_new_plane_state(state, master_plane);
	पूर्ण अन्यथा अणु
		new_master_plane_state = new_plane_state;
	पूर्ण

	पूर्णांकel_plane_copy_uapi_to_hw_state(new_plane_state,
					  new_master_plane_state,
					  crtc);

	new_plane_state->uapi.visible = false;
	अगर (!new_crtc_state)
		वापस 0;

	वापस पूर्णांकel_plane_atomic_check_with_state(old_crtc_state,
						   new_crtc_state,
						   old_plane_state,
						   new_plane_state);
पूर्ण

अटल काष्ठा पूर्णांकel_plane *
skl_next_plane_to_commit(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा skl_ddb_entry entries_y[I915_MAX_PLANES],
			 काष्ठा skl_ddb_entry entries_uv[I915_MAX_PLANES],
			 अचिन्हित पूर्णांक *update_mask)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	अगर (*update_mask == 0)
		वापस शून्य;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		क्रमागत plane_id plane_id = plane->id;

		अगर (crtc->pipe != plane->pipe ||
		    !(*update_mask & BIT(plane_id)))
			जारी;

		अगर (skl_ddb_allocation_overlaps(&crtc_state->wm.skl.plane_ddb_y[plane_id],
						entries_y,
						I915_MAX_PLANES, plane_id) ||
		    skl_ddb_allocation_overlaps(&crtc_state->wm.skl.plane_ddb_uv[plane_id],
						entries_uv,
						I915_MAX_PLANES, plane_id))
			जारी;

		*update_mask &= ~BIT(plane_id);
		entries_y[plane_id] = crtc_state->wm.skl.plane_ddb_y[plane_id];
		entries_uv[plane_id] = crtc_state->wm.skl.plane_ddb_uv[plane_id];

		वापस plane;
	पूर्ण

	/* should never happen */
	drm_WARN_ON(state->base.dev, 1);

	वापस शून्य;
पूर्ण

व्योम पूर्णांकel_update_plane(काष्ठा पूर्णांकel_plane *plane,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	trace_पूर्णांकel_update_plane(&plane->base, crtc);

	अगर (crtc_state->uapi.async_flip && plane->async_flip)
		plane->async_flip(plane, crtc_state, plane_state, true);
	अन्यथा
		plane->update_plane(plane, crtc_state, plane_state);
पूर्ण

व्योम पूर्णांकel_disable_plane(काष्ठा पूर्णांकel_plane *plane,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	trace_पूर्णांकel_disable_plane(&plane->base, crtc);
	plane->disable_plane(plane, crtc_state);
पूर्ण

व्योम skl_update_planes_on_crtc(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा skl_ddb_entry entries_y[I915_MAX_PLANES];
	काष्ठा skl_ddb_entry entries_uv[I915_MAX_PLANES];
	u32 update_mask = new_crtc_state->update_planes;
	काष्ठा पूर्णांकel_plane *plane;

	स_नकल(entries_y, old_crtc_state->wm.skl.plane_ddb_y,
	       माप(old_crtc_state->wm.skl.plane_ddb_y));
	स_नकल(entries_uv, old_crtc_state->wm.skl.plane_ddb_uv,
	       माप(old_crtc_state->wm.skl.plane_ddb_uv));

	जबतक ((plane = skl_next_plane_to_commit(state, crtc,
						 entries_y, entries_uv,
						 &update_mask))) अणु
		काष्ठा पूर्णांकel_plane_state *new_plane_state =
			पूर्णांकel_atomic_get_new_plane_state(state, plane);

		अगर (new_plane_state->uapi.visible ||
		    new_plane_state->planar_slave) अणु
			पूर्णांकel_update_plane(plane, new_crtc_state, new_plane_state);
		पूर्ण अन्यथा अणु
			पूर्णांकel_disable_plane(plane, new_crtc_state);
		पूर्ण
	पूर्ण
पूर्ण

व्योम i9xx_update_planes_on_crtc(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	u32 update_mask = new_crtc_state->update_planes;
	काष्ठा पूर्णांकel_plane_state *new_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, new_plane_state, i) अणु
		अगर (crtc->pipe != plane->pipe ||
		    !(update_mask & BIT(plane->id)))
			जारी;

		अगर (new_plane_state->uapi.visible)
			पूर्णांकel_update_plane(plane, new_crtc_state, new_plane_state);
		अन्यथा
			पूर्णांकel_disable_plane(plane, new_crtc_state);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_atomic_plane_check_clipping(काष्ठा पूर्णांकel_plane_state *plane_state,
				      काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      पूर्णांक min_scale, पूर्णांक max_scale,
				      bool can_position)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा drm_rect *src = &plane_state->uapi.src;
	काष्ठा drm_rect *dst = &plane_state->uapi.dst;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	काष्ठा drm_rect clip = अणुपूर्ण;
	पूर्णांक hscale, vscale;

	अगर (!fb) अणु
		plane_state->uapi.visible = false;
		वापस 0;
	पूर्ण

	drm_rect_rotate(src, fb->width << 16, fb->height << 16, rotation);

	/* Check scaling */
	hscale = drm_rect_calc_hscale(src, dst, min_scale, max_scale);
	vscale = drm_rect_calc_vscale(src, dst, min_scale, max_scale);
	अगर (hscale < 0 || vscale < 0) अणु
		DRM_DEBUG_KMS("Invalid scaling of plane\n");
		drm_rect_debug_prपूर्णांक("src: ", src, true);
		drm_rect_debug_prपूर्णांक("dst: ", dst, false);
		वापस -दुस्फल;
	पूर्ण

	अगर (crtc_state->hw.enable) अणु
		clip.x2 = crtc_state->pipe_src_w;
		clip.y2 = crtc_state->pipe_src_h;
	पूर्ण

	/* right side of the image is on the slave crtc, adjust dst to match */
	अगर (crtc_state->bigjoiner_slave)
		drm_rect_translate(dst, -crtc_state->pipe_src_w, 0);

	/*
	 * FIXME: This might need further adjusपंचांगent क्रम seamless scaling
	 * with phase inक्रमmation, क्रम the 2p2 and 2p1 scenarios.
	 */
	plane_state->uapi.visible = drm_rect_clip_scaled(src, dst, &clip);

	drm_rect_rotate_inv(src, fb->width << 16, fb->height << 16, rotation);

	अगर (!can_position && plane_state->uapi.visible &&
	    !drm_rect_equals(dst, &clip)) अणु
		DRM_DEBUG_KMS("Plane must cover entire CRTC\n");
		drm_rect_debug_prपूर्णांक("dst: ", dst, false);
		drm_rect_debug_prपूर्णांक("clip: ", &clip, false);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा drm_plane_helper_funcs पूर्णांकel_plane_helper_funcs = अणु
	.prepare_fb = पूर्णांकel_prepare_plane_fb,
	.cleanup_fb = पूर्णांकel_cleanup_plane_fb,
पूर्ण;
