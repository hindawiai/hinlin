<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OKI Semiconductor ML86V7667 video decoder driver
 *
 * Author: Vladimir Barinov <source@cogentembedded.com>
 * Copyright (C) 2013 Cogent Embedded, Inc.
 * Copyright (C) 2013 Renesas Solutions Corp.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा DRV_NAME "ml86v7667"

/* Subaddresses */
#घोषणा MRA_REG			0x00 /* Mode Register A */
#घोषणा MRC_REG			0x02 /* Mode Register C */
#घोषणा LUMC_REG		0x0C /* Luminance Control */
#घोषणा CLC_REG			0x10 /* Contrast level control */
#घोषणा SSEPL_REG		0x11 /* Sync separation level */
#घोषणा CHRCA_REG		0x12 /* Chrominance Control A */
#घोषणा ACCC_REG		0x14 /* ACC Loop filter & Chrominance control */
#घोषणा ACCRC_REG		0x15 /* ACC Reference level control */
#घोषणा HUE_REG			0x16 /* Hue control */
#घोषणा ADC2_REG		0x1F /* ADC Register 2 */
#घोषणा PLLR1_REG		0x20 /* PLL Register 1 */
#घोषणा STATUS_REG		0x2C /* STATUS Register */

/* Mode Register A रेजिस्टर bits */
#घोषणा MRA_OUTPUT_MODE_MASK	(3 << 6)
#घोषणा MRA_ITUR_BT601		(1 << 6)
#घोषणा MRA_ITUR_BT656		(0 << 6)
#घोषणा MRA_INPUT_MODE_MASK	(7 << 3)
#घोषणा MRA_PAL_BT601		(4 << 3)
#घोषणा MRA_NTSC_BT601		(0 << 3)
#घोषणा MRA_REGISTER_MODE	(1 << 0)

/* Mode Register C रेजिस्टर bits */
#घोषणा MRC_AUTOSELECT		(1 << 7)

/* Luminance Control रेजिस्टर bits */
#घोषणा LUMC_ONOFF_SHIFT	7
#घोषणा LUMC_ONOFF_MASK		(1 << 7)

/* Contrast level control रेजिस्टर bits */
#घोषणा CLC_CONTRAST_ONOFF	(1 << 7)
#घोषणा CLC_CONTRAST_MASK	0x0F

/* Sync separation level रेजिस्टर bits */
#घोषणा SSEPL_LUMIन_अंकCE_ONOFF	(1 << 7)
#घोषणा SSEPL_LUMIन_अंकCE_MASK	0x7F

/* Chrominance Control A रेजिस्टर bits */
#घोषणा CHRCA_MODE_SHIFT	6
#घोषणा CHRCA_MODE_MASK		(1 << 6)

/* ACC Loop filter & Chrominance control रेजिस्टर bits */
#घोषणा ACCC_CHROMA_CR_SHIFT	3
#घोषणा ACCC_CHROMA_CR_MASK	(7 << 3)
#घोषणा ACCC_CHROMA_CB_SHIFT	0
#घोषणा ACCC_CHROMA_CB_MASK	(7 << 0)

/* ACC Reference level control रेजिस्टर bits */
#घोषणा ACCRC_CHROMA_MASK	0xfc
#घोषणा ACCRC_CHROMA_SHIFT	2

/* ADC Register 2 रेजिस्टर bits */
#घोषणा ADC2_CLAMP_VOLTAGE_MASK	(7 << 1)
#घोषणा ADC2_CLAMP_VOLTAGE(n)	((n & 7) << 1)

/* PLL Register 1 रेजिस्टर bits */
#घोषणा PLLR1_FIXED_CLOCK	(1 << 7)

/* STATUS Register रेजिस्टर bits */
#घोषणा STATUS_HLOCK_DETECT	(1 << 3)
#घोषणा STATUS_NTSCPAL		(1 << 2)

काष्ठा ml86v7667_priv अणु
	काष्ठा v4l2_subdev		sd;
	काष्ठा v4l2_ctrl_handler	hdl;
	v4l2_std_id			std;
पूर्ण;

अटल अंतरभूत काष्ठा ml86v7667_priv *to_ml86v7667(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा ml86v7667_priv, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ml86v7667_priv, hdl)->sd;
पूर्ण

अटल पूर्णांक ml86v7667_mask_set(काष्ठा i2c_client *client, स्थिर u8 reg,
			      स्थिर u8 mask, स्थिर u8 data)
अणु
	पूर्णांक val = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (val < 0)
		वापस val;

	val = (val & ~mask) | (data & mask);
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

अटल पूर्णांक ml86v7667_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		ret = ml86v7667_mask_set(client, SSEPL_REG,
					 SSEPL_LUMIन_अंकCE_MASK, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = ml86v7667_mask_set(client, CLC_REG,
					 CLC_CONTRAST_MASK, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CHROMA_GAIN:
		ret = ml86v7667_mask_set(client, ACCRC_REG, ACCRC_CHROMA_MASK,
					 ctrl->val << ACCRC_CHROMA_SHIFT);
		अवरोध;
	हाल V4L2_CID_HUE:
		ret = ml86v7667_mask_set(client, HUE_REG, ~0, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		ret = ml86v7667_mask_set(client, ACCC_REG,
					 ACCC_CHROMA_CR_MASK,
					 ctrl->val << ACCC_CHROMA_CR_SHIFT);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		ret = ml86v7667_mask_set(client, ACCC_REG,
					 ACCC_CHROMA_CB_MASK,
					 ctrl->val << ACCC_CHROMA_CB_SHIFT);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		ret = ml86v7667_mask_set(client, LUMC_REG,
					 LUMC_ONOFF_MASK,
					 ctrl->val << LUMC_ONOFF_SHIFT);
		अवरोध;
	हाल V4L2_CID_COLOR_KILLER:
		ret = ml86v7667_mask_set(client, CHRCA_REG,
					 CHRCA_MODE_MASK,
					 ctrl->val << CHRCA_MODE_SHIFT);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ml86v7667_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक status;

	status = i2c_smbus_पढ़ो_byte_data(client, STATUS_REG);
	अगर (status < 0)
		वापस status;

	अगर (status & STATUS_HLOCK_DETECT)
		*std &= status & STATUS_NTSCPAL ? V4L2_STD_625_50 : V4L2_STD_525_60;
	अन्यथा
		*std = V4L2_STD_UNKNOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक status_reg;

	status_reg = i2c_smbus_पढ़ो_byte_data(client, STATUS_REG);
	अगर (status_reg < 0)
		वापस status_reg;

	*status = status_reg & STATUS_HLOCK_DETECT ? 0 : V4L2_IN_ST_NO_SIGNAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_YUYV8_2X8;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_fill_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ml86v7667_priv *priv = to_ml86v7667(sd);
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	fmt->code = MEDIA_BUS_FMT_YUYV8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	/* The top field is always transferred first by the chip */
	fmt->field = V4L2_FIELD_INTERLACED_TB;
	fmt->width = 720;
	fmt->height = priv->std & V4L2_STD_525_60 ? 480 : 576;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_get_mbus_config(काष्ठा v4l2_subdev *sd,
				     अचिन्हित पूर्णांक pad,
				     काष्ठा v4l2_mbus_config *cfg)
अणु
	cfg->flags = V4L2_MBUS_MASTER | V4L2_MBUS_PCLK_SAMPLE_RISING |
		     V4L2_MBUS_DATA_ACTIVE_HIGH;
	cfg->type = V4L2_MBUS_BT656;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा ml86v7667_priv *priv = to_ml86v7667(sd);

	*std = priv->std;

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा ml86v7667_priv *priv = to_ml86v7667(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	पूर्णांक ret;
	u8 mode;

	/* PAL/NTSC ITU-R BT.601 input mode */
	mode = std & V4L2_STD_525_60 ? MRA_NTSC_BT601 : MRA_PAL_BT601;
	ret = ml86v7667_mask_set(client, MRA_REG, MRA_INPUT_MODE_MASK, mode);
	अगर (ret < 0)
		वापस ret;

	priv->std = std;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ml86v7667_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, (u8)reg->reg);
	अगर (ret < 0)
		वापस ret;

	reg->val = ret;
	reg->size = माप(u8);

	वापस 0;
पूर्ण

अटल पूर्णांक ml86v7667_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, (u8)reg->reg, (u8)reg->val);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_ops ml86v7667_ctrl_ops = अणु
	.s_ctrl = ml86v7667_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ml86v7667_subdev_video_ops = अणु
	.g_std = ml86v7667_g_std,
	.s_std = ml86v7667_s_std,
	.querystd = ml86v7667_querystd,
	.g_input_status = ml86v7667_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ml86v7667_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = ml86v7667_क्रमागत_mbus_code,
	.get_fmt = ml86v7667_fill_fmt,
	.set_fmt = ml86v7667_fill_fmt,
	.get_mbus_config = ml86v7667_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ml86v7667_subdev_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ml86v7667_g_रेजिस्टर,
	.s_रेजिस्टर = ml86v7667_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ml86v7667_subdev_ops = अणु
	.core = &ml86v7667_subdev_core_ops,
	.video = &ml86v7667_subdev_video_ops,
	.pad = &ml86v7667_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ml86v7667_init(काष्ठा ml86v7667_priv *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->sd);
	पूर्णांक val;
	पूर्णांक ret;

	/* BT.656-4 output mode, रेजिस्टर mode */
	ret = ml86v7667_mask_set(client, MRA_REG,
				 MRA_OUTPUT_MODE_MASK | MRA_REGISTER_MODE,
				 MRA_ITUR_BT656 | MRA_REGISTER_MODE);

	/* PLL circuit fixed घड़ी, 32MHz */
	ret |= ml86v7667_mask_set(client, PLLR1_REG, PLLR1_FIXED_CLOCK,
				  PLLR1_FIXED_CLOCK);

	/* ADC2 clamping voltage maximum  */
	ret |= ml86v7667_mask_set(client, ADC2_REG, ADC2_CLAMP_VOLTAGE_MASK,
				  ADC2_CLAMP_VOLTAGE(7));

	/* enable luminance function */
	ret |= ml86v7667_mask_set(client, SSEPL_REG, SSEPL_LUMIन_अंकCE_ONOFF,
				  SSEPL_LUMIन_अंकCE_ONOFF);

	/* enable contrast function */
	ret |= ml86v7667_mask_set(client, CLC_REG, CLC_CONTRAST_ONOFF, 0);

	/*
	 * PAL/NTSC स्वतःdetection is enabled after reset,
	 * set the स्वतःdetected std in manual std mode and
	 * disable स्वतःdetection
	 */
	val = i2c_smbus_पढ़ो_byte_data(client, STATUS_REG);
	अगर (val < 0)
		वापस val;

	priv->std = val & STATUS_NTSCPAL ? V4L2_STD_625_50 : V4L2_STD_525_60;
	ret |= ml86v7667_mask_set(client, MRC_REG, MRC_AUTOSELECT, 0);

	val = priv->std & V4L2_STD_525_60 ? MRA_NTSC_BT601 : MRA_PAL_BT601;
	ret |= ml86v7667_mask_set(client, MRA_REG, MRA_INPUT_MODE_MASK, val);

	वापस ret;
पूर्ण

अटल पूर्णांक ml86v7667_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा ml86v7667_priv *priv;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&priv->sd, client, &ml86v7667_subdev_ops);

	v4l2_ctrl_handler_init(&priv->hdl, 8);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, -64, 63, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_CONTRAST, -8, 7, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_CHROMA_GAIN, -32, 31, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_RED_BALANCE, -4, 3, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_BLUE_BALANCE, -4, 3, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_SHARPNESS, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ml86v7667_ctrl_ops,
			  V4L2_CID_COLOR_KILLER, 0, 1, 1, 0);
	priv->sd.ctrl_handler = &priv->hdl;

	ret = priv->hdl.error;
	अगर (ret)
		जाओ cleanup;

	v4l2_ctrl_handler_setup(&priv->hdl);

	ret = ml86v7667_init(priv);
	अगर (ret)
		जाओ cleanup;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
		 client->addr, client->adapter->name);
	वापस 0;

cleanup:
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	v4l2_device_unरेजिस्टर_subdev(&priv->sd);
	v4l_err(client, "failed to probe @ 0x%02x (%s)\n",
		client->addr, client->adapter->name);
	वापस ret;
पूर्ण

अटल पूर्णांक ml86v7667_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ml86v7667_priv *priv = to_ml86v7667(sd);

	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	v4l2_device_unरेजिस्टर_subdev(&priv->sd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ml86v7667_id[] = अणु
	अणुDRV_NAME, 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ml86v7667_id);

अटल काष्ठा i2c_driver ml86v7667_i2c_driver = अणु
	.driver = अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= ml86v7667_probe,
	.हटाओ		= ml86v7667_हटाओ,
	.id_table	= ml86v7667_id,
पूर्ण;

module_i2c_driver(ml86v7667_i2c_driver);

MODULE_DESCRIPTION("OKI Semiconductor ML86V7667 video decoder driver");
MODULE_AUTHOR("Vladimir Barinov");
MODULE_LICENSE("GPL");
