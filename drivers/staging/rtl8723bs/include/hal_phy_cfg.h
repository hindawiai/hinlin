<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __INC_HAL8723BPHYCFG_H__
#घोषणा __INC_HAL8723BPHYCFG_H__

/*--------------------------Define Parameters-------------------------------*/
#घोषणा LOOP_LIMIT		5
#घोषणा MAX_STALL_TIME		50	/* us */
#घोषणा AntennaDiversityValue	0x80	/* Adapter->bSoftwareAntennaDiversity ? 0x00:0x80) */
#घोषणा MAX_TXPWR_IDX_NMODE_92S	63
#घोषणा Reset_Cnt_Limit		3

#घोषणा MAX_AGGR_NUM	0x07


/*--------------------------Define Parameters End-------------------------------*/


/*------------------------------Define काष्ठाure----------------------------*/

/*------------------------------Define काष्ठाure End----------------------------*/

/*--------------------------Exported Function prototype---------------------*/
u32 PHY_QueryBBReg_8723B(काष्ठा adapter *Adapter, u32 RegAddr, u32 BitMask);

व्योम PHY_SetBBReg_8723B(काष्ठा adapter *Adapter, u32 RegAddr,
			u32 BitMask, u32 Data);

u32 PHY_QueryRFReg_8723B(काष्ठा adapter *Adapter, u8 eRFPath,
			 u32 RegAddr, u32 BitMask);

व्योम PHY_SetRFReg_8723B(काष्ठा adapter *Adapter, u8 eRFPath,
			u32 RegAddr, u32 BitMask, u32 Data);

/* MAC/BB/RF HAL config */
पूर्णांक PHY_BBConfig8723B(काष्ठा adapter *Adapter);

पूर्णांक PHY_RFConfig8723B(काष्ठा adapter *Adapter);

s32 PHY_MACConfig8723B(काष्ठा adapter *padapter);

व्योम PHY_SetTxPowerIndex(काष्ठा adapter *Adapter, u32 PowerIndex,
			 u8 RFPath, u8 Rate);

u8 PHY_GetTxPowerIndex(काष्ठा adapter *padapter, u8 RFPath, u8 Rate,
			क्रमागत channel_width BandWidth, u8 Channel);

व्योम PHY_GetTxPowerLevel8723B(काष्ठा adapter *Adapter, s32 *घातerlevel);

व्योम PHY_SetTxPowerLevel8723B(काष्ठा adapter *Adapter, u8 channel);

व्योम PHY_SetBWMode8723B(काष्ठा adapter *Adapter, क्रमागत channel_width Bandwidth,
			अचिन्हित अक्षर Offset);

/*  Call after initialization */
व्योम PHY_SwChnl8723B(काष्ठा adapter *Adapter, u8 channel);

व्योम PHY_SetSwChnlBWMode8723B(काष्ठा adapter *Adapter, u8 channel,
				क्रमागत channel_width Bandwidth,
				u8 Offset40, u8 Offset80);

/*--------------------------Exported Function prototype End---------------------*/

#पूर्ण_अगर
