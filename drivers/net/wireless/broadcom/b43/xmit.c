<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  Transmission (TX/RX) related functions.

  Copyright (C) 2005 Martin Langer <martin-langer@gmx.de>
  Copyright (C) 2005 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (C) 2005, 2006 Michael Buesch <m@bues.ch>
  Copyright (C) 2005 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (C) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>


*/

#समावेश "xmit.h"
#समावेश "phy_common.h"
#समावेश "dma.h"
#समावेश "pio.h"

अटल स्थिर काष्ठा b43_tx_legacy_rate_phy_ctl_entry b43_tx_legacy_rate_phy_ctl[] = अणु
	अणु B43_CCK_RATE_1MB,	0x0,			0x0 पूर्ण,
	अणु B43_CCK_RATE_2MB,	0x0,			0x1 पूर्ण,
	अणु B43_CCK_RATE_5MB,	0x0,			0x2 पूर्ण,
	अणु B43_CCK_RATE_11MB,	0x0,			0x3 पूर्ण,
	अणु B43_OFDM_RATE_6MB,	B43_TXH_PHY1_CRATE_1_2,	B43_TXH_PHY1_MODUL_BPSK पूर्ण,
	अणु B43_OFDM_RATE_9MB,	B43_TXH_PHY1_CRATE_3_4,	B43_TXH_PHY1_MODUL_BPSK पूर्ण,
	अणु B43_OFDM_RATE_12MB,	B43_TXH_PHY1_CRATE_1_2,	B43_TXH_PHY1_MODUL_QPSK पूर्ण,
	अणु B43_OFDM_RATE_18MB,	B43_TXH_PHY1_CRATE_3_4,	B43_TXH_PHY1_MODUL_QPSK पूर्ण,
	अणु B43_OFDM_RATE_24MB,	B43_TXH_PHY1_CRATE_1_2,	B43_TXH_PHY1_MODUL_QAM16 पूर्ण,
	अणु B43_OFDM_RATE_36MB,	B43_TXH_PHY1_CRATE_3_4,	B43_TXH_PHY1_MODUL_QAM16 पूर्ण,
	अणु B43_OFDM_RATE_48MB,	B43_TXH_PHY1_CRATE_2_3,	B43_TXH_PHY1_MODUL_QAM64 पूर्ण,
	अणु B43_OFDM_RATE_54MB,	B43_TXH_PHY1_CRATE_3_4,	B43_TXH_PHY1_MODUL_QAM64 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा b43_tx_legacy_rate_phy_ctl_entry *
b43_tx_legacy_rate_phy_ctl_ent(u8 bitrate)
अणु
	स्थिर काष्ठा b43_tx_legacy_rate_phy_ctl_entry *e;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(b43_tx_legacy_rate_phy_ctl); i++) अणु
		e = &(b43_tx_legacy_rate_phy_ctl[i]);
		अगर (e->bitrate == bitrate)
			वापस e;
	पूर्ण

	B43_WARN_ON(1);
	वापस शून्य;
पूर्ण

/* Extract the bitrate index out of a CCK PLCP header. */
अटल पूर्णांक b43_plcp_get_bitrate_idx_cck(काष्ठा b43_plcp_hdr6 *plcp)
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
	वापस -1;
पूर्ण

/* Extract the bitrate index out of an OFDM PLCP header. */
अटल पूर्णांक b43_plcp_get_bitrate_idx_ofdm(काष्ठा b43_plcp_hdr6 *plcp, bool ghz5)
अणु
	/* For 2 GHz band first OFDM rate is at index 4, see मुख्य.c */
	पूर्णांक base = ghz5 ? 0 : 4;

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
	वापस -1;
पूर्ण

u8 b43_plcp_get_ratecode_cck(स्थिर u8 bitrate)
अणु
	चयन (bitrate) अणु
	हाल B43_CCK_RATE_1MB:
		वापस 0x0A;
	हाल B43_CCK_RATE_2MB:
		वापस 0x14;
	हाल B43_CCK_RATE_5MB:
		वापस 0x37;
	हाल B43_CCK_RATE_11MB:
		वापस 0x6E;
	पूर्ण
	B43_WARN_ON(1);
	वापस 0;
पूर्ण

u8 b43_plcp_get_ratecode_ofdm(स्थिर u8 bitrate)
अणु
	चयन (bitrate) अणु
	हाल B43_OFDM_RATE_6MB:
		वापस 0xB;
	हाल B43_OFDM_RATE_9MB:
		वापस 0xF;
	हाल B43_OFDM_RATE_12MB:
		वापस 0xA;
	हाल B43_OFDM_RATE_18MB:
		वापस 0xE;
	हाल B43_OFDM_RATE_24MB:
		वापस 0x9;
	हाल B43_OFDM_RATE_36MB:
		वापस 0xD;
	हाल B43_OFDM_RATE_48MB:
		वापस 0x8;
	हाल B43_OFDM_RATE_54MB:
		वापस 0xC;
	पूर्ण
	B43_WARN_ON(1);
	वापस 0;
पूर्ण

व्योम b43_generate_plcp_hdr(काष्ठा b43_plcp_hdr4 *plcp,
			   स्थिर u16 octets, स्थिर u8 bitrate)
अणु
	__u8 *raw = plcp->raw;

	अगर (b43_is_ofdm_rate(bitrate)) अणु
		u32 d;

		d = b43_plcp_get_ratecode_ofdm(bitrate);
		B43_WARN_ON(octets & 0xF000);
		d |= (octets << 5);
		plcp->data = cpu_to_le32(d);
	पूर्ण अन्यथा अणु
		u32 plen;

		plen = octets * 16 / bitrate;
		अगर ((octets * 16 % bitrate) > 0) अणु
			plen++;
			अगर ((bitrate == B43_CCK_RATE_11MB)
			    && ((octets * 8 % 11) < 4)) अणु
				raw[1] = 0x84;
			पूर्ण अन्यथा
				raw[1] = 0x04;
		पूर्ण अन्यथा
			raw[1] = 0x04;
		plcp->data |= cpu_to_le32(plen << 16);
		raw[0] = b43_plcp_get_ratecode_cck(bitrate);
	पूर्ण
पूर्ण

/* TODO: verअगरy अगर needed क्रम SSLPN or LCN  */
अटल u16 b43_generate_tx_phy_ctl1(काष्ठा b43_wldev *dev, u8 bitrate)
अणु
	स्थिर काष्ठा b43_phy *phy = &dev->phy;
	स्थिर काष्ठा b43_tx_legacy_rate_phy_ctl_entry *e;
	u16 control = 0;
	u16 bw;

	अगर (phy->type == B43_PHYTYPE_LP)
		bw = B43_TXH_PHY1_BW_20;
	अन्यथा /* FIXME */
		bw = B43_TXH_PHY1_BW_20;

	अगर (0) अणु /* FIXME: MIMO */
	पूर्ण अन्यथा अगर (b43_is_cck_rate(bitrate) && phy->type != B43_PHYTYPE_LP) अणु
		control = bw;
	पूर्ण अन्यथा अणु
		control = bw;
		e = b43_tx_legacy_rate_phy_ctl_ent(bitrate);
		अगर (e) अणु
			control |= e->coding_rate;
			control |= e->modulation;
		पूर्ण
		control |= B43_TXH_PHY1_MODE_SISO;
	पूर्ण

	वापस control;
पूर्ण

अटल u8 b43_calc_fallback_rate(u8 bitrate, पूर्णांक gmode)
अणु
	चयन (bitrate) अणु
	हाल B43_CCK_RATE_1MB:
		वापस B43_CCK_RATE_1MB;
	हाल B43_CCK_RATE_2MB:
		वापस B43_CCK_RATE_1MB;
	हाल B43_CCK_RATE_5MB:
		वापस B43_CCK_RATE_2MB;
	हाल B43_CCK_RATE_11MB:
		वापस B43_CCK_RATE_5MB;
	/*
	 * Don't just fallback to CCK; it may be in 5GHz operation
	 * and falling back to CCK won't work out very well.
	 */
	हाल B43_OFDM_RATE_6MB:
		अगर (gmode)
			वापस B43_CCK_RATE_5MB;
		अन्यथा
			वापस B43_OFDM_RATE_6MB;
	हाल B43_OFDM_RATE_9MB:
		वापस B43_OFDM_RATE_6MB;
	हाल B43_OFDM_RATE_12MB:
		वापस B43_OFDM_RATE_9MB;
	हाल B43_OFDM_RATE_18MB:
		वापस B43_OFDM_RATE_12MB;
	हाल B43_OFDM_RATE_24MB:
		वापस B43_OFDM_RATE_18MB;
	हाल B43_OFDM_RATE_36MB:
		वापस B43_OFDM_RATE_24MB;
	हाल B43_OFDM_RATE_48MB:
		वापस B43_OFDM_RATE_36MB;
	हाल B43_OFDM_RATE_54MB:
		वापस B43_OFDM_RATE_48MB;
	पूर्ण
	B43_WARN_ON(1);
	वापस 0;
पूर्ण

/* Generate a TX data header. */
पूर्णांक b43_generate_txhdr(काष्ठा b43_wldev *dev,
		       u8 *_txhdr,
		       काष्ठा sk_buff *skb_frag,
		       काष्ठा ieee80211_tx_info *info,
		       u16 cookie)
अणु
	स्थिर अचिन्हित अक्षर *fragment_data = skb_frag->data;
	अचिन्हित पूर्णांक fragment_len = skb_frag->len;
	काष्ठा b43_txhdr *txhdr = (काष्ठा b43_txhdr *)_txhdr;
	स्थिर काष्ठा b43_phy *phy = &dev->phy;
	स्थिर काष्ठा ieee80211_hdr *wlhdr =
	    (स्थिर काष्ठा ieee80211_hdr *)fragment_data;
	पूर्णांक use_encryption = !!info->control.hw_key;
	__le16 fctl = wlhdr->frame_control;
	काष्ठा ieee80211_rate *fbrate;
	u8 rate, rate_fb;
	पूर्णांक rate_ofdm, rate_fb_ofdm;
	अचिन्हित पूर्णांक plcp_fragment_len;
	u32 mac_ctl = 0;
	u16 phy_ctl = 0;
	bool fill_phy_ctl1 = (phy->type == B43_PHYTYPE_LP ||
			      phy->type == B43_PHYTYPE_N ||
			      phy->type == B43_PHYTYPE_HT);
	u8 extra_ft = 0;
	काष्ठा ieee80211_rate *txrate;
	काष्ठा ieee80211_tx_rate *rates;

	स_रखो(txhdr, 0, माप(*txhdr));

	txrate = ieee80211_get_tx_rate(dev->wl->hw, info);
	rate = txrate ? txrate->hw_value : B43_CCK_RATE_1MB;
	rate_ofdm = b43_is_ofdm_rate(rate);
	fbrate = ieee80211_get_alt_retry_rate(dev->wl->hw, info, 0) ? : txrate;
	rate_fb = fbrate->hw_value;
	rate_fb_ofdm = b43_is_ofdm_rate(rate_fb);

	अगर (rate_ofdm)
		txhdr->phy_rate = b43_plcp_get_ratecode_ofdm(rate);
	अन्यथा
		txhdr->phy_rate = b43_plcp_get_ratecode_cck(rate);
	txhdr->mac_frame_ctl = wlhdr->frame_control;
	स_नकल(txhdr->tx_receiver, wlhdr->addr1, ETH_ALEN);

	/* Calculate duration क्रम fallback rate */
	अगर ((rate_fb == rate) ||
	    (wlhdr->duration_id & cpu_to_le16(0x8000)) ||
	    (wlhdr->duration_id == cpu_to_le16(0))) अणु
		/* If the fallback rate equals the normal rate or the
		 * dur_id field contains an AID, CFP magic or 0,
		 * use the original dur_id field. */
		txhdr->dur_fb = wlhdr->duration_id;
	पूर्ण अन्यथा अणु
		txhdr->dur_fb = ieee80211_generic_frame_duration(
			dev->wl->hw, info->control.vअगर, info->band,
			fragment_len, fbrate);
	पूर्ण

	plcp_fragment_len = fragment_len + FCS_LEN;
	अगर (use_encryption) अणु
		u8 key_idx = info->control.hw_key->hw_key_idx;
		काष्ठा b43_key *key;
		पूर्णांक wlhdr_len;
		माप_प्रकार iv_len;

		B43_WARN_ON(key_idx >= ARRAY_SIZE(dev->key));
		key = &(dev->key[key_idx]);

		अगर (unlikely(!key->keyconf)) अणु
			/* This key is invalid. This might only happen
			 * in a लघु समयframe after machine resume beक्रमe
			 * we were able to reconfigure keys.
			 * Drop this packet completely. Do not transmit it
			 * unencrypted to aव्योम leaking inक्रमmation. */
			वापस -ENOKEY;
		पूर्ण

		/* Hardware appends ICV. */
		plcp_fragment_len += info->control.hw_key->icv_len;

		key_idx = b43_kidx_to_fw(dev, key_idx);
		mac_ctl |= (key_idx << B43_TXH_MAC_KEYIDX_SHIFT) &
			   B43_TXH_MAC_KEYIDX;
		mac_ctl |= (key->algorithm << B43_TXH_MAC_KEYALG_SHIFT) &
			   B43_TXH_MAC_KEYALG;
		wlhdr_len = ieee80211_hdrlen(fctl);
		अगर (key->algorithm == B43_SEC_ALGO_TKIP) अणु
			u16 phase1key[5];
			पूर्णांक i;
			/* we give the phase1key and iv16 here, the key is stored in
			 * shm. With that the hardware can करो phase 2 and encryption.
			 */
			ieee80211_get_tkip_p1k(info->control.hw_key, skb_frag, phase1key);
			/* phase1key is in host endian. Copy to little-endian txhdr->iv. */
			क्रम (i = 0; i < 5; i++) अणु
				txhdr->iv[i * 2 + 0] = phase1key[i];
				txhdr->iv[i * 2 + 1] = phase1key[i] >> 8;
			पूर्ण
			/* iv16 */
			स_नकल(txhdr->iv + 10, ((u8 *) wlhdr) + wlhdr_len, 3);
		पूर्ण अन्यथा अणु
			iv_len = min_t(माप_प्रकार, info->control.hw_key->iv_len,
				     ARRAY_SIZE(txhdr->iv));
			स_नकल(txhdr->iv, ((u8 *) wlhdr) + wlhdr_len, iv_len);
		पूर्ण
	पूर्ण
	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_598:
		b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)(&txhdr->क्रमmat_598.plcp),
				      plcp_fragment_len, rate);
		अवरोध;
	हाल B43_FW_HDR_351:
		b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)(&txhdr->क्रमmat_351.plcp),
				      plcp_fragment_len, rate);
		अवरोध;
	हाल B43_FW_HDR_410:
		b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)(&txhdr->क्रमmat_410.plcp),
				      plcp_fragment_len, rate);
		अवरोध;
	पूर्ण
	b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)(&txhdr->plcp_fb),
			      plcp_fragment_len, rate_fb);

	/* Extra Frame Types */
	अगर (rate_fb_ofdm)
		extra_ft |= B43_TXH_EFT_FB_OFDM;
	अन्यथा
		extra_ft |= B43_TXH_EFT_FB_CCK;

	/* Set channel radio code. Note that the micrcode ORs 0x100 to
	 * this value beक्रमe comparing it to the value in SHM, अगर this
	 * is a 5Ghz packet.
	 */
	txhdr->chan_radio_code = phy->channel;

	/* PHY TX Control word */
	अगर (rate_ofdm)
		phy_ctl |= B43_TXH_PHY_ENC_OFDM;
	अन्यथा
		phy_ctl |= B43_TXH_PHY_ENC_CCK;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		phy_ctl |= B43_TXH_PHY_SHORTPRMBL;

	चयन (b43_ieee80211_antenna_sanitize(dev, 0)) अणु
	हाल 0: /* Default */
		phy_ctl |= B43_TXH_PHY_ANT01AUTO;
		अवरोध;
	हाल 1: /* Antenna 0 */
		phy_ctl |= B43_TXH_PHY_ANT0;
		अवरोध;
	हाल 2: /* Antenna 1 */
		phy_ctl |= B43_TXH_PHY_ANT1;
		अवरोध;
	हाल 3: /* Antenna 2 */
		phy_ctl |= B43_TXH_PHY_ANT2;
		अवरोध;
	हाल 4: /* Antenna 3 */
		phy_ctl |= B43_TXH_PHY_ANT3;
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण

	rates = info->control.rates;
	/* MAC control */
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		mac_ctl |= B43_TXH_MAC_ACK;
	/* use hardware sequence counter as the non-TID counter */
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
		mac_ctl |= B43_TXH_MAC_HWSEQ;
	अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
		mac_ctl |= B43_TXH_MAC_STMSDU;
	अगर (!phy->gmode)
		mac_ctl |= B43_TXH_MAC_5GHZ;

	/* Overग_लिखो rates[0].count to make the retry calculation
	 * in the tx status easier. need the actual retry limit to
	 * detect whether the fallback rate was used.
	 */
	अगर ((rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) ||
	    (rates[0].count <= dev->wl->hw->conf.दीर्घ_frame_max_tx_count)) अणु
		rates[0].count = dev->wl->hw->conf.दीर्घ_frame_max_tx_count;
		mac_ctl |= B43_TXH_MAC_LONGFRAME;
	पूर्ण अन्यथा अणु
		rates[0].count = dev->wl->hw->conf.लघु_frame_max_tx_count;
	पूर्ण

	/* Generate the RTS or CTS-to-self frame */
	अगर ((rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) ||
	    (rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)) अणु
		अचिन्हित पूर्णांक len;
		काष्ठा ieee80211_hdr *hdr;
		पूर्णांक rts_rate, rts_rate_fb;
		पूर्णांक rts_rate_ofdm, rts_rate_fb_ofdm;
		काष्ठा b43_plcp_hdr6 *plcp;
		काष्ठा ieee80211_rate *rts_cts_rate;

		rts_cts_rate = ieee80211_get_rts_cts_rate(dev->wl->hw, info);

		rts_rate = rts_cts_rate ? rts_cts_rate->hw_value : B43_CCK_RATE_1MB;
		rts_rate_ofdm = b43_is_ofdm_rate(rts_rate);
		rts_rate_fb = b43_calc_fallback_rate(rts_rate, phy->gmode);
		rts_rate_fb_ofdm = b43_is_ofdm_rate(rts_rate_fb);

		अगर (rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
			काष्ठा ieee80211_cts *cts;

			चयन (dev->fw.hdr_क्रमmat) अणु
			हाल B43_FW_HDR_598:
				cts = (काष्ठा ieee80211_cts *)
					(txhdr->क्रमmat_598.rts_frame);
				अवरोध;
			हाल B43_FW_HDR_351:
				cts = (काष्ठा ieee80211_cts *)
					(txhdr->क्रमmat_351.rts_frame);
				अवरोध;
			हाल B43_FW_HDR_410:
				cts = (काष्ठा ieee80211_cts *)
					(txhdr->क्रमmat_410.rts_frame);
				अवरोध;
			पूर्ण
			ieee80211_ctstoself_get(dev->wl->hw, info->control.vअगर,
						fragment_data, fragment_len,
						info, cts);
			mac_ctl |= B43_TXH_MAC_SENDCTS;
			len = माप(काष्ठा ieee80211_cts);
		पूर्ण अन्यथा अणु
			काष्ठा ieee80211_rts *rts;

			चयन (dev->fw.hdr_क्रमmat) अणु
			हाल B43_FW_HDR_598:
				rts = (काष्ठा ieee80211_rts *)
					(txhdr->क्रमmat_598.rts_frame);
				अवरोध;
			हाल B43_FW_HDR_351:
				rts = (काष्ठा ieee80211_rts *)
					(txhdr->क्रमmat_351.rts_frame);
				अवरोध;
			हाल B43_FW_HDR_410:
				rts = (काष्ठा ieee80211_rts *)
					(txhdr->क्रमmat_410.rts_frame);
				अवरोध;
			पूर्ण
			ieee80211_rts_get(dev->wl->hw, info->control.vअगर,
					  fragment_data, fragment_len,
					  info, rts);
			mac_ctl |= B43_TXH_MAC_SENDRTS;
			len = माप(काष्ठा ieee80211_rts);
		पूर्ण
		len += FCS_LEN;

		/* Generate the PLCP headers क्रम the RTS/CTS frame */
		चयन (dev->fw.hdr_क्रमmat) अणु
		हाल B43_FW_HDR_598:
			plcp = &txhdr->क्रमmat_598.rts_plcp;
			अवरोध;
		हाल B43_FW_HDR_351:
			plcp = &txhdr->क्रमmat_351.rts_plcp;
			अवरोध;
		हाल B43_FW_HDR_410:
			plcp = &txhdr->क्रमmat_410.rts_plcp;
			अवरोध;
		पूर्ण
		b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)plcp,
				      len, rts_rate);
		plcp = &txhdr->rts_plcp_fb;
		b43_generate_plcp_hdr((काष्ठा b43_plcp_hdr4 *)plcp,
				      len, rts_rate_fb);

		चयन (dev->fw.hdr_क्रमmat) अणु
		हाल B43_FW_HDR_598:
			hdr = (काष्ठा ieee80211_hdr *)
				(&txhdr->क्रमmat_598.rts_frame);
			अवरोध;
		हाल B43_FW_HDR_351:
			hdr = (काष्ठा ieee80211_hdr *)
				(&txhdr->क्रमmat_351.rts_frame);
			अवरोध;
		हाल B43_FW_HDR_410:
			hdr = (काष्ठा ieee80211_hdr *)
				(&txhdr->क्रमmat_410.rts_frame);
			अवरोध;
		पूर्ण
		txhdr->rts_dur_fb = hdr->duration_id;

		अगर (rts_rate_ofdm) अणु
			extra_ft |= B43_TXH_EFT_RTS_OFDM;
			txhdr->phy_rate_rts =
			    b43_plcp_get_ratecode_ofdm(rts_rate);
		पूर्ण अन्यथा अणु
			extra_ft |= B43_TXH_EFT_RTS_CCK;
			txhdr->phy_rate_rts =
			    b43_plcp_get_ratecode_cck(rts_rate);
		पूर्ण
		अगर (rts_rate_fb_ofdm)
			extra_ft |= B43_TXH_EFT_RTSFB_OFDM;
		अन्यथा
			extra_ft |= B43_TXH_EFT_RTSFB_CCK;

		अगर (rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS &&
		    fill_phy_ctl1) अणु
			txhdr->phy_ctl1_rts = cpu_to_le16(
				b43_generate_tx_phy_ctl1(dev, rts_rate));
			txhdr->phy_ctl1_rts_fb = cpu_to_le16(
				b43_generate_tx_phy_ctl1(dev, rts_rate_fb));
		पूर्ण
	पूर्ण

	/* Magic cookie */
	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_598:
		txhdr->क्रमmat_598.cookie = cpu_to_le16(cookie);
		अवरोध;
	हाल B43_FW_HDR_351:
		txhdr->क्रमmat_351.cookie = cpu_to_le16(cookie);
		अवरोध;
	हाल B43_FW_HDR_410:
		txhdr->क्रमmat_410.cookie = cpu_to_le16(cookie);
		अवरोध;
	पूर्ण

	अगर (fill_phy_ctl1) अणु
		txhdr->phy_ctl1 =
			cpu_to_le16(b43_generate_tx_phy_ctl1(dev, rate));
		txhdr->phy_ctl1_fb =
			cpu_to_le16(b43_generate_tx_phy_ctl1(dev, rate_fb));
	पूर्ण

	/* Apply the bitfields */
	txhdr->mac_ctl = cpu_to_le32(mac_ctl);
	txhdr->phy_ctl = cpu_to_le16(phy_ctl);
	txhdr->extra_ft = extra_ft;

	वापस 0;
पूर्ण

अटल s8 b43_rssi_postprocess(काष्ठा b43_wldev *dev,
			       u8 in_rssi, पूर्णांक ofdm,
			       पूर्णांक adjust_2053, पूर्णांक adjust_2050)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	काष्ठा b43_phy_g *gphy = phy->g;
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
			अगर (dev->dev->bus_sprom->
			    boardflags_lo & B43_BFL_RSSI) अणु
				अगर (in_rssi > 63)
					in_rssi = 63;
				B43_WARN_ON(phy->type != B43_PHYTYPE_G);
				पंचांगp = gphy->nrssi_lt[in_rssi];
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
			अगर (phy->type == B43_PHYTYPE_G && adjust_2050)
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

	वापस (s8) पंचांगp;
पूर्ण

व्योम b43_rx(काष्ठा b43_wldev *dev, काष्ठा sk_buff *skb, स्थिर व्योम *_rxhdr)
अणु
	काष्ठा ieee80211_rx_status status;
	काष्ठा b43_plcp_hdr6 *plcp;
	काष्ठा ieee80211_hdr *wlhdr;
	स्थिर काष्ठा b43_rxhdr_fw4 *rxhdr = _rxhdr;
	__le16 fctl;
	u16 phystat0, phystat3;
	u16 chanstat, maस_समय;
	u32 macstat;
	u16 chanid;
	पूर्णांक padding, rate_idx;

	स_रखो(&status, 0, माप(status));

	/* Get metadata about the frame from the header. */
	phystat0 = le16_to_cpu(rxhdr->phy_status0);
	phystat3 = le16_to_cpu(rxhdr->phy_status3);
	चयन (dev->fw.hdr_क्रमmat) अणु
	हाल B43_FW_HDR_598:
		macstat = le32_to_cpu(rxhdr->क्रमmat_598.mac_status);
		maस_समय = le16_to_cpu(rxhdr->क्रमmat_598.mac_समय);
		chanstat = le16_to_cpu(rxhdr->क्रमmat_598.channel);
		अवरोध;
	हाल B43_FW_HDR_410:
	हाल B43_FW_HDR_351:
		macstat = le32_to_cpu(rxhdr->क्रमmat_351.mac_status);
		maस_समय = le16_to_cpu(rxhdr->क्रमmat_351.mac_समय);
		chanstat = le16_to_cpu(rxhdr->क्रमmat_351.channel);
		अवरोध;
	पूर्ण

	अगर (unlikely(macstat & B43_RX_MAC_FCSERR)) अणु
		dev->wl->ieee_stats.करोt11FCSErrorCount++;
		status.flag |= RX_FLAG_FAILED_FCS_CRC;
	पूर्ण
	अगर (unlikely(phystat0 & (B43_RX_PHYST0_PLCPHCF | B43_RX_PHYST0_PLCPFV)))
		status.flag |= RX_FLAG_FAILED_PLCP_CRC;
	अगर (phystat0 & B43_RX_PHYST0_SHORTPRMBL)
		status.enc_flags |= RX_ENC_FLAG_SHORTPRE;
	अगर (macstat & B43_RX_MAC_DECERR) अणु
		/* Decryption with the given key failed.
		 * Drop the packet. We also won't be able to decrypt it with
		 * the key in software. */
		जाओ drop;
	पूर्ण

	/* Skip PLCP and padding */
	padding = (macstat & B43_RX_MAC_PADDING) ? 2 : 0;
	अगर (unlikely(skb->len < (माप(काष्ठा b43_plcp_hdr6) + padding))) अणु
		b43dbg(dev->wl, "RX: Packet size underrun (1)\n");
		जाओ drop;
	पूर्ण
	plcp = (काष्ठा b43_plcp_hdr6 *)(skb->data + padding);
	skb_pull(skb, माप(काष्ठा b43_plcp_hdr6) + padding);
	/* The skb contains the Wireless Header + payload data now */
	अगर (unlikely(skb->len < (2 + 2 + 6 /*minimum hdr */  + FCS_LEN))) अणु
		b43dbg(dev->wl, "RX: Packet size underrun (2)\n");
		जाओ drop;
	पूर्ण
	wlhdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fctl = wlhdr->frame_control;

	अगर (macstat & B43_RX_MAC_DEC) अणु
		अचिन्हित पूर्णांक keyidx;
		पूर्णांक wlhdr_len;

		keyidx = ((macstat & B43_RX_MAC_KEYIDX)
			  >> B43_RX_MAC_KEYIDX_SHIFT);
		/* We must adjust the key index here. We want the "physical"
		 * key index, but the ucode passed it slightly dअगरferent.
		 */
		keyidx = b43_kidx_to_raw(dev, keyidx);
		B43_WARN_ON(keyidx >= ARRAY_SIZE(dev->key));

		अगर (dev->key[keyidx].algorithm != B43_SEC_ALGO_NONE) अणु
			wlhdr_len = ieee80211_hdrlen(fctl);
			अगर (unlikely(skb->len < (wlhdr_len + 3))) अणु
				b43dbg(dev->wl,
				       "RX: Packet size underrun (3)\n");
				जाओ drop;
			पूर्ण
			status.flag |= RX_FLAG_DECRYPTED;
		पूर्ण
	पूर्ण

	/* Link quality statistics */
	चयन (chanstat & B43_RX_CHAN_PHYTYPE) अणु
	हाल B43_PHYTYPE_HT:
		/* TODO: is max the right choice? */
		status.संकेत = max_t(__s8,
			max(rxhdr->phy_ht_घातer0, rxhdr->phy_ht_घातer1),
			rxhdr->phy_ht_घातer2);
		अवरोध;
	हाल B43_PHYTYPE_N:
		/* Broadcom has code क्रम min and avg, but always uses max */
		अगर (rxhdr->घातer0 == 16 || rxhdr->घातer0 == 32)
			status.संकेत = max(rxhdr->घातer1, rxhdr->घातer2);
		अन्यथा
			status.संकेत = max(rxhdr->घातer0, rxhdr->घातer1);
		अवरोध;
	हाल B43_PHYTYPE_B:
	हाल B43_PHYTYPE_G:
	हाल B43_PHYTYPE_LP:
		status.संकेत = b43_rssi_postprocess(dev, rxhdr->jssi,
						  (phystat0 & B43_RX_PHYST0_OFDM),
						  (phystat0 & B43_RX_PHYST0_GAINCTL),
						  (phystat3 & B43_RX_PHYST3_TRSTATE));
		अवरोध;
	पूर्ण

	अगर (phystat0 & B43_RX_PHYST0_OFDM)
		rate_idx = b43_plcp_get_bitrate_idx_ofdm(plcp,
					!!(chanstat & B43_RX_CHAN_5GHZ));
	अन्यथा
		rate_idx = b43_plcp_get_bitrate_idx_cck(plcp);
	अगर (unlikely(rate_idx == -1)) अणु
		/* PLCP seems to be corrupted.
		 * Drop the frame, अगर we are not पूर्णांकerested in corrupted frames. */
		अगर (!(dev->wl->filter_flags & FIF_PLCPFAIL))
			जाओ drop;
	पूर्ण
	status.rate_idx = rate_idx;
	status.antenna = !!(phystat0 & B43_RX_PHYST0_ANT);

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

		b43_tsf_पढ़ो(dev, &status.maस_समय);
		low_maस_समय_now = status.maस_समय;
		status.maस_समय = status.maस_समय & ~0xFFFFULL;
		status.maस_समय += maस_समय;
		अगर (low_maस_समय_now <= maस_समय)
			status.maस_समय -= 0x10000;
		status.flag |= RX_FLAG_MACTIME_START;
	पूर्ण

	chanid = (chanstat & B43_RX_CHAN_ID) >> B43_RX_CHAN_ID_SHIFT;
	चयन (chanstat & B43_RX_CHAN_PHYTYPE) अणु
	हाल B43_PHYTYPE_G:
		status.band = NL80211_BAND_2GHZ;
		/* Somewhere between 478.104 and 508.1084 firmware क्रम G-PHY
		 * has been modअगरied to be compatible with N-PHY and others.
		 */
		अगर (dev->fw.rev >= 508)
			status.freq = ieee80211_channel_to_frequency(chanid, status.band);
		अन्यथा
			status.freq = chanid + 2400;
		अवरोध;
	हाल B43_PHYTYPE_N:
	हाल B43_PHYTYPE_LP:
	हाल B43_PHYTYPE_HT:
		/* chanid is the SHM channel cookie. Which is the plain
		 * channel number in b43. */
		अगर (chanstat & B43_RX_CHAN_5GHZ)
			status.band = NL80211_BAND_5GHZ;
		अन्यथा
			status.band = NL80211_BAND_2GHZ;
		status.freq =
			ieee80211_channel_to_frequency(chanid, status.band);
		अवरोध;
	शेष:
		B43_WARN_ON(1);
		जाओ drop;
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), &status, माप(status));
	ieee80211_rx_ni(dev->wl->hw, skb);

#अगर B43_DEBUG
	dev->rx_count++;
#पूर्ण_अगर
	वापस;
drop:
	dev_kमुक्त_skb_any(skb);
पूर्ण

व्योम b43_handle_txstatus(काष्ठा b43_wldev *dev,
			 स्थिर काष्ठा b43_txstatus *status)
अणु
	b43_debugfs_log_txstat(dev, status);

	अगर (status->पूर्णांकermediate)
		वापस;
	अगर (status->क्रम_ampdu)
		वापस;
	अगर (!status->acked)
		dev->wl->ieee_stats.करोt11ACKFailureCount++;
	अगर (status->rts_count) अणु
		अगर (status->rts_count == 0xF)	//FIXME
			dev->wl->ieee_stats.करोt11RTSFailureCount++;
		अन्यथा
			dev->wl->ieee_stats.करोt11RTSSuccessCount++;
	पूर्ण

	अगर (b43_using_pio_transfers(dev))
		b43_pio_handle_txstatus(dev, status);
	अन्यथा
		b43_dma_handle_txstatus(dev, status);

	b43_phy_txघातer_check(dev, 0);
पूर्ण

/* Fill out the mac80211 TXstatus report based on the b43-specअगरic
 * txstatus report data. This वापसs a boolean whether the frame was
 * successfully transmitted. */
bool b43_fill_txstatus_report(काष्ठा b43_wldev *dev,
			      काष्ठा ieee80211_tx_info *report,
			      स्थिर काष्ठा b43_txstatus *status)
अणु
	bool frame_success = true;
	पूर्णांक retry_limit;

	/* preserve the confiured retry limit beक्रमe clearing the status
	 * The xmit function has overwritten the rc's value with the actual
	 * retry limit करोne by the hardware */
	retry_limit = report->status.rates[0].count;
	ieee80211_tx_info_clear_status(report);

	अगर (status->acked) अणु
		/* The frame was ACKed. */
		report->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण अन्यथा अणु
		/* The frame was not ACKed... */
		अगर (!(report->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
			/* ...but we expected an ACK. */
			frame_success = false;
		पूर्ण
	पूर्ण
	अगर (status->frame_count == 0) अणु
		/* The frame was not transmitted at all. */
		report->status.rates[0].count = 0;
	पूर्ण अन्यथा अगर (status->rts_count > dev->wl->hw->conf.लघु_frame_max_tx_count) अणु
		/*
		 * If the लघु retries (RTS, not data frame) have exceeded
		 * the limit, the hw will not have tried the selected rate,
		 * but will have used the fallback rate instead.
		 * Don't let the rate control count attempts क्रम the selected
		 * rate in this हाल, otherwise the statistics will be off.
		 */
		report->status.rates[0].count = 0;
		report->status.rates[1].count = status->frame_count;
	पूर्ण अन्यथा अणु
		अगर (status->frame_count > retry_limit) अणु
			report->status.rates[0].count = retry_limit;
			report->status.rates[1].count = status->frame_count -
					retry_limit;

		पूर्ण अन्यथा अणु
			report->status.rates[0].count = status->frame_count;
			report->status.rates[1].idx = -1;
		पूर्ण
	पूर्ण

	वापस frame_success;
पूर्ण

/* Stop any TX operation on the device (suspend the hardware queues) */
व्योम b43_tx_suspend(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_using_pio_transfers(dev))
		b43_pio_tx_suspend(dev);
	अन्यथा
		b43_dma_tx_suspend(dev);
पूर्ण

/* Resume any TX operation on the device (resume the hardware queues) */
व्योम b43_tx_resume(काष्ठा b43_wldev *dev)
अणु
	अगर (b43_using_pio_transfers(dev))
		b43_pio_tx_resume(dev);
	अन्यथा
		b43_dma_tx_resume(dev);
पूर्ण
