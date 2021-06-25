<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_COMMON_H__
#घोषणा __HAL_COMMON_H__

/*  */
/*        Rate Definition */
/*  */
/* CCK */
#घोषणा	RATR_1M					0x00000001
#घोषणा	RATR_2M					0x00000002
#घोषणा	RATR_55M				0x00000004
#घोषणा	RATR_11M				0x00000008
/* OFDM */
#घोषणा	RATR_6M					0x00000010
#घोषणा	RATR_9M					0x00000020
#घोषणा	RATR_12M				0x00000040
#घोषणा	RATR_18M				0x00000080
#घोषणा	RATR_24M				0x00000100
#घोषणा	RATR_36M				0x00000200
#घोषणा	RATR_48M				0x00000400
#घोषणा	RATR_54M				0x00000800
/* MCS 1 Spatial Stream */
#घोषणा	RATR_MCS0				0x00001000
#घोषणा	RATR_MCS1				0x00002000
#घोषणा	RATR_MCS2				0x00004000
#घोषणा	RATR_MCS3				0x00008000
#घोषणा	RATR_MCS4				0x00010000
#घोषणा	RATR_MCS5				0x00020000
#घोषणा	RATR_MCS6				0x00040000
#घोषणा	RATR_MCS7				0x00080000
/* MCS 2 Spatial Stream */
#घोषणा	RATR_MCS8				0x00100000
#घोषणा	RATR_MCS9				0x00200000
#घोषणा	RATR_MCS10				0x00400000
#घोषणा	RATR_MCS11				0x00800000
#घोषणा	RATR_MCS12				0x01000000
#घोषणा	RATR_MCS13				0x02000000
#घोषणा	RATR_MCS14				0x04000000
#घोषणा	RATR_MCS15				0x08000000

/* CCK */
#घोषणा RATE_1M					BIT(0)
#घोषणा RATE_2M					BIT(1)
#घोषणा RATE_5_5M				BIT(2)
#घोषणा RATE_11M				BIT(3)
/* OFDM */
#घोषणा RATE_6M					BIT(4)
#घोषणा RATE_9M					BIT(5)
#घोषणा RATE_12M				BIT(6)
#घोषणा RATE_18M				BIT(7)
#घोषणा RATE_24M				BIT(8)
#घोषणा RATE_36M				BIT(9)
#घोषणा RATE_48M				BIT(10)
#घोषणा RATE_54M				BIT(11)
/* MCS 1 Spatial Stream */
#घोषणा RATE_MCS0				BIT(12)
#घोषणा RATE_MCS1				BIT(13)
#घोषणा RATE_MCS2				BIT(14)
#घोषणा RATE_MCS3				BIT(15)
#घोषणा RATE_MCS4				BIT(16)
#घोषणा RATE_MCS5				BIT(17)
#घोषणा RATE_MCS6				BIT(18)
#घोषणा RATE_MCS7				BIT(19)
/* MCS 2 Spatial Stream */
#घोषणा RATE_MCS8				BIT(20)
#घोषणा RATE_MCS9				BIT(21)
#घोषणा RATE_MCS10				BIT(22)
#घोषणा RATE_MCS11				BIT(23)
#घोषणा RATE_MCS12				BIT(24)
#घोषणा RATE_MCS13				BIT(25)
#घोषणा RATE_MCS14				BIT(26)
#घोषणा RATE_MCS15				BIT(27)

/*  ALL CCK Rate */
#घोषणा	RATE_ALL_CCK		(RATR_1M | RATR_2M | RATR_55M | RATR_11M)
#घोषणा	RATE_ALL_OFDM_AG	(RATR_6M | RATR_9M | RATR_12M | RATR_18M | \
				 RATR_24M | RATR_36M | RATR_48M | RATR_54M)
#घोषणा	RATE_ALL_OFDM_1SS	(RATR_MCS0 | RATR_MCS1 | RATR_MCS2 |	\
				 RATR_MCS3 | RATR_MCS4 | RATR_MCS5 | RATR_MCS6 | \
				 RATR_MCS7)
#घोषणा	RATE_ALL_OFDM_2SS	(RATR_MCS8 | RATR_MCS9 | RATR_MCS10 | \
				 RATR_MCS11 | RATR_MCS12 | RATR_MCS13 | \
				 RATR_MCS14 | RATR_MCS15)

/*------------------------------ Tx Desc definition Macro --------------------*/
/* pragma mark -- Tx Desc related definition. -- */
/*	Rate */
/*  CCK Rates, TxHT = 0 */
#घोषणा DESC_RATE1M				0x00
#घोषणा DESC_RATE2M				0x01
#घोषणा DESC_RATE5_5M				0x02
#घोषणा DESC_RATE11M				0x03

/*  OFDM Rates, TxHT = 0 */
#घोषणा DESC_RATE6M				0x04
#घोषणा DESC_RATE9M				0x05
#घोषणा DESC_RATE12M				0x06
#घोषणा DESC_RATE18M				0x07
#घोषणा DESC_RATE24M				0x08
#घोषणा DESC_RATE36M				0x09
#घोषणा DESC_RATE48M				0x0a
#घोषणा DESC_RATE54M				0x0b

/*  MCS Rates, TxHT = 1 */
#घोषणा DESC_RATEMCS0				0x0c
#घोषणा DESC_RATEMCS1				0x0d
#घोषणा DESC_RATEMCS2				0x0e
#घोषणा DESC_RATEMCS3				0x0f
#घोषणा DESC_RATEMCS4				0x10
#घोषणा DESC_RATEMCS5				0x11
#घोषणा DESC_RATEMCS6				0x12
#घोषणा DESC_RATEMCS7				0x13
#घोषणा DESC_RATEMCS8				0x14
#घोषणा DESC_RATEMCS9				0x15
#घोषणा DESC_RATEMCS10				0x16
#घोषणा DESC_RATEMCS11				0x17
#घोषणा DESC_RATEMCS12				0x18
#घोषणा DESC_RATEMCS13				0x19
#घोषणा DESC_RATEMCS14				0x1a
#घोषणा DESC_RATEMCS15				0x1b
#घोषणा DESC_RATEMCS15_SG			0x1c
#घोषणा DESC_RATEMCS32				0x20

/*  1 Byte दीर्घ (in unit of TU) */
#घोषणा REG_P2P_CTWIN				0x0572
#घोषणा REG_NOA_DESC_SEL			0x05CF
#घोषणा REG_NOA_DESC_DURATION			0x05E0
#घोषणा REG_NOA_DESC_INTERVAL			0x05E4
#घोषणा REG_NOA_DESC_START			0x05E8
#घोषणा REG_NOA_DESC_COUNT			0x05EC

#समावेश "HalVerDef.h"
व्योम dump_chip_info(काष्ठा HAL_VERSION	ChipVersion);

/* वापस the final channel plan decision */
u8 hal_com_get_channel_plan(u8 hw_channel_plan, u8 sw_channel_plan,
			    u8 def_channel_plan, bool load_fail);

u8 MRateToHwRate(u8 rate);

व्योम hal_set_brate_cfg(u8 *brates, u16 *rate_cfg);

bool hal_mapping_out_pipe(काष्ठा adapter *adapter, u8 numoutpipe);

#पूर्ण_अगर /* __HAL_COMMON_H__ */
