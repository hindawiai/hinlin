<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम AK8813 / AK8814 TV-ecoders from Asahi Kasei Microप्रणालीs Co., Ltd. (AKM)
 *
 * Copyright (C) 2010, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>

#समावेश <media/i2c/ak881x.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>

#घोषणा AK881X_INTERFACE_MODE	0
#घोषणा AK881X_VIDEO_PROCESS1	1
#घोषणा AK881X_VIDEO_PROCESS2	2
#घोषणा AK881X_VIDEO_PROCESS3	3
#घोषणा AK881X_DAC_MODE		5
#घोषणा AK881X_STATUS		0x24
#घोषणा AK881X_DEVICE_ID	0x25
#घोषणा AK881X_DEVICE_REVISION	0x26

काष्ठा ak881x अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा ak881x_pdata *pdata;
	अचिन्हित पूर्णांक lines;
	अक्षर revision;	/* DEVICE_REVISION content */
पूर्ण;

अटल पूर्णांक reg_पढ़ो(काष्ठा i2c_client *client, स्थिर u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक reg_ग_लिखो(काष्ठा i2c_client *client, स्थिर u8 reg,
		     स्थिर u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, data);
पूर्ण

अटल पूर्णांक reg_set(काष्ठा i2c_client *client, स्थिर u8 reg,
		   स्थिर u8 data, u8 mask)
अणु
	पूर्णांक ret = reg_पढ़ो(client, reg);
	अगर (ret < 0)
		वापस ret;
	वापस reg_ग_लिखो(client, reg, (ret & ~mask) | (data & mask));
पूर्ण

अटल काष्ठा ak881x *to_ak881x(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा ak881x, subdev);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ak881x_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0x26)
		वापस -EINVAL;

	reg->size = 1;
	reg->val = reg_पढ़ो(client, reg->reg);

	अगर (reg->val > 0xffff)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ak881x_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0x26)
		वापस -EINVAL;

	अगर (reg_ग_लिखो(client, reg->reg, reg->val) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ak881x_fill_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ak881x *ak881x = to_ak881x(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	v4l_bound_align_image(&mf->width, 0, 720, 2,
			      &mf->height, 0, ak881x->lines, 1, 0);
	mf->field	= V4L2_FIELD_INTERLACED;
	mf->code	= MEDIA_BUS_FMT_YUYV8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक ak881x_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_YUYV8_2X8;
	वापस 0;
पूर्ण

अटल पूर्णांक ak881x_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ak881x *ak881x = to_ak881x(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = 720;
		sel->r.height = ak881x->lines;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ak881x_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ak881x *ak881x = to_ak881x(client);
	u8 vp1;

	अगर (std == V4L2_STD_NTSC_443) अणु
		vp1 = 3;
		ak881x->lines = 480;
	पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_M) अणु
		vp1 = 5;
		ak881x->lines = 480;
	पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_60) अणु
		vp1 = 7;
		ak881x->lines = 480;
	पूर्ण अन्यथा अगर (std & V4L2_STD_NTSC) अणु
		vp1 = 0;
		ak881x->lines = 480;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		vp1 = 0xf;
		ak881x->lines = 576;
	पूर्ण अन्यथा अणु
		/* No SECAM or PAL_N/Nc supported */
		वापस -EINVAL;
	पूर्ण

	reg_set(client, AK881X_VIDEO_PROCESS1, vp1, 0xf);

	वापस 0;
पूर्ण

अटल पूर्णांक ak881x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ak881x *ak881x = to_ak881x(client);

	अगर (enable) अणु
		u8 dac;
		/* For colour-bar testing set bit 6 of AK881X_VIDEO_PROCESS1 */
		/* Default: composite output */
		अगर (ak881x->pdata->flags & AK881X_COMPONENT)
			dac = 3;
		अन्यथा
			dac = 4;
		/* Turn on the DAC(s) */
		reg_ग_लिखो(client, AK881X_DAC_MODE, dac);
		dev_dbg(&client->dev, "chip status 0x%x\n",
			reg_पढ़ो(client, AK881X_STATUS));
	पूर्ण अन्यथा अणु
		/* ...and clear bit 6 of AK881X_VIDEO_PROCESS1 here */
		reg_ग_लिखो(client, AK881X_DAC_MODE, 0);
		dev_dbg(&client->dev, "chip status 0x%x\n",
			reg_पढ़ो(client, AK881X_STATUS));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops ak881x_subdev_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= ak881x_g_रेजिस्टर,
	.s_रेजिस्टर	= ak881x_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ak881x_subdev_video_ops = अणु
	.s_std_output	= ak881x_s_std_output,
	.s_stream	= ak881x_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ak881x_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = ak881x_क्रमागत_mbus_code,
	.get_selection	= ak881x_get_selection,
	.set_fmt	= ak881x_fill_fmt,
	.get_fmt	= ak881x_fill_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ak881x_subdev_ops = अणु
	.core	= &ak881x_subdev_core_ops,
	.video	= &ak881x_subdev_video_ops,
	.pad	= &ak881x_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ak881x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा ak881x *ak881x;
	u8 अगरmode, data;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	ak881x = devm_kzalloc(&client->dev, माप(*ak881x), GFP_KERNEL);
	अगर (!ak881x)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&ak881x->subdev, client, &ak881x_subdev_ops);

	data = reg_पढ़ो(client, AK881X_DEVICE_ID);

	चयन (data) अणु
	हाल 0x13:
	हाल 0x14:
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"No ak881x chip detected, register read %x\n", data);
		वापस -ENODEV;
	पूर्ण

	ak881x->revision = reg_पढ़ो(client, AK881X_DEVICE_REVISION);
	ak881x->pdata = client->dev.platक्रमm_data;

	अगर (ak881x->pdata) अणु
		अगर (ak881x->pdata->flags & AK881X_FIELD)
			अगरmode = 4;
		अन्यथा
			अगरmode = 0;

		चयन (ak881x->pdata->flags & AK881X_IF_MODE_MASK) अणु
		हाल AK881X_IF_MODE_BT656:
			अगरmode |= 1;
			अवरोध;
		हाल AK881X_IF_MODE_MASTER:
			अगरmode |= 2;
			अवरोध;
		हाल AK881X_IF_MODE_SLAVE:
		शेष:
			अवरोध;
		पूर्ण

		dev_dbg(&client->dev, "IF mode %x\n", अगरmode);

		/*
		 * "Line Blanking No." seems to be the same as the number of
		 * "black" lines on, e.g., SuperH VOU, whose शेष value of 20
		 * "incidentally" matches ak881x' शेष
		 */
		reg_ग_लिखो(client, AK881X_INTERFACE_MODE, अगरmode | (20 << 3));
	पूर्ण

	/* Hardware शेष: NTSC-M */
	ak881x->lines = 480;

	dev_info(&client->dev, "Detected an ak881x chip ID %x, revision %x\n",
		 data, ak881x->revision);

	वापस 0;
पूर्ण

अटल पूर्णांक ak881x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ak881x *ak881x = to_ak881x(client);

	v4l2_device_unरेजिस्टर_subdev(&ak881x->subdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ak881x_id[] = अणु
	अणु "ak8813", 0 पूर्ण,
	अणु "ak8814", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ak881x_id);

अटल काष्ठा i2c_driver ak881x_i2c_driver = अणु
	.driver = अणु
		.name = "ak881x",
	पूर्ण,
	.probe		= ak881x_probe,
	.हटाओ		= ak881x_हटाओ,
	.id_table	= ak881x_id,
पूर्ण;

module_i2c_driver(ak881x_i2c_driver);

MODULE_DESCRIPTION("TV-output driver for ak8813/ak8814");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_LICENSE("GPL v2");
