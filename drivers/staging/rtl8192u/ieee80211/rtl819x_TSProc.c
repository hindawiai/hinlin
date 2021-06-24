<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "ieee80211.h"
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश "rtl819x_TS.h"

अटल व्योम TsSetupTimeOut(काष्ठा समयr_list *unused)
अणु
	// Not implement yet
	// This is used क्रम WMMSA and ACM , that would send ADDTSReq frame.
पूर्ण

अटल व्योम TsInactTimeout(काष्ठा समयr_list *unused)
अणु
	// Not implement yet
	// This is used क्रम WMMSA and ACM.
	// This function would be call when TS is no Tx/Rx क्रम some period of समय.
पूर्ण

/********************************************************************************************************************
 *function:  I still not understand this function, so रुको क्रम further implementation
 *   input:  अचिन्हित दीर्घ	 data		//acturally we send काष्ठा tx_ts_record or काष्ठा rx_ts_record to these समयr
 *  वापस:  शून्य
 *  notice:
 ********************************************************************************************************************/
अटल व्योम RxPktPendingTimeout(काष्ठा समयr_list *t)
अणु
	काष्ठा rx_ts_record     *pRxTs = from_समयr(pRxTs, t, rx_pkt_pending_समयr);
	काष्ठा ieee80211_device *ieee = container_of(pRxTs, काष्ठा ieee80211_device, RxTsRecord[pRxTs->num]);

	काष्ठा rx_reorder_entry	*pReorderEntry = शून्य;

	//u32 flags = 0;
	अचिन्हित दीर्घ flags = 0;
	u8 index = 0;
	bool bPktInBuf = false;

	spin_lock_irqsave(&(ieee->reorder_spinlock), flags);
	IEEE80211_DEBUG(IEEE80211_DL_REORDER, "==================>%s()\n", __func__);
	अगर (pRxTs->rx_समयout_indicate_seq != 0xffff) अणु
		// Indicate the pending packets sequentially according to SeqNum until meet the gap.
		जबतक (!list_empty(&pRxTs->rx_pending_pkt_list)) अणु
			pReorderEntry = list_entry(pRxTs->rx_pending_pkt_list.prev, काष्ठा rx_reorder_entry, List);
			अगर (index == 0)
				pRxTs->rx_indicate_seq = pReorderEntry->SeqNum;

			अगर (SN_LESS(pReorderEntry->SeqNum, pRxTs->rx_indicate_seq) ||
				SN_EQUAL(pReorderEntry->SeqNum, pRxTs->rx_indicate_seq)) अणु
				list_del_init(&pReorderEntry->List);

				अगर (SN_EQUAL(pReorderEntry->SeqNum, pRxTs->rx_indicate_seq))
					pRxTs->rx_indicate_seq = (pRxTs->rx_indicate_seq + 1) % 4096;

				IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s: IndicateSeq: %d\n", __func__, pReorderEntry->SeqNum);
				ieee->stats_IndicateArray[index] = pReorderEntry->prxb;
				index++;

				list_add_tail(&pReorderEntry->List, &ieee->RxReorder_Unused_List);
			पूर्ण अन्यथा अणु
				bPktInBuf = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (index > 0) अणु
		// Set rx_समयout_indicate_seq to 0xffff to indicate no pending packets in buffer now.
		pRxTs->rx_समयout_indicate_seq = 0xffff;

		// Indicate packets
		अगर (index > REORDER_WIN_SIZE) अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR, "RxReorderIndicatePacket(): Rx Reorder buffer full!! \n");
			spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
			वापस;
		पूर्ण
		ieee80211_indicate_packets(ieee, ieee->stats_IndicateArray, index);
	पूर्ण

	अगर (bPktInBuf && (pRxTs->rx_समयout_indicate_seq == 0xffff)) अणु
		pRxTs->rx_समयout_indicate_seq = pRxTs->rx_indicate_seq;
		mod_समयr(&pRxTs->rx_pkt_pending_समयr,
			  jअगरfies + msecs_to_jअगरfies(ieee->pHTInfo->RxReorderPendingTime));
	पूर्ण
	spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
पूर्ण

/********************************************************************************************************************
 *function:  Add BA समयr function
 *   input:  अचिन्हित दीर्घ	 data		//acturally we send काष्ठा tx_ts_record or काष्ठा rx_ts_record to these समयr
 *  वापस:  शून्य
 *  notice:
 ********************************************************************************************************************/
अटल व्योम TsAddBaProcess(काष्ठा समयr_list *t)
अणु
	काष्ठा tx_ts_record *pTxTs = from_समयr(pTxTs, t, ts_add_ba_समयr);
	u8 num = pTxTs->num;
	काष्ठा ieee80211_device *ieee = container_of(pTxTs, काष्ठा ieee80211_device, TxTsRecord[num]);

	TsInitAddBA(ieee, pTxTs, BA_POLICY_IMMEDIATE, false);
	IEEE80211_DEBUG(IEEE80211_DL_BA, "%s: ADDBA Req is started!! \n", __func__);
पूर्ण


अटल व्योम ResetTsCommonInfo(काष्ठा ts_common_info *pTsCommonInfo)
अणु
	eth_zero_addr(pTsCommonInfo->addr);
	स_रखो(&pTsCommonInfo->t_spec, 0, माप(काष्ठा tspec_body));
	स_रखो(&pTsCommonInfo->t_class, 0, माप(जोड़ qos_tclas) * TCLAS_NUM);
	pTsCommonInfo->t_clas_proc = 0;
	pTsCommonInfo->t_clas_num = 0;
पूर्ण

अटल व्योम ResetTxTsEntry(काष्ठा tx_ts_record *pTS)
अणु
	ResetTsCommonInfo(&pTS->ts_common_info);
	pTS->tx_cur_seq = 0;
	pTS->add_ba_req_in_progress = false;
	pTS->add_ba_req_delayed = false;
	pTS->using_ba = false;
	ResetBaEntry(&pTS->tx_admitted_ba_record); //For BA Originator
	ResetBaEntry(&pTS->tx_pending_ba_record);
पूर्ण

अटल व्योम ResetRxTsEntry(काष्ठा rx_ts_record *pTS)
अणु
	ResetTsCommonInfo(&pTS->ts_common_info);
	pTS->rx_indicate_seq = 0xffff; // This indicate the rx_indicate_seq is not used now!!
	pTS->rx_समयout_indicate_seq = 0xffff; // This indicate the rx_समयout_indicate_seq is not used now!!
	ResetBaEntry(&pTS->rx_admitted_ba_record);	  // For BA Recipient
पूर्ण

व्योम TSInitialize(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा tx_ts_record     *pTxTS  = ieee->TxTsRecord;
	काष्ठा rx_ts_record     *pRxTS  = ieee->RxTsRecord;
	काष्ठा rx_reorder_entry	*pRxReorderEntry = ieee->RxReorderEntry;
	u8				count = 0;
	IEEE80211_DEBUG(IEEE80211_DL_TS, "==========>%s()\n", __func__);
	// Initialize Tx TS related info.
	INIT_LIST_HEAD(&ieee->Tx_TS_Admit_List);
	INIT_LIST_HEAD(&ieee->Tx_TS_Pending_List);
	INIT_LIST_HEAD(&ieee->Tx_TS_Unused_List);

	क्रम (count = 0; count < TOTAL_TS_NUM; count++) अणु
		//
		pTxTS->num = count;
		// The समयrs क्रम the operation of Traffic Stream and Block Ack.
		// DLS related समयr will be add here in the future!!
		समयr_setup(&pTxTS->ts_common_info.setup_समयr, TsSetupTimeOut,
			    0);
		समयr_setup(&pTxTS->ts_common_info.inact_समयr, TsInactTimeout,
			    0);
		समयr_setup(&pTxTS->ts_add_ba_समयr, TsAddBaProcess, 0);
		समयr_setup(&pTxTS->tx_pending_ba_record.समयr, BaSetupTimeOut,
			    0);
		समयr_setup(&pTxTS->tx_admitted_ba_record.समयr,
			    TxBaInactTimeout, 0);
		ResetTxTsEntry(pTxTS);
		list_add_tail(&pTxTS->ts_common_info.list, &ieee->Tx_TS_Unused_List);
		pTxTS++;
	पूर्ण

	// Initialize Rx TS related info.
	INIT_LIST_HEAD(&ieee->Rx_TS_Admit_List);
	INIT_LIST_HEAD(&ieee->Rx_TS_Pending_List);
	INIT_LIST_HEAD(&ieee->Rx_TS_Unused_List);
	क्रम (count = 0; count < TOTAL_TS_NUM; count++) अणु
		pRxTS->num = count;
		INIT_LIST_HEAD(&pRxTS->rx_pending_pkt_list);
		समयr_setup(&pRxTS->ts_common_info.setup_समयr, TsSetupTimeOut,
			    0);
		समयr_setup(&pRxTS->ts_common_info.inact_समयr, TsInactTimeout,
			    0);
		समयr_setup(&pRxTS->rx_admitted_ba_record.समयr,
			    RxBaInactTimeout, 0);
		समयr_setup(&pRxTS->rx_pkt_pending_समयr, RxPktPendingTimeout, 0);
		ResetRxTsEntry(pRxTS);
		list_add_tail(&pRxTS->ts_common_info.list, &ieee->Rx_TS_Unused_List);
		pRxTS++;
	पूर्ण
	// Initialize unused Rx Reorder List.
	INIT_LIST_HEAD(&ieee->RxReorder_Unused_List);
	क्रम (count = 0; count < REORDER_ENTRY_NUM; count++) अणु
		list_add_tail(&pRxReorderEntry->List, &ieee->RxReorder_Unused_List);
		अगर (count == (REORDER_ENTRY_NUM - 1))
			अवरोध;
		pRxReorderEntry = &ieee->RxReorderEntry[count + 1];
	पूर्ण
पूर्ण

अटल व्योम AdmitTS(काष्ठा ieee80211_device *ieee,
		    काष्ठा ts_common_info *pTsCommonInfo, u32 InactTime)
अणु
	del_समयr_sync(&pTsCommonInfo->setup_समयr);
	del_समयr_sync(&pTsCommonInfo->inact_समयr);

	अगर (InactTime != 0)
		mod_समयr(&pTsCommonInfo->inact_समयr,
			  jअगरfies + msecs_to_jअगरfies(InactTime));
पूर्ण


अटल काष्ठा ts_common_info *SearchAdmitTRStream(काष्ठा ieee80211_device *ieee,
						  u8 *Addr, u8 TID,
						  क्रमागत tr_select TxRxSelect)
अणु
	//सूचीECTION_VALUE	dir;
	u8	dir;
	bool				search_dir[4] = अणु0पूर्ण;
	काष्ठा list_head		*psearch_list; //FIXME
	काष्ठा ts_common_info	*pRet = शून्य;
	अगर (ieee->iw_mode == IW_MODE_MASTER) अणु //ap mode
		अगर (TxRxSelect == TX_सूची) अणु
			search_dir[सूची_DOWN] = true;
			search_dir[सूची_BI_सूची] = true;
		पूर्ण अन्यथा अणु
			search_dir[सूची_UP]	= true;
			search_dir[सूची_BI_सूची] = true;
		पूर्ण
	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
		अगर (TxRxSelect == TX_सूची)
			search_dir[सूची_UP]	= true;
		अन्यथा
			search_dir[सूची_DOWN] = true;
	पूर्ण अन्यथा अणु
		अगर (TxRxSelect == TX_सूची) अणु
			search_dir[सूची_UP]	= true;
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

	//क्रम(dir = सूची_UP; dir <= सूची_BI_सूची; dir++)
	क्रम (dir = 0; dir <= सूची_BI_सूची; dir++) अणु
		अगर (!search_dir[dir])
			जारी;
		list_क्रम_each_entry(pRet, psearch_list, list) अणु
	//		IEEE80211_DEBUG(IEEE80211_DL_TS, "ADD:%pM, TID:%d, dir:%d\n", pRet->Addr, pRet->TSpec.ts_info.ucTSID, pRet->TSpec.ts_info.ucDirection);
			अगर (स_भेद(pRet->addr, Addr, 6) == 0)
				अगर (pRet->t_spec.ts_info.uc_tsid == TID)
					अगर (pRet->t_spec.ts_info.uc_direction == dir) अणु
	//					prपूर्णांकk("Bingo! got it\n");
						अवरोध;
					पूर्ण
		पूर्ण
		अगर (&pRet->list  != psearch_list)
			अवरोध;
	पूर्ण

	अगर (&pRet->list  != psearch_list)
		वापस pRet;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम MakeTSEntry(काष्ठा ts_common_info *pTsCommonInfo, u8 *Addr,
			काष्ठा tspec_body *pTSPEC, जोड़ qos_tclas *pTCLAS, u8 TCLAS_Num,
			u8 TCLAS_Proc)
अणु
	u8	count;

	अगर (pTsCommonInfo == शून्य)
		वापस;

	स_नकल(pTsCommonInfo->addr, Addr, 6);

	अगर (pTSPEC != शून्य)
		स_नकल((u8 *)(&(pTsCommonInfo->t_spec)), (u8 *)pTSPEC, माप(काष्ठा tspec_body));

	क्रम (count = 0; count < TCLAS_Num; count++)
		स_नकल((u8 *)(&(pTsCommonInfo->t_class[count])), (u8 *)pTCLAS, माप(जोड़ qos_tclas));

	pTsCommonInfo->t_clas_proc = TCLAS_Proc;
	pTsCommonInfo->t_clas_num = TCLAS_Num;
पूर्ण


bool GetTs(
	काष्ठा ieee80211_device		*ieee,
	काष्ठा ts_common_info		**ppTS,
	u8				*Addr,
	u8				TID,
	क्रमागत tr_select			TxRxSelect,  //Rx:1, Tx:0
	bool				bAddNewTs
	)
अणु
	u8	UP = 0;
	//
	// We करो not build any TS क्रम Broadcast or Multicast stream.
	// So reject these kinds of search here.
	//
	अगर (is_multicast_ether_addr(Addr)) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "get TS for Broadcast or Multicast\n");
		वापस false;
	पूर्ण

	अगर (ieee->current_network.qos_data.supported == 0) अणु
		UP = 0;
	पूर्ण अन्यथा अणु
		// In WMM हाल: we use 4 TID only
		अगर (!is_ac_valid(TID)) अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR, " in %s(), TID(%d) is not valid\n", __func__, TID);
			वापस false;
		पूर्ण

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
		पूर्ण
	पूर्ण

	*ppTS = SearchAdmitTRStream(
			ieee,
			Addr,
			UP,
			TxRxSelect);
	अगर (*ppTS != शून्य) अणु
		वापस true;
	पूर्ण अन्यथा अणु
		अगर (!bAddNewTs) अणु
			IEEE80211_DEBUG(IEEE80211_DL_TS, "add new TS failed(tid:%d)\n", UP);
			वापस false;
		पूर्ण अन्यथा अणु
			//
			// Create a new Traffic stream क्रम current Tx/Rx
			// This is क्रम EDCA and WMM to add a new TS.
			// For HCCA or WMMSA, TS cannot be addmit without negotiation.
			//
			काष्ठा tspec_body	TSpec;
			काष्ठा qos_tsinfo	*pTSInfo = &TSpec.ts_info;
			काष्ठा list_head	*pUnusedList =
								(TxRxSelect == TX_सूची) ?
								(&ieee->Tx_TS_Unused_List) :
								(&ieee->Rx_TS_Unused_List);

			काष्ठा list_head	*pAddmitList =
								(TxRxSelect == TX_सूची) ?
								(&ieee->Tx_TS_Admit_List) :
								(&ieee->Rx_TS_Admit_List);

			क्रमागत direction_value	Dir =		(ieee->iw_mode == IW_MODE_MASTER) ?
								((TxRxSelect == TX_सूची) ? सूची_DOWN : सूची_UP) :
								((TxRxSelect == TX_सूची) ? सूची_UP : सूची_DOWN);
			IEEE80211_DEBUG(IEEE80211_DL_TS, "to add Ts\n");
			अगर (!list_empty(pUnusedList)) अणु
				(*ppTS) = list_entry(pUnusedList->next, काष्ठा ts_common_info, list);
				list_del_init(&(*ppTS)->list);
				अगर (TxRxSelect == TX_सूची) अणु
					काष्ठा tx_ts_record *पंचांगp = container_of(*ppTS, काष्ठा tx_ts_record, ts_common_info);
					ResetTxTsEntry(पंचांगp);
				पूर्ण अन्यथा अणु
					काष्ठा rx_ts_record *पंचांगp = container_of(*ppTS, काष्ठा rx_ts_record, ts_common_info);
					ResetRxTsEntry(पंचांगp);
				पूर्ण

				IEEE80211_DEBUG(IEEE80211_DL_TS, "to init current TS, UP:%d, Dir:%d, addr:%pM\n", UP, Dir, Addr);
				// Prepare TS Info related field
				pTSInfo->uc_traffic_type = 0;		// Traffic type: WMM is reserved in this field
				pTSInfo->uc_tsid = UP;			// TSID
				pTSInfo->uc_direction = Dir;		// Direction: अगर there is DirectLink, this need additional consideration.
				pTSInfo->uc_access_policy = 1;		// Access policy
				pTSInfo->uc_aggregation = 0;		// Aggregation
				pTSInfo->uc_psb = 0;			// Aggregation
				pTSInfo->uc_up = UP;			// User priority
				pTSInfo->uc_ts_info_ack_policy = 0;	// Ack policy
				pTSInfo->uc_schedule = 0;		// Schedule

				MakeTSEntry(*ppTS, Addr, &TSpec, शून्य, 0, 0);
				AdmitTS(ieee, *ppTS, 0);
				list_add_tail(&((*ppTS)->list), pAddmitList);
				// अगर there is DirectLink, we need to करो additional operation here!!

				वापस true;
			पूर्ण अन्यथा अणु
				IEEE80211_DEBUG(IEEE80211_DL_ERR, "in function %s() There is not enough TS record to be used!!", __func__);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम RemoveTsEntry(काष्ठा ieee80211_device *ieee, काष्ठा ts_common_info *pTs,
			  क्रमागत tr_select TxRxSelect)
अणु
	//u32 flags = 0;
	अचिन्हित दीर्घ flags = 0;
	del_समयr_sync(&pTs->setup_समयr);
	del_समयr_sync(&pTs->inact_समयr);
	TsInitDelBA(ieee, pTs, TxRxSelect);

	अगर (TxRxSelect == RX_सूची) अणु
		काष्ठा rx_reorder_entry	*pRxReorderEntry;
		काष्ठा rx_ts_record     *pRxTS = (काष्ठा rx_ts_record *)pTs;
		अगर (समयr_pending(&pRxTS->rx_pkt_pending_समयr))
			del_समयr_sync(&pRxTS->rx_pkt_pending_समयr);

		जबतक (!list_empty(&pRxTS->rx_pending_pkt_list)) अणु
			spin_lock_irqsave(&(ieee->reorder_spinlock), flags);
			//pRxReorderEntry = list_entry(&pRxTS->rx_pending_pkt_list.prev,RX_REORDER_ENTRY,List);
			pRxReorderEntry = list_entry(pRxTS->rx_pending_pkt_list.prev, काष्ठा rx_reorder_entry, List);
			list_del_init(&pRxReorderEntry->List);
			अणु
				पूर्णांक i = 0;
				काष्ठा ieee80211_rxb *prxb = pRxReorderEntry->prxb;
				अगर (unlikely(!prxb)) अणु
					spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
					वापस;
				पूर्ण
				क्रम (i =  0; i < prxb->nr_subframes; i++)
					dev_kमुक्त_skb(prxb->subframes[i]);

				kमुक्त(prxb);
				prxb = शून्य;
			पूर्ण
			list_add_tail(&pRxReorderEntry->List, &ieee->RxReorder_Unused_List);
			spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
		पूर्ण

	पूर्ण अन्यथा अणु
		काष्ठा tx_ts_record *pTxTS = (काष्ठा tx_ts_record *)pTs;
		del_समयr_sync(&pTxTS->ts_add_ba_समयr);
	पूर्ण
पूर्ण

व्योम RemovePeerTS(काष्ठा ieee80211_device *ieee, u8 *Addr)
अणु
	काष्ठा ts_common_info	*pTS, *pTmpTS;

	prपूर्णांकk("===========>%s,%pM\n", __func__, Addr);
	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Pending_List, list) अणु
		अगर (स_भेद(pTS->addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, TX_सूची);
			list_del_init(&pTS->list);
			list_add_tail(&pTS->list, &ieee->Tx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Admit_List, list) अणु
		अगर (स_भेद(pTS->addr, Addr, 6) == 0) अणु
			prपूर्णांकk("====>remove Tx_TS_admin_list\n");
			RemoveTsEntry(ieee, pTS, TX_सूची);
			list_del_init(&pTS->list);
			list_add_tail(&pTS->list, &ieee->Tx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Pending_List, list) अणु
		अगर (स_भेद(pTS->addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, RX_सूची);
			list_del_init(&pTS->list);
			list_add_tail(&pTS->list, &ieee->Rx_TS_Unused_List);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Admit_List, list) अणु
		अगर (स_भेद(pTS->addr, Addr, 6) == 0) अणु
			RemoveTsEntry(ieee, pTS, RX_सूची);
			list_del_init(&pTS->list);
			list_add_tail(&pTS->list, &ieee->Rx_TS_Unused_List);
		पूर्ण
	पूर्ण
पूर्ण

व्योम RemoveAllTS(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा ts_common_info *pTS, *pTmpTS;

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Pending_List, list) अणु
		RemoveTsEntry(ieee, pTS, TX_सूची);
		list_del_init(&pTS->list);
		list_add_tail(&pTS->list, &ieee->Tx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Tx_TS_Admit_List, list) अणु
		RemoveTsEntry(ieee, pTS, TX_सूची);
		list_del_init(&pTS->list);
		list_add_tail(&pTS->list, &ieee->Tx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Pending_List, list) अणु
		RemoveTsEntry(ieee, pTS, RX_सूची);
		list_del_init(&pTS->list);
		list_add_tail(&pTS->list, &ieee->Rx_TS_Unused_List);
	पूर्ण

	list_क्रम_each_entry_safe(pTS, pTmpTS, &ieee->Rx_TS_Admit_List, list) अणु
		RemoveTsEntry(ieee, pTS, RX_सूची);
		list_del_init(&pTS->list);
		list_add_tail(&pTS->list, &ieee->Rx_TS_Unused_List);
	पूर्ण
पूर्ण

व्योम TsStartAddBaProcess(काष्ठा ieee80211_device *ieee, काष्ठा tx_ts_record *pTxTS)
अणु
	अगर (!pTxTS->add_ba_req_in_progress) अणु
		pTxTS->add_ba_req_in_progress = true;
		अगर (pTxTS->add_ba_req_delayed)	अणु
			IEEE80211_DEBUG(IEEE80211_DL_BA, "%s: Delayed Start ADDBA after 60 sec!!\n", __func__);
			mod_समयr(&pTxTS->ts_add_ba_समयr,
				  jअगरfies + msecs_to_jअगरfies(TS_ADDBA_DELAY));
		पूर्ण अन्यथा अणु
			IEEE80211_DEBUG(IEEE80211_DL_BA, "%s: Immediately Start ADDBA now!!\n", __func__);
			mod_समयr(&pTxTS->ts_add_ba_समयr, jअगरfies + 10); //set 10 ticks
		पूर्ण
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "%s()==>BA timer is already added\n", __func__);
	पूर्ण
पूर्ण
