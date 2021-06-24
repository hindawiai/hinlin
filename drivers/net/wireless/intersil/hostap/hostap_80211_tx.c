<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>

#समावेश "hostap_80211.h"
#समावेश "hostap_common.h"
#समावेश "hostap_wlan.h"
#समावेश "hostap.h"
#समावेश "hostap_ap.h"

/* See IEEE 802.1H क्रम LLC/SNAP encapsulation/decapsulation */
/* Ethernet-II snap header (RFC1042 क्रम most EtherTypes) */
अटल अचिन्हित अक्षर rfc1042_header[] =
अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 पूर्ण;
/* Bridge-Tunnel header (क्रम EtherTypes ETH_P_AARP and ETH_P_IPX) */
अटल अचिन्हित अक्षर bridge_tunnel_header[] =
अणु 0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 पूर्ण;
/* No encapsulation header अगर EtherType < 0x600 (=length) */

व्योम hostap_dump_tx_80211(स्थिर अक्षर *name, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	prपूर्णांकk(KERN_DEBUG "%s: TX len=%d jiffies=%ld\n",
	       name, skb->len, jअगरfies);

	अगर (skb->len < 2)
		वापस;

	fc = le16_to_cpu(hdr->frame_control);
	prपूर्णांकk(KERN_DEBUG "   FC=0x%04x (type=%d:%d)%s%s",
	       fc, (fc & IEEE80211_FCTL_FTYPE) >> 2,
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       fc & IEEE80211_FCTL_TODS ? " [ToDS]" : "",
	       fc & IEEE80211_FCTL_FROMDS ? " [FromDS]" : "");

	अगर (skb->len < IEEE80211_DATA_HDR3_LEN) अणु
		prपूर्णांकk("\n");
		वापस;
	पूर्ण

	prपूर्णांकk(" dur=0x%04x seq=0x%04x\n", le16_to_cpu(hdr->duration_id),
	       le16_to_cpu(hdr->seq_ctrl));

	prपूर्णांकk(KERN_DEBUG "   A1=%pM", hdr->addr1);
	prपूर्णांकk(" A2=%pM", hdr->addr2);
	prपूर्णांकk(" A3=%pM", hdr->addr3);
	अगर (skb->len >= 30)
		prपूर्णांकk(" A4=%pM", hdr->addr4);
	prपूर्णांकk("\n");
पूर्ण


/* hard_start_xmit function क्रम data पूर्णांकerfaces (wlan#, wlan#wds#, wlan#sta)
 * Convert Ethernet header पूर्णांकo a suitable IEEE 802.11 header depending on
 * device configuration. */
netdev_tx_t hostap_data_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक need_headroom, need_tailroom = 0;
	काष्ठा ieee80211_hdr hdr;
	u16 fc, ethertype = 0;
	क्रमागत अणु
		WDS_NO = 0, WDS_OWN_FRAME, WDS_COMPLIANT_FRAME
	पूर्ण use_wds = WDS_NO;
	u8 *encaps_data;
	पूर्णांक hdr_len, encaps_len, skip_header_bytes;
	पूर्णांक to_assoc_ap = 0;
	काष्ठा hostap_skb_tx_data *meta;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (skb->len < ETH_HLEN) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_data_start_xmit: short skb "
		       "(len=%d)\n", dev->name, skb->len);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (local->ddev != dev) अणु
		use_wds = (local->iw_mode == IW_MODE_MASTER &&
			   !(local->wds_type & HOSTAP_WDS_STANDARD_FRAME)) ?
			WDS_OWN_FRAME : WDS_COMPLIANT_FRAME;
		अगर (dev == local->stadev) अणु
			to_assoc_ap = 1;
			use_wds = WDS_NO;
		पूर्ण अन्यथा अगर (dev == local->apdev) अणु
			prपूर्णांकk(KERN_DEBUG "%s: prism2_tx: trying to use "
			       "AP device with Ethernet net dev\n", dev->name);
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (local->iw_mode == IW_MODE_REPEAT) अणु
			prपूर्णांकk(KERN_DEBUG "%s: prism2_tx: trying to use "
			       "non-WDS link in Repeater mode\n", dev->name);
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण अन्यथा अगर (local->iw_mode == IW_MODE_INFRA &&
			   (local->wds_type & HOSTAP_WDS_AP_CLIENT) &&
			   !ether_addr_equal(skb->data + ETH_ALEN, dev->dev_addr)) अणु
			/* AP client mode: send frames with क्रमeign src addr
			 * using 4-addr WDS frames */
			use_wds = WDS_COMPLIANT_FRAME;
		पूर्ण
	पूर्ण

	/* Incoming skb->data: dst_addr[6], src_addr[6], proto[2], payload
	 * ==>
	 * Prism2 TX frame with 802.11 header:
	 * txdesc (address order depending on used mode; includes dst_addr and
	 * src_addr), possible encapsulation (RFC1042/Bridge-Tunnel;
	 * proto[2], payload अणु, possible addr4[6]पूर्ण */

	ethertype = (skb->data[12] << 8) | skb->data[13];

	स_रखो(&hdr, 0, माप(hdr));

	/* Length of data after IEEE 802.11 header */
	encaps_data = शून्य;
	encaps_len = 0;
	skip_header_bytes = ETH_HLEN;
	अगर (ethertype == ETH_P_AARP || ethertype == ETH_P_IPX) अणु
		encaps_data = bridge_tunnel_header;
		encaps_len = माप(bridge_tunnel_header);
		skip_header_bytes -= 2;
	पूर्ण अन्यथा अगर (ethertype >= 0x600) अणु
		encaps_data = rfc1042_header;
		encaps_len = माप(rfc1042_header);
		skip_header_bytes -= 2;
	पूर्ण

	fc = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA;
	hdr_len = IEEE80211_DATA_HDR3_LEN;

	अगर (use_wds != WDS_NO) अणु
		/* Note! Prism2 station firmware has problems with sending real
		 * 802.11 frames with four addresses; until these problems can
		 * be fixed or worked around, 4-addr frames needed क्रम WDS are
		 * using incompatible क्रमmat: FromDS flag is not set and the
		 * fourth address is added after the frame payload; it is
		 * assumed, that the receiving station knows how to handle this
		 * frame क्रमmat */

		अगर (use_wds == WDS_COMPLIANT_FRAME) अणु
			fc |= IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS;
			/* From&To DS: Addr1 = RA, Addr2 = TA, Addr3 = DA,
			 * Addr4 = SA */
			skb_copy_from_linear_data_offset(skb, ETH_ALEN,
							 &hdr.addr4, ETH_ALEN);
			hdr_len += ETH_ALEN;
		पूर्ण अन्यथा अणु
			/* bogus 4-addr क्रमmat to workaround Prism2 station
			 * f/w bug */
			fc |= IEEE80211_FCTL_TODS;
			/* From DS: Addr1 = DA (used as RA),
			 * Addr2 = BSSID (used as TA), Addr3 = SA (used as DA),
			 */

			/* SA from skb->data + ETH_ALEN will be added after
			 * frame payload; use hdr.addr4 as a temporary buffer
			 */
			skb_copy_from_linear_data_offset(skb, ETH_ALEN,
							 &hdr.addr4, ETH_ALEN);
			need_tailroom += ETH_ALEN;
		पूर्ण

		/* send broadcast and multicast frames to broadcast RA, अगर
		 * configured; otherwise, use unicast RA of the WDS link */
		अगर ((local->wds_type & HOSTAP_WDS_BROADCAST_RA) &&
		    is_multicast_ether_addr(skb->data))
			eth_broadcast_addr(hdr.addr1);
		अन्यथा अगर (अगरace->type == HOSTAP_INTERFACE_WDS)
			स_नकल(&hdr.addr1, अगरace->u.wds.remote_addr,
			       ETH_ALEN);
		अन्यथा
			स_नकल(&hdr.addr1, local->bssid, ETH_ALEN);
		स_नकल(&hdr.addr2, dev->dev_addr, ETH_ALEN);
		skb_copy_from_linear_data(skb, &hdr.addr3, ETH_ALEN);
	पूर्ण अन्यथा अगर (local->iw_mode == IW_MODE_MASTER && !to_assoc_ap) अणु
		fc |= IEEE80211_FCTL_FROMDS;
		/* From DS: Addr1 = DA, Addr2 = BSSID, Addr3 = SA */
		skb_copy_from_linear_data(skb, &hdr.addr1, ETH_ALEN);
		स_नकल(&hdr.addr2, dev->dev_addr, ETH_ALEN);
		skb_copy_from_linear_data_offset(skb, ETH_ALEN, &hdr.addr3,
						 ETH_ALEN);
	पूर्ण अन्यथा अगर (local->iw_mode == IW_MODE_INFRA || to_assoc_ap) अणु
		fc |= IEEE80211_FCTL_TODS;
		/* To DS: Addr1 = BSSID, Addr2 = SA, Addr3 = DA */
		स_नकल(&hdr.addr1, to_assoc_ap ?
		       local->assoc_ap_addr : local->bssid, ETH_ALEN);
		skb_copy_from_linear_data_offset(skb, ETH_ALEN, &hdr.addr2,
						 ETH_ALEN);
		skb_copy_from_linear_data(skb, &hdr.addr3, ETH_ALEN);
	पूर्ण अन्यथा अगर (local->iw_mode == IW_MODE_ADHOC) अणु
		/* not From/To DS: Addr1 = DA, Addr2 = SA, Addr3 = BSSID */
		skb_copy_from_linear_data(skb, &hdr.addr1, ETH_ALEN);
		skb_copy_from_linear_data_offset(skb, ETH_ALEN, &hdr.addr2,
						 ETH_ALEN);
		स_नकल(&hdr.addr3, local->bssid, ETH_ALEN);
	पूर्ण

	hdr.frame_control = cpu_to_le16(fc);

	skb_pull(skb, skip_header_bytes);
	need_headroom = local->func->need_tx_headroom + hdr_len + encaps_len;
	अगर (skb_tailroom(skb) < need_tailroom) अणु
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (skb == शून्य) अणु
			अगरace->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
		अगर (pskb_expand_head(skb, need_headroom, need_tailroom,
				     GFP_ATOMIC)) अणु
			kमुक्त_skb(skb);
			अगरace->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण अन्यथा अगर (skb_headroom(skb) < need_headroom) अणु
		काष्ठा sk_buff *पंचांगp = skb;
		skb = skb_पुनः_स्मृति_headroom(skb, need_headroom);
		kमुक्त_skb(पंचांगp);
		अगर (skb == शून्य) अणु
			अगरace->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (skb == शून्य) अणु
			अगरace->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	अगर (encaps_data)
		स_नकल(skb_push(skb, encaps_len), encaps_data, encaps_len);
	स_नकल(skb_push(skb, hdr_len), &hdr, hdr_len);
	अगर (use_wds == WDS_OWN_FRAME) अणु
		skb_put_data(skb, &hdr.addr4, ETH_ALEN);
	पूर्ण

	अगरace->stats.tx_packets++;
	अगरace->stats.tx_bytes += skb->len;

	skb_reset_mac_header(skb);
	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	स_रखो(meta, 0, माप(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	अगर (use_wds)
		meta->flags |= HOSTAP_TX_FLAGS_WDS;
	meta->ethertype = ethertype;
	meta->अगरace = अगरace;

	/* Send IEEE 802.11 encapsulated frame using the master radio device */
	skb->dev = local->dev;
	dev_queue_xmit(skb);
	वापस NETDEV_TX_OK;
पूर्ण


/* hard_start_xmit function क्रम hostapd wlan#ap पूर्णांकerfaces */
netdev_tx_t hostap_mgmt_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hostap_skb_tx_data *meta;
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (skb->len < 10) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_mgmt_start_xmit: short skb "
		       "(len=%d)\n", dev->name, skb->len);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगरace->stats.tx_packets++;
	अगरace->stats.tx_bytes += skb->len;

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	स_रखो(meta, 0, माप(*meta));
	meta->magic = HOSTAP_SKB_TX_DATA_MAGIC;
	meta->अगरace = अगरace;

	अगर (skb->len >= IEEE80211_DATA_HDR3_LEN + माप(rfc1042_header) + 2) अणु
		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		fc = le16_to_cpu(hdr->frame_control);
		अगर (ieee80211_is_data(hdr->frame_control) &&
		    (fc & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_DATA) अणु
			u8 *pos = &skb->data[IEEE80211_DATA_HDR3_LEN +
					     माप(rfc1042_header)];
			meta->ethertype = (pos[0] << 8) | pos[1];
		पूर्ण
	पूर्ण

	/* Send IEEE 802.11 encapsulated frame using the master radio device */
	skb->dev = local->dev;
	dev_queue_xmit(skb);
	वापस NETDEV_TX_OK;
पूर्ण


/* Called only from software IRQ */
अटल काष्ठा sk_buff * hostap_tx_encrypt(काष्ठा sk_buff *skb,
					  काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक prefix_len, postfix_len, hdr_len, res;

	अगरace = netdev_priv(skb->dev);
	local = अगरace->local;

	अगर (skb->len < IEEE80211_DATA_HDR3_LEN) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	अगर (local->tkip_countermeasures &&
	    म_भेद(crypt->ops->name, "TKIP") == 0) अणु
		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: TKIP countermeasures: dropped "
			       "TX packet to %pM\n",
			       local->dev->name, hdr->addr1);
		पूर्ण
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस शून्य;

	prefix_len = crypt->ops->extra_mpdu_prefix_len +
		crypt->ops->extra_msdu_prefix_len;
	postfix_len = crypt->ops->extra_mpdu_postfix_len +
		crypt->ops->extra_msdu_postfix_len;
	अगर ((skb_headroom(skb) < prefix_len ||
	     skb_tailroom(skb) < postfix_len) &&
	    pskb_expand_head(skb, prefix_len, postfix_len, GFP_ATOMIC)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdr_len = hostap_80211_get_hdrlen(hdr->frame_control);

	/* Host-based IEEE 802.11 fragmentation क्रम TX is not yet supported, so
	 * call both MSDU and MPDU encryption functions from here. */
	atomic_inc(&crypt->refcnt);
	res = 0;
	अगर (crypt->ops->encrypt_msdu)
		res = crypt->ops->encrypt_msdu(skb, hdr_len, crypt->priv);
	अगर (res == 0 && crypt->ops->encrypt_mpdu)
		res = crypt->ops->encrypt_mpdu(skb, hdr_len, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	वापस skb;
पूर्ण


/* hard_start_xmit function क्रम master radio पूर्णांकerface wअगरi#.
 * AP processing (TX rate control, घातer save buffering, etc.).
 * Use hardware TX function to send the frame. */
netdev_tx_t hostap_master_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	netdev_tx_t ret = NETDEV_TX_BUSY;
	u16 fc;
	काष्ठा hostap_tx_data tx;
	ap_tx_ret tx_ret;
	काष्ठा hostap_skb_tx_data *meta;
	पूर्णांक no_encrypt = 0;
	काष्ठा ieee80211_hdr *hdr;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	tx.skb = skb;
	tx.sta_ptr = शून्य;

	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	अगर (meta->magic != HOSTAP_SKB_TX_DATA_MAGIC) अणु
		prपूर्णांकk(KERN_DEBUG "%s: invalid skb->cb magic (0x%08x, "
		       "expected 0x%08x)\n",
		       dev->name, meta->magic, HOSTAP_SKB_TX_DATA_MAGIC);
		ret = NETDEV_TX_OK;
		अगरace->stats.tx_dropped++;
		जाओ fail;
	पूर्ण

	अगर (local->host_encrypt) अणु
		/* Set crypt to शेष algorithm and key; will be replaced in
		 * AP code अगर STA has own alg/key */
		tx.crypt = local->crypt_info.crypt[local->crypt_info.tx_keyidx];
		tx.host_encrypt = 1;
	पूर्ण अन्यथा अणु
		tx.crypt = शून्य;
		tx.host_encrypt = 0;
	पूर्ण

	अगर (skb->len < 24) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_master_start_xmit: short skb "
		       "(len=%d)\n", dev->name, skb->len);
		ret = NETDEV_TX_OK;
		अगरace->stats.tx_dropped++;
		जाओ fail;
	पूर्ण

	/* FIX (?):
	 * Wi-Fi 802.11b test plan suggests that AP should ignore घातer save
	 * bit in authentication and (re)association frames and assume tha
	 * STA reमुख्यs awake क्रम the response. */
	tx_ret = hostap_handle_sta_tx(local, &tx);
	skb = tx.skb;
	meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(hdr->frame_control);
	चयन (tx_ret) अणु
	हाल AP_TX_CONTINUE:
		अवरोध;
	हाल AP_TX_CONTINUE_NOT_AUTHORIZED:
		अगर (local->ieee_802_1x &&
		    ieee80211_is_data(hdr->frame_control) &&
		    meta->ethertype != ETH_P_PAE &&
		    !(meta->flags & HOSTAP_TX_FLAGS_WDS)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped frame to unauthorized "
			       "port (IEEE 802.1X): ethertype=0x%04x\n",
			       dev->name, meta->ethertype);
			hostap_dump_tx_80211(dev->name, skb);

			ret = NETDEV_TX_OK; /* drop packet */
			अगरace->stats.tx_dropped++;
			जाओ fail;
		पूर्ण
		अवरोध;
	हाल AP_TX_DROP:
		ret = NETDEV_TX_OK; /* drop packet */
		अगरace->stats.tx_dropped++;
		जाओ fail;
	हाल AP_TX_RETRY:
		जाओ fail;
	हाल AP_TX_BUFFERED:
		/* करो not मुक्त skb here, it will be मुक्तd when the
		 * buffered frame is sent/समयd out */
		ret = NETDEV_TX_OK;
		जाओ tx_निकास;
	पूर्ण

	/* Request TX callback अगर protocol version is 2 in 802.11 header;
	 * this version 2 is a special हाल used between hostapd and kernel
	 * driver */
	अगर (((fc & IEEE80211_FCTL_VERS) == BIT(1)) &&
	    local->ap && local->ap->tx_callback_idx && meta->tx_cb_idx == 0) अणु
		meta->tx_cb_idx = local->ap->tx_callback_idx;

		/* हटाओ special version from the frame header */
		fc &= ~IEEE80211_FCTL_VERS;
		hdr->frame_control = cpu_to_le16(fc);
	पूर्ण

	अगर (!ieee80211_is_data(hdr->frame_control)) अणु
		no_encrypt = 1;
		tx.crypt = शून्य;
	पूर्ण

	अगर (local->ieee_802_1x && meta->ethertype == ETH_P_PAE && tx.crypt &&
	    !(fc & IEEE80211_FCTL_PROTECTED)) अणु
		no_encrypt = 1;
		PDEBUG(DEBUG_EXTRA2, "%s: TX: IEEE 802.1X - passing "
		       "unencrypted EAPOL frame\n", dev->name);
		tx.crypt = शून्य; /* no encryption क्रम IEEE 802.1X frames */
	पूर्ण

	अगर (tx.crypt && (!tx.crypt->ops || !tx.crypt->ops->encrypt_mpdu))
		tx.crypt = शून्य;
	अन्यथा अगर ((tx.crypt ||
		 local->crypt_info.crypt[local->crypt_info.tx_keyidx]) &&
		 !no_encrypt) अणु
		/* Add ISWEP flag both क्रम firmware and host based encryption
		 */
		fc |= IEEE80211_FCTL_PROTECTED;
		hdr->frame_control = cpu_to_le16(fc);
	पूर्ण अन्यथा अगर (local->drop_unencrypted &&
		   ieee80211_is_data(hdr->frame_control) &&
		   meta->ethertype != ETH_P_PAE) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped unencrypted TX data "
			       "frame (drop_unencrypted=1)\n", dev->name);
		पूर्ण
		अगरace->stats.tx_dropped++;
		ret = NETDEV_TX_OK;
		जाओ fail;
	पूर्ण

	अगर (tx.crypt) अणु
		skb = hostap_tx_encrypt(skb, tx.crypt);
		अगर (skb == शून्य) अणु
			prपूर्णांकk(KERN_DEBUG "%s: TX - encryption failed\n",
			       dev->name);
			ret = NETDEV_TX_OK;
			जाओ fail;
		पूर्ण
		meta = (काष्ठा hostap_skb_tx_data *) skb->cb;
		अगर (meta->magic != HOSTAP_SKB_TX_DATA_MAGIC) अणु
			prपूर्णांकk(KERN_DEBUG "%s: invalid skb->cb magic (0x%08x, "
			       "expected 0x%08x) after hostap_tx_encrypt\n",
			       dev->name, meta->magic,
			       HOSTAP_SKB_TX_DATA_MAGIC);
			ret = NETDEV_TX_OK;
			अगरace->stats.tx_dropped++;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (local->func->tx == शून्य || local->func->tx(skb, dev)) अणु
		ret = NETDEV_TX_OK;
		अगरace->stats.tx_dropped++;
	पूर्ण अन्यथा अणु
		ret = NETDEV_TX_OK;
		अगरace->stats.tx_packets++;
		अगरace->stats.tx_bytes += skb->len;
	पूर्ण

 fail:
	अगर (ret == NETDEV_TX_OK && skb)
		dev_kमुक्त_skb(skb);
 tx_निकास:
	अगर (tx.sta_ptr)
		hostap_handle_sta_release(tx.sta_ptr);
	वापस ret;
पूर्ण


EXPORT_SYMBOL(hostap_master_start_xmit);
