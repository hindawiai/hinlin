<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-camera.c - driver क्रम Empia EM25xx/27xx/28xx USB video capture devices
//
// Copyright (C) 2009 Mauro Carvalho Chehab <mchehab@kernel.org>
// Copyright (C) 2013 Frank Schथअfer <fschaefer.oss@googlemail.com>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/i2c.h>
#समावेश <linux/usb.h>
#समावेश <media/i2c/mt9v011.h>
#समावेश <media/v4l2-common.h>

/* Possible i2c addresses of Micron sensors */
अटल अचिन्हित लघु micron_sensor_addrs[] = अणु
	0xb8 >> 1,   /* MT9V111, MT9V403 */
	0xba >> 1,   /* MT9M001/011/111/112, MT9V011/012/112, MT9D011 */
	0x90 >> 1,   /* MT9V012/112, MT9D011 (alternative address) */
	I2C_CLIENT_END
पूर्ण;

/* Possible i2c addresses of Omnivision sensors */
अटल अचिन्हित लघु omnivision_sensor_addrs[] = अणु
	0x42 >> 1,   /* OV7725, OV7670/60/48 */
	0x60 >> 1,   /* OV2640, OV9650/53/55 */
	I2C_CLIENT_END
पूर्ण;

/* FIXME: Should be replaced by a proper mt9m111 driver */
अटल पूर्णांक em28xx_initialize_mt9m111(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर regs[][3] = अणु
		अणु 0x0d, 0x00, 0x01, पूर्ण,  /* reset and use शेषs */
		अणु 0x0d, 0x00, 0x00, पूर्ण,
		अणु 0x0a, 0x00, 0x21, पूर्ण,
		अणु 0x21, 0x04, 0x00, पूर्ण,  /* full पढ़ोout spd, no row/col skip */
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				&regs[i][0], 3);

	/* FIXME: This won't be creating a sensor at the media graph */

	वापस 0;
पूर्ण

/* FIXME: Should be replaced by a proper mt9m001 driver */
अटल पूर्णांक em28xx_initialize_mt9m001(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर regs[][3] = अणु
		अणु 0x0d, 0x00, 0x01, पूर्ण,
		अणु 0x0d, 0x00, 0x00, पूर्ण,
		अणु 0x04, 0x05, 0x00, पूर्ण,	/* hres = 1280 */
		अणु 0x03, 0x04, 0x00, पूर्ण,  /* vres = 1024 */
		अणु 0x20, 0x11, 0x00, पूर्ण,
		अणु 0x06, 0x00, 0x10, पूर्ण,
		अणु 0x2b, 0x00, 0x24, पूर्ण,
		अणु 0x2e, 0x00, 0x24, पूर्ण,
		अणु 0x35, 0x00, 0x24, पूर्ण,
		अणु 0x2d, 0x00, 0x20, पूर्ण,
		अणु 0x2c, 0x00, 0x20, पूर्ण,
		अणु 0x09, 0x0a, 0xd4, पूर्ण,
		अणु 0x35, 0x00, 0x57, पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus],
				&regs[i][0], 3);

	/* FIXME: This won't be creating a sensor at the media graph */

	वापस 0;
पूर्ण

/*
 * Probes Micron sensors with 8 bit address and 16 bit रेजिस्टर width
 */
अटल पूर्णांक em28xx_probe_sensor_micron(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret, i;
	अक्षर *name;
	u16 id;

	काष्ठा i2c_client *client = &dev->i2c_client[dev->def_i2c_bus];

	dev->em28xx_sensor = EM28XX_NOSENSOR;
	क्रम (i = 0; micron_sensor_addrs[i] != I2C_CLIENT_END; i++) अणु
		client->addr = micron_sensor_addrs[i];
		/* Read chip ID from रेजिस्टर 0x00 */
		ret = i2c_smbus_पढ़ो_word_data(client, 0x00); /* assumes LE */
		अगर (ret < 0) अणु
			अगर (ret != -ENXIO)
				dev_err(&dev->पूर्णांकf->dev,
					"couldn't read from i2c device 0x%02x: error %i\n",
				       client->addr << 1, ret);
			जारी;
		पूर्ण
		id = swab16(ret); /* LE -> BE */
		/* Read chip ID from रेजिस्टर 0xff */
		ret = i2c_smbus_पढ़ो_word_data(client, 0xff);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"couldn't read from i2c device 0x%02x: error %i\n",
				client->addr << 1, ret);
			जारी;
		पूर्ण
		/* Validate chip ID to be sure we have a Micron device */
		अगर (id != swab16(ret))
			जारी;
		/* Check chip ID */
		चयन (id) अणु
		हाल 0x1222:
			name = "MT9V012"; /* MI370 */ /* 640x480 */
			अवरोध;
		हाल 0x1229:
			name = "MT9V112"; /* 640x480 */
			अवरोध;
		हाल 0x1433:
			name = "MT9M011"; /* 1280x1024 */
			अवरोध;
		हाल 0x143a:    /* found in the ECS G200 */
			name = "MT9M111"; /* MI1310 */ /* 1280x1024 */
			dev->em28xx_sensor = EM28XX_MT9M111;
			अवरोध;
		हाल 0x148c:
			name = "MT9M112"; /* MI1320 */ /* 1280x1024 */
			अवरोध;
		हाल 0x1511:
			name = "MT9D011"; /* MI2010 */ /* 1600x1200 */
			अवरोध;
		हाल 0x8232:
		हाल 0x8243:	/* rev B */
			name = "MT9V011"; /* MI360 */ /* 640x480 */
			dev->em28xx_sensor = EM28XX_MT9V011;
			अवरोध;
		हाल 0x8431:
			name = "MT9M001"; /* 1280x1024 */
			dev->em28xx_sensor = EM28XX_MT9M001;
			अवरोध;
		शेष:
			dev_info(&dev->पूर्णांकf->dev,
				 "unknown Micron sensor detected: 0x%04x\n",
				 id);
			वापस 0;
		पूर्ण

		अगर (dev->em28xx_sensor == EM28XX_NOSENSOR)
			dev_info(&dev->पूर्णांकf->dev,
				 "unsupported sensor detected: %s\n", name);
		अन्यथा
			dev_info(&dev->पूर्णांकf->dev,
				 "sensor %s detected\n", name);

		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * Probes Omnivision sensors with 8 bit address and रेजिस्टर width
 */
अटल पूर्णांक em28xx_probe_sensor_omnivision(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret, i;
	अक्षर *name;
	u8 reg;
	u16 id;
	काष्ठा i2c_client *client = &dev->i2c_client[dev->def_i2c_bus];

	dev->em28xx_sensor = EM28XX_NOSENSOR;
	/*
	 * NOTE: these devices have the रेजिस्टर स्वतः incrementation disabled
	 * by शेष, so we have to use single byte पढ़ोs !
	 */
	क्रम (i = 0; omnivision_sensor_addrs[i] != I2C_CLIENT_END; i++) अणु
		client->addr = omnivision_sensor_addrs[i];
		/* Read manufacturer ID from रेजिस्टरs 0x1c-0x1d (BE) */
		reg = 0x1c;
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0) अणु
			अगर (ret != -ENXIO)
				dev_err(&dev->पूर्णांकf->dev,
					"couldn't read from i2c device 0x%02x: error %i\n",
					client->addr << 1, ret);
			जारी;
		पूर्ण
		id = ret << 8;
		reg = 0x1d;
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"couldn't read from i2c device 0x%02x: error %i\n",
				client->addr << 1, ret);
			जारी;
		पूर्ण
		id += ret;
		/* Check manufacturer ID */
		अगर (id != 0x7fa2)
			जारी;
		/* Read product ID from रेजिस्टरs 0x0a-0x0b (BE) */
		reg = 0x0a;
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"couldn't read from i2c device 0x%02x: error %i\n",
				client->addr << 1, ret);
			जारी;
		पूर्ण
		id = ret << 8;
		reg = 0x0b;
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"couldn't read from i2c device 0x%02x: error %i\n",
				client->addr << 1, ret);
			जारी;
		पूर्ण
		id += ret;
		/* Check product ID */
		चयन (id) अणु
		हाल 0x2642:
			name = "OV2640";
			dev->em28xx_sensor = EM28XX_OV2640;
			अवरोध;
		हाल 0x7648:
			name = "OV7648";
			अवरोध;
		हाल 0x7660:
			name = "OV7660";
			अवरोध;
		हाल 0x7673:
			name = "OV7670";
			अवरोध;
		हाल 0x7720:
			name = "OV7720";
			अवरोध;
		हाल 0x7721:
			name = "OV7725";
			अवरोध;
		हाल 0x9648: /* Rev 2 */
		हाल 0x9649: /* Rev 3 */
			name = "OV9640";
			अवरोध;
		हाल 0x9650:
		हाल 0x9652: /* OV9653 */
			name = "OV9650";
			अवरोध;
		हाल 0x9656: /* Rev 4 */
		हाल 0x9657: /* Rev 5 */
			name = "OV9655";
			अवरोध;
		शेष:
			dev_info(&dev->पूर्णांकf->dev,
				 "unknown OmniVision sensor detected: 0x%04x\n",
				id);
			वापस 0;
		पूर्ण

		अगर (dev->em28xx_sensor == EM28XX_NOSENSOR)
			dev_info(&dev->पूर्णांकf->dev,
				 "unsupported sensor detected: %s\n", name);
		अन्यथा
			dev_info(&dev->पूर्णांकf->dev,
				 "sensor %s detected\n", name);

		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

पूर्णांक em28xx_detect_sensor(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret;

	ret = em28xx_probe_sensor_micron(dev);

	अगर (dev->em28xx_sensor == EM28XX_NOSENSOR && ret < 0)
		ret = em28xx_probe_sensor_omnivision(dev);

	/*
	 * NOTE: the Winकरोws driver also probes i2c addresses
	 *       0x22 (Samsung ?) and 0x66 (Kodak ?)
	 */

	अगर (dev->em28xx_sensor == EM28XX_NOSENSOR && ret < 0) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "No sensor detected\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक em28xx_init_camera(काष्ठा em28xx *dev)
अणु
	काष्ठा i2c_client *client = &dev->i2c_client[dev->def_i2c_bus];
	काष्ठा i2c_adapter *adap = &dev->i2c_adap[dev->def_i2c_bus];
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	चयन (dev->em28xx_sensor) अणु
	हाल EM28XX_MT9V011:
	अणु
		काष्ठा mt9v011_platक्रमm_data pdata;
		काष्ठा i2c_board_info mt9v011_info = अणु
			.type = "mt9v011",
			.addr = client->addr,
			.platक्रमm_data = &pdata,
		पूर्ण;

		v4l2->sensor_xres = 640;
		v4l2->sensor_yres = 480;

		/*
		 * FIXME: mt9v011 uses I2S speed as xtal clk - at least with
		 * the Silvercrest cam I have here क्रम testing - क्रम higher
		 * resolutions, a high घड़ी cause horizontal artअगरacts, so we
		 * need to use a lower xclk frequency.
		 * Yet, it would be possible to adjust xclk depending on the
		 * desired resolution, since this affects directly the
		 * frame rate.
		 */
		dev->board.xclk = EM28XX_XCLK_FREQUENCY_4_3MHZ;
		em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK, dev->board.xclk);
		v4l2->sensor_xtal = 4300000;
		pdata.xtal = v4l2->sensor_xtal;
		अगर (शून्य ==
		    v4l2_i2c_new_subdev_board(&v4l2->v4l2_dev, adap,
					      &mt9v011_info, शून्य))
			वापस -ENODEV;
		v4l2->vinmode = EM28XX_VINMODE_RGB8_GRBG;
		v4l2->vinctl = 0x00;

		अवरोध;
	पूर्ण
	हाल EM28XX_MT9M001:
		v4l2->sensor_xres = 1280;
		v4l2->sensor_yres = 1024;

		em28xx_initialize_mt9m001(dev);

		v4l2->vinmode = EM28XX_VINMODE_RGB8_BGGR;
		v4l2->vinctl = 0x00;

		अवरोध;
	हाल EM28XX_MT9M111:
		v4l2->sensor_xres = 640;
		v4l2->sensor_yres = 512;

		dev->board.xclk = EM28XX_XCLK_FREQUENCY_48MHZ;
		em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK, dev->board.xclk);
		em28xx_initialize_mt9m111(dev);

		v4l2->vinmode = EM28XX_VINMODE_YUV422_UYVY;
		v4l2->vinctl = 0x00;

		अवरोध;
	हाल EM28XX_OV2640:
	अणु
		काष्ठा v4l2_subdev *subdev;
		काष्ठा i2c_board_info ov2640_info = अणु
			.type = "ov2640",
			.flags = I2C_CLIENT_SCCB,
			.addr = client->addr,
		पूर्ण;
		काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
			.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		पूर्ण;

		/*
		 * FIXME: sensor supports resolutions up to 1600x1200, but
		 * resolution setting/चयनing needs to be modअगरied to
		 * - चयन sensor output resolution (including further
		 *   configuration changes)
		 * - adjust bridge xclk
		 * - disable 16 bit (12 bit) output क्रमmats on high resolutions
		 */
		v4l2->sensor_xres = 640;
		v4l2->sensor_yres = 480;

		subdev =
		     v4l2_i2c_new_subdev_board(&v4l2->v4l2_dev, adap,
					       &ov2640_info, शून्य);
		अगर (!subdev)
			वापस -ENODEV;

		क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_2X8;
		क्रमmat.क्रमmat.width = 640;
		क्रमmat.क्रमmat.height = 480;
		v4l2_subdev_call(subdev, pad, set_fmt, शून्य, &क्रमmat);

		/* NOTE: क्रम UXGA=1600x1200 चयन to 12MHz */
		dev->board.xclk = EM28XX_XCLK_FREQUENCY_24MHZ;
		em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK, dev->board.xclk);
		v4l2->vinmode = EM28XX_VINMODE_YUV422_YUYV;
		v4l2->vinctl = 0x00;

		अवरोध;
	पूर्ण
	हाल EM28XX_NOSENSOR:
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_init_camera);
