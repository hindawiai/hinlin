<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support क्रम the Broadcom BCM3510 ATSC demodulator (1st generation Air2PC)
 *
 *  Copyright (C) 2001-5, B2C2 inc.
 *
 *  GPL/Linux driver written by Patrick Boettcher <patrick.boettcher@posteo.de>
 */
#अगर_अघोषित __BCM3510_PRIV_H__
#घोषणा __BCM3510_PRIV_H__

#घोषणा PACKED __attribute__((packed))

#अघोषित err
#घोषणा err(क्रमmat, arg...)  prपूर्णांकk(KERN_ERR     "bcm3510: " क्रमmat "\n" , ## arg)
#अघोषित info
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO    "bcm3510: " क्रमmat "\n" , ## arg)
#अघोषित warn
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "bcm3510: " क्रमmat "\n" , ## arg)


#घोषणा PANASONIC_FIRST_IF_BASE_IN_KHz  1407500
#घोषणा BCM3510_SYMBOL_RATE             5381000

प्रकार जोड़ अणु
	u8 raw;

	काष्ठा अणु
		u8 CTL   :8;
	पूर्ण TSTCTL_2e;

	u8 LDCERC_4e;
	u8 LDUERC_4f;
	u8 LD_BER0_65;
	u8 LD_BER1_66;
	u8 LD_BER2_67;
	u8 LD_BER3_68;

	काष्ठा अणु
		u8 RESET :1;
		u8 IDLE  :1;
		u8 STOP  :1;
		u8 HIRQ0 :1;
		u8 HIRQ1 :1;
		u8 na0   :1;
		u8 HABAV :1;
		u8 na1   :1;
	पूर्ण HCTL1_a0;

	काष्ठा अणु
		u8 na0    :1;
		u8 IDLMSK :1;
		u8 STMSK  :1;
		u8 I0MSK  :1;
		u8 I1MSK  :1;
		u8 na1    :1;
		u8 HABMSK :1;
		u8 na2    :1;
	पूर्ण HCTLMSK_a1;

	काष्ठा अणु
		u8 RESET  :1;
		u8 IDLE   :1;
		u8 STOP   :1;
		u8 RUN    :1;
		u8 HABAV  :1;
		u8 MEMAV  :1;
		u8 ALDONE :1;
		u8 REIRQ  :1;
	पूर्ण APSTAT1_a2;

	काष्ठा अणु
		u8 RSTMSK :1;
		u8 IMSK   :1;
		u8 SMSK   :1;
		u8 RMSK   :1;
		u8 HABMSK :1;
		u8 MAVMSK :1;
		u8 ALDMSK :1;
		u8 REMSK  :1;
	पूर्ण APMSK1_a3;

	u8 APSTAT2_a4;
	u8 APMSK2_a5;

	काष्ठा अणु
		u8 HABADR :7;
		u8 na     :1;
	पूर्ण HABADR_a6;

	u8 HABDATA_a7;

	काष्ठा अणु
		u8 HABR   :1;
		u8 LDHABR :1;
		u8 APMSK  :1;
		u8 HMSK   :1;
		u8 LDMSK  :1;
		u8 na     :3;
	पूर्ण HABSTAT_a8;

	u8 MADRH_a9;
	u8 MADRL_aa;
	u8 MDATA_ab;

	काष्ठा अणु
#घोषणा JDEC_WAIT_AT_RAM      0x7
#घोषणा JDEC_EEPROM_LOAD_WAIT 0x4
		u8 JDEC   :3;
		u8 na     :5;
	पूर्ण JDEC_ca;

	काष्ठा अणु
		u8 REV   :4;
		u8 LAYER :4;
	पूर्ण REVID_e0;

	काष्ठा अणु
		u8 unk0   :1;
		u8 CNTCTL :1;
		u8 BITCNT :1;
		u8 unk1   :1;
		u8 RESYNC :1;
		u8 unk2   :3;
	पूर्ण BERCTL_fa;

	काष्ठा अणु
		u8 CSEL0  :1;
		u8 CLKED0 :1;
		u8 CSEL1  :1;
		u8 CLKED1 :1;
		u8 CLKLEV :1;
		u8 SPIVAR :1;
		u8 na     :2;
	पूर्ण TUNSET_fc;

	काष्ठा अणु
		u8 CLK    :1;
		u8 DATA   :1;
		u8 CS0    :1;
		u8 CS1    :1;
		u8 AGCSEL :1;
		u8 na0    :1;
		u8 TUNSEL :1;
		u8 na1    :1;
	पूर्ण TUNCTL_fd;

	u8 TUNSEL0_fe;
	u8 TUNSEL1_ff;

पूर्ण bcm3510_रेजिस्टर_value;

/* HAB commands */

/* version */
#घोषणा CMD_GET_VERSION_INFO   0x3D
#घोषणा MSGID_GET_VERSION_INFO 0x15
काष्ठा bcm3510_hab_cmd_get_version_info अणु
	u8 microcode_version;
	u8 script_version;
	u8 config_version;
	u8 demod_version;
पूर्ण PACKED;

#घोषणा BCM3510_DEF_MICROCODE_VERSION 0x0E
#घोषणा BCM3510_DEF_SCRIPT_VERSION    0x06
#घोषणा BCM3510_DEF_CONFIG_VERSION    0x01
#घोषणा BCM3510_DEF_DEMOD_VERSION     0xB1

/* acquire */
#घोषणा CMD_ACQUIRE            0x38

#घोषणा MSGID_EXT_TUNER_ACQUIRE 0x0A
काष्ठा bcm3510_hab_cmd_ext_acquire अणु
	काष्ठा अणु
		u8 MODE      :4;
		u8 BW        :1;
		u8 FA        :1;
		u8 NTSCSWEEP :1;
		u8 OFFSET    :1;
	पूर्ण PACKED ACQUIRE0; /* control_byte */

	काष्ठा अणु
		u8 IF_FREQ  :3;
		u8 zero0    :1;
		u8 SYM_RATE :3;
		u8 zero1    :1;
	पूर्ण PACKED ACQUIRE1; /* sym_अगर */

	u8 IF_OFFSET0;   /* IF_Offset_10hz */
	u8 IF_OFFSET1;
	u8 SYM_OFFSET0;  /* SymbolRateOffset */
	u8 SYM_OFFSET1;
	u8 NTSC_OFFSET0; /* NTSC_Offset_10hz */
	u8 NTSC_OFFSET1;
पूर्ण PACKED;

#घोषणा MSGID_INT_TUNER_ACQUIRE 0x0B
काष्ठा bcm3510_hab_cmd_पूर्णांक_acquire अणु
	काष्ठा अणु
		u8 MODE      :4;
		u8 BW        :1;
		u8 FA        :1;
		u8 NTSCSWEEP :1;
		u8 OFFSET    :1;
	पूर्ण PACKED ACQUIRE0; /* control_byte */

	काष्ठा अणु
		u8 IF_FREQ  :3;
		u8 zero0    :1;
		u8 SYM_RATE :3;
		u8 zero1    :1;
	पूर्ण PACKED ACQUIRE1; /* sym_अगर */

	u8 TUNER_FREQ0;
	u8 TUNER_FREQ1;
	u8 TUNER_FREQ2;
	u8 TUNER_FREQ3;
	u8 IF_OFFSET0;   /* IF_Offset_10hz */
	u8 IF_OFFSET1;
	u8 SYM_OFFSET0;  /* SymbolRateOffset */
	u8 SYM_OFFSET1;
	u8 NTSC_OFFSET0; /* NTSC_Offset_10hz */
	u8 NTSC_OFFSET1;
पूर्ण PACKED;

/* modes */
#घोषणा BCM3510_QAM16           =   0x01
#घोषणा BCM3510_QAM32           =   0x02
#घोषणा BCM3510_QAM64           =   0x03
#घोषणा BCM3510_QAM128          =   0x04
#घोषणा BCM3510_QAM256          =   0x05
#घोषणा BCM3510_8VSB            =   0x0B
#घोषणा BCM3510_16VSB           =   0x0D

/* IF_FREQS */
#घोषणा BCM3510_IF_TERRESTRIAL 0x0
#घोषणा BCM3510_IF_CABLE       0x1
#घोषणा BCM3510_IF_USE_CMD     0x7

/* SYM_RATE */
#घोषणा BCM3510_SR_8VSB        0x0 /* 5381119 s/sec */
#घोषणा BCM3510_SR_256QAM      0x1 /* 5360537 s/sec */
#घोषणा BCM3510_SR_16QAM       0x2 /* 5056971 s/sec */
#घोषणा BCM3510_SR_MISC        0x3 /* 5000000 s/sec */
#घोषणा BCM3510_SR_USE_CMD     0x7

/* special symbol rate */
#घोषणा CMD_SET_VALUE_NOT_LISTED  0x2d
#घोषणा MSGID_SET_SYMBOL_RATE_NOT_LISTED 0x0c
काष्ठा bcm3510_hab_cmd_set_sr_not_listed अणु
	u8 HOST_SYM_RATE0;
	u8 HOST_SYM_RATE1;
	u8 HOST_SYM_RATE2;
	u8 HOST_SYM_RATE3;
पूर्ण PACKED;

/* special IF */
#घोषणा MSGID_SET_IF_FREQ_NOT_LISTED 0x0d
काष्ठा bcm3510_hab_cmd_set_अगर_freq_not_listed अणु
	u8 HOST_IF_FREQ0;
	u8 HOST_IF_FREQ1;
	u8 HOST_IF_FREQ2;
	u8 HOST_IF_FREQ3;
पूर्ण PACKED;

/* स्वतः reacquire */
#घोषणा CMD_AUTO_PARAM       0x2a
#घोषणा MSGID_AUTO_REACQUIRE 0x0e
काष्ठा bcm3510_hab_cmd_स्वतः_reacquire अणु
	u8 ACQ    :1; /* on/off*/
	u8 unused :7;
पूर्ण PACKED;

#घोषणा MSGID_SET_RF_AGC_SEL 0x12
काष्ठा bcm3510_hab_cmd_set_agc अणु
	u8 LVL    :1;
	u8 unused :6;
	u8 SEL    :1;
पूर्ण PACKED;

#घोषणा MSGID_SET_AUTO_INVERSION 0x14
काष्ठा bcm3510_hab_cmd_स्वतः_inversion अणु
	u8 AI     :1;
	u8 unused :7;
पूर्ण PACKED;


/* bert control */
#घोषणा CMD_STATE_CONTROL  0x12
#घोषणा MSGID_BERT_CONTROL 0x0e
#घोषणा MSGID_BERT_SET     0xfa
काष्ठा bcm3510_hab_cmd_bert_control अणु
	u8 BE     :1;
	u8 unused :7;
पूर्ण PACKED;

#घोषणा MSGID_TRI_STATE 0x2e
काष्ठा bcm3510_hab_cmd_tri_state अणु
	u8 RE :1; /* a/d ram port pins */
	u8 PE :1; /* baud घड़ी pin */
	u8 AC :1; /* a/d घड़ी pin */
	u8 BE :1; /* baud घड़ी pin */
	u8 unused :4;
पूर्ण PACKED;


/* tune */
#घोषणा CMD_TUNE   0x38
#घोषणा MSGID_TUNE 0x16
काष्ठा bcm3510_hab_cmd_tune_ctrl_data_pair अणु
	काष्ठा अणु
#घोषणा BITS_8 0x07
#घोषणा BITS_7 0x06
#घोषणा BITS_6 0x05
#घोषणा BITS_5 0x04
#घोषणा BITS_4 0x03
#घोषणा BITS_3 0x02
#घोषणा BITS_2 0x01
#घोषणा BITS_1 0x00
		u8 size    :3;
		u8 unk     :2;
		u8 clk_off :1;
		u8 cs0     :1;
		u8 cs1     :1;

	पूर्ण PACKED ctrl;

	u8 data;
पूर्ण PACKED;

काष्ठा bcm3510_hab_cmd_tune अणु
	u8 length;
	u8 घड़ी_width;
	u8 misc;
	u8 TUNCTL_state;

	काष्ठा bcm3510_hab_cmd_tune_ctrl_data_pair ctl_dat[16];
पूर्ण PACKED;

#घोषणा CMD_STATUS    0x38
#घोषणा MSGID_STATUS1 0x08
काष्ठा bcm3510_hab_cmd_status1 अणु
	काष्ठा अणु
		u8 EQ_MODE       :4;
		u8 reserved      :2;
		u8 QRE           :1; /* अगर QSE and the spectrum is inversed */
		u8 QSE           :1; /* स्वतःmatic spectral inversion */
	पूर्ण PACKED STATUS0;

	काष्ठा अणु
		u8 RECEIVER_LOCK :1;
		u8 FEC_LOCK      :1;
		u8 OUT_PLL_LOCK  :1;
		u8 reserved      :5;
	पूर्ण PACKED STATUS1;

	काष्ठा अणु
		u8 reserved      :2;
		u8 BW            :1;
		u8 NTE           :1; /* NTSC filter sweep enabled */
		u8 AQI           :1; /* currently acquiring */
		u8 FA            :1; /* fast acquisition */
		u8 ARI           :1; /* स्वतः reacquire */
		u8 TI            :1; /* programming the tuner */
	पूर्ण PACKED STATUS2;
	u8 STATUS3;
	u8 SNR_EST0;
	u8 SNR_EST1;
	u8 TUNER_FREQ0;
	u8 TUNER_FREQ1;
	u8 TUNER_FREQ2;
	u8 TUNER_FREQ3;
	u8 SYM_RATE0;
	u8 SYM_RATE1;
	u8 SYM_RATE2;
	u8 SYM_RATE3;
	u8 SYM_OFFSET0;
	u8 SYM_OFFSET1;
	u8 SYM_ERROR0;
	u8 SYM_ERROR1;
	u8 IF_FREQ0;
	u8 IF_FREQ1;
	u8 IF_FREQ2;
	u8 IF_FREQ3;
	u8 IF_OFFSET0;
	u8 IF_OFFSET1;
	u8 IF_ERROR0;
	u8 IF_ERROR1;
	u8 NTSC_FILTER0;
	u8 NTSC_FILTER1;
	u8 NTSC_FILTER2;
	u8 NTSC_FILTER3;
	u8 NTSC_OFFSET0;
	u8 NTSC_OFFSET1;
	u8 NTSC_ERROR0;
	u8 NTSC_ERROR1;
	u8 INT_AGC_LEVEL0;
	u8 INT_AGC_LEVEL1;
	u8 EXT_AGC_LEVEL0;
	u8 EXT_AGC_LEVEL1;
पूर्ण PACKED;

#घोषणा MSGID_STATUS2 0x14
काष्ठा bcm3510_hab_cmd_status2 अणु
	काष्ठा अणु
		u8 EQ_MODE  :4;
		u8 reserved :2;
		u8 QRE      :1;
		u8 QSR      :1;
	पूर्ण PACKED STATUS0;
	काष्ठा अणु
		u8 RL       :1;
		u8 FL       :1;
		u8 OL       :1;
		u8 reserved :5;
	पूर्ण PACKED STATUS1;
	u8 SYMBOL_RATE0;
	u8 SYMBOL_RATE1;
	u8 SYMBOL_RATE2;
	u8 SYMBOL_RATE3;
	u8 LDCERC0;
	u8 LDCERC1;
	u8 LDCERC2;
	u8 LDCERC3;
	u8 LDUERC0;
	u8 LDUERC1;
	u8 LDUERC2;
	u8 LDUERC3;
	u8 LDBER0;
	u8 LDBER1;
	u8 LDBER2;
	u8 LDBER3;
	काष्ठा अणु
		u8 MODE_TYPE :4; /* acquire mode 0 */
		u8 reservd   :4;
	पूर्ण MODE_TYPE;
	u8 SNR_EST0;
	u8 SNR_EST1;
	u8 SIGNAL;
पूर्ण PACKED;

#घोषणा CMD_SET_RF_BW_NOT_LISTED   0x3f
#घोषणा MSGID_SET_RF_BW_NOT_LISTED 0x11
/* TODO */

#पूर्ण_अगर
