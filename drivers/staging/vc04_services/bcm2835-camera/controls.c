<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-common.h>

#समावेश "mmal-common.h"
#समावेश "mmal-vchiq.h"
#समावेश "mmal-parameters.h"
#समावेश "bcm2835-camera.h"

/* The supported V4L2_CID_AUTO_EXPOSURE_BIAS values are from -4.0 to +4.0.
 * MMAL values are in 1/6th increments so the MMAL range is -24 to +24.
 * V4L2 करोcs say value "is expressed in terms of EV, drivers should पूर्णांकerpret
 * the values as 0.001 EV units, where the value 1000 stands क्रम +1 EV."
 * V4L2 is limited to a max of 32 values in a menu, so count in 1/3rds from
 * -4 to +4
 */
अटल स्थिर s64 ev_bias_qmenu[] = अणु
	-4000, -3667, -3333,
	-3000, -2667, -2333,
	-2000, -1667, -1333,
	-1000,  -667,  -333,
	    0,   333,   667,
	 1000,  1333,  1667,
	 2000,  2333,  2667,
	 3000,  3333,  3667,
	 4000
पूर्ण;

/* Supported ISO values (*1000)
 * ISOO = स्वतः ISO
 */
अटल स्थिर s64 iso_qmenu[] = अणु
	0, 100000, 200000, 400000, 800000,
पूर्ण;

अटल स्थिर u32 iso_values[] = अणु
	0, 100, 200, 400, 800,
पूर्ण;

क्रमागत bm2835_mmal_ctrl_type अणु
	MMAL_CONTROL_TYPE_STD,
	MMAL_CONTROL_TYPE_STD_MENU,
	MMAL_CONTROL_TYPE_INT_MENU,
	MMAL_CONTROL_TYPE_CLUSTER, /* special cluster entry */
पूर्ण;

काष्ठा bm2835_mmal_v4l2_ctrl;

प्रकार	पूर्णांक(bm2835_mmal_v4l2_ctrl_cb)(
				काष्ठा bm2835_mmal_dev *dev,
				काष्ठा v4l2_ctrl *ctrl,
				स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl);

काष्ठा bm2835_mmal_v4l2_ctrl अणु
	u32 id; /* v4l2 control identअगरier */
	क्रमागत bm2835_mmal_ctrl_type type;
	/* control minimum value or
	 * mask क्रम MMAL_CONTROL_TYPE_STD_MENU
	 */
	s64 min;
	s64 max; /* maximum value of control */
	s64 def;  /* शेष value of control */
	u64 step; /* step size of the control */
	स्थिर s64 *imenu; /* पूर्णांकeger menu array */
	u32 mmal_id; /* mmal parameter id */
	bm2835_mmal_v4l2_ctrl_cb *setter;
पूर्ण;

काष्ठा v4l2_to_mmal_effects_setting अणु
	u32 v4l2_effect;
	u32 mmal_effect;
	s32 col_fx_enable;
	s32 col_fx_fixed_cbcr;
	u32 u;
	u32 v;
	u32 num_effect_params;
	u32 effect_params[MMAL_MAX_IMAGEFX_PARAMETERS];
पूर्ण;

अटल स्थिर काष्ठा v4l2_to_mmal_effects_setting
	v4l2_to_mmal_effects_values[] = अणु
	अणु  V4L2_COLORFX_NONE,         MMAL_PARAM_IMAGEFX_NONE,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_BW,           MMAL_PARAM_IMAGEFX_NONE,
		1,   0,    128,  128, 0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SEPIA,        MMAL_PARAM_IMAGEFX_NONE,
		1,   0,    87,   151, 0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_NEGATIVE,     MMAL_PARAM_IMAGEFX_NEGATIVE,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_EMBOSS,       MMAL_PARAM_IMAGEFX_EMBOSS,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SKETCH,       MMAL_PARAM_IMAGEFX_SKETCH,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SKY_BLUE,     MMAL_PARAM_IMAGEFX_PASTEL,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_GRASS_GREEN,  MMAL_PARAM_IMAGEFX_WATERCOLOUR,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SKIN_WHITEN,  MMAL_PARAM_IMAGEFX_WASHEDOUT,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_VIVID,        MMAL_PARAM_IMAGEFX_SATURATION,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_AQUA,         MMAL_PARAM_IMAGEFX_NONE,
		1,   0,    171,  121, 0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_ART_FREEZE,   MMAL_PARAM_IMAGEFX_HATCH,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SILHOUETTE,   MMAL_PARAM_IMAGEFX_FILM,
		0,   0,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SOLARIZATION, MMAL_PARAM_IMAGEFX_SOLARIZE,
		0,   0,    0,    0,   5, अणु1, 128, 160, 160, 48पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_ANTIQUE,      MMAL_PARAM_IMAGEFX_COLOURBALANCE,
		0,   0,    0,    0,   3, अणु108, 274, 238, 0, 0पूर्ण पूर्ण,
	अणु  V4L2_COLORFX_SET_CBCR,     MMAL_PARAM_IMAGEFX_NONE,
		1,   1,    0,    0,   0, अणु0, 0, 0, 0, 0पूर्ण पूर्ण
पूर्ण;

काष्ठा v4l2_mmal_scene_config अणु
	क्रमागत v4l2_scene_mode v4l2_scene;
	क्रमागत mmal_parameter_exposuremode exposure_mode;
	क्रमागत mmal_parameter_exposuremeteringmode metering_mode;
पूर्ण;

अटल स्थिर काष्ठा v4l2_mmal_scene_config scene_configs[] = अणु
	/* V4L2_SCENE_MODE_NONE स्वतःmatically added */
	अणु
		V4L2_SCENE_MODE_NIGHT,
		MMAL_PARAM_EXPOSUREMODE_NIGHT,
		MMAL_PARAM_EXPOSUREMETERINGMODE_AVERAGE
	पूर्ण,
	अणु
		V4L2_SCENE_MODE_SPORTS,
		MMAL_PARAM_EXPOSUREMODE_SPORTS,
		MMAL_PARAM_EXPOSUREMETERINGMODE_AVERAGE
	पूर्ण,
पूर्ण;

/* control handlers*/

अटल पूर्णांक ctrl_set_rational(काष्ठा bm2835_mmal_dev *dev,
			     काष्ठा v4l2_ctrl *ctrl,
			     स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	काष्ठा mmal_parameter_rational rational_value;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	rational_value.num = ctrl->val;
	rational_value.den = 100;

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &rational_value,
					     माप(rational_value));
पूर्ण

अटल पूर्णांक ctrl_set_value(काष्ठा bm2835_mmal_dev *dev,
			  काष्ठा v4l2_ctrl *ctrl,
			  स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	u32_value = ctrl->val;

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_iso(काष्ठा bm2835_mmal_dev *dev,
			काष्ठा v4l2_ctrl *ctrl,
			स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *control;

	अगर (ctrl->val > mmal_ctrl->max || ctrl->val < mmal_ctrl->min)
		वापस 1;

	अगर (ctrl->id == V4L2_CID_ISO_SENSITIVITY)
		dev->iso = iso_values[ctrl->val];
	अन्यथा अगर (ctrl->id == V4L2_CID_ISO_SENSITIVITY_AUTO)
		dev->manual_iso_enabled =
				(ctrl->val == V4L2_ISO_SENSITIVITY_MANUAL);

	control = &dev->component[COMP_CAMERA]->control;

	अगर (dev->manual_iso_enabled)
		u32_value = dev->iso;
	अन्यथा
		u32_value = 0;

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     MMAL_PARAMETER_ISO,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_value_ev(काष्ठा bm2835_mmal_dev *dev,
			     काष्ठा v4l2_ctrl *ctrl,
			     स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	s32 s32_value;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	s32_value = (ctrl->val - 12) * 2;	/* Convert from index to 1/6ths */

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &s32_value, माप(s32_value));
पूर्ण

अटल पूर्णांक ctrl_set_rotate(काष्ठा bm2835_mmal_dev *dev,
			   काष्ठा v4l2_ctrl *ctrl,
			   स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret;
	u32 u32_value;
	काष्ठा vchiq_mmal_component *camera;

	camera = dev->component[COMP_CAMERA];

	u32_value = ((ctrl->val % 360) / 90) * 90;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[0],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
	अगर (ret < 0)
		वापस ret;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[1],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
	अगर (ret < 0)
		वापस ret;

	वापस vchiq_mmal_port_parameter_set(dev->instance, &camera->output[2],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_flip(काष्ठा bm2835_mmal_dev *dev,
			 काष्ठा v4l2_ctrl *ctrl,
			 स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret;
	u32 u32_value;
	काष्ठा vchiq_mmal_component *camera;

	अगर (ctrl->id == V4L2_CID_HFLIP)
		dev->hflip = ctrl->val;
	अन्यथा
		dev->vflip = ctrl->val;

	camera = dev->component[COMP_CAMERA];

	अगर (dev->hflip && dev->vflip)
		u32_value = MMAL_PARAM_MIRROR_BOTH;
	अन्यथा अगर (dev->hflip)
		u32_value = MMAL_PARAM_MIRROR_HORIZONTAL;
	अन्यथा अगर (dev->vflip)
		u32_value = MMAL_PARAM_MIRROR_VERTICAL;
	अन्यथा
		u32_value = MMAL_PARAM_MIRROR_NONE;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[0],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
	अगर (ret < 0)
		वापस ret;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[1],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
	अगर (ret < 0)
		वापस ret;

	वापस vchiq_mmal_port_parameter_set(dev->instance, &camera->output[2],
					    mmal_ctrl->mmal_id,
					    &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_exposure(काष्ठा bm2835_mmal_dev *dev,
			     काष्ठा v4l2_ctrl *ctrl,
			     स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	क्रमागत mmal_parameter_exposuremode exp_mode = dev->exposure_mode_user;
	u32 shutter_speed = 0;
	काष्ठा vchiq_mmal_port *control;
	पूर्णांक ret = 0;

	control = &dev->component[COMP_CAMERA]->control;

	अगर (mmal_ctrl->mmal_id == MMAL_PARAMETER_SHUTTER_SPEED)	अणु
		/* V4L2 is in 100usec increments.
		 * MMAL is 1usec.
		 */
		dev->manual_shutter_speed = ctrl->val * 100;
	पूर्ण अन्यथा अगर (mmal_ctrl->mmal_id == MMAL_PARAMETER_EXPOSURE_MODE) अणु
		चयन (ctrl->val) अणु
		हाल V4L2_EXPOSURE_AUTO:
			exp_mode = MMAL_PARAM_EXPOSUREMODE_AUTO;
			अवरोध;

		हाल V4L2_EXPOSURE_MANUAL:
			exp_mode = MMAL_PARAM_EXPOSUREMODE_OFF;
			अवरोध;
		पूर्ण
		dev->exposure_mode_user = exp_mode;
		dev->exposure_mode_v4l2_user = ctrl->val;
	पूर्ण अन्यथा अगर (mmal_ctrl->id == V4L2_CID_EXPOSURE_AUTO_PRIORITY) अणु
		dev->exp_स्वतः_priority = ctrl->val;
	पूर्ण

	अगर (dev->scene_mode == V4L2_SCENE_MODE_NONE) अणु
		अगर (exp_mode == MMAL_PARAM_EXPOSUREMODE_OFF)
			shutter_speed = dev->manual_shutter_speed;

		ret = vchiq_mmal_port_parameter_set(dev->instance,
						    control,
						    MMAL_PARAMETER_SHUTTER_SPEED,
						    &shutter_speed,
						    माप(shutter_speed));
		ret += vchiq_mmal_port_parameter_set(dev->instance,
						     control,
						     MMAL_PARAMETER_EXPOSURE_MODE,
						     &exp_mode,
						     माप(u32));
		dev->exposure_mode_active = exp_mode;
	पूर्ण
	/* exposure_dynamic_framerate (V4L2_CID_EXPOSURE_AUTO_PRIORITY) should
	 * always apply irrespective of scene mode.
	 */
	ret += set_framerate_params(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ctrl_set_metering_mode(काष्ठा bm2835_mmal_dev *dev,
				  काष्ठा v4l2_ctrl *ctrl,
				  स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	चयन (ctrl->val) अणु
	हाल V4L2_EXPOSURE_METERING_AVERAGE:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_AVERAGE;
		अवरोध;

	हाल V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_BACKLIT;
		अवरोध;

	हाल V4L2_EXPOSURE_METERING_SPOT:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_SPOT;
		अवरोध;

	हाल V4L2_EXPOSURE_METERING_MATRIX:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_MATRIX;
		अवरोध;
	पूर्ण

	अगर (dev->scene_mode == V4L2_SCENE_MODE_NONE) अणु
		काष्ठा vchiq_mmal_port *control;
		u32 u32_value = dev->metering_mode;

		control = &dev->component[COMP_CAMERA]->control;

		वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ctrl_set_flicker_aव्योमance(काष्ठा bm2835_mmal_dev *dev,
				      काष्ठा v4l2_ctrl *ctrl,
				      स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	चयन (ctrl->val) अणु
	हाल V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		u32_value = MMAL_PARAM_FLICKERAVOID_OFF;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		u32_value = MMAL_PARAM_FLICKERAVOID_50HZ;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		u32_value = MMAL_PARAM_FLICKERAVOID_60HZ;
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		u32_value = MMAL_PARAM_FLICKERAVOID_AUTO;
		अवरोध;
	पूर्ण

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_awb_mode(काष्ठा bm2835_mmal_dev *dev,
			     काष्ठा v4l2_ctrl *ctrl,
			     स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	चयन (ctrl->val) अणु
	हाल V4L2_WHITE_BALANCE_MANUAL:
		u32_value = MMAL_PARAM_AWBMODE_OFF;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_AUTO:
		u32_value = MMAL_PARAM_AWBMODE_AUTO;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_INCANDESCENT:
		u32_value = MMAL_PARAM_AWBMODE_INCANDESCENT;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_FLUORESCENT:
		u32_value = MMAL_PARAM_AWBMODE_FLUORESCENT;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_FLUORESCENT_H:
		u32_value = MMAL_PARAM_AWBMODE_TUNGSTEN;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_HORIZON:
		u32_value = MMAL_PARAM_AWBMODE_HORIZON;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_DAYLIGHT:
		u32_value = MMAL_PARAM_AWBMODE_SUNLIGHT;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_FLASH:
		u32_value = MMAL_PARAM_AWBMODE_FLASH;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_CLOUDY:
		u32_value = MMAL_PARAM_AWBMODE_CLOUDY;
		अवरोध;

	हाल V4L2_WHITE_BALANCE_SHADE:
		u32_value = MMAL_PARAM_AWBMODE_SHADE;
		अवरोध;
	पूर्ण

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_awb_gains(काष्ठा bm2835_mmal_dev *dev,
			      काष्ठा v4l2_ctrl *ctrl,
			      स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	काष्ठा vchiq_mmal_port *control;
	काष्ठा mmal_parameter_awbgains gains;

	control = &dev->component[COMP_CAMERA]->control;

	अगर (ctrl->id == V4L2_CID_RED_BALANCE)
		dev->red_gain = ctrl->val;
	अन्यथा अगर (ctrl->id == V4L2_CID_BLUE_BALANCE)
		dev->blue_gain = ctrl->val;

	gains.r_gain.num = dev->red_gain;
	gains.b_gain.num = dev->blue_gain;
	gains.r_gain.den = gains.b_gain.den = 1000;

	वापस vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &gains, माप(gains));
पूर्ण

अटल पूर्णांक ctrl_set_image_effect(काष्ठा bm2835_mmal_dev *dev,
				 काष्ठा v4l2_ctrl *ctrl,
				 स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक i, j;
	काष्ठा vchiq_mmal_port *control;
	काष्ठा mmal_parameter_imagefx_parameters imagefx;

	क्रम (i = 0; i < ARRAY_SIZE(v4l2_to_mmal_effects_values); i++) अणु
		अगर (ctrl->val != v4l2_to_mmal_effects_values[i].v4l2_effect)
			जारी;

		imagefx.effect =
			v4l2_to_mmal_effects_values[i].mmal_effect;
		imagefx.num_effect_params =
			v4l2_to_mmal_effects_values[i].num_effect_params;

		अगर (imagefx.num_effect_params > MMAL_MAX_IMAGEFX_PARAMETERS)
			imagefx.num_effect_params = MMAL_MAX_IMAGEFX_PARAMETERS;

		क्रम (j = 0; j < imagefx.num_effect_params; j++)
			imagefx.effect_parameter[j] =
				v4l2_to_mmal_effects_values[i].effect_params[j];

		dev->colourfx.enable =
			v4l2_to_mmal_effects_values[i].col_fx_enable;
		अगर (!v4l2_to_mmal_effects_values[i].col_fx_fixed_cbcr) अणु
			dev->colourfx.u = v4l2_to_mmal_effects_values[i].u;
			dev->colourfx.v = v4l2_to_mmal_effects_values[i].v;
		पूर्ण

		control = &dev->component[COMP_CAMERA]->control;

		ret = vchiq_mmal_port_parameter_set(
				dev->instance, control,
				MMAL_PARAMETER_IMAGE_EFFECT_PARAMETERS,
				&imagefx, माप(imagefx));
		अगर (ret)
			जाओ निकास;

		ret = vchiq_mmal_port_parameter_set(
				dev->instance, control,
				MMAL_PARAMETER_COLOUR_EFFECT,
				&dev->colourfx, माप(dev->colourfx));
	पूर्ण

निकास:
	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "mmal_ctrl:%p ctrl id:0x%x ctrl val:%d imagefx:0x%x color_effect:%s u:%d v:%d ret %d(%d)\n",
				mmal_ctrl, ctrl->id, ctrl->val, imagefx.effect,
				dev->colourfx.enable ? "true" : "false",
				dev->colourfx.u, dev->colourfx.v,
				ret, (ret == 0 ? 0 : -EINVAL));
	वापस (ret == 0 ? 0 : -EINVAL);
पूर्ण

अटल पूर्णांक ctrl_set_colfx(काष्ठा bm2835_mmal_dev *dev,
			  काष्ठा v4l2_ctrl *ctrl,
			  स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret;
	काष्ठा vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	dev->colourfx.u = (ctrl->val & 0xff00) >> 8;
	dev->colourfx.v = ctrl->val & 0xff;

	ret = vchiq_mmal_port_parameter_set(dev->instance, control,
					    MMAL_PARAMETER_COLOUR_EFFECT,
					    &dev->colourfx,
					    माप(dev->colourfx));

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "%s: After: mmal_ctrl:%p ctrl id:0x%x ctrl val:%d ret %d(%d)\n",
			__func__, mmal_ctrl, ctrl->id, ctrl->val, ret,
			(ret == 0 ? 0 : -EINVAL));
	वापस (ret == 0 ? 0 : -EINVAL);
पूर्ण

अटल पूर्णांक ctrl_set_bitrate(काष्ठा bm2835_mmal_dev *dev,
			    काष्ठा v4l2_ctrl *ctrl,
			    स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret;
	काष्ठा vchiq_mmal_port *encoder_out;

	dev->capture.encode_bitrate = ctrl->val;

	encoder_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	ret = vchiq_mmal_port_parameter_set(dev->instance, encoder_out,
					    mmal_ctrl->mmal_id, &ctrl->val,
					    माप(ctrl->val));

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "%s: After: mmal_ctrl:%p ctrl id:0x%x ctrl val:%d ret %d(%d)\n",
		 __func__, mmal_ctrl, ctrl->id, ctrl->val, ret,
		 (ret == 0 ? 0 : -EINVAL));

	/*
	 * Older firmware versions (pre July 2019) have a bug in handling
	 * MMAL_PARAMETER_VIDEO_BIT_RATE that result in the call
	 * वापसing -MMAL_MSG_STATUS_EINVAL. So ignore errors from this call.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_set_bitrate_mode(काष्ठा bm2835_mmal_dev *dev,
				 काष्ठा v4l2_ctrl *ctrl,
				 स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 bitrate_mode;
	काष्ठा vchiq_mmal_port *encoder_out;

	encoder_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	dev->capture.encode_bitrate_mode = ctrl->val;
	चयन (ctrl->val) अणु
	शेष:
	हाल V4L2_MPEG_VIDEO_BITRATE_MODE_VBR:
		bitrate_mode = MMAL_VIDEO_RATECONTROL_VARIABLE;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_BITRATE_MODE_CBR:
		bitrate_mode = MMAL_VIDEO_RATECONTROL_CONSTANT;
		अवरोध;
	पूर्ण

	vchiq_mmal_port_parameter_set(dev->instance, encoder_out,
				      mmal_ctrl->mmal_id,
					     &bitrate_mode,
					     माप(bitrate_mode));
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_set_image_encode_output(काष्ठा bm2835_mmal_dev *dev,
					काष्ठा v4l2_ctrl *ctrl,
					स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *jpeg_out;

	jpeg_out = &dev->component[COMP_IMAGE_ENCODE]->output[0];

	u32_value = ctrl->val;

	वापस vchiq_mmal_port_parameter_set(dev->instance, jpeg_out,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_video_encode_param_output(काष्ठा bm2835_mmal_dev *dev,
					      काष्ठा v4l2_ctrl *ctrl,
					      स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	u32 u32_value;
	काष्ठा vchiq_mmal_port *vid_enc_ctl;

	vid_enc_ctl = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	u32_value = ctrl->val;

	वापस vchiq_mmal_port_parameter_set(dev->instance, vid_enc_ctl,
					     mmal_ctrl->mmal_id,
					     &u32_value, माप(u32_value));
पूर्ण

अटल पूर्णांक ctrl_set_video_encode_profile_level(काष्ठा bm2835_mmal_dev *dev,
					       काष्ठा v4l2_ctrl *ctrl,
					       स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	काष्ठा mmal_parameter_video_profile param;
	पूर्णांक ret = 0;

	अगर (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_PROखाता) अणु
		चयन (ctrl->val) अणु
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE:
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE:
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_MAIN:
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_HIGH:
			dev->capture.enc_profile = ctrl->val;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_LEVEL) अणु
		चयन (ctrl->val) अणु
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
			dev->capture.enc_level = ctrl->val;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		चयन (dev->capture.enc_profile) अणु
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE:
			param.profile = MMAL_VIDEO_PROखाता_H264_BASELINE;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE:
			param.profile =
				MMAL_VIDEO_PROखाता_H264_CONSTRAINED_BASELINE;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_MAIN:
			param.profile = MMAL_VIDEO_PROखाता_H264_MAIN;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_PROखाता_HIGH:
			param.profile = MMAL_VIDEO_PROखाता_H264_HIGH;
			अवरोध;
		शेष:
			/* Should never get here */
			अवरोध;
		पूर्ण

		चयन (dev->capture.enc_level) अणु
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
			param.level = MMAL_VIDEO_LEVEL_H264_1;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1B:
			param.level = MMAL_VIDEO_LEVEL_H264_1b;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
			param.level = MMAL_VIDEO_LEVEL_H264_11;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
			param.level = MMAL_VIDEO_LEVEL_H264_12;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
			param.level = MMAL_VIDEO_LEVEL_H264_13;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
			param.level = MMAL_VIDEO_LEVEL_H264_2;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
			param.level = MMAL_VIDEO_LEVEL_H264_21;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
			param.level = MMAL_VIDEO_LEVEL_H264_22;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
			param.level = MMAL_VIDEO_LEVEL_H264_3;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
			param.level = MMAL_VIDEO_LEVEL_H264_31;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
			param.level = MMAL_VIDEO_LEVEL_H264_32;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
			param.level = MMAL_VIDEO_LEVEL_H264_4;
			अवरोध;
		शेष:
			/* Should never get here */
			अवरोध;
		पूर्ण

		ret = vchiq_mmal_port_parameter_set(dev->instance,
						    &dev->component[COMP_VIDEO_ENCODE]->output[0],
			mmal_ctrl->mmal_id,
			&param, माप(param));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ctrl_set_scene_mode(काष्ठा bm2835_mmal_dev *dev,
			       काष्ठा v4l2_ctrl *ctrl,
			       स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl)
अणु
	पूर्णांक ret = 0;
	पूर्णांक shutter_speed;
	काष्ठा vchiq_mmal_port *control;

	v4l2_dbg(0, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "scene mode selected %d, was %d\n", ctrl->val,
		 dev->scene_mode);
	control = &dev->component[COMP_CAMERA]->control;

	अगर (ctrl->val == dev->scene_mode)
		वापस 0;

	अगर (ctrl->val == V4L2_SCENE_MODE_NONE) अणु
		/* Restore all user selections */
		dev->scene_mode = V4L2_SCENE_MODE_NONE;

		अगर (dev->exposure_mode_user == MMAL_PARAM_EXPOSUREMODE_OFF)
			shutter_speed = dev->manual_shutter_speed;
		अन्यथा
			shutter_speed = 0;

		v4l2_dbg(0, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s: scene mode none: shut_speed %d, exp_mode %d, metering %d\n",
			 __func__, shutter_speed, dev->exposure_mode_user,
			 dev->metering_mode);
		ret = vchiq_mmal_port_parameter_set(dev->instance,
						    control,
						    MMAL_PARAMETER_SHUTTER_SPEED,
						    &shutter_speed,
						    माप(shutter_speed));
		ret += vchiq_mmal_port_parameter_set(dev->instance,
						     control,
						     MMAL_PARAMETER_EXPOSURE_MODE,
						     &dev->exposure_mode_user,
						     माप(u32));
		dev->exposure_mode_active = dev->exposure_mode_user;
		ret += vchiq_mmal_port_parameter_set(dev->instance,
						     control,
						     MMAL_PARAMETER_EXP_METERING_MODE,
						     &dev->metering_mode,
						     माप(u32));
		ret += set_framerate_params(dev);
	पूर्ण अन्यथा अणु
		/* Set up scene mode */
		पूर्णांक i;
		स्थिर काष्ठा v4l2_mmal_scene_config *scene = शून्य;
		पूर्णांक shutter_speed;
		क्रमागत mmal_parameter_exposuremode exposure_mode;
		क्रमागत mmal_parameter_exposuremeteringmode metering_mode;

		क्रम (i = 0; i < ARRAY_SIZE(scene_configs); i++) अणु
			अगर (scene_configs[i].v4l2_scene == ctrl->val) अणु
				scene = &scene_configs[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!scene)
			वापस -EINVAL;
		अगर (i >= ARRAY_SIZE(scene_configs))
			वापस -EINVAL;

		/* Set all the values */
		dev->scene_mode = ctrl->val;

		अगर (scene->exposure_mode == MMAL_PARAM_EXPOSUREMODE_OFF)
			shutter_speed = dev->manual_shutter_speed;
		अन्यथा
			shutter_speed = 0;
		exposure_mode = scene->exposure_mode;
		metering_mode = scene->metering_mode;

		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s: scene mode none: shut_speed %d, exp_mode %d, metering %d\n",
			 __func__, shutter_speed, exposure_mode, metering_mode);

		ret = vchiq_mmal_port_parameter_set(dev->instance, control,
						    MMAL_PARAMETER_SHUTTER_SPEED,
						    &shutter_speed,
						    माप(shutter_speed));
		ret += vchiq_mmal_port_parameter_set(dev->instance, control,
						     MMAL_PARAMETER_EXPOSURE_MODE,
						     &exposure_mode,
						     माप(u32));
		dev->exposure_mode_active = exposure_mode;
		ret += vchiq_mmal_port_parameter_set(dev->instance, control,
						     MMAL_PARAMETER_EXPOSURE_MODE,
						     &exposure_mode,
						     माप(u32));
		ret += vchiq_mmal_port_parameter_set(dev->instance, control,
						     MMAL_PARAMETER_EXP_METERING_MODE,
						     &metering_mode,
						     माप(u32));
		ret += set_framerate_params(dev);
	पूर्ण
	अगर (ret) अणु
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "%s: Setting scene to %d, ret=%d\n",
			 __func__, ctrl->val, ret);
		ret = -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bm2835_mmal_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा bm2835_mmal_dev *dev =
		container_of(ctrl->handler, काष्ठा bm2835_mmal_dev,
			     ctrl_handler);
	स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *mmal_ctrl = ctrl->priv;
	पूर्णांक ret;

	अगर (!mmal_ctrl || mmal_ctrl->id != ctrl->id || !mmal_ctrl->setter) अणु
		pr_warn("mmal_ctrl:%p ctrl id:%d\n", mmal_ctrl, ctrl->id);
		वापस -EINVAL;
	पूर्ण

	ret = mmal_ctrl->setter(dev, ctrl, mmal_ctrl);
	अगर (ret)
		pr_warn("ctrl id:%d/MMAL param %08X- returned ret %d\n",
			ctrl->id, mmal_ctrl->mmal_id, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops bm2835_mmal_ctrl_ops = अणु
	.s_ctrl = bm2835_mmal_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा bm2835_mmal_v4l2_ctrl v4l2_ctrls[V4L2_CTRL_COUNT] = अणु
	अणु
		.id = V4L2_CID_SATURATION,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_SATURATION,
		.setter = ctrl_set_rational,
	पूर्ण,
	अणु
		.id = V4L2_CID_SHARPNESS,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_SHARPNESS,
		.setter = ctrl_set_rational,
	पूर्ण,
	अणु
		.id = V4L2_CID_CONTRAST,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_CONTRAST,
		.setter = ctrl_set_rational,
	पूर्ण,
	अणु
		.id = V4L2_CID_BRIGHTNESS,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 100,
		.def = 50,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_BRIGHTNESS,
		.setter = ctrl_set_rational,
	पूर्ण,
	अणु
		.id = V4L2_CID_ISO_SENSITIVITY,
		.type = MMAL_CONTROL_TYPE_INT_MENU,
		.min = 0,
		.max = ARRAY_SIZE(iso_qmenu) - 1,
		.def = 0,
		.step = 1,
		.imenu = iso_qmenu,
		.mmal_id = MMAL_PARAMETER_ISO,
		.setter = ctrl_set_iso,
	पूर्ण,
	अणु
		.id = V4L2_CID_ISO_SENSITIVITY_AUTO,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = 0,
		.max = V4L2_ISO_SENSITIVITY_AUTO,
		.def = V4L2_ISO_SENSITIVITY_AUTO,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_ISO,
		.setter = ctrl_set_iso,
	पूर्ण,
	अणु
		.id = V4L2_CID_IMAGE_STABILIZATION,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_VIDEO_STABILISATION,
		.setter = ctrl_set_value,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_AUTO,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = ~0x03,
		.max = V4L2_EXPOSURE_APERTURE_PRIORITY,
		.def = V4L2_EXPOSURE_AUTO,
		.step = 0,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_EXPOSURE_MODE,
		.setter = ctrl_set_exposure,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_ABSOLUTE,
		.type = MMAL_CONTROL_TYPE_STD,
		/* Units of 100usecs */
		.min = 1,
		.max = 1 * 1000 * 10,
		.def = 100 * 10,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_SHUTTER_SPEED,
		.setter = ctrl_set_exposure,
	पूर्ण,
	अणु
		.id = V4L2_CID_AUTO_EXPOSURE_BIAS,
		.type = MMAL_CONTROL_TYPE_INT_MENU,
		.min = 0,
		.max = ARRAY_SIZE(ev_bias_qmenu) - 1,
		.def = (ARRAY_SIZE(ev_bias_qmenu) + 1) / 2 - 1,
		.step = 0,
		.imenu = ev_bias_qmenu,
		.mmal_id = MMAL_PARAMETER_EXPOSURE_COMP,
		.setter = ctrl_set_value_ev,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_AUTO_PRIORITY,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		/* Dummy MMAL ID as it माला_लो mapped पूर्णांकo FPS range */
		.mmal_id = 0,
		.setter = ctrl_set_exposure,
	पूर्ण,
	अणु
		.id = V4L2_CID_EXPOSURE_METERING,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = ~0xf,
		.max = V4L2_EXPOSURE_METERING_MATRIX,
		.def = V4L2_EXPOSURE_METERING_AVERAGE,
		.step = 0,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_EXP_METERING_MODE,
		.setter = ctrl_set_metering_mode,
	पूर्ण,
	अणु
		.id = V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = ~0x3ff,
		.max = V4L2_WHITE_BALANCE_SHADE,
		.def = V4L2_WHITE_BALANCE_AUTO,
		.step = 0,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_AWB_MODE,
		.setter = ctrl_set_awb_mode,
	पूर्ण,
	अणु
		.id = V4L2_CID_RED_BALANCE,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 1,
		.max = 7999,
		.def = 1000,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_CUSTOM_AWB_GAINS,
		.setter = ctrl_set_awb_gains,
	पूर्ण,
	अणु
		.id = V4L2_CID_BLUE_BALANCE,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 1,
		.max = 7999,
		.def = 1000,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_CUSTOM_AWB_GAINS,
		.setter = ctrl_set_awb_gains,
	पूर्ण,
	अणु
		.id = V4L2_CID_COLORFX,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = 0,
		.max = V4L2_COLORFX_SET_CBCR,
		.def = V4L2_COLORFX_NONE,
		.step = 0,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_IMAGE_EFFECT,
		.setter = ctrl_set_image_effect,
	पूर्ण,
	अणु
		.id = V4L2_CID_COLORFX_CBCR,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 0xffff,
		.def = 0x8080,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_COLOUR_EFFECT,
		.setter = ctrl_set_colfx,
	पूर्ण,
	अणु
		.id = V4L2_CID_ROTATE,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 360,
		.def = 0,
		.step = 90,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_ROTATION,
		.setter = ctrl_set_rotate,
	पूर्ण,
	अणु
		.id = V4L2_CID_HFLIP,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_MIRROR,
		.setter = ctrl_set_flip,
	पूर्ण,
	अणु
		.id = V4L2_CID_VFLIP,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_MIRROR,
		.setter = ctrl_set_flip,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = 0,
		.max = V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
		.def = 0,
		.step = 0,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_RATECONTROL,
		.setter = ctrl_set_bitrate_mode,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_BITRATE,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 25 * 1000,
		.max = 25 * 1000 * 1000,
		.def = 10 * 1000 * 1000,
		.step = 25 * 1000,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_VIDEO_BIT_RATE,
		.setter = ctrl_set_bitrate,
	पूर्ण,
	अणु
		.id = V4L2_CID_JPEG_COMPRESSION_QUALITY,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 1,
		.max = 100,
		.def = 30,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_JPEG_Q_FACTOR,
		.setter = ctrl_set_image_encode_output,
	पूर्ण,
	अणु
		.id = V4L2_CID_POWER_LINE_FREQUENCY,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = 0,
		.max = V4L2_CID_POWER_LINE_FREQUENCY_AUTO,
		.def = 1,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_FLICKER_AVOID,
		.setter = ctrl_set_flicker_aव्योमance,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_VIDEO_ENCODE_INLINE_HEADER,
		.setter = ctrl_set_video_encode_param_output,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = ~(BIT(V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
			 BIT(V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE) |
			 BIT(V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
			 BIT(V4L2_MPEG_VIDEO_H264_PROखाता_HIGH)),
		.max = V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
		.def = V4L2_MPEG_VIDEO_H264_PROखाता_HIGH,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_PROखाता,
		.setter = ctrl_set_video_encode_profile_level,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		.min = ~(BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_0) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1B) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_1) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_2) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_1_3) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_1) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_2_2) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
			 BIT(V4L2_MPEG_VIDEO_H264_LEVEL_4_0)),
		.max = V4L2_MPEG_VIDEO_H264_LEVEL_4_0,
		.def = V4L2_MPEG_VIDEO_H264_LEVEL_4_0,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_PROखाता,
		.setter = ctrl_set_video_encode_profile_level,
	पूर्ण,
	अणु
		.id = V4L2_CID_SCENE_MODE,
		.type = MMAL_CONTROL_TYPE_STD_MENU,
		/* mask is computed at runसमय */
		.min = -1,
		.max = V4L2_SCENE_MODE_TEXT,
		.def = V4L2_SCENE_MODE_NONE,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_PROखाता,
		.setter = ctrl_set_scene_mode,
	पूर्ण,
	अणु
		.id = V4L2_CID_MPEG_VIDEO_H264_I_PERIOD,
		.type = MMAL_CONTROL_TYPE_STD,
		.min = 0,
		.max = 0x7FFFFFFF,
		.def = 60,
		.step = 1,
		.imenu = शून्य,
		.mmal_id = MMAL_PARAMETER_INTRAPERIOD,
		.setter = ctrl_set_video_encode_param_output,
	पूर्ण,
पूर्ण;

पूर्णांक bm2835_mmal_set_all_camera_controls(काष्ठा bm2835_mmal_dev *dev)
अणु
	पूर्णांक c;
	पूर्णांक ret = 0;

	क्रम (c = 0; c < V4L2_CTRL_COUNT; c++) अणु
		अगर ((dev->ctrls[c]) && (v4l2_ctrls[c].setter)) अणु
			ret = v4l2_ctrls[c].setter(dev, dev->ctrls[c],
						   &v4l2_ctrls[c]);
			अगर (ret) अणु
				v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
					 "Failed when setting default values for ctrl %d\n",
					 c);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक set_framerate_params(काष्ठा bm2835_mmal_dev *dev)
अणु
	काष्ठा mmal_parameter_fps_range fps_range;
	पूर्णांक ret;

	fps_range.fps_high.num = dev->capture.समयperframe.denominator;
	fps_range.fps_high.den = dev->capture.समयperframe.numerator;

	अगर ((dev->exposure_mode_active != MMAL_PARAM_EXPOSUREMODE_OFF) &&
	    (dev->exp_स्वतः_priority)) अणु
		/* Variable FPS. Define min FPS as 1fps. */
		fps_range.fps_low.num = 1;
		fps_range.fps_low.den = 1;
	पूर्ण अन्यथा अणु
		/* Fixed FPS - set min and max to be the same */
		fps_range.fps_low.num = fps_range.fps_high.num;
		fps_range.fps_low.den = fps_range.fps_high.den;
	पूर्ण

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Set fps range to %d/%d to %d/%d\n",
		 fps_range.fps_low.num,
		 fps_range.fps_low.den,
		 fps_range.fps_high.num,
		 fps_range.fps_high.den);

	ret = vchiq_mmal_port_parameter_set(dev->instance,
					    &dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW],
					    MMAL_PARAMETER_FPS_RANGE,
					    &fps_range, माप(fps_range));
	ret += vchiq_mmal_port_parameter_set(dev->instance,
					     &dev->component[COMP_CAMERA]->output[CAM_PORT_VIDEO],
					     MMAL_PARAMETER_FPS_RANGE,
					     &fps_range, माप(fps_range));
	ret += vchiq_mmal_port_parameter_set(dev->instance,
					     &dev->component[COMP_CAMERA]->output[CAM_PORT_CAPTURE],
					     MMAL_PARAMETER_FPS_RANGE,
					     &fps_range, माप(fps_range));
	अगर (ret)
		v4l2_dbg(0, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Failed to set fps ret %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक bm2835_mmal_init_controls(काष्ठा bm2835_mmal_dev *dev,
			      काष्ठा v4l2_ctrl_handler *hdl)
अणु
	पूर्णांक c;
	स्थिर काष्ठा bm2835_mmal_v4l2_ctrl *ctrl;

	v4l2_ctrl_handler_init(hdl, V4L2_CTRL_COUNT);

	क्रम (c = 0; c < V4L2_CTRL_COUNT; c++) अणु
		ctrl = &v4l2_ctrls[c];

		चयन (ctrl->type) अणु
		हाल MMAL_CONTROL_TYPE_STD:
			dev->ctrls[c] =
				v4l2_ctrl_new_std(hdl,
						  &bm2835_mmal_ctrl_ops,
						  ctrl->id, ctrl->min,
						  ctrl->max, ctrl->step,
						  ctrl->def);
			अवरोध;

		हाल MMAL_CONTROL_TYPE_STD_MENU:
		अणु
			u64 mask = ctrl->min;

			अगर (ctrl->id == V4L2_CID_SCENE_MODE) अणु
				/* Special handling to work out the mask
				 * value based on the scene_configs array
				 * at runसमय. Reduces the chance of
				 * mismatches.
				 */
				पूर्णांक i;

				mask = BIT(V4L2_SCENE_MODE_NONE);
				क्रम (i = 0;
				     i < ARRAY_SIZE(scene_configs);
				     i++) अणु
					mask |= BIT(scene_configs[i].v4l2_scene);
				पूर्ण
				mask = ~mask;
			पूर्ण

			dev->ctrls[c] =
				v4l2_ctrl_new_std_menu(hdl,
						       &bm2835_mmal_ctrl_ops,
						       ctrl->id, ctrl->max,
						       mask, ctrl->def);
			अवरोध;
		पूर्ण

		हाल MMAL_CONTROL_TYPE_INT_MENU:
			dev->ctrls[c] =
				v4l2_ctrl_new_पूर्णांक_menu(hdl,
						       &bm2835_mmal_ctrl_ops,
						       ctrl->id, ctrl->max,
						       ctrl->def, ctrl->imenu);
			अवरोध;

		हाल MMAL_CONTROL_TYPE_CLUSTER:
			/* skip this entry when स्थिरructing controls */
			जारी;
		पूर्ण

		अगर (hdl->error)
			अवरोध;

		dev->ctrls[c]->priv = (व्योम *)ctrl;
	पूर्ण

	अगर (hdl->error) अणु
		pr_err("error adding control %d/%d id 0x%x\n", c,
		       V4L2_CTRL_COUNT, ctrl->id);
		वापस hdl->error;
	पूर्ण

	क्रम (c = 0; c < V4L2_CTRL_COUNT; c++) अणु
		ctrl = &v4l2_ctrls[c];

		चयन (ctrl->type) अणु
		हाल MMAL_CONTROL_TYPE_CLUSTER:
			v4l2_ctrl_स्वतः_cluster(ctrl->min,
					       &dev->ctrls[c + 1],
					       ctrl->max,
					       ctrl->def);
			अवरोध;

		हाल MMAL_CONTROL_TYPE_STD:
		हाल MMAL_CONTROL_TYPE_STD_MENU:
		हाल MMAL_CONTROL_TYPE_INT_MENU:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
