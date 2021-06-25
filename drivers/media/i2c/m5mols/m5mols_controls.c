<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Controls क्रम M-5MOLS 8M Pixel camera sensor with ISP
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <करोngsoo45.kim@samsung.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "m5mols.h"
#समावेश "m5mols_reg.h"

अटल काष्ठा m5mols_scenemode m5mols_शेष_scenemode[] = अणु
	[REG_SCENE_NORMAL] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_NORMAL, REG_LIGHT_OFF, REG_FLASH_OFF,
		5, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_PORTRAIT] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 4,
		REG_AF_NORMAL, BIT_FD_EN | BIT_FD_DRAW_FACE_FRAME,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_LANDSCAPE] = अणु
		REG_AE_ALL, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 4, REG_EDGE_ON, 6,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_SPORTS] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_PARTY_INDOOR] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 4, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_200, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_BEACH_SNOW] = अणु
		REG_AE_CENTER, REG_AE_INDEX_10_POS, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 4, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_50, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_SUNSET] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_PRESET,
		REG_AWB_DAYLIGHT,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_DAWN_DUSK] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_PRESET,
		REG_AWB_FLUORESCENT_1,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_FALL] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 5, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_NIGHT] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_AGAINST_LIGHT] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_FIRE] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_50, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
	[REG_SCENE_TEXT] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 7,
		REG_AF_MACRO, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_ANTI_SHAKE, REG_WDR_ON,
	पूर्ण,
	[REG_SCENE_CANDLE] = अणु
		REG_AE_CENTER, REG_AE_INDEX_00, REG_AWB_AUTO, 0,
		REG_CHROMA_ON, 3, REG_EDGE_ON, 5,
		REG_AF_NORMAL, REG_FD_OFF,
		REG_MCC_OFF, REG_LIGHT_OFF, REG_FLASH_OFF,
		6, REG_ISO_AUTO, REG_CAP_NONE, REG_WDR_OFF,
	पूर्ण,
पूर्ण;

/**
 * m5mols_करो_scenemode() - Change current scenemode
 * @info: M-5MOLS driver data काष्ठाure
 * @mode:	Desired mode of the scenemode
 *
 * WARNING: The execution order is important. Do not change the order.
 */
पूर्णांक m5mols_करो_scenemode(काष्ठा m5mols_info *info, u8 mode)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	काष्ठा m5mols_scenemode scenemode = m5mols_शेष_scenemode[mode];
	पूर्णांक ret;

	अगर (mode > REG_SCENE_CANDLE)
		वापस -EINVAL;

	ret = v4l2_ctrl_s_ctrl(info->lock_3a, 0);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AE_EV_PRESET_MONITOR, mode);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AE_EV_PRESET_CAPTURE, mode);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AE_MODE, scenemode.metering);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AE_INDEX, scenemode.ev_bias);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AWB_MODE, scenemode.wb_mode);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AWB_MANUAL, scenemode.wb_preset);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_CHROMA_EN, scenemode.chroma_en);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_CHROMA_LVL, scenemode.chroma_lvl);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_EDGE_EN, scenemode.edge_en);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_EDGE_LVL, scenemode.edge_lvl);
	अगर (!ret && is_available_af(info))
		ret = m5mols_ग_लिखो(sd, AF_MODE, scenemode.af_range);
	अगर (!ret && is_available_af(info))
		ret = m5mols_ग_लिखो(sd, FD_CTL, scenemode.fd_mode);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_TONE_CTL, scenemode.tone);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, AE_ISO, scenemode.iso);
	अगर (!ret)
		ret = m5mols_set_mode(info, REG_CAPTURE);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_WDR_EN, scenemode.wdr);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_MCC_MODE, scenemode.mcc);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_LIGHT_CTRL, scenemode.light);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPP_FLASH_CTRL, scenemode.flash);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, CAPC_MODE, scenemode.capt_mode);
	अगर (!ret)
		ret = m5mols_set_mode(info, REG_MONITOR);

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_3a_lock(काष्ठा m5mols_info *info, काष्ठा v4l2_ctrl *ctrl)
अणु
	bool af_lock = ctrl->val & V4L2_LOCK_FOCUS;
	पूर्णांक ret = 0;

	अगर ((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_EXPOSURE) अणु
		bool ae_lock = ctrl->val & V4L2_LOCK_EXPOSURE;

		ret = m5mols_ग_लिखो(&info->sd, AE_LOCK, ae_lock ?
				   REG_AE_LOCK : REG_AE_UNLOCK);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_WHITE_BALANCE)
	    && info->स्वतः_wb->val) अणु
		bool awb_lock = ctrl->val & V4L2_LOCK_WHITE_BALANCE;

		ret = m5mols_ग_लिखो(&info->sd, AWB_LOCK, awb_lock ?
				   REG_AWB_LOCK : REG_AWB_UNLOCK);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!info->ver.af || !af_lock)
		वापस ret;

	अगर ((ctrl->val ^ ctrl->cur.val) & V4L2_LOCK_FOCUS)
		ret = m5mols_ग_लिखो(&info->sd, AF_EXECUTE, REG_AF_STOP);

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_set_metering_mode(काष्ठा m5mols_info *info, पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक metering;

	चयन (mode) अणु
	हाल V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		metering = REG_AE_CENTER;
		अवरोध;
	हाल V4L2_EXPOSURE_METERING_SPOT:
		metering = REG_AE_SPOT;
		अवरोध;
	शेष:
		metering = REG_AE_ALL;
		अवरोध;
	पूर्ण

	वापस m5mols_ग_लिखो(&info->sd, AE_MODE, metering);
पूर्ण

अटल पूर्णांक m5mols_set_exposure(काष्ठा m5mols_info *info, पूर्णांक exposure)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret = 0;

	अगर (exposure == V4L2_EXPOSURE_AUTO) अणु
		/* Unlock स्वतः exposure */
		info->lock_3a->val &= ~V4L2_LOCK_EXPOSURE;
		m5mols_3a_lock(info, info->lock_3a);

		ret = m5mols_set_metering_mode(info, info->metering->val);
		अगर (ret < 0)
			वापस ret;

		v4l2_dbg(1, m5mols_debug, sd,
			 "%s: exposure bias: %#x, metering: %#x\n",
			 __func__, info->exposure_bias->val,
			 info->metering->val);

		वापस m5mols_ग_लिखो(sd, AE_INDEX, info->exposure_bias->val);
	पूर्ण

	अगर (exposure == V4L2_EXPOSURE_MANUAL) अणु
		ret = m5mols_ग_लिखो(sd, AE_MODE, REG_AE_OFF);
		अगर (ret == 0)
			ret = m5mols_ग_लिखो(sd, AE_MAN_GAIN_MON,
					   info->exposure->val);
		अगर (ret == 0)
			ret = m5mols_ग_लिखो(sd, AE_MAN_GAIN_CAP,
					   info->exposure->val);

		v4l2_dbg(1, m5mols_debug, sd, "%s: exposure: %#x\n",
			 __func__, info->exposure->val);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_set_white_balance(काष्ठा m5mols_info *info, पूर्णांक val)
अणु
	अटल स्थिर अचिन्हित लघु wb[][2] = अणु
		अणु V4L2_WHITE_BALANCE_INCANDESCENT,  REG_AWB_INCANDESCENT पूर्ण,
		अणु V4L2_WHITE_BALANCE_FLUORESCENT,   REG_AWB_FLUORESCENT_1 पूर्ण,
		अणु V4L2_WHITE_BALANCE_FLUORESCENT_H, REG_AWB_FLUORESCENT_2 पूर्ण,
		अणु V4L2_WHITE_BALANCE_HORIZON,       REG_AWB_HORIZON पूर्ण,
		अणु V4L2_WHITE_BALANCE_DAYLIGHT,      REG_AWB_DAYLIGHT पूर्ण,
		अणु V4L2_WHITE_BALANCE_FLASH,         REG_AWB_LEDLIGHT पूर्ण,
		अणु V4L2_WHITE_BALANCE_CLOUDY,        REG_AWB_CLOUDY पूर्ण,
		अणु V4L2_WHITE_BALANCE_SHADE,         REG_AWB_SHADE पूर्ण,
		अणु V4L2_WHITE_BALANCE_AUTO,          REG_AWB_AUTO पूर्ण,
	पूर्ण;
	पूर्णांक i;
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret = -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(wb); i++) अणु
		पूर्णांक awb;
		अगर (wb[i][0] != val)
			जारी;

		v4l2_dbg(1, m5mols_debug, sd,
			 "Setting white balance to: %#x\n", wb[i][0]);

		awb = wb[i][0] == V4L2_WHITE_BALANCE_AUTO;
		ret = m5mols_ग_लिखो(sd, AWB_MODE, awb ? REG_AWB_AUTO :
						 REG_AWB_PRESET);
		अगर (ret < 0)
			वापस ret;

		अगर (!awb)
			ret = m5mols_ग_लिखो(sd, AWB_MANUAL, wb[i][1]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_set_saturation(काष्ठा m5mols_info *info, पूर्णांक val)
अणु
	पूर्णांक ret = m5mols_ग_लिखो(&info->sd, MON_CHROMA_LVL, val);
	अगर (ret < 0)
		वापस ret;

	वापस m5mols_ग_लिखो(&info->sd, MON_CHROMA_EN, REG_CHROMA_ON);
पूर्ण

अटल पूर्णांक m5mols_set_color_effect(काष्ठा m5mols_info *info, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक m_effect = REG_COLOR_EFFECT_OFF;
	अचिन्हित पूर्णांक p_effect = REG_EFFECT_OFF;
	अचिन्हित पूर्णांक cfix_r = 0, cfix_b = 0;
	काष्ठा v4l2_subdev *sd = &info->sd;
	पूर्णांक ret = 0;

	चयन (val) अणु
	हाल V4L2_COLORFX_BW:
		m_effect = REG_COLOR_EFFECT_ON;
		अवरोध;
	हाल V4L2_COLORFX_NEGATIVE:
		p_effect = REG_EFFECT_NEGA;
		अवरोध;
	हाल V4L2_COLORFX_EMBOSS:
		p_effect = REG_EFFECT_EMBOSS;
		अवरोध;
	हाल V4L2_COLORFX_SEPIA:
		m_effect = REG_COLOR_EFFECT_ON;
		cfix_r = REG_CFIXR_SEPIA;
		cfix_b = REG_CFIXB_SEPIA;
		अवरोध;
	पूर्ण

	ret = m5mols_ग_लिखो(sd, PARM_EFFECT, p_effect);
	अगर (!ret)
		ret = m5mols_ग_लिखो(sd, MON_EFFECT, m_effect);

	अगर (ret == 0 && m_effect == REG_COLOR_EFFECT_ON) अणु
		ret = m5mols_ग_लिखो(sd, MON_CFIXR, cfix_r);
		अगर (!ret)
			ret = m5mols_ग_लिखो(sd, MON_CFIXB, cfix_b);
	पूर्ण

	v4l2_dbg(1, m5mols_debug, sd,
		 "p_effect: %#x, m_effect: %#x, r: %#x, b: %#x (%d)\n",
		 p_effect, m_effect, cfix_r, cfix_b, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_set_iso(काष्ठा m5mols_info *info, पूर्णांक स्वतः_iso)
अणु
	u32 iso = स्वतः_iso ? 0 : info->iso->val + 1;

	वापस m5mols_ग_लिखो(&info->sd, AE_ISO, iso);
पूर्ण

अटल पूर्णांक m5mols_set_wdr(काष्ठा m5mols_info *info, पूर्णांक wdr)
अणु
	पूर्णांक ret;

	ret = m5mols_ग_लिखो(&info->sd, MON_TONE_CTL, wdr ? 9 : 5);
	अगर (ret < 0)
		वापस ret;

	ret = m5mols_set_mode(info, REG_CAPTURE);
	अगर (ret < 0)
		वापस ret;

	वापस m5mols_ग_लिखो(&info->sd, CAPP_WDR_EN, wdr);
पूर्ण

अटल पूर्णांक m5mols_set_stabilization(काष्ठा m5mols_info *info, पूर्णांक val)
अणु
	काष्ठा v4l2_subdev *sd = &info->sd;
	अचिन्हित पूर्णांक evp = val ? 0xe : 0x0;
	पूर्णांक ret;

	ret = m5mols_ग_लिखो(sd, AE_EV_PRESET_MONITOR, evp);
	अगर (ret < 0)
		वापस ret;

	वापस m5mols_ग_लिखो(sd, AE_EV_PRESET_CAPTURE, evp);
पूर्ण

अटल पूर्णांक m5mols_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा m5mols_info *info = to_m5mols(sd);
	पूर्णांक ret = 0;
	u8 status = REG_ISO_AUTO;

	v4l2_dbg(1, m5mols_debug, sd, "%s: ctrl: %s (%d)\n",
		 __func__, ctrl->name, info->isp_पढ़ोy);

	अगर (!info->isp_पढ़ोy)
		वापस -EBUSY;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ISO_SENSITIVITY_AUTO:
		ret = m5mols_पढ़ो_u8(sd, AE_ISO, &status);
		अगर (ret == 0)
			ctrl->val = !status;
		अगर (status != REG_ISO_AUTO)
			info->iso->val = status - 1;
		अवरोध;

	हाल V4L2_CID_3A_LOCK:
		ctrl->val &= ~0x7;

		ret = m5mols_पढ़ो_u8(sd, AE_LOCK, &status);
		अगर (ret)
			वापस ret;
		अगर (status)
			info->lock_3a->val |= V4L2_LOCK_EXPOSURE;

		ret = m5mols_पढ़ो_u8(sd, AWB_LOCK, &status);
		अगर (ret)
			वापस ret;
		अगर (status)
			info->lock_3a->val |= V4L2_LOCK_EXPOSURE;

		ret = m5mols_पढ़ो_u8(sd, AF_EXECUTE, &status);
		अगर (!status)
			info->lock_3a->val |= V4L2_LOCK_EXPOSURE;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक m5mols_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	अचिन्हित पूर्णांक ctrl_mode = m5mols_get_ctrl_mode(ctrl);
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा m5mols_info *info = to_m5mols(sd);
	पूर्णांक last_mode = info->mode;
	पूर्णांक ret = 0;

	/*
	 * If needed, defer restoring the controls until
	 * the device is fully initialized.
	 */
	अगर (!info->isp_पढ़ोy) अणु
		info->ctrl_sync = 0;
		वापस 0;
	पूर्ण

	v4l2_dbg(1, m5mols_debug, sd, "%s: %s, val: %d, priv: %p\n",
		 __func__, ctrl->name, ctrl->val, ctrl->priv);

	अगर (ctrl_mode && ctrl_mode != info->mode) अणु
		ret = m5mols_set_mode(info, ctrl_mode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	चयन (ctrl->id) अणु
	हाल V4L2_CID_3A_LOCK:
		ret = m5mols_3a_lock(info, ctrl);
		अवरोध;

	हाल V4L2_CID_ZOOM_ABSOLUTE:
		ret = m5mols_ग_लिखो(sd, MON_ZOOM, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = m5mols_set_exposure(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_ISO_SENSITIVITY:
		ret = m5mols_set_iso(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		ret = m5mols_set_white_balance(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		ret = m5mols_set_saturation(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_COLORFX:
		ret = m5mols_set_color_effect(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_WIDE_DYNAMIC_RANGE:
		ret = m5mols_set_wdr(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_IMAGE_STABILIZATION:
		ret = m5mols_set_stabilization(info, ctrl->val);
		अवरोध;

	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ret = m5mols_ग_लिखो(sd, CAPP_JPEG_RATIO, ctrl->val);
		अवरोध;
	पूर्ण

	अगर (ret == 0 && info->mode != last_mode)
		ret = m5mols_set_mode(info, last_mode);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops m5mols_ctrl_ops = अणु
	.g_अस्थिर_ctrl	= m5mols_g_अस्थिर_ctrl,
	.s_ctrl			= m5mols_s_ctrl,
पूर्ण;

/* Supported manual ISO values */
अटल स्थिर s64 iso_qmenu[] = अणु
	/* AE_ISO: 0x01...0x07 (ISO: 50...3200) */
	50000, 100000, 200000, 400000, 800000, 1600000, 3200000
पूर्ण;

/* Supported Exposure Bias values, -2.0EV...+2.0EV */
अटल स्थिर s64 ev_bias_qmenu[] = अणु
	/* AE_INDEX: 0x00...0x08 */
	-2000, -1500, -1000, -500, 0, 500, 1000, 1500, 2000
पूर्ण;

पूर्णांक m5mols_init_controls(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा m5mols_info *info = to_m5mols(sd);
	u16 exposure_max;
	u16 zoom_step;
	पूर्णांक ret;

	/* Determine the firmware dependent control range and step values */
	ret = m5mols_पढ़ो_u16(sd, AE_MAX_GAIN_MON, &exposure_max);
	अगर (ret < 0)
		वापस ret;

	zoom_step = is_manufacturer(info, REG_SAMSUNG_OPTICS) ? 31 : 1;
	v4l2_ctrl_handler_init(&info->handle, 20);

	info->स्वतः_wb = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
			9, ~0x3fe, V4L2_WHITE_BALANCE_AUTO);

	/* Exposure control cluster */
	info->स्वतः_exposure = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			1, ~0x03, V4L2_EXPOSURE_AUTO);

	info->exposure = v4l2_ctrl_new_std(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE,
			0, exposure_max, 1, exposure_max / 2);

	info->exposure_bias = v4l2_ctrl_new_पूर्णांक_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_AUTO_EXPOSURE_BIAS,
			ARRAY_SIZE(ev_bias_qmenu) - 1,
			ARRAY_SIZE(ev_bias_qmenu)/2 - 1,
			ev_bias_qmenu);

	info->metering = v4l2_ctrl_new_std_menu(&info->handle,
			&m5mols_ctrl_ops, V4L2_CID_EXPOSURE_METERING,
			2, ~0x7, V4L2_EXPOSURE_METERING_AVERAGE);

	/* ISO control cluster */
	info->स्वतः_iso = v4l2_ctrl_new_std_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ISO_SENSITIVITY_AUTO, 1, ~0x03, 1);

	info->iso = v4l2_ctrl_new_पूर्णांक_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ISO_SENSITIVITY, ARRAY_SIZE(iso_qmenu) - 1,
			ARRAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	info->saturation = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_SATURATION, 1, 5, 1, 3);

	info->zoom = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_ZOOM_ABSOLUTE, 1, 70, zoom_step, 1);

	info->colorfx = v4l2_ctrl_new_std_menu(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_COLORFX, 4, 0, V4L2_COLORFX_NONE);

	info->wdr = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_WIDE_DYNAMIC_RANGE, 0, 1, 1, 0);

	info->stabilization = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_IMAGE_STABILIZATION, 0, 1, 1, 0);

	info->jpeg_quality = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY, 1, 100, 1, 80);

	info->lock_3a = v4l2_ctrl_new_std(&info->handle, &m5mols_ctrl_ops,
			V4L2_CID_3A_LOCK, 0, 0x7, 0, 0);

	अगर (info->handle.error) अणु
		पूर्णांक ret = info->handle.error;
		v4l2_err(sd, "Failed to initialize controls: %d\n", ret);
		v4l2_ctrl_handler_मुक्त(&info->handle);
		वापस ret;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(4, &info->स्वतः_exposure, 1, false);
	info->स्वतः_iso->flags |= V4L2_CTRL_FLAG_VOLATILE |
				V4L2_CTRL_FLAG_UPDATE;
	v4l2_ctrl_स्वतः_cluster(2, &info->स्वतः_iso, 0, false);

	info->lock_3a->flags |= V4L2_CTRL_FLAG_VOLATILE;

	m5mols_set_ctrl_mode(info->स्वतः_exposure, REG_PARAMETER);
	m5mols_set_ctrl_mode(info->स्वतः_wb, REG_PARAMETER);
	m5mols_set_ctrl_mode(info->colorfx, REG_MONITOR);

	sd->ctrl_handler = &info->handle;

	वापस 0;
पूर्ण
