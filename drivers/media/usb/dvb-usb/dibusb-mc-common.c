<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Common methods क्रम dibusb-based-receivers.
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#समावेश "dibusb.h"

MODULE_LICENSE("GPL");

/* 3000MC/P stuff */
// Config Adjacent channels  Perf -cal22
अटल काष्ठा dibx000_agc_config dib3000p_mt2060_agc_config = अणु
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (1 << 4) | (1 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 48497,
	.agc1_min = 23593,
	.agc2_max = 46531,
	.agc2_min = 24904,

	.agc1_pt1 = 0x65,
	.agc1_pt2 = 0x69,

	.agc1_slope1 = 0x51,
	.agc1_slope2 = 0x27,

	.agc2_pt1 = 0,
	.agc2_pt2 = 0x33,

	.agc2_slope1 = 0x35,
	.agc2_slope2 = 0x37,
पूर्ण;

अटल काष्ठा dib3000mc_config stk3000p_dib3000p_config = अणु
	&dib3000p_mt2060_agc_config,

	.max_समय     = 0x196,
	.ln_adc_level = 0x1cc7,

	.output_mpeg2_in_188_bytes = 1,

	.agc_command1 = 1,
	.agc_command2 = 1,
पूर्ण;

अटल काष्ठा dibx000_agc_config dib3000p_panasonic_agc_config = अणु
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (1 << 4) | (1 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 56361,
	.agc1_min = 22282,
	.agc2_max = 47841,
	.agc2_min = 36045,

	.agc1_pt1 = 0x3b,
	.agc1_pt2 = 0x6b,

	.agc1_slope1 = 0x55,
	.agc1_slope2 = 0x1d,

	.agc2_pt1 = 0,
	.agc2_pt2 = 0x0a,

	.agc2_slope1 = 0x95,
	.agc2_slope2 = 0x1e,
पूर्ण;

अटल काष्ठा dib3000mc_config mod3000p_dib3000p_config = अणु
	&dib3000p_panasonic_agc_config,

	.max_समय     = 0x51,
	.ln_adc_level = 0x1cc7,

	.output_mpeg2_in_188_bytes = 1,

	.agc_command1 = 1,
	.agc_command2 = 1,
पूर्ण;

पूर्णांक dibusb_dib3000mc_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	अगर (le16_to_cpu(adap->dev->udev->descriptor.idVenकरोr) == USB_VID_LITEON &&
	    le16_to_cpu(adap->dev->udev->descriptor.idProduct) ==
			USB_PID_LITEON_DVB_T_WARM) अणु
		msleep(1000);
	पूर्ण

	adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
					 &adap->dev->i2c_adap,
					 DEFAULT_DIB3000P_I2C_ADDRESS,
					 &mod3000p_dib3000p_config);
	अगर ((adap->fe_adap[0].fe) == शून्य)
		adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
						 &adap->dev->i2c_adap,
						 DEFAULT_DIB3000MC_I2C_ADDRESS,
						 &mod3000p_dib3000p_config);
	अगर ((adap->fe_adap[0].fe) != शून्य) अणु
		अगर (adap->priv != शून्य) अणु
			काष्ठा dibusb_state *st = adap->priv;
			st->ops.pid_parse = dib3000mc_pid_parse;
			st->ops.pid_ctrl  = dib3000mc_pid_control;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(dibusb_dib3000mc_frontend_attach);

अटल काष्ठा mt2060_config stk3000p_mt2060_config = अणु
	0x60
पूर्ण;

पूर्णांक dibusb_dib3000mc_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dibusb_state *st = adap->priv;
	u8 a,b;
	u16 अगर1 = 1220;
	काष्ठा i2c_adapter *tun_i2c;

	// First IF calibration क्रम Liteon Sticks
	अगर (le16_to_cpu(adap->dev->udev->descriptor.idVenकरोr) == USB_VID_LITEON &&
	    le16_to_cpu(adap->dev->udev->descriptor.idProduct) == USB_PID_LITEON_DVB_T_WARM) अणु

		dibusb_पढ़ो_eeprom_byte(adap->dev,0x7E,&a);
		dibusb_पढ़ो_eeprom_byte(adap->dev,0x7F,&b);

		अगर (a == 0x00)
			अगर1 += b;
		अन्यथा अगर (a == 0x80)
			अगर1 -= b;
		अन्यथा
			warn("LITE-ON DVB-T: Strange IF1 calibration :%2X %2X\n", a, b);

	पूर्ण अन्यथा अगर (le16_to_cpu(adap->dev->udev->descriptor.idVenकरोr) == USB_VID_DIBCOM &&
		   le16_to_cpu(adap->dev->udev->descriptor.idProduct) == USB_PID_DIBCOM_MOD3001_WARM) अणु
		u8 desc;
		dibusb_पढ़ो_eeprom_byte(adap->dev, 7, &desc);
		अगर (desc == 2) अणु
			a = 127;
			करो अणु
				dibusb_पढ़ो_eeprom_byte(adap->dev, a, &desc);
				a--;
			पूर्ण जबतक (a > 7 && (desc == 0xff || desc == 0x00));
			अगर (desc & 0x80)
				अगर1 -= (0xff - desc);
			अन्यथा
				अगर1 += desc;
		पूर्ण
	पूर्ण

	tun_i2c = dib3000mc_get_tuner_i2c_master(adap->fe_adap[0].fe, 1);
	अगर (dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c, &stk3000p_mt2060_config, अगर1) == शून्य) अणु
		/* not found - use panasonic pll parameters */
		अगर (dvb_attach(dvb_pll_attach, adap->fe_adap[0].fe, 0x60, tun_i2c, DVB_PLL_ENV57H1XD5) == शून्य)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		st->mt2060_present = 1;
		/* set the correct parameters क्रम the dib3000p */
		dib3000mc_set_config(adap->fe_adap[0].fe, &stk3000p_dib3000p_config);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dibusb_dib3000mc_tuner_attach);
