<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// पंचांग6000-core.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
//
// Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Copyright (c) 2007 Michel Ludwig <michel.ludwig@gmail.com>
//     - DVB-T support

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>

#घोषणा USB_TIMEOUT	(5 * HZ) /* ms */

पूर्णांक पंचांग6000_पढ़ो_ग_लिखो_usb(काष्ठा पंचांग6000_core *dev, u8 req_type, u8 req,
			  u16 value, u16 index, u8 *buf, u16 len)
अणु
	पूर्णांक          ret, i;
	अचिन्हित पूर्णांक pipe;
	u8	     *data = शून्य;
	पूर्णांक delay = 5000;

	अगर (len) अणु
		data = kzalloc(len, GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
	पूर्ण

	mutex_lock(&dev->usb_lock);

	अगर (req_type & USB_सूची_IN)
		pipe = usb_rcvctrlpipe(dev->udev, 0);
	अन्यथा अणु
		pipe = usb_sndctrlpipe(dev->udev, 0);
		स_नकल(data, buf, len);
	पूर्ण

	अगर (पंचांग6000_debug & V4L2_DEBUG_I2C) अणु
		prपूर्णांकk(KERN_DEBUG "(dev %p, pipe %08x): ", dev->udev, pipe);

		prपूर्णांकk(KERN_CONT "%s: %02x %02x %02x %02x %02x %02x %02x %02x ",
			(req_type & USB_सूची_IN) ? " IN" : "OUT",
			req_type, req, value&0xff, value>>8, index&0xff,
			index>>8, len&0xff, len>>8);

		अगर (!(req_type & USB_सूची_IN)) अणु
			prपूर्णांकk(KERN_CONT ">>> ");
			क्रम (i = 0; i < len; i++)
				prपूर्णांकk(KERN_CONT " %02x", buf[i]);
			prपूर्णांकk(KERN_CONT "\n");
		पूर्ण
	पूर्ण

	ret = usb_control_msg(dev->udev, pipe, req, req_type, value, index,
			      data, len, USB_TIMEOUT);

	अगर (req_type &  USB_सूची_IN)
		स_नकल(buf, data, len);

	अगर (पंचांग6000_debug & V4L2_DEBUG_I2C) अणु
		अगर (ret < 0) अणु
			अगर (req_type &  USB_सूची_IN)
				prपूर्णांकk(KERN_DEBUG "<<< (len=%d)\n", len);

			prपूर्णांकk(KERN_CONT "%s: Error #%d\n", __func__, ret);
		पूर्ण अन्यथा अगर (req_type &  USB_सूची_IN) अणु
			prपूर्णांकk(KERN_CONT "<<< ");
			क्रम (i = 0; i < len; i++)
				prपूर्णांकk(KERN_CONT " %02x", buf[i]);
			prपूर्णांकk(KERN_CONT "\n");
		पूर्ण
	पूर्ण

	kमुक्त(data);

	अगर (dev->quirks & TM6000_QUIRK_NO_USB_DELAY)
		delay = 0;

	अगर (req == REQ_16_SET_GET_I2C_WR1_RDN && !(req_type & USB_सूची_IN)) अणु
		अचिन्हित पूर्णांक tsleep;
		/* Calculate delay समय, 14000us क्रम 64 bytes */
		tsleep = (len * 200) + 200;
		अगर (tsleep < delay)
			tsleep = delay;
		usleep_range(tsleep, tsleep + 1000);
	पूर्ण
	अन्यथा अगर (delay)
		usleep_range(delay, delay + 1000);

	mutex_unlock(&dev->usb_lock);
	वापस ret;
पूर्ण

पूर्णांक पंचांग6000_set_reg(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index)
अणु
	वापस
		पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_OUT | USB_TYPE_VENDOR,
				      req, value, index, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_set_reg);

पूर्णांक पंचांग6000_get_reg(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index)
अणु
	पूर्णांक rc;
	u8 buf[1];

	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR, req,
					value, index, buf, 1);

	अगर (rc < 0)
		वापस rc;

	वापस *buf;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_get_reg);

पूर्णांक पंचांग6000_set_reg_mask(काष्ठा पंचांग6000_core *dev, u8 req, u16 value,
						u16 index, u16 mask)
अणु
	पूर्णांक rc;
	u8 buf[1];
	u8 new_index;

	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR, req,
					value, 0, buf, 1);

	अगर (rc < 0)
		वापस rc;

	new_index = (buf[0] & ~mask) | (index & mask);

	अगर (new_index == buf[0])
		वापस 0;

	वापस पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_OUT | USB_TYPE_VENDOR,
				      req, value, new_index, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_set_reg_mask);

पूर्णांक पंचांग6000_get_reg16(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index)
अणु
	पूर्णांक rc;
	u8 buf[2];

	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR, req,
					value, index, buf, 2);

	अगर (rc < 0)
		वापस rc;

	वापस buf[1]|buf[0]<<8;
पूर्ण

पूर्णांक पंचांग6000_get_reg32(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index)
अणु
	पूर्णांक rc;
	u8 buf[4];

	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR, req,
					value, index, buf, 4);

	अगर (rc < 0)
		वापस rc;

	वापस buf[3] | buf[2] << 8 | buf[1] << 16 | buf[0] << 24;
पूर्ण

पूर्णांक पंचांग6000_i2c_reset(काष्ठा पंचांग6000_core *dev, u16 tsleep)
अणु
	पूर्णांक rc;

	rc = पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, TM6000_GPIO_CLK, 0);
	अगर (rc < 0)
		वापस rc;

	msleep(tsleep);

	rc = पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN, TM6000_GPIO_CLK, 1);
	msleep(tsleep);

	वापस rc;
पूर्ण

व्योम पंचांग6000_set_fourcc_क्रमmat(काष्ठा पंचांग6000_core *dev)
अणु
	अगर (dev->dev_type == TM6010) अणु
		पूर्णांक val;

		val = पंचांग6000_get_reg(dev, TM6010_REQ07_RCC_ACTIVE_IF, 0) & 0xfc;
		अगर (dev->fourcc == V4L2_PIX_FMT_UYVY)
			पंचांग6000_set_reg(dev, TM6010_REQ07_RCC_ACTIVE_IF, val);
		अन्यथा
			पंचांग6000_set_reg(dev, TM6010_REQ07_RCC_ACTIVE_IF, val | 1);
	पूर्ण अन्यथा अणु
		अगर (dev->fourcc == V4L2_PIX_FMT_UYVY)
			पंचांग6000_set_reg(dev, TM6010_REQ07_RC1_TRESHOLD, 0xd0);
		अन्यथा
			पंचांग6000_set_reg(dev, TM6010_REQ07_RC1_TRESHOLD, 0x90);
	पूर्ण
पूर्ण

अटल व्योम पंचांग6000_set_vbi(काष्ठा पंचांग6000_core *dev)
अणु
	/*
	 * FIXME:
	 * VBI lines and start/end are dअगरferent between 60Hz and 50Hz
	 * So, it is very likely that we need to change the config to
	 * something that takes it पूर्णांकo account, करोing something dअगरferent
	 * अगर (dev->norm & V4L2_STD_525_60)
	 */

	अगर (dev->dev_type == TM6010) अणु
		पंचांग6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x01);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R41_TELETEXT_VBI_CODE1, 0x27);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R42_VBI_DATA_HIGH_LEVEL, 0x55);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R43_VBI_DATA_TYPE_LINE7, 0x66);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R44_VBI_DATA_TYPE_LINE8, 0x66);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R45_VBI_DATA_TYPE_LINE9, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R46_VBI_DATA_TYPE_LINE10, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R47_VBI_DATA_TYPE_LINE11, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R48_VBI_DATA_TYPE_LINE12, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R49_VBI_DATA_TYPE_LINE13, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4A_VBI_DATA_TYPE_LINE14, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4B_VBI_DATA_TYPE_LINE15, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4C_VBI_DATA_TYPE_LINE16, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4D_VBI_DATA_TYPE_LINE17, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4E_VBI_DATA_TYPE_LINE18, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R4F_VBI_DATA_TYPE_LINE19, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R50_VBI_DATA_TYPE_LINE20, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R51_VBI_DATA_TYPE_LINE21, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R52_VBI_DATA_TYPE_LINE22, 0x66);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R53_VBI_DATA_TYPE_LINE23, 0x00);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R54_VBI_DATA_TYPE_RLINES, 0x00);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R55_VBI_LOOP_FILTER_GAIN, 0x01);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R56_VBI_LOOP_FILTER_I_GAIN, 0x00);
		पंचांग6000_set_reg(dev,
			TM6010_REQ07_R57_VBI_LOOP_FILTER_P_GAIN, 0x02);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R58_VBI_CAPTION_DTO1, 0x35);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R59_VBI_CAPTION_DTO0, 0xa0);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R5A_VBI_TELETEXT_DTO1, 0x11);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R5B_VBI_TELETEXT_DTO0, 0x4c);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R40_TELETEXT_VBI_CODE0, 0x01);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x00);
	पूर्ण
पूर्ण

पूर्णांक पंचांग6000_init_analog_mode(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा v4l2_frequency f;

	अगर (dev->dev_type == TM6010) अणु
		u8 active = TM6010_REQ07_RCC_ACTIVE_IF_AUDIO_ENABLE;

		अगर (!dev->radio)
			active |= TM6010_REQ07_RCC_ACTIVE_IF_VIDEO_ENABLE;

		/* Enable video and audio */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ07_RCC_ACTIVE_IF,
							active, 0x60);
		/* Disable TS input */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE,
							0x00, 0x40);
	पूर्ण अन्यथा अणु
		/* Enables soft reset */
		पंचांग6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x01);

		अगर (dev->scaler)
			/* Disable Hfilter and Enable TS Drop err */
			पंचांग6000_set_reg(dev, TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE, 0x20);
		अन्यथा	/* Enable Hfilter and disable TS Drop err */
			पंचांग6000_set_reg(dev, TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE, 0x80);

		पंचांग6000_set_reg(dev, TM6010_REQ07_RC3_HSTART1, 0x88);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RDA_CLK_SEL, 0x23);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD1_ADDR_FOR_REQ1, 0xc0);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD2_ADDR_FOR_REQ2, 0xd8);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD6_ENDP_REQ1_REQ2, 0x06);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RDF_PWDOWN_ACLK, 0x1f);

		/* AP Software reset */
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFF_SOFT_RESET, 0x08);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFF_SOFT_RESET, 0x00);

		पंचांग6000_set_fourcc_क्रमmat(dev);

		/* Disables soft reset */
		पंचांग6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x00);
	पूर्ण
	msleep(20);

	/* Tuner firmware can now be loaded */

	/*
	 * FIXME: This is a hack! xc3028 "sleeps" when no channel is detected
	 * क्रम more than a few seconds. Not sure why, as this behavior करोes
	 * not happen on other devices with xc3028. So, I suspect that it
	 * is yet another bug at पंचांग6000. After start sleeping, decoding
	 * करोesn't start स्वतःmatically. Instead, it requires some
	 * I2C commands to wake it up. As we want to have image at the
	 * beginning, we needed to add this hack. The better would be to
	 * discover some way to make पंचांग6000 to wake up without this hack.
	 */
	f.frequency = dev->freq;
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, &f);

	msleep(100);
	पंचांग6000_set_standard(dev);
	पंचांग6000_set_vbi(dev);
	पंचांग6000_set_audio_bitrate(dev, 48000);

	/* चयन dvb led off */
	अगर (dev->gpio.dvb_led) अणु
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			dev->gpio.dvb_led, 0x01);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पंचांग6000_init_digital_mode(काष्ठा पंचांग6000_core *dev)
अणु
	अगर (dev->dev_type == TM6010) अणु
		/* Disable video and audio */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ07_RCC_ACTIVE_IF,
				0x00, 0x60);
		/* Enable TS input */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE,
				0x40, 0x40);
		/* all घातer करोwn, but not the digital data port */
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFE_POWER_DOWN, 0x28);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RE2_POWER_DOWN_CTRL1, 0xfc);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RE6_POWER_DOWN_CTRL2, 0xff);
	पूर्ण अन्यथा  अणु
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFF_SOFT_RESET, 0x08);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RFF_SOFT_RESET, 0x00);
		पंचांग6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x01);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RDF_PWDOWN_ACLK, 0x08);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RE2_VADC_STATUS_CTL, 0x0c);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0xff);
		पंचांग6000_set_reg(dev, TM6000_REQ07_REB_VADC_AADC_MODE, 0xd8);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE, 0x40);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RC1_TRESHOLD, 0xd0);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RC3_HSTART1, 0x09);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RDA_CLK_SEL, 0x37);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD1_ADDR_FOR_REQ1, 0xd8);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD2_ADDR_FOR_REQ2, 0xc0);
		पंचांग6000_set_reg(dev, TM6010_REQ07_RD6_ENDP_REQ1_REQ2, 0x60);

		पंचांग6000_set_reg(dev, TM6000_REQ07_RE2_VADC_STATUS_CTL, 0x0c);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0xff);
		पंचांग6000_set_reg(dev, TM6000_REQ07_REB_VADC_AADC_MODE, 0x08);
		msleep(50);

		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 0x0020, 0x00);
		msleep(50);
		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 0x0020, 0x01);
		msleep(50);
		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 0x0020, 0x00);
		msleep(100);
	पूर्ण

	/* चयन dvb led on */
	अगर (dev->gpio.dvb_led) अणु
		पंचांग6000_set_reg(dev, REQ_03_SET_GET_MCU_PIN,
			dev->gpio.dvb_led, 0x00);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(पंचांग6000_init_digital_mode);

काष्ठा reg_init अणु
	u8 req;
	u8 reg;
	u8 val;
पूर्ण;

/* The meaning of those initializations are unknown */
अटल काष्ठा reg_init पंचांग6000_init_tab[] = अणु
	/* REG  VALUE */
	अणु TM6000_REQ07_RDF_PWDOWN_ACLK, 0x1f पूर्ण,
	अणु TM6010_REQ07_RFF_SOFT_RESET, 0x08 पूर्ण,
	अणु TM6010_REQ07_RFF_SOFT_RESET, 0x00 पूर्ण,
	अणु TM6010_REQ07_RD5_POWERSAVE, 0x4f पूर्ण,
	अणु TM6000_REQ07_RDA_CLK_SEL, 0x23 पूर्ण,
	अणु TM6000_REQ07_RDB_OUT_SEL, 0x08 पूर्ण,
	अणु TM6000_REQ07_RE2_VADC_STATUS_CTL, 0x00 पूर्ण,
	अणु TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x10 पूर्ण,
	अणु TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x00 पूर्ण,
	अणु TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x00 पूर्ण,
	अणु TM6000_REQ07_REB_VADC_AADC_MODE, 0x64 पूर्ण,	/* 48000 bits/sample, बाह्यal input */
	अणु TM6000_REQ07_REE_VADC_CTRL_SEL_CONTROL, 0xc2 पूर्ण,

	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,		/* Start of soft reset */
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x00 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x07 पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x00 पूर्ण,
	अणु TM6010_REQ07_R05_NOISE_THRESHOLD, 0x64 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x01 पूर्ण,
	अणु TM6010_REQ07_R08_LUMA_CONTRAST_ADJ, 0x82 पूर्ण,
	अणु TM6010_REQ07_R09_LUMA_BRIGHTNESS_ADJ, 0x36 पूर्ण,
	अणु TM6010_REQ07_R0A_CHROMA_SATURATION_ADJ, 0x50 पूर्ण,
	अणु TM6010_REQ07_R0C_CHROMA_AGC_CONTROL, 0x6a पूर्ण,
	अणु TM6010_REQ07_R11_AGC_PEAK_CONTROL, 0xc9 पूर्ण,
	अणु TM6010_REQ07_R12_AGC_GATE_STARTH, 0x07 पूर्ण,
	अणु TM6010_REQ07_R13_AGC_GATE_STARTL, 0x3b पूर्ण,
	अणु TM6010_REQ07_R14_AGC_GATE_WIDTH, 0x47 पूर्ण,
	अणु TM6010_REQ07_R15_AGC_BP_DELAY, 0x6f पूर्ण,
	अणु TM6010_REQ07_R17_HLOOP_MAXSTATE, 0xcd पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x8b पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xa2 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe9 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R20_HSYNC_RISING_EDGE_TIME, 0x3c पूर्ण,
	अणु TM6010_REQ07_R21_HSYNC_PHASE_OFFSET, 0x3c पूर्ण,
	अणु TM6010_REQ07_R2D_CHROMA_BURST_END, 0x48 पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R32_VSYNC_HLOCK_MIN, 0x74 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R34_VSYNC_AGC_MIN, 0x74 पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R36_VSYNC_VBI_MIN, 0x7a पूर्ण,
	अणु TM6010_REQ07_R37_VSYNC_VBI_MAX, 0x26 पूर्ण,
	अणु TM6010_REQ07_R38_VSYNC_THRESHOLD, 0x40 पूर्ण,
	अणु TM6010_REQ07_R39_VSYNC_TIME_CONSTANT, 0x0a पूर्ण,
	अणु TM6010_REQ07_R42_VBI_DATA_HIGH_LEVEL, 0x55 पूर्ण,
	अणु TM6010_REQ07_R51_VBI_DATA_TYPE_LINE21, 0x11 पूर्ण,
	अणु TM6010_REQ07_R55_VBI_LOOP_FILTER_GAIN, 0x01 पूर्ण,
	अणु TM6010_REQ07_R57_VBI_LOOP_FILTER_P_GAIN, 0x02 पूर्ण,
	अणु TM6010_REQ07_R58_VBI_CAPTION_DTO1, 0x35 पूर्ण,
	अणु TM6010_REQ07_R59_VBI_CAPTION_DTO0, 0xa0 पूर्ण,
	अणु TM6010_REQ07_R80_COMB_FILTER_TRESHOLD, 0x15 पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_RC1_TRESHOLD, 0xd0 पूर्ण,
	अणु TM6010_REQ07_RC3_HSTART1, 0x88 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,		/* End of the soft reset */
	अणु TM6010_REQ05_R18_IMASK7, 0x00 पूर्ण,
पूर्ण;

अटल काष्ठा reg_init पंचांग6010_init_tab[] = अणु
	अणु TM6010_REQ07_RC0_ACTIVE_VIDEO_SOURCE, 0x00 पूर्ण,
	अणु TM6010_REQ07_RC4_HSTART0, 0xa0 पूर्ण,
	अणु TM6010_REQ07_RC6_HEND0, 0x40 पूर्ण,
	अणु TM6010_REQ07_RCA_VEND0, 0x31 पूर्ण,
	अणु TM6010_REQ07_RCC_ACTIVE_IF, 0xe1 पूर्ण,
	अणु TM6010_REQ07_RE0_DVIDEO_SOURCE, 0x03 पूर्ण,
	अणु TM6010_REQ07_RFE_POWER_DOWN, 0x7f पूर्ण,

	अणु TM6010_REQ08_RE2_POWER_DOWN_CTRL1, 0xf0 पूर्ण,
	अणु TM6010_REQ08_RE3_ADC_IN1_SEL, 0xf4 पूर्ण,
	अणु TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf8 पूर्ण,
	अणु TM6010_REQ08_RE6_POWER_DOWN_CTRL2, 0x00 पूर्ण,
	अणु TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf2 पूर्ण,
	अणु TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xf0 पूर्ण,
	अणु TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2 पूर्ण,
	अणु TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG, 0x60 पूर्ण,
	अणु TM6010_REQ08_RF1_AADC_POWER_DOWN, 0xfc पूर्ण,

	अणु TM6010_REQ07_R3F_RESET, 0x01 पूर्ण,
	अणु TM6010_REQ07_R00_VIDEO_CONTROL0, 0x00 पूर्ण,
	अणु TM6010_REQ07_R01_VIDEO_CONTROL1, 0x07 पूर्ण,
	अणु TM6010_REQ07_R02_VIDEO_CONTROL2, 0x5f पूर्ण,
	अणु TM6010_REQ07_R03_YC_SEP_CONTROL, 0x00 पूर्ण,
	अणु TM6010_REQ07_R05_NOISE_THRESHOLD, 0x64 पूर्ण,
	अणु TM6010_REQ07_R07_OUTPUT_CONTROL, 0x01 पूर्ण,
	अणु TM6010_REQ07_R08_LUMA_CONTRAST_ADJ, 0x82 पूर्ण,
	अणु TM6010_REQ07_R09_LUMA_BRIGHTNESS_ADJ, 0x36 पूर्ण,
	अणु TM6010_REQ07_R0A_CHROMA_SATURATION_ADJ, 0x50 पूर्ण,
	अणु TM6010_REQ07_R0C_CHROMA_AGC_CONTROL, 0x6a पूर्ण,
	अणु TM6010_REQ07_R11_AGC_PEAK_CONTROL, 0xc9 पूर्ण,
	अणु TM6010_REQ07_R12_AGC_GATE_STARTH, 0x07 पूर्ण,
	अणु TM6010_REQ07_R13_AGC_GATE_STARTL, 0x3b पूर्ण,
	अणु TM6010_REQ07_R14_AGC_GATE_WIDTH, 0x47 पूर्ण,
	अणु TM6010_REQ07_R15_AGC_BP_DELAY, 0x6f पूर्ण,
	अणु TM6010_REQ07_R17_HLOOP_MAXSTATE, 0xcd पूर्ण,
	अणु TM6010_REQ07_R18_CHROMA_DTO_INCREMENT3, 0x1e पूर्ण,
	अणु TM6010_REQ07_R19_CHROMA_DTO_INCREMENT2, 0x8b पूर्ण,
	अणु TM6010_REQ07_R1A_CHROMA_DTO_INCREMENT1, 0xa2 पूर्ण,
	अणु TM6010_REQ07_R1B_CHROMA_DTO_INCREMENT0, 0xe9 पूर्ण,
	अणु TM6010_REQ07_R1C_HSYNC_DTO_INCREMENT3, 0x1c पूर्ण,
	अणु TM6010_REQ07_R1D_HSYNC_DTO_INCREMENT2, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1E_HSYNC_DTO_INCREMENT1, 0xcc पूर्ण,
	अणु TM6010_REQ07_R1F_HSYNC_DTO_INCREMENT0, 0xcd पूर्ण,
	अणु TM6010_REQ07_R20_HSYNC_RISING_EDGE_TIME, 0x3c पूर्ण,
	अणु TM6010_REQ07_R21_HSYNC_PHASE_OFFSET, 0x3c पूर्ण,
	अणु TM6010_REQ07_R2D_CHROMA_BURST_END, 0x48 पूर्ण,
	अणु TM6010_REQ07_R2E_ACTIVE_VIDEO_HSTART, 0x88 पूर्ण,
	अणु TM6010_REQ07_R30_ACTIVE_VIDEO_VSTART, 0x22 पूर्ण,
	अणु TM6010_REQ07_R31_ACTIVE_VIDEO_VHIGHT, 0x61 पूर्ण,
	अणु TM6010_REQ07_R32_VSYNC_HLOCK_MIN, 0x74 पूर्ण,
	अणु TM6010_REQ07_R33_VSYNC_HLOCK_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R34_VSYNC_AGC_MIN, 0x74 पूर्ण,
	अणु TM6010_REQ07_R35_VSYNC_AGC_MAX, 0x1c पूर्ण,
	अणु TM6010_REQ07_R36_VSYNC_VBI_MIN, 0x7a पूर्ण,
	अणु TM6010_REQ07_R37_VSYNC_VBI_MAX, 0x26 पूर्ण,
	अणु TM6010_REQ07_R38_VSYNC_THRESHOLD, 0x40 पूर्ण,
	अणु TM6010_REQ07_R39_VSYNC_TIME_CONSTANT, 0x0a पूर्ण,
	अणु TM6010_REQ07_R42_VBI_DATA_HIGH_LEVEL, 0x55 पूर्ण,
	अणु TM6010_REQ07_R51_VBI_DATA_TYPE_LINE21, 0x11 पूर्ण,
	अणु TM6010_REQ07_R55_VBI_LOOP_FILTER_GAIN, 0x01 पूर्ण,
	अणु TM6010_REQ07_R57_VBI_LOOP_FILTER_P_GAIN, 0x02 पूर्ण,
	अणु TM6010_REQ07_R58_VBI_CAPTION_DTO1, 0x35 पूर्ण,
	अणु TM6010_REQ07_R59_VBI_CAPTION_DTO0, 0xa0 पूर्ण,
	अणु TM6010_REQ07_R80_COMB_FILTER_TRESHOLD, 0x15 पूर्ण,
	अणु TM6010_REQ07_R82_COMB_FILTER_CONFIG, 0x42 पूर्ण,
	अणु TM6010_REQ07_RC1_TRESHOLD, 0xd0 पूर्ण,
	अणु TM6010_REQ07_RC3_HSTART1, 0x88 पूर्ण,
	अणु TM6010_REQ07_R3F_RESET, 0x00 पूर्ण,

	अणु TM6010_REQ05_R18_IMASK7, 0x00 पूर्ण,

	अणु TM6010_REQ07_RDC_IR_LEADER1, 0xaa पूर्ण,
	अणु TM6010_REQ07_RDD_IR_LEADER0, 0x30 पूर्ण,
	अणु TM6010_REQ07_RDE_IR_PULSE_CNT1, 0x20 पूर्ण,
	अणु TM6010_REQ07_RDF_IR_PULSE_CNT0, 0xd0 पूर्ण,
	अणु REQ_04_EN_DISABLE_MCU_INT, 0x02, 0x00 पूर्ण,
	अणु TM6010_REQ07_RD8_IR, 0x0f पूर्ण,

	/* set remote wakeup key:any key wakeup */
	अणु TM6010_REQ07_RE5_REMOTE_WAKEUP,  0xfe पूर्ण,
	अणु TM6010_REQ07_RDA_IR_WAKEUP_SEL,  0xff पूर्ण,
पूर्ण;

पूर्णांक पंचांग6000_init(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक board, rc = 0, i, size;
	काष्ठा reg_init *tab;

	/* Check board revision */
	board = पंचांग6000_get_reg32(dev, REQ_40_GET_VERSION, 0, 0);
	अगर (board >= 0) अणु
		चयन (board & 0xff) अणु
		हाल 0xf3:
			prपूर्णांकk(KERN_INFO "Found tm6000\n");
			अगर (dev->dev_type != TM6000)
				dev->dev_type = TM6000;
			अवरोध;
		हाल 0xf4:
			prपूर्णांकk(KERN_INFO "Found tm6010\n");
			अगर (dev->dev_type != TM6010)
				dev->dev_type = TM6010;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "Unknown board version = 0x%08x\n", board);
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "Error %i while retrieving board version\n", board);

	अगर (dev->dev_type == TM6010) अणु
		tab = पंचांग6010_init_tab;
		size = ARRAY_SIZE(पंचांग6010_init_tab);
	पूर्ण अन्यथा अणु
		tab = पंचांग6000_init_tab;
		size = ARRAY_SIZE(पंचांग6000_init_tab);
	पूर्ण

	/* Load board's initialization table */
	क्रम (i = 0; i < size; i++) अणु
		rc = पंचांग6000_set_reg(dev, tab[i].req, tab[i].reg, tab[i].val);
		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_ERR "Error %i while setting req %d, reg %d to value %d\n",
			       rc,
					tab[i].req, tab[i].reg, tab[i].val);
			वापस rc;
		पूर्ण
	पूर्ण

	msleep(5); /* Just to be conservative */

	rc = पंचांग6000_cards_setup(dev);

	वापस rc;
पूर्ण


पूर्णांक पंचांग6000_set_audio_bitrate(काष्ठा पंचांग6000_core *dev, पूर्णांक bitrate)
अणु
	पूर्णांक val = 0;
	u8 areg_f0 = 0x60; /* ADC MCLK = 250 Fs */
	u8 areg_0a = 0x91; /* SIF 48KHz */

	चयन (bitrate) अणु
	हाल 48000:
		areg_f0 = 0x60; /* ADC MCLK = 250 Fs */
		areg_0a = 0x91; /* SIF 48KHz */
		dev->audio_bitrate = bitrate;
		अवरोध;
	हाल 32000:
		areg_f0 = 0x00; /* ADC MCLK = 375 Fs */
		areg_0a = 0x90; /* SIF 32KHz */
		dev->audio_bitrate = bitrate;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	/* enable I2S, अगर we use sअगर or बाह्यal I2S device */
	अगर (dev->dev_type == TM6010) अणु
		val = पंचांग6000_set_reg(dev, TM6010_REQ08_R0A_A_I2S_MOD, areg_0a);
		अगर (val < 0)
			वापस val;

		val = पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
							areg_f0, 0xf0);
		अगर (val < 0)
			वापस val;
	पूर्ण अन्यथा अणु
		val = पंचांग6000_set_reg_mask(dev, TM6000_REQ07_REB_VADC_AADC_MODE,
							areg_f0, 0xf0);
		अगर (val < 0)
			वापस val;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांग6000_set_audio_bitrate);

पूर्णांक पंचांग6000_set_audio_rinput(काष्ठा पंचांग6000_core *dev)
अणु
	अगर (dev->dev_type == TM6010) अणु
		/* Audio crossbar setting, शेष SIF1 */
		u8 areg_f0;
		u8 areg_07 = 0x10;

		चयन (dev->rinput.amux) अणु
		हाल TM6000_AMUX_SIF1:
		हाल TM6000_AMUX_SIF2:
			areg_f0 = 0x03;
			areg_07 = 0x30;
			अवरोध;
		हाल TM6000_AMUX_ADC1:
			areg_f0 = 0x00;
			अवरोध;
		हाल TM6000_AMUX_ADC2:
			areg_f0 = 0x08;
			अवरोध;
		हाल TM6000_AMUX_I2S:
			areg_f0 = 0x04;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "%s: audio input doesn't support\n",
				dev->name);
			वापस 0;
			अवरोध;
		पूर्ण
		/* Set audio input crossbar */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
							areg_f0, 0x0f);
		/* Mux overflow workaround */
		पंचांग6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
			areg_07, 0xf0);
	पूर्ण अन्यथा अणु
		u8 areg_eb;
		/* Audio setting, शेष LINE1 */
		चयन (dev->rinput.amux) अणु
		हाल TM6000_AMUX_ADC1:
			areg_eb = 0x00;
			अवरोध;
		हाल TM6000_AMUX_ADC2:
			areg_eb = 0x04;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "%s: audio input doesn't support\n",
				dev->name);
			वापस 0;
			अवरोध;
		पूर्ण
		/* Set audio input */
		पंचांग6000_set_reg_mask(dev, TM6000_REQ07_REB_VADC_AADC_MODE,
							areg_eb, 0x0f);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पंचांग6010_set_mute_sअगर(काष्ठा पंचांग6000_core *dev, u8 mute)
अणु
	u8 mute_reg = 0;

	अगर (mute)
		mute_reg = 0x08;

	पंचांग6000_set_reg_mask(dev, TM6010_REQ08_R0A_A_I2S_MOD, mute_reg, 0x08);
पूर्ण

अटल व्योम पंचांग6010_set_mute_adc(काष्ठा पंचांग6000_core *dev, u8 mute)
अणु
	u8 mute_reg = 0;

	अगर (mute)
		mute_reg = 0x20;

	अगर (dev->dev_type == TM6010) अणु
		पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF2_LEFT_CHANNEL_VOL,
							mute_reg, 0x20);
		पंचांग6000_set_reg_mask(dev, TM6010_REQ08_RF3_RIGHT_CHANNEL_VOL,
							mute_reg, 0x20);
	पूर्ण अन्यथा अणु
		पंचांग6000_set_reg_mask(dev, TM6000_REQ07_REC_VADC_AADC_LVOL,
							mute_reg, 0x20);
		पंचांग6000_set_reg_mask(dev, TM6000_REQ07_RED_VADC_AADC_RVOL,
							mute_reg, 0x20);
	पूर्ण
पूर्ण

पूर्णांक पंचांग6000_tvaudio_set_mute(काष्ठा पंचांग6000_core *dev, u8 mute)
अणु
	क्रमागत पंचांग6000_mux mux;

	अगर (dev->radio)
		mux = dev->rinput.amux;
	अन्यथा
		mux = dev->vinput[dev->input].amux;

	चयन (mux) अणु
	हाल TM6000_AMUX_SIF1:
	हाल TM6000_AMUX_SIF2:
		अगर (dev->dev_type == TM6010)
			पंचांग6010_set_mute_sअगर(dev, mute);
		अन्यथा अणु
			prपूर्णांकk(KERN_INFO "ERROR: TM5600 and TM6000 don't has SIF audio inputs. Please check the %s configuration.\n",
			       dev->name);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल TM6000_AMUX_ADC1:
	हाल TM6000_AMUX_ADC2:
		पंचांग6010_set_mute_adc(dev, mute);
		अवरोध;
	शेष:
		वापस -EINVAL;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम पंचांग6010_set_volume_sअगर(काष्ठा पंचांग6000_core *dev, पूर्णांक vol)
अणु
	u8 vol_reg;

	vol_reg = vol & 0x0F;

	अगर (vol < 0)
		vol_reg |= 0x40;

	पंचांग6000_set_reg(dev, TM6010_REQ08_R07_A_LEFT_VOL, vol_reg);
	पंचांग6000_set_reg(dev, TM6010_REQ08_R08_A_RIGHT_VOL, vol_reg);
पूर्ण

अटल व्योम पंचांग6010_set_volume_adc(काष्ठा पंचांग6000_core *dev, पूर्णांक vol)
अणु
	u8 vol_reg;

	vol_reg = (vol + 0x10) & 0x1f;

	अगर (dev->dev_type == TM6010) अणु
		पंचांग6000_set_reg(dev, TM6010_REQ08_RF2_LEFT_CHANNEL_VOL, vol_reg);
		पंचांग6000_set_reg(dev, TM6010_REQ08_RF3_RIGHT_CHANNEL_VOL, vol_reg);
	पूर्ण अन्यथा अणु
		पंचांग6000_set_reg(dev, TM6000_REQ07_REC_VADC_AADC_LVOL, vol_reg);
		पंचांग6000_set_reg(dev, TM6000_REQ07_RED_VADC_AADC_RVOL, vol_reg);
	पूर्ण
पूर्ण

व्योम पंचांग6000_set_volume(काष्ठा पंचांग6000_core *dev, पूर्णांक vol)
अणु
	क्रमागत पंचांग6000_mux mux;

	अगर (dev->radio) अणु
		mux = dev->rinput.amux;
		vol += 8; /* Offset to 0 dB */
	पूर्ण अन्यथा
		mux = dev->vinput[dev->input].amux;

	चयन (mux) अणु
	हाल TM6000_AMUX_SIF1:
	हाल TM6000_AMUX_SIF2:
		अगर (dev->dev_type == TM6010)
			पंचांग6010_set_volume_sअगर(dev, vol);
		अन्यथा
			prपूर्णांकk(KERN_INFO "ERROR: TM5600 and TM6000 don't has SIF audio inputs. Please check the %s configuration.\n",
			       dev->name);
		अवरोध;
	हाल TM6000_AMUX_ADC1:
	हाल TM6000_AMUX_ADC2:
		पंचांग6010_set_volume_adc(dev, vol);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल LIST_HEAD(पंचांग6000_devlist);
अटल DEFINE_MUTEX(पंचांग6000_devlist_mutex);

/*
 * पंचांग6000_realease_resource()
 */

व्योम पंचांग6000_हटाओ_from_devlist(काष्ठा पंचांग6000_core *dev)
अणु
	mutex_lock(&पंचांग6000_devlist_mutex);
	list_del(&dev->devlist);
	mutex_unlock(&पंचांग6000_devlist_mutex);
पूर्ण;

व्योम पंचांग6000_add_पूर्णांकo_devlist(काष्ठा पंचांग6000_core *dev)
अणु
	mutex_lock(&पंचांग6000_devlist_mutex);
	list_add_tail(&dev->devlist, &पंचांग6000_devlist);
	mutex_unlock(&पंचांग6000_devlist_mutex);
पूर्ण;

/*
 * Extension पूर्णांकerface
 */

अटल LIST_HEAD(पंचांग6000_extension_devlist);

पूर्णांक पंचांग6000_call_fillbuf(काष्ठा पंचांग6000_core *dev, क्रमागत पंचांग6000_ops_type type,
			अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा पंचांग6000_ops *ops = शून्य;

	/* FIXME: पंचांग6000_extension_devlist_lock should be a spinlock */

	list_क्रम_each_entry(ops, &पंचांग6000_extension_devlist, next) अणु
		अगर (ops->fillbuf && ops->type == type)
			ops->fillbuf(dev, buf, size);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पंचांग6000_रेजिस्टर_extension(काष्ठा पंचांग6000_ops *ops)
अणु
	काष्ठा पंचांग6000_core *dev = शून्य;

	mutex_lock(&पंचांग6000_devlist_mutex);
	list_add_tail(&ops->next, &पंचांग6000_extension_devlist);
	list_क्रम_each_entry(dev, &पंचांग6000_devlist, devlist) अणु
		ops->init(dev);
		prपूर्णांकk(KERN_INFO "%s: Initialized (%s) extension\n",
		       dev->name, ops->name);
	पूर्ण
	mutex_unlock(&पंचांग6000_devlist_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(पंचांग6000_रेजिस्टर_extension);

व्योम पंचांग6000_unरेजिस्टर_extension(काष्ठा पंचांग6000_ops *ops)
अणु
	काष्ठा पंचांग6000_core *dev = शून्य;

	mutex_lock(&पंचांग6000_devlist_mutex);
	list_क्रम_each_entry(dev, &पंचांग6000_devlist, devlist)
		ops->fini(dev);

	prपूर्णांकk(KERN_INFO "tm6000: Remove (%s) extension\n", ops->name);
	list_del(&ops->next);
	mutex_unlock(&पंचांग6000_devlist_mutex);
पूर्ण
EXPORT_SYMBOL(पंचांग6000_unरेजिस्टर_extension);

व्योम पंचांग6000_init_extension(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_ops *ops = शून्य;

	mutex_lock(&पंचांग6000_devlist_mutex);
	list_क्रम_each_entry(ops, &पंचांग6000_extension_devlist, next) अणु
		अगर (ops->init)
			ops->init(dev);
	पूर्ण
	mutex_unlock(&पंचांग6000_devlist_mutex);
पूर्ण

व्योम पंचांग6000_बंद_extension(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_ops *ops = शून्य;

	mutex_lock(&पंचांग6000_devlist_mutex);
	list_क्रम_each_entry(ops, &पंचांग6000_extension_devlist, next) अणु
		अगर (ops->fini)
			ops->fini(dev);
	पूर्ण
	mutex_unlock(&पंचांग6000_devlist_mutex);
पूर्ण
