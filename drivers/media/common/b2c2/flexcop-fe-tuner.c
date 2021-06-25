<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-fe-tuner.c - methods क्रम frontend attachment and DiSEqC controlling
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश <media/tuner.h>
#समावेश "flexcop.h"
#समावेश "mt312.h"
#समावेश "stv0299.h"
#समावेश "s5h1420.h"
#समावेश "itd1000.h"
#समावेश "cx24113.h"
#समावेश "cx24123.h"
#समावेश "isl6421.h"
#समावेश "cx24120.h"
#समावेश "mt352.h"
#समावेश "bcm3510.h"
#समावेश "nxt200x.h"
#समावेश "dvb-pll.h"
#समावेश "lgdt330x.h"
#समावेश "tuner-simple.h"
#समावेश "stv0297.h"


/* Can we use the specअगरied front-end?  Remember that अगर we are compiled
 * पूर्णांकo the kernel we can't call code that's in modules.  */
#घोषणा FE_SUPPORTED(fe) IS_REACHABLE(CONFIG_DVB_ ## fe)

#अगर FE_SUPPORTED(BCM3510) || (FE_SUPPORTED(CX24120) && FE_SUPPORTED(ISL6421))
अटल पूर्णांक flexcop_fe_request_firmware(काष्ठा dvb_frontend *fe,
	स्थिर काष्ठा firmware **fw, अक्षर *name)
अणु
	काष्ठा flexcop_device *fc = fe->dvb->priv;

	वापस request_firmware(fw, name, fc->dev);
पूर्ण
#पूर्ण_अगर

/* lnb control */
#अगर (FE_SUPPORTED(MT312) || FE_SUPPORTED(STV0299)) && FE_SUPPORTED(PLL)
अटल पूर्णांक flexcop_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा flexcop_device *fc = fe->dvb->priv;
	flexcop_ibi_value v;
	deb_tuner("polarity/voltage = %u\n", voltage);

	v = fc->पढ़ो_ibi_reg(fc, misc_204);
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_OFF:
		v.misc_204.ACPI1_sig = 1;
		अवरोध;
	हाल SEC_VOLTAGE_13:
		v.misc_204.ACPI1_sig = 0;
		v.misc_204.LNB_L_H_sig = 0;
		अवरोध;
	हाल SEC_VOLTAGE_18:
		v.misc_204.ACPI1_sig = 0;
		v.misc_204.LNB_L_H_sig = 1;
		अवरोध;
	शेष:
		err("unknown SEC_VOLTAGE value");
		वापस -EINVAL;
	पूर्ण
	वापस fc->ग_लिखो_ibi_reg(fc, misc_204, v);
पूर्ण
#पूर्ण_अगर

#अगर FE_SUPPORTED(S5H1420) || FE_SUPPORTED(STV0299) || FE_SUPPORTED(MT312)
अटल पूर्णांक __maybe_unused flexcop_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा flexcop_device *fc = fe->dvb->priv;
	अगर (fc->fe_sleep)
		वापस fc->fe_sleep(fe);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* SkyStar2 DVB-S rev 2.3 */
#अगर FE_SUPPORTED(MT312) && FE_SUPPORTED(PLL)
अटल पूर्णांक flexcop_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
/* u16 wz_half_period_क्रम_45_mhz[] = अणु 0x01ff, 0x0154, 0x00ff, 0x00cc पूर्ण; */
	काष्ठा flexcop_device *fc = fe->dvb->priv;
	flexcop_ibi_value v;
	u16 ax;
	v.raw = 0;
	deb_tuner("tone = %u\n",tone);

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		ax = 0x01ff;
		अवरोध;
	हाल SEC_TONE_OFF:
		ax = 0;
		अवरोध;
	शेष:
		err("unknown SEC_TONE value");
		वापस -EINVAL;
	पूर्ण

	v.lnb_चयन_freq_200.LNB_CTLPrescaler_sig = 1; /* भागide by 2 */
	v.lnb_चयन_freq_200.LNB_CTLHighCount_sig = ax;
	v.lnb_चयन_freq_200.LNB_CTLLowCount_sig  = ax == 0 ? 0x1ff : ax;
	वापस fc->ग_लिखो_ibi_reg(fc,lnb_चयन_freq_200,v);
पूर्ण

अटल व्योम flexcop_diseqc_send_bit(काष्ठा dvb_frontend* fe, पूर्णांक data)
अणु
	flexcop_set_tone(fe, SEC_TONE_ON);
	udelay(data ? 500 : 1000);
	flexcop_set_tone(fe, SEC_TONE_OFF);
	udelay(data ? 1000 : 500);
पूर्ण

अटल व्योम flexcop_diseqc_send_byte(काष्ठा dvb_frontend* fe, पूर्णांक data)
अणु
	पूर्णांक i, par = 1, d;
	क्रम (i = 7; i >= 0; i--) अणु
		d = (data >> i) & 1;
		par ^= d;
		flexcop_diseqc_send_bit(fe, d);
	पूर्ण
	flexcop_diseqc_send_bit(fe, par);
पूर्ण

अटल पूर्णांक flexcop_send_diseqc_msg(काष्ठा dvb_frontend *fe,
	पूर्णांक len, u8 *msg, अचिन्हित दीर्घ burst)
अणु
	पूर्णांक i;

	flexcop_set_tone(fe, SEC_TONE_OFF);
	mdelay(16);

	क्रम (i = 0; i < len; i++)
		flexcop_diseqc_send_byte(fe,msg[i]);
	mdelay(16);

	अगर (burst != -1) अणु
		अगर (burst)
			flexcop_diseqc_send_byte(fe, 0xff);
		अन्यथा अणु
			flexcop_set_tone(fe, SEC_TONE_ON);
			mdelay(12);
			udelay(500);
			flexcop_set_tone(fe, SEC_TONE_OFF);
		पूर्ण
		msleep(20);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flexcop_diseqc_send_master_cmd(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	वापस flexcop_send_diseqc_msg(fe, cmd->msg_len, cmd->msg, 0);
पूर्ण

अटल पूर्णांक flexcop_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd minicmd)
अणु
	वापस flexcop_send_diseqc_msg(fe, 0, शून्य, minicmd);
पूर्ण

अटल काष्ठा mt312_config skystar23_samsung_tbdu18132_config = अणु
	.demod_address = 0x0e,
पूर्ण;

अटल पूर्णांक skystar2_rev23_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा dvb_frontend_ops *ops;

	fc->fe = dvb_attach(mt312_attach, &skystar23_samsung_tbdu18132_config, i2c);
	अगर (!fc->fe)
		वापस 0;

	अगर (!dvb_attach(dvb_pll_attach, fc->fe, 0x61, i2c,
			DVB_PLL_SAMSUNG_TBDU18132))
		वापस 0;

	ops = &fc->fe->ops;
	ops->diseqc_send_master_cmd = flexcop_diseqc_send_master_cmd;
	ops->diseqc_send_burst      = flexcop_diseqc_send_burst;
	ops->set_tone               = flexcop_set_tone;
	ops->set_voltage            = flexcop_set_voltage;
	fc->fe_sleep                = ops->sleep;
	ops->sleep                  = flexcop_sleep;
	वापस 1;
पूर्ण
#अन्यथा
#घोषणा skystar2_rev23_attach शून्य
#पूर्ण_अगर

/* SkyStar2 DVB-S rev 2.6 */
#अगर FE_SUPPORTED(STV0299) && FE_SUPPORTED(PLL)
अटल पूर्णांक samsung_tbmu24112_set_symbol_rate(काष्ठा dvb_frontend *fe,
	u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;

	अगर (srate < 1500000) अणु
		aclk = 0xb7; bclk = 0x47;
	पूर्ण अन्यथा अगर (srate < 3000000) अणु
		aclk = 0xb7; bclk = 0x4b;
	पूर्ण अन्यथा अगर (srate < 7000000) अणु
		aclk = 0xb7; bclk = 0x4f;
	पूर्ण अन्यथा अगर (srate < 14000000) अणु
		aclk = 0xb7; bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 30000000) अणु
		aclk = 0xb6; bclk = 0x53;
	पूर्ण अन्यथा अगर (srate < 45000000) अणु
		aclk = 0xb4; bclk = 0x51;
	पूर्ण

	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >>  8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21,  ratio        & 0xf0);
	वापस 0;
पूर्ण

अटल u8 samsung_tbmu24112_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7D,
	0x05, 0x35,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0xC3,
	0x0C, 0x00,
	0x0D, 0x81,
	0x0E, 0x23,
	0x0F, 0x12,
	0x10, 0x7E,
	0x11, 0x84,
	0x12, 0xB9,
	0x13, 0x88,
	0x14, 0x89,
	0x15, 0xC9,
	0x16, 0x00,
	0x17, 0x5C,
	0x18, 0x00,
	0x19, 0x00,
	0x1A, 0x00,
	0x1C, 0x00,
	0x1D, 0x00,
	0x1E, 0x00,
	0x1F, 0x3A,
	0x20, 0x2E,
	0x21, 0x80,
	0x22, 0xFF,
	0x23, 0xC1,
	0x28, 0x00,
	0x29, 0x1E,
	0x2A, 0x14,
	0x2B, 0x0F,
	0x2C, 0x09,
	0x2D, 0x05,
	0x31, 0x1F,
	0x32, 0x19,
	0x33, 0xFE,
	0x34, 0x93,
	0xff, 0xff,
पूर्ण;

अटल काष्ठा stv0299_config samsung_tbmu24112_config = अणु
	.demod_address = 0x68,
	.inittab = samsung_tbmu24112_inittab,
	.mclk = 88000000UL,
	.invert = 0,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_LK,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = samsung_tbmu24112_set_symbol_rate,
पूर्ण;

अटल पूर्णांक skystar2_rev26_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(stv0299_attach, &samsung_tbmu24112_config, i2c);
	अगर (!fc->fe)
		वापस 0;

	अगर (!dvb_attach(dvb_pll_attach, fc->fe, 0x61, i2c,
			DVB_PLL_SAMSUNG_TBMU24112))
		वापस 0;

	fc->fe->ops.set_voltage = flexcop_set_voltage;
	fc->fe_sleep = fc->fe->ops.sleep;
	fc->fe->ops.sleep = flexcop_sleep;
	वापस 1;

पूर्ण
#अन्यथा
#घोषणा skystar2_rev26_attach शून्य
#पूर्ण_अगर

/* SkyStar2 DVB-S rev 2.7 */
#अगर FE_SUPPORTED(S5H1420) && FE_SUPPORTED(ISL6421) && FE_SUPPORTED(TUNER_ITD1000)
अटल काष्ठा s5h1420_config skystar2_rev2_7_s5h1420_config = अणु
	.demod_address = 0x53,
	.invert = 1,
	.repeated_start_workaround = 1,
	.serial_mpeg = 1,
पूर्ण;

अटल काष्ठा itd1000_config skystar2_rev2_7_itd1000_config = अणु
	.i2c_address = 0x61,
पूर्ण;

अटल पूर्णांक skystar2_rev27_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	flexcop_ibi_value r108;
	काष्ठा i2c_adapter *i2c_tuner;

	/* enable no_base_addr - no repeated start when पढ़ोing */
	fc->fc_i2c_adap[0].no_base_addr = 1;
	fc->fe = dvb_attach(s5h1420_attach, &skystar2_rev2_7_s5h1420_config,
			    i2c);
	अगर (!fc->fe)
		जाओ fail;

	i2c_tuner = s5h1420_get_tuner_i2c_adapter(fc->fe);
	अगर (!i2c_tuner)
		जाओ fail;

	fc->fe_sleep = fc->fe->ops.sleep;
	fc->fe->ops.sleep = flexcop_sleep;

	/* enable no_base_addr - no repeated start when पढ़ोing */
	fc->fc_i2c_adap[2].no_base_addr = 1;
	अगर (!dvb_attach(isl6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 1, 1, false)) अणु
		err("ISL6421 could NOT be attached");
		जाओ fail_isl;
	पूर्ण
	info("ISL6421 successfully attached");

	/* the ITD1000 requires a lower i2c घड़ी - is it a problem ? */
	r108.raw = 0x00000506;
	fc->ग_लिखो_ibi_reg(fc, tw_sm_c_108, r108);
	अगर (!dvb_attach(itd1000_attach, fc->fe, i2c_tuner,
			&skystar2_rev2_7_itd1000_config)) अणु
		err("ITD1000 could NOT be attached");
		/* Should i2c घड़ी be restored? */
		जाओ fail_isl;
	पूर्ण
	info("ITD1000 successfully attached");

	वापस 1;

fail_isl:
	fc->fc_i2c_adap[2].no_base_addr = 0;
fail:
	/* क्रम the next devices we need it again */
	fc->fc_i2c_adap[0].no_base_addr = 0;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा skystar2_rev27_attach शून्य
#पूर्ण_अगर

/* SkyStar2 rev 2.8 */
#अगर FE_SUPPORTED(CX24123) && FE_SUPPORTED(ISL6421) && FE_SUPPORTED(TUNER_CX24113)
अटल काष्ठा cx24123_config skystar2_rev2_8_cx24123_config = अणु
	.demod_address = 0x55,
	.करोnt_use_pll = 1,
	.agc_callback = cx24113_agc_callback,
पूर्ण;

अटल स्थिर काष्ठा cx24113_config skystar2_rev2_8_cx24113_config = अणु
	.i2c_addr = 0x54,
	.xtal_khz = 10111,
पूर्ण;

अटल पूर्णांक skystar2_rev28_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा i2c_adapter *i2c_tuner;

	fc->fe = dvb_attach(cx24123_attach, &skystar2_rev2_8_cx24123_config,
			    i2c);
	अगर (!fc->fe)
		वापस 0;

	i2c_tuner = cx24123_get_tuner_i2c_adapter(fc->fe);
	अगर (!i2c_tuner)
		वापस 0;

	अगर (!dvb_attach(cx24113_attach, fc->fe, &skystar2_rev2_8_cx24113_config,
			i2c_tuner)) अणु
		err("CX24113 could NOT be attached");
		वापस 0;
	पूर्ण
	info("CX24113 successfully attached");

	fc->fc_i2c_adap[2].no_base_addr = 1;
	अगर (!dvb_attach(isl6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 0, 0, false)) अणु
		err("ISL6421 could NOT be attached");
		fc->fc_i2c_adap[2].no_base_addr = 0;
		वापस 0;
	पूर्ण
	info("ISL6421 successfully attached");
	/* TODO on i2c_adap[1] addr 0x11 (EEPROM) there seems to be an
	 * IR-receiver (PIC16F818) - but the card has no input क्रम that ??? */
	वापस 1;
पूर्ण
#अन्यथा
#घोषणा skystar2_rev28_attach शून्य
#पूर्ण_अगर

/* AirStar DVB-T */
#अगर FE_SUPPORTED(MT352) && FE_SUPPORTED(PLL)
अटल पूर्णांक samsung_tdtc9251dh0_demod_init(काष्ठा dvb_frontend *fe)
अणु
	अटल u8 mt352_घड़ी_config[] = अणु 0x89, 0x18, 0x2d पूर्ण;
	अटल u8 mt352_reset[] = अणु 0x50, 0x80 पूर्ण;
	अटल u8 mt352_adc_ctl_1_cfg[] = अणु 0x8E, 0x40 पूर्ण;
	अटल u8 mt352_agc_cfg[] = अणु 0x67, 0x28, 0xa1 पूर्ण;
	अटल u8 mt352_capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, mt352_घड़ी_config, माप(mt352_घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_reset, माप(mt352_reset));
	mt352_ग_लिखो(fe, mt352_adc_ctl_1_cfg, माप(mt352_adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, mt352_agc_cfg, माप(mt352_agc_cfg));
	mt352_ग_लिखो(fe, mt352_capt_range_cfg, माप(mt352_capt_range_cfg));
	वापस 0;
पूर्ण

अटल काष्ठा mt352_config samsung_tdtc9251dh0_config = अणु
	.demod_address = 0x0f,
	.demod_init    = samsung_tdtc9251dh0_demod_init,
पूर्ण;

अटल पूर्णांक airstar_dvbt_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(mt352_attach, &samsung_tdtc9251dh0_config, i2c);
	अगर (!fc->fe)
		वापस 0;

	वापस !!dvb_attach(dvb_pll_attach, fc->fe, 0x61, शून्य,
			    DVB_PLL_SAMSUNG_TDTC9251DH0);
पूर्ण
#अन्यथा
#घोषणा airstar_dvbt_attach शून्य
#पूर्ण_अगर

/* AirStar ATSC 1st generation */
#अगर FE_SUPPORTED(BCM3510)
अटल काष्ठा bcm3510_config air2pc_atsc_first_gen_config = अणु
	.demod_address    = 0x0f,
	.request_firmware = flexcop_fe_request_firmware,
पूर्ण;

अटल पूर्णांक airstar_atsc1_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(bcm3510_attach, &air2pc_atsc_first_gen_config, i2c);
	वापस fc->fe != शून्य;
पूर्ण
#अन्यथा
#घोषणा airstar_atsc1_attach शून्य
#पूर्ण_अगर

/* AirStar ATSC 2nd generation */
#अगर FE_SUPPORTED(NXT200X) && FE_SUPPORTED(PLL)
अटल स्थिर काष्ठा nxt200x_config samsung_tbmv_config = अणु
	.demod_address = 0x0a,
पूर्ण;

अटल पूर्णांक airstar_atsc2_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(nxt200x_attach, &samsung_tbmv_config, i2c);
	अगर (!fc->fe)
		वापस 0;

	वापस !!dvb_attach(dvb_pll_attach, fc->fe, 0x61, शून्य,
			    DVB_PLL_SAMSUNG_TBMV);
पूर्ण
#अन्यथा
#घोषणा airstar_atsc2_attach शून्य
#पूर्ण_अगर

/* AirStar ATSC 3rd generation */
#अगर FE_SUPPORTED(LGDT330X)
अटल काष्ठा lgdt330x_config air2pc_atsc_hd5000_config = अणु
	.demod_chip          = LGDT3303,
	.serial_mpeg         = 0x04,
	.घड़ी_polarity_flip = 1,
पूर्ण;

अटल पूर्णांक airstar_atsc3_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(lgdt330x_attach, &air2pc_atsc_hd5000_config,
			    0x59, i2c);
	अगर (!fc->fe)
		वापस 0;

	वापस !!dvb_attach(simple_tuner_attach, fc->fe, i2c, 0x61,
			    TUNER_LG_TDVS_H06XF);
पूर्ण
#अन्यथा
#घोषणा airstar_atsc3_attach शून्य
#पूर्ण_अगर

/* CableStar2 DVB-C */
#अगर FE_SUPPORTED(STV0297) && FE_SUPPORTED(PLL)
अटल u8 alps_tdee4_stv0297_inittab[] = अणु
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x48,
	0x01, 0x58,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x30, 0xff,
	0x31, 0x9d,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x29,
	0x35, 0x55,
	0x36, 0x80,
	0x37, 0x6e,
	0x38, 0x9c,
	0x40, 0x1a,
	0x41, 0xfe,
	0x42, 0x33,
	0x43, 0x00,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x51,
	0x4b, 0xf8,
	0x52, 0x30,
	0x53, 0x06,
	0x59, 0x06,
	0x5a, 0x5e,
	0x5b, 0x04,
	0x61, 0x49,
	0x62, 0x0a,
	0x70, 0xff,
	0x71, 0x04,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x20,
	0x81, 0x00,
	0x82, 0x30,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x22,
	0x86, 0x08,
	0x87, 0x1b,
	0x88, 0x00,
	0x89, 0x00,
	0x90, 0x00,
	0x91, 0x04,
	0xa0, 0x86,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x5b,
	0xc1, 0x10,
	0xc2, 0x12,
	0xd0, 0x02,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x02,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x01,
	0xff, 0xff,
पूर्ण;

अटल काष्ठा stv0297_config alps_tdee4_stv0297_config = अणु
	.demod_address = 0x1c,
	.inittab = alps_tdee4_stv0297_inittab,
पूर्ण;

अटल पूर्णांक cablestar2_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fc_i2c_adap[0].no_base_addr = 1;
	fc->fe = dvb_attach(stv0297_attach, &alps_tdee4_stv0297_config, i2c);
	अगर (!fc->fe)
		जाओ fail;

	/* This tuner करोesn't use the stv0297's I2C gate, but instead the
	 * tuner is connected to a dअगरferent flexcop I2C adapter.  */
	अगर (fc->fe->ops.i2c_gate_ctrl)
		fc->fe->ops.i2c_gate_ctrl(fc->fe, 0);
	fc->fe->ops.i2c_gate_ctrl = शून्य;

	अगर (!dvb_attach(dvb_pll_attach, fc->fe, 0x61,
			&fc->fc_i2c_adap[2].i2c_adap, DVB_PLL_TDEE4))
		जाओ fail;

	वापस 1;

fail:
	/* Reset क्रम next frontend to try */
	fc->fc_i2c_adap[0].no_base_addr = 0;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा cablestar2_attach शून्य
#पूर्ण_अगर

/* SkyStar S2 PCI DVB-S/S2 card based on Conexant cx24120/cx24118 */
#अगर FE_SUPPORTED(CX24120) && FE_SUPPORTED(ISL6421)
अटल स्थिर काष्ठा cx24120_config skystar2_rev3_3_cx24120_config = अणु
	.i2c_addr = 0x55,
	.xtal_khz = 10111,
	.initial_mpeg_config = अणु 0xa1, 0x76, 0x07 पूर्ण,
	.request_firmware = flexcop_fe_request_firmware,
	.i2c_wr_max = 4,
पूर्ण;

अटल पूर्णांक skystarS2_rev33_attach(काष्ठा flexcop_device *fc,
	काष्ठा i2c_adapter *i2c)
अणु
	fc->fe = dvb_attach(cx24120_attach,
			    &skystar2_rev3_3_cx24120_config, i2c);
	अगर (!fc->fe)
		वापस 0;

	fc->dev_type = FC_SKYS2_REV33;
	fc->fc_i2c_adap[2].no_base_addr = 1;
	अगर (!dvb_attach(isl6421_attach, fc->fe, &fc->fc_i2c_adap[2].i2c_adap,
			0x08, 0, 0, false)) अणु
		err("ISL6421 could NOT be attached!");
		fc->fc_i2c_adap[2].no_base_addr = 0;
		वापस 0;
	पूर्ण
	info("ISL6421 successfully attached.");

	अगर (fc->has_32_hw_pid_filter)
		fc->skip_6_hw_pid_filter = 1;

	वापस 1;
पूर्ण
#अन्यथा
#घोषणा skystarS2_rev33_attach शून्य
#पूर्ण_अगर

अटल काष्ठा अणु
	flexcop_device_type_t type;
	पूर्णांक (*attach)(काष्ठा flexcop_device *, काष्ठा i2c_adapter *);
पूर्ण flexcop_frontends[] = अणु
	अणु FC_SKY_REV27, skystar2_rev27_attach पूर्ण,
	अणु FC_SKY_REV28, skystar2_rev28_attach पूर्ण,
	अणु FC_SKY_REV26, skystar2_rev26_attach पूर्ण,
	अणु FC_AIR_DVBT, airstar_dvbt_attach पूर्ण,
	अणु FC_AIR_ATSC2, airstar_atsc2_attach पूर्ण,
	अणु FC_AIR_ATSC3, airstar_atsc3_attach पूर्ण,
	अणु FC_AIR_ATSC1, airstar_atsc1_attach पूर्ण,
	अणु FC_CABLE, cablestar2_attach पूर्ण,
	अणु FC_SKY_REV23, skystar2_rev23_attach पूर्ण,
	अणु FC_SKYS2_REV33, skystarS2_rev33_attach पूर्ण,
पूर्ण;

/* try to figure out the frontend */
पूर्णांक flexcop_frontend_init(काष्ठा flexcop_device *fc)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(flexcop_frontends); i++) अणु
		अगर (!flexcop_frontends[i].attach)
			जारी;
		/* type needs to be set beक्रमe, because of some workarounds
		 * करोne based on the probed card type */
		fc->dev_type = flexcop_frontends[i].type;
		अगर (flexcop_frontends[i].attach(fc, &fc->fc_i2c_adap[0].i2c_adap))
			जाओ fe_found;
		/* Clean up partially attached frontend */
		अगर (fc->fe) अणु
			dvb_frontend_detach(fc->fe);
			fc->fe = शून्य;
		पूर्ण
	पूर्ण
	fc->dev_type = FC_UNK;
	err("no frontend driver found for this B2C2/FlexCop adapter");
	वापस -ENODEV;

fe_found:
	info("found '%s' .", fc->fe->ops.info.name);
	अगर (dvb_रेजिस्टर_frontend(&fc->dvb_adapter, fc->fe)) अणु
		err("frontend registration failed!");
		dvb_frontend_detach(fc->fe);
		fc->fe = शून्य;
		वापस -EINVAL;
	पूर्ण
	fc->init_state |= FC_STATE_FE_INIT;
	वापस 0;
पूर्ण

व्योम flexcop_frontend_निकास(काष्ठा flexcop_device *fc)
अणु
	अगर (fc->init_state & FC_STATE_FE_INIT) अणु
		dvb_unरेजिस्टर_frontend(fc->fe);
		dvb_frontend_detach(fc->fe);
	पूर्ण
	fc->init_state &= ~FC_STATE_FE_INIT;
पूर्ण
