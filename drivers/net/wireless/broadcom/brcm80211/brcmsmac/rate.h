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

#अगर_अघोषित _BRCM_RATE_H_
#घोषणा _BRCM_RATE_H_

#समावेश "types.h"
#समावेश "d11.h"
#समावेश "phy_hal.h"

बाह्य स्थिर u8 rate_info[];
बाह्य स्थिर काष्ठा brcms_c_rateset cck_ofdm_mimo_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset ofdm_mimo_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset cck_ofdm_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset ofdm_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset cck_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset gphy_legacy_rates;
बाह्य स्थिर काष्ठा brcms_c_rateset rate_limit_1_2;

काष्ठा brcms_mcs_info अणु
	/* phy rate in kbps [20Mhz] */
	u32 phy_rate_20;
	/* phy rate in kbps [40Mhz] */
	u32 phy_rate_40;
	/* phy rate in kbps [20Mhz] with SGI */
	u32 phy_rate_20_sgi;
	/* phy rate in kbps [40Mhz] with SGI */
	u32 phy_rate_40_sgi;
	/* phy ctl byte 3, code rate, modulation type, # of streams */
	u8 tx_phy_ctl3;
	/* matching legacy ofdm rate in 500bkps */
	u8 leg_ofdm;
पूर्ण;

#घोषणा BRCMS_MAXMCS	32	/* max valid mcs index */
#घोषणा MCS_TABLE_SIZE	33	/* Number of mcs entries in the table */
बाह्य स्थिर काष्ठा brcms_mcs_info mcs_table[];

#घोषणा MCS_TXS_MASK	0xc0	/* num tx streams - 1 bit mask */
#घोषणा MCS_TXS_SHIFT	6	/* num tx streams - 1 bit shअगरt */

/* वापसs num tx streams - 1 */
अटल अंतरभूत u8 mcs_2_txstreams(u8 mcs)
अणु
	वापस (mcs_table[mcs].tx_phy_ctl3 & MCS_TXS_MASK) >> MCS_TXS_SHIFT;
पूर्ण

अटल अंतरभूत uपूर्णांक mcs_2_rate(u8 mcs, bool is40, bool sgi)
अणु
	अगर (sgi) अणु
		अगर (is40)
			वापस mcs_table[mcs].phy_rate_40_sgi;
		वापस mcs_table[mcs].phy_rate_20_sgi;
	पूर्ण
	अगर (is40)
		वापस mcs_table[mcs].phy_rate_40;

	वापस mcs_table[mcs].phy_rate_20;
पूर्ण

/* Macro to use the rate_info table */
#घोषणा	BRCMS_RATE_MASK_FULL 0xff /* Rate value mask with basic rate flag */

/*
 * rate spec : holds rate and mode specअगरic inक्रमmation required to generate a
 * tx frame. Legacy CCK and OFDM inक्रमmation is held in the same manner as was
 * करोne in the past (in the lower byte) the upper 3 bytes primarily hold MIMO
 * specअगरic inक्रमmation
 */

/* rate spec bit fields */

/* Either 500Kbps units or MIMO MCS idx */
#घोषणा RSPEC_RATE_MASK		0x0000007F
/* mimo MCS is stored in RSPEC_RATE_MASK */
#घोषणा RSPEC_MIMORATE		0x08000000
/* mimo bw mask */
#घोषणा RSPEC_BW_MASK		0x00000700
/* mimo bw shअगरt */
#घोषणा RSPEC_BW_SHIFT		8
/* mimo Space/Time/Frequency mode mask */
#घोषणा RSPEC_STF_MASK		0x00003800
/* mimo Space/Time/Frequency mode shअगरt */
#घोषणा RSPEC_STF_SHIFT		11
/* mimo coding type mask */
#घोषणा RSPEC_CT_MASK		0x0000C000
/* mimo coding type shअगरt */
#घोषणा RSPEC_CT_SHIFT		14
/* mimo num STC streams per PLCP defn. */
#घोषणा RSPEC_STC_MASK		0x00300000
/* mimo num STC streams per PLCP defn. */
#घोषणा RSPEC_STC_SHIFT		20
/* mimo bit indicates adv coding in use */
#घोषणा RSPEC_LDPC_CODING	0x00400000
/* mimo bit indicates लघु GI in use */
#घोषणा RSPEC_SHORT_GI		0x00800000
/* bit indicates override both rate & mode */
#घोषणा RSPEC_OVERRIDE		0x80000000
/* bit indicates override rate only */
#घोषणा RSPEC_OVERRIDE_MCS_ONLY 0x40000000

अटल अंतरभूत bool rspec_active(u32 rspec)
अणु
	वापस rspec & (RSPEC_RATE_MASK | RSPEC_MIMORATE);
पूर्ण

अटल अंतरभूत u8 rspec_phytxbyte2(u32 rspec)
अणु
	वापस (rspec & 0xff00) >> 8;
पूर्ण

अटल अंतरभूत u32 rspec_get_bw(u32 rspec)
अणु
	वापस (rspec & RSPEC_BW_MASK) >> RSPEC_BW_SHIFT;
पूर्ण

अटल अंतरभूत bool rspec_issgi(u32 rspec)
अणु
	वापस (rspec & RSPEC_SHORT_GI) == RSPEC_SHORT_GI;
पूर्ण

अटल अंतरभूत bool rspec_is40mhz(u32 rspec)
अणु
	u32 bw = rspec_get_bw(rspec);

	वापस bw == PHY_TXC1_BW_40MHZ || bw == PHY_TXC1_BW_40MHZ_DUP;
पूर्ण

अटल अंतरभूत uपूर्णांक rspec2rate(u32 rspec)
अणु
	अगर (rspec & RSPEC_MIMORATE)
		वापस mcs_2_rate(rspec & RSPEC_RATE_MASK, rspec_is40mhz(rspec),
				  rspec_issgi(rspec));
	वापस rspec & RSPEC_RATE_MASK;
पूर्ण

अटल अंतरभूत u8 rspec_mimoplcp3(u32 rspec)
अणु
	वापस (rspec & 0xf00000) >> 16;
पूर्ण

अटल अंतरभूत bool plcp3_issgi(u8 plcp)
अणु
	वापस (plcp & (RSPEC_SHORT_GI >> 16)) != 0;
पूर्ण

अटल अंतरभूत uपूर्णांक rspec_stc(u32 rspec)
अणु
	वापस (rspec & RSPEC_STC_MASK) >> RSPEC_STC_SHIFT;
पूर्ण

अटल अंतरभूत uपूर्णांक rspec_stf(u32 rspec)
अणु
	वापस (rspec & RSPEC_STF_MASK) >> RSPEC_STF_SHIFT;
पूर्ण

अटल अंतरभूत bool is_mcs_rate(u32 ratespec)
अणु
	वापस (ratespec & RSPEC_MIMORATE) != 0;
पूर्ण

अटल अंतरभूत bool is_ofdm_rate(u32 ratespec)
अणु
	वापस !is_mcs_rate(ratespec) &&
	       (rate_info[ratespec & RSPEC_RATE_MASK] & BRCMS_RATE_FLAG);
पूर्ण

अटल अंतरभूत bool is_cck_rate(u32 ratespec)
अणु
	u32 rate = (ratespec & BRCMS_RATE_MASK);

	वापस !is_mcs_rate(ratespec) && (
			rate == BRCM_RATE_1M || rate == BRCM_RATE_2M ||
			rate == BRCM_RATE_5M5 || rate == BRCM_RATE_11M);
पूर्ण

अटल अंतरभूत bool is_single_stream(u8 mcs)
अणु
	वापस mcs <= HIGHEST_SINGLE_STREAM_MCS || mcs == 32;
पूर्ण

अटल अंतरभूत u8 cck_rspec(u8 cck)
अणु
	वापस cck & RSPEC_RATE_MASK;
पूर्ण

/* Convert encoded rate value in plcp header to numerical rates in 500 KHz
 * increments */
अटल अंतरभूत u8 ofdm_phy2mac_rate(u8 rlpt)
अणु
	वापस wlc_phy_get_ofdm_rate_lookup()[rlpt & 0x7];
पूर्ण

अटल अंतरभूत u8 cck_phy2mac_rate(u8 संकेत)
अणु
	वापस संकेत/5;
पूर्ण

/* Rates specअगरied in brcms_c_rateset_filter() */
#घोषणा BRCMS_RATES_CCK_OFDM	0
#घोषणा BRCMS_RATES_CCK		1
#घोषणा BRCMS_RATES_OFDM		2

/* sanitize, and sort a rateset with the basic bit(s) preserved, validate
 * rateset */
bool brcms_c_rate_hwrs_filter_sort_validate(काष्ठा brcms_c_rateset *rs,
					    स्थिर काष्ठा brcms_c_rateset *hw_rs,
					    bool check_brate, u8 txstreams);
/* copy rateset src to dst as-is (no masking or sorting) */
व्योम brcms_c_rateset_copy(स्थिर काष्ठा brcms_c_rateset *src,
			  काष्ठा brcms_c_rateset *dst);

/* would be nice to have these करोcumented ... */
u32 brcms_c_compute_rspec(काष्ठा d11rxhdr *rxh, u8 *plcp);

व्योम brcms_c_rateset_filter(काष्ठा brcms_c_rateset *src,
			    काष्ठा brcms_c_rateset *dst, bool basic_only,
			    u8 rates, uपूर्णांक xmask, bool mcsallow);

व्योम brcms_c_rateset_शेष(काष्ठा brcms_c_rateset *rs_tgt,
			     स्थिर काष्ठा brcms_c_rateset *rs_hw, uपूर्णांक phy_type,
			     पूर्णांक bandtype, bool cck_only, uपूर्णांक rate_mask,
			     bool mcsallow, u8 bw, u8 txstreams);

s16 brcms_c_rate_legacy_phyctl(uपूर्णांक rate);

व्योम brcms_c_rateset_mcs_upd(काष्ठा brcms_c_rateset *rs, u8 txstreams);
व्योम brcms_c_rateset_mcs_clear(काष्ठा brcms_c_rateset *rateset);
व्योम brcms_c_rateset_mcs_build(काष्ठा brcms_c_rateset *rateset, u8 txstreams);
व्योम brcms_c_rateset_bw_mcs_filter(काष्ठा brcms_c_rateset *rateset, u8 bw);

#पूर्ण_अगर				/* _BRCM_RATE_H_ */
