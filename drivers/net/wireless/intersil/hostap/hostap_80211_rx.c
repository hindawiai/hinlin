<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/lib80211.h>
#समावेश <linux/अगर_arp.h>

#समावेश "hostap_80211.h"
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

व्योम hostap_dump_rx_80211(स्थिर अक्षर *name, काष्ठा sk_buff *skb,
			  काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	prपूर्णांकk(KERN_DEBUG "%s: RX signal=%d noise=%d rate=%d len=%d "
	       "jiffies=%ld\n",
	       name, rx_stats->संकेत, rx_stats->noise, rx_stats->rate,
	       skb->len, jअगरfies);

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


/* Send RX frame to netअगर with 802.11 (and possible prism) header.
 * Called from hardware or software IRQ context. */
पूर्णांक prism2_rx_80211(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		    काष्ठा hostap_80211_rx_status *rx_stats, पूर्णांक type)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक hdrlen, phdrlen, head_need, tail_need;
	u16 fc;
	पूर्णांक prism_header, ret;
	काष्ठा ieee80211_hdr *fhdr;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (dev->type == ARPHRD_IEEE80211_PRISM) अणु
		अगर (local->monitor_type == PRISM2_MONITOR_PRISM) अणु
			prism_header = 1;
			phdrlen = माप(काष्ठा linux_wlan_ng_prism_hdr);
		पूर्ण अन्यथा अणु /* local->monitor_type == PRISM2_MONITOR_CAPHDR */
			prism_header = 2;
			phdrlen = माप(काष्ठा linux_wlan_ng_cap_hdr);
		पूर्ण
	पूर्ण अन्यथा अगर (dev->type == ARPHRD_IEEE80211_RADIOTAP) अणु
		prism_header = 3;
		phdrlen = माप(काष्ठा hostap_radiotap_rx);
	पूर्ण अन्यथा अणु
		prism_header = 0;
		phdrlen = 0;
	पूर्ण

	fhdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(fhdr->frame_control);

	अगर (type == PRISM2_RX_MGMT && (fc & IEEE80211_FCTL_VERS)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: dropped management frame with header "
		       "version %d\n", dev->name, fc & IEEE80211_FCTL_VERS);
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	hdrlen = hostap_80211_get_hdrlen(fhdr->frame_control);

	/* check अगर there is enough room क्रम extra data; अगर not, expand skb
	 * buffer to be large enough क्रम the changes */
	head_need = phdrlen;
	tail_need = 0;
#अगर_घोषित PRISM2_ADD_BOGUS_CRC
	tail_need += 4;
#पूर्ण_अगर /* PRISM2_ADD_BOGUS_CRC */

	head_need -= skb_headroom(skb);
	tail_need -= skb_tailroom(skb);

	अगर (head_need > 0 || tail_need > 0) अणु
		अगर (pskb_expand_head(skb, head_need > 0 ? head_need : 0,
				     tail_need > 0 ? tail_need : 0,
				     GFP_ATOMIC)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: prism2_rx_80211 failed to "
			       "reallocate skb buffer\n", dev->name);
			dev_kमुक्त_skb_any(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	/* We now have an skb with enough head and tail room, so just insert
	 * the extra data */

#अगर_घोषित PRISM2_ADD_BOGUS_CRC
	स_रखो(skb_put(skb, 4), 0xff, 4); /* Prism2 strips CRC */
#पूर्ण_अगर /* PRISM2_ADD_BOGUS_CRC */

	अगर (prism_header == 1) अणु
		काष्ठा linux_wlan_ng_prism_hdr *hdr;
		hdr = skb_push(skb, phdrlen);
		स_रखो(hdr, 0, phdrlen);
		hdr->msgcode = LWNG_CAP_DID_BASE;
		hdr->msglen = माप(*hdr);
		स_नकल(hdr->devname, dev->name, माप(hdr->devname));
#घोषणा LWNG_SETVAL(f,i,s,l,d) \
hdr->f.did = LWNG_CAP_DID_BASE | (i << 12); \
hdr->f.status = s; hdr->f.len = l; hdr->f.data = d
		LWNG_SETVAL(hostसमय, 1, 0, 4, jअगरfies);
		LWNG_SETVAL(maस_समय, 2, 0, 4, rx_stats->mac_समय);
		LWNG_SETVAL(channel, 3, 1 /* no value */, 4, 0);
		LWNG_SETVAL(rssi, 4, 1 /* no value */, 4, 0);
		LWNG_SETVAL(sq, 5, 1 /* no value */, 4, 0);
		LWNG_SETVAL(संकेत, 6, 0, 4, rx_stats->संकेत);
		LWNG_SETVAL(noise, 7, 0, 4, rx_stats->noise);
		LWNG_SETVAL(rate, 8, 0, 4, rx_stats->rate / 5);
		LWNG_SETVAL(istx, 9, 0, 4, 0);
		LWNG_SETVAL(frmlen, 10, 0, 4, skb->len - phdrlen);
#अघोषित LWNG_SETVAL
	पूर्ण अन्यथा अगर (prism_header == 2) अणु
		काष्ठा linux_wlan_ng_cap_hdr *hdr;
		hdr = skb_push(skb, phdrlen);
		स_रखो(hdr, 0, phdrlen);
		hdr->version    = htonl(LWNG_CAPHDR_VERSION);
		hdr->length     = htonl(phdrlen);
		hdr->maस_समय    = __cpu_to_be64(rx_stats->mac_समय);
		hdr->hostसमय   = __cpu_to_be64(jअगरfies);
		hdr->phytype    = htonl(4); /* dss_करोt11_b */
		hdr->channel    = htonl(local->channel);
		hdr->datarate   = htonl(rx_stats->rate);
		hdr->antenna    = htonl(0); /* unknown */
		hdr->priority   = htonl(0); /* unknown */
		hdr->ssi_type   = htonl(3); /* raw */
		hdr->ssi_संकेत = htonl(rx_stats->संकेत);
		hdr->ssi_noise  = htonl(rx_stats->noise);
		hdr->preamble   = htonl(0); /* unknown */
		hdr->encoding   = htonl(1); /* cck */
	पूर्ण अन्यथा अगर (prism_header == 3) अणु
		काष्ठा hostap_radiotap_rx *hdr;
		hdr = skb_push(skb, phdrlen);
		स_रखो(hdr, 0, phdrlen);
		hdr->hdr.it_len = cpu_to_le16(phdrlen);
		hdr->hdr.it_present =
			cpu_to_le32((1 << IEEE80211_RADIOTAP_TSFT) |
				    (1 << IEEE80211_RADIOTAP_CHANNEL) |
				    (1 << IEEE80211_RADIOTAP_RATE) |
				    (1 << IEEE80211_RADIOTAP_DBM_ANTSIGNAL) |
				    (1 << IEEE80211_RADIOTAP_DBM_ANTNOISE));
		hdr->tsft = cpu_to_le64(rx_stats->mac_समय);
		hdr->chan_freq = cpu_to_le16(freq_list[local->channel - 1]);
		hdr->chan_flags = cpu_to_le16(IEEE80211_CHAN_CCK |
						 IEEE80211_CHAN_2GHZ);
		hdr->rate = rx_stats->rate / 5;
		hdr->dbm_antसंकेत = rx_stats->संकेत;
		hdr->dbm_antnoise = rx_stats->noise;
	पूर्ण

	ret = skb->len - phdrlen;
	skb->dev = dev;
	skb_reset_mac_header(skb);
	skb_pull(skb, hdrlen);
	अगर (prism_header)
		skb_pull(skb, phdrlen);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = cpu_to_be16(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));
	netअगर_rx(skb);

	वापस ret;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल व्योम monitor_rx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	पूर्णांक len;

	len = prism2_rx_80211(dev, skb, rx_stats, PRISM2_RX_MONITOR);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल काष्ठा prism2_frag_entry *
prism2_frag_cache_find(local_info_t *local, अचिन्हित पूर्णांक seq,
		       अचिन्हित पूर्णांक frag, u8 *src, u8 *dst)
अणु
	काष्ठा prism2_frag_entry *entry;
	पूर्णांक i;

	क्रम (i = 0; i < PRISM2_FRAG_CACHE_LEN; i++) अणु
		entry = &local->frag_cache[i];
		अगर (entry->skb != शून्य &&
		    समय_after(jअगरfies, entry->first_frag_समय + 2 * HZ)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: expiring fragment cache entry "
			       "seq=%u last_frag=%u\n",
			       local->dev->name, entry->seq, entry->last_frag);
			dev_kमुक्त_skb(entry->skb);
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
prism2_frag_cache_get(local_info_t *local, काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 sc;
	अचिन्हित पूर्णांक frag, seq;
	काष्ठा prism2_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctrl);
	frag = sc & IEEE80211_SCTL_FRAG;
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;

	अगर (frag == 0) अणु
		/* Reserve enough space to fit maximum frame length */
		skb = dev_alloc_skb(local->dev->mtu +
				    माप(काष्ठा ieee80211_hdr) +
				    8 /* LLC */ +
				    2 /* alignment */ +
				    8 /* WEP */ + ETH_ALEN /* WDS */);
		अगर (skb == शून्य)
			वापस शून्य;

		entry = &local->frag_cache[local->frag_next_idx];
		local->frag_next_idx++;
		अगर (local->frag_next_idx >= PRISM2_FRAG_CACHE_LEN)
			local->frag_next_idx = 0;

		अगर (entry->skb != शून्य)
			dev_kमुक्त_skb(entry->skb);

		entry->first_frag_समय = jअगरfies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		स_नकल(entry->src_addr, hdr->addr2, ETH_ALEN);
		स_नकल(entry->dst_addr, hdr->addr1, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* received a fragment of a frame क्रम which the head fragment
		 * should have alपढ़ोy been received */
		entry = prism2_frag_cache_find(local, seq, frag, hdr->addr2,
					       hdr->addr1);
		अगर (entry != शून्य) अणु
			entry->last_frag = frag;
			skb = entry->skb;
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक prism2_frag_cache_invalidate(local_info_t *local,
					काष्ठा ieee80211_hdr *hdr)
अणु
	u16 sc;
	अचिन्हित पूर्णांक seq;
	काष्ठा prism2_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctrl);
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;

	entry = prism2_frag_cache_find(local, seq, -1, hdr->addr2, hdr->addr1);

	अगर (entry == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: could not invalidate fragment cache "
		       "entry (seq=%u)\n",
		       local->dev->name, seq);
		वापस -1;
	पूर्ण

	entry->skb = शून्य;
	वापस 0;
पूर्ण


अटल काष्ठा hostap_bss_info *__hostap_get_bss(local_info_t *local, u8 *bssid,
						u8 *ssid, माप_प्रकार ssid_len)
अणु
	काष्ठा list_head *ptr;
	काष्ठा hostap_bss_info *bss;

	list_क्रम_each(ptr, &local->bss_list) अणु
		bss = list_entry(ptr, काष्ठा hostap_bss_info, list);
		अगर (स_भेद(bss->bssid, bssid, ETH_ALEN) == 0 &&
		    (ssid == शून्य ||
		     (ssid_len == bss->ssid_len &&
		      स_भेद(ssid, bss->ssid, ssid_len) == 0))) अणु
			list_move(&bss->list, &local->bss_list);
			वापस bss;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण


अटल काष्ठा hostap_bss_info *__hostap_add_bss(local_info_t *local, u8 *bssid,
						u8 *ssid, माप_प्रकार ssid_len)
अणु
	काष्ठा hostap_bss_info *bss;

	अगर (local->num_bss_info >= HOSTAP_MAX_BSS_COUNT) अणु
		bss = list_entry(local->bss_list.prev,
				 काष्ठा hostap_bss_info, list);
		list_del(&bss->list);
		local->num_bss_info--;
	पूर्ण अन्यथा अणु
		bss = kदो_स्मृति(माप(*bss), GFP_ATOMIC);
		अगर (bss == शून्य)
			वापस शून्य;
	पूर्ण

	स_रखो(bss, 0, माप(*bss));
	स_नकल(bss->bssid, bssid, ETH_ALEN);
	स_नकल(bss->ssid, ssid, ssid_len);
	bss->ssid_len = ssid_len;
	local->num_bss_info++;
	list_add(&bss->list, &local->bss_list);
	वापस bss;
पूर्ण


अटल व्योम __hostap_expire_bss(local_info_t *local)
अणु
	काष्ठा hostap_bss_info *bss;

	जबतक (local->num_bss_info > 0) अणु
		bss = list_entry(local->bss_list.prev,
				 काष्ठा hostap_bss_info, list);
		अगर (!समय_after(jअगरfies, bss->last_update + 60 * HZ))
			अवरोध;

		list_del(&bss->list);
		local->num_bss_info--;
		kमुक्त(bss);
	पूर्ण
पूर्ण


/* Both IEEE 802.11 Beacon and Probe Response frames have similar काष्ठाure, so
 * the same routine can be used to parse both of them. */
अटल व्योम hostap_rx_sta_beacon(local_info_t *local, काष्ठा sk_buff *skb,
				 पूर्णांक stype)
अणु
	काष्ठा hostap_ieee80211_mgmt *mgmt;
	पूर्णांक left, chan = 0;
	u8 *pos;
	u8 *ssid = शून्य, *wpa = शून्य, *rsn = शून्य;
	माप_प्रकार ssid_len = 0, wpa_len = 0, rsn_len = 0;
	काष्ठा hostap_bss_info *bss;

	अगर (skb->len < IEEE80211_MGMT_HDR_LEN + माप(mgmt->u.beacon))
		वापस;

	mgmt = (काष्ठा hostap_ieee80211_mgmt *) skb->data;
	pos = mgmt->u.beacon.variable;
	left = skb->len - (pos - skb->data);

	जबतक (left >= 2) अणु
		अगर (2 + pos[1] > left)
			वापस; /* parse failed */
		चयन (*pos) अणु
		हाल WLAN_EID_SSID:
			ssid = pos + 2;
			ssid_len = pos[1];
			अवरोध;
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (pos[1] >= 4 &&
			    pos[2] == 0x00 && pos[3] == 0x50 &&
			    pos[4] == 0xf2 && pos[5] == 1) अणु
				wpa = pos;
				wpa_len = pos[1] + 2;
			पूर्ण
			अवरोध;
		हाल WLAN_EID_RSN:
			rsn = pos;
			rsn_len = pos[1] + 2;
			अवरोध;
		हाल WLAN_EID_DS_PARAMS:
			अगर (pos[1] >= 1)
				chan = pos[2];
			अवरोध;
		पूर्ण
		left -= 2 + pos[1];
		pos += 2 + pos[1];
	पूर्ण

	अगर (wpa_len > MAX_WPA_IE_LEN)
		wpa_len = MAX_WPA_IE_LEN;
	अगर (rsn_len > MAX_WPA_IE_LEN)
		rsn_len = MAX_WPA_IE_LEN;
	अगर (ssid_len > माप(bss->ssid))
		ssid_len = माप(bss->ssid);

	spin_lock(&local->lock);
	bss = __hostap_get_bss(local, mgmt->bssid, ssid, ssid_len);
	अगर (bss == शून्य)
		bss = __hostap_add_bss(local, mgmt->bssid, ssid, ssid_len);
	अगर (bss) अणु
		bss->last_update = jअगरfies;
		bss->count++;
		bss->capab_info = le16_to_cpu(mgmt->u.beacon.capab_info);
		अगर (wpa) अणु
			स_नकल(bss->wpa_ie, wpa, wpa_len);
			bss->wpa_ie_len = wpa_len;
		पूर्ण अन्यथा
			bss->wpa_ie_len = 0;
		अगर (rsn) अणु
			स_नकल(bss->rsn_ie, rsn, rsn_len);
			bss->rsn_ie_len = rsn_len;
		पूर्ण अन्यथा
			bss->rsn_ie_len = 0;
		bss->chan = chan;
	पूर्ण
	__hostap_expire_bss(local);
	spin_unlock(&local->lock);
पूर्ण


अटल पूर्णांक
hostap_rx_frame_mgmt(local_info_t *local, काष्ठा sk_buff *skb,
		     काष्ठा hostap_80211_rx_status *rx_stats, u16 type,
		     u16 stype)
अणु
	अगर (local->iw_mode == IW_MODE_MASTER)
		hostap_update_sta_ps(local, (काष्ठा ieee80211_hdr *) skb->data);

	अगर (local->hostapd && type == IEEE80211_FTYPE_MGMT) अणु
		अगर (stype == IEEE80211_STYPE_BEACON &&
		    local->iw_mode == IW_MODE_MASTER) अणु
			काष्ठा sk_buff *skb2;
			/* Process beacon frames also in kernel driver to
			 * update STA(AP) table statistics */
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb2)
				hostap_rx(skb2->dev, skb2, rx_stats);
		पूर्ण

		/* send management frames to the user space daemon क्रम
		 * processing */
		local->apdevstats.rx_packets++;
		local->apdevstats.rx_bytes += skb->len;
		अगर (local->apdev == शून्य)
			वापस -1;
		prism2_rx_80211(local->apdev, skb, rx_stats, PRISM2_RX_MGMT);
		वापस 0;
	पूर्ण

	अगर (local->iw_mode == IW_MODE_MASTER) अणु
		अगर (type != IEEE80211_FTYPE_MGMT &&
		    type != IEEE80211_FTYPE_CTL) अणु
			prपूर्णांकk(KERN_DEBUG "%s: unknown management frame "
			       "(type=0x%02x, stype=0x%02x) dropped\n",
			       skb->dev->name, type >> 2, stype >> 4);
			वापस -1;
		पूर्ण

		hostap_rx(skb->dev, skb, rx_stats);
		वापस 0;
	पूर्ण अन्यथा अगर (type == IEEE80211_FTYPE_MGMT &&
		   (stype == IEEE80211_STYPE_BEACON ||
		    stype == IEEE80211_STYPE_PROBE_RESP)) अणु
		hostap_rx_sta_beacon(local, skb, stype);
		वापस -1;
	पूर्ण अन्यथा अगर (type == IEEE80211_FTYPE_MGMT &&
		   (stype == IEEE80211_STYPE_ASSOC_RESP ||
		    stype == IEEE80211_STYPE_REASSOC_RESP)) अणु
		/* Ignore (Re)AssocResp silently since these are not currently
		 * needed but are still received when WPA/RSN mode is enabled.
		 */
		वापस -1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: hostap_rx_frame_mgmt: dropped unhandled"
		       " management frame in non-Host AP mode (type=%d:%d)\n",
		       skb->dev->name, type >> 2, stype >> 4);
		वापस -1;
	पूर्ण
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल काष्ठा net_device *prism2_rx_get_wds(local_info_t *local,
						   u8 *addr)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = शून्य;
	काष्ठा list_head *ptr;

	पढ़ो_lock_bh(&local->अगरace_lock);
	list_क्रम_each(ptr, &local->hostap_पूर्णांकerfaces) अणु
		अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
		अगर (अगरace->type == HOSTAP_INTERFACE_WDS &&
		    स_भेद(अगरace->u.wds.remote_addr, addr, ETH_ALEN) == 0)
			अवरोध;
		अगरace = शून्य;
	पूर्ण
	पढ़ो_unlock_bh(&local->अगरace_lock);

	वापस अगरace ? अगरace->dev : शून्य;
पूर्ण


अटल पूर्णांक
hostap_rx_frame_wds(local_info_t *local, काष्ठा ieee80211_hdr *hdr, u16 fc,
		    काष्ठा net_device **wds)
अणु
	/* FIX: is this really supposed to accept WDS frames only in Master
	 * mode? What about Repeater or Managed with WDS frames? */
	अगर ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) !=
	    (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS) &&
	    (local->iw_mode != IW_MODE_MASTER || !(fc & IEEE80211_FCTL_TODS)))
		वापस 0; /* not a WDS frame */

	/* Possible WDS frame: either IEEE 802.11 compliant (अगर FromDS)
	 * or own non-standard frame with 4th address after payload */
	अगर (!ether_addr_equal(hdr->addr1, local->dev->dev_addr) &&
	    (hdr->addr1[0] != 0xff || hdr->addr1[1] != 0xff ||
	     hdr->addr1[2] != 0xff || hdr->addr1[3] != 0xff ||
	     hdr->addr1[4] != 0xff || hdr->addr1[5] != 0xff)) अणु
		/* RA (or BSSID) is not ours - drop */
		PDEBUG(DEBUG_EXTRA2, "%s: received WDS frame with "
		       "not own or broadcast %s=%pM\n",
		       local->dev->name,
		       fc & IEEE80211_FCTL_FROMDS ? "RA" : "BSSID",
		       hdr->addr1);
		वापस -1;
	पूर्ण

	/* check अगर the frame came from a रेजिस्टरed WDS connection */
	*wds = prism2_rx_get_wds(local, hdr->addr2);
	अगर (*wds == शून्य && fc & IEEE80211_FCTL_FROMDS &&
	    (local->iw_mode != IW_MODE_INFRA ||
	     !(local->wds_type & HOSTAP_WDS_AP_CLIENT) ||
	     स_भेद(hdr->addr2, local->bssid, ETH_ALEN) != 0)) अणु
		/* require that WDS link has been रेजिस्टरed with TA or the
		 * frame is from current AP when using 'AP client mode' */
		PDEBUG(DEBUG_EXTRA, "%s: received WDS[4 addr] frame "
		       "from unknown TA=%pM\n",
		       local->dev->name, hdr->addr2);
		अगर (local->ap && local->ap->स्वतःm_ap_wds)
			hostap_wds_link_oper(local, hdr->addr2, WDS_ADD);
		वापस -1;
	पूर्ण

	अगर (*wds && !(fc & IEEE80211_FCTL_FROMDS) && local->ap &&
	    hostap_is_sta_assoc(local->ap, hdr->addr2)) अणु
		/* STA is actually associated with us even though it has a
		 * रेजिस्टरed WDS link. Assume it is in 'AP client' mode.
		 * Since this is a 3-addr frame, assume it is not (bogus) WDS
		 * frame and process it like any normal ToDS frame from
		 * associated STA. */
		*wds = शून्य;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_is_eapol_frame(local_info_t *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = local->dev;
	u16 fc, ethertype;
	काष्ठा ieee80211_hdr *hdr;
	u8 *pos;

	अगर (skb->len < 24)
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(hdr->frame_control);

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


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक
hostap_rx_frame_decrypt(local_info_t *local, काष्ठा sk_buff *skb,
			काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_mpdu == शून्य)
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdrlen = hostap_80211_get_hdrlen(hdr->frame_control);

	अगर (local->tkip_countermeasures &&
	    म_भेद(crypt->ops->name, "TKIP") == 0) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: TKIP countermeasures: dropped "
			       "received packet from %pM\n",
			       local->dev->name, hdr->addr2);
		पूर्ण
		वापस -1;
	पूर्ण

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: decryption failed (SA=%pM) res=%d\n",
		       local->dev->name, hdr->addr2, res);
		local->comm_tallies.rx_discards_wep_undecryptable++;
		वापस -1;
	पूर्ण

	वापस res;
पूर्ण


/* Called only as a tasklet (software IRQ) */
अटल पूर्णांक
hostap_rx_frame_decrypt_msdu(local_info_t *local, काष्ठा sk_buff *skb,
			     पूर्णांक keyidx, काष्ठा lib80211_crypt_data *crypt)
अणु
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक res, hdrlen;

	अगर (crypt == शून्य || crypt->ops->decrypt_msdu == शून्य)
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdrlen = hostap_80211_get_hdrlen(hdr->frame_control);

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_msdu(skb, keyidx, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: MSDU decryption/MIC verification failed"
		       " (SA=%pM keyidx=%d)\n",
		       local->dev->name, hdr->addr2, keyidx);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/* All received frames are sent to this function. @skb contains the frame in
 * IEEE 802.11 क्रमmat, i.e., in the क्रमmat it was sent over air.
 * This function is called only as a tasklet (software IRQ). */
व्योम hostap_80211_rx(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		     काष्ठा hostap_80211_rx_status *rx_stats)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdrlen;
	u16 fc, type, stype, sc;
	काष्ठा net_device *wds = शून्य;
	अचिन्हित पूर्णांक frag;
	u8 *payload;
	काष्ठा sk_buff *skb2 = शून्य;
	u16 ethertype;
	पूर्णांक frame_authorized = 0;
	पूर्णांक from_assoc_ap = 0;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	काष्ठा lib80211_crypt_data *crypt = शून्य;
	व्योम *sta = शून्य;
	पूर्णांक keyidx = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	अगरace->stats.rx_packets++;
	अगरace->stats.rx_bytes += skb->len;

	/* dev is the master radio device; change this to be the शेष
	 * भव पूर्णांकerface (this may be changed to WDS device below) */
	dev = local->ddev;
	अगरace = netdev_priv(dev);

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (skb->len < 10)
		जाओ rx_dropped;

	fc = le16_to_cpu(hdr->frame_control);
	type = fc & IEEE80211_FCTL_FTYPE;
	stype = fc & IEEE80211_FCTL_STYPE;
	sc = le16_to_cpu(hdr->seq_ctrl);
	frag = sc & IEEE80211_SCTL_FRAG;
	hdrlen = hostap_80211_get_hdrlen(hdr->frame_control);

	/* Put this code here so that we aव्योम duplicating it in all
	 * Rx paths. - Jean II */
#अगर_घोषित IW_WIRELESS_SPY		/* defined in iw_handler.h */
	/* If spy monitoring on */
	अगर (अगरace->spy_data.spy_number > 0) अणु
		काष्ठा iw_quality wstats;
		wstats.level = rx_stats->संकेत;
		wstats.noise = rx_stats->noise;
		wstats.updated = IW_QUAL_LEVEL_UPDATED | IW_QUAL_NOISE_UPDATED
			| IW_QUAL_QUAL_INVALID | IW_QUAL_DBM;
		/* Update spy records */
		wireless_spy_update(dev, hdr->addr2, &wstats);
	पूर्ण
#पूर्ण_अगर /* IW_WIRELESS_SPY */
	hostap_update_rx_stats(local->ap, hdr, rx_stats);

	अगर (local->iw_mode == IW_MODE_MONITOR) अणु
		monitor_rx(dev, skb, rx_stats);
		वापस;
	पूर्ण

	अगर (local->host_decrypt) अणु
		पूर्णांक idx = 0;
		अगर (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;
		crypt = local->crypt_info.crypt[idx];
		sta = शून्य;

		/* Use station specअगरic key to override शेष keys अगर the
		 * receiver address is a unicast address ("individual RA"). If
		 * bcrx_sta_key parameter is set, station specअगरic key is used
		 * even with broad/multicast tarमाला_लो (this is against IEEE
		 * 802.11, but makes it easier to use dअगरferent keys with
		 * stations that करो not support WEP key mapping). */

		अगर (!(hdr->addr1[0] & 0x01) || local->bcrx_sta_key)
			(व्योम) hostap_handle_sta_crypto(local, hdr, &crypt,
							&sta);

		/* allow शून्य decrypt to indicate an station specअगरic override
		 * क्रम शेष encryption */
		अगर (crypt && (crypt->ops == शून्य ||
			      crypt->ops->decrypt_mpdu == शून्य))
			crypt = शून्य;

		अगर (!crypt && (fc & IEEE80211_FCTL_PROTECTED)) अणु
#अगर 0
			/* This seems to be triggered by some (multicast?)
			 * frames from other than current BSS, so just drop the
			 * frames silently instead of filling प्रणाली log with
			 * these reports. */
			prपूर्णांकk(KERN_DEBUG "%s: WEP decryption failed (not set)"
			       " (SA=%pM)\n",
			       local->dev->name, hdr->addr2);
#पूर्ण_अगर
			local->comm_tallies.rx_discards_wep_undecryptable++;
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	अगर (type != IEEE80211_FTYPE_DATA) अणु
		अगर (type == IEEE80211_FTYPE_MGMT &&
		    stype == IEEE80211_STYPE_AUTH &&
		    fc & IEEE80211_FCTL_PROTECTED && local->host_decrypt &&
		    (keyidx = hostap_rx_frame_decrypt(local, skb, crypt)) < 0)
		अणु
			prपूर्णांकk(KERN_DEBUG "%s: failed to decrypt mgmt::auth "
			       "from %pM\n", dev->name, hdr->addr2);
			/* TODO: could inक्रमm hostapd about this so that it
			 * could send auth failure report */
			जाओ rx_dropped;
		पूर्ण

		अगर (hostap_rx_frame_mgmt(local, skb, rx_stats, type, stype))
			जाओ rx_dropped;
		अन्यथा
			जाओ rx_निकास;
	पूर्ण

	/* Data frame - extract src/dst addresses */
	अगर (skb->len < IEEE80211_DATA_HDR3_LEN)
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
		अगर (skb->len < IEEE80211_DATA_HDR4_LEN)
			जाओ rx_dropped;
		स_नकल(dst, hdr->addr3, ETH_ALEN);
		स_नकल(src, hdr->addr4, ETH_ALEN);
		अवरोध;
	शेष:
		स_नकल(dst, hdr->addr1, ETH_ALEN);
		स_नकल(src, hdr->addr2, ETH_ALEN);
		अवरोध;
	पूर्ण

	अगर (hostap_rx_frame_wds(local, hdr, fc, &wds))
		जाओ rx_dropped;
	अगर (wds)
		skb->dev = dev = wds;

	अगर (local->iw_mode == IW_MODE_MASTER && !wds &&
	    (fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
	    IEEE80211_FCTL_FROMDS &&
	    local->stadev &&
	    स_भेद(hdr->addr2, local->assoc_ap_addr, ETH_ALEN) == 0) अणु
		/* Frame from BSSID of the AP क्रम which we are a client */
		skb->dev = dev = local->stadev;
		from_assoc_ap = 1;
	पूर्ण

	अगर ((local->iw_mode == IW_MODE_MASTER ||
	     local->iw_mode == IW_MODE_REPEAT) &&
	    !from_assoc_ap) अणु
		चयन (hostap_handle_sta_rx(local, dev, skb, rx_stats,
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

	/* Nullfunc frames may have PS-bit set, so they must be passed to
	 * hostap_handle_sta_rx() beक्रमe being dropped here. */
	अगर (stype != IEEE80211_STYPE_DATA &&
	    stype != IEEE80211_STYPE_DATA_CFACK &&
	    stype != IEEE80211_STYPE_DATA_CFPOLL &&
	    stype != IEEE80211_STYPE_DATA_CFACKPOLL) अणु
		अगर (stype != IEEE80211_STYPE_शून्यFUNC)
			prपूर्णांकk(KERN_DEBUG "%s: RX: dropped data frame "
			       "with no data (type=0x%02x, subtype=0x%02x)\n",
			       dev->name, type >> 2, stype >> 4);
		जाओ rx_dropped;
	पूर्ण

	/* skb: hdr + (possibly fragmented, possibly encrypted) payload */

	अगर (local->host_decrypt && (fc & IEEE80211_FCTL_PROTECTED) &&
	    (keyidx = hostap_rx_frame_decrypt(local, skb, crypt)) < 0)
		जाओ rx_dropped;
	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	/* skb: hdr + (possibly fragmented) plaपूर्णांकext payload */

	अगर (local->host_decrypt && (fc & IEEE80211_FCTL_PROTECTED) &&
	    (frag != 0 || (fc & IEEE80211_FCTL_MOREFRAGS))) अणु
		पूर्णांक flen;
		काष्ठा sk_buff *frag_skb =
			prism2_frag_cache_get(local, hdr);
		अगर (!frag_skb) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Rx cannot get skb from "
			       "fragment cache (morefrag=%d seq=%u frag=%u)\n",
			       dev->name, (fc & IEEE80211_FCTL_MOREFRAGS) != 0,
			       (sc & IEEE80211_SCTL_SEQ) >> 4, frag);
			जाओ rx_dropped;
		पूर्ण

		flen = skb->len;
		अगर (frag != 0)
			flen -= hdrlen;

		अगर (frag_skb->tail + flen > frag_skb->end) अणु
			prपूर्णांकk(KERN_WARNING "%s: host decrypted and "
			       "reassembled frame did not fit skb\n",
			       dev->name);
			prism2_frag_cache_invalidate(local, hdr);
			जाओ rx_dropped;
		पूर्ण

		अगर (frag == 0) अणु
			/* copy first fragment (including full headers) पूर्णांकo
			 * beginning of the fragment cache skb */
			skb_copy_from_linear_data(skb, skb_put(frag_skb, flen),
						  flen);
		पूर्ण अन्यथा अणु
			/* append frame payload to the end of the fragment
			 * cache skb */
			skb_copy_from_linear_data_offset(skb, hdrlen,
							 skb_put(frag_skb,
								 flen), flen);
		पूर्ण
		dev_kमुक्त_skb(skb);
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
		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		prism2_frag_cache_invalidate(local, hdr);
	पूर्ण

	/* skb: hdr + (possible reassembled) full MSDU payload; possibly still
	 * encrypted/authenticated */

	अगर (local->host_decrypt && (fc & IEEE80211_FCTL_PROTECTED) &&
	    hostap_rx_frame_decrypt_msdu(local, skb, keyidx, crypt))
		जाओ rx_dropped;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अगर (crypt && !(fc & IEEE80211_FCTL_PROTECTED) && !local->खोलो_wep) अणु
		अगर (local->ieee_802_1x &&
		    hostap_is_eapol_frame(local, skb)) अणु
			/* pass unencrypted EAPOL frames even अगर encryption is
			 * configured */
			PDEBUG(DEBUG_EXTRA2, "%s: RX: IEEE 802.1X - passing "
			       "unencrypted EAPOL frame\n", local->dev->name);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "%s: encryption configured, but RX "
			       "frame not encrypted (SA=%pM)\n",
			       local->dev->name, hdr->addr2);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	अगर (local->drop_unencrypted && !(fc & IEEE80211_FCTL_PROTECTED) &&
	    !hostap_is_eapol_frame(local, skb)) अणु
		अगर (net_ratelimit()) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped unencrypted RX data "
			       "frame from %pM (drop_unencrypted=1)\n",
			       dev->name, hdr->addr2);
		पूर्ण
		जाओ rx_dropped;
	पूर्ण

	/* skb: hdr + (possible reassembled) full plaपूर्णांकext payload */

	payload = skb->data + hdrlen;
	ethertype = (payload[6] << 8) | payload[7];

	/* If IEEE 802.1X is used, check whether the port is authorized to send
	 * the received frame. */
	अगर (local->ieee_802_1x && local->iw_mode == IW_MODE_MASTER) अणु
		अगर (ethertype == ETH_P_PAE) अणु
			PDEBUG(DEBUG_EXTRA2, "%s: RX: IEEE 802.1X frame\n",
			       dev->name);
			अगर (local->hostapd && local->apdev) अणु
				/* Send IEEE 802.1X frames to the user
				 * space daemon क्रम processing */
				prism2_rx_80211(local->apdev, skb, rx_stats,
						PRISM2_RX_MGMT);
				local->apdevstats.rx_packets++;
				local->apdevstats.rx_bytes += skb->len;
				जाओ rx_निकास;
			पूर्ण
		पूर्ण अन्यथा अगर (!frame_authorized) अणु
			prपूर्णांकk(KERN_DEBUG "%s: dropped frame from "
			       "unauthorized port (IEEE 802.1X): "
			       "ethertype=0x%04x\n",
			       dev->name, ethertype);
			जाओ rx_dropped;
		पूर्ण
	पूर्ण

	/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
	अगर (skb->len - hdrlen >= 8 &&
	    ((स_भेद(payload, rfc1042_header, 6) == 0 &&
	      ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
	     स_भेद(payload, bridge_tunnel_header, 6) == 0)) अणु
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
		 * replace EtherType */
		skb_pull(skb, hdrlen + 6);
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

	अगर (wds && ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		    IEEE80211_FCTL_TODS) &&
	    skb->len >= ETH_HLEN + ETH_ALEN) अणु
		/* Non-standard frame: get addr4 from its bogus location after
		 * the payload */
		skb_copy_from_linear_data_offset(skb, skb->len - ETH_ALEN,
						 skb->data + ETH_ALEN,
						 ETH_ALEN);
		skb_trim(skb, skb->len - ETH_ALEN);
	पूर्ण

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;

	अगर (local->iw_mode == IW_MODE_MASTER && !wds &&
	    local->ap->bridge_packets) अणु
		अगर (dst[0] & 0x01) अणु
			/* copy multicast frame both to the higher layers and
			 * to the wireless media */
			local->ap->bridged_multicast++;
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb2 == शून्य)
				prपूर्णांकk(KERN_DEBUG "%s: skb_clone failed for "
				       "multicast frame\n", dev->name);
		पूर्ण अन्यथा अगर (hostap_is_sta_authorized(local->ap, dst)) अणु
			/* send frame directly to the associated STA using
			 * wireless media and not passing to higher layers */
			local->ap->bridged_unicast++;
			skb2 = skb;
			skb = शून्य;
		पूर्ण
	पूर्ण

	अगर (skb2 != शून्य) अणु
		/* send to wireless media */
		skb2->dev = dev;
		skb2->protocol = cpu_to_be16(ETH_P_802_3);
		skb_reset_mac_header(skb2);
		skb_reset_network_header(skb2);
		/* skb2->network_header += ETH_HLEN; */
		dev_queue_xmit(skb2);
	पूर्ण

	अगर (skb) अणु
		skb->protocol = eth_type_trans(skb, dev);
		स_रखो(skb->cb, 0, माप(skb->cb));
		netअगर_rx(skb);
	पूर्ण

 rx_निकास:
	अगर (sta)
		hostap_handle_sta_release(sta);
	वापस;

 rx_dropped:
	dev_kमुक्त_skb(skb);

	dev->stats.rx_dropped++;
	जाओ rx_निकास;
पूर्ण


EXPORT_SYMBOL(hostap_80211_rx);
