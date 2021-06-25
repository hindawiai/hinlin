<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#अगर_अघोषित __RTL8821AE_DEF_H__
#घोषणा __RTL8821AE_DEF_H__

/*--------------------------Define -------------------------------------------*/
#घोषणा	USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN	1

/* BIT 7 HT Rate*/
/*TxHT = 0*/
#घोषणा	MGN_1M				0x02
#घोषणा	MGN_2M				0x04
#घोषणा	MGN_5_5M			0x0b
#घोषणा	MGN_11M				0x16

#घोषणा	MGN_6M				0x0c
#घोषणा	MGN_9M				0x12
#घोषणा	MGN_12M				0x18
#घोषणा	MGN_18M				0x24
#घोषणा	MGN_24M				0x30
#घोषणा	MGN_36M				0x48
#घोषणा	MGN_48M				0x60
#घोषणा	MGN_54M				0x6c

/* TxHT = 1 */
#घोषणा	MGN_MCS0			0x80
#घोषणा	MGN_MCS1			0x81
#घोषणा	MGN_MCS2			0x82
#घोषणा	MGN_MCS3			0x83
#घोषणा	MGN_MCS4			0x84
#घोषणा	MGN_MCS5			0x85
#घोषणा	MGN_MCS6			0x86
#घोषणा	MGN_MCS7			0x87
#घोषणा	MGN_MCS8			0x88
#घोषणा	MGN_MCS9			0x89
#घोषणा	MGN_MCS10			0x8a
#घोषणा	MGN_MCS11			0x8b
#घोषणा	MGN_MCS12			0x8c
#घोषणा	MGN_MCS13			0x8d
#घोषणा	MGN_MCS14			0x8e
#घोषणा	MGN_MCS15			0x8f
/* VHT rate */
#घोषणा	MGN_VHT1SS_MCS0		0x90
#घोषणा	MGN_VHT1SS_MCS1		0x91
#घोषणा	MGN_VHT1SS_MCS2		0x92
#घोषणा	MGN_VHT1SS_MCS3		0x93
#घोषणा	MGN_VHT1SS_MCS4		0x94
#घोषणा	MGN_VHT1SS_MCS5		0x95
#घोषणा	MGN_VHT1SS_MCS6		0x96
#घोषणा	MGN_VHT1SS_MCS7		0x97
#घोषणा	MGN_VHT1SS_MCS8		0x98
#घोषणा	MGN_VHT1SS_MCS9		0x99
#घोषणा	MGN_VHT2SS_MCS0		0x9a
#घोषणा	MGN_VHT2SS_MCS1		0x9b
#घोषणा	MGN_VHT2SS_MCS2		0x9c
#घोषणा	MGN_VHT2SS_MCS3		0x9d
#घोषणा	MGN_VHT2SS_MCS4		0x9e
#घोषणा	MGN_VHT2SS_MCS5		0x9f
#घोषणा	MGN_VHT2SS_MCS6		0xa0
#घोषणा	MGN_VHT2SS_MCS7		0xa1
#घोषणा	MGN_VHT2SS_MCS8		0xa2
#घोषणा	MGN_VHT2SS_MCS9		0xa3

#घोषणा	MGN_VHT3SS_MCS0		0xa4
#घोषणा	MGN_VHT3SS_MCS1		0xa5
#घोषणा	MGN_VHT3SS_MCS2		0xa6
#घोषणा	MGN_VHT3SS_MCS3		0xa7
#घोषणा	MGN_VHT3SS_MCS4		0xa8
#घोषणा	MGN_VHT3SS_MCS5		0xa9
#घोषणा	MGN_VHT3SS_MCS6		0xaa
#घोषणा	MGN_VHT3SS_MCS7		0xab
#घोषणा	MGN_VHT3SS_MCS8		0xac
#घोषणा	MGN_VHT3SS_MCS9		0xad

#घोषणा	MGN_MCS0_SG			0xc0
#घोषणा	MGN_MCS1_SG			0xc1
#घोषणा	MGN_MCS2_SG			0xc2
#घोषणा	MGN_MCS3_SG			0xc3
#घोषणा	MGN_MCS4_SG			0xc4
#घोषणा	MGN_MCS5_SG			0xc5
#घोषणा	MGN_MCS6_SG			0xc6
#घोषणा	MGN_MCS7_SG			0xc7
#घोषणा	MGN_MCS8_SG			0xc8
#घोषणा	MGN_MCS9_SG			0xc9
#घोषणा	MGN_MCS10_SG		0xca
#घोषणा	MGN_MCS11_SG		0xcb
#घोषणा	MGN_MCS12_SG		0xcc
#घोषणा	MGN_MCS13_SG		0xcd
#घोषणा	MGN_MCS14_SG		0xce
#घोषणा	MGN_MCS15_SG		0xcf

#घोषणा	MGN_UNKNOWN			0xff

/* 30 ms */
#घोषणा	WIFI_NAV_UPPER_US				30000
#घोषणा HAL_92C_NAV_UPPER_UNIT			128

#घोषणा MAX_RX_DMA_BUFFER_SIZE				0x3E80

#घोषणा HAL_PRIME_CHNL_OFFSET_DONT_CARE		0
#घोषणा HAL_PRIME_CHNL_OFFSET_LOWER			1
#घोषणा HAL_PRIME_CHNL_OFFSET_UPPER			2

#घोषणा RX_MPDU_QUEUE						0
#घोषणा RX_CMD_QUEUE						1

#घोषणा MAX_RX_DMA_BUFFER_SIZE_8812	0x3E80

#घोषणा CHIP_BONDING_IDENTIFIER(_value)	(((_value)>>22)&0x3)

#घोषणा CHIP_8812				BIT(2)
#घोषणा CHIP_8821				(BIT(0)|BIT(2))

#घोषणा CHIP_8821A				(BIT(0)|BIT(2))
#घोषणा NORMAL_CHIP				BIT(3)
#घोषणा RF_TYPE_1T1R				(~(BIT(4)|BIT(5)|BIT(6)))
#घोषणा RF_TYPE_1T2R				BIT(4)
#घोषणा RF_TYPE_2T2R				BIT(5)
#घोषणा CHIP_VENDOR_UMC				BIT(7)
#घोषणा B_CUT_VERSION				BIT(12)
#घोषणा C_CUT_VERSION				BIT(13)
#घोषणा D_CUT_VERSION				((BIT(12)|BIT(13)))
#घोषणा E_CUT_VERSION				BIT(14)
#घोषणा	RF_RL_ID			(BIT(31)|BIT(30)|BIT(29)|BIT(28))

क्रमागत version_8821ae अणु
	VERSION_TEST_CHIP_1T1R_8812 = 0x0004,
	VERSION_TEST_CHIP_2T2R_8812 = 0x0024,
	VERSION_NORMAL_TSMC_CHIP_1T1R_8812 = 0x100c,
	VERSION_NORMAL_TSMC_CHIP_2T2R_8812 = 0x102c,
	VERSION_NORMAL_TSMC_CHIP_1T1R_8812_C_CUT = 0x200c,
	VERSION_NORMAL_TSMC_CHIP_2T2R_8812_C_CUT = 0x202c,
	VERSION_TEST_CHIP_8821 = 0x0005,
	VERSION_NORMAL_TSMC_CHIP_8821 = 0x000d,
	VERSION_NORMAL_TSMC_CHIP_8821_B_CUT = 0x100d,
	VERSION_UNKNOWN = 0xFF,
पूर्ण;

क्रमागत vht_data_sc अणु
	VHT_DATA_SC_DONOT_CARE = 0,
	VHT_DATA_SC_20_UPPER_OF_80MHZ = 1,
	VHT_DATA_SC_20_LOWER_OF_80MHZ = 2,
	VHT_DATA_SC_20_UPPERST_OF_80MHZ = 3,
	VHT_DATA_SC_20_LOWEST_OF_80MHZ = 4,
	VHT_DATA_SC_20_RECV1 = 5,
	VHT_DATA_SC_20_RECV2 = 6,
	VHT_DATA_SC_20_RECV3 = 7,
	VHT_DATA_SC_20_RECV4 = 8,
	VHT_DATA_SC_40_UPPER_OF_80MHZ = 9,
	VHT_DATA_SC_40_LOWER_OF_80MHZ = 10,
पूर्ण;

/* MASK */
#घोषणा IC_TYPE_MASK			(BIT(0)|BIT(1)|BIT(2))
#घोषणा CHIP_TYPE_MASK			BIT(3)
#घोषणा RF_TYPE_MASK			(BIT(4)|BIT(5)|BIT(6))
#घोषणा MANUFACTUER_MASK		BIT(7)
#घोषणा ROM_VERSION_MASK		(BIT(11)|BIT(10)|BIT(9)|BIT(8))
#घोषणा CUT_VERSION_MASK		(BIT(15)|BIT(14)|BIT(13)|BIT(12))

/* Get element */
#घोषणा GET_CVID_IC_TYPE(version)	((version) & IC_TYPE_MASK)
#घोषणा GET_CVID_CHIP_TYPE(version)	((version) & CHIP_TYPE_MASK)
#घोषणा GET_CVID_RF_TYPE(version)	((version) & RF_TYPE_MASK)
#घोषणा GET_CVID_MANUFACTUER(version)	((version) & MANUFACTUER_MASK)
#घोषणा GET_CVID_ROM_VERSION(version)	((version) & ROM_VERSION_MASK)
#घोषणा GET_CVID_CUT_VERSION(version)	((version) & CUT_VERSION_MASK)

#घोषणा IS_1T1R(version)	((GET_CVID_RF_TYPE(version)) ? false : true)
#घोषणा IS_1T2R(version)	((GET_CVID_RF_TYPE(version) == RF_TYPE_1T2R)\
							? true : false)
#घोषणा IS_2T2R(version)	((GET_CVID_RF_TYPE(version) == RF_TYPE_2T2R)\
							? true : false)

#घोषणा IS_8812_SERIES(version)	((GET_CVID_IC_TYPE(version) == CHIP_8812) ? \
								true : false)
#घोषणा IS_8821_SERIES(version)	((GET_CVID_IC_TYPE(version) == CHIP_8821) ? \
								true : false)

#घोषणा IS_VENDOR_8812A_TEST_CHIP(version)	((IS_8812_SERIES(version)) ? \
					((IS_NORMAL_CHIP(version)) ? \
						false : true) : false)
#घोषणा IS_VENDOR_8812A_MP_CHIP(version)	((IS_8812_SERIES(version)) ? \
					((IS_NORMAL_CHIP(version)) ? \
						true : false) : false)
#घोषणा IS_VENDOR_8812A_C_CUT(version)		((IS_8812_SERIES(version)) ? \
					((GET_CVID_CUT_VERSION(version) == \
					C_CUT_VERSION) ? \
					true : false) : false)

#घोषणा IS_VENDOR_8821A_TEST_CHIP(version)	((IS_8821_SERIES(version)) ? \
					((IS_NORMAL_CHIP(version)) ? \
					false : true) : false)
#घोषणा IS_VENDOR_8821A_MP_CHIP(version)	((IS_8821_SERIES(version)) ? \
					((IS_NORMAL_CHIP(version)) ? \
						true : false) : false)
#घोषणा IS_VENDOR_8821A_B_CUT(version)		((IS_8821_SERIES(version)) ? \
					((GET_CVID_CUT_VERSION(version) == \
					B_CUT_VERSION) ? \
					true : false) : false)
क्रमागत board_type अणु
	ODM_BOARD_DEFAULT = 0,	  /* The DEFAULT हाल. */
	ODM_BOARD_MINICARD = BIT(0), /* 0 = non-mini card, 1 = mini card. */
	ODM_BOARD_SLIM = BIT(1), /* 0 = non-slim card, 1 = slim card */
	ODM_BOARD_BT = BIT(2), /* 0 = without BT card, 1 = with BT */
	ODM_BOARD_EXT_PA = BIT(3), /* 1 = existing 2G ext-PA */
	ODM_BOARD_EXT_LNA = BIT(4), /* 1 = existing 2G ext-LNA */
	ODM_BOARD_EXT_TRSW = BIT(5), /* 1 = existing ext-TRSW */
	ODM_BOARD_EXT_PA_5G = BIT(6), /* 1 = existing 5G ext-PA */
	ODM_BOARD_EXT_LNA_5G = BIT(7), /* 1 = existing 5G ext-LNA */
पूर्ण;

क्रमागत rf_optype अणु
	RF_OP_BY_SW_3WIRE = 0,
	RF_OP_BY_FW,
	RF_OP_MAX
पूर्ण;

क्रमागत rf_घातer_state अणु
	RF_ON,
	RF_OFF,
	RF_SLEEP,
	RF_SHUT_DOWN,
पूर्ण;

क्रमागत घातer_save_mode अणु
	POWER_SAVE_MODE_ACTIVE,
	POWER_SAVE_MODE_SAVE,
पूर्ण;

क्रमागत घातer_polocy_config अणु
	POWERCFG_MAX_POWER_SAVINGS,
	POWERCFG_GLOBAL_POWER_SAVINGS,
	POWERCFG_LOCAL_POWER_SAVINGS,
	POWERCFG_LENOVO,
पूर्ण;

क्रमागत पूर्णांकerface_select_pci अणु
	INTF_SEL1_MINICARD = 0,
	INTF_SEL0_PCIE = 1,
	INTF_SEL2_RSV = 2,
	INTF_SEL3_RSV = 3,
पूर्ण;

क्रमागत rtl_desc_qsel अणु
	QSLT_BK = 0x2,
	QSLT_BE = 0x0,
	QSLT_VI = 0x5,
	QSLT_VO = 0x7,
	QSLT_BEACON = 0x10,
	QSLT_HIGH = 0x11,
	QSLT_MGNT = 0x12,
	QSLT_CMD = 0x13,
पूर्ण;

काष्ठा phy_sts_cck_8821ae_t अणु
	u8 adc_pwdb_X[4];
	u8 sq_rpt;
	u8 cck_agc_rpt;
पूर्ण;

काष्ठा h2c_cmd_8821ae अणु
	u8 element_id;
	u32 cmd_len;
	u8 *p_cmdbuffer;
पूर्ण;

#पूर्ण_अगर
