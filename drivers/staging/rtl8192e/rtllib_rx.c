<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Original code based Host AP (software wireless LAN access poपूर्णांक) driver
 * क्रम Intersil Prism2/2.5/3 - hostap.o module, common routines
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <jkmaline@cc.hut.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2004, Intel Corporation
 *
 * Few modअगरications क्रम Realtek's Wi-Fi drivers by
 * Andrea Merello <andrea.merello@gmail.com>
 *
 * A special thanks goes to Realtek क्रम their support !
 */
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
#समावेश <linux/प्रकार.स>

#समावेश "rtllib.h"
#समावेश "dot11d.h"

अटल व्योम rtllib_rx_mgt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			  काष्ठा rtllib_rx_stats *stats);

अटल अंतरभूत व्योम rtllib_monitor_rx(काष्ठा rtllib_device *ieee,
				     काष्ठा sk_buff *skb,
				     काष्ठा rtllib_rx_stats *rx_status,
				     माप_प्रकार hdr_length)
अणु
	skb->dev = ieee->dev;
	skb_reset_mac_header(skb);
	skb_pull(skb, hdr_length);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_80211_RAW);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल काष्ठा rtllib_frag_entry *
rtllib_frag_cache_find(काष्ठा rtllib_device *ieee, अचिन्हित पूर्णांक seq,
			  अचिन्हित पूर्णांक frag, u8 tid, u8 *src, u8 *dst)
अणु
	काष्ठा rtllib_frag_entry *entry;
	पूर्णांक i;

	क्रम (i = 0; i < RTLLIB_FRAG_CACHE_LEN; i++) अणु
		entry = &ieee->frag_cache[tid][i];
		अगर (entry->skb != शून्य &&
		    समय_after(jअगरfies, entry->first_frag_समय + 2 * HZ)) अणु
			netdev_dbg(ieee->dev,
				   "expiring fragment cache entry seq=%u last_frag=%u\n",
				   entry->seq, entry->last_frag);
			dev_kमुक्त_skb_any(entry->skb);
			entry->skb = शून्य;
		पूर्ण

		अगर (entry->skb != शून्य && entry->seq == seq &&
		    (entry->last_frag + 1 == frag || frag == -1) &&
		    स_भेद(entry->src_addr, src, ETH_ALEN) == 0 &&
		    स_भेद(entry->dst_addr, dst, ETH_ALEN) == 0)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल काष्ठा sk_buff *
rtllib_frag_cache_get(काष्ठा rtllib_device *ieee,
			 काष्ठा rtllib_hdr_4addr *hdr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	u16 sc = le16_to_cpu(hdr->seq_ctl);
	अचिन्हित पूर्णांक frag = WLAN_GET_SEQ_FRAG(sc);
	अचिन्हित पूर्णांक seq = WLAN_GET_SEQ_SEQ(sc);
	काष्ठा rtllib_frag_entry *entry;
	काष्ठा rtllib_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtllib_hdr_4addrqos *hdr_4addrqos;
	u8 tid;

	अगर (((fc & RTLLIB_FCTL_DSTODS) == RTLLIB_FCTL_DSTODS) &&
	    RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtllib_hdr_4addrqos *)hdr;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_3addrqos = (काष्ठा rtllib_hdr_3addrqos *)hdr;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु
		tid = 0;
	पूर्ण

	अगर (frag == 0) अणु
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(ieee->dev->mtu +
				    माप(काष्ठा rtllib_hdr_4addr) +
				    8 /* LLC */ +
				    2 /* alignment */ +
				    8 /* WEP */ +
				    ETH_ALEN /* WDS */ +
				    /* QOS Control */
				    (RTLLIB_QOS_HAS_SEQ(fc) ? 2 : 0));
		अगर (!skb)
			वापस शून्य;

		entry = &ieee->frag_cache[tid][ieee->frag_next_idx[tid]];
		ieee->frag_next_idx[tid]++;
		अगर (ieee->frag_next_idx[tid] >= RTLLIB_FRAG_CACHE_LEN)
			ieee->frag_next_idx[tid] = 0;

		अगर (entry->skb != शून्य)
			dev_kमुक्त_skb_any(entry->skb);

		entry->first_frag_समय = jअगरfies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		ether_addr_copy(entry->src_addr, hdr->addr2);
		ether_addr_copy(entry->dst_addr, hdr->addr1);
	पूर्ण अन्यथा अणु
		/* received a fragment of a frame क्रम which the head fragment
		 * should have alपढ़ोy been received
		 */
		entry = rtllib_frag_cache_find(ieee, seq, frag, tid, hdr->addr2,
						  hdr->addr1);
		अगर (entry != शून्य) अणु
			entry->last_frag = frag;
			skb = entry->skb;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक rtllib_frag_cache_invalidate(काष्ठा rtllib_device *ieee,
					   काष्ठा rtllib_hdr_4addr *hdr)
अणु
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	u16 sc = le16_to_cpu(hdr->seq_ctl);
	अचिन्हित पूर्णांक seq = WLAN_GET_SEQ_SEQ(sc);
	काष्ठा rtllib_frag_entry *entry;
	काष्ठा rtllib_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtllib_hdr_4addrqos *hdr_4addrqos;
	u8 tid;

	अगर (((fc & RTLLIB_FCTL_DSTODS) == RTLLIB_FCTL_DSTODS) &&
	    RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtllib_hdr_4addrqos *)hdr;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_3addrqos = (काष्ठा rtllib_hdr_3addrqos *)hdr;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु
		tid = 0;
	पूर्ण

	entry = rtllib_frag_cache_find(ieee, seq, -1, tid, hdr->addr2,
					  hdr->addr1);

	अगर (entry == शून्य) अणु
		netdev_dbg(ieee->dev,
			   "Couldn't invalidate fragment cache entry (seq=%u)\n",
			   seq);
		वापस -1;
	पूर्ण

	entry->skb = शून्य;
	वापस 0;
पूर्ण

/* rtllib_rx_frame_mgपंचांगt
 *
 * Responsible क्रम handling management control frames
 *
 * Called by rtllib_rx
 */
अटल अंतरभूत पूर्णांक
rtllib_rx_frame_mgmt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			काष्ठा rtllib_rx_stats *rx_stats, u16 type,
			u16 stype)
अणु
	/* On the काष्ठा stats definition there is written that
	 * this is not mandatory.... but seems that the probe
	 * response parser uses it
	 */
	काष्ठा rtllib_hdr_3addr *hdr = (काष्ठा rtllib_hdr_3addr *)skb->data;

	rx_stats->len = skb->len;
	rtllib_rx_mgt(ieee, skb, rx_stats);
	अगर ((स_भेद(hdr->addr1, ieee->dev->dev_addr, ETH_ALEN))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण
	rtllib_rx_frame_sofपंचांगac(ieee, skb, rx_stats, type, stype);

	dev_kमुक्त_skb_any(skb);

	वापस 0;
पूर्ण

/* See IEEE 802.1H क्रम LLC/SNAP encapsulation/decapsulation
 * Ethernet-II snap header (RFC1042 क्रम most EtherTypes)
 */
अटल अचिन्हित अक्षर rfc1042_header[] = अणु
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00
पूर्ण;
/* Bridge-Tunnel header (क्रम EtherTypes ETH_P_AARP and ETH_P_IPX) */
अटल अचिन्हित अक्षर bridge_tunnel_header[] = अणु
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8
पूर्ण;
/* No encapsulation header अगर EtherType < 0x600 (=length) */

/* Called by rtllib_rx_frame_decrypt */
अटल पूर्णांक rtllib_is_eapol_frame(काष्ठा rtllib_device *ieee,
				    काष्ठा sk_buff *skb, माप_प्रकार hdrlen)
अणु
	काष्ठा net_device *dev = ieee->dev;
	u16 fc, ethertype;
	काष्ठा rtllib_hdr_4addr *hdr;
	u8 *pos;

	अगर (skb->len < 24)
		वापस 0;

	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	/* check that the frame is unicast frame to us */
	अगर ((fc & (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS)) ==
	    RTLLIB_FCTL_TODS &&
	    स_भेद(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0 &&
	    स_भेद(hdr->addr3, dev->dev_addr, ETH_ALEN) == 0) अणु
		/* ToDS frame with own addr BSSID and DA */
	पूर्ण अन्यथा अगर ((fc & (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS)) ==
		   RTLLIB_FCTL_FROMDS &&
		   स_भेद(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0) अणु
		/* FromDS frame with own addr as DA */
	पूर्ण अन्यथा
		वापस 0;

	अगर (skb->len < 24 + 8)
		वापस 0;

	/* check क्रम port access entity Ethernet type */
	pos = skb->data + hdrlen;
	ethertype = (pos[6] << 8) | pos[7];
	अगर (ethertype == ETH_P_PAE)
		वापस 1;

	वापस 0;
पूर्ण

/* Called only as a tasklet (software IRQ), by rtllib_rx */
अटल अंतरभूत पूर्णांक
rtllib_rx_frame_decrypt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा rtllib_hdr_4addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_mpdu == शून्य)
		वापस 0;

	अगर (ieee->hwsec_active) अणु
		काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)
						(skb->cb + MAX_DEV_ADDR_SIZE);

		tcb_desc->bHwSec = 1;

		अगर (ieee->need_sw_enc)
			tcb_desc->bHwSec = 0;
	पूर्ण

	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	hdrlen = rtllib_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		netdev_dbg(ieee->dev, "decryption failed (SA= %pM) res=%d\n",
			   hdr->addr2, res);
		अगर (res == -2)
			netdev_dbg(ieee->dev,
				   "Decryption failed ICV mismatch (key %d)\n",
				   skb->data[hdrlen + 3] >> 6);
		वापस -1;
	पूर्ण

	वापस res;
पूर्ण


/* Called only as a tasklet (software IRQ), by rtllib_rx */
अटल अंतरभूत पूर्णांक
rtllib_rx_frame_decrypt_msdu(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			     पूर्णांक keyidx, काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा rtllib_hdr_4addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_msdu == शून्य)
		वापस 0;
	अगर (ieee->hwsec_active) अणु
		काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)
						(skb->cb + MAX_DEV_ADDR_SIZE);

		tcb_desc->bHwSec = 1;

		अगर (ieee->need_sw_enc)
			tcb_desc->bHwSec = 0;
	पूर्ण

	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	hdrlen = rtllib_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_msdu(skb, keyidx, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		netdev_dbg(ieee->dev,
			   "MSDU decryption/MIC verification failed (SA= %pM keyidx=%d)\n",
			   hdr->addr2, keyidx);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/* this function is stolen from ipw2200 driver*/
#घोषणा IEEE_PACKET_RETRY_TIME (5*HZ)
अटल पूर्णांक is_duplicate_packet(काष्ठा rtllib_device *ieee,
				      काष्ठा rtllib_hdr_4addr *header)
अणु
	u16 fc = le16_to_cpu(header->frame_ctl);
	u16 sc = le16_to_cpu(header->seq_ctl);
	u16 seq = WLAN_GET_SEQ_SEQ(sc);
	u16 frag = WLAN_GET_SEQ_FRAG(sc);
	u16 *last_seq, *last_frag;
	अचिन्हित दीर्घ *last_समय;
	काष्ठा rtllib_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtllib_hdr_4addrqos *hdr_4addrqos;
	u8 tid;

	अगर (((fc & RTLLIB_FCTL_DSTODS) == RTLLIB_FCTL_DSTODS) &&
	    RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtllib_hdr_4addrqos *)header;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (RTLLIB_QOS_HAS_SEQ(fc)) अणु
		hdr_3addrqos = (काष्ठा rtllib_hdr_3addrqos *)header;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & RTLLIB_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु
		tid = 0;
	पूर्ण

	चयन (ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
	अणु
		काष्ठा list_head *p;
		काष्ठा ieee_ibss_seq *entry = शून्य;
		u8 *mac = header->addr2;
		पूर्णांक index = mac[5] % IEEE_IBSS_MAC_HASH_SIZE;

		list_क्रम_each(p, &ieee->ibss_mac_hash[index]) अणु
			entry = list_entry(p, काष्ठा ieee_ibss_seq, list);
			अगर (!स_भेद(entry->mac, mac, ETH_ALEN))
				अवरोध;
		पूर्ण
		अगर (p == &ieee->ibss_mac_hash[index]) अणु
			entry = kदो_स्मृति(माप(काष्ठा ieee_ibss_seq),
					GFP_ATOMIC);
			अगर (!entry)
				वापस 0;

			ether_addr_copy(entry->mac, mac);
			entry->seq_num[tid] = seq;
			entry->frag_num[tid] = frag;
			entry->packet_समय[tid] = jअगरfies;
			list_add(&entry->list, &ieee->ibss_mac_hash[index]);
			वापस 0;
		पूर्ण
		last_seq = &entry->seq_num[tid];
		last_frag = &entry->frag_num[tid];
		last_समय = &entry->packet_समय[tid];
		अवरोध;
	पूर्ण

	हाल IW_MODE_INFRA:
		last_seq = &ieee->last_rxseq_num[tid];
		last_frag = &ieee->last_rxfrag_num[tid];
		last_समय = &ieee->last_packet_समय[tid];
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर ((*last_seq == seq) &&
	    समय_after(*last_समय + IEEE_PACKET_RETRY_TIME, jअगरfies)) अणु
		अगर (*last_frag == frag)
			जाओ drop;
		अगर (*last_frag + 1 != frag)
			/* out-of-order fragment */
			जाओ drop;
	पूर्ण अन्यथा
		*last_seq = seq;

	*last_frag = frag;
	*last_समय = jअगरfies;
	वापस 0;

drop:

	वापस 1;
पूर्ण

अटल bool AddReorderEntry(काष्ठा rx_ts_record *pTS,
			    काष्ठा rx_reorder_entry *pReorderEntry)
अणु
	काष्ठा list_head *pList = &pTS->rx_pending_pkt_list;

	जबतक (pList->next != &pTS->rx_pending_pkt_list) अणु
		अगर (SN_LESS(pReorderEntry->SeqNum, ((काष्ठा rx_reorder_entry *)
		    list_entry(pList->next, काष्ठा rx_reorder_entry,
		    List))->SeqNum))
			pList = pList->next;
		अन्यथा अगर (SN_EQUAL(pReorderEntry->SeqNum,
			((काष्ठा rx_reorder_entry *)list_entry(pList->next,
			काष्ठा rx_reorder_entry, List))->SeqNum))
			वापस false;
		अन्यथा
			अवरोध;
	पूर्ण
	pReorderEntry->List.next = pList->next;
	pReorderEntry->List.next->prev = &pReorderEntry->List;
	pReorderEntry->List.prev = pList;
	pList->next = &pReorderEntry->List;

	वापस true;
पूर्ण

व्योम rtllib_indicate_packets(काष्ठा rtllib_device *ieee,
			     काष्ठा rtllib_rxb **prxbIndicateArray, u8 index)
अणु
	काष्ठा net_device_stats *stats = &ieee->stats;
	u8 i = 0, j = 0;
	u16 ethertype;

	क्रम (j = 0; j < index; j++) अणु
		काष्ठा rtllib_rxb *prxb = prxbIndicateArray[j];

		क्रम (i = 0; i < prxb->nr_subframes; i++) अणु
			काष्ठा sk_buff *sub_skb = prxb->subframes[i];

		/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
			ethertype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			अगर (sub_skb->len >= 8 &&
			    ((स_भेद(sub_skb->data, rfc1042_header,
				     SNAP_SIZE) == 0 &&
			      ethertype != ETH_P_AARP &&
			      ethertype != ETH_P_IPX) ||
			    स_भेद(sub_skb->data, bridge_tunnel_header,
				   SNAP_SIZE) == 0)) अणु
				/* हटाओ RFC1042 or Bridge-Tunnel encapsulation
				 * and replace EtherType
				 */
				skb_pull(sub_skb, SNAP_SIZE);
				स_नकल(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				स_नकल(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			पूर्ण अन्यथा अणु
				u16 len;
			/* Leave Ethernet header part of hdr and full payload */
				len = sub_skb->len;
				स_नकल(skb_push(sub_skb, 2), &len, 2);
				स_नकल(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				स_नकल(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			पूर्ण

			/* Indicate the packets to upper layer */
			अगर (sub_skb) अणु
				stats->rx_packets++;
				stats->rx_bytes += sub_skb->len;

				स_रखो(sub_skb->cb, 0, माप(sub_skb->cb));
				sub_skb->protocol = eth_type_trans(sub_skb,
								   ieee->dev);
				sub_skb->dev = ieee->dev;
				sub_skb->dev->stats.rx_packets++;
				sub_skb->dev->stats.rx_bytes += sub_skb->len;
				/* 802.11 crc not sufficient */
				sub_skb->ip_summed = CHECKSUM_NONE;
				ieee->last_rx_ps_समय = jअगरfies;
				netअगर_rx(sub_skb);
			पूर्ण
		पूर्ण
		kमुक्त(prxb);
		prxb = शून्य;
	पूर्ण
पूर्ण

व्योम rtllib_FlushRxTsPendingPkts(काष्ठा rtllib_device *ieee,
				 काष्ठा rx_ts_record *pTS)
अणु
	काष्ठा rx_reorder_entry *pRxReorderEntry;
	u8 RfdCnt = 0;

	del_समयr_sync(&pTS->rx_pkt_pending_समयr);
	जबतक (!list_empty(&pTS->rx_pending_pkt_list)) अणु
		अगर (RfdCnt >= REORDER_WIN_SIZE) अणु
			netdev_info(ieee->dev,
				    "-------------->%s() error! RfdCnt >= REORDER_WIN_SIZE\n",
				    __func__);
			अवरोध;
		पूर्ण

		pRxReorderEntry = (काष्ठा rx_reorder_entry *)
				  list_entry(pTS->rx_pending_pkt_list.prev,
					     काष्ठा rx_reorder_entry, List);
		netdev_dbg(ieee->dev, "%s(): Indicate SeqNum %d!\n", __func__,
			   pRxReorderEntry->SeqNum);
		list_del_init(&pRxReorderEntry->List);

		ieee->RfdArray[RfdCnt] = pRxReorderEntry->prxb;

		RfdCnt = RfdCnt + 1;
		list_add_tail(&pRxReorderEntry->List,
			      &ieee->RxReorder_Unused_List);
	पूर्ण
	rtllib_indicate_packets(ieee, ieee->RfdArray, RfdCnt);

	pTS->rx_indicate_seq = 0xffff;
पूर्ण

अटल व्योम RxReorderIndicatePacket(काष्ठा rtllib_device *ieee,
				    काष्ठा rtllib_rxb *prxb,
				    काष्ठा rx_ts_record *pTS, u16 SeqNum)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	काष्ठा rx_reorder_entry *pReorderEntry = शून्य;
	u8 WinSize = pHTInfo->RxReorderWinSize;
	u16 WinEnd = 0;
	u8 index = 0;
	bool bMatchWinStart = false, bPktInBuf = false;
	अचिन्हित दीर्घ flags;

	netdev_dbg(ieee->dev,
		   "%s(): Seq is %d, pTS->rx_indicate_seq is %d, WinSize is %d\n",
		   __func__, SeqNum, pTS->rx_indicate_seq, WinSize);

	spin_lock_irqsave(&(ieee->reorder_spinlock), flags);

	WinEnd = (pTS->rx_indicate_seq + WinSize - 1) % 4096;
	/* Rx Reorder initialize condition.*/
	अगर (pTS->rx_indicate_seq == 0xffff)
		pTS->rx_indicate_seq = SeqNum;

	/* Drop out the packet which SeqNum is smaller than WinStart */
	अगर (SN_LESS(SeqNum, pTS->rx_indicate_seq)) अणु
		netdev_dbg(ieee->dev,
			   "Packet Drop! IndicateSeq: %d, NewSeq: %d\n",
			   pTS->rx_indicate_seq, SeqNum);
		pHTInfo->RxReorderDropCounter++;
		अणु
			पूर्णांक i;

			क्रम (i = 0; i < prxb->nr_subframes; i++)
				dev_kमुक्त_skb(prxb->subframes[i]);
			kमुक्त(prxb);
			prxb = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
		वापस;
	पूर्ण

	/* Sliding winकरोw manipulation. Conditions includes:
	 * 1. Incoming SeqNum is equal to WinStart =>Winकरोw shअगरt 1
	 * 2. Incoming SeqNum is larger than the WinEnd => Winकरोw shअगरt N
	 */
	अगर (SN_EQUAL(SeqNum, pTS->rx_indicate_seq)) अणु
		pTS->rx_indicate_seq = (pTS->rx_indicate_seq + 1) % 4096;
		bMatchWinStart = true;
	पूर्ण अन्यथा अगर (SN_LESS(WinEnd, SeqNum)) अणु
		अगर (SeqNum >= (WinSize - 1))
			pTS->rx_indicate_seq = SeqNum + 1 - WinSize;
		अन्यथा
			pTS->rx_indicate_seq = 4095 -
					     (WinSize - (SeqNum + 1)) + 1;
		netdev_dbg(ieee->dev,
			   "Window Shift! IndicateSeq: %d, NewSeq: %d\n",
			   pTS->rx_indicate_seq, SeqNum);
	पूर्ण

	/* Indication process.
	 * After Packet dropping and Sliding Winकरोw shअगरting as above, we can
	 * now just indicate the packets with the SeqNum smaller than latest
	 * WinStart and काष्ठा buffer other packets.
	 *
	 * For Rx Reorder condition:
	 * 1. All packets with SeqNum smaller than WinStart => Indicate
	 * 2. All packets with SeqNum larger than or equal to
	 *	 WinStart => Buffer it.
	 */
	अगर (bMatchWinStart) अणु
		/* Current packet is going to be indicated.*/
		netdev_dbg(ieee->dev,
			   "Packets indication! IndicateSeq: %d, NewSeq: %d\n",
			   pTS->rx_indicate_seq, SeqNum);
		ieee->prxbIndicateArray[0] = prxb;
		index = 1;
	पूर्ण अन्यथा अणु
		/* Current packet is going to be inserted पूर्णांकo pending list.*/
		अगर (!list_empty(&ieee->RxReorder_Unused_List)) अणु
			pReorderEntry = (काष्ठा rx_reorder_entry *)
					list_entry(ieee->RxReorder_Unused_List.next,
					काष्ठा rx_reorder_entry, List);
			list_del_init(&pReorderEntry->List);

			/* Make a reorder entry and insert
			 * पूर्णांकo a the packet list.
			 */
			pReorderEntry->SeqNum = SeqNum;
			pReorderEntry->prxb = prxb;

			अगर (!AddReorderEntry(pTS, pReorderEntry)) अणु
				पूर्णांक i;

				netdev_dbg(ieee->dev,
					   "%s(): Duplicate packet is dropped. IndicateSeq: %d, NewSeq: %d\n",
					   __func__, pTS->rx_indicate_seq,
					   SeqNum);
				list_add_tail(&pReorderEntry->List,
					      &ieee->RxReorder_Unused_List);

				क्रम (i = 0; i < prxb->nr_subframes; i++)
					dev_kमुक्त_skb(prxb->subframes[i]);
				kमुक्त(prxb);
				prxb = शून्य;
			पूर्ण अन्यथा अणु
				netdev_dbg(ieee->dev,
					   "Pkt insert into struct buffer. IndicateSeq: %d, NewSeq: %d\n",
					   pTS->rx_indicate_seq, SeqNum);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Packets are dropped अगर there are not enough reorder
			 * entries. This part should be modअगरied!! We can just
			 * indicate all the packets in काष्ठा buffer and get
			 * reorder entries.
			 */
			netdev_err(ieee->dev,
				   "%s(): There is no reorder entry! Packet is dropped!\n",
				   __func__);
			अणु
				पूर्णांक i;

				क्रम (i = 0; i < prxb->nr_subframes; i++)
					dev_kमुक्त_skb(prxb->subframes[i]);
				kमुक्त(prxb);
				prxb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check अगर there is any packet need indicate.*/
	जबतक (!list_empty(&pTS->rx_pending_pkt_list)) अणु
		netdev_dbg(ieee->dev, "%s(): start RREORDER indicate\n",
			   __func__);

		pReorderEntry = (काष्ठा rx_reorder_entry *)
					list_entry(pTS->rx_pending_pkt_list.prev,
						   काष्ठा rx_reorder_entry,
						   List);
		अगर (SN_LESS(pReorderEntry->SeqNum, pTS->rx_indicate_seq) ||
		    SN_EQUAL(pReorderEntry->SeqNum, pTS->rx_indicate_seq)) अणु
			/* This protect काष्ठा buffer from overflow. */
			अगर (index >= REORDER_WIN_SIZE) अणु
				netdev_err(ieee->dev,
					   "%s(): Buffer overflow!\n",
					   __func__);
				bPktInBuf = true;
				अवरोध;
			पूर्ण

			list_del_init(&pReorderEntry->List);

			अगर (SN_EQUAL(pReorderEntry->SeqNum, pTS->rx_indicate_seq))
				pTS->rx_indicate_seq = (pTS->rx_indicate_seq + 1) %
						     4096;

			ieee->prxbIndicateArray[index] = pReorderEntry->prxb;
			netdev_dbg(ieee->dev, "%s(): Indicate SeqNum %d!\n",
				   __func__, pReorderEntry->SeqNum);
			index++;

			list_add_tail(&pReorderEntry->List,
				      &ieee->RxReorder_Unused_List);
		पूर्ण अन्यथा अणु
			bPktInBuf = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Handling pending समयr. Set this समयr to prevent from दीर्घ समय
	 * Rx buffering.
	 */
	अगर (index > 0) अणु
		अगर (समयr_pending(&pTS->rx_pkt_pending_समयr))
			del_समयr_sync(&pTS->rx_pkt_pending_समयr);
		pTS->rx_समयout_indicate_seq = 0xffff;

		अगर (index > REORDER_WIN_SIZE) अणु
			netdev_err(ieee->dev,
				   "%s(): Rx Reorder struct buffer full!\n",
				   __func__);
			spin_unlock_irqrestore(&(ieee->reorder_spinlock),
					       flags);
			वापस;
		पूर्ण
		rtllib_indicate_packets(ieee, ieee->prxbIndicateArray, index);
		bPktInBuf = false;
	पूर्ण

	अगर (bPktInBuf && pTS->rx_समयout_indicate_seq == 0xffff) अणु
		netdev_dbg(ieee->dev, "%s(): SET rx timeout timer\n", __func__);
		pTS->rx_समयout_indicate_seq = pTS->rx_indicate_seq;
		mod_समयr(&pTS->rx_pkt_pending_समयr, jअगरfies +
			  msecs_to_jअगरfies(pHTInfo->RxReorderPendingTime));
	पूर्ण
	spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
पूर्ण

अटल u8 parse_subframe(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			 काष्ठा rtllib_rx_stats *rx_stats,
			 काष्ठा rtllib_rxb *rxb, u8 *src, u8 *dst)
अणु
	काष्ठा rtllib_hdr_3addr  *hdr = (काष्ठा rtllib_hdr_3addr *)skb->data;
	u16		fc = le16_to_cpu(hdr->frame_ctl);

	u16		LLCOffset = माप(काष्ठा rtllib_hdr_3addr);
	u16		ChkLength;
	bool		bIsAggregateFrame = false;
	u16		nSubframe_Length;
	u8		nPadding_Length = 0;
	u16		SeqNum = 0;
	काष्ठा sk_buff *sub_skb;
	/* just क्रम debug purpose */
	SeqNum = WLAN_GET_SEQ_SEQ(le16_to_cpu(hdr->seq_ctl));
	अगर ((RTLLIB_QOS_HAS_SEQ(fc)) &&
	   (((जोड़ frameqos *)(skb->data + RTLLIB_3ADDR_LEN))->field.reserved))
		bIsAggregateFrame = true;

	अगर (RTLLIB_QOS_HAS_SEQ(fc))
		LLCOffset += 2;
	अगर (rx_stats->bContainHTC)
		LLCOffset += sHTCLng;

	ChkLength = LLCOffset;

	अगर (skb->len <= ChkLength)
		वापस 0;

	skb_pull(skb, LLCOffset);
	ieee->bIsAggregateFrame = bIsAggregateFrame;
	अगर (!bIsAggregateFrame) अणु
		rxb->nr_subframes = 1;

		/* altered by clark 3/30/2010
		 * The काष्ठा buffer size of the skb indicated to upper layer
		 * must be less than 5000, or the defraged IP datagram
		 * in the IP layer will exceed "ipfrag_high_tresh" and be
		 * discarded. so there must not use the function
		 * "skb_copy" and "skb_clone" क्रम "skb".
		 */

		/* Allocate new skb क्रम releasing to upper layer */
		sub_skb = dev_alloc_skb(RTLLIB_SKBBUFFER_SIZE);
		अगर (!sub_skb)
			वापस 0;
		skb_reserve(sub_skb, 12);
		skb_put_data(sub_skb, skb->data, skb->len);
		sub_skb->dev = ieee->dev;

		rxb->subframes[0] = sub_skb;

		स_नकल(rxb->src, src, ETH_ALEN);
		स_नकल(rxb->dst, dst, ETH_ALEN);
		rxb->subframes[0]->dev = ieee->dev;
		वापस 1;
	पूर्ण

	rxb->nr_subframes = 0;
	स_नकल(rxb->src, src, ETH_ALEN);
	स_नकल(rxb->dst, dst, ETH_ALEN);
	जबतक (skb->len > ETHERNET_HEADER_SIZE) अणु
		/* Offset 12 denote 2 mac address */
		nSubframe_Length = *((u16 *)(skb->data + 12));
		nSubframe_Length = (nSubframe_Length >> 8) +
				   (nSubframe_Length << 8);

		अगर (skb->len < (ETHERNET_HEADER_SIZE + nSubframe_Length)) अणु
			netdev_info(ieee->dev,
				    "%s: A-MSDU parse error!! pRfd->nTotalSubframe : %d\n",
				    __func__, rxb->nr_subframes);
			netdev_info(ieee->dev,
				    "%s: A-MSDU parse error!! Subframe Length: %d\n",
				    __func__, nSubframe_Length);
			netdev_info(ieee->dev,
				    "nRemain_Length is %d and nSubframe_Length is : %d\n",
				    skb->len, nSubframe_Length);
			netdev_info(ieee->dev,
				    "The Packet SeqNum is %d\n",
				    SeqNum);
			वापस 0;
		पूर्ण

		/* move the data poपूर्णांक to data content */
		skb_pull(skb, ETHERNET_HEADER_SIZE);

		/* altered by clark 3/30/2010
		 * The काष्ठा buffer size of the skb indicated to upper layer
		 * must be less than 5000, or the defraged IP datagram
		 * in the IP layer will exceed "ipfrag_high_tresh" and be
		 * discarded. so there must not use the function
		 * "skb_copy" and "skb_clone" क्रम "skb".
		 */

		/* Allocate new skb क्रम releasing to upper layer */
		sub_skb = dev_alloc_skb(nSubframe_Length + 12);
		अगर (!sub_skb)
			वापस 0;
		skb_reserve(sub_skb, 12);
		skb_put_data(sub_skb, skb->data, nSubframe_Length);

		sub_skb->dev = ieee->dev;
		rxb->subframes[rxb->nr_subframes++] = sub_skb;
		अगर (rxb->nr_subframes >= MAX_SUBFRAME_COUNT) अणु
			netdev_dbg(ieee->dev,
				   "ParseSubframe(): Too many Subframes! Packets dropped!\n");
			अवरोध;
		पूर्ण
		skb_pull(skb, nSubframe_Length);

		अगर (skb->len != 0) अणु
			nPadding_Length = 4 - ((nSubframe_Length +
					  ETHERNET_HEADER_SIZE) % 4);
			अगर (nPadding_Length == 4)
				nPadding_Length = 0;

			अगर (skb->len < nPadding_Length)
				वापस 0;

			skb_pull(skb, nPadding_Length);
		पूर्ण
	पूर्ण

	वापस rxb->nr_subframes;
पूर्ण


अटल माप_प्रकार rtllib_rx_get_hdrlen(काष्ठा rtllib_device *ieee,
				   काष्ठा sk_buff *skb,
				   काष्ठा rtllib_rx_stats *rx_stats)
अणु
	काष्ठा rtllib_hdr_4addr *hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	माप_प्रकार hdrlen;

	hdrlen = rtllib_get_hdrlen(fc);
	अगर (HTCCheck(ieee, skb->data)) अणु
		अगर (net_ratelimit())
			netdev_info(ieee->dev, "%s: find HTCControl!\n",
				    __func__);
		hdrlen += 4;
		rx_stats->bContainHTC = true;
	पूर्ण

	अगर (RTLLIB_QOS_HAS_SEQ(fc))
		rx_stats->bIsQosData = true;

	वापस hdrlen;
पूर्ण

अटल पूर्णांक rtllib_rx_check_duplicate(काष्ठा rtllib_device *ieee,
				     काष्ठा sk_buff *skb, u8 multicast)
अणु
	काष्ठा rtllib_hdr_4addr *hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	u16 fc, sc;
	u8 frag, type, stype;

	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);
	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);

	अगर (!ieee->pHTInfo->bCurRxReorderEnable ||
		!ieee->current_network.qos_data.active ||
		!IsDataFrame(skb->data) ||
		IsLegacyDataFrame(skb->data)) अणु
		अगर (!((type == RTLLIB_FTYPE_MGMT) &&
		      (stype == RTLLIB_STYPE_BEACON))) अणु
			अगर (is_duplicate_packet(ieee, hdr))
				वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा rx_ts_record *pRxTS = शून्य;

		अगर (GetTs(ieee, (काष्ठा ts_common_info **) &pRxTS, hdr->addr2,
			(u8)Frame_QoSTID((u8 *)(skb->data)), RX_सूची, true)) अणु
			अगर ((fc & (1<<11)) && (frag == pRxTS->rx_last_frag_num) &&
			    (WLAN_GET_SEQ_SEQ(sc) == pRxTS->rx_last_seq_num))
				वापस -1;
			pRxTS->rx_last_frag_num = frag;
			pRxTS->rx_last_seq_num = WLAN_GET_SEQ_SEQ(sc);
		पूर्ण अन्यथा अणु
			netdev_warn(ieee->dev, "%s(): No TS! Skip the check!\n",
				    __func__);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtllib_rx_extract_addr(काष्ठा rtllib_device *ieee,
				   काष्ठा rtllib_hdr_4addr *hdr, u8 *dst,
				   u8 *src, u8 *bssid)
अणु
	u16 fc = le16_to_cpu(hdr->frame_ctl);

	चयन (fc & (RTLLIB_FCTL_FROMDS | RTLLIB_FCTL_TODS)) अणु
	हाल RTLLIB_FCTL_FROMDS:
		ether_addr_copy(dst, hdr->addr1);
		ether_addr_copy(src, hdr->addr3);
		ether_addr_copy(bssid, hdr->addr2);
		अवरोध;
	हाल RTLLIB_FCTL_TODS:
		ether_addr_copy(dst, hdr->addr3);
		ether_addr_copy(src, hdr->addr2);
		ether_addr_copy(bssid, hdr->addr1);
		अवरोध;
	हाल RTLLIB_FCTL_FROMDS | RTLLIB_FCTL_TODS:
		ether_addr_copy(dst, hdr->addr3);
		ether_addr_copy(src, hdr->addr4);
		ether_addr_copy(bssid, ieee->current_network.bssid);
		अवरोध;
	शेष:
		ether_addr_copy(dst, hdr->addr1);
		ether_addr_copy(src, hdr->addr2);
		ether_addr_copy(bssid, hdr->addr3);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtllib_rx_data_filter(काष्ठा rtllib_device *ieee, u16 fc,
				 u8 *dst, u8 *src, u8 *bssid, u8 *addr2)
अणु
	u8 type, stype;

	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);

	/* Filter frames from dअगरferent BSS */
	अगर (((fc & RTLLIB_FCTL_DSTODS) != RTLLIB_FCTL_DSTODS) &&
	    !ether_addr_equal(ieee->current_network.bssid, bssid) &&
	    !is_zero_ether_addr(ieee->current_network.bssid)) अणु
		वापस -1;
	पूर्ण

	/* Filter packets sent by an STA that will be क्रमwarded by AP */
	अगर (ieee->IntelPromiscuousModeInfo.bPromiscuousOn  &&
		ieee->IntelPromiscuousModeInfo.bFilterSourceStationFrame) अणु
		अगर ((fc & RTLLIB_FCTL_TODS) && !(fc & RTLLIB_FCTL_FROMDS) &&
		    !ether_addr_equal(dst, ieee->current_network.bssid) &&
		    ether_addr_equal(bssid, ieee->current_network.bssid)) अणु
			वापस -1;
		पूर्ण
	पूर्ण

	/* Nullfunc frames may have PS-bit set, so they must be passed to
	 * hostap_handle_sta_rx() beक्रमe being dropped here.
	 */
	अगर (!ieee->IntelPromiscuousModeInfo.bPromiscuousOn) अणु
		अगर (stype != RTLLIB_STYPE_DATA &&
		    stype != RTLLIB_STYPE_DATA_CFACK &&
		    stype != RTLLIB_STYPE_DATA_CFPOLL &&
		    stype != RTLLIB_STYPE_DATA_CFACKPOLL &&
		    stype != RTLLIB_STYPE_QOS_DATA) अणु
			अगर (stype != RTLLIB_STYPE_शून्यFUNC)
				netdev_dbg(ieee->dev,
					   "RX: dropped data frame with no data (type=0x%02x, subtype=0x%02x)\n",
					   type, stype);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (ieee->iw_mode != IW_MODE_MESH) अणु
		/* packets from our adapter are dropped (echo) */
		अगर (!स_भेद(src, ieee->dev->dev_addr, ETH_ALEN))
			वापस -1;

		/* अणुbroad,multiपूर्णcast packets to our BSS go through */
		अगर (is_multicast_ether_addr(dst)) अणु
			अगर (स_भेद(bssid, ieee->current_network.bssid,
				   ETH_ALEN))
				वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtllib_rx_get_crypt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
			काष्ठा lib80211_crypt_data **crypt, माप_प्रकार hdrlen)
अणु
	काष्ठा rtllib_hdr_4addr *hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	पूर्णांक idx = 0;

	अगर (ieee->host_decrypt) अणु
		अगर (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;

		*crypt = ieee->crypt_info.crypt[idx];
		/* allow शून्य decrypt to indicate an station specअगरic override
		 * क्रम शेष encryption
		 */
		अगर (*crypt && ((*crypt)->ops == शून्य ||
			      (*crypt)->ops->decrypt_mpdu == शून्य))
			*crypt = शून्य;

		अगर (!*crypt && (fc & RTLLIB_FCTL_WEP)) अणु
			/* This seems to be triggered by some (multicast?)
			 * frames from other than current BSS, so just drop the
			 * frames silently instead of filling प्रणाली log with
			 * these reports.
			 */
			netdev_dbg(ieee->dev,
				   "Decryption failed (not set) (SA= %pM)\n",
				   hdr->addr2);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtllib_rx_decrypt(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		      काष्ठा rtllib_rx_stats *rx_stats,
		      काष्ठा lib80211_crypt_data *crypt, माप_प्रकार hdrlen)
अणु
	काष्ठा rtllib_hdr_4addr *hdr;
	पूर्णांक keyidx = 0;
	u16 fc, sc;
	u8 frag;

	hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);
	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);

	अगर ((!rx_stats->Decrypted))
		ieee->need_sw_enc = 1;
	अन्यथा
		ieee->need_sw_enc = 0;

	keyidx = rtllib_rx_frame_decrypt(ieee, skb, crypt);
	अगर (ieee->host_decrypt && (fc & RTLLIB_FCTL_WEP) && (keyidx < 0)) अणु
		netdev_info(ieee->dev, "%s: decrypt frame error\n", __func__);
		वापस -1;
	पूर्ण

	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	अगर ((frag != 0 || (fc & RTLLIB_FCTL_MOREFRAGS))) अणु
		पूर्णांक flen;
		काष्ठा sk_buff *frag_skb = rtllib_frag_cache_get(ieee, hdr);

		netdev_dbg(ieee->dev, "Rx Fragment received (%u)\n", frag);

		अगर (!frag_skb) अणु
			netdev_dbg(ieee->dev,
				   "Rx cannot get skb from fragment cache (morefrag=%d seq=%u frag=%u)\n",
				   (fc & RTLLIB_FCTL_MOREFRAGS) != 0,
				   WLAN_GET_SEQ_SEQ(sc), frag);
			वापस -1;
		पूर्ण
		flen = skb->len;
		अगर (frag != 0)
			flen -= hdrlen;

		अगर (frag_skb->tail + flen > frag_skb->end) अणु
			netdev_warn(ieee->dev,
				    "%s: host decrypted and reassembled frame did not fit skb\n",
				    __func__);
			rtllib_frag_cache_invalidate(ieee, hdr);
			वापस -1;
		पूर्ण

		अगर (frag == 0) अणु
			/* copy first fragment (including full headers) पूर्णांकo
			 * beginning of the fragment cache skb
			 */
			skb_put_data(frag_skb, skb->data, flen);
		पूर्ण अन्यथा अणु
			/* append frame payload to the end of the fragment
			 * cache skb
			 */
			skb_put_data(frag_skb, skb->data + hdrlen, flen);
		पूर्ण
		dev_kमुक्त_skb_any(skb);
		skb = शून्य;

		अगर (fc & RTLLIB_FCTL_MOREFRAGS) अणु
			/* more fragments expected - leave the skb in fragment
			 * cache क्रम now; it will be delivered to upper layers
			 * after all fragments have been received
			 */
			वापस -2;
		पूर्ण

		/* this was the last fragment and the frame will be
		 * delivered, so हटाओ skb from fragment cache
		 */
		skb = frag_skb;
		hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
		rtllib_frag_cache_invalidate(ieee, hdr);
	पूर्ण

	/* skb: hdr + (possible reassembled) full MSDU payload; possibly still
	 * encrypted/authenticated
	 */
	अगर (ieee->host_decrypt && (fc & RTLLIB_FCTL_WEP) &&
		rtllib_rx_frame_decrypt_msdu(ieee, skb, keyidx, crypt)) अणु
		netdev_info(ieee->dev, "%s: ==>decrypt msdu error\n", __func__);
		वापस -1;
	पूर्ण

	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	अगर (crypt && !(fc & RTLLIB_FCTL_WEP) && !ieee->खोलो_wep) अणु
		अगर (/*ieee->ieee802_1x &&*/
		    rtllib_is_eapol_frame(ieee, skb, hdrlen)) अणु

			/* pass unencrypted EAPOL frames even अगर encryption is
			 * configured
			 */
			काष्ठा eapol *eap = (काष्ठा eapol *)(skb->data +
				24);
			netdev_dbg(ieee->dev,
				   "RX: IEEE 802.1X EAPOL frame: %s\n",
				   eap_get_type(eap->type));
		पूर्ण अन्यथा अणु
			netdev_dbg(ieee->dev,
				   "encryption configured, but RX frame not encrypted (SA= %pM)\n",
				   hdr->addr2);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (crypt && !(fc & RTLLIB_FCTL_WEP) &&
	    rtllib_is_eapol_frame(ieee, skb, hdrlen)) अणु
		काष्ठा eapol *eap = (काष्ठा eapol *)(skb->data + 24);

		netdev_dbg(ieee->dev, "RX: IEEE 802.1X EAPOL frame: %s\n",
			   eap_get_type(eap->type));
	पूर्ण

	अगर (crypt && !(fc & RTLLIB_FCTL_WEP) && !ieee->खोलो_wep &&
	    !rtllib_is_eapol_frame(ieee, skb, hdrlen)) अणु
		netdev_dbg(ieee->dev,
			   "dropped unencrypted RX data frame from %pM (drop_unencrypted=1)\n",
			   hdr->addr2);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtllib_rx_check_leave_lps(काष्ठा rtllib_device *ieee, u8 unicast,
				      u8 nr_subframes)
अणु
	अगर (unicast) अणु

		अगर (ieee->state == RTLLIB_LINKED) अणु
			अगर (((ieee->LinkDetectInfo.NumRxUnicastOkInPeriod +
			    ieee->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
			    (ieee->LinkDetectInfo.NumRxUnicastOkInPeriod > 2)) अणु
				अगर (ieee->LeisurePSLeave)
					ieee->LeisurePSLeave(ieee->dev);
			पूर्ण
		पूर्ण
	पूर्ण
	ieee->last_rx_ps_समय = jअगरfies;
पूर्ण

अटल व्योम rtllib_rx_indicate_pkt_legacy(काष्ठा rtllib_device *ieee,
		काष्ठा rtllib_rx_stats *rx_stats,
		काष्ठा rtllib_rxb *rxb,
		u8 *dst,
		u8 *src)
अणु
	काष्ठा net_device *dev = ieee->dev;
	u16 ethertype;
	पूर्णांक i = 0;

	अगर (rxb == शून्य) अणु
		netdev_info(dev, "%s: rxb is NULL!!\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < rxb->nr_subframes; i++) अणु
		काष्ठा sk_buff *sub_skb = rxb->subframes[i];

		अगर (sub_skb) अणु
			/* convert hdr + possible LLC headers
			 * पूर्णांकo Ethernet header
			 */
			ethertype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			अगर (sub_skb->len >= 8 &&
				((स_भेद(sub_skb->data, rfc1042_header, SNAP_SIZE) == 0 &&
				ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
				स_भेद(sub_skb->data, bridge_tunnel_header, SNAP_SIZE) == 0)) अणु
				/* हटाओ RFC1042 or Bridge-Tunnel encapsulation
				 * and replace EtherType
				 */
				skb_pull(sub_skb, SNAP_SIZE);
				ether_addr_copy(skb_push(sub_skb, ETH_ALEN),
						src);
				ether_addr_copy(skb_push(sub_skb, ETH_ALEN),
						dst);
			पूर्ण अन्यथा अणु
				u16 len;
				/* Leave Ethernet header part of hdr
				 * and full payload
				 */
				len = sub_skb->len;
				स_नकल(skb_push(sub_skb, 2), &len, 2);
				ether_addr_copy(skb_push(sub_skb, ETH_ALEN),
						src);
				ether_addr_copy(skb_push(sub_skb, ETH_ALEN),
						dst);
			पूर्ण

			ieee->stats.rx_packets++;
			ieee->stats.rx_bytes += sub_skb->len;

			अगर (is_multicast_ether_addr(dst))
				ieee->stats.multicast++;

			/* Indicate the packets to upper layer */
			स_रखो(sub_skb->cb, 0, माप(sub_skb->cb));
			sub_skb->protocol = eth_type_trans(sub_skb, dev);
			sub_skb->dev = dev;
			sub_skb->dev->stats.rx_packets++;
			sub_skb->dev->stats.rx_bytes += sub_skb->len;
			/* 802.11 crc not sufficient */
			sub_skb->ip_summed = CHECKSUM_NONE;
			netअगर_rx(sub_skb);
		पूर्ण
	पूर्ण
	kमुक्त(rxb);
पूर्ण

अटल पूर्णांक rtllib_rx_InfraAdhoc(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा rtllib_rx_stats *rx_stats)
अणु
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा rtllib_hdr_4addr *hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	काष्ठा lib80211_crypt_data *crypt = शून्य;
	काष्ठा rtllib_rxb *rxb = शून्य;
	काष्ठा rx_ts_record *pTS = शून्य;
	u16 fc, sc, SeqNum = 0;
	u8 type, stype, multicast = 0, unicast = 0, nr_subframes = 0, TID = 0;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 bssid[ETH_ALEN] = अणु0पूर्ण;

	माप_प्रकार hdrlen = 0;
	bool bToOtherSTA = false;
	पूर्णांक ret = 0, i = 0;

	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);
	sc = le16_to_cpu(hdr->seq_ctl);

	/*Filter pkt not to me*/
	multicast = is_multicast_ether_addr(hdr->addr1);
	unicast = !multicast;
	अगर (unicast && !ether_addr_equal(dev->dev_addr, hdr->addr1)) अणु
		अगर (ieee->bNetPromiscuousMode)
			bToOtherSTA = true;
		अन्यथा
			जाओ rx_dropped;
	पूर्ण

	/*Filter pkt has too small length */
	hdrlen = rtllib_rx_get_hdrlen(ieee, skb, rx_stats);
	अगर (skb->len < hdrlen) अणु
		netdev_info(dev,
			    "%s():ERR!!! skb->len is smaller than hdrlen\n",
			    __func__);
		जाओ rx_dropped;
	पूर्ण

	/* Filter Duplicate pkt */
	ret = rtllib_rx_check_duplicate(ieee, skb, multicast);
	अगर (ret < 0)
		जाओ rx_dropped;

	/* Filter CTRL Frame */
	अगर (type == RTLLIB_FTYPE_CTL)
		जाओ rx_dropped;

	/* Filter MGNT Frame */
	अगर (type == RTLLIB_FTYPE_MGMT) अणु
		अगर (bToOtherSTA)
			जाओ rx_dropped;
		अगर (rtllib_rx_frame_mgmt(ieee, skb, rx_stats, type, stype))
			जाओ rx_dropped;
		अन्यथा
			जाओ rx_निकास;
	पूर्ण

	/* Filter WAPI DATA Frame */

	/* Update statstics क्रम AP roaming */
	अगर (!bToOtherSTA) अणु
		ieee->LinkDetectInfo.NumRecvDataInPeriod++;
		ieee->LinkDetectInfo.NumRxOkInPeriod++;
	पूर्ण

	/* Data frame - extract src/dst addresses */
	rtllib_rx_extract_addr(ieee, hdr, dst, src, bssid);

	/* Filter Data frames */
	ret = rtllib_rx_data_filter(ieee, fc, dst, src, bssid, hdr->addr2);
	अगर (ret < 0)
		जाओ rx_dropped;

	अगर (skb->len == hdrlen)
		जाओ rx_dropped;

	/* Send pspoll based on moredata */
	अगर ((ieee->iw_mode == IW_MODE_INFRA)  &&
	    (ieee->sta_sleep == LPS_IS_SLEEP) &&
	    (ieee->polling) && (!bToOtherSTA)) अणु
		अगर (WLAN_FC_MORE_DATA(fc)) अणु
			/* more data bit is set, let's request a new frame
			 * from the AP
			 */
			rtllib_sta_ps_send_pspoll_frame(ieee);
		पूर्ण अन्यथा अणु
			ieee->polling =  false;
		पूर्ण
	पूर्ण

	/* Get crypt अगर encrypted */
	ret = rtllib_rx_get_crypt(ieee, skb, &crypt, hdrlen);
	अगर (ret == -1)
		जाओ rx_dropped;

	/* Decrypt data frame (including reassemble) */
	ret = rtllib_rx_decrypt(ieee, skb, rx_stats, crypt, hdrlen);
	अगर (ret == -1)
		जाओ rx_dropped;
	अन्यथा अगर (ret == -2)
		जाओ rx_निकास;

	/* Get TS क्रम Rx Reorder  */
	hdr = (काष्ठा rtllib_hdr_4addr *) skb->data;
	अगर (ieee->current_network.qos_data.active && IsQoSDataFrame(skb->data)
		&& !is_multicast_ether_addr(hdr->addr1)
		&& (!bToOtherSTA)) अणु
		TID = Frame_QoSTID(skb->data);
		SeqNum = WLAN_GET_SEQ_SEQ(sc);
		GetTs(ieee, (काष्ठा ts_common_info **) &pTS, hdr->addr2, TID,
		      RX_सूची, true);
		अगर (TID != 0 && TID != 3)
			ieee->bis_any_nonbepkts = true;
	पूर्ण

	/* Parse rx data frame (For AMSDU) */
	/* skb: hdr + (possible reassembled) full plaपूर्णांकext payload */
	rxb = kदो_स्मृति(माप(काष्ठा rtllib_rxb), GFP_ATOMIC);
	अगर (!rxb)
		जाओ rx_dropped;

	/* to parse amsdu packets */
	/* qos data packets & reserved bit is 1 */
	अगर (parse_subframe(ieee, skb, rx_stats, rxb, src, dst) == 0) अणु
		/* only to मुक्त rxb, and not submit the packets
		 * to upper layer
		 */
		क्रम (i = 0; i < rxb->nr_subframes; i++)
			dev_kमुक्त_skb(rxb->subframes[i]);
		kमुक्त(rxb);
		rxb = शून्य;
		जाओ rx_dropped;
	पूर्ण

	/* Update WAPI PN */

	/* Check अगर leave LPS */
	अगर (!bToOtherSTA) अणु
		अगर (ieee->bIsAggregateFrame)
			nr_subframes = rxb->nr_subframes;
		अन्यथा
			nr_subframes = 1;
		अगर (unicast)
			ieee->LinkDetectInfo.NumRxUnicastOkInPeriod += nr_subframes;
		rtllib_rx_check_leave_lps(ieee, unicast, nr_subframes);
	पूर्ण

	/* Indicate packets to upper layer or Rx Reorder */
	अगर (!ieee->pHTInfo->bCurRxReorderEnable || pTS == शून्य || bToOtherSTA)
		rtllib_rx_indicate_pkt_legacy(ieee, rx_stats, rxb, dst, src);
	अन्यथा
		RxReorderIndicatePacket(ieee, rxb, pTS, SeqNum);

	dev_kमुक्त_skb(skb);

 rx_निकास:
	वापस 1;

 rx_dropped:
	ieee->stats.rx_dropped++;

	/* Returning 0 indicates to caller that we have not handled the SKB--
	 * so it is still allocated and can be used again by underlying
	 * hardware as a DMA target
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक rtllib_rx_Master(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा rtllib_rx_stats *rx_stats)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtllib_rx_Monitor(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा rtllib_rx_stats *rx_stats)
अणु
	काष्ठा rtllib_hdr_4addr *hdr = (काष्ठा rtllib_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	माप_प्रकार hdrlen = rtllib_get_hdrlen(fc);

	अगर (skb->len < hdrlen) अणु
		netdev_info(ieee->dev,
			    "%s():ERR!!! skb->len is smaller than hdrlen\n",
			    __func__);
		वापस 0;
	पूर्ण

	अगर (HTCCheck(ieee, skb->data)) अणु
		अगर (net_ratelimit())
			netdev_info(ieee->dev, "%s: Find HTCControl!\n",
				    __func__);
		hdrlen += 4;
	पूर्ण

	rtllib_monitor_rx(ieee, skb, rx_stats, hdrlen);
	ieee->stats.rx_packets++;
	ieee->stats.rx_bytes += skb->len;

	वापस 1;
पूर्ण

अटल पूर्णांक rtllib_rx_Mesh(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा rtllib_rx_stats *rx_stats)
अणु
	वापस 0;
पूर्ण

/* All received frames are sent to this function. @skb contains the frame in
 * IEEE 802.11 क्रमmat, i.e., in the क्रमmat it was sent over air.
 * This function is called only as a tasklet (software IRQ).
 */
पूर्णांक rtllib_rx(काष्ठा rtllib_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा rtllib_rx_stats *rx_stats)
अणु
	पूर्णांक ret = 0;

	अगर (!ieee || !skb || !rx_stats) अणु
		pr_info("%s: Input parameters NULL!\n", __func__);
		जाओ rx_dropped;
	पूर्ण
	अगर (skb->len < 10) अणु
		netdev_info(ieee->dev, "%s: SKB length < 10\n", __func__);
		जाओ rx_dropped;
	पूर्ण

	चयन (ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
	हाल IW_MODE_INFRA:
		ret = rtllib_rx_InfraAdhoc(ieee, skb, rx_stats);
		अवरोध;
	हाल IW_MODE_MASTER:
	हाल IW_MODE_REPEAT:
		ret = rtllib_rx_Master(ieee, skb, rx_stats);
		अवरोध;
	हाल IW_MODE_MONITOR:
		ret = rtllib_rx_Monitor(ieee, skb, rx_stats);
		अवरोध;
	हाल IW_MODE_MESH:
		ret = rtllib_rx_Mesh(ieee, skb, rx_stats);
		अवरोध;
	शेष:
		netdev_info(ieee->dev, "%s: ERR iw mode!!!\n", __func__);
		अवरोध;
	पूर्ण

	वापस ret;

 rx_dropped:
	अगर (ieee)
		ieee->stats.rx_dropped++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_rx);

अटल u8 qos_oui[QOS_OUI_LEN] = अणु 0x00, 0x50, 0xF2 पूर्ण;

/* Make ther काष्ठाure we पढ़ो from the beacon packet has the right values */
अटल पूर्णांक rtllib_verअगरy_qos_info(काष्ठा rtllib_qos_inक्रमmation_element
				     *info_element, पूर्णांक sub_type)
अणु

	अगर (info_element->qui_subtype != sub_type)
		वापस -1;
	अगर (स_भेद(info_element->qui, qos_oui, QOS_OUI_LEN))
		वापस -1;
	अगर (info_element->qui_type != QOS_OUI_TYPE)
		वापस -1;
	अगर (info_element->version != QOS_VERSION_1)
		वापस -1;

	वापस 0;
पूर्ण


/* Parse a QoS parameter element */
अटल पूर्णांक rtllib_पढ़ो_qos_param_element(काष्ठा rtllib_qos_parameter_info
							*element_param,
					 काष्ठा rtllib_info_element
							*info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा rtllib_qos_parameter_info) - 2;

	अगर ((info_element == शून्य) || (element_param == शून्य))
		वापस -1;

	अगर (info_element->id == QOS_ELEMENT_ID && info_element->len == size) अणु
		स_नकल(element_param->info_element.qui, info_element->data,
		       info_element->len);
		element_param->info_element.elementID = info_element->id;
		element_param->info_element.length = info_element->len;
	पूर्ण अन्यथा
		ret = -1;
	अगर (ret == 0)
		ret = rtllib_verअगरy_qos_info(&element_param->info_element,
						QOS_OUI_PARAM_SUB_TYPE);
	वापस ret;
पूर्ण

/* Parse a QoS inक्रमmation element */
अटल पूर्णांक rtllib_पढ़ो_qos_info_element(काष्ठा rtllib_qos_inक्रमmation_element
							*element_info,
					काष्ठा rtllib_info_element
							*info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा rtllib_qos_inक्रमmation_element) - 2;

	अगर (element_info == शून्य)
		वापस -1;
	अगर (info_element == शून्य)
		वापस -1;

	अगर ((info_element->id == QOS_ELEMENT_ID) &&
	    (info_element->len == size)) अणु
		स_नकल(element_info->qui, info_element->data,
		       info_element->len);
		element_info->elementID = info_element->id;
		element_info->length = info_element->len;
	पूर्ण अन्यथा
		ret = -1;

	अगर (ret == 0)
		ret = rtllib_verअगरy_qos_info(element_info,
					     QOS_OUI_INFO_SUB_TYPE);
	वापस ret;
पूर्ण


/* Write QoS parameters from the ac parameters. */
अटल पूर्णांक rtllib_qos_convert_ac_to_parameters(काष्ठा rtllib_qos_parameter_info *param_elm,
					       काष्ठा rtllib_qos_data *qos_data)
अणु
	काष्ठा rtllib_qos_ac_parameter *ac_params;
	काष्ठा rtllib_qos_parameters *qos_param = &(qos_data->parameters);
	पूर्णांक i;
	u8 aci;
	u8 acm;

	qos_data->wmm_acm = 0;
	क्रम (i = 0; i < QOS_QUEUE_NUM; i++) अणु
		ac_params = &(param_elm->ac_params_record[i]);

		aci = (ac_params->aci_aअगरsn & 0x60) >> 5;
		acm = (ac_params->aci_aअगरsn & 0x10) >> 4;

		अगर (aci >= QOS_QUEUE_NUM)
			जारी;
		चयन (aci) अणु
		हाल 1:
			/* BIT(0) | BIT(3) */
			अगर (acm)
				qos_data->wmm_acm |= (0x01<<0)|(0x01<<3);
			अवरोध;
		हाल 2:
			/* BIT(4) | BIT(5) */
			अगर (acm)
				qos_data->wmm_acm |= (0x01<<4)|(0x01<<5);
			अवरोध;
		हाल 3:
			/* BIT(6) | BIT(7) */
			अगर (acm)
				qos_data->wmm_acm |= (0x01<<6)|(0x01<<7);
			अवरोध;
		हाल 0:
		शेष:
			/* BIT(1) | BIT(2) */
			अगर (acm)
				qos_data->wmm_acm |= (0x01<<1)|(0x01<<2);
			अवरोध;
		पूर्ण

		qos_param->aअगरs[aci] = (ac_params->aci_aअगरsn) & 0x0f;

		/* WMM spec P.11: The minimum value क्रम AIFSN shall be 2 */
		qos_param->aअगरs[aci] = max_t(u8, qos_param->aअगरs[aci], 2);

		qos_param->cw_min[aci] = cpu_to_le16(ac_params->ecw_min_max &
						     0x0F);

		qos_param->cw_max[aci] = cpu_to_le16((ac_params->ecw_min_max &
						      0xF0) >> 4);

		qos_param->flag[aci] =
		    (ac_params->aci_aअगरsn & 0x10) ? 0x01 : 0x00;
		qos_param->tx_op_limit[aci] = ac_params->tx_op_limit;
	पूर्ण
	वापस 0;
पूर्ण

/* we have a generic data element which it may contain QoS inक्रमmation or
 * parameters element. check the inक्रमmation element length to decide
 * which type to पढ़ो
 */
अटल पूर्णांक rtllib_parse_qos_info_param_IE(काष्ठा rtllib_device *ieee,
					  काष्ठा rtllib_info_element
					     *info_element,
					  काष्ठा rtllib_network *network)
अणु
	पूर्णांक rc = 0;
	काष्ठा rtllib_qos_inक्रमmation_element qos_info_element;

	rc = rtllib_पढ़ो_qos_info_element(&qos_info_element, info_element);

	अगर (rc == 0) अणु
		network->qos_data.param_count = qos_info_element.ac_info & 0x0F;
		network->flags |= NETWORK_HAS_QOS_INFORMATION;
	पूर्ण अन्यथा अणु
		काष्ठा rtllib_qos_parameter_info param_element;

		rc = rtllib_पढ़ो_qos_param_element(&param_element,
						      info_element);
		अगर (rc == 0) अणु
			rtllib_qos_convert_ac_to_parameters(&param_element,
							       &(network->qos_data));
			network->flags |= NETWORK_HAS_QOS_PARAMETERS;
			network->qos_data.param_count =
			    param_element.info_element.ac_info & 0x0F;
		पूर्ण
	पूर्ण

	अगर (rc == 0) अणु
		netdev_dbg(ieee->dev, "QoS is supported\n");
		network->qos_data.supported = 1;
	पूर्ण
	वापस rc;
पूर्ण

अटल स्थिर अक्षर *get_info_element_string(u16 id)
अणु
	चयन (id) अणु
	हाल MFIE_TYPE_SSID:
		वापस "SSID";
	हाल MFIE_TYPE_RATES:
		वापस "RATES";
	हाल MFIE_TYPE_FH_SET:
		वापस "FH_SET";
	हाल MFIE_TYPE_DS_SET:
		वापस "DS_SET";
	हाल MFIE_TYPE_CF_SET:
		वापस "CF_SET";
	हाल MFIE_TYPE_TIM:
		वापस "TIM";
	हाल MFIE_TYPE_IBSS_SET:
		वापस "IBSS_SET";
	हाल MFIE_TYPE_COUNTRY:
		वापस "COUNTRY";
	हाल MFIE_TYPE_HOP_PARAMS:
		वापस "HOP_PARAMS";
	हाल MFIE_TYPE_HOP_TABLE:
		वापस "HOP_TABLE";
	हाल MFIE_TYPE_REQUEST:
		वापस "REQUEST";
	हाल MFIE_TYPE_CHALLENGE:
		वापस "CHALLENGE";
	हाल MFIE_TYPE_POWER_CONSTRAINT:
		वापस "POWER_CONSTRAINT";
	हाल MFIE_TYPE_POWER_CAPABILITY:
		वापस "POWER_CAPABILITY";
	हाल MFIE_TYPE_TPC_REQUEST:
		वापस "TPC_REQUEST";
	हाल MFIE_TYPE_TPC_REPORT:
		वापस "TPC_REPORT";
	हाल MFIE_TYPE_SUPP_CHANNELS:
		वापस "SUPP_CHANNELS";
	हाल MFIE_TYPE_CSA:
		वापस "CSA";
	हाल MFIE_TYPE_MEASURE_REQUEST:
		वापस "MEASURE_REQUEST";
	हाल MFIE_TYPE_MEASURE_REPORT:
		वापस "MEASURE_REPORT";
	हाल MFIE_TYPE_QUIET:
		वापस "QUIET";
	हाल MFIE_TYPE_IBSS_DFS:
		वापस "IBSS_DFS";
	हाल MFIE_TYPE_RSN:
		वापस "RSN";
	हाल MFIE_TYPE_RATES_EX:
		वापस "RATES_EX";
	हाल MFIE_TYPE_GENERIC:
		वापस "GENERIC";
	हाल MFIE_TYPE_QOS_PARAMETER:
		वापस "QOS_PARAMETER";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rtllib_extract_country_ie(
	काष्ठा rtllib_device *ieee,
	काष्ठा rtllib_info_element *info_element,
	काष्ठा rtllib_network *network,
	u8 *addr2)
अणु
	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (info_element->len != 0) अणु
			स_नकल(network->CountryIeBuf, info_element->data,
			       info_element->len);
			network->CountryIeLen = info_element->len;

			अगर (!IS_COUNTRY_IE_VALID(ieee)) अणु
				अगर (rtllib_act_scanning(ieee, false) &&
				    ieee->FirstIe_InScan)
					netdev_info(ieee->dev,
						    "Received beacon ContryIE, SSID: <%s>\n",
						    network->ssid);
				करोt11d_update_country(ieee, addr2,
						       info_element->len,
						       info_element->data);
			पूर्ण
		पूर्ण

		अगर (IS_EQUAL_CIE_SRC(ieee, addr2))
			UPDATE_CIE_WATCHDOG(ieee);
	पूर्ण
पूर्ण

अटल व्योम rtllib_parse_mअगरe_generic(काष्ठा rtllib_device *ieee,
				      काष्ठा rtllib_info_element *info_element,
				      काष्ठा rtllib_network *network,
				      u16 *पंचांगp_htcap_len,
				      u16 *पंचांगp_htinfo_len)
अणु
	u16 ht_realtek_agg_len = 0;
	u8  ht_realtek_agg_buf[MAX_IE_LEN];

	अगर (!rtllib_parse_qos_info_param_IE(ieee, info_element, network))
		वापस;
	अगर (info_element->len >= 4 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x50 &&
	    info_element->data[2] == 0xf2 &&
	    info_element->data[3] == 0x01) अणु
		network->wpa_ie_len = min(info_element->len + 2,
					  MAX_WPA_IE_LEN);
		स_नकल(network->wpa_ie, info_element, network->wpa_ie_len);
		वापस;
	पूर्ण
	अगर (info_element->len == 7 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0xe0 &&
	    info_element->data[2] == 0x4c &&
	    info_element->data[3] == 0x01 &&
	    info_element->data[4] == 0x02)
		network->Turbo_Enable = 1;

	अगर (*पंचांगp_htcap_len == 0) अणु
		अगर (info_element->len >= 4 &&
		    info_element->data[0] == 0x00 &&
		    info_element->data[1] == 0x90 &&
		    info_element->data[2] == 0x4c &&
		    info_element->data[3] == 0x033) अणु
			*पंचांगp_htcap_len = min_t(u8, info_element->len,
					       MAX_IE_LEN);
			अगर (*पंचांगp_htcap_len != 0) अणु
				network->bssht.bd_ht_spec_ver = HT_SPEC_VER_EWC;
				network->bssht.bd_ht_cap_len = min_t(u16, *पंचांगp_htcap_len,
								  माप(network->bssht.bd_ht_cap_buf));
				स_नकल(network->bssht.bd_ht_cap_buf,
				       info_element->data,
				       network->bssht.bd_ht_cap_len);
			पूर्ण
		पूर्ण
		अगर (*पंचांगp_htcap_len != 0) अणु
			network->bssht.bd_support_ht = true;
			network->bssht.bd_ht_1r = ((((काष्ठा ht_capab_ele *)(network->bssht.bd_ht_cap_buf))->MCS[1]) == 0);
		पूर्ण अन्यथा अणु
			network->bssht.bd_support_ht = false;
			network->bssht.bd_ht_1r = false;
		पूर्ण
	पूर्ण


	अगर (*पंचांगp_htinfo_len == 0) अणु
		अगर (info_element->len >= 4 &&
		    info_element->data[0] == 0x00 &&
		    info_element->data[1] == 0x90 &&
		    info_element->data[2] == 0x4c &&
		    info_element->data[3] == 0x034) अणु
			*पंचांगp_htinfo_len = min_t(u8, info_element->len,
						MAX_IE_LEN);
			अगर (*पंचांगp_htinfo_len != 0) अणु
				network->bssht.bd_ht_spec_ver = HT_SPEC_VER_EWC;
				network->bssht.bd_ht_info_len = min_t(u16, *पंचांगp_htinfo_len,
								      माप(network->bssht.bd_ht_info_buf));
				स_नकल(network->bssht.bd_ht_info_buf,
				       info_element->data,
				       network->bssht.bd_ht_info_len);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (network->bssht.bd_support_ht) अणु
		अगर (info_element->len >= 4 &&
		    info_element->data[0] == 0x00 &&
		    info_element->data[1] == 0xe0 &&
		    info_element->data[2] == 0x4c &&
		    info_element->data[3] == 0x02) अणु
			ht_realtek_agg_len = min_t(u8, info_element->len,
						   MAX_IE_LEN);
			स_नकल(ht_realtek_agg_buf, info_element->data,
			       info_element->len);
		पूर्ण
		अगर (ht_realtek_agg_len >= 5) अणु
			network->realtek_cap_निकास = true;
			network->bssht.bd_rt2rt_aggregation = true;

			अगर ((ht_realtek_agg_buf[4] == 1) &&
			    (ht_realtek_agg_buf[5] & 0x02))
				network->bssht.bd_rt2rt_दीर्घ_slot_समय = true;

			अगर ((ht_realtek_agg_buf[4] == 1) &&
			    (ht_realtek_agg_buf[5] & RT_HT_CAP_USE_92SE))
				network->bssht.rt2rt_ht_mode |= RT_HT_CAP_USE_92SE;
		पूर्ण
	पूर्ण
	अगर (ht_realtek_agg_len >= 5) अणु
		अगर ((ht_realtek_agg_buf[5] & RT_HT_CAP_USE_SOFTAP))
			network->bssht.rt2rt_ht_mode |= RT_HT_CAP_USE_SOFTAP;
	पूर्ण

	अगर ((info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x05 &&
	     info_element->data[2] == 0xb5) ||
	     (info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x0a &&
	     info_element->data[2] == 0xf7) ||
	     (info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x10 &&
	     info_element->data[2] == 0x18)) अणु
		network->broadcom_cap_exist = true;
	पूर्ण
	अगर (info_element->len >= 3 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x0c &&
	    info_element->data[2] == 0x43)
		network->ralink_cap_exist = true;
	अगर ((info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x03 &&
	     info_element->data[2] == 0x7f) ||
	     (info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x13 &&
	     info_element->data[2] == 0x74))
		network->atheros_cap_exist = true;

	अगर ((info_element->len >= 3 &&
	     info_element->data[0] == 0x00 &&
	     info_element->data[1] == 0x50 &&
	     info_element->data[2] == 0x43))
		network->marvell_cap_exist = true;
	अगर (info_element->len >= 3 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x40 &&
	    info_element->data[2] == 0x96)
		network->cisco_cap_exist = true;


	अगर (info_element->len >= 3 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x0a &&
	    info_element->data[2] == 0xf5)
		network->airgo_cap_exist = true;

	अगर (info_element->len > 4 &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x40 &&
	    info_element->data[2] == 0x96 &&
	    info_element->data[3] == 0x01) अणु
		अगर (info_element->len == 6) अणु
			स_नकल(network->CcxRmState, &info_element->data[4], 2);
			अगर (network->CcxRmState[0] != 0)
				network->bCcxRmEnable = true;
			अन्यथा
				network->bCcxRmEnable = false;
			network->MBssidMask = network->CcxRmState[1] & 0x07;
			अगर (network->MBssidMask != 0) अणु
				network->bMBssidValid = true;
				network->MBssidMask = 0xff <<
						      (network->MBssidMask);
				ether_addr_copy(network->MBssid,
						network->bssid);
				network->MBssid[5] &= network->MBssidMask;
			पूर्ण अन्यथा अणु
				network->bMBssidValid = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			network->bCcxRmEnable = false;
		पूर्ण
	पूर्ण
	अगर (info_element->len > 4  &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x40 &&
	    info_element->data[2] == 0x96 &&
	    info_element->data[3] == 0x03) अणु
		अगर (info_element->len == 5) अणु
			network->bWithCcxVerNum = true;
			network->BssCcxVerNumber = info_element->data[4];
		पूर्ण अन्यथा अणु
			network->bWithCcxVerNum = false;
			network->BssCcxVerNumber = 0;
		पूर्ण
	पूर्ण
	अगर (info_element->len > 4  &&
	    info_element->data[0] == 0x00 &&
	    info_element->data[1] == 0x50 &&
	    info_element->data[2] == 0xf2 &&
	    info_element->data[3] == 0x04) अणु
		netdev_dbg(ieee->dev, "MFIE_TYPE_WZC: %d bytes\n",
			   info_element->len);
		network->wzc_ie_len = min(info_element->len+2, MAX_WZC_IE_LEN);
		स_नकल(network->wzc_ie, info_element, network->wzc_ie_len);
	पूर्ण
पूर्ण

अटल व्योम rtllib_parse_mfie_ht_cap(काष्ठा rtllib_info_element *info_element,
				     काष्ठा rtllib_network *network,
				     u16 *पंचांगp_htcap_len)
अणु
	काष्ठा bss_ht *ht = &network->bssht;

	*पंचांगp_htcap_len = min_t(u8, info_element->len, MAX_IE_LEN);
	अगर (*पंचांगp_htcap_len != 0) अणु
		ht->bd_ht_spec_ver = HT_SPEC_VER_EWC;
		ht->bd_ht_cap_len = min_t(u16, *पंचांगp_htcap_len,
				       माप(ht->bd_ht_cap_buf));
		स_नकल(ht->bd_ht_cap_buf, info_element->data, ht->bd_ht_cap_len);

		ht->bd_support_ht = true;
		ht->bd_ht_1r = ((((काष्ठा ht_capab_ele *)
				ht->bd_ht_cap_buf))->MCS[1]) == 0;

		ht->bd_bandwidth = (क्रमागत ht_channel_width)
					     (((काष्ठा ht_capab_ele *)
					     (ht->bd_ht_cap_buf))->ChlWidth);
	पूर्ण अन्यथा अणु
		ht->bd_support_ht = false;
		ht->bd_ht_1r = false;
		ht->bd_bandwidth = HT_CHANNEL_WIDTH_20;
	पूर्ण
पूर्ण

पूर्णांक rtllib_parse_info_param(काष्ठा rtllib_device *ieee,
		काष्ठा rtllib_info_element *info_element,
		u16 length,
		काष्ठा rtllib_network *network,
		काष्ठा rtllib_rx_stats *stats)
अणु
	u8 i;
	लघु offset;
	u16	पंचांगp_htcap_len = 0;
	u16	पंचांगp_htinfo_len = 0;
	अक्षर rates_str[64];
	अक्षर *p;

	जबतक (length >= माप(*info_element)) अणु
		अगर (माप(*info_element) + info_element->len > length) अणु
			netdev_dbg(ieee->dev,
				   "Info elem: parse failed: info_element->len + 2 > left : info_element->len+2=%zd left=%d, id=%d.\n",
				   info_element->len + माप(*info_element),
				   length, info_element->id);
			/* We stop processing but करोn't वापस an error here
			 * because some misbehaviour APs अवरोध this rule. ie.
			 * Orinoco AP1000.
			 */
			अवरोध;
		पूर्ण

		चयन (info_element->id) अणु
		हाल MFIE_TYPE_SSID:
			अगर (rtllib_is_empty_essid(info_element->data,
						     info_element->len)) अणु
				network->flags |= NETWORK_EMPTY_ESSID;
				अवरोध;
			पूर्ण

			network->ssid_len = min(info_element->len,
						(u8) IW_ESSID_MAX_SIZE);
			स_नकल(network->ssid, info_element->data,
			       network->ssid_len);
			अगर (network->ssid_len < IW_ESSID_MAX_SIZE)
				स_रखो(network->ssid + network->ssid_len, 0,
				       IW_ESSID_MAX_SIZE - network->ssid_len);

			netdev_dbg(ieee->dev, "MFIE_TYPE_SSID: '%s' len=%d.\n",
				   network->ssid, network->ssid_len);
			अवरोध;

		हाल MFIE_TYPE_RATES:
			p = rates_str;
			network->rates_len = min(info_element->len,
						 MAX_RATES_LENGTH);
			क्रम (i = 0; i < network->rates_len; i++) अणु
				network->rates[i] = info_element->data[i];
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates[i]);
				अगर (rtllib_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    RTLLIB_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण

				अगर (rtllib_is_cck_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			netdev_dbg(ieee->dev, "MFIE_TYPE_RATES: '%s' (%d)\n",
				   rates_str, network->rates_len);
			अवरोध;

		हाल MFIE_TYPE_RATES_EX:
			p = rates_str;
			network->rates_ex_len = min(info_element->len,
						    MAX_RATES_EX_LENGTH);
			क्रम (i = 0; i < network->rates_ex_len; i++) अणु
				network->rates_ex[i] = info_element->data[i];
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates_ex[i]);
				अगर (rtllib_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    RTLLIB_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			netdev_dbg(ieee->dev, "MFIE_TYPE_RATES_EX: '%s' (%d)\n",
				   rates_str, network->rates_ex_len);
			अवरोध;

		हाल MFIE_TYPE_DS_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_DS_SET: %d\n",
				   info_element->data[0]);
			network->channel = info_element->data[0];
			अवरोध;

		हाल MFIE_TYPE_FH_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_FH_SET: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_CF_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_CF_SET: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_TIM:
			अगर (info_element->len < 4)
				अवरोध;

			network->tim.tim_count = info_element->data[0];
			network->tim.tim_period = info_element->data[1];

			network->dtim_period = info_element->data[1];
			अगर (ieee->state != RTLLIB_LINKED)
				अवरोध;
			network->last_dtim_sta_समय = jअगरfies;

			network->dtim_data = RTLLIB_DTIM_VALID;


			अगर (info_element->data[2] & 1)
				network->dtim_data |= RTLLIB_DTIM_MBCAST;

			offset = (info_element->data[2] >> 1)*2;


			अगर (ieee->assoc_id < 8*offset ||
			    ieee->assoc_id > 8*(offset + info_element->len - 3))
				अवरोध;

			offset = (ieee->assoc_id / 8) - offset;
			अगर (info_element->data[3 + offset] &
			   (1 << (ieee->assoc_id % 8)))
				network->dtim_data |= RTLLIB_DTIM_UCAST;

			network->listen_पूर्णांकerval = network->dtim_period;
			अवरोध;

		हाल MFIE_TYPE_ERP:
			network->erp_value = info_element->data[0];
			network->flags |= NETWORK_HAS_ERP_VALUE;
			netdev_dbg(ieee->dev, "MFIE_TYPE_ERP_SET: %d\n",
				   network->erp_value);
			अवरोध;
		हाल MFIE_TYPE_IBSS_SET:
			network->atim_winकरोw = info_element->data[0];
			netdev_dbg(ieee->dev, "MFIE_TYPE_IBSS_SET: %d\n",
				   network->atim_winकरोw);
			अवरोध;

		हाल MFIE_TYPE_CHALLENGE:
			netdev_dbg(ieee->dev, "MFIE_TYPE_CHALLENGE: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_GENERIC:
			netdev_dbg(ieee->dev, "MFIE_TYPE_GENERIC: %d bytes\n",
				   info_element->len);

			rtllib_parse_mअगरe_generic(ieee, info_element, network,
						  &पंचांगp_htcap_len,
						  &पंचांगp_htinfo_len);
			अवरोध;

		हाल MFIE_TYPE_RSN:
			netdev_dbg(ieee->dev, "MFIE_TYPE_RSN: %d bytes\n",
				   info_element->len);
			network->rsn_ie_len = min(info_element->len + 2,
						  MAX_WPA_IE_LEN);
			स_नकल(network->rsn_ie, info_element,
			       network->rsn_ie_len);
			अवरोध;

		हाल MFIE_TYPE_HT_CAP:
			netdev_dbg(ieee->dev, "MFIE_TYPE_HT_CAP: %d bytes\n",
				   info_element->len);

			rtllib_parse_mfie_ht_cap(info_element, network,
						 &पंचांगp_htcap_len);
			अवरोध;


		हाल MFIE_TYPE_HT_INFO:
			netdev_dbg(ieee->dev, "MFIE_TYPE_HT_INFO: %d bytes\n",
				   info_element->len);
			पंचांगp_htinfo_len = min_t(u8, info_element->len,
					       MAX_IE_LEN);
			अगर (पंचांगp_htinfo_len) अणु
				network->bssht.bd_ht_spec_ver = HT_SPEC_VER_IEEE;
				network->bssht.bd_ht_info_len = पंचांगp_htinfo_len >
					माप(network->bssht.bd_ht_info_buf) ?
					माप(network->bssht.bd_ht_info_buf) :
					पंचांगp_htinfo_len;
				स_नकल(network->bssht.bd_ht_info_buf,
				       info_element->data,
				       network->bssht.bd_ht_info_len);
			पूर्ण
			अवरोध;

		हाल MFIE_TYPE_AIRONET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_AIRONET: %d bytes\n",
				   info_element->len);
			अगर (info_element->len > IE_CISCO_FLAG_POSITION) अणु
				network->bWithAironetIE = true;

				अगर ((info_element->data[IE_CISCO_FLAG_POSITION]
				     & SUPPORT_CKIP_MIC) ||
				     (info_element->data[IE_CISCO_FLAG_POSITION]
				     & SUPPORT_CKIP_PK))
					network->bCkipSupported = true;
				अन्यथा
					network->bCkipSupported = false;
			पूर्ण अन्यथा अणु
				network->bWithAironetIE = false;
				network->bCkipSupported = false;
			पूर्ण
			अवरोध;
		हाल MFIE_TYPE_QOS_PARAMETER:
			netdev_err(ieee->dev,
				   "QoS Error need to parse QOS_PARAMETER IE\n");
			अवरोध;

		हाल MFIE_TYPE_COUNTRY:
			netdev_dbg(ieee->dev, "MFIE_TYPE_COUNTRY: %d bytes\n",
				   info_element->len);
			rtllib_extract_country_ie(ieee, info_element, network,
						  network->bssid);
			अवरोध;
/* TODO */
		शेष:
			netdev_dbg(ieee->dev,
				   "Unsupported info element: %s (%d)\n",
				   get_info_element_string(info_element->id),
				   info_element->id);
			अवरोध;
		पूर्ण

		length -= माप(*info_element) + info_element->len;
		info_element =
		    (काष्ठा rtllib_info_element *)&info_element->
		    data[info_element->len];
	पूर्ण

	अगर (!network->atheros_cap_exist && !network->broadcom_cap_exist &&
	    !network->cisco_cap_exist && !network->ralink_cap_exist &&
	    !network->bssht.bd_rt2rt_aggregation)
		network->unknown_cap_exist = true;
	अन्यथा
		network->unknown_cap_exist = false;
	वापस 0;
पूर्ण

अटल दीर्घ rtllib_translate_todbm(u8 संकेत_strength_index)
अणु
	दीर्घ	संकेत_घातer;

	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;

	वापस संकेत_घातer;
पूर्ण

अटल अंतरभूत पूर्णांक rtllib_network_init(
	काष्ठा rtllib_device *ieee,
	काष्ठा rtllib_probe_response *beacon,
	काष्ठा rtllib_network *network,
	काष्ठा rtllib_rx_stats *stats)
अणु
	स_रखो(&network->qos_data, 0, माप(काष्ठा rtllib_qos_data));

	/* Pull out fixed field data */
	ether_addr_copy(network->bssid, beacon->header.addr3);
	network->capability = le16_to_cpu(beacon->capability);
	network->last_scanned = jअगरfies;
	network->समय_stamp[0] = beacon->समय_stamp[0];
	network->समय_stamp[1] = beacon->समय_stamp[1];
	network->beacon_पूर्णांकerval = le16_to_cpu(beacon->beacon_पूर्णांकerval);
	/* Where to pull this? beacon->listen_पूर्णांकerval;*/
	network->listen_पूर्णांकerval = 0x0A;
	network->rates_len = network->rates_ex_len = 0;
	network->ssid_len = 0;
	network->hidden_ssid_len = 0;
	स_रखो(network->hidden_ssid, 0, माप(network->hidden_ssid));
	network->flags = 0;
	network->atim_winकरोw = 0;
	network->erp_value = (network->capability & WLAN_CAPABILITY_IBSS) ?
	    0x3 : 0x0;
	network->berp_info_valid = false;
	network->broadcom_cap_exist = false;
	network->ralink_cap_exist = false;
	network->atheros_cap_exist = false;
	network->cisco_cap_exist = false;
	network->unknown_cap_exist = false;
	network->realtek_cap_निकास = false;
	network->marvell_cap_exist = false;
	network->airgo_cap_exist = false;
	network->Turbo_Enable = 0;
	network->SignalStrength = stats->SignalStrength;
	network->RSSI = stats->SignalStrength;
	network->CountryIeLen = 0;
	स_रखो(network->CountryIeBuf, 0, MAX_IE_LEN);
	HTInitializeBssDesc(&network->bssht);
	अगर (stats->freq == RTLLIB_52GHZ_BAND) अणु
		/* क्रम A band (No DS info) */
		network->channel = stats->received_channel;
	पूर्ण अन्यथा
		network->flags |= NETWORK_HAS_CCK;

	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;
	network->wzc_ie_len = 0;

	अगर (rtllib_parse_info_param(ieee,
			beacon->info_element,
			(stats->len - माप(*beacon)),
			network,
			stats))
		वापस 1;

	network->mode = 0;
	अगर (stats->freq == RTLLIB_52GHZ_BAND)
		network->mode = IEEE_A;
	अन्यथा अणु
		अगर (network->flags & NETWORK_HAS_OFDM)
			network->mode |= IEEE_G;
		अगर (network->flags & NETWORK_HAS_CCK)
			network->mode |= IEEE_B;
	पूर्ण

	अगर (network->mode == 0) अणु
		netdev_dbg(ieee->dev, "Filtered out '%s (%pM)' network.\n",
			   escape_essid(network->ssid, network->ssid_len),
			   network->bssid);
		वापस 1;
	पूर्ण

	अगर (network->bssht.bd_support_ht) अणु
		अगर (network->mode == IEEE_A)
			network->mode = IEEE_N_5G;
		अन्यथा अगर (network->mode & (IEEE_G | IEEE_B))
			network->mode = IEEE_N_24G;
	पूर्ण
	अगर (rtllib_is_empty_essid(network->ssid, network->ssid_len))
		network->flags |= NETWORK_EMPTY_ESSID;
	stats->संकेत = 30 + (stats->SignalStrength * 70) / 100;
	stats->noise = rtllib_translate_todbm((u8)(100-stats->संकेत)) - 25;

	स_नकल(&network->stats, stats, माप(network->stats));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_same_network(काष्ठा rtllib_network *src,
				  काष्ठा rtllib_network *dst, u8 ssidbroad)
अणु
	/* A network is only a duplicate अगर the channel, BSSID, ESSID
	 * and the capability field (in particular IBSS and BSS) all match.
	 * We treat all <hidden> with the same BSSID and channel
	 * as one network
	 */
	वापस (((src->ssid_len == dst->ssid_len) || (!ssidbroad)) &&
		(src->channel == dst->channel) &&
		!स_भेद(src->bssid, dst->bssid, ETH_ALEN) &&
		(!स_भेद(src->ssid, dst->ssid, src->ssid_len) ||
		(!ssidbroad)) &&
		((src->capability & WLAN_CAPABILITY_IBSS) ==
		(dst->capability & WLAN_CAPABILITY_IBSS)) &&
		((src->capability & WLAN_CAPABILITY_ESS) ==
		(dst->capability & WLAN_CAPABILITY_ESS)));
पूर्ण


अटल अंतरभूत व्योम update_network(काष्ठा rtllib_device *ieee,
				  काष्ठा rtllib_network *dst,
				  काष्ठा rtllib_network *src)
अणु
	पूर्णांक qos_active;
	u8 old_param;

	स_नकल(&dst->stats, &src->stats, माप(काष्ठा rtllib_rx_stats));
	dst->capability = src->capability;
	स_नकल(dst->rates, src->rates, src->rates_len);
	dst->rates_len = src->rates_len;
	स_नकल(dst->rates_ex, src->rates_ex, src->rates_ex_len);
	dst->rates_ex_len = src->rates_ex_len;
	अगर (src->ssid_len > 0) अणु
		अगर (dst->ssid_len == 0) अणु
			स_रखो(dst->hidden_ssid, 0, माप(dst->hidden_ssid));
			dst->hidden_ssid_len = src->ssid_len;
			स_नकल(dst->hidden_ssid, src->ssid, src->ssid_len);
		पूर्ण अन्यथा अणु
			स_रखो(dst->ssid, 0, dst->ssid_len);
			dst->ssid_len = src->ssid_len;
			स_नकल(dst->ssid, src->ssid, src->ssid_len);
		पूर्ण
	पूर्ण
	dst->mode = src->mode;
	dst->flags = src->flags;
	dst->समय_stamp[0] = src->समय_stamp[0];
	dst->समय_stamp[1] = src->समय_stamp[1];
	अगर (src->flags & NETWORK_HAS_ERP_VALUE) अणु
		dst->erp_value = src->erp_value;
		dst->berp_info_valid = src->berp_info_valid = true;
	पूर्ण
	dst->beacon_पूर्णांकerval = src->beacon_पूर्णांकerval;
	dst->listen_पूर्णांकerval = src->listen_पूर्णांकerval;
	dst->atim_winकरोw = src->atim_winकरोw;
	dst->dtim_period = src->dtim_period;
	dst->dtim_data = src->dtim_data;
	dst->last_dtim_sta_समय = src->last_dtim_sta_समय;
	स_नकल(&dst->tim, &src->tim, माप(काष्ठा rtllib_tim_parameters));

	dst->bssht.bd_support_ht = src->bssht.bd_support_ht;
	dst->bssht.bd_rt2rt_aggregation = src->bssht.bd_rt2rt_aggregation;
	dst->bssht.bd_ht_cap_len = src->bssht.bd_ht_cap_len;
	स_नकल(dst->bssht.bd_ht_cap_buf, src->bssht.bd_ht_cap_buf,
	       src->bssht.bd_ht_cap_len);
	dst->bssht.bd_ht_info_len = src->bssht.bd_ht_info_len;
	स_नकल(dst->bssht.bd_ht_info_buf, src->bssht.bd_ht_info_buf,
	       src->bssht.bd_ht_info_len);
	dst->bssht.bd_ht_spec_ver = src->bssht.bd_ht_spec_ver;
	dst->bssht.bd_rt2rt_दीर्घ_slot_समय = src->bssht.bd_rt2rt_दीर्घ_slot_समय;
	dst->broadcom_cap_exist = src->broadcom_cap_exist;
	dst->ralink_cap_exist = src->ralink_cap_exist;
	dst->atheros_cap_exist = src->atheros_cap_exist;
	dst->realtek_cap_निकास = src->realtek_cap_निकास;
	dst->marvell_cap_exist = src->marvell_cap_exist;
	dst->cisco_cap_exist = src->cisco_cap_exist;
	dst->airgo_cap_exist = src->airgo_cap_exist;
	dst->unknown_cap_exist = src->unknown_cap_exist;
	स_नकल(dst->wpa_ie, src->wpa_ie, src->wpa_ie_len);
	dst->wpa_ie_len = src->wpa_ie_len;
	स_नकल(dst->rsn_ie, src->rsn_ie, src->rsn_ie_len);
	dst->rsn_ie_len = src->rsn_ie_len;
	स_नकल(dst->wzc_ie, src->wzc_ie, src->wzc_ie_len);
	dst->wzc_ie_len = src->wzc_ie_len;

	dst->last_scanned = jअगरfies;
	/* qos related parameters */
	qos_active = dst->qos_data.active;
	old_param = dst->qos_data.param_count;
	dst->qos_data.supported = src->qos_data.supported;
	अगर (dst->flags & NETWORK_HAS_QOS_PARAMETERS)
		स_नकल(&dst->qos_data, &src->qos_data,
		       माप(काष्ठा rtllib_qos_data));
	अगर (dst->qos_data.supported == 1) अणु
		अगर (dst->ssid_len)
			netdev_dbg(ieee->dev,
				   "QoS the network %s is QoS supported\n",
				   dst->ssid);
		अन्यथा
			netdev_dbg(ieee->dev,
				   "QoS the network is QoS supported\n");
	पूर्ण
	dst->qos_data.active = qos_active;
	dst->qos_data.old_param_count = old_param;

	dst->wmm_info = src->wmm_info;
	अगर (src->wmm_param[0].ac_aci_acm_aअगरsn ||
	   src->wmm_param[1].ac_aci_acm_aअगरsn ||
	   src->wmm_param[2].ac_aci_acm_aअगरsn ||
	   src->wmm_param[3].ac_aci_acm_aअगरsn)
		स_नकल(dst->wmm_param, src->wmm_param, WME_AC_PRAM_LEN);

	dst->SignalStrength = src->SignalStrength;
	dst->RSSI = src->RSSI;
	dst->Turbo_Enable = src->Turbo_Enable;

	dst->CountryIeLen = src->CountryIeLen;
	स_नकल(dst->CountryIeBuf, src->CountryIeBuf, src->CountryIeLen);

	dst->bWithAironetIE = src->bWithAironetIE;
	dst->bCkipSupported = src->bCkipSupported;
	स_नकल(dst->CcxRmState, src->CcxRmState, 2);
	dst->bCcxRmEnable = src->bCcxRmEnable;
	dst->MBssidMask = src->MBssidMask;
	dst->bMBssidValid = src->bMBssidValid;
	स_नकल(dst->MBssid, src->MBssid, 6);
	dst->bWithCcxVerNum = src->bWithCcxVerNum;
	dst->BssCcxVerNumber = src->BssCcxVerNumber;
पूर्ण

अटल अंतरभूत पूर्णांक is_beacon(u16 fc)
अणु
	वापस (WLAN_FC_GET_STYPE(fc) == RTLLIB_STYPE_BEACON);
पूर्ण

अटल पूर्णांक IsPassiveChannel(काष्ठा rtllib_device *rtllib, u8 channel)
अणु
	अगर (channel > MAX_CHANNEL_NUMBER) अणु
		netdev_info(rtllib->dev, "%s(): Invalid Channel\n", __func__);
		वापस 0;
	पूर्ण

	अगर (rtllib->active_channel_map[channel] == 2)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक rtllib_legal_channel(काष्ठा rtllib_device *rtllib, u8 channel)
अणु
	अगर (channel > MAX_CHANNEL_NUMBER) अणु
		netdev_info(rtllib->dev, "%s(): Invalid Channel\n", __func__);
		वापस 0;
	पूर्ण
	अगर (rtllib->active_channel_map[channel] > 0)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtllib_legal_channel);

अटल अंतरभूत व्योम rtllib_process_probe_response(
	काष्ठा rtllib_device *ieee,
	काष्ठा rtllib_probe_response *beacon,
	काष्ठा rtllib_rx_stats *stats)
अणु
	काष्ठा rtllib_network *target;
	काष्ठा rtllib_network *oldest = शून्य;
	काष्ठा rtllib_info_element *info_element = &beacon->info_element[0];
	अचिन्हित दीर्घ flags;
	लघु renew;
	काष्ठा rtllib_network *network = kzalloc(माप(काष्ठा rtllib_network),
						 GFP_ATOMIC);
	u16 frame_ctl = le16_to_cpu(beacon->header.frame_ctl);

	अगर (!network)
		वापस;

	netdev_dbg(ieee->dev,
		   "'%s' ( %pM ): %c%c%c%c %c%c%c%c-%c%c%c%c %c%c%c%c\n",
		   escape_essid(info_element->data, info_element->len),
		   beacon->header.addr3,
		   (le16_to_cpu(beacon->capability) & (1<<0xf)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0xe)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0xd)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0xc)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0xb)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0xa)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x9)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x8)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x7)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x6)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x5)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x4)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x3)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x2)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x1)) ? '1' : '0',
		   (le16_to_cpu(beacon->capability) & (1<<0x0)) ? '1' : '0');

	अगर (rtllib_network_init(ieee, beacon, network, stats)) अणु
		netdev_dbg(ieee->dev, "Dropped '%s' ( %pM) via %s.\n",
			   escape_essid(info_element->data, info_element->len),
			   beacon->header.addr3,
			   is_beacon(frame_ctl) ? "BEACON" : "PROBE RESPONSE");
		जाओ मुक्त_network;
	पूर्ण


	अगर (!rtllib_legal_channel(ieee, network->channel))
		जाओ मुक्त_network;

	अगर (WLAN_FC_GET_STYPE(frame_ctl) == RTLLIB_STYPE_PROBE_RESP) अणु
		अगर (IsPassiveChannel(ieee, network->channel)) अणु
			netdev_info(ieee->dev,
				    "GetScanInfo(): For Global Domain, filter probe response at channel(%d).\n",
				    network->channel);
			जाओ मुक्त_network;
		पूर्ण
	पूर्ण

	/* The network parsed correctly -- so now we scan our known networks
	 * to see अगर we can find it in our list.
	 *
	 * NOTE:  This search is definitely not optimized.  Once its करोing
	 *	the "right thing" we'll optimize it क्रम efficiency अगर
	 *	necessary
	 */

	/* Search क्रम this entry in the list and update it अगर it is
	 * alपढ़ोy there.
	 */

	spin_lock_irqsave(&ieee->lock, flags);
	अगर (is_same_network(&ieee->current_network, network,
	   (network->ssid_len ? 1 : 0))) अणु
		update_network(ieee, &ieee->current_network, network);
		अगर ((ieee->current_network.mode == IEEE_N_24G ||
		     ieee->current_network.mode == IEEE_G) &&
		    ieee->current_network.berp_info_valid) अणु
			अगर (ieee->current_network.erp_value & ERP_UseProtection)
				ieee->current_network.buseprotection = true;
			अन्यथा
				ieee->current_network.buseprotection = false;
		पूर्ण
		अगर (is_beacon(frame_ctl)) अणु
			अगर (ieee->state >= RTLLIB_LINKED)
				ieee->LinkDetectInfo.NumRecvBcnInPeriod++;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(target, &ieee->network_list, list) अणु
		अगर (is_same_network(target, network,
		   (target->ssid_len ? 1 : 0)))
			अवरोध;
		अगर ((oldest == शून्य) ||
		    (target->last_scanned < oldest->last_scanned))
			oldest = target;
	पूर्ण

	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation
	 */
	अगर (&target->list == &ieee->network_list) अणु
		अगर (list_empty(&ieee->network_मुक्त_list)) अणु
			/* If there are no more slots, expire the oldest */
			list_del(&oldest->list);
			target = oldest;
			netdev_dbg(ieee->dev,
				   "Expired '%s' ( %pM) from network list.\n",
				   escape_essid(target->ssid, target->ssid_len),
				   target->bssid);
		पूर्ण अन्यथा अणु
			/* Otherwise just pull from the मुक्त list */
			target = list_entry(ieee->network_मुक्त_list.next,
					    काष्ठा rtllib_network, list);
			list_del(ieee->network_मुक्त_list.next);
		पूर्ण

		netdev_dbg(ieee->dev, "Adding '%s' ( %pM) via %s.\n",
			   escape_essid(network->ssid, network->ssid_len),
			   network->bssid,
			   is_beacon(frame_ctl) ? "BEACON" : "PROBE RESPONSE");

		स_नकल(target, network, माप(*target));
		list_add_tail(&target->list, &ieee->network_list);
		अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE)
			rtllib_sofपंचांगac_new_net(ieee, network);
	पूर्ण अन्यथा अणु
		netdev_dbg(ieee->dev, "Updating '%s' ( %pM) via %s.\n",
			   escape_essid(target->ssid, target->ssid_len),
			   target->bssid,
			   is_beacon(frame_ctl) ? "BEACON" : "PROBE RESPONSE");

		/* we have an entry and we are going to update it. But this
		 *  entry may be alपढ़ोy expired. In this हाल we करो the same
		 * as we found a new net and call the new_net handler
		 */
		renew = !समय_after(target->last_scanned + ieee->scan_age,
				    jअगरfies);
		अगर ((!target->ssid_len) &&
		    (((network->ssid_len > 0) && (target->hidden_ssid_len == 0))
		    || ((ieee->current_network.ssid_len == network->ssid_len) &&
		    (म_भेदन(ieee->current_network.ssid, network->ssid,
		    network->ssid_len) == 0) &&
		    (ieee->state == RTLLIB_NOLINK))))
			renew = 1;
		update_network(ieee, target, network);
		अगर (renew && (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE))
			rtllib_sofपंचांगac_new_net(ieee, network);
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);
	अगर (is_beacon(frame_ctl) &&
	    is_same_network(&ieee->current_network, network,
	    (network->ssid_len ? 1 : 0)) &&
	    (ieee->state == RTLLIB_LINKED)) अणु
		अगर (ieee->handle_beacon != शून्य)
			ieee->handle_beacon(ieee->dev, beacon,
					    &ieee->current_network);
	पूर्ण
मुक्त_network:
	kमुक्त(network);
पूर्ण

अटल व्योम rtllib_rx_mgt(काष्ठा rtllib_device *ieee,
			  काष्ठा sk_buff *skb,
			  काष्ठा rtllib_rx_stats *stats)
अणु
	काष्ठा rtllib_hdr_4addr *header = (काष्ठा rtllib_hdr_4addr *)skb->data;

	अगर ((WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) !=
	    RTLLIB_STYPE_PROBE_RESP) &&
	    (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) !=
	    RTLLIB_STYPE_BEACON))
		ieee->last_rx_ps_समय = jअगरfies;

	चयन (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl))) अणु

	हाल RTLLIB_STYPE_BEACON:
		netdev_dbg(ieee->dev, "received BEACON (%d)\n",
			   WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		rtllib_process_probe_response(
				ieee, (काष्ठा rtllib_probe_response *)header,
				stats);

		अगर (ieee->sta_sleep || (ieee->ps != RTLLIB_PS_DISABLED &&
		    ieee->iw_mode == IW_MODE_INFRA &&
		    ieee->state == RTLLIB_LINKED))
			tasklet_schedule(&ieee->ps_task);

		अवरोध;

	हाल RTLLIB_STYPE_PROBE_RESP:
		netdev_dbg(ieee->dev, "received PROBE RESPONSE (%d)\n",
			   WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		rtllib_process_probe_response(ieee,
			      (काष्ठा rtllib_probe_response *)header, stats);
		अवरोध;
	हाल RTLLIB_STYPE_PROBE_REQ:
		netdev_dbg(ieee->dev, "received PROBE RESQUEST (%d)\n",
			   WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		अगर ((ieee->sofपंचांगac_features & IEEE_SOFTMAC_PROBERS) &&
		    ((ieee->iw_mode == IW_MODE_ADHOC ||
		    ieee->iw_mode == IW_MODE_MASTER) &&
		    ieee->state == RTLLIB_LINKED))
			rtllib_rx_probe_rq(ieee, skb);
		अवरोध;
	पूर्ण
पूर्ण
