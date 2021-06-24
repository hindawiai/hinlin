<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "coex.h"
#समावेश "fw.h"
#समावेश "ps.h"
#समावेश "debug.h"
#समावेश "reg.h"
#समावेश "phy.h"

अटल u8 rtw_coex_next_rssi_state(काष्ठा rtw_dev *rtwdev, u8 pre_state,
				   u8 rssi, u8 rssi_thresh)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 tol = chip->rssi_tolerance;
	u8 next_state;

	अगर (pre_state == COEX_RSSI_STATE_LOW ||
	    pre_state == COEX_RSSI_STATE_STAY_LOW) अणु
		अगर (rssi >= (rssi_thresh + tol))
			next_state = COEX_RSSI_STATE_HIGH;
		अन्यथा
			next_state = COEX_RSSI_STATE_STAY_LOW;
	पूर्ण अन्यथा अणु
		अगर (rssi < rssi_thresh)
			next_state = COEX_RSSI_STATE_LOW;
		अन्यथा
			next_state = COEX_RSSI_STATE_STAY_HIGH;
	पूर्ण

	वापस next_state;
पूर्ण

अटल व्योम rtw_coex_limited_tx(काष्ठा rtw_dev *rtwdev,
				bool tx_limit_en, bool ampdu_limit_en)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 num_of_active_port = 1;

	अगर (!chip->scbd_support)
		वापस;

	/* क्रमce max tx retry limit = 8 */
	अगर (coex_stat->wl_tx_limit_en == tx_limit_en &&
	    coex_stat->wl_ampdu_limit_en == ampdu_limit_en)
		वापस;

	अगर (!coex_stat->wl_tx_limit_en) अणु
		coex_stat->darfrc = rtw_पढ़ो32(rtwdev, REG_DARFRC);
		coex_stat->darfrch = rtw_पढ़ो32(rtwdev, REG_DARFRCH);
		coex_stat->retry_limit = rtw_पढ़ो16(rtwdev, REG_RETRY_LIMIT);
	पूर्ण

	अगर (!coex_stat->wl_ampdu_limit_en)
		coex_stat->ampdu_max_समय =
				rtw_पढ़ो8(rtwdev, REG_AMPDU_MAX_TIME_V1);

	coex_stat->wl_tx_limit_en = tx_limit_en;
	coex_stat->wl_ampdu_limit_en = ampdu_limit_en;

	अगर (tx_limit_en) अणु
		/* set BT polluted packet on क्रम tx rate adaptive,
		 * not including tx retry broken by PTA
		 */
		rtw_ग_लिखो8_set(rtwdev, REG_TX_HANG_CTRL, BIT_EN_GNT_BT_AWAKE);

		/* set queue lअगरe समय to aव्योम can't reach tx retry limit
		 * अगर tx is always broken by GNT_BT
		 */
		अगर (num_of_active_port <= 1)
			rtw_ग_लिखो8_set(rtwdev, REG_LIFETIME_EN, 0xf);
		rtw_ग_लिखो16(rtwdev, REG_RETRY_LIMIT, 0x0808);

		/* स्वतः rate fallback step within 8 retries */
		rtw_ग_लिखो32(rtwdev, REG_DARFRC, 0x1000000);
		rtw_ग_लिखो32(rtwdev, REG_DARFRCH, 0x4030201);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8_clr(rtwdev, REG_TX_HANG_CTRL, BIT_EN_GNT_BT_AWAKE);
		rtw_ग_लिखो8_clr(rtwdev, REG_LIFETIME_EN, 0xf);

		rtw_ग_लिखो16(rtwdev, REG_RETRY_LIMIT, coex_stat->retry_limit);
		rtw_ग_लिखो32(rtwdev, REG_DARFRC, coex_stat->darfrc);
		rtw_ग_लिखो32(rtwdev, REG_DARFRCH, coex_stat->darfrch);
	पूर्ण

	अगर (ampdu_limit_en)
		rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME_V1, 0x20);
	अन्यथा
		rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME_V1,
			   coex_stat->ampdu_max_समय);
पूर्ण

अटल व्योम rtw_coex_limited_wl(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	bool tx_limit = false;
	bool tx_agg_ctrl = false;

	अगर (!coex->under_5g && coex_dm->bt_status != COEX_BTSTATUS_NCON_IDLE) अणु
		tx_limit = true;
		tx_agg_ctrl = true;
	पूर्ण

	rtw_coex_limited_tx(rtwdev, tx_limit, tx_agg_ctrl);
पूर्ण

अटल bool rtw_coex_मुक्तrun_check(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 bt_rssi;
	u8 ant_distance = 10;

	अगर (coex_stat->bt_disabled)
		वापस false;

	अगर (efuse->share_ant || ant_distance <= 5 || !coex_stat->wl_gl_busy)
		वापस false;

	अगर (ant_distance >= 40 || coex_stat->bt_hid_pair_num >= 2)
		वापस true;

	/* ant_distance = 5 ~ 40  */
	अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]) &&
	    COEX_RSSI_HIGH(coex_dm->bt_rssi_state[0]))
		वापस true;

	अगर (coex_stat->wl_tput_dir == COEX_WL_TPUT_TX)
		bt_rssi = coex_dm->bt_rssi_state[0];
	अन्यथा
		bt_rssi = coex_dm->bt_rssi_state[1];

	अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[3]) &&
	    COEX_RSSI_HIGH(bt_rssi) &&
	    coex_stat->cnt_wl[COEX_CNT_WL_SCANAP] <= 5)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम rtw_coex_wl_slot_extend(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 para[6] = अणु0पूर्ण;

	para[0] = COEX_H2C69_WL_LEAKAP;
	para[1] = PARA1_H2C69_DIS_5MS;

	अगर (enable)
		para[1] = PARA1_H2C69_EN_5MS;
	अन्यथा
		coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] = 0;

	coex_stat->wl_slot_extend = enable;
	rtw_fw_bt_wअगरi_control(rtwdev, para[0], &para[1]);
पूर्ण

अटल व्योम rtw_coex_wl_ccklock_action(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;


	अगर (coex_stat->tdma_समयr_base == 3 && coex_stat->wl_slot_extend) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], set h2c 0x69 opcode 12 to turn off 5ms WL slot extend!!\n");
		rtw_coex_wl_slot_extend(rtwdev, false);
		वापस;
	पूर्ण

	अगर (coex_stat->wl_slot_extend && coex_stat->wl_क्रमce_lps_ctrl &&
	    !coex_stat->wl_cck_lock_ever) अणु
		अगर (coex_stat->wl_fw_dbg_info[7] <= 5)
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND]++;
		अन्यथा
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] = 0;

		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], 5ms WL slot extend cnt = %d!!\n",
			coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND]);

		अगर (coex_stat->cnt_wl[COEX_CNT_WL_5MS_NOEXTEND] == 7) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], set h2c 0x69 opcode 12 to turn off 5ms WL slot extend!!\n");
			rtw_coex_wl_slot_extend(rtwdev, false);
		पूर्ण
	पूर्ण अन्यथा अगर (!coex_stat->wl_slot_extend && coex_stat->wl_cck_lock) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], set h2c 0x69 opcode 12 to turn on 5ms WL slot extend!!\n");

		rtw_coex_wl_slot_extend(rtwdev, true);
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_wl_ccklock_detect(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	bool is_cck_lock_rate = false;

	अगर (coex_dm->bt_status == COEX_BTSTATUS_INQ_PAGE ||
	    coex_stat->bt_setup_link) अणु
		coex_stat->wl_cck_lock = false;
		coex_stat->wl_cck_lock_pre = false;
		वापस;
	पूर्ण

	अगर (coex_stat->wl_rx_rate <= COEX_CCK_2 ||
	    coex_stat->wl_rts_rx_rate <= COEX_CCK_2)
		is_cck_lock_rate = true;

	अगर (coex_stat->wl_connected && coex_stat->wl_gl_busy &&
	    COEX_RSSI_HIGH(coex_dm->wl_rssi_state[3]) &&
	    (coex_dm->bt_status == COEX_BTSTATUS_ACL_BUSY ||
	     coex_dm->bt_status == COEX_BTSTATUS_ACL_SCO_BUSY ||
	     coex_dm->bt_status == COEX_BTSTATUS_SCO_BUSY)) अणु
		अगर (is_cck_lock_rate) अणु
			coex_stat->wl_cck_lock = true;

			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], cck locking...\n");

		पूर्ण अन्यथा अणु
			coex_stat->wl_cck_lock = false;

			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], cck unlock...\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		coex_stat->wl_cck_lock = false;
	पूर्ण

	/* CCK lock identअगरication */
	अगर (coex_stat->wl_cck_lock && !coex_stat->wl_cck_lock_pre)
		ieee80211_queue_delayed_work(rtwdev->hw, &coex->wl_ccklock_work,
					     3 * HZ);

	coex_stat->wl_cck_lock_pre = coex_stat->wl_cck_lock;
पूर्ण

अटल व्योम rtw_coex_wl_noisy_detect(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cnt_cck;
	bool wl_cck_lock = false;

	/* wअगरi noisy environment identअगरication */
	cnt_cck = dm_info->cck_ok_cnt + dm_info->cck_err_cnt;

	अगर (!coex_stat->wl_gl_busy && !wl_cck_lock) अणु
		अगर (cnt_cck > 250) अणु
			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2]++;

			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] == 5) अणु
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (cnt_cck < 100) अणु
			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0]++;

			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] == 5) अणु
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] < 5)
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY1]++;

			अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] == 5) अणु
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY0] = 0;
				coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] = 0;
			पूर्ण
		पूर्ण

		अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY2] == 5)
			coex_stat->wl_noisy_level = 2;
		अन्यथा अगर (coex_stat->cnt_wl[COEX_CNT_WL_NOISY1] == 5)
			coex_stat->wl_noisy_level = 1;
		अन्यथा
			coex_stat->wl_noisy_level = 0;

		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], wl_noisy_level = %d\n",
			coex_stat->wl_noisy_level);
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_tdma_समयr_base(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 para[2] = अणु0पूर्ण;
	u8 बार;
	u16 tbtt_पूर्णांकerval = coex_stat->wl_beacon_पूर्णांकerval;

	अगर (coex_stat->tdma_समयr_base == type)
		वापस;

	coex_stat->tdma_समयr_base = type;

	para[0] = COEX_H2C69_TDMA_SLOT;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], tbtt_interval = %d\n",
		tbtt_पूर्णांकerval);

	अगर (type == TDMA_TIMER_TYPE_4SLOT && tbtt_पूर्णांकerval < 120) अणु
		para[1] = PARA1_H2C69_TDMA_4SLOT; /* 4-slot */
	पूर्ण अन्यथा अगर (tbtt_पूर्णांकerval < 80 && tbtt_पूर्णांकerval > 0) अणु
		बार = 100 / tbtt_पूर्णांकerval;
		अगर (100 % tbtt_पूर्णांकerval != 0)
			बार++;

		para[1] = FIELD_PREP(PARA1_H2C69_TBTT_TIMES, बार);
	पूर्ण अन्यथा अगर (tbtt_पूर्णांकerval >= 180) अणु
		बार = tbtt_पूर्णांकerval / 100;
		अगर (tbtt_पूर्णांकerval % 100 <= 80)
			बार--;

		para[1] = FIELD_PREP(PARA1_H2C69_TBTT_TIMES, बार) |
			  FIELD_PREP(PARA1_H2C69_TBTT_DIV100, 1);
	पूर्ण अन्यथा अणु
		para[1] = PARA1_H2C69_TDMA_2SLOT;
	पूर्ण

	rtw_fw_bt_wअगरi_control(rtwdev, para[0], &para[1]);

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): h2c_0x69 = 0x%x\n",
		__func__, para[1]);

	/* no 5ms_wl_slot_extend क्रम 4-slot mode  */
	अगर (coex_stat->tdma_समयr_base == 3)
		rtw_coex_wl_ccklock_action(rtwdev);
पूर्ण

अटल व्योम rtw_coex_set_wl_pri_mask(काष्ठा rtw_dev *rtwdev, u8 biपंचांगap,
				     u8 data)
अणु
	u32 addr;

	addr = REG_BT_COEX_TABLE_H + (biपंचांगap / 8);
	biपंचांगap = biपंचांगap % 8;

	rtw_ग_लिखो8_mask(rtwdev, addr, BIT(biपंचांगap), data);
पूर्ण

व्योम rtw_coex_ग_लिखो_scbd(काष्ठा rtw_dev *rtwdev, u16 bitpos, bool set)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u16 val = 0x2;

	अगर (!chip->scbd_support)
		वापस;

	val |= coex_stat->score_board;

	/* क्रम 8822b, scbd[10] is CQDDR on
	 * क्रम 8822c, scbd[10] is no fix 2M
	 */
	अगर (!chip->new_scbd10_def && (bitpos & COEX_SCBD_FIX2M)) अणु
		अगर (set)
			val &= ~COEX_SCBD_FIX2M;
		अन्यथा
			val |= COEX_SCBD_FIX2M;
	पूर्ण अन्यथा अणु
		अगर (set)
			val |= bitpos;
		अन्यथा
			val &= ~bitpos;
	पूर्ण

	अगर (val != coex_stat->score_board) अणु
		coex_stat->score_board = val;
		val |= BIT_BT_INT_EN;
		rtw_ग_लिखो16(rtwdev, REG_WIFI_BT_INFO, val);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_coex_ग_लिखो_scbd);

अटल u16 rtw_coex_पढ़ो_scbd(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (!chip->scbd_support)
		वापस 0;

	वापस (rtw_पढ़ो16(rtwdev, REG_WIFI_BT_INFO)) & ~(BIT_BT_INT_EN);
पूर्ण

अटल व्योम rtw_coex_check_rfk(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	u8 cnt = 0;
	u32 रुको_cnt;
	bool btk, wlk;

	अगर (coex_rfe->wlg_at_btg && chip->scbd_support &&
	    coex_stat->bt_iqk_state != 0xff) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], (Before Ant Setup) Delay by IQK\n");

		रुको_cnt = COEX_RFK_TIMEOUT / COEX_MIN_DELAY;
		करो अणु
			/* BT RFK */
			btk = !!(rtw_coex_पढ़ो_scbd(rtwdev) & COEX_SCBD_BT_RFK);

			/* WL RFK */
			wlk = !!(rtw_पढ़ो8(rtwdev, REG_ARFR4) & BIT_WL_RFK);

			अगर (!btk && !wlk)
				अवरोध;

			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], (Before Ant Setup) wlk = %d, btk = %d\n",
				wlk, btk);

			mdelay(COEX_MIN_DELAY);
		पूर्ण जबतक (++cnt < रुको_cnt);

		अगर (cnt >= रुको_cnt)
			coex_stat->bt_iqk_state = 0xff;
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_query_bt_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex_stat->bt_disabled)
		वापस;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_fw_query_bt_info(rtwdev);
पूर्ण

अटल व्योम rtw_coex_gnt_workaround(काष्ठा rtw_dev *rtwdev, bool क्रमce, u8 mode)
अणु
	rtw_coex_set_gnt_fix(rtwdev);
पूर्ण

अटल व्योम rtw_coex_monitor_bt_enable(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	bool bt_disabled = false;
	u16 score_board;

	अगर (chip->scbd_support) अणु
		score_board = rtw_coex_पढ़ो_scbd(rtwdev);
		bt_disabled = !(score_board & COEX_SCBD_ONOFF);
	पूर्ण

	अगर (coex_stat->bt_disabled != bt_disabled) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], BT state changed (%d) -> (%d)\n",
			coex_stat->bt_disabled, bt_disabled);

		coex_stat->bt_disabled = bt_disabled;
		coex_stat->bt_ble_scan_type = 0;
		coex_dm->cur_bt_lna_lvl = 0;

		अगर (!coex_stat->bt_disabled) अणु
			coex_stat->bt_reenable = true;
			ieee80211_queue_delayed_work(rtwdev->hw,
						     &coex->bt_reenable_work,
						     15 * HZ);
		पूर्ण अन्यथा अणु
			coex_stat->bt_mailbox_reply = false;
			coex_stat->bt_reenable = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_update_wl_link_info(काष्ठा rtw_dev *rtwdev, u8 reason)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;
	bool is_5G = false;
	bool wl_busy = false;
	bool scan = false, link = false;
	पूर्णांक i;
	u8 rssi_state;
	u8 rssi_step;
	u8 rssi;

	scan = test_bit(RTW_FLAG_SCANNING, rtwdev->flags);
	coex_stat->wl_connected = !!rtwdev->sta_cnt;

	wl_busy = test_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);
	अगर (wl_busy != coex_stat->wl_gl_busy) अणु
		अगर (wl_busy)
			coex_stat->wl_gl_busy = true;
		अन्यथा
			ieee80211_queue_delayed_work(rtwdev->hw,
						     &coex->wl_reमुख्य_work,
						     12 * HZ);
	पूर्ण

	अगर (stats->tx_throughput > stats->rx_throughput)
		coex_stat->wl_tput_dir = COEX_WL_TPUT_TX;
	अन्यथा
		coex_stat->wl_tput_dir = COEX_WL_TPUT_RX;

	अगर (scan || link || reason == COEX_RSN_2GCONSTART ||
	    reason == COEX_RSN_2GSCANSTART || reason == COEX_RSN_2GSWITCHBAND)
		coex_stat->wl_linkscan_proc = true;
	अन्यथा
		coex_stat->wl_linkscan_proc = false;

	rtw_coex_wl_noisy_detect(rtwdev);

	क्रम (i = 0; i < 4; i++) अणु
		rssi_state = coex_dm->wl_rssi_state[i];
		rssi_step = chip->wl_rssi_step[i];
		rssi = rtwdev->dm_info.min_rssi;
		rssi_state = rtw_coex_next_rssi_state(rtwdev, rssi_state,
						      rssi, rssi_step);
		coex_dm->wl_rssi_state[i] = rssi_state;
	पूर्ण

	अगर (coex_stat->wl_linkscan_proc || coex_stat->wl_hi_pri_task1 ||
	    coex_stat->wl_hi_pri_task2 || coex_stat->wl_gl_busy)
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_SCAN, true);
	अन्यथा
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_SCAN, false);

	चयन (reason) अणु
	हाल COEX_RSN_5GSCANSTART:
	हाल COEX_RSN_5GSWITCHBAND:
	हाल COEX_RSN_5GCONSTART:

		is_5G = true;
		अवरोध;
	हाल COEX_RSN_2GSCANSTART:
	हाल COEX_RSN_2GSWITCHBAND:
	हाल COEX_RSN_2GCONSTART:

		is_5G = false;
		अवरोध;
	शेष:
		अगर (rtwdev->hal.current_band_type == RTW_BAND_5G)
			is_5G = true;
		अन्यथा
			is_5G = false;
		अवरोध;
	पूर्ण

	coex->under_5g = is_5G;
पूर्ण

अटल अंतरभूत u8 *get_payload_from_coex_resp(काष्ठा sk_buff *resp)
अणु
	काष्ठा rtw_c2h_cmd *c2h;
	u32 pkt_offset;

	pkt_offset = *((u32 *)resp->cb);
	c2h = (काष्ठा rtw_c2h_cmd *)(resp->data + pkt_offset);

	वापस c2h->payload;
पूर्ण

व्योम rtw_coex_info_response(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	u8 *payload = get_payload_from_coex_resp(skb);

	अगर (payload[0] != COEX_RESP_ACK_BY_WL_FW)
		वापस;

	skb_queue_tail(&coex->queue, skb);
	wake_up(&coex->रुको);
पूर्ण

अटल काष्ठा sk_buff *rtw_coex_info_request(काष्ठा rtw_dev *rtwdev,
					     काष्ठा rtw_coex_info_req *req)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा sk_buff *skb_resp = शून्य;

	mutex_lock(&coex->mutex);

	rtw_fw_query_bt_mp_info(rtwdev, req);

	अगर (!रुको_event_समयout(coex->रुको, !skb_queue_empty(&coex->queue),
				COEX_REQUEST_TIMEOUT)) अणु
		rtw_err(rtwdev, "coex request time out\n");
		जाओ out;
	पूर्ण

	skb_resp = skb_dequeue(&coex->queue);
	अगर (!skb_resp) अणु
		rtw_err(rtwdev, "failed to get coex info response\n");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&coex->mutex);
	वापस skb_resp;
पूर्ण

अटल bool rtw_coex_get_bt_scan_type(काष्ठा rtw_dev *rtwdev, u8 *scan_type)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	u8 *payload;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_SCAN_TYPE;
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb)
		जाओ out;

	payload = get_payload_from_coex_resp(skb);
	*scan_type = GET_COEX_RESP_BT_SCAN_TYPE(payload);
	dev_kमुक्त_skb_any(skb);
	ret = true;

out:
	वापस ret;
पूर्ण

अटल bool rtw_coex_set_lna_स्थिरrain_level(काष्ठा rtw_dev *rtwdev,
					     u8 lna_स्थिरrain_level)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_LNA_CONSTRAINT;
	req.para1 = lna_स्थिरrain_level;
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb)
		जाओ out;

	dev_kमुक्त_skb_any(skb);
	ret = true;

out:
	वापस ret;
पूर्ण

#घोषणा हाल_BTSTATUS(src) \
	हाल COEX_BTSTATUS_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_bt_status_string(u8 bt_status)
अणु
	चयन (bt_status) अणु
	हाल_BTSTATUS(NCON_IDLE);
	हाल_BTSTATUS(CON_IDLE);
	हाल_BTSTATUS(INQ_PAGE);
	हाल_BTSTATUS(ACL_BUSY);
	हाल_BTSTATUS(SCO_BUSY);
	हाल_BTSTATUS(ACL_SCO_BUSY);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_update_bt_link_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 i;
	u8 rssi_state;
	u8 rssi_step;
	u8 rssi;

	/* update wl/bt rssi by btinfo */
	क्रम (i = 0; i < COEX_RSSI_STEP; i++) अणु
		rssi_state = coex_dm->bt_rssi_state[i];
		rssi_step = chip->bt_rssi_step[i];
		rssi = coex_stat->bt_rssi;
		rssi_state = rtw_coex_next_rssi_state(rtwdev, rssi_state, rssi,
						      rssi_step);
		coex_dm->bt_rssi_state[i] = rssi_state;
	पूर्ण

	अगर (coex_stat->bt_ble_scan_en &&
	    coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE] % 3 == 0) अणु
		u8 scan_type;

		अगर (rtw_coex_get_bt_scan_type(rtwdev, &scan_type)) अणु
			coex_stat->bt_ble_scan_type = scan_type;
			अगर ((coex_stat->bt_ble_scan_type & 0x1) == 0x1)
				coex_stat->bt_init_scan = true;
			अन्यथा
				coex_stat->bt_init_scan = false;
		पूर्ण
	पूर्ण

	coex_stat->bt_profile_num = 0;

	/* set link exist status */
	अगर (!(coex_stat->bt_info_lb2 & COEX_INFO_CONNECTION)) अणु
		coex_stat->bt_link_exist = false;
		coex_stat->bt_pan_exist = false;
		coex_stat->bt_a2dp_exist = false;
		coex_stat->bt_hid_exist = false;
		coex_stat->bt_hfp_exist = false;
	पूर्ण अन्यथा अणु
		/* connection exists */
		coex_stat->bt_link_exist = true;
		अगर (coex_stat->bt_info_lb2 & COEX_INFO_FTP) अणु
			coex_stat->bt_pan_exist = true;
			coex_stat->bt_profile_num++;
		पूर्ण अन्यथा अणु
			coex_stat->bt_pan_exist = false;
		पूर्ण

		अगर (coex_stat->bt_info_lb2 & COEX_INFO_A2DP) अणु
			coex_stat->bt_a2dp_exist = true;
			coex_stat->bt_profile_num++;
		पूर्ण अन्यथा अणु
			coex_stat->bt_a2dp_exist = false;
		पूर्ण

		अगर (coex_stat->bt_info_lb2 & COEX_INFO_HID) अणु
			coex_stat->bt_hid_exist = true;
			coex_stat->bt_profile_num++;
		पूर्ण अन्यथा अणु
			coex_stat->bt_hid_exist = false;
		पूर्ण

		अगर (coex_stat->bt_info_lb2 & COEX_INFO_SCO_ESCO) अणु
			coex_stat->bt_hfp_exist = true;
			coex_stat->bt_profile_num++;
		पूर्ण अन्यथा अणु
			coex_stat->bt_hfp_exist = false;
		पूर्ण
	पूर्ण

	अगर (coex_stat->bt_info_lb2 & COEX_INFO_INQ_PAGE) अणु
		coex_dm->bt_status = COEX_BTSTATUS_INQ_PAGE;
	पूर्ण अन्यथा अगर (!(coex_stat->bt_info_lb2 & COEX_INFO_CONNECTION)) अणु
		coex_dm->bt_status = COEX_BTSTATUS_NCON_IDLE;
		coex_stat->bt_multi_link_reमुख्य = false;
	पूर्ण अन्यथा अगर (coex_stat->bt_info_lb2 == COEX_INFO_CONNECTION) अणु
		coex_dm->bt_status = COEX_BTSTATUS_CON_IDLE;
	पूर्ण अन्यथा अगर ((coex_stat->bt_info_lb2 & COEX_INFO_SCO_ESCO) ||
		   (coex_stat->bt_info_lb2 & COEX_INFO_SCO_BUSY)) अणु
		अगर (coex_stat->bt_info_lb2 & COEX_INFO_ACL_BUSY)
			coex_dm->bt_status = COEX_BTSTATUS_ACL_SCO_BUSY;
		अन्यथा
			coex_dm->bt_status = COEX_BTSTATUS_SCO_BUSY;
	पूर्ण अन्यथा अगर (coex_stat->bt_info_lb2 & COEX_INFO_ACL_BUSY) अणु
		coex_dm->bt_status = COEX_BTSTATUS_ACL_BUSY;
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = COEX_BTSTATUS_MAX;
	पूर्ण

	coex_stat->cnt_bt[COEX_CNT_BT_INFOUPDATE]++;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(), %s!!!\n", __func__,
		rtw_coex_get_bt_status_string(coex_dm->bt_status));
पूर्ण

अटल व्योम rtw_coex_update_wl_ch_info(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex_dm *coex_dm = &rtwdev->coex.dm;
	u8 link = 0;
	u8 center_chan = 0;
	u8 bw;
	पूर्णांक i;

	bw = rtwdev->hal.current_band_width;

	अगर (type != COEX_MEDIA_DISCONNECT)
		center_chan = rtwdev->hal.current_channel;

	अगर (center_chan == 0) अणु
		link = 0;
		center_chan = 0;
		bw = 0;
	पूर्ण अन्यथा अगर (center_chan <= 14) अणु
		link = 0x1;

		अगर (bw == RTW_CHANNEL_WIDTH_40)
			bw = chip->bt_afh_span_bw40;
		अन्यथा
			bw = chip->bt_afh_span_bw20;
	पूर्ण अन्यथा अगर (chip->afh_5g_num > 1) अणु
		क्रम (i = 0; i < chip->afh_5g_num; i++) अणु
			अगर (center_chan == chip->afh_5g[i].wl_5g_ch) अणु
				link = 0x3;
				center_chan = chip->afh_5g[i].bt_skip_ch;
				bw = chip->afh_5g[i].bt_skip_span;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	coex_dm->wl_ch_info[0] = link;
	coex_dm->wl_ch_info[1] = center_chan;
	coex_dm->wl_ch_info[2] = bw;

	rtw_fw_wl_ch_info(rtwdev, link, center_chan, bw);
	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], %s: para[0:2] = 0x%x 0x%x 0x%x\n", __func__, link,
		center_chan, bw);
पूर्ण

अटल व्योम rtw_coex_set_bt_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 bt_pwr_dec_lvl)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	अगर (bt_pwr_dec_lvl == coex_dm->cur_bt_pwr_lvl)
		वापस;

	coex_dm->cur_bt_pwr_lvl = bt_pwr_dec_lvl;

	rtw_fw_क्रमce_bt_tx_घातer(rtwdev, bt_pwr_dec_lvl);
पूर्ण

अटल व्योम rtw_coex_set_bt_rx_gain(काष्ठा rtw_dev *rtwdev, u8 bt_lna_lvl)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	अगर (bt_lna_lvl == coex_dm->cur_bt_lna_lvl)
		वापस;

	coex_dm->cur_bt_lna_lvl = bt_lna_lvl;

	/* notअगरy BT rx gain table changed */
	अगर (bt_lna_lvl < 7) अणु
		rtw_coex_set_lna_स्थिरrain_level(rtwdev, bt_lna_lvl);
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_RXGAIN, true);
	पूर्ण अन्यथा अणु
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_RXGAIN, false);
	पूर्ण
	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): bt_rx_LNA_level = %d\n",
		__func__, bt_lna_lvl);
पूर्ण

अटल व्योम rtw_coex_set_rf_para(काष्ठा rtw_dev *rtwdev,
				 काष्ठा coex_rf_para para)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 offset = 0;

	अगर (coex->मुक्तrun && coex_stat->cnt_wl[COEX_CNT_WL_SCANAP] <= 5)
		offset = 3;

	rtw_coex_set_wl_tx_घातer(rtwdev, para.wl_pwr_dec_lvl);
	rtw_coex_set_bt_tx_घातer(rtwdev, para.bt_pwr_dec_lvl + offset);
	rtw_coex_set_wl_rx_gain(rtwdev, para.wl_low_gain_en);
	rtw_coex_set_bt_rx_gain(rtwdev, para.bt_lna_lvl);
पूर्ण

u32 rtw_coex_पढ़ो_indirect_reg(काष्ठा rtw_dev *rtwdev, u16 addr)
अणु
	u32 val;

	अगर (!ltecoex_पढ़ो_reg(rtwdev, addr, &val)) अणु
		rtw_err(rtwdev, "failed to read indirect register\n");
		वापस 0;
	पूर्ण

	वापस val;
पूर्ण
EXPORT_SYMBOL(rtw_coex_पढ़ो_indirect_reg);

व्योम rtw_coex_ग_लिखो_indirect_reg(काष्ठा rtw_dev *rtwdev, u16 addr,
				 u32 mask, u32 val)
अणु
	u32 shअगरt = __ffs(mask);
	u32 पंचांगp;

	पंचांगp = rtw_coex_पढ़ो_indirect_reg(rtwdev, addr);
	पंचांगp = (पंचांगp & (~mask)) | ((val << shअगरt) & mask);

	अगर (!ltecoex_reg_ग_लिखो(rtwdev, addr, पंचांगp))
		rtw_err(rtwdev, "failed to write indirect register\n");
पूर्ण
EXPORT_SYMBOL(rtw_coex_ग_लिखो_indirect_reg);

अटल व्योम rtw_coex_coex_ctrl_owner(काष्ठा rtw_dev *rtwdev, bool wअगरi_control)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_hw_reg *btg_reg = chip->btg_reg;

	अगर (wअगरi_control) अणु
		rtw_ग_लिखो8_set(rtwdev, REG_SYS_SDIO_CTRL + 3,
			       BIT_LTE_MUX_CTRL_PATH >> 24);
		अगर (btg_reg)
			rtw_ग_लिखो8_set(rtwdev, btg_reg->addr, btg_reg->mask);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8_clr(rtwdev, REG_SYS_SDIO_CTRL + 3,
			       BIT_LTE_MUX_CTRL_PATH >> 24);
		अगर (btg_reg)
			rtw_ग_लिखो8_clr(rtwdev, btg_reg->addr, btg_reg->mask);
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_set_gnt_bt(काष्ठा rtw_dev *rtwdev, u8 state)
अणु
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, 0xc000, state);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, 0x0c00, state);
पूर्ण

अटल व्योम rtw_coex_set_gnt_wl(काष्ठा rtw_dev *rtwdev, u8 state)
अणु
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, 0x3000, state);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, 0x0300, state);
पूर्ण

अटल व्योम rtw_btc_wltoggle_table_a(काष्ठा rtw_dev *rtwdev, bool क्रमce,
				     u8 table_हाल)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 h2c_para[6] = अणु0पूर्ण;
	u32 table_wl = 0x5a5a5a5a;

	h2c_para[0] = COEX_H2C69_TOGGLE_TABLE_A;
	/* no definition */
	h2c_para[1] = 0x1;

	अगर (efuse->share_ant) अणु
		अगर (table_हाल < chip->table_sant_num)
			table_wl = chip->table_sant[table_हाल].wl;
	पूर्ण अन्यथा अणु
		अगर (table_हाल < chip->table_nsant_num)
			table_wl = chip->table_nsant[table_हाल].wl;
	पूर्ण

	/* tell WL FW WL slot toggle table-A*/
	h2c_para[2] = (u8)u32_get_bits(table_wl, GENMASK(7, 0));
	h2c_para[3] = (u8)u32_get_bits(table_wl, GENMASK(15, 8));
	h2c_para[4] = (u8)u32_get_bits(table_wl, GENMASK(23, 16));
	h2c_para[5] = (u8)u32_get_bits(table_wl, GENMASK(31, 24));

	rtw_fw_bt_wअगरi_control(rtwdev, h2c_para[0], &h2c_para[1]);

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], %s(): H2C = [%02x %02x %02x %02x %02x %02x]\n",
		__func__, h2c_para[0], h2c_para[1], h2c_para[2],
		h2c_para[3], h2c_para[4], h2c_para[5]);
पूर्ण

#घोषणा COEX_WL_SLOT_TOGLLE 0x5a5a5aaa
अटल व्योम rtw_btc_wltoggle_table_b(काष्ठा rtw_dev *rtwdev, bool क्रमce,
				     u8 पूर्णांकerval, u32 table)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 cur_h2c_para[6] = अणु0पूर्ण;
	u8 i;

	cur_h2c_para[0] = COEX_H2C69_TOGGLE_TABLE_B;
	cur_h2c_para[1] = पूर्णांकerval;
	cur_h2c_para[2] = (u8)u32_get_bits(table, GENMASK(7, 0));
	cur_h2c_para[3] = (u8)u32_get_bits(table, GENMASK(15, 8));
	cur_h2c_para[4] = (u8)u32_get_bits(table, GENMASK(23, 16));
	cur_h2c_para[5] = (u8)u32_get_bits(table, GENMASK(31, 24));

	coex_stat->wl_toggle_पूर्णांकerval = पूर्णांकerval;

	क्रम (i = 0; i <= 5; i++)
		coex_stat->wl_toggle_para[i] = cur_h2c_para[i];

	rtw_fw_bt_wअगरi_control(rtwdev, cur_h2c_para[0], &cur_h2c_para[1]);

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], %s(): H2C = [%02x %02x %02x %02x %02x %02x]\n",
		__func__, cur_h2c_para[0], cur_h2c_para[1], cur_h2c_para[2],
		cur_h2c_para[3], cur_h2c_para[4], cur_h2c_para[5]);
पूर्ण

अटल व्योम rtw_coex_set_table(काष्ठा rtw_dev *rtwdev, bool क्रमce, u32 table0,
			       u32 table1)
अणु
#घोषणा DEF_BRK_TABLE_VAL 0xf0ffffff
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	/* If last tdma is wl slot toggle, क्रमce ग_लिखो table*/
	अगर (!क्रमce && coex_dm->reason != COEX_RSN_LPS) अणु
		अगर (table0 == rtw_पढ़ो32(rtwdev, REG_BT_COEX_TABLE0) &&
		    table1 == rtw_पढ़ो32(rtwdev, REG_BT_COEX_TABLE1))
			वापस;
	पूर्ण
	rtw_ग_लिखो32(rtwdev, REG_BT_COEX_TABLE0, table0);
	rtw_ग_लिखो32(rtwdev, REG_BT_COEX_TABLE1, table1);
	rtw_ग_लिखो32(rtwdev, REG_BT_COEX_BRK_TABLE, DEF_BRK_TABLE_VAL);

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], %s(): 0x6c0 = %x, 0x6c4 = %x\n", __func__, table0,
		table1);
पूर्ण

अटल व्योम rtw_coex_table(काष्ठा rtw_dev *rtwdev, bool क्रमce, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	coex_dm->cur_table = type;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], Coex_Table - %d\n", type);

	अगर (efuse->share_ant) अणु
		अगर (type < chip->table_sant_num)
			rtw_coex_set_table(rtwdev, क्रमce,
					   chip->table_sant[type].bt,
					   chip->table_sant[type].wl);
	पूर्ण अन्यथा अणु
		type = type - 100;
		अगर (type < chip->table_nsant_num)
			rtw_coex_set_table(rtwdev, क्रमce,
					   chip->table_nsant[type].bt,
					   chip->table_nsant[type].wl);
	पूर्ण
	अगर (coex_stat->wl_slot_toggle_change)
		rtw_btc_wltoggle_table_a(rtwdev, true, type);
पूर्ण

अटल व्योम rtw_coex_ignore_wlan_act(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	rtw_fw_bt_ignore_wlan_action(rtwdev, enable);
पूर्ण

अटल व्योम rtw_coex_घातer_save_state(काष्ठा rtw_dev *rtwdev, u8 ps_type,
				      u8 lps_val, u8 rpwm_val)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 lps_mode = 0x0;

	lps_mode = rtwdev->lps_conf.mode;

	चयन (ps_type) अणु
	हाल COEX_PS_WIFI_NATIVE:
		/* recover to original 32k low घातer setting */
		coex_stat->wl_क्रमce_lps_ctrl = false;
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s(): COEX_PS_WIFI_NATIVE\n", __func__);
		rtw_leave_lps(rtwdev);
		अवरोध;
	हाल COEX_PS_LPS_OFF:
		coex_stat->wl_क्रमce_lps_ctrl = true;
		अगर (lps_mode)
			rtw_fw_coex_tdma_type(rtwdev, 0, 0, 0, 0, 0);

		rtw_leave_lps(rtwdev);
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s(): COEX_PS_LPS_OFF\n", __func__);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_set_tdma(काष्ठा rtw_dev *rtwdev, u8 byte1, u8 byte2,
			      u8 byte3, u8 byte4, u8 byte5)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 ps_type = COEX_PS_WIFI_NATIVE;
	bool ap_enable = false;

	अगर (ap_enable && (byte1 & BIT(4) && !(byte1 & BIT(5)))) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): AP mode\n",
			__func__);

		byte1 &= ~BIT(4);
		byte1 |= BIT(5);

		byte5 |= BIT(5);
		byte5 &= ~BIT(6);

		ps_type = COEX_PS_WIFI_NATIVE;
		rtw_coex_घातer_save_state(rtwdev, ps_type, 0x0, 0x0);
	पूर्ण अन्यथा अगर (byte1 & BIT(4) && !(byte1 & BIT(5))) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s(): Force LPS (byte1 = 0x%x)\n", __func__,
			byte1);

		अगर (chip->pstdma_type == COEX_PSTDMA_FORCE_LPSOFF)
			ps_type = COEX_PS_LPS_OFF;
		अन्यथा
			ps_type = COEX_PS_LPS_ON;
		rtw_coex_घातer_save_state(rtwdev, ps_type, 0x50, 0x4);
	पूर्ण अन्यथा अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s(): native power save (byte1 = 0x%x)\n",
			__func__, byte1);

		ps_type = COEX_PS_WIFI_NATIVE;
		rtw_coex_घातer_save_state(rtwdev, ps_type, 0x0, 0x0);
	पूर्ण

	coex_dm->ps_tdma_para[0] = byte1;
	coex_dm->ps_tdma_para[1] = byte2;
	coex_dm->ps_tdma_para[2] = byte3;
	coex_dm->ps_tdma_para[3] = byte4;
	coex_dm->ps_tdma_para[4] = byte5;

	rtw_fw_coex_tdma_type(rtwdev, byte1, byte2, byte3, byte4, byte5);

	अगर (byte1 & BIT(2)) अणु
		coex_stat->wl_slot_toggle = true;
		coex_stat->wl_slot_toggle_change = false;
	पूर्ण अन्यथा अणु
		coex_stat->wl_slot_toggle_change = coex_stat->wl_slot_toggle;
		coex_stat->wl_slot_toggle = false;
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_tdma(काष्ठा rtw_dev *rtwdev, bool क्रमce, u32 tहाल)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 n, type;
	bool turn_on;
	bool wl_busy = false;

	अगर (tहाल & TDMA_4SLOT) /* 4-slot (50ms) mode */
		rtw_coex_tdma_समयr_base(rtwdev, TDMA_TIMER_TYPE_4SLOT);
	अन्यथा
		rtw_coex_tdma_समयr_base(rtwdev, TDMA_TIMER_TYPE_2SLOT);

	type = (u8)(tहाल & 0xff);

	turn_on = (type == 0 || type == 100) ? false : true;

	अगर (!क्रमce && turn_on == coex_dm->cur_ps_tdma_on &&
	    type == coex_dm->cur_ps_tdma) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], Skip TDMA because no change TDMA(%s, %d)\n",
			(coex_dm->cur_ps_tdma_on ? "on" : "off"),
			coex_dm->cur_ps_tdma);

		वापस;
	पूर्ण
	wl_busy = test_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);

	अगर ((coex_stat->bt_a2dp_exist &&
	     (coex_stat->bt_inq_reमुख्य || coex_stat->bt_multi_link)) ||
	    !wl_busy)
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_TDMA, false);
	अन्यथा
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_TDMA, true);

	/* update pre state */
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	अगर (efuse->share_ant) अणु
		अगर (type < chip->tdma_sant_num)
			rtw_coex_set_tdma(rtwdev,
					  chip->tdma_sant[type].para[0],
					  chip->tdma_sant[type].para[1],
					  chip->tdma_sant[type].para[2],
					  chip->tdma_sant[type].para[3],
					  chip->tdma_sant[type].para[4]);
	पूर्ण अन्यथा अणु
		n = type - 100;
		अगर (n < chip->tdma_nsant_num)
			rtw_coex_set_tdma(rtwdev,
					  chip->tdma_nsant[n].para[0],
					  chip->tdma_nsant[n].para[1],
					  chip->tdma_nsant[n].para[2],
					  chip->tdma_nsant[n].para[3],
					  chip->tdma_nsant[n].para[4]);
	पूर्ण


	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], coex tdma type(%s, %d)\n",
		turn_on ? "on" : "off", type);
पूर्ण

अटल व्योम rtw_coex_set_ant_path(काष्ठा rtw_dev *rtwdev, bool क्रमce, u8 phase)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	u8 ctrl_type = COEX_SWITCH_CTRL_MAX;
	u8 pos_type = COEX_SWITCH_TO_MAX;

	अगर (!क्रमce && coex_dm->cur_ant_pos_type == phase)
		वापस;

	coex_dm->cur_ant_pos_type = phase;

	/* aव्योम चयन coex_ctrl_owner during BT IQK */
	rtw_coex_check_rfk(rtwdev);

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex],  coex_stat->bt_disabled = 0x%x\n",
		coex_stat->bt_disabled);

	चयन (phase) अणु
	हाल COEX_SET_ANT_POWERON:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_COEX_POWERON\n", __func__);
		/* set path control owner to BT at घातer-on */
		अगर (coex_stat->bt_disabled)
			rtw_coex_coex_ctrl_owner(rtwdev, true);
		अन्यथा
			rtw_coex_coex_ctrl_owner(rtwdev, false);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		अवरोध;
	हाल COEX_SET_ANT_INIT:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_COEX_INIT\n", __func__);
		अगर (coex_stat->bt_disabled) अणु
			/* set GNT_BT to SW low */
			rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_LOW);

			/* set GNT_WL to SW high */
			rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);
		पूर्ण अन्यथा अणु
			/* set GNT_BT to SW high */
			rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_HIGH);

			/* set GNT_WL to SW low */
			rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_LOW);
		पूर्ण

		/* set path control owner to wl at initial step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_BT;
		अवरोध;
	हाल COEX_SET_ANT_WONLY:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_WLANONLY_INIT\n", __func__);
		/* set GNT_BT to SW Low */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_SW_LOW);

		/* set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at initial step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG;
		अवरोध;
	हाल COEX_SET_ANT_WOFF:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_WLAN_OFF\n", __func__);
		/* set path control owner to BT */
		rtw_coex_coex_ctrl_owner(rtwdev, false);

		ctrl_type = COEX_SWITCH_CTRL_BY_BT;
		pos_type = COEX_SWITCH_TO_NOCARE;
		अवरोध;
	हाल COEX_SET_ANT_2G:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_RUNTIME\n", __func__);
		/* set GNT_BT to PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set GNT_WL to PTA */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set path control owner to wl at runसमय step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_PTA;
		pos_type = COEX_SWITCH_TO_NOCARE;
		अवरोध;
	हाल COEX_SET_ANT_5G:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_5G_RUNTIME\n", __func__);

		/* set GNT_BT to HW PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at runसमय step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLA;
		अवरोध;
	हाल COEX_SET_ANT_2G_FREERUN:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_FREERUN\n", __func__);

		/* set GNT_BT to HW PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* Set GNT_WL to SW high */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_SW_HIGH);

		/* set path control owner to wl at runसमय step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG_BT;
		अवरोध;
	हाल COEX_SET_ANT_2G_WLBT:
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s() - PHASE_2G_WLBT\n", __func__);
		/* set GNT_BT to HW PTA */
		rtw_coex_set_gnt_bt(rtwdev, COEX_GNT_SET_HW_PTA);

		/* Set GNT_WL to HW PTA */
		rtw_coex_set_gnt_wl(rtwdev, COEX_GNT_SET_HW_PTA);

		/* set path control owner to wl at runसमय step */
		rtw_coex_coex_ctrl_owner(rtwdev, true);

		ctrl_type = COEX_SWITCH_CTRL_BY_BBSW;
		pos_type = COEX_SWITCH_TO_WLG_BT;
		अवरोध;
	शेष:
		WARN(1, "unknown phase when setting antenna path\n");
		वापस;
	पूर्ण

	अगर (ctrl_type < COEX_SWITCH_CTRL_MAX && pos_type < COEX_SWITCH_TO_MAX &&
	    coex_rfe->ant_चयन_exist)
		rtw_coex_set_ant_चयन(rtwdev, ctrl_type, pos_type);
पूर्ण

#घोषणा हाल_ALGO(src) \
	हाल COEX_ALGO_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_algo_string(u8 algo)
अणु
	चयन (algo) अणु
	हाल_ALGO(NOPROखाता);
	हाल_ALGO(HFP);
	हाल_ALGO(HID);
	हाल_ALGO(A2DP);
	हाल_ALGO(PAN);
	हाल_ALGO(A2DP_HID);
	हाल_ALGO(A2DP_PAN);
	हाल_ALGO(PAN_HID);
	हाल_ALGO(A2DP_PAN_HID);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

#घोषणा हाल_BT_PROखाता(src) \
	हाल BPM_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_bt_profile_string(u8 bt_profile)
अणु
	चयन (bt_profile) अणु
	हाल_BT_PROखाता(NOPROखाता);
	हाल_BT_PROखाता(HFP);
	हाल_BT_PROखाता(HID);
	हाल_BT_PROखाता(A2DP);
	हाल_BT_PROखाता(PAN);
	हाल_BT_PROखाता(HID_HFP);
	हाल_BT_PROखाता(A2DP_HFP);
	हाल_BT_PROखाता(A2DP_HID);
	हाल_BT_PROखाता(A2DP_HID_HFP);
	हाल_BT_PROखाता(PAN_HFP);
	हाल_BT_PROखाता(PAN_HID);
	हाल_BT_PROखाता(PAN_HID_HFP);
	हाल_BT_PROखाता(PAN_A2DP);
	हाल_BT_PROखाता(PAN_A2DP_HFP);
	हाल_BT_PROखाता(PAN_A2DP_HID);
	हाल_BT_PROखाता(PAN_A2DP_HID_HFP);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल u8 rtw_coex_algorithm(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 algorithm = COEX_ALGO_NOPROखाता;
	u8 profile_map = 0;

	अगर (coex_stat->bt_hfp_exist)
		profile_map |= BPM_HFP;
	अगर (coex_stat->bt_hid_exist)
		profile_map |= BPM_HID;
	अगर (coex_stat->bt_a2dp_exist)
		profile_map |= BPM_A2DP;
	अगर (coex_stat->bt_pan_exist)
		profile_map |= BPM_PAN;

	चयन (profile_map) अणु
	हाल BPM_HFP:
		algorithm = COEX_ALGO_HFP;
		अवरोध;
	हाल           BPM_HID:
	हाल BPM_HFP + BPM_HID:
		algorithm = COEX_ALGO_HID;
		अवरोध;
	हाल BPM_HFP           + BPM_A2DP:
	हाल           BPM_HID + BPM_A2DP:
	हाल BPM_HFP + BPM_HID + BPM_A2DP:
		algorithm = COEX_ALGO_A2DP_HID;
		अवरोध;
	हाल BPM_HFP                      + BPM_PAN:
	हाल           BPM_HID            + BPM_PAN:
	हाल BPM_HFP + BPM_HID            + BPM_PAN:
		algorithm = COEX_ALGO_PAN_HID;
		अवरोध;
	हाल BPM_HFP           + BPM_A2DP + BPM_PAN:
	हाल           BPM_HID + BPM_A2DP + BPM_PAN:
	हाल BPM_HFP + BPM_HID + BPM_A2DP + BPM_PAN:
		algorithm = COEX_ALGO_A2DP_PAN_HID;
		अवरोध;
	हाल                                BPM_PAN:
		algorithm = COEX_ALGO_PAN;
		अवरोध;
	हाल                     BPM_A2DP + BPM_PAN:
		algorithm = COEX_ALGO_A2DP_PAN;
		अवरोध;
	हाल                     BPM_A2DP:
		अगर (coex_stat->bt_multi_link) अणु
			अगर (coex_stat->bt_hid_pair_num > 0)
				algorithm = COEX_ALGO_A2DP_HID;
			अन्यथा
				algorithm = COEX_ALGO_A2DP_PAN;
		पूर्ण अन्यथा अणु
			algorithm = COEX_ALGO_A2DP;
		पूर्ण
		अवरोध;
	शेष:
		algorithm = COEX_ALGO_NOPROखाता;
		अवरोध;
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], BT Profile = %s => Algorithm = %s\n",
		rtw_coex_get_bt_profile_string(profile_map),
		rtw_coex_get_algo_string(algorithm));
	वापस algorithm;
पूर्ण

अटल व्योम rtw_coex_action_coex_all_off(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 2;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_मुक्तrun(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 level = 0;
	bool bt_afh_loss = true;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	अगर (efuse->share_ant)
		वापस;

	coex->मुक्तrun = true;

	अगर (bt_afh_loss)
		rtw_coex_update_wl_ch_info(rtwdev, COEX_MEDIA_CONNECT);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G_FREERUN);

	rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_FIX2M, false);

	अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[0]))
		level = 2;
	अन्यथा अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]))
		level = 3;
	अन्यथा अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[2]))
		level = 4;
	अन्यथा
		level = 5;

	अगर (level > chip->wl_rf_para_num - 1)
		level = chip->wl_rf_para_num - 1;

	अगर (coex_stat->wl_tput_dir == COEX_WL_TPUT_TX)
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_tx[level]);
	अन्यथा
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[level]);

	rtw_coex_table(rtwdev, false, 100);
	rtw_coex_tdma(rtwdev, false, 100);
पूर्ण

अटल व्योम rtw_coex_action_rf4ce(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 9;
		tdma_हाल = 16;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_whql_test(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 2;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_relink(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	u32 slot_type = 0;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु /* Shared-Ant */
		अगर (coex_stat->wl_gl_busy) अणु
			table_हाल = 26;
			अगर (coex_stat->bt_hid_exist &&
			    coex_stat->bt_profile_num == 1) अणु
				slot_type = TDMA_4SLOT;
				tdma_हाल = 20;
			पूर्ण अन्यथा अणु
				tdma_हाल = 20;
			पूर्ण
		पूर्ण अन्यथा अणु
			table_हाल = 1;
			tdma_हाल = 0;
		पूर्ण
	पूर्ण अन्यथा अणु /* Non-Shared-Ant */
		अगर (coex_stat->wl_gl_busy)
			table_हाल = 115;
		अन्यथा
			table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_bt_idle(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	u8 table_हाल = 0xff, tdma_हाल = 0xff;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (coex_rfe->ant_चयन_with_bt &&
	    coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) अणु
		अगर (efuse->share_ant &&
		    COEX_RSSI_HIGH(coex_dm->wl_rssi_state[3]) &&
		    coex_stat->wl_gl_busy) अणु
			table_हाल = 0;
			tdma_हाल = 0;
		पूर्ण अन्यथा अगर (!efuse->share_ant) अणु
			table_हाल = 100;
			tdma_हाल = 100;
		पूर्ण
	पूर्ण

	अगर (table_हाल != 0xff && tdma_हाल != 0xff) अणु
		rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G_FREERUN);
		जाओ निकास;
	पूर्ण

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (!coex_stat->wl_gl_busy) अणु
			table_हाल = 10;
			tdma_हाल = 3;
		पूर्ण अन्यथा अगर (coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) अणु
			table_हाल = 11;

			अगर (coex_stat->lo_pri_rx + coex_stat->lo_pri_tx > 250)
				tdma_हाल = 17;
			अन्यथा
				tdma_हाल = 7;
		पूर्ण अन्यथा अणु
			table_हाल = 12;
			tdma_हाल = 7;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		अगर (!coex_stat->wl_gl_busy) अणु
			table_हाल = 112;
			tdma_हाल = 104;
		पूर्ण अन्यथा अगर ((coex_stat->bt_ble_scan_type & 0x2) &&
			   coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE) अणु
			table_हाल = 114;
			tdma_हाल = 103;
		पूर्ण अन्यथा अणु
			table_हाल = 112;
			tdma_हाल = 103;
		पूर्ण
	पूर्ण

निकास:
	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_inquiry(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	bool wl_hi_pri = false;
	u8 table_हाल, tdma_हाल;
	u32 slot_type = 0;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (coex_stat->wl_linkscan_proc || coex_stat->wl_hi_pri_task1 ||
	    coex_stat->wl_hi_pri_task2)
		wl_hi_pri = true;

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (wl_hi_pri) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi hi-pri task\n");
			table_हाल = 15;

			अगर (coex_stat->bt_profile_num > 0)
				tdma_हाल = 10;
			अन्यथा अगर (coex_stat->wl_hi_pri_task1)
				tdma_हाल = 6;
			अन्यथा अगर (!coex_stat->bt_page)
				tdma_हाल = 8;
			अन्यथा
				tdma_हाल = 9;
		पूर्ण अन्यथा अगर (coex_stat->wl_gl_busy) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi busy\n");
			अगर (coex_stat->bt_profile_num == 0) अणु
				table_हाल = 12;
				tdma_हाल = 18;
			पूर्ण अन्यथा अगर (coex_stat->bt_profile_num == 1 &&
				   !coex_stat->bt_a2dp_exist) अणु
				slot_type = TDMA_4SLOT;
				table_हाल = 12;
				tdma_हाल = 20;
			पूर्ण अन्यथा अणु
				slot_type = TDMA_4SLOT;
				table_हाल = 12;
				tdma_हाल = 26;
			पूर्ण
		पूर्ण अन्यथा अगर (coex_stat->wl_connected) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi connected\n");
			table_हाल = 9;
			tdma_हाल = 27;
		पूर्ण अन्यथा अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi not-connected\n");
			table_हाल = 1;
			tdma_हाल = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non_Shared-Ant */
		अगर (wl_hi_pri) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi hi-pri task\n");
			table_हाल = 114;

			अगर (coex_stat->bt_profile_num > 0)
				tdma_हाल = 110;
			अन्यथा अगर (coex_stat->wl_hi_pri_task1)
				tdma_हाल = 106;
			अन्यथा अगर (!coex_stat->bt_page)
				tdma_हाल = 108;
			अन्यथा
				tdma_हाल = 109;
		पूर्ण  अन्यथा अगर (coex_stat->wl_gl_busy) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page + wifi busy\n");
			table_हाल = 114;
			tdma_हाल = 121;
		पूर्ण अन्यथा अगर (coex_stat->wl_connected) अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi connected\n");
			table_हाल = 101;
			tdma_हाल = 100;
		पूर्ण अन्यथा अणु
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], bt inq/page +  wifi not-connected\n");
			table_हाल = 101;
			tdma_हाल = 100;
		पूर्ण
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], wifi hi(%d), bt page(%d)\n",
		wl_hi_pri, coex_stat->bt_page);

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_bt_hfp(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (coex_stat->bt_multi_link) अणु
			table_हाल = 10;
			tdma_हाल = 17;
		पूर्ण अन्यथा अणु
			table_हाल = 10;
			tdma_हाल = 5;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		अगर (coex_stat->bt_multi_link) अणु
			table_हाल = 112;
			tdma_हाल = 117;
		पूर्ण अन्यथा अणु
			table_हाल = 105;
			tdma_हाल = 100;
		पूर्ण
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_hid(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	u32 slot_type = 0;
	bool bt_multi_link_reमुख्य = false, is_toggle_table = false;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (coex_stat->bt_ble_exist) अणु
			/* RCU */
			अगर (coex_stat->cnt_wl[COEX_CNT_WL_SCANAP] > 5) अणु
				table_हाल = 26;
				tdma_हाल = 2;
			पूर्ण अन्यथा अणु
				table_हाल = 27;
				tdma_हाल = 9;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Legacy HID  */
			अगर (coex_stat->bt_profile_num == 1 &&
			    (coex_stat->bt_multi_link ||
			    (coex_stat->lo_pri_rx +
			     coex_stat->lo_pri_tx > 360) ||
			     coex_stat->bt_slave ||
			     bt_multi_link_reमुख्य)) अणु
				slot_type = TDMA_4SLOT;
				table_हाल = 12;
				tdma_हाल = 20;
			पूर्ण अन्यथा अगर (coex_stat->bt_a2dp_active) अणु
				table_हाल = 9;
				tdma_हाल = 18;
			पूर्ण अन्यथा अगर (coex_stat->bt_418_hid_exist &&
				   coex_stat->wl_gl_busy) अणु
				is_toggle_table = true;
				slot_type = TDMA_4SLOT;
				table_हाल = 9;
				tdma_हाल = 24;
			पूर्ण अन्यथा अगर (coex_stat->bt_ble_hid_exist &&
				   coex_stat->wl_gl_busy) अणु
				table_हाल = 32;
				tdma_हाल = 9;
			पूर्ण अन्यथा अणु
				table_हाल = 9;
				tdma_हाल = 9;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		अगर (coex_stat->bt_ble_exist) अणु
			/* BLE */
			अगर (coex_stat->cnt_wl[COEX_CNT_WL_SCANAP] > 5) अणु
				table_हाल = 121;
				tdma_हाल = 102;
			पूर्ण अन्यथा अणु
				table_हाल = 122;
				tdma_हाल = 109;
			पूर्ण
		पूर्ण अन्यथा अगर (coex_stat->bt_a2dp_active) अणु
			table_हाल = 113;
			tdma_हाल = 118;
		पूर्ण अन्यथा अणु
			table_हाल = 113;
			tdma_हाल = 104;
		पूर्ण
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	अगर (is_toggle_table) अणु
		rtw_btc_wltoggle_table_a(rtwdev, true, table_हाल);
		rtw_btc_wltoggle_table_b(rtwdev, false, 1, COEX_WL_SLOT_TOGLLE);
	पूर्ण

	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_bt_a2dp(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	u32 slot_type = 0;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	slot_type = TDMA_4SLOT;

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (coex_stat->wl_gl_busy && coex_stat->wl_noisy_level == 0)
			table_हाल = 12;
		अन्यथा
			table_हाल = 9;

		अगर (coex_stat->wl_connecting || !coex_stat->wl_gl_busy)
			tdma_हाल = 14;
		अन्यथा
			tdma_हाल = 13;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 112;

		अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]))
			tdma_हाल = 112;
		अन्यथा
			tdma_हाल = 113;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_bt_a2dpsink(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	bool ap_enable = false;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु /* Shared-Ant */
		अगर (ap_enable) अणु
			table_हाल = 2;
			tdma_हाल = 0;
		पूर्ण अन्यथा अगर (coex_stat->wl_gl_busy) अणु
			table_हाल = 28;
			tdma_हाल = 20;
		पूर्ण अन्यथा अणु
			table_हाल = 28;
			tdma_हाल = 26;
		पूर्ण
	पूर्ण अन्यथा अणु /* Non-Shared-Ant */
		अगर (ap_enable) अणु
			table_हाल = 100;
			tdma_हाल = 100;
		पूर्ण अन्यथा अणु
			table_हाल = 119;
			tdma_हाल = 120;
		पूर्ण
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_pan(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (coex_stat->wl_gl_busy && coex_stat->wl_noisy_level == 0)
			table_हाल = 14;
		अन्यथा
			table_हाल = 10;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 17;
		अन्यथा
			tdma_हाल = 20;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 112;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 117;
		अन्यथा
			tdma_हाल = 119;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_a2dp_hid(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल, पूर्णांकerval = 0;
	u32 slot_type = 0;
	bool is_toggle_table = false;

	slot_type = TDMA_4SLOT;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (coex_stat->bt_ble_exist) अणु
			table_हाल = 26; /* क्रम RCU */
		पूर्ण अन्यथा अगर (coex_stat->bt_418_hid_exist) अणु
			table_हाल = 9;
			पूर्णांकerval = 1;
		पूर्ण अन्यथा अणु
			table_हाल = 9;
		पूर्ण

		अगर (coex_stat->wl_connecting || !coex_stat->wl_gl_busy) अणु
			tdma_हाल = 14;
		पूर्ण अन्यथा अगर (coex_stat->bt_418_hid_exist) अणु
			is_toggle_table = true;
			tdma_हाल = 23;
		पूर्ण अन्यथा अणु
			tdma_हाल = 13;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		अगर (coex_stat->bt_ble_exist)
			table_हाल = 121;
		अन्यथा
			table_हाल = 113;

		अगर (COEX_RSSI_HIGH(coex_dm->wl_rssi_state[1]))
			tdma_हाल = 112;
		अन्यथा
			tdma_हाल = 113;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	अगर (is_toggle_table) अणु
		rtw_btc_wltoggle_table_a(rtwdev, true, table_हाल);
		rtw_btc_wltoggle_table_b(rtwdev, false, पूर्णांकerval, COEX_WL_SLOT_TOGLLE);
	पूर्ण
	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_bt_a2dp_pan(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	bool wl_cpt_test = false, bt_cpt_test = false;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);
	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		अगर (wl_cpt_test) अणु
			अगर (coex_stat->wl_gl_busy) अणु
				table_हाल = 20;
				tdma_हाल = 17;
			पूर्ण अन्यथा अणु
				table_हाल = 10;
				tdma_हाल = 15;
			पूर्ण
		पूर्ण अन्यथा अगर (bt_cpt_test) अणु
			table_हाल = 26;
			tdma_हाल = 26;
		पूर्ण अन्यथा अणु
			अगर (coex_stat->wl_gl_busy &&
			    coex_stat->wl_noisy_level == 0)
				table_हाल = 14;
			अन्यथा
				table_हाल = 10;

			अगर (coex_stat->wl_gl_busy)
				tdma_हाल = 15;
			अन्यथा
				tdma_हाल = 20;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 112;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 115;
		अन्यथा
			tdma_हाल = 120;
	पूर्ण

	अगर (wl_cpt_test)
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[1]);
	अन्यथा
		rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_pan_hid(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 9;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 18;
		अन्यथा
			tdma_हाल = 19;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 113;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 117;
		अन्यथा
			tdma_हाल = 119;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_bt_a2dp_pan_hid(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 10;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 15;
		अन्यथा
			tdma_हाल = 20;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 113;

		अगर (coex_stat->wl_gl_busy)
			tdma_हाल = 115;
		अन्यथा
			tdma_हाल = 120;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_wl_under5g(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_FIX2M, false);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 0;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_wl_only(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 2;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_wl_native_lps(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	अगर (coex->under_5g)
		वापस;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 28;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_wl_linkscan(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;
	u32 slot_type = 0;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु /* Shared-Ant */
		अगर (coex_stat->bt_a2dp_exist) अणु
			slot_type = TDMA_4SLOT;
			tdma_हाल = 11;
			अगर (coex_stat->wl_gl_busy)
				table_हाल = 26;
			अन्यथा
				table_हाल = 9;
		पूर्ण अन्यथा अणु
			table_हाल = 9;
			tdma_हाल = 7;
		पूर्ण
	पूर्ण अन्यथा अणु /* Non-Shared-Ant */
		अगर (coex_stat->bt_a2dp_exist) अणु
			slot_type = TDMA_4SLOT;
			table_हाल = 112;
			tdma_हाल = 111;
		पूर्ण अन्यथा अणु
			table_हाल = 112;
			tdma_हाल = 107;
		पूर्ण
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल | slot_type);
पूर्ण

अटल व्योम rtw_coex_action_wl_not_connected(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 table_हाल, tdma_हाल;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	rtw_coex_set_ant_path(rtwdev, false, COEX_SET_ANT_2G);
	rtw_coex_set_rf_para(rtwdev, chip->wl_rf_para_rx[0]);

	अगर (efuse->share_ant) अणु
		/* Shared-Ant */
		table_हाल = 1;
		tdma_हाल = 0;
	पूर्ण अन्यथा अणु
		/* Non-Shared-Ant */
		table_हाल = 100;
		tdma_हाल = 100;
	पूर्ण

	rtw_coex_table(rtwdev, false, table_हाल);
	rtw_coex_tdma(rtwdev, false, tdma_हाल);
पूर्ण

अटल व्योम rtw_coex_action_wl_connected(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 algorithm;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	algorithm = rtw_coex_algorithm(rtwdev);

	चयन (algorithm) अणु
	हाल COEX_ALGO_HFP:
		rtw_coex_action_bt_hfp(rtwdev);
		अवरोध;
	हाल COEX_ALGO_HID:
		अगर (rtw_coex_मुक्तrun_check(rtwdev))
			rtw_coex_action_मुक्तrun(rtwdev);
		अन्यथा
			rtw_coex_action_bt_hid(rtwdev);
		अवरोध;
	हाल COEX_ALGO_A2DP:
		अगर (rtw_coex_मुक्तrun_check(rtwdev))
			rtw_coex_action_मुक्तrun(rtwdev);
		अन्यथा अगर (coex_stat->bt_a2dp_sink)
			rtw_coex_action_bt_a2dpsink(rtwdev);
		अन्यथा
			rtw_coex_action_bt_a2dp(rtwdev);
		अवरोध;
	हाल COEX_ALGO_PAN:
		rtw_coex_action_bt_pan(rtwdev);
		अवरोध;
	हाल COEX_ALGO_A2DP_HID:
		अगर (rtw_coex_मुक्तrun_check(rtwdev))
			rtw_coex_action_मुक्तrun(rtwdev);
		अन्यथा
			rtw_coex_action_bt_a2dp_hid(rtwdev);
		अवरोध;
	हाल COEX_ALGO_A2DP_PAN:
		rtw_coex_action_bt_a2dp_pan(rtwdev);
		अवरोध;
	हाल COEX_ALGO_PAN_HID:
		rtw_coex_action_bt_pan_hid(rtwdev);
		अवरोध;
	हाल COEX_ALGO_A2DP_PAN_HID:
		rtw_coex_action_bt_a2dp_pan_hid(rtwdev);
		अवरोध;
	शेष:
	हाल COEX_ALGO_NOPROखाता:
		rtw_coex_action_bt_idle(rtwdev);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw_coex_run_coex(काष्ठा rtw_dev *rtwdev, u8 reason)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	bool rf4ce_en = false;

	lockdep_निश्चित_held(&rtwdev->mutex);

	अगर (!test_bit(RTW_FLAG_RUNNING, rtwdev->flags))
		वापस;

	coex_dm->reason = reason;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): reason = %d\n", __func__,
		reason);

	/* update wअगरi_link_info_ext variable */
	rtw_coex_update_wl_link_info(rtwdev, reason);

	rtw_coex_monitor_bt_enable(rtwdev);

	अगर (coex->manual_control) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], return for Manual CTRL!!\n");
		वापस;
	पूर्ण

	अगर (coex->stop_dm) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], return for Stop Coex DM!!\n");
		वापस;
	पूर्ण

	अगर (coex_stat->wl_under_ips) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], return for wifi is under IPS!!\n");
		वापस;
	पूर्ण

	अगर (coex->मुक्तze && coex_dm->reason == COEX_RSN_BTINFO &&
	    !coex_stat->bt_setup_link) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], return for coex_freeze!!\n");
		वापस;
	पूर्ण

	coex_stat->cnt_wl[COEX_CNT_WL_COEXRUN]++;
	coex->मुक्तrun = false;

	/* Pure-5G Coex Process */
	अगर (coex->under_5g) अणु
		coex_stat->wl_coex_mode = COEX_WLINK_5G;
		rtw_coex_action_wl_under5g(rtwdev);
		जाओ निकास;
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], WiFi is single-port 2G!!\n");
	coex_stat->wl_coex_mode = COEX_WLINK_2G1PORT;

	अगर (coex_stat->bt_disabled) अणु
		अगर (coex_stat->wl_connected && rf4ce_en)
			rtw_coex_action_rf4ce(rtwdev);
		अन्यथा अगर (!coex_stat->wl_connected)
			rtw_coex_action_wl_not_connected(rtwdev);
		अन्यथा
			rtw_coex_action_wl_only(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->wl_under_lps && !coex_stat->wl_क्रमce_lps_ctrl) अणु
		rtw_coex_action_wl_native_lps(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->bt_whck_test) अणु
		rtw_coex_action_bt_whql_test(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->bt_setup_link) अणु
		rtw_coex_action_bt_relink(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->bt_inq_page) अणु
		rtw_coex_action_bt_inquiry(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर ((coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE ||
	     coex_dm->bt_status == COEX_BTSTATUS_CON_IDLE) &&
	     coex_stat->wl_connected) अणु
		rtw_coex_action_bt_idle(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->wl_linkscan_proc && !coex->मुक्तrun) अणु
		rtw_coex_action_wl_linkscan(rtwdev);
		जाओ निकास;
	पूर्ण

	अगर (coex_stat->wl_connected) अणु
		rtw_coex_action_wl_connected(rtwdev);
		जाओ निकास;
	पूर्ण अन्यथा अणु
		rtw_coex_action_wl_not_connected(rtwdev);
		जाओ निकास;
	पूर्ण

निकास:
	rtw_coex_gnt_workaround(rtwdev, false, coex_stat->wl_coex_mode);
	rtw_coex_limited_wl(rtwdev);
पूर्ण

अटल व्योम rtw_coex_init_coex_var(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	u8 i;

	स_रखो(coex_dm, 0, माप(*coex_dm));
	स_रखो(coex_stat, 0, माप(*coex_stat));

	क्रम (i = 0; i < COEX_CNT_WL_MAX; i++)
		coex_stat->cnt_wl[i] = 0;

	क्रम (i = 0; i < COEX_CNT_BT_MAX; i++)
		coex_stat->cnt_bt[i] = 0;

	क्रम (i = 0; i < ARRAY_SIZE(coex_dm->bt_rssi_state); i++)
		coex_dm->bt_rssi_state[i] = COEX_RSSI_STATE_LOW;

	क्रम (i = 0; i < ARRAY_SIZE(coex_dm->wl_rssi_state); i++)
		coex_dm->wl_rssi_state[i] = COEX_RSSI_STATE_LOW;

	coex_stat->wl_coex_mode = COEX_WLINK_MAX;
	coex_stat->wl_rx_rate = DESC_RATE5_5M;
	coex_stat->wl_rts_rx_rate = DESC_RATE5_5M;
पूर्ण

अटल व्योम __rtw_coex_init_hw_config(काष्ठा rtw_dev *rtwdev, bool wअगरi_only)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	rtw_coex_init_coex_var(rtwdev);

	coex_stat->kt_ver = u8_get_bits(rtw_पढ़ो8(rtwdev, 0xf1), GENMASK(7, 4));

	rtw_coex_monitor_bt_enable(rtwdev);
	rtw_coex_wl_slot_extend(rtwdev, coex_stat->wl_slot_extend);

	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	rtw_coex_set_rfe_type(rtwdev);
	rtw_coex_set_init(rtwdev);

	/* set Tx response = Hi-Pri (ex: Transmitting ACK,BA,CTS) */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_RSP, 1);

	/* set Tx beacon = Hi-Pri */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_BEACON, 1);

	/* set Tx beacon queue = Hi-Pri */
	rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_TX_BEACONQ, 1);

	/* antenna config */
	अगर (coex->wl_rf_off) अणु
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WOFF);
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ALL, false);
		coex->stop_dm = true;

		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): RF Off\n",
			__func__);
	पूर्ण अन्यथा अगर (wअगरi_only) अणु
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WONLY);
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF,
				    true);
		coex->stop_dm = true;
	पूर्ण अन्यथा अणु
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_INIT);
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF,
				    true);
		coex->stop_dm = false;
		coex->मुक्तze = true;
	पूर्ण

	/* PTA parameter */
	rtw_coex_table(rtwdev, true, 1);
	rtw_coex_tdma(rtwdev, true, 0);
	rtw_coex_query_bt_info(rtwdev);
पूर्ण

व्योम rtw_coex_घातer_on_setting(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	u8 table_हाल = 1;

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);

	coex->stop_dm = true;
	coex->wl_rf_off = false;

	/* enable BB, we can ग_लिखो 0x948 */
	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN,
		       BIT_FEN_BB_GLB_RST | BIT_FEN_BB_RSTB);

	rtw_coex_monitor_bt_enable(rtwdev);
	rtw_coex_set_rfe_type(rtwdev);

	/* set antenna path to BT */
	rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_POWERON);

	rtw_coex_table(rtwdev, true, table_हाल);
	/* red x issue */
	rtw_ग_लिखो8(rtwdev, 0xff1a, 0x0);
	rtw_coex_set_gnt_debug(rtwdev);
पूर्ण

व्योम rtw_coex_घातer_off_setting(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो16(rtwdev, REG_WIFI_BT_INFO, BIT_BT_INT_EN);
पूर्ण

व्योम rtw_coex_init_hw_config(काष्ठा rtw_dev *rtwdev, bool wअगरi_only)
अणु
	__rtw_coex_init_hw_config(rtwdev, wअगरi_only);
पूर्ण

व्योम rtw_coex_ips_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	अगर (type == COEX_IPS_ENTER) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], IPS ENTER notify\n");

		coex_stat->wl_under_ips = true;

		/* क्रम lps off */
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ALL, false);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_WOFF);
		rtw_coex_action_coex_all_off(rtwdev);
	पूर्ण अन्यथा अगर (type == COEX_IPS_LEAVE) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], IPS LEAVE notify\n");

		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, true);
		/* run init hw config (exclude wअगरi only) */
		__rtw_coex_init_hw_config(rtwdev, false);

		coex_stat->wl_under_ips = false;
	पूर्ण
पूर्ण

व्योम rtw_coex_lps_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	अगर (type == COEX_LPS_ENABLE) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], LPS ENABLE notify\n");

		coex_stat->wl_under_lps = true;

		अगर (coex_stat->wl_क्रमce_lps_ctrl) अणु
			/* क्रम ps-tdma */
			rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE, true);
		पूर्ण अन्यथा अणु
			/* क्रम native ps */
			rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE, false);
			rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_WLBUSY, false);

			rtw_coex_run_coex(rtwdev, COEX_RSN_LPS);
		पूर्ण
	पूर्ण अन्यथा अगर (type == COEX_LPS_DISABLE) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], LPS DISABLE notify\n");

		coex_stat->wl_under_lps = false;

		/* क्रम lps off */
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		अगर (!coex_stat->wl_क्रमce_lps_ctrl)
			rtw_coex_query_bt_info(rtwdev);

		rtw_coex_run_coex(rtwdev, COEX_RSN_LPS);
	पूर्ण
पूर्ण

व्योम rtw_coex_scan_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	coex->मुक्तze = false;
	rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, true);

	अगर (type == COEX_SCAN_START_5G) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], SCAN START notify (5G)\n");

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GSCANSTART);
	पूर्ण अन्यथा अगर ((type == COEX_SCAN_START_2G) || (type == COEX_SCAN_START)) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], SCAN START notify (2G)\n");

		coex_stat->wl_hi_pri_task2 = true;

		/* Force antenna setup क्रम no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GSCANSTART);
	पूर्ण अन्यथा अणु
		coex_stat->cnt_wl[COEX_CNT_WL_SCANAP] = 30; /* To करो */

		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], SCAN FINISH notify (Scan-AP = %d)\n",
			coex_stat->cnt_wl[COEX_CNT_WL_SCANAP]);

		coex_stat->wl_hi_pri_task2 = false;
		rtw_coex_run_coex(rtwdev, COEX_RSN_SCANFINISH);
	पूर्ण
पूर्ण

व्योम rtw_coex_चयनband_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	अगर (type == COEX_SWITCH_TO_5G) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): TO_5G\n",
			__func__);
	पूर्ण अन्यथा अगर (type == COEX_SWITCH_TO_24G_NOFORSCAN) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], %s(): TO_24G_NOFORSCAN\n", __func__);
	पूर्ण अन्यथा अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): TO_2G\n",
			__func__);
	पूर्ण

	अगर (type == COEX_SWITCH_TO_5G)
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GSWITCHBAND);
	अन्यथा अगर (type == COEX_SWITCH_TO_24G_NOFORSCAN)
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GSWITCHBAND);
	अन्यथा
		rtw_coex_scan_notअगरy(rtwdev, COEX_SCAN_START_2G);
पूर्ण

व्योम rtw_coex_connect_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE | COEX_SCBD_ONOFF, true);

	अगर (type == COEX_ASSOCIATE_5G_START) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 5G start\n",
			__func__);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GCONSTART);
	पूर्ण अन्यथा अगर (type == COEX_ASSOCIATE_5G_FINISH) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 5G finish\n",
			__func__);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GCONFINISH);
	पूर्ण अन्यथा अगर (type == COEX_ASSOCIATE_START) अणु
		coex_stat->wl_hi_pri_task1 = true;
		coex_stat->wl_connecting = true;
		coex_stat->cnt_wl[COEX_CNT_WL_CONNPKT] = 2;
		coex_stat->wl_connecting = true;
		ieee80211_queue_delayed_work(rtwdev->hw,
					     &coex->wl_connecting_work, 2 * HZ);

		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 2G start\n",
			__func__);
		/* Force antenna setup क्रम no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);

		rtw_coex_run_coex(rtwdev, COEX_RSN_2GCONSTART);

		/* To keep TDMA हाल during connect process,
		 * to aव्योम changed by Btinfo and runcoexmechanism
		 */
		coex->मुक्तze = true;
		ieee80211_queue_delayed_work(rtwdev->hw, &coex->deमुक्तze_work,
					     5 * HZ);
	पूर्ण अन्यथा अणु
		coex_stat->wl_hi_pri_task1 = false;
		coex->मुक्तze = false;
		coex_stat->wl_connecting = false;

		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 2G finish\n",
			__func__);
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GCONFINISH);
	पूर्ण
पूर्ण

व्योम rtw_coex_media_status_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	अगर (coex->manual_control || coex->stop_dm)
		वापस;

	अगर (type == COEX_MEDIA_CONNECT_5G) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 5G\n", __func__);

		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_5G);
		rtw_coex_run_coex(rtwdev, COEX_RSN_5GMEDIA);
	पूर्ण अन्यथा अगर (type == COEX_MEDIA_CONNECT) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): 2G\n", __func__);

		coex_stat->wl_connecting = false;

		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_ACTIVE, true);

		/* Force antenna setup क्रम no scan result issue */
		rtw_coex_set_ant_path(rtwdev, true, COEX_SET_ANT_2G);

		/* Set CCK Rx high Pri */
		rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_RX_CCK, 1);
		rtw_coex_run_coex(rtwdev, COEX_RSN_2GMEDIA);
	पूर्ण अन्यथा अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s(): disconnect!!\n",
			__func__);
		rtw_coex_set_wl_pri_mask(rtwdev, COEX_WLPRI_RX_CCK, 0);
		rtw_coex_run_coex(rtwdev, COEX_RSN_MEDIADISCON);
	पूर्ण

	rtw_coex_update_wl_ch_info(rtwdev, type);
पूर्ण

व्योम rtw_coex_bt_info_notअगरy(काष्ठा rtw_dev *rtwdev, u8 *buf, u8 length)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	u32 bt_relink_समय;
	u8 i, rsp_source = 0, type;
	bool inq_page = false;

	rsp_source = buf[0] & 0xf;
	अगर (rsp_source >= COEX_BTINFO_SRC_MAX)
		वापस;
	coex_stat->cnt_bt_info_c2h[rsp_source]++;

	अगर (rsp_source == COEX_BTINFO_SRC_BT_IQK) अणु
		coex_stat->bt_iqk_state = buf[1];
		अगर (coex_stat->bt_iqk_state == 0)
			coex_stat->cnt_bt[COEX_CNT_BT_IQK]++;
		अन्यथा अगर (coex_stat->bt_iqk_state == 2)
			coex_stat->cnt_bt[COEX_CNT_BT_IQKFAIL]++;

		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], BT IQK by bt_info, data0 = 0x%02x\n",
			buf[1]);

		वापस;
	पूर्ण

	अगर (rsp_source == COEX_BTINFO_SRC_BT_SCBD) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], BT Scoreboard change notify by WL FW c2h, 0xaa = 0x%02x, 0xab = 0x%02x\n",
			buf[1], buf[2]);

		rtw_coex_monitor_bt_enable(rtwdev);
		अगर (coex_stat->bt_disabled != coex_stat->bt_disabled_pre) अणु
			coex_stat->bt_disabled_pre = coex_stat->bt_disabled;
			rtw_coex_run_coex(rtwdev, COEX_RSN_BTINFO);
		पूर्ण
		वापस;
	पूर्ण

	अगर (rsp_source == COEX_BTINFO_SRC_H2C60) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], H2C 0x60 content replied by WL FW: H2C_0x60 = [%02x %02x %02x %02x %02x]\n",
			buf[1], buf[2], buf[3], buf[4], buf[5]);

		क्रम (i = 1; i <= COEX_WL_TDMA_PARA_LENGTH; i++)
			coex_dm->fw_tdma_para[i - 1] = buf[i];
		वापस;
	पूर्ण

	अगर (rsp_source == COEX_BTINFO_SRC_WL_FW) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], bt_info reply by WL FW\n");

		rtw_coex_update_bt_link_info(rtwdev);
		वापस;
	पूर्ण

	अगर (rsp_source == COEX_BTINFO_SRC_BT_RSP ||
	    rsp_source == COEX_BTINFO_SRC_BT_ACT) अणु
		अगर (coex_stat->bt_disabled) अणु
			coex_stat->bt_disabled = false;
			coex_stat->bt_reenable = true;
			ieee80211_queue_delayed_work(rtwdev->hw,
						     &coex->bt_reenable_work,
						     15 * HZ);
			rtw_dbg(rtwdev, RTW_DBG_COEX,
				"[BTCoex], BT enable detected by bt_info\n");
		पूर्ण
	पूर्ण

	अगर (length != COEX_BTINFO_LENGTH) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], Bt_info length = %d invalid!!\n", length);

		वापस;
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], Bt_info[%d], len=%d, data=[%02x %02x %02x %02x %02x %02x]\n",
		buf[0], length, buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);

	क्रम (i = 0; i < COEX_BTINFO_LENGTH; i++)
		coex_stat->bt_info_c2h[rsp_source][i] = buf[i];

	/* get the same info from bt, skip it */
	अगर (coex_stat->bt_info_c2h[rsp_source][1] == coex_stat->bt_info_lb2 &&
	    coex_stat->bt_info_c2h[rsp_source][2] == coex_stat->bt_info_lb3 &&
	    coex_stat->bt_info_c2h[rsp_source][3] == coex_stat->bt_info_hb0 &&
	    coex_stat->bt_info_c2h[rsp_source][4] == coex_stat->bt_info_hb1 &&
	    coex_stat->bt_info_c2h[rsp_source][5] == coex_stat->bt_info_hb2 &&
	    coex_stat->bt_info_c2h[rsp_source][6] == coex_stat->bt_info_hb3) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], Return because Btinfo duplicate!!\n");
		वापस;
	पूर्ण

	coex_stat->bt_info_lb2 = coex_stat->bt_info_c2h[rsp_source][1];
	coex_stat->bt_info_lb3 = coex_stat->bt_info_c2h[rsp_source][2];
	coex_stat->bt_info_hb0 = coex_stat->bt_info_c2h[rsp_source][3];
	coex_stat->bt_info_hb1 = coex_stat->bt_info_c2h[rsp_source][4];
	coex_stat->bt_info_hb2 = coex_stat->bt_info_c2h[rsp_source][5];
	coex_stat->bt_info_hb3 = coex_stat->bt_info_c2h[rsp_source][6];

	/* 0xff means BT is under WHCK test */
	coex_stat->bt_whck_test = (coex_stat->bt_info_lb2 == 0xff);

	inq_page = ((coex_stat->bt_info_lb2 & BIT(2)) == BIT(2));

	अगर (inq_page != coex_stat->bt_inq_page) अणु
		cancel_delayed_work_sync(&coex->bt_reमुख्य_work);
		coex_stat->bt_inq_page = inq_page;

		अगर (inq_page)
			coex_stat->bt_inq_reमुख्य = true;
		अन्यथा
			ieee80211_queue_delayed_work(rtwdev->hw,
						     &coex->bt_reमुख्य_work,
						     4 * HZ);
	पूर्ण
	coex_stat->bt_acl_busy = ((coex_stat->bt_info_lb2 & BIT(3)) == BIT(3));
	अगर (chip->ble_hid_profile_support) अणु
		अगर (coex_stat->bt_info_lb2 & BIT(5)) अणु
			अगर (coex_stat->bt_info_hb1 & BIT(0)) अणु
				/*BLE HID*/
				coex_stat->bt_ble_hid_exist = true;
			पूर्ण अन्यथा अणु
				coex_stat->bt_ble_hid_exist = false;
			पूर्ण
			coex_stat->bt_ble_exist = false;
		पूर्ण अन्यथा अगर (coex_stat->bt_info_hb1 & BIT(0)) अणु
			/*RCU*/
			coex_stat->bt_ble_hid_exist = false;
			coex_stat->bt_ble_exist = true;
		पूर्ण अन्यथा अणु
			coex_stat->bt_ble_hid_exist = false;
			coex_stat->bt_ble_exist = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (coex_stat->bt_info_hb1 & BIT(0)) अणु
			अगर (coex_stat->bt_hid_slot == 1 &&
			    coex_stat->hi_pri_rx + 100 < coex_stat->hi_pri_tx &&
			    coex_stat->hi_pri_rx < 100) अणु
				coex_stat->bt_ble_hid_exist = true;
				coex_stat->bt_ble_exist = false;
			पूर्ण अन्यथा अणु
				coex_stat->bt_ble_hid_exist = false;
				coex_stat->bt_ble_exist = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			coex_stat->bt_ble_hid_exist = false;
			coex_stat->bt_ble_exist = false;
		पूर्ण
	पूर्ण

	coex_stat->cnt_bt[COEX_CNT_BT_RETRY] = coex_stat->bt_info_lb3 & 0xf;
	अगर (coex_stat->cnt_bt[COEX_CNT_BT_RETRY] >= 1)
		coex_stat->cnt_bt[COEX_CNT_BT_POPEVENT]++;

	coex_stat->bt_fix_2M = ((coex_stat->bt_info_lb3 & BIT(4)) == BIT(4));
	coex_stat->bt_inq = ((coex_stat->bt_info_lb3 & BIT(5)) == BIT(5));
	अगर (coex_stat->bt_inq)
		coex_stat->cnt_bt[COEX_CNT_BT_INQ]++;

	coex_stat->bt_page = ((coex_stat->bt_info_lb3 & BIT(7)) == BIT(7));
	अगर (coex_stat->bt_page)
		coex_stat->cnt_bt[COEX_CNT_BT_PAGE]++;

	/* unit: % (value-100 to translate to unit: dBm in coex info) */
	अगर (chip->bt_rssi_type == COEX_BTRSSI_RATIO) अणु
		coex_stat->bt_rssi = coex_stat->bt_info_hb0 * 2 + 10;
	पूर्ण अन्यथा अणु
		अगर (coex_stat->bt_info_hb0 <= 127)
			coex_stat->bt_rssi = 100;
		अन्यथा अगर (256 - coex_stat->bt_info_hb0 <= 100)
			coex_stat->bt_rssi = 100 - (256 - coex_stat->bt_info_hb0);
		अन्यथा
			coex_stat->bt_rssi = 0;
	पूर्ण

	अगर (coex_stat->bt_info_hb1 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_REINIT]++;

	अगर (coex_stat->bt_info_hb1 & BIT(2)) अणु
		coex_stat->cnt_bt[COEX_CNT_BT_SETUPLINK]++;
		coex_stat->bt_setup_link = true;
		अगर (coex_stat->bt_reenable)
			bt_relink_समय = 6 * HZ;
		अन्यथा
			bt_relink_समय = 1 * HZ;

		ieee80211_queue_delayed_work(rtwdev->hw,
					     &coex->bt_relink_work,
					     bt_relink_समय);

		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], Re-Link start in BT info!!\n");
	पूर्ण

	अगर (coex_stat->bt_info_hb1 & BIT(3))
		coex_stat->cnt_bt[COEX_CNT_BT_IGNWLANACT]++;

	coex_stat->bt_ble_voice = ((coex_stat->bt_info_hb1 & BIT(4)) == BIT(4));
	coex_stat->bt_ble_scan_en = ((coex_stat->bt_info_hb1 & BIT(5)) == BIT(5));
	अगर (coex_stat->bt_info_hb1 & BIT(6))
		coex_stat->cnt_bt[COEX_CNT_BT_ROLESWITCH]++;

	coex_stat->bt_multi_link = ((coex_stat->bt_info_hb1 & BIT(7)) == BIT(7));
	/* क्रम multi_link = 0 but bt pkt reमुख्य exist */
	/* Use PS-TDMA to protect WL RX */
	अगर (!coex_stat->bt_multi_link && coex_stat->bt_multi_link_pre) अणु
		coex_stat->bt_multi_link_reमुख्य = true;
		ieee80211_queue_delayed_work(rtwdev->hw,
					     &coex->bt_multi_link_reमुख्य_work,
					     3 * HZ);
	पूर्ण
	coex_stat->bt_multi_link_pre = coex_stat->bt_multi_link;

	/* resend wअगरi info to bt, it is reset and lost the info */
	अगर (coex_stat->bt_info_hb1 & BIT(1)) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], BT Re-init, send wifi BW & Chnl to BT!!\n");

		अगर (coex_stat->wl_connected)
			type = COEX_MEDIA_CONNECT;
		अन्यथा
			type = COEX_MEDIA_DISCONNECT;
		rtw_coex_update_wl_ch_info(rtwdev, type);
	पूर्ण

	/* अगर ignore_wlan_act && not set_up_link */
	अगर ((coex_stat->bt_info_hb1 & BIT(3)) &&
	    (!(coex_stat->bt_info_hb1 & BIT(2)))) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX,
			"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
		rtw_coex_ignore_wlan_act(rtwdev, false);
	पूर्ण

	coex_stat->bt_opp_exist = ((coex_stat->bt_info_hb2 & BIT(0)) == BIT(0));
	अगर (coex_stat->bt_info_hb2 & BIT(1))
		coex_stat->cnt_bt[COEX_CNT_BT_AFHUPDATE]++;

	coex_stat->bt_a2dp_active = (coex_stat->bt_info_hb2 & BIT(2)) == BIT(2);
	coex_stat->bt_slave = ((coex_stat->bt_info_hb2 & BIT(3)) == BIT(3));
	coex_stat->bt_hid_slot = (coex_stat->bt_info_hb2 & 0x30) >> 4;
	coex_stat->bt_hid_pair_num = (coex_stat->bt_info_hb2 & 0xc0) >> 6;
	अगर (coex_stat->bt_hid_pair_num > 0 && coex_stat->bt_hid_slot >= 2)
		coex_stat->bt_418_hid_exist = true;
	अन्यथा अगर (coex_stat->bt_hid_pair_num == 0 || coex_stat->bt_hid_slot == 1)
		coex_stat->bt_418_hid_exist = false;

	अगर ((coex_stat->bt_info_lb2 & 0x49) == 0x49)
		coex_stat->bt_a2dp_bitpool = (coex_stat->bt_info_hb3 & 0x7f);
	अन्यथा
		coex_stat->bt_a2dp_bitpool = 0;

	coex_stat->bt_a2dp_sink = ((coex_stat->bt_info_hb3 & BIT(7)) == BIT(7));

	rtw_coex_update_bt_link_info(rtwdev);
	rtw_coex_run_coex(rtwdev, COEX_RSN_BTINFO);
पूर्ण

व्योम rtw_coex_wl_fwdbginfo_notअगरy(काष्ठा rtw_dev *rtwdev, u8 *buf, u8 length)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u8 val;
	पूर्णांक i;

	rtw_dbg(rtwdev, RTW_DBG_COEX,
		"[BTCoex], WiFi Fw Dbg info = %8ph (len = %d)\n",
		buf, length);
	अगर (WARN(length < 8, "invalid wl info c2h length\n"))
		वापस;

	अगर (buf[0] != 0x08)
		वापस;

	क्रम (i = 1; i < 8; i++) अणु
		val = coex_stat->wl_fw_dbg_info_pre[i];
		अगर (buf[i] >= val)
			coex_stat->wl_fw_dbg_info[i] = buf[i] - val;
		अन्यथा
			coex_stat->wl_fw_dbg_info[i] = 255 - val + buf[i];

		coex_stat->wl_fw_dbg_info_pre[i] = buf[i];
	पूर्ण

	coex_stat->cnt_wl[COEX_CNT_WL_FW_NOTIFY]++;
	rtw_coex_wl_ccklock_action(rtwdev);
	rtw_coex_wl_ccklock_detect(rtwdev);
पूर्ण

व्योम rtw_coex_wl_status_change_notअगरy(काष्ठा rtw_dev *rtwdev, u32 type)
अणु
	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
पूर्ण

व्योम rtw_coex_bt_relink_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.bt_relink_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->bt_setup_link = false;
	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_bt_reenable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.bt_reenable_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->bt_reenable = false;
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_deमुक्तze_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.deमुक्तze_work.work);
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex->मुक्तze = false;
	coex_stat->wl_hi_pri_task1 = false;
	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_wl_reमुख्य_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.wl_reमुख्य_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->wl_gl_busy = test_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);
	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_bt_reमुख्य_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.bt_reमुख्य_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->bt_inq_reमुख्य = coex_stat->bt_inq_page;
	rtw_coex_run_coex(rtwdev, COEX_RSN_BTSTATUS);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_wl_connecting_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.wl_connecting_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->wl_connecting = false;
	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], WL connecting stop!!\n");
	rtw_coex_run_coex(rtwdev, COEX_RSN_WLSTATUS);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_bt_multi_link_reमुख्य_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
		coex.bt_multi_link_reमुख्य_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->bt_multi_link_reमुख्य = false;
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_coex_wl_ccklock_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      coex.wl_ccklock_work.work);
	काष्ठा rtw_coex_stat *coex_stat = &rtwdev->coex.stat;

	mutex_lock(&rtwdev->mutex);
	coex_stat->wl_cck_lock = false;
	mutex_unlock(&rtwdev->mutex);
पूर्ण

#अगर_घोषित CONFIG_RTW88_DEBUGFS
#घोषणा INFO_SIZE	80

#घोषणा हाल_BTINFO(src) \
	हाल COEX_BTINFO_SRC_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_bt_info_src_string(u8 bt_info_src)
अणु
	चयन (bt_info_src) अणु
	हाल_BTINFO(WL_FW);
	हाल_BTINFO(BT_RSP);
	हाल_BTINFO(BT_ACT);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

#घोषणा हाल_RSN(src) \
	हाल COEX_RSN_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_reason_string(u8 reason)
अणु
	चयन (reason) अणु
	हाल_RSN(2GSCANSTART);
	हाल_RSN(5GSCANSTART);
	हाल_RSN(SCANFINISH);
	हाल_RSN(2GSWITCHBAND);
	हाल_RSN(5GSWITCHBAND);
	हाल_RSN(2GCONSTART);
	हाल_RSN(5GCONSTART);
	हाल_RSN(2GCONFINISH);
	हाल_RSN(5GCONFINISH);
	हाल_RSN(2GMEDIA);
	हाल_RSN(5GMEDIA);
	हाल_RSN(MEDIADISCON);
	हाल_RSN(BTINFO);
	हाल_RSN(LPS);
	हाल_RSN(WLSTATUS);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल u8 rtw_coex_get_table_index(काष्ठा rtw_dev *rtwdev, u32 wl_reg_6c0,
				   u32 wl_reg_6c4)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 ans = 0xFF;
	u8 n, i;
	u32 load_bt_val;
	u32 load_wl_val;
	bool share_ant = efuse->share_ant;

	अगर (share_ant)
		n = chip->table_sant_num;
	अन्यथा
		n = chip->table_nsant_num;

	क्रम (i = 0; i < n; i++) अणु
		अगर (share_ant) अणु
			load_bt_val = chip->table_sant[i].bt;
			load_wl_val = chip->table_sant[i].wl;
		पूर्ण अन्यथा अणु
			load_bt_val = chip->table_nsant[i].bt;
			load_wl_val = chip->table_nsant[i].wl;
		पूर्ण

		अगर (wl_reg_6c0 == load_bt_val &&
		    wl_reg_6c4 == load_wl_val) अणु
			ans = i;
			अगर (!share_ant)
				ans += 100;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ans;
पूर्ण

अटल u8 rtw_coex_get_tdma_index(काष्ठा rtw_dev *rtwdev, u8 *tdma_para)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 ans = 0xFF;
	u8 n, i, j;
	u8 load_cur_tab_val;
	bool valid = false;
	bool share_ant = efuse->share_ant;

	अगर (share_ant)
		n = chip->tdma_sant_num;
	अन्यथा
		n = chip->tdma_nsant_num;

	क्रम (i = 0; i < n; i++) अणु
		valid = false;
		क्रम (j = 0; j < 5; j++) अणु
			अगर (share_ant)
				load_cur_tab_val = chip->tdma_sant[i].para[j];
			अन्यथा
				load_cur_tab_val = chip->tdma_nsant[i].para[j];

			अगर (*(tdma_para + j) != load_cur_tab_val)
				अवरोध;

			अगर (j == 4)
				valid = true;
		पूर्ण
		अगर (valid) अणु
			ans = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ans;
पूर्ण

अटल पूर्णांक rtw_coex_addr_info(काष्ठा rtw_dev *rtwdev,
			      स्थिर काष्ठा rtw_reg_करोमुख्य *reg,
			      अक्षर addr_info[], पूर्णांक n)
अणु
	स्थिर अक्षर *rf_prefix = "";
	स्थिर अक्षर *sep = n == 0 ? "" : "/ ";
	पूर्णांक ffs, fls;
	पूर्णांक max_fls;

	अगर (INFO_SIZE - n <= 0)
		वापस 0;

	चयन (reg->करोमुख्य) अणु
	हाल RTW_REG_DOMAIN_MAC32:
		max_fls = 31;
		अवरोध;
	हाल RTW_REG_DOMAIN_MAC16:
		max_fls = 15;
		अवरोध;
	हाल RTW_REG_DOMAIN_MAC8:
		max_fls = 7;
		अवरोध;
	हाल RTW_REG_DOMAIN_RF_A:
	हाल RTW_REG_DOMAIN_RF_B:
		rf_prefix = "RF_";
		max_fls = 19;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ffs = __ffs(reg->mask);
	fls = __fls(reg->mask);

	अगर (ffs == 0 && fls == max_fls)
		वापस scnम_लिखो(addr_info + n, INFO_SIZE - n, "%s%s%x",
				 sep, rf_prefix, reg->addr);
	अन्यथा अगर (ffs == fls)
		वापस scnम_लिखो(addr_info + n, INFO_SIZE - n, "%s%s%x[%d]",
				 sep, rf_prefix, reg->addr, ffs);
	अन्यथा
		वापस scnम_लिखो(addr_info + n, INFO_SIZE - n, "%s%s%x[%d:%d]",
				 sep, rf_prefix, reg->addr, fls, ffs);
पूर्ण

अटल पूर्णांक rtw_coex_val_info(काष्ठा rtw_dev *rtwdev,
			     स्थिर काष्ठा rtw_reg_करोमुख्य *reg,
			     अक्षर val_info[], पूर्णांक n)
अणु
	स्थिर अक्षर *sep = n == 0 ? "" : "/ ";
	u8 rf_path;

	अगर (INFO_SIZE - n <= 0)
		वापस 0;

	चयन (reg->करोमुख्य) अणु
	हाल RTW_REG_DOMAIN_MAC32:
		वापस scnम_लिखो(val_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 rtw_पढ़ो32_mask(rtwdev, reg->addr, reg->mask));
	हाल RTW_REG_DOMAIN_MAC16:
		वापस scnम_लिखो(val_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 rtw_पढ़ो16_mask(rtwdev, reg->addr, reg->mask));
	हाल RTW_REG_DOMAIN_MAC8:
		वापस scnम_लिखो(val_info + n, INFO_SIZE - n, "%s0x%x", sep,
				 rtw_पढ़ो8_mask(rtwdev, reg->addr, reg->mask));
	हाल RTW_REG_DOMAIN_RF_A:
		rf_path = RF_PATH_A;
		अवरोध;
	हाल RTW_REG_DOMAIN_RF_B:
		rf_path = RF_PATH_B;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* only RF go through here */
	वापस scnम_लिखो(val_info + n, INFO_SIZE - n, "%s0x%x", sep,
			 rtw_पढ़ो_rf(rtwdev, rf_path, reg->addr, reg->mask));
पूर्ण

अटल व्योम rtw_coex_set_coexinfo_hw(काष्ठा rtw_dev *rtwdev, काष्ठा seq_file *m)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_reg_करोमुख्य *reg;
	अक्षर addr_info[INFO_SIZE];
	पूर्णांक n_addr = 0;
	अक्षर val_info[INFO_SIZE];
	पूर्णांक n_val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chip->coex_info_hw_regs_num; i++) अणु
		reg = &chip->coex_info_hw_regs[i];

		n_addr += rtw_coex_addr_info(rtwdev, reg, addr_info, n_addr);
		n_val += rtw_coex_val_info(rtwdev, reg, val_info, n_val);

		अगर (reg->करोमुख्य == RTW_REG_DOMAIN_NL) अणु
			seq_म_लिखो(m, "%-40s = %s\n", addr_info, val_info);
			n_addr = 0;
			n_val = 0;
		पूर्ण
	पूर्ण

	अगर (n_addr != 0 && n_val != 0)
		seq_म_लिखो(m, "%-40s = %s\n", addr_info, val_info);
पूर्ण

अटल bool rtw_coex_get_bt_reg(काष्ठा rtw_dev *rtwdev,
				u8 type, u16 addr, u16 *val)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	__le16 le_addr;
	u8 *payload;

	le_addr = cpu_to_le16(addr);
	req.op_code = BT_MP_INFO_OP_READ_REG;
	req.para1 = type;
	req.para2 = le16_get_bits(le_addr, GENMASK(7, 0));
	req.para3 = le16_get_bits(le_addr, GENMASK(15, 8));
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb) अणु
		*val = 0xeaea;
		वापस false;
	पूर्ण

	payload = get_payload_from_coex_resp(skb);
	*val = GET_COEX_RESP_BT_REG_VAL(payload);

	वापस true;
पूर्ण

अटल bool rtw_coex_get_bt_patch_version(काष्ठा rtw_dev *rtwdev,
					  u32 *patch_version)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	u8 *payload;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_PATCH_VER;
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb)
		जाओ out;

	payload = get_payload_from_coex_resp(skb);
	*patch_version = GET_COEX_RESP_BT_PATCH_VER(payload);
	ret = true;

out:
	वापस ret;
पूर्ण

अटल bool rtw_coex_get_bt_supported_version(काष्ठा rtw_dev *rtwdev,
					      u32 *supported_version)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	u8 *payload;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_SUPP_VER;
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb)
		जाओ out;

	payload = get_payload_from_coex_resp(skb);
	*supported_version = GET_COEX_RESP_BT_SUPP_VER(payload);
	ret = true;

out:
	वापस ret;
पूर्ण

अटल bool rtw_coex_get_bt_supported_feature(काष्ठा rtw_dev *rtwdev,
					      u32 *supported_feature)
अणु
	काष्ठा rtw_coex_info_req req = अणु0पूर्ण;
	काष्ठा sk_buff *skb;
	u8 *payload;
	bool ret = false;

	req.op_code = BT_MP_INFO_OP_SUPP_FEAT;
	skb = rtw_coex_info_request(rtwdev, &req);
	अगर (!skb)
		जाओ out;

	payload = get_payload_from_coex_resp(skb);
	*supported_feature = GET_COEX_RESP_BT_SUPP_FEAT(payload);
	ret = true;

out:
	वापस ret;
पूर्ण

काष्ठा rtw_coex_sta_stat_iter_data अणु
	काष्ठा rtw_vअगर *rtwvअगर;
	काष्ठा seq_file *file;
पूर्ण;

अटल व्योम rtw_coex_sta_stat_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_coex_sta_stat_iter_data *sta_iter_data = data;
	काष्ठा rtw_vअगर *rtwvअगर = sta_iter_data->rtwvअगर;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	काष्ठा seq_file *m = sta_iter_data->file;
	काष्ठा ieee80211_vअगर *vअगर = rtwvअगर_to_vअगर(rtwvअगर);
	u8 rssi;

	अगर (si->vअगर != vअगर)
		वापस;

	rssi = ewma_rssi_पढ़ो(&si->avg_rssi);
	seq_म_लिखो(m, "\tPeer %3d\n", si->mac_id);
	seq_म_लिखो(m, "\t\t%-24s = %d\n", "RSSI", rssi);
	seq_म_लिखो(m, "\t\t%-24s = %d\n", "BW mode", si->bw_mode);
पूर्ण

काष्ठा rtw_coex_vअगर_stat_iter_data अणु
	काष्ठा rtw_dev *rtwdev;
	काष्ठा seq_file *file;
पूर्ण;

अटल व्योम rtw_coex_vअगर_stat_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_coex_vअगर_stat_iter_data *vअगर_iter_data = data;
	काष्ठा rtw_coex_sta_stat_iter_data sta_iter_data;
	काष्ठा rtw_dev *rtwdev = vअगर_iter_data->rtwdev;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा seq_file *m = vअगर_iter_data->file;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	seq_म_लिखो(m, "Iface on Port (%d)\n", rtwvअगर->port);
	seq_म_लिखो(m, "\t%-32s = %d\n",
		   "Beacon interval", bss_conf->beacon_पूर्णांक);
	seq_म_लिखो(m, "\t%-32s = %d\n",
		   "Network Type", rtwvअगर->net_type);

	sta_iter_data.rtwvअगर = rtwvअगर;
	sta_iter_data.file = m;
	rtw_iterate_stas_atomic(rtwdev, rtw_coex_sta_stat_iter,
				&sta_iter_data);
पूर्ण

#घोषणा हाल_WLINK(src) \
	हाल COEX_WLINK_##src: वापस #src

अटल स्थिर अक्षर *rtw_coex_get_wl_coex_mode(u8 coex_wl_link_mode)
अणु
	चयन (coex_wl_link_mode) अणु
	हाल_WLINK(2G1PORT);
	हाल_WLINK(5G);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

व्योम rtw_coex_display_coex_info(काष्ठा rtw_dev *rtwdev, काष्ठा seq_file *m)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_fw_state *fw = &rtwdev->fw;
	काष्ठा rtw_coex_vअगर_stat_iter_data vअगर_iter_data;
	u8 reason = coex_dm->reason;
	u8 sys_lte;
	u16 score_board_WB, score_board_BW;
	u32 wl_reg_6c0, wl_reg_6c4, wl_reg_6c8, wl_reg_778, wl_reg_6cc;
	u32 lte_coex, bt_coex;
	u32 bt_hi_pri, bt_lo_pri;
	पूर्णांक i;

	score_board_BW = rtw_coex_पढ़ो_scbd(rtwdev);
	score_board_WB = coex_stat->score_board;
	wl_reg_6c0 = rtw_पढ़ो32(rtwdev, REG_BT_COEX_TABLE0);
	wl_reg_6c4 = rtw_पढ़ो32(rtwdev, REG_BT_COEX_TABLE1);
	wl_reg_6c8 = rtw_पढ़ो32(rtwdev, REG_BT_COEX_BRK_TABLE);
	wl_reg_6cc = rtw_पढ़ो32(rtwdev, REG_BT_COEX_TABLE_H);
	wl_reg_778 = rtw_पढ़ो8(rtwdev, REG_BT_STAT_CTRL);

	bt_hi_pri = rtw_पढ़ो32(rtwdev, REG_BT_ACT_STATISTICS);
	bt_lo_pri = rtw_पढ़ो32(rtwdev, REG_BT_ACT_STATISTICS_1);
	rtw_ग_लिखो8(rtwdev, REG_BT_COEX_ENH_INTR_CTRL,
		   BIT_R_GRANTALL_WLMASK | BIT_STATIS_BT_EN);

	coex_stat->hi_pri_tx = FIELD_GET(MASKLWORD, bt_hi_pri);
	coex_stat->hi_pri_rx = FIELD_GET(MASKHWORD, bt_hi_pri);

	coex_stat->lo_pri_tx = FIELD_GET(MASKLWORD, bt_lo_pri);
	coex_stat->lo_pri_rx = FIELD_GET(MASKHWORD, bt_lo_pri);

	sys_lte = rtw_पढ़ो8(rtwdev, 0x73);
	lte_coex = rtw_coex_पढ़ो_indirect_reg(rtwdev, 0x38);
	bt_coex = rtw_coex_पढ़ो_indirect_reg(rtwdev, 0x54);

	अगर (!coex_stat->bt_disabled && !coex_stat->bt_mailbox_reply) अणु
		rtw_coex_get_bt_supported_version(rtwdev,
				&coex_stat->bt_supported_version);
		rtw_coex_get_bt_patch_version(rtwdev, &coex_stat->patch_ver);
		rtw_coex_get_bt_supported_feature(rtwdev,
				&coex_stat->bt_supported_feature);
		rtw_coex_get_bt_reg(rtwdev, 3, 0xae, &coex_stat->bt_reg_venकरोr_ae);
		rtw_coex_get_bt_reg(rtwdev, 3, 0xac, &coex_stat->bt_reg_venकरोr_ac);

		अगर (coex_stat->patch_ver != 0)
			coex_stat->bt_mailbox_reply = true;
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], %s()\n", __func__);
	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "\t\tBT Coexist info %x\n", chip->id);
	seq_म_लिखो(m, "**********************************************\n");

	अगर (coex->manual_control) अणु
		seq_माला_दो(m, "============[Under Manual Control]============\n");
		seq_माला_दो(m, "==========================================\n");

	पूर्ण अन्यथा अगर (coex->stop_dm) अणु
		seq_माला_दो(m, "============[Coex is STOPPED]============\n");
		seq_माला_दो(m, "==========================================\n");

	पूर्ण अन्यथा अगर (coex->मुक्तze) अणु
		seq_माला_दो(m, "============[coex_freeze]============\n");
		seq_माला_दो(m, "==========================================\n");
	पूर्ण

	seq_म_लिखो(m, "%-40s = %s/ %d\n",
		   "Mech/ RFE",
		   efuse->share_ant ? "Shared" : "Non-Shared",
		   efuse->rfe_option);
	seq_म_लिखो(m, "%-40s = %08x/ 0x%02x/ 0x%08x %s\n",
		   "Coex Ver/ BT Dez/ BT Rpt",
		   chip->coex_para_ver, chip->bt_desired_ver,
		   coex_stat->bt_supported_version,
		   coex_stat->bt_disabled ? "(BT disabled)" :
		   coex_stat->bt_supported_version >= chip->bt_desired_ver ?
		   "(Match)" : "(Mismatch)");
	seq_म_लिखो(m, "%-40s = %s/ %u/ %d\n",
		   "Role/ RoleSwCnt/ IgnWL/ Feature",
		   coex_stat->bt_slave ? "Slave" : "Master",
		   coex_stat->cnt_bt[COEX_CNT_BT_ROLESWITCH],
		   coex_dm->ignore_wl_act);
	seq_म_लिखो(m, "%-40s = %u.%u/ 0x%x/ 0x%x/ %c\n",
		   "WL FW/ BT FW/ BT FW Desired/ KT",
		   fw->version, fw->sub_version,
		   coex_stat->patch_ver,
		   chip->wl_fw_desired_ver, coex_stat->kt_ver + 65);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ ch-(%u)\n",
		   "AFH Map",
		   coex_dm->wl_ch_info[0], coex_dm->wl_ch_info[1],
		   coex_dm->wl_ch_info[2], hal->current_channel);

	rtw_debugfs_get_simple_phy_info(m);
	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "\t\tBT Status\n");
	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "%-40s = %s/ %ddBm/ %u/ %u\n",
		   "BT status/ rssi/ retry/ pop",
		   coex_dm->bt_status == COEX_BTSTATUS_NCON_IDLE ? "non-conn" :
		   coex_dm->bt_status == COEX_BTSTATUS_CON_IDLE ? "conn-idle" : "busy",
		   coex_stat->bt_rssi - 100,
		   coex_stat->cnt_bt[COEX_CNT_BT_RETRY],
		   coex_stat->cnt_bt[COEX_CNT_BT_POPEVENT]);
	seq_म_लिखो(m, "%-40s = %s%s%s%s%s (multi-link %d)\n",
		   "Profiles",
		   coex_stat->bt_a2dp_exist ? (coex_stat->bt_a2dp_sink ?
					       "A2DP sink," : "A2DP,") : "",
		   coex_stat->bt_hfp_exist ? "HFP," : "",
		   coex_stat->bt_hid_exist ?
		   (coex_stat->bt_ble_exist ? "HID(RCU)," :
		    coex_stat->bt_hid_slot >= 2 ? "HID(4/18)" :
		    coex_stat->bt_ble_hid_exist ? "HID(BLE)" :
		    "HID(2/18),") : "",
		   coex_stat->bt_pan_exist ? coex_stat->bt_opp_exist ?
		   "OPP," : "PAN," : "",
		   coex_stat->bt_ble_voice ? "Voice," : "",
		   coex_stat->bt_multi_link);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ 0x%08x\n",
		   "Reinit/ Relink/ IgnWl/ Feature",
		   coex_stat->cnt_bt[COEX_CNT_BT_REINIT],
		   coex_stat->cnt_bt[COEX_CNT_BT_SETUPLINK],
		   coex_stat->cnt_bt[COEX_CNT_BT_IGNWLANACT],
		   coex_stat->bt_supported_feature);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "Page/ Inq/ iqk/ iqk fail",
		   coex_stat->cnt_bt[COEX_CNT_BT_PAGE],
		   coex_stat->cnt_bt[COEX_CNT_BT_INQ],
		   coex_stat->cnt_bt[COEX_CNT_BT_IQK],
		   coex_stat->cnt_bt[COEX_CNT_BT_IQKFAIL]);
	seq_म_लिखो(m, "%-40s = 0x%04x/ 0x%04x/ 0x%04x/ 0x%04x\n",
		   "0xae/ 0xac/ score board (W->B)/ (B->W)",
		   coex_stat->bt_reg_venकरोr_ae,
		   coex_stat->bt_reg_venकरोr_ac,
		   score_board_WB, score_board_BW);
	seq_म_लिखो(m, "%-40s = %u/%u, %u/%u\n",
		   "Hi-Pri TX/RX, Lo-Pri TX/RX",
		   coex_stat->hi_pri_tx, coex_stat->hi_pri_rx,
		   coex_stat->lo_pri_tx, coex_stat->lo_pri_rx);
	क्रम (i = 0; i < COEX_BTINFO_SRC_BT_IQK; i++)
		seq_म_लिखो(m, "%-40s = %7ph\n",
			   rtw_coex_get_bt_info_src_string(i),
			   coex_stat->bt_info_c2h[i]);

	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "\t\tWiFi Status\n");
	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "%-40s = %d\n",
		   "Scanning", test_bit(RTW_FLAG_SCANNING, rtwdev->flags));
	seq_म_लिखो(m, "%-40s = %u/ TX %d Mbps/ RX %d Mbps\n",
		   "G_busy/ TX/ RX",
		   coex_stat->wl_gl_busy,
		   rtwdev->stats.tx_throughput, rtwdev->stats.rx_throughput);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u\n",
		   "IPS/ Low Power/ PS mode",
		   test_bit(RTW_FLAG_INACTIVE_PS, rtwdev->flags),
		   test_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags),
		   rtwdev->lps_conf.mode);

	vअगर_iter_data.rtwdev = rtwdev;
	vअगर_iter_data.file = m;
	rtw_iterate_vअगरs_atomic(rtwdev, rtw_coex_vअगर_stat_iter, &vअगर_iter_data);

	अगर (coex->manual_control) अणु
		seq_म_लिखो(m, "**********************************************\n");
		seq_म_लिखो(m, "\t\tMechanism (Under Manual)\n");
		seq_म_लिखो(m, "**********************************************\n");
		seq_म_लिखो(m, "%-40s = %5ph (%d)\n",
			   "TDMA Now",
			   coex_dm->fw_tdma_para,
			   rtw_coex_get_tdma_index(rtwdev,
						   &coex_dm->fw_tdma_para[0]));
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "**********************************************\n");
		seq_म_लिखो(m, "\t\tMechanism\n");
		seq_म_लिखो(m, "**********************************************\n");
		seq_म_लिखो(m, "%-40s = %5ph (case-%d)\n",
			   "TDMA",
			   coex_dm->ps_tdma_para, coex_dm->cur_ps_tdma);
	पूर्ण
	seq_म_लिखो(m, "%-40s = %s/ %s/ %d\n",
		   "Coex Mode/Free Run/Timer base",
		   rtw_coex_get_wl_coex_mode(coex_stat->wl_coex_mode),
		   coex->मुक्तrun ? "Yes" : "No",
		   coex_stat->tdma_समयr_base);
	seq_म_लिखो(m, "%-40s = %d(%d)/ 0x%08x/ 0x%08x/ 0x%08x\n",
		   "Table/ 0x6c0/ 0x6c4/ 0x6c8",
		   coex_dm->cur_table,
		   rtw_coex_get_table_index(rtwdev, wl_reg_6c0, wl_reg_6c4),
		   wl_reg_6c0, wl_reg_6c4, wl_reg_6c8);
	seq_म_लिखो(m, "%-40s = 0x%08x/ 0x%08x/ %d/ reason (%s)\n",
		   "0x778/ 0x6cc/ Run Count/ Reason",
		   wl_reg_778, wl_reg_6cc,
		   coex_stat->cnt_wl[COEX_CNT_WL_COEXRUN],
		   rtw_coex_get_reason_string(reason));
	seq_म_लिखो(m, "%-40s = %3ph\n",
		   "AFH Map to BT",
		   coex_dm->wl_ch_info);
	seq_म_लिखो(m, "%-40s = %s/ %d\n",
		   "AntDiv/ BtCtrlLPS/ g_busy",
		   coex_stat->wl_क्रमce_lps_ctrl ? "On" : "Off",
		   coex_stat->wl_gl_busy);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ %u/ %u\n",
		   "Null All/ Retry/ Ack/ BT Empty/ BT Late",
		   coex_stat->wl_fw_dbg_info[1], coex_stat->wl_fw_dbg_info[2],
		   coex_stat->wl_fw_dbg_info[3], coex_stat->wl_fw_dbg_info[4],
		   coex_stat->wl_fw_dbg_info[5]);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %s/ %u\n",
		   "Cnt TDMA Toggle/ Lk 5ms/ Lk 5ms on/ FW",
		   coex_stat->wl_fw_dbg_info[6],
		   coex_stat->wl_fw_dbg_info[7],
		   coex_stat->wl_slot_extend ? "Yes" : "No",
		   coex_stat->cnt_wl[COEX_CNT_WL_FW_NOTIFY]);
	seq_म_लिखो(m, "%-40s = %d/ %d/ %s/ %d\n",
		   "WL_TxPw/ BT_TxPw/ WL_Rx/ BT_LNA_Lvl",
		   coex_dm->cur_wl_pwr_lvl,
		   coex_dm->cur_bt_pwr_lvl,
		   coex_dm->cur_wl_rx_low_gain_en ? "On" : "Off",
		   coex_dm->cur_bt_lna_lvl);

	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "\t\tHW setting\n");
	seq_म_लिखो(m, "**********************************************\n");
	seq_म_लिखो(m, "%-40s = %s/ %s\n",
		   "LTE Coex/ Path Owner",
		   lte_coex & BIT(7) ? "ON" : "OFF",
		   sys_lte & BIT(2) ? "WL" : "BT");
	seq_म_लिखो(m, "%-40s = RF:%s_BB:%s/ RF:%s_BB:%s/ %s\n",
		   "GNT_WL_CTRL/ GNT_BT_CTRL/ Dbg",
		   lte_coex & BIT(12) ? "SW" : "HW",
		   lte_coex & BIT(8) ? "SW" : "HW",
		   lte_coex & BIT(14) ? "SW" : "HW",
		   lte_coex & BIT(10) ? "SW" : "HW",
		   sys_lte & BIT(3) ? "On" : "Off");
	seq_म_लिखो(m, "%-40s = %lu/ %lu\n",
		   "GNT_WL/ GNT_BT",
		   (bt_coex & BIT(2)) >> 2, (bt_coex & BIT(3)) >> 3);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "CRC OK CCK/ OFDM/ HT/ VHT",
		   dm_info->cck_ok_cnt, dm_info->ofdm_ok_cnt,
		   dm_info->ht_ok_cnt, dm_info->vht_ok_cnt);
	seq_म_लिखो(m, "%-40s = %u/ %u/ %u/ %u\n",
		   "CRC ERR CCK/ OFDM/ HT/ VHT",
		   dm_info->cck_err_cnt, dm_info->ofdm_err_cnt,
		   dm_info->ht_err_cnt, dm_info->vht_err_cnt);
	seq_म_लिखो(m, "%-40s = %s/ %s/ %s/ %u\n",
		   "HiPr/ Locking/ Locked/ Noisy",
		   coex_stat->wl_hi_pri_task1 ? "Y" : "N",
		   coex_stat->wl_cck_lock ? "Y" : "N",
		   coex_stat->wl_cck_lock_ever ? "Y" : "N",
		   coex_stat->wl_noisy_level);

	rtw_coex_set_coexinfo_hw(rtwdev, m);
	seq_म_लिखो(m, "%-40s = %d/ %d/ %d/ %d\n",
		   "EVM A/ EVM B/ SNR A/ SNR B",
		   -dm_info->rx_evm_dbm[RF_PATH_A],
		   -dm_info->rx_evm_dbm[RF_PATH_B],
		   -dm_info->rx_snr[RF_PATH_A],
		   -dm_info->rx_snr[RF_PATH_B]);
	seq_म_लिखो(m, "%-40s = %d/ %d/ %d/ %d\n",
		   "CCK-CCA/CCK-FA/OFDM-CCA/OFDM-FA",
		   dm_info->cck_cca_cnt, dm_info->cck_fa_cnt,
		   dm_info->ofdm_cca_cnt, dm_info->ofdm_fa_cnt);
	seq_म_लिखो(m, "%-40s = %d/ %d/ %d/ %d\n", "CRC OK CCK/11g/11n/11ac",
		   dm_info->cck_ok_cnt, dm_info->ofdm_ok_cnt,
		   dm_info->ht_ok_cnt, dm_info->vht_ok_cnt);
	seq_म_लिखो(m, "%-40s = %d/ %d/ %d/ %d\n", "CRC Err CCK/11g/11n/11ac",
		   dm_info->cck_err_cnt, dm_info->ofdm_err_cnt,
		   dm_info->ht_err_cnt, dm_info->vht_err_cnt);

पूर्ण
#पूर्ण_अगर /* CONFIG_RTW88_DEBUGFS */
