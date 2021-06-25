<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Neratec Solutions AG
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

#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश "ath9k.h"
#समावेश "dfs.h"
#समावेश "dfs_debug.h"

/* पूर्णांकernal काष्ठा to pass radar data */
काष्ठा ath_radar_data अणु
	u8 pulse_bw_info;
	u8 rssi;
	u8 ext_rssi;
	u8 pulse_length_ext;
	u8 pulse_length_pri;
पूर्ण;

/**** begin: CHIRP ************************************************************/

/* min and max gradients क्रम defined FCC chirping pulses, given by
 * - 20MHz chirp width over a pulse width of  50us
 * -  5MHz chirp width over a pulse width of 100us
 */
अटल स्थिर पूर्णांक BIN_DELTA_MIN		= 1;
अटल स्थिर पूर्णांक BIN_DELTA_MAX		= 10;

/* we need at least 3 deltas / 4 samples क्रम a reliable chirp detection */
#घोषणा NUM_DIFFS 3
#घोषणा FFT_NUM_SAMPLES		(NUM_DIFFS + 1)

/* Threshold क्रम dअगरference of delta peaks */
अटल स्थिर पूर्णांक MAX_DIFF		= 2;

/* width range to be checked क्रम chirping */
अटल स्थिर पूर्णांक MIN_CHIRP_PULSE_WIDTH	= 20;
अटल स्थिर पूर्णांक MAX_CHIRP_PULSE_WIDTH	= 110;

काष्ठा ath9k_dfs_fft_20 अणु
	u8 bin[28];
	u8 lower_bins[3];
पूर्ण __packed;
काष्ठा ath9k_dfs_fft_40 अणु
	u8 bin[64];
	u8 lower_bins[3];
	u8 upper_bins[3];
पूर्ण __packed;

अटल अंतरभूत पूर्णांक fft_max_index(u8 *bins)
अणु
	वापस (bins[2] & 0xfc) >> 2;
पूर्ण
अटल अंतरभूत पूर्णांक fft_max_magnitude(u8 *bins)
अणु
	वापस (bins[0] & 0xc0) >> 6 | bins[1] << 2 | (bins[2] & 0x03) << 10;
पूर्ण
अटल अंतरभूत u8 fft_biपंचांगap_weight(u8 *bins)
अणु
	वापस bins[0] & 0x3f;
पूर्ण

अटल पूर्णांक ath9k_get_max_index_ht40(काष्ठा ath9k_dfs_fft_40 *fft,
				    bool is_ctl, bool is_ext)
अणु
	स्थिर पूर्णांक DFS_UPPER_BIN_OFFSET = 64;
	/* अगर detected radar on both channels, select the signअगरicant one */
	अगर (is_ctl && is_ext) अणु
		/* first check wether channels have 'strong' bins */
		is_ctl = fft_biपंचांगap_weight(fft->lower_bins) != 0;
		is_ext = fft_biपंचांगap_weight(fft->upper_bins) != 0;

		/* अगर still unclear, take higher magnitude */
		अगर (is_ctl && is_ext) अणु
			पूर्णांक mag_lower = fft_max_magnitude(fft->lower_bins);
			पूर्णांक mag_upper = fft_max_magnitude(fft->upper_bins);
			अगर (mag_upper > mag_lower)
				is_ctl = false;
			अन्यथा
				is_ext = false;
		पूर्ण
	पूर्ण
	अगर (is_ctl)
		वापस fft_max_index(fft->lower_bins);
	वापस fft_max_index(fft->upper_bins) + DFS_UPPER_BIN_OFFSET;
पूर्ण
अटल bool ath9k_check_chirping(काष्ठा ath_softc *sc, u8 *data,
				 पूर्णांक datalen, bool is_ctl, bool is_ext)
अणु
	पूर्णांक i;
	पूर्णांक max_bin[FFT_NUM_SAMPLES];
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक prev_delta;

	अगर (IS_CHAN_HT40(ah->curchan)) अणु
		काष्ठा ath9k_dfs_fft_40 *fft = (काष्ठा ath9k_dfs_fft_40 *) data;
		पूर्णांक num_fft_packets = datalen / माप(*fft);
		अगर (num_fft_packets == 0)
			वापस false;

		ath_dbg(common, DFS, "HT40: datalen=%d, num_fft_packets=%d\n",
			datalen, num_fft_packets);
		अगर (num_fft_packets < FFT_NUM_SAMPLES) अणु
			ath_dbg(common, DFS, "not enough packets for chirp\n");
			वापस false;
		पूर्ण
		/* HW someबार adds 2 garbage bytes in front of FFT samples */
		अगर ((datalen % माप(*fft)) == 2) अणु
			fft = (काष्ठा ath9k_dfs_fft_40 *) (data + 2);
			ath_dbg(common, DFS, "fixing datalen by 2\n");
		पूर्ण
		अगर (IS_CHAN_HT40MINUS(ah->curchan))
			swap(is_ctl, is_ext);

		क्रम (i = 0; i < FFT_NUM_SAMPLES; i++)
			max_bin[i] = ath9k_get_max_index_ht40(fft + i, is_ctl,
							      is_ext);
	पूर्ण अन्यथा अणु
		काष्ठा ath9k_dfs_fft_20 *fft = (काष्ठा ath9k_dfs_fft_20 *) data;
		पूर्णांक num_fft_packets = datalen / माप(*fft);
		अगर (num_fft_packets == 0)
			वापस false;
		ath_dbg(common, DFS, "HT20: datalen=%d, num_fft_packets=%d\n",
			datalen, num_fft_packets);
		अगर (num_fft_packets < FFT_NUM_SAMPLES) अणु
			ath_dbg(common, DFS, "not enough packets for chirp\n");
			वापस false;
		पूर्ण
		/* in ht20, this is a 6-bit चिन्हित number => shअगरt it to 0 */
		क्रम (i = 0; i < FFT_NUM_SAMPLES; i++)
			max_bin[i] = fft_max_index(fft[i].lower_bins) ^ 0x20;
	पूर्ण
	ath_dbg(common, DFS, "bin_max = [%d, %d, %d, %d]\n",
		max_bin[0], max_bin[1], max_bin[2], max_bin[3]);

	/* Check क्रम chirp attributes within specs
	 * a) delta of adjacent max_bins is within range
	 * b) delta of adjacent deltas are within tolerance
	 */
	prev_delta = 0;
	क्रम (i = 0; i < NUM_DIFFS; i++) अणु
		पूर्णांक ddelta = -1;
		पूर्णांक delta = max_bin[i + 1] - max_bin[i];

		/* ensure gradient is within valid range */
		अगर (असल(delta) < BIN_DELTA_MIN || असल(delta) > BIN_DELTA_MAX) अणु
			ath_dbg(common, DFS, "CHIRP: invalid delta %d "
				"in sample %d\n", delta, i);
			वापस false;
		पूर्ण
		अगर (i == 0)
			जाओ करोne;
		ddelta = delta - prev_delta;
		अगर (असल(ddelta) > MAX_DIFF) अणु
			ath_dbg(common, DFS, "CHIRP: ddelta %d too high\n",
				ddelta);
			वापस false;
		पूर्ण
करोne:
		ath_dbg(common, DFS, "CHIRP - %d: delta=%d, ddelta=%d\n",
			i, delta, ddelta);
		prev_delta = delta;
	पूर्ण
	वापस true;
पूर्ण
/**** end: CHIRP **************************************************************/

/* convert pulse duration to usecs, considering घड़ी mode */
अटल u32 dur_to_usecs(काष्ठा ath_hw *ah, u32 dur)
अणु
	स्थिर u32 AR93X_NSECS_PER_DUR = 800;
	स्थिर u32 AR93X_NSECS_PER_DUR_FAST = (8000 / 11);
	u32 nsecs;

	अगर (IS_CHAN_A_FAST_CLOCK(ah, ah->curchan))
		nsecs = dur * AR93X_NSECS_PER_DUR_FAST;
	अन्यथा
		nsecs = dur * AR93X_NSECS_PER_DUR;

	वापस (nsecs + 500) / 1000;
पूर्ण

#घोषणा PRI_CH_RADAR_FOUND 0x01
#घोषणा EXT_CH_RADAR_FOUND 0x02
अटल bool
ath9k_postprocess_radar_event(काष्ठा ath_softc *sc,
			      काष्ठा ath_radar_data *ard,
			      काष्ठा pulse_event *pe)
अणु
	u8 rssi;
	u16 dur;

	/*
	 * Only the last 2 bits of the BW info are relevant, they indicate
	 * which channel the radar was detected in.
	 */
	ard->pulse_bw_info &= 0x03;

	चयन (ard->pulse_bw_info) अणु
	हाल PRI_CH_RADAR_FOUND:
		/* radar in ctrl channel */
		dur = ard->pulse_length_pri;
		DFS_STAT_INC(sc, pri_phy_errors);
		/*
		 * cannot use ctrl channel RSSI
		 * अगर extension channel is stronger
		 */
		rssi = (ard->ext_rssi >= (ard->rssi + 3)) ? 0 : ard->rssi;
		अवरोध;
	हाल EXT_CH_RADAR_FOUND:
		/* radar in extension channel */
		dur = ard->pulse_length_ext;
		DFS_STAT_INC(sc, ext_phy_errors);
		/*
		 * cannot use extension channel RSSI
		 * अगर control channel is stronger
		 */
		rssi = (ard->rssi >= (ard->ext_rssi + 12)) ? 0 : ard->ext_rssi;
		अवरोध;
	हाल (PRI_CH_RADAR_FOUND | EXT_CH_RADAR_FOUND):
		/*
		 * Conducted testing, when pulse is on DC, both pri and ext
		 * durations are reported to be same
		 *
		 * Radiated testing, when pulse is on DC, dअगरferent pri and
		 * ext durations are reported, so take the larger of the two
		 */
		अगर (ard->pulse_length_ext >= ard->pulse_length_pri)
			dur = ard->pulse_length_ext;
		अन्यथा
			dur = ard->pulse_length_pri;
		DFS_STAT_INC(sc, dc_phy_errors);

		/* when both are present use stronger one */
		rssi = (ard->rssi < ard->ext_rssi) ? ard->ext_rssi : ard->rssi;
		अवरोध;
	शेष:
		/*
		 * Bogus bandwidth info was received in descriptor,
		 * so ignore this PHY error
		 */
		DFS_STAT_INC(sc, bwinfo_discards);
		वापस false;
	पूर्ण

	अगर (rssi == 0) अणु
		DFS_STAT_INC(sc, rssi_discards);
		वापस false;
	पूर्ण

	/* convert duration to usecs */
	pe->width = dur_to_usecs(sc->sc_ah, dur);
	pe->rssi = rssi;

	DFS_STAT_INC(sc, pulses_detected);
	वापस true;
पूर्ण

अटल व्योम
ath9k_dfs_process_radar_pulse(काष्ठा ath_softc *sc, काष्ठा pulse_event *pe)
अणु
	काष्ठा dfs_pattern_detector *pd = sc->dfs_detector;
	DFS_STAT_INC(sc, pulses_processed);
	अगर (pd == शून्य)
		वापस;
	अगर (!pd->add_pulse(pd, pe, शून्य))
		वापस;
	DFS_STAT_INC(sc, radar_detected);
	ieee80211_radar_detected(sc->hw);
पूर्ण

/*
 * DFS: check PHY-error क्रम radar pulse and feed the detector
 */
व्योम ath9k_dfs_process_phyerr(काष्ठा ath_softc *sc, व्योम *data,
			      काष्ठा ath_rx_status *rs, u64 maस_समय)
अणु
	काष्ठा ath_radar_data ard;
	u16 datalen;
	अक्षर *vdata_end;
	काष्ठा pulse_event pe;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	DFS_STAT_INC(sc, pulses_total);
	अगर ((rs->rs_phyerr != ATH9K_PHYERR_RADAR) &&
	    (rs->rs_phyerr != ATH9K_PHYERR_FALSE_RADAR_EXT)) अणु
		ath_dbg(common, DFS,
			"Error: rs_phyer=0x%x not a radar error\n",
			rs->rs_phyerr);
		DFS_STAT_INC(sc, pulses_no_dfs);
		वापस;
	पूर्ण

	datalen = rs->rs_datalen;
	अगर (datalen == 0) अणु
		DFS_STAT_INC(sc, datalen_discards);
		वापस;
	पूर्ण

	ard.rssi = rs->rs_rssi_ctl[0];
	ard.ext_rssi = rs->rs_rssi_ext[0];

	/*
	 * hardware stores this as 8 bit चिन्हित value.
	 * we will cap it at 0 अगर it is a negative number
	 */
	अगर (ard.rssi & 0x80)
		ard.rssi = 0;
	अगर (ard.ext_rssi & 0x80)
		ard.ext_rssi = 0;

	vdata_end = data + datalen;
	ard.pulse_bw_info = vdata_end[-1];
	ard.pulse_length_ext = vdata_end[-2];
	ard.pulse_length_pri = vdata_end[-3];
	pe.freq = ah->curchan->channel;
	pe.ts = maस_समय;
	अगर (!ath9k_postprocess_radar_event(sc, &ard, &pe))
		वापस;

	अगर (pe.width > MIN_CHIRP_PULSE_WIDTH &&
	    pe.width < MAX_CHIRP_PULSE_WIDTH) अणु
		bool is_ctl = !!(ard.pulse_bw_info & PRI_CH_RADAR_FOUND);
		bool is_ext = !!(ard.pulse_bw_info & EXT_CH_RADAR_FOUND);
		पूर्णांक clen = datalen - 3;
		pe.chirp = ath9k_check_chirping(sc, data, clen, is_ctl, is_ext);
	पूर्ण अन्यथा अणु
		pe.chirp = false;
	पूर्ण

	ath_dbg(common, DFS,
		"ath9k_dfs_process_phyerr: type=%d, freq=%d, ts=%llu, "
		"width=%d, rssi=%d, delta_ts=%llu\n",
		ard.pulse_bw_info, pe.freq, pe.ts, pe.width, pe.rssi,
		pe.ts - sc->dfs_prev_pulse_ts);
	sc->dfs_prev_pulse_ts = pe.ts;
	अगर (ard.pulse_bw_info & PRI_CH_RADAR_FOUND)
		ath9k_dfs_process_radar_pulse(sc, &pe);
	अगर (IS_CHAN_HT40(ah->curchan) &&
	    ard.pulse_bw_info & EXT_CH_RADAR_FOUND) अणु
		pe.freq += IS_CHAN_HT40PLUS(ah->curchan) ? 20 : -20;
		ath9k_dfs_process_radar_pulse(sc, &pe);
	पूर्ण
पूर्ण
#अघोषित PRI_CH_RADAR_FOUND
#अघोषित EXT_CH_RADAR_FOUND
