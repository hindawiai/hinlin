<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8188E_XMIT_C_
#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <mon.h>
#समावेश <wअगरi.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <usb_ops_linux.h>
#समावेश <rtl8188e_hal.h>

s32 rtw_hal_init_xmit_priv(काष्ठा adapter *adapt)
अणु
	काष्ठा xmit_priv *pxmitpriv = &adapt->xmitpriv;

	tasklet_setup(&pxmitpriv->xmit_tasklet, rtl8188eu_xmit_tasklet);
	वापस _SUCCESS;
पूर्ण

अटल u8 urb_zero_packet_chk(काष्ठा adapter *adapt, पूर्णांक sz)
अणु
	वापस !((sz + TXDESC_SIZE) % adapt->HalData->UsbBulkOutSize);
पूर्ण

अटल व्योम rtl8188eu_cal_txdesc_chksum(काष्ठा tx_desc	*ptxdesc)
अणु
	u16 *usptr = (u16 *)ptxdesc;
	u32 count = 16; /* (32 bytes / 2 bytes per XOR) => 16 बार */
	u32 index;
	u16 checksum = 0;

	/* Clear first */
	ptxdesc->txdw7 &= cpu_to_le32(0xffff0000);

	क्रम (index = 0; index < count; index++)
		checksum = checksum ^ le16_to_cpu(*(__le16 *)(usptr + index));
	ptxdesc->txdw7 |= cpu_to_le32(0x0000ffff & checksum);
पूर्ण

/*
 * In normal chip, we should send some packet to Hw which will be used by Fw
 * in FW LPS mode. The function is to fill the Tx descriptor of this packets,
 * then Fw can tell Hw to send these packet derectly.
 */
व्योम rtl8188e_fill_fake_txdesc(काष्ठा adapter *adapt, u8 *desc, u32 BufferLen, u8  ispspoll, u8  is_btqosnull)
अणु
	काष्ठा tx_desc *ptxdesc;

	/*  Clear all status */
	ptxdesc = (काष्ठा tx_desc *)desc;
	स_रखो(desc, 0, TXDESC_SIZE);

	/* offset 0 */
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG); /* own, bFirstSeg, bLastSeg; */

	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ) << OFFSET_SHT) & 0x00ff0000); /* 32 bytes क्रम TX Desc */

	ptxdesc->txdw0 |= cpu_to_le32(BufferLen & 0x0000ffff); /*  Buffer size + command header */

	/* offset 4 */
	ptxdesc->txdw1 |= cpu_to_le32((QSLT_MGNT << QSEL_SHT) & 0x00001f00); /*  Fixed queue of Mgnt queue */

	/* Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error vlaue by Hw. */
	अगर (ispspoll) अणु
		ptxdesc->txdw1 |= cpu_to_le32(NAVUSEHDR);
	पूर्ण अन्यथा अणु
		ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); /*  Hw set sequence number */
		ptxdesc->txdw3 |= cpu_to_le32((8 << 28)); /* set bit3 to 1. Suugested by TimChen. 2009.12.29. */
	पूर्ण

	अगर (is_btqosnull)
		ptxdesc->txdw2 |= cpu_to_le32(BIT(23)); /*  BT शून्य */

	/* offset 16 */
	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));/* driver uses rate */

	/*  USB पूर्णांकerface drop packet अगर the checksum of descriptor isn't correct. */
	/*  Using this checksum can let hardware recovery from packet bulk out error (e.g. Cancel URC, Bulk out error.). */
	rtl8188eu_cal_txdesc_chksum(ptxdesc);
पूर्ण

अटल व्योम fill_txdesc_sectype(काष्ठा pkt_attrib *pattrib, काष्ठा tx_desc *ptxdesc)
अणु
	अगर ((pattrib->encrypt > 0) && !pattrib->bswenc) अणु
		चयन (pattrib->encrypt) अणु
		/* SEC_TYPE : 0:NO_ENC,1:WEP40/TKIP,2:WAPI,3:AES */
		हाल _WEP40_:
		हाल _WEP104_:
			ptxdesc->txdw1 |= cpu_to_le32((0x01 << SEC_TYPE_SHT) & 0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			अवरोध;
		हाल _TKIP_:
		हाल _TKIP_WTMIC_:
			ptxdesc->txdw1 |= cpu_to_le32((0x01 << SEC_TYPE_SHT) & 0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			अवरोध;
		हाल _AES_:
			ptxdesc->txdw1 |= cpu_to_le32((0x03 << SEC_TYPE_SHT) & 0x00c00000);
			ptxdesc->txdw2 |= cpu_to_le32(0x7 << AMPDU_DENSITY_SHT);
			अवरोध;
		हाल _NO_PRIVACY_:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fill_txdesc_vcs(काष्ठा pkt_attrib *pattrib, __le32 *pdw)
अणु
	चयन (pattrib->vcs_mode) अणु
	हाल RTS_CTS:
		*pdw |= cpu_to_le32(RTS_EN);
		अवरोध;
	हाल CTS_TO_SELF:
		*pdw |= cpu_to_le32(CTS_2_SELF);
		अवरोध;
	हाल NONE_VCS:
	शेष:
		अवरोध;
	पूर्ण
	अगर (pattrib->vcs_mode) अणु
		*pdw |= cpu_to_le32(HW_RTS_EN);
		/*  Set RTS BW */
		अगर (pattrib->ht_en) अणु
			*pdw |= (pattrib->bwmode & HT_CHANNEL_WIDTH_40) ?	cpu_to_le32(BIT(27)) : 0;

			अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
				*pdw |= cpu_to_le32((0x01 << 28) & 0x30000000);
			अन्यथा अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
				*pdw |= cpu_to_le32((0x02 << 28) & 0x30000000);
			अन्यथा अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
				*pdw |= 0;
			अन्यथा
				*pdw |= cpu_to_le32((0x03 << 28) & 0x30000000);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fill_txdesc_phy(काष्ठा pkt_attrib *pattrib, __le32 *pdw)
अणु
	अगर (pattrib->ht_en) अणु
		*pdw |= (pattrib->bwmode & HT_CHANNEL_WIDTH_40) ?	cpu_to_le32(BIT(25)) : 0;

		अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			*pdw |= cpu_to_le32((0x01 << DATA_SC_SHT) & 0x003f0000);
		अन्यथा अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
			*pdw |= cpu_to_le32((0x02 << DATA_SC_SHT) & 0x003f0000);
		अन्यथा अगर (pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
			*pdw |= 0;
		अन्यथा
			*pdw |= cpu_to_le32((0x03 << DATA_SC_SHT) & 0x003f0000);
	पूर्ण
पूर्ण

अटल s32 update_txdesc(काष्ठा xmit_frame *pxmitframe, u8 *pmem, s32 sz, u8 bagg_pkt)
अणु
	पूर्णांक pull = 0;
	uपूर्णांक qsel;
	u8 data_rate, pwr_status, offset;
	काष्ठा adapter *adapt = pxmitframe->padapter;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा odm_dm_काष्ठा *odmpriv = &adapt->HalData->odmpriv;
	काष्ठा tx_desc *ptxdesc = (काष्ठा tx_desc *)pmem;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (adapt->registrypriv.mp_mode == 0) अणु
		अगर ((!bagg_pkt) && (urb_zero_packet_chk(adapt, sz) == 0)) अणु
			ptxdesc = (काष्ठा tx_desc *)(pmem + PACKET_OFFSET_SZ);
			pull = 1;
		पूर्ण
	पूर्ण

	स_रखो(ptxdesc, 0, माप(काष्ठा tx_desc));

	/* 4 offset 0 */
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
	ptxdesc->txdw0 |= cpu_to_le32(sz & 0x0000ffff);/* update TXPKTSIZE */

	offset = TXDESC_SIZE + OFFSET_SZ;

	ptxdesc->txdw0 |= cpu_to_le32(((offset) << OFFSET_SHT) & 0x00ff0000);/* 32 bytes क्रम TX Desc */

	अगर (is_multicast_ether_addr(pattrib->ra))
		ptxdesc->txdw0 |= cpu_to_le32(BMC);

	अगर (adapt->registrypriv.mp_mode == 0) अणु
		अगर (!bagg_pkt) अणु
			अगर ((pull) && (pxmitframe->pkt_offset > 0))
				pxmitframe->pkt_offset = pxmitframe->pkt_offset - 1;
		पूर्ण
	पूर्ण

	/*  pkt_offset, unit:8 bytes padding */
	अगर (pxmitframe->pkt_offset > 0)
		ptxdesc->txdw1 |= cpu_to_le32((pxmitframe->pkt_offset << 26) & 0x7c000000);

	/* driver uses rate */
	ptxdesc->txdw4 |= cpu_to_le32(USERATE);/* rate control always by driver */

	अगर ((pxmitframe->frame_tag & 0x0f) == DATA_FRAMETAG) अणु
		/* offset 4 */
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id & 0x3F);

		qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid << RATE_ID_SHT) & 0x000F0000);

		fill_txdesc_sectype(pattrib, ptxdesc);

		अगर (pattrib->ampdu_en) अणु
			ptxdesc->txdw2 |= cpu_to_le32(AGG_EN);/* AGG EN */
			ptxdesc->txdw6 = cpu_to_le32(0x6666f800);
		पूर्ण अन्यथा अणु
			ptxdesc->txdw2 |= cpu_to_le32(AGG_BK);/* AGG BK */
		पूर्ण

		/* offset 8 */

		/* offset 12 */
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum << SEQ_SHT) & 0x0FFF0000);

		/* offset 16 , offset 20 */
		अगर (pattrib->qos_en)
			ptxdesc->txdw4 |= cpu_to_le32(QOS);/* QoS */

		/* offset 20 */
		अगर (pxmitframe->agg_num > 1)
			ptxdesc->txdw5 |= cpu_to_le32((pxmitframe->agg_num << USB_TXAGG_NUM_SHT) & 0xFF000000);

		अगर ((pattrib->ether_type != 0x888e) &&
		    (pattrib->ether_type != 0x0806) &&
		    (pattrib->ether_type != 0x88b4) &&
		    (pattrib->dhcp_pkt != 1)) अणु
			/* Non EAP & ARP & DHCP type data packet */

			fill_txdesc_vcs(pattrib, &ptxdesc->txdw4);
			fill_txdesc_phy(pattrib, &ptxdesc->txdw4);

			ptxdesc->txdw4 |= cpu_to_le32(0x00000008);/* RTS Rate=24M */
			ptxdesc->txdw5 |= cpu_to_le32(0x0001ff00);/* DATA/RTS  Rate FB LMT */

			अगर (pattrib->ht_en) अणु
				अगर (ODM_RA_GetShortGI_8188E(odmpriv, pattrib->mac_id))
					ptxdesc->txdw5 |= cpu_to_le32(SGI);/* SGI */
			पूर्ण
			data_rate = ODM_RA_GetDecisionRate_8188E(odmpriv, pattrib->mac_id);
			ptxdesc->txdw5 |= cpu_to_le32(data_rate & 0x3F);
			pwr_status = ODM_RA_GetHwPwrStatus_8188E(odmpriv, pattrib->mac_id);
			ptxdesc->txdw4 |= cpu_to_le32((pwr_status & 0x7) << PWR_STATUS_SHT);
		पूर्ण अन्यथा अणु
			/*  EAP data packet and ARP packet and DHCP. */
			/*  Use the 1M data rate to send the EAP/ARP packet. */
			/*  This will maybe make the handshake smooth. */
			ptxdesc->txdw2 |= cpu_to_le32(AGG_BK);/* AGG BK */
			अगर (pmlmeinfo->preamble_mode == PREAMBLE_SHORT)
				ptxdesc->txdw4 |= cpu_to_le32(BIT(24));/*  DATA_SHORT */
			ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
		पूर्ण
	पूर्ण अन्यथा अगर ((pxmitframe->frame_tag & 0x0f) == MGNT_FRAMETAG) अणु
		/* offset 4 */
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id & 0x3f);

		qsel = (uपूर्णांक)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid << RATE_ID_SHT) & 0x000f0000);

		/* offset 8 */
		/* CCX-TXRPT ack क्रम xmit mgmt frames. */
		अगर (pxmitframe->ack_report)
			ptxdesc->txdw2 |= cpu_to_le32(BIT(19));

		/* offset 12 */
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum << SEQ_SHT) & 0x0FFF0000);

		/* offset 20 */
		ptxdesc->txdw5 |= cpu_to_le32(RTY_LMT_EN);/* retry limit enable */
		अगर (pattrib->retry_ctrl)
			ptxdesc->txdw5 |= cpu_to_le32(0x00180000);/* retry limit = 6 */
		अन्यथा
			ptxdesc->txdw5 |= cpu_to_le32(0x00300000);/* retry limit = 12 */

		ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
	पूर्ण अन्यथा अगर ((pxmitframe->frame_tag & 0x0f) == TXAGG_FRAMETAG) अणु
		DBG_88E("pxmitframe->frame_tag == TXAGG_FRAMETAG\n");
	पूर्ण अन्यथा अणु
		DBG_88E("pxmitframe->frame_tag = %d\n", pxmitframe->frame_tag);

		/* offset 4 */
		ptxdesc->txdw1 |= cpu_to_le32((4) & 0x3f);/* CAM_ID(MAC_ID) */

		ptxdesc->txdw1 |= cpu_to_le32((6 << RATE_ID_SHT) & 0x000f0000);/* raid */

		/* offset 8 */

		/* offset 12 */
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum << SEQ_SHT) & 0x0fff0000);

		/* offset 20 */
		ptxdesc->txdw5 |= cpu_to_le32(MRateToHwRate(pmlmeext->tx_rate));
	पूर्ण

	/*  2009.11.05. tynli_test. Suggested by SD4 Filen क्रम FW LPS. */
	/*  (1) The sequence number of each non-Qos frame / broadcast / multicast / */
	/*  mgnt frame should be controlled by Hw because Fw will also send null data */
	/*  which we cannot control when Fw LPS enable. */
	/*  --> शेष enable non-Qos data sequense number. 2010.06.23. by tynli. */
	/*  (2) Enable HW SEQ control क्रम beacon packet, because we use Hw beacon. */
	/*  (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos packets. */
	/*  2010.06.23. Added by tynli. */
	अगर (!pattrib->qos_en) अणु
		ptxdesc->txdw3 |= cpu_to_le32(EN_HWSEQ); /*  Hw set sequence number */
		ptxdesc->txdw4 |= cpu_to_le32(HW_SSN);	/*  Hw set sequence number */
	पूर्ण

	rtl88eu_dm_set_tx_ant_by_tx_info(odmpriv, pmem, pattrib->mac_id);

	rtl8188eu_cal_txdesc_chksum(ptxdesc);
	_dbg_dump_tx_info(adapt, pxmitframe->frame_tag, ptxdesc);
	वापस pull;
पूर्ण

/* क्रम non-agg data frame or management frame */
अटल s32 rtw_dump_xframe(काष्ठा adapter *adapt, काष्ठा xmit_frame *pxmitframe)
अणु
	s32 ret = _SUCCESS;
	s32 inner_ret = _SUCCESS;
	पूर्णांक t, sz, w_sz, pull = 0;
	u8 *mem_addr;
	u32 ff_hwaddr;
	काष्ठा xmit_buf *pxmitbuf = pxmitframe->pxmitbuf;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा xmit_priv *pxmitpriv = &adapt->xmitpriv;

	अगर ((pxmitframe->frame_tag == DATA_FRAMETAG) &&
	    (pxmitframe->attrib.ether_type != 0x0806) &&
	    (pxmitframe->attrib.ether_type != 0x888e) &&
	    (pxmitframe->attrib.ether_type != 0x88b4) &&
	    (pxmitframe->attrib.dhcp_pkt != 1))
		rtw_issue_addbareq_cmd(adapt, pxmitframe);
	mem_addr = pxmitframe->buf_addr;

	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("%s()\n", __func__));

	क्रम (t = 0; t < pattrib->nr_frags; t++) अणु
		अगर (inner_ret != _SUCCESS && ret == _SUCCESS)
			ret = _FAIL;

		अगर (t != (pattrib->nr_frags - 1)) अणु
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("pattrib->nr_frags=%d\n", pattrib->nr_frags));

			sz = pxmitpriv->frag_len;
			sz = sz - 4 - pattrib->icv_len;
		पूर्ण अन्यथा अणु
			/* no frag */
			sz = pattrib->last_txcmdsz;
		पूर्ण

		pull = update_txdesc(pxmitframe, mem_addr, sz, false);

		अगर (pull) अणु
			mem_addr += PACKET_OFFSET_SZ; /* pull txdesc head */
			pxmitframe->buf_addr = mem_addr;
			w_sz = sz + TXDESC_SIZE;
		पूर्ण अन्यथा अणु
			w_sz = sz + TXDESC_SIZE + PACKET_OFFSET_SZ;
		पूर्ण
		ff_hwaddr = rtw_get_ff_hwaddr(pxmitframe);

		inner_ret = usb_ग_लिखो_port(adapt, ff_hwaddr, w_sz, pxmitbuf);

		rtw_count_tx_stats(adapt, pxmitframe, sz);

		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("rtw_write_port, w_sz=%d\n", w_sz));

		mem_addr += w_sz;

		mem_addr = (u8 *)round_up((माप_प्रकार)mem_addr, 4);
	पूर्ण

	rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

	अगर  (ret != _SUCCESS)
		rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_UNKNOWN);

	वापस ret;
पूर्ण

अटल u32 xmitframe_need_length(काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	u32 len;

	/*  no consider fragement */
	len = pattrib->hdrlen + pattrib->iv_len +
		SNAP_SIZE + माप(u16) +
		pattrib->pktlen +
		((pattrib->bswenc) ? pattrib->icv_len : 0);

	अगर (pattrib->encrypt == _TKIP_)
		len += 8;

	वापस len;
पूर्ण

bool rtl8188eu_xmitframe_complete(काष्ठा adapter *adapt,
				  काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा xmit_frame *pfirstframe = शून्य;
	काष्ठा xmit_buf *pxmitbuf;

	/*  aggregate variable */
	काष्ठा hw_xmit *phwxmit;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा tx_servq *ptxservq = शून्य;

	काष्ठा list_head *xmitframe_plist = शून्य, *xmitframe_phead = शून्य;

	u32 pbuf;	/*  next pkt address */
	u32 pbuf_tail;	/*  last pkt tail */
	u32 len;	/*  packet length, except TXDESC_SIZE and PKT_OFFSET */

	u32 bulksize = adapt->HalData->UsbBulkOutSize;
	u8 desc_cnt;
	u32 bulkptr;

	/*  dump frame variable */
	u32 ff_hwaddr;

	RT_TRACE(_module_rtl8192c_xmit_c_, _drv_info_, ("+xmitframe_complete\n"));

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	अगर (!pxmitbuf)
		वापस false;

	/* 3 1. pick up first frame */
	rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

	pxmitframe = rtw_dequeue_xframe(pxmitpriv, pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);
	अगर (!pxmitframe) अणु
		/*  no more xmit frame, release xmit buffer */
		rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
		वापस false;
	पूर्ण

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	pxmitframe->agg_num = 1; /*  alloc xmitframe should assign to 1. */
	pxmitframe->pkt_offset = 1; /*  first frame of aggregation, reserve offset */

	rtw_xmitframe_coalesce(adapt, pxmitframe->pkt, pxmitframe);

	/*  always वापस ndis_packet after rtw_xmitframe_coalesce */
	rtw_os_xmit_complete(adapt, pxmitframe);

	/* 3 2. aggregate same priority and same DA(AP or STA) frames */
	pfirstframe = pxmitframe;
	len = xmitframe_need_length(pfirstframe) + TXDESC_SIZE + (pfirstframe->pkt_offset * PACKET_OFFSET_SZ);
	pbuf_tail = len;
	pbuf = round_up(pbuf_tail, 8);

	/*  check pkt amount in one bulk */
	desc_cnt = 0;
	bulkptr = bulksize;
	अगर (pbuf < bulkptr) अणु
		desc_cnt++;
	पूर्ण अन्यथा अणु
		desc_cnt = 0;
		bulkptr = ((pbuf / bulksize) + 1) * bulksize; /*  round to next bulksize */
	पूर्ण

	/*  dequeue same priority packet from station tx queue */
	psta = pfirstframe->attrib.psta;
	चयन (pfirstframe->attrib.priority) अणु
	हाल 1:
	हाल 2:
		ptxservq = &psta->sta_xmitpriv.bk_q;
		phwxmit = pxmitpriv->hwxmits + 3;
		अवरोध;
	हाल 4:
	हाल 5:
		ptxservq = &psta->sta_xmitpriv.vi_q;
		phwxmit = pxmitpriv->hwxmits + 1;
		अवरोध;
	हाल 6:
	हाल 7:
		ptxservq = &psta->sta_xmitpriv.vo_q;
		phwxmit = pxmitpriv->hwxmits;
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &psta->sta_xmitpriv.be_q;
		phwxmit = pxmitpriv->hwxmits + 2;
		अवरोध;
	पूर्ण
	spin_lock_bh(&pxmitpriv->lock);

	xmitframe_phead = get_list_head(&ptxservq->sta_pending);
	xmitframe_plist = xmitframe_phead->next;

	जबतक (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);
		xmitframe_plist = xmitframe_plist->next;

		pxmitframe->agg_num = 0; /*  not first frame of aggregation */
		pxmitframe->pkt_offset = 0; /*  not first frame of aggregation, no need to reserve offset */

		len = xmitframe_need_length(pxmitframe) + TXDESC_SIZE + (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);

		अगर (round_up(pbuf + len, 8) > MAX_XMITBUF_SZ) अणु
			pxmitframe->agg_num = 1;
			pxmitframe->pkt_offset = 1;
			अवरोध;
		पूर्ण
		list_del_init(&pxmitframe->list);
		ptxservq->qcnt--;
		phwxmit->accnt--;

		pxmitframe->buf_addr = pxmitbuf->pbuf + pbuf;

		rtw_xmitframe_coalesce(adapt, pxmitframe->pkt, pxmitframe);
		/*  always वापस ndis_packet after rtw_xmitframe_coalesce */
		rtw_os_xmit_complete(adapt, pxmitframe);

		/*  (len - TXDESC_SIZE) == pxmitframe->attrib.last_txcmdsz */
		update_txdesc(pxmitframe, pxmitframe->buf_addr, pxmitframe->attrib.last_txcmdsz, true);

		/*  करोn't need xmitframe any more */
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

		/*  handle poपूर्णांकer and stop condition */
		pbuf_tail = pbuf + len;
		pbuf = round_up(pbuf_tail, 8);

		pfirstframe->agg_num++;
		अगर (pfirstframe->agg_num ==  MAX_TX_AGG_PACKET_NUMBER)
			अवरोध;

		अगर (pbuf < bulkptr) अणु
			desc_cnt++;
			अगर (desc_cnt == adapt->HalData->UsbTxAggDescNum)
				अवरोध;
		पूर्ण अन्यथा अणु
			desc_cnt = 0;
			bulkptr = ((pbuf / bulksize) + 1) * bulksize;
		पूर्ण
	पूर्ण /* end जबतक (aggregate same priority and same DA(AP or STA) frames) */

	अगर (list_empty(&ptxservq->sta_pending.queue))
		list_del_init(&ptxservq->tx_pending);

	spin_unlock_bh(&pxmitpriv->lock);
	अगर ((pfirstframe->attrib.ether_type != 0x0806) &&
	    (pfirstframe->attrib.ether_type != 0x888e) &&
	    (pfirstframe->attrib.ether_type != 0x88b4) &&
	    (pfirstframe->attrib.dhcp_pkt != 1))
		rtw_issue_addbareq_cmd(adapt, pfirstframe);
	/* 3 3. update first frame txdesc */
	अगर ((pbuf_tail % bulksize) == 0) अणु
		/*  हटाओ pkt_offset */
		pbuf_tail -= PACKET_OFFSET_SZ;
		pfirstframe->buf_addr += PACKET_OFFSET_SZ;
		pfirstframe->pkt_offset--;
	पूर्ण

	update_txdesc(pfirstframe, pfirstframe->buf_addr, pfirstframe->attrib.last_txcmdsz, true);

	/* 3 4. ग_लिखो xmit buffer to USB FIFO */
	ff_hwaddr = rtw_get_ff_hwaddr(pfirstframe);
	usb_ग_लिखो_port(adapt, ff_hwaddr, pbuf_tail, pxmitbuf);

	/* 3 5. update statisitc */
	pbuf_tail -= (pfirstframe->agg_num * TXDESC_SIZE);
	pbuf_tail -= (pfirstframe->pkt_offset * PACKET_OFFSET_SZ);

	rtw_count_tx_stats(adapt, pfirstframe, pbuf_tail);

	rtw_मुक्त_xmitframe(pxmitpriv, pfirstframe);

	वापस true;
पूर्ण

/*
 * Return
 *	true	dump packet directly
 *	false	enqueue packet
 */
bool rtw_hal_xmit(काष्ठा adapter *adapt, काष्ठा xmit_frame *pxmitframe)
अणु
	s32 res;
	काष्ठा xmit_buf *pxmitbuf = शून्य;
	काष्ठा xmit_priv *pxmitpriv = &adapt->xmitpriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा mlme_priv *pmlmepriv = &adapt->mlmepriv;

	spin_lock_bh(&pxmitpriv->lock);

	अगर (rtw_txframes_sta_ac_pending(adapt, pattrib) > 0)
		जाओ enqueue;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING))
		जाओ enqueue;

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	अगर (!pxmitbuf)
		जाओ enqueue;

	spin_unlock_bh(&pxmitpriv->lock);

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	res = rtw_xmitframe_coalesce(adapt, pxmitframe->pkt, pxmitframe);

	अगर (res == _SUCCESS) अणु
		rtw_dump_xframe(adapt, pxmitframe);
	पूर्ण अन्यथा अणु
		DBG_88E("==> %s xmitframe_coalesce failed\n", __func__);
		rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
	पूर्ण

	वापस true;

enqueue:
	res = rtw_xmitframe_enqueue(adapt, pxmitframe);
	spin_unlock_bh(&pxmitpriv->lock);

	अगर (res != _SUCCESS) अणु
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("pre_xmitframe: enqueue xmitframe fail\n"));
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);

		/*  Trick, make the statistics correct */
		pxmitpriv->tx_pkts--;
		pxmitpriv->tx_drop++;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

s32 rtw_hal_mgnt_xmit(काष्ठा adapter *adapt, काष्ठा xmit_frame *pmgntframe)
अणु
	काष्ठा xmit_priv *xmitpriv = &adapt->xmitpriv;

	rtl88eu_mon_xmit_hook(adapt->pmondev, pmgntframe, xmitpriv->frag_len);
	वापस rtw_dump_xframe(adapt, pmgntframe);
पूर्ण
