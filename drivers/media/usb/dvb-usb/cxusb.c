<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम Conexant USB reference design.
 *
 * The Conexant reference design I saw on their website was only क्रम analogue
 * capturing (using the cx25842). The box I took to ग_लिखो this driver (reverse
 * engineered) is the one labeled Medion MD95700. In addition to the cx25842
 * क्रम analogue capturing it also has a cx22702 DVB-T demodulator on the मुख्य
 * board. Besides it has a atiremote (X10) and a USB2.0 hub onboard.
 *
 * Maybe it is a little bit premature to call this driver cxusb, but I assume
 * the USB protocol is identical or at least inherited from the reference
 * design, so it can be reused क्रम the "analogue-only" device (अगर it will
 * appear at all).
 *
 *
 * Copyright (C) 2005 Patrick Boettcher (patrick.boettcher@posteo.de)
 * Copyright (C) 2006 Michael Krufky (mkrufky@linuxtv.org)
 * Copyright (C) 2006, 2007 Chris Pascoe (c.pascoe@itee.uq.edu.au)
 * Copyright (C) 2011, 2017 Maciej S. Szmigiero (mail@maciej.szmigiero.name)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश <media/tuner.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "cxusb.h"

#समावेश "cx22702.h"
#समावेश "lgdt330x.h"
#समावेश "mt352.h"
#समावेश "mt352_priv.h"
#समावेश "zl10353.h"
#समावेश "tuner-xc2028.h"
#समावेश "tuner-simple.h"
#समावेश "mxl5005s.h"
#समावेश "max2165.h"
#समावेश "dib7000p.h"
#समावेश "dib0070.h"
#समावेश "lgs8gxx.h"
#समावेश "atbm8830.h"
#समावेश "si2168.h"
#समावेश "si2157.h"

/* debug */
पूर्णांक dvb_usb_cxusb_debug;
module_param_named(debug, dvb_usb_cxusb_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (see cxusb.h)."
		 DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

क्रमागत cxusb_table_index अणु
	MEDION_MD95700,
	DVICO_BLUEBIRD_LG064F_COLD,
	DVICO_BLUEBIRD_LG064F_WARM,
	DVICO_BLUEBIRD_DUAL_1_COLD,
	DVICO_BLUEBIRD_DUAL_1_WARM,
	DVICO_BLUEBIRD_LGZ201_COLD,
	DVICO_BLUEBIRD_LGZ201_WARM,
	DVICO_BLUEBIRD_TH7579_COLD,
	DVICO_BLUEBIRD_TH7579_WARM,
	DIGITALNOW_BLUEBIRD_DUAL_1_COLD,
	DIGITALNOW_BLUEBIRD_DUAL_1_WARM,
	DVICO_BLUEBIRD_DUAL_2_COLD,
	DVICO_BLUEBIRD_DUAL_2_WARM,
	DVICO_BLUEBIRD_DUAL_4,
	DVICO_BLUEBIRD_DVB_T_न_अंकO_2,
	DVICO_BLUEBIRD_DVB_T_न_अंकO_2_NFW_WARM,
	AVERMEDIA_VOLAR_A868R,
	DVICO_BLUEBIRD_DUAL_4_REV_2,
	CONEXANT_D680_DMB,
	MYGICA_D689,
	NR__cxusb_table_index
पूर्ण;

अटल काष्ठा usb_device_id cxusb_table[];

पूर्णांक cxusb_ctrl_msg(काष्ठा dvb_usb_device *d,
		   u8 cmd, स्थिर u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा cxusb_state *st = d->priv;
	पूर्णांक ret;

	अगर (1 + wlen > MAX_XFER_SIZE) अणु
		warn("i2c wr: len=%d is too big!\n", wlen);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (rlen > MAX_XFER_SIZE) अणु
		warn("i2c rd: len=%d is too big!\n", rlen);
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&d->data_mutex);
	st->data[0] = cmd;
	स_नकल(&st->data[1], wbuf, wlen);
	ret = dvb_usb_generic_rw(d, st->data, 1 + wlen, st->data, rlen, 0);
	अगर (!ret && rbuf && rlen)
		स_नकल(rbuf, st->data, rlen);

	mutex_unlock(&d->data_mutex);
	वापस ret;
पूर्ण

/* GPIO */
अटल व्योम cxusb_gpio_tuner(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	काष्ठा cxusb_state *st = d->priv;
	u8 o[2], i;

	अगर (st->gpio_ग_लिखो_state[GPIO_TUNER] == onoff &&
	    !st->gpio_ग_लिखो_refresh[GPIO_TUNER])
		वापस;

	o[0] = GPIO_TUNER;
	o[1] = onoff;
	cxusb_ctrl_msg(d, CMD_GPIO_WRITE, o, 2, &i, 1);

	अगर (i != 0x01)
		dev_info(&d->udev->dev, "gpio_write failed.\n");

	st->gpio_ग_लिखो_state[GPIO_TUNER] = onoff;
	st->gpio_ग_लिखो_refresh[GPIO_TUNER] = false;
पूर्ण

अटल पूर्णांक cxusb_bluebird_gpio_rw(काष्ठा dvb_usb_device *d, u8 changemask,
				  u8 newval)
अणु
	u8 o[2], gpio_state;
	पूर्णांक rc;

	o[0] = 0xff & ~changemask;	/* mask of bits to keep */
	o[1] = newval & changemask;	/* new values क्रम bits  */

	rc = cxusb_ctrl_msg(d, CMD_BLUEBIRD_GPIO_RW, o, 2, &gpio_state, 1);
	अगर (rc < 0 || (gpio_state & changemask) != (newval & changemask))
		dev_info(&d->udev->dev, "bluebird_gpio_write failed.\n");

	वापस rc < 0 ? rc : gpio_state;
पूर्ण

अटल व्योम cxusb_bluebird_gpio_pulse(काष्ठा dvb_usb_device *d, u8 pin, पूर्णांक low)
अणु
	cxusb_bluebird_gpio_rw(d, pin, low ? 0 : pin);
	msleep(5);
	cxusb_bluebird_gpio_rw(d, pin, low ? pin : 0);
पूर्ण

अटल व्योम cxusb_nano2_led(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	cxusb_bluebird_gpio_rw(d, 0x40, onoff ? 0 : 0x40);
पूर्ण

अटल पूर्णांक cxusb_d680_dmb_gpio_tuner(काष्ठा dvb_usb_device *d,
				     u8 addr, पूर्णांक onoff)
अणु
	u8  o[2] = अणुaddr, onoffपूर्ण;
	u8  i;
	पूर्णांक rc;

	rc = cxusb_ctrl_msg(d, CMD_GPIO_WRITE, o, 2, &i, 1);

	अगर (rc < 0)
		वापस rc;

	अगर (i == 0x01)
		वापस 0;

	dev_info(&d->udev->dev, "gpio_write failed.\n");
	वापस -EIO;
पूर्ण

/* I2C */
अटल पूर्णांक cxusb_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
			  पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		अगर (le16_to_cpu(d->udev->descriptor.idVenकरोr) == USB_VID_MEDION)
			चयन (msg[i].addr) अणु
			हाल 0x63:
				cxusb_gpio_tuner(d, 0);
				अवरोध;
			शेष:
				cxusb_gpio_tuner(d, 1);
				अवरोध;
			पूर्ण

		अगर (msg[i].flags & I2C_M_RD) अणु
			/* पढ़ो only */
			u8 obuf[3], ibuf[MAX_XFER_SIZE];

			अगर (1 + msg[i].len > माप(ibuf)) अणु
				warn("i2c rd: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण
			obuf[0] = 0;
			obuf[1] = msg[i].len;
			obuf[2] = msg[i].addr;
			अगर (cxusb_ctrl_msg(d, CMD_I2C_READ,
					   obuf, 3,
					   ibuf, 1 + msg[i].len) < 0) अणु
				warn("i2c read failed");
				अवरोध;
			पूर्ण
			स_नकल(msg[i].buf, &ibuf[1], msg[i].len);
		पूर्ण अन्यथा अगर (i + 1 < num && (msg[i + 1].flags & I2C_M_RD) &&
			   msg[i].addr == msg[i + 1].addr) अणु
			/* ग_लिखो to then पढ़ो from same address */
			u8 obuf[MAX_XFER_SIZE], ibuf[MAX_XFER_SIZE];

			अगर (3 + msg[i].len > माप(obuf)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण
			अगर (1 + msg[i + 1].len > माप(ibuf)) अणु
				warn("i2c rd: len=%d is too big!\n",
				     msg[i + 1].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण
			obuf[0] = msg[i].len;
			obuf[1] = msg[i + 1].len;
			obuf[2] = msg[i].addr;
			स_नकल(&obuf[3], msg[i].buf, msg[i].len);

			अगर (cxusb_ctrl_msg(d, CMD_I2C_READ,
					   obuf, 3 + msg[i].len,
					   ibuf, 1 + msg[i + 1].len) < 0)
				अवरोध;

			अगर (ibuf[0] != 0x08)
				dev_info(&d->udev->dev, "i2c read may have failed\n");

			स_नकल(msg[i + 1].buf, &ibuf[1], msg[i + 1].len);

			i++;
		पूर्ण अन्यथा अणु
			/* ग_लिखो only */
			u8 obuf[MAX_XFER_SIZE], ibuf;

			अगर (2 + msg[i].len > माप(obuf)) अणु
				warn("i2c wr: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				जाओ unlock;
			पूर्ण
			obuf[0] = msg[i].addr;
			obuf[1] = msg[i].len;
			स_नकल(&obuf[2], msg[i].buf, msg[i].len);

			अगर (cxusb_ctrl_msg(d, CMD_I2C_WRITE, obuf,
					   2 + msg[i].len, &ibuf, 1) < 0)
				अवरोध;
			अगर (ibuf != 0x08)
				dev_info(&d->udev->dev, "i2c write may have failed\n");
		पूर्ण
	पूर्ण

	अगर (i == num)
		ret = num;
	अन्यथा
		ret = -EREMOTEIO;

unlock:
	mutex_unlock(&d->i2c_mutex);
	वापस ret;
पूर्ण

अटल u32 cxusb_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल काष्ठा i2c_algorithm cxusb_i2c_algo = अणु
	.master_xfer   = cxusb_i2c_xfer,
	.functionality = cxusb_i2c_func,
पूर्ण;

अटल पूर्णांक _cxusb_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 b = 0;

	dev_info(&d->udev->dev, "setting power %s\n", onoff ? "ON" : "OFF");

	अगर (onoff)
		वापस cxusb_ctrl_msg(d, CMD_POWER_ON, &b, 1, शून्य, 0);
	अन्यथा
		वापस cxusb_ctrl_msg(d, CMD_POWER_OFF, &b, 1, शून्य, 0);
पूर्ण

अटल पूर्णांक cxusb_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	bool is_medion = d->props.devices[0].warm_ids[0] == &cxusb_table[MEDION_MD95700];
	पूर्णांक ret;

	अगर (is_medion && !onoff) अणु
		काष्ठा cxusb_medion_dev *cxdev = d->priv;

		mutex_lock(&cxdev->खोलो_lock);

		अगर (cxdev->खोलो_type == CXUSB_OPEN_ANALOG) अणु
			dev_info(&d->udev->dev, "preventing DVB core from setting power OFF while we are in analog mode\n");
			ret = -EBUSY;
			जाओ ret_unlock;
		पूर्ण
	पूर्ण

	ret = _cxusb_घातer_ctrl(d, onoff);

ret_unlock:
	अगर (is_medion && !onoff) अणु
		काष्ठा cxusb_medion_dev *cxdev = d->priv;

		mutex_unlock(&cxdev->खोलो_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_aver_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;

	अगर (!onoff)
		वापस cxusb_ctrl_msg(d, CMD_POWER_OFF, शून्य, 0, शून्य, 0);
	अगर (d->state == DVB_USB_STATE_INIT &&
	    usb_set_पूर्णांकerface(d->udev, 0, 0) < 0)
		err("set interface failed");
	करो अणु
		/* Nothing */
	पूर्ण जबतक (!(ret = cxusb_ctrl_msg(d, CMD_POWER_ON, शून्य, 0, शून्य, 0)) &&
		 !(ret = cxusb_ctrl_msg(d, 0x15, शून्य, 0, शून्य, 0)) &&
		 !(ret = cxusb_ctrl_msg(d, 0x17, शून्य, 0, शून्य, 0)) && 0);

	अगर (!ret) अणु
		/*
		 * FIXME: We करोn't know why, but we need to configure the
		 * lgdt3303 with the रेजिस्टर settings below on resume
		 */
		पूर्णांक i;
		u8 buf;
		अटल स्थिर u8 bufs[] = अणु
			0x0e, 0x2, 0x00, 0x7f,
			0x0e, 0x2, 0x02, 0xfe,
			0x0e, 0x2, 0x02, 0x01,
			0x0e, 0x2, 0x00, 0x03,
			0x0e, 0x2, 0x0d, 0x40,
			0x0e, 0x2, 0x0e, 0x87,
			0x0e, 0x2, 0x0f, 0x8e,
			0x0e, 0x2, 0x10, 0x01,
			0x0e, 0x2, 0x14, 0xd7,
			0x0e, 0x2, 0x47, 0x88,
		पूर्ण;
		msleep(20);
		क्रम (i = 0; i < ARRAY_SIZE(bufs); i += 4 / माप(u8)) अणु
			ret = cxusb_ctrl_msg(d, CMD_I2C_WRITE,
					     bufs + i, 4, &buf, 1);
			अगर (ret)
				अवरोध;
			अगर (buf != 0x8)
				वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_bluebird_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 b = 0;

	अगर (onoff)
		वापस cxusb_ctrl_msg(d, CMD_POWER_ON, &b, 1, शून्य, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक cxusb_nano2_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक rc = 0;

	rc = cxusb_घातer_ctrl(d, onoff);
	अगर (!onoff)
		cxusb_nano2_led(d, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक cxusb_d680_dmb_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	u8  b;

	ret = cxusb_घातer_ctrl(d, onoff);
	अगर (!onoff)
		वापस ret;

	msleep(128);
	cxusb_ctrl_msg(d, CMD_DIGITAL, शून्य, 0, &b, 1);
	msleep(100);
	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *dvbdev = adap->dev;
	bool is_medion = dvbdev->props.devices[0].warm_ids[0] ==
		&cxusb_table[MEDION_MD95700];
	u8 buf[2] = अणु 0x03, 0x00 पूर्ण;

	अगर (is_medion && onoff) अणु
		पूर्णांक ret;

		ret = cxusb_medion_get(dvbdev, CXUSB_OPEN_DIGITAL);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	अगर (onoff)
		cxusb_ctrl_msg(dvbdev, CMD_STREAMING_ON, buf, 2, शून्य, 0);
	अन्यथा
		cxusb_ctrl_msg(dvbdev, CMD_STREAMING_OFF, शून्य, 0, शून्य, 0);

	अगर (is_medion && !onoff)
		cxusb_medion_put(dvbdev);

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_aver_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	अगर (onoff)
		cxusb_ctrl_msg(adap->dev, CMD_AVER_STREAM_ON, शून्य, 0, शून्य, 0);
	अन्यथा
		cxusb_ctrl_msg(adap->dev, CMD_AVER_STREAM_OFF,
			       शून्य, 0, शून्य, 0);
	वापस 0;
पूर्ण

अटल व्योम cxusb_d680_dmb_drain_message(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक       ep = d->props.generic_bulk_ctrl_endpoपूर्णांक;
	स्थिर पूर्णांक समयout = 100;
	स्थिर पूर्णांक junk_len = 32;
	u8        *junk;
	पूर्णांक       rd_count;

	/* Discard reमुख्यing data in video pipe */
	junk = kदो_स्मृति(junk_len, GFP_KERNEL);
	अगर (!junk)
		वापस;
	जबतक (1) अणु
		अगर (usb_bulk_msg(d->udev,
				 usb_rcvbulkpipe(d->udev, ep),
				 junk, junk_len, &rd_count, समयout) < 0)
			अवरोध;
		अगर (!rd_count)
			अवरोध;
	पूर्ण
	kमुक्त(junk);
पूर्ण

अटल व्योम cxusb_d680_dmb_drain_video(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा usb_data_stream_properties *p = &d->props.adapter[0].fe[0].stream;
	स्थिर पूर्णांक समयout = 100;
	स्थिर पूर्णांक junk_len = p->u.bulk.buffersize;
	u8        *junk;
	पूर्णांक       rd_count;

	/* Discard reमुख्यing data in video pipe */
	junk = kदो_स्मृति(junk_len, GFP_KERNEL);
	अगर (!junk)
		वापस;
	जबतक (1) अणु
		अगर (usb_bulk_msg(d->udev,
				 usb_rcvbulkpipe(d->udev, p->endpoपूर्णांक),
				 junk, junk_len, &rd_count, समयout) < 0)
			अवरोध;
		अगर (!rd_count)
			अवरोध;
	पूर्ण
	kमुक्त(junk);
पूर्ण

अटल पूर्णांक cxusb_d680_dmb_streaming_ctrl(काष्ठा dvb_usb_adapter *adap,
					 पूर्णांक onoff)
अणु
	अगर (onoff) अणु
		u8 buf[2] = अणु 0x03, 0x00 पूर्ण;

		cxusb_d680_dmb_drain_video(adap->dev);
		वापस cxusb_ctrl_msg(adap->dev, CMD_STREAMING_ON,
				      buf, माप(buf), शून्य, 0);
	पूर्ण अन्यथा अणु
		पूर्णांक ret = cxusb_ctrl_msg(adap->dev,
					 CMD_STREAMING_OFF, शून्य, 0, शून्य, 0);
		वापस ret;
	पूर्ण
पूर्ण

अटल पूर्णांक cxusb_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 ircode[4];

	अगर (cxusb_ctrl_msg(d, CMD_GET_IR_CODE, शून्य, 0, ircode, 4) < 0)
		वापस 0;

	अगर (ircode[2] || ircode[3])
		rc_keyकरोwn(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(~ircode[2] & 0xff, ircode[3]), 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_bluebird2_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 ircode[4];
	काष्ठा i2c_msg msg = अणु
		.addr = 0x6b,
		.flags = I2C_M_RD,
		.buf = ircode,
		.len = 4
	पूर्ण;

	अगर (cxusb_i2c_xfer(&d->i2c_adap, &msg, 1) != 1)
		वापस 0;

	अगर (ircode[1] || ircode[2])
		rc_keyकरोwn(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(~ircode[1] & 0xff, ircode[2]), 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_d680_dmb_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u8 ircode[2];

	अगर (cxusb_ctrl_msg(d, 0x10, शून्य, 0, ircode, 2) < 0)
		वापस 0;

	अगर (ircode[0] || ircode[1])
		rc_keyकरोwn(d->rc_dev, RC_PROTO_UNKNOWN,
			   RC_SCANCODE_RC5(ircode[0], ircode[1]), 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_dee1601_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 घड़ी_config[]   = अणु CLOCK_CTL,  0x38, 0x28 पूर्ण;
	अटल u8 reset[]          = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg[]  = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg[]        = अणु AGC_TARGET, 0x28, 0x20 पूर्ण;
	अटल u8 gpp_ctl_cfg[]    = अणु GPP_CTL,    0x33 पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_mt352_demod_init(काष्ठा dvb_frontend *fe)
अणु
	/* used in both lgz201 and th7579 */
	अटल u8 घड़ी_config[]   = अणु CLOCK_CTL,  0x38, 0x29 पूर्ण;
	अटल u8 reset[]          = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg[]  = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg[]        = अणु AGC_TARGET, 0x24, 0x20 पूर्ण;
	अटल u8 gpp_ctl_cfg[]    = अणु GPP_CTL,    0x33 पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));
	वापस 0;
पूर्ण

अटल काष्ठा cx22702_config cxusb_cx22702_config = अणु
	.demod_address = 0x63,
	.output_mode = CX22702_PARALLEL_OUTPUT,
पूर्ण;

अटल काष्ठा lgdt330x_config cxusb_lgdt3303_config = अणु
	.demod_chip    = LGDT3303,
पूर्ण;

अटल काष्ठा lgdt330x_config cxusb_aver_lgdt3303_config = अणु
	.demod_chip          = LGDT3303,
	.घड़ी_polarity_flip = 2,
पूर्ण;

अटल काष्ठा mt352_config cxusb_dee1601_config = अणु
	.demod_address = 0x0f,
	.demod_init    = cxusb_dee1601_demod_init,
पूर्ण;

अटल काष्ठा zl10353_config cxusb_zl10353_dee1601_config = अणु
	.demod_address = 0x0f,
	.parallel_ts = 1,
पूर्ण;

अटल काष्ठा mt352_config cxusb_mt352_config = अणु
	/* used in both lgz201 and th7579 */
	.demod_address = 0x0f,
	.demod_init    = cxusb_mt352_demod_init,
पूर्ण;

अटल काष्ठा zl10353_config cxusb_zl10353_xc3028_config = अणु
	.demod_address = 0x0f,
	.अगर2 = 45600,
	.no_tuner = 1,
	.parallel_ts = 1,
पूर्ण;

अटल काष्ठा zl10353_config cxusb_zl10353_xc3028_config_no_i2c_gate = अणु
	.demod_address = 0x0f,
	.अगर2 = 45600,
	.no_tuner = 1,
	.parallel_ts = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा mt352_config cxusb_mt352_xc3028_config = अणु
	.demod_address = 0x0f,
	.अगर2 = 4560,
	.no_tuner = 1,
	.demod_init = cxusb_mt352_demod_init,
पूर्ण;

/* FIXME: needs tweaking */
अटल काष्ठा mxl5005s_config aver_a868r_tuner = अणु
	.i2c_address     = 0x63,
	.अगर_freq         = 6000000UL,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_C,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

/* FIXME: needs tweaking */
अटल काष्ठा mxl5005s_config d680_dmb_tuner = अणु
	.i2c_address     = 0x63,
	.अगर_freq         = 36125000UL,
	.xtal_freq       = CRYSTAL_FREQ_16000000HZ,
	.agc_mode        = MXL_SINGLE_AGC,
	.tracking_filter = MXL_TF_C,
	.rssi_enable     = MXL_RSSI_ENABLE,
	.cap_select      = MXL_CAP_SEL_ENABLE,
	.भाग_out         = MXL_DIV_OUT_4,
	.घड़ी_out       = MXL_CLOCK_OUT_DISABLE,
	.output_load     = MXL5005S_IF_OUTPUT_LOAD_200_OHM,
	.top		 = MXL5005S_TOP_25P2,
	.mod_mode        = MXL_DIGITAL_MODE,
	.अगर_mode         = MXL_ZERO_IF,
	.AgcMasterByte   = 0x00,
पूर्ण;

अटल काष्ठा max2165_config mygica_d689_max2165_cfg = अणु
	.i2c_address = 0x60,
	.osc_clk = 20
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल पूर्णांक cxusb_fmd1216me_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *dvbdev = adap->dev;
	bool is_medion = dvbdev->props.devices[0].warm_ids[0] ==
		&cxusb_table[MEDION_MD95700];

	dvb_attach(simple_tuner_attach, adap->fe_adap[0].fe,
		   &dvbdev->i2c_adap, 0x61,
		   TUNER_PHILIPS_FMD1216ME_MK3);

	अगर (is_medion && adap->fe_adap[0].fe)
		/*
		 * make sure that DVB core won't put to sleep (reset, really)
		 * tuner when we might be खोलो in analog mode
		 */
		adap->fe_adap[0].fe->ops.tuner_ops.sleep = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_dee1601_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x61,
		   शून्य, DVB_PLL_THOMSON_DTT7579);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_lgz201_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x61,
		   शून्य, DVB_PLL_LG_Z201);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_dtt7579_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60,
		   शून्य, DVB_PLL_THOMSON_DTT7579);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_lgh064f_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(simple_tuner_attach, adap->fe_adap[0].fe,
		   &adap->dev->i2c_adap, 0x61, TUNER_LG_TDVS_H06XF);
	वापस 0;
पूर्ण

अटल पूर्णांक dvico_bluebird_xc2028_callback(व्योम *ptr, पूर्णांक component,
					  पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा dvb_usb_adapter *adap = ptr;
	काष्ठा dvb_usb_device *d = adap->dev;

	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		dev_info(&d->udev->dev, "XC2028_TUNER_RESET %d\n", arg);
		cxusb_bluebird_gpio_pulse(d, 0x01, 1);
		अवरोध;
	हाल XC2028_RESET_CLK:
		dev_info(&d->udev->dev, "XC2028_RESET_CLK %d\n", arg);
		अवरोध;
	हाल XC2028_I2C_FLUSH:
		अवरोध;
	शेष:
		dev_info(&d->udev->dev, "unknown command %d, arg %d\n",
			 command, arg);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_dvico_xc3028_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_frontend	 *fe;
	काष्ठा xc2028_config	  cfg = अणु
		.i2c_adap  = &adap->dev->i2c_adap,
		.i2c_addr  = 0x61,
	पूर्ण;
	अटल काष्ठा xc2028_ctrl ctl = अणु
		.fname       = XC2028_DEFAULT_FIRMWARE,
		.max_len     = 64,
		.demod       = XC3028_FE_ZARLINK456,
	पूर्ण;

	/* FIXME: generalize & move to common area */
	adap->fe_adap[0].fe->callback = dvico_bluebird_xc2028_callback;

	fe = dvb_attach(xc2028_attach, adap->fe_adap[0].fe, &cfg);
	अगर (!fe || !fe->ops.tuner_ops.set_config)
		वापस -EIO;

	fe->ops.tuner_ops.set_config(fe, &ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_mxl5003s_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(mxl5005s_attach, adap->fe_adap[0].fe,
		   &adap->dev->i2c_adap, &aver_a868r_tuner);
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_d680_dmb_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_frontend *fe;

	fe = dvb_attach(mxl5005s_attach, adap->fe_adap[0].fe,
			&adap->dev->i2c_adap, &d680_dmb_tuner);
	वापस (!fe) ? -EIO : 0;
पूर्ण

अटल पूर्णांक cxusb_mygica_d689_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_frontend *fe;

	fe = dvb_attach(max2165_attach, adap->fe_adap[0].fe,
			&adap->dev->i2c_adap, &mygica_d689_max2165_cfg);
	वापस (!fe) ? -EIO : 0;
पूर्ण

अटल पूर्णांक cxusb_medion_fe_ts_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dvb_usb_device *dvbdev = adap->dev;

	अगर (acquire)
		वापस cxusb_medion_get(dvbdev, CXUSB_OPEN_DIGITAL);

	cxusb_medion_put(dvbdev);

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_medion_set_mode(काष्ठा dvb_usb_device *dvbdev, bool digital)
अणु
	काष्ठा cxusb_state *st = dvbdev->priv;
	पूर्णांक ret;
	u8 b;
	अचिन्हित पूर्णांक i;

	/*
	 * चयनing mode जबतक करोing an I2C transaction often causes
	 * the device to crash
	 */
	mutex_lock(&dvbdev->i2c_mutex);

	अगर (digital) अणु
		ret = usb_set_पूर्णांकerface(dvbdev->udev, 0, 6);
		अगर (ret != 0) अणु
			dev_err(&dvbdev->udev->dev,
				"digital interface selection failed (%d)\n",
				ret);
			जाओ ret_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = usb_set_पूर्णांकerface(dvbdev->udev, 0, 1);
		अगर (ret != 0) अणु
			dev_err(&dvbdev->udev->dev,
				"analog interface selection failed (%d)\n",
				ret);
			जाओ ret_unlock;
		पूर्ण
	पूर्ण

	/* pipes need to be cleared after setting पूर्णांकerface */
	ret = usb_clear_halt(dvbdev->udev, usb_rcvbulkpipe(dvbdev->udev, 1));
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "clear halt on IN pipe failed (%d)\n",
			 ret);

	ret = usb_clear_halt(dvbdev->udev, usb_sndbulkpipe(dvbdev->udev, 1));
	अगर (ret != 0)
		dev_warn(&dvbdev->udev->dev,
			 "clear halt on OUT pipe failed (%d)\n",
			 ret);

	ret = cxusb_ctrl_msg(dvbdev, digital ? CMD_DIGITAL : CMD_ANALOG,
			     शून्य, 0, &b, 1);
	अगर (ret != 0) अणु
		dev_err(&dvbdev->udev->dev, "mode switch failed (%d)\n",
			ret);
		जाओ ret_unlock;
	पूर्ण

	/* mode चयन seems to reset GPIO states */
	क्रम (i = 0; i < ARRAY_SIZE(st->gpio_ग_लिखो_refresh); i++)
		st->gpio_ग_लिखो_refresh[i] = true;

ret_unlock:
	mutex_unlock(&dvbdev->i2c_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक cxusb_cx22702_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *dvbdev = adap->dev;
	bool is_medion = dvbdev->props.devices[0].warm_ids[0] ==
		&cxusb_table[MEDION_MD95700];

	अगर (is_medion) अणु
		पूर्णांक ret;

		ret = cxusb_medion_set_mode(dvbdev, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	adap->fe_adap[0].fe = dvb_attach(cx22702_attach, &cxusb_cx22702_config,
					 &dvbdev->i2c_adap);
	अगर (!adap->fe_adap[0].fe)
		वापस -EIO;

	अगर (is_medion)
		adap->fe_adap[0].fe->ops.ts_bus_ctrl =
			cxusb_medion_fe_ts_bus_ctrl;

	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_lgdt3303_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 7) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	adap->fe_adap[0].fe = dvb_attach(lgdt330x_attach,
					 &cxusb_lgdt3303_config,
					 0x0e,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक cxusb_aver_lgdt3303_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	adap->fe_adap[0].fe = dvb_attach(lgdt330x_attach,
					 &cxusb_aver_lgdt3303_config,
					 0x0e,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक cxusb_mt352_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	/* used in both lgz201 and th7579 */
	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 0) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &cxusb_mt352_config,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक cxusb_dee1601_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 0) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &cxusb_dee1601_config,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	adap->fe_adap[0].fe = dvb_attach(zl10353_attach,
					 &cxusb_zl10353_dee1601_config,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक cxusb_dualdig4_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	u8 ircode[4];
	पूर्णांक i;
	काष्ठा i2c_msg msg = अणु
		.addr = 0x6b,
		.flags = I2C_M_RD,
		.buf = ircode,
		.len = 4
	पूर्ण;

	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 1) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	/* reset the tuner and demodulator */
	cxusb_bluebird_gpio_rw(adap->dev, 0x04, 0);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x01, 1);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1);

	adap->fe_adap[0].fe =
		dvb_attach(zl10353_attach,
			   &cxusb_zl10353_xc3028_config_no_i2c_gate,
			   &adap->dev->i2c_adap);
	अगर (!adap->fe_adap[0].fe)
		वापस -EIO;

	/* try to determine अगर there is no IR decoder on the I2C bus */
	क्रम (i = 0; adap->dev->props.rc.core.rc_codes && i < 5; i++) अणु
		msleep(20);
		अगर (cxusb_i2c_xfer(&adap->dev->i2c_adap, &msg, 1) != 1)
			जाओ no_IR;
		अगर (ircode[0] == 0 && ircode[1] == 0)
			जारी;
		अगर (ircode[2] + ircode[3] != 0xff) अणु
no_IR:
			adap->dev->props.rc.core.rc_codes = शून्य;
			info("No IR receiver detected on this device.");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dibx000_agc_config dib7070_agc_config = अणु
	.band_caps = BAND_UHF | BAND_VHF | BAND_LBAND | BAND_SBAND,

	/*
	 * P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=5,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
	 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0
	 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) |
		 (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),
	.inv_gain = 600,
	.समय_stabiliz = 10,
	.alpha_level = 0,
	.thlock = 118,
	.wbd_inv = 0,
	.wbd_ref = 3530,
	.wbd_sel = 1,
	.wbd_alpha = 5,
	.agc1_max = 65535,
	.agc1_min = 0,
	.agc2_max = 65535,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 40,
	.agc1_pt3 = 183,
	.agc1_slope1 = 206,
	.agc1_slope2 = 255,
	.agc2_pt1 = 72,
	.agc2_pt2 = 152,
	.agc2_slope1 = 88,
	.agc2_slope2 = 90,
	.alpha_mant = 17,
	.alpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.perक्रमm_agc_softsplit = 0,
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib7070_bw_config_12_mhz = अणु
	.पूर्णांकernal = 60000,
	.sampling = 15000,
	.pll_preभाग = 1,
	.pll_ratio = 20,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	/* refsel, sel, freq_15k */
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = (0 << 25) | 0,
	.timf = 20452225,
	.xtal_hz = 12000000,
पूर्ण;

अटल काष्ठा dib7000p_config cxusb_dualdig4_rev2_config = अणु
	.output_mode = OUTMODE_MPEG2_PAR_GATED_CLK,
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tuner_is_baseband = 1,
	.spur_protect = 1,

	.gpio_dir = 0xfcef,
	.gpio_val = 0x0110,

	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
पूर्ण;

काष्ठा dib0700_adapter_state अणु
	पूर्णांक (*set_param_save)(काष्ठा dvb_frontend *fe);
	काष्ठा dib7000p_ops dib7000p_ops;
पूर्ण;

अटल पूर्णांक cxusb_dualdig4_rev2_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 1) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1);

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
						&cxusb_dualdig4_rev2_config) < 0) अणु
		pr_warn("Unable to enumerate dib7000p\n");
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
						       0x80,
						       &cxusb_dualdig4_rev2_config);
	अगर (!adap->fe_adap[0].fe)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dib7070_tuner_reset(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	वापस state->dib7000p_ops.set_gpio(fe, 8, 0, !onoff);
पूर्ण

अटल पूर्णांक dib7070_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा dib0070_config dib7070p_dib0070_config = अणु
	.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
	.reset = dib7070_tuner_reset,
	.sleep = dib7070_tuner_sleep,
	.घड़ी_khz = 12000,
पूर्ण;

अटल पूर्णांक dib7070_set_param_override(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	u16 offset;
	u8 band = BAND_OF_FREQUENCY(p->frequency / 1000);

	चयन (band) अणु
	हाल BAND_VHF:
		offset = 950;
		अवरोध;
	शेष:
	हाल BAND_UHF:
		offset = 550;
		अवरोध;
	पूर्ण

	state->dib7000p_ops.set_wbd_ref(fe, offset + dib0070_wbd_offset(fe));

	वापस state->set_param_save(fe);
पूर्ण

अटल पूर्णांक cxusb_dualdig4_rev2_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c;

	/*
	 * No need to call dvb7000p_attach here, as it was called
	 * alपढ़ोy, as frontend_attach method is called first, and
	 * tuner_attach is only called on success.
	 */
	tun_i2c = st->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
					DIBX000_I2C_INTERFACE_TUNER, 1);

	अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
		       &dib7070p_dib0070_config) == शून्य)
		वापस -ENODEV;

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7070_set_param_override;
	वापस 0;
पूर्ण

अटल पूर्णांक cxusb_nano2_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 1) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0);

	/* reset the tuner and demodulator */
	cxusb_bluebird_gpio_rw(adap->dev, 0x04, 0);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x01, 1);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1);

	adap->fe_adap[0].fe = dvb_attach(zl10353_attach,
					 &cxusb_zl10353_xc3028_config,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach,
					 &cxusb_mt352_xc3028_config,
					 &adap->dev->i2c_adap);
	अगर (adap->fe_adap[0].fe)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल काष्ठा lgs8gxx_config d680_lgs8gl5_cfg = अणु
	.prod = LGS8GXX_PROD_LGS8GL5,
	.demod_address = 0x19,
	.serial_ts = 0,
	.ts_clk_pol = 0,
	.ts_clk_gated = 1,
	.अगर_clk_freq = 30400, /* 30.4 MHz */
	.अगर_freq = 5725, /* 5.725 MHz */
	.अगर_neg_center = 0,
	.ext_adc = 0,
	.adc_चिन्हित = 0,
	.अगर_neg_edge = 0,
पूर्ण;

अटल पूर्णांक cxusb_d680_dmb_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;
	पूर्णांक n;

	/* Select required USB configuration */
	अगर (usb_set_पूर्णांकerface(d->udev, 0, 0) < 0)
		err("set interface failed");

	/* Unblock all USB pipes */
	usb_clear_halt(d->udev,
		       usb_sndbulkpipe(d->udev,
				       d->props.generic_bulk_ctrl_endpoपूर्णांक));
	usb_clear_halt(d->udev,
		       usb_rcvbulkpipe(d->udev,
				       d->props.generic_bulk_ctrl_endpoपूर्णांक));
	usb_clear_halt(d->udev,
		       usb_rcvbulkpipe(d->udev,
				       d->props.adapter[0].fe[0].stream.endpoपूर्णांक));

	/* Drain USB pipes to aव्योम hang after reboot */
	क्रम (n = 0;  n < 5;  n++) अणु
		cxusb_d680_dmb_drain_message(d);
		cxusb_d680_dmb_drain_video(d);
		msleep(200);
	पूर्ण

	/* Reset the tuner */
	अगर (cxusb_d680_dmb_gpio_tuner(d, 0x07, 0) < 0) अणु
		err("clear tuner gpio failed");
		वापस -EIO;
	पूर्ण
	msleep(100);
	अगर (cxusb_d680_dmb_gpio_tuner(d, 0x07, 1) < 0) अणु
		err("set tuner gpio failed");
		वापस -EIO;
	पूर्ण
	msleep(100);

	/* Attach frontend */
	adap->fe_adap[0].fe = dvb_attach(lgs8gxx_attach,
					 &d680_lgs8gl5_cfg, &d->i2c_adap);
	अगर (!adap->fe_adap[0].fe)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा atbm8830_config mygica_d689_atbm8830_cfg = अणु
	.prod = ATBM8830_PROD_8830,
	.demod_address = 0x40,
	.serial_ts = 0,
	.ts_sampling_edge = 1,
	.ts_clk_gated = 0,
	.osc_clk_freq = 30400, /* in kHz */
	.अगर_freq = 0, /* zero IF */
	.zअगर_swap_iq = 1,
	.agc_min = 0x2E,
	.agc_max = 0x90,
	.agc_hold_loop = 0,
पूर्ण;

अटल पूर्णांक cxusb_mygica_d689_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap->dev;

	/* Select required USB configuration */
	अगर (usb_set_पूर्णांकerface(d->udev, 0, 0) < 0)
		err("set interface failed");

	/* Unblock all USB pipes */
	usb_clear_halt(d->udev,
		       usb_sndbulkpipe(d->udev,
				       d->props.generic_bulk_ctrl_endpoपूर्णांक));
	usb_clear_halt(d->udev,
		       usb_rcvbulkpipe(d->udev,
				       d->props.generic_bulk_ctrl_endpoपूर्णांक));
	usb_clear_halt(d->udev,
		       usb_rcvbulkpipe(d->udev,
				       d->props.adapter[0].fe[0].stream.endpoपूर्णांक));

	/* Reset the tuner */
	अगर (cxusb_d680_dmb_gpio_tuner(d, 0x07, 0) < 0) अणु
		err("clear tuner gpio failed");
		वापस -EIO;
	पूर्ण
	msleep(100);
	अगर (cxusb_d680_dmb_gpio_tuner(d, 0x07, 1) < 0) अणु
		err("set tuner gpio failed");
		वापस -EIO;
	पूर्ण
	msleep(100);

	/* Attach frontend */
	adap->fe_adap[0].fe = dvb_attach(atbm8830_attach,
					 &mygica_d689_atbm8830_cfg,
					 &d->i2c_adap);
	अगर (!adap->fe_adap[0].fe)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * DViCO has shipped two devices with the same USB ID, but only one of them
 * needs a firmware करोwnload.  Check the device class details to see अगर they
 * have non-शेष values to decide whether the device is actually cold or
 * not, and क्रमget a match अगर it turns out we selected the wrong device.
 */
अटल पूर्णांक bluebird_fx2_identअगरy_state(काष्ठा usb_device *udev,
				       स्थिर काष्ठा dvb_usb_device_properties *props,
				       स्थिर काष्ठा dvb_usb_device_description **desc,
				       पूर्णांक *cold)
अणु
	पूर्णांक wascold = *cold;

	*cold = udev->descriptor.bDeviceClass == 0xff &&
		udev->descriptor.bDeviceSubClass == 0xff &&
		udev->descriptor.bDeviceProtocol == 0xff;

	अगर (*cold && !wascold)
		*desc = शून्य;

	वापस 0;
पूर्ण

/*
 * DViCO bluebird firmware needs the "warm" product ID to be patched पूर्णांकo the
 * firmware file beक्रमe करोwnload.
 */

अटल स्थिर पूर्णांक dvico_firmware_id_offsets[] = अणु 6638, 3204 पूर्ण;
अटल पूर्णांक bluebird_patch_dvico_firmware_करोwnload(काष्ठा usb_device *udev,
						  स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक pos;

	क्रम (pos = 0; pos < ARRAY_SIZE(dvico_firmware_id_offsets); pos++) अणु
		पूर्णांक iकरोff = dvico_firmware_id_offsets[pos];

		अगर (fw->size < iकरोff + 4)
			जारी;

		अगर (fw->data[iकरोff] == (USB_VID_DVICO & 0xff) &&
		    fw->data[iकरोff + 1] == USB_VID_DVICO >> 8) अणु
			काष्ठा firmware new_fw;
			u8 *new_fw_data = vदो_स्मृति(fw->size);
			पूर्णांक ret;

			अगर (!new_fw_data)
				वापस -ENOMEM;

			स_नकल(new_fw_data, fw->data, fw->size);
			new_fw.size = fw->size;
			new_fw.data = new_fw_data;

			new_fw_data[iकरोff + 2] =
				le16_to_cpu(udev->descriptor.idProduct) + 1;
			new_fw_data[iकरोff + 3] =
				le16_to_cpu(udev->descriptor.idProduct) >> 8;

			ret = usb_cypress_load_firmware(udev, &new_fw,
							CYPRESS_FX2);
			vमुक्त(new_fw_data);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक cxusb_medion_get(काष्ठा dvb_usb_device *dvbdev,
		     क्रमागत cxusb_खोलो_type खोलो_type)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;
	पूर्णांक ret = 0;

	mutex_lock(&cxdev->खोलो_lock);

	अगर (WARN_ON((cxdev->खोलो_type == CXUSB_OPEN_INIT ||
		     cxdev->खोलो_type == CXUSB_OPEN_NONE) &&
		    cxdev->खोलो_ctr != 0)) अणु
		ret = -EINVAL;
		जाओ ret_unlock;
	पूर्ण

	अगर (cxdev->खोलो_type == CXUSB_OPEN_INIT) अणु
		ret = -EAGAIN;
		जाओ ret_unlock;
	पूर्ण

	अगर (cxdev->खोलो_ctr == 0) अणु
		अगर (cxdev->खोलो_type != खोलो_type) अणु
			dev_info(&dvbdev->udev->dev, "will acquire and switch to %s\n",
				 खोलो_type == CXUSB_OPEN_ANALOG ?
				 "analog" : "digital");

			अगर (खोलो_type == CXUSB_OPEN_ANALOG) अणु
				ret = _cxusb_घातer_ctrl(dvbdev, 1);
				अगर (ret != 0)
					dev_warn(&dvbdev->udev->dev,
						 "powerup for analog switch failed (%d)\n",
						 ret);

				ret = cxusb_medion_set_mode(dvbdev, false);
				अगर (ret != 0)
					जाओ ret_unlock;

				ret = cxusb_medion_analog_init(dvbdev);
				अगर (ret != 0)
					जाओ ret_unlock;
			पूर्ण अन्यथा अणु /* digital */
				ret = _cxusb_घातer_ctrl(dvbdev, 1);
				अगर (ret != 0)
					dev_warn(&dvbdev->udev->dev,
						 "powerup for digital switch failed (%d)\n",
						 ret);

				ret = cxusb_medion_set_mode(dvbdev, true);
				अगर (ret != 0)
					जाओ ret_unlock;
			पूर्ण

			cxdev->खोलो_type = खोलो_type;
		पूर्ण अन्यथा अणु
			dev_info(&dvbdev->udev->dev, "reacquired idle %s\n",
				 खोलो_type == CXUSB_OPEN_ANALOG ?
				 "analog" : "digital");
		पूर्ण

		cxdev->खोलो_ctr = 1;
	पूर्ण अन्यथा अगर (cxdev->खोलो_type == खोलो_type) अणु
		cxdev->खोलो_ctr++;
		dev_info(&dvbdev->udev->dev, "acquired %s\n",
			 खोलो_type == CXUSB_OPEN_ANALOG ? "analog" : "digital");
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण

ret_unlock:
	mutex_unlock(&cxdev->खोलो_lock);

	वापस ret;
पूर्ण

व्योम cxusb_medion_put(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	mutex_lock(&cxdev->खोलो_lock);

	अगर (cxdev->खोलो_type == CXUSB_OPEN_INIT) अणु
		WARN_ON(cxdev->खोलो_ctr != 0);
		cxdev->खोलो_type = CXUSB_OPEN_NONE;
		जाओ unlock;
	पूर्ण

	अगर (!WARN_ON(cxdev->खोलो_ctr < 1)) अणु
		cxdev->खोलो_ctr--;

		dev_info(&dvbdev->udev->dev, "release %s\n",
			 cxdev->खोलो_type == CXUSB_OPEN_ANALOG ?
			 "analog" : "digital");
	पूर्ण

unlock:
	mutex_unlock(&cxdev->खोलो_lock);
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties cxusb_medion_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_lgh064f_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dee1601_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_lgz201_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dtt7579_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dualdig4_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dualdig4_rev2_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_nano2_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_nano2_needsfirmware_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_aver_a868r_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_d680_dmb_properties;
अटल काष्ठा dvb_usb_device_properties cxusb_mygica_d689_properties;

अटल पूर्णांक cxusb_medion_priv_init(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	cxdev->dvbdev = dvbdev;
	cxdev->खोलो_type = CXUSB_OPEN_INIT;
	mutex_init(&cxdev->खोलो_lock);

	वापस 0;
पूर्ण

अटल व्योम cxusb_medion_priv_destroy(काष्ठा dvb_usb_device *dvbdev)
अणु
	काष्ठा cxusb_medion_dev *cxdev = dvbdev->priv;

	mutex_destroy(&cxdev->खोलो_lock);
पूर्ण

अटल bool cxusb_medion_check_altsetting(काष्ठा usb_host_पूर्णांकerface *as)
अणु
	अचिन्हित पूर्णांक ctr;

	क्रम (ctr = 0; ctr < as->desc.bNumEndpoपूर्णांकs; ctr++) अणु
		अगर ((as->endpoपूर्णांक[ctr].desc.bEndpoपूर्णांकAddress &
		     USB_ENDPOINT_NUMBER_MASK) != 2)
			जारी;

		अगर (as->endpoपूर्णांक[ctr].desc.bEndpoपूर्णांकAddress & USB_सूची_IN &&
		    ((as->endpoपूर्णांक[ctr].desc.bmAttributes &
		      USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_ISOC))
			वापस true;

		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool cxusb_medion_check_पूर्णांकf(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अचिन्हित पूर्णांक ctr;

	अगर (पूर्णांकf->num_altsetting < 2) अणु
		dev_err(पूर्णांकf->usb_dev, "no alternate interface");

		वापस false;
	पूर्ण

	क्रम (ctr = 0; ctr < पूर्णांकf->num_altsetting; ctr++) अणु
		अगर (पूर्णांकf->altsetting[ctr].desc.bAlternateSetting != 1)
			जारी;

		अगर (cxusb_medion_check_altsetting(&पूर्णांकf->altsetting[ctr]))
			वापस true;

		अवरोध;
	पूर्ण

	dev_err(पूर्णांकf->usb_dev, "no iso interface");

	वापस false;
पूर्ण

अटल पूर्णांक cxusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dvb_usb_device *dvbdev;
	पूर्णांक ret;

	/* Medion 95700 */
	अगर (!dvb_usb_device_init(पूर्णांकf, &cxusb_medion_properties,
				 THIS_MODULE, &dvbdev, adapter_nr)) अणु
		अगर (!cxusb_medion_check_पूर्णांकf(पूर्णांकf)) अणु
			ret = -ENODEV;
			जाओ ret_uninit;
		पूर्ण

		_cxusb_घातer_ctrl(dvbdev, 1);
		ret = cxusb_medion_set_mode(dvbdev, false);
		अगर (ret)
			जाओ ret_uninit;

		ret = cxusb_medion_रेजिस्टर_analog(dvbdev);

		cxusb_medion_set_mode(dvbdev, true);
		_cxusb_घातer_ctrl(dvbdev, 0);

		अगर (ret != 0)
			जाओ ret_uninit;

		/* release device from INIT mode to normal operation */
		cxusb_medion_put(dvbdev);

		वापस 0;
	पूर्ण अन्यथा अगर (!dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_lgh064f_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_dee1601_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_lgz201_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_dtt7579_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_dualdig4_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_nano2_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_nano2_needsfirmware_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf, &cxusb_aver_a868r_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf,
					&cxusb_bluebird_dualdig4_rev2_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf, &cxusb_d680_dmb_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   !dvb_usb_device_init(पूर्णांकf, &cxusb_mygica_d689_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
		   0)
		वापस 0;

	वापस -EINVAL;

ret_uninit:
	dvb_usb_device_निकास(पूर्णांकf);

	वापस ret;
पूर्ण

अटल व्योम cxusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा cxusb_state *st = d->priv;
	काष्ठा i2c_client *client;

	अगर (d->props.devices[0].warm_ids[0] == &cxusb_table[MEDION_MD95700])
		cxusb_medion_unरेजिस्टर_analog(d);

	/* हटाओ I2C client क्रम tuner */
	client = st->i2c_client_tuner;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम demodulator */
	client = st->i2c_client_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_device_id cxusb_table[NR__cxusb_table_index + 1] = अणु
	[MEDION_MD95700] = अणु
		USB_DEVICE(USB_VID_MEDION, USB_PID_MEDION_MD95700)
	पूर्ण,
	[DVICO_BLUEBIRD_LG064F_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_LG064F_COLD)
	पूर्ण,
	[DVICO_BLUEBIRD_LG064F_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_LG064F_WARM)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_1_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_1_COLD)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_1_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_1_WARM)
	पूर्ण,
	[DVICO_BLUEBIRD_LGZ201_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_LGZ201_COLD)
	पूर्ण,
	[DVICO_BLUEBIRD_LGZ201_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_LGZ201_WARM)
	पूर्ण,
	[DVICO_BLUEBIRD_TH7579_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_TH7579_COLD)
	पूर्ण,
	[DVICO_BLUEBIRD_TH7579_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_TH7579_WARM)
	पूर्ण,
	[DIGITALNOW_BLUEBIRD_DUAL_1_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO,
			   USB_PID_DIGITALNOW_BLUEBIRD_DUAL_1_COLD)
	पूर्ण,
	[DIGITALNOW_BLUEBIRD_DUAL_1_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO,
			   USB_PID_DIGITALNOW_BLUEBIRD_DUAL_1_WARM)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_2_COLD] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_2_COLD)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_2_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_2_WARM)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_4] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_4)
	पूर्ण,
	[DVICO_BLUEBIRD_DVB_T_न_अंकO_2] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DVB_T_न_अंकO_2)
	पूर्ण,
	[DVICO_BLUEBIRD_DVB_T_न_अंकO_2_NFW_WARM] = अणु
		USB_DEVICE(USB_VID_DVICO,
			   USB_PID_DVICO_BLUEBIRD_DVB_T_न_अंकO_2_NFW_WARM)
	पूर्ण,
	[AVERMEDIA_VOLAR_A868R] = अणु
		USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_VOLAR_A868R)
	पूर्ण,
	[DVICO_BLUEBIRD_DUAL_4_REV_2] = अणु
		USB_DEVICE(USB_VID_DVICO, USB_PID_DVICO_BLUEBIRD_DUAL_4_REV_2)
	पूर्ण,
	[CONEXANT_D680_DMB] = अणु
		USB_DEVICE(USB_VID_CONEXANT, USB_PID_CONEXANT_D680_DMB)
	पूर्ण,
	[MYGICA_D689] = अणु
		USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_D689)
	पूर्ण,
	अणुपूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, cxusb_table);

अटल काष्ठा dvb_usb_device_properties cxusb_medion_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_medion_dev),
	.priv_init        = cxusb_medion_priv_init,
	.priv_destroy     = cxusb_medion_priv_destroy,

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_cx22702_frontend_attach,
			.tuner_attach     = cxusb_fmd1216me_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
					.stream = अणु
						.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,
	.घातer_ctrl       = cxusb_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु
			"Medion MD95700 (MDUSBTV-HYBRID)",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[MEDION_MD95700], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_lgh064f_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = DEVICE_SPECIFIC,
	.firmware          = "dvb-usb-bluebird-01.fw",
	.करोwnload_firmware = bluebird_patch_dvico_firmware_करोwnload,
	/*
	 * use usb alt setting 0 क्रम EP4 transfer (dvb-t),
	 * use usb alt setting 7 क्रम EP2 transfer (atsc)
	 */

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_lgdt3303_frontend_attach,
			.tuner_attach     = cxusb_lgh064f_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
					.stream = अणु
						.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_bluebird_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_PORTABLE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV5 USB Gold",
			अणु &cxusb_table[DVICO_BLUEBIRD_LG064F_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_LG064F_WARM], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dee1601_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = DEVICE_SPECIFIC,
	.firmware          = "dvb-usb-bluebird-01.fw",
	.करोwnload_firmware = bluebird_patch_dvico_firmware_करोwnload,
	/*
	 * use usb alt setting 0 क्रम EP4 transfer (dvb-t),
	 * use usb alt setting 7 क्रम EP2 transfer (atsc)
	 */

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_dee1601_frontend_attach,
			.tuner_attach     = cxusb_dee1601_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x04,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_bluebird_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_MCE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 3,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T Dual USB",
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_1_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_1_WARM], शून्य पूर्ण,
		पूर्ण,
		अणु   "DigitalNow DVB-T Dual USB",
			अणु &cxusb_table[DIGITALNOW_BLUEBIRD_DUAL_1_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DIGITALNOW_BLUEBIRD_DUAL_1_WARM], शून्य पूर्ण,
		पूर्ण,
		अणु   "DViCO FusionHDTV DVB-T Dual Digital 2",
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_2_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_2_WARM], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_lgz201_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = DEVICE_SPECIFIC,
	.firmware          = "dvb-usb-bluebird-01.fw",
	.करोwnload_firmware = bluebird_patch_dvico_firmware_करोwnload,
	/*
	 * use usb alt setting 0 क्रम EP4 transfer (dvb-t),
	 * use usb alt setting 7 क्रम EP2 transfer (atsc)
	 */

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 2,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_mt352_frontend_attach,
			.tuner_attach     = cxusb_lgz201_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x04,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,
	.घातer_ctrl       = cxusb_bluebird_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_PORTABLE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T USB (LGZ201)",
			अणु &cxusb_table[DVICO_BLUEBIRD_LGZ201_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_LGZ201_WARM], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dtt7579_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = DEVICE_SPECIFIC,
	.firmware          = "dvb-usb-bluebird-01.fw",
	.करोwnload_firmware = bluebird_patch_dvico_firmware_करोwnload,

	/*
	 * use usb alt setting 0 क्रम EP4 transfer (dvb-t),
	 * use usb alt setting 7 क्रम EP2 transfer (atsc)
	 */

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_mt352_frontend_attach,
			.tuner_attach     = cxusb_dtt7579_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x04,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,
	.घातer_ctrl       = cxusb_bluebird_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_PORTABLE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T USB (TH7579)",
			अणु &cxusb_table[DVICO_BLUEBIRD_TH7579_COLD], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_TH7579_WARM], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_dualdig4_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_dualdig4_frontend_attach,
			.tuner_attach     = cxusb_dvico_xc3028_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_MCE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_bluebird2_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T Dual Digital 4",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_4], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_bluebird_nano2_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,
	.identअगरy_state   = bluebird_fx2_identअगरy_state,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_nano2_frontend_attach,
			.tuner_attach     = cxusb_dvico_xc3028_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_nano2_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_PORTABLE,
		.module_name	= KBUILD_MODNAME,
		.rc_query       = cxusb_bluebird2_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T NANO2",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DVB_T_न_अंकO_2], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties
cxusb_bluebird_nano2_needsfirmware_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl          = DEVICE_SPECIFIC,
	.firmware          = "dvb-usb-bluebird-02.fw",
	.करोwnload_firmware = bluebird_patch_dvico_firmware_करोwnload,
	.identअगरy_state    = bluebird_fx2_identअगरy_state,

	.size_of_priv      = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_streaming_ctrl,
			.frontend_attach  = cxusb_nano2_frontend_attach,
			.tuner_attach     = cxusb_dvico_xc3028_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_nano2_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_PORTABLE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु अणु
			"DViCO FusionHDTV DVB-T NANO2 w/o firmware",
			अणु &cxusb_table[DVICO_BLUEBIRD_DVB_T_न_अंकO_2], शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DVB_T_न_अंकO_2_NFW_WARM],
			  शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_aver_a868r_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_aver_streaming_ctrl,
			.frontend_attach  = cxusb_aver_lgdt3303_frontend_attach,
			.tuner_attach     = cxusb_mxl5003s_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x04,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,
	.घातer_ctrl       = cxusb_aver_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "AVerMedia AVerTVHD Volar (A868R)",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[AVERMEDIA_VOLAR_A868R], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल
काष्ठा dvb_usb_device_properties cxusb_bluebird_dualdig4_rev2_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.size_of_priv    = माप(काष्ठा dib0700_adapter_state),
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl  = cxusb_streaming_ctrl,
			.frontend_attach = cxusb_dualdig4_rev2_frontend_attach,
			.tuner_attach    = cxusb_dualdig4_rev2_tuner_attach,
			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 7,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_bluebird_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_DVICO_MCE,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= cxusb_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DViCO FusionHDTV DVB-T Dual Digital 4 (rev 2)",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[DVICO_BLUEBIRD_DUAL_4_REV_2], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_d680_dmb_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_d680_dmb_streaming_ctrl,
			.frontend_attach  = cxusb_d680_dmb_frontend_attach,
			.tuner_attach     = cxusb_d680_dmb_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_d680_dmb_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_TOTAL_MEDIA_IN_HAND_02,
		.module_name	= KBUILD_MODNAME,
		.rc_query       = cxusb_d680_dmb_rc_query,
		.allowed_protos = RC_PROTO_BIT_UNKNOWN,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु
			"Conexant DMB-TH Stick",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[CONEXANT_D680_DMB], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties cxusb_mygica_d689_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl         = CYPRESS_FX2,

	.size_of_priv     = माप(काष्ठा cxusb_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = cxusb_d680_dmb_streaming_ctrl,
			.frontend_attach  = cxusb_mygica_d689_frontend_attach,
			.tuner_attach     = cxusb_mygica_d689_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 8192,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = cxusb_d680_dmb_घातer_ctrl,

	.i2c_algo         = &cxusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 100,
		.rc_codes	= RC_MAP_D680_DMB,
		.module_name	= KBUILD_MODNAME,
		.rc_query       = cxusb_d680_dmb_rc_query,
		.allowed_protos = RC_PROTO_BIT_UNKNOWN,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु
			"Mygica D689 DMB-TH",
			अणु शून्य पूर्ण,
			अणु &cxusb_table[MYGICA_D689], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver cxusb_driver = अणु
	.name		= "dvb_usb_cxusb",
	.probe		= cxusb_probe,
	.disconnect     = cxusb_disconnect,
	.id_table	= cxusb_table,
पूर्ण;

module_usb_driver(cxusb_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_AUTHOR("Chris Pascoe <c.pascoe@itee.uq.edu.au>");
MODULE_AUTHOR("Maciej S. Szmigiero <mail@maciej.szmigiero.name>");
MODULE_DESCRIPTION("Driver for Conexant USB2.0 hybrid reference design");
MODULE_LICENSE("GPL");
