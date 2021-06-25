<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 *  (c) Copyright 2008, RealTEK Technologies Inc. All Rights Reserved.
 *
 *  Module:	r819xusb_cmdpkt.c
 *		(RTL8190 TX/RX command packet handler Source C File)
 *
 *  Note:	The module is responsible क्रम handling TX and RX command packet.
 *		1. TX : Send set and query configuration command packet.
 *		2. RX : Receive tx feedback, beacon state, query configuration
 *			command packet.
 *
 *  Function:
 *
 *  Export:
 *
 *  Abbrev:
 *
 *  History:
 *
 *	Date		Who		Remark
 *	05/06/2008	amy		Create initial version porting from
 *					winकरोws driver.
 *
 ******************************************************************************/
#समावेश "r8192U.h"
#समावेश "r819xU_cmdpkt.h"

rt_status SendTxCommandPacket(काष्ठा net_device *dev, व्योम *pData, u32 DataLen)
अणु
	काष्ठा r8192_priv   *priv = ieee80211_priv(dev);
	काष्ठा sk_buff	    *skb;
	काष्ठा cb_desc	    *tcb_desc;

	/* Get TCB and local buffer from common pool.
	 * (It is shared by CmdQ, MgntQ, and USB coalesce DataQ)
	 */
	skb  = dev_alloc_skb(USB_HWDESC_HEADER_LEN + DataLen + 4);
	अगर (!skb)
		वापस RT_STATUS_FAILURE;
	स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
	tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	tcb_desc->queue_index = TXCMD_QUEUE;
	tcb_desc->bCmdOrInit = DESC_PACKET_TYPE_NORMAL;
	tcb_desc->bLastIniPkt = 0;
	skb_reserve(skb, USB_HWDESC_HEADER_LEN);
	skb_put_data(skb, pData, DataLen);
	tcb_desc->txbuf_size = (u16)DataLen;

	अगर (!priv->ieee80211->check_nic_enough_desc(dev, tcb_desc->queue_index) ||
	    (!skb_queue_empty(&priv->ieee80211->skb_रुकोQ[tcb_desc->queue_index])) ||
	    (priv->ieee80211->queue_stop)) अणु
		RT_TRACE(COMP_FIRMWARE, "=== NULL packet ======> tx full!\n");
		skb_queue_tail(&priv->ieee80211->skb_रुकोQ[tcb_desc->queue_index], skb);
	पूर्ण अन्यथा अणु
		priv->ieee80211->sofपंचांगac_hard_start_xmit(skb, dev);
	पूर्ण

	वापस RT_STATUS_SUCCESS;
पूर्ण

अटल व्योम cmpk_count_txstatistic(काष्ठा net_device *dev, काष्ठा cmd_pkt_tx_feedback *pstx_fb)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
#अगर_घोषित ENABLE_PS
	RT_RF_POWER_STATE	rtState;

	pAdapter->HalFunc.GetHwRegHandler(pAdapter, HW_VAR_RF_STATE,
					  (pu1Byte)(&rtState));

	/* When RF is off, we should not count the packet क्रम hw/sw synchronize
	 * reason, ie. there may be a duration जबतक sw चयन is changed and
	 * hw चयन is being changed.
	 */
	अगर (rtState == eRfOff)
		वापस;
#पूर्ण_अगर

#अगर_घोषित TODO
	अगर (pAdapter->bInHctTest)
		वापस;
#पूर्ण_अगर
	/* We can not know the packet length and transmit type:
	 * broadcast or uni or multicast. So the relative statistics
	 * must be collected in tx feedback info.
	 */
	अगर (pstx_fb->tok) अणु
		priv->stats.txfeedbackok++;
		priv->stats.txoktotal++;
		priv->stats.txokbytestotal += pstx_fb->pkt_length;
		priv->stats.txokinperiod++;

		/* We can not make sure broadcast/multicast or unicast mode. */
		अगर (pstx_fb->pkt_type == PACKET_MULTICAST) अणु
			priv->stats.txmulticast++;
			priv->stats.txbytesmulticast += pstx_fb->pkt_length;
		पूर्ण अन्यथा अगर (pstx_fb->pkt_type == PACKET_BROADCAST) अणु
			priv->stats.txbroadcast++;
			priv->stats.txbytesbroadcast += pstx_fb->pkt_length;
		पूर्ण अन्यथा अणु
			priv->stats.txunicast++;
			priv->stats.txbytesunicast += pstx_fb->pkt_length;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->stats.txfeedbackfail++;
		priv->stats.txerrtotal++;
		priv->stats.txerrbytestotal += pstx_fb->pkt_length;

		/* We can not make sure broadcast/multicast or unicast mode. */
		अगर (pstx_fb->pkt_type == PACKET_MULTICAST)
			priv->stats.txerrmulticast++;
		अन्यथा अगर (pstx_fb->pkt_type == PACKET_BROADCAST)
			priv->stats.txerrbroadcast++;
		अन्यथा
			priv->stats.txerrunicast++;
	पूर्ण

	priv->stats.txretrycount += pstx_fb->retry_cnt;
	priv->stats.txfeedbackretry += pstx_fb->retry_cnt;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:    cmpk_handle_tx_feedback()
 *
 * Overview:	The function is responsible क्रम extract the message inside TX
 *		feedbck message from firmware. It will contain dedicated info in
 *		ws-06-0063-rtl8190-command-packet-specअगरication.
 *		Please refer to chapter "TX Feedback Element".
 *              We have to पढ़ो 20 bytes in the command packet.
 *
 * Input:       काष्ठा net_device	*dev
 *              u8			*pmsg	- Msg Ptr of the command packet.
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 *  When		Who	Remark
 *  05/08/2008		amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_handle_tx_feedback(काष्ठा net_device *dev, u8 *pmsg)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा cmd_pkt_tx_feedback rx_tx_fb;

	priv->stats.txfeedback++;

	/* 1. Extract TX feedback info from RFD to temp काष्ठाure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * winकरोws OS. So we have to पढ़ो the content byte by byte or transfer
	 * endian type beक्रमe copy the message copy.
	 */
	/* Use poपूर्णांकer to transfer काष्ठाure memory. */
	स_नकल((u8 *)&rx_tx_fb, pmsg, माप(काष्ठा cmd_pkt_tx_feedback));
	/* 2. Use tx feedback info to count TX statistics. */
	cmpk_count_txstatistic(dev, &rx_tx_fb);
	/* Comment previous method क्रम TX statistic function. */
	/* Collect info TX feedback packet to fill TCB. */
	/* We can not know the packet length and transmit type: broadcast or uni
	 * or multicast.
	 */
पूर्ण

अटल व्योम cmdpkt_beaconसमयrपूर्णांकerrupt_819xusb(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u16 tx_rate;

	/* 87B have to S/W beacon क्रम DTM encryption_cmn. */
	अगर (priv->ieee80211->current_network.mode == IEEE_A ||
	    priv->ieee80211->current_network.mode == IEEE_N_5G ||
	    (priv->ieee80211->current_network.mode == IEEE_N_24G &&
	     (!priv->ieee80211->pHTInfo->bCurSuppCCK))) अणु
		tx_rate = 60;
		DMESG("send beacon frame  tx rate is 6Mbpm\n");
	पूर्ण अन्यथा अणु
		tx_rate = 10;
		DMESG("send beacon frame  tx rate is 1Mbpm\n");
	पूर्ण

	rtl819xusb_beacon_tx(dev, tx_rate); /* HW Beacon */
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:    cmpk_handle_पूर्णांकerrupt_status()
 *
 * Overview:    The function is responsible क्रम extract the message from
 *		firmware. It will contain dedicated info in
 *		ws-07-0063-v06-rtl819x-command-packet-specअगरication-070315.करोc.
 *		Please refer to chapter "Interrupt Status Element".
 *
 * Input:       काष्ठा net_device *dev
 *              u8 *pmsg		- Message Poपूर्णांकer of the command packet.
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 *  When		Who	Remark
 *  05/12/2008		amy	Add this क्रम rtl8192 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_handle_पूर्णांकerrupt_status(काष्ठा net_device *dev, u8 *pmsg)
अणु
	काष्ठा cmd_pkt_पूर्णांकerrupt_status	 rx_पूर्णांकr_status;	/* */
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	DMESG("---> cmpk_Handle_Interrupt_Status()\n");

	/* 1. Extract TX feedback info from RFD to temp काष्ठाure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * winकरोws OS. So we have to पढ़ो the content byte by byte or transfer
	 * endian type beक्रमe copy the message copy.
	 */
	rx_पूर्णांकr_status.length = pmsg[1];
	अगर (rx_पूर्णांकr_status.length != (माप(काष्ठा cmd_pkt_पूर्णांकerrupt_status) - 2)) अणु
		DMESG("cmpk_Handle_Interrupt_Status: wrong length!\n");
		वापस;
	पूर्ण

	/* Statistics of beacon क्रम ad-hoc mode. */
	अगर (priv->ieee80211->iw_mode == IW_MODE_ADHOC) अणु
		/* 2 maybe need endian transक्रमm? */
		rx_पूर्णांकr_status.पूर्णांकerrupt_status = *((u32 *)(pmsg + 4));

		DMESG("interrupt status = 0x%x\n",
		      rx_पूर्णांकr_status.पूर्णांकerrupt_status);

		अगर (rx_पूर्णांकr_status.पूर्णांकerrupt_status & ISR_TX_BCN_OK) अणु
			priv->ieee80211->bibsscoordinator = true;
			priv->stats.txbeaconokपूर्णांक++;
		पूर्ण अन्यथा अगर (rx_पूर्णांकr_status.पूर्णांकerrupt_status & ISR_TX_BCN_ERR) अणु
			priv->ieee80211->bibsscoordinator = false;
			priv->stats.txbeaconerr++;
		पूर्ण

		अगर (rx_पूर्णांकr_status.पूर्णांकerrupt_status & ISR_BCN_TIMER_INTR)
			cmdpkt_beaconसमयrपूर्णांकerrupt_819xusb(dev);
	पूर्ण

	/* Other inक्रमmation in पूर्णांकerrupt status we need? */

	DMESG("<---- cmpk_handle_interrupt_status()\n");
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:    cmpk_handle_query_config_rx()
 *
 * Overview:    The function is responsible क्रम extract the message from
 *		firmware. It will contain dedicated info in
 *		ws-06-0063-rtl8190-command-packet-specअगरication. Please
 *		refer to chapter "Beacon State Element".
 *
 * Input:       u8    *pmsg	-	Message Poपूर्णांकer of the command packet.
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 *  When		Who	Remark
 *  05/12/2008		amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_handle_query_config_rx(काष्ठा net_device *dev, u8 *pmsg)
अणु
	काष्ठा cmpk_query_cfg	rx_query_cfg;

	/* 1. Extract TX feedback info from RFD to temp काष्ठाure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * winकरोws OS. So we have to पढ़ो the content byte by byte or transfer
	 * endian type beक्रमe copy the message copy.
	 */
	rx_query_cfg.cfg_action		= (pmsg[4] & 0x80) >> 7;
	rx_query_cfg.cfg_type		= (pmsg[4] & 0x60) >> 5;
	rx_query_cfg.cfg_size		= (pmsg[4] & 0x18) >> 3;
	rx_query_cfg.cfg_page		= (pmsg[6] & 0x0F) >> 0;
	rx_query_cfg.cfg_offset		= pmsg[7];
	rx_query_cfg.value		= (pmsg[8]  << 24) | (pmsg[9]  << 16) |
					  (pmsg[10] <<  8) | (pmsg[11] <<  0);
	rx_query_cfg.mask		= (pmsg[12] << 24) | (pmsg[13] << 16) |
					  (pmsg[14] <<  8) | (pmsg[15] <<  0);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	cmpk_count_tx_status()
 *
 * Overview:	Count aggregated tx status from firmwar of one type rx command
 *		packet element id = RX_TX_STATUS.
 *
 * Input:	NONE
 *
 * Output:	NONE
 *
 * Return:	NONE
 *
 * Revised History:
 *	When		Who	Remark
 *	05/12/2008	amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_count_tx_status(काष्ठा net_device *dev,
				 cmpk_tx_status_t *pstx_status)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

#अगर_घोषित ENABLE_PS

	RT_RF_POWER_STATE	rtstate;

	pAdapter->HalFunc.GetHwRegHandler(pAdapter, HW_VAR_RF_STATE,
					  (pu1Byte)(&rtState));

	/* When RF is off, we should not count the packet क्रम hw/sw synchronize
	 * reason, ie. there may be a duration जबतक sw चयन is changed and
	 * hw चयन is being changed.
	 */
	अगर (rtState == eRfOff)
		वापस;
#पूर्ण_अगर

	priv->stats.txfeedbackok	+= pstx_status->txok;
	priv->stats.txoktotal		+= pstx_status->txok;

	priv->stats.txfeedbackfail	+= pstx_status->txfail;
	priv->stats.txerrtotal		+= pstx_status->txfail;

	priv->stats.txretrycount	+= pstx_status->txretry;
	priv->stats.txfeedbackretry	+= pstx_status->txretry;

	priv->stats.txmulticast		+= pstx_status->txmcok;
	priv->stats.txbroadcast		+= pstx_status->txbcok;
	priv->stats.txunicast		+= pstx_status->txucok;

	priv->stats.txerrmulticast	+= pstx_status->txmcfail;
	priv->stats.txerrbroadcast	+= pstx_status->txbcfail;
	priv->stats.txerrunicast	+= pstx_status->txucfail;

	priv->stats.txbytesmulticast	+= pstx_status->txmclength;
	priv->stats.txbytesbroadcast	+= pstx_status->txbclength;
	priv->stats.txbytesunicast	+= pstx_status->txuclength;

	priv->stats.last_packet_rate	= pstx_status->rate;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	cmpk_handle_tx_status()
 *
 * Overview:	Firmware add a new tx feedback status to reduce rx command
 *		packet buffer operation load.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who	Remark
 *	05/12/2008	amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_handle_tx_status(काष्ठा net_device *dev, u8 *pmsg)
अणु
	cmpk_tx_status_t	rx_tx_sts;

	स_नकल((व्योम *)&rx_tx_sts, (व्योम *)pmsg, माप(cmpk_tx_status_t));
	/* 2. Use tx feedback info to count TX statistics. */
	cmpk_count_tx_status(dev, &rx_tx_sts);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	cmpk_handle_tx_rate_history()
 *
 * Overview:	Firmware add a new tx rate history
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *	When		Who	Remark
 *	05/12/2008	amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम cmpk_handle_tx_rate_history(काष्ठा net_device *dev, u8 *pmsg)
अणु
	cmpk_tx_rahis_t	*ptxrate;
	u8		i, j;
	u16		length = माप(cmpk_tx_rahis_t);
	u32		*ptemp;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

#अगर_घोषित ENABLE_PS
	pAdapter->HalFunc.GetHwRegHandler(pAdapter, HW_VAR_RF_STATE,
					  (pu1Byte)(&rtState));

	/* When RF is off, we should not count the packet क्रम hw/sw synchronize
	 * reason, ie. there may be a duration जबतक sw चयन is changed and
	 * hw चयन is being changed.
	 */
	अगर (rtState == eRfOff)
		वापस;
#पूर्ण_अगर

	ptemp = (u32 *)pmsg;

	/* Do endian transfer to word alignment(16 bits) क्रम winकरोws प्रणाली.
	 * You must करो dअगरferent endian transfer क्रम linux and MAC OS
	 */
	क्रम (i = 0; i < (length/4); i++) अणु
		u16	 temp1, temp2;

		temp1 = ptemp[i] & 0x0000FFFF;
		temp2 = ptemp[i] >> 16;
		ptemp[i] = (temp1 << 16) | temp2;
	पूर्ण

	ptxrate = (cmpk_tx_rahis_t *)pmsg;

	अगर (!ptxrate)
		वापस;

	क्रम (i = 0; i < 16; i++) अणु
		/* Collect CCK rate packet num */
		अगर (i < 4)
			priv->stats.txrate.cck[i] += ptxrate->cck[i];

		/* Collect OFDM rate packet num */
		अगर (i < 8)
			priv->stats.txrate.ofdm[i] += ptxrate->ofdm[i];

		क्रम (j = 0; j < 4; j++)
			priv->stats.txrate.ht_mcs[j][i] += ptxrate->ht_mcs[j][i];
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:    cmpk_message_handle_rx()
 *
 * Overview:    In the function, we will capture dअगरferent RX command packet
 *		info. Every RX command packet element has dअगरferent message
 *		length and meaning in content. We only support three type of RX
 *		command packet now. Please refer to करोcument
 *		ws-06-0063-rtl8190-command-packet-specअगरication.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 *  When		Who	Remark
 *  05/06/2008		amy	Create Version 0 porting from winकरोws code.
 *
 *---------------------------------------------------------------------------
 */
u32 cmpk_message_handle_rx(काष्ठा net_device *dev,
			   काष्ठा ieee80211_rx_stats *pstats)
अणु
	पूर्णांक			total_length;
	u8			cmd_length, exe_cnt = 0;
	u8			element_id;
	u8			*pcmd_buff;

	/* 0. Check inpt arguments. It is a command queue message or
	 * poपूर्णांकer is null.
	 */
	अगर (!pstats)
		वापस 0;	/* This is not a command packet. */

	/* 1. Read received command packet message length from RFD. */
	total_length = pstats->Length;

	/* 2. Read भव address from RFD. */
	pcmd_buff = pstats->भव_address;

	/* 3. Read command packet element id and length. */
	element_id = pcmd_buff[0];

	/* 4. Check every received command packet content according to dअगरferent
	 *    element type. Because FW may aggregate RX command packet to
	 *    minimize transmit समय between DRV and FW.
	 */
	/* Add a counter to prevent the lock in the loop from being held too
	 * दीर्घ
	 */
	जबतक (total_length > 0 && exe_cnt++ < 100) अणु
		/* We support aggregation of dअगरferent cmd in the same packet */
		element_id = pcmd_buff[0];

		चयन (element_id) अणु
		हाल RX_TX_FEEDBACK:
			cmpk_handle_tx_feedback(dev, pcmd_buff);
			cmd_length = CMPK_RX_TX_FB_SIZE;
			अवरोध;

		हाल RX_INTERRUPT_STATUS:
			cmpk_handle_पूर्णांकerrupt_status(dev, pcmd_buff);
			cmd_length = माप(काष्ठा cmd_pkt_पूर्णांकerrupt_status);
			अवरोध;

		हाल BOTH_QUERY_CONFIG:
			cmpk_handle_query_config_rx(dev, pcmd_buff);
			cmd_length = CMPK_BOTH_QUERY_CONFIG_SIZE;
			अवरोध;

		हाल RX_TX_STATUS:
			cmpk_handle_tx_status(dev, pcmd_buff);
			cmd_length = CMPK_RX_TX_STS_SIZE;
			अवरोध;

		हाल RX_TX_PER_PKT_FEEDBACK:
			/* You must at lease add a चयन हाल element here,
			 * Otherwise, we will jump to शेष हाल.
			 */
			cmd_length = CMPK_RX_TX_FB_SIZE;
			अवरोध;

		हाल RX_TX_RATE_HISTORY:
			cmpk_handle_tx_rate_history(dev, pcmd_buff);
			cmd_length = CMPK_TX_RAHIS_SIZE;
			अवरोध;

		शेष:

			RT_TRACE(COMP_ERR, "---->%s():unknown CMD Element\n",
				 __func__);
			वापस 1;	/* This is a command packet. */
		पूर्ण

		total_length -= cmd_length;
		pcmd_buff    += cmd_length;
	पूर्ण
	वापस	1;	/* This is a command packet. */
पूर्ण
