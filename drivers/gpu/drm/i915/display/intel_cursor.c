<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश <linux/kernel.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "intel_atomic.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_cursor.h"
#समावेश "intel_display_types.h"
#समावेश "intel_display.h"
#समावेश "intel_fb.h"

#समावेश "intel_frontbuffer.h"
#समावेश "intel_pm.h"
#समावेश "intel_psr.h"
#समावेश "intel_sprite.h"

/* Cursor क्रमmats */
अटल स्थिर u32 पूर्णांकel_cursor_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर u64 cursor_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल u32 पूर्णांकel_cursor_base(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	स्थिर काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(fb);
	u32 base;

	अगर (INTEL_INFO(dev_priv)->display.cursor_needs_physical)
		base = sg_dma_address(obj->mm.pages->sgl);
	अन्यथा
		base = पूर्णांकel_plane_ggtt_offset(plane_state);

	वापस base + plane_state->view.color_plane[0].offset;
पूर्ण

अटल u32 पूर्णांकel_cursor_position(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	पूर्णांक x = plane_state->uapi.dst.x1;
	पूर्णांक y = plane_state->uapi.dst.y1;
	u32 pos = 0;

	अगर (x < 0) अणु
		pos |= CURSOR_POS_SIGN << CURSOR_X_SHIFT;
		x = -x;
	पूर्ण
	pos |= x << CURSOR_X_SHIFT;

	अगर (y < 0) अणु
		pos |= CURSOR_POS_SIGN << CURSOR_Y_SHIFT;
		y = -y;
	पूर्ण
	pos |= y << CURSOR_Y_SHIFT;

	वापस pos;
पूर्ण

अटल bool पूर्णांकel_cursor_size_ok(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_mode_config *config =
		&plane_state->uapi.plane->dev->mode_config;
	पूर्णांक width = drm_rect_width(&plane_state->uapi.dst);
	पूर्णांक height = drm_rect_height(&plane_state->uapi.dst);

	वापस width > 0 && width <= config->cursor_width &&
		height > 0 && height <= config->cursor_height;
पूर्ण

अटल पूर्णांक पूर्णांकel_cursor_check_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	पूर्णांक src_x, src_y;
	u32 offset;
	पूर्णांक ret;

	ret = पूर्णांकel_plane_compute_gtt(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	src_x = plane_state->uapi.src.x1 >> 16;
	src_y = plane_state->uapi.src.y1 >> 16;

	पूर्णांकel_add_fb_offsets(&src_x, &src_y, plane_state, 0);
	offset = पूर्णांकel_plane_compute_aligned_offset(&src_x, &src_y,
						    plane_state, 0);

	अगर (src_x != 0 || src_y != 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Arbitrary cursor panning not supported\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Put the final coordinates back so that the src
	 * coordinate checks will see the right values.
	 */
	drm_rect_translate_to(&plane_state->uapi.src,
			      src_x << 16, src_y << 16);

	/* ILK+ करो this स्वतःmagically in hardware */
	अगर (HAS_GMCH(dev_priv) && rotation & DRM_MODE_ROTATE_180) अणु
		स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
		पूर्णांक src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
		पूर्णांक src_h = drm_rect_height(&plane_state->uapi.src) >> 16;

		offset += (src_h * src_w - 1) * fb->क्रमmat->cpp[0];
	पूर्ण

	plane_state->view.color_plane[0].offset = offset;
	plane_state->view.color_plane[0].x = src_x;
	plane_state->view.color_plane[0].y = src_y;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_check_cursor(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा drm_i915_निजी *i915 = to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_rect src = plane_state->uapi.src;
	स्थिर काष्ठा drm_rect dst = plane_state->uapi.dst;
	पूर्णांक ret;

	अगर (fb && fb->modअगरier != DRM_FORMAT_MOD_LINEAR) अणु
		drm_dbg_kms(&i915->drm, "cursor cannot be tiled\n");
		वापस -EINVAL;
	पूर्ण

	ret = पूर्णांकel_atomic_plane_check_clipping(plane_state, crtc_state,
						DRM_PLANE_HELPER_NO_SCALING,
						DRM_PLANE_HELPER_NO_SCALING,
						true);
	अगर (ret)
		वापस ret;

	/* Use the unclipped src/dst rectangles, which we program to hw */
	plane_state->uapi.src = src;
	plane_state->uapi.dst = dst;

	ret = पूर्णांकel_cursor_check_surface(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	ret = पूर्णांकel_plane_check_src_coordinates(plane_state);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
i845_cursor_max_stride(काष्ठा पूर्णांकel_plane *plane,
		       u32 pixel_क्रमmat, u64 modअगरier,
		       अचिन्हित पूर्णांक rotation)
अणु
	वापस 2048;
पूर्ण

अटल u32 i845_cursor_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 cntl = 0;

	अगर (crtc_state->gamma_enable)
		cntl |= CURSOR_GAMMA_ENABLE;

	वापस cntl;
पूर्ण

अटल u32 i845_cursor_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	वापस CURSOR_ENABLE |
		CURSOR_FORMAT_ARGB |
		CURSOR_STRIDE(plane_state->view.color_plane[0].stride);
पूर्ण

अटल bool i845_cursor_size_ok(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	पूर्णांक width = drm_rect_width(&plane_state->uapi.dst);

	/*
	 * 845g/865g are only limited by the width of their cursors,
	 * the height is arbitrary up to the precision of the रेजिस्टर.
	 */
	वापस पूर्णांकel_cursor_size_ok(plane_state) && IS_ALIGNED(width, 64);
पूर्ण

अटल पूर्णांक i845_check_cursor(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा drm_i915_निजी *i915 = to_i915(plane_state->uapi.plane->dev);
	पूर्णांक ret;

	ret = पूर्णांकel_check_cursor(crtc_state, plane_state);
	अगर (ret)
		वापस ret;

	/* अगर we want to turn off the cursor ignore width and height */
	अगर (!fb)
		वापस 0;

	/* Check क्रम which cursor types we support */
	अगर (!i845_cursor_size_ok(plane_state)) अणु
		drm_dbg_kms(&i915->drm,
			    "Cursor dimension %dx%d not supported\n",
			    drm_rect_width(&plane_state->uapi.dst),
			    drm_rect_height(&plane_state->uapi.dst));
		वापस -EINVAL;
	पूर्ण

	drm_WARN_ON(&i915->drm, plane_state->uapi.visible &&
		    plane_state->view.color_plane[0].stride != fb->pitches[0]);

	चयन (fb->pitches[0]) अणु
	हाल 256:
	हाल 512:
	हाल 1024:
	हाल 2048:
		अवरोध;
	शेष:
		 drm_dbg_kms(&i915->drm, "Invalid cursor stride (%u)\n",
			     fb->pitches[0]);
		वापस -EINVAL;
	पूर्ण

	plane_state->ctl = i845_cursor_ctl(crtc_state, plane_state);

	वापस 0;
पूर्ण

अटल व्योम i845_update_cursor(काष्ठा पूर्णांकel_plane *plane,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	u32 cntl = 0, base = 0, pos = 0, size = 0;
	अचिन्हित दीर्घ irqflags;

	अगर (plane_state && plane_state->uapi.visible) अणु
		अचिन्हित पूर्णांक width = drm_rect_width(&plane_state->uapi.dst);
		अचिन्हित पूर्णांक height = drm_rect_height(&plane_state->uapi.dst);

		cntl = plane_state->ctl |
			i845_cursor_ctl_crtc(crtc_state);

		size = (height << 12) | width;

		base = पूर्णांकel_cursor_base(plane_state);
		pos = पूर्णांकel_cursor_position(plane_state);
	पूर्ण

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/* On these chipsets we can only modअगरy the base/size/stride
	 * whilst the cursor is disabled.
	 */
	अगर (plane->cursor.base != base ||
	    plane->cursor.size != size ||
	    plane->cursor.cntl != cntl) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURCNTR(PIPE_A), 0);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURBASE(PIPE_A), base);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURSIZE, size);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURPOS(PIPE_A), pos);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURCNTR(PIPE_A), cntl);

		plane->cursor.base = base;
		plane->cursor.size = size;
		plane->cursor.cntl = cntl;
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURPOS(PIPE_A), pos);
	पूर्ण

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम i845_disable_cursor(काष्ठा पूर्णांकel_plane *plane,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	i845_update_cursor(plane, crtc_state, शून्य);
पूर्ण

अटल bool i845_cursor_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
				     क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(PIPE_A);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_de_पढ़ो(dev_priv, CURCNTR(PIPE_A)) & CURSOR_ENABLE;

	*pipe = PIPE_A;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
i9xx_cursor_max_stride(काष्ठा पूर्णांकel_plane *plane,
		       u32 pixel_क्रमmat, u64 modअगरier,
		       अचिन्हित पूर्णांक rotation)
अणु
	वापस plane->base.dev->mode_config.cursor_width * 4;
पूर्ण

अटल u32 i9xx_cursor_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 cntl = 0;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		वापस cntl;

	अगर (crtc_state->gamma_enable)
		cntl = MCURSOR_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		cntl |= MCURSOR_PIPE_CSC_ENABLE;

	अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv))
		cntl |= MCURSOR_PIPE_SELECT(crtc->pipe);

	वापस cntl;
पूर्ण

अटल u32 i9xx_cursor_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	u32 cntl = 0;

	अगर (IS_SANDYBRIDGE(dev_priv) || IS_IVYBRIDGE(dev_priv))
		cntl |= MCURSOR_TRICKLE_FEED_DISABLE;

	चयन (drm_rect_width(&plane_state->uapi.dst)) अणु
	हाल 64:
		cntl |= MCURSOR_MODE_64_ARGB_AX;
		अवरोध;
	हाल 128:
		cntl |= MCURSOR_MODE_128_ARGB_AX;
		अवरोध;
	हाल 256:
		cntl |= MCURSOR_MODE_256_ARGB_AX;
		अवरोध;
	शेष:
		MISSING_CASE(drm_rect_width(&plane_state->uapi.dst));
		वापस 0;
	पूर्ण

	अगर (plane_state->hw.rotation & DRM_MODE_ROTATE_180)
		cntl |= MCURSOR_ROTATE_180;

	वापस cntl;
पूर्ण

अटल bool i9xx_cursor_size_ok(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	पूर्णांक width = drm_rect_width(&plane_state->uapi.dst);
	पूर्णांक height = drm_rect_height(&plane_state->uapi.dst);

	अगर (!पूर्णांकel_cursor_size_ok(plane_state))
		वापस false;

	/* Cursor width is limited to a few घातer-of-two sizes */
	चयन (width) अणु
	हाल 256:
	हाल 128:
	हाल 64:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/*
	 * IVB+ have CUR_FBC_CTL which allows an arbitrary cursor
	 * height from 8 lines up to the cursor width, when the
	 * cursor is not rotated. Everything अन्यथा requires square
	 * cursors.
	 */
	अगर (HAS_CUR_FBC(dev_priv) &&
	    plane_state->hw.rotation & DRM_MODE_ROTATE_0) अणु
		अगर (height < 8 || height > width)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (height != width)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक i9xx_check_cursor(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	क्रमागत pipe pipe = plane->pipe;
	पूर्णांक ret;

	ret = पूर्णांकel_check_cursor(crtc_state, plane_state);
	अगर (ret)
		वापस ret;

	/* अगर we want to turn off the cursor ignore width and height */
	अगर (!fb)
		वापस 0;

	/* Check क्रम which cursor types we support */
	अगर (!i9xx_cursor_size_ok(plane_state)) अणु
		drm_dbg(&dev_priv->drm,
			"Cursor dimension %dx%d not supported\n",
			drm_rect_width(&plane_state->uapi.dst),
			drm_rect_height(&plane_state->uapi.dst));
		वापस -EINVAL;
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, plane_state->uapi.visible &&
		    plane_state->view.color_plane[0].stride != fb->pitches[0]);

	अगर (fb->pitches[0] !=
	    drm_rect_width(&plane_state->uapi.dst) * fb->क्रमmat->cpp[0]) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Invalid cursor stride (%u) (cursor width %d)\n",
			    fb->pitches[0],
			    drm_rect_width(&plane_state->uapi.dst));
		वापस -EINVAL;
	पूर्ण

	/*
	 * There's something wrong with the cursor on CHV pipe C.
	 * If it straddles the left edge of the screen then
	 * moving it away from the edge or disabling it often
	 * results in a pipe underrun, and often that can lead to
	 * dead pipe (स्थिरant underrun reported, and it scans
	 * out just a solid color). To recover from that, the
	 * display घातer well must be turned off and on again.
	 * Refuse the put the cursor पूर्णांकo that compromised position.
	 */
	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_C &&
	    plane_state->uapi.visible && plane_state->uapi.dst.x1 < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "CHV cursor C not allowed to straddle the left screen edge\n");
		वापस -EINVAL;
	पूर्ण

	plane_state->ctl = i9xx_cursor_ctl(crtc_state, plane_state);

	वापस 0;
पूर्ण

अटल व्योम i9xx_update_cursor(काष्ठा पूर्णांकel_plane *plane,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;
	u32 cntl = 0, base = 0, pos = 0, fbc_ctl = 0;
	अचिन्हित दीर्घ irqflags;

	अगर (plane_state && plane_state->uapi.visible) अणु
		पूर्णांक width = drm_rect_width(&plane_state->uapi.dst);
		पूर्णांक height = drm_rect_height(&plane_state->uapi.dst);

		cntl = plane_state->ctl |
			i9xx_cursor_ctl_crtc(crtc_state);

		अगर (width != height)
			fbc_ctl = CUR_FBC_CTL_EN | (height - 1);

		base = पूर्णांकel_cursor_base(plane_state);
		pos = पूर्णांकel_cursor_position(plane_state);
	पूर्ण

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	/*
	 * On some platक्रमms writing CURCNTR first will also
	 * cause CURPOS to be armed by the CURBASE ग_लिखो.
	 * Without the CURCNTR ग_लिखो the CURPOS ग_लिखो would
	 * arm itself. Thus we always update CURCNTR beक्रमe
	 * CURPOS.
	 *
	 * On other platक्रमms CURPOS always requires the
	 * CURBASE ग_लिखो to arm the update. Additonally
	 * a ग_लिखो to any of the cursor रेजिस्टर will cancel
	 * an alपढ़ोy armed cursor update. Thus leaving out
	 * the CURBASE ग_लिखो after CURPOS could lead to a
	 * cursor that करोesn't appear to move, or even change
	 * shape. Thus we always ग_लिखो CURBASE.
	 *
	 * The other रेजिस्टरs are armed by the CURBASE ग_लिखो
	 * except when the plane is getting enabled at which समय
	 * the CURCNTR ग_लिखो arms the update.
	 */

	अगर (DISPLAY_VER(dev_priv) >= 9)
		skl_ग_लिखो_cursor_wm(plane, crtc_state);

	अगर (!पूर्णांकel_crtc_needs_modeset(crtc_state))
		पूर्णांकel_psr2_program_plane_sel_fetch(plane, crtc_state, plane_state, 0);

	अगर (plane->cursor.base != base ||
	    plane->cursor.size != fbc_ctl ||
	    plane->cursor.cntl != cntl) अणु
		अगर (HAS_CUR_FBC(dev_priv))
			पूर्णांकel_de_ग_लिखो_fw(dev_priv, CUR_FBC_CTL(pipe),
					  fbc_ctl);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURCNTR(pipe), cntl);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURPOS(pipe), pos);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURBASE(pipe), base);

		plane->cursor.base = base;
		plane->cursor.size = fbc_ctl;
		plane->cursor.cntl = cntl;
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURPOS(pipe), pos);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, CURBASE(pipe), base);
	पूर्ण

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम i9xx_disable_cursor(काष्ठा पूर्णांकel_plane *plane,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	i9xx_update_cursor(plane, crtc_state, शून्य);
पूर्ण

अटल bool i9xx_cursor_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
				     क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;
	u32 val;

	/*
	 * Not 100% correct क्रम planes that can move between pipes,
	 * but that's only the case for gen2-3 which don't have any
	 * display घातer wells.
	 */
	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, CURCNTR(plane->pipe));

	ret = val & MCURSOR_MODE;

	अगर (DISPLAY_VER(dev_priv) >= 5 || IS_G4X(dev_priv))
		*pipe = plane->pipe;
	अन्यथा
		*pipe = (val & MCURSOR_PIPE_SELECT_MASK) >>
			MCURSOR_PIPE_SELECT_SHIFT;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_cursor_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					      u32 क्रमmat, u64 modअगरier)
अणु
	वापस modअगरier == DRM_FORMAT_MOD_LINEAR &&
		क्रमmat == DRM_FORMAT_ARGB8888;
पूर्ण

अटल पूर्णांक
पूर्णांकel_legacy_cursor_update(काष्ठा drm_plane *_plane,
			   काष्ठा drm_crtc *_crtc,
			   काष्ठा drm_framebuffer *fb,
			   पूर्णांक crtc_x, पूर्णांक crtc_y,
			   अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
			   u32 src_x, u32 src_y,
			   u32 src_w, u32 src_h,
			   काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(_plane);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(_crtc);
	काष्ठा पूर्णांकel_plane_state *old_plane_state =
		to_पूर्णांकel_plane_state(plane->base.state);
	काष्ठा पूर्णांकel_plane_state *new_plane_state;
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	पूर्णांक ret;

	/*
	 * When crtc is inactive or there is a modeset pending,
	 * रुको क्रम it to complete in the slowpath
	 *
	 * FIXME bigjoiner fastpath would be good
	 */
	अगर (!crtc_state->hw.active || पूर्णांकel_crtc_needs_modeset(crtc_state) ||
	    crtc_state->update_pipe || crtc_state->bigjoiner)
		जाओ slow;

	/*
	 * Don't करो an async update अगर there is an outstanding commit modअगरying
	 * the plane.  This prevents our async update's changes from getting
	 * overridden by a previous synchronous update's state.
	 */
	अगर (old_plane_state->uapi.commit &&
	    !try_रुको_क्रम_completion(&old_plane_state->uapi.commit->hw_करोne))
		जाओ slow;

	/*
	 * If any parameters change that may affect watermarks,
	 * take the slowpath. Only changing fb or position should be
	 * in the fastpath.
	 */
	अगर (old_plane_state->uapi.crtc != &crtc->base ||
	    old_plane_state->uapi.src_w != src_w ||
	    old_plane_state->uapi.src_h != src_h ||
	    old_plane_state->uapi.crtc_w != crtc_w ||
	    old_plane_state->uapi.crtc_h != crtc_h ||
	    !old_plane_state->uapi.fb != !fb)
		जाओ slow;

	new_plane_state = to_पूर्णांकel_plane_state(पूर्णांकel_plane_duplicate_state(&plane->base));
	अगर (!new_plane_state)
		वापस -ENOMEM;

	new_crtc_state = to_पूर्णांकel_crtc_state(पूर्णांकel_crtc_duplicate_state(&crtc->base));
	अगर (!new_crtc_state) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	drm_atomic_set_fb_क्रम_plane(&new_plane_state->uapi, fb);

	new_plane_state->uapi.src_x = src_x;
	new_plane_state->uapi.src_y = src_y;
	new_plane_state->uapi.src_w = src_w;
	new_plane_state->uapi.src_h = src_h;
	new_plane_state->uapi.crtc_x = crtc_x;
	new_plane_state->uapi.crtc_y = crtc_y;
	new_plane_state->uapi.crtc_w = crtc_w;
	new_plane_state->uapi.crtc_h = crtc_h;

	पूर्णांकel_plane_copy_uapi_to_hw_state(new_plane_state, new_plane_state, crtc);

	ret = पूर्णांकel_plane_atomic_check_with_state(crtc_state, new_crtc_state,
						  old_plane_state, new_plane_state);
	अगर (ret)
		जाओ out_मुक्त;

	ret = पूर्णांकel_plane_pin_fb(new_plane_state);
	अगर (ret)
		जाओ out_मुक्त;

	पूर्णांकel_frontbuffer_flush(to_पूर्णांकel_frontbuffer(new_plane_state->hw.fb),
				ORIGIN_FLIP);
	पूर्णांकel_frontbuffer_track(to_पूर्णांकel_frontbuffer(old_plane_state->hw.fb),
				to_पूर्णांकel_frontbuffer(new_plane_state->hw.fb),
				plane->frontbuffer_bit);

	/* Swap plane state */
	plane->base.state = &new_plane_state->uapi;

	/*
	 * We cannot swap crtc_state as it may be in use by an atomic commit or
	 * page flip that's running simultaneously. If we swap crtc_state and
	 * destroy the old state, we will cause a use-after-मुक्त there.
	 *
	 * Only update active_planes, which is needed क्रम our पूर्णांकernal
	 * bookkeeping. Either value will करो the right thing when updating
	 * planes atomically. If the cursor was part of the atomic update then
	 * we would have taken the slowpath.
	 */
	crtc_state->active_planes = new_crtc_state->active_planes;

	अगर (new_plane_state->uapi.visible)
		पूर्णांकel_update_plane(plane, crtc_state, new_plane_state);
	अन्यथा
		पूर्णांकel_disable_plane(plane, crtc_state);

	पूर्णांकel_plane_unpin_fb(old_plane_state);

out_मुक्त:
	अगर (new_crtc_state)
		पूर्णांकel_crtc_destroy_state(&crtc->base, &new_crtc_state->uapi);
	अगर (ret)
		पूर्णांकel_plane_destroy_state(&plane->base, &new_plane_state->uapi);
	अन्यथा
		पूर्णांकel_plane_destroy_state(&plane->base, &old_plane_state->uapi);
	वापस ret;

slow:
	वापस drm_atomic_helper_update_plane(&plane->base, &crtc->base, fb,
					      crtc_x, crtc_y, crtc_w, crtc_h,
					      src_x, src_y, src_w, src_h, ctx);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs पूर्णांकel_cursor_plane_funcs = अणु
	.update_plane = पूर्णांकel_legacy_cursor_update,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = पूर्णांकel_cursor_क्रमmat_mod_supported,
पूर्ण;

काष्ठा पूर्णांकel_plane *
पूर्णांकel_cursor_plane_create(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_plane *cursor;
	पूर्णांक ret, zpos;

	cursor = पूर्णांकel_plane_alloc();
	अगर (IS_ERR(cursor))
		वापस cursor;

	cursor->pipe = pipe;
	cursor->i9xx_plane = (क्रमागत i9xx_plane_id) pipe;
	cursor->id = PLANE_CURSOR;
	cursor->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, cursor->id);

	अगर (IS_I845G(dev_priv) || IS_I865G(dev_priv)) अणु
		cursor->max_stride = i845_cursor_max_stride;
		cursor->update_plane = i845_update_cursor;
		cursor->disable_plane = i845_disable_cursor;
		cursor->get_hw_state = i845_cursor_get_hw_state;
		cursor->check_plane = i845_check_cursor;
	पूर्ण अन्यथा अणु
		cursor->max_stride = i9xx_cursor_max_stride;
		cursor->update_plane = i9xx_update_cursor;
		cursor->disable_plane = i9xx_disable_cursor;
		cursor->get_hw_state = i9xx_cursor_get_hw_state;
		cursor->check_plane = i9xx_check_cursor;
	पूर्ण

	cursor->cursor.base = ~0;
	cursor->cursor.cntl = ~0;

	अगर (IS_I845G(dev_priv) || IS_I865G(dev_priv) || HAS_CUR_FBC(dev_priv))
		cursor->cursor.size = ~0;

	ret = drm_universal_plane_init(&dev_priv->drm, &cursor->base,
				       0, &पूर्णांकel_cursor_plane_funcs,
				       पूर्णांकel_cursor_क्रमmats,
				       ARRAY_SIZE(पूर्णांकel_cursor_क्रमmats),
				       cursor_क्रमmat_modअगरiers,
				       DRM_PLANE_TYPE_CURSOR,
				       "cursor %c", pipe_name(pipe));
	अगर (ret)
		जाओ fail;

	अगर (DISPLAY_VER(dev_priv) >= 4)
		drm_plane_create_rotation_property(&cursor->base,
						   DRM_MODE_ROTATE_0,
						   DRM_MODE_ROTATE_0 |
						   DRM_MODE_ROTATE_180);

	zpos = RUNTIME_INFO(dev_priv)->num_sprites[pipe] + 1;
	drm_plane_create_zpos_immutable_property(&cursor->base, zpos);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		drm_plane_enable_fb_damage_clips(&cursor->base);

	drm_plane_helper_add(&cursor->base, &पूर्णांकel_plane_helper_funcs);

	वापस cursor;

fail:
	पूर्णांकel_plane_मुक्त(cursor);

	वापस ERR_PTR(ret);
पूर्ण
