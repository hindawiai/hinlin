<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STV0900/0903 Multistandard Broadcast Frontend driver
	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STV090x_PRIV_H
#घोषणा __STV090x_PRIV_H

#समावेश <media/dvb_frontend.h>

#घोषणा FE_ERROR				0
#घोषणा FE_NOTICE				1
#घोषणा FE_INFO					2
#घोषणा FE_DEBUG				3
#घोषणा FE_DEBUGREG				4

#घोषणा dprपूर्णांकk(__y, __z, क्रमmat, arg...) करो अणु						\
	अगर (__z) अणु									\
		अगर	((verbose > FE_ERROR) && (verbose > __y))			\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर	((verbose > FE_NOTICE) && (verbose > __y))			\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((verbose > FE_INFO) && (verbose > __y))			\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर ((verbose > FE_DEBUG) && (verbose > __y))			\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (verbose > __y)							\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक (0)

#घोषणा STV090x_READ_DEMOD(__state, __reg) ((			\
	(__state)->demod == STV090x_DEMODULATOR_1)	?	\
	stv090x_पढ़ो_reg(__state, STV090x_P2_##__reg) :		\
	stv090x_पढ़ो_reg(__state, STV090x_P1_##__reg))

#घोषणा STV090x_WRITE_DEMOD(__state, __reg, __data) ((		\
	(__state)->demod == STV090x_DEMODULATOR_1)	?	\
	stv090x_ग_लिखो_reg(__state, STV090x_P2_##__reg, __data) :\
	stv090x_ग_लिखो_reg(__state, STV090x_P1_##__reg, __data))

#घोषणा STV090x_ADDR_OFFST(__state, __x) ((			\
	(__state->demod) == STV090x_DEMODULATOR_1)	?	\
		STV090x_P1_##__x :				\
		STV090x_P2_##__x)


#घोषणा STV090x_SETFIELD(mask, bitf, val)	(mask = (mask & (~(((1 << STV090x_WIDTH_##bitf) - 1) <<\
							 STV090x_OFFST_##bitf))) | \
							 (val << STV090x_OFFST_##bitf))

#घोषणा STV090x_GETFIELD(val, bitf)		((val >> STV090x_OFFST_##bitf) & ((1 << STV090x_WIDTH_##bitf) - 1))


#घोषणा STV090x_SETFIELD_Px(mask, bitf, val)	(mask = (mask & (~(((1 << STV090x_WIDTH_Px_##bitf) - 1) <<\
							 STV090x_OFFST_Px_##bitf))) | \
							 (val << STV090x_OFFST_Px_##bitf))

#घोषणा STV090x_GETFIELD_Px(val, bitf)		((val >> STV090x_OFFST_Px_##bitf) & ((1 << STV090x_WIDTH_Px_##bitf) - 1))

#घोषणा MAKEWORD16(__a, __b)			(((__a) << 8) | (__b))

#घोषणा MSB(__x)				((__x >> 8) & 0xff)
#घोषणा LSB(__x)				(__x & 0xff)


#घोषणा STV090x_IQPOWER_THRESHOLD	  30
#घोषणा STV090x_SEARCH_AGC2_TH_CUT20	 700
#घोषणा STV090x_SEARCH_AGC2_TH_CUT30	1400

#घोषणा STV090x_SEARCH_AGC2_TH(__ver)	\
	((__ver <= 0x20) ?		\
	STV090x_SEARCH_AGC2_TH_CUT20 :	\
	STV090x_SEARCH_AGC2_TH_CUT30)

क्रमागत stv090x_संकेत_state अणु
	STV090x_NOAGC1,
	STV090x_NOCARRIER,
	STV090x_NODATA,
	STV090x_DATAOK,
	STV090x_RANGEOK,
	STV090x_OUTOFRANGE
पूर्ण;

क्रमागत stv090x_fec अणु
	STV090x_PR12 = 0,
	STV090x_PR23,
	STV090x_PR34,
	STV090x_PR45,
	STV090x_PR56,
	STV090x_PR67,
	STV090x_PR78,
	STV090x_PR89,
	STV090x_PR910,
	STV090x_PRERR
पूर्ण;

क्रमागत stv090x_modulation अणु
	STV090x_QPSK,
	STV090x_8PSK,
	STV090x_16APSK,
	STV090x_32APSK,
	STV090x_UNKNOWN
पूर्ण;

क्रमागत stv090x_frame अणु
	STV090x_LONG_FRAME,
	STV090x_SHORT_FRAME
पूर्ण;

क्रमागत stv090x_pilot अणु
	STV090x_PILOTS_OFF,
	STV090x_PILOTS_ON
पूर्ण;

क्रमागत stv090x_rolloff अणु
	STV090x_RO_35,
	STV090x_RO_25,
	STV090x_RO_20
पूर्ण;

क्रमागत stv090x_inversion अणु
	STV090x_IQ_AUTO,
	STV090x_IQ_NORMAL,
	STV090x_IQ_SWAP
पूर्ण;

क्रमागत stv090x_modcod अणु
	STV090x_DUMMY_PLF = 0,
	STV090x_QPSK_14,
	STV090x_QPSK_13,
	STV090x_QPSK_25,
	STV090x_QPSK_12,
	STV090x_QPSK_35,
	STV090x_QPSK_23,
	STV090x_QPSK_34,
	STV090x_QPSK_45,
	STV090x_QPSK_56,
	STV090x_QPSK_89,
	STV090x_QPSK_910,
	STV090x_8PSK_35,
	STV090x_8PSK_23,
	STV090x_8PSK_34,
	STV090x_8PSK_56,
	STV090x_8PSK_89,
	STV090x_8PSK_910,
	STV090x_16APSK_23,
	STV090x_16APSK_34,
	STV090x_16APSK_45,
	STV090x_16APSK_56,
	STV090x_16APSK_89,
	STV090x_16APSK_910,
	STV090x_32APSK_34,
	STV090x_32APSK_45,
	STV090x_32APSK_56,
	STV090x_32APSK_89,
	STV090x_32APSK_910,
	STV090x_MODCODE_UNKNOWN
पूर्ण;

क्रमागत stv090x_search अणु
	STV090x_SEARCH_DSS = 0,
	STV090x_SEARCH_DVBS1,
	STV090x_SEARCH_DVBS2,
	STV090x_SEARCH_AUTO
पूर्ण;

क्रमागत stv090x_algo अणु
	STV090x_BLIND_SEARCH,
	STV090x_COLD_SEARCH,
	STV090x_WARM_SEARCH
पूर्ण;

क्रमागत stv090x_delsys अणु
	STV090x_ERROR = 0,
	STV090x_DVBS1 = 1,
	STV090x_DVBS2,
	STV090x_DSS
पूर्ण;

काष्ठा stv090x_दीर्घ_frame_crloop अणु
	क्रमागत stv090x_modcod	modcod;

	u8 crl_pilots_on_2;
	u8 crl_pilots_off_2;
	u8 crl_pilots_on_5;
	u8 crl_pilots_off_5;
	u8 crl_pilots_on_10;
	u8 crl_pilots_off_10;
	u8 crl_pilots_on_20;
	u8 crl_pilots_off_20;
	u8 crl_pilots_on_30;
	u8 crl_pilots_off_30;
पूर्ण;

काष्ठा stv090x_लघु_frame_crloop अणु
	क्रमागत stv090x_modulation	modulation;

	u8 crl_2;  /*      SR <   3M */
	u8 crl_5;  /*  3 < SR <=  7M */
	u8 crl_10; /*  7 < SR <= 15M */
	u8 crl_20; /* 10 < SR <= 25M */
	u8 crl_30; /* 10 < SR <= 45M */
पूर्ण;

काष्ठा stv090x_reg अणु
	u16 addr;
	u8  data;
पूर्ण;

काष्ठा stv090x_tab अणु
	s32 real;
	s32 पढ़ो;
पूर्ण;

काष्ठा stv090x_पूर्णांकernal अणु
	काष्ठा i2c_adapter	*i2c_adap;
	u8			i2c_addr;

	काष्ठा mutex		demod_lock; /* Lock access to shared रेजिस्टर */
	काष्ठा mutex		tuner_lock; /* Lock access to tuners */
	s32			mclk; /* Masterघड़ी Divider factor */
	u32			dev_ver;

	पूर्णांक			num_used;
पूर्ण;

काष्ठा stv090x_state अणु
	क्रमागत stv090x_device		device;
	क्रमागत stv090x_demodulator	demod;
	क्रमागत stv090x_mode		demod_mode;
	काष्ठा stv090x_पूर्णांकernal		*पूर्णांकernal;

	काष्ठा i2c_adapter		*i2c;
	काष्ठा stv090x_config	*config;
	काष्ठा dvb_frontend		frontend;

	u32				*verbose; /* Cached module verbosity */

	क्रमागत stv090x_delsys		delsys;
	क्रमागत stv090x_fec		fec;
	क्रमागत stv090x_modulation		modulation;
	क्रमागत stv090x_modcod		modcod;
	क्रमागत stv090x_search		search_mode;
	क्रमागत stv090x_frame		frame_len;
	क्रमागत stv090x_pilot		pilots;
	क्रमागत stv090x_rolloff		rolloff;
	क्रमागत stv090x_inversion		inversion;
	क्रमागत stv090x_algo		algo;

	u32				frequency;
	u32				srate;

	s32				tuner_bw;

	s32				search_range;

	s32				DemodTimeout;
	s32				FecTimeout;
पूर्ण;

#पूर्ण_अगर /* __STV090x_PRIV_H */
