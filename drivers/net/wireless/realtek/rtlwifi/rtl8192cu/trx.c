<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../usb.h"
#समावेश "../ps.h"
#समावेश "../base.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "mac.h"
#समावेश "trx.h"
#समावेश "../rtl8192c/fw_common.h"

अटल पूर्णांक configvertoutep(काष्ठा ieee80211_hw *hw)
अणु
	u8 ep_cfg, txqsele;
	u8 ep_nums = 0;

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);

	rtlusb->out_queue_sel = 0;
	ep_cfg = rtl_पढ़ो_byte(rtlpriv, REG_TEST_SIE_OPTIONAL);
	ep_cfg = (ep_cfg & USB_TEST_EP_MASK) >> USB_TEST_EP_SHIFT;
	चयन (ep_cfg)	अणु
	हाल 0:		/* 2 bulk OUT, 1 bulk IN */
	हाल 3:
		rtlusb->out_queue_sel  = TX_SELE_HQ | TX_SELE_LQ;
		ep_nums = 2;
		अवरोध;
	हाल 1:	/* 1 bulk IN/OUT => map all endpoपूर्णांक to Low queue */
	हाल 2:	/* 1 bulk IN, 1 bulk OUT => map all endpoपूर्णांक to High queue */
		txqsele = rtl_पढ़ो_byte(rtlpriv, REG_TEST_USB_TXQS);
		अगर (txqsele & 0x0F) /* /map all endpoपूर्णांक to High queue */
			rtlusb->out_queue_sel =  TX_SELE_HQ;
		अन्यथा अगर (txqsele&0xF0) /* map all endpoपूर्णांक to Low queue */
			rtlusb->out_queue_sel =  TX_SELE_LQ;
		ep_nums = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस (rtlusb->out_ep_nums == ep_nums) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक configvernoutep(काष्ठा ieee80211_hw *hw)
अणु
	u8 ep_cfg;
	u8 ep_nums = 0;

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);

	rtlusb->out_queue_sel = 0;
	/* Normal and High queue */
	ep_cfg =  rtl_पढ़ो_byte(rtlpriv, (REG_NORMAL_SIE_EP + 1));
	अगर (ep_cfg & USB_NORMAL_SIE_EP_MASK) अणु
		rtlusb->out_queue_sel |= TX_SELE_HQ;
		ep_nums++;
	पूर्ण
	अगर ((ep_cfg >> USB_NORMAL_SIE_EP_SHIFT) & USB_NORMAL_SIE_EP_MASK) अणु
		rtlusb->out_queue_sel |= TX_SELE_NQ;
		ep_nums++;
	पूर्ण
	/* Low queue */
	ep_cfg =  rtl_पढ़ो_byte(rtlpriv, (REG_NORMAL_SIE_EP + 2));
	अगर (ep_cfg & USB_NORMAL_SIE_EP_MASK) अणु
		rtlusb->out_queue_sel |= TX_SELE_LQ;
		ep_nums++;
	पूर्ण
	वापस (rtlusb->out_ep_nums == ep_nums) ? 0 : -EINVAL;
पूर्ण

अटल व्योम twooutepmapping(काष्ठा ieee80211_hw *hw, bool is_chip8,
			     bool  bwअगरicfg, काष्ठा rtl_ep_map *ep_map)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (bwअगरicfg) अणु /* क्रम WMM */
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"USB Chip-B & WMM Setting.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 2;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VO] = 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	पूर्ण अन्यथा अणु /* typical setting */
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"USB typical Setting.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 3;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 2;
		ep_map->ep_mapping[RTL_TXQ_VO]	= 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	पूर्ण
पूर्ण

अटल व्योम threeoutepmapping(काष्ठा ieee80211_hw *hw, bool  bwअगरicfg,
			       काष्ठा rtl_ep_map *ep_map)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (bwअगरicfg) अणु /* क्रम WMM */
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"USB 3EP Setting for WMM.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 5;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VO]	= 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	पूर्ण अन्यथा अणु /* typical setting */
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"USB 3EP Setting for typical.....\n");
		ep_map->ep_mapping[RTL_TXQ_BE]	= 5;
		ep_map->ep_mapping[RTL_TXQ_BK]	= 5;
		ep_map->ep_mapping[RTL_TXQ_VI]	= 3;
		ep_map->ep_mapping[RTL_TXQ_VO]	= 2;
		ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
		ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
		ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
	पूर्ण
पूर्ण

अटल व्योम oneoutepmapping(काष्ठा ieee80211_hw *hw, काष्ठा rtl_ep_map *ep_map)
अणु
	ep_map->ep_mapping[RTL_TXQ_BE]	= 2;
	ep_map->ep_mapping[RTL_TXQ_BK]	= 2;
	ep_map->ep_mapping[RTL_TXQ_VI]	= 2;
	ep_map->ep_mapping[RTL_TXQ_VO] = 2;
	ep_map->ep_mapping[RTL_TXQ_MGT] = 2;
	ep_map->ep_mapping[RTL_TXQ_BCN] = 2;
	ep_map->ep_mapping[RTL_TXQ_HI]	= 2;
पूर्ण

अटल पूर्णांक _out_ep_mapping(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक err = 0;
	bool ischipn, bwअगरicfg = false;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);
	काष्ठा rtl_ep_map *ep_map = &(rtlusb->ep_map);

	ischipn = IS_NORMAL_CHIP(rtlhal->version);
	चयन (rtlusb->out_ep_nums) अणु
	हाल 2:
		twooutepmapping(hw, ischipn, bwअगरicfg, ep_map);
		अवरोध;
	हाल 3:
		/* Test chip करोesn't support three out EPs. */
		अगर (!ischipn) अणु
			err  =  -EINVAL;
			जाओ err_out;
		पूर्ण
		threeoutepmapping(hw, ischipn, ep_map);
		अवरोध;
	हाल 1:
		oneoutepmapping(hw, ep_map);
		अवरोध;
	शेष:
		err  =  -EINVAL;
		अवरोध;
	पूर्ण
err_out:
	वापस err;

पूर्ण

/* endpoपूर्णांक mapping */
पूर्णांक  rtl8192cu_endpoपूर्णांक_mapping(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक error = 0;

	अगर (likely(IS_NORMAL_CHIP(rtlhal->version)))
		error = configvernoutep(hw);
	अन्यथा
		error = configvertoutep(hw);
	अगर (error)
		जाओ err_out;
	error = _out_ep_mapping(hw);
	अगर (error)
		जाओ err_out;
err_out:
	वापस error;
पूर्ण

u16 rtl8192cu_mq_to_hwq(__le16 fc, u16 mac80211_queue_index)
अणु
	u16 hw_queue_index;

	अगर (unlikely(ieee80211_is_beacon(fc))) अणु
		hw_queue_index = RTL_TXQ_BCN;
		जाओ out;
	पूर्ण
	अगर (ieee80211_is_mgmt(fc)) अणु
		hw_queue_index = RTL_TXQ_MGT;
		जाओ out;
	पूर्ण
	चयन (mac80211_queue_index) अणु
	हाल 0:
		hw_queue_index = RTL_TXQ_VO;
		अवरोध;
	हाल 1:
		hw_queue_index = RTL_TXQ_VI;
		अवरोध;
	हाल 2:
		hw_queue_index = RTL_TXQ_BE;
		अवरोध;
	हाल 3:
		hw_queue_index = RTL_TXQ_BK;
		अवरोध;
	शेष:
		hw_queue_index = RTL_TXQ_BE;
		WARN_ONCE(true, "rtl8192cu: QSLT_BE queue, skb_queue:%d\n",
			  mac80211_queue_index);
		अवरोध;
	पूर्ण
out:
	वापस hw_queue_index;
पूर्ण

अटल क्रमागत rtl_desc_qsel _rtl8192cu_mq_to_descq(काष्ठा ieee80211_hw *hw,
					 __le16 fc, u16 mac80211_queue_index)
अणु
	क्रमागत rtl_desc_qsel qsel;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (unlikely(ieee80211_is_beacon(fc))) अणु
		qsel = QSLT_BEACON;
		जाओ out;
	पूर्ण
	अगर (ieee80211_is_mgmt(fc)) अणु
		qsel = QSLT_MGNT;
		जाओ out;
	पूर्ण
	चयन (mac80211_queue_index) अणु
	हाल 0:	/* VO */
		qsel = QSLT_VO;
		rtl_dbg(rtlpriv, COMP_USB, DBG_DMESG,
			"VO queue, set qsel = 0x%x\n", QSLT_VO);
		अवरोध;
	हाल 1:	/* VI */
		qsel = QSLT_VI;
		rtl_dbg(rtlpriv, COMP_USB, DBG_DMESG,
			"VI queue, set qsel = 0x%x\n", QSLT_VI);
		अवरोध;
	हाल 3:	/* BK */
		qsel = QSLT_BK;
		rtl_dbg(rtlpriv, COMP_USB, DBG_DMESG,
			"BK queue, set qsel = 0x%x\n", QSLT_BK);
		अवरोध;
	हाल 2:	/* BE */
	शेष:
		qsel = QSLT_BE;
		rtl_dbg(rtlpriv, COMP_USB, DBG_DMESG,
			"BE queue, set qsel = 0x%x\n", QSLT_BE);
		अवरोध;
	पूर्ण
out:
	वापस qsel;
पूर्ण

/* =============================================================== */

/*----------------------------------------------------------------------
 *
 *	Rx handler
 *
 *---------------------------------------------------------------------- */
bool rtl92cu_rx_query_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा rtl_stats *stats,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rx_fwinfo_92c *p_drvinfo;
	काष्ठा rx_desc_92c *p_desc = (काष्ठा rx_desc_92c *)pdesc8;
	__le32 *pdesc = (__le32 *)pdesc8;
	u32 phystatus = get_rx_desc_phy_status(pdesc);

	stats->length = (u16)get_rx_desc_pkt_len(pdesc);
	stats->rx_drvinfo_size = (u8)get_rx_desc_drvinfo_size(pdesc) *
				 RX_DRV_INFO_SIZE_UNIT;
	stats->rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(pdesc) & 0x03);
	stats->icv = (u16)get_rx_desc_icv(pdesc);
	stats->crc = (u16)get_rx_desc_crc32(pdesc);
	stats->hwerror = (stats->crc | stats->icv);
	stats->decrypted = !get_rx_desc_swdec(pdesc);
	stats->rate = (u8)get_rx_desc_rx_mcs(pdesc);
	stats->लघुpreamble = (u16)get_rx_desc_splcp(pdesc);
	stats->isampdu = (bool)(get_rx_desc_paggr(pdesc) == 1);
	stats->isfirst_ampdu = (bool)((get_rx_desc_paggr(pdesc) == 1) &&
				      (get_rx_desc_faggr(pdesc) == 1));
	stats->बारtamp_low = get_rx_desc_tsfl(pdesc);
	stats->rx_is40mhzpacket = (bool)get_rx_desc_bw(pdesc);
	stats->is_ht = (bool)get_rx_desc_rx_ht(pdesc);
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;
	अगर (get_rx_desc_crc32(pdesc))
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (!get_rx_desc_swdec(pdesc))
		rx_status->flag |= RX_FLAG_DECRYPTED;
	अगर (get_rx_desc_bw(pdesc))
		rx_status->bw = RATE_INFO_BW_40;
	अगर (get_rx_desc_rx_ht(pdesc))
		rx_status->encoding = RX_ENC_HT;
	rx_status->flag |= RX_FLAG_MACTIME_START;
	अगर (stats->decrypted)
		rx_status->flag |= RX_FLAG_DECRYPTED;
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, stats->is_ht,
						   false, stats->rate);
	rx_status->maस_समय = get_rx_desc_tsfl(pdesc);
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_92c *)(skb->data +
						     stats->rx_bufshअगरt);
		rtl92c_translate_rx_संकेत_stuff(hw, skb, stats, p_desc,
						 p_drvinfo);
	पूर्ण
	/*rx_status->qual = stats->संकेत; */
	rx_status->संकेत = stats->recvसंकेतघातer + 10;
	वापस true;
पूर्ण

#घोषणा RTL_RX_DRV_INFO_UNIT		8

अटल व्योम _rtl_rx_process(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status =
		 (काष्ठा ieee80211_rx_status *)IEEE80211_SKB_RXCB(skb);
	u32 skb_len, pkt_len, drvinfo_len;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	__le32 *rxdesc;
	काष्ठा rtl_stats stats = अणु
		.संकेत = 0,
		.rate = 0,
	पूर्ण;
	काष्ठा rx_fwinfo_92c *p_drvinfo;
	bool bv;
	__le16 fc;
	काष्ठा ieee80211_hdr *hdr;

	स_रखो(rx_status, 0, माप(*rx_status));
	rxdesc	= (__le32 *)skb->data;
	skb_len	= skb->len;
	drvinfo_len = (get_rx_desc_drvinfo_size(rxdesc) * RTL_RX_DRV_INFO_UNIT);
	pkt_len		= get_rx_desc_pkt_len(rxdesc);
	/* TODO: Error recovery. drop this skb or something. */
	WARN_ON(skb_len < (pkt_len + RTL_RX_DESC_SIZE + drvinfo_len));
	stats.length = (u16)get_rx_desc_pkt_len(rxdesc);
	stats.rx_drvinfo_size = (u8)get_rx_desc_drvinfo_size(rxdesc) *
				RX_DRV_INFO_SIZE_UNIT;
	stats.rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(rxdesc) & 0x03);
	stats.icv = (u16)get_rx_desc_icv(rxdesc);
	stats.crc = (u16)get_rx_desc_crc32(rxdesc);
	stats.hwerror = (stats.crc | stats.icv);
	stats.decrypted = !get_rx_desc_swdec(rxdesc);
	stats.rate = (u8)get_rx_desc_rx_mcs(rxdesc);
	stats.लघुpreamble = (u16)get_rx_desc_splcp(rxdesc);
	stats.isampdu = (bool)((get_rx_desc_paggr(rxdesc) == 1) &&
			       (get_rx_desc_faggr(rxdesc) == 1));
	stats.बारtamp_low = get_rx_desc_tsfl(rxdesc);
	stats.rx_is40mhzpacket = (bool)get_rx_desc_bw(rxdesc);
	stats.is_ht = (bool)get_rx_desc_rx_ht(rxdesc);
	/* TODO: is center_freq changed when करोing scan? */
	/* TODO: Shall we add protection or just skip those two step? */
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;
	अगर (get_rx_desc_crc32(rxdesc))
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (!get_rx_desc_swdec(rxdesc))
		rx_status->flag |= RX_FLAG_DECRYPTED;
	अगर (get_rx_desc_bw(rxdesc))
		rx_status->bw = RATE_INFO_BW_40;
	अगर (get_rx_desc_rx_ht(rxdesc))
		rx_status->encoding = RX_ENC_HT;
	/* Data rate */
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, stats.is_ht,
						   false, stats.rate);
	/*  There is a phy status after this rx descriptor. */
	अगर (get_rx_desc_phy_status(rxdesc)) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_92c *)(rxdesc + RTL_RX_DESC_SIZE);
		rtl92c_translate_rx_संकेत_stuff(hw, skb, &stats,
				 (काष्ठा rx_desc_92c *)rxdesc, p_drvinfo);
	पूर्ण
	skb_pull(skb, (drvinfo_len + RTL_RX_DESC_SIZE));
	hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fc = hdr->frame_control;
	bv = ieee80211_is_probe_resp(fc);
	अगर (bv)
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Got probe response frame\n");
	अगर (ieee80211_is_beacon(fc))
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Got beacon frame\n");
	अगर (ieee80211_is_data(fc))
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Got data frame\n");
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"Fram: fc = 0x%X addr1 = 0x%02X:0x%02X:0x%02X:0x%02X:0x%02X:0x%02X\n",
		fc,
		(u32)hdr->addr1[0], (u32)hdr->addr1[1],
		(u32)hdr->addr1[2], (u32)hdr->addr1[3],
		(u32)hdr->addr1[4], (u32)hdr->addr1[5]);
	ieee80211_rx(hw, skb);
पूर्ण

व्योम  rtl8192cu_rx_hdl(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff * skb)
अणु
	_rtl_rx_process(hw, skb);
पूर्ण

/*----------------------------------------------------------------------
 *
 *	Tx handler
 *
 *---------------------------------------------------------------------- */
व्योम rtl8192c_tx_cleanup(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff  *skb)
अणु
पूर्ण

पूर्णांक rtl8192c_tx_post_hdl(काष्ठा ieee80211_hw *hw, काष्ठा urb *urb,
			 काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

काष्ठा sk_buff *rtl8192c_tx_aggregate_hdl(काष्ठा ieee80211_hw *hw,
					   काष्ठा sk_buff_head *list)
अणु
	वापस skb_dequeue(list);
पूर्ण

/*======================================== trx ===============================*/

अटल व्योम _rtl_fill_usb_tx_desc(__le32 *txdesc)
अणु
	set_tx_desc_own(txdesc, 1);
	set_tx_desc_last_seg(txdesc, 1);
	set_tx_desc_first_seg(txdesc, 1);
पूर्ण

/*
 *	For HW recovery inक्रमmation
 */
अटल व्योम _rtl_tx_desc_checksum(__le32 *txdesc)
अणु
	__le16 *ptr = (__le16 *)txdesc;
	u16	checksum = 0;
	u32 index;

	/* Clear first */
	set_tx_desc_tx_desc_checksum(txdesc, 0);
	क्रम (index = 0; index < 16; index++)
		checksum = checksum ^ le16_to_cpu(*(ptr + index));
	set_tx_desc_tx_desc_checksum(txdesc, checksum);
पूर्ण

व्योम rtl92cu_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  u8 queue_index,
			  काष्ठा rtl_tcb_desc *tcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool शेषadapter = true;
	u8 *qc = ieee80211_get_qos_ctl(hdr);
	u8 tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 rate_flag = info->control.rates[0].flags;
	u16 pktlen = skb->len;
	क्रमागत rtl_desc_qsel fw_qsel = _rtl8192cu_mq_to_descq(hw, fc,
						skb_get_queue_mapping(skb));
	u8 *txdesc8;
	__le32 *txdesc;

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	rtl_get_tcb_desc(hw, info, sta, skb, tcb_desc);
	txdesc8 = skb_push(skb, RTL_TX_HEADER_SIZE);
	txdesc = (__le32 *)txdesc8;
	स_रखो(txdesc, 0, RTL_TX_HEADER_SIZE);
	set_tx_desc_pkt_size(txdesc, pktlen);
	set_tx_desc_linip(txdesc, 0);
	set_tx_desc_pkt_offset(txdesc, RTL_DUMMY_OFFSET);
	set_tx_desc_offset(txdesc, RTL_TX_HEADER_SIZE);
	set_tx_desc_tx_rate(txdesc, tcb_desc->hw_rate);
	अगर (tcb_desc->use_लघुgi || tcb_desc->use_लघुpreamble)
		set_tx_desc_data_लघुgi(txdesc, 1);
	अगर (mac->tids[tid].agg.agg_state == RTL_AGG_ON &&
		    info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		set_tx_desc_agg_enable(txdesc, 1);
		set_tx_desc_max_agg_num(txdesc, 0x14);
	पूर्ण अन्यथा अणु
		set_tx_desc_agg_अवरोध(txdesc, 1);
	पूर्ण
	set_tx_desc_seq(txdesc, seq_number);
	set_tx_desc_rts_enable(txdesc,
			       ((tcb_desc->rts_enable &&
				!tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_hw_rts_enable(txdesc,
				  ((tcb_desc->rts_enable ||
				   tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_cts2self(txdesc, ((tcb_desc->cts_enable) ? 1 : 0));
	set_tx_desc_rts_stbc(txdesc, ((tcb_desc->rts_stbc) ? 1 : 0));
	set_tx_desc_rts_rate(txdesc, tcb_desc->rts_rate);
	set_tx_desc_rts_bw(txdesc, 0);
	set_tx_desc_rts_sc(txdesc, tcb_desc->rts_sc);
	set_tx_desc_rts_लघु(txdesc,
			      ((tcb_desc->rts_rate <= DESC_RATE54M) ?
			       (tcb_desc->rts_use_लघुpreamble ? 1 : 0)
			       : (tcb_desc->rts_use_लघुgi ? 1 : 0)));
	अगर (mac->bw_40) अणु
		अगर (rate_flag & IEEE80211_TX_RC_DUP_DATA) अणु
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, 3);
		पूर्ण अन्यथा अगर(rate_flag & IEEE80211_TX_RC_40_MHZ_WIDTH)अणु
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, mac->cur_40_prime_sc);
		पूर्ण अन्यथा अणु
			set_tx_desc_data_bw(txdesc, 0);
			set_tx_desc_data_sc(txdesc, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_tx_desc_data_bw(txdesc, 0);
		set_tx_desc_data_sc(txdesc, 0);
	पूर्ण
	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(mac->vअगर, mac->bssid);
	अगर (sta) अणु
		u8 ampdu_density = sta->ht_cap.ampdu_density;

		set_tx_desc_ampdu_density(txdesc, ampdu_density);
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (info->control.hw_key) अणु
		काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;

		चयन (keyconf->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			set_tx_desc_sec_type(txdesc, 0x1);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			set_tx_desc_sec_type(txdesc, 0x3);
			अवरोध;
		शेष:
			set_tx_desc_sec_type(txdesc, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण
	set_tx_desc_pkt_id(txdesc, 0);
	set_tx_desc_queue_sel(txdesc, fw_qsel);
	set_tx_desc_data_rate_fb_limit(txdesc, 0x1F);
	set_tx_desc_rts_rate_fb_limit(txdesc, 0xF);
	set_tx_desc_disable_fb(txdesc, 0);
	set_tx_desc_use_rate(txdesc, tcb_desc->use_driver_rate ? 1 : 0);
	अगर (ieee80211_is_data_qos(fc)) अणु
		अगर (mac->rdg_en) अणु
			rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
				"Enable RDG function\n");
			set_tx_desc_rdg_enable(txdesc, 1);
			set_tx_desc_htc(txdesc, 1);
		पूर्ण
	पूर्ण
	अगर (rtlpriv->dm.useramask) अणु
		set_tx_desc_rate_id(txdesc, tcb_desc->ratr_index);
		set_tx_desc_macid(txdesc, tcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(txdesc, 0xC + tcb_desc->ratr_index);
		set_tx_desc_macid(txdesc, tcb_desc->ratr_index);
	पूर्ण
	अगर ((!ieee80211_is_data_qos(fc)) && ppsc->leisure_ps &&
	      ppsc->fwctrl_lps) अणु
		set_tx_desc_hwseq_en(txdesc, 1);
		set_tx_desc_pkt_id(txdesc, 8);
		अगर (!शेषadapter)
			set_tx_desc_qos(txdesc, 1);
	पूर्ण
	अगर (ieee80211_has_morefrags(fc))
		set_tx_desc_more_frag(txdesc, 1);
	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr)))
		set_tx_desc_bmc(txdesc, 1);
	_rtl_fill_usb_tx_desc(txdesc);
	_rtl_tx_desc_checksum(txdesc);
	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "==>\n");
पूर्ण

व्योम rtl92cu_fill_fake_txdesc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
			      u32 buffer_len, bool is_pspoll)
अणु
	__le32 *pdesc = (__le32 *)pdesc8;

	/* Clear all status */
	स_रखो(pdesc, 0, RTL_TX_HEADER_SIZE);
	set_tx_desc_first_seg(pdesc, 1); /* bFirstSeg; */
	set_tx_desc_last_seg(pdesc, 1); /* bLastSeg; */
	set_tx_desc_offset(pdesc, RTL_TX_HEADER_SIZE); /* Offset = 32 */
	set_tx_desc_pkt_size(pdesc, buffer_len); /* Buffer size + command hdr */
	set_tx_desc_queue_sel(pdesc, QSLT_MGNT); /* Fixed queue of Mgnt queue */
	/* Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error
	 * vlaue by Hw. */
	अगर (is_pspoll) अणु
		set_tx_desc_nav_use_hdr(pdesc, 1);
	पूर्ण अन्यथा अणु
		set_tx_desc_hwseq_en(pdesc, 1); /* Hw set sequence number */
		set_tx_desc_pkt_id(pdesc, BIT(3)); /* set bit3 to 1. */
	पूर्ण
	set_tx_desc_use_rate(pdesc, 1); /* use data rate which is set by Sw */
	set_tx_desc_own(pdesc, 1);
	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	_rtl_tx_desc_checksum(pdesc);
पूर्ण

व्योम rtl92cu_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 fw_queue = QSLT_BEACON;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	__le32 *pdesc = (__le32 *)pdesc8;

	स_रखो((व्योम *)pdesc, 0, RTL_TX_HEADER_SIZE);
	अगर (firstseg)
		set_tx_desc_offset(pdesc, RTL_TX_HEADER_SIZE);
	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	set_tx_desc_seq(pdesc, 0);
	set_tx_desc_linip(pdesc, 0);
	set_tx_desc_queue_sel(pdesc, fw_queue);
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_rate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);
	set_tx_desc_own(pdesc, 1);
	set_tx_desc_pkt_size(pdesc, (u16)skb->len);
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_offset(pdesc, 0x20);
	set_tx_desc_use_rate(pdesc, 1);
	अगर (!ieee80211_is_data_qos(fc)) अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	पूर्ण
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD, "H2C Tx Cmd Content",
		      pdesc, RTL_TX_DESC_SIZE);
पूर्ण
