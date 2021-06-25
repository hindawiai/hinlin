<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */
#अगर_अघोषित _AS10X_TYPES_H_
#घोषणा _AS10X_TYPES_H_

/*********************************/
/*       MACRO DEFINITIONS       */
/*********************************/

/* bandwidth स्थिरant values */
#घोषणा BW_5_MHZ		0x00
#घोषणा BW_6_MHZ		0x01
#घोषणा BW_7_MHZ		0x02
#घोषणा BW_8_MHZ		0x03

/* hierarchy priority selection values */
#घोषणा HIER_NO_PRIORITY	0x00
#घोषणा HIER_LOW_PRIORITY	0x01
#घोषणा HIER_HIGH_PRIORITY	0x02

/* स्थिरellation available values */
#घोषणा CONST_QPSK		0x00
#घोषणा CONST_QAM16		0x01
#घोषणा CONST_QAM64		0x02
#घोषणा CONST_UNKNOWN		0xFF

/* hierarchy available values */
#घोषणा HIER_NONE		0x00
#घोषणा HIER_ALPHA_1		0x01
#घोषणा HIER_ALPHA_2		0x02
#घोषणा HIER_ALPHA_4		0x03
#घोषणा HIER_UNKNOWN		0xFF

/* पूर्णांकerleaving available values */
#घोषणा INTLV_NATIVE		0x00
#घोषणा INTLV_IN_DEPTH		0x01
#घोषणा INTLV_UNKNOWN		0xFF

/* code rate available values */
#घोषणा CODE_RATE_1_2		0x00
#घोषणा CODE_RATE_2_3		0x01
#घोषणा CODE_RATE_3_4		0x02
#घोषणा CODE_RATE_5_6		0x03
#घोषणा CODE_RATE_7_8		0x04
#घोषणा CODE_RATE_UNKNOWN	0xFF

/* guard पूर्णांकerval available values */
#घोषणा GUARD_INT_1_32		0x00
#घोषणा GUARD_INT_1_16		0x01
#घोषणा GUARD_INT_1_8		0x02
#घोषणा GUARD_INT_1_4		0x03
#घोषणा GUARD_UNKNOWN		0xFF

/* transmission mode available values */
#घोषणा TRANS_MODE_2K		0x00
#घोषणा TRANS_MODE_8K		0x01
#घोषणा TRANS_MODE_4K		0x02
#घोषणा TRANS_MODE_UNKNOWN	0xFF

/* DVBH संकेतling available values */
#घोषणा TIMESLICING_PRESENT	0x01
#घोषणा MPE_FEC_PRESENT		0x02

/* tune state available */
#घोषणा TUNE_STATUS_NOT_TUNED		0x00
#घोषणा TUNE_STATUS_IDLE		0x01
#घोषणा TUNE_STATUS_LOCKING		0x02
#घोषणा TUNE_STATUS_SIGNAL_DVB_OK	0x03
#घोषणा TUNE_STATUS_STREAM_DETECTED	0x04
#घोषणा TUNE_STATUS_STREAM_TUNED	0x05
#घोषणा TUNE_STATUS_ERROR		0xFF

/* available TS FID filter types */
#घोषणा TS_PID_TYPE_TS		0
#घोषणा TS_PID_TYPE_PSI_SI	1
#घोषणा TS_PID_TYPE_MPE		2

/* number of echos available */
#घोषणा MAX_ECHOS	15

/* Context types */
#घोषणा CONTEXT_LNA			1010
#घोषणा CONTEXT_ELNA_HYSTERESIS		4003
#घोषणा CONTEXT_ELNA_GAIN		4004
#घोषणा CONTEXT_MER_THRESHOLD		5005
#घोषणा CONTEXT_MER_OFFSET		5006
#घोषणा CONTEXT_IR_STATE		7000
#घोषणा CONTEXT_TSOUT_MSB_FIRST		7004
#घोषणा CONTEXT_TSOUT_FALLING_EDGE	7005

/* Configuration modes */
#घोषणा CFG_MODE_ON	0
#घोषणा CFG_MODE_OFF	1
#घोषणा CFG_MODE_AUTO	2

काष्ठा as10x_tps अणु
	uपूर्णांक8_t modulation;
	uपूर्णांक8_t hierarchy;
	uपूर्णांक8_t पूर्णांकerleaving_mode;
	uपूर्णांक8_t code_rate_HP;
	uपूर्णांक8_t code_rate_LP;
	uपूर्णांक8_t guard_पूर्णांकerval;
	uपूर्णांक8_t transmission_mode;
	uपूर्णांक8_t DVBH_mask_HP;
	uपूर्णांक8_t DVBH_mask_LP;
	uपूर्णांक16_t cell_ID;
पूर्ण __packed;

काष्ठा as10x_tune_args अणु
	/* frequency */
	uपूर्णांक32_t freq;
	/* bandwidth */
	uपूर्णांक8_t bandwidth;
	/* hierarchy selection */
	uपूर्णांक8_t hier_select;
	/* स्थिरellation */
	uपूर्णांक8_t modulation;
	/* hierarchy */
	uपूर्णांक8_t hierarchy;
	/* पूर्णांकerleaving mode */
	uपूर्णांक8_t पूर्णांकerleaving_mode;
	/* code rate */
	uपूर्णांक8_t code_rate;
	/* guard पूर्णांकerval */
	uपूर्णांक8_t guard_पूर्णांकerval;
	/* transmission mode */
	uपूर्णांक8_t transmission_mode;
पूर्ण __packed;

काष्ठा as10x_tune_status अणु
	/* tune status */
	uपूर्णांक8_t tune_state;
	/* संकेत strength */
	पूर्णांक16_t संकेत_strength;
	/* packet error rate 10^-4 */
	uपूर्णांक16_t PER;
	/* bit error rate 10^-4 */
	uपूर्णांक16_t BER;
पूर्ण __packed;

काष्ठा as10x_demod_stats अणु
	/* frame counter */
	uपूर्णांक32_t frame_count;
	/* Bad frame counter */
	uपूर्णांक32_t bad_frame_count;
	/* Number of wrong bytes fixed by Reed-Solomon */
	uपूर्णांक32_t bytes_fixed_by_rs;
	/* Averaged MER */
	uपूर्णांक16_t mer;
	/* statistics calculation state indicator (started or not) */
	uपूर्णांक8_t has_started;
पूर्ण __packed;

काष्ठा as10x_ts_filter अणु
	uपूर्णांक16_t pid;  /* valid PID value 0x00 : 0x2000 */
	uपूर्णांक8_t  type; /* Red TS_PID_TYPE_<N> values */
	uपूर्णांक8_t  idx;  /* index in filtering table */
पूर्ण __packed;

काष्ठा as10x_रेजिस्टर_value अणु
	uपूर्णांक8_t mode;
	जोड़ अणु
		uपूर्णांक8_t  value8;   /* 8 bit value */
		uपूर्णांक16_t value16;  /* 16 bit value */
		uपूर्णांक32_t value32;  /* 32 bit value */
	पूर्ण __packed u;
पूर्ण __packed;

काष्ठा as10x_रेजिस्टर_addr अणु
	/* रेजिस्टर addr */
	uपूर्णांक32_t addr;
	/* रेजिस्टर mode access */
	uपूर्णांक8_t mode;
पूर्ण;

#पूर्ण_अगर
