<शैली गुरु>
/*
 * Copyright (c) 2009-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Module क्रम common driver code between ath9k and ath9k_htc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "common.h"

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Shared library for Atheros wireless 802.11n LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

/* Assumes you've alपढ़ोy करोne the endian to CPU conversion */
bool ath9k_cmn_rx_accept(काष्ठा ath_common *common,
			 काष्ठा ieee80211_hdr *hdr,
			 काष्ठा ieee80211_rx_status *rxs,
			 काष्ठा ath_rx_status *rx_stats,
			 bool *decrypt_error,
			 अचिन्हित पूर्णांक rxfilter)
अणु
	काष्ठा ath_hw *ah = common->ah;
	bool is_mc, is_valid_tkip, strip_mic, mic_error;
	__le16 fc;

	fc = hdr->frame_control;

	is_mc = !!is_multicast_ether_addr(hdr->addr1);
	is_valid_tkip = rx_stats->rs_keyix != ATH9K_RXKEYIX_INVALID &&
		test_bit(rx_stats->rs_keyix, common->tkip_keymap);
	strip_mic = is_valid_tkip && ieee80211_is_data(fc) &&
		ieee80211_has_रक्षित(fc) &&
		!(rx_stats->rs_status &
		(ATH9K_RXERR_DECRYPT | ATH9K_RXERR_CRC | ATH9K_RXERR_MIC |
		 ATH9K_RXERR_KEYMISS));

	/*
	 * Key miss events are only relevant क्रम pairwise keys where the
	 * descriptor करोes contain a valid key index. This has been observed
	 * mostly with CCMP encryption.
	 */
	अगर (rx_stats->rs_keyix == ATH9K_RXKEYIX_INVALID ||
	    !test_bit(rx_stats->rs_keyix, common->ccmp_keymap))
		rx_stats->rs_status &= ~ATH9K_RXERR_KEYMISS;

	mic_error = is_valid_tkip && !ieee80211_is_ctl(fc) &&
		!ieee80211_has_morefrags(fc) &&
		!(le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG) &&
		(rx_stats->rs_status & ATH9K_RXERR_MIC);

	/*
	 * The rx_stats->rs_status will not be set until the end of the
	 * chained descriptors so it can be ignored अगर rs_more is set. The
	 * rs_more will be false at the last element of the chained
	 * descriptors.
	 */
	अगर (rx_stats->rs_status != 0) अणु
		u8 status_mask;

		अगर (rx_stats->rs_status & ATH9K_RXERR_CRC) अणु
			rxs->flag |= RX_FLAG_FAILED_FCS_CRC;
			mic_error = false;
		पूर्ण

		अगर ((rx_stats->rs_status & ATH9K_RXERR_DECRYPT) ||
		    (!is_mc && (rx_stats->rs_status & ATH9K_RXERR_KEYMISS))) अणु
			*decrypt_error = true;
			mic_error = false;
		पूर्ण


		/*
		 * Reject error frames with the exception of
		 * decryption and MIC failures. For monitor mode,
		 * we also ignore the CRC error.
		 */
		status_mask = ATH9K_RXERR_DECRYPT | ATH9K_RXERR_MIC |
			      ATH9K_RXERR_KEYMISS;

		अगर (ah->is_monitoring && (rxfilter & FIF_FCSFAIL))
			status_mask |= ATH9K_RXERR_CRC;

		अगर (rx_stats->rs_status & ~status_mask)
			वापस false;
	पूर्ण

	/*
	 * For unicast frames the MIC error bit can have false positives,
	 * so all MIC error reports need to be validated in software.
	 * False negatives are not common, so skip software verअगरication
	 * अगर the hardware considers the MIC valid.
	 */
	अगर (strip_mic)
		rxs->flag |= RX_FLAG_MMIC_STRIPPED;
	अन्यथा अगर (is_mc && mic_error)
		rxs->flag |= RX_FLAG_MMIC_ERROR;

	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_rx_accept);

व्योम ath9k_cmn_rx_skb_postprocess(काष्ठा ath_common *common,
				  काष्ठा sk_buff *skb,
				  काष्ठा ath_rx_status *rx_stats,
				  काष्ठा ieee80211_rx_status *rxs,
				  bool decrypt_error)
अणु
	काष्ठा ath_hw *ah = common->ah;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक hdrlen, padpos, padsize;
	u8 keyix;
	__le16 fc;

	/* see अगर any padding is करोne by the hw and हटाओ it */
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdrlen = ieee80211_get_hdrlen_from_skb(skb);
	fc = hdr->frame_control;
	padpos = ieee80211_hdrlen(fc);

	/* The MAC header is padded to have 32-bit boundary अगर the
	 * packet payload is non-zero. The general calculation क्रम
	 * padsize would take पूर्णांकo account odd header lengths:
	 * padsize = (4 - padpos % 4) % 4; However, since only
	 * even-length headers are used, padding can only be 0 or 2
	 * bytes and we can optimize this a bit. In addition, we must
	 * not try to हटाओ padding from लघु control frames that करो
	 * not have payload. */
	padsize = padpos & 3;
	अगर (padsize && skb->len>=padpos+padsize+FCS_LEN) अणु
		स_हटाओ(skb->data + padsize, skb->data, padpos);
		skb_pull(skb, padsize);
	पूर्ण

	keyix = rx_stats->rs_keyix;

	अगर (!(keyix == ATH9K_RXKEYIX_INVALID) && !decrypt_error &&
	    ieee80211_has_रक्षित(fc)) अणु
		rxs->flag |= RX_FLAG_DECRYPTED;
	पूर्ण अन्यथा अगर (ieee80211_has_रक्षित(fc)
		   && !decrypt_error && skb->len >= hdrlen + 4) अणु
		keyix = skb->data[hdrlen + 3] >> 6;

		अगर (test_bit(keyix, common->keymap))
			rxs->flag |= RX_FLAG_DECRYPTED;
	पूर्ण
	अगर (ah->sw_mgmt_crypto_rx &&
	    (rxs->flag & RX_FLAG_DECRYPTED) &&
	    ieee80211_is_mgmt(fc))
		/* Use software decrypt क्रम management frames. */
		rxs->flag &= ~RX_FLAG_DECRYPTED;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_rx_skb_postprocess);

पूर्णांक ath9k_cmn_process_rate(काष्ठा ath_common *common,
			   काष्ठा ieee80211_hw *hw,
			   काष्ठा ath_rx_status *rx_stats,
			   काष्ठा ieee80211_rx_status *rxs)
अणु
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_band band;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा ath_hw *ah = common->ah;

	band = ah->curchan->chan->band;
	sband = hw->wiphy->bands[band];

	अगर (IS_CHAN_QUARTER_RATE(ah->curchan))
		rxs->bw = RATE_INFO_BW_5;
	अन्यथा अगर (IS_CHAN_HALF_RATE(ah->curchan))
		rxs->bw = RATE_INFO_BW_10;

	अगर (rx_stats->rs_rate & 0x80) अणु
		/* HT rate */
		rxs->encoding = RX_ENC_HT;
		rxs->enc_flags |= rx_stats->enc_flags;
		rxs->bw = rx_stats->bw;
		rxs->rate_idx = rx_stats->rs_rate & 0x7f;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (sband->bitrates[i].hw_value == rx_stats->rs_rate) अणु
			rxs->rate_idx = i;
			वापस 0;
		पूर्ण
		अगर (sband->bitrates[i].hw_value_लघु == rx_stats->rs_rate) अणु
			rxs->enc_flags |= RX_ENC_FLAG_SHORTPRE;
			rxs->rate_idx = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_process_rate);

व्योम ath9k_cmn_process_rssi(काष्ठा ath_common *common,
			    काष्ठा ieee80211_hw *hw,
			    काष्ठा ath_rx_status *rx_stats,
			    काष्ठा ieee80211_rx_status *rxs)
अणु
	काष्ठा ath_hw *ah = common->ah;
	पूर्णांक last_rssi;
	पूर्णांक rssi = rx_stats->rs_rssi;
	पूर्णांक i, j;

	/*
	 * RSSI is not available क्रम subframes in an A-MPDU.
	 */
	अगर (rx_stats->rs_moreaggr) अणु
		rxs->flag |= RX_FLAG_NO_SIGNAL_VAL;
		वापस;
	पूर्ण

	/*
	 * Check अगर the RSSI क्रम the last subframe in an A-MPDU
	 * or an unaggregated frame is valid.
	 */
	अगर (rx_stats->rs_rssi == ATH9K_RSSI_BAD) अणु
		rxs->flag |= RX_FLAG_NO_SIGNAL_VAL;
		वापस;
	पूर्ण

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(rx_stats->rs_rssi_ctl); i++) अणु
		s8 rssi;

		अगर (!(ah->rxchainmask & BIT(i)))
			जारी;

		rssi = rx_stats->rs_rssi_ctl[i];
		अगर (rssi != ATH9K_RSSI_BAD) अणु
		    rxs->chains |= BIT(j);
		    rxs->chain_संकेत[j] = ah->noise + rssi;
		पूर्ण
		j++;
	पूर्ण

	/*
	 * Update Beacon RSSI, this is used by ANI.
	 */
	अगर (rx_stats->is_mybeacon &&
	    ((ah->opmode == NL80211_IFTYPE_STATION) ||
	     (ah->opmode == NL80211_IFTYPE_ADHOC))) अणु
		ATH_RSSI_LPF(common->last_rssi, rx_stats->rs_rssi);
		last_rssi = common->last_rssi;

		अगर (likely(last_rssi != ATH_RSSI_DUMMY_MARKER))
			rssi = ATH_EP_RND(last_rssi, ATH_RSSI_EP_MULTIPLIER);
		अगर (rssi < 0)
			rssi = 0;

		ah->stats.avgbrssi = rssi;
	पूर्ण

	rxs->संकेत = ah->noise + rx_stats->rs_rssi;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_process_rssi);

पूर्णांक ath9k_cmn_get_hw_crypto_keytype(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	अगर (tx_info->control.hw_key) अणु
		चयन (tx_info->control.hw_key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			वापस ATH9K_KEY_TYPE_WEP;
		हाल WLAN_CIPHER_SUITE_TKIP:
			वापस ATH9K_KEY_TYPE_TKIP;
		हाल WLAN_CIPHER_SUITE_CCMP:
			वापस ATH9K_KEY_TYPE_AES;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ATH9K_KEY_TYPE_CLEAR;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_get_hw_crypto_keytype);

/*
 * Update पूर्णांकernal channel flags.
 */
अटल व्योम ath9k_cmn_update_ichannel(काष्ठा ath9k_channel *ichan,
				      काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_channel *chan = chandef->chan;
	u16 flags = 0;

	ichan->channel = chan->center_freq;
	ichan->chan = chan;

	अगर (chan->band == NL80211_BAND_5GHZ)
		flags |= CHANNEL_5GHZ;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
		flags |= CHANNEL_QUARTER;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		flags |= CHANNEL_HALF;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		flags |= CHANNEL_HT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		अगर (chandef->center_freq1 > chandef->chan->center_freq)
			flags |= CHANNEL_HT40PLUS | CHANNEL_HT;
		अन्यथा
			flags |= CHANNEL_HT40MINUS | CHANNEL_HT;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	ichan->channelFlags = flags;
पूर्ण

/*
 * Get the पूर्णांकernal channel reference.
 */
काष्ठा ath9k_channel *ath9k_cmn_get_channel(काष्ठा ieee80211_hw *hw,
					    काष्ठा ath_hw *ah,
					    काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_channel *curchan = chandef->chan;
	काष्ठा ath9k_channel *channel;

	channel = &ah->channels[curchan->hw_value];
	ath9k_cmn_update_ichannel(channel, chandef);

	वापस channel;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_get_channel);

पूर्णांक ath9k_cmn_count_streams(अचिन्हित पूर्णांक chainmask, पूर्णांक max)
अणु
	पूर्णांक streams = 0;

	करो अणु
		अगर (++streams == max)
			अवरोध;
	पूर्ण जबतक ((chainmask = chainmask & (chainmask - 1)));

	वापस streams;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_count_streams);

व्योम ath9k_cmn_update_txघात(काष्ठा ath_hw *ah, u16 cur_txघात,
			    u16 new_txघात, u16 *txघातer)
अणु
	काष्ठा ath_regulatory *reg = ath9k_hw_regulatory(ah);

	अगर (ah->curchan && reg->घातer_limit != new_txघात)
		ath9k_hw_set_txघातerlimit(ah, new_txघात, false);

	/* पढ़ो back in हाल value is clamped */
	*txघातer = reg->max_घातer_level;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_update_txघात);

व्योम ath9k_cmn_init_crypto(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक i = 0;

	/* Get the hardware key cache size. */
	common->keymax = AR_KEYTABLE_SIZE;

	/*
	 * Check whether the separate key cache entries
	 * are required to handle both tx+rx MIC keys.
	 * With split mic keys the number of stations is limited
	 * to 27 otherwise 59.
	 */
	अगर (ah->misc_mode & AR_PCU_MIC_NEW_LOC_ENA)
		common->crypt_caps |= ATH_CRYPT_CAP_MIC_COMBINED;

	/*
	 * Reset the key cache since some parts करो not
	 * reset the contents on initial घातer up.
	 */
	क्रम (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_init_crypto);

अटल पूर्णांक __init ath9k_cmn_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(ath9k_cmn_init);

अटल व्योम __निकास ath9k_cmn_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(ath9k_cmn_निकास);
