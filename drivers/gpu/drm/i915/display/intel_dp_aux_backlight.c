<शैली गुरु>
/*
 * Copyright तऊ 2015 Intel Corporation
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
 */

/*
 * Laptops with Intel GPUs which have panels that support controlling the
 * backlight through DP AUX can actually use two dअगरferent पूर्णांकerfaces: Intel's
 * proprietary DP AUX backlight पूर्णांकerface, and the standard VESA backlight
 * पूर्णांकerface. Unक्रमtunately, at the समय of writing this a lot of laptops will
 * advertise support क्रम the standard VESA backlight पूर्णांकerface when they
 * करोn't properly support it. However, on these प्रणालीs the Intel backlight
 * पूर्णांकerface generally करोes work properly. Additionally, these प्रणालीs will
 * usually just indicate that they use PWM backlight controls in their VBIOS
 * क्रम some reason.
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dp_aux_backlight.h"
#समावेश "intel_panel.h"

/* TODO:
 * Implement HDR, right now we just implement the bare minimum to bring us back पूर्णांकo SDR mode so we
 * can make people's backlights work in the mean समय
 */

/*
 * DP AUX रेजिस्टरs क्रम Intel's proprietary HDR backlight पूर्णांकerface. We define
 * them here since we'll likely be the only driver to ever use these.
 */
#घोषणा INTEL_EDP_HDR_TCON_CAP0                                        0x340

#घोषणा INTEL_EDP_HDR_TCON_CAP1                                        0x341
# define INTEL_EDP_HDR_TCON_2084_DECODE_CAP                           BIT(0)
# define INTEL_EDP_HDR_TCON_2020_GAMUT_CAP                            BIT(1)
# define INTEL_EDP_HDR_TCON_TONE_MAPPING_CAP                          BIT(2)
# define INTEL_EDP_HDR_TCON_SEGMENTED_BACKLIGHT_CAP                   BIT(3)
# define INTEL_EDP_HDR_TCON_BRIGHTNESS_NITS_CAP                       BIT(4)
# define INTEL_EDP_HDR_TCON_OPTIMIZATION_CAP                          BIT(5)
# define INTEL_EDP_HDR_TCON_SDP_COLORIMETRY_CAP                       BIT(6)
# define INTEL_EDP_HDR_TCON_SRGB_TO_PANEL_GAMUT_CONVERSION_CAP        BIT(7)

#घोषणा INTEL_EDP_HDR_TCON_CAP2                                        0x342
# define INTEL_EDP_SDR_TCON_BRIGHTNESS_AUX_CAP                        BIT(0)

#घोषणा INTEL_EDP_HDR_TCON_CAP3                                        0x343

#घोषणा INTEL_EDP_HDR_GETSET_CTRL_PARAMS                               0x344
# define INTEL_EDP_HDR_TCON_2084_DECODE_ENABLE                        BIT(0)
# define INTEL_EDP_HDR_TCON_2020_GAMUT_ENABLE                         BIT(1)
# define INTEL_EDP_HDR_TCON_TONE_MAPPING_ENABLE                       BIT(2) /* Pre-TGL+ */
# define INTEL_EDP_HDR_TCON_SEGMENTED_BACKLIGHT_ENABLE                BIT(3)
# define INTEL_EDP_HDR_TCON_BRIGHTNESS_AUX_ENABLE                     BIT(4)
# define INTEL_EDP_HDR_TCON_SRGB_TO_PANEL_GAMUT_ENABLE                BIT(5)
/* Bit 6 is reserved */
# define INTEL_EDP_HDR_TCON_SDP_COLORIMETRY_ENABLE                    BIT(7)

#घोषणा INTEL_EDP_HDR_CONTENT_LUMIन_अंकCE                                0x346 /* Pre-TGL+ */
#घोषणा INTEL_EDP_HDR_PANEL_LUMIन_अंकCE_OVERRIDE                         0x34A
#घोषणा INTEL_EDP_SDR_LUMIन_अंकCE_LEVEL                                  0x352
#घोषणा INTEL_EDP_BRIGHTNESS_NITS_LSB                                  0x354
#घोषणा INTEL_EDP_BRIGHTNESS_NITS_MSB                                  0x355
#घोषणा INTEL_EDP_BRIGHTNESS_DELAY_FRAMES                              0x356
#घोषणा INTEL_EDP_BRIGHTNESS_PER_FRAME_STEPS                           0x357

#घोषणा INTEL_EDP_BRIGHTNESS_OPTIMIZATION_0                            0x358
# define INTEL_EDP_TCON_USAGE_MASK                             GENMASK(0, 3)
# define INTEL_EDP_TCON_USAGE_UNKNOWN                                    0x0
# define INTEL_EDP_TCON_USAGE_DESKTOP                                    0x1
# define INTEL_EDP_TCON_USAGE_FULL_SCREEN_MEDIA                          0x2
# define INTEL_EDP_TCON_USAGE_FULL_SCREEN_GAMING                         0x3
# define INTEL_EDP_TCON_POWER_MASK                                    BIT(4)
# define INTEL_EDP_TCON_POWER_DC                                    (0 << 4)
# define INTEL_EDP_TCON_POWER_AC                                    (1 << 4)
# define INTEL_EDP_TCON_OPTIMIZATION_STRENGTH_MASK             GENMASK(5, 7)

#घोषणा INTEL_EDP_BRIGHTNESS_OPTIMIZATION_1                            0x359

/* Intel EDP backlight callbacks */
अटल bool
पूर्णांकel_dp_aux_supports_hdr_backlight(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(connector->encoder);
	काष्ठा drm_dp_aux *aux = &पूर्णांकel_dp->aux;
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	पूर्णांक ret;
	u8 tcon_cap[4];

	ret = drm_dp_dpcd_पढ़ो(aux, INTEL_EDP_HDR_TCON_CAP0, tcon_cap, माप(tcon_cap));
	अगर (ret < 0)
		वापस false;

	अगर (!(tcon_cap[1] & INTEL_EDP_HDR_TCON_BRIGHTNESS_NITS_CAP))
		वापस false;

	अगर (tcon_cap[0] >= 1) अणु
		drm_dbg_kms(&i915->drm, "Detected Intel HDR backlight interface version %d\n",
			    tcon_cap[0]);
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&i915->drm, "Detected unsupported HDR backlight interface version %d\n",
			    tcon_cap[0]);
		वापस false;
	पूर्ण

	panel->backlight.edp.पूर्णांकel.sdr_uses_aux =
		tcon_cap[2] & INTEL_EDP_SDR_TCON_BRIGHTNESS_AUX_CAP;

	वापस true;
पूर्ण

अटल u32
पूर्णांकel_dp_aux_hdr_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(connector->encoder);
	u8 पंचांगp;
	u8 buf[2] = अणु 0 पूर्ण;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, INTEL_EDP_HDR_GETSET_CTRL_PARAMS, &पंचांगp) < 0) अणु
		drm_err(&i915->drm, "Failed to read current backlight mode from DPCD\n");
		वापस 0;
	पूर्ण

	अगर (!(पंचांगp & INTEL_EDP_HDR_TCON_BRIGHTNESS_AUX_ENABLE)) अणु
		अगर (!panel->backlight.edp.पूर्णांकel.sdr_uses_aux) अणु
			u32 pwm_level = panel->backlight.pwm_funcs->get(connector, pipe);

			वापस पूर्णांकel_panel_backlight_level_from_pwm(connector, pwm_level);
		पूर्ण

		/* Assume 100% brightness अगर backlight controls aren't enabled yet */
		वापस panel->backlight.max;
	पूर्ण

	अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, INTEL_EDP_BRIGHTNESS_NITS_LSB, buf, माप(buf)) < 0) अणु
		drm_err(&i915->drm, "Failed to read brightness from DPCD\n");
		वापस 0;
	पूर्ण

	वापस (buf[1] << 8 | buf[0]);
पूर्ण

अटल व्योम
पूर्णांकel_dp_aux_hdr_set_aux_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(connector->encoder);
	u8 buf[4] = अणु 0 पूर्ण;

	buf[0] = level & 0xFF;
	buf[1] = (level & 0xFF00) >> 8;

	अगर (drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, INTEL_EDP_BRIGHTNESS_NITS_LSB, buf, 4) < 0)
		drm_err(dev, "Failed to write brightness level to DPCD\n");
पूर्ण

अटल व्योम
पूर्णांकel_dp_aux_hdr_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	अगर (panel->backlight.edp.पूर्णांकel.sdr_uses_aux) अणु
		पूर्णांकel_dp_aux_hdr_set_aux_backlight(conn_state, level);
	पूर्ण अन्यथा अणु
		स्थिर u32 pwm_level = पूर्णांकel_panel_backlight_level_to_pwm(connector, level);

		पूर्णांकel_panel_set_pwm_level(conn_state, pwm_level);
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_dp_aux_hdr_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(connector->encoder);
	पूर्णांक ret;
	u8 old_ctrl, ctrl;

	ret = drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, INTEL_EDP_HDR_GETSET_CTRL_PARAMS, &old_ctrl);
	अगर (ret < 0) अणु
		drm_err(&i915->drm, "Failed to read current backlight control mode: %d\n", ret);
		वापस;
	पूर्ण

	ctrl = old_ctrl;
	अगर (panel->backlight.edp.पूर्णांकel.sdr_uses_aux) अणु
		ctrl |= INTEL_EDP_HDR_TCON_BRIGHTNESS_AUX_ENABLE;
		पूर्णांकel_dp_aux_hdr_set_aux_backlight(conn_state, level);
	पूर्ण अन्यथा अणु
		u32 pwm_level = पूर्णांकel_panel_backlight_level_to_pwm(connector, level);

		panel->backlight.pwm_funcs->enable(crtc_state, conn_state, pwm_level);

		ctrl &= ~INTEL_EDP_HDR_TCON_BRIGHTNESS_AUX_ENABLE;
	पूर्ण

	अगर (ctrl != old_ctrl)
		अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, INTEL_EDP_HDR_GETSET_CTRL_PARAMS, ctrl) < 0)
			drm_err(&i915->drm, "Failed to configure DPCD brightness controls\n");
पूर्ण

अटल व्योम
पूर्णांकel_dp_aux_hdr_disable_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	/* Nothing to करो क्रम AUX based backlight controls */
	अगर (panel->backlight.edp.पूर्णांकel.sdr_uses_aux)
		वापस;

	/* Note we want the actual pwm_level to be 0, regardless of pwm_min */
	panel->backlight.pwm_funcs->disable(conn_state, पूर्णांकel_panel_invert_pwm_level(connector, 0));
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_aux_hdr_setup_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe pipe)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	पूर्णांक ret;

	अगर (panel->backlight.edp.पूर्णांकel.sdr_uses_aux) अणु
		drm_dbg_kms(&i915->drm, "SDR backlight is controlled through DPCD\n");
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&i915->drm, "SDR backlight is controlled through PWM\n");

		ret = panel->backlight.pwm_funcs->setup(connector, pipe);
		अगर (ret < 0) अणु
			drm_err(&i915->drm,
				"Failed to setup SDR backlight controls through PWM: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	panel->backlight.max = 512;
	panel->backlight.min = 0;
	panel->backlight.level = पूर्णांकel_dp_aux_hdr_get_backlight(connector, pipe);
	panel->backlight.enabled = panel->backlight.level != 0;

	वापस 0;
पूर्ण

/* VESA backlight callbacks */
अटल व्योम set_vesa_backlight_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool enable)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 reg_val = 0;

	/* Early वापस when display use other mechanism to enable backlight. */
	अगर (!(पूर्णांकel_dp->edp_dpcd[1] & DP_EDP_BACKLIGHT_AUX_ENABLE_CAP))
		वापस;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_EDP_DISPLAY_CONTROL_REGISTER,
			      &reg_val) < 0) अणु
		drm_dbg_kms(&i915->drm, "Failed to read DPCD register 0x%x\n",
			    DP_EDP_DISPLAY_CONTROL_REGISTER);
		वापस;
	पूर्ण
	अगर (enable)
		reg_val |= DP_EDP_BACKLIGHT_ENABLE;
	अन्यथा
		reg_val &= ~(DP_EDP_BACKLIGHT_ENABLE);

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_EDP_DISPLAY_CONTROL_REGISTER,
			       reg_val) != 1) अणु
		drm_dbg_kms(&i915->drm, "Failed to %s aux backlight\n",
			    enable ? "enable" : "disable");
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_dp_aux_vesa_backlight_dpcd_mode(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 mode_reg;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_EDP_BACKLIGHT_MODE_SET_REGISTER,
			      &mode_reg) != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to read the DPCD register 0x%x\n",
			    DP_EDP_BACKLIGHT_MODE_SET_REGISTER);
		वापस false;
	पूर्ण

	वापस (mode_reg & DP_EDP_BACKLIGHT_CONTROL_MODE_MASK) ==
	       DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD;
पूर्ण

/*
 * Read the current backlight value from DPCD रेजिस्टर(s) based
 * on अगर 8-bit(MSB) or 16-bit(MSB and LSB) values are supported
 */
अटल u32 पूर्णांकel_dp_aux_vesa_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 पढ़ो_val[2] = अणु 0x0 पूर्ण;
	u16 level = 0;

	/*
	 * If we're not in DPCD control mode yet, the programmed brightness
	 * value is meaningless and we should assume max brightness
	 */
	अगर (!पूर्णांकel_dp_aux_vesa_backlight_dpcd_mode(connector))
		वापस connector->panel.backlight.max;

	अगर (drm_dp_dpcd_पढ़ो(&पूर्णांकel_dp->aux, DP_EDP_BACKLIGHT_BRIGHTNESS_MSB,
			     &पढ़ो_val, माप(पढ़ो_val)) < 0) अणु
		drm_dbg_kms(&i915->drm, "Failed to read DPCD register 0x%x\n",
			    DP_EDP_BACKLIGHT_BRIGHTNESS_MSB);
		वापस 0;
	पूर्ण
	level = पढ़ो_val[0];
	अगर (पूर्णांकel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_BYTE_COUNT)
		level = (पढ़ो_val[0] << 8 | पढ़ो_val[1]);

	वापस level;
पूर्ण

/*
 * Sends the current backlight level over the aux channel, checking अगर its using
 * 8-bit or 16 bit value (MSB and LSB)
 */
अटल व्योम
पूर्णांकel_dp_aux_vesa_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state,
				u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 vals[2] = अणु 0x0 पूर्ण;

	vals[0] = level;

	/* Write the MSB and/or LSB */
	अगर (पूर्णांकel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_BYTE_COUNT) अणु
		vals[0] = (level & 0xFF00) >> 8;
		vals[1] = (level & 0xFF);
	पूर्ण
	अगर (drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_EDP_BACKLIGHT_BRIGHTNESS_MSB,
			      vals, माप(vals)) < 0) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to write aux backlight level\n");
		वापस;
	पूर्ण
पूर्ण

/*
 * Set PWM Frequency भागider to match desired frequency in vbt.
 * The PWM Frequency is calculated as 27Mhz / (F x P).
 * - Where F = PWM Frequency Pre-Divider value programmed by field 7:0 of the
 *             EDP_BACKLIGHT_FREQ_SET रेजिस्टर (DPCD Address 00728h)
 * - Where P = 2^Pn, where Pn is the value programmed by field 4:0 of the
 *             EDP_PWMGEN_BIT_COUNT रेजिस्टर (DPCD Address 00724h)
 */
अटल bool पूर्णांकel_dp_aux_vesa_set_pwm_freq(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	स्थिर u8 pn = connector->panel.backlight.edp.vesa.pwmgen_bit_count;
	पूर्णांक freq, fxp, f, fxp_actual, fxp_min, fxp_max;

	freq = dev_priv->vbt.backlight.pwm_freq_hz;
	अगर (!freq) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Use panel default backlight frequency\n");
		वापस false;
	पूर्ण

	fxp = DIV_ROUND_CLOSEST(KHz(DP_EDP_BACKLIGHT_FREQ_BASE_KHZ), freq);
	f = clamp(DIV_ROUND_CLOSEST(fxp, 1 << pn), 1, 255);
	fxp_actual = f << pn;

	/* Ensure frequency is within 25% of desired value */
	fxp_min = DIV_ROUND_CLOSEST(fxp * 3, 4);
	fxp_max = DIV_ROUND_CLOSEST(fxp * 5, 4);

	अगर (fxp_min > fxp_actual || fxp_actual > fxp_max) अणु
		drm_dbg_kms(&dev_priv->drm, "Actual frequency out of range\n");
		वापस false;
	पूर्ण

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			       DP_EDP_BACKLIGHT_FREQ_SET, (u8) f) < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Failed to write aux backlight freq\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम
पूर्णांकel_dp_aux_vesa_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u8 dpcd_buf, new_dpcd_buf, edp_backlight_mode;
	u8 pwmgen_bit_count = panel->backlight.edp.vesa.pwmgen_bit_count;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			DP_EDP_BACKLIGHT_MODE_SET_REGISTER, &dpcd_buf) != 1) अणु
		drm_dbg_kms(&i915->drm, "Failed to read DPCD register 0x%x\n",
			    DP_EDP_BACKLIGHT_MODE_SET_REGISTER);
		वापस;
	पूर्ण

	new_dpcd_buf = dpcd_buf;
	edp_backlight_mode = dpcd_buf & DP_EDP_BACKLIGHT_CONTROL_MODE_MASK;

	चयन (edp_backlight_mode) अणु
	हाल DP_EDP_BACKLIGHT_CONTROL_MODE_PWM:
	हाल DP_EDP_BACKLIGHT_CONTROL_MODE_PRESET:
	हाल DP_EDP_BACKLIGHT_CONTROL_MODE_PRODUCT:
		new_dpcd_buf &= ~DP_EDP_BACKLIGHT_CONTROL_MODE_MASK;
		new_dpcd_buf |= DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD;

		अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
				       DP_EDP_PWMGEN_BIT_COUNT,
				       pwmgen_bit_count) < 0)
			drm_dbg_kms(&i915->drm,
				    "Failed to write aux pwmgen bit count\n");

		अवरोध;

	/* Do nothing when it is alपढ़ोy DPCD mode */
	हाल DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD:
	शेष:
		अवरोध;
	पूर्ण

	अगर (पूर्णांकel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_FREQ_AUX_SET_CAP)
		अगर (पूर्णांकel_dp_aux_vesa_set_pwm_freq(connector))
			new_dpcd_buf |= DP_EDP_BACKLIGHT_FREQ_AUX_SET_ENABLE;

	अगर (new_dpcd_buf != dpcd_buf) अणु
		अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			DP_EDP_BACKLIGHT_MODE_SET_REGISTER, new_dpcd_buf) < 0) अणु
			drm_dbg_kms(&i915->drm,
				    "Failed to write aux backlight mode\n");
		पूर्ण
	पूर्ण

	पूर्णांकel_dp_aux_vesa_set_backlight(conn_state, level);
	set_vesa_backlight_enable(पूर्णांकel_dp, true);
पूर्ण

अटल व्योम पूर्णांकel_dp_aux_vesa_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state,
						u32 level)
अणु
	set_vesa_backlight_enable(enc_to_पूर्णांकel_dp(to_पूर्णांकel_encoder(old_conn_state->best_encoder)),
				  false);
पूर्ण

अटल u32 पूर्णांकel_dp_aux_vesa_calc_max_backlight(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	u32 max_backlight = 0;
	पूर्णांक freq, fxp, fxp_min, fxp_max, fxp_actual, f = 1;
	u8 pn, pn_min, pn_max;

	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux, DP_EDP_PWMGEN_BIT_COUNT, &pn) == 1) अणु
		pn &= DP_EDP_PWMGEN_BIT_COUNT_MASK;
		max_backlight = (1 << pn) - 1;
	पूर्ण

	/* Find desired value of (F x P)
	 * Note that, अगर F x P is out of supported range, the maximum value or
	 * minimum value will applied स्वतःmatically. So no need to check that.
	 */
	freq = i915->vbt.backlight.pwm_freq_hz;
	drm_dbg_kms(&i915->drm, "VBT defined backlight frequency %u Hz\n",
		    freq);
	अगर (!freq) अणु
		drm_dbg_kms(&i915->drm,
			    "Use panel default backlight frequency\n");
		वापस max_backlight;
	पूर्ण

	fxp = DIV_ROUND_CLOSEST(KHz(DP_EDP_BACKLIGHT_FREQ_BASE_KHZ), freq);

	/* Use highest possible value of Pn क्रम more granularity of brightness
	 * adjusपंचांगent जबतक satअगरying the conditions below.
	 * - Pn is in the range of Pn_min and Pn_max
	 * - F is in the range of 1 and 255
	 * - FxP is within 25% of desired value.
	 *   Note: 25% is arbitrary value and may need some tweak.
	 */
	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_EDP_PWMGEN_BIT_COUNT_CAP_MIN, &pn_min) != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to read pwmgen bit count cap min\n");
		वापस max_backlight;
	पूर्ण
	अगर (drm_dp_dpcd_पढ़ोb(&पूर्णांकel_dp->aux,
			      DP_EDP_PWMGEN_BIT_COUNT_CAP_MAX, &pn_max) != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to read pwmgen bit count cap max\n");
		वापस max_backlight;
	पूर्ण
	pn_min &= DP_EDP_PWMGEN_BIT_COUNT_MASK;
	pn_max &= DP_EDP_PWMGEN_BIT_COUNT_MASK;

	fxp_min = DIV_ROUND_CLOSEST(fxp * 3, 4);
	fxp_max = DIV_ROUND_CLOSEST(fxp * 5, 4);
	अगर (fxp_min < (1 << pn_min) || (255 << pn_max) < fxp_max) अणु
		drm_dbg_kms(&i915->drm,
			    "VBT defined backlight frequency out of range\n");
		वापस max_backlight;
	पूर्ण

	क्रम (pn = pn_max; pn >= pn_min; pn--) अणु
		f = clamp(DIV_ROUND_CLOSEST(fxp, 1 << pn), 1, 255);
		fxp_actual = f << pn;
		अगर (fxp_min <= fxp_actual && fxp_actual <= fxp_max)
			अवरोध;
	पूर्ण

	drm_dbg_kms(&i915->drm, "Using eDP pwmgen bit count of %d\n", pn);
	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux,
			       DP_EDP_PWMGEN_BIT_COUNT, pn) < 0) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to write aux pwmgen bit count\n");
		वापस max_backlight;
	पूर्ण
	panel->backlight.edp.vesa.pwmgen_bit_count = pn;

	max_backlight = (1 << pn) - 1;

	वापस max_backlight;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_aux_vesa_setup_backlight(काष्ठा पूर्णांकel_connector *connector,
					     क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.max = पूर्णांकel_dp_aux_vesa_calc_max_backlight(connector);
	अगर (!panel->backlight.max)
		वापस -ENODEV;

	panel->backlight.min = 0;
	panel->backlight.level = पूर्णांकel_dp_aux_vesa_get_backlight(connector, pipe);
	panel->backlight.enabled = पूर्णांकel_dp_aux_vesa_backlight_dpcd_mode(connector) &&
				   panel->backlight.level != 0;

	वापस 0;
पूर्ण

अटल bool
पूर्णांकel_dp_aux_supports_vesa_backlight(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	/* Check the eDP Display control capabilities रेजिस्टरs to determine अगर
	 * the panel can support backlight control over the aux channel.
	 *
	 * TODO: We currently only support AUX only backlight configurations, not backlights which
	 * require a mix of PWM and AUX controls to work. In the mean समय, these machines typically
	 * work just fine using normal PWM controls anyway.
	 */
	अगर (पूर्णांकel_dp->edp_dpcd[1] & DP_EDP_TCON_BACKLIGHT_ADJUSTMENT_CAP &&
	    (पूर्णांकel_dp->edp_dpcd[1] & DP_EDP_BACKLIGHT_AUX_ENABLE_CAP) &&
	    (पूर्णांकel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_AUX_SET_CAP)) अणु
		drm_dbg_kms(&i915->drm, "AUX Backlight Control Supported!\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs पूर्णांकel_dp_hdr_bl_funcs = अणु
	.setup = पूर्णांकel_dp_aux_hdr_setup_backlight,
	.enable = पूर्णांकel_dp_aux_hdr_enable_backlight,
	.disable = पूर्णांकel_dp_aux_hdr_disable_backlight,
	.set = पूर्णांकel_dp_aux_hdr_set_backlight,
	.get = पूर्णांकel_dp_aux_hdr_get_backlight,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs पूर्णांकel_dp_vesa_bl_funcs = अणु
	.setup = पूर्णांकel_dp_aux_vesa_setup_backlight,
	.enable = पूर्णांकel_dp_aux_vesa_enable_backlight,
	.disable = पूर्णांकel_dp_aux_vesa_disable_backlight,
	.set = पूर्णांकel_dp_aux_vesa_set_backlight,
	.get = पूर्णांकel_dp_aux_vesa_get_backlight,
पूर्ण;

क्रमागत पूर्णांकel_dp_aux_backlight_modparam अणु
	INTEL_DP_AUX_BACKLIGHT_AUTO = -1,
	INTEL_DP_AUX_BACKLIGHT_OFF = 0,
	INTEL_DP_AUX_BACKLIGHT_ON = 1,
	INTEL_DP_AUX_BACKLIGHT_FORCE_VESA = 2,
	INTEL_DP_AUX_BACKLIGHT_FORCE_INTEL = 3,
पूर्ण;

पूर्णांक पूर्णांकel_dp_aux_init_backlight_funcs(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(connector->encoder);
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	bool try_पूर्णांकel_पूर्णांकerface = false, try_vesa_पूर्णांकerface = false;

	/* Check the VBT and user's module parameters to figure out which
	 * पूर्णांकerfaces to probe
	 */
	चयन (i915->params.enable_dpcd_backlight) अणु
	हाल INTEL_DP_AUX_BACKLIGHT_OFF:
		वापस -ENODEV;
	हाल INTEL_DP_AUX_BACKLIGHT_AUTO:
		चयन (i915->vbt.backlight.type) अणु
		हाल INTEL_BACKLIGHT_VESA_EDP_AUX_INTERFACE:
			try_vesa_पूर्णांकerface = true;
			अवरोध;
		हाल INTEL_BACKLIGHT_DISPLAY_DDI:
			try_पूर्णांकel_पूर्णांकerface = true;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	हाल INTEL_DP_AUX_BACKLIGHT_ON:
		अगर (i915->vbt.backlight.type != INTEL_BACKLIGHT_VESA_EDP_AUX_INTERFACE)
			try_पूर्णांकel_पूर्णांकerface = true;

		try_vesa_पूर्णांकerface = true;
		अवरोध;
	हाल INTEL_DP_AUX_BACKLIGHT_FORCE_VESA:
		try_vesa_पूर्णांकerface = true;
		अवरोध;
	हाल INTEL_DP_AUX_BACKLIGHT_FORCE_INTEL:
		try_पूर्णांकel_पूर्णांकerface = true;
		अवरोध;
	पूर्ण

	/*
	 * A lot of eDP panels in the wild will report supporting both the
	 * Intel proprietary backlight control पूर्णांकerface, and the VESA
	 * backlight control पूर्णांकerface. Many of these panels are liars though,
	 * and will only work with the Intel पूर्णांकerface. So, always probe क्रम
	 * that first.
	 */
	अगर (try_पूर्णांकel_पूर्णांकerface && पूर्णांकel_dp_aux_supports_hdr_backlight(connector)) अणु
		drm_dbg_kms(dev, "Using Intel proprietary eDP backlight controls\n");
		panel->backlight.funcs = &पूर्णांकel_dp_hdr_bl_funcs;
		वापस 0;
	पूर्ण

	अगर (try_vesa_पूर्णांकerface && पूर्णांकel_dp_aux_supports_vesa_backlight(connector)) अणु
		drm_dbg_kms(dev, "Using VESA eDP backlight controls\n");
		panel->backlight.funcs = &पूर्णांकel_dp_vesa_bl_funcs;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण
