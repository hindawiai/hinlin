<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB framework compliant Linux driver क्रम the Hauppauge WinTV-NOVA-T usb2
 * DVB-T receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dibusb.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=rc,2=eeprom (|-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा deb_rc(args...) dprपूर्णांकk(debug,0x01,args)
#घोषणा deb_ee(args...) dprपूर्णांकk(debug,0x02,args)

/* Hauppauge NOVA-T USB2 keys */
अटल काष्ठा rc_map_table rc_map_haupp_table[] = अणु
	अणु 0x1e00, KEY_0 पूर्ण,
	अणु 0x1e01, KEY_1 पूर्ण,
	अणु 0x1e02, KEY_2 पूर्ण,
	अणु 0x1e03, KEY_3 पूर्ण,
	अणु 0x1e04, KEY_4 पूर्ण,
	अणु 0x1e05, KEY_5 पूर्ण,
	अणु 0x1e06, KEY_6 पूर्ण,
	अणु 0x1e07, KEY_7 पूर्ण,
	अणु 0x1e08, KEY_8 पूर्ण,
	अणु 0x1e09, KEY_9 पूर्ण,
	अणु 0x1e0a, KEY_KPASTERISK पूर्ण,
	अणु 0x1e0b, KEY_RED पूर्ण,
	अणु 0x1e0c, KEY_RADIO पूर्ण,
	अणु 0x1e0d, KEY_MENU पूर्ण,
	अणु 0x1e0e, KEY_GRAVE पूर्ण, /* # */
	अणु 0x1e0f, KEY_MUTE पूर्ण,
	अणु 0x1e10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1e11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1e12, KEY_CHANNEL पूर्ण,
	अणु 0x1e14, KEY_UP पूर्ण,
	अणु 0x1e15, KEY_DOWN पूर्ण,
	अणु 0x1e16, KEY_LEFT पूर्ण,
	अणु 0x1e17, KEY_RIGHT पूर्ण,
	अणु 0x1e18, KEY_VIDEO पूर्ण,
	अणु 0x1e19, KEY_AUDIO पूर्ण,
	अणु 0x1e1a, KEY_IMAGES पूर्ण,
	अणु 0x1e1b, KEY_EPG पूर्ण,
	अणु 0x1e1c, KEY_TV पूर्ण,
	अणु 0x1e1e, KEY_NEXT पूर्ण,
	अणु 0x1e1f, KEY_BACK पूर्ण,
	अणु 0x1e20, KEY_CHANNELUP पूर्ण,
	अणु 0x1e21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1e24, KEY_LAST पूर्ण, /* Skip backwards */
	अणु 0x1e25, KEY_OK पूर्ण,
	अणु 0x1e29, KEY_BLUEपूर्ण,
	अणु 0x1e2e, KEY_GREEN पूर्ण,
	अणु 0x1e30, KEY_PAUSE पूर्ण,
	अणु 0x1e32, KEY_REWIND पूर्ण,
	अणु 0x1e34, KEY_FASTFORWARD पूर्ण,
	अणु 0x1e35, KEY_PLAY पूर्ण,
	अणु 0x1e36, KEY_STOP पूर्ण,
	अणु 0x1e37, KEY_RECORD पूर्ण,
	अणु 0x1e38, KEY_YELLOW पूर्ण,
	अणु 0x1e3b, KEY_GOTO पूर्ण,
	अणु 0x1e3d, KEY_POWER पूर्ण,
पूर्ण;

/* Firmware bug? someबार, when a new key is pressed, the previous pressed key
 * is delivered. No workaround yet, maybe a new firmware.
 */
अटल पूर्णांक nova_t_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
	u8 *buf, data, toggle, custom;
	u16 raw;
	पूर्णांक i, ret;
	काष्ठा dibusb_device_state *st = d->priv;

	buf = kदो_स्मृति(5, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = DIBUSB_REQ_POLL_REMOTE;
	buf[1] = 0x35;
	ret = dvb_usb_generic_rw(d, buf, 2, buf, 5, 0);
	अगर (ret < 0)
		जाओ ret;

	*state = REMOTE_NO_KEY_PRESSED;
	चयन (buf[0]) अणु
		हाल DIBUSB_RC_HAUPPAUGE_KEY_PRESSED:
			raw = ((buf[1] << 8) | buf[2]) >> 3;
			toggle = !!(raw & 0x800);
			data = raw & 0x3f;
			custom = (raw >> 6) & 0x1f;

			deb_rc("raw key code 0x%02x, 0x%02x, 0x%02x to c: %02x d: %02x toggle: %d\n",
			       buf[1], buf[2], buf[3], custom, data, toggle);

			क्रम (i = 0; i < ARRAY_SIZE(rc_map_haupp_table); i++) अणु
				अगर (rc5_data(&rc_map_haupp_table[i]) == data &&
					rc5_custom(&rc_map_haupp_table[i]) == custom) अणु

					deb_rc("c: %x, d: %x\n", rc5_data(&rc_map_haupp_table[i]),
								 rc5_custom(&rc_map_haupp_table[i]));

					*event = rc_map_haupp_table[i].keycode;
					*state = REMOTE_KEY_PRESSED;
					अगर (st->old_toggle == toggle) अणु
						अगर (st->last_repeat_count++ < 2)
							*state = REMOTE_NO_KEY_PRESSED;
					पूर्ण अन्यथा अणु
						st->last_repeat_count = 0;
						st->old_toggle = toggle;
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण

			अवरोध;
		हाल DIBUSB_RC_HAUPPAUGE_KEY_EMPTY:
		शेष:
			अवरोध;
	पूर्ण

ret:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक nova_t_पढ़ो_mac_address (काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	पूर्णांक i;
	u8 b;

	mac[0] = 0x00;
	mac[1] = 0x0d;
	mac[2] = 0xfe;

	/* this is a complete guess, but works क्रम my box */
	क्रम (i = 136; i < 139; i++) अणु
		dibusb_पढ़ो_eeprom_byte(d,i, &b);

		mac[5 - (i - 136)] = b;
	पूर्ण

	वापस 0;
पूर्ण

/* USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties nova_t_properties;

अटल पूर्णांक nova_t_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf, &nova_t_properties,
				   THIS_MODULE, शून्य, adapter_nr);
पूर्ण

/* करो not change the order of the ID table */
अटल काष्ठा usb_device_id nova_t_table [] = अणु
/* 00 */	अणु USB_DEVICE(USB_VID_HAUPPAUGE,     USB_PID_WINTV_NOVA_T_USB2_COLD) पूर्ण,
/* 01 */	अणु USB_DEVICE(USB_VID_HAUPPAUGE,     USB_PID_WINTV_NOVA_T_USB2_WARM) पूर्ण,
			अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, nova_t_table);

अटल काष्ठा dvb_usb_device_properties nova_t_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-nova-t-usb2-02.fw",

	.num_adapters     = 1,
	.adapter          = अणु
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
		पूर्ण
	पूर्ण,
	.size_of_priv     = माप(काष्ठा dibusb_device_state),

	.घातer_ctrl       = dibusb2_0_घातer_ctrl,
	.पढ़ो_mac_address = nova_t_पढ़ो_mac_address,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = 100,
		.rc_map_table     = rc_map_haupp_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_haupp_table),
		.rc_query         = nova_t_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "Hauppauge WinTV-NOVA-T usb2",
			अणु &nova_t_table[0], शून्य पूर्ण,
			अणु &nova_t_table[1], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver nova_t_driver = अणु
	.name		= "dvb_usb_nova_t_usb2",
	.probe		= nova_t_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= nova_t_table,
पूर्ण;

module_usb_driver(nova_t_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Hauppauge WinTV-NOVA-T usb2");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
