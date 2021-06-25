<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv0367_priv.h
 *
 * Driver क्रम ST STV0367 DVB-T & DVB-C demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2010,2011 NetUP Inc.
 * Copyright (C) 2010,2011 Igor M. Liplianin <liplianin@netup.ru>
 */
/* Common driver error स्थिरants */

#अगर_अघोषित STV0367_PRIV_H
#घोषणा STV0367_PRIV_H

#अगर_अघोषित TRUE
    #घोषणा TRUE (1 == 1)
#पूर्ण_अगर
#अगर_अघोषित FALSE
    #घोषणा FALSE (!TRUE)
#पूर्ण_अगर

#अगर_अघोषित शून्य
#घोषणा शून्य 0
#पूर्ण_अगर

/* MACRO definitions */
#घोषणा MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#घोषणा MIN(X, Y) ((X) <= (Y) ? (X) : (Y))
#घोषणा INRANGE(X, Y, Z) \
	((((X) <= (Y)) && ((Y) <= (Z))) || \
	(((Z) <= (Y)) && ((Y) <= (X))) ? 1 : 0)

#अगर_अघोषित MAKEWORD
#घोषणा MAKEWORD(X, Y) (((X) << 8) + (Y))
#पूर्ण_अगर

#घोषणा LSB(X) (((X) & 0xff))
#घोषणा MSB(Y) (((Y) >> 8) & 0xff)
#घोषणा MMSB(Y)(((Y) >> 16) & 0xff)

क्रमागत stv0367_ter_संकेत_type अणु
	FE_TER_NOAGC = 0,
	FE_TER_AGCOK = 5,
	FE_TER_NOTPS = 6,
	FE_TER_TPSOK = 7,
	FE_TER_NOSYMBOL = 8,
	FE_TER_BAD_CPQ = 9,
	FE_TER_PRFOUNDOK = 10,
	FE_TER_NOPRFOUND = 11,
	FE_TER_LOCKOK = 12,
	FE_TER_NOLOCK = 13,
	FE_TER_SYMBOLOK = 15,
	FE_TER_CPAMPOK = 16,
	FE_TER_NOCPAMP = 17,
	FE_TER_SWNOK = 18
पूर्ण;

क्रमागत stv0367_ts_mode अणु
	STV0367_OUTPUTMODE_DEFAULT,
	STV0367_SERIAL_PUNCT_CLOCK,
	STV0367_SERIAL_CONT_CLOCK,
	STV0367_PARALLEL_PUNCT_CLOCK,
	STV0367_DVBCI_CLOCK
पूर्ण;

क्रमागत stv0367_clk_pol अणु
	STV0367_CLOCKPOLARITY_DEFAULT,
	STV0367_RISINGEDGE_CLOCK,
	STV0367_FALLINGEDGE_CLOCK
पूर्ण;

क्रमागत stv0367_ter_bw अणु
	FE_TER_CHAN_BW_6M = 6,
	FE_TER_CHAN_BW_7M = 7,
	FE_TER_CHAN_BW_8M = 8
पूर्ण;

#अगर 0
क्रमागत FE_TER_Rate_TPS अणु
	FE_TER_TPS_1_2 = 0,
	FE_TER_TPS_2_3 = 1,
	FE_TER_TPS_3_4 = 2,
	FE_TER_TPS_5_6 = 3,
	FE_TER_TPS_7_8 = 4
पूर्ण;
#पूर्ण_अगर

क्रमागत stv0367_ter_mode अणु
	FE_TER_MODE_2K,
	FE_TER_MODE_8K,
	FE_TER_MODE_4K
पूर्ण;
#अगर 0
क्रमागत FE_TER_Hierarchy_Alpha अणु
	FE_TER_HIER_ALPHA_NONE,	/* Regular modulation */
	FE_TER_HIER_ALPHA_1,	/* Hierarchical modulation a = 1*/
	FE_TER_HIER_ALPHA_2,	/* Hierarchical modulation a = 2*/
	FE_TER_HIER_ALPHA_4	/* Hierarchical modulation a = 4*/
पूर्ण;
#पूर्ण_अगर
क्रमागत stv0367_ter_hierarchy अणु
	FE_TER_HIER_NONE,	/*Hierarchy None*/
	FE_TER_HIER_LOW_PRIO,	/*Hierarchy : Low Priority*/
	FE_TER_HIER_HIGH_PRIO,	/*Hierarchy : High Priority*/
	FE_TER_HIER_PRIO_ANY	/*Hierarchy  :Any*/
पूर्ण;

#अगर 0
क्रमागत fe_stv0367_ter_spec अणु
	FE_TER_INVERSION_NONE = 0,
	FE_TER_INVERSION = 1,
	FE_TER_INVERSION_AUTO = 2,
	FE_TER_INVERSION_UNK  = 4
पूर्ण;
#पूर्ण_अगर

क्रमागत stv0367_ter_अगर_iq_mode अणु
	FE_TER_NORMAL_IF_TUNER = 0,
	FE_TER_LONGPATH_IF_TUNER = 1,
	FE_TER_IQ_TUNER = 2

पूर्ण;

#अगर 0
क्रमागत FE_TER_FECRate अणु
	FE_TER_FEC_NONE = 0x00,	/* no FEC rate specअगरied */
	FE_TER_FEC_ALL = 0xFF,	 /* Logical OR of all FECs */
	FE_TER_FEC_1_2 = 1,
	FE_TER_FEC_2_3 = (1 << 1),
	FE_TER_FEC_3_4 = (1 << 2),
	FE_TER_FEC_4_5 = (1 << 3),
	FE_TER_FEC_5_6 = (1 << 4),
	FE_TER_FEC_6_7 = (1 << 5),
	FE_TER_FEC_7_8 = (1 << 6),
	FE_TER_FEC_8_9 = (1 << 7)
पूर्ण;

क्रमागत FE_TER_Rate अणु
	FE_TER_FE_1_2 = 0,
	FE_TER_FE_2_3 = 1,
	FE_TER_FE_3_4 = 2,
	FE_TER_FE_5_6 = 3,
	FE_TER_FE_6_7 = 4,
	FE_TER_FE_7_8 = 5
पूर्ण;
#पूर्ण_अगर

क्रमागत stv0367_ter_क्रमce अणु
	FE_TER_FORCENONE = 0,
	FE_TER_FORCE_M_G = 1
पूर्ण;

क्रमागत  stv0367cab_mod अणु
	FE_CAB_MOD_QAM4,
	FE_CAB_MOD_QAM16,
	FE_CAB_MOD_QAM32,
	FE_CAB_MOD_QAM64,
	FE_CAB_MOD_QAM128,
	FE_CAB_MOD_QAM256,
	FE_CAB_MOD_QAM512,
	FE_CAB_MOD_QAM1024
पूर्ण;
#अगर 0
क्रमागत अणु
	FE_CAB_FEC_A = 1,	/* J83 Annex A */
	FE_CAB_FEC_B = (1 << 1),/* J83 Annex B */
	FE_CAB_FEC_C = (1 << 2)	/* J83 Annex C */
पूर्ण FE_CAB_FECType_t;
#पूर्ण_अगर
काष्ठा stv0367_cab_संकेत_info अणु
	पूर्णांक locked;
	u32 frequency; /* kHz */
	u32 symbol_rate; /* Mbds */
	क्रमागत stv0367cab_mod modulation;
	क्रमागत fe_spectral_inversion spect_inv;
	s32 Power_dBmx10;	/* Power of the RF संकेत (dBm x 10) */
	u32	CN_dBx10;	/* Carrier to noise ratio (dB x 10) */
	u32	BER;		/* Bit error rate (x 10000000)	*/
पूर्ण;

क्रमागत stv0367_cab_संकेत_type अणु
	FE_CAB_NOTUNER,
	FE_CAB_NOAGC,
	FE_CAB_NOSIGNAL,
	FE_CAB_NOTIMING,
	FE_CAB_TIMINGOK,
	FE_CAB_NOCARRIER,
	FE_CAB_CARRIEROK,
	FE_CAB_NOBLIND,
	FE_CAB_BLINDOK,
	FE_CAB_NODEMOD,
	FE_CAB_DEMODOK,
	FE_CAB_DATAOK
पूर्ण;

#पूर्ण_अगर
