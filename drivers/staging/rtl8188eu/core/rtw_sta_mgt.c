<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_STA_MGT_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <xmit_osdep.h>
#समावेश <mlme_osdep.h>
#समावेश <sta_info.h>
#समावेश <linux/vदो_स्मृति.h>

अटल व्योम _rtw_init_stainfo(काष्ठा sta_info *psta)
अणु
	स_रखो((u8 *)psta, 0, माप(काष्ठा sta_info));

	spin_lock_init(&psta->lock);
	INIT_LIST_HEAD(&psta->list);
	INIT_LIST_HEAD(&psta->hash_list);
	_rtw_init_queue(&psta->sleep_q);
	psta->sleepq_len = 0;

	_rtw_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_rtw_init_sta_recv_priv(&psta->sta_recvpriv);

#अगर_घोषित CONFIG_88EU_AP_MODE

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

#पूर्ण_अगर	/*  CONFIG_88EU_AP_MODE */
पूर्ण

u32 _rtw_init_sta_priv(काष्ठा sta_priv *pstapriv)
अणु
	काष्ठा sta_info *psta;
	s32 i;

	pstapriv->pallocated_stainfo_buf = vzalloc(माप(काष्ठा sta_info) * NUM_STA + 4);

	अगर (!pstapriv->pallocated_stainfo_buf)
		वापस _FAIL;

	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 -
		((माप_प्रकार)(pstapriv->pallocated_stainfo_buf) & 3);

	_rtw_init_queue(&pstapriv->मुक्त_sta_queue);

	spin_lock_init(&pstapriv->sta_hash_lock);

	pstapriv->asoc_sta_count = 0;
	_rtw_init_queue(&pstapriv->sleep_q);
	_rtw_init_queue(&pstapriv->wakeup_q);

	psta = (काष्ठा sta_info *)(pstapriv->pstainfo_buf);

	क्रम (i = 0; i < NUM_STA; i++) अणु
		_rtw_init_stainfo(psta);

		INIT_LIST_HEAD(&pstapriv->sta_hash[i]);

		list_add_tail(&psta->list,
			      get_list_head(&pstapriv->मुक्त_sta_queue));

		psta++;
	पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE

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
#पूर्ण_अगर

	वापस _SUCCESS;
पूर्ण

अंतरभूत पूर्णांक rtw_stainfo_offset(काष्ठा sta_priv *stapriv, काष्ठा sta_info *sta)
अणु
	पूर्णांक offset = (((u8 *)sta) - stapriv->pstainfo_buf) / माप(काष्ठा sta_info);

	अगर (!stainfo_offset_valid(offset))
		DBG_88E("%s invalid offset(%d), out of range!!!", __func__, offset);

	वापस offset;
पूर्ण

अंतरभूत काष्ठा sta_info *rtw_get_stainfo_by_offset(काष्ठा sta_priv *stapriv, पूर्णांक offset)
अणु
	अगर (!stainfo_offset_valid(offset))
		DBG_88E("%s invalid offset(%d), out of range!!!", __func__, offset);

	वापस (काष्ठा sta_info *)(stapriv->pstainfo_buf + offset * माप(काष्ठा sta_info));
पूर्ण

u32 _rtw_मुक्त_sta_priv(काष्ठा sta_priv *pstapriv)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	पूर्णांक index;

	अगर (!pstapriv)
		वापस _SUCCESS;

	/* delete all reordering_ctrl_समयr */
	spin_lock_bh(&pstapriv->sta_hash_lock);
	क्रम (index = 0; index < NUM_STA; index++) अणु
		phead = &pstapriv->sta_hash[index];
		plist = phead->next;

		जबतक (phead != plist) अणु
			पूर्णांक i;

			psta = container_of(plist, काष्ठा sta_info, hash_list);
			plist = plist->next;

			क्रम (i = 0; i < 16; i++) अणु
				preorder_ctrl = &psta->recvreorder_ctrl[i];
				del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pstapriv->sta_hash_lock);

	vमुक्त(pstapriv->pallocated_stainfo_buf);

	वापस _SUCCESS;
पूर्ण

काष्ठा sta_info *rtw_alloc_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr)
अणु
	s32 index;
	काष्ठा list_head *phash_list;
	काष्ठा sta_info *psta;
	काष्ठा __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	पूर्णांक i = 0;
	u16 wRxSeqInitialValue = 0xffff;

	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;

	spin_lock_bh(&pमुक्त_sta_queue->lock);
	psta = list_first_entry_or_null(&pमुक्त_sta_queue->queue,
					काष्ठा sta_info, list);
	अगर (!psta) अणु
		spin_unlock_bh(&pमुक्त_sta_queue->lock);
		वापस शून्य;
	पूर्ण

	list_del_init(&psta->list);
	spin_unlock_bh(&pमुक्त_sta_queue->lock);
	_rtw_init_stainfo(psta);
	स_नकल(psta->hwaddr, hwaddr, ETH_ALEN);
	index = wअगरi_mac_hash(hwaddr);
	RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_info_,
		 ("%s: index=%x", __func__, index));
	अगर (index >= NUM_STA) अणु
		RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_err_,
			 ("ERROR => %s: index >= NUM_STA", __func__));
		वापस शून्य;
	पूर्ण
	phash_list = &pstapriv->sta_hash[index];

	spin_lock_bh(&pstapriv->sta_hash_lock);
	list_add_tail(&psta->hash_list, phash_list);
	pstapriv->asoc_sta_count++;
	spin_unlock_bh(&pstapriv->sta_hash_lock);

	/* Commented by Albert 2009/08/13
	 * For the SMC router, the sequence number of first packet of
	 * WPS handshake will be 0. In this हाल, this packet will be
	 * dropped by recv_decache function अगर we use the 0x00 as the
	 * शेष value क्रम tid_rxseq variable. So, we initialize the
	 * tid_rxseq variable as the 0xffff.
	 */

	क्रम (i = 0; i < 16; i++)
		स_नकल(&psta->sta_recvpriv.rxcache.tid_rxseq[i],
		       &wRxSeqInitialValue, 2);

	RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_info_,
		 ("alloc number_%d stainfo  with hwaddr = %pM\n",
		  pstapriv->asoc_sta_count, hwaddr));

	init_addba_retry_समयr(pstapriv->padapter, psta);

	/* क्रम A-MPDU Rx reordering buffer control */
	क्रम (i = 0; i < 16; i++) अणु
		preorder_ctrl = &psta->recvreorder_ctrl[i];

		preorder_ctrl->padapter = pstapriv->padapter;

		preorder_ctrl->enable = false;

		preorder_ctrl->indicate_seq = 0xffff;
		preorder_ctrl->wend_b = 0xffff;
		preorder_ctrl->wsize_b = 64;/* 64; */

		_rtw_init_queue(&preorder_ctrl->pending_recvframe_queue);

		rtw_init_recv_समयr(preorder_ctrl);
	पूर्ण

	/* init क्रम DM */
	psta->rssi_stat.UndecoratedSmoothedPWDB = -1;
	psta->rssi_stat.UndecoratedSmoothedCCK = -1;

	/* init क्रम the sequence number of received management frame */
	psta->RxMgmtFrameSeqNum = 0xffff;

	वापस psta;
पूर्ण

/*  using pstapriv->sta_hash_lock to protect */
u32 rtw_मुक्त_stainfo(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक i;
	काष्ठा __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा sta_xmit_priv *pstaxmitpriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (!psta)
		जाओ निकास;

	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;

	pstaxmitpriv = &psta->sta_xmitpriv;

	spin_lock_bh(&pxmitpriv->lock);

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &psta->sleep_q);
	psta->sleepq_len = 0;

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vo_q.sta_pending);

	list_del_init(&pstaxmitpriv->vo_q.tx_pending);

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vi_q.sta_pending);

	list_del_init(&pstaxmitpriv->vi_q.tx_pending);

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->bk_q.sta_pending);

	list_del_init(&pstaxmitpriv->bk_q.tx_pending);

	rtw_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->be_q.sta_pending);

	list_del_init(&pstaxmitpriv->be_q.tx_pending);

	spin_unlock_bh(&pxmitpriv->lock);

	list_del_init(&psta->hash_list);
	RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_err_,
		 ("\n free number_%d stainfo with hwaddr=0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n",
		 pstapriv->asoc_sta_count, psta->hwaddr[0], psta->hwaddr[1],
		 psta->hwaddr[2], psta->hwaddr[3], psta->hwaddr[4],
		 psta->hwaddr[5]));
	pstapriv->asoc_sta_count--;

	/*  re-init sta_info; 20061114 */
	_rtw_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_rtw_init_sta_recv_priv(&psta->sta_recvpriv);

	del_समयr_sync(&psta->addba_retry_समयr);

	/* क्रम A-MPDU Rx reordering buffer control, cancel
	 * reordering_ctrl_समयr
	 */
	क्रम (i = 0; i < 16; i++) अणु
		काष्ठा list_head *phead, *plist;
		काष्ठा recv_frame *prframe;
		काष्ठा __queue *ppending_recvframe_queue;
		काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

		preorder_ctrl = &psta->recvreorder_ctrl[i];

		del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);

		ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

		spin_lock_bh(&ppending_recvframe_queue->lock);

		phead = get_list_head(ppending_recvframe_queue);
		plist = phead->next;

		जबतक (!list_empty(phead)) अणु
			prframe = container_of(plist, काष्ठा recv_frame, list);

			plist = plist->next;

			list_del_init(&prframe->list);

			rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
		पूर्ण

		spin_unlock_bh(&ppending_recvframe_queue->lock);
	पूर्ण

	अगर (!(psta->state & WIFI_AP_STATE))
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, false);

#अगर_घोषित CONFIG_88EU_AP_MODE

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

#पूर्ण_अगर	/*  CONFIG_88EU_AP_MODE */

	spin_lock_bh(&pमुक्त_sta_queue->lock);
	list_add_tail(&psta->list, get_list_head(pमुक्त_sta_queue));
	spin_unlock_bh(&pमुक्त_sta_queue->lock);

निकास:

	वापस _SUCCESS;
पूर्ण

/*  मुक्त all stainfo which in sta_hash[all] */
व्योम rtw_मुक्त_all_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *plist, *phead;
	s32 index;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *pbcmc_stainfo = rtw_get_bcmc_stainfo(padapter);

	अगर (pstapriv->asoc_sta_count == 1)
		वापस;

	spin_lock_bh(&pstapriv->sta_hash_lock);

	क्रम (index = 0; index < NUM_STA; index++) अणु
		phead = &pstapriv->sta_hash[index];
		plist = phead->next;

		जबतक (phead != plist) अणु
			psta = container_of(plist, काष्ठा sta_info, hash_list);

			plist = plist->next;

			अगर (pbcmc_stainfo != psta)
				rtw_मुक्त_stainfo(padapter, psta);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pstapriv->sta_hash_lock);
पूर्ण

/* any station allocated can be searched by hash list */
काष्ठा sta_info *rtw_get_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा sta_info *psta = शून्य;
	u32 index;
	u8 *addr;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	अगर (!hwaddr)
		वापस शून्य;

	अगर (is_multicast_ether_addr(hwaddr))
		addr = bc_addr;
	अन्यथा
		addr = hwaddr;

	index = wअगरi_mac_hash(addr);

	spin_lock_bh(&pstapriv->sta_hash_lock);

	phead = &pstapriv->sta_hash[index];
	plist = phead->next;

	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, hash_list);

		अगर (!स_भेद(psta->hwaddr, addr, ETH_ALEN)) अणु
			/*  अगर found the matched address */
			अवरोध;
		पूर्ण
		psta = शून्य;
		plist = plist->next;
	पूर्ण

	spin_unlock_bh(&pstapriv->sta_hash_lock);
	वापस psta;
पूर्ण

u32 rtw_init_bcmc_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_info *psta;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	psta = rtw_alloc_stainfo(pstapriv, bc_addr);

	अगर (!psta) अणु
		RT_TRACE(_module_rtl871x_sta_mgt_c_, _drv_err_,
			 ("rtw_alloc_stainfo fail"));
		वापस _FAIL;
	पूर्ण

	/*  शेष broadcast & multicast use macid 1 */
	psta->mac_id = 1;

	वापस _SUCCESS;
पूर्ण

काष्ठा sta_info *rtw_get_bcmc_stainfo(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	वापस rtw_get_stainfo(pstapriv, bc_addr);
पूर्ण

bool rtw_access_ctrl(काष्ठा adapter *padapter, u8 *mac_addr)
अणु
	bool res = true;
#अगर_घोषित CONFIG_88EU_AP_MODE
	काष्ठा list_head *plist, *phead;
	काष्ठा rtw_wlan_acl_node *paclnode;
	bool match = false;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue *pacl_node_q = &pacl_list->acl_node_q;

	spin_lock_bh(&pacl_node_q->lock);
	phead = get_list_head(pacl_node_q);
	plist = phead->next;
	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = plist->next;

		अगर (!स_भेद(paclnode->addr, mac_addr, ETH_ALEN)) अणु
			अगर (paclnode->valid) अणु
				match = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pacl_node_q->lock);

	अगर (pacl_list->mode == 1)/* accept unless in deny list */
		res = !match;
	अन्यथा अगर (pacl_list->mode == 2)/* deny unless in accept list */
		res = match;
	अन्यथा
		res = true;

#पूर्ण_अगर

	वापस res;
पूर्ण
