<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtllib.h"
#समावेश <linux/etherdevice.h>
#समावेश "rtl819x_TS.h"

अटल व्योम TsSetupTimeOut(काष्ठा समयr_list *unused)
अणु
पूर्ण

अटल व्योम TsInactTimeout(काष्ठा समयr_list *unused)
अणु
पूर्ण

अटल व्योम RxPktPendingTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा rx_ts_record *pRxTs = from_समयr(pRxTs, t,
						     rx_pkt_pending_समयr);
	काष्ठा rtllib_device *ieee = container_of(pRxTs, काष्ठा rtllib_device,
						  RxTsRecord[pRxTs->num]);

	काष्ठा rx_reorder_entry *pReorderEntry = शून्य;

	अचिन्हित दीर्घ flags = 0;
	u8 index = 0;
	bool bPktInBuf = false;

	spin_lock_irqsave(&(ieee->reorder_spinlock), flags);
	अगर (pRxTs->rx_समयout_indicate_seq != 0xffff) अणु
		जबतक (!list_empty(&pRxTs->rx_pending_pkt_list)) अणु
			pReorderEntry = (काष्ठा rx_reorder_entry *)
					list_entry(pRxTs->rx_pending_pkt_list.prev,
					काष्ठा rx_reorder_entry, List);
			अगर (index == 0)
				pRxTs->rx_indicate_seq = pReorderEntry->SeqNum;

			अगर (SN_LESS(pReorderEntry->SeqNum,
				    pRxTs->rx_indicate_seq) ||
			    SN_EQUAL(pReorderEntry->SeqNum,
				     pRxTs->rx_indicate_seq)) अणु
				list_del_init(&pReorderEntry->List);

				अगर (SN_EQUAL(pReorderEntry->SeqNum,
				    pRxTs->rx_indicate_seq))
					pRxTs->rx_indicate_seq =
					      (pRxTs->rx_indicate_seq + 1) % 4096;

				netdev_dbg(ieee->dev,
					   "%s(): Indicate SeqNum: %d\n",
					   __func__, pReorderEntry->SeqNum);
				ieee->stats_IndicateArray[index] =
							 pReorderEntry->prxb;
				index++;

				list_add_tail(&pReorderEntry->List,
					      &ieee->RxReorder_Unused_List);
			पूर्ण अन्यथा अणु
				bPktInBuf = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (index > 0) अणु
		pRxTs->rx_समयout_indicate_seq = 0xffff;

		अगर (index > REORDER_WIN_SIZE) अणु
			netdev_warn(ieee->dev,
				    "%s(): Rx Reorder struct buffer full\n",
				    __func__);
			spin_unlock_irqrestore(&(ieee->reorder_spinlock),
					       flags);
			वापस;
		पूर्ण
		rtllib_indicate_packets(ieee, ieee->stats_IndicateArray, index);
		bPktInBuf = false;
	पूर्ण

	अगर (bPktInBuf && (pRxTs->rx_समयout_indicate_seq == 0xffff)) अणु
		pRxTs->rx_समयout_indicate_seq = pRxTs->rx_indicate_seq;
		mod_समयr(&pRxTs->rx_pkt_pending_समयr,  jअगरfies +
			  msecs_to_jअगरfies(ieee->pHTInfo->RxReorderPendingTime)
			  );
	पूर्ण
	spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
पूर्ण

अटल व्योम TsAddBaProcess(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t, TsAddBaTimer);
	u8 num = pTxTs->num;
	काष्ठा rtllib_device *ieee = container_of(pTxTs, काष्ठा rtllib_device,
				     TxTsRecord[num]);

	TsInitAddBA(ieee, pTxTs, BA_POLICY_IMMEDIATE, false);
	netdev_dbg(ieee->dev, "%s(): ADDBA Req is started\n", __func__);
पूर्ण

अटल व्योम ResetTsCommonInfo(काष्ठा ts_common_info *pTsCommonInfo)
अणु
	eth_zero_addr(pTsCommonInfo->Addr);
	स_रखो(&pTsCommonInfo->TSpec, 0, माप(जोड़ tspec_body));
	स_रखो(&pTsCommonInfo->TClass, 0, माप(जोड़ qos_tclas) * TCLAS_NUM);
	pTsCommonInfo->TClasProc = 0;
	pTsCommonInfo->TClasNum = 0;
पूर्ण

अटल व्योम ResetTxTsEntry(काष्ठा tx_ts_record *pTS)
अणु
	ResetTsCommonInfo(&pTS->TsCommonInfo);
	pTS->TxCurSeq = 0;
	pTS->bAddBaReqInProgress = false;
	pTS->bAddBaReqDelayed = false;
	pTS->bUsingBa = false;
	pTS->bDisable_AddBa = false;
	ResetBaEntry(&pTS->TxAdmittedBARecord);
	ResetBaEntry(&pTS->TxPendingBARecord);
पूर्ण

अटल व्योम ResetRxTsEntry(काष्ठा rx_ts_record *pTS)
अणु
	ResetTsCommonInfo(&pTS->ts_common_info);
	pTS->rx_indicate_seq = 0xffff;
	pTS->rx_समयout_indicate_seq = 0xffff;
	ResetBaEntry(&pTS->rx_admitted_ba_record);
पूर्ण

व्योम TSInitialize(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा tx_ts_record *pTxTS  = ieee->TxTsRecord;
	काष्ठा rx_ts_record *pRxTS  = ieee->RxTsRecord;
	काष्ठा rx_reorder_entry *pRxReorderEntry = ieee->RxReorderEntry;
	u8				count = 0;

	INIT_LIST_HEAD(&ieee->Tx_TS_Admit_List);
	INIT_LIST_HEAD(&ieee->Tx_TS_Pending_List);
	INIT_LIST_HEAD(&ieee->Tx_TS_Unused_List);

	क्रम (count = 0; count < TOTAL_TS_NUM; count++) अणु
		pTxTS->num = count;
		समयr_setup(&pTxTS->TsCommonInfo.SetupTimer, TsSetupTimeOut,
			    0);

		समयr_setup(&pTxTS->TsCommonInfo.InactTimer, TsInactTimeout,
			    0);

		समयr_setup(&pTxTS->TsAddBaTimer, TsAddBaProcess, 0);

		समयr_setup(&pTxTS->TxPendingBARecord.समयr, BaSetupTimeOut,
			    0);
		समयr_setup(&pTxTS->TxAdmittedBARecord.समयr,
			    TxBaInactTimeout, 0);

		ResetTxTsEntry(pTxTS);
		list_add_tail(&pTxTS->TsCommonInfo.List,
				&ieee->Tx_TS_Unused_List);
		pTxTS++;
	पूर्ण

	INIT_LIST_HEAD(&ieee->Rx_TS_Admit_List);
	INIT_LIST_HEAD(&ieee->Rx_TS_Pending_List);
	INIT_LIST_HEAD(&ieee->Rx_TS_Unused_List);
	क्रम (count = 0; count < TOTAL_TS_NUM; count++) अणु
		pRxTS->num = count;
		INIT_LIST_HEAD(&pRxTS->rx_pending_pkt_list);

		समयr_setup(&pRxTS->ts_common_info.SetupTimer, TsSetupTimeOut,
			    0);

		समयr_setup(&pRxTS->ts_common_info.InactTimer, TsInactTimeout,
			    0);

		समयr_setup(&pRxTS->rx_admitted_ba_record.समयr,
			    RxBaInactTimeout, 0);

		समयr_setup(&pRxTS->rx_pkt_pending_समयr, RxPktPendingTimeout, 0);

		ResetRxTsEntry(pRxTS);
		list_add_tail(&pRxTS->ts_common_info.List,
			      &ieee->Rx_TS_Unused_List);
		pRxTS++;
	पूर्ण
	INIT_LIST_HEAD(&ieee->RxReorder_Unused_List);
	क्रम (count = 0; count < REORDER_ENTRY_NUM; count++) अणु
		list_add_tail(&pRxReorderEntry->List,
			      &ieee->RxReorder_Unused_List);
		अगर (count == (REORDER_ENTRY_NUM - 1))
			अवरोध;
		pRxReorderEntry = &ieee->RxReorderEntry[count + 1];
	पूर्ण
पूर्ण

अटल व्योम AdmitTS(काष्ठा rtllib_device *ieee,
		    काष्ठा ts_common_info *pTsCommonInfo, u32 InactTime)
अणु
	del_समयr_sync(&pTsCommonInfo->SetupTimer);
	del_समयr_sync(&pTsCommonInfo->InactTimer);

	अगर (InactTime != 0)
		mod_समयr(&pTsCommonInfo->InactTimer, jअगरfies +
			  msecs_to_jअगरfies(InactTime));
पूर्ण

अटल काष्ठा ts_common_info *SearchAdmitTRStream(काष्ठा rtllib_device *ieee,
						  u8 *Addr, u8 TID,
						  क्रमागत tr_select TxRxSelect)
अणु
	u8	dir;
	bool	search_dir[4] = अणु0पूर्ण;
	काष्ठा list_head *psearch_list;
	काष्ठा ts_common_info *pRet = शून्य;

	अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		अगर (TxRxSelect == TX_सूची) अणु
			search_dir[सूची_DOWN] = true;
			search_dir[सूची_BI_सूची] = true;
		पूर्ण अन्यथा अणु
			search_dir[सूची_UP] = true;
			search_dir[सूची_BI_सूची] = true;
		पूर्ण
	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (TxRxSelect == TX_सूची)
			search_dir[सूची_UP] = true;
		अन्यथा
			search_dir[सूची_DOWN] = true;
	पूर्ण अन्यथा अणु
		अगर (TxRxSelect == TX_सूची) अणु
			search_dir[सूची_UP] = true;
			search_dir[सूची_BI_सूची] = true;
			search_dir[सूची_सूचीECT] = true;
		पूर्ण अन्यथा अणु
			search_dir[सूची_DOWN] = true;
			search_dir[सूची_BI_सूची] = true;
			search_dir[सूची_सूचीECT] = true;
		पूर्ण
	पूर्ण

	अगर (TxRxSelect == TX_सूची)
		psearch_list = &ieee->Tx_TS_Admit_List;
	अन्यथा
		psearch_list = &ieee->Rx_TS_Admit_List;

	क्रम (dir = 0; dir <= सूची_BI_सूची; dir++) अणु
		अगर (!search_dir[dir])
			जारी;
		list_क्रम_each_entry(pRet, psearch_list, List) अणु
			अगर (स_भेद(pRet->Addr, Addr, 6) == 0 &&
			    pRet->TSpec.f.TSInfo.field.ucTSID == TID &&
			    pRet->TSpec.f.TSInfo.field.ucDirection == dir)
				अवरोध;
		पूर्ण
		अगर (&pRet->List  != psearch_list)
			अवरोध;
	पूर्ण

	अगर (pRet && &pRet->List  != psearch_list)
		वापस pRet;
	वापस शून्य;
पूर्ण

अटल व्योम MakeTSEntry(काष्ठा ts_common_info *pTsCommonInfo, u8 *Addr,
			जोड़ tspec_body *pTSPEC, जोड़ qos_tclas *pTCLAS,
			u8 TCLAS_Num, u8 TCLAS_Proc)
अणु
	u8	count;

	अगर (!pTsCommonInfo)
		वापस;

	स_नकल(pTsCommonInfo->Addr, Addr, 6);

	अगर (pTSPEC)
		स_नकल((u8 *)(&(pTsCommonInfo->TSpec)), (u8 *)pTSPEC,
			माप(जोड़ tspec_body));

	क्रम (count = 0; count < TCLAS_Num; count++)
		स_नकल((u8 *)(&(pTsCommonInfo->TClass[count])),
		       (u8 *)pTCLAS, माप(जोड़ qos_tclas));

	pTsCommonInfo->TClasProc = TCLAS_Proc;
	pTsCommonInfo->TClasNum = TCLAS_Num;
पूर्ण

bool GetTs(काष्ठा rtllib_device *ieee, काष्ठा ts_common_info **ppTS,
	   u8 *Addr, u8 TID, क्रमागत tr_select TxRxSelect, bool bAddNewTs)
अणु
	u8	UP = 0;
	जोड़ tspec_body TSpec;
	जोड़ qos_tsinfo *pTSInfo = &TSpec.f.TSInfo;
	काष्ठा list_head *pUnusedList;
	काष्ठा list_head *pAddmitList;
	क्रमागत direction_value Dir;

	अगर (is_multicast_ether_addr(Addr)) अणु
		netdev_warn(ieee->dev, "Get TS for Broadcast or Multicast\n");
		वापस false;
	पूर्ण
	अगर (ieee->current_network.qos_data.supported == 0) अणु
		UP = 0;
	पूर्ण अन्यथा अणु
		चयन (TID) अणु
		हाल 0:
		हाल 3:
			UP = 0;
			अवरोध;
		हाल 1:
		हाल 2:
			UP = 2;
			अवरोध;
		हाल 4:
		हाल 5:
			UP = 5;
			अवरोध;
		हाल 6:
		हाल 7:
			UP = 7;
			अवरोध;
		शेष:
			netdev_warn(ieee->dev, "%s(): TID(%d) is not valid\n",
				    __func__, TID);
			वापस false;
		पूर्ण
	पूर्ण

	*ppTS = SearchAdmitTRStream(ieee, Addr, UP, TxRxSelect);
	अगर (*ppTS)
		वापस true;

	अगर (!bAddNewTs) अणु
		netdev_dbg(ieee->dev, "add new TS failed(tid:%d)\n", UP);
		वापस false;
	पूर्ण

	pUnusedList = (TxRxSelect == TX_सूची) ?
				(&ieee->Tx_TS_Unused_List) :
				(&ieee->Rx_TS_Unused_List);

	pAddmitList = (TxRxSelect == TX_सूची) ?
				(&ieee->Tx_TS_Admit_List) :
				(&ieee->Rx_TS_Admit_List);

	Dir = (ieee->iw_mode == IW_MODE_MASTER) ?
				((TxRxSelect == TX_सूची) ? सूची_DOWN : सूची_UP) :
				((TxRxSelect == TX_सूची) ? सूची_UP : सूची_DOWN);

	अगर (!list_empty(pUnusedList)) अणु
		(*ppTS) = list_entry(pUnusedList->next,
			  काष्ठा ts_common_info, List);
		list_del_init(&(*ppTS)->List);
		अगर (TxRxSelect == TX_सूची) अणु
			काष्ठा tx_ts_record *पंचांगp =
				container_of(*ppTS,
				काष्ठा tx_ts_record,
				TsCommonInfo);
			ResetTxTsEntry(पंचांगp);
		पूर्ण अन्यथा अणु
			काष्ठा rx_ts_record *पंचांगp =
				 container_of(*ppTS,
				 काष्ठा rx_ts_record,
				 ts_common_info);
			ResetRxTsEntry(पंचांगp);
		पूर्ण

		netdev_dbg(ieee->dev,
			   "to init current TS, UP:%d, Dir:%d, addr: %pM ppTs=%p\n",
			   UP, Dir, Addr, *ppTS);
		pTSInfo->field.ucTrafficType = 0;
		pTSInfo->field.ucTSID = UP;
		pTSInfo->field.ucDirection = Dir;
		pTSInfo->field.ucAccessPolicy = 1;
		pTSInfo->field.ucAggregation = 0;
		pTSInfo->field.ucPSB = 0;
		pTSInfo->field.ucUP = UP;
		pTSInfo->field.ucTSInfoAckPolicy = 0;
		pTSInfo->field.ucSchedule = 0;

		MakeTSEntry(*ppTS, Addr, &TSpec, शून्य, 0, 0);
		AdmitTS(ieee, *ppTS, 0);
		list_add_tail(&((*ppTS)->List), pAddmitList);

		वापस true;
	पूर्ण

	netdev_warn(ieee->dev,
		    "There is not enough dir=%d(0=up down=1) TS record to be used!",
		    Dir);
	वापस false;
पूर्ण

अटल व्योम RemoveTsEntry(काष्ठा rtllib_device *ieee,
			  काष्ठा ts_common_info *pTs, क्रमागत tr_select TxRxSelect)
अणु
	del_समयr_sync(&pTs->SetupTimer);
	del_समयr_sync(&pTs->InactTimer);
	TsInitDelBA(ieee, pTs, TxRxSelect);

	अगर (TxRxSelect == RX_सूची) अणु
		काष्ठा rx_reorder_entry *pRxReorderEntry;
		काष्ठा rx_ts_record *pRxTS = (काष्ठा rx_ts_record *)pTs;

		अगर (समयr_pending(&pRxTS->rx_pkt_pending_समयr))
			del_समयr_sync(&pRxTS->rx_pkt_pending_समयr);

		जबतक (!list_empty(&pRxTS->rx_pending_pkt_list)) अणु
			pRxReorderEntry = (काष्ठा rx_reorder_entry *)
					list_entry(pRxTS->rx_pending_pkt_list.prev,
					काष्ठा rx_reorder_entry, List);
			netdev_dbg(ieee->dev,  "%s(): Delete SeqNum %d!\n",
				   __func__, pRxReorderEntry->SeqNum);
			list_del_init(&pRxReorderEntry->List);
			अणु
				पूर्णांक i = 0;
				काष्ठा rtllib_rxb *prxb = pRxReorderEntry->prxb;

				अगर (unlikely(!prxb))
					वापस;
				क्रम (i = 0; i < prxb->nr_subframes; i++)
					dev_kमुक्त_skb(prxb->subframes[i]);
				kमुक्त(prxb);
				prxb = शून्य;
			पूर्ण
			list_add_tail(&pRxReorderEntry->List,
				      &ieee->RxReorder_Unused_List);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा tx_ts_record *pTxTS = (काष्ठा tx_ts_record *)pTs;

		del_समयr_sync(&pTxTS->TsAddBaTimer);
	पूर्ण
पूर्ण

व्योम RemovePeerTS(काष्ठा rtllib_device *ieee, u8 *Addr)
अणु
	काष्ठा ts_common_info *pTS, *pTmpTS;

	netdev_info(ieee->dev, "===========>%s, %pM\n", __func__, Addr);

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Pending_List, List) अणु
		अगर (स_भेद(pTS->Addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, TX_सूची);
			list_del_init(&pTS->List);
			list_add_tail(&pTS->List, &ieee->Tx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Admit_List, List) अणु
		अगर (स_भेद(pTS->Addr, Addr, 6) == 0) अणु
			netdev_info(ieee->dev,
				    "====>remove Tx_TS_admin_list\n");
			RemoveTsEntry(ieee, pTS, TX_सूची);
			list_del_init(&pTS->List);
			list_add_tail(&pTS->List, &ieee->Tx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Pending_List, List) अणु
		अगर (स_भेद(pTS->Addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, RX_सूची);
			list_del_init(&pTS->List);
			list_add_tail(&pTS->List, &ieee->Rx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Admit_List, List) अणु
		अगर (स_भेद(pTS->Addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, RX_सूची);
			list_del_init(&pTS->List);
			list_add_tail(&pTS->List, &ieee->Rx_TS_Unused_List);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(RemovePeerTS);

व्योम RemoveAllTS(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा ts_common_info *pTS, *pTmpTS;

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Pending_List, List) अणु
		RemoveTsEntry(ieee, pTS, TX_सूची);
		list_del_init(&pTS->List);
		list_add_tail(&pTS->List, &ieee->Tx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Admit_List, List) अणु
		RemoveTsEntry(ieee, pTS, TX_सूची);
		list_del_init(&pTS->List);
		list_add_tail(&pTS->List, &ieee->Tx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Pending_List, List) अणु
		RemoveTsEntry(ieee, pTS, RX_सूची);
		list_del_init(&pTS->List);
		list_add_tail(&pTS->List, &ieee->Rx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Admit_List, List) अणु
		RemoveTsEntry(ieee, pTS, RX_सूची);
		list_del_init(&pTS->List);
		list_add_tail(&pTS->List, &ieee->Rx_TS_Unused_List);
	पूर्ण
पूर्ण

व्योम TsStartAddBaProcess(काष्ठा rtllib_device *ieee, काष्ठा tx_ts_record *pTxTS)
अणु
	अगर (pTxTS->bAddBaReqInProgress == false) अणु
		pTxTS->bAddBaReqInProgress = true;

		अगर (pTxTS->bAddBaReqDelayed) अणु
			netdev_dbg(ieee->dev, "Start ADDBA after 60 sec!!\n");
			mod_समयr(&pTxTS->TsAddBaTimer, jअगरfies +
				  msecs_to_jअगरfies(TS_ADDBA_DELAY));
		पूर्ण अन्यथा अणु
			netdev_dbg(ieee->dev, "Immediately Start ADDBA\n");
			mod_समयr(&pTxTS->TsAddBaTimer, jअगरfies + 10);
		पूर्ण
	पूर्ण अन्यथा
		netdev_dbg(ieee->dev, "BA timer is already added\n");
पूर्ण
