<शैली गुरु>
/*
 * Copyright 2006 Dave Airlie <airlied@linux.ie>
 * Copyright तऊ 2006-2009 Intel Corporation
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
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_hdcp.h>
#समावेश <drm/drm_scdc_helper.h>
#समावेश <drm/पूर्णांकel_lpe_audपन.स>

#समावेश "i915_debugfs.h"
#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_connector.h"
#समावेश "intel_ddi.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_lspcon.h"
#समावेश "intel_panel.h"

अटल काष्ठा drm_device *पूर्णांकel_hdmi_to_dev(काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi)
अणु
	वापस hdmi_to_dig_port(पूर्णांकel_hdmi)->base.base.dev;
पूर्ण

अटल व्योम
निश्चित_hdmi_port_disabled(काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_hdmi_to_dev(पूर्णांकel_hdmi);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 enabled_bits;

	enabled_bits = HAS_DDI(dev_priv) ? DDI_BUF_CTL_ENABLE : SDVO_ENABLE;

	drm_WARN(dev,
		 पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg) & enabled_bits,
		 "HDMI port enabled, expecting disabled\n");
पूर्ण

अटल व्योम
निश्चित_hdmi_transcoder_func_disabled(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत transcoder cpu_transcoder)
अणु
	drm_WARN(&dev_priv->drm,
		 पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder)) &
		 TRANS_DDI_FUNC_ENABLE,
		 "HDMI transcoder function enabled, expecting disabled\n");
पूर्ण

अटल u32 g4x_infoframe_index(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		वापस VIDEO_DIP_SELECT_GAMUT;
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस VIDEO_DIP_SELECT_AVI;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस VIDEO_DIP_SELECT_SPD;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस VIDEO_DIP_SELECT_VENDOR;
	शेष:
		MISSING_CASE(type);
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 g4x_infoframe_enable(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल HDMI_PACKET_TYPE_GENERAL_CONTROL:
		वापस VIDEO_DIP_ENABLE_GCP;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		वापस VIDEO_DIP_ENABLE_GAMUT;
	हाल DP_SDP_VSC:
		वापस 0;
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस VIDEO_DIP_ENABLE_AVI;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस VIDEO_DIP_ENABLE_SPD;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस VIDEO_DIP_ENABLE_VENDOR;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		वापस 0;
	शेष:
		MISSING_CASE(type);
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 hsw_infoframe_enable(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल HDMI_PACKET_TYPE_GENERAL_CONTROL:
		वापस VIDEO_DIP_ENABLE_GCP_HSW;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		वापस VIDEO_DIP_ENABLE_GMP_HSW;
	हाल DP_SDP_VSC:
		वापस VIDEO_DIP_ENABLE_VSC_HSW;
	हाल DP_SDP_PPS:
		वापस VDIP_ENABLE_PPS;
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस VIDEO_DIP_ENABLE_AVI_HSW;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस VIDEO_DIP_ENABLE_SPD_HSW;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस VIDEO_DIP_ENABLE_VS_HSW;
	हाल HDMI_INFOFRAME_TYPE_DRM:
		वापस VIDEO_DIP_ENABLE_DRM_GLK;
	शेष:
		MISSING_CASE(type);
		वापस 0;
	पूर्ण
पूर्ण

अटल i915_reg_t
hsw_dip_data_reg(काष्ठा drm_i915_निजी *dev_priv,
		 क्रमागत transcoder cpu_transcoder,
		 अचिन्हित पूर्णांक type,
		 पूर्णांक i)
अणु
	चयन (type) अणु
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		वापस HSW_TVIDEO_DIP_GMP_DATA(cpu_transcoder, i);
	हाल DP_SDP_VSC:
		वापस HSW_TVIDEO_DIP_VSC_DATA(cpu_transcoder, i);
	हाल DP_SDP_PPS:
		वापस ICL_VIDEO_DIP_PPS_DATA(cpu_transcoder, i);
	हाल HDMI_INFOFRAME_TYPE_AVI:
		वापस HSW_TVIDEO_DIP_AVI_DATA(cpu_transcoder, i);
	हाल HDMI_INFOFRAME_TYPE_SPD:
		वापस HSW_TVIDEO_DIP_SPD_DATA(cpu_transcoder, i);
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		वापस HSW_TVIDEO_DIP_VS_DATA(cpu_transcoder, i);
	हाल HDMI_INFOFRAME_TYPE_DRM:
		वापस GLK_TVIDEO_DIP_DRM_DATA(cpu_transcoder, i);
	शेष:
		MISSING_CASE(type);
		वापस INVALID_MMIO_REG;
	पूर्ण
पूर्ण

अटल पूर्णांक hsw_dip_data_size(काष्ठा drm_i915_निजी *dev_priv,
			     अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल DP_SDP_VSC:
		वापस VIDEO_DIP_VSC_DATA_SIZE;
	हाल DP_SDP_PPS:
		वापस VIDEO_DIP_PPS_DATA_SIZE;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		अगर (DISPLAY_VER(dev_priv) >= 11)
			वापस VIDEO_DIP_GMP_DATA_SIZE;
		अन्यथा
			वापस VIDEO_DIP_DATA_SIZE;
	शेष:
		वापस VIDEO_DIP_DATA_SIZE;
	पूर्ण
पूर्ण

अटल व्योम g4x_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				अचिन्हित पूर्णांक type,
				स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	स्थिर u32 *data = frame;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, VIDEO_DIP_CTL);
	पूर्णांक i;

	drm_WARN(&dev_priv->drm, !(val & VIDEO_DIP_ENABLE),
		 "Writing DIP with CTL reg disabled\n");

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	val &= ~g4x_infoframe_enable(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, VIDEO_DIP_CTL, val);

	क्रम (i = 0; i < len; i += 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, VIDEO_DIP_DATA, *data);
		data++;
	पूर्ण
	/* Write every possible data byte to क्रमce correct ECC calculation. */
	क्रम (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv, VIDEO_DIP_DATA, 0);

	val |= g4x_infoframe_enable(type);
	val &= ~VIDEO_DIP_FREQ_MASK;
	val |= VIDEO_DIP_FREQ_VSYNC;

	पूर्णांकel_de_ग_लिखो(dev_priv, VIDEO_DIP_CTL, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, VIDEO_DIP_CTL);
पूर्ण

अटल व्योम g4x_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type,
			       व्योम *frame, sमाप_प्रकार len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val, *data = frame;
	पूर्णांक i;

	val = पूर्णांकel_de_पढ़ो(dev_priv, VIDEO_DIP_CTL);

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, VIDEO_DIP_CTL, val);

	क्रम (i = 0; i < len; i += 4)
		*data++ = पूर्णांकel_de_पढ़ो(dev_priv, VIDEO_DIP_DATA);
पूर्ण

अटल u32 g4x_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, VIDEO_DIP_CTL);

	अगर ((val & VIDEO_DIP_ENABLE) == 0)
		वापस 0;

	अगर ((val & VIDEO_DIP_PORT_MASK) != VIDEO_DIP_PORT(encoder->port))
		वापस 0;

	वापस val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_SPD);
पूर्ण

अटल व्योम ibx_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				अचिन्हित पूर्णांक type,
				स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	स्थिर u32 *data = frame;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	i915_reg_t reg = TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांक i;

	drm_WARN(&dev_priv->drm, !(val & VIDEO_DIP_ENABLE),
		 "Writing DIP with CTL reg disabled\n");

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	val &= ~g4x_infoframe_enable(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);

	क्रम (i = 0; i < len; i += 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe),
			       *data);
		data++;
	पूर्ण
	/* Write every possible data byte to क्रमce correct ECC calculation. */
	क्रम (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe), 0);

	val |= g4x_infoframe_enable(type);
	val &= ~VIDEO_DIP_FREQ_MASK;
	val |= VIDEO_DIP_FREQ_VSYNC;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
पूर्ण

अटल व्योम ibx_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type,
			       व्योम *frame, sमाप_प्रकार len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	u32 val, *data = frame;
	पूर्णांक i;

	val = पूर्णांकel_de_पढ़ो(dev_priv, TVIDEO_DIP_CTL(crtc->pipe));

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_CTL(crtc->pipe), val);

	क्रम (i = 0; i < len; i += 4)
		*data++ = पूर्णांकel_de_पढ़ो(dev_priv, TVIDEO_DIP_DATA(crtc->pipe));
पूर्ण

अटल u32 ibx_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(pipe_config->uapi.crtc)->pipe;
	i915_reg_t reg = TVIDEO_DIP_CTL(pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	अगर ((val & VIDEO_DIP_ENABLE) == 0)
		वापस 0;

	अगर ((val & VIDEO_DIP_PORT_MASK) != VIDEO_DIP_PORT(encoder->port))
		वापस 0;

	वापस val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		      VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
पूर्ण

अटल व्योम cpt_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				अचिन्हित पूर्णांक type,
				स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	स्थिर u32 *data = frame;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	i915_reg_t reg = TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांक i;

	drm_WARN(&dev_priv->drm, !(val & VIDEO_DIP_ENABLE),
		 "Writing DIP with CTL reg disabled\n");

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	/* The DIP control रेजिस्टर spec says that we need to update the AVI
	 * infoframe without clearing its enable bit */
	अगर (type != HDMI_INFOFRAME_TYPE_AVI)
		val &= ~g4x_infoframe_enable(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);

	क्रम (i = 0; i < len; i += 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe),
			       *data);
		data++;
	पूर्ण
	/* Write every possible data byte to क्रमce correct ECC calculation. */
	क्रम (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe), 0);

	val |= g4x_infoframe_enable(type);
	val &= ~VIDEO_DIP_FREQ_MASK;
	val |= VIDEO_DIP_FREQ_VSYNC;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
पूर्ण

अटल व्योम cpt_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type,
			       व्योम *frame, sमाप_प्रकार len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	u32 val, *data = frame;
	पूर्णांक i;

	val = पूर्णांकel_de_पढ़ो(dev_priv, TVIDEO_DIP_CTL(crtc->pipe));

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, TVIDEO_DIP_CTL(crtc->pipe), val);

	क्रम (i = 0; i < len; i += 4)
		*data++ = पूर्णांकel_de_पढ़ो(dev_priv, TVIDEO_DIP_DATA(crtc->pipe));
पूर्ण

अटल u32 cpt_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(pipe_config->uapi.crtc)->pipe;
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, TVIDEO_DIP_CTL(pipe));

	अगर ((val & VIDEO_DIP_ENABLE) == 0)
		वापस 0;

	वापस val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		      VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
पूर्ण

अटल व्योम vlv_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				अचिन्हित पूर्णांक type,
				स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	स्थिर u32 *data = frame;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	i915_reg_t reg = VLV_TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	पूर्णांक i;

	drm_WARN(&dev_priv->drm, !(val & VIDEO_DIP_ENABLE),
		 "Writing DIP with CTL reg disabled\n");

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	val &= ~g4x_infoframe_enable(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);

	क्रम (i = 0; i < len; i += 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       VLV_TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe), *data);
		data++;
	पूर्ण
	/* Write every possible data byte to क्रमce correct ECC calculation. */
	क्रम (; i < VIDEO_DIP_DATA_SIZE; i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       VLV_TVIDEO_DIP_DATA(पूर्णांकel_crtc->pipe), 0);

	val |= g4x_infoframe_enable(type);
	val &= ~VIDEO_DIP_FREQ_MASK;
	val |= VIDEO_DIP_FREQ_VSYNC;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
पूर्ण

अटल व्योम vlv_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       अचिन्हित पूर्णांक type,
			       व्योम *frame, sमाप_प्रकार len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	u32 val, *data = frame;
	पूर्णांक i;

	val = पूर्णांकel_de_पढ़ो(dev_priv, VLV_TVIDEO_DIP_CTL(crtc->pipe));

	val &= ~(VIDEO_DIP_SELECT_MASK | 0xf); /* clear DIP data offset */
	val |= g4x_infoframe_index(type);

	पूर्णांकel_de_ग_लिखो(dev_priv, VLV_TVIDEO_DIP_CTL(crtc->pipe), val);

	क्रम (i = 0; i < len; i += 4)
		*data++ = पूर्णांकel_de_पढ़ो(dev_priv,
				        VLV_TVIDEO_DIP_DATA(crtc->pipe));
पूर्ण

अटल u32 vlv_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(pipe_config->uapi.crtc)->pipe;
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, VLV_TVIDEO_DIP_CTL(pipe));

	अगर ((val & VIDEO_DIP_ENABLE) == 0)
		वापस 0;

	अगर ((val & VIDEO_DIP_PORT_MASK) != VIDEO_DIP_PORT(encoder->port))
		वापस 0;

	वापस val & (VIDEO_DIP_ENABLE_AVI |
		      VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		      VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
पूर्ण

व्योम hsw_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 अचिन्हित पूर्णांक type,
			 स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	स्थिर u32 *data = frame;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	i915_reg_t ctl_reg = HSW_TVIDEO_DIP_CTL(cpu_transcoder);
	पूर्णांक data_size;
	पूर्णांक i;
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, ctl_reg);

	data_size = hsw_dip_data_size(dev_priv, type);

	drm_WARN_ON(&dev_priv->drm, len > data_size);

	val &= ~hsw_infoframe_enable(type);
	पूर्णांकel_de_ग_लिखो(dev_priv, ctl_reg, val);

	क्रम (i = 0; i < len; i += 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       hsw_dip_data_reg(dev_priv, cpu_transcoder, type, i >> 2),
			       *data);
		data++;
	पूर्ण
	/* Write every possible data byte to क्रमce correct ECC calculation. */
	क्रम (; i < data_size; i += 4)
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       hsw_dip_data_reg(dev_priv, cpu_transcoder, type, i >> 2),
			       0);

	val |= hsw_infoframe_enable(type);
	पूर्णांकel_de_ग_लिखो(dev_priv, ctl_reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, ctl_reg);
पूर्ण

व्योम hsw_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			अचिन्हित पूर्णांक type, व्योम *frame, sमाप_प्रकार len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 val, *data = frame;
	पूर्णांक i;

	val = पूर्णांकel_de_पढ़ो(dev_priv, HSW_TVIDEO_DIP_CTL(cpu_transcoder));

	क्रम (i = 0; i < len; i += 4)
		*data++ = पूर्णांकel_de_पढ़ो(dev_priv,
				        hsw_dip_data_reg(dev_priv, cpu_transcoder, type, i >> 2));
पूर्ण

अटल u32 hsw_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv,
				HSW_TVIDEO_DIP_CTL(pipe_config->cpu_transcoder));
	u32 mask;

	mask = (VIDEO_DIP_ENABLE_VSC_HSW | VIDEO_DIP_ENABLE_AVI_HSW |
		VIDEO_DIP_ENABLE_GCP_HSW | VIDEO_DIP_ENABLE_VS_HSW |
		VIDEO_DIP_ENABLE_GMP_HSW | VIDEO_DIP_ENABLE_SPD_HSW);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		mask |= VIDEO_DIP_ENABLE_DRM_GLK;

	वापस val & mask;
पूर्ण

अटल स्थिर u8 infoframe_type_to_idx[] = अणु
	HDMI_PACKET_TYPE_GENERAL_CONTROL,
	HDMI_PACKET_TYPE_GAMUT_METADATA,
	DP_SDP_VSC,
	HDMI_INFOFRAME_TYPE_AVI,
	HDMI_INFOFRAME_TYPE_SPD,
	HDMI_INFOFRAME_TYPE_VENDOR,
	HDMI_INFOFRAME_TYPE_DRM,
पूर्ण;

u32 पूर्णांकel_hdmi_infoframe_enable(अचिन्हित पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(infoframe_type_to_idx); i++) अणु
		अगर (infoframe_type_to_idx[i] == type)
			वापस BIT(i);
	पूर्ण

	वापस 0;
पूर्ण

u32 पूर्णांकel_hdmi_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	u32 val, ret = 0;
	पूर्णांक i;

	val = dig_port->infoframes_enabled(encoder, crtc_state);

	/* map from hardware bits to dip idx */
	क्रम (i = 0; i < ARRAY_SIZE(infoframe_type_to_idx); i++) अणु
		अचिन्हित पूर्णांक type = infoframe_type_to_idx[i];

		अगर (HAS_DDI(dev_priv)) अणु
			अगर (val & hsw_infoframe_enable(type))
				ret |= BIT(i);
		पूर्ण अन्यथा अणु
			अगर (val & g4x_infoframe_enable(type))
				ret |= BIT(i);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The data we ग_लिखो to the DIP data buffer रेजिस्टरs is 1 byte bigger than the
 * HDMI infoframe size because of an ECC/reserved byte at position 3 (starting
 * at 0). It's also a byte used by DisplayPort so the same DIP रेजिस्टरs can be
 * used क्रम both technologies.
 *
 * DW0: Reserved/ECC/DP | HB2 | HB1 | HB0
 * DW1:       DB3       | DB2 | DB1 | DB0
 * DW2:       DB7       | DB6 | DB5 | DB4
 * DW3: ...
 *
 * (HB is Header Byte, DB is Data Byte)
 *
 * The hdmi pack() functions करोn't know about that hardware specअगरic hole so we
 * trick them by giving an offset पूर्णांकo the buffer and moving back the header
 * bytes by one.
 */
अटल व्योम पूर्णांकel_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  क्रमागत hdmi_infoframe_type type,
				  स्थिर जोड़ hdmi_infoframe *frame)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	u8 buffer[VIDEO_DIP_DATA_SIZE];
	sमाप_प्रकार len;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(type)) == 0)
		वापस;

	अगर (drm_WARN_ON(encoder->base.dev, frame->any.type != type))
		वापस;

	/* see comment above क्रम the reason क्रम this offset */
	len = hdmi_infoframe_pack_only(frame, buffer + 1, माप(buffer) - 1);
	अगर (drm_WARN_ON(encoder->base.dev, len < 0))
		वापस;

	/* Insert the 'hole' (see big comment above) at position 3 */
	स_हटाओ(&buffer[0], &buffer[1], 3);
	buffer[3] = 0;
	len++;

	dig_port->ग_लिखो_infoframe(encoder, crtc_state, type, buffer, len);
पूर्ण

व्योम पूर्णांकel_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  क्रमागत hdmi_infoframe_type type,
			  जोड़ hdmi_infoframe *frame)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	u8 buffer[VIDEO_DIP_DATA_SIZE];
	पूर्णांक ret;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(type)) == 0)
		वापस;

	dig_port->पढ़ो_infoframe(encoder, crtc_state,
				       type, buffer, माप(buffer));

	/* Fill the 'hole' (see big comment above) at position 3 */
	स_हटाओ(&buffer[1], &buffer[0], 3);

	/* see comment above क्रम the reason क्रम this offset */
	ret = hdmi_infoframe_unpack(frame, buffer + 1, माप(buffer) - 1);
	अगर (ret) अणु
		drm_dbg_kms(encoder->base.dev,
			    "Failed to unpack infoframe type 0x%02x\n", type);
		वापस;
	पूर्ण

	अगर (frame->any.type != type)
		drm_dbg_kms(encoder->base.dev,
			    "Found the wrong infoframe type 0x%x (expected 0x%02x)\n",
			    frame->any.type, type);
पूर्ण

अटल bool
पूर्णांकel_hdmi_compute_avi_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा hdmi_avi_infoframe *frame = &crtc_state->infoframes.avi.avi;
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	काष्ठा drm_connector *connector = conn_state->connector;
	पूर्णांक ret;

	अगर (!crtc_state->has_infoframe)
		वापस true;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI);

	ret = drm_hdmi_avi_infoframe_from_display_mode(frame, connector,
						       adjusted_mode);
	अगर (ret)
		वापस false;

	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
		frame->colorspace = HDMI_COLORSPACE_YUV420;
	अन्यथा अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444)
		frame->colorspace = HDMI_COLORSPACE_YUV444;
	अन्यथा
		frame->colorspace = HDMI_COLORSPACE_RGB;

	drm_hdmi_avi_infoframe_colorspace(frame, conn_state);

	/* nonsense combination */
	drm_WARN_ON(encoder->base.dev, crtc_state->limited_color_range &&
		    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB);

	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_RGB) अणु
		drm_hdmi_avi_infoframe_quant_range(frame, connector,
						   adjusted_mode,
						   crtc_state->limited_color_range ?
						   HDMI_QUANTIZATION_RANGE_LIMITED :
						   HDMI_QUANTIZATION_RANGE_FULL);
	पूर्ण अन्यथा अणु
		frame->quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;
		frame->ycc_quantization_range = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	पूर्ण

	drm_hdmi_avi_infoframe_content_type(frame, conn_state);

	/* TODO: handle pixel repetition क्रम YCBCR420 outमाला_दो */

	ret = hdmi_avi_infoframe_check(frame);
	अगर (drm_WARN_ON(encoder->base.dev, ret))
		वापस false;

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_hdmi_compute_spd_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा hdmi_spd_infoframe *frame = &crtc_state->infoframes.spd.spd;
	पूर्णांक ret;

	अगर (!crtc_state->has_infoframe)
		वापस true;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_SPD);

	ret = hdmi_spd_infoframe_init(frame, "Intel", "Integrated gfx");
	अगर (drm_WARN_ON(encoder->base.dev, ret))
		वापस false;

	frame->sdi = HDMI_SPD_SDI_PC;

	ret = hdmi_spd_infoframe_check(frame);
	अगर (drm_WARN_ON(encoder->base.dev, ret))
		वापस false;

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_hdmi_compute_hdmi_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा hdmi_venकरोr_infoframe *frame =
		&crtc_state->infoframes.hdmi.venकरोr.hdmi;
	स्थिर काष्ठा drm_display_info *info =
		&conn_state->connector->display_info;
	पूर्णांक ret;

	अगर (!crtc_state->has_infoframe || !info->has_hdmi_infoframe)
		वापस true;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_VENDOR);

	ret = drm_hdmi_venकरोr_infoframe_from_display_mode(frame,
							  conn_state->connector,
							  &crtc_state->hw.adjusted_mode);
	अगर (drm_WARN_ON(encoder->base.dev, ret))
		वापस false;

	ret = hdmi_venकरोr_infoframe_check(frame);
	अगर (drm_WARN_ON(encoder->base.dev, ret))
		वापस false;

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_hdmi_compute_drm_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा hdmi_drm_infoframe *frame = &crtc_state->infoframes.drm.drm;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	पूर्णांक ret;

	अगर (DISPLAY_VER(dev_priv) < 10)
		वापस true;

	अगर (!crtc_state->has_infoframe)
		वापस true;

	अगर (!conn_state->hdr_output_metadata)
		वापस true;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_DRM);

	ret = drm_hdmi_infoframe_set_hdr_metadata(frame, conn_state);
	अगर (ret < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "couldn't set HDR metadata in infoframe\n");
		वापस false;
	पूर्ण

	ret = hdmi_drm_infoframe_check(frame);
	अगर (drm_WARN_ON(&dev_priv->drm, ret))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम g4x_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = &dig_port->hdmi;
	i915_reg_t reg = VIDEO_DIP_CTL;
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	u32 port = VIDEO_DIP_PORT(encoder->port);

	निश्चित_hdmi_port_disabled(पूर्णांकel_hdmi);

	/* If the रेजिस्टरs were not initialized yet, they might be zeroes,
	 * which means we're selecting the AVI DIP and we're setting its
	 * frequency to once. This seems to really confuse the HW and make
	 * things stop working (the रेजिस्टर spec says the AVI always needs to
	 * be sent every VSync). So here we aव्योम writing to the रेजिस्टर more
	 * than we need and also explicitly select the AVI DIP and explicitly
	 * set its frequency to every VSync. Aव्योमing to ग_लिखो it twice seems to
	 * be enough to solve the problem, but being defensive shouldn't hurt us
	 * either. */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	अगर (!enable) अणु
		अगर (!(val & VIDEO_DIP_ENABLE))
			वापस;
		अगर (port != (val & VIDEO_DIP_PORT_MASK)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "video DIP still enabled on port %c\n",
				    (val & VIDEO_DIP_PORT_MASK) >> 29);
			वापस;
		पूर्ण
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_SPD);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	अगर (port != (val & VIDEO_DIP_PORT_MASK)) अणु
		अगर (val & VIDEO_DIP_ENABLE) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "video DIP already enabled on port %c\n",
				    (val & VIDEO_DIP_PORT_MASK) >> 29);
			वापस;
		पूर्ण
		val &= ~VIDEO_DIP_PORT_MASK;
		val |= port;
	पूर्ण

	val |= VIDEO_DIP_ENABLE;
	val &= ~(VIDEO_DIP_ENABLE_AVI |
		 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_SPD);

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
पूर्ण

/*
 * Determine अगर शेष_phase=1 can be indicated in the GCP infoframe.
 *
 * From HDMI specअगरication 1.4a:
 * - The first pixel of each Video Data Period shall always have a pixel packing phase of 0
 * - The first pixel following each Video Data Period shall have a pixel packing phase of 0
 * - The PP bits shall be स्थिरant क्रम all GCPs and will be equal to the last packing phase
 * - The first pixel following every transition of HSYNC or VSYNC shall have a pixel packing
 *   phase of 0
 */
अटल bool gcp_शेष_phase_possible(पूर्णांक pipe_bpp,
				       स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक pixels_per_group;

	चयन (pipe_bpp) अणु
	हाल 30:
		/* 4 pixels in 5 घड़ीs */
		pixels_per_group = 4;
		अवरोध;
	हाल 36:
		/* 2 pixels in 3 घड़ीs */
		pixels_per_group = 2;
		अवरोध;
	हाल 48:
		/* 1 pixel in 2 घड़ीs */
		pixels_per_group = 1;
		अवरोध;
	शेष:
		/* phase inक्रमmation not relevant क्रम 8bpc */
		वापस false;
	पूर्ण

	वापस mode->crtc_hdisplay % pixels_per_group == 0 &&
		mode->crtc_htotal % pixels_per_group == 0 &&
		mode->crtc_hblank_start % pixels_per_group == 0 &&
		mode->crtc_hblank_end % pixels_per_group == 0 &&
		mode->crtc_hsync_start % pixels_per_group == 0 &&
		mode->crtc_hsync_end % pixels_per_group == 0 &&
		((mode->flags & DRM_MODE_FLAG_INTERLACE) == 0 ||
		 mode->crtc_htotal/2 % pixels_per_group == 0);
पूर्ण

अटल bool पूर्णांकel_hdmi_set_gcp_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	i915_reg_t reg;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GENERAL_CONTROL)) == 0)
		वापस false;

	अगर (HAS_DDI(dev_priv))
		reg = HSW_TVIDEO_DIP_GCP(crtc_state->cpu_transcoder);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		reg = VLV_TVIDEO_DIP_GCP(crtc->pipe);
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		reg = TVIDEO_DIP_GCP(crtc->pipe);
	अन्यथा
		वापस false;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, crtc_state->infoframes.gcp);

	वापस true;
पूर्ण

व्योम पूर्णांकel_hdmi_पढ़ो_gcp_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				   काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	i915_reg_t reg;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GENERAL_CONTROL)) == 0)
		वापस;

	अगर (HAS_DDI(dev_priv))
		reg = HSW_TVIDEO_DIP_GCP(crtc_state->cpu_transcoder);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		reg = VLV_TVIDEO_DIP_GCP(crtc->pipe);
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		reg = TVIDEO_DIP_GCP(crtc->pipe);
	अन्यथा
		वापस;

	crtc_state->infoframes.gcp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
पूर्ण

अटल व्योम पूर्णांकel_hdmi_compute_gcp_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
					     काष्ठा पूर्णांकel_crtc_state *crtc_state,
					     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_G4X(dev_priv) || !crtc_state->has_infoframe)
		वापस;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GENERAL_CONTROL);

	/* Indicate color indication क्रम deep color mode */
	अगर (crtc_state->pipe_bpp > 24)
		crtc_state->infoframes.gcp |= GCP_COLOR_INDICATION;

	/* Enable शेष_phase whenever the display mode is suitably aligned */
	अगर (gcp_शेष_phase_possible(crtc_state->pipe_bpp,
				       &crtc_state->hw.adjusted_mode))
		crtc_state->infoframes.gcp |= GCP_DEFAULT_PHASE_ENABLE;
पूर्ण

अटल व्योम ibx_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = &dig_port->hdmi;
	i915_reg_t reg = TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	u32 port = VIDEO_DIP_PORT(encoder->port);

	निश्चित_hdmi_port_disabled(पूर्णांकel_hdmi);

	/* See the big comment in g4x_set_infoframes() */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	अगर (!enable) अणु
		अगर (!(val & VIDEO_DIP_ENABLE))
			वापस;
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
			 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	अगर (port != (val & VIDEO_DIP_PORT_MASK)) अणु
		drm_WARN(&dev_priv->drm, val & VIDEO_DIP_ENABLE,
			 "DIP already enabled on port %c\n",
			 (val & VIDEO_DIP_PORT_MASK) >> 29);
		val &= ~VIDEO_DIP_PORT_MASK;
		val |= port;
	पूर्ण

	val |= VIDEO_DIP_ENABLE;
	val &= ~(VIDEO_DIP_ENABLE_AVI |
		 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);

	अगर (पूर्णांकel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
पूर्ण

अटल व्योम cpt_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	i915_reg_t reg = TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	निश्चित_hdmi_port_disabled(पूर्णांकel_hdmi);

	/* See the big comment in g4x_set_infoframes() */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	अगर (!enable) अणु
		अगर (!(val & VIDEO_DIP_ENABLE))
			वापस;
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
			 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	/* Set both together, unset both together: see the spec. */
	val |= VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI;
	val &= ~(VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);

	अगर (पूर्णांकel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
पूर्ण

अटल व्योम vlv_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	i915_reg_t reg = VLV_TVIDEO_DIP_CTL(पूर्णांकel_crtc->pipe);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	u32 port = VIDEO_DIP_PORT(encoder->port);

	निश्चित_hdmi_port_disabled(पूर्णांकel_hdmi);

	/* See the big comment in g4x_set_infoframes() */
	val |= VIDEO_DIP_SELECT_AVI | VIDEO_DIP_FREQ_VSYNC;

	अगर (!enable) अणु
		अगर (!(val & VIDEO_DIP_ENABLE))
			वापस;
		val &= ~(VIDEO_DIP_ENABLE | VIDEO_DIP_ENABLE_AVI |
			 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
			 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	अगर (port != (val & VIDEO_DIP_PORT_MASK)) अणु
		drm_WARN(&dev_priv->drm, val & VIDEO_DIP_ENABLE,
			 "DIP already enabled on port %c\n",
			 (val & VIDEO_DIP_PORT_MASK) >> 29);
		val &= ~VIDEO_DIP_PORT_MASK;
		val |= port;
	पूर्ण

	val |= VIDEO_DIP_ENABLE;
	val &= ~(VIDEO_DIP_ENABLE_AVI |
		 VIDEO_DIP_ENABLE_VENDOR | VIDEO_DIP_ENABLE_GAMUT |
		 VIDEO_DIP_ENABLE_SPD | VIDEO_DIP_ENABLE_GCP);

	अगर (पूर्णांकel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
पूर्ण

अटल व्योम hsw_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			       bool enable,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	i915_reg_t reg = HSW_TVIDEO_DIP_CTL(crtc_state->cpu_transcoder);
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	निश्चित_hdmi_transcoder_func_disabled(dev_priv,
					     crtc_state->cpu_transcoder);

	val &= ~(VIDEO_DIP_ENABLE_VSC_HSW | VIDEO_DIP_ENABLE_AVI_HSW |
		 VIDEO_DIP_ENABLE_GCP_HSW | VIDEO_DIP_ENABLE_VS_HSW |
		 VIDEO_DIP_ENABLE_GMP_HSW | VIDEO_DIP_ENABLE_SPD_HSW |
		 VIDEO_DIP_ENABLE_DRM_GLK);

	अगर (!enable) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		वापस;
	पूर्ण

	अगर (पूर्णांकel_hdmi_set_gcp_infoframe(encoder, crtc_state, conn_state))
		val |= VIDEO_DIP_ENABLE_GCP_HSW;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_AVI,
			      &crtc_state->infoframes.avi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_SPD,
			      &crtc_state->infoframes.spd);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_VENDOR,
			      &crtc_state->infoframes.hdmi);
	पूर्णांकel_ग_लिखो_infoframe(encoder, crtc_state,
			      HDMI_INFOFRAME_TYPE_DRM,
			      &crtc_state->infoframes.drm);
पूर्ण

व्योम पूर्णांकel_dp_dual_mode_set_पंचांगds_output(काष्ठा पूर्णांकel_hdmi *hdmi, bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_hdmi_to_dev(hdmi));
	काष्ठा i2c_adapter *adapter =
		पूर्णांकel_gmbus_get_adapter(dev_priv, hdmi->ddc_bus);

	अगर (hdmi->dp_dual_mode.type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		वापस;

	drm_dbg_kms(&dev_priv->drm, "%s DP dual mode adaptor TMDS output\n",
		    enable ? "Enabling" : "Disabling");

	drm_dp_dual_mode_set_पंचांगds_output(hdmi->dp_dual_mode.type,
					 adapter, enable);
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो(काष्ठा पूर्णांकel_digital_port *dig_port,
				अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = &dig_port->hdmi;
	काष्ठा i2c_adapter *adapter = पूर्णांकel_gmbus_get_adapter(i915,
							      hdmi->ddc_bus);
	पूर्णांक ret;
	u8 start = offset & 0xff;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = DRM_HDCP_DDC_ADDR,
			.flags = 0,
			.len = 1,
			.buf = &start,
		पूर्ण,
		अणु
			.addr = DRM_HDCP_DDC_ADDR,
			.flags = I2C_M_RD,
			.len = size,
			.buf = buffer
		पूर्ण
	पूर्ण;
	ret = i2c_transfer(adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret == ARRAY_SIZE(msgs))
		वापस 0;
	वापस ret >= 0 ? -EIO : ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_hdcp_ग_लिखो(काष्ठा पूर्णांकel_digital_port *dig_port,
				 अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = &dig_port->hdmi;
	काष्ठा i2c_adapter *adapter = पूर्णांकel_gmbus_get_adapter(i915,
							      hdmi->ddc_bus);
	पूर्णांक ret;
	u8 *ग_लिखो_buf;
	काष्ठा i2c_msg msg;

	ग_लिखो_buf = kzalloc(size + 1, GFP_KERNEL);
	अगर (!ग_लिखो_buf)
		वापस -ENOMEM;

	ग_लिखो_buf[0] = offset & 0xff;
	स_नकल(&ग_लिखो_buf[1], buffer, size);

	msg.addr = DRM_HDCP_DDC_ADDR;
	msg.flags = 0,
	msg.len = size + 1,
	msg.buf = ग_लिखो_buf;

	ret = i2c_transfer(adapter, &msg, 1);
	अगर (ret == 1)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	kमुक्त(ग_लिखो_buf);
	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_ग_लिखो_an_aksv(काष्ठा पूर्णांकel_digital_port *dig_port,
				  u8 *an)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = &dig_port->hdmi;
	काष्ठा i2c_adapter *adapter = पूर्णांकel_gmbus_get_adapter(i915,
							      hdmi->ddc_bus);
	पूर्णांक ret;

	ret = पूर्णांकel_hdmi_hdcp_ग_लिखो(dig_port, DRM_HDCP_DDC_AN, an,
				    DRM_HDCP_AN_LEN);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "Write An over DDC failed (%d)\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_gmbus_output_aksv(adapter);
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm, "Failed to output aksv (%d)\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_bksv(काष्ठा पूर्णांकel_digital_port *dig_port,
				     u8 *bksv)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	पूर्णांक ret;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_BKSV, bksv,
				   DRM_HDCP_KSV_LEN);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Read Bksv over DDC failed (%d)\n",
			    ret);
	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_bstatus(काष्ठा पूर्णांकel_digital_port *dig_port,
				 u8 *bstatus)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	पूर्णांक ret;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_BSTATUS,
				   bstatus, DRM_HDCP_BSTATUS_LEN);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Read bstatus over DDC failed (%d)\n",
			    ret);
	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_repeater_present(काष्ठा पूर्णांकel_digital_port *dig_port,
				     bool *repeater_present)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret;
	u8 val;

	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_BCAPS, &val, 1);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "Read bcaps over DDC failed (%d)\n",
			    ret);
		वापस ret;
	पूर्ण
	*repeater_present = val & DRM_HDCP_DDC_BCAPS_REPEATER_PRESENT;
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_ri_prime(काष्ठा पूर्णांकel_digital_port *dig_port,
				  u8 *ri_prime)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	पूर्णांक ret;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_RI_PRIME,
				   ri_prime, DRM_HDCP_RI_LEN);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Read Ri' over DDC failed (%d)\n",
			    ret);
	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_ksv_पढ़ोy(काष्ठा पूर्णांकel_digital_port *dig_port,
				   bool *ksv_पढ़ोy)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret;
	u8 val;

	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_BCAPS, &val, 1);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "Read bcaps over DDC failed (%d)\n",
			    ret);
		वापस ret;
	पूर्ण
	*ksv_पढ़ोy = val & DRM_HDCP_DDC_BCAPS_KSV_FIFO_READY;
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_ksv_fअगरo(काष्ठा पूर्णांकel_digital_port *dig_port,
				  पूर्णांक num_करोwnstream, u8 *ksv_fअगरo)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_KSV_FIFO,
				   ksv_fअगरo, num_करोwnstream * DRM_HDCP_KSV_LEN);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm,
			    "Read ksv fifo over DDC failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_पढ़ो_v_prime_part(काष्ठा पूर्णांकel_digital_port *dig_port,
				      पूर्णांक i, u32 *part)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret;

	अगर (i >= DRM_HDCP_V_PRIME_NUM_PARTS)
		वापस -EINVAL;

	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, DRM_HDCP_DDC_V_PRIME(i),
				   part, DRM_HDCP_V_PRIME_PART_LEN);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Read V'[%d] over DDC failed (%d)\n",
			    i, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक kbl_repositioning_enc_en_संकेत(काष्ठा पूर्णांकel_connector *connector,
					   क्रमागत transcoder cpu_transcoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_crtc *crtc = connector->base.state->crtc;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = container_of(crtc,
						     काष्ठा पूर्णांकel_crtc, base);
	u32 scanline;
	पूर्णांक ret;

	क्रम (;;) अणु
		scanline = पूर्णांकel_de_पढ़ो(dev_priv, PIPEDSL(पूर्णांकel_crtc->pipe));
		अगर (scanline > 100 && scanline < 200)
			अवरोध;
		usleep_range(25, 50);
	पूर्ण

	ret = पूर्णांकel_ddi_toggle_hdcp_bits(&dig_port->base, cpu_transcoder,
					 false, TRANS_DDI_HDCP_SIGNALLING);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Disable HDCP signalling failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_ddi_toggle_hdcp_bits(&dig_port->base, cpu_transcoder,
					 true, TRANS_DDI_HDCP_SIGNALLING);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Enable HDCP signalling failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp_toggle_संकेतling(काष्ठा पूर्णांकel_digital_port *dig_port,
				      क्रमागत transcoder cpu_transcoder,
				      bool enable)
अणु
	काष्ठा पूर्णांकel_hdmi *hdmi = &dig_port->hdmi;
	काष्ठा पूर्णांकel_connector *connector = hdmi->attached_connector;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	पूर्णांक ret;

	अगर (!enable)
		usleep_range(6, 60); /* Bspec says >= 6us */

	ret = पूर्णांकel_ddi_toggle_hdcp_bits(&dig_port->base,
					 cpu_transcoder, enable,
					 TRANS_DDI_HDCP_SIGNALLING);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "%s HDCP signalling failed (%d)\n",
			enable ? "Enable" : "Disable", ret);
		वापस ret;
	पूर्ण

	/*
	 * WA: To fix incorrect positioning of the winकरोw of
	 * opportunity and enc_en संकेतling in KABYLAKE.
	 */
	अगर (IS_KABYLAKE(dev_priv) && enable)
		वापस kbl_repositioning_enc_en_संकेत(connector,
						       cpu_transcoder);

	वापस 0;
पूर्ण

अटल
bool पूर्णांकel_hdmi_hdcp_check_link_once(काष्ठा पूर्णांकel_digital_port *dig_port,
				     काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder = connector->hdcp.cpu_transcoder;
	पूर्णांक ret;
	जोड़ अणु
		u32 reg;
		u8 shim[DRM_HDCP_RI_LEN];
	पूर्ण ri;

	ret = पूर्णांकel_hdmi_hdcp_पढ़ो_ri_prime(dig_port, ri.shim);
	अगर (ret)
		वापस false;

	पूर्णांकel_de_ग_लिखो(i915, HDCP_RPRIME(i915, cpu_transcoder, port), ri.reg);

	/* Wait क्रम Ri prime match */
	अगर (रुको_क्रम((पूर्णांकel_de_पढ़ो(i915, HDCP_STATUS(i915, cpu_transcoder, port)) &
		      (HDCP_STATUS_RI_MATCH | HDCP_STATUS_ENC)) ==
		     (HDCP_STATUS_RI_MATCH | HDCP_STATUS_ENC), 1)) अणु
		drm_dbg_kms(&i915->drm, "Ri' mismatch detected (%x)\n",
			पूर्णांकel_de_पढ़ो(i915, HDCP_STATUS(i915, cpu_transcoder,
							port)));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल
bool पूर्णांकel_hdmi_hdcp_check_link(काष्ठा पूर्णांकel_digital_port *dig_port,
				काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक retry;

	क्रम (retry = 0; retry < 3; retry++)
		अगर (पूर्णांकel_hdmi_hdcp_check_link_once(dig_port, connector))
			वापस true;

	drm_err(&i915->drm, "Link check failed\n");
	वापस false;
पूर्ण

काष्ठा hdcp2_hdmi_msg_समयout अणु
	u8 msg_id;
	u16 समयout;
पूर्ण;

अटल स्थिर काष्ठा hdcp2_hdmi_msg_समयout hdcp2_msg_समयout[] = अणु
	अणु HDCP_2_2_AKE_SEND_CERT, HDCP_2_2_CERT_TIMEOUT_MS, पूर्ण,
	अणु HDCP_2_2_AKE_SEND_PAIRING_INFO, HDCP_2_2_PAIRING_TIMEOUT_MS, पूर्ण,
	अणु HDCP_2_2_LC_SEND_LPRIME, HDCP_2_2_HDMI_LPRIME_TIMEOUT_MS, पूर्ण,
	अणु HDCP_2_2_REP_SEND_RECVID_LIST, HDCP_2_2_RECVID_LIST_TIMEOUT_MS, पूर्ण,
	अणु HDCP_2_2_REP_STREAM_READY, HDCP_2_2_STREAM_READY_TIMEOUT_MS, पूर्ण,
पूर्ण;

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp2_पढ़ो_rx_status(काष्ठा पूर्णांकel_digital_port *dig_port,
				    u8 *rx_status)
अणु
	वापस पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port,
				    HDCP_2_2_HDMI_REG_RXSTATUS_OFFSET,
				    rx_status,
				    HDCP_2_2_HDMI_RXSTATUS_LEN);
पूर्ण

अटल पूर्णांक get_hdcp2_msg_समयout(u8 msg_id, bool is_paired)
अणु
	पूर्णांक i;

	अगर (msg_id == HDCP_2_2_AKE_SEND_HPRIME) अणु
		अगर (is_paired)
			वापस HDCP_2_2_HPRIME_PAIRED_TIMEOUT_MS;
		अन्यथा
			वापस HDCP_2_2_HPRIME_NO_PAIRED_TIMEOUT_MS;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(hdcp2_msg_समयout); i++) अणु
		अगर (hdcp2_msg_समयout[i].msg_id == msg_id)
			वापस hdcp2_msg_समयout[i].समयout;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
hdcp2_detect_msg_availability(काष्ठा पूर्णांकel_digital_port *dig_port,
			      u8 msg_id, bool *msg_पढ़ोy,
			      sमाप_प्रकार *msg_sz)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	u8 rx_status[HDCP_2_2_HDMI_RXSTATUS_LEN];
	पूर्णांक ret;

	ret = पूर्णांकel_hdmi_hdcp2_पढ़ो_rx_status(dig_port, rx_status);
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm, "rx_status read failed. Err %d\n",
			    ret);
		वापस ret;
	पूर्ण

	*msg_sz = ((HDCP_2_2_HDMI_RXSTATUS_MSG_SZ_HI(rx_status[1]) << 8) |
		  rx_status[0]);

	अगर (msg_id == HDCP_2_2_REP_SEND_RECVID_LIST)
		*msg_पढ़ोy = (HDCP_2_2_HDMI_RXSTATUS_READY(rx_status[1]) &&
			     *msg_sz);
	अन्यथा
		*msg_पढ़ोy = *msg_sz;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकel_hdmi_hdcp2_रुको_क्रम_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			      u8 msg_id, bool paired)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	bool msg_पढ़ोy = false;
	पूर्णांक समयout, ret;
	sमाप_प्रकार msg_sz = 0;

	समयout = get_hdcp2_msg_समयout(msg_id, paired);
	अगर (समयout < 0)
		वापस समयout;

	ret = __रुको_क्रम(ret = hdcp2_detect_msg_availability(dig_port,
							     msg_id, &msg_पढ़ोy,
							     &msg_sz),
			 !ret && msg_पढ़ोy && msg_sz, समयout * 1000,
			 1000, 5 * 1000);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "msg_id: %d, ret: %d, timeout: %d\n",
			    msg_id, ret, समयout);

	वापस ret ? ret : msg_sz;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp2_ग_लिखो_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			       व्योम *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक offset;

	offset = HDCP_2_2_HDMI_REG_WR_MSG_OFFSET;
	वापस पूर्णांकel_hdmi_hdcp_ग_लिखो(dig_port, offset, buf, size);
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp2_पढ़ो_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			      u8 msg_id, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = &dig_port->hdmi;
	काष्ठा पूर्णांकel_hdcp *hdcp = &hdmi->attached_connector->hdcp;
	अचिन्हित पूर्णांक offset;
	sमाप_प्रकार ret;

	ret = पूर्णांकel_hdmi_hdcp2_रुको_क्रम_msg(dig_port, msg_id,
					    hdcp->is_paired);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Available msg size should be equal to or lesser than the
	 * available buffer.
	 */
	अगर (ret > size) अणु
		drm_dbg_kms(&i915->drm,
			    "msg_sz(%zd) is more than exp size(%zu)\n",
			    ret, size);
		वापस -1;
	पूर्ण

	offset = HDCP_2_2_HDMI_REG_RD_MSG_OFFSET;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, offset, buf, ret);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Failed to read msg_id: %d(%zd)\n",
			    msg_id, ret);

	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp2_check_link(काष्ठा पूर्णांकel_digital_port *dig_port,
				काष्ठा पूर्णांकel_connector *connector)
अणु
	u8 rx_status[HDCP_2_2_HDMI_RXSTATUS_LEN];
	पूर्णांक ret;

	ret = पूर्णांकel_hdmi_hdcp2_पढ़ो_rx_status(dig_port, rx_status);
	अगर (ret)
		वापस ret;

	/*
	 * Re-auth request and Link Integrity Failures are represented by
	 * same bit. i.e reauth_req.
	 */
	अगर (HDCP_2_2_HDMI_RXSTATUS_REAUTH_REQ(rx_status[1]))
		ret = HDCP_REAUTH_REQUEST;
	अन्यथा अगर (HDCP_2_2_HDMI_RXSTATUS_READY(rx_status[1]))
		ret = HDCP_TOPOLOGY_CHANGE;

	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdmi_hdcp2_capable(काष्ठा पूर्णांकel_digital_port *dig_port,
			     bool *capable)
अणु
	u8 hdcp2_version;
	पूर्णांक ret;

	*capable = false;
	ret = पूर्णांकel_hdmi_hdcp_पढ़ो(dig_port, HDCP_2_2_HDMI_REG_VER_OFFSET,
				   &hdcp2_version, माप(hdcp2_version));
	अगर (!ret && hdcp2_version & HDCP_2_2_HDMI_SUPPORT_MASK)
		*capable = true;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_hdcp_shim पूर्णांकel_hdmi_hdcp_shim = अणु
	.ग_लिखो_an_aksv = पूर्णांकel_hdmi_hdcp_ग_लिखो_an_aksv,
	.पढ़ो_bksv = पूर्णांकel_hdmi_hdcp_पढ़ो_bksv,
	.पढ़ो_bstatus = पूर्णांकel_hdmi_hdcp_पढ़ो_bstatus,
	.repeater_present = पूर्णांकel_hdmi_hdcp_repeater_present,
	.पढ़ो_ri_prime = पूर्णांकel_hdmi_hdcp_पढ़ो_ri_prime,
	.पढ़ो_ksv_पढ़ोy = पूर्णांकel_hdmi_hdcp_पढ़ो_ksv_पढ़ोy,
	.पढ़ो_ksv_fअगरo = पूर्णांकel_hdmi_hdcp_पढ़ो_ksv_fअगरo,
	.पढ़ो_v_prime_part = पूर्णांकel_hdmi_hdcp_पढ़ो_v_prime_part,
	.toggle_संकेतling = पूर्णांकel_hdmi_hdcp_toggle_संकेतling,
	.check_link = पूर्णांकel_hdmi_hdcp_check_link,
	.ग_लिखो_2_2_msg = पूर्णांकel_hdmi_hdcp2_ग_लिखो_msg,
	.पढ़ो_2_2_msg = पूर्णांकel_hdmi_hdcp2_पढ़ो_msg,
	.check_2_2_link	= पूर्णांकel_hdmi_hdcp2_check_link,
	.hdcp_2_2_capable = पूर्णांकel_hdmi_hdcp2_capable,
	.protocol = HDCP_PROTOCOL_HDMI,
पूर्ण;

अटल पूर्णांक पूर्णांकel_hdmi_source_max_पंचांगds_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	पूर्णांक max_पंचांगds_घड़ी, vbt_max_पंचांगds_घड़ी;

	अगर (DISPLAY_VER(dev_priv) >= 10)
		max_पंचांगds_घड़ी = 594000;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8 || IS_HASWELL(dev_priv))
		max_पंचांगds_घड़ी = 300000;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5)
		max_पंचांगds_घड़ी = 225000;
	अन्यथा
		max_पंचांगds_घड़ी = 165000;

	vbt_max_पंचांगds_घड़ी = पूर्णांकel_bios_max_पंचांगds_घड़ी(encoder);
	अगर (vbt_max_पंचांगds_घड़ी)
		max_पंचांगds_घड़ी = min(max_पंचांगds_घड़ी, vbt_max_पंचांगds_घड़ी);

	वापस max_पंचांगds_घड़ी;
पूर्ण

अटल bool पूर्णांकel_has_hdmi_sink(काष्ठा पूर्णांकel_hdmi *hdmi,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	वापस hdmi->has_hdmi_sink &&
		READ_ONCE(to_पूर्णांकel_digital_connector_state(conn_state)->क्रमce_audio) != HDMI_AUDIO_OFF_DVI;
पूर्ण

अटल पूर्णांक hdmi_port_घड़ी_limit(काष्ठा पूर्णांकel_hdmi *hdmi,
				 bool respect_करोwnstream_limits,
				 bool has_hdmi_sink)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &hdmi_to_dig_port(hdmi)->base;
	पूर्णांक max_पंचांगds_घड़ी = पूर्णांकel_hdmi_source_max_पंचांगds_घड़ी(encoder);

	अगर (respect_करोwnstream_limits) अणु
		काष्ठा पूर्णांकel_connector *connector = hdmi->attached_connector;
		स्थिर काष्ठा drm_display_info *info = &connector->base.display_info;

		अगर (hdmi->dp_dual_mode.max_पंचांगds_घड़ी)
			max_पंचांगds_घड़ी = min(max_पंचांगds_घड़ी,
					     hdmi->dp_dual_mode.max_पंचांगds_घड़ी);

		अगर (info->max_पंचांगds_घड़ी)
			max_पंचांगds_घड़ी = min(max_पंचांगds_घड़ी,
					     info->max_पंचांगds_घड़ी);
		अन्यथा अगर (!has_hdmi_sink)
			max_पंचांगds_घड़ी = min(max_पंचांगds_घड़ी, 165000);
	पूर्ण

	वापस max_पंचांगds_घड़ी;
पूर्ण

अटल क्रमागत drm_mode_status
hdmi_port_घड़ी_valid(काष्ठा पूर्णांकel_hdmi *hdmi,
		      पूर्णांक घड़ी, bool respect_करोwnstream_limits,
		      bool has_hdmi_sink)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_hdmi_to_dev(hdmi));

	अगर (घड़ी < 25000)
		वापस MODE_CLOCK_LOW;
	अगर (घड़ी > hdmi_port_घड़ी_limit(hdmi, respect_करोwnstream_limits,
					  has_hdmi_sink))
		वापस MODE_CLOCK_HIGH;

	/* GLK DPLL can't generate 446-480 MHz */
	अगर (IS_GEMINILAKE(dev_priv) && घड़ी > 446666 && घड़ी < 480000)
		वापस MODE_CLOCK_RANGE;

	/* BXT/GLK DPLL can't generate 223-240 MHz */
	अगर (IS_GEN9_LP(dev_priv) && घड़ी > 223333 && घड़ी < 240000)
		वापस MODE_CLOCK_RANGE;

	/* CHV DPLL can't generate 216-240 MHz */
	अगर (IS_CHERRYVIEW(dev_priv) && घड़ी > 216000 && घड़ी < 240000)
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_port_घड़ी(पूर्णांक घड़ी, पूर्णांक bpc)
अणु
	/*
	 * Need to adjust the port link by:
	 *  1.5x क्रम 12bpc
	 *  1.25x क्रम 10bpc
	 */
	वापस घड़ी * bpc / 8;
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_hdmi_mode_valid(काष्ठा drm_connector *connector,
		      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_hdmi *hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));
	काष्ठा drm_device *dev = पूर्णांकel_hdmi_to_dev(hdmi);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत drm_mode_status status;
	पूर्णांक घड़ी = mode->घड़ी;
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;
	bool has_hdmi_sink = पूर्णांकel_has_hdmi_sink(hdmi, connector->state);

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर ((mode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		घड़ी *= 2;

	अगर (घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK) अणु
		अगर (!has_hdmi_sink)
			वापस MODE_CLOCK_LOW;
		घड़ी *= 2;
	पूर्ण

	अगर (drm_mode_is_420_only(&connector->display_info, mode))
		घड़ी /= 2;

	/* check अगर we can करो 8bpc */
	status = hdmi_port_घड़ी_valid(hdmi, पूर्णांकel_hdmi_port_घड़ी(घड़ी, 8),
				       true, has_hdmi_sink);

	अगर (has_hdmi_sink) अणु
		/* अगर we can't करो 8bpc we may still be able to करो 12bpc */
		अगर (status != MODE_OK && !HAS_GMCH(dev_priv))
			status = hdmi_port_घड़ी_valid(hdmi, पूर्णांकel_hdmi_port_घड़ी(घड़ी, 12),
						       true, has_hdmi_sink);

		/* अगर we can't करो 8,12bpc we may still be able to करो 10bpc */
		अगर (status != MODE_OK && DISPLAY_VER(dev_priv) >= 11)
			status = hdmi_port_घड़ी_valid(hdmi, पूर्णांकel_hdmi_port_घड़ी(घड़ी, 10),
						       true, has_hdmi_sink);
	पूर्ण
	अगर (status != MODE_OK)
		वापस status;

	वापस पूर्णांकel_mode_valid_max_plane_size(dev_priv, mode, false);
पूर्ण

bool पूर्णांकel_hdmi_deep_color_possible(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक bpc, bool has_hdmi_sink, bool ycbcr420_output)
अणु
	काष्ठा drm_atomic_state *state = crtc_state->uapi.state;
	काष्ठा drm_connector_state *connector_state;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	अगर (crtc_state->pipe_bpp < bpc * 3)
		वापस false;

	अगर (!has_hdmi_sink)
		वापस false;

	क्रम_each_new_connector_in_state(state, connector, connector_state, i) अणु
		स्थिर काष्ठा drm_display_info *info = &connector->display_info;

		अगर (connector_state->crtc != crtc_state->uapi.crtc)
			जारी;

		अगर (ycbcr420_output) अणु
			स्थिर काष्ठा drm_hdmi_info *hdmi = &info->hdmi;

			अगर (bpc == 12 && !(hdmi->y420_dc_modes &
					   DRM_EDID_YCBCR420_DC_36))
				वापस false;
			अन्यथा अगर (bpc == 10 && !(hdmi->y420_dc_modes &
						DRM_EDID_YCBCR420_DC_30))
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (bpc == 12 && !(info->edid_hdmi_dc_modes &
					   DRM_EDID_HDMI_DC_36))
				वापस false;
			अन्यथा अगर (bpc == 10 && !(info->edid_hdmi_dc_modes &
						DRM_EDID_HDMI_DC_30))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool hdmi_deep_color_possible(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     पूर्णांक bpc)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(crtc_state->uapi.crtc->dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	अगर (HAS_GMCH(dev_priv))
		वापस false;

	अगर (bpc == 10 && DISPLAY_VER(dev_priv) < 11)
		वापस false;

	/*
	 * HDMI deep color affects the घड़ीs, so it's only possible
	 * when not cloning with other encoder types.
	 */
	अगर (crtc_state->output_types != BIT(INTEL_OUTPUT_HDMI))
		वापस false;

	/* Display Wa_1405510057:icl,ehl */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420 &&
	    bpc == 10 && IS_DISPLAY_VER(dev_priv, 11) &&
	    (adjusted_mode->crtc_hblank_end -
	     adjusted_mode->crtc_hblank_start) % 8 == 2)
		वापस false;

	वापस पूर्णांकel_hdmi_deep_color_possible(crtc_state, bpc,
					      crtc_state->has_hdmi_sink,
					      crtc_state->output_क्रमmat ==
					      INTEL_OUTPUT_FORMAT_YCBCR420);
पूर्ण

अटल पूर्णांक
पूर्णांकel_hdmi_ycbcr420_config(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	अगर (!drm_mode_is_420_only(&connector->display_info, adjusted_mode))
		वापस 0;

	अगर (!connector->ycbcr_420_allowed) अणु
		drm_err(&i915->drm,
			"Platform doesn't support YCBCR420 output\n");
		वापस -EINVAL;
	पूर्ण

	crtc_state->output_क्रमmat = INTEL_OUTPUT_FORMAT_YCBCR420;

	वापस पूर्णांकel_pch_panel_fitting(crtc_state, conn_state);
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_compute_bpc(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  पूर्णांक घड़ी)
अणु
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	पूर्णांक bpc;

	क्रम (bpc = 12; bpc >= 10; bpc -= 2) अणु
		अगर (hdmi_deep_color_possible(crtc_state, bpc) &&
		    hdmi_port_घड़ी_valid(पूर्णांकel_hdmi,
					  पूर्णांकel_hdmi_port_घड़ी(घड़ी, bpc),
					  true, crtc_state->has_hdmi_sink) == MODE_OK)
			वापस bpc;
	पूर्ण

	वापस 8;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_compute_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	पूर्णांक bpc, घड़ी = adjusted_mode->crtc_घड़ी;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		घड़ी *= 2;

	/* YCBCR420 TMDS rate requirement is half the pixel घड़ी */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
		घड़ी /= 2;

	bpc = पूर्णांकel_hdmi_compute_bpc(encoder, crtc_state, घड़ी);

	crtc_state->port_घड़ी = पूर्णांकel_hdmi_port_घड़ी(घड़ी, bpc);

	/*
	 * pipe_bpp could alपढ़ोy be below 8bpc due to
	 * FDI bandwidth स्थिरraपूर्णांकs. We shouldn't bump it
	 * back up to 8bpc in that हाल.
	 */
	अगर (crtc_state->pipe_bpp > bpc * 3)
		crtc_state->pipe_bpp = bpc * 3;

	drm_dbg_kms(&i915->drm,
		    "picking %d bpc for HDMI output (pipe bpp: %d)\n",
		    bpc, crtc_state->pipe_bpp);

	अगर (hdmi_port_घड़ी_valid(पूर्णांकel_hdmi, crtc_state->port_घड़ी,
				  false, crtc_state->has_hdmi_sink) != MODE_OK) अणु
		drm_dbg_kms(&i915->drm,
			    "unsupported HDMI clock (%d kHz), rejecting mode\n",
			    crtc_state->port_घड़ी);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool पूर्णांकel_hdmi_limited_color_range(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	स्थिर काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(conn_state);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	/*
	 * Our YCbCr output is always limited range.
	 * crtc_state->limited_color_range only applies to RGB,
	 * and it must never be set क्रम YCbCr or we risk setting
	 * some conflicting bits in PIPECONF which will mess up
	 * the colors on the monitor.
	 */
	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB)
		वापस false;

	अगर (पूर्णांकel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_AUTO) अणु
		/* See CEA-861-E - 5.1 Default Encoding Parameters */
		वापस crtc_state->has_hdmi_sink &&
			drm_शेष_rgb_quant_range(adjusted_mode) ==
			HDMI_QUANTIZATION_RANGE_LIMITED;
	पूर्ण अन्यथा अणु
		वापस पूर्णांकel_conn_state->broadcast_rgb == INTEL_BROADCAST_RGB_LIMITED;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_hdmi_has_audio(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	स्थिर काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(conn_state);

	अगर (!crtc_state->has_hdmi_sink)
		वापस false;

	अगर (पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_AUTO)
		वापस पूर्णांकel_hdmi->has_audio;
	अन्यथा
		वापस पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_ON;
पूर्ण

पूर्णांक पूर्णांकel_hdmi_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
			      काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा drm_scdc *scdc = &connector->display_info.hdmi.scdc;
	पूर्णांक ret;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
	pipe_config->has_hdmi_sink = पूर्णांकel_has_hdmi_sink(पूर्णांकel_hdmi,
							 conn_state);

	अगर (pipe_config->has_hdmi_sink)
		pipe_config->has_infoframe = true;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLCLK)
		pipe_config->pixel_multiplier = 2;

	ret = पूर्णांकel_hdmi_ycbcr420_config(pipe_config, conn_state);
	अगर (ret)
		वापस ret;

	pipe_config->limited_color_range =
		पूर्णांकel_hdmi_limited_color_range(pipe_config, conn_state);

	अगर (HAS_PCH_SPLIT(dev_priv) && !HAS_DDI(dev_priv))
		pipe_config->has_pch_encoder = true;

	pipe_config->has_audio =
		पूर्णांकel_hdmi_has_audio(encoder, pipe_config, conn_state);

	ret = पूर्णांकel_hdmi_compute_घड़ी(encoder, pipe_config);
	अगर (ret)
		वापस ret;

	अगर (conn_state->picture_aspect_ratio)
		adjusted_mode->picture_aspect_ratio =
			conn_state->picture_aspect_ratio;

	pipe_config->lane_count = 4;

	अगर (scdc->scrambling.supported && DISPLAY_VER(dev_priv) >= 10) अणु
		अगर (scdc->scrambling.low_rates)
			pipe_config->hdmi_scrambling = true;

		अगर (pipe_config->port_घड़ी > 340000) अणु
			pipe_config->hdmi_scrambling = true;
			pipe_config->hdmi_high_पंचांगds_घड़ी_ratio = true;
		पूर्ण
	पूर्ण

	पूर्णांकel_hdmi_compute_gcp_infoframe(encoder, pipe_config,
					 conn_state);

	अगर (!पूर्णांकel_hdmi_compute_avi_infoframe(encoder, pipe_config, conn_state)) अणु
		drm_dbg_kms(&dev_priv->drm, "bad AVI infoframe\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!पूर्णांकel_hdmi_compute_spd_infoframe(encoder, pipe_config, conn_state)) अणु
		drm_dbg_kms(&dev_priv->drm, "bad SPD infoframe\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!पूर्णांकel_hdmi_compute_hdmi_infoframe(encoder, pipe_config, conn_state)) अणु
		drm_dbg_kms(&dev_priv->drm, "bad HDMI infoframe\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!पूर्णांकel_hdmi_compute_drm_infoframe(encoder, pipe_config, conn_state)) अणु
		drm_dbg_kms(&dev_priv->drm, "bad DRM infoframe\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_hdmi_unset_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));

	पूर्णांकel_hdmi->has_hdmi_sink = false;
	पूर्णांकel_hdmi->has_audio = false;

	पूर्णांकel_hdmi->dp_dual_mode.type = DRM_DP_DUAL_MODE_NONE;
	पूर्णांकel_hdmi->dp_dual_mode.max_पंचांगds_घड़ी = 0;

	kमुक्त(to_पूर्णांकel_connector(connector)->detect_edid);
	to_पूर्णांकel_connector(connector)->detect_edid = शून्य;
पूर्ण

अटल व्योम
पूर्णांकel_hdmi_dp_dual_mode_detect(काष्ठा drm_connector *connector, bool has_edid)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));
	क्रमागत port port = hdmi_to_dig_port(hdmi)->base.port;
	काष्ठा i2c_adapter *adapter =
		पूर्णांकel_gmbus_get_adapter(dev_priv, hdmi->ddc_bus);
	क्रमागत drm_dp_dual_mode_type type = drm_dp_dual_mode_detect(adapter);

	/*
	 * Type 1 DVI adaptors are not required to implement any
	 * रेजिस्टरs, so we can't always detect their presence.
	 * Ideally we should be able to check the state of the
	 * CONFIG1 pin, but no such luck on our hardware.
	 *
	 * The only method left to us is to check the VBT to see
	 * अगर the port is a dual mode capable DP port. But let's
	 * only करो that when we sucesfully पढ़ो the EDID, to aव्योम
	 * confusing log messages about DP dual mode adaptors when
	 * there's nothing connected to the port.
	 */
	अगर (type == DRM_DP_DUAL_MODE_UNKNOWN) अणु
		/* An overridden EDID imply that we want this port क्रम testing.
		 * Make sure not to set limits क्रम that port.
		 */
		अगर (has_edid && !connector->override_edid &&
		    पूर्णांकel_bios_is_port_dp_dual_mode(dev_priv, port)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Assuming DP dual mode adaptor presence based on VBT\n");
			type = DRM_DP_DUAL_MODE_TYPE1_DVI;
		पूर्ण अन्यथा अणु
			type = DRM_DP_DUAL_MODE_NONE;
		पूर्ण
	पूर्ण

	अगर (type == DRM_DP_DUAL_MODE_NONE)
		वापस;

	hdmi->dp_dual_mode.type = type;
	hdmi->dp_dual_mode.max_पंचांगds_घड़ी =
		drm_dp_dual_mode_max_पंचांगds_घड़ी(type, adapter);

	drm_dbg_kms(&dev_priv->drm,
		    "DP dual mode adaptor (%s) detected (max TMDS clock: %d kHz)\n",
		    drm_dp_get_dual_mode_type_name(type),
		    hdmi->dp_dual_mode.max_पंचांगds_घड़ी);
पूर्ण

अटल bool
पूर्णांकel_hdmi_set_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा edid *edid;
	bool connected = false;
	काष्ठा i2c_adapter *i2c;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_GMBUS);

	i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, पूर्णांकel_hdmi->ddc_bus);

	edid = drm_get_edid(connector, i2c);

	अगर (!edid && !पूर्णांकel_gmbus_is_क्रमced_bit(i2c)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "HDMI GMBUS EDID read failed, retry using GPIO bit-banging\n");
		पूर्णांकel_gmbus_क्रमce_bit(i2c, true);
		edid = drm_get_edid(connector, i2c);
		पूर्णांकel_gmbus_क्रमce_bit(i2c, false);
	पूर्ण

	पूर्णांकel_hdmi_dp_dual_mode_detect(connector, edid != शून्य);

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_GMBUS, wakeref);

	to_पूर्णांकel_connector(connector)->detect_edid = edid;
	अगर (edid && edid->input & DRM_EDID_INPUT_DIGITAL) अणु
		पूर्णांकel_hdmi->has_audio = drm_detect_monitor_audio(edid);
		पूर्णांकel_hdmi->has_hdmi_sink = drm_detect_hdmi_monitor(edid);

		connected = true;
	पूर्ण

	cec_notअगरier_set_phys_addr_from_edid(पूर्णांकel_hdmi->cec_notअगरier, edid);

	वापस connected;
पूर्ण

अटल क्रमागत drm_connector_status
पूर्णांकel_hdmi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	क्रमागत drm_connector_status status = connector_status_disconnected;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_encoder *encoder = &hdmi_to_dig_port(पूर्णांकel_hdmi)->base;
	पूर्णांकel_wakeref_t wakeref;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.id, connector->name);

	अगर (!INTEL_DISPLAY_ENABLED(dev_priv))
		वापस connector_status_disconnected;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_GMBUS);

	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    !पूर्णांकel_digital_port_connected(encoder))
		जाओ out;

	पूर्णांकel_hdmi_unset_edid(connector);

	अगर (पूर्णांकel_hdmi_set_edid(connector))
		status = connector_status_connected;

out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_GMBUS, wakeref);

	अगर (status != connector_status_connected)
		cec_notअगरier_phys_addr_invalidate(पूर्णांकel_hdmi->cec_notअगरier);

	/*
	 * Make sure the refs क्रम घातer wells enabled during detect are
	 * dropped to aव्योम a new detect cycle triggered by HPD polling.
	 */
	पूर्णांकel_display_घातer_flush_work(dev_priv);

	वापस status;
पूर्ण

अटल व्योम
पूर्णांकel_hdmi_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);

	drm_dbg_kms(&i915->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.id, connector->name);

	पूर्णांकel_hdmi_unset_edid(connector);

	अगर (connector->status != connector_status_connected)
		वापस;

	पूर्णांकel_hdmi_set_edid(connector);
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;

	edid = to_पूर्णांकel_connector(connector)->detect_edid;
	अगर (edid == शून्य)
		वापस 0;

	वापस पूर्णांकel_connector_update_modes(connector, edid);
पूर्ण

अटल काष्ठा i2c_adapter *
पूर्णांकel_hdmi_get_i2c_adapter(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector));

	वापस पूर्णांकel_gmbus_get_adapter(dev_priv, पूर्णांकel_hdmi->ddc_bus);
पूर्ण

अटल व्योम पूर्णांकel_hdmi_create_i2c_symlink(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा i2c_adapter *adapter = पूर्णांकel_hdmi_get_i2c_adapter(connector);
	काष्ठा kobject *i2c_kobj = &adapter->dev.kobj;
	काष्ठा kobject *connector_kobj = &connector->kdev->kobj;
	पूर्णांक ret;

	ret = sysfs_create_link(connector_kobj, i2c_kobj, i2c_kobj->name);
	अगर (ret)
		drm_err(&i915->drm, "Failed to create i2c symlink (%d)\n", ret);
पूर्ण

अटल व्योम पूर्णांकel_hdmi_हटाओ_i2c_symlink(काष्ठा drm_connector *connector)
अणु
	काष्ठा i2c_adapter *adapter = पूर्णांकel_hdmi_get_i2c_adapter(connector);
	काष्ठा kobject *i2c_kobj = &adapter->dev.kobj;
	काष्ठा kobject *connector_kobj = &connector->kdev->kobj;

	sysfs_हटाओ_link(connector_kobj, i2c_kobj->name);
पूर्ण

अटल पूर्णांक
पूर्णांकel_hdmi_connector_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret;

	ret = पूर्णांकel_connector_रेजिस्टर(connector);
	अगर (ret)
		वापस ret;

	पूर्णांकel_hdmi_create_i2c_symlink(connector);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_hdmi_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा cec_notअगरier *n = पूर्णांकel_attached_hdmi(to_पूर्णांकel_connector(connector))->cec_notअगरier;

	cec_notअगरier_conn_unरेजिस्टर(n);

	पूर्णांकel_hdmi_हटाओ_i2c_symlink(connector);
	पूर्णांकel_connector_unरेजिस्टर(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_hdmi_connector_funcs = अणु
	.detect = पूर्णांकel_hdmi_detect,
	.क्रमce = पूर्णांकel_hdmi_क्रमce,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_digital_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_digital_connector_atomic_set_property,
	.late_रेजिस्टर = पूर्णांकel_hdmi_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_hdmi_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_digital_connector_duplicate_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_hdmi_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_hdmi_get_modes,
	.mode_valid = पूर्णांकel_hdmi_mode_valid,
	.atomic_check = पूर्णांकel_digital_connector_atomic_check,
पूर्ण;

अटल व्योम
पूर्णांकel_hdmi_add_properties(काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);

	पूर्णांकel_attach_क्रमce_audio_property(connector);
	पूर्णांकel_attach_broadcast_rgb_property(connector);
	पूर्णांकel_attach_aspect_ratio_property(connector);

	पूर्णांकel_attach_hdmi_colorspace_property(connector);
	drm_connector_attach_content_type_property(connector);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		drm_object_attach_property(&connector->base,
			connector->dev->mode_config.hdr_output_metadata_property, 0);

	अगर (!HAS_GMCH(dev_priv))
		drm_connector_attach_max_bpc_property(connector, 8, 12);
पूर्ण

/*
 * पूर्णांकel_hdmi_handle_sink_scrambling: handle sink scrambling/घड़ी ratio setup
 * @encoder: पूर्णांकel_encoder
 * @connector: drm_connector
 * @high_पंचांगds_घड़ी_ratio = bool to indicate अगर the function needs to set
 *  or reset the high पंचांगds घड़ी ratio क्रम scrambling
 * @scrambling: bool to Indicate अगर the function needs to set or reset
 *  sink scrambling
 *
 * This function handles scrambling on HDMI 2.0 capable sinks.
 * If required घड़ी rate is > 340 Mhz && scrambling is supported by sink
 * it enables scrambling. This should be called beक्रमe enabling the HDMI
 * 2.0 port, as the sink can choose to disable the scrambling अगर it करोesn't
 * detect a scrambled घड़ी within 100 ms.
 *
 * Returns:
 * True on success, false on failure.
 */
bool पूर्णांकel_hdmi_handle_sink_scrambling(काष्ठा पूर्णांकel_encoder *encoder,
				       काष्ठा drm_connector *connector,
				       bool high_पंचांगds_घड़ी_ratio,
				       bool scrambling)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	काष्ठा drm_scrambling *sink_scrambling =
		&connector->display_info.hdmi.scdc.scrambling;
	काष्ठा i2c_adapter *adapter =
		पूर्णांकel_gmbus_get_adapter(dev_priv, पूर्णांकel_hdmi->ddc_bus);

	अगर (!sink_scrambling->supported)
		वापस true;

	drm_dbg_kms(&dev_priv->drm,
		    "[CONNECTOR:%d:%s] scrambling=%s, TMDS bit clock ratio=1/%d\n",
		    connector->base.id, connector->name,
		    yesno(scrambling), high_पंचांगds_घड़ी_ratio ? 40 : 10);

	/* Set TMDS bit घड़ी ratio to 1/40 or 1/10, and enable/disable scrambling */
	वापस drm_scdc_set_high_पंचांगds_घड़ी_ratio(adapter,
						  high_पंचांगds_घड़ी_ratio) &&
		drm_scdc_set_scrambling(adapter, scrambling);
पूर्ण

अटल u8 chv_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	u8 ddc_pin;

	चयन (port) अणु
	हाल PORT_B:
		ddc_pin = GMBUS_PIN_DPB;
		अवरोध;
	हाल PORT_C:
		ddc_pin = GMBUS_PIN_DPC;
		अवरोध;
	हाल PORT_D:
		ddc_pin = GMBUS_PIN_DPD_CHV;
		अवरोध;
	शेष:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_DPB;
		अवरोध;
	पूर्ण
	वापस ddc_pin;
पूर्ण

अटल u8 bxt_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	u8 ddc_pin;

	चयन (port) अणु
	हाल PORT_B:
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	हाल PORT_C:
		ddc_pin = GMBUS_PIN_2_BXT;
		अवरोध;
	शेष:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	पूर्ण
	वापस ddc_pin;
पूर्ण

अटल u8 cnp_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत port port)
अणु
	u8 ddc_pin;

	चयन (port) अणु
	हाल PORT_B:
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	हाल PORT_C:
		ddc_pin = GMBUS_PIN_2_BXT;
		अवरोध;
	हाल PORT_D:
		ddc_pin = GMBUS_PIN_4_CNP;
		अवरोध;
	हाल PORT_F:
		ddc_pin = GMBUS_PIN_3_BXT;
		अवरोध;
	शेष:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	पूर्ण
	वापस ddc_pin;
पूर्ण

अटल u8 icl_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);

	अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
		वापस GMBUS_PIN_1_BXT + port;
	अन्यथा अगर (पूर्णांकel_phy_is_tc(dev_priv, phy))
		वापस GMBUS_PIN_9_TC1_ICP + पूर्णांकel_port_to_tc(dev_priv, port);

	drm_WARN(&dev_priv->drm, 1, "Unknown port:%c\n", port_name(port));
	वापस GMBUS_PIN_2_BXT;
पूर्ण

अटल u8 mcc_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);
	u8 ddc_pin;

	चयन (phy) अणु
	हाल PHY_A:
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	हाल PHY_B:
		ddc_pin = GMBUS_PIN_2_BXT;
		अवरोध;
	हाल PHY_C:
		ddc_pin = GMBUS_PIN_9_TC1_ICP;
		अवरोध;
	शेष:
		MISSING_CASE(phy);
		ddc_pin = GMBUS_PIN_1_BXT;
		अवरोध;
	पूर्ण
	वापस ddc_pin;
पूर्ण

अटल u8 rkl_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);

	WARN_ON(port == PORT_C);

	/*
	 * Pin mapping क्रम RKL depends on which PCH is present.  With TGP, the
	 * final two outमाला_दो use type-c pins, even though they're actually
	 * combo outमाला_दो.  With CMP, the traditional DDI A-D pins are used क्रम
	 * all outमाला_दो.
	 */
	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_TGP && phy >= PHY_C)
		वापस GMBUS_PIN_9_TC1_ICP + phy - PHY_C;

	वापस GMBUS_PIN_1_BXT + phy;
पूर्ण

अटल u8 gen9bc_tgp_port_to_ddc_pin(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, port);

	drm_WARN_ON(&i915->drm, port == PORT_A);

	/*
	 * Pin mapping क्रम GEN9 BC depends on which PCH is present.  With TGP,
	 * final two outमाला_दो use type-c pins, even though they're actually
	 * combo outमाला_दो.  With CMP, the traditional DDI A-D pins are used क्रम
	 * all outमाला_दो.
	 */
	अगर (INTEL_PCH_TYPE(i915) >= PCH_TGP && phy >= PHY_C)
		वापस GMBUS_PIN_9_TC1_ICP + phy - PHY_C;

	वापस GMBUS_PIN_1_BXT + phy;
पूर्ण

अटल u8 dg1_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	वापस पूर्णांकel_port_to_phy(dev_priv, port) + 1;
पूर्ण

अटल u8 adls_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);

	WARN_ON(port == PORT_B || port == PORT_C);

	/*
	 * Pin mapping क्रम ADL-S requires TC pins क्रम all combo phy outमाला_दो
	 * except first combo output.
	 */
	अगर (phy == PHY_A)
		वापस GMBUS_PIN_1_BXT;

	वापस GMBUS_PIN_9_TC1_ICP + phy - PHY_B;
पूर्ण

अटल u8 g4x_port_to_ddc_pin(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत port port)
अणु
	u8 ddc_pin;

	चयन (port) अणु
	हाल PORT_B:
		ddc_pin = GMBUS_PIN_DPB;
		अवरोध;
	हाल PORT_C:
		ddc_pin = GMBUS_PIN_DPC;
		अवरोध;
	हाल PORT_D:
		ddc_pin = GMBUS_PIN_DPD;
		अवरोध;
	शेष:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_DPB;
		अवरोध;
	पूर्ण
	वापस ddc_pin;
पूर्ण

अटल u8 पूर्णांकel_hdmi_ddc_pin(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	u8 ddc_pin;

	ddc_pin = पूर्णांकel_bios_alternate_ddc_pin(encoder);
	अगर (ddc_pin) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Using DDC pin 0x%x for port %c (VBT)\n",
			    ddc_pin, port_name(port));
		वापस ddc_pin;
	पूर्ण

	अगर (HAS_PCH_ADP(dev_priv))
		ddc_pin = adls_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_DG1)
		ddc_pin = dg1_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (IS_ROCKETLAKE(dev_priv))
		ddc_pin = rkl_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (IS_GEN9_BC(dev_priv) && HAS_PCH_TGP(dev_priv))
		ddc_pin = gen9bc_tgp_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (HAS_PCH_MCC(dev_priv))
		ddc_pin = mcc_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
		ddc_pin = icl_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (HAS_PCH_CNP(dev_priv))
		ddc_pin = cnp_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		ddc_pin = bxt_port_to_ddc_pin(dev_priv, port);
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		ddc_pin = chv_port_to_ddc_pin(dev_priv, port);
	अन्यथा
		ddc_pin = g4x_port_to_ddc_pin(dev_priv, port);

	drm_dbg_kms(&dev_priv->drm,
		    "Using DDC pin 0x%x for port %c (platform default)\n",
		    ddc_pin, port_name(port));

	वापस ddc_pin;
पूर्ण

व्योम पूर्णांकel_infoframe_init(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(dig_port->base.base.dev);

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		dig_port->ग_लिखो_infoframe = vlv_ग_लिखो_infoframe;
		dig_port->पढ़ो_infoframe = vlv_पढ़ो_infoframe;
		dig_port->set_infoframes = vlv_set_infoframes;
		dig_port->infoframes_enabled = vlv_infoframes_enabled;
	पूर्ण अन्यथा अगर (IS_G4X(dev_priv)) अणु
		dig_port->ग_लिखो_infoframe = g4x_ग_लिखो_infoframe;
		dig_port->पढ़ो_infoframe = g4x_पढ़ो_infoframe;
		dig_port->set_infoframes = g4x_set_infoframes;
		dig_port->infoframes_enabled = g4x_infoframes_enabled;
	पूर्ण अन्यथा अगर (HAS_DDI(dev_priv)) अणु
		अगर (पूर्णांकel_bios_is_lspcon_present(dev_priv, dig_port->base.port)) अणु
			dig_port->ग_लिखो_infoframe = lspcon_ग_लिखो_infoframe;
			dig_port->पढ़ो_infoframe = lspcon_पढ़ो_infoframe;
			dig_port->set_infoframes = lspcon_set_infoframes;
			dig_port->infoframes_enabled = lspcon_infoframes_enabled;
		पूर्ण अन्यथा अणु
			dig_port->ग_लिखो_infoframe = hsw_ग_लिखो_infoframe;
			dig_port->पढ़ो_infoframe = hsw_पढ़ो_infoframe;
			dig_port->set_infoframes = hsw_set_infoframes;
			dig_port->infoframes_enabled = hsw_infoframes_enabled;
		पूर्ण
	पूर्ण अन्यथा अगर (HAS_PCH_IBX(dev_priv)) अणु
		dig_port->ग_लिखो_infoframe = ibx_ग_लिखो_infoframe;
		dig_port->पढ़ो_infoframe = ibx_पढ़ो_infoframe;
		dig_port->set_infoframes = ibx_set_infoframes;
		dig_port->infoframes_enabled = ibx_infoframes_enabled;
	पूर्ण अन्यथा अणु
		dig_port->ग_लिखो_infoframe = cpt_ग_लिखो_infoframe;
		dig_port->पढ़ो_infoframe = cpt_पढ़ो_infoframe;
		dig_port->set_infoframes = cpt_set_infoframes;
		dig_port->infoframes_enabled = cpt_infoframes_enabled;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_hdmi_init_connector(काष्ठा पूर्णांकel_digital_port *dig_port,
			       काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = &dig_port->hdmi;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &dig_port->base;
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा i2c_adapter *ddc;
	क्रमागत port port = पूर्णांकel_encoder->port;
	काष्ठा cec_connector_info conn_info;

	drm_dbg_kms(&dev_priv->drm,
		    "Adding HDMI connector on [ENCODER:%d:%s]\n",
		    पूर्णांकel_encoder->base.base.id, पूर्णांकel_encoder->base.name);

	अगर (DISPLAY_VER(dev_priv) < 12 && drm_WARN_ON(dev, port == PORT_A))
		वापस;

	अगर (drm_WARN(dev, dig_port->max_lanes < 4,
		     "Not enough lanes (%d) for HDMI on [ENCODER:%d:%s]\n",
		     dig_port->max_lanes, पूर्णांकel_encoder->base.base.id,
		     पूर्णांकel_encoder->base.name))
		वापस;

	पूर्णांकel_hdmi->ddc_bus = पूर्णांकel_hdmi_ddc_pin(पूर्णांकel_encoder);
	ddc = पूर्णांकel_gmbus_get_adapter(dev_priv, पूर्णांकel_hdmi->ddc_bus);

	drm_connector_init_with_ddc(dev, connector,
				    &पूर्णांकel_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    ddc);
	drm_connector_helper_add(connector, &पूर्णांकel_hdmi_connector_helper_funcs);

	connector->पूर्णांकerlace_allowed = 1;
	connector->द्विगुनscan_allowed = 0;
	connector->stereo_allowed = 1;

	अगर (DISPLAY_VER(dev_priv) >= 10)
		connector->ycbcr_420_allowed = true;

	पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_HPD;

	अगर (HAS_DDI(dev_priv))
		पूर्णांकel_connector->get_hw_state = पूर्णांकel_ddi_connector_get_hw_state;
	अन्यथा
		पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	पूर्णांकel_hdmi_add_properties(पूर्णांकel_hdmi, connector);

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);
	पूर्णांकel_hdmi->attached_connector = पूर्णांकel_connector;

	अगर (is_hdcp_supported(dev_priv, port)) अणु
		पूर्णांक ret = पूर्णांकel_hdcp_init(पूर्णांकel_connector, dig_port,
					  &पूर्णांकel_hdmi_hdcp_shim);
		अगर (ret)
			drm_dbg_kms(&dev_priv->drm,
				    "HDCP init failed, skipping.\n");
	पूर्ण

	/* For G4X desktop chip, PEG_BAND_GAP_DATA 3:0 must first be written
	 * 0xd.  Failure to करो so will result in spurious पूर्णांकerrupts being
	 * generated on the port when a cable is not attached.
	 */
	अगर (IS_G45(dev_priv)) अणु
		u32 temp = पूर्णांकel_de_पढ़ो(dev_priv, PEG_BAND_GAP_DATA);
		पूर्णांकel_de_ग_लिखो(dev_priv, PEG_BAND_GAP_DATA,
		               (temp & ~0xf) | 0xd);
	पूर्ण

	cec_fill_conn_info_from_drm(&conn_info, connector);

	पूर्णांकel_hdmi->cec_notअगरier =
		cec_notअगरier_conn_रेजिस्टर(dev->dev, port_identअगरier(port),
					   &conn_info);
	अगर (!पूर्णांकel_hdmi->cec_notअगरier)
		drm_dbg_kms(&dev_priv->drm, "CEC notifier get failed\n");
पूर्ण

/*
 * पूर्णांकel_hdmi_dsc_get_slice_height - get the dsc slice_height
 * @vactive: Vactive of a display mode
 *
 * @वापस: appropriate dsc slice height क्रम a given mode.
 */
पूर्णांक पूर्णांकel_hdmi_dsc_get_slice_height(पूर्णांक vactive)
अणु
	पूर्णांक slice_height;

	/*
	 * Slice Height determination : HDMI2.1 Section 7.7.5.2
	 * Select smallest slice height >=96, that results in a valid PPS and
	 * requires minimum padding lines required क्रम final slice.
	 *
	 * Assumption : Vactive is even.
	 */
	क्रम (slice_height = 96; slice_height <= vactive; slice_height += 2)
		अगर (vactive % slice_height == 0)
			वापस slice_height;

	वापस 0;
पूर्ण

/*
 * पूर्णांकel_hdmi_dsc_get_num_slices - get no. of dsc slices based on dsc encoder
 * and dsc decoder capabilities
 *
 * @crtc_state: पूर्णांकel crtc_state
 * @src_max_slices: maximum slices supported by the DSC encoder
 * @src_max_slice_width: maximum slice width supported by DSC encoder
 * @hdmi_max_slices: maximum slices supported by sink DSC decoder
 * @hdmi_throughput: maximum घड़ी per slice (MHz) supported by HDMI sink
 *
 * @वापस: num of dsc slices that can be supported by the dsc encoder
 * and decoder.
 */
पूर्णांक
पूर्णांकel_hdmi_dsc_get_num_slices(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      पूर्णांक src_max_slices, पूर्णांक src_max_slice_width,
			      पूर्णांक hdmi_max_slices, पूर्णांक hdmi_throughput)
अणु
/* Pixel rates in KPixels/sec */
#घोषणा HDMI_DSC_PEAK_PIXEL_RATE		2720000
/*
 * Rates at which the source and sink are required to process pixels in each
 * slice, can be two levels: either atleast 340000KHz or atleast 40000KHz.
 */
#घोषणा HDMI_DSC_MAX_ENC_THROUGHPUT_0		340000
#घोषणा HDMI_DSC_MAX_ENC_THROUGHPUT_1		400000

/* Spec limits the slice width to 2720 pixels */
#घोषणा MAX_HDMI_SLICE_WIDTH			2720
	पूर्णांक kslice_adjust;
	पूर्णांक adjusted_clk_khz;
	पूर्णांक min_slices;
	पूर्णांक target_slices;
	पूर्णांक max_throughput; /* max घड़ी freq. in khz per slice */
	पूर्णांक max_slice_width;
	पूर्णांक slice_width;
	पूर्णांक pixel_घड़ी = crtc_state->hw.adjusted_mode.crtc_घड़ी;

	अगर (!hdmi_throughput)
		वापस 0;

	/*
	 * Slice Width determination : HDMI2.1 Section 7.7.5.1
	 * kslice_adjust factor क्रम 4:2:0, and 4:2:2 क्रमmats is 0.5, where as
	 * क्रम 4:4:4 is 1.0. Multiplying these factors by 10 and later
	 * भागiding adjusted घड़ी value by 10.
	 */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444 ||
	    crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_RGB)
		kslice_adjust = 10;
	अन्यथा
		kslice_adjust = 5;

	/*
	 * As per spec, the rate at which the source and the sink process
	 * the pixels per slice are at two levels: atleast 340Mhz or 400Mhz.
	 * This depends upon the pixel घड़ी rate and output क्रमmats
	 * (kslice adjust).
	 * If pixel घड़ी * kslice adjust >= 2720MHz slices can be processed
	 * at max 340MHz, otherwise they can be processed at max 400MHz.
	 */

	adjusted_clk_khz = DIV_ROUND_UP(kslice_adjust * pixel_घड़ी, 10);

	अगर (adjusted_clk_khz <= HDMI_DSC_PEAK_PIXEL_RATE)
		max_throughput = HDMI_DSC_MAX_ENC_THROUGHPUT_0;
	अन्यथा
		max_throughput = HDMI_DSC_MAX_ENC_THROUGHPUT_1;

	/*
	 * Taking पूर्णांकo account the sink's capability क्रम maximum
	 * घड़ी per slice (in MHz) as पढ़ो from HF-VSDB.
	 */
	max_throughput = min(max_throughput, hdmi_throughput * 1000);

	min_slices = DIV_ROUND_UP(adjusted_clk_khz, max_throughput);
	max_slice_width = min(MAX_HDMI_SLICE_WIDTH, src_max_slice_width);

	/*
	 * Keep on increasing the num of slices/line, starting from min_slices
	 * per line till we get such a number, क्रम which the slice_width is
	 * just less than max_slice_width. The slices/line selected should be
	 * less than or equal to the max horizontal slices that the combination
	 * of PCON encoder and HDMI decoder can support.
	 */
	slice_width = max_slice_width;

	करो अणु
		अगर (min_slices <= 1 && src_max_slices >= 1 && hdmi_max_slices >= 1)
			target_slices = 1;
		अन्यथा अगर (min_slices <= 2 && src_max_slices >= 2 && hdmi_max_slices >= 2)
			target_slices = 2;
		अन्यथा अगर (min_slices <= 4 && src_max_slices >= 4 && hdmi_max_slices >= 4)
			target_slices = 4;
		अन्यथा अगर (min_slices <= 8 && src_max_slices >= 8 && hdmi_max_slices >= 8)
			target_slices = 8;
		अन्यथा अगर (min_slices <= 12 && src_max_slices >= 12 && hdmi_max_slices >= 12)
			target_slices = 12;
		अन्यथा अगर (min_slices <= 16 && src_max_slices >= 16 && hdmi_max_slices >= 16)
			target_slices = 16;
		अन्यथा
			वापस 0;

		slice_width = DIV_ROUND_UP(crtc_state->hw.adjusted_mode.hdisplay, target_slices);
		अगर (slice_width >= max_slice_width)
			min_slices = target_slices + 1;
	पूर्ण जबतक (slice_width >= max_slice_width);

	वापस target_slices;
पूर्ण

/*
 * पूर्णांकel_hdmi_dsc_get_bpp - get the appropriate compressed bits_per_pixel based on
 * source and sink capabilities.
 *
 * @src_fraction_bpp: fractional bpp supported by the source
 * @slice_width: dsc slice width supported by the source and sink
 * @num_slices: num of slices supported by the source and sink
 * @output_क्रमmat: video output क्रमmat
 * @hdmi_all_bpp: sink supports decoding of 1/16th bpp setting
 * @hdmi_max_chunk_bytes: max bytes in a line of chunks supported by sink
 *
 * @वापस: compressed bits_per_pixel in step of 1/16 of bits_per_pixel
 */
पूर्णांक
पूर्णांकel_hdmi_dsc_get_bpp(पूर्णांक src_fractional_bpp, पूर्णांक slice_width, पूर्णांक num_slices,
		       पूर्णांक output_क्रमmat, bool hdmi_all_bpp,
		       पूर्णांक hdmi_max_chunk_bytes)
अणु
	पूर्णांक max_dsc_bpp, min_dsc_bpp;
	पूर्णांक target_bytes;
	bool bpp_found = false;
	पूर्णांक bpp_decrement_x16;
	पूर्णांक bpp_target;
	पूर्णांक bpp_target_x16;

	/*
	 * Get min bpp and max bpp as per Table 7.23, in HDMI2.1 spec
	 * Start with the max bpp and keep on decrementing with
	 * fractional bpp, अगर supported by PCON DSC encoder
	 *
	 * क्रम each bpp we check अगर no of bytes can be supported by HDMI sink
	 */

	/* Assuming: bpc as 8*/
	अगर (output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420) अणु
		min_dsc_bpp = 6;
		max_dsc_bpp = 3 * 4; /* 3*bpc/2 */
	पूर्ण अन्यथा अगर (output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444 ||
		   output_क्रमmat == INTEL_OUTPUT_FORMAT_RGB) अणु
		min_dsc_bpp = 8;
		max_dsc_bpp = 3 * 8; /* 3*bpc */
	पूर्ण अन्यथा अणु
		/* Assuming 4:2:2 encoding */
		min_dsc_bpp = 7;
		max_dsc_bpp = 2 * 8; /* 2*bpc */
	पूर्ण

	/*
	 * Taking पूर्णांकo account अगर all dsc_all_bpp supported by HDMI2.1 sink
	 * Section 7.7.34 : Source shall not enable compressed Video
	 * Transport with bpp_target settings above 12 bpp unless
	 * DSC_all_bpp is set to 1.
	 */
	अगर (!hdmi_all_bpp)
		max_dsc_bpp = min(max_dsc_bpp, 12);

	/*
	 * The Sink has a limit of compressed data in bytes क्रम a scanline,
	 * as described in max_chunk_bytes field in HFVSDB block of edid.
	 * The no. of bytes depend on the target bits per pixel that the
	 * source configures. So we start with the max_bpp and calculate
	 * the target_chunk_bytes. We keep on decrementing the target_bpp,
	 * till we get the target_chunk_bytes just less than what the sink's
	 * max_chunk_bytes, or अन्यथा till we reach the min_dsc_bpp.
	 *
	 * The decrement is according to the fractional support from PCON DSC
	 * encoder. For fractional BPP we use bpp_target as a multiple of 16.
	 *
	 * bpp_target_x16 = bpp_target * 16
	 * So we need to decrement by अणु1, 2, 4, 8, 16पूर्ण क्रम fractional bpps
	 * अणु1/16, 1/8, 1/4, 1/2, 1पूर्ण respectively.
	 */

	bpp_target = max_dsc_bpp;

	/* src करोes not support fractional bpp implies decrement by 16 क्रम bppx16 */
	अगर (!src_fractional_bpp)
		src_fractional_bpp = 1;
	bpp_decrement_x16 = DIV_ROUND_UP(16, src_fractional_bpp);
	bpp_target_x16 = (bpp_target * 16) - bpp_decrement_x16;

	जबतक (bpp_target_x16 > (min_dsc_bpp * 16)) अणु
		पूर्णांक bpp;

		bpp = DIV_ROUND_UP(bpp_target_x16, 16);
		target_bytes = DIV_ROUND_UP((num_slices * slice_width * bpp), 8);
		अगर (target_bytes <= hdmi_max_chunk_bytes) अणु
			bpp_found = true;
			अवरोध;
		पूर्ण
		bpp_target_x16 -= bpp_decrement_x16;
	पूर्ण
	अगर (bpp_found)
		वापस bpp_target_x16;

	वापस 0;
पूर्ण
