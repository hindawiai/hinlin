<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright(c) 2015 - 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <linux/kcov.h>
#समावेश <linux/bitops.h>
#समावेश <net/mac80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "led.h"
#समावेश "mesh.h"
#समावेश "wep.h"
#समावेश "wpa.h"
#समावेश "tkip.h"
#समावेश "wme.h"
#समावेश "rate.h"

/*
 * monitor mode reception
 *
 * This function cleans up the SKB, i.e. it हटाओs all the stuff
 * only useful क्रम monitoring.
 */
अटल काष्ठा sk_buff *ieee80211_clean_skb(काष्ठा sk_buff *skb,
					   अचिन्हित पूर्णांक present_fcs_len,
					   अचिन्हित पूर्णांक rtap_space)
अणु
	काष्ठा ieee80211_hdr *hdr;
	अचिन्हित पूर्णांक hdrlen;
	__le16 fc;

	अगर (present_fcs_len)
		__pskb_trim(skb, skb->len - present_fcs_len);
	__pskb_pull(skb, rtap_space);

	hdr = (व्योम *)skb->data;
	fc = hdr->frame_control;

	/*
	 * Remove the HT-Control field (अगर present) on management
	 * frames after we've sent the frame to monitoring. We
	 * (currently) करोn't need it, and don't properly parse
	 * frames with it present, due to the assumption of a
	 * fixed management header length.
	 */
	अगर (likely(!ieee80211_is_mgmt(fc) || !ieee80211_has_order(fc)))
		वापस skb;

	hdrlen = ieee80211_hdrlen(fc);
	hdr->frame_control &= ~cpu_to_le16(IEEE80211_FCTL_ORDER);

	अगर (!pskb_may_pull(skb, hdrlen)) अणु
		dev_kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	स_हटाओ(skb->data + IEEE80211_HT_CTL_LEN, skb->data,
		hdrlen - IEEE80211_HT_CTL_LEN);
	__pskb_pull(skb, IEEE80211_HT_CTL_LEN);

	वापस skb;
पूर्ण

अटल अंतरभूत bool should_drop_frame(काष्ठा sk_buff *skb, पूर्णांक present_fcs_len,
				     अचिन्हित पूर्णांक rtap_space)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr;

	hdr = (व्योम *)(skb->data + rtap_space);

	अगर (status->flag & (RX_FLAG_FAILED_FCS_CRC |
			    RX_FLAG_FAILED_PLCP_CRC |
			    RX_FLAG_ONLY_MONITOR |
			    RX_FLAG_NO_PSDU))
		वापस true;

	अगर (unlikely(skb->len < 16 + present_fcs_len + rtap_space))
		वापस true;

	अगर (ieee80211_is_ctl(hdr->frame_control) &&
	    !ieee80211_is_pspoll(hdr->frame_control) &&
	    !ieee80211_is_back_req(hdr->frame_control))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
ieee80211_rx_radiotap_hdrlen(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_rx_status *status,
			     काष्ठा sk_buff *skb)
अणु
	पूर्णांक len;

	/* always present fields */
	len = माप(काष्ठा ieee80211_radiotap_header) + 8;

	/* allocate extra biपंचांगaps */
	अगर (status->chains)
		len += 4 * hweight8(status->chains);
	/* venकरोr presence biपंचांगap */
	अगर (status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA)
		len += 4;

	अगर (ieee80211_have_rx_बारtamp(status)) अणु
		len = ALIGN(len, 8);
		len += 8;
	पूर्ण
	अगर (ieee80211_hw_check(&local->hw, SIGNAL_DBM))
		len += 1;

	/* antenna field, अगर we करोn't have per-chain info */
	अगर (!status->chains)
		len += 1;

	/* padding क्रम RX_FLAGS अगर necessary */
	len = ALIGN(len, 2);

	अगर (status->encoding == RX_ENC_HT) /* HT info */
		len += 3;

	अगर (status->flag & RX_FLAG_AMPDU_DETAILS) अणु
		len = ALIGN(len, 4);
		len += 8;
	पूर्ण

	अगर (status->encoding == RX_ENC_VHT) अणु
		len = ALIGN(len, 2);
		len += 12;
	पूर्ण

	अगर (local->hw.radiotap_बारtamp.units_pos >= 0) अणु
		len = ALIGN(len, 8);
		len += 12;
	पूर्ण

	अगर (status->encoding == RX_ENC_HE &&
	    status->flag & RX_FLAG_RADIOTAP_HE) अणु
		len = ALIGN(len, 2);
		len += 12;
		BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he) != 12);
	पूर्ण

	अगर (status->encoding == RX_ENC_HE &&
	    status->flag & RX_FLAG_RADIOTAP_HE_MU) अणु
		len = ALIGN(len, 2);
		len += 12;
		BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he_mu) != 12);
	पूर्ण

	अगर (status->flag & RX_FLAG_NO_PSDU)
		len += 1;

	अगर (status->flag & RX_FLAG_RADIOTAP_LSIG) अणु
		len = ALIGN(len, 2);
		len += 4;
		BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_lsig) != 4);
	पूर्ण

	अगर (status->chains) अणु
		/* antenna and antenna संकेत fields */
		len += 2 * hweight8(status->chains);
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) अणु
		काष्ठा ieee80211_venकरोr_radiotap *rtap;
		पूर्णांक venकरोr_data_offset = 0;

		/*
		 * The position to look at depends on the existence (or non-
		 * existence) of other elements, so take that पूर्णांकo account...
		 */
		अगर (status->flag & RX_FLAG_RADIOTAP_HE)
			venकरोr_data_offset +=
				माप(काष्ठा ieee80211_radiotap_he);
		अगर (status->flag & RX_FLAG_RADIOTAP_HE_MU)
			venकरोr_data_offset +=
				माप(काष्ठा ieee80211_radiotap_he_mu);
		अगर (status->flag & RX_FLAG_RADIOTAP_LSIG)
			venकरोr_data_offset +=
				माप(काष्ठा ieee80211_radiotap_lsig);

		rtap = (व्योम *)&skb->data[venकरोr_data_offset];

		/* alignment क्रम fixed 6-byte venकरोr data header */
		len = ALIGN(len, 2);
		/* venकरोr data header */
		len += 6;
		अगर (WARN_ON(rtap->align == 0))
			rtap->align = 1;
		len = ALIGN(len, rtap->align);
		len += rtap->len + rtap->pad;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम ieee80211_handle_mu_mimo_mon(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा sk_buff *skb,
					 पूर्णांक rtap_space)
अणु
	काष्ठा अणु
		काष्ठा ieee80211_hdr_3addr hdr;
		u8 category;
		u8 action_code;
	पूर्ण __packed __aligned(2) action;

	अगर (!sdata)
		वापस;

	BUILD_BUG_ON(माप(action) != IEEE80211_MIN_ACTION_SIZE + 1);

	अगर (skb->len < rtap_space + माप(action) +
		       VHT_MUMIMO_GROUPS_DATA_LEN)
		वापस;

	अगर (!is_valid_ether_addr(sdata->u.mntr.mu_follow_addr))
		वापस;

	skb_copy_bits(skb, rtap_space, &action, माप(action));

	अगर (!ieee80211_is_action(action.hdr.frame_control))
		वापस;

	अगर (action.category != WLAN_CATEGORY_VHT)
		वापस;

	अगर (action.action_code != WLAN_VHT_ACTION_GROUPID_MGMT)
		वापस;

	अगर (!ether_addr_equal(action.hdr.addr1, sdata->u.mntr.mu_follow_addr))
		वापस;

	skb = skb_copy(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb_queue_tail(&sdata->skb_queue, skb);
	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

/*
 * ieee80211_add_rx_radiotap_header - add radiotap header
 *
 * add a radiotap header containing all the fields which the hardware provided.
 */
अटल व्योम
ieee80211_add_rx_radiotap_header(काष्ठा ieee80211_local *local,
				 काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_rate *rate,
				 पूर्णांक rtap_len, bool has_fcs)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_radiotap_header *rthdr;
	अचिन्हित अक्षर *pos;
	__le32 *it_present;
	u32 it_present_val;
	u16 rx_flags = 0;
	u16 channel_flags = 0;
	पूर्णांक mpdulen, chain;
	अचिन्हित दीर्घ chains = status->chains;
	काष्ठा ieee80211_venकरोr_radiotap rtap = अणुपूर्ण;
	काष्ठा ieee80211_radiotap_he he = अणुपूर्ण;
	काष्ठा ieee80211_radiotap_he_mu he_mu = अणुपूर्ण;
	काष्ठा ieee80211_radiotap_lsig lsig = अणुपूर्ण;

	अगर (status->flag & RX_FLAG_RADIOTAP_HE) अणु
		he = *(काष्ठा ieee80211_radiotap_he *)skb->data;
		skb_pull(skb, माप(he));
		WARN_ON_ONCE(status->encoding != RX_ENC_HE);
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_HE_MU) अणु
		he_mu = *(काष्ठा ieee80211_radiotap_he_mu *)skb->data;
		skb_pull(skb, माप(he_mu));
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_LSIG) अणु
		lsig = *(काष्ठा ieee80211_radiotap_lsig *)skb->data;
		skb_pull(skb, माप(lsig));
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) अणु
		rtap = *(काष्ठा ieee80211_venकरोr_radiotap *)skb->data;
		/* rtap.len and rtap.pad are unकरोne immediately */
		skb_pull(skb, माप(rtap) + rtap.len + rtap.pad);
	पूर्ण

	mpdulen = skb->len;
	अगर (!(has_fcs && ieee80211_hw_check(&local->hw, RX_INCLUDES_FCS)))
		mpdulen += FCS_LEN;

	rthdr = skb_push(skb, rtap_len);
	स_रखो(rthdr, 0, rtap_len - rtap.len - rtap.pad);
	it_present = &rthdr->it_present;

	/* radiotap header, set always present flags */
	rthdr->it_len = cpu_to_le16(rtap_len);
	it_present_val = BIT(IEEE80211_RADIOTAP_FLAGS) |
			 BIT(IEEE80211_RADIOTAP_CHANNEL) |
			 BIT(IEEE80211_RADIOTAP_RX_FLAGS);

	अगर (!status->chains)
		it_present_val |= BIT(IEEE80211_RADIOTAP_ANTENNA);

	क्रम_each_set_bit(chain, &chains, IEEE80211_MAX_CHAINS) अणु
		it_present_val |=
			BIT(IEEE80211_RADIOTAP_EXT) |
			BIT(IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE);
		put_unaligned_le32(it_present_val, it_present);
		it_present++;
		it_present_val = BIT(IEEE80211_RADIOTAP_ANTENNA) |
				 BIT(IEEE80211_RADIOTAP_DBM_ANTSIGNAL);
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) अणु
		it_present_val |= BIT(IEEE80211_RADIOTAP_VENDOR_NAMESPACE) |
				  BIT(IEEE80211_RADIOTAP_EXT);
		put_unaligned_le32(it_present_val, it_present);
		it_present++;
		it_present_val = rtap.present;
	पूर्ण

	put_unaligned_le32(it_present_val, it_present);

	pos = (व्योम *)(it_present + 1);

	/* the order of the following fields is important */

	/* IEEE80211_RADIOTAP_TSFT */
	अगर (ieee80211_have_rx_बारtamp(status)) अणु
		/* padding */
		जबतक ((pos - (u8 *)rthdr) & 7)
			*pos++ = 0;
		put_unaligned_le64(
			ieee80211_calculate_rx_बारtamp(local, status,
							 mpdulen, 0),
			pos);
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_TSFT);
		pos += 8;
	पूर्ण

	/* IEEE80211_RADIOTAP_FLAGS */
	अगर (has_fcs && ieee80211_hw_check(&local->hw, RX_INCLUDES_FCS))
		*pos |= IEEE80211_RADIOTAP_F_FCS;
	अगर (status->flag & (RX_FLAG_FAILED_FCS_CRC | RX_FLAG_FAILED_PLCP_CRC))
		*pos |= IEEE80211_RADIOTAP_F_BADFCS;
	अगर (status->enc_flags & RX_ENC_FLAG_SHORTPRE)
		*pos |= IEEE80211_RADIOTAP_F_SHORTPRE;
	pos++;

	/* IEEE80211_RADIOTAP_RATE */
	अगर (!rate || status->encoding != RX_ENC_LEGACY) अणु
		/*
		 * Without rate inक्रमmation करोn't add it. If we have,
		 * MCS inक्रमmation is a separate field in radiotap,
		 * added below. The byte here is needed as padding
		 * क्रम the channel though, so initialise it to 0.
		 */
		*pos = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक shअगरt = 0;
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_RATE);
		अगर (status->bw == RATE_INFO_BW_10)
			shअगरt = 1;
		अन्यथा अगर (status->bw == RATE_INFO_BW_5)
			shअगरt = 2;
		*pos = DIV_ROUND_UP(rate->bitrate, 5 * (1 << shअगरt));
	पूर्ण
	pos++;

	/* IEEE80211_RADIOTAP_CHANNEL */
	/* TODO: frequency offset in KHz */
	put_unaligned_le16(status->freq, pos);
	pos += 2;
	अगर (status->bw == RATE_INFO_BW_10)
		channel_flags |= IEEE80211_CHAN_HALF;
	अन्यथा अगर (status->bw == RATE_INFO_BW_5)
		channel_flags |= IEEE80211_CHAN_QUARTER;

	अगर (status->band == NL80211_BAND_5GHZ ||
	    status->band == NL80211_BAND_6GHZ)
		channel_flags |= IEEE80211_CHAN_OFDM | IEEE80211_CHAN_5GHZ;
	अन्यथा अगर (status->encoding != RX_ENC_LEGACY)
		channel_flags |= IEEE80211_CHAN_DYN | IEEE80211_CHAN_2GHZ;
	अन्यथा अगर (rate && rate->flags & IEEE80211_RATE_ERP_G)
		channel_flags |= IEEE80211_CHAN_OFDM | IEEE80211_CHAN_2GHZ;
	अन्यथा अगर (rate)
		channel_flags |= IEEE80211_CHAN_CCK | IEEE80211_CHAN_2GHZ;
	अन्यथा
		channel_flags |= IEEE80211_CHAN_2GHZ;
	put_unaligned_le16(channel_flags, pos);
	pos += 2;

	/* IEEE80211_RADIOTAP_DBM_ANTSIGNAL */
	अगर (ieee80211_hw_check(&local->hw, SIGNAL_DBM) &&
	    !(status->flag & RX_FLAG_NO_SIGNAL_VAL)) अणु
		*pos = status->संकेत;
		rthdr->it_present |=
			cpu_to_le32(1 << IEEE80211_RADIOTAP_DBM_ANTSIGNAL);
		pos++;
	पूर्ण

	/* IEEE80211_RADIOTAP_LOCK_QUALITY is missing */

	अगर (!status->chains) अणु
		/* IEEE80211_RADIOTAP_ANTENNA */
		*pos = status->antenna;
		pos++;
	पूर्ण

	/* IEEE80211_RADIOTAP_DB_ANTNOISE is not used */

	/* IEEE80211_RADIOTAP_RX_FLAGS */
	/* ensure 2 byte alignment क्रम the 2 byte field as required */
	अगर ((pos - (u8 *)rthdr) & 1)
		*pos++ = 0;
	अगर (status->flag & RX_FLAG_FAILED_PLCP_CRC)
		rx_flags |= IEEE80211_RADIOTAP_F_RX_BADPLCP;
	put_unaligned_le16(rx_flags, pos);
	pos += 2;

	अगर (status->encoding == RX_ENC_HT) अणु
		अचिन्हित पूर्णांक stbc;

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_MCS);
		*pos++ = local->hw.radiotap_mcs_details;
		*pos = 0;
		अगर (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			*pos |= IEEE80211_RADIOTAP_MCS_SGI;
		अगर (status->bw == RATE_INFO_BW_40)
			*pos |= IEEE80211_RADIOTAP_MCS_BW_40;
		अगर (status->enc_flags & RX_ENC_FLAG_HT_GF)
			*pos |= IEEE80211_RADIOTAP_MCS_FMT_GF;
		अगर (status->enc_flags & RX_ENC_FLAG_LDPC)
			*pos |= IEEE80211_RADIOTAP_MCS_FEC_LDPC;
		stbc = (status->enc_flags & RX_ENC_FLAG_STBC_MASK) >> RX_ENC_FLAG_STBC_SHIFT;
		*pos |= stbc << IEEE80211_RADIOTAP_MCS_STBC_SHIFT;
		pos++;
		*pos++ = status->rate_idx;
	पूर्ण

	अगर (status->flag & RX_FLAG_AMPDU_DETAILS) अणु
		u16 flags = 0;

		/* ensure 4 byte alignment */
		जबतक ((pos - (u8 *)rthdr) & 3)
			pos++;
		rthdr->it_present |=
			cpu_to_le32(1 << IEEE80211_RADIOTAP_AMPDU_STATUS);
		put_unaligned_le32(status->ampdu_reference, pos);
		pos += 4;
		अगर (status->flag & RX_FLAG_AMPDU_LAST_KNOWN)
			flags |= IEEE80211_RADIOTAP_AMPDU_LAST_KNOWN;
		अगर (status->flag & RX_FLAG_AMPDU_IS_LAST)
			flags |= IEEE80211_RADIOTAP_AMPDU_IS_LAST;
		अगर (status->flag & RX_FLAG_AMPDU_DELIM_CRC_ERROR)
			flags |= IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR;
		अगर (status->flag & RX_FLAG_AMPDU_DELIM_CRC_KNOWN)
			flags |= IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_KNOWN;
		अगर (status->flag & RX_FLAG_AMPDU_खातापूर्ण_BIT_KNOWN)
			flags |= IEEE80211_RADIOTAP_AMPDU_खातापूर्ण_KNOWN;
		अगर (status->flag & RX_FLAG_AMPDU_खातापूर्ण_BIT)
			flags |= IEEE80211_RADIOTAP_AMPDU_खातापूर्ण;
		put_unaligned_le16(flags, pos);
		pos += 2;
		अगर (status->flag & RX_FLAG_AMPDU_DELIM_CRC_KNOWN)
			*pos++ = status->ampdu_delimiter_crc;
		अन्यथा
			*pos++ = 0;
		*pos++ = 0;
	पूर्ण

	अगर (status->encoding == RX_ENC_VHT) अणु
		u16 known = local->hw.radiotap_vht_details;

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_VHT);
		put_unaligned_le16(known, pos);
		pos += 2;
		/* flags */
		अगर (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_SGI;
		/* in VHT, STBC is binary */
		अगर (status->enc_flags & RX_ENC_FLAG_STBC_MASK)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_STBC;
		अगर (status->enc_flags & RX_ENC_FLAG_BF)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_BEAMFORMED;
		pos++;
		/* bandwidth */
		चयन (status->bw) अणु
		हाल RATE_INFO_BW_80:
			*pos++ = 4;
			अवरोध;
		हाल RATE_INFO_BW_160:
			*pos++ = 11;
			अवरोध;
		हाल RATE_INFO_BW_40:
			*pos++ = 1;
			अवरोध;
		शेष:
			*pos++ = 0;
		पूर्ण
		/* MCS/NSS */
		*pos = (status->rate_idx << 4) | status->nss;
		pos += 4;
		/* coding field */
		अगर (status->enc_flags & RX_ENC_FLAG_LDPC)
			*pos |= IEEE80211_RADIOTAP_CODING_LDPC_USER0;
		pos++;
		/* group ID */
		pos++;
		/* partial_aid */
		pos += 2;
	पूर्ण

	अगर (local->hw.radiotap_बारtamp.units_pos >= 0) अणु
		u16 accuracy = 0;
		u8 flags = IEEE80211_RADIOTAP_TIMESTAMP_FLAG_32BIT;

		rthdr->it_present |=
			cpu_to_le32(1 << IEEE80211_RADIOTAP_TIMESTAMP);

		/* ensure 8 byte alignment */
		जबतक ((pos - (u8 *)rthdr) & 7)
			pos++;

		put_unaligned_le64(status->device_बारtamp, pos);
		pos += माप(u64);

		अगर (local->hw.radiotap_बारtamp.accuracy >= 0) अणु
			accuracy = local->hw.radiotap_बारtamp.accuracy;
			flags |= IEEE80211_RADIOTAP_TIMESTAMP_FLAG_ACCURACY;
		पूर्ण
		put_unaligned_le16(accuracy, pos);
		pos += माप(u16);

		*pos++ = local->hw.radiotap_बारtamp.units_pos;
		*pos++ = flags;
	पूर्ण

	अगर (status->encoding == RX_ENC_HE &&
	    status->flag & RX_FLAG_RADIOTAP_HE) अणु
#घोषणा HE_PREP(f, val)	le16_encode_bits(val, IEEE80211_RADIOTAP_HE_##f)

		अगर (status->enc_flags & RX_ENC_FLAG_STBC_MASK) अणु
			he.data6 |= HE_PREP(DATA6_NSTS,
					    FIELD_GET(RX_ENC_FLAG_STBC_MASK,
						      status->enc_flags));
			he.data3 |= HE_PREP(DATA3_STBC, 1);
		पूर्ण अन्यथा अणु
			he.data6 |= HE_PREP(DATA6_NSTS, status->nss);
		पूर्ण

#घोषणा CHECK_GI(s) \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA5_GI_##s != \
		     (पूर्णांक)NL80211_RATE_INFO_HE_GI_##s)

		CHECK_GI(0_8);
		CHECK_GI(1_6);
		CHECK_GI(3_2);

		he.data3 |= HE_PREP(DATA3_DATA_MCS, status->rate_idx);
		he.data3 |= HE_PREP(DATA3_DATA_DCM, status->he_dcm);
		he.data3 |= HE_PREP(DATA3_CODING,
				    !!(status->enc_flags & RX_ENC_FLAG_LDPC));

		he.data5 |= HE_PREP(DATA5_GI, status->he_gi);

		चयन (status->bw) अणु
		हाल RATE_INFO_BW_20:
			he.data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					    IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_20MHZ);
			अवरोध;
		हाल RATE_INFO_BW_40:
			he.data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					    IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_40MHZ);
			अवरोध;
		हाल RATE_INFO_BW_80:
			he.data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					    IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_80MHZ);
			अवरोध;
		हाल RATE_INFO_BW_160:
			he.data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					    IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_160MHZ);
			अवरोध;
		हाल RATE_INFO_BW_HE_RU:
#घोषणा CHECK_RU_ALLOC(s) \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_##s##T != \
		     NL80211_RATE_INFO_HE_RU_ALLOC_##s + 4)

			CHECK_RU_ALLOC(26);
			CHECK_RU_ALLOC(52);
			CHECK_RU_ALLOC(106);
			CHECK_RU_ALLOC(242);
			CHECK_RU_ALLOC(484);
			CHECK_RU_ALLOC(996);
			CHECK_RU_ALLOC(2x996);

			he.data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					    status->he_ru + 4);
			अवरोध;
		शेष:
			WARN_ONCE(1, "Invalid SU BW %d\n", status->bw);
		पूर्ण

		/* ensure 2 byte alignment */
		जबतक ((pos - (u8 *)rthdr) & 1)
			pos++;
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_HE);
		स_नकल(pos, &he, माप(he));
		pos += माप(he);
	पूर्ण

	अगर (status->encoding == RX_ENC_HE &&
	    status->flag & RX_FLAG_RADIOTAP_HE_MU) अणु
		/* ensure 2 byte alignment */
		जबतक ((pos - (u8 *)rthdr) & 1)
			pos++;
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_HE_MU);
		स_नकल(pos, &he_mu, माप(he_mu));
		pos += माप(he_mu);
	पूर्ण

	अगर (status->flag & RX_FLAG_NO_PSDU) अणु
		rthdr->it_present |=
			cpu_to_le32(1 << IEEE80211_RADIOTAP_ZERO_LEN_PSDU);
		*pos++ = status->zero_length_psdu_type;
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_LSIG) अणु
		/* ensure 2 byte alignment */
		जबतक ((pos - (u8 *)rthdr) & 1)
			pos++;
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_LSIG);
		स_नकल(pos, &lsig, माप(lsig));
		pos += माप(lsig);
	पूर्ण

	क्रम_each_set_bit(chain, &chains, IEEE80211_MAX_CHAINS) अणु
		*pos++ = status->chain_संकेत[chain];
		*pos++ = chain;
	पूर्ण

	अगर (status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) अणु
		/* ensure 2 byte alignment क्रम the venकरोr field as required */
		अगर ((pos - (u8 *)rthdr) & 1)
			*pos++ = 0;
		*pos++ = rtap.oui[0];
		*pos++ = rtap.oui[1];
		*pos++ = rtap.oui[2];
		*pos++ = rtap.subns;
		put_unaligned_le16(rtap.len, pos);
		pos += 2;
		/* align the actual payload as requested */
		जबतक ((pos - (u8 *)rthdr) & (rtap.align - 1))
			*pos++ = 0;
		/* data (and possible padding) alपढ़ोy follows */
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *
ieee80211_make_monitor_skb(काष्ठा ieee80211_local *local,
			   काष्ठा sk_buff **origskb,
			   काष्ठा ieee80211_rate *rate,
			   पूर्णांक rtap_space, bool use_origskb)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(*origskb);
	पूर्णांक rt_hdrlen, needed_headroom;
	काष्ठा sk_buff *skb;

	/* room क्रम the radiotap header based on driver features */
	rt_hdrlen = ieee80211_rx_radiotap_hdrlen(local, status, *origskb);
	needed_headroom = rt_hdrlen - rtap_space;

	अगर (use_origskb) अणु
		/* only need to expand headroom अगर necessary */
		skb = *origskb;
		*origskb = शून्य;

		/*
		 * This shouldn't trigger often because most devices have an
		 * RX header they pull beक्रमe we get here, and that should
		 * be big enough क्रम our radiotap inक्रमmation. We should
		 * probably export the length to drivers so that we can have
		 * them allocate enough headroom to start with.
		 */
		अगर (skb_headroom(skb) < needed_headroom &&
		    pskb_expand_head(skb, needed_headroom, 0, GFP_ATOMIC)) अणु
			dev_kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Need to make a copy and possibly हटाओ radiotap header
		 * and FCS from the original.
		 */
		skb = skb_copy_expand(*origskb, needed_headroom, 0, GFP_ATOMIC);

		अगर (!skb)
			वापस शून्य;
	पूर्ण

	/* prepend radiotap inक्रमmation */
	ieee80211_add_rx_radiotap_header(local, skb, rate, rt_hdrlen, true);

	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);

	वापस skb;
पूर्ण

/*
 * This function copies a received frame to all monitor पूर्णांकerfaces and
 * वापसs a cleaned-up SKB that no दीर्घer includes the FCS nor the
 * radiotap header the driver might have added.
 */
अटल काष्ठा sk_buff *
ieee80211_rx_monitor(काष्ठा ieee80211_local *local, काष्ठा sk_buff *origskb,
		     काष्ठा ieee80211_rate *rate)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(origskb);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sk_buff *monskb = शून्य;
	पूर्णांक present_fcs_len = 0;
	अचिन्हित पूर्णांक rtap_space = 0;
	काष्ठा ieee80211_sub_अगर_data *monitor_sdata =
		rcu_dereference(local->monitor_sdata);
	bool only_monitor = false;
	अचिन्हित पूर्णांक min_head_len;

	अगर (status->flag & RX_FLAG_RADIOTAP_HE)
		rtap_space += माप(काष्ठा ieee80211_radiotap_he);

	अगर (status->flag & RX_FLAG_RADIOTAP_HE_MU)
		rtap_space += माप(काष्ठा ieee80211_radiotap_he_mu);

	अगर (status->flag & RX_FLAG_RADIOTAP_LSIG)
		rtap_space += माप(काष्ठा ieee80211_radiotap_lsig);

	अगर (unlikely(status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA)) अणु
		काष्ठा ieee80211_venकरोr_radiotap *rtap =
			(व्योम *)(origskb->data + rtap_space);

		rtap_space += माप(*rtap) + rtap->len + rtap->pad;
	पूर्ण

	min_head_len = rtap_space;

	/*
	 * First, we may need to make a copy of the skb because
	 *  (1) we need to modअगरy it क्रम radiotap (अगर not present), and
	 *  (2) the other RX handlers will modअगरy the skb we got.
	 *
	 * We करोn't need to, of course, if we aren't going to वापस
	 * the SKB because it has a bad FCS/PLCP checksum.
	 */

	अगर (!(status->flag & RX_FLAG_NO_PSDU)) अणु
		अगर (ieee80211_hw_check(&local->hw, RX_INCLUDES_FCS)) अणु
			अगर (unlikely(origskb->len <= FCS_LEN + rtap_space)) अणु
				/* driver bug */
				WARN_ON(1);
				dev_kमुक्त_skb(origskb);
				वापस शून्य;
			पूर्ण
			present_fcs_len = FCS_LEN;
		पूर्ण

		/* also consider the hdr->frame_control */
		min_head_len += 2;
	पूर्ण

	/* ensure that the expected data elements are in skb head */
	अगर (!pskb_may_pull(origskb, min_head_len)) अणु
		dev_kमुक्त_skb(origskb);
		वापस शून्य;
	पूर्ण

	only_monitor = should_drop_frame(origskb, present_fcs_len, rtap_space);

	अगर (!local->monitors || (status->flag & RX_FLAG_SKIP_MONITOR)) अणु
		अगर (only_monitor) अणु
			dev_kमुक्त_skb(origskb);
			वापस शून्य;
		पूर्ण

		वापस ieee80211_clean_skb(origskb, present_fcs_len,
					   rtap_space);
	पूर्ण

	ieee80211_handle_mu_mimo_mon(monitor_sdata, origskb, rtap_space);

	list_क्रम_each_entry_rcu(sdata, &local->mon_list, u.mntr.list) अणु
		bool last_monitor = list_is_last(&sdata->u.mntr.list,
						 &local->mon_list);

		अगर (!monskb)
			monskb = ieee80211_make_monitor_skb(local, &origskb,
							    rate, rtap_space,
							    only_monitor &&
							    last_monitor);

		अगर (monskb) अणु
			काष्ठा sk_buff *skb;

			अगर (last_monitor) अणु
				skb = monskb;
				monskb = शून्य;
			पूर्ण अन्यथा अणु
				skb = skb_clone(monskb, GFP_ATOMIC);
			पूर्ण

			अगर (skb) अणु
				skb->dev = sdata->dev;
				dev_sw_netstats_rx_add(skb->dev, skb->len);
				netअगर_receive_skb(skb);
			पूर्ण
		पूर्ण

		अगर (last_monitor)
			अवरोध;
	पूर्ण

	/* this happens अगर last_monitor was erroneously false */
	dev_kमुक्त_skb(monskb);

	/* ditto */
	अगर (!origskb)
		वापस शून्य;

	वापस ieee80211_clean_skb(origskb, present_fcs_len, rtap_space);
पूर्ण

अटल व्योम ieee80211_parse_qos(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	पूर्णांक tid, seqno_idx, security_idx;

	/* करोes the frame have a qos control field? */
	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		/* frame has qos control */
		tid = *qc & IEEE80211_QOS_CTL_TID_MASK;
		अगर (*qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			status->rx_flags |= IEEE80211_RX_AMSDU;

		seqno_idx = tid;
		security_idx = tid;
	पूर्ण अन्यथा अणु
		/*
		 * IEEE 802.11-2007, 7.1.3.4.1 ("Sequence Number field"):
		 *
		 *	Sequence numbers क्रम management frames, QoS data
		 *	frames with a broadcast/multicast address in the
		 *	Address 1 field, and all non-QoS data frames sent
		 *	by QoS STAs are asचिन्हित using an additional single
		 *	modulo-4096 counter, [...]
		 *
		 * We also use that counter क्रम non-QoS STAs.
		 */
		seqno_idx = IEEE80211_NUM_TIDS;
		security_idx = 0;
		अगर (ieee80211_is_mgmt(hdr->frame_control))
			security_idx = IEEE80211_NUM_TIDS;
		tid = 0;
	पूर्ण

	rx->seqno_idx = seqno_idx;
	rx->security_idx = security_idx;
	/* Set skb->priority to 1d tag अगर highest order bit of TID is not set.
	 * For now, set skb->priority to 0 क्रम other हालs. */
	rx->skb->priority = (tid > 7) ? 0 : tid;
पूर्ण

/**
 * DOC: Packet alignment
 *
 * Drivers always need to pass packets that are aligned to two-byte boundaries
 * to the stack.
 *
 * Additionally, should, अगर possible, align the payload data in a way that
 * guarantees that the contained IP header is aligned to a four-byte
 * boundary. In the हाल of regular frames, this simply means aligning the
 * payload to a four-byte boundary (because either the IP header is directly
 * contained, or IV/RFC1042 headers that have a length भागisible by four are
 * in front of it).  If the payload data is not properly aligned and the
 * architecture करोesn't support efficient unaligned operations, mac80211
 * will align the data.
 *
 * With A-MSDU frames, however, the payload data address must yield two modulo
 * four because there are 14-byte 802.3 headers within the A-MSDU frames that
 * push the IP header further back to a multiple of four again. Thankfully, the
 * specs were sane enough this समय around to require padding each A-MSDU
 * subframe to a length that is a multiple of four.
 *
 * Padding like Atheros hardware adds which is between the 802.11 header and
 * the payload is not supported, the driver is required to move the 802.11
 * header to be directly in front of the payload in that हाल.
 */
अटल व्योम ieee80211_verअगरy_alignment(काष्ठा ieee80211_rx_data *rx)
अणु
#अगर_घोषित CONFIG_MAC80211_VERBOSE_DEBUG
	WARN_ON_ONCE((अचिन्हित दीर्घ)rx->skb->data & 1);
#पूर्ण_अगर
पूर्ण


/* rx handlers */

अटल पूर्णांक ieee80211_is_unicast_robust_mgmt_frame(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस 0;

	वापस ieee80211_is_robust_mgmt_frame(skb);
पूर्ण


अटल पूर्णांक ieee80211_is_multicast_robust_mgmt_frame(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (!is_multicast_ether_addr(hdr->addr1))
		वापस 0;

	वापस ieee80211_is_robust_mgmt_frame(skb);
पूर्ण


/* Get the BIP key index from MMIE; वापस -1 अगर this is not a BIP frame */
अटल पूर्णांक ieee80211_get_mmie_keyidx(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_mgmt *hdr = (काष्ठा ieee80211_mgmt *) skb->data;
	काष्ठा ieee80211_mmie *mmie;
	काष्ठा ieee80211_mmie_16 *mmie16;

	अगर (skb->len < 24 + माप(*mmie) || !is_multicast_ether_addr(hdr->da))
		वापस -1;

	अगर (!ieee80211_is_robust_mgmt_frame(skb) &&
	    !ieee80211_is_beacon(hdr->frame_control))
		वापस -1; /* not a robust management frame */

	mmie = (काष्ठा ieee80211_mmie *)
		(skb->data + skb->len - माप(*mmie));
	अगर (mmie->element_id == WLAN_EID_MMIE &&
	    mmie->length == माप(*mmie) - 2)
		वापस le16_to_cpu(mmie->key_id);

	mmie16 = (काष्ठा ieee80211_mmie_16 *)
		(skb->data + skb->len - माप(*mmie16));
	अगर (skb->len >= 24 + माप(*mmie16) &&
	    mmie16->element_id == WLAN_EID_MMIE &&
	    mmie16->length == माप(*mmie16) - 2)
		वापस le16_to_cpu(mmie16->key_id);

	वापस -1;
पूर्ण

अटल पूर्णांक ieee80211_get_keyid(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा ieee80211_cipher_scheme *cs)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 fc;
	पूर्णांक hdrlen;
	पूर्णांक minlen;
	u8 key_idx_off;
	u8 key_idx_shअगरt;
	u8 keyid;

	fc = hdr->frame_control;
	hdrlen = ieee80211_hdrlen(fc);

	अगर (cs) अणु
		minlen = hdrlen + cs->hdr_len;
		key_idx_off = hdrlen + cs->key_idx_off;
		key_idx_shअगरt = cs->key_idx_shअगरt;
	पूर्ण अन्यथा अणु
		/* WEP, TKIP, CCMP and GCMP */
		minlen = hdrlen + IEEE80211_WEP_IV_LEN;
		key_idx_off = hdrlen + 3;
		key_idx_shअगरt = 6;
	पूर्ण

	अगर (unlikely(skb->len < minlen))
		वापस -EINVAL;

	skb_copy_bits(skb, key_idx_off, &keyid, 1);

	अगर (cs)
		keyid &= cs->key_idx_mask;
	keyid >>= key_idx_shअगरt;

	/* cs could use more than the usual two bits क्रम the keyid */
	अगर (unlikely(keyid >= NUM_DEFAULT_KEYS))
		वापस -EINVAL;

	वापस keyid;
पूर्ण

अटल ieee80211_rx_result ieee80211_rx_mesh_check(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	अक्षर *dev_addr = rx->sdata->vअगर.addr;

	अगर (ieee80211_is_data(hdr->frame_control)) अणु
		अगर (is_multicast_ether_addr(hdr->addr1)) अणु
			अगर (ieee80211_has_tods(hdr->frame_control) ||
			    !ieee80211_has_fromds(hdr->frame_control))
				वापस RX_DROP_MONITOR;
			अगर (ether_addr_equal(hdr->addr3, dev_addr))
				वापस RX_DROP_MONITOR;
		पूर्ण अन्यथा अणु
			अगर (!ieee80211_has_a4(hdr->frame_control))
				वापस RX_DROP_MONITOR;
			अगर (ether_addr_equal(hdr->addr4, dev_addr))
				वापस RX_DROP_MONITOR;
		पूर्ण
	पूर्ण

	/* If there is not an established peer link and this is not a peer link
	 * establisment frame, beacon or probe, drop the frame.
	 */

	अगर (!rx->sta || sta_plink_state(rx->sta) != NL80211_PLINK_ESTAB) अणु
		काष्ठा ieee80211_mgmt *mgmt;

		अगर (!ieee80211_is_mgmt(hdr->frame_control))
			वापस RX_DROP_MONITOR;

		अगर (ieee80211_is_action(hdr->frame_control)) अणु
			u8 category;

			/* make sure category field is present */
			अगर (rx->skb->len < IEEE80211_MIN_ACTION_SIZE)
				वापस RX_DROP_MONITOR;

			mgmt = (काष्ठा ieee80211_mgmt *)hdr;
			category = mgmt->u.action.category;
			अगर (category != WLAN_CATEGORY_MESH_ACTION &&
			    category != WLAN_CATEGORY_SELF_PROTECTED)
				वापस RX_DROP_MONITOR;
			वापस RX_CONTINUE;
		पूर्ण

		अगर (ieee80211_is_probe_req(hdr->frame_control) ||
		    ieee80211_is_probe_resp(hdr->frame_control) ||
		    ieee80211_is_beacon(hdr->frame_control) ||
		    ieee80211_is_auth(hdr->frame_control))
			वापस RX_CONTINUE;

		वापस RX_DROP_MONITOR;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण

अटल अंतरभूत bool ieee80211_rx_reorder_पढ़ोy(काष्ठा tid_ampdu_rx *tid_agg_rx,
					      पूर्णांक index)
अणु
	काष्ठा sk_buff_head *frames = &tid_agg_rx->reorder_buf[index];
	काष्ठा sk_buff *tail = skb_peek_tail(frames);
	काष्ठा ieee80211_rx_status *status;

	अगर (tid_agg_rx->reorder_buf_filtered & BIT_ULL(index))
		वापस true;

	अगर (!tail)
		वापस false;

	status = IEEE80211_SKB_RXCB(tail);
	अगर (status->flag & RX_FLAG_AMSDU_MORE)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ieee80211_release_reorder_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
					    काष्ठा tid_ampdu_rx *tid_agg_rx,
					    पूर्णांक index,
					    काष्ठा sk_buff_head *frames)
अणु
	काष्ठा sk_buff_head *skb_list = &tid_agg_rx->reorder_buf[index];
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_rx_status *status;

	lockdep_निश्चित_held(&tid_agg_rx->reorder_lock);

	अगर (skb_queue_empty(skb_list))
		जाओ no_frame;

	अगर (!ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, index)) अणु
		__skb_queue_purge(skb_list);
		जाओ no_frame;
	पूर्ण

	/* release frames from the reorder ring buffer */
	tid_agg_rx->stored_mpdu_num--;
	जबतक ((skb = __skb_dequeue(skb_list))) अणु
		status = IEEE80211_SKB_RXCB(skb);
		status->rx_flags |= IEEE80211_RX_DEFERRED_RELEASE;
		__skb_queue_tail(frames, skb);
	पूर्ण

no_frame:
	tid_agg_rx->reorder_buf_filtered &= ~BIT_ULL(index);
	tid_agg_rx->head_seq_num = ieee80211_sn_inc(tid_agg_rx->head_seq_num);
पूर्ण

अटल व्योम ieee80211_release_reorder_frames(काष्ठा ieee80211_sub_अगर_data *sdata,
					     काष्ठा tid_ampdu_rx *tid_agg_rx,
					     u16 head_seq_num,
					     काष्ठा sk_buff_head *frames)
अणु
	पूर्णांक index;

	lockdep_निश्चित_held(&tid_agg_rx->reorder_lock);

	जबतक (ieee80211_sn_less(tid_agg_rx->head_seq_num, head_seq_num)) अणु
		index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
		ieee80211_release_reorder_frame(sdata, tid_agg_rx, index,
						frames);
	पूर्ण
पूर्ण

/*
 * Timeout (in jअगरfies) क्रम skb's that are रुकोing in the RX reorder buffer. If
 * the skb was added to the buffer दीर्घer than this समय ago, the earlier
 * frames that have not yet been received are assumed to be lost and the skb
 * can be released क्रम processing. This may also release other skb's from the
 * reorder buffer अगर there are no additional gaps between the frames.
 *
 * Callers must hold tid_agg_rx->reorder_lock.
 */
#घोषणा HT_RX_REORDER_BUF_TIMEOUT (HZ / 10)

अटल व्योम ieee80211_sta_reorder_release(काष्ठा ieee80211_sub_अगर_data *sdata,
					  काष्ठा tid_ampdu_rx *tid_agg_rx,
					  काष्ठा sk_buff_head *frames)
अणु
	पूर्णांक index, i, j;

	lockdep_निश्चित_held(&tid_agg_rx->reorder_lock);

	/* release the buffer until next missing frame */
	index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
	अगर (!ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, index) &&
	    tid_agg_rx->stored_mpdu_num) अणु
		/*
		 * No buffers पढ़ोy to be released, but check whether any
		 * frames in the reorder buffer have समयd out.
		 */
		पूर्णांक skipped = 1;
		क्रम (j = (index + 1) % tid_agg_rx->buf_size; j != index;
		     j = (j + 1) % tid_agg_rx->buf_size) अणु
			अगर (!ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, j)) अणु
				skipped++;
				जारी;
			पूर्ण
			अगर (skipped &&
			    !समय_after(jअगरfies, tid_agg_rx->reorder_समय[j] +
					HT_RX_REORDER_BUF_TIMEOUT))
				जाओ set_release_समयr;

			/* करोn't leave incomplete A-MSDUs around */
			क्रम (i = (index + 1) % tid_agg_rx->buf_size; i != j;
			     i = (i + 1) % tid_agg_rx->buf_size)
				__skb_queue_purge(&tid_agg_rx->reorder_buf[i]);

			ht_dbg_ratelimited(sdata,
					   "release an RX reorder frame due to timeout on earlier frames\n");
			ieee80211_release_reorder_frame(sdata, tid_agg_rx, j,
							frames);

			/*
			 * Increment the head seq# also क्रम the skipped slots.
			 */
			tid_agg_rx->head_seq_num =
				(tid_agg_rx->head_seq_num +
				 skipped) & IEEE80211_SN_MASK;
			skipped = 0;
		पूर्ण
	पूर्ण अन्यथा जबतक (ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, index)) अणु
		ieee80211_release_reorder_frame(sdata, tid_agg_rx, index,
						frames);
		index =	tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;
	पूर्ण

	अगर (tid_agg_rx->stored_mpdu_num) अणु
		j = index = tid_agg_rx->head_seq_num % tid_agg_rx->buf_size;

		क्रम (; j != (index - 1) % tid_agg_rx->buf_size;
		     j = (j + 1) % tid_agg_rx->buf_size) अणु
			अगर (ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, j))
				अवरोध;
		पूर्ण

 set_release_समयr:

		अगर (!tid_agg_rx->हटाओd)
			mod_समयr(&tid_agg_rx->reorder_समयr,
				  tid_agg_rx->reorder_समय[j] + 1 +
				  HT_RX_REORDER_BUF_TIMEOUT);
	पूर्ण अन्यथा अणु
		del_समयr(&tid_agg_rx->reorder_समयr);
	पूर्ण
पूर्ण

/*
 * As this function beदीर्घs to the RX path it must be under
 * rcu_पढ़ो_lock protection. It वापसs false अगर the frame
 * can be processed immediately, true अगर it was consumed.
 */
अटल bool ieee80211_sta_manage_reorder_buf(काष्ठा ieee80211_sub_अगर_data *sdata,
					     काष्ठा tid_ampdu_rx *tid_agg_rx,
					     काष्ठा sk_buff *skb,
					     काष्ठा sk_buff_head *frames)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u16 sc = le16_to_cpu(hdr->seq_ctrl);
	u16 mpdu_seq_num = (sc & IEEE80211_SCTL_SEQ) >> 4;
	u16 head_seq_num, buf_size;
	पूर्णांक index;
	bool ret = true;

	spin_lock(&tid_agg_rx->reorder_lock);

	/*
	 * Offloaded BA sessions have no known starting sequence number so pick
	 * one from first Rxed frame क्रम this tid after BA was started.
	 */
	अगर (unlikely(tid_agg_rx->स्वतः_seq)) अणु
		tid_agg_rx->स्वतः_seq = false;
		tid_agg_rx->ssn = mpdu_seq_num;
		tid_agg_rx->head_seq_num = mpdu_seq_num;
	पूर्ण

	buf_size = tid_agg_rx->buf_size;
	head_seq_num = tid_agg_rx->head_seq_num;

	/*
	 * If the current MPDU's SN is smaller than the SSN, it shouldn't
	 * be reordered.
	 */
	अगर (unlikely(!tid_agg_rx->started)) अणु
		अगर (ieee80211_sn_less(mpdu_seq_num, head_seq_num)) अणु
			ret = false;
			जाओ out;
		पूर्ण
		tid_agg_rx->started = true;
	पूर्ण

	/* frame with out of date sequence number */
	अगर (ieee80211_sn_less(mpdu_seq_num, head_seq_num)) अणु
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	/*
	 * If frame the sequence number exceeds our buffering winकरोw
	 * size release some previous frames to make room क्रम this one.
	 */
	अगर (!ieee80211_sn_less(mpdu_seq_num, head_seq_num + buf_size)) अणु
		head_seq_num = ieee80211_sn_inc(
				ieee80211_sn_sub(mpdu_seq_num, buf_size));
		/* release stored frames up to new head to stack */
		ieee80211_release_reorder_frames(sdata, tid_agg_rx,
						 head_seq_num, frames);
	पूर्ण

	/* Now the new frame is always in the range of the reordering buffer */

	index = mpdu_seq_num % tid_agg_rx->buf_size;

	/* check अगर we alपढ़ोy stored this frame */
	अगर (ieee80211_rx_reorder_पढ़ोy(tid_agg_rx, index)) अणु
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	/*
	 * If the current MPDU is in the right order and nothing अन्यथा
	 * is stored we can process it directly, no need to buffer it.
	 * If it is first but there's something stored, we may be able
	 * to release frames after this one.
	 */
	अगर (mpdu_seq_num == tid_agg_rx->head_seq_num &&
	    tid_agg_rx->stored_mpdu_num == 0) अणु
		अगर (!(status->flag & RX_FLAG_AMSDU_MORE))
			tid_agg_rx->head_seq_num =
				ieee80211_sn_inc(tid_agg_rx->head_seq_num);
		ret = false;
		जाओ out;
	पूर्ण

	/* put the frame in the reordering buffer */
	__skb_queue_tail(&tid_agg_rx->reorder_buf[index], skb);
	अगर (!(status->flag & RX_FLAG_AMSDU_MORE)) अणु
		tid_agg_rx->reorder_समय[index] = jअगरfies;
		tid_agg_rx->stored_mpdu_num++;
		ieee80211_sta_reorder_release(sdata, tid_agg_rx, frames);
	पूर्ण

 out:
	spin_unlock(&tid_agg_rx->reorder_lock);
	वापस ret;
पूर्ण

/*
 * Reorder MPDUs from A-MPDUs, keeping them on a buffer. Returns
 * true अगर the MPDU was buffered, false अगर it should be processed.
 */
अटल व्योम ieee80211_rx_reorder_ampdu(काष्ठा ieee80211_rx_data *rx,
				       काष्ठा sk_buff_head *frames)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा sta_info *sta = rx->sta;
	काष्ठा tid_ampdu_rx *tid_agg_rx;
	u16 sc;
	u8 tid, ack_policy;

	अगर (!ieee80211_is_data_qos(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1))
		जाओ करोnt_reorder;

	/*
	 * filter the QoS data rx stream according to
	 * STA/TID and check अगर this STA/TID is on aggregation
	 */

	अगर (!sta)
		जाओ करोnt_reorder;

	ack_policy = *ieee80211_get_qos_ctl(hdr) &
		     IEEE80211_QOS_CTL_ACK_POLICY_MASK;
	tid = ieee80211_get_tid(hdr);

	tid_agg_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
	अगर (!tid_agg_rx) अणु
		अगर (ack_policy == IEEE80211_QOS_CTL_ACK_POLICY_BLOCKACK &&
		    !test_bit(tid, rx->sta->ampdu_mlme.agg_session_valid) &&
		    !test_and_set_bit(tid, rx->sta->ampdu_mlme.unexpected_agg))
			ieee80211_send_delba(rx->sdata, rx->sta->sta.addr, tid,
					     WLAN_BACK_RECIPIENT,
					     WLAN_REASON_QSTA_REQUIRE_SETUP);
		जाओ करोnt_reorder;
	पूर्ण

	/* qos null data frames are excluded */
	अगर (unlikely(hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_शून्यFUNC)))
		जाओ करोnt_reorder;

	/* not part of a BA session */
	अगर (ack_policy != IEEE80211_QOS_CTL_ACK_POLICY_BLOCKACK &&
	    ack_policy != IEEE80211_QOS_CTL_ACK_POLICY_NORMAL)
		जाओ करोnt_reorder;

	/* new, potentially un-ordered, ampdu frame - process it */

	/* reset session समयr */
	अगर (tid_agg_rx->समयout)
		tid_agg_rx->last_rx = jअगरfies;

	/* अगर this mpdu is fragmented - terminate rx aggregation session */
	sc = le16_to_cpu(hdr->seq_ctrl);
	अगर (sc & IEEE80211_SCTL_FRAG) अणु
		skb_queue_tail(&rx->sdata->skb_queue, skb);
		ieee80211_queue_work(&local->hw, &rx->sdata->work);
		वापस;
	पूर्ण

	/*
	 * No locking needed -- we will only ever process one
	 * RX packet at a समय, and thus own tid_agg_rx. All
	 * other code manipulating it needs to (and करोes) make
	 * sure that we cannot get to it any more beक्रमe करोing
	 * anything with it.
	 */
	अगर (ieee80211_sta_manage_reorder_buf(rx->sdata, tid_agg_rx, skb,
					     frames))
		वापस;

 करोnt_reorder:
	__skb_queue_tail(frames, skb);
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_check_dup(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);

	अगर (status->flag & RX_FLAG_DUP_VALIDATED)
		वापस RX_CONTINUE;

	/*
	 * Drop duplicate 802.11 retransmissions
	 * (IEEE 802.11-2012: 9.3.2.10 "Duplicate detection and recovery")
	 */

	अगर (rx->skb->len < 24)
		वापस RX_CONTINUE;

	अगर (ieee80211_is_ctl(hdr->frame_control) ||
	    ieee80211_is_any_nullfunc(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1))
		वापस RX_CONTINUE;

	अगर (!rx->sta)
		वापस RX_CONTINUE;

	अगर (unlikely(ieee80211_has_retry(hdr->frame_control) &&
		     rx->sta->last_seq_ctrl[rx->seqno_idx] == hdr->seq_ctrl)) अणु
		I802_DEBUG_INC(rx->local->करोt11FrameDuplicateCount);
		rx->sta->rx_stats.num_duplicates++;
		वापस RX_DROP_UNUSABLE;
	पूर्ण अन्यथा अगर (!(status->flag & RX_FLAG_AMSDU_MORE)) अणु
		rx->sta->last_seq_ctrl[rx->seqno_idx] = hdr->seq_ctrl;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_check(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;

	/* Drop disallowed frame classes based on STA auth/assoc state;
	 * IEEE 802.11, Chap 5.5.
	 *
	 * mac80211 filters only based on association state, i.e. it drops
	 * Class 3 frames from not associated stations. hostapd sends
	 * deauth/disassoc frames when needed. In addition, hostapd is
	 * responsible क्रम filtering on both auth and assoc states.
	 */

	अगर (ieee80211_vअगर_is_mesh(&rx->sdata->vअगर))
		वापस ieee80211_rx_mesh_check(rx);

	अगर (unlikely((ieee80211_is_data(hdr->frame_control) ||
		      ieee80211_is_pspoll(hdr->frame_control)) &&
		     rx->sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
		     rx->sdata->vअगर.type != NL80211_IFTYPE_OCB &&
		     (!rx->sta || !test_sta_flag(rx->sta, WLAN_STA_ASSOC)))) अणु
		/*
		 * accept port control frames from the AP even when it's not
		 * yet marked ASSOC to prevent a race where we करोn't set the
		 * assoc bit quickly enough beक्रमe it sends the first frame
		 */
		अगर (rx->sta && rx->sdata->vअगर.type == NL80211_IFTYPE_STATION &&
		    ieee80211_is_data_present(hdr->frame_control)) अणु
			अचिन्हित पूर्णांक hdrlen;
			__be16 ethertype;

			hdrlen = ieee80211_hdrlen(hdr->frame_control);

			अगर (rx->skb->len < hdrlen + 8)
				वापस RX_DROP_MONITOR;

			skb_copy_bits(rx->skb, hdrlen + 6, &ethertype, 2);
			अगर (ethertype == rx->sdata->control_port_protocol)
				वापस RX_CONTINUE;
		पूर्ण

		अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_AP &&
		    cfg80211_rx_spurious_frame(rx->sdata->dev,
					       hdr->addr2,
					       GFP_ATOMIC))
			वापस RX_DROP_UNUSABLE;

		वापस RX_DROP_MONITOR;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण


अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_check_more_data(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb;

	local = rx->local;
	skb = rx->skb;
	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (!local->pspolling)
		वापस RX_CONTINUE;

	अगर (!ieee80211_has_fromds(hdr->frame_control))
		/* this is not from AP */
		वापस RX_CONTINUE;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस RX_CONTINUE;

	अगर (!ieee80211_has_moredata(hdr->frame_control)) अणु
		/* AP has no more frames buffered क्रम us */
		local->pspolling = false;
		वापस RX_CONTINUE;
	पूर्ण

	/* more data bit is set, let's request a new frame from the AP */
	ieee80211_send_pspoll(local, rx->sdata);

	वापस RX_CONTINUE;
पूर्ण

अटल व्योम sta_ps_start(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ps_data *ps;
	पूर्णांक tid;

	अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		ps = &sdata->bss->ps;
	अन्यथा
		वापस;

	atomic_inc(&ps->num_sta_ps);
	set_sta_flag(sta, WLAN_STA_PS_STA);
	अगर (!ieee80211_hw_check(&local->hw, AP_LINK_PS))
		drv_sta_notअगरy(local, sdata, STA_NOTIFY_SLEEP, &sta->sta);
	ps_dbg(sdata, "STA %pM aid %d enters power save mode\n",
	       sta->sta.addr, sta->sta.aid);

	ieee80211_clear_fast_xmit(sta);

	अगर (!sta->sta.txq[0])
		वापस;

	क्रम (tid = 0; tid < IEEE80211_NUM_TIDS; tid++) अणु
		काष्ठा ieee80211_txq *txq = sta->sta.txq[tid];
		काष्ठा txq_info *txqi = to_txq_info(txq);

		spin_lock(&local->active_txq_lock[txq->ac]);
		अगर (!list_empty(&txqi->schedule_order))
			list_del_init(&txqi->schedule_order);
		spin_unlock(&local->active_txq_lock[txq->ac]);

		अगर (txq_has_queue(txq))
			set_bit(tid, &sta->txq_buffered_tids);
		अन्यथा
			clear_bit(tid, &sta->txq_buffered_tids);
	पूर्ण
पूर्ण

अटल व्योम sta_ps_end(काष्ठा sta_info *sta)
अणु
	ps_dbg(sta->sdata, "STA %pM aid %d exits power save mode\n",
	       sta->sta.addr, sta->sta.aid);

	अगर (test_sta_flag(sta, WLAN_STA_PS_DRIVER)) अणु
		/*
		 * Clear the flag only अगर the other one is still set
		 * so that the TX path won't start TX'ing new frames
		 * directly ... In the हाल that the driver flag isn't
		 * set ieee80211_sta_ps_deliver_wakeup() will clear it.
		 */
		clear_sta_flag(sta, WLAN_STA_PS_STA);
		ps_dbg(sta->sdata, "STA %pM aid %d driver-ps-blocked\n",
		       sta->sta.addr, sta->sta.aid);
		वापस;
	पूर्ण

	set_sta_flag(sta, WLAN_STA_PS_DELIVER);
	clear_sta_flag(sta, WLAN_STA_PS_STA);
	ieee80211_sta_ps_deliver_wakeup(sta);
पूर्ण

पूर्णांक ieee80211_sta_ps_transition(काष्ठा ieee80211_sta *pubsta, bool start)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	bool in_ps;

	WARN_ON(!ieee80211_hw_check(&sta->local->hw, AP_LINK_PS));

	/* Don't let the same PS state be set twice */
	in_ps = test_sta_flag(sta, WLAN_STA_PS_STA);
	अगर ((start && in_ps) || (!start && !in_ps))
		वापस -EINVAL;

	अगर (start)
		sta_ps_start(sta);
	अन्यथा
		sta_ps_end(sta);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_ps_transition);

व्योम ieee80211_sta_pspoll(काष्ठा ieee80211_sta *pubsta)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);

	अगर (test_sta_flag(sta, WLAN_STA_SP))
		वापस;

	अगर (!test_sta_flag(sta, WLAN_STA_PS_DRIVER))
		ieee80211_sta_ps_deliver_poll_response(sta);
	अन्यथा
		set_sta_flag(sta, WLAN_STA_PSPOLL);
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_pspoll);

व्योम ieee80211_sta_uapsd_trigger(काष्ठा ieee80211_sta *pubsta, u8 tid)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	पूर्णांक ac = ieee80211_ac_from_tid(tid);

	/*
	 * If this AC is not trigger-enabled करो nothing unless the
	 * driver is calling us after it alपढ़ोy checked.
	 *
	 * NB: This could/should check a separate biपंचांगap of trigger-
	 * enabled queues, but क्रम now we only implement uAPSD w/o
	 * TSPEC changes to the ACs, so they're always the same.
	 */
	अगर (!(sta->sta.uapsd_queues & ieee80211_ac_to_qos_mask[ac]) &&
	    tid != IEEE80211_NUM_TIDS)
		वापस;

	/* अगर we are in a service period, करो nothing */
	अगर (test_sta_flag(sta, WLAN_STA_SP))
		वापस;

	अगर (!test_sta_flag(sta, WLAN_STA_PS_DRIVER))
		ieee80211_sta_ps_deliver_uapsd(sta);
	अन्यथा
		set_sta_flag(sta, WLAN_STA_UAPSD);
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_uapsd_trigger);

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_uapsd_and_pspoll(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);

	अगर (!rx->sta)
		वापस RX_CONTINUE;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP &&
	    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN)
		वापस RX_CONTINUE;

	/*
	 * The device handles station घातersave, so करोn't करो anything about
	 * uAPSD and PS-Poll frames (the latter shouldn't even come up from
	 * it to mac80211 since they're handled.)
	 */
	अगर (ieee80211_hw_check(&sdata->local->hw, AP_LINK_PS))
		वापस RX_CONTINUE;

	/*
	 * Don't do anything if the station isn't alपढ़ोy asleep. In
	 * the uAPSD हाल, the station will probably be marked asleep,
	 * in the PS-Poll हाल the station must be confused ...
	 */
	अगर (!test_sta_flag(rx->sta, WLAN_STA_PS_STA))
		वापस RX_CONTINUE;

	अगर (unlikely(ieee80211_is_pspoll(hdr->frame_control))) अणु
		ieee80211_sta_pspoll(&rx->sta->sta);

		/* Free PS Poll skb here instead of वापसing RX_DROP that would
		 * count as an dropped frame. */
		dev_kमुक्त_skb(rx->skb);

		वापस RX_QUEUED;
	पूर्ण अन्यथा अगर (!ieee80211_has_morefrags(hdr->frame_control) &&
		   !(status->rx_flags & IEEE80211_RX_DEFERRED_RELEASE) &&
		   ieee80211_has_pm(hdr->frame_control) &&
		   (ieee80211_is_data_qos(hdr->frame_control) ||
		    ieee80211_is_qos_nullfunc(hdr->frame_control))) अणु
		u8 tid = ieee80211_get_tid(hdr);

		ieee80211_sta_uapsd_trigger(&rx->sta->sta, tid);
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_sta_process(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sta_info *sta = rx->sta;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक i;

	अगर (!sta)
		वापस RX_CONTINUE;

	/*
	 * Update last_rx only क्रम IBSS packets which are क्रम the current
	 * BSSID and क्रम station alपढ़ोy AUTHORIZED to aव्योम keeping the
	 * current IBSS network alive in हालs where other STAs start
	 * using dअगरferent BSSID. This will also give the station another
	 * chance to restart the authentication/authorization in हाल
	 * something went wrong the first समय.
	 */
	अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_ADHOC) अणु
		u8 *bssid = ieee80211_get_bssid(hdr, rx->skb->len,
						NL80211_IFTYPE_ADHOC);
		अगर (ether_addr_equal(bssid, rx->sdata->u.ibss.bssid) &&
		    test_sta_flag(sta, WLAN_STA_AUTHORIZED)) अणु
			sta->rx_stats.last_rx = jअगरfies;
			अगर (ieee80211_is_data(hdr->frame_control) &&
			    !is_multicast_ether_addr(hdr->addr1))
				sta->rx_stats.last_rate =
					sta_stats_encode_rate(status);
		पूर्ण
	पूर्ण अन्यथा अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_OCB) अणु
		sta->rx_stats.last_rx = jअगरfies;
	पूर्ण अन्यथा अगर (!ieee80211_is_s1g_beacon(hdr->frame_control) &&
		   !is_multicast_ether_addr(hdr->addr1)) अणु
		/*
		 * Mesh beacons will update last_rx when अगर they are found to
		 * match the current local configuration when processed.
		 */
		sta->rx_stats.last_rx = jअगरfies;
		अगर (ieee80211_is_data(hdr->frame_control))
			sta->rx_stats.last_rate = sta_stats_encode_rate(status);
	पूर्ण

	sta->rx_stats.fragments++;

	u64_stats_update_begin(&rx->sta->rx_stats.syncp);
	sta->rx_stats.bytes += rx->skb->len;
	u64_stats_update_end(&rx->sta->rx_stats.syncp);

	अगर (!(status->flag & RX_FLAG_NO_SIGNAL_VAL)) अणु
		sta->rx_stats.last_संकेत = status->संकेत;
		ewma_संकेत_add(&sta->rx_stats_avg.संकेत, -status->संकेत);
	पूर्ण

	अगर (status->chains) अणु
		sta->rx_stats.chains = status->chains;
		क्रम (i = 0; i < ARRAY_SIZE(status->chain_संकेत); i++) अणु
			पूर्णांक संकेत = status->chain_संकेत[i];

			अगर (!(status->chains & BIT(i)))
				जारी;

			sta->rx_stats.chain_संकेत_last[i] = संकेत;
			ewma_संकेत_add(&sta->rx_stats_avg.chain_संकेत[i],
					-संकेत);
		पूर्ण
	पूर्ण

	अगर (ieee80211_is_s1g_beacon(hdr->frame_control))
		वापस RX_CONTINUE;

	/*
	 * Change STA घातer saving mode only at the end of a frame
	 * exchange sequence, and only क्रम a data or management
	 * frame as specअगरied in IEEE 802.11-2016 11.2.3.2
	 */
	अगर (!ieee80211_hw_check(&sta->local->hw, AP_LINK_PS) &&
	    !ieee80211_has_morefrags(hdr->frame_control) &&
	    !is_multicast_ether_addr(hdr->addr1) &&
	    (ieee80211_is_mgmt(hdr->frame_control) ||
	     ieee80211_is_data(hdr->frame_control)) &&
	    !(status->rx_flags & IEEE80211_RX_DEFERRED_RELEASE) &&
	    (rx->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	     rx->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)) अणु
		अगर (test_sta_flag(sta, WLAN_STA_PS_STA)) अणु
			अगर (!ieee80211_has_pm(hdr->frame_control))
				sta_ps_end(sta);
		पूर्ण अन्यथा अणु
			अगर (ieee80211_has_pm(hdr->frame_control))
				sta_ps_start(sta);
		पूर्ण
	पूर्ण

	/* mesh घातer save support */
	अगर (ieee80211_vअगर_is_mesh(&rx->sdata->vअगर))
		ieee80211_mps_rx_h_sta_process(sta, hdr);

	/*
	 * Drop (qos-)data::nullfunc frames silently, since they
	 * are used only to control station घातer saving mode.
	 */
	अगर (ieee80211_is_any_nullfunc(hdr->frame_control)) अणु
		I802_DEBUG_INC(rx->local->rx_handlers_drop_nullfunc);

		/*
		 * If we receive a 4-addr nullfunc frame from a STA
		 * that was not moved to a 4-addr STA vlan yet send
		 * the event to userspace and क्रम older hostapd drop
		 * the frame to the monitor पूर्णांकerface.
		 */
		अगर (ieee80211_has_a4(hdr->frame_control) &&
		    (rx->sdata->vअगर.type == NL80211_IFTYPE_AP ||
		     (rx->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN &&
		      !rx->sdata->u.vlan.sta))) अणु
			अगर (!test_and_set_sta_flag(sta, WLAN_STA_4ADDR_EVENT))
				cfg80211_rx_unexpected_4addr_frame(
					rx->sdata->dev, sta->sta.addr,
					GFP_ATOMIC);
			वापस RX_DROP_MONITOR;
		पूर्ण
		/*
		 * Update counter and मुक्त packet here to aव्योम
		 * counting this as a dropped packed.
		 */
		sta->rx_stats.packets++;
		dev_kमुक्त_skb(rx->skb);
		वापस RX_QUEUED;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण /* ieee80211_rx_h_sta_process */

अटल काष्ठा ieee80211_key *
ieee80211_rx_get_bigtk(काष्ठा ieee80211_rx_data *rx, पूर्णांक idx)
अणु
	काष्ठा ieee80211_key *key = शून्य;
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	पूर्णांक idx2;

	/* Make sure key माला_लो set अगर either BIGTK key index is set so that
	 * ieee80211_drop_unencrypted_mgmt() can properly drop both unरक्षित
	 * Beacon frames and Beacon frames that claim to use another BIGTK key
	 * index (i.e., a key that we करो not have).
	 */

	अगर (idx < 0) अणु
		idx = NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS;
		idx2 = idx + 1;
	पूर्ण अन्यथा अणु
		अगर (idx == NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS)
			idx2 = idx + 1;
		अन्यथा
			idx2 = idx - 1;
	पूर्ण

	अगर (rx->sta)
		key = rcu_dereference(rx->sta->gtk[idx]);
	अगर (!key)
		key = rcu_dereference(sdata->keys[idx]);
	अगर (!key && rx->sta)
		key = rcu_dereference(rx->sta->gtk[idx2]);
	अगर (!key)
		key = rcu_dereference(sdata->keys[idx2]);

	वापस key;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक keyidx;
	ieee80211_rx_result result = RX_DROP_UNUSABLE;
	काष्ठा ieee80211_key *sta_ptk = शून्य;
	काष्ठा ieee80211_key *ptk_idx = शून्य;
	पूर्णांक mmie_keyidx = -1;
	__le16 fc;
	स्थिर काष्ठा ieee80211_cipher_scheme *cs = शून्य;

	अगर (ieee80211_is_ext(hdr->frame_control))
		वापस RX_CONTINUE;

	/*
	 * Key selection 101
	 *
	 * There are five types of keys:
	 *  - GTK (group keys)
	 *  - IGTK (group keys क्रम management frames)
	 *  - BIGTK (group keys क्रम Beacon frames)
	 *  - PTK (pairwise keys)
	 *  - STK (station-to-station pairwise keys)
	 *
	 * When selecting a key, we have to distinguish between multicast
	 * (including broadcast) and unicast frames, the latter can only
	 * use PTKs and STKs जबतक the क्रमmer always use GTKs, IGTKs, and
	 * BIGTKs. Unless, of course, actual WEP keys ("pre-RSNA") are used,
	 * then unicast frames can also use key indices like GTKs. Hence, अगर we
	 * करोn't have a PTK/STK we check the key index क्रम a WEP key.
	 *
	 * Note that in a regular BSS, multicast frames are sent by the
	 * AP only, associated stations unicast the frame to the AP first
	 * which then multicasts it on their behalf.
	 *
	 * There is also a slight problem in IBSS mode: GTKs are negotiated
	 * with each station, that is something we करोn't currently handle.
	 * The spec seems to expect that one negotiates the same key with
	 * every station but there's no such requirement; VLANs could be
	 * possible.
	 */

	/* start without a key */
	rx->key = शून्य;
	fc = hdr->frame_control;

	अगर (rx->sta) अणु
		पूर्णांक keyid = rx->sta->ptk_idx;
		sta_ptk = rcu_dereference(rx->sta->ptk[keyid]);

		अगर (ieee80211_has_रक्षित(fc)) अणु
			cs = rx->sta->cipher_scheme;
			keyid = ieee80211_get_keyid(rx->skb, cs);

			अगर (unlikely(keyid < 0))
				वापस RX_DROP_UNUSABLE;

			ptk_idx = rcu_dereference(rx->sta->ptk[keyid]);
		पूर्ण
	पूर्ण

	अगर (!ieee80211_has_रक्षित(fc))
		mmie_keyidx = ieee80211_get_mmie_keyidx(rx->skb);

	अगर (!is_multicast_ether_addr(hdr->addr1) && sta_ptk) अणु
		rx->key = ptk_idx ? ptk_idx : sta_ptk;
		अगर ((status->flag & RX_FLAG_DECRYPTED) &&
		    (status->flag & RX_FLAG_IV_STRIPPED))
			वापस RX_CONTINUE;
		/* Skip decryption अगर the frame is not रक्षित. */
		अगर (!ieee80211_has_रक्षित(fc))
			वापस RX_CONTINUE;
	पूर्ण अन्यथा अगर (mmie_keyidx >= 0 && ieee80211_is_beacon(fc)) अणु
		/* Broadcast/multicast robust management frame / BIP */
		अगर ((status->flag & RX_FLAG_DECRYPTED) &&
		    (status->flag & RX_FLAG_IV_STRIPPED))
			वापस RX_CONTINUE;

		अगर (mmie_keyidx < NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS ||
		    mmie_keyidx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS +
		    NUM_DEFAULT_BEACON_KEYS) अणु
			cfg80211_rx_unprot_mlme_mgmt(rx->sdata->dev,
						     skb->data,
						     skb->len);
			वापस RX_DROP_MONITOR; /* unexpected BIP keyidx */
		पूर्ण

		rx->key = ieee80211_rx_get_bigtk(rx, mmie_keyidx);
		अगर (!rx->key)
			वापस RX_CONTINUE; /* Beacon protection not in use */
	पूर्ण अन्यथा अगर (mmie_keyidx >= 0) अणु
		/* Broadcast/multicast robust management frame / BIP */
		अगर ((status->flag & RX_FLAG_DECRYPTED) &&
		    (status->flag & RX_FLAG_IV_STRIPPED))
			वापस RX_CONTINUE;

		अगर (mmie_keyidx < NUM_DEFAULT_KEYS ||
		    mmie_keyidx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS)
			वापस RX_DROP_MONITOR; /* unexpected BIP keyidx */
		अगर (rx->sta) अणु
			अगर (ieee80211_is_group_privacy_action(skb) &&
			    test_sta_flag(rx->sta, WLAN_STA_MFP))
				वापस RX_DROP_MONITOR;

			rx->key = rcu_dereference(rx->sta->gtk[mmie_keyidx]);
		पूर्ण
		अगर (!rx->key)
			rx->key = rcu_dereference(rx->sdata->keys[mmie_keyidx]);
	पूर्ण अन्यथा अगर (!ieee80211_has_रक्षित(fc)) अणु
		/*
		 * The frame was not रक्षित, so skip decryption. However, we
		 * need to set rx->key अगर there is a key that could have been
		 * used so that the frame may be dropped अगर encryption would
		 * have been expected.
		 */
		काष्ठा ieee80211_key *key = शून्य;
		काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
		पूर्णांक i;

		अगर (ieee80211_is_beacon(fc)) अणु
			key = ieee80211_rx_get_bigtk(rx, -1);
		पूर्ण अन्यथा अगर (ieee80211_is_mgmt(fc) &&
			   is_multicast_ether_addr(hdr->addr1)) अणु
			key = rcu_dereference(rx->sdata->शेष_mgmt_key);
		पूर्ण अन्यथा अणु
			अगर (rx->sta) अणु
				क्रम (i = 0; i < NUM_DEFAULT_KEYS; i++) अणु
					key = rcu_dereference(rx->sta->gtk[i]);
					अगर (key)
						अवरोध;
				पूर्ण
			पूर्ण
			अगर (!key) अणु
				क्रम (i = 0; i < NUM_DEFAULT_KEYS; i++) अणु
					key = rcu_dereference(sdata->keys[i]);
					अगर (key)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (key)
			rx->key = key;
		वापस RX_CONTINUE;
	पूर्ण अन्यथा अणु
		/*
		 * The device करोesn't give us the IV so we won't be
		 * able to look up the key. That's ok though, we
		 * करोn't need to decrypt the frame, we just won't
		 * be able to keep statistics accurate.
		 * Except क्रम key threshold notअगरications, should
		 * we somehow allow the driver to tell us which key
		 * the hardware used अगर this flag is set?
		 */
		अगर ((status->flag & RX_FLAG_DECRYPTED) &&
		    (status->flag & RX_FLAG_IV_STRIPPED))
			वापस RX_CONTINUE;

		keyidx = ieee80211_get_keyid(rx->skb, cs);

		अगर (unlikely(keyidx < 0))
			वापस RX_DROP_UNUSABLE;

		/* check per-station GTK first, अगर multicast packet */
		अगर (is_multicast_ether_addr(hdr->addr1) && rx->sta)
			rx->key = rcu_dereference(rx->sta->gtk[keyidx]);

		/* अगर not found, try शेष key */
		अगर (!rx->key) अणु
			rx->key = rcu_dereference(rx->sdata->keys[keyidx]);

			/*
			 * RSNA-रक्षित unicast frames should always be
			 * sent with pairwise or station-to-station keys,
			 * but क्रम WEP we allow using a key index as well.
			 */
			अगर (rx->key &&
			    rx->key->conf.cipher != WLAN_CIPHER_SUITE_WEP40 &&
			    rx->key->conf.cipher != WLAN_CIPHER_SUITE_WEP104 &&
			    !is_multicast_ether_addr(hdr->addr1))
				rx->key = शून्य;
		पूर्ण
	पूर्ण

	अगर (rx->key) अणु
		अगर (unlikely(rx->key->flags & KEY_FLAG_TAINTED))
			वापस RX_DROP_MONITOR;

		/* TODO: add threshold stuff again */
	पूर्ण अन्यथा अणु
		वापस RX_DROP_MONITOR;
	पूर्ण

	चयन (rx->key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		result = ieee80211_crypto_wep_decrypt(rx);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		result = ieee80211_crypto_tkip_decrypt(rx);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		result = ieee80211_crypto_ccmp_decrypt(
			rx, IEEE80211_CCMP_MIC_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		result = ieee80211_crypto_ccmp_decrypt(
			rx, IEEE80211_CCMP_256_MIC_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		result = ieee80211_crypto_aes_cmac_decrypt(rx);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		result = ieee80211_crypto_aes_cmac_256_decrypt(rx);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		result = ieee80211_crypto_aes_gmac_decrypt(rx);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		result = ieee80211_crypto_gcmp_decrypt(rx);
		अवरोध;
	शेष:
		result = ieee80211_crypto_hw_decrypt(rx);
	पूर्ण

	/* the hdr variable is invalid after the decrypt handlers */

	/* either the frame has been decrypted or will be dropped */
	status->flag |= RX_FLAG_DECRYPTED;

	अगर (unlikely(ieee80211_is_beacon(fc) && result == RX_DROP_UNUSABLE))
		cfg80211_rx_unprot_mlme_mgmt(rx->sdata->dev,
					     skb->data, skb->len);

	वापस result;
पूर्ण

व्योम ieee80211_init_frag_cache(काष्ठा ieee80211_fragment_cache *cache)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cache->entries); i++)
		skb_queue_head_init(&cache->entries[i].skb_list);
पूर्ण

व्योम ieee80211_destroy_frag_cache(काष्ठा ieee80211_fragment_cache *cache)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cache->entries); i++)
		__skb_queue_purge(&cache->entries[i].skb_list);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_fragment_entry *
ieee80211_reassemble_add(काष्ठा ieee80211_fragment_cache *cache,
			 अचिन्हित पूर्णांक frag, अचिन्हित पूर्णांक seq, पूर्णांक rx_queue,
			 काष्ठा sk_buff **skb)
अणु
	काष्ठा ieee80211_fragment_entry *entry;

	entry = &cache->entries[cache->next++];
	अगर (cache->next >= IEEE80211_FRAGMENT_MAX)
		cache->next = 0;

	__skb_queue_purge(&entry->skb_list);

	__skb_queue_tail(&entry->skb_list, *skb); /* no need क्रम locking */
	*skb = शून्य;
	entry->first_frag_समय = jअगरfies;
	entry->seq = seq;
	entry->rx_queue = rx_queue;
	entry->last_frag = frag;
	entry->check_sequential_pn = false;
	entry->extra_len = 0;

	वापस entry;
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_fragment_entry *
ieee80211_reassemble_find(काष्ठा ieee80211_fragment_cache *cache,
			  अचिन्हित पूर्णांक frag, अचिन्हित पूर्णांक seq,
			  पूर्णांक rx_queue, काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा ieee80211_fragment_entry *entry;
	पूर्णांक i, idx;

	idx = cache->next;
	क्रम (i = 0; i < IEEE80211_FRAGMENT_MAX; i++) अणु
		काष्ठा ieee80211_hdr *f_hdr;
		काष्ठा sk_buff *f_skb;

		idx--;
		अगर (idx < 0)
			idx = IEEE80211_FRAGMENT_MAX - 1;

		entry = &cache->entries[idx];
		अगर (skb_queue_empty(&entry->skb_list) || entry->seq != seq ||
		    entry->rx_queue != rx_queue ||
		    entry->last_frag + 1 != frag)
			जारी;

		f_skb = __skb_peek(&entry->skb_list);
		f_hdr = (काष्ठा ieee80211_hdr *) f_skb->data;

		/*
		 * Check ftype and addresses are equal, अन्यथा check next fragment
		 */
		अगर (((hdr->frame_control ^ f_hdr->frame_control) &
		     cpu_to_le16(IEEE80211_FCTL_FTYPE)) ||
		    !ether_addr_equal(hdr->addr1, f_hdr->addr1) ||
		    !ether_addr_equal(hdr->addr2, f_hdr->addr2))
			जारी;

		अगर (समय_after(jअगरfies, entry->first_frag_समय + 2 * HZ)) अणु
			__skb_queue_purge(&entry->skb_list);
			जारी;
		पूर्ण
		वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool requires_sequential_pn(काष्ठा ieee80211_rx_data *rx, __le16 fc)
अणु
	वापस rx->key &&
		(rx->key->conf.cipher == WLAN_CIPHER_SUITE_CCMP ||
		 rx->key->conf.cipher == WLAN_CIPHER_SUITE_CCMP_256 ||
		 rx->key->conf.cipher == WLAN_CIPHER_SUITE_GCMP ||
		 rx->key->conf.cipher == WLAN_CIPHER_SUITE_GCMP_256) &&
		ieee80211_has_रक्षित(fc);
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_defragment(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_fragment_cache *cache = &rx->sdata->frags;
	काष्ठा ieee80211_hdr *hdr;
	u16 sc;
	__le16 fc;
	अचिन्हित पूर्णांक frag, seq;
	काष्ठा ieee80211_fragment_entry *entry;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);

	hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	fc = hdr->frame_control;

	अगर (ieee80211_is_ctl(fc) || ieee80211_is_ext(fc))
		वापस RX_CONTINUE;

	sc = le16_to_cpu(hdr->seq_ctrl);
	frag = sc & IEEE80211_SCTL_FRAG;

	अगर (rx->sta)
		cache = &rx->sta->frags;

	अगर (likely(!ieee80211_has_morefrags(fc) && frag == 0))
		जाओ out;

	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस RX_DROP_MONITOR;

	I802_DEBUG_INC(rx->local->rx_handlers_fragments);

	अगर (skb_linearize(rx->skb))
		वापस RX_DROP_UNUSABLE;

	/*
	 *  skb_linearize() might change the skb->data and
	 *  previously cached variables (in this हाल, hdr) need to
	 *  be refreshed with the new data.
	 */
	hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;

	अगर (frag == 0) अणु
		/* This is the first fragment of a new frame. */
		entry = ieee80211_reassemble_add(cache, frag, seq,
						 rx->seqno_idx, &(rx->skb));
		अगर (requires_sequential_pn(rx, fc)) अणु
			पूर्णांक queue = rx->security_idx;

			/* Store CCMP/GCMP PN so that we can verअगरy that the
			 * next fragment has a sequential PN value.
			 */
			entry->check_sequential_pn = true;
			entry->is_रक्षित = true;
			entry->key_color = rx->key->color;
			स_नकल(entry->last_pn,
			       rx->key->u.ccmp.rx_pn[queue],
			       IEEE80211_CCMP_PN_LEN);
			BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_key,
					      u.ccmp.rx_pn) !=
				     दुरत्व(काष्ठा ieee80211_key,
					      u.gcmp.rx_pn));
			BUILD_BUG_ON(माप(rx->key->u.ccmp.rx_pn[queue]) !=
				     माप(rx->key->u.gcmp.rx_pn[queue]));
			BUILD_BUG_ON(IEEE80211_CCMP_PN_LEN !=
				     IEEE80211_GCMP_PN_LEN);
		पूर्ण अन्यथा अगर (rx->key &&
			   (ieee80211_has_रक्षित(fc) ||
			    (status->flag & RX_FLAG_DECRYPTED))) अणु
			entry->is_रक्षित = true;
			entry->key_color = rx->key->color;
		पूर्ण
		वापस RX_QUEUED;
	पूर्ण

	/* This is a fragment क्रम a frame that should alपढ़ोy be pending in
	 * fragment cache. Add this fragment to the end of the pending entry.
	 */
	entry = ieee80211_reassemble_find(cache, frag, seq,
					  rx->seqno_idx, hdr);
	अगर (!entry) अणु
		I802_DEBUG_INC(rx->local->rx_handlers_drop_defrag);
		वापस RX_DROP_MONITOR;
	पूर्ण

	/* "The receiver shall discard MSDUs and MMPDUs whose स्थिरituent
	 *  MPDU PN values are not incrementing in steps of 1."
	 * see IEEE P802.11-REVmc/D5.0, 12.5.3.4.4, item d (क्रम CCMP)
	 * and IEEE P802.11-REVmc/D5.0, 12.5.5.4.4, item d (क्रम GCMP)
	 */
	अगर (entry->check_sequential_pn) अणु
		पूर्णांक i;
		u8 pn[IEEE80211_CCMP_PN_LEN], *rpn;

		अगर (!requires_sequential_pn(rx, fc))
			वापस RX_DROP_UNUSABLE;

		/* Prevent mixed key and fragment cache attacks */
		अगर (entry->key_color != rx->key->color)
			वापस RX_DROP_UNUSABLE;

		स_नकल(pn, entry->last_pn, IEEE80211_CCMP_PN_LEN);
		क्रम (i = IEEE80211_CCMP_PN_LEN - 1; i >= 0; i--) अणु
			pn[i]++;
			अगर (pn[i])
				अवरोध;
		पूर्ण

		rpn = rx->ccm_gcm.pn;
		अगर (स_भेद(pn, rpn, IEEE80211_CCMP_PN_LEN))
			वापस RX_DROP_UNUSABLE;
		स_नकल(entry->last_pn, pn, IEEE80211_CCMP_PN_LEN);
	पूर्ण अन्यथा अगर (entry->is_रक्षित &&
		   (!rx->key ||
		    (!ieee80211_has_रक्षित(fc) &&
		     !(status->flag & RX_FLAG_DECRYPTED)) ||
		    rx->key->color != entry->key_color)) अणु
		/* Drop this as a mixed key or fragment cache attack, even
		 * अगर क्रम TKIP Michael MIC should protect us, and WEP is a
		 * lost cause anyway.
		 */
		वापस RX_DROP_UNUSABLE;
	पूर्ण अन्यथा अगर (entry->is_रक्षित && rx->key &&
		   entry->key_color != rx->key->color &&
		   (status->flag & RX_FLAG_DECRYPTED)) अणु
		वापस RX_DROP_UNUSABLE;
	पूर्ण

	skb_pull(rx->skb, ieee80211_hdrlen(fc));
	__skb_queue_tail(&entry->skb_list, rx->skb);
	entry->last_frag = frag;
	entry->extra_len += rx->skb->len;
	अगर (ieee80211_has_morefrags(fc)) अणु
		rx->skb = शून्य;
		वापस RX_QUEUED;
	पूर्ण

	rx->skb = __skb_dequeue(&entry->skb_list);
	अगर (skb_tailroom(rx->skb) < entry->extra_len) अणु
		I802_DEBUG_INC(rx->local->rx_expand_skb_head_defrag);
		अगर (unlikely(pskb_expand_head(rx->skb, 0, entry->extra_len,
					      GFP_ATOMIC))) अणु
			I802_DEBUG_INC(rx->local->rx_handlers_drop_defrag);
			__skb_queue_purge(&entry->skb_list);
			वापस RX_DROP_UNUSABLE;
		पूर्ण
	पूर्ण
	जबतक ((skb = __skb_dequeue(&entry->skb_list))) अणु
		skb_put_data(rx->skb, skb->data, skb->len);
		dev_kमुक्त_skb(skb);
	पूर्ण

 out:
	ieee80211_led_rx(rx->local);
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;
	वापस RX_CONTINUE;
पूर्ण

अटल पूर्णांक ieee80211_802_1x_port_control(काष्ठा ieee80211_rx_data *rx)
अणु
	अगर (unlikely(!rx->sta || !test_sta_flag(rx->sta, WLAN_STA_AUTHORIZED)))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_drop_unencrypted(काष्ठा ieee80211_rx_data *rx, __le16 fc)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)rx->skb->data;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);

	/*
	 * Pass through unencrypted frames अगर the hardware has
	 * decrypted them alपढ़ोy.
	 */
	अगर (status->flag & RX_FLAG_DECRYPTED)
		वापस 0;

	/* check mesh EAPOL frames first */
	अगर (unlikely(rx->sta && ieee80211_vअगर_is_mesh(&rx->sdata->vअगर) &&
		     ieee80211_is_data(fc))) अणु
		काष्ठा ieee80211s_hdr *mesh_hdr;
		u16 hdr_len = ieee80211_hdrlen(fc);
		u16 ethertype_offset;
		__be16 ethertype;

		अगर (!ether_addr_equal(hdr->addr1, rx->sdata->vअगर.addr))
			जाओ drop_check;

		/* make sure fixed part of mesh header is there, also checks skb len */
		अगर (!pskb_may_pull(rx->skb, hdr_len + 6))
			जाओ drop_check;

		mesh_hdr = (काष्ठा ieee80211s_hdr *)(skb->data + hdr_len);
		ethertype_offset = hdr_len + ieee80211_get_mesh_hdrlen(mesh_hdr) +
				   माप(rfc1042_header);

		अगर (skb_copy_bits(rx->skb, ethertype_offset, &ethertype, 2) == 0 &&
		    ethertype == rx->sdata->control_port_protocol)
			वापस 0;
	पूर्ण

drop_check:
	/* Drop unencrypted frames अगर key is set. */
	अगर (unlikely(!ieee80211_has_रक्षित(fc) &&
		     !ieee80211_is_any_nullfunc(fc) &&
		     ieee80211_is_data(fc) && rx->key))
		वापस -EACCES;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_drop_unencrypted_mgmt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	__le16 fc = hdr->frame_control;

	/*
	 * Pass through unencrypted frames अगर the hardware has
	 * decrypted them alपढ़ोy.
	 */
	अगर (status->flag & RX_FLAG_DECRYPTED)
		वापस 0;

	अगर (rx->sta && test_sta_flag(rx->sta, WLAN_STA_MFP)) अणु
		अगर (unlikely(!ieee80211_has_रक्षित(fc) &&
			     ieee80211_is_unicast_robust_mgmt_frame(rx->skb) &&
			     rx->key)) अणु
			अगर (ieee80211_is_deauth(fc) ||
			    ieee80211_is_disassoc(fc))
				cfg80211_rx_unprot_mlme_mgmt(rx->sdata->dev,
							     rx->skb->data,
							     rx->skb->len);
			वापस -EACCES;
		पूर्ण
		/* BIP करोes not use Protected field, so need to check MMIE */
		अगर (unlikely(ieee80211_is_multicast_robust_mgmt_frame(rx->skb) &&
			     ieee80211_get_mmie_keyidx(rx->skb) < 0)) अणु
			अगर (ieee80211_is_deauth(fc) ||
			    ieee80211_is_disassoc(fc))
				cfg80211_rx_unprot_mlme_mgmt(rx->sdata->dev,
							     rx->skb->data,
							     rx->skb->len);
			वापस -EACCES;
		पूर्ण
		अगर (unlikely(ieee80211_is_beacon(fc) && rx->key &&
			     ieee80211_get_mmie_keyidx(rx->skb) < 0)) अणु
			cfg80211_rx_unprot_mlme_mgmt(rx->sdata->dev,
						     rx->skb->data,
						     rx->skb->len);
			वापस -EACCES;
		पूर्ण
		/*
		 * When using MFP, Action frames are not allowed prior to
		 * having configured keys.
		 */
		अगर (unlikely(ieee80211_is_action(fc) && !rx->key &&
			     ieee80211_is_robust_mgmt_frame(rx->skb)))
			वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__ieee80211_data_to_8023(काष्ठा ieee80211_rx_data *rx, bool *port_control)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	bool check_port_control = false;
	काष्ठा ethhdr *ehdr;
	पूर्णांक ret;

	*port_control = false;
	अगर (ieee80211_has_a4(hdr->frame_control) &&
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN && !sdata->u.vlan.sta)
		वापस -1;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !!sdata->u.mgd.use_4addr != !!ieee80211_has_a4(hdr->frame_control)) अणु

		अगर (!sdata->u.mgd.use_4addr)
			वापस -1;
		अन्यथा अगर (!ether_addr_equal(hdr->addr1, sdata->vअगर.addr))
			check_port_control = true;
	पूर्ण

	अगर (is_multicast_ether_addr(hdr->addr1) &&
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN && sdata->u.vlan.sta)
		वापस -1;

	ret = ieee80211_data_to_8023(rx->skb, sdata->vअगर.addr, sdata->vअगर.type);
	अगर (ret < 0)
		वापस ret;

	ehdr = (काष्ठा ethhdr *) rx->skb->data;
	अगर (ehdr->h_proto == rx->sdata->control_port_protocol)
		*port_control = true;
	अन्यथा अगर (check_port_control)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * requires that rx->skb is a frame with ethernet header
 */
अटल bool ieee80211_frame_allowed(काष्ठा ieee80211_rx_data *rx, __le16 fc)
अणु
	अटल स्थिर u8 pae_group_addr[ETH_ALEN] __aligned(2)
		= अणु 0x01, 0x80, 0xC2, 0x00, 0x00, 0x03 पूर्ण;
	काष्ठा ethhdr *ehdr = (काष्ठा ethhdr *) rx->skb->data;

	/*
	 * Allow EAPOL frames to us/the PAE group address regardless of
	 * whether the frame was encrypted or not, and always disallow
	 * all other destination addresses क्रम them.
	 */
	अगर (unlikely(ehdr->h_proto == rx->sdata->control_port_protocol))
		वापस ether_addr_equal(ehdr->h_dest, rx->sdata->vअगर.addr) ||
		       ether_addr_equal(ehdr->h_dest, pae_group_addr);

	अगर (ieee80211_802_1x_port_control(rx) ||
	    ieee80211_drop_unencrypted(rx, fc))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ieee80211_deliver_skb_to_local_stack(काष्ठा sk_buff *skb,
						 काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा net_device *dev = sdata->dev;

	अगर (unlikely((skb->protocol == sdata->control_port_protocol ||
		     (skb->protocol == cpu_to_be16(ETH_P_PREAUTH) &&
		      !sdata->control_port_no_preauth)) &&
		     sdata->control_port_over_nl80211)) अणु
		काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
		bool noencrypt = !(status->flag & RX_FLAG_DECRYPTED);

		cfg80211_rx_control_port(dev, skb, noencrypt);
		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		काष्ठा ethhdr *ehdr = (व्योम *)skb_mac_header(skb);

		स_रखो(skb->cb, 0, माप(skb->cb));

		/*
		 * 802.1X over 802.11 requires that the authenticator address
		 * be used क्रम EAPOL frames. However, 802.1X allows the use of
		 * the PAE group address instead. If the पूर्णांकerface is part of
		 * a bridge and we pass the frame with the PAE group address,
		 * then the bridge will क्रमward it to the network (even अगर the
		 * client was not associated yet), which isn't supposed to
		 * happen.
		 * To aव्योम that, reग_लिखो the destination address to our own
		 * address, so that the authenticator (e.g. hostapd) will see
		 * the frame, but bridge won't क्रमward it anywhere अन्यथा. Note
		 * that due to earlier filtering, the only other address can
		 * be the PAE group address.
		 */
		अगर (unlikely(skb->protocol == sdata->control_port_protocol &&
			     !ether_addr_equal(ehdr->h_dest, sdata->vअगर.addr)))
			ether_addr_copy(ehdr->h_dest, sdata->vअगर.addr);

		/* deliver to local stack */
		अगर (rx->list)
			list_add_tail(&skb->list, rx->list);
		अन्यथा
			netअगर_receive_skb(skb);
	पूर्ण
पूर्ण

/*
 * requires that rx->skb is a frame with ethernet header
 */
अटल व्योम
ieee80211_deliver_skb(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा net_device *dev = sdata->dev;
	काष्ठा sk_buff *skb, *xmit_skb;
	काष्ठा ethhdr *ehdr = (काष्ठा ethhdr *) rx->skb->data;
	काष्ठा sta_info *dsta;

	skb = rx->skb;
	xmit_skb = शून्य;

	dev_sw_netstats_rx_add(dev, skb->len);

	अगर (rx->sta) अणु
		/* The seqno index has the same property as needed
		 * क्रम the rx_msdu field, i.e. it is IEEE80211_NUM_TIDS
		 * क्रम non-QoS-data frames. Here we know it's a data
		 * frame, so count MSDUs.
		 */
		u64_stats_update_begin(&rx->sta->rx_stats.syncp);
		rx->sta->rx_stats.msdu[rx->seqno_idx]++;
		u64_stats_update_end(&rx->sta->rx_stats.syncp);
	पूर्ण

	अगर ((sdata->vअगर.type == NL80211_IFTYPE_AP ||
	     sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) &&
	    !(sdata->flags & IEEE80211_SDATA_DONT_BRIDGE_PACKETS) &&
	    ehdr->h_proto != rx->sdata->control_port_protocol &&
	    (sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN || !sdata->u.vlan.sta)) अणु
		अगर (is_multicast_ether_addr(ehdr->h_dest) &&
		    ieee80211_vअगर_get_num_mcast_अगर(sdata) != 0) अणु
			/*
			 * send multicast frames both to higher layers in
			 * local net stack and back to the wireless medium
			 */
			xmit_skb = skb_copy(skb, GFP_ATOMIC);
			अगर (!xmit_skb)
				net_info_ratelimited("%s: failed to clone multicast frame\n",
						    dev->name);
		पूर्ण अन्यथा अगर (!is_multicast_ether_addr(ehdr->h_dest) &&
			   !ether_addr_equal(ehdr->h_dest, ehdr->h_source)) अणु
			dsta = sta_info_get(sdata, ehdr->h_dest);
			अगर (dsta) अणु
				/*
				 * The destination station is associated to
				 * this AP (in this VLAN), so send the frame
				 * directly to it and करो not pass it to local
				 * net stack.
				 */
				xmit_skb = skb;
				skb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (skb) अणु
		/* 'align' will only take the values 0 or 2 here since all
		 * frames are required to be aligned to 2-byte boundaries
		 * when being passed to mac80211; the code here works just
		 * as well अगर that isn't true, but mac80211 assumes it can
		 * access fields as 2-byte aligned (e.g. क्रम ether_addr_equal)
		 */
		पूर्णांक align;

		align = (अचिन्हित दीर्घ)(skb->data + माप(काष्ठा ethhdr)) & 3;
		अगर (align) अणु
			अगर (WARN_ON(skb_headroom(skb) < 3)) अणु
				dev_kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण अन्यथा अणु
				u8 *data = skb->data;
				माप_प्रकार len = skb_headlen(skb);
				skb->data -= align;
				स_हटाओ(skb->data, data, len);
				skb_set_tail_poपूर्णांकer(skb, len);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (skb) अणु
		skb->protocol = eth_type_trans(skb, dev);
		ieee80211_deliver_skb_to_local_stack(skb, rx);
	पूर्ण

	अगर (xmit_skb) अणु
		/*
		 * Send to wireless media and increase priority by 256 to
		 * keep the received priority instead of reclassअगरying
		 * the frame (see cfg80211_classअगरy8021d).
		 */
		xmit_skb->priority += 256;
		xmit_skb->protocol = htons(ETH_P_802_3);
		skb_reset_network_header(xmit_skb);
		skb_reset_mac_header(xmit_skb);
		dev_queue_xmit(xmit_skb);
	पूर्ण
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
__ieee80211_rx_h_amsdu(काष्ठा ieee80211_rx_data *rx, u8 data_offset)
अणु
	काष्ठा net_device *dev = rx->sdata->dev;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;
	काष्ठा sk_buff_head frame_list;
	काष्ठा ethhdr ethhdr;
	स्थिर u8 *check_da = ethhdr.h_dest, *check_sa = ethhdr.h_source;

	अगर (unlikely(ieee80211_has_a4(hdr->frame_control))) अणु
		check_da = शून्य;
		check_sa = शून्य;
	पूर्ण अन्यथा चयन (rx->sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_AP_VLAN:
			check_da = शून्य;
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			अगर (!rx->sta ||
			    !test_sta_flag(rx->sta, WLAN_STA_TDLS_PEER))
				check_sa = शून्य;
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			check_sa = शून्य;
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	skb->dev = dev;
	__skb_queue_head_init(&frame_list);

	अगर (ieee80211_data_to_8023_exthdr(skb, &ethhdr,
					  rx->sdata->vअगर.addr,
					  rx->sdata->vअगर.type,
					  data_offset, true))
		वापस RX_DROP_UNUSABLE;

	ieee80211_amsdu_to_8023s(skb, &frame_list, dev->dev_addr,
				 rx->sdata->vअगर.type,
				 rx->local->hw.extra_tx_headroom,
				 check_da, check_sa);

	जबतक (!skb_queue_empty(&frame_list)) अणु
		rx->skb = __skb_dequeue(&frame_list);

		अगर (!ieee80211_frame_allowed(rx, fc)) अणु
			dev_kमुक्त_skb(rx->skb);
			जारी;
		पूर्ण

		ieee80211_deliver_skb(rx);
	पूर्ण

	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_amsdu(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;

	अगर (!(status->rx_flags & IEEE80211_RX_AMSDU))
		वापस RX_CONTINUE;

	अगर (unlikely(!ieee80211_is_data(fc)))
		वापस RX_CONTINUE;

	अगर (unlikely(!ieee80211_is_data_present(fc)))
		वापस RX_DROP_MONITOR;

	अगर (unlikely(ieee80211_has_a4(hdr->frame_control))) अणु
		चयन (rx->sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_AP_VLAN:
			अगर (!rx->sdata->u.vlan.sta)
				वापस RX_DROP_UNUSABLE;
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			अगर (!rx->sdata->u.mgd.use_4addr)
				वापस RX_DROP_UNUSABLE;
			अवरोध;
		शेष:
			वापस RX_DROP_UNUSABLE;
		पूर्ण
	पूर्ण

	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस RX_DROP_UNUSABLE;

	अगर (rx->key) अणु
		/*
		 * We should not receive A-MSDUs on pre-HT connections,
		 * and HT connections cannot use old ciphers. Thus drop
		 * them, as in those हालs we couldn't even have SPP
		 * A-MSDUs or such.
		 */
		चयन (rx->key->conf.cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			वापस RX_DROP_UNUSABLE;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस __ieee80211_rx_h_amsdu(rx, 0);
पूर्ण

#अगर_घोषित CONFIG_MAC80211_MESH
अटल ieee80211_rx_result
ieee80211_rx_h_mesh_fwding(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *fwd_hdr, *hdr;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211s_hdr *mesh_hdr;
	काष्ठा sk_buff *skb = rx->skb, *fwd_skb;
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	u16 ac, q, hdrlen;
	पूर्णांक tailroom = 0;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	/* make sure fixed part of mesh header is there, also checks skb len */
	अगर (!pskb_may_pull(rx->skb, hdrlen + 6))
		वापस RX_DROP_MONITOR;

	mesh_hdr = (काष्ठा ieee80211s_hdr *) (skb->data + hdrlen);

	/* make sure full mesh header is there, also checks skb len */
	अगर (!pskb_may_pull(rx->skb,
			   hdrlen + ieee80211_get_mesh_hdrlen(mesh_hdr)))
		वापस RX_DROP_MONITOR;

	/* reload poपूर्णांकers */
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	mesh_hdr = (काष्ठा ieee80211s_hdr *) (skb->data + hdrlen);

	अगर (ieee80211_drop_unencrypted(rx, hdr->frame_control))
		वापस RX_DROP_MONITOR;

	/* frame is in RMC, करोn't क्रमward */
	अगर (ieee80211_is_data(hdr->frame_control) &&
	    is_multicast_ether_addr(hdr->addr1) &&
	    mesh_rmc_check(rx->sdata, hdr->addr3, mesh_hdr))
		वापस RX_DROP_MONITOR;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस RX_CONTINUE;

	अगर (!mesh_hdr->ttl)
		वापस RX_DROP_MONITOR;

	अगर (mesh_hdr->flags & MESH_FLAGS_AE) अणु
		काष्ठा mesh_path *mppath;
		अक्षर *proxied_addr;
		अक्षर *mpp_addr;

		अगर (is_multicast_ether_addr(hdr->addr1)) अणु
			mpp_addr = hdr->addr3;
			proxied_addr = mesh_hdr->eaddr1;
		पूर्ण अन्यथा अगर ((mesh_hdr->flags & MESH_FLAGS_AE) ==
			    MESH_FLAGS_AE_A5_A6) अणु
			/* has_a4 alपढ़ोy checked in ieee80211_rx_mesh_check */
			mpp_addr = hdr->addr4;
			proxied_addr = mesh_hdr->eaddr2;
		पूर्ण अन्यथा अणु
			वापस RX_DROP_MONITOR;
		पूर्ण

		rcu_पढ़ो_lock();
		mppath = mpp_path_lookup(sdata, proxied_addr);
		अगर (!mppath) अणु
			mpp_path_add(sdata, proxied_addr, mpp_addr);
		पूर्ण अन्यथा अणु
			spin_lock_bh(&mppath->state_lock);
			अगर (!ether_addr_equal(mppath->mpp, mpp_addr))
				स_नकल(mppath->mpp, mpp_addr, ETH_ALEN);
			mppath->exp_समय = jअगरfies;
			spin_unlock_bh(&mppath->state_lock);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* Frame has reached destination.  Don't क्रमward */
	अगर (!is_multicast_ether_addr(hdr->addr1) &&
	    ether_addr_equal(sdata->vअगर.addr, hdr->addr3))
		वापस RX_CONTINUE;

	ac = ieee80211_select_queue_80211(sdata, skb, hdr);
	q = sdata->vअगर.hw_queue[ac];
	अगर (ieee80211_queue_stopped(&local->hw, q)) अणु
		IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh, dropped_frames_congestion);
		वापस RX_DROP_MONITOR;
	पूर्ण
	skb_set_queue_mapping(skb, q);

	अगर (!--mesh_hdr->ttl) अणु
		अगर (!is_multicast_ether_addr(hdr->addr1))
			IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh,
						     dropped_frames_ttl);
		जाओ out;
	पूर्ण

	अगर (!अगरmsh->mshcfg.करोt11MeshForwarding)
		जाओ out;

	अगर (sdata->crypto_tx_tailroom_needed_cnt)
		tailroom = IEEE80211_ENCRYPT_TAILROOM;

	fwd_skb = skb_copy_expand(skb, local->tx_headroom +
				       sdata->encrypt_headroom,
				  tailroom, GFP_ATOMIC);
	अगर (!fwd_skb)
		जाओ out;

	fwd_hdr =  (काष्ठा ieee80211_hdr *) fwd_skb->data;
	fwd_hdr->frame_control &= ~cpu_to_le16(IEEE80211_FCTL_RETRY);
	info = IEEE80211_SKB_CB(fwd_skb);
	स_रखो(info, 0, माप(*info));
	info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
	info->control.vअगर = &rx->sdata->vअगर;
	info->control.jअगरfies = jअगरfies;
	अगर (is_multicast_ether_addr(fwd_hdr->addr1)) अणु
		IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh, fwded_mcast);
		स_नकल(fwd_hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
		/* update घातer mode indication when क्रमwarding */
		ieee80211_mps_set_frame_flags(sdata, शून्य, fwd_hdr);
	पूर्ण अन्यथा अगर (!mesh_nexthop_lookup(sdata, fwd_skb)) अणु
		/* mesh घातer mode flags updated in mesh_nexthop_lookup */
		IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh, fwded_unicast);
	पूर्ण अन्यथा अणु
		/* unable to resolve next hop */
		mesh_path_error_tx(sdata, अगरmsh->mshcfg.element_ttl,
				   fwd_hdr->addr3, 0,
				   WLAN_REASON_MESH_PATH_NOFORWARD,
				   fwd_hdr->addr2);
		IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh, dropped_frames_no_route);
		kमुक्त_skb(fwd_skb);
		वापस RX_DROP_MONITOR;
	पूर्ण

	IEEE80211_IFSTA_MESH_CTR_INC(अगरmsh, fwded_frames);
	ieee80211_add_pending_skb(local, fwd_skb);
 out:
	अगर (is_multicast_ether_addr(hdr->addr1))
		वापस RX_CONTINUE;
	वापस RX_DROP_MONITOR;
पूर्ण
#पूर्ण_अगर

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_data(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा net_device *dev = sdata->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	__le16 fc = hdr->frame_control;
	bool port_control;
	पूर्णांक err;

	अगर (unlikely(!ieee80211_is_data(hdr->frame_control)))
		वापस RX_CONTINUE;

	अगर (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		वापस RX_DROP_MONITOR;

	/*
	 * Send unexpected-4addr-frame event to hostapd. For older versions,
	 * also drop the frame to cooked monitor पूर्णांकerfaces.
	 */
	अगर (ieee80211_has_a4(hdr->frame_control) &&
	    sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		अगर (rx->sta &&
		    !test_and_set_sta_flag(rx->sta, WLAN_STA_4ADDR_EVENT))
			cfg80211_rx_unexpected_4addr_frame(
				rx->sdata->dev, rx->sta->sta.addr, GFP_ATOMIC);
		वापस RX_DROP_MONITOR;
	पूर्ण

	err = __ieee80211_data_to_8023(rx, &port_control);
	अगर (unlikely(err))
		वापस RX_DROP_UNUSABLE;

	अगर (!ieee80211_frame_allowed(rx, fc))
		वापस RX_DROP_MONITOR;

	/* directly handle TDLS channel चयन requests/responses */
	अगर (unlikely(((काष्ठा ethhdr *)rx->skb->data)->h_proto ==
						cpu_to_be16(ETH_P_TDLS))) अणु
		काष्ठा ieee80211_tdls_data *tf = (व्योम *)rx->skb->data;

		अगर (pskb_may_pull(rx->skb,
				  दुरत्व(काष्ठा ieee80211_tdls_data, u)) &&
		    tf->payload_type == WLAN_TDLS_SNAP_RFTYPE &&
		    tf->category == WLAN_CATEGORY_TDLS &&
		    (tf->action_code == WLAN_TDLS_CHANNEL_SWITCH_REQUEST ||
		     tf->action_code == WLAN_TDLS_CHANNEL_SWITCH_RESPONSE)) अणु
			skb_queue_tail(&local->skb_queue_tdls_chsw, rx->skb);
			schedule_work(&local->tdls_chsw_work);
			अगर (rx->sta)
				rx->sta->rx_stats.packets++;

			वापस RX_QUEUED;
		पूर्ण
	पूर्ण

	अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN &&
	    unlikely(port_control) && sdata->bss) अणु
		sdata = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data,
				     u.ap);
		dev = sdata->dev;
		rx->sdata = sdata;
	पूर्ण

	rx->skb->dev = dev;

	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS) &&
	    local->ps_sdata && local->hw.conf.dynamic_ps_समयout > 0 &&
	    !is_multicast_ether_addr(
		    ((काष्ठा ethhdr *)rx->skb->data)->h_dest) &&
	    (!local->scanning &&
	     !test_bit(SDATA_STATE_OFFCHANNEL, &sdata->state)))
		mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
			  msecs_to_jअगरfies(local->hw.conf.dynamic_ps_समयout));

	ieee80211_deliver_skb(rx);

	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_ctrl(काष्ठा ieee80211_rx_data *rx, काष्ठा sk_buff_head *frames)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_bar *bar = (काष्ठा ieee80211_bar *)skb->data;
	काष्ठा tid_ampdu_rx *tid_agg_rx;
	u16 start_seq_num;
	u16 tid;

	अगर (likely(!ieee80211_is_ctl(bar->frame_control)))
		वापस RX_CONTINUE;

	अगर (ieee80211_is_back_req(bar->frame_control)) अणु
		काष्ठा अणु
			__le16 control, start_seq_num;
		पूर्ण __packed bar_data;
		काष्ठा ieee80211_event event = अणु
			.type = BAR_RX_EVENT,
		पूर्ण;

		अगर (!rx->sta)
			वापस RX_DROP_MONITOR;

		अगर (skb_copy_bits(skb, दुरत्व(काष्ठा ieee80211_bar, control),
				  &bar_data, माप(bar_data)))
			वापस RX_DROP_MONITOR;

		tid = le16_to_cpu(bar_data.control) >> 12;

		अगर (!test_bit(tid, rx->sta->ampdu_mlme.agg_session_valid) &&
		    !test_and_set_bit(tid, rx->sta->ampdu_mlme.unexpected_agg))
			ieee80211_send_delba(rx->sdata, rx->sta->sta.addr, tid,
					     WLAN_BACK_RECIPIENT,
					     WLAN_REASON_QSTA_REQUIRE_SETUP);

		tid_agg_rx = rcu_dereference(rx->sta->ampdu_mlme.tid_rx[tid]);
		अगर (!tid_agg_rx)
			वापस RX_DROP_MONITOR;

		start_seq_num = le16_to_cpu(bar_data.start_seq_num) >> 4;
		event.u.ba.tid = tid;
		event.u.ba.ssn = start_seq_num;
		event.u.ba.sta = &rx->sta->sta;

		/* reset session समयr */
		अगर (tid_agg_rx->समयout)
			mod_समयr(&tid_agg_rx->session_समयr,
				  TU_TO_EXP_TIME(tid_agg_rx->समयout));

		spin_lock(&tid_agg_rx->reorder_lock);
		/* release stored frames up to start of BAR */
		ieee80211_release_reorder_frames(rx->sdata, tid_agg_rx,
						 start_seq_num, frames);
		spin_unlock(&tid_agg_rx->reorder_lock);

		drv_event_callback(rx->local, rx->sdata, &event);

		kमुक्त_skb(skb);
		वापस RX_QUEUED;
	पूर्ण

	/*
	 * After this poपूर्णांक, we only want management frames,
	 * so we can drop all reमुख्यing control frames to
	 * cooked monitor पूर्णांकerfaces.
	 */
	वापस RX_DROP_MONITOR;
पूर्ण

अटल व्योम ieee80211_process_sa_query_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा ieee80211_mgmt *mgmt,
					   माप_प्रकार len)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *resp;

	अगर (!ether_addr_equal(mgmt->da, sdata->vअगर.addr)) अणु
		/* Not to own unicast address */
		वापस;
	पूर्ण

	अगर (!ether_addr_equal(mgmt->sa, sdata->u.mgd.bssid) ||
	    !ether_addr_equal(mgmt->bssid, sdata->u.mgd.bssid)) अणु
		/* Not from the current AP or not associated yet. */
		वापस;
	पूर्ण

	अगर (len < 24 + 1 + माप(resp->u.action.u.sa_query)) अणु
		/* Too लघु SA Query request frame */
		वापस;
	पूर्ण

	skb = dev_alloc_skb(माप(*resp) + local->hw.extra_tx_headroom);
	अगर (skb == शून्य)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	resp = skb_put_zero(skb, 24);
	स_नकल(resp->da, mgmt->sa, ETH_ALEN);
	स_नकल(resp->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(resp->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	resp->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	skb_put(skb, 1 + माप(resp->u.action.u.sa_query));
	resp->u.action.category = WLAN_CATEGORY_SA_QUERY;
	resp->u.action.u.sa_query.action = WLAN_ACTION_SA_QUERY_RESPONSE;
	स_नकल(resp->u.action.u.sa_query.trans_id,
	       mgmt->u.action.u.sa_query.trans_id,
	       WLAN_SA_QUERY_TR_ID_LEN);

	ieee80211_tx_skb(sdata, skb);
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_mgmt_check(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *) rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);

	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control))
		वापस RX_CONTINUE;

	/*
	 * From here on, look only at management frames.
	 * Data and control frames are alपढ़ोy handled,
	 * and unknown (reserved) frames are useless.
	 */
	अगर (rx->skb->len < 24)
		वापस RX_DROP_MONITOR;

	अगर (!ieee80211_is_mgmt(mgmt->frame_control))
		वापस RX_DROP_MONITOR;

	अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_AP &&
	    ieee80211_is_beacon(mgmt->frame_control) &&
	    !(rx->flags & IEEE80211_RX_BEACON_REPORTED)) अणु
		पूर्णांक sig = 0;

		अगर (ieee80211_hw_check(&rx->local->hw, SIGNAL_DBM) &&
		    !(status->flag & RX_FLAG_NO_SIGNAL_VAL))
			sig = status->संकेत;

		cfg80211_report_obss_beacon_khz(rx->local->hw.wiphy,
						rx->skb->data, rx->skb->len,
						ieee80211_rx_status_to_khz(status),
						sig);
		rx->flags |= IEEE80211_RX_BEACON_REPORTED;
	पूर्ण

	अगर (ieee80211_drop_unencrypted_mgmt(rx))
		वापस RX_DROP_UNUSABLE;

	वापस RX_CONTINUE;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_action(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *) rx->skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	पूर्णांक len = rx->skb->len;

	अगर (!ieee80211_is_action(mgmt->frame_control))
		वापस RX_CONTINUE;

	/* drop too small frames */
	अगर (len < IEEE80211_MIN_ACTION_SIZE)
		वापस RX_DROP_UNUSABLE;

	अगर (!rx->sta && mgmt->u.action.category != WLAN_CATEGORY_PUBLIC &&
	    mgmt->u.action.category != WLAN_CATEGORY_SELF_PROTECTED &&
	    mgmt->u.action.category != WLAN_CATEGORY_SPECTRUM_MGMT)
		वापस RX_DROP_UNUSABLE;

	चयन (mgmt->u.action.category) अणु
	हाल WLAN_CATEGORY_HT:
		/* reject HT action frames from stations not supporting HT */
		अगर (!rx->sta->sta.ht_cap.ht_supported)
			जाओ invalid;

		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
		    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP &&
		    sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
			अवरोध;

		/* verअगरy action & smps_control/chanwidth are present */
		अगर (len < IEEE80211_MIN_ACTION_SIZE + 2)
			जाओ invalid;

		चयन (mgmt->u.action.u.ht_smps.action) अणु
		हाल WLAN_HT_ACTION_SMPS: अणु
			काष्ठा ieee80211_supported_band *sband;
			क्रमागत ieee80211_smps_mode smps_mode;
			काष्ठा sta_opmode_info sta_opmode = अणुपूर्ण;

			अगर (sdata->vअगर.type != NL80211_IFTYPE_AP &&
			    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN)
				जाओ handled;

			/* convert to HT capability */
			चयन (mgmt->u.action.u.ht_smps.smps_control) अणु
			हाल WLAN_HT_SMPS_CONTROL_DISABLED:
				smps_mode = IEEE80211_SMPS_OFF;
				अवरोध;
			हाल WLAN_HT_SMPS_CONTROL_STATIC:
				smps_mode = IEEE80211_SMPS_STATIC;
				अवरोध;
			हाल WLAN_HT_SMPS_CONTROL_DYNAMIC:
				smps_mode = IEEE80211_SMPS_DYNAMIC;
				अवरोध;
			शेष:
				जाओ invalid;
			पूर्ण

			/* अगर no change करो nothing */
			अगर (rx->sta->sta.smps_mode == smps_mode)
				जाओ handled;
			rx->sta->sta.smps_mode = smps_mode;
			sta_opmode.smps_mode =
				ieee80211_smps_mode_to_smps_mode(smps_mode);
			sta_opmode.changed = STA_OPMODE_SMPS_MODE_CHANGED;

			sband = rx->local->hw.wiphy->bands[status->band];

			rate_control_rate_update(local, sband, rx->sta,
						 IEEE80211_RC_SMPS_CHANGED);
			cfg80211_sta_opmode_change_notअगरy(sdata->dev,
							  rx->sta->addr,
							  &sta_opmode,
							  GFP_ATOMIC);
			जाओ handled;
		पूर्ण
		हाल WLAN_HT_ACTION_NOTIFY_CHANWIDTH: अणु
			काष्ठा ieee80211_supported_band *sband;
			u8 chanwidth = mgmt->u.action.u.ht_notअगरy_cw.chanwidth;
			क्रमागत ieee80211_sta_rx_bandwidth max_bw, new_bw;
			काष्ठा sta_opmode_info sta_opmode = अणुपूर्ण;

			/* If it करोesn't support 40 MHz it can't change ... */
			अगर (!(rx->sta->sta.ht_cap.cap &
					IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				जाओ handled;

			अगर (chanwidth == IEEE80211_HT_CHANWIDTH_20MHZ)
				max_bw = IEEE80211_STA_RX_BW_20;
			अन्यथा
				max_bw = ieee80211_sta_cap_rx_bw(rx->sta);

			/* set cur_max_bandwidth and recalc sta bw */
			rx->sta->cur_max_bandwidth = max_bw;
			new_bw = ieee80211_sta_cur_vht_bw(rx->sta);

			अगर (rx->sta->sta.bandwidth == new_bw)
				जाओ handled;

			rx->sta->sta.bandwidth = new_bw;
			sband = rx->local->hw.wiphy->bands[status->band];
			sta_opmode.bw =
				ieee80211_sta_rx_bw_to_chan_width(rx->sta);
			sta_opmode.changed = STA_OPMODE_MAX_BW_CHANGED;

			rate_control_rate_update(local, sband, rx->sta,
						 IEEE80211_RC_BW_CHANGED);
			cfg80211_sta_opmode_change_notअगरy(sdata->dev,
							  rx->sta->addr,
							  &sta_opmode,
							  GFP_ATOMIC);
			जाओ handled;
		पूर्ण
		शेष:
			जाओ invalid;
		पूर्ण

		अवरोध;
	हाल WLAN_CATEGORY_PUBLIC:
		अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
			जाओ invalid;
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
			अवरोध;
		अगर (!rx->sta)
			अवरोध;
		अगर (!ether_addr_equal(mgmt->bssid, sdata->u.mgd.bssid))
			अवरोध;
		अगर (mgmt->u.action.u.ext_chan_चयन.action_code !=
				WLAN_PUB_ACTION_EXT_CHANSW_ANN)
			अवरोध;
		अगर (len < दुरत्व(काष्ठा ieee80211_mgmt,
				   u.action.u.ext_chan_चयन.variable))
			जाओ invalid;
		जाओ queue;
	हाल WLAN_CATEGORY_VHT:
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
		    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP &&
		    sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
			अवरोध;

		/* verअगरy action code is present */
		अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
			जाओ invalid;

		चयन (mgmt->u.action.u.vht_opmode_notअगर.action_code) अणु
		हाल WLAN_VHT_ACTION_OPMODE_NOTIF: अणु
			/* verअगरy opmode is present */
			अगर (len < IEEE80211_MIN_ACTION_SIZE + 2)
				जाओ invalid;
			जाओ queue;
		पूर्ण
		हाल WLAN_VHT_ACTION_GROUPID_MGMT: अणु
			अगर (len < IEEE80211_MIN_ACTION_SIZE + 25)
				जाओ invalid;
			जाओ queue;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WLAN_CATEGORY_BACK:
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
		    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP &&
		    sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
			अवरोध;

		/* verअगरy action_code is present */
		अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
			अवरोध;

		चयन (mgmt->u.action.u.addba_req.action_code) अणु
		हाल WLAN_ACTION_ADDBA_REQ:
			अगर (len < (IEEE80211_MIN_ACTION_SIZE +
				   माप(mgmt->u.action.u.addba_req)))
				जाओ invalid;
			अवरोध;
		हाल WLAN_ACTION_ADDBA_RESP:
			अगर (len < (IEEE80211_MIN_ACTION_SIZE +
				   माप(mgmt->u.action.u.addba_resp)))
				जाओ invalid;
			अवरोध;
		हाल WLAN_ACTION_DELBA:
			अगर (len < (IEEE80211_MIN_ACTION_SIZE +
				   माप(mgmt->u.action.u.delba)))
				जाओ invalid;
			अवरोध;
		शेष:
			जाओ invalid;
		पूर्ण

		जाओ queue;
	हाल WLAN_CATEGORY_SPECTRUM_MGMT:
		/* verअगरy action_code is present */
		अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
			अवरोध;

		चयन (mgmt->u.action.u.measurement.action_code) अणु
		हाल WLAN_ACTION_SPCT_MSR_REQ:
			अगर (status->band != NL80211_BAND_5GHZ)
				अवरोध;

			अगर (len < (IEEE80211_MIN_ACTION_SIZE +
				   माप(mgmt->u.action.u.measurement)))
				अवरोध;

			अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
				अवरोध;

			ieee80211_process_measurement_req(sdata, mgmt, len);
			जाओ handled;
		हाल WLAN_ACTION_SPCT_CHL_SWITCH: अणु
			u8 *bssid;
			अगर (len < (IEEE80211_MIN_ACTION_SIZE +
				   माप(mgmt->u.action.u.chan_चयन)))
				अवरोध;

			अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
			    sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
			    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT)
				अवरोध;

			अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
				bssid = sdata->u.mgd.bssid;
			अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
				bssid = sdata->u.ibss.bssid;
			अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT)
				bssid = mgmt->sa;
			अन्यथा
				अवरोध;

			अगर (!ether_addr_equal(mgmt->bssid, bssid))
				अवरोध;

			जाओ queue;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WLAN_CATEGORY_SELF_PROTECTED:
		अगर (len < (IEEE80211_MIN_ACTION_SIZE +
			   माप(mgmt->u.action.u.self_prot.action_code)))
			अवरोध;

		चयन (mgmt->u.action.u.self_prot.action_code) अणु
		हाल WLAN_SP_MESH_PEERING_OPEN:
		हाल WLAN_SP_MESH_PEERING_CLOSE:
		हाल WLAN_SP_MESH_PEERING_CONFIRM:
			अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर))
				जाओ invalid;
			अगर (sdata->u.mesh.user_mpm)
				/* userspace handles this frame */
				अवरोध;
			जाओ queue;
		हाल WLAN_SP_MGK_INFORM:
		हाल WLAN_SP_MGK_ACK:
			अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर))
				जाओ invalid;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WLAN_CATEGORY_MESH_ACTION:
		अगर (len < (IEEE80211_MIN_ACTION_SIZE +
			   माप(mgmt->u.action.u.mesh_action.action_code)))
			अवरोध;

		अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर))
			अवरोध;
		अगर (mesh_action_is_path_sel(mgmt) &&
		    !mesh_path_sel_is_hwmp(sdata))
			अवरोध;
		जाओ queue;
	पूर्ण

	वापस RX_CONTINUE;

 invalid:
	status->rx_flags |= IEEE80211_RX_MALFORMED_ACTION_FRM;
	/* will वापस in the next handlers */
	वापस RX_CONTINUE;

 handled:
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;
	dev_kमुक्त_skb(rx->skb);
	वापस RX_QUEUED;

 queue:
	skb_queue_tail(&sdata->skb_queue, rx->skb);
	ieee80211_queue_work(&local->hw, &sdata->work);
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;
	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_userspace_mgmt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	पूर्णांक sig = 0;

	/* skip known-bad action frames and वापस them in the next handler */
	अगर (status->rx_flags & IEEE80211_RX_MALFORMED_ACTION_FRM)
		वापस RX_CONTINUE;

	/*
	 * Getting here means the kernel करोesn't know how to handle
	 * it, but maybe userspace करोes ... include वापसed frames
	 * so userspace can रेजिस्टर क्रम those to know whether ones
	 * it transmitted were processed or वापसed.
	 */

	अगर (ieee80211_hw_check(&rx->local->hw, SIGNAL_DBM) &&
	    !(status->flag & RX_FLAG_NO_SIGNAL_VAL))
		sig = status->संकेत;

	अगर (cfg80211_rx_mgmt_khz(&rx->sdata->wdev,
				 ieee80211_rx_status_to_khz(status), sig,
				 rx->skb->data, rx->skb->len, 0)) अणु
		अगर (rx->sta)
			rx->sta->rx_stats.packets++;
		dev_kमुक्त_skb(rx->skb);
		वापस RX_QUEUED;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_action_post_userspace(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *) rx->skb->data;
	पूर्णांक len = rx->skb->len;

	अगर (!ieee80211_is_action(mgmt->frame_control))
		वापस RX_CONTINUE;

	चयन (mgmt->u.action.category) अणु
	हाल WLAN_CATEGORY_SA_QUERY:
		अगर (len < (IEEE80211_MIN_ACTION_SIZE +
			   माप(mgmt->u.action.u.sa_query)))
			अवरोध;

		चयन (mgmt->u.action.u.sa_query.action) अणु
		हाल WLAN_ACTION_SA_QUERY_REQUEST:
			अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
				अवरोध;
			ieee80211_process_sa_query_req(sdata, mgmt, len);
			जाओ handled;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस RX_CONTINUE;

 handled:
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;
	dev_kमुक्त_skb(rx->skb);
	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_action_वापस(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *) rx->skb->data;
	काष्ठा sk_buff *nskb;
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);

	अगर (!ieee80211_is_action(mgmt->frame_control))
		वापस RX_CONTINUE;

	/*
	 * For AP mode, hostapd is responsible क्रम handling any action
	 * frames that we didn't handle, including वापसing unknown
	 * ones. For all other modes we will वापस them to the sender,
	 * setting the 0x80 bit in the action category, as required by
	 * 802.11-2012 9.24.4.
	 * Newer versions of hostapd shall also use the management frame
	 * registration mechanisms, but older ones still use cooked
	 * monitor पूर्णांकerfaces so push all frames there.
	 */
	अगर (!(status->rx_flags & IEEE80211_RX_MALFORMED_ACTION_FRM) &&
	    (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	     sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN))
		वापस RX_DROP_MONITOR;

	अगर (is_multicast_ether_addr(mgmt->da))
		वापस RX_DROP_MONITOR;

	/* करो not वापस rejected action frames */
	अगर (mgmt->u.action.category & 0x80)
		वापस RX_DROP_UNUSABLE;

	nskb = skb_copy_expand(rx->skb, local->hw.extra_tx_headroom, 0,
			       GFP_ATOMIC);
	अगर (nskb) अणु
		काष्ठा ieee80211_mgmt *nmgmt = (व्योम *)nskb->data;

		nmgmt->u.action.category |= 0x80;
		स_नकल(nmgmt->da, nmgmt->sa, ETH_ALEN);
		स_नकल(nmgmt->sa, rx->sdata->vअगर.addr, ETH_ALEN);

		स_रखो(nskb->cb, 0, माप(nskb->cb));

		अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_P2P_DEVICE) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(nskb);

			info->flags = IEEE80211_TX_CTL_TX_OFFCHAN |
				      IEEE80211_TX_INTFL_OFFCHAN_TX_OK |
				      IEEE80211_TX_CTL_NO_CCK_RATE;
			अगर (ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
				info->hw_queue =
					local->hw.offchannel_tx_hw_queue;
		पूर्ण

		__ieee80211_tx_skb_tid_band(rx->sdata, nskb, 7,
					    status->band);
	पूर्ण
	dev_kमुक्त_skb(rx->skb);
	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_ext(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)rx->skb->data;

	अगर (!ieee80211_is_ext(hdr->frame_control))
		वापस RX_CONTINUE;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस RX_DROP_MONITOR;

	/* क्रम now only beacons are ext, so queue them */
	skb_queue_tail(&sdata->skb_queue, rx->skb);
	ieee80211_queue_work(&rx->local->hw, &sdata->work);
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;

	वापस RX_QUEUED;
पूर्ण

अटल ieee80211_rx_result debug_noअंतरभूत
ieee80211_rx_h_mgmt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)rx->skb->data;
	__le16 stype;

	stype = mgmt->frame_control & cpu_to_le16(IEEE80211_FCTL_STYPE);

	अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
	    sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
	    sdata->vअगर.type != NL80211_IFTYPE_OCB &&
	    sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस RX_DROP_MONITOR;

	चयन (stype) अणु
	हाल cpu_to_le16(IEEE80211_STYPE_AUTH):
	हाल cpu_to_le16(IEEE80211_STYPE_BEACON):
	हाल cpu_to_le16(IEEE80211_STYPE_PROBE_RESP):
		/* process क्रम all: mesh, mlme, ibss */
		अवरोध;
	हाल cpu_to_le16(IEEE80211_STYPE_DEAUTH):
		अगर (is_multicast_ether_addr(mgmt->da) &&
		    !is_broadcast_ether_addr(mgmt->da))
			वापस RX_DROP_MONITOR;

		/* process only क्रम station/IBSS */
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
		    sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
			वापस RX_DROP_MONITOR;
		अवरोध;
	हाल cpu_to_le16(IEEE80211_STYPE_ASSOC_RESP):
	हाल cpu_to_le16(IEEE80211_STYPE_REASSOC_RESP):
	हाल cpu_to_le16(IEEE80211_STYPE_DISASSOC):
		अगर (is_multicast_ether_addr(mgmt->da) &&
		    !is_broadcast_ether_addr(mgmt->da))
			वापस RX_DROP_MONITOR;

		/* process only क्रम station */
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
			वापस RX_DROP_MONITOR;
		अवरोध;
	हाल cpu_to_le16(IEEE80211_STYPE_PROBE_REQ):
		/* process only क्रम ibss and mesh */
		अगर (sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
		    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT)
			वापस RX_DROP_MONITOR;
		अवरोध;
	शेष:
		वापस RX_DROP_MONITOR;
	पूर्ण

	/* queue up frame and kick off work to process it */
	skb_queue_tail(&sdata->skb_queue, rx->skb);
	ieee80211_queue_work(&rx->local->hw, &sdata->work);
	अगर (rx->sta)
		rx->sta->rx_stats.packets++;

	वापस RX_QUEUED;
पूर्ण

अटल व्योम ieee80211_rx_cooked_monitor(काष्ठा ieee80211_rx_data *rx,
					काष्ठा ieee80211_rate *rate)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा sk_buff *skb = rx->skb, *skb2;
	काष्ठा net_device *prev_dev = शून्य;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	पूर्णांक needed_headroom;

	/*
	 * If cooked monitor has been processed alपढ़ोy, then
	 * करोn't करो it again. If not, set the flag.
	 */
	अगर (rx->flags & IEEE80211_RX_CMNTR)
		जाओ out_मुक्त_skb;
	rx->flags |= IEEE80211_RX_CMNTR;

	/* If there are no cooked monitor पूर्णांकerfaces, just मुक्त the SKB */
	अगर (!local->cooked_mntrs)
		जाओ out_मुक्त_skb;

	/* venकरोr data is दीर्घ हटाओd here */
	status->flag &= ~RX_FLAG_RADIOTAP_VENDOR_DATA;
	/* room क्रम the radiotap header based on driver features */
	needed_headroom = ieee80211_rx_radiotap_hdrlen(local, status, skb);

	अगर (skb_headroom(skb) < needed_headroom &&
	    pskb_expand_head(skb, needed_headroom, 0, GFP_ATOMIC))
		जाओ out_मुक्त_skb;

	/* prepend radiotap inक्रमmation */
	ieee80211_add_rx_radiotap_header(local, skb, rate, needed_headroom,
					 false);

	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (sdata->vअगर.type != NL80211_IFTYPE_MONITOR ||
		    !(sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES))
			जारी;

		अगर (prev_dev) अणु
			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (skb2) अणु
				skb2->dev = prev_dev;
				netअगर_receive_skb(skb2);
			पूर्ण
		पूर्ण

		prev_dev = sdata->dev;
		dev_sw_netstats_rx_add(sdata->dev, skb->len);
	पूर्ण

	अगर (prev_dev) अणु
		skb->dev = prev_dev;
		netअगर_receive_skb(skb);
		वापस;
	पूर्ण

 out_मुक्त_skb:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम ieee80211_rx_handlers_result(काष्ठा ieee80211_rx_data *rx,
					 ieee80211_rx_result res)
अणु
	चयन (res) अणु
	हाल RX_DROP_MONITOR:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_drop);
		अगर (rx->sta)
			rx->sta->rx_stats.dropped++;
		fallthrough;
	हाल RX_CONTINUE: अणु
		काष्ठा ieee80211_rate *rate = शून्य;
		काष्ठा ieee80211_supported_band *sband;
		काष्ठा ieee80211_rx_status *status;

		status = IEEE80211_SKB_RXCB((rx->skb));

		sband = rx->local->hw.wiphy->bands[status->band];
		अगर (status->encoding == RX_ENC_LEGACY)
			rate = &sband->bitrates[status->rate_idx];

		ieee80211_rx_cooked_monitor(rx, rate);
		अवरोध;
		पूर्ण
	हाल RX_DROP_UNUSABLE:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_drop);
		अगर (rx->sta)
			rx->sta->rx_stats.dropped++;
		dev_kमुक्त_skb(rx->skb);
		अवरोध;
	हाल RX_QUEUED:
		I802_DEBUG_INC(rx->sdata->local->rx_handlers_queued);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ieee80211_rx_handlers(काष्ठा ieee80211_rx_data *rx,
				  काष्ठा sk_buff_head *frames)
अणु
	ieee80211_rx_result res = RX_DROP_MONITOR;
	काष्ठा sk_buff *skb;

#घोषणा CALL_RXH(rxh)			\
	करो अणु				\
		res = rxh(rx);		\
		अगर (res != RX_CONTINUE)	\
			जाओ rxh_next;  \
	पूर्ण जबतक (0)

	/* Lock here to aव्योम hitting all of the data used in the RX
	 * path (e.g. key data, station data, ...) concurrently when
	 * a frame is released from the reorder buffer due to समयout
	 * from the समयr, potentially concurrently with RX from the
	 * driver.
	 */
	spin_lock_bh(&rx->local->rx_path_lock);

	जबतक ((skb = __skb_dequeue(frames))) अणु
		/*
		 * all the other fields are valid across frames
		 * that beदीर्घ to an aMPDU since they are on the
		 * same TID from the same station
		 */
		rx->skb = skb;

		CALL_RXH(ieee80211_rx_h_check_more_data);
		CALL_RXH(ieee80211_rx_h_uapsd_and_pspoll);
		CALL_RXH(ieee80211_rx_h_sta_process);
		CALL_RXH(ieee80211_rx_h_decrypt);
		CALL_RXH(ieee80211_rx_h_defragment);
		CALL_RXH(ieee80211_rx_h_michael_mic_verअगरy);
		/* must be after MMIC verअगरy so header is counted in MPDU mic */
#अगर_घोषित CONFIG_MAC80211_MESH
		अगर (ieee80211_vअगर_is_mesh(&rx->sdata->vअगर))
			CALL_RXH(ieee80211_rx_h_mesh_fwding);
#पूर्ण_अगर
		CALL_RXH(ieee80211_rx_h_amsdu);
		CALL_RXH(ieee80211_rx_h_data);

		/* special treaपंचांगent -- needs the queue */
		res = ieee80211_rx_h_ctrl(rx, frames);
		अगर (res != RX_CONTINUE)
			जाओ rxh_next;

		CALL_RXH(ieee80211_rx_h_mgmt_check);
		CALL_RXH(ieee80211_rx_h_action);
		CALL_RXH(ieee80211_rx_h_userspace_mgmt);
		CALL_RXH(ieee80211_rx_h_action_post_userspace);
		CALL_RXH(ieee80211_rx_h_action_वापस);
		CALL_RXH(ieee80211_rx_h_ext);
		CALL_RXH(ieee80211_rx_h_mgmt);

 rxh_next:
		ieee80211_rx_handlers_result(rx, res);

#अघोषित CALL_RXH
	पूर्ण

	spin_unlock_bh(&rx->local->rx_path_lock);
पूर्ण

अटल व्योम ieee80211_invoke_rx_handlers(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff_head reorder_release;
	ieee80211_rx_result res = RX_DROP_MONITOR;

	__skb_queue_head_init(&reorder_release);

#घोषणा CALL_RXH(rxh)			\
	करो अणु				\
		res = rxh(rx);		\
		अगर (res != RX_CONTINUE)	\
			जाओ rxh_next;  \
	पूर्ण जबतक (0)

	CALL_RXH(ieee80211_rx_h_check_dup);
	CALL_RXH(ieee80211_rx_h_check);

	ieee80211_rx_reorder_ampdu(rx, &reorder_release);

	ieee80211_rx_handlers(rx, &reorder_release);
	वापस;

 rxh_next:
	ieee80211_rx_handlers_result(rx, res);

#अघोषित CALL_RXH
पूर्ण

/*
 * This function makes calls पूर्णांकo the RX path, thereक्रमe
 * it has to be invoked under RCU पढ़ो lock.
 */
व्योम ieee80211_release_reorder_समयout(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	काष्ठा sk_buff_head frames;
	काष्ठा ieee80211_rx_data rx = अणु
		.sta = sta,
		.sdata = sta->sdata,
		.local = sta->local,
		/* This is OK -- must be QoS data frame */
		.security_idx = tid,
		.seqno_idx = tid,
	पूर्ण;
	काष्ठा tid_ampdu_rx *tid_agg_rx;

	tid_agg_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
	अगर (!tid_agg_rx)
		वापस;

	__skb_queue_head_init(&frames);

	spin_lock(&tid_agg_rx->reorder_lock);
	ieee80211_sta_reorder_release(sta->sdata, tid_agg_rx, &frames);
	spin_unlock(&tid_agg_rx->reorder_lock);

	अगर (!skb_queue_empty(&frames)) अणु
		काष्ठा ieee80211_event event = अणु
			.type = BA_FRAME_TIMEOUT,
			.u.ba.tid = tid,
			.u.ba.sta = &sta->sta,
		पूर्ण;
		drv_event_callback(rx.local, rx.sdata, &event);
	पूर्ण

	ieee80211_rx_handlers(&rx, &frames);
पूर्ण

व्योम ieee80211_mark_rx_ba_filtered_frames(काष्ठा ieee80211_sta *pubsta, u8 tid,
					  u16 ssn, u64 filtered,
					  u16 received_mpdus)
अणु
	काष्ठा sta_info *sta;
	काष्ठा tid_ampdu_rx *tid_agg_rx;
	काष्ठा sk_buff_head frames;
	काष्ठा ieee80211_rx_data rx = अणु
		/* This is OK -- must be QoS data frame */
		.security_idx = tid,
		.seqno_idx = tid,
	पूर्ण;
	पूर्णांक i, dअगरf;

	अगर (WARN_ON(!pubsta || tid >= IEEE80211_NUM_TIDS))
		वापस;

	__skb_queue_head_init(&frames);

	sta = container_of(pubsta, काष्ठा sta_info, sta);

	rx.sta = sta;
	rx.sdata = sta->sdata;
	rx.local = sta->local;

	rcu_पढ़ो_lock();
	tid_agg_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
	अगर (!tid_agg_rx)
		जाओ out;

	spin_lock_bh(&tid_agg_rx->reorder_lock);

	अगर (received_mpdus >= IEEE80211_SN_MODULO >> 1) अणु
		पूर्णांक release;

		/* release all frames in the reorder buffer */
		release = (tid_agg_rx->head_seq_num + tid_agg_rx->buf_size) %
			   IEEE80211_SN_MODULO;
		ieee80211_release_reorder_frames(sta->sdata, tid_agg_rx,
						 release, &frames);
		/* update ssn to match received ssn */
		tid_agg_rx->head_seq_num = ssn;
	पूर्ण अन्यथा अणु
		ieee80211_release_reorder_frames(sta->sdata, tid_agg_rx, ssn,
						 &frames);
	पूर्ण

	/* handle the हाल that received ssn is behind the mac ssn.
	 * it can be tid_agg_rx->buf_size behind and still be valid */
	dअगरf = (tid_agg_rx->head_seq_num - ssn) & IEEE80211_SN_MASK;
	अगर (dअगरf >= tid_agg_rx->buf_size) अणु
		tid_agg_rx->reorder_buf_filtered = 0;
		जाओ release;
	पूर्ण
	filtered = filtered >> dअगरf;
	ssn += dअगरf;

	/* update biपंचांगap */
	क्रम (i = 0; i < tid_agg_rx->buf_size; i++) अणु
		पूर्णांक index = (ssn + i) % tid_agg_rx->buf_size;

		tid_agg_rx->reorder_buf_filtered &= ~BIT_ULL(index);
		अगर (filtered & BIT_ULL(i))
			tid_agg_rx->reorder_buf_filtered |= BIT_ULL(index);
	पूर्ण

	/* now process also frames that the filter marking released */
	ieee80211_sta_reorder_release(sta->sdata, tid_agg_rx, &frames);

release:
	spin_unlock_bh(&tid_agg_rx->reorder_lock);

	ieee80211_rx_handlers(&rx, &frames);

 out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_mark_rx_ba_filtered_frames);

/* मुख्य receive path */

अटल bool ieee80211_accept_frame(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u8 *bssid = ieee80211_get_bssid(hdr, skb->len, sdata->vअगर.type);
	bool multicast = is_multicast_ether_addr(hdr->addr1) ||
			 ieee80211_is_s1g_beacon(hdr->frame_control);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (!bssid && !sdata->u.mgd.use_4addr)
			वापस false;
		अगर (ieee80211_is_robust_mgmt_frame(skb) && !rx->sta)
			वापस false;
		अगर (multicast)
			वापस true;
		वापस ether_addr_equal(sdata->vअगर.addr, hdr->addr1);
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!bssid)
			वापस false;
		अगर (ether_addr_equal(sdata->vअगर.addr, hdr->addr2) ||
		    ether_addr_equal(sdata->u.ibss.bssid, hdr->addr2))
			वापस false;
		अगर (ieee80211_is_beacon(hdr->frame_control))
			वापस true;
		अगर (!ieee80211_bssid_match(bssid, sdata->u.ibss.bssid))
			वापस false;
		अगर (!multicast &&
		    !ether_addr_equal(sdata->vअगर.addr, hdr->addr1))
			वापस false;
		अगर (!rx->sta) अणु
			पूर्णांक rate_idx;
			अगर (status->encoding != RX_ENC_LEGACY)
				rate_idx = 0; /* TODO: HT/VHT rates */
			अन्यथा
				rate_idx = status->rate_idx;
			ieee80211_ibss_rx_no_sta(sdata, bssid, hdr->addr2,
						 BIT(rate_idx));
		पूर्ण
		वापस true;
	हाल NL80211_IFTYPE_OCB:
		अगर (!bssid)
			वापस false;
		अगर (!ieee80211_is_data_present(hdr->frame_control))
			वापस false;
		अगर (!is_broadcast_ether_addr(bssid))
			वापस false;
		अगर (!multicast &&
		    !ether_addr_equal(sdata->dev->dev_addr, hdr->addr1))
			वापस false;
		अगर (!rx->sta) अणु
			पूर्णांक rate_idx;
			अगर (status->encoding != RX_ENC_LEGACY)
				rate_idx = 0; /* TODO: HT rates */
			अन्यथा
				rate_idx = status->rate_idx;
			ieee80211_ocb_rx_no_sta(sdata, bssid, hdr->addr2,
						BIT(rate_idx));
		पूर्ण
		वापस true;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (ether_addr_equal(sdata->vअगर.addr, hdr->addr2))
			वापस false;
		अगर (multicast)
			वापस true;
		वापस ether_addr_equal(sdata->vअगर.addr, hdr->addr1);
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_AP:
		अगर (!bssid)
			वापस ether_addr_equal(sdata->vअगर.addr, hdr->addr1);

		अगर (!ieee80211_bssid_match(bssid, sdata->vअगर.addr)) अणु
			/*
			 * Accept खुला action frames even when the
			 * BSSID करोesn't match, this is used क्रम P2P
			 * and location updates. Note that mac80211
			 * itself never looks at these frames.
			 */
			अगर (!multicast &&
			    !ether_addr_equal(sdata->vअगर.addr, hdr->addr1))
				वापस false;
			अगर (ieee80211_is_खुला_action(hdr, skb->len))
				वापस true;
			वापस ieee80211_is_beacon(hdr->frame_control);
		पूर्ण

		अगर (!ieee80211_has_tods(hdr->frame_control)) अणु
			/* ignore data frames to TDLS-peers */
			अगर (ieee80211_is_data(hdr->frame_control))
				वापस false;
			/* ignore action frames to TDLS-peers */
			अगर (ieee80211_is_action(hdr->frame_control) &&
			    !is_broadcast_ether_addr(bssid) &&
			    !ether_addr_equal(bssid, hdr->addr1))
				वापस false;
		पूर्ण

		/*
		 * 802.11-2016 Table 9-26 says that क्रम data frames, A1 must be
		 * the BSSID - we've checked that alपढ़ोy but may have accepted
		 * the wildcard (ff:ff:ff:ff:ff:ff).
		 *
		 * It also says:
		 *	The BSSID of the Data frame is determined as follows:
		 *	a) If the STA is contained within an AP or is associated
		 *	   with an AP, the BSSID is the address currently in use
		 *	   by the STA contained in the AP.
		 *
		 * So we should not accept data frames with an address that's
		 * multicast.
		 *
		 * Accepting it also खोलोs a security problem because stations
		 * could encrypt it with the GTK and inject traffic that way.
		 */
		अगर (ieee80211_is_data(hdr->frame_control) && multicast)
			वापस false;

		वापस true;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस ieee80211_is_खुला_action(hdr, skb->len) ||
		       ieee80211_is_probe_req(hdr->frame_control) ||
		       ieee80211_is_probe_resp(hdr->frame_control) ||
		       ieee80211_is_beacon(hdr->frame_control);
	हाल NL80211_IFTYPE_न_अंक:
		/* Currently no frames on न_अंक पूर्णांकerface are allowed */
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

व्योम ieee80211_check_fast_rx(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_key *key;
	काष्ठा ieee80211_fast_rx fastrx = अणु
		.dev = sdata->dev,
		.vअगर_type = sdata->vअगर.type,
		.control_port_protocol = sdata->control_port_protocol,
	पूर्ण, *old, *new = शून्य;
	bool set_offload = false;
	bool assign = false;
	bool offload;

	/* use sparse to check that we करोn't वापस without updating */
	__acquire(check_fast_rx);

	BUILD_BUG_ON(माप(fastrx.rfc1042_hdr) != माप(rfc1042_header));
	BUILD_BUG_ON(माप(fastrx.rfc1042_hdr) != ETH_ALEN);
	ether_addr_copy(fastrx.rfc1042_hdr, rfc1042_header);
	ether_addr_copy(fastrx.vअगर_addr, sdata->vअगर.addr);

	fastrx.uses_rss = ieee80211_hw_check(&local->hw, USES_RSS);

	/* fast-rx करोesn't करो reordering */
	अगर (ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION) &&
	    !ieee80211_hw_check(&local->hw, SUPPORTS_REORDERING_BUFFER))
		जाओ clear;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (sta->sta.tdls) अणु
			fastrx.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr1);
			fastrx.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr2);
			fastrx.expected_ds_bits = 0;
		पूर्ण अन्यथा अणु
			fastrx.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr1);
			fastrx.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
			fastrx.expected_ds_bits =
				cpu_to_le16(IEEE80211_FCTL_FROMDS);
		पूर्ण

		अगर (sdata->u.mgd.use_4addr && !sta->sta.tdls) अणु
			fastrx.expected_ds_bits |=
				cpu_to_le16(IEEE80211_FCTL_TODS);
			fastrx.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
			fastrx.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr4);
		पूर्ण

		अगर (!sdata->u.mgd.घातersave)
			अवरोध;

		/* software घातersave is a huge mess, aव्योम all of it */
		अगर (ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK))
			जाओ clear;
		अगर (ieee80211_hw_check(&local->hw, SUPPORTS_PS) &&
		    !ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS))
			जाओ clear;
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_AP:
		/* parallel-rx requires this, at least with calls to
		 * ieee80211_sta_ps_transition()
		 */
		अगर (!ieee80211_hw_check(&local->hw, AP_LINK_PS))
			जाओ clear;
		fastrx.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
		fastrx.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr2);
		fastrx.expected_ds_bits = cpu_to_le16(IEEE80211_FCTL_TODS);

		fastrx.पूर्णांकernal_क्रमward =
			!(sdata->flags & IEEE80211_SDATA_DONT_BRIDGE_PACKETS) &&
			(sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN ||
			 !sdata->u.vlan.sta);

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN &&
		    sdata->u.vlan.sta) अणु
			fastrx.expected_ds_bits |=
				cpu_to_le16(IEEE80211_FCTL_FROMDS);
			fastrx.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr4);
			fastrx.पूर्णांकernal_क्रमward = 0;
		पूर्ण

		अवरोध;
	शेष:
		जाओ clear;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_AUTHORIZED))
		जाओ clear;

	rcu_पढ़ो_lock();
	key = rcu_dereference(sta->ptk[sta->ptk_idx]);
	अगर (!key)
		key = rcu_dereference(sdata->शेष_unicast_key);
	अगर (key) अणु
		चयन (key->conf.cipher) अणु
		हाल WLAN_CIPHER_SUITE_TKIP:
			/* we करोn't want to deal with MMIC in fast-rx */
			जाओ clear_rcu;
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			अवरोध;
		शेष:
			/* We also करोn't want to deal with
			 * WEP or cipher scheme.
			 */
			जाओ clear_rcu;
		पूर्ण

		fastrx.key = true;
		fastrx.icv_len = key->conf.icv_len;
	पूर्ण

	assign = true;
 clear_rcu:
	rcu_पढ़ो_unlock();
 clear:
	__release(check_fast_rx);

	अगर (assign)
		new = kmemdup(&fastrx, माप(fastrx), GFP_KERNEL);

	offload = assign &&
		  (sdata->vअगर.offload_flags & IEEE80211_OFFLOAD_DECAP_ENABLED);

	अगर (offload)
		set_offload = !test_and_set_sta_flag(sta, WLAN_STA_DECAP_OFFLOAD);
	अन्यथा
		set_offload = test_and_clear_sta_flag(sta, WLAN_STA_DECAP_OFFLOAD);

	अगर (set_offload)
		drv_sta_set_decap_offload(local, sdata, &sta->sta, assign);

	spin_lock_bh(&sta->lock);
	old = rcu_dereference_रक्षित(sta->fast_rx, true);
	rcu_assign_poपूर्णांकer(sta->fast_rx, new);
	spin_unlock_bh(&sta->lock);

	अगर (old)
		kमुक्त_rcu(old, rcu_head);
पूर्ण

व्योम ieee80211_clear_fast_rx(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_fast_rx *old;

	spin_lock_bh(&sta->lock);
	old = rcu_dereference_रक्षित(sta->fast_rx, true);
	RCU_INIT_POINTER(sta->fast_rx, शून्य);
	spin_unlock_bh(&sta->lock);

	अगर (old)
		kमुक्त_rcu(old, rcu_head);
पूर्ण

व्योम __ieee80211_check_fast_rx_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	lockdep_निश्चित_held(&local->sta_mtx);

	list_क्रम_each_entry(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata &&
		    (!sta->sdata->bss || sta->sdata->bss != sdata->bss))
			जारी;
		ieee80211_check_fast_rx(sta);
	पूर्ण
पूर्ण

व्योम ieee80211_check_fast_rx_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	mutex_lock(&local->sta_mtx);
	__ieee80211_check_fast_rx_अगरace(sdata);
	mutex_unlock(&local->sta_mtx);
पूर्ण

अटल व्योम ieee80211_rx_8023(काष्ठा ieee80211_rx_data *rx,
			      काष्ठा ieee80211_fast_rx *fast_rx,
			      पूर्णांक orig_len)
अणु
	काष्ठा ieee80211_sta_rx_stats *stats;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	काष्ठा sta_info *sta = rx->sta;
	काष्ठा sk_buff *skb = rx->skb;
	व्योम *sa = skb->data + ETH_ALEN;
	व्योम *da = skb->data;

	stats = &sta->rx_stats;
	अगर (fast_rx->uses_rss)
		stats = this_cpu_ptr(sta->pcpu_rx_stats);

	/* statistics part of ieee80211_rx_h_sta_process() */
	अगर (!(status->flag & RX_FLAG_NO_SIGNAL_VAL)) अणु
		stats->last_संकेत = status->संकेत;
		अगर (!fast_rx->uses_rss)
			ewma_संकेत_add(&sta->rx_stats_avg.संकेत,
					-status->संकेत);
	पूर्ण

	अगर (status->chains) अणु
		पूर्णांक i;

		stats->chains = status->chains;
		क्रम (i = 0; i < ARRAY_SIZE(status->chain_संकेत); i++) अणु
			पूर्णांक संकेत = status->chain_संकेत[i];

			अगर (!(status->chains & BIT(i)))
				जारी;

			stats->chain_संकेत_last[i] = संकेत;
			अगर (!fast_rx->uses_rss)
				ewma_संकेत_add(&sta->rx_stats_avg.chain_संकेत[i],
						-संकेत);
		पूर्ण
	पूर्ण
	/* end of statistics */

	stats->last_rx = jअगरfies;
	stats->last_rate = sta_stats_encode_rate(status);

	stats->fragments++;
	stats->packets++;

	skb->dev = fast_rx->dev;

	dev_sw_netstats_rx_add(fast_rx->dev, skb->len);

	/* The seqno index has the same property as needed
	 * क्रम the rx_msdu field, i.e. it is IEEE80211_NUM_TIDS
	 * क्रम non-QoS-data frames. Here we know it's a data
	 * frame, so count MSDUs.
	 */
	u64_stats_update_begin(&stats->syncp);
	stats->msdu[rx->seqno_idx]++;
	stats->bytes += orig_len;
	u64_stats_update_end(&stats->syncp);

	अगर (fast_rx->पूर्णांकernal_क्रमward) अणु
		काष्ठा sk_buff *xmit_skb = शून्य;
		अगर (is_multicast_ether_addr(da)) अणु
			xmit_skb = skb_copy(skb, GFP_ATOMIC);
		पूर्ण अन्यथा अगर (!ether_addr_equal(da, sa) &&
			   sta_info_get(rx->sdata, da)) अणु
			xmit_skb = skb;
			skb = शून्य;
		पूर्ण

		अगर (xmit_skb) अणु
			/*
			 * Send to wireless media and increase priority by 256
			 * to keep the received priority instead of
			 * reclassअगरying the frame (see cfg80211_classअगरy8021d).
			 */
			xmit_skb->priority += 256;
			xmit_skb->protocol = htons(ETH_P_802_3);
			skb_reset_network_header(xmit_skb);
			skb_reset_mac_header(xmit_skb);
			dev_queue_xmit(xmit_skb);
		पूर्ण

		अगर (!skb)
			वापस;
	पूर्ण

	/* deliver to local stack */
	skb->protocol = eth_type_trans(skb, fast_rx->dev);
	स_रखो(skb->cb, 0, माप(skb->cb));
	अगर (rx->list)
		list_add_tail(&skb->list, rx->list);
	अन्यथा
		netअगर_receive_skb(skb);

पूर्ण

अटल bool ieee80211_invoke_fast_rx(काष्ठा ieee80211_rx_data *rx,
				     काष्ठा ieee80211_fast_rx *fast_rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा sta_info *sta = rx->sta;
	पूर्णांक orig_len = skb->len;
	पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);
	पूर्णांक snap_offs = hdrlen;
	काष्ठा अणु
		u8 snap[माप(rfc1042_header)];
		__be16 proto;
	पूर्ण *payload __aligned(2);
	काष्ठा अणु
		u8 da[ETH_ALEN];
		u8 sa[ETH_ALEN];
	पूर्ण addrs __aligned(2);
	काष्ठा ieee80211_sta_rx_stats *stats = &sta->rx_stats;

	/* क्रम parallel-rx, we need to have DUP_VALIDATED, otherwise we ग_लिखो
	 * to a common data काष्ठाure; drivers can implement that per queue
	 * but we करोn't have that inक्रमmation in mac80211
	 */
	अगर (!(status->flag & RX_FLAG_DUP_VALIDATED))
		वापस false;

#घोषणा FAST_RX_CRYPT_FLAGS	(RX_FLAG_PN_VALIDATED | RX_FLAG_DECRYPTED)

	/* If using encryption, we also need to have:
	 *  - PN_VALIDATED: similar, but the implementation is tricky
	 *  - DECRYPTED: necessary क्रम PN_VALIDATED
	 */
	अगर (fast_rx->key &&
	    (status->flag & FAST_RX_CRYPT_FLAGS) != FAST_RX_CRYPT_FLAGS)
		वापस false;

	अगर (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		वापस false;

	अगर (unlikely(ieee80211_is_frag(hdr)))
		वापस false;

	/* Since our पूर्णांकerface address cannot be multicast, this
	 * implicitly also rejects multicast frames without the
	 * explicit check.
	 *
	 * We shouldn't get any *data* frames not addressed to us
	 * (AP mode will accept multicast *management* frames), but
	 * punting here will make it go through the full checks in
	 * ieee80211_accept_frame().
	 */
	अगर (!ether_addr_equal(fast_rx->vअगर_addr, hdr->addr1))
		वापस false;

	अगर ((hdr->frame_control & cpu_to_le16(IEEE80211_FCTL_FROMDS |
					      IEEE80211_FCTL_TODS)) !=
	    fast_rx->expected_ds_bits)
		वापस false;

	/* assign the key to drop unencrypted frames (later)
	 * and strip the IV/MIC अगर necessary
	 */
	अगर (fast_rx->key && !(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		/* GCMP header length is the same */
		snap_offs += IEEE80211_CCMP_HDR_LEN;
	पूर्ण

	अगर (!(status->rx_flags & IEEE80211_RX_AMSDU)) अणु
		अगर (!pskb_may_pull(skb, snap_offs + माप(*payload)))
			जाओ drop;

		payload = (व्योम *)(skb->data + snap_offs);

		अगर (!ether_addr_equal(payload->snap, fast_rx->rfc1042_hdr))
			वापस false;

		/* Don't handle these here since they require special code.
		 * Accept AARP and IPX even though they should come with a
		 * bridge-tunnel header - but अगर we get them this way then
		 * there's little poपूर्णांक in discarding them.
		 */
		अगर (unlikely(payload->proto == cpu_to_be16(ETH_P_TDLS) ||
			     payload->proto == fast_rx->control_port_protocol))
			वापस false;
	पूर्ण

	/* after this poपूर्णांक, करोn't punt to the slowpath! */

	अगर (rx->key && !(status->flag & RX_FLAG_MIC_STRIPPED) &&
	    pskb_trim(skb, skb->len - fast_rx->icv_len))
		जाओ drop;

	अगर (rx->key && !ieee80211_has_रक्षित(hdr->frame_control))
		जाओ drop;

	अगर (status->rx_flags & IEEE80211_RX_AMSDU) अणु
		अगर (__ieee80211_rx_h_amsdu(rx, snap_offs - hdrlen) !=
		    RX_QUEUED)
			जाओ drop;

		वापस true;
	पूर्ण

	/* करो the header conversion - first grab the addresses */
	ether_addr_copy(addrs.da, skb->data + fast_rx->da_offs);
	ether_addr_copy(addrs.sa, skb->data + fast_rx->sa_offs);
	/* हटाओ the SNAP but leave the ethertype */
	skb_pull(skb, snap_offs + माप(rfc1042_header));
	/* push the addresses in front */
	स_नकल(skb_push(skb, माप(addrs)), &addrs, माप(addrs));

	ieee80211_rx_8023(rx, fast_rx, orig_len);

	वापस true;
 drop:
	dev_kमुक्त_skb(skb);
	अगर (fast_rx->uses_rss)
		stats = this_cpu_ptr(sta->pcpu_rx_stats);

	stats->dropped++;
	वापस true;
पूर्ण

/*
 * This function वापसs whether or not the SKB
 * was destined क्रम RX processing or not, which,
 * अगर consume is true, is equivalent to whether
 * or not the skb was consumed.
 */
अटल bool ieee80211_prepare_and_rx_handle(काष्ठा ieee80211_rx_data *rx,
					    काष्ठा sk_buff *skb, bool consume)
अणु
	काष्ठा ieee80211_local *local = rx->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = rx->sdata;

	rx->skb = skb;

	/* See अगर we can करो fast-rx; अगर we have to copy we alपढ़ोy lost,
	 * so punt in that हाल. We should never have to deliver a data
	 * frame to multiple पूर्णांकerfaces anyway.
	 *
	 * We skip the ieee80211_accept_frame() call and करो the necessary
	 * checking inside ieee80211_invoke_fast_rx().
	 */
	अगर (consume && rx->sta) अणु
		काष्ठा ieee80211_fast_rx *fast_rx;

		fast_rx = rcu_dereference(rx->sta->fast_rx);
		अगर (fast_rx && ieee80211_invoke_fast_rx(rx, fast_rx))
			वापस true;
	पूर्ण

	अगर (!ieee80211_accept_frame(rx))
		वापस false;

	अगर (!consume) अणु
		skb = skb_copy(skb, GFP_ATOMIC);
		अगर (!skb) अणु
			अगर (net_ratelimit())
				wiphy_debug(local->hw.wiphy,
					"failed to copy skb for %s\n",
					sdata->name);
			वापस true;
		पूर्ण

		rx->skb = skb;
	पूर्ण

	ieee80211_invoke_rx_handlers(rx);
	वापस true;
पूर्ण

अटल व्योम __ieee80211_rx_handle_8023(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_sta *pubsta,
				       काष्ठा sk_buff *skb,
				       काष्ठा list_head *list)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_fast_rx *fast_rx;
	काष्ठा ieee80211_rx_data rx;

	स_रखो(&rx, 0, माप(rx));
	rx.skb = skb;
	rx.local = local;
	rx.list = list;

	I802_DEBUG_INC(local->करोt11ReceivedFragmentCount);

	/* drop frame अगर too लघु क्रम header */
	अगर (skb->len < माप(काष्ठा ethhdr))
		जाओ drop;

	अगर (!pubsta)
		जाओ drop;

	rx.sta = container_of(pubsta, काष्ठा sta_info, sta);
	rx.sdata = rx.sta->sdata;

	fast_rx = rcu_dereference(rx.sta->fast_rx);
	अगर (!fast_rx)
		जाओ drop;

	ieee80211_rx_8023(&rx, fast_rx, skb->len);
	वापस;

drop:
	dev_kमुक्त_skb(skb);
पूर्ण

/*
 * This is the actual Rx frames handler. as it beदीर्घs to Rx path it must
 * be called with rcu_पढ़ो_lock protection.
 */
अटल व्योम __ieee80211_rx_handle_packet(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_sta *pubsta,
					 काष्ठा sk_buff *skb,
					 काष्ठा list_head *list)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_hdr *hdr;
	__le16 fc;
	काष्ठा ieee80211_rx_data rx;
	काष्ठा ieee80211_sub_अगर_data *prev;
	काष्ठा rhlist_head *पंचांगp;
	पूर्णांक err = 0;

	fc = ((काष्ठा ieee80211_hdr *)skb->data)->frame_control;
	स_रखो(&rx, 0, माप(rx));
	rx.skb = skb;
	rx.local = local;
	rx.list = list;

	अगर (ieee80211_is_data(fc) || ieee80211_is_mgmt(fc))
		I802_DEBUG_INC(local->करोt11ReceivedFragmentCount);

	अगर (ieee80211_is_mgmt(fc)) अणु
		/* drop frame अगर too लघु क्रम header */
		अगर (skb->len < ieee80211_hdrlen(fc))
			err = -ENOBUFS;
		अन्यथा
			err = skb_linearize(skb);
	पूर्ण अन्यथा अणु
		err = !pskb_may_pull(skb, ieee80211_hdrlen(fc));
	पूर्ण

	अगर (err) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	ieee80211_parse_qos(&rx);
	ieee80211_verअगरy_alignment(&rx);

	अगर (unlikely(ieee80211_is_probe_resp(hdr->frame_control) ||
		     ieee80211_is_beacon(hdr->frame_control) ||
		     ieee80211_is_s1g_beacon(hdr->frame_control)))
		ieee80211_scan_rx(local, skb);

	अगर (ieee80211_is_data(fc)) अणु
		काष्ठा sta_info *sta, *prev_sta;

		अगर (pubsta) अणु
			rx.sta = container_of(pubsta, काष्ठा sta_info, sta);
			rx.sdata = rx.sta->sdata;
			अगर (ieee80211_prepare_and_rx_handle(&rx, skb, true))
				वापस;
			जाओ out;
		पूर्ण

		prev_sta = शून्य;

		क्रम_each_sta_info(local, hdr->addr2, sta, पंचांगp) अणु
			अगर (!prev_sta) अणु
				prev_sta = sta;
				जारी;
			पूर्ण

			rx.sta = prev_sta;
			rx.sdata = prev_sta->sdata;
			ieee80211_prepare_and_rx_handle(&rx, skb, false);

			prev_sta = sta;
		पूर्ण

		अगर (prev_sta) अणु
			rx.sta = prev_sta;
			rx.sdata = prev_sta->sdata;

			अगर (ieee80211_prepare_and_rx_handle(&rx, skb, true))
				वापस;
			जाओ out;
		पूर्ण
	पूर्ण

	prev = शून्य;

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR ||
		    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			जारी;

		/*
		 * frame is destined क्रम this पूर्णांकerface, but अगर it's
		 * not also क्रम the previous one we handle that after
		 * the loop to aव्योम copying the SKB once too much
		 */

		अगर (!prev) अणु
			prev = sdata;
			जारी;
		पूर्ण

		rx.sta = sta_info_get_bss(prev, hdr->addr2);
		rx.sdata = prev;
		ieee80211_prepare_and_rx_handle(&rx, skb, false);

		prev = sdata;
	पूर्ण

	अगर (prev) अणु
		rx.sta = sta_info_get_bss(prev, hdr->addr2);
		rx.sdata = prev;

		अगर (ieee80211_prepare_and_rx_handle(&rx, skb, true))
			वापस;
	पूर्ण

 out:
	dev_kमुक्त_skb(skb);
पूर्ण

/*
 * This is the receive path handler. It is called by a low level driver when an
 * 802.11 MPDU is received from the hardware.
 */
व्योम ieee80211_rx_list(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *pubsta,
		       काष्ठा sk_buff *skb, काष्ठा list_head *list)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_rate *rate = शून्य;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);

	WARN_ON_ONCE(softirq_count() == 0);

	अगर (WARN_ON(status->band >= NUM_NL80211_BANDS))
		जाओ drop;

	sband = local->hw.wiphy->bands[status->band];
	अगर (WARN_ON(!sband))
		जाओ drop;

	/*
	 * If we're suspending, it is possible although not too likely
	 * that we'd be receiving frames after having alपढ़ोy partially
	 * quiesced the stack. We can't process such frames then since
	 * that might, क्रम example, cause stations to be added or other
	 * driver callbacks be invoked.
	 */
	अगर (unlikely(local->quiescing || local->suspended))
		जाओ drop;

	/* We might be during a HW reconfig, prevent Rx क्रम the same reason */
	अगर (unlikely(local->in_reconfig))
		जाओ drop;

	/*
	 * The same happens when we're not even started,
	 * but that's worth a warning.
	 */
	अगर (WARN_ON(!local->started))
		जाओ drop;

	अगर (likely(!(status->flag & RX_FLAG_FAILED_PLCP_CRC))) अणु
		/*
		 * Validate the rate, unless a PLCP error means that
		 * we probably can't have a valid rate here anyway.
		 */

		चयन (status->encoding) अणु
		हाल RX_ENC_HT:
			/*
			 * rate_idx is MCS index, which can be [0-76]
			 * as करोcumented on:
			 *
			 * https://wireless.wiki.kernel.org/en/developers/Documentation/ieee80211/802.11n
			 *
			 * Anything अन्यथा would be some sort of driver or
			 * hardware error. The driver should catch hardware
			 * errors.
			 */
			अगर (WARN(status->rate_idx > 76,
				 "Rate marked as an HT rate but passed "
				 "status->rate_idx is not "
				 "an MCS index [0-76]: %d (0x%02x)\n",
				 status->rate_idx,
				 status->rate_idx))
				जाओ drop;
			अवरोध;
		हाल RX_ENC_VHT:
			अगर (WARN_ONCE(status->rate_idx > 9 ||
				      !status->nss ||
				      status->nss > 8,
				      "Rate marked as a VHT rate but data is invalid: MCS: %d, NSS: %d\n",
				      status->rate_idx, status->nss))
				जाओ drop;
			अवरोध;
		हाल RX_ENC_HE:
			अगर (WARN_ONCE(status->rate_idx > 11 ||
				      !status->nss ||
				      status->nss > 8,
				      "Rate marked as an HE rate but data is invalid: MCS: %d, NSS: %d\n",
				      status->rate_idx, status->nss))
				जाओ drop;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			fallthrough;
		हाल RX_ENC_LEGACY:
			अगर (WARN_ON(status->rate_idx >= sband->n_bitrates))
				जाओ drop;
			rate = &sband->bitrates[status->rate_idx];
		पूर्ण
	पूर्ण

	status->rx_flags = 0;

	kcov_remote_start_common(skb_get_kcov_handle(skb));

	/*
	 * Frames with failed FCS/PLCP checksum are not वापसed,
	 * all other frames are वापसed without radiotap header
	 * अगर it was previously present.
	 * Also, frames with less than 16 bytes are dropped.
	 */
	अगर (!(status->flag & RX_FLAG_8023))
		skb = ieee80211_rx_monitor(local, skb, rate);
	अगर (skb) अणु
		ieee80211_tpt_led_trig_rx(local,
					  ((काष्ठा ieee80211_hdr *)skb->data)->frame_control,
					  skb->len);

		अगर (status->flag & RX_FLAG_8023)
			__ieee80211_rx_handle_8023(hw, pubsta, skb, list);
		अन्यथा
			__ieee80211_rx_handle_packet(hw, pubsta, skb, list);
	पूर्ण

	kcov_remote_stop();
	वापस;
 drop:
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(ieee80211_rx_list);

व्योम ieee80211_rx_napi(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *pubsta,
		       काष्ठा sk_buff *skb, काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff *पंचांगp;
	LIST_HEAD(list);


	/*
	 * key references and भव पूर्णांकerfaces are रक्षित using RCU
	 * and this requires that we are in a पढ़ो-side RCU section during
	 * receive processing
	 */
	rcu_पढ़ो_lock();
	ieee80211_rx_list(hw, pubsta, skb, &list);
	rcu_पढ़ो_unlock();

	अगर (!napi) अणु
		netअगर_receive_skb_list(&list);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(skb, पंचांगp, &list, list) अणु
		skb_list_del_init(skb);
		napi_gro_receive(napi, skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_rx_napi);

/* This is a version of the rx handler that can be called from hard irq
 * context. Post the skb on the queue and schedule the tasklet */
व्योम ieee80211_rx_irqsafe(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	BUILD_BUG_ON(माप(काष्ठा ieee80211_rx_status) > माप(skb->cb));

	skb->pkt_type = IEEE80211_RX_MSG;
	skb_queue_tail(&local->skb_queue, skb);
	tasklet_schedule(&local->tasklet);
पूर्ण
EXPORT_SYMBOL(ieee80211_rx_irqsafe);
