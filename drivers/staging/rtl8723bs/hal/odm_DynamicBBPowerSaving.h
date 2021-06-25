<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__ODMDYNAMICBBPOWERSAVING_H__
#घोषणा    __ODMDYNAMICBBPOWERSAVING_H__

काष्ठा ps_t अणु /* _Dynamic_Power_Saving_ */
	u8 PreCCAState;
	u8 CurCCAState;

	u8 PreRFState;
	u8 CurRFState;

	पूर्णांक Rssi_val_min;

	u8 initialize;
	u32 Reg874, RegC70, Reg85C, RegA74;

पूर्ण;

#घोषणा dm_RF_Saving ODM_RF_Saving

व्योम ODM_RF_Saving(व्योम *pDM_VOID, u8 bForceInNormal);

व्योम odm_DynamicBBPowerSavingInit(व्योम *pDM_VOID);

#पूर्ण_अगर
