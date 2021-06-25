<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv0900_priv.h
 *
 * Driver क्रम ST STV0900 satellite demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित STV0900_PRIV_H
#घोषणा STV0900_PRIV_H

#समावेश <linux/i2c.h>

#घोषणा INRANGE(X, Y, Z) ((((X) <= (Y)) && ((Y) <= (Z))) \
		|| (((Z) <= (Y)) && ((Y) <= (X))) ? 1 : 0)

#अगर_अघोषित MAKEWORD
#घोषणा MAKEWORD(X, Y) (((X) << 8) + (Y))
#पूर्ण_अगर

#घोषणा LSB(X) (((X) & 0xFF))
#घोषणा MSB(Y) (((Y) >> 8) & 0xFF)

#अगर_अघोषित TRUE
#घोषणा TRUE (1 == 1)
#पूर्ण_अगर
#अगर_अघोषित FALSE
#घोषणा FALSE (!TRUE)
#पूर्ण_अगर

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (stvdebug) \
			prपूर्णांकk(KERN_DEBUG args); \
	पूर्ण जबतक (0)

#घोषणा STV0900_MAXLOOKUPSIZE 500
#घोषणा STV0900_BLIND_SEARCH_AGC2_TH 700
#घोषणा STV0900_BLIND_SEARCH_AGC2_TH_CUT30 1400
#घोषणा IQPOWER_THRESHOLD  30

/* One poपूर्णांक of the lookup table */
काष्ठा stv000_lookpoपूर्णांक अणु
	s32 realval;/* real value */
	s32 regval;/* binary value */
पूर्ण;

/* Lookup table definition */
काष्ठा stv0900_tableअणु
	s32 size;/* Size of the lookup table */
	काष्ठा stv000_lookpoपूर्णांक table[STV0900_MAXLOOKUPSIZE];/* Lookup table */
पूर्ण;

क्रमागत fe_stv0900_error अणु
	STV0900_NO_ERROR = 0,
	STV0900_INVALID_HANDLE,
	STV0900_BAD_PARAMETER,
	STV0900_I2C_ERROR,
	STV0900_SEARCH_FAILED,
पूर्ण;

क्रमागत fe_stv0900_घड़ी_प्रकारype अणु
	STV0900_USE_REGISTERS_DEFAULT,
	STV0900_SERIAL_PUNCT_CLOCK,/*Serial punctured घड़ी */
	STV0900_SERIAL_CONT_CLOCK,/*Serial जारीs घड़ी */
	STV0900_PARALLEL_PUNCT_CLOCK,/*Parallel punctured घड़ी */
	STV0900_DVBCI_CLOCK/*Parallel जारीs घड़ी : DVBCI */
पूर्ण;

क्रमागत fe_stv0900_search_state अणु
	STV0900_SEARCH = 0,
	STV0900_PLH_DETECTED,
	STV0900_DVBS2_FOUND,
	STV0900_DVBS_FOUND

पूर्ण;

क्रमागत fe_stv0900_ldpc_state अणु
	STV0900_PATH1_OFF_PATH2_OFF = 0,
	STV0900_PATH1_ON_PATH2_OFF = 1,
	STV0900_PATH1_OFF_PATH2_ON = 2,
	STV0900_PATH1_ON_PATH2_ON = 3
पूर्ण;

क्रमागत fe_stv0900_संकेत_type अणु
	STV0900_NOAGC1 = 0,
	STV0900_AGC1OK,
	STV0900_NOTIMING,
	STV0900_ANALOGCARRIER,
	STV0900_TIMINGOK,
	STV0900_NOAGC2,
	STV0900_AGC2OK,
	STV0900_NOCARRIER,
	STV0900_CARRIEROK,
	STV0900_NODATA,
	STV0900_DATAOK,
	STV0900_OUTOFRANGE,
	STV0900_RANGEOK
पूर्ण;

क्रमागत fe_stv0900_demod_num अणु
	STV0900_DEMOD_1,
	STV0900_DEMOD_2
पूर्ण;

क्रमागत fe_stv0900_tracking_standard अणु
	STV0900_DVBS1_STANDARD,/* Found Standard*/
	STV0900_DVBS2_STANDARD,
	STV0900_DSS_STANDARD,
	STV0900_TURBOCODE_STANDARD,
	STV0900_UNKNOWN_STANDARD
पूर्ण;

क्रमागत fe_stv0900_search_standard अणु
	STV0900_AUTO_SEARCH,
	STV0900_SEARCH_DVBS1,/* Search Standard*/
	STV0900_SEARCH_DVBS2,
	STV0900_SEARCH_DSS,
	STV0900_SEARCH_TURBOCODE
पूर्ण;

क्रमागत fe_stv0900_search_algo अणु
	STV0900_BLIND_SEARCH,/* offset freq and SR are Unknown */
	STV0900_COLD_START,/* only the SR is known */
	STV0900_WARM_START/* offset freq and SR are known */
पूर्ण;

क्रमागत fe_stv0900_modulation अणु
	STV0900_QPSK,
	STV0900_8PSK,
	STV0900_16APSK,
	STV0900_32APSK,
	STV0900_UNKNOWN
पूर्ण;

क्रमागत fe_stv0900_modcode अणु
	STV0900_DUMMY_PLF,
	STV0900_QPSK_14,
	STV0900_QPSK_13,
	STV0900_QPSK_25,
	STV0900_QPSK_12,
	STV0900_QPSK_35,
	STV0900_QPSK_23,
	STV0900_QPSK_34,
	STV0900_QPSK_45,
	STV0900_QPSK_56,
	STV0900_QPSK_89,
	STV0900_QPSK_910,
	STV0900_8PSK_35,
	STV0900_8PSK_23,
	STV0900_8PSK_34,
	STV0900_8PSK_56,
	STV0900_8PSK_89,
	STV0900_8PSK_910,
	STV0900_16APSK_23,
	STV0900_16APSK_34,
	STV0900_16APSK_45,
	STV0900_16APSK_56,
	STV0900_16APSK_89,
	STV0900_16APSK_910,
	STV0900_32APSK_34,
	STV0900_32APSK_45,
	STV0900_32APSK_56,
	STV0900_32APSK_89,
	STV0900_32APSK_910,
	STV0900_MODCODE_UNKNOWN
पूर्ण;

क्रमागत fe_stv0900_fec अणु/*DVBS1, DSS and turbo code puncture rate*/
	STV0900_FEC_1_2 = 0,
	STV0900_FEC_2_3,
	STV0900_FEC_3_4,
	STV0900_FEC_4_5,/*क्रम turbo code only*/
	STV0900_FEC_5_6,
	STV0900_FEC_6_7,/*क्रम DSS only */
	STV0900_FEC_7_8,
	STV0900_FEC_8_9,/*क्रम turbo code only*/
	STV0900_FEC_UNKNOWN
पूर्ण;

क्रमागत fe_stv0900_frame_length अणु
	STV0900_LONG_FRAME,
	STV0900_SHORT_FRAME
पूर्ण;

क्रमागत fe_stv0900_pilot अणु
	STV0900_PILOTS_OFF,
	STV0900_PILOTS_ON
पूर्ण;

क्रमागत fe_stv0900_rolloff अणु
	STV0900_35,
	STV0900_25,
	STV0900_20
पूर्ण;

क्रमागत fe_stv0900_search_iq अणु
	STV0900_IQ_AUTO,
	STV0900_IQ_AUTO_NORMAL_FIRST,
	STV0900_IQ_FORCE_NORMAL,
	STV0900_IQ_FORCE_SWAPPED
पूर्ण;

क्रमागत stv0900_iq_inversion अणु
	STV0900_IQ_NORMAL,
	STV0900_IQ_SWAPPED
पूर्ण;

क्रमागत fe_stv0900_diseqc_mode अणु
	STV0900_22KHZ_Continues = 0,
	STV0900_DISEQC_2_3_PWM = 2,
	STV0900_DISEQC_3_3_PWM = 3,
	STV0900_DISEQC_2_3_ENVELOP = 4,
	STV0900_DISEQC_3_3_ENVELOP = 5
पूर्ण;

क्रमागत fe_stv0900_demod_mode अणु
	STV0900_SINGLE = 0,
	STV0900_DUAL
पूर्ण;

काष्ठा stv0900_init_paramsअणु
	u32	dmd_ref_clk;/* Reference,Input घड़ी क्रम the demod in Hz */

	/* Demodulator Type (single demod or dual demod) */
	क्रमागत fe_stv0900_demod_mode	demod_mode;
	क्रमागत fe_stv0900_rolloff		rolloff;
	क्रमागत fe_stv0900_घड़ी_प्रकारype	path1_ts_घड़ी;

	u8	tun1_maddress;
	पूर्णांक	tuner1_adc;
	पूर्णांक	tuner1_type;

	/* IQ from the tuner1 to the demod */
	क्रमागत stv0900_iq_inversion	tun1_iq_inv;
	क्रमागत fe_stv0900_घड़ी_प्रकारype	path2_ts_घड़ी;

	u8	tun2_maddress;
	पूर्णांक	tuner2_adc;
	पूर्णांक	tuner2_type;

	/* IQ from the tuner2 to the demod */
	क्रमागत stv0900_iq_inversion	tun2_iq_inv;
	काष्ठा stv0900_reg		*ts_config;
पूर्ण;

काष्ठा stv0900_search_params अणु
	क्रमागत fe_stv0900_demod_num	path;/* Path Used demod1 or 2 */

	u32	frequency;/* Transponder frequency (in KHz) */
	u32	symbol_rate;/* Transponder symbol rate  (in bds)*/
	u32	search_range;/* Range of the search (in Hz) */

	क्रमागत fe_stv0900_search_standard	standard;
	क्रमागत fe_stv0900_modulation	modulation;
	क्रमागत fe_stv0900_fec		fec;
	क्रमागत fe_stv0900_modcode		modcode;
	क्रमागत fe_stv0900_search_iq	iq_inversion;
	क्रमागत fe_stv0900_search_algo	search_algo;

पूर्ण;

काष्ठा stv0900_संकेत_info अणु
	पूर्णांक	locked;/* Transponder locked */
	u32	frequency;/* Transponder frequency (in KHz) */
	u32	symbol_rate;/* Transponder symbol rate  (in Mbds) */

	क्रमागत fe_stv0900_tracking_standard	standard;
	क्रमागत fe_stv0900_fec			fec;
	क्रमागत fe_stv0900_modcode			modcode;
	क्रमागत fe_stv0900_modulation		modulation;
	क्रमागत fe_stv0900_pilot			pilot;
	क्रमागत fe_stv0900_frame_length		frame_len;
	क्रमागत stv0900_iq_inversion		spectrum;
	क्रमागत fe_stv0900_rolloff			rolloff;

	s32 Power;/* Power of the RF संकेत (dBm) */
	s32 C_N;/* Carrier to noise ratio (dB x10)*/
	u32 BER;/* Bit error rate (x10^7) */

पूर्ण;

काष्ठा stv0900_पूर्णांकernalअणु
	s32	quartz;
	s32	mclk;
	/* manual RollOff क्रम DVBS1/DSS only */
	क्रमागत fe_stv0900_rolloff		rolloff;
	/* Demodulator use क्रम single demod or क्रम dual demod) */
	क्रमागत fe_stv0900_demod_mode	demod_mode;

	/*Demods */
	s32	freq[2];
	s32	bw[2];
	s32	symbol_rate[2];
	s32	srch_range[2];
	/* क्रम software/स्वतः tuner */
	पूर्णांक	tuner_type[2];

	/* algorithm क्रम search Blind, Cold or Warm*/
	क्रमागत fe_stv0900_search_algo	srch_algo[2];
	/* search standard: Auto, DVBS1/DSS only or DVBS2 only*/
	क्रमागत fe_stv0900_search_standard	srch_standard[2];
	/* inversion search : स्वतः, स्वतः norma first, normal or inverted */
	क्रमागत fe_stv0900_search_iq	srch_iq_inv[2];
	क्रमागत fe_stv0900_modcode		modcode[2];
	क्रमागत fe_stv0900_modulation	modulation[2];
	क्रमागत fe_stv0900_fec		fec[2];

	काष्ठा stv0900_संकेत_info	result[2];
	क्रमागत fe_stv0900_error		err[2];


	काष्ठा i2c_adapter	*i2c_adap;
	u8			i2c_addr;
	u8			clkmode;/* 0 क्रम CLKI, 2 क्रम XTALI */
	u8			chip_id;
	काष्ठा stv0900_reg	*ts_config;
	क्रमागत fe_stv0900_error	errs;
	पूर्णांक dmds_used;
पूर्ण;

/* state क्रम each demod */
काष्ठा stv0900_state अणु
	/* poपूर्णांकer क्रम पूर्णांकernal params, one क्रम each pair of demods */
	काष्ठा stv0900_पूर्णांकernal		*पूर्णांकernal;
	काष्ठा i2c_adapter		*i2c_adap;
	स्थिर काष्ठा stv0900_config	*config;
	काष्ठा dvb_frontend		frontend;
	पूर्णांक demod;
पूर्ण;

बाह्य पूर्णांक stvdebug;

बाह्य s32 ge2comp(s32 a, s32 width);

बाह्य व्योम stv0900_ग_लिखो_reg(काष्ठा stv0900_पूर्णांकernal *i_params,
				u16 reg_addr, u8 reg_data);

बाह्य u8 stv0900_पढ़ो_reg(काष्ठा stv0900_पूर्णांकernal *i_params,
				u16 reg_addr);

बाह्य व्योम stv0900_ग_लिखो_bits(काष्ठा stv0900_पूर्णांकernal *i_params,
				u32 label, u8 val);

बाह्य u8 stv0900_get_bits(काष्ठा stv0900_पूर्णांकernal *i_params,
				u32 label);

बाह्य पूर्णांक stv0900_get_demod_lock(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod, s32 समय_out);
बाह्य पूर्णांक stv0900_check_संकेत_presence(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य क्रमागत fe_stv0900_संकेत_type stv0900_algo(काष्ठा dvb_frontend *fe);

बाह्य व्योम stv0900_set_tuner(काष्ठा dvb_frontend *fe, u32 frequency,
				u32 bandwidth);
बाह्य व्योम stv0900_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth);

बाह्य व्योम stv0900_start_search(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य u8 stv0900_get_optim_carr_loop(s32 srate,
				क्रमागत fe_stv0900_modcode modcode,
				s32 pilot, u8 chip_id);

बाह्य u8 stv0900_get_optim_लघु_carr_loop(s32 srate,
				क्रमागत fe_stv0900_modulation modulation,
				u8 chip_id);

बाह्य व्योम stv0900_stop_all_s2_modcod(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य व्योम stv0900_activate_s2_modcod(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य व्योम stv0900_activate_s2_modcod_single(काष्ठा stv0900_पूर्णांकernal *i_params,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य क्रमागत
fe_stv0900_tracking_standard stv0900_get_standard(काष्ठा dvb_frontend *fe,
				क्रमागत fe_stv0900_demod_num demod);

बाह्य u32
stv0900_get_freq_स्वतः(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, पूर्णांक demod);

बाह्य व्योम
stv0900_set_tuner_स्वतः(काष्ठा stv0900_पूर्णांकernal *पूर्णांकp, u32 Frequency,
						u32 Bandwidth, पूर्णांक demod);

#पूर्ण_अगर
