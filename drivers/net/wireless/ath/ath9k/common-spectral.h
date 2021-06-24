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

#अगर_अघोषित SPECTRAL_H
#घोषणा SPECTRAL_H

#समावेश "../spectral_common.h"

/* क्रमागत spectral_mode:
 *
 * @SPECTRAL_DISABLED: spectral mode is disabled
 * @SPECTRAL_BACKGROUND: hardware sends samples when it is not busy with
 *	something अन्यथा.
 * @SPECTRAL_MANUAL: spectral scan is enabled, triggering क्रम samples
 *	is perक्रमmed manually.
 * @SPECTRAL_CHANSCAN: Like manual, but also triggered when changing channels
 *	during a channel scan.
 */
क्रमागत spectral_mode अणु
	SPECTRAL_DISABLED = 0,
	SPECTRAL_BACKGROUND,
	SPECTRAL_MANUAL,
	SPECTRAL_CHANSCAN,
पूर्ण;

#घोषणा SPECTRAL_SCAN_BITMASK		0x10
/* Radar info packet क्रमmat, used क्रम DFS and spectral क्रमmats. */
काष्ठा ath_radar_info अणु
	u8 pulse_length_pri;
	u8 pulse_length_ext;
	u8 pulse_bw_info;
पूर्ण __packed;

/* The HT20 spectral data has 4 bytes of additional inक्रमmation at it's end.
 *
 * [7:0]: all bins अणुmax_magnitude[1:0], biपंचांगap_weight[5:0]पूर्ण
 * [7:0]: all bins  max_magnitude[9:2]
 * [7:0]: all bins अणुmax_index[5:0], max_magnitude[11:10]पूर्ण
 * [3:0]: max_exp (shअगरt amount to size max bin to 8-bit अचिन्हित)
 */
काष्ठा ath_ht20_mag_info अणु
	u8 all_bins[3];
	u8 max_exp;
पूर्ण __packed;

/* WARNING: करोn't actually use this काष्ठा! MAC may vary the amount of
 * data by -1/+2. This काष्ठा is क्रम reference only.
 */
काष्ठा ath_ht20_fft_packet अणु
	u8 data[SPECTRAL_HT20_NUM_BINS];
	काष्ठा ath_ht20_mag_info mag_info;
	काष्ठा ath_radar_info radar_info;
पूर्ण __packed;

#घोषणा SPECTRAL_HT20_TOTAL_DATA_LEN	(माप(काष्ठा ath_ht20_fft_packet))
#घोषणा	SPECTRAL_HT20_SAMPLE_LEN	(माप(काष्ठा ath_ht20_mag_info) +\
					SPECTRAL_HT20_NUM_BINS)

/* Dynamic 20/40 mode:
 *
 * [7:0]: lower bins अणुmax_magnitude[1:0], biपंचांगap_weight[5:0]पूर्ण
 * [7:0]: lower bins  max_magnitude[9:2]
 * [7:0]: lower bins अणुmax_index[5:0], max_magnitude[11:10]पूर्ण
 * [7:0]: upper bins अणुmax_magnitude[1:0], biपंचांगap_weight[5:0]पूर्ण
 * [7:0]: upper bins  max_magnitude[9:2]
 * [7:0]: upper bins अणुmax_index[5:0], max_magnitude[11:10]पूर्ण
 * [3:0]: max_exp (shअगरt amount to size max bin to 8-bit अचिन्हित)
 */
काष्ठा ath_ht20_40_mag_info अणु
	u8 lower_bins[3];
	u8 upper_bins[3];
	u8 max_exp;
पूर्ण __packed;

/* WARNING: करोn't actually use this काष्ठा! MAC may vary the amount of
 * data. This काष्ठा is क्रम reference only.
 */
काष्ठा ath_ht20_40_fft_packet अणु
	u8 data[SPECTRAL_HT20_40_NUM_BINS];
	काष्ठा ath_ht20_40_mag_info mag_info;
	काष्ठा ath_radar_info radar_info;
पूर्ण __packed;

काष्ठा ath_spec_scan_priv अणु
	काष्ठा ath_hw *ah;
	/* relay(fs) channel क्रम spectral scan */
	काष्ठा rchan *rfs_chan_spec_scan;
	क्रमागत spectral_mode spectral_mode;
	काष्ठा ath_spec_scan spec_config;
पूर्ण;

#घोषणा SPECTRAL_HT20_40_TOTAL_DATA_LEN	(माप(काष्ठा ath_ht20_40_fft_packet))
#घोषणा	SPECTRAL_HT20_40_SAMPLE_LEN	(माप(काष्ठा ath_ht20_40_mag_info) +\
					SPECTRAL_HT20_40_NUM_BINS)

#घोषणा	SPECTRAL_SAMPLE_MAX_LEN		SPECTRAL_HT20_40_SAMPLE_LEN

/* grअसल the max magnitude from the all/upper/lower bins */
अटल अंतरभूत u16 spectral_max_magnitude(u8 *bins)
अणु
	वापस (bins[0] & 0xc0) >> 6 |
	       (bins[1] & 0xff) << 2 |
	       (bins[2] & 0x03) << 10;
पूर्ण

/* वापस the max magnitude from the all/upper/lower bins */
अटल अंतरभूत u8 spectral_max_index(u8 *bins, पूर्णांक num_bins)
अणु
	s8 m = (bins[2] & 0xfc) >> 2;
	u8 zero_idx = num_bins / 2;

	/* It's a 5 bit signed int, remove its sign and use one's
	 * complement पूर्णांकerpretation to add the sign back to the 8
	 * bit पूर्णांक
	 */
	अगर (m & 0x20) अणु
		m &= ~0x20;
		m |= 0xe0;
	पूर्ण

	/* Bring the zero poपूर्णांक to the beginning
	 * instead of the middle so that we can use
	 * it क्रम array lookup and that we करोn't deal
	 * with negative values later
	 */
	m += zero_idx;

	/* Sanity check to make sure index is within bounds */
	अगर (m < 0 || m > num_bins - 1)
		m = 0;

	वापस m;
पूर्ण

अटल अंतरभूत u8 spectral_max_index_ht40(u8 *bins)
अणु
	u8 idx;

	idx = spectral_max_index(bins, SPECTRAL_HT20_40_NUM_BINS);

	/* positive values and zero are starting at the beginning
	 * of the data field.
	 */
	वापस idx % (SPECTRAL_HT20_40_NUM_BINS / 2);
पूर्ण

अटल अंतरभूत u8 spectral_max_index_ht20(u8 *bins)
अणु
	वापस spectral_max_index(bins, SPECTRAL_HT20_NUM_BINS);
पूर्ण

/* वापस the biपंचांगap weight from the all/upper/lower bins */
अटल अंतरभूत u8 spectral_biपंचांगap_weight(u8 *bins)
अणु
	वापस bins[0] & 0x3f;
पूर्ण

#अगर_घोषित CONFIG_ATH9K_COMMON_SPECTRAL
व्योम ath9k_cmn_spectral_init_debug(काष्ठा ath_spec_scan_priv *spec_priv, काष्ठा dentry *debugfs_phy);
व्योम ath9k_cmn_spectral_deinit_debug(काष्ठा ath_spec_scan_priv *spec_priv);

व्योम ath9k_cmn_spectral_scan_trigger(काष्ठा ath_common *common,
				 काष्ठा ath_spec_scan_priv *spec_priv);
पूर्णांक ath9k_cmn_spectral_scan_config(काष्ठा ath_common *common,
			       काष्ठा ath_spec_scan_priv *spec_priv,
			       क्रमागत spectral_mode spectral_mode);
पूर्णांक ath_cmn_process_fft(काष्ठा ath_spec_scan_priv *spec_priv, काष्ठा ieee80211_hdr *hdr,
		    काष्ठा ath_rx_status *rs, u64 tsf);
#अन्यथा
अटल अंतरभूत व्योम ath9k_cmn_spectral_init_debug(काष्ठा ath_spec_scan_priv *spec_priv,
						 काष्ठा dentry *debugfs_phy)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_cmn_spectral_deinit_debug(काष्ठा ath_spec_scan_priv *spec_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_cmn_spectral_scan_trigger(काष्ठा ath_common *common,
						   काष्ठा ath_spec_scan_priv *spec_priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath_cmn_process_fft(काष्ठा ath_spec_scan_priv *spec_priv,
				      काष्ठा ieee80211_hdr *hdr,
				      काष्ठा ath_rx_status *rs, u64 tsf)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_COMMON_SPECTRAL */

#पूर्ण_अगर /* SPECTRAL_H */
