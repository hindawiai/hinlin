<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frontend driver क्रम mobile DVB-T demodulator DiBcom 3000M-B
 * DiBcom (http://www.dibcom.fr/)
 *
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * based on GPL code from DibCom, which has
 *
 * Copyright (C) 2004 Amaury Demol क्रम DiBcom
 *
 * Acknowledgements
 *
 *  Amaury Demol from DiBcom क्रम providing specs and driver
 *  sources, on which this driver (and the dvb-dibusb) are based.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "dib3000.h"
#समावेश "dib3000mb_priv.h"

/* Version inक्रमmation */
#घोषणा DRIVER_VERSION "0.1"
#घोषणा DRIVER_DESC "DiBcom 3000M-B DVB-T demodulator"
#घोषणा DRIVER_AUTHOR "Patrick Boettcher, patrick.boettcher@posteo.de"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,2=xfer,4=setfe,8=getfe (|-able)).");

#घोषणा deb_info(args...) dprपूर्णांकk(0x01, args)
#घोषणा deb_i2c(args...)  dprपूर्णांकk(0x02, args)
#घोषणा deb_srch(args...) dprपूर्णांकk(0x04, args)
#घोषणा deb_info(args...) dprपूर्णांकk(0x01, args)
#घोषणा deb_xfer(args...) dprपूर्णांकk(0x02, args)
#घोषणा deb_setf(args...) dprपूर्णांकk(0x04, args)
#घोषणा deb_getf(args...) dprपूर्णांकk(0x08, args)

अटल पूर्णांक dib3000_पढ़ो_reg(काष्ठा dib3000_state *state, u16 reg)
अणु
	u8 wb[] = अणु ((reg >> 8) | 0x80) & 0xff, reg & 0xff पूर्ण;
	u8 rb[2];
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config.demod_address, .flags = 0,        .buf = wb, .len = 2 पूर्ण,
		अणु .addr = state->config.demod_address, .flags = I2C_M_RD, .buf = rb, .len = 2 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(state->i2c, msg, 2) != 2)
		deb_i2c("i2c read error\n");

	deb_i2c("reading i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)\n",reg,reg,
			(rb[0] << 8) | rb[1],(rb[0] << 8) | rb[1]);

	वापस (rb[0] << 8) | rb[1];
पूर्ण

अटल पूर्णांक dib3000_ग_लिखो_reg(काष्ठा dib3000_state *state, u16 reg, u16 val)
अणु
	u8 b[] = अणु
		(reg >> 8) & 0xff, reg & 0xff,
		(val >> 8) & 0xff, val & 0xff,
	पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config.demod_address, .flags = 0, .buf = b, .len = 4 पूर्ण
	पूर्ण;
	deb_i2c("writing i2c bus (reg: %5d 0x%04x, val: %5d 0x%04x)\n",reg,reg,val,val);

	वापस i2c_transfer(state->i2c,msg, 1) != 1 ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक dib3000_search_status(u16 irq,u16 lock)
अणु
	अगर (irq & 0x02) अणु
		अगर (lock & 0x01) अणु
			deb_srch("auto search succeeded\n");
			वापस 1; // स्वतः search succeeded
		पूर्ण अन्यथा अणु
			deb_srch("auto search not successful\n");
			वापस 0; // स्वतः search failed
		पूर्ण
	पूर्ण अन्यथा अगर (irq & 0x01)  अणु
		deb_srch("auto search failed\n");
		वापस 0; // स्वतः search failed
	पूर्ण
	वापस -1; // try again
पूर्ण

/* क्रम स्वतः search */
अटल u16 dib3000_seq[2][2][2] =     /* fft,gua,   inv   */
	अणु /* fft */
		अणु /* gua */
			अणु 0, 1 पूर्ण,                   /*  0   0   अणु 0,1 पूर्ण */
			अणु 3, 9 पूर्ण,                   /*  0   1   अणु 0,1 पूर्ण */
		पूर्ण,
		अणु
			अणु 2, 5 पूर्ण,                   /*  1   0   अणु 0,1 पूर्ण */
			अणु 6, 11 पूर्ण,                  /*  1   1   अणु 0,1 पूर्ण */
		पूर्ण
	पूर्ण;

अटल पूर्णांक dib3000mb_get_frontend(काष्ठा dvb_frontend* fe,
				  काष्ठा dtv_frontend_properties *c);

अटल पूर्णांक dib3000mb_set_frontend(काष्ठा dvb_frontend *fe, पूर्णांक tuner)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	क्रमागत fe_code_rate fe_cr = FEC_NONE;
	पूर्णांक search_state, seq;

	अगर (tuner && fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);

		चयन (c->bandwidth_hz) अणु
			हाल 8000000:
				wr_क्रमeach(dib3000mb_reg_timing_freq, dib3000mb_timing_freq[2]);
				wr_क्रमeach(dib3000mb_reg_bandwidth, dib3000mb_bandwidth_8mhz);
				अवरोध;
			हाल 7000000:
				wr_क्रमeach(dib3000mb_reg_timing_freq, dib3000mb_timing_freq[1]);
				wr_क्रमeach(dib3000mb_reg_bandwidth, dib3000mb_bandwidth_7mhz);
				अवरोध;
			हाल 6000000:
				wr_क्रमeach(dib3000mb_reg_timing_freq, dib3000mb_timing_freq[0]);
				wr_क्रमeach(dib3000mb_reg_bandwidth, dib3000mb_bandwidth_6mhz);
				अवरोध;
			हाल 0:
				वापस -EOPNOTSUPP;
			शेष:
				pr_err("unknown bandwidth value.\n");
				वापस -EINVAL;
		पूर्ण
		deb_setf("bandwidth: %d MHZ\n", c->bandwidth_hz / 1000000);
	पूर्ण
	wr(DIB3000MB_REG_LOCK1_MASK, DIB3000MB_LOCK1_SEARCH_4);

	चयन (c->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K:
			deb_setf("transmission mode: 2k\n");
			wr(DIB3000MB_REG_FFT, DIB3000_TRANSMISSION_MODE_2K);
			अवरोध;
		हाल TRANSMISSION_MODE_8K:
			deb_setf("transmission mode: 8k\n");
			wr(DIB3000MB_REG_FFT, DIB3000_TRANSMISSION_MODE_8K);
			अवरोध;
		हाल TRANSMISSION_MODE_AUTO:
			deb_setf("transmission mode: auto\n");
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_32:
			deb_setf("guard 1_32\n");
			wr(DIB3000MB_REG_GUARD_TIME, DIB3000_GUARD_TIME_1_32);
			अवरोध;
		हाल GUARD_INTERVAL_1_16:
			deb_setf("guard 1_16\n");
			wr(DIB3000MB_REG_GUARD_TIME, DIB3000_GUARD_TIME_1_16);
			अवरोध;
		हाल GUARD_INTERVAL_1_8:
			deb_setf("guard 1_8\n");
			wr(DIB3000MB_REG_GUARD_TIME, DIB3000_GUARD_TIME_1_8);
			अवरोध;
		हाल GUARD_INTERVAL_1_4:
			deb_setf("guard 1_4\n");
			wr(DIB3000MB_REG_GUARD_TIME, DIB3000_GUARD_TIME_1_4);
			अवरोध;
		हाल GUARD_INTERVAL_AUTO:
			deb_setf("guard auto\n");
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (c->inversion) अणु
		हाल INVERSION_OFF:
			deb_setf("inversion off\n");
			wr(DIB3000MB_REG_DDS_INV, DIB3000_DDS_INVERSION_OFF);
			अवरोध;
		हाल INVERSION_AUTO:
			deb_setf("inversion auto\n");
			अवरोध;
		हाल INVERSION_ON:
			deb_setf("inversion on\n");
			wr(DIB3000MB_REG_DDS_INV, DIB3000_DDS_INVERSION_ON);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	चयन (c->modulation) अणु
		हाल QPSK:
			deb_setf("modulation: qpsk\n");
			wr(DIB3000MB_REG_QAM, DIB3000_CONSTELLATION_QPSK);
			अवरोध;
		हाल QAM_16:
			deb_setf("modulation: qam16\n");
			wr(DIB3000MB_REG_QAM, DIB3000_CONSTELLATION_16QAM);
			अवरोध;
		हाल QAM_64:
			deb_setf("modulation: qam64\n");
			wr(DIB3000MB_REG_QAM, DIB3000_CONSTELLATION_64QAM);
			अवरोध;
		हाल QAM_AUTO:
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	चयन (c->hierarchy) अणु
		हाल HIERARCHY_NONE:
			deb_setf("hierarchy: none\n");
			fallthrough;
		हाल HIERARCHY_1:
			deb_setf("hierarchy: alpha=1\n");
			wr(DIB3000MB_REG_VIT_ALPHA, DIB3000_ALPHA_1);
			अवरोध;
		हाल HIERARCHY_2:
			deb_setf("hierarchy: alpha=2\n");
			wr(DIB3000MB_REG_VIT_ALPHA, DIB3000_ALPHA_2);
			अवरोध;
		हाल HIERARCHY_4:
			deb_setf("hierarchy: alpha=4\n");
			wr(DIB3000MB_REG_VIT_ALPHA, DIB3000_ALPHA_4);
			अवरोध;
		हाल HIERARCHY_AUTO:
			deb_setf("hierarchy: alpha=auto\n");
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	अगर (c->hierarchy == HIERARCHY_NONE) अणु
		wr(DIB3000MB_REG_VIT_HRCH, DIB3000_HRCH_OFF);
		wr(DIB3000MB_REG_VIT_HP, DIB3000_SELECT_HP);
		fe_cr = c->code_rate_HP;
	पूर्ण अन्यथा अगर (c->hierarchy != HIERARCHY_AUTO) अणु
		wr(DIB3000MB_REG_VIT_HRCH, DIB3000_HRCH_ON);
		wr(DIB3000MB_REG_VIT_HP, DIB3000_SELECT_LP);
		fe_cr = c->code_rate_LP;
	पूर्ण
	चयन (fe_cr) अणु
		हाल FEC_1_2:
			deb_setf("fec: 1_2\n");
			wr(DIB3000MB_REG_VIT_CODE_RATE, DIB3000_FEC_1_2);
			अवरोध;
		हाल FEC_2_3:
			deb_setf("fec: 2_3\n");
			wr(DIB3000MB_REG_VIT_CODE_RATE, DIB3000_FEC_2_3);
			अवरोध;
		हाल FEC_3_4:
			deb_setf("fec: 3_4\n");
			wr(DIB3000MB_REG_VIT_CODE_RATE, DIB3000_FEC_3_4);
			अवरोध;
		हाल FEC_5_6:
			deb_setf("fec: 5_6\n");
			wr(DIB3000MB_REG_VIT_CODE_RATE, DIB3000_FEC_5_6);
			अवरोध;
		हाल FEC_7_8:
			deb_setf("fec: 7_8\n");
			wr(DIB3000MB_REG_VIT_CODE_RATE, DIB3000_FEC_7_8);
			अवरोध;
		हाल FEC_NONE:
			deb_setf("fec: none\n");
			अवरोध;
		हाल FEC_AUTO:
			deb_setf("fec: auto\n");
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	seq = dib3000_seq
		[c->transmission_mode == TRANSMISSION_MODE_AUTO]
		[c->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO]
		[c->inversion == INVERSION_AUTO];

	deb_setf("seq? %d\n", seq);

	wr(DIB3000MB_REG_SEQ, seq);

	wr(DIB3000MB_REG_ISI, seq ? DIB3000MB_ISI_INHIBIT : DIB3000MB_ISI_ACTIVATE);

	अगर (c->transmission_mode == TRANSMISSION_MODE_2K) अणु
		अगर (c->guard_पूर्णांकerval == GUARD_INTERVAL_1_8) अणु
			wr(DIB3000MB_REG_SYNC_IMPROVEMENT, DIB3000MB_SYNC_IMPROVE_2K_1_8);
		पूर्ण अन्यथा अणु
			wr(DIB3000MB_REG_SYNC_IMPROVEMENT, DIB3000MB_SYNC_IMPROVE_DEFAULT);
		पूर्ण

		wr(DIB3000MB_REG_UNK_121, DIB3000MB_UNK_121_2K);
	पूर्ण अन्यथा अणु
		wr(DIB3000MB_REG_UNK_121, DIB3000MB_UNK_121_DEFAULT);
	पूर्ण

	wr(DIB3000MB_REG_MOBILE_ALGO, DIB3000MB_MOBILE_ALGO_OFF);
	wr(DIB3000MB_REG_MOBILE_MODE_QAM, DIB3000MB_MOBILE_MODE_QAM_OFF);
	wr(DIB3000MB_REG_MOBILE_MODE, DIB3000MB_MOBILE_MODE_OFF);

	wr_क्रमeach(dib3000mb_reg_agc_bandwidth, dib3000mb_agc_bandwidth_high);

	wr(DIB3000MB_REG_ISI, DIB3000MB_ISI_ACTIVATE);

	wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_AGC + DIB3000MB_RESTART_CTRL);
	wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_OFF);

	/* रुको क्रम AGC lock */
	msleep(70);

	wr_क्रमeach(dib3000mb_reg_agc_bandwidth, dib3000mb_agc_bandwidth_low);

	/* something has to be स्वतः searched */
	अगर (c->modulation == QAM_AUTO ||
		c->hierarchy == HIERARCHY_AUTO ||
		fe_cr == FEC_AUTO ||
		c->inversion == INVERSION_AUTO) अणु
		पूर्णांक as_count=0;

		deb_setf("autosearch enabled.\n");

		wr(DIB3000MB_REG_ISI, DIB3000MB_ISI_INHIBIT);

		wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_AUTO_SEARCH);
		wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_OFF);

		जबतक ((search_state =
				dib3000_search_status(
					rd(DIB3000MB_REG_AS_IRQ_PENDING),
					rd(DIB3000MB_REG_LOCK2_VALUE))) < 0 && as_count++ < 100)
			msleep(1);

		deb_setf("search_state after autosearch %d after %d checks\n",
			 search_state, as_count);

		अगर (search_state == 1) अणु
			अगर (dib3000mb_get_frontend(fe, c) == 0) अणु
				deb_setf("reading tuning data from frontend succeeded.\n");
				वापस dib3000mb_set_frontend(fe, 0);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_CTRL);
		wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_OFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_fe_init(काष्ठा dvb_frontend* fe, पूर्णांक mobile_mode)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;

	deb_info("dib3000mb is getting up.\n");
	wr(DIB3000MB_REG_POWER_CONTROL, DIB3000MB_POWER_UP);

	wr(DIB3000MB_REG_RESTART, DIB3000MB_RESTART_AGC);

	wr(DIB3000MB_REG_RESET_DEVICE, DIB3000MB_RESET_DEVICE);
	wr(DIB3000MB_REG_RESET_DEVICE, DIB3000MB_RESET_DEVICE_RST);

	wr(DIB3000MB_REG_CLOCK, DIB3000MB_CLOCK_DEFAULT);

	wr(DIB3000MB_REG_ELECT_OUT_MODE, DIB3000MB_ELECT_OUT_MODE_ON);

	wr(DIB3000MB_REG_DDS_FREQ_MSB, DIB3000MB_DDS_FREQ_MSB);
	wr(DIB3000MB_REG_DDS_FREQ_LSB, DIB3000MB_DDS_FREQ_LSB);

	wr_क्रमeach(dib3000mb_reg_timing_freq, dib3000mb_timing_freq[2]);

	wr_क्रमeach(dib3000mb_reg_impulse_noise,
			dib3000mb_impulse_noise_values[DIB3000MB_IMPNOISE_OFF]);

	wr_क्रमeach(dib3000mb_reg_agc_gain, dib3000mb_शेष_agc_gain);

	wr(DIB3000MB_REG_PHASE_NOISE, DIB3000MB_PHASE_NOISE_DEFAULT);

	wr_क्रमeach(dib3000mb_reg_phase_noise, dib3000mb_शेष_noise_phase);

	wr_क्रमeach(dib3000mb_reg_lock_duration, dib3000mb_शेष_lock_duration);

	wr_क्रमeach(dib3000mb_reg_agc_bandwidth, dib3000mb_agc_bandwidth_low);

	wr(DIB3000MB_REG_LOCK0_MASK, DIB3000MB_LOCK0_DEFAULT);
	wr(DIB3000MB_REG_LOCK1_MASK, DIB3000MB_LOCK1_SEARCH_4);
	wr(DIB3000MB_REG_LOCK2_MASK, DIB3000MB_LOCK2_DEFAULT);
	wr(DIB3000MB_REG_SEQ, dib3000_seq[1][1][1]);

	wr_क्रमeach(dib3000mb_reg_bandwidth, dib3000mb_bandwidth_8mhz);

	wr(DIB3000MB_REG_UNK_68, DIB3000MB_UNK_68);
	wr(DIB3000MB_REG_UNK_69, DIB3000MB_UNK_69);
	wr(DIB3000MB_REG_UNK_71, DIB3000MB_UNK_71);
	wr(DIB3000MB_REG_UNK_77, DIB3000MB_UNK_77);
	wr(DIB3000MB_REG_UNK_78, DIB3000MB_UNK_78);
	wr(DIB3000MB_REG_ISI, DIB3000MB_ISI_INHIBIT);
	wr(DIB3000MB_REG_UNK_92, DIB3000MB_UNK_92);
	wr(DIB3000MB_REG_UNK_96, DIB3000MB_UNK_96);
	wr(DIB3000MB_REG_UNK_97, DIB3000MB_UNK_97);
	wr(DIB3000MB_REG_UNK_106, DIB3000MB_UNK_106);
	wr(DIB3000MB_REG_UNK_107, DIB3000MB_UNK_107);
	wr(DIB3000MB_REG_UNK_108, DIB3000MB_UNK_108);
	wr(DIB3000MB_REG_UNK_122, DIB3000MB_UNK_122);
	wr(DIB3000MB_REG_MOBILE_MODE_QAM, DIB3000MB_MOBILE_MODE_QAM_OFF);
	wr(DIB3000MB_REG_BERLEN, DIB3000MB_BERLEN_DEFAULT);

	wr_क्रमeach(dib3000mb_reg_filter_coeffs, dib3000mb_filter_coeffs);

	wr(DIB3000MB_REG_MOBILE_ALGO, DIB3000MB_MOBILE_ALGO_ON);
	wr(DIB3000MB_REG_MULTI_DEMOD_MSB, DIB3000MB_MULTI_DEMOD_MSB);
	wr(DIB3000MB_REG_MULTI_DEMOD_LSB, DIB3000MB_MULTI_DEMOD_LSB);

	wr(DIB3000MB_REG_OUTPUT_MODE, DIB3000MB_OUTPUT_MODE_SLAVE);

	wr(DIB3000MB_REG_FIFO_142, DIB3000MB_FIFO_142);
	wr(DIB3000MB_REG_MPEG2_OUT_MODE, DIB3000MB_MPEG2_OUT_MODE_188);
	wr(DIB3000MB_REG_PID_PARSE, DIB3000MB_PID_PARSE_ACTIVATE);
	wr(DIB3000MB_REG_FIFO, DIB3000MB_FIFO_INHIBIT);
	wr(DIB3000MB_REG_FIFO_146, DIB3000MB_FIFO_146);
	wr(DIB3000MB_REG_FIFO_147, DIB3000MB_FIFO_147);

	wr(DIB3000MB_REG_DATA_IN_DIVERSITY, DIB3000MB_DATA_DIVERSITY_IN_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_get_frontend(काष्ठा dvb_frontend* fe,
				  काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;
	क्रमागत fe_code_rate *cr;
	u16 tps_val;
	पूर्णांक inv_test1,inv_test2;
	u32 dds_val, threshold = 0x800000;

	अगर (!rd(DIB3000MB_REG_TPS_LOCK))
		वापस 0;

	dds_val = ((rd(DIB3000MB_REG_DDS_VALUE_MSB) & 0xff) << 16) + rd(DIB3000MB_REG_DDS_VALUE_LSB);
	deb_getf("DDS_VAL: %x %x %x\n", dds_val, rd(DIB3000MB_REG_DDS_VALUE_MSB), rd(DIB3000MB_REG_DDS_VALUE_LSB));
	अगर (dds_val < threshold)
		inv_test1 = 0;
	अन्यथा अगर (dds_val == threshold)
		inv_test1 = 1;
	अन्यथा
		inv_test1 = 2;

	dds_val = ((rd(DIB3000MB_REG_DDS_FREQ_MSB) & 0xff) << 16) + rd(DIB3000MB_REG_DDS_FREQ_LSB);
	deb_getf("DDS_FREQ: %x %x %x\n", dds_val, rd(DIB3000MB_REG_DDS_FREQ_MSB), rd(DIB3000MB_REG_DDS_FREQ_LSB));
	अगर (dds_val < threshold)
		inv_test2 = 0;
	अन्यथा अगर (dds_val == threshold)
		inv_test2 = 1;
	अन्यथा
		inv_test2 = 2;

	c->inversion =
		((inv_test2 == 2) && (inv_test1==1 || inv_test1==0)) ||
		((inv_test2 == 0) && (inv_test1==1 || inv_test1==2)) ?
		INVERSION_ON : INVERSION_OFF;

	deb_getf("inversion %d %d, %d\n", inv_test2, inv_test1, c->inversion);

	चयन ((tps_val = rd(DIB3000MB_REG_TPS_QAM))) अणु
		हाल DIB3000_CONSTELLATION_QPSK:
			deb_getf("QPSK\n");
			c->modulation = QPSK;
			अवरोध;
		हाल DIB3000_CONSTELLATION_16QAM:
			deb_getf("QAM16\n");
			c->modulation = QAM_16;
			अवरोध;
		हाल DIB3000_CONSTELLATION_64QAM:
			deb_getf("QAM64\n");
			c->modulation = QAM_64;
			अवरोध;
		शेष:
			pr_err("Unexpected constellation returned by TPS (%d)\n", tps_val);
			अवरोध;
	पूर्ण
	deb_getf("TPS: %d\n", tps_val);

	अगर (rd(DIB3000MB_REG_TPS_HRCH)) अणु
		deb_getf("HRCH ON\n");
		cr = &c->code_rate_LP;
		c->code_rate_HP = FEC_NONE;
		चयन ((tps_val = rd(DIB3000MB_REG_TPS_VIT_ALPHA))) अणु
			हाल DIB3000_ALPHA_0:
				deb_getf("HIERARCHY_NONE\n");
				c->hierarchy = HIERARCHY_NONE;
				अवरोध;
			हाल DIB3000_ALPHA_1:
				deb_getf("HIERARCHY_1\n");
				c->hierarchy = HIERARCHY_1;
				अवरोध;
			हाल DIB3000_ALPHA_2:
				deb_getf("HIERARCHY_2\n");
				c->hierarchy = HIERARCHY_2;
				अवरोध;
			हाल DIB3000_ALPHA_4:
				deb_getf("HIERARCHY_4\n");
				c->hierarchy = HIERARCHY_4;
				अवरोध;
			शेष:
				pr_err("Unexpected ALPHA value returned by TPS (%d)\n", tps_val);
				अवरोध;
		पूर्ण
		deb_getf("TPS: %d\n", tps_val);

		tps_val = rd(DIB3000MB_REG_TPS_CODE_RATE_LP);
	पूर्ण अन्यथा अणु
		deb_getf("HRCH OFF\n");
		cr = &c->code_rate_HP;
		c->code_rate_LP = FEC_NONE;
		c->hierarchy = HIERARCHY_NONE;

		tps_val = rd(DIB3000MB_REG_TPS_CODE_RATE_HP);
	पूर्ण

	चयन (tps_val) अणु
		हाल DIB3000_FEC_1_2:
			deb_getf("FEC_1_2\n");
			*cr = FEC_1_2;
			अवरोध;
		हाल DIB3000_FEC_2_3:
			deb_getf("FEC_2_3\n");
			*cr = FEC_2_3;
			अवरोध;
		हाल DIB3000_FEC_3_4:
			deb_getf("FEC_3_4\n");
			*cr = FEC_3_4;
			अवरोध;
		हाल DIB3000_FEC_5_6:
			deb_getf("FEC_5_6\n");
			*cr = FEC_4_5;
			अवरोध;
		हाल DIB3000_FEC_7_8:
			deb_getf("FEC_7_8\n");
			*cr = FEC_7_8;
			अवरोध;
		शेष:
			pr_err("Unexpected FEC returned by TPS (%d)\n", tps_val);
			अवरोध;
	पूर्ण
	deb_getf("TPS: %d\n",tps_val);

	चयन ((tps_val = rd(DIB3000MB_REG_TPS_GUARD_TIME))) अणु
		हाल DIB3000_GUARD_TIME_1_32:
			deb_getf("GUARD_INTERVAL_1_32\n");
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
			अवरोध;
		हाल DIB3000_GUARD_TIME_1_16:
			deb_getf("GUARD_INTERVAL_1_16\n");
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
			अवरोध;
		हाल DIB3000_GUARD_TIME_1_8:
			deb_getf("GUARD_INTERVAL_1_8\n");
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
			अवरोध;
		हाल DIB3000_GUARD_TIME_1_4:
			deb_getf("GUARD_INTERVAL_1_4\n");
			c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
			अवरोध;
		शेष:
			pr_err("Unexpected Guard Time returned by TPS (%d)\n", tps_val);
			अवरोध;
	पूर्ण
	deb_getf("TPS: %d\n", tps_val);

	चयन ((tps_val = rd(DIB3000MB_REG_TPS_FFT))) अणु
		हाल DIB3000_TRANSMISSION_MODE_2K:
			deb_getf("TRANSMISSION_MODE_2K\n");
			c->transmission_mode = TRANSMISSION_MODE_2K;
			अवरोध;
		हाल DIB3000_TRANSMISSION_MODE_8K:
			deb_getf("TRANSMISSION_MODE_8K\n");
			c->transmission_mode = TRANSMISSION_MODE_8K;
			अवरोध;
		शेष:
			pr_err("unexpected transmission mode return by TPS (%d)\n", tps_val);
			अवरोध;
	पूर्ण
	deb_getf("TPS: %d\n", tps_val);

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *stat)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;

	*stat = 0;

	अगर (rd(DIB3000MB_REG_AGC_LOCK))
		*stat |= FE_HAS_SIGNAL;
	अगर (rd(DIB3000MB_REG_CARRIER_LOCK))
		*stat |= FE_HAS_CARRIER;
	अगर (rd(DIB3000MB_REG_VIT_LCK))
		*stat |= FE_HAS_VITERBI;
	अगर (rd(DIB3000MB_REG_TS_SYNC_LOCK))
		*stat |= (FE_HAS_SYNC | FE_HAS_LOCK);

	deb_getf("actual status is %2x\n",*stat);

	deb_getf("autoval: tps: %d, qam: %d, hrch: %d, alpha: %d, hp: %d, lp: %d, guard: %d, fft: %d cell: %d\n",
			rd(DIB3000MB_REG_TPS_LOCK),
			rd(DIB3000MB_REG_TPS_QAM),
			rd(DIB3000MB_REG_TPS_HRCH),
			rd(DIB3000MB_REG_TPS_VIT_ALPHA),
			rd(DIB3000MB_REG_TPS_CODE_RATE_HP),
			rd(DIB3000MB_REG_TPS_CODE_RATE_LP),
			rd(DIB3000MB_REG_TPS_GUARD_TIME),
			rd(DIB3000MB_REG_TPS_FFT),
			rd(DIB3000MB_REG_TPS_CELL_ID));

	//*stat = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32 *ber)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;

	*ber = ((rd(DIB3000MB_REG_BER_MSB) << 16) | rd(DIB3000MB_REG_BER_LSB));
	वापस 0;
पूर्ण

/* see dib3000-watch dvb-apps क्रम exact calcuations of संकेत_strength and snr */
अटल पूर्णांक dib3000mb_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 *strength)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;

	*strength = rd(DIB3000MB_REG_SIGNAL_POWER) * 0xffff / 0x170;
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;
	लघु sigघात = rd(DIB3000MB_REG_SIGNAL_POWER);
	पूर्णांक iciघात = ((rd(DIB3000MB_REG_NOISE_POWER_MSB) & 0xff) << 16) |
		rd(DIB3000MB_REG_NOISE_POWER_LSB);
	*snr = (sigघात << 8) / ((iciघात > 0) ? iciघात : 1);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_पढ़ो_unc_blocks(काष्ठा dvb_frontend* fe, u32 *unc)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;

	*unc = rd(DIB3000MB_REG_PACKET_ERROR_RATE);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dib3000_state* state = fe->demodulator_priv;
	deb_info("dib3000mb is going to bed.\n");
	wr(DIB3000MB_REG_POWER_CONTROL, DIB3000MB_POWER_DOWN);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 800;
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_fe_init_nonmobile(काष्ठा dvb_frontend* fe)
अणु
	वापस dib3000mb_fe_init(fe, 0);
पूर्ण

अटल पूर्णांक dib3000mb_set_frontend_and_tuner(काष्ठा dvb_frontend *fe)
अणु
	वापस dib3000mb_set_frontend(fe, 1);
पूर्ण

अटल व्योम dib3000mb_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dib3000_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

/* pid filter and transfer stuff */
अटल पूर्णांक dib3000mb_pid_control(काष्ठा dvb_frontend *fe,पूर्णांक index, पूर्णांक pid,पूर्णांक onoff)
अणु
	काष्ठा dib3000_state *state = fe->demodulator_priv;
	pid = (onoff ? pid | DIB3000_ACTIVATE_PID_FILTERING : 0);
	wr(index+DIB3000MB_REG_FIRST_PID,pid);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_fअगरo_control(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib3000_state *state = fe->demodulator_priv;

	deb_xfer("%s fifo\n",onoff ? "enabling" : "disabling");
	अगर (onoff) अणु
		wr(DIB3000MB_REG_FIFO, DIB3000MB_FIFO_ACTIVATE);
	पूर्ण अन्यथा अणु
		wr(DIB3000MB_REG_FIFO, DIB3000MB_FIFO_INHIBIT);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_pid_parse(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib3000_state *state = fe->demodulator_priv;
	deb_xfer("%s pid parsing\n",onoff ? "enabling" : "disabling");
	wr(DIB3000MB_REG_PID_PARSE,onoff);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mb_tuner_pass_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff, u8 pll_addr)
अणु
	काष्ठा dib3000_state *state = fe->demodulator_priv;
	अगर (onoff) अणु
		wr(DIB3000MB_REG_TUNER, DIB3000_TUNER_WRITE_ENABLE(pll_addr));
	पूर्ण अन्यथा अणु
		wr(DIB3000MB_REG_TUNER, DIB3000_TUNER_WRITE_DISABLE(pll_addr));
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dib3000mb_ops;

काष्ठा dvb_frontend* dib3000mb_attach(स्थिर काष्ठा dib3000_config* config,
				      काष्ठा i2c_adapter* i2c, काष्ठा dib_fe_xfer_ops *xfer_ops)
अणु
	काष्ठा dib3000_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा dib3000_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	स_नकल(&state->config,config,माप(काष्ठा dib3000_config));

	/* check क्रम the correct demod */
	अगर (rd(DIB3000_REG_MANUFACTOR_ID) != DIB3000_I2C_ID_DIBCOM)
		जाओ error;

	अगर (rd(DIB3000_REG_DEVICE_ID) != DIB3000MB_DEVICE_ID)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &dib3000mb_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* set the xfer operations */
	xfer_ops->pid_parse = dib3000mb_pid_parse;
	xfer_ops->fअगरo_ctrl = dib3000mb_fअगरo_control;
	xfer_ops->pid_ctrl = dib3000mb_pid_control;
	xfer_ops->tuner_pass_ctrl = dib3000mb_tuner_pass_ctrl;

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dib3000mb_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "DiBcom 3000M-B DVB-T",
		.frequency_min_hz	=  44250 * kHz,
		.frequency_max_hz	= 867250 * kHz,
		.frequency_stepsize_hz	= 62500,
		.caps = FE_CAN_INVERSION_AUTO |
				FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
				FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
				FE_CAN_TRANSMISSION_MODE_AUTO |
				FE_CAN_GUARD_INTERVAL_AUTO |
				FE_CAN_RECOVER |
				FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = dib3000mb_release,

	.init = dib3000mb_fe_init_nonmobile,
	.sleep = dib3000mb_sleep,

	.set_frontend = dib3000mb_set_frontend_and_tuner,
	.get_frontend = dib3000mb_get_frontend,
	.get_tune_settings = dib3000mb_fe_get_tune_settings,

	.पढ़ो_status = dib3000mb_पढ़ो_status,
	.पढ़ो_ber = dib3000mb_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib3000mb_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dib3000mb_पढ़ो_snr,
	.पढ़ो_ucblocks = dib3000mb_पढ़ो_unc_blocks,
पूर्ण;

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(dib3000mb_attach);
