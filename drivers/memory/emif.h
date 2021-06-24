<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Defines क्रम the EMIF driver
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Benoit Cousson (b-cousson@ti.com)
 */
#अगर_अघोषित __EMIF_H
#घोषणा __EMIF_H

/*
 * Maximum number of dअगरferent frequencies supported by EMIF driver
 * Determines the number of entries in the poपूर्णांकer array क्रम रेजिस्टर
 * cache
 */
#घोषणा EMIF_MAX_NUM_FREQUENCIES			6

/* State of the core voltage */
#घोषणा DDR_VOLTAGE_STABLE				0
#घोषणा DDR_VOLTAGE_RAMPING				1

/* Defines क्रम timing De-rating */
#घोषणा EMIF_NORMAL_TIMINGS				0
#घोषणा EMIF_DERATED_TIMINGS				1

/* Length of the क्रमced पढ़ो idle period in terms of cycles */
#घोषणा EMIF_READ_IDLE_LEN_VAL				5

/*
 * क्रमced पढ़ो idle पूर्णांकerval to be used when voltage
 * is changed as part of DVFS/DPS - 1ms
 */
#घोषणा READ_IDLE_INTERVAL_DVFS				(1*1000000)

/*
 * Forced पढ़ो idle पूर्णांकerval to be used when voltage is stable
 * 50us - or maximum value will करो
 */
#घोषणा READ_IDLE_INTERVAL_NORMAL			(50*1000000)

/* DLL calibration पूर्णांकerval when voltage is NOT stable - 1us */
#घोषणा DLL_CALIB_INTERVAL_DVFS				(1*1000000)

#घोषणा DLL_CALIB_ACK_WAIT_VAL				5

/* Interval between ZQCS commands - hw team recommended value */
#घोषणा EMIF_ZQCS_INTERVAL_US				(50*1000)
/* Enable ZQ Calibration on निकासing Self-refresh */
#घोषणा ZQ_SFEXITEN_ENABLE				1
/*
 * ZQ Calibration simultaneously on both chip-selects:
 * Needs one calibration resistor per CS
 */
#घोषणा	ZQ_DUALCALEN_DISABLE				0
#घोषणा	ZQ_DUALCALEN_ENABLE				1

#घोषणा T_ZQCS_DEFAULT_NS				90
#घोषणा T_ZQCL_DEFAULT_NS				360
#घोषणा T_ZQINIT_DEFAULT_NS				1000

/* DPD_EN */
#घोषणा DPD_DISABLE					0
#घोषणा DPD_ENABLE					1

/*
 * Default values क्रम the low-घातer entry to be used अगर not provided by user.
 * OMAP4/5 has a hw bug(i735) due to which this value can not be less than 512
 * Timeout values are in DDR घड़ी 'cycles' and frequency threshold in Hz
 */
#घोषणा EMIF_LP_MODE_TIMEOUT_PERFORMANCE		2048
#घोषणा EMIF_LP_MODE_TIMEOUT_POWER			512
#घोषणा EMIF_LP_MODE_FREQ_THRESHOLD			400000000

/* DDR_PHY_CTRL_1 values क्रम EMIF4D - ATTILA PHY combination */
#घोषणा EMIF_DDR_PHY_CTRL_1_BASE_VAL_ATTILAPHY		0x049FF000
#घोषणा EMIF_DLL_SLAVE_DLY_CTRL_400_MHZ_ATTILAPHY	0x41
#घोषणा EMIF_DLL_SLAVE_DLY_CTRL_200_MHZ_ATTILAPHY	0x80
#घोषणा EMIF_DLL_SLAVE_DLY_CTRL_100_MHZ_AND_LESS_ATTILAPHY 0xFF

/* DDR_PHY_CTRL_1 values क्रम EMIF4D5 INTELLIPHY combination */
#घोषणा EMIF_DDR_PHY_CTRL_1_BASE_VAL_INTELLIPHY		0x0E084200
#घोषणा EMIF_PHY_TOTAL_READ_LATENCY_INTELLIPHY_PS	10000

/* TEMP_ALERT_CONFIG - corresponding to temp gradient 5 C/s */
#घोषणा TEMP_ALERT_POLL_INTERVAL_DEFAULT_MS		360

#घोषणा EMIF_T_CSTA					3
#घोषणा EMIF_T_PDLL_UL					128

/* External PHY control रेजिस्टरs magic values */
#घोषणा EMIF_EXT_PHY_CTRL_1_VAL				0x04020080
#घोषणा EMIF_EXT_PHY_CTRL_5_VAL				0x04010040
#घोषणा EMIF_EXT_PHY_CTRL_6_VAL				0x01004010
#घोषणा EMIF_EXT_PHY_CTRL_7_VAL				0x00001004
#घोषणा EMIF_EXT_PHY_CTRL_8_VAL				0x04010040
#घोषणा EMIF_EXT_PHY_CTRL_9_VAL				0x01004010
#घोषणा EMIF_EXT_PHY_CTRL_10_VAL			0x00001004
#घोषणा EMIF_EXT_PHY_CTRL_11_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_12_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_13_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_14_VAL			0x80080080
#घोषणा EMIF_EXT_PHY_CTRL_15_VAL			0x00800800
#घोषणा EMIF_EXT_PHY_CTRL_16_VAL			0x08102040
#घोषणा EMIF_EXT_PHY_CTRL_17_VAL			0x00000001
#घोषणा EMIF_EXT_PHY_CTRL_18_VAL			0x540A8150
#घोषणा EMIF_EXT_PHY_CTRL_19_VAL			0xA81502A0
#घोषणा EMIF_EXT_PHY_CTRL_20_VAL			0x002A0540
#घोषणा EMIF_EXT_PHY_CTRL_21_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_22_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_23_VAL			0x00000000
#घोषणा EMIF_EXT_PHY_CTRL_24_VAL			0x00000077

#घोषणा EMIF_INTELLI_PHY_DQS_GATE_OPENING_DELAY_PS	1200

/* Registers offset */
#घोषणा EMIF_MODULE_ID_AND_REVISION			0x0000
#घोषणा EMIF_STATUS					0x0004
#घोषणा EMIF_SDRAM_CONFIG				0x0008
#घोषणा EMIF_SDRAM_CONFIG_2				0x000c
#घोषणा EMIF_SDRAM_REFRESH_CONTROL			0x0010
#घोषणा EMIF_SDRAM_REFRESH_CTRL_SHDW			0x0014
#घोषणा EMIF_SDRAM_TIMING_1				0x0018
#घोषणा EMIF_SDRAM_TIMING_1_SHDW			0x001c
#घोषणा EMIF_SDRAM_TIMING_2				0x0020
#घोषणा EMIF_SDRAM_TIMING_2_SHDW			0x0024
#घोषणा EMIF_SDRAM_TIMING_3				0x0028
#घोषणा EMIF_SDRAM_TIMING_3_SHDW			0x002c
#घोषणा EMIF_LPDDR2_NVM_TIMING				0x0030
#घोषणा EMIF_LPDDR2_NVM_TIMING_SHDW			0x0034
#घोषणा EMIF_POWER_MANAGEMENT_CONTROL			0x0038
#घोषणा EMIF_POWER_MANAGEMENT_CTRL_SHDW			0x003c
#घोषणा EMIF_LPDDR2_MODE_REG_DATA			0x0040
#घोषणा EMIF_LPDDR2_MODE_REG_CONFIG			0x0050
#घोषणा EMIF_OCP_CONFIG					0x0054
#घोषणा EMIF_OCP_CONFIG_VALUE_1				0x0058
#घोषणा EMIF_OCP_CONFIG_VALUE_2				0x005c
#घोषणा EMIF_IODFT_TEST_LOGIC_GLOBAL_CONTROL		0x0060
#घोषणा EMIF_IODFT_TEST_LOGIC_CTRL_MISR_RESULT		0x0064
#घोषणा EMIF_IODFT_TEST_LOGIC_ADDRESS_MISR_RESULT	0x0068
#घोषणा EMIF_IODFT_TEST_LOGIC_DATA_MISR_RESULT_1	0x006c
#घोषणा EMIF_IODFT_TEST_LOGIC_DATA_MISR_RESULT_2	0x0070
#घोषणा EMIF_IODFT_TEST_LOGIC_DATA_MISR_RESULT_3	0x0074
#घोषणा EMIF_PERFORMANCE_COUNTER_1			0x0080
#घोषणा EMIF_PERFORMANCE_COUNTER_2			0x0084
#घोषणा EMIF_PERFORMANCE_COUNTER_CONFIG			0x0088
#घोषणा EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT	0x008c
#घोषणा EMIF_PERFORMANCE_COUNTER_TIME			0x0090
#घोषणा EMIF_MISC_REG					0x0094
#घोषणा EMIF_DLL_CALIB_CTRL				0x0098
#घोषणा EMIF_DLL_CALIB_CTRL_SHDW			0x009c
#घोषणा EMIF_END_OF_INTERRUPT				0x00a0
#घोषणा EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS		0x00a4
#घोषणा EMIF_LL_OCP_INTERRUPT_RAW_STATUS		0x00a8
#घोषणा EMIF_SYSTEM_OCP_INTERRUPT_STATUS		0x00ac
#घोषणा EMIF_LL_OCP_INTERRUPT_STATUS			0x00b0
#घोषणा EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET		0x00b4
#घोषणा EMIF_LL_OCP_INTERRUPT_ENABLE_SET		0x00b8
#घोषणा EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR		0x00bc
#घोषणा EMIF_LL_OCP_INTERRUPT_ENABLE_CLEAR		0x00c0
#घोषणा EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x00c8
#घोषणा EMIF_TEMPERATURE_ALERT_CONFIG			0x00cc
#घोषणा EMIF_OCP_ERROR_LOG				0x00d0
#घोषणा EMIF_READ_WRITE_LEVELING_RAMP_WINDOW		0x00d4
#घोषणा EMIF_READ_WRITE_LEVELING_RAMP_CONTROL		0x00d8
#घोषणा EMIF_READ_WRITE_LEVELING_CONTROL		0x00dc
#घोषणा EMIF_DDR_PHY_CTRL_1				0x00e4
#घोषणा EMIF_DDR_PHY_CTRL_1_SHDW			0x00e8
#घोषणा EMIF_DDR_PHY_CTRL_2				0x00ec
#घोषणा EMIF_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING	0x0100
#घोषणा EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_1_MAPPING 0x0104
#घोषणा EMIF_CONNECTION_ID_TO_CLASS_OF_SERVICE_2_MAPPING 0x0108
#घोषणा EMIF_READ_WRITE_EXECUTION_THRESHOLD		0x0120
#घोषणा EMIF_COS_CONFIG					0x0124
#घोषणा EMIF_PHY_STATUS_1				0x0140
#घोषणा EMIF_PHY_STATUS_2				0x0144
#घोषणा EMIF_PHY_STATUS_3				0x0148
#घोषणा EMIF_PHY_STATUS_4				0x014c
#घोषणा EMIF_PHY_STATUS_5				0x0150
#घोषणा EMIF_PHY_STATUS_6				0x0154
#घोषणा EMIF_PHY_STATUS_7				0x0158
#घोषणा EMIF_PHY_STATUS_8				0x015c
#घोषणा EMIF_PHY_STATUS_9				0x0160
#घोषणा EMIF_PHY_STATUS_10				0x0164
#घोषणा EMIF_PHY_STATUS_11				0x0168
#घोषणा EMIF_PHY_STATUS_12				0x016c
#घोषणा EMIF_PHY_STATUS_13				0x0170
#घोषणा EMIF_PHY_STATUS_14				0x0174
#घोषणा EMIF_PHY_STATUS_15				0x0178
#घोषणा EMIF_PHY_STATUS_16				0x017c
#घोषणा EMIF_PHY_STATUS_17				0x0180
#घोषणा EMIF_PHY_STATUS_18				0x0184
#घोषणा EMIF_PHY_STATUS_19				0x0188
#घोषणा EMIF_PHY_STATUS_20				0x018c
#घोषणा EMIF_PHY_STATUS_21				0x0190
#घोषणा EMIF_EXT_PHY_CTRL_1				0x0200
#घोषणा EMIF_EXT_PHY_CTRL_1_SHDW			0x0204
#घोषणा EMIF_EXT_PHY_CTRL_2				0x0208
#घोषणा EMIF_EXT_PHY_CTRL_2_SHDW			0x020c
#घोषणा EMIF_EXT_PHY_CTRL_3				0x0210
#घोषणा EMIF_EXT_PHY_CTRL_3_SHDW			0x0214
#घोषणा EMIF_EXT_PHY_CTRL_4				0x0218
#घोषणा EMIF_EXT_PHY_CTRL_4_SHDW			0x021c
#घोषणा EMIF_EXT_PHY_CTRL_5				0x0220
#घोषणा EMIF_EXT_PHY_CTRL_5_SHDW			0x0224
#घोषणा EMIF_EXT_PHY_CTRL_6				0x0228
#घोषणा EMIF_EXT_PHY_CTRL_6_SHDW			0x022c
#घोषणा EMIF_EXT_PHY_CTRL_7				0x0230
#घोषणा EMIF_EXT_PHY_CTRL_7_SHDW			0x0234
#घोषणा EMIF_EXT_PHY_CTRL_8				0x0238
#घोषणा EMIF_EXT_PHY_CTRL_8_SHDW			0x023c
#घोषणा EMIF_EXT_PHY_CTRL_9				0x0240
#घोषणा EMIF_EXT_PHY_CTRL_9_SHDW			0x0244
#घोषणा EMIF_EXT_PHY_CTRL_10				0x0248
#घोषणा EMIF_EXT_PHY_CTRL_10_SHDW			0x024c
#घोषणा EMIF_EXT_PHY_CTRL_11				0x0250
#घोषणा EMIF_EXT_PHY_CTRL_11_SHDW			0x0254
#घोषणा EMIF_EXT_PHY_CTRL_12				0x0258
#घोषणा EMIF_EXT_PHY_CTRL_12_SHDW			0x025c
#घोषणा EMIF_EXT_PHY_CTRL_13				0x0260
#घोषणा EMIF_EXT_PHY_CTRL_13_SHDW			0x0264
#घोषणा EMIF_EXT_PHY_CTRL_14				0x0268
#घोषणा EMIF_EXT_PHY_CTRL_14_SHDW			0x026c
#घोषणा EMIF_EXT_PHY_CTRL_15				0x0270
#घोषणा EMIF_EXT_PHY_CTRL_15_SHDW			0x0274
#घोषणा EMIF_EXT_PHY_CTRL_16				0x0278
#घोषणा EMIF_EXT_PHY_CTRL_16_SHDW			0x027c
#घोषणा EMIF_EXT_PHY_CTRL_17				0x0280
#घोषणा EMIF_EXT_PHY_CTRL_17_SHDW			0x0284
#घोषणा EMIF_EXT_PHY_CTRL_18				0x0288
#घोषणा EMIF_EXT_PHY_CTRL_18_SHDW			0x028c
#घोषणा EMIF_EXT_PHY_CTRL_19				0x0290
#घोषणा EMIF_EXT_PHY_CTRL_19_SHDW			0x0294
#घोषणा EMIF_EXT_PHY_CTRL_20				0x0298
#घोषणा EMIF_EXT_PHY_CTRL_20_SHDW			0x029c
#घोषणा EMIF_EXT_PHY_CTRL_21				0x02a0
#घोषणा EMIF_EXT_PHY_CTRL_21_SHDW			0x02a4
#घोषणा EMIF_EXT_PHY_CTRL_22				0x02a8
#घोषणा EMIF_EXT_PHY_CTRL_22_SHDW			0x02ac
#घोषणा EMIF_EXT_PHY_CTRL_23				0x02b0
#घोषणा EMIF_EXT_PHY_CTRL_23_SHDW			0x02b4
#घोषणा EMIF_EXT_PHY_CTRL_24				0x02b8
#घोषणा EMIF_EXT_PHY_CTRL_24_SHDW			0x02bc
#घोषणा EMIF_EXT_PHY_CTRL_25				0x02c0
#घोषणा EMIF_EXT_PHY_CTRL_25_SHDW			0x02c4
#घोषणा EMIF_EXT_PHY_CTRL_26				0x02c8
#घोषणा EMIF_EXT_PHY_CTRL_26_SHDW			0x02cc
#घोषणा EMIF_EXT_PHY_CTRL_27				0x02d0
#घोषणा EMIF_EXT_PHY_CTRL_27_SHDW			0x02d4
#घोषणा EMIF_EXT_PHY_CTRL_28				0x02d8
#घोषणा EMIF_EXT_PHY_CTRL_28_SHDW			0x02dc
#घोषणा EMIF_EXT_PHY_CTRL_29				0x02e0
#घोषणा EMIF_EXT_PHY_CTRL_29_SHDW			0x02e4
#घोषणा EMIF_EXT_PHY_CTRL_30				0x02e8
#घोषणा EMIF_EXT_PHY_CTRL_30_SHDW			0x02ec

/* Registers shअगरts and masks */

/* EMIF_MODULE_ID_AND_REVISION */
#घोषणा SCHEME_SHIFT					30
#घोषणा SCHEME_MASK					(0x3 << 30)
#घोषणा MODULE_ID_SHIFT					16
#घोषणा MODULE_ID_MASK					(0xfff << 16)
#घोषणा RTL_VERSION_SHIFT				11
#घोषणा RTL_VERSION_MASK				(0x1f << 11)
#घोषणा MAJOR_REVISION_SHIFT				8
#घोषणा MAJOR_REVISION_MASK				(0x7 << 8)
#घोषणा MINOR_REVISION_SHIFT				0
#घोषणा MINOR_REVISION_MASK				(0x3f << 0)

/* STATUS */
#घोषणा BE_SHIFT					31
#घोषणा BE_MASK						(1 << 31)
#घोषणा DUAL_CLK_MODE_SHIFT				30
#घोषणा DUAL_CLK_MODE_MASK				(1 << 30)
#घोषणा FAST_INIT_SHIFT					29
#घोषणा FAST_INIT_MASK					(1 << 29)
#घोषणा RDLVLGATETO_SHIFT				6
#घोषणा RDLVLGATETO_MASK				(1 << 6)
#घोषणा RDLVLTO_SHIFT					5
#घोषणा RDLVLTO_MASK					(1 << 5)
#घोषणा WRLVLTO_SHIFT					4
#घोषणा WRLVLTO_MASK					(1 << 4)
#घोषणा PHY_DLL_READY_SHIFT				2
#घोषणा PHY_DLL_READY_MASK				(1 << 2)

/* SDRAM_CONFIG */
#घोषणा SDRAM_TYPE_SHIFT				29
#घोषणा SDRAM_TYPE_MASK					(0x7 << 29)
#घोषणा IBANK_POS_SHIFT					27
#घोषणा IBANK_POS_MASK					(0x3 << 27)
#घोषणा DDR_TERM_SHIFT					24
#घोषणा DDR_TERM_MASK					(0x7 << 24)
#घोषणा DDR2_DDQS_SHIFT					23
#घोषणा DDR2_DDQS_MASK					(1 << 23)
#घोषणा DYN_ODT_SHIFT					21
#घोषणा DYN_ODT_MASK					(0x3 << 21)
#घोषणा DDR_DISABLE_DLL_SHIFT				20
#घोषणा DDR_DISABLE_DLL_MASK				(1 << 20)
#घोषणा SDRAM_DRIVE_SHIFT				18
#घोषणा SDRAM_DRIVE_MASK				(0x3 << 18)
#घोषणा CWL_SHIFT					16
#घोषणा CWL_MASK					(0x3 << 16)
#घोषणा NARROW_MODE_SHIFT				14
#घोषणा NARROW_MODE_MASK				(0x3 << 14)
#घोषणा CL_SHIFT					10
#घोषणा CL_MASK						(0xf << 10)
#घोषणा ROWSIZE_SHIFT					7
#घोषणा ROWSIZE_MASK					(0x7 << 7)
#घोषणा IBANK_SHIFT					4
#घोषणा IBANK_MASK					(0x7 << 4)
#घोषणा EBANK_SHIFT					3
#घोषणा EBANK_MASK					(1 << 3)
#घोषणा PAGESIZE_SHIFT					0
#घोषणा PAGESIZE_MASK					(0x7 << 0)

/* SDRAM_CONFIG_2 */
#घोषणा CS1NVMEN_SHIFT					30
#घोषणा CS1NVMEN_MASK					(1 << 30)
#घोषणा EBANK_POS_SHIFT					27
#घोषणा EBANK_POS_MASK					(1 << 27)
#घोषणा RDBNUM_SHIFT					4
#घोषणा RDBNUM_MASK					(0x3 << 4)
#घोषणा RDBSIZE_SHIFT					0
#घोषणा RDBSIZE_MASK					(0x7 << 0)

/* SDRAM_REFRESH_CONTROL */
#घोषणा INITREF_DIS_SHIFT				31
#घोषणा INITREF_DIS_MASK				(1 << 31)
#घोषणा SRT_SHIFT					29
#घोषणा SRT_MASK					(1 << 29)
#घोषणा ASR_SHIFT					28
#घोषणा ASR_MASK					(1 << 28)
#घोषणा PASR_SHIFT					24
#घोषणा PASR_MASK					(0x7 << 24)
#घोषणा REFRESH_RATE_SHIFT				0
#घोषणा REFRESH_RATE_MASK				(0xffff << 0)

/* SDRAM_TIMING_1 */
#घोषणा T_RTW_SHIFT					29
#घोषणा T_RTW_MASK					(0x7 << 29)
#घोषणा T_RP_SHIFT					25
#घोषणा T_RP_MASK					(0xf << 25)
#घोषणा T_RCD_SHIFT					21
#घोषणा T_RCD_MASK					(0xf << 21)
#घोषणा T_WR_SHIFT					17
#घोषणा T_WR_MASK					(0xf << 17)
#घोषणा T_RAS_SHIFT					12
#घोषणा T_RAS_MASK					(0x1f << 12)
#घोषणा T_RC_SHIFT					6
#घोषणा T_RC_MASK					(0x3f << 6)
#घोषणा T_RRD_SHIFT					3
#घोषणा T_RRD_MASK					(0x7 << 3)
#घोषणा T_WTR_SHIFT					0
#घोषणा T_WTR_MASK					(0x7 << 0)

/* SDRAM_TIMING_2 */
#घोषणा T_XP_SHIFT					28
#घोषणा T_XP_MASK					(0x7 << 28)
#घोषणा T_ODT_SHIFT					25
#घोषणा T_ODT_MASK					(0x7 << 25)
#घोषणा T_XSNR_SHIFT					16
#घोषणा T_XSNR_MASK					(0x1ff << 16)
#घोषणा T_XSRD_SHIFT					6
#घोषणा T_XSRD_MASK					(0x3ff << 6)
#घोषणा T_RTP_SHIFT					3
#घोषणा T_RTP_MASK					(0x7 << 3)
#घोषणा T_CKE_SHIFT					0
#घोषणा T_CKE_MASK					(0x7 << 0)

/* SDRAM_TIMING_3 */
#घोषणा T_PDLL_UL_SHIFT					28
#घोषणा T_PDLL_UL_MASK					(0xf << 28)
#घोषणा T_CSTA_SHIFT					24
#घोषणा T_CSTA_MASK					(0xf << 24)
#घोषणा T_CKESR_SHIFT					21
#घोषणा T_CKESR_MASK					(0x7 << 21)
#घोषणा ZQ_ZQCS_SHIFT					15
#घोषणा ZQ_ZQCS_MASK					(0x3f << 15)
#घोषणा T_TDQSCKMAX_SHIFT				13
#घोषणा T_TDQSCKMAX_MASK				(0x3 << 13)
#घोषणा T_RFC_SHIFT					4
#घोषणा T_RFC_MASK					(0x1ff << 4)
#घोषणा T_RAS_MAX_SHIFT					0
#घोषणा T_RAS_MAX_MASK					(0xf << 0)

/* POWER_MANAGEMENT_CONTROL */
#घोषणा PD_TIM_SHIFT					12
#घोषणा PD_TIM_MASK					(0xf << 12)
#घोषणा DPD_EN_SHIFT					11
#घोषणा DPD_EN_MASK					(1 << 11)
#घोषणा LP_MODE_SHIFT					8
#घोषणा LP_MODE_MASK					(0x7 << 8)
#घोषणा SR_TIM_SHIFT					4
#घोषणा SR_TIM_MASK					(0xf << 4)
#घोषणा CS_TIM_SHIFT					0
#घोषणा CS_TIM_MASK					(0xf << 0)

/* LPDDR2_MODE_REG_DATA */
#घोषणा VALUE_0_SHIFT					0
#घोषणा VALUE_0_MASK					(0x7f << 0)

/* LPDDR2_MODE_REG_CONFIG */
#घोषणा CS_SHIFT					31
#घोषणा CS_MASK						(1 << 31)
#घोषणा REFRESH_EN_SHIFT				30
#घोषणा REFRESH_EN_MASK					(1 << 30)
#घोषणा ADDRESS_SHIFT					0
#घोषणा ADDRESS_MASK					(0xff << 0)

/* OCP_CONFIG */
#घोषणा SYS_THRESH_MAX_SHIFT				24
#घोषणा SYS_THRESH_MAX_MASK				(0xf << 24)
#घोषणा MPU_THRESH_MAX_SHIFT				20
#घोषणा MPU_THRESH_MAX_MASK				(0xf << 20)
#घोषणा LL_THRESH_MAX_SHIFT				16
#घोषणा LL_THRESH_MAX_MASK				(0xf << 16)

/* PERFORMANCE_COUNTER_1 */
#घोषणा COUNTER1_SHIFT					0
#घोषणा COUNTER1_MASK					(0xffffffff << 0)

/* PERFORMANCE_COUNTER_2 */
#घोषणा COUNTER2_SHIFT					0
#घोषणा COUNTER2_MASK					(0xffffffff << 0)

/* PERFORMANCE_COUNTER_CONFIG */
#घोषणा CNTR2_MCONNID_EN_SHIFT				31
#घोषणा CNTR2_MCONNID_EN_MASK				(1 << 31)
#घोषणा CNTR2_REGION_EN_SHIFT				30
#घोषणा CNTR2_REGION_EN_MASK				(1 << 30)
#घोषणा CNTR2_CFG_SHIFT					16
#घोषणा CNTR2_CFG_MASK					(0xf << 16)
#घोषणा CNTR1_MCONNID_EN_SHIFT				15
#घोषणा CNTR1_MCONNID_EN_MASK				(1 << 15)
#घोषणा CNTR1_REGION_EN_SHIFT				14
#घोषणा CNTR1_REGION_EN_MASK				(1 << 14)
#घोषणा CNTR1_CFG_SHIFT					0
#घोषणा CNTR1_CFG_MASK					(0xf << 0)

/* PERFORMANCE_COUNTER_MASTER_REGION_SELECT */
#घोषणा MCONNID2_SHIFT					24
#घोषणा MCONNID2_MASK					(0xff << 24)
#घोषणा REGION_SEL2_SHIFT				16
#घोषणा REGION_SEL2_MASK				(0x3 << 16)
#घोषणा MCONNID1_SHIFT					8
#घोषणा MCONNID1_MASK					(0xff << 8)
#घोषणा REGION_SEL1_SHIFT				0
#घोषणा REGION_SEL1_MASK				(0x3 << 0)

/* PERFORMANCE_COUNTER_TIME */
#घोषणा TOTAL_TIME_SHIFT				0
#घोषणा TOTAL_TIME_MASK					(0xffffffff << 0)

/* DLL_CALIB_CTRL */
#घोषणा ACK_WAIT_SHIFT					16
#घोषणा ACK_WAIT_MASK					(0xf << 16)
#घोषणा DLL_CALIB_INTERVAL_SHIFT			0
#घोषणा DLL_CALIB_INTERVAL_MASK				(0x1ff << 0)

/* END_OF_INTERRUPT */
#घोषणा EOI_SHIFT					0
#घोषणा EOI_MASK					(1 << 0)

/* SYSTEM_OCP_INTERRUPT_RAW_STATUS */
#घोषणा DNV_SYS_SHIFT					2
#घोषणा DNV_SYS_MASK					(1 << 2)
#घोषणा TA_SYS_SHIFT					1
#घोषणा TA_SYS_MASK					(1 << 1)
#घोषणा ERR_SYS_SHIFT					0
#घोषणा ERR_SYS_MASK					(1 << 0)

/* LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS */
#घोषणा DNV_LL_SHIFT					2
#घोषणा DNV_LL_MASK					(1 << 2)
#घोषणा TA_LL_SHIFT					1
#घोषणा TA_LL_MASK					(1 << 1)
#घोषणा ERR_LL_SHIFT					0
#घोषणा ERR_LL_MASK					(1 << 0)

/* SYSTEM_OCP_INTERRUPT_ENABLE_SET */
#घोषणा EN_DNV_SYS_SHIFT				2
#घोषणा EN_DNV_SYS_MASK					(1 << 2)
#घोषणा EN_TA_SYS_SHIFT					1
#घोषणा EN_TA_SYS_MASK					(1 << 1)
#घोषणा EN_ERR_SYS_SHIFT					0
#घोषणा EN_ERR_SYS_MASK					(1 << 0)

/* LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET */
#घोषणा EN_DNV_LL_SHIFT					2
#घोषणा EN_DNV_LL_MASK					(1 << 2)
#घोषणा EN_TA_LL_SHIFT					1
#घोषणा EN_TA_LL_MASK					(1 << 1)
#घोषणा EN_ERR_LL_SHIFT					0
#घोषणा EN_ERR_LL_MASK					(1 << 0)

/* SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG */
#घोषणा ZQ_CS1EN_SHIFT					31
#घोषणा ZQ_CS1EN_MASK					(1 << 31)
#घोषणा ZQ_CS0EN_SHIFT					30
#घोषणा ZQ_CS0EN_MASK					(1 << 30)
#घोषणा ZQ_DUALCALEN_SHIFT				29
#घोषणा ZQ_DUALCALEN_MASK				(1 << 29)
#घोषणा ZQ_SFEXITEN_SHIFT				28
#घोषणा ZQ_SFEXITEN_MASK				(1 << 28)
#घोषणा ZQ_ZQINIT_MULT_SHIFT				18
#घोषणा ZQ_ZQINIT_MULT_MASK				(0x3 << 18)
#घोषणा ZQ_ZQCL_MULT_SHIFT				16
#घोषणा ZQ_ZQCL_MULT_MASK				(0x3 << 16)
#घोषणा ZQ_REFINTERVAL_SHIFT				0
#घोषणा ZQ_REFINTERVAL_MASK				(0xffff << 0)

/* TEMPERATURE_ALERT_CONFIG */
#घोषणा TA_CS1EN_SHIFT					31
#घोषणा TA_CS1EN_MASK					(1 << 31)
#घोषणा TA_CS0EN_SHIFT					30
#घोषणा TA_CS0EN_MASK					(1 << 30)
#घोषणा TA_SFEXITEN_SHIFT				28
#घोषणा TA_SFEXITEN_MASK				(1 << 28)
#घोषणा TA_DEVWDT_SHIFT					26
#घोषणा TA_DEVWDT_MASK					(0x3 << 26)
#घोषणा TA_DEVCNT_SHIFT					24
#घोषणा TA_DEVCNT_MASK					(0x3 << 24)
#घोषणा TA_REFINTERVAL_SHIFT				0
#घोषणा TA_REFINTERVAL_MASK				(0x3fffff << 0)

/* OCP_ERROR_LOG */
#घोषणा MADDRSPACE_SHIFT				14
#घोषणा MADDRSPACE_MASK					(0x3 << 14)
#घोषणा MBURSTSEQ_SHIFT					11
#घोषणा MBURSTSEQ_MASK					(0x7 << 11)
#घोषणा MCMD_SHIFT					8
#घोषणा MCMD_MASK					(0x7 << 8)
#घोषणा MCONNID_SHIFT					0
#घोषणा MCONNID_MASK					(0xff << 0)

/* READ_WRITE_LEVELING_CONTROL */
#घोषणा RDWRLVLFULL_START				0x80000000

/* DDR_PHY_CTRL_1 - EMIF4D */
#घोषणा DLL_SLAVE_DLY_CTRL_SHIFT_4D			4
#घोषणा DLL_SLAVE_DLY_CTRL_MASK_4D			(0xFF << 4)
#घोषणा READ_LATENCY_SHIFT_4D				0
#घोषणा READ_LATENCY_MASK_4D				(0xf << 0)

/* DDR_PHY_CTRL_1 - EMIF4D5 */
#घोषणा DLL_HALF_DELAY_SHIFT_4D5			21
#घोषणा DLL_HALF_DELAY_MASK_4D5				(1 << 21)
#घोषणा READ_LATENCY_SHIFT_4D5				0
#घोषणा READ_LATENCY_MASK_4D5				(0x1f << 0)

/* DDR_PHY_CTRL_1_SHDW */
#घोषणा DDR_PHY_CTRL_1_SHDW_SHIFT			5
#घोषणा DDR_PHY_CTRL_1_SHDW_MASK			(0x7ffffff << 5)
#घोषणा READ_LATENCY_SHDW_SHIFT				0
#घोषणा READ_LATENCY_SHDW_MASK				(0x1f << 0)

#घोषणा EMIF_SRAM_AM33_REG_LAYOUT			0x00000000
#घोषणा EMIF_SRAM_AM43_REG_LAYOUT			0x00000001

#अगर_अघोषित __ASSEMBLY__
/*
 * Structure containing shaकरोw of important रेजिस्टरs in EMIF
 * The calculation function fills in this काष्ठाure to be later used क्रम
 * initialisation and DVFS
 */
काष्ठा emअगर_regs अणु
	u32 freq;
	u32 ref_ctrl_shdw;
	u32 ref_ctrl_shdw_derated;
	u32 sdram_tim1_shdw;
	u32 sdram_tim1_shdw_derated;
	u32 sdram_tim2_shdw;
	u32 sdram_tim3_shdw;
	u32 sdram_tim3_shdw_derated;
	u32 pwr_mgmt_ctrl_shdw;
	जोड़ अणु
		u32 पढ़ो_idle_ctrl_shdw_normal;
		u32 dll_calib_ctrl_shdw_normal;
	पूर्ण;
	जोड़ अणु
		u32 पढ़ो_idle_ctrl_shdw_volt_ramp;
		u32 dll_calib_ctrl_shdw_volt_ramp;
	पूर्ण;

	u32 phy_ctrl_1_shdw;
	u32 ext_phy_ctrl_2_shdw;
	u32 ext_phy_ctrl_3_shdw;
	u32 ext_phy_ctrl_4_shdw;
पूर्ण;

काष्ठा ti_emअगर_pm_functions;

बाह्य अचिन्हित पूर्णांक ti_emअगर_sram;
बाह्य अचिन्हित पूर्णांक ti_emअगर_sram_sz;
बाह्य काष्ठा ti_emअगर_pm_data ti_emअगर_pm_sram_data;
बाह्य काष्ठा emअगर_regs_amx3 ti_emअगर_regs_amx3;

व्योम ti_emअगर_save_context(व्योम);
व्योम ti_emअगर_restore_context(व्योम);
व्योम ti_emअगर_run_hw_leveling(व्योम);
व्योम ti_emअगर_enter_sr(व्योम);
व्योम ti_emअगर_निकास_sr(व्योम);
व्योम ti_emअगर_पात_sr(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __EMIF_H */
