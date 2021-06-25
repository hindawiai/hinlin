<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant Linux driver क्रम the
 *  - TwinhanDTV Alpha/MagicBoxII USB2.0 DVB-T receiver
 *  - DigitalNow TinyUSB2 DVB-t receiver
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * Thanks to Twinhan who kindly provided hardware and inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "vp7045.h"

/* debug */
अटल पूर्णांक dvb_usb_vp7045_debug;
module_param_named(debug,dvb_usb_vp7045_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2,rc=4 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा deb_info(args...) dprपूर्णांकk(dvb_usb_vp7045_debug,0x01,args)
#घोषणा deb_xfer(args...) dprपूर्णांकk(dvb_usb_vp7045_debug,0x02,args)
#घोषणा deb_rc(args...)   dprपूर्णांकk(dvb_usb_vp7045_debug,0x04,args)

पूर्णांक vp7045_usb_op(काष्ठा dvb_usb_device *d, u8 cmd, u8 *out, पूर्णांक outlen, u8 *in, पूर्णांक inlen, पूर्णांक msec)
अणु
	पूर्णांक ret = 0;
	u8 *buf = d->priv;

	buf[0] = cmd;

	अगर (outlen > 19)
		outlen = 19;

	अगर (inlen > 11)
		inlen = 11;

	ret = mutex_lock_पूर्णांकerruptible(&d->usb_mutex);
	अगर (ret)
		वापस ret;

	अगर (out != शून्य && outlen > 0)
		स_नकल(&buf[1], out, outlen);

	deb_xfer("out buffer: ");
	debug_dump(buf, outlen+1, deb_xfer);


	अगर (usb_control_msg(d->udev,
			usb_sndctrlpipe(d->udev,0),
			TH_COMMAND_OUT, USB_TYPE_VENDOR | USB_सूची_OUT, 0, 0,
			buf, 20, 2000) != 20) अणु
		err("USB control message 'out' went wrong.");
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	msleep(msec);

	अगर (usb_control_msg(d->udev,
			usb_rcvctrlpipe(d->udev,0),
			TH_COMMAND_IN, USB_TYPE_VENDOR | USB_सूची_IN, 0, 0,
			buf, 12, 2000) != 12) अणु
		err("USB control message 'in' went wrong.");
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	deb_xfer("in buffer: ");
	debug_dump(buf, 12, deb_xfer);

	अगर (in != शून्य && inlen > 0)
		स_नकल(in, &buf[1], inlen);

unlock:
	mutex_unlock(&d->usb_mutex);

	वापस ret;
पूर्ण

u8 vp7045_पढ़ो_reg(काष्ठा dvb_usb_device *d, u8 reg)
अणु
	u8 obuf[2] = अणु 0 पूर्ण,v;
	obuf[1] = reg;

	vp7045_usb_op(d,TUNER_REG_READ,obuf,2,&v,1,30);

	वापस v;
पूर्ण

अटल पूर्णांक vp7045_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 v = onoff;
	वापस vp7045_usb_op(d,SET_TUNER_POWER,&v,1,शून्य,0,150);
पूर्ण

अटल पूर्णांक vp7045_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret;
	u8 key;

	ret = vp7045_usb_op(d, RC_VAL_READ, शून्य, 0, &key, 1, 20);
	अगर (ret)
		वापस ret;

	deb_rc("remote query key: %x\n", key);

	अगर (key != 0x44) अणु
		/*
		 * The 8 bit address isn't available, but since the remote uses
		 * address 0 we'll use that. nec repeats are ignored too, even
		 * though the remote sends them.
		 */
		rc_keyकरोwn(d->rc_dev, RC_PROTO_NEC, RC_SCANCODE_NEC(0, key), 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_पढ़ो_eeprom(काष्ठा dvb_usb_device *d,u8 *buf, पूर्णांक len, पूर्णांक offset)
अणु
	पूर्णांक i, ret;
	u8 v, br[2];
	क्रम (i=0; i < len; i++) अणु
		v = offset + i;
		ret = vp7045_usb_op(d, GET_EE_VALUE, &v, 1, br, 2, 5);
		अगर (ret)
			वापस ret;

		buf[i] = br[1];
	पूर्ण
	deb_info("VP7045 EEPROM read (offs: %d, len: %d) : ", offset, i);
	debug_dump(buf, i, deb_info);
	वापस 0;
पूर्ण

अटल पूर्णांक vp7045_पढ़ो_mac_addr(काष्ठा dvb_usb_device *d,u8 mac[6])
अणु
	वापस vp7045_पढ़ो_eeprom(d,mac, 6, MAC_0_ADDR);
पूर्ण

अटल पूर्णांक vp7045_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	u8 buf[255] = अणु 0 पूर्ण;

	vp7045_usb_op(adap->dev,VENDOR_STRING_READ,शून्य,0,buf,20,0);
	buf[10] = '\0';
	deb_info("firmware says: %s ",buf);

	vp7045_usb_op(adap->dev,PRODUCT_STRING_READ,शून्य,0,buf,20,0);
	buf[10] = '\0';
	deb_info("%s ",buf);

	vp7045_usb_op(adap->dev,FW_VERSION_READ,शून्य,0,buf,20,0);
	buf[10] = '\0';
	deb_info("v%s\n",buf);

/*	Dump the EEPROM */
/*	vp7045_पढ़ो_eeprom(d,buf, 255, FX2_ID_ADDR); */

	adap->fe_adap[0].fe = vp7045_fe_attach(adap->dev);

	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties vp7045_properties;

अटल पूर्णांक vp7045_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf, &vp7045_properties,
				   THIS_MODULE, शून्य, adapter_nr);
पूर्ण

अटल काष्ठा usb_device_id vp7045_usb_table [] = अणु
	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TWINHAN_VP7045_COLD) पूर्ण,
	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_TWINHAN_VP7045_WARM) पूर्ण,
	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_DNTV_TINYUSB2_COLD) पूर्ण,
	    अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_DNTV_TINYUSB2_WARM) पूर्ण,
	    अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, vp7045_usb_table);

अटल काष्ठा dvb_usb_device_properties vp7045_properties = अणु
	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-vp7045-01.fw",
	.size_of_priv = 20,

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach  = vp7045_frontend_attach,
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
	.घातer_ctrl       = vp7045_घातer_ctrl,
	.पढ़ो_mac_address = vp7045_पढ़ो_mac_addr,

	.rc.core = अणु
		.rc_पूर्णांकerval	= 400,
		.rc_codes	= RC_MAP_TWINHAN_VP1027_DVBS,
		.module_name    = KBUILD_MODNAME,
		.rc_query	= vp7045_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
		.scancode_mask	= 0xff,
	पूर्ण,

	.num_device_descs = 2,
	.devices = अणु
		अणु .name = "Twinhan USB2.0 DVB-T receiver (TwinhanDTV Alpha/MagicBox II)",
		  .cold_ids = अणु &vp7045_usb_table[0], शून्य पूर्ण,
		  .warm_ids = अणु &vp7045_usb_table[1], शून्य पूर्ण,
		पूर्ण,
		अणु .name = "DigitalNow TinyUSB 2 DVB-t Receiver",
		  .cold_ids = अणु &vp7045_usb_table[2], शून्य पूर्ण,
		  .warm_ids = अणु &vp7045_usb_table[3], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver vp7045_usb_driver = अणु
	.name		= "dvb_usb_vp7045",
	.probe		= vp7045_usb_probe,
	.disconnect	= dvb_usb_device_निकास,
	.id_table	= vp7045_usb_table,
पूर्ण;

module_usb_driver(vp7045_usb_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for Twinhan MagicBox/Alpha and DNTV tinyUSB2 DVB-T USB2.0");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
