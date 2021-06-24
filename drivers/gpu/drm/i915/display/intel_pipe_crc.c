<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Author: Damien Lespiau <damien.lespiau@पूर्णांकel.com>
 *
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश "intel_atomic.h"
#समावेश "intel_display_types.h"
#समावेश "intel_pipe_crc.h"

अटल स्थिर अक्षर * स्थिर pipe_crc_sources[] = अणु
	[INTEL_PIPE_CRC_SOURCE_NONE] = "none",
	[INTEL_PIPE_CRC_SOURCE_PLANE1] = "plane1",
	[INTEL_PIPE_CRC_SOURCE_PLANE2] = "plane2",
	[INTEL_PIPE_CRC_SOURCE_PLANE3] = "plane3",
	[INTEL_PIPE_CRC_SOURCE_PLANE4] = "plane4",
	[INTEL_PIPE_CRC_SOURCE_PLANE5] = "plane5",
	[INTEL_PIPE_CRC_SOURCE_PLANE6] = "plane6",
	[INTEL_PIPE_CRC_SOURCE_PLANE7] = "plane7",
	[INTEL_PIPE_CRC_SOURCE_PIPE] = "pipe",
	[INTEL_PIPE_CRC_SOURCE_TV] = "TV",
	[INTEL_PIPE_CRC_SOURCE_DP_B] = "DP-B",
	[INTEL_PIPE_CRC_SOURCE_DP_C] = "DP-C",
	[INTEL_PIPE_CRC_SOURCE_DP_D] = "DP-D",
	[INTEL_PIPE_CRC_SOURCE_AUTO] = "auto",
पूर्ण;

अटल पूर्णांक i8xx_pipe_crc_ctl_reg(क्रमागत पूर्णांकel_pipe_crc_source *source,
				 u32 *val)
अणु
	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_INCLUDE_BORDER_I8XX;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i9xx_pipe_crc_स्वतः_source(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत pipe pipe,
				     क्रमागत पूर्णांकel_pipe_crc_source *source)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_digital_port *dig_port;
	पूर्णांक ret = 0;

	*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	drm_modeset_lock_all(dev);
	क्रम_each_पूर्णांकel_encoder(dev, encoder) अणु
		अगर (!encoder->base.crtc)
			जारी;

		crtc = to_पूर्णांकel_crtc(encoder->base.crtc);

		अगर (crtc->pipe != pipe)
			जारी;

		चयन (encoder->type) अणु
		हाल INTEL_OUTPUT_TVOUT:
			*source = INTEL_PIPE_CRC_SOURCE_TV;
			अवरोध;
		हाल INTEL_OUTPUT_DP:
		हाल INTEL_OUTPUT_EDP:
			dig_port = enc_to_dig_port(encoder);
			चयन (dig_port->base.port) अणु
			हाल PORT_B:
				*source = INTEL_PIPE_CRC_SOURCE_DP_B;
				अवरोध;
			हाल PORT_C:
				*source = INTEL_PIPE_CRC_SOURCE_DP_C;
				अवरोध;
			हाल PORT_D:
				*source = INTEL_PIPE_CRC_SOURCE_DP_D;
				अवरोध;
			शेष:
				drm_WARN(dev, 1, "nonexisting DP port %c\n",
					 port_name(dig_port->base.port));
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	drm_modeset_unlock_all(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vlv_pipe_crc_ctl_reg(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत pipe pipe,
				क्रमागत पूर्णांकel_pipe_crc_source *source,
				u32 *val)
अणु
	bool need_stable_symbols = false;

	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO) अणु
		पूर्णांक ret = i9xx_pipe_crc_स्वतः_source(dev_priv, pipe, source);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PIPE_VLV;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_DP_B:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_B_VLV;
		need_stable_symbols = true;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_DP_C:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_C_VLV;
		need_stable_symbols = true;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_DP_D:
		अगर (!IS_CHERRYVIEW(dev_priv))
			वापस -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DP_D_VLV;
		need_stable_symbols = true;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * When the pipe CRC tap poपूर्णांक is after the transcoders we need
	 * to tweak symbol-level features to produce a deterministic series of
	 * symbols क्रम a given frame. We need to reset those features only once
	 * a frame (instead of every nth symbol):
	 *   - DC-balance: used to ensure a better घड़ी recovery from the data
	 *     link (SDVO)
	 *   - DisplayPort scrambling: used क्रम EMI reduction
	 */
	अगर (need_stable_symbols) अणु
		u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PORT_DFT2_G4X);

		पंचांगp |= DC_BALANCE_RESET_VLV;
		चयन (pipe) अणु
		हाल PIPE_A:
			पंचांगp |= PIPE_A_SCRAMBLE_RESET;
			अवरोध;
		हाल PIPE_B:
			पंचांगp |= PIPE_B_SCRAMBLE_RESET;
			अवरोध;
		हाल PIPE_C:
			पंचांगp |= PIPE_C_SCRAMBLE_RESET;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, PORT_DFT2_G4X, पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i9xx_pipe_crc_ctl_reg(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत pipe pipe,
				 क्रमागत पूर्णांकel_pipe_crc_source *source,
				 u32 *val)
अणु
	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO) अणु
		पूर्णांक ret = i9xx_pipe_crc_स्वतः_source(dev_priv, pipe, source);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PIPE_I9XX;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_TV:
		अगर (!SUPPORTS_TV(dev_priv))
			वापस -EINVAL;
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_TV_PRE;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		/*
		 * The DP CRC source करोesn't work on g4x.
		 * It can be made to work to some degree by selecting
		 * the correct CRC source beक्रमe the port is enabled,
		 * and not touching the CRC source bits again until
		 * the port is disabled. But even then the bits
		 * eventually get stuck and a reboot is needed to get
		 * working CRCs on the pipe again. Let's simply
		 * refuse to use DP CRCs on g4x.
		 */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vlv_unकरो_pipe_scramble_reset(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pipe)
अणु
	u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PORT_DFT2_G4X);

	चयन (pipe) अणु
	हाल PIPE_A:
		पंचांगp &= ~PIPE_A_SCRAMBLE_RESET;
		अवरोध;
	हाल PIPE_B:
		पंचांगp &= ~PIPE_B_SCRAMBLE_RESET;
		अवरोध;
	हाल PIPE_C:
		पंचांगp &= ~PIPE_C_SCRAMBLE_RESET;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	अगर (!(पंचांगp & PIPE_SCRAMBLE_RESET_MASK))
		पंचांगp &= ~DC_BALANCE_RESET_VLV;
	पूर्णांकel_de_ग_लिखो(dev_priv, PORT_DFT2_G4X, पंचांगp);
पूर्ण

अटल पूर्णांक ilk_pipe_crc_ctl_reg(क्रमागत पूर्णांकel_pipe_crc_source *source,
				u32 *val)
अणु
	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PRIMARY_ILK;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_SPRITE_ILK;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PIPE_ILK;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_crtc_crc_setup_workarounds(काष्ठा पूर्णांकel_crtc *crtc, bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *pipe_config;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(&dev_priv->drm);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	state->acquire_ctx = &ctx;

retry:
	pipe_config = पूर्णांकel_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(pipe_config)) अणु
		ret = PTR_ERR(pipe_config);
		जाओ put_state;
	पूर्ण

	pipe_config->uapi.mode_changed = pipe_config->has_psr;
	pipe_config->crc_enabled = enable;

	अगर (IS_HASWELL(dev_priv) &&
	    pipe_config->hw.active && crtc->pipe == PIPE_A &&
	    pipe_config->cpu_transcoder == TRANSCODER_EDP)
		pipe_config->uapi.mode_changed = true;

	ret = drm_atomic_commit(state);

put_state:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);
unlock:
	drm_WARN(&dev_priv->drm, ret,
		 "Toggling workaround to %i returns %i\n", enable, ret);
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
पूर्ण

अटल पूर्णांक ivb_pipe_crc_ctl_reg(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत pipe pipe,
				क्रमागत पूर्णांकel_pipe_crc_source *source,
				u32 *val)
अणु
	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PRIMARY_IVB;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_SPRITE_IVB;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PF_IVB;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_pipe_crc_ctl_reg(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत pipe pipe,
				क्रमागत पूर्णांकel_pipe_crc_source *source,
				u32 *val)
अणु
	अगर (*source == INTEL_PIPE_CRC_SOURCE_AUTO)
		*source = INTEL_PIPE_CRC_SOURCE_PIPE;

	चयन (*source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_1_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_2_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE3:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_3_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE4:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_4_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE5:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_5_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE6:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_6_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PLANE7:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_PLANE_7_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
		*val = PIPE_CRC_ENABLE | PIPE_CRC_SOURCE_DMUX_SKL;
		अवरोध;
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		*val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_new_crc_ctl_reg(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत pipe pipe,
			       क्रमागत पूर्णांकel_pipe_crc_source *source, u32 *val)
अणु
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		वापस i8xx_pipe_crc_ctl_reg(source, val);
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 5)
		वापस i9xx_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		वापस vlv_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
	अन्यथा अगर (IS_IRONLAKE(dev_priv) || IS_SANDYBRIDGE(dev_priv))
		वापस ilk_pipe_crc_ctl_reg(source, val);
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 9)
		वापस ivb_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
	अन्यथा
		वापस skl_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
पूर्ण

अटल पूर्णांक
display_crc_ctl_parse_source(स्थिर अक्षर *buf, क्रमागत पूर्णांकel_pipe_crc_source *s)
अणु
	पूर्णांक i;

	अगर (!buf) अणु
		*s = INTEL_PIPE_CRC_SOURCE_NONE;
		वापस 0;
	पूर्ण

	i = match_string(pipe_crc_sources, ARRAY_SIZE(pipe_crc_sources), buf);
	अगर (i < 0)
		वापस i;

	*s = i;
	वापस 0;
पूर्ण

व्योम पूर्णांकel_crtc_crc_init(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_pipe_crc *pipe_crc = &crtc->pipe_crc;

	spin_lock_init(&pipe_crc->lock);
पूर्ण

अटल पूर्णांक i8xx_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				 स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक i9xx_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				 स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_TV:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vlv_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_DP_B:
	हाल INTEL_PIPE_CRC_SOURCE_DP_C:
	हाल INTEL_PIPE_CRC_SOURCE_DP_D:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ilk_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ivb_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_crc_source_valid(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	चयन (source) अणु
	हाल INTEL_PIPE_CRC_SOURCE_PIPE:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE1:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE2:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE3:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE4:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE5:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE6:
	हाल INTEL_PIPE_CRC_SOURCE_PLANE7:
	हाल INTEL_PIPE_CRC_SOURCE_NONE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
पूर्णांकel_is_valid_crc_source(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर क्रमागत पूर्णांकel_pipe_crc_source source)
अणु
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		वापस i8xx_crc_source_valid(dev_priv, source);
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 5)
		वापस i9xx_crc_source_valid(dev_priv, source);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		वापस vlv_crc_source_valid(dev_priv, source);
	अन्यथा अगर (IS_IRONLAKE(dev_priv) || IS_SANDYBRIDGE(dev_priv))
		वापस ilk_crc_source_valid(dev_priv, source);
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 9)
		वापस ivb_crc_source_valid(dev_priv, source);
	अन्यथा
		वापस skl_crc_source_valid(dev_priv, source);
पूर्ण

स्थिर अक्षर *स्थिर *पूर्णांकel_crtc_get_crc_sources(काष्ठा drm_crtc *crtc,
					      माप_प्रकार *count)
अणु
	*count = ARRAY_SIZE(pipe_crc_sources);
	वापस pipe_crc_sources;
पूर्ण

पूर्णांक पूर्णांकel_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name,
				 माप_प्रकार *values_cnt)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	क्रमागत पूर्णांकel_pipe_crc_source source;

	अगर (display_crc_ctl_parse_source(source_name, &source) < 0) अणु
		drm_dbg(&dev_priv->drm, "unknown source %s\n", source_name);
		वापस -EINVAL;
	पूर्ण

	अगर (source == INTEL_PIPE_CRC_SOURCE_AUTO ||
	    पूर्णांकel_is_valid_crc_source(dev_priv, source) == 0) अणु
		*values_cnt = 5;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक पूर्णांकel_crtc_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);
	काष्ठा पूर्णांकel_pipe_crc *pipe_crc = &पूर्णांकel_crtc->pipe_crc;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	क्रमागत पूर्णांकel_pipe_crc_source source;
	पूर्णांकel_wakeref_t wakeref;
	u32 val = 0; /* shut up gcc */
	पूर्णांक ret = 0;
	bool enable;

	अगर (display_crc_ctl_parse_source(source_name, &source) < 0) अणु
		drm_dbg(&dev_priv->drm, "unknown source %s\n", source_name);
		वापस -EINVAL;
	पूर्ण

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(crtc->index);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Trying to capture CRC while pipe is off\n");
		वापस -EIO;
	पूर्ण

	enable = source != INTEL_PIPE_CRC_SOURCE_NONE;
	अगर (enable)
		पूर्णांकel_crtc_crc_setup_workarounds(to_पूर्णांकel_crtc(crtc), true);

	ret = get_new_crc_ctl_reg(dev_priv, crtc->index, &source, &val);
	अगर (ret != 0)
		जाओ out;

	pipe_crc->source = source;
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CRC_CTL(crtc->index), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPE_CRC_CTL(crtc->index));

	अगर (!source) अणु
		अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
			vlv_unकरो_pipe_scramble_reset(dev_priv, crtc->index);
	पूर्ण

	pipe_crc->skipped = 0;

out:
	अगर (!enable)
		पूर्णांकel_crtc_crc_setup_workarounds(to_पूर्णांकel_crtc(crtc), false);

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_crtc_enable_pipe_crc(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc)
अणु
	काष्ठा drm_crtc *crtc = &पूर्णांकel_crtc->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_pipe_crc *pipe_crc = &पूर्णांकel_crtc->pipe_crc;
	u32 val = 0;

	अगर (!crtc->crc.खोलोed)
		वापस;

	अगर (get_new_crc_ctl_reg(dev_priv, crtc->index, &pipe_crc->source, &val) < 0)
		वापस;

	/* Don't need pipe_crc->lock here, IRQs are not generated. */
	pipe_crc->skipped = 0;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CRC_CTL(crtc->index), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPE_CRC_CTL(crtc->index));
पूर्ण

व्योम पूर्णांकel_crtc_disable_pipe_crc(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc)
अणु
	काष्ठा drm_crtc *crtc = &पूर्णांकel_crtc->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_pipe_crc *pipe_crc = &पूर्णांकel_crtc->pipe_crc;

	/* Swallow crc's until we stop generating them. */
	spin_lock_irq(&pipe_crc->lock);
	pipe_crc->skipped = पूर्णांक_न्यून;
	spin_unlock_irq(&pipe_crc->lock);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CRC_CTL(crtc->index), 0);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPE_CRC_CTL(crtc->index));
	पूर्णांकel_synchronize_irq(dev_priv);
पूर्ण
