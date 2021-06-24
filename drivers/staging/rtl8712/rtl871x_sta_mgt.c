<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_sta_mgt.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_STA_MGT_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "xmit_osdep.h"
#समावेश "sta_info.h"

अटल व्योम _init_stainfo(काष्ठा sta_info *psta)
अणु
	स_रखो((u8 *)psta, 0, माप(काष्ठा sta_info));
	spin_lock_init(&psta->lock);
	INIT_LIST_HEAD(&psta->list);
	INIT_LIST_HEAD(&psta->hash_list);
	_r8712_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_r8712_init_sta_recv_priv(&psta->sta_recvpriv);
	INIT_LIST_HEAD(&psta->asoc_list);
	INIT_LIST_HEAD(&psta->auth_list);
पूर्ण

पूर्णांक _r8712_init_sta_priv(काष्ठा	sta_priv *pstapriv)
अणु
	काष्ठा sta_info *psta;
	s32 i;

	pstapriv->pallocated_stainfo_buf = kदो_स्मृति(माप(काष्ठा sta_info) *
						   NUM_STA + 4, GFP_ATOMIC);
	अगर (!pstapriv->pallocated_stainfo_buf)
		वापस -ENOMEM;
	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 -
		((addr_t)(pstapriv->pallocated_stainfo_buf) & 3);
	_init_queue(&pstapriv->मुक्त_sta_queue);
	spin_lock_init(&pstapriv->sta_hash_lock);
	pstapriv->asoc_sta_count = 0;
	_init_queue(&pstapriv->sleep_q);
	_init_queue(&pstapriv->wakeup_q);
	psta = (काष्ठा sta_info *)(pstapriv->pstainfo_buf);
	क्रम (i = 0; i < NUM_STA; i++) अणु
		_init_stainfo(psta);
		INIT_LIST_HEAD(&(pstapriv->sta_hash[i]));
		list_add_tail(&psta->list, &pstapriv->मुक्त_sta_queue.queue);
		psta++;
	पूर्ण
	INIT_LIST_HEAD(&pstapriv->asoc_list);
	INIT_LIST_HEAD(&pstapriv->auth_list);
	वापस 0;
पूर्ण

/* this function is used to मुक्त the memory of lock || sema क्रम all stainfos */
अटल व्योम mमुक्त_all_stainfo(काष्ठा sta_priv *pstapriv)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *plist, *phead;

	spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
	phead = &pstapriv->मुक्त_sta_queue.queue;
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist))
		plist = plist->next;

	spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
पूर्ण

व्योम _r8712_मुक्त_sta_priv(काष्ठा sta_priv *pstapriv)
अणु
	अगर (pstapriv) अणु
		/* be करोne beक्रमe मुक्त sta_hash_lock */
		mमुक्त_all_stainfo(pstapriv);
		kमुक्त(pstapriv->pallocated_stainfo_buf);
	पूर्ण
पूर्ण

काष्ठा sta_info *r8712_alloc_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr)
अणु
	s32	index;
	काष्ठा list_head *phash_list;
	काष्ठा sta_info	*psta;
	काष्ठा  __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	पूर्णांक i = 0;
	u16  wRxSeqInitialValue = 0xffff;
	अचिन्हित दीर्घ flags;

	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;
	spin_lock_irqsave(&pमुक्त_sta_queue->lock, flags);
	psta = list_first_entry_or_null(&pमुक्त_sta_queue->queue,
					काष्ठा sta_info, list);
	अगर (psta) अणु
		list_del_init(&psta->list);
		_init_stainfo(psta);
		स_नकल(psta->hwaddr, hwaddr, ETH_ALEN);
		index = wअगरi_mac_hash(hwaddr);
		अगर (index >= NUM_STA) अणु
			psta = शून्य;
			जाओ निकास;
		पूर्ण
		phash_list = &pstapriv->sta_hash[index];
		list_add_tail(&psta->hash_list, phash_list);
		pstapriv->asoc_sta_count++;

/* For the SMC router, the sequence number of first packet of WPS handshake
 * will be 0. In this हाल, this packet will be dropped by recv_decache function
 * अगर we use the 0x00 as the शेष value क्रम tid_rxseq variable. So, we
 * initialize the tid_rxseq variable as the 0xffff.
 */
		क्रम (i = 0; i < 16; i++)
			स_नकल(&psta->sta_recvpriv.rxcache.tid_rxseq[i],
				&wRxSeqInitialValue, 2);
		/* क्रम A-MPDU Rx reordering buffer control */
		क्रम (i = 0; i < 16; i++) अणु
			preorder_ctrl = &psta->recvreorder_ctrl[i];
			preorder_ctrl->padapter = pstapriv->padapter;
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
			preorder_ctrl->wsize_b = 64;
			_init_queue(&preorder_ctrl->pending_recvframe_queue);
			r8712_init_recv_समयr(preorder_ctrl);
		पूर्ण
	पूर्ण
निकास:
	spin_unlock_irqrestore(&pमुक्त_sta_queue->lock, flags);
	वापस psta;
पूर्ण

/* using pstapriv->sta_hash_lock to protect */
व्योम r8712_मुक्त_stainfo(काष्ठा _adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ irqL0;
	काष्ठा  __queue *pमुक्त_sta_queue;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा	sta_xmit_priv *pstaxmitpriv;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;

	अगर (!psta)
		वापस;
	pमुक्त_sta_queue = &pstapriv->मुक्त_sta_queue;
	pstaxmitpriv = &psta->sta_xmitpriv;
	spin_lock_irqsave(&(pxmitpriv->vo_pending.lock), irqL0);
	r8712_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vo_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vo_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->vo_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->vi_pending.lock), irqL0);
	r8712_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vi_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vi_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->vi_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->bk_pending.lock), irqL0);
	r8712_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->bk_q.sta_pending);
	list_del_init(&(pstaxmitpriv->bk_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->bk_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->be_pending.lock), irqL0);
	r8712_मुक्त_xmitframe_queue(pxmitpriv, &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&(pstaxmitpriv->be_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->be_pending.lock), irqL0);
	list_del_init(&psta->hash_list);
	pstapriv->asoc_sta_count--;
	/* re-init sta_info; 20061114 */
	_r8712_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_r8712_init_sta_recv_priv(&psta->sta_recvpriv);
	/* क्रम A-MPDU Rx reordering buffer control,
	 * cancel reordering_ctrl_समयr
	 */
	क्रम (i = 0; i < 16; i++) अणु
		preorder_ctrl = &psta->recvreorder_ctrl[i];
		del_समयr(&preorder_ctrl->reordering_ctrl_समयr);
	पूर्ण
	spin_lock(&(pमुक्त_sta_queue->lock));
	/* insert पूर्णांकo मुक्त_sta_queue; 20061114 */
	list_add_tail(&psta->list, &pमुक्त_sta_queue->queue);
	spin_unlock(&(pमुक्त_sta_queue->lock));
पूर्ण

/* मुक्त all stainfo which in sta_hash[all] */
व्योम r8712_मुक्त_all_stainfo(काष्ठा _adapter *padapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *plist, *phead;
	s32 index;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *pbcmc_stainfo = r8712_get_bcmc_stainfo(padapter);

	अगर (pstapriv->asoc_sta_count == 1)
		वापस;
	spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
	क्रम (index = 0; index < NUM_STA; index++) अणु
		phead = &(pstapriv->sta_hash[index]);
		plist = phead->next;
		जबतक (!end_of_queue_search(phead, plist)) अणु
			psta = container_of(plist,
					    काष्ठा sta_info, hash_list);
			plist = plist->next;
			अगर (pbcmc_stainfo != psta)
				r8712_मुक्त_stainfo(padapter, psta);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
पूर्ण

/* any station allocated can be searched by hash list */
काष्ठा sta_info *r8712_get_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr)
अणु
	अचिन्हित दीर्घ	 irqL;
	काष्ठा list_head *plist, *phead;
	काष्ठा sta_info *psta = शून्य;
	u32	index;

	अगर (!hwaddr)
		वापस शून्य;
	index = wअगरi_mac_hash(hwaddr);
	spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
	phead = &(pstapriv->sta_hash[index]);
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		psta = container_of(plist, काष्ठा sta_info, hash_list);
		अगर ((!स_भेद(psta->hwaddr, hwaddr, ETH_ALEN))) अणु
			/* अगर found the matched address */
			अवरोध;
		पूर्ण
		psta = शून्य;
		plist = plist->next;
	पूर्ण
	spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
	वापस psta;
पूर्ण

व्योम r8712_init_bcmc_stainfo(काष्ठा _adapter *padapter)
अणु
	अचिन्हित अक्षर bcast_addr[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;

	r8712_alloc_stainfo(pstapriv, bcast_addr);
पूर्ण

काष्ठा sta_info *r8712_get_bcmc_stainfo(काष्ठा _adapter *padapter)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	वापस r8712_get_stainfo(pstapriv, bc_addr);
पूर्ण


u8 r8712_access_ctrl(काष्ठा wlan_acl_pool *pacl_list, u8 *mac_addr)
अणु
	वापस true;
पूर्ण
