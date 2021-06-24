<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
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

#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>

#समावेश "d11.h"
#समावेश "pub.h"
#समावेश "rate.h"

/*
 * Rate info per rate: It tells whether a rate is ofdm or not and its phy_rate
 * value
 */
स्थिर u8 rate_info[BRCM_MAXRATE + 1] = अणु
	/*  0     1     2     3     4     5     6     7     8     9 */
/*   0 */ 0x00, 0x00, 0x0a, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  10 */ 0x00, 0x37, 0x8b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0x00,
/*  20 */ 0x00, 0x00, 0x6e, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  30 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0x00, 0x00, 0x00,
/*  40 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x89, 0x00,
/*  50 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  60 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  70 */ 0x00, 0x00, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  80 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00,
/* 100 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c
पूर्ण;

/* rates are in units of Kbps */
स्थिर काष्ठा brcms_mcs_info mcs_table[MCS_TABLE_SIZE] = अणु
	/* MCS  0: SS 1, MOD: BPSK,  CR 1/2 */
	अणु6500, 13500, CEIL(6500 * 10, 9), CEIL(13500 * 10, 9), 0x00,
	 BRCM_RATE_6Mपूर्ण,
	/* MCS  1: SS 1, MOD: QPSK,  CR 1/2 */
	अणु13000, 27000, CEIL(13000 * 10, 9), CEIL(27000 * 10, 9), 0x08,
	 BRCM_RATE_12Mपूर्ण,
	/* MCS  2: SS 1, MOD: QPSK,  CR 3/4 */
	अणु19500, 40500, CEIL(19500 * 10, 9), CEIL(40500 * 10, 9), 0x0A,
	 BRCM_RATE_18Mपूर्ण,
	/* MCS  3: SS 1, MOD: 16QAM, CR 1/2 */
	अणु26000, 54000, CEIL(26000 * 10, 9), CEIL(54000 * 10, 9), 0x10,
	 BRCM_RATE_24Mपूर्ण,
	/* MCS  4: SS 1, MOD: 16QAM, CR 3/4 */
	अणु39000, 81000, CEIL(39000 * 10, 9), CEIL(81000 * 10, 9), 0x12,
	 BRCM_RATE_36Mपूर्ण,
	/* MCS  5: SS 1, MOD: 64QAM, CR 2/3 */
	अणु52000, 108000, CEIL(52000 * 10, 9), CEIL(108000 * 10, 9), 0x19,
	 BRCM_RATE_48Mपूर्ण,
	/* MCS  6: SS 1, MOD: 64QAM, CR 3/4 */
	अणु58500, 121500, CEIL(58500 * 10, 9), CEIL(121500 * 10, 9), 0x1A,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS  7: SS 1, MOD: 64QAM, CR 5/6 */
	अणु65000, 135000, CEIL(65000 * 10, 9), CEIL(135000 * 10, 9), 0x1C,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS  8: SS 2, MOD: BPSK,  CR 1/2 */
	अणु13000, 27000, CEIL(13000 * 10, 9), CEIL(27000 * 10, 9), 0x40,
	 BRCM_RATE_6Mपूर्ण,
	/* MCS  9: SS 2, MOD: QPSK,  CR 1/2 */
	अणु26000, 54000, CEIL(26000 * 10, 9), CEIL(54000 * 10, 9), 0x48,
	 BRCM_RATE_12Mपूर्ण,
	/* MCS 10: SS 2, MOD: QPSK,  CR 3/4 */
	अणु39000, 81000, CEIL(39000 * 10, 9), CEIL(81000 * 10, 9), 0x4A,
	 BRCM_RATE_18Mपूर्ण,
	/* MCS 11: SS 2, MOD: 16QAM, CR 1/2 */
	अणु52000, 108000, CEIL(52000 * 10, 9), CEIL(108000 * 10, 9), 0x50,
	 BRCM_RATE_24Mपूर्ण,
	/* MCS 12: SS 2, MOD: 16QAM, CR 3/4 */
	अणु78000, 162000, CEIL(78000 * 10, 9), CEIL(162000 * 10, 9), 0x52,
	 BRCM_RATE_36Mपूर्ण,
	/* MCS 13: SS 2, MOD: 64QAM, CR 2/3 */
	अणु104000, 216000, CEIL(104000 * 10, 9), CEIL(216000 * 10, 9), 0x59,
	 BRCM_RATE_48Mपूर्ण,
	/* MCS 14: SS 2, MOD: 64QAM, CR 3/4 */
	अणु117000, 243000, CEIL(117000 * 10, 9), CEIL(243000 * 10, 9), 0x5A,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 15: SS 2, MOD: 64QAM, CR 5/6 */
	अणु130000, 270000, CEIL(130000 * 10, 9), CEIL(270000 * 10, 9), 0x5C,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 16: SS 3, MOD: BPSK,  CR 1/2 */
	अणु19500, 40500, CEIL(19500 * 10, 9), CEIL(40500 * 10, 9), 0x80,
	 BRCM_RATE_6Mपूर्ण,
	/* MCS 17: SS 3, MOD: QPSK,  CR 1/2 */
	अणु39000, 81000, CEIL(39000 * 10, 9), CEIL(81000 * 10, 9), 0x88,
	 BRCM_RATE_12Mपूर्ण,
	/* MCS 18: SS 3, MOD: QPSK,  CR 3/4 */
	अणु58500, 121500, CEIL(58500 * 10, 9), CEIL(121500 * 10, 9), 0x8A,
	 BRCM_RATE_18Mपूर्ण,
	/* MCS 19: SS 3, MOD: 16QAM, CR 1/2 */
	अणु78000, 162000, CEIL(78000 * 10, 9), CEIL(162000 * 10, 9), 0x90,
	 BRCM_RATE_24Mपूर्ण,
	/* MCS 20: SS 3, MOD: 16QAM, CR 3/4 */
	अणु117000, 243000, CEIL(117000 * 10, 9), CEIL(243000 * 10, 9), 0x92,
	 BRCM_RATE_36Mपूर्ण,
	/* MCS 21: SS 3, MOD: 64QAM, CR 2/3 */
	अणु156000, 324000, CEIL(156000 * 10, 9), CEIL(324000 * 10, 9), 0x99,
	 BRCM_RATE_48Mपूर्ण,
	/* MCS 22: SS 3, MOD: 64QAM, CR 3/4 */
	अणु175500, 364500, CEIL(175500 * 10, 9), CEIL(364500 * 10, 9), 0x9A,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 23: SS 3, MOD: 64QAM, CR 5/6 */
	अणु195000, 405000, CEIL(195000 * 10, 9), CEIL(405000 * 10, 9), 0x9B,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 24: SS 4, MOD: BPSK,  CR 1/2 */
	अणु26000, 54000, CEIL(26000 * 10, 9), CEIL(54000 * 10, 9), 0xC0,
	 BRCM_RATE_6Mपूर्ण,
	/* MCS 25: SS 4, MOD: QPSK,  CR 1/2 */
	अणु52000, 108000, CEIL(52000 * 10, 9), CEIL(108000 * 10, 9), 0xC8,
	 BRCM_RATE_12Mपूर्ण,
	/* MCS 26: SS 4, MOD: QPSK,  CR 3/4 */
	अणु78000, 162000, CEIL(78000 * 10, 9), CEIL(162000 * 10, 9), 0xCA,
	 BRCM_RATE_18Mपूर्ण,
	/* MCS 27: SS 4, MOD: 16QAM, CR 1/2 */
	अणु104000, 216000, CEIL(104000 * 10, 9), CEIL(216000 * 10, 9), 0xD0,
	 BRCM_RATE_24Mपूर्ण,
	/* MCS 28: SS 4, MOD: 16QAM, CR 3/4 */
	अणु156000, 324000, CEIL(156000 * 10, 9), CEIL(324000 * 10, 9), 0xD2,
	 BRCM_RATE_36Mपूर्ण,
	/* MCS 29: SS 4, MOD: 64QAM, CR 2/3 */
	अणु208000, 432000, CEIL(208000 * 10, 9), CEIL(432000 * 10, 9), 0xD9,
	 BRCM_RATE_48Mपूर्ण,
	/* MCS 30: SS 4, MOD: 64QAM, CR 3/4 */
	अणु234000, 486000, CEIL(234000 * 10, 9), CEIL(486000 * 10, 9), 0xDA,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 31: SS 4, MOD: 64QAM, CR 5/6 */
	अणु260000, 540000, CEIL(260000 * 10, 9), CEIL(540000 * 10, 9), 0xDB,
	 BRCM_RATE_54Mपूर्ण,
	/* MCS 32: SS 1, MOD: BPSK,  CR 1/2 */
	अणु0, 6000, 0, CEIL(6000 * 10, 9), 0x00, BRCM_RATE_6Mपूर्ण,
पूर्ण;

/*
 * phycfg क्रम legacy OFDM frames: code rate, modulation scheme, spatial streams
 * Number of spatial streams: always 1 other fields: refer to table 78 of
 * section 17.3.2.2 of the original .11a standard
 */
काष्ठा legacy_phycfg अणु
	u32 rate_ofdm;	/* ofdm mac rate */
	/* phy ctl byte 3, code rate, modulation type, # of streams */
	u8 tx_phy_ctl3;
पूर्ण;

/* Number of legacy_rate_cfg entries in the table */
#घोषणा LEGACY_PHYCFG_TABLE_SIZE	12

/*
 * In CCK mode LPPHY overloads OFDM Modulation bits with CCK Data Rate
 * Eventually MIMOPHY would also be converted to this क्रमmat
 * 0 = 1Mbps; 1 = 2Mbps; 2 = 5.5Mbps; 3 = 11Mbps
 */
अटल स्थिर काष्ठा
legacy_phycfg legacy_phycfg_table[LEGACY_PHYCFG_TABLE_SIZE] = अणु
	अणुBRCM_RATE_1M, 0x00पूर्ण,	/* CCK  1Mbps,  data rate  0 */
	अणुBRCM_RATE_2M, 0x08पूर्ण,	/* CCK  2Mbps,  data rate  1 */
	अणुBRCM_RATE_5M5, 0x10पूर्ण,	/* CCK  5.5Mbps,  data rate  2 */
	अणुBRCM_RATE_11M, 0x18पूर्ण,	/* CCK  11Mbps,  data rate   3 */
	/* OFDM  6Mbps,  code rate 1/2, BPSK,   1 spatial stream */
	अणुBRCM_RATE_6M, 0x00पूर्ण,
	/* OFDM  9Mbps,  code rate 3/4, BPSK,   1 spatial stream */
	अणुBRCM_RATE_9M, 0x02पूर्ण,
	/* OFDM  12Mbps, code rate 1/2, QPSK,   1 spatial stream */
	अणुBRCM_RATE_12M, 0x08पूर्ण,
	/* OFDM  18Mbps, code rate 3/4, QPSK,   1 spatial stream */
	अणुBRCM_RATE_18M, 0x0Aपूर्ण,
	/* OFDM  24Mbps, code rate 1/2, 16-QAM, 1 spatial stream */
	अणुBRCM_RATE_24M, 0x10पूर्ण,
	/* OFDM  36Mbps, code rate 3/4, 16-QAM, 1 spatial stream */
	अणुBRCM_RATE_36M, 0x12पूर्ण,
	/* OFDM  48Mbps, code rate 2/3, 64-QAM, 1 spatial stream */
	अणुBRCM_RATE_48M, 0x19पूर्ण,
	/* OFDM  54Mbps, code rate 3/4, 64-QAM, 1 spatial stream */
	अणुBRCM_RATE_54M, 0x1Aपूर्ण,
पूर्ण;

/* Hardware rates (also encodes शेष basic rates) */

स्थिर काष्ठा brcms_c_rateset cck_ofdm_mimo_rates = अणु
	12,
	/*  1b,   2b,   5.5b, 6,    9,    11b,  12,   18,   24,   36,   48, */
	अणु 0x82, 0x84, 0x8b, 0x0c, 0x12, 0x96, 0x18, 0x24, 0x30, 0x48, 0x60,
	/* 54 Mbps */
	  0x6cपूर्ण,
	0x00,
	अणु 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

स्थिर काष्ठा brcms_c_rateset ofdm_mimo_rates = अणु
	8,
	/*  6b,   9,    12b,  18,   24b,  36,   48,   54 Mbps */
	अणु 0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6cपूर्ण,
	0x00,
	अणु 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

/* Default ratesets that include MCS32 क्रम 40BW channels */
अटल स्थिर काष्ठा brcms_c_rateset cck_ofdm_40bw_mimo_rates = अणु
	12,
	/*  1b,   2b,   5.5b, 6,    9,    11b,  12,   18,   24,   36,   48 */
	अणु 0x82, 0x84, 0x8b, 0x0c, 0x12, 0x96, 0x18, 0x24, 0x30, 0x48, 0x60,
	/* 54 Mbps */
	  0x6cपूर्ण,
	0x00,
	अणु 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा brcms_c_rateset ofdm_40bw_mimo_rates = अणु
	8,
	/*  6b,   9,    12b,  18,   24b,  36,   48,   54 Mbps */
	अणु 0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6cपूर्ण,
	0x00,
	अणु 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

स्थिर काष्ठा brcms_c_rateset cck_ofdm_rates = अणु
	12,
	/*  1b,   2b, 5.5b, 6,    9,    11b,  12,   18,   24,   36,   48,*/
	अणु 0x82, 0x84, 0x8b, 0x0c, 0x12, 0x96, 0x18, 0x24, 0x30, 0x48, 0x60,
	/*54 Mbps */
	  0x6cपूर्ण,
	0x00,
	अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

स्थिर काष्ठा brcms_c_rateset gphy_legacy_rates = अणु
	4,
	/*  1b,   2b,   5.5b, 11b Mbps */
	अणु 0x82, 0x84, 0x8b, 0x96पूर्ण,
	0x00,
	अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

स्थिर काष्ठा brcms_c_rateset ofdm_rates = अणु
	8,
	/*  6b,   9,    12b,  18,   24b,  36,   48,   54 Mbps */
	अणु 0x8c, 0x12, 0x98, 0x24, 0xb0, 0x48, 0x60, 0x6cपूर्ण,
	0x00,
	अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

स्थिर काष्ठा brcms_c_rateset cck_rates = अणु
	4,
	/*  1b,   2b,   5.5,  11 Mbps */
	अणु 0x82, 0x84, 0x0b, 0x16पूर्ण,
	0x00,
	अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

/* check अगर rateset is valid.
 * अगर check_brate is true, rateset without a basic rate is considered NOT valid.
 */
अटल bool brcms_c_rateset_valid(काष्ठा brcms_c_rateset *rs, bool check_brate)
अणु
	uपूर्णांक idx;

	अगर (!rs->count)
		वापस false;

	अगर (!check_brate)
		वापस true;

	/* error अगर no basic rates */
	क्रम (idx = 0; idx < rs->count; idx++) अणु
		अगर (rs->rates[idx] & BRCMS_RATE_FLAG)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम brcms_c_rateset_mcs_upd(काष्ठा brcms_c_rateset *rs, u8 txstreams)
अणु
	पूर्णांक i;
	क्रम (i = txstreams; i < MAX_STREAMS_SUPPORTED; i++)
		rs->mcs[i] = 0;
पूर्ण

/*
 * filter based on hardware rateset, and sort filtered rateset with basic
 * bit(s) preserved, and check अगर resulting rateset is valid.
*/
bool
brcms_c_rate_hwrs_filter_sort_validate(काष्ठा brcms_c_rateset *rs,
				   स्थिर काष्ठा brcms_c_rateset *hw_rs,
				   bool check_brate, u8 txstreams)
अणु
	u8 rateset[BRCM_MAXRATE + 1];
	u8 r;
	uपूर्णांक count;
	uपूर्णांक i;

	स_रखो(rateset, 0, माप(rateset));
	count = rs->count;

	क्रम (i = 0; i < count; i++) अणु
		/* mask off "basic rate" bit, BRCMS_RATE_FLAG */
		r = (पूर्णांक)rs->rates[i] & BRCMS_RATE_MASK;
		अगर ((r > BRCM_MAXRATE) || (rate_info[r] == 0))
			जारी;
		rateset[r] = rs->rates[i];	/* preserve basic bit! */
	पूर्ण

	/* fill out the rates in order, looking at only supported rates */
	count = 0;
	क्रम (i = 0; i < hw_rs->count; i++) अणु
		r = hw_rs->rates[i] & BRCMS_RATE_MASK;
		अगर (rateset[r])
			rs->rates[count++] = rateset[r];
	पूर्ण

	rs->count = count;

	/* only set the mcs rate bit अगर the equivalent hw mcs bit is set */
	क्रम (i = 0; i < MCSSET_LEN; i++)
		rs->mcs[i] = (rs->mcs[i] & hw_rs->mcs[i]);

	अगर (brcms_c_rateset_valid(rs, check_brate))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* calculate the rate of a rx'd frame and वापस it as a ratespec */
u32 brcms_c_compute_rspec(काष्ठा d11rxhdr *rxh, u8 *plcp)
अणु
	पूर्णांक phy_type;
	u32 rspec = PHY_TXC1_BW_20MHZ << RSPEC_BW_SHIFT;

	phy_type =
	    ((rxh->RxChan & RXS_CHAN_PHYTYPE_MASK) >> RXS_CHAN_PHYTYPE_SHIFT);

	अगर ((phy_type == PHY_TYPE_N) || (phy_type == PHY_TYPE_SSN) ||
	    (phy_type == PHY_TYPE_LCN) || (phy_type == PHY_TYPE_HT)) अणु
		चयन (rxh->PhyRxStatus_0 & PRXS0_FT_MASK) अणु
		हाल PRXS0_CCK:
			rspec =
				cck_phy2mac_rate(
				((काष्ठा cck_phy_hdr *) plcp)->संकेत);
			अवरोध;
		हाल PRXS0_OFDM:
			rspec =
			    ofdm_phy2mac_rate(
				((काष्ठा ofdm_phy_hdr *) plcp)->rlpt[0]);
			अवरोध;
		हाल PRXS0_PREN:
			rspec = (plcp[0] & MIMO_PLCP_MCS_MASK) | RSPEC_MIMORATE;
			अगर (plcp[0] & MIMO_PLCP_40MHZ) अणु
				/* indicate rspec is क्रम 40 MHz mode */
				rspec &= ~RSPEC_BW_MASK;
				rspec |= (PHY_TXC1_BW_40MHZ << RSPEC_BW_SHIFT);
			पूर्ण
			अवरोध;
		हाल PRXS0_STDN:
			/* fallthru */
		शेष:
			/* not supported, error condition */
			अवरोध;
		पूर्ण
		अगर (plcp3_issgi(plcp[3]))
			rspec |= RSPEC_SHORT_GI;
	पूर्ण अन्यथा
	    अगर ((phy_type == PHY_TYPE_A) || (rxh->PhyRxStatus_0 & PRXS0_OFDM))
		rspec = ofdm_phy2mac_rate(
				((काष्ठा ofdm_phy_hdr *) plcp)->rlpt[0]);
	अन्यथा
		rspec = cck_phy2mac_rate(
				((काष्ठा cck_phy_hdr *) plcp)->संकेत);

	वापस rspec;
पूर्ण

/* copy rateset src to dst as-is (no masking or sorting) */
व्योम brcms_c_rateset_copy(स्थिर काष्ठा brcms_c_rateset *src,
			  काष्ठा brcms_c_rateset *dst)
अणु
	स_नकल(dst, src, माप(काष्ठा brcms_c_rateset));
पूर्ण

/*
 * Copy and selectively filter one rateset to another.
 * 'basic_only' means only copy basic rates.
 * 'rates' indicates cck (11b) and ofdm rates combinations.
 *    - 0: cck and ofdm
 *    - 1: cck only
 *    - 2: ofdm only
 * 'xmask' is the copy mask (typically 0x7f or 0xff).
 */
व्योम
brcms_c_rateset_filter(काष्ठा brcms_c_rateset *src, काष्ठा brcms_c_rateset *dst,
		       bool basic_only, u8 rates, uपूर्णांक xmask, bool mcsallow)
अणु
	uपूर्णांक i;
	uपूर्णांक r;
	uपूर्णांक count;

	count = 0;
	क्रम (i = 0; i < src->count; i++) अणु
		r = src->rates[i];
		अगर (basic_only && !(r & BRCMS_RATE_FLAG))
			जारी;
		अगर (rates == BRCMS_RATES_CCK &&
		    is_ofdm_rate((r & BRCMS_RATE_MASK)))
			जारी;
		अगर (rates == BRCMS_RATES_OFDM &&
		    is_cck_rate((r & BRCMS_RATE_MASK)))
			जारी;
		dst->rates[count++] = r & xmask;
	पूर्ण
	dst->count = count;
	dst->htphy_membership = src->htphy_membership;

	अगर (mcsallow && rates != BRCMS_RATES_CCK)
		स_नकल(&dst->mcs[0], &src->mcs[0], MCSSET_LEN);
	अन्यथा
		brcms_c_rateset_mcs_clear(dst);
पूर्ण

/* select rateset क्रम a given phy_type and bandtype and filter it, sort it
 * and fill rs_tgt with result
 */
व्योम
brcms_c_rateset_शेष(काष्ठा brcms_c_rateset *rs_tgt,
			स्थिर काष्ठा brcms_c_rateset *rs_hw,
			uपूर्णांक phy_type, पूर्णांक bandtype, bool cck_only,
			uपूर्णांक rate_mask, bool mcsallow, u8 bw, u8 txstreams)
अणु
	स्थिर काष्ठा brcms_c_rateset *rs_dflt;
	काष्ठा brcms_c_rateset rs_sel;
	अगर ((PHYTYPE_IS(phy_type, PHY_TYPE_HT)) ||
	    (PHYTYPE_IS(phy_type, PHY_TYPE_N)) ||
	    (PHYTYPE_IS(phy_type, PHY_TYPE_LCN)) ||
	    (PHYTYPE_IS(phy_type, PHY_TYPE_SSN))) अणु
		अगर (bandtype == BRCM_BAND_5G)
			rs_dflt = (bw == BRCMS_20_MHZ ?
				   &ofdm_mimo_rates : &ofdm_40bw_mimo_rates);
		अन्यथा
			rs_dflt = (bw == BRCMS_20_MHZ ?
				   &cck_ofdm_mimo_rates :
				   &cck_ofdm_40bw_mimo_rates);
	पूर्ण अन्यथा अगर (PHYTYPE_IS(phy_type, PHY_TYPE_LP)) अणु
		rs_dflt = (bandtype == BRCM_BAND_5G) ?
			  &ofdm_rates : &cck_ofdm_rates;
	पूर्ण अन्यथा अगर (PHYTYPE_IS(phy_type, PHY_TYPE_A)) अणु
		rs_dflt = &ofdm_rates;
	पूर्ण अन्यथा अगर (PHYTYPE_IS(phy_type, PHY_TYPE_G)) अणु
		rs_dflt = &cck_ofdm_rates;
	पूर्ण अन्यथा अणु
		/* should not happen, error condition */
		rs_dflt = &cck_rates;	/* क्रमce cck */
	पूर्ण

	/* अगर hw rateset is not supplied, assign selected rateset to it */
	अगर (!rs_hw)
		rs_hw = rs_dflt;

	brcms_c_rateset_copy(rs_dflt, &rs_sel);
	brcms_c_rateset_mcs_upd(&rs_sel, txstreams);
	brcms_c_rateset_filter(&rs_sel, rs_tgt, false,
			   cck_only ? BRCMS_RATES_CCK : BRCMS_RATES_CCK_OFDM,
			   rate_mask, mcsallow);
	brcms_c_rate_hwrs_filter_sort_validate(rs_tgt, rs_hw, false,
					   mcsallow ? txstreams : 1);
पूर्ण

s16 brcms_c_rate_legacy_phyctl(uपूर्णांक rate)
अणु
	uपूर्णांक i;
	क्रम (i = 0; i < LEGACY_PHYCFG_TABLE_SIZE; i++)
		अगर (rate == legacy_phycfg_table[i].rate_ofdm)
			वापस legacy_phycfg_table[i].tx_phy_ctl3;

	वापस -1;
पूर्ण

व्योम brcms_c_rateset_mcs_clear(काष्ठा brcms_c_rateset *rateset)
अणु
	uपूर्णांक i;
	क्रम (i = 0; i < MCSSET_LEN; i++)
		rateset->mcs[i] = 0;
पूर्ण

व्योम brcms_c_rateset_mcs_build(काष्ठा brcms_c_rateset *rateset, u8 txstreams)
अणु
	स_नकल(&rateset->mcs[0], &cck_ofdm_mimo_rates.mcs[0], MCSSET_LEN);
	brcms_c_rateset_mcs_upd(rateset, txstreams);
पूर्ण

/* Based on bandwidth passed, allow/disallow MCS 32 in the rateset */
व्योम brcms_c_rateset_bw_mcs_filter(काष्ठा brcms_c_rateset *rateset, u8 bw)
अणु
	अगर (bw == BRCMS_40_MHZ)
		setbit(rateset->mcs, 32);
	अन्यथा
		clrbit(rateset->mcs, 32);
पूर्ण
