<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-core.c - driver क्रम Empia EM2800/EM2820/2840 USB video capture devices
//
// Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
//		      Markus Rechberger <mrechberger@gmail.com>
//		      Mauro Carvalho Chehab <mchehab@kernel.org>
//		      Sascha Sommer <saschasommer@मुक्तnet.de>
// Copyright (C) 2012 Frank Schथअfer <fschaefer.oss@googlemail.com>
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

#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <sound/ac97_codec.h>
#समावेश <media/v4l2-common.h>

#घोषणा DRIVER_AUTHOR "Ludovico Cavedon <cavedon@sssup.it>, " \
		      "Markus Rechberger <mrechberger@gmail.com>, " \
		      "Mauro Carvalho Chehab <mchehab@kernel.org>, " \
		      "Sascha Sommer <saschasommer@freenet.de>"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
MODULE_VERSION(EM28XX_VERSION);

/* #घोषणा ENABLE_DEBUG_ISOC_FRAMES */

अटल अचिन्हित पूर्णांक core_debug;
module_param(core_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(core_debug, "enable debug messages [core and isoc]");

#घोषणा em28xx_coredbg(fmt, arg...) करो अणु				\
	अगर (core_debug)							\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "core: %s: " fmt, __func__, ## arg);		\
पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक reg_debug;
module_param(reg_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(reg_debug, "enable debug messages [URB reg]");

#घोषणा em28xx_regdbg(fmt, arg...) करो अणु				\
	अगर (reg_debug)							\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "reg: %s: " fmt, __func__, ## arg);		\
पूर्ण जबतक (0)

/* FIXME: करोn't abuse core_debug */
#घोषणा em28xx_isocdbg(fmt, arg...) करो अणु				\
	अगर (core_debug)							\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "core: %s: " fmt, __func__, ## arg);		\
पूर्ण जबतक (0)

/*
 * em28xx_पढ़ो_reg_req()
 * पढ़ोs data from the usb device specअगरying bRequest
 */
पूर्णांक em28xx_पढ़ो_reg_req_len(काष्ठा em28xx *dev, u8 req, u16 reg,
			    अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक pipe = usb_rcvctrlpipe(udev, 0);

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (len > URB_MAX_CTRL_SIZE)
		वापस -EINVAL;

	mutex_lock(&dev->ctrl_urb_lock);
	ret = usb_control_msg(udev, pipe, req,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0x0000, reg, dev->urb_buf, len, HZ);
	अगर (ret < 0) अणु
		em28xx_regdbg("(pipe 0x%08x): IN:  %02x %02x %02x %02x %02x %02x %02x %02x  failed with error %i\n",
			      pipe,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      req, 0, 0,
			      reg & 0xff, reg >> 8,
			      len & 0xff, len >> 8, ret);
		mutex_unlock(&dev->ctrl_urb_lock);
		वापस usb_translate_errors(ret);
	पूर्ण

	अगर (len)
		स_नकल(buf, dev->urb_buf, len);

	mutex_unlock(&dev->ctrl_urb_lock);

	em28xx_regdbg("(pipe 0x%08x): IN:  %02x %02x %02x %02x %02x %02x %02x %02x <<< %*ph\n",
		      pipe, USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		      req, 0, 0,
		      reg & 0xff, reg >> 8,
		      len & 0xff, len >> 8, len, buf);

	वापस ret;
पूर्ण

/*
 * em28xx_पढ़ो_reg_req()
 * पढ़ोs data from the usb device specअगरying bRequest
 */
पूर्णांक em28xx_पढ़ो_reg_req(काष्ठा em28xx *dev, u8 req, u16 reg)
अणु
	पूर्णांक ret;
	u8 val;

	ret = em28xx_पढ़ो_reg_req_len(dev, req, reg, &val, 1);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

पूर्णांक em28xx_पढ़ो_reg(काष्ठा em28xx *dev, u16 reg)
अणु
	वापस em28xx_पढ़ो_reg_req(dev, USB_REQ_GET_STATUS, reg);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_पढ़ो_reg);

/*
 * em28xx_ग_लिखो_regs_req()
 * sends data to the usb device, specअगरying bRequest
 */
पूर्णांक em28xx_ग_लिखो_regs_req(काष्ठा em28xx *dev, u8 req, u16 reg, अक्षर *buf,
			  पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक pipe = usb_sndctrlpipe(udev, 0);

	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (len < 1 || len > URB_MAX_CTRL_SIZE)
		वापस -EINVAL;

	mutex_lock(&dev->ctrl_urb_lock);
	स_नकल(dev->urb_buf, buf, len);
	ret = usb_control_msg(udev, pipe, req,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0x0000, reg, dev->urb_buf, len, HZ);
	mutex_unlock(&dev->ctrl_urb_lock);

	अगर (ret < 0) अणु
		em28xx_regdbg("(pipe 0x%08x): OUT:  %02x %02x %02x %02x %02x %02x %02x %02x >>> %*ph  failed with error %i\n",
			      pipe,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      req, 0, 0,
			      reg & 0xff, reg >> 8,
			      len & 0xff, len >> 8, len, buf, ret);
		वापस usb_translate_errors(ret);
	पूर्ण

	em28xx_regdbg("(pipe 0x%08x): OUT:  %02x %02x %02x %02x %02x %02x %02x %02x >>> %*ph\n",
		      pipe,
		      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		      req, 0, 0,
		      reg & 0xff, reg >> 8,
		      len & 0xff, len >> 8, len, buf);

	अगर (dev->रुको_after_ग_लिखो)
		msleep(dev->रुको_after_ग_लिखो);

	वापस ret;
पूर्ण

पूर्णांक em28xx_ग_लिखो_regs(काष्ठा em28xx *dev, u16 reg, अक्षर *buf, पूर्णांक len)
अणु
	वापस em28xx_ग_लिखो_regs_req(dev, USB_REQ_GET_STATUS, reg, buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_ग_लिखो_regs);

/* Write a single रेजिस्टर */
पूर्णांक em28xx_ग_लिखो_reg(काष्ठा em28xx *dev, u16 reg, u8 val)
अणु
	वापस em28xx_ग_लिखो_regs(dev, reg, &val, 1);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_ग_लिखो_reg);

/*
 * em28xx_ग_लिखो_reg_bits()
 * sets only some bits (specअगरied by biपंचांगask) of a रेजिस्टर, by first पढ़ोing
 * the actual value
 */
पूर्णांक em28xx_ग_लिखो_reg_bits(काष्ठा em28xx *dev, u16 reg, u8 val,
			  u8 biपंचांगask)
अणु
	पूर्णांक oldval;
	u8 newval;

	oldval = em28xx_पढ़ो_reg(dev, reg);
	अगर (oldval < 0)
		वापस oldval;

	newval = (((u8)oldval) & ~biपंचांगask) | (val & biपंचांगask);

	वापस em28xx_ग_लिखो_regs(dev, reg, &newval, 1);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_ग_लिखो_reg_bits);

/*
 * em28xx_toggle_reg_bits()
 * toggles/inverts the bits (specअगरied by biपंचांगask) of a रेजिस्टर
 */
पूर्णांक em28xx_toggle_reg_bits(काष्ठा em28xx *dev, u16 reg, u8 biपंचांगask)
अणु
	पूर्णांक oldval;
	u8 newval;

	oldval = em28xx_पढ़ो_reg(dev, reg);
	अगर (oldval < 0)
		वापस oldval;

	newval = (~oldval & biपंचांगask) | (oldval & ~biपंचांगask);

	वापस em28xx_ग_लिखो_reg(dev, reg, newval);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_toggle_reg_bits);

/*
 * em28xx_is_ac97_पढ़ोy()
 * Checks अगर ac97 is पढ़ोy
 */
अटल पूर्णांक em28xx_is_ac97_पढ़ोy(काष्ठा em28xx *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(EM28XX_AC97_XFER_TIMEOUT);
	पूर्णांक ret;

	/* Wait up to 50 ms क्रम AC97 command to complete */
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		ret = em28xx_पढ़ो_reg(dev, EM28XX_R43_AC97BUSY);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & 0x01))
			वापस 0;
		msleep(5);
	पूर्ण

	dev_warn(&dev->पूर्णांकf->dev,
		 "AC97 command still being executed: not handled properly!\n");
	वापस -EBUSY;
पूर्ण

/*
 * em28xx_पढ़ो_ac97()
 * ग_लिखो a 16 bit value to the specअगरied AC97 address (LSB first!)
 */
पूर्णांक em28xx_पढ़ो_ac97(काष्ठा em28xx *dev, u8 reg)
अणु
	पूर्णांक ret;
	u8 addr = (reg & 0x7f) | 0x80;
	__le16 val;

	ret = em28xx_is_ac97_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	ret = em28xx_ग_लिखो_regs(dev, EM28XX_R42_AC97ADDR, &addr, 1);
	अगर (ret < 0)
		वापस ret;

	ret = dev->em28xx_पढ़ो_reg_req_len(dev, 0, EM28XX_R40_AC97LSB,
					   (u8 *)&val, माप(val));

	अगर (ret < 0)
		वापस ret;
	वापस le16_to_cpu(val);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_पढ़ो_ac97);

/*
 * em28xx_ग_लिखो_ac97()
 * ग_लिखो a 16 bit value to the specअगरied AC97 address (LSB first!)
 */
पूर्णांक em28xx_ग_लिखो_ac97(काष्ठा em28xx *dev, u8 reg, u16 val)
अणु
	पूर्णांक ret;
	u8 addr = reg & 0x7f;
	__le16 value;

	value = cpu_to_le16(val);

	ret = em28xx_is_ac97_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	ret = em28xx_ग_लिखो_regs(dev, EM28XX_R40_AC97LSB, (u8 *)&value, 2);
	अगर (ret < 0)
		वापस ret;

	ret = em28xx_ग_लिखो_regs(dev, EM28XX_R42_AC97ADDR, &addr, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_ग_लिखो_ac97);

काष्ठा em28xx_vol_itable अणु
	क्रमागत em28xx_amux mux;
	u8		 reg;
पूर्ण;

अटल काष्ठा em28xx_vol_itable inमाला_दो[] = अणु
	अणु EM28XX_AMUX_VIDEO,	AC97_VIDEO	पूर्ण,
	अणु EM28XX_AMUX_LINE_IN,	AC97_LINE	पूर्ण,
	अणु EM28XX_AMUX_PHONE,	AC97_PHONE	पूर्ण,
	अणु EM28XX_AMUX_MIC,	AC97_MIC	पूर्ण,
	अणु EM28XX_AMUX_CD,	AC97_CD		पूर्ण,
	अणु EM28XX_AMUX_AUX,	AC97_AUX	पूर्ण,
	अणु EM28XX_AMUX_PCM_OUT,	AC97_PCM	पूर्ण,
पूर्ण;

अटल पूर्णांक set_ac97_input(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret, i;
	क्रमागत em28xx_amux amux = dev->ctl_ainput;

	/*
	 * EM28XX_AMUX_VIDEO2 is a special हाल used to indicate that
	 * em28xx should poपूर्णांक to LINE IN, जबतक AC97 should use VIDEO
	 */
	अगर (amux == EM28XX_AMUX_VIDEO2)
		amux = EM28XX_AMUX_VIDEO;

	/* Mute all entres but the one that were selected */
	क्रम (i = 0; i < ARRAY_SIZE(inमाला_दो); i++) अणु
		अगर (amux == inमाला_दो[i].mux)
			ret = em28xx_ग_लिखो_ac97(dev, inमाला_दो[i].reg, 0x0808);
		अन्यथा
			ret = em28xx_ग_लिखो_ac97(dev, inमाला_दो[i].reg, 0x8000);

		अगर (ret < 0)
			dev_warn(&dev->पूर्णांकf->dev,
				 "couldn't setup AC97 register %d\n",
				 inमाला_दो[i].reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_set_audio_source(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret;
	u8 input;

	अगर (dev->board.is_em2800) अणु
		अगर (dev->ctl_ainput == EM28XX_AMUX_VIDEO)
			input = EM2800_AUDIO_SRC_TUNER;
		अन्यथा
			input = EM2800_AUDIO_SRC_LINE;

		ret = em28xx_ग_लिखो_regs(dev, EM2800_R08_AUDIOSRC, &input, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (dev->has_msp34xx) अणु
		input = EM28XX_AUDIO_SRC_TUNER;
	पूर्ण अन्यथा अणु
		चयन (dev->ctl_ainput) अणु
		हाल EM28XX_AMUX_VIDEO:
			input = EM28XX_AUDIO_SRC_TUNER;
			अवरोध;
		शेष:
			input = EM28XX_AUDIO_SRC_LINE;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (dev->board.mute_gpio && dev->mute)
		em28xx_gpio_set(dev, dev->board.mute_gpio);
	अन्यथा
		em28xx_gpio_set(dev, INPUT(dev->ctl_input)->gpio);

	ret = em28xx_ग_लिखो_reg_bits(dev, EM28XX_R0E_AUDIOSRC, input, 0xc0);
	अगर (ret < 0)
		वापस ret;
	usleep_range(10000, 11000);

	चयन (dev->audio_mode.ac97) अणु
	हाल EM28XX_NO_AC97:
		अवरोध;
	शेष:
		ret = set_ac97_input(dev);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा em28xx_vol_otable अणु
	क्रमागत em28xx_aout mux;
	u8		 reg;
पूर्ण;

अटल स्थिर काष्ठा em28xx_vol_otable outमाला_दो[] = अणु
	अणु EM28XX_AOUT_MASTER, AC97_MASTER		पूर्ण,
	अणु EM28XX_AOUT_LINE,   AC97_HEADPHONE		पूर्ण,
	अणु EM28XX_AOUT_MONO,   AC97_MASTER_MONO		पूर्ण,
	अणु EM28XX_AOUT_LFE,    AC97_CENTER_LFE_MASTER	पूर्ण,
	अणु EM28XX_AOUT_SURR,   AC97_SURROUND_MASTER	पूर्ण,
पूर्ण;

पूर्णांक em28xx_audio_analog_set(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret, i;
	u8 xclk;

	अगर (dev->पूर्णांक_audio_type == EM28XX_INT_AUDIO_NONE)
		वापस 0;

	/*
	 * It is assumed that all devices use master volume क्रम output.
	 * It would be possible to use also line output.
	 */
	अगर (dev->audio_mode.ac97 != EM28XX_NO_AC97) अणु
		/* Mute all outमाला_दो */
		क्रम (i = 0; i < ARRAY_SIZE(outमाला_दो); i++) अणु
			ret = em28xx_ग_लिखो_ac97(dev, outमाला_दो[i].reg, 0x8000);
			अगर (ret < 0)
				dev_warn(&dev->पूर्णांकf->dev,
					 "couldn't setup AC97 register %d\n",
					 outमाला_दो[i].reg);
		पूर्ण
	पूर्ण

	xclk = dev->board.xclk & 0x7f;
	अगर (!dev->mute)
		xclk |= EM28XX_XCLK_AUDIO_UNMUTE;

	ret = em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK, xclk);
	अगर (ret < 0)
		वापस ret;
	usleep_range(10000, 11000);

	/* Selects the proper audio input */
	ret = em28xx_set_audio_source(dev);

	/* Sets volume */
	अगर (dev->audio_mode.ac97 != EM28XX_NO_AC97) अणु
		पूर्णांक vol;

		em28xx_ग_लिखो_ac97(dev, AC97_POWERDOWN, 0x4200);
		em28xx_ग_लिखो_ac97(dev, AC97_EXTENDED_STATUS, 0x0031);
		em28xx_ग_लिखो_ac97(dev, AC97_PCM_LR_ADC_RATE, 0xbb80);

		/* LSB: left channel - both channels with the same level */
		vol = (0x1f - dev->volume) | ((0x1f - dev->volume) << 8);

		/* Mute device, अगर needed */
		अगर (dev->mute)
			vol |= 0x8000;

		/* Sets volume */
		क्रम (i = 0; i < ARRAY_SIZE(outमाला_दो); i++) अणु
			अगर (dev->ctl_aoutput & outमाला_दो[i].mux)
				ret = em28xx_ग_लिखो_ac97(dev, outमाला_दो[i].reg,
							vol);
			अगर (ret < 0)
				dev_warn(&dev->पूर्णांकf->dev,
					 "couldn't setup AC97 register %d\n",
					 outमाला_दो[i].reg);
		पूर्ण

		अगर (dev->ctl_aoutput & EM28XX_AOUT_PCM_IN) अणु
			पूर्णांक sel = ac97_वापस_record_select(dev->ctl_aoutput);

			/*
			 * Use the same input क्रम both left and right
			 * channels
			 */
			sel |= (sel << 8);

			em28xx_ग_लिखो_ac97(dev, AC97_REC_SEL, sel);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_audio_analog_set);

पूर्णांक em28xx_audio_setup(काष्ठा em28xx *dev)
अणु
	पूर्णांक vid1, vid2, feat, cfg;
	u32 vid = 0;
	u8 i2s_samplerates;

	अगर (dev->chip_id == CHIP_ID_EM2870 ||
	    dev->chip_id == CHIP_ID_EM2874 ||
	    dev->chip_id == CHIP_ID_EM28174 ||
	    dev->chip_id == CHIP_ID_EM28178) अणु
		/* Digital only device - करोn't load any alsa module */
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_NONE;
		dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		वापस 0;
	पूर्ण

	/* See how this device is configured */
	cfg = em28xx_पढ़ो_reg(dev, EM28XX_R00_CHIPCFG);
	dev_info(&dev->पूर्णांकf->dev, "Config register raw data: 0x%02x\n", cfg);
	अगर (cfg < 0) अणु /* Register पढ़ो error */
		/* Be conservative */
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_AC97;
	पूर्ण अन्यथा अगर ((cfg & EM28XX_CHIPCFG_AUDIOMASK) == 0x00) अणु
		/* The device करोesn't have venकरोr audio at all */
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_NONE;
		dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		वापस 0;
	पूर्ण अन्यथा अगर ((cfg & EM28XX_CHIPCFG_AUDIOMASK) != EM28XX_CHIPCFG_AC97) अणु
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_I2S;
		अगर (dev->chip_id < CHIP_ID_EM2860 &&
		    (cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
		    EM2820_CHIPCFG_I2S_1_SAMPRATE)
			i2s_samplerates = 1;
		अन्यथा अगर (dev->chip_id >= CHIP_ID_EM2860 &&
			 (cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
			 EM2860_CHIPCFG_I2S_5_SAMPRATES)
			i2s_samplerates = 5;
		अन्यथा
			i2s_samplerates = 3;
		dev_info(&dev->पूर्णांकf->dev, "I2S Audio (%d sample rate(s))\n",
			 i2s_samplerates);
		/* Skip the code that करोes AC97 venकरोr detection */
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		जाओ init_audio;
	पूर्ण अन्यथा अणु
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_AC97;
	पूर्ण

	dev->audio_mode.ac97 = EM28XX_AC97_OTHER;

	vid1 = em28xx_पढ़ो_ac97(dev, AC97_VENDOR_ID1);
	अगर (vid1 < 0) अणु
		/*
		 * Device likely करोesn't support AC97
		 * Note: (some) em2800 devices without eeprom reports 0x91 on
		 *	 CHIPCFG रेजिस्टर, even not having an AC97 chip
		 */
		dev_warn(&dev->पूर्णांकf->dev,
			 "AC97 chip type couldn't be determined\n");
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		अगर (dev->usb_audio_type == EM28XX_USB_AUDIO_VENDOR)
			dev->usb_audio_type = EM28XX_USB_AUDIO_NONE;
		dev->पूर्णांक_audio_type = EM28XX_INT_AUDIO_NONE;
		जाओ init_audio;
	पूर्ण

	vid2 = em28xx_पढ़ो_ac97(dev, AC97_VENDOR_ID2);
	अगर (vid2 < 0)
		जाओ init_audio;

	vid = vid1 << 16 | vid2;
	dev_warn(&dev->पूर्णांकf->dev, "AC97 vendor ID = 0x%08x\n", vid);

	feat = em28xx_पढ़ो_ac97(dev, AC97_RESET);
	अगर (feat < 0)
		जाओ init_audio;

	dev_warn(&dev->पूर्णांकf->dev, "AC97 features = 0x%04x\n", feat);

	/* Try to identअगरy what audio processor we have */
	अगर ((vid == 0xffffffff || vid == 0x83847650) && feat == 0x6a90)
		dev->audio_mode.ac97 = EM28XX_AC97_EM202;
	अन्यथा अगर ((vid >> 8) == 0x838476)
		dev->audio_mode.ac97 = EM28XX_AC97_SIGMATEL;

init_audio:
	/* Reports detected AC97 processor */
	चयन (dev->audio_mode.ac97) अणु
	हाल EM28XX_NO_AC97:
		dev_info(&dev->पूर्णांकf->dev, "No AC97 audio processor\n");
		अवरोध;
	हाल EM28XX_AC97_EM202:
		dev_info(&dev->पूर्णांकf->dev,
			 "Empia 202 AC97 audio processor detected\n");
		अवरोध;
	हाल EM28XX_AC97_SIGMATEL:
		dev_info(&dev->पूर्णांकf->dev,
			 "Sigmatel audio processor detected (stac 97%02x)\n",
			 vid & 0xff);
		अवरोध;
	हाल EM28XX_AC97_OTHER:
		dev_warn(&dev->पूर्णांकf->dev,
			 "Unknown AC97 audio processor detected!\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस em28xx_audio_analog_set(dev);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_audio_setup);

स्थिर काष्ठा em28xx_led *em28xx_find_led(काष्ठा em28xx *dev,
					 क्रमागत em28xx_led_role role)
अणु
	अगर (dev->board.leds) अणु
		u8 k = 0;

		जबतक (dev->board.leds[k].role >= 0 &&
		       dev->board.leds[k].role < EM28XX_NUM_LED_ROLES) अणु
			अगर (dev->board.leds[k].role == role)
				वापस &dev->board.leds[k];
			k++;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_find_led);

पूर्णांक em28xx_capture_start(काष्ठा em28xx *dev, पूर्णांक start)
अणु
	पूर्णांक rc;
	स्थिर काष्ठा em28xx_led *led = शून्य;

	अगर (dev->chip_id == CHIP_ID_EM2874 ||
	    dev->chip_id == CHIP_ID_EM2884 ||
	    dev->chip_id == CHIP_ID_EM28174 ||
	    dev->chip_id == CHIP_ID_EM28178) अणु
		/* The Transport Stream Enable Register moved in em2874 */
		अगर (dev->dvb_xfer_bulk) अणु
			/* Max Tx Size = 188 * 256 = 48128 - LCM(188,512) * 2 */
			em28xx_ग_लिखो_reg(dev, (dev->ts == PRIMARY_TS) ?
					 EM2874_R5D_TS1_PKT_SIZE :
					 EM2874_R5E_TS2_PKT_SIZE,
					 0xff);
		पूर्ण अन्यथा अणु
			/* ISOC Maximum Transfer Size = 188 * 5 */
			em28xx_ग_लिखो_reg(dev, (dev->ts == PRIMARY_TS) ?
					 EM2874_R5D_TS1_PKT_SIZE :
					 EM2874_R5E_TS2_PKT_SIZE,
					 dev->dvb_max_pkt_size_isoc / 188);
		पूर्ण
		अगर (dev->ts == PRIMARY_TS)
			rc = em28xx_ग_लिखो_reg_bits(dev,
						   EM2874_R5F_TS_ENABLE,
						   start ? EM2874_TS1_CAPTURE_ENABLE : 0x00,
						   EM2874_TS1_CAPTURE_ENABLE | EM2874_TS1_FILTER_ENABLE | EM2874_TS1_शून्य_DISCARD);
		अन्यथा
			rc = em28xx_ग_लिखो_reg_bits(dev,
						   EM2874_R5F_TS_ENABLE,
						   start ? EM2874_TS2_CAPTURE_ENABLE : 0x00,
						   EM2874_TS2_CAPTURE_ENABLE | EM2874_TS2_FILTER_ENABLE | EM2874_TS2_शून्य_DISCARD);
	पूर्ण अन्यथा अणु
		/* FIXME: which is the best order? */
		/* video रेजिस्टरs are sampled by VREF */
		rc = em28xx_ग_लिखो_reg_bits(dev, EM28XX_R0C_USBSUSP,
					   start ? 0x10 : 0x00, 0x10);
		अगर (rc < 0)
			वापस rc;

		अगर (start) अणु
			अगर (dev->is_webcam)
				rc = em28xx_ग_लिखो_reg(dev, 0x13, 0x0c);

			/* Enable video capture */
			rc = em28xx_ग_लिखो_reg(dev, 0x48, 0x00);
			अगर (rc < 0)
				वापस rc;

			अगर (dev->mode == EM28XX_ANALOG_MODE)
				rc = em28xx_ग_लिखो_reg(dev,
						      EM28XX_R12_VINENABLE,
						      0x67);
			अन्यथा
				rc = em28xx_ग_लिखो_reg(dev,
						      EM28XX_R12_VINENABLE,
						      0x37);
			अगर (rc < 0)
				वापस rc;

			usleep_range(10000, 11000);
		पूर्ण अन्यथा अणु
			/* disable video capture */
			rc = em28xx_ग_लिखो_reg(dev, EM28XX_R12_VINENABLE, 0x27);
		पूर्ण
	पूर्ण

	अगर (dev->mode == EM28XX_ANALOG_MODE)
		led = em28xx_find_led(dev, EM28XX_LED_ANALOG_CAPTURING);
	अन्यथा अगर (dev->ts == PRIMARY_TS)
		led = em28xx_find_led(dev, EM28XX_LED_DIGITAL_CAPTURING);
	अन्यथा
		led = em28xx_find_led(dev, EM28XX_LED_DIGITAL_CAPTURING_TS2);

	अगर (led)
		em28xx_ग_लिखो_reg_bits(dev, led->gpio_reg,
				      (!start ^ led->inverted) ?
				      ~led->gpio_mask : led->gpio_mask,
				      led->gpio_mask);

	वापस rc;
पूर्ण

पूर्णांक em28xx_gpio_set(काष्ठा em28xx *dev, स्थिर काष्ठा em28xx_reg_seq *gpio)
अणु
	पूर्णांक rc = 0;

	अगर (!gpio)
		वापस rc;

	अगर (dev->mode != EM28XX_SUSPEND) अणु
		em28xx_ग_लिखो_reg(dev, 0x48, 0x00);
		अगर (dev->mode == EM28XX_ANALOG_MODE)
			em28xx_ग_लिखो_reg(dev, EM28XX_R12_VINENABLE, 0x67);
		अन्यथा
			em28xx_ग_लिखो_reg(dev, EM28XX_R12_VINENABLE, 0x37);
		usleep_range(10000, 11000);
	पूर्ण

	/* Send GPIO reset sequences specअगरied at board entry */
	जबतक (gpio->sleep >= 0) अणु
		अगर (gpio->reg >= 0) अणु
			rc = em28xx_ग_लिखो_reg_bits(dev,
						   gpio->reg,
						   gpio->val,
						   gpio->mask);
			अगर (rc < 0)
				वापस rc;
		पूर्ण
		अगर (gpio->sleep > 0)
			msleep(gpio->sleep);

		gpio++;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_gpio_set);

पूर्णांक em28xx_set_mode(काष्ठा em28xx *dev, क्रमागत em28xx_mode set_mode)
अणु
	अगर (dev->mode == set_mode)
		वापस 0;

	अगर (set_mode == EM28XX_SUSPEND) अणु
		dev->mode = set_mode;

		/* FIXME: add suspend support क्रम ac97 */

		वापस em28xx_gpio_set(dev, dev->board.suspend_gpio);
	पूर्ण

	dev->mode = set_mode;

	अगर (dev->mode == EM28XX_DIGITAL_MODE)
		वापस em28xx_gpio_set(dev, dev->board.dvb_gpio);
	अन्यथा
		वापस em28xx_gpio_set(dev, INPUT(dev->ctl_input)->gpio);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_set_mode);

/*
 *URB control
 */

/*
 * URB completion handler क्रम isoc/bulk transfers
 */
अटल व्योम em28xx_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा em28xx *dev = urb->context;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:            /* error */
		em28xx_isocdbg("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	/* Copy data from URB */
	spin_lock_irqsave(&dev->slock, flags);
	dev->usb_ctl.urb_data_copy(dev, urb);
	spin_unlock_irqrestore(&dev->slock, flags);

	/* Reset urb buffers */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		/* isoc only (bulk: number_of_packets = 0) */
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण
	urb->status = 0;

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status) अणु
		em28xx_isocdbg("urb resubmit failed (error=%i)\n",
			       urb->status);
	पूर्ण
पूर्ण

/*
 * Stop and Deallocate URBs
 */
व्योम em28xx_uninit_usb_xfer(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode)
अणु
	काष्ठा urb *urb;
	काष्ठा em28xx_usb_bufs *usb_bufs;
	पूर्णांक i;

	em28xx_isocdbg("called %s in mode %d\n", __func__, mode);

	अगर (mode == EM28XX_DIGITAL_MODE)
		usb_bufs = &dev->usb_ctl.digital_bufs;
	अन्यथा
		usb_bufs = &dev->usb_ctl.analog_bufs;

	क्रम (i = 0; i < usb_bufs->num_bufs; i++) अणु
		urb = usb_bufs->urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);

			usb_मुक्त_urb(urb);
			usb_bufs->urb[i] = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(usb_bufs->urb);
	kमुक्त(usb_bufs->buf);

	usb_bufs->urb = शून्य;
	usb_bufs->buf = शून्य;
	usb_bufs->num_bufs = 0;

	em28xx_capture_start(dev, 0);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_uninit_usb_xfer);

/*
 * Stop URBs
 */
व्योम em28xx_stop_urbs(काष्ठा em28xx *dev)
अणु
	पूर्णांक i;
	काष्ठा urb *urb;
	काष्ठा em28xx_usb_bufs *isoc_bufs = &dev->usb_ctl.digital_bufs;

	em28xx_isocdbg("called %s\n", __func__);

	क्रम (i = 0; i < isoc_bufs->num_bufs; i++) अणु
		urb = isoc_bufs->urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);
		पूर्ण
	पूर्ण

	em28xx_capture_start(dev, 0);
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_stop_urbs);

/*
 * Allocate URBs
 */
पूर्णांक em28xx_alloc_urbs(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode, पूर्णांक xfer_bulk,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size, पूर्णांक packet_multiplier)
अणु
	काष्ठा em28xx_usb_bufs *usb_bufs;
	काष्ठा urb *urb;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक i;
	पूर्णांक sb_size, pipe;
	पूर्णांक j, k;

	em28xx_isocdbg("em28xx: called %s in mode %d\n", __func__, mode);

	/*
	 * Check mode and अगर we have an endpoपूर्णांक क्रम the selected
	 * transfer type, select buffer
	 */
	अगर (mode == EM28XX_DIGITAL_MODE) अणु
		अगर ((xfer_bulk && !dev->dvb_ep_bulk) ||
		    (!xfer_bulk && !dev->dvb_ep_isoc)) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"no endpoint for DVB mode and transfer type %d\n",
				xfer_bulk > 0);
			वापस -EINVAL;
		पूर्ण
		usb_bufs = &dev->usb_ctl.digital_bufs;
	पूर्ण अन्यथा अगर (mode == EM28XX_ANALOG_MODE) अणु
		अगर ((xfer_bulk && !dev->analog_ep_bulk) ||
		    (!xfer_bulk && !dev->analog_ep_isoc)) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"no endpoint for analog mode and transfer type %d\n",
				xfer_bulk > 0);
			वापस -EINVAL;
		पूर्ण
		usb_bufs = &dev->usb_ctl.analog_bufs;
	पूर्ण अन्यथा अणु
		dev_err(&dev->पूर्णांकf->dev, "invalid mode selected\n");
		वापस -EINVAL;
	पूर्ण

	/* De-allocates all pending stuff */
	em28xx_uninit_usb_xfer(dev, mode);

	usb_bufs->num_bufs = num_bufs;

	usb_bufs->urb = kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!usb_bufs->urb)
		वापस -ENOMEM;

	usb_bufs->buf = kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!usb_bufs->buf) अणु
		kमुक्त(usb_bufs->urb);
		वापस -ENOMEM;
	पूर्ण

	usb_bufs->max_pkt_size = max_pkt_size;
	अगर (xfer_bulk)
		usb_bufs->num_packets = 0;
	अन्यथा
		usb_bufs->num_packets = packet_multiplier;
	dev->usb_ctl.vid_buf = शून्य;
	dev->usb_ctl.vbi_buf = शून्य;

	sb_size = packet_multiplier * usb_bufs->max_pkt_size;

	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < usb_bufs->num_bufs; i++) अणु
		urb = usb_alloc_urb(usb_bufs->num_packets, GFP_KERNEL);
		अगर (!urb) अणु
			em28xx_uninit_usb_xfer(dev, mode);
			वापस -ENOMEM;
		पूर्ण
		usb_bufs->urb[i] = urb;

		usb_bufs->buf[i] = kzalloc(sb_size, GFP_KERNEL);
		अगर (!usb_bufs->buf[i]) अणु
			क्रम (i--; i >= 0; i--)
				kमुक्त(usb_bufs->buf[i]);

			em28xx_uninit_usb_xfer(dev, mode);
			वापस -ENOMEM;
		पूर्ण

		urb->transfer_flags = URB_FREE_BUFFER;

		अगर (xfer_bulk) अणु /* bulk */
			pipe = usb_rcvbulkpipe(udev,
					       mode == EM28XX_ANALOG_MODE ?
					       dev->analog_ep_bulk :
					       dev->dvb_ep_bulk);
			usb_fill_bulk_urb(urb, udev, pipe, usb_bufs->buf[i],
					  sb_size, em28xx_irq_callback, dev);
		पूर्ण अन्यथा अणु /* isoc */
			pipe = usb_rcvisocpipe(udev,
					       mode == EM28XX_ANALOG_MODE ?
					       dev->analog_ep_isoc :
					       dev->dvb_ep_isoc);
			usb_fill_पूर्णांक_urb(urb, udev, pipe, usb_bufs->buf[i],
					 sb_size, em28xx_irq_callback, dev, 1);
			urb->transfer_flags |= URB_ISO_ASAP;
			k = 0;
			क्रम (j = 0; j < usb_bufs->num_packets; j++) अणु
				urb->iso_frame_desc[j].offset = k;
				urb->iso_frame_desc[j].length =
							usb_bufs->max_pkt_size;
				k += usb_bufs->max_pkt_size;
			पूर्ण
		पूर्ण

		urb->number_of_packets = usb_bufs->num_packets;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_alloc_urbs);

/*
 * Allocate URBs and start IRQ
 */
पूर्णांक em28xx_init_usb_xfer(काष्ठा em28xx *dev, क्रमागत em28xx_mode mode,
			 पूर्णांक xfer_bulk, पूर्णांक num_bufs, पूर्णांक max_pkt_size,
		    पूर्णांक packet_multiplier,
		    पूर्णांक (*urb_data_copy)(काष्ठा em28xx *dev, काष्ठा urb *urb))
अणु
	काष्ठा em28xx_dmaqueue *dma_q = &dev->vidq;
	काष्ठा em28xx_dmaqueue *vbi_dma_q = &dev->vbiq;
	काष्ठा em28xx_usb_bufs *usb_bufs;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक i;
	पूर्णांक rc;
	पूर्णांक alloc;

	em28xx_isocdbg("em28xx: called %s in mode %d\n", __func__, mode);

	dev->usb_ctl.urb_data_copy = urb_data_copy;

	अगर (mode == EM28XX_DIGITAL_MODE) अणु
		usb_bufs = &dev->usb_ctl.digital_bufs;
		/* no need to मुक्त/alloc usb buffers in digital mode */
		alloc = 0;
	पूर्ण अन्यथा अणु
		usb_bufs = &dev->usb_ctl.analog_bufs;
		alloc = 1;
	पूर्ण

	अगर (alloc) अणु
		rc = em28xx_alloc_urbs(dev, mode, xfer_bulk, num_bufs,
				       max_pkt_size, packet_multiplier);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (xfer_bulk) अणु
		rc = usb_clear_halt(udev, usb_bufs->urb[0]->pipe);
		अगर (rc < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"failed to clear USB bulk endpoint stall/halt condition (error=%i)\n",
			       rc);
			em28xx_uninit_usb_xfer(dev, mode);
			वापस rc;
		पूर्ण
	पूर्ण

	init_रुकोqueue_head(&dma_q->wq);
	init_रुकोqueue_head(&vbi_dma_q->wq);

	em28xx_capture_start(dev, 1);

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < usb_bufs->num_bufs; i++) अणु
		rc = usb_submit_urb(usb_bufs->urb[i], GFP_KERNEL);
		अगर (rc) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"submit of urb %i failed (error=%i)\n", i, rc);
			em28xx_uninit_usb_xfer(dev, mode);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(em28xx_init_usb_xfer);

/*
 * Device control list
 */

अटल LIST_HEAD(em28xx_devlist);
अटल DEFINE_MUTEX(em28xx_devlist_mutex);

/*
 * Extension पूर्णांकerface
 */

अटल LIST_HEAD(em28xx_extension_devlist);

पूर्णांक em28xx_रेजिस्टर_extension(काष्ठा em28xx_ops *ops)
अणु
	काष्ठा em28xx *dev = शून्य;

	mutex_lock(&em28xx_devlist_mutex);
	list_add_tail(&ops->next, &em28xx_extension_devlist);
	list_क्रम_each_entry(dev, &em28xx_devlist, devlist) अणु
		अगर (ops->init) अणु
			ops->init(dev);
			अगर (dev->dev_next)
				ops->init(dev->dev_next);
		पूर्ण
	पूर्ण
	mutex_unlock(&em28xx_devlist_mutex);
	pr_info("em28xx: Registered (%s) extension\n", ops->name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(em28xx_रेजिस्टर_extension);

व्योम em28xx_unरेजिस्टर_extension(काष्ठा em28xx_ops *ops)
अणु
	काष्ठा em28xx *dev = शून्य;

	mutex_lock(&em28xx_devlist_mutex);
	list_क्रम_each_entry(dev, &em28xx_devlist, devlist) अणु
		अगर (ops->fini) अणु
			अगर (dev->dev_next)
				ops->fini(dev->dev_next);
			ops->fini(dev);
		पूर्ण
	पूर्ण
	list_del(&ops->next);
	mutex_unlock(&em28xx_devlist_mutex);
	pr_info("em28xx: Removed (%s) extension\n", ops->name);
पूर्ण
EXPORT_SYMBOL(em28xx_unरेजिस्टर_extension);

व्योम em28xx_init_extension(काष्ठा em28xx *dev)
अणु
	स्थिर काष्ठा em28xx_ops *ops = शून्य;

	mutex_lock(&em28xx_devlist_mutex);
	list_add_tail(&dev->devlist, &em28xx_devlist);
	list_क्रम_each_entry(ops, &em28xx_extension_devlist, next) अणु
		अगर (ops->init) अणु
			ops->init(dev);
			अगर (dev->dev_next)
				ops->init(dev->dev_next);
		पूर्ण
	पूर्ण
	mutex_unlock(&em28xx_devlist_mutex);
पूर्ण

व्योम em28xx_बंद_extension(काष्ठा em28xx *dev)
अणु
	स्थिर काष्ठा em28xx_ops *ops = शून्य;

	mutex_lock(&em28xx_devlist_mutex);
	list_क्रम_each_entry(ops, &em28xx_extension_devlist, next) अणु
		अगर (ops->fini) अणु
			अगर (dev->dev_next)
				ops->fini(dev->dev_next);
			ops->fini(dev);
		पूर्ण
	पूर्ण
	list_del(&dev->devlist);
	mutex_unlock(&em28xx_devlist_mutex);
पूर्ण

पूर्णांक em28xx_suspend_extension(काष्ठा em28xx *dev)
अणु
	स्थिर काष्ठा em28xx_ops *ops = शून्य;

	dev_info(&dev->पूर्णांकf->dev, "Suspending extensions\n");
	mutex_lock(&em28xx_devlist_mutex);
	list_क्रम_each_entry(ops, &em28xx_extension_devlist, next) अणु
		अगर (ops->suspend)
			ops->suspend(dev);
		अगर (dev->dev_next)
			ops->suspend(dev->dev_next);
	पूर्ण
	mutex_unlock(&em28xx_devlist_mutex);
	वापस 0;
पूर्ण

पूर्णांक em28xx_resume_extension(काष्ठा em28xx *dev)
अणु
	स्थिर काष्ठा em28xx_ops *ops = शून्य;

	dev_info(&dev->पूर्णांकf->dev, "Resuming extensions\n");
	mutex_lock(&em28xx_devlist_mutex);
	list_क्रम_each_entry(ops, &em28xx_extension_devlist, next) अणु
		अगर (!ops->resume)
			जारी;
		ops->resume(dev);
		अगर (dev->dev_next)
			ops->resume(dev->dev_next);
	पूर्ण
	mutex_unlock(&em28xx_devlist_mutex);
	वापस 0;
पूर्ण
