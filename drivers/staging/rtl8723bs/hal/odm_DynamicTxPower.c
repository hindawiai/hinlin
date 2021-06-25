<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

व्योम odm_DynamicTxPowerInit(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;

	pdmpriv->bDynamicTxPowerEnable = false;

	pdmpriv->LastDTPLvl = TxHighPwrLevel_Normal;
	pdmpriv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
पूर्ण
