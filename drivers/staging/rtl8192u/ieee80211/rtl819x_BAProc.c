<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/********************************************************************************************************************************
 * This file is created to process BA Action Frame. According to 802.11 spec, there are 3 BA action types at all. And as BA is
 * related to TS, this part need some काष्ठाure defined in QOS side code. Also TX RX is going to be resturctured, so how to send
 * ADDBAREQ ADDBARSP and DELBA packet is still on consideration. Temporarily use MANAGE QUEUE instead of Normal Queue.
 * WB 2008-05-27
 * *****************************************************************************************************************************/
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ieee80211.h"
#समावेश "rtl819x_BA.h"

/********************************************************************************************************************
 *function:  Activate BA entry. And अगर Time is nozero, start समयr.
 *   input:  काष्ठा ba_record          *pBA  //BA entry to be enabled
 *	     u16			Time //indicate समय delay.
 *  output:  none
 ********************************************************************************************************************/
अटल व्योम ActivateBAEntry(काष्ठा ieee80211_device *ieee, काष्ठा ba_record *pBA, u16 Time)
अणु
	pBA->valid = true;
	अगर (Time != 0)
		mod_समयr(&pBA->समयr, jअगरfies + msecs_to_jअगरfies(Time));
पूर्ण

/********************************************************************************************************************
 *function:  deactivate BA entry, including its समयr.
 *   input:  काष्ठा ba_record       *pBA  //BA entry to be disabled
 *  output:  none
 ********************************************************************************************************************/
अटल व्योम DeActivateBAEntry(काष्ठा ieee80211_device *ieee, काष्ठा ba_record *pBA)
अणु
	pBA->valid = false;
	del_समयr_sync(&pBA->समयr);
पूर्ण
/********************************************************************************************************************
 *function: deactivete BA entry in Tx Ts, and send DELBA.
 *   input:
 *	     काष्ठा tx_ts_record *pTxTs //Tx Ts which is to deactivate BA entry.
 *  output:  none
 *  notice:  As काष्ठा tx_ts_record * काष्ठाure will be defined in QOS, so रुको to be merged. //FIXME
 ********************************************************************************************************************/
अटल u8 TxTsDeleteBA(काष्ठा ieee80211_device *ieee, काष्ठा tx_ts_record *pTxTs)
अणु
	काष्ठा ba_record *pAdmittedBa = &pTxTs->tx_admitted_ba_record;  //These two BA entries must exist in TS काष्ठाure
	काष्ठा ba_record *pPendingBa = &pTxTs->tx_pending_ba_record;
	u8			bSendDELBA = false;

	// Delete pending BA
	अगर (pPendingBa->valid) अणु
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	पूर्ण

	// Delete admitted BA
	अगर (pAdmittedBa->valid) अणु
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	पूर्ण

	वापस bSendDELBA;
पूर्ण

/********************************************************************************************************************
 *function: deactivete BA entry in Tx Ts, and send DELBA.
 *   input:
 *	     काष्ठा rx_ts_record  *pRxTs //Rx Ts which is to deactivate BA entry.
 *  output:  none
 *  notice:  As काष्ठा rx_ts_record * काष्ठाure will be defined in QOS, so रुको to be merged. //FIXME, same with above
 ********************************************************************************************************************/
अटल u8 RxTsDeleteBA(काष्ठा ieee80211_device *ieee, काष्ठा rx_ts_record *pRxTs)
अणु
	काष्ठा ba_record       *pBa = &pRxTs->rx_admitted_ba_record;
	u8			bSendDELBA = false;

	अगर (pBa->valid) अणु
		DeActivateBAEntry(ieee, pBa);
		bSendDELBA = true;
	पूर्ण

	वापस bSendDELBA;
पूर्ण

/********************************************************************************************************************
 *function: reset BA entry
 *   input:
 *	     काष्ठा ba_record *pBA //entry to be reset
 *  output:  none
 ********************************************************************************************************************/
व्योम ResetBaEntry(काष्ठा ba_record *pBA)
अणु
	pBA->valid			= false;
	pBA->param_set.लघु_data	= 0;
	pBA->समयout_value		= 0;
	pBA->dialog_token		= 0;
	pBA->start_seq_ctrl.लघु_data	= 0;
पूर्ण
//These functions need porting here or not?
/*******************************************************************************************************************************
 *function:  स्थिरruct ADDBAREQ and ADDBARSP frame here together.
 *   input:  u8*		Dst	//ADDBA frame's destination
 *	     काष्ठा ba_record  *pBA	//BA_RECORD entry which stores the necessary inक्रमmation क्रम BA.
 *	     u16		StatusCode  //status code in RSP and I will use it to indicate whether it's RSP or REQ(will I?)
 *	     u8			type	//indicate whether it's RSP(ACT_ADDBARSP) ow REQ(ACT_ADDBAREQ)
 *  output:  none
 *  वापस:  sk_buff*		skb     //वापस स्थिरructed skb to xmit
 *******************************************************************************************************************************/
अटल काष्ठा sk_buff *ieee80211_ADDBA(काष्ठा ieee80211_device *ieee, u8 *Dst, काष्ठा ba_record *pBA, u16 StatusCode, u8 type)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtl_80211_hdr_3addr *BAReq = शून्य;
	u8 *tag = शून्य;
	u16 len = ieee->tx_headroom + 9;
	//category(1) + action field(1) + Dialog Token(1) + BA Parameter Set(2) +  BA Timeout Value(2) +  BA Start SeqCtrl(2)(or StatusCode(2))
	IEEE80211_DEBUG(IEEE80211_DL_TRACE | IEEE80211_DL_BA, "========>%s(), frame(%d) sentd to:%pM, ieee->dev:%p\n", __func__, type, Dst, ieee->dev);
	अगर (pBA == शून्य) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "pBA is NULL\n");
		वापस शून्य;
	पूर्ण
	skb = dev_alloc_skb(len + माप(काष्ठा rtl_80211_hdr_3addr)); //need to add something others? FIXME
	अगर (!skb)
		वापस शून्य;

	स_रखो(skb->data, 0, माप(काष्ठा rtl_80211_hdr_3addr));	//I wonder whether it's necessary. Apparently kernel will not करो it when alloc a skb.
	skb_reserve(skb, ieee->tx_headroom);

	BAReq = skb_put(skb, माप(काष्ठा rtl_80211_hdr_3addr));

	स_नकल(BAReq->addr1, Dst, ETH_ALEN);
	स_नकल(BAReq->addr2, ieee->dev->dev_addr, ETH_ALEN);

	स_नकल(BAReq->addr3, ieee->current_network.bssid, ETH_ALEN);

	BAReq->frame_ctl = cpu_to_le16(IEEE80211_STYPE_MANAGE_ACT); //action frame

	//tag += माप( काष्ठा rtl_80211_hdr_3addr); //move to action field
	tag = skb_put(skb, 9);
	*tag++ = ACT_CAT_BA;
	*tag++ = type;
	// Dialog Token
	*tag++ = pBA->dialog_token;

	अगर (type == ACT_ADDBARSP) अणु
		// Status Code
		netdev_info(ieee->dev, "=====>to send ADDBARSP\n");

		put_unaligned_le16(StatusCode, tag);
		tag += 2;
	पूर्ण
	// BA Parameter Set

	put_unaligned_le16(pBA->param_set.लघु_data, tag);
	tag += 2;
	// BA Timeout Value

	put_unaligned_le16(pBA->समयout_value, tag);
	tag += 2;

	अगर (type == ACT_ADDBAREQ) अणु
	// BA Start SeqCtrl
		स_नकल(tag, (u8 *)&(pBA->start_seq_ctrl), 2);
		tag += 2;
	पूर्ण

	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_BA, skb->data, skb->len);
	वापस skb;
	//वापस शून्य;
पूर्ण


/********************************************************************************************************************
 *function:  स्थिरruct DELBA frame
 *   input:  u8*		dst	//DELBA frame's destination
 *	     काष्ठा ba_record  *pBA	//BA_RECORD entry which stores the necessary inक्रमmation क्रम BA
 *	     क्रमागत tr_select	TxRxSelect  //TX RX direction
 *	     u16		ReasonCode  //status code.
 *  output:  none
 *  वापस:  sk_buff*		skb     //वापस स्थिरructed skb to xmit
 ********************************************************************************************************************/
अटल काष्ठा sk_buff *ieee80211_DELBA(
	काष्ठा ieee80211_device  *ieee,
	u8		         *dst,
	काष्ठा ba_record         *pBA,
	क्रमागत tr_select		 TxRxSelect,
	u16			 ReasonCode
	)
अणु
	जोड़ delba_param_set	DelbaParamSet;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtl_80211_hdr_3addr *Delba = शून्य;
	u8 *tag = शून्य;
	//len = head len + DELBA Parameter Set(2) + Reason Code(2)
	u16 len = 6 + ieee->tx_headroom;

	अगर (net_ratelimit())
		IEEE80211_DEBUG(IEEE80211_DL_TRACE | IEEE80211_DL_BA,
				"========>%s(), ReasonCode(%d) sentd to:%pM\n",
				__func__, ReasonCode, dst);

	स_रखो(&DelbaParamSet, 0, 2);

	DelbaParamSet.field.initiator	= (TxRxSelect == TX_सूची) ? 1 : 0;
	DelbaParamSet.field.tid	= pBA->param_set.field.tid;

	skb = dev_alloc_skb(len + माप(काष्ठा rtl_80211_hdr_3addr)); //need to add something others? FIXME
	अगर (!skb)
		वापस शून्य;
//	स_रखो(skb->data, 0, len+माप( काष्ठा rtl_80211_hdr_3addr));
	skb_reserve(skb, ieee->tx_headroom);

	Delba = skb_put(skb, माप(काष्ठा rtl_80211_hdr_3addr));

	स_नकल(Delba->addr1, dst, ETH_ALEN);
	स_नकल(Delba->addr2, ieee->dev->dev_addr, ETH_ALEN);
	स_नकल(Delba->addr3, ieee->current_network.bssid, ETH_ALEN);
	Delba->frame_ctl = cpu_to_le16(IEEE80211_STYPE_MANAGE_ACT); //action frame

	tag = skb_put(skb, 6);

	*tag++ = ACT_CAT_BA;
	*tag++ = ACT_DELBA;

	// DELBA Parameter Set

	put_unaligned_le16(DelbaParamSet.लघु_data, tag);
	tag += 2;
	// Reason Code

	put_unaligned_le16(ReasonCode, tag);
	tag += 2;

	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_BA, skb->data, skb->len);
	अगर (net_ratelimit())
		IEEE80211_DEBUG(IEEE80211_DL_TRACE | IEEE80211_DL_BA,
				"<=====%s()\n", __func__);
	वापस skb;
पूर्ण

/********************************************************************************************************************
 *function: send ADDBAReq frame out
 *   input:  u8*		dst	//ADDBAReq frame's destination
 *	     काष्ठा ba_record  *pBA	//BA_RECORD entry which stores the necessary inक्रमmation क्रम BA
 *  output:  none
 *  notice: If any possible, please hide pBA in ieee. And temporarily use Manage Queue as sofपंचांगac_mgmt_xmit() usually करोes
 ********************************************************************************************************************/
अटल व्योम ieee80211_send_ADDBAReq(काष्ठा ieee80211_device *ieee,
				    u8 *dst, काष्ठा ba_record *pBA)
अणु
	काष्ठा sk_buff *skb;
	skb = ieee80211_ADDBA(ieee, dst, pBA, 0, ACT_ADDBAREQ); //स्थिरruct ACT_ADDBAREQ frames so set statuscode zero.

	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		//add statistic needed here.
		//and skb will be मुक्तd in sofपंचांगac_mgmt_xmit(), so omit all dev_kमुक्त_skb_any() outside sofपंचांगac_mgmt_xmit()
		//WB
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "alloc skb error in function %s()\n", __func__);
	पूर्ण
पूर्ण

/********************************************************************************************************************
 *function: send ADDBARSP frame out
 *   input:  u8*		dst	//DELBA frame's destination
 *	     काष्ठा ba_record  *pBA	//BA_RECORD entry which stores the necessary inक्रमmation क्रम BA
 *	     u16		StatusCode //RSP StatusCode
 *  output:  none
 *  notice: If any possible, please hide pBA in ieee. And temporarily use Manage Queue as sofपंचांगac_mgmt_xmit() usually करोes
 ********************************************************************************************************************/
अटल व्योम ieee80211_send_ADDBARsp(काष्ठा ieee80211_device *ieee, u8 *dst,
				    काष्ठा ba_record *pBA, u16 StatusCode)
अणु
	काष्ठा sk_buff *skb;
	skb = ieee80211_ADDBA(ieee, dst, pBA, StatusCode, ACT_ADDBARSP); //स्थिरruct ACT_ADDBARSP frames
	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		//same above
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "alloc skb error in function %s()\n", __func__);
	पूर्ण

	वापस;

पूर्ण
/********************************************************************************************************************
 *function: send ADDBARSP frame out
 *   input:  u8*		dst	//DELBA frame's destination
 *	     काष्ठा ba_record  *pBA	//BA_RECORD entry which stores the necessary inक्रमmation क्रम BA
 *	     क्रमागत tr_select     TxRxSelect //TX or RX
 *	     u16		ReasonCode //DEL ReasonCode
 *  output:  none
 *  notice: If any possible, please hide pBA in ieee. And temporarily use Manage Queue as sofपंचांगac_mgmt_xmit() usually करोes
 ********************************************************************************************************************/

अटल व्योम ieee80211_send_DELBA(काष्ठा ieee80211_device *ieee, u8 *dst,
				 काष्ठा ba_record *pBA, क्रमागत tr_select TxRxSelect,
				 u16 ReasonCode)
अणु
	काष्ठा sk_buff *skb;
	skb = ieee80211_DELBA(ieee, dst, pBA, TxRxSelect, ReasonCode); //स्थिरruct ACT_ADDBARSP frames
	अगर (skb) अणु
		sofपंचांगac_mgmt_xmit(skb, ieee);
		//same above
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "alloc skb error in function %s()\n", __func__);
	पूर्ण
पूर्ण

/********************************************************************************************************************
 *function: RX ADDBAReq
 *   input:  काष्ठा sk_buff *   skb	//incoming ADDBAReq skb.
 *  वापस:  0(pass), other(fail)
 *  notice:  As this function need support of QOS, I comment some code out. And when qos is पढ़ोy, this code need to be support.
 ********************************************************************************************************************/
पूर्णांक ieee80211_rx_ADDBAReq(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_80211_hdr_3addr *req = शून्य;
	u16 rc = 0;
	u8 *dst = शून्य, *pDialogToken = शून्य, *tag = शून्य;
	काष्ठा ba_record *pBA = शून्य;
	जोड़ ba_param_set     *pBaParamSet = शून्य;
	u16 *pBaTimeoutVal = शून्य;
	जोड़ sequence_control *pBaStartSeqCtrl = शून्य;
	काष्ठा rx_ts_record  *pTS = शून्य;

	अगर (skb->len < माप(काष्ठा rtl_80211_hdr_3addr) + 9) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				" Invalid skb len in BAREQ(%d / %zu)\n",
				skb->len,
				(माप(काष्ठा rtl_80211_hdr_3addr) + 9));
		वापस -1;
	पूर्ण

	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_BA, skb->data, skb->len);

	req = (काष्ठा rtl_80211_hdr_3addr *)skb->data;
	tag = (u8 *)req;
	dst = &req->addr2[0];
	tag += माप(काष्ठा rtl_80211_hdr_3addr);
	pDialogToken = tag + 2;  //category+action
	pBaParamSet = (जोड़ ba_param_set *)(tag + 3);   //+DialogToken
	pBaTimeoutVal = (u16 *)(tag + 5);
	pBaStartSeqCtrl = (जोड़ sequence_control *)(req + 7);

	netdev_info(ieee->dev, "====================>rx ADDBAREQ from :%pM\n", dst);
//some other capability is not पढ़ोy now.
	अगर ((ieee->current_network.qos_data.active == 0) ||
		(!ieee->pHTInfo->bCurrentHTSupport)) //||
	//	(!ieee->pStaQos->bEnableRxImmBA)	)
	अणु
		rc = ADDBA_STATUS_REFUSED;
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "Failed to reply on ADDBA_REQ as some capability is not ready(%d, %d)\n", ieee->current_network.qos_data.active, ieee->pHTInfo->bCurrentHTSupport);
		जाओ OnADDBAReq_Fail;
	पूर्ण
	// Search क्रम related traffic stream.
	// If there is no matched TS, reject the ADDBA request.
	अगर (!GetTs(
			ieee,
			(काष्ठा ts_common_info **)(&pTS),
			dst,
			(u8)(pBaParamSet->field.tid),
			RX_सूची,
			true)) अणु
		rc = ADDBA_STATUS_REFUSED;
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "can't get TS in %s()\n", __func__);
		जाओ OnADDBAReq_Fail;
	पूर्ण
	pBA = &pTS->rx_admitted_ba_record;
	// To Determine the ADDBA Req content
	// We can करो much more check here, including buffer_size, AMSDU_Support, Policy, StartSeqCtrl...
	// I want to check StartSeqCtrl to make sure when we start aggregation!!!
	//
	अगर (pBaParamSet->field.ba_policy == BA_POLICY_DELAYED) अणु
		rc = ADDBA_STATUS_INVALID_PARAM;
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "BA Policy is not correct in %s()\n", __func__);
		जाओ OnADDBAReq_Fail;
	पूर्ण
		// Admit the ADDBA Request
	//
	DeActivateBAEntry(ieee, pBA);
	pBA->dialog_token = *pDialogToken;
	pBA->param_set = *pBaParamSet;
	pBA->समयout_value = *pBaTimeoutVal;
	pBA->start_seq_ctrl = *pBaStartSeqCtrl;
	//क्रम half N mode we only aggregate 1 frame
	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pBA->param_set.field.buffer_size = 1;
	अन्यथा
		pBA->param_set.field.buffer_size = 32;
	ActivateBAEntry(ieee, pBA, pBA->समयout_value);
	ieee80211_send_ADDBARsp(ieee, dst, pBA, ADDBA_STATUS_SUCCESS);

	// End of procedure.
	वापस 0;

OnADDBAReq_Fail:
	अणु
		काष्ठा ba_record	BA;
		BA.param_set = *pBaParamSet;
		BA.समयout_value = *pBaTimeoutVal;
		BA.dialog_token = *pDialogToken;
		BA.param_set.field.ba_policy = BA_POLICY_IMMEDIATE;
		ieee80211_send_ADDBARsp(ieee, dst, &BA, rc);
		वापस 0; //we send RSP out.
	पूर्ण

पूर्ण

/********************************************************************************************************************
 *function: RX ADDBARSP
 *   input:  काष्ठा sk_buff *   skb	//incoming ADDBAReq skb.
 *  वापस:  0(pass), other(fail)
 *  notice:  As this function need support of QOS, I comment some code out. And when qos is पढ़ोy, this code need to be support.
 ********************************************************************************************************************/
पूर्णांक ieee80211_rx_ADDBARsp(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_80211_hdr_3addr *rsp = शून्य;
	काष्ठा ba_record        *pPendingBA, *pAdmittedBA;
	काष्ठा tx_ts_record     *pTS = शून्य;
	u8 *dst = शून्य, *pDialogToken = शून्य, *tag = शून्य;
	u16 *pStatusCode = शून्य, *pBaTimeoutVal = शून्य;
	जोड़ ba_param_set       *pBaParamSet = शून्य;
	u16			ReasonCode;

	अगर (skb->len < माप(काष्ठा rtl_80211_hdr_3addr) + 9) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				" Invalid skb len in BARSP(%d / %zu)\n",
				skb->len,
				(माप(काष्ठा rtl_80211_hdr_3addr) + 9));
		वापस -1;
	पूर्ण
	rsp = (काष्ठा rtl_80211_hdr_3addr *)skb->data;
	tag = (u8 *)rsp;
	dst = &rsp->addr2[0];
	tag += माप(काष्ठा rtl_80211_hdr_3addr);
	pDialogToken = tag + 2;
	pStatusCode = (u16 *)(tag + 3);
	pBaParamSet = (जोड़ ba_param_set *)(tag + 5);
	pBaTimeoutVal = (u16 *)(tag + 7);

	// Check the capability
	// Since we can always receive A-MPDU, we just check अगर it is under HT mode.
	अगर (ieee->current_network.qos_data.active == 0  ||
	    !ieee->pHTInfo->bCurrentHTSupport ||
	    !ieee->pHTInfo->bCurrentAMPDUEnable) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "reject to ADDBA_RSP as some capability is not ready(%d, %d, %d)\n", ieee->current_network.qos_data.active, ieee->pHTInfo->bCurrentHTSupport, ieee->pHTInfo->bCurrentAMPDUEnable);
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण


	//
	// Search क्रम related TS.
	// If there is no TS found, we wil reject ADDBA Rsp by sending DELBA frame.
	//
	अगर (!GetTs(
			ieee,
			(काष्ठा ts_common_info **)(&pTS),
			dst,
			(u8)(pBaParamSet->field.tid),
			TX_सूची,
			false)) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "can't get TS in %s()\n", __func__);
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण

	pTS->add_ba_req_in_progress = false;
	pPendingBA = &pTS->tx_pending_ba_record;
	pAdmittedBA = &pTS->tx_admitted_ba_record;


	//
	// Check अगर related BA is रुकोing क्रम setup.
	// If not, reject by sending DELBA frame.
	//
	अगर (pAdmittedBA->valid) अणु
		// Since BA is alपढ़ोy setup, we ignore all other ADDBA Response.
		IEEE80211_DEBUG(IEEE80211_DL_BA, "OnADDBARsp(): Recv ADDBA Rsp. Drop because already admit it! \n");
		वापस -1;
	पूर्ण अन्यथा अगर ((!pPendingBA->valid) || (*pDialogToken != pPendingBA->dialog_token)) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,  "OnADDBARsp(): Recv ADDBA Rsp. BA invalid, DELBA! \n");
		ReasonCode = DELBA_REASON_UNKNOWN_BA;
		जाओ OnADDBARsp_Reject;
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_BA, "OnADDBARsp(): Recv ADDBA Rsp. BA is admitted! Status code:%X\n", *pStatusCode);
		DeActivateBAEntry(ieee, pPendingBA);
	पूर्ण


	अगर (*pStatusCode == ADDBA_STATUS_SUCCESS) अणु
		//
		// Determine ADDBA Rsp content here.
		// We can compare the value of BA parameter set that Peer वापसed and Self sent.
		// If it is OK, then admitted. Or we can send DELBA to cancel BA mechanism.
		//
		अगर (pBaParamSet->field.ba_policy == BA_POLICY_DELAYED) अणु
			// Since this is a kind of ADDBA failed, we delay next ADDBA process.
			pTS->add_ba_req_delayed = true;
			DeActivateBAEntry(ieee, pAdmittedBA);
			ReasonCode = DELBA_REASON_END_BA;
			जाओ OnADDBARsp_Reject;
		पूर्ण


		//
		// Admitted condition
		//
		pAdmittedBA->dialog_token = *pDialogToken;
		pAdmittedBA->समयout_value = *pBaTimeoutVal;
		pAdmittedBA->start_seq_ctrl = pPendingBA->start_seq_ctrl;
		pAdmittedBA->param_set = *pBaParamSet;
		DeActivateBAEntry(ieee, pAdmittedBA);
		ActivateBAEntry(ieee, pAdmittedBA, *pBaTimeoutVal);
	पूर्ण अन्यथा अणु
		// Delay next ADDBA process.
		pTS->add_ba_req_delayed = true;
	पूर्ण

	// End of procedure
	वापस 0;

OnADDBARsp_Reject:
	अणु
		काष्ठा ba_record	BA;
		BA.param_set = *pBaParamSet;
		ieee80211_send_DELBA(ieee, dst, &BA, TX_सूची, ReasonCode);
		वापस 0;
	पूर्ण

पूर्ण

/********************************************************************************************************************
 *function: RX DELBA
 *   input:  काष्ठा sk_buff *   skb	//incoming ADDBAReq skb.
 *  वापस:  0(pass), other(fail)
 *  notice:  As this function need support of QOS, I comment some code out. And when qos is पढ़ोy, this code need to be support.
 ********************************************************************************************************************/
पूर्णांक ieee80211_rx_DELBA(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_80211_hdr_3addr *delba = शून्य;
	जोड़ delba_param_set   *pDelBaParamSet = शून्य;
	u8			*dst = शून्य;

	अगर (skb->len < माप(काष्ठा rtl_80211_hdr_3addr) + 6) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				" Invalid skb len in DELBA(%d / %zu)\n",
				skb->len,
				(माप(काष्ठा rtl_80211_hdr_3addr) + 6));
		वापस -1;
	पूर्ण

	अगर (ieee->current_network.qos_data.active == 0 ||
	    !ieee->pHTInfo->bCurrentHTSupport) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "received DELBA while QOS or HT is not supported(%d, %d)\n", ieee->current_network.qos_data.active, ieee->pHTInfo->bCurrentHTSupport);
		वापस -1;
	पूर्ण

	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_BA, skb->data, skb->len);
	delba = (काष्ठा rtl_80211_hdr_3addr *)skb->data;
	dst = &delba->addr2[0];
	pDelBaParamSet = (जोड़ delba_param_set *)&delba->payload[2];

	अगर (pDelBaParamSet->field.initiator == 1) अणु
		काष्ठा rx_ts_record *pRxTs;

		अगर (!GetTs(
				ieee,
				(काष्ठा ts_common_info **)&pRxTs,
				dst,
				(u8)pDelBaParamSet->field.tid,
				RX_सूची,
				false)) अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR,  "can't get TS for RXTS in %s()\n", __func__);
			वापस -1;
		पूर्ण

		RxTsDeleteBA(ieee, pRxTs);
	पूर्ण अन्यथा अणु
		काष्ठा tx_ts_record *pTxTs;

		अगर (!GetTs(
			ieee,
			(काष्ठा ts_common_info **)&pTxTs,
			dst,
			(u8)pDelBaParamSet->field.tid,
			TX_सूची,
			false)) अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR,  "can't get TS for TXTS in %s()\n", __func__);
			वापस -1;
		पूर्ण

		pTxTs->using_ba = false;
		pTxTs->add_ba_req_in_progress = false;
		pTxTs->add_ba_req_delayed = false;
		del_समयr_sync(&pTxTs->ts_add_ba_समयr);
		//Platक्रमmCancelTimer(Adapter, &pTxTs->ts_add_ba_समयr);
		TxTsDeleteBA(ieee, pTxTs);
	पूर्ण
	वापस 0;
पूर्ण

//
// ADDBA initiate. This can only be called by TX side.
//
व्योम
TsInitAddBA(
	काष्ठा ieee80211_device *ieee,
	काष्ठा tx_ts_record     *pTS,
	u8		Policy,
	u8		bOverग_लिखोPending
	)
अणु
	काष्ठा ba_record *pBA = &pTS->tx_pending_ba_record;

	अगर (pBA->valid && !bOverग_लिखोPending)
		वापस;

	// Set parameters to "Pending" variable set
	DeActivateBAEntry(ieee, pBA);

	pBA->dialog_token++;						// DialogToken: Only keep the latest dialog token
	pBA->param_set.field.amsdu_support = 0;	// Do not support A-MSDU with A-MPDU now!!
	pBA->param_set.field.ba_policy = Policy;	// Policy: Delayed or Immediate
	pBA->param_set.field.tid = pTS->ts_common_info.t_spec.ts_info.uc_tsid;	// TID
	// buffer_size: This need to be set according to A-MPDU vector
	pBA->param_set.field.buffer_size = 32;		// buffer_size: This need to be set according to A-MPDU vector
	pBA->समयout_value = 0;					// Timeout value: Set 0 to disable Timer
	pBA->start_seq_ctrl.field.seq_num = (pTS->tx_cur_seq + 3) % 4096;	// Block Ack will start after 3 packets later.

	ActivateBAEntry(ieee, pBA, BA_SETUP_TIMEOUT);

	ieee80211_send_ADDBAReq(ieee, pTS->ts_common_info.addr, pBA);
पूर्ण

व्योम
TsInitDelBA(काष्ठा ieee80211_device *ieee, काष्ठा ts_common_info *pTsCommonInfo, क्रमागत tr_select TxRxSelect)
अणु
	अगर (TxRxSelect == TX_सूची) अणु
		काष्ठा tx_ts_record *pTxTs = (काष्ठा tx_ts_record *)pTsCommonInfo;

		अगर (TxTsDeleteBA(ieee, pTxTs))
			ieee80211_send_DELBA(
				ieee,
				pTsCommonInfo->addr,
				(pTxTs->tx_admitted_ba_record.valid) ? (&pTxTs->tx_admitted_ba_record) : (&pTxTs->tx_pending_ba_record),
				TxRxSelect,
				DELBA_REASON_END_BA);
	पूर्ण अन्यथा अगर (TxRxSelect == RX_सूची) अणु
		काष्ठा rx_ts_record *pRxTs = (काष्ठा rx_ts_record *)pTsCommonInfo;
		अगर (RxTsDeleteBA(ieee, pRxTs))
			ieee80211_send_DELBA(
				ieee,
				pTsCommonInfo->addr,
				&pRxTs->rx_admitted_ba_record,
				TxRxSelect,
				DELBA_REASON_END_BA);
	पूर्ण
पूर्ण
/********************************************************************************************************************
 *function:  BA setup समयr
 *   input:  अचिन्हित दीर्घ	 data		//acturally we send काष्ठा tx_ts_record or काष्ठा rx_ts_record to these समयr
 *  वापस:  शून्य
 *  notice:
 ********************************************************************************************************************/
व्योम BaSetupTimeOut(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t, tx_pending_ba_record.समयr);

	pTxTs->add_ba_req_in_progress = false;
	pTxTs->add_ba_req_delayed = true;
	pTxTs->tx_pending_ba_record.valid = false;
पूर्ण

व्योम TxBaInactTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t, tx_admitted_ba_record.समयr);
	काष्ठा ieee80211_device *ieee = container_of(pTxTs, काष्ठा ieee80211_device, TxTsRecord[pTxTs->num]);
	TxTsDeleteBA(ieee, pTxTs);
	ieee80211_send_DELBA(
		ieee,
		pTxTs->ts_common_info.addr,
		&pTxTs->tx_admitted_ba_record,
		TX_सूची,
		DELBA_REASON_TIMEOUT);
पूर्ण

व्योम RxBaInactTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा rx_ts_record *pRxTs = from_समयr(pRxTs, t, rx_admitted_ba_record.समयr);
	काष्ठा ieee80211_device *ieee = container_of(pRxTs, काष्ठा ieee80211_device, RxTsRecord[pRxTs->num]);

	RxTsDeleteBA(ieee, pRxTs);
	ieee80211_send_DELBA(
		ieee,
		pRxTs->ts_common_info.addr,
		&pRxTs->rx_admitted_ba_record,
		RX_सूची,
		DELBA_REASON_TIMEOUT);
पूर्ण
