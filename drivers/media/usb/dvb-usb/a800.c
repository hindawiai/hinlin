<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB framework compliant Linux driver क्रम the AVerMedia AverTV DVB-T
 * USB2.0 (A800) DVB-T receiver.
 *
 * Copyright (C) 2005 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * Thanks to
 *   - AVerMedia who kindly provided inक्रमmation and
 *   - Glen Harris who suffered from my mistakes during development.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dibusb.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (rc=1 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा deb_rc(args...)   dprपूर्णांकk(debug,0x01,args)

अटल पूर्णांक a800_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	/* करो nothing क्रम the AVerMedia */
	वापस 0;
पूर्ण

/* assure to put cold to 0 क्रम iManufacturer == 1 */
अटल पूर्णांक a800_identअगरy_state(काष्ठा usb_device *udev,
			       स्थिर काष्ठा dvb_usb_device_properties *props,
			       स्थिर काष्ठा dvb_usb_device_description **desc,
			       पूर्णांक *cold)
अणु
	*cold = udev->descriptor.iManufacturer != 1;
	वापस 0;
पूर्ण

अटल पूर्णांक a800_rc_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret = 0;
	u8 *key = kदो_स्मृति(5, GFP_KERNEL);
	अगर (!key)
		वापस -ENOMEM;

	अगर (usb_control_msg(d->udev,usb_rcvctrlpipe(d->udev,0),
				0x04, USB_TYPE_VENDOR | USB_सूची_IN, 0, 0, key, 5,
				2000) != 5) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Note that extended nec and nec32 are dropped */
	अगर (key[0] == 1)
		rc_keyकरोwn(d->rc_dev, RC_PROTO_NEC,
			   RC_SCANCODE_NEC(key[1], key[3]), 0);
	अन्यथा अगर (key[0] == 2)
		rc_repeat(d->rc_dev);
out:
	kमुक्त(key);
	वापस ret;
पूर्ण

/* USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties a800_properties;

अटल पूर्णांक a800_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf, &a800_properties,
				   THIS_MODULE, शून्य, adapter_nr);
पूर्ण

/* करो not change the order of the ID table */
अटल काष्ठा usb_device_id a800_table [] = अणु
/* 00 */	अणु USB_DEVICE(USB_VID_AVERMEDIA,     USB_PID_AVERMEDIA_DVBT_USB2_COLD) पूर्ण,
/* 01 */	अणु USB_DEVICE(USB_VID_AVERMEDIA,     USB_PID_AVERMEDIA_DVBT_USB2_WARM) पूर्ण,
			अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, a800_table);

अटल काष्ठा dvb_usb_device_properties a800_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-avertv-a800-02.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 32,
			.streaming_ctrl   = dibusb2_0_streaming_ctrl,
			.pid_filter       = dibusb_pid_filter,
			.pid_filter_ctrl  = dibusb_pid_filter_ctrl,

			.frontend_attach  = dibusb_dib3000mc_frontend_attach,
			.tuner_attach     = dibusb_dib3000mc_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
					.stream = अणु
						.type = USB_BULK,
				.count = 7,
				.endpoपूर्णांक = 0x06,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
			.size_of_priv     = माप(काष्ठा dibusb_state),
		पूर्ण,
	पूर्ण,

	.घातer_ctrl       = a800_घातer_ctrl,
	.identअगरy_state   = a800_identअगरy_state,

	.rc.core = अणु
		.rc_पूर्णांकerval	= DEFAULT_RC_INTERVAL,
		.rc_codes	= RC_MAP_AVERMEDIA_M135A,
		.module_name	= KBUILD_MODNAME,
		.rc_query	= a800_rc_query,
		.allowed_protos = RC_PROTO_BIT_NEC,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.num_device_descs = 1,
	.devices = अणु
		अणु   "AVerMedia AverTV DVB-T USB 2.0 (A800)",
			अणु &a800_table[0], शून्य पूर्ण,
			अणु &a800_table[1], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver a800_driver = अणु
	.name		= "dvb_usb_a800",
	.probe		= a800_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= a800_table,
पूर्ण;

module_usb_driver(a800_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("AVerMedia AverTV DVB-T USB 2.0 (A800)");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
