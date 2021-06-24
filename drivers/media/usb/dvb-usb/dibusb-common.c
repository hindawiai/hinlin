<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Common methods क्रम dibusb-based-receivers.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#समावेश "dibusb.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info (|-able))." DVB_USB_DEBUG_STATUS);
MODULE_LICENSE("GPL");

#घोषणा deb_info(args...) dprपूर्णांकk(debug,0x01,args)

/* common stuff used by the dअगरferent dibusb modules */
पूर्णांक dibusb_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	अगर (adap->priv != शून्य) अणु
		काष्ठा dibusb_state *st = adap->priv;
		अगर (st->ops.fअगरo_ctrl != शून्य)
			अगर (st->ops.fअगरo_ctrl(adap->fe_adap[0].fe, onoff)) अणु
				err("error while controlling the fifo of the demod.");
				वापस -ENODEV;
			पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dibusb_streaming_ctrl);

पूर्णांक dibusb_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid, पूर्णांक onoff)
अणु
	अगर (adap->priv != शून्य) अणु
		काष्ठा dibusb_state *st = adap->priv;
		अगर (st->ops.pid_ctrl != शून्य)
			st->ops.pid_ctrl(adap->fe_adap[0].fe,
					 index, pid, onoff);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dibusb_pid_filter);

पूर्णांक dibusb_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	अगर (adap->priv != शून्य) अणु
		काष्ठा dibusb_state *st = adap->priv;
		अगर (st->ops.pid_parse != शून्य)
			अगर (st->ops.pid_parse(adap->fe_adap[0].fe, onoff) < 0)
				err("could not handle pid_parser");
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dibusb_pid_filter_ctrl);

पूर्णांक dibusb_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 *b;
	पूर्णांक ret;

	b = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	b[0] = DIBUSB_REQ_SET_IOCTL;
	b[1] = DIBUSB_IOCTL_CMD_POWER_MODE;
	b[2] = onoff ? DIBUSB_IOCTL_POWER_WAKEUP : DIBUSB_IOCTL_POWER_SLEEP;

	ret = dvb_usb_generic_ग_लिखो(d, b, 3);

	kमुक्त(b);

	msleep(10);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dibusb_घातer_ctrl);

पूर्णांक dibusb2_0_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	u8 *b;

	b = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	अगर ((ret = dibusb_streaming_ctrl(adap,onoff)) < 0)
		जाओ ret;

	अगर (onoff) अणु
		b[0] = DIBUSB_REQ_SET_STREAMING_MODE;
		b[1] = 0x00;
		ret = dvb_usb_generic_ग_लिखो(adap->dev, b, 2);
		अगर (ret  < 0)
			जाओ ret;
	पूर्ण

	b[0] = DIBUSB_REQ_SET_IOCTL;
	b[1] = onoff ? DIBUSB_IOCTL_CMD_ENABLE_STREAM : DIBUSB_IOCTL_CMD_DISABLE_STREAM;
	ret = dvb_usb_generic_ग_लिखो(adap->dev, b, 3);

ret:
	kमुक्त(b);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dibusb2_0_streaming_ctrl);

पूर्णांक dibusb2_0_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 *b;
	पूर्णांक ret;

	अगर (!onoff)
		वापस 0;

	b = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	b[0] = DIBUSB_REQ_SET_IOCTL;
	b[1] = DIBUSB_IOCTL_CMD_POWER_MODE;
	b[2] = DIBUSB_IOCTL_POWER_WAKEUP;

	ret = dvb_usb_generic_ग_लिखो(d, b, 3);

	kमुक्त(b);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dibusb2_0_घातer_ctrl);

अटल पूर्णांक dibusb_i2c_msg(काष्ठा dvb_usb_device *d, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	u8 *sndbuf;
	पूर्णांक ret, wo, len;

	/* ग_लिखो only ? */
	wo = (rbuf == शून्य || rlen == 0);

	len = 2 + wlen + (wo ? 0 : 2);

	sndbuf = kदो_स्मृति(MAX_XFER_SIZE, GFP_KERNEL);
	अगर (!sndbuf)
		वापस -ENOMEM;

	अगर (4 + wlen > MAX_XFER_SIZE) अणु
		warn("i2c wr: len=%d is too big!\n", wlen);
		ret = -EOPNOTSUPP;
		जाओ ret;
	पूर्ण

	sndbuf[0] = wo ? DIBUSB_REQ_I2C_WRITE : DIBUSB_REQ_I2C_READ;
	sndbuf[1] = (addr << 1) | (wo ? 0 : 1);

	स_नकल(&sndbuf[2], wbuf, wlen);

	अगर (!wo) अणु
		sndbuf[wlen + 2] = (rlen >> 8) & 0xff;
		sndbuf[wlen + 3] = rlen & 0xff;
	पूर्ण

	ret = dvb_usb_generic_rw(d, sndbuf, len, rbuf, rlen, 0);

ret:
	kमुक्त(sndbuf);
	वापस ret;
पूर्ण

/*
 * I2C master xfer function
 */
अटल पूर्णांक dibusb_i2c_xfer(काष्ठा i2c_adapter *adap,काष्ठा i2c_msg msg[],पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		/* ग_लिखो/पढ़ो request */
		अगर (i+1 < num && (msg[i].flags & I2C_M_RD) == 0
					  && (msg[i+1].flags & I2C_M_RD)) अणु
			अगर (dibusb_i2c_msg(d, msg[i].addr, msg[i].buf,msg[i].len,
						msg[i+1].buf,msg[i+1].len) < 0)
				अवरोध;
			i++;
		पूर्ण अन्यथा अगर ((msg[i].flags & I2C_M_RD) == 0) अणु
			अगर (dibusb_i2c_msg(d, msg[i].addr, msg[i].buf,msg[i].len,शून्य,0) < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (msg[i].addr != 0x50) अणु
			/* 0x50 is the address of the eeprom - we need to protect it
			 * from dibusb's bad i2c implementation: पढ़ोs without
			 * writing the offset beक्रमe are क्रमbidden */
			अगर (dibusb_i2c_msg(d, msg[i].addr, शून्य, 0, msg[i].buf, msg[i].len) < 0)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 dibusb_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

काष्ठा i2c_algorithm dibusb_i2c_algo = अणु
	.master_xfer   = dibusb_i2c_xfer,
	.functionality = dibusb_i2c_func,
पूर्ण;
EXPORT_SYMBOL(dibusb_i2c_algo);

पूर्णांक dibusb_पढ़ो_eeprom_byte(काष्ठा dvb_usb_device *d, u8 offs, u8 *val)
अणु
	u8 *buf;
	पूर्णांक rc;

	buf = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = offs;

	rc = dibusb_i2c_msg(d, 0x50, &buf[0], 1, &buf[1], 1);
	*val = buf[1];
	kमुक्त(buf);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(dibusb_पढ़ो_eeprom_byte);

/*
 * common remote control stuff
 */
काष्ठा rc_map_table rc_map_dibusb_table[] = अणु
	/* Key codes क्रम the little Artec T1/Twinhan/HAMA/ remote. */
	अणु 0x0016, KEY_POWER पूर्ण,
	अणु 0x0010, KEY_MUTE पूर्ण,
	अणु 0x0003, KEY_1 पूर्ण,
	अणु 0x0001, KEY_2 पूर्ण,
	अणु 0x0006, KEY_3 पूर्ण,
	अणु 0x0009, KEY_4 पूर्ण,
	अणु 0x001d, KEY_5 पूर्ण,
	अणु 0x001f, KEY_6 पूर्ण,
	अणु 0x000d, KEY_7 पूर्ण,
	अणु 0x0019, KEY_8 पूर्ण,
	अणु 0x001b, KEY_9 पूर्ण,
	अणु 0x0015, KEY_0 पूर्ण,
	अणु 0x0005, KEY_CHANNELUP पूर्ण,
	अणु 0x0002, KEY_CHANNELDOWN पूर्ण,
	अणु 0x001e, KEY_VOLUMEUP पूर्ण,
	अणु 0x000a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0011, KEY_RECORD पूर्ण,
	अणु 0x0017, KEY_FAVORITES पूर्ण, /* Heart symbol - Channel list. */
	अणु 0x0014, KEY_PLAY पूर्ण,
	अणु 0x001a, KEY_STOP पूर्ण,
	अणु 0x0040, KEY_REWIND पूर्ण,
	अणु 0x0012, KEY_FASTFORWARD पूर्ण,
	अणु 0x000e, KEY_PREVIOUS पूर्ण, /* Recall - Previous channel. */
	अणु 0x004c, KEY_PAUSE पूर्ण,
	अणु 0x004d, KEY_SCREEN पूर्ण, /* Full screen mode. */
	अणु 0x0054, KEY_AUDIO पूर्ण, /* MTS - Switch to secondary audio. */
	/* additional keys TwinHan VisionPlus, the Artec seemingly not have */
	अणु 0x000c, KEY_CANCEL पूर्ण, /* Cancel */
	अणु 0x001c, KEY_EPG पूर्ण, /* EPG */
	अणु 0x0000, KEY_TAB पूर्ण, /* Tab */
	अणु 0x0048, KEY_INFO पूर्ण, /* Preview */
	अणु 0x0004, KEY_LIST पूर्ण, /* RecordList */
	अणु 0x000f, KEY_TEXT पूर्ण, /* Teletext */
	/* Key codes क्रम the KWorld/ADSTech/JetWay remote. */
	अणु 0x8612, KEY_POWER पूर्ण,
	अणु 0x860f, KEY_SELECT पूर्ण, /* source */
	अणु 0x860c, KEY_UNKNOWN पूर्ण, /* scan */
	अणु 0x860b, KEY_EPG पूर्ण,
	अणु 0x8610, KEY_MUTE पूर्ण,
	अणु 0x8601, KEY_1 पूर्ण,
	अणु 0x8602, KEY_2 पूर्ण,
	अणु 0x8603, KEY_3 पूर्ण,
	अणु 0x8604, KEY_4 पूर्ण,
	अणु 0x8605, KEY_5 पूर्ण,
	अणु 0x8606, KEY_6 पूर्ण,
	अणु 0x8607, KEY_7 पूर्ण,
	अणु 0x8608, KEY_8 पूर्ण,
	अणु 0x8609, KEY_9 पूर्ण,
	अणु 0x860a, KEY_0 पूर्ण,
	अणु 0x8618, KEY_ZOOM पूर्ण,
	अणु 0x861c, KEY_UNKNOWN पूर्ण, /* preview */
	अणु 0x8613, KEY_UNKNOWN पूर्ण, /* snap */
	अणु 0x8600, KEY_UNDO पूर्ण,
	अणु 0x861d, KEY_RECORD पूर्ण,
	अणु 0x860d, KEY_STOP पूर्ण,
	अणु 0x860e, KEY_PAUSE पूर्ण,
	अणु 0x8616, KEY_PLAY पूर्ण,
	अणु 0x8611, KEY_BACK पूर्ण,
	अणु 0x8619, KEY_FORWARD पूर्ण,
	अणु 0x8614, KEY_UNKNOWN पूर्ण, /* pip */
	अणु 0x8615, KEY_ESC पूर्ण,
	अणु 0x861a, KEY_UP पूर्ण,
	अणु 0x861e, KEY_DOWN पूर्ण,
	अणु 0x861f, KEY_LEFT पूर्ण,
	अणु 0x861b, KEY_RIGHT पूर्ण,

	/* Key codes क्रम the DiBcom MOD3000 remote. */
	अणु 0x8000, KEY_MUTE पूर्ण,
	अणु 0x8001, KEY_TEXT पूर्ण,
	अणु 0x8002, KEY_HOME पूर्ण,
	अणु 0x8003, KEY_POWER पूर्ण,

	अणु 0x8004, KEY_RED पूर्ण,
	अणु 0x8005, KEY_GREEN पूर्ण,
	अणु 0x8006, KEY_YELLOW पूर्ण,
	अणु 0x8007, KEY_BLUE पूर्ण,

	अणु 0x8008, KEY_DVD पूर्ण,
	अणु 0x8009, KEY_AUDIO पूर्ण,
	अणु 0x800a, KEY_IMAGES पूर्ण,      /* Pictures */
	अणु 0x800b, KEY_VIDEO पूर्ण,

	अणु 0x800c, KEY_BACK पूर्ण,
	अणु 0x800d, KEY_UP पूर्ण,
	अणु 0x800e, KEY_RADIO पूर्ण,
	अणु 0x800f, KEY_EPG पूर्ण,

	अणु 0x8010, KEY_LEFT पूर्ण,
	अणु 0x8011, KEY_OK पूर्ण,
	अणु 0x8012, KEY_RIGHT पूर्ण,
	अणु 0x8013, KEY_UNKNOWN पूर्ण,    /* SAP */

	अणु 0x8014, KEY_TV पूर्ण,
	अणु 0x8015, KEY_DOWN पूर्ण,
	अणु 0x8016, KEY_MENU पूर्ण,       /* DVD Menu */
	अणु 0x8017, KEY_LAST पूर्ण,

	अणु 0x8018, KEY_RECORD पूर्ण,
	अणु 0x8019, KEY_STOP पूर्ण,
	अणु 0x801a, KEY_PAUSE पूर्ण,
	अणु 0x801b, KEY_PLAY पूर्ण,

	अणु 0x801c, KEY_PREVIOUS पूर्ण,
	अणु 0x801d, KEY_REWIND पूर्ण,
	अणु 0x801e, KEY_FASTFORWARD पूर्ण,
	अणु 0x801f, KEY_NEXTपूर्ण,

	अणु 0x8040, KEY_1 पूर्ण,
	अणु 0x8041, KEY_2 पूर्ण,
	अणु 0x8042, KEY_3 पूर्ण,
	अणु 0x8043, KEY_CHANNELUP पूर्ण,

	अणु 0x8044, KEY_4 पूर्ण,
	अणु 0x8045, KEY_5 पूर्ण,
	अणु 0x8046, KEY_6 पूर्ण,
	अणु 0x8047, KEY_CHANNELDOWN पूर्ण,

	अणु 0x8048, KEY_7 पूर्ण,
	अणु 0x8049, KEY_8 पूर्ण,
	अणु 0x804a, KEY_9 पूर्ण,
	अणु 0x804b, KEY_VOLUMEUP पूर्ण,

	अणु 0x804c, KEY_CLEAR पूर्ण,
	अणु 0x804d, KEY_0 पूर्ण,
	अणु 0x804e, KEY_ENTER पूर्ण,
	अणु 0x804f, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;
EXPORT_SYMBOL(rc_map_dibusb_table);

पूर्णांक dibusb_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(5, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = DIBUSB_REQ_POLL_REMOTE;

	ret = dvb_usb_generic_rw(d, buf, 1, buf, 5, 0);
	अगर (ret < 0)
		जाओ ret;

	dvb_usb_nec_rc_key_to_event(d, buf, event, state);

	अगर (buf[0] != 0)
		deb_info("key: %*ph\n", 5, buf);

ret:
	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dibusb_rc_query);
