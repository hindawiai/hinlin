<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Defines क्रम the Maxlinear MX58x family of tuners/demods
 *
 * Copyright (C) 2014 Digital Devices GmbH
 *
 * based on code:
 * Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 */

क्रमागत MXL_BOOL_E अणु
	MXL_DISABLE = 0,
	MXL_ENABLE  = 1,

	MXL_FALSE = 0,
	MXL_TRUE  = 1,

	MXL_INVALID = 0,
	MXL_VALID   = 1,

	MXL_NO      = 0,
	MXL_YES     = 1,

	MXL_OFF     = 0,
	MXL_ON      = 1
पूर्ण;

/* Firmware-Host Command IDs */
क्रमागत MXL_HYDRA_HOST_CMD_ID_E अणु
	/* --Device command IDs-- */
	MXL_HYDRA_DEV_NO_OP_CMD = 0, /* No OP */

	MXL_HYDRA_DEV_SET_POWER_MODE_CMD = 1,
	MXL_HYDRA_DEV_SET_OVERWRITE_DEF_CMD = 2,

	/* Host-used CMD, not used by firmware */
	MXL_HYDRA_DEV_FIRMWARE_DOWNLOAD_CMD = 3,

	/* Additional CONTROL types from DTV */
	MXL_HYDRA_DEV_SET_BROADCAST_PID_STB_ID_CMD = 4,
	MXL_HYDRA_DEV_GET_PMM_SLEEP_CMD = 5,

	/* --Tuner command IDs-- */
	MXL_HYDRA_TUNER_TUNE_CMD = 6,
	MXL_HYDRA_TUNER_GET_STATUS_CMD = 7,

	/* --Demod command IDs-- */
	MXL_HYDRA_DEMOD_SET_PARAM_CMD = 8,
	MXL_HYDRA_DEMOD_GET_STATUS_CMD = 9,

	MXL_HYDRA_DEMOD_RESET_FEC_COUNTER_CMD = 10,

	MXL_HYDRA_DEMOD_SET_PKT_NUM_CMD = 11,

	MXL_HYDRA_DEMOD_SET_IQ_SOURCE_CMD = 12,
	MXL_HYDRA_DEMOD_GET_IQ_DATA_CMD = 13,

	MXL_HYDRA_DEMOD_GET_M68HC05_VER_CMD = 14,

	MXL_HYDRA_DEMOD_SET_ERROR_COUNTER_MODE_CMD = 15,

	/* --- ABORT channel tune */
	MXL_HYDRA_ABORT_TUNE_CMD = 16, /* Abort current tune command. */

	/* --SWM/FSK command IDs-- */
	MXL_HYDRA_FSK_RESET_CMD = 17,
	MXL_HYDRA_FSK_MSG_CMD = 18,
	MXL_HYDRA_FSK_SET_OP_MODE_CMD = 19,

	/* --DiSeqC command IDs-- */
	MXL_HYDRA_DISEQC_MSG_CMD = 20,
	MXL_HYDRA_DISEQC_COPY_MSG_TO_MAILBOX = 21,
	MXL_HYDRA_DISEQC_CFG_MSG_CMD = 22,

	/* --- FFT Debug Command IDs-- */
	MXL_HYDRA_REQ_FFT_SPECTRUM_CMD = 23,

	/* -- Demod scramblle code */
	MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD = 24,

	/* ---For host to know how many commands in total */
	MXL_HYDRA_LAST_HOST_CMD = 25,

	MXL_HYDRA_DEMOD_INTR_TYPE_CMD = 47,
	MXL_HYDRA_DEV_INTR_CLEAR_CMD = 48,
	MXL_HYDRA_TUNER_SPECTRUM_REQ_CMD = 53,
	MXL_HYDRA_TUNER_ACTIVATE_CMD = 55,
	MXL_HYDRA_DEV_CFG_POWER_MODE_CMD = 56,
	MXL_HYDRA_DEV_XTAL_CAP_CMD = 57,
	MXL_HYDRA_DEV_CFG_SKU_CMD = 58,
	MXL_HYDRA_TUNER_SPECTRUM_MIN_GAIN_CMD = 59,
	MXL_HYDRA_DISEQC_CONT_TONE_CFG = 60,
	MXL_HYDRA_DEV_RF_WAKE_UP_CMD = 61,
	MXL_HYDRA_DEMOD_CFG_EQ_CTRL_PARAM_CMD = 62,
	MXL_HYDRA_DEMOD_FREQ_OFFSET_SEARCH_RANGE_CMD = 63,
	MXL_HYDRA_DEV_REQ_PWR_FROM_ADCRSSI_CMD = 64,

	MXL_XCPU_PID_FLT_CFG_CMD = 65,
	MXL_XCPU_SHMEM_TEST_CMD = 66,
	MXL_XCPU_ABORT_TUNE_CMD = 67,
	MXL_XCPU_CHAN_TUNE_CMD = 68,
	MXL_XCPU_FLT_BOND_HDRS_CMD = 69,

	MXL_HYDRA_DEV_BROADCAST_WAKE_UP_CMD = 70,
	MXL_HYDRA_FSK_CFG_FSK_FREQ_CMD = 71,
	MXL_HYDRA_FSK_POWER_DOWN_CMD = 72,
	MXL_XCPU_CLEAR_CB_STATS_CMD = 73,
	MXL_XCPU_CHAN_BOND_RESTART_CMD = 74
पूर्ण;

#घोषणा MXL_ENABLE_BIG_ENDIAN        (0)

#घोषणा MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH   248

#घोषणा MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN        (248)

#घोषणा MXL_HYDRA_CAP_MIN     10
#घोषणा MXL_HYDRA_CAP_MAX     33

#घोषणा MXL_HYDRA_PLID_REG_READ       0xFB   /* Read रेजिस्टर PLID */
#घोषणा MXL_HYDRA_PLID_REG_WRITE      0xFC   /* Write रेजिस्टर PLID */

#घोषणा MXL_HYDRA_PLID_CMD_READ       0xFD   /* Command Read PLID */
#घोषणा MXL_HYDRA_PLID_CMD_WRITE      0xFE   /* Command Write PLID */

#घोषणा MXL_HYDRA_REG_SIZE_IN_BYTES   4      /* Hydra रेजिस्टर size in bytes */
#घोषणा MXL_HYDRA_I2C_HDR_SIZE        (2 * माप(u8)) /* PLID + LEN(0xFF) */
#घोषणा MXL_HYDRA_CMD_HEADER_SIZE     (MXL_HYDRA_REG_SIZE_IN_BYTES + MXL_HYDRA_I2C_HDR_SIZE)

#घोषणा MXL_HYDRA_SKU_ID_581 0
#घोषणा MXL_HYDRA_SKU_ID_584 1
#घोषणा MXL_HYDRA_SKU_ID_585 2
#घोषणा MXL_HYDRA_SKU_ID_544 3
#घोषणा MXL_HYDRA_SKU_ID_561 4
#घोषणा MXL_HYDRA_SKU_ID_582 5
#घोषणा MXL_HYDRA_SKU_ID_568 6

/* macro क्रम रेजिस्टर ग_लिखो data buffer size
 * (PLID + LEN (0xFF) + RegAddr + RegData)
 */
#घोषणा MXL_HYDRA_REG_WRITE_LEN       (MXL_HYDRA_I2C_HDR_SIZE + (2 * MXL_HYDRA_REG_SIZE_IN_BYTES))

/* macro to extract a single byte from 4-byte(32-bit) data */
#घोषणा GET_BYTE(x, n)  (((x) >> (8*(n))) & 0xFF)

#घोषणा MAX_CMD_DATA 512

#घोषणा MXL_GET_REG_MASK_32(lsb_loc, num_of_bits) ((0xFFFFFFFF >> (32 - (num_of_bits))) << (lsb_loc))

#घोषणा FW_DL_SIGN (0xDEADBEEF)

#घोषणा MBIN_FORMAT_VERSION               '1'
#घोषणा MBIN_खाता_HEADER_ID               'M'
#घोषणा MBIN_SEGMENT_HEADER_ID            'S'
#घोषणा MBIN_MAX_खाता_LENGTH              (1<<23)

काष्ठा MBIN_खाता_HEADER_T अणु
	u8 id;
	u8 fmt_version;
	u8 header_len;
	u8 num_segments;
	u8 entry_address[4];
	u8 image_size24[3];
	u8 image_checksum;
	u8 reserved[4];
पूर्ण;

काष्ठा MBIN_खाता_T अणु
	काष्ठा MBIN_खाता_HEADER_T header;
	u8 data[1];
पूर्ण;

काष्ठा MBIN_SEGMENT_HEADER_T अणु
	u8 id;
	u8 len24[3];
	u8 address[4];
पूर्ण;

काष्ठा MBIN_SEGMENT_T अणु
	काष्ठा MBIN_SEGMENT_HEADER_T header;
	u8 data[1];
पूर्ण;

क्रमागत MXL_CMD_TYPE_E अणु MXL_CMD_WRITE = 0, MXL_CMD_READ पूर्ण;

#घोषणा BUILD_HYDRA_CMD(cmd_id, req_type, size, data_ptr, cmd_buff)		\
	करो अणु								\
		cmd_buff[0] = ((req_type == MXL_CMD_WRITE) ? MXL_HYDRA_PLID_CMD_WRITE : MXL_HYDRA_PLID_CMD_READ); \
		cmd_buff[1] = (size > 251) ? 0xff : (u8) (size + 4);	\
		cmd_buff[2] = size;					\
		cmd_buff[3] = cmd_id;					\
		cmd_buff[4] = 0x00;					\
		cmd_buff[5] = 0x00;					\
		convert_endian(MXL_ENABLE_BIG_ENDIAN, size, (u8 *)data_ptr); \
		स_नकल((व्योम *)&cmd_buff[6], data_ptr, size);		\
	पूर्ण जबतक (0)

काष्ठा MXL_REG_FIELD_T अणु
	u32 reg_addr;
	u8 lsb_pos;
	u8 num_of_bits;
पूर्ण;

काष्ठा MXL_DEV_CMD_DATA_T अणु
	u32 data_size;
	u8 data[MAX_CMD_DATA];
पूर्ण;

क्रमागत MXL_HYDRA_SKU_TYPE_E अणु
	MXL_HYDRA_SKU_TYPE_MIN = 0x00,
	MXL_HYDRA_SKU_TYPE_581 = 0x00,
	MXL_HYDRA_SKU_TYPE_584 = 0x01,
	MXL_HYDRA_SKU_TYPE_585 = 0x02,
	MXL_HYDRA_SKU_TYPE_544 = 0x03,
	MXL_HYDRA_SKU_TYPE_561 = 0x04,
	MXL_HYDRA_SKU_TYPE_5XX = 0x05,
	MXL_HYDRA_SKU_TYPE_5YY = 0x06,
	MXL_HYDRA_SKU_TYPE_511 = 0x07,
	MXL_HYDRA_SKU_TYPE_561_DE = 0x08,
	MXL_HYDRA_SKU_TYPE_582 = 0x09,
	MXL_HYDRA_SKU_TYPE_541 = 0x0A,
	MXL_HYDRA_SKU_TYPE_568 = 0x0B,
	MXL_HYDRA_SKU_TYPE_542 = 0x0C,
	MXL_HYDRA_SKU_TYPE_MAX = 0x0D,
पूर्ण;

काष्ठा MXL_HYDRA_SKU_COMMAND_T अणु
	क्रमागत MXL_HYDRA_SKU_TYPE_E sku_type;
पूर्ण;

क्रमागत MXL_HYDRA_DEMOD_ID_E अणु
	MXL_HYDRA_DEMOD_ID_0 = 0,
	MXL_HYDRA_DEMOD_ID_1,
	MXL_HYDRA_DEMOD_ID_2,
	MXL_HYDRA_DEMOD_ID_3,
	MXL_HYDRA_DEMOD_ID_4,
	MXL_HYDRA_DEMOD_ID_5,
	MXL_HYDRA_DEMOD_ID_6,
	MXL_HYDRA_DEMOD_ID_7,
	MXL_HYDRA_DEMOD_MAX
पूर्ण;

#घोषणा MXL_DEMOD_SCRAMBLE_SEQ_LEN  12

#घोषणा MAX_STEP_SIZE_24_XTAL_102_05_KHZ  195
#घोषणा MAX_STEP_SIZE_24_XTAL_204_10_KHZ  215
#घोषणा MAX_STEP_SIZE_24_XTAL_306_15_KHZ  203
#घोषणा MAX_STEP_SIZE_24_XTAL_408_20_KHZ  177

#घोषणा MAX_STEP_SIZE_27_XTAL_102_05_KHZ  195
#घोषणा MAX_STEP_SIZE_27_XTAL_204_10_KHZ  215
#घोषणा MAX_STEP_SIZE_27_XTAL_306_15_KHZ  203
#घोषणा MAX_STEP_SIZE_27_XTAL_408_20_KHZ  177

#घोषणा MXL_HYDRA_SPECTRUM_MIN_FREQ_KHZ  300000
#घोषणा MXL_HYDRA_SPECTRUM_MAX_FREQ_KHZ 2350000

क्रमागत MXL_DEMOD_CHAN_PARAMS_OFFSET_E अणु
	DMD_STANDARD_ADDR = 0,
	DMD_SPECTRUM_INVERSION_ADDR,
	DMD_SPECTRUM_ROLL_OFF_ADDR,
	DMD_SYMBOL_RATE_ADDR,
	DMD_MODULATION_SCHEME_ADDR,
	DMD_FEC_CODE_RATE_ADDR,
	DMD_SNR_ADDR,
	DMD_FREQ_OFFSET_ADDR,
	DMD_CTL_FREQ_OFFSET_ADDR,
	DMD_STR_FREQ_OFFSET_ADDR,
	DMD_FTL_FREQ_OFFSET_ADDR,
	DMD_STR_NBC_SYNC_LOCK_ADDR,
	DMD_CYCLE_SLIP_COUNT_ADDR,
	DMD_DISPLAY_IQ_ADDR,
	DMD_DVBS2_CRC_ERRORS_ADDR,
	DMD_DVBS2_PER_COUNT_ADDR,
	DMD_DVBS2_PER_WINDOW_ADDR,
	DMD_DVBS_CORR_RS_ERRORS_ADDR,
	DMD_DVBS_UNCORR_RS_ERRORS_ADDR,
	DMD_DVBS_BER_COUNT_ADDR,
	DMD_DVBS_BER_WINDOW_ADDR,
	DMD_TUNER_ID_ADDR,
	DMD_DVBS2_PILOT_ON_OFF_ADDR,
	DMD_FREQ_SEARCH_RANGE_IN_KHZ_ADDR,

	MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE,
पूर्ण;

क्रमागत MXL_HYDRA_TUNER_ID_E अणु
	MXL_HYDRA_TUNER_ID_0 = 0,
	MXL_HYDRA_TUNER_ID_1,
	MXL_HYDRA_TUNER_ID_2,
	MXL_HYDRA_TUNER_ID_3,
	MXL_HYDRA_TUNER_MAX
पूर्ण;

क्रमागत MXL_HYDRA_BCAST_STD_E अणु
	MXL_HYDRA_DSS = 0,
	MXL_HYDRA_DVBS,
	MXL_HYDRA_DVBS2,
पूर्ण;

क्रमागत MXL_HYDRA_FEC_E अणु
	MXL_HYDRA_FEC_AUTO = 0,
	MXL_HYDRA_FEC_1_2,
	MXL_HYDRA_FEC_3_5,
	MXL_HYDRA_FEC_2_3,
	MXL_HYDRA_FEC_3_4,
	MXL_HYDRA_FEC_4_5,
	MXL_HYDRA_FEC_5_6,
	MXL_HYDRA_FEC_6_7,
	MXL_HYDRA_FEC_7_8,
	MXL_HYDRA_FEC_8_9,
	MXL_HYDRA_FEC_9_10,
पूर्ण;

क्रमागत MXL_HYDRA_MODULATION_E अणु
	MXL_HYDRA_MOD_AUTO = 0,
	MXL_HYDRA_MOD_QPSK,
	MXL_HYDRA_MOD_8PSK
पूर्ण;

क्रमागत MXL_HYDRA_SPECTRUM_E अणु
	MXL_HYDRA_SPECTRUM_AUTO = 0,
	MXL_HYDRA_SPECTRUM_INVERTED,
	MXL_HYDRA_SPECTRUM_NON_INVERTED,
पूर्ण;

क्रमागत MXL_HYDRA_ROLLOFF_E अणु
	MXL_HYDRA_ROLLOFF_AUTO  = 0,
	MXL_HYDRA_ROLLOFF_0_20,
	MXL_HYDRA_ROLLOFF_0_25,
	MXL_HYDRA_ROLLOFF_0_35
पूर्ण;

क्रमागत MXL_HYDRA_PILOTS_E अणु
	MXL_HYDRA_PILOTS_OFF  = 0,
	MXL_HYDRA_PILOTS_ON,
	MXL_HYDRA_PILOTS_AUTO
पूर्ण;

क्रमागत MXL_HYDRA_CONSTELLATION_SRC_E अणु
	MXL_HYDRA_FORMATTER = 0,
	MXL_HYDRA_LEGACY_FEC,
	MXL_HYDRA_FREQ_RECOVERY,
	MXL_HYDRA_NBC,
	MXL_HYDRA_CTL,
	MXL_HYDRA_EQ,
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_LOCK_T अणु
	पूर्णांक agc_lock; /* AGC lock info */
	पूर्णांक fec_lock; /* Demod FEC block lock info */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_STATUS_DVBS_T अणु
	u32 rs_errors;        /* RS decoder err counter */
	u32 ber_winकरोw;       /* Ber Winकरोws */
	u32 ber_count;        /* BER count */
	u32 ber_winकरोw_iter1; /* Ber Winकरोws - post viterbi */
	u32 ber_count_iter1;  /* BER count - post viterbi */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_STATUS_DSS_T अणु
	u32 rs_errors;  /* RS decoder err counter */
	u32 ber_winकरोw; /* Ber Winकरोws */
	u32 ber_count;  /* BER count */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_STATUS_DVBS2_T अणु
	u32 crc_errors;        /* CRC error counter */
	u32 packet_error_count; /* Number of packet errors */
	u32 total_packets;     /* Total packets */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_STATUS_T अणु
	क्रमागत MXL_HYDRA_BCAST_STD_E standard_mask; /* Standard DVB-S, DVB-S2 or DSS */

	जोड़ अणु
		काष्ठा MXL_HYDRA_DEMOD_STATUS_DVBS_T demod_status_dvbs;   /* DVB-S demod status */
		काष्ठा MXL_HYDRA_DEMOD_STATUS_DVBS2_T demod_status_dvbs2; /* DVB-S2 demod status */
		काष्ठा MXL_HYDRA_DEMOD_STATUS_DSS_T demod_status_dss;     /* DSS demod status */
	पूर्ण u;
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_SIG_OFFSET_INFO_T अणु
	s32 carrier_offset_in_hz; /* CRL offset info */
	s32 symbol_offset_in_symbol; /* SRL offset info */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_SCRAMBLE_INFO_T अणु
	u8 scramble_sequence[MXL_DEMOD_SCRAMBLE_SEQ_LEN]; /* scramble sequence */
	u32 scramble_code; /* scramble gold code */
पूर्ण;

क्रमागत MXL_HYDRA_SPECTRUM_STEP_SIZE_E अणु
	MXL_HYDRA_STEP_SIZE_24_XTAL_102_05KHZ, /* 102.05 KHz क्रम 24 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_24_XTAL_204_10KHZ, /* 204.10 KHz क्रम 24 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_24_XTAL_306_15KHZ, /* 306.15 KHz क्रम 24 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ, /* 408.20 KHz क्रम 24 MHz XTAL */

	MXL_HYDRA_STEP_SIZE_27_XTAL_102_05KHZ, /* 102.05 KHz क्रम 27 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_27_XTAL_204_35KHZ, /* 204.35 KHz क्रम 27 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_27_XTAL_306_52KHZ, /* 306.52 KHz क्रम 27 MHz XTAL */
	MXL_HYDRA_STEP_SIZE_27_XTAL_408_69KHZ, /* 408.69 KHz क्रम 27 MHz XTAL */
पूर्ण;

क्रमागत MXL_HYDRA_SPECTRUM_RESOLUTION_E अणु
	MXL_HYDRA_SPECTRUM_RESOLUTION_00_1_DB, /* 0.1 dB */
	MXL_HYDRA_SPECTRUM_RESOLUTION_01_0_DB, /* 1.0 dB */
	MXL_HYDRA_SPECTRUM_RESOLUTION_05_0_DB, /* 5.0 dB */
	MXL_HYDRA_SPECTRUM_RESOLUTION_10_0_DB, /* 10 dB */
पूर्ण;

क्रमागत MXL_HYDRA_SPECTRUM_ERROR_CODE_E अणु
	MXL_SPECTRUM_NO_ERROR,
	MXL_SPECTRUM_INVALID_PARAMETER,
	MXL_SPECTRUM_INVALID_STEP_SIZE,
	MXL_SPECTRUM_BW_CANNOT_BE_COVERED,
	MXL_SPECTRUM_DEMOD_BUSY,
	MXL_SPECTRUM_TUNER_NOT_ENABLED,
पूर्ण;

काष्ठा MXL_HYDRA_SPECTRUM_REQ_T अणु
	u32 tuner_index; /* TUNER Ctrl: one of MXL58x_TUNER_ID_E */
	u32 demod_index; /* DEMOD Ctrl: one of MXL58x_DEMOD_ID_E */
	क्रमागत MXL_HYDRA_SPECTRUM_STEP_SIZE_E step_size_in_khz;
	u32 starting_freq_ink_hz;
	u32 total_steps;
	क्रमागत MXL_HYDRA_SPECTRUM_RESOLUTION_E spectrum_भागision;
पूर्ण;

क्रमागत MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E अणु
	MXL_HYDRA_SEARCH_MAX_OFFSET = 0, /* DMD searches क्रम max freq offset (i.e. 5MHz) */
	MXL_HYDRA_SEARCH_BW_PLUS_ROLLOFF, /* DMD searches क्रम BW + ROLLOFF/2 */
पूर्ण;

काष्ठा MXL58X_CFG_FREQ_OFF_SEARCH_RANGE_T अणु
	u32 demod_index;
	क्रमागत MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E search_type;
पूर्ण;

/* there are two slices
 * slice0 - TS0, TS1, TS2 & TS3
 * slice1 - TS4, TS5, TS6 & TS7
 */
#घोषणा MXL_HYDRA_TS_SLICE_MAX  2

#घोषणा MAX_FIXED_PID_NUM   32

#घोषणा MXL_HYDRA_NCO_CLK   418 /* 418 MHz */

#घोषणा MXL_HYDRA_MAX_TS_CLOCK  139 /* 139 MHz */

#घोषणा MXL_HYDRA_TS_FIXED_PID_FILT_SIZE          32

#घोषणा MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT    33   /* Shared PID filter size in 1-1 mux mode */
#घोषणा MXL_HYDRA_SHARED_PID_FILT_SIZE_2_TO_1     66   /* Shared PID filter size in 2-1 mux mode */
#घोषणा MXL_HYDRA_SHARED_PID_FILT_SIZE_4_TO_1     132  /* Shared PID filter size in 4-1 mux mode */

क्रमागत MXL_HYDRA_PID_BANK_TYPE_E अणु
	MXL_HYDRA_SOFTWARE_PID_BANK = 0,
	MXL_HYDRA_HARDWARE_PID_BANK,
पूर्ण;

क्रमागत MXL_HYDRA_TS_MUX_MODE_E अणु
	MXL_HYDRA_TS_MUX_PID_REMAP = 0,
	MXL_HYDRA_TS_MUX_PREFIX_EXTRA_HEADER = 1,
पूर्ण;

क्रमागत MXL_HYDRA_TS_MUX_TYPE_E अणु
	MXL_HYDRA_TS_MUX_DISABLE = 0, /* No Mux ( 1 TSIF to 1 TSIF) */
	MXL_HYDRA_TS_MUX_2_TO_1, /* Mux 2 TSIF to 1 TSIF */
	MXL_HYDRA_TS_MUX_4_TO_1, /* Mux 4 TSIF to 1 TSIF */
पूर्ण;

क्रमागत MXL_HYDRA_TS_GROUP_E अणु
	MXL_HYDRA_TS_GROUP_0_3 = 0, /* TS group 0 to 3 (TS0, TS1, TS2 & TS3) */
	MXL_HYDRA_TS_GROUP_4_7,     /* TS group 0 to 3 (TS4, TS5, TS6 & TS7) */
पूर्ण;

क्रमागत MXL_HYDRA_TS_PID_FLT_CTRL_E अणु
	MXL_HYDRA_TS_PIDS_ALLOW_ALL = 0, /* Allow all pids */
	MXL_HYDRA_TS_PIDS_DROP_ALL,	 /* Drop all pids */
	MXL_HYDRA_TS_INVALIDATE_PID_FILTER, /* Delete current PD filter in the device */
पूर्ण;

क्रमागत MXL_HYDRA_TS_PID_TYPE_E अणु
	MXL_HYDRA_TS_PID_FIXED = 0,
	MXL_HYDRA_TS_PID_REGULAR,
पूर्ण;

काष्ठा MXL_HYDRA_TS_PID_T अणु
	u16 original_pid;           /* pid from TS */
	u16 remapped_pid;           /* remapped pid */
	क्रमागत MXL_BOOL_E enable;         /* enable or disable pid */
	क्रमागत MXL_BOOL_E allow_or_drop;    /* allow or drop pid */
	क्रमागत MXL_BOOL_E enable_pid_remap; /* enable or disable pid remap */
	u8 bond_id;                 /* Bond ID in A0 always 0 - Only क्रम 568 Sku */
	u8 dest_id;                 /* Output port ID क्रम the PID - Only क्रम 568 Sku */
पूर्ण;

काष्ठा MXL_HYDRA_TS_MUX_PREFIX_HEADER_T अणु
	क्रमागत MXL_BOOL_E enable;
	u8 num_byte;
	u8 header[12];
पूर्ण;

क्रमागत MXL_HYDRA_PID_FILTER_BANK_E अणु
	MXL_HYDRA_PID_BANK_A = 0,
	MXL_HYDRA_PID_BANK_B,
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_DATA_FMT_E अणु
	MXL_HYDRA_MPEG_SERIAL_MSB_1ST = 0,
	MXL_HYDRA_MPEG_SERIAL_LSB_1ST,

	MXL_HYDRA_MPEG_SYNC_WIDTH_BIT = 0,
	MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_MODE_E अणु
	MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE = 0, /* MPEG 4 Wire serial mode */
	MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE,     /* MPEG 3 Wire serial mode */
	MXL_HYDRA_MPEG_MODE_SERIAL_2_WIRE,     /* MPEG 2 Wire serial mode */
	MXL_HYDRA_MPEG_MODE_PARALLEL           /* MPEG parallel mode - valid only क्रम MxL581 */
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_CLK_TYPE_E अणु
	MXL_HYDRA_MPEG_CLK_CONTINUOUS = 0, /* Continuous MPEG घड़ी */
	MXL_HYDRA_MPEG_CLK_GAPPED,         /* Gapped (gated) MPEG घड़ी */
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_CLK_FMT_E अणु
	MXL_HYDRA_MPEG_ACTIVE_LOW = 0,
	MXL_HYDRA_MPEG_ACTIVE_HIGH,

	MXL_HYDRA_MPEG_CLK_NEGATIVE = 0,
	MXL_HYDRA_MPEG_CLK_POSITIVE,

	MXL_HYDRA_MPEG_CLK_IN_PHASE = 0,
	MXL_HYDRA_MPEG_CLK_INVERTED,
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_CLK_PHASE_E अणु
	MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG = 0,
	MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_90_DEG,
	MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_180_DEG,
	MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_270_DEG
पूर्ण;

क्रमागत MXL_HYDRA_MPEG_ERR_INDICATION_E अणु
	MXL_HYDRA_MPEG_ERR_REPLACE_SYNC = 0,
	MXL_HYDRA_MPEG_ERR_REPLACE_VALID,
	MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED
पूर्ण;

काष्ठा MXL_HYDRA_MPEGOUT_PARAM_T अणु
	पूर्णांक                                  enable;               /* Enable or Disable MPEG OUT */
	क्रमागत MXL_HYDRA_MPEG_CLK_TYPE_E       mpeg_clk_type;          /* Continuous or gapped */
	क्रमागत MXL_HYDRA_MPEG_CLK_FMT_E        mpeg_clk_pol;           /* MPEG Clk polarity */
	u8                                   max_mpeg_clk_rate;       /* Max MPEG Clk rate (0 - 104 MHz, 139 MHz) */
	क्रमागत MXL_HYDRA_MPEG_CLK_PHASE_E      mpeg_clk_phase;         /* MPEG Clk phase */
	क्रमागत MXL_HYDRA_MPEG_DATA_FMT_E       lsb_or_msb_first;        /* LSB first or MSB first in TS transmission */
	क्रमागत MXL_HYDRA_MPEG_DATA_FMT_E       mpeg_sync_pulse_width;   /* MPEG SYNC pulse width (1-bit or 1-byte) */
	क्रमागत MXL_HYDRA_MPEG_CLK_FMT_E        mpeg_valid_pol;         /* MPEG VALID polarity */
	क्रमागत MXL_HYDRA_MPEG_CLK_FMT_E        mpeg_sync_pol;          /* MPEG SYNC polarity */
	क्रमागत MXL_HYDRA_MPEG_MODE_E           mpeg_mode;             /* config 4/3/2-wire serial or parallel TS out */
	क्रमागत MXL_HYDRA_MPEG_ERR_INDICATION_E mpeg_error_indication;  /* Enable or Disable MPEG error indication */
पूर्ण;

क्रमागत MXL_HYDRA_EXT_TS_IN_ID_E अणु
	MXL_HYDRA_EXT_TS_IN_0 = 0,
	MXL_HYDRA_EXT_TS_IN_1,
	MXL_HYDRA_EXT_TS_IN_2,
	MXL_HYDRA_EXT_TS_IN_3,
	MXL_HYDRA_EXT_TS_IN_MAX
पूर्ण;

क्रमागत MXL_HYDRA_TS_OUT_ID_E अणु
	MXL_HYDRA_TS_OUT_0 = 0,
	MXL_HYDRA_TS_OUT_1,
	MXL_HYDRA_TS_OUT_2,
	MXL_HYDRA_TS_OUT_3,
	MXL_HYDRA_TS_OUT_4,
	MXL_HYDRA_TS_OUT_5,
	MXL_HYDRA_TS_OUT_6,
	MXL_HYDRA_TS_OUT_7,
	MXL_HYDRA_TS_OUT_MAX
पूर्ण;

क्रमागत MXL_HYDRA_TS_DRIVE_STRENGTH_E अणु
	MXL_HYDRA_TS_DRIVE_STRENGTH_1X = 0,
	MXL_HYDRA_TS_DRIVE_STRENGTH_2X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_3X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_4X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_5X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_6X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_7X,
	MXL_HYDRA_TS_DRIVE_STRENGTH_8X
पूर्ण;

क्रमागत MXL_HYDRA_DEVICE_E अणु
	MXL_HYDRA_DEVICE_581 = 0,
	MXL_HYDRA_DEVICE_584,
	MXL_HYDRA_DEVICE_585,
	MXL_HYDRA_DEVICE_544,
	MXL_HYDRA_DEVICE_561,
	MXL_HYDRA_DEVICE_TEST,
	MXL_HYDRA_DEVICE_582,
	MXL_HYDRA_DEVICE_541,
	MXL_HYDRA_DEVICE_568,
	MXL_HYDRA_DEVICE_542,
	MXL_HYDRA_DEVICE_541S,
	MXL_HYDRA_DEVICE_561S,
	MXL_HYDRA_DEVICE_581S,
	MXL_HYDRA_DEVICE_MAX
पूर्ण;

/* Demod IQ data */
काष्ठा MXL_HYDRA_DEMOD_IQ_SRC_T अणु
	u32 demod_id;
	u32 source_of_iq; /* == 0, it means I/Q comes from Formatter
			 * == 1, Legacy FEC
			 * == 2, Frequency Recovery
			 * == 3, NBC
			 * == 4, CTL
			 * == 5, EQ
			 * == 6, FPGA
			 */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_ABORT_TUNE_T अणु
	u32 demod_id;
पूर्ण;

काष्ठा MXL_HYDRA_TUNER_CMD अणु
	u8 tuner_id;
	u8 enable;
पूर्ण;

/* Demod Para क्रम Channel Tune */
काष्ठा MXL_HYDRA_DEMOD_PARAM_T अणु
	u32 tuner_index;
	u32 demod_index;
	u32 frequency_in_hz;     /* Frequency */
	u32 standard;          /* one of MXL_HYDRA_BCAST_STD_E */
	u32 spectrum_inversion; /* Input : Spectrum inversion. */
	u32 roll_off;           /* rollOff (alpha) factor */
	u32 symbol_rate_in_hz;    /* Symbol rate */
	u32 pilots;            /* TRUE = pilots enabled */
	u32 modulation_scheme;  /* Input : Modulation Scheme is one of MXL_HYDRA_MODULATION_E */
	u32 fec_code_rate;       /* Input : Forward error correction rate. Is one of MXL_HYDRA_FEC_E */
	u32 max_carrier_offset_in_mhz; /* Maximum carrier freq offset in MHz. Same as freqSearchRangeKHz, but in unit of MHz. */
पूर्ण;

काष्ठा MXL_HYDRA_DEMOD_SCRAMBLE_CODE_T अणु
	u32 demod_index;
	u8 scramble_sequence[12]; /* scramble sequence */
	u32 scramble_code; /* scramble gold code */
पूर्ण;

काष्ठा MXL_INTR_CFG_T अणु
	u32 पूर्णांकr_type;
	u32 पूर्णांकr_duration_in_nano_secs;
	u32 पूर्णांकr_mask;
पूर्ण;

काष्ठा MXL_HYDRA_POWER_MODE_CMD अणु
	u8 घातer_mode; /* क्रमागतeration values are defined in MXL_HYDRA_PWR_MODE_E (device API.h) */
पूर्ण;

काष्ठा MXL_HYDRA_RF_WAKEUP_PARAM_T अणु
	u32 समय_पूर्णांकerval_in_seconds; /* in seconds */
	u32 tuner_index;
	s32 rssi_threshold;
पूर्ण;

काष्ठा MXL_HYDRA_RF_WAKEUP_CFG_T अणु
	u32 tuner_count;
	काष्ठा MXL_HYDRA_RF_WAKEUP_PARAM_T params;
पूर्ण;

क्रमागत MXL_HYDRA_AUX_CTRL_MODE_E अणु
	MXL_HYDRA_AUX_CTRL_MODE_FSK = 0, /* Select FSK controller */
	MXL_HYDRA_AUX_CTRL_MODE_DISEQC,  /* Select DiSEqC controller */
पूर्ण;

क्रमागत MXL_HYDRA_DISEQC_OPMODE_E अणु
	MXL_HYDRA_DISEQC_ENVELOPE_MODE = 0,
	MXL_HYDRA_DISEQC_TONE_MODE,
पूर्ण;

क्रमागत MXL_HYDRA_DISEQC_VER_E अणु
	MXL_HYDRA_DISEQC_1_X = 0, /* Config DiSEqC 1.x mode */
	MXL_HYDRA_DISEQC_2_X, /* Config DiSEqC 2.x mode */
	MXL_HYDRA_DISEQC_DISABLE /* Disable DiSEqC */
पूर्ण;

क्रमागत MXL_HYDRA_DISEQC_CARRIER_FREQ_E अणु
	MXL_HYDRA_DISEQC_CARRIER_FREQ_22KHZ = 0, /* DiSEqC संकेत frequency of 22 KHz */
	MXL_HYDRA_DISEQC_CARRIER_FREQ_33KHZ,     /* DiSEqC संकेत frequency of 33 KHz */
	MXL_HYDRA_DISEQC_CARRIER_FREQ_44KHZ      /* DiSEqC संकेत frequency of 44 KHz */
पूर्ण;

क्रमागत MXL_HYDRA_DISEQC_ID_E अणु
	MXL_HYDRA_DISEQC_ID_0 = 0,
	MXL_HYDRA_DISEQC_ID_1,
	MXL_HYDRA_DISEQC_ID_2,
	MXL_HYDRA_DISEQC_ID_3
पूर्ण;

क्रमागत MXL_HYDRA_FSK_OP_MODE_E अणु
	MXL_HYDRA_FSK_CFG_TYPE_39KPBS = 0, /* 39.0kbps */
	MXL_HYDRA_FSK_CFG_TYPE_39_017KPBS, /* 39.017kbps */
	MXL_HYDRA_FSK_CFG_TYPE_115_2KPBS   /* 115.2kbps */
पूर्ण;

काष्ठा MXL58X_DSQ_OP_MODE_T अणु
	u32 diseqc_id; /* DSQ 0, 1, 2 or 3 */
	u32 op_mode; /* Envelope mode (0) or पूर्णांकernal tone mode (1) */
	u32 version; /* 0: 1.0, 1: 1.1, 2: Disable */
	u32 center_freq; /* 0: 22KHz, 1: 33KHz and 2: 44 KHz */
पूर्ण;

काष्ठा MXL_HYDRA_DISEQC_CFG_CONT_TONE_T अणु
	u32 diseqc_id;
	u32 cont_tone_flag; /* 1: Enable , 0: Disable */
पूर्ण;
