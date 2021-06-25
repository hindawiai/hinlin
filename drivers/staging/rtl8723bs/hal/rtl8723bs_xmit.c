<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8723BS_XMIT_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>

अटल u8 rtw_sdio_रुको_enough_TxOQT_space(काष्ठा adapter *padapter, u8 agg_num)
अणु
	u32 n = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	जबतक (pHalData->SdioTxOQTFreeSpace < agg_num) अणु
		अगर (
			(padapter->bSurpriseRemoved) ||
			(padapter->bDriverStopped)
		)
			वापस false;

		HalQueryTxOQTBufferStatus8723BSdio(padapter);

		अगर ((++n % 60) == 0) अणु
			msleep(1);
			/* yield(); */
		पूर्ण
	पूर्ण

	pHalData->SdioTxOQTFreeSpace -= agg_num;

	/* अगर (n > 1) */
	/* 	++priv->pshare->nr_out_of_txoqt_space; */

	वापस true;
पूर्ण

अटल s32 rtl8723_dequeue_ग_लिखोport(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा adapter *pri_padapter = padapter;
	s32 ret = 0;
	u8 PageIdx = 0;
	u32 deviceId;
	u8 bUpdatePageNum = false;

	ret = ret || check_fwstate(pmlmepriv, _FW_UNDER_SURVEY);

	अगर (ret)
		pxmitbuf = dequeue_pending_xmitbuf_under_survey(pxmitpriv);
	अन्यथा
		pxmitbuf = dequeue_pending_xmitbuf(pxmitpriv);

	अगर (!pxmitbuf)
		वापस true;

	deviceId = ffaddr2deviceId(pdvobjpriv, pxmitbuf->ff_hwaddr);

	/*  translate fअगरo addr to queue index */
	चयन (deviceId) अणु
	हाल WLAN_TX_HIQ_DEVICE_ID:
		PageIdx = HI_QUEUE_IDX;
		अवरोध;

	हाल WLAN_TX_MIQ_DEVICE_ID:
		PageIdx = MID_QUEUE_IDX;
		अवरोध;

	हाल WLAN_TX_LOQ_DEVICE_ID:
		PageIdx = LOW_QUEUE_IDX;
		अवरोध;
	पूर्ण

query_मुक्त_page:
	/*  check अगर hardware tx fअगरo page is enough */
	अगर (!rtw_hal_sdio_query_tx_मुक्तpage(pri_padapter, PageIdx, pxmitbuf->pg_num)) अणु
		अगर (!bUpdatePageNum) अणु
			/*  Total number of page is NOT available, so update current FIFO status */
			HalQueryTxBufferStatus8723BSdio(padapter);
			bUpdatePageNum = true;
			जाओ query_मुक्त_page;
		पूर्ण अन्यथा अणु
			bUpdatePageNum = false;
			enqueue_pending_xmitbuf_to_head(pxmitpriv, pxmitbuf);
			वापस true;
		पूर्ण
	पूर्ण

	अगर (
		(padapter->bSurpriseRemoved) ||
		(padapter->bDriverStopped)
	)
		जाओ मुक्त_xmitbuf;

	अगर (rtw_sdio_रुको_enough_TxOQT_space(padapter, pxmitbuf->agg_num) == false)
		जाओ मुक्त_xmitbuf;

	traffic_check_क्रम_leave_lps(padapter, true, pxmitbuf->agg_num);

	rtw_ग_लिखो_port(padapter, deviceId, pxmitbuf->len, (u8 *)pxmitbuf);

	rtw_hal_sdio_update_tx_मुक्तpage(pri_padapter, PageIdx, pxmitbuf->pg_num);

मुक्त_xmitbuf:
	/* rtw_मुक्त_xmitframe(pxmitpriv, pframe); */
	/* pxmitbuf->priv_data = शून्य; */
	rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);

	वापस _FAIL;
पूर्ण

/*
 * Description
 *Transmit xmitbuf to hardware tx fअगरo
 *
 * Return
 *_SUCCESS	ok
 *_FAIL		something error
 */
s32 rtl8723bs_xmit_buf_handler(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv;
	u8 queue_empty, queue_pending;
	s32 ret;


	pxmitpriv = &padapter->xmitpriv;

	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&pxmitpriv->xmit_comp)) अणु
		netdev_emerg(padapter->pnetdev,
			     "%s: down SdioXmitBufSema fail!\n", __func__);
		वापस _FAIL;
	पूर्ण

	ret = (padapter->bDriverStopped) || (padapter->bSurpriseRemoved);
	अगर (ret)
		वापस _FAIL;

	queue_pending = check_pending_xmitbuf(pxmitpriv);

	अगर (!queue_pending)
		वापस _SUCCESS;

	ret = rtw_रेजिस्टर_tx_alive(padapter);
	अगर (ret != _SUCCESS) अणु
		वापस _SUCCESS;
	पूर्ण

	करो अणु
		queue_empty = rtl8723_dequeue_ग_लिखोport(padapter);
/* 	dump secondary adapter xmitbuf */
	पूर्ण जबतक (!queue_empty);

	rtw_unरेजिस्टर_tx_alive(padapter);

	वापस _SUCCESS;
पूर्ण

/*
 * Description:
 *Aggregation packets and send to hardware
 *
 * Return:
 *0	Success
 *-1	Hardware resource(TX FIFO) not पढ़ोy
 *-2	Software resource(xmitbuf) not पढ़ोy
 */
अटल s32 xmit_xmitframes(काष्ठा adapter *padapter, काष्ठा xmit_priv *pxmitpriv)
अणु
	s32 err, ret;
	u32 k = 0;
	काष्ठा hw_xmit *hwxmits, *phwxmit;
	u8 idx, hwentry;
	काष्ठा tx_servq *ptxservq;
	काष्ठा list_head *sta_plist, *sta_phead, *frame_plist, *frame_phead;
	काष्ठा xmit_frame *pxmitframe;
	काष्ठा __queue *pframe_queue;
	काष्ठा xmit_buf *pxmitbuf;
	u32 txlen, max_xmit_len;
	u8 txdesc_size = TXDESC_SIZE;
	पूर्णांक inx[4];

	err = 0;
	hwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;
	ptxservq = शून्य;
	pxmitframe = शून्य;
	pframe_queue = शून्य;
	pxmitbuf = शून्य;

	अगर (padapter->registrypriv.wअगरi_spec == 1) अणु
		क्रम (idx = 0; idx < 4; idx++)
			inx[idx] = pxmitpriv->wmm_para_seq[idx];
	पूर्ण अन्यथा अणु
		inx[0] = 0;
		inx[1] = 1;
		inx[2] = 2;
		inx[3] = 3;
	पूर्ण

	/*  0(VO), 1(VI), 2(BE), 3(BK) */
	क्रम (idx = 0; idx < hwentry; idx++) अणु
		phwxmit = hwxmits + inx[idx];

		अगर (
			(check_pending_xmitbuf(pxmitpriv)) &&
			(padapter->mlmepriv.LinkDetectInfo.bHigherBusyTxTraffic)
		) अणु
			अगर ((phwxmit->accnt > 0) && (phwxmit->accnt < 5)) अणु
				err = -2;
				अवरोध;
			पूर्ण
		पूर्ण

		max_xmit_len = rtw_hal_get_sdio_tx_max_length(padapter, inx[idx]);

		spin_lock_bh(&pxmitpriv->lock);

		sta_phead = get_list_head(phwxmit->sta_queue);
		sta_plist = get_next(sta_phead);
		/* because stop_sta_xmit may delete sta_plist at any समय */
		/* so we should add lock here, or जबतक loop can not निकास */
		जबतक (sta_phead != sta_plist) अणु
			ptxservq = container_of(sta_plist, काष्ठा tx_servq, tx_pending);
			sta_plist = get_next(sta_plist);

			pframe_queue = &ptxservq->sta_pending;

			frame_phead = get_list_head(pframe_queue);

			जबतक (list_empty(frame_phead) == false) अणु
				frame_plist = get_next(frame_phead);
				pxmitframe = container_of(frame_plist, काष्ठा xmit_frame, list);

				/*  check xmit_buf size enough or not */
				txlen = txdesc_size + rtw_wlan_pkt_size(pxmitframe);
				अगर (!pxmitbuf ||
					((_RND(pxmitbuf->len, 8) + txlen) > max_xmit_len) ||
					(k >= (rtw_hal_sdio_max_txoqt_मुक्त_space(padapter) - 1))
				) अणु
					अगर (pxmitbuf) अणु
						/* pxmitbuf->priv_data will be शून्य, and will crash here */
						अगर (pxmitbuf->len > 0 &&
						    pxmitbuf->priv_data) अणु
							काष्ठा xmit_frame *pframe;
							pframe = (काष्ठा xmit_frame *)pxmitbuf->priv_data;
							pframe->agg_num = k;
							pxmitbuf->agg_num = k;
							rtl8723b_update_txdesc(pframe, pframe->buf_addr);
							rtw_मुक्त_xmitframe(pxmitpriv, pframe);
							pxmitbuf->priv_data = शून्य;
							enqueue_pending_xmitbuf(pxmitpriv, pxmitbuf);
							/* can not yield under lock */
							/* yield(); */
						पूर्ण अन्यथा
							rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
					पूर्ण

					pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
					अगर (!pxmitbuf) अणु
#अगर_घोषित DBG_XMIT_BUF
						netdev_err(padapter->pnetdev,
							   "%s: xmit_buf is not enough!\n",
							   __func__);
#पूर्ण_अगर
						err = -2;
						complete(&(pxmitpriv->xmit_comp));
						अवरोध;
					पूर्ण
					k = 0;
				पूर्ण

				/*  ok to send, हटाओ frame from queue */
				अगर (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true)
					अगर (
						(pxmitframe->attrib.psta->state & WIFI_SLEEP_STATE) &&
						(pxmitframe->attrib.triggered == 0)
					)
						अवरोध;

				list_del_init(&pxmitframe->list);
				ptxservq->qcnt--;
				phwxmit->accnt--;

				अगर (k == 0) अणु
					pxmitbuf->ff_hwaddr = rtw_get_ff_hwaddr(pxmitframe);
					pxmitbuf->priv_data = (u8 *)pxmitframe;
				पूर्ण

				/*  coalesce the xmitframe to xmitbuf */
				pxmitframe->pxmitbuf = pxmitbuf;
				pxmitframe->buf_addr = pxmitbuf->ptail;

				ret = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
				अगर (ret == _FAIL) अणु
					netdev_err(padapter->pnetdev,
						   "%s: coalesce FAIL!",
						   __func__);
					/*  Toकरो: error handler */
				पूर्ण अन्यथा अणु
					k++;
					अगर (k != 1)
						rtl8723b_update_txdesc(pxmitframe, pxmitframe->buf_addr);
					rtw_count_tx_stats(padapter, pxmitframe, pxmitframe->attrib.last_txcmdsz);

					txlen = txdesc_size + pxmitframe->attrib.last_txcmdsz;
					pxmitframe->pg_num = (txlen + 127) / 128;
					pxmitbuf->pg_num += (txlen + 127) / 128;
				    /* अगर (k != 1) */
					/* 	((काष्ठा xmit_frame*)pxmitbuf->priv_data)->pg_num += pxmitframe->pg_num; */
					pxmitbuf->ptail += _RND(txlen, 8); /*  round to 8 bytes alignment */
					pxmitbuf->len = _RND(pxmitbuf->len, 8) + txlen;
				पूर्ण

				अगर (k != 1)
					rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
				pxmitframe = शून्य;
			पूर्ण

			अगर (list_empty(&pframe_queue->queue))
				list_del_init(&ptxservq->tx_pending);

			अगर (err)
				अवरोध;
		पूर्ण
		spin_unlock_bh(&pxmitpriv->lock);

		/*  dump xmit_buf to hw tx fअगरo */
		अगर (pxmitbuf) अणु
			अगर (pxmitbuf->len > 0) अणु
				काष्ठा xmit_frame *pframe;
				pframe = (काष्ठा xmit_frame *)pxmitbuf->priv_data;
				pframe->agg_num = k;
				pxmitbuf->agg_num = k;
				rtl8723b_update_txdesc(pframe, pframe->buf_addr);
				rtw_मुक्त_xmitframe(pxmitpriv, pframe);
				pxmitbuf->priv_data = शून्य;
				enqueue_pending_xmitbuf(pxmitpriv, pxmitbuf);
				yield();
			पूर्ण अन्यथा
				rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
			pxmitbuf = शून्य;
		पूर्ण

		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * Description
 *Transmit xmitframe from queue
 *
 * Return
 *_SUCCESS	ok
 *_FAIL		something error
 */
अटल s32 rtl8723bs_xmit_handler(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv;
	s32 ret;


	pxmitpriv = &padapter->xmitpriv;

	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&pxmitpriv->SdioXmitStart)) अणु
		netdev_emerg(padapter->pnetdev, "%s: SdioXmitStart fail!\n",
			     __func__);
		वापस _FAIL;
	पूर्ण

next:
	अगर (
		(padapter->bDriverStopped) ||
		(padapter->bSurpriseRemoved)
	)
		वापस _FAIL;

	spin_lock_bh(&pxmitpriv->lock);
	ret = rtw_txframes_pending(padapter);
	spin_unlock_bh(&pxmitpriv->lock);
	अगर (ret == 0) अणु
		वापस _SUCCESS;
	पूर्ण

	/*  dequeue frame and ग_लिखो to hardware */

	ret = xmit_xmitframes(padapter, pxmitpriv);
	अगर (ret == -2) अणु
		/* here sleep 1ms will cause big TP loss of TX */
		/* from 50+ to 40+ */
		अगर (padapter->registrypriv.wअगरi_spec)
			msleep(1);
		अन्यथा
			yield();
		जाओ next;
	पूर्ण

	spin_lock_bh(&pxmitpriv->lock);
	ret = rtw_txframes_pending(padapter);
	spin_unlock_bh(&pxmitpriv->lock);
	अगर (ret == 1) अणु
		जाओ next;
	पूर्ण

	वापस _SUCCESS;
पूर्ण

पूर्णांक rtl8723bs_xmit_thपढ़ो(व्योम *context)
अणु
	s32 ret;
	काष्ठा adapter *padapter;
	काष्ठा xmit_priv *pxmitpriv;
	u8 thपढ़ो_name[20];

	ret = _SUCCESS;
	padapter = context;
	pxmitpriv = &padapter->xmitpriv;

	rtw_प्र_लिखो(thपढ़ो_name, 20, "RTWHALXT-%s", ADPT_ARG(padapter));
	thपढ़ो_enter(thपढ़ो_name);

	करो अणु
		ret = rtl8723bs_xmit_handler(padapter);
		अगर (संकेत_pending(current)) अणु
			flush_संकेतs(current);
		पूर्ण
	पूर्ण जबतक (_SUCCESS == ret);

	complete(&pxmitpriv->SdioXmitTerminate);

	thपढ़ो_निकास();
पूर्ण

s32 rtl8723bs_mgnt_xmit(
	काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe
)
अणु
	s32 ret = _SUCCESS;
	काष्ठा pkt_attrib *pattrib;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);
	u8 *pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	u8 txdesc_size = TXDESC_SIZE;

	pattrib = &pmgntframe->attrib;
	pxmitbuf = pmgntframe->pxmitbuf;

	rtl8723b_update_txdesc(pmgntframe, pmgntframe->buf_addr);

	pxmitbuf->len = txdesc_size + pattrib->last_txcmdsz;
	pxmitbuf->pg_num = (pxmitbuf->len + 127) / 128; /*  128 is tx page size */
	pxmitbuf->ptail = pmgntframe->buf_addr + pxmitbuf->len;
	pxmitbuf->ff_hwaddr = rtw_get_ff_hwaddr(pmgntframe);

	rtw_count_tx_stats(padapter, pmgntframe, pattrib->last_txcmdsz);

	rtw_मुक्त_xmitframe(pxmitpriv, pmgntframe);

	pxmitbuf->priv_data = शून्य;

	अगर (GetFrameSubType(pframe) == WIFI_BEACON) अणु /* dump beacon directly */
		ret = rtw_ग_लिखो_port(padapter, pdvobjpriv->Queue2Pipe[pxmitbuf->ff_hwaddr], pxmitbuf->len, (u8 *)pxmitbuf);
		अगर (ret != _SUCCESS)
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_WRITE_PORT_ERR);

		rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
	पूर्ण अन्यथा
		enqueue_pending_xmitbuf(pxmitpriv, pxmitbuf);

	वापस ret;
पूर्ण

/*
 * Description:
 *Handle xmitframe(packet) come from rtw_xmit()
 *
 * Return:
 *true	dump packet directly ok
 *false	enqueue, temporary can't transmit packets to hardware
 */
s32 rtl8723bs_hal_xmit(
	काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe
)
अणु
	काष्ठा xmit_priv *pxmitpriv;
	s32 err;


	pxmitframe->attrib.qsel = pxmitframe->attrib.priority;
	pxmitpriv = &padapter->xmitpriv;

	अगर (
		(pxmitframe->frame_tag == DATA_FRAMETAG) &&
		(pxmitframe->attrib.ether_type != 0x0806) &&
		(pxmitframe->attrib.ether_type != 0x888e) &&
		(pxmitframe->attrib.dhcp_pkt != 1)
	) अणु
		अगर (padapter->mlmepriv.LinkDetectInfo.bBusyTraffic)
			rtw_issue_addbareq_cmd(padapter, pxmitframe);
	पूर्ण

	spin_lock_bh(&pxmitpriv->lock);
	err = rtw_xmitframe_enqueue(padapter, pxmitframe);
	spin_unlock_bh(&pxmitpriv->lock);
	अगर (err != _SUCCESS) अणु
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

		pxmitpriv->tx_drop++;
		वापस true;
	पूर्ण

	complete(&pxmitpriv->SdioXmitStart);

	वापस false;
पूर्ण

s32	rtl8723bs_hal_xmitframe_enqueue(
	काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe
)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	s32 err;

	err = rtw_xmitframe_enqueue(padapter, pxmitframe);
	अगर (err != _SUCCESS) अणु
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

		pxmitpriv->tx_drop++;
	पूर्ण अन्यथा अणु
		complete(&pxmitpriv->SdioXmitStart);
	पूर्ण

	वापस err;

पूर्ण

/*
 * Return
 *_SUCCESS	start thपढ़ो ok
 *_FAIL		start thपढ़ो fail
 *
 */
s32 rtl8723bs_init_xmit_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *xmitpriv = &padapter->xmitpriv;
	काष्ठा hal_com_data *phal;


	phal = GET_HAL_DATA(padapter);

	spin_lock_init(&phal->SdioTxFIFOFreePageLock);
	init_completion(&xmitpriv->SdioXmitStart);
	init_completion(&xmitpriv->SdioXmitTerminate);

	वापस _SUCCESS;
पूर्ण

व्योम rtl8723bs_मुक्त_xmit_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा __queue *pqueue;
	काष्ठा list_head *plist, *phead;
	काष्ठा list_head पंचांगplist;


	pxmitpriv = &padapter->xmitpriv;
	pqueue = &pxmitpriv->pending_xmitbuf_queue;
	phead = get_list_head(pqueue);
	INIT_LIST_HEAD(&पंचांगplist);

	spin_lock_bh(&pqueue->lock);
	अगर (!list_empty(&pqueue->queue)) अणु
		/*  Insert पंचांगplist to end of queue, and delete phead */
		/*  then पंचांगplist become head of queue. */
		list_add_tail(&पंचांगplist, phead);
		list_del_init(phead);
	पूर्ण
	spin_unlock_bh(&pqueue->lock);

	phead = &पंचांगplist;
	जबतक (list_empty(phead) == false) अणु
		plist = get_next(phead);
		list_del_init(plist);

		pxmitbuf = container_of(plist, काष्ठा xmit_buf, list);
		rtw_मुक्त_xmitframe(pxmitpriv, (काष्ठा xmit_frame *)pxmitbuf->priv_data);
		pxmitbuf->priv_data = शून्य;
		rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
	पूर्ण
पूर्ण
