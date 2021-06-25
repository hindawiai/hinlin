<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB framework compliant Linux driver क्रम the HanfTek UMT-010 USB2.0
 * DVB-T receiver.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "dibusb.h"

#समावेश "mt352.h"

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक umt_mt352_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 mt352_घड़ी_config[] = अणु 0x89, 0xb8, 0x2d पूर्ण;
	अटल u8 mt352_reset[] = अणु 0x50, 0x80 पूर्ण;
	अटल u8 mt352_mclk_ratio[] = अणु 0x8b, 0x00 पूर्ण;
	अटल u8 mt352_adc_ctl_1_cfg[] = अणु 0x8E, 0x40 पूर्ण;
	अटल u8 mt352_agc_cfg[] = अणु 0x67, 0x10, 0xa0 पूर्ण;

	अटल u8 mt352_sec_agc_cfg1[] = अणु 0x6a, 0xff पूर्ण;
	अटल u8 mt352_sec_agc_cfg2[] = अणु 0x6d, 0xff पूर्ण;
	अटल u8 mt352_sec_agc_cfg3[] = अणु 0x70, 0x40 पूर्ण;
	अटल u8 mt352_sec_agc_cfg4[] = अणु 0x7b, 0x03 पूर्ण;
	अटल u8 mt352_sec_agc_cfg5[] = अणु 0x7d, 0x0f पूर्ण;

	अटल u8 mt352_acq_ctl[] = अणु 0x53, 0x50 पूर्ण;
	अटल u8 mt352_input_freq_1[] = अणु 0x56, 0x31, 0x06 पूर्ण;

	mt352_ग_लिखो(fe, mt352_घड़ी_config, माप(mt352_घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_reset, माप(mt352_reset));
	mt352_ग_लिखो(fe, mt352_mclk_ratio, माप(mt352_mclk_ratio));

	mt352_ग_लिखो(fe, mt352_adc_ctl_1_cfg, माप(mt352_adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, mt352_agc_cfg, माप(mt352_agc_cfg));

	mt352_ग_लिखो(fe, mt352_sec_agc_cfg1, माप(mt352_sec_agc_cfg1));
	mt352_ग_लिखो(fe, mt352_sec_agc_cfg2, माप(mt352_sec_agc_cfg2));
	mt352_ग_लिखो(fe, mt352_sec_agc_cfg3, माप(mt352_sec_agc_cfg3));
	mt352_ग_लिखो(fe, mt352_sec_agc_cfg4, माप(mt352_sec_agc_cfg4));
	mt352_ग_लिखो(fe, mt352_sec_agc_cfg5, माप(mt352_sec_agc_cfg5));

	mt352_ग_लिखो(fe, mt352_acq_ctl, माप(mt352_acq_ctl));
	mt352_ग_लिखो(fe, mt352_input_freq_1, माप(mt352_input_freq_1));

	वापस 0;
पूर्ण

अटल पूर्णांक umt_mt352_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा mt352_config umt_config;

	स_रखो(&umt_config,0,माप(काष्ठा mt352_config));
	umt_config.demod_init = umt_mt352_demod_init;
	umt_config.demod_address = 0xf;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &umt_config, &adap->dev->i2c_adap);

	वापस 0;
पूर्ण

अटल पूर्णांक umt_tuner_attach (काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x61, शून्य, DVB_PLL_TUA6034);
	वापस 0;
पूर्ण

/* USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties umt_properties;

अटल पूर्णांक umt_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (0 == dvb_usb_device_init(पूर्णांकf, &umt_properties,
				     THIS_MODULE, शून्य, adapter_nr))
		वापस 0;
	वापस -EINVAL;
पूर्ण

/* करो not change the order of the ID table */
अटल काष्ठा usb_device_id umt_table [] = अणु
/* 00 */	अणु USB_DEVICE(USB_VID_HANFTEK, USB_PID_HANFTEK_UMT_010_COLD) पूर्ण,
/* 01 */	अणु USB_DEVICE(USB_VID_HANFTEK, USB_PID_HANFTEK_UMT_010_WARM) पूर्ण,
			अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, umt_table);

अटल काष्ठा dvb_usb_device_properties umt_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = CYPRESS_FX2,
	.firmware = "dvb-usb-umt-010-02.fw",

	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = dibusb2_0_streaming_ctrl,
			.frontend_attach  = umt_mt352_frontend_attach,
			.tuner_attach     = umt_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = MAX_NO_URBS_FOR_DATA_STREAM,
				.endpoपूर्णांक = 0x06,
				.u = अणु
					.bulk = अणु
						.buffersize = 512,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
			.size_of_priv     = माप(काष्ठा dibusb_state),
		पूर्ण
	पूर्ण,
	.घातer_ctrl       = dibusb_घातer_ctrl,

	.i2c_algo         = &dibusb_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,

	.num_device_descs = 1,
	.devices = अणु
		अणु	"Hanftek UMT-010 DVB-T USB2.0",
			अणु &umt_table[0], शून्य पूर्ण,
			अणु &umt_table[1], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा usb_driver umt_driver = अणु
	.name		= "dvb_usb_umt_010",
	.probe		= umt_probe,
	.disconnect = dvb_usb_device_निकास,
	.id_table	= umt_table,
पूर्ण;

module_usb_driver(umt_driver);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for HanfTek UMT 010 USB2.0 DVB-T device");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
