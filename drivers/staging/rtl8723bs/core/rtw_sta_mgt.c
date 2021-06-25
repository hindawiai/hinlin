<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_STA_MGT_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

व्योम _rtw_init_stainfo(काष्ठा sta_info *psta);
व्योम _rtw_init_stainfo(काष्ठा sta_info *psta)
अणु
	स_रखो((u8 *)psta, 0, माप(काष्ठा sta_info));

	spin_lock_init(&psta->lock);
	INIT_LIST_HEAD(&psta->list);
	INIT_LIST_HEAD(&psta->hash_list);
	/* INIT_LIST_HEAD(&psta->asoc_list); */
	/* INIT_LIST_HEAD(&psta->sleep_list); */
	/* INIT_LIST_HEAD(&psta->wakeup_list); */

	_rtw_init_queue(&psta->sleep_q);
	psta->sleepq_len = 0;

	_rtw_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_rtw_init_sta_recv_priv(&psta->sta_recvpriv);

	INIT_LIST_HEAD(&psta->asoc_list);

	INIT_LIST_HEAD(&psta->auth_list);

	psta->expire_to = 0;

	psta->flags = 0;

	psta->capability = 0;

	psta->bpairwise_key_installed = false;

	psta->nonerp_set = 0;
	psta->no_लघु_slot_समय_set = 0;
	psta->no_लघु_preamble_set = 0;
	psta->no_ht_gf_set = 0;
	psta->no_ht_set = 0;
	psta->ht_20mhz_set = 0;

	psta->under_exist_checking = 0;

	psta->keep_alive_trycnt = 0;
पूर्ण

u32 _rtw_init_sta_priv(काष्ठा	sta_priv *pstapriv)
अणु
	काष्ठा sta_info *psta;
	s32 i;

	pstapriv->pallocated_stainfo_buf = vzalloc(माप(काष्ठा sta_info) * NUM_STA+4);

	अगर (!pstapriv->pallocated_stainfo_buf)
		वापस _FAIL;

	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 -
		((SIZE_PTR)(pstapriv->pallocated_stainfo_buf) & 3);

	_rtw_init_queue(&pstapriv->मुक्त_sta_queue);

	spin_lock_init(&pstapriv->sta_hash_lock);

	/* _rtw_init_queue(&pstapriv->asoc_q); */
	pstapriv->asoc_sta_count = 0;
	_rtw_init_queue(&pstapriv->sleep_q);
	_rtw_init_queue(&pstapriv->wakeup_q);

	psta = (काष्ठा sta_info *)(pstapriv->pstainfo_buf);

	क्रम (i = 0; i < NUM_STA; i++) अणु
		_rtw_init_stainfo(psta);

		INIT_LIST_HEAD(&(pstapriv->sta_hash[i]));

		list_add_tail(&psta->list, get_list_head(&pstapriv->मुक्त_sta_queue));

		psta++;
	पूर्ण

	pstapriv->sta_dz_biपंचांगap = 0;
	pstapriv->tim_biपंचांगap = 0;

	INIT_LIST_HEAD(&pstapriv->asoc_list);
	INIT_LIST_HEAD(&pstapriv->auth_list);
	spin_lock_init(&pstapriv->asoc_list_lock);
	spin_lock_init(&pstapriv->auth_list_lock);
	pstapriv->asoc_list_cnt = 0;
	pstapriv->auth_list_cnt = 0;

	pstapriv->auth_to = 3; /*  3*2 = 6 sec */
	pstapriv->assoc_to = 3;
	pstapriv->expire_to = 3; /*  3*2 = 6 sec */
	pstapriv->max_num_sta = NUM_STA;
	वापस _SUCCESS;
पूर्ण

अंतरभूत पूर्णांक rtw_stainfo_offset(काष्ठा sta_priv *stapriv, काष्ठा sta_info *sta)
अणु
	पूर्णांक offset = (((u8 *)sta) - stapriv->pstainfo_buf)/माप(काष्ठा sta_info);

	वापस offset;
पूर्ण

अंतरभूत काष्ठा sta_info *rtw_get_stainfo_by_offset(काष्ठा sta_priv *stapriv, पूर्णांक offset)
अणु
	वापस (काष्ठा sta_info *)(stapriv->pstainfo_buf + offset * माप(काष्ठा sta_info));
पूर्ण

/*  this function is used to मुक्त the memory of lock || sema क्रम all stainfos */
व्योम kमुक्त_all_stainfo(काष्ठा sta_priv *pstapriv);
व्योम kमुक्त_all_stainfo(काष्ठा sta_priv *pstapriv)
अणु
	काष्ठा list_head	*plist, *phead;
	काष्ठा sta_info *psta = शून्य;

	spin_lock_bh(&pstapriv->sta_hash_lock);

	phead = get_list_head(&pstapriv->मुक्त_sta_queue);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, list);
		plist = get_next(plist);
	पूर्ण

	spin_unlock_bh(&pstapriv->sta_hash_lock);
पूर्ण

व्योम kमुक्त_sta_priv_lock(काष्ठा	sta_priv *pstapriv);
व्योम kमुक्त_sta_priv_lock(काष्ठा	sta_priv *pstapriv)
अणु
	 kमुक्त_all_stainfo(pstapriv); /* be करोne beक्रमe मुक्त sta_hash_lock */
पूर्ण

u32 _rtw_मुक्त_sta_priv(काष्ठा	sta_priv *pstapriv)
अणु
	काष्ठा list_head	*phead, *plist;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	पूर्णांक	index;

	अगर (pstapriv) अणु
		/*delete all reordering_ctrl_समयr		*/
		spin_lock_bh(&pstapriv->sta_hash_lock);
		क्रम (index = 0; index < NUM_STA; index++) अणु
			phead = &(pstapriv->sta_hash[index]);
			plist = get_next(phead);

			जबतक (phead != plist) अणु
				पूर्णांक i;

				psta = container_of(plist, काष्ठा sta_info, hash_list);
				plist = get_next(plist);

				क्रम (i = 0; i < 16 ; i++) अणु
					preorder_ctrl = &psta->recvreorder_ctrl[i];
					del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&pstapriv->sta_hash_lock);
		/*===============================*/

		kमुक्त_sta_priv_lock(pstapriv);

		vमुक्त(pstapriv->pallocated_stainfo_buf);
	पूर्ण
	वापस _SUCCESS;
पूर्ण

/* काष्ठा	sta_info *rtw_alloc_stainfo(_queue *pमुक्त_sta_queue, अचिन्हित अक्षर *hwaddr) */
काष्ठा	sta_info *rtw_alloc_stainfo(काष्ठा	sta_priv *pstapriv, u8 *hwaddr)
अणु
	s32	index;
	काष्ठा list_head	*phash_list;
	काष्ठा sta_info *psta;
	काष्ठा __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	पूर्णांक i = 0;
	u16  wRxSeqInitialValue = 0xffff;

	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;

	/* spin_lock_bh(&(pमुक्त_sta_queue->lock)); */
	spin_lock_bh(&(pstapriv->sta_hash_lock));
	अगर (list_empty(&pमुक्त_sta_queue->queue)) अणु
		/* spin_unlock_bh(&(pमुक्त_sta_queue->lock)); */
		spin_unlock_bh(&(pstapriv->sta_hash_lock));
		वापस शून्य;
	पूर्ण अन्यथा अणु
		psta = container_of(get_next(&pमुक्त_sta_queue->queue), काष्ठा sta_info, list);

		list_del_init(&(psta->list));

		/* spin_unlock_bh(&(pमुक्त_sta_queue->lock)); */

		_rtw_init_stainfo(psta);

		psta->padapter = pstapriv->padapter;

		स_नकल(psta->hwaddr, hwaddr, ETH_ALEN);

		index = wअगरi_mac_hash(hwaddr);

		अगर (index >= NUM_STA) अणु
			spin_unlock_bh(&(pstapriv->sta_hash_lock));
			psta = शून्य;
			जाओ निकास;
		पूर्ण
		phash_list = &(pstapriv->sta_hash[index]);

		/* spin_lock_bh(&(pstapriv->sta_hash_lock)); */

		list_add_tail(&psta->hash_list, phash_list);

		pstapriv->asoc_sta_count++;

		/* spin_unlock_bh(&(pstapriv->sta_hash_lock)); */

/*  Commented by Albert 2009/08/13 */
/*  For the SMC router, the sequence number of first packet of WPS handshake will be 0. */
/*  In this हाल, this packet will be dropped by recv_decache function अगर we use the 0x00 as the शेष value क्रम tid_rxseq variable. */
/*  So, we initialize the tid_rxseq variable as the 0xffff. */

		क्रम (i = 0; i < 16; i++)
			स_नकल(&psta->sta_recvpriv.rxcache.tid_rxseq[i], &wRxSeqInitialValue, 2);

		init_addba_retry_समयr(pstapriv->padapter, psta);

		/* क्रम A-MPDU Rx reordering buffer control */
		क्रम (i = 0; i < 16 ; i++) अणु
			preorder_ctrl = &psta->recvreorder_ctrl[i];

			preorder_ctrl->padapter = pstapriv->padapter;

			preorder_ctrl->enable = false;

			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
			/* preorder_ctrl->wsize_b = (NR_RECVBUFF-2); */
			preorder_ctrl->wsize_b = 64;/* 64; */

			_rtw_init_queue(&preorder_ctrl->pending_recvframe_queue);

			rtw_init_recv_समयr(preorder_ctrl);
		पूर्ण

		/* init क्रम DM */
		psta->rssi_stat.UndecoratedSmoothedPWDB = (-1);
		psta->rssi_stat.UndecoratedSmoothedCCK = (-1);

		/* init क्रम the sequence number of received management frame */
		psta->RxMgmtFrameSeqNum = 0xffff;
		spin_unlock_bh(&(pstapriv->sta_hash_lock));
		/* alloc mac id क्रम non-bc/mc station, */
		rtw_alloc_macid(pstapriv->padapter, psta);
	पूर्ण

निकास:

	वापस psta;
पूर्ण

/*  using pstapriv->sta_hash_lock to protect */
u32 rtw_मुक्त_stainfo(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक i;
	काष्ठा __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा	sta_xmit_priv *pstaxmitpriv;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा hw_xmit *phwxmit;

	अगर (!psta)
		जाओ निकास;

	spin_lock_bh(&psta->lock);
	psta->state &= ~_FW_LINKED;
	spin_unlock_bh(&psta->lock);

	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;

	pstaxmitpriv = &psta->sta_xmitpriv;

	/* list_del_init(&psta->sleep_list); */

	/* list_del_init(&psta->wakeup_list); */

	spin_lock_bh(&pxmitpriv->lock);

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &psta->sleep_q);
	psta->sleepq_len = 0;

	/* vo */
	/* spin_lock_bh(&(pxmitpriv->vo_pending.lock)); */
	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vo_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vo_q.tx_pending));
	phwxmit = pxmitpriv->hwxmits;
	phwxmit->accnt -= pstaxmitpriv->vo_q.qcnt;
	pstaxmitpriv->vo_q.qcnt = 0;
	/* spin_unlock_bh(&(pxmitpriv->vo_pending.lock)); */

	/* vi */
	/* spin_lock_bh(&(pxmitpriv->vi_pending.lock)); */
	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vi_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vi_q.tx_pending));
	phwxmit = pxmitpriv->hwxmits+1;
	phwxmit->accnt -= pstaxmitpriv->vi_q.qcnt;
	pstaxmitpriv->vi_q.qcnt = 0;
	/* spin_unlock_bh(&(pxmitpriv->vi_pending.lock)); */

	/* be */
	/* spin_lock_bh(&(pxmitpriv->be_pending.lock)); */
	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&(pstaxmitpriv->be_q.tx_pending));
	phwxmit = pxmitpriv->hwxmits+2;
	phwxmit->accnt -= pstaxmitpriv->be_q.qcnt;
	pstaxmitpriv->be_q.qcnt = 0;
	/* spin_unlock_bh(&(pxmitpriv->be_pending.lock)); */

	/* bk */
	/* spin_lock_bh(&(pxmitpriv->bk_pending.lock)); */
	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->bk_q.sta_pending);
	list_del_init(&(pstaxmitpriv->bk_q.tx_pending));
	phwxmit = pxmitpriv->hwxmits+3;
	phwxmit->accnt -= pstaxmitpriv->bk_q.qcnt;
	pstaxmitpriv->bk_q.qcnt = 0;
	/* spin_unlock_bh(&(pxmitpriv->bk_pending.lock)); */

	spin_unlock_bh(&pxmitpriv->lock);

	list_del_init(&psta->hash_list);
	pstapriv->asoc_sta_count--;

	/*  re-init sta_info; 20061114 will be init in alloc_stainfo */
	/* _rtw_init_sta_xmit_priv(&psta->sta_xmitpriv); */
	/* _rtw_init_sta_recv_priv(&psta->sta_recvpriv); */

	del_समयr_sync(&psta->addba_retry_समयr);

	/* क्रम A-MPDU Rx reordering buffer control, cancel reordering_ctrl_समयr */
	क्रम (i = 0; i < 16 ; i++) अणु
		काष्ठा list_head	*phead, *plist;
		जोड़ recv_frame *prframe;
		काष्ठा __queue *ppending_recvframe_queue;
		काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

		preorder_ctrl = &psta->recvreorder_ctrl[i];

		del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);

		ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

		spin_lock_bh(&ppending_recvframe_queue->lock);

		phead =		get_list_head(ppending_recvframe_queue);
		plist = get_next(phead);

		जबतक (!list_empty(phead)) अणु
			prframe = (जोड़ recv_frame *)plist;

			plist = get_next(plist);

			list_del_init(&(prframe->u.hdr.list));

			rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
		पूर्ण

		spin_unlock_bh(&ppending_recvframe_queue->lock);
	पूर्ण

	अगर (!(psta->state & WIFI_AP_STATE))
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, false);

	/* release mac id क्रम non-bc/mc station, */
	rtw_release_macid(pstapriv->padapter, psta);

/*
	spin_lock_bh(&pstapriv->asoc_list_lock);
	list_del_init(&psta->asoc_list);
	spin_unlock_bh(&pstapriv->asoc_list_lock);
*/
	spin_lock_bh(&pstapriv->auth_list_lock);
	अगर (!list_empty(&psta->auth_list)) अणु
		list_del_init(&psta->auth_list);
		pstapriv->auth_list_cnt--;
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	psta->expire_to = 0;
	psta->sleepq_ac_len = 0;
	psta->qos_info = 0;

	psta->max_sp_len = 0;
	psta->uapsd_bk = 0;
	psta->uapsd_be = 0;
	psta->uapsd_vi = 0;
	psta->uapsd_vo = 0;

	psta->has_legacy_ac = 0;

	pstapriv->sta_dz_biपंचांगap &= ~BIT(psta->aid);
	pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

	अगर ((psta->aid > 0) && (pstapriv->sta_aid[psta->aid - 1] == psta)) अणु
		pstapriv->sta_aid[psta->aid - 1] = शून्य;
		psta->aid = 0;
	पूर्ण

	psta->under_exist_checking = 0;

	/* spin_lock_bh(&(pमुक्त_sta_queue->lock)); */
	list_add_tail(&psta->list, get_list_head(pमुक्त_sta_queue));
	/* spin_unlock_bh(&(pमुक्त_sta_queue->lock)); */

निकास:
	वापस _SUCCESS;
पूर्ण

/*  मुक्त all stainfo which in sta_hash[all] */
व्योम rtw_मुक्त_all_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head	*plist, *phead;
	s32	index;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *pbcmc_stainfo = rtw_get_bcmc_stainfo(padapter);

	अगर (pstapriv->asoc_sta_count == 1)
		वापस;

	spin_lock_bh(&pstapriv->sta_hash_lock);

	क्रम (index = 0; index < NUM_STA; index++) अणु
		phead = &(pstapriv->sta_hash[index]);
		plist = get_next(phead);

		जबतक (phead != plist) अणु
			psta = container_of(plist, काष्ठा sta_info, hash_list);

			plist = get_next(plist);

			अगर (pbcmc_stainfo != psta)
				rtw_मुक्त_stainfo(padapter, psta);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pstapriv->sta_hash_lock);
पूर्ण

/* any station allocated can be searched by hash list */
काष्ठा sta_info *rtw_get_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr)
अणु
	काष्ठा list_head	*plist, *phead;
	काष्ठा sta_info *psta = शून्य;
	u32 index;
	u8 *addr;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	अगर (!hwaddr)
		वापस शून्य;

	अगर (IS_MCAST(hwaddr))
		addr = bc_addr;
	अन्यथा
		addr = hwaddr;

	index = wअगरi_mac_hash(addr);

	spin_lock_bh(&pstapriv->sta_hash_lock);

	phead = &(pstapriv->sta_hash[index]);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, hash_list);

		अगर ((!स_भेद(psta->hwaddr, addr, ETH_ALEN)))
		 /*  अगर found the matched address */
			अवरोध;

		psta = शून्य;
		plist = get_next(plist);
	पूर्ण

	spin_unlock_bh(&pstapriv->sta_hash_lock);
	वापस psta;
पूर्ण

u32 rtw_init_bcmc_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_info *psta;
	u32 res = _SUCCESS;
	NDIS_802_11_MAC_ADDRESS	bcast_addr = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	/* काष्ठा __queue	*pstapending = &padapter->xmitpriv.bm_pending; */

	psta = rtw_alloc_stainfo(pstapriv, bcast_addr);

	अगर (!psta) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	/*  शेष broadcast & multicast use macid 1 */
	psta->mac_id = 1;

निकास:
	वापस _SUCCESS;
पूर्ण

काष्ठा sta_info *rtw_get_bcmc_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	वापस rtw_get_stainfo(pstapriv, bc_addr);
पूर्ण

u8 rtw_access_ctrl(काष्ठा adapter *padapter, u8 *mac_addr)
अणु
	bool res = true;
	काष्ठा list_head	*plist, *phead;
	काष्ठा rtw_wlan_acl_node *paclnode;
	bool match = false;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue	*pacl_node_q = &pacl_list->acl_node_q;

	spin_lock_bh(&(pacl_node_q->lock));
	phead = get_list_head(pacl_node_q);
	plist = get_next(phead);
	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = get_next(plist);

		अगर (!स_भेद(paclnode->addr, mac_addr, ETH_ALEN))
			अगर (paclnode->valid == true) अणु
				match = true;
				अवरोध;
			पूर्ण
	पूर्ण
	spin_unlock_bh(&(pacl_node_q->lock));

	अगर (pacl_list->mode == 1) /* accept unless in deny list */
		res = !match;

	अन्यथा अगर (pacl_list->mode == 2)/* deny unless in accept list */
		res = match;
	अन्यथा
		 res = true;

	वापस res;
पूर्ण
