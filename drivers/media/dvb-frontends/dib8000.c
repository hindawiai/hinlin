<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux-DVB Driver क्रम DiBcom's DiB8000 chip (ISDB-T).
 *
 * Copyright (C) 2009 DiBcom (http://www.dibcom.fr/)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_गणित.स>

#समावेश <media/dvb_frontend.h>

#समावेश "dib8000.h"

#घोषणा LAYER_ALL -1
#घोषणा LAYER_A   1
#घोषणा LAYER_B   2
#घोषणा LAYER_C   3

#घोषणा MAX_NUMBER_OF_FRONTENDS 6
/* #घोषणा DIB8000_AGC_FREEZE */

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

काष्ठा i2c_device अणु
	काष्ठा i2c_adapter *adap;
	u8 addr;
	u8 *i2c_ग_लिखो_buffer;
	u8 *i2c_पढ़ो_buffer;
	काष्ठा mutex *i2c_buffer_lock;
पूर्ण;

क्रमागत param_loop_step अणु
	LOOP_TUNE_1,
	LOOP_TUNE_2
पूर्ण;

क्रमागत dib8000_स्वतःsearch_step अणु
	AS_START = 0,
	AS_SEARCHING_FFT,
	AS_SEARCHING_GUARD,
	AS_DONE = 100,
पूर्ण;

क्रमागत समयout_mode अणु
	SYMBOL_DEPENDENT_OFF = 0,
	SYMBOL_DEPENDENT_ON,
पूर्ण;

काष्ठा dib8000_state अणु
	काष्ठा dib8000_config cfg;

	काष्ठा i2c_device i2c;

	काष्ठा dibx000_i2c_master i2c_master;

	u16 wbd_ref;

	u8 current_band;
	u32 current_bandwidth;
	काष्ठा dibx000_agc_config *current_agc;
	u32 timf;
	u32 timf_शेष;

	u8 भाग_क्रमce_off:1;
	u8 भाग_state:1;
	u16 भाग_sync_रुको;

	u8 agc_state;
	u8 dअगरferential_स्थिरellation;
	u8 भागersity_onoff;

	s16 ber_monitored_layer;
	u16 gpio_dir;
	u16 gpio_val;

	u16 revision;
	u8 isdbt_cfg_loaded;
	क्रमागत frontend_tune_state tune_state;
	s32 status;

	काष्ठा dvb_frontend *fe[MAX_NUMBER_OF_FRONTENDS];

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[4];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
	u8 input_mode_mpeg;

	u16 tuner_enable;
	काष्ठा i2c_adapter dib8096p_tuner_adap;
	u16 current_demod_bw;

	u16 seg_mask;
	u16 seg_dअगरf_mask;
	u16 mode;
	u8 layer_b_nb_seg;
	u8 layer_c_nb_seg;

	u8 channel_parameters_set;
	u16 स्वतःsearch_state;
	u16 found_nfft;
	u16 found_guard;
	u8 subchannel;
	u8 symbol_duration;
	अचिन्हित दीर्घ समयout;
	u8 दीर्घest_पूर्णांकlv_layer;
	u16 output_mode;

	/* क्रम DVBv5 stats */
	s64 init_ucb;
	अचिन्हित दीर्घ per_jअगरfies_stats;
	अचिन्हित दीर्घ ber_jअगरfies_stats;
	अचिन्हित दीर्घ ber_jअगरfies_stats_layer[3];

#अगर_घोषित DIB8000_AGC_FREEZE
	u16 agc1_max;
	u16 agc1_min;
	u16 agc2_max;
	u16 agc2_min;
#पूर्ण_अगर
पूर्ण;

क्रमागत dib8000_घातer_mode अणु
	DIB8000_POWER_ALL = 0,
	DIB8000_POWER_INTERFACE_ONLY,
पूर्ण;

अटल u16 dib8000_i2c_पढ़ो16(काष्ठा i2c_device *i2c, u16 reg)
अणु
	u16 ret;
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = i2c->addr >> 1, .flags = 0, .len = 2पूर्ण,
		अणु.addr = i2c->addr >> 1, .flags = I2C_M_RD, .len = 2पूर्ण,
	पूर्ण;

	अगर (mutex_lock_पूर्णांकerruptible(i2c->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	msg[0].buf    = i2c->i2c_ग_लिखो_buffer;
	msg[0].buf[0] = reg >> 8;
	msg[0].buf[1] = reg & 0xff;
	msg[1].buf    = i2c->i2c_पढ़ो_buffer;

	अगर (i2c_transfer(i2c->adap, msg, 2) != 2)
		dprपूर्णांकk("i2c read error on %d\n", reg);

	ret = (msg[1].buf[0] << 8) | msg[1].buf[1];
	mutex_unlock(i2c->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल u16 __dib8000_पढ़ो_word(काष्ठा dib8000_state *state, u16 reg)
अणु
	u16 ret;

	state->i2c_ग_लिखो_buffer[0] = reg >> 8;
	state->i2c_ग_लिखो_buffer[1] = reg & 0xff;

	स_रखो(state->msg, 0, 2 * माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c.addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 2;
	state->msg[1].addr = state->i2c.addr >> 1;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = state->i2c_पढ़ो_buffer;
	state->msg[1].len = 2;

	अगर (i2c_transfer(state->i2c.adap, state->msg, 2) != 2)
		dprपूर्णांकk("i2c read error on %d\n", reg);

	ret = (state->i2c_पढ़ो_buffer[0] << 8) | state->i2c_पढ़ो_buffer[1];

	वापस ret;
पूर्ण

अटल u16 dib8000_पढ़ो_word(काष्ठा dib8000_state *state, u16 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	ret = __dib8000_पढ़ो_word(state, reg);

	mutex_unlock(&state->i2c_buffer_lock);

	वापस ret;
पूर्ण

अटल u32 dib8000_पढ़ो32(काष्ठा dib8000_state *state, u16 reg)
अणु
	u16 rw[2];

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	rw[0] = __dib8000_पढ़ो_word(state, reg + 0);
	rw[1] = __dib8000_पढ़ो_word(state, reg + 1);

	mutex_unlock(&state->i2c_buffer_lock);

	वापस ((rw[0] << 16) | (rw[1]));
पूर्ण

अटल पूर्णांक dib8000_i2c_ग_लिखो16(काष्ठा i2c_device *i2c, u16 reg, u16 val)
अणु
	काष्ठा i2c_msg msg = अणु.addr = i2c->addr >> 1, .flags = 0, .len = 4पूर्ण;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(i2c->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	msg.buf    = i2c->i2c_ग_लिखो_buffer;
	msg.buf[0] = (reg >> 8) & 0xff;
	msg.buf[1] = reg & 0xff;
	msg.buf[2] = (val >> 8) & 0xff;
	msg.buf[3] = val & 0xff;

	ret = i2c_transfer(i2c->adap, &msg, 1) != 1 ? -EREMOTEIO : 0;
	mutex_unlock(i2c->i2c_buffer_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dib8000_ग_लिखो_word(काष्ठा dib8000_state *state, u16 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = (reg >> 8) & 0xff;
	state->i2c_ग_लिखो_buffer[1] = reg & 0xff;
	state->i2c_ग_लिखो_buffer[2] = (val >> 8) & 0xff;
	state->i2c_ग_लिखो_buffer[3] = val & 0xff;

	स_रखो(&state->msg[0], 0, माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c.addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 4;

	ret = (i2c_transfer(state->i2c.adap, state->msg, 1) != 1 ?
			-EREMOTEIO : 0);
	mutex_unlock(&state->i2c_buffer_lock);

	वापस ret;
पूर्ण

अटल स्थिर s16 coeff_2k_sb_1seg_dqpsk[8] = अणु
	(769 << 5) | 0x0a, (745 << 5) | 0x03, (595 << 5) | 0x0d, (769 << 5) | 0x0a, (920 << 5) | 0x09, (784 << 5) | 0x02, (519 << 5) | 0x0c,
		(920 << 5) | 0x09
पूर्ण;

अटल स्थिर s16 coeff_2k_sb_1seg[8] = अणु
	(692 << 5) | 0x0b, (683 << 5) | 0x01, (519 << 5) | 0x09, (692 << 5) | 0x0b, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f
पूर्ण;

अटल स्थिर s16 coeff_2k_sb_3seg_0dqpsk_1dqpsk[8] = अणु
	(832 << 5) | 0x10, (912 << 5) | 0x05, (900 << 5) | 0x12, (832 << 5) | 0x10, (-931 << 5) | 0x0f, (912 << 5) | 0x04, (807 << 5) | 0x11,
		(-931 << 5) | 0x0f
पूर्ण;

अटल स्थिर s16 coeff_2k_sb_3seg_0dqpsk[8] = अणु
	(622 << 5) | 0x0c, (941 << 5) | 0x04, (796 << 5) | 0x10, (622 << 5) | 0x0c, (982 << 5) | 0x0c, (519 << 5) | 0x02, (572 << 5) | 0x0e,
		(982 << 5) | 0x0c
पूर्ण;

अटल स्थिर s16 coeff_2k_sb_3seg_1dqpsk[8] = अणु
	(699 << 5) | 0x14, (607 << 5) | 0x04, (944 << 5) | 0x13, (699 << 5) | 0x14, (-720 << 5) | 0x0d, (640 << 5) | 0x03, (866 << 5) | 0x12,
		(-720 << 5) | 0x0d
पूर्ण;

अटल स्थिर s16 coeff_2k_sb_3seg[8] = अणु
	(664 << 5) | 0x0c, (925 << 5) | 0x03, (937 << 5) | 0x10, (664 << 5) | 0x0c, (-610 << 5) | 0x0a, (697 << 5) | 0x01, (836 << 5) | 0x0e,
		(-610 << 5) | 0x0a
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_1seg_dqpsk[8] = अणु
	(-955 << 5) | 0x0e, (687 << 5) | 0x04, (818 << 5) | 0x10, (-955 << 5) | 0x0e, (-922 << 5) | 0x0d, (750 << 5) | 0x03, (665 << 5) | 0x0f,
		(-922 << 5) | 0x0d
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_1seg[8] = अणु
	(638 << 5) | 0x0d, (683 << 5) | 0x02, (638 << 5) | 0x0d, (638 << 5) | 0x0d, (-655 << 5) | 0x0a, (517 << 5) | 0x00, (698 << 5) | 0x0d,
		(-655 << 5) | 0x0a
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_3seg_0dqpsk_1dqpsk[8] = अणु
	(-707 << 5) | 0x14, (910 << 5) | 0x06, (889 << 5) | 0x16, (-707 << 5) | 0x14, (-958 << 5) | 0x13, (993 << 5) | 0x05, (523 << 5) | 0x14,
		(-958 << 5) | 0x13
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_3seg_0dqpsk[8] = अणु
	(-723 << 5) | 0x13, (910 << 5) | 0x05, (777 << 5) | 0x14, (-723 << 5) | 0x13, (-568 << 5) | 0x0f, (547 << 5) | 0x03, (696 << 5) | 0x12,
		(-568 << 5) | 0x0f
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_3seg_1dqpsk[8] = अणु
	(-940 << 5) | 0x15, (607 << 5) | 0x05, (915 << 5) | 0x16, (-940 << 5) | 0x15, (-848 << 5) | 0x13, (683 << 5) | 0x04, (543 << 5) | 0x14,
		(-848 << 5) | 0x13
पूर्ण;

अटल स्थिर s16 coeff_4k_sb_3seg[8] = अणु
	(612 << 5) | 0x12, (910 << 5) | 0x04, (864 << 5) | 0x14, (612 << 5) | 0x12, (-869 << 5) | 0x13, (683 << 5) | 0x02, (869 << 5) | 0x12,
		(-869 << 5) | 0x13
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_1seg_dqpsk[8] = अणु
	(-835 << 5) | 0x12, (684 << 5) | 0x05, (735 << 5) | 0x14, (-835 << 5) | 0x12, (-598 << 5) | 0x10, (781 << 5) | 0x04, (739 << 5) | 0x13,
		(-598 << 5) | 0x10
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_1seg[8] = अणु
	(673 << 5) | 0x0f, (683 << 5) | 0x03, (808 << 5) | 0x12, (673 << 5) | 0x0f, (585 << 5) | 0x0f, (512 << 5) | 0x01, (780 << 5) | 0x0f,
		(585 << 5) | 0x0f
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_3seg_0dqpsk_1dqpsk[8] = अणु
	(863 << 5) | 0x17, (930 << 5) | 0x07, (878 << 5) | 0x19, (863 << 5) | 0x17, (0 << 5) | 0x14, (521 << 5) | 0x05, (980 << 5) | 0x18,
		(0 << 5) | 0x14
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_3seg_0dqpsk[8] = अणु
	(-924 << 5) | 0x17, (910 << 5) | 0x06, (774 << 5) | 0x17, (-924 << 5) | 0x17, (-877 << 5) | 0x15, (565 << 5) | 0x04, (553 << 5) | 0x15,
		(-877 << 5) | 0x15
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_3seg_1dqpsk[8] = अणु
	(-921 << 5) | 0x19, (607 << 5) | 0x06, (881 << 5) | 0x19, (-921 << 5) | 0x19, (-921 << 5) | 0x14, (713 << 5) | 0x05, (1018 << 5) | 0x18,
		(-921 << 5) | 0x14
पूर्ण;

अटल स्थिर s16 coeff_8k_sb_3seg[8] = अणु
	(514 << 5) | 0x14, (910 << 5) | 0x05, (861 << 5) | 0x17, (514 << 5) | 0x14, (690 << 5) | 0x14, (683 << 5) | 0x03, (662 << 5) | 0x15,
		(690 << 5) | 0x14
पूर्ण;

अटल स्थिर s16 ana_fe_coeff_3seg[24] = अणु
	81, 80, 78, 74, 68, 61, 54, 45, 37, 28, 19, 11, 4, 1022, 1017, 1013, 1010, 1008, 1008, 1008, 1008, 1010, 1014, 1017
पूर्ण;

अटल स्थिर s16 ana_fe_coeff_1seg[24] = अणु
	249, 226, 164, 82, 5, 981, 970, 988, 1018, 20, 31, 26, 8, 1012, 1000, 1018, 1012, 8, 15, 14, 9, 3, 1017, 1003
पूर्ण;

अटल स्थिर s16 ana_fe_coeff_13seg[24] = अणु
	396, 305, 105, -51, -77, -12, 41, 31, -11, -30, -11, 14, 15, -2, -13, -7, 5, 8, 1, -6, -7, -3, 0, 1
पूर्ण;

अटल u16 fft_to_mode(काष्ठा dib8000_state *state)
अणु
	u16 mode;
	चयन (state->fe[0]->dtv_property_cache.transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		mode = 1;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		mode = 2;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_AUTO:
	हाल TRANSMISSION_MODE_8K:
		mode = 3;
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

अटल व्योम dib8000_set_acquisition_mode(काष्ठा dib8000_state *state)
अणु
	u16 nud = dib8000_पढ़ो_word(state, 298);
	nud |= (1 << 3) | (1 << 0);
	dprपूर्णांकk("acquisition mode activated\n");
	dib8000_ग_लिखो_word(state, 298, nud);
पूर्ण
अटल पूर्णांक dib8000_set_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 outreg, fअगरo_threshold, smo_mode, sram = 0x0205;	/* by शेष SDRAM deपूर्णांकlv is enabled */

	state->output_mode = mode;
	outreg = 0;
	fअगरo_threshold = 1792;
	smo_mode = (dib8000_पढ़ो_word(state, 299) & 0x0050) | (1 << 1);

	dprपूर्णांकk("-I-	Setting output mode for demod %p to %d\n",
			&state->fe[0], mode);

	चयन (mode) अणु
	हाल OUTMODE_MPEG2_PAR_GATED_CLK:	// STBs with parallel gated घड़ी
		outreg = (1 << 10);	/* 0x0400 */
		अवरोध;
	हाल OUTMODE_MPEG2_PAR_CONT_CLK:	// STBs with parallel जारीs घड़ी
		outreg = (1 << 10) | (1 << 6);	/* 0x0440 */
		अवरोध;
	हाल OUTMODE_MPEG2_SERIAL:	// STBs with serial input
		outreg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0482 */
		अवरोध;
	हाल OUTMODE_DIVERSITY:
		अगर (state->cfg.hostbus_भागersity) अणु
			outreg = (1 << 10) | (4 << 6);	/* 0x0500 */
			sram &= 0xfdff;
		पूर्ण अन्यथा
			sram |= 0x0c00;
		अवरोध;
	हाल OUTMODE_MPEG2_FIFO:	// e.g. USB feeding
		smo_mode |= (3 << 1);
		fअगरo_threshold = 512;
		outreg = (1 << 10) | (5 << 6);
		अवरोध;
	हाल OUTMODE_HIGH_Z:	// disable
		outreg = 0;
		अवरोध;

	हाल OUTMODE_ANALOG_ADC:
		outreg = (1 << 10) | (3 << 6);
		dib8000_set_acquisition_mode(state);
		अवरोध;

	शेष:
		dprपूर्णांकk("Unhandled output_mode passed to be set for demod %p\n",
				&state->fe[0]);
		वापस -EINVAL;
	पूर्ण

	अगर (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	dib8000_ग_लिखो_word(state, 299, smo_mode);
	dib8000_ग_लिखो_word(state, 300, fअगरo_threshold);	/* synchronous ख_पढ़ो */
	dib8000_ग_लिखो_word(state, 1286, outreg);
	dib8000_ग_लिखो_word(state, 1291, sram);

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_भागersity_in(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 पंचांगp, sync_रुको = dib8000_पढ़ो_word(state, 273) & 0xfff0;

	dprपूर्णांकk("set diversity input to %i\n", onoff);
	अगर (!state->dअगरferential_स्थिरellation) अणु
		dib8000_ग_लिखो_word(state, 272, 1 << 9);	//dvsy_off_lmod4 = 1
		dib8000_ग_लिखो_word(state, 273, sync_रुको | (1 << 2) | 2);	// sync_enable = 1; comb_mode = 2
	पूर्ण अन्यथा अणु
		dib8000_ग_लिखो_word(state, 272, 0);	//dvsy_off_lmod4 = 0
		dib8000_ग_लिखो_word(state, 273, sync_रुको);	// sync_enable = 0; comb_mode = 0
	पूर्ण
	state->भागersity_onoff = onoff;

	चयन (onoff) अणु
	हाल 0:		/* only use the पूर्णांकernal way - not the भागersity input */
		dib8000_ग_लिखो_word(state, 270, 1);
		dib8000_ग_लिखो_word(state, 271, 0);
		अवरोध;
	हाल 1:		/* both ways */
		dib8000_ग_लिखो_word(state, 270, 6);
		dib8000_ग_लिखो_word(state, 271, 6);
		अवरोध;
	हाल 2:		/* only the भागersity input */
		dib8000_ग_लिखो_word(state, 270, 0);
		dib8000_ग_लिखो_word(state, 271, 1);
		अवरोध;
	पूर्ण

	अगर (state->revision == 0x8002) अणु
		पंचांगp = dib8000_पढ़ो_word(state, 903);
		dib8000_ग_लिखो_word(state, 903, पंचांगp & ~(1 << 3));
		msleep(30);
		dib8000_ग_लिखो_word(state, 903, पंचांगp | (1 << 3));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dib8000_set_घातer_mode(काष्ठा dib8000_state *state, क्रमागत dib8000_घातer_mode mode)
अणु
	/* by शेष everything is going to be घातered off */
	u16 reg_774 = 0x3fff, reg_775 = 0xffff, reg_776 = 0xffff,
		reg_900 = (dib8000_पढ़ो_word(state, 900) & 0xfffc) | 0x3,
		reg_1280;

	अगर (state->revision != 0x8090)
		reg_1280 = (dib8000_पढ़ो_word(state, 1280) & 0x00ff) | 0xff00;
	अन्यथा
		reg_1280 = (dib8000_पढ़ो_word(state, 1280) & 0x707f) | 0x8f80;

	/* now, depending on the requested mode, we घातer on */
	चयन (mode) अणु
		/* घातer up everything in the demod */
	हाल DIB8000_POWER_ALL:
		reg_774 = 0x0000;
		reg_775 = 0x0000;
		reg_776 = 0x0000;
		reg_900 &= 0xfffc;
		अगर (state->revision != 0x8090)
			reg_1280 &= 0x00ff;
		अन्यथा
			reg_1280 &= 0x707f;
		अवरोध;
	हाल DIB8000_POWER_INTERFACE_ONLY:
		अगर (state->revision != 0x8090)
			reg_1280 &= 0x00ff;
		अन्यथा
			reg_1280 &= 0xfa7b;
		अवरोध;
	पूर्ण

	dprपूर्णांकk("powermode : 774 : %x ; 775 : %x; 776 : %x ; 900 : %x; 1280 : %x\n", reg_774, reg_775, reg_776, reg_900, reg_1280);
	dib8000_ग_लिखो_word(state, 774, reg_774);
	dib8000_ग_लिखो_word(state, 775, reg_775);
	dib8000_ग_लिखो_word(state, 776, reg_776);
	dib8000_ग_लिखो_word(state, 900, reg_900);
	dib8000_ग_लिखो_word(state, 1280, reg_1280);
पूर्ण

अटल पूर्णांक dib8000_set_adc_state(काष्ठा dib8000_state *state, क्रमागत dibx000_adc_states no)
अणु
	पूर्णांक ret = 0;
	u16 reg, reg_907 = dib8000_पढ़ो_word(state, 907);
	u16 reg_908 = dib8000_पढ़ो_word(state, 908);

	चयन (no) अणु
	हाल DIBX000_SLOW_ADC_ON:
		अगर (state->revision != 0x8090) अणु
			reg_908 |= (1 << 1) | (1 << 0);
			ret |= dib8000_ग_लिखो_word(state, 908, reg_908);
			reg_908 &= ~(1 << 1);
		पूर्ण अन्यथा अणु
			reg = dib8000_पढ़ो_word(state, 1925);
			/* en_slowAdc = 1 & reset_sladc = 1 */
			dib8000_ग_लिखो_word(state, 1925, reg |
					(1<<4) | (1<<2));

			/* पढ़ो access to make it works... strange ... */
			reg = dib8000_पढ़ो_word(state, 1925);
			msleep(20);
			/* en_slowAdc = 1 & reset_sladc = 0 */
			dib8000_ग_लिखो_word(state, 1925, reg & ~(1<<4));

			reg = dib8000_पढ़ो_word(state, 921) & ~((0x3 << 14)
					| (0x3 << 12));
			/* ref = Vin1 => Vbg ; sel = Vin0 or Vin3 ;
			   (Vin2 = Vcm) */
			dib8000_ग_लिखो_word(state, 921, reg | (1 << 14)
					| (3 << 12));
		पूर्ण
		अवरोध;

	हाल DIBX000_SLOW_ADC_OFF:
		अगर (state->revision == 0x8090) अणु
			reg = dib8000_पढ़ो_word(state, 1925);
			/* reset_sladc = 1 en_slowAdc = 0 */
			dib8000_ग_लिखो_word(state, 1925,
					(reg & ~(1<<2)) | (1<<4));
		पूर्ण
		reg_908 |= (1 << 1) | (1 << 0);
		अवरोध;

	हाल DIBX000_ADC_ON:
		reg_907 &= 0x0fff;
		reg_908 &= 0x0003;
		अवरोध;

	हाल DIBX000_ADC_OFF:	// leave the VBG voltage on
		reg_907 = (1 << 13) | (1 << 12);
		reg_908 = (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 1);
		अवरोध;

	हाल DIBX000_VBG_ENABLE:
		reg_907 &= ~(1 << 15);
		अवरोध;

	हाल DIBX000_VBG_DISABLE:
		reg_907 |= (1 << 15);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ret |= dib8000_ग_लिखो_word(state, 907, reg_907);
	ret |= dib8000_ग_लिखो_word(state, 908, reg_908);

	वापस ret;
पूर्ण

अटल पूर्णांक dib8000_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bw)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u32 timf;

	अगर (bw == 0)
		bw = 6000;

	अगर (state->timf == 0) अणु
		dprपूर्णांकk("using default timf\n");
		timf = state->timf_शेष;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("using updated timf\n");
		timf = state->timf;
	पूर्ण

	dib8000_ग_लिखो_word(state, 29, (u16) ((timf >> 16) & 0xffff));
	dib8000_ग_लिखो_word(state, 30, (u16) ((timf) & 0xffff));

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_sad_calib(काष्ठा dib8000_state *state)
अणु
	u8 sad_sel = 3;

	अगर (state->revision == 0x8090) अणु
		dib8000_ग_लिखो_word(state, 922, (sad_sel << 2));
		dib8000_ग_लिखो_word(state, 923, 2048);

		dib8000_ग_लिखो_word(state, 922, (sad_sel << 2) | 0x1);
		dib8000_ग_लिखो_word(state, 922, (sad_sel << 2));
	पूर्ण अन्यथा अणु
		/* पूर्णांकernal */
		dib8000_ग_लिखो_word(state, 923, (0 << 1) | (0 << 0));
		dib8000_ग_लिखो_word(state, 924, 776);

		/* करो the calibration */
		dib8000_ग_लिखो_word(state, 923, (1 << 0));
		dib8000_ग_लिखो_word(state, 923, (0 << 0));
	पूर्ण

	msleep(1);
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_wbd_ref(काष्ठा dvb_frontend *fe, u16 value)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	अगर (value > 4095)
		value = 4095;
	state->wbd_ref = value;
	वापस dib8000_ग_लिखो_word(state, 106, value);
पूर्ण

अटल व्योम dib8000_reset_pll_common(काष्ठा dib8000_state *state, स्थिर काष्ठा dibx000_bandwidth_config *bw)
अणु
	dprपूर्णांकk("ifreq: %d %x, inversion: %d\n", bw->अगरreq, bw->अगरreq, bw->अगरreq >> 25);
	अगर (state->revision != 0x8090) अणु
		dib8000_ग_लिखो_word(state, 23,
				(u16) (((bw->पूर्णांकernal * 1000) >> 16) & 0xffff));
		dib8000_ग_लिखो_word(state, 24,
				(u16) ((bw->पूर्णांकernal * 1000) & 0xffff));
	पूर्ण अन्यथा अणु
		dib8000_ग_लिखो_word(state, 23, (u16) (((bw->पूर्णांकernal / 2 * 1000) >> 16) & 0xffff));
		dib8000_ग_लिखो_word(state, 24,
				(u16) ((bw->पूर्णांकernal  / 2 * 1000) & 0xffff));
	पूर्ण
	dib8000_ग_लिखो_word(state, 27, (u16) ((bw->अगरreq >> 16) & 0x01ff));
	dib8000_ग_लिखो_word(state, 28, (u16) (bw->अगरreq & 0xffff));
	dib8000_ग_लिखो_word(state, 26, (u16) ((bw->अगरreq >> 25) & 0x0003));

	अगर (state->revision != 0x8090)
		dib8000_ग_लिखो_word(state, 922, bw->sad_cfg);
पूर्ण

अटल व्योम dib8000_reset_pll(काष्ठा dib8000_state *state)
अणु
	स्थिर काष्ठा dibx000_bandwidth_config *pll = state->cfg.pll;
	u16 clk_cfg1, reg;

	अगर (state->revision != 0x8090) अणु
		dib8000_ग_लिखो_word(state, 901,
				(pll->pll_preभाग << 8) | (pll->pll_ratio << 0));

		clk_cfg1 = (1 << 10) | (0 << 9) | (pll->IO_CLK_en_core << 8) |
			(pll->bypclk_भाग << 5) | (pll->enable_refभाग << 4) |
			(1 << 3) | (pll->pll_range << 1) |
			(pll->pll_reset << 0);

		dib8000_ग_लिखो_word(state, 902, clk_cfg1);
		clk_cfg1 = (clk_cfg1 & 0xfff7) | (pll->pll_bypass << 3);
		dib8000_ग_लिखो_word(state, 902, clk_cfg1);

		dprपूर्णांकk("clk_cfg1: 0x%04x\n", clk_cfg1);

		/* smpl_cfg: P_refclksel=2, P_ensmplsel=1 noभागsmpl=1 */
		अगर (state->cfg.pll->ADClkSrc == 0)
			dib8000_ग_लिखो_word(state, 904,
					(0 << 15) | (0 << 12) | (0 << 10) |
					(pll->modulo << 8) |
					(pll->ADClkSrc << 7) | (0 << 1));
		अन्यथा अगर (state->cfg.refclksel != 0)
			dib8000_ग_लिखो_word(state, 904, (0 << 15) | (1 << 12) |
					((state->cfg.refclksel & 0x3) << 10) |
					(pll->modulo << 8) |
					(pll->ADClkSrc << 7) | (0 << 1));
		अन्यथा
			dib8000_ग_लिखो_word(state, 904, (0 << 15) | (1 << 12) |
					(3 << 10) | (pll->modulo << 8) |
					(pll->ADClkSrc << 7) | (0 << 1));
	पूर्ण अन्यथा अणु
		dib8000_ग_लिखो_word(state, 1856, (!pll->pll_reset<<13) |
				(pll->pll_range<<12) | (pll->pll_ratio<<6) |
				(pll->pll_preभाग));

		reg = dib8000_पढ़ो_word(state, 1857);
		dib8000_ग_लिखो_word(state, 1857, reg|(!pll->pll_bypass<<15));

		reg = dib8000_पढ़ो_word(state, 1858); /* Force clk out pll /2 */
		dib8000_ग_लिखो_word(state, 1858, reg | 1);

		dib8000_ग_लिखो_word(state, 904, (pll->modulo << 8));
	पूर्ण

	dib8000_reset_pll_common(state, pll);
पूर्ण

अटल पूर्णांक dib8000_update_pll(काष्ठा dvb_frontend *fe,
		काष्ठा dibx000_bandwidth_config *pll, u32 bw, u8 ratio)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 reg_1857, reg_1856 = dib8000_पढ़ो_word(state, 1856);
	u8 loopभाग, preभाग, oldpreभाग = state->cfg.pll->pll_preभाग ;
	u32 पूर्णांकernal, xtal;

	/* get back old values */
	preभाग = reg_1856 & 0x3f;
	loopभाग = (reg_1856 >> 6) & 0x3f;

	अगर ((pll == शून्य) || (pll->pll_preभाग == preभाग &&
				pll->pll_ratio == loopभाग))
		वापस -EINVAL;

	dprपूर्णांकk("Updating pll (prediv: old =  %d new = %d ; loopdiv : old = %d new = %d)\n", preभाग, pll->pll_preभाग, loopभाग, pll->pll_ratio);
	अगर (state->revision == 0x8090) अणु
		reg_1856 &= 0xf000;
		reg_1857 = dib8000_पढ़ो_word(state, 1857);
		/* disable PLL */
		dib8000_ग_लिखो_word(state, 1857, reg_1857 & ~(1 << 15));

		dib8000_ग_लिखो_word(state, 1856, reg_1856 |
				((pll->pll_ratio & 0x3f) << 6) |
				(pll->pll_preभाग & 0x3f));

		/* ग_लिखो new प्रणाली clk पूर्णांकo P_sec_len */
		पूर्णांकernal = dib8000_पढ़ो32(state, 23) / 1000;
		dprपूर्णांकk("Old Internal = %d\n", पूर्णांकernal);
		xtal = 2 * (पूर्णांकernal / loopभाग) * preभाग;
		पूर्णांकernal = 1000 * (xtal/pll->pll_preभाग) * pll->pll_ratio;
		dprपूर्णांकk("Xtal = %d , New Fmem = %d New Fdemod = %d, New Fsampling = %d\n", xtal, पूर्णांकernal/1000, पूर्णांकernal/2000, पूर्णांकernal/8000);
		dprपूर्णांकk("New Internal = %d\n", पूर्णांकernal);

		dib8000_ग_लिखो_word(state, 23,
				(u16) (((पूर्णांकernal / 2) >> 16) & 0xffff));
		dib8000_ग_लिखो_word(state, 24, (u16) ((पूर्णांकernal / 2) & 0xffff));
		/* enable PLL */
		dib8000_ग_लिखो_word(state, 1857, reg_1857 | (1 << 15));

		जबतक (((dib8000_पढ़ो_word(state, 1856)>>15)&0x1) != 1)
			dprपूर्णांकk("Waiting for PLL to lock\n");

		/* verअगरy */
		reg_1856 = dib8000_पढ़ो_word(state, 1856);
		dprपूर्णांकk("PLL Updated with prediv = %d and loopdiv = %d\n",
				reg_1856&0x3f, (reg_1856>>6)&0x3f);
	पूर्ण अन्यथा अणु
		अगर (bw != state->current_demod_bw) अणु
			/** Bandwidth change => क्रमce PLL update **/
			dprपूर्णांकk("PLL: Bandwidth Change %d MHz -> %d MHz (prediv: %d->%d)\n", state->current_demod_bw / 1000, bw / 1000, oldpreभाग, state->cfg.pll->pll_preभाग);

			अगर (state->cfg.pll->pll_preभाग != oldpreभाग) अणु
				/** Full PLL change only अगर preभाग is changed **/

				/** full update => bypass and reconfigure **/
				dprपूर्णांकk("PLL: New Setting for %d MHz Bandwidth (prediv: %d, ratio: %d)\n", bw/1000, state->cfg.pll->pll_preभाग, state->cfg.pll->pll_ratio);
				dib8000_ग_लिखो_word(state, 902, dib8000_पढ़ो_word(state, 902) | (1<<3)); /* bypass PLL */
				dib8000_reset_pll(state);
				dib8000_ग_लिखो_word(state, 898, 0x0004); /* sad */
			पूर्ण अन्यथा
				ratio = state->cfg.pll->pll_ratio;

			state->current_demod_bw = bw;
		पूर्ण

		अगर (ratio != 0) अणु
			/** ratio update => only change ratio **/
			dprपूर्णांकk("PLL: Update ratio (prediv: %d, ratio: %d)\n", state->cfg.pll->pll_preभाग, ratio);
			dib8000_ग_लिखो_word(state, 901, (state->cfg.pll->pll_preभाग << 8) | (ratio << 0)); /* only the PLL ratio is updated. */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_reset_gpio(काष्ठा dib8000_state *st)
अणु
	/* reset the GPIOs */
	dib8000_ग_लिखो_word(st, 1029, st->cfg.gpio_dir);
	dib8000_ग_लिखो_word(st, 1030, st->cfg.gpio_val);

	/* TODO 782 is P_gpio_od */

	dib8000_ग_लिखो_word(st, 1032, st->cfg.gpio_pwm_pos);

	dib8000_ग_लिखो_word(st, 1037, st->cfg.pwm_freq_भाग);
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_cfg_gpio(काष्ठा dib8000_state *st, u8 num, u8 dir, u8 val)
अणु
	st->cfg.gpio_dir = dib8000_पढ़ो_word(st, 1029);
	st->cfg.gpio_dir &= ~(1 << num);	/* reset the direction bit */
	st->cfg.gpio_dir |= (dir & 0x1) << num;	/* set the new direction */
	dib8000_ग_लिखो_word(st, 1029, st->cfg.gpio_dir);

	st->cfg.gpio_val = dib8000_पढ़ो_word(st, 1030);
	st->cfg.gpio_val &= ~(1 << num);	/* reset the direction bit */
	st->cfg.gpio_val |= (val & 0x01) << num;	/* set the new value */
	dib8000_ग_लिखो_word(st, 1030, st->cfg.gpio_val);

	dprपूर्णांकk("gpio dir: %x: gpio val: %x\n", st->cfg.gpio_dir, st->cfg.gpio_val);

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_gpio(काष्ठा dvb_frontend *fe, u8 num, u8 dir, u8 val)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	वापस dib8000_cfg_gpio(state, num, dir, val);
पूर्ण

अटल स्थिर u16 dib8000_शेषs[] = अणु
	/* स्वतः search configuration - lock0 by शेष रुकोing
	 * क्रम cpil_lock; lock1 cpil_lock; lock2 पंचांगcc_sync_lock */
	3, 7,
	0x0004,
	0x0400,
	0x0814,

	12, 11,
	0x001b,
	0x7740,
	0x005b,
	0x8d80,
	0x01c9,
	0xc380,
	0x0000,
	0x0080,
	0x0000,
	0x0090,
	0x0001,
	0xd4c0,

	/*1, 32,
		0x6680 // P_corm_thres Lock algorithms configuration */

	11, 80,			/* set ADC level to -16 */
	(1 << 13) - 825 - 117,
	(1 << 13) - 837 - 117,
	(1 << 13) - 811 - 117,
	(1 << 13) - 766 - 117,
	(1 << 13) - 737 - 117,
	(1 << 13) - 693 - 117,
	(1 << 13) - 648 - 117,
	(1 << 13) - 619 - 117,
	(1 << 13) - 575 - 117,
	(1 << 13) - 531 - 117,
	(1 << 13) - 501 - 117,

	4, 108,
	0,
	0,
	0,
	0,

	1, 175,
	0x0410,
	1, 179,
	8192,			// P_fft_nb_to_cut

	6, 181,
	0x2800,			// P_coff_corthres_ ( 2k 4k 8k ) 0x2800
	0x2800,
	0x2800,
	0x2800,			// P_coff_cpilthres_ ( 2k 4k 8k ) 0x2800
	0x2800,
	0x2800,

	2, 193,
	0x0666,			// P_pha3_thres
	0x0000,			// P_cti_use_cpe, P_cti_use_prog

	2, 205,
	0x200f,			// P_cspu_regul, P_cspu_win_cut
	0x000f,			// P_des_shअगरt_work

	5, 215,
	0x023d,			// P_adp_regul_cnt
	0x00a4,			// P_adp_noise_cnt
	0x00a4,			// P_adp_regul_ext
	0x7ff0,			// P_adp_noise_ext
	0x3ccc,			// P_adp_fil

	1, 230,
	0x0000,			// P_2d_byp_ti_num

	1, 263,
	0x800,			//P_equal_thres_wgn

	1, 268,
	(2 << 9) | 39,		// P_equal_ctrl_synchro, P_equal_speedmode

	1, 270,
	0x0001,			// P_भाग_lock0_रुको
	1, 285,
	0x0020,			//p_fec_
	1, 299,
	0x0062,			/* P_smo_mode, P_smo_rs_discard, P_smo_fअगरo_flush, P_smo_pid_parse, P_smo_error_discard */

	1, 338,
	(1 << 12) |		// P_ctrl_corm_thres4pre_freq_inh=1
		(1 << 10) |
		(0 << 9) |		/* P_ctrl_pre_freq_inh=0 */
		(3 << 5) |		/* P_ctrl_pre_freq_step=3 */
		(1 << 0),		/* P_pre_freq_win_len=1 */

	0,
पूर्ण;

अटल u16 dib8000_identअगरy(काष्ठा i2c_device *client)
अणु
	u16 value;

	//because of glitches someबार
	value = dib8000_i2c_पढ़ो16(client, 896);

	अगर ((value = dib8000_i2c_पढ़ो16(client, 896)) != 0x01b3) अणु
		dprपूर्णांकk("wrong Vendor ID (read=0x%x)\n", value);
		वापस 0;
	पूर्ण

	value = dib8000_i2c_पढ़ो16(client, 897);
	अगर (value != 0x8000 && value != 0x8001 &&
			value != 0x8002 && value != 0x8090) अणु
		dprपूर्णांकk("wrong Device ID (%x)\n", value);
		वापस 0;
	पूर्ण

	चयन (value) अणु
	हाल 0x8000:
		dprपूर्णांकk("found DiB8000A\n");
		अवरोध;
	हाल 0x8001:
		dprपूर्णांकk("found DiB8000B\n");
		अवरोध;
	हाल 0x8002:
		dprपूर्णांकk("found DiB8000C\n");
		अवरोध;
	हाल 0x8090:
		dprपूर्णांकk("found DiB8096P\n");
		अवरोध;
	पूर्ण
	वापस value;
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 *unc);

अटल व्योम dib8000_reset_stats(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u32 ucb;

	स_रखो(&c->strength, 0, माप(c->strength));
	स_रखो(&c->cnr, 0, माप(c->cnr));
	स_रखो(&c->post_bit_error, 0, माप(c->post_bit_error));
	स_रखो(&c->post_bit_count, 0, माप(c->post_bit_count));
	स_रखो(&c->block_error, 0, माप(c->block_error));

	c->strength.len = 1;
	c->cnr.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;
	c->post_bit_error.len = 1;
	c->post_bit_count.len = 1;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].uvalue = 0;

	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dib8000_पढ़ो_unc_blocks(fe, &ucb);

	state->init_ucb = -ucb;
	state->ber_jअगरfies_stats = 0;
	state->per_jअगरfies_stats = 0;
	स_रखो(&state->ber_jअगरfies_stats_layer, 0,
	       माप(state->ber_jअगरfies_stats_layer));
पूर्ण

अटल पूर्णांक dib8000_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	अगर ((state->revision = dib8000_identअगरy(&state->i2c)) == 0)
		वापस -EINVAL;

	/* sram lead in, rdy */
	अगर (state->revision != 0x8090)
		dib8000_ग_लिखो_word(state, 1287, 0x0003);

	अगर (state->revision == 0x8000)
		dprपूर्णांकk("error : dib8000 MA not supported\n");

	dibx000_reset_i2c_master(&state->i2c_master);

	dib8000_set_घातer_mode(state, DIB8000_POWER_ALL);

	/* always leave the VBG voltage on - it consumes almost nothing but takes a दीर्घ समय to start */
	dib8000_set_adc_state(state, DIBX000_ADC_OFF);

	/* restart all parts */
	dib8000_ग_लिखो_word(state, 770, 0xffff);
	dib8000_ग_लिखो_word(state, 771, 0xffff);
	dib8000_ग_लिखो_word(state, 772, 0xfffc);
	dib8000_ग_लिखो_word(state, 898, 0x000c);	/* restart sad */
	अगर (state->revision == 0x8090)
		dib8000_ग_लिखो_word(state, 1280, 0x0045);
	अन्यथा
		dib8000_ग_लिखो_word(state, 1280, 0x004d);
	dib8000_ग_लिखो_word(state, 1281, 0x000c);

	dib8000_ग_लिखो_word(state, 770, 0x0000);
	dib8000_ग_लिखो_word(state, 771, 0x0000);
	dib8000_ग_लिखो_word(state, 772, 0x0000);
	dib8000_ग_लिखो_word(state, 898, 0x0004);	// sad
	dib8000_ग_लिखो_word(state, 1280, 0x0000);
	dib8000_ग_लिखो_word(state, 1281, 0x0000);

	/* drives */
	अगर (state->revision != 0x8090) अणु
		अगर (state->cfg.drives)
			dib8000_ग_लिखो_word(state, 906, state->cfg.drives);
		अन्यथा अणु
			dprपूर्णांकk("using standard PAD-drive-settings, please adjust settings in config-struct to be optimal.\n");
			/* min drive SDRAM - not optimal - adjust */
			dib8000_ग_लिखो_word(state, 906, 0x2d98);
		पूर्ण
	पूर्ण

	dib8000_reset_pll(state);
	अगर (state->revision != 0x8090)
		dib8000_ग_लिखो_word(state, 898, 0x0004);

	अगर (dib8000_reset_gpio(state) != 0)
		dprपूर्णांकk("GPIO reset was not successful.\n");

	अगर ((state->revision != 0x8090) &&
			(dib8000_set_output_mode(fe, OUTMODE_HIGH_Z) != 0))
		dprपूर्णांकk("OUTPUT_MODE could not be reset.\n");

	state->current_agc = शून्य;

	// P_iqc_alpha_pha, P_iqc_alpha_amp, P_iqc_dcc_alpha, ...
	/* P_iqc_ca2 = 0; P_iqc_impnc_on = 0; P_iqc_mode = 0; */
	अगर (state->cfg.pll->अगरreq == 0)
		dib8000_ग_लिखो_word(state, 40, 0x0755);	/* P_iqc_corr_inh = 0 enable IQcorr block */
	अन्यथा
		dib8000_ग_लिखो_word(state, 40, 0x1f55);	/* P_iqc_corr_inh = 1 disable IQcorr block */

	अणु
		u16 l = 0, r;
		स्थिर u16 *n;
		n = dib8000_शेषs;
		l = *n++;
		जबतक (l) अणु
			r = *n++;
			करो अणु
				dib8000_ग_लिखो_word(state, r, *n++);
				r++;
			पूर्ण जबतक (--l);
			l = *n++;
		पूर्ण
	पूर्ण

	state->isdbt_cfg_loaded = 0;

	//भाग_cfg override क्रम special configs
	अगर ((state->revision != 8090) && (state->cfg.भाग_cfg != 0))
		dib8000_ग_लिखो_word(state, 903, state->cfg.भाग_cfg);

	/* unक्रमce भागstr regardless whether i2c क्रमागतeration was करोne or not */
	dib8000_ग_लिखो_word(state, 1285, dib8000_पढ़ो_word(state, 1285) & ~(1 << 1));

	dib8000_set_bandwidth(fe, 6000);

	dib8000_set_adc_state(state, DIBX000_SLOW_ADC_ON);
	dib8000_sad_calib(state);
	अगर (state->revision != 0x8090)
		dib8000_set_adc_state(state, DIBX000_SLOW_ADC_OFF);

	/* ber_rs_len = 3 */
	dib8000_ग_लिखो_word(state, 285, (dib8000_पढ़ो_word(state, 285) & ~0x60) | (3 << 5));

	dib8000_set_घातer_mode(state, DIB8000_POWER_INTERFACE_ONLY);

	dib8000_reset_stats(fe);

	वापस 0;
पूर्ण

अटल व्योम dib8000_restart_agc(काष्ठा dib8000_state *state)
अणु
	// P_restart_iqc & P_restart_agc
	dib8000_ग_लिखो_word(state, 770, 0x0a00);
	dib8000_ग_लिखो_word(state, 770, 0x0000);
पूर्ण

अटल पूर्णांक dib8000_update_lna(काष्ठा dib8000_state *state)
अणु
	u16 dyn_gain;

	अगर (state->cfg.update_lna) अणु
		// पढ़ो dyn_gain here (because it is demod-dependent and not tuner)
		dyn_gain = dib8000_पढ़ो_word(state, 390);

		अगर (state->cfg.update_lna(state->fe[0], dyn_gain)) अणु
			dib8000_restart_agc(state);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_agc_config(काष्ठा dib8000_state *state, u8 band)
अणु
	काष्ठा dibx000_agc_config *agc = शून्य;
	पूर्णांक i;
	u16 reg;

	अगर (state->current_band == band && state->current_agc != शून्य)
		वापस 0;
	state->current_band = band;

	क्रम (i = 0; i < state->cfg.agc_config_count; i++)
		अगर (state->cfg.agc[i].band_caps & band) अणु
			agc = &state->cfg.agc[i];
			अवरोध;
		पूर्ण

	अगर (agc == शून्य) अणु
		dprपूर्णांकk("no valid AGC configuration found for band 0x%02x\n", band);
		वापस -EINVAL;
	पूर्ण

	state->current_agc = agc;

	/* AGC */
	dib8000_ग_लिखो_word(state, 76, agc->setup);
	dib8000_ग_लिखो_word(state, 77, agc->inv_gain);
	dib8000_ग_लिखो_word(state, 78, agc->समय_stabiliz);
	dib8000_ग_लिखो_word(state, 101, (agc->alpha_level << 12) | agc->thlock);

	// Demod AGC loop configuration
	dib8000_ग_लिखो_word(state, 102, (agc->alpha_mant << 5) | agc->alpha_exp);
	dib8000_ग_लिखो_word(state, 103, (agc->beta_mant << 6) | agc->beta_exp);

	dprपूर्णांकk("WBD: ref: %d, sel: %d, active: %d, alpha: %d\n",
		state->wbd_ref != 0 ? state->wbd_ref : agc->wbd_ref, agc->wbd_sel, !agc->perक्रमm_agc_softsplit, agc->wbd_sel);

	/* AGC जारीd */
	अगर (state->wbd_ref != 0)
		dib8000_ग_लिखो_word(state, 106, state->wbd_ref);
	अन्यथा			// use शेष
		dib8000_ग_लिखो_word(state, 106, agc->wbd_ref);

	अगर (state->revision == 0x8090) अणु
		reg = dib8000_पढ़ो_word(state, 922) & (0x3 << 2);
		dib8000_ग_लिखो_word(state, 922, reg | (agc->wbd_sel << 2));
	पूर्ण

	dib8000_ग_लिखो_word(state, 107, (agc->wbd_alpha << 9) | (agc->perक्रमm_agc_softsplit << 8));
	dib8000_ग_लिखो_word(state, 108, agc->agc1_max);
	dib8000_ग_लिखो_word(state, 109, agc->agc1_min);
	dib8000_ग_लिखो_word(state, 110, agc->agc2_max);
	dib8000_ग_लिखो_word(state, 111, agc->agc2_min);
	dib8000_ग_लिखो_word(state, 112, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib8000_ग_लिखो_word(state, 113, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib8000_ग_लिखो_word(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib8000_ग_लिखो_word(state, 115, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

	dib8000_ग_लिखो_word(state, 75, agc->agc1_pt3);
	अगर (state->revision != 0x8090)
		dib8000_ग_लिखो_word(state, 923,
				(dib8000_पढ़ो_word(state, 923) & 0xffe3) |
				(agc->wbd_inv << 4) | (agc->wbd_sel << 2));

	वापस 0;
पूर्ण

अटल व्योम dib8000_pwm_agc_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	dib8000_set_adc_state(state, DIBX000_ADC_ON);
	dib8000_set_agc_config(state, (अचिन्हित अक्षर)(BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000)));
पूर्ण

अटल पूर्णांक dib8000_agc_soft_split(काष्ठा dib8000_state *state)
अणु
	u16 agc, split_offset;

	अगर (!state->current_agc || !state->current_agc->perक्रमm_agc_softsplit || state->current_agc->split.max == 0)
		वापस 0;

	// n_agc_global
	agc = dib8000_पढ़ो_word(state, 390);

	अगर (agc > state->current_agc->split.min_thres)
		split_offset = state->current_agc->split.min;
	अन्यथा अगर (agc < state->current_agc->split.max_thres)
		split_offset = state->current_agc->split.max;
	अन्यथा
		split_offset = state->current_agc->split.max *
			(agc - state->current_agc->split.min_thres) /
			(state->current_agc->split.max_thres - state->current_agc->split.min_thres);

	dprपूर्णांकk("AGC split_offset: %d\n", split_offset);

	// P_agc_क्रमce_split and P_agc_split_offset
	dib8000_ग_लिखो_word(state, 107, (dib8000_पढ़ो_word(state, 107) & 0xff00) | split_offset);
	वापस 5000;
पूर्ण

अटल पूर्णांक dib8000_agc_startup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	क्रमागत frontend_tune_state *tune_state = &state->tune_state;
	पूर्णांक ret = 0;
	u16 reg;
	u32 upd_demod_gain_period = 0x8000;

	चयन (*tune_state) अणु
	हाल CT_AGC_START:
		// set घातer-up level: पूर्णांकerf+analog+AGC

		अगर (state->revision != 0x8090)
			dib8000_set_adc_state(state, DIBX000_ADC_ON);
		अन्यथा अणु
			dib8000_set_घातer_mode(state, DIB8000_POWER_ALL);

			reg = dib8000_पढ़ो_word(state, 1947)&0xff00;
			dib8000_ग_लिखो_word(state, 1946,
					upd_demod_gain_period & 0xFFFF);
			/* bit 14 = enDemodGain */
			dib8000_ग_लिखो_word(state, 1947, reg | (1<<14) |
					((upd_demod_gain_period >> 16) & 0xFF));

			/* enable adc i & q */
			reg = dib8000_पढ़ो_word(state, 1920);
			dib8000_ग_लिखो_word(state, 1920, (reg | 0x3) &
					(~(1 << 7)));
		पूर्ण

		अगर (dib8000_set_agc_config(state, (अचिन्हित अक्षर)(BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000))) != 0) अणु
			*tune_state = CT_AGC_STOP;
			state->status = FE_STATUS_TUNE_FAILED;
			अवरोध;
		पूर्ण

		ret = 70;
		*tune_state = CT_AGC_STEP_0;
		अवरोध;

	हाल CT_AGC_STEP_0:
		//AGC initialization
		अगर (state->cfg.agc_control)
			state->cfg.agc_control(fe, 1);

		dib8000_restart_agc(state);

		// रुको AGC rough lock समय
		ret = 50;
		*tune_state = CT_AGC_STEP_1;
		अवरोध;

	हाल CT_AGC_STEP_1:
		// रुको AGC accurate lock समय
		ret = 70;

		अगर (dib8000_update_lna(state))
			// रुको only AGC rough lock समय
			ret = 50;
		अन्यथा
			*tune_state = CT_AGC_STEP_2;
		अवरोध;

	हाल CT_AGC_STEP_2:
		dib8000_agc_soft_split(state);

		अगर (state->cfg.agc_control)
			state->cfg.agc_control(fe, 0);

		*tune_state = CT_AGC_STOP;
		अवरोध;
	शेष:
		ret = dib8000_agc_soft_split(state);
		अवरोध;
	पूर्ण
	वापस ret;

पूर्ण

अटल व्योम dib8096p_host_bus_drive(काष्ठा dib8000_state *state, u8 drive)
अणु
	u16 reg;

	drive &= 0x7;

	/* drive host bus 2, 3, 4 */
	reg = dib8000_पढ़ो_word(state, 1798) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_ग_लिखो_word(state, 1798, reg);

	/* drive host bus 5,6 */
	reg = dib8000_पढ़ो_word(state, 1799) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive<<8) | (drive<<2);
	dib8000_ग_लिखो_word(state, 1799, reg);

	/* drive host bus 7, 8, 9 */
	reg = dib8000_पढ़ो_word(state, 1800) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_ग_लिखो_word(state, 1800, reg);

	/* drive host bus 10, 11 */
	reg = dib8000_पढ़ो_word(state, 1801) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive<<8) | (drive<<2);
	dib8000_ग_लिखो_word(state, 1801, reg);

	/* drive host bus 12, 13, 14 */
	reg = dib8000_पढ़ो_word(state, 1802) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	reg |= (drive<<12) | (drive<<6) | drive;
	dib8000_ग_लिखो_word(state, 1802, reg);
पूर्ण

अटल u32 dib8096p_calcSyncFreq(u32 P_Kin, u32 P_Kout,
		u32 insertExtSynchro, u32 syncSize)
अणु
	u32 quantअगर = 3;
	u32 nom = (insertExtSynchro * P_Kin+syncSize);
	u32 denom = P_Kout;
	u32 syncFreq = ((nom << quantअगर) / denom);

	अगर ((syncFreq & ((1 << quantअगर) - 1)) != 0)
		syncFreq = (syncFreq >> quantअगर) + 1;
	अन्यथा
		syncFreq = (syncFreq >> quantअगर);

	अगर (syncFreq != 0)
		syncFreq = syncFreq - 1;

	वापस syncFreq;
पूर्ण

अटल व्योम dib8096p_cfg_DibTx(काष्ठा dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 insertExtSynchro, u32 synchroMode,
		u32 syncWord, u32 syncSize)
अणु
	dprपूर्णांकk("Configure DibStream Tx\n");

	dib8000_ग_लिखो_word(state, 1615, 1);
	dib8000_ग_लिखो_word(state, 1603, P_Kin);
	dib8000_ग_लिखो_word(state, 1605, P_Kout);
	dib8000_ग_लिखो_word(state, 1606, insertExtSynchro);
	dib8000_ग_लिखो_word(state, 1608, synchroMode);
	dib8000_ग_लिखो_word(state, 1609, (syncWord >> 16) & 0xffff);
	dib8000_ग_लिखो_word(state, 1610, syncWord & 0xffff);
	dib8000_ग_लिखो_word(state, 1612, syncSize);
	dib8000_ग_लिखो_word(state, 1615, 0);
पूर्ण

अटल व्योम dib8096p_cfg_DibRx(काष्ठा dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 synchroMode, u32 insertExtSynchro,
		u32 syncWord, u32 syncSize, u32 dataOutRate)
अणु
	u32 syncFreq;

	dprपूर्णांकk("Configure DibStream Rx synchroMode = %d\n", synchroMode);

	अगर ((P_Kin != 0) && (P_Kout != 0)) अणु
		syncFreq = dib8096p_calcSyncFreq(P_Kin, P_Kout,
				insertExtSynchro, syncSize);
		dib8000_ग_लिखो_word(state, 1542, syncFreq);
	पूर्ण

	dib8000_ग_लिखो_word(state, 1554, 1);
	dib8000_ग_लिखो_word(state, 1536, P_Kin);
	dib8000_ग_लिखो_word(state, 1537, P_Kout);
	dib8000_ग_लिखो_word(state, 1539, synchroMode);
	dib8000_ग_लिखो_word(state, 1540, (syncWord >> 16) & 0xffff);
	dib8000_ग_लिखो_word(state, 1541, syncWord & 0xffff);
	dib8000_ग_लिखो_word(state, 1543, syncSize);
	dib8000_ग_लिखो_word(state, 1544, dataOutRate);
	dib8000_ग_लिखो_word(state, 1554, 0);
पूर्ण

अटल व्योम dib8096p_enMpegMux(काष्ठा dib8000_state *state, पूर्णांक onoff)
अणु
	u16 reg_1287;

	reg_1287 = dib8000_पढ़ो_word(state, 1287);

	चयन (onoff) अणु
	हाल 1:
			reg_1287 &= ~(1 << 8);
			अवरोध;
	हाल 0:
			reg_1287 |= (1 << 8);
			अवरोध;
	पूर्ण

	dib8000_ग_लिखो_word(state, 1287, reg_1287);
पूर्ण

अटल व्योम dib8096p_configMpegMux(काष्ठा dib8000_state *state,
		u16 pulseWidth, u16 enSerialMode, u16 enSerialClkDiv2)
अणु
	u16 reg_1287;

	dprपूर्णांकk("Enable Mpeg mux\n");

	dib8096p_enMpegMux(state, 0);

	/* If the input mode is MPEG करो not भागide the serial घड़ी */
	अगर ((enSerialMode == 1) && (state->input_mode_mpeg == 1))
		enSerialClkDiv2 = 0;

	reg_1287 = ((pulseWidth & 0x1f) << 3) |
		((enSerialMode & 0x1) << 2) | (enSerialClkDiv2 & 0x1);
	dib8000_ग_लिखो_word(state, 1287, reg_1287);

	dib8096p_enMpegMux(state, 1);
पूर्ण

अटल व्योम dib8096p_setDibTxMux(काष्ठा dib8000_state *state, पूर्णांक mode)
अणु
	u16 reg_1288 = dib8000_पढ़ो_word(state, 1288) & ~(0x7 << 7);

	चयन (mode) अणु
	हाल MPEG_ON_DIBTX:
			dprपूर्णांकk("SET MPEG ON DIBSTREAM TX\n");
			dib8096p_cfg_DibTx(state, 8, 5, 0, 0, 0, 0);
			reg_1288 |= (1 << 9); अवरोध;
	हाल DIV_ON_DIBTX:
			dprपूर्णांकk("SET DIV_OUT ON DIBSTREAM TX\n");
			dib8096p_cfg_DibTx(state, 5, 5, 0, 0, 0, 0);
			reg_1288 |= (1 << 8); अवरोध;
	हाल ADC_ON_DIBTX:
			dprपूर्णांकk("SET ADC_OUT ON DIBSTREAM TX\n");
			dib8096p_cfg_DibTx(state, 20, 5, 10, 0, 0, 0);
			reg_1288 |= (1 << 7); अवरोध;
	शेष:
			अवरोध;
	पूर्ण
	dib8000_ग_लिखो_word(state, 1288, reg_1288);
पूर्ण

अटल व्योम dib8096p_setHostBusMux(काष्ठा dib8000_state *state, पूर्णांक mode)
अणु
	u16 reg_1288 = dib8000_पढ़ो_word(state, 1288) & ~(0x7 << 4);

	चयन (mode) अणु
	हाल DEMOUT_ON_HOSTBUS:
			dprपूर्णांकk("SET DEM OUT OLD INTERF ON HOST BUS\n");
			dib8096p_enMpegMux(state, 0);
			reg_1288 |= (1 << 6);
			अवरोध;
	हाल DIBTX_ON_HOSTBUS:
			dprपूर्णांकk("SET DIBSTREAM TX ON HOST BUS\n");
			dib8096p_enMpegMux(state, 0);
			reg_1288 |= (1 << 5);
			अवरोध;
	हाल MPEG_ON_HOSTBUS:
			dprपूर्णांकk("SET MPEG MUX ON HOST BUS\n");
			reg_1288 |= (1 << 4);
			अवरोध;
	शेष:
			अवरोध;
	पूर्ण
	dib8000_ग_लिखो_word(state, 1288, reg_1288);
पूर्ण

अटल पूर्णांक dib8096p_set_भागersity_in(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 reg_1287;

	चयन (onoff) अणु
	हाल 0: /* only use the पूर्णांकernal way - not the भागersity input */
			dprपूर्णांकk("%s mode OFF : by default Enable Mpeg INPUT\n",
					__func__);
			/* outputRate = 8 */
			dib8096p_cfg_DibRx(state, 8, 5, 0, 0, 0, 8, 0);

			/* Do not भागide the serial घड़ी of MPEG MUX in
			   SERIAL MODE in हाल input mode MPEG is used */
			reg_1287 = dib8000_पढ़ो_word(state, 1287);
			/* enSerialClkDiv2 == 1 ? */
			अगर ((reg_1287 & 0x1) == 1) अणु
				/* क्रमce enSerialClkDiv2 = 0 */
				reg_1287 &= ~0x1;
				dib8000_ग_लिखो_word(state, 1287, reg_1287);
			पूर्ण
			state->input_mode_mpeg = 1;
			अवरोध;
	हाल 1: /* both ways */
	हाल 2: /* only the भागersity input */
			dprपूर्णांकk("%s ON : Enable diversity INPUT\n", __func__);
			dib8096p_cfg_DibRx(state, 5, 5, 0, 0, 0, 0, 0);
			state->input_mode_mpeg = 0;
			अवरोध;
	पूर्ण

	dib8000_set_भागersity_in(state->fe[0], onoff);
	वापस 0;
पूर्ण

अटल पूर्णांक dib8096p_set_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 outreg, smo_mode, fअगरo_threshold;
	u8 prefer_mpeg_mux_use = 1;
	पूर्णांक ret = 0;

	state->output_mode = mode;
	dib8096p_host_bus_drive(state, 1);

	fअगरo_threshold = 1792;
	smo_mode = (dib8000_पढ़ो_word(state, 299) & 0x0050) | (1 << 1);
	outreg   = dib8000_पढ़ो_word(state, 1286) &
		~((1 << 10) | (0x7 << 6) | (1 << 1));

	चयन (mode) अणु
	हाल OUTMODE_HIGH_Z:
			outreg = 0;
			अवरोध;

	हाल OUTMODE_MPEG2_SERIAL:
			अगर (prefer_mpeg_mux_use) अणु
				dprपूर्णांकk("dib8096P setting output mode TS_SERIAL using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 3, 1, 1);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			पूर्ण अन्यथा अणु/* Use Smooth block */
				dprपूर्णांकk("dib8096P setting output mode TS_SERIAL using Smooth bloc\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outreg |= (2 << 6) | (0 << 1);
			पूर्ण
			अवरोध;

	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
			अगर (prefer_mpeg_mux_use) अणु
				dprपूर्णांकk("dib8096P setting output mode TS_PARALLEL_GATED using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 2, 0, 0);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			पूर्ण अन्यथा अणु /* Use Smooth block */
				dprपूर्णांकk("dib8096P setting output mode TS_PARALLEL_GATED using Smooth block\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outreg |= (0 << 6);
			पूर्ण
			अवरोध;

	हाल OUTMODE_MPEG2_PAR_CONT_CLK: /* Using Smooth block only */
			dprपूर्णांकk("dib8096P setting output mode TS_PARALLEL_CONT using Smooth block\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (1 << 6);
			अवरोध;

	हाल OUTMODE_MPEG2_FIFO:
			/* Using Smooth block because not supported
			   by new Mpeg Mux bloc */
			dprपूर्णांकk("dib8096P setting output mode TS_FIFO using Smooth block\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (5 << 6);
			smo_mode |= (3 << 1);
			fअगरo_threshold = 512;
			अवरोध;

	हाल OUTMODE_DIVERSITY:
			dprपूर्णांकk("dib8096P setting output mode MODE_DIVERSITY\n");
			dib8096p_setDibTxMux(state, DIV_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			अवरोध;

	हाल OUTMODE_ANALOG_ADC:
			dprपूर्णांकk("dib8096P setting output mode MODE_ANALOG_ADC\n");
			dib8096p_setDibTxMux(state, ADC_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			अवरोध;
	पूर्ण

	अगर (mode != OUTMODE_HIGH_Z)
		outreg |= (1<<10);

	dprपूर्णांकk("output_mpeg2_in_188_bytes = %d\n",
			state->cfg.output_mpeg2_in_188_bytes);
	अगर (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	ret |= dib8000_ग_लिखो_word(state, 299, smo_mode);
	/* synchronous ख_पढ़ो */
	ret |= dib8000_ग_लिखो_word(state, 299 + 1, fअगरo_threshold);
	ret |= dib8000_ग_लिखो_word(state, 1286, outreg);

	वापस ret;
पूर्ण

अटल पूर्णांक map_addr_to_serpar_number(काष्ठा i2c_msg *msg)
अणु
	अगर (msg->buf[0] <= 15)
		msg->buf[0] -= 1;
	अन्यथा अगर (msg->buf[0] == 17)
		msg->buf[0] = 15;
	अन्यथा अगर (msg->buf[0] == 16)
		msg->buf[0] = 17;
	अन्यथा अगर (msg->buf[0] == 19)
		msg->buf[0] = 16;
	अन्यथा अगर (msg->buf[0] >= 21 && msg->buf[0] <= 25)
		msg->buf[0] -= 3;
	अन्यथा अगर (msg->buf[0] == 28)
		msg->buf[0] = 23;
	अन्यथा अगर (msg->buf[0] == 99)
		msg->buf[0] = 99;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक dib8096p_tuner_ग_लिखो_serpar(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_overflow = 1;
	u16 i = 1000;
	u16 serpar_num = msg[0].buf[0];

	जबतक (n_overflow == 1 && i) अणु
		n_overflow = (dib8000_पढ़ो_word(state, 1984) >> 1) & 0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("Tuner ITF: write busy (overflow)\n");
	पूर्ण
	dib8000_ग_लिखो_word(state, 1985, (1 << 6) | (serpar_num & 0x3f));
	dib8000_ग_लिखो_word(state, 1986, (msg[0].buf[1] << 8) | msg[0].buf[2]);

	वापस num;
पूर्ण

अटल पूर्णांक dib8096p_tuner_पढ़ो_serpar(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_overflow = 1, n_empty = 1;
	u16 i = 1000;
	u16 serpar_num = msg[0].buf[0];
	u16 पढ़ो_word;

	जबतक (n_overflow == 1 && i) अणु
		n_overflow = (dib8000_पढ़ो_word(state, 1984) >> 1) & 0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("TunerITF: read busy (overflow)\n");
	पूर्ण
	dib8000_ग_लिखो_word(state, 1985, (0<<6) | (serpar_num&0x3f));

	i = 1000;
	जबतक (n_empty == 1 && i) अणु
		n_empty = dib8000_पढ़ो_word(state, 1984)&0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("TunerITF: read busy (empty)\n");
	पूर्ण

	पढ़ो_word = dib8000_पढ़ो_word(state, 1987);
	msg[1].buf[0] = (पढ़ो_word >> 8) & 0xff;
	msg[1].buf[1] = (पढ़ो_word) & 0xff;

	वापस num;
पूर्ण

अटल पूर्णांक dib8096p_tuner_rw_serpar(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	अगर (map_addr_to_serpar_number(&msg[0]) == 0) अणु
		अगर (num == 1) /* ग_लिखो */
			वापस dib8096p_tuner_ग_लिखो_serpar(i2c_adap, msg, 1);
		अन्यथा /* पढ़ो */
			वापस dib8096p_tuner_पढ़ो_serpar(i2c_adap, msg, 2);
	पूर्ण
	वापस num;
पूर्ण

अटल पूर्णांक dib8096p_rw_on_apb(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num, u16 apb_address)
अणु
	काष्ठा dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u16 word;

	अगर (num == 1) अणु		/* ग_लिखो */
		dib8000_ग_लिखो_word(state, apb_address,
				((msg[0].buf[1] << 8) | (msg[0].buf[2])));
	पूर्ण अन्यथा अणु
		word = dib8000_पढ़ो_word(state, apb_address);
		msg[1].buf[0] = (word >> 8) & 0xff;
		msg[1].buf[1] = (word) & 0xff;
	पूर्ण
	वापस num;
पूर्ण

अटल पूर्णांक dib8096p_tuner_xfer(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u16 apb_address = 0, word;
	पूर्णांक i = 0;

	चयन (msg[0].buf[0]) अणु
	हाल 0x12:
			apb_address = 1920;
			अवरोध;
	हाल 0x14:
			apb_address = 1921;
			अवरोध;
	हाल 0x24:
			apb_address = 1922;
			अवरोध;
	हाल 0x1a:
			apb_address = 1923;
			अवरोध;
	हाल 0x22:
			apb_address = 1924;
			अवरोध;
	हाल 0x33:
			apb_address = 1926;
			अवरोध;
	हाल 0x34:
			apb_address = 1927;
			अवरोध;
	हाल 0x35:
			apb_address = 1928;
			अवरोध;
	हाल 0x36:
			apb_address = 1929;
			अवरोध;
	हाल 0x37:
			apb_address = 1930;
			अवरोध;
	हाल 0x38:
			apb_address = 1931;
			अवरोध;
	हाल 0x39:
			apb_address = 1932;
			अवरोध;
	हाल 0x2a:
			apb_address = 1935;
			अवरोध;
	हाल 0x2b:
			apb_address = 1936;
			अवरोध;
	हाल 0x2c:
			apb_address = 1937;
			अवरोध;
	हाल 0x2d:
			apb_address = 1938;
			अवरोध;
	हाल 0x2e:
			apb_address = 1939;
			अवरोध;
	हाल 0x2f:
			apb_address = 1940;
			अवरोध;
	हाल 0x30:
			apb_address = 1941;
			अवरोध;
	हाल 0x31:
			apb_address = 1942;
			अवरोध;
	हाल 0x32:
			apb_address = 1943;
			अवरोध;
	हाल 0x3e:
			apb_address = 1944;
			अवरोध;
	हाल 0x3f:
			apb_address = 1945;
			अवरोध;
	हाल 0x40:
			apb_address = 1948;
			अवरोध;
	हाल 0x25:
			apb_address = 936;
			अवरोध;
	हाल 0x26:
			apb_address = 937;
			अवरोध;
	हाल 0x27:
			apb_address = 938;
			अवरोध;
	हाल 0x28:
			apb_address = 939;
			अवरोध;
	हाल 0x1d:
			/* get sad sel request */
			i = ((dib8000_पढ़ो_word(state, 921) >> 12)&0x3);
			word = dib8000_पढ़ो_word(state, 924+i);
			msg[1].buf[0] = (word >> 8) & 0xff;
			msg[1].buf[1] = (word) & 0xff;
			वापस num;
	हाल 0x1f:
			अगर (num == 1) अणु	/* ग_लिखो */
				word = (u16) ((msg[0].buf[1] << 8) |
						msg[0].buf[2]);
				/* in the VGAMODE Sel are located on bit 0/1 */
				word &= 0x3;
				word = (dib8000_पढ़ो_word(state, 921) &
						~(3<<12)) | (word<<12);
				/* Set the proper input */
				dib8000_ग_लिखो_word(state, 921, word);
				वापस num;
			पूर्ण
	पूर्ण

	अगर (apb_address != 0) /* R/W access via APB */
		वापस dib8096p_rw_on_apb(i2c_adap, msg, num, apb_address);
	अन्यथा  /* R/W access via SERPAR  */
		वापस dib8096p_tuner_rw_serpar(i2c_adap, msg, num);

	वापस 0;
पूर्ण

अटल u32 dib8096p_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dib8096p_tuner_xfer_algo = अणु
	.master_xfer = dib8096p_tuner_xfer,
	.functionality = dib8096p_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter *dib8096p_get_i2c_tuner(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *st = fe->demodulator_priv;
	वापस &st->dib8096p_tuner_adap;
पूर्ण

अटल पूर्णांक dib8096p_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 en_cur_state;

	dprपूर्णांकk("sleep dib8096p: %d\n", onoff);

	en_cur_state = dib8000_पढ़ो_word(state, 1922);

	/* LNAs and MIX are ON and thereक्रमe it is a valid configuration */
	अगर (en_cur_state > 0xff)
		state->tuner_enable = en_cur_state ;

	अगर (onoff)
		en_cur_state &= 0x00ff;
	अन्यथा अणु
		अगर (state->tuner_enable != 0)
			en_cur_state = state->tuner_enable;
	पूर्ण

	dib8000_ग_लिखो_word(state, 1922, en_cur_state);

	वापस 0;
पूर्ण

अटल स्थिर s32 lut_1000ln_mant[] =
अणु
	908, 7003, 7090, 7170, 7244, 7313, 7377, 7438, 7495, 7549, 7600
पूर्ण;

अटल s32 dib8000_get_adc_घातer(काष्ठा dvb_frontend *fe, u8 mode)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u32 ix = 0, पंचांगp_val = 0, exp = 0, mant = 0;
	s32 val;

	val = dib8000_पढ़ो32(state, 384);
	अगर (mode) अणु
		पंचांगp_val = val;
		जबतक (पंचांगp_val >>= 1)
			exp++;
		mant = (val * 1000 / (1<<exp));
		ix = (u8)((mant-1000)/100); /* index of the LUT */
		val = (lut_1000ln_mant[ix] + 693*(exp-20) - 6908);
		val = (val*256)/1000;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक dib8090p_get_dc_घातer(काष्ठा dvb_frontend *fe, u8 IQ)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	पूर्णांक val = 0;

	चयन (IQ) अणु
	हाल 1:
			val = dib8000_पढ़ो_word(state, 403);
			अवरोध;
	हाल 0:
			val = dib8000_पढ़ो_word(state, 404);
			अवरोध;
	पूर्ण
	अगर (val  & 0x200)
		val -= 1024;

	वापस val;
पूर्ण

अटल व्योम dib8000_update_timf(काष्ठा dib8000_state *state)
अणु
	u32 timf = state->timf = dib8000_पढ़ो32(state, 435);

	dib8000_ग_लिखो_word(state, 29, (u16) (timf >> 16));
	dib8000_ग_लिखो_word(state, 30, (u16) (timf & 0xffff));
	dprपूर्णांकk("Updated timing frequency: %d (default: %d)\n", state->timf, state->timf_शेष);
पूर्ण

अटल u32 dib8000_ctrl_timf(काष्ठा dvb_frontend *fe, uपूर्णांक8_t op, uपूर्णांक32_t timf)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	चयन (op) अणु
	हाल DEMOD_TIMF_SET:
			state->timf = timf;
			अवरोध;
	हाल DEMOD_TIMF_UPDATE:
			dib8000_update_timf(state);
			अवरोध;
	हाल DEMOD_TIMF_GET:
			अवरोध;
	पूर्ण
	dib8000_set_bandwidth(state->fe[0], 6000);

	वापस state->timf;
पूर्ण

अटल स्थिर u16 adc_target_16dB[11] = अणु
	7250, 7238, 7264, 7309, 7338, 7382, 7427, 7456, 7500, 7544, 7574
पूर्ण;

अटल स्थिर u8 permu_seg[] = अणु 6, 5, 7, 4, 8, 3, 9, 2, 10, 1, 11, 0, 12 पूर्ण;

अटल u16 dib8000_set_layer(काष्ठा dib8000_state *state, u8 layer_index, u16 max_स्थिरellation)
अणु
	u8  cr, स्थिरellation, समय_पूर्णांकlv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;

	चयन (c->layer[layer_index].modulation) अणु
	हाल DQPSK:
			स्थिरellation = 0;
			अवरोध;
	हाल  QPSK:
			स्थिरellation = 1;
			अवरोध;
	हाल QAM_16:
			स्थिरellation = 2;
			अवरोध;
	हाल QAM_64:
	शेष:
			स्थिरellation = 3;
			अवरोध;
	पूर्ण

	चयन (c->layer[layer_index].fec) अणु
	हाल FEC_1_2:
			cr = 1;
			अवरोध;
	हाल FEC_2_3:
			cr = 2;
			अवरोध;
	हाल FEC_3_4:
			cr = 3;
			अवरोध;
	हाल FEC_5_6:
			cr = 5;
			अवरोध;
	हाल FEC_7_8:
	शेष:
			cr = 7;
			अवरोध;
	पूर्ण

	समय_पूर्णांकlv = fls(c->layer[layer_index].पूर्णांकerleaving);
	अगर (समय_पूर्णांकlv > 3 && !(समय_पूर्णांकlv == 4 && c->isdbt_sb_mode == 1))
		समय_पूर्णांकlv = 0;

	dib8000_ग_लिखो_word(state, 2 + layer_index, (स्थिरellation << 10) | ((c->layer[layer_index].segment_count & 0xf) << 6) | (cr << 3) | समय_पूर्णांकlv);
	अगर (c->layer[layer_index].segment_count > 0) अणु
		चयन (max_स्थिरellation) अणु
		हाल DQPSK:
		हाल QPSK:
				अगर (c->layer[layer_index].modulation == QAM_16 || c->layer[layer_index].modulation == QAM_64)
					max_स्थिरellation = c->layer[layer_index].modulation;
				अवरोध;
		हाल QAM_16:
				अगर (c->layer[layer_index].modulation == QAM_64)
					max_स्थिरellation = c->layer[layer_index].modulation;
				अवरोध;
		पूर्ण
	पूर्ण

	वापस  max_स्थिरellation;
पूर्ण

अटल स्थिर u16 adp_Q64[4] = अणु0x0148, 0xfff0, 0x00a4, 0xfff8पूर्ण; /* P_adp_regul_cnt 0.04, P_adp_noise_cnt -0.002, P_adp_regul_ext 0.02, P_adp_noise_ext -0.001 */
अटल स्थिर u16 adp_Q16[4] = अणु0x023d, 0xffdf, 0x00a4, 0xfff0पूर्ण; /* P_adp_regul_cnt 0.07, P_adp_noise_cnt -0.004, P_adp_regul_ext 0.02, P_adp_noise_ext -0.002 */
अटल स्थिर u16 adp_Qशेष[4] = अणु0x099a, 0xffae, 0x0333, 0xfff8पूर्ण; /* P_adp_regul_cnt 0.3,  P_adp_noise_cnt -0.01,  P_adp_regul_ext 0.1,  P_adp_noise_ext -0.002 */
अटल u16 dib8000_adp_fine_tune(काष्ठा dib8000_state *state, u16 max_स्थिरellation)
अणु
	u16 i, ana_gain = 0;
	स्थिर u16 *adp;

	/* channel estimation fine configuration */
	चयन (max_स्थिरellation) अणु
	हाल QAM_64:
			ana_gain = 0x7;
			adp = &adp_Q64[0];
			अवरोध;
	हाल QAM_16:
			ana_gain = 0x7;
			adp = &adp_Q16[0];
			अवरोध;
	शेष:
			ana_gain = 0;
			adp = &adp_Qशेष[0];
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		dib8000_ग_लिखो_word(state, 215 + i, adp[i]);

	वापस ana_gain;
पूर्ण

अटल व्योम dib8000_update_ana_gain(काष्ठा dib8000_state *state, u16 ana_gain)
अणु
	u16 i;

	dib8000_ग_लिखो_word(state, 116, ana_gain);

	/* update ADC target depending on ana_gain */
	अगर (ana_gain) अणु /* set -16dB ADC target क्रम ana_gain=-1 */
		क्रम (i = 0; i < 10; i++)
			dib8000_ग_लिखो_word(state, 80 + i, adc_target_16dB[i]);
	पूर्ण अन्यथा अणु /* set -22dB ADC target क्रम ana_gain=0 */
		क्रम (i = 0; i < 10; i++)
			dib8000_ग_लिखो_word(state, 80 + i, adc_target_16dB[i] - 355);
	पूर्ण
पूर्ण

अटल व्योम dib8000_load_ana_fe_coefs(काष्ठा dib8000_state *state, स्थिर s16 *ana_fe)
अणु
	u16 mode = 0;

	अगर (state->isdbt_cfg_loaded == 0)
		क्रम (mode = 0; mode < 24; mode++)
			dib8000_ग_लिखो_word(state, 117 + mode, ana_fe[mode]);
पूर्ण

अटल स्थिर u16 lut_prbs_2k[14] = अणु
	0, 0x423, 0x009, 0x5C7, 0x7A6, 0x3D8, 0x527, 0x7FF, 0x79B, 0x3D6, 0x3A2, 0x53B, 0x2F4, 0x213
पूर्ण;
अटल स्थिर u16 lut_prbs_4k[14] = अणु
	0, 0x208, 0x0C3, 0x7B9, 0x423, 0x5C7, 0x3D8, 0x7FF, 0x3D6, 0x53B, 0x213, 0x029, 0x0D0, 0x48E
पूर्ण;
अटल स्थिर u16 lut_prbs_8k[14] = अणु
	0, 0x740, 0x069, 0x7DD, 0x208, 0x7B9, 0x5C7, 0x7FF, 0x53B, 0x029, 0x48E, 0x4C4, 0x367, 0x684
पूर्ण;

अटल u16 dib8000_get_init_prbs(काष्ठा dib8000_state *state, u16 subchannel)
अणु
	पूर्णांक sub_channel_prbs_group = 0;

	sub_channel_prbs_group = (subchannel / 3) + 1;
	dprपूर्णांकk("sub_channel_prbs_group = %d , subchannel =%d prbs = 0x%04x\n", sub_channel_prbs_group, subchannel, lut_prbs_8k[sub_channel_prbs_group]);

	चयन (state->fe[0]->dtv_property_cache.transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
			वापस lut_prbs_2k[sub_channel_prbs_group];
	हाल TRANSMISSION_MODE_4K:
			वापस lut_prbs_4k[sub_channel_prbs_group];
	शेष:
	हाल TRANSMISSION_MODE_8K:
			वापस lut_prbs_8k[sub_channel_prbs_group];
	पूर्ण
पूर्ण

अटल व्योम dib8000_set_13seg_channel(काष्ठा dib8000_state *state)
अणु
	u16 i;
	u16 coff_घात = 0x2800;

	state->seg_mask = 0x1fff; /* All 13 segments enabled */

	/* ---- COFF ---- Carloff, the most robust --- */
	अगर (state->isdbt_cfg_loaded == 0) अणु  /* अगर not Sound Broadcasting mode : put शेष values क्रम 13 segments */
		dib8000_ग_लिखो_word(state, 180, (16 << 6) | 9);
		dib8000_ग_लिखो_word(state, 187, (4 << 12) | (8 << 5) | 0x2);
		coff_घात = 0x2800;
		क्रम (i = 0; i < 6; i++)
			dib8000_ग_लिखो_word(state, 181+i, coff_घात);

		/* P_ctrl_corm_thres4pre_freq_inh=1, P_ctrl_pre_freq_mode_sat=1 */
		/* P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 3, P_pre_freq_win_len=1 */
		dib8000_ग_लिखो_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (3 << 5) | 1);

		/* P_ctrl_pre_freq_win_len=8, P_ctrl_pre_freq_thres_lockin=6 */
		dib8000_ग_लिखो_word(state, 340, (8 << 6) | (6 << 0));
		/* P_ctrl_pre_freq_thres_lockout=4, P_small_use_पंचांगcc/ac/cp=1 */
		dib8000_ग_लिखो_word(state, 341, (4 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

		dib8000_ग_लिखो_word(state, 228, 0);  /* शेष value */
		dib8000_ग_लिखो_word(state, 265, 31); /* शेष value */
		dib8000_ग_लिखो_word(state, 205, 0x200f); /* init value */
	पूर्ण

	/*
	 * make the cpil_coff_lock more robust but slower p_coff_winlen
	 * 6bits; p_coff_thres_lock 6bits (क्रम coff lock अगर needed)
	 */

	अगर (state->cfg.pll->अगरreq == 0)
		dib8000_ग_लिखो_word(state, 266, ~state->seg_mask | state->seg_dअगरf_mask | 0x40); /* P_equal_noise_seg_inh */

	dib8000_load_ana_fe_coefs(state, ana_fe_coeff_13seg);
पूर्ण

अटल व्योम dib8000_set_subchannel_prbs(काष्ठा dib8000_state *state, u16 init_prbs)
अणु
	u16 reg_1;

	reg_1 = dib8000_पढ़ो_word(state, 1);
	dib8000_ग_लिखो_word(state, 1, (init_prbs << 2) | (reg_1 & 0x3)); /* ADDR 1 */
पूर्ण

अटल व्योम dib8000_small_fine_tune(काष्ठा dib8000_state *state)
अणु
	u16 i;
	स्थिर s16 *ncoeff;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;

	dib8000_ग_लिखो_word(state, 352, state->seg_dअगरf_mask);
	dib8000_ग_लिखो_word(state, 353, state->seg_mask);

	/* P_small_coef_ext_enable=ISDB-Tsb, P_small_narrow_band=ISDB-Tsb, P_small_last_seg=13, P_small_offset_num_car=5 */
	dib8000_ग_लिखो_word(state, 351, (c->isdbt_sb_mode << 9) | (c->isdbt_sb_mode << 8) | (13 << 4) | 5);

	अगर (c->isdbt_sb_mode) अणु
		/* ---- SMALL ---- */
		चयन (c->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K:
				अगर (c->isdbt_partial_reception == 0) अणु /* 1-seg */
					अगर (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_2k_sb_1seg_dqpsk;
					अन्यथा /* QPSK or QAM */
						ncoeff = coeff_2k_sb_1seg;
				पूर्ण अन्यथा अणु /* 3-segments */
					अगर (c->layer[0].modulation == DQPSK) अणु /* DQPSK on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk;
					पूर्ण अन्यथा अणु /* QPSK or QAM on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_2k_sb_3seg_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_2k_sb_3seg;
					पूर्ण
				पूर्ण
				अवरोध;
		हाल TRANSMISSION_MODE_4K:
				अगर (c->isdbt_partial_reception == 0) अणु /* 1-seg */
					अगर (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_4k_sb_1seg_dqpsk;
					अन्यथा /* QPSK or QAM */
						ncoeff = coeff_4k_sb_1seg;
				पूर्ण अन्यथा अणु /* 3-segments */
					अगर (c->layer[0].modulation == DQPSK) अणु /* DQPSK on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk;
					पूर्ण अन्यथा अणु /* QPSK or QAM on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_4k_sb_3seg_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_4k_sb_3seg;
					पूर्ण
				पूर्ण
				अवरोध;
		हाल TRANSMISSION_MODE_AUTO:
		हाल TRANSMISSION_MODE_8K:
		शेष:
				अगर (c->isdbt_partial_reception == 0) अणु /* 1-seg */
					अगर (c->layer[0].modulation == DQPSK) /* DQPSK */
						ncoeff = coeff_8k_sb_1seg_dqpsk;
					अन्यथा /* QPSK or QAM */
						ncoeff = coeff_8k_sb_1seg;
				पूर्ण अन्यथा अणु /* 3-segments */
					अगर (c->layer[0].modulation == DQPSK) अणु /* DQPSK on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk;
					पूर्ण अन्यथा अणु /* QPSK or QAM on central segment */
						अगर (c->layer[1].modulation == DQPSK) /* DQPSK on बाह्यal segments */
							ncoeff = coeff_8k_sb_3seg_1dqpsk;
						अन्यथा /* QPSK or QAM on बाह्यal segments */
							ncoeff = coeff_8k_sb_3seg;
					पूर्ण
				पूर्ण
				अवरोध;
		पूर्ण

		क्रम (i = 0; i < 8; i++)
			dib8000_ग_लिखो_word(state, 343 + i, ncoeff[i]);
	पूर्ण
पूर्ण

अटल स्थिर u16 coff_thres_1seg[3] = अणु300, 150, 80पूर्ण;
अटल स्थिर u16 coff_thres_3seg[3] = अणु350, 300, 250पूर्ण;
अटल व्योम dib8000_set_sb_channel(काष्ठा dib8000_state *state)
अणु
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	स्थिर u16 *coff;
	u16 i;

	अगर (c->transmission_mode == TRANSMISSION_MODE_2K || c->transmission_mode == TRANSMISSION_MODE_4K) अणु
		dib8000_ग_लिखो_word(state, 219, dib8000_पढ़ो_word(state, 219) | 0x1); /* adp_pass =1 */
		dib8000_ग_लिखो_word(state, 190, dib8000_पढ़ो_word(state, 190) | (0x1 << 14)); /* pha3_क्रमce_pha_shअगरt = 1 */
	पूर्ण अन्यथा अणु
		dib8000_ग_लिखो_word(state, 219, dib8000_पढ़ो_word(state, 219) & 0xfffe); /* adp_pass =0 */
		dib8000_ग_लिखो_word(state, 190, dib8000_पढ़ो_word(state, 190) & 0xbfff); /* pha3_क्रमce_pha_shअगरt = 0 */
	पूर्ण

	अगर (c->isdbt_partial_reception == 1) /* 3-segments */
		state->seg_mask = 0x00E0;
	अन्यथा /* 1-segment */
		state->seg_mask = 0x0040;

	dib8000_ग_लिखो_word(state, 268, (dib8000_पढ़ो_word(state, 268) & 0xF9FF) | 0x0200);

	/* ---- COFF ---- Carloff, the most robust --- */
	/* P_coff_cpil_alpha=4, P_coff_inh=0, P_coff_cpil_winlen=64, P_coff_narrow_band=1, P_coff_square_val=1, P_coff_one_seg=~partial_rcpt, P_coff_use_पंचांगcc=1, P_coff_use_ac=1 */
	dib8000_ग_लिखो_word(state, 187, (4 << 12) | (0 << 11) | (63 << 5) | (0x3 << 3) | ((~c->isdbt_partial_reception & 1) << 2) | 0x3);

	dib8000_ग_लिखो_word(state, 340, (16 << 6) | (8 << 0)); /* P_ctrl_pre_freq_win_len=16, P_ctrl_pre_freq_thres_lockin=8 */
	dib8000_ग_लिखो_word(state, 341, (6 << 3) | (1 << 2) | (1 << 1) | (1 << 0));/* P_ctrl_pre_freq_thres_lockout=6, P_small_use_पंचांगcc/ac/cp=1 */

	/* Sound Broadcasting mode 1 seg */
	अगर (c->isdbt_partial_reception == 0) अणु
		/* P_coff_winlen=63, P_coff_thres_lock=15, P_coff_one_seg_width = (P_mode == 3) , P_coff_one_seg_sym = (P_mode-1) */
		अगर (state->mode == 3)
			dib8000_ग_लिखो_word(state, 180, 0x1fcf | ((state->mode - 1) << 14));
		अन्यथा
			dib8000_ग_लिखो_word(state, 180, 0x0fcf | ((state->mode - 1) << 14));

		/* P_ctrl_corm_thres4pre_freq_inh=1,P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 5, P_pre_freq_win_len=4 */
		dib8000_ग_लिखो_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (5 << 5) | 4);
		coff = &coff_thres_1seg[0];
	पूर्ण अन्यथा अणु   /* Sound Broadcasting mode 3 seg */
		dib8000_ग_लिखो_word(state, 180, 0x1fcf | (1 << 14));
		/* P_ctrl_corm_thres4pre_freq_inh = 1, P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 4, P_pre_freq_win_len=4 */
		dib8000_ग_लिखो_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (4 << 5) | 4);
		coff = &coff_thres_3seg[0];
	पूर्ण

	dib8000_ग_लिखो_word(state, 228, 1); /* P_2d_mode_byp=1 */
	dib8000_ग_लिखो_word(state, 205, dib8000_पढ़ो_word(state, 205) & 0xfff0); /* P_cspu_win_cut = 0 */

	अगर (c->isdbt_partial_reception == 0 && c->transmission_mode == TRANSMISSION_MODE_2K)
		dib8000_ग_लिखो_word(state, 265, 15); /* P_equal_noise_sel = 15 */

	/* Write COFF thres */
	क्रम (i = 0 ; i < 3; i++) अणु
		dib8000_ग_लिखो_word(state, 181+i, coff[i]);
		dib8000_ग_लिखो_word(state, 184+i, coff[i]);
	पूर्ण

	/*
	 * make the cpil_coff_lock more robust but slower p_coff_winlen
	 * 6bits; p_coff_thres_lock 6bits (क्रम coff lock अगर needed)
	 */

	dib8000_ग_लिखो_word(state, 266, ~state->seg_mask | state->seg_dअगरf_mask); /* P_equal_noise_seg_inh */

	अगर (c->isdbt_partial_reception == 0)
		dib8000_ग_लिखो_word(state, 178, 64); /* P_fft_घातrange = 64 */
	अन्यथा
		dib8000_ग_लिखो_word(state, 178, 32); /* P_fft_घातrange = 32 */
पूर्ण

अटल व्योम dib8000_set_isdbt_common_channel(काष्ठा dib8000_state *state, u8 seq, u8 स्वतःsearching)
अणु
	u16 p_cfr_left_edge  = 0, p_cfr_right_edge = 0;
	u16 पंचांगcc_घात = 0, ana_gain = 0, पंचांगp = 0, i = 0, nbseg_dअगरf = 0 ;
	u16 max_स्थिरellation = DQPSK;
	पूर्णांक init_prbs;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;

	अगर (स्वतःsearching)
		c->isdbt_partial_reception = 1;

	/* P_mode */
	dib8000_ग_लिखो_word(state, 10, (seq << 4));

	/* init mode */
	state->mode = fft_to_mode(state);

	/* set guard */
	पंचांगp = dib8000_पढ़ो_word(state, 1);
	dib8000_ग_लिखो_word(state, 1, (पंचांगp&0xfffc) | (c->guard_पूर्णांकerval & 0x3));

	dib8000_ग_लिखो_word(state, 274, (dib8000_पढ़ो_word(state, 274) & 0xffcf) | ((c->isdbt_partial_reception & 1) << 5) | ((c->isdbt_sb_mode & 1) << 4));

	/* संकेत optimization parameter */
	अगर (c->isdbt_partial_reception) अणु
		state->seg_dअगरf_mask = (c->layer[0].modulation == DQPSK) << permu_seg[0];
		क्रम (i = 1; i < 3; i++)
			nbseg_dअगरf += (c->layer[i].modulation == DQPSK) * c->layer[i].segment_count;
		क्रम (i = 0; i < nbseg_dअगरf; i++)
			state->seg_dअगरf_mask |= 1 << permu_seg[i+1];
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 3; i++)
			nbseg_dअगरf += (c->layer[i].modulation == DQPSK) * c->layer[i].segment_count;
		क्रम (i = 0; i < nbseg_dअगरf; i++)
			state->seg_dअगरf_mask |= 1 << permu_seg[i];
	पूर्ण

	अगर (state->seg_dअगरf_mask)
		dib8000_ग_लिखो_word(state, 268, (dib8000_पढ़ो_word(state, 268) & 0xF9FF) | 0x0200);
	अन्यथा
		dib8000_ग_लिखो_word(state, 268, (2 << 9) | 39); /*init value */

	क्रम (i = 0; i < 3; i++)
		max_स्थिरellation = dib8000_set_layer(state, i, max_स्थिरellation);
	अगर (स्वतःsearching == 0) अणु
		state->layer_b_nb_seg = c->layer[1].segment_count;
		state->layer_c_nb_seg = c->layer[2].segment_count;
	पूर्ण

	/* WRITE: Mode & Dअगरf mask */
	dib8000_ग_लिखो_word(state, 0, (state->mode << 13) | state->seg_dअगरf_mask);

	state->dअगरferential_स्थिरellation = (state->seg_dअगरf_mask != 0);

	/* channel estimation fine configuration */
	ana_gain = dib8000_adp_fine_tune(state, max_स्थिरellation);

	/* update ana_gain depending on max स्थिरellation */
	dib8000_update_ana_gain(state, ana_gain);

	/* ---- ANA_FE ---- */
	अगर (c->isdbt_partial_reception) /* 3-segments */
		dib8000_load_ana_fe_coefs(state, ana_fe_coeff_3seg);
	अन्यथा
		dib8000_load_ana_fe_coefs(state, ana_fe_coeff_1seg); /* 1-segment */

	/* TSB or ISDBT ? apply it now */
	अगर (c->isdbt_sb_mode) अणु
		dib8000_set_sb_channel(state);
		अगर (c->isdbt_sb_subchannel < 14)
			init_prbs = dib8000_get_init_prbs(state, c->isdbt_sb_subchannel);
		अन्यथा
			init_prbs = 0;
	पूर्ण अन्यथा अणु
		dib8000_set_13seg_channel(state);
		init_prbs = 0xfff;
	पूर्ण

	/* SMALL */
	dib8000_small_fine_tune(state);

	dib8000_set_subchannel_prbs(state, init_prbs);

	/* ---- CHAN_BLK ---- */
	क्रम (i = 0; i < 13; i++) अणु
		अगर ((((~state->seg_dअगरf_mask) >> i) & 1) == 1) अणु
			p_cfr_left_edge  += (1 << i) * ((i == 0) || ((((state->seg_mask & (~state->seg_dअगरf_mask)) >> (i - 1)) & 1) == 0));
			p_cfr_right_edge += (1 << i) * ((i == 12) || ((((state->seg_mask & (~state->seg_dअगरf_mask)) >> (i + 1)) & 1) == 0));
		पूर्ण
	पूर्ण
	dib8000_ग_लिखो_word(state, 222, p_cfr_left_edge); /* p_cfr_left_edge */
	dib8000_ग_लिखो_word(state, 223, p_cfr_right_edge); /* p_cfr_right_edge */
	/* "P_cspu_left_edge" & "P_cspu_right_edge" not used => करो not care */

	dib8000_ग_लिखो_word(state, 189, ~state->seg_mask | state->seg_dअगरf_mask); /* P_lmod4_seg_inh */
	dib8000_ग_लिखो_word(state, 192, ~state->seg_mask | state->seg_dअगरf_mask); /* P_pha3_seg_inh */
	dib8000_ग_लिखो_word(state, 225, ~state->seg_mask | state->seg_dअगरf_mask); /* P_tac_seg_inh */

	अगर (!स्वतःsearching)
		dib8000_ग_लिखो_word(state, 288, (~state->seg_mask | state->seg_dअगरf_mask) & 0x1fff); /* P_पंचांगcc_seg_eq_inh */
	अन्यथा
		dib8000_ग_लिखो_word(state, 288, 0x1fff); /*disable equalisation of the पंचांगcc when स्वतःsearch to be able to find the DQPSK channels. */

	dib8000_ग_लिखो_word(state, 211, state->seg_mask & (~state->seg_dअगरf_mask)); /* P_des_seg_enabled */
	dib8000_ग_लिखो_word(state, 287, ~state->seg_mask | 0x1000); /* P_पंचांगcc_seg_inh */

	dib8000_ग_लिखो_word(state, 178, 32); /* P_fft_घातrange = 32 */

	/* ---- TMCC ---- */
	क्रम (i = 0; i < 3; i++)
		पंचांगcc_घात += (((c->layer[i].modulation == DQPSK) * 4 + 1) * c->layer[i].segment_count) ;

	/* Quantअगर of "P_tmcc_dec_thres_?k" is (0, 5+mode, 9); */
	/* Threshold is set at 1/4 of max घातer. */
	पंचांगcc_घात *= (1 << (9-2));
	dib8000_ग_लिखो_word(state, 290, पंचांगcc_घात); /* P_पंचांगcc_dec_thres_2k */
	dib8000_ग_लिखो_word(state, 291, पंचांगcc_घात); /* P_पंचांगcc_dec_thres_4k */
	dib8000_ग_लिखो_word(state, 292, पंचांगcc_घात); /* P_पंचांगcc_dec_thres_8k */
	/*dib8000_ग_लिखो_word(state, 287, (1 << 13) | 0x1000 ); */

	/* ---- PHA3 ---- */
	अगर (state->isdbt_cfg_loaded == 0)
		dib8000_ग_लिखो_word(state, 250, 3285); /* p_2d_hspeed_thr0 */

	state->isdbt_cfg_loaded = 0;
पूर्ण

अटल u32 dib8000_रुको_lock(काष्ठा dib8000_state *state, u32 पूर्णांकernal,
			     u32 रुको0_ms, u32 रुको1_ms, u32 रुको2_ms)
अणु
	u32 value = 0;	/* P_search_end0 रुको समय */
	u16 reg = 11;	/* P_search_end0 start addr */

	क्रम (reg = 11; reg < 16; reg += 2) अणु
		अगर (reg == 11) अणु
			अगर (state->revision == 0x8090)
				value = पूर्णांकernal * रुको1_ms;
			अन्यथा
				value = पूर्णांकernal * रुको0_ms;
		पूर्ण अन्यथा अगर (reg == 13)
			value = पूर्णांकernal * रुको1_ms;
		अन्यथा अगर (reg == 15)
			value = पूर्णांकernal * रुको2_ms;
		dib8000_ग_लिखो_word(state, reg, (u16)((value >> 16) & 0xffff));
		dib8000_ग_लिखो_word(state, (reg + 1), (u16)(value & 0xffff));
	पूर्ण
	वापस value;
पूर्ण

अटल पूर्णांक dib8000_स्वतःsearch_start(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u8 slist = 0;
	u32 value, पूर्णांकernal = state->cfg.pll->पूर्णांकernal;

	अगर (state->revision == 0x8090)
		पूर्णांकernal = dib8000_पढ़ो32(state, 23) / 1000;

	अगर ((state->revision >= 0x8002) &&
	    (state->स्वतःsearch_state == AS_SEARCHING_FFT)) अणु
		dib8000_ग_लिखो_word(state,  37, 0x0065); /* P_ctrl_pha_off_max शेष values */
		dib8000_ग_लिखो_word(state, 116, 0x0000); /* P_ana_gain to 0 */

		dib8000_ग_लिखो_word(state, 0, (dib8000_पढ़ो_word(state, 0) & 0x1fff) | (0 << 13) | (1 << 15)); /* P_mode = 0, P_restart_search=1 */
		dib8000_ग_लिखो_word(state, 1, (dib8000_पढ़ो_word(state, 1) & 0xfffc) | 0); /* P_guard = 0 */
		dib8000_ग_लिखो_word(state, 6, 0); /* P_lock0_mask = 0 */
		dib8000_ग_लिखो_word(state, 7, 0); /* P_lock1_mask = 0 */
		dib8000_ग_लिखो_word(state, 8, 0); /* P_lock2_mask = 0 */
		dib8000_ग_लिखो_word(state, 10, (dib8000_पढ़ो_word(state, 10) & 0x200) | (16 << 4) | (0 << 0)); /* P_search_list=16, P_search_maxtrial=0 */

		अगर (state->revision == 0x8090)
			value = dib8000_रुको_lock(state, पूर्णांकernal, 10, 10, 10); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */
		अन्यथा
			value = dib8000_रुको_lock(state, पूर्णांकernal, 20, 20, 20); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */

		dib8000_ग_लिखो_word(state, 17, 0);
		dib8000_ग_लिखो_word(state, 18, 200); /* P_search_rstst = 200 */
		dib8000_ग_लिखो_word(state, 19, 0);
		dib8000_ग_लिखो_word(state, 20, 400); /* P_search_rstend = 400 */
		dib8000_ग_लिखो_word(state, 21, (value >> 16) & 0xffff); /* P_search_checkst */
		dib8000_ग_लिखो_word(state, 22, value & 0xffff);

		अगर (state->revision == 0x8090)
			dib8000_ग_लिखो_word(state, 32, (dib8000_पढ़ो_word(state, 32) & 0xf0ff) | (0 << 8)); /* P_corm_alpha = 0 */
		अन्यथा
			dib8000_ग_लिखो_word(state, 32, (dib8000_पढ़ो_word(state, 32) & 0xf0ff) | (9 << 8)); /* P_corm_alpha = 3 */
		dib8000_ग_लिखो_word(state, 355, 2); /* P_search_param_max = 2 */

		/* P_search_param_select = (1 | 1<<4 | 1 << 8) */
		dib8000_ग_लिखो_word(state, 356, 0);
		dib8000_ग_लिखो_word(state, 357, 0x111);

		dib8000_ग_लिखो_word(state, 770, (dib8000_पढ़ो_word(state, 770) & 0xdfff) | (1 << 13)); /* P_restart_ccg = 1 */
		dib8000_ग_लिखो_word(state, 770, (dib8000_पढ़ो_word(state, 770) & 0xdfff) | (0 << 13)); /* P_restart_ccg = 0 */
		dib8000_ग_लिखो_word(state, 0, (dib8000_पढ़ो_word(state, 0) & 0x7ff) | (0 << 15) | (1 << 13)); /* P_restart_search = 0; */
	पूर्ण अन्यथा अगर ((state->revision >= 0x8002) &&
		   (state->स्वतःsearch_state == AS_SEARCHING_GUARD)) अणु
		c->transmission_mode = TRANSMISSION_MODE_8K;
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		c->inversion = 0;
		c->layer[0].modulation = QAM_64;
		c->layer[0].fec = FEC_2_3;
		c->layer[0].पूर्णांकerleaving = 0;
		c->layer[0].segment_count = 13;

		slist = 16;
		c->transmission_mode = state->found_nfft;

		dib8000_set_isdbt_common_channel(state, slist, 1);

		/* set lock_mask values */
		dib8000_ग_लिखो_word(state, 6, 0x4);
		अगर (state->revision == 0x8090)
			dib8000_ग_लिखो_word(state, 7, ((1 << 12) | (1 << 11) | (1 << 10)));/* पंचांगcc_dec_lock, पंचांगcc_sync_lock, पंचांगcc_data_lock, पंचांगcc_bch_uncor */
		अन्यथा
			dib8000_ग_लिखो_word(state, 7, 0x8);
		dib8000_ग_लिखो_word(state, 8, 0x1000);

		/* set lock_mask रुको समय values */
		अगर (state->revision == 0x8090)
			dib8000_रुको_lock(state, पूर्णांकernal, 50, 100, 1000); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */
		अन्यथा
			dib8000_रुको_lock(state, पूर्णांकernal, 50, 200, 1000); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */

		dib8000_ग_लिखो_word(state, 355, 3); /* P_search_param_max = 3 */

		/* P_search_param_select = 0xf; look क्रम the 4 dअगरferent guard पूर्णांकervals */
		dib8000_ग_लिखो_word(state, 356, 0);
		dib8000_ग_लिखो_word(state, 357, 0xf);

		value = dib8000_पढ़ो_word(state, 0);
		dib8000_ग_लिखो_word(state, 0, (u16)((1 << 15) | value));
		dib8000_पढ़ो_word(state, 1284);  /* reset the INT. n_irq_pending */
		dib8000_ग_लिखो_word(state, 0, (u16)value);
	पूर्ण अन्यथा अणु
		c->inversion = 0;
		c->layer[0].modulation = QAM_64;
		c->layer[0].fec = FEC_2_3;
		c->layer[0].पूर्णांकerleaving = 0;
		c->layer[0].segment_count = 13;
		अगर (!c->isdbt_sb_mode)
			c->layer[0].segment_count = 13;

		/* choose the right list, in sb, always करो everything */
		अगर (c->isdbt_sb_mode) अणु
			slist = 7;
			dib8000_ग_लिखो_word(state, 0, (dib8000_पढ़ो_word(state, 0) & 0x9fff) | (1 << 13));
		पूर्ण अन्यथा अणु
			अगर (c->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO) अणु
				अगर (c->transmission_mode == TRANSMISSION_MODE_AUTO) अणु
					c->transmission_mode = TRANSMISSION_MODE_8K;
					c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
					slist = 7;
					dib8000_ग_लिखो_word(state, 0, (dib8000_पढ़ो_word(state, 0) & 0x9fff) | (1 << 13));  /* P_mode = 1 to have स्वतःsearch start ok with mode2 */
				पूर्ण अन्यथा अणु
					c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
					slist = 3;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (c->transmission_mode == TRANSMISSION_MODE_AUTO) अणु
					c->transmission_mode = TRANSMISSION_MODE_8K;
					slist = 2;
					dib8000_ग_लिखो_word(state, 0, (dib8000_पढ़ो_word(state, 0) & 0x9fff) | (1 << 13));  /* P_mode = 1 */
				पूर्ण अन्यथा
					slist = 0;
			पूर्ण
		पूर्ण
		dprपूर्णांकk("Using list for autosearch : %d\n", slist);

		dib8000_set_isdbt_common_channel(state, slist, 1);

		/* set lock_mask values */
		dib8000_ग_लिखो_word(state, 6, 0x4);
		अगर (state->revision == 0x8090)
			dib8000_ग_लिखो_word(state, 7, (1 << 12) | (1 << 11) | (1 << 10));
		अन्यथा
			dib8000_ग_लिखो_word(state, 7, 0x8);
		dib8000_ग_लिखो_word(state, 8, 0x1000);

		/* set lock_mask रुको समय values */
		अगर (state->revision == 0x8090)
			dib8000_रुको_lock(state, पूर्णांकernal, 50, 200, 1000); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */
		अन्यथा
			dib8000_रुको_lock(state, पूर्णांकernal, 50, 100, 1000); /* समय in ms configure P_search_end0 P_search_end1 P_search_end2 */

		value = dib8000_पढ़ो_word(state, 0);
		dib8000_ग_लिखो_word(state, 0, (u16)((1 << 15) | value));
		dib8000_पढ़ो_word(state, 1284);  /* reset the INT. n_irq_pending */
		dib8000_ग_लिखो_word(state, 0, (u16)value);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_स्वतःsearch_irq(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 irq_pending = dib8000_पढ़ो_word(state, 1284);

	अगर ((state->revision >= 0x8002) &&
	    (state->स्वतःsearch_state == AS_SEARCHING_FFT)) अणु
		अगर (irq_pending & 0x1) अणु
			dprपूर्णांकk("dib8000_autosearch_irq: max correlation result available\n");
			वापस 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (irq_pending & 0x1) अणु	/* failed */
			dprपूर्णांकk("dib8000_autosearch_irq failed\n");
			वापस 1;
		पूर्ण

		अगर (irq_pending & 0x2) अणु	/* succeeded */
			dprपूर्णांकk("dib8000_autosearch_irq succeeded\n");
			वापस 2;
		पूर्ण
	पूर्ण

	वापस 0;		// still pending
पूर्ण

अटल व्योम dib8000_viterbi_state(काष्ठा dib8000_state *state, u8 onoff)
अणु
	u16 पंचांगp;

	पंचांगp = dib8000_पढ़ो_word(state, 771);
	अगर (onoff) /* start P_restart_chd : channel_decoder */
		dib8000_ग_लिखो_word(state, 771, पंचांगp & 0xfffd);
	अन्यथा /* stop P_restart_chd : channel_decoder */
		dib8000_ग_लिखो_word(state, 771, पंचांगp | (1<<1));
पूर्ण

अटल व्योम dib8000_set_dds(काष्ठा dib8000_state *state, s32 offset_khz)
अणु
	s16 unit_khz_dds_val;
	u32 असल_offset_khz = असल(offset_khz);
	u32 dds = state->cfg.pll->अगरreq & 0x1ffffff;
	u8 invert = !!(state->cfg.pll->अगरreq & (1 << 25));
	u8 ratio;

	अगर (state->revision == 0x8090) अणु
		ratio = 4;
		unit_khz_dds_val = (1<<26) / (dib8000_पढ़ो32(state, 23) / 1000);
		अगर (offset_khz < 0)
			dds = (1 << 26) - (असल_offset_khz * unit_khz_dds_val);
		अन्यथा
			dds = (असल_offset_khz * unit_khz_dds_val);

		अगर (invert)
			dds = (1<<26) - dds;
	पूर्ण अन्यथा अणु
		ratio = 2;
		unit_khz_dds_val = (u16) (67108864 / state->cfg.pll->पूर्णांकernal);

		अगर (offset_khz < 0)
			unit_khz_dds_val *= -1;

		/* IF tuner */
		अगर (invert)
			dds -= असल_offset_khz * unit_khz_dds_val;
		अन्यथा
			dds += असल_offset_khz * unit_khz_dds_val;
	पूर्ण

	dprपूर्णांकk("setting a DDS frequency offset of %c%dkHz\n", invert ? '-' : ' ', dds / unit_khz_dds_val);

	अगर (असल_offset_khz <= (state->cfg.pll->पूर्णांकernal / ratio)) अणु
		/* Max dds offset is the half of the demod freq */
		dib8000_ग_लिखो_word(state, 26, invert);
		dib8000_ग_लिखो_word(state, 27, (u16)(dds >> 16) & 0x1ff);
		dib8000_ग_लिखो_word(state, 28, (u16)(dds & 0xffff));
	पूर्ण
पूर्ण

अटल व्योम dib8000_set_frequency_offset(काष्ठा dib8000_state *state)
अणु
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	पूर्णांक i;
	u32 current_rf;
	पूर्णांक total_dds_offset_khz;

	अगर (state->fe[0]->ops.tuner_ops.get_frequency)
		state->fe[0]->ops.tuner_ops.get_frequency(state->fe[0], &current_rf);
	अन्यथा
		current_rf = c->frequency;
	current_rf /= 1000;
	total_dds_offset_khz = (पूर्णांक)current_rf - (पूर्णांक)c->frequency / 1000;

	अगर (c->isdbt_sb_mode) अणु
		state->subchannel = c->isdbt_sb_subchannel;

		i = dib8000_पढ़ो_word(state, 26) & 1; /* P_dds_invspec */
		dib8000_ग_लिखो_word(state, 26, c->inversion ^ i);

		अगर (state->cfg.pll->अगरreq == 0) अणु /* low अगर tuner */
			अगर ((c->inversion ^ i) == 0)
				dib8000_ग_लिखो_word(state, 26, dib8000_पढ़ो_word(state, 26) | 1);
		पूर्ण अन्यथा अणु
			अगर ((c->inversion ^ i) == 0)
				total_dds_offset_khz *= -1;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("%dkhz tuner offset (frequency = %dHz & current_rf = %dHz) total_dds_offset_hz = %d\n", c->frequency - current_rf, c->frequency, current_rf, total_dds_offset_khz);

	/* apply dds offset now */
	dib8000_set_dds(state, total_dds_offset_khz);
पूर्ण

अटल u16 LUT_isdbt_symbol_duration[4] = अणु 26, 101, 63 पूर्ण;

अटल u32 dib8000_get_symbol_duration(काष्ठा dib8000_state *state)
अणु
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 i;

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
			i = 0;
			अवरोध;
	हाल TRANSMISSION_MODE_4K:
			i = 2;
			अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_AUTO:
	हाल TRANSMISSION_MODE_8K:
			i = 1;
			अवरोध;
	पूर्ण

	वापस (LUT_isdbt_symbol_duration[i] / (c->bandwidth_hz / 1000)) + 1;
पूर्ण

अटल व्योम dib8000_set_isdbt_loop_params(काष्ठा dib8000_state *state, क्रमागत param_loop_step loop_step)
अणु
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 reg_32 = 0, reg_37 = 0;

	चयन (loop_step) अणु
	हाल LOOP_TUNE_1:
			अगर (c->isdbt_sb_mode)  अणु
				अगर (c->isdbt_partial_reception == 0) अणु
					reg_32 = ((11 - state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (11-P_mode), P_corm_alpha=6, P_corm_thres=0x40 */
					reg_37 = (3 << 5) | (0 << 4) | (10 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (10-P_mode)  */
				पूर्ण अन्यथा अणु /* Sound Broadcasting mode 3 seg */
					reg_32 = ((10 - state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (10-P_mode), P_corm_alpha=6, P_corm_thres=0x60 */
					reg_37 = (3 << 5) | (0 << 4) | (9 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (9-P_mode)  */
				पूर्ण
			पूर्ण अन्यथा अणु /* 13-seg start conf offset loop parameters */
				reg_32 = ((9 - state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = (9-P_mode, P_corm_alpha=6, P_corm_thres=0x80 */
				reg_37 = (3 << 5) | (0 << 4) | (8 - state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = 9  */
			पूर्ण
			अवरोध;
	हाल LOOP_TUNE_2:
			अगर (c->isdbt_sb_mode)  अणु
				अगर (c->isdbt_partial_reception == 0) अणु  /* Sound Broadcasting mode 1 seg */
					reg_32 = ((13-state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (13-P_mode) , P_corm_alpha=6, P_corm_thres=0x40*/
					reg_37 = (12-state->mode) | ((5 + state->mode) << 5);
				पूर्ण अन्यथा अणु  /* Sound Broadcasting mode 3 seg */
					reg_32 = ((12-state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (12-P_mode) , P_corm_alpha=6, P_corm_thres=0x60 */
					reg_37 = (11-state->mode) | ((5 + state->mode) << 5);
				पूर्ण
			पूर्ण अन्यथा अणु  /* 13 seg */
				reg_32 = ((11-state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = 8 , P_corm_alpha=6, P_corm_thres=0x80 */
				reg_37 = ((5+state->mode) << 5) | (10 - state->mode);
			पूर्ण
			अवरोध;
	पूर्ण
	dib8000_ग_लिखो_word(state, 32, reg_32);
	dib8000_ग_लिखो_word(state, 37, reg_37);
पूर्ण

अटल व्योम dib8000_demod_restart(काष्ठा dib8000_state *state)
अणु
	dib8000_ग_लिखो_word(state, 770, 0x4000);
	dib8000_ग_लिखो_word(state, 770, 0x0000);
	वापस;
पूर्ण

अटल व्योम dib8000_set_sync_रुको(काष्ठा dib8000_state *state)
अणु
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	u16 sync_रुको = 64;

	/* P_dvsy_sync_रुको - reuse mode */
	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_8K:
			sync_रुको = 256;
			अवरोध;
	हाल TRANSMISSION_MODE_4K:
			sync_रुको = 128;
			अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_2K:
			sync_रुको =  64;
			अवरोध;
	पूर्ण

	अगर (state->cfg.भागersity_delay == 0)
		sync_रुको = (sync_रुको * (1 << (c->guard_पूर्णांकerval)) * 3) / 2 + 48; /* add 50% SFN margin + compensate क्रम one DVSY-fअगरo */
	अन्यथा
		sync_रुको = (sync_रुको * (1 << (c->guard_पूर्णांकerval)) * 3) / 2 + state->cfg.भागersity_delay; /* add 50% SFN margin + compensate क्रम DVSY-fअगरo */

	dib8000_ग_लिखो_word(state, 273, (dib8000_पढ़ो_word(state, 273) & 0x000f) | (sync_रुको << 4));
पूर्ण

अटल अचिन्हित दीर्घ dib8000_get_समयout(काष्ठा dib8000_state *state, u32 delay, क्रमागत समयout_mode mode)
अणु
	अगर (mode == SYMBOL_DEPENDENT_ON)
		delay *= state->symbol_duration;

	वापस jअगरfies + usecs_to_jअगरfies(delay * 100);
पूर्ण

अटल s32 dib8000_get_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	वापस state->status;
पूर्ण

अटल क्रमागत frontend_tune_state dib8000_get_tune_state(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	वापस state->tune_state;
पूर्ण

अटल पूर्णांक dib8000_set_tune_state(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	state->tune_state = tune_state;
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_tune_restart_from_demod(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	state->status = FE_STATUS_TUNE_PENDING;
	state->tune_state = CT_DEMOD_START;
	वापस 0;
पूर्ण

अटल u16 dib8000_पढ़ो_lock(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	अगर (state->revision == 0x8090)
		वापस dib8000_पढ़ो_word(state, 570);
	वापस dib8000_पढ़ो_word(state, 568);
पूर्ण

अटल पूर्णांक dib8090p_init_sdram(काष्ठा dib8000_state *state)
अणु
	u16 reg = 0;
	dprपूर्णांकk("init sdram\n");

	reg = dib8000_पढ़ो_word(state, 274) & 0xfff0;
	dib8000_ग_लिखो_word(state, 274, reg | 0x7); /* P_dपूर्णांकlv_delay_ram = 7 because of MobileSdram */

	dib8000_ग_लिखो_word(state, 1803, (7 << 2));

	reg = dib8000_पढ़ो_word(state, 1280);
	dib8000_ग_लिखो_word(state, 1280,  reg | (1 << 2)); /* क्रमce restart P_restart_sdram */
	dib8000_ग_लिखो_word(state, 1280,  reg); /* release restart P_restart_sdram */

	वापस 0;
पूर्ण

/**
 * is_manual_mode - Check अगर TMCC should be used क्रम parameters settings
 * @c:	काष्ठा dvb_frontend_properties
 *
 * By शेष, TMCC table should be used क्रम parameter settings on most
 * userहालs. However, someबार it is desirable to lock the demod to
 * use the manual parameters.
 *
 * On manual mode, the current dib8000_tune state machine is very restrict:
 * It requires that both per-layer and per-transponder parameters to be
 * properly specअगरied, otherwise the device won't lock.
 *
 * Check अगर all those conditions are properly satisfied beक्रमe allowing
 * the device to use the manual frequency lock mode.
 */
अटल पूर्णांक is_manual_mode(काष्ठा dtv_frontend_properties *c)
अणु
	पूर्णांक i, n_segs = 0;

	/* Use स्वतः mode on DVB-T compat mode */
	अगर (c->delivery_प्रणाली != SYS_ISDBT)
		वापस 0;

	/*
	 * Transmission mode is only detected on स्वतः mode, currently
	 */
	अगर (c->transmission_mode == TRANSMISSION_MODE_AUTO) अणु
		dprपूर्णांकk("transmission mode auto\n");
		वापस 0;
	पूर्ण

	/*
	 * Guard पूर्णांकerval is only detected on स्वतः mode, currently
	 */
	अगर (c->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO) अणु
		dprपूर्णांकk("guard interval auto\n");
		वापस 0;
	पूर्ण

	/*
	 * If no layer is enabled, assume स्वतः mode, as at least one
	 * layer should be enabled
	 */
	अगर (!c->isdbt_layer_enabled) अणु
		dprपूर्णांकk("no layer modulation specified\n");
		वापस 0;
	पूर्ण

	/*
	 * Check अगर the per-layer parameters aren't स्वतः and
	 * disable a layer अगर segment count is 0 or invalid.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!(c->isdbt_layer_enabled & 1 << i))
			जारी;

		अगर ((c->layer[i].segment_count > 13) ||
		    (c->layer[i].segment_count == 0)) अणु
			c->isdbt_layer_enabled &= ~(1 << i);
			जारी;
		पूर्ण

		n_segs += c->layer[i].segment_count;

		अगर ((c->layer[i].modulation == QAM_AUTO) ||
		    (c->layer[i].fec == FEC_AUTO)) अणु
			dprपूर्णांकk("layer %c has either modulation or FEC auto\n",
				'A' + i);
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Userspace specअगरied a wrong number of segments.
	 *	fallback to स्वतः mode.
	 */
	अगर (n_segs == 0 || n_segs > 13) अणु
		dprपूर्णांकk("number of segments is invalid\n");
		वापस 0;
	पूर्ण

	/* Everything looks ok क्रम manual mode */
	वापस 1;
पूर्ण

अटल पूर्णांक dib8000_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	क्रमागत frontend_tune_state *tune_state = &state->tune_state;

	u16 locks, deeper_पूर्णांकerleaver = 0, i;
	पूर्णांक ret = 1; /* 1 symbol duration (in 100us unit) delay most of the समय */

	अचिन्हित दीर्घ *समयout = &state->समयout;
	अचिन्हित दीर्घ now = jअगरfies;
#अगर_घोषित DIB8000_AGC_FREEZE
	u16 agc1, agc2;
#पूर्ण_अगर

	u32 corm[4] = अणु0, 0, 0, 0पूर्ण;
	u8 find_index, max_value;

#अगर 0
	अगर (*tune_state < CT_DEMOD_STOP)
		dprपूर्णांकk("IN: context status = %d, TUNE_STATE %d autosearch step = %u jiffies = %lu\n",
			state->channel_parameters_set, *tune_state, state->स्वतःsearch_state, now);
#पूर्ण_अगर

	चयन (*tune_state) अणु
	हाल CT_DEMOD_START: /* 30 */
		dib8000_reset_stats(fe);

		अगर (state->revision == 0x8090)
			dib8090p_init_sdram(state);
		state->status = FE_STATUS_TUNE_PENDING;
		state->channel_parameters_set = is_manual_mode(c);

		dprपूर्णांकk("Tuning channel on %s search mode\n",
			state->channel_parameters_set ? "manual" : "auto");

		dib8000_viterbi_state(state, 0); /* क्रमce chan dec in restart */

		/* Layer monitor */
		dib8000_ग_लिखो_word(state, 285, dib8000_पढ़ो_word(state, 285) & 0x60);

		dib8000_set_frequency_offset(state);
		dib8000_set_bandwidth(fe, c->bandwidth_hz / 1000);

		अगर (state->channel_parameters_set == 0) अणु /* The channel काष्ठा is unknown, search it ! */
#अगर_घोषित DIB8000_AGC_FREEZE
			अगर (state->revision != 0x8090) अणु
				state->agc1_max = dib8000_पढ़ो_word(state, 108);
				state->agc1_min = dib8000_पढ़ो_word(state, 109);
				state->agc2_max = dib8000_पढ़ो_word(state, 110);
				state->agc2_min = dib8000_पढ़ो_word(state, 111);
				agc1 = dib8000_पढ़ो_word(state, 388);
				agc2 = dib8000_पढ़ो_word(state, 389);
				dib8000_ग_लिखो_word(state, 108, agc1);
				dib8000_ग_लिखो_word(state, 109, agc1);
				dib8000_ग_लिखो_word(state, 110, agc2);
				dib8000_ग_लिखो_word(state, 111, agc2);
			पूर्ण
#पूर्ण_अगर
			state->स्वतःsearch_state = AS_SEARCHING_FFT;
			state->found_nfft = TRANSMISSION_MODE_AUTO;
			state->found_guard = GUARD_INTERVAL_AUTO;
			*tune_state = CT_DEMOD_SEARCH_NEXT;
		पूर्ण अन्यथा अणु /* we alपढ़ोy know the channel काष्ठा so TUNE only ! */
			state->स्वतःsearch_state = AS_DONE;
			*tune_state = CT_DEMOD_STEP_3;
		पूर्ण
		state->symbol_duration = dib8000_get_symbol_duration(state);
		अवरोध;

	हाल CT_DEMOD_SEARCH_NEXT: /* 51 */
		dib8000_स्वतःsearch_start(fe);
		अगर (state->revision == 0x8090)
			ret = 50;
		अन्यथा
			ret = 15;
		*tune_state = CT_DEMOD_STEP_1;
		अवरोध;

	हाल CT_DEMOD_STEP_1: /* 31 */
		चयन (dib8000_स्वतःsearch_irq(fe)) अणु
		हाल 1: /* fail */
			state->status = FE_STATUS_TUNE_FAILED;
			state->स्वतःsearch_state = AS_DONE;
			*tune_state = CT_DEMOD_STOP; /* अन्यथा we are करोne here */
			अवरोध;
		हाल 2: /* Success */
			state->status = FE_STATUS_FFT_SUCCESS; /* संकेत to the upper layer, that there was a channel found and the parameters can be पढ़ो */
			*tune_state = CT_DEMOD_STEP_3;
			अगर (state->स्वतःsearch_state == AS_SEARCHING_GUARD)
				*tune_state = CT_DEMOD_STEP_2;
			अन्यथा
				state->स्वतःsearch_state = AS_DONE;
			अवरोध;
		हाल 3: /* Autosearch FFT max correlation endded */
			*tune_state = CT_DEMOD_STEP_2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_2:
		चयन (state->स्वतःsearch_state) अणु
		हाल AS_SEARCHING_FFT:
			/* searching क्रम the correct FFT */
			अगर (state->revision == 0x8090) अणु
				corm[2] = (dib8000_पढ़ो_word(state, 596) << 16) | (dib8000_पढ़ो_word(state, 597));
				corm[1] = (dib8000_पढ़ो_word(state, 598) << 16) | (dib8000_पढ़ो_word(state, 599));
				corm[0] = (dib8000_पढ़ो_word(state, 600) << 16) | (dib8000_पढ़ो_word(state, 601));
			पूर्ण अन्यथा अणु
				corm[2] = (dib8000_पढ़ो_word(state, 594) << 16) | (dib8000_पढ़ो_word(state, 595));
				corm[1] = (dib8000_पढ़ो_word(state, 596) << 16) | (dib8000_पढ़ो_word(state, 597));
				corm[0] = (dib8000_पढ़ो_word(state, 598) << 16) | (dib8000_पढ़ो_word(state, 599));
			पूर्ण
			/* dprपूर्णांकk("corm fft: %u %u %u\n", corm[0], corm[1], corm[2]); */

			max_value = 0;
			क्रम (find_index = 1 ; find_index < 3 ; find_index++) अणु
				अगर (corm[max_value] < corm[find_index])
					max_value = find_index ;
			पूर्ण

			चयन (max_value) अणु
			हाल 0:
				state->found_nfft = TRANSMISSION_MODE_2K;
				अवरोध;
			हाल 1:
				state->found_nfft = TRANSMISSION_MODE_4K;
				अवरोध;
			हाल 2:
			शेष:
				state->found_nfft = TRANSMISSION_MODE_8K;
				अवरोध;
			पूर्ण
			/* dprपूर्णांकk("Autosearch FFT has found Mode %d\n", max_value + 1); */

			*tune_state = CT_DEMOD_SEARCH_NEXT;
			state->स्वतःsearch_state = AS_SEARCHING_GUARD;
			अगर (state->revision == 0x8090)
				ret = 50;
			अन्यथा
				ret = 10;
			अवरोध;
		हाल AS_SEARCHING_GUARD:
			/* searching क्रम the correct guard पूर्णांकerval */
			अगर (state->revision == 0x8090)
				state->found_guard = dib8000_पढ़ो_word(state, 572) & 0x3;
			अन्यथा
				state->found_guard = dib8000_पढ़ो_word(state, 570) & 0x3;
			/* dprपूर्णांकk("guard interval found=%i\n", state->found_guard); */

			*tune_state = CT_DEMOD_STEP_3;
			अवरोध;
		शेष:
			/* the demod should never be in this state */
			state->status = FE_STATUS_TUNE_FAILED;
			state->स्वतःsearch_state = AS_DONE;
			*tune_state = CT_DEMOD_STOP; /* अन्यथा we are करोne here */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_3: /* 33 */
		dib8000_set_isdbt_loop_params(state, LOOP_TUNE_1);
		dib8000_set_isdbt_common_channel(state, 0, 0);/* setting the known channel parameters here */
		*tune_state = CT_DEMOD_STEP_4;
		अवरोध;

	हाल CT_DEMOD_STEP_4: /* (34) */
		dib8000_demod_restart(state);

		dib8000_set_sync_रुको(state);
		dib8000_set_भागersity_in(state->fe[0], state->भागersity_onoff);

		locks = (dib8000_पढ़ो_word(state, 180) >> 6) & 0x3f; /* P_coff_winlen ? */
		/* coff should lock over P_coff_winlen ofdm symbols : give 3 बार this length to lock */
		*समयout = dib8000_get_समयout(state, 2 * locks, SYMBOL_DEPENDENT_ON);
		*tune_state = CT_DEMOD_STEP_5;
		अवरोध;

	हाल CT_DEMOD_STEP_5: /* (35) */
		locks = dib8000_पढ़ो_lock(fe);
		अगर (locks & (0x3 << 11)) अणु /* coff-lock and off_cpil_lock achieved */
			dib8000_update_timf(state); /* we achieved a coff_cpil_lock - it's समय to update the timf */
			अगर (!state->dअगरferential_स्थिरellation) अणु
				/* 2 बार lmod4_win_len + 10 symbols (pipe delay after coff + nb to compute a 1st correlation) */
				*समयout = dib8000_get_समयout(state, (20 * ((dib8000_पढ़ो_word(state, 188)>>5)&0x1f)), SYMBOL_DEPENDENT_ON);
				*tune_state = CT_DEMOD_STEP_7;
			पूर्ण अन्यथा अणु
				*tune_state = CT_DEMOD_STEP_8;
			पूर्ण
		पूर्ण अन्यथा अगर (समय_after(now, *समयout)) अणु
			*tune_state = CT_DEMOD_STEP_6; /* जाओ check क्रम भागersity input connection */
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_6: /* (36)  अगर there is an input (भागersity) */
		अगर ((state->fe[1] != शून्य) && (state->output_mode != OUTMODE_DIVERSITY)) अणु
			/* अगर there is a भागersity fe in input and this fe is has not alपढ़ोy failed : रुको here until this this fe has succedeed or failed */
			अगर (dib8000_get_status(state->fe[1]) <= FE_STATUS_STD_SUCCESS) /* Something is locked on the input fe */
				*tune_state = CT_DEMOD_STEP_8; /* go क्रम mpeg */
			अन्यथा अगर (dib8000_get_status(state->fe[1]) >= FE_STATUS_TUNE_TIME_TOO_SHORT) अणु /* fe in input failed also, अवरोध the current one */
				*tune_state = CT_DEMOD_STOP; /* अन्यथा we are करोne here ; step 8 will बंद the loops and निकास */
				dib8000_viterbi_state(state, 1); /* start viterbi chandec */
				dib8000_set_isdbt_loop_params(state, LOOP_TUNE_2);
				state->status = FE_STATUS_TUNE_FAILED;
			पूर्ण
		पूर्ण अन्यथा अणु
			dib8000_viterbi_state(state, 1); /* start viterbi chandec */
			dib8000_set_isdbt_loop_params(state, LOOP_TUNE_2);
			*tune_state = CT_DEMOD_STOP; /* अन्यथा we are करोne here ; step 8 will बंद the loops and निकास */
			state->status = FE_STATUS_TUNE_FAILED;
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_7: /* 37 */
		locks = dib8000_पढ़ो_lock(fe);
		अगर (locks & (1<<10)) अणु /* lmod4_lock */
			ret = 14; /* रुको क्रम 14 symbols */
			*tune_state = CT_DEMOD_STEP_8;
		पूर्ण अन्यथा अगर (समय_after(now, *समयout))
			*tune_state = CT_DEMOD_STEP_6; /* जाओ check क्रम भागersity input connection */
		अवरोध;

	हाल CT_DEMOD_STEP_8: /* 38 */
		dib8000_viterbi_state(state, 1); /* start viterbi chandec */
		dib8000_set_isdbt_loop_params(state, LOOP_TUNE_2);

		/* mpeg will never lock on this condition because init_prbs is not set : search क्रम it !*/
		अगर (c->isdbt_sb_mode
		    && c->isdbt_sb_subchannel < 14
		    && !state->dअगरferential_स्थिरellation) अणु
			state->subchannel = 0;
			*tune_state = CT_DEMOD_STEP_11;
		पूर्ण अन्यथा अणु
			*tune_state = CT_DEMOD_STEP_9;
			state->status = FE_STATUS_LOCKED;
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_9: /* 39 */
		अगर ((state->revision == 0x8090) || ((dib8000_पढ़ो_word(state, 1291) >> 9) & 0x1)) अणु /* fe capable of deपूर्णांकerleaving : esram */
			/* defines समयout क्रम mpeg lock depending on पूर्णांकerleaver length of दीर्घest layer */
			क्रम (i = 0; i < 3; i++) अणु
				अगर (c->layer[i].पूर्णांकerleaving >= deeper_पूर्णांकerleaver) अणु
					dprपूर्णांकk("layer%i: time interleaver = %d\n", i, c->layer[i].पूर्णांकerleaving);
					अगर (c->layer[i].segment_count > 0) अणु /* valid layer */
						deeper_पूर्णांकerleaver = c->layer[0].पूर्णांकerleaving;
						state->दीर्घest_पूर्णांकlv_layer = i;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (deeper_पूर्णांकerleaver == 0)
				locks = 2; /* locks is the पंचांगp local variable name */
			अन्यथा अगर (deeper_पूर्णांकerleaver == 3)
				locks = 8;
			अन्यथा
				locks = 2 * deeper_पूर्णांकerleaver;

			अगर (state->भागersity_onoff != 0) /* because of भागersity sync */
				locks *= 2;

			*समयout = now + msecs_to_jअगरfies(200 * locks); /* give the mpeg lock 800ms अगर sram is present */
			dprपूर्णांकk("Deeper interleaver mode = %d on layer %d : timeout mult factor = %d => will use timeout = %ld\n",
				deeper_पूर्णांकerleaver, state->दीर्घest_पूर्णांकlv_layer, locks, *समयout);

			*tune_state = CT_DEMOD_STEP_10;
		पूर्ण अन्यथा
			*tune_state = CT_DEMOD_STOP;
		अवरोध;

	हाल CT_DEMOD_STEP_10: /* 40 */
		locks = dib8000_पढ़ो_lock(fe);
		अगर (locks&(1<<(7-state->दीर्घest_पूर्णांकlv_layer))) अणु /* mpeg lock : check the दीर्घest one */
			dprपूर्णांकk("ISDB-T layer locks: Layer A %s, Layer B %s, Layer C %s\n",
				c->layer[0].segment_count ? (locks >> 7) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled",
				c->layer[1].segment_count ? (locks >> 6) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled",
				c->layer[2].segment_count ? (locks >> 5) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled");
			अगर (c->isdbt_sb_mode
			    && c->isdbt_sb_subchannel < 14
			    && !state->dअगरferential_स्थिरellation)
				/* संकेत to the upper layer, that there was a channel found and the parameters can be पढ़ो */
				state->status = FE_STATUS_DEMOD_SUCCESS;
			अन्यथा
				state->status = FE_STATUS_DATA_LOCKED;
			*tune_state = CT_DEMOD_STOP;
		पूर्ण अन्यथा अगर (समय_after(now, *समयout)) अणु
			अगर (c->isdbt_sb_mode
			    && c->isdbt_sb_subchannel < 14
			    && !state->dअगरferential_स्थिरellation) अणु /* जारी to try init prbs स्वतःsearch */
				state->subchannel += 3;
				*tune_state = CT_DEMOD_STEP_11;
			पूर्ण अन्यथा अणु /* we are करोne mpeg of the दीर्घest पूर्णांकerleaver xas not locking but let's try अगर an other layer has locked in the same समय */
				अगर (locks & (0x7 << 5)) अणु
					dprपूर्णांकk("Not all ISDB-T layers locked in %d ms: Layer A %s, Layer B %s, Layer C %s\n",
						jअगरfies_to_msecs(now - *समयout),
						c->layer[0].segment_count ? (locks >> 7) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled",
						c->layer[1].segment_count ? (locks >> 6) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled",
						c->layer[2].segment_count ? (locks >> 5) & 0x1 ? "locked" : "NOT LOCKED" : "not enabled");

					state->status = FE_STATUS_DATA_LOCKED;
				पूर्ण अन्यथा
					state->status = FE_STATUS_TUNE_FAILED;
				*tune_state = CT_DEMOD_STOP;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल CT_DEMOD_STEP_11:  /* 41 : init prbs स्वतःsearch */
		अगर (state->subchannel <= 41) अणु
			dib8000_set_subchannel_prbs(state, dib8000_get_init_prbs(state, state->subchannel));
			*tune_state = CT_DEMOD_STEP_9;
		पूर्ण अन्यथा अणु
			*tune_state = CT_DEMOD_STOP;
			state->status = FE_STATUS_TUNE_FAILED;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* tuning is finished - cleanup the demod */
	चयन (*tune_state) अणु
	हाल CT_DEMOD_STOP: /* (42) */
#अगर_घोषित DIB8000_AGC_FREEZE
		अगर ((state->revision != 0x8090) && (state->agc1_max != 0)) अणु
			dib8000_ग_लिखो_word(state, 108, state->agc1_max);
			dib8000_ग_लिखो_word(state, 109, state->agc1_min);
			dib8000_ग_लिखो_word(state, 110, state->agc2_max);
			dib8000_ग_लिखो_word(state, 111, state->agc2_min);
			state->agc1_max = 0;
			state->agc1_min = 0;
			state->agc2_max = 0;
			state->agc2_min = 0;
		पूर्ण
#पूर्ण_अगर
		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((ret > 0) && (*tune_state > CT_DEMOD_STEP_3))
		वापस ret * state->symbol_duration;
	अगर ((ret > 0) && (ret < state->symbol_duration))
		वापस state->symbol_duration; /* at least one symbol */
	वापस ret;
पूर्ण

अटल पूर्णांक dib8000_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	पूर्णांक ret;

	dib8000_set_घातer_mode(state, DIB8000_POWER_ALL);
	dib8000_set_adc_state(state, DIBX000_ADC_ON);
	अगर (dib8000_set_adc_state(state, DIBX000_SLOW_ADC_ON) != 0)
		dprपूर्णांकk("could not start Slow ADC\n");

	अगर (state->revision == 0x8090)
		dib8000_sad_calib(state);

	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		ret = state->fe[index_frontend]->ops.init(state->fe[index_frontend]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	पूर्णांक ret;

	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		ret = state->fe[index_frontend]->ops.sleep(state->fe[index_frontend]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (state->revision != 0x8090)
		dib8000_set_output_mode(fe, OUTMODE_HIGH_Z);
	dib8000_set_घातer_mode(state, DIB8000_POWER_INTERFACE_ONLY);
	वापस dib8000_set_adc_state(state, DIBX000_SLOW_ADC_OFF) | dib8000_set_adc_state(state, DIBX000_ADC_OFF);
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat);

अटल पूर्णांक dib8000_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 i, val = 0;
	क्रमागत fe_status stat = 0;
	u8 index_frontend, sub_index_frontend;

	c->bandwidth_hz = 6000000;

	/*
	 * If called to early, get_frontend makes dib8000_tune to either
	 * not lock or not sync. This causes dvbv5-scan/dvbv5-zap to fail.
	 * So, let's just वापस अगर frontend 0 has not locked.
	 */
	dib8000_पढ़ो_status(fe, &stat);
	अगर (!(stat & FE_HAS_SYNC))
		वापस 0;

	dprपूर्णांकk("dib8000_get_frontend: TMCC lock\n");
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->ops.पढ़ो_status(state->fe[index_frontend], &stat);
		अगर (stat&FE_HAS_SYNC) अणु
			dprपूर्णांकk("TMCC lock on the slave%i\n", index_frontend);
			/* synchronize the cache with the other frontends */
			state->fe[index_frontend]->ops.get_frontend(state->fe[index_frontend], c);
			क्रम (sub_index_frontend = 0; (sub_index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[sub_index_frontend] != शून्य); sub_index_frontend++) अणु
				अगर (sub_index_frontend != index_frontend) अणु
					state->fe[sub_index_frontend]->dtv_property_cache.isdbt_sb_mode = state->fe[index_frontend]->dtv_property_cache.isdbt_sb_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.inversion = state->fe[index_frontend]->dtv_property_cache.inversion;
					state->fe[sub_index_frontend]->dtv_property_cache.transmission_mode = state->fe[index_frontend]->dtv_property_cache.transmission_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.guard_पूर्णांकerval = state->fe[index_frontend]->dtv_property_cache.guard_पूर्णांकerval;
					state->fe[sub_index_frontend]->dtv_property_cache.isdbt_partial_reception = state->fe[index_frontend]->dtv_property_cache.isdbt_partial_reception;
					क्रम (i = 0; i < 3; i++) अणु
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].segment_count = state->fe[index_frontend]->dtv_property_cache.layer[i].segment_count;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].पूर्णांकerleaving = state->fe[index_frontend]->dtv_property_cache.layer[i].पूर्णांकerleaving;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].fec = state->fe[index_frontend]->dtv_property_cache.layer[i].fec;
						state->fe[sub_index_frontend]->dtv_property_cache.layer[i].modulation = state->fe[index_frontend]->dtv_property_cache.layer[i].modulation;
					पूर्ण
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	c->isdbt_sb_mode = dib8000_पढ़ो_word(state, 508) & 0x1;

	अगर (state->revision == 0x8090)
		val = dib8000_पढ़ो_word(state, 572);
	अन्यथा
		val = dib8000_पढ़ो_word(state, 570);
	c->inversion = (val & 0x40) >> 6;
	चयन ((val & 0x30) >> 4) अणु
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		dprपूर्णांकk("dib8000_get_frontend: transmission mode 2K\n");
		अवरोध;
	हाल 2:
		c->transmission_mode = TRANSMISSION_MODE_4K;
		dprपूर्णांकk("dib8000_get_frontend: transmission mode 4K\n");
		अवरोध;
	हाल 3:
	शेष:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		dprपूर्णांकk("dib8000_get_frontend: transmission mode 8K\n");
		अवरोध;
	पूर्ण

	चयन (val & 0x3) अणु
	हाल 0:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		dprपूर्णांकk("dib8000_get_frontend: Guard Interval = 1/32\n");
		अवरोध;
	हाल 1:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		dprपूर्णांकk("dib8000_get_frontend: Guard Interval = 1/16\n");
		अवरोध;
	हाल 2:
		dprपूर्णांकk("dib8000_get_frontend: Guard Interval = 1/8\n");
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		dprपूर्णांकk("dib8000_get_frontend: Guard Interval = 1/4\n");
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	val = dib8000_पढ़ो_word(state, 505);
	c->isdbt_partial_reception = val & 1;
	dprपूर्णांकk("dib8000_get_frontend: partial_reception = %d\n", c->isdbt_partial_reception);

	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांक show;

		val = dib8000_पढ़ो_word(state, 493 + i) & 0x0f;
		c->layer[i].segment_count = val;

		अगर (val == 0 || val > 13)
			show = 0;
		अन्यथा
			show = 1;

		अगर (show)
			dprपूर्णांकk("dib8000_get_frontend: Layer %d segments = %d\n",
				i, c->layer[i].segment_count);

		val = dib8000_पढ़ो_word(state, 499 + i) & 0x3;
		/* Interleaving can be 0, 1, 2 or 4 */
		अगर (val == 3)
			val = 4;
		c->layer[i].पूर्णांकerleaving = val;
		अगर (show)
			dprपूर्णांकk("dib8000_get_frontend: Layer %d time_intlv = %d\n",
				i, c->layer[i].पूर्णांकerleaving);

		val = dib8000_पढ़ो_word(state, 481 + i);
		चयन (val & 0x7) अणु
		हाल 1:
			c->layer[i].fec = FEC_1_2;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d Code Rate = 1/2\n", i);
			अवरोध;
		हाल 2:
			c->layer[i].fec = FEC_2_3;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d Code Rate = 2/3\n", i);
			अवरोध;
		हाल 3:
			c->layer[i].fec = FEC_3_4;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d Code Rate = 3/4\n", i);
			अवरोध;
		हाल 5:
			c->layer[i].fec = FEC_5_6;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d Code Rate = 5/6\n", i);
			अवरोध;
		शेष:
			c->layer[i].fec = FEC_7_8;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d Code Rate = 7/8\n", i);
			अवरोध;
		पूर्ण

		val = dib8000_पढ़ो_word(state, 487 + i);
		चयन (val & 0x3) अणु
		हाल 0:
			c->layer[i].modulation = DQPSK;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d DQPSK\n", i);
			अवरोध;
		हाल 1:
			c->layer[i].modulation = QPSK;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d QPSK\n", i);
			अवरोध;
		हाल 2:
			c->layer[i].modulation = QAM_16;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d QAM16\n", i);
			अवरोध;
		हाल 3:
		शेष:
			c->layer[i].modulation = QAM_64;
			अगर (show)
				dprपूर्णांकk("dib8000_get_frontend: Layer %d QAM64\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	/* synchronize the cache with the other frontends */
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->dtv_property_cache.isdbt_sb_mode = c->isdbt_sb_mode;
		state->fe[index_frontend]->dtv_property_cache.inversion = c->inversion;
		state->fe[index_frontend]->dtv_property_cache.transmission_mode = c->transmission_mode;
		state->fe[index_frontend]->dtv_property_cache.guard_पूर्णांकerval = c->guard_पूर्णांकerval;
		state->fe[index_frontend]->dtv_property_cache.isdbt_partial_reception = c->isdbt_partial_reception;
		क्रम (i = 0; i < 3; i++) अणु
			state->fe[index_frontend]->dtv_property_cache.layer[i].segment_count = c->layer[i].segment_count;
			state->fe[index_frontend]->dtv_property_cache.layer[i].पूर्णांकerleaving = c->layer[i].पूर्णांकerleaving;
			state->fe[index_frontend]->dtv_property_cache.layer[i].fec = c->layer[i].fec;
			state->fe[index_frontend]->dtv_property_cache.layer[i].modulation = c->layer[i].modulation;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	पूर्णांक l, i, active, समय, समय_slave = 0;
	u8 निकास_condition, index_frontend;
	अचिन्हित दीर्घ delay, callback_समय;

	अगर (c->frequency == 0) अणु
		dprपूर्णांकk("dib8000: must at least specify frequency\n");
		वापस 0;
	पूर्ण

	अगर (c->bandwidth_hz == 0) अणु
		dprपूर्णांकk("dib8000: no bandwidth specified, set to default\n");
		c->bandwidth_hz = 6000000;
	पूर्ण

	क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		/* synchronization of the cache */
		state->fe[index_frontend]->dtv_property_cache.delivery_प्रणाली = SYS_ISDBT;
		स_नकल(&state->fe[index_frontend]->dtv_property_cache, &fe->dtv_property_cache, माप(काष्ठा dtv_frontend_properties));

		/* set output mode and भागersity input */
		अगर (state->revision != 0x8090) अणु
			dib8000_set_भागersity_in(state->fe[index_frontend], 1);
			अगर (index_frontend != 0)
				dib8000_set_output_mode(state->fe[index_frontend],
						OUTMODE_DIVERSITY);
			अन्यथा
				dib8000_set_output_mode(state->fe[0], OUTMODE_HIGH_Z);
		पूर्ण अन्यथा अणु
			dib8096p_set_भागersity_in(state->fe[index_frontend], 1);
			अगर (index_frontend != 0)
				dib8096p_set_output_mode(state->fe[index_frontend],
						OUTMODE_DIVERSITY);
			अन्यथा
				dib8096p_set_output_mode(state->fe[0], OUTMODE_HIGH_Z);
		पूर्ण

		/* tune the tuner */
		अगर (state->fe[index_frontend]->ops.tuner_ops.set_params)
			state->fe[index_frontend]->ops.tuner_ops.set_params(state->fe[index_frontend]);

		dib8000_set_tune_state(state->fe[index_frontend], CT_AGC_START);
	पूर्ण

	/* turn off the भागersity of the last chip */
	अगर (state->revision != 0x8090)
		dib8000_set_भागersity_in(state->fe[index_frontend - 1], 0);
	अन्यथा
		dib8096p_set_भागersity_in(state->fe[index_frontend - 1], 0);

	/* start up the AGC */
	करो अणु
		समय = dib8000_agc_startup(state->fe[0]);
		क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			समय_slave = dib8000_agc_startup(state->fe[index_frontend]);
			अगर (समय == 0)
				समय = समय_slave;
			अन्यथा अगर ((समय_slave != 0) && (समय_slave > समय))
				समय = समय_slave;
		पूर्ण
		अगर (समय == 0)
			अवरोध;

		/*
		 * Despite dib8000_agc_startup वापसs समय at a 0.1 ms range,
		 * the actual sleep समय depends on CONFIG_HZ. The worse हाल
		 * is when CONFIG_HZ=100. In such हाल, the minimum granularity
		 * is 10ms. On some real field tests, the tuner someबार करोn't
		 * lock when this समयr is lower than 10ms. So, enक्रमce a 10ms
		 * granularity.
		 */
		समय = 10 * (समय + 99)/100;
		usleep_range(समय * 1000, (समय + 1) * 1000);
		निकास_condition = 1;
		क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			अगर (dib8000_get_tune_state(state->fe[index_frontend]) != CT_AGC_STOP) अणु
				निकास_condition = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (निकास_condition == 0);

	क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		dib8000_set_tune_state(state->fe[index_frontend], CT_DEMOD_START);

	active = 1;
	करो अणु
		callback_समय = 0;
		क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			delay = dib8000_tune(state->fe[index_frontend]);
			अगर (delay != 0) अणु
				delay = jअगरfies + usecs_to_jअगरfies(100 * delay);
				अगर (!callback_समय || delay < callback_समय)
					callback_समय = delay;
			पूर्ण

			/* we are in स्वतःsearch */
			अगर (state->channel_parameters_set == 0) अणु /* searching */
				अगर ((dib8000_get_status(state->fe[index_frontend]) == FE_STATUS_DEMOD_SUCCESS) || (dib8000_get_status(state->fe[index_frontend]) == FE_STATUS_FFT_SUCCESS)) अणु
					dprपूर्णांकk("autosearch succeeded on fe%i\n", index_frontend);
					dib8000_get_frontend(state->fe[index_frontend], c); /* we पढ़ो the channel parameters from the frontend which was successful */
					state->channel_parameters_set = 1;

					क्रम (l = 0; (l < MAX_NUMBER_OF_FRONTENDS) && (state->fe[l] != शून्य); l++) अणु
						अगर (l != index_frontend) अणु /* and क्रम all frontend except the successful one */
							dprपूर्णांकk("Restarting frontend %d\n", l);
							dib8000_tune_restart_from_demod(state->fe[l]);

							state->fe[l]->dtv_property_cache.isdbt_sb_mode = state->fe[index_frontend]->dtv_property_cache.isdbt_sb_mode;
							state->fe[l]->dtv_property_cache.inversion = state->fe[index_frontend]->dtv_property_cache.inversion;
							state->fe[l]->dtv_property_cache.transmission_mode = state->fe[index_frontend]->dtv_property_cache.transmission_mode;
							state->fe[l]->dtv_property_cache.guard_पूर्णांकerval = state->fe[index_frontend]->dtv_property_cache.guard_पूर्णांकerval;
							state->fe[l]->dtv_property_cache.isdbt_partial_reception = state->fe[index_frontend]->dtv_property_cache.isdbt_partial_reception;
							क्रम (i = 0; i < 3; i++) अणु
								state->fe[l]->dtv_property_cache.layer[i].segment_count = state->fe[index_frontend]->dtv_property_cache.layer[i].segment_count;
								state->fe[l]->dtv_property_cache.layer[i].पूर्णांकerleaving = state->fe[index_frontend]->dtv_property_cache.layer[i].पूर्णांकerleaving;
								state->fe[l]->dtv_property_cache.layer[i].fec = state->fe[index_frontend]->dtv_property_cache.layer[i].fec;
								state->fe[l]->dtv_property_cache.layer[i].modulation = state->fe[index_frontend]->dtv_property_cache.layer[i].modulation;
							पूर्ण

						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		/* tuning is करोne when the master frontend is करोne (failed or success) */
		अगर (dib8000_get_status(state->fe[0]) == FE_STATUS_TUNE_FAILED ||
				dib8000_get_status(state->fe[0]) == FE_STATUS_LOCKED ||
				dib8000_get_status(state->fe[0]) == FE_STATUS_DATA_LOCKED) अणु
			active = 0;
			/* we need to रुको क्रम all frontends to be finished */
			क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
				अगर (dib8000_get_tune_state(state->fe[index_frontend]) != CT_DEMOD_STOP)
					active = 1;
			पूर्ण
			अगर (active == 0)
				dprपूर्णांकk("tuning done with status %d\n", dib8000_get_status(state->fe[0]));
		पूर्ण

		अगर ((active == 1) && (callback_समय == 0)) अणु
			dprपूर्णांकk("strange callback time something went wrong\n");
			active = 0;
		पूर्ण

		जबतक ((active == 1) && (समय_beक्रमe(jअगरfies, callback_समय)))
			msleep(100);
	पूर्ण जबतक (active);

	/* set output mode */
	अगर (state->revision != 0x8090)
		dib8000_set_output_mode(state->fe[0], state->cfg.output_mode);
	अन्यथा अणु
		dib8096p_set_output_mode(state->fe[0], state->cfg.output_mode);
		अगर (state->cfg.enMpegOutput == 0) अणु
			dib8096p_setDibTxMux(state, MPEG_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_get_stats(काष्ठा dvb_frontend *fe, क्रमागत fe_status stat);

अटल पूर्णांक dib8000_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u16 lock_slave = 0, lock;
	u8 index_frontend;

	lock = dib8000_पढ़ो_lock(fe);
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		lock_slave |= dib8000_पढ़ो_lock(state->fe[index_frontend]);

	*stat = 0;

	अगर (((lock >> 13) & 1) || ((lock_slave >> 13) & 1))
		*stat |= FE_HAS_SIGNAL;

	अगर (((lock >> 8) & 1) || ((lock_slave >> 8) & 1)) /* Equal */
		*stat |= FE_HAS_CARRIER;

	अगर ((((lock >> 1) & 0xf) == 0xf) || (((lock_slave >> 1) & 0xf) == 0xf)) /* TMCC_SYNC */
		*stat |= FE_HAS_SYNC;

	अगर ((((lock >> 12) & 1) || ((lock_slave >> 12) & 1)) && ((lock >> 5) & 7)) /* FEC MPEG */
		*stat |= FE_HAS_LOCK;

	अगर (((lock >> 12) & 1) || ((lock_slave >> 12) & 1)) अणु
		lock = dib8000_पढ़ो_word(state, 554); /* Viterbi Layer A */
		अगर (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_पढ़ो_word(state, 555); /* Viterbi Layer B */
		अगर (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_पढ़ो_word(state, 556); /* Viterbi Layer C */
		अगर (lock & 0x01)
			*stat |= FE_HAS_VITERBI;
	पूर्ण
	dib8000_get_stats(fe, *stat);

	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	/* 13 segments */
	अगर (state->revision == 0x8090)
		*ber = (dib8000_पढ़ो_word(state, 562) << 16) |
			dib8000_पढ़ो_word(state, 563);
	अन्यथा
		*ber = (dib8000_पढ़ो_word(state, 560) << 16) |
			dib8000_पढ़ो_word(state, 561);
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 * unc)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	/* packet error on 13 seg */
	अगर (state->revision == 0x8090)
		*unc = dib8000_पढ़ो_word(state, 567);
	अन्यथा
		*unc = dib8000_पढ़ो_word(state, 565);
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 * strength)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u16 val;

	*strength = 0;
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->ops.पढ़ो_संकेत_strength(state->fe[index_frontend], &val);
		अगर (val > 65535 - *strength)
			*strength = 65535;
		अन्यथा
			*strength += val;
	पूर्ण

	val = 65535 - dib8000_पढ़ो_word(state, 390);
	अगर (val > 65535 - *strength)
		*strength = 65535;
	अन्यथा
		*strength += val;
	वापस 0;
पूर्ण

अटल u32 dib8000_get_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u32 n, s, exp;
	u16 val;

	अगर (state->revision != 0x8090)
		val = dib8000_पढ़ो_word(state, 542);
	अन्यथा
		val = dib8000_पढ़ो_word(state, 544);
	n = (val >> 6) & 0xff;
	exp = (val & 0x3f);
	अगर ((exp & 0x20) != 0)
		exp -= 0x40;
	n <<= exp+16;

	अगर (state->revision != 0x8090)
		val = dib8000_पढ़ो_word(state, 543);
	अन्यथा
		val = dib8000_पढ़ो_word(state, 545);
	s = (val >> 6) & 0xff;
	exp = (val & 0x3f);
	अगर ((exp & 0x20) != 0)
		exp -= 0x40;
	s <<= exp+16;

	अगर (n > 0) अणु
		u32 t = (s/n) << 16;
		वापस t + ((s << 16) - n*t) / n;
	पूर्ण
	वापस 0xffffffff;
पूर्ण

अटल पूर्णांक dib8000_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 * snr)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u32 snr_master;

	snr_master = dib8000_get_snr(fe);
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		snr_master += dib8000_get_snr(state->fe[index_frontend]);

	अगर ((snr_master >> 16) != 0) अणु
		snr_master = 10*पूर्णांकlog10(snr_master>>16);
		*snr = snr_master / ((1 << 24) / 10);
	पूर्ण
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

काष्ठा per_layer_regs अणु
	u16 lock, ber, per;
पूर्ण;

अटल स्थिर काष्ठा per_layer_regs per_layer_regs[] = अणु
	अणु 554, 560, 562 पूर्ण,
	अणु 555, 576, 578 पूर्ण,
	अणु 556, 581, 583 पूर्ण,
पूर्ण;

काष्ठा linear_segments अणु
	अचिन्हित x;
	चिन्हित y;
पूर्ण;

/*
 * Table to estimate संकेत strength in dBm.
 * This table was empirically determinated by measuring the संकेत
 * strength generated by a DTA-2111 RF generator directly connected पूर्णांकo
 * a dib8076 device (a PixelView PV-D231U stick), using a good quality
 * 3 meters RC6 cable and good RC6 connectors.
 * The real value can actually be dअगरferent on other devices, depending
 * on several factors, like अगर LNA is enabled or not, अगर भागersity is
 * enabled, type of connectors, etc.
 * Yet, it is better to use this measure in dB than a अक्रमom non-linear
 * percentage value, especially क्रम antenna adjusपंचांगents.
 * On my tests, the precision of the measure using this table is about
 * 0.5 dB, with sounds reasonable enough.
 */
अटल काष्ठा linear_segments strength_to_db_table[] = अणु
	अणु 55953, 108500 पूर्ण,	/* -22.5 dBm */
	अणु 55394, 108000 पूर्ण,
	अणु 53834, 107000 पूर्ण,
	अणु 52863, 106000 पूर्ण,
	अणु 52239, 105000 पूर्ण,
	अणु 52012, 104000 पूर्ण,
	अणु 51803, 103000 पूर्ण,
	अणु 51566, 102000 पूर्ण,
	अणु 51356, 101000 पूर्ण,
	अणु 51112, 100000 पूर्ण,
	अणु 50869,  99000 पूर्ण,
	अणु 50600,  98000 पूर्ण,
	अणु 50363,  97000 पूर्ण,
	अणु 50117,  96000 पूर्ण,	/* -35 dBm */
	अणु 49889,  95000 पूर्ण,
	अणु 49680,  94000 पूर्ण,
	अणु 49493,  93000 पूर्ण,
	अणु 49302,  92000 पूर्ण,
	अणु 48929,  91000 पूर्ण,
	अणु 48416,  90000 पूर्ण,
	अणु 48035,  89000 पूर्ण,
	अणु 47593,  88000 पूर्ण,
	अणु 47282,  87000 पूर्ण,
	अणु 46953,  86000 पूर्ण,
	अणु 46698,  85000 पूर्ण,
	अणु 45617,  84000 पूर्ण,
	अणु 44773,  83000 पूर्ण,
	अणु 43845,  82000 पूर्ण,
	अणु 43020,  81000 पूर्ण,
	अणु 42010,  80000 पूर्ण,	/* -51 dBm */
	अणु     0,      0 पूर्ण,
पूर्ण;

अटल u32 पूर्णांकerpolate_value(u32 value, काष्ठा linear_segments *segments,
			     अचिन्हित len)
अणु
	u64 पंचांगp64;
	u32 dx;
	s32 dy;
	पूर्णांक i, ret;

	अगर (value >= segments[0].x)
		वापस segments[0].y;
	अगर (value < segments[len-1].x)
		वापस segments[len-1].y;

	क्रम (i = 1; i < len - 1; i++) अणु
		/* If value is identical, no need to पूर्णांकerpolate */
		अगर (value == segments[i].x)
			वापस segments[i].y;
		अगर (value > segments[i].x)
			अवरोध;
	पूर्ण

	/* Linear पूर्णांकerpolation between the two (x,y) poपूर्णांकs */
	dy = segments[i - 1].y - segments[i].y;
	dx = segments[i - 1].x - segments[i].x;

	पंचांगp64 = value - segments[i].x;
	पंचांगp64 *= dy;
	करो_भाग(पंचांगp64, dx);
	ret = segments[i].y + पंचांगp64;

	वापस ret;
पूर्ण

अटल u32 dib8000_get_समय_us(काष्ठा dvb_frontend *fe, पूर्णांक layer)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	पूर्णांक ini_layer, end_layer, i;
	u64 समय_us, पंचांगp64;
	u32 पंचांगp, denom;
	पूर्णांक guard, rate_num, rate_dक्रमागत = 1, bits_per_symbol, nsegs;
	पूर्णांक पूर्णांकerleaving = 0, fft_भाग;

	अगर (layer >= 0) अणु
		ini_layer = layer;
		end_layer = layer + 1;
	पूर्ण अन्यथा अणु
		ini_layer = 0;
		end_layer = 3;
	पूर्ण

	चयन (c->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_4:
		guard = 4;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		guard = 8;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		guard = 16;
		अवरोध;
	शेष:
	हाल GUARD_INTERVAL_1_32:
		guard = 32;
		अवरोध;
	पूर्ण

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		fft_भाग = 4;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		fft_भाग = 2;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		fft_भाग = 1;
		अवरोध;
	पूर्ण

	denom = 0;
	क्रम (i = ini_layer; i < end_layer; i++) अणु
		nsegs = c->layer[i].segment_count;
		अगर (nsegs == 0 || nsegs > 13)
			जारी;

		चयन (c->layer[i].modulation) अणु
		हाल DQPSK:
		हाल QPSK:
			bits_per_symbol = 2;
			अवरोध;
		हाल QAM_16:
			bits_per_symbol = 4;
			अवरोध;
		शेष:
		हाल QAM_64:
			bits_per_symbol = 6;
			अवरोध;
		पूर्ण

		चयन (c->layer[i].fec) अणु
		हाल FEC_1_2:
			rate_num = 1;
			rate_dक्रमागत = 2;
			अवरोध;
		हाल FEC_2_3:
			rate_num = 2;
			rate_dक्रमागत = 3;
			अवरोध;
		हाल FEC_3_4:
			rate_num = 3;
			rate_dक्रमागत = 4;
			अवरोध;
		हाल FEC_5_6:
			rate_num = 5;
			rate_dक्रमागत = 6;
			अवरोध;
		शेष:
		हाल FEC_7_8:
			rate_num = 7;
			rate_dक्रमागत = 8;
			अवरोध;
		पूर्ण

		पूर्णांकerleaving = c->layer[i].पूर्णांकerleaving;

		denom += bits_per_symbol * rate_num * fft_भाग * nsegs * 384;
	पूर्ण

	/* If all goes wrong, रुको क्रम 1s क्रम the next stats */
	अगर (!denom)
		वापस 0;

	/* Estimate the period क्रम the total bit rate */
	समय_us = rate_dक्रमागत * (1008 * 1562500L);
	पंचांगp64 = समय_us;
	करो_भाग(पंचांगp64, guard);
	समय_us = समय_us + पंचांगp64;
	समय_us += denom / 2;
	करो_भाग(समय_us, denom);

	पंचांगp = 1008 * 96 * पूर्णांकerleaving;
	समय_us += पंचांगp + पंचांगp / guard;

	वापस समय_us;
पूर्ण

अटल पूर्णांक dib8000_get_stats(काष्ठा dvb_frontend *fe, क्रमागत fe_status stat)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &state->fe[0]->dtv_property_cache;
	पूर्णांक i;
	पूर्णांक show_per_stats = 0;
	u32 समय_us = 0, snr, val;
	u64 blocks;
	s32 db;
	u16 strength;

	/* Get Signal strength */
	dib8000_पढ़ो_संकेत_strength(fe, &strength);
	val = strength;
	db = पूर्णांकerpolate_value(val,
			       strength_to_db_table,
			       ARRAY_SIZE(strength_to_db_table)) - 131000;
	c->strength.stat[0].svalue = db;

	/* UCB/BER/CNR measures require lock */
	अगर (!(stat & FE_HAS_LOCK)) अणु
		c->cnr.len = 1;
		c->block_count.len = 1;
		c->block_error.len = 1;
		c->post_bit_error.len = 1;
		c->post_bit_count.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	/* Check अगर समय क्रम stats was elapsed */
	अगर (समय_after(jअगरfies, state->per_jअगरfies_stats)) अणु
		state->per_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies(1000);

		/* Get SNR */
		snr = dib8000_get_snr(fe);
		क्रम (i = 1; i < MAX_NUMBER_OF_FRONTENDS; i++) अणु
			अगर (state->fe[i])
				snr += dib8000_get_snr(state->fe[i]);
		पूर्ण
		snr = snr >> 16;

		अगर (snr) अणु
			snr = 10 * पूर्णांकlog10(snr);
			snr = (1000L * snr) >> 24;
		पूर्ण अन्यथा अणु
			snr = 0;
		पूर्ण
		c->cnr.stat[0].svalue = snr;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;

		/* Get UCB measures */
		dib8000_पढ़ो_unc_blocks(fe, &val);
		अगर (val < state->init_ucb)
			state->init_ucb += 0x100000000LL;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = val + state->init_ucb;

		/* Estimate the number of packets based on bitrate */
		अगर (!समय_us)
			समय_us = dib8000_get_समय_us(fe, -1);

		अगर (समय_us) अणु
			blocks = 1250000ULL * 1000000ULL;
			करो_भाग(blocks, समय_us * 8 * 204);
			c->block_count.stat[0].scale = FE_SCALE_COUNTER;
			c->block_count.stat[0].uvalue += blocks;
		पूर्ण

		show_per_stats = 1;
	पूर्ण

	/* Get post-BER measures */
	अगर (समय_after(jअगरfies, state->ber_jअगरfies_stats)) अणु
		समय_us = dib8000_get_समय_us(fe, -1);
		state->ber_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies((समय_us + 500) / 1000);

		dprपूर्णांकk("Next all layers stats available in %u us.\n", समय_us);

		dib8000_पढ़ो_ber(fe, &val);
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += val;

		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += 100000000;
	पूर्ण

	अगर (state->revision < 0x8002)
		वापस 0;

	c->block_error.len = 4;
	c->post_bit_error.len = 4;
	c->post_bit_count.len = 4;

	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित nsegs = c->layer[i].segment_count;

		अगर (nsegs == 0 || nsegs > 13)
			जारी;

		समय_us = 0;

		अगर (समय_after(jअगरfies, state->ber_jअगरfies_stats_layer[i])) अणु
			समय_us = dib8000_get_समय_us(fe, i);

			state->ber_jअगरfies_stats_layer[i] = jअगरfies + msecs_to_jअगरfies((समय_us + 500) / 1000);
			dprपूर्णांकk("Next layer %c  stats will be available in %u us\n",
				'A' + i, समय_us);

			val = dib8000_पढ़ो_word(state, per_layer_regs[i].ber);
			c->post_bit_error.stat[1 + i].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[1 + i].uvalue += val;

			c->post_bit_count.stat[1 + i].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[1 + i].uvalue += 100000000;
		पूर्ण

		अगर (show_per_stats) अणु
			val = dib8000_पढ़ो_word(state, per_layer_regs[i].per);

			c->block_error.stat[1 + i].scale = FE_SCALE_COUNTER;
			c->block_error.stat[1 + i].uvalue += val;

			अगर (!समय_us)
				समय_us = dib8000_get_समय_us(fe, i);
			अगर (समय_us) अणु
				blocks = 1250000ULL * 1000000ULL;
				करो_भाग(blocks, समय_us * 8 * 204);
				c->block_count.stat[0].scale = FE_SCALE_COUNTER;
				c->block_count.stat[0].uvalue += blocks;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib8000_set_slave_frontend(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend *fe_slave)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;
	u8 index_frontend = 1;

	जबतक ((index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य))
		index_frontend++;
	अगर (index_frontend < MAX_NUMBER_OF_FRONTENDS) अणु
		dprपूर्णांकk("set slave fe %p to index %i\n", fe_slave, index_frontend);
		state->fe[index_frontend] = fe_slave;
		वापस 0;
	पूर्ण

	dprपूर्णांकk("too many slave frontend\n");
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा dvb_frontend *dib8000_get_slave_frontend(काष्ठा dvb_frontend *fe, पूर्णांक slave_index)
अणु
	काष्ठा dib8000_state *state = fe->demodulator_priv;

	अगर (slave_index >= MAX_NUMBER_OF_FRONTENDS)
		वापस शून्य;
	वापस state->fe[slave_index];
पूर्ण

अटल पूर्णांक dib8000_i2c_क्रमागतeration(काष्ठा i2c_adapter *host, पूर्णांक no_of_demods,
		u8 शेष_addr, u8 first_addr, u8 is_dib8096p)
अणु
	पूर्णांक k = 0, ret = 0;
	u8 new_addr = 0;
	काष्ठा i2c_device client = अणु.adap = host पूर्ण;

	client.i2c_ग_लिखो_buffer = kzalloc(4, GFP_KERNEL);
	अगर (!client.i2c_ग_लिखो_buffer) अणु
		dprपूर्णांकk("%s: not enough memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	client.i2c_पढ़ो_buffer = kzalloc(4, GFP_KERNEL);
	अगर (!client.i2c_पढ़ो_buffer) अणु
		dprपूर्णांकk("%s: not enough memory\n", __func__);
		ret = -ENOMEM;
		जाओ error_memory_पढ़ो;
	पूर्ण
	client.i2c_buffer_lock = kzalloc(माप(काष्ठा mutex), GFP_KERNEL);
	अगर (!client.i2c_buffer_lock) अणु
		dprपूर्णांकk("%s: not enough memory\n", __func__);
		ret = -ENOMEM;
		जाओ error_memory_lock;
	पूर्ण
	mutex_init(client.i2c_buffer_lock);

	क्रम (k = no_of_demods - 1; k >= 0; k--) अणु
		/* designated i2c address */
		new_addr = first_addr + (k << 1);

		client.addr = new_addr;
		अगर (!is_dib8096p)
			dib8000_i2c_ग_लिखो16(&client, 1287, 0x0003);	/* sram lead in, rdy */
		अगर (dib8000_identअगरy(&client) == 0) अणु
			/* sram lead in, rdy */
			अगर (!is_dib8096p)
				dib8000_i2c_ग_लिखो16(&client, 1287, 0x0003);
			client.addr = शेष_addr;
			अगर (dib8000_identअगरy(&client) == 0) अणु
				dprपूर्णांकk("#%d: not identified\n", k);
				ret  = -EINVAL;
				जाओ error;
			पूर्ण
		पूर्ण

		/* start भागersity to pull_करोwn भाग_str - just क्रम i2c-क्रमागतeration */
		dib8000_i2c_ग_लिखो16(&client, 1286, (1 << 10) | (4 << 6));

		/* set new i2c address and क्रमce भागstart */
		dib8000_i2c_ग_लिखो16(&client, 1285, (new_addr << 2) | 0x2);
		client.addr = new_addr;
		dib8000_identअगरy(&client);

		dprपूर्णांकk("IC %d initialized (to i2c_address 0x%x)\n", k, new_addr);
	पूर्ण

	क्रम (k = 0; k < no_of_demods; k++) अणु
		new_addr = first_addr | (k << 1);
		client.addr = new_addr;

		// unक्रमce भागstr
		dib8000_i2c_ग_लिखो16(&client, 1285, new_addr << 2);

		/* deactivate भाग - it was just क्रम i2c-क्रमागतeration */
		dib8000_i2c_ग_लिखो16(&client, 1286, 0);
	पूर्ण

error:
	kमुक्त(client.i2c_buffer_lock);
error_memory_lock:
	kमुक्त(client.i2c_पढ़ो_buffer);
error_memory_पढ़ो:
	kमुक्त(client.i2c_ग_लिखो_buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक dib8000_fe_get_tune_settings(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	tune->step_size = 0;
	tune->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम dib8000_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib8000_state *st = fe->demodulator_priv;
	u8 index_frontend;

	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (st->fe[index_frontend] != शून्य); index_frontend++)
		dvb_frontend_detach(st->fe[index_frontend]);

	dibx000_निकास_i2c_master(&st->i2c_master);
	i2c_del_adapter(&st->dib8096p_tuner_adap);
	kमुक्त(st->fe[0]);
	kमुक्त(st);
पूर्ण

अटल काष्ठा i2c_adapter *dib8000_get_i2c_master(काष्ठा dvb_frontend *fe, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating)
अणु
	काष्ठा dib8000_state *st = fe->demodulator_priv;
	वापस dibx000_get_i2c_adapter(&st->i2c_master, पूर्णांकf, gating);
पूर्ण

अटल पूर्णांक dib8000_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	काष्ठा dib8000_state *st = fe->demodulator_priv;
	u16 val = dib8000_पढ़ो_word(st, 299) & 0xffef;
	val |= (onoff & 0x1) << 4;

	dprपूर्णांकk("pid filter enabled %d\n", onoff);
	वापस dib8000_ग_लिखो_word(st, 299, val);
पूर्ण

अटल पूर्णांक dib8000_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff)
अणु
	काष्ठा dib8000_state *st = fe->demodulator_priv;
	dprपूर्णांकk("Index %x, PID %d, OnOff %d\n", id, pid, onoff);
	वापस dib8000_ग_लिखो_word(st, 305 + id, onoff ? (1 << 13) | pid : 0);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dib8000_ops = अणु
	.delsys = अणु SYS_ISDBT पूर्ण,
	.info = अणु
		 .name = "DiBcom 8000 ISDB-T",
		 .frequency_min_hz =  44250 * kHz,
		 .frequency_max_hz = 867250 * kHz,
		 .frequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVERSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER | FE_CAN_HIERARCHY_AUTO,
		 पूर्ण,

	.release = dib8000_release,

	.init = dib8000_wakeup,
	.sleep = dib8000_sleep,

	.set_frontend = dib8000_set_frontend,
	.get_tune_settings = dib8000_fe_get_tune_settings,
	.get_frontend = dib8000_get_frontend,

	.पढ़ो_status = dib8000_पढ़ो_status,
	.पढ़ो_ber = dib8000_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib8000_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dib8000_पढ़ो_snr,
	.पढ़ो_ucblocks = dib8000_पढ़ो_unc_blocks,
पूर्ण;

अटल काष्ठा dvb_frontend *dib8000_init(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib8000_config *cfg)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा dib8000_state *state;

	dprपूर्णांकk("dib8000_init\n");

	state = kzalloc(माप(काष्ठा dib8000_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;
	fe = kzalloc(माप(काष्ठा dvb_frontend), GFP_KERNEL);
	अगर (fe == शून्य)
		जाओ error;

	स_नकल(&state->cfg, cfg, माप(काष्ठा dib8000_config));
	state->i2c.adap = i2c_adap;
	state->i2c.addr = i2c_addr;
	state->i2c.i2c_ग_लिखो_buffer = state->i2c_ग_लिखो_buffer;
	state->i2c.i2c_पढ़ो_buffer = state->i2c_पढ़ो_buffer;
	mutex_init(&state->i2c_buffer_lock);
	state->i2c.i2c_buffer_lock = &state->i2c_buffer_lock;
	state->gpio_val = cfg->gpio_val;
	state->gpio_dir = cfg->gpio_dir;

	/* Ensure the output mode reमुख्यs at the previous शेष अगर it's
	 * not specअगरically set by the caller.
	 */
	अगर ((state->cfg.output_mode != OUTMODE_MPEG2_SERIAL) && (state->cfg.output_mode != OUTMODE_MPEG2_PAR_GATED_CLK))
		state->cfg.output_mode = OUTMODE_MPEG2_FIFO;

	state->fe[0] = fe;
	fe->demodulator_priv = state;
	स_नकल(&state->fe[0]->ops, &dib8000_ops, माप(काष्ठा dvb_frontend_ops));

	state->timf_शेष = cfg->pll->timf;

	अगर (dib8000_identअगरy(&state->i2c) == 0)
		जाओ error;

	dibx000_init_i2c_master(&state->i2c_master, DIB8000, state->i2c.adap, state->i2c.addr);

	/* init 8096p tuner adapter */
	strscpy(state->dib8096p_tuner_adap.name, "DiB8096P tuner interface",
		माप(state->dib8096p_tuner_adap.name));
	state->dib8096p_tuner_adap.algo = &dib8096p_tuner_xfer_algo;
	state->dib8096p_tuner_adap.algo_data = शून्य;
	state->dib8096p_tuner_adap.dev.parent = state->i2c.adap->dev.parent;
	i2c_set_adapdata(&state->dib8096p_tuner_adap, state);
	i2c_add_adapter(&state->dib8096p_tuner_adap);

	dib8000_reset(fe);

	dib8000_ग_लिखो_word(state, 285, (dib8000_पढ़ो_word(state, 285) & ~0x60) | (3 << 5));	/* ber_rs_len = 3 */
	state->current_demod_bw = 6000;

	वापस fe;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

व्योम *dib8000_attach(काष्ठा dib8000_ops *ops)
अणु
	अगर (!ops)
		वापस शून्य;

	ops->pwm_agc_reset = dib8000_pwm_agc_reset;
	ops->get_dc_घातer = dib8090p_get_dc_घातer;
	ops->set_gpio = dib8000_set_gpio;
	ops->get_slave_frontend = dib8000_get_slave_frontend;
	ops->set_tune_state = dib8000_set_tune_state;
	ops->pid_filter_ctrl = dib8000_pid_filter_ctrl;
	ops->get_adc_घातer = dib8000_get_adc_घातer;
	ops->update_pll = dib8000_update_pll;
	ops->tuner_sleep = dib8096p_tuner_sleep;
	ops->get_tune_state = dib8000_get_tune_state;
	ops->get_i2c_tuner = dib8096p_get_i2c_tuner;
	ops->set_slave_frontend = dib8000_set_slave_frontend;
	ops->pid_filter = dib8000_pid_filter;
	ops->ctrl_timf = dib8000_ctrl_timf;
	ops->init = dib8000_init;
	ops->get_i2c_master = dib8000_get_i2c_master;
	ops->i2c_क्रमागतeration = dib8000_i2c_क्रमागतeration;
	ops->set_wbd_ref = dib8000_set_wbd_ref;

	वापस ops;
पूर्ण
EXPORT_SYMBOL(dib8000_attach);

MODULE_AUTHOR("Olivier Grenie <Olivier.Grenie@parrot.com, Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the DiBcom 8000 ISDB-T demodulator");
MODULE_LICENSE("GPL");
