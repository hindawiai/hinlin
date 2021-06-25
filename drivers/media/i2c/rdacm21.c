<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IMI RDACM21 GMSL Camera Driver
 *
 * Copyright (C) 2017-2020 Jacopo Mondi
 * Copyright (C) 2017-2019 Kieran Bingham
 * Copyright (C) 2017-2019 Laurent Pinअक्षरt
 * Copyright (C) 2017-2019 Niklas Sथघderlund
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2015 Cogent Embedded, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "max9271.h"

#घोषणा MAX9271_RESET_CYCLES		10

#घोषणा OV490_I2C_ADDRESS		0x24

#घोषणा OV490_PAGE_HIGH_REG		0xfffd
#घोषणा OV490_PAGE_LOW_REG		0xfffe

/*
 * The SCCB slave handling is unकरोcumented; the रेजिस्टरs naming scheme is
 * totally arbitrary.
 */
#घोषणा OV490_SCCB_SLAVE_WRITE		0x00
#घोषणा OV490_SCCB_SLAVE_READ		0x01
#घोषणा OV490_SCCB_SLAVE0_सूची		0x80195000
#घोषणा OV490_SCCB_SLAVE0_ADDR_HIGH	0x80195001
#घोषणा OV490_SCCB_SLAVE0_ADDR_LOW	0x80195002

#घोषणा OV490_DVP_CTRL3			0x80286009

#घोषणा OV490_ODS_CTRL_FRAME_OUTPUT_EN	0x0c
#घोषणा OV490_ODS_CTRL			0x8029d000

#घोषणा OV490_HOST_CMD			0x808000c0
#घोषणा OV490_HOST_CMD_TRIGGER		0xc1

#घोषणा OV490_ID_VAL			0x0490
#घोषणा OV490_ID(_p, _v)		((((_p) & 0xff) << 8) | ((_v) & 0xff))
#घोषणा OV490_PID			0x8080300a
#घोषणा OV490_VER			0x8080300b
#घोषणा OV490_PID_TIMEOUT		20
#घोषणा OV490_OUTPUT_EN_TIMEOUT		300

#घोषणा OV490_GPIO0			BIT(0)
#घोषणा OV490_SPWDN0			BIT(0)
#घोषणा OV490_GPIO_SEL0			0x80800050
#घोषणा OV490_GPIO_SEL1			0x80800051
#घोषणा OV490_GPIO_सूचीECTION0		0x80800054
#घोषणा OV490_GPIO_सूचीECTION1		0x80800055
#घोषणा OV490_GPIO_OUTPUT_VALUE0	0x80800058
#घोषणा OV490_GPIO_OUTPUT_VALUE1	0x80800059

#घोषणा OV490_ISP_HSIZE_LOW		0x80820060
#घोषणा OV490_ISP_HSIZE_HIGH		0x80820061
#घोषणा OV490_ISP_VSIZE_LOW		0x80820062
#घोषणा OV490_ISP_VSIZE_HIGH		0x80820063

#घोषणा OV10640_ID_HIGH			0xa6
#घोषणा OV10640_CHIP_ID			0x300a
#घोषणा OV10640_PIXEL_RATE		55000000

काष्ठा rdacm21_device अणु
	काष्ठा device			*dev;
	काष्ठा max9271_device		serializer;
	काष्ठा i2c_client		*isp;
	काष्ठा v4l2_subdev		sd;
	काष्ठा media_pad		pad;
	काष्ठा v4l2_mbus_framefmt	fmt;
	काष्ठा v4l2_ctrl_handler	ctrls;
	u32				addrs[2];
	u16				last_page;
पूर्ण;

अटल अंतरभूत काष्ठा rdacm21_device *sd_to_rdacm21(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा rdacm21_device, sd);
पूर्ण

अटल स्थिर काष्ठा ov490_reg अणु
	u16 reg;
	u8 val;
पूर्ण ov490_regs_wizard[] = अणु
	अणु0xfffd, 0x80पूर्ण,
	अणु0xfffe, 0x82पूर्ण,
	अणु0x0071, 0x11पूर्ण,
	अणु0x0075, 0x11पूर्ण,
	अणु0xfffe, 0x29पूर्ण,
	अणु0x6010, 0x01पूर्ण,
	/*
	 * OV490 EMB line disable in YUV and RAW data,
	 * NOTE: EMB line is still used in ISP and sensor
	 */
	अणु0xe000, 0x14पूर्ण,
	अणु0xfffe, 0x28पूर्ण,
	अणु0x6000, 0x04पूर्ण,
	अणु0x6004, 0x00पूर्ण,
	/*
	 * PCLK polarity - useless due to silicon bug.
	 * Use 0x808000bb रेजिस्टर instead.
	 */
	अणु0x6008, 0x00पूर्ण,
	अणु0xfffe, 0x80पूर्ण,
	अणु0x0091, 0x00पूर्ण,
	/* bit[3]=0 - PCLK polarity workaround. */
	अणु0x00bb, 0x1dपूर्ण,
	/* Ov490 FSIN: app_fsin_from_fsync */
	अणु0xfffe, 0x85पूर्ण,
	अणु0x0008, 0x00पूर्ण,
	अणु0x0009, 0x01पूर्ण,
	/* FSIN0 source. */
	अणु0x000A, 0x05पूर्ण,
	अणु0x000B, 0x00पूर्ण,
	/* FSIN0 delay. */
	अणु0x0030, 0x02पूर्ण,
	अणु0x0031, 0x00पूर्ण,
	अणु0x0032, 0x00पूर्ण,
	अणु0x0033, 0x00पूर्ण,
	/* FSIN1 delay. */
	अणु0x0038, 0x02पूर्ण,
	अणु0x0039, 0x00पूर्ण,
	अणु0x003A, 0x00पूर्ण,
	अणु0x003B, 0x00पूर्ण,
	/* FSIN0 length. */
	अणु0x0070, 0x2Cपूर्ण,
	अणु0x0071, 0x01पूर्ण,
	अणु0x0072, 0x00पूर्ण,
	अणु0x0073, 0x00पूर्ण,
	/* FSIN1 length. */
	अणु0x0074, 0x64पूर्ण,
	अणु0x0075, 0x00पूर्ण,
	अणु0x0076, 0x00पूर्ण,
	अणु0x0077, 0x00पूर्ण,
	अणु0x0000, 0x14पूर्ण,
	अणु0x0001, 0x00पूर्ण,
	अणु0x0002, 0x00पूर्ण,
	अणु0x0003, 0x00पूर्ण,
	/*
	 * Load fsin0,load fsin1,load other,
	 * It will be cleared स्वतःmatically.
	 */
	अणु0x0004, 0x32पूर्ण,
	अणु0x0005, 0x00पूर्ण,
	अणु0x0006, 0x00पूर्ण,
	अणु0x0007, 0x00पूर्ण,
	अणु0xfffe, 0x80पूर्ण,
	/* Sensor FSIN. */
	अणु0x0081, 0x00पूर्ण,
	/* ov10640 FSIN enable */
	अणु0xfffe, 0x19पूर्ण,
	अणु0x5000, 0x00पूर्ण,
	अणु0x5001, 0x30पूर्ण,
	अणु0x5002, 0x8cपूर्ण,
	अणु0x5003, 0xb2पूर्ण,
	अणु0xfffe, 0x80पूर्ण,
	अणु0x00c0, 0xc1पूर्ण,
	/* ov10640 HFLIP=1 by शेष */
	अणु0xfffe, 0x19पूर्ण,
	अणु0x5000, 0x01पूर्ण,
	अणु0x5001, 0x00पूर्ण,
	अणु0xfffe, 0x80पूर्ण,
	अणु0x00c0, 0xdcपूर्ण,
पूर्ण;

अटल पूर्णांक ov490_पढ़ो(काष्ठा rdacm21_device *dev, u16 reg, u8 *val)
अणु
	u8 buf[2] = अणु reg >> 8, reg पूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(dev->isp, buf, 2);
	अगर (ret == 2)
		ret = i2c_master_recv(dev->isp, val, 1);

	अगर (ret < 0) अणु
		dev_dbg(dev->dev, "%s: register 0x%04x read failed (%d)\n",
			__func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov490_ग_लिखो(काष्ठा rdacm21_device *dev, u16 reg, u8 val)
अणु
	u8 buf[3] = अणु reg >> 8, reg, val पूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(dev->isp, buf, 3);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "%s: register 0x%04x write failed (%d)\n",
			__func__, reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ov490_set_page(काष्ठा rdacm21_device *dev, u16 page)
अणु
	u8 page_high = page >> 8;
	u8 page_low = page;
	पूर्णांक ret;

	अगर (page == dev->last_page)
		वापस 0;

	अगर (page_high != (dev->last_page >> 8)) अणु
		ret = ov490_ग_लिखो(dev, OV490_PAGE_HIGH_REG, page_high);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (page_low != (u8)dev->last_page) अणु
		ret = ov490_ग_लिखो(dev, OV490_PAGE_LOW_REG, page_low);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev->last_page = page;
	usleep_range(100, 150);

	वापस 0;
पूर्ण

अटल पूर्णांक ov490_पढ़ो_reg(काष्ठा rdacm21_device *dev, u32 reg, u8 *val)
अणु
	पूर्णांक ret;

	ret = ov490_set_page(dev, reg >> 16);
	अगर (ret)
		वापस ret;

	ret = ov490_पढ़ो(dev, (u16)reg, val);
	अगर (ret)
		वापस ret;

	dev_dbg(dev->dev, "%s: 0x%08x = 0x%02x\n", __func__, reg, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक ov490_ग_लिखो_reg(काष्ठा rdacm21_device *dev, u32 reg, u8 val)
अणु
	पूर्णांक ret;

	ret = ov490_set_page(dev, reg >> 16);
	अगर (ret)
		वापस ret;

	ret = ov490_ग_लिखो(dev, (u16)reg, val);
	अगर (ret)
		वापस ret;

	dev_dbg(dev->dev, "%s: 0x%08x = 0x%02x\n", __func__, reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rdacm21_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा rdacm21_device *dev = sd_to_rdacm21(sd);

	/*
	 * Enable serial link now that the ISP provides a valid pixel घड़ी
	 * to start serializing video data on the GMSL link.
	 */
	वापस max9271_set_serial_link(&dev->serializer, enable);
पूर्ण

अटल पूर्णांक rdacm21_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_YUYV8_1X16;

	वापस 0;
पूर्ण

अटल पूर्णांक rdacm21_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा rdacm21_device *dev = sd_to_rdacm21(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mf->width		= dev->fmt.width;
	mf->height		= dev->fmt.height;
	mf->code		= MEDIA_BUS_FMT_YUYV8_1X16;
	mf->colorspace		= V4L2_COLORSPACE_SRGB;
	mf->field		= V4L2_FIELD_NONE;
	mf->ycbcr_enc		= V4L2_YCBCR_ENC_601;
	mf->quantization	= V4L2_QUANTIZATION_FULL_RANGE;
	mf->xfer_func		= V4L2_XFER_FUNC_NONE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops rdacm21_video_ops = अणु
	.s_stream	= rdacm21_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops rdacm21_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = rdacm21_क्रमागत_mbus_code,
	.get_fmt	= rdacm21_get_fmt,
	.set_fmt	= rdacm21_get_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops rdacm21_subdev_ops = अणु
	.video		= &rdacm21_video_ops,
	.pad		= &rdacm21_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक ov10640_initialize(काष्ठा rdacm21_device *dev)
अणु
	u8 val;

	/* Power-up OV10640 by setting RESETB and PWDNB pins high. */
	ov490_ग_लिखो_reg(dev, OV490_GPIO_SEL0, OV490_GPIO0);
	ov490_ग_लिखो_reg(dev, OV490_GPIO_SEL1, OV490_SPWDN0);
	ov490_ग_लिखो_reg(dev, OV490_GPIO_सूचीECTION0, OV490_GPIO0);
	ov490_ग_लिखो_reg(dev, OV490_GPIO_सूचीECTION1, OV490_SPWDN0);
	ov490_ग_लिखो_reg(dev, OV490_GPIO_OUTPUT_VALUE0, OV490_GPIO0);
	ov490_ग_लिखो_reg(dev, OV490_GPIO_OUTPUT_VALUE0, OV490_SPWDN0);
	usleep_range(3000, 5000);

	/* Read OV10640 ID to test communications. */
	ov490_ग_लिखो_reg(dev, OV490_SCCB_SLAVE0_सूची, OV490_SCCB_SLAVE_READ);
	ov490_ग_लिखो_reg(dev, OV490_SCCB_SLAVE0_ADDR_HIGH, OV10640_CHIP_ID >> 8);
	ov490_ग_लिखो_reg(dev, OV490_SCCB_SLAVE0_ADDR_LOW, OV10640_CHIP_ID & 0xff);

	/* Trigger SCCB slave transaction and give it some समय to complete. */
	ov490_ग_लिखो_reg(dev, OV490_HOST_CMD, OV490_HOST_CMD_TRIGGER);
	usleep_range(1000, 1500);

	ov490_पढ़ो_reg(dev, OV490_SCCB_SLAVE0_सूची, &val);
	अगर (val != OV10640_ID_HIGH) अणु
		dev_err(dev->dev, "OV10640 ID mismatch: (0x%02x)\n", val);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(dev->dev, "OV10640 ID = 0x%2x\n", val);

	वापस 0;
पूर्ण

अटल पूर्णांक ov490_initialize(काष्ठा rdacm21_device *dev)
अणु
	u8 pid, ver, val;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Read OV490 Id to test communications. Give it up to 40msec to
	 * निकास from reset.
	 */
	क्रम (i = 0; i < OV490_PID_TIMEOUT; ++i) अणु
		ret = ov490_पढ़ो_reg(dev, OV490_PID, &pid);
		अगर (ret == 0)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (i == OV490_PID_TIMEOUT) अणु
		dev_err(dev->dev, "OV490 PID read failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = ov490_पढ़ो_reg(dev, OV490_VER, &ver);
	अगर (ret < 0)
		वापस ret;

	अगर (OV490_ID(pid, ver) != OV490_ID_VAL) अणु
		dev_err(dev->dev, "OV490 ID mismatch (0x%04x)\n",
			OV490_ID(pid, ver));
		वापस -ENODEV;
	पूर्ण

	/* Wait क्रम firmware boot by पढ़ोing streamon status. */
	क्रम (i = 0; i < OV490_OUTPUT_EN_TIMEOUT; ++i) अणु
		ov490_पढ़ो_reg(dev, OV490_ODS_CTRL, &val);
		अगर (val == OV490_ODS_CTRL_FRAME_OUTPUT_EN)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (i == OV490_OUTPUT_EN_TIMEOUT) अणु
		dev_err(dev->dev, "Timeout waiting for firmware boot\n");
		वापस -ENODEV;
	पूर्ण

	ret = ov10640_initialize(dev);
	अगर (ret)
		वापस ret;

	/* Program OV490 with रेजिस्टर-value table. */
	क्रम (i = 0; i < ARRAY_SIZE(ov490_regs_wizard); ++i) अणु
		ret = ov490_ग_लिखो(dev, ov490_regs_wizard[i].reg,
				  ov490_regs_wizard[i].val);
		अगर (ret < 0) अणु
			dev_err(dev->dev,
				"%s: register %u (0x%04x) write failed (%d)\n",
				__func__, i, ov490_regs_wizard[i].reg, ret);

			वापस -EIO;
		पूर्ण

		usleep_range(100, 150);
	पूर्ण

	/*
	 * The ISP is programmed with the content of a serial flash memory.
	 * Read the firmware configuration to reflect it through the V4L2 APIs.
	 */
	ov490_पढ़ो_reg(dev, OV490_ISP_HSIZE_HIGH, &val);
	dev->fmt.width = (val & 0xf) << 8;
	ov490_पढ़ो_reg(dev, OV490_ISP_HSIZE_LOW, &val);
	dev->fmt.width |= (val & 0xff);

	ov490_पढ़ो_reg(dev, OV490_ISP_VSIZE_HIGH, &val);
	dev->fmt.height = (val & 0xf) << 8;
	ov490_पढ़ो_reg(dev, OV490_ISP_VSIZE_LOW, &val);
	dev->fmt.height |= val & 0xff;

	/* Set bus width to 12 bits with [0:11] ordering. */
	ov490_ग_लिखो_reg(dev, OV490_DVP_CTRL3, 0x10);

	dev_info(dev->dev, "Identified RDACM21 camera module\n");

	वापस 0;
पूर्ण

अटल पूर्णांक rdacm21_initialize(काष्ठा rdacm21_device *dev)
अणु
	पूर्णांक ret;

	/* Verअगरy communication with the MAX9271: ping to wakeup. */
	dev->serializer.client->addr = MAX9271_DEFAULT_ADDR;
	i2c_smbus_पढ़ो_byte(dev->serializer.client);
	usleep_range(3000, 5000);

	/* Enable reverse channel and disable the serial link. */
	ret = max9271_set_serial_link(&dev->serializer, false);
	अगर (ret)
		वापस ret;

	/* Configure I2C bus at 105Kbps speed and configure GMSL. */
	ret = max9271_configure_i2c(&dev->serializer,
				    MAX9271_I2CSLVSH_469NS_234NS |
				    MAX9271_I2CSLVTO_1024US |
				    MAX9271_I2CMSTBT_105KBPS);
	अगर (ret)
		वापस ret;

	ret = max9271_verअगरy_id(&dev->serializer);
	अगर (ret)
		वापस ret;

	/* Enable GPIO1 and hold OV490 in reset during max9271 configuration. */
	ret = max9271_enable_gpios(&dev->serializer, MAX9271_GPIO1OUT);
	अगर (ret)
		वापस ret;

	ret = max9271_clear_gpios(&dev->serializer, MAX9271_GPIO1OUT);
	अगर (ret)
		वापस ret;

	ret = max9271_configure_gmsl_link(&dev->serializer);
	अगर (ret)
		वापस ret;

	ret = max9271_set_address(&dev->serializer, dev->addrs[0]);
	अगर (ret)
		वापस ret;
	dev->serializer.client->addr = dev->addrs[0];

	ret = max9271_set_translation(&dev->serializer, dev->addrs[1],
				      OV490_I2C_ADDRESS);
	अगर (ret)
		वापस ret;
	dev->isp->addr = dev->addrs[1];

	/* Release OV490 from reset and initialize it. */
	ret = max9271_set_gpios(&dev->serializer, MAX9271_GPIO1OUT);
	अगर (ret)
		वापस ret;
	usleep_range(3000, 5000);

	ret = ov490_initialize(dev);
	अगर (ret)
		वापस ret;

	/*
	 * Set reverse channel high threshold to increase noise immunity.
	 *
	 * This should be compensated by increasing the reverse channel
	 * amplitude on the remote deserializer side.
	 */
	वापस max9271_set_high_threshold(&dev->serializer, true);
पूर्ण

अटल पूर्णांक rdacm21_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा rdacm21_device *dev;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	dev = devm_kzalloc(&client->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->dev = &client->dev;
	dev->serializer.client = client;

	ret = of_property_पढ़ो_u32_array(client->dev.of_node, "reg",
					 dev->addrs, 2);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "Invalid DT reg property: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	/* Create the dummy I2C client क्रम the sensor. */
	dev->isp = i2c_new_dummy_device(client->adapter, OV490_I2C_ADDRESS);
	अगर (IS_ERR(dev->isp))
		वापस PTR_ERR(dev->isp);

	ret = rdacm21_initialize(dev);
	अगर (ret < 0)
		जाओ error;

	/* Initialize and रेजिस्टर the subdevice. */
	v4l2_i2c_subdev_init(&dev->sd, client, &rdacm21_subdev_ops);
	dev->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	v4l2_ctrl_handler_init(&dev->ctrls, 1);
	v4l2_ctrl_new_std(&dev->ctrls, शून्य, V4L2_CID_PIXEL_RATE,
			  OV10640_PIXEL_RATE, OV10640_PIXEL_RATE, 1,
			  OV10640_PIXEL_RATE);
	dev->sd.ctrl_handler = &dev->ctrls;

	ret = dev->ctrls.error;
	अगर (ret)
		जाओ error_मुक्त_ctrls;

	dev->pad.flags = MEDIA_PAD_FL_SOURCE;
	dev->sd.entity.flags |= MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&dev->sd.entity, 1, &dev->pad);
	अगर (ret < 0)
		जाओ error_मुक्त_ctrls;

	ep = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(&client->dev), शून्य);
	अगर (!ep) अणु
		dev_err(&client->dev,
			"Unable to get endpoint in node %pOF\n",
			client->dev.of_node);
		ret = -ENOENT;
		जाओ error_मुक्त_ctrls;
	पूर्ण
	dev->sd.fwnode = ep;

	ret = v4l2_async_रेजिस्टर_subdev(&dev->sd);
	अगर (ret)
		जाओ error_put_node;

	वापस 0;

error_put_node:
	fwnode_handle_put(dev->sd.fwnode);
error_मुक्त_ctrls:
	v4l2_ctrl_handler_मुक्त(&dev->ctrls);
error:
	i2c_unरेजिस्टर_device(dev->isp);

	वापस ret;
पूर्ण

अटल पूर्णांक rdacm21_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rdacm21_device *dev = sd_to_rdacm21(i2c_get_clientdata(client));

	v4l2_async_unरेजिस्टर_subdev(&dev->sd);
	v4l2_ctrl_handler_मुक्त(&dev->ctrls);
	i2c_unरेजिस्टर_device(dev->isp);
	fwnode_handle_put(dev->sd.fwnode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rdacm21_of_ids[] = अणु
	अणु .compatible = "imi,rdacm21" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rdacm21_of_ids);

अटल काष्ठा i2c_driver rdacm21_i2c_driver = अणु
	.driver	= अणु
		.name	= "rdacm21",
		.of_match_table = rdacm21_of_ids,
	पूर्ण,
	.probe_new	= rdacm21_probe,
	.हटाओ		= rdacm21_हटाओ,
पूर्ण;

module_i2c_driver(rdacm21_i2c_driver);

MODULE_DESCRIPTION("GMSL Camera driver for RDACM21");
MODULE_AUTHOR("Jacopo Mondi");
MODULE_LICENSE("GPL v2");
