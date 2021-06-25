<शैली गुरु>
/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
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

#समावेश <linux/relay.h>
#समावेश <linux/अक्रमom.h>
#समावेश "ath9k.h"

अटल s8 fix_rssi_inv_only(u8 rssi_val)
अणु
	अगर (rssi_val == 128)
		rssi_val = 0;
	वापस (s8) rssi_val;
पूर्ण

अटल व्योम ath_debug_send_fft_sample(काष्ठा ath_spec_scan_priv *spec_priv,
				      काष्ठा fft_sample_tlv *fft_sample_tlv)
अणु
	पूर्णांक length;
	अगर (!spec_priv->rfs_chan_spec_scan)
		वापस;

	length = __be16_to_cpu(fft_sample_tlv->length) +
		 माप(*fft_sample_tlv);
	relay_ग_लिखो(spec_priv->rfs_chan_spec_scan, fft_sample_tlv, length);
पूर्ण

प्रकार पूर्णांक (ath_cmn_fft_idx_validator) (u8 *sample_end, पूर्णांक bytes_पढ़ो);

अटल पूर्णांक
ath_cmn_max_idx_verअगरy_ht20_fft(u8 *sample_end, पूर्णांक bytes_पढ़ो)
अणु
	काष्ठा ath_ht20_mag_info *mag_info;
	u8 *sample;
	u16 max_magnitude;
	u8 max_index;
	u8 max_exp;

	/* Sanity check so that we करोn't पढ़ो outside the पढ़ो
	 * buffer
	 */
	अगर (bytes_पढ़ो < SPECTRAL_HT20_SAMPLE_LEN - 1)
		वापस -1;

	mag_info = (काष्ठा ath_ht20_mag_info *) (sample_end -
				माप(काष्ठा ath_ht20_mag_info) + 1);

	sample = sample_end - SPECTRAL_HT20_SAMPLE_LEN + 1;

	max_index = spectral_max_index_ht20(mag_info->all_bins);
	max_magnitude = spectral_max_magnitude(mag_info->all_bins);

	max_exp = mag_info->max_exp & 0xf;

	/* Don't try to पढ़ो something outside the पढ़ो buffer
	 * in हाल of a missing byte (so bins[0] will be outside
	 * the पढ़ो buffer)
	 */
	अगर (bytes_पढ़ो < SPECTRAL_HT20_SAMPLE_LEN && max_index < 1)
		वापस -1;

	अगर ((sample[max_index] & 0xf8) != ((max_magnitude >> max_exp) & 0xf8))
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक
ath_cmn_max_idx_verअगरy_ht20_40_fft(u8 *sample_end, पूर्णांक bytes_पढ़ो)
अणु
	काष्ठा ath_ht20_40_mag_info *mag_info;
	u8 *sample;
	u16 lower_mag, upper_mag;
	u8 lower_max_index, upper_max_index;
	u8 max_exp;
	पूर्णांक dc_pos = SPECTRAL_HT20_40_NUM_BINS / 2;

	/* Sanity check so that we करोn't पढ़ो outside the पढ़ो
	 * buffer
	 */
	अगर (bytes_पढ़ो < SPECTRAL_HT20_40_SAMPLE_LEN - 1)
		वापस -1;

	mag_info = (काष्ठा ath_ht20_40_mag_info *) (sample_end -
				माप(काष्ठा ath_ht20_40_mag_info) + 1);

	sample = sample_end - SPECTRAL_HT20_40_SAMPLE_LEN + 1;

	lower_mag = spectral_max_magnitude(mag_info->lower_bins);
	lower_max_index = spectral_max_index_ht40(mag_info->lower_bins);

	upper_mag = spectral_max_magnitude(mag_info->upper_bins);
	upper_max_index = spectral_max_index_ht40(mag_info->upper_bins);

	max_exp = mag_info->max_exp & 0xf;

	/* Don't try to पढ़ो something outside the पढ़ो buffer
	 * in हाल of a missing byte (so bins[0] will be outside
	 * the पढ़ो buffer)
	 */
	अगर (bytes_पढ़ो < SPECTRAL_HT20_40_SAMPLE_LEN &&
	   ((upper_max_index < 1) || (lower_max_index < 1)))
		वापस -1;

	अगर (((sample[upper_max_index + dc_pos] & 0xf8) !=
	     ((upper_mag >> max_exp) & 0xf8)) ||
	    ((sample[lower_max_index] & 0xf8) !=
	     ((lower_mag >> max_exp) & 0xf8)))
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

प्रकार पूर्णांक (ath_cmn_fft_sample_handler) (काष्ठा ath_rx_status *rs,
			काष्ठा ath_spec_scan_priv *spec_priv,
			u8 *sample_buf, u64 tsf, u16 freq, पूर्णांक chan_type);

अटल पूर्णांक
ath_cmn_process_ht20_fft(काष्ठा ath_rx_status *rs,
			काष्ठा ath_spec_scan_priv *spec_priv,
			u8 *sample_buf,
			u64 tsf, u16 freq, पूर्णांक chan_type)
अणु
	काष्ठा fft_sample_ht20 fft_sample_20;
	काष्ठा ath_common *common = ath9k_hw_common(spec_priv->ah);
	काष्ठा ath_hw *ah = spec_priv->ah;
	काष्ठा ath_ht20_mag_info *mag_info;
	काष्ठा fft_sample_tlv *tlv;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	पूर्णांक dc_pos = SPECTRAL_HT20_NUM_BINS / 2;
	u16 magnitude, पंचांगp_mag, length;
	u8 max_index, biपंचांगap_w, max_exp;

	length = माप(fft_sample_20) - माप(काष्ठा fft_sample_tlv);
	fft_sample_20.tlv.type = ATH_FFT_SAMPLE_HT20;
	fft_sample_20.tlv.length = __cpu_to_be16(length);
	fft_sample_20.freq = __cpu_to_be16(freq);
	fft_sample_20.rssi = fix_rssi_inv_only(rs->rs_rssi_ctl[0]);
	fft_sample_20.noise = ah->noise;

	mag_info = (काष्ठा ath_ht20_mag_info *) (sample_buf +
					SPECTRAL_HT20_NUM_BINS);

	magnitude = spectral_max_magnitude(mag_info->all_bins);
	fft_sample_20.max_magnitude = __cpu_to_be16(magnitude);

	max_index = spectral_max_index_ht20(mag_info->all_bins);
	fft_sample_20.max_index = max_index;

	biपंचांगap_w = spectral_biपंचांगap_weight(mag_info->all_bins);
	fft_sample_20.biपंचांगap_weight = biपंचांगap_w;

	max_exp = mag_info->max_exp & 0xf;
	fft_sample_20.max_exp = max_exp;

	fft_sample_20.tsf = __cpu_to_be64(tsf);

	स_नकल(fft_sample_20.data, sample_buf, SPECTRAL_HT20_NUM_BINS);

	ath_dbg(common, SPECTRAL_SCAN, "FFT HT20 frame: max mag 0x%X,"
					"max_mag_idx %i\n",
					magnitude >> max_exp,
					max_index);

	अगर ((fft_sample_20.data[max_index] & 0xf8) !=
	    ((magnitude >> max_exp) & 0xf8)) अणु
		ath_dbg(common, SPECTRAL_SCAN, "Magnitude mismatch !\n");
		ret = -1;
	पूर्ण

	/* DC value (value in the middle) is the blind spot of the spectral
	 * sample and invalid, पूर्णांकerpolate it.
	 */
	fft_sample_20.data[dc_pos] = (fft_sample_20.data[dc_pos + 1] +
					fft_sample_20.data[dc_pos - 1]) / 2;

	/* Check अगर the maximum magnitude is indeed maximum,
	 * also अगर the maximum value was at dc_pos, calculate
	 * a new one (since value at dc_pos is invalid).
	 */
	अगर (max_index == dc_pos) अणु
		पंचांगp_mag = 0;
		क्रम (i = 0; i < dc_pos; i++) अणु
			अगर (fft_sample_20.data[i] > पंचांगp_mag) अणु
				पंचांगp_mag = fft_sample_20.data[i];
				fft_sample_20.max_index = i;
			पूर्ण
		पूर्ण

		magnitude = पंचांगp_mag << max_exp;
		fft_sample_20.max_magnitude = __cpu_to_be16(magnitude);

		ath_dbg(common, SPECTRAL_SCAN,
			"Calculated new lower max 0x%X at %i\n",
			पंचांगp_mag, fft_sample_20.max_index);
	पूर्ण अन्यथा
	क्रम (i = 0; i < SPECTRAL_HT20_NUM_BINS; i++) अणु
		अगर (fft_sample_20.data[i] == (magnitude >> max_exp))
			ath_dbg(common, SPECTRAL_SCAN,
				"Got max: 0x%X at index %i\n",
				fft_sample_20.data[i], i);

		अगर (fft_sample_20.data[i] > (magnitude >> max_exp)) अणु
			ath_dbg(common, SPECTRAL_SCAN,
				"Got bin %i greater than max: 0x%X\n",
				i, fft_sample_20.data[i]);
			ret = -1;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	tlv = (काष्ठा fft_sample_tlv *)&fft_sample_20;

	ath_debug_send_fft_sample(spec_priv, tlv);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath_cmn_process_ht20_40_fft(काष्ठा ath_rx_status *rs,
			काष्ठा ath_spec_scan_priv *spec_priv,
			u8 *sample_buf,
			u64 tsf, u16 freq, पूर्णांक chan_type)
अणु
	काष्ठा fft_sample_ht20_40 fft_sample_40;
	काष्ठा ath_common *common = ath9k_hw_common(spec_priv->ah);
	काष्ठा ath_hw *ah = spec_priv->ah;
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	काष्ठा ath_ht20_40_mag_info *mag_info;
	काष्ठा fft_sample_tlv *tlv;
	पूर्णांक dc_pos = SPECTRAL_HT20_40_NUM_BINS / 2;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	s16 ext_nf;
	u16 lower_mag, upper_mag, पंचांगp_mag, length;
	s8 lower_rssi, upper_rssi;
	u8 lower_max_index, upper_max_index;
	u8 lower_biपंचांगap_w, upper_biपंचांगap_w, max_exp;

	अगर (caldata)
		ext_nf = ath9k_hw_अ_लोhan_noise(ah, ah->curchan,
				caldata->nfCalHist[3].privNF);
	अन्यथा
		ext_nf = ATH_DEFAULT_NOISE_FLOOR;

	length = माप(fft_sample_40) - माप(काष्ठा fft_sample_tlv);
	fft_sample_40.tlv.type = ATH_FFT_SAMPLE_HT20_40;
	fft_sample_40.tlv.length = __cpu_to_be16(length);
	fft_sample_40.freq = __cpu_to_be16(freq);
	fft_sample_40.channel_type = chan_type;

	अगर (chan_type == NL80211_CHAN_HT40PLUS) अणु
		lower_rssi = fix_rssi_inv_only(rs->rs_rssi_ctl[0]);
		upper_rssi = fix_rssi_inv_only(rs->rs_rssi_ext[0]);

		fft_sample_40.lower_noise = ah->noise;
		fft_sample_40.upper_noise = ext_nf;
	पूर्ण अन्यथा अणु
		lower_rssi = fix_rssi_inv_only(rs->rs_rssi_ext[0]);
		upper_rssi = fix_rssi_inv_only(rs->rs_rssi_ctl[0]);

		fft_sample_40.lower_noise = ext_nf;
		fft_sample_40.upper_noise = ah->noise;
	पूर्ण

	fft_sample_40.lower_rssi = lower_rssi;
	fft_sample_40.upper_rssi = upper_rssi;

	mag_info = (काष्ठा ath_ht20_40_mag_info *) (sample_buf +
					SPECTRAL_HT20_40_NUM_BINS);

	lower_mag = spectral_max_magnitude(mag_info->lower_bins);
	fft_sample_40.lower_max_magnitude = __cpu_to_be16(lower_mag);

	upper_mag = spectral_max_magnitude(mag_info->upper_bins);
	fft_sample_40.upper_max_magnitude = __cpu_to_be16(upper_mag);

	lower_max_index = spectral_max_index_ht40(mag_info->lower_bins);
	fft_sample_40.lower_max_index = lower_max_index;

	upper_max_index = spectral_max_index_ht40(mag_info->upper_bins);
	fft_sample_40.upper_max_index = upper_max_index;

	lower_biपंचांगap_w = spectral_biपंचांगap_weight(mag_info->lower_bins);
	fft_sample_40.lower_biपंचांगap_weight = lower_biपंचांगap_w;

	upper_biपंचांगap_w = spectral_biपंचांगap_weight(mag_info->upper_bins);
	fft_sample_40.upper_biपंचांगap_weight = upper_biपंचांगap_w;

	max_exp = mag_info->max_exp & 0xf;
	fft_sample_40.max_exp = max_exp;

	fft_sample_40.tsf = __cpu_to_be64(tsf);

	स_नकल(fft_sample_40.data, sample_buf, SPECTRAL_HT20_40_NUM_BINS);

	ath_dbg(common, SPECTRAL_SCAN, "FFT HT20/40 frame: lower mag 0x%X,"
					"lower_mag_idx %i, upper mag 0x%X,"
					"upper_mag_idx %i\n",
					lower_mag >> max_exp,
					lower_max_index,
					upper_mag >> max_exp,
					upper_max_index);

	/* Check अगर we got the expected magnitude values at
	 * the expected bins
	 */
	अगर (((fft_sample_40.data[upper_max_index + dc_pos] & 0xf8)
	    != ((upper_mag >> max_exp) & 0xf8)) ||
	   ((fft_sample_40.data[lower_max_index] & 0xf8)
	    != ((lower_mag >> max_exp) & 0xf8))) अणु
		ath_dbg(common, SPECTRAL_SCAN, "Magnitude mismatch !\n");
		ret = -1;
	पूर्ण

	/* DC value (value in the middle) is the blind spot of the spectral
	 * sample and invalid, पूर्णांकerpolate it.
	 */
	fft_sample_40.data[dc_pos] = (fft_sample_40.data[dc_pos + 1] +
					fft_sample_40.data[dc_pos - 1]) / 2;

	/* Check अगर the maximum magnitudes are indeed maximum,
	 * also अगर the maximum value was at dc_pos, calculate
	 * a new one (since value at dc_pos is invalid).
	 */
	अगर (lower_max_index == dc_pos) अणु
		पंचांगp_mag = 0;
		क्रम (i = 0; i < dc_pos; i++) अणु
			अगर (fft_sample_40.data[i] > पंचांगp_mag) अणु
				पंचांगp_mag = fft_sample_40.data[i];
				fft_sample_40.lower_max_index = i;
			पूर्ण
		पूर्ण

		lower_mag = पंचांगp_mag << max_exp;
		fft_sample_40.lower_max_magnitude = __cpu_to_be16(lower_mag);

		ath_dbg(common, SPECTRAL_SCAN,
			"Calculated new lower max 0x%X at %i\n",
			पंचांगp_mag, fft_sample_40.lower_max_index);
	पूर्ण अन्यथा
	क्रम (i = 0; i < dc_pos; i++) अणु
		अगर (fft_sample_40.data[i] == (lower_mag >> max_exp))
			ath_dbg(common, SPECTRAL_SCAN,
				"Got lower mag: 0x%X at index %i\n",
				fft_sample_40.data[i], i);

		अगर (fft_sample_40.data[i] > (lower_mag >> max_exp)) अणु
			ath_dbg(common, SPECTRAL_SCAN,
				"Got lower bin %i higher than max: 0x%X\n",
				i, fft_sample_40.data[i]);
			ret = -1;
		पूर्ण
	पूर्ण

	अगर (upper_max_index == dc_pos) अणु
		पंचांगp_mag = 0;
		क्रम (i = dc_pos; i < SPECTRAL_HT20_40_NUM_BINS; i++) अणु
			अगर (fft_sample_40.data[i] > पंचांगp_mag) अणु
				पंचांगp_mag = fft_sample_40.data[i];
				fft_sample_40.upper_max_index = i;
			पूर्ण
		पूर्ण
		upper_mag = पंचांगp_mag << max_exp;
		fft_sample_40.upper_max_magnitude = __cpu_to_be16(upper_mag);

		ath_dbg(common, SPECTRAL_SCAN,
			"Calculated new upper max 0x%X at %i\n",
			पंचांगp_mag, fft_sample_40.upper_max_index);
	पूर्ण अन्यथा
	क्रम (i = dc_pos; i < SPECTRAL_HT20_40_NUM_BINS; i++) अणु
		अगर (fft_sample_40.data[i] == (upper_mag >> max_exp))
			ath_dbg(common, SPECTRAL_SCAN,
				"Got upper mag: 0x%X at index %i\n",
				fft_sample_40.data[i], i);

		अगर (fft_sample_40.data[i] > (upper_mag >> max_exp)) अणु
			ath_dbg(common, SPECTRAL_SCAN,
				"Got upper bin %i higher than max: 0x%X\n",
				i, fft_sample_40.data[i]);

			ret = -1;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	tlv = (काष्ठा fft_sample_tlv *)&fft_sample_40;

	ath_debug_send_fft_sample(spec_priv, tlv);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
ath_cmn_copy_fft_frame(u8 *in, u8 *out, पूर्णांक sample_len, पूर्णांक sample_bytes)
अणु
	चयन (sample_bytes - sample_len) अणु
	हाल -1:
		/* First byte missing */
		स_नकल(&out[1], in,
		       sample_len - 1);
		अवरोध;
	हाल 0:
		/* Length correct, nothing to करो. */
		स_नकल(out, in, sample_len);
		अवरोध;
	हाल 1:
		/* MAC added 2 extra bytes AND first byte
		 * is missing.
		 */
		स_नकल(&out[1], in, 30);
		out[31] = in[31];
		स_नकल(&out[32], &in[33],
		       sample_len - 32);
		अवरोध;
	हाल 2:
		/* MAC added 2 extra bytes at bin 30 and 32,
		 * हटाओ them.
		 */
		स_नकल(out, in, 30);
		out[30] = in[31];
		स_नकल(&out[31], &in[33],
		       sample_len - 31);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
ath_cmn_is_fft_buf_full(काष्ठा ath_spec_scan_priv *spec_priv)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret = 0;
	काष्ठा rchan_buf *buf;
	काष्ठा rchan *rc = spec_priv->rfs_chan_spec_scan;

	क्रम_each_possible_cpu(i) अणु
		अगर ((buf = *per_cpu_ptr(rc->buf, i))) अणु
			ret += relay_buf_full(buf);
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* वापसs 1 अगर this was a spectral frame, even अगर not handled. */
पूर्णांक ath_cmn_process_fft(काष्ठा ath_spec_scan_priv *spec_priv, काष्ठा ieee80211_hdr *hdr,
		    काष्ठा ath_rx_status *rs, u64 tsf)
अणु
	u8 sample_buf[SPECTRAL_SAMPLE_MAX_LEN] = अणु0पूर्ण;
	काष्ठा ath_hw *ah = spec_priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(spec_priv->ah);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *)common->priv;
	u8 num_bins, *vdata = (u8 *)hdr;
	काष्ठा ath_radar_info *radar_info;
	पूर्णांक len = rs->rs_datalen;
	पूर्णांक i;
	पूर्णांक got_slen = 0;
	u8  *sample_start;
	पूर्णांक sample_bytes = 0;
	पूर्णांक ret = 0;
	u16 fft_len, sample_len, freq = ah->curchan->chan->center_freq;
	क्रमागत nl80211_channel_type chan_type;
	ath_cmn_fft_idx_validator *fft_idx_validator;
	ath_cmn_fft_sample_handler *fft_handler;

	/* AR9280 and beक्रमe report via ATH9K_PHYERR_RADAR, AR93xx and newer
	 * via ATH9K_PHYERR_SPECTRAL. Haven't seen ATH9K_PHYERR_FALSE_RADAR_EXT
	 * yet, but this is supposed to be possible as well.
	 */
	अगर (rs->rs_phyerr != ATH9K_PHYERR_RADAR &&
	    rs->rs_phyerr != ATH9K_PHYERR_FALSE_RADAR_EXT &&
	    rs->rs_phyerr != ATH9K_PHYERR_SPECTRAL)
		वापस 0;

	/* check अगर spectral scan bit is set. This करोes not have to be checked
	 * अगर received through a SPECTRAL phy error, but shouldn't hurt.
	 */
	radar_info = ((काष्ठा ath_radar_info *)&vdata[len]) - 1;
	अगर (!(radar_info->pulse_bw_info & SPECTRAL_SCAN_BITMASK))
		वापस 0;

	अगर (!spec_priv->rfs_chan_spec_scan)
		वापस 1;

	/* Output buffers are full, no need to process anything
	 * since there is no space to put the result anyway
	 */
	ret = ath_cmn_is_fft_buf_full(spec_priv);
	अगर (ret == 1) अणु
		ath_dbg(common, SPECTRAL_SCAN, "FFT report ignored, no space "
						"left on output buffers\n");
		वापस 1;
	पूर्ण

	chan_type = cfg80211_get_chandef_type(&common->hw->conf.chandef);
	अगर ((chan_type == NL80211_CHAN_HT40MINUS) ||
	    (chan_type == NL80211_CHAN_HT40PLUS)) अणु
		fft_len = SPECTRAL_HT20_40_TOTAL_DATA_LEN;
		sample_len = SPECTRAL_HT20_40_SAMPLE_LEN;
		num_bins = SPECTRAL_HT20_40_NUM_BINS;
		fft_idx_validator = &ath_cmn_max_idx_verअगरy_ht20_40_fft;
		fft_handler = &ath_cmn_process_ht20_40_fft;
	पूर्ण अन्यथा अणु
		fft_len = SPECTRAL_HT20_TOTAL_DATA_LEN;
		sample_len = SPECTRAL_HT20_SAMPLE_LEN;
		num_bins = SPECTRAL_HT20_NUM_BINS;
		fft_idx_validator = ath_cmn_max_idx_verअगरy_ht20_fft;
		fft_handler = &ath_cmn_process_ht20_fft;
	पूर्ण

	ath_dbg(common, SPECTRAL_SCAN, "Got radar dump bw_info: 0x%X,"
					"len: %i fft_len: %i\n",
					radar_info->pulse_bw_info,
					len,
					fft_len);
	sample_start = vdata;
	क्रम (i = 0; i < len - 2; i++) अणु
		sample_bytes++;

		/* Only a single sample received, no need to look
		 * क्रम the sample's end, करो the correction based
		 * on the packet's length instead. Note that hw
		 * will always put the radar_info काष्ठाure on
		 * the end.
		 */
		अगर (len <= fft_len + 2) अणु
			sample_bytes = len - माप(काष्ठा ath_radar_info);
			got_slen = 1;
		पूर्ण

		/* Search क्रम the end of the FFT frame between
		 * sample_len - 1 and sample_len + 2. exp_max is 3
		 * bits दीर्घ and it's the only value on the last
		 * byte of the frame so since it'll be smaller than
		 * the next byte (the first bin of the next sample)
		 * 90% of the समय, we can use it as a separator.
		 */
		अगर (vdata[i] <= 0x7 && sample_bytes >= sample_len - 1) अणु

			/* Got a frame length within boundaries, there are
			 * four scenarios here:
			 *
			 * a) sample_len -> We got the correct length
			 * b) sample_len + 2 -> 2 bytes added around bin[31]
			 * c) sample_len - 1 -> The first byte is missing
			 * d) sample_len + 1 -> b + c at the same समय
			 *
			 * When MAC adds 2 extra bytes, bin[31] and bin[32]
			 * have the same value, so we can use that क्रम further
			 * verअगरication in हालs b and d.
			 */

			/* Did we go too far ? If so we couldn't determine
			 * this sample's boundaries, discard any further
			 * data
			 */
			अगर ((sample_bytes > sample_len + 2) ||
			   ((sample_bytes > sample_len) &&
			   (sample_start[31] != sample_start[32])))
				अवरोध;

			/* See अगर we got a valid frame by checking the
			 * consistency of mag_info fields. This is to
			 * prevent from "fixing" a correct frame.
			 * Failure is non-fatal, later frames may
			 * be valid.
			 */
			अगर (!fft_idx_validator(&vdata[i], i)) अणु
				ath_dbg(common, SPECTRAL_SCAN,
					"Found valid fft frame at %i\n", i);
				got_slen = 1;
			पूर्ण

			/* We expect 1 - 2 more bytes */
			अन्यथा अगर ((sample_start[31] == sample_start[32]) &&
				(sample_bytes >= sample_len) &&
				(sample_bytes < sample_len + 2) &&
				(vdata[i + 1] <= 0x7))
				जारी;

			/* Try to distinguish हालs a and c */
			अन्यथा अगर ((sample_bytes == sample_len - 1) &&
				(vdata[i + 1] <= 0x7))
				जारी;

			got_slen = 1;
		पूर्ण

		अगर (got_slen) अणु
			ath_dbg(common, SPECTRAL_SCAN, "FFT frame len: %i\n",
				sample_bytes);

			/* Only try to fix a frame अगर it's the only one
			 * on the report, अन्यथा just skip it.
			 */
			अगर (sample_bytes != sample_len && len <= fft_len + 2) अणु
				ath_cmn_copy_fft_frame(sample_start,
						       sample_buf, sample_len,
						       sample_bytes);

				ret = fft_handler(rs, spec_priv, sample_buf,
						  tsf, freq, chan_type);

				अगर (ret == 0)
					RX_STAT_INC(sc, rx_spectral_sample_good);
				अन्यथा
					RX_STAT_INC(sc, rx_spectral_sample_err);

				स_रखो(sample_buf, 0, SPECTRAL_SAMPLE_MAX_LEN);

				/* Mix the received bins to the /dev/अक्रमom
				 * pool
				 */
				add_device_अक्रमomness(sample_buf, num_bins);
			पूर्ण

			/* Process a normal frame */
			अगर (sample_bytes == sample_len) अणु
				ret = fft_handler(rs, spec_priv, sample_start,
						  tsf, freq, chan_type);

				अगर (ret == 0)
					RX_STAT_INC(sc, rx_spectral_sample_good);
				अन्यथा
					RX_STAT_INC(sc, rx_spectral_sample_err);

				/* Mix the received bins to the /dev/अक्रमom
				 * pool
				 */
				add_device_अक्रमomness(sample_start, num_bins);
			पूर्ण

			/* Short report processed, अवरोध out of the
			 * loop.
			 */
			अगर (len <= fft_len + 2)
				वापस 1;

			sample_start = &vdata[i + 1];

			/* -1 to grab sample_len -1, -2 since
			 * they 'll get increased by one. In हाल
			 * of failure try to recover by going byte
			 * by byte instead.
			 */
			अगर (ret == 0) अणु
				i += num_bins - 2;
				sample_bytes = num_bins - 2;
			पूर्ण
			got_slen = 0;
		पूर्ण
	पूर्ण

	i -= num_bins - 2;
	अगर (len - i != माप(काष्ठा ath_radar_info))
		ath_dbg(common, SPECTRAL_SCAN, "FFT report truncated"
						"(bytes left: %i)\n",
						len - i);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(ath_cmn_process_fft);

/*********************/
/* spectral_scan_ctl */
/*********************/

अटल sमाप_प्रकार पढ़ो_file_spec_scan_ctl(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अक्षर *mode = "";
	अचिन्हित पूर्णांक len;

	चयन (spec_priv->spectral_mode) अणु
	हाल SPECTRAL_DISABLED:
		mode = "disable";
		अवरोध;
	हाल SPECTRAL_BACKGROUND:
		mode = "background";
		अवरोध;
	हाल SPECTRAL_CHANSCAN:
		mode = "chanscan";
		अवरोध;
	हाल SPECTRAL_MANUAL:
		mode = "manual";
		अवरोध;
	पूर्ण
	len = म_माप(mode);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, mode, len);
पूर्ण

व्योम ath9k_cmn_spectral_scan_trigger(काष्ठा ath_common *common,
				 काष्ठा ath_spec_scan_priv *spec_priv)
अणु
	काष्ठा ath_hw *ah = spec_priv->ah;
	u32 rxfilter;

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस;

	अगर (!ath9k_hw_ops(ah)->spectral_scan_trigger) अणु
		ath_err(common, "spectrum analyzer not implemented on this hardware\n");
		वापस;
	पूर्ण

	अगर (!spec_priv->spec_config.enabled)
		वापस;

	ath_ps_ops(common)->wakeup(common);
	rxfilter = ath9k_hw_getrxfilter(ah);
	ath9k_hw_setrxfilter(ah, rxfilter |
				 ATH9K_RX_FILTER_PHYRADAR |
				 ATH9K_RX_FILTER_PHYERR);

	/* TODO: usually this should not be neccesary, but क्रम some reason
	 * (or in some mode?) the trigger must be called after the
	 * configuration, otherwise the रेजिस्टर will have its values reset
	 * (on my ar9220 to value 0x01002310)
	 */
	ath9k_cmn_spectral_scan_config(common, spec_priv, spec_priv->spectral_mode);
	ath9k_hw_ops(ah)->spectral_scan_trigger(ah);
	ath_ps_ops(common)->restore(common);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_spectral_scan_trigger);

पूर्णांक ath9k_cmn_spectral_scan_config(काष्ठा ath_common *common,
			       काष्ठा ath_spec_scan_priv *spec_priv,
			       क्रमागत spectral_mode spectral_mode)
अणु
	काष्ठा ath_hw *ah = spec_priv->ah;

	अगर (!ath9k_hw_ops(ah)->spectral_scan_trigger) अणु
		ath_err(common, "spectrum analyzer not implemented on this hardware\n");
		वापस -1;
	पूर्ण

	चयन (spectral_mode) अणु
	हाल SPECTRAL_DISABLED:
		spec_priv->spec_config.enabled = 0;
		अवरोध;
	हाल SPECTRAL_BACKGROUND:
		/* send endless samples.
		 * TODO: is this really useful क्रम "background"?
		 */
		spec_priv->spec_config.endless = 1;
		spec_priv->spec_config.enabled = 1;
		अवरोध;
	हाल SPECTRAL_CHANSCAN:
	हाल SPECTRAL_MANUAL:
		spec_priv->spec_config.endless = 0;
		spec_priv->spec_config.enabled = 1;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	ath_ps_ops(common)->wakeup(common);
	ath9k_hw_ops(ah)->spectral_scan_config(ah, &spec_priv->spec_config);
	ath_ps_ops(common)->restore(common);

	spec_priv->spectral_mode = spectral_mode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_spectral_scan_config);

अटल sमाप_प्रकार ग_लिखो_file_spec_scan_ctl(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(spec_priv->ah);
	अक्षर buf[32];
	sमाप_प्रकार len;

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस -EOPNOTSUPP;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';

	अगर (म_भेदन("trigger", buf, 7) == 0) अणु
		ath9k_cmn_spectral_scan_trigger(common, spec_priv);
	पूर्ण अन्यथा अगर (म_भेदन("background", buf, 10) == 0) अणु
		ath9k_cmn_spectral_scan_config(common, spec_priv, SPECTRAL_BACKGROUND);
		ath_dbg(common, CONFIG, "spectral scan: background mode enabled\n");
	पूर्ण अन्यथा अगर (म_भेदन("chanscan", buf, 8) == 0) अणु
		ath9k_cmn_spectral_scan_config(common, spec_priv, SPECTRAL_CHANSCAN);
		ath_dbg(common, CONFIG, "spectral scan: channel scan mode enabled\n");
	पूर्ण अन्यथा अगर (म_भेदन("manual", buf, 6) == 0) अणु
		ath9k_cmn_spectral_scan_config(common, spec_priv, SPECTRAL_MANUAL);
		ath_dbg(common, CONFIG, "spectral scan: manual mode enabled\n");
	पूर्ण अन्यथा अगर (म_भेदन("disable", buf, 7) == 0) अणु
		ath9k_cmn_spectral_scan_config(common, spec_priv, SPECTRAL_DISABLED);
		ath_dbg(common, CONFIG, "spectral scan: disabled\n");
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spec_scan_ctl = अणु
	.पढ़ो = पढ़ो_file_spec_scan_ctl,
	.ग_लिखो = ग_लिखो_file_spec_scan_ctl,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/*************************/
/* spectral_लघु_repeat */
/*************************/

अटल sमाप_प्रकार पढ़ो_file_spectral_लघु_repeat(काष्ठा file *file,
					       अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", spec_priv->spec_config.लघु_repeat);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_लघु_repeat(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 1)
		वापस -EINVAL;

	spec_priv->spec_config.लघु_repeat = val;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_लघु_repeat = अणु
	.पढ़ो = पढ़ो_file_spectral_लघु_repeat,
	.ग_लिखो = ग_लिखो_file_spectral_लघु_repeat,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/******************/
/* spectral_count */
/******************/

अटल sमाप_प्रकार पढ़ो_file_spectral_count(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", spec_priv->spec_config.count);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_count(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 255)
		वापस -EINVAL;

	spec_priv->spec_config.count = val;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_count = अणु
	.पढ़ो = पढ़ो_file_spectral_count,
	.ग_लिखो = ग_लिखो_file_spectral_count,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/*******************/
/* spectral_period */
/*******************/

अटल sमाप_प्रकार पढ़ो_file_spectral_period(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", spec_priv->spec_config.period);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_period(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 255)
		वापस -EINVAL;

	spec_priv->spec_config.period = val;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_period = अणु
	.पढ़ो = पढ़ो_file_spectral_period,
	.ग_लिखो = ग_लिखो_file_spectral_period,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/***********************/
/* spectral_fft_period */
/***********************/

अटल sमाप_प्रकार पढ़ो_file_spectral_fft_period(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", spec_priv->spec_config.fft_period);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_spectral_fft_period(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_spec_scan_priv *spec_priv = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 15)
		वापस -EINVAL;

	spec_priv->spec_config.fft_period = val;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_spectral_fft_period = अणु
	.पढ़ो = पढ़ो_file_spectral_fft_period,
	.ग_लिखो = ग_लिखो_file_spectral_fft_period,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/*******************/
/* Relay पूर्णांकerface */
/*******************/

अटल काष्ठा dentry *create_buf_file_handler(स्थिर अक्षर *filename,
					      काष्ठा dentry *parent,
					      umode_t mode,
					      काष्ठा rchan_buf *buf,
					      पूर्णांक *is_global)
अणु
	काष्ठा dentry *buf_file;

	buf_file = debugfs_create_file(filename, mode, parent, buf,
				       &relay_file_operations);
	अगर (IS_ERR(buf_file))
		वापस शून्य;

	*is_global = 1;
	वापस buf_file;
पूर्ण

अटल पूर्णांक हटाओ_buf_file_handler(काष्ठा dentry *dentry)
अणु
	debugfs_हटाओ(dentry);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rchan_callbacks rfs_spec_scan_cb = अणु
	.create_buf_file = create_buf_file_handler,
	.हटाओ_buf_file = हटाओ_buf_file_handler,
पूर्ण;

/*********************/
/* Debug Init/Deinit */
/*********************/

व्योम ath9k_cmn_spectral_deinit_debug(काष्ठा ath_spec_scan_priv *spec_priv)
अणु
	अगर (spec_priv->rfs_chan_spec_scan) अणु
		relay_बंद(spec_priv->rfs_chan_spec_scan);
		spec_priv->rfs_chan_spec_scan = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_spectral_deinit_debug);

व्योम ath9k_cmn_spectral_init_debug(काष्ठा ath_spec_scan_priv *spec_priv,
				   काष्ठा dentry *debugfs_phy)
अणु
	spec_priv->rfs_chan_spec_scan = relay_खोलो("spectral_scan",
					    debugfs_phy,
					    1024, 256, &rfs_spec_scan_cb,
					    शून्य);
	अगर (!spec_priv->rfs_chan_spec_scan)
		वापस;

	debugfs_create_file("spectral_scan_ctl",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spec_scan_ctl);
	debugfs_create_file("spectral_short_repeat",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_लघु_repeat);
	debugfs_create_file("spectral_count",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_count);
	debugfs_create_file("spectral_period",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_period);
	debugfs_create_file("spectral_fft_period",
			    0600,
			    debugfs_phy, spec_priv,
			    &fops_spectral_fft_period);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_spectral_init_debug);
