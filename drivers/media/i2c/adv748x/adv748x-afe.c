<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Analog Devices ADV748X 8 channel analog front end (AFE) receiver
 * with standard definition processor (SDP)
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/v4l2-dv-timings.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "adv748x.h"

/* -----------------------------------------------------------------------------
 * SDP
 */

#घोषणा ADV748X_AFE_STD_AD_PAL_BG_NTSC_J_SECAM		0x0
#घोषणा ADV748X_AFE_STD_AD_PAL_BG_NTSC_J_SECAM_PED	0x1
#घोषणा ADV748X_AFE_STD_AD_PAL_N_NTSC_J_SECAM		0x2
#घोषणा ADV748X_AFE_STD_AD_PAL_N_NTSC_M_SECAM		0x3
#घोषणा ADV748X_AFE_STD_NTSC_J				0x4
#घोषणा ADV748X_AFE_STD_NTSC_M				0x5
#घोषणा ADV748X_AFE_STD_PAL60				0x6
#घोषणा ADV748X_AFE_STD_NTSC_443			0x7
#घोषणा ADV748X_AFE_STD_PAL_BG				0x8
#घोषणा ADV748X_AFE_STD_PAL_N				0x9
#घोषणा ADV748X_AFE_STD_PAL_M				0xa
#घोषणा ADV748X_AFE_STD_PAL_M_PED			0xb
#घोषणा ADV748X_AFE_STD_PAL_COMB_N			0xc
#घोषणा ADV748X_AFE_STD_PAL_COMB_N_PED			0xd
#घोषणा ADV748X_AFE_STD_PAL_SECAM			0xe
#घोषणा ADV748X_AFE_STD_PAL_SECAM_PED			0xf

अटल पूर्णांक adv748x_afe_पढ़ो_ro_map(काष्ठा adv748x_state *state, u8 reg)
अणु
	पूर्णांक ret;

	/* Select SDP Read-Only Main Map */
	ret = sdp_ग_लिखो(state, ADV748X_SDP_MAP_SEL,
			ADV748X_SDP_MAP_SEL_RO_MAIN);
	अगर (ret < 0)
		वापस ret;

	वापस sdp_पढ़ो(state, reg);
पूर्ण

अटल पूर्णांक adv748x_afe_status(काष्ठा adv748x_afe *afe, u32 *संकेत,
			      v4l2_std_id *std)
अणु
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	पूर्णांक info;

	/* Read status from reg 0x10 of SDP RO Map */
	info = adv748x_afe_पढ़ो_ro_map(state, ADV748X_SDP_RO_10);
	अगर (info < 0)
		वापस info;

	अगर (संकेत)
		*संकेत = info & ADV748X_SDP_RO_10_IN_LOCK ?
				0 : V4L2_IN_ST_NO_SIGNAL;

	अगर (!std)
		वापस 0;

	/* Standard not valid अगर there is no संकेत */
	अगर (!(info & ADV748X_SDP_RO_10_IN_LOCK)) अणु
		*std = V4L2_STD_UNKNOWN;
		वापस 0;
	पूर्ण

	चयन (info & 0x70) अणु
	हाल 0x00:
		*std = V4L2_STD_NTSC;
		अवरोध;
	हाल 0x10:
		*std = V4L2_STD_NTSC_443;
		अवरोध;
	हाल 0x20:
		*std = V4L2_STD_PAL_M;
		अवरोध;
	हाल 0x30:
		*std = V4L2_STD_PAL_60;
		अवरोध;
	हाल 0x40:
		*std = V4L2_STD_PAL;
		अवरोध;
	हाल 0x50:
		*std = V4L2_STD_SECAM;
		अवरोध;
	हाल 0x60:
		*std = V4L2_STD_PAL_Nc | V4L2_STD_PAL_N;
		अवरोध;
	हाल 0x70:
		*std = V4L2_STD_SECAM;
		अवरोध;
	शेष:
		*std = V4L2_STD_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adv748x_afe_fill_क्रमmat(काष्ठा adv748x_afe *afe,
				    काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	स_रखो(fmt, 0, माप(*fmt));

	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	fmt->field = V4L2_FIELD_ALTERNATE;

	fmt->width = 720;
	fmt->height = afe->curr_norm & V4L2_STD_525_60 ? 480 : 576;

	/* Field height */
	fmt->height /= 2;
पूर्ण

अटल पूर्णांक adv748x_afe_std(v4l2_std_id std)
अणु
	अगर (std == V4L2_STD_PAL_60)
		वापस ADV748X_AFE_STD_PAL60;
	अगर (std == V4L2_STD_NTSC_443)
		वापस ADV748X_AFE_STD_NTSC_443;
	अगर (std == V4L2_STD_PAL_N)
		वापस ADV748X_AFE_STD_PAL_N;
	अगर (std == V4L2_STD_PAL_M)
		वापस ADV748X_AFE_STD_PAL_M;
	अगर (std == V4L2_STD_PAL_Nc)
		वापस ADV748X_AFE_STD_PAL_COMB_N;
	अगर (std & V4L2_STD_NTSC)
		वापस ADV748X_AFE_STD_NTSC_M;
	अगर (std & V4L2_STD_PAL)
		वापस ADV748X_AFE_STD_PAL_BG;
	अगर (std & V4L2_STD_SECAM)
		वापस ADV748X_AFE_STD_PAL_SECAM;

	वापस -EINVAL;
पूर्ण

अटल व्योम adv748x_afe_set_video_standard(काष्ठा adv748x_state *state,
					  पूर्णांक sdpstd)
अणु
	sdp_clrset(state, ADV748X_SDP_VID_SEL, ADV748X_SDP_VID_SEL_MASK,
		   (sdpstd & 0xf) << ADV748X_SDP_VID_SEL_SHIFT);
पूर्ण

पूर्णांक adv748x_afe_s_input(काष्ठा adv748x_afe *afe, अचिन्हित पूर्णांक input)
अणु
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);

	वापस sdp_ग_लिखो(state, ADV748X_SDP_INSEL, input);
पूर्ण

अटल पूर्णांक adv748x_afe_g_pixelaspect(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_fract *aspect)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);

	अगर (afe->curr_norm & V4L2_STD_525_60) अणु
		aspect->numerator = 11;
		aspect->denominator = 10;
	पूर्ण अन्यथा अणु
		aspect->numerator = 54;
		aspect->denominator = 59;
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * v4l2_subdev_video_ops
 */

अटल पूर्णांक adv748x_afe_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);

	*norm = afe->curr_norm;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_afe_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	पूर्णांक afe_std = adv748x_afe_std(std);

	अगर (afe_std < 0)
		वापस afe_std;

	mutex_lock(&state->mutex);

	adv748x_afe_set_video_standard(state, afe_std);
	afe->curr_norm = std;

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_afe_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	पूर्णांक afe_std;
	पूर्णांक ret;

	mutex_lock(&state->mutex);

	अगर (afe->streaming) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	/* Set स्वतः detect mode */
	adv748x_afe_set_video_standard(state,
				       ADV748X_AFE_STD_AD_PAL_BG_NTSC_J_SECAM);

	msleep(100);

	/* Read detected standard */
	ret = adv748x_afe_status(afe, शून्य, std);

	afe_std = adv748x_afe_std(afe->curr_norm);
	अगर (afe_std < 0)
		जाओ unlock;

	/* Restore original state */
	adv748x_afe_set_video_standard(state, afe_std);

unlock:
	mutex_unlock(&state->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_afe_g_tvnorms(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	*norm = V4L2_STD_ALL;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_afe_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	पूर्णांक ret;

	mutex_lock(&state->mutex);

	ret = adv748x_afe_status(afe, status, शून्य);

	mutex_unlock(&state->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_afe_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	u32 संकेत = V4L2_IN_ST_NO_SIGNAL;
	पूर्णांक ret;

	mutex_lock(&state->mutex);

	अगर (enable) अणु
		ret = adv748x_afe_s_input(afe, afe->input);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	ret = adv748x_tx_घातer(afe->tx, enable);
	अगर (ret)
		जाओ unlock;

	afe->streaming = enable;

	adv748x_afe_status(afe, &संकेत, शून्य);
	अगर (संकेत != V4L2_IN_ST_NO_SIGNAL)
		adv_dbg(state, "Detected SDP signal\n");
	अन्यथा
		adv_dbg(state, "Couldn't detect SDP video signal\n");

unlock:
	mutex_unlock(&state->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv748x_afe_video_ops = अणु
	.g_std = adv748x_afe_g_std,
	.s_std = adv748x_afe_s_std,
	.querystd = adv748x_afe_querystd,
	.g_tvnorms = adv748x_afe_g_tvnorms,
	.g_input_status = adv748x_afe_g_input_status,
	.s_stream = adv748x_afe_s_stream,
	.g_pixelaspect = adv748x_afe_g_pixelaspect,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_pad_ops
 */

अटल पूर्णांक adv748x_afe_propagate_pixelrate(काष्ठा adv748x_afe *afe)
अणु
	काष्ठा v4l2_subdev *tx;

	tx = adv748x_get_remote_sd(&afe->pads[ADV748X_AFE_SOURCE]);
	अगर (!tx)
		वापस -ENOLINK;

	/*
	 * The ADV748x ADC sampling frequency is twice the बाह्यally supplied
	 * घड़ी whose frequency is required to be 28.63636 MHz. It oversamples
	 * with a factor of 4 resulting in a pixel rate of 14.3180180 MHz.
	 */
	वापस adv748x_csi2_set_pixelrate(tx, 14318180);
पूर्ण

अटल पूर्णांक adv748x_afe_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_afe_get_क्रमmat(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा adv748x_afe *afe = adv748x_sd_to_afe(sd);
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;

	/* It makes no sense to get the क्रमmat of the analog sink pads */
	अगर (sdक्रमmat->pad != ADV748X_AFE_SOURCE)
		वापस -EINVAL;

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mbusक्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, sdक्रमmat->pad);
		sdक्रमmat->क्रमmat = *mbusक्रमmat;
	पूर्ण अन्यथा अणु
		adv748x_afe_fill_क्रमmat(afe, &sdक्रमmat->क्रमmat);
		adv748x_afe_propagate_pixelrate(afe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_afe_set_क्रमmat(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;

	/* It makes no sense to get the क्रमmat of the analog sink pads */
	अगर (sdक्रमmat->pad != ADV748X_AFE_SOURCE)
		वापस -EINVAL;

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस adv748x_afe_get_क्रमmat(sd, cfg, sdक्रमmat);

	mbusक्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, sdक्रमmat->pad);
	*mbusक्रमmat = sdक्रमmat->क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv748x_afe_pad_ops = अणु
	.क्रमागत_mbus_code = adv748x_afe_क्रमागत_mbus_code,
	.set_fmt = adv748x_afe_set_क्रमmat,
	.get_fmt = adv748x_afe_get_क्रमmat,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_ops
 */

अटल स्थिर काष्ठा v4l2_subdev_ops adv748x_afe_ops = अणु
	.video = &adv748x_afe_video_ops,
	.pad = &adv748x_afe_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Controls
 */

अटल स्थिर अक्षर * स्थिर afe_ctrl_frp_menu[] = अणु
	"Disabled",
	"Solid Blue",
	"Color Bars",
	"Grey Ramp",
	"Cb Ramp",
	"Cr Ramp",
	"Boundary"
पूर्ण;

अटल पूर्णांक adv748x_afe_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा adv748x_afe *afe = adv748x_ctrl_to_afe(ctrl);
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	bool enable;
	पूर्णांक ret;

	ret = sdp_ग_लिखो(state, 0x0e, 0x00);
	अगर (ret < 0)
		वापस ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = sdp_ग_लिखो(state, ADV748X_SDP_BRI, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		/* Hue is inverted according to HSL अक्षरt */
		ret = sdp_ग_लिखो(state, ADV748X_SDP_HUE, -ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = sdp_ग_लिखो(state, ADV748X_SDP_CON, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = sdp_ग_लिखो(state, ADV748X_SDP_SD_SAT_U, ctrl->val);
		अगर (ret)
			अवरोध;
		ret = sdp_ग_लिखो(state, ADV748X_SDP_SD_SAT_V, ctrl->val);
		अवरोध;
	हाल V4L2_CID_TEST_PATTERN:
		enable = !!ctrl->val;

		/* Enable/Disable Color bar test patterns */
		ret = sdp_clrset(state, ADV748X_SDP_DEF, ADV748X_SDP_DEF_VAL_EN,
				enable);
		अगर (ret)
			अवरोध;
		ret = sdp_clrset(state, ADV748X_SDP_FRP, ADV748X_SDP_FRP_MASK,
				enable ? ctrl->val - 1 : 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv748x_afe_ctrl_ops = अणु
	.s_ctrl = adv748x_afe_s_ctrl,
पूर्ण;

अटल पूर्णांक adv748x_afe_init_controls(काष्ठा adv748x_afe *afe)
अणु
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);

	v4l2_ctrl_handler_init(&afe->ctrl_hdl, 5);

	/* Use our mutex क्रम the controls */
	afe->ctrl_hdl.lock = &state->mutex;

	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, ADV748X_SDP_BRI_MIN,
			  ADV748X_SDP_BRI_MAX, 1, ADV748X_SDP_BRI_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_CONTRAST, ADV748X_SDP_CON_MIN,
			  ADV748X_SDP_CON_MAX, 1, ADV748X_SDP_CON_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_SATURATION, ADV748X_SDP_SAT_MIN,
			  ADV748X_SDP_SAT_MAX, 1, ADV748X_SDP_SAT_DEF);
	v4l2_ctrl_new_std(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
			  V4L2_CID_HUE, ADV748X_SDP_HUE_MIN,
			  ADV748X_SDP_HUE_MAX, 1, ADV748X_SDP_HUE_DEF);

	v4l2_ctrl_new_std_menu_items(&afe->ctrl_hdl, &adv748x_afe_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(afe_ctrl_frp_menu) - 1,
				     0, 0, afe_ctrl_frp_menu);

	afe->sd.ctrl_handler = &afe->ctrl_hdl;
	अगर (afe->ctrl_hdl.error) अणु
		v4l2_ctrl_handler_मुक्त(&afe->ctrl_hdl);
		वापस afe->ctrl_hdl.error;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&afe->ctrl_hdl);
पूर्ण

पूर्णांक adv748x_afe_init(काष्ठा adv748x_afe *afe)
अणु
	काष्ठा adv748x_state *state = adv748x_afe_to_state(afe);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	afe->input = 0;
	afe->streaming = false;
	afe->curr_norm = V4L2_STD_NTSC_M;

	adv748x_subdev_init(&afe->sd, state, &adv748x_afe_ops,
			    MEDIA_ENT_F_ATV_DECODER, "afe");

	/* Identअगरy the first connector found as a शेष input अगर set */
	क्रम (i = ADV748X_PORT_AIN0; i <= ADV748X_PORT_AIN7; i++) अणु
		/* Inमाला_दो and ports are 1-indexed to match the data sheet */
		अगर (state->endpoपूर्णांकs[i]) अणु
			afe->input = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Entity pads and sinks are 0-indexed to match the pads */
	क्रम (i = ADV748X_AFE_SINK_AIN0; i <= ADV748X_AFE_SINK_AIN7; i++)
		afe->pads[i].flags = MEDIA_PAD_FL_SINK;

	afe->pads[ADV748X_AFE_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&afe->sd.entity, ADV748X_AFE_NR_PADS,
			afe->pads);
	अगर (ret)
		वापस ret;

	ret = adv748x_afe_init_controls(afe);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	media_entity_cleanup(&afe->sd.entity);

	वापस ret;
पूर्ण

व्योम adv748x_afe_cleanup(काष्ठा adv748x_afe *afe)
अणु
	v4l2_device_unरेजिस्टर_subdev(&afe->sd);
	media_entity_cleanup(&afe->sd.entity);
	v4l2_ctrl_handler_मुक्त(&afe->ctrl_hdl);
पूर्ण
