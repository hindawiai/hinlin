<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश "intel_atomic.h"
#समावेश "intel_ddi.h"
#समावेश "intel_ddi_buf_trans.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fdi.h"

/* units of 100MHz */
अटल पूर्णांक pipe_required_fdi_lanes(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (crtc_state->hw.enable && crtc_state->has_pch_encoder)
		वापस crtc_state->fdi_lanes;

	वापस 0;
पूर्ण

अटल पूर्णांक ilk_check_fdi_lanes(काष्ठा drm_device *dev, क्रमागत pipe pipe,
			       काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_atomic_state *state = pipe_config->uapi.state;
	काष्ठा पूर्णांकel_crtc *other_crtc;
	काष्ठा पूर्णांकel_crtc_state *other_crtc_state;

	drm_dbg_kms(&dev_priv->drm,
		    "checking fdi config on pipe %c, lanes %i\n",
		    pipe_name(pipe), pipe_config->fdi_lanes);
	अगर (pipe_config->fdi_lanes > 4) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "invalid fdi lane config on pipe %c: %i lanes\n",
			    pipe_name(pipe), pipe_config->fdi_lanes);
		वापस -EINVAL;
	पूर्ण

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		अगर (pipe_config->fdi_lanes > 2) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "only 2 lanes on haswell, required: %i lanes\n",
				    pipe_config->fdi_lanes);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (INTEL_NUM_PIPES(dev_priv) == 2)
		वापस 0;

	/* Ivybridge 3 pipe is really complicated */
	चयन (pipe) अणु
	हाल PIPE_A:
		वापस 0;
	हाल PIPE_B:
		अगर (pipe_config->fdi_lanes <= 2)
			वापस 0;

		other_crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, PIPE_C);
		other_crtc_state =
			पूर्णांकel_atomic_get_crtc_state(state, other_crtc);
		अगर (IS_ERR(other_crtc_state))
			वापस PTR_ERR(other_crtc_state);

		अगर (pipe_required_fdi_lanes(other_crtc_state) > 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "invalid shared fdi lane config on pipe %c: %i lanes\n",
				    pipe_name(pipe), pipe_config->fdi_lanes);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	हाल PIPE_C:
		अगर (pipe_config->fdi_lanes > 2) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "only 2 lanes on pipe %c: required %i lanes\n",
				    pipe_name(pipe), pipe_config->fdi_lanes);
			वापस -EINVAL;
		पूर्ण

		other_crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, PIPE_B);
		other_crtc_state =
			पूर्णांकel_atomic_get_crtc_state(state, other_crtc);
		अगर (IS_ERR(other_crtc_state))
			वापस PTR_ERR(other_crtc_state);

		अगर (pipe_required_fdi_lanes(other_crtc_state) > 2) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "fdi link B uses too many lanes to enable link C\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	शेष:
		BUG();
	पूर्ण
पूर्ण

पूर्णांक ilk_fdi_compute_config(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_crtc->base.dev;
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	पूर्णांक lane, link_bw, fdi_करोtघड़ी, ret;
	bool needs_recompute = false;

retry:
	/* FDI is a binary संकेत running at ~2.7GHz, encoding
	 * each output octet as 10 bits. The actual frequency
	 * is stored as a भागider पूर्णांकo a 100MHz घड़ी, and the
	 * mode pixel घड़ी is stored in units of 1KHz.
	 * Hence the bw of each lane in terms of the mode संकेत
	 * is:
	 */
	link_bw = पूर्णांकel_fdi_link_freq(i915, pipe_config);

	fdi_करोtघड़ी = adjusted_mode->crtc_घड़ी;

	lane = ilk_get_lanes_required(fdi_करोtघड़ी, link_bw,
				      pipe_config->pipe_bpp);

	pipe_config->fdi_lanes = lane;

	पूर्णांकel_link_compute_m_n(pipe_config->pipe_bpp, lane, fdi_करोtघड़ी,
			       link_bw, &pipe_config->fdi_m_n, false, false);

	ret = ilk_check_fdi_lanes(dev, पूर्णांकel_crtc->pipe, pipe_config);
	अगर (ret == -EDEADLK)
		वापस ret;

	अगर (ret == -EINVAL && pipe_config->pipe_bpp > 6*3) अणु
		pipe_config->pipe_bpp -= 2*3;
		drm_dbg_kms(&i915->drm,
			    "fdi link bw constraint, reducing pipe bpp to %i\n",
			    pipe_config->pipe_bpp);
		needs_recompute = true;
		pipe_config->bw_स्थिरrained = true;

		जाओ retry;
	पूर्ण

	अगर (needs_recompute)
		वापस I915_DISPLAY_CONFIG_RETRY;

	वापस ret;
पूर्ण

व्योम पूर्णांकel_fdi_normal_train(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp;

	/* enable normal train */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (IS_IVYBRIDGE(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_NONE_IVB;
		temp |= FDI_LINK_TRAIN_NONE_IVB | FDI_TX_ENHANCE_FRAME_ENABLE;
	पूर्ण अन्यथा अणु
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_NONE | FDI_TX_ENHANCE_FRAME_ENABLE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (HAS_PCH_CPT(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_NORMAL_CPT;
	पूर्ण अन्यथा अणु
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_NONE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_ENHANCE_FRAME_ENABLE);

	/* रुको one idle pattern समय */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(1000);

	/* IVB wants error correction enabled */
	अगर (IS_IVYBRIDGE(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, reg,
			       पूर्णांकel_de_पढ़ो(dev_priv, reg) | FDI_FS_ERRC_ENABLE | FDI_FE_ERRC_ENABLE);
पूर्ण

/* The FDI link training functions क्रम ILK/Ibexpeak. */
अटल व्योम ilk_fdi_link_train(काष्ठा पूर्णांकel_crtc *crtc,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp, tries;

	/* FDI needs bits from pipe first */
	निश्चित_pipe_enabled(dev_priv, crtc_state->cpu_transcoder);

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   क्रम train result */
	reg = FDI_RX_IMR(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);
	पूर्णांकel_de_पढ़ो(dev_priv, reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_DP_PORT_WIDTH_MASK;
	temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_TX_ENABLE);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_ENABLE);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	/* Ironlake workaround, enable घड़ी poपूर्णांकer after FDI enable*/
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CHICKEN(pipe),
		       FDI_RX_PHASE_SYNC_POINTER_OVR);
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CHICKEN(pipe),
		       FDI_RX_PHASE_SYNC_POINTER_OVR | FDI_RX_PHASE_SYNC_POINTER_EN);

	reg = FDI_RX_IIR(pipe);
	क्रम (tries = 0; tries < 5; tries++) अणु
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);

		अगर ((temp & FDI_RX_BIT_LOCK)) अणु
			drm_dbg_kms(&dev_priv->drm, "FDI train 1 done.\n");
			पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_BIT_LOCK);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (tries == 5)
		drm_err(&dev_priv->drm, "FDI train 1 fail!\n");

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	reg = FDI_RX_IIR(pipe);
	क्रम (tries = 0; tries < 5; tries++) अणु
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);

		अगर (temp & FDI_RX_SYMBOL_LOCK) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, reg,
				       temp | FDI_RX_SYMBOL_LOCK);
			drm_dbg_kms(&dev_priv->drm, "FDI train 2 done.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (tries == 5)
		drm_err(&dev_priv->drm, "FDI train 2 fail!\n");

	drm_dbg_kms(&dev_priv->drm, "FDI train done\n");

पूर्ण

अटल स्थिर पूर्णांक snb_b_fdi_train_param[] = अणु
	FDI_LINK_TRAIN_400MV_0DB_SNB_B,
	FDI_LINK_TRAIN_400MV_6DB_SNB_B,
	FDI_LINK_TRAIN_600MV_3_5DB_SNB_B,
	FDI_LINK_TRAIN_800MV_0DB_SNB_B,
पूर्ण;

/* The FDI link training functions क्रम SNB/Cougarpoपूर्णांक. */
अटल व्योम gen6_fdi_link_train(काष्ठा पूर्णांकel_crtc *crtc,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp, i, retry;

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   क्रम train result */
	reg = FDI_RX_IMR(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	/* enable CPU FDI TX and PCH FDI RX */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_DP_PORT_WIDTH_MASK;
	temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
	/* SNB-B */
	temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_TX_ENABLE);

	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(pipe),
		       FDI_RX_TP1_TO_TP2_48 | FDI_RX_FDI_DELAY_90);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (HAS_PCH_CPT(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
	पूर्ण अन्यथा अणु
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_1;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_ENABLE);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	क्रम (i = 0; i < 4; i++) अणु
		reg = FDI_TX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(500);

		क्रम (retry = 0; retry < 5; retry++) अणु
			reg = FDI_RX_IIR(pipe);
			temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
			drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);
			अगर (temp & FDI_RX_BIT_LOCK) अणु
				पूर्णांकel_de_ग_लिखो(dev_priv, reg,
					       temp | FDI_RX_BIT_LOCK);
				drm_dbg_kms(&dev_priv->drm,
					    "FDI train 1 done.\n");
				अवरोध;
			पूर्ण
			udelay(50);
		पूर्ण
		अगर (retry < 5)
			अवरोध;
	पूर्ण
	अगर (i == 4)
		drm_err(&dev_priv->drm, "FDI train 1 fail!\n");

	/* Train 2 */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_2;
	अगर (IS_SANDYBRIDGE(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		/* SNB-B */
		temp |= FDI_LINK_TRAIN_400MV_0DB_SNB_B;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (HAS_PCH_CPT(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_2_CPT;
	पूर्ण अन्यथा अणु
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_2;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	क्रम (i = 0; i < 4; i++) अणु
		reg = FDI_TX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[i];
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(500);

		क्रम (retry = 0; retry < 5; retry++) अणु
			reg = FDI_RX_IIR(pipe);
			temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
			drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);
			अगर (temp & FDI_RX_SYMBOL_LOCK) अणु
				पूर्णांकel_de_ग_लिखो(dev_priv, reg,
					       temp | FDI_RX_SYMBOL_LOCK);
				drm_dbg_kms(&dev_priv->drm,
					    "FDI train 2 done.\n");
				अवरोध;
			पूर्ण
			udelay(50);
		पूर्ण
		अगर (retry < 5)
			अवरोध;
	पूर्ण
	अगर (i == 4)
		drm_err(&dev_priv->drm, "FDI train 2 fail!\n");

	drm_dbg_kms(&dev_priv->drm, "FDI train done.\n");
पूर्ण

/* Manual link training क्रम Ivy Bridge A0 parts */
अटल व्योम ivb_manual_fdi_link_train(काष्ठा पूर्णांकel_crtc *crtc,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp, i, j;

	/* Train 1: umask FDI RX Interrupt symbol_lock and bit_lock bit
	   क्रम train result */
	reg = FDI_RX_IMR(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_RX_SYMBOL_LOCK;
	temp &= ~FDI_RX_BIT_LOCK;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR before link train 0x%x\n",
		    पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_IIR(pipe)));

	/* Try each vswing and preemphasis setting twice beक्रमe moving on */
	क्रम (j = 0; j < ARRAY_SIZE(snb_b_fdi_train_param) * 2; j++) अणु
		/* disable first in हाल we need to retry */
		reg = FDI_TX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~(FDI_LINK_TRAIN_AUTO | FDI_LINK_TRAIN_NONE_IVB);
		temp &= ~FDI_TX_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		reg = FDI_RX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_LINK_TRAIN_AUTO;
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp &= ~FDI_RX_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		/* enable CPU FDI TX and PCH FDI RX */
		reg = FDI_TX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_DP_PORT_WIDTH_MASK;
		temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
		temp |= FDI_LINK_TRAIN_PATTERN_1_IVB;
		temp &= ~FDI_LINK_TRAIN_VOL_EMP_MASK;
		temp |= snb_b_fdi_train_param[j/2];
		temp |= FDI_COMPOSITE_SYNC;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_TX_ENABLE);

		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(pipe),
			       FDI_RX_TP1_TO_TP2_48 | FDI_RX_FDI_DELAY_90);

		reg = FDI_RX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
		temp |= FDI_COMPOSITE_SYNC;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_ENABLE);

		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(1); /* should be 0.5us */

		क्रम (i = 0; i < 4; i++) अणु
			reg = FDI_RX_IIR(pipe);
			temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
			drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);

			अगर (temp & FDI_RX_BIT_LOCK ||
			    (पूर्णांकel_de_पढ़ो(dev_priv, reg) & FDI_RX_BIT_LOCK)) अणु
				पूर्णांकel_de_ग_लिखो(dev_priv, reg,
					       temp | FDI_RX_BIT_LOCK);
				drm_dbg_kms(&dev_priv->drm,
					    "FDI train 1 done, level %i.\n",
					    i);
				अवरोध;
			पूर्ण
			udelay(1); /* should be 0.5us */
		पूर्ण
		अगर (i == 4) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "FDI train 1 fail on vswing %d\n", j / 2);
			जारी;
		पूर्ण

		/* Train 2 */
		reg = FDI_TX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_LINK_TRAIN_NONE_IVB;
		temp |= FDI_LINK_TRAIN_PATTERN_2_IVB;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		reg = FDI_RX_CTL(pipe);
		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_2_CPT;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(2); /* should be 1.5us */

		क्रम (i = 0; i < 4; i++) अणु
			reg = FDI_RX_IIR(pipe);
			temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
			drm_dbg_kms(&dev_priv->drm, "FDI_RX_IIR 0x%x\n", temp);

			अगर (temp & FDI_RX_SYMBOL_LOCK ||
			    (पूर्णांकel_de_पढ़ो(dev_priv, reg) & FDI_RX_SYMBOL_LOCK)) अणु
				पूर्णांकel_de_ग_लिखो(dev_priv, reg,
					       temp | FDI_RX_SYMBOL_LOCK);
				drm_dbg_kms(&dev_priv->drm,
					    "FDI train 2 done, level %i.\n",
					    i);
				जाओ train_करोne;
			पूर्ण
			udelay(2); /* should be 1.5us */
		पूर्ण
		अगर (i == 4)
			drm_dbg_kms(&dev_priv->drm,
				    "FDI train 2 fail on vswing %d\n", j / 2);
	पूर्ण

train_करोne:
	drm_dbg_kms(&dev_priv->drm, "FDI train done.\n");
पूर्ण

/* Starting with Haswell, dअगरferent DDI ports can work in FDI mode क्रम
 * connection to the PCH-located connectors. For this, it is necessary to train
 * both the DDI port and PCH receiver क्रम the desired DDI buffer settings.
 *
 * The recommended port to work in FDI mode is DDI E, which we use here. Also,
 * please note that when FDI mode is active on DDI E, it shares 2 lines with
 * DDI A (which is used क्रम eDP)
 */
व्योम hsw_fdi_link_train(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 temp, i, rx_ctl_val;
	पूर्णांक n_entries;

	पूर्णांकel_ddi_get_buf_trans_fdi(dev_priv, &n_entries);

	पूर्णांकel_prepare_dp_ddi_buffers(encoder, crtc_state);

	/* Set the FDI_RX_MISC pwrdn lanes and the 2 workarounds listed at the
	 * mode set "sequence for CRT port" करोcument:
	 * - TP1 to TP2 समय with the शेष value
	 * - FDI delay to 90h
	 *
	 * WaFDIAutoLinkSetTimingOverrride:hsw
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(PIPE_A),
		       FDI_RX_PWRDN_LANE1_VAL(2) | FDI_RX_PWRDN_LANE0_VAL(2) | FDI_RX_TP1_TO_TP2_48 | FDI_RX_FDI_DELAY_90);

	/* Enable the PCH Receiver FDI PLL */
	rx_ctl_val = dev_priv->fdi_rx_config | FDI_RX_ENHANCE_FRAME_ENABLE |
		     FDI_RX_PLL_ENABLE |
		     FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), rx_ctl_val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));
	udelay(220);

	/* Switch from Rawclk to PCDclk */
	rx_ctl_val |= FDI_PCDCLK;
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), rx_ctl_val);

	/* Configure Port Clock Select */
	drm_WARN_ON(&dev_priv->drm, crtc_state->shared_dpll->info->id != DPLL_ID_SPLL);
	पूर्णांकel_ddi_enable_घड़ी(encoder, crtc_state);

	/* Start the training iterating through available voltages and emphasis,
	 * testing each value twice. */
	क्रम (i = 0; i < n_entries * 2; i++) अणु
		/* Configure DP_TP_CTL with स्वतः-training */
		पूर्णांकel_de_ग_लिखो(dev_priv, DP_TP_CTL(PORT_E),
			       DP_TP_CTL_FDI_AUTOTRAIN |
			       DP_TP_CTL_ENHANCED_FRAME_ENABLE |
			       DP_TP_CTL_LINK_TRAIN_PAT1 |
			       DP_TP_CTL_ENABLE);

		/* Configure and enable DDI_BUF_CTL क्रम DDI E with next voltage.
		 * DDI E करोes not support port reversal, the functionality is
		 * achieved on the PCH side in FDI_RX_CTL, so no need to set the
		 * port reversal bit */
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(PORT_E),
			       DDI_BUF_CTL_ENABLE | ((crtc_state->fdi_lanes - 1) << 1) | DDI_BUF_TRANS_SELECT(i / 2));
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_E));

		udelay(600);

		/* Program PCH FDI Receiver TU */
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_TUSIZE1(PIPE_A), TU_SIZE(64));

		/* Enable PCH FDI Receiver with स्वतः-training */
		rx_ctl_val |= FDI_RX_ENABLE | FDI_LINK_TRAIN_AUTO;
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), rx_ctl_val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));

		/* Wait क्रम FDI receiver lane calibration */
		udelay(30);

		/* Unset FDI_RX_MISC pwrdn lanes */
		temp = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_MISC(PIPE_A));
		temp &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(PIPE_A), temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, FDI_RX_MISC(PIPE_A));

		/* Wait क्रम FDI स्वतः training समय */
		udelay(5);

		temp = पूर्णांकel_de_पढ़ो(dev_priv, DP_TP_STATUS(PORT_E));
		अगर (temp & DP_TP_STATUS_AUTOTRAIN_DONE) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "FDI link training done on step %d\n", i);
			अवरोध;
		पूर्ण

		/*
		 * Leave things enabled even अगर we failed to train FDI.
		 * Results in less fireworks from the state checker.
		 */
		अगर (i == n_entries * 2 - 1) अणु
			drm_err(&dev_priv->drm, "FDI link training failed!\n");
			अवरोध;
		पूर्ण

		rx_ctl_val &= ~FDI_RX_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), rx_ctl_val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));

		temp = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_E));
		temp &= ~DDI_BUF_CTL_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(PORT_E), temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_E));

		/* Disable DP_TP_CTL and FDI_RX_CTL and retry */
		temp = पूर्णांकel_de_पढ़ो(dev_priv, DP_TP_CTL(PORT_E));
		temp &= ~(DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_MASK);
		temp |= DP_TP_CTL_LINK_TRAIN_PAT1;
		पूर्णांकel_de_ग_लिखो(dev_priv, DP_TP_CTL(PORT_E), temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DP_TP_CTL(PORT_E));

		पूर्णांकel_रुको_ddi_buf_idle(dev_priv, PORT_E);

		/* Reset FDI_RX_MISC pwrdn lanes */
		temp = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_MISC(PIPE_A));
		temp &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
		temp |= FDI_RX_PWRDN_LANE1_VAL(2) | FDI_RX_PWRDN_LANE0_VAL(2);
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(PIPE_A), temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, FDI_RX_MISC(PIPE_A));
	पूर्ण

	/* Enable normal pixel sending क्रम FDI */
	पूर्णांकel_de_ग_लिखो(dev_priv, DP_TP_CTL(PORT_E),
		       DP_TP_CTL_FDI_AUTOTRAIN |
		       DP_TP_CTL_LINK_TRAIN_NORMAL |
		       DP_TP_CTL_ENHANCED_FRAME_ENABLE |
		       DP_TP_CTL_ENABLE);
पूर्ण

व्योम ilk_fdi_pll_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_crtc->base.dev);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	i915_reg_t reg;
	u32 temp;

	/* enable PCH FDI RX PLL, रुको warmup plus DMI latency */
	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~(FDI_DP_PORT_WIDTH_MASK | (0x7 << 16));
	temp |= FDI_DP_PORT_WIDTH(crtc_state->fdi_lanes);
	temp |= (पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe)) & PIPECONF_BPC_MASK) << 11;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_RX_PLL_ENABLE);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(200);

	/* Switch from Rawclk to PCDclk */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_PCDCLK);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(200);

	/* Enable CPU FDI TX PLL, always on क्रम Ironlake */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर ((temp & FDI_TX_PLL_ENABLE) == 0) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp | FDI_TX_PLL_ENABLE);

		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(100);
	पूर्ण
पूर्ण

व्योम ilk_fdi_pll_disable(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	i915_reg_t reg;
	u32 temp;

	/* Switch from PCDclk to Rawclk */
	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp & ~FDI_PCDCLK);

	/* Disable CPU FDI TX PLL */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp & ~FDI_TX_PLL_ENABLE);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(100);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp & ~FDI_RX_PLL_ENABLE);

	/* Wait क्रम the घड़ीs to turn off. */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(100);
पूर्ण

व्योम ilk_fdi_disable(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 temp;

	/* disable CPU FDI tx and PCH FDI rx */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp & ~FDI_TX_ENABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~(0x7 << 16);
	temp |= (पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe)) & PIPECONF_BPC_MASK) << 11;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp & ~FDI_RX_ENABLE);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(100);

	/* Ironlake workaround, disable घड़ी poपूर्णांकer after करोwning FDI */
	अगर (HAS_PCH_IBX(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CHICKEN(pipe),
			       FDI_RX_PHASE_SYNC_POINTER_OVR);

	/* still set train pattern 1 */
	reg = FDI_TX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	temp &= ~FDI_LINK_TRAIN_NONE;
	temp |= FDI_LINK_TRAIN_PATTERN_1;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	reg = FDI_RX_CTL(pipe);
	temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (HAS_PCH_CPT(dev_priv)) अणु
		temp &= ~FDI_LINK_TRAIN_PATTERN_MASK_CPT;
		temp |= FDI_LINK_TRAIN_PATTERN_1_CPT;
	पूर्ण अन्यथा अणु
		temp &= ~FDI_LINK_TRAIN_NONE;
		temp |= FDI_LINK_TRAIN_PATTERN_1;
	पूर्ण
	/* BPC in FDI rx is consistent with that in PIPECONF */
	temp &= ~(0x07 << 16);
	temp |= (पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe)) & PIPECONF_BPC_MASK) << 11;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(100);
पूर्ण

व्योम
पूर्णांकel_fdi_init_hook(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_IRONLAKE(dev_priv)) अणु
		dev_priv->display.fdi_link_train = ilk_fdi_link_train;
	पूर्ण अन्यथा अगर (IS_SANDYBRIDGE(dev_priv)) अणु
		dev_priv->display.fdi_link_train = gen6_fdi_link_train;
	पूर्ण अन्यथा अगर (IS_IVYBRIDGE(dev_priv)) अणु
		/* FIXME: detect B0+ stepping and use स्वतः training */
		dev_priv->display.fdi_link_train = ivb_manual_fdi_link_train;
	पूर्ण
पूर्ण
