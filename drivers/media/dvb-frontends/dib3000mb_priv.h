<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * dib3000mb_priv.h
 *
 * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@posteo.de)
 *
 * क्रम more inक्रमmation see dib3000mb.c .
 */

#अगर_अघोषित __DIB3000MB_PRIV_H_INCLUDED__
#घोषणा __DIB3000MB_PRIV_H_INCLUDED__

/* handy लघुcuts */
#घोषणा rd(reg) dib3000_पढ़ो_reg(state,reg)

#घोषणा wr(reg,val) अगर (dib3000_ग_लिखो_reg(state,reg,val)) \
	अणु pr_err("while sending 0x%04x to 0x%04x.", val, reg); वापस -EREMOTEIO; पूर्ण

#घोषणा wr_क्रमeach(a,v) अणु पूर्णांक i; \
	अगर (माप(a) != माप(v)) \
		pr_err("sizeof: %zu %zu is different", माप(a), माप(v));\
	क्रम (i=0; i < माप(a)/माप(u16); i++) \
		wr(a[i],v[i]); \
	पूर्ण

#घोषणा set_or(reg,val) wr(reg,rd(reg) | val)

#घोषणा set_and(reg,val) wr(reg,rd(reg) & val)

/* debug */

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug & level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

/* mask क्रम enabling a specअगरic pid क्रम the pid_filter */
#घोषणा DIB3000_ACTIVATE_PID_FILTERING	(0x2000)

/* common values क्रम tuning */
#घोषणा DIB3000_ALPHA_0					(     0)
#घोषणा DIB3000_ALPHA_1					(     1)
#घोषणा DIB3000_ALPHA_2					(     2)
#घोषणा DIB3000_ALPHA_4					(     4)

#घोषणा DIB3000_CONSTELLATION_QPSK		(     0)
#घोषणा DIB3000_CONSTELLATION_16QAM		(     1)
#घोषणा DIB3000_CONSTELLATION_64QAM		(     2)

#घोषणा DIB3000_GUARD_TIME_1_32			(     0)
#घोषणा DIB3000_GUARD_TIME_1_16			(     1)
#घोषणा DIB3000_GUARD_TIME_1_8			(     2)
#घोषणा DIB3000_GUARD_TIME_1_4			(     3)

#घोषणा DIB3000_TRANSMISSION_MODE_2K	(     0)
#घोषणा DIB3000_TRANSMISSION_MODE_8K	(     1)

#घोषणा DIB3000_SELECT_LP				(     0)
#घोषणा DIB3000_SELECT_HP				(     1)

#घोषणा DIB3000_FEC_1_2					(     1)
#घोषणा DIB3000_FEC_2_3					(     2)
#घोषणा DIB3000_FEC_3_4					(     3)
#घोषणा DIB3000_FEC_5_6					(     5)
#घोषणा DIB3000_FEC_7_8					(     7)

#घोषणा DIB3000_HRCH_OFF				(     0)
#घोषणा DIB3000_HRCH_ON					(     1)

#घोषणा DIB3000_DDS_INVERSION_OFF		(     0)
#घोषणा DIB3000_DDS_INVERSION_ON		(     1)

#घोषणा DIB3000_TUNER_WRITE_ENABLE(a)	(0xffff & (a << 8))
#घोषणा DIB3000_TUNER_WRITE_DISABLE(a)	(0xffff & ((a << 8) | (1 << 7)))

#घोषणा DIB3000_REG_MANUFACTOR_ID		(  1025)
#घोषणा DIB3000_I2C_ID_DIBCOM			(0x01b3)

#घोषणा DIB3000_REG_DEVICE_ID			(  1026)
#घोषणा DIB3000MB_DEVICE_ID				(0x3000)
#घोषणा DIB3000MC_DEVICE_ID				(0x3001)
#घोषणा DIB3000P_DEVICE_ID				(0x3002)

/* frontend state */
काष्ठा dib3000_state अणु
	काष्ठा i2c_adapter* i2c;

/* configuration settings */
	काष्ठा dib3000_config config;

	काष्ठा dvb_frontend frontend;
	पूर्णांक timing_offset;
	पूर्णांक timing_offset_comp_करोne;

	u32 last_tuned_bw;
	u32 last_tuned_freq;
पूर्ण;

/* रेजिस्टर addresses and some of their शेष values */

/* restart subप्रणालीs */
#घोषणा DIB3000MB_REG_RESTART			(     0)

#घोषणा DIB3000MB_RESTART_OFF			(     0)
#घोषणा DIB3000MB_RESTART_AUTO_SEARCH		(1 << 1)
#घोषणा DIB3000MB_RESTART_CTRL				(1 << 2)
#घोषणा DIB3000MB_RESTART_AGC				(1 << 3)

/* FFT size */
#घोषणा DIB3000MB_REG_FFT				(     1)

/* Guard समय */
#घोषणा DIB3000MB_REG_GUARD_TIME		(     2)

/* QAM */
#घोषणा DIB3000MB_REG_QAM				(     3)

/* Alpha coefficient high priority Viterbi algorithm */
#घोषणा DIB3000MB_REG_VIT_ALPHA			(     4)

/* spectrum inversion */
#घोषणा DIB3000MB_REG_DDS_INV			(     5)

/* DDS frequency value (IF position) ad ? values करोn't match reg_3000mb.txt */
#घोषणा DIB3000MB_REG_DDS_FREQ_MSB		(     6)
#घोषणा DIB3000MB_REG_DDS_FREQ_LSB		(     7)
#घोषणा DIB3000MB_DDS_FREQ_MSB				(   178)
#घोषणा DIB3000MB_DDS_FREQ_LSB				(  8990)

/* timing frequency (carrier spacing) */
अटल u16 dib3000mb_reg_timing_freq[] = अणु 8,9 पूर्ण;
अटल u16 dib3000mb_timing_freq[][2] = अणु
	अणु 126 , 48873 पूर्ण, /* 6 MHz */
	अणु 147 , 57019 पूर्ण, /* 7 MHz */
	अणु 168 , 65164 पूर्ण, /* 8 MHz */
पूर्ण;

/* impulse noise parameter */
/* 36 ??? */

अटल u16 dib3000mb_reg_impulse_noise[] = अणु 10,11,12,15,36 पूर्ण;

क्रमागत dib3000mb_impulse_noise_type अणु
	DIB3000MB_IMPNOISE_OFF,
	DIB3000MB_IMPNOISE_MOBILE,
	DIB3000MB_IMPNOISE_FIXED,
	DIB3000MB_IMPNOISE_DEFAULT
पूर्ण;

अटल u16 dib3000mb_impulse_noise_values[][5] = अणु
	अणु 0x0000, 0x0004, 0x0014, 0x01ff, 0x0399 पूर्ण, /* off */
	अणु 0x0001, 0x0004, 0x0014, 0x01ff, 0x037b पूर्ण, /* mobile */
	अणु 0x0001, 0x0004, 0x0020, 0x01bd, 0x0399 पूर्ण, /* fixed */
	अणु 0x0000, 0x0002, 0x000a, 0x01ff, 0x0399 पूर्ण, /* शेष */
पूर्ण;

/*
 * Dual Automatic-Gain-Control
 * - gains RF in tuner (AGC1)
 * - gains IF after filtering (AGC2)
 */

/* also from 16 to 18 */
अटल u16 dib3000mb_reg_agc_gain[] = अणु
	19,20,21,22,23,24,25,26,27,28,29,30,31,32
पूर्ण;

अटल u16 dib3000mb_शेष_agc_gain[] =
	अणु 0x0001, 52429,   623, 128, 166, 195, 61,   /* RF ??? */
	  0x0001, 53766, 38011,   0,  90,  33, 23 पूर्ण; /* IF ??? */

/* phase noise */
/* 36 is set when setting the impulse noise */
अटल u16 dib3000mb_reg_phase_noise[] = अणु 33,34,35,37,38 पूर्ण;

अटल u16 dib3000mb_शेष_noise_phase[] = अणु 2, 544, 0, 5, 4 पूर्ण;

/* lock duration */
अटल u16 dib3000mb_reg_lock_duration[] = अणु 39,40 पूर्ण;
अटल u16 dib3000mb_शेष_lock_duration[] = अणु 135, 135 पूर्ण;

/* AGC loop bandwidth */
अटल u16 dib3000mb_reg_agc_bandwidth[] = अणु 43,44,45,46,47,48,49,50 पूर्ण;

अटल u16 dib3000mb_agc_bandwidth_low[]  =
	अणु 2088, 10, 2088, 10, 3448, 5, 3448, 5 पूर्ण;
अटल u16 dib3000mb_agc_bandwidth_high[] =
	अणु 2349,  5, 2349,  5, 2586, 2, 2586, 2 पूर्ण;

/*
 * lock0 definition (coff_lock)
 */
#घोषणा DIB3000MB_REG_LOCK0_MASK		(    51)
#घोषणा DIB3000MB_LOCK0_DEFAULT				(     4)

/*
 * lock1 definition (cpil_lock)
 * क्रम स्वतः search
 * which values hide behind the lock masks
 */
#घोषणा DIB3000MB_REG_LOCK1_MASK		(    52)
#घोषणा DIB3000MB_LOCK1_SEARCH_4			(0x0004)
#घोषणा DIB3000MB_LOCK1_SEARCH_2048			(0x0800)
#घोषणा DIB3000MB_LOCK1_DEFAULT				(0x0001)

/*
 * lock2 definition (fec_lock) */
#घोषणा DIB3000MB_REG_LOCK2_MASK		(    53)
#घोषणा DIB3000MB_LOCK2_DEFAULT				(0x0080)

/*
 * SEQ ? what was that again ... :)
 * changes when, inversion, guard समय and fft is
 * either स्वतःmatically detected or not
 */
#घोषणा DIB3000MB_REG_SEQ				(    54)

/* bandwidth */
अटल u16 dib3000mb_reg_bandwidth[] = अणु 55,56,57,58,59,60,61,62,63,64,65,66,67 पूर्ण;
अटल u16 dib3000mb_bandwidth_6mhz[] =
	अणु 0, 33, 53312, 112, 46635, 563, 36565, 0, 1000, 0, 1010, 1, 45264 पूर्ण;

अटल u16 dib3000mb_bandwidth_7mhz[] =
	अणु 0, 28, 64421,  96, 39973, 483,  3255, 0, 1000, 0, 1010, 1, 45264 पूर्ण;

अटल u16 dib3000mb_bandwidth_8mhz[] =
	अणु 0, 25, 23600,  84, 34976, 422, 43808, 0, 1000, 0, 1010, 1, 45264 पूर्ण;

#घोषणा DIB3000MB_REG_UNK_68				(    68)
#घोषणा DIB3000MB_UNK_68						(     0)

#घोषणा DIB3000MB_REG_UNK_69				(    69)
#घोषणा DIB3000MB_UNK_69						(     0)

#घोषणा DIB3000MB_REG_UNK_71				(    71)
#घोषणा DIB3000MB_UNK_71						(     0)

#घोषणा DIB3000MB_REG_UNK_77				(    77)
#घोषणा DIB3000MB_UNK_77						(     6)

#घोषणा DIB3000MB_REG_UNK_78				(    78)
#घोषणा DIB3000MB_UNK_78						(0x0080)

/* isi */
#घोषणा DIB3000MB_REG_ISI				(    79)
#घोषणा DIB3000MB_ISI_ACTIVATE				(     0)
#घोषणा DIB3000MB_ISI_INHIBIT				(     1)

/* sync impovement */
#घोषणा DIB3000MB_REG_SYNC_IMPROVEMENT	(    84)
#घोषणा DIB3000MB_SYNC_IMPROVE_2K_1_8		(     3)
#घोषणा DIB3000MB_SYNC_IMPROVE_DEFAULT		(     0)

/* phase noise compensation inhibition */
#घोषणा DIB3000MB_REG_PHASE_NOISE		(    87)
#घोषणा DIB3000MB_PHASE_NOISE_DEFAULT	(     0)

#घोषणा DIB3000MB_REG_UNK_92				(    92)
#घोषणा DIB3000MB_UNK_92						(0x0080)

#घोषणा DIB3000MB_REG_UNK_96				(    96)
#घोषणा DIB3000MB_UNK_96						(0x0010)

#घोषणा DIB3000MB_REG_UNK_97				(    97)
#घोषणा DIB3000MB_UNK_97						(0x0009)

/* mobile mode ??? */
#घोषणा DIB3000MB_REG_MOBILE_MODE		(   101)
#घोषणा DIB3000MB_MOBILE_MODE_ON			(     1)
#घोषणा DIB3000MB_MOBILE_MODE_OFF			(     0)

#घोषणा DIB3000MB_REG_UNK_106			(   106)
#घोषणा DIB3000MB_UNK_106					(0x0080)

#घोषणा DIB3000MB_REG_UNK_107			(   107)
#घोषणा DIB3000MB_UNK_107					(0x0080)

#घोषणा DIB3000MB_REG_UNK_108			(   108)
#घोषणा DIB3000MB_UNK_108					(0x0080)

/* fft */
#घोषणा DIB3000MB_REG_UNK_121			(   121)
#घोषणा DIB3000MB_UNK_121_2K				(     7)
#घोषणा DIB3000MB_UNK_121_DEFAULT			(     5)

#घोषणा DIB3000MB_REG_UNK_122			(   122)
#घोषणा DIB3000MB_UNK_122					(  2867)

/* QAM क्रम mobile mode */
#घोषणा DIB3000MB_REG_MOBILE_MODE_QAM	(   126)
#घोषणा DIB3000MB_MOBILE_MODE_QAM_64		(     3)
#घोषणा DIB3000MB_MOBILE_MODE_QAM_QPSK_16	(     1)
#घोषणा DIB3000MB_MOBILE_MODE_QAM_OFF		(     0)

/*
 * data भागersity when having more than one chip on-board
 * see also DIB3000MB_OUTPUT_MODE_DATA_DIVERSITY
 */
#घोषणा DIB3000MB_REG_DATA_IN_DIVERSITY		(   127)
#घोषणा DIB3000MB_DATA_DIVERSITY_IN_OFF			(     0)
#घोषणा DIB3000MB_DATA_DIVERSITY_IN_ON			(     2)

/* vit hrch */
#घोषणा DIB3000MB_REG_VIT_HRCH			(   128)

/* vit code rate */
#घोषणा DIB3000MB_REG_VIT_CODE_RATE		(   129)

/* vit select hp */
#घोषणा DIB3000MB_REG_VIT_HP			(   130)

/* समय frame क्रम Bit-Error-Rate calculation */
#घोषणा DIB3000MB_REG_BERLEN			(   135)
#घोषणा DIB3000MB_BERLEN_LONG				(     0)
#घोषणा DIB3000MB_BERLEN_DEFAULT			(     1)
#घोषणा DIB3000MB_BERLEN_MEDIUM				(     2)
#घोषणा DIB3000MB_BERLEN_SHORT				(     3)

/* 142 - 152 FIFO parameters
 * which is what ?
 */

#घोषणा DIB3000MB_REG_FIFO_142			(   142)
#घोषणा DIB3000MB_FIFO_142					(     0)

/* MPEG2 TS output mode */
#घोषणा DIB3000MB_REG_MPEG2_OUT_MODE	(   143)
#घोषणा DIB3000MB_MPEG2_OUT_MODE_204		(     0)
#घोषणा DIB3000MB_MPEG2_OUT_MODE_188		(     1)

#घोषणा DIB3000MB_REG_PID_PARSE			(   144)
#घोषणा DIB3000MB_PID_PARSE_INHIBIT		(     0)
#घोषणा DIB3000MB_PID_PARSE_ACTIVATE	(     1)

#घोषणा DIB3000MB_REG_FIFO				(   145)
#घोषणा DIB3000MB_FIFO_INHIBIT				(     1)
#घोषणा DIB3000MB_FIFO_ACTIVATE				(     0)

#घोषणा DIB3000MB_REG_FIFO_146			(   146)
#घोषणा DIB3000MB_FIFO_146					(     3)

#घोषणा DIB3000MB_REG_FIFO_147			(   147)
#घोषणा DIB3000MB_FIFO_147					(0x0100)

/*
 * pidfilter
 * it is not a hardware pidfilter but a filter which drops all pids
 * except the ones set. Necessary because of the limited USB1.1 bandwidth.
 * regs 153-168
 */

#घोषणा DIB3000MB_REG_FIRST_PID			(   153)
#घोषणा DIB3000MB_NUM_PIDS				(    16)

/*
 * output mode
 * USB devices have to use 'slave'-mode
 * see also DIB3000MB_REG_ELECT_OUT_MODE
 */
#घोषणा DIB3000MB_REG_OUTPUT_MODE		(   169)
#घोषणा DIB3000MB_OUTPUT_MODE_GATED_CLK		(     0)
#घोषणा DIB3000MB_OUTPUT_MODE_CONT_CLK		(     1)
#घोषणा DIB3000MB_OUTPUT_MODE_SERIAL		(     2)
#घोषणा DIB3000MB_OUTPUT_MODE_DATA_DIVERSITY	(     5)
#घोषणा DIB3000MB_OUTPUT_MODE_SLAVE			(     6)

/* irq event mask */
#घोषणा DIB3000MB_REG_IRQ_EVENT_MASK		(   170)
#घोषणा DIB3000MB_IRQ_EVENT_MASK				(     0)

/* filter coefficients */
अटल u16 dib3000mb_reg_filter_coeffs[] = अणु
	171, 172, 173, 174, 175, 176, 177, 178,
	179, 180, 181, 182, 183, 184, 185, 186,
	188, 189, 190, 191, 192, 194
पूर्ण;

अटल u16 dib3000mb_filter_coeffs[] = अणु
	 226,  160,   29,
	 979,  998,   19,
	  22, 1019, 1006,
	1022,   12,    6,
	1017, 1017,    3,
	   6,       1019,
	1021,    2,    3,
	   1,          0,
पूर्ण;

/*
 * mobile algorithm (when you are moving with your device)
 * but not faster than 90 km/h
 */
#घोषणा DIB3000MB_REG_MOBILE_ALGO		(   195)
#घोषणा DIB3000MB_MOBILE_ALGO_ON			(     0)
#घोषणा DIB3000MB_MOBILE_ALGO_OFF			(     1)

/* multiple demodulators algorithm */
#घोषणा DIB3000MB_REG_MULTI_DEMOD_MSB	(   206)
#घोषणा DIB3000MB_REG_MULTI_DEMOD_LSB	(   207)

/* terminator, no more demods */
#घोषणा DIB3000MB_MULTI_DEMOD_MSB			( 32767)
#घोषणा DIB3000MB_MULTI_DEMOD_LSB			(  4095)

/* bring the device पूर्णांकo a known  */
#घोषणा DIB3000MB_REG_RESET_DEVICE		(  1024)
#घोषणा DIB3000MB_RESET_DEVICE				(0x812c)
#घोषणा DIB3000MB_RESET_DEVICE_RST			(     0)

/* hardware घड़ी configuration */
#घोषणा DIB3000MB_REG_CLOCK				(  1027)
#घोषणा DIB3000MB_CLOCK_DEFAULT				(0x9000)
#घोषणा DIB3000MB_CLOCK_DIVERSITY			(0x92b0)

/* घातer करोwn config */
#घोषणा DIB3000MB_REG_POWER_CONTROL		(  1028)
#घोषणा DIB3000MB_POWER_DOWN				(     1)
#घोषणा DIB3000MB_POWER_UP					(     0)

/* electrical output mode */
#घोषणा DIB3000MB_REG_ELECT_OUT_MODE	(  1029)
#घोषणा DIB3000MB_ELECT_OUT_MODE_OFF		(     0)
#घोषणा DIB3000MB_ELECT_OUT_MODE_ON			(     1)

/* set the tuner i2c address */
#घोषणा DIB3000MB_REG_TUNER				(  1089)

/* monitoring रेजिस्टरs (पढ़ो only) */

/* agc loop locked (size: 1) */
#घोषणा DIB3000MB_REG_AGC_LOCK			(   324)

/* agc घातer (size: 16) */
#घोषणा DIB3000MB_REG_AGC_POWER			(   325)

/* agc1 value (16) */
#घोषणा DIB3000MB_REG_AGC1_VALUE		(   326)

/* agc2 value (16) */
#घोषणा DIB3000MB_REG_AGC2_VALUE		(   327)

/* total RF घातer (16), can be used क्रम संकेत strength */
#घोषणा DIB3000MB_REG_RF_POWER			(   328)

/* dds_frequency with offset (24) */
#घोषणा DIB3000MB_REG_DDS_VALUE_MSB		(   339)
#घोषणा DIB3000MB_REG_DDS_VALUE_LSB		(   340)

/* timing offset चिन्हित (24) */
#घोषणा DIB3000MB_REG_TIMING_OFFSET_MSB	(   341)
#घोषणा DIB3000MB_REG_TIMING_OFFSET_LSB	(   342)

/* fft start position (13) */
#घोषणा DIB3000MB_REG_FFT_WINDOW_POS	(   353)

/* carriers locked (1) */
#घोषणा DIB3000MB_REG_CARRIER_LOCK		(   355)

/* noise घातer (24) */
#घोषणा DIB3000MB_REG_NOISE_POWER_MSB	(   372)
#घोषणा DIB3000MB_REG_NOISE_POWER_LSB	(   373)

#घोषणा DIB3000MB_REG_MOBILE_NOISE_MSB	(   374)
#घोषणा DIB3000MB_REG_MOBILE_NOISE_LSB	(   375)

/*
 * संकेत घातer (16), this and the above can be
 * used to calculate the संकेत/noise - ratio
 */
#घोषणा DIB3000MB_REG_SIGNAL_POWER		(   380)

/* mer (24) */
#घोषणा DIB3000MB_REG_MER_MSB			(   381)
#घोषणा DIB3000MB_REG_MER_LSB			(   382)

/*
 * Transmission Parameter Signalling (TPS)
 * the following रेजिस्टरs can be used to get TPS-inक्रमmation.
 * The values are according to the DVB-T standard.
 */

/* TPS locked (1) */
#घोषणा DIB3000MB_REG_TPS_LOCK			(   394)

/* QAM from TPS (2) (values according to DIB3000MB_REG_QAM) */
#घोषणा DIB3000MB_REG_TPS_QAM			(   398)

/* hierarchy from TPS (1) */
#घोषणा DIB3000MB_REG_TPS_HRCH			(   399)

/* alpha from TPS (3) (values according to DIB3000MB_REG_VIT_ALPHA) */
#घोषणा DIB3000MB_REG_TPS_VIT_ALPHA		(   400)

/* code rate high priority from TPS (3) (values according to DIB3000MB_FEC_*) */
#घोषणा DIB3000MB_REG_TPS_CODE_RATE_HP	(   401)

/* code rate low priority from TPS (3) अगर DIB3000MB_REG_TPS_VIT_ALPHA */
#घोषणा DIB3000MB_REG_TPS_CODE_RATE_LP	(   402)

/* guard समय from TPS (2) (values according to DIB3000MB_REG_GUARD_TIME */
#घोषणा DIB3000MB_REG_TPS_GUARD_TIME	(   403)

/* fft size from TPS (2) (values according to DIB3000MB_REG_FFT) */
#घोषणा DIB3000MB_REG_TPS_FFT			(   404)

/* cell id from TPS (16) */
#घोषणा DIB3000MB_REG_TPS_CELL_ID		(   406)

/* TPS (68) */
#घोषणा DIB3000MB_REG_TPS_1				(   408)
#घोषणा DIB3000MB_REG_TPS_2				(   409)
#घोषणा DIB3000MB_REG_TPS_3				(   410)
#घोषणा DIB3000MB_REG_TPS_4				(   411)
#घोषणा DIB3000MB_REG_TPS_5				(   412)

/* bit error rate (beक्रमe RS correction) (21) */
#घोषणा DIB3000MB_REG_BER_MSB			(   414)
#घोषणा DIB3000MB_REG_BER_LSB			(   415)

/* packet error rate (uncorrected TS packets) (16) */
#घोषणा DIB3000MB_REG_PACKET_ERROR_RATE	(   417)

/* uncorrected packet count (16) */
#घोषणा DIB3000MB_REG_UNC				(   420)

/* viterbi locked (1) */
#घोषणा DIB3000MB_REG_VIT_LCK			(   421)

/* viterbi inidcator (16) */
#घोषणा DIB3000MB_REG_VIT_INDICATOR		(   422)

/* transport stream sync lock (1) */
#घोषणा DIB3000MB_REG_TS_SYNC_LOCK		(   423)

/* transport stream RS lock (1) */
#घोषणा DIB3000MB_REG_TS_RS_LOCK		(   424)

/* lock mask 0 value (1) */
#घोषणा DIB3000MB_REG_LOCK0_VALUE		(   425)

/* lock mask 1 value (1) */
#घोषणा DIB3000MB_REG_LOCK1_VALUE		(   426)

/* lock mask 2 value (1) */
#घोषणा DIB3000MB_REG_LOCK2_VALUE		(   427)

/* पूर्णांकerrupt pending क्रम स्वतः search */
#घोषणा DIB3000MB_REG_AS_IRQ_PENDING	(   434)

#पूर्ण_अगर
