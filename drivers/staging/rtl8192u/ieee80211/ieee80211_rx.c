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
 ******************************************************************************

  Few modअगरications क्रम Realtek's Wi-Fi drivers by
  Andrea Merello <andrea.merello@gmail.com>

  A special thanks goes to Realtek क्रम their support !

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
#समावेश <linux/प्रकार.स>

#समावेश "ieee80211.h"
#समावेश "dot11d.h"
अटल अंतरभूत व्योम ieee80211_monitor_rx(काष्ठा ieee80211_device *ieee,
					काष्ठा sk_buff *skb,
					काष्ठा ieee80211_rx_stats *rx_stats)
अणु
	काष्ठा rtl_80211_hdr_4addr *hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);

	skb->dev = ieee->dev;
	skb_reset_mac_header(skb);

	skb_pull(skb, ieee80211_get_hdrlen(fc));
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_80211_RAW);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल काष्ठा ieee80211_frag_entry *
ieee80211_frag_cache_find(काष्ठा ieee80211_device *ieee, अचिन्हित पूर्णांक seq,
			  अचिन्हित पूर्णांक frag, u8 tid, u8 *src, u8 *dst)
अणु
	काष्ठा ieee80211_frag_entry *entry;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_FRAG_CACHE_LEN; i++) अणु
		entry = &ieee->frag_cache[tid][i];
		अगर (entry->skb &&
		    समय_after(jअगरfies, entry->first_frag_समय + 2 * HZ)) अणु
			IEEE80211_DEBUG_FRAG(
				"expiring fragment cache entry "
				"seq=%u last_frag=%u\n",
				entry->seq, entry->last_frag);
			dev_kमुक्त_skb_any(entry->skb);
			entry->skb = शून्य;
		पूर्ण

		अगर (entry->skb && entry->seq == seq &&
		    (entry->last_frag + 1 == frag || frag == -1) &&
		    स_भेद(entry->src_addr, src, ETH_ALEN) == 0 &&
		    स_भेद(entry->dst_addr, dst, ETH_ALEN) == 0)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल काष्ठा sk_buff *
ieee80211_frag_cache_get(काष्ठा ieee80211_device *ieee,
			 काष्ठा rtl_80211_hdr_4addr *hdr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	u16 sc = le16_to_cpu(hdr->seq_ctl);
	अचिन्हित पूर्णांक frag = WLAN_GET_SEQ_FRAG(sc);
	अचिन्हित पूर्णांक seq = WLAN_GET_SEQ_SEQ(sc);
	काष्ठा ieee80211_frag_entry *entry;
	काष्ठा rtl_80211_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtl_80211_hdr_4addrqos *hdr_4addrqos;
	u8 tid;

	अगर (((fc & IEEE80211_FCTL_DSTODS) == IEEE80211_FCTL_DSTODS) && IEEE80211_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtl_80211_hdr_4addrqos *)hdr;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (IEEE80211_QOS_HAS_SEQ(fc)) अणु
		hdr_3addrqos = (काष्ठा rtl_80211_hdr_3addrqos *)hdr;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु
		tid = 0;
	पूर्ण

	अगर (frag == 0) अणु
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(ieee->dev->mtu +
				    माप(काष्ठा rtl_80211_hdr_4addr) +
				    8 /* LLC */ +
				    2 /* alignment */ +
				    8 /* WEP */ +
				    ETH_ALEN /* WDS */ +
				    (IEEE80211_QOS_HAS_SEQ(fc) ? 2 : 0) /* QOS Control */);
		अगर (!skb)
			वापस शून्य;

		entry = &ieee->frag_cache[tid][ieee->frag_next_idx[tid]];
		ieee->frag_next_idx[tid]++;
		अगर (ieee->frag_next_idx[tid] >= IEEE80211_FRAG_CACHE_LEN)
			ieee->frag_next_idx[tid] = 0;

		अगर (entry->skb)
			dev_kमुक्त_skb_any(entry->skb);

		entry->first_frag_समय = jअगरfies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		स_नकल(entry->src_addr, hdr->addr2, ETH_ALEN);
		स_नकल(entry->dst_addr, hdr->addr1, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* received a fragment of a frame क्रम which the head fragment
		 * should have alपढ़ोy been received */
		entry = ieee80211_frag_cache_find(ieee, seq, frag, tid, hdr->addr2,
						  hdr->addr1);
		अगर (entry) अणु
			entry->last_frag = frag;
			skb = entry->skb;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक ieee80211_frag_cache_invalidate(काष्ठा ieee80211_device *ieee,
					   काष्ठा rtl_80211_hdr_4addr *hdr)
अणु
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	u16 sc = le16_to_cpu(hdr->seq_ctl);
	अचिन्हित पूर्णांक seq = WLAN_GET_SEQ_SEQ(sc);
	काष्ठा ieee80211_frag_entry *entry;
	काष्ठा rtl_80211_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtl_80211_hdr_4addrqos *hdr_4addrqos;
	u8 tid;

	अगर (((fc & IEEE80211_FCTL_DSTODS) == IEEE80211_FCTL_DSTODS) && IEEE80211_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtl_80211_hdr_4addrqos *)hdr;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (IEEE80211_QOS_HAS_SEQ(fc)) अणु
		hdr_3addrqos = (काष्ठा rtl_80211_hdr_3addrqos *)hdr;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु
		tid = 0;
	पूर्ण

	entry = ieee80211_frag_cache_find(ieee, seq, -1, tid, hdr->addr2,
					  hdr->addr1);

	अगर (!entry) अणु
		IEEE80211_DEBUG_FRAG(
			"could not invalidate fragment cache "
			"entry (seq=%u)\n", seq);
		वापस -1;
	पूर्ण

	entry->skb = शून्य;
	वापस 0;
पूर्ण



/* ieee80211_rx_frame_mgपंचांगt
 *
 * Responsible क्रम handling management control frames
 *
 * Called by ieee80211_rx */
अटल अंतरभूत पूर्णांक
ieee80211_rx_frame_mgmt(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
			काष्ठा ieee80211_rx_stats *rx_stats, u16 type,
			u16 stype)
अणु
	/* On the काष्ठा stats definition there is written that
	 * this is not mandatory.... but seems that the probe
	 * response parser uses it
	 */
	काष्ठा rtl_80211_hdr_3addr *hdr = (काष्ठा rtl_80211_hdr_3addr *)skb->data;

	rx_stats->len = skb->len;
	ieee80211_rx_mgt(ieee, (काष्ठा rtl_80211_hdr_4addr *)skb->data, rx_stats);
	/* अगर ((ieee->state == IEEE80211_LINKED) && (स_भेद(hdr->addr3, ieee->current_network.bssid, ETH_ALEN))) */
	अगर ((स_भेद(hdr->addr1, ieee->dev->dev_addr, ETH_ALEN))) अणु
		/* use ADDR1 to perक्रमm address matching क्रम Management frames */
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	ieee80211_rx_frame_sofपंचांगac(ieee, skb, rx_stats, type, stype);

	dev_kमुक्त_skb_any(skb);

	वापस 0;

	#अगर_घोषित NOT_YET
	अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		netdev_dbg(ieee->dev, "Master mode not yet supported.\n");
		वापस 0;
/*
  hostap_update_sta_ps(ieee, (काष्ठा hostap_ieee80211_hdr_4addr *)
  skb->data);*/
	पूर्ण

	अगर (ieee->hostapd && type == IEEE80211_TYPE_MGMT) अणु
		अगर (stype == WLAN_FC_STYPE_BEACON &&
		    ieee->iw_mode == IW_MODE_MASTER) अणु
			काष्ठा sk_buff *skb2;
			/* Process beacon frames also in kernel driver to
			 * update STA(AP) table statistics */
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb2)
				hostap_rx(skb2->dev, skb2, rx_stats);
		पूर्ण

		/* send management frames to the user space daemon क्रम
		 * processing */
		ieee->apdevstats.rx_packets++;
		ieee->apdevstats.rx_bytes += skb->len;
		prism2_rx_80211(ieee->apdev, skb, rx_stats, PRISM2_RX_MGMT);
		वापस 0;
	पूर्ण

	    अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		अगर (type != WLAN_FC_TYPE_MGMT && type != WLAN_FC_TYPE_CTRL) अणु
			netdev_dbg(skb->dev, "unknown management frame "
			       "(type=0x%02x, stype=0x%02x) dropped\n",
			       type, stype);
			वापस -1;
		पूर्ण

		hostap_rx(skb->dev, skb, rx_stats);
		वापस 0;
	पूर्ण

	netdev_dbg(skb->dev, "hostap_rx_frame_mgmt: management frame "
	       "received in non-Host AP mode\n");
	वापस -1;
	#पूर्ण_अगर
पूर्ण



/* See IEEE 802.1H क्रम LLC/SNAP encapsulation/decapsulation */
/* Ethernet-II snap header (RFC1042 क्रम most EtherTypes) */
अटल अचिन्हित अक्षर rfc1042_header[] = अणु
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 पूर्ण;
/* Bridge-Tunnel header (क्रम EtherTypes ETH_P_AARP and ETH_P_IPX) */
अटल अचिन्हित अक्षर bridge_tunnel_header[] = अणु
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 पूर्ण;
/* No encapsulation header अगर EtherType < 0x600 (=length) */

/* Called by ieee80211_rx_frame_decrypt */
अटल पूर्णांक ieee80211_is_eapol_frame(काष्ठा ieee80211_device *ieee,
				    काष्ठा sk_buff *skb, माप_प्रकार hdrlen)
अणु
	काष्ठा net_device *dev = ieee->dev;
	u16 fc, ethertype;
	काष्ठा rtl_80211_hdr_4addr *hdr;
	u8 *pos;

	अगर (skb->len < 24)
		वापस 0;

	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	/* check that the frame is unicast frame to us */
	अगर ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
	    IEEE80211_FCTL_TODS &&
	    स_भेद(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0 &&
	    स_भेद(hdr->addr3, dev->dev_addr, ETH_ALEN) == 0) अणु
		/* ToDS frame with own addr BSSID and DA */
	पूर्ण अन्यथा अगर ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		   IEEE80211_FCTL_FROMDS &&
		   स_भेद(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0) अणु
		/* FromDS frame with own addr as DA */
	पूर्ण अन्यथा
		वापस 0;

	अगर (skb->len < 24 + 8)
		वापस 0;

	/* check क्रम port access entity Ethernet type */
//	pos = skb->data + 24;
	pos = skb->data + hdrlen;
	ethertype = (pos[6] << 8) | pos[7];
	अगर (ethertype == ETH_P_PAE)
		वापस 1;

	वापस 0;
पूर्ण

/* Called only as a tasklet (software IRQ), by ieee80211_rx */
अटल अंतरभूत पूर्णांक
ieee80211_rx_frame_decrypt(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_crypt_data *crypt)
अणु
	काष्ठा rtl_80211_hdr_4addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (!crypt || !crypt->ops->decrypt_mpdu)
		वापस 0;
	अगर (ieee->hwsec_active) अणु
		काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->bHwSec = 1;
	पूर्ण
	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	hdrlen = ieee80211_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	अगर (ieee->tkip_countermeasures &&
	    म_भेद(crypt->ops->name, "TKIP") == 0) अणु
		अगर (net_ratelimit()) अणु
			netdev_dbg(ieee->dev, "TKIP countermeasures: dropped "
			       "received packet from %pM\n",
			       hdr->addr2);
		पूर्ण
		वापस -1;
	पूर्ण

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		IEEE80211_DEBUG_DROP(
			"decryption failed (SA=%pM"
			") res=%d\n", hdr->addr2, res);
		अगर (res == -2)
			IEEE80211_DEBUG_DROP("Decryption failed ICV "
					     "mismatch (key %d)\n",
					     skb->data[hdrlen + 3] >> 6);
		ieee->ieee_stats.rx_discards_undecryptable++;
		वापस -1;
	पूर्ण

	वापस res;
पूर्ण


/* Called only as a tasklet (software IRQ), by ieee80211_rx */
अटल अंतरभूत पूर्णांक
ieee80211_rx_frame_decrypt_msdu(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
			     पूर्णांक keyidx, काष्ठा ieee80211_crypt_data *crypt)
अणु
	काष्ठा rtl_80211_hdr_4addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (!crypt || !crypt->ops->decrypt_msdu)
		वापस 0;
	अगर (ieee->hwsec_active) अणु
		काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->bHwSec = 1;
	पूर्ण

	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	hdrlen = ieee80211_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_msdu(skb, keyidx, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		netdev_dbg(ieee->dev, "MSDU decryption/MIC verification failed"
		       " (SA=%pM keyidx=%d)\n",
		       hdr->addr2, keyidx);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/* this function is stolen from ipw2200 driver*/
#घोषणा IEEE_PACKET_RETRY_TIME (5 * HZ)
अटल पूर्णांक is_duplicate_packet(काष्ठा ieee80211_device *ieee,
				      काष्ठा rtl_80211_hdr_4addr *header)
अणु
	u16 fc = le16_to_cpu(header->frame_ctl);
	u16 sc = le16_to_cpu(header->seq_ctl);
	u16 seq = WLAN_GET_SEQ_SEQ(sc);
	u16 frag = WLAN_GET_SEQ_FRAG(sc);
	u16 *last_seq, *last_frag;
	अचिन्हित दीर्घ *last_समय;
	काष्ठा rtl_80211_hdr_3addrqos *hdr_3addrqos;
	काष्ठा rtl_80211_hdr_4addrqos *hdr_4addrqos;
	u8 tid;


	//TO2DS and QoS
	अगर (((fc & IEEE80211_FCTL_DSTODS) == IEEE80211_FCTL_DSTODS) && IEEE80211_QOS_HAS_SEQ(fc)) अणु
		hdr_4addrqos = (काष्ठा rtl_80211_hdr_4addrqos *)header;
		tid = le16_to_cpu(hdr_4addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अगर (IEEE80211_QOS_HAS_SEQ(fc)) अणु //QoS
		hdr_3addrqos = (काष्ठा rtl_80211_hdr_3addrqos *)header;
		tid = le16_to_cpu(hdr_3addrqos->qos_ctl) & IEEE80211_QCTL_TID;
		tid = UP2AC(tid);
		tid++;
	पूर्ण अन्यथा अणु // no QoS
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
	//	अगर (स_भेद(entry->mac, mac, ETH_ALEN))अणु
		अगर (p == &ieee->ibss_mac_hash[index]) अणु
			entry = kदो_स्मृति(माप(काष्ठा ieee_ibss_seq), GFP_ATOMIC);
			अगर (!entry)
				वापस 0;
			स_नकल(entry->mac, mac, ETH_ALEN);
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

//	अगर(tid != 0) अणु
//		prपूर्णांकk(KERN_WARNING ":)))))))))))%x %x %x, fc(%x)\n", tid, *last_seq, seq, header->frame_ctl);
//	पूर्ण
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
//	BUG_ON(!(fc & IEEE80211_FCTL_RETRY));

	वापस 1;
पूर्ण

अटल bool AddReorderEntry(काष्ठा rx_ts_record *pTS, काष्ठा rx_reorder_entry *pReorderEntry)
अणु
	काष्ठा list_head *pList = &pTS->rx_pending_pkt_list;
	जबतक (pList->next != &pTS->rx_pending_pkt_list) अणु
		अगर (SN_LESS(pReorderEntry->SeqNum, list_entry(pList->next, काष्ठा rx_reorder_entry, List)->SeqNum))
			pList = pList->next;
		अन्यथा अगर (SN_EQUAL(pReorderEntry->SeqNum, list_entry(pList->next, काष्ठा rx_reorder_entry, List)->SeqNum))
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

अटल व्योम indicate_packets(काष्ठा ieee80211_device *ieee,
			     काष्ठा ieee80211_rxb *rxb)
अणु
	काष्ठा net_device_stats *stats = &ieee->stats;
	काष्ठा net_device *dev = ieee->dev;
	u16 ethertype;
	u8 i;

	क्रम (i = 0; i < rxb->nr_subframes; i++) अणु
		काष्ठा sk_buff *sub_skb = rxb->subframes[i];

		अगर (!sub_skb)
			जारी;

		/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
		ethertype = (sub_skb->data[6] << 8) | sub_skb->data[7];
		अगर (sub_skb->len >= 8 &&
		    ((!स_भेद(sub_skb->data, rfc1042_header, SNAP_SIZE) &&
			ethertype != ETH_P_AARP &&
			ethertype != ETH_P_IPX) ||
		     !स_भेद(sub_skb->data, bridge_tunnel_header, SNAP_SIZE))) अणु
			/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
			 * replace EtherType */
			skb_pull(sub_skb, SNAP_SIZE);
		पूर्ण अन्यथा अणु
			/* Leave Ethernet header part of hdr and full payload */
			put_unaligned_be16(sub_skb->len, skb_push(sub_skb, 2));
		पूर्ण
		स_नकल(skb_push(sub_skb, ETH_ALEN), rxb->src, ETH_ALEN);
		स_नकल(skb_push(sub_skb, ETH_ALEN), rxb->dst, ETH_ALEN);

		stats->rx_packets++;
		stats->rx_bytes += sub_skb->len;
		अगर (is_multicast_ether_addr(rxb->dst))
			stats->multicast++;

		/* Indicate the packets to upper layer */
		sub_skb->protocol = eth_type_trans(sub_skb, dev);
		स_रखो(sub_skb->cb, 0, माप(sub_skb->cb));
		sub_skb->dev = dev;
		/* 802.11 crc not sufficient */
		sub_skb->ip_summed = CHECKSUM_NONE;
		ieee->last_rx_ps_समय = jअगरfies;
		netअगर_rx(sub_skb);
	पूर्ण
पूर्ण

व्योम ieee80211_indicate_packets(काष्ठा ieee80211_device *ieee,
				काष्ठा ieee80211_rxb **prxbIndicateArray,
				u8 index)
अणु
	u8 i;

	क्रम (i = 0; i < index; i++) अणु
		काष्ठा ieee80211_rxb *prxb = prxbIndicateArray[i];

		indicate_packets(ieee, prxb);
		kमुक्त(prxb);
		prxb = शून्य;
	पूर्ण
पूर्ण

अटल व्योम RxReorderIndicatePacket(काष्ठा ieee80211_device *ieee,
				    काष्ठा ieee80211_rxb *prxb,
				    काष्ठा rx_ts_record *pTS, u16 SeqNum)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	काष्ठा rx_reorder_entry *pReorderEntry = शून्य;
	काष्ठा ieee80211_rxb **prxbIndicateArray;
	u8			WinSize = pHTInfo->RxReorderWinSize;
	u16			WinEnd = (pTS->rx_indicate_seq + WinSize - 1) % 4096;
	u8			index = 0;
	bool			bMatchWinStart = false, bPktInBuf = false;
	IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s(): Seq is %d,pTS->rx_indicate_seq is %d, WinSize is %d\n", __func__, SeqNum, pTS->rx_indicate_seq, WinSize);

	prxbIndicateArray = kदो_स्मृति_array(REORDER_WIN_SIZE,
					  माप(काष्ठा ieee80211_rxb *),
					  GFP_ATOMIC);
	अगर (!prxbIndicateArray)
		वापस;

	/* Rx Reorder initialize condition.*/
	अगर (pTS->rx_indicate_seq == 0xffff)
		pTS->rx_indicate_seq = SeqNum;

	/* Drop out the packet which SeqNum is smaller than WinStart */
	अगर (SN_LESS(SeqNum, pTS->rx_indicate_seq)) अणु
		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "Packet Drop! IndicateSeq: %d, NewSeq: %d\n",
				 pTS->rx_indicate_seq, SeqNum);
		pHTInfo->RxReorderDropCounter++;
		अणु
			पूर्णांक i;
			क्रम (i = 0; i < prxb->nr_subframes; i++)
				dev_kमुक्त_skb(prxb->subframes[i]);

			kमुक्त(prxb);
			prxb = शून्य;
		पूर्ण

		kमुक्त(prxbIndicateArray);
		वापस;
	पूर्ण

	/*
	 * Sliding winकरोw manipulation. Conditions includes:
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
			pTS->rx_indicate_seq = 4095 - (WinSize - (SeqNum + 1)) + 1;

		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "Window Shift! IndicateSeq: %d, NewSeq: %d\n", pTS->rx_indicate_seq, SeqNum);
	पूर्ण

	/*
	 * Indication process.
	 * After Packet dropping and Sliding Winकरोw shअगरting as above, we can now just indicate the packets
	 * with the SeqNum smaller than latest WinStart and buffer other packets.
	 */
	/* For Rx Reorder condition:
	 * 1. All packets with SeqNum smaller than WinStart => Indicate
	 * 2. All packets with SeqNum larger than or equal to WinStart => Buffer it.
	 */
	अगर (bMatchWinStart) अणु
		/* Current packet is going to be indicated.*/
		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "Packets indication!! IndicateSeq: %d, NewSeq: %d\n",\
				pTS->rx_indicate_seq, SeqNum);
		prxbIndicateArray[0] = prxb;
//		prपूर्णांकk("========================>%s(): SeqNum is %d\n",__func__,SeqNum);
		index = 1;
	पूर्ण अन्यथा अणु
		/* Current packet is going to be inserted पूर्णांकo pending list.*/
		//IEEE80211_DEBUG(IEEE80211_DL_REORDER,"%s(): We RX no ordered packed, insert to ordered list\n",__func__);
		अगर (!list_empty(&ieee->RxReorder_Unused_List)) अणु
			pReorderEntry = list_entry(ieee->RxReorder_Unused_List.next, काष्ठा rx_reorder_entry, List);
			list_del_init(&pReorderEntry->List);

			/* Make a reorder entry and insert पूर्णांकo a the packet list.*/
			pReorderEntry->SeqNum = SeqNum;
			pReorderEntry->prxb = prxb;
	//		IEEE80211_DEBUG(IEEE80211_DL_REORDER,"%s(): pREorderEntry->SeqNum is %d\n",__func__,pReorderEntry->SeqNum);

			अगर (!AddReorderEntry(pTS, pReorderEntry)) अणु
				IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s(): Duplicate packet is dropped!! IndicateSeq: %d, NewSeq: %d\n",
					__func__, pTS->rx_indicate_seq, SeqNum);
				list_add_tail(&pReorderEntry->List, &ieee->RxReorder_Unused_List);
				अणु
					पूर्णांक i;
					क्रम (i = 0; i < prxb->nr_subframes; i++)
						dev_kमुक्त_skb(prxb->subframes[i]);

					kमुक्त(prxb);
					prxb = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				IEEE80211_DEBUG(IEEE80211_DL_REORDER,
					 "Pkt insert into buffer!! IndicateSeq: %d, NewSeq: %d\n", pTS->rx_indicate_seq, SeqNum);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Packets are dropped अगर there is not enough reorder entries.
			 * This part shall be modअगरied!! We can just indicate all the
			 * packets in buffer and get reorder entries.
			 */
			IEEE80211_DEBUG(IEEE80211_DL_ERR, "RxReorderIndicatePacket(): There is no reorder entry!! Packet is dropped!!\n");
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
		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s(): start RREORDER indicate\n", __func__);
		pReorderEntry = list_entry(pTS->rx_pending_pkt_list.prev, काष्ठा rx_reorder_entry, List);
		अगर (SN_LESS(pReorderEntry->SeqNum, pTS->rx_indicate_seq) ||
		    SN_EQUAL(pReorderEntry->SeqNum, pTS->rx_indicate_seq)) अणु
			/* This protect buffer from overflow. */
			अगर (index >= REORDER_WIN_SIZE) अणु
				IEEE80211_DEBUG(IEEE80211_DL_ERR, "RxReorderIndicatePacket(): Buffer overflow!! \n");
				bPktInBuf = true;
				अवरोध;
			पूर्ण

			list_del_init(&pReorderEntry->List);

			अगर (SN_EQUAL(pReorderEntry->SeqNum, pTS->rx_indicate_seq))
				pTS->rx_indicate_seq = (pTS->rx_indicate_seq + 1) % 4096;

			IEEE80211_DEBUG(IEEE80211_DL_REORDER, "Packets indication!! IndicateSeq: %d, NewSeq: %d\n", pTS->rx_indicate_seq, SeqNum);
			prxbIndicateArray[index] = pReorderEntry->prxb;
		//	prपूर्णांकk("========================>%s(): pReorderEntry->SeqNum is %d\n",__func__,pReorderEntry->SeqNum);
			index++;

			list_add_tail(&pReorderEntry->List, &ieee->RxReorder_Unused_List);
		पूर्ण अन्यथा अणु
			bPktInBuf = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Handling pending समयr. Set this समयr to prevent from दीर्घ समय Rx buffering.*/
	अगर (index > 0) अणु
		// Cancel previous pending समयr.
	//	del_समयr_sync(&pTS->rx_pkt_pending_समयr);
		pTS->rx_समयout_indicate_seq = 0xffff;

		// Indicate packets
		अगर (index > REORDER_WIN_SIZE) अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR, "RxReorderIndicatePacket(): Rx Reorder buffer full!! \n");
			kमुक्त(prxbIndicateArray);
			वापस;
		पूर्ण
		ieee80211_indicate_packets(ieee, prxbIndicateArray, index);
	पूर्ण

	अगर (bPktInBuf && pTS->rx_समयout_indicate_seq == 0xffff) अणु
		// Set new pending समयr.
		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s(): SET rx timeout timer\n", __func__);
		pTS->rx_समयout_indicate_seq = pTS->rx_indicate_seq;
		अगर (समयr_pending(&pTS->rx_pkt_pending_समयr))
			del_समयr_sync(&pTS->rx_pkt_pending_समयr);
		pTS->rx_pkt_pending_समयr.expires = jअगरfies +
				msecs_to_jअगरfies(pHTInfo->RxReorderPendingTime);
		add_समयr(&pTS->rx_pkt_pending_समयr);
	पूर्ण

	kमुक्त(prxbIndicateArray);
पूर्ण

अटल u8 parse_subframe(काष्ठा ieee80211_device *ieee,
			 काष्ठा sk_buff *skb,
			 काष्ठा ieee80211_rx_stats *rx_stats,
			 काष्ठा ieee80211_rxb *rxb, u8 *src, u8 *dst)
अणु
	काष्ठा rtl_80211_hdr_3addr  *hdr = (काष्ठा rtl_80211_hdr_3addr *)skb->data;
	u16		fc = le16_to_cpu(hdr->frame_ctl);

	u16		LLCOffset = माप(काष्ठा rtl_80211_hdr_3addr);
	u16		ChkLength;
	bool		bIsAggregateFrame = false;
	u16		nSubframe_Length;
	u8		nPadding_Length = 0;
	u16		SeqNum = 0;

	काष्ठा sk_buff *sub_skb;
	/* just क्रम debug purpose */
	SeqNum = WLAN_GET_SEQ_SEQ(le16_to_cpu(hdr->seq_ctl));

	अगर ((IEEE80211_QOS_HAS_SEQ(fc)) && \
			(((frameqos *)(skb->data + IEEE80211_3ADDR_LEN))->field.reserved)) अणु
		bIsAggregateFrame = true;
	पूर्ण

	अगर (IEEE80211_QOS_HAS_SEQ(fc))
		LLCOffset += 2;

	अगर (rx_stats->bContainHTC)
		LLCOffset += HTCLNG;

	// Null packet, करोn't indicate it to upper layer
	ChkLength = LLCOffset;/* + (Frame_WEP(frame)!=0 ?Adapter->MgntInfo.SecurityInfo.EncryptionHeadOverhead:0);*/

	अगर (skb->len <= ChkLength)
		वापस 0;

	skb_pull(skb, LLCOffset);

	अगर (!bIsAggregateFrame) अणु
		rxb->nr_subframes = 1;
#अगर_घोषित JOHN_NOCPY
		rxb->subframes[0] = skb;
#अन्यथा
		rxb->subframes[0] = skb_copy(skb, GFP_ATOMIC);
#पूर्ण_अगर

		स_नकल(rxb->src, src, ETH_ALEN);
		स_नकल(rxb->dst, dst, ETH_ALEN);
		//IEEE80211_DEBUG_DATA(IEEE80211_DL_RX,skb->data,skb->len);
		वापस 1;
	पूर्ण अन्यथा अणु
		rxb->nr_subframes = 0;
		स_नकल(rxb->src, src, ETH_ALEN);
		स_नकल(rxb->dst, dst, ETH_ALEN);
		जबतक (skb->len > ETHERNET_HEADER_SIZE) अणु
			/* Offset 12 denote 2 mac address */
			nSubframe_Length = *((u16 *)(skb->data + 12));
			//==m==>change the length order
			nSubframe_Length = (nSubframe_Length >> 8) + (nSubframe_Length << 8);

			अगर (skb->len < (ETHERNET_HEADER_SIZE + nSubframe_Length)) अणु
				netdev_dbg(ieee->dev, "A-MSDU parse error!! pRfd->nTotalSubframe : %d\n",
					   rxb->nr_subframes);
				netdev_dbg(ieee->dev, "A-MSDU parse error!! Subframe Length: %d\n", nSubframe_Length);
				netdev_dbg(ieee->dev, "nRemain_Length is %d and nSubframe_Length is : %d\n", skb->len, nSubframe_Length);
				netdev_dbg(ieee->dev, "The Packet SeqNum is %d\n", SeqNum);
				वापस 0;
			पूर्ण

			/* move the data poपूर्णांक to data content */
			skb_pull(skb, ETHERNET_HEADER_SIZE);

#अगर_घोषित JOHN_NOCPY
			sub_skb = skb_clone(skb, GFP_ATOMIC);
			sub_skb->len = nSubframe_Length;
			sub_skb->tail = sub_skb->data + nSubframe_Length;
#अन्यथा
			/* Allocate new skb क्रम releasing to upper layer */
			sub_skb = dev_alloc_skb(nSubframe_Length + 12);
			अगर (!sub_skb)
				वापस 0;
			skb_reserve(sub_skb, 12);
			skb_put_data(sub_skb, skb->data, nSubframe_Length);
#पूर्ण_अगर
			rxb->subframes[rxb->nr_subframes++] = sub_skb;
			अगर (rxb->nr_subframes >= MAX_SUBFRAME_COUNT) अणु
				IEEE80211_DEBUG_RX("ParseSubframe(): Too many Subframes! Packets dropped!\n");
				अवरोध;
			पूर्ण
			skb_pull(skb, nSubframe_Length);

			अगर (skb->len != 0) अणु
				nPadding_Length = 4 - ((nSubframe_Length + ETHERNET_HEADER_SIZE) % 4);
				अगर (nPadding_Length == 4)
					nPadding_Length = 0;

				अगर (skb->len < nPadding_Length)
					वापस 0;

				skb_pull(skb, nPadding_Length);
			पूर्ण
		पूर्ण
#अगर_घोषित JOHN_NOCPY
		dev_kमुक्त_skb(skb);
#पूर्ण_अगर
		//अणुjust क्रम debug added by david
		//prपूर्णांकk("AMSDU::rxb->nr_subframes = %d\n",rxb->nr_subframes);
		//पूर्ण
		वापस rxb->nr_subframes;
	पूर्ण
पूर्ण

/* All received frames are sent to this function. @skb contains the frame in
 * IEEE 802.11 क्रमmat, i.e., in the क्रमmat it was sent over air.
 * This function is called only as a tasklet (software IRQ). */
पूर्णांक ieee80211_rx(काष्ठा ieee80211_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा ieee80211_rx_stats *rx_stats)
अणु
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा rtl_80211_hdr_4addr *hdr;
	//काष्ठा rtl_80211_hdr_3addrqos *hdr;

	माप_प्रकार hdrlen;
	u16 fc, type, stype, sc;
	काष्ठा net_device_stats *stats;
	अचिन्हित पूर्णांक frag;
	//added by amy क्रम reorder
	u8	TID = 0;
	u16	SeqNum = 0;
	काष्ठा rx_ts_record *pTS = शून्य;
	//bool bIsAggregateFrame = false;
	//added by amy क्रम reorder
#अगर_घोषित NOT_YET
	काष्ठा net_device *wds = शून्य;
	काष्ठा net_device *wds = शून्य;
	पूर्णांक from_assoc_ap = 0;
	व्योम *sta = शून्य;
#पूर्ण_अगर
//	u16 qos_ctl = 0;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	काष्ठा ieee80211_crypt_data *crypt = शून्य;
	पूर्णांक keyidx = 0;

	पूर्णांक i;
	काष्ठा ieee80211_rxb *rxb = शून्य;
	// cheat the hdr type
	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	stats = &ieee->stats;

	अगर (skb->len < 10) अणु
		netdev_info(dev, "SKB length < 10\n");
		जाओ rx_dropped;
	पूर्ण

	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);
	sc = le16_to_cpu(hdr->seq_ctl);

	frag = WLAN_GET_SEQ_FRAG(sc);
	hdrlen = ieee80211_get_hdrlen(fc);

	अगर (HTCCheck(ieee, skb->data)) अणु
		अगर (net_ratelimit())
			netdev_warn(dev, "find HTCControl\n");
		hdrlen += 4;
		rx_stats->bContainHTC = true;
	पूर्ण

	//IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, skb->data, skb->len);
#अगर_घोषित NOT_YET
	/* Put this code here so that we aव्योम duplicating it in all
	 * Rx paths. - Jean II */
#अगर_घोषित IW_WIRELESS_SPY		/* defined in iw_handler.h */
	/* If spy monitoring on */
	अगर (अगरace->spy_data.spy_number > 0) अणु
		काष्ठा iw_quality wstats;
		wstats.level = rx_stats->rssi;
		wstats.noise = rx_stats->noise;
		wstats.updated = 6;	/* No qual value */
		/* Update spy records */
		wireless_spy_update(dev, hdr->addr2, &wstats);
	पूर्ण
#पूर्ण_अगर /* IW_WIRELESS_SPY */
	hostap_update_rx_stats(local->ap, hdr, rx_stats);
#पूर्ण_अगर

	अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		ieee80211_monitor_rx(ieee, skb, rx_stats);
		stats->rx_packets++;
		stats->rx_bytes += skb->len;
		वापस 1;
	पूर्ण

	अगर (ieee->host_decrypt) अणु
		पूर्णांक idx = 0;
		अगर (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;
		crypt = ieee->crypt[idx];
#अगर_घोषित NOT_YET
		sta = शून्य;

		/* Use station specअगरic key to override शेष keys अगर the
		 * receiver address is a unicast address ("individual RA"). If
		 * bcrx_sta_key parameter is set, station specअगरic key is used
		 * even with broad/multicast tarमाला_लो (this is against IEEE
		 * 802.11, but makes it easier to use dअगरferent keys with
		 * stations that करो not support WEP key mapping). */

		अगर (!(hdr->addr1[0] & 0x01) || local->bcrx_sta_key)
			(व्योम)hostap_handle_sta_crypto(local, hdr, &crypt,
							&sta);
#पूर्ण_अगर

		/* allow शून्य decrypt to indicate an station specअगरic override
		 * क्रम शेष encryption */
		अगर (crypt && (!crypt->ops || !crypt->ops->decrypt_mpdu))
			crypt = शून्य;

		अगर (!crypt && (fc & IEEE80211_FCTL_WEP)) अणु
			/* This seems to be triggered by some (multicast?)
			 * frames from other than current BSS, so just drop the
			 * frames silently instead of filling प्रणाली log with
			 * these reports. */
			IEEE80211_DEBUG_DROP("Decryption failed (not set)"
					     " (SA=%pM)\n",
					     hdr->addr2);
			ieee->ieee_stats.rx_discards_undecryptable++;
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	अगर (skb->len < IEEE80211_DATA_HDR3_LEN)
		जाओ rx_dropped;

	// अगर QoS enabled, should check the sequence क्रम each of the AC
	अगर ((!ieee->pHTInfo->bCurRxReorderEnable) || !ieee->current_network.qos_data.active || !IsDataFrame(skb->data) || IsLegacyDataFrame(skb->data)) अणु
		अगर (is_duplicate_packet(ieee, hdr))
			जाओ rx_dropped;

	पूर्ण अन्यथा अणु
		काष्ठा rx_ts_record *pRxTS = शून्य;
			//IEEE80211_DEBUG(IEEE80211_DL_REORDER,"%s(): QOS ENABLE AND RECEIVE QOS DATA , we will get Ts, tid:%d\n",__func__, tid);
		अगर (GetTs(
				ieee,
				(काष्ठा ts_common_info **)&pRxTS,
				hdr->addr2,
				Frame_QoSTID((u8 *)(skb->data)),
				RX_सूची,
				true)) अणु

		//	IEEE80211_DEBUG(IEEE80211_DL_REORDER,"%s(): pRxTS->rx_last_frag_num is %d,frag is %d,pRxTS->rx_last_seq_num is %d,seq is %d\n",__func__,pRxTS->rx_last_frag_num,frag,pRxTS->rx_last_seq_num,WLAN_GET_SEQ_SEQ(sc));
			अगर ((fc & (1 << 11)) &&
			    (frag == pRxTS->rx_last_frag_num) &&
			    (WLAN_GET_SEQ_SEQ(sc) == pRxTS->rx_last_seq_num)) अणु
				जाओ rx_dropped;
			पूर्ण अन्यथा अणु
				pRxTS->rx_last_frag_num = frag;
				pRxTS->rx_last_seq_num = WLAN_GET_SEQ_SEQ(sc);
			पूर्ण
		पूर्ण अन्यथा अणु
			IEEE80211_DEBUG(IEEE80211_DL_ERR, "%s(): No TS!! Skip the check!!\n", __func__);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण
	अगर (type == IEEE80211_FTYPE_MGMT) अणु


	//IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, skb->data, skb->len);
		अगर (ieee80211_rx_frame_mgmt(ieee, skb, rx_stats, type, stype))
			जाओ rx_dropped;
		अन्यथा
			जाओ rx_निकास;
	पूर्ण

	/* Data frame - extract src/dst addresses */
	चयन (fc & (IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS)) अणु
	हाल IEEE80211_FCTL_FROMDS:
		स_नकल(dst, hdr->addr1, ETH_ALEN);
		स_नकल(src, hdr->addr3, ETH_ALEN);
		स_नकल(bssid, hdr->addr2, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_TODS:
		स_नकल(dst, hdr->addr3, ETH_ALEN);
		स_नकल(src, hdr->addr2, ETH_ALEN);
		स_नकल(bssid, hdr->addr1, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS:
		अगर (skb->len < IEEE80211_DATA_HDR4_LEN)
			जाओ rx_dropped;
		स_नकल(dst, hdr->addr3, ETH_ALEN);
		स_नकल(src, hdr->addr4, ETH_ALEN);
		स_नकल(bssid, ieee->current_network.bssid, ETH_ALEN);
		अवरोध;
	शेष:
		स_नकल(dst, hdr->addr1, ETH_ALEN);
		स_नकल(src, hdr->addr2, ETH_ALEN);
		स_नकल(bssid, hdr->addr3, ETH_ALEN);
		अवरोध;
	पूर्ण

#अगर_घोषित NOT_YET
	अगर (hostap_rx_frame_wds(ieee, hdr, fc, &wds))
		जाओ rx_dropped;
	अगर (wds) अणु
		skb->dev = dev = wds;
		stats = hostap_get_stats(dev);
	पूर्ण

	अगर (ieee->iw_mode == IW_MODE_MASTER && !wds &&
	    (fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) == IEEE80211_FCTL_FROMDS &&
	    ieee->stadev &&
	    स_भेद(hdr->addr2, ieee->assoc_ap_addr, ETH_ALEN) == 0) अणु
		/* Frame from BSSID of the AP क्रम which we are a client */
		skb->dev = dev = ieee->stadev;
		stats = hostap_get_stats(dev);
		from_assoc_ap = 1;
	पूर्ण

	अगर ((ieee->iw_mode == IW_MODE_MASTER ||
	     ieee->iw_mode == IW_MODE_REPEAT) &&
	    !from_assoc_ap) अणु
		चयन (hostap_handle_sta_rx(ieee, dev, skb, rx_stats,
					     wds)) अणु
		हाल AP_RX_CONTINUE_NOT_AUTHORIZED:
		हाल AP_RX_CONTINUE:
			अवरोध;
		हाल AP_RX_DROP:
			जाओ rx_dropped;
		हाल AP_RX_EXIT:
			जाओ rx_निकास;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	//IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, skb->data, skb->len);
	/* Nullfunc frames may have PS-bit set, so they must be passed to
	 * hostap_handle_sta_rx() beक्रमe being dropped here. */
	अगर (stype != IEEE80211_STYPE_DATA &&
	    stype != IEEE80211_STYPE_DATA_CFACK &&
	    stype != IEEE80211_STYPE_DATA_CFPOLL &&
	    stype != IEEE80211_STYPE_DATA_CFACKPOLL &&
	    stype != IEEE80211_STYPE_QOS_DATA//add by David,2006.8.4
	    ) अणु
		अगर (stype != IEEE80211_STYPE_शून्यFUNC)
			IEEE80211_DEBUG_DROP(
				"RX: dropped data frame "
				"with no data (type=0x%02x, "
				"subtype=0x%02x, len=%d)\n",
				type, stype, skb->len);
		जाओ rx_dropped;
	पूर्ण
	अगर (स_भेद(bssid, ieee->current_network.bssid, ETH_ALEN))
		जाओ rx_dropped;

	/* skb: hdr + (possibly fragmented, possibly encrypted) payload */

	अगर (ieee->host_decrypt && (fc & IEEE80211_FCTL_WEP) &&
	    (keyidx = ieee80211_rx_frame_decrypt(ieee, skb, crypt)) < 0) अणु
		netdev_dbg(ieee->dev, "decrypt frame error\n");
		जाओ rx_dropped;
	पूर्ण


	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;

	/* skb: hdr + (possibly fragmented) plaपूर्णांकext payload */
	// PR: FIXME: hostap has additional conditions in the "if" below:
	// ieee->host_decrypt && (fc & IEEE80211_FCTL_WEP) &&
	अगर ((frag != 0 || (fc & IEEE80211_FCTL_MOREFRAGS))) अणु
		पूर्णांक flen;
		काष्ठा sk_buff *frag_skb = ieee80211_frag_cache_get(ieee, hdr);
		IEEE80211_DEBUG_FRAG("Rx Fragment received (%u)\n", frag);

		अगर (!frag_skb) अणु
			IEEE80211_DEBUG(IEEE80211_DL_RX | IEEE80211_DL_FRAG,
					"Rx cannot get skb from fragment "
					"cache (morefrag=%d seq=%u frag=%u)\n",
					(fc & IEEE80211_FCTL_MOREFRAGS) != 0,
					WLAN_GET_SEQ_SEQ(sc), frag);
			जाओ rx_dropped;
		पूर्ण
		flen = skb->len;
		अगर (frag != 0)
			flen -= hdrlen;

		अगर (frag_skb->tail + flen > frag_skb->end) अणु
			netdev_warn(dev, "host decrypted and "
			       "reassembled frame did not fit skb\n");
			ieee80211_frag_cache_invalidate(ieee, hdr);
			जाओ rx_dropped;
		पूर्ण

		अगर (frag == 0) अणु
			/* copy first fragment (including full headers) पूर्णांकo
			 * beginning of the fragment cache skb */
			skb_put_data(frag_skb, skb->data, flen);
		पूर्ण अन्यथा अणु
			/* append frame payload to the end of the fragment
			 * cache skb */
			skb_put_data(frag_skb, skb->data + hdrlen, flen);
		पूर्ण
		dev_kमुक्त_skb_any(skb);
		skb = शून्य;

		अगर (fc & IEEE80211_FCTL_MOREFRAGS) अणु
			/* more fragments expected - leave the skb in fragment
			 * cache क्रम now; it will be delivered to upper layers
			 * after all fragments have been received */
			जाओ rx_निकास;
		पूर्ण

		/* this was the last fragment and the frame will be
		 * delivered, so हटाओ skb from fragment cache */
		skb = frag_skb;
		hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
		ieee80211_frag_cache_invalidate(ieee, hdr);
	पूर्ण

	/* skb: hdr + (possible reassembled) full MSDU payload; possibly still
	 * encrypted/authenticated */
	अगर (ieee->host_decrypt && (fc & IEEE80211_FCTL_WEP) &&
	    ieee80211_rx_frame_decrypt_msdu(ieee, skb, keyidx, crypt)) अणु
		netdev_dbg(ieee->dev, "==>decrypt msdu error\n");
		जाओ rx_dropped;
	पूर्ण

	//added by amy क्रम AP roaming
	ieee->LinkDetectInfo.NumRecvDataInPeriod++;
	ieee->LinkDetectInfo.NumRxOkInPeriod++;

	hdr = (काष्ठा rtl_80211_hdr_4addr *)skb->data;
	अगर (crypt && !(fc & IEEE80211_FCTL_WEP) && !ieee->खोलो_wep) अणु
		अगर (/*ieee->ieee802_1x &&*/
		    ieee80211_is_eapol_frame(ieee, skb, hdrlen)) अणु

#अगर_घोषित CONFIG_IEEE80211_DEBUG
			/* pass unencrypted EAPOL frames even अगर encryption is
			 * configured */
			काष्ठा eapol *eap = (काष्ठा eapol *)(skb->data +
				24);
			IEEE80211_DEBUG_EAP("RX: IEEE 802.1X EAPOL frame: %s\n",
						eap_get_type(eap->type));
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			IEEE80211_DEBUG_DROP(
				"encryption configured, but RX "
				"frame not encrypted (SA=%pM)\n",
				hdr->addr2);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_IEEE80211_DEBUG
	अगर (crypt && !(fc & IEEE80211_FCTL_WEP) &&
	    ieee80211_is_eapol_frame(ieee, skb, hdrlen)) अणु
		काष्ठा eapol *eap = (काष्ठा eapol *)(skb->data +
			24);
		IEEE80211_DEBUG_EAP("RX: IEEE 802.1X EAPOL frame: %s\n",
					eap_get_type(eap->type));
	पूर्ण
#पूर्ण_अगर

	अगर (crypt && !(fc & IEEE80211_FCTL_WEP) && !ieee->खोलो_wep &&
	    !ieee80211_is_eapol_frame(ieee, skb, hdrlen)) अणु
		IEEE80211_DEBUG_DROP(
			"dropped unencrypted RX data "
			"frame from %pM"
			" (drop_unencrypted=1)\n",
			hdr->addr2);
		जाओ rx_dropped;
	पूर्ण
/*
	अगर(ieee80211_is_eapol_frame(ieee, skb, hdrlen)) अणु
		prपूर्णांकk(KERN_WARNING "RX: IEEE802.1X EPAOL frame!\n");
	पूर्ण
*/
//added by amy क्रम reorder
	अगर (ieee->current_network.qos_data.active && IsQoSDataFrame(skb->data)
		&& !is_multicast_ether_addr(hdr->addr1)) अणु
		TID = Frame_QoSTID(skb->data);
		SeqNum = WLAN_GET_SEQ_SEQ(sc);
		GetTs(ieee, (काष्ठा ts_common_info **)&pTS, hdr->addr2, TID, RX_सूची, true);
		अगर (TID != 0 && TID != 3)
			ieee->bis_any_nonbepkts = true;
	पूर्ण
//added by amy क्रम reorder
	/* skb: hdr + (possible reassembled) full plaपूर्णांकext payload */
	//ethertype = (payload[6] << 8) | payload[7];
	rxb = kदो_स्मृति(माप(काष्ठा ieee80211_rxb), GFP_ATOMIC);
	अगर (!rxb)
		जाओ rx_dropped;
	/* to parse amsdu packets */
	/* qos data packets & reserved bit is 1 */
	अगर (parse_subframe(ieee, skb, rx_stats, rxb, src, dst) == 0) अणु
		/* only to मुक्त rxb, and not submit the packets to upper layer */
		क्रम (i = 0; i < rxb->nr_subframes; i++)
			dev_kमुक्त_skb(rxb->subframes[i]);

		kमुक्त(rxb);
		rxb = शून्य;
		जाओ rx_dropped;
	पूर्ण

//added by amy क्रम reorder
	अगर (!ieee->pHTInfo->bCurRxReorderEnable || !pTS) अणु
		indicate_packets(ieee, rxb);
		kमुक्त(rxb);
		rxb = शून्य;

	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG(IEEE80211_DL_REORDER, "%s(): REORDER ENABLE AND PTS not NULL, and we will enter RxReorderIndicatePacket()\n", __func__);
		RxReorderIndicatePacket(ieee, rxb, pTS, SeqNum);
	पूर्ण
#अगर_अघोषित JOHN_NOCPY
	dev_kमुक्त_skb(skb);
#पूर्ण_अगर

 rx_निकास:
#अगर_घोषित NOT_YET
	अगर (sta)
		hostap_handle_sta_release(sta);
#पूर्ण_अगर
	वापस 1;

 rx_dropped:
	kमुक्त(rxb);
	rxb = शून्य;
	stats->rx_dropped++;

	/* Returning 0 indicates to caller that we have not handled the SKB--
	 * so it is still allocated and can be used again by underlying
	 * hardware as a DMA target */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_rx);

#घोषणा MGMT_FRAME_FIXED_PART_LENGTH            0x24

अटल u8 qos_oui[QOS_OUI_LEN] = अणु 0x00, 0x50, 0xF2 पूर्ण;

/*
* Make the काष्ठाure we पढ़ो from the beacon packet to have
* the right values
*/
अटल पूर्णांक ieee80211_verअगरy_qos_info(काष्ठा ieee80211_qos_inक्रमmation_element
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


/*
 * Parse a QoS parameter element
 */
अटल पूर्णांक ieee80211_पढ़ो_qos_param_element(काष्ठा ieee80211_qos_parameter_info
					    *element_param, काष्ठा ieee80211_info_element
					    *info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा ieee80211_qos_parameter_info) - 2;

	अगर (!info_element || !element_param)
		वापस -1;

	अगर (info_element->id == QOS_ELEMENT_ID && info_element->len == size) अणु
		स_नकल(element_param->info_element.qui, info_element->data,
		       info_element->len);
		element_param->info_element.elementID = info_element->id;
		element_param->info_element.length = info_element->len;
	पूर्ण अन्यथा
		ret = -1;
	अगर (ret == 0)
		ret = ieee80211_verअगरy_qos_info(&element_param->info_element,
						QOS_OUI_PARAM_SUB_TYPE);
	वापस ret;
पूर्ण

/*
 * Parse a QoS inक्रमmation element
 */
अटल पूर्णांक ieee80211_पढ़ो_qos_info_element(
		काष्ठा ieee80211_qos_inक्रमmation_element *element_info,
		काष्ठा ieee80211_info_element *info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा ieee80211_qos_inक्रमmation_element) - 2;

	अगर (!element_info)
		वापस -1;
	अगर (!info_element)
		वापस -1;

	अगर ((info_element->id == QOS_ELEMENT_ID) && (info_element->len == size)) अणु
		स_नकल(element_info->qui, info_element->data,
		       info_element->len);
		element_info->elementID = info_element->id;
		element_info->length = info_element->len;
	पूर्ण अन्यथा
		ret = -1;

	अगर (ret == 0)
		ret = ieee80211_verअगरy_qos_info(element_info,
						QOS_OUI_INFO_SUB_TYPE);
	वापस ret;
पूर्ण


/*
 * Write QoS parameters from the ac parameters.
 */
अटल पूर्णांक ieee80211_qos_convert_ac_to_parameters(
		काष्ठा ieee80211_qos_parameter_info *param_elm,
		काष्ठा ieee80211_qos_parameters *qos_param)
अणु
	पूर्णांक i;
	काष्ठा ieee80211_qos_ac_parameter *ac_params;
	u8 aci;
	//u8 cw_min;
	//u8 cw_max;

	क्रम (i = 0; i < QOS_QUEUE_NUM; i++) अणु
		ac_params = &(param_elm->ac_params_record[i]);

		aci = (ac_params->aci_aअगरsn & 0x60) >> 5;

		अगर (aci >= QOS_QUEUE_NUM)
			जारी;
		qos_param->aअगरs[aci] = (ac_params->aci_aअगरsn) & 0x0f;

		/* WMM spec P.11: The minimum value क्रम AIFSN shall be 2 */
		qos_param->aअगरs[aci] = (qos_param->aअगरs[aci] < 2) ? 2 : qos_param->aअगरs[aci];

		qos_param->cw_min[aci] =
		    cpu_to_le16(ac_params->ecw_min_max & 0x0F);

		qos_param->cw_max[aci] =
		    cpu_to_le16((ac_params->ecw_min_max & 0xF0) >> 4);

		qos_param->flag[aci] =
		    (ac_params->aci_aअगरsn & 0x10) ? 0x01 : 0x00;
		qos_param->tx_op_limit[aci] = ac_params->tx_op_limit;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * we have a generic data element which it may contain QoS inक्रमmation or
 * parameters element. check the inक्रमmation element length to decide
 * which type to पढ़ो
 */
अटल पूर्णांक ieee80211_parse_qos_info_param_IE(काष्ठा ieee80211_info_element
					     *info_element,
					     काष्ठा ieee80211_network *network)
अणु
	पूर्णांक rc = 0;
	काष्ठा ieee80211_qos_parameters *qos_param = शून्य;
	काष्ठा ieee80211_qos_inक्रमmation_element qos_info_element;

	rc = ieee80211_पढ़ो_qos_info_element(&qos_info_element, info_element);

	अगर (rc == 0) अणु
		network->qos_data.param_count = qos_info_element.ac_info & 0x0F;
		network->flags |= NETWORK_HAS_QOS_INFORMATION;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_qos_parameter_info param_element;

		rc = ieee80211_पढ़ो_qos_param_element(&param_element,
						      info_element);
		अगर (rc == 0) अणु
			qos_param = &(network->qos_data.parameters);
			ieee80211_qos_convert_ac_to_parameters(&param_element,
							       qos_param);
			network->flags |= NETWORK_HAS_QOS_PARAMETERS;
			network->qos_data.param_count =
			    param_element.info_element.ac_info & 0x0F;
		पूर्ण
	पूर्ण

	अगर (rc == 0) अणु
		IEEE80211_DEBUG_QOS("QoS is supported\n");
		network->qos_data.supported = 1;
	पूर्ण
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_IEEE80211_DEBUG
#घोषणा MFIE_STRING(x) हाल MFIE_TYPE_ ##x: वापस #x

अटल स्थिर अक्षर *get_info_element_string(u16 id)
अणु
	चयन (id) अणु
		MFIE_STRING(SSID);
		MFIE_STRING(RATES);
		MFIE_STRING(FH_SET);
		MFIE_STRING(DS_SET);
		MFIE_STRING(CF_SET);
		MFIE_STRING(TIM);
		MFIE_STRING(IBSS_SET);
		MFIE_STRING(COUNTRY);
		MFIE_STRING(HOP_PARAMS);
		MFIE_STRING(HOP_TABLE);
		MFIE_STRING(REQUEST);
		MFIE_STRING(CHALLENGE);
		MFIE_STRING(POWER_CONSTRAINT);
		MFIE_STRING(POWER_CAPABILITY);
		MFIE_STRING(TPC_REQUEST);
		MFIE_STRING(TPC_REPORT);
		MFIE_STRING(SUPP_CHANNELS);
		MFIE_STRING(CSA);
		MFIE_STRING(MEASURE_REQUEST);
		MFIE_STRING(MEASURE_REPORT);
		MFIE_STRING(QUIET);
		MFIE_STRING(IBSS_DFS);
	       // MFIE_STRING(ERP_INFO);
		MFIE_STRING(RSN);
		MFIE_STRING(RATES_EX);
		MFIE_STRING(GENERIC);
		MFIE_STRING(QOS_PARAMETER);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ieee80211_extract_country_ie(
	काष्ठा ieee80211_device *ieee,
	काष्ठा ieee80211_info_element *info_element,
	काष्ठा ieee80211_network *network,
	u8 *addr2
)
अणु
	अगर (IS_DOT11D_ENABLE(ieee)) अणु
		अगर (info_element->len != 0) अणु
			स_नकल(network->CountryIeBuf, info_element->data, info_element->len);
			network->CountryIeLen = info_element->len;

			अगर (!IS_COUNTRY_IE_VALID(ieee)) अणु
				करोt11d_update_country_ie(ieee, addr2, info_element->len, info_element->data);
			पूर्ण
		पूर्ण

		//
		// 070305, rcnjko: I update country IE watch करोg here because
		// some AP (e.g. Cisco 1242) करोn't include country IE in their
		// probe response frame.
		//
		अगर (IS_EQUAL_CIE_SRC(ieee, addr2))
			UPDATE_CIE_WATCHDOG(ieee);
	पूर्ण
पूर्ण

पूर्णांक ieee80211_parse_info_param(काष्ठा ieee80211_device *ieee,
		काष्ठा ieee80211_info_element *info_element,
		u16 length,
		काष्ठा ieee80211_network *network,
		काष्ठा ieee80211_rx_stats *stats)
अणु
	u8 i;
	लघु offset;
	u16	पंचांगp_htcap_len = 0;
	u16	पंचांगp_htinfo_len = 0;
	u16 ht_realtek_agg_len = 0;
	u8  ht_realtek_agg_buf[MAX_IE_LEN];
//	u16 broadcom_len = 0;
#अगर_घोषित CONFIG_IEEE80211_DEBUG
	अक्षर rates_str[64];
	अक्षर *p;
#पूर्ण_अगर

	जबतक (length >= माप(*info_element)) अणु
		अगर (माप(*info_element) + info_element->len > length) अणु
			IEEE80211_DEBUG_MGMT("Info elem: parse failed: "
					     "info_element->len + 2 > left : "
					     "info_element->len+2=%zd left=%d, id=%d.\n",
					     info_element->len +
					     माप(*info_element),
					     length, info_element->id);
			/* We stop processing but करोn't वापस an error here
			 * because some misbehaviour APs अवरोध this rule. ie.
			 * Orinoco AP1000. */
			अवरोध;
		पूर्ण

		चयन (info_element->id) अणु
		हाल MFIE_TYPE_SSID:
			अगर (ieee80211_is_empty_essid(info_element->data,
						     info_element->len)) अणु
				network->flags |= NETWORK_EMPTY_ESSID;
				अवरोध;
			पूर्ण

			network->ssid_len = min(info_element->len,
						(u8)IW_ESSID_MAX_SIZE);
			स_नकल(network->ssid, info_element->data, network->ssid_len);
			अगर (network->ssid_len < IW_ESSID_MAX_SIZE)
				स_रखो(network->ssid + network->ssid_len, 0,
				       IW_ESSID_MAX_SIZE - network->ssid_len);

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_SSID: '%s' len=%d.\n",
					     network->ssid, network->ssid_len);
			अवरोध;

		हाल MFIE_TYPE_RATES:
#अगर_घोषित CONFIG_IEEE80211_DEBUG
			p = rates_str;
#पूर्ण_अगर
			network->rates_len = min(info_element->len,
						 MAX_RATES_LENGTH);
			क्रम (i = 0; i < network->rates_len; i++) अणु
				network->rates[i] = info_element->data[i];
#अगर_घोषित CONFIG_IEEE80211_DEBUG
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates[i]);
#पूर्ण_अगर
				अगर (ieee80211_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    IEEE80211_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RATES: '%s' (%d)\n",
					     rates_str, network->rates_len);
			अवरोध;

		हाल MFIE_TYPE_RATES_EX:
#अगर_घोषित CONFIG_IEEE80211_DEBUG
			p = rates_str;
#पूर्ण_अगर
			network->rates_ex_len = min(info_element->len,
						    MAX_RATES_EX_LENGTH);
			क्रम (i = 0; i < network->rates_ex_len; i++) अणु
				network->rates_ex[i] = info_element->data[i];
#अगर_घोषित CONFIG_IEEE80211_DEBUG
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates_ex[i]);
#पूर्ण_अगर
				अगर (ieee80211_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    IEEE80211_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RATES_EX: '%s' (%d)\n",
					     rates_str, network->rates_ex_len);
			अवरोध;

		हाल MFIE_TYPE_DS_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_DS_SET: %d\n",
					     info_element->data[0]);
			network->channel = info_element->data[0];
			अवरोध;

		हाल MFIE_TYPE_FH_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_FH_SET: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_CF_SET:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_CF_SET: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_TIM:
			अगर (info_element->len < 4)
				अवरोध;

			network->tim.tim_count = info_element->data[0];
			network->tim.tim_period = info_element->data[1];

			network->dtim_period = info_element->data[1];
			अगर (ieee->state != IEEE80211_LINKED)
				अवरोध;

			network->last_dtim_sta_समय[0] = stats->mac_समय[0];
			network->last_dtim_sta_समय[1] = stats->mac_समय[1];

			network->dtim_data = IEEE80211_DTIM_VALID;

			अगर (info_element->data[0] != 0)
				अवरोध;

			अगर (info_element->data[2] & 1)
				network->dtim_data |= IEEE80211_DTIM_MBCAST;

			offset = (info_element->data[2] >> 1) * 2;

			अगर (ieee->assoc_id < 8 * offset ||
				ieee->assoc_id > 8 * (offset + info_element->len - 3))

				अवरोध;

			offset = (ieee->assoc_id / 8) - offset;// + ((aid % 8)? 0 : 1) ;

			अगर (info_element->data[3 + offset] & (1 << (ieee->assoc_id % 8)))
				network->dtim_data |= IEEE80211_DTIM_UCAST;

			//IEEE80211_DEBUG_MGMT("MFIE_TYPE_TIM: partially ignored\n");
			अवरोध;

		हाल MFIE_TYPE_ERP:
			network->erp_value = info_element->data[0];
			network->flags |= NETWORK_HAS_ERP_VALUE;
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_ERP_SET: %d\n",
					     network->erp_value);
			अवरोध;
		हाल MFIE_TYPE_IBSS_SET:
			network->atim_winकरोw = info_element->data[0];
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_IBSS_SET: %d\n",
					     network->atim_winकरोw);
			अवरोध;

		हाल MFIE_TYPE_CHALLENGE:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_CHALLENGE: ignored\n");
			अवरोध;

		हाल MFIE_TYPE_GENERIC:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_GENERIC: %d bytes\n",
					     info_element->len);
			अगर (!ieee80211_parse_qos_info_param_IE(info_element,
							       network))
				अवरोध;

			अगर (info_element->len >= 4 &&
			    info_element->data[0] == 0x00 &&
			    info_element->data[1] == 0x50 &&
			    info_element->data[2] == 0xf2 &&
			    info_element->data[3] == 0x01) अणु
				network->wpa_ie_len = min(info_element->len + 2,
							  MAX_WPA_IE_LEN);
				स_नकल(network->wpa_ie, info_element,
				       network->wpa_ie_len);
				अवरोध;
			पूर्ण

#अगर_घोषित THOMAS_TURBO
			अगर (info_element->len == 7 &&
			    info_element->data[0] == 0x00 &&
			    info_element->data[1] == 0xe0 &&
			    info_element->data[2] == 0x4c &&
			    info_element->data[3] == 0x01 &&
			    info_element->data[4] == 0x02) अणु
				network->Turbo_Enable = 1;
			पूर्ण
#पूर्ण_अगर

			//क्रम HTcap and HTinfo parameters
			अगर (पंचांगp_htcap_len == 0) अणु
				अगर (info_element->len >= 4 &&
				   info_element->data[0] == 0x00 &&
				   info_element->data[1] == 0x90 &&
				   info_element->data[2] == 0x4c &&
				   info_element->data[3] == 0x033)अणु

					पंचांगp_htcap_len = min(info_element->len, (u8)MAX_IE_LEN);
					अगर (पंचांगp_htcap_len != 0) अणु
						network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
						network->bssht.bdHTCapLen = पंचांगp_htcap_len > माप(network->bssht.bdHTCapBuf) ? \
							माप(network->bssht.bdHTCapBuf) : पंचांगp_htcap_len;
						स_नकल(network->bssht.bdHTCapBuf, info_element->data, network->bssht.bdHTCapLen);
					पूर्ण
				पूर्ण
				अगर (पंचांगp_htcap_len != 0)
					network->bssht.bdSupportHT = true;
				अन्यथा
					network->bssht.bdSupportHT = false;
			पूर्ण


			अगर (पंचांगp_htinfo_len == 0) अणु
				अगर (info_element->len >= 4 &&
					info_element->data[0] == 0x00 &&
					info_element->data[1] == 0x90 &&
					info_element->data[2] == 0x4c &&
					info_element->data[3] == 0x034)अणु

					पंचांगp_htinfo_len = min(info_element->len, (u8)MAX_IE_LEN);
					अगर (पंचांगp_htinfo_len != 0) अणु
						network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
						अगर (पंचांगp_htinfo_len) अणु
							network->bssht.bdHTInfoLen = पंचांगp_htinfo_len > माप(network->bssht.bdHTInfoBuf) ? \
								माप(network->bssht.bdHTInfoBuf) : पंचांगp_htinfo_len;
							स_नकल(network->bssht.bdHTInfoBuf, info_element->data, network->bssht.bdHTInfoLen);
						पूर्ण

					पूर्ण

				पूर्ण
			पूर्ण

			अगर (ieee->aggregation) अणु
				अगर (network->bssht.bdSupportHT) अणु
					अगर (info_element->len >= 4 &&
						info_element->data[0] == 0x00 &&
						info_element->data[1] == 0xe0 &&
						info_element->data[2] == 0x4c &&
						info_element->data[3] == 0x02)अणु

						ht_realtek_agg_len = min(info_element->len, (u8)MAX_IE_LEN);
						स_नकल(ht_realtek_agg_buf, info_element->data, info_element->len);

					पूर्ण
					अगर (ht_realtek_agg_len >= 5) अणु
						network->bssht.bdRT2RTAggregation = true;

						अगर ((ht_realtek_agg_buf[4] == 1) && (ht_realtek_agg_buf[5] & 0x02))
							network->bssht.bdRT2RTLongSlotTime = true;
					पूर्ण
				पूर्ण

			पूर्ण

			//अगर(पंचांगp_htcap_len !=0  ||  पंचांगp_htinfo_len != 0)
			अणु
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
					 info_element->data[2] == 0x18))अणु

					network->broadcom_cap_exist = true;

				पूर्ण
			पूर्ण
			अगर (info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x0c &&
				info_element->data[2] == 0x43) अणु
				network->ralink_cap_exist = true;
			पूर्ण अन्यथा
				network->ralink_cap_exist = false;
			//added by amy क्रम atheros AP
			अगर ((info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x03 &&
				info_element->data[2] == 0x7f) ||
				(info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x13 &&
				info_element->data[2] == 0x74)) अणु
				netdev_dbg(ieee->dev, "========> athros AP is exist\n");
				network->atheros_cap_exist = true;
			पूर्ण अन्यथा
				network->atheros_cap_exist = false;

			अगर (info_element->len >= 3 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x40 &&
				info_element->data[2] == 0x96) अणु
				network->cisco_cap_exist = true;
			पूर्ण अन्यथा
				network->cisco_cap_exist = false;
			//added by amy क्रम LEAP of cisco
			अगर (info_element->len > 4 &&
				info_element->data[0] == 0x00 &&
				info_element->data[1] == 0x40 &&
				info_element->data[2] == 0x96 &&
				info_element->data[3] == 0x01) अणु
				अगर (info_element->len == 6) अणु
					स_नकल(network->CcxRmState, &info_element[4], 2);
					अगर (network->CcxRmState[0] != 0)
						network->bCcxRmEnable = true;
					अन्यथा
						network->bCcxRmEnable = false;
					//
					// CCXv4 Table 59-1 MBSSID Masks.
					//
					network->MBssidMask = network->CcxRmState[1] & 0x07;
					अगर (network->MBssidMask != 0) अणु
						network->bMBssidValid = true;
						network->MBssidMask = 0xff << (network->MBssidMask);
						ether_addr_copy(network->MBssid, network->bssid);
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
			अवरोध;

		हाल MFIE_TYPE_RSN:
			IEEE80211_DEBUG_MGMT("MFIE_TYPE_RSN: %d bytes\n",
					     info_element->len);
			network->rsn_ie_len = min(info_element->len + 2,
						  MAX_WPA_IE_LEN);
			स_नकल(network->rsn_ie, info_element,
			       network->rsn_ie_len);
			अवरोध;

			//HT related element.
		हाल MFIE_TYPE_HT_CAP:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_HT_CAP: %d bytes\n",
					     info_element->len);
			पंचांगp_htcap_len = min(info_element->len, (u8)MAX_IE_LEN);
			अगर (पंचांगp_htcap_len != 0) अणु
				network->bssht.bdHTSpecVer = HT_SPEC_VER_EWC;
				network->bssht.bdHTCapLen = पंचांगp_htcap_len > माप(network->bssht.bdHTCapBuf) ? \
					माप(network->bssht.bdHTCapBuf) : पंचांगp_htcap_len;
				स_नकल(network->bssht.bdHTCapBuf, info_element->data, network->bssht.bdHTCapLen);

				//If peer is HT, but not WMM, call QosSetLegacyWMMParamWithHT()
				// winकरोws driver will update WMM parameters each beacon received once connected
				// Linux driver is a bit dअगरferent.
				network->bssht.bdSupportHT = true;
			पूर्ण अन्यथा
				network->bssht.bdSupportHT = false;
			अवरोध;


		हाल MFIE_TYPE_HT_INFO:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_HT_INFO: %d bytes\n",
					     info_element->len);
			पंचांगp_htinfo_len = min(info_element->len, (u8)MAX_IE_LEN);
			अगर (पंचांगp_htinfo_len) अणु
				network->bssht.bdHTSpecVer = HT_SPEC_VER_IEEE;
				network->bssht.bdHTInfoLen = पंचांगp_htinfo_len > माप(network->bssht.bdHTInfoBuf) ? \
					माप(network->bssht.bdHTInfoBuf) : पंचांगp_htinfo_len;
				स_नकल(network->bssht.bdHTInfoBuf, info_element->data, network->bssht.bdHTInfoLen);
			पूर्ण
			अवरोध;

		हाल MFIE_TYPE_AIRONET:
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_AIRONET: %d bytes\n",
					     info_element->len);
			अगर (info_element->len > IE_CISCO_FLAG_POSITION) अणु
				network->bWithAironetIE = true;

				// CCX 1 spec v1.13, A01.1 CKIP Negotiation (page23):
				// "A Cisco access poपूर्णांक advertises support क्रम CKIP in beacon and probe response packets,
				//  by adding an Aironet element and setting one or both of the CKIP negotiation bits."
				अगर ((info_element->data[IE_CISCO_FLAG_POSITION] & SUPPORT_CKIP_MIC)	||
					(info_element->data[IE_CISCO_FLAG_POSITION] & SUPPORT_CKIP_PK)) अणु
					network->bCkipSupported = true;
				पूर्ण अन्यथा अणु
					network->bCkipSupported = false;
				पूर्ण
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
			IEEE80211_DEBUG_SCAN("MFIE_TYPE_COUNTRY: %d bytes\n",
					     info_element->len);
			ieee80211_extract_country_ie(ieee, info_element, network, network->bssid);//addr2 is same as addr3 when from an AP
			अवरोध;
/* TODO */
		शेष:
			IEEE80211_DEBUG_MGMT
			    ("Unsupported info element: %s (%d)\n",
			     get_info_element_string(info_element->id),
			     info_element->id);
			अवरोध;
		पूर्ण

		length -= माप(*info_element) + info_element->len;
		info_element =
		    (काष्ठा ieee80211_info_element *)&info_element->
		    data[info_element->len];
	पूर्ण

	अगर (!network->atheros_cap_exist && !network->broadcom_cap_exist &&
		!network->cisco_cap_exist && !network->ralink_cap_exist && !network->bssht.bdRT2RTAggregation) अणु
		network->unknown_cap_exist = true;
	पूर्ण अन्यथा अणु
		network->unknown_cap_exist = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u8 ieee80211_SignalStrengthTranslate(
	u8  CurrSS
	)
अणु
	u8 RetSS;

	// Step 1. Scale mapping.
	अगर (CurrSS >= 71 && CurrSS <= 100) अणु
		RetSS = 90 + ((CurrSS - 70) / 3);
	पूर्ण अन्यथा अगर (CurrSS >= 41 && CurrSS <= 70) अणु
		RetSS = 78 + ((CurrSS - 40) / 3);
	पूर्ण अन्यथा अगर (CurrSS >= 31 && CurrSS <= 40) अणु
		RetSS = 66 + (CurrSS - 30);
	पूर्ण अन्यथा अगर (CurrSS >= 21 && CurrSS <= 30) अणु
		RetSS = 54 + (CurrSS - 20);
	पूर्ण अन्यथा अगर (CurrSS >= 5 && CurrSS <= 20) अणु
		RetSS = 42 + (((CurrSS - 5) * 2) / 3);
	पूर्ण अन्यथा अगर (CurrSS == 4) अणु
		RetSS = 36;
	पूर्ण अन्यथा अगर (CurrSS == 3) अणु
		RetSS = 27;
	पूर्ण अन्यथा अगर (CurrSS == 2) अणु
		RetSS = 18;
	पूर्ण अन्यथा अगर (CurrSS == 1) अणु
		RetSS = 9;
	पूर्ण अन्यथा अणु
		RetSS = CurrSS;
	पूर्ण
	//RT_TRACE(COMP_DBG, DBG_LOUD, ("##### After Mapping:  LastSS: %d, CurrSS: %d, RetSS: %d\n", LastSS, CurrSS, RetSS));

	// Step 2. Smoothing.

	//RT_TRACE(COMP_DBG, DBG_LOUD, ("$$$$$ After Smoothing:  LastSS: %d, CurrSS: %d, RetSS: %d\n", LastSS, CurrSS, RetSS));

	वापस RetSS;
पूर्ण

/* 0-100 index */
अटल दीर्घ ieee80211_translate_todbm(u8 संकेत_strength_index)
अणु
	दीर्घ	संकेत_घातer; // in dBm.

	// Translate to dBm (x=0.5y-95).
	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;

	वापस संकेत_घातer;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_network_init(
	काष्ठा ieee80211_device *ieee,
	काष्ठा ieee80211_probe_response *beacon,
	काष्ठा ieee80211_network *network,
	काष्ठा ieee80211_rx_stats *stats)
अणु
#अगर_घोषित CONFIG_IEEE80211_DEBUG
	//अक्षर rates_str[64];
	//अक्षर *p;
#पूर्ण_अगर

	network->qos_data.active = 0;
	network->qos_data.supported = 0;
	network->qos_data.param_count = 0;
	network->qos_data.old_param_count = 0;

	/* Pull out fixed field data */
	स_नकल(network->bssid, beacon->header.addr3, ETH_ALEN);
	network->capability = le16_to_cpu(beacon->capability);
	network->last_scanned = jअगरfies;
	network->समय_stamp[0] = le32_to_cpu(beacon->समय_stamp[0]);
	network->समय_stamp[1] = le32_to_cpu(beacon->समय_stamp[1]);
	network->beacon_पूर्णांकerval = le16_to_cpu(beacon->beacon_पूर्णांकerval);
	/* Where to pull this? beacon->listen_पूर्णांकerval;*/
	network->listen_पूर्णांकerval = 0x0A;
	network->rates_len = network->rates_ex_len = 0;
	network->last_associate = 0;
	network->ssid_len = 0;
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
#अगर_घोषित THOMAS_TURBO
	network->Turbo_Enable = 0;
#पूर्ण_अगर
	network->CountryIeLen = 0;
	स_रखो(network->CountryIeBuf, 0, MAX_IE_LEN);
//Initialize HT parameters
	//ieee80211_ht_initialize(&network->bssht);
	HTInitializeBssDesc(&network->bssht);
	अगर (stats->freq == IEEE80211_52GHZ_BAND) अणु
		/* क्रम A band (No DS info) */
		network->channel = stats->received_channel;
	पूर्ण अन्यथा
		network->flags |= NETWORK_HAS_CCK;

	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;

	अगर (ieee80211_parse_info_param
	    (ieee, beacon->info_element, stats->len - माप(*beacon), network, stats))
		वापस 1;

	network->mode = 0;
	अगर (stats->freq == IEEE80211_52GHZ_BAND)
		network->mode = IEEE_A;
	अन्यथा अणु
		अगर (network->flags & NETWORK_HAS_OFDM)
			network->mode |= IEEE_G;
		अगर (network->flags & NETWORK_HAS_CCK)
			network->mode |= IEEE_B;
	पूर्ण

	अगर (network->mode == 0) अणु
		IEEE80211_DEBUG_SCAN("Filtered out '%s (%pM)' "
				     "network.\n",
				     escape_essid(network->ssid,
						  network->ssid_len),
				     network->bssid);
		वापस 1;
	पूर्ण

	अगर (network->bssht.bdSupportHT) अणु
		अगर (network->mode == IEEE_A)
			network->mode = IEEE_N_5G;
		अन्यथा अगर (network->mode & (IEEE_G | IEEE_B))
			network->mode = IEEE_N_24G;
	पूर्ण
	अगर (ieee80211_is_empty_essid(network->ssid, network->ssid_len))
		network->flags |= NETWORK_EMPTY_ESSID;

	stats->संकेत = 30 + (stats->SignalStrength * 70) / 100;
	//stats->संकेत = ieee80211_SignalStrengthTranslate(stats->संकेत);
	stats->noise = ieee80211_translate_todbm((u8)(100 - stats->संकेत)) - 25;

	स_नकल(&network->stats, stats, माप(network->stats));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_same_network(काष्ठा ieee80211_network *src,
				  काष्ठा ieee80211_network *dst, काष्ठा ieee80211_device *ieee)
अणु
	/* A network is only a duplicate अगर the channel, BSSID, ESSID
	 * and the capability field (in particular IBSS and BSS) all match.
	 * We treat all <hidden> with the same BSSID and channel
	 * as one network */
	वापस //((src->ssid_len == dst->ssid_len) &&
		(((src->ssid_len == dst->ssid_len) || (ieee->iw_mode == IW_MODE_INFRA)) &&
		(src->channel == dst->channel) &&
		!स_भेद(src->bssid, dst->bssid, ETH_ALEN) &&
		//!स_भेद(src->ssid, dst->ssid, src->ssid_len) &&
		(!स_भेद(src->ssid, dst->ssid, src->ssid_len) || (ieee->iw_mode == IW_MODE_INFRA)) &&
		((src->capability & WLAN_CAPABILITY_IBSS) ==
		(dst->capability & WLAN_CAPABILITY_IBSS)) &&
		((src->capability & WLAN_CAPABILITY_BSS) ==
		(dst->capability & WLAN_CAPABILITY_BSS)));
पूर्ण

अटल अंतरभूत व्योम update_network(काष्ठा ieee80211_network *dst,
				  काष्ठा ieee80211_network *src)
अणु
	पूर्णांक qos_active;
	u8 old_param;

	स_नकल(&dst->stats, &src->stats, माप(काष्ठा ieee80211_rx_stats));
	dst->capability = src->capability;
	स_नकल(dst->rates, src->rates, src->rates_len);
	dst->rates_len = src->rates_len;
	स_नकल(dst->rates_ex, src->rates_ex, src->rates_ex_len);
	dst->rates_ex_len = src->rates_ex_len;
	अगर (src->ssid_len > 0) अणु
		स_रखो(dst->ssid, 0, dst->ssid_len);
		dst->ssid_len = src->ssid_len;
		स_नकल(dst->ssid, src->ssid, src->ssid_len);
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
	dst->last_dtim_sta_समय[0] = src->last_dtim_sta_समय[0];
	dst->last_dtim_sta_समय[1] = src->last_dtim_sta_समय[1];
	स_नकल(&dst->tim, &src->tim, माप(काष्ठा ieee80211_tim_parameters));

	dst->bssht.bdSupportHT = src->bssht.bdSupportHT;
	dst->bssht.bdRT2RTAggregation = src->bssht.bdRT2RTAggregation;
	dst->bssht.bdHTCapLen = src->bssht.bdHTCapLen;
	स_नकल(dst->bssht.bdHTCapBuf, src->bssht.bdHTCapBuf, src->bssht.bdHTCapLen);
	dst->bssht.bdHTInfoLen = src->bssht.bdHTInfoLen;
	स_नकल(dst->bssht.bdHTInfoBuf, src->bssht.bdHTInfoBuf, src->bssht.bdHTInfoLen);
	dst->bssht.bdHTSpecVer = src->bssht.bdHTSpecVer;
	dst->bssht.bdRT2RTLongSlotTime = src->bssht.bdRT2RTLongSlotTime;
	dst->broadcom_cap_exist = src->broadcom_cap_exist;
	dst->ralink_cap_exist = src->ralink_cap_exist;
	dst->atheros_cap_exist = src->atheros_cap_exist;
	dst->cisco_cap_exist = src->cisco_cap_exist;
	dst->unknown_cap_exist = src->unknown_cap_exist;
	स_नकल(dst->wpa_ie, src->wpa_ie, src->wpa_ie_len);
	dst->wpa_ie_len = src->wpa_ie_len;
	स_नकल(dst->rsn_ie, src->rsn_ie, src->rsn_ie_len);
	dst->rsn_ie_len = src->rsn_ie_len;

	dst->last_scanned = jअगरfies;
	/* qos related parameters */
	//qos_active = src->qos_data.active;
	qos_active = dst->qos_data.active;
	//old_param = dst->qos_data.old_param_count;
	old_param = dst->qos_data.param_count;
	अगर (dst->flags & NETWORK_HAS_QOS_MASK)
		स_नकल(&dst->qos_data, &src->qos_data,
			माप(काष्ठा ieee80211_qos_data));
	अन्यथा अणु
		dst->qos_data.supported = src->qos_data.supported;
		dst->qos_data.param_count = src->qos_data.param_count;
	पूर्ण

	अगर (dst->qos_data.supported == 1) अणु
		dst->QoS_Enable = 1;
		अगर (dst->ssid_len)
			IEEE80211_DEBUG_QOS
				("QoS the network %s is QoS supported\n",
				dst->ssid);
		अन्यथा
			IEEE80211_DEBUG_QOS
				("QoS the network is QoS supported\n");
	पूर्ण
	dst->qos_data.active = qos_active;
	dst->qos_data.old_param_count = old_param;

	/* dst->last_associate is not overwritten */
	dst->wmm_info = src->wmm_info; //sure to exist in beacon or probe response frame.
	अगर (src->wmm_param[0].aci_aअगरsn || \
	   src->wmm_param[1].aci_aअगरsn || \
	   src->wmm_param[2].aci_aअगरsn || \
	   src->wmm_param[3].aci_aअगरsn) अणु
		स_नकल(dst->wmm_param, src->wmm_param, WME_AC_PRAM_LEN);
	पूर्ण
	//dst->QoS_Enable = src->QoS_Enable;
#अगर_घोषित THOMAS_TURBO
	dst->Turbo_Enable = src->Turbo_Enable;
#पूर्ण_अगर

	dst->CountryIeLen = src->CountryIeLen;
	स_नकल(dst->CountryIeBuf, src->CountryIeBuf, src->CountryIeLen);

	//added by amy क्रम LEAP
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

अटल अंतरभूत पूर्णांक is_beacon(__le16 fc)
अणु
	वापस (WLAN_FC_GET_STYPE(le16_to_cpu(fc)) == IEEE80211_STYPE_BEACON);
पूर्ण

अटल अंतरभूत व्योम ieee80211_process_probe_response(
	काष्ठा ieee80211_device *ieee,
	काष्ठा ieee80211_probe_response *beacon,
	काष्ठा ieee80211_rx_stats *stats)
अणु
	काष्ठा ieee80211_network *network;
	काष्ठा ieee80211_network *target;
	काष्ठा ieee80211_network *oldest = शून्य;
#अगर_घोषित CONFIG_IEEE80211_DEBUG
	काष्ठा ieee80211_info_element *info_element = &beacon->info_element[0];
#पूर्ण_अगर
	पूर्णांक fc = WLAN_FC_GET_STYPE(le16_to_cpu(beacon->header.frame_ctl));
	अचिन्हित दीर्घ flags;
	लघु renew;
	u16 capability;
	//u8 wmm_info;

	network = kzalloc(माप(*network), GFP_ATOMIC);
	अगर (!network)
		जाओ out;

	capability = le16_to_cpu(beacon->capability);
	IEEE80211_DEBUG_SCAN(
		"'%s' (%pM): %c%c%c%c %c%c%c%c-%c%c%c%c %c%c%c%c\n",
		escape_essid(info_element->data, info_element->len),
		beacon->header.addr3,
		(capability & BIT(0xf)) ? '1' : '0',
		(capability & BIT(0xe)) ? '1' : '0',
		(capability & BIT(0xd)) ? '1' : '0',
		(capability & BIT(0xc)) ? '1' : '0',
		(capability & BIT(0xb)) ? '1' : '0',
		(capability & BIT(0xa)) ? '1' : '0',
		(capability & BIT(0x9)) ? '1' : '0',
		(capability & BIT(0x8)) ? '1' : '0',
		(capability & BIT(0x7)) ? '1' : '0',
		(capability & BIT(0x6)) ? '1' : '0',
		(capability & BIT(0x5)) ? '1' : '0',
		(capability & BIT(0x4)) ? '1' : '0',
		(capability & BIT(0x3)) ? '1' : '0',
		(capability & BIT(0x2)) ? '1' : '0',
		(capability & BIT(0x1)) ? '1' : '0',
		(capability & BIT(0x0)) ? '1' : '0');

	अगर (ieee80211_network_init(ieee, beacon, network, stats)) अणु
		IEEE80211_DEBUG_SCAN("Dropped '%s' (%pM) via %s.\n",
				     escape_essid(info_element->data,
						  info_element->len),
				     beacon->header.addr3,
				     fc == IEEE80211_STYPE_PROBE_RESP ?
				     "PROBE RESPONSE" : "BEACON");
		जाओ out;
	पूर्ण

	// For Asus EeePc request,
	// (1) अगर wireless adapter receive get any 802.11d country code in AP beacon,
	//	   wireless adapter should follow the country code.
	// (2)  If there is no any country code in beacon,
	//       then wireless adapter should करो active scan from ch1~11 and
	//       passive scan from ch12~14

	अगर (!is_legal_channel(ieee, network->channel))
		जाओ out;
	अगर (ieee->bGlobalDoमुख्य) अणु
		अगर (fc == IEEE80211_STYPE_PROBE_RESP) अणु
			अगर (IS_COUNTRY_IE_VALID(ieee)) अणु
				// Case 1: Country code
				अगर (!is_legal_channel(ieee, network->channel)) अणु
					netdev_warn(ieee->dev, "GetScanInfo(): For Country code, filter probe response at channel(%d).\n", network->channel);
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				// Case 2: No any country code.
				// Filter over channel ch12~14
				अगर (network->channel > 11) अणु
					netdev_warn(ieee->dev, "GetScanInfo(): For Global Domain, filter probe response at channel(%d).\n", network->channel);
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (IS_COUNTRY_IE_VALID(ieee)) अणु
				// Case 1: Country code
				अगर (!is_legal_channel(ieee, network->channel)) अणु
					netdev_warn(ieee->dev, "GetScanInfo(): For Country code, filter beacon at channel(%d).\n", network->channel);
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				// Case 2: No any country code.
				// Filter over channel ch12~14
				अगर (network->channel > 14) अणु
					netdev_warn(ieee->dev, "GetScanInfo(): For Global Domain, filter beacon at channel(%d).\n", network->channel);
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* The network parsed correctly -- so now we scan our known networks
	 * to see अगर we can find it in our list.
	 *
	 * NOTE:  This search is definitely not optimized.  Once its करोing
	 *        the "right thing" we'll optimize it क्रम efficiency अगर
	 *        necessary */

	/* Search क्रम this entry in the list and update it अगर it is
	 * alपढ़ोy there. */

	spin_lock_irqsave(&ieee->lock, flags);

	अगर (is_same_network(&ieee->current_network, network, ieee)) अणु
		update_network(&ieee->current_network, network);
		अगर ((ieee->current_network.mode == IEEE_N_24G || ieee->current_network.mode == IEEE_G)
		    && ieee->current_network.berp_info_valid)अणु
			अगर (ieee->current_network.erp_value & ERP_UseProtection)
				ieee->current_network.buseprotection = true;
			अन्यथा
				ieee->current_network.buseprotection = false;
		पूर्ण
		अगर (is_beacon(beacon->header.frame_ctl)) अणु
			अगर (ieee->state == IEEE80211_LINKED)
				ieee->LinkDetectInfo.NumRecvBcnInPeriod++;
		पूर्ण अन्यथा //hidden AP
			network->flags = (~NETWORK_EMPTY_ESSID & network->flags) | (NETWORK_EMPTY_ESSID & ieee->current_network.flags);
	पूर्ण

	list_क्रम_each_entry(target, &ieee->network_list, list) अणु
		अगर (is_same_network(target, network, ieee))
			अवरोध;
		अगर (!oldest ||
		    (target->last_scanned < oldest->last_scanned))
			oldest = target;
	पूर्ण

	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation */
	अगर (&target->list == &ieee->network_list) अणु
		अगर (list_empty(&ieee->network_मुक्त_list)) अणु
			/* If there are no more slots, expire the oldest */
			list_del(&oldest->list);
			target = oldest;
			IEEE80211_DEBUG_SCAN("Expired '%s' (%pM) from "
					     "network list.\n",
					     escape_essid(target->ssid,
							  target->ssid_len),
					     target->bssid);
		पूर्ण अन्यथा अणु
			/* Otherwise just pull from the मुक्त list */
			target = list_entry(ieee->network_मुक्त_list.next,
					    काष्ठा ieee80211_network, list);
			list_del(ieee->network_मुक्त_list.next);
		पूर्ण


#अगर_घोषित CONFIG_IEEE80211_DEBUG
		IEEE80211_DEBUG_SCAN("Adding '%s' (%pM) via %s.\n",
				     escape_essid(network->ssid,
						  network->ssid_len),
				     network->bssid,
				     fc == IEEE80211_STYPE_PROBE_RESP ?
				     "PROBE RESPONSE" : "BEACON");
#पूर्ण_अगर
		स_नकल(target, network, माप(*target));
		list_add_tail(&target->list, &ieee->network_list);
		अगर (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE)
			ieee80211_sofपंचांगac_new_net(ieee, network);
	पूर्ण अन्यथा अणु
		IEEE80211_DEBUG_SCAN("Updating '%s' (%pM) via %s.\n",
				     escape_essid(target->ssid,
						  target->ssid_len),
				     target->bssid,
				     fc == IEEE80211_STYPE_PROBE_RESP ?
				     "PROBE RESPONSE" : "BEACON");

		/* we have an entry and we are going to update it. But this entry may
		 * be alपढ़ोy expired. In this हाल we करो the same as we found a new
		 * net and call the new_net handler
		 */
		renew = !समय_after(target->last_scanned + ieee->scan_age, jअगरfies);
		//YJ,add,080819,क्रम hidden ap
		अगर (is_beacon(beacon->header.frame_ctl) == 0)
			network->flags = (~NETWORK_EMPTY_ESSID & network->flags) | (NETWORK_EMPTY_ESSID & target->flags);
		//अगर(म_भेदन(network->ssid, "linksys-c",9) == 0)
		//	prपूर्णांकk("====>2 network->ssid=%s FLAG=%d target.ssid=%s FLAG=%d\n", network->ssid, network->flags, target->ssid, target->flags);
		अगर (((network->flags & NETWORK_EMPTY_ESSID) == NETWORK_EMPTY_ESSID) \
		    && (((network->ssid_len > 0) && (म_भेदन(target->ssid, network->ssid, network->ssid_len)))\
 || ((ieee->current_network.ssid_len == network->ssid_len) && (म_भेदन(ieee->current_network.ssid, network->ssid, network->ssid_len) == 0) && (ieee->state == IEEE80211_NOLINK))))
			renew = 1;
		//YJ,add,080819,क्रम hidden ap,end

		update_network(target, network);
		अगर (renew && (ieee->sofपंचांगac_features & IEEE_SOFTMAC_ASSOCIATE))
			ieee80211_sofपंचांगac_new_net(ieee, network);
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);
	अगर (is_beacon(beacon->header.frame_ctl) && is_same_network(&ieee->current_network, network, ieee) && \
		(ieee->state == IEEE80211_LINKED)) अणु
		अगर (ieee->handle_beacon)
			ieee->handle_beacon(ieee->dev, beacon, &ieee->current_network);
	पूर्ण

out:
	kमुक्त(network);
पूर्ण

व्योम ieee80211_rx_mgt(काष्ठा ieee80211_device *ieee,
		      काष्ठा rtl_80211_hdr_4addr *header,
		      काष्ठा ieee80211_rx_stats *stats)
अणु
	चयन (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl))) अणु

	हाल IEEE80211_STYPE_BEACON:
		IEEE80211_DEBUG_MGMT("received BEACON (%d)\n",
			WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		IEEE80211_DEBUG_SCAN("Beacon\n");
		ieee80211_process_probe_response(
			ieee, (काष्ठा ieee80211_probe_response *)header, stats);
		अवरोध;

	हाल IEEE80211_STYPE_PROBE_RESP:
		IEEE80211_DEBUG_MGMT("received PROBE RESPONSE (%d)\n",
			WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		IEEE80211_DEBUG_SCAN("Probe response\n");
		ieee80211_process_probe_response(
			ieee, (काष्ठा ieee80211_probe_response *)header, stats);
		अवरोध;

	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_rx_mgt);
