<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __HAL_PHY_RF_8723B_H__
#घोषणा __HAL_PHY_RF_8723B_H__

/*--------------------------Define Parameters-------------------------------*/
#घोषणा	IQK_DELAY_TIME_8723B		20		/* ms */
#घोषणा IQK_DEFERRED_TIME_8723B		4
#घोषणा	index_mapping_NUM_8723B		15
#घोषणा AVG_THERMAL_NUM_8723B		4
#घोषणा	RF_T_METER_8723B					0x42	/*  */


व्योम ConfigureTxघातerTrack_8723B(काष्ठा txpwrtrack_cfg *pConfig);

व्योम DoIQK_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 DeltaThermalIndex,
	u8 ThermalValue,
	u8 Threshold
);

व्योम ODM_TxPwrTrackSetPwr_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत pwrtrack_method Method,
	u8 RFPath,
	u8 ChannelMappedIndex
);

/* 1 7. IQK */
व्योम PHY_IQCalibrate_8723B(
	काष्ठा adapter *Adapter,
	bool bReCovery,
	bool bRestore,
	bool Is2ant,
	u8 RF_Path
);

व्योम ODM_SetIQCbyRFpath(काष्ठा dm_odm_t *pDM_Odm, u32 RFpath);

/*  */
/*  LC calibrate */
/*  */
व्योम PHY_LCCalibrate_8723B(काष्ठा dm_odm_t *pDM_Odm);

/*  */
/*  AP calibrate */
/*  */
व्योम PHY_DigitalPredistortion_8723B(काष्ठा adapter *padapter);


व्योम _PHY_SaveADDARegisters_8723B(
	काष्ठा adapter *padapter,
	u32 *ADDAReg,
	u32 *ADDABackup,
	u32 RegisterNum
);

व्योम _PHY_PathADDAOn_8723B(
	काष्ठा adapter *padapter,
	u32 *ADDAReg,
	bool isPathAOn,
	bool is2T
);

व्योम _PHY_MACSettingCalibration_8723B(
	काष्ठा adapter *padapter, u32 *MACReg, u32 *MACBackup
);

#पूर्ण_अगर /*  #अगर_अघोषित __HAL_PHY_RF_8188E_H__ */
