<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INC_RA_H
#घोषणा __INC_RA_H
/*
 * Copyright (c) Realtek Semiconductor Corp. All rights reserved.
 *
 * Module Name:
 *	RateAdaptive.h
 *
 * Abstract:
 *	Prototype of RA and related data काष्ठाure.
 *
 * Major Change History:
 *	When       Who               What
 *	---------- ---------------   -------------------------------
 *	2011-08-12 Page            Create.
 */

/*  Rate adaptive define */
#घोषणा	PERENTRY	23
#घोषणा	RETRYSIZE	5
#घोषणा	RATESIZE	28
#घोषणा	TX_RPT2_ITEM_SIZE	8

/*  */
/*  TX report 2 क्रमmat in Rx desc */
/*  */
#घोषणा GET_TX_RPT2_DESC_PKT_LEN_88E(__pRxStatusDesc)		\
	LE_BITS_TO_4BYTE(__pRxStatusDesc, 0, 9)
#घोषणा GET_TX_RPT2_DESC_MACID_VALID_1_88E(__pRxStatusDesc)	\
	LE_BITS_TO_4BYTE(__pRxStatusDesc + 16, 0, 32)
#घोषणा GET_TX_RPT2_DESC_MACID_VALID_2_88E(__pRxStatusDesc)	\
	LE_BITS_TO_4BYTE(__pRxStatusDesc + 20, 0, 32)

#घोषणा GET_TX_REPORT_TYPE1_RERTY_0(__pAddr)			\
	LE_BITS_TO_4BYTE(__pAddr, 0, 16)
#घोषणा GET_TX_REPORT_TYPE1_RERTY_1(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 2, 0, 8)
#घोषणा GET_TX_REPORT_TYPE1_RERTY_2(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 3, 0, 8)
#घोषणा GET_TX_REPORT_TYPE1_RERTY_3(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 4, 0, 8)
#घोषणा GET_TX_REPORT_TYPE1_RERTY_4(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 4 + 1, 0, 8)
#घोषणा GET_TX_REPORT_TYPE1_DROP_0(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 4 + 2, 0, 8)
#घोषणा GET_TX_REPORT_TYPE1_DROP_1(__pAddr)			\
	LE_BITS_TO_1BYTE(__pAddr + 4 + 3, 0, 8)

/*  End rate adaptive define */

पूर्णांक ODM_RAInfo_Init_all(काष्ठा odm_dm_काष्ठा *dm_odm);

पूर्णांक ODM_RAInfo_Init(काष्ठा odm_dm_काष्ठा *dm_odm, u8 MacID);

u8 ODM_RA_GetShortGI_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 MacID);

u8 ODM_RA_GetDecisionRate_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 MacID);

u8 ODM_RA_GetHwPwrStatus_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 MacID);
व्योम ODM_RA_UpdateRateInfo_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 MacID,
				 u8 RateID, u32 RateMask,
				 u8 SGIEnable);

व्योम ODM_RA_SetRSSI_8188E(काष्ठा odm_dm_काष्ठा *dm_odm, u8 macid,
			  u8 rssi);

व्योम ODM_RA_TxRPT2Handle_8188E(काष्ठा odm_dm_काष्ठा *dm_odm,
			       u8 *txrpt_buf, u16 txrpt_len,
			       u32 validentry0, u32 validentry1);

व्योम ODM_RA_Set_TxRPT_Time(काष्ठा odm_dm_काष्ठा *dm_odm, u16 minRptTime);

#पूर्ण_अगर
