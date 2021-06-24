<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Broadcom
 */

/**
 * DOC: VC4 KMS
 *
 * This is the general code क्रम implementing KMS mode setting that
 * करोesn't clearly associate with any of the other objects (plane,
 * crtc, HDMI encoder).
 */

#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा HVS_NUM_CHANNELS 3

काष्ठा vc4_cपंचांग_state अणु
	काष्ठा drm_निजी_state base;
	काष्ठा drm_color_cपंचांग *cपंचांग;
	पूर्णांक fअगरo;
पूर्ण;

अटल काष्ठा vc4_cपंचांग_state *to_vc4_cपंचांग_state(काष्ठा drm_निजी_state *priv)
अणु
	वापस container_of(priv, काष्ठा vc4_cपंचांग_state, base);
पूर्ण

काष्ठा vc4_hvs_state अणु
	काष्ठा drm_निजी_state base;

	काष्ठा अणु
		अचिन्हित in_use: 1;
		काष्ठा drm_crtc_commit *pending_commit;
	पूर्ण fअगरo_state[HVS_NUM_CHANNELS];
पूर्ण;

अटल काष्ठा vc4_hvs_state *
to_vc4_hvs_state(काष्ठा drm_निजी_state *priv)
अणु
	वापस container_of(priv, काष्ठा vc4_hvs_state, base);
पूर्ण

काष्ठा vc4_load_tracker_state अणु
	काष्ठा drm_निजी_state base;
	u64 hvs_load;
	u64 membus_load;
पूर्ण;

अटल काष्ठा vc4_load_tracker_state *
to_vc4_load_tracker_state(काष्ठा drm_निजी_state *priv)
अणु
	वापस container_of(priv, काष्ठा vc4_load_tracker_state, base);
पूर्ण

अटल काष्ठा vc4_cपंचांग_state *vc4_get_cपंचांग_state(काष्ठा drm_atomic_state *state,
					       काष्ठा drm_निजी_obj *manager)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_निजी_state *priv_state;
	पूर्णांक ret;

	ret = drm_modeset_lock(&vc4->cपंचांग_state_lock, state->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	priv_state = drm_atomic_get_निजी_obj_state(state, manager);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_vc4_cपंचांग_state(priv_state);
पूर्ण

अटल काष्ठा drm_निजी_state *
vc4_cपंचांग_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा vc4_cपंचांग_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम vc4_cपंचांग_destroy_state(काष्ठा drm_निजी_obj *obj,
				  काष्ठा drm_निजी_state *state)
अणु
	काष्ठा vc4_cपंचांग_state *cपंचांग_state = to_vc4_cपंचांग_state(state);

	kमुक्त(cपंचांग_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs vc4_cपंचांग_state_funcs = अणु
	.atomic_duplicate_state = vc4_cपंचांग_duplicate_state,
	.atomic_destroy_state = vc4_cपंचांग_destroy_state,
पूर्ण;

अटल व्योम vc4_cपंचांग_obj_fini(काष्ठा drm_device *dev, व्योम *unused)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	drm_atomic_निजी_obj_fini(&vc4->cपंचांग_manager);
पूर्ण

अटल पूर्णांक vc4_cपंचांग_obj_init(काष्ठा vc4_dev *vc4)
अणु
	काष्ठा vc4_cपंचांग_state *cपंचांग_state;

	drm_modeset_lock_init(&vc4->cपंचांग_state_lock);

	cपंचांग_state = kzalloc(माप(*cपंचांग_state), GFP_KERNEL);
	अगर (!cपंचांग_state)
		वापस -ENOMEM;

	drm_atomic_निजी_obj_init(&vc4->base, &vc4->cपंचांग_manager, &cपंचांग_state->base,
				    &vc4_cपंचांग_state_funcs);

	वापस drmm_add_action_or_reset(&vc4->base, vc4_cपंचांग_obj_fini, शून्य);
पूर्ण

/* Converts a DRM S31.32 value to the HW S0.9 क्रमmat. */
अटल u16 vc4_cपंचांग_s31_32_to_s0_9(u64 in)
अणु
	u16 r;

	/* Sign bit. */
	r = in & BIT_ULL(63) ? BIT(9) : 0;

	अगर ((in & GENMASK_ULL(62, 32)) > 0) अणु
		/* We have zero पूर्णांकeger bits so we can only saturate here. */
		r |= GENMASK(8, 0);
	पूर्ण अन्यथा अणु
		/* Otherwise take the 9 most important fractional bits. */
		r |= (in >> 23) & GENMASK(8, 0);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम
vc4_cपंचांग_commit(काष्ठा vc4_dev *vc4, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_cपंचांग_state *cपंचांग_state = to_vc4_cपंचांग_state(vc4->cपंचांग_manager.state);
	काष्ठा drm_color_cपंचांग *cपंचांग = cपंचांग_state->cपंचांग;

	अगर (cपंचांग_state->fअगरo) अणु
		HVS_WRITE(SCALER_OLEDCOEF2,
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[0]),
					SCALER_OLEDCOEF2_R_TO_R) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[3]),
					SCALER_OLEDCOEF2_R_TO_G) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[6]),
					SCALER_OLEDCOEF2_R_TO_B));
		HVS_WRITE(SCALER_OLEDCOEF1,
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[1]),
					SCALER_OLEDCOEF1_G_TO_R) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[4]),
					SCALER_OLEDCOEF1_G_TO_G) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[7]),
					SCALER_OLEDCOEF1_G_TO_B));
		HVS_WRITE(SCALER_OLEDCOEF0,
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[2]),
					SCALER_OLEDCOEF0_B_TO_R) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[5]),
					SCALER_OLEDCOEF0_B_TO_G) |
			  VC4_SET_FIELD(vc4_cपंचांग_s31_32_to_s0_9(cपंचांग->matrix[8]),
					SCALER_OLEDCOEF0_B_TO_B));
	पूर्ण

	HVS_WRITE(SCALER_OLEDOFFS,
		  VC4_SET_FIELD(cपंचांग_state->fअगरo, SCALER_OLEDOFFS_DISPFIFO));
पूर्ण

अटल काष्ठा vc4_hvs_state *
vc4_hvs_get_new_global_state(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->dev);
	काष्ठा drm_निजी_state *priv_state;

	priv_state = drm_atomic_get_new_निजी_obj_state(state, &vc4->hvs_channels);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_vc4_hvs_state(priv_state);
पूर्ण

अटल काष्ठा vc4_hvs_state *
vc4_hvs_get_old_global_state(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->dev);
	काष्ठा drm_निजी_state *priv_state;

	priv_state = drm_atomic_get_old_निजी_obj_state(state, &vc4->hvs_channels);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_vc4_hvs_state(priv_state);
पूर्ण

अटल काष्ठा vc4_hvs_state *
vc4_hvs_get_global_state(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->dev);
	काष्ठा drm_निजी_state *priv_state;

	priv_state = drm_atomic_get_निजी_obj_state(state, &vc4->hvs_channels);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_vc4_hvs_state(priv_state);
पूर्ण

अटल व्योम vc4_hvs_pv_muxing_commit(काष्ठा vc4_dev *vc4,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc_state);
		u32 dispctrl;
		u32 dsp3_mux;

		अगर (!crtc_state->active)
			जारी;

		अगर (vc4_state->asचिन्हित_channel != 2)
			जारी;

		/*
		 * SCALER_DISPCTRL_DSP3 = X, where X < 2 means 'connect DSP3 to
		 * FIFO X'.
		 * SCALER_DISPCTRL_DSP3 = 3 means 'disable DSP 3'.
		 *
		 * DSP3 is connected to FIFO2 unless the transposer is
		 * enabled. In this हाल, FIFO 2 is directly accessed by the
		 * TXP IP, and we need to disable the FIFO2 -> pixelvalve1
		 * route.
		 */
		अगर (vc4_state->feed_txp)
			dsp3_mux = VC4_SET_FIELD(3, SCALER_DISPCTRL_DSP3_MUX);
		अन्यथा
			dsp3_mux = VC4_SET_FIELD(2, SCALER_DISPCTRL_DSP3_MUX);

		dispctrl = HVS_READ(SCALER_DISPCTRL) &
			   ~SCALER_DISPCTRL_DSP3_MUX_MASK;
		HVS_WRITE(SCALER_DISPCTRL, dispctrl | dsp3_mux);
	पूर्ण
पूर्ण

अटल व्योम vc5_hvs_pv_muxing_commit(काष्ठा vc4_dev *vc4,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित अक्षर mux;
	अचिन्हित पूर्णांक i;
	u32 reg;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा vc4_crtc_state *vc4_state = to_vc4_crtc_state(crtc_state);
		काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);

		अगर (!vc4_state->update_muxing)
			जारी;

		चयन (vc4_crtc->data->hvs_output) अणु
		हाल 2:
			mux = (vc4_state->asचिन्हित_channel == 2) ? 0 : 1;
			reg = HVS_READ(SCALER_DISPECTRL);
			HVS_WRITE(SCALER_DISPECTRL,
				  (reg & ~SCALER_DISPECTRL_DSP2_MUX_MASK) |
				  VC4_SET_FIELD(mux, SCALER_DISPECTRL_DSP2_MUX));
			अवरोध;

		हाल 3:
			अगर (vc4_state->asचिन्हित_channel == VC4_HVS_CHANNEL_DISABLED)
				mux = 3;
			अन्यथा
				mux = vc4_state->asचिन्हित_channel;

			reg = HVS_READ(SCALER_DISPCTRL);
			HVS_WRITE(SCALER_DISPCTRL,
				  (reg & ~SCALER_DISPCTRL_DSP3_MUX_MASK) |
				  VC4_SET_FIELD(mux, SCALER_DISPCTRL_DSP3_MUX));
			अवरोध;

		हाल 4:
			अगर (vc4_state->asचिन्हित_channel == VC4_HVS_CHANNEL_DISABLED)
				mux = 3;
			अन्यथा
				mux = vc4_state->asचिन्हित_channel;

			reg = HVS_READ(SCALER_DISPEOLN);
			HVS_WRITE(SCALER_DISPEOLN,
				  (reg & ~SCALER_DISPEOLN_DSP4_MUX_MASK) |
				  VC4_SET_FIELD(mux, SCALER_DISPEOLN_DSP4_MUX));

			अवरोध;

		हाल 5:
			अगर (vc4_state->asचिन्हित_channel == VC4_HVS_CHANNEL_DISABLED)
				mux = 3;
			अन्यथा
				mux = vc4_state->asचिन्हित_channel;

			reg = HVS_READ(SCALER_DISPDITHER);
			HVS_WRITE(SCALER_DISPDITHER,
				  (reg & ~SCALER_DISPDITHER_DSP5_MUX_MASK) |
				  VC4_SET_FIELD(mux, SCALER_DISPDITHER_DSP5_MUX));
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vc4_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_hvs *hvs = vc4->hvs;
	काष्ठा drm_crtc_state *old_crtc_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा vc4_hvs_state *old_hvs_state;
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		काष्ठा vc4_crtc_state *vc4_crtc_state;

		अगर (!new_crtc_state->commit)
			जारी;

		vc4_crtc_state = to_vc4_crtc_state(new_crtc_state);
		vc4_hvs_mask_underrun(dev, vc4_crtc_state->asचिन्हित_channel);
	पूर्ण

	अगर (vc4->hvs->hvs5)
		clk_set_min_rate(hvs->core_clk, 500000000);

	old_hvs_state = vc4_hvs_get_old_global_state(state);
	अगर (!old_hvs_state)
		वापस;

	क्रम_each_old_crtc_in_state(state, crtc, old_crtc_state, i) अणु
		काष्ठा vc4_crtc_state *vc4_crtc_state =
			to_vc4_crtc_state(old_crtc_state);
		अचिन्हित पूर्णांक channel = vc4_crtc_state->asचिन्हित_channel;
		पूर्णांक ret;

		अगर (channel == VC4_HVS_CHANNEL_DISABLED)
			जारी;

		अगर (!old_hvs_state->fअगरo_state[channel].in_use)
			जारी;

		ret = drm_crtc_commit_रुको(old_hvs_state->fअगरo_state[channel].pending_commit);
		अगर (ret)
			drm_err(dev, "Timed out waiting for commit\n");
	पूर्ण

	drm_atomic_helper_commit_modeset_disables(dev, state);

	vc4_cपंचांग_commit(vc4, state);

	अगर (vc4->hvs->hvs5)
		vc5_hvs_pv_muxing_commit(vc4, state);
	अन्यथा
		vc4_hvs_pv_muxing_commit(vc4, state);

	drm_atomic_helper_commit_planes(dev, state, 0);

	drm_atomic_helper_commit_modeset_enables(dev, state);

	drm_atomic_helper_fake_vblank(state);

	drm_atomic_helper_commit_hw_करोne(state);

	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, state);

	drm_atomic_helper_cleanup_planes(dev, state);

	अगर (vc4->hvs->hvs5)
		clk_set_min_rate(hvs->core_clk, 0);
पूर्ण

अटल पूर्णांक vc4_atomic_commit_setup(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा vc4_hvs_state *hvs_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;

	hvs_state = vc4_hvs_get_new_global_state(state);
	अगर (!hvs_state)
		वापस -EINVAL;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा vc4_crtc_state *vc4_crtc_state =
			to_vc4_crtc_state(crtc_state);
		अचिन्हित पूर्णांक channel =
			vc4_crtc_state->asचिन्हित_channel;

		अगर (channel == VC4_HVS_CHANNEL_DISABLED)
			जारी;

		अगर (!hvs_state->fअगरo_state[channel].in_use)
			जारी;

		hvs_state->fअगरo_state[channel].pending_commit =
			drm_crtc_commit_get(crtc_state->commit);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_framebuffer *vc4_fb_create(काष्ठा drm_device *dev,
					     काष्ठा drm_file *file_priv,
					     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_mode_fb_cmd2 mode_cmd_local;

	/* If the user didn't specअगरy a modअगरier, use the
	 * vc4_set_tiling_ioctl() state क्रम the BO.
	 */
	अगर (!(mode_cmd->flags & DRM_MODE_FB_MODIFIERS)) अणु
		काष्ठा drm_gem_object *gem_obj;
		काष्ठा vc4_bo *bo;

		gem_obj = drm_gem_object_lookup(file_priv,
						mode_cmd->handles[0]);
		अगर (!gem_obj) अणु
			DRM_DEBUG("Failed to look up GEM BO %d\n",
				  mode_cmd->handles[0]);
			वापस ERR_PTR(-ENOENT);
		पूर्ण
		bo = to_vc4_bo(gem_obj);

		mode_cmd_local = *mode_cmd;

		अगर (bo->t_क्रमmat) अणु
			mode_cmd_local.modअगरier[0] =
				DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED;
		पूर्ण अन्यथा अणु
			mode_cmd_local.modअगरier[0] = DRM_FORMAT_MOD_NONE;
		पूर्ण

		drm_gem_object_put(gem_obj);

		mode_cmd = &mode_cmd_local;
	पूर्ण

	वापस drm_gem_fb_create(dev, file_priv, mode_cmd);
पूर्ण

/* Our CTM has some peculiar limitations: we can only enable it क्रम one CRTC
 * at a समय and the HW only supports S0.9 scalars. To account क्रम the latter,
 * we करोn't allow userland to set a CTM that we have no hope of approximating.
 */
अटल पूर्णांक
vc4_cपंचांग_atomic_check(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_cपंचांग_state *cपंचांग_state = शून्य;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_color_cपंचांग *cपंचांग;
	पूर्णांक i;

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		/* CTM is being disabled. */
		अगर (!new_crtc_state->cपंचांग && old_crtc_state->cपंचांग) अणु
			cपंचांग_state = vc4_get_cपंचांग_state(state, &vc4->cपंचांग_manager);
			अगर (IS_ERR(cपंचांग_state))
				वापस PTR_ERR(cपंचांग_state);
			cपंचांग_state->fअगरo = 0;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		अगर (new_crtc_state->cपंचांग == old_crtc_state->cपंचांग)
			जारी;

		अगर (!cपंचांग_state) अणु
			cपंचांग_state = vc4_get_cपंचांग_state(state, &vc4->cपंचांग_manager);
			अगर (IS_ERR(cपंचांग_state))
				वापस PTR_ERR(cपंचांग_state);
		पूर्ण

		/* CTM is being enabled or the matrix changed. */
		अगर (new_crtc_state->cपंचांग) अणु
			काष्ठा vc4_crtc_state *vc4_crtc_state =
				to_vc4_crtc_state(new_crtc_state);

			/* fअगरo is 1-based since 0 disables CTM. */
			पूर्णांक fअगरo = vc4_crtc_state->asचिन्हित_channel + 1;

			/* Check userland isn't trying to turn on CTM क्रम more
			 * than one CRTC at a समय.
			 */
			अगर (cपंचांग_state->fअगरo && cपंचांग_state->fअगरo != fअगरo) अणु
				DRM_DEBUG_DRIVER("Too many CTM configured\n");
				वापस -EINVAL;
			पूर्ण

			/* Check we can approximate the specअगरied CTM.
			 * We disallow scalars |c| > 1.0 since the HW has
			 * no पूर्णांकeger bits.
			 */
			cपंचांग = new_crtc_state->cपंचांग->data;
			क्रम (i = 0; i < ARRAY_SIZE(cपंचांग->matrix); i++) अणु
				u64 val = cपंचांग->matrix[i];

				val &= ~BIT_ULL(63);
				अगर (val > BIT_ULL(32))
					वापस -EINVAL;
			पूर्ण

			cपंचांग_state->fअगरo = fअगरo;
			cपंचांग_state->cपंचांग = cपंचांग;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_load_tracker_atomic_check(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(state->dev);
	काष्ठा vc4_load_tracker_state *load_state;
	काष्ठा drm_निजी_state *priv_state;
	काष्ठा drm_plane *plane;
	पूर्णांक i;

	अगर (!vc4->load_tracker_available)
		वापस 0;

	priv_state = drm_atomic_get_निजी_obj_state(state,
						      &vc4->load_tracker);
	अगर (IS_ERR(priv_state))
		वापस PTR_ERR(priv_state);

	load_state = to_vc4_load_tracker_state(priv_state);
	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state,
				       new_plane_state, i) अणु
		काष्ठा vc4_plane_state *vc4_plane_state;

		अगर (old_plane_state->fb && old_plane_state->crtc) अणु
			vc4_plane_state = to_vc4_plane_state(old_plane_state);
			load_state->membus_load -= vc4_plane_state->membus_load;
			load_state->hvs_load -= vc4_plane_state->hvs_load;
		पूर्ण

		अगर (new_plane_state->fb && new_plane_state->crtc) अणु
			vc4_plane_state = to_vc4_plane_state(new_plane_state);
			load_state->membus_load += vc4_plane_state->membus_load;
			load_state->hvs_load += vc4_plane_state->hvs_load;
		पूर्ण
	पूर्ण

	/* Don't check the load when the tracker is disabled. */
	अगर (!vc4->load_tracker_enabled)
		वापस 0;

	/* The असलolute limit is 2Gbyte/sec, but let's take a margin to let
	 * the प्रणाली work when other blocks are accessing the memory.
	 */
	अगर (load_state->membus_load > SZ_1G + SZ_512M)
		वापस -ENOSPC;

	/* HVS घड़ी is supposed to run @ 250Mhz, let's take a margin and
	 * consider the maximum number of cycles is 240M.
	 */
	अगर (load_state->hvs_load > 240000000ULL)
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल काष्ठा drm_निजी_state *
vc4_load_tracker_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा vc4_load_tracker_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम vc4_load_tracker_destroy_state(काष्ठा drm_निजी_obj *obj,
					   काष्ठा drm_निजी_state *state)
अणु
	काष्ठा vc4_load_tracker_state *load_state;

	load_state = to_vc4_load_tracker_state(state);
	kमुक्त(load_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs vc4_load_tracker_state_funcs = अणु
	.atomic_duplicate_state = vc4_load_tracker_duplicate_state,
	.atomic_destroy_state = vc4_load_tracker_destroy_state,
पूर्ण;

अटल व्योम vc4_load_tracker_obj_fini(काष्ठा drm_device *dev, व्योम *unused)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	अगर (!vc4->load_tracker_available)
		वापस;

	drm_atomic_निजी_obj_fini(&vc4->load_tracker);
पूर्ण

अटल पूर्णांक vc4_load_tracker_obj_init(काष्ठा vc4_dev *vc4)
अणु
	काष्ठा vc4_load_tracker_state *load_state;

	अगर (!vc4->load_tracker_available)
		वापस 0;

	load_state = kzalloc(माप(*load_state), GFP_KERNEL);
	अगर (!load_state)
		वापस -ENOMEM;

	drm_atomic_निजी_obj_init(&vc4->base, &vc4->load_tracker,
				    &load_state->base,
				    &vc4_load_tracker_state_funcs);

	वापस drmm_add_action_or_reset(&vc4->base, vc4_load_tracker_obj_fini, शून्य);
पूर्ण

अटल काष्ठा drm_निजी_state *
vc4_hvs_channels_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा vc4_hvs_state *old_state = to_vc4_hvs_state(obj->state);
	काष्ठा vc4_hvs_state *state;
	अचिन्हित पूर्णांक i;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);


	क्रम (i = 0; i < HVS_NUM_CHANNELS; i++) अणु
		state->fअगरo_state[i].in_use = old_state->fअगरo_state[i].in_use;

		अगर (!old_state->fअगरo_state[i].pending_commit)
			जारी;

		state->fअगरo_state[i].pending_commit =
			drm_crtc_commit_get(old_state->fअगरo_state[i].pending_commit);
	पूर्ण

	वापस &state->base;
पूर्ण

अटल व्योम vc4_hvs_channels_destroy_state(काष्ठा drm_निजी_obj *obj,
					   काष्ठा drm_निजी_state *state)
अणु
	काष्ठा vc4_hvs_state *hvs_state = to_vc4_hvs_state(state);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < HVS_NUM_CHANNELS; i++) अणु
		अगर (!hvs_state->fअगरo_state[i].pending_commit)
			जारी;

		drm_crtc_commit_put(hvs_state->fअगरo_state[i].pending_commit);
	पूर्ण

	kमुक्त(hvs_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs vc4_hvs_state_funcs = अणु
	.atomic_duplicate_state = vc4_hvs_channels_duplicate_state,
	.atomic_destroy_state = vc4_hvs_channels_destroy_state,
पूर्ण;

अटल व्योम vc4_hvs_channels_obj_fini(काष्ठा drm_device *dev, व्योम *unused)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	drm_atomic_निजी_obj_fini(&vc4->hvs_channels);
पूर्ण

अटल पूर्णांक vc4_hvs_channels_obj_init(काष्ठा vc4_dev *vc4)
अणु
	काष्ठा vc4_hvs_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	drm_atomic_निजी_obj_init(&vc4->base, &vc4->hvs_channels,
				    &state->base,
				    &vc4_hvs_state_funcs);

	वापस drmm_add_action_or_reset(&vc4->base, vc4_hvs_channels_obj_fini, शून्य);
पूर्ण

/*
 * The BCM2711 HVS has up to 7 outमाला_दो connected to the pixelvalves and
 * the TXP (and thereक्रमe all the CRTCs found on that platक्रमm).
 *
 * The naive (and our initial) implementation would just iterate over
 * all the active CRTCs, try to find a suitable FIFO, and then हटाओ it
 * from the pool of available FIFOs. However, there are a few corner
 * हालs that need to be considered:
 *
 * - When running in a dual-display setup (so with two CRTCs involved),
 *   we can update the state of a single CRTC (क्रम example by changing
 *   its mode using xअक्रमr under X11) without affecting the other. In
 *   this हाल, the other CRTC wouldn't be in the state at all, so we
 *   need to consider all the running CRTCs in the DRM device to assign
 *   a FIFO, not just the one in the state.
 *
 * - To fix the above, we can't use drm_atomic_get_crtc_state on all
 *   enabled CRTCs to pull their CRTC state पूर्णांकo the global state, since
 *   a page flip would start considering their vblank to complete. Since
 *   we करोn't have a guarantee that they are actually active, that
 *   vblank might never happen, and shouldn't even be considered अगर we
 *   want to करो a page flip on a single CRTC. That can be tested by
 *   करोing a modetest -v first on HDMI1 and then on HDMI0.
 *
 * - Since we need the pixelvalve to be disabled and enabled back when
 *   the FIFO is changed, we should keep the FIFO asचिन्हित क्रम as दीर्घ
 *   as the CRTC is enabled, only considering it मुक्त again once that
 *   CRTC has been disabled. This can be tested by booting X11 on a
 *   single display, and changing the resolution करोwn and then back up.
 */
अटल पूर्णांक vc4_pv_muxing_atomic_check(काष्ठा drm_device *dev,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_hvs_state *hvs_new_state;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक unasचिन्हित_channels = 0;
	अचिन्हित पूर्णांक i;

	hvs_new_state = vc4_hvs_get_global_state(state);
	अगर (!hvs_new_state)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(hvs_new_state->fअगरo_state); i++)
		अगर (!hvs_new_state->fअगरo_state[i].in_use)
			unasचिन्हित_channels |= BIT(i);

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		काष्ठा vc4_crtc_state *old_vc4_crtc_state =
			to_vc4_crtc_state(old_crtc_state);
		काष्ठा vc4_crtc_state *new_vc4_crtc_state =
			to_vc4_crtc_state(new_crtc_state);
		काष्ठा vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
		अचिन्हित पूर्णांक matching_channels;
		अचिन्हित पूर्णांक channel;

		/* Nothing to करो here, let's skip it */
		अगर (old_crtc_state->enable == new_crtc_state->enable)
			जारी;

		/* Muxing will need to be modअगरied, mark it as such */
		new_vc4_crtc_state->update_muxing = true;

		/* If we're disabling our CRTC, we put back our channel */
		अगर (!new_crtc_state->enable) अणु
			channel = old_vc4_crtc_state->asचिन्हित_channel;
			hvs_new_state->fअगरo_state[channel].in_use = false;
			new_vc4_crtc_state->asचिन्हित_channel = VC4_HVS_CHANNEL_DISABLED;
			जारी;
		पूर्ण

		/*
		 * The problem we have to solve here is that we have
		 * up to 7 encoders, connected to up to 6 CRTCs.
		 *
		 * Those CRTCs, depending on the instance, can be
		 * routed to 1, 2 or 3 HVS FIFOs, and we need to set
		 * the change the muxing between FIFOs and outमाला_दो in
		 * the HVS accordingly.
		 *
		 * It would be pretty hard to come up with an
		 * algorithm that would generically solve
		 * this. However, the current routing trees we support
		 * allow us to simplअगरy a bit the problem.
		 *
		 * Indeed, with the current supported layouts, अगर we
		 * try to assign in the ascending crtc index order the
		 * FIFOs, we can't fall पूर्णांकo the situation where an
		 * earlier CRTC that had multiple routes is asचिन्हित
		 * one that was the only option क्रम a later CRTC.
		 *
		 * If the layout changes and करोesn't give us that in
		 * the future, we will need to have something smarter,
		 * but it works so far.
		 */
		matching_channels = unasचिन्हित_channels & vc4_crtc->data->hvs_available_channels;
		अगर (!matching_channels)
			वापस -EINVAL;

		channel = ffs(matching_channels) - 1;
		new_vc4_crtc_state->asचिन्हित_channel = channel;
		unasचिन्हित_channels &= ~BIT(channel);
		hvs_new_state->fअगरo_state[channel].in_use = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vc4_atomic_check(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक ret;

	ret = vc4_pv_muxing_atomic_check(dev, state);
	अगर (ret)
		वापस ret;

	ret = vc4_cपंचांग_atomic_check(dev, state);
	अगर (ret < 0)
		वापस ret;

	ret = drm_atomic_helper_check(dev, state);
	अगर (ret)
		वापस ret;

	वापस vc4_load_tracker_atomic_check(state);
पूर्ण

अटल काष्ठा drm_mode_config_helper_funcs vc4_mode_config_helpers = अणु
	.atomic_commit_setup	= vc4_atomic_commit_setup,
	.atomic_commit_tail	= vc4_atomic_commit_tail,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs vc4_mode_funcs = अणु
	.atomic_check = vc4_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
	.fb_create = vc4_fb_create,
पूर्ण;

पूर्णांक vc4_kms_load(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	bool is_vc5 = of_device_is_compatible(dev->dev->of_node,
					      "brcm,bcm2711-vc5");
	पूर्णांक ret;

	अगर (!is_vc5) अणु
		vc4->load_tracker_available = true;

		/* Start with the load tracker enabled. Can be
		 * disabled through the debugfs load_tracker file.
		 */
		vc4->load_tracker_enabled = true;
	पूर्ण

	/* Set support क्रम vblank irq fast disable, beक्रमe drm_vblank_init() */
	dev->vblank_disable_immediate = true;

	dev->irq_enabled = true;
	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to initialize vblank\n");
		वापस ret;
	पूर्ण

	अगर (is_vc5) अणु
		dev->mode_config.max_width = 7680;
		dev->mode_config.max_height = 7680;
	पूर्ण अन्यथा अणु
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	पूर्ण

	dev->mode_config.funcs = &vc4_mode_funcs;
	dev->mode_config.helper_निजी = &vc4_mode_config_helpers;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.async_page_flip = true;
	dev->mode_config.allow_fb_modअगरiers = true;

	ret = vc4_cपंचांग_obj_init(vc4);
	अगर (ret)
		वापस ret;

	ret = vc4_load_tracker_obj_init(vc4);
	अगर (ret)
		वापस ret;

	ret = vc4_hvs_channels_obj_init(vc4);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(dev);

	drm_kms_helper_poll_init(dev);

	वापस 0;
पूर्ण
