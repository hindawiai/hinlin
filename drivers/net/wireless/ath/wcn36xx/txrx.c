<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "txrx.h"

अटल अंतरभूत पूर्णांक get_rssi0(काष्ठा wcn36xx_rx_bd *bd)
अणु
	वापस 100 - ((bd->phy_stat0 >> 24) & 0xff);
पूर्ण

काष्ठा wcn36xx_rate अणु
	u16 bitrate;
	u16 mcs_or_legacy_index;
	क्रमागत mac80211_rx_encoding encoding;
	क्रमागत mac80211_rx_encoding_flags encoding_flags;
	क्रमागत rate_info_bw bw;
पूर्ण;

अटल स्थिर काष्ठा wcn36xx_rate wcn36xx_rate_table[] = अणु
	/* 11b rates */
	अणु  10, 0, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  20, 1, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  55, 2, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 110, 3, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,

	/* 11b SP (लघु preamble) */
	अणु  10, 0, RX_ENC_LEGACY, RX_ENC_FLAG_SHORTPRE, RATE_INFO_BW_20 पूर्ण,
	अणु  20, 1, RX_ENC_LEGACY, RX_ENC_FLAG_SHORTPRE, RATE_INFO_BW_20 पूर्ण,
	अणु  55, 2, RX_ENC_LEGACY, RX_ENC_FLAG_SHORTPRE, RATE_INFO_BW_20 पूर्ण,
	अणु 110, 3, RX_ENC_LEGACY, RX_ENC_FLAG_SHORTPRE, RATE_INFO_BW_20 पूर्ण,

	/* 11ag */
	अणु  60, 4, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  90, 5, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 120, 6, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 180, 7, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 240, 8, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 360, 9, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 480, 10, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 540, 11, RX_ENC_LEGACY, 0, RATE_INFO_BW_20 पूर्ण,

	/* 11n */
	अणु  65, 0, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 130, 1, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 195, 2, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 260, 3, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 390, 4, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 520, 5, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 585, 6, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु 650, 7, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,

	/* 11n SGI */
	अणु  72, 0, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 144, 1, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 217, 2, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 289, 3, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 434, 4, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 578, 5, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 650, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु 722, 7, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,

	/* 11n GF (greenfield) */
	अणु  65, 0, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 130, 1, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 195, 2, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 260, 3, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 390, 4, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 520, 5, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 585, 6, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,
	अणु 650, 7, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_20 पूर्ण,

	/* 11n CB (channel bonding) */
	अणु 135, 0, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 270, 1, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 405, 2, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 540, 3, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 810, 4, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1080, 5, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1215, 6, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 7, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,

	/* 11n CB + SGI */
	अणु 150, 0, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 300, 1, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 450, 2, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 600, 3, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 900, 4, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1200, 5, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1500, 7, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11n GF + CB */
	अणु 135, 0, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 270, 1, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 405, 2, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 540, 3, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 810, 4, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 1080, 5, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 1215, 6, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 7, RX_ENC_HT, RX_ENC_FLAG_HT_GF, RATE_INFO_BW_40 पूर्ण,

	/* 11ac reserved indices */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 20 MHz 800ns GI MCS 0-8 */
	अणु   65, 0, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  130, 1, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  195, 2, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  260, 3, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  390, 4, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  520, 5, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  585, 6, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  650, 7, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,
	अणु  780, 8, RX_ENC_HT, 0, RATE_INFO_BW_20 पूर्ण,

	/* 11ac reserved indices */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 20 MHz 400ns SGI MCS 6-8 */
	अणु  655, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु  722, 7, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,
	अणु  866, 8, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_20 पूर्ण,

	/* 11ac reserved indices */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 40 MHz 800ns GI MCS 0-9 */
	अणु  135, 0, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु  270, 1, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु  405, 2, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु  540, 3, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु  810, 4, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1080, 5, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1215, 6, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 7, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 7, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1620, 8, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,
	अणु 1800, 9, RX_ENC_HT, 0, RATE_INFO_BW_40 पूर्ण,

	/* 11ac reserved indices */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 40 MHz 400ns SGI MCS 5-7 */
	अणु 1200, 5, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1500, 7, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac reserved index */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 40 MHz 400ns SGI MCS 5-7 */
	अणु 1800, 8, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 2000, 9, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac reserved index */
	अणु 1350, 6, RX_ENC_HT,  RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 80 MHz 800ns GI MCS 0-7 */
	अणु  292, 0, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु  585, 1, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु  877, 2, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 1170, 3, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 1755, 4, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 2340, 5, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 2632, 6, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 2925, 7, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,

	/* 11 ac reserved index */
	अणु 1350, 6, RX_ENC_HT,  RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 80 MHz 800 ns GI MCS 8-9 */
	अणु 3510, 8, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,
	अणु 3900, 9, RX_ENC_HT, 0, RATE_INFO_BW_80पूर्ण,

	/* 11 ac reserved indices */
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,
	अणु 1350, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 80 MHz 400 ns SGI MCS 6-7 */
	अणु 2925, 6, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_80 पूर्ण,
	अणु 3250, 7, RX_ENC_HT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_80 पूर्ण,

	/* 11ac reserved index */
	अणु 1350, 6, RX_ENC_HT,  RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_40 पूर्ण,

	/* 11ac 80 MHz 400ns SGI MCS 8-9 */
	अणु 3900, 8, RX_ENC_VHT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_80 पूर्ण,
	अणु 4333, 9, RX_ENC_VHT, RX_ENC_FLAG_SHORT_GI, RATE_INFO_BW_80 पूर्ण,
पूर्ण;

पूर्णांक wcn36xx_rx_skb(काष्ठा wcn36xx *wcn, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status status;
	स्थिर काष्ठा wcn36xx_rate *rate;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा wcn36xx_rx_bd *bd;
	काष्ठा ieee80211_supported_band *sband;
	u16 fc, sn;

	/*
	 * All fields must be 0, otherwise it can lead to
	 * unexpected consequences.
	 */
	स_रखो(&status, 0, माप(status));

	bd = (काष्ठा wcn36xx_rx_bd *)skb->data;
	buff_to_be((u32 *)bd, माप(*bd)/माप(u32));
	wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP,
			 "BD   <<< ", (अक्षर *)bd,
			 माप(काष्ठा wcn36xx_rx_bd));

	skb_put(skb, bd->pdu.mpdu_header_off + bd->pdu.mpdu_len);
	skb_pull(skb, bd->pdu.mpdu_header_off);

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = __le16_to_cpu(hdr->frame_control);
	sn = IEEE80211_SEQ_TO_SN(__le16_to_cpu(hdr->seq_ctrl));

	status.freq = WCN36XX_CENTER_FREQ(wcn);
	status.band = WCN36XX_BAND(wcn);
	status.maस_समय = 10;
	status.संकेत = -get_rssi0(bd);
	status.antenna = 1;
	status.flag = 0;
	status.rx_flags = 0;
	status.flag |= RX_FLAG_IV_STRIPPED |
		       RX_FLAG_MMIC_STRIPPED |
		       RX_FLAG_DECRYPTED;

	wcn36xx_dbg(WCN36XX_DBG_RX, "status.flags=%x\n", status.flag);

	अगर (bd->rate_id < ARRAY_SIZE(wcn36xx_rate_table)) अणु
		rate = &wcn36xx_rate_table[bd->rate_id];
		status.encoding = rate->encoding;
		status.enc_flags = rate->encoding_flags;
		status.bw = rate->bw;
		status.rate_idx = rate->mcs_or_legacy_index;
		sband = wcn->hw->wiphy->bands[status.band];
		status.nss = 1;

		अगर (status.band == NL80211_BAND_5GHZ &&
		    status.encoding == RX_ENC_LEGACY &&
		    status.rate_idx >= sband->n_bitrates) अणु
			/* no dsss rates in 5Ghz rates table */
			status.rate_idx -= 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		status.encoding = 0;
		status.bw = 0;
		status.enc_flags = 0;
		status.rate_idx = 0;
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), &status, माप(status));

	अगर (ieee80211_is_beacon(hdr->frame_control)) अणु
		wcn36xx_dbg(WCN36XX_DBG_BEACON, "beacon skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_BEACON_DUMP, "SKB <<< ",
				 (अक्षर *)skb->data, skb->len);
	पूर्ण अन्यथा अणु
		wcn36xx_dbg(WCN36XX_DBG_RX, "rx skb %p len %d fc %04x sn %d\n",
			    skb, skb->len, fc, sn);
		wcn36xx_dbg_dump(WCN36XX_DBG_RX_DUMP, "SKB <<< ",
				 (अक्षर *)skb->data, skb->len);
	पूर्ण

	ieee80211_rx_irqsafe(wcn->hw, skb);

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_set_tx_pdu(काष्ठा wcn36xx_tx_bd *bd,
			       u32 mpdu_header_len,
			       u32 len,
			       u16 tid)
अणु
	bd->pdu.mpdu_header_len = mpdu_header_len;
	bd->pdu.mpdu_header_off = माप(*bd);
	bd->pdu.mpdu_data_off = bd->pdu.mpdu_header_len +
		bd->pdu.mpdu_header_off;
	bd->pdu.mpdu_len = len;
	bd->pdu.tid = tid;
	/* Use seq number generated by mac80211 */
	bd->pdu.bd_ssn = WCN36XX_TXBD_SSN_FILL_HOST;
पूर्ण

अटल अंतरभूत काष्ठा wcn36xx_vअगर *get_vअगर_by_addr(काष्ठा wcn36xx *wcn,
						  u8 *addr)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = शून्य;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	list_क्रम_each_entry(vअगर_priv, &wcn->vअगर_list, list) अणु
			vअगर = wcn36xx_priv_to_vअगर(vअगर_priv);
			अगर (स_भेद(vअगर->addr, addr, ETH_ALEN) == 0)
				वापस vअगर_priv;
	पूर्ण
	wcn36xx_warn("vif %pM not found\n", addr);
	वापस शून्य;
पूर्ण

अटल व्योम wcn36xx_tx_start_ampdu(काष्ठा wcn36xx *wcn,
				   काष्ठा wcn36xx_sta *sta_priv,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_sta *sta;
	u8 *qc, tid;

	अगर (!conf_is_ht(&wcn->hw->conf))
		वापस;

	sta = wcn36xx_priv_to_sta(sta_priv);

	अगर (WARN_ON(!ieee80211_is_data_qos(hdr->frame_control)))
		वापस;

	अगर (skb_get_queue_mapping(skb) == IEEE80211_AC_VO)
		वापस;

	qc = ieee80211_get_qos_ctl(hdr);
	tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;

	spin_lock(&sta_priv->ampdu_lock);
	अगर (sta_priv->ampdu_state[tid] != WCN36XX_AMPDU_NONE)
		जाओ out_unlock;

	अगर (sta_priv->non_agg_frame_ct++ >= WCN36XX_AMPDU_START_THRESH) अणु
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_START;
		sta_priv->non_agg_frame_ct = 0;
		ieee80211_start_tx_ba_session(sta, tid, 0);
	पूर्ण
out_unlock:
	spin_unlock(&sta_priv->ampdu_lock);
पूर्ण

अटल व्योम wcn36xx_set_tx_data(काष्ठा wcn36xx_tx_bd *bd,
				काष्ठा wcn36xx *wcn,
				काष्ठा wcn36xx_vअगर **vअगर_priv,
				काष्ठा wcn36xx_sta *sta_priv,
				काष्ठा sk_buff *skb,
				bool bcast)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	काष्ठा wcn36xx_vअगर *__vअगर_priv = शून्य;
	bool is_data_qos = ieee80211_is_data_qos(hdr->frame_control);
	u16 tid = 0;

	bd->bd_rate = WCN36XX_BD_RATE_DATA;

	/*
	 * For not unicast frames mac80211 will not set sta poपूर्णांकer so use
	 * self_sta_index instead.
	 */
	अगर (sta_priv) अणु
		__vअगर_priv = sta_priv->vअगर;
		vअगर = wcn36xx_priv_to_vअगर(__vअगर_priv);

		bd->dpu_sign = sta_priv->ucast_dpu_sign;
		अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			bd->sta_index = sta_priv->bss_sta_index;
			bd->dpu_desc_idx = sta_priv->bss_dpu_desc_index;
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_AP ||
			   vअगर->type == NL80211_IFTYPE_ADHOC ||
			   vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
			bd->sta_index = sta_priv->sta_index;
			bd->dpu_desc_idx = sta_priv->dpu_desc_index;
		पूर्ण
	पूर्ण अन्यथा अणु
		__vअगर_priv = get_vअगर_by_addr(wcn, hdr->addr2);
		bd->sta_index = __vअगर_priv->self_sta_index;
		bd->dpu_desc_idx = __vअगर_priv->self_dpu_desc_index;
		bd->dpu_sign = __vअगर_priv->self_ucast_dpu_sign;
	पूर्ण

	अगर (is_data_qos) अणु
		tid = ieee80211_get_tid(hdr);
		/* TID->QID is one-to-one mapping */
		bd->queue_id = tid;
	पूर्ण

	अगर (info->flags & IEEE80211_TX_INTFL_DONT_ENCRYPT ||
	    (sta_priv && !sta_priv->is_data_encrypted)) अणु
		bd->dpu_ne = 1;
	पूर्ण

	अगर (ieee80211_is_any_nullfunc(hdr->frame_control)) अणु
		/* Don't use a regular queue क्रम null packet (no ampdu) */
		bd->queue_id = WCN36XX_TX_U_WQ_ID;
	पूर्ण

	अगर (bcast) अणु
		bd->ub = 1;
		bd->ack_policy = 1;
	पूर्ण
	*vअगर_priv = __vअगर_priv;

	wcn36xx_set_tx_pdu(bd,
			   is_data_qos ?
			   माप(काष्ठा ieee80211_qos_hdr) :
			   माप(काष्ठा ieee80211_hdr_3addr),
			   skb->len, tid);

	अगर (sta_priv && is_data_qos)
		wcn36xx_tx_start_ampdu(wcn, sta_priv, skb);
पूर्ण

अटल व्योम wcn36xx_set_tx_mgmt(काष्ठा wcn36xx_tx_bd *bd,
				काष्ठा wcn36xx *wcn,
				काष्ठा wcn36xx_vअगर **vअगर_priv,
				काष्ठा sk_buff *skb,
				bool bcast)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा wcn36xx_vअगर *__vअगर_priv =
		get_vअगर_by_addr(wcn, hdr->addr2);
	bd->sta_index = __vअगर_priv->self_sta_index;
	bd->dpu_desc_idx = __vअगर_priv->self_dpu_desc_index;
	bd->dpu_ne = 1;

	/* शेष rate क्रम unicast */
	अगर (ieee80211_is_mgmt(hdr->frame_control))
		bd->bd_rate = (WCN36XX_BAND(wcn) == NL80211_BAND_5GHZ) ?
			WCN36XX_BD_RATE_CTRL :
			WCN36XX_BD_RATE_MGMT;
	अन्यथा अगर (ieee80211_is_ctl(hdr->frame_control))
		bd->bd_rate = WCN36XX_BD_RATE_CTRL;
	अन्यथा
		wcn36xx_warn("frame control type unknown\n");

	/*
	 * In joining state trick hardware that probe is sent as
	 * unicast even अगर address is broadcast.
	 */
	अगर (__vअगर_priv->is_joining &&
	    ieee80211_is_probe_req(hdr->frame_control))
		bcast = false;

	अगर (bcast) अणु
		/* broadcast */
		bd->ub = 1;
		/* No ack needed not unicast */
		bd->ack_policy = 1;
		bd->queue_id = WCN36XX_TX_B_WQ_ID;
	पूर्ण अन्यथा
		bd->queue_id = WCN36XX_TX_U_WQ_ID;
	*vअगर_priv = __vअगर_priv;

	wcn36xx_set_tx_pdu(bd,
			   ieee80211_is_data_qos(hdr->frame_control) ?
			   माप(काष्ठा ieee80211_qos_hdr) :
			   माप(काष्ठा ieee80211_hdr_3addr),
			   skb->len, WCN36XX_TID);
पूर्ण

पूर्णांक wcn36xx_start_tx(काष्ठा wcn36xx *wcn,
		     काष्ठा wcn36xx_sta *sta_priv,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा wcn36xx_vअगर *vअगर_priv = शून्य;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	अचिन्हित दीर्घ flags;
	bool is_low = ieee80211_is_data(hdr->frame_control);
	bool bcast = is_broadcast_ether_addr(hdr->addr1) ||
		is_multicast_ether_addr(hdr->addr1);
	काष्ठा wcn36xx_tx_bd bd;
	पूर्णांक ret;

	स_रखो(&bd, 0, माप(bd));

	wcn36xx_dbg(WCN36XX_DBG_TX,
		    "tx skb %p len %d fc %04x sn %d %s %s\n",
		    skb, skb->len, __le16_to_cpu(hdr->frame_control),
		    IEEE80211_SEQ_TO_SN(__le16_to_cpu(hdr->seq_ctrl)),
		    is_low ? "low" : "high", bcast ? "bcast" : "ucast");

	wcn36xx_dbg_dump(WCN36XX_DBG_TX_DUMP, "", skb->data, skb->len);

	bd.dpu_rf = WCN36XX_BMU_WQ_TX;

	अगर (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS) अणु
		wcn36xx_dbg(WCN36XX_DBG_DXE, "TX_ACK status requested\n");

		spin_lock_irqsave(&wcn->dxe_lock, flags);
		अगर (wcn->tx_ack_skb) अणु
			spin_unlock_irqrestore(&wcn->dxe_lock, flags);
			wcn36xx_warn("tx_ack_skb already set\n");
			वापस -EINVAL;
		पूर्ण

		wcn->tx_ack_skb = skb;
		spin_unlock_irqrestore(&wcn->dxe_lock, flags);

		/* Only one at a समय is supported by fw. Stop the TX queues
		 * until the ack status माला_लो back.
		 */
		ieee80211_stop_queues(wcn->hw);

		/* TX watchकरोg अगर no TX irq or ack indication received  */
		mod_समयr(&wcn->tx_ack_समयr, jअगरfies + HZ / 10);

		/* Request ack indication from the firmware */
		अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
			bd.tx_comp = 1;
	पूर्ण

	/* Data frames served first*/
	अगर (is_low)
		wcn36xx_set_tx_data(&bd, wcn, &vअगर_priv, sta_priv, skb, bcast);
	अन्यथा
		/* MGMT and CTRL frames are handeld here*/
		wcn36xx_set_tx_mgmt(&bd, wcn, &vअगर_priv, skb, bcast);

	buff_to_be((u32 *)&bd, माप(bd)/माप(u32));
	bd.tx_bd_sign = 0xbdbdbdbd;

	ret = wcn36xx_dxe_tx_frame(wcn, vअगर_priv, &bd, skb, is_low);
	अगर (ret && (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)) अणु
		/* If the skb has not been transmitted,
		 * करोn't keep a reference to it.
		 */
		spin_lock_irqsave(&wcn->dxe_lock, flags);
		wcn->tx_ack_skb = शून्य;
		spin_unlock_irqrestore(&wcn->dxe_lock, flags);

		ieee80211_wake_queues(wcn->hw);
	पूर्ण

	वापस ret;
पूर्ण
