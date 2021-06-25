<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8188E_DM_H__
#घोषणा __RTL8188E_DM_H__
क्रमागतअणु
	UP_LINK,
	DOWN_LINK,
पूर्ण;

काष्ठा	dm_priv अणु
	u8	DM_Type;
	u8	DMFlag;
	u8	InitDMFlag;
	u32	InitODMFlag;

	/*  Upper and Lower Signal threshold क्रम Rate Adaptive*/
	पूर्णांक	UndecoratedSmoothedPWDB;
	पूर्णांक	UndecoratedSmoothedCCK;
	पूर्णांक	EntryMinUndecoratedSmoothedPWDB;
	पूर्णांक	EntryMaxUndecoratedSmoothedPWDB;
	पूर्णांक	MinUndecoratedPWDBForDM;
	पूर्णांक	LastMinUndecoratedPWDBForDM;

	/* क्रम High Power */
	u8 bDynamicTxPowerEnable;
	u8 LastDTPLvl;
	u8 DynamicTxHighPowerLvl;/* Tx Power Control क्रम Near/Far Range */
	u8	PowerIndex_backup[6];
पूर्ण;

व्योम rtl8188e_InitHalDm(काष्ठा adapter *adapt);

व्योम AntDivCompare8188E(काष्ठा adapter *adapt, काष्ठा wlan_bssid_ex *dst,
			काष्ठा wlan_bssid_ex *src);

#पूर्ण_अगर
