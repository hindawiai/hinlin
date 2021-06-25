<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम mobile DVB-T USB devices based on
 * reference designs made by DiBcom (http://www.dibcom.fr/) (DiB3000M-C/P)
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * based on GPL code from DiBcom, which has
 * Copyright (C) 2004 Amaury Demol क्रम DiBcom
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dibusb.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties dibusb_mc_properties;

अटल पूर्णांक dibusb_mc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf, &dibusb_mc_properties, THIS_MODULE,
				   शून्य, adapter_nr);
पूर्ण

/* करो not change the order of the ID table */
अटल काष्ठा usb_device_id dibusb_dib3000mc_table [] = अणु
/* 00 */	अणु USB_DEVICE(USB_VID_DIBCOM,		USB_PID_DIBCOM_MOD3001_COLD) पूर्ण,
/* 01 */	अणु USB_DEVICE(USB_VID_DIBCOM,		USB_PID_DIBCOM_MOD3001_WARM) पूर्ण,
/* 02 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_USB2_COLD) पूर्ण,
/* 03 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_USB2_WARM) पूर्ण, // ( ? )
/* 04 */	अणु USB_DEVICE(USB_VID_LITEON,		USB_PID_LITEON_DVB_T_COLD) पूर्ण,
/* 05 */	अणु USB_DEVICE(USB_VID_LITEON,		USB_PID_LITEON_DVB_T_WARM) पूर्ण,
/* 06 */	अणु USB_DEVICE(USB_VID_EMPIA,		USB_PID_DIGIVOX_MINI_SL_COLD) पूर्ण,
/* 07 */	अणु USB_DEVICE(USB_VID_EMPIA,		USB_PID_DIGIVOX_MINI_SL_WARM) पूर्ण,
/* 08 */	अणु USB_DEVICE(USB_VID_GRANDTEC,          USB_PID_GRANDTEC_DVBT_USB2_COLD) पूर्ण,
/* 09 */	अणु USB_DEVICE(USB_VID_GRANDTEC,          USB_PID_GRANDTEC_DVBT_USB2_WARM) पूर्ण,
/* 10 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ARTEC_T14_COLD) पूर्ण,
/* 11 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ARTEC_T14_WARM) पूर्ण,
/* 12 */	अणु USB_DEVICE(USB_VID_LEADTEK,		USB_PID_WINFAST_DTV_DONGLE_COLD) पूर्ण,
/* 13 */	अणु USB_DEVICE(USB_VID_LEADTEK,		USB_PID_WINFAST_DTV_DONGLE_WARM) पूर्ण,
/* 14 */	अणु USB_DEVICE(USB_VID_HUMAX_COEX,	USB_PID_DVB_T_USB_STICK_HIGH_SPEED_COLD) पूर्ण,
/* 15 */	अणु USB_DEVICE(USB_VID_HUMAX_COEX,	USB_PID_DVB_T_USB_STICK_HIGH_SPEED_WARM) पूर्ण,
			अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, dibusb_dib3000mc_table);

अटल काष्ठा dvb_usb_device_properties dibusb_mc_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-dibusb-6.0.0.8.fw",

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
				.count = 8,
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
	.घातer_ctrl       = dibusb2_0_घातer_ctrl,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
		.rc_map_table     = rc_map_dibusb_table,
		.rc_map_size      = 111, /* FIXME */
		.rc_query         = dibusb_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 8,
	.devices = अणु
		अणु   "DiBcom USB2.0 DVB-T reference design (MOD3000P)",
			अणु &dibusb_dib3000mc_table[0], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[1], शून्य पूर्ण,
		पूर्ण,
		अणु   "Artec T1 USB2.0 TVBOX (please check the warm ID)",
			अणु &dibusb_dib3000mc_table[2], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[3], शून्य पूर्ण,
		पूर्ण,
		अणु   "LITE-ON USB2.0 DVB-T Tuner",
		    /* Also rebअक्रमed as Intuix S800, Toshiba */
			अणु &dibusb_dib3000mc_table[4], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[5], शून्य पूर्ण,
		पूर्ण,
		अणु   "MSI Digivox Mini SL",
			अणु &dibusb_dib3000mc_table[6], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[7], शून्य पूर्ण,
		पूर्ण,
		अणु   "GRAND - USB2.0 DVB-T adapter",
			अणु &dibusb_dib3000mc_table[8], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[9], शून्य पूर्ण,
		पूर्ण,
		अणु   "Artec T14 - USB2.0 DVB-T",
			अणु &dibusb_dib3000mc_table[10], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[11], शून्य पूर्ण,
		पूर्ण,
		अणु   "Leadtek - USB2.0 Winfast DTV dongle",
			अणु &dibusb_dib3000mc_table[12], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[13], शून्य पूर्ण,
		पूर्ण,
		अणु   "Humax/Coex DVB-T USB Stick 2.0 High Speed",
			अणु &dibusb_dib3000mc_table[14], शून्य पूर्ण,
			अणु &dibusb_dib3000mc_table[15], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver dibusb_mc_driver = अणु
	.name		= "dvb_usb_dibusb_mc",
	.probe		= dibusb_mc_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= dibusb_dib3000mc_table,
पूर्ण;

module_usb_driver(dibusb_mc_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for DiBcom USB2.0 DVB-T (DiB3000M-C/P based) devices");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
