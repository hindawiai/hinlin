<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/bcd.h>

#समावेश "main.h"
#समावेश "reg.h"
#समावेश "fw.h"
#समावेश "phy.h"
#समावेश "debug.h"

काष्ठा phy_cfg_pair अणु
	u32 addr;
	u32 data;
पूर्ण;

जोड़ phy_table_tile अणु
	काष्ठा rtw_phy_cond cond;
	काष्ठा phy_cfg_pair cfg;
पूर्ण;

अटल स्थिर u32 db_invert_table[12][8] = अणु
	अणु10,		13,		16,		20,
	 25,		32,		40,		50पूर्ण,
	अणु64,		80,		101,		128,
	 160,		201,		256,		318पूर्ण,
	अणु401,		505,		635,		800,
	 1007,		1268,		1596,		2010पूर्ण,
	अणु316,		398,		501,		631,
	 794,		1000,		1259,		1585पूर्ण,
	अणु1995,		2512,		3162,		3981,
	 5012,		6310,		7943,		10000पूर्ण,
	अणु12589,		15849,		19953,		25119,
	 31623,		39811,		50119,		63098पूर्ण,
	अणु79433,		100000,		125893,		158489,
	 199526,	251189,		316228,		398107पूर्ण,
	अणु501187,	630957,		794328,		1000000,
	 1258925,	1584893,	1995262,	2511886पूर्ण,
	अणु3162278,	3981072,	5011872,	6309573,
	 7943282,	1000000,	12589254,	15848932पूर्ण,
	अणु19952623,	25118864,	31622777,	39810717,
	 50118723,	63095734,	79432823,	100000000पूर्ण,
	अणु125892541,	158489319,	199526232,	251188643,
	 316227766,	398107171,	501187234,	630957345पूर्ण,
	अणु794328235,	1000000000,	1258925412,	1584893192,
	 1995262315,	2511886432U,	3162277660U,	3981071706Uपूर्ण
पूर्ण;

u8 rtw_cck_rates[] = अणु DESC_RATE1M, DESC_RATE2M, DESC_RATE5_5M, DESC_RATE11M पूर्ण;
u8 rtw_ofdm_rates[] = अणु
	DESC_RATE6M,  DESC_RATE9M,  DESC_RATE12M,
	DESC_RATE18M, DESC_RATE24M, DESC_RATE36M,
	DESC_RATE48M, DESC_RATE54M
पूर्ण;
u8 rtw_ht_1s_rates[] = अणु
	DESC_RATEMCS0, DESC_RATEMCS1, DESC_RATEMCS2,
	DESC_RATEMCS3, DESC_RATEMCS4, DESC_RATEMCS5,
	DESC_RATEMCS6, DESC_RATEMCS7
पूर्ण;
u8 rtw_ht_2s_rates[] = अणु
	DESC_RATEMCS8,  DESC_RATEMCS9,  DESC_RATEMCS10,
	DESC_RATEMCS11, DESC_RATEMCS12, DESC_RATEMCS13,
	DESC_RATEMCS14, DESC_RATEMCS15
पूर्ण;
u8 rtw_vht_1s_rates[] = अणु
	DESC_RATEVHT1SS_MCS0, DESC_RATEVHT1SS_MCS1,
	DESC_RATEVHT1SS_MCS2, DESC_RATEVHT1SS_MCS3,
	DESC_RATEVHT1SS_MCS4, DESC_RATEVHT1SS_MCS5,
	DESC_RATEVHT1SS_MCS6, DESC_RATEVHT1SS_MCS7,
	DESC_RATEVHT1SS_MCS8, DESC_RATEVHT1SS_MCS9
पूर्ण;
u8 rtw_vht_2s_rates[] = अणु
	DESC_RATEVHT2SS_MCS0, DESC_RATEVHT2SS_MCS1,
	DESC_RATEVHT2SS_MCS2, DESC_RATEVHT2SS_MCS3,
	DESC_RATEVHT2SS_MCS4, DESC_RATEVHT2SS_MCS5,
	DESC_RATEVHT2SS_MCS6, DESC_RATEVHT2SS_MCS7,
	DESC_RATEVHT2SS_MCS8, DESC_RATEVHT2SS_MCS9
पूर्ण;
u8 *rtw_rate_section[RTW_RATE_SECTION_MAX] = अणु
	rtw_cck_rates, rtw_ofdm_rates,
	rtw_ht_1s_rates, rtw_ht_2s_rates,
	rtw_vht_1s_rates, rtw_vht_2s_rates
पूर्ण;
EXPORT_SYMBOL(rtw_rate_section);

u8 rtw_rate_size[RTW_RATE_SECTION_MAX] = अणु
	ARRAY_SIZE(rtw_cck_rates),
	ARRAY_SIZE(rtw_ofdm_rates),
	ARRAY_SIZE(rtw_ht_1s_rates),
	ARRAY_SIZE(rtw_ht_2s_rates),
	ARRAY_SIZE(rtw_vht_1s_rates),
	ARRAY_SIZE(rtw_vht_2s_rates)
पूर्ण;
EXPORT_SYMBOL(rtw_rate_size);

अटल स्थिर u8 rtw_cck_size = ARRAY_SIZE(rtw_cck_rates);
अटल स्थिर u8 rtw_ofdm_size = ARRAY_SIZE(rtw_ofdm_rates);
अटल स्थिर u8 rtw_ht_1s_size = ARRAY_SIZE(rtw_ht_1s_rates);
अटल स्थिर u8 rtw_ht_2s_size = ARRAY_SIZE(rtw_ht_2s_rates);
अटल स्थिर u8 rtw_vht_1s_size = ARRAY_SIZE(rtw_vht_1s_rates);
अटल स्थिर u8 rtw_vht_2s_size = ARRAY_SIZE(rtw_vht_2s_rates);

क्रमागत rtw_phy_band_type अणु
	PHY_BAND_2G	= 0,
	PHY_BAND_5G	= 1,
पूर्ण;

अटल व्योम rtw_phy_cck_pd_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 i, j;

	क्रम (i = 0; i <= RTW_CHANNEL_WIDTH_40; i++) अणु
		क्रम (j = 0; j < RTW_RF_PATH_MAX; j++)
			dm_info->cck_pd_lv[i][j] = CCK_PD_LV0;
	पूर्ण

	dm_info->cck_fa_avg = CCK_FA_AVG_RESET;
पूर्ण

अटल व्योम rtw_phy_cfo_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (chip->ops->cfo_init)
		chip->ops->cfo_init(rtwdev);
पूर्ण

व्योम rtw_phy_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 addr, mask;

	dm_info->fa_history[3] = 0;
	dm_info->fa_history[2] = 0;
	dm_info->fa_history[1] = 0;
	dm_info->fa_history[0] = 0;
	dm_info->igi_biपंचांगap = 0;
	dm_info->igi_history[3] = 0;
	dm_info->igi_history[2] = 0;
	dm_info->igi_history[1] = 0;

	addr = chip->dig[0].addr;
	mask = chip->dig[0].mask;
	dm_info->igi_history[0] = rtw_पढ़ो32_mask(rtwdev, addr, mask);
	rtw_phy_cck_pd_init(rtwdev);

	dm_info->iqk.करोne = false;
	rtw_phy_cfo_init(rtwdev);
पूर्ण
EXPORT_SYMBOL(rtw_phy_init);

व्योम rtw_phy_dig_ग_लिखो(काष्ठा rtw_dev *rtwdev, u8 igi)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u32 addr, mask;
	u8 path;

	अगर (chip->dig_cck) अणु
		स्थिर काष्ठा rtw_hw_reg *dig_cck = &chip->dig_cck[0];
		rtw_ग_लिखो32_mask(rtwdev, dig_cck->addr, dig_cck->mask, igi >> 1);
	पूर्ण

	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		addr = chip->dig[path].addr;
		mask = chip->dig[path].mask;
		rtw_ग_लिखो32_mask(rtwdev, addr, mask, igi);
	पूर्ण
पूर्ण

अटल व्योम rtw_phy_stat_false_alarm(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->false_alarm_statistics(rtwdev);
पूर्ण

#घोषणा RA_FLOOR_TABLE_SIZE	7
#घोषणा RA_FLOOR_UP_GAP		3

अटल u8 rtw_phy_get_rssi_level(u8 old_level, u8 rssi)
अणु
	u8 table[RA_FLOOR_TABLE_SIZE] = अणु20, 34, 38, 42, 46, 50, 100पूर्ण;
	u8 new_level = 0;
	पूर्णांक i;

	क्रम (i = 0; i < RA_FLOOR_TABLE_SIZE; i++)
		अगर (i >= old_level)
			table[i] += RA_FLOOR_UP_GAP;

	क्रम (i = 0; i < RA_FLOOR_TABLE_SIZE; i++) अणु
		अगर (rssi < table[i]) अणु
			new_level = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस new_level;
पूर्ण

काष्ठा rtw_phy_stat_iter_data अणु
	काष्ठा rtw_dev *rtwdev;
	u8 min_rssi;
पूर्ण;

अटल व्योम rtw_phy_stat_rssi_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_phy_stat_iter_data *iter_data = data;
	काष्ठा rtw_dev *rtwdev = iter_data->rtwdev;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	u8 rssi;

	rssi = ewma_rssi_पढ़ो(&si->avg_rssi);
	si->rssi_level = rtw_phy_get_rssi_level(si->rssi_level, rssi);

	rtw_fw_send_rssi_info(rtwdev, si);

	iter_data->min_rssi = min_t(u8, rssi, iter_data->min_rssi);
पूर्ण

अटल व्योम rtw_phy_stat_rssi(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_phy_stat_iter_data data = अणुपूर्ण;

	data.rtwdev = rtwdev;
	data.min_rssi = U8_MAX;
	rtw_iterate_stas_atomic(rtwdev, rtw_phy_stat_rssi_iter, &data);

	dm_info->pre_min_rssi = dm_info->min_rssi;
	dm_info->min_rssi = data.min_rssi;
पूर्ण

अटल व्योम rtw_phy_stat_rate_cnt(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	dm_info->last_pkt_count = dm_info->cur_pkt_count;
	स_रखो(&dm_info->cur_pkt_count, 0, माप(dm_info->cur_pkt_count));
पूर्ण

अटल व्योम rtw_phy_statistics(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_phy_stat_rssi(rtwdev);
	rtw_phy_stat_false_alarm(rtwdev);
	rtw_phy_stat_rate_cnt(rtwdev);
पूर्ण

#घोषणा DIG_PERF_FA_TH_LOW			250
#घोषणा DIG_PERF_FA_TH_HIGH			500
#घोषणा DIG_PERF_FA_TH_EXTRA_HIGH		750
#घोषणा DIG_PERF_MAX				0x5a
#घोषणा DIG_PERF_MID				0x40
#घोषणा DIG_CVRG_FA_TH_LOW			2000
#घोषणा DIG_CVRG_FA_TH_HIGH			4000
#घोषणा DIG_CVRG_FA_TH_EXTRA_HIGH		5000
#घोषणा DIG_CVRG_MAX				0x2a
#घोषणा DIG_CVRG_MID				0x26
#घोषणा DIG_CVRG_MIN				0x1c
#घोषणा DIG_RSSI_GAIN_OFFSET			15

अटल bool
rtw_phy_dig_check_damping(काष्ठा rtw_dm_info *dm_info)
अणु
	u16 fa_lo = DIG_PERF_FA_TH_LOW;
	u16 fa_hi = DIG_PERF_FA_TH_HIGH;
	u16 *fa_history;
	u8 *igi_history;
	u8 damping_rssi;
	u8 min_rssi;
	u8 dअगरf;
	u8 igi_biपंचांगap;
	bool damping = false;

	min_rssi = dm_info->min_rssi;
	अगर (dm_info->damping) अणु
		damping_rssi = dm_info->damping_rssi;
		dअगरf = min_rssi > damping_rssi ? min_rssi - damping_rssi :
						 damping_rssi - min_rssi;
		अगर (dअगरf > 3 || dm_info->damping_cnt++ > 20) अणु
			dm_info->damping = false;
			वापस false;
		पूर्ण

		वापस true;
	पूर्ण

	igi_history = dm_info->igi_history;
	fa_history = dm_info->fa_history;
	igi_biपंचांगap = dm_info->igi_biपंचांगap & 0xf;
	चयन (igi_biपंचांगap) अणु
	हाल 5:
		/* करोwn -> up -> करोwn -> up */
		अगर (igi_history[0] > igi_history[1] &&
		    igi_history[2] > igi_history[3] &&
		    igi_history[0] - igi_history[1] >= 2 &&
		    igi_history[2] - igi_history[3] >= 2 &&
		    fa_history[0] > fa_hi && fa_history[1] < fa_lo &&
		    fa_history[2] > fa_hi && fa_history[3] < fa_lo)
			damping = true;
		अवरोध;
	हाल 9:
		/* up -> करोwn -> करोwn -> up */
		अगर (igi_history[0] > igi_history[1] &&
		    igi_history[3] > igi_history[2] &&
		    igi_history[0] - igi_history[1] >= 4 &&
		    igi_history[3] - igi_history[2] >= 2 &&
		    fa_history[0] > fa_hi && fa_history[1] < fa_lo &&
		    fa_history[2] < fa_lo && fa_history[3] > fa_hi)
			damping = true;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (damping) अणु
		dm_info->damping = true;
		dm_info->damping_cnt = 0;
		dm_info->damping_rssi = min_rssi;
	पूर्ण

	वापस damping;
पूर्ण

अटल व्योम rtw_phy_dig_get_boundary(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_dm_info *dm_info,
				     u8 *upper, u8 *lower, bool linked)
अणु
	u8 dig_max, dig_min, dig_mid;
	u8 min_rssi;

	अगर (linked) अणु
		dig_max = DIG_PERF_MAX;
		dig_mid = DIG_PERF_MID;
		dig_min = rtwdev->chip->dig_min;
		min_rssi = max_t(u8, dm_info->min_rssi, dig_min);
	पूर्ण अन्यथा अणु
		dig_max = DIG_CVRG_MAX;
		dig_mid = DIG_CVRG_MID;
		dig_min = DIG_CVRG_MIN;
		min_rssi = dig_min;
	पूर्ण

	/* DIG MAX should be bounded by minimum RSSI with offset +15 */
	dig_max = min_t(u8, dig_max, min_rssi + DIG_RSSI_GAIN_OFFSET);

	*lower = clamp_t(u8, min_rssi, dig_min, dig_mid);
	*upper = clamp_t(u8, *lower + DIG_RSSI_GAIN_OFFSET, dig_min, dig_max);
पूर्ण

अटल व्योम rtw_phy_dig_get_threshold(काष्ठा rtw_dm_info *dm_info,
				      u16 *fa_th, u8 *step, bool linked)
अणु
	u8 min_rssi, pre_min_rssi;

	min_rssi = dm_info->min_rssi;
	pre_min_rssi = dm_info->pre_min_rssi;
	step[0] = 4;
	step[1] = 3;
	step[2] = 2;

	अगर (linked) अणु
		fa_th[0] = DIG_PERF_FA_TH_EXTRA_HIGH;
		fa_th[1] = DIG_PERF_FA_TH_HIGH;
		fa_th[2] = DIG_PERF_FA_TH_LOW;
		अगर (pre_min_rssi > min_rssi) अणु
			step[0] = 6;
			step[1] = 4;
			step[2] = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		fa_th[0] = DIG_CVRG_FA_TH_EXTRA_HIGH;
		fa_th[1] = DIG_CVRG_FA_TH_HIGH;
		fa_th[2] = DIG_CVRG_FA_TH_LOW;
	पूर्ण
पूर्ण

अटल व्योम rtw_phy_dig_recorder(काष्ठा rtw_dm_info *dm_info, u8 igi, u16 fa)
अणु
	u8 *igi_history;
	u16 *fa_history;
	u8 igi_biपंचांगap;
	bool up;

	igi_biपंचांगap = dm_info->igi_biपंचांगap << 1 & 0xfe;
	igi_history = dm_info->igi_history;
	fa_history = dm_info->fa_history;

	up = igi > igi_history[0];
	igi_biपंचांगap |= up;

	igi_history[3] = igi_history[2];
	igi_history[2] = igi_history[1];
	igi_history[1] = igi_history[0];
	igi_history[0] = igi;

	fa_history[3] = fa_history[2];
	fa_history[2] = fa_history[1];
	fa_history[1] = fa_history[0];
	fa_history[0] = fa;

	dm_info->igi_biपंचांगap = igi_biपंचांगap;
पूर्ण

अटल व्योम rtw_phy_dig(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 upper_bound, lower_bound;
	u8 pre_igi, cur_igi;
	u16 fa_th[3], fa_cnt;
	u8 level;
	u8 step[3];
	bool linked;

	अगर (test_bit(RTW_FLAG_DIG_DISABLE, rtwdev->flags))
		वापस;

	अगर (rtw_phy_dig_check_damping(dm_info))
		वापस;

	linked = !!rtwdev->sta_cnt;

	fa_cnt = dm_info->total_fa_cnt;
	pre_igi = dm_info->igi_history[0];

	rtw_phy_dig_get_threshold(dm_info, fa_th, step, linked);

	/* test the false alarm count from the highest threshold level first,
	 * and increase it by corresponding step size
	 *
	 * note that the step size is offset by -2, compensate it afterall
	 */
	cur_igi = pre_igi;
	क्रम (level = 0; level < 3; level++) अणु
		अगर (fa_cnt > fa_th[level]) अणु
			cur_igi += step[level];
			अवरोध;
		पूर्ण
	पूर्ण
	cur_igi -= 2;

	/* calculate the upper/lower bound by the minimum rssi we have among
	 * the peers connected with us, meanजबतक make sure the igi value करोes
	 * not beyond the hardware limitation
	 */
	rtw_phy_dig_get_boundary(rtwdev, dm_info, &upper_bound, &lower_bound,
				 linked);
	cur_igi = clamp_t(u8, cur_igi, lower_bound, upper_bound);

	/* record current igi value and false alarm statistics क्रम further
	 * damping checks, and record the trend of igi values
	 */
	rtw_phy_dig_recorder(dm_info, cur_igi, fa_cnt);

	अगर (cur_igi != pre_igi)
		rtw_phy_dig_ग_लिखो(rtwdev, cur_igi);
पूर्ण

अटल व्योम rtw_phy_ra_info_update_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_dev *rtwdev = data;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;

	rtw_update_sta_info(rtwdev, si);
पूर्ण

अटल व्योम rtw_phy_ra_info_update(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtwdev->watch_करोg_cnt & 0x3)
		वापस;

	rtw_iterate_stas_atomic(rtwdev, rtw_phy_ra_info_update_iter, rtwdev);
पूर्ण

अटल u32 rtw_phy_get_rrsr_mask(काष्ठा rtw_dev *rtwdev, u8 rate_idx)
अणु
	u8 rate_order;

	rate_order = rate_idx;

	अगर (rate_idx >= DESC_RATEVHT4SS_MCS0)
		rate_order -= DESC_RATEVHT4SS_MCS0;
	अन्यथा अगर (rate_idx >= DESC_RATEVHT3SS_MCS0)
		rate_order -= DESC_RATEVHT3SS_MCS0;
	अन्यथा अगर (rate_idx >= DESC_RATEVHT2SS_MCS0)
		rate_order -= DESC_RATEVHT2SS_MCS0;
	अन्यथा अगर (rate_idx >= DESC_RATEVHT1SS_MCS0)
		rate_order -= DESC_RATEVHT1SS_MCS0;
	अन्यथा अगर (rate_idx >= DESC_RATEMCS24)
		rate_order -= DESC_RATEMCS24;
	अन्यथा अगर (rate_idx >= DESC_RATEMCS16)
		rate_order -= DESC_RATEMCS16;
	अन्यथा अगर (rate_idx >= DESC_RATEMCS8)
		rate_order -= DESC_RATEMCS8;
	अन्यथा अगर (rate_idx >= DESC_RATEMCS0)
		rate_order -= DESC_RATEMCS0;
	अन्यथा अगर (rate_idx >= DESC_RATE6M)
		rate_order -= DESC_RATE6M;
	अन्यथा
		rate_order -= DESC_RATE1M;

	अगर (rate_idx >= DESC_RATEMCS0 || rate_order == 0)
		rate_order++;

	वापस GENMASK(rate_order + RRSR_RATE_ORDER_CCK_LEN - 1, 0);
पूर्ण

अटल व्योम rtw_phy_rrsr_mask_min_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_dev *rtwdev = (काष्ठा rtw_dev *)data;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 mask = 0;

	mask = rtw_phy_get_rrsr_mask(rtwdev, si->ra_report.desc_rate);
	अगर (mask < dm_info->rrsr_mask_min)
		dm_info->rrsr_mask_min = mask;
पूर्ण

अटल व्योम rtw_phy_rrsr_update(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	dm_info->rrsr_mask_min = RRSR_RATE_ORDER_MAX;
	rtw_iterate_stas_atomic(rtwdev, rtw_phy_rrsr_mask_min_iter, rtwdev);
	rtw_ग_लिखो32(rtwdev, REG_RRSR, dm_info->rrsr_val_init & dm_info->rrsr_mask_min);
पूर्ण

अटल व्योम rtw_phy_dpk_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (chip->ops->dpk_track)
		chip->ops->dpk_track(rtwdev);
पूर्ण

काष्ठा rtw_rx_addr_match_data अणु
	काष्ठा rtw_dev *rtwdev;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rtw_rx_pkt_stat *pkt_stat;
	u8 *bssid;
पूर्ण;

अटल व्योम rtw_phy_parsing_cfo_iter(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_rx_addr_match_data *iter_data = data;
	काष्ठा rtw_dev *rtwdev = iter_data->rtwdev;
	काष्ठा rtw_rx_pkt_stat *pkt_stat = iter_data->pkt_stat;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;
	u8 *bssid = iter_data->bssid;
	u8 i;

	अगर (!ether_addr_equal(vअगर->bss_conf.bssid, bssid))
		वापस;

	क्रम (i = 0; i < rtwdev->hal.rf_path_num; i++) अणु
		cfo->cfo_tail[i] += pkt_stat->cfo_tail[i];
		cfo->cfo_cnt[i]++;
	पूर्ण

	cfo->packet_count++;
पूर्ण

व्योम rtw_phy_parsing_cfo(काष्ठा rtw_dev *rtwdev,
			 काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा ieee80211_hdr *hdr = pkt_stat->hdr;
	काष्ठा rtw_rx_addr_match_data data = अणुपूर्ण;

	अगर (pkt_stat->crc_err || pkt_stat->icv_err || !pkt_stat->phy_status ||
	    ieee80211_is_ctl(hdr->frame_control))
		वापस;

	data.rtwdev = rtwdev;
	data.hdr = hdr;
	data.pkt_stat = pkt_stat;
	data.bssid = get_hdr_bssid(hdr);

	rtw_iterate_vअगरs_atomic(rtwdev, rtw_phy_parsing_cfo_iter, &data);
पूर्ण
EXPORT_SYMBOL(rtw_phy_parsing_cfo);

अटल व्योम rtw_phy_cfo_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (chip->ops->cfo_track)
		chip->ops->cfo_track(rtwdev);
पूर्ण

#घोषणा CCK_PD_FA_LV1_MIN	1000
#घोषणा CCK_PD_FA_LV0_MAX	500

अटल u8 rtw_phy_cck_pd_lv_unlink(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_fa_avg = dm_info->cck_fa_avg;

	अगर (cck_fa_avg > CCK_PD_FA_LV1_MIN)
		वापस CCK_PD_LV1;

	अगर (cck_fa_avg < CCK_PD_FA_LV0_MAX)
		वापस CCK_PD_LV0;

	वापस CCK_PD_LV_MAX;
पूर्ण

#घोषणा CCK_PD_IGI_LV4_VAL 0x38
#घोषणा CCK_PD_IGI_LV3_VAL 0x2a
#घोषणा CCK_PD_IGI_LV2_VAL 0x24
#घोषणा CCK_PD_RSSI_LV4_VAL 32
#घोषणा CCK_PD_RSSI_LV3_VAL 32
#घोषणा CCK_PD_RSSI_LV2_VAL 24

अटल u8 rtw_phy_cck_pd_lv_link(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 igi = dm_info->igi_history[0];
	u8 rssi = dm_info->min_rssi;
	u32 cck_fa_avg = dm_info->cck_fa_avg;

	अगर (igi > CCK_PD_IGI_LV4_VAL && rssi > CCK_PD_RSSI_LV4_VAL)
		वापस CCK_PD_LV4;
	अगर (igi > CCK_PD_IGI_LV3_VAL && rssi > CCK_PD_RSSI_LV3_VAL)
		वापस CCK_PD_LV3;
	अगर (igi > CCK_PD_IGI_LV2_VAL || rssi > CCK_PD_RSSI_LV2_VAL)
		वापस CCK_PD_LV2;
	अगर (cck_fa_avg > CCK_PD_FA_LV1_MIN)
		वापस CCK_PD_LV1;
	अगर (cck_fa_avg < CCK_PD_FA_LV0_MAX)
		वापस CCK_PD_LV0;

	वापस CCK_PD_LV_MAX;
पूर्ण

अटल u8 rtw_phy_cck_pd_lv(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (!rtw_is_assoc(rtwdev))
		वापस rtw_phy_cck_pd_lv_unlink(rtwdev);
	अन्यथा
		वापस rtw_phy_cck_pd_lv_link(rtwdev);
पूर्ण

अटल व्योम rtw_phy_cck_pd(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 cck_fa = dm_info->cck_fa_cnt;
	u8 level;

	अगर (rtwdev->hal.current_band_type != RTW_BAND_2G)
		वापस;

	अगर (dm_info->cck_fa_avg == CCK_FA_AVG_RESET)
		dm_info->cck_fa_avg = cck_fa;
	अन्यथा
		dm_info->cck_fa_avg = (dm_info->cck_fa_avg * 3 + cck_fa) >> 2;

	rtw_dbg(rtwdev, RTW_DBG_PHY, "IGI=0x%x, rssi_min=%d, cck_fa=%d\n",
		dm_info->igi_history[0], dm_info->min_rssi,
		dm_info->fa_history[0]);
	rtw_dbg(rtwdev, RTW_DBG_PHY, "cck_fa_avg=%d, cck_pd_default=%d\n",
		dm_info->cck_fa_avg, dm_info->cck_pd_शेष);

	level = rtw_phy_cck_pd_lv(rtwdev);

	अगर (level >= CCK_PD_LV_MAX)
		वापस;

	अगर (chip->ops->cck_pd_set)
		chip->ops->cck_pd_set(rtwdev, level);
पूर्ण

अटल व्योम rtw_phy_pwr_track(काष्ठा rtw_dev *rtwdev)
अणु
	rtwdev->chip->ops->pwr_track(rtwdev);
पूर्ण

अटल व्योम rtw_phy_ra_track(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_fw_update_wl_phy_info(rtwdev);
	rtw_phy_ra_info_update(rtwdev);
	rtw_phy_rrsr_update(rtwdev);
पूर्ण

व्योम rtw_phy_dynamic_mechanism(काष्ठा rtw_dev *rtwdev)
अणु
	/* क्रम further calculation */
	rtw_phy_statistics(rtwdev);
	rtw_phy_dig(rtwdev);
	rtw_phy_cck_pd(rtwdev);
	rtw_phy_ra_track(rtwdev);
	rtw_phy_cfo_track(rtwdev);
	rtw_phy_dpk_track(rtwdev);
	rtw_phy_pwr_track(rtwdev);
पूर्ण

#घोषणा FRAC_BITS 3

अटल u8 rtw_phy_घातer_2_db(s8 घातer)
अणु
	अगर (घातer <= -100 || घातer >= 20)
		वापस 0;
	अन्यथा अगर (घातer >= 0)
		वापस 100;
	अन्यथा
		वापस 100 + घातer;
पूर्ण

अटल u64 rtw_phy_db_2_linear(u8 घातer_db)
अणु
	u8 i, j;
	u64 linear;

	अगर (घातer_db > 96)
		घातer_db = 96;
	अन्यथा अगर (घातer_db < 1)
		वापस 1;

	/* 1dB ~ 96dB */
	i = (घातer_db - 1) >> 3;
	j = (घातer_db - 1) - (i << 3);

	linear = db_invert_table[i][j];
	linear = i > 2 ? linear << FRAC_BITS : linear;

	वापस linear;
पूर्ण

अटल u8 rtw_phy_linear_2_db(u64 linear)
अणु
	u8 i;
	u8 j;
	u32 dB;

	अगर (linear >= db_invert_table[11][7])
		वापस 96; /* maximum 96 dB */

	क्रम (i = 0; i < 12; i++) अणु
		अगर (i <= 2 && (linear << FRAC_BITS) <= db_invert_table[i][7])
			अवरोध;
		अन्यथा अगर (i > 2 && linear <= db_invert_table[i][7])
			अवरोध;
	पूर्ण

	क्रम (j = 0; j < 8; j++) अणु
		अगर (i <= 2 && (linear << FRAC_BITS) <= db_invert_table[i][j])
			अवरोध;
		अन्यथा अगर (i > 2 && linear <= db_invert_table[i][j])
			अवरोध;
	पूर्ण

	अगर (j == 0 && i == 0)
		जाओ end;

	अगर (j == 0) अणु
		अगर (i != 3) अणु
			अगर (db_invert_table[i][0] - linear >
			    linear - db_invert_table[i - 1][7]) अणु
				i = i - 1;
				j = 7;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (db_invert_table[3][0] - linear >
			    linear - db_invert_table[2][7]) अणु
				i = 2;
				j = 7;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (db_invert_table[i][j] - linear >
		    linear - db_invert_table[i][j - 1]) अणु
			j = j - 1;
		पूर्ण
	पूर्ण
end:
	dB = (i << 3) + j + 1;

	वापस dB;
पूर्ण

u8 rtw_phy_rf_घातer_2_rssi(s8 *rf_घातer, u8 path_num)
अणु
	s8 घातer;
	u8 घातer_db;
	u64 linear;
	u64 sum = 0;
	u8 path;

	क्रम (path = 0; path < path_num; path++) अणु
		घातer = rf_घातer[path];
		घातer_db = rtw_phy_घातer_2_db(घातer);
		linear = rtw_phy_db_2_linear(घातer_db);
		sum += linear;
	पूर्ण

	sum = (sum + (1 << (FRAC_BITS - 1))) >> FRAC_BITS;
	चयन (path_num) अणु
	हाल 2:
		sum >>= 1;
		अवरोध;
	हाल 3:
		sum = ((sum) + ((sum) << 1) + ((sum) << 3)) >> 5;
		अवरोध;
	हाल 4:
		sum >>= 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rtw_phy_linear_2_db(sum);
पूर्ण
EXPORT_SYMBOL(rtw_phy_rf_घातer_2_rssi);

u32 rtw_phy_पढ़ो_rf(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
		    u32 addr, u32 mask)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर u32 *base_addr = chip->rf_base_addr;
	u32 val, direct_addr;

	अगर (rf_path >= hal->rf_phy_num) अणु
		rtw_err(rtwdev, "unsupported rf path (%d)\n", rf_path);
		वापस INV_RF_DATA;
	पूर्ण

	addr &= 0xff;
	direct_addr = base_addr[rf_path] + (addr << 2);
	mask &= RFREG_MASK;

	val = rtw_पढ़ो32_mask(rtwdev, direct_addr, mask);

	वापस val;
पूर्ण
EXPORT_SYMBOL(rtw_phy_पढ़ो_rf);

u32 rtw_phy_पढ़ो_rf_sipi(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			 u32 addr, u32 mask)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_rf_sipi_addr *rf_sipi_addr;
	स्थिर काष्ठा rtw_rf_sipi_addr *rf_sipi_addr_a;
	u32 val32;
	u32 en_pi;
	u32 r_addr;
	u32 shअगरt;

	अगर (rf_path >= hal->rf_phy_num) अणु
		rtw_err(rtwdev, "unsupported rf path (%d)\n", rf_path);
		वापस INV_RF_DATA;
	पूर्ण

	अगर (!chip->rf_sipi_पढ़ो_addr) अणु
		rtw_err(rtwdev, "rf_sipi_read_addr isn't defined\n");
		वापस INV_RF_DATA;
	पूर्ण

	rf_sipi_addr = &chip->rf_sipi_पढ़ो_addr[rf_path];
	rf_sipi_addr_a = &chip->rf_sipi_पढ़ो_addr[RF_PATH_A];

	addr &= 0xff;

	val32 = rtw_पढ़ो32(rtwdev, rf_sipi_addr->hssi_2);
	val32 = (val32 & ~LSSI_READ_ADDR_MASK) | (addr << 23);
	rtw_ग_लिखो32(rtwdev, rf_sipi_addr->hssi_2, val32);

	/* toggle पढ़ो edge of path A */
	val32 = rtw_पढ़ो32(rtwdev, rf_sipi_addr_a->hssi_2);
	rtw_ग_लिखो32(rtwdev, rf_sipi_addr_a->hssi_2, val32 & ~LSSI_READ_EDGE_MASK);
	rtw_ग_लिखो32(rtwdev, rf_sipi_addr_a->hssi_2, val32 | LSSI_READ_EDGE_MASK);

	udelay(120);

	en_pi = rtw_पढ़ो32_mask(rtwdev, rf_sipi_addr->hssi_1, BIT(8));
	r_addr = en_pi ? rf_sipi_addr->lssi_पढ़ो_pi : rf_sipi_addr->lssi_पढ़ो;

	val32 = rtw_पढ़ो32_mask(rtwdev, r_addr, LSSI_READ_DATA_MASK);

	shअगरt = __ffs(mask);

	वापस (val32 & mask) >> shअगरt;
पूर्ण
EXPORT_SYMBOL(rtw_phy_पढ़ो_rf_sipi);

bool rtw_phy_ग_लिखो_rf_reg_sipi(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			       u32 addr, u32 mask, u32 data)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 *sipi_addr = chip->rf_sipi_addr;
	u32 data_and_addr;
	u32 old_data = 0;
	u32 shअगरt;

	अगर (rf_path >= hal->rf_phy_num) अणु
		rtw_err(rtwdev, "unsupported rf path (%d)\n", rf_path);
		वापस false;
	पूर्ण

	addr &= 0xff;
	mask &= RFREG_MASK;

	अगर (mask != RFREG_MASK) अणु
		old_data = chip->ops->पढ़ो_rf(rtwdev, rf_path, addr, RFREG_MASK);

		अगर (old_data == INV_RF_DATA) अणु
			rtw_err(rtwdev, "Write fail, rf is disabled\n");
			वापस false;
		पूर्ण

		shअगरt = __ffs(mask);
		data = ((old_data) & (~mask)) | (data << shअगरt);
	पूर्ण

	data_and_addr = ((addr << 20) | (data & 0x000fffff)) & 0x0fffffff;

	rtw_ग_लिखो32(rtwdev, sipi_addr[rf_path], data_and_addr);

	udelay(13);

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtw_phy_ग_लिखो_rf_reg_sipi);

bool rtw_phy_ग_लिखो_rf_reg(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			  u32 addr, u32 mask, u32 data)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर u32 *base_addr = chip->rf_base_addr;
	u32 direct_addr;

	अगर (rf_path >= hal->rf_phy_num) अणु
		rtw_err(rtwdev, "unsupported rf path (%d)\n", rf_path);
		वापस false;
	पूर्ण

	addr &= 0xff;
	direct_addr = base_addr[rf_path] + (addr << 2);
	mask &= RFREG_MASK;

	rtw_ग_लिखो32_mask(rtwdev, direct_addr, mask, data);

	udelay(1);

	वापस true;
पूर्ण

bool rtw_phy_ग_लिखो_rf_reg_mix(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			      u32 addr, u32 mask, u32 data)
अणु
	अगर (addr != 0x00)
		वापस rtw_phy_ग_लिखो_rf_reg(rtwdev, rf_path, addr, mask, data);

	वापस rtw_phy_ग_लिखो_rf_reg_sipi(rtwdev, rf_path, addr, mask, data);
पूर्ण
EXPORT_SYMBOL(rtw_phy_ग_लिखो_rf_reg_mix);

व्योम rtw_phy_setup_phy_cond(काष्ठा rtw_dev *rtwdev, u32 pkg)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_phy_cond cond = अणु0पूर्ण;

	cond.cut = hal->cut_version ? hal->cut_version : 15;
	cond.pkg = pkg ? pkg : 15;
	cond.plat = 0x04;
	cond.rfe = efuse->rfe_option;

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_USB:
		cond.पूर्णांकf = INTF_USB;
		अवरोध;
	हाल RTW_HCI_TYPE_SDIO:
		cond.पूर्णांकf = INTF_SDIO;
		अवरोध;
	हाल RTW_HCI_TYPE_PCIE:
	शेष:
		cond.पूर्णांकf = INTF_PCIE;
		अवरोध;
	पूर्ण

	hal->phy_cond = cond;

	rtw_dbg(rtwdev, RTW_DBG_PHY, "phy cond=0x%08x\n", *((u32 *)&hal->phy_cond));
पूर्ण

अटल bool check_positive(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_phy_cond cond)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_phy_cond drv_cond = hal->phy_cond;

	अगर (cond.cut && cond.cut != drv_cond.cut)
		वापस false;

	अगर (cond.pkg && cond.pkg != drv_cond.pkg)
		वापस false;

	अगर (cond.पूर्णांकf && cond.पूर्णांकf != drv_cond.पूर्णांकf)
		वापस false;

	अगर (cond.rfe != drv_cond.rfe)
		वापस false;

	वापस true;
पूर्ण

व्योम rtw_parse_tbl_phy_cond(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl)
अणु
	स्थिर जोड़ phy_table_tile *p = tbl->data;
	स्थिर जोड़ phy_table_tile *end = p + tbl->size / 2;
	काष्ठा rtw_phy_cond pos_cond = अणु0पूर्ण;
	bool is_matched = true, is_skipped = false;

	BUILD_BUG_ON(माप(जोड़ phy_table_tile) != माप(काष्ठा phy_cfg_pair));

	क्रम (; p < end; p++) अणु
		अगर (p->cond.pos) अणु
			चयन (p->cond.branch) अणु
			हाल BRANCH_ENDIF:
				is_matched = true;
				is_skipped = false;
				अवरोध;
			हाल BRANCH_ELSE:
				is_matched = is_skipped ? false : true;
				अवरोध;
			हाल BRANCH_IF:
			हाल BRANCH_ELIF:
			शेष:
				pos_cond = p->cond;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (p->cond.neg) अणु
			अगर (!is_skipped) अणु
				अगर (check_positive(rtwdev, pos_cond)) अणु
					is_matched = true;
					is_skipped = true;
				पूर्ण अन्यथा अणु
					is_matched = false;
					is_skipped = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				is_matched = false;
			पूर्ण
		पूर्ण अन्यथा अगर (is_matched) अणु
			(*tbl->करो_cfg)(rtwdev, tbl, p->cfg.addr, p->cfg.data);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_parse_tbl_phy_cond);

#घोषणा bcd_to_dec_pwr_by_rate(val, i) bcd2bin(val >> (i * 8))

अटल u8 tbl_to_dec_pwr_by_rate(काष्ठा rtw_dev *rtwdev, u32 hex, u8 i)
अणु
	अगर (rtwdev->chip->is_pwr_by_rate_dec)
		वापस bcd_to_dec_pwr_by_rate(hex, i);

	वापस (hex >> (i * 8)) & 0xFF;
पूर्ण

अटल व्योम
rtw_phy_get_rate_values_of_txpwr_by_rate(काष्ठा rtw_dev *rtwdev,
					 u32 addr, u32 mask, u32 val, u8 *rate,
					 u8 *pwr_by_rate, u8 *rate_num)
अणु
	पूर्णांक i;

	चयन (addr) अणु
	हाल 0xE00:
	हाल 0x830:
		rate[0] = DESC_RATE6M;
		rate[1] = DESC_RATE9M;
		rate[2] = DESC_RATE12M;
		rate[3] = DESC_RATE18M;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xE04:
	हाल 0x834:
		rate[0] = DESC_RATE24M;
		rate[1] = DESC_RATE36M;
		rate[2] = DESC_RATE48M;
		rate[3] = DESC_RATE54M;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xE08:
		rate[0] = DESC_RATE1M;
		pwr_by_rate[0] = bcd_to_dec_pwr_by_rate(val, 1);
		*rate_num = 1;
		अवरोध;
	हाल 0x86C:
		अगर (mask == 0xffffff00) अणु
			rate[0] = DESC_RATE2M;
			rate[1] = DESC_RATE5_5M;
			rate[2] = DESC_RATE11M;
			क्रम (i = 1; i < 4; ++i)
				pwr_by_rate[i - 1] =
					tbl_to_dec_pwr_by_rate(rtwdev, val, i);
			*rate_num = 3;
		पूर्ण अन्यथा अगर (mask == 0x000000ff) अणु
			rate[0] = DESC_RATE11M;
			pwr_by_rate[0] = bcd_to_dec_pwr_by_rate(val, 0);
			*rate_num = 1;
		पूर्ण
		अवरोध;
	हाल 0xE10:
	हाल 0x83C:
		rate[0] = DESC_RATEMCS0;
		rate[1] = DESC_RATEMCS1;
		rate[2] = DESC_RATEMCS2;
		rate[3] = DESC_RATEMCS3;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xE14:
	हाल 0x848:
		rate[0] = DESC_RATEMCS4;
		rate[1] = DESC_RATEMCS5;
		rate[2] = DESC_RATEMCS6;
		rate[3] = DESC_RATEMCS7;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xE18:
	हाल 0x84C:
		rate[0] = DESC_RATEMCS8;
		rate[1] = DESC_RATEMCS9;
		rate[2] = DESC_RATEMCS10;
		rate[3] = DESC_RATEMCS11;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xE1C:
	हाल 0x868:
		rate[0] = DESC_RATEMCS12;
		rate[1] = DESC_RATEMCS13;
		rate[2] = DESC_RATEMCS14;
		rate[3] = DESC_RATEMCS15;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0x838:
		rate[0] = DESC_RATE1M;
		rate[1] = DESC_RATE2M;
		rate[2] = DESC_RATE5_5M;
		क्रम (i = 1; i < 4; ++i)
			pwr_by_rate[i - 1] = tbl_to_dec_pwr_by_rate(rtwdev,
								    val, i);
		*rate_num = 3;
		अवरोध;
	हाल 0xC20:
	हाल 0xE20:
	हाल 0x1820:
	हाल 0x1A20:
		rate[0] = DESC_RATE1M;
		rate[1] = DESC_RATE2M;
		rate[2] = DESC_RATE5_5M;
		rate[3] = DESC_RATE11M;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC24:
	हाल 0xE24:
	हाल 0x1824:
	हाल 0x1A24:
		rate[0] = DESC_RATE6M;
		rate[1] = DESC_RATE9M;
		rate[2] = DESC_RATE12M;
		rate[3] = DESC_RATE18M;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC28:
	हाल 0xE28:
	हाल 0x1828:
	हाल 0x1A28:
		rate[0] = DESC_RATE24M;
		rate[1] = DESC_RATE36M;
		rate[2] = DESC_RATE48M;
		rate[3] = DESC_RATE54M;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC2C:
	हाल 0xE2C:
	हाल 0x182C:
	हाल 0x1A2C:
		rate[0] = DESC_RATEMCS0;
		rate[1] = DESC_RATEMCS1;
		rate[2] = DESC_RATEMCS2;
		rate[3] = DESC_RATEMCS3;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC30:
	हाल 0xE30:
	हाल 0x1830:
	हाल 0x1A30:
		rate[0] = DESC_RATEMCS4;
		rate[1] = DESC_RATEMCS5;
		rate[2] = DESC_RATEMCS6;
		rate[3] = DESC_RATEMCS7;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC34:
	हाल 0xE34:
	हाल 0x1834:
	हाल 0x1A34:
		rate[0] = DESC_RATEMCS8;
		rate[1] = DESC_RATEMCS9;
		rate[2] = DESC_RATEMCS10;
		rate[3] = DESC_RATEMCS11;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC38:
	हाल 0xE38:
	हाल 0x1838:
	हाल 0x1A38:
		rate[0] = DESC_RATEMCS12;
		rate[1] = DESC_RATEMCS13;
		rate[2] = DESC_RATEMCS14;
		rate[3] = DESC_RATEMCS15;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC3C:
	हाल 0xE3C:
	हाल 0x183C:
	हाल 0x1A3C:
		rate[0] = DESC_RATEVHT1SS_MCS0;
		rate[1] = DESC_RATEVHT1SS_MCS1;
		rate[2] = DESC_RATEVHT1SS_MCS2;
		rate[3] = DESC_RATEVHT1SS_MCS3;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC40:
	हाल 0xE40:
	हाल 0x1840:
	हाल 0x1A40:
		rate[0] = DESC_RATEVHT1SS_MCS4;
		rate[1] = DESC_RATEVHT1SS_MCS5;
		rate[2] = DESC_RATEVHT1SS_MCS6;
		rate[3] = DESC_RATEVHT1SS_MCS7;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC44:
	हाल 0xE44:
	हाल 0x1844:
	हाल 0x1A44:
		rate[0] = DESC_RATEVHT1SS_MCS8;
		rate[1] = DESC_RATEVHT1SS_MCS9;
		rate[2] = DESC_RATEVHT2SS_MCS0;
		rate[3] = DESC_RATEVHT2SS_MCS1;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC48:
	हाल 0xE48:
	हाल 0x1848:
	हाल 0x1A48:
		rate[0] = DESC_RATEVHT2SS_MCS2;
		rate[1] = DESC_RATEVHT2SS_MCS3;
		rate[2] = DESC_RATEVHT2SS_MCS4;
		rate[3] = DESC_RATEVHT2SS_MCS5;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xC4C:
	हाल 0xE4C:
	हाल 0x184C:
	हाल 0x1A4C:
		rate[0] = DESC_RATEVHT2SS_MCS6;
		rate[1] = DESC_RATEVHT2SS_MCS7;
		rate[2] = DESC_RATEVHT2SS_MCS8;
		rate[3] = DESC_RATEVHT2SS_MCS9;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xCD8:
	हाल 0xED8:
	हाल 0x18D8:
	हाल 0x1AD8:
		rate[0] = DESC_RATEMCS16;
		rate[1] = DESC_RATEMCS17;
		rate[2] = DESC_RATEMCS18;
		rate[3] = DESC_RATEMCS19;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xCDC:
	हाल 0xEDC:
	हाल 0x18DC:
	हाल 0x1ADC:
		rate[0] = DESC_RATEMCS20;
		rate[1] = DESC_RATEMCS21;
		rate[2] = DESC_RATEMCS22;
		rate[3] = DESC_RATEMCS23;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xCE0:
	हाल 0xEE0:
	हाल 0x18E0:
	हाल 0x1AE0:
		rate[0] = DESC_RATEVHT3SS_MCS0;
		rate[1] = DESC_RATEVHT3SS_MCS1;
		rate[2] = DESC_RATEVHT3SS_MCS2;
		rate[3] = DESC_RATEVHT3SS_MCS3;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xCE4:
	हाल 0xEE4:
	हाल 0x18E4:
	हाल 0x1AE4:
		rate[0] = DESC_RATEVHT3SS_MCS4;
		rate[1] = DESC_RATEVHT3SS_MCS5;
		rate[2] = DESC_RATEVHT3SS_MCS6;
		rate[3] = DESC_RATEVHT3SS_MCS7;
		क्रम (i = 0; i < 4; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 4;
		अवरोध;
	हाल 0xCE8:
	हाल 0xEE8:
	हाल 0x18E8:
	हाल 0x1AE8:
		rate[0] = DESC_RATEVHT3SS_MCS8;
		rate[1] = DESC_RATEVHT3SS_MCS9;
		क्रम (i = 0; i < 2; ++i)
			pwr_by_rate[i] = tbl_to_dec_pwr_by_rate(rtwdev, val, i);
		*rate_num = 2;
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "invalid tx power index addr 0x%08x\n", addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw_phy_store_tx_घातer_by_rate(काष्ठा rtw_dev *rtwdev,
					   u32 band, u32 rfpath, u32 txnum,
					   u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 rate_num = 0;
	u8 rate;
	u8 rates[RTW_RF_PATH_MAX] = अणु0पूर्ण;
	s8 offset;
	s8 pwr_by_rate[RTW_RF_PATH_MAX] = अणु0पूर्ण;
	पूर्णांक i;

	rtw_phy_get_rate_values_of_txpwr_by_rate(rtwdev, regaddr, biपंचांगask, data,
						 rates, pwr_by_rate, &rate_num);

	अगर (WARN_ON(rfpath >= RTW_RF_PATH_MAX ||
		    (band != PHY_BAND_2G && band != PHY_BAND_5G) ||
		    rate_num > RTW_RF_PATH_MAX))
		वापस;

	क्रम (i = 0; i < rate_num; i++) अणु
		offset = pwr_by_rate[i];
		rate = rates[i];
		अगर (band == PHY_BAND_2G)
			hal->tx_pwr_by_rate_offset_2g[rfpath][rate] = offset;
		अन्यथा अगर (band == PHY_BAND_5G)
			hal->tx_pwr_by_rate_offset_5g[rfpath][rate] = offset;
		अन्यथा
			जारी;
	पूर्ण
पूर्ण

व्योम rtw_parse_tbl_bb_pg(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl)
अणु
	स्थिर काष्ठा rtw_phy_pg_cfg_pair *p = tbl->data;
	स्थिर काष्ठा rtw_phy_pg_cfg_pair *end = p + tbl->size;

	क्रम (; p < end; p++) अणु
		अगर (p->addr == 0xfe || p->addr == 0xffe) अणु
			msleep(50);
			जारी;
		पूर्ण
		rtw_phy_store_tx_घातer_by_rate(rtwdev, p->band, p->rf_path,
					       p->tx_num, p->addr, p->biपंचांगask,
					       p->data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_parse_tbl_bb_pg);

अटल स्थिर u8 rtw_channel_idx_5g[RTW_MAX_CHANNEL_NUM_5G] = अणु
	36,  38,  40,  42,  44,  46,  48, /* Band 1 */
	52,  54,  56,  58,  60,  62,  64, /* Band 2 */
	100, 102, 104, 106, 108, 110, 112, /* Band 3 */
	116, 118, 120, 122, 124, 126, 128, /* Band 3 */
	132, 134, 136, 138, 140, 142, 144, /* Band 3 */
	149, 151, 153, 155, 157, 159, 161, /* Band 4 */
	165, 167, 169, 171, 173, 175, 177पूर्ण; /* Band 4 */

अटल पूर्णांक rtw_channel_to_idx(u8 band, u8 channel)
अणु
	पूर्णांक ch_idx;
	u8 n_channel;

	अगर (band == PHY_BAND_2G) अणु
		ch_idx = channel - 1;
		n_channel = RTW_MAX_CHANNEL_NUM_2G;
	पूर्ण अन्यथा अगर (band == PHY_BAND_5G) अणु
		n_channel = RTW_MAX_CHANNEL_NUM_5G;
		क्रम (ch_idx = 0; ch_idx < n_channel; ch_idx++)
			अगर (rtw_channel_idx_5g[ch_idx] == channel)
				अवरोध;
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	अगर (ch_idx >= n_channel)
		वापस -1;

	वापस ch_idx;
पूर्ण

अटल व्योम rtw_phy_set_tx_घातer_limit(काष्ठा rtw_dev *rtwdev, u8 regd, u8 band,
				       u8 bw, u8 rs, u8 ch, s8 pwr_limit)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 max_घातer_index = rtwdev->chip->max_घातer_index;
	s8 ww;
	पूर्णांक ch_idx;

	pwr_limit = clamp_t(s8, pwr_limit,
			    -max_घातer_index, max_घातer_index);
	ch_idx = rtw_channel_to_idx(band, ch);

	अगर (regd >= RTW_REGD_MAX || bw >= RTW_CHANNEL_WIDTH_MAX ||
	    rs >= RTW_RATE_SECTION_MAX || ch_idx < 0) अणु
		WARN(1,
		     "wrong txpwr_lmt regd=%u, band=%u bw=%u, rs=%u, ch_idx=%u, pwr_limit=%d\n",
		     regd, band, bw, rs, ch_idx, pwr_limit);
		वापस;
	पूर्ण

	अगर (band == PHY_BAND_2G) अणु
		hal->tx_pwr_limit_2g[regd][bw][rs][ch_idx] = pwr_limit;
		ww = hal->tx_pwr_limit_2g[RTW_REGD_WW][bw][rs][ch_idx];
		ww = min_t(s8, ww, pwr_limit);
		hal->tx_pwr_limit_2g[RTW_REGD_WW][bw][rs][ch_idx] = ww;
	पूर्ण अन्यथा अगर (band == PHY_BAND_5G) अणु
		hal->tx_pwr_limit_5g[regd][bw][rs][ch_idx] = pwr_limit;
		ww = hal->tx_pwr_limit_5g[RTW_REGD_WW][bw][rs][ch_idx];
		ww = min_t(s8, ww, pwr_limit);
		hal->tx_pwr_limit_5g[RTW_REGD_WW][bw][rs][ch_idx] = ww;
	पूर्ण
पूर्ण

/* cross-reference 5G घातer limits अगर values are not asचिन्हित */
अटल व्योम
rtw_xref_5g_txpwr_lmt(काष्ठा rtw_dev *rtwdev, u8 regd,
		      u8 bw, u8 ch_idx, u8 rs_ht, u8 rs_vht)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 max_घातer_index = rtwdev->chip->max_घातer_index;
	s8 lmt_ht = hal->tx_pwr_limit_5g[regd][bw][rs_ht][ch_idx];
	s8 lmt_vht = hal->tx_pwr_limit_5g[regd][bw][rs_vht][ch_idx];

	अगर (lmt_ht == lmt_vht)
		वापस;

	अगर (lmt_ht == max_घातer_index)
		hal->tx_pwr_limit_5g[regd][bw][rs_ht][ch_idx] = lmt_vht;

	अन्यथा अगर (lmt_vht == max_घातer_index)
		hal->tx_pwr_limit_5g[regd][bw][rs_vht][ch_idx] = lmt_ht;
पूर्ण

/* cross-reference घातer limits क्रम ht and vht */
अटल व्योम
rtw_xref_txpwr_lmt_by_rs(काष्ठा rtw_dev *rtwdev, u8 regd, u8 bw, u8 ch_idx)
अणु
	u8 rs_idx, rs_ht, rs_vht;
	u8 rs_cmp[2][2] = अणुअणुRTW_RATE_SECTION_HT_1S, RTW_RATE_SECTION_VHT_1Sपूर्ण,
			   अणुRTW_RATE_SECTION_HT_2S, RTW_RATE_SECTION_VHT_2Sपूर्ण पूर्ण;

	क्रम (rs_idx = 0; rs_idx < 2; rs_idx++) अणु
		rs_ht = rs_cmp[rs_idx][0];
		rs_vht = rs_cmp[rs_idx][1];

		rtw_xref_5g_txpwr_lmt(rtwdev, regd, bw, ch_idx, rs_ht, rs_vht);
	पूर्ण
पूर्ण

/* cross-reference घातer limits क्रम 5G channels */
अटल व्योम
rtw_xref_5g_txpwr_lmt_by_ch(काष्ठा rtw_dev *rtwdev, u8 regd, u8 bw)
अणु
	u8 ch_idx;

	क्रम (ch_idx = 0; ch_idx < RTW_MAX_CHANNEL_NUM_5G; ch_idx++)
		rtw_xref_txpwr_lmt_by_rs(rtwdev, regd, bw, ch_idx);
पूर्ण

/* cross-reference घातer limits क्रम 20/40M bandwidth */
अटल व्योम
rtw_xref_txpwr_lmt_by_bw(काष्ठा rtw_dev *rtwdev, u8 regd)
अणु
	u8 bw;

	क्रम (bw = RTW_CHANNEL_WIDTH_20; bw <= RTW_CHANNEL_WIDTH_40; bw++)
		rtw_xref_5g_txpwr_lmt_by_ch(rtwdev, regd, bw);
पूर्ण

/* cross-reference घातer limits */
अटल व्योम rtw_xref_txpwr_lmt(काष्ठा rtw_dev *rtwdev)
अणु
	u8 regd;

	क्रम (regd = 0; regd < RTW_REGD_MAX; regd++)
		rtw_xref_txpwr_lmt_by_bw(rtwdev, regd);
पूर्ण

व्योम rtw_parse_tbl_txpwr_lmt(काष्ठा rtw_dev *rtwdev,
			     स्थिर काष्ठा rtw_table *tbl)
अणु
	स्थिर काष्ठा rtw_txpwr_lmt_cfg_pair *p = tbl->data;
	स्थिर काष्ठा rtw_txpwr_lmt_cfg_pair *end = p + tbl->size;

	क्रम (; p < end; p++) अणु
		rtw_phy_set_tx_घातer_limit(rtwdev, p->regd, p->band,
					   p->bw, p->rs, p->ch, p->txpwr_lmt);
	पूर्ण

	rtw_xref_txpwr_lmt(rtwdev);
पूर्ण
EXPORT_SYMBOL(rtw_parse_tbl_txpwr_lmt);

व्योम rtw_phy_cfg_mac(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		     u32 addr, u32 data)
अणु
	rtw_ग_लिखो8(rtwdev, addr, data);
पूर्ण
EXPORT_SYMBOL(rtw_phy_cfg_mac);

व्योम rtw_phy_cfg_agc(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		     u32 addr, u32 data)
अणु
	rtw_ग_लिखो32(rtwdev, addr, data);
पूर्ण
EXPORT_SYMBOL(rtw_phy_cfg_agc);

व्योम rtw_phy_cfg_bb(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		    u32 addr, u32 data)
अणु
	अगर (addr == 0xfe)
		msleep(50);
	अन्यथा अगर (addr == 0xfd)
		mdelay(5);
	अन्यथा अगर (addr == 0xfc)
		mdelay(1);
	अन्यथा अगर (addr == 0xfb)
		usleep_range(50, 60);
	अन्यथा अगर (addr == 0xfa)
		udelay(5);
	अन्यथा अगर (addr == 0xf9)
		udelay(1);
	अन्यथा
		rtw_ग_लिखो32(rtwdev, addr, data);
पूर्ण
EXPORT_SYMBOL(rtw_phy_cfg_bb);

व्योम rtw_phy_cfg_rf(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		    u32 addr, u32 data)
अणु
	अगर (addr == 0xffe) अणु
		msleep(50);
	पूर्ण अन्यथा अगर (addr == 0xfe) अणु
		usleep_range(100, 110);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो_rf(rtwdev, tbl->rf_path, addr, RFREG_MASK, data);
		udelay(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_phy_cfg_rf);

अटल व्योम rtw_load_rfk_table(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	अगर (!chip->rfk_init_tbl)
		वापस;

	rtw_ग_लिखो32_mask(rtwdev, 0x1e24, BIT(17), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x1cd0, BIT(28), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x1cd0, BIT(29), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x1cd0, BIT(30), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x1cd0, BIT(31), 0x0);

	rtw_load_table(rtwdev, chip->rfk_init_tbl);

	dpk_info->is_dpk_pwr_on = true;
पूर्ण

व्योम rtw_phy_load_tables(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 rf_path;

	rtw_load_table(rtwdev, chip->mac_tbl);
	rtw_load_table(rtwdev, chip->bb_tbl);
	rtw_load_table(rtwdev, chip->agc_tbl);
	rtw_load_rfk_table(rtwdev);

	क्रम (rf_path = 0; rf_path < rtwdev->hal.rf_path_num; rf_path++) अणु
		स्थिर काष्ठा rtw_table *tbl;

		tbl = chip->rf_tbl[rf_path];
		rtw_load_table(rtwdev, tbl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_phy_load_tables);

अटल u8 rtw_get_channel_group(u8 channel, u8 rate)
अणु
	चयन (channel) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल 1:
	हाल 2:
	हाल 36:
	हाल 38:
	हाल 40:
	हाल 42:
		वापस 0;
	हाल 3:
	हाल 4:
	हाल 5:
	हाल 44:
	हाल 46:
	हाल 48:
	हाल 50:
		वापस 1;
	हाल 6:
	हाल 7:
	हाल 8:
	हाल 52:
	हाल 54:
	हाल 56:
	हाल 58:
		वापस 2;
	हाल 9:
	हाल 10:
	हाल 11:
	हाल 60:
	हाल 62:
	हाल 64:
		वापस 3;
	हाल 12:
	हाल 13:
	हाल 100:
	हाल 102:
	हाल 104:
	हाल 106:
		वापस 4;
	हाल 14:
		वापस rate <= DESC_RATE11M ? 5 : 4;
	हाल 108:
	हाल 110:
	हाल 112:
	हाल 114:
		वापस 5;
	हाल 116:
	हाल 118:
	हाल 120:
	हाल 122:
		वापस 6;
	हाल 124:
	हाल 126:
	हाल 128:
	हाल 130:
		वापस 7;
	हाल 132:
	हाल 134:
	हाल 136:
	हाल 138:
		वापस 8;
	हाल 140:
	हाल 142:
	हाल 144:
		वापस 9;
	हाल 149:
	हाल 151:
	हाल 153:
	हाल 155:
		वापस 10;
	हाल 157:
	हाल 159:
	हाल 161:
		वापस 11;
	हाल 165:
	हाल 167:
	हाल 169:
	हाल 171:
		वापस 12;
	हाल 173:
	हाल 175:
	हाल 177:
		वापस 13;
	पूर्ण
पूर्ण

अटल s8 rtw_phy_get_dis_dpd_by_rate_dअगरf(काष्ठा rtw_dev *rtwdev, u16 rate)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	s8 dpd_dअगरf = 0;

	अगर (!chip->en_dis_dpd)
		वापस 0;

#घोषणा RTW_DPD_RATE_CHECK(_rate)					\
	हाल DESC_RATE ## _rate:					\
	अगर (DIS_DPD_RATE ## _rate & chip->dpd_ratemask)			\
		dpd_dअगरf = -6 * chip->txgi_factor;			\
	अवरोध

	चयन (rate) अणु
	RTW_DPD_RATE_CHECK(6M);
	RTW_DPD_RATE_CHECK(9M);
	RTW_DPD_RATE_CHECK(MCS0);
	RTW_DPD_RATE_CHECK(MCS1);
	RTW_DPD_RATE_CHECK(MCS8);
	RTW_DPD_RATE_CHECK(MCS9);
	RTW_DPD_RATE_CHECK(VHT1SS_MCS0);
	RTW_DPD_RATE_CHECK(VHT1SS_MCS1);
	RTW_DPD_RATE_CHECK(VHT2SS_MCS0);
	RTW_DPD_RATE_CHECK(VHT2SS_MCS1);
	पूर्ण
#अघोषित RTW_DPD_RATE_CHECK

	वापस dpd_dअगरf;
पूर्ण

अटल u8 rtw_phy_get_2g_tx_घातer_index(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_2g_txpwr_idx *pwr_idx_2g,
					क्रमागत rtw_bandwidth bandwidth,
					u8 rate, u8 group)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 tx_घातer;
	bool mcs_rate;
	bool above_2ss;
	u8 factor = chip->txgi_factor;

	अगर (rate <= DESC_RATE11M)
		tx_घातer = pwr_idx_2g->cck_base[group];
	अन्यथा
		tx_घातer = pwr_idx_2g->bw40_base[group];

	अगर (rate >= DESC_RATE6M && rate <= DESC_RATE54M)
		tx_घातer += pwr_idx_2g->ht_1s_dअगरf.ofdm * factor;

	mcs_rate = (rate >= DESC_RATEMCS0 && rate <= DESC_RATEMCS15) ||
		   (rate >= DESC_RATEVHT1SS_MCS0 &&
		    rate <= DESC_RATEVHT2SS_MCS9);
	above_2ss = (rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
		    (rate >= DESC_RATEVHT2SS_MCS0);

	अगर (!mcs_rate)
		वापस tx_घातer;

	चयन (bandwidth) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल RTW_CHANNEL_WIDTH_20:
		tx_घातer += pwr_idx_2g->ht_1s_dअगरf.bw20 * factor;
		अगर (above_2ss)
			tx_घातer += pwr_idx_2g->ht_2s_dअगरf.bw20 * factor;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		/* bw40 is the base घातer */
		अगर (above_2ss)
			tx_घातer += pwr_idx_2g->ht_2s_dअगरf.bw40 * factor;
		अवरोध;
	पूर्ण

	वापस tx_घातer;
पूर्ण

अटल u8 rtw_phy_get_5g_tx_घातer_index(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_5g_txpwr_idx *pwr_idx_5g,
					क्रमागत rtw_bandwidth bandwidth,
					u8 rate, u8 group)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 tx_घातer;
	u8 upper, lower;
	bool mcs_rate;
	bool above_2ss;
	u8 factor = chip->txgi_factor;

	tx_घातer = pwr_idx_5g->bw40_base[group];

	mcs_rate = (rate >= DESC_RATEMCS0 && rate <= DESC_RATEMCS15) ||
		   (rate >= DESC_RATEVHT1SS_MCS0 &&
		    rate <= DESC_RATEVHT2SS_MCS9);
	above_2ss = (rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
		    (rate >= DESC_RATEVHT2SS_MCS0);

	अगर (!mcs_rate) अणु
		tx_घातer += pwr_idx_5g->ht_1s_dअगरf.ofdm * factor;
		वापस tx_घातer;
	पूर्ण

	चयन (bandwidth) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल RTW_CHANNEL_WIDTH_20:
		tx_घातer += pwr_idx_5g->ht_1s_dअगरf.bw20 * factor;
		अगर (above_2ss)
			tx_घातer += pwr_idx_5g->ht_2s_dअगरf.bw20 * factor;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		/* bw40 is the base घातer */
		अगर (above_2ss)
			tx_घातer += pwr_idx_5g->ht_2s_dअगरf.bw40 * factor;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		/* the base idx of bw80 is the average of bw40+/bw40- */
		lower = pwr_idx_5g->bw40_base[group];
		upper = pwr_idx_5g->bw40_base[group + 1];

		tx_घातer = (lower + upper) / 2;
		tx_घातer += pwr_idx_5g->vht_1s_dअगरf.bw80 * factor;
		अगर (above_2ss)
			tx_घातer += pwr_idx_5g->vht_2s_dअगरf.bw80 * factor;
		अवरोध;
	पूर्ण

	वापस tx_घातer;
पूर्ण

अटल s8 rtw_phy_get_tx_घातer_limit(काष्ठा rtw_dev *rtwdev, u8 band,
				     क्रमागत rtw_bandwidth bw, u8 rf_path,
				     u8 rate, u8 channel, u8 regd)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 *cch_by_bw = hal->cch_by_bw;
	s8 घातer_limit = (s8)rtwdev->chip->max_घातer_index;
	u8 rs;
	पूर्णांक ch_idx;
	u8 cur_bw, cur_ch;
	s8 cur_lmt;

	अगर (regd > RTW_REGD_WW)
		वापस घातer_limit;

	अगर (rate >= DESC_RATE1M && rate <= DESC_RATE11M)
		rs = RTW_RATE_SECTION_CCK;
	अन्यथा अगर (rate >= DESC_RATE6M && rate <= DESC_RATE54M)
		rs = RTW_RATE_SECTION_OFDM;
	अन्यथा अगर (rate >= DESC_RATEMCS0 && rate <= DESC_RATEMCS7)
		rs = RTW_RATE_SECTION_HT_1S;
	अन्यथा अगर (rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15)
		rs = RTW_RATE_SECTION_HT_2S;
	अन्यथा अगर (rate >= DESC_RATEVHT1SS_MCS0 && rate <= DESC_RATEVHT1SS_MCS9)
		rs = RTW_RATE_SECTION_VHT_1S;
	अन्यथा अगर (rate >= DESC_RATEVHT2SS_MCS0 && rate <= DESC_RATEVHT2SS_MCS9)
		rs = RTW_RATE_SECTION_VHT_2S;
	अन्यथा
		जाओ err;

	/* only 20M BW with cck and ofdm */
	अगर (rs == RTW_RATE_SECTION_CCK || rs == RTW_RATE_SECTION_OFDM)
		bw = RTW_CHANNEL_WIDTH_20;

	/* only 20/40M BW with ht */
	अगर (rs == RTW_RATE_SECTION_HT_1S || rs == RTW_RATE_SECTION_HT_2S)
		bw = min_t(u8, bw, RTW_CHANNEL_WIDTH_40);

	/* select min घातer limit among [20M BW ~ current BW] */
	क्रम (cur_bw = RTW_CHANNEL_WIDTH_20; cur_bw <= bw; cur_bw++) अणु
		cur_ch = cch_by_bw[cur_bw];

		ch_idx = rtw_channel_to_idx(band, cur_ch);
		अगर (ch_idx < 0)
			जाओ err;

		cur_lmt = cur_ch <= RTW_MAX_CHANNEL_NUM_2G ?
			hal->tx_pwr_limit_2g[regd][cur_bw][rs][ch_idx] :
			hal->tx_pwr_limit_5g[regd][cur_bw][rs][ch_idx];

		घातer_limit = min_t(s8, cur_lmt, घातer_limit);
	पूर्ण

	वापस घातer_limit;

err:
	WARN(1, "invalid arguments, band=%d, bw=%d, path=%d, rate=%d, ch=%d\n",
	     band, bw, rf_path, rate, channel);
	वापस (s8)rtwdev->chip->max_घातer_index;
पूर्ण

व्योम rtw_get_tx_घातer_params(काष्ठा rtw_dev *rtwdev, u8 path, u8 rate, u8 bw,
			     u8 ch, u8 regd, काष्ठा rtw_घातer_params *pwr_param)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_txpwr_idx *pwr_idx;
	u8 group, band;
	u8 *base = &pwr_param->pwr_base;
	s8 *offset = &pwr_param->pwr_offset;
	s8 *limit = &pwr_param->pwr_limit;
	s8 *remnant = &pwr_param->pwr_remnant;

	pwr_idx = &rtwdev->efuse.txpwr_idx_table[path];
	group = rtw_get_channel_group(ch, rate);

	/* base घातer index क्रम 2.4G/5G */
	अगर (IS_CH_2G_BAND(ch)) अणु
		band = PHY_BAND_2G;
		*base = rtw_phy_get_2g_tx_घातer_index(rtwdev,
						      &pwr_idx->pwr_idx_2g,
						      bw, rate, group);
		*offset = hal->tx_pwr_by_rate_offset_2g[path][rate];
	पूर्ण अन्यथा अणु
		band = PHY_BAND_5G;
		*base = rtw_phy_get_5g_tx_घातer_index(rtwdev,
						      &pwr_idx->pwr_idx_5g,
						      bw, rate, group);
		*offset = hal->tx_pwr_by_rate_offset_5g[path][rate];
	पूर्ण

	*limit = rtw_phy_get_tx_घातer_limit(rtwdev, band, bw, path,
					    rate, ch, regd);
	*remnant = (rate <= DESC_RATE11M ? dm_info->txagc_remnant_cck :
		    dm_info->txagc_remnant_ofdm);
पूर्ण

u8
rtw_phy_get_tx_घातer_index(काष्ठा rtw_dev *rtwdev, u8 rf_path, u8 rate,
			   क्रमागत rtw_bandwidth bandwidth, u8 channel, u8 regd)
अणु
	काष्ठा rtw_घातer_params pwr_param = अणु0पूर्ण;
	u8 tx_घातer;
	s8 offset;

	rtw_get_tx_घातer_params(rtwdev, rf_path, rate, bandwidth,
				channel, regd, &pwr_param);

	tx_घातer = pwr_param.pwr_base;
	offset = min_t(s8, pwr_param.pwr_offset, pwr_param.pwr_limit);

	अगर (rtwdev->chip->en_dis_dpd)
		offset += rtw_phy_get_dis_dpd_by_rate_dअगरf(rtwdev, rate);

	tx_घातer += offset + pwr_param.pwr_remnant;

	अगर (tx_घातer > rtwdev->chip->max_घातer_index)
		tx_घातer = rtwdev->chip->max_घातer_index;

	वापस tx_घातer;
पूर्ण
EXPORT_SYMBOL(rtw_phy_get_tx_घातer_index);

अटल व्योम rtw_phy_set_tx_घातer_index_by_rs(काष्ठा rtw_dev *rtwdev,
					     u8 ch, u8 path, u8 rs)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 regd = rtwdev->regd.txpwr_regd;
	u8 *rates;
	u8 size;
	u8 rate;
	u8 pwr_idx;
	u8 bw;
	पूर्णांक i;

	अगर (rs >= RTW_RATE_SECTION_MAX)
		वापस;

	rates = rtw_rate_section[rs];
	size = rtw_rate_size[rs];
	bw = hal->current_band_width;
	क्रम (i = 0; i < size; i++) अणु
		rate = rates[i];
		pwr_idx = rtw_phy_get_tx_घातer_index(rtwdev, path, rate,
						     bw, ch, regd);
		hal->tx_pwr_tbl[path][rate] = pwr_idx;
	पूर्ण
पूर्ण

/* set tx घातer level by path क्रम each rates, note that the order of the rates
 * are *very* important, bacause 8822B/8821C combines every four bytes of tx
 * घातer index पूर्णांकo a four-byte घातer index रेजिस्टर, and calls set_tx_agc to
 * ग_लिखो these values पूर्णांकo hardware
 */
अटल व्योम rtw_phy_set_tx_घातer_level_by_path(काष्ठा rtw_dev *rtwdev,
					       u8 ch, u8 path)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 rs;

	/* करो not need cck rates अगर we are not in 2.4G */
	अगर (hal->current_band_type == RTW_BAND_2G)
		rs = RTW_RATE_SECTION_CCK;
	अन्यथा
		rs = RTW_RATE_SECTION_OFDM;

	क्रम (; rs < RTW_RATE_SECTION_MAX; rs++)
		rtw_phy_set_tx_घातer_index_by_rs(rtwdev, ch, path, rs);
पूर्ण

व्योम rtw_phy_set_tx_घातer_level(काष्ठा rtw_dev *rtwdev, u8 channel)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 path;

	mutex_lock(&hal->tx_घातer_mutex);

	क्रम (path = 0; path < hal->rf_path_num; path++)
		rtw_phy_set_tx_घातer_level_by_path(rtwdev, channel, path);

	chip->ops->set_tx_घातer_index(rtwdev);
	mutex_unlock(&hal->tx_घातer_mutex);
पूर्ण
EXPORT_SYMBOL(rtw_phy_set_tx_घातer_level);

अटल व्योम
rtw_phy_tx_घातer_by_rate_config_by_path(काष्ठा rtw_hal *hal, u8 path,
					u8 rs, u8 size, u8 *rates)
अणु
	u8 rate;
	u8 base_idx, rate_idx;
	s8 base_2g, base_5g;

	अगर (rs >= RTW_RATE_SECTION_VHT_1S)
		base_idx = rates[size - 3];
	अन्यथा
		base_idx = rates[size - 1];
	base_2g = hal->tx_pwr_by_rate_offset_2g[path][base_idx];
	base_5g = hal->tx_pwr_by_rate_offset_5g[path][base_idx];
	hal->tx_pwr_by_rate_base_2g[path][rs] = base_2g;
	hal->tx_pwr_by_rate_base_5g[path][rs] = base_5g;
	क्रम (rate = 0; rate < size; rate++) अणु
		rate_idx = rates[rate];
		hal->tx_pwr_by_rate_offset_2g[path][rate_idx] -= base_2g;
		hal->tx_pwr_by_rate_offset_5g[path][rate_idx] -= base_5g;
	पूर्ण
पूर्ण

व्योम rtw_phy_tx_घातer_by_rate_config(काष्ठा rtw_hal *hal)
अणु
	u8 path;

	क्रम (path = 0; path < RTW_RF_PATH_MAX; path++) अणु
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_CCK,
				rtw_cck_size, rtw_cck_rates);
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_OFDM,
				rtw_ofdm_size, rtw_ofdm_rates);
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_HT_1S,
				rtw_ht_1s_size, rtw_ht_1s_rates);
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_HT_2S,
				rtw_ht_2s_size, rtw_ht_2s_rates);
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_VHT_1S,
				rtw_vht_1s_size, rtw_vht_1s_rates);
		rtw_phy_tx_घातer_by_rate_config_by_path(hal, path,
				RTW_RATE_SECTION_VHT_2S,
				rtw_vht_2s_size, rtw_vht_2s_rates);
	पूर्ण
पूर्ण

अटल व्योम
__rtw_phy_tx_घातer_limit_config(काष्ठा rtw_hal *hal, u8 regd, u8 bw, u8 rs)
अणु
	s8 base;
	u8 ch;

	क्रम (ch = 0; ch < RTW_MAX_CHANNEL_NUM_2G; ch++) अणु
		base = hal->tx_pwr_by_rate_base_2g[0][rs];
		hal->tx_pwr_limit_2g[regd][bw][rs][ch] -= base;
	पूर्ण

	क्रम (ch = 0; ch < RTW_MAX_CHANNEL_NUM_5G; ch++) अणु
		base = hal->tx_pwr_by_rate_base_5g[0][rs];
		hal->tx_pwr_limit_5g[regd][bw][rs][ch] -= base;
	पूर्ण
पूर्ण

व्योम rtw_phy_tx_घातer_limit_config(काष्ठा rtw_hal *hal)
अणु
	u8 regd, bw, rs;

	/* शेष at channel 1 */
	hal->cch_by_bw[RTW_CHANNEL_WIDTH_20] = 1;

	क्रम (regd = 0; regd < RTW_REGD_MAX; regd++)
		क्रम (bw = 0; bw < RTW_CHANNEL_WIDTH_MAX; bw++)
			क्रम (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
				__rtw_phy_tx_घातer_limit_config(hal, regd, bw, rs);
पूर्ण

अटल व्योम rtw_phy_init_tx_घातer_limit(काष्ठा rtw_dev *rtwdev,
					u8 regd, u8 bw, u8 rs)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	s8 max_घातer_index = (s8)rtwdev->chip->max_घातer_index;
	u8 ch;

	/* 2.4G channels */
	क्रम (ch = 0; ch < RTW_MAX_CHANNEL_NUM_2G; ch++)
		hal->tx_pwr_limit_2g[regd][bw][rs][ch] = max_घातer_index;

	/* 5G channels */
	क्रम (ch = 0; ch < RTW_MAX_CHANNEL_NUM_5G; ch++)
		hal->tx_pwr_limit_5g[regd][bw][rs][ch] = max_घातer_index;
पूर्ण

व्योम rtw_phy_init_tx_घातer(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 regd, path, rate, rs, bw;

	/* init tx घातer by rate offset */
	क्रम (path = 0; path < RTW_RF_PATH_MAX; path++) अणु
		क्रम (rate = 0; rate < DESC_RATE_MAX; rate++) अणु
			hal->tx_pwr_by_rate_offset_2g[path][rate] = 0;
			hal->tx_pwr_by_rate_offset_5g[path][rate] = 0;
		पूर्ण
	पूर्ण

	/* init tx घातer limit */
	क्रम (regd = 0; regd < RTW_REGD_MAX; regd++)
		क्रम (bw = 0; bw < RTW_CHANNEL_WIDTH_MAX; bw++)
			क्रम (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
				rtw_phy_init_tx_घातer_limit(rtwdev, regd, bw,
							    rs);
पूर्ण

व्योम rtw_phy_config_swing_table(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_swing_table *swing_table)
अणु
	स्थिर काष्ठा rtw_pwr_track_tbl *tbl = rtwdev->chip->pwr_track_tbl;
	u8 channel = rtwdev->hal.current_channel;

	अगर (IS_CH_2G_BAND(channel)) अणु
		अगर (rtwdev->dm_info.tx_rate <= DESC_RATE11M) अणु
			swing_table->p[RF_PATH_A] = tbl->pwrtrk_2g_ccka_p;
			swing_table->n[RF_PATH_A] = tbl->pwrtrk_2g_ccka_n;
			swing_table->p[RF_PATH_B] = tbl->pwrtrk_2g_cckb_p;
			swing_table->n[RF_PATH_B] = tbl->pwrtrk_2g_cckb_n;
		पूर्ण अन्यथा अणु
			swing_table->p[RF_PATH_A] = tbl->pwrtrk_2ga_p;
			swing_table->n[RF_PATH_A] = tbl->pwrtrk_2ga_n;
			swing_table->p[RF_PATH_B] = tbl->pwrtrk_2gb_p;
			swing_table->n[RF_PATH_B] = tbl->pwrtrk_2gb_n;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_CH_5G_BAND_1(channel) || IS_CH_5G_BAND_2(channel)) अणु
		swing_table->p[RF_PATH_A] = tbl->pwrtrk_5ga_p[RTW_PWR_TRK_5G_1];
		swing_table->n[RF_PATH_A] = tbl->pwrtrk_5ga_n[RTW_PWR_TRK_5G_1];
		swing_table->p[RF_PATH_B] = tbl->pwrtrk_5gb_p[RTW_PWR_TRK_5G_1];
		swing_table->n[RF_PATH_B] = tbl->pwrtrk_5gb_n[RTW_PWR_TRK_5G_1];
	पूर्ण अन्यथा अगर (IS_CH_5G_BAND_3(channel)) अणु
		swing_table->p[RF_PATH_A] = tbl->pwrtrk_5ga_p[RTW_PWR_TRK_5G_2];
		swing_table->n[RF_PATH_A] = tbl->pwrtrk_5ga_n[RTW_PWR_TRK_5G_2];
		swing_table->p[RF_PATH_B] = tbl->pwrtrk_5gb_p[RTW_PWR_TRK_5G_2];
		swing_table->n[RF_PATH_B] = tbl->pwrtrk_5gb_n[RTW_PWR_TRK_5G_2];
	पूर्ण अन्यथा अगर (IS_CH_5G_BAND_4(channel)) अणु
		swing_table->p[RF_PATH_A] = tbl->pwrtrk_5ga_p[RTW_PWR_TRK_5G_3];
		swing_table->n[RF_PATH_A] = tbl->pwrtrk_5ga_n[RTW_PWR_TRK_5G_3];
		swing_table->p[RF_PATH_B] = tbl->pwrtrk_5gb_p[RTW_PWR_TRK_5G_3];
		swing_table->n[RF_PATH_B] = tbl->pwrtrk_5gb_n[RTW_PWR_TRK_5G_3];
	पूर्ण अन्यथा अणु
		swing_table->p[RF_PATH_A] = tbl->pwrtrk_2ga_p;
		swing_table->n[RF_PATH_A] = tbl->pwrtrk_2ga_n;
		swing_table->p[RF_PATH_B] = tbl->pwrtrk_2gb_p;
		swing_table->n[RF_PATH_B] = tbl->pwrtrk_2gb_n;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_phy_config_swing_table);

व्योम rtw_phy_pwrtrack_avg(काष्ठा rtw_dev *rtwdev, u8 thermal, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	ewma_thermal_add(&dm_info->avg_thermal[path], thermal);
	dm_info->thermal_avg[path] =
		ewma_thermal_पढ़ो(&dm_info->avg_thermal[path]);
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_avg);

bool rtw_phy_pwrtrack_thermal_changed(काष्ठा rtw_dev *rtwdev, u8 thermal,
				      u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 avg = ewma_thermal_पढ़ो(&dm_info->avg_thermal[path]);

	अगर (avg == thermal)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_thermal_changed);

u8 rtw_phy_pwrtrack_get_delta(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 therm_avg, therm_efuse, therm_delta;

	therm_avg = dm_info->thermal_avg[path];
	therm_efuse = rtwdev->efuse.thermal_meter[path];
	therm_delta = असल(therm_avg - therm_efuse);

	वापस min_t(u8, therm_delta, RTW_PWR_TRK_TBL_SZ - 1);
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_get_delta);

s8 rtw_phy_pwrtrack_get_pwridx(काष्ठा rtw_dev *rtwdev,
			       काष्ठा rtw_swing_table *swing_table,
			       u8 tbl_path, u8 therm_path, u8 delta)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	स्थिर u8 *delta_swing_table_idx_pos;
	स्थिर u8 *delta_swing_table_idx_neg;

	अगर (delta >= RTW_PWR_TRK_TBL_SZ) अणु
		rtw_warn(rtwdev, "power track table overflow\n");
		वापस 0;
	पूर्ण

	अगर (!swing_table) अणु
		rtw_warn(rtwdev, "swing table not configured\n");
		वापस 0;
	पूर्ण

	delta_swing_table_idx_pos = swing_table->p[tbl_path];
	delta_swing_table_idx_neg = swing_table->n[tbl_path];

	अगर (!delta_swing_table_idx_pos || !delta_swing_table_idx_neg) अणु
		rtw_warn(rtwdev, "invalid swing table index\n");
		वापस 0;
	पूर्ण

	अगर (dm_info->thermal_avg[therm_path] >
	    rtwdev->efuse.thermal_meter[therm_path])
		वापस delta_swing_table_idx_pos[delta];
	अन्यथा
		वापस -delta_swing_table_idx_neg[delta];
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_get_pwridx);

bool rtw_phy_pwrtrack_need_lck(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 delta_lck;

	delta_lck = असल(dm_info->thermal_avg[0] - dm_info->thermal_meter_lck);
	अगर (delta_lck >= rtwdev->chip->lck_threshold) अणु
		dm_info->thermal_meter_lck = dm_info->thermal_avg[0];
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_need_lck);

bool rtw_phy_pwrtrack_need_iqk(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 delta_iqk;

	delta_iqk = असल(dm_info->thermal_avg[0] - dm_info->thermal_meter_k);
	अगर (delta_iqk >= rtwdev->chip->iqk_threshold) अणु
		dm_info->thermal_meter_k = dm_info->thermal_avg[0];
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(rtw_phy_pwrtrack_need_iqk);
