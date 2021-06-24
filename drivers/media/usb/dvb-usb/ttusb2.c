<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम Technotrend DVB USB boxes and clones
 * (e.g. Pinnacle 400e DVB-S USB2.0).
 *
 * The Pinnacle 400e uses the same protocol as the Technotrend USB1.1 boxes.
 *
 * TDA8263 + TDA10086
 *
 * I2C addresses:
 * 0x08 - LNBP21PD   - LNB घातer supply
 * 0x0e - TDA10086   - Demodulator
 * 0x50 - FX2 eeprom
 * 0x60 - TDA8263    - Tuner
 * 0x78 ???
 *
 * Copyright (c) 2002 Holger Waechtler <holger@convergence.de>
 * Copyright (c) 2003 Felix Domke <पंचांगbinc@elitedvb.net>
 * Copyright (C) 2005-6 Patrick Boettcher <pb@linuxtv.org>
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#घोषणा DVB_USB_LOG_PREFIX "ttusb2"
#समावेश "dvb-usb.h"

#समावेश "ttusb2.h"

#समावेश "tda826x.h"
#समावेश "tda10086.h"
#समावेश "tda1002x.h"
#समावेश "tda10048.h"
#समावेश "tda827x.h"
#समावेश "lnbp21.h"
/* CA */
#समावेश <media/dvb_ca_en50221.h>

/* debug */
अटल पूर्णांक dvb_usb_ttusb2_debug;
#घोषणा deb_info(args...)   dprपूर्णांकk(dvb_usb_ttusb2_debug,0x01,args)
module_param_named(debug,dvb_usb_ttusb2_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (or-able))." DVB_USB_DEBUG_STATUS);
अटल पूर्णांक dvb_usb_ttusb2_debug_ci;
module_param_named(debug_ci,dvb_usb_ttusb2_debug_ci, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_ci, "set debugging ci." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा ci_dbg(क्रमmat, arg...)                \
करो अणु                                          \
	अगर (dvb_usb_ttusb2_debug_ci)                                    \
		prपूर्णांकk(KERN_DEBUG DVB_USB_LOG_PREFIX \
			": %s " क्रमmat "\n" , __func__, ## arg);       \
पूर्ण जबतक (0)

क्रमागत अणु
	TT3650_CMD_CI_TEST = 0x40,
	TT3650_CMD_CI_RD_CTRL,
	TT3650_CMD_CI_WR_CTRL,
	TT3650_CMD_CI_RD_ATTR,
	TT3650_CMD_CI_WR_ATTR,
	TT3650_CMD_CI_RESET,
	TT3650_CMD_CI_SET_VIDEO_PORT
पूर्ण;

काष्ठा ttusb2_state अणु
	काष्ठा dvb_ca_en50221 ca;
	काष्ठा mutex ca_mutex;
	u8 id;
	u16 last_rc_key;
पूर्ण;

अटल पूर्णांक ttusb2_msg(काष्ठा dvb_usb_device *d, u8 cmd,
		u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा ttusb2_state *st = d->priv;
	u8 *s, *r = शून्य;
	पूर्णांक ret = 0;

	अगर (4 + rlen > 64)
		वापस -EIO;

	s = kzalloc(wlen+4, GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	r = kzalloc(64, GFP_KERNEL);
	अगर (!r) अणु
		kमुक्त(s);
		वापस -ENOMEM;
	पूर्ण

	s[0] = 0xaa;
	s[1] = ++st->id;
	s[2] = cmd;
	s[3] = wlen;
	स_नकल(&s[4],wbuf,wlen);

	ret = dvb_usb_generic_rw(d, s, wlen+4, r, 64, 0);

	अगर (ret  != 0 ||
		r[0] != 0x55 ||
		r[1] != s[1] ||
		r[2] != cmd ||
		(rlen > 0 && r[3] != rlen)) अणु
		warn("there might have been an error during control message transfer. (rlen = %d, was %d)",rlen,r[3]);
		kमुक्त(s);
		kमुक्त(r);
		वापस -EIO;
	पूर्ण

	अगर (rlen > 0)
		स_नकल(rbuf, &r[4], rlen);

	kमुक्त(s);
	kमुक्त(r);

	वापस 0;
पूर्ण

/* ci */
अटल पूर्णांक tt3650_ci_msg(काष्ठा dvb_usb_device *d, u8 cmd, u8 *data, अचिन्हित पूर्णांक ग_लिखो_len, अचिन्हित पूर्णांक पढ़ो_len)
अणु
	पूर्णांक ret;
	u8 rx[60];/* (64 -4) */
	ret = ttusb2_msg(d, cmd, data, ग_लिखो_len, rx, पढ़ो_len);
	अगर (!ret)
		स_नकल(data, rx, पढ़ो_len);
	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_msg_locked(काष्ठा dvb_ca_en50221 *ca, u8 cmd, u8 *data, अचिन्हित पूर्णांक ग_लिखो_len, अचिन्हित पूर्णांक पढ़ो_len)
अणु
	काष्ठा dvb_usb_device *d = ca->data;
	काष्ठा ttusb2_state *state = d->priv;
	पूर्णांक ret;

	mutex_lock(&state->ca_mutex);
	ret = tt3650_ci_msg(d, cmd, data, ग_लिखो_len, पढ़ो_len);
	mutex_unlock(&state->ca_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address)
अणु
	u8 buf[3];
	पूर्णांक ret = 0;

	अगर (slot)
		वापस -EINVAL;

	buf[0] = (address >> 8) & 0x0F;
	buf[1] = address;


	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_RD_ATTR, buf, 2, 3);

	ci_dbg("%04x -> %d 0x%02x", address, ret, buf[2]);

	अगर (ret < 0)
		वापस ret;

	वापस buf[2];
पूर्ण

अटल पूर्णांक tt3650_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक address, u8 value)
अणु
	u8 buf[3];

	ci_dbg("%d 0x%04x 0x%02x", slot, address, value);

	अगर (slot)
		वापस -EINVAL;

	buf[0] = (address >> 8) & 0x0F;
	buf[1] = address;
	buf[2] = value;

	वापस tt3650_ci_msg_locked(ca, TT3650_CMD_CI_WR_ATTR, buf, 3, 3);
पूर्ण

अटल पूर्णांक tt3650_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address)
अणु
	u8 buf[2];
	पूर्णांक ret;

	अगर (slot)
		वापस -EINVAL;

	buf[0] = address & 3;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_RD_CTRL, buf, 1, 2);

	ci_dbg("0x%02x -> %d 0x%02x", address, ret, buf[1]);

	अगर (ret < 0)
		वापस ret;

	वापस buf[1];
पूर्ण

अटल पूर्णांक tt3650_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 address, u8 value)
अणु
	u8 buf[2];

	ci_dbg("%d 0x%02x 0x%02x", slot, address, value);

	अगर (slot)
		वापस -EINVAL;

	buf[0] = address;
	buf[1] = value;

	वापस tt3650_ci_msg_locked(ca, TT3650_CMD_CI_WR_CTRL, buf, 2, 2);
पूर्ण

अटल पूर्णांक tt3650_ci_set_video_port(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक enable)
अणु
	u8 buf[1];
	पूर्णांक ret;

	ci_dbg("%d %d", slot, enable);

	अगर (slot)
		वापस -EINVAL;

	buf[0] = enable;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_SET_VIDEO_PORT, buf, 1, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (enable != buf[0]) अणु
		err("CI not %sabled.", enable ? "en" : "dis");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tt3650_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस tt3650_ci_set_video_port(ca, slot, 0);
पूर्ण

अटल पूर्णांक tt3650_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस tt3650_ci_set_video_port(ca, slot, 1);
पूर्ण

अटल पूर्णांक tt3650_ci_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = ca->data;
	काष्ठा ttusb2_state *state = d->priv;
	u8 buf[1];
	पूर्णांक ret;

	ci_dbg("%d", slot);

	अगर (slot)
		वापस -EINVAL;

	buf[0] = 0;

	mutex_lock(&state->ca_mutex);

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_RESET, buf, 1, 1);
	अगर (ret)
		जाओ failed;

	msleep(500);

	buf[0] = 1;

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_RESET, buf, 1, 1);
	अगर (ret)
		जाओ failed;

	msleep(500);

	buf[0] = 0; /* FTA */

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_SET_VIDEO_PORT, buf, 1, 1);

	msleep(1100);

 failed:
	mutex_unlock(&state->ca_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	u8 buf[1];
	पूर्णांक ret;

	अगर (slot)
		वापस -EINVAL;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_TEST, buf, 0, 1);
	अगर (ret)
		वापस ret;

	अगर (1 == buf[0]) अणु
		वापस DVB_CA_EN50221_POLL_CAM_PRESENT |
			DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tt3650_ci_uninit(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा ttusb2_state *state;

	ci_dbg("");

	अगर (शून्य == d)
		वापस;

	state = d->priv;
	अगर (शून्य == state)
		वापस;

	अगर (शून्य == state->ca.data)
		वापस;

	dvb_ca_en50221_release(&state->ca);

	स_रखो(&state->ca, 0, माप(state->ca));
पूर्ण

अटल पूर्णांक tt3650_ci_init(काष्ठा dvb_usb_adapter *a)
अणु
	काष्ठा dvb_usb_device *d = a->dev;
	काष्ठा ttusb2_state *state = d->priv;
	पूर्णांक ret;

	ci_dbg("");

	mutex_init(&state->ca_mutex);

	state->ca.owner = THIS_MODULE;
	state->ca.पढ़ो_attribute_mem = tt3650_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem = tt3650_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control = tt3650_ci_पढ़ो_cam_control;
	state->ca.ग_लिखो_cam_control = tt3650_ci_ग_लिखो_cam_control;
	state->ca.slot_reset = tt3650_ci_slot_reset;
	state->ca.slot_shutकरोwn = tt3650_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable = tt3650_ci_slot_ts_enable;
	state->ca.poll_slot_status = tt3650_ci_poll_slot_status;
	state->ca.data = d;

	ret = dvb_ca_en50221_init(&a->dvb_adap,
				  &state->ca,
				  /* flags */ 0,
				  /* n_slots */ 1);
	अगर (ret) अणु
		err("Cannot initialize CI: Error %d.", ret);
		स_रखो(&state->ca, 0, माप(state->ca));
		वापस ret;
	पूर्ण

	info("CI initialized.");

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb2_i2c_xfer(काष्ठा i2c_adapter *adap,काष्ठा i2c_msg msg[],पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	अटल u8 obuf[60], ibuf[60];
	पूर्णांक i, ग_लिखो_पढ़ो, पढ़ो;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	अगर (num > 2)
		warn("more than 2 i2c messages at a time is not handled yet. TODO.");

	क्रम (i = 0; i < num; i++) अणु
		ग_लिखो_पढ़ो = i+1 < num && (msg[i+1].flags & I2C_M_RD);
		पढ़ो = msg[i].flags & I2C_M_RD;

		अगर (3 + msg[i].len > माप(obuf)) अणु
			err("i2c wr len=%d too high", msg[i].len);
			अवरोध;
		पूर्ण
		अगर (ग_लिखो_पढ़ो) अणु
			अगर (3 + msg[i+1].len > माप(ibuf)) अणु
				err("i2c rd len=%d too high", msg[i+1].len);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (पढ़ो) अणु
			अगर (3 + msg[i].len > माप(ibuf)) अणु
				err("i2c rd len=%d too high", msg[i].len);
				अवरोध;
			पूर्ण
		पूर्ण

		obuf[0] = (msg[i].addr << 1) | (ग_लिखो_पढ़ो | पढ़ो);
		अगर (पढ़ो)
			obuf[1] = 0;
		अन्यथा
			obuf[1] = msg[i].len;

		/* पढ़ो request */
		अगर (ग_लिखो_पढ़ो)
			obuf[2] = msg[i+1].len;
		अन्यथा अगर (पढ़ो)
			obuf[2] = msg[i].len;
		अन्यथा
			obuf[2] = 0;

		स_नकल(&obuf[3], msg[i].buf, msg[i].len);

		अगर (ttusb2_msg(d, CMD_I2C_XFER, obuf, obuf[1]+3, ibuf, obuf[2] + 3) < 0) अणु
			err("i2c transfer failed.");
			अवरोध;
		पूर्ण

		अगर (ग_लिखो_पढ़ो) अणु
			स_नकल(msg[i+1].buf, &ibuf[3], msg[i+1].len);
			i++;
		पूर्ण अन्यथा अगर (पढ़ो)
			स_नकल(msg[i].buf, &ibuf[3], msg[i].len);
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 ttusb2_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm ttusb2_i2c_algo = अणु
	.master_xfer   = ttusb2_i2c_xfer,
	.functionality = ttusb2_i2c_func,
पूर्ण;

/* command to poll IR receiver (copied from pctv452e.c) */
#घोषणा CMD_GET_IR_CODE     0x1b

/* IR */
अटल पूर्णांक tt3650_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	u8 rx[9]; /* A CMD_GET_IR_CODE reply is 9 bytes दीर्घ */
	काष्ठा ttusb2_state *st = d->priv;
	ret = ttusb2_msg(d, CMD_GET_IR_CODE, शून्य, 0, rx, माप(rx));
	अगर (ret != 0)
		वापस ret;

	अगर (rx[8] & 0x01) अणु
		/* got a "press" event */
		st->last_rc_key = RC_SCANCODE_RC5(rx[3], rx[2]);
		deb_info("%s: cmd=0x%02x sys=0x%02x\n", __func__, rx[2], rx[3]);
		rc_keyकरोwn(d->rc_dev, RC_PROTO_RC5, st->last_rc_key, rx[1]);
	पूर्ण अन्यथा अगर (st->last_rc_key) अणु
		rc_keyup(d->rc_dev);
		st->last_rc_key = 0;
	पूर्ण

	वापस 0;
पूर्ण


/* Callbacks क्रम DVB USB */
अटल पूर्णांक ttusb2_identअगरy_state(काष्ठा usb_device *udev,
				 स्थिर काष्ठा dvb_usb_device_properties *props,
				 स्थिर काष्ठा dvb_usb_device_description **desc,
				 पूर्णांक *cold)
अणु
	*cold = udev->descriptor.iManufacturer == 0 && udev->descriptor.iProduct == 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ttusb2_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 b = onoff;
	ttusb2_msg(d, CMD_POWER, &b, 0, शून्य, 0);
	वापस ttusb2_msg(d, CMD_POWER, &b, 1, शून्य, 0);
पूर्ण


अटल काष्ठा tda10086_config tda10086_config = अणु
	.demod_address = 0x0e,
	.invert = 0,
	.diseqc_tone = 1,
	.xtal_freq = TDA10086_XTAL_16M,
पूर्ण;

अटल काष्ठा tda10023_config tda10023_config = अणु
	.demod_address = 0x0c,
	.invert = 0,
	.xtal = 16000000,
	.pll_m = 11,
	.pll_p = 3,
	.pll_n = 1,
	.deltaf = 0xa511,
पूर्ण;

अटल काष्ठा tda10048_config tda10048_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_PARALLEL_OUTPUT,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_4000,
	.dtv7_अगर_freq_khz = TDA10048_IF_4500,
	.dtv8_अगर_freq_khz = TDA10048_IF_5000,
	.clk_freq_khz     = TDA10048_CLK_16000,
	.no_firmware      = 1,
	.set_pll          = true ,
	.pll_m            = 5,
	.pll_n            = 3,
	.pll_p            = 0,
पूर्ण;

अटल काष्ठा tda827x_config tda827x_config = अणु
	.config = 0,
पूर्ण;

अटल पूर्णांक ttusb2_frontend_tda10086_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (usb_set_पूर्णांकerface(adap->dev->udev,0,3) < 0)
		err("set interface to alts=3 failed");

	अगर ((adap->fe_adap[0].fe = dvb_attach(tda10086_attach, &tda10086_config, &adap->dev->i2c_adap)) == शून्य) अणु
		deb_info("TDA10086 attach failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb2_ct3650_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;

	वापस adap->fe_adap[0].fe->ops.i2c_gate_ctrl(adap->fe_adap[0].fe, enable);
पूर्ण

अटल पूर्णांक ttusb2_frontend_tda10023_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (usb_set_पूर्णांकerface(adap->dev->udev, 0, 3) < 0)
		err("set interface to alts=3 failed");

	अगर (adap->fe_adap[0].fe == शून्य) अणु
		/* FE 0 DVB-C */
		adap->fe_adap[0].fe = dvb_attach(tda10023_attach,
			&tda10023_config, &adap->dev->i2c_adap, 0x48);

		अगर (adap->fe_adap[0].fe == शून्य) अणु
			deb_info("TDA10023 attach failed\n");
			वापस -ENODEV;
		पूर्ण
		tt3650_ci_init(adap);
	पूर्ण अन्यथा अणु
		adap->fe_adap[1].fe = dvb_attach(tda10048_attach,
			&tda10048_config, &adap->dev->i2c_adap);

		अगर (adap->fe_adap[1].fe == शून्य) अणु
			deb_info("TDA10048 attach failed\n");
			वापस -ENODEV;
		पूर्ण

		/* tuner is behind TDA10023 I2C-gate */
		adap->fe_adap[1].fe->ops.i2c_gate_ctrl = ttusb2_ct3650_i2c_gate_ctrl;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb2_tuner_tda827x_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_frontend *fe;

	/* MFE: select correct FE to attach tuner since that's called twice */
	अगर (adap->fe_adap[1].fe == शून्य)
		fe = adap->fe_adap[0].fe;
	अन्यथा
		fe = adap->fe_adap[1].fe;

	/* attach tuner */
	अगर (dvb_attach(tda827x_attach, fe, 0x61, &adap->dev->i2c_adap, &tda827x_config) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: No tda827x found!\n", __func__);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ttusb2_tuner_tda826x_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (dvb_attach(tda826x_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap, 0) == शून्य) अणु
		deb_info("TDA8263 attach failed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dvb_attach(lnbp21_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap, 0, 0) == शून्य) अणु
		deb_info("LNBP21 attach failed\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties ttusb2_properties;
अटल काष्ठा dvb_usb_device_properties ttusb2_properties_s2400;
अटल काष्ठा dvb_usb_device_properties ttusb2_properties_ct3650;

अटल व्योम ttusb2_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);

	tt3650_ci_uninit(d);
	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण

अटल पूर्णांक ttusb2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (0 == dvb_usb_device_init(पूर्णांकf, &ttusb2_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &ttusb2_properties_s2400,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &ttusb2_properties_ct3650,
				     THIS_MODULE, शून्य, adapter_nr))
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल काष्ठा usb_device_id ttusb2_table [] = अणु
	अणु USB_DEVICE(USB_VID_PINNACLE, USB_PID_PCTV_400E) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE, USB_PID_PCTV_450E) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_S2400) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_CT3650) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_S2400_8KEEPROM) पूर्ण,
	अणुपूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, ttusb2_table);

अटल काष्ठा dvb_usb_device_properties ttusb2_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-pctv-400e-01.fw",

	.size_of_priv = माप(काष्ठा ttusb2_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = शून्य, // ttusb2_streaming_ctrl,

			.frontend_attach  = ttusb2_frontend_tda10086_attach,
			.tuner_attach     = ttusb2_tuner_tda826x_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_ISOC,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 4,
						.framesize = 940,
						.पूर्णांकerval = 1,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,

	.घातer_ctrl       = ttusb2_घातer_ctrl,
	.identअगरy_state   = ttusb2_identअगरy_state,

	.i2c_algo         = &ttusb2_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 2,
	.devices = अणु
		अणु   "Pinnacle 400e DVB-S USB2.0",
			अणु &ttusb2_table[0], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु   "Pinnacle 450e DVB-S USB2.0",
			अणु &ttusb2_table[1], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties ttusb2_properties_s2400 = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-tt-s2400-01.fw",

	.size_of_priv = माप(काष्ठा ttusb2_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = शून्य,

			.frontend_attach  = ttusb2_frontend_tda10086_attach,
			.tuner_attach     = ttusb2_tuner_tda826x_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_ISOC,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 4,
						.framesize = 940,
						.पूर्णांकerval = 1,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,

	.घातer_ctrl       = ttusb2_घातer_ctrl,
	.identअगरy_state   = ttusb2_identअगरy_state,

	.i2c_algo         = &ttusb2_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 2,
	.devices = अणु
		अणु   "Technotrend TT-connect S-2400",
			अणु &ttusb2_table[2], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु   "Technotrend TT-connect S-2400 (8kB EEPROM)",
			अणु &ttusb2_table[4], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties ttusb2_properties_ct3650 = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,

	.size_of_priv = माप(काष्ठा ttusb2_state),

	.rc.core = अणु
		.rc_पूर्णांकerval      = 150, /* Less than IR_KEYPRESS_TIMEOUT */
		.rc_codes         = RC_MAP_TT_1500,
		.rc_query         = tt3650_rc_query,
		.allowed_protos   = RC_PROTO_BIT_RC5,
	पूर्ण,

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 2,
		.fe = अणुअणु
			.streaming_ctrl   = शून्य,

			.frontend_attach  = ttusb2_frontend_tda10023_attach,
			.tuner_attach = ttusb2_tuner_tda827x_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_ISOC,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 4,
						.framesize = 940,
						.पूर्णांकerval = 1,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण, अणु
			.streaming_ctrl   = शून्य,

			.frontend_attach  = ttusb2_frontend_tda10023_attach,
			.tuner_attach = ttusb2_tuner_tda827x_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_ISOC,
				.count = 5,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 4,
						.framesize = 940,
						.पूर्णांकerval = 1,
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = ttusb2_घातer_ctrl,
	.identअगरy_state   = ttusb2_identअगरy_state,

	.i2c_algo         = &ttusb2_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "Technotrend TT-connect CT-3650",
			.warm_ids = अणु &ttusb2_table[3], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver ttusb2_driver = अणु
	.name		= "dvb_usb_ttusb2",
	.probe		= ttusb2_probe,
	.disconnect	= ttusb2_usb_disconnect,
	.id_table	= ttusb2_table,
पूर्ण;

module_usb_driver(ttusb2_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for Pinnacle PCTV 400e DVB-S USB2.0");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
