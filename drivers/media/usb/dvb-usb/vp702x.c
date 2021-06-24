<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant Linux driver क्रम the TwinhanDTV StarBox USB2.0 DVB-S
 * receiver.
 *
 * Copyright (C) 2005 Ralph Metzler <rjkm@metzlerbros.de>
 *                    Metzler Brothers Systementwicklung GbR
 *
 * Copyright (C) 2005 Patrick Boettcher <patrick.boettcher@posteo.de>
 *
 * Thanks to Twinhan who kindly provided hardware and inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "vp702x.h"
#समावेश <linux/mutex.h>

/* debug */
पूर्णांक dvb_usb_vp702x_debug;
module_param_named(debug,dvb_usb_vp702x_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2,rc=4 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा vp702x_adapter_state अणु
	पूर्णांक pid_filter_count;
	पूर्णांक pid_filter_can_bypass;
	u8  pid_filter_state;
पूर्ण;

अटल पूर्णांक vp702x_usb_in_op_unlocked(काष्ठा dvb_usb_device *d, u8 req,
				     u16 value, u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(d->udev,
		usb_rcvctrlpipe(d->udev, 0),
		req,
		USB_TYPE_VENDOR | USB_सूची_IN,
		value, index, b, blen,
		2000);

	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;


	deb_xfer("in: req. %02x, val: %04x, ind: %04x, buffer: ",req,value,index);
	debug_dump(b,blen,deb_xfer);

	वापस ret;
पूर्ण

पूर्णांक vp702x_usb_in_op(काष्ठा dvb_usb_device *d, u8 req, u16 value,
		     u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;

	mutex_lock(&d->usb_mutex);
	ret = vp702x_usb_in_op_unlocked(d, req, value, index, b, blen);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक vp702x_usb_out_op_unlocked(काष्ठा dvb_usb_device *d, u8 req,
				      u16 value, u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;
	deb_xfer("out: req. %02x, val: %04x, ind: %04x, buffer: ",req,value,index);
	debug_dump(b,blen,deb_xfer);

	अगर ((ret = usb_control_msg(d->udev,
			usb_sndctrlpipe(d->udev,0),
			req,
			USB_TYPE_VENDOR | USB_सूची_OUT,
			value,index,b,blen,
			2000)) != blen) अणु
		warn("usb out operation failed. (%d)",ret);
		वापस -EIO;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक vp702x_usb_out_op(काष्ठा dvb_usb_device *d, u8 req, u16 value,
			     u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret;

	mutex_lock(&d->usb_mutex);
	ret = vp702x_usb_out_op_unlocked(d, req, value, index, b, blen);
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

पूर्णांक vp702x_usb_inout_op(काष्ठा dvb_usb_device *d, u8 *o, पूर्णांक olen, u8 *i, पूर्णांक ilen, पूर्णांक msec)
अणु
	पूर्णांक ret;

	अगर ((ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex)))
		वापस ret;

	ret = vp702x_usb_out_op_unlocked(d, REQUEST_OUT, 0, 0, o, olen);
	msleep(msec);
	ret = vp702x_usb_in_op_unlocked(d, REQUEST_IN, 0, 0, i, ilen);

	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vp702x_usb_inout_cmd(काष्ठा dvb_usb_device *d, u8 cmd, u8 *o,
				पूर्णांक olen, u8 *i, पूर्णांक ilen, पूर्णांक msec)
अणु
	काष्ठा vp702x_device_state *st = d->priv;
	पूर्णांक ret = 0;
	u8 *buf;
	पूर्णांक buflen = max(olen + 2, ilen + 1);

	ret = mutex_lock_पूर्णांकerruptible(&st->buf_mutex);
	अगर (ret < 0)
		वापस ret;

	अगर (buflen > st->buf_len) अणु
		buf = kदो_स्मृति(buflen, GFP_KERNEL);
		अगर (!buf) अणु
			mutex_unlock(&st->buf_mutex);
			वापस -ENOMEM;
		पूर्ण
		info("successfully reallocated a bigger buffer");
		kमुक्त(st->buf);
		st->buf = buf;
		st->buf_len = buflen;
	पूर्ण अन्यथा अणु
		buf = st->buf;
	पूर्ण

	buf[0] = 0x00;
	buf[1] = cmd;
	स_नकल(&buf[2], o, olen);

	ret = vp702x_usb_inout_op(d, buf, olen+2, buf, ilen+1, msec);

	अगर (ret == 0)
		स_नकल(i, &buf[1], ilen);
	mutex_unlock(&st->buf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक vp702x_set_pld_mode(काष्ठा dvb_usb_adapter *adap, u8 bypass)
अणु
	पूर्णांक ret;
	काष्ठा vp702x_device_state *st = adap->dev->priv;
	u8 *buf;

	mutex_lock(&st->buf_mutex);

	buf = st->buf;
	स_रखो(buf, 0, 16);

	ret = vp702x_usb_in_op(adap->dev, 0xe0, (bypass << 8) | 0x0e,
			0, buf, 16);
	mutex_unlock(&st->buf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vp702x_set_pld_state(काष्ठा dvb_usb_adapter *adap, u8 state)
अणु
	पूर्णांक ret;
	काष्ठा vp702x_device_state *st = adap->dev->priv;
	u8 *buf;

	mutex_lock(&st->buf_mutex);

	buf = st->buf;
	स_रखो(buf, 0, 16);
	ret = vp702x_usb_in_op(adap->dev, 0xe0, (state << 8) | 0x0f,
			0, buf, 16);

	mutex_unlock(&st->buf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक vp702x_set_pid(काष्ठा dvb_usb_adapter *adap, u16 pid, u8 id, पूर्णांक onoff)
अणु
	काष्ठा vp702x_adapter_state *st = adap->priv;
	काष्ठा vp702x_device_state *dst = adap->dev->priv;
	u8 *buf;

	अगर (onoff)
		st->pid_filter_state |=  (1 << id);
	अन्यथा अणु
		st->pid_filter_state &= ~(1 << id);
		pid = 0xffff;
	पूर्ण

	id = 0x10 + id*2;

	vp702x_set_pld_state(adap, st->pid_filter_state);

	mutex_lock(&dst->buf_mutex);

	buf = dst->buf;
	स_रखो(buf, 0, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid >> 8) & 0xff) << 8) | (id), 0, buf, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid     ) & 0xff) << 8) | (id+1), 0, buf, 16);

	mutex_unlock(&dst->buf_mutex);

	वापस 0;
पूर्ण


अटल पूर्णांक vp702x_init_pid_filter(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा vp702x_adapter_state *st = adap->priv;
	काष्ठा vp702x_device_state *dst = adap->dev->priv;
	पूर्णांक i;
	u8 *b;

	st->pid_filter_count = 8;
	st->pid_filter_can_bypass = 1;
	st->pid_filter_state = 0x00;

	vp702x_set_pld_mode(adap, 1); /* bypass */

	क्रम (i = 0; i < st->pid_filter_count; i++)
		vp702x_set_pid(adap, 0xffff, i, 1);

	mutex_lock(&dst->buf_mutex);
	b = dst->buf;
	स_रखो(b, 0, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 3, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 0, 0, b, 10);
	vp702x_usb_in_op(adap->dev, 0xb5, 1, 0, b, 10);
	mutex_unlock(&dst->buf_mutex);
	/*vp702x_set_pld_mode(d, 0); // filter */

	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	वापस 0;
पूर्ण

/* keys क्रम the enबंदd remote control */
अटल काष्ठा rc_map_table rc_map_vp702x_table[] = अणु
	अणु 0x0001, KEY_1 पूर्ण,
	अणु 0x0002, KEY_2 पूर्ण,
पूर्ण;

/* remote control stuff (करोes not work with my box) */
अटल पूर्णांक vp702x_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
/* हटाओ the following वापस to enabled remote querying */
#अगर 0
	u8 *key;
	पूर्णांक i;

	key = kदो_स्मृति(10, GFP_KERNEL);
	अगर (!key)
		वापस -ENOMEM;

	vp702x_usb_in_op(d,READ_REMOTE_REQ,0,0,key,10);

	deb_rc("remote query key: %x %d\n",key[1],key[1]);

	अगर (key[1] == 0x44) अणु
		*state = REMOTE_NO_KEY_PRESSED;
		kमुक्त(key);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rc_map_vp702x_table); i++)
		अगर (rc5_custom(&rc_map_vp702x_table[i]) == key[1]) अणु
			*state = REMOTE_KEY_PRESSED;
			*event = rc_map_vp702x_table[i].keycode;
			अवरोध;
		पूर्ण
	kमुक्त(key);
#पूर्ण_अगर

	वापस 0;
पूर्ण


अटल पूर्णांक vp702x_पढ़ो_mac_addr(काष्ठा dvb_usb_device *d,u8 mac[6])
अणु
	u8 i, *buf;
	काष्ठा vp702x_device_state *st = d->priv;

	mutex_lock(&st->buf_mutex);
	buf = st->buf;
	क्रम (i = 6; i < 12; i++)
		vp702x_usb_in_op(d, READ_EEPROM_REQ, i, 1, &buf[i - 6], 1);

	स_नकल(mac, buf, 6);
	mutex_unlock(&st->buf_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	u8 buf[10] = अणु 0 पूर्ण;

	vp702x_usb_out_op(adap->dev, SET_TUNER_POWER_REQ, 0, 7, शून्य, 0);

	अगर (vp702x_usb_inout_cmd(adap->dev, GET_SYSTEM_STRING, शून्य, 0,
				   buf, 10, 10))
		वापस -EIO;

	buf[9] = '\0';
	info("system string: %s",&buf[1]);

	vp702x_init_pid_filter(adap);

	adap->fe_adap[0].fe = vp702x_fe_attach(adap->dev);
	vp702x_usb_out_op(adap->dev, SET_TUNER_POWER_REQ, 1, 7, शून्य, 0);

	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties vp702x_properties;

अटल पूर्णांक vp702x_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dvb_usb_device *d;
	काष्ठा vp702x_device_state *st;
	पूर्णांक ret;

	ret = dvb_usb_device_init(पूर्णांकf, &vp702x_properties,
				   THIS_MODULE, &d, adapter_nr);
	अगर (ret)
		जाओ out;

	st = d->priv;
	st->buf_len = 16;
	st->buf = kदो_स्मृति(st->buf_len, GFP_KERNEL);
	अगर (!st->buf) अणु
		ret = -ENOMEM;
		dvb_usb_device_निकास(पूर्णांकf);
		जाओ out;
	पूर्ण
	mutex_init(&st->buf_mutex);

out:
	वापस ret;

पूर्ण

अटल व्योम vp702x_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा vp702x_device_state *st = d->priv;
	mutex_lock(&st->buf_mutex);
	kमुक्त(st->buf);
	mutex_unlock(&st->buf_mutex);
	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_device_id vp702x_usb_table [] = अणु
	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TWINHAN_VP7021_COLD) पूर्ण,
//	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TWINHAN_VP7020_COLD) पूर्ण,
//	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TWINHAN_VP7020_WARM) पूर्ण,
	    अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, vp702x_usb_table);

अटल काष्ठा dvb_usb_device_properties vp702x_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware            = "dvb-usb-vp702x-02.fw",
	.no_reconnect        = 1,

	.size_of_priv     = माप(काष्ठा vp702x_device_state),

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps             = DVB_USB_ADAP_RECEIVES_204_BYTE_TS,

			.streaming_ctrl   = vp702x_streaming_ctrl,
			.frontend_attach  = vp702x_frontend_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 10,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
			.size_of_priv     = माप(काष्ठा vp702x_adapter_state),
		पूर्ण
	पूर्ण,
	.पढ़ो_mac_address = vp702x_पढ़ो_mac_addr,

	.rc.legacy = अणु
		.rc_map_table       = rc_map_vp702x_table,
		.rc_map_size  = ARRAY_SIZE(rc_map_vp702x_table),
		.rc_पूर्णांकerval      = 400,
		.rc_query         = vp702x_rc_query,
	पूर्ण,

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "TwinhanDTV StarBox DVB-S USB2.0 (VP7021)",
		  .cold_ids = अणु &vp702x_usb_table[0], शून्य पूर्ण,
		  .warm_ids = अणु शून्य पूर्ण,
		पूर्ण,
/*		अणु .name = "TwinhanDTV StarBox DVB-S USB2.0 (VP7020)",
		  .cold_ids = अणु &vp702x_usb_table[2], शून्य पूर्ण,
		  .warm_ids = अणु &vp702x_usb_table[3], शून्य पूर्ण,
		पूर्ण,
*/		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver vp702x_usb_driver = अणु
	.name		= "dvb_usb_vp702x",
	.probe		= vp702x_usb_probe,
	.disconnect	= vp702x_usb_disconnect,
	.id_table	= vp702x_usb_table,
पूर्ण;

module_usb_driver(vp702x_usb_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for Twinhan StarBox DVB-S USB2.0 and clones");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
