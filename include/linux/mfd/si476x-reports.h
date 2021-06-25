<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/media/si476x-platक्रमm.h -- Definitions of the data क्रमmats
 * वापसed by debugfs hooks
 *
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#अगर_अघोषित __SI476X_REPORTS_H__
#घोषणा __SI476X_REPORTS_H__

/**
 * काष्ठा si476x_rsq_status - काष्ठाure containing received संकेत
 * quality
 * @multhपूर्णांक:   Multipath Detect High.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_MULTIPATH_HIGH_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_MULTIPATH_HIGH_THRESHOLD
 * @multlपूर्णांक:   Multipath Detect Low.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_MULTIPATH_LOW_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_MULTIPATH_LOW_THRESHOLD
 * @snrhपूर्णांक:    SNR Detect High.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_SNR_HIGH_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_SNR_HIGH_THRESHOLD
 * @snrlपूर्णांक:    SNR Detect Low.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_SNR_LOW_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_SNR_LOW_THRESHOLD
 * @rssihपूर्णांक:   RSSI Detect High.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_RSSI_HIGH_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_RSSI_HIGH_THRESHOLD
 * @rssilपूर्णांक:   RSSI Detect Low.
 *              true  - Indicatedes that the value is below
 *                      FM_RSQ_RSSI_LOW_THRESHOLD
 *              false - Indicatedes that the value is above
 *                      FM_RSQ_RSSI_LOW_THRESHOLD
 * @bltf:       Band Limit.
 *              Set अगर seek command hits the band limit or wrapped to
 *              the original frequency.
 * @snr_पढ़ोy:  SNR measurement in progress.
 * @rssiपढ़ोy:  RSSI measurement in progress.
 * @afcrl:      Set अगर FREQOFF >= MAX_TUNE_ERROR
 * @valid:      Set अगर the channel is valid
 *               rssi < FM_VALID_RSSI_THRESHOLD
 *               snr  < FM_VALID_SNR_THRESHOLD
 *               tune_error < FM_VALID_MAX_TUNE_ERROR
 * @पढ़ोfreq:   Current tuned frequency.
 * @freqoff:    Signed frequency offset.
 * @rssi:       Received Signal Strength Indicator(dBuV).
 * @snr:        RF SNR Indicator(dB).
 * @lassi:
 * @hassi:      Low/High side Adjacent(100 kHz) Channel Strength Indicator
 * @mult:       Multipath indicator
 * @dev:        Who knows? But values may vary.
 * @पढ़ोantcap: Antenna tuning capacity value.
 * @assi:       Adjacent Channel(+/- 200kHz) Strength Indicator
 * @usn:        Ultrasonic Noise Inticator in -DBFS
 */
काष्ठा si476x_rsq_status_report अणु
	__u8 multhपूर्णांक, multlपूर्णांक;
	__u8 snrhपूर्णांक,  snrlपूर्णांक;
	__u8 rssihपूर्णांक, rssilपूर्णांक;
	__u8 bltf;
	__u8 snr_पढ़ोy;
	__u8 rssiपढ़ोy;
	__u8 injside;
	__u8 afcrl;
	__u8 valid;

	__u16 पढ़ोfreq;
	__s8  freqoff;
	__s8  rssi;
	__s8  snr;
	__s8  issi;
	__s8  lassi, hassi;
	__s8  mult;
	__u8  dev;
	__u16 पढ़ोantcap;
	__s8  assi;
	__s8  usn;

	__u8 pilotdev;
	__u8 rdsdev;
	__u8 assidev;
	__u8 strongdev;
	__u16 rdspi;
पूर्ण __packed;

/**
 * si476x_acf_status_report - ACF report results
 *
 * @blend_पूर्णांक: If set, indicates that stereo separation has crossed
 * below the blend threshold as set by FM_ACF_BLEND_THRESHOLD
 * @hblend_पूर्णांक: If set, indicates that HiBlend cutoff frequency is
 * lower than threshold as set by FM_ACF_HBLEND_THRESHOLD
 * @hicut_पूर्णांक:  If set, indicates that HiCut cutoff frequency is lower
 * than the threshold set by ACF_

 */
काष्ठा si476x_acf_status_report अणु
	__u8 blend_पूर्णांक;
	__u8 hblend_पूर्णांक;
	__u8 hicut_पूर्णांक;
	__u8 chbw_पूर्णांक;
	__u8 sofपंचांगute_पूर्णांक;
	__u8 smute;
	__u8 smattn;
	__u8 chbw;
	__u8 hicut;
	__u8 hiblend;
	__u8 pilot;
	__u8 stblend;
पूर्ण __packed;

क्रमागत si476x_fmagc अणु
	SI476X_FMAGC_10K_OHM	= 0,
	SI476X_FMAGC_800_OHM	= 1,
	SI476X_FMAGC_400_OHM	= 2,
	SI476X_FMAGC_200_OHM	= 4,
	SI476X_FMAGC_100_OHM	= 8,
	SI476X_FMAGC_50_OHM	= 16,
	SI476X_FMAGC_25_OHM	= 32,
	SI476X_FMAGC_12P5_OHM	= 64,
	SI476X_FMAGC_6P25_OHM	= 128,
पूर्ण;

काष्ठा si476x_agc_status_report अणु
	__u8 mxhi;
	__u8 mxlo;
	__u8 lnahi;
	__u8 lnalo;
	__u8 fmagc1;
	__u8 fmagc2;
	__u8 pgagain;
	__u8 fmwblang;
पूर्ण __packed;

काष्ठा si476x_rds_blockcount_report अणु
	__u16 expected;
	__u16 received;
	__u16 uncorrectable;
पूर्ण __packed;

#पूर्ण_अगर  /* __SI476X_REPORTS_H__ */
