<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम Nebula Electronics uDigiTV DVB-T USB2.0
 * receiver
 *
 * Copyright (C) 2005 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * partly based on the SDK published by Nebula Electronics
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "digitv.h"

#समावेश "mt352.h"
#समावेश "nxt6000.h"

/* debug */
अटल पूर्णांक dvb_usb_digitv_debug;
module_param_named(debug,dvb_usb_digitv_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=rc (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा deb_rc(args...)   dprपूर्णांकk(dvb_usb_digitv_debug,0x01,args)

अटल पूर्णांक digitv_ctrl_msg(काष्ठा dvb_usb_device *d,
		u8 cmd, u8 vv, u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा digitv_state *st = d->priv;
	पूर्णांक ret, wo;

	wo = (rbuf == शून्य || rlen == 0); /* ग_लिखो-only */

	अगर (wlen > 4 || rlen > 4)
		वापस -EIO;

	स_रखो(st->sndbuf, 0, 7);
	स_रखो(st->rcvbuf, 0, 7);

	st->sndbuf[0] = cmd;
	st->sndbuf[1] = vv;
	st->sndbuf[2] = wo ? wlen : rlen;

	अगर (wo) अणु
		स_नकल(&st->sndbuf[3], wbuf, wlen);
		ret = dvb_usb_generic_ग_लिखो(d, st->sndbuf, 7);
	पूर्ण अन्यथा अणु
		ret = dvb_usb_generic_rw(d, st->sndbuf, 7, st->rcvbuf, 7, 10);
		स_नकल(rbuf, &st->rcvbuf[3], rlen);
	पूर्ण
	वापस ret;
पूर्ण

/* I2C */
अटल पूर्णांक digitv_i2c_xfer(काष्ठा i2c_adapter *adap,काष्ठा i2c_msg msg[],पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	अगर (num > 2)
		warn("more than 2 i2c messages at a time is not handled yet. TODO.");

	क्रम (i = 0; i < num; i++) अणु
		/* ग_लिखो/पढ़ो request */
		अगर (i+1 < num && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (digitv_ctrl_msg(d, USB_READ_COFDM, msg[i].buf[0], शून्य, 0,
						msg[i+1].buf,msg[i+1].len) < 0)
				अवरोध;
			i++;
		पूर्ण अन्यथा
			अगर (digitv_ctrl_msg(d,USB_WRITE_COFDM, msg[i].buf[0],
						&msg[i].buf[1],msg[i].len-1,शून्य,0) < 0)
				अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 digitv_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm digitv_i2c_algo = अणु
	.master_xfer   = digitv_i2c_xfer,
	.functionality = digitv_i2c_func,
पूर्ण;

/* Callbacks क्रम DVB USB */
अटल पूर्णांक digitv_identअगरy_state(काष्ठा usb_device *udev,
				 स्थिर काष्ठा dvb_usb_device_properties *props,
				 स्थिर काष्ठा dvb_usb_device_description **desc,
				 पूर्णांक *cold)
अणु
	*cold = udev->descriptor.iManufacturer == 0 && udev->descriptor.iProduct == 0;
	वापस 0;
पूर्ण

अटल पूर्णांक digitv_mt352_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 reset_buf[] = अणु 0x89, 0x38,  0x8a, 0x2d, 0x50, 0x80 पूर्ण;
	अटल u8 init_buf[] = अणु 0x68, 0xa0,  0x8e, 0x40,  0x53, 0x50,
			0x67, 0x20,  0x7d, 0x01,  0x7c, 0x00,  0x7a, 0x00,
			0x79, 0x20,  0x57, 0x05,  0x56, 0x31,  0x88, 0x0f,
			0x75, 0x32 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reset_buf); i += 2)
		mt352_ग_लिखो(fe, &reset_buf[i], 2);

	msleep(1);

	क्रम (i = 0; i < ARRAY_SIZE(init_buf); i += 2)
		mt352_ग_लिखो(fe, &init_buf[i], 2);

	वापस 0;
पूर्ण

अटल काष्ठा mt352_config digitv_mt352_config = अणु
	.demod_init = digitv_mt352_demod_init,
पूर्ण;

अटल पूर्णांक digitv_nxt6000_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	u8 b[5];

	fe->ops.tuner_ops.calc_regs(fe, b, माप(b));
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	वापस digitv_ctrl_msg(adap->dev, USB_WRITE_TUNER, 0, &b[1], 4, शून्य, 0);
पूर्ण

अटल काष्ठा nxt6000_config digitv_nxt6000_config = अणु
	.घड़ी_inversion = 1,
पूर्ण;

अटल पूर्णांक digitv_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा digitv_state *st = adap->dev->priv;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &digitv_mt352_config,
					 &adap->dev->i2c_adap);
	अगर ((adap->fe_adap[0].fe) != शून्य) अणु
		st->is_nxt6000 = 0;
		वापस 0;
	पूर्ण
	adap->fe_adap[0].fe = dvb_attach(nxt6000_attach,
					 &digitv_nxt6000_config,
					 &adap->dev->i2c_adap);
	अगर ((adap->fe_adap[0].fe) != शून्य) अणु
		st->is_nxt6000 = 1;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक digitv_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा digitv_state *st = adap->dev->priv;

	अगर (!dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60, शून्य, DVB_PLL_TDED4))
		वापस -ENODEV;

	अगर (st->is_nxt6000)
		adap->fe_adap[0].fe->ops.tuner_ops.set_params = digitv_nxt6000_tuner_set_params;

	वापस 0;
पूर्ण

अटल काष्ठा rc_map_table rc_map_digitv_table[] = अणु
	अणु 0x5f55, KEY_0 पूर्ण,
	अणु 0x6f55, KEY_1 पूर्ण,
	अणु 0x9f55, KEY_2 पूर्ण,
	अणु 0xaf55, KEY_3 पूर्ण,
	अणु 0x5f56, KEY_4 पूर्ण,
	अणु 0x6f56, KEY_5 पूर्ण,
	अणु 0x9f56, KEY_6 पूर्ण,
	अणु 0xaf56, KEY_7 पूर्ण,
	अणु 0x5f59, KEY_8 पूर्ण,
	अणु 0x6f59, KEY_9 पूर्ण,
	अणु 0x9f59, KEY_TV पूर्ण,
	अणु 0xaf59, KEY_AUX पूर्ण,
	अणु 0x5f5a, KEY_DVD पूर्ण,
	अणु 0x6f5a, KEY_POWER पूर्ण,
	अणु 0x9f5a, KEY_CAMERA पूर्ण,     /* labelled 'Picture' */
	अणु 0xaf5a, KEY_AUDIO पूर्ण,
	अणु 0x5f65, KEY_INFO पूर्ण,
	अणु 0x6f65, KEY_F13 पूर्ण,     /* 16:9 */
	अणु 0x9f65, KEY_F14 पूर्ण,     /* 14:9 */
	अणु 0xaf65, KEY_EPG पूर्ण,
	अणु 0x5f66, KEY_EXIT पूर्ण,
	अणु 0x6f66, KEY_MENU पूर्ण,
	अणु 0x9f66, KEY_UP पूर्ण,
	अणु 0xaf66, KEY_DOWN पूर्ण,
	अणु 0x5f69, KEY_LEFT पूर्ण,
	अणु 0x6f69, KEY_RIGHT पूर्ण,
	अणु 0x9f69, KEY_ENTER पूर्ण,
	अणु 0xaf69, KEY_CHANNELUP पूर्ण,
	अणु 0x5f6a, KEY_CHANNELDOWN पूर्ण,
	अणु 0x6f6a, KEY_VOLUMEUP पूर्ण,
	अणु 0x9f6a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0xaf6a, KEY_RED पूर्ण,
	अणु 0x5f95, KEY_GREEN पूर्ण,
	अणु 0x6f95, KEY_YELLOW पूर्ण,
	अणु 0x9f95, KEY_BLUE पूर्ण,
	अणु 0xaf95, KEY_SUBTITLE पूर्ण,
	अणु 0x5f96, KEY_F15 पूर्ण,     /* AD */
	अणु 0x6f96, KEY_TEXT पूर्ण,
	अणु 0x9f96, KEY_MUTE पूर्ण,
	अणु 0xaf96, KEY_REWIND पूर्ण,
	अणु 0x5f99, KEY_STOP पूर्ण,
	अणु 0x6f99, KEY_PLAY पूर्ण,
	अणु 0x9f99, KEY_FASTFORWARD पूर्ण,
	अणु 0xaf99, KEY_F16 पूर्ण,     /* chapter */
	अणु 0x5f9a, KEY_PAUSE पूर्ण,
	अणु 0x6f9a, KEY_PLAY पूर्ण,
	अणु 0x9f9a, KEY_RECORD पूर्ण,
	अणु 0xaf9a, KEY_F17 पूर्ण,     /* picture in picture */
	अणु 0x5fa5, KEY_KPPLUS पूर्ण,  /* zoom in */
	अणु 0x6fa5, KEY_KPMINUS पूर्ण, /* zoom out */
	अणु 0x9fa5, KEY_F18 पूर्ण,     /* capture */
	अणु 0xafa5, KEY_F19 पूर्ण,     /* web */
	अणु 0x5fa6, KEY_EMAIL पूर्ण,
	अणु 0x6fa6, KEY_PHONE पूर्ण,
	अणु 0x9fa6, KEY_PC पूर्ण,
पूर्ण;

अटल पूर्णांक digitv_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
	काष्ठा rc_map_table *entry;
	पूर्णांक ret, i;
	u8 key[4];
	u8 b[4] = अणु 0 पूर्ण;

	*event = 0;
	*state = REMOTE_NO_KEY_PRESSED;

	ret = digitv_ctrl_msg(d, USB_READ_REMOTE, 0, शून्य, 0, key, 4);
	अगर (ret)
		वापस ret;

	/* Tell the device we've पढ़ो the remote. Not sure how necessary
	   this is, but the Nebula SDK करोes it. */
	ret = digitv_ctrl_msg(d, USB_WRITE_REMOTE, 0, b, 4, शून्य, 0);
	अगर (ret)
		वापस ret;

	/* अगर something is inside the buffer, simulate key press */
	अगर (key[0] != 0) अणु
		क्रम (i = 0; i < d->props.rc.legacy.rc_map_size; i++) अणु
			entry = &d->props.rc.legacy.rc_map_table[i];

			अगर (rc5_custom(entry) == key[0] &&
			    rc5_data(entry) == key[1]) अणु
				*event = entry->keycode;
				*state = REMOTE_KEY_PRESSED;
				वापस 0;
			पूर्ण
		पूर्ण

		deb_rc("key: %*ph\n", 4, key);
	पूर्ण

	वापस 0;
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties digitv_properties;

अटल पूर्णांक digitv_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dvb_usb_device *d;
	पूर्णांक ret = dvb_usb_device_init(पूर्णांकf, &digitv_properties, THIS_MODULE, &d,
				      adapter_nr);
	अगर (ret == 0) अणु
		u8 b[4] = अणु 0 पूर्ण;

		अगर (d != शून्य) अणु /* करो that only when the firmware is loaded */
			b[0] = 1;
			digitv_ctrl_msg(d,USB_WRITE_REMOTE_TYPE,0,b,4,शून्य,0);

			b[0] = 0;
			digitv_ctrl_msg(d,USB_WRITE_REMOTE,0,b,4,शून्य,0);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा usb_device_id digitv_table [] = अणु
		अणु USB_DEVICE(USB_VID_ANCHOR, USB_PID_NEBULA_DIGITV) पूर्ण,
		अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, digitv_table);

अटल काष्ठा dvb_usb_device_properties digitv_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-digitv-02.fw",

	.size_of_priv = माप(काष्ठा digitv_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach  = digitv_frontend_attach,
			.tuner_attach     = digitv_tuner_attach,

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
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
	.identअगरy_state   = digitv_identअगरy_state,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = 1000,
		.rc_map_table     = rc_map_digitv_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_digitv_table),
		.rc_query         = digitv_rc_query,
	पूर्ण,

	.i2c_algo         = &digitv_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "Nebula Electronics uDigiTV DVB-T USB2.0)",
			अणु &digitv_table[0], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver digitv_driver = अणु
	.name		= "dvb_usb_digitv",
	.probe		= digitv_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= digitv_table,
पूर्ण;

module_usb_driver(digitv_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for Nebula Electronics uDigiTV DVB-T USB2.0");
MODULE_VERSION("1.0-alpha");
MODULE_LICENSE("GPL");
