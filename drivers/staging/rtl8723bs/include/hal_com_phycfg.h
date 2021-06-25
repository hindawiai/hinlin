<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_COM_PHYCFG_H__
#घोषणा __HAL_COM_PHYCFG_H__

#घोषणा		PathA		0x0	/*  Useless */
#घोषणा		PathB		0x1
#घोषणा		PathC		0x2
#घोषणा		PathD		0x3

क्रमागत rate_section अणु
	CCK = 0,
	OFDM,
	HT_MCS0_MCS7,
	HT_MCS8_MCS15,
	HT_MCS16_MCS23,
	HT_MCS24_MCS31,
	VHT_1SSMCS0_1SSMCS9,
	VHT_2SSMCS0_2SSMCS9,
	VHT_3SSMCS0_3SSMCS9,
	VHT_4SSMCS0_4SSMCS9,
पूर्ण;

क्रमागत अणु
	RF_1TX = 0,
	RF_2TX,
	RF_3TX,
	RF_4TX,
	RF_MAX_TX_NUM,
	RF_TX_NUM_NONIMPLEMENT,
पूर्ण;

#घोषणा MAX_POWER_INDEX			0x3F

क्रमागत अणु
	TXPWR_LMT_FCC = 0,
	TXPWR_LMT_MKK,
	TXPWR_LMT_ETSI,
	TXPWR_LMT_WW,
	TXPWR_LMT_MAX_REGULATION_NUM,
पूर्ण;

/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा bb_रेजिस्टर_def अणु
	u32 rfपूर्णांकfs;			/*  set software control: */
					/* 	0x870~0x877[8 bytes] */

	u32 rfपूर्णांकfo;			/*  output data: */
					/* 	0x860~0x86f [16 bytes] */

	u32 rfपूर्णांकfe;			/*  output enable: */
					/* 	0x860~0x86f [16 bytes] */

	u32 rf3wireOffset;		/*  LSSI data: */
					/* 	0x840~0x84f [16 bytes] */

	u32 rfHSSIPara2;		/*  wire parameter control2 : */
					/* 	0x824~0x827, 0x82c~0x82f,
					 *	0x834~0x837, 0x83c~0x83f
					 */
	u32 rfLSSIReadBack;		/* LSSI RF पढ़ोback data SI mode */
					/* 	0x8a0~0x8af [16 bytes] */

	u32 rfLSSIReadBackPi;		/* LSSI RF पढ़ोback data PI mode
					 *	0x8b8-8bc क्रम Path A and B */

पूर्ण;

u8
PHY_GetTxPowerByRateBase(
काष्ठा adapter *Adapter,
u8 		Band,
u8 		RfPath,
u8 		TxNum,
क्रमागत rate_section	RateSection
	);

u8
PHY_GetRateSectionIndexOfTxPowerByRate(
काष्ठा adapter *padapter,
u32 		RegAddr,
u32 		BitMask
	);

व्योम
PHY_GetRateValuesOfTxPowerByRate(
काष्ठा adapter *padapter,
u32 		RegAddr,
u32 		BitMask,
u32 		Value,
u8		*RateIndex,
s8		*PwrByRateVal,
u8		*RateNum
	);

u8
PHY_GetRateIndexOfTxPowerByRate(
u8 Rate
	);

व्योम
PHY_SetTxPowerIndexByRateSection(
काष्ठा adapter *padapter,
u8 		RFPath,
u8 		Channel,
u8 		RateSection
	);

s8
PHY_GetTxPowerByRate(
काष्ठा adapter *padapter,
u8 	Band,
u8 	RFPath,
u8 	TxNum,
u8 	RateIndex
	);

व्योम
PHY_SetTxPowerByRate(
काष्ठा adapter *padapter,
u8 	Band,
u8 	RFPath,
u8 	TxNum,
u8 	Rate,
s8			Value
	);

व्योम
PHY_SetTxPowerLevelByPath(
काष्ठा adapter *Adapter,
u8 	channel,
u8 	path
	);

व्योम
PHY_SetTxPowerIndexByRateArray(
काष्ठा adapter *padapter,
u8 		RFPath,
क्रमागत channel_width	BandWidth,
u8 		Channel,
u8		*Rates,
u8 		RateArraySize
	);

व्योम
PHY_InitTxPowerByRate(
काष्ठा adapter *padapter
	);

व्योम
PHY_StoreTxPowerByRate(
काष्ठा adapter *padapter,
u32 		Band,
u32 		RfPath,
u32 		TxNum,
u32 		RegAddr,
u32 		BitMask,
u32 		Data
	);

व्योम
PHY_TxPowerByRateConfiguration(
	काष्ठा adapter *padapter
	);

u8
PHY_GetTxPowerIndexBase(
काष्ठा adapter *padapter,
u8 		RFPath,
u8 		Rate,
क्रमागत channel_width	BandWidth,
u8 		Channel,
	bool		*bIn24G
	);

s8 phy_get_tx_pwr_lmt(काष्ठा adapter *adapter, u32 RegPwrTblSel,
			क्रमागत band_type Band, क्रमागत channel_width Bandwidth,
u8 		RfPath,
u8 		DataRate,
u8 		Channel
	);

व्योम
PHY_SetTxPowerLimit(
काष्ठा adapter *Adapter,
u8 			*Regulation,
u8 			*Band,
u8 			*Bandwidth,
u8 			*RateSection,
u8 			*RfPath,
u8 			*Channel,
u8 			*PowerLimit
	);

व्योम
PHY_ConvertTxPowerLimitToPowerIndex(
काष्ठा adapter *Adapter
	);

व्योम
PHY_InitTxPowerLimit(
काष्ठा adapter *Adapter
	);

s8
PHY_GetTxPowerTrackingOffset(
	काष्ठा adapter *padapter,
	u8 	Rate,
	u8 	RFPath
	);

व्योम
Hal_ChannelPlanToRegulation(
काष्ठा adapter *Adapter,
u16 			ChannelPlan
	);

#पूर्ण_अगर /* __HAL_COMMON_H__ */
