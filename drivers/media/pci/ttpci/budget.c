<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * budget.c: driver क्रम the SAA7146 based Budget DVB cards
 *
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * 26feb2004 Support क्रम FS Activy Card (Grundig tuner) by
 *           Michael Dreher <michael@5करोt1.de>,
 *           Oliver Endriss <o.endriss@gmx.de> and
 *           Andreas 'randy' Weinberger
 *
 * the project's page is at https://linuxtv.org
 */

#समावेश "budget.h"
#समावेश "stv0299.h"
#समावेश "ves1x93.h"
#समावेश "ves1820.h"
#समावेश "l64781.h"
#समावेश "tda8083.h"
#समावेश "s5h1420.h"
#समावेश "tda10086.h"
#समावेश "tda826x.h"
#समावेश "lnbp21.h"
#समावेश "bsru6.h"
#समावेश "bsbe1.h"
#समावेश "tdhd1.h"
#समावेश "stv6110x.h"
#समावेश "stv090x.h"
#समावेश "isl6423.h"
#समावेश "lnbh24.h"


अटल पूर्णांक diseqc_method;
module_param(diseqc_method, पूर्णांक, 0444);
MODULE_PARM_DESC(diseqc_method, "Select DiSEqC method for subsystem id 13c2:1003, 0: default, 1: more reliable (for newer revisions only)");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल व्योम Set22K (काष्ठा budget *budget, पूर्णांक state)
अणु
	काष्ठा saa7146_dev *dev=budget->dev;
	dprपूर्णांकk(2, "budget: %p\n", budget);
	saa7146_setgpio(dev, 3, (state ? SAA7146_GPIO_OUTHI : SAA7146_GPIO_OUTLO));
पूर्ण

/* Diseqc functions only क्रम TT Budget card */
/* taken from the Skyvision DVB driver by
   Ralph Metzler <rjkm@metzlerbros.de> */

अटल व्योम DiseqcSendBit (काष्ठा budget *budget, पूर्णांक data)
अणु
	काष्ठा saa7146_dev *dev=budget->dev;
	dprपूर्णांकk(2, "budget: %p\n", budget);

	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
	udelay(data ? 500 : 1000);
	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
	udelay(data ? 1000 : 500);
पूर्ण

अटल व्योम DiseqcSendByte (काष्ठा budget *budget, पूर्णांक data)
अणु
	पूर्णांक i, par=1, d;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	क्रम (i=7; i>=0; i--) अणु
		d = (data>>i)&1;
		par ^= d;
		DiseqcSendBit(budget, d);
	पूर्ण

	DiseqcSendBit(budget, par);
पूर्ण

अटल पूर्णांक SendDiSEqCMsg (काष्ठा budget *budget, पूर्णांक len, u8 *msg, अचिन्हित दीर्घ burst)
अणु
	काष्ठा saa7146_dev *dev=budget->dev;
	पूर्णांक i;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
	mdelay(16);

	क्रम (i=0; i<len; i++)
		DiseqcSendByte(budget, msg[i]);

	mdelay(16);

	अगर (burst!=-1) अणु
		अगर (burst)
			DiseqcSendByte(budget, 0xff);
		अन्यथा अणु
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
			mdelay(12);
			udelay(500);
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
		पूर्ण
		msleep(20);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *   Routines क्रम the Fujitsu Siemens Activy budget card
 *   22 kHz tone and DiSEqC are handled by the frontend.
 *   Voltage must be set here.
 *   GPIO 1: LNBP EN, GPIO 2: LNBP VSEL
 */
अटल पूर्णांक SetVoltage_Activy(काष्ठा budget *budget,
			     क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा saa7146_dev *dev=budget->dev;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	चयन (voltage) अणु
		हाल SEC_VOLTAGE_13:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI);
			saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTLO);
			अवरोध;
		हाल SEC_VOLTAGE_18:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI);
			saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);
			अवरोध;
		हाल SEC_VOLTAGE_OFF:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTLO);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक siemens_budget_set_voltage(काष्ठा dvb_frontend *fe,
				      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;

	वापस SetVoltage_Activy (budget, voltage);
पूर्ण

अटल पूर्णांक budget_set_tone(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		Set22K (budget, 1);
		अवरोध;

	हाल SEC_TONE_OFF:
		Set22K (budget, 0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक budget_diseqc_send_master_cmd(काष्ठा dvb_frontend* fe, काष्ठा dvb_diseqc_master_cmd* cmd)
अणु
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;

	SendDiSEqCMsg (budget, cmd->msg_len, cmd->msg, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक budget_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;

	SendDiSEqCMsg (budget, 0, शून्य, minicmd);

	वापस 0;
पूर्ण

अटल पूर्णांक alps_bsrv2_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;
	u8 pwr = 0;
	u8 buf[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = buf, .len = माप(buf) पूर्ण;
	u32 भाग = (c->frequency + 479500) / 125;

	अगर (c->frequency > 2000000)
		pwr = 3;
	अन्यथा अगर (c->frequency > 1800000)
		pwr = 2;
	अन्यथा अगर (c->frequency > 1600000)
		pwr = 1;
	अन्यथा अगर (c->frequency > 1200000)
		pwr = 0;
	अन्यथा अगर (c->frequency >= 1100000)
		pwr = 1;
	अन्यथा pwr = 2;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = ((भाग & 0x18000) >> 10) | 0x95;
	buf[3] = (pwr << 6) | 0x30;

	// NOTE: since we're using a prescaler of 2, we set the
	// भागisor frequency to 62.5kHz and भागide by 125 above

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा ves1x93_config alps_bsrv2_config =
अणु
	.demod_address = 0x08,
	.xin = 90100000UL,
	.invert_pwm = 0,
पूर्ण;

अटल पूर्णांक alps_tdbe2_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x62, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (c->frequency + 35937500 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x85 | ((भाग >> 10) & 0x60);
	data[3] = (c->frequency < 174000000 ? 0x88 : c->frequency < 470000000 ? 0x84 : 0x81);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा ves1820_config alps_tdbe2_config = अणु
	.demod_address = 0x09,
	.xin = 57840000UL,
	.invert = 1,
	.selagc = VES1820_SELAGC_SIGNAMPERR,
पूर्ण;

अटल पूर्णांक grundig_29504_401_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget *budget = fe->dvb->priv;
	u8 *tuner_addr = fe->tuner_priv;
	u32 भाग;
	u8 cfg, cpump, band_select;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	अगर (tuner_addr)
		msg.addr = *tuner_addr;
	अन्यथा
		msg.addr = 0x61;

	भाग = (36125000 + c->frequency) / 166666;

	cfg = 0x88;

	अगर (c->frequency < 175000000)
		cpump = 2;
	अन्यथा अगर (c->frequency < 390000000)
		cpump = 1;
	अन्यथा अगर (c->frequency < 470000000)
		cpump = 2;
	अन्यथा अगर (c->frequency < 750000000)
		cpump = 1;
	अन्यथा
		cpump = 3;

	अगर (c->frequency < 175000000)
		band_select = 0x0e;
	अन्यथा अगर (c->frequency < 470000000)
		band_select = 0x05;
	अन्यथा
		band_select = 0x03;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = ((भाग >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_select;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा l64781_config grundig_29504_401_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल काष्ठा l64781_config grundig_29504_401_config_activy = अणु
	.demod_address = 0x54,
पूर्ण;

अटल u8 tuner_address_grundig_29504_401_activy = 0x60;

अटल पूर्णांक grundig_29504_451_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = c->frequency / 125;
	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x8e;
	data[3] = 0x00;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा tda8083_config grundig_29504_451_config = अणु
	.demod_address = 0x68,
पूर्ण;

अटल पूर्णांक s5h1420_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा budget* budget = (काष्ठा budget*) fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = c->frequency / 1000;
	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0xc2;

	अगर (भाग < 1450)
		data[3] = 0x00;
	अन्यथा अगर (भाग < 1850)
		data[3] = 0x40;
	अन्यथा अगर (भाग < 2000)
		data[3] = 0x80;
	अन्यथा
		data[3] = 0xc0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&budget->i2c_adap, &msg, 1) != 1) वापस -EIO;

	वापस 0;
पूर्ण

अटल काष्ठा s5h1420_config s5h1420_config = अणु
	.demod_address = 0x53,
	.invert = 1,
	.cdclk_polarity = 1,
पूर्ण;

अटल काष्ठा tda10086_config tda10086_config = अणु
	.demod_address = 0x0e,
	.invert = 0,
	.diseqc_tone = 1,
	.xtal_freq = TDA10086_XTAL_16M,
पूर्ण;

अटल स्थिर काष्ठा stv0299_config alps_bsru6_config_activy = अणु
	.demod_address = 0x68,
	.inittab = alps_bsru6_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.op0_off = 1,
	.min_delay_ms = 100,
	.set_symbol_rate = alps_bsru6_set_symbol_rate,
पूर्ण;

अटल स्थिर काष्ठा stv0299_config alps_bsbe1_config_activy = अणु
	.demod_address = 0x68,
	.inittab = alps_bsbe1_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.op0_off = 1,
	.min_delay_ms = 100,
	.set_symbol_rate = alps_bsbe1_set_symbol_rate,
पूर्ण;

अटल पूर्णांक alps_tdhd1_204_request_firmware(काष्ठा dvb_frontend *fe, स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा budget *budget = (काष्ठा budget *)fe->dvb->priv;

	वापस request_firmware(fw, name, &budget->dev->pci->dev);
पूर्ण


अटल पूर्णांक i2c_पढ़ोreg(काष्ठा i2c_adapter *i2c, u8 adr, u8 reg)
अणु
	u8 val;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = adr, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = adr, .flags = I2C_M_RD, .buf = &val, .len = 1 पूर्ण
	पूर्ण;

	वापस (i2c_transfer(i2c, msg, 2) != 2) ? -EIO : val;
पूर्ण

अटल u8 पढ़ो_pwm(काष्ठा budget* budget)
अणु
	u8 b = 0xff;
	u8 pwm;
	काष्ठा i2c_msg msg[] = अणु अणु .addr = 0x50,.flags = 0,.buf = &b,.len = 1 पूर्ण,
				 अणु .addr = 0x50,.flags = I2C_M_RD,.buf = &pwm,.len = 1पूर्ण पूर्ण;

	अगर ((i2c_transfer(&budget->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	वापस pwm;
पूर्ण

अटल काष्ठा stv090x_config tt1600_stv090x_config = अणु
	.device			= STV0903,
	.demod_mode		= STV090x_SINGLE,
	.clk_mode		= STV090x_CLK_EXT,

	.xtal			= 13500000,
	.address		= 0x68,

	.ts1_mode		= STV090x_TSMODE_DVBCI,
	.ts2_mode		= STV090x_TSMODE_SERIAL_CONTINUOUS,

	.repeater_level		= STV090x_RPTLEVEL_16,

	.tuner_init		= शून्य,
	.tuner_sleep		= शून्य,
	.tuner_set_mode		= शून्य,
	.tuner_set_frequency	= शून्य,
	.tuner_get_frequency	= शून्य,
	.tuner_set_bandwidth	= शून्य,
	.tuner_get_bandwidth	= शून्य,
	.tuner_set_bbgain	= शून्य,
	.tuner_get_bbgain	= शून्य,
	.tuner_set_refclk	= शून्य,
	.tuner_get_status	= शून्य,
पूर्ण;

अटल काष्ठा stv6110x_config tt1600_stv6110x_config = अणु
	.addr			= 0x60,
	.refclk			= 27000000,
	.clk_भाग		= 2,
पूर्ण;

अटल काष्ठा isl6423_config tt1600_isl6423_config = अणु
	.current_max		= SEC_CURRENT_515m,
	.curlim			= SEC_CURRENT_LIM_ON,
	.mod_बाह्य		= 1,
	.addr			= 0x08,
पूर्ण;

अटल व्योम frontend_init(काष्ठा budget *budget)
अणु
	(व्योम)alps_bsbe1_config; /* aव्योम warning */

	चयन(budget->dev->pci->subप्रणाली_device) अणु
	हाल 0x1003: // Hauppauge/TT Nova budget (stv0299/ALPS BSRU6(tsa5059) OR ves1893/ALPS BSRV2(sp5659))
	हाल 0x1013:
		// try the ALPS BSRV2 first of all
		budget->dvb_frontend = dvb_attach(ves1x93_attach, &alps_bsrv2_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsrv2_tuner_set_params;
			budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
			budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
			budget->dvb_frontend->ops.set_tone = budget_set_tone;
			अवरोध;
		पूर्ण

		// try the ALPS BSRU6 now
		budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsru6_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
			budget->dvb_frontend->tuner_priv = &budget->i2c_adap;
			अगर (budget->dev->pci->subप्रणाली_device == 0x1003 && diseqc_method == 0) अणु
				budget->dvb_frontend->ops.diseqc_send_master_cmd = budget_diseqc_send_master_cmd;
				budget->dvb_frontend->ops.diseqc_send_burst = budget_diseqc_send_burst;
				budget->dvb_frontend->ops.set_tone = budget_set_tone;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1004: // Hauppauge/TT DVB-C budget (ves1820/ALPS TDBE2(sp5659))

		budget->dvb_frontend = dvb_attach(ves1820_attach, &alps_tdbe2_config, &budget->i2c_adap, पढ़ो_pwm(budget));
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_tdbe2_tuner_set_params;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x1005: // Hauppauge/TT Nova-T budget (L64781/Grundig 29504-401(tsa5060))

		budget->dvb_frontend = dvb_attach(l64781_attach, &grundig_29504_401_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = grundig_29504_401_tuner_set_params;
			budget->dvb_frontend->tuner_priv = शून्य;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x4f52: /* Cards based on Philips Semi Sylt PCI ref. design */
		budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsru6_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			prपूर्णांकk(KERN_INFO "budget: tuner ALPS BSRU6 in Philips Semi. Sylt detected\n");
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
			budget->dvb_frontend->tuner_priv = &budget->i2c_adap;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x4f60: /* Fujitsu Siemens Activy Budget-S PCI rev AL (stv0299/tsa5059) */
	अणु
		पूर्णांक subtype = i2c_पढ़ोreg(&budget->i2c_adap, 0x50, 0x67);

		अगर (subtype < 0)
			अवरोध;
		/* fixme: find a better way to identअगरy the card */
		अगर (subtype < 0x36) अणु
			/* assume ALPS BSRU6 */
			budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsru6_config_activy, &budget->i2c_adap);
			अगर (budget->dvb_frontend) अणु
				prपूर्णांकk(KERN_INFO "budget: tuner ALPS BSRU6 detected\n");
				budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
				budget->dvb_frontend->tuner_priv = &budget->i2c_adap;
				budget->dvb_frontend->ops.set_voltage = siemens_budget_set_voltage;
				budget->dvb_frontend->ops.dishnetwork_send_legacy_command = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* assume ALPS BSBE1 */
			/* reset tuner */
			saa7146_setgpio(budget->dev, 3, SAA7146_GPIO_OUTLO);
			msleep(50);
			saa7146_setgpio(budget->dev, 3, SAA7146_GPIO_OUTHI);
			msleep(250);
			budget->dvb_frontend = dvb_attach(stv0299_attach, &alps_bsbe1_config_activy, &budget->i2c_adap);
			अगर (budget->dvb_frontend) अणु
				prपूर्णांकk(KERN_INFO "budget: tuner ALPS BSBE1 detected\n");
				budget->dvb_frontend->ops.tuner_ops.set_params = alps_bsbe1_tuner_set_params;
				budget->dvb_frontend->tuner_priv = &budget->i2c_adap;
				budget->dvb_frontend->ops.set_voltage = siemens_budget_set_voltage;
				budget->dvb_frontend->ops.dishnetwork_send_legacy_command = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	हाल 0x4f61: // Fujitsu Siemens Activy Budget-S PCI rev GR (tda8083/Grundig 29504-451(tsa5522))
		budget->dvb_frontend = dvb_attach(tda8083_attach, &grundig_29504_451_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = grundig_29504_451_tuner_set_params;
			budget->dvb_frontend->ops.set_voltage = siemens_budget_set_voltage;
			budget->dvb_frontend->ops.dishnetwork_send_legacy_command = शून्य;
		पूर्ण
		अवरोध;

	हाल 0x5f60: /* Fujitsu Siemens Activy Budget-T PCI rev AL (tda10046/ALPS TDHD1-204A) */
		budget->dvb_frontend = dvb_attach(tda10046_attach, &alps_tdhd1_204a_config, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->ops.tuner_ops.set_params = alps_tdhd1_204a_tuner_set_params;
			budget->dvb_frontend->tuner_priv = &budget->i2c_adap;
		पूर्ण
		अवरोध;

	हाल 0x5f61: /* Fujitsu Siemens Activy Budget-T PCI rev GR (L64781/Grundig 29504-401(tsa5060)) */
		budget->dvb_frontend = dvb_attach(l64781_attach, &grundig_29504_401_config_activy, &budget->i2c_adap);
		अगर (budget->dvb_frontend) अणु
			budget->dvb_frontend->tuner_priv = &tuner_address_grundig_29504_401_activy;
			budget->dvb_frontend->ops.tuner_ops.set_params = grundig_29504_401_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल 0x1016: // Hauppauge/TT Nova-S SE (samsung s5h1420/????(tda8260))
	अणु
		काष्ठा dvb_frontend *fe;

		fe = dvb_attach(s5h1420_attach, &s5h1420_config, &budget->i2c_adap);
		अगर (fe) अणु
			fe->ops.tuner_ops.set_params = s5h1420_tuner_set_params;
			budget->dvb_frontend = fe;
			अगर (dvb_attach(lnbp21_attach, fe, &budget->i2c_adap,
				       0, 0) == शून्य) अणु
				prपूर्णांकk("%s: No LNBP21 found!\n", __func__);
				जाओ error_out;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
		fallthrough;
	हाल 0x1018: // TT Budget-S-1401 (philips tda10086/philips tda8262)
	अणु
		काष्ठा dvb_frontend *fe;

		// gpio2 is connected to CLB - reset it + leave it high
		saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTLO);
		msleep(1);
		saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
		msleep(1);

		fe = dvb_attach(tda10086_attach, &tda10086_config, &budget->i2c_adap);
		अगर (fe) अणु
			budget->dvb_frontend = fe;
			अगर (dvb_attach(tda826x_attach, fe, 0x60,
				       &budget->i2c_adap, 0) == शून्य)
				prपूर्णांकk("%s: No tda826x found!\n", __func__);
			अगर (dvb_attach(lnbp21_attach, fe,
				       &budget->i2c_adap, 0, 0) == शून्य) अणु
				prपूर्णांकk("%s: No LNBP21 found!\n", __func__);
				जाओ error_out;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
		fallthrough;

	हाल 0x101c: अणु /* TT S2-1600 */
			स्थिर काष्ठा stv6110x_devctl *ctl;
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTLO);
			msleep(50);
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
			msleep(250);

			budget->dvb_frontend = dvb_attach(stv090x_attach,
							  &tt1600_stv090x_config,
							  &budget->i2c_adap,
							  STV090x_DEMODULATOR_0);

			अगर (budget->dvb_frontend) अणु

				ctl = dvb_attach(stv6110x_attach,
						 budget->dvb_frontend,
						 &tt1600_stv6110x_config,
						 &budget->i2c_adap);

				अगर (ctl) अणु
					tt1600_stv090x_config.tuner_init	  = ctl->tuner_init;
					tt1600_stv090x_config.tuner_sleep	  = ctl->tuner_sleep;
					tt1600_stv090x_config.tuner_set_mode	  = ctl->tuner_set_mode;
					tt1600_stv090x_config.tuner_set_frequency = ctl->tuner_set_frequency;
					tt1600_stv090x_config.tuner_get_frequency = ctl->tuner_get_frequency;
					tt1600_stv090x_config.tuner_set_bandwidth = ctl->tuner_set_bandwidth;
					tt1600_stv090x_config.tuner_get_bandwidth = ctl->tuner_get_bandwidth;
					tt1600_stv090x_config.tuner_set_bbgain	  = ctl->tuner_set_bbgain;
					tt1600_stv090x_config.tuner_get_bbgain	  = ctl->tuner_get_bbgain;
					tt1600_stv090x_config.tuner_set_refclk	  = ctl->tuner_set_refclk;
					tt1600_stv090x_config.tuner_get_status	  = ctl->tuner_get_status;

					/* call the init function once to initialize
					   tuner's clock output divider and demod's
					   master घड़ी */
					अगर (budget->dvb_frontend->ops.init)
						budget->dvb_frontend->ops.init(budget->dvb_frontend);

					अगर (dvb_attach(isl6423_attach,
						       budget->dvb_frontend,
						       &budget->i2c_adap,
						       &tt1600_isl6423_config) == शून्य) अणु
						prपूर्णांकk(KERN_ERR "%s: No Intersil ISL6423 found!\n", __func__);
						जाओ error_out;
					पूर्ण
				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_ERR "%s: No STV6110(A) Silicon Tuner found!\n", __func__);
					जाओ error_out;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x1020: अणु /* Omicom S2 */
			स्थिर काष्ठा stv6110x_devctl *ctl;
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTLO);
			msleep(50);
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
			msleep(250);

			budget->dvb_frontend = dvb_attach(stv090x_attach,
							  &tt1600_stv090x_config,
							  &budget->i2c_adap,
							  STV090x_DEMODULATOR_0);

			अगर (budget->dvb_frontend) अणु
				prपूर्णांकk(KERN_INFO "budget: Omicom S2 detected\n");

				ctl = dvb_attach(stv6110x_attach,
						 budget->dvb_frontend,
						 &tt1600_stv6110x_config,
						 &budget->i2c_adap);

				अगर (ctl) अणु
					tt1600_stv090x_config.tuner_init	  = ctl->tuner_init;
					tt1600_stv090x_config.tuner_sleep	  = ctl->tuner_sleep;
					tt1600_stv090x_config.tuner_set_mode	  = ctl->tuner_set_mode;
					tt1600_stv090x_config.tuner_set_frequency = ctl->tuner_set_frequency;
					tt1600_stv090x_config.tuner_get_frequency = ctl->tuner_get_frequency;
					tt1600_stv090x_config.tuner_set_bandwidth = ctl->tuner_set_bandwidth;
					tt1600_stv090x_config.tuner_get_bandwidth = ctl->tuner_get_bandwidth;
					tt1600_stv090x_config.tuner_set_bbgain	  = ctl->tuner_set_bbgain;
					tt1600_stv090x_config.tuner_get_bbgain	  = ctl->tuner_get_bbgain;
					tt1600_stv090x_config.tuner_set_refclk	  = ctl->tuner_set_refclk;
					tt1600_stv090x_config.tuner_get_status	  = ctl->tuner_get_status;

					/* call the init function once to initialize
					   tuner's clock output divider and demod's
					   master घड़ी */
					अगर (budget->dvb_frontend->ops.init)
						budget->dvb_frontend->ops.init(budget->dvb_frontend);

					अगर (dvb_attach(lnbh24_attach,
							budget->dvb_frontend,
							&budget->i2c_adap,
							LNBH24_PCL | LNBH24_TTX,
							LNBH24_TEN, 0x14>>1) == शून्य) अणु
						prपूर्णांकk(KERN_ERR
						"No LNBH24 found!\n");
						जाओ error_out;
					पूर्ण
				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_ERR "%s: No STV6110(A) Silicon Tuner found!\n", __func__);
					जाओ error_out;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (budget->dvb_frontend == शून्य) अणु
		prपूर्णांकk("budget: A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget->dev->pci->venकरोr,
		       budget->dev->pci->device,
		       budget->dev->pci->subप्रणाली_venकरोr,
		       budget->dev->pci->subप्रणाली_device);
	पूर्ण अन्यथा अणु
		अगर (dvb_रेजिस्टर_frontend(&budget->dvb_adapter, budget->dvb_frontend))
			जाओ error_out;
	पूर्ण
	वापस;

error_out:
	prपूर्णांकk("budget: Frontend registration failed!\n");
	dvb_frontend_detach(budget->dvb_frontend);
	budget->dvb_frontend = शून्य;
	वापस;
पूर्ण

अटल पूर्णांक budget_attach (काष्ठा saa7146_dev* dev, काष्ठा saa7146_pci_extension_data *info)
अणु
	काष्ठा budget *budget = शून्य;
	पूर्णांक err;

	budget = kदो_स्मृति(माप(काष्ठा budget), GFP_KERNEL);
	अगर( शून्य == budget ) अणु
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(2, "dev:%p, info:%p, budget:%p\n", dev, info, budget);

	dev->ext_priv = budget;

	err = ttpci_budget_init(budget, dev, info, THIS_MODULE, adapter_nr);
	अगर (err) अणु
		prपूर्णांकk("==> failed\n");
		kमुक्त (budget);
		वापस err;
	पूर्ण

	budget->dvb_adapter.priv = budget;
	frontend_init(budget);

	ttpci_budget_init_hooks(budget);

	वापस 0;
पूर्ण

अटल पूर्णांक budget_detach (काष्ठा saa7146_dev* dev)
अणु
	काष्ठा budget *budget = (काष्ठा budget*) dev->ext_priv;
	पूर्णांक err;

	अगर (budget->dvb_frontend) अणु
		dvb_unरेजिस्टर_frontend(budget->dvb_frontend);
		dvb_frontend_detach(budget->dvb_frontend);
	पूर्ण

	err = ttpci_budget_deinit (budget);

	kमुक्त (budget);
	dev->ext_priv = शून्य;

	वापस err;
पूर्ण

अटल काष्ठा saa7146_extension budget_extension;

MAKE_BUDGET_INFO(ttbs,	"TT-Budget/WinTV-NOVA-S  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(ttbc,	"TT-Budget/WinTV-NOVA-C  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(ttbt,	"TT-Budget/WinTV-NOVA-T  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(satel,	"SATELCO Multimedia PCI",	BUDGET_TT_HW_DISEQC);
MAKE_BUDGET_INFO(ttbs1401, "TT-Budget-S-1401 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(tt1600, "TT-Budget S2-1600 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(fsacs0, "Fujitsu Siemens Activy Budget-S PCI (rev GR/grundig frontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsacs1, "Fujitsu Siemens Activy Budget-S PCI (rev AL/alps frontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsact,	 "Fujitsu Siemens Activy Budget-T PCI (rev GR/Grundig frontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsact1, "Fujitsu Siemens Activy Budget-T PCI (rev AL/ALPS TDHD1-204A)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(omicom, "Omicom S2 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(sylt,   "Philips Semi Sylt PCI", BUDGET_TT_HW_DISEQC);

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	MAKE_EXTENSION_PCI(ttbs,  0x13c2, 0x1003),
	MAKE_EXTENSION_PCI(ttbc,  0x13c2, 0x1004),
	MAKE_EXTENSION_PCI(ttbt,  0x13c2, 0x1005),
	MAKE_EXTENSION_PCI(satel, 0x13c2, 0x1013),
	MAKE_EXTENSION_PCI(ttbs,  0x13c2, 0x1016),
	MAKE_EXTENSION_PCI(ttbs1401, 0x13c2, 0x1018),
	MAKE_EXTENSION_PCI(tt1600, 0x13c2, 0x101c),
	MAKE_EXTENSION_PCI(fsacs1,0x1131, 0x4f60),
	MAKE_EXTENSION_PCI(fsacs0,0x1131, 0x4f61),
	MAKE_EXTENSION_PCI(fsact1, 0x1131, 0x5f60),
	MAKE_EXTENSION_PCI(fsact, 0x1131, 0x5f61),
	MAKE_EXTENSION_PCI(omicom, 0x14c4, 0x1020),
	MAKE_EXTENSION_PCI(sylt, 0x1131, 0x4f52),
	अणु
		.venकरोr    = 0,
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल काष्ठा saa7146_extension budget_extension = अणु
	.name		= "budget dvb",
	.flags		= SAA7146_USE_I2C_IRQ,

	.module		= THIS_MODULE,
	.pci_tbl	= pci_tbl,
	.attach		= budget_attach,
	.detach		= budget_detach,

	.irq_mask	= MASK_10,
	.irq_func	= ttpci_budget_irq10_handler,
पूर्ण;

अटल पूर्णांक __init budget_init(व्योम)
अणु
	वापस saa7146_रेजिस्टर_extension(&budget_extension);
पूर्ण

अटल व्योम __निकास budget_निकास(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&budget_extension);
पूर्ण

module_init(budget_init);
module_निकास(budget_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralph Metzler, Marcus Metzler, Michael Hunold, others");
MODULE_DESCRIPTION("driver for the SAA7146 based so-called budget PCI DVB cards by Siemens, Technotrend, Hauppauge");
