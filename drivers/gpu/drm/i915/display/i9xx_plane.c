<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश <linux/kernel.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "intel_atomic.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fb.h"
#समावेश "intel_sprite.h"
#समावेश "i9xx_plane.h"

/* Primary plane क्रमmats क्रम gen <= 3 */
अटल स्थिर u32 i8xx_primary_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

/* Primary plane क्रमmats क्रम ivb (no fp16 due to hw issue) */
अटल स्थिर u32 ivb_primary_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
पूर्ण;

/* Primary plane क्रमmats क्रम gen >= 4, except ivb */
अटल स्थिर u32 i965_primary_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_XBGR16161616F,
पूर्ण;

/* Primary plane क्रमmats क्रम vlv/chv */
अटल स्थिर u32 vlv_primary_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XRGB2101010,
	DRM_FORMAT_XBGR2101010,
	DRM_FORMAT_ARGB2101010,
	DRM_FORMAT_ABGR2101010,
	DRM_FORMAT_XBGR16161616F,
पूर्ण;

अटल स्थिर u64 i9xx_क्रमmat_modअगरiers[] = अणु
	I915_FORMAT_MOD_X_TILED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल bool i8xx_plane_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_XRGB8888:
		वापस modअगरier == DRM_FORMAT_MOD_LINEAR ||
			modअगरier == I915_FORMAT_MOD_X_TILED;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool i965_plane_क्रमmat_mod_supported(काष्ठा drm_plane *_plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	चयन (modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_C8:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_XBGR16161616F:
		वापस modअगरier == DRM_FORMAT_MOD_LINEAR ||
			modअगरier == I915_FORMAT_MOD_X_TILED;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool i9xx_plane_has_fbc(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत i9xx_plane_id i9xx_plane)
अणु
	अगर (!HAS_FBC(dev_priv))
		वापस false;

	अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		वापस i9xx_plane == PLANE_A; /* tied to pipe A */
	अन्यथा अगर (IS_IVYBRIDGE(dev_priv))
		वापस i9xx_plane == PLANE_A || i9xx_plane == PLANE_B ||
			i9xx_plane == PLANE_C;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4)
		वापस i9xx_plane == PLANE_A || i9xx_plane == PLANE_B;
	अन्यथा
		वापस i9xx_plane == PLANE_A;
पूर्ण

अटल bool i9xx_plane_has_winकरोwing(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;

	अगर (IS_CHERRYVIEW(dev_priv))
		वापस i9xx_plane == PLANE_B;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5 || IS_G4X(dev_priv))
		वापस false;
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 4))
		वापस i9xx_plane == PLANE_C;
	अन्यथा
		वापस i9xx_plane == PLANE_B ||
			i9xx_plane == PLANE_C;
पूर्ण

अटल u32 i9xx_plane_ctl(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	u32 dspcntr;

	dspcntr = DISPLAY_PLANE_ENABLE;

	अगर (IS_G4X(dev_priv) || IS_IRONLAKE(dev_priv) ||
	    IS_SANDYBRIDGE(dev_priv) || IS_IVYBRIDGE(dev_priv))
		dspcntr |= DISPPLANE_TRICKLE_FEED_DISABLE;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		dspcntr |= DISPPLANE_8BPP;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		dspcntr |= DISPPLANE_BGRX555;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		dspcntr |= DISPPLANE_BGRA555;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		dspcntr |= DISPPLANE_BGRX565;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		dspcntr |= DISPPLANE_BGRX888;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		dspcntr |= DISPPLANE_RGBX888;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		dspcntr |= DISPPLANE_BGRA888;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
		dspcntr |= DISPPLANE_RGBA888;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
		dspcntr |= DISPPLANE_BGRX101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
		dspcntr |= DISPPLANE_RGBX101010;
		अवरोध;
	हाल DRM_FORMAT_ARGB2101010:
		dspcntr |= DISPPLANE_BGRA101010;
		अवरोध;
	हाल DRM_FORMAT_ABGR2101010:
		dspcntr |= DISPPLANE_RGBA101010;
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
		dspcntr |= DISPPLANE_RGBX161616;
		अवरोध;
	शेष:
		MISSING_CASE(fb->क्रमmat->क्रमmat);
		वापस 0;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 4 &&
	    fb->modअगरier == I915_FORMAT_MOD_X_TILED)
		dspcntr |= DISPPLANE_TILED;

	अगर (rotation & DRM_MODE_ROTATE_180)
		dspcntr |= DISPPLANE_ROTATE_180;

	अगर (rotation & DRM_MODE_REFLECT_X)
		dspcntr |= DISPPLANE_MIRROR;

	वापस dspcntr;
पूर्ण

पूर्णांक i9xx_check_plane_surface(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(plane_state->uapi.plane->dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक src_x, src_y, src_w;
	u32 offset;
	पूर्णांक ret;

	ret = पूर्णांकel_plane_compute_gtt(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	src_x = plane_state->uapi.src.x1 >> 16;
	src_y = plane_state->uapi.src.y1 >> 16;

	/* Unकरोcumented hardware limit on i965/g4x/vlv/chv */
	अगर (HAS_GMCH(dev_priv) && fb->क्रमmat->cpp[0] == 8 && src_w > 2048)
		वापस -EINVAL;

	पूर्णांकel_add_fb_offsets(&src_x, &src_y, plane_state, 0);

	अगर (DISPLAY_VER(dev_priv) >= 4)
		offset = पूर्णांकel_plane_compute_aligned_offset(&src_x, &src_y,
							    plane_state, 0);
	अन्यथा
		offset = 0;

	/*
	 * When using an X-tiled surface the plane starts to
	 * misbehave अगर the x offset + width exceeds the stride.
	 * hsw/bdw: underrun galore
	 * ilk/snb/ivb: wrap to the next tile row mid scanout
	 * i965/g4x: so far appear immune to this
	 * vlv/chv: TODO check
	 *
	 * Linear surfaces seem to work just fine, even on hsw/bdw
	 * despite them not using the linear offset anymore.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 4 && fb->modअगरier == I915_FORMAT_MOD_X_TILED) अणु
		u32 alignment = पूर्णांकel_surf_alignment(fb, 0);
		पूर्णांक cpp = fb->क्रमmat->cpp[0];

		जबतक ((src_x + src_w) * cpp > plane_state->view.color_plane[0].stride) अणु
			अगर (offset == 0) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "Unable to find suitable display surface offset due to X-tiling\n");
				वापस -EINVAL;
			पूर्ण

			offset = पूर्णांकel_plane_adjust_aligned_offset(&src_x, &src_y, plane_state, 0,
								   offset, offset - alignment);
		पूर्ण
	पूर्ण

	/*
	 * Put the final coordinates back so that the src
	 * coordinate checks will see the right values.
	 */
	drm_rect_translate_to(&plane_state->uapi.src,
			      src_x << 16, src_y << 16);

	/* HSW/BDW करो this स्वतःmagically in hardware */
	अगर (!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv)) अणु
		अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
		पूर्णांक src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
		पूर्णांक src_h = drm_rect_height(&plane_state->uapi.src) >> 16;

		अगर (rotation & DRM_MODE_ROTATE_180) अणु
			src_x += src_w - 1;
			src_y += src_h - 1;
		पूर्ण अन्यथा अगर (rotation & DRM_MODE_REFLECT_X) अणु
			src_x += src_w - 1;
		पूर्ण
	पूर्ण

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		drm_WARN_ON(&dev_priv->drm, src_x > 8191 || src_y > 4095);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4 &&
		   fb->modअगरier == I915_FORMAT_MOD_X_TILED) अणु
		drm_WARN_ON(&dev_priv->drm, src_x > 4095 || src_y > 4095);
	पूर्ण

	plane_state->view.color_plane[0].offset = offset;
	plane_state->view.color_plane[0].x = src_x;
	plane_state->view.color_plane[0].y = src_y;

	वापस 0;
पूर्ण

अटल पूर्णांक
i9xx_plane_check(काष्ठा पूर्णांकel_crtc_state *crtc_state,
		 काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	पूर्णांक ret;

	ret = chv_plane_check_rotation(plane_state);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_atomic_plane_check_clipping(plane_state, crtc_state,
						DRM_PLANE_HELPER_NO_SCALING,
						DRM_PLANE_HELPER_NO_SCALING,
						i9xx_plane_has_winकरोwing(plane));
	अगर (ret)
		वापस ret;

	ret = i9xx_check_plane_surface(plane_state);
	अगर (ret)
		वापस ret;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	ret = पूर्णांकel_plane_check_src_coordinates(plane_state);
	अगर (ret)
		वापस ret;

	plane_state->ctl = i9xx_plane_ctl(crtc_state, plane_state);

	वापस 0;
पूर्ण

अटल u32 i9xx_plane_ctl_crtc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 dspcntr = 0;

	अगर (crtc_state->gamma_enable)
		dspcntr |= DISPPLANE_GAMMA_ENABLE;

	अगर (crtc_state->csc_enable)
		dspcntr |= DISPPLANE_PIPE_CSC_ENABLE;

	अगर (DISPLAY_VER(dev_priv) < 5)
		dspcntr |= DISPPLANE_SEL_PIPE(crtc->pipe);

	वापस dspcntr;
पूर्ण

अटल व्योम i9xx_plane_ratio(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			     अचिन्हित पूर्णांक *num, अचिन्हित पूर्णांक *den)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];

	/*
	 * g4x bspec says 64bpp pixel rate can't exceed 80%
	 * of cdclk when the sprite plane is enabled on the
	 * same pipe. ilk/snb bspec says 64bpp pixel rate is
	 * never allowed to exceed 80% of cdclk. Let's just go
	 * with the ilk/snb limit always.
	 */
	अगर (cpp == 8) अणु
		*num = 10;
		*den = 8;
	पूर्ण अन्यथा अणु
		*num = 1;
		*den = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक i9xx_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	अचिन्हित पूर्णांक pixel_rate;
	अचिन्हित पूर्णांक num, den;

	/*
	 * Note that crtc_state->pixel_rate accounts क्रम both
	 * horizontal and vertical panel fitter करोwnscaling factors.
	 * Pre-HSW bspec tells us to only consider the horizontal
	 * करोwnscaling factor here. We ignore that and just consider
	 * both क्रम simplicity.
	 */
	pixel_rate = crtc_state->pixel_rate;

	i9xx_plane_ratio(crtc_state, plane_state, &num, &den);

	/* two pixels per घड़ी with द्विगुन wide pipe */
	अगर (crtc_state->द्विगुन_wide)
		den *= 2;

	वापस DIV_ROUND_UP(pixel_rate * num, den);
पूर्ण

अटल व्योम i9xx_update_plane(काष्ठा पूर्णांकel_plane *plane,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	u32 linear_offset;
	पूर्णांक x = plane_state->view.color_plane[0].x;
	पूर्णांक y = plane_state->view.color_plane[0].y;
	पूर्णांक crtc_x = plane_state->uapi.dst.x1;
	पूर्णांक crtc_y = plane_state->uapi.dst.y1;
	पूर्णांक crtc_w = drm_rect_width(&plane_state->uapi.dst);
	पूर्णांक crtc_h = drm_rect_height(&plane_state->uapi.dst);
	अचिन्हित दीर्घ irqflags;
	u32 dspaddr_offset;
	u32 dspcntr;

	dspcntr = plane_state->ctl | i9xx_plane_ctl_crtc(crtc_state);

	linear_offset = पूर्णांकel_fb_xy_to_linear(x, y, plane_state, 0);

	अगर (DISPLAY_VER(dev_priv) >= 4)
		dspaddr_offset = plane_state->view.color_plane[0].offset;
	अन्यथा
		dspaddr_offset = linear_offset;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSTRIDE(i9xx_plane),
			  plane_state->view.color_plane[0].stride);

	अगर (DISPLAY_VER(dev_priv) < 4) अणु
		/*
		 * PLANE_A करोesn't actually have a full winकरोw
		 * generator but let's assume we still need to
		 * program whatever is there.
		 */
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPPOS(i9xx_plane),
				  (crtc_y << 16) | crtc_x);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSIZE(i9xx_plane),
				  ((crtc_h - 1) << 16) | (crtc_w - 1));
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv) && i9xx_plane == PLANE_B) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PRIMPOS(i9xx_plane),
				  (crtc_y << 16) | crtc_x);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PRIMSIZE(i9xx_plane),
				  ((crtc_h - 1) << 16) | (crtc_w - 1));
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, PRIMCNSTALPHA(i9xx_plane), 0);
	पूर्ण

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPOFFSET(i9xx_plane),
				  (y << 16) | x);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPLINOFF(i9xx_plane),
				  linear_offset);
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPTILखातापूर्णF(i9xx_plane),
				  (y << 16) | x);
	पूर्ण

	/*
	 * The control रेजिस्टर self-arms अगर the plane was previously
	 * disabled. Try to make the plane enable atomic by writing
	 * the control रेजिस्टर just beक्रमe the surface रेजिस्टर.
	 */
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPCNTR(i9xx_plane), dspcntr);
	अगर (DISPLAY_VER(dev_priv) >= 4)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSURF(i9xx_plane),
				  पूर्णांकel_plane_ggtt_offset(plane_state) + dspaddr_offset);
	अन्यथा
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPADDR(i9xx_plane),
				  पूर्णांकel_plane_ggtt_offset(plane_state) + dspaddr_offset);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम i9xx_disable_plane(काष्ठा पूर्णांकel_plane *plane,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	अचिन्हित दीर्घ irqflags;
	u32 dspcntr;

	/*
	 * DSPCNTR pipe gamma enable on g4x+ and pipe csc
	 * enable on ilk+ affect the pipe bottom color as
	 * well, so we must configure them even अगर the plane
	 * is disabled.
	 *
	 * On pre-g4x there is no way to gamma correct the
	 * pipe bottom color but we'll keep on करोing this
	 * anyway so that the crtc state पढ़ोout works correctly.
	 */
	dspcntr = i9xx_plane_ctl_crtc(crtc_state);

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPCNTR(i9xx_plane), dspcntr);
	अगर (DISPLAY_VER(dev_priv) >= 4)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSURF(i9xx_plane), 0);
	अन्यथा
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPADDR(i9xx_plane), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
g4x_primary_async_flip(काष्ठा पूर्णांकel_plane *plane,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		       bool async_flip)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	u32 dspcntr = plane_state->ctl | i9xx_plane_ctl_crtc(crtc_state);
	u32 dspaddr_offset = plane_state->view.color_plane[0].offset;
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	अचिन्हित दीर्घ irqflags;

	अगर (async_flip)
		dspcntr |= DISPPLANE_ASYNC_FLIP;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPCNTR(i9xx_plane), dspcntr);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPSURF(i9xx_plane),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + dspaddr_offset);
	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
vlv_primary_async_flip(काष्ठा पूर्णांकel_plane *plane,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
		       bool async_flip)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	u32 dspaddr_offset = plane_state->view.color_plane[0].offset;
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);
	पूर्णांकel_de_ग_लिखो_fw(dev_priv, DSPADDR_VLV(i9xx_plane),
			  पूर्णांकel_plane_ggtt_offset(plane_state) + dspaddr_offset);
	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
पूर्ण

अटल व्योम
bdw_primary_enable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	bdw_enable_pipe_irq(i915, pipe, GEN8_PIPE_PRIMARY_FLIP_DONE);
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
bdw_primary_disable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	bdw_disable_pipe_irq(i915, pipe, GEN8_PIPE_PRIMARY_FLIP_DONE);
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
ivb_primary_enable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);

	spin_lock_irq(&i915->irq_lock);
	ilk_enable_display_irq(i915, DE_PLANE_FLIP_DONE_IVB(plane->i9xx_plane));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
ivb_primary_disable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);

	spin_lock_irq(&i915->irq_lock);
	ilk_disable_display_irq(i915, DE_PLANE_FLIP_DONE_IVB(plane->i9xx_plane));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
ilk_primary_enable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);

	spin_lock_irq(&i915->irq_lock);
	ilk_enable_display_irq(i915, DE_PLANE_FLIP_DONE(plane->i9xx_plane));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
ilk_primary_disable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);

	spin_lock_irq(&i915->irq_lock);
	ilk_disable_display_irq(i915, DE_PLANE_FLIP_DONE(plane->i9xx_plane));
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
vlv_primary_enable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	i915_enable_pipestat(i915, pipe, PLANE_FLIP_DONE_INT_STATUS_VLV);
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल व्योम
vlv_primary_disable_flip_करोne(काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	क्रमागत pipe pipe = plane->pipe;

	spin_lock_irq(&i915->irq_lock);
	i915_disable_pipestat(i915, pipe, PLANE_FLIP_DONE_INT_STATUS_VLV);
	spin_unlock_irq(&i915->irq_lock);
पूर्ण

अटल bool i9xx_plane_get_hw_state(काष्ठा पूर्णांकel_plane *plane,
				    क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;
	u32 val;

	/*
	 * Not 100% correct क्रम planes that can move between pipes,
	 * but that's only the case for gen2-4 which don't have any
	 * display घातer wells.
	 */
	घातer_करोमुख्य = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(i9xx_plane));

	ret = val & DISPLAY_PLANE_ENABLE;

	अगर (DISPLAY_VER(dev_priv) >= 5)
		*pipe = plane->pipe;
	अन्यथा
		*pipe = (val & DISPPLANE_SEL_PIPE_MASK) >>
			DISPPLANE_SEL_PIPE_SHIFT;

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक
hsw_primary_max_stride(काष्ठा पूर्णांकel_plane *plane,
		       u32 pixel_क्रमmat, u64 modअगरier,
		       अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/* Limit to 8k pixels to guarantee OFFSET.x करोesn't get too big. */
	वापस min(8192 * cpp, 32 * 1024);
पूर्ण

अटल अचिन्हित पूर्णांक
ilk_primary_max_stride(काष्ठा पूर्णांकel_plane *plane,
		       u32 pixel_क्रमmat, u64 modअगरier,
		       अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/* Limit to 4k pixels to guarantee TILखातापूर्णF.x करोesn't get too big. */
	अगर (modअगरier == I915_FORMAT_MOD_X_TILED)
		वापस min(4096 * cpp, 32 * 1024);
	अन्यथा
		वापस 32 * 1024;
पूर्ण

अचिन्हित पूर्णांक
i965_plane_max_stride(काष्ठा पूर्णांकel_plane *plane,
		      u32 pixel_क्रमmat, u64 modअगरier,
		      अचिन्हित पूर्णांक rotation)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	पूर्णांक cpp = info->cpp[0];

	/* Limit to 4k pixels to guarantee TILखातापूर्णF.x करोesn't get too big. */
	अगर (modअगरier == I915_FORMAT_MOD_X_TILED)
		वापस min(4096 * cpp, 16 * 1024);
	अन्यथा
		वापस 32 * 1024;
पूर्ण

अटल अचिन्हित पूर्णांक
i9xx_plane_max_stride(काष्ठा पूर्णांकel_plane *plane,
		      u32 pixel_क्रमmat, u64 modअगरier,
		      अचिन्हित पूर्णांक rotation)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 3) अणु
		अगर (modअगरier == I915_FORMAT_MOD_X_TILED)
			वापस 8*1024;
		अन्यथा
			वापस 16*1024;
	पूर्ण अन्यथा अणु
		अगर (plane->i9xx_plane == PLANE_C)
			वापस 4*1024;
		अन्यथा
			वापस 8*1024;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs i965_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = i965_plane_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs i8xx_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = पूर्णांकel_plane_destroy,
	.atomic_duplicate_state = पूर्णांकel_plane_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_plane_destroy_state,
	.क्रमmat_mod_supported = i8xx_plane_क्रमmat_mod_supported,
पूर्ण;

काष्ठा पूर्णांकel_plane *
पूर्णांकel_primary_plane_create(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	स्थिर काष्ठा drm_plane_funcs *plane_funcs;
	अचिन्हित पूर्णांक supported_rotations;
	स्थिर u32 *क्रमmats;
	पूर्णांक num_क्रमmats;
	पूर्णांक ret, zpos;

	plane = पूर्णांकel_plane_alloc();
	अगर (IS_ERR(plane))
		वापस plane;

	plane->pipe = pipe;
	/*
	 * On gen2/3 only plane A can करो FBC, but the panel fitter and LVDS
	 * port is hooked to pipe B. Hence we want plane A feeding pipe B.
	 */
	अगर (HAS_FBC(dev_priv) && DISPLAY_VER(dev_priv) < 4 &&
	    INTEL_NUM_PIPES(dev_priv) == 2)
		plane->i9xx_plane = (क्रमागत i9xx_plane_id) !pipe;
	अन्यथा
		plane->i9xx_plane = (क्रमागत i9xx_plane_id) pipe;
	plane->id = PLANE_PRIMARY;
	plane->frontbuffer_bit = INTEL_FRONTBUFFER(pipe, plane->id);

	plane->has_fbc = i9xx_plane_has_fbc(dev_priv, plane->i9xx_plane);
	अगर (plane->has_fbc) अणु
		काष्ठा पूर्णांकel_fbc *fbc = &dev_priv->fbc;

		fbc->possible_framebuffer_bits |= plane->frontbuffer_bit;
	पूर्ण

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		क्रमmats = vlv_primary_क्रमmats;
		num_क्रमmats = ARRAY_SIZE(vlv_primary_क्रमmats);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		/*
		 * WaFP16GammaEnabling:ivb
		 * "Workaround : When using the 64-bit क्रमmat, the plane
		 *  output on each color channel has one quarter amplitude.
		 *  It can be brought up to full amplitude by using pipe
		 *  gamma correction or pipe color space conversion to
		 *  multiply the plane output by four."
		 *
		 * There is no dedicated plane gamma क्रम the primary plane,
		 * and using the pipe gamma/csc could conflict with other
		 * planes, so we choose not to expose fp16 on IVB primary
		 * planes. HSW primary planes no दीर्घer have this problem.
		 */
		अगर (IS_IVYBRIDGE(dev_priv)) अणु
			क्रमmats = ivb_primary_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(ivb_primary_क्रमmats);
		पूर्ण अन्यथा अणु
			क्रमmats = i965_primary_क्रमmats;
			num_क्रमmats = ARRAY_SIZE(i965_primary_क्रमmats);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रमmats = i8xx_primary_क्रमmats;
		num_क्रमmats = ARRAY_SIZE(i8xx_primary_क्रमmats);
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 4)
		plane_funcs = &i965_plane_funcs;
	अन्यथा
		plane_funcs = &i8xx_plane_funcs;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		plane->min_cdclk = vlv_plane_min_cdclk;
	अन्यथा अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		plane->min_cdclk = hsw_plane_min_cdclk;
	अन्यथा अगर (IS_IVYBRIDGE(dev_priv))
		plane->min_cdclk = ivb_plane_min_cdclk;
	अन्यथा
		plane->min_cdclk = i9xx_plane_min_cdclk;

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (DISPLAY_VER(dev_priv) >= 4)
			plane->max_stride = i965_plane_max_stride;
		अन्यथा
			plane->max_stride = i9xx_plane_max_stride;
	पूर्ण अन्यथा अणु
		अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
			plane->max_stride = hsw_primary_max_stride;
		अन्यथा
			plane->max_stride = ilk_primary_max_stride;
	पूर्ण

	plane->update_plane = i9xx_update_plane;
	plane->disable_plane = i9xx_disable_plane;
	plane->get_hw_state = i9xx_plane_get_hw_state;
	plane->check_plane = i9xx_plane_check;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		plane->async_flip = vlv_primary_async_flip;
		plane->enable_flip_करोne = vlv_primary_enable_flip_करोne;
		plane->disable_flip_करोne = vlv_primary_disable_flip_करोne;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		plane->need_async_flip_disable_wa = true;
		plane->async_flip = g4x_primary_async_flip;
		plane->enable_flip_करोne = bdw_primary_enable_flip_करोne;
		plane->disable_flip_करोne = bdw_primary_disable_flip_करोne;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7) अणु
		plane->async_flip = g4x_primary_async_flip;
		plane->enable_flip_करोne = ivb_primary_enable_flip_करोne;
		plane->disable_flip_करोne = ivb_primary_disable_flip_करोne;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		plane->async_flip = g4x_primary_async_flip;
		plane->enable_flip_करोne = ilk_primary_enable_flip_करोne;
		plane->disable_flip_करोne = ilk_primary_disable_flip_करोne;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 5 || IS_G4X(dev_priv))
		ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
					       0, plane_funcs,
					       क्रमmats, num_क्रमmats,
					       i9xx_क्रमmat_modअगरiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "primary %c", pipe_name(pipe));
	अन्यथा
		ret = drm_universal_plane_init(&dev_priv->drm, &plane->base,
					       0, plane_funcs,
					       क्रमmats, num_क्रमmats,
					       i9xx_क्रमmat_modअगरiers,
					       DRM_PLANE_TYPE_PRIMARY,
					       "plane %c",
					       plane_name(plane->i9xx_plane));
	अगर (ret)
		जाओ fail;

	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) अणु
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		supported_rotations =
			DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_180;
	पूर्ण अन्यथा अणु
		supported_rotations = DRM_MODE_ROTATE_0;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 4)
		drm_plane_create_rotation_property(&plane->base,
						   DRM_MODE_ROTATE_0,
						   supported_rotations);

	zpos = 0;
	drm_plane_create_zpos_immutable_property(&plane->base, zpos);

	drm_plane_helper_add(&plane->base, &पूर्णांकel_plane_helper_funcs);

	वापस plane;

fail:
	पूर्णांकel_plane_मुक्त(plane);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक i9xx_क्रमmat_to_fourcc(पूर्णांक क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DISPPLANE_8BPP:
		वापस DRM_FORMAT_C8;
	हाल DISPPLANE_BGRA555:
		वापस DRM_FORMAT_ARGB1555;
	हाल DISPPLANE_BGRX555:
		वापस DRM_FORMAT_XRGB1555;
	हाल DISPPLANE_BGRX565:
		वापस DRM_FORMAT_RGB565;
	शेष:
	हाल DISPPLANE_BGRX888:
		वापस DRM_FORMAT_XRGB8888;
	हाल DISPPLANE_RGBX888:
		वापस DRM_FORMAT_XBGR8888;
	हाल DISPPLANE_BGRA888:
		वापस DRM_FORMAT_ARGB8888;
	हाल DISPPLANE_RGBA888:
		वापस DRM_FORMAT_ABGR8888;
	हाल DISPPLANE_BGRX101010:
		वापस DRM_FORMAT_XRGB2101010;
	हाल DISPPLANE_RGBX101010:
		वापस DRM_FORMAT_XBGR2101010;
	हाल DISPPLANE_BGRA101010:
		वापस DRM_FORMAT_ARGB2101010;
	हाल DISPPLANE_RGBA101010:
		वापस DRM_FORMAT_ABGR2101010;
	हाल DISPPLANE_RGBX161616:
		वापस DRM_FORMAT_XBGR16161616F;
	पूर्ण
पूर्ण

व्योम
i9xx_get_initial_plane_config(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	क्रमागत pipe pipe;
	u32 val, base, offset;
	पूर्णांक fourcc, pixel_क्रमmat;
	अचिन्हित पूर्णांक aligned_height;
	काष्ठा drm_framebuffer *fb;
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb;

	अगर (!plane->get_hw_state(plane, &pipe))
		वापस;

	drm_WARN_ON(dev, pipe != crtc->pipe);

	पूर्णांकel_fb = kzalloc(माप(*पूर्णांकel_fb), GFP_KERNEL);
	अगर (!पूर्णांकel_fb) अणु
		drm_dbg_kms(&dev_priv->drm, "failed to alloc fb\n");
		वापस;
	पूर्ण

	fb = &पूर्णांकel_fb->base;

	fb->dev = dev;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(i9xx_plane));

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		अगर (val & DISPPLANE_TILED) अणु
			plane_config->tiling = I915_TILING_X;
			fb->modअगरier = I915_FORMAT_MOD_X_TILED;
		पूर्ण

		अगर (val & DISPPLANE_ROTATE_180)
			plane_config->rotation = DRM_MODE_ROTATE_180;
	पूर्ण

	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B &&
	    val & DISPPLANE_MIRROR)
		plane_config->rotation |= DRM_MODE_REFLECT_X;

	pixel_क्रमmat = val & DISPPLANE_PIXFORMAT_MASK;
	fourcc = i9xx_क्रमmat_to_fourcc(pixel_क्रमmat);
	fb->क्रमmat = drm_क्रमmat_info(fourcc);

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		offset = पूर्णांकel_de_पढ़ो(dev_priv, DSPOFFSET(i9xx_plane));
		base = पूर्णांकel_de_पढ़ो(dev_priv, DSPSURF(i9xx_plane)) & 0xfffff000;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		अगर (plane_config->tiling)
			offset = पूर्णांकel_de_पढ़ो(dev_priv,
					       DSPTILखातापूर्णF(i9xx_plane));
		अन्यथा
			offset = पूर्णांकel_de_पढ़ो(dev_priv,
					       DSPLINOFF(i9xx_plane));
		base = पूर्णांकel_de_पढ़ो(dev_priv, DSPSURF(i9xx_plane)) & 0xfffff000;
	पूर्ण अन्यथा अणु
		base = पूर्णांकel_de_पढ़ो(dev_priv, DSPADDR(i9xx_plane));
	पूर्ण
	plane_config->base = base;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PIPESRC(pipe));
	fb->width = ((val >> 16) & 0xfff) + 1;
	fb->height = ((val >> 0) & 0xfff) + 1;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DSPSTRIDE(i9xx_plane));
	fb->pitches[0] = val & 0xffffffc0;

	aligned_height = पूर्णांकel_fb_align_height(fb, 0, fb->height);

	plane_config->size = fb->pitches[0] * aligned_height;

	drm_dbg_kms(&dev_priv->drm,
		    "%s/%s with fb: size=%dx%d@%d, offset=%x, pitch %d, size 0x%x\n",
		    crtc->base.name, plane->base.name, fb->width, fb->height,
		    fb->क्रमmat->cpp[0] * 8, base, fb->pitches[0],
		    plane_config->size);

	plane_config->fb = पूर्णांकel_fb;
पूर्ण

