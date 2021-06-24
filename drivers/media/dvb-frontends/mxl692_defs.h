<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the MaxLinear MxL69x family of combo tuners/demods
 *
 * Copyright (C) 2020 Brad Love <brad@nextdimension.cc>
 *
 * based on code:
 * Copyright (c) 2016 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*****************************************************************************
 *	Defines
 *****************************************************************************
 */
#घोषणा MXL_EAGLE_HOST_MSG_HEADER_SIZE  8
#घोषणा MXL_EAGLE_FW_MAX_SIZE_IN_KB     76
#घोषणा MXL_EAGLE_QAM_FFE_TAPS_LENGTH   16
#घोषणा MXL_EAGLE_QAM_SPUR_TAPS_LENGTH  32
#घोषणा MXL_EAGLE_QAM_DFE_TAPS_LENGTH   72
#घोषणा MXL_EAGLE_ATSC_FFE_TAPS_LENGTH  4096
#घोषणा MXL_EAGLE_ATSC_DFE_TAPS_LENGTH  384
#घोषणा MXL_EAGLE_VERSION_SIZE          5     /* A.B.C.D-RCx */
#घोषणा MXL_EAGLE_FW_LOAD_TIME          50

#घोषणा MXL_EAGLE_FW_MAX_SIZE_IN_KB       76
#घोषणा MXL_EAGLE_FW_HEADER_SIZE          16
#घोषणा MXL_EAGLE_FW_SEGMENT_HEADER_SIZE  8
#घोषणा MXL_EAGLE_MAX_I2C_PACKET_SIZE     58
#घोषणा MXL_EAGLE_I2C_MHEADER_SIZE        6
#घोषणा MXL_EAGLE_I2C_PHEADER_SIZE        2

/* Enum of Eagle family devices */
क्रमागत MXL_EAGLE_DEVICE_E अणु
	MXL_EAGLE_DEVICE_691 = 1,    /* Device Mxl691 */
	MXL_EAGLE_DEVICE_248 = 2,    /* Device Mxl248 */
	MXL_EAGLE_DEVICE_692 = 3,    /* Device Mxl692 */
	MXL_EAGLE_DEVICE_MAX,        /* No such device */
पूर्ण;

#घोषणा VER_A   1
#घोषणा VER_B   1
#घोषणा VER_C   1
#घोषणा VER_D   3
#घोषणा VER_E   6

/* Enum of Host to Eagle I2C protocol opcodes */
क्रमागत MXL_EAGLE_OPCODE_E अणु
	/* DEVICE */
	MXL_EAGLE_OPCODE_DEVICE_DEMODULATOR_TYPE_SET,
	MXL_EAGLE_OPCODE_DEVICE_MPEG_OUT_PARAMS_SET,
	MXL_EAGLE_OPCODE_DEVICE_POWERMODE_SET,
	MXL_EAGLE_OPCODE_DEVICE_GPIO_सूचीECTION_SET,
	MXL_EAGLE_OPCODE_DEVICE_GPO_LEVEL_SET,
	MXL_EAGLE_OPCODE_DEVICE_INTR_MASK_SET,
	MXL_EAGLE_OPCODE_DEVICE_IO_MUX_SET,
	MXL_EAGLE_OPCODE_DEVICE_VERSION_GET,
	MXL_EAGLE_OPCODE_DEVICE_STATUS_GET,
	MXL_EAGLE_OPCODE_DEVICE_GPI_LEVEL_GET,

	/* TUNER */
	MXL_EAGLE_OPCODE_TUNER_CHANNEL_TUNE_SET,
	MXL_EAGLE_OPCODE_TUNER_LOCK_STATUS_GET,
	MXL_EAGLE_OPCODE_TUNER_AGC_STATUS_GET,

	/* ATSC */
	MXL_EAGLE_OPCODE_ATSC_INIT_SET,
	MXL_EAGLE_OPCODE_ATSC_ACQUIRE_CARRIER_SET,
	MXL_EAGLE_OPCODE_ATSC_STATUS_GET,
	MXL_EAGLE_OPCODE_ATSC_ERROR_COUNTERS_GET,
	MXL_EAGLE_OPCODE_ATSC_EQUALIZER_FILTER_DFE_TAPS_GET,
	MXL_EAGLE_OPCODE_ATSC_EQUALIZER_FILTER_FFE_TAPS_GET,

	/* QAM */
	MXL_EAGLE_OPCODE_QAM_PARAMS_SET,
	MXL_EAGLE_OPCODE_QAM_RESTART_SET,
	MXL_EAGLE_OPCODE_QAM_STATUS_GET,
	MXL_EAGLE_OPCODE_QAM_ERROR_COUNTERS_GET,
	MXL_EAGLE_OPCODE_QAM_CONSTELLATION_VALUE_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_FFE_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_SPUR_START_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_SPUR_END_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_TAPS_NUMBER_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_START_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_MIDDLE_GET,
	MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_END_GET,

	/* OOB */
	MXL_EAGLE_OPCODE_OOB_PARAMS_SET,
	MXL_EAGLE_OPCODE_OOB_RESTART_SET,
	MXL_EAGLE_OPCODE_OOB_ERROR_COUNTERS_GET,
	MXL_EAGLE_OPCODE_OOB_STATUS_GET,

	/* SMA */
	MXL_EAGLE_OPCODE_SMA_INIT_SET,
	MXL_EAGLE_OPCODE_SMA_PARAMS_SET,
	MXL_EAGLE_OPCODE_SMA_TRANSMIT_SET,
	MXL_EAGLE_OPCODE_SMA_RECEIVE_GET,

	/* DEBUG */
	MXL_EAGLE_OPCODE_INTERNAL,

	MXL_EAGLE_OPCODE_MAX = 70,
पूर्ण;

/* Enum of Host to Eagle I2C protocol opcodes */
अटल स्थिर अक्षर * स्थिर MXL_EAGLE_OPCODE_STRING[] = अणु
	/* DEVICE */
	"DEVICE_DEMODULATOR_TYPE_SET",
	"DEVICE_MPEG_OUT_PARAMS_SET",
	"DEVICE_POWERMODE_SET",
	"DEVICE_GPIO_DIRECTION_SET",
	"DEVICE_GPO_LEVEL_SET",
	"DEVICE_INTR_MASK_SET",
	"DEVICE_IO_MUX_SET",
	"DEVICE_VERSION_GET",
	"DEVICE_STATUS_GET",
	"DEVICE_GPI_LEVEL_GET",

	/* TUNER */
	"TUNER_CHANNEL_TUNE_SET",
	"TUNER_LOCK_STATUS_GET",
	"TUNER_AGC_STATUS_GET",

	/* ATSC */
	"ATSC_INIT_SET",
	"ATSC_ACQUIRE_CARRIER_SET",
	"ATSC_STATUS_GET",
	"ATSC_ERROR_COUNTERS_GET",
	"ATSC_EQUALIZER_FILTER_DFE_TAPS_GET",
	"ATSC_EQUALIZER_FILTER_FFE_TAPS_GET",

	/* QAM */
	"QAM_PARAMS_SET",
	"QAM_RESTART_SET",
	"QAM_STATUS_GET",
	"QAM_ERROR_COUNTERS_GET",
	"QAM_CONSTELLATION_VALUE_GET",
	"QAM_EQUALIZER_FILTER_FFE_GET",
	"QAM_EQUALIZER_FILTER_SPUR_START_GET",
	"QAM_EQUALIZER_FILTER_SPUR_END_GET",
	"QAM_EQUALIZER_FILTER_DFE_TAPS_NUMBER_GET",
	"QAM_EQUALIZER_FILTER_DFE_START_GET",
	"QAM_EQUALIZER_FILTER_DFE_MIDDLE_GET",
	"QAM_EQUALIZER_FILTER_DFE_END_GET",

	/* OOB */
	"OOB_PARAMS_SET",
	"OOB_RESTART_SET",
	"OOB_ERROR_COUNTERS_GET",
	"OOB_STATUS_GET",

	/* SMA */
	"SMA_INIT_SET",
	"SMA_PARAMS_SET",
	"SMA_TRANSMIT_SET",
	"SMA_RECEIVE_GET",

	/* DEBUG */
	"INTERNAL",
पूर्ण;

/* Enum of Callabck function types */
क्रमागत MXL_EAGLE_CB_TYPE_E अणु
	MXL_EAGLE_CB_FW_DOWNLOAD = 0,
पूर्ण;

/* Enum of घातer supply types */
क्रमागत MXL_EAGLE_POWER_SUPPLY_SOURCE_E अणु
	MXL_EAGLE_POWER_SUPPLY_SOURCE_SINGLE,   /* Single supply of 3.3V */
	MXL_EAGLE_POWER_SUPPLY_SOURCE_DUAL,     /* Dual supply, 1.8V & 3.3V */
पूर्ण;

/* Enum of I/O pad drive modes */
क्रमागत MXL_EAGLE_IO_MUX_DRIVE_MODE_E अणु
	MXL_EAGLE_IO_MUX_DRIVE_MODE_1X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_2X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_3X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_4X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_5X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_6X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_7X,
	MXL_EAGLE_IO_MUX_DRIVE_MODE_8X,
पूर्ण;

/* Enum of demodulator types. Used क्रम selection of demodulator
 * type in relevant devices, e.g. ATSC vs. QAM in Mxl691
 */
क्रमागत MXL_EAGLE_DEMOD_TYPE_E अणु
	MXL_EAGLE_DEMOD_TYPE_QAM,    /* Mxl248 or Mxl692 */
	MXL_EAGLE_DEMOD_TYPE_OOB,    /* Mxl248 only */
	MXL_EAGLE_DEMOD_TYPE_ATSC    /* Mxl691 or Mxl692 */
पूर्ण;

/* Enum of घातer modes. Used क्रम initial
 * activation, or क्रम activating sleep mode
 */
क्रमागत MXL_EAGLE_POWER_MODE_E अणु
	MXL_EAGLE_POWER_MODE_SLEEP,
	MXL_EAGLE_POWER_MODE_ACTIVE
पूर्ण;

/* Enum of GPIOs, used in device GPIO APIs */
क्रमागत MXL_EAGLE_GPIO_NUMBER_E अणु
	MXL_EAGLE_GPIO_NUMBER_0,
	MXL_EAGLE_GPIO_NUMBER_1,
	MXL_EAGLE_GPIO_NUMBER_2,
	MXL_EAGLE_GPIO_NUMBER_3,
	MXL_EAGLE_GPIO_NUMBER_4,
	MXL_EAGLE_GPIO_NUMBER_5,
	MXL_EAGLE_GPIO_NUMBER_6
पूर्ण;

/* Enum of GPIO directions, used in GPIO direction configuration API */
क्रमागत MXL_EAGLE_GPIO_सूचीECTION_E अणु
	MXL_EAGLE_GPIO_सूचीECTION_INPUT,
	MXL_EAGLE_GPIO_सूचीECTION_OUTPUT
पूर्ण;

/* Enum of GPIO level, used in device GPIO APIs */
क्रमागत MXL_EAGLE_GPIO_LEVEL_E अणु
	MXL_EAGLE_GPIO_LEVEL_LOW,
	MXL_EAGLE_GPIO_LEVEL_HIGH,
पूर्ण;

/* Enum of I/O Mux function, used in device I/O mux configuration API */
क्रमागत MXL_EAGLE_IOMUX_FUNCTION_E अणु
	MXL_EAGLE_IOMUX_FUNC_FEC_LOCK,
	MXL_EAGLE_IOMUX_FUNC_MERR,
पूर्ण;

/* Enum of MPEG Data क्रमmat, used in MPEG and OOB output configuration */
क्रमागत MXL_EAGLE_MPEG_DATA_FORMAT_E अणु
	MXL_EAGLE_DATA_SERIAL_LSB_1ST = 0,
	MXL_EAGLE_DATA_SERIAL_MSB_1ST,

	MXL_EAGLE_DATA_SYNC_WIDTH_BIT = 0,
	MXL_EAGLE_DATA_SYNC_WIDTH_BYTE
पूर्ण;

/* Enum of MPEG Clock क्रमmat, used in MPEG and OOB output configuration */
क्रमागत MXL_EAGLE_MPEG_CLOCK_FORMAT_E अणु
	MXL_EAGLE_CLOCK_ACTIVE_HIGH = 0,
	MXL_EAGLE_CLOCK_ACTIVE_LOW,

	MXL_EAGLE_CLOCK_POSITIVE  = 0,
	MXL_EAGLE_CLOCK_NEGATIVE,

	MXL_EAGLE_CLOCK_IN_PHASE = 0,
	MXL_EAGLE_CLOCK_INVERTED,
पूर्ण;

/* Enum of MPEG Clock speeds, used in MPEG output configuration */
क्रमागत MXL_EAGLE_MPEG_CLOCK_RATE_E अणु
	MXL_EAGLE_MPEG_CLOCK_54MHZ,
	MXL_EAGLE_MPEG_CLOCK_40_5MHZ,
	MXL_EAGLE_MPEG_CLOCK_27MHZ,
	MXL_EAGLE_MPEG_CLOCK_13_5MHZ,
पूर्ण;

/* Enum of Interrupt mask bit, used in host पूर्णांकerrupt configuration */
क्रमागत MXL_EAGLE_INTR_MASK_BITS_E अणु
	MXL_EAGLE_INTR_MASK_DEMOD = 0,
	MXL_EAGLE_INTR_MASK_SMA_RX = 1,
	MXL_EAGLE_INTR_MASK_WDOG = 31
पूर्ण;

/* Enum of QAM Demodulator type, used in QAM configuration */
क्रमागत MXL_EAGLE_QAM_DEMOD_ANNEX_TYPE_E अणु
	MXL_EAGLE_QAM_DEMOD_ANNEX_B,    /* J.83B */
	MXL_EAGLE_QAM_DEMOD_ANNEX_A,    /* DVB-C */
पूर्ण;

/* Enum of QAM Demodulator modulation, used in QAM configuration and status */
क्रमागत MXL_EAGLE_QAM_DEMOD_QAM_TYPE_E अणु
	MXL_EAGLE_QAM_DEMOD_QAM16,
	MXL_EAGLE_QAM_DEMOD_QAM64,
	MXL_EAGLE_QAM_DEMOD_QAM256,
	MXL_EAGLE_QAM_DEMOD_QAM1024,
	MXL_EAGLE_QAM_DEMOD_QAM32,
	MXL_EAGLE_QAM_DEMOD_QAM128,
	MXL_EAGLE_QAM_DEMOD_QPSK,
	MXL_EAGLE_QAM_DEMOD_AUTO,
पूर्ण;

/* Enum of Demodulator IQ setup, used in QAM, OOB configuration and status */
क्रमागत MXL_EAGLE_IQ_FLIP_E अणु
	MXL_EAGLE_DEMOD_IQ_NORMAL,
	MXL_EAGLE_DEMOD_IQ_FLIPPED,
	MXL_EAGLE_DEMOD_IQ_AUTO,
पूर्ण;

/* Enum of OOB Demodulator symbol rates, used in OOB configuration */
क्रमागत MXL_EAGLE_OOB_DEMOD_SYMB_RATE_E अणु
	MXL_EAGLE_OOB_DEMOD_SYMB_RATE_0_772MHZ,  /* ANSI/SCTE 55-2 0.772 MHz */
	MXL_EAGLE_OOB_DEMOD_SYMB_RATE_1_024MHZ,  /* ANSI/SCTE 55-1 1.024 MHz */
	MXL_EAGLE_OOB_DEMOD_SYMB_RATE_1_544MHZ,  /* ANSI/SCTE 55-2 1.544 MHz */
पूर्ण;

/* Enum of tuner channel tuning mode */
क्रमागत MXL_EAGLE_TUNER_CHANNEL_TUNE_MODE_E अणु
	MXL_EAGLE_TUNER_CHANNEL_TUNE_MODE_VIEW,    /* Normal "view" mode */
	MXL_EAGLE_TUNER_CHANNEL_TUNE_MODE_SCAN,    /* Fast "scan" mode */
पूर्ण;

/* Enum of tuner bandwidth */
क्रमागत MXL_EAGLE_TUNER_BW_E अणु
	MXL_EAGLE_TUNER_BW_6MHZ,
	MXL_EAGLE_TUNER_BW_7MHZ,
	MXL_EAGLE_TUNER_BW_8MHZ,
पूर्ण;

/* Enum of tuner bandwidth */
क्रमागत MXL_EAGLE_JUNCTION_TEMPERATURE_E अणु
	MXL_EAGLE_JUNCTION_TEMPERATURE_BELOW_0_CELSIUS          = 0,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_0_TO_14_CELSIUS  = 1,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_14_TO_28_CELSIUS = 3,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_28_TO_42_CELSIUS = 2,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_42_TO_57_CELSIUS = 6,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_57_TO_71_CELSIUS = 7,
	MXL_EAGLE_JUNCTION_TEMPERATURE_BETWEEN_71_TO_85_CELSIUS = 5,
	MXL_EAGLE_JUNCTION_TEMPERATURE_ABOVE_85_CELSIUS         = 4,
पूर्ण;

/* Struct passed in optional callback used during FW करोwnload */
काष्ठा MXL_EAGLE_FW_DOWNLOAD_CB_PAYLOAD_T अणु
	u32  total_len;
	u32  करोwnloaded_len;
पूर्ण;

/* Struct used of I2C protocol between host and Eagle, पूर्णांकernal use only */
काष्ठा __packed MXL_EAGLE_HOST_MSG_HEADER_T अणु
	u8   opcode;
	u8   seqnum;
	u8   payload_size;
	u8   status;
	u32  checksum;
पूर्ण;

/* Device version inक्रमmation काष्ठा */
काष्ठा __packed MXL_EAGLE_DEV_VER_T अणु
	u8   chip_id;
	u8   firmware_ver[MXL_EAGLE_VERSION_SIZE];
	u8   mxlware_ver[MXL_EAGLE_VERSION_SIZE];
पूर्ण;

/* Xtal configuration काष्ठा */
काष्ठा __packed MXL_EAGLE_DEV_XTAL_T अणु
	u8   xtal_cap;           /* accepted range is 1..31 pF. Default is 26 */
	u8   clk_out_enable;
	u8   clk_out_भाग_enable;   /* घड़ी out freq is xtal freq / 6 */
	u8   xtal_sharing_enable; /* अगर enabled set xtal_cap to 25 pF */
	u8   xtal_calibration_enable;  /* enable क्रम master, disable क्रम slave */
पूर्ण;

/* GPIO direction काष्ठा, पूर्णांकernally used in GPIO configuration API */
काष्ठा __packed MXL_EAGLE_DEV_GPIO_सूचीECTION_T अणु
	u8   gpio_number;
	u8   gpio_direction;
पूर्ण;

/* GPO level काष्ठा, पूर्णांकernally used in GPIO configuration API */
काष्ठा __packed MXL_EAGLE_DEV_GPO_LEVEL_T अणु
	u8   gpio_number;
	u8   gpo_level;
पूर्ण;

/* Device Status काष्ठा */
काष्ठा MXL_EAGLE_DEV_STATUS_T अणु
	u8   temperature;
	u8   demod_type;
	u8   घातer_mode;
	u8   cpu_utilization_percent;
पूर्ण;

/* Device पूर्णांकerrupt configuration काष्ठा */
काष्ठा __packed MXL_EAGLE_DEV_INTR_CFG_T अणु
	u32  पूर्णांकr_mask;
	u8   edge_trigger;
	u8   positive_trigger;
	u8   global_enable_पूर्णांकerrupt;
पूर्ण;

/* MPEG pad drive parameters, used on MPEG output configuration */
/* See MXL_EAGLE_IO_MUX_DRIVE_MODE_E */
काष्ठा MXL_EAGLE_MPEG_PAD_DRIVE_T अणु
	u8   pad_drv_mpeg_syn;
	u8   pad_drv_mpeg_dat;
	u8   pad_drv_mpeg_val;
	u8   pad_drv_mpeg_clk;
पूर्ण;

/* MPEGOUT parameter काष्ठा, used in MPEG output configuration */
काष्ठा MXL_EAGLE_MPEGOUT_PARAMS_T अणु
	u8   mpeg_parallel;
	u8   msb_first;
	u8   mpeg_sync_pulse_width;    /* See MXL_EAGLE_MPEG_DATA_FORMAT_E */
	u8   mpeg_valid_pol;
	u8   mpeg_sync_pol;
	u8   mpeg_clk_pol;
	u8   mpeg3wire_mode_enable;
	u8   mpeg_clk_freq;
	काष्ठा MXL_EAGLE_MPEG_PAD_DRIVE_T mpeg_pad_drv;
पूर्ण;

/* QAM Demodulator parameters काष्ठा, used in QAM params configuration */
काष्ठा __packed MXL_EAGLE_QAM_DEMOD_PARAMS_T अणु
	u8   annex_type;
	u8   qam_type;
	u8   iq_flip;
	u8   search_range_idx;
	u8   spur_canceller_enable;
	u32  symbol_rate_hz;
	u32  symbol_rate_256qam_hz;
पूर्ण;

/* QAM Demodulator status */
काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T अणु
	u8   annex_type;
	u8   qam_type;
	u8   iq_flip;
	u8   पूर्णांकerleaver_depth_i;
	u8   पूर्णांकerleaver_depth_j;
	u8   qam_locked;
	u8   fec_locked;
	u8   mpeg_locked;
	u16  snr_db_tenths;
	s16  timing_offset;
	s32  carrier_offset_hz;
पूर्ण;

/* QAM Demodulator error counters */
काष्ठा MXL_EAGLE_QAM_DEMOD_ERROR_COUNTERS_T अणु
	u32  corrected_code_words;
	u32  uncorrected_code_words;
	u32  total_code_words_received;
	u32  corrected_bits;
	u32  error_mpeg_frames;
	u32  mpeg_frames_received;
	u32  erasures;
पूर्ण;

/* QAM Demodulator स्थिरellation poपूर्णांक */
काष्ठा MXL_EAGLE_QAM_DEMOD_CONSTELLATION_VAL_T अणु
	s16  i_value[12];
	s16  q_value[12];
पूर्ण;

/* QAM Demodulator equalizer filter taps */
काष्ठा MXL_EAGLE_QAM_DEMOD_EQU_FILTER_T अणु
	s16  ffe_taps[MXL_EAGLE_QAM_FFE_TAPS_LENGTH];
	s16  spur_taps[MXL_EAGLE_QAM_SPUR_TAPS_LENGTH];
	s16  dfe_taps[MXL_EAGLE_QAM_DFE_TAPS_LENGTH];
	u8   ffe_leading_tap_index;
	u8   dfe_taps_number;
पूर्ण;

/* OOB Demodulator parameters काष्ठा, used in OOB params configuration */
काष्ठा __packed MXL_EAGLE_OOB_DEMOD_PARAMS_T अणु
	u8   symbol_rate;
	u8   iq_flip;
	u8   clk_pol;
पूर्ण;

/* OOB Demodulator error counters */
काष्ठा MXL_EAGLE_OOB_DEMOD_ERROR_COUNTERS_T अणु
	u32  corrected_packets;
	u32  uncorrected_packets;
	u32  total_packets_received;
पूर्ण;

/* OOB status */
काष्ठा __packed MXL_EAGLE_OOB_DEMOD_STATUS_T अणु
	u16  snr_db_tenths;
	s16  timing_offset;
	s32  carrier_offsetHz;
	u8   qam_locked;
	u8   fec_locked;
	u8   mpeg_locked;
	u8   retune_required;
	u8   iq_flip;
पूर्ण;

/* ATSC Demodulator status */
काष्ठा __packed MXL_EAGLE_ATSC_DEMOD_STATUS_T अणु
	s16  snr_db_tenths;
	s16  timing_offset;
	s32  carrier_offset_hz;
	u8   frame_lock;
	u8   atsc_lock;
	u8   fec_lock;
पूर्ण;

/* ATSC Demodulator error counters */
काष्ठा MXL_EAGLE_ATSC_DEMOD_ERROR_COUNTERS_T अणु
	u32  error_packets;
	u32  total_packets;
	u32  error_bytes;
पूर्ण;

/* ATSC Demodulator equalizers filter taps */
काष्ठा __packed MXL_EAGLE_ATSC_DEMOD_EQU_FILTER_T अणु
	s16  ffe_taps[MXL_EAGLE_ATSC_FFE_TAPS_LENGTH];
	s8   dfe_taps[MXL_EAGLE_ATSC_DFE_TAPS_LENGTH];
पूर्ण;

/* Tuner AGC Status */
काष्ठा __packed MXL_EAGLE_TUNER_AGC_STATUS_T अणु
	u8   locked;
	u16  raw_agc_gain;    /* AGC gain [dB] = rawAgcGain / 2^6 */
	s16  rx_घातer_db_hundredths;
पूर्ण;

/* Tuner channel tune parameters */
काष्ठा __packed MXL_EAGLE_TUNER_CHANNEL_PARAMS_T अणु
	u32  freq_hz;
	u8   tune_mode;
	u8   bandwidth;
पूर्ण;

/* Tuner channel lock indications */
काष्ठा __packed MXL_EAGLE_TUNER_LOCK_STATUS_T अणु
	u8   rf_pll_locked;
	u8   ref_pll_locked;
पूर्ण;

/* Smart antenna parameters  used in Smart antenna params configuration */
काष्ठा __packed MXL_EAGLE_SMA_PARAMS_T अणु
	u8   full_duplex_enable;
	u8   rx_disable;
	u8   idle_logic_high;
पूर्ण;

/* Smart antenna message क्रमmat */
काष्ठा __packed MXL_EAGLE_SMA_MESSAGE_T अणु
	u32  payload_bits;
	u8   total_num_bits;
पूर्ण;

