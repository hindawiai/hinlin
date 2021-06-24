<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _TSTYPE_H_
#घोषणा _TSTYPE_H_
#समावेश "rtl819x_Qos.h"
#घोषणा TS_ADDBA_DELAY		60

#घोषणा TOTAL_TS_NUM		16
#घोषणा TCLAS_NUM		4

क्रमागत tr_select अणु
	TX_सूची = 0,
	RX_सूची = 1,
पूर्ण;

काष्ठा ts_common_info अणु
	काष्ठा list_head		List;
	काष्ठा समयr_list		SetupTimer;
	काष्ठा समयr_list		InactTimer;
	u8				Addr[ETH_ALEN];
	जोड़ tspec_body TSpec;
	जोड़ qos_tclas TClass[TCLAS_NUM];
	u8				TClasProc;
	u8				TClasNum;
पूर्ण;

काष्ठा tx_ts_record अणु
	काष्ठा ts_common_info TsCommonInfo;
	u16				TxCurSeq;
	काष्ठा ba_record TxPendingBARecord;
	काष्ठा ba_record TxAdmittedBARecord;
	u8				bAddBaReqInProgress;
	u8				bAddBaReqDelayed;
	u8				bUsingBa;
	u8				bDisable_AddBa;
	काष्ठा समयr_list		TsAddBaTimer;
	u8				num;
पूर्ण;

काष्ठा rx_ts_record अणु
	काष्ठा ts_common_info ts_common_info;
	u16 rx_indicate_seq;
	u16 rx_समयout_indicate_seq;
	काष्ठा list_head rx_pending_pkt_list;
	काष्ठा समयr_list rx_pkt_pending_समयr;
	काष्ठा ba_record rx_admitted_ba_record;
	u16 rx_last_seq_num;
	u8 rx_last_frag_num;
	u8 num;
पूर्ण;



#पूर्ण_अगर
