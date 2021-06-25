<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Linux driver क्रम devices based on the DiBcom DiB0700 USB bridge
 *
 *  Copyright (C) 2005-9 DiBcom, SA et al
 */
#समावेश "dib0700.h"

#समावेश "dib3000mc.h"
#समावेश "dib7000m.h"
#समावेश "dib7000p.h"
#समावेश "dib8000.h"
#समावेश "dib9000.h"
#समावेश "mt2060.h"
#समावेश "mt2266.h"
#समावेश "tuner-xc2028.h"
#समावेश "xc5000.h"
#समावेश "xc4000.h"
#समावेश "s5h1411.h"
#समावेश "dib0070.h"
#समावेश "dib0090.h"
#समावेश "lgdt3305.h"
#समावेश "mxl5007t.h"
#समावेश "mn88472.h"
#समावेश "tda18250.h"


अटल पूर्णांक क्रमce_lna_activation;
module_param(क्रमce_lna_activation, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_lna_activation, "force the activation of Low-Noise-Amplifier(s) (LNA), if applicable for the device (default: 0=automatic/off).");

काष्ठा dib0700_adapter_state अणु
	पूर्णांक (*set_param_save) (काष्ठा dvb_frontend *);
	स्थिर काष्ठा firmware *frontend_firmware;
	काष्ठा dib7000p_ops dib7000p_ops;
	काष्ठा dib8000_ops dib8000_ops;
पूर्ण;

/* Hauppauge Nova-T 500 (aka Bristol)
 *  has a LNA on GPIO0 which is enabled by setting 1 */
अटल काष्ठा mt2060_config bristol_mt2060_config[2] = अणु
	अणु
		.i2c_address = 0x60,
		.घड़ी_out   = 3,
	पूर्ण, अणु
		.i2c_address = 0x61,
	पूर्ण
पूर्ण;


अटल काष्ठा dibx000_agc_config bristol_dib3000p_mt2060_agc_config = अणु
	.band_caps = BAND_VHF | BAND_UHF,
	.setup     = (1 << 8) | (5 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (2 << 0),

	.agc1_max = 42598,
	.agc1_min = 17694,
	.agc2_max = 45875,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 59,

	.agc1_slope1 = 0,
	.agc1_slope2 = 69,

	.agc2_pt1 = 0,
	.agc2_pt2 = 59,

	.agc2_slope1 = 111,
	.agc2_slope2 = 28,
पूर्ण;

अटल काष्ठा dib3000mc_config bristol_dib3000mc_config[2] = अणु
	अणु	.agc          = &bristol_dib3000p_mt2060_agc_config,
		.max_समय     = 0x196,
		.ln_adc_level = 0x1cc7,
		.output_mpeg2_in_188_bytes = 1,
	पूर्ण,
	अणु	.agc          = &bristol_dib3000p_mt2060_agc_config,
		.max_समय     = 0x196,
		.ln_adc_level = 0x1cc7,
		.output_mpeg2_in_188_bytes = 1,
	पूर्ण
पूर्ण;

अटल पूर्णांक bristol_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	अगर (adap->id == 0) अणु
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msleep(10);

		अगर (क्रमce_lna_activation)
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
		अन्यथा
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);

		अगर (dib3000mc_i2c_क्रमागतeration(&adap->dev->i2c_adap, 2, DEFAULT_DIB3000P_I2C_ADDRESS, bristol_dib3000mc_config) != 0) अणु
			dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0); msleep(10);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	st->mt2060_अगर1[adap->id] = 1220;
	वापस (adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach, &adap->dev->i2c_adap,
		(10 + adap->id) << 1, &bristol_dib3000mc_config[adap->id])) == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक eeprom_पढ़ो(काष्ठा i2c_adapter *adap,u8 adrs,u8 *pval)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = 0x50, .flags = 0,        .buf = &adrs, .len = 1 पूर्ण,
		अणु .addr = 0x50, .flags = I2C_M_RD, .buf = pval,  .len = 1 पूर्ण,
	पूर्ण;
	अगर (i2c_transfer(adap, msg, 2) != 2) वापस -EREMOTEIO;
	वापस 0;
पूर्ण

अटल पूर्णांक bristol_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *prim_i2c = &adap->dev->i2c_adap;
	काष्ठा i2c_adapter *tun_i2c = dib3000mc_get_tuner_i2c_master(adap->fe_adap[0].fe, 1);
	s8 a;
	पूर्णांक अगर1=1220;
	अगर (adap->dev->udev->descriptor.idVenकरोr  == cpu_to_le16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descriptor.idProduct == cpu_to_le16(USB_PID_HAUPPAUGE_NOVA_T_500_2)) अणु
		अगर (!eeprom_पढ़ो(prim_i2c,0x59 + adap->id,&a)) अगर1=1220+a;
	पूर्ण
	वापस dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c,
			  &bristol_mt2060_config[adap->id], अगर1) == शून्य ?
			  -ENODEV : 0;
पूर्ण

/* STK7700D: Pinnacle/Terratec/Hauppauge Dual DVB-T Diversity */

/* MT226x */
अटल काष्ठा dibx000_agc_config stk7700d_7000p_mt2266_agc_config[2] = अणु
	अणु
		BAND_UHF,

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=2, P_agc_ग_लिखो=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8)
	    | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		1130,
		21,

		0,
		118,

		0,
		3530,
		1,
		0,

		65535,
		33770,
		65535,
		23592,

		0,
		62,
		255,
		64,
		64,
		132,
		192,
		80,
		80,

		17,
		27,
		23,
		51,

		1,
	पूर्ण, अणु
		BAND_VHF | BAND_LBAND,

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=2, P_agc_ग_लिखो=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8)
	    | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),

		2372,
		21,

		0,
		118,

		0,
		3530,
		1,
		0,

		65535,
		0,
		65535,
		23592,

		0,
		128,
		128,
		128,
		0,
		128,
		253,
		81,
		0,

		17,
		27,
		23,
		51,

		1,
	पूर्ण
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config stk7700d_mt2266_pll_config = अणु
	.पूर्णांकernal = 60000,
	.sampling = 30000,
	.pll_preभाग = 1,
	.pll_ratio = 8,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = 0,
	.timf = 20452225,
पूर्ण;

अटल काष्ठा dib7000p_config stk7700d_dib7000p_mt2266_config[] = अणु
	अणु	.output_mpeg2_in_188_bytes = 1,
		.hostbus_भागersity = 1,
		.tuner_is_baseband = 1,

		.agc_config_count = 2,
		.agc = stk7700d_7000p_mt2266_agc_config,
		.bw  = &stk7700d_mt2266_pll_config,

		.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,
	पूर्ण,
	अणु	.output_mpeg2_in_188_bytes = 1,
		.hostbus_भागersity = 1,
		.tuner_is_baseband = 1,

		.agc_config_count = 2,
		.agc = stk7700d_7000p_mt2266_agc_config,
		.bw  = &stk7700d_mt2266_pll_config,

		.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,
	पूर्ण
पूर्ण;

अटल काष्ठा mt2266_config stk7700d_mt2266_config[2] = अणु
	अणु	.i2c_address = 0x60
	पूर्ण,
	अणु	.i2c_address = 0x60
	पूर्ण
पूर्ण;

अटल पूर्णांक stk7700P2_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (adap->id == 0) अणु
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
		msleep(10);
		अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
					     stk7700d_dib7000p_mt2266_config)
		    != 0) अणु
			err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n", __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_ref);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			   0x80 + (adap->id << 1),
			   &stk7700d_dib7000p_mt2266_config[adap->id]);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk7700d_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (adap->id == 0) अणु
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
		अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 2, 18,
					     stk7700d_dib7000p_mt2266_config)
		    != 0) अणु
			err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n", __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_ref);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			   0x80 + (adap->id << 1),
			   &stk7700d_dib7000p_mt2266_config[adap->id]);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk7700d_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *tun_i2c;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
					    DIBX000_I2C_INTERFACE_TUNER, 1);
	वापस dvb_attach(mt2266_attach, adap->fe_adap[0].fe, tun_i2c,
		&stk7700d_mt2266_config[adap->id]) == शून्य ? -ENODEV : 0;
पूर्ण

/* STK7700-PH: Digital/Analog Hybrid Tuner, e.h. Cinergy HT USB HE */
अटल काष्ठा dibx000_agc_config xc3028_agc_config = अणु
	.band_caps = BAND_VHF | BAND_UHF,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=0,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
	 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=2, P_agc_ग_लिखो=0 */
	.setup = (0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),
	.inv_gain = 712,
	.समय_stabiliz = 21,
	.alpha_level = 0,
	.thlock = 118,
	.wbd_inv = 0,
	.wbd_ref = 2867,
	.wbd_sel = 0,
	.wbd_alpha = 2,
	.agc1_max = 0,
	.agc1_min = 0,
	.agc2_max = 39718,
	.agc2_min = 9930,
	.agc1_pt1 = 0,
	.agc1_pt2 = 0,
	.agc1_pt3 = 0,
	.agc1_slope1 = 0,
	.agc1_slope2 = 0,
	.agc2_pt1 = 0,
	.agc2_pt2 = 128,
	.agc2_slope1 = 29,
	.agc2_slope2 = 29,
	.alpha_mant = 17,
	.alpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.perक्रमm_agc_softsplit = 1,
पूर्ण;

/* PLL Configuration क्रम COFDM BW_MHz = 8.00 with बाह्यal घड़ी = 30.00 */
अटल काष्ठा dibx000_bandwidth_config xc3028_bw_config = अणु
	.पूर्णांकernal = 60000,
	.sampling = 30000,
	.pll_preभाग = 1,
	.pll_ratio = 8,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0), /* sad_cfg: refsel, sel, freq_15k */
	.अगरreq = (1 << 25) | 5816102,  /* अगरreq = 5.200000 MHz */
	.timf = 20452225,
	.xtal_hz = 30000000,
पूर्ण;

अटल काष्ठा dib7000p_config stk7700ph_dib7700_xc3028_config = अणु
	.output_mpeg2_in_188_bytes = 1,
	.tuner_is_baseband = 1,

	.agc_config_count = 1,
	.agc = &xc3028_agc_config,
	.bw  = &xc3028_bw_config,

	.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,
पूर्ण;

अटल पूर्णांक stk7700ph_xc3028_callback(व्योम *ptr, पूर्णांक component,
				     पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा dvb_usb_adapter *adap = ptr;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		/* Send the tuner in then out of reset */
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 0);
		msleep(10);
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);
		अवरोध;
	हाल XC2028_RESET_CLK:
	हाल XC2028_I2C_FLUSH:
		अवरोध;
	शेष:
		err("%s: unknown command %d, arg %d\n", __func__,
			command, arg);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xc2028_ctrl stk7700ph_xc3028_ctrl = अणु
	.fname = XC2028_DEFAULT_FIRMWARE,
	.max_len = 64,
	.demod = XC3028_FE_DIBCOM52,
पूर्ण;

अटल काष्ठा xc2028_config stk7700ph_xc3028_config = अणु
	.i2c_addr = 0x61,
	.ctrl = &stk7700ph_xc3028_ctrl,
पूर्ण;

अटल पूर्णांक stk7700ph_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा usb_device_descriptor *desc = &adap->dev->udev->descriptor;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (desc->idVenकरोr  == cpu_to_le16(USB_VID_PINNACLE) &&
	    desc->idProduct == cpu_to_le16(USB_PID_PINNACLE_EXPRESSCARD_320CX))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	अन्यथा
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
	msleep(10);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
				     &stk7700ph_dib7700_xc3028_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&stk7700ph_dib7700_xc3028_config);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk7700ph_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *tun_i2c;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
		DIBX000_I2C_INTERFACE_TUNER, 1);

	stk7700ph_xc3028_config.i2c_adap = tun_i2c;

	/* FIXME: generalize & move to common area */
	adap->fe_adap[0].fe->callback = stk7700ph_xc3028_callback;

	वापस dvb_attach(xc2028_attach, adap->fe_adap[0].fe, &stk7700ph_xc3028_config)
		== शून्य ? -ENODEV : 0;
पूर्ण

#घोषणा DEFAULT_RC_INTERVAL 50

/*
 * This function is used only when firmware is < 1.20 version. Newer
 * firmwares use bulk mode, with functions implemented at dib0700_core,
 * at dib0700_rc_urb_completion()
 */
अटल पूर्णांक dib0700_rc_query_old_firmware(काष्ठा dvb_usb_device *d)
अणु
	क्रमागत rc_proto protocol;
	u32 scancode;
	u8 toggle;
	पूर्णांक i;
	काष्ठा dib0700_state *st = d->priv;

	अगर (st->fw_version >= 0x10200) अणु
		/* For 1.20 firmware , We need to keep the RC polling
		   callback so we can reuse the input device setup in
		   dvb-usb-remote.c.  However, the actual work is being करोne
		   in the bulk URB completion handler. */
		वापस 0;
	पूर्ण

	st->buf[0] = REQUEST_POLL_RC;
	st->buf[1] = 0;

	i = dib0700_ctrl_rd(d, st->buf, 2, st->buf, 4);
	अगर (i <= 0) अणु
		err("RC Query Failed");
		वापस -EIO;
	पूर्ण

	/* losing half of KEY_0 events from Philipps rc5 remotes.. */
	अगर (st->buf[0] == 0 && st->buf[1] == 0
	    && st->buf[2] == 0 && st->buf[3] == 0)
		वापस 0;

	/* info("%d: %2X %2X %2X %2X",dvb_usb_dib0700_ir_proto,(पूर्णांक)st->buf[3 - 2],(पूर्णांक)st->buf[3 - 3],(पूर्णांक)st->buf[3 - 1],(पूर्णांक)st->buf[3]);  */

	dib0700_rc_setup(d, शून्य); /* reset ir sensor data to prevent false events */

	चयन (d->props.rc.core.protocol) अणु
	हाल RC_PROTO_BIT_NEC:
		/* NEC protocol sends repeat code as 0 0 0 FF */
		अगर ((st->buf[3 - 2] == 0x00) && (st->buf[3 - 3] == 0x00) &&
		    (st->buf[3] == 0xff)) अणु
			rc_repeat(d->rc_dev);
			वापस 0;
		पूर्ण

		protocol = RC_PROTO_NEC;
		scancode = RC_SCANCODE_NEC(st->buf[3 - 2], st->buf[3 - 3]);
		toggle = 0;
		अवरोध;

	शेष:
		/* RC-5 protocol changes toggle bit on new keypress */
		protocol = RC_PROTO_RC5;
		scancode = RC_SCANCODE_RC5(st->buf[3 - 2], st->buf[3 - 3]);
		toggle = st->buf[3 - 1];
		अवरोध;
	पूर्ण

	rc_keyकरोwn(d->rc_dev, protocol, scancode, toggle);
	वापस 0;
पूर्ण

/* STK7700P: Hauppauge Nova-T Stick, AVerMedia Volar */
अटल काष्ठा dibx000_agc_config stk7700p_7000m_mt2060_agc_config = अणु
	BAND_UHF | BAND_VHF,

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=2, P_agc_ग_लिखो=0 */
	(0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),

	712,
	41,

	0,
	118,

	0,
	4095,
	0,
	0,

	42598,
	17694,
	45875,
	2621,
	0,
	76,
	139,
	52,
	59,
	107,
	172,
	57,
	70,

	21,
	25,
	28,
	48,

	1,
	अणु  0,
	   107,
	   51800,
	   24700
	पूर्ण,
पूर्ण;

अटल काष्ठा dibx000_agc_config stk7700p_7000p_mt2060_agc_config = अणु
	.band_caps = BAND_UHF | BAND_VHF,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=2, P_agc_ग_लिखो=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0),
	.inv_gain = 712,
	.समय_stabiliz = 41,
	.alpha_level = 0,
	.thlock = 118,
	.wbd_inv = 0,
	.wbd_ref = 4095,
	.wbd_sel = 0,
	.wbd_alpha = 0,
	.agc1_max = 42598,
	.agc1_min = 16384,
	.agc2_max = 42598,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 137,
	.agc1_pt3 = 255,
	.agc1_slope1 = 0,
	.agc1_slope2 = 255,
	.agc2_pt1 = 0,
	.agc2_pt2 = 0,
	.agc2_slope1 = 0,
	.agc2_slope2 = 41,
	.alpha_mant = 15,
	.alpha_exp = 25,
	.beta_mant = 28,
	.beta_exp = 48,
	.perक्रमm_agc_softsplit = 0,
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config stk7700p_pll_config = अणु
	.पूर्णांकernal = 60000,
	.sampling = 30000,
	.pll_preभाग = 1,
	.pll_ratio = 8,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = 60258167,
	.timf = 20452225,
	.xtal_hz = 30000000,
पूर्ण;

अटल काष्ठा dib7000m_config stk7700p_dib7000m_config = अणु
	.dvbt_mode = 1,
	.output_mpeg2_in_188_bytes = 1,
	.quartz_direct = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000m_mt2060_agc_config,
	.bw  = &stk7700p_pll_config,

	.gpio_dir = DIB7000M_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000M_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAULT_PWM_POS,
पूर्ण;

अटल काष्ठा dib7000p_config stk7700p_dib7000p_config = अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000p_mt2060_agc_config,
	.bw  = &stk7700p_pll_config,

	.gpio_dir = DIB7000M_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000M_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAULT_PWM_POS,
पूर्ण;

अटल पूर्णांक stk7700p_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	/* unless there is no real घातer management in DVB - we leave the device on GPIO6 */

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msleep(50);

	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9,  GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msleep(10);
	dib0700_ctrl_घड़ी(adap->dev, 72, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msleep(100);

	dib0700_set_gpio(adap->dev,  GPIO0, GPIO_OUT, 1);

	st->mt2060_अगर1[0] = 1220;

	अगर (state->dib7000p_ops.dib7000pc_detection(&adap->dev->i2c_adap)) अणु
		adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 18, &stk7700p_dib7000p_config);
		st->is_dib7000pc = 1;
	पूर्ण अन्यथा अणु
		स_रखो(&state->dib7000p_ops, 0, माप(state->dib7000p_ops));
		adap->fe_adap[0].fe = dvb_attach(dib7000m_attach, &adap->dev->i2c_adap, 18, &stk7700p_dib7000m_config);
	पूर्ण

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल काष्ठा mt2060_config stk7700p_mt2060_config = अणु
	0x60
पूर्ण;

अटल पूर्णांक stk7700p_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *prim_i2c = &adap->dev->i2c_adap;
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा i2c_adapter *tun_i2c;
	काष्ठा dib0700_adapter_state *state = adap->priv;
	s8 a;
	पूर्णांक अगर1=1220;

	अगर (adap->dev->udev->descriptor.idVenकरोr  == cpu_to_le16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descriptor.idProduct == cpu_to_le16(USB_PID_HAUPPAUGE_NOVA_T_STICK)) अणु
		अगर (!eeprom_पढ़ो(prim_i2c,0x58,&a)) अगर1=1220+a;
	पूर्ण
	अगर (st->is_dib7000pc)
		tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);
	अन्यथा
		tun_i2c = dib7000m_get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);

	वापस dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c, &stk7700p_mt2060_config,
		अगर1) == शून्य ? -ENODEV : 0;
पूर्ण

/* DIB7070 generic */
अटल काष्ठा dibx000_agc_config dib7070_agc_config = अणु
	.band_caps = BAND_UHF | BAND_VHF | BAND_LBAND | BAND_SBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),
	.inv_gain = 600,
	.समय_stabiliz = 10,
	.alpha_level = 0,
	.thlock = 118,
	.wbd_inv = 0,
	.wbd_ref = 3530,
	.wbd_sel = 1,
	.wbd_alpha = 5,
	.agc1_max = 65535,
	.agc1_min = 0,
	.agc2_max = 65535,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 40,
	.agc1_pt3 = 183,
	.agc1_slope1 = 206,
	.agc1_slope2 = 255,
	.agc2_pt1 = 72,
	.agc2_pt2 = 152,
	.agc2_slope1 = 88,
	.agc2_slope2 = 90,
	.alpha_mant = 17,
	.alpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.perक्रमm_agc_softsplit = 0,
पूर्ण;

अटल पूर्णांक dib7070_tuner_reset(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	deb_info("reset: %d", onoff);
	वापस state->dib7000p_ops.set_gpio(fe, 8, 0, !onoff);
पूर्ण

अटल पूर्णांक dib7070_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	deb_info("sleep: %d", onoff);
	वापस state->dib7000p_ops.set_gpio(fe, 9, 0, onoff);
पूर्ण

अटल काष्ठा dib0070_config dib7070p_dib0070_config[2] = अणु
	अणु
		.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
		.reset = dib7070_tuner_reset,
		.sleep = dib7070_tuner_sleep,
		.घड़ी_khz = 12000,
		.घड़ी_pad_drive = 4,
		.अक्षरge_pump = 2,
	पूर्ण, अणु
		.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
		.reset = dib7070_tuner_reset,
		.sleep = dib7070_tuner_sleep,
		.घड़ी_khz = 12000,
		.अक्षरge_pump = 2,
	पूर्ण
पूर्ण;

अटल काष्ठा dib0070_config dib7770p_dib0070_config = अणु
	 .i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
	 .reset = dib7070_tuner_reset,
	 .sleep = dib7070_tuner_sleep,
	 .घड़ी_khz = 12000,
	 .घड़ी_pad_drive = 0,
	 .flip_chip = 1,
	 .अक्षरge_pump = 2,
पूर्ण;

अटल पूर्णांक dib7070_set_param_override(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	u16 offset;
	u8 band = BAND_OF_FREQUENCY(p->frequency/1000);
	चयन (band) अणु
		हाल BAND_VHF: offset = 950; अवरोध;
		हाल BAND_UHF:
		शेष: offset = 550; अवरोध;
	पूर्ण
	deb_info("WBD for DiB7000P: %d\n", offset + dib0070_wbd_offset(fe));
	state->dib7000p_ops.set_wbd_ref(fe, offset + dib0070_wbd_offset(fe));
	वापस state->set_param_save(fe);
पूर्ण

अटल पूर्णांक dib7770_set_param_override(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	u16 offset;
	u8 band = BAND_OF_FREQUENCY(p->frequency/1000);
	चयन (band) अणु
	हाल BAND_VHF:
		state->dib7000p_ops.set_gpio(fe, 0, 0, 1);
		offset = 850;
		अवरोध;
	हाल BAND_UHF:
	शेष:
		state->dib7000p_ops.set_gpio(fe, 0, 0, 0);
		offset = 250;
		अवरोध;
	पूर्ण
	deb_info("WBD for DiB7000P: %d\n", offset + dib0070_wbd_offset(fe));
	state->dib7000p_ops.set_wbd_ref(fe, offset + dib0070_wbd_offset(fe));
	वापस state->set_param_save(fe);
पूर्ण

अटल पूर्णांक dib7770p_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
			 DIBX000_I2C_INTERFACE_TUNER, 1);

	अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
		       &dib7770p_dib0070_config) == शून्य)
		वापस -ENODEV;

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7770_set_param_override;
	वापस 0;
पूर्ण

अटल पूर्णांक dib7070p_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);

	अगर (adap->id == 0) अणु
		अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[0]) == शून्य)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c, &dib7070p_dib0070_config[1]) == शून्य)
			वापस -ENODEV;
	पूर्ण

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7070_set_param_override;
	वापस 0;
पूर्ण

अटल पूर्णांक stk7700p_pid_filter(काष्ठा dvb_usb_adapter *adapter, पूर्णांक index,
		u16 pid, पूर्णांक onoff)
अणु
	काष्ठा dib0700_adapter_state *state = adapter->priv;
	काष्ठा dib0700_state *st = adapter->dev->priv;

	अगर (st->is_dib7000pc)
		वापस state->dib7000p_ops.pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
	वापस dib7000m_pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
पूर्ण

अटल पूर्णांक stk7700p_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adapter, पूर्णांक onoff)
अणु
	काष्ठा dib0700_state *st = adapter->dev->priv;
	काष्ठा dib0700_adapter_state *state = adapter->priv;
	अगर (st->is_dib7000pc)
		वापस state->dib7000p_ops.pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
	वापस dib7000m_pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
पूर्ण

अटल पूर्णांक stk70x0p_pid_filter(काष्ठा dvb_usb_adapter *adapter, पूर्णांक index, u16 pid, पूर्णांक onoff)
अणु
	काष्ठा dib0700_adapter_state *state = adapter->priv;
	वापस state->dib7000p_ops.pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
पूर्ण

अटल पूर्णांक stk70x0p_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adapter, पूर्णांक onoff)
अणु
	काष्ठा dib0700_adapter_state *state = adapter->priv;
	वापस state->dib7000p_ops.pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
पूर्ण

अटल काष्ठा dibx000_bandwidth_config dib7070_bw_config_12_mhz = अणु
	.पूर्णांकernal = 60000,
	.sampling = 15000,
	.pll_preभाग = 1,
	.pll_ratio = 20,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = (0 << 25) | 0,
	.timf = 20452225,
	.xtal_hz = 12000000,
पूर्ण;

अटल काष्ठा dib7000p_config dib7070p_dib7000p_config = अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tuner_is_baseband = 1,
	.spur_protect = 1,

	.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
पूर्ण;

/* STK7070P */
अटल पूर्णांक stk7070p_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा usb_device_descriptor *p = &adap->dev->udev->descriptor;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (p->idVenकरोr  == cpu_to_le16(USB_VID_PINNACLE) &&
	    p->idProduct == cpu_to_le16(USB_PID_PINNACLE_PCTV72E))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	अन्यथा
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
				     &dib7070p_dib7000p_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&dib7070p_dib7000p_config);
	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

/* STK7770P */
अटल काष्ठा dib7000p_config dib7770p_dib7000p_config = अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tuner_is_baseband = 1,
	.spur_protect = 1,

	.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
	.enable_current_mirror = 1,
	.disable_sample_and_hold = 0,
पूर्ण;

अटल पूर्णांक stk7770p_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा usb_device_descriptor *p = &adap->dev->udev->descriptor;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (p->idVenकरोr  == cpu_to_le16(USB_VID_PINNACLE) &&
	    p->idProduct == cpu_to_le16(USB_PID_PINNACLE_PCTV72E))
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	अन्यथा
		dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
				     &dib7770p_dib7000p_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80,
		&dib7770p_dib7000p_config);
	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

/* DIB807x generic */
अटल काष्ठा dibx000_agc_config dib807x_agc_config[2] = अणु
	अणु
		BAND_VHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		 * P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0,
		 * P_agc_inv_pwm2=0,P_agc_inh_dc_rv_est=0,
		 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5,
		 * P_agc_ग_लिखो=0 */
		(0 << 15) | (0 << 14) | (7 << 11) | (0 << 10) | (0 << 9) |
			(0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) |
			(0 << 0), /* setup*/

		600, /* inv_gain*/
		10,  /* समय_stabiliz*/

		0,  /* alpha_level*/
		118,  /* thlock*/

		0,     /* wbd_inv*/
		3530,  /* wbd_ref*/
		1,     /* wbd_sel*/
		5,     /* wbd_alpha*/

		65535,  /* agc1_max*/
		0,  /* agc1_min*/

		65535,  /* agc2_max*/
		0,      /* agc2_min*/

		0,      /* agc1_pt1*/
		40,     /* agc1_pt2*/
		183,    /* agc1_pt3*/
		206,    /* agc1_slope1*/
		255,    /* agc1_slope2*/
		72,     /* agc2_pt1*/
		152,    /* agc2_pt2*/
		88,     /* agc2_slope1*/
		90,     /* agc2_slope2*/

		17,  /* alpha_mant*/
		27,  /* alpha_exp*/
		23,  /* beta_mant*/
		51,  /* beta_exp*/

		0,  /* perक्रमm_agc_softsplit*/
	पूर्ण, अणु
		BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		 * P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0,
		 * P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
		 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5,
		 * P_agc_ग_लिखो=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (0 << 10) | (0 << 9) |
			(0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) |
			(0 << 0), /* setup */

		600, /* inv_gain*/
		10,  /* समय_stabiliz*/

		0,  /* alpha_level*/
		118,  /* thlock*/

		0,     /* wbd_inv*/
		3530,  /* wbd_ref*/
		1,     /* wbd_sel*/
		5,     /* wbd_alpha*/

		65535,  /* agc1_max*/
		0,  /* agc1_min*/

		65535,  /* agc2_max*/
		0,      /* agc2_min*/

		0,      /* agc1_pt1*/
		40,     /* agc1_pt2*/
		183,    /* agc1_pt3*/
		206,    /* agc1_slope1*/
		255,    /* agc1_slope2*/
		72,     /* agc2_pt1*/
		152,    /* agc2_pt2*/
		88,     /* agc2_slope1*/
		90,     /* agc2_slope2*/

		17,  /* alpha_mant*/
		27,  /* alpha_exp*/
		23,  /* beta_mant*/
		51,  /* beta_exp*/

		0,  /* perक्रमm_agc_softsplit*/
	पूर्ण
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib807x_bw_config_12_mhz = अणु
	.पूर्णांकernal = 60000,
	.sampling = 15000,
	.pll_preभाग = 1,
	.pll_ratio = 20,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (599 << 0),	/* sad_cfg: refsel, sel, freq_15k*/
	.अगरreq = (0 << 25) | 0,				/* अगरreq = 0.000000 MHz*/
	.timf = 18179755,
	.xtal_hz = 12000000,
पूर्ण;

अटल काष्ठा dib8000_config dib807x_dib8000_config[2] = अणु
	अणु
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 2,
		.agc = dib807x_agc_config,
		.pll = &dib807x_bw_config_12_mhz,
		.tuner_is_baseband = 1,

		.gpio_dir = DIB8000_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB8000_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB8000_GPIO_DEFAULT_PWM_POS,

		.hostbus_भागersity = 1,
		.भाग_cfg = 1,
		.agc_control = &dib0070_ctrl_agc_filter,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.drives = 0x2d98,
	पूर्ण, अणु
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 2,
		.agc = dib807x_agc_config,
		.pll = &dib807x_bw_config_12_mhz,
		.tuner_is_baseband = 1,

		.gpio_dir = DIB8000_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB8000_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB8000_GPIO_DEFAULT_PWM_POS,

		.hostbus_भागersity = 1,
		.agc_control = &dib0070_ctrl_agc_filter,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.drives = 0x2d98,
	पूर्ण
पूर्ण;

अटल पूर्णांक dib80xx_tuner_reset(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	वापस state->dib8000_ops.set_gpio(fe, 5, 0, !onoff);
पूर्ण

अटल पूर्णांक dib80xx_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	वापस state->dib8000_ops.set_gpio(fe, 0, 0, onoff);
पूर्ण

अटल स्थिर काष्ठा dib0070_wbd_gain_cfg dib8070_wbd_gain_cfg[] = अणु
    अणु 240,      7पूर्ण,
    अणु 0xffff,   6पूर्ण,
पूर्ण;

अटल काष्ठा dib0070_config dib807x_dib0070_config[2] = अणु
	अणु
		.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
		.reset = dib80xx_tuner_reset,
		.sleep = dib80xx_tuner_sleep,
		.घड़ी_khz = 12000,
		.घड़ी_pad_drive = 4,
		.vga_filter = 1,
		.क्रमce_crystal_mode = 1,
		.enable_third_order_filter = 1,
		.अक्षरge_pump = 0,
		.wbd_gain = dib8070_wbd_gain_cfg,
		.osc_buffer_state = 0,
		.freq_offset_khz_uhf = -100,
		.freq_offset_khz_vhf = -100,
	पूर्ण, अणु
		.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
		.reset = dib80xx_tuner_reset,
		.sleep = dib80xx_tuner_sleep,
		.घड़ी_khz = 12000,
		.घड़ी_pad_drive = 2,
		.vga_filter = 1,
		.क्रमce_crystal_mode = 1,
		.enable_third_order_filter = 1,
		.अक्षरge_pump = 0,
		.wbd_gain = dib8070_wbd_gain_cfg,
		.osc_buffer_state = 0,
		.freq_offset_khz_uhf = -25,
		.freq_offset_khz_vhf = -25,
	पूर्ण
पूर्ण;

अटल पूर्णांक dib807x_set_param_override(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	u16 offset = dib0070_wbd_offset(fe);
	u8 band = BAND_OF_FREQUENCY(p->frequency/1000);
	चयन (band) अणु
	हाल BAND_VHF:
		offset += 750;
		अवरोध;
	हाल BAND_UHF:  /* fall-thru wanted */
	शेष:
		offset += 250; अवरोध;
	पूर्ण
	deb_info("WBD for DiB8000: %d\n", offset);
	state->dib8000_ops.set_wbd_ref(fe, offset);

	वापस state->set_param_save(fe);
पूर्ण

अटल पूर्णांक dib807x_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib8000_ops.get_i2c_master(adap->fe_adap[0].fe,
			DIBX000_I2C_INTERFACE_TUNER, 1);

	अगर (adap->id == 0) अणु
		अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
				&dib807x_dib0070_config[0]) == शून्य)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (dvb_attach(dib0070_attach, adap->fe_adap[0].fe, tun_i2c,
				&dib807x_dib0070_config[1]) == शून्य)
			वापस -ENODEV;
	पूर्ण

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib807x_set_param_override;
	वापस 0;
पूर्ण

अटल पूर्णांक stk80xx_pid_filter(काष्ठा dvb_usb_adapter *adapter, पूर्णांक index,
	u16 pid, पूर्णांक onoff)
अणु
	काष्ठा dib0700_adapter_state *state = adapter->priv;

	वापस state->dib8000_ops.pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
पूर्ण

अटल पूर्णांक stk80xx_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adapter,
		पूर्णांक onoff)
अणु
	काष्ठा dib0700_adapter_state *state = adapter->priv;

	वापस state->dib8000_ops.pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
पूर्ण

/* STK807x */
अटल पूर्णांक stk807x_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18,
				0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

/* STK807xPVR */
अटल पूर्णांक stk807xpvr_frontend_attach0(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(500);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initialize IC 0 */
	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x22, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk807xpvr_frontend_attach1(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	/* initialize IC 1 */
	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x12, 0x82, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82,
			      &dib807x_dib8000_config[1]);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

/* STK8096GP */
अटल काष्ठा dibx000_agc_config dib8090_agc_config[2] = अणु
	अणु
	.band_caps = BAND_UHF | BAND_VHF | BAND_LBAND | BAND_SBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
	 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

	.inv_gain = 787,
	.समय_stabiliz = 10,

	.alpha_level = 0,
	.thlock = 118,

	.wbd_inv = 0,
	.wbd_ref = 3530,
	.wbd_sel = 1,
	.wbd_alpha = 5,

	.agc1_max = 65535,
	.agc1_min = 0,

	.agc2_max = 65535,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 32,
	.agc1_pt3 = 114,
	.agc1_slope1 = 143,
	.agc1_slope2 = 144,
	.agc2_pt1 = 114,
	.agc2_pt2 = 227,
	.agc2_slope1 = 116,
	.agc2_slope2 = 117,

	.alpha_mant = 28,
	.alpha_exp = 26,
	.beta_mant = 31,
	.beta_exp = 51,

	.perक्रमm_agc_softsplit = 0,
	पूर्ण,
	अणु
	.band_caps = BAND_CBAND,
	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
	 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8)
	| (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

	.inv_gain = 787,
	.समय_stabiliz = 10,

	.alpha_level = 0,
	.thlock = 118,

	.wbd_inv = 0,
	.wbd_ref = 3530,
	.wbd_sel = 1,
	.wbd_alpha = 5,

	.agc1_max = 0,
	.agc1_min = 0,

	.agc2_max = 65535,
	.agc2_min = 0,

	.agc1_pt1 = 0,
	.agc1_pt2 = 32,
	.agc1_pt3 = 114,
	.agc1_slope1 = 143,
	.agc1_slope2 = 144,
	.agc2_pt1 = 114,
	.agc2_pt2 = 227,
	.agc2_slope1 = 116,
	.agc2_slope2 = 117,

	.alpha_mant = 28,
	.alpha_exp = 26,
	.beta_mant = 31,
	.beta_exp = 51,

	.perक्रमm_agc_softsplit = 0,
	पूर्ण
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib8090_pll_config_12mhz = अणु
	.पूर्णांकernal = 54000,
	.sampling = 13500,

	.pll_preभाग = 1,
	.pll_ratio = 18,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,

	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,

	.sad_cfg = (3 << 14) | (1 << 12) | (599 << 0),

	.अगरreq = (0 << 25) | 0,
	.timf = 20199727,

	.xtal_hz = 12000000,
पूर्ण;

अटल पूर्णांक dib8090_get_adc_घातer(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	वापस state->dib8000_ops.get_adc_घातer(fe, 1);
पूर्ण

अटल व्योम dib8090_agc_control(काष्ठा dvb_frontend *fe, u8 restart)
अणु
	deb_info("AGC control callback: %i\n", restart);
	dib0090_dcc_freq(fe, restart);

	अगर (restart == 0) /* beक्रमe AGC startup */
		dib0090_set_dc_servo(fe, 1);
पूर्ण

अटल काष्ठा dib8000_config dib809x_dib8000_config[2] = अणु
	अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 2,
	.agc = dib8090_agc_config,
	.agc_control = dib8090_agc_control,
	.pll = &dib8090_pll_config_12mhz,
	.tuner_is_baseband = 1,

	.gpio_dir = DIB8000_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB8000_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB8000_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
	.भाग_cfg = 0x31,
	.output_mode = OUTMODE_MPEG2_FIFO,
	.drives = 0x2d98,
	.भागersity_delay = 48,
	.refclksel = 3,
	पूर्ण, अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 2,
	.agc = dib8090_agc_config,
	.agc_control = dib8090_agc_control,
	.pll = &dib8090_pll_config_12mhz,
	.tuner_is_baseband = 1,

	.gpio_dir = DIB8000_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB8000_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB8000_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
	.भाग_cfg = 0x31,
	.output_mode = OUTMODE_DIVERSITY,
	.drives = 0x2d08,
	.भागersity_delay = 1,
	.refclksel = 3,
	पूर्ण
पूर्ण;

अटल काष्ठा dib0090_wbd_slope dib8090_wbd_table[] = अणु
	/* max freq ; cold slope ; cold offset ; warm slope ; warm offset ; wbd gain */
	अणु 120,     0, 500,  0,   500, 4 पूर्ण, /* CBAND */
	अणु 170,     0, 450,  0,   450, 4 पूर्ण, /* CBAND */
	अणु 380,    48, 373, 28,   259, 6 पूर्ण, /* VHF */
	अणु 860,    34, 700, 36,   616, 6 पूर्ण, /* high UHF */
	अणु 0xFFFF, 34, 700, 36,   616, 6 पूर्ण, /* शेष */
पूर्ण;

अटल काष्ठा dib0090_config dib809x_dib0090_config = अणु
	.io.pll_bypass = 1,
	.io.pll_range = 1,
	.io.pll_preभाग = 1,
	.io.pll_loopभाग = 20,
	.io.adc_घड़ी_ratio = 8,
	.io.pll_पूर्णांक_loop_filt = 0,
	.io.घड़ी_khz = 12000,
	.reset = dib80xx_tuner_reset,
	.sleep = dib80xx_tuner_sleep,
	.clkouttobamse = 1,
	.analog_output = 1,
	.i2c_address = DEFAULT_DIB0090_I2C_ADDRESS,
	.use_pwm_agc = 1,
	.clkoutdrive = 1,
	.get_adc_घातer = dib8090_get_adc_घातer,
	.freq_offset_khz_uhf = -63,
	.freq_offset_khz_vhf = -143,
	.wbd = dib8090_wbd_table,
	.fref_घड़ी_ratio = 6,
पूर्ण;

अटल u8 dib8090_compute_pll_parameters(काष्ठा dvb_frontend *fe)
अणु
	u8 optimal_pll_ratio = 20;
	u32 freq_adc, ratio, rest, max = 0;
	u8 pll_ratio;

	क्रम (pll_ratio = 17; pll_ratio <= 20; pll_ratio++) अणु
		freq_adc = 12 * pll_ratio * (1 << 8) / 16;
		ratio = ((fe->dtv_property_cache.frequency / 1000) * (1 << 8) / 1000) / freq_adc;
		rest = ((fe->dtv_property_cache.frequency / 1000) * (1 << 8) / 1000) - ratio * freq_adc;

		अगर (rest > freq_adc / 2)
			rest = freq_adc - rest;
		deb_info("PLL ratio=%i rest=%i\n", pll_ratio, rest);
		अगर ((rest > max) && (rest > 717)) अणु
			optimal_pll_ratio = pll_ratio;
			max = rest;
		पूर्ण
	पूर्ण
	deb_info("optimal PLL ratio=%i\n", optimal_pll_ratio);

	वापस optimal_pll_ratio;
पूर्ण

अटल पूर्णांक dib8096_set_param_override(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;
	u8 pll_ratio, band = BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000);
	u16 target, ltgain, rf_gain_limit;
	u32 timf;
	पूर्णांक ret = 0;
	क्रमागत frontend_tune_state tune_state = CT_SHUTDOWN;

	चयन (band) अणु
	शेष:
		deb_info("Warning : Rf frequency  (%iHz) is not in the supported range, using VHF switch ", fe->dtv_property_cache.frequency);
		fallthrough;
	हाल BAND_VHF:
		state->dib8000_ops.set_gpio(fe, 3, 0, 1);
		अवरोध;
	हाल BAND_UHF:
		state->dib8000_ops.set_gpio(fe, 3, 0, 0);
		अवरोध;
	पूर्ण

	ret = state->set_param_save(fe);
	अगर (ret < 0)
		वापस ret;

	अगर (fe->dtv_property_cache.bandwidth_hz != 6000000) अणु
		deb_info("only 6MHz bandwidth is supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Update PLL अगर needed ratio */
	state->dib8000_ops.update_pll(fe, &dib8090_pll_config_12mhz, fe->dtv_property_cache.bandwidth_hz / 1000, 0);

	/* Get optimize PLL ratio to हटाओ spurious */
	pll_ratio = dib8090_compute_pll_parameters(fe);
	अगर (pll_ratio == 17)
		timf = 21387946;
	अन्यथा अगर (pll_ratio == 18)
		timf = 20199727;
	अन्यथा अगर (pll_ratio == 19)
		timf = 19136583;
	अन्यथा
		timf = 18179756;

	/* Update ratio */
	state->dib8000_ops.update_pll(fe, &dib8090_pll_config_12mhz, fe->dtv_property_cache.bandwidth_hz / 1000, pll_ratio);

	state->dib8000_ops.ctrl_timf(fe, DEMOD_TIMF_SET, timf);

	अगर (band != BAND_CBAND) अणु
		/* dib0090_get_wbd_target is वापसing any possible temperature compensated wbd-target */
		target = (dib0090_get_wbd_target(fe) * 8 * 18 / 33 + 1) / 2;
		state->dib8000_ops.set_wbd_ref(fe, target);
	पूर्ण

	अगर (band == BAND_CBAND) अणु
		deb_info("tuning in CBAND - soft-AGC startup\n");
		dib0090_set_tune_state(fe, CT_AGC_START);

		करो अणु
			ret = dib0090_gain_control(fe);
			msleep(ret);
			tune_state = dib0090_get_tune_state(fe);
			अगर (tune_state == CT_AGC_STEP_0)
				state->dib8000_ops.set_gpio(fe, 6, 0, 1);
			अन्यथा अगर (tune_state == CT_AGC_STEP_1) अणु
				dib0090_get_current_gain(fe, शून्य, शून्य, &rf_gain_limit, &ltgain);
				अगर (rf_gain_limit < 2000) /* activate the बाह्यal attenuator in हाल of very high input घातer */
					state->dib8000_ops.set_gpio(fe, 6, 0, 0);
			पूर्ण
		पूर्ण जबतक (tune_state < CT_AGC_STOP);

		deb_info("switching to PWM AGC\n");
		dib0090_pwm_gain_reset(fe);
		state->dib8000_ops.pwm_agc_reset(fe);
		state->dib8000_ops.set_tune_state(fe, CT_DEMOD_START);
	पूर्ण अन्यथा अणु
		/* क्रम everything अन्यथा than CBAND we are using standard AGC */
		deb_info("not tuning in CBAND - standard AGC startup\n");
		dib0090_pwm_gain_reset(fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib809x_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib8000_ops.get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);

	/* FIXME: अगर adap->id != 0, check अगर it is fe_adap[1] */
	अगर (!dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c, &dib809x_dib0090_config))
		वापस -ENODEV;

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib8096_set_param_override;
	वापस 0;
पूर्ण

अटल पूर्णांक stk809x_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 18, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80, &dib809x_dib8000_config[0]);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk809x_frontend1_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x10, 0x82, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82, &dib809x_dib8000_config[1]);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक nim8096md_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c;
	काष्ठा dvb_frontend *fe_slave  = st->dib8000_ops.get_slave_frontend(adap->fe_adap[0].fe, 1);

	अगर (fe_slave) अणु
		tun_i2c = st->dib8000_ops.get_i2c_master(fe_slave, DIBX000_I2C_INTERFACE_TUNER, 1);
		अगर (dvb_attach(dib0090_रेजिस्टर, fe_slave, tun_i2c, &dib809x_dib0090_config) == शून्य)
			वापस -ENODEV;
		fe_slave->dvb = adap->fe_adap[0].fe->dvb;
		fe_slave->ops.tuner_ops.set_params = dib8096_set_param_override;
	पूर्ण
	tun_i2c = st->dib8000_ops.get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_TUNER, 1);
	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c, &dib809x_dib0090_config) == शून्य)
		वापस -ENODEV;

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib8096_set_param_override;

	वापस 0;
पूर्ण

अटल पूर्णांक nim8096md_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_frontend *fe_slave;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(1000);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 2, 18, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80, &dib809x_dib8000_config[0]);
	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -ENODEV;

	/* Needed to increment refcount */
	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	fe_slave = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x82, &dib809x_dib8000_config[1]);
	state->dib8000_ops.set_slave_frontend(adap->fe_adap[0].fe, fe_slave);

	वापस fe_slave == शून्य ?  -ENODEV : 0;
पूर्ण

/* TFE8096P */
अटल काष्ठा dibx000_agc_config dib8096p_agc_config[2] = अणु
	अणु
		.band_caps		= BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		   P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0,
		   P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
		   P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5,
		   P_agc_ग_लिखो=0 */
		.setup			= (0 << 15) | (0 << 14) | (5 << 11)
			| (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5)
			| (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain		= 684,
		.समय_stabiliz	= 10,

		.alpha_level	= 0,
		.thlock			= 118,

		.wbd_inv		= 0,
		.wbd_ref		= 1200,
		.wbd_sel		= 3,
		.wbd_alpha		= 5,

		.agc1_max		= 65535,
		.agc1_min		= 0,

		.agc2_max		= 32767,
		.agc2_min		= 0,

		.agc1_pt1		= 0,
		.agc1_pt2		= 0,
		.agc1_pt3		= 105,
		.agc1_slope1	= 0,
		.agc1_slope2	= 156,
		.agc2_pt1		= 105,
		.agc2_pt2		= 255,
		.agc2_slope1	= 54,
		.agc2_slope2	= 0,

		.alpha_mant		= 28,
		.alpha_exp		= 26,
		.beta_mant		= 31,
		.beta_exp		= 51,

		.perक्रमm_agc_softsplit = 0,
	पूर्ण , अणु
		.band_caps		= BAND_FM | BAND_VHF | BAND_CBAND,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0,
		   P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0,
		   P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
		   P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5,
		   P_agc_ग_लिखो=0 */
		.setup			= (0 << 15) | (0 << 14) | (5 << 11)
			| (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5)
			| (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain		= 732,
		.समय_stabiliz  = 10,

		.alpha_level	= 0,
		.thlock			= 118,

		.wbd_inv		= 0,
		.wbd_ref		= 1200,
		.wbd_sel		= 3,
		.wbd_alpha		= 5,

		.agc1_max		= 65535,
		.agc1_min		= 0,

		.agc2_max		= 32767,
		.agc2_min		= 0,

		.agc1_pt1		= 0,
		.agc1_pt2		= 0,
		.agc1_pt3		= 98,
		.agc1_slope1	= 0,
		.agc1_slope2	= 167,
		.agc2_pt1		= 98,
		.agc2_pt2		= 255,
		.agc2_slope1	= 52,
		.agc2_slope2	= 0,

		.alpha_mant		= 28,
		.alpha_exp		= 26,
		.beta_mant		= 31,
		.beta_exp		= 51,

		.perक्रमm_agc_softsplit = 0,
	पूर्ण
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib8096p_घड़ी_config_12_mhz = अणु
	.पूर्णांकernal = 108000,
	.sampling = 13500,
	.pll_preभाग = 1,
	.pll_ratio = 9,
	.pll_range = 1,
	.pll_reset = 0,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 0,
	.ADClkSrc = 0,
	.modulo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = (0 << 25) | 0,
	.timf = 20199729,
	.xtal_hz = 12000000,
पूर्ण;

अटल काष्ठा dib8000_config tfe8096p_dib8000_config = अणु
	.output_mpeg2_in_188_bytes	= 1,
	.hostbus_भागersity			= 1,
	.update_lna					= शून्य,

	.agc_config_count			= 2,
	.agc						= dib8096p_agc_config,
	.pll						= &dib8096p_घड़ी_config_12_mhz,

	.gpio_dir					= DIB8000_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val					= DIB8000_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos				= DIB8000_GPIO_DEFAULT_PWM_POS,

	.agc_control				= शून्य,
	.भागersity_delay			= 48,
	.output_mode				= OUTMODE_MPEG2_FIFO,
	.enMpegOutput				= 1,
पूर्ण;

अटल काष्ठा dib0090_wbd_slope dib8096p_wbd_table[] = अणु
	अणु 380, 81, 850, 64, 540, 4पूर्ण,
	अणु 860, 51, 866, 21, 375, 4पूर्ण,
	अणु1700, 0, 250, 0, 100, 6पूर्ण,
	अणु2600, 0, 250, 0, 100, 6पूर्ण,
	अणु 0xFFFF, 0, 0, 0, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा dib0090_config tfe8096p_dib0090_config = अणु
	.io.घड़ी_khz			= 12000,
	.io.pll_bypass			= 0,
	.io.pll_range			= 0,
	.io.pll_preभाग			= 3,
	.io.pll_loopभाग			= 6,
	.io.adc_घड़ी_ratio		= 0,
	.io.pll_पूर्णांक_loop_filt	= 0,

	.freq_offset_khz_uhf	= -143,
	.freq_offset_khz_vhf	= -143,

	.get_adc_घातer			= dib8090_get_adc_घातer,

	.clkouttobamse			= 1,
	.analog_output			= 0,

	.wbd_vhf_offset			= 0,
	.wbd_cband_offset		= 0,
	.use_pwm_agc			= 1,
	.clkoutdrive			= 0,

	.fref_घड़ी_ratio		= 1,

	.ls_cfg_pad_drv			= 0,
	.data_tx_drv			= 0,
	.low_अगर					= शून्य,
	.in_soc					= 1,
	.क्रमce_cband_input		= 0,
पूर्ण;

काष्ठा dibx090p_adc अणु
	u32 freq;			/* RF freq MHz */
	u32 timf;			/* New Timf */
	u32 pll_loopभाग;	/* New preभाग */
	u32 pll_preभाग;		/* New loopभाग */
पूर्ण;

काष्ठा dibx090p_best_adc अणु
	u32 timf;
	u32 pll_loopभाग;
	u32 pll_preभाग;
पूर्ण;

अटल पूर्णांक dib8096p_get_best_sampling(काष्ठा dvb_frontend *fe, काष्ठा dibx090p_best_adc *adc)
अणु
	u8 spur = 0, preभाग = 0, loopभाग = 0, min_preभाग = 1, max_preभाग = 1;
	u16 xtal = 12000;
	u16 fcp_min = 1900;  /* PLL, Minimum Frequency of phase comparator (KHz) */
	u16 fcp_max = 20000; /* PLL, Maximum Frequency of phase comparator (KHz) */
	u32 fmem_max = 140000; /* 140MHz max SDRAM freq */
	u32 fdem_min = 66000;
	u32 fcp = 0, fs = 0, fdem = 0, fmem = 0;
	u32 harmonic_id = 0;

	adc->timf = 0;
	adc->pll_loopभाग = loopभाग;
	adc->pll_preभाग = preभाग;

	deb_info("bandwidth = %d", fe->dtv_property_cache.bandwidth_hz);

	/* Find Min and Max preभाग */
	जबतक ((xtal / max_preभाग) >= fcp_min)
		max_preभाग++;

	max_preभाग--;
	min_preभाग = max_preभाग;
	जबतक ((xtal / min_preभाग) <= fcp_max) अणु
		min_preभाग--;
		अगर (min_preभाग == 1)
			अवरोध;
	पूर्ण
	deb_info("MIN prediv = %d : MAX prediv = %d", min_preभाग, max_preभाग);

	min_preभाग = 1;

	क्रम (preभाग = min_preभाग; preभाग < max_preभाग; preभाग++) अणु
		fcp = xtal / preभाग;
		अगर (fcp > fcp_min && fcp < fcp_max) अणु
			क्रम (loopभाग = 1; loopभाग < 64; loopभाग++) अणु
				fmem = ((xtal/preभाग) * loopभाग);
				fdem = fmem / 2;
				fs   = fdem / 4;

				/* test min/max प्रणाली restrictions */
				अगर ((fdem >= fdem_min) && (fmem <= fmem_max) && (fs >= fe->dtv_property_cache.bandwidth_hz / 1000)) अणु
					spur = 0;
					/* test fs harmonics positions */
					क्रम (harmonic_id = (fe->dtv_property_cache.frequency / (1000 * fs));  harmonic_id <= ((fe->dtv_property_cache.frequency / (1000 * fs)) + 1); harmonic_id++) अणु
						अगर (((fs * harmonic_id) >= (fe->dtv_property_cache.frequency / 1000 - (fe->dtv_property_cache.bandwidth_hz / 2000))) &&  ((fs * harmonic_id) <= (fe->dtv_property_cache.frequency / 1000 + (fe->dtv_property_cache.bandwidth_hz / 2000)))) अणु
							spur = 1;
							अवरोध;
						पूर्ण
					पूर्ण

					अगर (!spur) अणु
						adc->pll_loopभाग = loopभाग;
						adc->pll_preभाग = preभाग;
						adc->timf = (4260880253U / fdem) * (1 << 8);
						adc->timf += ((4260880253U % fdem) << 8) / fdem;

						deb_info("RF %6d; BW %6d; Xtal %6d; Fmem %6d; Fdem %6d; Fs %6d; Prediv %2d; Loopdiv %2d; Timf %8d;", fe->dtv_property_cache.frequency, fe->dtv_property_cache.bandwidth_hz, xtal, fmem, fdem, fs, preभाग, loopभाग, adc->timf);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!spur)
			अवरोध;
	पूर्ण

	अगर (adc->pll_loopभाग == 0 && adc->pll_preभाग == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक dib8096p_agc_startup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा dibx000_bandwidth_config pll;
	काष्ठा dibx090p_best_adc adc;
	u16 target;
	पूर्णांक ret;

	ret = state->set_param_save(fe);
	अगर (ret < 0)
		वापस ret;
	स_रखो(&pll, 0, माप(काष्ठा dibx000_bandwidth_config));

	dib0090_pwm_gain_reset(fe);
	/* dib0090_get_wbd_target is वापसing any possible
	   temperature compensated wbd-target */
	target = (dib0090_get_wbd_target(fe) * 8  + 1) / 2;
	state->dib8000_ops.set_wbd_ref(fe, target);

	अगर (dib8096p_get_best_sampling(fe, &adc) == 0) अणु
		pll.pll_ratio  = adc.pll_loopभाग;
		pll.pll_preभाग = adc.pll_preभाग;

		dib0700_set_i2c_speed(adap->dev, 200);
		state->dib8000_ops.update_pll(fe, &pll, fe->dtv_property_cache.bandwidth_hz / 1000, 0);
		state->dib8000_ops.ctrl_timf(fe, DEMOD_TIMF_SET, adc.timf);
		dib0700_set_i2c_speed(adap->dev, 1000);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tfe8096p_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	u32 fw_version;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		वापस -ENODEV;

	dib0700_get_version(adap->dev, शून्य, शून्य, &fw_version, शून्य);
	अगर (fw_version >= 0x10200)
		st->fw_use_new_i2c_api = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	state->dib8000_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x10, 0x80, 1);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap,
					     0x80, &tfe8096p_dib8000_config);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक tfe8096p_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib8000_ops.get_i2c_tuner(adap->fe_adap[0].fe);

	tfe8096p_dib0090_config.reset = st->dib8000_ops.tuner_sleep;
	tfe8096p_dib0090_config.sleep = st->dib8000_ops.tuner_sleep;
	tfe8096p_dib0090_config.wbd = dib8096p_wbd_table;

	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c,
				&tfe8096p_dib0090_config) == शून्य)
		वापस -ENODEV;

	st->dib8000_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib8096p_agc_startup;
	वापस 0;
पूर्ण

/* STK9090M */
अटल पूर्णांक dib90x0_pid_filter(काष्ठा dvb_usb_adapter *adapter, पूर्णांक index, u16 pid, पूर्णांक onoff)
अणु
	वापस dib9000_fw_pid_filter(adapter->fe_adap[0].fe, index, pid, onoff);
पूर्ण

अटल पूर्णांक dib90x0_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adapter, पूर्णांक onoff)
अणु
	वापस dib9000_fw_pid_filter_ctrl(adapter->fe_adap[0].fe, onoff);
पूर्ण

अटल पूर्णांक dib90x0_tuner_reset(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	वापस dib9000_set_gpio(fe, 5, 0, !onoff);
पूर्ण

अटल पूर्णांक dib90x0_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	वापस dib9000_set_gpio(fe, 0, 0, onoff);
पूर्ण

अटल पूर्णांक dib01x0_pmu_update(काष्ठा i2c_adapter *i2c, u16 *data, u8 len)
अणु
	u8 wb[4] = अणु 0xc >> 8, 0xc & 0xff, 0, 0 पूर्ण;
	u8 rb[2];
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = 0x1e >> 1, .flags = 0, .buf = wb, .len = 2पूर्ण,
		अणु.addr = 0x1e >> 1, .flags = I2C_M_RD, .buf = rb, .len = 2पूर्ण,
	पूर्ण;
	u8 index_data;

	dibx000_i2c_set_speed(i2c, 250);

	अगर (i2c_transfer(i2c, msg, 2) != 2)
		वापस -EIO;

	चयन (rb[0] << 8 | rb[1]) अणु
	हाल 0:
			deb_info("Found DiB0170 rev1: This version of DiB0170 is not supported any longer.\n");
			वापस -EIO;
	हाल 1:
			deb_info("Found DiB0170 rev2");
			अवरोध;
	हाल 2:
			deb_info("Found DiB0190 rev2");
			अवरोध;
	शेष:
			deb_info("DiB01x0 not found");
			वापस -EIO;
	पूर्ण

	क्रम (index_data = 0; index_data < len; index_data += 2) अणु
		wb[2] = (data[index_data + 1] >> 8) & 0xff;
		wb[3] = (data[index_data + 1]) & 0xff;

		अगर (data[index_data] == 0) अणु
			wb[0] = (data[index_data] >> 8) & 0xff;
			wb[1] = (data[index_data]) & 0xff;
			msg[0].len = 2;
			अगर (i2c_transfer(i2c, msg, 2) != 2)
				वापस -EIO;
			wb[2] |= rb[0];
			wb[3] |= rb[1] & ~(3 << 4);
		पूर्ण

		wb[0] = (data[index_data] >> 8)&0xff;
		wb[1] = (data[index_data])&0xff;
		msg[0].len = 4;
		अगर (i2c_transfer(i2c, &msg[0], 1) != 1)
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा dib9000_config stk9090m_config = अणु
	.output_mpeg2_in_188_bytes = 1,
	.output_mode = OUTMODE_MPEG2_FIFO,
	.vcxo_समयr = 279620,
	.timing_frequency = 20452225,
	.demod_घड़ी_khz = 60000,
	.xtal_घड़ी_khz = 30000,
	.अगर_drives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
	.subband = अणु
		2,
		अणु
			अणु 240, अणु BOARD_GPIO_COMPONENT_DEMOD, BOARD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0008, 0x0000, 0x0008 पूर्ण पूर्ण, /* GPIO 3 to 1 क्रम VHF */
			अणु 890, अणु BOARD_GPIO_COMPONENT_DEMOD, BOARD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0008, 0x0000, 0x0000 पूर्ण पूर्ण, /* GPIO 3 to 0 क्रम UHF */
			अणु 0 पूर्ण,
		पूर्ण,
	पूर्ण,
	.gpio_function = अणु
		अणु .component = BOARD_GPIO_COMPONENT_DEMOD, .function = BOARD_GPIO_FUNCTION_COMPONENT_ON, .mask = 0x10 | 0x21, .direction = 0 & ~0x21, .value = (0x10 & ~0x1) | 0x20 पूर्ण,
		अणु .component = BOARD_GPIO_COMPONENT_DEMOD, .function = BOARD_GPIO_FUNCTION_COMPONENT_OFF, .mask = 0x10 | 0x21, .direction = 0 & ~0x21, .value = 0 | 0x21 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा dib9000_config nim9090md_config[2] = अणु
	अणु
		.output_mpeg2_in_188_bytes = 1,
		.output_mode = OUTMODE_MPEG2_FIFO,
		.vcxo_समयr = 279620,
		.timing_frequency = 20452225,
		.demod_घड़ी_khz = 60000,
		.xtal_घड़ी_khz = 30000,
		.अगर_drives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
	पूर्ण, अणु
		.output_mpeg2_in_188_bytes = 1,
		.output_mode = OUTMODE_DIVERSITY,
		.vcxo_समयr = 279620,
		.timing_frequency = 20452225,
		.demod_घड़ी_khz = 60000,
		.xtal_घड़ी_khz = 30000,
		.अगर_drives = (0 << 15) | (1 << 13) | (0 << 12) | (3 << 10) | (0 << 9) | (1 << 7) | (0 << 6) | (0 << 4) | (1 << 3) | (1 << 1) | (0),
		.subband = अणु
			2,
			अणु
				अणु 240, अणु BOARD_GPIO_COMPONENT_DEMOD, BOARD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0006, 0x0000, 0x0006 पूर्ण पूर्ण, /* GPIO 1 and 2 to 1 क्रम VHF */
				अणु 890, अणु BOARD_GPIO_COMPONENT_DEMOD, BOARD_GPIO_FUNCTION_SUBBAND_GPIO, 0x0006, 0x0000, 0x0000 पूर्ण पूर्ण, /* GPIO 1 and 2 to 0 क्रम UHF */
				अणु 0 पूर्ण,
			पूर्ण,
		पूर्ण,
		.gpio_function = अणु
			अणु .component = BOARD_GPIO_COMPONENT_DEMOD, .function = BOARD_GPIO_FUNCTION_COMPONENT_ON, .mask = 0x10 | 0x21, .direction = 0 & ~0x21, .value = (0x10 & ~0x1) | 0x20 पूर्ण,
			अणु .component = BOARD_GPIO_COMPONENT_DEMOD, .function = BOARD_GPIO_FUNCTION_COMPONENT_OFF, .mask = 0x10 | 0x21, .direction = 0 & ~0x21, .value = 0 | 0x21 पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dib0090_config dib9090_dib0090_config = अणु
	.io.pll_bypass = 0,
	.io.pll_range = 1,
	.io.pll_preभाग = 1,
	.io.pll_loopभाग = 8,
	.io.adc_घड़ी_ratio = 8,
	.io.pll_पूर्णांक_loop_filt = 0,
	.io.घड़ी_khz = 30000,
	.reset = dib90x0_tuner_reset,
	.sleep = dib90x0_tuner_sleep,
	.clkouttobamse = 0,
	.analog_output = 0,
	.use_pwm_agc = 0,
	.clkoutdrive = 0,
	.freq_offset_khz_uhf = 0,
	.freq_offset_khz_vhf = 0,
पूर्ण;

अटल काष्ठा dib0090_config nim9090md_dib0090_config[2] = अणु
	अणु
		.io.pll_bypass = 0,
		.io.pll_range = 1,
		.io.pll_preभाग = 1,
		.io.pll_loopभाग = 8,
		.io.adc_घड़ी_ratio = 8,
		.io.pll_पूर्णांक_loop_filt = 0,
		.io.घड़ी_khz = 30000,
		.reset = dib90x0_tuner_reset,
		.sleep = dib90x0_tuner_sleep,
		.clkouttobamse = 1,
		.analog_output = 0,
		.use_pwm_agc = 0,
		.clkoutdrive = 0,
		.freq_offset_khz_uhf = 0,
		.freq_offset_khz_vhf = 0,
	पूर्ण, अणु
		.io.pll_bypass = 0,
		.io.pll_range = 1,
		.io.pll_preभाग = 1,
		.io.pll_loopभाग = 8,
		.io.adc_घड़ी_ratio = 8,
		.io.pll_पूर्णांक_loop_filt = 0,
		.io.घड़ी_khz = 30000,
		.reset = dib90x0_tuner_reset,
		.sleep = dib90x0_tuner_sleep,
		.clkouttobamse = 0,
		.analog_output = 0,
		.use_pwm_agc = 0,
		.clkoutdrive = 0,
		.freq_offset_khz_uhf = 0,
		.freq_offset_khz_vhf = 0,
	पूर्ण
पूर्ण;


अटल पूर्णांक stk9090m_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा dib0700_state *st = adap->dev->priv;
	u32 fw_version;

	/* Make use of the new i2c functions from FW 1.20 */
	dib0700_get_version(adap->dev, शून्य, शून्य, &fw_version, शून्य);
	अगर (fw_version >= 0x10200)
		st->fw_use_new_i2c_api = 1;
	dib0700_set_i2c_speed(adap->dev, 340);

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	dib9000_i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x10, 0x80);

	अगर (request_firmware(&state->frontend_firmware, "dib9090.fw", &adap->dev->udev->dev)) अणु
		deb_info("%s: Upload failed. (file not found?)\n", __func__);
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		deb_info("%s: firmware read %zu bytes.\n", __func__, state->frontend_firmware->size);
	पूर्ण
	stk9090m_config.microcode_B_fe_size = state->frontend_firmware->size;
	stk9090m_config.microcode_B_fe_buffer = state->frontend_firmware->data;

	adap->fe_adap[0].fe = dvb_attach(dib9000_attach, &adap->dev->i2c_adap, 0x80, &stk9090m_config);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक dib9090_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा i2c_adapter *i2c = dib9000_get_tuner_पूर्णांकerface(adap->fe_adap[0].fe);
	u16 data_dib190[10] = अणु
		1, 0x1374,
		2, 0x01a2,
		7, 0x0020,
		0, 0x00ef,
		8, 0x0486,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_DVB_DIB9000))
		वापस -ENODEV;
	अगर (dvb_attach(dib0090_fw_रेजिस्टर, adap->fe_adap[0].fe, i2c, &dib9090_dib0090_config) == शून्य)
		वापस -ENODEV;
	i2c = dib9000_get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_GPIO_1_2, 0);
	अगर (!i2c)
		वापस -ENODEV;
	अगर (dib01x0_pmu_update(i2c, data_dib190, 10) != 0)
		वापस -ENODEV;
	dib0700_set_i2c_speed(adap->dev, 1500);
	अगर (dib9000_firmware_post_pll_init(adap->fe_adap[0].fe) < 0)
		वापस -ENODEV;
	release_firmware(state->frontend_firmware);
	वापस 0;
पूर्ण

अटल पूर्णांक nim9090md_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend *fe_slave;
	u32 fw_version;

	/* Make use of the new i2c functions from FW 1.20 */
	dib0700_get_version(adap->dev, शून्य, शून्य, &fw_version, शून्य);
	अगर (fw_version >= 0x10200)
		st->fw_use_new_i2c_api = 1;
	dib0700_set_i2c_speed(adap->dev, 340);

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (request_firmware(&state->frontend_firmware, "dib9090.fw", &adap->dev->udev->dev)) अणु
		deb_info("%s: Upload failed. (file not found?)\n", __func__);
		वापस -EIO;
	पूर्ण अन्यथा अणु
		deb_info("%s: firmware read %zu bytes.\n", __func__, state->frontend_firmware->size);
	पूर्ण
	nim9090md_config[0].microcode_B_fe_size = state->frontend_firmware->size;
	nim9090md_config[0].microcode_B_fe_buffer = state->frontend_firmware->data;
	nim9090md_config[1].microcode_B_fe_size = state->frontend_firmware->size;
	nim9090md_config[1].microcode_B_fe_buffer = state->frontend_firmware->data;

	dib9000_i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x20, 0x80);
	adap->fe_adap[0].fe = dvb_attach(dib9000_attach, &adap->dev->i2c_adap, 0x80, &nim9090md_config[0]);

	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -ENODEV;

	i2c = dib9000_get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_GPIO_3_4, 0);
	dib9000_i2c_क्रमागतeration(i2c, 1, 0x12, 0x82);

	fe_slave = dvb_attach(dib9000_attach, i2c, 0x82, &nim9090md_config[1]);
	dib9000_set_slave_frontend(adap->fe_adap[0].fe, fe_slave);

	वापस fe_slave == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक nim9090md_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend *fe_slave;
	u16 data_dib190[10] = अणु
		1, 0x5374,
		2, 0x01ae,
		7, 0x0020,
		0, 0x00ef,
		8, 0x0406,
	पूर्ण;
	अगर (!IS_ENABLED(CONFIG_DVB_DIB9000))
		वापस -ENODEV;
	i2c = dib9000_get_tuner_पूर्णांकerface(adap->fe_adap[0].fe);
	अगर (dvb_attach(dib0090_fw_रेजिस्टर, adap->fe_adap[0].fe, i2c, &nim9090md_dib0090_config[0]) == शून्य)
		वापस -ENODEV;
	i2c = dib9000_get_i2c_master(adap->fe_adap[0].fe, DIBX000_I2C_INTERFACE_GPIO_1_2, 0);
	अगर (!i2c)
		वापस -ENODEV;
	अगर (dib01x0_pmu_update(i2c, data_dib190, 10) < 0)
		वापस -ENODEV;

	dib0700_set_i2c_speed(adap->dev, 1500);
	अगर (dib9000_firmware_post_pll_init(adap->fe_adap[0].fe) < 0)
		वापस -ENODEV;

	fe_slave = dib9000_get_slave_frontend(adap->fe_adap[0].fe, 1);
	अगर (fe_slave != शून्य) अणु
		i2c = dib9000_get_component_bus_पूर्णांकerface(adap->fe_adap[0].fe);
		dib9000_set_i2c_adapter(fe_slave, i2c);

		i2c = dib9000_get_tuner_पूर्णांकerface(fe_slave);
		अगर (dvb_attach(dib0090_fw_रेजिस्टर, fe_slave, i2c, &nim9090md_dib0090_config[1]) == शून्य)
			वापस -ENODEV;
		fe_slave->dvb = adap->fe_adap[0].fe->dvb;
		dib9000_fw_set_component_bus_speed(adap->fe_adap[0].fe, 1500);
		अगर (dib9000_firmware_post_pll_init(fe_slave) < 0)
			वापस -ENODEV;
	पूर्ण
	release_firmware(state->frontend_firmware);

	वापस 0;
पूर्ण

/* NIM7090 */
अटल पूर्णांक dib7090p_get_best_sampling(काष्ठा dvb_frontend *fe , काष्ठा dibx090p_best_adc *adc)
अणु
	u8 spur = 0, preभाग = 0, loopभाग = 0, min_preभाग = 1, max_preभाग = 1;

	u16 xtal = 12000;
	u32 fcp_min = 1900;  /* PLL Minimum Frequency comparator KHz */
	u32 fcp_max = 20000; /* PLL Maximum Frequency comparator KHz */
	u32 fdem_max = 76000;
	u32 fdem_min = 69500;
	u32 fcp = 0, fs = 0, fdem = 0;
	u32 harmonic_id = 0;

	adc->pll_loopभाग = loopभाग;
	adc->pll_preभाग = preभाग;
	adc->timf = 0;

	deb_info("bandwidth = %d fdem_min =%d", fe->dtv_property_cache.bandwidth_hz, fdem_min);

	/* Find Min and Max preभाग */
	जबतक ((xtal/max_preभाग) >= fcp_min)
		max_preभाग++;

	max_preभाग--;
	min_preभाग = max_preभाग;
	जबतक ((xtal/min_preभाग) <= fcp_max) अणु
		min_preभाग--;
		अगर (min_preभाग == 1)
			अवरोध;
	पूर्ण
	deb_info("MIN prediv = %d : MAX prediv = %d", min_preभाग, max_preभाग);

	min_preभाग = 2;

	क्रम (preभाग = min_preभाग ; preभाग < max_preभाग; preभाग++) अणु
		fcp = xtal / preभाग;
		अगर (fcp > fcp_min && fcp < fcp_max) अणु
			क्रम (loopभाग = 1 ; loopभाग < 64 ; loopभाग++) अणु
				fdem = ((xtal/preभाग) * loopभाग);
				fs   = fdem / 4;
				/* test min/max प्रणाली restrictions */

				अगर ((fdem >= fdem_min) && (fdem <= fdem_max) && (fs >= fe->dtv_property_cache.bandwidth_hz/1000)) अणु
					spur = 0;
					/* test fs harmonics positions */
					क्रम (harmonic_id = (fe->dtv_property_cache.frequency / (1000*fs)) ;  harmonic_id <= ((fe->dtv_property_cache.frequency / (1000*fs))+1) ; harmonic_id++) अणु
						अगर (((fs*harmonic_id) >= ((fe->dtv_property_cache.frequency/1000) - (fe->dtv_property_cache.bandwidth_hz/2000))) &&  ((fs*harmonic_id) <= ((fe->dtv_property_cache.frequency/1000) + (fe->dtv_property_cache.bandwidth_hz/2000)))) अणु
							spur = 1;
							अवरोध;
						पूर्ण
					पूर्ण

					अगर (!spur) अणु
						adc->pll_loopभाग = loopभाग;
						adc->pll_preभाग = preभाग;
						adc->timf = 2396745143UL/fdem*(1 << 9);
						adc->timf += ((2396745143UL%fdem) << 9)/fdem;
						deb_info("loopdiv=%i prediv=%i timf=%i", loopभाग, preभाग, adc->timf);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!spur)
			अवरोध;
	पूर्ण


	अगर (adc->pll_loopभाग == 0 && adc->pll_preभाग == 0)
		वापस -EINVAL;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक dib7090_agc_startup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;
	काष्ठा dibx000_bandwidth_config pll;
	u16 target;
	काष्ठा dibx090p_best_adc adc;
	पूर्णांक ret;

	ret = state->set_param_save(fe);
	अगर (ret < 0)
		वापस ret;

	स_रखो(&pll, 0, माप(काष्ठा dibx000_bandwidth_config));
	dib0090_pwm_gain_reset(fe);
	target = (dib0090_get_wbd_target(fe) * 8 + 1) / 2;
	state->dib7000p_ops.set_wbd_ref(fe, target);

	अगर (dib7090p_get_best_sampling(fe, &adc) == 0) अणु
		pll.pll_ratio  = adc.pll_loopभाग;
		pll.pll_preभाग = adc.pll_preभाग;

		state->dib7000p_ops.update_pll(fe, &pll);
		state->dib7000p_ops.ctrl_timf(fe, DEMOD_TIMF_SET, adc.timf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib7090_agc_restart(काष्ठा dvb_frontend *fe, u8 restart)
अणु
	deb_info("AGC restart callback: %d", restart);
	अगर (restart == 0) /* beक्रमe AGC startup */
		dib0090_set_dc_servo(fe, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक tfe7790p_update_lna(काष्ठा dvb_frontend *fe, u16 agc_global)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	deb_info("update LNA: agc global=%i", agc_global);

	अगर (agc_global < 25000) अणु
		state->dib7000p_ops.set_gpio(fe, 8, 0, 0);
		state->dib7000p_ops.set_agc1_min(fe, 0);
	पूर्ण अन्यथा अणु
		state->dib7000p_ops.set_gpio(fe, 8, 0, 1);
		state->dib7000p_ops.set_agc1_min(fe, 32768);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dib0090_wbd_slope dib7090_wbd_table[] = अणु
	अणु 380,   81, 850, 64, 540,  4पूर्ण,
	अणु 860,   51, 866, 21,  375, 4पूर्ण,
	अणु1700,    0, 250, 0,   100, 6पूर्ण,
	अणु2600,    0, 250, 0,   100, 6पूर्ण,
	अणु 0xFFFF, 0,   0, 0,   0,   0पूर्ण,
पूर्ण;

अटल काष्ठा dibx000_agc_config dib7090_agc_config[2] = अणु
	अणु
		.band_caps      = BAND_UHF,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
		* P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0 */
		.setup          = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain       = 687,
		.समय_stabiliz  = 10,

		.alpha_level    = 0,
		.thlock         = 118,

		.wbd_inv        = 0,
		.wbd_ref        = 1200,
		.wbd_sel        = 3,
		.wbd_alpha      = 5,

		.agc1_max       = 65535,
		.agc1_min       = 32768,

		.agc2_max       = 65535,
		.agc2_min       = 0,

		.agc1_pt1       = 0,
		.agc1_pt2       = 32,
		.agc1_pt3       = 114,
		.agc1_slope1    = 143,
		.agc1_slope2    = 144,
		.agc2_pt1       = 114,
		.agc2_pt2       = 227,
		.agc2_slope1    = 116,
		.agc2_slope2    = 117,

		.alpha_mant     = 18,
		.alpha_exp      = 0,
		.beta_mant      = 20,
		.beta_exp       = 59,

		.perक्रमm_agc_softsplit = 0,
	पूर्ण , अणु
		.band_caps      = BAND_FM | BAND_VHF | BAND_CBAND,
		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=1, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
		* P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0 */
		.setup          = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),

		.inv_gain       = 732,
		.समय_stabiliz  = 10,

		.alpha_level    = 0,
		.thlock         = 118,

		.wbd_inv        = 0,
		.wbd_ref        = 1200,
		.wbd_sel        = 3,
		.wbd_alpha      = 5,

		.agc1_max       = 65535,
		.agc1_min       = 0,

		.agc2_max       = 65535,
		.agc2_min       = 0,

		.agc1_pt1       = 0,
		.agc1_pt2       = 0,
		.agc1_pt3       = 98,
		.agc1_slope1    = 0,
		.agc1_slope2    = 167,
		.agc2_pt1       = 98,
		.agc2_pt2       = 255,
		.agc2_slope1    = 104,
		.agc2_slope2    = 0,

		.alpha_mant     = 18,
		.alpha_exp      = 0,
		.beta_mant      = 20,
		.beta_exp       = 59,

		.perक्रमm_agc_softsplit = 0,
	पूर्ण
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib7090_घड़ी_config_12_mhz = अणु
	.पूर्णांकernal = 60000,
	.sampling = 15000,
	.pll_preभाग = 1,
	.pll_ratio = 5,
	.pll_range = 0,
	.pll_reset = 0,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = (0 << 25) | 0,
	.timf = 20452225,
	.xtal_hz = 15000000,
पूर्ण;

अटल काष्ठा dib7000p_config nim7090_dib7000p_config = अणु
	.output_mpeg2_in_188_bytes  = 1,
	.hostbus_भागersity			= 1,
	.tuner_is_baseband			= 1,
	.update_lna					= tfe7790p_update_lna, /* GPIO used is the same as TFE7790 */

	.agc_config_count			= 2,
	.agc						= dib7090_agc_config,

	.bw							= &dib7090_घड़ी_config_12_mhz,

	.gpio_dir					= DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val					= DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos				= DIB7000P_GPIO_DEFAULT_PWM_POS,

	.pwm_freq_भाग				= 0,

	.agc_control				= dib7090_agc_restart,

	.spur_protect				= 0,
	.disable_sample_and_hold	= 0,
	.enable_current_mirror		= 0,
	.भागersity_delay			= 0,

	.output_mode				= OUTMODE_MPEG2_FIFO,
	.enMpegOutput				= 1,
पूर्ण;

अटल पूर्णांक tfe7090p_pvr_update_lna(काष्ठा dvb_frontend *fe, u16 agc_global)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	deb_info("TFE7090P-PVR update LNA: agc global=%i", agc_global);
	अगर (agc_global < 25000) अणु
		state->dib7000p_ops.set_gpio(fe, 5, 0, 0);
		state->dib7000p_ops.set_agc1_min(fe, 0);
	पूर्ण अन्यथा अणु
		state->dib7000p_ops.set_gpio(fe, 5, 0, 1);
		state->dib7000p_ops.set_agc1_min(fe, 32768);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dib7000p_config tfe7090pvr_dib7000p_config[2] = अणु
	अणु
		.output_mpeg2_in_188_bytes  = 1,
		.hostbus_भागersity			= 1,
		.tuner_is_baseband			= 1,
		.update_lna					= tfe7090p_pvr_update_lna,

		.agc_config_count			= 2,
		.agc						= dib7090_agc_config,

		.bw							= &dib7090_घड़ी_config_12_mhz,

		.gpio_dir					= DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val					= DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos				= DIB7000P_GPIO_DEFAULT_PWM_POS,

		.pwm_freq_भाग				= 0,

		.agc_control				= dib7090_agc_restart,

		.spur_protect				= 0,
		.disable_sample_and_hold	= 0,
		.enable_current_mirror		= 0,
		.भागersity_delay			= 0,

		.output_mode				= OUTMODE_MPEG2_PAR_GATED_CLK,
		.शेष_i2c_addr			= 0x90,
		.enMpegOutput				= 1,
	पूर्ण, अणु
		.output_mpeg2_in_188_bytes  = 1,
		.hostbus_भागersity			= 1,
		.tuner_is_baseband			= 1,
		.update_lna					= tfe7090p_pvr_update_lna,

		.agc_config_count			= 2,
		.agc						= dib7090_agc_config,

		.bw							= &dib7090_घड़ी_config_12_mhz,

		.gpio_dir					= DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val					= DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos				= DIB7000P_GPIO_DEFAULT_PWM_POS,

		.pwm_freq_भाग				= 0,

		.agc_control				= dib7090_agc_restart,

		.spur_protect				= 0,
		.disable_sample_and_hold	= 0,
		.enable_current_mirror		= 0,
		.भागersity_delay			= 0,

		.output_mode				= OUTMODE_MPEG2_PAR_GATED_CLK,
		.शेष_i2c_addr			= 0x92,
		.enMpegOutput				= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा dib0090_config nim7090_dib0090_config = अणु
	.io.घड़ी_khz = 12000,
	.io.pll_bypass = 0,
	.io.pll_range = 0,
	.io.pll_preभाग = 3,
	.io.pll_loopभाग = 6,
	.io.adc_घड़ी_ratio = 0,
	.io.pll_पूर्णांक_loop_filt = 0,

	.freq_offset_khz_uhf = 0,
	.freq_offset_khz_vhf = 0,

	.clkouttobamse = 1,
	.analog_output = 0,

	.wbd_vhf_offset = 0,
	.wbd_cband_offset = 0,
	.use_pwm_agc = 1,
	.clkoutdrive = 0,

	.fref_घड़ी_ratio = 0,

	.wbd = dib7090_wbd_table,

	.ls_cfg_pad_drv = 0,
	.data_tx_drv = 0,
	.low_अगर = शून्य,
	.in_soc = 1,
पूर्ण;

अटल काष्ठा dib7000p_config tfe7790p_dib7000p_config = अणु
	.output_mpeg2_in_188_bytes  = 1,
	.hostbus_भागersity			= 1,
	.tuner_is_baseband			= 1,
	.update_lna					= tfe7790p_update_lna,

	.agc_config_count			= 2,
	.agc						= dib7090_agc_config,

	.bw							= &dib7090_घड़ी_config_12_mhz,

	.gpio_dir					= DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val					= DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos				= DIB7000P_GPIO_DEFAULT_PWM_POS,

	.pwm_freq_भाग				= 0,

	.agc_control				= dib7090_agc_restart,

	.spur_protect				= 0,
	.disable_sample_and_hold	= 0,
	.enable_current_mirror		= 0,
	.भागersity_delay			= 0,

	.output_mode				= OUTMODE_MPEG2_PAR_GATED_CLK,
	.enMpegOutput				= 1,
पूर्ण;

अटल काष्ठा dib0090_config tfe7790p_dib0090_config = अणु
	.io.घड़ी_khz = 12000,
	.io.pll_bypass = 0,
	.io.pll_range = 0,
	.io.pll_preभाग = 3,
	.io.pll_loopभाग = 6,
	.io.adc_घड़ी_ratio = 0,
	.io.pll_पूर्णांक_loop_filt = 0,

	.freq_offset_khz_uhf = 0,
	.freq_offset_khz_vhf = 0,

	.clkouttobamse = 1,
	.analog_output = 0,

	.wbd_vhf_offset = 0,
	.wbd_cband_offset = 0,
	.use_pwm_agc = 1,
	.clkoutdrive = 0,

	.fref_घड़ी_ratio = 0,

	.wbd = dib7090_wbd_table,

	.ls_cfg_pad_drv = 0,
	.data_tx_drv = 0,
	.low_अगर = शून्य,
	.in_soc = 1,
	.क्रमce_cband_input = 0,
	.is_dib7090e = 0,
	.क्रमce_crystal_mode = 1,
पूर्ण;

अटल काष्ठा dib0090_config tfe7090pvr_dib0090_config[2] = अणु
	अणु
		.io.घड़ी_khz = 12000,
		.io.pll_bypass = 0,
		.io.pll_range = 0,
		.io.pll_preभाग = 3,
		.io.pll_loopभाग = 6,
		.io.adc_घड़ी_ratio = 0,
		.io.pll_पूर्णांक_loop_filt = 0,

		.freq_offset_khz_uhf = 50,
		.freq_offset_khz_vhf = 70,

		.clkouttobamse = 1,
		.analog_output = 0,

		.wbd_vhf_offset = 0,
		.wbd_cband_offset = 0,
		.use_pwm_agc = 1,
		.clkoutdrive = 0,

		.fref_घड़ी_ratio = 0,

		.wbd = dib7090_wbd_table,

		.ls_cfg_pad_drv = 0,
		.data_tx_drv = 0,
		.low_अगर = शून्य,
		.in_soc = 1,
	पूर्ण, अणु
		.io.घड़ी_khz = 12000,
		.io.pll_bypass = 0,
		.io.pll_range = 0,
		.io.pll_preभाग = 3,
		.io.pll_loopभाग = 6,
		.io.adc_घड़ी_ratio = 0,
		.io.pll_पूर्णांक_loop_filt = 0,

		.freq_offset_khz_uhf = -50,
		.freq_offset_khz_vhf = -70,

		.clkouttobamse = 1,
		.analog_output = 0,

		.wbd_vhf_offset = 0,
		.wbd_cband_offset = 0,
		.use_pwm_agc = 1,
		.clkoutdrive = 0,

		.fref_घड़ी_ratio = 0,

		.wbd = dib7090_wbd_table,

		.ls_cfg_pad_drv = 0,
		.data_tx_drv = 0,
		.low_अगर = शून्य,
		.in_soc = 1,
	पूर्ण
पूर्ण;

अटल पूर्णांक nim7090_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x10, &nim7090_dib7000p_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80, &nim7090_dib7000p_config);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक nim7090_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_tuner(adap->fe_adap[0].fe);

	nim7090_dib0090_config.reset = st->dib7000p_ops.tuner_sleep;
	nim7090_dib0090_config.sleep = st->dib7000p_ops.tuner_sleep;
	nim7090_dib0090_config.get_adc_घातer = st->dib7000p_ops.get_adc_घातer;

	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c, &nim7090_dib0090_config) == शून्य)
		वापस -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7090_agc_startup;
	वापस 0;
पूर्ण

अटल पूर्णांक tfe7090pvr_frontend0_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	/* The TFE7090 requires the dib0700 to not be in master mode */
	st->disable_streaming_master_mode = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initialize IC 0 */
	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 1, 0x20, &tfe7090pvr_dib7000p_config[0]) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	dib0700_set_i2c_speed(adap->dev, 340);
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x90, &tfe7090pvr_dib7000p_config[0]);
	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -ENODEV;

	state->dib7000p_ops.slave_reset(adap->fe_adap[0].fe);

	वापस 0;
पूर्ण

अटल पूर्णांक tfe7090pvr_frontend1_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (adap->dev->adapter[0].fe_adap[0].fe == शून्य) अणु
		err("the master dib7090 has to be initialized first");
		वापस -ENODEV; /* the master device has not been initialized */
	पूर्ण

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	i2c = state->dib7000p_ops.get_i2c_master(adap->dev->adapter[0].fe_adap[0].fe, DIBX000_I2C_INTERFACE_GPIO_6_7, 1);
	अगर (state->dib7000p_ops.i2c_क्रमागतeration(i2c, 1, 0x10, &tfe7090pvr_dib7000p_config[1]) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n", __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(i2c, 0x92, &tfe7090pvr_dib7000p_config[1]);
	dib0700_set_i2c_speed(adap->dev, 200);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक tfe7090pvr_tuner0_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_tuner(adap->fe_adap[0].fe);

	tfe7090pvr_dib0090_config[0].reset = st->dib7000p_ops.tuner_sleep;
	tfe7090pvr_dib0090_config[0].sleep = st->dib7000p_ops.tuner_sleep;
	tfe7090pvr_dib0090_config[0].get_adc_घातer = st->dib7000p_ops.get_adc_घातer;

	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c, &tfe7090pvr_dib0090_config[0]) == शून्य)
		वापस -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7090_agc_startup;
	वापस 0;
पूर्ण

अटल पूर्णांक tfe7090pvr_tuner1_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c = st->dib7000p_ops.get_i2c_tuner(adap->fe_adap[0].fe);

	tfe7090pvr_dib0090_config[1].reset = st->dib7000p_ops.tuner_sleep;
	tfe7090pvr_dib0090_config[1].sleep = st->dib7000p_ops.tuner_sleep;
	tfe7090pvr_dib0090_config[1].get_adc_घातer = st->dib7000p_ops.get_adc_घातer;

	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c, &tfe7090pvr_dib0090_config[1]) == शून्य)
		वापस -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7090_agc_startup;
	वापस 0;
पूर्ण

अटल पूर्णांक tfe7790p_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	/* The TFE7790P requires the dib0700 to not be in master mode */
	st->disable_streaming_master_mode = 1;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(20);
	dib0700_ctrl_घड़ी(adap->dev, 72, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(20);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap,
				1, 0x10, &tfe7790p_dib7000p_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
				__func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण
	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap,
			0x80, &tfe7790p_dib7000p_config);

	वापस adap->fe_adap[0].fe == शून्य ?  -ENODEV : 0;
पूर्ण

अटल पूर्णांक tfe7790p_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *st = adap->priv;
	काष्ठा i2c_adapter *tun_i2c =
		st->dib7000p_ops.get_i2c_tuner(adap->fe_adap[0].fe);


	tfe7790p_dib0090_config.reset = st->dib7000p_ops.tuner_sleep;
	tfe7790p_dib0090_config.sleep = st->dib7000p_ops.tuner_sleep;
	tfe7790p_dib0090_config.get_adc_घातer = st->dib7000p_ops.get_adc_घातer;

	अगर (dvb_attach(dib0090_रेजिस्टर, adap->fe_adap[0].fe, tun_i2c,
				&tfe7790p_dib0090_config) == शून्य)
		वापस -ENODEV;

	st->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);

	st->set_param_save = adap->fe_adap[0].fe->ops.tuner_ops.set_params;
	adap->fe_adap[0].fe->ops.tuner_ops.set_params = dib7090_agc_startup;
	वापस 0;
पूर्ण

/* STK7070PD */
अटल काष्ठा dib7000p_config stk7070pd_dib7000p_config[2] = अणु
	अणु
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 1,
		.agc = &dib7070_agc_config,
		.bw  = &dib7070_bw_config_12_mhz,
		.tuner_is_baseband = 1,
		.spur_protect = 1,

		.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

		.hostbus_भागersity = 1,
	पूर्ण, अणु
		.output_mpeg2_in_188_bytes = 1,

		.agc_config_count = 1,
		.agc = &dib7070_agc_config,
		.bw  = &dib7070_bw_config_12_mhz,
		.tuner_is_baseband = 1,
		.spur_protect = 1,

		.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
		.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
		.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

		.hostbus_भागersity = 1,
	पूर्ण
पूर्ण;

अटल व्योम stk7070pd_init(काष्ठा dvb_usb_device *dev)
अणु
	dib0700_set_gpio(dev, GPIO6, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_घड़ी(dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(dev, GPIO10, GPIO_OUT, 1);
पूर्ण

अटल पूर्णांक stk7070pd_frontend_attach0(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	stk7070pd_init(adap->dev);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	अगर (state->dib7000p_ops.i2c_क्रमागतeration(&adap->dev->i2c_adap, 2, 18,
				     stk7070pd_dib7000p_config) != 0) अणु
		err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
		    __func__);
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x80, &stk7070pd_dib7000p_config[0]);
	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक stk7070pd_frontend_attach1(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x82, &stk7070pd_dib7000p_config[1]);
	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक novatd_पढ़ो_status_override(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_status *stat)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dvb_usb_device *dev = adap->dev;
	काष्ठा dib0700_state *state = dev->priv;
	पूर्णांक ret;

	ret = state->पढ़ो_status(fe, stat);

	अगर (!ret)
		dib0700_set_gpio(dev, adap->id == 0 ? GPIO1 : GPIO0, GPIO_OUT,
				!!(*stat & FE_HAS_LOCK));

	वापस ret;
पूर्ण

अटल पूर्णांक novatd_sleep_override(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;
	काष्ठा dvb_usb_device *dev = adap->dev;
	काष्ठा dib0700_state *state = dev->priv;

	/* turn off LED */
	dib0700_set_gpio(dev, adap->id == 0 ? GPIO1 : GPIO0, GPIO_OUT, 0);

	वापस state->sleep(fe);
पूर्ण

/*
 * novatd_frontend_attach - Nova-TD specअगरic attach
 *
 * Nova-TD has GPIO0, 1 and 2 क्रम LEDs. So करो not fiddle with them except क्रम
 * inक्रमmation purposes.
 */
अटल पूर्णांक novatd_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *dev = adap->dev;
	काष्ठा dib0700_state *st = dev->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	अगर (adap->id == 0) अणु
		stk7070pd_init(dev);

		/* turn the घातer LED on, the other two off (just in हाल) */
		dib0700_set_gpio(dev, GPIO0, GPIO_OUT, 0);
		dib0700_set_gpio(dev, GPIO1, GPIO_OUT, 0);
		dib0700_set_gpio(dev, GPIO2, GPIO_OUT, 1);

		अगर (state->dib7000p_ops.i2c_क्रमागतeration(&dev->i2c_adap, 2, 18,
					     stk7070pd_dib7000p_config) != 0) अणु
			err("%s: state->dib7000p_ops.i2c_enumeration failed.  Cannot continue\n",
			    __func__);
			dvb_detach(state->dib7000p_ops.set_wbd_ref);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&dev->i2c_adap,
			adap->id == 0 ? 0x80 : 0x82,
			&stk7070pd_dib7000p_config[adap->id]);

	अगर (adap->fe_adap[0].fe == शून्य)
		वापस -ENODEV;

	st->पढ़ो_status = adap->fe_adap[0].fe->ops.पढ़ो_status;
	adap->fe_adap[0].fe->ops.पढ़ो_status = novatd_पढ़ो_status_override;
	st->sleep = adap->fe_adap[0].fe->ops.sleep;
	adap->fe_adap[0].fe->ops.sleep = novatd_sleep_override;

	वापस 0;
पूर्ण

/* S5H1411 */
अटल काष्ठा s5h1411_config pinnacle_801e_config = अणु
	.output_mode   = S5H1411_PARALLEL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.mpeg_timing   = S5H1411_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK,
	.qam_अगर        = S5H1411_IF_44000,
	.vsb_अगर        = S5H1411_IF_44000,
	.inversion     = S5H1411_INVERSION_OFF,
	.status_mode   = S5H1411_DEMODLOCKING
पूर्ण;

/* Pinnacle PCTV HD Pro 801e GPIOs map:
   GPIO0  - currently unknown
   GPIO1  - xc5000 tuner reset
   GPIO2  - CX25843 sleep
   GPIO3  - currently unknown
   GPIO4  - currently unknown
   GPIO6  - currently unknown
   GPIO7  - currently unknown
   GPIO9  - currently unknown
   GPIO10 - CX25843 reset
 */
अटल पूर्णांक s5h1411_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;

	/* Make use of the new i2c functions from FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	/* The s5h1411 requires the dib0700 to not be in master mode */
	st->disable_streaming_master_mode = 1;

	/* All msleep values taken from Winकरोws USB trace */
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO3, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(400);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(60);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 0);
	msleep(30);

	/* Put the CX25843 to sleep क्रम now since we're in digital mode */
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 1);

	/* GPIOs are initialized, करो the attach */
	adap->fe_adap[0].fe = dvb_attach(s5h1411_attach, &pinnacle_801e_config,
			      &adap->dev->i2c_adap);
	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक dib0700_xc5000_tuner_callback(व्योम *priv, पूर्णांक component,
					 पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा dvb_usb_adapter *adap = priv;

	अगर (command == XC5000_TUNER_RESET) अणु
		/* Reset the tuner */
		dib0700_set_gpio(adap->dev, GPIO1, GPIO_OUT, 0);
		msleep(10);
		dib0700_set_gpio(adap->dev, GPIO1, GPIO_OUT, 1);
		msleep(10);
	पूर्ण अन्यथा अणु
		err("xc5000: unknown tuner callback command: %d\n", command);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xc5000_config s5h1411_xc5000_tunerconfig = अणु
	.i2c_address      = 0x64,
	.अगर_khz           = 5380,
पूर्ण;

अटल पूर्णांक xc5000_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	/* FIXME: generalize & move to common area */
	adap->fe_adap[0].fe->callback = dib0700_xc5000_tuner_callback;

	वापस dvb_attach(xc5000_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap,
			  &s5h1411_xc5000_tunerconfig)
		== शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक dib0700_xc4000_tuner_callback(व्योम *priv, पूर्णांक component,
					 पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा dvb_usb_adapter *adap = priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (command == XC4000_TUNER_RESET) अणु
		/* Reset the tuner */
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 0);
		msleep(10);
		state->dib7000p_ops.set_gpio(adap->fe_adap[0].fe, 8, 0, 1);
	पूर्ण अन्यथा अणु
		err("xc4000: unknown tuner callback command: %d\n", command);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dibx000_agc_config stk7700p_7000p_xc4000_agc_config = अणु
	.band_caps = BAND_UHF | BAND_VHF,
	.setup = 0x64,
	.inv_gain = 0x02c8,
	.समय_stabiliz = 0x15,
	.alpha_level = 0x00,
	.thlock = 0x76,
	.wbd_inv = 0x01,
	.wbd_ref = 0x0b33,
	.wbd_sel = 0x00,
	.wbd_alpha = 0x02,
	.agc1_max = 0x00,
	.agc1_min = 0x00,
	.agc2_max = 0x9b26,
	.agc2_min = 0x26ca,
	.agc1_pt1 = 0x00,
	.agc1_pt2 = 0x00,
	.agc1_pt3 = 0x00,
	.agc1_slope1 = 0x00,
	.agc1_slope2 = 0x00,
	.agc2_pt1 = 0x00,
	.agc2_pt2 = 0x80,
	.agc2_slope1 = 0x1d,
	.agc2_slope2 = 0x1d,
	.alpha_mant = 0x11,
	.alpha_exp = 0x1b,
	.beta_mant = 0x17,
	.beta_exp = 0x33,
	.perक्रमm_agc_softsplit = 0x00,
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config stk7700p_xc4000_pll_config = अणु
	.पूर्णांकernal = 60000,
	.sampling = 30000,
	.pll_preभाग = 1,
	.pll_ratio = 8,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 0,
	.sad_cfg = (3 << 14) | (1 << 12) | 524, /* sad_cfg: refsel, sel, freq_15k */
	.अगरreq = 39370534,
	.timf = 20452225,
	.xtal_hz = 30000000
पूर्ण;

/* FIXME: none of these inमाला_दो are validated yet */
अटल काष्ठा dib7000p_config pctv_340e_config = अणु
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &stk7700p_7000p_xc4000_agc_config,
	.bw  = &stk7700p_xc4000_pll_config,

	.gpio_dir = DIB7000M_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000M_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000M_GPIO_DEFAULT_PWM_POS,
पूर्ण;

/* PCTV 340e GPIOs map:
   dib0700:
   GPIO2  - CX25843 sleep
   GPIO3  - CS5340 reset
   GPIO5  - IRD
   GPIO6  - Power Supply
   GPIO8  - LNA (1=off 0=on)
   GPIO10 - CX25843 reset
   dib7000:
   GPIO8  - xc4000 reset
 */
अटल पूर्णांक pctv340e_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	अगर (!dvb_attach(dib7000p_attach, &state->dib7000p_ops))
		वापस -ENODEV;

	/* Power Supply on */
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0);
	msleep(50);
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1);
	msleep(100); /* Allow घातer supply to settle beक्रमe probing */

	/* cx25843 reset */
	dib0700_set_gpio(adap->dev, GPIO10,  GPIO_OUT, 0);
	msleep(1); /* cx25843 datasheet say 350us required */
	dib0700_set_gpio(adap->dev, GPIO10,  GPIO_OUT, 1);

	/* LNA off क्रम now */
	dib0700_set_gpio(adap->dev, GPIO8,  GPIO_OUT, 1);

	/* Put the CX25843 to sleep क्रम now since we're in digital mode */
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 1);

	/* FIXME: not verअगरied yet */
	dib0700_ctrl_घड़ी(adap->dev, 72, 1);

	msleep(500);

	अगर (state->dib7000p_ops.dib7000pc_detection(&adap->dev->i2c_adap) == 0) अणु
		/* Demodulator not found क्रम some reason? */
		dvb_detach(state->dib7000p_ops.set_wbd_ref);
		वापस -ENODEV;
	पूर्ण

	adap->fe_adap[0].fe = state->dib7000p_ops.init(&adap->dev->i2c_adap, 0x12,
			      &pctv_340e_config);
	st->is_dib7000pc = 1;

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल काष्ठा xc4000_config dib7000p_xc4000_tunerconfig = अणु
	.i2c_address	  = 0x61,
	.शेष_pm	  = 1,
	.dvb_amplitude	  = 0,
	.set_smoothedcvbs = 0,
	.अगर_khz		  = 5400
पूर्ण;

अटल पूर्णांक xc4000_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा i2c_adapter *tun_i2c;
	काष्ठा dib0700_adapter_state *state = adap->priv;

	/* The xc4000 is not on the मुख्य i2c bus */
	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
					  DIBX000_I2C_INTERFACE_TUNER, 1);
	अगर (tun_i2c == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Could not reach tuner i2c bus\n");
		वापस 0;
	पूर्ण

	/* Setup the reset callback */
	adap->fe_adap[0].fe->callback = dib0700_xc4000_tuner_callback;

	वापस dvb_attach(xc4000_attach, adap->fe_adap[0].fe, tun_i2c,
			  &dib7000p_xc4000_tunerconfig)
		== शून्य ? -ENODEV : 0;
पूर्ण

अटल काष्ठा lgdt3305_config hcw_lgdt3305_config = अणु
	.i2c_addr           = 0x0e,
	.mpeg_mode          = LGDT3305_MPEG_PARALLEL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_LOW,
	.deny_i2c_rptr      = 0,
	.spectral_inversion = 1,
	.qam_अगर_khz         = 6000,
	.vsb_अगर_khz         = 6000,
	.usref_8vsb         = 0x0500,
पूर्ण;

अटल काष्ठा mxl5007t_config hcw_mxl5007t_config = अणु
	.xtal_freq_hz = MxL_XTAL_25_MHZ,
	.अगर_freq_hz = MxL_IF_6_MHZ,
	.invert_अगर = 1,
पूर्ण;

/* TIGER-ATSC map:
   GPIO0  - LNA_CTR  (H: LNA घातer enabled, L: LNA घातer disabled)
   GPIO1  - ANT_SEL  (H: VPA, L: MCX)
   GPIO4  - SCL2
   GPIO6  - EN_TUNER
   GPIO7  - SDA2
   GPIO10 - DEM_RST

   MXL is behind LG's i2c repeater.  LG is on SCL2/SDA2 gpios on the DIB
 */
अटल पूर्णांक lgdt3305_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;

	/* Make use of the new i2c functions from FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	st->disable_streaming_master_mode = 1;

	/* fe घातer enable */
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(30);

	/* demod reset */
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);

	adap->fe_adap[0].fe = dvb_attach(lgdt3305_attach,
			      &hcw_lgdt3305_config,
			      &adap->dev->i2c_adap);

	वापस adap->fe_adap[0].fe == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक mxl5007t_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	वापस dvb_attach(mxl5007t_attach, adap->fe_adap[0].fe,
			  &adap->dev->i2c_adap, 0x60,
			  &hcw_mxl5007t_config) == शून्य ? -ENODEV : 0;
पूर्ण

अटल पूर्णांक xbox_one_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dib0700_state *st = adap->dev->priv;
	काष्ठा i2c_client *client_demod, *client_tuner;
	काष्ठा dvb_usb_device *d = adap->dev;
	काष्ठा mn88472_config mn88472_config = अणु पूर्ण;
	काष्ठा tda18250_config tda18250_config;
	काष्ठा i2c_board_info info;

	st->fw_use_new_i2c_api = 1;
	st->disable_streaming_master_mode = 1;

	/* fe घातer enable */
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(30);

	/* demod reset */
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);

	/* attach demod */
	mn88472_config.fe = &adap->fe_adap[0].fe;
	mn88472_config.i2c_wr_max = 22;
	mn88472_config.xtal = 20500000;
	mn88472_config.ts_mode = PARALLEL_TS_MODE;
	mn88472_config.ts_घड़ी = FIXED_TS_CLOCK;
	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "mn88472", I2C_NAME_SIZE);
	info.addr = 0x18;
	info.platक्रमm_data = &mn88472_config;
	request_module(info.type);
	client_demod = i2c_new_client_device(&d->i2c_adap, &info);
	अगर (!i2c_client_has_driver(client_demod))
		जाओ fail_demod_device;
	अगर (!try_module_get(client_demod->dev.driver->owner))
		जाओ fail_demod_module;

	st->i2c_client_demod = client_demod;

	adap->fe_adap[0].fe = mn88472_config.get_dvb_frontend(client_demod);

	/* attach tuner */
	स_रखो(&tda18250_config, 0, माप(tda18250_config));
	tda18250_config.अगर_dvbt_6 = 3950;
	tda18250_config.अगर_dvbt_7 = 4450;
	tda18250_config.अगर_dvbt_8 = 4950;
	tda18250_config.अगर_dvbc_6 = 4950;
	tda18250_config.अगर_dvbc_8 = 4950;
	tda18250_config.अगर_atsc = 4079;
	tda18250_config.loopthrough = true;
	tda18250_config.xtal_freq = TDA18250_XTAL_FREQ_27MHZ;
	tda18250_config.fe = adap->fe_adap[0].fe;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "tda18250", I2C_NAME_SIZE);
	info.addr = 0x60;
	info.platक्रमm_data = &tda18250_config;

	request_module(info.type);
	client_tuner = i2c_new_client_device(&adap->dev->i2c_adap, &info);
	अगर (!i2c_client_has_driver(client_tuner))
		जाओ fail_tuner_device;
	अगर (!try_module_get(client_tuner->dev.driver->owner))
		जाओ fail_tuner_module;

	st->i2c_client_tuner = client_tuner;
	वापस 0;

fail_tuner_module:
	i2c_unरेजिस्टर_device(client_tuner);
fail_tuner_device:
	module_put(client_demod->dev.driver->owner);
fail_demod_module:
	i2c_unरेजिस्टर_device(client_demod);
fail_demod_device:
	वापस -ENODEV;
पूर्ण


/* DVB-USB and USB stuff follows */
काष्ठा usb_device_id dib0700_usb_id_table[] = अणु
/* 0 */	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK7700P) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK7700P_PC) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_500) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_500_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_STICK) पूर्ण,
/* 5 */	अणु USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_VOLAR) पूर्ण,
	अणु USB_DEVICE(USB_VID_COMPRO,    USB_PID_COMPRO_VIDEOMATE_U500) पूर्ण,
	अणु USB_DEVICE(USB_VID_UNIWILL,   USB_PID_UNIWILL_STK7700P) पूर्ण,
	अणु USB_DEVICE(USB_VID_LEADTEK,   USB_PID_WINFAST_DTV_DONGLE_STK7700P) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_STICK_2) पूर्ण,
/* 10 */अणु USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_VOLAR_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV2000E) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,
			USB_PID_TERRATEC_CINERGY_DT_XS_DIVERSITY) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_TD_STICK) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK7700D) पूर्ण,
/* 15 */अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK7070P) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV_DVB_T_FLASH) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK7070PD) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,
			USB_PID_PINNACLE_PCTV_DUAL_DIVERSITY_DVB_T) पूर्ण,
	अणु USB_DEVICE(USB_VID_COMPRO,    USB_PID_COMPRO_VIDEOMATE_U500_PC) पूर्ण,
/* 20 */अणु USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_EXPRESS) पूर्ण,
	अणु USB_DEVICE(USB_VID_GIGABYTE,  USB_PID_GIGABYTE_U7000) पूर्ण,
	अणु USB_DEVICE(USB_VID_ULTIMA_ELECTRONIC, USB_PID_ARTEC_T14BR) पूर्ण,
	अणु USB_DEVICE(USB_VID_ASUS,      USB_PID_ASUS_U3000) पूर्ण,
	अणु USB_DEVICE(USB_VID_ASUS,      USB_PID_ASUS_U3100) पूर्ण,
/* 25 */अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_STICK_3) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_MYTV_T) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,  USB_PID_TERRATEC_CINERGY_HT_USB_XE) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_EXPRESSCARD_320CX) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_PCTV72E) पूर्ण,
/* 30 */अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_PCTV73E) पूर्ण,
	अणु USB_DEVICE(USB_VID_YUAN,	USB_PID_YUAN_EC372S) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_CINERGY_HT_EXPRESS) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_CINERGY_T_XXS) पूर्ण,
	अणु USB_DEVICE(USB_VID_LEADTEK,   USB_PID_WINFAST_DTV_DONGLE_STK7700P_2) पूर्ण,
/* 35 */अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_TD_STICK_52009) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_NOVA_T_500_3) पूर्ण,
	अणु USB_DEVICE(USB_VID_GIGABYTE,  USB_PID_GIGABYTE_U8000) पूर्ण,
	अणु USB_DEVICE(USB_VID_YUAN,      USB_PID_YUAN_STK7700PH) पूर्ण,
	अणु USB_DEVICE(USB_VID_ASUS,	USB_PID_ASUS_U3000H) पूर्ण,
/* 40 */अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV801E) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV801E_SE) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_CINERGY_T_EXPRESS) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,
			USB_PID_TERRATEC_CINERGY_DT_XS_DIVERSITY_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_SONY,	USB_PID_SONY_PLAYTV) पूर्ण,
/* 45 */अणु USB_DEVICE(USB_VID_YUAN,      USB_PID_YUAN_PD378S) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_TIGER_ATSC) पूर्ण,
	अणु USB_DEVICE(USB_VID_HAUPPAUGE, USB_PID_HAUPPAUGE_TIGER_ATSC_B210) पूर्ण,
	अणु USB_DEVICE(USB_VID_YUAN,	USB_PID_YUAN_MC770) पूर्ण,
	अणु USB_DEVICE(USB_VID_ELGATO,	USB_PID_ELGATO_EYETV_DTT) पूर्ण,
/* 50 */अणु USB_DEVICE(USB_VID_ELGATO,	USB_PID_ELGATO_EYETV_DTT_Dlx) पूर्ण,
	अणु USB_DEVICE(USB_VID_LEADTEK,   USB_PID_WINFAST_DTV_DONGLE_H) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_T3) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_T5) पूर्ण,
	अणु USB_DEVICE(USB_VID_YUAN,      USB_PID_YUAN_STK7700D) पूर्ण,
/* 55 */अणु USB_DEVICE(USB_VID_YUAN,	USB_PID_YUAN_STK7700D_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_PCTV73A) पूर्ण,
	अणु USB_DEVICE(USB_VID_PCTV,	USB_PID_PINNACLE_PCTV73ESE) पूर्ण,
	अणु USB_DEVICE(USB_VID_PCTV,	USB_PID_PINNACLE_PCTV282E) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,	USB_PID_DIBCOM_STK7770P) पूर्ण,
/* 60 */अणु USB_DEVICE(USB_VID_TERRATEC,	USB_PID_TERRATEC_CINERGY_T_XXS_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK807XPVR) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK807XP) पूर्ण,
	अणु USB_DEVICE_VER(USB_VID_PIXELVIEW, USB_PID_PIXELVIEW_SBTVD, 0x000, 0x3f00) पूर्ण,
	अणु USB_DEVICE(USB_VID_EVOLUTEPC, USB_PID_TVWAY_PLUS) पूर्ण,
/* 65 */अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_PCTV73ESE) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,	USB_PID_PINNACLE_PCTV282E) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK8096GP) पूर्ण,
	अणु USB_DEVICE(USB_VID_ELGATO,    USB_PID_ELGATO_EYETV_DIVERSITY) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_NIM9090M) पूर्ण,
/* 70 */अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_NIM8096MD) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_NIM9090MD) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_NIM7090) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_TFE7090PVR) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_AIRSTAR_TELESTICK_2) पूर्ण,
/* 75 */अणु USB_DEVICE(USB_VID_MEDION,    USB_PID_CREATIX_CTX1921) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV340E) पूर्ण,
	अणु USB_DEVICE(USB_VID_PINNACLE,  USB_PID_PINNACLE_PCTV340E_SE) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_TFE7790P) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_TFE8096P) पूर्ण,
/* 80 */अणु USB_DEVICE(USB_VID_ELGATO,	USB_PID_ELGATO_EYETV_DTT_2) पूर्ण,
	अणु USB_DEVICE(USB_VID_PCTV,      USB_PID_PCTV_2002E) पूर्ण,
	अणु USB_DEVICE(USB_VID_PCTV,      USB_PID_PCTV_2002E_SE) पूर्ण,
	अणु USB_DEVICE(USB_VID_PCTV,      USB_PID_DIBCOM_STK8096PVR) पूर्ण,
	अणु USB_DEVICE(USB_VID_DIBCOM,    USB_PID_DIBCOM_STK8096PVR) पूर्ण,
/* 85 */अणु USB_DEVICE(USB_VID_HAMA,	USB_PID_HAMA_DVBT_HYBRID) पूर्ण,
	अणु USB_DEVICE(USB_VID_MICROSOFT,	USB_PID_XBOX_ONE_TUNER) पूर्ण,
	अणु 0 पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, dib0700_usb_id_table);

#घोषणा DIB0700_DEFAULT_DEVICE_PROPERTIES \
	.caps              = DVB_USB_IS_AN_I2C_ADAPTER, \
	.usb_ctrl          = DEVICE_SPECIFIC, \
	.firmware          = "dvb-usb-dib0700-1.20.fw", \
	.करोwnload_firmware = dib0700_करोwnload_firmware, \
	.no_reconnect      = 1, \
	.size_of_priv      = माप(काष्ठा dib0700_state), \
	.i2c_algo          = &dib0700_i2c_algo, \
	.identअगरy_state    = dib0700_identअगरy_state

#घोषणा DIB0700_DEFAULT_STREAMING_CONFIG(ep) \
	.streaming_ctrl   = dib0700_streaming_ctrl, \
	.stream = अणु \
		.type = USB_BULK, \
		.count = 4, \
		.endpoपूर्णांक = ep, \
		.u = अणु \
			.bulk = अणु \
				.buffersize = 39480, \
			पूर्ण \
		पूर्ण \
	पूर्ण

#घोषणा DIB0700_NUM_FRONTENDS(n) \
	.num_frontends = n, \
	.size_of_priv     = माप(काष्ठा dib0700_adapter_state)

काष्ठा dvb_usb_device_properties dib0700_devices[] = अणु
	अणु
		DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk7700p_pid_filter,
				.pid_filter_ctrl  = stk7700p_pid_filter_ctrl,
				.frontend_attach  = stk7700p_frontend_attach,
				.tuner_attach     = stk7700p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 8,
		.devices = अणु
			अणु   "DiBcom STK7700P reference design",
				अणु &dib0700_usb_id_table[0], &dib0700_usb_id_table[1] पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge Nova-T Stick",
				अणु &dib0700_usb_id_table[4], &dib0700_usb_id_table[9], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "AVerMedia AVerTV DVB-T Volar",
				अणु &dib0700_usb_id_table[5], &dib0700_usb_id_table[10] पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Compro Videomate U500",
				अणु &dib0700_usb_id_table[6], &dib0700_usb_id_table[19] पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Uniwill STK7700P based (Hama and others)",
				अणु &dib0700_usb_id_table[7], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Leadtek Winfast DTV Dongle (STK7700P based)",
				अणु &dib0700_usb_id_table[8], &dib0700_usb_id_table[34] पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "AVerMedia AVerTV DVB-T Express",
				अणु &dib0700_usb_id_table[20] पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Gigabyte U7000",
				अणु &dib0700_usb_id_table[21], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.frontend_attach  = bristol_frontend_attach,
				.tuner_attach     = bristol_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण, अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.frontend_attach  = bristol_frontend_attach,
				.tuner_attach     = bristol_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "Hauppauge Nova-T 500 Dual DVB-T",
				अणु &dib0700_usb_id_table[2], &dib0700_usb_id_table[3], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7700d_frontend_attach,
				.tuner_attach     = stk7700d_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण, अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7700d_frontend_attach,
				.tuner_attach     = stk7700d_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण
		पूर्ण,

		.num_device_descs = 5,
		.devices = अणु
			अणु   "Pinnacle PCTV 2000e",
				अणु &dib0700_usb_id_table[11], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Terratec Cinergy DT XS Diversity",
				अणु &dib0700_usb_id_table[12], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge Nova-TD Stick/Elgato Eye-TV Diversity",
				अणु &dib0700_usb_id_table[13], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "DiBcom STK7700D reference design",
				अणु &dib0700_usb_id_table[14], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "YUAN High-Tech DiBcom STK7700D",
				अणु &dib0700_usb_id_table[55], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,

		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7700P2_frontend_attach,
				.tuner_attach     = stk7700d_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 3,
		.devices = अणु
			अणु   "ASUS My Cinema U3000 Mini DVBT Tuner",
				अणु &dib0700_usb_id_table[23], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Yuan EC372S",
				अणु &dib0700_usb_id_table[31], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Terratec Cinergy T Express",
				अणु &dib0700_usb_id_table[42], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070p_frontend_attach,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 12,
		.devices = अणु
			अणु   "DiBcom STK7070P reference design",
				अणु &dib0700_usb_id_table[15], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV DVB-T Flash Stick",
				अणु &dib0700_usb_id_table[16], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Artec T14BR DVB-T",
				अणु &dib0700_usb_id_table[22], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "ASUS My Cinema U3100 Mini DVBT Tuner",
				अणु &dib0700_usb_id_table[24], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge Nova-T Stick",
				अणु &dib0700_usb_id_table[25], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge Nova-T MyTV.t",
				अणु &dib0700_usb_id_table[26], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV 72e",
				अणु &dib0700_usb_id_table[29], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV 73e",
				अणु &dib0700_usb_id_table[30], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Elgato EyeTV DTT",
				अणु &dib0700_usb_id_table[49], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Yuan PD378S",
				अणु &dib0700_usb_id_table[45], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Elgato EyeTV Dtt Dlx PD378S",
				अणु &dib0700_usb_id_table[50], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Elgato EyeTV DTT rev. 2",
				अणु &dib0700_usb_id_table[80], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070p_frontend_attach,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 3,
		.devices = अणु
			अणु   "Pinnacle PCTV 73A",
				अणु &dib0700_usb_id_table[56], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV 73e SE",
				अणु &dib0700_usb_id_table[57], &dib0700_usb_id_table[65], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV 282e",
				अणु &dib0700_usb_id_table[58], &dib0700_usb_id_table[66], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = novatd_frontend_attach,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण, अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = novatd_frontend_attach,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण
		पूर्ण,

		.num_device_descs = 3,
		.devices = अणु
			अणु   "Hauppauge Nova-TD Stick (52009)",
				अणु &dib0700_usb_id_table[35], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "PCTV 2002e",
				अणु &dib0700_usb_id_table[81], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "PCTV 2002e SE",
				अणु &dib0700_usb_id_table[82], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070pd_frontend_attach0,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण, अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070pd_frontend_attach1,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण
		पूर्ण,

		.num_device_descs = 5,
		.devices = अणु
			अणु   "DiBcom STK7070PD reference design",
				अणु &dib0700_usb_id_table[17], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV Dual DVB-T Diversity Stick",
				अणु &dib0700_usb_id_table[18], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge Nova-TD-500 (84xxx)",
				अणु &dib0700_usb_id_table[36], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु  "Terratec Cinergy DT USB XS Diversity/ T5",
				अणु &dib0700_usb_id_table[43],
					&dib0700_usb_id_table[53], शून्यपूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु  "Sony PlayTV",
				अणु &dib0700_usb_id_table[44], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070pd_frontend_attach0,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण, अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7070pd_frontend_attach1,
				.tuner_attach     = dib7070p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "Elgato EyeTV Diversity",
				अणु &dib0700_usb_id_table[68], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_NEC_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7700ph_frontend_attach,
				.tuner_attach     = stk7700ph_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 10,
		.devices = अणु
			अणु   "Terratec Cinergy HT USB XE",
				अणु &dib0700_usb_id_table[27], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle Expresscard 320cx",
				अणु &dib0700_usb_id_table[28], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Terratec Cinergy HT Express",
				अणु &dib0700_usb_id_table[32], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Gigabyte U8000-RH",
				अणु &dib0700_usb_id_table[37], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "YUAN High-Tech STK7700PH",
				अणु &dib0700_usb_id_table[38], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Asus My Cinema-U3000Hybrid",
				अणु &dib0700_usb_id_table[39], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "YUAN High-Tech MC770",
				अणु &dib0700_usb_id_table[48], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Leadtek WinFast DTV Dongle H",
				अणु &dib0700_usb_id_table[51], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "YUAN High-Tech STK7700D",
				अणु &dib0700_usb_id_table[54], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hama DVB=T Hybrid USB Stick",
				अणु &dib0700_usb_id_table[85], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.frontend_attach  = s5h1411_frontend_attach,
				.tuner_attach     = xc5000_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 2,
		.devices = अणु
			अणु   "Pinnacle PCTV HD Pro USB Stick",
				अणु &dib0700_usb_id_table[40], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV HD USB Stick",
				अणु &dib0700_usb_id_table[41], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.frontend_attach  = lgdt3305_frontend_attach,
				.tuner_attach     = mxl5007t_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 2,
		.devices = अणु
			अणु   "Hauppauge ATSC MiniCard (B200)",
				अणु &dib0700_usb_id_table[46], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Hauppauge ATSC MiniCard (B210)",
				अणु &dib0700_usb_id_table[47], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,

		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter       = stk70x0p_pid_filter,
				.pid_filter_ctrl  = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = stk7770p_frontend_attach,
				.tuner_attach     = dib7770p_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 4,
		.devices = अणु
			अणु   "DiBcom STK7770P reference design",
				अणु &dib0700_usb_id_table[59], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Terratec Cinergy T USB XXS (HD)/ T3",
				अणु &dib0700_usb_id_table[33],
					&dib0700_usb_id_table[52],
					&dib0700_usb_id_table[60], शून्यपूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "TechniSat AirStar TeleStick 2",
				अणु &dib0700_usb_id_table[74], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Medion CTX1921 DVB-T USB",
				अणु &dib0700_usb_id_table[75], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk80xx_pid_filter,
				.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
				.frontend_attach  = stk807x_frontend_attach,
				.tuner_attach     = dib807x_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 3,
		.devices = अणु
			अणु   "DiBcom STK807xP reference design",
				अणु &dib0700_usb_id_table[62], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Prolink Pixelview SBTVD",
				अणु &dib0700_usb_id_table[63], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "EvolutePC TVWay+",
				अणु &dib0700_usb_id_table[64], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_NEC_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk80xx_pid_filter,
				.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
				.frontend_attach  = stk807xpvr_frontend_attach0,
				.tuner_attach     = dib807x_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER | DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk80xx_pid_filter,
				.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
				.frontend_attach  = stk807xpvr_frontend_attach1,
				.tuner_attach     = dib807x_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom STK807xPVR reference design",
				अणु &dib0700_usb_id_table[61], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk80xx_pid_filter,
				.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
				.frontend_attach  = stk809x_frontend_attach,
				.tuner_attach     = dib809x_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom STK8096GP reference design",
				अणु &dib0700_usb_id_table[67], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = dib90x0_pid_filter,
				.pid_filter_ctrl = dib90x0_pid_filter_ctrl,
				.frontend_attach  = stk9090m_frontend_attach,
				.tuner_attach     = dib9090_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom STK9090M reference design",
				अणु &dib0700_usb_id_table[69], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk80xx_pid_filter,
				.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
				.frontend_attach  = nim8096md_frontend_attach,
				.tuner_attach     = nim8096md_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom NIM8096MD reference design",
				अणु &dib0700_usb_id_table[70], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = dib90x0_pid_filter,
				.pid_filter_ctrl = dib90x0_pid_filter_ctrl,
				.frontend_attach  = nim9090md_frontend_attach,
				.tuner_attach     = nim9090md_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom NIM9090MD reference design",
				अणु &dib0700_usb_id_table[71], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk70x0p_pid_filter,
				.pid_filter_ctrl = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = nim7090_frontend_attach,
				.tuner_attach     = nim7090_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom NIM7090 reference design",
				अणु &dib0700_usb_id_table[72], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 2,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk70x0p_pid_filter,
				.pid_filter_ctrl = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = tfe7090pvr_frontend0_attach,
				.tuner_attach     = tfe7090pvr_tuner0_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
			पूर्णपूर्ण,
			पूर्ण,
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
					DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
				.pid_filter_count = 32,
				.pid_filter = stk70x0p_pid_filter,
				.pid_filter_ctrl = stk70x0p_pid_filter_ctrl,
				.frontend_attach  = tfe7090pvr_frontend1_attach,
				.tuner_attach     = tfe7090pvr_tuner1_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom TFE7090PVR reference design",
				अणु &dib0700_usb_id_table[73], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
			DIB0700_NUM_FRONTENDS(1),
			.fe = अणुअणु
				.frontend_attach  = pctv340e_frontend_attach,
				.tuner_attach     = xc4000_tuner_attach,

				DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
			पूर्णपूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 2,
		.devices = अणु
			अणु   "Pinnacle PCTV 340e HD Pro USB Stick",
				अणु &dib0700_usb_id_table[76], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
			अणु   "Pinnacle PCTV Hybrid Stick Solo",
				अणु &dib0700_usb_id_table[77], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,
		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
				DIB0700_NUM_FRONTENDS(1),
				.fe = अणुअणु
					.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
						DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
					.pid_filter_count = 32,
					.pid_filter = stk70x0p_pid_filter,
					.pid_filter_ctrl = stk70x0p_pid_filter_ctrl,
					.frontend_attach  = tfe7790p_frontend_attach,
					.tuner_attach     = tfe7790p_tuner_attach,

					DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
				पूर्ण पूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom TFE7790P reference design",
				अणु &dib0700_usb_id_table[78], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
				DIB0700_NUM_FRONTENDS(1),
				.fe = अणुअणु
					.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
						DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
					.pid_filter_count = 32,
					.pid_filter = stk80xx_pid_filter,
					.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
					.frontend_attach  = tfe8096p_frontend_attach,
					.tuner_attach     = tfe8096p_tuner_attach,

					DIB0700_DEFAULT_STREAMING_CONFIG(0x02),

				पूर्ण पूर्ण,
			पूर्ण,
		पूर्ण,

		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom TFE8096P reference design",
				अणु &dib0700_usb_id_table[79], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name	  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
					    RC_PROTO_BIT_RC6_MCE |
					    RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 2,
		.adapter = अणु
			अणु
				.num_frontends = 1,
				.fe = अणुअणु
					.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
						DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
					.pid_filter_count = 32,
					.pid_filter = stk80xx_pid_filter,
					.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
					.frontend_attach  = stk809x_frontend_attach,
					.tuner_attach     = dib809x_tuner_attach,

					DIB0700_DEFAULT_STREAMING_CONFIG(0x02),
				पूर्ण पूर्ण,
				.size_of_priv =
					माप(काष्ठा dib0700_adapter_state),
			पूर्ण, अणु
				.num_frontends = 1,
				.fe = अणु अणु
					.caps  = DVB_USB_ADAP_HAS_PID_FILTER |
						DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,
					.pid_filter_count = 32,
					.pid_filter = stk80xx_pid_filter,
					.pid_filter_ctrl = stk80xx_pid_filter_ctrl,
					.frontend_attach  = stk809x_frontend1_attach,
					.tuner_attach     = dib809x_tuner_attach,

					DIB0700_DEFAULT_STREAMING_CONFIG(0x03),
				पूर्ण पूर्ण,
				.size_of_priv =
					माप(काष्ठा dib0700_adapter_state),
			पूर्ण,
		पूर्ण,
		.num_device_descs = 1,
		.devices = अणु
			अणु   "DiBcom STK8096-PVR reference design",
				अणु &dib0700_usb_id_table[83],
					&dib0700_usb_id_table[84], शून्यपूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,

		.rc.core = अणु
			.rc_पूर्णांकerval      = DEFAULT_RC_INTERVAL,
			.rc_codes         = RC_MAP_DIB0700_RC5_TABLE,
			.module_name  = "dib0700",
			.rc_query         = dib0700_rc_query_old_firmware,
			.allowed_protos   = RC_PROTO_BIT_RC5 |
				RC_PROTO_BIT_RC6_MCE |
				RC_PROTO_BIT_NEC,
			.change_protocol  = dib0700_change_protocol,
		पूर्ण,
	पूर्ण, अणु DIB0700_DEFAULT_DEVICE_PROPERTIES,
		.num_adapters = 1,
		.adapter = अणु
			अणु
				DIB0700_NUM_FRONTENDS(1),
				.fe = अणुअणु
					.frontend_attach = xbox_one_attach,

					DIB0700_DEFAULT_STREAMING_CONFIG(0x82),
				पूर्ण पूर्ण,
			पूर्ण,
		पूर्ण,
		.num_device_descs = 1,
		.devices = अणु
			अणु "Microsoft Xbox One Digital TV Tuner",
				अणु &dib0700_usb_id_table[86], शून्य पूर्ण,
				अणु शून्य पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक dib0700_device_count = ARRAY_SIZE(dib0700_devices);
