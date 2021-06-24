<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl8712_xmit.c
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

#घोषणा _RTL8712_XMIT_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wifi.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"

अटल व्योम dump_xframe(काष्ठा _adapter *padapter,
			काष्ठा xmit_frame *pxmitframe);
अटल व्योम update_txdesc(काष्ठा xmit_frame *pxmitframe, uपूर्णांक *pmem, पूर्णांक sz);

sपूर्णांक _r8712_init_hw_txqueue(काष्ठा hw_txqueue *phw_txqueue, u8 ac_tag)
अणु
	phw_txqueue->ac_tag = ac_tag;
	चयन (ac_tag) अणु
	हाल BE_QUEUE_INX:
		phw_txqueue->ff_hwaddr = RTL8712_DMA_BEQ;
		अवरोध;
	हाल BK_QUEUE_INX:
		phw_txqueue->ff_hwaddr = RTL8712_DMA_BKQ;
		अवरोध;
	हाल VI_QUEUE_INX:
		phw_txqueue->ff_hwaddr = RTL8712_DMA_VIQ;
		अवरोध;
	हाल VO_QUEUE_INX:
		phw_txqueue->ff_hwaddr = RTL8712_DMA_VOQ;
		अवरोध;
	हाल BMC_QUEUE_INX:
		phw_txqueue->ff_hwaddr = RTL8712_DMA_BEQ;
		अवरोध;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

पूर्णांक r8712_txframes_sta_ac_pending(काष्ठा _adapter *padapter,
				  काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा sta_info *psta;
	काष्ठा tx_servq *ptxservq;
	पूर्णांक priority = pattrib->priority;

	psta = pattrib->psta;
	चयन (priority) अणु
	हाल 1:
	हाल 2:
		ptxservq = &psta->sta_xmitpriv.bk_q;
		अवरोध;
	हाल 4:
	हाल 5:
		ptxservq = &psta->sta_xmitpriv.vi_q;
		अवरोध;
	हाल 6:
	हाल 7:
		ptxservq = &psta->sta_xmitpriv.vo_q;
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &psta->sta_xmitpriv.be_q;
	अवरोध;
	पूर्ण
	वापस ptxservq->qcnt;
पूर्ण

अटल u32 get_ff_hwaddr(काष्ठा xmit_frame *pxmitframe)
अणु
	u32 addr = 0;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;

	अगर (pxmitframe->frame_tag == TXAGG_FRAMETAG) अणु
		addr = RTL8712_DMA_H2CCMD;
	पूर्ण अन्यथा अगर (pxmitframe->frame_tag == MGNT_FRAMETAG) अणु
		addr = RTL8712_DMA_MGTQ;
	पूर्ण अन्यथा अगर (pdvobj->nr_endpoपूर्णांक == 6) अणु
		चयन (pattrib->priority) अणु
		हाल 0:
		हाल 3:
			addr = RTL8712_DMA_BEQ;
			अवरोध;
		हाल 1:
		हाल 2:
			addr = RTL8712_DMA_BKQ;
			अवरोध;
		हाल 4:
		हाल 5:
			addr = RTL8712_DMA_VIQ;
			अवरोध;
		हाल 6:
		हाल 7:
			addr = RTL8712_DMA_VOQ;
			अवरोध;
		हाल 0x10:
		हाल 0x11:
		हाल 0x12:
		हाल 0x13:
			addr = RTL8712_DMA_H2CCMD;
			अवरोध;
		शेष:
			addr = RTL8712_DMA_BEQ;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (pdvobj->nr_endpoपूर्णांक == 4) अणु
		चयन (pattrib->qsel) अणु
		हाल 0:
		हाल 3:
		हाल 1:
		हाल 2:
			addr = RTL8712_DMA_BEQ;/*RTL8712_EP_LO;*/
			अवरोध;
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
			addr = RTL8712_DMA_VOQ;/*RTL8712_EP_HI;*/
			अवरोध;
		हाल 0x10:
		हाल 0x11:
		हाल 0x12:
		हाल 0x13:
			addr = RTL8712_DMA_H2CCMD;
			अवरोध;
		शेष:
			addr = RTL8712_DMA_BEQ;/*RTL8712_EP_LO;*/
			अवरोध;
		पूर्ण
	पूर्ण
	वापस addr;
पूर्ण

अटल काष्ठा xmit_frame *dequeue_one_xmitframe(काष्ठा xmit_priv *pxmitpriv,
					 काष्ठा hw_xmit *phwxmit,
					 काष्ठा tx_servq *ptxservq,
					 काष्ठा  __queue *pframe_queue)
अणु
	काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
	काष्ठा	xmit_frame *pxmitframe = शून्य;

	xmitframe_phead = &pframe_queue->queue;
	xmitframe_plist = xmitframe_phead->next;
	अगर (!end_of_queue_search(xmitframe_phead, xmitframe_plist)) अणु
		pxmitframe = container_of(xmitframe_plist,
					  काष्ठा xmit_frame, list);
		list_del_init(&pxmitframe->list);
		ptxservq->qcnt--;
		phwxmit->txcmdcnt++;
	पूर्ण
	वापस pxmitframe;
पूर्ण

अटल काष्ठा xmit_frame *dequeue_xframe_ex(काष्ठा xmit_priv *pxmitpriv,
				     काष्ठा hw_xmit *phwxmit_i, sपूर्णांक entry)
अणु
	अचिन्हित दीर्घ irqL0;
	काष्ठा list_head *sta_plist, *sta_phead;
	काष्ठा hw_xmit *phwxmit;
	काष्ठा tx_servq *ptxservq = शून्य;
	काष्ठा  __queue *pframe_queue = शून्य;
	काष्ठा	xmit_frame *pxmitframe = शून्य;
	पूर्णांक i, inx[4];
	पूर्णांक j, acirp_cnt[4];

	/*entry indx: 0->vo, 1->vi, 2->be, 3->bk.*/
	inx[0] = 0; acirp_cnt[0] = pxmitpriv->voq_cnt;
	inx[1] = 1; acirp_cnt[1] = pxmitpriv->viq_cnt;
	inx[2] = 2; acirp_cnt[2] = pxmitpriv->beq_cnt;
	inx[3] = 3; acirp_cnt[3] = pxmitpriv->bkq_cnt;
	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = i + 1; j < 4; j++) अणु
			अगर (acirp_cnt[j] < acirp_cnt[i]) अणु
				swap(acirp_cnt[i], acirp_cnt[j]);
				swap(inx[i], inx[j]);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&pxmitpriv->lock, irqL0);
	क्रम (i = 0; i < entry; i++) अणु
		phwxmit = phwxmit_i + inx[i];
		sta_phead = &phwxmit->sta_queue->queue;
		sta_plist = sta_phead->next;
		जबतक (!end_of_queue_search(sta_phead, sta_plist)) अणु
			ptxservq = container_of(sta_plist, काष्ठा tx_servq,
						tx_pending);
			pframe_queue = &ptxservq->sta_pending;
			pxmitframe = dequeue_one_xmitframe(pxmitpriv, phwxmit,
				     ptxservq, pframe_queue);
			अगर (pxmitframe) अणु
				phwxmit->accnt--;
				जाओ निकास_dequeue_xframe_ex;
			पूर्ण
			sta_plist = sta_plist->next;
			/*Remove sta node when there are no pending packets.*/
			अगर (list_empty(&pframe_queue->queue)) अणु
				/* must be करोne after sta_plist->next
				 * and beक्रमe अवरोध
				 */
				list_del_init(&ptxservq->tx_pending);
			पूर्ण
		पूर्ण
	पूर्ण
निकास_dequeue_xframe_ex:
	spin_unlock_irqrestore(&pxmitpriv->lock, irqL0);
	वापस pxmitframe;
पूर्ण

व्योम r8712_करो_queue_select(काष्ठा _adapter *padapter,
			   काष्ठा pkt_attrib *pattrib)
अणु
	अचिन्हित पूर्णांक qsel = 0;
	काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;

	अगर (pdvobj->nr_endpoपूर्णांक == 6) अणु
		qsel = (अचिन्हित पूर्णांक)pattrib->priority;
	पूर्ण अन्यथा अगर (pdvobj->nr_endpoपूर्णांक == 4) अणु
		qsel = (अचिन्हित पूर्णांक)pattrib->priority;
		अगर (qsel == 0 || qsel == 3)
			qsel = 3;
		अन्यथा अगर (qsel == 1 || qsel == 2)
			qsel = 1;
		अन्यथा अगर (qsel == 4 || qsel == 5)
			qsel = 5;
		अन्यथा अगर (qsel == 6 || qsel == 7)
			qsel = 7;
		अन्यथा
			qsel = 3;
	पूर्ण
	pattrib->qsel = qsel;
पूर्ण

#अगर_घोषित CONFIG_R8712_TX_AGGR
व्योम r8712_स्थिरruct_txaggr_cmd_desc(काष्ठा xmit_buf *pxmitbuf)
अणु
	काष्ठा tx_desc *ptx_desc = (काष्ठा tx_desc *)pxmitbuf->pbuf;

	/* Fill up TxCmd Descriptor according as USB FW Tx Aaggregation info.*/
	/* dw0 */
	ptx_desc->txdw0 = cpu_to_le32(CMD_HDR_SZ & 0xffff);
	ptx_desc->txdw0 |=
		cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ) << OFFSET_SHT) &
			    0x00ff0000);
	ptx_desc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);

	/* dw1 */
	ptx_desc->txdw1 |= cpu_to_le32((0x13 << QSEL_SHT) & 0x00001f00);
पूर्ण

व्योम r8712_स्थिरruct_txaggr_cmd_hdr(काष्ठा xmit_buf *pxmitbuf)
अणु
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)
		pxmitbuf->priv_data;
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा cmd_hdr *pcmd_hdr = (काष्ठा cmd_hdr  *)
		(pxmitbuf->pbuf + TXDESC_SIZE);

	/* Fill up Cmd Header क्रम USB FW Tx Aggregation.*/
	/* dw0 */
	pcmd_hdr->cmd_dw0 = cpu_to_le32((GEN_CMD_CODE(_AMSDU_TO_AMPDU) << 16) |
					(pcmdpriv->cmd_seq << 24));
	pcmdpriv->cmd_seq++;
पूर्ण

व्योम r8712_append_mpdu_unit(काष्ठा xmit_buf *pxmitbuf,
			    काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा tx_desc *ptx_desc = (काष्ठा tx_desc *)pxmitbuf->pbuf;
	पूर्णांक last_txcmdsz = 0;
	पूर्णांक padding_sz = 0;

	/* 802.3->802.11 converter */
	r8712_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	/* मुक्त skb काष्ठा */
	r8712_xmit_complete(padapter, pxmitframe);
	अगर (pxmitframe->attrib.ether_type != 0x0806) अणु
		अगर ((pxmitframe->attrib.ether_type != 0x888e) &&
			(pxmitframe->attrib.dhcp_pkt != 1)) अणु
			r8712_issue_addbareq_cmd(padapter,
					pxmitframe->attrib.priority);
		पूर्ण
	पूर्ण
	pxmitframe->last[0] = 1;
	update_txdesc(pxmitframe, (uपूर्णांक *)(pxmitframe->buf_addr),
		pxmitframe->attrib.last_txcmdsz);
	/*padding zero */
	last_txcmdsz = pxmitframe->attrib.last_txcmdsz;
	padding_sz = (8 - (last_txcmdsz % 8));
	अगर ((last_txcmdsz % 8) != 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < padding_sz; i++)
			*(pxmitframe->buf_addr + TXDESC_SIZE + last_txcmdsz +
			  i) = 0;
	पूर्ण
	/* Add the new mpdu's length */
	ptx_desc->txdw0 = cpu_to_le32((ptx_desc->txdw0 & 0xffff0000) |
		((ptx_desc->txdw0 & 0x0000ffff) +
			((TXDESC_SIZE + last_txcmdsz + padding_sz) &
			 0x0000ffff)));
पूर्ण

व्योम r8712_xmitframe_aggr_1st(काष्ठा xmit_buf *pxmitbuf,
			      काष्ठा xmit_frame *pxmitframe)
अणु
	/* linux complete context करोesn't need to protect */
	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitbuf->priv_data = pxmitframe;
	pxmitframe->pxmit_urb[0] = pxmitbuf->pxmit_urb[0];
	/* buffer addr assoc */
	pxmitframe->buf_addr = pxmitbuf->pbuf + TXDESC_SIZE + CMD_HDR_SZ;
	/*RTL8712_DMA_H2CCMD */
	r8712_स्थिरruct_txaggr_cmd_desc(pxmitbuf);
	r8712_स्थिरruct_txaggr_cmd_hdr(pxmitbuf);
	r8712_append_mpdu_unit(pxmitbuf, pxmitframe);
	pxmitbuf->aggr_nr = 1;
पूर्ण

u16 r8712_xmitframe_aggr_next(काष्ठा xmit_buf *pxmitbuf,
			काष्ठा xmit_frame *pxmitframe)
अणु
	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitbuf->priv_data = pxmitframe;
	pxmitframe->pxmit_urb[0] = pxmitbuf->pxmit_urb[0];
	/* buffer addr assoc */
	pxmitframe->buf_addr = pxmitbuf->pbuf + TXDESC_SIZE +
		(((काष्ठा tx_desc *)pxmitbuf->pbuf)->txdw0 & 0x0000ffff);
	r8712_append_mpdu_unit(pxmitbuf, pxmitframe);
	r8712_मुक्त_xmitframe_ex(&pxmitframe->padapter->xmitpriv,
				pxmitframe);
	pxmitbuf->aggr_nr++;

	वापस TXDESC_SIZE +
		(((काष्ठा tx_desc *)pxmitbuf->pbuf)->txdw0 & 0x0000ffff);
पूर्ण

व्योम r8712_dump_aggr_xframe(काष्ठा xmit_buf *pxmitbuf,
			    काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;
	काष्ठा tx_desc *ptxdesc = pxmitbuf->pbuf;
	काष्ठा cmd_hdr *pcmd_hdr = (काष्ठा cmd_hdr *)
		(pxmitbuf->pbuf + TXDESC_SIZE);
	u16 total_length = (u16)(ptxdesc->txdw0 & 0xffff);

	/* use 1st xmitframe as media */
	xmitframe_xmitbuf_attach(pxmitframe, pxmitbuf);
	pcmd_hdr->cmd_dw0 = cpu_to_le32(((total_length - CMD_HDR_SZ) &
					 0x0000ffff) | (pcmd_hdr->cmd_dw0 &
							0xffff0000));

	/* urb length in cmd_dw1 */
	pcmd_hdr->cmd_dw1 = cpu_to_le32((pxmitbuf->aggr_nr & 0xff) |
					((total_length + TXDESC_SIZE) << 16));
	pxmitframe->last[0] = 1;
	pxmitframe->bpending[0] = false;
	pxmitframe->mem_addr = pxmitbuf->pbuf;

	अगर ((pdvobj->ishighspeed && ((total_length + TXDESC_SIZE) % 0x200) ==
	     0) || ((!pdvobj->ishighspeed && ((total_length + TXDESC_SIZE) %
					      0x40) == 0))) अणु
		ptxdesc->txdw0 |= cpu_to_le32
			(((TXDESC_SIZE + OFFSET_SZ + 8) << OFFSET_SHT) &
			 0x00ff0000);
		/*32 bytes क्रम TX Desc + 8 bytes pending*/
	पूर्ण अन्यथा अणु
		ptxdesc->txdw0 |= cpu_to_le32
			(((TXDESC_SIZE + OFFSET_SZ) << OFFSET_SHT) &
			 0x00ff0000);
		/*शेष = 32 bytes क्रम TX Desc*/
	पूर्ण
	r8712_ग_लिखो_port(pxmitframe->padapter, RTL8712_DMA_H2CCMD,
			total_length + TXDESC_SIZE, (u8 *)pxmitframe);
पूर्ण

#पूर्ण_अगर

अटल व्योम update_txdesc(काष्ठा xmit_frame *pxmitframe, uपूर्णांक *pmem, पूर्णांक sz)
अणु
	uपूर्णांक qsel;
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा tx_desc *ptxdesc = (काष्ठा tx_desc *)pmem;
	काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;
#अगर_घोषित CONFIG_R8712_TX_AGGR
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
#पूर्ण_अगर
	u8 blnSetTxDescOffset;
	bool bmcst = is_multicast_ether_addr(pattrib->ra);
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	काष्ठा tx_desc txdesc_mp;

	स_नकल(&txdesc_mp, ptxdesc, माप(काष्ठा tx_desc));
	स_रखो(ptxdesc, 0, माप(काष्ठा tx_desc));
	/* offset 0 */
	ptxdesc->txdw0 |= cpu_to_le32(sz & 0x0000ffff);
	अगर (pdvobj->ishighspeed) अणु
		अगर (((sz + TXDESC_SIZE) % 512) == 0)
			blnSetTxDescOffset = 1;
		अन्यथा
			blnSetTxDescOffset = 0;
	पूर्ण अन्यथा अणु
		अगर (((sz + TXDESC_SIZE) % 64) == 0)
			blnSetTxDescOffset = 1;
		अन्यथा
			blnSetTxDescOffset = 0;
	पूर्ण
	अगर (blnSetTxDescOffset) अणु
		/* 32 bytes क्रम TX Desc + 8 bytes pending */
		ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ + 8) <<
			      OFFSET_SHT) & 0x00ff0000);
	पूर्ण अन्यथा अणु
		/* शेष = 32 bytes क्रम TX Desc */
		ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ) <<
				  OFFSET_SHT) & 0x00ff0000);
	पूर्ण
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
	अगर (pxmitframe->frame_tag == DATA_FRAMETAG) अणु
		/* offset 4 */
		ptxdesc->txdw1 |= cpu_to_le32((pattrib->mac_id) & 0x1f);

#अगर_घोषित CONFIG_R8712_TX_AGGR
		/* dirty workaround, need to check अगर it is aggr cmd. */
		अगर ((u8 *)pmem != (u8 *)pxmitframe->pxmitbuf->pbuf) अणु
			ptxdesc->txdw0 |= cpu_to_le32
				((0x3 << TYPE_SHT) & TYPE_MSK);
			qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
			अगर (qsel == 2)
				qsel = 0;
			ptxdesc->txdw1 |= cpu_to_le32
				((qsel << QSEL_SHT) & 0x00001f00);
			ptxdesc->txdw2 = cpu_to_le32
				((qsel << RTS_RC_SHT) & 0x001f0000);
			ptxdesc->txdw6 |= cpu_to_le32
				((0x5 << RSVD6_SHT) & RSVD6_MSK);
		पूर्ण अन्यथा अणु
			ptxdesc->txdw0 |= cpu_to_le32
				((0x3 << TYPE_SHT) & TYPE_MSK);
			ptxdesc->txdw1 |= cpu_to_le32
				((0x13 << QSEL_SHT) & 0x00001f00);
			qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
			अगर (qsel == 2)
				qsel = 0;
			ptxdesc->txdw2 = cpu_to_le32
				((qsel << RTS_RC_SHT) & 0x0001f000);
			ptxdesc->txdw7 |= cpu_to_le32
				(pcmdpriv->cmd_seq << 24);
			pcmdpriv->cmd_seq++;
		पूर्ण
		pattrib->qsel = 0x13;
#अन्यथा
		qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);
#पूर्ण_अगर
		अगर (!pqospriv->qos_option)
			ptxdesc->txdw1 |= cpu_to_le32(BIT(16));/*Non-QoS*/
		अगर ((pattrib->encrypt > 0) && !pattrib->bswenc) अणु
			चयन (pattrib->encrypt) अणु	/*SEC_TYPE*/
			हाल _WEP40_:
			हाल _WEP104_:
				ptxdesc->txdw1 |= cpu_to_le32((0x01 << 22) &
						  0x00c00000);
				/*KEY_ID when WEP is used;*/
				ptxdesc->txdw1 |= cpu_to_le32((psecuritypriv->
						  PrivacyKeyIndex << 17) &
						  0x00060000);
				अवरोध;
			हाल _TKIP_:
			हाल _TKIP_WTMIC_:
				ptxdesc->txdw1 |= cpu_to_le32((0x02 << 22) &
						  0x00c00000);
				अवरोध;
			हाल _AES_:
				ptxdesc->txdw1 |= cpu_to_le32((0x03 << 22) &
						  0x00c00000);
				अवरोध;
			हाल _NO_PRIVACY_:
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		/*offset 8*/
		अगर (bmcst)
			ptxdesc->txdw2 |= cpu_to_le32(BMC);

		/*offset 12*/
		/* f/w will increase the seqnum by itself, driver pass the
		 * correct priority to fw.
		 * fw will check the correct priority क्रम increasing the
		 * seqnum per tid. about usb using 4-endpoपूर्णांक, qsel poपूर्णांकs out
		 * the correct mapping between AC&Endpoपूर्णांक,
		 * the purpose is that correct mapping lets the MAC release
		 * the AC Queue list correctly.
		 */
		ptxdesc->txdw3 = cpu_to_le32((pattrib->priority << SEQ_SHT) &
				 0x0fff0000);
		अगर ((pattrib->ether_type != 0x888e) &&
		    (pattrib->ether_type != 0x0806) &&
		    (pattrib->dhcp_pkt != 1)) अणु
			/*Not EAP & ARP type data packet*/
			अगर (phtpriv->ht_option == 1) अणु /*B/G/N Mode*/
				अगर (!phtpriv->ampdu_enable)
					ptxdesc->txdw2 |= cpu_to_le32(BK);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* EAP data packet and ARP packet.
			 * Use the 1M data rate to send the EAP/ARP packet.
			 * This will maybe make the handshake smooth.
			 */
			/*driver uses data rate*/
			ptxdesc->txdw4 = cpu_to_le32(0x80000000);
			ptxdesc->txdw5 = cpu_to_le32(0x001f8000);/*1M*/
		पूर्ण
		अगर (pattrib->pctrl == 1) अणु /* mp tx packets */
			काष्ठा tx_desc *ptxdesc_mp;

			ptxdesc_mp = &txdesc_mp;
			/* offset 8 */
			ptxdesc->txdw2 = ptxdesc_mp->txdw2;
			अगर (bmcst)
				ptxdesc->txdw2 |= cpu_to_le32(BMC);
			ptxdesc->txdw2 |= cpu_to_le32(BK);
			/* offset 16 */
			ptxdesc->txdw4 = ptxdesc_mp->txdw4;
			/* offset 20 */
			ptxdesc->txdw5 = ptxdesc_mp->txdw5;
			pattrib->pctrl = 0;/* reset to zero; */
		पूर्ण
	पूर्ण अन्यथा अगर (pxmitframe->frame_tag == MGNT_FRAMETAG) अणु
		/* offset 4 */
		/* CAM_ID(MAC_ID), शेष=5; */
		ptxdesc->txdw1 |= cpu_to_le32((0x05) & 0x1f);
		qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);
		ptxdesc->txdw1 |= cpu_to_le32(BIT(16));/* Non-QoS */
		/* offset 8 */
		अगर (bmcst)
			ptxdesc->txdw2 |= cpu_to_le32(BMC);
		/* offset 12 */
		/* f/w will increase the seqnum by itself, driver pass the
		 * correct priority to fw.
		 * fw will check the correct priority क्रम increasing the seqnum
		 * per tid. about usb using 4-endpoपूर्णांक, qsel poपूर्णांकs out the
		 * correct mapping between AC&Endpoपूर्णांक,
		 * the purpose is that correct mapping let the MAC releases
		 * the AC Queue list correctly.
		 */
		ptxdesc->txdw3 = cpu_to_le32((pattrib->priority << SEQ_SHT) &
					      0x0fff0000);
		/* offset 16 */
		ptxdesc->txdw4 = cpu_to_le32(0x80002040);/*gtest*/
		/* offset 20 */
		ptxdesc->txdw5 = cpu_to_le32(0x001f8000);/* gtest 1M */
	पूर्ण अन्यथा अगर (pxmitframe->frame_tag == TXAGG_FRAMETAG) अणु
		/* offset 4 */
		qsel = 0x13;
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);
	पूर्ण अन्यथा अणु
		/* offset 4 */
		qsel = (uपूर्णांक)(pattrib->priority & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);
		/*offset 8*/
		/*offset 12*/
		ptxdesc->txdw3 = cpu_to_le32((pattrib->seqnum << SEQ_SHT) &
					      0x0fff0000);
		/*offset 16*/
		ptxdesc->txdw4 = cpu_to_le32(0x80002040);/*gtest*/
		/*offset 20*/
		ptxdesc->txdw5 = cpu_to_le32(0x001f9600);/*gtest*/
	पूर्ण
पूर्ण

पूर्णांक r8712_xmitframe_complete(काष्ठा _adapter *padapter,
			     काष्ठा xmit_priv *pxmitpriv,
			     काष्ठा xmit_buf *pxmitbuf)
अणु
	काष्ठा hw_xmit *phwxmits;
	sपूर्णांक hwentry;
	काष्ठा xmit_frame *pxmitframe = शून्य;
#अगर_घोषित CONFIG_R8712_TX_AGGR
	काष्ठा xmit_frame *p2ndxmitframe = शून्य;
#अन्यथा
	पूर्णांक res = _SUCCESS, xcnt = 0;
#पूर्ण_अगर

	phwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;
	अगर (!pxmitbuf) अणु
		pxmitbuf = r8712_alloc_xmitbuf(pxmitpriv);
		अगर (!pxmitbuf)
			वापस false;
#अगर_घोषित CONFIG_R8712_TX_AGGR
		pxmitbuf->aggr_nr = 0;
#पूर्ण_अगर
	पूर्ण
	/* 1st frame dequeued */
	pxmitframe = dequeue_xframe_ex(pxmitpriv, phwxmits, hwentry);
	/* need to remember the 1st frame */
	अगर (pxmitframe) अणु

#अगर_घोषित CONFIG_R8712_TX_AGGR
		/* 1. dequeue 2nd frame
		 * 2. aggr अगर 2nd xframe is dequeued, अन्यथा dump directly
		 */
		अगर (AGGR_NR_HIGH_BOUND > 1)
			p2ndxmitframe = dequeue_xframe_ex(pxmitpriv, phwxmits,
							hwentry);
		अगर (pxmitframe->frame_tag != DATA_FRAMETAG) अणु
			r8712_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
			वापस false;
		पूर्ण
		अगर (p2ndxmitframe)
			अगर (p2ndxmitframe->frame_tag != DATA_FRAMETAG) अणु
				r8712_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
				वापस false;
			पूर्ण
		r8712_xmitframe_aggr_1st(pxmitbuf, pxmitframe);
		अगर (p2ndxmitframe) अणु
			u16 total_length;

			total_length = r8712_xmitframe_aggr_next(
				pxmitbuf, p2ndxmitframe);
			करो अणु
				p2ndxmitframe = dequeue_xframe_ex(
					pxmitpriv, phwxmits, hwentry);
				अगर (p2ndxmitframe)
					total_length =
						r8712_xmitframe_aggr_next(
							pxmitbuf,
							p2ndxmitframe);
				अन्यथा
					अवरोध;
			पूर्ण जबतक (total_length <= 0x1800 &&
				pxmitbuf->aggr_nr <= AGGR_NR_HIGH_BOUND);
		पूर्ण
		अगर (pxmitbuf->aggr_nr > 0)
			r8712_dump_aggr_xframe(pxmitbuf, pxmitframe);

#अन्यथा

		xmitframe_xmitbuf_attach(pxmitframe, pxmitbuf);
		अगर (pxmitframe->frame_tag == DATA_FRAMETAG) अणु
			अगर (pxmitframe->attrib.priority <= 15)
				res = r8712_xmitframe_coalesce(padapter,
					pxmitframe->pkt, pxmitframe);
			/* always वापस ndis_packet after
			 * r8712_xmitframe_coalesce
			 */
			r8712_xmit_complete(padapter, pxmitframe);
		पूर्ण
		अगर (res == _SUCCESS)
			dump_xframe(padapter, pxmitframe);
		अन्यथा
			r8712_मुक्त_xmitframe_ex(pxmitpriv, pxmitframe);
		xcnt++;
#पूर्ण_अगर

	पूर्ण अन्यथा अणु /* pxmitframe == शून्य && p2ndxmitframe == शून्य */
		r8712_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम dump_xframe(काष्ठा _adapter *padapter,
			काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक t, sz, w_sz;
	u8 *mem_addr;
	u32 ff_hwaddr;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	अगर (pxmitframe->attrib.ether_type != 0x0806) अणु
		अगर (pxmitframe->attrib.ether_type != 0x888e)
			r8712_issue_addbareq_cmd(padapter, pattrib->priority);
	पूर्ण
	mem_addr = pxmitframe->buf_addr;
	क्रम (t = 0; t < pattrib->nr_frags; t++) अणु
		अगर (t != (pattrib->nr_frags - 1)) अणु
			sz = pxmitpriv->frag_len;
			sz = sz - 4 - (psecuritypriv->sw_encrypt ? 0 :
			     pattrib->icv_len);
			pxmitframe->last[t] = 0;
		पूर्ण अन्यथा अणु
			sz = pattrib->last_txcmdsz;
			pxmitframe->last[t] = 1;
		पूर्ण
		update_txdesc(pxmitframe, (uपूर्णांक *)mem_addr, sz);
		w_sz = sz + TXDESC_SIZE;
		pxmitframe->mem_addr = mem_addr;
		pxmitframe->bpending[t] = false;
		ff_hwaddr = get_ff_hwaddr(pxmitframe);
#अगर_घोषित CONFIG_R8712_TX_AGGR
		r8712_ग_लिखो_port(padapter, RTL8712_DMA_H2CCMD, w_sz,
				(अचिन्हित अक्षर *)pxmitframe);
#अन्यथा
		r8712_ग_लिखो_port(padapter, ff_hwaddr, w_sz,
			   (अचिन्हित अक्षर *)pxmitframe);
#पूर्ण_अगर
		mem_addr += w_sz;
		mem_addr = (u8 *)RND4(((addr_t)(mem_addr)));
	पूर्ण
पूर्ण

व्योम r8712_xmit_direct(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक res;

	res = r8712_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	pxmitframe->pkt = शून्य;
	अगर (res == _SUCCESS)
		dump_xframe(padapter, pxmitframe);
पूर्ण

पूर्णांक r8712_xmit_enqueue(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (r8712_xmit_classअगरier(padapter, pxmitframe)) अणु
		pxmitframe->pkt = शून्य;
		वापस _FAIL;
	पूर्ण
	वापस _SUCCESS;
पूर्ण
