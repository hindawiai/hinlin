<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * (c) 2004 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 *
 *  Extended 3 / 2005 by Harपंचांगut Hackmann to support various
 *  cards with the tda10046 DVB-T channel decoder
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/suspend.h>

#समावेश <media/v4l2-common.h>
#समावेश "dvb-pll.h"
#समावेश <media/dvb_frontend.h>

#समावेश "mt352.h"
#समावेश "mt352_priv.h" /* FIXME */
#समावेश "tda1004x.h"
#समावेश "nxt200x.h"
#समावेश "tuner-xc2028.h"
#समावेश "xc5000.h"

#समावेश "tda10086.h"
#समावेश "tda826x.h"
#समावेश "tda827x.h"
#समावेश "isl6421.h"
#समावेश "isl6405.h"
#समावेश "lnbp21.h"
#समावेश "tuner-simple.h"
#समावेश "tda10048.h"
#समावेश "tda18271.h"
#समावेश "lgdt3305.h"
#समावेश "tda8290.h"
#समावेश "mb86a20s.h"
#समावेश "lgs8gxx.h"

#समावेश "zl10353.h"
#समावेश "qt1010.h"

#समावेश "zl10036.h"
#समावेश "zl10039.h"
#समावेश "mt312.h"
#समावेश "s5h1411.h"

MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक antenna_pwr;

module_param(antenna_pwr, पूर्णांक, 0444);
MODULE_PARM_DESC(antenna_pwr,"enable antenna power (Pinnacle 300i)");

अटल पूर्णांक use_frontend;
module_param(use_frontend, पूर्णांक, 0644);
MODULE_PARM_DESC(use_frontend,"for cards with multiple frontends (0: terrestrial, 1: satellite)");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* ------------------------------------------------------------------
 * mt352 based DVB-T cards
 */

अटल पूर्णांक pinnacle_antenna_pwr(काष्ठा saa7134_dev *dev, पूर्णांक on)
अणु
	u32 ok;

	अगर (!on) अणु
		saa_setl(SAA7134_GPIO_GPMODE0 >> 2,     (1 << 26));
		saa_clearl(SAA7134_GPIO_GPSTATUS0 >> 2, (1 << 26));
		वापस 0;
	पूर्ण

	saa_setl(SAA7134_GPIO_GPMODE0 >> 2,     (1 << 26));
	saa_setl(SAA7134_GPIO_GPSTATUS0 >> 2,   (1 << 26));
	udelay(10);

	saa_setl(SAA7134_GPIO_GPMODE0 >> 2,     (1 << 28));
	saa_clearl(SAA7134_GPIO_GPSTATUS0 >> 2, (1 << 28));
	udelay(10);
	saa_setl(SAA7134_GPIO_GPSTATUS0 >> 2,   (1 << 28));
	udelay(10);
	ok = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0) & (1 << 27);
	pr_debug("%s %s\n", __func__, ok ? "on" : "off");

	अगर (!ok)
		saa_clearl(SAA7134_GPIO_GPSTATUS0 >> 2,   (1 << 26));
	वापस ok;
पूर्ण

अटल पूर्णांक mt352_pinnacle_init(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 घड़ी_config []  = अणु CLOCK_CTL,  0x3d, 0x28 पूर्ण;
	अटल u8 reset []         = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg [] = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg []       = अणु AGC_TARGET, 0x28, 0xa0 पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x31 पूर्ण;
	अटल u8 fsm_ctl_cfg[]    = अणु 0x7b,       0x04 पूर्ण;
	अटल u8 gpp_ctl_cfg []   = अणु GPP_CTL,    0x0f पूर्ण;
	अटल u8 scan_ctl_cfg []  = अणु SCAN_CTL,   0x0d पूर्ण;
	अटल u8 irq_cfg []       = अणु INTERRUPT_EN_0, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	pr_debug("%s called\n", __func__);

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));
	mt352_ग_लिखो(fe, gpp_ctl_cfg,    माप(gpp_ctl_cfg));

	mt352_ग_लिखो(fe, fsm_ctl_cfg,    माप(fsm_ctl_cfg));
	mt352_ग_लिखो(fe, scan_ctl_cfg,   माप(scan_ctl_cfg));
	mt352_ग_लिखो(fe, irq_cfg,        माप(irq_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_aver777_init(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 घड़ी_config []  = अणु CLOCK_CTL,  0x38, 0x2d पूर्ण;
	अटल u8 reset []         = अणु RESET,      0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg [] = अणु ADC_CTL_1,  0x40 पूर्ण;
	अटल u8 agc_cfg []       = अणु AGC_TARGET, 0x28, 0xa0 पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x33 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक mt352_avermedia_xc3028_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 घड़ी_config []  = अणु CLOCK_CTL, 0x38, 0x2d पूर्ण;
	अटल u8 reset []         = अणु RESET, 0x80 पूर्ण;
	अटल u8 adc_ctl_1_cfg [] = अणु ADC_CTL_1, 0x40 पूर्ण;
	अटल u8 agc_cfg []       = अणु AGC_TARGET, 0xe पूर्ण;
	अटल u8 capt_range_cfg[] = अणु CAPT_RANGE, 0x33 पूर्ण;

	mt352_ग_लिखो(fe, घड़ी_config,   माप(घड़ी_config));
	udelay(200);
	mt352_ग_लिखो(fe, reset,          माप(reset));
	mt352_ग_लिखो(fe, adc_ctl_1_cfg,  माप(adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, agc_cfg,        माप(agc_cfg));
	mt352_ग_लिखो(fe, capt_range_cfg, माप(capt_range_cfg));
	वापस 0;
पूर्ण

अटल पूर्णांक mt352_pinnacle_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 off[] = अणु 0x00, 0xf1पूर्ण;
	u8 on[]  = अणु 0x00, 0x71पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr=0x43, .flags=0, .buf=off, .len = माप(off)पूर्ण;

	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा v4l2_frequency f;

	/* set frequency (mt2050) */
	f.tuner     = 0;
	f.type      = V4L2_TUNER_DIGITAL_TV;
	f.frequency = c->frequency / 1000 * 16 / 1000;
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(&dev->i2c_adap, &msg, 1);
	saa_call_all(dev, tuner, s_frequency, &f);
	msg.buf = on;
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(&dev->i2c_adap, &msg, 1);

	pinnacle_antenna_pwr(dev, antenna_pwr);

	/* mt352 setup */
	वापस mt352_pinnacle_init(fe);
पूर्ण

अटल काष्ठा mt352_config pinnacle_300i = अणु
	.demod_address = 0x3c >> 1,
	.adc_घड़ी     = 20333,
	.अगर2           = 36150,
	.no_tuner      = 1,
	.demod_init    = mt352_pinnacle_init,
पूर्ण;

अटल काष्ठा mt352_config avermedia_777 = अणु
	.demod_address = 0xf,
	.demod_init    = mt352_aver777_init,
पूर्ण;

अटल काष्ठा mt352_config avermedia_xc3028_mt352_dev = अणु
	.demod_address   = (0x1e >> 1),
	.no_tuner        = 1,
	.demod_init      = mt352_avermedia_xc3028_init,
पूर्ण;

अटल काष्ठा tda18271_std_map mb86a20s_tda18271_std_map = अणु
	.dvbt_6   = अणु .अगर_freq = 3300, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 7, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config kworld_tda18271_config = अणु
	.std_map = &mb86a20s_tda18271_std_map,
	.gate    = TDA18271_GATE_DIGITAL,
	.config  = 3,	/* Use tuner callback क्रम AGC */

पूर्ण;

अटल स्थिर काष्ठा mb86a20s_config kworld_mb86a20s_config = अणु
	.demod_address = 0x10,
पूर्ण;

अटल पूर्णांक kworld_sbtvd_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;

	अचिन्हित अक्षर iniपंचांगsg[] = अणु0x45, 0x97पूर्ण;
	अचिन्हित अक्षर msg_enable[] = अणु0x45, 0xc1पूर्ण;
	अचिन्हित अक्षर msg_disable[] = अणु0x45, 0x81पूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = 0x4b, .flags = 0, .buf = iniपंचांगsg, .len = 2पूर्ण;

	अगर (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1) अणु
		pr_warn("could not access the I2C gate\n");
		वापस -EIO;
	पूर्ण
	अगर (enable)
		msg.buf = msg_enable;
	अन्यथा
		msg.buf = msg_disable;
	अगर (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1) अणु
		pr_warn("could not access the I2C gate\n");
		वापस -EIO;
	पूर्ण
	msleep(20);
	वापस 0;
पूर्ण

/* ==================================================================
 * tda1004x based DVB-T cards, helper functions
 */

अटल पूर्णांक philips_tda1004x_request_firmware(काष्ठा dvb_frontend *fe,
					   स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	वापस request_firmware(fw, name, &dev->pci->dev);
पूर्ण

/* ------------------------------------------------------------------
 * these tuners are tu1216, td1316(a)
 */

अटल पूर्णांक philips_tda6651_pll_set(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;
	u8 addr = state->config->tuner_address;
	u8 tuner_buf[4];
	काष्ठा i2c_msg tuner_msg = अणु.addr = addr,.flags = 0,.buf = tuner_buf,.len =
			माप(tuner_buf) पूर्ण;
	पूर्णांक tuner_frequency = 0;
	u8 band, cp, filter;

	/* determine अक्षरge pump */
	tuner_frequency = c->frequency + 36166000;
	अगर (tuner_frequency < 87000000)
		वापस -EINVAL;
	अन्यथा अगर (tuner_frequency < 130000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 160000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 200000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 290000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 420000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 480000000)
		cp = 6;
	अन्यथा अगर (tuner_frequency < 620000000)
		cp = 3;
	अन्यथा अगर (tuner_frequency < 830000000)
		cp = 5;
	अन्यथा अगर (tuner_frequency < 895000000)
		cp = 7;
	अन्यथा
		वापस -EINVAL;

	/* determine band */
	अगर (c->frequency < 49000000)
		वापस -EINVAL;
	अन्यथा अगर (c->frequency < 161000000)
		band = 1;
	अन्यथा अगर (c->frequency < 444000000)
		band = 2;
	अन्यथा अगर (c->frequency < 861000000)
		band = 4;
	अन्यथा
		वापस -EINVAL;

	/* setup PLL filter */
	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		filter = 0;
		अवरोध;

	हाल 7000000:
		filter = 0;
		अवरोध;

	हाल 8000000:
		filter = 1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* calculate भागisor
	 * ((36166000+((1000000/6)/2)) + Finput)/(1000000/6)
	 */
	tuner_frequency = (((c->frequency / 1000) * 6) + 217496) / 1000;

	/* setup tuner buffer */
	tuner_buf[0] = (tuner_frequency >> 8) & 0x7f;
	tuner_buf[1] = tuner_frequency & 0xff;
	tuner_buf[2] = 0xca;
	tuner_buf[3] = (cp << 5) | (filter << 3) | band;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&dev->i2c_adap, &tuner_msg, 1) != 1) अणु
		pr_warn("could not write to tuner at addr: 0x%02x\n",
			addr << 1);
		वापस -EIO;
	पूर्ण
	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tu1216_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;
	u8 addr = state->config->tuner_address;
	अटल u8 tu1216_init[] = अणु 0x0b, 0xf5, 0x85, 0xab पूर्ण;
	काष्ठा i2c_msg tuner_msg = अणु.addr = addr,.flags = 0,.buf = tu1216_init,.len = माप(tu1216_init) पूर्ण;

	/* setup PLL configuration */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&dev->i2c_adap, &tuner_msg, 1) != 1)
		वापस -EIO;
	msleep(1);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल काष्ठा tda1004x_config philips_tu1216_60_config = अणु
	.demod_address = 0x8,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_4M,
	.agc_config    = TDA10046_AGC_DEFAULT,
	.अगर_freq       = TDA10046_FREQ_3617,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config philips_tu1216_61_config = अणु

	.demod_address = 0x8,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_4M,
	.agc_config    = TDA10046_AGC_DEFAULT,
	.अगर_freq       = TDA10046_FREQ_3617,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक philips_td1316_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;
	u8 addr = state->config->tuner_address;
	अटल u8 msg[] = अणु 0x0b, 0xf5, 0x86, 0xab पूर्ण;
	काष्ठा i2c_msg init_msg = अणु.addr = addr,.flags = 0,.buf = msg,.len = माप(msg) पूर्ण;

	/* setup PLL configuration */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&dev->i2c_adap, &init_msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक philips_td1316_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	वापस philips_tda6651_pll_set(fe);
पूर्ण

अटल पूर्णांक philips_td1316_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;
	u8 addr = state->config->tuner_address;
	अटल u8 msg[] = अणु 0x0b, 0xdc, 0x86, 0xa4 पूर्ण;
	काष्ठा i2c_msg analog_msg = अणु.addr = addr,.flags = 0,.buf = msg,.len = माप(msg) पूर्ण;

	/* चयन the tuner to analog mode */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&dev->i2c_adap, &analog_msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक philips_europa_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	अटल u8 msg[] = अणु 0x00, 0x40पूर्ण;
	काष्ठा i2c_msg init_msg = अणु.addr = 0x43,.flags = 0,.buf = msg,.len = माप(msg) पूर्ण;


	अगर (philips_td1316_tuner_init(fe))
		वापस -EIO;
	msleep(1);
	अगर (i2c_transfer(&dev->i2c_adap, &init_msg, 1) != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक philips_europa_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;

	अटल u8 msg[] = अणु 0x00, 0x14 पूर्ण;
	काष्ठा i2c_msg analog_msg = अणु.addr = 0x43,.flags = 0,.buf = msg,.len = माप(msg) पूर्ण;

	अगर (philips_td1316_tuner_sleep(fe))
		वापस -EIO;

	/* चयन the board to analog mode */
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(&dev->i2c_adap, &analog_msg, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_europa_demod_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;

	अगर (dev->original_demod_sleep)
		dev->original_demod_sleep(fe);
	fe->ops.i2c_gate_ctrl(fe, 1);
	वापस 0;
पूर्ण

अटल काष्ठा tda1004x_config philips_europa_config = अणु

	.demod_address = 0x8,
	.invert        = 0,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_4M,
	.agc_config    = TDA10046_AGC_IFO_AUTO_POS,
	.अगर_freq       = TDA10046_FREQ_052,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config medion_cardbus = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_IFO_AUTO_NEG,
	.अगर_freq       = TDA10046_FREQ_3613,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config technotrend_budget_t3000_config = अणु
	.demod_address = 0x8,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_4M,
	.agc_config    = TDA10046_AGC_DEFAULT,
	.अगर_freq       = TDA10046_FREQ_3617,
	.tuner_address = 0x63,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

/* ------------------------------------------------------------------
 * tda 1004x based cards with philips silicon tuner
 */

अटल पूर्णांक tda8290_i2c_gate_ctrl( काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा tda1004x_state *state = fe->demodulator_priv;

	u8 addr = state->config->i2c_gate;
	अटल u8 tda8290_बंद[] = अणु 0x21, 0xc0पूर्ण;
	अटल u8 tda8290_खोलो[]  = अणु 0x21, 0x80पूर्ण;
	काष्ठा i2c_msg tda8290_msg = अणु.addr = addr,.flags = 0, .len = 2पूर्ण;
	अगर (enable) अणु
		tda8290_msg.buf = tda8290_बंद;
	पूर्ण अन्यथा अणु
		tda8290_msg.buf = tda8290_खोलो;
	पूर्ण
	अगर (i2c_transfer(state->i2c, &tda8290_msg, 1) != 1) अणु
		pr_warn("could not access tda8290 I2C gate\n");
		वापस -EIO;
	पूर्ण
	msleep(20);
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tda827x_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;

	चयन (state->config->antenna_चयन) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		pr_debug("setting GPIO21 to 0 (TV antenna?)\n");
		saa7134_set_gpio(dev, 21, 0);
		अवरोध;
	हाल 2:
		pr_debug("setting GPIO21 to 1 (Radio antenna?)\n");
		saa7134_set_gpio(dev, 21, 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक philips_tda827x_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	काष्ठा tda1004x_state *state = fe->demodulator_priv;

	चयन (state->config->antenna_चयन) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		pr_debug("setting GPIO21 to 1 (Radio antenna?)\n");
		saa7134_set_gpio(dev, 21, 1);
		अवरोध;
	हाल 2:
		pr_debug("setting GPIO21 to 0 (TV antenna?)\n");
		saa7134_set_gpio(dev, 21, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक configure_tda827x_fe(काष्ठा saa7134_dev *dev,
				काष्ठा tda1004x_config *cdec_conf,
				काष्ठा tda827x_config *tuner_conf)
अणु
	काष्ठा vb2_dvb_frontend *fe0;

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);

	अगर (!fe0)
		वापस -EINVAL;

	fe0->dvb.frontend = dvb_attach(tda10046_attach, cdec_conf, &dev->i2c_adap);
	अगर (fe0->dvb.frontend) अणु
		अगर (cdec_conf->i2c_gate)
			fe0->dvb.frontend->ops.i2c_gate_ctrl = tda8290_i2c_gate_ctrl;
		अगर (dvb_attach(tda827x_attach, fe0->dvb.frontend,
			       cdec_conf->tuner_address,
			       &dev->i2c_adap, tuner_conf))
			वापस 0;

		pr_warn("no tda827x tuner found at addr: %02x\n",
				cdec_conf->tuner_address);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ------------------------------------------------------------------ */

अटल काष्ठा tda827x_config tda827x_cfg_0 = अणु
	.init = philips_tda827x_tuner_init,
	.sleep = philips_tda827x_tuner_sleep,
	.config = 0,
	.चयन_addr = 0
पूर्ण;

अटल काष्ठा tda827x_config tda827x_cfg_1 = अणु
	.init = philips_tda827x_tuner_init,
	.sleep = philips_tda827x_tuner_sleep,
	.config = 1,
	.चयन_addr = 0x4b
पूर्ण;

अटल काष्ठा tda827x_config tda827x_cfg_2 = अणु
	.init = philips_tda827x_tuner_init,
	.sleep = philips_tda827x_tuner_sleep,
	.config = 2,
	.चयन_addr = 0x4b
पूर्ण;

अटल काष्ठा tda827x_config tda827x_cfg_2_sw42 = अणु
	.init = philips_tda827x_tuner_init,
	.sleep = philips_tda827x_tuner_sleep,
	.config = 2,
	.चयन_addr = 0x42
पूर्ण;

/* ------------------------------------------------------------------ */

अटल काष्ठा tda1004x_config tda827x_lअगरeview_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config philips_tiger_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config cinergy_ht_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config cinergy_ht_pci_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config philips_tiger_s_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config pinnacle_pctv_310i_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config hauppauge_hvr_1110_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config asus_p7131_dual_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 2,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config lअगरeview_trio_config = अणु
	.demod_address = 0x09,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP00_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config tevion_dvbt220rf_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config md8800_dvbt_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x60,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config asus_p7131_4871_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 2,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config asus_p7131_hybrid_lna_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 2,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config kworld_dvb_t_210_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन= 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config avermedia_super_007_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x60,
	.antenna_चयन= 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config twinhan_dtv_dvb_3056_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP01_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x42,
	.tuner_address = 0x61,
	.antenna_चयन = 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config asus_tiger_3in1_config = अणु
	.demod_address = 0x0b,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन = 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा tda1004x_config asus_ps3_100_config = अणु
	.demod_address = 0x0b,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP11_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.i2c_gate      = 0x4b,
	.tuner_address = 0x61,
	.antenna_चयन = 1,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

/* ------------------------------------------------------------------
 * special हाल: this card uses saa713x GPIO22 क्रम the mode चयन
 */

अटल पूर्णांक ads_duo_tuner_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	philips_tda827x_tuner_init(fe);
	/* route TDA8275a AGC input to the channel decoder */
	saa7134_set_gpio(dev, 22, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक ads_duo_tuner_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	/* route TDA8275a AGC input to the analog IF chip*/
	saa7134_set_gpio(dev, 22, 0);
	philips_tda827x_tuner_sleep(fe);
	वापस 0;
पूर्ण

अटल काष्ठा tda827x_config ads_duo_cfg = अणु
	.init = ads_duo_tuner_init,
	.sleep = ads_duo_tuner_sleep,
	.config = 0
पूर्ण;

अटल काष्ठा tda1004x_config ads_tech_duo_config = अणु
	.demod_address = 0x08,
	.invert        = 1,
	.invert_oclk   = 0,
	.xtal_freq     = TDA10046_XTAL_16M,
	.agc_config    = TDA10046_AGC_TDA827X,
	.gpio_config   = TDA10046_GP00_I,
	.अगर_freq       = TDA10046_FREQ_045,
	.tuner_address = 0x61,
	.request_firmware = philips_tda1004x_request_firmware
पूर्ण;

अटल काष्ठा zl10353_config behold_h6_config = अणु
	.demod_address = 0x1e>>1,
	.no_tuner      = 1,
	.parallel_ts   = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा xc5000_config behold_x7_tunerconfig = अणु
	.i2c_address      = 0xc2>>1,
	.अगर_khz           = 4560,
	.radio_input      = XC5000_RADIO_FM1,
पूर्ण;

अटल काष्ठा zl10353_config behold_x7_config = अणु
	.demod_address = 0x1e>>1,
	.अगर2           = 45600,
	.no_tuner      = 1,
	.parallel_ts   = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा zl10353_config videomate_t750_zl10353_config = अणु
	.demod_address         = 0x0f,
	.no_tuner              = 1,
	.parallel_ts           = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा qt1010_config videomate_t750_qt1010_config = अणु
	.i2c_address = 0x62
पूर्ण;


/* ==================================================================
 * tda10086 based DVB-S cards, helper functions
 */

अटल काष्ठा tda10086_config flydvbs = अणु
	.demod_address = 0x0e,
	.invert = 0,
	.diseqc_tone = 0,
	.xtal_freq = TDA10086_XTAL_16M,
पूर्ण;

अटल काष्ठा tda10086_config sd1878_4m = अणु
	.demod_address = 0x0e,
	.invert = 0,
	.diseqc_tone = 0,
	.xtal_freq = TDA10086_XTAL_4M,
पूर्ण;

/* ------------------------------------------------------------------
 * special हाल: lnb supply is connected to the gated i2c
 */

अटल पूर्णांक md8800_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक res = -EIO;
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	अगर (fe->ops.i2c_gate_ctrl) अणु
		fe->ops.i2c_gate_ctrl(fe, 1);
		अगर (dev->original_set_voltage)
			res = dev->original_set_voltage(fe, voltage);
		fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण
	वापस res;
पूर्ण;

अटल पूर्णांक md8800_set_high_voltage(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	पूर्णांक res = -EIO;
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	अगर (fe->ops.i2c_gate_ctrl) अणु
		fe->ops.i2c_gate_ctrl(fe, 1);
		अगर (dev->original_set_high_voltage)
			res = dev->original_set_high_voltage(fe, arg);
		fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण
	वापस res;
पूर्ण;

अटल पूर्णांक md8800_set_voltage2(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा saa7134_dev *dev = fe->dvb->priv;
	u8 wbuf[2] = अणु 0x1f, 00 पूर्ण;
	u8 rbuf;
	काष्ठा i2c_msg msg[] = अणु अणु .addr = 0x08, .flags = 0, .buf = wbuf, .len = 1 पूर्ण,
				 अणु .addr = 0x08, .flags = I2C_M_RD, .buf = &rbuf, .len = 1 पूर्ण पूर्ण;

	अगर (i2c_transfer(&dev->i2c_adap, msg, 2) != 2)
		वापस -EIO;
	/* NOTE: this assumes that gpo1 is used, it might be bit 5 (gpo2) */
	अगर (voltage == SEC_VOLTAGE_18)
		wbuf[1] = rbuf | 0x10;
	अन्यथा
		wbuf[1] = rbuf & 0xef;
	msg[0].len = 2;
	i2c_transfer(&dev->i2c_adap, msg, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक md8800_set_high_voltage2(काष्ठा dvb_frontend *fe, दीर्घ arg)
अणु
	pr_warn("%s: sorry can't set high LNB supply voltage from here\n",
		__func__);
	वापस -EIO;
पूर्ण

/* ==================================================================
 * nxt200x based ATSC cards, helper functions
 */

अटल स्थिर काष्ठा nxt200x_config avertvhda180 = अणु
	.demod_address    = 0x0a,
पूर्ण;

अटल स्थिर काष्ठा nxt200x_config kworldatsc110 = अणु
	.demod_address    = 0x0a,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल काष्ठा mt312_config avertv_a700_mt312 = अणु
	.demod_address = 0x0e,
	.voltage_inverted = 1,
पूर्ण;

अटल काष्ठा zl10036_config avertv_a700_tuner = अणु
	.tuner_address = 0x60,
पूर्ण;

अटल काष्ठा mt312_config zl10313_compro_s350_config = अणु
	.demod_address = 0x0e,
पूर्ण;

अटल काष्ठा mt312_config zl10313_avermedia_a706_config = अणु
	.demod_address = 0x0e,
पूर्ण;

अटल काष्ठा lgdt3305_config hcw_lgdt3305_config = अणु
	.i2c_addr           = 0x0e,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_RISING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 1,
	.qam_अगर_khz         = 4000,
	.vsb_अगर_khz         = 3250,
पूर्ण;

अटल काष्ठा tda10048_config hcw_tda10048_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_SERIAL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3500,
	.dtv8_अगर_freq_khz = TDA10048_IF_4000,
	.clk_freq_khz     = TDA10048_CLK_16000,
	.disable_gate_access = 1,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x58, पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x58, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hcw_tda18271_config = अणु
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.config  = 3,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda829x_config tda829x_no_probe = अणु
	.probe_tuner = TDA829X_DONT_PROBE,
पूर्ण;

अटल काष्ठा tda10048_config zolid_tda10048_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_PARALLEL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3500,
	.dtv8_अगर_freq_khz = TDA10048_IF_4000,
	.clk_freq_khz     = TDA10048_CLK_16000,
	.disable_gate_access = 1,
पूर्ण;

अटल काष्ठा tda18271_config zolid_tda18271_config = अणु
	.gate    = TDA18271_GATE_ANALOG,
पूर्ण;

अटल काष्ठा tda10048_config dtv1000s_tda10048_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_PARALLEL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3800,
	.dtv8_अगर_freq_khz = TDA10048_IF_4300,
	.clk_freq_khz     = TDA10048_CLK_16000,
	.disable_gate_access = 1,
पूर्ण;

अटल काष्ठा tda18271_std_map dtv1000s_tda18271_std_map = अणु
	.dvbt_6   = अणु .अगर_freq = 3300, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_7   = अणु .अगर_freq = 3800, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_8   = अणु .अगर_freq = 4300, .agc_mode = 3, .std = 6,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config dtv1000s_tda18271_config = अणु
	.std_map = &dtv1000s_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
पूर्ण;

अटल काष्ठा lgs8gxx_config prohdtv_pro2_lgs8g75_config = अणु
	.prod = LGS8GXX_PROD_LGS8G75,
	.demod_address = 0x1d,
	.serial_ts = 0,
	.ts_clk_pol = 1,
	.ts_clk_gated = 0,
	.अगर_clk_freq = 30400, /* 30.4 MHz */
	.अगर_freq = 4000, /* 4.00 MHz */
	.अगर_neg_center = 0,
	.ext_adc = 0,
	.adc_चिन्हित = 1,
	.adc_vpp = 3, /* 2.0 Vpp */
	.अगर_neg_edge = 1,
पूर्ण;

अटल काष्ठा tda18271_config prohdtv_pro2_tda18271_config = अणु
	.gate = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda18271_std_map kworld_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 3,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config kworld_pc150u_tda18271_config = अणु
	.std_map = &kworld_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
	.config  = 3,	/* Use tuner callback क्रम AGC */
	.rf_cal_on_startup = 1
पूर्ण;

अटल काष्ठा s5h1411_config kworld_s5h1411_config = अणु
	.output_mode   = S5H1411_PARALLEL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.qam_अगर        = S5H1411_IF_4000,
	.vsb_अगर        = S5H1411_IF_3250,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   =
		S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;


/* ==================================================================
 * Core code
 */

अटल पूर्णांक dvb_init(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक ret;
	पूर्णांक attach_xc3028 = 0;
	काष्ठा vb2_dvb_frontend *fe0;
	काष्ठा vb2_queue *q;

	/* FIXME: add support क्रम multi-frontend */
	mutex_init(&dev->frontends.lock);
	INIT_LIST_HEAD(&dev->frontends.felist);

	pr_info("%s() allocating 1 frontend\n", __func__);
	fe0 = vb2_dvb_alloc_frontend(&dev->frontends, 1);
	अगर (!fe0) अणु
		pr_err("%s() failed to alloc\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* init काष्ठा vb2_dvb */
	dev->ts.nr_bufs    = 32;
	dev->ts.nr_packets = 32*4;
	fe0->dvb.name = dev->name;
	q = &fe0->dvb.dvbq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ;
	q->drv_priv = &dev->ts_q;
	q->ops = &saa7134_ts_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->buf_काष्ठा_size = माप(काष्ठा saa7134_buf);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;
	ret = vb2_queue_init(q);
	अगर (ret) अणु
		vb2_dvb_dealloc_frontends(&dev->frontends);
		वापस ret;
	पूर्ण

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_PINNACLE_300I_DVBT_PAL:
		pr_debug("pinnacle 300i dvb setup\n");
		fe0->dvb.frontend = dvb_attach(mt352_attach, &pinnacle_300i,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.tuner_ops.set_params = mt352_pinnacle_tuner_set_params;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_777:
	हाल SAA7134_BOARD_AVERMEDIA_A16AR:
		pr_debug("avertv 777 dvb setup\n");
		fe0->dvb.frontend = dvb_attach(mt352_attach, &avermedia_777,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x61,
				   TUNER_PHILIPS_TD1316);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A16D:
		pr_debug("AverMedia A16D dvb setup\n");
		fe0->dvb.frontend = dvb_attach(mt352_attach,
						&avermedia_xc3028_mt352_dev,
						&dev->i2c_adap);
		attach_xc3028 = 1;
		अवरोध;
	हाल SAA7134_BOARD_MD7134:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &medion_cardbus,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			/*
			 * The TV tuner on this board is actually NOT
			 * behind the demod i2c gate.
			 * However, the demod EEPROM is indeed there and it
			 * conflicts with the SAA7134 chip config EEPROM
			 * अगर the i2c gate is खोलो (since they have same
			 * bus addresses) resulting in card PCI SVID / SSID
			 * being garbage after a reboot from समय to समय.
			 *
			 * Let's just leave the gate permanently बंदd -
			 * saa7134_i2c_eeprom_md7134_gate() will बंद it क्रम
			 * us at probe समय अगर it was खोलो क्रम some reason.
			 */
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, medion_cardbus.tuner_address,
				   TUNER_PHILIPS_FMD1216ME_MK3);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_PHILIPS_TOUGH:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &philips_tu1216_60_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.tuner_ops.init = philips_tu1216_init;
			fe0->dvb.frontend->ops.tuner_ops.set_params = philips_tda6651_pll_set;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBTDUO:
	हाल SAA7134_BOARD_FLYDVBT_DUO_CARDBUS:
		अगर (configure_tda827x_fe(dev, &tda827x_lअगरeview_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_PHILIPS_EUROPA:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_300:
	हाल SAA7134_BOARD_ASUS_EUROPA_HYBRID:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &philips_europa_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dev->original_demod_sleep = fe0->dvb.frontend->ops.sleep;
			fe0->dvb.frontend->ops.sleep = philips_europa_demod_sleep;
			fe0->dvb.frontend->ops.tuner_ops.init = philips_europa_tuner_init;
			fe0->dvb.frontend->ops.tuner_ops.sleep = philips_europa_tuner_sleep;
			fe0->dvb.frontend->ops.tuner_ops.set_params = philips_td1316_tuner_set_params;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_TECHNOTREND_BUDGET_T3000:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &technotrend_budget_t3000_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dev->original_demod_sleep = fe0->dvb.frontend->ops.sleep;
			fe0->dvb.frontend->ops.sleep = philips_europa_demod_sleep;
			fe0->dvb.frontend->ops.tuner_ops.init = philips_europa_tuner_init;
			fe0->dvb.frontend->ops.tuner_ops.sleep = philips_europa_tuner_sleep;
			fe0->dvb.frontend->ops.tuner_ops.set_params = philips_td1316_tuner_set_params;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &philips_tu1216_61_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.tuner_ops.init = philips_tu1216_init;
			fe0->dvb.frontend->ops.tuner_ops.set_params = philips_tda6651_pll_set;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_DVBT_210:
		अगर (configure_tda827x_fe(dev, &kworld_dvb_t_210_config,
					 &tda827x_cfg_2) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
		fe0->dvb.frontend = dvb_attach(tda10048_attach,
					       &hcw_tda10048_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &hcw_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_PHILIPS_TIGER:
		अगर (configure_tda827x_fe(dev, &philips_tiger_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_PINNACLE_PCTV_310i:
		अगर (configure_tda827x_fe(dev, &pinnacle_pctv_310i_config,
					 &tda827x_cfg_1) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1110:
		अगर (configure_tda827x_fe(dev, &hauppauge_hvr_1110_config,
					 &tda827x_cfg_1) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
		fe0->dvb.frontend = dvb_attach(lgdt3305_attach,
					       &hcw_lgdt3305_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &hcw_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_P7131_DUAL:
		अगर (configure_tda827x_fe(dev, &asus_p7131_dual_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBT_LR301:
		अगर (configure_tda827x_fe(dev, &tda827x_lअगरeview_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_FLYDVB_TRIO:
		अगर (!use_frontend) अणु	/* terrestrial */
			अगर (configure_tda827x_fe(dev, &lअगरeview_trio_config,
						 &tda827x_cfg_0) < 0)
				जाओ detach_frontend;
		पूर्ण अन्यथा अणु		/* satellite */
			fe0->dvb.frontend = dvb_attach(tda10086_attach, &flydvbs, &dev->i2c_adap);
			अगर (fe0->dvb.frontend) अणु
				अगर (dvb_attach(tda826x_attach, fe0->dvb.frontend, 0x63,
									&dev->i2c_adap, 0) == शून्य) अणु
					pr_warn("%s: Lifeview Trio, No tda826x found!\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
				अगर (dvb_attach(isl6421_attach, fe0->dvb.frontend,
					       &dev->i2c_adap,
					       0x08, 0, 0, false) == शून्य) अणु
					pr_warn("%s: Lifeview Trio, No ISL6421 found!\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331:
	हाल SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &ads_tech_duo_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (dvb_attach(tda827x_attach,fe0->dvb.frontend,
				   ads_tech_duo_config.tuner_address, &dev->i2c_adap,
								&ads_duo_cfg) == शून्य) अणु
				pr_warn("no tda827x tuner found at addr: %02x\n",
					ads_tech_duo_config.tuner_address);
				जाओ detach_frontend;
			पूर्ण
		पूर्ण अन्यथा
			pr_warn("failed to attach tda10046\n");
		अवरोध;
	हाल SAA7134_BOARD_TEVION_DVBT_220RF:
		अगर (configure_tda827x_fe(dev, &tevion_dvbt220rf_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_MEDION_MD8800_QUADRO:
		अगर (!use_frontend) अणु     /* terrestrial */
			अगर (configure_tda827x_fe(dev, &md8800_dvbt_config,
						 &tda827x_cfg_0) < 0)
				जाओ detach_frontend;
		पूर्ण अन्यथा अणु        /* satellite */
			fe0->dvb.frontend = dvb_attach(tda10086_attach,
							&flydvbs, &dev->i2c_adap);
			अगर (fe0->dvb.frontend) अणु
				काष्ठा dvb_frontend *fe = fe0->dvb.frontend;
				u8 dev_id = dev->eedata[2];
				u8 data = 0xc4;
				काष्ठा i2c_msg msg = अणु.addr = 0x08, .flags = 0, .len = 1पूर्ण;

				अगर (dvb_attach(tda826x_attach, fe0->dvb.frontend,
						0x60, &dev->i2c_adap, 0) == शून्य) अणु
					pr_warn("%s: Medion Quadro, no tda826x found !\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
				अगर (dev_id != 0x08) अणु
					/* we need to खोलो the i2c gate (we know it exists) */
					fe->ops.i2c_gate_ctrl(fe, 1);
					अगर (dvb_attach(isl6405_attach, fe,
							&dev->i2c_adap, 0x08, 0, 0) == शून्य) अणु
						pr_warn("%s: Medion Quadro, no ISL6405 found !\n",
							__func__);
						जाओ detach_frontend;
					पूर्ण
					अगर (dev_id == 0x07) अणु
						/* fire up the 2nd section of the LNB supply since
						   we can't करो this from the other section */
						msg.buf = &data;
						i2c_transfer(&dev->i2c_adap, &msg, 1);
					पूर्ण
					fe->ops.i2c_gate_ctrl(fe, 0);
					dev->original_set_voltage = fe->ops.set_voltage;
					fe->ops.set_voltage = md8800_set_voltage;
					dev->original_set_high_voltage = fe->ops.enable_high_lnb_voltage;
					fe->ops.enable_high_lnb_voltage = md8800_set_high_voltage;
				पूर्ण अन्यथा अणु
					fe->ops.set_voltage = md8800_set_voltage2;
					fe->ops.enable_high_lnb_voltage = md8800_set_high_voltage2;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_AVERTVHD_A180:
		fe0->dvb.frontend = dvb_attach(nxt200x_attach, &avertvhda180,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend)
			dvb_attach(dvb_pll_attach, fe0->dvb.frontend, 0x61,
				   शून्य, DVB_PLL_TDHU2);
		अवरोध;
	हाल SAA7134_BOARD_ADS_INSTANT_HDTV_PCI:
	हाल SAA7134_BOARD_KWORLD_ATSC110:
		fe0->dvb.frontend = dvb_attach(nxt200x_attach, &kworldatsc110,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend)
			dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x61,
				   TUNER_PHILIPS_TUV1236D);
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_PC150U:
		saa7134_set_gpio(dev, 18, 1); /* Switch to digital mode */
		saa7134_tuner_callback(dev, 0,
				       TDA18271_CALLBACK_CMD_AGC_ENABLE, 1);
		fe0->dvb.frontend = dvb_attach(s5h1411_attach,
					       &kworld_s5h1411_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &kworld_pc150u_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBS_LR300:
		fe0->dvb.frontend = dvb_attach(tda10086_attach, &flydvbs,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (dvb_attach(tda826x_attach, fe0->dvb.frontend, 0x60,
				       &dev->i2c_adap, 0) == शून्य) अणु
				pr_warn("%s: No tda826x found!\n", __func__);
				जाओ detach_frontend;
			पूर्ण
			अगर (dvb_attach(isl6421_attach, fe0->dvb.frontend,
				       &dev->i2c_adap,
				       0x08, 0, 0, false) == शून्य) अणु
				pr_warn("%s: No ISL6421 found!\n", __func__);
				जाओ detach_frontend;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ASUS_EUROPA2_HYBRID:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
					       &medion_cardbus,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dev->original_demod_sleep = fe0->dvb.frontend->ops.sleep;
			fe0->dvb.frontend->ops.sleep = philips_europa_demod_sleep;

			dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, medion_cardbus.tuner_address,
				   TUNER_PHILIPS_FMD1216ME_MK3);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200A:
		fe0->dvb.frontend = dvb_attach(tda10046_attach,
				&philips_europa_config,
				&dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.tuner_ops.init = philips_td1316_tuner_init;
			fe0->dvb.frontend->ops.tuner_ops.set_params = philips_td1316_tuner_set_params;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_CINERGY_HT_PCMCIA:
		अगर (configure_tda827x_fe(dev, &cinergy_ht_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_CINERGY_HT_PCI:
		अगर (configure_tda827x_fe(dev, &cinergy_ht_pci_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_PHILIPS_TIGER_S:
		अगर (configure_tda827x_fe(dev, &philips_tiger_s_config,
					 &tda827x_cfg_2) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_ASUS_P7131_4871:
		अगर (configure_tda827x_fe(dev, &asus_p7131_4871_config,
					 &tda827x_cfg_2) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA:
		अगर (configure_tda827x_fe(dev, &asus_p7131_hybrid_lna_config,
					 &tda827x_cfg_2) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_SUPER_007:
		अगर (configure_tda827x_fe(dev, &avermedia_super_007_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_TWINHAN_DTV_DVB_3056:
		अगर (configure_tda827x_fe(dev, &twinhan_dtv_dvb_3056_config,
					 &tda827x_cfg_2_sw42) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_PHILIPS_SNAKE:
		fe0->dvb.frontend = dvb_attach(tda10086_attach, &flydvbs,
						&dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (dvb_attach(tda826x_attach, fe0->dvb.frontend, 0x60,
					&dev->i2c_adap, 0) == शून्य) अणु
				pr_warn("%s: No tda826x found!\n", __func__);
				जाओ detach_frontend;
			पूर्ण
			अगर (dvb_attach(lnbp21_attach, fe0->dvb.frontend,
					&dev->i2c_adap, 0, 0) == शून्य) अणु
				pr_warn("%s: No lnbp21 found!\n", __func__);
				जाओ detach_frontend;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_CREATIX_CTX953:
		अगर (configure_tda827x_fe(dev, &md8800_dvbt_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_MSI_TVANYWHERE_AD11:
		अगर (configure_tda827x_fe(dev, &philips_tiger_s_config,
					 &tda827x_cfg_2) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		pr_debug("AverMedia E506R dvb setup\n");
		saa7134_set_gpio(dev, 25, 0);
		msleep(10);
		saa7134_set_gpio(dev, 25, 1);
		fe0->dvb.frontend = dvb_attach(mt352_attach,
						&avermedia_xc3028_mt352_dev,
						&dev->i2c_adap);
		attach_xc3028 = 1;
		अवरोध;
	हाल SAA7134_BOARD_MD7134_BRIDGE_2:
		fe0->dvb.frontend = dvb_attach(tda10086_attach,
						&sd1878_4m, &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			काष्ठा dvb_frontend *fe;
			अगर (dvb_attach(dvb_pll_attach, fe0->dvb.frontend, 0x60,
				  &dev->i2c_adap, DVB_PLL_PHILIPS_SD1878_TDA8261) == शून्य) अणु
				pr_warn("%s: MD7134 DVB-S, no SD1878 found !\n",
					__func__);
				जाओ detach_frontend;
			पूर्ण
			/* we need to खोलो the i2c gate (we know it exists) */
			fe = fe0->dvb.frontend;
			fe->ops.i2c_gate_ctrl(fe, 1);
			अगर (dvb_attach(isl6405_attach, fe,
					&dev->i2c_adap, 0x08, 0, 0) == शून्य) अणु
				pr_warn("%s: MD7134 DVB-S, no ISL6405 found !\n",
					__func__);
				जाओ detach_frontend;
			पूर्ण
			fe->ops.i2c_gate_ctrl(fe, 0);
			dev->original_set_voltage = fe->ops.set_voltage;
			fe->ops.set_voltage = md8800_set_voltage;
			dev->original_set_high_voltage = fe->ops.enable_high_lnb_voltage;
			fe->ops.enable_high_lnb_voltage = md8800_set_high_voltage;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M103:
		saa7134_set_gpio(dev, 25, 0);
		msleep(10);
		saa7134_set_gpio(dev, 25, 1);
		fe0->dvb.frontend = dvb_attach(mt352_attach,
						&avermedia_xc3028_mt352_dev,
						&dev->i2c_adap);
		attach_xc3028 = 1;
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_TIGER_3IN1:
		अगर (!use_frontend) अणु     /* terrestrial */
			अगर (configure_tda827x_fe(dev, &asus_tiger_3in1_config,
							&tda827x_cfg_2) < 0)
				जाओ detach_frontend;
		पूर्ण अन्यथा अणु		/* satellite */
			fe0->dvb.frontend = dvb_attach(tda10086_attach,
						&flydvbs, &dev->i2c_adap);
			अगर (fe0->dvb.frontend) अणु
				अगर (dvb_attach(tda826x_attach,
						fe0->dvb.frontend, 0x60,
						&dev->i2c_adap, 0) == शून्य) अणु
					pr_warn("%s: Asus Tiger 3in1, no tda826x found!\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
				अगर (dvb_attach(lnbp21_attach, fe0->dvb.frontend,
						&dev->i2c_adap, 0, 0) == शून्य) अणु
					pr_warn("%s: Asus Tiger 3in1, no lnbp21 found!\n",
						__func__);
					जाओ detach_frontend;
			       पूर्ण
		       पूर्ण
	       पूर्ण
	       अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_PS3_100:
		अगर (!use_frontend) अणु     /* terrestrial */
			अगर (configure_tda827x_fe(dev, &asus_ps3_100_config,
						 &tda827x_cfg_2) < 0)
				जाओ detach_frontend;
	       पूर्ण अन्यथा अणु                /* satellite */
			fe0->dvb.frontend = dvb_attach(tda10086_attach,
						       &flydvbs, &dev->i2c_adap);
			अगर (fe0->dvb.frontend) अणु
				अगर (dvb_attach(tda826x_attach,
					       fe0->dvb.frontend, 0x60,
					       &dev->i2c_adap, 0) == शून्य) अणु
					pr_warn("%s: Asus My Cinema PS3-100, no tda826x found!\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
				अगर (dvb_attach(lnbp21_attach, fe0->dvb.frontend,
					       &dev->i2c_adap, 0, 0) == शून्य) अणु
					pr_warn("%s: Asus My Cinema PS3-100, no lnbp21 found!\n",
						__func__);
					जाओ detach_frontend;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ASUSTeK_TIGER:
		अगर (configure_tda827x_fe(dev, &philips_tiger_config,
					 &tda827x_cfg_0) < 0)
			जाओ detach_frontend;
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_H6:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
						&behold_h6_config,
						&dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x61,
				   TUNER_PHILIPS_FMD1216MEX_MK3);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_X7:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
						&behold_x7_config,
						&dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(xc5000_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, &behold_x7_tunerconfig);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_H7:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
						&behold_x7_config,
						&dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			dvb_attach(xc5000_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, &behold_x7_tunerconfig);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A700_PRO:
	हाल SAA7134_BOARD_AVERMEDIA_A700_HYBRID:
		/* Zarlink ZL10313 */
		fe0->dvb.frontend = dvb_attach(mt312_attach,
			&avertv_a700_mt312, &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			अगर (dvb_attach(zl10036_attach, fe0->dvb.frontend,
					&avertv_a700_tuner, &dev->i2c_adap) == शून्य) अणु
				pr_warn("%s: No zl10036 found!\n",
					__func__);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_S350:
		fe0->dvb.frontend = dvb_attach(mt312_attach,
				&zl10313_compro_s350_config, &dev->i2c_adap);
		अगर (fe0->dvb.frontend)
			अगर (dvb_attach(zl10039_attach, fe0->dvb.frontend,
					0x60, &dev->i2c_adap) == शून्य)
				pr_warn("%s: No zl10039 found!\n",
					__func__);

		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_T750:
		fe0->dvb.frontend = dvb_attach(zl10353_attach,
						&videomate_t750_zl10353_config,
						&dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			अगर (dvb_attach(qt1010_attach,
					fe0->dvb.frontend,
					&dev->i2c_adap,
					&videomate_t750_qt1010_config) == शून्य)
				pr_warn("error attaching QT1010\n");
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ZOLID_HYBRID_PCI:
		fe0->dvb.frontend = dvb_attach(tda10048_attach,
					       &zolid_tda10048_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &zolid_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S:
		fe0->dvb.frontend = dvb_attach(tda10048_attach,
					       &dtv1000s_tda10048_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &dtv1000s_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
		/* Switch to digital mode */
		saa7134_tuner_callback(dev, 0,
				       TDA18271_CALLBACK_CMD_AGC_ENABLE, 1);
		fe0->dvb.frontend = dvb_attach(mb86a20s_attach,
					       &kworld_mb86a20s_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			fe0->dvb.frontend->ops.i2c_gate_ctrl = kworld_sbtvd_gate_ctrl;
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &kworld_tda18271_config);
		पूर्ण

		/* mb86a20s need to use the I2C gateway */
		अवरोध;
	हाल SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
		fe0->dvb.frontend = dvb_attach(lgs8gxx_attach,
					       &prohdtv_pro2_lgs8g75_config,
					       &dev->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_adap, 0x4b,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_adap,
				   &prohdtv_pro2_tda18271_config);
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A706:
		/* Enable all DVB-S devices now */
		/* CE5039 DVB-S tuner SLEEP pin low */
		saa7134_set_gpio(dev, 23, 0);
		/* CE6313 DVB-S demod SLEEP pin low */
		saa7134_set_gpio(dev, 9, 0);
		/* CE6313 DVB-S demod RESET# pin high */
		saa7134_set_gpio(dev, 25, 1);
		msleep(1);
		fe0->dvb.frontend = dvb_attach(mt312_attach,
				&zl10313_avermedia_a706_config, &dev->i2c_adap);
		अगर (fe0->dvb.frontend) अणु
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			अगर (dvb_attach(zl10039_attach, fe0->dvb.frontend,
					0x60, &dev->i2c_adap) == शून्य)
				pr_warn("%s: No zl10039 found!\n",
					__func__);
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("Huh? unknown DVB card?\n");
		अवरोध;
	पूर्ण

	अगर (attach_xc3028) अणु
		काष्ठा dvb_frontend *fe;
		काष्ठा xc2028_config cfg = अणु
			.i2c_adap  = &dev->i2c_adap,
			.i2c_addr  = 0x61,
		पूर्ण;

		अगर (!fe0->dvb.frontend)
			जाओ detach_frontend;

		fe = dvb_attach(xc2028_attach, fe0->dvb.frontend, &cfg);
		अगर (!fe) अणु
			pr_err("%s/2: xc3028 attach failed\n",
			       dev->name);
			जाओ detach_frontend;
		पूर्ण
	पूर्ण

	अगर (शून्य == fe0->dvb.frontend) अणु
		pr_err("%s/dvb: frontend initialization failed\n", dev->name);
		जाओ detach_frontend;
	पूर्ण
	/* define general-purpose callback poपूर्णांकer */
	fe0->dvb.frontend->callback = saa7134_tuner_callback;

	/* रेजिस्टर everything अन्यथा */
#अगर_अघोषित CONFIG_MEDIA_CONTROLLER_DVB
	ret = vb2_dvb_रेजिस्टर_bus(&dev->frontends, THIS_MODULE, dev,
				   &dev->pci->dev, शून्य,
				   adapter_nr, 0);
#अन्यथा
	ret = vb2_dvb_रेजिस्टर_bus(&dev->frontends, THIS_MODULE, dev,
				   &dev->pci->dev, dev->media_dev,
				   adapter_nr, 0);
#पूर्ण_अगर

	/* this sequence is necessary to make the tda1004x load its firmware
	 * and to enter analog mode of hybrid boards
	 */
	अगर (!ret) अणु
		अगर (fe0->dvb.frontend->ops.init)
			fe0->dvb.frontend->ops.init(fe0->dvb.frontend);
		अगर (fe0->dvb.frontend->ops.sleep)
			fe0->dvb.frontend->ops.sleep(fe0->dvb.frontend);
		अगर (fe0->dvb.frontend->ops.tuner_ops.sleep)
			fe0->dvb.frontend->ops.tuner_ops.sleep(fe0->dvb.frontend);
	पूर्ण
	वापस ret;

detach_frontend:
	vb2_dvb_dealloc_frontends(&dev->frontends);
	vb2_queue_release(&fe0->dvb.dvbq);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dvb_fini(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा vb2_dvb_frontend *fe0;

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&dev->frontends, 1);
	अगर (!fe0)
		वापस -EINVAL;

	/* FIXME: I suspect that this code is bogus, since the entry क्रम
	   Pinnacle 300I DVB-T PAL alपढ़ोy defines the proper init to allow
	   the detection of mt2032 (TDA9887_PORT2_INACTIVE)
	 */
	अगर (dev->board == SAA7134_BOARD_PINNACLE_300I_DVBT_PAL) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;
		अटल पूर्णांक on  = TDA9887_PRESENT | TDA9887_PORT2_INACTIVE;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv  = &on;

		/* otherwise we करोn't detect the tuner on next insmod */
		saa_call_all(dev, tuner, s_config, &tda9887_cfg);
	पूर्ण अन्यथा अगर (dev->board == SAA7134_BOARD_MEDION_MD8800_QUADRO) अणु
		अगर ((dev->eedata[2] == 0x07) && use_frontend) अणु
			/* turn off the 2nd lnb supply */
			u8 data = 0x80;
			काष्ठा i2c_msg msg = अणु.addr = 0x08, .buf = &data, .flags = 0, .len = 1पूर्ण;
			काष्ठा dvb_frontend *fe;
			fe = fe0->dvb.frontend;
			अगर (fe->ops.i2c_gate_ctrl) अणु
				fe->ops.i2c_gate_ctrl(fe, 1);
				i2c_transfer(&dev->i2c_adap, &msg, 1);
				fe->ops.i2c_gate_ctrl(fe, 0);
			पूर्ण
		पूर्ण
	पूर्ण
	vb2_dvb_unरेजिस्टर_bus(&dev->frontends);
	vb2_queue_release(&fe0->dvb.dvbq);
	वापस 0;
पूर्ण

अटल काष्ठा saa7134_mpeg_ops dvb_ops = अणु
	.type          = SAA7134_MPEG_DVB,
	.init          = dvb_init,
	.fini          = dvb_fini,
पूर्ण;

अटल पूर्णांक __init dvb_रेजिस्टर(व्योम)
अणु
	वापस saa7134_ts_रेजिस्टर(&dvb_ops);
पूर्ण

अटल व्योम __निकास dvb_unरेजिस्टर(व्योम)
अणु
	saa7134_ts_unरेजिस्टर(&dvb_ops);
पूर्ण

module_init(dvb_रेजिस्टर);
module_निकास(dvb_unरेजिस्टर);
