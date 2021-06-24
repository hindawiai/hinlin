<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX IPUv3 DP Overlay Planes
 *
 * Copyright (C) 2013 Philipp Zabel, Pengutronix
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश <video/imx-ipu-v3.h>

#समावेश "imx-drm.h"
#समावेश "ipuv3-plane.h"

काष्ठा ipu_plane_state अणु
	काष्ठा drm_plane_state base;
	bool use_pre;
पूर्ण;

अटल अंतरभूत काष्ठा ipu_plane_state *
to_ipu_plane_state(काष्ठा drm_plane_state *p)
अणु
	वापस container_of(p, काष्ठा ipu_plane_state, base);
पूर्ण

अटल अंतरभूत काष्ठा ipu_plane *to_ipu_plane(काष्ठा drm_plane *p)
अणु
	वापस container_of(p, काष्ठा ipu_plane, base);
पूर्ण

अटल स्थिर uपूर्णांक32_t ipu_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YVU422,
	DRM_FORMAT_YUV444,
	DRM_FORMAT_YVU444,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV16,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB565_A8,
	DRM_FORMAT_BGR565_A8,
	DRM_FORMAT_RGB888_A8,
	DRM_FORMAT_BGR888_A8,
	DRM_FORMAT_RGBX8888_A8,
	DRM_FORMAT_BGRX8888_A8,
पूर्ण;

अटल स्थिर uपूर्णांक64_t ipu_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर uपूर्णांक64_t pre_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_VIVANTE_TILED,
	DRM_FORMAT_MOD_VIVANTE_SUPER_TILED,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

पूर्णांक ipu_plane_irq(काष्ठा ipu_plane *ipu_plane)
अणु
	वापस ipu_idmac_channel_irq(ipu_plane->ipu, ipu_plane->ipu_ch,
				     IPU_IRQ_खातापूर्ण);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
drm_plane_state_to_eba(काष्ठा drm_plane_state *state, पूर्णांक plane)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *cma_obj;
	पूर्णांक x = state->src.x1 >> 16;
	पूर्णांक y = state->src.y1 >> 16;

	cma_obj = drm_fb_cma_get_gem_obj(fb, plane);
	BUG_ON(!cma_obj);

	वापस cma_obj->paddr + fb->offsets[plane] + fb->pitches[plane] * y +
	       fb->क्रमmat->cpp[plane] * x;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
drm_plane_state_to_ubo(काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *cma_obj;
	अचिन्हित दीर्घ eba = drm_plane_state_to_eba(state, 0);
	पूर्णांक x = state->src.x1 >> 16;
	पूर्णांक y = state->src.y1 >> 16;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 1);
	BUG_ON(!cma_obj);

	x /= fb->क्रमmat->hsub;
	y /= fb->क्रमmat->vsub;

	वापस cma_obj->paddr + fb->offsets[1] + fb->pitches[1] * y +
	       fb->क्रमmat->cpp[1] * x - eba;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
drm_plane_state_to_vbo(काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_gem_cma_object *cma_obj;
	अचिन्हित दीर्घ eba = drm_plane_state_to_eba(state, 0);
	पूर्णांक x = state->src.x1 >> 16;
	पूर्णांक y = state->src.y1 >> 16;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 2);
	BUG_ON(!cma_obj);

	x /= fb->क्रमmat->hsub;
	y /= fb->क्रमmat->vsub;

	वापस cma_obj->paddr + fb->offsets[2] + fb->pitches[2] * y +
	       fb->क्रमmat->cpp[2] * x - eba;
पूर्ण

अटल व्योम ipu_plane_put_resources(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा ipu_plane *ipu_plane = ptr;

	अगर (!IS_ERR_OR_शून्य(ipu_plane->dp))
		ipu_dp_put(ipu_plane->dp);
	अगर (!IS_ERR_OR_शून्य(ipu_plane->dmfc))
		ipu_dmfc_put(ipu_plane->dmfc);
	अगर (!IS_ERR_OR_शून्य(ipu_plane->ipu_ch))
		ipu_idmac_put(ipu_plane->ipu_ch);
	अगर (!IS_ERR_OR_शून्य(ipu_plane->alpha_ch))
		ipu_idmac_put(ipu_plane->alpha_ch);
पूर्ण

अटल पूर्णांक ipu_plane_get_resources(काष्ठा drm_device *dev,
				   काष्ठा ipu_plane *ipu_plane)
अणु
	पूर्णांक ret;
	पूर्णांक alpha_ch;

	ipu_plane->ipu_ch = ipu_idmac_get(ipu_plane->ipu, ipu_plane->dma);
	अगर (IS_ERR(ipu_plane->ipu_ch)) अणु
		ret = PTR_ERR(ipu_plane->ipu_ch);
		DRM_ERROR("failed to get idmac channel: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drmm_add_action_or_reset(dev, ipu_plane_put_resources, ipu_plane);
	अगर (ret)
		वापस ret;

	alpha_ch = ipu_channel_alpha_channel(ipu_plane->dma);
	अगर (alpha_ch >= 0) अणु
		ipu_plane->alpha_ch = ipu_idmac_get(ipu_plane->ipu, alpha_ch);
		अगर (IS_ERR(ipu_plane->alpha_ch)) अणु
			ret = PTR_ERR(ipu_plane->alpha_ch);
			DRM_ERROR("failed to get alpha idmac channel %d: %d\n",
				  alpha_ch, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ipu_plane->dmfc = ipu_dmfc_get(ipu_plane->ipu, ipu_plane->dma);
	अगर (IS_ERR(ipu_plane->dmfc)) अणु
		ret = PTR_ERR(ipu_plane->dmfc);
		DRM_ERROR("failed to get dmfc: ret %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ipu_plane->dp_flow >= 0) अणु
		ipu_plane->dp = ipu_dp_get(ipu_plane->ipu, ipu_plane->dp_flow);
		अगर (IS_ERR(ipu_plane->dp)) अणु
			ret = PTR_ERR(ipu_plane->dp);
			DRM_ERROR("failed to get dp flow: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ipu_plane_separate_alpha(काष्ठा ipu_plane *ipu_plane)
अणु
	चयन (ipu_plane->base.state->fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565_A8:
	हाल DRM_FORMAT_BGR565_A8:
	हाल DRM_FORMAT_RGB888_A8:
	हाल DRM_FORMAT_BGR888_A8:
	हाल DRM_FORMAT_RGBX8888_A8:
	हाल DRM_FORMAT_BGRX8888_A8:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ipu_plane_enable(काष्ठा ipu_plane *ipu_plane)
अणु
	अगर (ipu_plane->dp)
		ipu_dp_enable(ipu_plane->ipu);
	ipu_dmfc_enable_channel(ipu_plane->dmfc);
	ipu_idmac_enable_channel(ipu_plane->ipu_ch);
	अगर (ipu_plane_separate_alpha(ipu_plane))
		ipu_idmac_enable_channel(ipu_plane->alpha_ch);
	अगर (ipu_plane->dp)
		ipu_dp_enable_channel(ipu_plane->dp);
पूर्ण

व्योम ipu_plane_disable(काष्ठा ipu_plane *ipu_plane, bool disable_dp_channel)
अणु
	पूर्णांक ret;

	DRM_DEBUG_KMS("[%d] %s\n", __LINE__, __func__);

	ret = ipu_idmac_रुको_busy(ipu_plane->ipu_ch, 50);
	अगर (ret == -ETIMEDOUT) अणु
		DRM_ERROR("[PLANE:%d] IDMAC timeout\n",
			  ipu_plane->base.base.id);
	पूर्ण

	अगर (ipu_plane->dp && disable_dp_channel)
		ipu_dp_disable_channel(ipu_plane->dp, false);
	ipu_idmac_disable_channel(ipu_plane->ipu_ch);
	अगर (ipu_plane->alpha_ch)
		ipu_idmac_disable_channel(ipu_plane->alpha_ch);
	ipu_dmfc_disable_channel(ipu_plane->dmfc);
	अगर (ipu_plane->dp)
		ipu_dp_disable(ipu_plane->ipu);
	अगर (ipu_prg_present(ipu_plane->ipu))
		ipu_prg_channel_disable(ipu_plane->ipu_ch);
पूर्ण

व्योम ipu_plane_disable_deferred(काष्ठा drm_plane *plane)
अणु
	काष्ठा ipu_plane *ipu_plane = to_ipu_plane(plane);

	अगर (ipu_plane->disabling) अणु
		ipu_plane->disabling = false;
		ipu_plane_disable(ipu_plane, false);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_plane_disable_deferred);

अटल व्योम ipu_plane_state_reset(काष्ठा drm_plane *plane)
अणु
	अचिन्हित पूर्णांक zpos = (plane->type == DRM_PLANE_TYPE_PRIMARY) ? 0 : 1;
	काष्ठा ipu_plane_state *ipu_state;

	अगर (plane->state) अणु
		ipu_state = to_ipu_plane_state(plane->state);
		__drm_atomic_helper_plane_destroy_state(plane->state);
		kमुक्त(ipu_state);
		plane->state = शून्य;
	पूर्ण

	ipu_state = kzalloc(माप(*ipu_state), GFP_KERNEL);

	अगर (ipu_state) अणु
		__drm_atomic_helper_plane_reset(plane, &ipu_state->base);
		ipu_state->base.zpos = zpos;
		ipu_state->base.normalized_zpos = zpos;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
ipu_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा ipu_plane_state *state;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_plane_duplicate_state(plane, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम ipu_plane_destroy_state(काष्ठा drm_plane *plane,
				    काष्ठा drm_plane_state *state)
अणु
	काष्ठा ipu_plane_state *ipu_state = to_ipu_plane_state(state);

	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(ipu_state);
पूर्ण

अटल bool ipu_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					   uपूर्णांक32_t क्रमmat, uपूर्णांक64_t modअगरier)
अणु
	काष्ठा ipu_soc *ipu = to_ipu_plane(plane)->ipu;

	/* linear is supported क्रम all planes and क्रमmats */
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	/* without a PRG there are no supported modअगरiers */
	अगर (!ipu_prg_present(ipu))
		वापस false;

	वापस ipu_prg_क्रमmat_supported(ipu, क्रमmat, modअगरier);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs ipu_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.reset		= ipu_plane_state_reset,
	.atomic_duplicate_state	= ipu_plane_duplicate_state,
	.atomic_destroy_state	= ipu_plane_destroy_state,
	.क्रमmat_mod_supported = ipu_plane_क्रमmat_mod_supported,
पूर्ण;

अटल पूर्णांक ipu_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा device *dev = plane->dev->dev;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_framebuffer *old_fb = old_state->fb;
	अचिन्हित दीर्घ eba, ubo, vbo, old_ubo, old_vbo, alpha_eba;
	bool can_position = (plane->type == DRM_PLANE_TYPE_OVERLAY);
	पूर्णांक ret;

	/* Ok to disable */
	अगर (!fb)
		वापस 0;

	अगर (WARN_ON(!new_state->crtc))
		वापस -EINVAL;

	crtc_state =
		drm_atomic_get_existing_crtc_state(state,
						   new_state->crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	ret = drm_atomic_helper_check_plane_state(new_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  can_position, true);
	अगर (ret)
		वापस ret;

	/* nothing to check when disabling or disabled */
	अगर (!crtc_state->enable)
		वापस 0;

	चयन (plane->type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		/* full plane minimum width is 13 pixels */
		अगर (drm_rect_width(&new_state->dst) < 13)
			वापस -EINVAL;
		अवरोध;
	हाल DRM_PLANE_TYPE_OVERLAY:
		अवरोध;
	शेष:
		dev_warn(dev, "Unsupported plane type %d\n", plane->type);
		वापस -EINVAL;
	पूर्ण

	अगर (drm_rect_height(&new_state->dst) < 2)
		वापस -EINVAL;

	/*
	 * We support resizing active plane or changing its क्रमmat by
	 * क्रमcing CRTC mode change in plane's ->atomic_check callback
	 * and disabling all affected active planes in CRTC's ->atomic_disable
	 * callback.  The planes will be reenabled in plane's ->atomic_update
	 * callback.
	 */
	अगर (old_fb &&
	    (drm_rect_width(&new_state->dst) != drm_rect_width(&old_state->dst) ||
	     drm_rect_height(&new_state->dst) != drm_rect_height(&old_state->dst) ||
	     fb->क्रमmat != old_fb->क्रमmat))
		crtc_state->mode_changed = true;

	eba = drm_plane_state_to_eba(new_state, 0);

	अगर (eba & 0x7)
		वापस -EINVAL;

	अगर (fb->pitches[0] < 1 || fb->pitches[0] > 16384)
		वापस -EINVAL;

	अगर (old_fb && fb->pitches[0] != old_fb->pitches[0])
		crtc_state->mode_changed = true;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YUV444:
	हाल DRM_FORMAT_YVU444:
		/*
		 * Multiplanar क्रमmats have to meet the following restrictions:
		 * - The (up to) three plane addresses are EBA, EBA+UBO, EBA+VBO
		 * - EBA, UBO and VBO are a multiple of 8
		 * - UBO and VBO are अचिन्हित and not larger than 0xfffff8
		 * - Only EBA may be changed जबतक scanout is active
		 * - The strides of U and V planes must be identical.
		 */
		vbo = drm_plane_state_to_vbo(new_state);

		अगर (vbo & 0x7 || vbo > 0xfffff8)
			वापस -EINVAL;

		अगर (old_fb && (fb->क्रमmat == old_fb->क्रमmat)) अणु
			old_vbo = drm_plane_state_to_vbo(old_state);
			अगर (vbo != old_vbo)
				crtc_state->mode_changed = true;
		पूर्ण

		अगर (fb->pitches[1] != fb->pitches[2])
			वापस -EINVAL;

		fallthrough;
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
		ubo = drm_plane_state_to_ubo(new_state);

		अगर (ubo & 0x7 || ubo > 0xfffff8)
			वापस -EINVAL;

		अगर (old_fb && (fb->क्रमmat == old_fb->क्रमmat)) अणु
			old_ubo = drm_plane_state_to_ubo(old_state);
			अगर (ubo != old_ubo)
				crtc_state->mode_changed = true;
		पूर्ण

		अगर (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			वापस -EINVAL;

		अगर (old_fb && old_fb->pitches[1] != fb->pitches[1])
			crtc_state->mode_changed = true;

		/*
		 * The x/y offsets must be even in हाल of horizontal/vertical
		 * chroma subsampling.
		 */
		अगर (((new_state->src.x1 >> 16) & (fb->क्रमmat->hsub - 1)) ||
		    ((new_state->src.y1 >> 16) & (fb->क्रमmat->vsub - 1)))
			वापस -EINVAL;
		अवरोध;
	हाल DRM_FORMAT_RGB565_A8:
	हाल DRM_FORMAT_BGR565_A8:
	हाल DRM_FORMAT_RGB888_A8:
	हाल DRM_FORMAT_BGR888_A8:
	हाल DRM_FORMAT_RGBX8888_A8:
	हाल DRM_FORMAT_BGRX8888_A8:
		alpha_eba = drm_plane_state_to_eba(new_state, 1);
		अगर (alpha_eba & 0x7)
			वापस -EINVAL;

		अगर (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			वापस -EINVAL;

		अगर (old_fb && old_fb->pitches[1] != fb->pitches[1])
			crtc_state->mode_changed = true;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipu_plane_atomic_disable(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा ipu_plane *ipu_plane = to_ipu_plane(plane);

	अगर (ipu_plane->dp)
		ipu_dp_disable_channel(ipu_plane->dp, true);
	ipu_plane->disabling = true;
पूर्ण

अटल पूर्णांक ipu_chan_assign_axi_id(पूर्णांक ipu_chan)
अणु
	चयन (ipu_chan) अणु
	हाल IPUV3_CHANNEL_MEM_BG_SYNC:
		वापस 1;
	हाल IPUV3_CHANNEL_MEM_FG_SYNC:
		वापस 2;
	हाल IPUV3_CHANNEL_MEM_DC_SYNC:
		वापस 3;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ipu_calculate_bursts(u32 width, u32 cpp, u32 stride,
				 u8 *burstsize, u8 *num_bursts)
अणु
	स्थिर अचिन्हित पूर्णांक width_bytes = width * cpp;
	अचिन्हित पूर्णांक npb, bursts;

	/* Maximum number of pixels per burst without overshooting stride */
	क्रम (npb = 64 / cpp; npb > 0; --npb) अणु
		अगर (round_up(width_bytes, npb * cpp) <= stride)
			अवरोध;
	पूर्ण
	*burstsize = npb;

	/* Maximum number of consecutive bursts without overshooting stride */
	क्रम (bursts = 8; bursts > 1; bursts /= 2) अणु
		अगर (round_up(width_bytes, npb * cpp * bursts) <= stride)
			अवरोध;
	पूर्ण
	*num_bursts = bursts;
पूर्ण

अटल व्योम ipu_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा ipu_plane *ipu_plane = to_ipu_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा ipu_plane_state *ipu_state = to_ipu_plane_state(new_state);
	काष्ठा drm_crtc_state *crtc_state = new_state->crtc->state;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा drm_rect *dst = &new_state->dst;
	अचिन्हित दीर्घ eba, ubo, vbo;
	अचिन्हित दीर्घ alpha_eba = 0;
	क्रमागत ipu_color_space ics;
	अचिन्हित पूर्णांक axi_id = 0;
	स्थिर काष्ठा drm_क्रमmat_info *info;
	u8 burstsize, num_bursts;
	u32 width, height;
	पूर्णांक active;

	अगर (ipu_plane->dp_flow == IPU_DP_FLOW_SYNC_FG)
		ipu_dp_set_winकरोw_pos(ipu_plane->dp, dst->x1, dst->y1);

	चयन (ipu_plane->dp_flow) अणु
	हाल IPU_DP_FLOW_SYNC_BG:
		अगर (new_state->normalized_zpos == 1) अणु
			ipu_dp_set_global_alpha(ipu_plane->dp,
						!fb->क्रमmat->has_alpha, 0xff,
						true);
		पूर्ण अन्यथा अणु
			ipu_dp_set_global_alpha(ipu_plane->dp, true, 0, true);
		पूर्ण
		अवरोध;
	हाल IPU_DP_FLOW_SYNC_FG:
		अगर (new_state->normalized_zpos == 1) अणु
			ipu_dp_set_global_alpha(ipu_plane->dp,
						!fb->क्रमmat->has_alpha, 0xff,
						false);
		पूर्ण
		अवरोध;
	पूर्ण

	eba = drm_plane_state_to_eba(new_state, 0);

	/*
	 * Configure PRG channel and attached PRE, this changes the EBA to an
	 * पूर्णांकernal SRAM location.
	 */
	अगर (ipu_state->use_pre) अणु
		axi_id = ipu_chan_assign_axi_id(ipu_plane->dma);
		ipu_prg_channel_configure(ipu_plane->ipu_ch, axi_id,
					  drm_rect_width(&new_state->src) >> 16,
					  drm_rect_height(&new_state->src) >> 16,
					  fb->pitches[0], fb->क्रमmat->क्रमmat,
					  fb->modअगरier, &eba);
	पूर्ण

	अगर (old_state->fb && !drm_atomic_crtc_needs_modeset(crtc_state)) अणु
		/* nothing to करो अगर PRE is used */
		अगर (ipu_state->use_pre)
			वापस;
		active = ipu_idmac_get_current_buffer(ipu_plane->ipu_ch);
		ipu_cpmem_set_buffer(ipu_plane->ipu_ch, !active, eba);
		ipu_idmac_select_buffer(ipu_plane->ipu_ch, !active);
		अगर (ipu_plane_separate_alpha(ipu_plane)) अणु
			active = ipu_idmac_get_current_buffer(ipu_plane->alpha_ch);
			ipu_cpmem_set_buffer(ipu_plane->alpha_ch, !active,
					     alpha_eba);
			ipu_idmac_select_buffer(ipu_plane->alpha_ch, !active);
		पूर्ण
		वापस;
	पूर्ण

	ics = ipu_drm_fourcc_to_colorspace(fb->क्रमmat->क्रमmat);
	चयन (ipu_plane->dp_flow) अणु
	हाल IPU_DP_FLOW_SYNC_BG:
		ipu_dp_setup_channel(ipu_plane->dp, ics, IPUV3_COLORSPACE_RGB);
		अवरोध;
	हाल IPU_DP_FLOW_SYNC_FG:
		ipu_dp_setup_channel(ipu_plane->dp, ics,
					IPUV3_COLORSPACE_UNKNOWN);
		अवरोध;
	पूर्ण

	ipu_dmfc_config_रुको4eot(ipu_plane->dmfc, drm_rect_width(dst));

	width = drm_rect_width(&new_state->src) >> 16;
	height = drm_rect_height(&new_state->src) >> 16;
	info = drm_क्रमmat_info(fb->क्रमmat->क्रमmat);
	ipu_calculate_bursts(width, info->cpp[0], fb->pitches[0],
			     &burstsize, &num_bursts);

	ipu_cpmem_zero(ipu_plane->ipu_ch);
	ipu_cpmem_set_resolution(ipu_plane->ipu_ch, width, height);
	ipu_cpmem_set_fmt(ipu_plane->ipu_ch, fb->क्रमmat->क्रमmat);
	ipu_cpmem_set_burstsize(ipu_plane->ipu_ch, burstsize);
	ipu_cpmem_set_high_priority(ipu_plane->ipu_ch);
	ipu_idmac_enable_watermark(ipu_plane->ipu_ch, true);
	ipu_idmac_set_द्विगुन_buffer(ipu_plane->ipu_ch, 1);
	ipu_cpmem_set_stride(ipu_plane->ipu_ch, fb->pitches[0]);
	ipu_cpmem_set_axi_id(ipu_plane->ipu_ch, axi_id);

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YUV444:
	हाल DRM_FORMAT_YVU444:
		ubo = drm_plane_state_to_ubo(new_state);
		vbo = drm_plane_state_to_vbo(new_state);
		अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_YVU420 ||
		    fb->क्रमmat->क्रमmat == DRM_FORMAT_YVU422 ||
		    fb->क्रमmat->क्रमmat == DRM_FORMAT_YVU444)
			swap(ubo, vbo);

		ipu_cpmem_set_yuv_planar_full(ipu_plane->ipu_ch,
					      fb->pitches[1], ubo, vbo);

		dev_dbg(ipu_plane->base.dev->dev,
			"phy = %lu %lu %lu, x = %d, y = %d", eba, ubo, vbo,
			new_state->src.x1 >> 16, new_state->src.y1 >> 16);
		अवरोध;
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV16:
		ubo = drm_plane_state_to_ubo(new_state);

		ipu_cpmem_set_yuv_planar_full(ipu_plane->ipu_ch,
					      fb->pitches[1], ubo, ubo);

		dev_dbg(ipu_plane->base.dev->dev,
			"phy = %lu %lu, x = %d, y = %d", eba, ubo,
			new_state->src.x1 >> 16, new_state->src.y1 >> 16);
		अवरोध;
	हाल DRM_FORMAT_RGB565_A8:
	हाल DRM_FORMAT_BGR565_A8:
	हाल DRM_FORMAT_RGB888_A8:
	हाल DRM_FORMAT_BGR888_A8:
	हाल DRM_FORMAT_RGBX8888_A8:
	हाल DRM_FORMAT_BGRX8888_A8:
		alpha_eba = drm_plane_state_to_eba(new_state, 1);
		num_bursts = 0;

		dev_dbg(ipu_plane->base.dev->dev, "phys = %lu %lu, x = %d, y = %d",
			eba, alpha_eba, new_state->src.x1 >> 16,
			new_state->src.y1 >> 16);

		ipu_cpmem_set_burstsize(ipu_plane->ipu_ch, 16);

		ipu_cpmem_zero(ipu_plane->alpha_ch);
		ipu_cpmem_set_resolution(ipu_plane->alpha_ch,
					 drm_rect_width(&new_state->src) >> 16,
					 drm_rect_height(&new_state->src) >> 16);
		ipu_cpmem_set_क्रमmat_passthrough(ipu_plane->alpha_ch, 8);
		ipu_cpmem_set_high_priority(ipu_plane->alpha_ch);
		ipu_idmac_set_द्विगुन_buffer(ipu_plane->alpha_ch, 1);
		ipu_cpmem_set_stride(ipu_plane->alpha_ch, fb->pitches[1]);
		ipu_cpmem_set_burstsize(ipu_plane->alpha_ch, 16);
		ipu_cpmem_set_buffer(ipu_plane->alpha_ch, 0, alpha_eba);
		ipu_cpmem_set_buffer(ipu_plane->alpha_ch, 1, alpha_eba);
		अवरोध;
	शेष:
		dev_dbg(ipu_plane->base.dev->dev, "phys = %lu, x = %d, y = %d",
			eba, new_state->src.x1 >> 16, new_state->src.y1 >> 16);
		अवरोध;
	पूर्ण
	ipu_cpmem_set_buffer(ipu_plane->ipu_ch, 0, eba);
	ipu_cpmem_set_buffer(ipu_plane->ipu_ch, 1, eba);
	ipu_idmac_lock_enable(ipu_plane->ipu_ch, num_bursts);
	ipu_plane_enable(ipu_plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs ipu_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = ipu_plane_atomic_check,
	.atomic_disable = ipu_plane_atomic_disable,
	.atomic_update = ipu_plane_atomic_update,
पूर्ण;

bool ipu_plane_atomic_update_pending(काष्ठा drm_plane *plane)
अणु
	काष्ठा ipu_plane *ipu_plane = to_ipu_plane(plane);
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा ipu_plane_state *ipu_state = to_ipu_plane_state(state);

	/* disabled crtcs must not block the update */
	अगर (!state->crtc)
		वापस false;

	अगर (ipu_state->use_pre)
		वापस ipu_prg_channel_configure_pending(ipu_plane->ipu_ch);

	/*
	 * Pretend no update is pending in the non-PRE/PRG हाल. For this to
	 * happen, an atomic update would have to be deferred until after the
	 * start of the next frame and simultaneously पूर्णांकerrupt latency would
	 * have to be high enough to let the atomic update finish and issue an
	 * event beक्रमe the previous end of frame पूर्णांकerrupt handler can be
	 * executed.
	 */
	वापस false;
पूर्ण
पूर्णांक ipu_planes_assign_pre(काष्ठा drm_device *dev,
			  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state, *crtc_state;
	काष्ठा drm_plane_state *plane_state;
	काष्ठा ipu_plane_state *ipu_state;
	काष्ठा ipu_plane *ipu_plane;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc *crtc;
	पूर्णांक available_pres = ipu_prg_max_active_channels();
	पूर्णांक ret, i;

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, crtc_state, i) अणु
		ret = drm_atomic_add_affected_planes(state, crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * We are going over the planes in 2 passes: first we assign PREs to
	 * planes with a tiling modअगरier, which need the PREs to resolve पूर्णांकo
	 * linear. Any failure to assign a PRE there is fatal. In the second
	 * pass we try to assign PREs to linear FBs, to improve memory access
	 * patterns क्रम them. Failure at this poपूर्णांक is non-fatal, as we can
	 * scan out linear FBs without a PRE.
	 */
	क्रम_each_new_plane_in_state(state, plane, plane_state, i) अणु
		ipu_state = to_ipu_plane_state(plane_state);
		ipu_plane = to_ipu_plane(plane);

		अगर (!plane_state->fb) अणु
			ipu_state->use_pre = false;
			जारी;
		पूर्ण

		अगर (!(plane_state->fb->flags & DRM_MODE_FB_MODIFIERS) ||
		    plane_state->fb->modअगरier == DRM_FORMAT_MOD_LINEAR)
			जारी;

		अगर (!ipu_prg_present(ipu_plane->ipu) || !available_pres)
			वापस -EINVAL;

		अगर (!ipu_prg_क्रमmat_supported(ipu_plane->ipu,
					      plane_state->fb->क्रमmat->क्रमmat,
					      plane_state->fb->modअगरier))
			वापस -EINVAL;

		ipu_state->use_pre = true;
		available_pres--;
	पूर्ण

	क्रम_each_new_plane_in_state(state, plane, plane_state, i) अणु
		ipu_state = to_ipu_plane_state(plane_state);
		ipu_plane = to_ipu_plane(plane);

		अगर (!plane_state->fb) अणु
			ipu_state->use_pre = false;
			जारी;
		पूर्ण

		अगर ((plane_state->fb->flags & DRM_MODE_FB_MODIFIERS) &&
		    plane_state->fb->modअगरier != DRM_FORMAT_MOD_LINEAR)
			जारी;

		/* make sure that modअगरier is initialized */
		plane_state->fb->modअगरier = DRM_FORMAT_MOD_LINEAR;

		अगर (ipu_prg_present(ipu_plane->ipu) && available_pres &&
		    ipu_prg_क्रमmat_supported(ipu_plane->ipu,
					     plane_state->fb->क्रमmat->क्रमmat,
					     plane_state->fb->modअगरier)) अणु
			ipu_state->use_pre = true;
			available_pres--;
		पूर्ण अन्यथा अणु
			ipu_state->use_pre = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_planes_assign_pre);

काष्ठा ipu_plane *ipu_plane_init(काष्ठा drm_device *dev, काष्ठा ipu_soc *ipu,
				 पूर्णांक dma, पूर्णांक dp, अचिन्हित पूर्णांक possible_crtcs,
				 क्रमागत drm_plane_type type)
अणु
	काष्ठा ipu_plane *ipu_plane;
	स्थिर uपूर्णांक64_t *modअगरiers = ipu_क्रमmat_modअगरiers;
	अचिन्हित पूर्णांक zpos = (type == DRM_PLANE_TYPE_PRIMARY) ? 0 : 1;
	पूर्णांक ret;

	DRM_DEBUG_KMS("channel %d, dp flow %d, possible_crtcs=0x%x\n",
		      dma, dp, possible_crtcs);

	ipu_plane = drmm_universal_plane_alloc(dev, काष्ठा ipu_plane, base,
					       possible_crtcs, &ipu_plane_funcs,
					       ipu_plane_क्रमmats,
					       ARRAY_SIZE(ipu_plane_क्रमmats),
					       modअगरiers, type, शून्य);
	अगर (IS_ERR(ipu_plane)) अणु
		DRM_ERROR("failed to allocate and initialize %s plane\n",
			  zpos ? "overlay" : "primary");
		वापस ipu_plane;
	पूर्ण

	ipu_plane->ipu = ipu;
	ipu_plane->dma = dma;
	ipu_plane->dp_flow = dp;

	अगर (ipu_prg_present(ipu))
		modअगरiers = pre_क्रमmat_modअगरiers;

	drm_plane_helper_add(&ipu_plane->base, &ipu_plane_helper_funcs);

	अगर (dp == IPU_DP_FLOW_SYNC_BG || dp == IPU_DP_FLOW_SYNC_FG)
		ret = drm_plane_create_zpos_property(&ipu_plane->base, zpos, 0,
						     1);
	अन्यथा
		ret = drm_plane_create_zpos_immutable_property(&ipu_plane->base,
							       0);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = ipu_plane_get_resources(dev, ipu_plane);
	अगर (ret) अणु
		DRM_ERROR("failed to get %s plane resources: %pe\n",
			  zpos ? "overlay" : "primary", &ret);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ipu_plane;
पूर्ण
