<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "reg.h"
#समावेश "fw.h"
#समावेश "ps.h"
#समावेश "mac.h"
#समावेश "coex.h"
#समावेश "debug.h"

अटल पूर्णांक rtw_ips_pwr_up(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	ret = rtw_core_start(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "leave idle state failed\n");

	rtw_set_channel(rtwdev);
	clear_bit(RTW_FLAG_INACTIVE_PS, rtwdev->flags);

	वापस ret;
पूर्ण

पूर्णांक rtw_enter_ips(काष्ठा rtw_dev *rtwdev)
अणु
	set_bit(RTW_FLAG_INACTIVE_PS, rtwdev->flags);

	rtw_coex_ips_notअगरy(rtwdev, COEX_IPS_ENTER);

	rtw_core_stop(rtwdev);
	rtw_hci_link_ps(rtwdev, true);

	वापस 0;
पूर्ण

अटल व्योम rtw_restore_port_cfg_iter(व्योम *data, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = data;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	u32 config = ~0;

	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);
पूर्ण

पूर्णांक rtw_leave_ips(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	rtw_hci_link_ps(rtwdev, false);

	ret = rtw_ips_pwr_up(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to leave ips state\n");
		वापस ret;
	पूर्ण

	rtw_iterate_vअगरs_atomic(rtwdev, rtw_restore_port_cfg_iter, rtwdev);

	rtw_coex_ips_notअगरy(rtwdev, COEX_IPS_LEAVE);

	वापस 0;
पूर्ण

व्योम rtw_घातer_mode_change(काष्ठा rtw_dev *rtwdev, bool enter)
अणु
	u8 request, confirm, polling;
	पूर्णांक ret;

	request = rtw_पढ़ो8(rtwdev, rtwdev->hci.rpwm_addr);
	confirm = rtw_पढ़ो8(rtwdev, rtwdev->hci.cpwm_addr);

	/* toggle to request घातer mode, others reमुख्य 0 */
	request ^= request | BIT_RPWM_TOGGLE;
	अगर (enter) अणु
		request |= POWER_MODE_LCLK;
		अगर (rtw_get_lps_deep_mode(rtwdev) == LPS_DEEP_MODE_PG)
			request |= POWER_MODE_PG;
	पूर्ण
	/* Each request require an ack from firmware */
	request |= POWER_MODE_ACK;

	rtw_ग_लिखो8(rtwdev, rtwdev->hci.rpwm_addr, request);

	/* Check firmware get the घातer requset and ack via cpwm रेजिस्टर */
	ret = पढ़ो_poll_समयout_atomic(rtw_पढ़ो8, polling,
				       (polling ^ confirm) & BIT_RPWM_TOGGLE,
				       100, 15000, true, rtwdev,
				       rtwdev->hci.cpwm_addr);
	अगर (ret) अणु
		/* Hit here means that driver failed to get an ack from firmware.
		 * The reason could be that hardware is locked at Deep sleep,
		 * so most of the hardware circuits are not working, even
		 * रेजिस्टर पढ़ो/ग_लिखो; or firmware is locked in some state and
		 * cannot get the request. It should be treated as fatal error
		 * and requires an entire analysis about the firmware/hardware.
		 */
		WARN(1, "firmware failed to ack driver for %s Deep Power mode\n",
		     enter ? "entering" : "leaving");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_घातer_mode_change);

अटल व्योम __rtw_leave_lps_deep(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_hci_deep_ps(rtwdev, false);
पूर्ण

अटल पूर्णांक __rtw_fw_leave_lps_check_reg(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक i;

	/* Driver needs to रुको क्रम firmware to leave LPS state
	 * successfully. Firmware will send null packet to inक्रमm AP,
	 * and see अगर AP sends an ACK back, then firmware will restore
	 * the REG_TCR रेजिस्टर.
	 *
	 * If driver करोes not रुको क्रम firmware, null packet with
	 * PS bit could be sent due to incorrect REG_TCR setting.
	 *
	 * In our test, 100ms should be enough क्रम firmware to finish
	 * the flow. If REG_TCR Register is still incorrect after 100ms,
	 * just modअगरy it directly, and throw a warn message.
	 */
	क्रम (i = 0 ; i < LEAVE_LPS_TRY_CNT; i++) अणु
		अगर (rtw_पढ़ो32_mask(rtwdev, REG_TCR, BIT_PWRMGT_HWDATA_EN) == 0)
			वापस 0;
		msleep(20);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल  पूर्णांक __rtw_fw_leave_lps_check_c2h(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (रुको_क्रम_completion_समयout(&rtwdev->lps_leave_check,
					LEAVE_LPS_TIMEOUT))
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल व्योम rtw_fw_leave_lps_check(काष्ठा rtw_dev *rtwdev)
अणु
	bool ret = false;
	काष्ठा rtw_fw_state *fw;

	अगर (test_bit(RTW_FLAG_WOWLAN, rtwdev->flags))
		fw = &rtwdev->wow_fw;
	अन्यथा
		fw = &rtwdev->fw;

	अगर (fw->feature & FW_FEATURE_LPS_C2H)
		ret = __rtw_fw_leave_lps_check_c2h(rtwdev);
	अन्यथा
		ret = __rtw_fw_leave_lps_check_reg(rtwdev);

	अगर (ret) अणु
		rtw_ग_लिखो32_clr(rtwdev, REG_TCR, BIT_PWRMGT_HWDATA_EN);
		rtw_warn(rtwdev, "firmware failed to leave lps state\n");
	पूर्ण
पूर्ण

अटल व्योम rtw_fw_leave_lps_check_prepare(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fw_state *fw;

	अगर (test_bit(RTW_FLAG_WOWLAN, rtwdev->flags))
		fw = &rtwdev->wow_fw;
	अन्यथा
		fw = &rtwdev->fw;

	अगर (fw->feature & FW_FEATURE_LPS_C2H)
		reinit_completion(&rtwdev->lps_leave_check);
पूर्ण

अटल व्योम rtw_leave_lps_core(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;

	conf->state = RTW_ALL_ON;
	conf->awake_पूर्णांकerval = 1;
	conf->rlbm = 0;
	conf->smart_ps = 0;

	rtw_hci_link_ps(rtwdev, false);
	rtw_fw_leave_lps_check_prepare(rtwdev);
	rtw_fw_set_pwr_mode(rtwdev);
	rtw_fw_leave_lps_check(rtwdev);

	clear_bit(RTW_FLAG_LEISURE_PS, rtwdev->flags);

	rtw_coex_lps_notअगरy(rtwdev, COEX_LPS_DISABLE);
पूर्ण

क्रमागत rtw_lps_deep_mode rtw_get_lps_deep_mode(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (test_bit(RTW_FLAG_WOWLAN, rtwdev->flags))
		वापस rtwdev->lps_conf.wow_deep_mode;
	अन्यथा
		वापस rtwdev->lps_conf.deep_mode;
पूर्ण

अटल व्योम __rtw_enter_lps_deep(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtw_get_lps_deep_mode(rtwdev) == LPS_DEEP_MODE_NONE)
		वापस;

	अगर (!test_bit(RTW_FLAG_LEISURE_PS, rtwdev->flags)) अणु
		rtw_dbg(rtwdev, RTW_DBG_PS,
			"Should enter LPS before entering deep PS\n");
		वापस;
	पूर्ण

	अगर (rtw_get_lps_deep_mode(rtwdev) == LPS_DEEP_MODE_PG)
		rtw_fw_set_pg_info(rtwdev);

	rtw_hci_deep_ps(rtwdev, true);
पूर्ण

अटल व्योम rtw_enter_lps_core(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;

	conf->state = RTW_RF_OFF;
	conf->awake_पूर्णांकerval = 1;
	conf->rlbm = 1;
	conf->smart_ps = 2;

	rtw_coex_lps_notअगरy(rtwdev, COEX_LPS_ENABLE);

	rtw_fw_set_pwr_mode(rtwdev);
	rtw_hci_link_ps(rtwdev, true);

	set_bit(RTW_FLAG_LEISURE_PS, rtwdev->flags);
पूर्ण

अटल व्योम __rtw_enter_lps(काष्ठा rtw_dev *rtwdev, u8 port_id)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;

	अगर (test_bit(RTW_FLAG_LEISURE_PS, rtwdev->flags))
		वापस;

	conf->mode = RTW_MODE_LPS;
	conf->port_id = port_id;

	rtw_enter_lps_core(rtwdev);
पूर्ण

अटल व्योम __rtw_leave_lps(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;

	अगर (test_and_clear_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags)) अणु
		rtw_dbg(rtwdev, RTW_DBG_PS,
			"Should leave deep PS before leaving LPS\n");
		__rtw_leave_lps_deep(rtwdev);
	पूर्ण

	अगर (!test_bit(RTW_FLAG_LEISURE_PS, rtwdev->flags))
		वापस;

	conf->mode = RTW_MODE_ACTIVE;

	rtw_leave_lps_core(rtwdev);
पूर्ण

व्योम rtw_enter_lps(काष्ठा rtw_dev *rtwdev, u8 port_id)
अणु
	lockdep_निश्चित_held(&rtwdev->mutex);

	अगर (rtwdev->coex.stat.wl_क्रमce_lps_ctrl)
		वापस;

	__rtw_enter_lps(rtwdev, port_id);
	__rtw_enter_lps_deep(rtwdev);
पूर्ण

व्योम rtw_leave_lps(काष्ठा rtw_dev *rtwdev)
अणु
	lockdep_निश्चित_held(&rtwdev->mutex);

	__rtw_leave_lps_deep(rtwdev);
	__rtw_leave_lps(rtwdev);
पूर्ण

व्योम rtw_leave_lps_deep(काष्ठा rtw_dev *rtwdev)
अणु
	lockdep_निश्चित_held(&rtwdev->mutex);

	__rtw_leave_lps_deep(rtwdev);
पूर्ण
