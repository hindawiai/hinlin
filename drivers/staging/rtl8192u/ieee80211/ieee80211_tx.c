<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 *  Copyright(c) 2003 - 2004 Intel Corporation. All rights reserved.
 *
 *  Contact Inक्रमmation:
 *  James P. Ketrenos <ipw2100-admin@linux.पूर्णांकel.com>
 *  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *
 *  Few modअगरications क्रम Realtek's Wi-Fi drivers by
 *  Andrea Merello <andrea.merello@gmail.com>
 *
 *  A special thanks goes to Realtek क्रम their support !
 *
 ******************************************************************************/

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "ieee80211.h"


/*
 *
 *
 * 802.11 Data Frame
 *
 *
 * 802.11 frame_contorl क्रम data frames - 2 bytes
 *      ,-----------------------------------------------------------------------------------------.
 * bits | 0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  a  |  b  |  c  |  d  |  e   |
 *      |----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|------|
 * val  | 0  |  0  |  0  |  1  |  x  |  0  |  0  |  0  |  1  |  0  |  x  |  x  |  x  |  x  |  x   |
 *      |----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|------|
 * desc | ^-ver-^  |  ^type-^  |  ^-----subtype-----^  | to  |from |more |retry| pwr |more |wep   |
 *      |          |           | x=0 data,x=1 data+ack | DS  | DS  |frag |     | mgm |data |      |
 *      '-----------------------------------------------------------------------------------------'
 *                                                    /\
 *                                                    |
 * 802.11 Data Frame                                  |
 *           ,--------- 'ctrl' expands to >-----------'
 *           |
 *        ,--'---,-------------------------------------------------------------.
 *  Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
 *        |------|------|---------|---------|---------|------|---------|------|
 *  Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  Frame  |  fcs |
 *        |      | tion | (BSSID) |         |         | ence |  data   |      |
 *        `--------------------------------------------------|         |------'
 *  Total: 28 non-data bytes                                 `----.----'
 *                                                                |
 *         .- 'Frame data' expands to <---------------------------'
 *         |
 *         V
 *        ,---------------------------------------------------.
 *  Bytes |  1   |  1   |    1    |    3     |  2   |  0-2304 |
 *        |------|------|---------|----------|------|---------|
 *  Desc. | SNAP | SNAP | Control |Eth Tunnel| Type | IP      |
 *        | DSAP | SSAP |         |          |      | Packet  |
 *        | 0xAA | 0xAA |0x03 (UI)|0x00-00-F8|      |         |
 *        `-----------------------------------------|         |
 *  Total: 8 non-data bytes                         `----.----'
 *                                                       |
 *         .- 'IP Packet' expands, if WEP enabled, to <--'
 *         |
 *         V
 *        ,-----------------------.
 *  Bytes |  4  |   0-2296  |  4  |
 *        |-----|-----------|-----|
 *  Desc. | IV  | Encrypted | ICV |
 *        |     | IP Packet |     |
 *        `-----------------------'
 *  Total: 8 non-data bytes
 *
 *
 *  802.3 Ethernet Data Frame
 *
 *        ,-----------------------------------------.
 *  Bytes |   6   |   6   |  2   |  Variable |   4  |
 *        |-------|-------|------|-----------|------|
 *  Desc. | Dest. | Source| Type | IP Packet |  fcs |
 *        |  MAC  |  MAC  |      |           |      |
 *        `-----------------------------------------'
 *  Total: 18 non-data bytes
 *
 *  In the event that fragmentation is required, the incoming payload is split पूर्णांकo
 *  N parts of size ieee->fts.  The first fragment contains the SNAP header and the
 *  reमुख्यing packets are just data.
 *
 *  If encryption is enabled, each fragment payload size is reduced by enough space
 *  to add the prefix and postfix (IV and ICV totalling 8 bytes in the हाल of WEP)
 *  So अगर you have 1500 bytes of payload with ieee->fts set to 500 without
 *  encryption it will take 3 frames.  With WEP it will take 4 frames as the
 *  payload of each frame is reduced to 492 bytes.
 *
 * SKB visualization
 *
 *  ,- skb->data
 * |
 * |    ETHERNET HEADER        ,-<-- PAYLOAD
 * |                           |     14 bytes from skb->data
 * |  2 bytes क्रम Type --> ,T. |     (माप ethhdr)
 * |                       | | |
 * |,-Dest.--. ,--Src.---. | | |
 * |  6 bytes| | 6 bytes | | | |
 * v         | |         | | | |
 * 0         | v       1 | v | v           2
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
 *     ^     | ^         | ^ |
 *     |     | |         | | |
 *     |     | |         | `T' <---- 2 bytes क्रम Type
 *     |     | |         |
 *     |     | '---SNAP--' <-------- 6 bytes क्रम SNAP
 *     |     |
 *     `-IV--' <-------------------- 4 bytes क्रम IV (WEP)
 *
 *      SNAP HEADER
 *
 */

अटल u8 P802_1H_OUI[P80211_OUI_LEN] = अणु 0x00, 0x00, 0xf8 पूर्ण;
अटल u8 RFC1042_OUI[P80211_OUI_LEN] = अणु 0x00, 0x00, 0x00 पूर्ण;

अटल अंतरभूत पूर्णांक ieee80211_put_snap(u8 *data, u16 h_proto)
अणु
	काष्ठा ieee80211_snap_hdr *snap;
	u8 *oui;

	snap = (काष्ठा ieee80211_snap_hdr *)data;
	snap->dsap = 0xaa;
	snap->ssap = 0xaa;
	snap->ctrl = 0x03;

	अगर (h_proto == 0x8137 || h_proto == 0x80f3)
		oui = P802_1H_OUI;
	अन्यथा
		oui = RFC1042_OUI;
	snap->oui[0] = oui[0];
	snap->oui[1] = oui[1];
	snap->oui[2] = oui[2];

	*(__be16 *)(data + SNAP_SIZE) = htons(h_proto);

	वापस SNAP_SIZE + माप(u16);
पूर्ण

पूर्णांक ieee80211_encrypt_fragment(
	काष्ठा ieee80211_device *ieee,
	काष्ठा sk_buff *frag,
	पूर्णांक hdr_len)
अणु
	काष्ठा ieee80211_crypt_data *crypt = ieee->crypt[ieee->tx_keyidx];
	पूर्णांक res;

	अगर (!(crypt && crypt->ops)) अणु
		prपूर्णांकk("=========>%s(), crypt is null\n", __func__);
		वापस -1;
	पूर्ण

	अगर (ieee->tkip_countermeasures &&
	    crypt && crypt->ops && म_भेद(crypt->ops->name, "TKIP") == 0) अणु
		अगर (net_ratelimit()) अणु
			काष्ठा rtl_80211_hdr_3addrqos *header;

			header = (काष्ठा rtl_80211_hdr_3addrqos *)frag->data;
			netdev_dbg(ieee->dev, "TKIP countermeasures: dropped "
			       "TX packet to %pM\n", header->addr1);
		पूर्ण
		वापस -1;
	पूर्ण

	/* To encrypt, frame क्रमmat is:
	 * IV (4 bytes), clear payload (including SNAP), ICV (4 bytes)
	 */

	// PR: FIXME: Copied from hostap. Check fragmentation/MSDU/MPDU encryption.
	/* Host-based IEEE 802.11 fragmentation क्रम TX is not yet supported, so
	 * call both MSDU and MPDU encryption functions from here.
	 */
	atomic_inc(&crypt->refcnt);
	res = 0;
	अगर (crypt->ops->encrypt_msdu)
		res = crypt->ops->encrypt_msdu(frag, hdr_len, crypt->priv);
	अगर (res == 0 && crypt->ops->encrypt_mpdu)
		res = crypt->ops->encrypt_mpdu(frag, hdr_len, crypt->priv);

	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		netdev_info(ieee->dev, "Encryption failed: len=%d.\n",
			    frag->len);
		ieee->ieee_stats.tx_discards++;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


व्योम ieee80211_txb_मुक्त(काष्ठा ieee80211_txb *txb)
अणु
	//पूर्णांक i;
	अगर (unlikely(!txb))
		वापस;
	kमुक्त(txb);
पूर्ण
EXPORT_SYMBOL(ieee80211_txb_मुक्त);

अटल काष्ठा ieee80211_txb *ieee80211_alloc_txb(पूर्णांक nr_frags, पूर्णांक txb_size,
						 gfp_t gfp_mask)
अणु
	काष्ठा ieee80211_txb *txb;
	पूर्णांक i;
	txb = kदो_स्मृति(
		माप(काष्ठा ieee80211_txb) + (माप(u8 *) * nr_frags),
		gfp_mask);
	अगर (!txb)
		वापस शून्य;

	स_रखो(txb, 0, माप(काष्ठा ieee80211_txb));
	txb->nr_frags = nr_frags;
	txb->frag_size = __cpu_to_le16(txb_size);

	क्रम (i = 0; i < nr_frags; i++) अणु
		txb->fragments[i] = dev_alloc_skb(txb_size);
		अगर (unlikely(!txb->fragments[i])) अणु
			i--;
			अवरोध;
		पूर्ण
		स_रखो(txb->fragments[i]->cb, 0, माप(txb->fragments[i]->cb));
	पूर्ण
	अगर (unlikely(i != nr_frags)) अणु
		जबतक (i >= 0)
			dev_kमुक्त_skb_any(txb->fragments[i--]);
		kमुक्त(txb);
		वापस शून्य;
	पूर्ण
	वापस txb;
पूर्ण

// Classअगरy the to-be send data packet
// Need to acquire the sent queue index.
अटल पूर्णांक
ieee80211_classअगरy(काष्ठा sk_buff *skb, काष्ठा ieee80211_network *network)
अणु
	काष्ठा ethhdr *eth;
	काष्ठा iphdr *ip;
	eth = (काष्ठा ethhdr *)skb->data;
	अगर (eth->h_proto != htons(ETH_P_IP))
		वापस 0;

	ip = ip_hdr(skb);
	चयन (ip->tos & 0xfc) अणु
	हाल 0x20:
		वापस 2;
	हाल 0x40:
		वापस 1;
	हाल 0x60:
		वापस 3;
	हाल 0x80:
		वापस 4;
	हाल 0xa0:
		वापस 5;
	हाल 0xc0:
		वापस 6;
	हाल 0xe0:
		वापस 7;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ieee80211_tx_query_agg_cap(काष्ठा ieee80211_device *ieee,
				       काष्ठा sk_buff *skb, काष्ठा cb_desc *tcb_desc)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	काष्ठा tx_ts_record        *pTxTs = शून्य;
	काष्ठा rtl_80211_hdr_1addr *hdr = (काष्ठा rtl_80211_hdr_1addr *)skb->data;

	अगर (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		वापस;
	अगर (!IsQoSDataFrame(skb->data))
		वापस;

	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस;
	//check packet and mode later
	अगर (!ieee->GetNmodeSupportBySecCfg(ieee->dev))
		वापस;

	अगर (pHTInfo->bCurrentAMPDUEnable) अणु
		अगर (!GetTs(ieee, (काष्ठा ts_common_info **)(&pTxTs), hdr->addr1, skb->priority, TX_सूची, true)) अणु
			prपूर्णांकk("===>can't get TS\n");
			वापस;
		पूर्ण
		अगर (!pTxTs->tx_admitted_ba_record.valid) अणु
			TsStartAddBaProcess(ieee, pTxTs);
			जाओ FORCED_AGG_SETTING;
		पूर्ण अन्यथा अगर (!pTxTs->using_ba) अणु
			अगर (SN_LESS(pTxTs->tx_admitted_ba_record.start_seq_ctrl.field.seq_num, (pTxTs->tx_cur_seq + 1) % 4096))
				pTxTs->using_ba = true;
			अन्यथा
				जाओ FORCED_AGG_SETTING;
		पूर्ण

		अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
			tcb_desc->bAMPDUEnable = true;
			tcb_desc->ampdu_factor = pHTInfo->CurrentAMPDUFactor;
			tcb_desc->ampdu_density = pHTInfo->CurrentMPDUDensity;
		पूर्ण
	पूर्ण
FORCED_AGG_SETTING:
	चयन (pHTInfo->ForcedAMPDUMode) अणु
	हाल HT_AGG_AUTO:
		अवरोध;

	हाल HT_AGG_FORCE_ENABLE:
		tcb_desc->bAMPDUEnable = true;
		tcb_desc->ampdu_density = pHTInfo->ForcedMPDUDensity;
		tcb_desc->ampdu_factor = pHTInfo->ForcedAMPDUFactor;
		अवरोध;

	हाल HT_AGG_FORCE_DISABLE:
		tcb_desc->bAMPDUEnable = false;
		tcb_desc->ampdu_density = 0;
		tcb_desc->ampdu_factor = 0;
		अवरोध;

	पूर्ण
		वापस;
पूर्ण

अटल व्योम ieee80211_qurey_ShortPreambleMode(काष्ठा ieee80211_device *ieee,
					      काष्ठा cb_desc *tcb_desc)
अणु
	tcb_desc->bUseShortPreamble = false;
	अगर (tcb_desc->data_rate == 2) अणु//// 1M can only use Long Preamble. 11B spec
		वापस;
	पूर्ण अन्यथा अगर (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE) अणु
		tcb_desc->bUseShortPreamble = true;
	पूर्ण
	वापस;
पूर्ण
अटल व्योम
ieee80211_query_HTCapShortGI(काष्ठा ieee80211_device *ieee, काष्ठा cb_desc *tcb_desc)
अणु
	PRT_HIGH_THROUGHPUT		pHTInfo = ieee->pHTInfo;

	tcb_desc->bUseShortGI		= false;

	अगर (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		वापस;

	अगर (pHTInfo->bForcedShortGI) अणु
		tcb_desc->bUseShortGI = true;
		वापस;
	पूर्ण

	अगर (pHTInfo->bCurBW40MHz && pHTInfo->bCurShortGI40MHz)
		tcb_desc->bUseShortGI = true;
	अन्यथा अगर (!pHTInfo->bCurBW40MHz && pHTInfo->bCurShortGI20MHz)
		tcb_desc->bUseShortGI = true;
पूर्ण

अटल व्योम ieee80211_query_BandwidthMode(काष्ठा ieee80211_device *ieee,
					  काष्ठा cb_desc *tcb_desc)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;

	tcb_desc->bPacketBW = false;

	अगर (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		वापस;

	अगर (tcb_desc->bMulticast || tcb_desc->bBroadcast)
		वापस;

	अगर ((tcb_desc->data_rate & 0x80) == 0) // If using legacy rate, it shall use 20MHz channel.
		वापस;
	//BandWidthAutoSwitch is क्रम स्वतः चयन to 20 or 40 in दीर्घ distance
	अगर (pHTInfo->bCurBW40MHz && pHTInfo->bCurTxBW40MHz && !ieee->bandwidth_स्वतः_चयन.bक्रमced_tx20Mhz)
		tcb_desc->bPacketBW = true;
	वापस;
पूर्ण

अटल व्योम ieee80211_query_protectionmode(काष्ठा ieee80211_device *ieee,
					   काष्ठा cb_desc *tcb_desc,
					   काष्ठा sk_buff *skb)
अणु
	// Common Settings
	tcb_desc->bRTSSTBC			= false;
	tcb_desc->bRTSUseShortGI		= false; // Since protection frames are always sent by legacy rate, ShortGI will never be used.
	tcb_desc->bCTSEnable			= false; // Most of protection using RTS/CTS
	tcb_desc->RTSSC				= 0;		// 20MHz: Don't care;  40MHz: Duplicate.
	tcb_desc->bRTSBW			= false; // RTS frame bandwidth is always 20MHz

	अगर (tcb_desc->bBroadcast || tcb_desc->bMulticast) //only unicast frame will use rts/cts
		वापस;

	अगर (is_broadcast_ether_addr(skb->data + 16))  //check addr3 as infraकाष्ठाure add3 is DA.
		वापस;

	अगर (ieee->mode < IEEE_N_24G) /* b, g mode */ अणु
			// (1) RTS_Threshold is compared to the MPDU, not MSDU.
			// (2) If there are more than one frag in  this MSDU, only the first frag uses protection frame.
			//		Other fragments are रक्षित by previous fragment.
			//		So we only need to check the length of first fragment.
		अगर (skb->len > ieee->rts) अणु
			tcb_desc->bRTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		पूर्ण अन्यथा अगर (ieee->current_network.buseprotection) अणु
			// Use CTS-to-SELF in protection mode.
			tcb_desc->bRTSEnable = true;
			tcb_desc->bCTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		पूर्ण
		//otherwise वापस;
		वापस;
	पूर्ण अन्यथा अणु // 11n High throughput हाल.
		PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;
		जबतक (true) अणु
			//check ERP protection
			अगर (ieee->current_network.buseprotection) अणु// CTS-to-SELF
				tcb_desc->bRTSEnable = true;
				tcb_desc->bCTSEnable = true;
				tcb_desc->rts_rate = MGN_24M;
				अवरोध;
			पूर्ण
			//check HT op mode
			अगर (pHTInfo->bCurrentHTSupport && pHTInfo->bEnableHT) अणु
				u8 HTOpMode = pHTInfo->CurrentOpMode;
				अगर ((pHTInfo->bCurBW40MHz && (HTOpMode == 2 || HTOpMode == 3)) ||
							(!pHTInfo->bCurBW40MHz && HTOpMode == 3)) अणु
					tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
					tcb_desc->bRTSEnable = true;
					अवरोध;
				पूर्ण
			पूर्ण
			//check rts
			अगर (skb->len > ieee->rts) अणु
				tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
				tcb_desc->bRTSEnable = true;
				अवरोध;
			पूर्ण
			//to करो list: check MIMO घातer save condition.
			//check AMPDU aggregation क्रम TXOP
			अगर (tcb_desc->bAMPDUEnable) अणु
				tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
				// According to 8190 design, firmware sends CF-End only अगर RTS/CTS is enabled. However, it degrads
				// throughput around 10M, so we disable of this mechanism. 2007.08.03 by Emily
				tcb_desc->bRTSEnable = false;
				अवरोध;
			पूर्ण
			//check IOT action
			अगर (pHTInfo->IOTAction & HT_IOT_ACT_FORCED_CTS2SELF) अणु
				tcb_desc->bCTSEnable	= true;
				tcb_desc->rts_rate  =	MGN_24M;
				tcb_desc->bRTSEnable = true;
				अवरोध;
			पूर्ण
			// Totally no protection हाल!!
			जाओ NO_PROTECTION;
		पूर्ण
		पूर्ण
	// For test , CTS replace with RTS
	अगर (0) अणु
		tcb_desc->bCTSEnable	= true;
		tcb_desc->rts_rate = MGN_24M;
		tcb_desc->bRTSEnable	= true;
	पूर्ण
	अगर (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		tcb_desc->bUseShortPreamble = true;
	अगर (ieee->mode == IW_MODE_MASTER)
		जाओ NO_PROTECTION;
	वापस;
NO_PROTECTION:
	tcb_desc->bRTSEnable	= false;
	tcb_desc->bCTSEnable	= false;
	tcb_desc->rts_rate		= 0;
	tcb_desc->RTSSC		= 0;
	tcb_desc->bRTSBW		= false;
पूर्ण


अटल व्योम ieee80211_txrate_selecपंचांगode(काष्ठा ieee80211_device *ieee,
					काष्ठा cb_desc *tcb_desc)
अणु
	अगर (ieee->bTxDisableRateFallBack)
		tcb_desc->bTxDisableRateFallBack = true;

	अगर (ieee->bTxUseDriverAssingedRate)
		tcb_desc->bTxUseDriverAssingedRate = true;
	अगर (!tcb_desc->bTxDisableRateFallBack || !tcb_desc->bTxUseDriverAssingedRate) अणु
		अगर (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC)
			tcb_desc->RATRIndex = 0;
	पूर्ण
पूर्ण

अटल व्योम ieee80211_query_seqnum(काष्ठा ieee80211_device *ieee,
				   काष्ठा sk_buff *skb, u8 *dst)
अणु
	अगर (is_multicast_ether_addr(dst))
		वापस;
	अगर (IsQoSDataFrame(skb->data)) /* we deal qos data only */ अणु
		काष्ठा tx_ts_record *pTS = शून्य;
		अगर (!GetTs(ieee, (काष्ठा ts_common_info **)(&pTS), dst, skb->priority, TX_सूची, true)) अणु
			वापस;
		पूर्ण
		pTS->tx_cur_seq = (pTS->tx_cur_seq + 1) % 4096;
	पूर्ण
पूर्ण

पूर्णांक ieee80211_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_device *ieee = netdev_priv(dev);
	काष्ठा ieee80211_txb *txb = शून्य;
	काष्ठा rtl_80211_hdr_3addrqos *frag_hdr;
	पूर्णांक i, bytes_per_frag, nr_frags, bytes_last_frag, frag_size;
	अचिन्हित दीर्घ flags;
	काष्ठा net_device_stats *stats = &ieee->stats;
	पूर्णांक ether_type = 0, encrypt;
	पूर्णांक bytes, fc, qos_ctl = 0, hdr_len;
	काष्ठा sk_buff *skb_frag;
	काष्ठा rtl_80211_hdr_3addrqos header = अणु /* Ensure zero initialized */
		.duration_id = 0,
		.seq_ctl = 0,
		.qos_ctl = 0
	पूर्ण;
	u8 dest[ETH_ALEN], src[ETH_ALEN];
	पूर्णांक qos_actived = ieee->current_network.qos_data.active;

	काष्ठा ieee80211_crypt_data *crypt;

	काष्ठा cb_desc *tcb_desc;

	spin_lock_irqsave(&ieee->lock, flags);

	/* If there is no driver handler to take the TXB, करोnt' bother
	 * creating it...
	 */
	अगर ((!ieee->hard_start_xmit && !(ieee->sofपंचांगac_features & IEEE_SOFTMAC_TX_QUEUE)) ||
	   ((!ieee->sofपंचांगac_data_hard_start_xmit && (ieee->sofपंचांगac_features & IEEE_SOFTMAC_TX_QUEUE)))) अणु
		netdev_warn(ieee->dev, "No xmit handler.\n");
		जाओ success;
	पूर्ण


	अगर (likely(ieee->raw_tx == 0)) अणु
		अगर (unlikely(skb->len < SNAP_SIZE + माप(u16))) अणु
			netdev_warn(ieee->dev, "skb too small (%d).\n",
				    skb->len);
			जाओ success;
		पूर्ण

		स_रखो(skb->cb, 0, माप(skb->cb));
		ether_type = ntohs(((काष्ठा ethhdr *)skb->data)->h_proto);

		crypt = ieee->crypt[ieee->tx_keyidx];

		encrypt = !(ether_type == ETH_P_PAE && ieee->ieee802_1x) &&
			ieee->host_encrypt && crypt && crypt->ops;

		अगर (!encrypt && ieee->ieee802_1x &&
		ieee->drop_unencrypted && ether_type != ETH_P_PAE) अणु
			stats->tx_dropped++;
			जाओ success;
		पूर्ण
	#अगर_घोषित CONFIG_IEEE80211_DEBUG
		अगर (crypt && !encrypt && ether_type == ETH_P_PAE) अणु
			काष्ठा eapol *eap = (काष्ठा eapol *)(skb->data +
				माप(काष्ठा ethhdr) - SNAP_SIZE - माप(u16));
			IEEE80211_DEBUG_EAP("TX: IEEE 802.11 EAPOL frame: %s\n",
				eap_get_type(eap->type));
		पूर्ण
	#पूर्ण_अगर

		/* Save source and destination addresses */
		स_नकल(&dest, skb->data, ETH_ALEN);
		स_नकल(&src, skb->data + ETH_ALEN, ETH_ALEN);

		/* Advance the SKB to the start of the payload */
		skb_pull(skb, माप(काष्ठा ethhdr));

		/* Determine total amount of storage required क्रम TXB packets */
		bytes = skb->len + SNAP_SIZE + माप(u16);

		अगर (encrypt)
			fc = IEEE80211_FTYPE_DATA | IEEE80211_FCTL_WEP;
		अन्यथा

			fc = IEEE80211_FTYPE_DATA;

		//अगर(ieee->current_network.QoS_Enable)
		अगर (qos_actived)
			fc |= IEEE80211_STYPE_QOS_DATA;
		अन्यथा
			fc |= IEEE80211_STYPE_DATA;

		अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
			fc |= IEEE80211_FCTL_TODS;
			/* To DS: Addr1 = BSSID, Addr2 = SA,
			 * Addr3 = DA
			 */
			स_नकल(&header.addr1, ieee->current_network.bssid, ETH_ALEN);
			स_नकल(&header.addr2, &src, ETH_ALEN);
			स_नकल(&header.addr3, &dest, ETH_ALEN);
		पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
			/* not From/To DS: Addr1 = DA, Addr2 = SA,
			 * Addr3 = BSSID
			 */
			स_नकल(&header.addr1, dest, ETH_ALEN);
			स_नकल(&header.addr2, src, ETH_ALEN);
			स_नकल(&header.addr3, ieee->current_network.bssid, ETH_ALEN);
		पूर्ण

		header.frame_ctl = cpu_to_le16(fc);

		/* Determine fragmentation size based on destination (multicast
		 * and broadcast are not fragmented)
		 */
		अगर (is_multicast_ether_addr(header.addr1)) अणु
			frag_size = MAX_FRAG_THRESHOLD;
			qos_ctl |= QOS_CTL_NOTCONTAIN_ACK;
		पूर्ण अन्यथा अणु
			frag_size = ieee->fts;//शेष:392
			qos_ctl = 0;
		पूर्ण

		//अगर (ieee->current_network.QoS_Enable)
		अगर (qos_actived) अणु
			hdr_len = IEEE80211_3ADDR_LEN + 2;

			skb->priority = ieee80211_classअगरy(skb, &ieee->current_network);
			qos_ctl |= skb->priority; //set in the ieee80211_classअगरy
			header.qos_ctl = cpu_to_le16(qos_ctl & IEEE80211_QOS_TID);
		पूर्ण अन्यथा अणु
			hdr_len = IEEE80211_3ADDR_LEN;
		पूर्ण
		/* Determine amount of payload per fragment.  Regardless of अगर
		 * this stack is providing the full 802.11 header, one will
		 * eventually be affixed to this fragment -- so we must account क्रम
		 * it when determining the amount of payload space.
		 */
		bytes_per_frag = frag_size - hdr_len;
		अगर (ieee->config &
		(CFG_IEEE80211_COMPUTE_FCS | CFG_IEEE80211_RESERVE_FCS))
			bytes_per_frag -= IEEE80211_FCS_LEN;

		/* Each fragment may need to have room क्रम encryption pre/postfix */
		अगर (encrypt)
			bytes_per_frag -= crypt->ops->extra_prefix_len +
				crypt->ops->extra_postfix_len;

		/* Number of fragments is the total bytes_per_frag /
		 * payload_per_fragment
		 */
		nr_frags = bytes / bytes_per_frag;
		bytes_last_frag = bytes % bytes_per_frag;
		अगर (bytes_last_frag)
			nr_frags++;
		अन्यथा
			bytes_last_frag = bytes_per_frag;

		/* When we allocate the TXB we allocate enough space क्रम the reserve
		 * and full fragment bytes (bytes_per_frag करोesn't include prefix,
		 * postfix, header, FCS, etc.)
		 */
		txb = ieee80211_alloc_txb(nr_frags, frag_size + ieee->tx_headroom, GFP_ATOMIC);
		अगर (unlikely(!txb)) अणु
			netdev_warn(ieee->dev, "Could not allocate TXB\n");
			जाओ failed;
		पूर्ण
		txb->encrypted = encrypt;
		txb->payload_size = __cpu_to_le16(bytes);

		//अगर (ieee->current_network.QoS_Enable)
		अगर (qos_actived)
			txb->queue_index = UP2AC(skb->priority);
		अन्यथा
			txb->queue_index = WME_AC_BK;



		क्रम (i = 0; i < nr_frags; i++) अणु
			skb_frag = txb->fragments[i];
			tcb_desc = (काष्ठा cb_desc *)(skb_frag->cb + MAX_DEV_ADDR_SIZE);
			अगर (qos_actived) अणु
				skb_frag->priority = skb->priority;//UP2AC(skb->priority);
				tcb_desc->queue_index =  UP2AC(skb->priority);
			पूर्ण अन्यथा अणु
				skb_frag->priority = WME_AC_BK;
				tcb_desc->queue_index = WME_AC_BK;
			पूर्ण
			skb_reserve(skb_frag, ieee->tx_headroom);

			अगर (encrypt) अणु
				अगर (ieee->hwsec_active)
					tcb_desc->bHwSec = 1;
				अन्यथा
					tcb_desc->bHwSec = 0;
				skb_reserve(skb_frag, crypt->ops->extra_prefix_len);
			पूर्ण अन्यथा अणु
				tcb_desc->bHwSec = 0;
			पूर्ण
			frag_hdr = skb_put_data(skb_frag, &header, hdr_len);

			/* If this is not the last fragment, then add the MOREFRAGS
			 * bit to the frame control
			 */
			अगर (i != nr_frags - 1) अणु
				frag_hdr->frame_ctl = cpu_to_le16(
					fc | IEEE80211_FCTL_MOREFRAGS);
				bytes = bytes_per_frag;

			पूर्ण अन्यथा अणु
				/* The last fragment takes the reमुख्यing length */
				bytes = bytes_last_frag;
			पूर्ण
			//अगर(ieee->current_network.QoS_Enable)
			अगर (qos_actived) अणु
				// add 1 only indicate to corresponding seq number control 2006/7/12
				frag_hdr->seq_ctl = cpu_to_le16(ieee->seq_ctrl[UP2AC(skb->priority) + 1] << 4 | i);
			पूर्ण अन्यथा अणु
				frag_hdr->seq_ctl = cpu_to_le16(ieee->seq_ctrl[0] << 4 | i);
			पूर्ण

			/* Put a SNAP header on the first fragment */
			अगर (i == 0) अणु
				ieee80211_put_snap(
					skb_put(skb_frag, SNAP_SIZE + माप(u16)),
					ether_type);
				bytes -= SNAP_SIZE + माप(u16);
			पूर्ण

			skb_put_data(skb_frag, skb->data, bytes);

			/* Advance the SKB... */
			skb_pull(skb, bytes);

			/* Encryption routine will move the header क्रमward in order
			 * to insert the IV between the header and the payload
			 */
			अगर (encrypt)
				ieee80211_encrypt_fragment(ieee, skb_frag, hdr_len);
			अगर (ieee->config &
			(CFG_IEEE80211_COMPUTE_FCS | CFG_IEEE80211_RESERVE_FCS))
				skb_put(skb_frag, 4);
		पूर्ण

		अगर (qos_actived) अणु
			अगर (ieee->seq_ctrl[UP2AC(skb->priority) + 1] == 0xFFF)
				ieee->seq_ctrl[UP2AC(skb->priority) + 1] = 0;
			अन्यथा
				ieee->seq_ctrl[UP2AC(skb->priority) + 1]++;
		पूर्ण अन्यथा अणु
			अगर (ieee->seq_ctrl[0] == 0xFFF)
				ieee->seq_ctrl[0] = 0;
			अन्यथा
				ieee->seq_ctrl[0]++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(skb->len < माप(काष्ठा rtl_80211_hdr_3addr))) अणु
			netdev_warn(ieee->dev, "skb too small (%d).\n",
				    skb->len);
			जाओ success;
		पूर्ण

		txb = ieee80211_alloc_txb(1, skb->len, GFP_ATOMIC);
		अगर (!txb) अणु
			netdev_warn(ieee->dev, "Could not allocate TXB\n");
			जाओ failed;
		पूर्ण

		txb->encrypted = 0;
		txb->payload_size = __cpu_to_le16(skb->len);
		skb_put_data(txb->fragments[0], skb->data, skb->len);
	पूर्ण

 success:
//WB add to fill data tcb_desc here. only first fragment is considered, need to change, and you may हटाओ to other place.
	अगर (txb) अणु
		काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(txb->fragments[0]->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->bTxEnableFwCalcDur = 1;
		अगर (is_multicast_ether_addr(header.addr1))
			tcb_desc->bMulticast = 1;
		अगर (is_broadcast_ether_addr(header.addr1))
			tcb_desc->bBroadcast = 1;
		ieee80211_txrate_selecपंचांगode(ieee, tcb_desc);
		अगर (tcb_desc->bMulticast ||  tcb_desc->bBroadcast)
			tcb_desc->data_rate = ieee->basic_rate;
		अन्यथा
			tcb_desc->data_rate = CURRENT_RATE(ieee->mode, ieee->rate, ieee->HTCurrentOperaRate);
		ieee80211_qurey_ShortPreambleMode(ieee, tcb_desc);
		ieee80211_tx_query_agg_cap(ieee, txb->fragments[0], tcb_desc);
		ieee80211_query_HTCapShortGI(ieee, tcb_desc);
		ieee80211_query_BandwidthMode(ieee, tcb_desc);
		ieee80211_query_protectionmode(ieee, tcb_desc, txb->fragments[0]);
		ieee80211_query_seqnum(ieee, txb->fragments[0], header.addr1);
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
	dev_kमुक्त_skb_any(skb);
	अगर (txb) अणु
		अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_TX_QUEUE) अणु
			ieee80211_sofपंचांगac_xmit(txb, ieee);
		पूर्ण अन्यथा अणु
			अगर ((*ieee->hard_start_xmit)(txb, dev) == 0) अणु
				stats->tx_packets++;
				stats->tx_bytes += __le16_to_cpu(txb->payload_size);
				वापस 0;
			पूर्ण
			ieee80211_txb_मुक्त(txb);
		पूर्ण
	पूर्ण

	वापस 0;

 failed:
	spin_unlock_irqrestore(&ieee->lock, flags);
	netअगर_stop_queue(dev);
	stats->tx_errors++;
	वापस 1;

पूर्ण
