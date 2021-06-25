<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Auvitek USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "au0828.h"
#समावेश "au0828-cards.h"
#समावेश "au8522.h"
#समावेश "media/tuner.h"
#समावेश "media/v4l2-common.h"

अटल व्योम hvr950q_cs5340_audio(व्योम *priv, पूर्णांक enable)
अणु
	/* Because the HVR-950q shares an i2s bus between the cs5340 and the
	   au8522, we need to hold cs5340 in reset when using the au8522 */
	काष्ठा au0828_dev *dev = priv;
	अगर (enable == 1)
		au0828_set(dev, REG_000, 0x10);
	अन्यथा
		au0828_clear(dev, REG_000, 0x10);
पूर्ण

/*
 * WARNING: There's a quirks table at sound/usb/quirks-table.h
 * that should also be updated every समय a new device with V4L2 support
 * is added here.
 */
काष्ठा au0828_board au0828_boards[] = अणु
	[AU0828_BOARD_UNKNOWN] = अणु
		.name	= "Unknown board",
		.tuner_type = -1U,
		.tuner_addr = ADDR_UNSET,
	पूर्ण,
	[AU0828_BOARD_HAUPPAUGE_HVR850] = अणु
		.name	= "Hauppauge HVR850",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.has_ir_i2c = 1,
		.has_analog = 1,
		.i2c_clk_भागider = AU0828_I2C_CLK_250KHZ,
		.input = अणु
			अणु
				.type = AU0828_VMUX_TELEVISION,
				.vmux = AU8522_COMPOSITE_CH4_SIF,
				.amux = AU8522_AUDIO_SIF,
			पूर्ण,
			अणु
				.type = AU0828_VMUX_COMPOSITE,
				.vmux = AU8522_COMPOSITE_CH1,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvr950q_cs5340_audio,
			पूर्ण,
			अणु
				.type = AU0828_VMUX_SVIDEO,
				.vmux = AU8522_SVIDEO_CH13,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvr950q_cs5340_audio,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AU0828_BOARD_HAUPPAUGE_HVR950Q] = अणु
		.name	= "Hauppauge HVR950Q",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.has_ir_i2c = 1,
		.has_analog = 1,
		.i2c_clk_भागider = AU0828_I2C_CLK_250KHZ,
		.input = अणु
			अणु
				.type = AU0828_VMUX_TELEVISION,
				.vmux = AU8522_COMPOSITE_CH4_SIF,
				.amux = AU8522_AUDIO_SIF,
			पूर्ण,
			अणु
				.type = AU0828_VMUX_COMPOSITE,
				.vmux = AU8522_COMPOSITE_CH1,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvr950q_cs5340_audio,
			पूर्ण,
			अणु
				.type = AU0828_VMUX_SVIDEO,
				.vmux = AU8522_SVIDEO_CH13,
				.amux = AU8522_AUDIO_NONE,
				.audio_setup = hvr950q_cs5340_audio,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL] = अणु
		.name	= "Hauppauge HVR950Q rev xxF8",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.i2c_clk_भागider = AU0828_I2C_CLK_250KHZ,
	पूर्ण,
	[AU0828_BOARD_DVICO_FUSIONHDTV7] = अणु
		.name	= "DViCO FusionHDTV USB",
		.tuner_type = TUNER_XC5000,
		.tuner_addr = 0x61,
		.i2c_clk_भागider = AU0828_I2C_CLK_250KHZ,
	पूर्ण,
	[AU0828_BOARD_HAUPPAUGE_WOODBURY] = अणु
		.name = "Hauppauge Woodbury",
		.tuner_type = TUNER_NXP_TDA18271,
		.tuner_addr = 0x60,
		.i2c_clk_भागider = AU0828_I2C_CLK_250KHZ,
	पूर्ण,
पूर्ण;

/* Tuner callback function क्रम au0828 boards. Currently only needed
 * क्रम HVR1500Q, which has an xc5000 tuner.
 */
पूर्णांक au0828_tuner_callback(व्योम *priv, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा au0828_dev *dev = priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	चयन (dev->boardnr) अणु
	हाल AU0828_BOARD_HAUPPAUGE_HVR850:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL:
	हाल AU0828_BOARD_DVICO_FUSIONHDTV7:
		अगर (command == 0) अणु
			/* Tuner Reset Command from xc5000 */
			/* Drive the tuner पूर्णांकo reset and out */
			au0828_clear(dev, REG_001, 2);
			mdelay(10);
			au0828_set(dev, REG_001, 2);
			mdelay(10);
			वापस 0;
		पूर्ण अन्यथा अणु
			pr_err("%s(): Unknown command.\n", __func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0; /* Should never be here */
पूर्ण

अटल व्योम hauppauge_eeprom(काष्ठा au0828_dev *dev, u8 *eeprom_data)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);
	dev->board.tuner_type = tv.tuner_type;

	/* Make sure we support the board model */
	चयन (tv.model) अणु
	हाल 72000: /* WinTV-HVR950q (Retail, IR, ATSC/QAM */
	हाल 72001: /* WinTV-HVR950q (Retail, IR, ATSC/QAM and analog video */
	हाल 72101: /* WinTV-HVR950q (Retail, IR, ATSC/QAM and analog video */
	हाल 72201: /* WinTV-HVR950q (OEM, IR, ATSC/QAM and analog video */
	हाल 72211: /* WinTV-HVR950q (OEM, IR, ATSC/QAM and analog video */
	हाल 72221: /* WinTV-HVR950q (OEM, IR, ATSC/QAM and analog video */
	हाल 72231: /* WinTV-HVR950q (OEM, IR, ATSC/QAM and analog video */
	हाल 72241: /* WinTV-HVR950q (OEM, No IR, ATSC/QAM and analog video */
	हाल 72251: /* WinTV-HVR950q (Retail, IR, ATSC/QAM and analog video */
	हाल 72261: /* WinTV-HVR950q (OEM, No IR, ATSC/QAM and analog video */
	हाल 72271: /* WinTV-HVR950q (OEM, No IR, ATSC/QAM and analog video */
	हाल 72281: /* WinTV-HVR950q (OEM, No IR, ATSC/QAM and analog video */
	हाल 72301: /* WinTV-HVR850 (Retail, IR, ATSC and analog video */
	हाल 72500: /* WinTV-HVR950q (OEM, No IR, ATSC/QAM */
		अवरोध;
	शेष:
		pr_warn("%s: warning: unknown hauppauge model #%d\n",
			__func__, tv.model);
		अवरोध;
	पूर्ण

	pr_info("%s: hauppauge eeprom: model=%d\n",
	       __func__, tv.model);
पूर्ण

व्योम au0828_card_analog_fe_setup(काष्ठा au0828_dev *dev);

व्योम au0828_card_setup(काष्ठा au0828_dev *dev)
अणु
	अटल u8 eeprom[256];

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (dev->i2c_rc == 0) अणु
		dev->i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_client, eeprom, माप(eeprom));
	पूर्ण

	चयन (dev->boardnr) अणु
	हाल AU0828_BOARD_HAUPPAUGE_HVR850:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL:
	हाल AU0828_BOARD_HAUPPAUGE_WOODBURY:
		अगर (dev->i2c_rc == 0)
			hauppauge_eeprom(dev, eeprom+0xa0);
		अवरोध;
	पूर्ण

	au0828_card_analog_fe_setup(dev);
पूर्ण

व्योम au0828_card_analog_fe_setup(काष्ठा au0828_dev *dev)
अणु
#अगर_घोषित CONFIG_VIDEO_AU0828_V4L2
	काष्ठा tuner_setup tun_setup;
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक mode_mask = T_ANALOG_TV;

	अगर (AUVI_INPUT(0).type != AU0828_VMUX_UNDEFINED) अणु
		/* Load the analog demodulator driver (note this would need to
		   be असलtracted out अगर we ever need to support a dअगरferent
		   demod) */
		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"au8522", 0x8e >> 1, शून्य);
		अगर (sd == शून्य)
			pr_err("analog subdev registration failed\n");
	पूर्ण

	/* Setup tuners */
	अगर (dev->board.tuner_type != TUNER_ABSENT && dev->board.has_analog) अणु
		/* Load the tuner module, which करोes the attach */
		sd = v4l2_i2c_new_subdev(&dev->v4l2_dev, &dev->i2c_adap,
				"tuner", dev->board.tuner_addr, शून्य);
		अगर (sd == शून्य)
			pr_err("tuner subdev registration fail\n");

		tun_setup.mode_mask      = mode_mask;
		tun_setup.type           = dev->board.tuner_type;
		tun_setup.addr           = dev->board.tuner_addr;
		tun_setup.tuner_callback = au0828_tuner_callback;
		v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_type_addr,
				     &tun_setup);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * The bridge has between 8 and 12 gpios.
 * Regs 1 and 0 deal with output enables.
 * Regs 3 and 2 deal with direction.
 */
व्योम au0828_gpio_setup(काष्ठा au0828_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	चयन (dev->boardnr) अणु
	हाल AU0828_BOARD_HAUPPAUGE_HVR850:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q:
	हाल AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL:
	हाल AU0828_BOARD_HAUPPAUGE_WOODBURY:
		/* GPIO's
		 * 4 - CS5340
		 * 5 - AU8522 Demodulator
		 * 6 - eeprom W/P
		 * 7 - घातer supply
		 * 9 - XC5000 Tuner
		 */

		/* Set relevant GPIOs as outमाला_दो (leave the EEPROM W/P
		   as an input since we will never touch it and it has
		   a pullup) */
		au0828_ग_लिखो(dev, REG_003, 0x02);
		au0828_ग_लिखो(dev, REG_002, 0x80 | 0x20 | 0x10);

		/* Into reset */
		au0828_ग_लिखो(dev, REG_001, 0x0);
		au0828_ग_लिखो(dev, REG_000, 0x0);
		msleep(50);

		/* Bring घातer supply out of reset */
		au0828_ग_लिखो(dev, REG_000, 0x80);
		msleep(50);

		/* Bring xc5000 and au8522 out of reset (leave the
		   cs5340 in reset until needed) */
		au0828_ग_लिखो(dev, REG_001, 0x02); /* xc5000 */
		au0828_ग_लिखो(dev, REG_000, 0x80 | 0x20); /* PS + au8522 */

		msleep(250);
		अवरोध;
	हाल AU0828_BOARD_DVICO_FUSIONHDTV7:
		/* GPIO's
		 * 6 - ?
		 * 8 - AU8522 Demodulator
		 * 9 - XC5000 Tuner
		 */

		/* Into reset */
		au0828_ग_लिखो(dev, REG_003, 0x02);
		au0828_ग_लिखो(dev, REG_002, 0xa0);
		au0828_ग_लिखो(dev, REG_001, 0x0);
		au0828_ग_लिखो(dev, REG_000, 0x0);
		msleep(100);

		/* Out of reset */
		au0828_ग_लिखो(dev, REG_003, 0x02);
		au0828_ग_लिखो(dev, REG_002, 0xa0);
		au0828_ग_लिखो(dev, REG_001, 0x02);
		au0828_ग_लिखो(dev, REG_000, 0xa0);
		msleep(250);
		अवरोध;
	पूर्ण
पूर्ण

/* table of devices that work with this driver */
काष्ठा usb_device_id au0828_usb_id_table[] = अणु
	अणु USB_DEVICE(0x2040, 0x7200),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7240),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR850 पूर्ण,
	अणु USB_DEVICE(0x0fe9, 0xd620),
		.driver_info = AU0828_BOARD_DVICO_FUSIONHDTV7 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7210),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7217),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x721b),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x721e),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x721f),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7280),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x0fd9, 0x0008),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7201),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7211),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7281),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q_MXL पूर्ण,
	अणु USB_DEVICE(0x05e1, 0x0480),
		.driver_info = AU0828_BOARD_HAUPPAUGE_WOODBURY पूर्ण,
	अणु USB_DEVICE(0x2040, 0x8200),
		.driver_info = AU0828_BOARD_HAUPPAUGE_WOODBURY पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7260),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7213),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु USB_DEVICE(0x2040, 0x7270),
		.driver_info = AU0828_BOARD_HAUPPAUGE_HVR950Q पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, au0828_usb_id_table);
