<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung LSI S5C73M3 8M pixel camera driver
 *
 * Copyright (C) 2012, Samsung Electronics, Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#समावेश <linux/sizes.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/videodev2.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/i2c/s5c73m3.h>

#समावेश "s5c73m3.h"

अटल पूर्णांक s5c73m3_get_af_status(काष्ठा s5c73m3 *state, काष्ठा v4l2_ctrl *ctrl)
अणु
	u16 reg = REG_AF_STATUS_UNFOCUSED;

	पूर्णांक ret = s5c73m3_पढ़ो(state, REG_AF_STATUS, &reg);

	चयन (reg) अणु
	हाल REG_CAF_STATUS_FIND_SEARCH_सूची:
	हाल REG_AF_STATUS_FOCUSING:
	हाल REG_CAF_STATUS_FOCUSING:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_BUSY;
		अवरोध;
	हाल REG_CAF_STATUS_FOCUSED:
	हाल REG_AF_STATUS_FOCUSED:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_REACHED;
		अवरोध;
	शेष:
		v4l2_info(&state->sensor_sd, "Unknown AF status %#x\n", reg);
		fallthrough;
	हाल REG_CAF_STATUS_UNFOCUSED:
	हाल REG_AF_STATUS_UNFOCUSED:
	हाल REG_AF_STATUS_INVALID:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_FAILED;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sensor_sd(ctrl);
	काष्ठा s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	पूर्णांक ret;

	अगर (state->घातer == 0)
		वापस -EBUSY;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_FOCUS_AUTO:
		ret = s5c73m3_get_af_status(state, state->ctrls.af_status);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5c73m3_set_colorfx(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	अटल स्थिर अचिन्हित लघु colorfx[][2] = अणु
		अणु V4L2_COLORFX_NONE,	 COMM_IMAGE_EFFECT_NONE पूर्ण,
		अणु V4L2_COLORFX_BW,	 COMM_IMAGE_EFFECT_MONO पूर्ण,
		अणु V4L2_COLORFX_SEPIA,	 COMM_IMAGE_EFFECT_SEPIA पूर्ण,
		अणु V4L2_COLORFX_NEGATIVE, COMM_IMAGE_EFFECT_NEGATIVE पूर्ण,
		अणु V4L2_COLORFX_AQUA,	 COMM_IMAGE_EFFECT_AQUA पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(colorfx); i++) अणु
		अगर (colorfx[i][0] != val)
			जारी;

		v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
			 "Setting %s color effect\n",
			 v4l2_ctrl_get_menu(state->ctrls.colorfx->id)[i]);

		वापस s5c73m3_isp_command(state, COMM_IMAGE_EFFECT,
					 colorfx[i][1]);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Set exposure metering/exposure bias */
अटल पूर्णांक s5c73m3_set_exposure(काष्ठा s5c73m3 *state, पूर्णांक स्वतः_exp)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;
	काष्ठा s5c73m3_ctrls *ctrls = &state->ctrls;
	पूर्णांक ret = 0;

	अगर (ctrls->exposure_metering->is_new) अणु
		u16 metering;

		चयन (ctrls->exposure_metering->val) अणु
		हाल V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
			metering = COMM_METERING_CENTER;
			अवरोध;
		हाल V4L2_EXPOSURE_METERING_SPOT:
			metering = COMM_METERING_SPOT;
			अवरोध;
		शेष:
			metering = COMM_METERING_AVERAGE;
			अवरोध;
		पूर्ण

		ret = s5c73m3_isp_command(state, COMM_METERING, metering);
	पूर्ण

	अगर (!ret && ctrls->exposure_bias->is_new) अणु
		u16 exp_bias = ctrls->exposure_bias->val;
		ret = s5c73m3_isp_command(state, COMM_EV, exp_bias);
	पूर्ण

	v4l2_dbg(1, s5c73m3_dbg, sd,
		 "%s: exposure bias: %#x, metering: %#x (%d)\n",  __func__,
		 ctrls->exposure_bias->val, ctrls->exposure_metering->val, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_set_white_balance(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	अटल स्थिर अचिन्हित लघु wb[][2] = अणु
		अणु V4L2_WHITE_BALANCE_INCANDESCENT,  COMM_AWB_MODE_INCANDESCENTपूर्ण,
		अणु V4L2_WHITE_BALANCE_FLUORESCENT,   COMM_AWB_MODE_FLUORESCENT1पूर्ण,
		अणु V4L2_WHITE_BALANCE_FLUORESCENT_H, COMM_AWB_MODE_FLUORESCENT2पूर्ण,
		अणु V4L2_WHITE_BALANCE_CLOUDY,        COMM_AWB_MODE_CLOUDYपूर्ण,
		अणु V4L2_WHITE_BALANCE_DAYLIGHT,      COMM_AWB_MODE_DAYLIGHTपूर्ण,
		अणु V4L2_WHITE_BALANCE_AUTO,          COMM_AWB_MODE_AUTOपूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wb); i++) अणु
		अगर (wb[i][0] != val)
			जारी;

		v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd,
			 "Setting white balance to: %s\n",
			 v4l2_ctrl_get_menu(state->ctrls.स्वतः_wb->id)[i]);

		वापस s5c73m3_isp_command(state, COMM_AWB_MODE, wb[i][1]);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5c73m3_af_run(काष्ठा s5c73m3 *state, bool on)
अणु
	काष्ठा s5c73m3_ctrls *c = &state->ctrls;

	अगर (!on)
		वापस s5c73m3_isp_command(state, COMM_AF_CON,
							COMM_AF_CON_STOP);

	अगर (c->focus_स्वतः->val)
		वापस s5c73m3_isp_command(state, COMM_AF_MODE,
					   COMM_AF_MODE_PREVIEW_CAF_START);

	वापस s5c73m3_isp_command(state, COMM_AF_CON, COMM_AF_CON_START);
पूर्ण

अटल पूर्णांक s5c73m3_3a_lock(काष्ठा s5c73m3 *state, काष्ठा v4l2_ctrl *ctrl)
अणु
	bool awb_lock = ctrl->val & V4L2_LOCK_WHITE_BALANCE;
	bool ae_lock = ctrl->val & V4L2_LOCK_EXPOSURE;
	bool af_lock = ctrl->val & V4L2_LOCK_FOCUS;
	पूर्णांक ret = 0;

	अगर ((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_EXPOSURE) अणु
		ret = s5c73m3_isp_command(state, COMM_AE_CON,
				ae_lock ? COMM_AE_STOP : COMM_AE_START);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_WHITE_BALANCE)
	    && state->ctrls.स्वतः_wb->val) अणु
		ret = s5c73m3_isp_command(state, COMM_AWB_CON,
			awb_lock ? COMM_AWB_STOP : COMM_AWB_START);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_FOCUS)
		ret = s5c73m3_af_run(state, !af_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_set_स्वतः_focus(काष्ठा s5c73m3 *state, पूर्णांक caf)
अणु
	काष्ठा s5c73m3_ctrls *c = &state->ctrls;
	पूर्णांक ret = 1;

	अगर (c->af_distance->is_new) अणु
		u16 mode = (c->af_distance->val == V4L2_AUTO_FOCUS_RANGE_MACRO)
				? COMM_AF_MODE_MACRO : COMM_AF_MODE_NORMAL;
		ret = s5c73m3_isp_command(state, COMM_AF_MODE, mode);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (!ret || (c->focus_स्वतः->is_new && c->focus_स्वतः->val) ||
							c->af_start->is_new)
		ret = s5c73m3_af_run(state, 1);
	अन्यथा अगर ((c->focus_स्वतः->is_new && !c->focus_स्वतः->val) ||
							c->af_stop->is_new)
		ret = s5c73m3_af_run(state, 0);
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक s5c73m3_set_contrast(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	u16 reg = (val < 0) ? -val + 2 : val;
	वापस s5c73m3_isp_command(state, COMM_CONTRAST, reg);
पूर्ण

अटल पूर्णांक s5c73m3_set_saturation(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	u16 reg = (val < 0) ? -val + 2 : val;
	वापस s5c73m3_isp_command(state, COMM_SATURATION, reg);
पूर्ण

अटल पूर्णांक s5c73m3_set_sharpness(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	u16 reg = (val < 0) ? -val + 2 : val;
	वापस s5c73m3_isp_command(state, COMM_SHARPNESS, reg);
पूर्ण

अटल पूर्णांक s5c73m3_set_iso(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	u32 iso;

	अगर (val == V4L2_ISO_SENSITIVITY_MANUAL)
		iso = state->ctrls.iso->val + 1;
	अन्यथा
		iso = 0;

	वापस s5c73m3_isp_command(state, COMM_ISO, iso);
पूर्ण

अटल पूर्णांक s5c73m3_set_stabilization(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	काष्ठा v4l2_subdev *sd = &state->sensor_sd;

	v4l2_dbg(1, s5c73m3_dbg, sd, "Image stabilization: %d\n", val);

	वापस s5c73m3_isp_command(state, COMM_FRAME_RATE, val ?
			COMM_FRAME_RATE_ANTI_SHAKE : COMM_FRAME_RATE_AUTO_SET);
पूर्ण

अटल पूर्णांक s5c73m3_set_jpeg_quality(काष्ठा s5c73m3 *state, पूर्णांक quality)
अणु
	पूर्णांक reg;

	अगर (quality <= 65)
		reg = COMM_IMAGE_QUALITY_NORMAL;
	अन्यथा अगर (quality <= 75)
		reg = COMM_IMAGE_QUALITY_FINE;
	अन्यथा
		reg = COMM_IMAGE_QUALITY_SUPERFINE;

	वापस s5c73m3_isp_command(state, COMM_IMAGE_QUALITY, reg);
पूर्ण

अटल पूर्णांक s5c73m3_set_scene_program(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	अटल स्थिर अचिन्हित लघु scene_lookup[] = अणु
		COMM_SCENE_MODE_NONE,	     /* V4L2_SCENE_MODE_NONE */
		COMM_SCENE_MODE_AGAINST_LIGHT,/* V4L2_SCENE_MODE_BACKLIGHT */
		COMM_SCENE_MODE_BEACH,	     /* V4L2_SCENE_MODE_BEACH_SNOW */
		COMM_SCENE_MODE_CANDLE,	     /* V4L2_SCENE_MODE_CANDLE_LIGHT */
		COMM_SCENE_MODE_DAWN,	     /* V4L2_SCENE_MODE_DAWN_DUSK */
		COMM_SCENE_MODE_FALL,	     /* V4L2_SCENE_MODE_FALL_COLORS */
		COMM_SCENE_MODE_FIRE,	     /* V4L2_SCENE_MODE_FIREWORKS */
		COMM_SCENE_MODE_LANDSCAPE,    /* V4L2_SCENE_MODE_LANDSCAPE */
		COMM_SCENE_MODE_NIGHT,	     /* V4L2_SCENE_MODE_NIGHT */
		COMM_SCENE_MODE_INDOOR,	     /* V4L2_SCENE_MODE_PARTY_INDOOR */
		COMM_SCENE_MODE_PORTRAIT,     /* V4L2_SCENE_MODE_PORTRAIT */
		COMM_SCENE_MODE_SPORTS,	     /* V4L2_SCENE_MODE_SPORTS */
		COMM_SCENE_MODE_SUNSET,	     /* V4L2_SCENE_MODE_SUNSET */
		COMM_SCENE_MODE_TEXT,	     /* V4L2_SCENE_MODE_TEXT */
	पूर्ण;

	v4l2_dbg(1, s5c73m3_dbg, &state->sensor_sd, "Setting %s scene mode\n",
		 v4l2_ctrl_get_menu(state->ctrls.scene_mode->id)[val]);

	वापस s5c73m3_isp_command(state, COMM_SCENE_MODE, scene_lookup[val]);
पूर्ण

अटल पूर्णांक s5c73m3_set_घातer_line_freq(काष्ठा s5c73m3 *state, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक pwr_line_freq = COMM_FLICKER_NONE;

	चयन (val) अणु
	हाल V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		pwr_line_freq = COMM_FLICKER_NONE;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_50HZ;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_60HZ;
		अवरोध;
	शेष:
	हाल V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		pwr_line_freq = COMM_FLICKER_NONE;
	पूर्ण

	वापस s5c73m3_isp_command(state, COMM_FLICKER_MODE, pwr_line_freq);
पूर्ण

अटल पूर्णांक s5c73m3_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sensor_sd(ctrl);
	काष्ठा s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	पूर्णांक ret = 0;

	v4l2_dbg(1, s5c73m3_dbg, sd, "set_ctrl: %s, value: %d\n",
		 ctrl->name, ctrl->val);

	mutex_lock(&state->lock);
	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any controls to H/W at this समय. Instead
	 * the controls will be restored right after घातer-up.
	 */
	अगर (state->घातer == 0)
		जाओ unlock;

	अगर (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	चयन (ctrl->id) अणु
	हाल V4L2_CID_3A_LOCK:
		ret = s5c73m3_3a_lock(state, ctrl);
		अवरोध;

	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		ret = s5c73m3_set_white_balance(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		ret = s5c73m3_set_contrast(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_COLORFX:
		ret = s5c73m3_set_colorfx(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = s5c73m3_set_exposure(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_FOCUS_AUTO:
		ret = s5c73m3_set_स्वतः_focus(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_IMAGE_STABILIZATION:
		ret = s5c73m3_set_stabilization(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_ISO_SENSITIVITY:
		ret = s5c73m3_set_iso(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ret = s5c73m3_set_jpeg_quality(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		ret = s5c73m3_set_घातer_line_freq(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		ret = s5c73m3_set_saturation(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SCENE_MODE:
		ret = s5c73m3_set_scene_program(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		ret = s5c73m3_set_sharpness(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_WIDE_DYNAMIC_RANGE:
		ret = s5c73m3_isp_command(state, COMM_WDR, !!ctrl->val);
		अवरोध;

	हाल V4L2_CID_ZOOM_ABSOLUTE:
		ret = s5c73m3_isp_command(state, COMM_ZOOM_STEP, ctrl->val);
		अवरोध;
	पूर्ण
unlock:
	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5c73m3_ctrl_ops = अणु
	.g_अस्थिर_ctrl	= s5c73m3_g_अस्थिर_ctrl,
	.s_ctrl			= s5c73m3_s_ctrl,
पूर्ण;

/* Supported manual ISO values */
अटल स्थिर s64 iso_qmenu[] = अणु
	/* COMM_ISO: 0x0001...0x0004 */
	100, 200, 400, 800,
पूर्ण;

/* Supported exposure bias values (-2.0EV...+2.0EV) */
अटल स्थिर s64 ev_bias_qmenu[] = अणु
	/* COMM_EV: 0x0000...0x0008 */
	-2000, -1500, -1000, -500, 0, 500, 1000, 1500, 2000
पूर्ण;

पूर्णांक s5c73m3_init_controls(काष्ठा s5c73m3 *state)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &s5c73m3_ctrl_ops;
	काष्ठा s5c73m3_ctrls *ctrls = &state->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;

	पूर्णांक ret = v4l2_ctrl_handler_init(hdl, 22);
	अगर (ret)
		वापस ret;

	/* White balance */
	ctrls->स्वतः_wb = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
			9, ~0x15e, V4L2_WHITE_BALANCE_AUTO);

	/* Exposure (only स्वतःmatic exposure) */
	ctrls->स्वतः_exposure = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_EXPOSURE_AUTO, 0, ~0x01, V4L2_EXPOSURE_AUTO);

	ctrls->exposure_bias = v4l2_ctrl_new_पूर्णांक_menu(hdl, ops,
			V4L2_CID_AUTO_EXPOSURE_BIAS,
			ARRAY_SIZE(ev_bias_qmenu) - 1,
			ARRAY_SIZE(ev_bias_qmenu)/2 - 1,
			ev_bias_qmenu);

	ctrls->exposure_metering = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_EXPOSURE_METERING,
			2, ~0x7, V4L2_EXPOSURE_METERING_AVERAGE);

	/* Auto focus */
	ctrls->focus_स्वतः = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_FOCUS_AUTO, 0, 1, 1, 0);

	ctrls->af_start = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_START, 0, 1, 1, 0);

	ctrls->af_stop = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_STOP, 0, 1, 1, 0);

	ctrls->af_status = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_AUTO_FOCUS_STATUS, 0,
			(V4L2_AUTO_FOCUS_STATUS_BUSY |
			 V4L2_AUTO_FOCUS_STATUS_REACHED |
			 V4L2_AUTO_FOCUS_STATUS_FAILED),
			0, V4L2_AUTO_FOCUS_STATUS_IDLE);

	ctrls->af_distance = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_AUTO_FOCUS_RANGE,
			V4L2_AUTO_FOCUS_RANGE_MACRO,
			~(1 << V4L2_AUTO_FOCUS_RANGE_NORMAL |
			  1 << V4L2_AUTO_FOCUS_RANGE_MACRO),
			V4L2_AUTO_FOCUS_RANGE_NORMAL);
	/* ISO sensitivity */
	ctrls->स्वतः_iso = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_ISO_SENSITIVITY_AUTO, 1, 0,
			V4L2_ISO_SENSITIVITY_AUTO);

	ctrls->iso = v4l2_ctrl_new_पूर्णांक_menu(hdl, ops,
			V4L2_CID_ISO_SENSITIVITY, ARRAY_SIZE(iso_qmenu) - 1,
			ARRAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	ctrls->contrast = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_CONTRAST, -2, 2, 1, 0);

	ctrls->saturation = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_SATURATION, -2, 2, 1, 0);

	ctrls->sharpness = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_SHARPNESS, -2, 2, 1, 0);

	ctrls->zoom = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_ZOOM_ABSOLUTE, 0, 30, 1, 0);

	ctrls->colorfx = v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_COLORFX,
			V4L2_COLORFX_AQUA, ~0x40f, V4L2_COLORFX_NONE);

	ctrls->wdr = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_WIDE_DYNAMIC_RANGE, 0, 1, 1, 0);

	ctrls->stabilization = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_IMAGE_STABILIZATION, 0, 1, 1, 0);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_POWER_LINE_FREQUENCY,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO);

	ctrls->jpeg_quality = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY, 1, 100, 1, 80);

	ctrls->scene_mode = v4l2_ctrl_new_std_menu(hdl, ops,
			V4L2_CID_SCENE_MODE, V4L2_SCENE_MODE_TEXT, ~0x3fff,
			V4L2_SCENE_MODE_NONE);

	ctrls->aaa_lock = v4l2_ctrl_new_std(hdl, ops,
			V4L2_CID_3A_LOCK, 0, 0x7, 0, 0);

	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(3, &ctrls->स्वतः_exposure, 0, false);
	ctrls->स्वतः_iso->flags |= V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_UPDATE;
	v4l2_ctrl_स्वतः_cluster(2, &ctrls->स्वतः_iso, 0, false);
	ctrls->af_status->flags |= V4L2_CTRL_FLAG_VOLATILE;
	v4l2_ctrl_cluster(5, &ctrls->focus_स्वतः);

	state->sensor_sd.ctrl_handler = hdl;

	वापस 0;
पूर्ण
