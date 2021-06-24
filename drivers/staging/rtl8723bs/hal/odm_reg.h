<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*  File Name: odm_reg.h */
/*  Description: */
/*  This file is क्रम general रेजिस्टर definition. */
#अगर_अघोषित	__HAL_ODM_REG_H__
#घोषणा __HAL_ODM_REG_H__

/*  Register Definition */

/* MAC REG */
#घोषणा	ODM_BB_RESET				0x002
#घोषणा	ODM_DUMMY				0x4fe
#घोषणा	RF_T_METER_OLD				0x24
#घोषणा	RF_T_METER_NEW				0x42

#घोषणा	ODM_EDCA_VO_PARAM			0x500
#घोषणा	ODM_EDCA_VI_PARAM			0x504
#घोषणा	ODM_EDCA_BE_PARAM			0x508
#घोषणा	ODM_EDCA_BK_PARAM			0x50C
#घोषणा	ODM_TXPAUSE				0x522

/* BB REG */
#घोषणा	ODM_FPGA_PHY0_PAGE8			0x800
#घोषणा	ODM_PSD_SETTING				0x808
#घोषणा	ODM_AFE_SETTING				0x818
#घोषणा	ODM_TXAGC_B_24_54			0x834
#घोषणा	ODM_TXAGC_B_MCS32_5			0x838
#घोषणा	ODM_TXAGC_B_MCS0_MCS3			0x83c
#घोषणा	ODM_TXAGC_B_MCS4_MCS7			0x848
#घोषणा	ODM_TXAGC_B_MCS8_MCS11			0x84c
#घोषणा	ODM_ANALOG_REGISTER			0x85c
#घोषणा	ODM_RF_INTERFACE_OUTPUT			0x860
#घोषणा	ODM_TXAGC_B_MCS12_MCS15			0x868
#घोषणा	ODM_TXAGC_B_11_A_2_11			0x86c
#घोषणा	ODM_AD_DA_LSB_MASK			0x874
#घोषणा	ODM_ENABLE_3_WIRE			0x88c
#घोषणा	ODM_PSD_REPORT				0x8b4
#घोषणा	ODM_R_ANT_SELECT			0x90c
#घोषणा	ODM_CCK_ANT_SELECT			0xa07
#घोषणा	ODM_CCK_PD_THRESH			0xa0a
#घोषणा	ODM_CCK_RF_REG1				0xa11
#घोषणा	ODM_CCK_MATCH_FILTER			0xa20
#घोषणा	ODM_CCK_RAKE_MAC			0xa2e
#घोषणा	ODM_CCK_CNT_RESET			0xa2d
#घोषणा	ODM_CCK_TX_DIVERSITY			0xa2f
#घोषणा	ODM_CCK_FA_CNT_MSB			0xa5b
#घोषणा	ODM_CCK_FA_CNT_LSB			0xa5c
#घोषणा	ODM_CCK_NEW_FUNCTION			0xa75
#घोषणा	ODM_OFDM_PHY0_PAGE_C			0xc00
#घोषणा	ODM_OFDM_RX_ANT				0xc04
#घोषणा	ODM_R_A_RXIQI				0xc14
#घोषणा	ODM_R_A_AGC_CORE1			0xc50
#घोषणा	ODM_R_A_AGC_CORE2			0xc54
#घोषणा	ODM_R_B_AGC_CORE1			0xc58
#घोषणा	ODM_R_AGC_PAR				0xc70
#घोषणा	ODM_R_HTSTF_AGC_PAR			0xc7c
#घोषणा	ODM_TX_PWR_TRAINING_A			0xc90
#घोषणा	ODM_TX_PWR_TRAINING_B			0xc98
#घोषणा	ODM_OFDM_FA_CNT1			0xcf0
#घोषणा	ODM_OFDM_PHY0_PAGE_D			0xd00
#घोषणा	ODM_OFDM_FA_CNT2			0xda0
#घोषणा	ODM_OFDM_FA_CNT3			0xda4
#घोषणा	ODM_OFDM_FA_CNT4			0xda8
#घोषणा	ODM_TXAGC_A_6_18			0xe00
#घोषणा	ODM_TXAGC_A_24_54			0xe04
#घोषणा	ODM_TXAGC_A_1_MCS32			0xe08
#घोषणा	ODM_TXAGC_A_MCS0_MCS3			0xe10
#घोषणा	ODM_TXAGC_A_MCS4_MCS7			0xe14
#घोषणा	ODM_TXAGC_A_MCS8_MCS11			0xe18
#घोषणा	ODM_TXAGC_A_MCS12_MCS15			0xe1c

/* RF REG */
#घोषणा	ODM_GAIN_SETTING			0x00
#घोषणा	ODM_CHANNEL				0x18

/* Ant Detect Reg */
#घोषणा	ODM_DPDT				0x300

/* PSD Init */
#घोषणा	ODM_PSDREG				0x808

/* 92D Path Div */
#घोषणा	PATHDIV_REG				0xB30
#घोषणा	PATHDIV_TRI				0xBA0

/*  Biपंचांगap Definition */

#घोषणा	BIT_FA_RESET				BIT0

#पूर्ण_अगर
