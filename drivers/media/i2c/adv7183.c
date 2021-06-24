<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adv7183.c Analog Devices ADV7183 video decoder driver
 *
 * Copyright (c) 2011 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/adv7183.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#समावेश "adv7183_regs.h"

काष्ठा adv7183 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;

	v4l2_std_id std; /* Current set standard */
	u32 input;
	u32 output;
	अचिन्हित reset_pin;
	अचिन्हित oe_pin;
	काष्ठा v4l2_mbus_framefmt fmt;
पूर्ण;

/* EXAMPLES USING 27 MHz CLOCK
 * Mode 1 CVBS Input (Composite Video on AIN5)
 * All standards are supported through स्वतःdetect, 8-bit, 4:2:2, ITU-R BT.656 output on P15 to P8.
 */
अटल स्थिर अचिन्हित अक्षर adv7183_init_regs[] = अणु
	ADV7183_IN_CTRL, 0x04,           /* CVBS input on AIN5 */
	ADV7183_DIGI_CLAMP_CTRL_1, 0x00, /* Slow करोwn digital clamps */
	ADV7183_SHAP_FILT_CTRL, 0x41,    /* Set CSFM to SH1 */
	ADV7183_ADC_CTRL, 0x16,          /* Power करोwn ADC 1 and ADC 2 */
	ADV7183_CTI_DNR_CTRL_4, 0x04,    /* Set DNR threshold to 4 क्रम flat response */
	/* ADI recommended programming sequence */
	ADV7183_ADI_CTRL, 0x80,
	ADV7183_CTI_DNR_CTRL_4, 0x20,
	0x52, 0x18,
	0x58, 0xED,
	0x77, 0xC5,
	0x7C, 0x93,
	0x7D, 0x00,
	0xD0, 0x48,
	0xD5, 0xA0,
	0xD7, 0xEA,
	ADV7183_SD_SATURATION_CR, 0x3E,
	ADV7183_PAL_V_END, 0x3E,
	ADV7183_PAL_F_TOGGLE, 0x0F,
	ADV7183_ADI_CTRL, 0x00,
पूर्ण;

अटल अंतरभूत काष्ठा adv7183 *to_adv7183(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा adv7183, sd);
पूर्ण
अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा adv7183, hdl)->sd;
पूर्ण

अटल अंतरभूत पूर्णांक adv7183_पढ़ो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक adv7183_ग_लिखो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
				अचिन्हित अक्षर value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल पूर्णांक adv7183_ग_लिखोregs(काष्ठा v4l2_subdev *sd,
		स्थिर अचिन्हित अक्षर *regs, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित अक्षर reg, data;
	अचिन्हित पूर्णांक cnt = 0;

	अगर (num & 0x1) अणु
		v4l2_err(sd, "invalid regs array\n");
		वापस -1;
	पूर्ण

	जबतक (cnt < num) अणु
		reg = *regs++;
		data = *regs++;
		cnt += 2;

		adv7183_ग_लिखो(sd, reg, data);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);

	v4l2_info(sd, "adv7183: Input control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_IN_CTRL));
	v4l2_info(sd, "adv7183: Video selection = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_VD_SEL));
	v4l2_info(sd, "adv7183: Output control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_OUT_CTRL));
	v4l2_info(sd, "adv7183: Extended output control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_EXT_OUT_CTRL));
	v4l2_info(sd, "adv7183: Autodetect enable = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_AUTO_DET_EN));
	v4l2_info(sd, "adv7183: Contrast = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_CONTRAST));
	v4l2_info(sd, "adv7183: Brightness = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_BRIGHTNESS));
	v4l2_info(sd, "adv7183: Hue = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_HUE));
	v4l2_info(sd, "adv7183: Default value Y = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_DEF_Y));
	v4l2_info(sd, "adv7183: Default value C = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_DEF_C));
	v4l2_info(sd, "adv7183: ADI control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_ADI_CTRL));
	v4l2_info(sd, "adv7183: Power Management = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_POW_MANAGE));
	v4l2_info(sd, "adv7183: Status 1 2 and 3 = 0x%02x 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_STATUS_1),
			adv7183_पढ़ो(sd, ADV7183_STATUS_2),
			adv7183_पढ़ो(sd, ADV7183_STATUS_3));
	v4l2_info(sd, "adv7183: Ident = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_IDENT));
	v4l2_info(sd, "adv7183: Analog clamp control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_ANAL_CLAMP_CTRL));
	v4l2_info(sd, "adv7183: Digital clamp control 1 = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_DIGI_CLAMP_CTRL_1));
	v4l2_info(sd, "adv7183: Shaping filter control 1 and 2 = 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_SHAP_FILT_CTRL),
			adv7183_पढ़ो(sd, ADV7183_SHAP_FILT_CTRL_2));
	v4l2_info(sd, "adv7183: Comb filter control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_COMB_FILT_CTRL));
	v4l2_info(sd, "adv7183: ADI control 2 = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_ADI_CTRL_2));
	v4l2_info(sd, "adv7183: Pixel delay control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_PIX_DELAY_CTRL));
	v4l2_info(sd, "adv7183: Misc gain control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_MISC_GAIN_CTRL));
	v4l2_info(sd, "adv7183: AGC mode control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_AGC_MODE_CTRL));
	v4l2_info(sd, "adv7183: Chroma gain control 1 and 2 = 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_CHRO_GAIN_CTRL_1),
			adv7183_पढ़ो(sd, ADV7183_CHRO_GAIN_CTRL_2));
	v4l2_info(sd, "adv7183: Luma gain control 1 and 2 = 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_LUMA_GAIN_CTRL_1),
			adv7183_पढ़ो(sd, ADV7183_LUMA_GAIN_CTRL_2));
	v4l2_info(sd, "adv7183: Vsync field control 1 2 and 3 = 0x%02x 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_VS_FIELD_CTRL_1),
			adv7183_पढ़ो(sd, ADV7183_VS_FIELD_CTRL_2),
			adv7183_पढ़ो(sd, ADV7183_VS_FIELD_CTRL_3));
	v4l2_info(sd, "adv7183: Hsync position control 1 2 and 3 = 0x%02x 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_HS_POS_CTRL_1),
			adv7183_पढ़ो(sd, ADV7183_HS_POS_CTRL_2),
			adv7183_पढ़ो(sd, ADV7183_HS_POS_CTRL_3));
	v4l2_info(sd, "adv7183: Polarity = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_POLARITY));
	v4l2_info(sd, "adv7183: ADC control = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_ADC_CTRL));
	v4l2_info(sd, "adv7183: SD offset Cb and Cr = 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_SD_OFFSET_CB),
			adv7183_पढ़ो(sd, ADV7183_SD_OFFSET_CR));
	v4l2_info(sd, "adv7183: SD saturation Cb and Cr = 0x%02x 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_SD_SATURATION_CB),
			adv7183_पढ़ो(sd, ADV7183_SD_SATURATION_CR));
	v4l2_info(sd, "adv7183: Drive strength = 0x%02x\n",
			adv7183_पढ़ो(sd, ADV7183_DRIVE_STR));
	v4l2_ctrl_handler_log_status(&decoder->hdl, sd->name);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);

	*std = decoder->std;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);
	पूर्णांक reg;

	reg = adv7183_पढ़ो(sd, ADV7183_IN_CTRL) & 0xF;
	अगर (std == V4L2_STD_PAL_60)
		reg |= 0x60;
	अन्यथा अगर (std == V4L2_STD_NTSC_443)
		reg |= 0x70;
	अन्यथा अगर (std == V4L2_STD_PAL_N)
		reg |= 0x90;
	अन्यथा अगर (std == V4L2_STD_PAL_M)
		reg |= 0xA0;
	अन्यथा अगर (std == V4L2_STD_PAL_Nc)
		reg |= 0xC0;
	अन्यथा अगर (std & V4L2_STD_PAL)
		reg |= 0x80;
	अन्यथा अगर (std & V4L2_STD_NTSC)
		reg |= 0x50;
	अन्यथा अगर (std & V4L2_STD_SECAM)
		reg |= 0xE0;
	अन्यथा
		वापस -EINVAL;
	adv7183_ग_लिखो(sd, ADV7183_IN_CTRL, reg);

	decoder->std = std;

	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	पूर्णांक reg;

	reg = adv7183_पढ़ो(sd, ADV7183_POW_MANAGE) | 0x80;
	adv7183_ग_लिखो(sd, ADV7183_POW_MANAGE, reg);
	/* रुको 5ms beक्रमe any further i2c ग_लिखोs are perक्रमmed */
	usleep_range(5000, 10000);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_s_routing(काष्ठा v4l2_subdev *sd,
				u32 input, u32 output, u32 config)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);
	पूर्णांक reg;

	अगर ((input > ADV7183_COMPONENT1) || (output > ADV7183_16BIT_OUT))
		वापस -EINVAL;

	अगर (input != decoder->input) अणु
		decoder->input = input;
		reg = adv7183_पढ़ो(sd, ADV7183_IN_CTRL) & 0xF0;
		चयन (input) अणु
		हाल ADV7183_COMPOSITE1:
			reg |= 0x1;
			अवरोध;
		हाल ADV7183_COMPOSITE2:
			reg |= 0x2;
			अवरोध;
		हाल ADV7183_COMPOSITE3:
			reg |= 0x3;
			अवरोध;
		हाल ADV7183_COMPOSITE4:
			reg |= 0x4;
			अवरोध;
		हाल ADV7183_COMPOSITE5:
			reg |= 0x5;
			अवरोध;
		हाल ADV7183_COMPOSITE6:
			reg |= 0xB;
			अवरोध;
		हाल ADV7183_COMPOSITE7:
			reg |= 0xC;
			अवरोध;
		हाल ADV7183_COMPOSITE8:
			reg |= 0xD;
			अवरोध;
		हाल ADV7183_COMPOSITE9:
			reg |= 0xE;
			अवरोध;
		हाल ADV7183_COMPOSITE10:
			reg |= 0xF;
			अवरोध;
		हाल ADV7183_SVIDEO0:
			reg |= 0x6;
			अवरोध;
		हाल ADV7183_SVIDEO1:
			reg |= 0x7;
			अवरोध;
		हाल ADV7183_SVIDEO2:
			reg |= 0x8;
			अवरोध;
		हाल ADV7183_COMPONENT0:
			reg |= 0x9;
			अवरोध;
		हाल ADV7183_COMPONENT1:
			reg |= 0xA;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		adv7183_ग_लिखो(sd, ADV7183_IN_CTRL, reg);
	पूर्ण

	अगर (output != decoder->output) अणु
		decoder->output = output;
		reg = adv7183_पढ़ो(sd, ADV7183_OUT_CTRL) & 0xC0;
		चयन (output) अणु
		हाल ADV7183_16BIT_OUT:
			reg |= 0x9;
			अवरोध;
		शेष:
			reg |= 0xC;
			अवरोध;
		पूर्ण
		adv7183_ग_लिखो(sd, ADV7183_OUT_CTRL, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	पूर्णांक val = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		अगर (val < 0)
			val = 127 - val;
		adv7183_ग_लिखो(sd, ADV7183_BRIGHTNESS, val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		adv7183_ग_लिखो(sd, ADV7183_CONTRAST, val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		adv7183_ग_लिखो(sd, ADV7183_SD_SATURATION_CB, val >> 8);
		adv7183_ग_लिखो(sd, ADV7183_SD_SATURATION_CR, (val & 0xFF));
		अवरोध;
	हाल V4L2_CID_HUE:
		adv7183_ग_लिखो(sd, ADV7183_SD_OFFSET_CB, val >> 8);
		adv7183_ग_लिखो(sd, ADV7183_SD_OFFSET_CR, (val & 0xFF));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);
	पूर्णांक reg;

	/* enable स्वतःdetection block */
	reg = adv7183_पढ़ो(sd, ADV7183_IN_CTRL) & 0xF;
	adv7183_ग_लिखो(sd, ADV7183_IN_CTRL, reg);

	/* रुको स्वतःdetection चयन */
	mdelay(10);

	/* get स्वतःdetection result */
	reg = adv7183_पढ़ो(sd, ADV7183_STATUS_1);
	चयन ((reg >> 0x4) & 0x7) अणु
	हाल 0:
		*std &= V4L2_STD_NTSC;
		अवरोध;
	हाल 1:
		*std &= V4L2_STD_NTSC_443;
		अवरोध;
	हाल 2:
		*std &= V4L2_STD_PAL_M;
		अवरोध;
	हाल 3:
		*std &= V4L2_STD_PAL_60;
		अवरोध;
	हाल 4:
		*std &= V4L2_STD_PAL;
		अवरोध;
	हाल 5:
		*std &= V4L2_STD_SECAM;
		अवरोध;
	हाल 6:
		*std &= V4L2_STD_PAL_Nc;
		अवरोध;
	हाल 7:
		*std &= V4L2_STD_SECAM;
		अवरोध;
	शेष:
		*std = V4L2_STD_UNKNOWN;
		अवरोध;
	पूर्ण

	/* after std detection, ग_लिखो back user set std */
	adv7183_s_std(sd, decoder->std);
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	पूर्णांक reg;

	*status = V4L2_IN_ST_NO_SIGNAL;
	reg = adv7183_पढ़ो(sd, ADV7183_STATUS_1);
	अगर (reg < 0)
		वापस reg;
	अगर (reg & 0x1)
		*status = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	अगर (decoder->std & V4L2_STD_525_60) अणु
		fmt->field = V4L2_FIELD_SEQ_TB;
		fmt->width = 720;
		fmt->height = 480;
	पूर्ण अन्यथा अणु
		fmt->field = V4L2_FIELD_SEQ_BT;
		fmt->width = 720;
		fmt->height = 576;
	पूर्ण
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		decoder->fmt = *fmt;
	अन्यथा
		cfg->try_fmt = *fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	क्रमmat->क्रमmat = decoder->fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv7183 *decoder = to_adv7183(sd);

	अगर (enable)
		gpio_set_value(decoder->oe_pin, 0);
	अन्यथा
		gpio_set_value(decoder->oe_pin, 1);
	udelay(1);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक adv7183_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = adv7183_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	adv7183_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_ops adv7183_ctrl_ops = अणु
	.s_ctrl = adv7183_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops adv7183_core_ops = अणु
	.log_status = adv7183_log_status,
	.reset = adv7183_reset,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = adv7183_g_रेजिस्टर,
	.s_रेजिस्टर = adv7183_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv7183_video_ops = अणु
	.g_std = adv7183_g_std,
	.s_std = adv7183_s_std,
	.s_routing = adv7183_s_routing,
	.querystd = adv7183_querystd,
	.g_input_status = adv7183_g_input_status,
	.s_stream = adv7183_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv7183_pad_ops = अणु
	.क्रमागत_mbus_code = adv7183_क्रमागत_mbus_code,
	.get_fmt = adv7183_get_fmt,
	.set_fmt = adv7183_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops adv7183_ops = अणु
	.core = &adv7183_core_ops,
	.video = &adv7183_video_ops,
	.pad = &adv7183_pad_ops,
पूर्ण;

अटल पूर्णांक adv7183_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adv7183 *decoder;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक ret;
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	स्थिर अचिन्हित *pin_array;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	pin_array = client->dev.platक्रमm_data;
	अगर (pin_array == शून्य)
		वापस -EINVAL;

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (decoder == शून्य)
		वापस -ENOMEM;

	decoder->reset_pin = pin_array[0];
	decoder->oe_pin = pin_array[1];

	अगर (devm_gpio_request_one(&client->dev, decoder->reset_pin,
				  GPIOF_OUT_INIT_LOW, "ADV7183 Reset")) अणु
		v4l_err(client, "failed to request GPIO %d\n", decoder->reset_pin);
		वापस -EBUSY;
	पूर्ण

	अगर (devm_gpio_request_one(&client->dev, decoder->oe_pin,
				  GPIOF_OUT_INIT_HIGH,
				  "ADV7183 Output Enable")) अणु
		v4l_err(client, "failed to request GPIO %d\n", decoder->oe_pin);
		वापस -EBUSY;
	पूर्ण

	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &adv7183_ops);

	hdl = &decoder->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &adv7183_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &adv7183_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0xFF, 1, 0x80);
	v4l2_ctrl_new_std(hdl, &adv7183_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0xFFFF, 1, 0x8080);
	v4l2_ctrl_new_std(hdl, &adv7183_ctrl_ops,
			V4L2_CID_HUE, 0, 0xFFFF, 1, 0x8080);
	/* hook the control handler पूर्णांकo the driver */
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		ret = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	/* v4l2 करोesn't support an स्वतःdetect standard, pick PAL as शेष */
	decoder->std = V4L2_STD_PAL;
	decoder->input = ADV7183_COMPOSITE4;
	decoder->output = ADV7183_8BIT_OUT;

	/* reset chip */
	/* reset pulse width at least 5ms */
	mdelay(10);
	gpio_set_value(decoder->reset_pin, 1);
	/* रुको 5ms beक्रमe any further i2c ग_लिखोs are perक्रमmed */
	mdelay(5);

	adv7183_ग_लिखोregs(sd, adv7183_init_regs, ARRAY_SIZE(adv7183_init_regs));
	adv7183_s_std(sd, decoder->std);
	fmt.क्रमmat.width = 720;
	fmt.क्रमmat.height = 576;
	adv7183_set_fmt(sd, शून्य, &fmt);

	/* initialize the hardware to the शेष control values */
	ret = v4l2_ctrl_handler_setup(hdl);
	अगर (ret) अणु
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv7183_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adv7183_id[] = अणु
	अणु"adv7183", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, adv7183_id);

अटल काष्ठा i2c_driver adv7183_driver = अणु
	.driver = अणु
		.name   = "adv7183",
	पूर्ण,
	.probe          = adv7183_probe,
	.हटाओ         = adv7183_हटाओ,
	.id_table       = adv7183_id,
पूर्ण;

module_i2c_driver(adv7183_driver);

MODULE_DESCRIPTION("Analog Devices ADV7183 video decoder driver");
MODULE_AUTHOR("Scott Jiang <Scott.Jiang.Linux@gmail.com>");
MODULE_LICENSE("GPL v2");
