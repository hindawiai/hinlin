<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "mdp4_kms.h"

#घोषणा DOWN_SCALE_MAX	8
#घोषणा UP_SCALE_MAX	8

काष्ठा mdp4_plane अणु
	काष्ठा drm_plane base;
	स्थिर अक्षर *name;

	क्रमागत mdp4_pipe pipe;

	uपूर्णांक32_t caps;
	uपूर्णांक32_t nक्रमmats;
	uपूर्णांक32_t क्रमmats[32];

	bool enabled;
पूर्ण;
#घोषणा to_mdp4_plane(x) container_of(x, काष्ठा mdp4_plane, base)

/* MDP क्रमmat helper functions */
अटल अंतरभूत
क्रमागत mdp4_frame_क्रमmat mdp4_get_frame_क्रमmat(काष्ठा drm_framebuffer *fb)
अणु
	bool is_tile = false;

	अगर (fb->modअगरier == DRM_FORMAT_MOD_SAMSUNG_64_32_TILE)
		is_tile = true;

	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_NV12 && is_tile)
		वापस FRAME_TILE_YCBCR_420;

	वापस FRAME_LINEAR;
पूर्ण

अटल व्योम mdp4_plane_set_scanout(काष्ठा drm_plane *plane,
		काष्ठा drm_framebuffer *fb);
अटल पूर्णांक mdp4_plane_mode_set(काष्ठा drm_plane *plane,
		काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
		पूर्णांक crtc_x, पूर्णांक crtc_y,
		अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
		uपूर्णांक32_t src_w, uपूर्णांक32_t src_h);

अटल काष्ठा mdp4_kms *get_kms(काष्ठा drm_plane *plane)
अणु
	काष्ठा msm_drm_निजी *priv = plane->dev->dev_निजी;
	वापस to_mdp4_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम mdp4_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp4_plane *mdp4_plane = to_mdp4_plane(plane);

	drm_plane_cleanup(plane);

	kमुक्त(mdp4_plane);
पूर्ण

/* helper to install properties which are common to planes and crtcs */
अटल व्योम mdp4_plane_install_properties(काष्ठा drm_plane *plane,
		काष्ठा drm_mode_object *obj)
अणु
	// XXX
पूर्ण

अटल पूर्णांक mdp4_plane_set_property(काष्ठा drm_plane *plane,
		काष्ठा drm_property *property, uपूर्णांक64_t val)
अणु
	// XXX
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs mdp4_plane_funcs = अणु
		.update_plane = drm_atomic_helper_update_plane,
		.disable_plane = drm_atomic_helper_disable_plane,
		.destroy = mdp4_plane_destroy,
		.set_property = mdp4_plane_set_property,
		.reset = drm_atomic_helper_plane_reset,
		.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
		.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल व्योम mdp4_plane_cleanup_fb(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(plane);
	काष्ठा msm_kms *kms = &mdp4_kms->base.base;
	काष्ठा drm_framebuffer *fb = old_state->fb;

	अगर (!fb)
		वापस;

	DBG("%s: cleanup: FB[%u]", mdp4_plane->name, fb->base.id);
	msm_framebuffer_cleanup(fb, kms->aspace);
पूर्ण


अटल पूर्णांक mdp4_plane_atomic_check(काष्ठा drm_plane *plane,
		काष्ठा drm_atomic_state *state)
अणु
	वापस 0;
पूर्ण

अटल व्योम mdp4_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	पूर्णांक ret;

	ret = mdp4_plane_mode_set(plane,
			new_state->crtc, new_state->fb,
			new_state->crtc_x, new_state->crtc_y,
			new_state->crtc_w, new_state->crtc_h,
			new_state->src_x,  new_state->src_y,
			new_state->src_w, new_state->src_h);
	/* atomic_check should have ensured that this करोesn't fail */
	WARN_ON(ret < 0);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs mdp4_plane_helper_funcs = अणु
		.prepare_fb = msm_atomic_prepare_fb,
		.cleanup_fb = mdp4_plane_cleanup_fb,
		.atomic_check = mdp4_plane_atomic_check,
		.atomic_update = mdp4_plane_atomic_update,
पूर्ण;

अटल व्योम mdp4_plane_set_scanout(काष्ठा drm_plane *plane,
		काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(plane);
	काष्ठा msm_kms *kms = &mdp4_kms->base.base;
	क्रमागत mdp4_pipe pipe = mdp4_plane->pipe;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_STRIDE_A(pipe),
			MDP4_PIPE_SRC_STRIDE_A_P0(fb->pitches[0]) |
			MDP4_PIPE_SRC_STRIDE_A_P1(fb->pitches[1]));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_STRIDE_B(pipe),
			MDP4_PIPE_SRC_STRIDE_B_P2(fb->pitches[2]) |
			MDP4_PIPE_SRC_STRIDE_B_P3(fb->pitches[3]));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRCP0_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 0));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRCP1_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 1));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRCP2_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 2));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRCP3_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 3));
पूर्ण

अटल व्योम mdp4_ग_लिखो_csc_config(काष्ठा mdp4_kms *mdp4_kms,
		क्रमागत mdp4_pipe pipe, काष्ठा csc_cfg *csc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(csc->matrix); i++) अणु
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_CSC_MV(pipe, i),
				csc->matrix[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(csc->post_bias) ; i++) अणु
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_CSC_PRE_BV(pipe, i),
				csc->pre_bias[i]);

		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_CSC_POST_BV(pipe, i),
				csc->post_bias[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(csc->post_clamp) ; i++) अणु
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_CSC_PRE_LV(pipe, i),
				csc->pre_clamp[i]);

		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_CSC_POST_LV(pipe, i),
				csc->post_clamp[i]);
	पूर्ण
पूर्ण

#घोषणा MDP4_VG_PHASE_STEP_DEFAULT	0x20000000

अटल पूर्णांक mdp4_plane_mode_set(काष्ठा drm_plane *plane,
		काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
		पूर्णांक crtc_x, पूर्णांक crtc_y,
		अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
		uपूर्णांक32_t src_w, uपूर्णांक32_t src_h)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(plane);
	क्रमागत mdp4_pipe pipe = mdp4_plane->pipe;
	स्थिर काष्ठा mdp_क्रमmat *क्रमmat;
	uपूर्णांक32_t op_mode = 0;
	uपूर्णांक32_t phasex_step = MDP4_VG_PHASE_STEP_DEFAULT;
	uपूर्णांक32_t phasey_step = MDP4_VG_PHASE_STEP_DEFAULT;
	क्रमागत mdp4_frame_क्रमmat frame_type;

	अगर (!(crtc && fb)) अणु
		DBG("%s: disabled!", mdp4_plane->name);
		वापस 0;
	पूर्ण

	frame_type = mdp4_get_frame_क्रमmat(fb);

	/* src values are in Q16 fixed poपूर्णांक, convert to पूर्णांकeger: */
	src_x = src_x >> 16;
	src_y = src_y >> 16;
	src_w = src_w >> 16;
	src_h = src_h >> 16;

	DBG("%s: FB[%u] %u,%u,%u,%u -> CRTC[%u] %d,%d,%u,%u", mdp4_plane->name,
			fb->base.id, src_x, src_y, src_w, src_h,
			crtc->base.id, crtc_x, crtc_y, crtc_w, crtc_h);

	क्रमmat = to_mdp_क्रमmat(msm_framebuffer_क्रमmat(fb));

	अगर (src_w > (crtc_w * DOWN_SCALE_MAX)) अणु
		DRM_DEV_ERROR(dev->dev, "Width down scaling exceeds limits!\n");
		वापस -दुस्फल;
	पूर्ण

	अगर (src_h > (crtc_h * DOWN_SCALE_MAX)) अणु
		DRM_DEV_ERROR(dev->dev, "Height down scaling exceeds limits!\n");
		वापस -दुस्फल;
	पूर्ण

	अगर (crtc_w > (src_w * UP_SCALE_MAX)) अणु
		DRM_DEV_ERROR(dev->dev, "Width up scaling exceeds limits!\n");
		वापस -दुस्फल;
	पूर्ण

	अगर (crtc_h > (src_h * UP_SCALE_MAX)) अणु
		DRM_DEV_ERROR(dev->dev, "Height up scaling exceeds limits!\n");
		वापस -दुस्फल;
	पूर्ण

	अगर (src_w != crtc_w) अणु
		uपूर्णांक32_t sel_unit = SCALE_FIR;
		op_mode |= MDP4_PIPE_OP_MODE_SCALEX_EN;

		अगर (MDP_FORMAT_IS_YUV(क्रमmat)) अणु
			अगर (crtc_w > src_w)
				sel_unit = SCALE_PIXEL_RPT;
			अन्यथा अगर (crtc_w <= (src_w / 4))
				sel_unit = SCALE_MN_PHASE;

			op_mode |= MDP4_PIPE_OP_MODE_SCALEX_UNIT_SEL(sel_unit);
			phasex_step = mult_frac(MDP4_VG_PHASE_STEP_DEFAULT,
					src_w, crtc_w);
		पूर्ण
	पूर्ण

	अगर (src_h != crtc_h) अणु
		uपूर्णांक32_t sel_unit = SCALE_FIR;
		op_mode |= MDP4_PIPE_OP_MODE_SCALEY_EN;

		अगर (MDP_FORMAT_IS_YUV(क्रमmat)) अणु

			अगर (crtc_h > src_h)
				sel_unit = SCALE_PIXEL_RPT;
			अन्यथा अगर (crtc_h <= (src_h / 4))
				sel_unit = SCALE_MN_PHASE;

			op_mode |= MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL(sel_unit);
			phasey_step = mult_frac(MDP4_VG_PHASE_STEP_DEFAULT,
					src_h, crtc_h);
		पूर्ण
	पूर्ण

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_SIZE(pipe),
			MDP4_PIPE_SRC_SIZE_WIDTH(src_w) |
			MDP4_PIPE_SRC_SIZE_HEIGHT(src_h));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_XY(pipe),
			MDP4_PIPE_SRC_XY_X(src_x) |
			MDP4_PIPE_SRC_XY_Y(src_y));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_DST_SIZE(pipe),
			MDP4_PIPE_DST_SIZE_WIDTH(crtc_w) |
			MDP4_PIPE_DST_SIZE_HEIGHT(crtc_h));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_DST_XY(pipe),
			MDP4_PIPE_DST_XY_X(crtc_x) |
			MDP4_PIPE_DST_XY_Y(crtc_y));

	mdp4_plane_set_scanout(plane, fb);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_FORMAT(pipe),
			MDP4_PIPE_SRC_FORMAT_A_BPC(क्रमmat->bpc_a) |
			MDP4_PIPE_SRC_FORMAT_R_BPC(क्रमmat->bpc_r) |
			MDP4_PIPE_SRC_FORMAT_G_BPC(क्रमmat->bpc_g) |
			MDP4_PIPE_SRC_FORMAT_B_BPC(क्रमmat->bpc_b) |
			COND(क्रमmat->alpha_enable, MDP4_PIPE_SRC_FORMAT_ALPHA_ENABLE) |
			MDP4_PIPE_SRC_FORMAT_CPP(क्रमmat->cpp - 1) |
			MDP4_PIPE_SRC_FORMAT_UNPACK_COUNT(क्रमmat->unpack_count - 1) |
			MDP4_PIPE_SRC_FORMAT_FETCH_PLANES(क्रमmat->fetch_type) |
			MDP4_PIPE_SRC_FORMAT_CHROMA_SAMP(क्रमmat->chroma_sample) |
			MDP4_PIPE_SRC_FORMAT_FRAME_FORMAT(frame_type) |
			COND(क्रमmat->unpack_tight, MDP4_PIPE_SRC_FORMAT_UNPACK_TIGHT));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SRC_UNPACK(pipe),
			MDP4_PIPE_SRC_UNPACK_ELEM0(क्रमmat->unpack[0]) |
			MDP4_PIPE_SRC_UNPACK_ELEM1(क्रमmat->unpack[1]) |
			MDP4_PIPE_SRC_UNPACK_ELEM2(क्रमmat->unpack[2]) |
			MDP4_PIPE_SRC_UNPACK_ELEM3(क्रमmat->unpack[3]));

	अगर (MDP_FORMAT_IS_YUV(क्रमmat)) अणु
		काष्ठा csc_cfg *csc = mdp_get_शेष_csc_cfg(CSC_YUV2RGB);

		op_mode |= MDP4_PIPE_OP_MODE_SRC_YCBCR;
		op_mode |= MDP4_PIPE_OP_MODE_CSC_EN;
		mdp4_ग_लिखो_csc_config(mdp4_kms, pipe, csc);
	पूर्ण

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_OP_MODE(pipe), op_mode);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_PHASEX_STEP(pipe), phasex_step);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_PHASEY_STEP(pipe), phasey_step);

	अगर (frame_type != FRAME_LINEAR)
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_SSTILE_FRAME_SIZE(pipe),
				MDP4_PIPE_SSTILE_FRAME_SIZE_WIDTH(src_w) |
				MDP4_PIPE_SSTILE_FRAME_SIZE_HEIGHT(src_h));

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *pipe_names[] = अणु
		"VG1", "VG2",
		"RGB1", "RGB2", "RGB3",
		"VG3", "VG4",
पूर्ण;

क्रमागत mdp4_pipe mdp4_plane_pipe(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	वापस mdp4_plane->pipe;
पूर्ण

/* initialize plane */
काष्ठा drm_plane *mdp4_plane_init(काष्ठा drm_device *dev,
		क्रमागत mdp4_pipe pipe_id, bool निजी_plane)
अणु
	काष्ठा drm_plane *plane = शून्य;
	काष्ठा mdp4_plane *mdp4_plane;
	पूर्णांक ret;
	क्रमागत drm_plane_type type;

	mdp4_plane = kzalloc(माप(*mdp4_plane), GFP_KERNEL);
	अगर (!mdp4_plane) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	plane = &mdp4_plane->base;

	mdp4_plane->pipe = pipe_id;
	mdp4_plane->name = pipe_names[pipe_id];
	mdp4_plane->caps = mdp4_pipe_caps(pipe_id);

	mdp4_plane->nक्रमmats = mdp_get_क्रमmats(mdp4_plane->क्रमmats,
			ARRAY_SIZE(mdp4_plane->क्रमmats),
			!pipe_supports_yuv(mdp4_plane->caps));

	type = निजी_plane ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
	ret = drm_universal_plane_init(dev, plane, 0xff, &mdp4_plane_funcs,
				 mdp4_plane->क्रमmats, mdp4_plane->nक्रमmats,
				 शून्य, type, शून्य);
	अगर (ret)
		जाओ fail;

	drm_plane_helper_add(plane, &mdp4_plane_helper_funcs);

	mdp4_plane_install_properties(plane, &plane->base);

	drm_plane_enable_fb_damage_clips(plane);

	वापस plane;

fail:
	अगर (plane)
		mdp4_plane_destroy(plane);

	वापस ERR_PTR(ret);
पूर्ण
