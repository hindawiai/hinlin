<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

  Copyright(c) 2003 - 2005 Intel Corporation. All rights reserved.


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

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
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>

#समावेश "libipw.h"

/*

802.11 Data Frame

      ,-------------------------------------------------------------------.
Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
      |------|------|---------|---------|---------|------|---------|------|
Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  Frame  |  fcs |
      |      | tion | (BSSID) |         |         | ence |  data   |      |
      `--------------------------------------------------|         |------'
Total: 28 non-data bytes                                 `----.----'
							      |
       .- 'Frame data' expands, if WEP enabled, to <----------'
       |
       V
      ,-----------------------.
Bytes |  4  |   0-2296  |  4  |
      |-----|-----------|-----|
Desc. | IV  | Encrypted | ICV |
      |     | Packet    |     |
      `-----|           |-----'
	    `-----.-----'
		  |
       .- 'Encrypted Packet' expands to
       |
       V
      ,---------------------------------------------------.
Bytes |  1   |  1   |    1    |    3     |  2   |  0-2304 |
      |------|------|---------|----------|------|---------|
Desc. | SNAP | SNAP | Control |Eth Tunnel| Type | IP      |
      | DSAP | SSAP |         |          |      | Packet  |
      | 0xAA | 0xAA |0x03 (UI)|0x00-00-F8|      |         |
      `----------------------------------------------------
Total: 8 non-data bytes

802.3 Ethernet Data Frame

      ,-----------------------------------------.
Bytes |   6   |   6   |  2   |  Variable |   4  |
      |-------|-------|------|-----------|------|
Desc. | Dest. | Source| Type | IP Packet |  fcs |
      |  MAC  |  MAC  |      |           |      |
      `-----------------------------------------'
Total: 18 non-data bytes

In the event that fragmentation is required, the incoming payload is split पूर्णांकo
N parts of size ieee->fts.  The first fragment contains the SNAP header and the
reमुख्यing packets are just data.

If encryption is enabled, each fragment payload size is reduced by enough space
to add the prefix and postfix (IV and ICV totalling 8 bytes in the हाल of WEP)
So अगर you have 1500 bytes of payload with ieee->fts set to 500 without
encryption it will take 3 frames.  With WEP it will take 4 frames as the
payload of each frame is reduced to 492 bytes.

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

अटल पूर्णांक libipw_copy_snap(u8 * data, __be16 h_proto)
अणु
	काष्ठा libipw_snap_hdr *snap;
	u8 *oui;

	snap = (काष्ठा libipw_snap_hdr *)data;
	snap->dsap = 0xaa;
	snap->ssap = 0xaa;
	snap->ctrl = 0x03;

	अगर (h_proto == htons(ETH_P_AARP) || h_proto == htons(ETH_P_IPX))
		oui = P802_1H_OUI;
	अन्यथा
		oui = RFC1042_OUI;
	snap->oui[0] = oui[0];
	snap->oui[1] = oui[1];
	snap->oui[2] = oui[2];

	स_नकल(data + SNAP_SIZE, &h_proto, माप(u16));

	वापस SNAP_SIZE + माप(u16);
पूर्ण

अटल पूर्णांक libipw_encrypt_fragment(काष्ठा libipw_device *ieee,
					     काष्ठा sk_buff *frag, पूर्णांक hdr_len)
अणु
	काष्ठा lib80211_crypt_data *crypt =
		ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];
	पूर्णांक res;

	अगर (crypt == शून्य)
		वापस -1;

	/* To encrypt, frame क्रमmat is:
	 * IV (4 bytes), clear payload (including SNAP), ICV (4 bytes) */
	atomic_inc(&crypt->refcnt);
	res = 0;
	अगर (crypt->ops && crypt->ops->encrypt_mpdu)
		res = crypt->ops->encrypt_mpdu(frag, hdr_len, crypt->priv);

	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_INFO "%s: Encryption failed: len=%d.\n",
		       ieee->dev->name, frag->len);
		ieee->ieee_stats.tx_discards++;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम libipw_txb_मुक्त(काष्ठा libipw_txb *txb)
अणु
	पूर्णांक i;
	अगर (unlikely(!txb))
		वापस;
	क्रम (i = 0; i < txb->nr_frags; i++)
		अगर (txb->fragments[i])
			dev_kमुक्त_skb_any(txb->fragments[i]);
	kमुक्त(txb);
पूर्ण

अटल काष्ठा libipw_txb *libipw_alloc_txb(पूर्णांक nr_frags, पूर्णांक txb_size,
						 पूर्णांक headroom, gfp_t gfp_mask)
अणु
	काष्ठा libipw_txb *txb;
	पूर्णांक i;
	txb = kदो_स्मृति(माप(काष्ठा libipw_txb) + (माप(u8 *) * nr_frags),
		      gfp_mask);
	अगर (!txb)
		वापस शून्य;

	स_रखो(txb, 0, माप(काष्ठा libipw_txb));
	txb->nr_frags = nr_frags;
	txb->frag_size = txb_size;

	क्रम (i = 0; i < nr_frags; i++) अणु
		txb->fragments[i] = __dev_alloc_skb(txb_size + headroom,
						    gfp_mask);
		अगर (unlikely(!txb->fragments[i])) अणु
			i--;
			अवरोध;
		पूर्ण
		skb_reserve(txb->fragments[i], headroom);
	पूर्ण
	अगर (unlikely(i != nr_frags)) अणु
		जबतक (i >= 0)
			dev_kमुक्त_skb_any(txb->fragments[i--]);
		kमुक्त(txb);
		वापस शून्य;
	पूर्ण
	वापस txb;
पूर्ण

अटल पूर्णांक libipw_classअगरy(काष्ठा sk_buff *skb)
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

/* Incoming skb is converted to a txb which consists of
 * a block of 802.11 fragment packets (stored as skbs) */
netdev_tx_t libipw_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा libipw_device *ieee = netdev_priv(dev);
	काष्ठा libipw_txb *txb = शून्य;
	काष्ठा libipw_hdr_3addrqos *frag_hdr;
	पूर्णांक i, bytes_per_frag, nr_frags, bytes_last_frag, frag_size,
	    rts_required;
	अचिन्हित दीर्घ flags;
	पूर्णांक encrypt, host_encrypt, host_encrypt_msdu;
	__be16 ether_type;
	पूर्णांक bytes, fc, hdr_len;
	काष्ठा sk_buff *skb_frag;
	काष्ठा libipw_hdr_3addrqos header = अणु/* Ensure zero initialized */
		.duration_id = 0,
		.seq_ctl = 0,
		.qos_ctl = 0
	पूर्ण;
	u8 dest[ETH_ALEN], src[ETH_ALEN];
	काष्ठा lib80211_crypt_data *crypt;
	पूर्णांक priority = skb->priority;
	पूर्णांक snapped = 0;

	अगर (ieee->is_queue_full && (*ieee->is_queue_full) (dev, priority))
		वापस NETDEV_TX_BUSY;

	spin_lock_irqsave(&ieee->lock, flags);

	/* If there is no driver handler to take the TXB, करोnt' bother
	 * creating it... */
	अगर (!ieee->hard_start_xmit) अणु
		prपूर्णांकk(KERN_WARNING "%s: No xmit handler.\n", ieee->dev->name);
		जाओ success;
	पूर्ण

	अगर (unlikely(skb->len < SNAP_SIZE + माप(u16))) अणु
		prपूर्णांकk(KERN_WARNING "%s: skb too small (%d).\n",
		       ieee->dev->name, skb->len);
		जाओ success;
	पूर्ण

	ether_type = ((काष्ठा ethhdr *)skb->data)->h_proto;

	crypt = ieee->crypt_info.crypt[ieee->crypt_info.tx_keyidx];

	encrypt = !(ether_type == htons(ETH_P_PAE) && ieee->ieee802_1x) &&
	    ieee->sec.encrypt;

	host_encrypt = ieee->host_encrypt && encrypt && crypt;
	host_encrypt_msdu = ieee->host_encrypt_msdu && encrypt && crypt;

	अगर (!encrypt && ieee->ieee802_1x &&
	    ieee->drop_unencrypted && ether_type != htons(ETH_P_PAE)) अणु
		dev->stats.tx_dropped++;
		जाओ success;
	पूर्ण

	/* Save source and destination addresses */
	skb_copy_from_linear_data(skb, dest, ETH_ALEN);
	skb_copy_from_linear_data_offset(skb, ETH_ALEN, src, ETH_ALEN);

	अगर (host_encrypt)
		fc = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA |
		    IEEE80211_FCTL_PROTECTED;
	अन्यथा
		fc = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA;

	अगर (ieee->iw_mode == IW_MODE_INFRA) अणु
		fc |= IEEE80211_FCTL_TODS;
		/* To DS: Addr1 = BSSID, Addr2 = SA, Addr3 = DA */
		स_नकल(header.addr1, ieee->bssid, ETH_ALEN);
		स_नकल(header.addr2, src, ETH_ALEN);
		स_नकल(header.addr3, dest, ETH_ALEN);
	पूर्ण अन्यथा अगर (ieee->iw_mode == IW_MODE_ADHOC) अणु
		/* not From/To DS: Addr1 = DA, Addr2 = SA, Addr3 = BSSID */
		स_नकल(header.addr1, dest, ETH_ALEN);
		स_नकल(header.addr2, src, ETH_ALEN);
		स_नकल(header.addr3, ieee->bssid, ETH_ALEN);
	पूर्ण
	hdr_len = LIBIPW_3ADDR_LEN;

	अगर (ieee->is_qos_active && ieee->is_qos_active(dev, skb)) अणु
		fc |= IEEE80211_STYPE_QOS_DATA;
		hdr_len += 2;

		skb->priority = libipw_classअगरy(skb);
		header.qos_ctl |= cpu_to_le16(skb->priority & LIBIPW_QCTL_TID);
	पूर्ण
	header.frame_ctl = cpu_to_le16(fc);

	/* Advance the SKB to the start of the payload */
	skb_pull(skb, माप(काष्ठा ethhdr));

	/* Determine total amount of storage required क्रम TXB packets */
	bytes = skb->len + SNAP_SIZE + माप(u16);

	/* Encrypt msdu first on the whole data packet. */
	अगर ((host_encrypt || host_encrypt_msdu) &&
	    crypt && crypt->ops && crypt->ops->encrypt_msdu) अणु
		पूर्णांक res = 0;
		पूर्णांक len = bytes + hdr_len + crypt->ops->extra_msdu_prefix_len +
		    crypt->ops->extra_msdu_postfix_len;
		काष्ठा sk_buff *skb_new = dev_alloc_skb(len);

		अगर (unlikely(!skb_new))
			जाओ failed;

		skb_reserve(skb_new, crypt->ops->extra_msdu_prefix_len);
		skb_put_data(skb_new, &header, hdr_len);
		snapped = 1;
		libipw_copy_snap(skb_put(skb_new, SNAP_SIZE + माप(u16)),
				    ether_type);
		skb_copy_from_linear_data(skb, skb_put(skb_new, skb->len), skb->len);
		res = crypt->ops->encrypt_msdu(skb_new, hdr_len, crypt->priv);
		अगर (res < 0) अणु
			LIBIPW_ERROR("msdu encryption failed\n");
			dev_kमुक्त_skb_any(skb_new);
			जाओ failed;
		पूर्ण
		dev_kमुक्त_skb_any(skb);
		skb = skb_new;
		bytes += crypt->ops->extra_msdu_prefix_len +
		    crypt->ops->extra_msdu_postfix_len;
		skb_pull(skb, hdr_len);
	पूर्ण

	अगर (host_encrypt || ieee->host_खोलो_frag) अणु
		/* Determine fragmentation size based on destination (multicast
		 * and broadcast are not fragmented) */
		अगर (is_multicast_ether_addr(dest) ||
		    is_broadcast_ether_addr(dest))
			frag_size = MAX_FRAG_THRESHOLD;
		अन्यथा
			frag_size = ieee->fts;

		/* Determine amount of payload per fragment.  Regardless of अगर
		 * this stack is providing the full 802.11 header, one will
		 * eventually be affixed to this fragment -- so we must account
		 * क्रम it when determining the amount of payload space. */
		bytes_per_frag = frag_size - hdr_len;
		अगर (ieee->config &
		    (CFG_LIBIPW_COMPUTE_FCS | CFG_LIBIPW_RESERVE_FCS))
			bytes_per_frag -= LIBIPW_FCS_LEN;

		/* Each fragment may need to have room क्रम encryption
		 * pre/postfix */
		अगर (host_encrypt)
			bytes_per_frag -= crypt->ops->extra_mpdu_prefix_len +
			    crypt->ops->extra_mpdu_postfix_len;

		/* Number of fragments is the total
		 * bytes_per_frag / payload_per_fragment */
		nr_frags = bytes / bytes_per_frag;
		bytes_last_frag = bytes % bytes_per_frag;
		अगर (bytes_last_frag)
			nr_frags++;
		अन्यथा
			bytes_last_frag = bytes_per_frag;
	पूर्ण अन्यथा अणु
		nr_frags = 1;
		bytes_per_frag = bytes_last_frag = bytes;
		frag_size = bytes + hdr_len;
	पूर्ण

	rts_required = (frag_size > ieee->rts
			&& ieee->config & CFG_LIBIPW_RTS);
	अगर (rts_required)
		nr_frags++;

	/* When we allocate the TXB we allocate enough space क्रम the reserve
	 * and full fragment bytes (bytes_per_frag करोesn't include prefix,
	 * postfix, header, FCS, etc.) */
	txb = libipw_alloc_txb(nr_frags, frag_size,
				  ieee->tx_headroom, GFP_ATOMIC);
	अगर (unlikely(!txb)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Could not allocate TXB\n",
		       ieee->dev->name);
		जाओ failed;
	पूर्ण
	txb->encrypted = encrypt;
	अगर (host_encrypt)
		txb->payload_size = frag_size * (nr_frags - 1) +
		    bytes_last_frag;
	अन्यथा
		txb->payload_size = bytes;

	अगर (rts_required) अणु
		skb_frag = txb->fragments[0];
		frag_hdr = skb_put(skb_frag, hdr_len);

		/*
		 * Set header frame_ctl to the RTS.
		 */
		header.frame_ctl =
		    cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);
		स_नकल(frag_hdr, &header, hdr_len);

		/*
		 * Restore header frame_ctl to the original data setting.
		 */
		header.frame_ctl = cpu_to_le16(fc);

		अगर (ieee->config &
		    (CFG_LIBIPW_COMPUTE_FCS | CFG_LIBIPW_RESERVE_FCS))
			skb_put(skb_frag, 4);

		txb->rts_included = 1;
		i = 1;
	पूर्ण अन्यथा
		i = 0;

	क्रम (; i < nr_frags; i++) अणु
		skb_frag = txb->fragments[i];

		अगर (host_encrypt)
			skb_reserve(skb_frag,
				    crypt->ops->extra_mpdu_prefix_len);

		frag_hdr = skb_put_data(skb_frag, &header, hdr_len);

		/* If this is not the last fragment, then add the MOREFRAGS
		 * bit to the frame control */
		अगर (i != nr_frags - 1) अणु
			frag_hdr->frame_ctl =
			    cpu_to_le16(fc | IEEE80211_FCTL_MOREFRAGS);
			bytes = bytes_per_frag;
		पूर्ण अन्यथा अणु
			/* The last fragment takes the reमुख्यing length */
			bytes = bytes_last_frag;
		पूर्ण

		अगर (i == 0 && !snapped) अणु
			libipw_copy_snap(skb_put
					    (skb_frag, SNAP_SIZE + माप(u16)),
					    ether_type);
			bytes -= SNAP_SIZE + माप(u16);
		पूर्ण

		skb_copy_from_linear_data(skb, skb_put(skb_frag, bytes), bytes);

		/* Advance the SKB... */
		skb_pull(skb, bytes);

		/* Encryption routine will move the header क्रमward in order
		 * to insert the IV between the header and the payload */
		अगर (host_encrypt)
			libipw_encrypt_fragment(ieee, skb_frag, hdr_len);

		अगर (ieee->config &
		    (CFG_LIBIPW_COMPUTE_FCS | CFG_LIBIPW_RESERVE_FCS))
			skb_put(skb_frag, 4);
	पूर्ण

      success:
	spin_unlock_irqrestore(&ieee->lock, flags);

	dev_kमुक्त_skb_any(skb);

	अगर (txb) अणु
		netdev_tx_t ret = (*ieee->hard_start_xmit)(txb, dev, priority);
		अगर (ret == NETDEV_TX_OK) अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += txb->payload_size;
			वापस NETDEV_TX_OK;
		पूर्ण

		libipw_txb_मुक्त(txb);
	पूर्ण

	वापस NETDEV_TX_OK;

      failed:
	spin_unlock_irqrestore(&ieee->lock, flags);
	netअगर_stop_queue(dev);
	dev->stats.tx_errors++;
	वापस NETDEV_TX_BUSY;
पूर्ण
EXPORT_SYMBOL(libipw_xmit);

EXPORT_SYMBOL(libipw_txb_मुक्त);
