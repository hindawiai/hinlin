<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Microchip Corporation.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा REG_OUTSIZE_LSB 0x34

/* OV7740 रेजिस्टर tables */
#घोषणा REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#घोषणा REG_BGAIN	0x01	/* blue gain */
#घोषणा REG_RGAIN	0x02	/* red gain */
#घोषणा REG_GGAIN	0x03	/* green gain */
#घोषणा REG_REG04	0x04	/* analog setting, करोn't change*/
#घोषणा REG_BAVG	0x05	/* b channel average */
#घोषणा REG_GAVG	0x06	/* g channel average */
#घोषणा REG_RAVG	0x07	/* r channel average */

#घोषणा REG_REG0C	0x0C	/* filp enable */
#घोषणा REG0C_IMG_FLIP		0x80
#घोषणा REG0C_IMG_MIRROR	0x40

#घोषणा REG_REG0E	0x0E	/* blc line */
#घोषणा REG_HAEC	0x0F	/* स्वतः exposure cntrl */
#घोषणा REG_AEC		0x10	/* स्वतः exposure cntrl */

#घोषणा REG_CLK		0x11	/* Clock control */
#घोषणा REG_REG55	0x55	/* Clock PLL DIV/PreDiv */

#घोषणा REG_REG12	0x12

#घोषणा REG_REG13	0x13	/* स्वतः/manual AGC, AEC, Write Balance*/
#घोषणा REG13_AEC_EN	0x01
#घोषणा REG13_AGC_EN	0x04

#घोषणा REG_REG14	0x14
#घोषणा REG_CTRL15	0x15
#घोषणा REG15_GAIN_MSB	0x03

#घोषणा REG_REG16	0x16

#घोषणा REG_MIDH	0x1C	/* manufacture id byte */
#घोषणा REG_MIDL	0x1D	/* manufacture id byre */
#घोषणा REG_PIDH	0x0A	/* Product ID MSB */
#घोषणा REG_PIDL	0x0B	/* Product ID LSB */

#घोषणा REG_84		0x84	/* lots of stuff */
#घोषणा REG_REG38	0x38	/* sub-addr */

#घोषणा REG_AHSTART	0x17	/* Horiz start high bits */
#घोषणा REG_AHSIZE	0x18
#घोषणा REG_AVSTART	0x19	/* Vert start high bits */
#घोषणा REG_AVSIZE	0x1A
#घोषणा REG_PSHFT	0x1b	/* Pixel delay after HREF */

#घोषणा REG_HOUTSIZE	0x31
#घोषणा REG_VOUTSIZE	0x32
#घोषणा REG_HVSIZखातापूर्णF	0x33
#घोषणा REG_REG34	0x34	/* DSP output size H/V LSB*/

#घोषणा REG_ISP_CTRL00	0x80
#घोषणा ISPCTRL00_AWB_EN	0x10
#घोषणा ISPCTRL00_AWB_GAIN_EN	0x04

#घोषणा	REG_YGAIN	0xE2	/* ygain क्रम contrast control */

#घोषणा	REG_YBRIGHT	  0xE3
#घोषणा	REG_SGNSET	  0xE4
#घोषणा	SGNSET_YBRIGHT_MASK	  0x08

#घोषणा REG_USAT	0xDD
#घोषणा REG_VSAT	0xDE


काष्ठा ov7740 अणु
	काष्ठा v4l2_subdev subdev;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad pad;
#पूर्ण_अगर
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	स्थिर काष्ठा ov7740_pixfmt *fmt;  /* Current क्रमmat */
	स्थिर काष्ठा ov7740_framesize *frmsize;
	काष्ठा regmap *regmap;
	काष्ठा clk *xvclk;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा अणु
		/* gain cluster */
		काष्ठा v4l2_ctrl *स्वतः_gain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_wb;
		काष्ठा v4l2_ctrl *blue_balance;
		काष्ठा v4l2_ctrl *red_balance;
	पूर्ण;
	काष्ठा अणु
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
	काष्ठा अणु
		/* exposure cluster */
		काष्ठा v4l2_ctrl *स्वतः_exposure;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		/* saturation/hue cluster */
		काष्ठा v4l2_ctrl *saturation;
		काष्ठा v4l2_ctrl *hue;
	पूर्ण;
	काष्ठा v4l2_ctrl *brightness;
	काष्ठा v4l2_ctrl *contrast;

	काष्ठा mutex mutex;	/* To serialize asynchronus callbacks */
	bool streaming;		/* Streaming on/off */

	काष्ठा gpio_desc *resetb_gpio;
	काष्ठा gpio_desc *pwdn_gpio;
पूर्ण;

काष्ठा ov7740_pixfmt अणु
	u32 mbus_code;
	क्रमागत v4l2_colorspace colorspace;
	स्थिर काष्ठा reg_sequence *regs;
	u32 reg_num;
पूर्ण;

काष्ठा ov7740_framesize अणु
	u16 width;
	u16 height;
	स्थिर काष्ठा reg_sequence *regs;
	u32 reg_num;
पूर्ण;

अटल स्थिर काष्ठा reg_sequence ov7740_vga[] = अणु
	अणु0x55, 0x40पूर्ण,
	अणु0x11, 0x02पूर्ण,

	अणु0xd5, 0x10पूर्ण,
	अणु0x0c, 0x12पूर्ण,
	अणु0x0d, 0x34पूर्ण,
	अणु0x17, 0x25पूर्ण,
	अणु0x18, 0xa0पूर्ण,
	अणु0x19, 0x03पूर्ण,
	अणु0x1a, 0xf0पूर्ण,
	अणु0x1b, 0x89पूर्ण,
	अणु0x22, 0x03पूर्ण,
	अणु0x29, 0x18पूर्ण,
	अणु0x2b, 0xf8पूर्ण,
	अणु0x2c, 0x01पूर्ण,
	अणुREG_HOUTSIZE, 0xa0पूर्ण,
	अणुREG_VOUTSIZE, 0xf0पूर्ण,
	अणु0x33, 0xc4पूर्ण,
	अणुREG_OUTSIZE_LSB, 0x0पूर्ण,
	अणु0x35, 0x05पूर्ण,
	अणु0x04, 0x60पूर्ण,
	अणु0x27, 0x80पूर्ण,
	अणु0x3d, 0x0fपूर्ण,
	अणु0x3e, 0x80पूर्ण,
	अणु0x3f, 0x40पूर्ण,
	अणु0x40, 0x7fपूर्ण,
	अणु0x41, 0x6aपूर्ण,
	अणु0x42, 0x29पूर्ण,
	अणु0x44, 0x22पूर्ण,
	अणु0x45, 0x41पूर्ण,
	अणु0x47, 0x02पूर्ण,
	अणु0x49, 0x64पूर्ण,
	अणु0x4a, 0xa1पूर्ण,
	अणु0x4b, 0x40पूर्ण,
	अणु0x4c, 0x1aपूर्ण,
	अणु0x4d, 0x50पूर्ण,
	अणु0x4e, 0x13पूर्ण,
	अणु0x64, 0x00पूर्ण,
	अणु0x67, 0x88पूर्ण,
	अणु0x68, 0x1aपूर्ण,

	अणु0x14, 0x28पूर्ण,
	अणु0x24, 0x3cपूर्ण,
	अणु0x25, 0x30पूर्ण,
	अणु0x26, 0x72पूर्ण,
	अणु0x50, 0x97पूर्ण,
	अणु0x51, 0x1fपूर्ण,
	अणु0x52, 0x00पूर्ण,
	अणु0x53, 0x00पूर्ण,
	अणु0x20, 0x00पूर्ण,
	अणु0x21, 0xcfपूर्ण,
	अणु0x50, 0x4bपूर्ण,
	अणु0x38, 0x14पूर्ण,
	अणु0xe9, 0x00पूर्ण,
	अणु0x56, 0x55पूर्ण,
	अणु0x57, 0xffपूर्ण,
	अणु0x58, 0xffपूर्ण,
	अणु0x59, 0xffपूर्ण,
	अणु0x5f, 0x04पूर्ण,
	अणु0xec, 0x00पूर्ण,
	अणु0x13, 0xffपूर्ण,

	अणु0x81, 0x3fपूर्ण,
	अणु0x82, 0x32पूर्ण,
	अणु0x38, 0x11पूर्ण,
	अणु0x84, 0x70पूर्ण,
	अणु0x85, 0x00पूर्ण,
	अणु0x86, 0x03पूर्ण,
	अणु0x87, 0x01पूर्ण,
	अणु0x88, 0x05पूर्ण,
	अणु0x89, 0x30पूर्ण,
	अणु0x8d, 0x30पूर्ण,
	अणु0x8f, 0x85पूर्ण,
	अणु0x93, 0x30पूर्ण,
	अणु0x95, 0x85पूर्ण,
	अणु0x99, 0x30पूर्ण,
	अणु0x9b, 0x85पूर्ण,

	अणु0x9c, 0x08पूर्ण,
	अणु0x9d, 0x12पूर्ण,
	अणु0x9e, 0x23पूर्ण,
	अणु0x9f, 0x45पूर्ण,
	अणु0xa0, 0x55पूर्ण,
	अणु0xa1, 0x64पूर्ण,
	अणु0xa2, 0x72पूर्ण,
	अणु0xa3, 0x7fपूर्ण,
	अणु0xa4, 0x8bपूर्ण,
	अणु0xa5, 0x95पूर्ण,
	अणु0xa6, 0xa7पूर्ण,
	अणु0xa7, 0xb5पूर्ण,
	अणु0xa8, 0xcbपूर्ण,
	अणु0xa9, 0xddपूर्ण,
	अणु0xaa, 0xecपूर्ण,
	अणु0xab, 0x1aपूर्ण,

	अणु0xce, 0x78पूर्ण,
	अणु0xcf, 0x6eपूर्ण,
	अणु0xd0, 0x0aपूर्ण,
	अणु0xd1, 0x0cपूर्ण,
	अणु0xd2, 0x84पूर्ण,
	अणु0xd3, 0x90पूर्ण,
	अणु0xd4, 0x1eपूर्ण,

	अणु0x5a, 0x24पूर्ण,
	अणु0x5b, 0x1fपूर्ण,
	अणु0x5c, 0x88पूर्ण,
	अणु0x5d, 0x60पूर्ण,

	अणु0xac, 0x6eपूर्ण,
	अणु0xbe, 0xffपूर्ण,
	अणु0xbf, 0x00पूर्ण,

	अणु0x0f, 0x1dपूर्ण,
	अणु0x0f, 0x1fपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov7740_framesize ov7740_framesizes[] = अणु
	अणु
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.regs		= ov7740_vga,
		.reg_num	= ARRAY_SIZE(ov7740_vga),
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov7740_get_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	काष्ठा regmap *regmap = ov7740->regmap;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, reg->reg & 0xff, &val);
	reg->val = val;
	reg->size = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_set_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			       स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	काष्ठा regmap *regmap = ov7740->regmap;

	regmap_ग_लिखो(regmap, reg->reg & 0xff, reg->val & 0xff);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ov7740_set_घातer(काष्ठा ov7740 *ov7740, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		ret = clk_prepare_enable(ov7740->xvclk);
		अगर (ret)
			वापस ret;

		अगर (ov7740->pwdn_gpio)
			gpiod_direction_output(ov7740->pwdn_gpio, 0);

		अगर (ov7740->resetb_gpio) अणु
			gpiod_set_value(ov7740->resetb_gpio, 1);
			usleep_range(500, 1000);
			gpiod_set_value(ov7740->resetb_gpio, 0);
			usleep_range(3000, 5000);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(ov7740->xvclk);

		अगर (ov7740->pwdn_gpio)
			gpiod_direction_output(ov7740->pwdn_gpio, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov7740_subdev_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ov7740_get_रेजिस्टर,
	.s_रेजिस्टर = ov7740_set_रेजिस्टर,
#पूर्ण_अगर
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल पूर्णांक ov7740_set_white_balance(काष्ठा ov7740 *ov7740, पूर्णांक awb)
अणु
	काष्ठा regmap *regmap = ov7740->regmap;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, REG_ISP_CTRL00, &value);
	अगर (!ret) अणु
		अगर (awb)
			value |= (ISPCTRL00_AWB_EN | ISPCTRL00_AWB_GAIN_EN);
		अन्यथा
			value &= ~(ISPCTRL00_AWB_EN | ISPCTRL00_AWB_GAIN_EN);
		ret = regmap_ग_लिखो(regmap, REG_ISP_CTRL00, value);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!awb) अणु
		ret = regmap_ग_लिखो(regmap, REG_BGAIN,
				   ov7740->blue_balance->val);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(regmap, REG_RGAIN, ov7740->red_balance->val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_set_saturation(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, REG_USAT, (अचिन्हित अक्षर)value);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(regmap, REG_VSAT, (अचिन्हित अक्षर)value);
पूर्ण

अटल पूर्णांक ov7740_set_gain(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, REG_GAIN, value & 0xff);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(regmap, REG_CTRL15,
				 REG15_GAIN_MSB, (value >> 8) & 0x3);
	अगर (!ret)
		ret = regmap_update_bits(regmap, REG_REG13, REG13_AGC_EN, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_set_स्वतःgain(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, REG_REG13, &reg);
	अगर (ret)
		वापस ret;
	अगर (value)
		reg |= REG13_AGC_EN;
	अन्यथा
		reg &= ~REG13_AGC_EN;
	वापस regmap_ग_लिखो(regmap, REG_REG13, reg);
पूर्ण

अटल पूर्णांक ov7740_set_brightness(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	/* Turn off AEC/AGC */
	regmap_update_bits(regmap, REG_REG13, REG13_AEC_EN, 0);
	regmap_update_bits(regmap, REG_REG13, REG13_AGC_EN, 0);

	अगर (value >= 0) अणु
		regmap_ग_लिखो(regmap, REG_YBRIGHT, (अचिन्हित अक्षर)value);
		regmap_update_bits(regmap, REG_SGNSET, SGNSET_YBRIGHT_MASK, 0);
	पूर्ण अन्यथाअणु
		regmap_ग_लिखो(regmap, REG_YBRIGHT, (अचिन्हित अक्षर)(-value));
		regmap_update_bits(regmap, REG_SGNSET, SGNSET_YBRIGHT_MASK, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_set_contrast(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	वापस regmap_ग_लिखो(regmap, REG_YGAIN, (अचिन्हित अक्षर)value);
पूर्ण

अटल पूर्णांक ov7740_get_gain(काष्ठा ov7740 *ov7740, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा regmap *regmap = ov7740->regmap;
	अचिन्हित पूर्णांक value0, value1;
	पूर्णांक ret;

	अगर (!ctrl->val)
		वापस 0;

	ret = regmap_पढ़ो(regmap, REG_GAIN, &value0);
	अगर (ret)
		वापस ret;
	ret = regmap_पढ़ो(regmap, REG_CTRL15, &value1);
	अगर (ret)
		वापस ret;

	ov7740->gain->val = (value1 << 8) | (value0 & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_get_exp(काष्ठा ov7740 *ov7740, काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा regmap *regmap = ov7740->regmap;
	अचिन्हित पूर्णांक value0, value1;
	पूर्णांक ret;

	अगर (ctrl->val == V4L2_EXPOSURE_MANUAL)
		वापस 0;

	ret = regmap_पढ़ो(regmap, REG_AEC, &value0);
	अगर (ret)
		वापस ret;
	ret = regmap_पढ़ो(regmap, REG_HAEC, &value1);
	अगर (ret)
		वापस ret;

	ov7740->exposure->val = (value1 << 8) | (value0 & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_set_exp(काष्ठा regmap *regmap, पूर्णांक value)
अणु
	पूर्णांक ret;

	/* Turn off AEC/AGC */
	ret = regmap_update_bits(regmap, REG_REG13,
				 REG13_AEC_EN | REG13_AGC_EN, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, REG_AEC, (अचिन्हित अक्षर)value);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(regmap, REG_HAEC, (अचिन्हित अक्षर)(value >> 8));
पूर्ण

अटल पूर्णांक ov7740_set_स्वतःexp(काष्ठा regmap *regmap,
			      क्रमागत v4l2_exposure_स्वतः_type value)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, REG_REG13, &reg);
	अगर (!ret) अणु
		अगर (value == V4L2_EXPOSURE_AUTO)
			reg |= (REG13_AEC_EN | REG13_AGC_EN);
		अन्यथा
			reg &= ~(REG13_AEC_EN | REG13_AGC_EN);
		ret = regmap_ग_लिखो(regmap, REG_REG13, reg);
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक ov7740_get_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov7740 *ov7740 = container_of(ctrl->handler,
					     काष्ठा ov7740, ctrl_handler);
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		ret = ov7740_get_gain(ov7740, ctrl);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov7740_get_exp(ov7740, ctrl);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov7740 *ov7740 = container_of(ctrl->handler,
					     काष्ठा ov7740, ctrl_handler);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov7740->subdev);
	काष्ठा regmap *regmap = ov7740->regmap;
	पूर्णांक ret;
	u8 val;

	अगर (!pm_runसमय_get_अगर_in_use(&client->dev))
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov7740_set_white_balance(ov7740, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = ov7740_set_saturation(regmap, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BRIGHTNESS:
		ret = ov7740_set_brightness(regmap, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = ov7740_set_contrast(regmap, ctrl->val);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		val = ctrl->val ? REG0C_IMG_FLIP : 0x00;
		ret = regmap_update_bits(regmap, REG_REG0C,
					 REG0C_IMG_FLIP, val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		val = ctrl->val ? REG0C_IMG_MIRROR : 0x00;
		ret = regmap_update_bits(regmap, REG_REG0C,
					 REG0C_IMG_MIRROR, val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (!ctrl->val)
			ret = ov7740_set_gain(regmap, ov7740->gain->val);
		अन्यथा
			ret = ov7740_set_स्वतःgain(regmap, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		अगर (ctrl->val == V4L2_EXPOSURE_MANUAL)
			ret = ov7740_set_exp(regmap, ov7740->exposure->val);
		अन्यथा
			ret = ov7740_set_स्वतःexp(regmap, ctrl->val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_put(&client->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov7740_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov7740_get_अस्थिर_ctrl,
	.s_ctrl = ov7740_set_ctrl,
पूर्ण;

अटल पूर्णांक ov7740_start_streaming(काष्ठा ov7740 *ov7740)
अणु
	पूर्णांक ret;

	अगर (ov7740->fmt) अणु
		ret = regmap_multi_reg_ग_लिखो(ov7740->regmap,
					     ov7740->fmt->regs,
					     ov7740->fmt->reg_num);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ov7740->frmsize) अणु
		ret = regmap_multi_reg_ग_लिखो(ov7740->regmap,
					     ov7740->frmsize->regs,
					     ov7740->frmsize->reg_num);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __v4l2_ctrl_handler_setup(ov7740->subdev.ctrl_handler);
पूर्ण

अटल पूर्णांक ov7740_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	mutex_lock(&ov7740->mutex);
	अगर (ov7740->streaming == enable) अणु
		mutex_unlock(&ov7740->mutex);
		वापस 0;
	पूर्ण

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(&client->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&client->dev);
			जाओ err_unlock;
		पूर्ण

		ret = ov7740_start_streaming(ov7740);
		अगर (ret)
			जाओ err_rpm_put;
	पूर्ण अन्यथा अणु
		pm_runसमय_put(&client->dev);
	पूर्ण

	ov7740->streaming = enable;

	mutex_unlock(&ov7740->mutex);
	वापस ret;

err_rpm_put:
	pm_runसमय_put(&client->dev);
err_unlock:
	mutex_unlock(&ov7740->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;


	tpf->numerator = 1;
	tpf->denominator = 60;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;


	tpf->numerator = 1;
	tpf->denominator = 60;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov7740_subdev_video_ops = अणु
	.s_stream = ov7740_set_stream,
	.s_frame_पूर्णांकerval = ov7740_s_frame_पूर्णांकerval,
	.g_frame_पूर्णांकerval = ov7740_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence ov7740_क्रमmat_yuyv[] = अणु
	अणु0x12, 0x00पूर्ण,
	अणु0x36, 0x3fपूर्ण,
	अणु0x80, 0x7fपूर्ण,
	अणु0x83, 0x01पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence ov7740_क्रमmat_bggr8[] = अणु
	अणु0x36, 0x2fपूर्ण,
	अणु0x80, 0x01पूर्ण,
	अणु0x83, 0x04पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov7740_pixfmt ov7740_क्रमmats[] = अणु
	अणु
		.mbus_code = MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.regs = ov7740_क्रमmat_yuyv,
		.reg_num = ARRAY_SIZE(ov7740_क्रमmat_yuyv),
	पूर्ण,
	अणु
		.mbus_code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.regs = ov7740_क्रमmat_bggr8,
		.reg_num = ARRAY_SIZE(ov7740_क्रमmat_bggr8),
	पूर्ण
पूर्ण;
#घोषणा N_OV7740_FMTS ARRAY_SIZE(ov7740_क्रमmats)

अटल पूर्णांक ov7740_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= N_OV7740_FMTS)
		वापस -EINVAL;

	code->code = ov7740_क्रमmats[code->index].mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अगर (fie->pad)
		वापस -EINVAL;

	अगर (fie->index >= 1)
		वापस -EINVAL;

	अगर ((fie->width != VGA_WIDTH) || (fie->height != VGA_HEIGHT))
		वापस -EINVAL;

	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = 60;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->pad)
		वापस -EINVAL;

	अगर (fse->index > 0)
		वापस -EINVAL;

	fse->min_width = fse->max_width = VGA_WIDTH;
	fse->min_height = fse->max_height = VGA_HEIGHT;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_try_fmt_पूर्णांकernal(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_mbus_framefmt *fmt,
				   स्थिर काष्ठा ov7740_pixfmt **ret_fmt,
				   स्थिर काष्ठा ov7740_framesize **ret_frmsize)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	स्थिर काष्ठा ov7740_framesize *fsize = &ov7740_framesizes[0];
	पूर्णांक index, i;

	क्रम (index = 0; index < N_OV7740_FMTS; index++) अणु
		अगर (ov7740_क्रमmats[index].mbus_code == fmt->code)
			अवरोध;
	पूर्ण
	अगर (index >= N_OV7740_FMTS) अणु
		/* शेष to first क्रमmat */
		index = 0;
		fmt->code = ov7740_क्रमmats[0].mbus_code;
	पूर्ण
	अगर (ret_fmt != शून्य)
		*ret_fmt = ov7740_क्रमmats + index;

	क्रम (i = 0; i < ARRAY_SIZE(ov7740_framesizes); i++) अणु
		अगर ((fsize->width >= fmt->width) &&
		    (fsize->height >= fmt->height)) अणु
			fmt->width = fsize->width;
			fmt->height = fsize->height;
			अवरोध;
		पूर्ण

		fsize++;
	पूर्ण
	अगर (i >= ARRAY_SIZE(ov7740_framesizes)) अणु
		fsize = &ov7740_framesizes[0];
		fmt->width = fsize->width;
		fmt->height = fsize->height;
	पूर्ण
	अगर (ret_frmsize != शून्य)
		*ret_frmsize = fsize;

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = ov7740_क्रमmats[index].colorspace;

	ov7740->क्रमmat = *fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	स्थिर काष्ठा ov7740_pixfmt *ovfmt;
	स्थिर काष्ठा ov7740_framesize *fsize;
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *mbus_fmt;
#पूर्ण_अगर
	पूर्णांक ret;

	mutex_lock(&ov7740->mutex);
	अगर (क्रमmat->pad) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		ret = ov7740_try_fmt_पूर्णांकernal(sd, &क्रमmat->क्रमmat, शून्य, शून्य);
		अगर (ret)
			जाओ error;
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		*mbus_fmt = क्रमmat->क्रमmat;
#पूर्ण_अगर
		mutex_unlock(&ov7740->mutex);
		वापस 0;
	पूर्ण

	ret = ov7740_try_fmt_पूर्णांकernal(sd, &क्रमmat->क्रमmat, &ovfmt, &fsize);
	अगर (ret)
		जाओ error;

	ov7740->fmt = ovfmt;
	ov7740->frmsize = fsize;

	mutex_unlock(&ov7740->mutex);
	वापस 0;

error:
	mutex_unlock(&ov7740->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *mbus_fmt;
#पूर्ण_अगर
	पूर्णांक ret = 0;

	mutex_lock(&ov7740->mutex);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		क्रमmat->क्रमmat = *mbus_fmt;
		ret = 0;
#अन्यथा
		ret = -EINVAL;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat = ov7740->क्रमmat;
	पूर्ण
	mutex_unlock(&ov7740->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov7740_subdev_pad_ops = अणु
	.क्रमागत_frame_पूर्णांकerval = ov7740_क्रमागत_frame_पूर्णांकerval,
	.क्रमागत_frame_size = ov7740_क्रमागत_frame_size,
	.क्रमागत_mbus_code = ov7740_क्रमागत_mbus_code,
	.get_fmt = ov7740_get_fmt,
	.set_fmt = ov7740_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov7740_subdev_ops = अणु
	.core	= &ov7740_subdev_core_ops,
	.video	= &ov7740_subdev_video_ops,
	.pad	= &ov7740_subdev_pad_ops,
पूर्ण;

अटल व्योम ov7740_get_शेष_क्रमmat(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);

	क्रमmat->width = ov7740->frmsize->width;
	क्रमmat->height = ov7740->frmsize->height;
	क्रमmat->colorspace = ov7740->fmt->colorspace;
	क्रमmat->code = ov7740->fmt->mbus_code;
	क्रमmat->field = V4L2_FIELD_NONE;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल पूर्णांक ov7740_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat =
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	mutex_lock(&ov7740->mutex);
	ov7740_get_शेष_क्रमmat(sd, क्रमmat);
	mutex_unlock(&ov7740->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov7740_subdev_पूर्णांकernal_ops = अणु
	.खोलो = ov7740_खोलो,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक ov7740_probe_dt(काष्ठा i2c_client *client,
			   काष्ठा ov7740 *ov7740)
अणु
	ov7740->resetb_gpio = devm_gpiod_get_optional(&client->dev, "reset",
			GPIOD_OUT_HIGH);
	अगर (IS_ERR(ov7740->resetb_gpio)) अणु
		dev_info(&client->dev, "can't get %s GPIO\n", "reset");
		वापस PTR_ERR(ov7740->resetb_gpio);
	पूर्ण

	ov7740->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
			GPIOD_OUT_LOW);
	अगर (IS_ERR(ov7740->pwdn_gpio)) अणु
		dev_info(&client->dev, "can't get %s GPIO\n", "powerdown");
		वापस PTR_ERR(ov7740->pwdn_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_detect(काष्ठा ov7740 *ov7740)
अणु
	काष्ठा regmap *regmap = ov7740->regmap;
	अचिन्हित पूर्णांक midh, midl, pidh, pidl;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, REG_MIDH, &midh);
	अगर (ret)
		वापस ret;
	अगर (midh != 0x7f)
		वापस -ENODEV;

	ret = regmap_पढ़ो(regmap, REG_MIDL, &midl);
	अगर (ret)
		वापस ret;
	अगर (midl != 0xa2)
		वापस -ENODEV;

	ret = regmap_पढ़ो(regmap, REG_PIDH, &pidh);
	अगर (ret)
		वापस ret;
	अगर (pidh != 0x77)
		वापस -ENODEV;

	ret = regmap_पढ़ो(regmap, REG_PIDL, &pidl);
	अगर (ret)
		वापस ret;
	अगर ((pidl != 0x40) && (pidl != 0x41) && (pidl != 0x42))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7740_init_controls(काष्ठा ov7740 *ov7740)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&ov7740->subdev);
	काष्ठा v4l2_ctrl_handler *ctrl_hdlr = &ov7740->ctrl_handler;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(ctrl_hdlr, 12);
	अगर (ret < 0)
		वापस ret;

	ctrl_hdlr->lock = &ov7740->mutex;
	ov7740->स्वतः_wb = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					  V4L2_CID_AUTO_WHITE_BALANCE,
					  0, 1, 1, 1);
	ov7740->blue_balance = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					       V4L2_CID_BLUE_BALANCE,
					       0, 0xff, 1, 0x80);
	ov7740->red_balance = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					      V4L2_CID_RED_BALANCE,
					      0, 0xff, 1, 0x80);

	ov7740->brightness = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					     V4L2_CID_BRIGHTNESS,
					     -255, 255, 1, 0);
	ov7740->contrast = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					   V4L2_CID_CONTRAST,
					   0, 127, 1, 0x20);
	ov7740->saturation = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 256, 1, 0x80);
	ov7740->hflip = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					V4L2_CID_HFLIP, 0, 1, 1, 0);
	ov7740->vflip = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					V4L2_CID_VFLIP, 0, 1, 1, 0);

	ov7740->gain = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
				       V4L2_CID_GAIN, 0, 1023, 1, 500);

	ov7740->स्वतः_gain = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					    V4L2_CID_AUTOGAIN, 0, 1, 1, 1);

	ov7740->exposure = v4l2_ctrl_new_std(ctrl_hdlr, &ov7740_ctrl_ops,
					   V4L2_CID_EXPOSURE, 0, 65535, 1, 500);

	ov7740->स्वतः_exposure = v4l2_ctrl_new_std_menu(ctrl_hdlr,
					&ov7740_ctrl_ops,
					V4L2_CID_EXPOSURE_AUTO,
					V4L2_EXPOSURE_MANUAL, 0,
					V4L2_EXPOSURE_AUTO);

	v4l2_ctrl_स्वतः_cluster(3, &ov7740->स्वतः_wb, 0, false);
	v4l2_ctrl_स्वतः_cluster(2, &ov7740->स्वतः_gain, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &ov7740->स्वतः_exposure,
			       V4L2_EXPOSURE_MANUAL, true);

	अगर (ctrl_hdlr->error) अणु
		ret = ctrl_hdlr->error;
		dev_err(&client->dev, "controls initialisation failed (%d)\n",
			ret);
		जाओ error;
	पूर्ण

	ret = v4l2_ctrl_handler_setup(ctrl_hdlr);
	अगर (ret) अणु
		dev_err(&client->dev, "%s control init failed (%d)\n",
			__func__, ret);
		जाओ error;
	पूर्ण

	ov7740->subdev.ctrl_handler = ctrl_hdlr;
	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(ctrl_hdlr);
	mutex_destroy(&ov7740->mutex);
	वापस ret;
पूर्ण

अटल व्योम ov7740_मुक्त_controls(काष्ठा ov7740 *ov7740)
अणु
	v4l2_ctrl_handler_मुक्त(ov7740->subdev.ctrl_handler);
	mutex_destroy(&ov7740->mutex);
पूर्ण

#घोषणा OV7740_MAX_REGISTER     0xff
अटल स्थिर काष्ठा regmap_config ov7740_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= OV7740_MAX_REGISTER,
पूर्ण;

अटल पूर्णांक ov7740_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा ov7740 *ov7740;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	ov7740 = devm_kzalloc(&client->dev, माप(*ov7740), GFP_KERNEL);
	अगर (!ov7740)
		वापस -ENOMEM;

	ov7740->xvclk = devm_clk_get(&client->dev, "xvclk");
	अगर (IS_ERR(ov7740->xvclk)) अणु
		ret = PTR_ERR(ov7740->xvclk);
		dev_err(&client->dev,
			"OV7740: fail to get xvclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ov7740_probe_dt(client, ov7740);
	अगर (ret)
		वापस ret;

	ov7740->regmap = devm_regmap_init_sccb(client, &ov7740_regmap_config);
	अगर (IS_ERR(ov7740->regmap)) अणु
		ret = PTR_ERR(ov7740->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	sd = &ov7740->subdev;
	v4l2_i2c_subdev_init(sd, client, &ov7740_subdev_ops);

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->पूर्णांकernal_ops = &ov7740_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
#पूर्ण_अगर

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	ov7740->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov7740->pad);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	ret = ov7740_set_घातer(ov7740, 1);
	अगर (ret)
		वापस ret;

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	ret = ov7740_detect(ov7740);
	अगर (ret)
		जाओ error_detect;

	mutex_init(&ov7740->mutex);

	ret = ov7740_init_controls(ov7740);
	अगर (ret)
		जाओ error_init_controls;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	ov7740->fmt = &ov7740_क्रमmats[0];
	ov7740->frmsize = &ov7740_framesizes[0];

	ov7740_get_शेष_क्रमmat(sd, &ov7740->क्रमmat);

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret)
		जाओ error_async_रेजिस्टर;

	pm_runसमय_idle(&client->dev);

	वापस 0;

error_async_रेजिस्टर:
	v4l2_ctrl_handler_मुक्त(ov7740->subdev.ctrl_handler);
error_init_controls:
	ov7740_मुक्त_controls(ov7740);
error_detect:
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	ov7740_set_घातer(ov7740, 0);
	media_entity_cleanup(&ov7740->subdev.entity);

	वापस ret;
पूर्ण

अटल पूर्णांक ov7740_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);

	mutex_destroy(&ov7740->mutex);
	v4l2_ctrl_handler_मुक्त(ov7740->subdev.ctrl_handler);
	media_entity_cleanup(&ov7740->subdev.entity);
	v4l2_async_unरेजिस्टर_subdev(sd);
	ov7740_मुक्त_controls(ov7740);

	pm_runसमय_get_sync(&client->dev);
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	ov7740_set_घातer(ov7740, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov7740_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);

	ov7740_set_घातer(ov7740, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ov7740_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा ov7740 *ov7740 = container_of(sd, काष्ठा ov7740, subdev);

	वापस ov7740_set_घातer(ov7740, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov7740_id[] = अणु
	अणु "ov7740", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov7740_id);

अटल स्थिर काष्ठा dev_pm_ops ov7740_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ov7740_runसमय_suspend, ov7740_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ov7740_of_match[] = अणु
	अणु.compatible = "ovti,ov7740", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov7740_of_match);

अटल काष्ठा i2c_driver ov7740_i2c_driver = अणु
	.driver = अणु
		.name = "ov7740",
		.pm = &ov7740_pm_ops,
		.of_match_table = of_match_ptr(ov7740_of_match),
	पूर्ण,
	.probe_new = ov7740_probe,
	.हटाओ   = ov7740_हटाओ,
	.id_table = ov7740_id,
पूर्ण;
module_i2c_driver(ov7740_i2c_driver);

MODULE_DESCRIPTION("The V4L2 driver for Omnivision 7740 sensor");
MODULE_AUTHOR("Songjun Wu <songjun.wu@atmel.com>");
MODULE_LICENSE("GPL v2");
