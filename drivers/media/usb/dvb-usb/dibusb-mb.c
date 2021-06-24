<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम mobile DVB-T USB devices based on
 * reference designs made by DiBcom (http://www.dibcom.fr/) (DiB3000M-B)
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

अटल पूर्णांक dib3000mb_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dibusb_state *st = adap->priv;

	वापस st->ops.tuner_pass_ctrl(fe, enable, st->tuner_addr);
पूर्ण

अटल पूर्णांक dibusb_dib3000mb_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib3000_config demod_cfg;
	काष्ठा dibusb_state *st = adap->priv;

	demod_cfg.demod_address = 0x8;

	adap->fe_adap[0].fe = dvb_attach(dib3000mb_attach, &demod_cfg,
					 &adap->dev->i2c_adap, &st->ops);
	अगर ((adap->fe_adap[0].fe) == शून्य)
		वापस -ENODEV;

	adap->fe_adap[0].fe->ops.i2c_gate_ctrl = dib3000mb_i2c_gate_ctrl;

	वापस 0;
पूर्ण

अटल पूर्णांक dibusb_thomson_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dibusb_state *st = adap->priv;

	st->tuner_addr = 0x61;

	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x61, &adap->dev->i2c_adap,
		   DVB_PLL_TUA6010XS);
	वापस 0;
पूर्ण

अटल पूर्णांक dibusb_panasonic_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dibusb_state *st = adap->priv;

	st->tuner_addr = 0x60;

	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap,
		   DVB_PLL_TDA665X);
	वापस 0;
पूर्ण

/* Some of the Artec 1.1 device aren't equipped with the शेष tuner
 * (Thomson Cable), but with a Panasonic ENV77H11D5.  This function figures
 * this out. */
अटल पूर्णांक dibusb_tuner_probe_and_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	u8 b[2] = अणु 0,0 पूर्ण, b2[1];
	पूर्णांक ret = 0;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .flags = 0,        .buf = b,  .len = 2 पूर्ण,
		अणु .flags = I2C_M_RD, .buf = b2, .len = 1 पूर्ण,
	पूर्ण;
	काष्ठा dibusb_state *st = adap->priv;

	/* the Panasonic sits on I2C addrass 0x60, the Thomson on 0x61 */
	msg[0].addr = msg[1].addr = st->tuner_addr = 0x60;

	अगर (adap->fe_adap[0].fe->ops.i2c_gate_ctrl)
		adap->fe_adap[0].fe->ops.i2c_gate_ctrl(adap->fe_adap[0].fe, 1);

	अगर (i2c_transfer(&adap->dev->i2c_adap, msg, 2) != 2) अणु
		err("tuner i2c write failed.");
		वापस -EREMOTEIO;
	पूर्ण

	अगर (adap->fe_adap[0].fe->ops.i2c_gate_ctrl)
		adap->fe_adap[0].fe->ops.i2c_gate_ctrl(adap->fe_adap[0].fe, 0);

	अगर (b2[0] == 0xfe) अणु
		info("This device has the Thomson Cable onboard. Which is default.");
		ret = dibusb_thomson_tuner_attach(adap);
	पूर्ण अन्यथा अणु
		info("This device has the Panasonic ENV77H11D5 onboard.");
		ret = dibusb_panasonic_tuner_attach(adap);
	पूर्ण

	वापस ret;
पूर्ण

/* USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties dibusb1_1_properties;
अटल काष्ठा dvb_usb_device_properties dibusb1_1_an2235_properties;
अटल काष्ठा dvb_usb_device_properties dibusb2_0b_properties;
अटल काष्ठा dvb_usb_device_properties artec_t1_usb2_properties;

अटल पूर्णांक dibusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (0 == dvb_usb_device_init(पूर्णांकf, &dibusb1_1_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &dibusb1_1_an2235_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &dibusb2_0b_properties,
				     THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &artec_t1_usb2_properties,
				     THIS_MODULE, शून्य, adapter_nr))
		वापस 0;

	वापस -EINVAL;
पूर्ण

/* करो not change the order of the ID table */
अटल काष्ठा usb_device_id dibusb_dib3000mb_table [] = अणु
/* 00 */	अणु USB_DEVICE(USB_VID_WIDEVIEW,		USB_PID_AVERMEDIA_DVBT_USB_COLD) पूर्ण,
/* 01 */	अणु USB_DEVICE(USB_VID_WIDEVIEW,		USB_PID_AVERMEDIA_DVBT_USB_WARM) पूर्ण,
/* 02 */	अणु USB_DEVICE(USB_VID_COMPRO,		USB_PID_COMPRO_DVBU2000_COLD) पूर्ण,
/* 03 */	अणु USB_DEVICE(USB_VID_COMPRO,		USB_PID_COMPRO_DVBU2000_WARM) पूर्ण,
/* 04 */	अणु USB_DEVICE(USB_VID_COMPRO_UNK,	USB_PID_COMPRO_DVBU2000_UNK_COLD) पूर्ण,
/* 05 */	अणु USB_DEVICE(USB_VID_DIBCOM,		USB_PID_DIBCOM_MOD3000_COLD) पूर्ण,
/* 06 */	अणु USB_DEVICE(USB_VID_DIBCOM,		USB_PID_DIBCOM_MOD3000_WARM) पूर्ण,
/* 07 */	अणु USB_DEVICE(USB_VID_EMPIA,		USB_PID_KWORLD_VSTREAM_COLD) पूर्ण,
/* 08 */	अणु USB_DEVICE(USB_VID_EMPIA,		USB_PID_KWORLD_VSTREAM_WARM) पूर्ण,
/* 09 */	अणु USB_DEVICE(USB_VID_GRANDTEC,		USB_PID_GRANDTEC_DVBT_USB_COLD) पूर्ण,
/* 10 */	अणु USB_DEVICE(USB_VID_GRANDTEC,		USB_PID_GRANDTEC_DVBT_USB_WARM) पूर्ण,
/* 11 */	अणु USB_DEVICE(USB_VID_GRANDTEC,		USB_PID_DIBCOM_MOD3000_COLD) पूर्ण,
/* 12 */	अणु USB_DEVICE(USB_VID_GRANDTEC,		USB_PID_DIBCOM_MOD3000_WARM) पूर्ण,
/* 13 */	अणु USB_DEVICE(USB_VID_HYPER_PALTEK,	USB_PID_UNK_HYPER_PALTEK_COLD) पूर्ण,
/* 14 */	अणु USB_DEVICE(USB_VID_HYPER_PALTEK,	USB_PID_UNK_HYPER_PALTEK_WARM) पूर्ण,
/* 15 */	अणु USB_DEVICE(USB_VID_VISIONPLUS,	USB_PID_TWINHAN_VP7041_COLD) पूर्ण,
/* 16 */	अणु USB_DEVICE(USB_VID_VISIONPLUS,	USB_PID_TWINHAN_VP7041_WARM) पूर्ण,
/* 17 */	अणु USB_DEVICE(USB_VID_TWINHAN,		USB_PID_TWINHAN_VP7041_COLD) पूर्ण,
/* 18 */	अणु USB_DEVICE(USB_VID_TWINHAN,		USB_PID_TWINHAN_VP7041_WARM) पूर्ण,
/* 19 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_COLD) पूर्ण,
/* 20 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_WARM) पूर्ण,
/* 21 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_AN2235_COLD) पूर्ण,
/* 22 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_AN2235_WARM) पूर्ण,
/* 23 */	अणु USB_DEVICE(USB_VID_ADSTECH,		USB_PID_ADSTECH_USB2_COLD) पूर्ण,

/* device ID with शेष DIBUSB2_0-firmware and with the hacked firmware */
/* 24 */	अणु USB_DEVICE(USB_VID_ADSTECH,		USB_PID_ADSTECH_USB2_WARM) पूर्ण,
/* 25 */	अणु USB_DEVICE(USB_VID_KYE,		USB_PID_KYE_DVB_T_COLD) पूर्ण,
/* 26 */	अणु USB_DEVICE(USB_VID_KYE,		USB_PID_KYE_DVB_T_WARM) पूर्ण,

/* 27 */	अणु USB_DEVICE(USB_VID_KWORLD,		USB_PID_KWORLD_VSTREAM_COLD) पूर्ण,

/* 28 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_USB2_COLD) पूर्ण,
/* 29 */	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC,	USB_PID_ULTIMA_TVBOX_USB2_WARM) पूर्ण,

/*
 * XXX: As Artec just 'forgot' to program the EEPROM on some Artec T1 devices
 *      we करोn't catch these faulty IDs (namely 'Cypress FX1 USB controller') that
 *      have been left on the device. If you करोn't have such a device but an Artec
 *      device that's supposed to work with this driver but is not detected by it,
 *      मुक्त to enable CONFIG_DVB_USB_DIBUSB_MB_FAULTY via your kernel config.
 */

#अगर_घोषित CONFIG_DVB_USB_DIBUSB_MB_FAULTY
/* 30 */	अणु USB_DEVICE(USB_VID_ANCHOR,		USB_PID_ULTIMA_TVBOX_ANCHOR_COLD) पूर्ण,
#पूर्ण_अगर

			अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, dibusb_dib3000mb_table);

अटल काष्ठा dvb_usb_device_properties dibusb1_1_properties = अणु
	.caps =  DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_AN2135,

	.firmware = "dvb-usb-dibusb-5.0.0.11.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 16,

			.streaming_ctrl   = dibusb_streaming_ctrl,
			.pid_filter       = dibusb_pid_filter,
			.pid_filter_ctrl  = dibusb_pid_filter_ctrl,
			.frontend_attach  = dibusb_dib3000mb_frontend_attach,
			.tuner_attach     = dibusb_tuner_probe_and_attach,

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
			.size_of_priv     = माप(काष्ठा dibusb_state),
		पूर्ण
	पूर्ण,

	.घातer_ctrl       = dibusb_घातer_ctrl,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
		.rc_map_table     = rc_map_dibusb_table,
		.rc_map_size      = 111, /* wow, that is ugly ... I want to load it to the driver dynamically */
		.rc_query         = dibusb_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 9,
	.devices = अणु
		अणु	"AVerMedia AverTV DVBT USB1.1",
			अणु &dibusb_dib3000mb_table[0],  शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[1],  शून्य पूर्ण,
		पूर्ण,
		अणु	"Compro Videomate DVB-U2000 - DVB-T USB1.1 (please confirm to linux-dvb)",
			अणु &dibusb_dib3000mb_table[2], &dibusb_dib3000mb_table[4], शून्यपूर्ण,
			अणु &dibusb_dib3000mb_table[3], शून्य पूर्ण,
		पूर्ण,
		अणु	"DiBcom USB1.1 DVB-T reference design (MOD3000)",
			अणु &dibusb_dib3000mb_table[5],  शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[6],  शून्य पूर्ण,
		पूर्ण,
		अणु	"KWorld V-Stream XPERT DTV - DVB-T USB1.1",
			अणु &dibusb_dib3000mb_table[7], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[8], शून्य पूर्ण,
		पूर्ण,
		अणु	"Grandtec USB1.1 DVB-T",
			अणु &dibusb_dib3000mb_table[9],  &dibusb_dib3000mb_table[11], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[10], &dibusb_dib3000mb_table[12], शून्य पूर्ण,
		पूर्ण,
		अणु	"Unknown USB1.1 DVB-T device ???? please report the name to the author",
			अणु &dibusb_dib3000mb_table[13], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[14], शून्य पूर्ण,
		पूर्ण,
		अणु	"TwinhanDTV USB-Ter USB1.1 / Magic Box I / HAMA USB1.1 DVB-T device",
			अणु &dibusb_dib3000mb_table[15], &dibusb_dib3000mb_table[17], शून्यपूर्ण,
			अणु &dibusb_dib3000mb_table[16], &dibusb_dib3000mb_table[18], शून्यपूर्ण,
		पूर्ण,
		अणु	"Artec T1 USB1.1 TVBOX with AN2135",
			अणु &dibusb_dib3000mb_table[19], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[20], शून्य पूर्ण,
		पूर्ण,
		अणु	"VideoWalker DVB-T USB",
			अणु &dibusb_dib3000mb_table[25], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[26], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dibusb1_1_an2235_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = CYPRESS_AN2235,

	.firmware = "dvb-usb-dibusb-an2235-01.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF | DVB_USB_ADAP_HAS_PID_FILTER,
			.pid_filter_count = 16,

			.streaming_ctrl   = dibusb_streaming_ctrl,
			.pid_filter       = dibusb_pid_filter,
			.pid_filter_ctrl  = dibusb_pid_filter_ctrl,
			.frontend_attach  = dibusb_dib3000mb_frontend_attach,
			.tuner_attach     = dibusb_tuner_probe_and_attach,

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
			.size_of_priv     = माप(काष्ठा dibusb_state),
		पूर्ण,
	पूर्ण,
	.घातer_ctrl       = dibusb_घातer_ctrl,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
		.rc_map_table     = rc_map_dibusb_table,
		.rc_map_size      = 111, /* wow, that is ugly ... I want to load it to the driver dynamically */
		.rc_query         = dibusb_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

#अगर_घोषित CONFIG_DVB_USB_DIBUSB_MB_FAULTY
	.num_device_descs = 2,
#अन्यथा
	.num_device_descs = 1,
#पूर्ण_अगर
	.devices = अणु
		अणु	"Artec T1 USB1.1 TVBOX with AN2235",
			अणु &dibusb_dib3000mb_table[21], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[22], शून्य पूर्ण,
		पूर्ण,
#अगर_घोषित CONFIG_DVB_USB_DIBUSB_MB_FAULTY
		अणु	"Artec T1 USB1.1 TVBOX with AN2235 (faulty USB IDs)",
			अणु &dibusb_dib3000mb_table[30], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
#पूर्ण_अगर
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dibusb2_0b_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,

	.firmware = "dvb-usb-adstech-usb2-02.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 16,

			.streaming_ctrl   = dibusb2_0_streaming_ctrl,
			.pid_filter       = dibusb_pid_filter,
			.pid_filter_ctrl  = dibusb_pid_filter_ctrl,
			.frontend_attach  = dibusb_dib3000mb_frontend_attach,
			.tuner_attach     = dibusb_thomson_tuner_attach,

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
	.घातer_ctrl       = dibusb2_0_घातer_ctrl,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
		.rc_map_table     = rc_map_dibusb_table,
		.rc_map_size      = 111, /* wow, that is ugly ... I want to load it to the driver dynamically */
		.rc_query         = dibusb_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 2,
	.devices = अणु
		अणु	"KWorld/ADSTech Instant DVB-T USB2.0",
			अणु &dibusb_dib3000mb_table[23], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[24], शून्य पूर्ण,
		पूर्ण,
		अणु	"KWorld Xpert DVB-T USB2.0",
			अणु &dibusb_dib3000mb_table[27], शून्य पूर्ण,
			अणु शून्य पूर्ण
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties artec_t1_usb2_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,

	.firmware = "dvb-usb-dibusb-6.0.0.8.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
			.pid_filter_count = 16,

			.streaming_ctrl   = dibusb2_0_streaming_ctrl,
			.pid_filter       = dibusb_pid_filter,
			.pid_filter_ctrl  = dibusb_pid_filter_ctrl,
			.frontend_attach  = dibusb_dib3000mb_frontend_attach,
			.tuner_attach     = dibusb_tuner_probe_and_attach,
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
	.घातer_ctrl       = dibusb2_0_घातer_ctrl,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
		.rc_map_table     = rc_map_dibusb_table,
		.rc_map_size      = 111, /* wow, that is ugly ... I want to load it to the driver dynamically */
		.rc_query         = dibusb_rc_query,
	पूर्ण,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु	"Artec T1 USB2.0",
			अणु &dibusb_dib3000mb_table[28], शून्य पूर्ण,
			अणु &dibusb_dib3000mb_table[29], शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver dibusb_driver = अणु
	.name		= "dvb_usb_dibusb_mb",
	.probe		= dibusb_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= dibusb_dib3000mb_table,
पूर्ण;

module_usb_driver(dibusb_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for DiBcom USB DVB-T devices (DiB3000M-B based)");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
