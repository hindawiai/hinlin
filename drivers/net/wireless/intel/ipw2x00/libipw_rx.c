<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Original code based Host AP (software wireless LAN access poपूर्णांक) driver
 * क्रम Intersil Prism2/2.5/3 - hostap.o module, common routines
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2004-2005, Intel Corporation
 */

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/gfp.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>

#समावेश <net/lib80211.h>

#समावेश "libipw.h"

अटल व्योम libipw_monitor_rx(काष्ठा libipw_device *ieee,
					काष्ठा sk_buff *skb,
					काष्ठा libipw_rx_stats *rx_stats)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_control);

	skb->dev = ieee->dev;
	skb_reset_mac_header(skb);
	skb_pull(skb, libipw_get_hdrlen(fc));
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_80211_RAW);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल काष्ठा libipw_frag_entry *libipw_frag_cache_find(काष्ठा
							      libipw_device
							      *ieee,
							      अचिन्हित पूर्णांक seq,
							      अचिन्हित पूर्णांक frag,
							      u8 * src,
							      u8 * dst)
अणु
	काष्ठा libipw_frag_entry *entry;
	पूर्णांक i;

	क्रम (i = 0; i < LIBIPW_FRAG_CACHE_LEN; i++) अणु
		entry = &ieee->frag_cache[i];
		अगर (entry->skb != शून्य &&
		    समय_after(jअगरfies, entry->first_frag_समय + 2 * HZ)) अणु
			LIBIPW_DEBUG_FRAG("expiring fragment cache entry "
					     "seq=%u last_frag=%u\n",
					     entry->seq, entry->last_frag);
			dev_kमुक्त_skb_any(entry->skb);
			entry->skb = शून्य;
		पूर्ण

		अगर (entry->skb != शून्य && entry->seq == seq &&
		    (entry->last_frag + 1 == frag || frag == -1) &&
		    ether_addr_equal(entry->src_addr, src) &&
		    ether_addr_equal(entry->dst_addr, dst))
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल काष्ठा sk_buff *libipw_frag_cache_get(काष्ठा libipw_device *ieee,
						काष्ठा libipw_hdr_4addr *hdr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 sc;
	अचिन्हित पूर्णांक frag, seq;
	काष्ठा libipw_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);
	seq = WLAN_GET_SEQ_SEQ(sc);

	अगर (frag == 0) अणु
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(ieee->dev->mtu +
				    माप(काष्ठा libipw_hdr_4addr) +
				    8 /* LLC */  +
				    2 /* alignment */  +
				    8 /* WEP */  + ETH_ALEN /* WDS */ );
		अगर (skb == शून्य)
			वापस शून्य;

		entry = &ieee->frag_cache[ieee->frag_next_idx];
		ieee->frag_next_idx++;
		अगर (ieee->frag_next_idx >= LIBIPW_FRAG_CACHE_LEN)
			ieee->frag_next_idx = 0;

		अगर (entry->skb != शून्य)
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
		entry = libipw_frag_cache_find(ieee, seq, frag, hdr->addr2,
						  hdr->addr1);
		अगर (entry != शून्य) अणु
			entry->last_frag = frag;
			skb = entry->skb;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक libipw_frag_cache_invalidate(काष्ठा libipw_device *ieee,
					   काष्ठा libipw_hdr_4addr *hdr)
अणु
	u16 sc;
	अचिन्हित पूर्णांक seq;
	काष्ठा libipw_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctl);
	seq = WLAN_GET_SEQ_SEQ(sc);

	entry = libipw_frag_cache_find(ieee, seq, -1, hdr->addr2,
					  hdr->addr1);

	अगर (entry == शून्य) अणु
		LIBIPW_DEBUG_FRAG("could not invalidate fragment cache "
				     "entry (seq=%u)\n", seq);
		वापस -1;
	पूर्ण

	entry->skb = शून्य;
	वापस 0;
पूर्ण

#अगर_घोषित NOT_YET
/* libipw_rx_frame_mgपंचांगt
 *
 * Responsible क्रम handling management control frames
 *
 * Called by libipw_rx */
अटल पूर्णांक
libipw_rx_frame_mgmt(काष्ठा libipw_device *ieee, काष्ठा sk_buff *skb,
			काष्ठा libipw_rx_stats *rx_stats, u16 type,
			u16 stype)
अणु
	अगर (ieee->iw_mode == IW_MODE_MASTER) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Master mode not yet supported.\n",
		       ieee->dev->name);
		वापस 0;
/*
  hostap_update_sta_ps(ieee, (काष्ठा hostap_libipw_hdr_4addr *)
  skb->data);*/
	पूर्ण

	अगर (ieee->hostapd && type == WLAN_FC_TYPE_MGMT) अणु
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
			prपूर्णांकk(KERN_DEBUG "%s: unknown management frame "
			       "(type=0x%02x, stype=0x%02x) dropped\n",
			       skb->dev->name, type, stype);
			वापस -1;
		पूर्ण

		hostap_rx(skb->dev, skb, rx_stats);
		वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: hostap_rx_frame_mgmt: management frame "
	       "received in non-Host AP mode\n", skb->dev->name);
	वापस -1;
पूर्ण
#पूर्ण_अगर

/* See IEEE 802.1H क्रम LLC/SNAP encapsulation/decapsulation */
/* Ethernet-II snap header (RFC1042 क्रम most EtherTypes) */
अटल अचिन्हित अक्षर libipw_rfc1042_header[] =
    अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 पूर्ण;

/* Bridge-Tunnel header (क्रम EtherTypes ETH_P_AARP and ETH_P_IPX) */
अटल अचिन्हित अक्षर libipw_bridge_tunnel_header[] =
    अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 पूर्ण;
/* No encapsulation header अगर EtherType < 0x600 (=length) */

/* Called by libipw_rx_frame_decrypt */
अटल पूर्णांक libipw_is_eapol_frame(काष्ठा libipw_device *ieee,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = ieee->dev;
	u16 fc, ethertype;
	काष्ठा libipw_hdr_3addr *hdr;
	u8 *pos;

	अगर (skb->len < 24)
		वापस 0;

	hdr = (काष्ठा libipw_hdr_3addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	/* check that the frame is unicast frame to us */
	अगर ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
	    IEEE80211_FCTL_TODS &&
	    ether_addr_equal(hdr->addr1, dev->dev_addr) &&
	    ether_addr_equal(hdr->addr3, dev->dev_addr)) अणु
		/* ToDS frame with own addr BSSID and DA */
	पूर्ण अन्यथा अगर ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		   IEEE80211_FCTL_FROMDS &&
		   ether_addr_equal(hdr->addr1, dev->dev_addr)) अणु
		/* FromDS frame with own addr as DA */
	पूर्ण अन्यथा
		वापस 0;

	अगर (skb->len < 24 + 8)
		वापस 0;

	/* check क्रम port access entity Ethernet type */
	pos = skb->data + 24;
	ethertype = (pos[6] << 8) | pos[7];
	अगर (ethertype == ETH_P_PAE)
		वापस 1;

	वापस 0;
पूर्ण

/* Called only as a tasklet (software IRQ), by libipw_rx */
अटल पूर्णांक
libipw_rx_frame_decrypt(काष्ठा libipw_device *ieee, काष्ठा sk_buff *skb,
			   काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा libipw_hdr_3addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_mpdu == शून्य)
		वापस 0;

	hdr = (काष्ठा libipw_hdr_3addr *)skb->data;
	hdrlen = libipw_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		LIBIPW_DEBUG_DROP("decryption failed (SA=%pM) res=%d\n",
				     hdr->addr2, res);
		अगर (res == -2)
			LIBIPW_DEBUG_DROP("Decryption failed ICV "
					     "mismatch (key %d)\n",
					     skb->data[hdrlen + 3] >> 6);
		ieee->ieee_stats.rx_discards_undecryptable++;
		वापस -1;
	पूर्ण

	वापस res;
पूर्ण

/* Called only as a tasklet (software IRQ), by libipw_rx */
अटल पूर्णांक
libipw_rx_frame_decrypt_msdu(काष्ठा libipw_device *ieee,
				काष्ठा sk_buff *skb, पूर्णांक keyidx,
				काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा libipw_hdr_3addr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_msdu == शून्य)
		वापस 0;

	hdr = (काष्ठा libipw_hdr_3addr *)skb->data;
	hdrlen = libipw_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_msdu(skb, keyidx, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: MSDU decryption/MIC verification failed"
		       " (SA=%pM keyidx=%d)\n", ieee->dev->name, hdr->addr2,
		       keyidx);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* All received frames are sent to this function. @skb contains the frame in
 * IEEE 802.11 क्रमmat, i.e., in the क्रमmat it was sent over air.
 * This function is called only as a tasklet (software IRQ). */
पूर्णांक libipw_rx(काष्ठा libipw_device *ieee, काष्ठा sk_buff *skb,
		 काष्ठा libipw_rx_stats *rx_stats)
अणु
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा libipw_hdr_4addr *hdr;
	माप_प्रकार hdrlen;
	u16 fc, type, stype, sc;
	अचिन्हित पूर्णांक frag;
	u8 *payload;
	u16 ethertype;
#अगर_घोषित NOT_YET
	काष्ठा net_device *wds = शून्य;
	काष्ठा sk_buff *skb2 = शून्य;
	काष्ठा net_device *wds = शून्य;
	पूर्णांक frame_authorized = 0;
	पूर्णांक from_assoc_ap = 0;
	व्योम *sta = शून्य;
#पूर्ण_अगर
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	काष्ठा lib80211_crypt_data *crypt = शून्य;
	पूर्णांक keyidx = 0;
	पूर्णांक can_be_decrypted = 0;

	hdr = (काष्ठा libipw_hdr_4addr *)skb->data;
	अगर (skb->len < 10) अणु
		prपूर्णांकk(KERN_INFO "%s: SKB length < 10\n", dev->name);
		जाओ rx_dropped;
	पूर्ण

	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	stype = WLAN_FC_GET_STYPE(fc);
	sc = le16_to_cpu(hdr->seq_ctl);
	frag = WLAN_GET_SEQ_FRAG(sc);
	hdrlen = libipw_get_hdrlen(fc);

	अगर (skb->len < hdrlen) अणु
		prपूर्णांकk(KERN_INFO "%s: invalid SKB length %d\n",
			dev->name, skb->len);
		जाओ rx_dropped;
	पूर्ण

	/* Put this code here so that we aव्योम duplicating it in all
	 * Rx paths. - Jean II */
#अगर_घोषित CONFIG_WIRELESS_EXT
#अगर_घोषित IW_WIRELESS_SPY		/* defined in iw_handler.h */
	/* If spy monitoring on */
	अगर (ieee->spy_data.spy_number > 0) अणु
		काष्ठा iw_quality wstats;

		wstats.updated = 0;
		अगर (rx_stats->mask & LIBIPW_STATMASK_RSSI) अणु
			wstats.level = rx_stats->संकेत;
			wstats.updated |= IW_QUAL_LEVEL_UPDATED;
		पूर्ण अन्यथा
			wstats.updated |= IW_QUAL_LEVEL_INVALID;

		अगर (rx_stats->mask & LIBIPW_STATMASK_NOISE) अणु
			wstats.noise = rx_stats->noise;
			wstats.updated |= IW_QUAL_NOISE_UPDATED;
		पूर्ण अन्यथा
			wstats.updated |= IW_QUAL_NOISE_INVALID;

		अगर (rx_stats->mask & LIBIPW_STATMASK_SIGNAL) अणु
			wstats.qual = rx_stats->संकेत;
			wstats.updated |= IW_QUAL_QUAL_UPDATED;
		पूर्ण अन्यथा
			wstats.updated |= IW_QUAL_QUAL_INVALID;

		/* Update spy records */
		wireless_spy_update(ieee->dev, hdr->addr2, &wstats);
	पूर्ण
#पूर्ण_अगर				/* IW_WIRELESS_SPY */
#पूर्ण_अगर				/* CONFIG_WIRELESS_EXT */

#अगर_घोषित NOT_YET
	hostap_update_rx_stats(local->ap, hdr, rx_stats);
#पूर्ण_अगर

	अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		libipw_monitor_rx(ieee, skb, rx_stats);
		वापस 1;
	पूर्ण

	can_be_decrypted = (is_multicast_ether_addr(hdr->addr1) ||
			    is_broadcast_ether_addr(hdr->addr2)) ?
	    ieee->host_mc_decrypt : ieee->host_decrypt;

	अगर (can_be_decrypted) अणु
		अगर (skb->len >= hdrlen + 3) अणु
			/* Top two-bits of byte 3 are the key index */
			keyidx = skb->data[hdrlen + 3] >> 6;
		पूर्ण

		/* ieee->crypt[] is WEP_KEY (4) in length.  Given that keyidx
		 * is only allowed 2-bits of storage, no value of keyidx can
		 * be provided via above code that would result in keyidx
		 * being out of range */
		crypt = ieee->crypt_info.crypt[keyidx];

#अगर_घोषित NOT_YET
		sta = शून्य;

		/* Use station specअगरic key to override शेष keys अगर the
		 * receiver address is a unicast address ("individual RA"). If
		 * bcrx_sta_key parameter is set, station specअगरic key is used
		 * even with broad/multicast tarमाला_लो (this is against IEEE
		 * 802.11, but makes it easier to use dअगरferent keys with
		 * stations that करो not support WEP key mapping). */

		अगर (is_unicast_ether_addr(hdr->addr1) || local->bcrx_sta_key)
			(व्योम)hostap_handle_sta_crypto(local, hdr, &crypt,
						       &sta);
#पूर्ण_अगर

		/* allow शून्य decrypt to indicate an station specअगरic override
		 * क्रम शेष encryption */
		अगर (crypt && (crypt->ops == शून्य ||
			      crypt->ops->decrypt_mpdu == शून्य))
			crypt = शून्य;

		अगर (!crypt && (fc & IEEE80211_FCTL_PROTECTED)) अणु
			/* This seems to be triggered by some (multicast?)
			 * frames from other than current BSS, so just drop the
			 * frames silently instead of filling प्रणाली log with
			 * these reports. */
			LIBIPW_DEBUG_DROP("Decryption failed (not set)"
					     " (SA=%pM)\n", hdr->addr2);
			ieee->ieee_stats.rx_discards_undecryptable++;
			जाओ rx_dropped;
		पूर्ण
	पूर्ण
#अगर_घोषित NOT_YET
	अगर (type != WLAN_FC_TYPE_DATA) अणु
		अगर (type == WLAN_FC_TYPE_MGMT && stype == WLAN_FC_STYPE_AUTH &&
		    fc & IEEE80211_FCTL_PROTECTED && ieee->host_decrypt &&
		    (keyidx = hostap_rx_frame_decrypt(ieee, skb, crypt)) < 0) अणु
			prपूर्णांकk(KERN_DEBUG "%s: failed to decrypt mgmt::auth "
			       "from %pM\n", dev->name, hdr->addr2);
			/* TODO: could inक्रमm hostapd about this so that it
			 * could send auth failure report */
			जाओ rx_dropped;
		पूर्ण

		अगर (libipw_rx_frame_mgmt(ieee, skb, rx_stats, type, stype))
			जाओ rx_dropped;
		अन्यथा
			जाओ rx_निकास;
	पूर्ण
#पूर्ण_अगर
	/* drop duplicate 802.11 retransmissions (IEEE 802.11 Chap. 9.29) */
	अगर (sc == ieee->prev_seq_ctl)
		जाओ rx_dropped;
	अन्यथा
		ieee->prev_seq_ctl = sc;

	/* Data frame - extract src/dst addresses */
	अगर (skb->len < LIBIPW_3ADDR_LEN)
		जाओ rx_dropped;

	चयन (fc & (IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS)) अणु
	हाल IEEE80211_FCTL_FROMDS:
		स_नकल(dst, hdr->addr1, ETH_ALEN);
		स_नकल(src, hdr->addr3, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_TODS:
		स_नकल(dst, hdr->addr3, ETH_ALEN);
		स_नकल(src, hdr->addr2, ETH_ALEN);
		अवरोध;
	हाल IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS:
		अगर (skb->len < LIBIPW_4ADDR_LEN)
			जाओ rx_dropped;
		स_नकल(dst, hdr->addr3, ETH_ALEN);
		स_नकल(src, hdr->addr4, ETH_ALEN);
		अवरोध;
	शेष:
		स_नकल(dst, hdr->addr1, ETH_ALEN);
		स_नकल(src, hdr->addr2, ETH_ALEN);
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
	    (fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
	    IEEE80211_FCTL_FROMDS && ieee->stadev &&
	    ether_addr_equal(hdr->addr2, ieee->assoc_ap_addr)) अणु
		/* Frame from BSSID of the AP क्रम which we are a client */
		skb->dev = dev = ieee->stadev;
		stats = hostap_get_stats(dev);
		from_assoc_ap = 1;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित NOT_YET
	अगर ((ieee->iw_mode == IW_MODE_MASTER ||
	     ieee->iw_mode == IW_MODE_REPEAT) && !from_assoc_ap) अणु
		चयन (hostap_handle_sta_rx(ieee, dev, skb, rx_stats,
					     wds != शून्य)) अणु
		हाल AP_RX_CONTINUE_NOT_AUTHORIZED:
			frame_authorized = 0;
			अवरोध;
		हाल AP_RX_CONTINUE:
			frame_authorized = 1;
			अवरोध;
		हाल AP_RX_DROP:
			जाओ rx_dropped;
		हाल AP_RX_EXIT:
			जाओ rx_निकास;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Nullfunc frames may have PS-bit set, so they must be passed to
	 * hostap_handle_sta_rx() beक्रमe being dropped here. */

	stype &= ~IEEE80211_STYPE_QOS_DATA;

	अगर (stype != IEEE80211_STYPE_DATA &&
	    stype != IEEE80211_STYPE_DATA_CFACK &&
	    stype != IEEE80211_STYPE_DATA_CFPOLL &&
	    stype != IEEE80211_STYPE_DATA_CFACKPOLL) अणु
		अगर (stype != IEEE80211_STYPE_शून्यFUNC)
			LIBIPW_DEBUG_DROP("RX: dropped data frame "
					     "with no data (type=0x%02x, "
					     "subtype=0x%02x, len=%d)\n",
					     type, stype, skb->len);
		जाओ rx_dropped;
	पूर्ण

	/* skb: hdr + (possibly fragmented, possibly encrypted) payload */

	अगर ((fc & IEEE80211_FCTL_PROTECTED) && can_be_decrypted &&
	    (keyidx = libipw_rx_frame_decrypt(ieee, skb, crypt)) < 0)
		जाओ rx_dropped;

	hdr = (काष्ठा libipw_hdr_4addr *)skb->data;

	/* skb: hdr + (possibly fragmented) plaपूर्णांकext payload */
	// PR: FIXME: hostap has additional conditions in the "if" below:
	// ieee->host_decrypt && (fc & IEEE80211_FCTL_PROTECTED) &&
	अगर ((frag != 0) || (fc & IEEE80211_FCTL_MOREFRAGS)) अणु
		पूर्णांक flen;
		काष्ठा sk_buff *frag_skb = libipw_frag_cache_get(ieee, hdr);
		LIBIPW_DEBUG_FRAG("Rx Fragment received (%u)\n", frag);

		अगर (!frag_skb) अणु
			LIBIPW_DEBUG(LIBIPW_DL_RX | LIBIPW_DL_FRAG,
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
			prपूर्णांकk(KERN_WARNING "%s: host decrypted and "
			       "reassembled frame did not fit skb\n",
			       dev->name);
			libipw_frag_cache_invalidate(ieee, hdr);
			जाओ rx_dropped;
		पूर्ण

		अगर (frag == 0) अणु
			/* copy first fragment (including full headers) पूर्णांकo
			 * beginning of the fragment cache skb */
			skb_copy_from_linear_data(skb, skb_put(frag_skb, flen), flen);
		पूर्ण अन्यथा अणु
			/* append frame payload to the end of the fragment
			 * cache skb */
			skb_copy_from_linear_data_offset(skb, hdrlen,
				      skb_put(frag_skb, flen), flen);
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
		hdr = (काष्ठा libipw_hdr_4addr *)skb->data;
		libipw_frag_cache_invalidate(ieee, hdr);
	पूर्ण

	/* skb: hdr + (possible reassembled) full MSDU payload; possibly still
	 * encrypted/authenticated */
	अगर ((fc & IEEE80211_FCTL_PROTECTED) && can_be_decrypted &&
	    libipw_rx_frame_decrypt_msdu(ieee, skb, keyidx, crypt))
		जाओ rx_dropped;

	hdr = (काष्ठा libipw_hdr_4addr *)skb->data;
	अगर (crypt && !(fc & IEEE80211_FCTL_PROTECTED) && !ieee->खोलो_wep) अणु
		अगर (		/*ieee->ieee802_1x && */
			   libipw_is_eapol_frame(ieee, skb)) अणु
			/* pass unencrypted EAPOL frames even अगर encryption is
			 * configured */
		पूर्ण अन्यथा अणु
			LIBIPW_DEBUG_DROP("encryption configured, but RX "
					     "frame not encrypted (SA=%pM)\n",
					     hdr->addr2);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	अगर (crypt && !(fc & IEEE80211_FCTL_PROTECTED) && !ieee->खोलो_wep &&
	    !libipw_is_eapol_frame(ieee, skb)) अणु
		LIBIPW_DEBUG_DROP("dropped unencrypted RX data "
				     "frame from %pM (drop_unencrypted=1)\n",
				     hdr->addr2);
		जाओ rx_dropped;
	पूर्ण

	/* If the frame was decrypted in hardware, we may need to strip off
	 * any security data (IV, ICV, etc) that was left behind */
	अगर (!can_be_decrypted && (fc & IEEE80211_FCTL_PROTECTED) &&
	    ieee->host_strip_iv_icv) अणु
		पूर्णांक trimlen = 0;

		/* Top two-bits of byte 3 are the key index */
		अगर (skb->len >= hdrlen + 3)
			keyidx = skb->data[hdrlen + 3] >> 6;

		/* To strip off any security data which appears beक्रमe the
		 * payload, we simply increase hdrlen (as the header माला_लो
		 * chopped off immediately below). For the security data which
		 * appears after the payload, we use skb_trim. */

		चयन (ieee->sec.encode_alg[keyidx]) अणु
		हाल SEC_ALG_WEP:
			/* 4 byte IV */
			hdrlen += 4;
			/* 4 byte ICV */
			trimlen = 4;
			अवरोध;
		हाल SEC_ALG_TKIP:
			/* 4 byte IV, 4 byte ExtIV */
			hdrlen += 8;
			/* 8 byte MIC, 4 byte ICV */
			trimlen = 12;
			अवरोध;
		हाल SEC_ALG_CCMP:
			/* 8 byte CCMP header */
			hdrlen += 8;
			/* 8 byte MIC */
			trimlen = 8;
			अवरोध;
		पूर्ण

		अगर (skb->len < trimlen)
			जाओ rx_dropped;

		__skb_trim(skb, skb->len - trimlen);

		अगर (skb->len < hdrlen)
			जाओ rx_dropped;
	पूर्ण

	/* skb: hdr + (possible reassembled) full plaपूर्णांकext payload */

	payload = skb->data + hdrlen;
	ethertype = (payload[6] << 8) | payload[7];

#अगर_घोषित NOT_YET
	/* If IEEE 802.1X is used, check whether the port is authorized to send
	 * the received frame. */
	अगर (ieee->ieee802_1x && ieee->iw_mode == IW_MODE_MASTER) अणु
		अगर (ethertype == ETH_P_PAE) अणु
			prपूर्णांकk(KERN_DEBUG "%s: RX: IEEE 802.1X frame\n",
			       dev->name);
			अगर (ieee->hostapd && ieee->apdev) अणु
				/* Send IEEE 802.1X frames to the user
				 * space daemon क्रम processing */
				prism2_rx_80211(ieee->apdev, skb, rx_stats,
						PRISM2_RX_MGMT);
				ieee->apdevstats.rx_packets++;
				ieee->apdevstats.rx_bytes += skb->len;
				जाओ rx_निकास;
			पूर्ण
		पूर्ण अन्यथा अगर (!frame_authorized) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped frame from "
			       "unauthorized port (IEEE 802.1X): "
			       "ethertype=0x%04x\n", dev->name, ethertype);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
	अगर (skb->len - hdrlen >= 8 &&
	    ((स_भेद(payload, libipw_rfc1042_header, SNAP_SIZE) == 0 &&
	      ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
	     स_भेद(payload, libipw_bridge_tunnel_header, SNAP_SIZE) == 0)) अणु
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
		 * replace EtherType */
		skb_pull(skb, hdrlen + SNAP_SIZE);
		स_नकल(skb_push(skb, ETH_ALEN), src, ETH_ALEN);
		स_नकल(skb_push(skb, ETH_ALEN), dst, ETH_ALEN);
	पूर्ण अन्यथा अणु
		__be16 len;
		/* Leave Ethernet header part of hdr and full payload */
		skb_pull(skb, hdrlen);
		len = htons(skb->len);
		स_नकल(skb_push(skb, 2), &len, 2);
		स_नकल(skb_push(skb, ETH_ALEN), src, ETH_ALEN);
		स_नकल(skb_push(skb, ETH_ALEN), dst, ETH_ALEN);
	पूर्ण

#अगर_घोषित NOT_YET
	अगर (wds && ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		    IEEE80211_FCTL_TODS) && skb->len >= ETH_HLEN + ETH_ALEN) अणु
		/* Non-standard frame: get addr4 from its bogus location after
		 * the payload */
		skb_copy_to_linear_data_offset(skb, ETH_ALEN,
					       skb->data + skb->len - ETH_ALEN,
					       ETH_ALEN);
		skb_trim(skb, skb->len - ETH_ALEN);
	पूर्ण
#पूर्ण_अगर

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;

#अगर_घोषित NOT_YET
	अगर (ieee->iw_mode == IW_MODE_MASTER && !wds && ieee->ap->bridge_packets) अणु
		अगर (is_multicast_ether_addr(dst)) अणु
			/* copy multicast frame both to the higher layers and
			 * to the wireless media */
			ieee->ap->bridged_multicast++;
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb2 == शून्य)
				prपूर्णांकk(KERN_DEBUG "%s: skb_clone failed for "
				       "multicast frame\n", dev->name);
		पूर्ण अन्यथा अगर (hostap_is_sta_assoc(ieee->ap, dst)) अणु
			/* send frame directly to the associated STA using
			 * wireless media and not passing to higher layers */
			ieee->ap->bridged_unicast++;
			skb2 = skb;
			skb = शून्य;
		पूर्ण
	पूर्ण

	अगर (skb2 != शून्य) अणु
		/* send to wireless media */
		skb2->dev = dev;
		skb2->protocol = htons(ETH_P_802_3);
		skb_reset_mac_header(skb2);
		skb_reset_network_header(skb2);
		/* skb2->network_header += ETH_HLEN; */
		dev_queue_xmit(skb2);
	पूर्ण
#पूर्ण_अगर

	अगर (skb) अणु
		skb->protocol = eth_type_trans(skb, dev);
		स_रखो(skb->cb, 0, माप(skb->cb));
		skb->ip_summed = CHECKSUM_NONE;	/* 802.11 crc not sufficient */
		अगर (netअगर_rx(skb) == NET_RX_DROP) अणु
			/* netअगर_rx always succeeds, but it might drop
			 * the packet.  If it drops the packet, we log that
			 * in our stats. */
			LIBIPW_DEBUG_DROP
			    ("RX: netif_rx dropped the packet\n");
			dev->stats.rx_dropped++;
		पूर्ण
	पूर्ण

      rx_निकास:
#अगर_घोषित NOT_YET
	अगर (sta)
		hostap_handle_sta_release(sta);
#पूर्ण_अगर
	वापस 1;

      rx_dropped:
	dev->stats.rx_dropped++;

	/* Returning 0 indicates to caller that we have not handled the SKB--
	 * so it is still allocated and can be used again by underlying
	 * hardware as a DMA target */
	वापस 0;
पूर्ण

/* Filter out unrelated packets, call libipw_rx[_mgt]
 * This function takes over the skb, it should not be used again after calling
 * this function. */
व्योम libipw_rx_any(काष्ठा libipw_device *ieee,
		     काष्ठा sk_buff *skb, काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा libipw_hdr_4addr *hdr;
	पूर्णांक is_packet_क्रम_us;
	u16 fc;

	अगर (ieee->iw_mode == IW_MODE_MONITOR) अणु
		अगर (!libipw_rx(ieee, skb, stats))
			dev_kमुक्त_skb_irq(skb);
		वापस;
	पूर्ण

	अगर (skb->len < माप(काष्ठा ieee80211_hdr))
		जाओ drop_मुक्त;

	hdr = (काष्ठा libipw_hdr_4addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	अगर ((fc & IEEE80211_FCTL_VERS) != 0)
		जाओ drop_मुक्त;

	चयन (fc & IEEE80211_FCTL_FTYPE) अणु
	हाल IEEE80211_FTYPE_MGMT:
		अगर (skb->len < माप(काष्ठा libipw_hdr_3addr))
			जाओ drop_मुक्त;
		libipw_rx_mgt(ieee, hdr, stats);
		dev_kमुक्त_skb_irq(skb);
		वापस;
	हाल IEEE80211_FTYPE_DATA:
		अवरोध;
	हाल IEEE80211_FTYPE_CTL:
		वापस;
	शेष:
		वापस;
	पूर्ण

	is_packet_क्रम_us = 0;
	चयन (ieee->iw_mode) अणु
	हाल IW_MODE_ADHOC:
		/* our BSS and not from/to DS */
		अगर (ether_addr_equal(hdr->addr3, ieee->bssid))
		अगर ((fc & (IEEE80211_FCTL_TODS+IEEE80211_FCTL_FROMDS)) == 0) अणु
			/* promisc: get all */
			अगर (ieee->dev->flags & IFF_PROMISC)
				is_packet_क्रम_us = 1;
			/* to us */
			अन्यथा अगर (ether_addr_equal(hdr->addr1, ieee->dev->dev_addr))
				is_packet_क्रम_us = 1;
			/* mcast */
			अन्यथा अगर (is_multicast_ether_addr(hdr->addr1))
				is_packet_क्रम_us = 1;
		पूर्ण
		अवरोध;
	हाल IW_MODE_INFRA:
		/* our BSS (== from our AP) and from DS */
		अगर (ether_addr_equal(hdr->addr2, ieee->bssid))
		अगर ((fc & (IEEE80211_FCTL_TODS+IEEE80211_FCTL_FROMDS)) == IEEE80211_FCTL_FROMDS) अणु
			/* promisc: get all */
			अगर (ieee->dev->flags & IFF_PROMISC)
				is_packet_क्रम_us = 1;
			/* to us */
			अन्यथा अगर (ether_addr_equal(hdr->addr1, ieee->dev->dev_addr))
				is_packet_क्रम_us = 1;
			/* mcast */
			अन्यथा अगर (is_multicast_ether_addr(hdr->addr1)) अणु
				/* not our own packet bcasted from AP */
				अगर (!ether_addr_equal(hdr->addr3, ieee->dev->dev_addr))
					is_packet_क्रम_us = 1;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		/* ? */
		अवरोध;
	पूर्ण

	अगर (is_packet_क्रम_us)
		अगर (!libipw_rx(ieee, skb, stats))
			dev_kमुक्त_skb_irq(skb);
	वापस;

drop_मुक्त:
	dev_kमुक्त_skb_irq(skb);
	ieee->dev->stats.rx_dropped++;
पूर्ण

#घोषणा MGMT_FRAME_FIXED_PART_LENGTH		0x24

अटल u8 qos_oui[QOS_OUI_LEN] = अणु 0x00, 0x50, 0xF2 पूर्ण;

/*
* Make the काष्ठाure we पढ़ो from the beacon packet to have
* the right values
*/
अटल पूर्णांक libipw_verअगरy_qos_info(काष्ठा libipw_qos_inक्रमmation_element
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
अटल पूर्णांक libipw_पढ़ो_qos_param_element(काष्ठा libipw_qos_parameter_info
					    *element_param, काष्ठा libipw_info_element
					    *info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा libipw_qos_parameter_info) - 2;

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
		ret = libipw_verअगरy_qos_info(&element_param->info_element,
						QOS_OUI_PARAM_SUB_TYPE);
	वापस ret;
पूर्ण

/*
 * Parse a QoS inक्रमmation element
 */
अटल पूर्णांक libipw_पढ़ो_qos_info_element(काष्ठा
					   libipw_qos_inक्रमmation_element
					   *element_info, काष्ठा libipw_info_element
					   *info_element)
अणु
	पूर्णांक ret = 0;
	u16 size = माप(काष्ठा libipw_qos_inक्रमmation_element) - 2;

	अगर (element_info == शून्य)
		वापस -1;
	अगर (info_element == शून्य)
		वापस -1;

	अगर ((info_element->id == QOS_ELEMENT_ID) && (info_element->len == size)) अणु
		स_नकल(element_info->qui, info_element->data,
		       info_element->len);
		element_info->elementID = info_element->id;
		element_info->length = info_element->len;
	पूर्ण अन्यथा
		ret = -1;

	अगर (ret == 0)
		ret = libipw_verअगरy_qos_info(element_info,
						QOS_OUI_INFO_SUB_TYPE);
	वापस ret;
पूर्ण

/*
 * Write QoS parameters from the ac parameters.
 */
अटल व्योम libipw_qos_convert_ac_to_parameters(काष्ठा
						  libipw_qos_parameter_info
						  *param_elm, काष्ठा
						  libipw_qos_parameters
						  *qos_param)
अणु
	पूर्णांक i;
	काष्ठा libipw_qos_ac_parameter *ac_params;
	u32 txop;
	u8 cw_min;
	u8 cw_max;

	क्रम (i = 0; i < QOS_QUEUE_NUM; i++) अणु
		ac_params = &(param_elm->ac_params_record[i]);

		qos_param->aअगरs[i] = (ac_params->aci_aअगरsn) & 0x0F;
		qos_param->aअगरs[i] -= (qos_param->aअगरs[i] < 2) ? 0 : 2;

		cw_min = ac_params->ecw_min_max & 0x0F;
		qos_param->cw_min[i] = cpu_to_le16((1 << cw_min) - 1);

		cw_max = (ac_params->ecw_min_max & 0xF0) >> 4;
		qos_param->cw_max[i] = cpu_to_le16((1 << cw_max) - 1);

		qos_param->flag[i] =
		    (ac_params->aci_aअगरsn & 0x10) ? 0x01 : 0x00;

		txop = le16_to_cpu(ac_params->tx_op_limit) * 32;
		qos_param->tx_op_limit[i] = cpu_to_le16(txop);
	पूर्ण
पूर्ण

/*
 * we have a generic data element which it may contain QoS inक्रमmation or
 * parameters element. check the inक्रमmation element length to decide
 * which type to पढ़ो
 */
अटल पूर्णांक libipw_parse_qos_info_param_IE(काष्ठा libipw_info_element
					     *info_element,
					     काष्ठा libipw_network *network)
अणु
	पूर्णांक rc = 0;
	काष्ठा libipw_qos_parameters *qos_param = शून्य;
	काष्ठा libipw_qos_inक्रमmation_element qos_info_element;

	rc = libipw_पढ़ो_qos_info_element(&qos_info_element, info_element);

	अगर (rc == 0) अणु
		network->qos_data.param_count = qos_info_element.ac_info & 0x0F;
		network->flags |= NETWORK_HAS_QOS_INFORMATION;
	पूर्ण अन्यथा अणु
		काष्ठा libipw_qos_parameter_info param_element;

		rc = libipw_पढ़ो_qos_param_element(&param_element,
						      info_element);
		अगर (rc == 0) अणु
			qos_param = &(network->qos_data.parameters);
			libipw_qos_convert_ac_to_parameters(&param_element,
							       qos_param);
			network->flags |= NETWORK_HAS_QOS_PARAMETERS;
			network->qos_data.param_count =
			    param_element.info_element.ac_info & 0x0F;
		पूर्ण
	पूर्ण

	अगर (rc == 0) अणु
		LIBIPW_DEBUG_QOS("QoS is supported\n");
		network->qos_data.supported = 1;
	पूर्ण
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_LIBIPW_DEBUG
#घोषणा MFIE_STRING(x) हाल WLAN_EID_ ##x: वापस #x

अटल स्थिर अक्षर *get_info_element_string(u16 id)
अणु
	चयन (id) अणु
		MFIE_STRING(SSID);
		MFIE_STRING(SUPP_RATES);
		MFIE_STRING(FH_PARAMS);
		MFIE_STRING(DS_PARAMS);
		MFIE_STRING(CF_PARAMS);
		MFIE_STRING(TIM);
		MFIE_STRING(IBSS_PARAMS);
		MFIE_STRING(COUNTRY);
		MFIE_STRING(REQUEST);
		MFIE_STRING(CHALLENGE);
		MFIE_STRING(PWR_CONSTRAINT);
		MFIE_STRING(PWR_CAPABILITY);
		MFIE_STRING(TPC_REQUEST);
		MFIE_STRING(TPC_REPORT);
		MFIE_STRING(SUPPORTED_CHANNELS);
		MFIE_STRING(CHANNEL_SWITCH);
		MFIE_STRING(MEASURE_REQUEST);
		MFIE_STRING(MEASURE_REPORT);
		MFIE_STRING(QUIET);
		MFIE_STRING(IBSS_DFS);
		MFIE_STRING(ERP_INFO);
		MFIE_STRING(RSN);
		MFIE_STRING(EXT_SUPP_RATES);
		MFIE_STRING(VENDOR_SPECIFIC);
		MFIE_STRING(QOS_PARAMETER);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक libipw_parse_info_param(काष्ठा libipw_info_element
				      *info_element, u16 length,
				      काष्ठा libipw_network *network)
अणु
	u8 i;
#अगर_घोषित CONFIG_LIBIPW_DEBUG
	अक्षर rates_str[64];
	अक्षर *p;
#पूर्ण_अगर

	जबतक (length >= माप(*info_element)) अणु
		अगर (माप(*info_element) + info_element->len > length) अणु
			LIBIPW_DEBUG_MGMT("Info elem: parse failed: "
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
		हाल WLAN_EID_SSID:
			network->ssid_len = min(info_element->len,
						(u8) IW_ESSID_MAX_SIZE);
			स_नकल(network->ssid, info_element->data,
			       network->ssid_len);
			अगर (network->ssid_len < IW_ESSID_MAX_SIZE)
				स_रखो(network->ssid + network->ssid_len, 0,
				       IW_ESSID_MAX_SIZE - network->ssid_len);

			LIBIPW_DEBUG_MGMT("WLAN_EID_SSID: '%*pE' len=%d.\n",
					  network->ssid_len, network->ssid,
					  network->ssid_len);
			अवरोध;

		हाल WLAN_EID_SUPP_RATES:
#अगर_घोषित CONFIG_LIBIPW_DEBUG
			p = rates_str;
#पूर्ण_अगर
			network->rates_len = min(info_element->len,
						 MAX_RATES_LENGTH);
			क्रम (i = 0; i < network->rates_len; i++) अणु
				network->rates[i] = info_element->data[i];
#अगर_घोषित CONFIG_LIBIPW_DEBUG
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates[i]);
#पूर्ण_अगर
				अगर (libipw_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    LIBIPW_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			LIBIPW_DEBUG_MGMT("WLAN_EID_SUPP_RATES: '%s' (%d)\n",
					     rates_str, network->rates_len);
			अवरोध;

		हाल WLAN_EID_EXT_SUPP_RATES:
#अगर_घोषित CONFIG_LIBIPW_DEBUG
			p = rates_str;
#पूर्ण_अगर
			network->rates_ex_len = min(info_element->len,
						    MAX_RATES_EX_LENGTH);
			क्रम (i = 0; i < network->rates_ex_len; i++) अणु
				network->rates_ex[i] = info_element->data[i];
#अगर_घोषित CONFIG_LIBIPW_DEBUG
				p += scnम_लिखो(p, माप(rates_str) -
					      (p - rates_str), "%02X ",
					      network->rates_ex[i]);
#पूर्ण_अगर
				अगर (libipw_is_ofdm_rate
				    (info_element->data[i])) अणु
					network->flags |= NETWORK_HAS_OFDM;
					अगर (info_element->data[i] &
					    LIBIPW_BASIC_RATE_MASK)
						network->flags &=
						    ~NETWORK_HAS_CCK;
				पूर्ण
			पूर्ण

			LIBIPW_DEBUG_MGMT("WLAN_EID_EXT_SUPP_RATES: '%s' (%d)\n",
					     rates_str, network->rates_ex_len);
			अवरोध;

		हाल WLAN_EID_DS_PARAMS:
			LIBIPW_DEBUG_MGMT("WLAN_EID_DS_PARAMS: %d\n",
					     info_element->data[0]);
			network->channel = info_element->data[0];
			अवरोध;

		हाल WLAN_EID_FH_PARAMS:
			LIBIPW_DEBUG_MGMT("WLAN_EID_FH_PARAMS: ignored\n");
			अवरोध;

		हाल WLAN_EID_CF_PARAMS:
			LIBIPW_DEBUG_MGMT("WLAN_EID_CF_PARAMS: ignored\n");
			अवरोध;

		हाल WLAN_EID_TIM:
			network->tim.tim_count = info_element->data[0];
			network->tim.tim_period = info_element->data[1];
			LIBIPW_DEBUG_MGMT("WLAN_EID_TIM: partially ignored\n");
			अवरोध;

		हाल WLAN_EID_ERP_INFO:
			network->erp_value = info_element->data[0];
			network->flags |= NETWORK_HAS_ERP_VALUE;
			LIBIPW_DEBUG_MGMT("MFIE_TYPE_ERP_SET: %d\n",
					     network->erp_value);
			अवरोध;

		हाल WLAN_EID_IBSS_PARAMS:
			network->atim_winकरोw = info_element->data[0];
			LIBIPW_DEBUG_MGMT("WLAN_EID_IBSS_PARAMS: %d\n",
					     network->atim_winकरोw);
			अवरोध;

		हाल WLAN_EID_CHALLENGE:
			LIBIPW_DEBUG_MGMT("WLAN_EID_CHALLENGE: ignored\n");
			अवरोध;

		हाल WLAN_EID_VENDOR_SPECIFIC:
			LIBIPW_DEBUG_MGMT("WLAN_EID_VENDOR_SPECIFIC: %d bytes\n",
					     info_element->len);
			अगर (!libipw_parse_qos_info_param_IE(info_element,
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
			पूर्ण
			अवरोध;

		हाल WLAN_EID_RSN:
			LIBIPW_DEBUG_MGMT("WLAN_EID_RSN: %d bytes\n",
					     info_element->len);
			network->rsn_ie_len = min(info_element->len + 2,
						  MAX_WPA_IE_LEN);
			स_नकल(network->rsn_ie, info_element,
			       network->rsn_ie_len);
			अवरोध;

		हाल WLAN_EID_QOS_PARAMETER:
			prपूर्णांकk(KERN_ERR
			       "QoS Error need to parse QOS_PARAMETER IE\n");
			अवरोध;
			/* 802.11h */
		हाल WLAN_EID_PWR_CONSTRAINT:
			network->घातer_स्थिरraपूर्णांक = info_element->data[0];
			network->flags |= NETWORK_HAS_POWER_CONSTRAINT;
			अवरोध;

		हाल WLAN_EID_CHANNEL_SWITCH:
			network->घातer_स्थिरraपूर्णांक = info_element->data[0];
			network->flags |= NETWORK_HAS_CSA;
			अवरोध;

		हाल WLAN_EID_QUIET:
			network->quiet.count = info_element->data[0];
			network->quiet.period = info_element->data[1];
			network->quiet.duration = info_element->data[2];
			network->quiet.offset = info_element->data[3];
			network->flags |= NETWORK_HAS_QUIET;
			अवरोध;

		हाल WLAN_EID_IBSS_DFS:
			network->flags |= NETWORK_HAS_IBSS_DFS;
			अवरोध;

		हाल WLAN_EID_TPC_REPORT:
			network->tpc_report.transmit_घातer =
			    info_element->data[0];
			network->tpc_report.link_margin = info_element->data[1];
			network->flags |= NETWORK_HAS_TPC_REPORT;
			अवरोध;

		शेष:
			LIBIPW_DEBUG_MGMT
			    ("Unsupported info element: %s (%d)\n",
			     get_info_element_string(info_element->id),
			     info_element->id);
			अवरोध;
		पूर्ण

		length -= माप(*info_element) + info_element->len;
		info_element =
		    (काष्ठा libipw_info_element *)&info_element->
		    data[info_element->len];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक libipw_handle_assoc_resp(काष्ठा libipw_device *ieee, काष्ठा libipw_assoc_response
				       *frame, काष्ठा libipw_rx_stats *stats)
अणु
	काष्ठा libipw_network network_resp = अणु पूर्ण;
	काष्ठा libipw_network *network = &network_resp;
	काष्ठा net_device *dev = ieee->dev;

	network->flags = 0;
	network->qos_data.active = 0;
	network->qos_data.supported = 0;
	network->qos_data.param_count = 0;
	network->qos_data.old_param_count = 0;

	//network->atim_winकरोw = le16_to_cpu(frame->aid) & (0x3FFF);
	network->atim_winकरोw = le16_to_cpu(frame->aid);
	network->listen_पूर्णांकerval = le16_to_cpu(frame->status);
	स_नकल(network->bssid, frame->header.addr3, ETH_ALEN);
	network->capability = le16_to_cpu(frame->capability);
	network->last_scanned = jअगरfies;
	network->rates_len = network->rates_ex_len = 0;
	network->last_associate = 0;
	network->ssid_len = 0;
	network->erp_value =
	    (network->capability & WLAN_CAPABILITY_IBSS) ? 0x3 : 0x0;

	अगर (stats->freq == LIBIPW_52GHZ_BAND) अणु
		/* क्रम A band (No DS info) */
		network->channel = stats->received_channel;
	पूर्ण अन्यथा
		network->flags |= NETWORK_HAS_CCK;

	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;

	अगर (libipw_parse_info_param
	    (frame->info_element, stats->len - माप(*frame), network))
		वापस 1;

	network->mode = 0;
	अगर (stats->freq == LIBIPW_52GHZ_BAND)
		network->mode = IEEE_A;
	अन्यथा अणु
		अगर (network->flags & NETWORK_HAS_OFDM)
			network->mode |= IEEE_G;
		अगर (network->flags & NETWORK_HAS_CCK)
			network->mode |= IEEE_B;
	पूर्ण

	स_नकल(&network->stats, stats, माप(network->stats));

	अगर (ieee->handle_assoc_response != शून्य)
		ieee->handle_assoc_response(dev, frame, network);

	वापस 0;
पूर्ण

/***************************************************/

अटल पूर्णांक libipw_network_init(काष्ठा libipw_device *ieee, काष्ठा libipw_probe_response
					 *beacon,
					 काष्ठा libipw_network *network,
					 काष्ठा libipw_rx_stats *stats)
अणु
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
	/* Where to pull this? beacon->listen_पूर्णांकerval; */
	network->listen_पूर्णांकerval = 0x0A;
	network->rates_len = network->rates_ex_len = 0;
	network->last_associate = 0;
	network->ssid_len = 0;
	network->flags = 0;
	network->atim_winकरोw = 0;
	network->erp_value = (network->capability & WLAN_CAPABILITY_IBSS) ?
	    0x3 : 0x0;

	अगर (stats->freq == LIBIPW_52GHZ_BAND) अणु
		/* क्रम A band (No DS info) */
		network->channel = stats->received_channel;
	पूर्ण अन्यथा
		network->flags |= NETWORK_HAS_CCK;

	network->wpa_ie_len = 0;
	network->rsn_ie_len = 0;

	अगर (libipw_parse_info_param
	    (beacon->info_element, stats->len - माप(*beacon), network))
		वापस 1;

	network->mode = 0;
	अगर (stats->freq == LIBIPW_52GHZ_BAND)
		network->mode = IEEE_A;
	अन्यथा अणु
		अगर (network->flags & NETWORK_HAS_OFDM)
			network->mode |= IEEE_G;
		अगर (network->flags & NETWORK_HAS_CCK)
			network->mode |= IEEE_B;
	पूर्ण

	अगर (network->mode == 0) अणु
		LIBIPW_DEBUG_SCAN("Filtered out '%*pE (%pM)' network.\n",
				  network->ssid_len, network->ssid,
				  network->bssid);
		वापस 1;
	पूर्ण

	स_नकल(&network->stats, stats, माप(network->stats));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_same_network(काष्ठा libipw_network *src,
				  काष्ठा libipw_network *dst)
अणु
	/* A network is only a duplicate अगर the channel, BSSID, and ESSID
	 * all match.  We treat all <hidden> with the same BSSID and channel
	 * as one network */
	वापस ((src->ssid_len == dst->ssid_len) &&
		(src->channel == dst->channel) &&
		ether_addr_equal_64bits(src->bssid, dst->bssid) &&
		!स_भेद(src->ssid, dst->ssid, src->ssid_len));
पूर्ण

अटल व्योम update_network(काष्ठा libipw_network *dst,
				  काष्ठा libipw_network *src)
अणु
	पूर्णांक qos_active;
	u8 old_param;

	/* We only update the statistics अगर they were created by receiving
	 * the network inक्रमmation on the actual channel the network is on.
	 *
	 * This keeps beacons received on neighbor channels from bringing
	 * करोwn the संकेत level of an AP. */
	अगर (dst->channel == src->stats.received_channel)
		स_नकल(&dst->stats, &src->stats,
		       माप(काष्ठा libipw_rx_stats));
	अन्यथा
		LIBIPW_DEBUG_SCAN("Network %pM info received "
			"off channel (%d vs. %d)\n", src->bssid,
			dst->channel, src->stats.received_channel);

	dst->capability = src->capability;
	स_नकल(dst->rates, src->rates, src->rates_len);
	dst->rates_len = src->rates_len;
	स_नकल(dst->rates_ex, src->rates_ex, src->rates_ex_len);
	dst->rates_ex_len = src->rates_ex_len;

	dst->mode = src->mode;
	dst->flags = src->flags;
	dst->समय_stamp[0] = src->समय_stamp[0];
	dst->समय_stamp[1] = src->समय_stamp[1];

	dst->beacon_पूर्णांकerval = src->beacon_पूर्णांकerval;
	dst->listen_पूर्णांकerval = src->listen_पूर्णांकerval;
	dst->atim_winकरोw = src->atim_winकरोw;
	dst->erp_value = src->erp_value;
	dst->tim = src->tim;

	स_नकल(dst->wpa_ie, src->wpa_ie, src->wpa_ie_len);
	dst->wpa_ie_len = src->wpa_ie_len;
	स_नकल(dst->rsn_ie, src->rsn_ie, src->rsn_ie_len);
	dst->rsn_ie_len = src->rsn_ie_len;

	dst->last_scanned = jअगरfies;
	qos_active = src->qos_data.active;
	old_param = dst->qos_data.old_param_count;
	अगर (dst->flags & NETWORK_HAS_QOS_MASK)
		स_नकल(&dst->qos_data, &src->qos_data,
		       माप(काष्ठा libipw_qos_data));
	अन्यथा अणु
		dst->qos_data.supported = src->qos_data.supported;
		dst->qos_data.param_count = src->qos_data.param_count;
	पूर्ण

	अगर (dst->qos_data.supported == 1) अणु
		अगर (dst->ssid_len)
			LIBIPW_DEBUG_QOS
			    ("QoS the network %s is QoS supported\n",
			     dst->ssid);
		अन्यथा
			LIBIPW_DEBUG_QOS
			    ("QoS the network is QoS supported\n");
	पूर्ण
	dst->qos_data.active = qos_active;
	dst->qos_data.old_param_count = old_param;

	/* dst->last_associate is not overwritten */
पूर्ण

अटल अंतरभूत पूर्णांक is_beacon(__le16 fc)
अणु
	वापस (WLAN_FC_GET_STYPE(le16_to_cpu(fc)) == IEEE80211_STYPE_BEACON);
पूर्ण

अटल व्योम libipw_process_probe_response(काष्ठा libipw_device
						    *ieee, काष्ठा
						    libipw_probe_response
						    *beacon, काष्ठा libipw_rx_stats
						    *stats)
अणु
	काष्ठा net_device *dev = ieee->dev;
	काष्ठा libipw_network network = अणु पूर्ण;
	काष्ठा libipw_network *target;
	काष्ठा libipw_network *oldest = शून्य;
#अगर_घोषित CONFIG_LIBIPW_DEBUG
	काष्ठा libipw_info_element *info_element = beacon->info_element;
#पूर्ण_अगर
	अचिन्हित दीर्घ flags;

	LIBIPW_DEBUG_SCAN("'%*pE' (%pM): %c%c%c%c %c%c%c%c-%c%c%c%c %c%c%c%c\n",
		     info_element->len, info_element->data,
		     beacon->header.addr3,
		     (beacon->capability & cpu_to_le16(1 << 0xf)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0xe)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0xd)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0xc)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0xb)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0xa)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x9)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x8)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x7)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x6)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x5)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x4)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x3)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x2)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x1)) ? '1' : '0',
		     (beacon->capability & cpu_to_le16(1 << 0x0)) ? '1' : '0');

	अगर (libipw_network_init(ieee, beacon, &network, stats)) अणु
		LIBIPW_DEBUG_SCAN("Dropped '%*pE' (%pM) via %s.\n",
				  info_element->len, info_element->data,
				  beacon->header.addr3,
				  is_beacon(beacon->header.frame_ctl) ?
				  "BEACON" : "PROBE RESPONSE");
		वापस;
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

	list_क्रम_each_entry(target, &ieee->network_list, list) अणु
		अगर (is_same_network(target, &network))
			अवरोध;

		अगर ((oldest == शून्य) ||
		    समय_beक्रमe(target->last_scanned, oldest->last_scanned))
			oldest = target;
	पूर्ण

	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation */
	अगर (&target->list == &ieee->network_list) अणु
		अगर (list_empty(&ieee->network_मुक्त_list)) अणु
			/* If there are no more slots, expire the oldest */
			list_del(&oldest->list);
			target = oldest;
			LIBIPW_DEBUG_SCAN("Expired '%*pE' (%pM) from network list.\n",
					  target->ssid_len, target->ssid,
					  target->bssid);
		पूर्ण अन्यथा अणु
			/* Otherwise just pull from the मुक्त list */
			target = list_entry(ieee->network_मुक्त_list.next,
					    काष्ठा libipw_network, list);
			list_del(ieee->network_मुक्त_list.next);
		पूर्ण

#अगर_घोषित CONFIG_LIBIPW_DEBUG
		LIBIPW_DEBUG_SCAN("Adding '%*pE' (%pM) via %s.\n",
				  network.ssid_len, network.ssid,
				  network.bssid,
				  is_beacon(beacon->header.frame_ctl) ?
				  "BEACON" : "PROBE RESPONSE");
#पूर्ण_अगर
		स_नकल(target, &network, माप(*target));
		list_add_tail(&target->list, &ieee->network_list);
	पूर्ण अन्यथा अणु
		LIBIPW_DEBUG_SCAN("Updating '%*pE' (%pM) via %s.\n",
				  target->ssid_len, target->ssid,
				  target->bssid,
				  is_beacon(beacon->header.frame_ctl) ?
				  "BEACON" : "PROBE RESPONSE");
		update_network(target, &network);
	पूर्ण

	spin_unlock_irqrestore(&ieee->lock, flags);

	अगर (is_beacon(beacon->header.frame_ctl)) अणु
		अगर (ieee->handle_beacon != शून्य)
			ieee->handle_beacon(dev, beacon, target);
	पूर्ण अन्यथा अणु
		अगर (ieee->handle_probe_response != शून्य)
			ieee->handle_probe_response(dev, beacon, target);
	पूर्ण
पूर्ण

व्योम libipw_rx_mgt(काष्ठा libipw_device *ieee,
		      काष्ठा libipw_hdr_4addr *header,
		      काष्ठा libipw_rx_stats *stats)
अणु
	चयन (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl))) अणु
	हाल IEEE80211_STYPE_ASSOC_RESP:
		LIBIPW_DEBUG_MGMT("received ASSOCIATION RESPONSE (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		libipw_handle_assoc_resp(ieee,
					    (काष्ठा libipw_assoc_response *)
					    header, stats);
		अवरोध;

	हाल IEEE80211_STYPE_REASSOC_RESP:
		LIBIPW_DEBUG_MGMT("received REASSOCIATION RESPONSE (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		अवरोध;

	हाल IEEE80211_STYPE_PROBE_REQ:
		LIBIPW_DEBUG_MGMT("received auth (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));

		अगर (ieee->handle_probe_request != शून्य)
			ieee->handle_probe_request(ieee->dev,
						   (काष्ठा
						    libipw_probe_request *)
						   header, stats);
		अवरोध;

	हाल IEEE80211_STYPE_PROBE_RESP:
		LIBIPW_DEBUG_MGMT("received PROBE RESPONSE (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		LIBIPW_DEBUG_SCAN("Probe response\n");
		libipw_process_probe_response(ieee,
						 (काष्ठा
						  libipw_probe_response *)
						 header, stats);
		अवरोध;

	हाल IEEE80211_STYPE_BEACON:
		LIBIPW_DEBUG_MGMT("received BEACON (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		LIBIPW_DEBUG_SCAN("Beacon\n");
		libipw_process_probe_response(ieee,
						 (काष्ठा
						  libipw_probe_response *)
						 header, stats);
		अवरोध;
	हाल IEEE80211_STYPE_AUTH:

		LIBIPW_DEBUG_MGMT("received auth (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));

		अगर (ieee->handle_auth != शून्य)
			ieee->handle_auth(ieee->dev,
					  (काष्ठा libipw_auth *)header);
		अवरोध;

	हाल IEEE80211_STYPE_DISASSOC:
		अगर (ieee->handle_disassoc != शून्य)
			ieee->handle_disassoc(ieee->dev,
					      (काष्ठा libipw_disassoc *)
					      header);
		अवरोध;

	हाल IEEE80211_STYPE_ACTION:
		LIBIPW_DEBUG_MGMT("ACTION\n");
		अगर (ieee->handle_action)
			ieee->handle_action(ieee->dev,
					    (काष्ठा libipw_action *)
					    header, stats);
		अवरोध;

	हाल IEEE80211_STYPE_REASSOC_REQ:
		LIBIPW_DEBUG_MGMT("received reassoc (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));

		LIBIPW_DEBUG_MGMT("%s: LIBIPW_REASSOC_REQ received\n",
				     ieee->dev->name);
		अगर (ieee->handle_reassoc_request != शून्य)
			ieee->handle_reassoc_request(ieee->dev,
						    (काष्ठा libipw_reassoc_request *)
						     header);
		अवरोध;

	हाल IEEE80211_STYPE_ASSOC_REQ:
		LIBIPW_DEBUG_MGMT("received assoc (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));

		LIBIPW_DEBUG_MGMT("%s: LIBIPW_ASSOC_REQ received\n",
				     ieee->dev->name);
		अगर (ieee->handle_assoc_request != शून्य)
			ieee->handle_assoc_request(ieee->dev);
		अवरोध;

	हाल IEEE80211_STYPE_DEAUTH:
		LIBIPW_DEBUG_MGMT("DEAUTH\n");
		अगर (ieee->handle_deauth != शून्य)
			ieee->handle_deauth(ieee->dev,
					    (काष्ठा libipw_deauth *)
					    header);
		अवरोध;
	शेष:
		LIBIPW_DEBUG_MGMT("received UNKNOWN (%d)\n",
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		LIBIPW_DEBUG_MGMT("%s: Unknown management packet: %d\n",
				     ieee->dev->name,
				     WLAN_FC_GET_STYPE(le16_to_cpu
						       (header->frame_ctl)));
		अवरोध;
	पूर्ण
पूर्ण

EXPORT_SYMBOL_GPL(libipw_rx_any);
EXPORT_SYMBOL(libipw_rx_mgt);
EXPORT_SYMBOL(libipw_rx);
