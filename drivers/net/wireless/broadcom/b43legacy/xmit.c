<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  Transmission (TX/RX) related functions.

  Copyright (C) 2005 Martin Langer <martin-langer@gmx.de>
  Copyright (C) 2005 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (C) 2005, 2006 Michael Buesch <m@bues.ch>
  Copyright (C) 2005 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (C) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
  Copyright (C) 2007 Larry Finger <Larry.Finger@lwfinger.net>


*/

#समावेश <net/dst.h>

#समावेश "xmit.h"
#समावेश "phy.h"
#समावेश "dma.h"
#समावेश "pio.h"


/* Extract the bitrate out of a CCK PLCP header. */
अटल u8 b43legacy_plcp_get_bitrate_idx_cck(काष्ठा b43legacy_plcp_hdr6 *plcp)
अणु
	चयन (plcp->raw[0]) अणु
	हाल 0x0A:
		वापस 0;
	हाल 0x14:
		वापस 1;
	हाल 0x37:
		वापस 2;
	हाल 0x6E:
		वापस 3;
	पूर्ण
	B43legacy_BUG_ON(1);
	वापस -1;
पूर्ण

/* Extract the bitrate out of an OFDM PLCP header. */
अटल u8 b43legacy_plcp_get_bitrate_idx_ofdm(काष्ठा b43legacy_plcp_hdr6 *plcp,
					      bool aphy)
अणु
	पूर्णांक base = aphy ? 0 : 4;

	चयन (plcp->raw[0] & 0xF) अणु
	हाल 0xB:
		वापस base + 0;
	हाल 0xF:
		वापस base + 1;
	हाल 0xA:
		वापस base + 2;
	हाल 0xE:
		वापस base + 3;
	हाल 0x9:
		वापस base + 4;
	हाल 0xD:
		वापस base + 5;
	हाल 0x8:
		वापस base + 6;
	हाल 0xC:
		वापस base + 7;
	पूर्ण
	B43legacy_BUG_ON(1);
	वापस -1;
पूर्ण

u8 b43legacy_plcp_get_ratecode_cck(स्थिर u8 bitrate)
अणु
	चयन (bitrate) अणु
	हाल B43legacy_CCK_RATE_1MB:
		वापस 0x0A;
	हाल B43legacy_CCK_RATE_2MB:
		वापस 0x14;
	हाल B43legacy_CCK_RATE_5MB:
		वापस 0x37;
	हाल B43legacy_CCK_RATE_11MB:
		वापस 0x6E;
	पूर्ण
	B43legacy_BUG_ON(1);
	वापस 0;
पूर्ण

u8 b43legacy_plcp_get_ratecode_ofdm(स्थिर u8 bitrate)
अणु
	चयन (bitrate) अणु
	हाल B43legacy_OFDM_RATE_6MB:
		वापस 0xB;
	हाल B43legacy_OFDM_RATE_9MB:
		वापस 0xF;
	हाल B43legacy_OFDM_RATE_12MB:
		वापस 0xA;
	हाल B43legacy_OFDM_RATE_18MB:
		वापस 0xE;
	हाल B43legacy_OFDM_RATE_24MB:
		वापस 0x9;
	हाल B43legacy_OFDM_RATE_36MB:
		वापस 0xD;
	हाल B43legacy_OFDM_RATE_48MB:
		वापस 0x8;
	हाल B43legacy_OFDM_RATE_54MB:
		वापस 0xC;
	पूर्ण
	B43legacy_BUG_ON(1);
	वापस 0;
पूर्ण

व्योम b43legacy_generate_plcp_hdr(काष्ठा b43legacy_plcp_hdr4 *plcp,
				 स्थिर u16 octets, स्थिर u8 bitrate)
अणु
	__le32 *data = &(plcp->data);
	__u8 *raw = plcp->raw;

	अगर (b43legacy_is_ofdm_rate(bitrate)) अणु
		u16 d;

		d = b43legacy_plcp_get_ratecode_ofdm(bitrate);
		B43legacy_WARN_ON(octets & 0xF000);
		d |= (octets << 5);
		*data = cpu_to_le32(d);
	पूर्ण अन्यथा अणु
		u32 plen;

		plen = octets * 16 / bitrate;
		अगर ((octets * 16 % bitrate) > 0) अणु
			plen++;
			अगर ((bitrate == B43legacy_CCK_RATE_11MB)
			    && ((octets * 8 % 11) < 4))
				raw[1] = 0x84;
			अन्यथा
				raw[1] = 0x04;
		पूर्ण अन्यथा
			raw[1] = 0x04;
		*data |= cpu_to_le32(plen << 16);
		raw[0] = b43legacy_plcp_get_ratecode_cck(bitrate);
	पूर्ण
पूर्ण

अटल u8 b43legacy_calc_fallback_rate(u8 bitrate)
अणु
	चयन (bitrate) अणु
	हाल B43legacy_CCK_RATE_1MB:
		वापस B43legacy_CCK_RATE_1MB;
	हाल B43legacy_CCK_RATE_2MB:
		वापस B43legacy_CCK_RATE_1MB;
	हाल B43legacy_CCK_RATE_5MB:
		वापस B43legacy_CCK_RATE_2MB;
	हाल B43legacy_CCK_RATE_11MB:
		वापस B43legacy_CCK_RATE_5MB;
	हाल B43legacy_OFDM_RATE_6MB:
		वापस B43legacy_CCK_RATE_5MB;
	हाल B43legacy_OFDM_RATE_9MB:
		वापस B43legacy_OFDM_RATE_6MB;
	हाल B43legacy_OFDM_RATE_12MB:
		वापस B43legacy_OFDM_RATE_9MB;
	हाल B43legacy_OFDM_RATE_18MB:
		वापस B43legacy_OFDM_RATE_12MB;
	हाल B43legacy_OFDM_RATE_24MB:
		वापस B43legacy_OFDM_RATE_18MB;
	हाल B43legacy_OFDM_RATE_36MB:
		वापस B43legacy_OFDM_RATE_24MB;
	हाल B43legacy_OFDM_RATE_48MB:
		वापस B43legacy_OFDM_RATE_36MB;
	हाल B43legacy_OFDM_RATE_54MB:
		वापस B43legacy_OFDM_RATE_48MB;
	पूर्ण
	B43legacy_BUG_ON(1);
	वापस 0;
पूर्ण

अटल पूर्णांक generate_txhdr_fw3(काष्ठा b43legacy_wldev *dev,
			       काष्ठा b43legacy_txhdr_fw3 *txhdr,
			       स्थिर अचिन्हित अक्षर *fragment_data,
			       अचिन्हित पूर्णांक fragment_len,
			       काष्ठा ieee80211_tx_info *info,
			       u16 cookie)
अणु
	स्थिर काष्ठा ieee80211_hdr *wlhdr;
	पूर्णांक use_encryption = !!info->control.hw_key;
	u8 rate;
	काष्ठा ieee80211_rate *rate_fb;
	पूर्णांक rate_ofdm;
	पूर्णांक rate_fb_ofdm;
	अचिन्हित पूर्णांक plcp_fragment_len;
	u32 mac_ctl = 0;
	u16 phy_ctl = 0;
	काष्ठा ieee80211_rate *tx_rate;
	काष्ठा ieee80211_tx_rate *rates;

	wlhdr = (स्थिर काष्ठा ieee80211_hdr *)fragment_data;

	स_रखो(txhdr, 0, माप(*txhdr));

	tx_rate = ieee80211_get_tx_rate(dev->wl->hw, info);

	rate = tx_rate->hw_value;
	rate_ofdm = b43legacy_is_ofdm_rate(rate);
	rate_fb = ieee80211_get_alt_retry_rate(dev->wl->hw, info, 0) ? : tx_rate;
	rate_fb_ofdm = b43legacy_is_ofdm_rate(rate_fb->hw_value);

	txhdr->mac_frame_ctl = wlhdr->frame_control;
	स_नकल(txhdr->tx_receiver, wlhdr->addr1, ETH_ALEN);

	/* Calculate duration क्रम fallback rate */
	अगर ((rate_fb->hw_value == rate) ||
	    (wlhdr->duration_id & cpu_to_le16(0x8000)) ||
	    (wlhdr->duration_id == cpu_to_le16(0))) अणु
		/* If the fallback rate equals the normal rate or the
		 * dur_id field contains an AID, CFP magic or 0,
		 * use the original dur_id field. */
		txhdr->dur_fb = wlhdr->duration_id;
	पूर्ण अन्यथा अणु
		txhdr->dur_fb = ieee80211_generic_frame_duration(dev->wl->hw,
							 info->control.vअगर,
							 info->band,
							 fragment_len,
							 rate_fb);
	पूर्ण

	plcp_fragment_len = fragment_len + FCS_LEN;
	अगर (use_encryption) अणु
		u8 key_idx = info->control.hw_key->hw_key_idx;
		काष्ठा b43legacy_key *key;
		पूर्णांक wlhdr_len;
		माप_प्रकार iv_len;

		B43legacy_WARN_ON(key_idx >= dev->max_nr_keys);
		key = &(dev->key[key_idx]);

		अगर (key->enabled) अणु
			/* Hardware appends ICV. */
			plcp_fragment_len += info->control.hw_key->icv_len;

			key_idx = b43legacy_kidx_to_fw(dev, key_idx);
			mac_ctl |= (key_idx << B43legacy_TX4_MAC_KEYIDX_SHIFT) &
				   B43legacy_TX4_MAC_KEYIDX;
			mac_ctl |= (key->algorithm <<
				   B43legacy_TX4_MAC_KEYALG_SHIFT) &
				   B43legacy_TX4_MAC_KEYALG;
			wlhdr_len = ieee80211_hdrlen(wlhdr->frame_control);
			iv_len = min_t(माप_प्रकार, info->control.hw_key->iv_len,
				     ARRAY_SIZE(txhdr->iv));
			स_नकल(txhdr->iv, ((u8 *)wlhdr) + wlhdr_len, iv_len);
		पूर्ण अन्यथा अणु
			/* This key is invalid. This might only happen
			 * in a लघु समयframe after machine resume beक्रमe
			 * we were able to reconfigure keys.
			 * Drop this packet completely. Do not transmit it
			 * unencrypted to aव्योम leaking inक्रमmation. */
			वापस -ENOKEY;
		पूर्ण
	पूर्ण
	b43legacy_generate_plcp_hdr((काष्ठा b43legacy_plcp_hdr4 *)
				    (&txhdr->plcp), plcp_fragment_len,
				    rate);
	b43legacy_generate_plcp_hdr(&txhdr->plcp_fb, plcp_fragment_len,
				    rate_fb->hw_value);

	/* PHY TX Control word */
	अगर (rate_ofdm)
		phy_ctl |= B43legacy_TX4_PHY_ENC_OFDM;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		phy_ctl |= B43legacy_TX4_PHY_SHORTPRMBL;
	phy_ctl |= B43legacy_TX4_PHY_ANTLAST;

	/* MAC control */
	rates = info->control.rates;
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		mac_ctl |= B43legacy_TX4_MAC_ACK;
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
		mac_ctl |= B43legacy_TX4_MAC_HWSEQ;
	अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
		mac_ctl |= B43legacy_TX4_MAC_STMSDU;
	अगर (rate_fb_ofdm)
		mac_ctl |= B43legacy_TX4_MAC_FALLBACKOFDM;

	/* Overग_लिखो rates[0].count to make the retry calculation
	 * in the tx status easier. need the actual retry limit to
	 * detect whether the fallback rate was used.
	 */
	अगर ((rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) ||
	    (rates[0].count <= dev->wl->hw->conf.दीर्घ_frame_max_tx_count)) अणु
		rates[0].count = dev->wl->hw->conf.दीर्घ_frame_max_tx_count;
		mac_ctl |= B43legacy_TX4_MAC_LONGFRAME;
	पूर्ण अन्यथा अणु
		rates[0].count = dev->wl->hw->conf.लघु_frame_max_tx_count;
	पूर्ण

	/* Generate the RTS or CTS-to-self frame */
	अगर ((rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) ||
	    (rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)) अणु
		अचिन्हित पूर्णांक len;
		काष्ठा ieee80211_hdr *hdr;
		पूर्णांक rts_rate;
		पूर्णांक rts_rate_fb;
		पूर्णांक rts_rate_fb_ofdm;

		rts_rate = ieee80211_get_rts_cts_rate(dev->wl->hw, info)->hw_value;
		rts_rate_fb = b43legacy_calc_fallback_rate(rts_rate);
		rts_rate_fb_ofdm = b43legacy_is_ofdm_rate(rts_rate_fb);
		अगर (rts_rate_fb_ofdm)
			mac_ctl |= B43legacy_TX4_MAC_CTSFALLBACKOFDM;

		अगर (rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
			ieee80211_ctstoself_get(dev->wl->hw,
						info->control.vअगर,
						fragment_data,
						fragment_len, info,
						(काष्ठा ieee80211_cts *)
						(txhdr->rts_frame));
			mac_ctl |= B43legacy_TX4_MAC_SENDCTS;
			len = माप(काष्ठा ieee80211_cts);
		पूर्ण अन्यथा अणु
			ieee80211_rts_get(dev->wl->hw,
					  info->control.vअगर,
					  fragment_data, fragment_len, info,
					  (काष्ठा ieee80211_rts *)
					  (txhdr->rts_frame));
			mac_ctl |= B43legacy_TX4_MAC_SENDRTS;
			len = माप(काष्ठा ieee80211_rts);
		पूर्ण
		len += FCS_LEN;
		b43legacy_generate_plcp_hdr((काष्ठा b43legacy_plcp_hdr4 *)
					    (&txhdr->rts_plcp),
					    len, rts_rate);
		b43legacy_generate_plcp_hdr(&txhdr->rts_plcp_fb,
					    len, rts_rate_fb);
		hdr = (काष्ठा ieee80211_hdr *)(&txhdr->rts_frame);
		txhdr->rts_dur_fb = hdr->duration_id;
	पूर्ण

	/* Magic cookie */
	txhdr->cookie = cpu_to_le16(cookie);

	/* Apply the bitfields */
	txhdr->mac_ctl = cpu_to_le32(mac_ctl);
	txhdr->phy_ctl = cpu_to_le16(phy_ctl);

	वापस 0;
पूर्ण

पूर्णांक b43legacy_generate_txhdr(काष्ठा b43legacy_wldev *dev,
			      u8 *txhdr,
			      स्थिर अचिन्हित अक्षर *fragment_data,
			      अचिन्हित पूर्णांक fragment_len,
			      काष्ठा ieee80211_tx_info *info,
			      u16 cookie)
अणु
	वापस generate_txhdr_fw3(dev, (काष्ठा b43legacy_txhdr_fw3 *)txhdr,
			   fragment_data, fragment_len,
			   info, cookie);
पूर्ण

अटल s8 b43legacy_rssi_postprocess(काष्ठा b43legacy_wldev *dev,
				     u8 in_rssi, पूर्णांक ofdm,
				     पूर्णांक adjust_2053, पूर्णांक adjust_2050)
अणु
	काष्ठा b43legacy_phy *phy = &dev->phy;
	s32 पंचांगp;

	चयन (phy->radio_ver) अणु
	हाल 0x2050:
		अगर (ofdm) अणु
			पंचांगp = in_rssi;
			अगर (पंचांगp > 127)
				पंचांगp -= 256;
			पंचांगp *= 73;
			पंचांगp /= 64;
			अगर (adjust_2050)
				पंचांगp += 25;
			अन्यथा
				पंचांगp -= 3;
		पूर्ण अन्यथा अणु
			अगर (dev->dev->bus->sprom.boardflags_lo
			    & B43legacy_BFL_RSSI) अणु
				अगर (in_rssi > 63)
					in_rssi = 63;
				पंचांगp = phy->nrssi_lt[in_rssi];
				पंचांगp = 31 - पंचांगp;
				पंचांगp *= -131;
				पंचांगp /= 128;
				पंचांगp -= 57;
			पूर्ण अन्यथा अणु
				पंचांगp = in_rssi;
				पंचांगp = 31 - पंचांगp;
				पंचांगp *= -149;
				पंचांगp /= 128;
				पंचांगp -= 68;
			पूर्ण
			अगर (phy->type == B43legacy_PHYTYPE_G &&
			    adjust_2050)
				पंचांगp += 25;
		पूर्ण
		अवरोध;
	हाल 0x2060:
		अगर (in_rssi > 127)
			पंचांगp = in_rssi - 256;
		अन्यथा
			पंचांगp = in_rssi;
		अवरोध;
	शेष:
		पंचांगp = in_rssi;
		पंचांगp -= 11;
		पंचांगp *= 103;
		पंचांगp /= 64;
		अगर (adjust_2053)
			पंचांगp -= 109;
		अन्यथा
			पंचांगp -= 83;
	पूर्ण

	वापस (s8)पंचांगp;
पूर्ण

व्योम b43legacy_rx(काष्ठा b43legacy_wldev *dev,
		  काष्ठा sk_buff *skb,
		  स्थिर व्योम *_rxhdr)
अणु
	काष्ठा ieee80211_rx_status status;
	काष्ठा b43legacy_plcp_hdr6 *plcp;
	काष्ठा ieee80211_hdr *wlhdr;
	स्थिर काष्ठा b43legacy_rxhdr_fw3 *rxhdr = _rxhdr;
	__le16 fctl;
	u16 phystat0;
	u16 phystat3;
	u16 chanstat;
	u16 maस_समय;
	u32 macstat;
	u16 chanid;
	u8 jssi;
	पूर्णांक padding;

	स_रखो(&status, 0, माप(status));

	/* Get metadata about the frame from the header. */
	phystat0 = le16_to_cpu(rxhdr->phy_status0);
	phystat3 = le16_to_cpu(rxhdr->phy_status3);
	jssi = rxhdr->jssi;
	macstat = le16_to_cpu(rxhdr->mac_status);
	maस_समय = le16_to_cpu(rxhdr->mac_समय);
	chanstat = le16_to_cpu(rxhdr->channel);

	अगर (macstat & B43legacy_RX_MAC_FCSERR)
		dev->wl->ieee_stats.करोt11FCSErrorCount++;

	/* Skip PLCP and padding */
	padding = (macstat & B43legacy_RX_MAC_PADDING) ? 2 : 0;
	अगर (unlikely(skb->len < (माप(काष्ठा b43legacy_plcp_hdr6) +
	    padding))) अणु
		b43legacydbg(dev->wl, "RX: Packet size underrun (1)\n");
		जाओ drop;
	पूर्ण
	plcp = (काष्ठा b43legacy_plcp_hdr6 *)(skb->data + padding);
	skb_pull(skb, माप(काष्ठा b43legacy_plcp_hdr6) + padding);
	/* The skb contains the Wireless Header + payload data now */
	अगर (unlikely(skb->len < (2+2+6/*minimum hdr*/ + FCS_LEN))) अणु
		b43legacydbg(dev->wl, "RX: Packet size underrun (2)\n");
		जाओ drop;
	पूर्ण
	wlhdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fctl = wlhdr->frame_control;

	अगर ((macstat & B43legacy_RX_MAC_DEC) &&
	    !(macstat & B43legacy_RX_MAC_DECERR)) अणु
		अचिन्हित पूर्णांक keyidx;
		पूर्णांक wlhdr_len;
		पूर्णांक iv_len;
		पूर्णांक icv_len;

		keyidx = ((macstat & B43legacy_RX_MAC_KEYIDX)
			  >> B43legacy_RX_MAC_KEYIDX_SHIFT);
		/* We must adjust the key index here. We want the "physical"
		 * key index, but the ucode passed it slightly dअगरferent.
		 */
		keyidx = b43legacy_kidx_to_raw(dev, keyidx);
		B43legacy_WARN_ON(keyidx >= dev->max_nr_keys);

		अगर (dev->key[keyidx].algorithm != B43legacy_SEC_ALGO_NONE) अणु
			/* Remove PROTECTED flag to mark it as decrypted. */
			B43legacy_WARN_ON(!ieee80211_has_रक्षित(fctl));
			fctl &= ~cpu_to_le16(IEEE80211_FCTL_PROTECTED);
			wlhdr->frame_control = fctl;

			wlhdr_len = ieee80211_hdrlen(fctl);
			अगर (unlikely(skb->len < (wlhdr_len + 3))) अणु
				b43legacydbg(dev->wl, "RX: Packet size"
					     " underrun3\n");
				जाओ drop;
			पूर्ण
			अगर (skb->data[wlhdr_len + 3] & (1 << 5)) अणु
				/* The Ext-IV Bit is set in the "KeyID"
				 * octet of the IV.
				 */
				iv_len = 8;
				icv_len = 8;
			पूर्ण अन्यथा अणु
				iv_len = 4;
				icv_len = 4;
			पूर्ण
			अगर (unlikely(skb->len < (wlhdr_len + iv_len +
			    icv_len))) अणु
				b43legacydbg(dev->wl, "RX: Packet size"
					     " underrun4\n");
				जाओ drop;
			पूर्ण
			/* Remove the IV */
			स_हटाओ(skb->data + iv_len, skb->data, wlhdr_len);
			skb_pull(skb, iv_len);
			/* Remove the ICV */
			skb_trim(skb, skb->len - icv_len);

			status.flag |= RX_FLAG_DECRYPTED;
		पूर्ण
	पूर्ण

	status.संकेत = b43legacy_rssi_postprocess(dev, jssi,
				      (phystat0 & B43legacy_RX_PHYST0_OFDM),
				      (phystat0 & B43legacy_RX_PHYST0_GAINCTL),
				      (phystat3 & B43legacy_RX_PHYST3_TRSTATE));
	/* change to support A PHY */
	अगर (phystat0 & B43legacy_RX_PHYST0_OFDM)
		status.rate_idx = b43legacy_plcp_get_bitrate_idx_ofdm(plcp, false);
	अन्यथा
		status.rate_idx = b43legacy_plcp_get_bitrate_idx_cck(plcp);
	status.antenna = !!(phystat0 & B43legacy_RX_PHYST0_ANT);

	/*
	 * All frames on monitor पूर्णांकerfaces and beacons always need a full
	 * 64-bit बारtamp. Monitor पूर्णांकerfaces need it क्रम diagnostic
	 * purposes and beacons क्रम IBSS merging.
	 * This code assumes we get to process the packet within 16 bits
	 * of बारtamp, i.e. about 65 milliseconds after the PHY received
	 * the first symbol.
	 */
	अगर (ieee80211_is_beacon(fctl) || dev->wl->radiotap_enabled) अणु
		u16 low_maस_समय_now;

		b43legacy_tsf_पढ़ो(dev, &status.maस_समय);
		low_maस_समय_now = status.maस_समय;
		status.maस_समय = status.maस_समय & ~0xFFFFULL;
		status.maस_समय += maस_समय;
		अगर (low_maस_समय_now <= maस_समय)
			status.maस_समय -= 0x10000;
		status.flag |= RX_FLAG_MACTIME_START;
	पूर्ण

	chanid = (chanstat & B43legacy_RX_CHAN_ID) >>
		  B43legacy_RX_CHAN_ID_SHIFT;
	चयन (chanstat & B43legacy_RX_CHAN_PHYTYPE) अणु
	हाल B43legacy_PHYTYPE_B:
	हाल B43legacy_PHYTYPE_G:
		status.band = NL80211_BAND_2GHZ;
		status.freq = chanid + 2400;
		अवरोध;
	शेष:
		b43legacywarn(dev->wl, "Unexpected value for chanstat (0x%X)\n",
		       chanstat);
		जाओ drop;
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), &status, माप(status));
	ieee80211_rx_irqsafe(dev->wl->hw, skb);

	वापस;
drop:
	b43legacydbg(dev->wl, "RX: Packet dropped\n");
	dev_kमुक्त_skb_any(skb);
पूर्ण

व्योम b43legacy_handle_txstatus(काष्ठा b43legacy_wldev *dev,
			     स्थिर काष्ठा b43legacy_txstatus *status)
अणु
	b43legacy_debugfs_log_txstat(dev, status);

	अगर (status->पूर्णांकermediate)
		वापस;
	अगर (status->क्रम_ampdu)
		वापस;
	अगर (!status->acked)
		dev->wl->ieee_stats.करोt11ACKFailureCount++;
	अगर (status->rts_count) अणु
		अगर (status->rts_count == 0xF) /* FIXME */
			dev->wl->ieee_stats.करोt11RTSFailureCount++;
		अन्यथा
			dev->wl->ieee_stats.करोt11RTSSuccessCount++;
	पूर्ण

	अगर (b43legacy_using_pio(dev))
		b43legacy_pio_handle_txstatus(dev, status);
	अन्यथा
		b43legacy_dma_handle_txstatus(dev, status);
पूर्ण

/* Handle TX status report as received through DMA/PIO queues */
व्योम b43legacy_handle_hwtxstatus(काष्ठा b43legacy_wldev *dev,
				 स्थिर काष्ठा b43legacy_hwtxstatus *hw)
अणु
	काष्ठा b43legacy_txstatus status;
	u8 पंचांगp;

	status.cookie = le16_to_cpu(hw->cookie);
	status.seq = le16_to_cpu(hw->seq);
	status.phy_stat = hw->phy_stat;
	पंचांगp = hw->count;
	status.frame_count = (पंचांगp >> 4);
	status.rts_count = (पंचांगp & 0x0F);
	पंचांगp = hw->flags << 1;
	status.supp_reason = ((पंचांगp & 0x1C) >> 2);
	status.pm_indicated = !!(पंचांगp & 0x80);
	status.पूर्णांकermediate = !!(पंचांगp & 0x40);
	status.क्रम_ampdu = !!(पंचांगp & 0x20);
	status.acked = !!(पंचांगp & 0x02);

	b43legacy_handle_txstatus(dev, &status);
पूर्ण

/* Stop any TX operation on the device (suspend the hardware queues) */
व्योम b43legacy_tx_suspend(काष्ठा b43legacy_wldev *dev)
अणु
	अगर (b43legacy_using_pio(dev))
		b43legacy_pio_मुक्तze_txqueues(dev);
	अन्यथा
		b43legacy_dma_tx_suspend(dev);
पूर्ण

/* Resume any TX operation on the device (resume the hardware queues) */
व्योम b43legacy_tx_resume(काष्ठा b43legacy_wldev *dev)
अणु
	अगर (b43legacy_using_pio(dev))
		b43legacy_pio_thaw_txqueues(dev);
	अन्यथा
		b43legacy_dma_tx_resume(dev);
पूर्ण

/* Initialize the QoS parameters */
व्योम b43legacy_qos_init(काष्ठा b43legacy_wldev *dev)
अणु
	/* FIXME: This function must probably be called from the mac80211
	 * config callback. */
वापस;

	b43legacy_hf_ग_लिखो(dev, b43legacy_hf_पढ़ो(dev) | B43legacy_HF_EDCF);
	/* FIXME समाप्त magic */
	b43legacy_ग_लिखो16(dev, 0x688,
			  b43legacy_पढ़ो16(dev, 0x688) | 0x4);


	/*TODO: We might need some stack support here to get the values. */
पूर्ण
