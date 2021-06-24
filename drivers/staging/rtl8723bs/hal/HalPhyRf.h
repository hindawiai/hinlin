<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

 #अगर_अघोषित __HAL_PHY_RF_H__
 #घोषणा __HAL_PHY_RF_H__

क्रमागत pwrtrack_method अणु
	BBSWING,
	TXAGC,
	MIX_MODE
पूर्ण;

प्रकार व्योम (*FuncSetPwr)(काष्ठा dm_odm_t *, क्रमागत pwrtrack_method, u8, u8);
प्रकार व्योम (*FuncIQK)(काष्ठा dm_odm_t *, u8, u8, u8);
प्रकार व्योम (*FuncLCK)(काष्ठा dm_odm_t *);
प्रकार व्योम (*FuncSwing)(काष्ठा dm_odm_t *, u8 **, u8 **, u8 **, u8 **);

काष्ठा txpwrtrack_cfg अणु
	u8 SwingTableSize_CCK;
	u8 SwingTableSize_OFDM;
	u8 Threshold_IQK;
	u8 AverageThermalNum;
	u8 RfPathCount;
	u32 ThermalRegAddr;
	FuncSetPwr ODM_TxPwrTrackSetPwr;
	FuncIQK DoIQK;
	FuncLCK PHY_LCCalibrate;
	FuncSwing GetDeltaSwingTable;
पूर्ण;

व्योम ConfigureTxघातerTrack(काष्ठा dm_odm_t *pDM_Odm, काष्ठा txpwrtrack_cfg *pConfig);


व्योम ODM_ClearTxPowerTrackingState(काष्ठा dm_odm_t *pDM_Odm);

व्योम ODM_TXPowerTrackingCallback_ThermalMeter(काष्ठा adapter *Adapter);

#पूर्ण_अगर	/*  #अगर_अघोषित __HAL_PHY_RF_H__ */
