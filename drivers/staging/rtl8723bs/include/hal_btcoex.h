<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_BTCOEX_H__
#घोषणा __HAL_BTCOEX_H__

#समावेश <drv_types.h>

/*  Some variables can't get from outsrc BT-Coex, */
/*  so we need to save here */
काष्ठा bt_coexist अणु
	u8 bBtExist;
	u8 btTotalAntNum;
	u8 btChipType;
	u8 bInitlized;
पूर्ण;

व्योम DBG_BT_INFO(u8 *dbgmsg);

व्योम hal_btcoex_SetBTCoexist(काष्ठा adapter *padapter, u8 bBtExist);
bool hal_btcoex_IsBtExist(काष्ठा adapter *padapter);
bool hal_btcoex_IsBtDisabled(काष्ठा adapter *);
व्योम hal_btcoex_SetChipType(काष्ठा adapter *padapter, u8 chipType);
व्योम hal_btcoex_SetPgAntNum(काष्ठा adapter *padapter, u8 antNum);
व्योम hal_btcoex_SetSingleAntPath(काष्ठा adapter *padapter, u8 singleAntPath);

व्योम hal_btcoex_Initialize(व्योम *padapter);
व्योम hal_btcoex_PowerOnSetting(काष्ठा adapter *padapter);
व्योम hal_btcoex_InitHwConfig(काष्ठा adapter *padapter, u8 bWअगरiOnly);

व्योम hal_btcoex_IpsNotअगरy(काष्ठा adapter *padapter, u8 type);
व्योम hal_btcoex_LpsNotअगरy(काष्ठा adapter *padapter, u8 type);
व्योम hal_btcoex_ScanNotअगरy(काष्ठा adapter *padapter, u8 type);
व्योम hal_btcoex_ConnectNotअगरy(काष्ठा adapter *padapter, u8 action);
व्योम hal_btcoex_MediaStatusNotअगरy(काष्ठा adapter *padapter, u8 mediaStatus);
व्योम hal_btcoex_SpecialPacketNotअगरy(काष्ठा adapter *padapter, u8 pktType);
व्योम hal_btcoex_IQKNotअगरy(काष्ठा adapter *padapter, u8 state);
व्योम hal_btcoex_BtInfoNotअगरy(काष्ठा adapter *padapter, u8 length, u8 *पंचांगpBuf);
व्योम hal_btcoex_SuspendNotअगरy(काष्ठा adapter *padapter, u8 state);
व्योम hal_btcoex_HaltNotअगरy(काष्ठा adapter *padapter);

व्योम hal_btcoex_Handler(काष्ठा adapter *padapter);

s32 hal_btcoex_IsBTCoexCtrlAMPDUSize(काष्ठा adapter *padapter);
व्योम hal_btcoex_SetManualControl(काष्ठा adapter *padapter, u8 bmanual);
bool hal_btcoex_IsBtControlLps(काष्ठा adapter *padapter);
bool hal_btcoex_IsLpsOn(काष्ठा adapter *padapter);
u8 hal_btcoex_RpwmVal(काष्ठा adapter *);
u8 hal_btcoex_LpsVal(काष्ठा adapter *);
u32 hal_btcoex_GetRaMask(काष्ठा adapter *);
व्योम hal_btcoex_RecordPwrMode(काष्ठा adapter *padapter, u8 *pCmdBuf, u8 cmdLen);
व्योम hal_btcoex_DisplayBtCoexInfo(काष्ठा adapter *, u8 *pbuf, u32 bufsize);
व्योम hal_btcoex_SetDBG(काष्ठा adapter *, u32 *pDbgModule);
u32 hal_btcoex_GetDBG(काष्ठा adapter *, u8 *pStrBuf, u32 bufSize);

#पूर्ण_अगर /*  !__HAL_BTCOEX_H__ */
