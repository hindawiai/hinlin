<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8723BS_RECV_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>

अटल व्योम initrecvbuf(काष्ठा recv_buf *precvbuf, काष्ठा adapter *padapter)
अणु
	INIT_LIST_HEAD(&precvbuf->list);
	spin_lock_init(&precvbuf->recvbuf_lock);

	precvbuf->adapter = padapter;
पूर्ण

अटल व्योम update_recvframe_attrib(काष्ठा adapter *padapter,
				    जोड़ recv_frame *precvframe,
				    काष्ठा recv_stat *prxstat)
अणु
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा recv_stat report;
	काष्ठा rxreport_8723b *prxreport = (काष्ठा rxreport_8723b *)&report;

	report.rxdw0 = prxstat->rxdw0;
	report.rxdw1 = prxstat->rxdw1;
	report.rxdw2 = prxstat->rxdw2;
	report.rxdw3 = prxstat->rxdw3;
	report.rxdw4 = prxstat->rxdw4;
	report.rxdw5 = prxstat->rxdw5;

	pattrib = &precvframe->u.hdr.attrib;
	स_रखो(pattrib, 0, माप(काष्ठा rx_pkt_attrib));

	/*  update rx report to recv_frame attribute */
	pattrib->pkt_rpt_type = prxreport->c2h_ind ? C2H_PACKET : NORMAL_RX;

	अगर (pattrib->pkt_rpt_type == NORMAL_RX) अणु
		/*  Normal rx packet */
		/*  update rx report to recv_frame attribute */
		pattrib->pkt_len = (u16)prxreport->pktlen;
		pattrib->drvinfo_sz = (u8)(prxreport->drvinfosize << 3);
		pattrib->physt = (u8)prxreport->physt;

		pattrib->crc_err = (u8)prxreport->crc32;
		pattrib->icv_err = (u8)prxreport->icverr;

		pattrib->bdecrypted = (u8)(prxreport->swdec ? 0 : 1);
		pattrib->encrypt = (u8)prxreport->security;

		pattrib->qos = (u8)prxreport->qos;
		pattrib->priority = (u8)prxreport->tid;

		pattrib->amsdu = (u8)prxreport->amsdu;

		pattrib->seq_num = (u16)prxreport->seq;
		pattrib->frag_num = (u8)prxreport->frag;
		pattrib->mfrag = (u8)prxreport->mf;
		pattrib->mdata = (u8)prxreport->md;

		pattrib->data_rate = (u8)prxreport->rx_rate;
	पूर्ण अन्यथा अणु
		pattrib->pkt_len = (u16)prxreport->pktlen;
	पूर्ण
पूर्ण

/*
 * Notice:
 *Beक्रमe calling this function,
 *precvframe->u.hdr.rx_data should be पढ़ोy!
 */
अटल व्योम update_recvframe_phyinfo(जोड़ recv_frame *precvframe,
				     काष्ठा phy_stat *pphy_status)
अणु
	काष्ठा adapter *padapter = precvframe->u.hdr.adapter;
	काष्ठा rx_pkt_attrib *pattrib = &precvframe->u.hdr.attrib;
	काष्ठा hal_com_data *p_hal_data = GET_HAL_DATA(padapter);
	काष्ठा odm_phy_info *p_phy_info =
		(काष्ठा odm_phy_info *)(&pattrib->phy_info);

	u8 *wlanhdr;
	u8 *my_bssid;
	u8 *rx_bssid;
	u8 *rx_ra;
	u8 *my_hwaddr;
	u8 *sa = शून्य;

	काष्ठा odm_packet_info pkt_info = अणु
		.data_rate   = 0x00,
		.station_id  = 0x00,
		.bssid_match = false,
		.to_self     = false,
		.is_beacon   = false,
	पूर्ण;

	/* अचिन्हित दीर्घ		irqL; */
	काष्ठा sta_priv *pstapriv;
	काष्ठा sta_info *psta;

	wlanhdr = get_recvframe_data(precvframe);
	my_bssid = get_bssid(&padapter->mlmepriv);
	rx_bssid = get_hdr_bssid(wlanhdr);
	pkt_info.bssid_match = ((!IsFrameTypeCtrl(wlanhdr)) &&
				!pattrib->icv_err && !pattrib->crc_err &&
				ether_addr_equal(rx_bssid, my_bssid));

	rx_ra = get_ra(wlanhdr);
	my_hwaddr = myid(&padapter->eeprompriv);
	pkt_info.to_self = pkt_info.bssid_match &&
		ether_addr_equal(rx_ra, my_hwaddr);


	pkt_info.is_beacon = pkt_info.bssid_match &&
		(GetFrameSubType(wlanhdr) == WIFI_BEACON);

	sa = get_ta(wlanhdr);

	pkt_info.station_id = 0xFF;

	pstapriv = &padapter->stapriv;
	psta = rtw_get_stainfo(pstapriv, sa);
	अगर (psta)
		pkt_info.station_id = psta->mac_id;

	pkt_info.data_rate = pattrib->data_rate;

	/* rtl8723b_query_rx_phy_status(precvframe, pphy_status); */
	/* spin_lock_bh(&p_hal_data->odm_stainfo_lock); */
	ODM_PhyStatusQuery(&p_hal_data->odmpriv, p_phy_info,
			   (u8 *)pphy_status, &(pkt_info));
	अगर (psta)
		psta->rssi = pattrib->phy_info.RecvSignalPower;
	/* spin_unlock_bh(&p_hal_data->odm_stainfo_lock); */
	precvframe->u.hdr.psta = शून्य;
	अगर (
		pkt_info.bssid_match &&
		(check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true)
	) अणु
		अगर (psta) अणु
			precvframe->u.hdr.psta = psta;
			rtl8723b_process_phy_info(padapter, precvframe);
		पूर्ण
	पूर्ण अन्यथा अगर (pkt_info.to_self || pkt_info.is_beacon) अणु
		u32 adhoc_state = WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE;
		अगर (check_fwstate(&padapter->mlmepriv, adhoc_state))
			अगर (psta)
				precvframe->u.hdr.psta = psta;
		rtl8723b_process_phy_info(padapter, precvframe);
	पूर्ण
पूर्ण

अटल व्योम rtl8723bs_c2h_packet_handler(काष्ठा adapter *padapter,
					 u8 *pbuf, u16 length)
अणु
	u8 *पंचांगp = शून्य;
	u8 res = false;

	अगर (length == 0)
		वापस;

	पंचांगp = rtw_zदो_स्मृति(length);
	अगर (!पंचांगp)
		वापस;

	स_नकल(पंचांगp, pbuf, length);

	res = rtw_c2h_packet_wk_cmd(padapter, पंचांगp, length);

	अगर (!res)
		kमुक्त(पंचांगp);
पूर्ण

अटल अंतरभूत जोड़ recv_frame *try_alloc_recvframe(काष्ठा recv_priv *precvpriv,
						    काष्ठा recv_buf *precvbuf)
अणु
	जोड़ recv_frame *precvframe;

	precvframe = rtw_alloc_recvframe(&precvpriv->मुक्त_recv_queue);
	अगर (!precvframe) अणु
		rtw_enqueue_recvbuf_to_head(precvbuf,
					    &precvpriv->recv_buf_pending_queue);

		/*  The हाल of can't allocate recvframe should be temporary, */
		/*  schedule again and hope recvframe is available next समय. */
		tasklet_schedule(&precvpriv->recv_tasklet);
	पूर्ण

	वापस precvframe;
पूर्ण

अटल अंतरभूत bool rx_crc_err(काष्ठा recv_priv *precvpriv,
			      काष्ठा hal_com_data *p_hal_data,
			      काष्ठा rx_pkt_attrib *pattrib,
			      जोड़ recv_frame *precvframe)
अणु
	/*  fix Hardware RX data error, drop whole recv_buffer */
	अगर ((!(p_hal_data->ReceiveConfig & RCR_ACRC32)) && pattrib->crc_err) अणु
		rtw_मुक्त_recvframe(precvframe, &precvpriv->मुक्त_recv_queue);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool pkt_exceeds_tail(काष्ठा recv_priv *precvpriv,
				    u8 *end, u8 *tail,
				    जोड़ recv_frame *precvframe)
अणु
	अगर (end > tail) अणु
		rtw_मुक्त_recvframe(precvframe, &precvpriv->मुक्त_recv_queue);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम rtl8723bs_recv_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा adapter *padapter = from_tasklet(padapter, t,
						recvpriv.recv_tasklet);
	काष्ठा hal_com_data *p_hal_data;
	काष्ठा recv_priv *precvpriv;
	काष्ठा recv_buf *precvbuf;
	जोड़ recv_frame *precvframe;
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा __queue *recv_buf_queue;
	u8 *ptr;
	u32 pkt_offset, skb_len, alloc_sz;
	काष्ठा sk_buff *pkt_copy = शून्य;
	u8 shअगरt_sz = 0, rx_report_sz = 0;

	p_hal_data = GET_HAL_DATA(padapter);
	precvpriv = &padapter->recvpriv;
	recv_buf_queue = &precvpriv->recv_buf_pending_queue;

	करो अणु
		precvbuf = rtw_dequeue_recvbuf(recv_buf_queue);
		अगर (!precvbuf)
			अवरोध;

		ptr = precvbuf->pdata;

		जबतक (ptr < precvbuf->ptail) अणु
			precvframe = try_alloc_recvframe(precvpriv, precvbuf);
			अगर (!precvframe)
				वापस;

			/* rx desc parsing */
			update_recvframe_attrib(padapter, precvframe,
						(काष्ठा recv_stat *)ptr);

			pattrib = &precvframe->u.hdr.attrib;

			अगर (rx_crc_err(precvpriv, p_hal_data,
				       pattrib, precvframe))
				अवरोध;

			rx_report_sz = RXDESC_SIZE + pattrib->drvinfo_sz;
			pkt_offset = rx_report_sz +
				pattrib->shअगरt_sz +
				pattrib->pkt_len;

			अगर (pkt_exceeds_tail(precvpriv, ptr + pkt_offset,
					     precvbuf->ptail, precvframe))
				अवरोध;

			अगर ((pattrib->crc_err) || (pattrib->icv_err)) अणु
				rtw_मुक्त_recvframe(precvframe,
						   &precvpriv->मुक्त_recv_queue);
			पूर्ण अन्यथा अणु
				/* 	Modअगरied by Albert 20101213 */
				/* 	For 8 bytes IP header alignment. */
				अगर (pattrib->qos)	/* 	Qos data, wireless lan header length is 26 */
					shअगरt_sz = 6;
				अन्यथा
					shअगरt_sz = 0;

				skb_len = pattrib->pkt_len;

				/*  क्रम first fragment packet, driver need allocate 1536+drvinfo_sz+RXDESC_SIZE to defrag packet. */
				/*  modअगरy alloc_sz क्रम recvive crc error packet by thomas 2011-06-02 */
				अगर ((pattrib->mfrag == 1) && (pattrib->frag_num == 0)) अणु
					अगर (skb_len <= 1650)
						alloc_sz = 1664;
					अन्यथा
						alloc_sz = skb_len + 14;
				पूर्ण अन्यथा अणु
					alloc_sz = skb_len;
					/* 	6 is क्रम IP header 8 bytes alignment in QoS packet हाल. */
					/* 	8 is क्रम skb->data 4 bytes alignment. */
					alloc_sz += 14;
				पूर्ण

				pkt_copy = rtw_skb_alloc(alloc_sz);
				अगर (!pkt_copy) अणु
					rtw_मुक्त_recvframe(precvframe, &precvpriv->मुक्त_recv_queue);
					अवरोध;
				पूर्ण

				pkt_copy->dev = padapter->pnetdev;
				precvframe->u.hdr.pkt = pkt_copy;
				skb_reserve(pkt_copy, 8 - ((SIZE_PTR)(pkt_copy->data) & 7));/* क्रमce pkt_copy->data at 8-byte alignment address */
				skb_reserve(pkt_copy, shअगरt_sz);/* क्रमce ip_hdr at 8-byte alignment address according to shअगरt_sz. */
				स_नकल(pkt_copy->data, (ptr + rx_report_sz + pattrib->shअगरt_sz), skb_len);
				precvframe->u.hdr.rx_head = pkt_copy->head;
				precvframe->u.hdr.rx_data = precvframe->u.hdr.rx_tail = pkt_copy->data;
				precvframe->u.hdr.rx_end = skb_end_poपूर्णांकer(pkt_copy);

				recvframe_put(precvframe, skb_len);
				/* recvframe_pull(precvframe, drvinfo_sz + RXDESC_SIZE); */

				अगर (p_hal_data->ReceiveConfig & RCR_APPFCS)
					recvframe_pull_tail(precvframe, IEEE80211_FCS_LEN);

				/*  move to drv info position */
				ptr += RXDESC_SIZE;

				/*  update drv info */
				अगर (p_hal_data->ReceiveConfig & RCR_APP_BA_SSN) अणु
					/* rtl8723s_update_bassn(padapter, pdrvinfo); */
					ptr += 4;
				पूर्ण

				अगर (pattrib->pkt_rpt_type == NORMAL_RX) अणु /* Normal rx packet */
					अगर (pattrib->physt)
						update_recvframe_phyinfo(precvframe, (काष्ठा phy_stat *)ptr);

					rtw_recv_entry(precvframe);
				पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == C2H_PACKET) अणु
					काष्ठा c2h_evt_hdr_t	C2hEvent;

					u16 len_c2h = pattrib->pkt_len;
					u8 *pbuf_c2h = precvframe->u.hdr.rx_data;
					u8 *pdata_c2h;

					C2hEvent.CmdID = pbuf_c2h[0];
					C2hEvent.CmdSeq = pbuf_c2h[1];
					C2hEvent.CmdLen = (len_c2h-2);
					pdata_c2h = pbuf_c2h+2;

					अगर (C2hEvent.CmdID == C2H_CCX_TX_RPT)
						CCX_FwC2HTxRpt_8723b(padapter, pdata_c2h, C2hEvent.CmdLen);
					अन्यथा
						rtl8723bs_c2h_packet_handler(padapter, precvframe->u.hdr.rx_data, pattrib->pkt_len);

					rtw_मुक्त_recvframe(precvframe, &precvpriv->मुक्त_recv_queue);
				पूर्ण
			पूर्ण

			pkt_offset = round_up(pkt_offset, 8);
			precvbuf->pdata += pkt_offset;
			ptr = precvbuf->pdata;
			precvframe = शून्य;
			pkt_copy = शून्य;
		पूर्ण

		rtw_enqueue_recvbuf(precvbuf, &precvpriv->मुक्त_recv_buf_queue);
	पूर्ण जबतक (1);
पूर्ण

/*
 * Initialize recv निजी variable क्रम hardware dependent
 * 1. recv buf
 * 2. recv tasklet
 *
 */
s32 rtl8723bs_init_recv_priv(काष्ठा adapter *padapter)
अणु
	s32 res;
	u32 i, n;
	काष्ठा recv_priv *precvpriv;
	काष्ठा recv_buf *precvbuf;

	res = _SUCCESS;
	precvpriv = &padapter->recvpriv;

	/* 3 1. init recv buffer */
	_rtw_init_queue(&precvpriv->मुक्त_recv_buf_queue);
	_rtw_init_queue(&precvpriv->recv_buf_pending_queue);

	n = NR_RECVBUFF * माप(काष्ठा recv_buf) + 4;
	precvpriv->pallocated_recv_buf = rtw_zदो_स्मृति(n);
	अगर (!precvpriv->pallocated_recv_buf) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	precvpriv->precv_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(precvpriv->pallocated_recv_buf), 4);

	/*  init each recv buffer */
	precvbuf = (काष्ठा recv_buf *)precvpriv->precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		initrecvbuf(precvbuf, padapter);

		अगर (!precvbuf->pskb) अणु
			SIZE_PTR पंचांगpaddr = 0;
			SIZE_PTR alignment = 0;

			precvbuf->pskb = rtw_skb_alloc(MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);

			अगर (precvbuf->pskb) अणु
				precvbuf->pskb->dev = padapter->pnetdev;

				पंचांगpaddr = (SIZE_PTR)precvbuf->pskb->data;
				alignment = पंचांगpaddr & (RECVBUFF_ALIGN_SZ-1);
				skb_reserve(precvbuf->pskb, (RECVBUFF_ALIGN_SZ - alignment));
			पूर्ण
		पूर्ण

		list_add_tail(&precvbuf->list, &precvpriv->मुक्त_recv_buf_queue.queue);

		precvbuf++;
	पूर्ण
	precvpriv->मुक्त_recv_buf_queue_cnt = i;

	अगर (res == _FAIL)
		जाओ initbuख_त्रुटि;

	/* 3 2. init tasklet */
	tasklet_setup(&precvpriv->recv_tasklet, rtl8723bs_recv_tasklet);

	जाओ निकास;

initbuख_त्रुटि:
	precvbuf = (काष्ठा recv_buf *)precvpriv->precv_buf;
	अगर (precvbuf) अणु
		n = precvpriv->मुक्त_recv_buf_queue_cnt;
		precvpriv->मुक्त_recv_buf_queue_cnt = 0;
		क्रम (i = 0; i < n ; i++) अणु
			list_del_init(&precvbuf->list);
			rtw_os_recvbuf_resource_मुक्त(padapter, precvbuf);
			precvbuf++;
		पूर्ण
		precvpriv->precv_buf = शून्य;
	पूर्ण

	kमुक्त(precvpriv->pallocated_recv_buf);
	precvpriv->pallocated_recv_buf = शून्य;

निकास:
	वापस res;
पूर्ण

/*
 * Free recv निजी variable of hardware dependent
 * 1. recv buf
 * 2. recv tasklet
 *
 */
व्योम rtl8723bs_मुक्त_recv_priv(काष्ठा adapter *padapter)
अणु
	u32 i;
	काष्ठा recv_priv *precvpriv;
	काष्ठा recv_buf *precvbuf;

	precvpriv = &padapter->recvpriv;

	/* 3 1. समाप्त tasklet */
	tasklet_समाप्त(&precvpriv->recv_tasklet);

	/* 3 2. मुक्त all recv buffers */
	precvbuf = (काष्ठा recv_buf *)precvpriv->precv_buf;
	अगर (precvbuf) अणु
		precvpriv->मुक्त_recv_buf_queue_cnt = 0;
		क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
			list_del_init(&precvbuf->list);
			rtw_os_recvbuf_resource_मुक्त(padapter, precvbuf);
			precvbuf++;
		पूर्ण
		precvpriv->precv_buf = शून्य;
	पूर्ण

	kमुक्त(precvpriv->pallocated_recv_buf);
	precvpriv->pallocated_recv_buf = शून्य;
पूर्ण
