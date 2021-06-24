<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/etherdevice.h>
#समावेश "rtllib.h"
#समावेश "rtl819x_BA.h"

अटल व्योम ActivateBAEntry(काष्ठा rtllib_device *ieee, काष्ठा ba_record *pBA,
			    u16 Time)
अणु
	pBA->b_valid = true;
	अगर (Time != 0)
		mod_समयr(&pBA->समयr, jअगरfies + msecs_to_jअगरfies(Time));
पूर्ण

अटल व्योम DeActivateBAEntry(काष्ठा rtllib_device *ieee, काष्ठा ba_record *pBA)
अणु
	pBA->b_valid = false;
	del_समयr_sync(&pBA->समयr);
पूर्ण

अटल u8 TxTsDeleteBA(काष्ठा rtllib_device *ieee, काष्ठा tx_ts_record *pTxTs)
अणु
	काष्ठा ba_record *pAdmittedBa = &pTxTs->TxAdmittedBARecord;
	काष्ठा ba_record *pPendingBa = &pTxTs->TxPendingBARecord;
	u8 bSendDELBA = false;

	अगर (pPendingBa->b_valid) अणु
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	पूर्ण

	अगर (pAdmittedBa->b_valid) अणु
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	पूर्ण
	वापस bSendDELBA;
पूर्ण

अटल u8 RxTsDeleteBA(काष्ठा rtllib_device *ieee, काष्ठा rx_ts_record *pRxTs)
अणु
	काष्ठा ba_record *pBa = &pRxTs->rx_admitted_ba_record;
	u8			bSendDELBA = false;

	अगर (pBa->b_valid) अणु
		DeActivateBAEntry(ieee, pBa);
		bSendDELBA = true;
	पूर्ण

	वापस bSendDELBA;
पूर्ण

व्योम ResetBaEntry(काष्ठा ba_record *pBA)
अणु
	pBA->b_valid			  = false;
	pBA->ba_param_set.लघु_data	  = 0;
	pBA->ba_समयout_value		  = 0;
	pBA->dialog_token		  = 0;
	pBA->ba_start_seq_ctrl.लघु_data = 0;
पूर्ण
अटल काष्ठा sk_buff *rtllib_ADDBA(काष्ठा rtllib_device *ieee, u8 *Dst,
				    काष्ठा ba_record *pBA,
				    u16 StatusCode, u8 type)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtllib_hdr_3addr *BAReq = शून्य;
	u8 *tag = शून्य;
	u16 len = ieee->tx_headroom + 9;

	netdev_dbg(ieee->dev, "%s(): frame(%d) sentd to: %pM, ieee->dev:%p\n",
		   __func__, type, Dst, ieee->dev);

	अगर (!pBA) अणु
		netdev_warn(ieee->dev, "pBA is NULL\n");
		वापस शून्य;
	पूर्ण
	skb = dev_alloc_skb(len + माप(काष्ठा rtllib_hdr_3addr));
	अगर (!skb)
		वापस शून्य;

	स_रखो(skb->data, 0, माप(काष्ठा rtllib_hdr_3addr));

	skb_reserve(skb, ieee->tx_headroom);

	BAReq = skb_put(skb, माप(काष्ठा rtllib_hdr_3addr));

	ether_addr_copy(BAReq->addr1, Dst);
	ether_addr_copy(BAReq->addr2, ieee->dev->dev_addr);

	ether_addr_copy(BAReq->addr3, ieee->current_network.bssid);
	BAReq->frame_ctl = cpu_to_le16(RTLLIB_STYPE_MANAGE_ACT);

	tag = skb_put(skb, 9);
	*tag++ = ACT_CAT_BA;
	*tag++ = type;
	*tag++ = pBA->dialog_token;

	अगर (type == ACT_ADDBARSP) अणु
		RT_TRACE(COMP_DBG, "====>to send ADDBARSP\n");

		put_unaligned_le16(StatusCode, tag);
		tag += 2;
	पूर्ण

	put_unaligned_le16(pBA->ba_param_set.लघु_data, tag);
	tag += 2;

	put_unaligned_le16(pBA->ba_समयout_value, tag);
	tag += 2;

	अगर (type == ACT_ADDBAREQ) अणु
		स_नकल(tag, (u8 *)&(pBA->ba_start_seq_ctrl), 2);
		tag += 2;
	पूर्ण

#अगर_घोषित VERBOSE_DEBUG
	prपूर्णांक_hex_dump_bytes("%s: ", DUMP_PREFIX_NONE, skb->data,
			     __func__, skb->len);
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtllib_DELBA(काष्ठा rtllib_device *ieee, u8 *dst,
				    काष्ठा ba_record *pBA,
				    क्रमागत tr_select TxRxSelect, u16 ReasonCode)
अणु
	जोड़ delba_param_set DelbaParamSet;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtllib_hdr_3addr *Delba = शून्य;
	u8 *tag = शून्य;
	u16 len = 6 + ieee->tx_headroom;

	अगर (net_ratelimit())
		netdev_dbg(ieee->dev, "%s(): ReasonCode(%d) sentd to: %pM\n",
			   __func__, ReasonCode, dst);

	स_रखो(&DelbaParamSet, 0, 2);

	DelbaParamSet.field.initiator = (TxRxSelect == TX_सूची) ? 1 : 0;
	DelbaParamSet.field.tid	= pBA->ba_param_set.field.tid;

	skb = dev_alloc_skb(len + माप(काष्ठा rtllib_hdr_3addr));
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, ieee->tx_headroom);

	Delba = skb_put(skb, माप(काष्ठा rtllib_hdr_3addr));

	ether_addr_copy(Delba->addr1, dst);
	ether_addr_copy(Delba->addr2, ieee->dev->dev_addr);
	ether_addr_copy(Delba->addr3, ieee->current_network.bssid);
	Delba->frame_ctl = cpu_to_le16(RTLLIB_STYPE_MANAGE_ACT);

	tag = skb_put(skb, 6);

	*tag++ = ACT_CAT_BA;
	*tag++ = ACT_DELBA;


	put_unaligned_le16(DelbaParamSet.लघु_data, tag);
	tag += 2;

	put_unaligned_le16(ReasonCode, tag);
	tag += 2;

#अगर_घोषित VERBOSE_DEBUG
	prपूर्णांक_hex_dump_bytes("%s: ", DUMP_PREFIX_NONE, skb->data,
			     __func__, skb->len);
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल व्योम rtllib_send_ADDBAReq(काष्ठा rtllib_device *ieee, u8 *dst,
				 काष्ठा ba_record *pBA)
अणु
	काष्ठा sk_buff *skb;

	skb = rtllib_ADDBA(ieee, dst, pBA, 0, ACT_ADDBAREQ);

	अगर (skb) अणु
		RT_TRACE(COMP_DBG, "====>to send ADDBAREQ!!!!!\n");
		sofपंचांगac_mgmt_xmit(skb, ieee);
	पूर्ण अन्यथा अणु
		netdev_dbg(ieee->dev, "Failed to generate ADDBAReq packet.\n");
	पूर्ण
पूर्ण

अटल व्योम rtllib_send_ADDBARsp(काष्ठा rtllib_device *ieee, u8 *dst,
				 काष्ठा ba_record *pBA, u16 StatusCode)
अणु
	काष्ठा sk_buff *skb;

	skb = rtllib_ADDBA(ieee, dst, pBA, StatusCode, ACT_ADDBARSP);
	अगर (skb)
		sofपंचांगac_mgmt_xmit(skb, ieee);
	अन्यथा
		netdev_dbg(ieee->dev, "Failed to generate ADDBARsp packet.\n");
पूर्ण

अटल व्योम rtllib_send_DELBA(काष्ठा rtllib_device *ieee, u8 *dst,
			      काष्ठा ba_record *pBA, क्रमागत tr_select TxRxSelect,
			      u16 ReasonCode)
अणु
	काष्ठा sk_buff *skb;

	skb = rtllib_DELBA(ieee, dst, pBA, TxRxSelect, ReasonCode);
	अगर (skb)
		sofपंचांगac_mgmt_xmit(skb, ieee);
	अन्यथा
		netdev_dbg(ieee->dev, "Failed to generate DELBA packet.\n");
पूर्ण

पूर्णांक rtllib_rx_ADDBAReq(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtllib_hdr_3addr *req = शून्य;
	u16 rc = 0;
	u8 *dst = शून्य, *pDialogToken = शून्य, *tag = शून्य;
	काष्ठा ba_record *pBA = शून्य;
	जोड़ ba_param_set *pBaParamSet = शून्य;
	u16 *pBaTimeoutVal = शून्य;
	जोड़ sequence_control *pBaStartSeqCtrl = शून्य;
	काष्ठा rx_ts_record *pTS = शून्य;

	अगर (skb->len < माप(काष्ठा rtllib_hdr_3addr) + 9) अणु
		netdev_warn(ieee->dev, "Invalid skb len in BAREQ(%d / %d)\n",
			    (पूर्णांक)skb->len,
			    (पूर्णांक)(माप(काष्ठा rtllib_hdr_3addr) + 9));
		वापस -1;
	पूर्ण

#अगर_घोषित VERBOSE_DEBUG
	prपूर्णांक_hex_dump_bytes("%s: ", DUMP_PREFIX_NONE, __func__,
			     skb->data, skb->len);
#पूर्ण_अगर

	req = (काष्ठा rtllib_hdr_3addr *) skb->data;
	tag = (u8 *)req;
	dst = (u8 *)(&req->addr2[0]);
	tag += माप(काष्ठा rtllib_hdr_3addr);
	pDialogToken = tag + 2;
	pBaParamSet = (जोड़ ba_param_set *)(tag + 3);
	pBaTimeoutVal = (u16 *)(tag + 5);
	pBaStartSeqCtrl = (जोड़ sequence_control *)(req + 7);

	RT_TRACE(COMP_DBG, "====>rx ADDBAREQ from : %pM\n", dst);
	अगर (!ieee->current_network.qos_data.active ||
	    !ieee->pHTInfo->bCurrentHTSupport ||
	    (ieee->pHTInfo->IOTAction & HT_IOT_ACT_REJECT_ADDBA_REQ)) अणु
		rc = ADDBA_STATUS_REFUSED;
		netdev_warn(ieee->dev,
			    "Failed to reply on ADDBA_REQ as some capability is not ready(%d, %d)\n",
			    ieee->current_network.qos_data.active,
			    ieee->pHTInfo->bCurrentHTSupport);
		जाओ OnADDBAReq_Fail;
	पूर्ण
	अगर (!GetTs(ieee, (काष्ठा ts_common_info **)(&pTS), dst,
	    (u8)(pBaParamSet->field.tid), RX_सूची, true)) अणु
		rc = ADDBA_STATUS_REFUSED;
		netdev_warn(ieee->dev, "%s(): can't get TS\n", __func__);
		जाओ OnADDBAReq_Fail;
	पूर्ण
	pBA = &pTS->rx_admitted_ba_record;

	अगर (pBaParamSet->field.ba_policy == BA_POLICY_DELAYED) अणु
		rc = ADDBA_STATUS_INVALID_PARAM;
		netdev_warn(ieee->dev, "%s(): BA Policy is not correct\n",
			    __func__);
		जाओ OnADDBAReq_Fail;
	पूर्ण

	rtllib_FlushRxTsPendingPkts(ieee, pTS);

	DeActivateBAEntry(ieee, pBA);
	pBA->dialog_token = *pDialogToken;
	pBA->ba_param_set = *pBaParamSet;
	pBA->ba_समयout_value = *pBaTimeoutVal;
	pBA->ba_start_seq_ctrl = *pBaStartSeqCtrl;

	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev) ||
	   (ieee->pHTInfo->IOTAction & HT_IOT_ACT_ALLOW_PEER_AGG_ONE_PKT))
		pBA->ba_param_set.field.buffer_size = 1;
	अन्यथा
		pBA->ba_param_set.field.buffer_size = 32;

	ActivateBAEntry(ieee, pBA, 0);
	rtllib_send_ADDBARsp(ieee, dst, pBA, ADDBA_STATUS_SUCCESS);

	वापस 0;

OnADDBAReq_Fail:
	अणु
		काष्ठा ba_record BA;

		BA.ba_param_set = *pBaParamSet;
		BA.ba_समयout_value = *pBaTimeoutVal;
		BA.dialog_token = *pDialogToken;
		BA.ba_param_set.field.ba_policy = BA_POLICY_IMMEDIATE;
		rtllib_send_ADDBARsp(ieee, dst, &BA, rc);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक rtllib_rx_ADDBARsp(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtllib_hdr_3addr *rsp = शून्य;
	काष्ठा ba_record *pPendingBA, *pAdmittedBA;
	काष्ठा tx_ts_record *pTS = शून्य;
	u8 *dst = शून्य, *pDialogToken = शून्य, *tag = शून्य;
	u16 *pStatusCode = शून्य, *pBaTimeoutVal = शून्य;
	जोड़ ba_param_set *pBaParamSet = शून्य;
	u16			ReasonCode;

	अगर (skb->len < माप(काष्ठा rtllib_hdr_3addr) + 9) अणु
		netdev_warn(ieee->dev, "Invalid skb len in BARSP(%d / %d)\n",
			    (पूर्णांक)skb->len,
			    (पूर्णांक)(माप(काष्ठा rtllib_hdr_3addr) + 9));
		वापस -1;
	पूर्ण
	rsp = (काष्ठा rtllib_hdr_3addr *)skb->data;
	tag = (u8 *)rsp;
	dst = (u8 *)(&rsp->addr2[0]);
	tag += माप(काष्ठा rtllib_hdr_3addr);
	pDialogToken = tag + 2;
	pStatusCode = (u16 *)(tag + 3);
	pBaParamSet = (जोड़ ba_param_set *)(tag + 5);
	pBaTimeoutVal = (u16 *)(tag + 7);

	RT_TRACE(COMP_DBG, "====>rx ADDBARSP from : %pM\n", dst);
	अगर (!ieee->current_network.qos_data.active ||
	    !ieee->pHTInfo->bCurrentHTSupport ||
	    !ieee->pHTInfo->bCurrentAMPDUEnable) अणु
		netdev_warn(ieee->dev,
			    "reject to ADDBA_RSP as some capability is not ready(%d, %d, %d)\n",
			    ieee->current_network.qos_data.active,
			    ieee->pHTInfo->bCurrentHTSupport,
			    ieee->pHTInfo->bCurrentAMPDUEnable);
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण


	अगर (!GetTs(ieee, (काष्ठा ts_common_info **)(&pTS), dst,
		   (u8)(pBaParamSet->field.tid), TX_सूची, false)) अणु
		netdev_warn(ieee->dev, "%s(): can't get TS\n", __func__);
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण

	pTS->bAddBaReqInProgress = false;
	pPendingBA = &pTS->TxPendingBARecord;
	pAdmittedBA = &pTS->TxAdmittedBARecord;


	अगर (pAdmittedBA->b_valid) अणु
		netdev_dbg(ieee->dev, "%s(): ADDBA response already admitted\n",
			   __func__);
		वापस -1;
	पूर्ण अन्यथा अगर (!pPendingBA->b_valid ||
		   (*pDialogToken != pPendingBA->dialog_token)) अणु
		netdev_warn(ieee->dev,
			    "%s(): ADDBA Rsp. BA invalid, DELBA!\n",
			    __func__);
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण अन्यथा अणु
		netdev_dbg(ieee->dev,
			   "%s(): Recv ADDBA Rsp. BA is admitted! Status code:%X\n",
			   __func__, *pStatusCode);
		DeActivateBAEntry(ieee, pPendingBA);
	पूर्ण


	अगर (*pStatusCode == ADDBA_STATUS_SUCCESS) अणु
		अगर (pBaParamSet->field.ba_policy == BA_POLICY_DELAYED) अणु
			pTS->bAddBaReqDelayed = true;
			DeActivateBAEntry(ieee, pAdmittedBA);
			ReasonCode = DELBA_REASON_END_BA;
			जाओ OnADDBARsp_Reject;
		पूर्ण


		pAdmittedBA->dialog_token = *pDialogToken;
		pAdmittedBA->ba_समयout_value = *pBaTimeoutVal;
		pAdmittedBA->ba_start_seq_ctrl = pPendingBA->ba_start_seq_ctrl;
		pAdmittedBA->ba_param_set = *pBaParamSet;
		DeActivateBAEntry(ieee, pAdmittedBA);
		ActivateBAEntry(ieee, pAdmittedBA, *pBaTimeoutVal);
	पूर्ण अन्यथा अणु
		pTS->bAddBaReqDelayed = true;
		pTS->bDisable_AddBa = true;
		ReasonCode = DELBA_REASON_END_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण

	वापस 0;

OnADDBARsp_Reject:
	अणु
		काष्ठा ba_record BA;

		BA.ba_param_set = *pBaParamSet;
		rtllib_send_DELBA(ieee, dst, &BA, TX_सूची, ReasonCode);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक rtllib_rx_DELBA(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtllib_hdr_3addr *delba = शून्य;
	जोड़ delba_param_set *pDelBaParamSet = शून्य;
	u8 *dst = शून्य;

	अगर (skb->len < माप(काष्ठा rtllib_hdr_3addr) + 6) अणु
		netdev_warn(ieee->dev, "Invalid skb len in DELBA(%d / %d)\n",
			    (पूर्णांक)skb->len,
			    (पूर्णांक)(माप(काष्ठा rtllib_hdr_3addr) + 6));
		वापस -1;
	पूर्ण

	अगर (!ieee->current_network.qos_data.active ||
		!ieee->pHTInfo->bCurrentHTSupport) अणु
		netdev_warn(ieee->dev,
			    "received DELBA while QOS or HT is not supported(%d, %d)\n",
			    ieee->current_network. qos_data.active,
			    ieee->pHTInfo->bCurrentHTSupport);
		वापस -1;
	पूर्ण

#अगर_घोषित VERBOSE_DEBUG
	prपूर्णांक_hex_dump_bytes("%s: ", DUMP_PREFIX_NONE, skb->data,
			     __func__, skb->len);
#पूर्ण_अगर
	delba = (काष्ठा rtllib_hdr_3addr *)skb->data;
	dst = (u8 *)(&delba->addr2[0]);
	pDelBaParamSet = (जोड़ delba_param_set *)&delba->payload[2];

	अगर (pDelBaParamSet->field.initiator == 1) अणु
		काष्ठा rx_ts_record *pRxTs;

		अगर (!GetTs(ieee, (काष्ठा ts_common_info **)&pRxTs, dst,
		    (u8)pDelBaParamSet->field.tid, RX_सूची, false)) अणु
			netdev_warn(ieee->dev,
				    "%s(): can't get TS for RXTS. dst:%pM TID:%d\n",
				    __func__, dst,
				    (u8)pDelBaParamSet->field.tid);
			वापस -1;
		पूर्ण

		RxTsDeleteBA(ieee, pRxTs);
	पूर्ण अन्यथा अणु
		काष्ठा tx_ts_record *pTxTs;

		अगर (!GetTs(ieee, (काष्ठा ts_common_info **)&pTxTs, dst,
			   (u8)pDelBaParamSet->field.tid, TX_सूची, false)) अणु
			netdev_warn(ieee->dev, "%s(): can't get TS for TXTS\n",
				    __func__);
			वापस -1;
		पूर्ण

		pTxTs->bUsingBa = false;
		pTxTs->bAddBaReqInProgress = false;
		pTxTs->bAddBaReqDelayed = false;
		del_समयr_sync(&pTxTs->TsAddBaTimer);
		TxTsDeleteBA(ieee, pTxTs);
	पूर्ण
	वापस 0;
पूर्ण

व्योम TsInitAddBA(काष्ठा rtllib_device *ieee, काष्ठा tx_ts_record *pTS,
		 u8 Policy, u8	bOverग_लिखोPending)
अणु
	काष्ठा ba_record *pBA = &pTS->TxPendingBARecord;

	अगर (pBA->b_valid && !bOverग_लिखोPending)
		वापस;

	DeActivateBAEntry(ieee, pBA);

	pBA->dialog_token++;
	pBA->ba_param_set.field.amsdu_support = 0;
	pBA->ba_param_set.field.ba_policy = Policy;
	pBA->ba_param_set.field.tid = pTS->TsCommonInfo.TSpec.f.TSInfo.field.ucTSID;
	pBA->ba_param_set.field.buffer_size = 32;
	pBA->ba_समयout_value = 0;
	pBA->ba_start_seq_ctrl.field.seq_num = (pTS->TxCurSeq + 3) % 4096;

	ActivateBAEntry(ieee, pBA, BA_SETUP_TIMEOUT);

	rtllib_send_ADDBAReq(ieee, pTS->TsCommonInfo.Addr, pBA);
पूर्ण

व्योम TsInitDelBA(काष्ठा rtllib_device *ieee,
		 काष्ठा ts_common_info *pTsCommonInfo,
		 क्रमागत tr_select TxRxSelect)
अणु
	अगर (TxRxSelect == TX_सूची) अणु
		काष्ठा tx_ts_record *pTxTs =
			 (काष्ठा tx_ts_record *)pTsCommonInfo;

		अगर (TxTsDeleteBA(ieee, pTxTs))
			rtllib_send_DELBA(ieee, pTsCommonInfo->Addr,
					  (pTxTs->TxAdmittedBARecord.b_valid) ?
					 (&pTxTs->TxAdmittedBARecord) :
					(&pTxTs->TxPendingBARecord),
					 TxRxSelect, DELBA_REASON_END_BA);
	पूर्ण अन्यथा अगर (TxRxSelect == RX_सूची) अणु
		काष्ठा rx_ts_record *pRxTs =
				 (काष्ठा rx_ts_record *)pTsCommonInfo;
		अगर (RxTsDeleteBA(ieee, pRxTs))
			rtllib_send_DELBA(ieee, pTsCommonInfo->Addr,
					  &pRxTs->rx_admitted_ba_record,
					  TxRxSelect, DELBA_REASON_END_BA);
	पूर्ण
पूर्ण

व्योम BaSetupTimeOut(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t,
					      TxPendingBARecord.समयr);

	pTxTs->bAddBaReqInProgress = false;
	pTxTs->bAddBaReqDelayed = true;
	pTxTs->TxPendingBARecord.b_valid = false;
पूर्ण

व्योम TxBaInactTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t,
					      TxAdmittedBARecord.समयr);
	काष्ठा rtllib_device *ieee = container_of(pTxTs, काष्ठा rtllib_device,
				     TxTsRecord[pTxTs->num]);
	TxTsDeleteBA(ieee, pTxTs);
	rtllib_send_DELBA(ieee, pTxTs->TsCommonInfo.Addr,
			  &pTxTs->TxAdmittedBARecord, TX_सूची,
			  DELBA_REASON_TIMEOUT);
पूर्ण

व्योम RxBaInactTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा rx_ts_record *pRxTs = from_समयr(pRxTs, t,
					      rx_admitted_ba_record.समयr);
	काष्ठा rtllib_device *ieee = container_of(pRxTs, काष्ठा rtllib_device,
				     RxTsRecord[pRxTs->num]);

	RxTsDeleteBA(ieee, pRxTs);
	rtllib_send_DELBA(ieee, pRxTs->ts_common_info.Addr,
			  &pRxTs->rx_admitted_ba_record, RX_सूची,
			  DELBA_REASON_TIMEOUT);
पूर्ण
