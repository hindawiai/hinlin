<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#अगर_अघोषित ATH9K_HW_OPS_H
#घोषणा ATH9K_HW_OPS_H

#समावेश "hw.h"

/* Hardware core and driver accessible callbacks */

अटल अंतरभूत व्योम ath9k_hw_configpciघातersave(काष्ठा ath_hw *ah,
					       bool घातer_off)
अणु
	अगर (!ah->aspm_enabled)
		वापस;

	ath9k_hw_ops(ah)->config_pci_घातersave(ah, घातer_off);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_rxena(काष्ठा ath_hw *ah)
अणु
	ath9k_hw_ops(ah)->rx_enable(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_desc_link(काष्ठा ath_hw *ah, व्योम *ds,
					  u32 link)
अणु
	ath9k_hw_ops(ah)->set_desc_link(ds, link);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_hw_calibrate(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_channel *chan,
				     u8 rxchainmask, bool दीर्घcal)
अणु
	वापस ath9k_hw_ops(ah)->calibrate(ah, chan, rxchainmask, दीर्घcal);
पूर्ण

अटल अंतरभूत bool ath9k_hw_getisr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked,
				   u32 *sync_cause_p)
अणु
	वापस ath9k_hw_ops(ah)->get_isr(ah, masked, sync_cause_p);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_txdesc(काष्ठा ath_hw *ah, व्योम *ds,
				       काष्ठा ath_tx_info *i)
अणु
	वापस ath9k_hw_ops(ah)->set_txdesc(ah, ds, i);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_hw_txprocdesc(काष्ठा ath_hw *ah, व्योम *ds,
				      काष्ठा ath_tx_status *ts)
अणु
	वापस ath9k_hw_ops(ah)->proc_txdesc(ah, ds, ts);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_hw_get_duration(काष्ठा ath_hw *ah, स्थिर व्योम *ds,
					पूर्णांक index)
अणु
	वापस ath9k_hw_ops(ah)->get_duration(ah, ds, index);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_antभाग_comb_conf_get(काष्ठा ath_hw *ah,
		काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	ath9k_hw_ops(ah)->antभाग_comb_conf_get(ah, antconf);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_antभाग_comb_conf_set(काष्ठा ath_hw *ah,
		काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	ath9k_hw_ops(ah)->antभाग_comb_conf_set(ah, antconf);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_tx99_start(काष्ठा ath_hw *ah, u32 qnum)
अणु
	ath9k_hw_ops(ah)->tx99_start(ah, qnum);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_tx99_stop(काष्ठा ath_hw *ah)
अणु
	ath9k_hw_ops(ah)->tx99_stop(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_tx99_set_txघातer(काष्ठा ath_hw *ah, u8 घातer)
अणु
	अगर (ath9k_hw_ops(ah)->tx99_set_txघातer)
		ath9k_hw_ops(ah)->tx99_set_txघातer(ah, घातer);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

अटल अंतरभूत व्योम ath9k_hw_set_bt_ant_भागersity(काष्ठा ath_hw *ah, bool enable)
अणु
	अगर (ath9k_hw_ops(ah)->set_bt_ant_भागersity)
		ath9k_hw_ops(ah)->set_bt_ant_भागersity(ah, enable);
पूर्ण

अटल अंतरभूत bool ath9k_hw_is_aic_enabled(काष्ठा ath_hw *ah)
अणु
	अगर (ath9k_hw_निजी_ops(ah)->is_aic_enabled)
		वापस ath9k_hw_निजी_ops(ah)->is_aic_enabled(ah);

	वापस false;
पूर्ण

#पूर्ण_अगर

/* Private hardware call ops */

अटल अंतरभूत व्योम ath9k_hw_init_hang_checks(काष्ठा ath_hw *ah)
अणु
	ath9k_hw_निजी_ops(ah)->init_hang_checks(ah);
पूर्ण

अटल अंतरभूत bool ath9k_hw_detect_mac_hang(काष्ठा ath_hw *ah)
अणु
	वापस ath9k_hw_निजी_ops(ah)->detect_mac_hang(ah);
पूर्ण

अटल अंतरभूत bool ath9k_hw_detect_bb_hang(काष्ठा ath_hw *ah)
अणु
	वापस ath9k_hw_निजी_ops(ah)->detect_bb_hang(ah);
पूर्ण

/* PHY ops */

अटल अंतरभूत पूर्णांक ath9k_hw_rf_set_freq(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->rf_set_freq(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_spur_mitigate_freq(काष्ठा ath_hw *ah,
					       काष्ठा ath9k_channel *chan)
अणु
	ath9k_hw_निजी_ops(ah)->spur_mitigate_freq(ah, chan);
पूर्ण

अटल अंतरभूत bool ath9k_hw_set_rf_regs(काष्ठा ath_hw *ah,
					काष्ठा ath9k_channel *chan,
					u16 modesIndex)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->set_rf_regs)
		वापस true;

	वापस ath9k_hw_निजी_ops(ah)->set_rf_regs(ah, chan, modesIndex);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_init_bb(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->init_bb(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_channel_regs(काष्ठा ath_hw *ah,
					     काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->set_channel_regs(ah, chan);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_hw_process_ini(काष्ठा ath_hw *ah,
					काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->process_ini(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_olc_init(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->olc_init)
		वापस;

	वापस ath9k_hw_निजी_ops(ah)->olc_init(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_rभ_शेषe(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->set_rभ_शेषe(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_mark_phy_inactive(काष्ठा ath_hw *ah)
अणु
	वापस ath9k_hw_निजी_ops(ah)->mark_phy_inactive(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_delta_slope(काष्ठा ath_hw *ah,
					    काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->set_delta_slope(ah, chan);
पूर्ण

अटल अंतरभूत bool ath9k_hw_rfbus_req(काष्ठा ath_hw *ah)
अणु
	वापस ath9k_hw_निजी_ops(ah)->rfbus_req(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_rfbus_करोne(काष्ठा ath_hw *ah)
अणु
	वापस ath9k_hw_निजी_ops(ah)->rfbus_करोne(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_restore_chainmask(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->restore_chainmask)
		वापस;

	वापस ath9k_hw_निजी_ops(ah)->restore_chainmask(ah);
पूर्ण

अटल अंतरभूत bool ath9k_hw_ani_control(काष्ठा ath_hw *ah,
					क्रमागत ath9k_ani_cmd cmd, पूर्णांक param)
अणु
	वापस ath9k_hw_निजी_ops(ah)->ani_control(ah, cmd, param);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_करो_getnf(काष्ठा ath_hw *ah,
				     पूर्णांक16_t nfarray[NUM_NF_READINGS])
अणु
	ath9k_hw_निजी_ops(ah)->करो_getnf(ah, nfarray);
पूर्ण

अटल अंतरभूत bool ath9k_hw_init_cal(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->init_cal(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_setup_calibration(काष्ठा ath_hw *ah,
					      काष्ठा ath9k_cal_list *currCal)
अणु
	ath9k_hw_निजी_ops(ah)->setup_calibration(ah, currCal);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_hw_fast_chan_change(काष्ठा ath_hw *ah,
					    काष्ठा ath9k_channel *chan,
					    u8 *ini_reloaded)
अणु
	वापस ath9k_hw_निजी_ops(ah)->fast_chan_change(ah, chan,
							  ini_reloaded);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_set_radar_params(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->set_radar_params)
		वापस;

	ath9k_hw_निजी_ops(ah)->set_radar_params(ah, &ah->radar_conf);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_init_cal_settings(काष्ठा ath_hw *ah)
अणु
	ath9k_hw_निजी_ops(ah)->init_cal_settings(ah);
पूर्ण

अटल अंतरभूत u32 ath9k_hw_compute_pll_control(काष्ठा ath_hw *ah,
					       काष्ठा ath9k_channel *chan)
अणु
	वापस ath9k_hw_निजी_ops(ah)->compute_pll_control(ah, chan);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_init_mode_gain_regs(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->init_mode_gain_regs)
		वापस;

	ath9k_hw_निजी_ops(ah)->init_mode_gain_regs(ah);
पूर्ण

अटल अंतरभूत व्योम ath9k_hw_ani_cache_ini_regs(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_निजी_ops(ah)->ani_cache_ini_regs)
		वापस;

	ath9k_hw_निजी_ops(ah)->ani_cache_ini_regs(ah);
पूर्ण

#पूर्ण_अगर /* ATH9K_HW_OPS_H */
