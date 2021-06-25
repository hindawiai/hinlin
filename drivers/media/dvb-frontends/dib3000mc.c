<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम DiBcom DiB3000MC/P-demodulator.
 *
 * Copyright (C) 2004-7 DiBcom (http://www.dibcom.fr/)
 * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * This code is partially based on the previous dib3000mc.c .
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>

#समावेश <media/dvb_frontend.h>

#समावेश "dib3000mc.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

अटल पूर्णांक buggy_sfn_workaround;
module_param(buggy_sfn_workaround, पूर्णांक, 0644);
MODULE_PARM_DESC(buggy_sfn_workaround, "Enable work-around for buggy SFNs (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

काष्ठा dib3000mc_state अणु
	काष्ठा dvb_frontend demod;
	काष्ठा dib3000mc_config *cfg;

	u8 i2c_addr;
	काष्ठा i2c_adapter *i2c_adap;

	काष्ठा dibx000_i2c_master i2c_master;

	u32 timf;

	u32 current_bandwidth;

	u16 dev_id;

	u8 sfn_workaround_active :1;
पूर्ण;

अटल u16 dib3000mc_पढ़ो_word(काष्ठा dib3000mc_state *state, u16 reg)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = state->i2c_addr >> 1, .flags = 0,        .len = 2 पूर्ण,
		अणु .addr = state->i2c_addr >> 1, .flags = I2C_M_RD, .len = 2 पूर्ण,
	पूर्ण;
	u16 word;
	u8 *b;

	b = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!b)
		वापस 0;

	b[0] = (reg >> 8) | 0x80;
	b[1] = reg;
	b[2] = 0;
	b[3] = 0;

	msg[0].buf = b;
	msg[1].buf = b + 2;

	अगर (i2c_transfer(state->i2c_adap, msg, 2) != 2)
		dprपूर्णांकk("i2c read error on %d\n",reg);

	word = (b[2] << 8) | b[3];
	kमुक्त(b);

	वापस word;
पूर्ण

अटल पूर्णांक dib3000mc_ग_लिखो_word(काष्ठा dib3000mc_state *state, u16 reg, u16 val)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = state->i2c_addr >> 1, .flags = 0, .len = 4
	पूर्ण;
	पूर्णांक rc;
	u8 *b;

	b = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	b[0] = reg >> 8;
	b[1] = reg;
	b[2] = val >> 8;
	b[3] = val;

	msg.buf = b;

	rc = i2c_transfer(state->i2c_adap, &msg, 1) != 1 ? -EREMOTEIO : 0;
	kमुक्त(b);

	वापस rc;
पूर्ण

अटल पूर्णांक dib3000mc_identअगरy(काष्ठा dib3000mc_state *state)
अणु
	u16 value;
	अगर ((value = dib3000mc_पढ़ो_word(state, 1025)) != 0x01b3) अणु
		dprपूर्णांकk("-E-  DiB3000MC/P: wrong Vendor ID (read=0x%x)\n",value);
		वापस -EREMOTEIO;
	पूर्ण

	value = dib3000mc_पढ़ो_word(state, 1026);
	अगर (value != 0x3001 && value != 0x3002) अणु
		dprपूर्णांकk("-E-  DiB3000MC/P: wrong Device ID (%x)\n",value);
		वापस -EREMOTEIO;
	पूर्ण
	state->dev_id = value;

	dprपूर्णांकk("-I-  found DiB3000MC/P: %x\n",state->dev_id);

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_set_timing(काष्ठा dib3000mc_state *state, s16 nfft, u32 bw, u8 update_offset)
अणु
	u32 timf;

	अगर (state->timf == 0) अणु
		timf = 1384402; // शेष value क्रम 8MHz
		अगर (update_offset)
			msleep(200); // first समय we करो an update
	पूर्ण अन्यथा
		timf = state->timf;

	timf *= (bw / 1000);

	अगर (update_offset) अणु
		s16 tim_offs = dib3000mc_पढ़ो_word(state, 416);

		अगर (tim_offs &  0x2000)
			tim_offs -= 0x4000;

		अगर (nfft == TRANSMISSION_MODE_2K)
			tim_offs *= 4;

		timf += tim_offs;
		state->timf = timf / (bw / 1000);
	पूर्ण

	dprपूर्णांकk("timf: %d\n", timf);

	dib3000mc_ग_लिखो_word(state, 23, (u16) (timf >> 16));
	dib3000mc_ग_लिखो_word(state, 24, (u16) (timf      ) & 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_setup_pwm_state(काष्ठा dib3000mc_state *state)
अणु
	u16 reg_51, reg_52 = state->cfg->agc->setup & 0xfefb;
	अगर (state->cfg->pwm3_inversion) अणु
		reg_51 =  (2 << 14) | (0 << 10) | (7 << 6) | (2 << 2) | (2 << 0);
		reg_52 |= (1 << 2);
	पूर्ण अन्यथा अणु
		reg_51 = (2 << 14) | (4 << 10) | (7 << 6) | (2 << 2) | (2 << 0);
		reg_52 |= (1 << 8);
	पूर्ण
	dib3000mc_ग_लिखो_word(state, 51, reg_51);
	dib3000mc_ग_लिखो_word(state, 52, reg_52);

	अगर (state->cfg->use_pwm3)
		dib3000mc_ग_लिखो_word(state, 245, (1 << 3) | (1 << 0));
	अन्यथा
		dib3000mc_ग_लिखो_word(state, 245, 0);

	dib3000mc_ग_लिखो_word(state, 1040, 0x3);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_set_output_mode(काष्ठा dib3000mc_state *state, पूर्णांक mode)
अणु
	पूर्णांक    ret = 0;
	u16 fअगरo_threshold = 1792;
	u16 outreg = 0;
	u16 ouपंचांगode = 0;
	u16 elecout = 1;
	u16 smo_reg = dib3000mc_पढ़ो_word(state, 206) & 0x0010; /* keep the pid_parse bit */

	dprपूर्णांकk("-I-  Setting output mode for demod %p to %d\n",
			&state->demod, mode);

	चयन (mode) अणु
		हाल OUTMODE_HIGH_Z:  // disable
			elecout = 0;
			अवरोध;
		हाल OUTMODE_MPEG2_PAR_GATED_CLK:   // STBs with parallel gated घड़ी
			ouपंचांगode = 0;
			अवरोध;
		हाल OUTMODE_MPEG2_PAR_CONT_CLK:    // STBs with parallel जारीs घड़ी
			ouपंचांगode = 1;
			अवरोध;
		हाल OUTMODE_MPEG2_SERIAL:          // STBs with serial input
			ouपंचांगode = 2;
			अवरोध;
		हाल OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			elecout = 3;
			/*ADDR @ 206 :
			P_smo_error_discard  [1;6:6] = 0
			P_smo_rs_discard     [1;5:5] = 0
			P_smo_pid_parse      [1;4:4] = 0
			P_smo_fअगरo_flush     [1;3:3] = 0
			P_smo_mode           [2;2:1] = 11
			P_smo_ovf_prot       [1;0:0] = 0
			*/
			smo_reg |= 3 << 1;
			fअगरo_threshold = 512;
			ouपंचांगode = 5;
			अवरोध;
		हाल OUTMODE_DIVERSITY:
			ouपंचांगode = 4;
			elecout = 1;
			अवरोध;
		शेष:
			dprपूर्णांकk("Unhandled output_mode passed to be set for demod %p\n",&state->demod);
			ouपंचांगode = 0;
			अवरोध;
	पूर्ण

	अगर ((state->cfg->output_mpeg2_in_188_bytes))
		smo_reg |= (1 << 5); // P_smo_rs_discard     [1;5:5] = 1

	outreg = dib3000mc_पढ़ो_word(state, 244) & 0x07FF;
	outreg |= (ouपंचांगode << 11);
	ret |= dib3000mc_ग_लिखो_word(state,  244, outreg);
	ret |= dib3000mc_ग_लिखो_word(state,  206, smo_reg);   /*smo_ mode*/
	ret |= dib3000mc_ग_लिखो_word(state,  207, fअगरo_threshold); /* synchronous ख_पढ़ो */
	ret |= dib3000mc_ग_लिखो_word(state, 1040, elecout);         /* P_out_cfg */
	वापस ret;
पूर्ण

अटल पूर्णांक dib3000mc_set_bandwidth(काष्ठा dib3000mc_state *state, u32 bw)
अणु
	u16 bw_cfg[6] = अणु 0 पूर्ण;
	u16 imp_bw_cfg[3] = अणु 0 पूर्ण;
	u16 reg;

/* settings here are क्रम 27.7MHz */
	चयन (bw) अणु
		हाल 8000:
			bw_cfg[0] = 0x0019; bw_cfg[1] = 0x5c30; bw_cfg[2] = 0x0054; bw_cfg[3] = 0x88a0; bw_cfg[4] = 0x01a6; bw_cfg[5] = 0xab20;
			imp_bw_cfg[0] = 0x04db; imp_bw_cfg[1] = 0x00db; imp_bw_cfg[2] = 0x00b7;
			अवरोध;

		हाल 7000:
			bw_cfg[0] = 0x001c; bw_cfg[1] = 0xfba5; bw_cfg[2] = 0x0060; bw_cfg[3] = 0x9c25; bw_cfg[4] = 0x01e3; bw_cfg[5] = 0x0cb7;
			imp_bw_cfg[0] = 0x04c0; imp_bw_cfg[1] = 0x00c0; imp_bw_cfg[2] = 0x00a0;
			अवरोध;

		हाल 6000:
			bw_cfg[0] = 0x0021; bw_cfg[1] = 0xd040; bw_cfg[2] = 0x0070; bw_cfg[3] = 0xb62b; bw_cfg[4] = 0x0233; bw_cfg[5] = 0x8ed5;
			imp_bw_cfg[0] = 0x04a5; imp_bw_cfg[1] = 0x00a5; imp_bw_cfg[2] = 0x0089;
			अवरोध;

		हाल 5000:
			bw_cfg[0] = 0x0028; bw_cfg[1] = 0x9380; bw_cfg[2] = 0x0087; bw_cfg[3] = 0x4100; bw_cfg[4] = 0x02a4; bw_cfg[5] = 0x4500;
			imp_bw_cfg[0] = 0x0489; imp_bw_cfg[1] = 0x0089; imp_bw_cfg[2] = 0x0072;
			अवरोध;

		शेष: वापस -EINVAL;
	पूर्ण

	क्रम (reg = 6; reg < 12; reg++)
		dib3000mc_ग_लिखो_word(state, reg, bw_cfg[reg - 6]);
	dib3000mc_ग_लिखो_word(state, 12, 0x0000);
	dib3000mc_ग_लिखो_word(state, 13, 0x03e8);
	dib3000mc_ग_लिखो_word(state, 14, 0x0000);
	dib3000mc_ग_लिखो_word(state, 15, 0x03f2);
	dib3000mc_ग_लिखो_word(state, 16, 0x0001);
	dib3000mc_ग_लिखो_word(state, 17, 0xb0d0);
	// P_sec_len
	dib3000mc_ग_लिखो_word(state, 18, 0x0393);
	dib3000mc_ग_लिखो_word(state, 19, 0x8700);

	क्रम (reg = 55; reg < 58; reg++)
		dib3000mc_ग_लिखो_word(state, reg, imp_bw_cfg[reg - 55]);

	// Timing configuration
	dib3000mc_set_timing(state, TRANSMISSION_MODE_2K, bw, 0);

	वापस 0;
पूर्ण

अटल u16 impulse_noise_val[29] =

अणु
	0x38, 0x6d9, 0x3f28, 0x7a7, 0x3a74, 0x196, 0x32a, 0x48c, 0x3ffe, 0x7f3,
	0x2d94, 0x76, 0x53d, 0x3ff8, 0x7e3, 0x3320, 0x76, 0x5b3, 0x3feb, 0x7d2,
	0x365e, 0x76, 0x48c, 0x3ffe, 0x5b3, 0x3feb, 0x76, 0x0000, 0xd
पूर्ण;

अटल व्योम dib3000mc_set_impulse_noise(काष्ठा dib3000mc_state *state, u8 mode, s16 nfft)
अणु
	u16 i;
	क्रम (i = 58; i < 87; i++)
		dib3000mc_ग_लिखो_word(state, i, impulse_noise_val[i-58]);

	अगर (nfft == TRANSMISSION_MODE_8K) अणु
		dib3000mc_ग_लिखो_word(state, 58, 0x3b);
		dib3000mc_ग_लिखो_word(state, 84, 0x00);
		dib3000mc_ग_लिखो_word(state, 85, 0x8200);
	पूर्ण

	dib3000mc_ग_लिखो_word(state, 34, 0x1294);
	dib3000mc_ग_लिखो_word(state, 35, 0x1ff8);
	अगर (mode == 1)
		dib3000mc_ग_लिखो_word(state, 55, dib3000mc_पढ़ो_word(state, 55) | (1 << 10));
पूर्ण

अटल पूर्णांक dib3000mc_init(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib3000mc_state *state = demod->demodulator_priv;
	काष्ठा dibx000_agc_config *agc = state->cfg->agc;

	// Restart Configuration
	dib3000mc_ग_लिखो_word(state, 1027, 0x8000);
	dib3000mc_ग_लिखो_word(state, 1027, 0x0000);

	// घातer up the demod + mobility configuration
	dib3000mc_ग_लिखो_word(state, 140, 0x0000);
	dib3000mc_ग_लिखो_word(state, 1031, 0);

	अगर (state->cfg->mobile_mode) अणु
		dib3000mc_ग_लिखो_word(state, 139,  0x0000);
		dib3000mc_ग_लिखो_word(state, 141,  0x0000);
		dib3000mc_ग_लिखो_word(state, 175,  0x0002);
		dib3000mc_ग_लिखो_word(state, 1032, 0x0000);
	पूर्ण अन्यथा अणु
		dib3000mc_ग_लिखो_word(state, 139,  0x0001);
		dib3000mc_ग_लिखो_word(state, 141,  0x0000);
		dib3000mc_ग_लिखो_word(state, 175,  0x0000);
		dib3000mc_ग_लिखो_word(state, 1032, 0x012C);
	पूर्ण
	dib3000mc_ग_लिखो_word(state, 1033, 0x0000);

	// P_clk_cfg
	dib3000mc_ग_लिखो_word(state, 1037, 0x3130);

	// other configurations

	// P_ctrl_sfreq
	dib3000mc_ग_लिखो_word(state, 33, (5 << 0));
	dib3000mc_ग_लिखो_word(state, 88, (1 << 10) | (0x10 << 0));

	// Phase noise control
	// P_fft_phacor_inh, P_fft_phacor_cpe, P_fft_घातrange
	dib3000mc_ग_लिखो_word(state, 99, (1 << 9) | (0x20 << 0));

	अगर (state->cfg->phase_noise_mode == 0)
		dib3000mc_ग_लिखो_word(state, 111, 0x00);
	अन्यथा
		dib3000mc_ग_लिखो_word(state, 111, 0x02);

	// P_agc_global
	dib3000mc_ग_लिखो_word(state, 50, 0x8000);

	// agc setup misc
	dib3000mc_setup_pwm_state(state);

	// P_agc_counter_lock
	dib3000mc_ग_लिखो_word(state, 53, 0x87);
	// P_agc_counter_unlock
	dib3000mc_ग_लिखो_word(state, 54, 0x87);

	/* agc */
	dib3000mc_ग_लिखो_word(state, 36, state->cfg->max_समय);
	dib3000mc_ग_लिखो_word(state, 37, (state->cfg->agc_command1 << 13) | (state->cfg->agc_command2 << 12) | (0x1d << 0));
	dib3000mc_ग_लिखो_word(state, 38, state->cfg->pwm3_value);
	dib3000mc_ग_लिखो_word(state, 39, state->cfg->ln_adc_level);

	// set_agc_loop_Bw
	dib3000mc_ग_लिखो_word(state, 40, 0x0179);
	dib3000mc_ग_लिखो_word(state, 41, 0x03f0);

	dib3000mc_ग_लिखो_word(state, 42, agc->agc1_max);
	dib3000mc_ग_लिखो_word(state, 43, agc->agc1_min);
	dib3000mc_ग_लिखो_word(state, 44, agc->agc2_max);
	dib3000mc_ग_लिखो_word(state, 45, agc->agc2_min);
	dib3000mc_ग_लिखो_word(state, 46, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib3000mc_ग_लिखो_word(state, 47, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib3000mc_ग_लिखो_word(state, 48, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib3000mc_ग_लिखो_word(state, 49, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

// Begin: TimeOut रेजिस्टरs
	// P_pha3_thres
	dib3000mc_ग_लिखो_word(state, 110, 3277);
	// P_timf_alpha = 6, P_corm_alpha = 6, P_corm_thres = 0x80
	dib3000mc_ग_लिखो_word(state,  26, 0x6680);
	// lock_mask0
	dib3000mc_ग_लिखो_word(state, 1, 4);
	// lock_mask1
	dib3000mc_ग_लिखो_word(state, 2, 4);
	// lock_mask2
	dib3000mc_ग_लिखो_word(state, 3, 0x1000);
	// P_search_maxtrial=1
	dib3000mc_ग_लिखो_word(state, 5, 1);

	dib3000mc_set_bandwidth(state, 8000);

	// भाग_lock_mask
	dib3000mc_ग_लिखो_word(state,  4, 0x814);

	dib3000mc_ग_लिखो_word(state, 21, (1 << 9) | 0x164);
	dib3000mc_ग_लिखो_word(state, 22, 0x463d);

	// Spurious rm cfg
	// P_cspu_regul, P_cspu_win_cut
	dib3000mc_ग_लिखो_word(state, 120, 0x200f);
	// P_adp_selec_monit
	dib3000mc_ग_लिखो_word(state, 134, 0);

	// Fec cfg
	dib3000mc_ग_लिखो_word(state, 195, 0x10);

	// भागersity रेजिस्टर: P_dvsy_sync_रुको..
	dib3000mc_ग_लिखो_word(state, 180, 0x2FF0);

	// Impulse noise configuration
	dib3000mc_set_impulse_noise(state, 0, TRANSMISSION_MODE_8K);

	// output mode set-up
	dib3000mc_set_output_mode(state, OUTMODE_HIGH_Z);

	/* बंद the i2c-gate */
	dib3000mc_ग_लिखो_word(state, 769, (1 << 7) );

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_sleep(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib3000mc_state *state = demod->demodulator_priv;

	dib3000mc_ग_लिखो_word(state, 1031, 0xFFFF);
	dib3000mc_ग_लिखो_word(state, 1032, 0xFFFF);
	dib3000mc_ग_लिखो_word(state, 1033, 0xFFF0);

	वापस 0;
पूर्ण

अटल व्योम dib3000mc_set_adp_cfg(काष्ठा dib3000mc_state *state, s16 qam)
अणु
	u16 cfg[4] = अणु 0 पूर्ण,reg;
	चयन (qam) अणु
		हाल QPSK:
			cfg[0] = 0x099a; cfg[1] = 0x7fae; cfg[2] = 0x0333; cfg[3] = 0x7ff0;
			अवरोध;
		हाल QAM_16:
			cfg[0] = 0x023d; cfg[1] = 0x7fdf; cfg[2] = 0x00a4; cfg[3] = 0x7ff0;
			अवरोध;
		हाल QAM_64:
			cfg[0] = 0x0148; cfg[1] = 0x7ff0; cfg[2] = 0x00a4; cfg[3] = 0x7ff8;
			अवरोध;
	पूर्ण
	क्रम (reg = 129; reg < 133; reg++)
		dib3000mc_ग_लिखो_word(state, reg, cfg[reg - 129]);
पूर्ण

अटल व्योम dib3000mc_set_channel_cfg(काष्ठा dib3000mc_state *state,
				      काष्ठा dtv_frontend_properties *ch, u16 seq)
अणु
	u16 value;
	u32 bw = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);

	dib3000mc_set_bandwidth(state, bw);
	dib3000mc_set_timing(state, ch->transmission_mode, bw, 0);

#अगर 1
	dib3000mc_ग_लिखो_word(state, 100, (16 << 6) + 9);
#अन्यथा
	अगर (boost)
		dib3000mc_ग_लिखो_word(state, 100, (11 << 6) + 6);
	अन्यथा
		dib3000mc_ग_लिखो_word(state, 100, (16 << 6) + 9);
#पूर्ण_अगर

	dib3000mc_ग_लिखो_word(state, 1027, 0x0800);
	dib3000mc_ग_लिखो_word(state, 1027, 0x0000);

	//Default cfg isi offset adp
	dib3000mc_ग_लिखो_word(state, 26,  0x6680);
	dib3000mc_ग_लिखो_word(state, 29,  0x1273);
	dib3000mc_ग_लिखो_word(state, 33,       5);
	dib3000mc_set_adp_cfg(state, QAM_16);
	dib3000mc_ग_लिखो_word(state, 133,  15564);

	dib3000mc_ग_लिखो_word(state, 12 , 0x0);
	dib3000mc_ग_लिखो_word(state, 13 , 0x3e8);
	dib3000mc_ग_लिखो_word(state, 14 , 0x0);
	dib3000mc_ग_लिखो_word(state, 15 , 0x3f2);

	dib3000mc_ग_लिखो_word(state, 93,0);
	dib3000mc_ग_लिखो_word(state, 94,0);
	dib3000mc_ग_लिखो_word(state, 95,0);
	dib3000mc_ग_लिखो_word(state, 96,0);
	dib3000mc_ग_लिखो_word(state, 97,0);
	dib3000mc_ग_लिखो_word(state, 98,0);

	dib3000mc_set_impulse_noise(state, 0, ch->transmission_mode);

	value = 0;
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K: value |= (0 << 7); अवरोध;
		शेष:
		हाल TRANSMISSION_MODE_8K: value |= (1 << 7); अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_32: value |= (0 << 5); अवरोध;
		हाल GUARD_INTERVAL_1_16: value |= (1 << 5); अवरोध;
		हाल GUARD_INTERVAL_1_4:  value |= (3 << 5); अवरोध;
		शेष:
		हाल GUARD_INTERVAL_1_8:  value |= (2 << 5); अवरोध;
	पूर्ण
	चयन (ch->modulation) अणु
		हाल QPSK:  value |= (0 << 3); अवरोध;
		हाल QAM_16: value |= (1 << 3); अवरोध;
		शेष:
		हाल QAM_64: value |= (2 << 3); अवरोध;
	पूर्ण
	चयन (HIERARCHY_1) अणु
		हाल HIERARCHY_2: value |= 2; अवरोध;
		हाल HIERARCHY_4: value |= 4; अवरोध;
		शेष:
		हाल HIERARCHY_1: value |= 1; अवरोध;
	पूर्ण
	dib3000mc_ग_लिखो_word(state, 0, value);
	dib3000mc_ग_लिखो_word(state, 5, (1 << 8) | ((seq & 0xf) << 4));

	value = 0;
	अगर (ch->hierarchy == 1)
		value |= (1 << 4);
	अगर (1 == 1)
		value |= 1;
	चयन ((ch->hierarchy == 0 || 1 == 1) ? ch->code_rate_HP : ch->code_rate_LP) अणु
		हाल FEC_2_3: value |= (2 << 1); अवरोध;
		हाल FEC_3_4: value |= (3 << 1); अवरोध;
		हाल FEC_5_6: value |= (5 << 1); अवरोध;
		हाल FEC_7_8: value |= (7 << 1); अवरोध;
		शेष:
		हाल FEC_1_2: value |= (1 << 1); अवरोध;
	पूर्ण
	dib3000mc_ग_लिखो_word(state, 181, value);

	// भागersity synchro delay add 50% SFN margin
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_8K: value = 256; अवरोध;
		हाल TRANSMISSION_MODE_2K:
		शेष: value = 64; अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_16: value *= 2; अवरोध;
		हाल GUARD_INTERVAL_1_8:  value *= 4; अवरोध;
		हाल GUARD_INTERVAL_1_4:  value *= 8; अवरोध;
		शेष:
		हाल GUARD_INTERVAL_1_32: value *= 1; अवरोध;
	पूर्ण
	value <<= 4;
	value |= dib3000mc_पढ़ो_word(state, 180) & 0x000f;
	dib3000mc_ग_लिखो_word(state, 180, value);

	// restart demod
	value = dib3000mc_पढ़ो_word(state, 0);
	dib3000mc_ग_लिखो_word(state, 0, value | (1 << 9));
	dib3000mc_ग_लिखो_word(state, 0, value);

	msleep(30);

	dib3000mc_set_impulse_noise(state, state->cfg->impulse_noise_mode, ch->transmission_mode);
पूर्ण

अटल पूर्णांक dib3000mc_स्वतःsearch_start(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *chan = &demod->dtv_property_cache;
	काष्ठा dib3000mc_state *state = demod->demodulator_priv;
	u16 reg;
//	u32 val;
	काष्ठा dtv_frontend_properties schan;

	schan = *chan;

	/* TODO what is that ? */

	/* a channel क्रम स्वतःsearch */
	schan.transmission_mode = TRANSMISSION_MODE_8K;
	schan.guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
	schan.modulation = QAM_64;
	schan.code_rate_HP = FEC_2_3;
	schan.code_rate_LP = FEC_2_3;
	schan.hierarchy = 0;

	dib3000mc_set_channel_cfg(state, &schan, 11);

	reg = dib3000mc_पढ़ो_word(state, 0);
	dib3000mc_ग_लिखो_word(state, 0, reg | (1 << 8));
	dib3000mc_पढ़ो_word(state, 511);
	dib3000mc_ग_लिखो_word(state, 0, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_स्वतःsearch_is_irq(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib3000mc_state *state = demod->demodulator_priv;
	u16 irq_pending = dib3000mc_पढ़ो_word(state, 511);

	अगर (irq_pending & 0x1) // failed
		वापस 1;

	अगर (irq_pending & 0x2) // succeeded
		वापस 2;

	वापस 0; // still pending
पूर्ण

अटल पूर्णांक dib3000mc_tune(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib3000mc_state *state = demod->demodulator_priv;

	// ** configure demod **
	dib3000mc_set_channel_cfg(state, ch, 0);

	// activates isi
	अगर (state->sfn_workaround_active) अणु
		dprपूर्णांकk("SFN workaround is active\n");
		dib3000mc_ग_लिखो_word(state, 29, 0x1273);
		dib3000mc_ग_लिखो_word(state, 108, 0x4000); // P_pha3_क्रमce_pha_shअगरt
	पूर्ण अन्यथा अणु
		dib3000mc_ग_लिखो_word(state, 29, 0x1073);
		dib3000mc_ग_लिखो_word(state, 108, 0x0000); // P_pha3_क्रमce_pha_shअगरt
	पूर्ण

	dib3000mc_set_adp_cfg(state, (u8)ch->modulation);
	अगर (ch->transmission_mode == TRANSMISSION_MODE_8K) अणु
		dib3000mc_ग_लिखो_word(state, 26, 38528);
		dib3000mc_ग_लिखो_word(state, 33, 8);
	पूर्ण अन्यथा अणु
		dib3000mc_ग_लिखो_word(state, 26, 30336);
		dib3000mc_ग_लिखो_word(state, 33, 6);
	पूर्ण

	अगर (dib3000mc_पढ़ो_word(state, 509) & 0x80)
		dib3000mc_set_timing(state, ch->transmission_mode,
				     BANDWIDTH_TO_KHZ(ch->bandwidth_hz), 1);

	वापस 0;
पूर्ण

काष्ठा i2c_adapter * dib3000mc_get_tuner_i2c_master(काष्ठा dvb_frontend *demod, पूर्णांक gating)
अणु
	काष्ठा dib3000mc_state *st = demod->demodulator_priv;
	वापस dibx000_get_i2c_adapter(&st->i2c_master, DIBX000_I2C_INTERFACE_TUNER, gating);
पूर्ण

EXPORT_SYMBOL(dib3000mc_get_tuner_i2c_master);

अटल पूर्णांक dib3000mc_get_frontend(काष्ठा dvb_frontend* fe,
				  काष्ठा dtv_frontend_properties *fep)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	u16 tps = dib3000mc_पढ़ो_word(state,458);

	fep->inversion = INVERSION_AUTO;

	fep->bandwidth_hz = state->current_bandwidth;

	चयन ((tps >> 8) & 0x1) अणु
		हाल 0: fep->transmission_mode = TRANSMISSION_MODE_2K; अवरोध;
		हाल 1: fep->transmission_mode = TRANSMISSION_MODE_8K; अवरोध;
	पूर्ण

	चयन (tps & 0x3) अणु
		हाल 0: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_32; अवरोध;
		हाल 1: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_16; अवरोध;
		हाल 2: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_8; अवरोध;
		हाल 3: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_4; अवरोध;
	पूर्ण

	चयन ((tps >> 13) & 0x3) अणु
		हाल 0: fep->modulation = QPSK; अवरोध;
		हाल 1: fep->modulation = QAM_16; अवरोध;
		हाल 2:
		शेष: fep->modulation = QAM_64; अवरोध;
	पूर्ण

	/* as दीर्घ as the frontend_param काष्ठाure is fixed क्रम hierarchical transmission I refuse to use it */
	/* (tps >> 12) & 0x1 == hrch is used, (tps >> 9) & 0x7 == alpha */

	fep->hierarchy = HIERARCHY_NONE;
	चयन ((tps >> 5) & 0x7) अणु
		हाल 1: fep->code_rate_HP = FEC_1_2; अवरोध;
		हाल 2: fep->code_rate_HP = FEC_2_3; अवरोध;
		हाल 3: fep->code_rate_HP = FEC_3_4; अवरोध;
		हाल 5: fep->code_rate_HP = FEC_5_6; अवरोध;
		हाल 7:
		शेष: fep->code_rate_HP = FEC_7_8; अवरोध;

	पूर्ण

	चयन ((tps >> 2) & 0x7) अणु
		हाल 1: fep->code_rate_LP = FEC_1_2; अवरोध;
		हाल 2: fep->code_rate_LP = FEC_2_3; अवरोध;
		हाल 3: fep->code_rate_LP = FEC_3_4; अवरोध;
		हाल 5: fep->code_rate_LP = FEC_5_6; अवरोध;
		हाल 7:
		शेष: fep->code_rate_LP = FEC_7_8; अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	dib3000mc_set_output_mode(state, OUTMODE_HIGH_Z);

	state->current_bandwidth = fep->bandwidth_hz;
	dib3000mc_set_bandwidth(state, BANDWIDTH_TO_KHZ(fep->bandwidth_hz));

	/* maybe the parameter has been changed */
	state->sfn_workaround_active = buggy_sfn_workaround;

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		msleep(100);
	पूर्ण

	अगर (fep->transmission_mode  == TRANSMISSION_MODE_AUTO ||
	    fep->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO ||
	    fep->modulation     == QAM_AUTO ||
	    fep->code_rate_HP   == FEC_AUTO) अणु
		पूर्णांक i = 1000, found;

		dib3000mc_स्वतःsearch_start(fe);
		करो अणु
			msleep(1);
			found = dib3000mc_स्वतःsearch_is_irq(fe);
		पूर्ण जबतक (found == 0 && i--);

		dprपूर्णांकk("autosearch returns: %d\n",found);
		अगर (found == 0 || found == 1)
			वापस 0; // no channel found

		dib3000mc_get_frontend(fe, fep);
	पूर्ण

	ret = dib3000mc_tune(fe);

	/* make this a config parameter */
	dib3000mc_set_output_mode(state, OUTMODE_MPEG2_FIFO);
	वापस ret;
पूर्ण

अटल पूर्णांक dib3000mc_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	u16 lock = dib3000mc_पढ़ो_word(state, 509);

	*stat = 0;

	अगर (lock & 0x8000)
		*stat |= FE_HAS_SIGNAL;
	अगर (lock & 0x3000)
		*stat |= FE_HAS_CARRIER;
	अगर (lock & 0x0100)
		*stat |= FE_HAS_VITERBI;
	अगर (lock & 0x0010)
		*stat |= FE_HAS_SYNC;
	अगर (lock & 0x0008)
		*stat |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	*ber = (dib3000mc_पढ़ो_word(state, 500) << 16) | dib3000mc_पढ़ो_word(state, 501);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 *unc)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	*unc = dib3000mc_पढ़ो_word(state, 508);
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	u16 val = dib3000mc_पढ़ो_word(state, 392);
	*strength = 65535 - val;
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	*snr = 0x0000;
	वापस 0;
पूर्ण

अटल पूर्णांक dib3000mc_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम dib3000mc_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	dibx000_निकास_i2c_master(&state->i2c_master);
	kमुक्त(state);
पूर्ण

पूर्णांक dib3000mc_pid_control(काष्ठा dvb_frontend *fe, पूर्णांक index, पूर्णांक pid,पूर्णांक onoff)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	dib3000mc_ग_लिखो_word(state, 212 + index,  onoff ? (1 << 13) | pid : 0);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib3000mc_pid_control);

पूर्णांक dib3000mc_pid_parse(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	u16 पंचांगp = dib3000mc_पढ़ो_word(state, 206) & ~(1 << 4);
	पंचांगp |= (onoff << 4);
	वापस dib3000mc_ग_लिखो_word(state, 206, पंचांगp);
पूर्ण
EXPORT_SYMBOL(dib3000mc_pid_parse);

व्योम dib3000mc_set_config(काष्ठा dvb_frontend *fe, काष्ठा dib3000mc_config *cfg)
अणु
	काष्ठा dib3000mc_state *state = fe->demodulator_priv;
	state->cfg = cfg;
पूर्ण
EXPORT_SYMBOL(dib3000mc_set_config);

पूर्णांक dib3000mc_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c, पूर्णांक no_of_demods, u8 शेष_addr, काष्ठा dib3000mc_config cfg[])
अणु
	काष्ठा dib3000mc_state *dmcst;
	पूर्णांक k;
	u8 new_addr;

	अटल u8 DIB3000MC_I2C_ADDRESS[] = अणु20,22,24,26पूर्ण;

	dmcst = kzalloc(माप(काष्ठा dib3000mc_state), GFP_KERNEL);
	अगर (dmcst == शून्य)
		वापस -ENOMEM;

	dmcst->i2c_adap = i2c;

	क्रम (k = no_of_demods-1; k >= 0; k--) अणु
		dmcst->cfg = &cfg[k];

		/* designated i2c address */
		new_addr          = DIB3000MC_I2C_ADDRESS[k];
		dmcst->i2c_addr = new_addr;
		अगर (dib3000mc_identअगरy(dmcst) != 0) अणु
			dmcst->i2c_addr = शेष_addr;
			अगर (dib3000mc_identअगरy(dmcst) != 0) अणु
				dprपूर्णांकk("-E-  DiB3000P/MC #%d: not identified\n", k);
				kमुक्त(dmcst);
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		dib3000mc_set_output_mode(dmcst, OUTMODE_MPEG2_PAR_CONT_CLK);

		// set new i2c address and क्रमce भागstr (Bit 1) to value 0 (Bit 0)
		dib3000mc_ग_लिखो_word(dmcst, 1024, (new_addr << 3) | 0x1);
		dmcst->i2c_addr = new_addr;
	पूर्ण

	क्रम (k = 0; k < no_of_demods; k++) अणु
		dmcst->cfg = &cfg[k];
		dmcst->i2c_addr = DIB3000MC_I2C_ADDRESS[k];

		dib3000mc_ग_लिखो_word(dmcst, 1024, dmcst->i2c_addr << 3);

		/* turn off data output */
		dib3000mc_set_output_mode(dmcst, OUTMODE_HIGH_Z);
	पूर्ण

	kमुक्त(dmcst);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib3000mc_i2c_क्रमागतeration);

अटल स्थिर काष्ठा dvb_frontend_ops dib3000mc_ops;

काष्ठा dvb_frontend * dib3000mc_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib3000mc_config *cfg)
अणु
	काष्ठा dvb_frontend *demod;
	काष्ठा dib3000mc_state *st;
	st = kzalloc(माप(काष्ठा dib3000mc_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;

	st->cfg = cfg;
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	स_नकल(&st->demod.ops, &dib3000mc_ops, माप(काष्ठा dvb_frontend_ops));

	अगर (dib3000mc_identअगरy(st) != 0)
		जाओ error;

	dibx000_init_i2c_master(&st->i2c_master, DIB3000MC, st->i2c_adap, st->i2c_addr);

	dib3000mc_ग_लिखो_word(st, 1037, 0x3130);

	वापस demod;

error:
	kमुक्त(st);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dib3000mc_attach);

अटल स्थिर काष्ठा dvb_frontend_ops dib3000mc_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "DiBcom 3000MC/P",
		.frequency_min_hz      =  44250 * kHz,
		.frequency_max_hz      = 867250 * kHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release              = dib3000mc_release,

	.init                 = dib3000mc_init,
	.sleep                = dib3000mc_sleep,

	.set_frontend         = dib3000mc_set_frontend,
	.get_tune_settings    = dib3000mc_fe_get_tune_settings,
	.get_frontend         = dib3000mc_get_frontend,

	.पढ़ो_status          = dib3000mc_पढ़ो_status,
	.पढ़ो_ber             = dib3000mc_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib3000mc_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = dib3000mc_पढ़ो_snr,
	.पढ़ो_ucblocks        = dib3000mc_पढ़ो_unc_blocks,
पूर्ण;

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the DiBcom 3000MC/P COFDM demodulator");
MODULE_LICENSE("GPL");
