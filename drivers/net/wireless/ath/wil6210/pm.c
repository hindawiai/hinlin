<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश "wil6210.h"
#समावेश <linux/jअगरfies.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा WIL6210_AUTOSUSPEND_DELAY_MS (1000)

अटल व्योम wil_pm_wake_connected_net_queues(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;

	mutex_lock(&wil->vअगर_mutex);
	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[i];

		अगर (vअगर && test_bit(wil_vअगर_fwconnected, vअगर->status))
			wil_update_net_queues_bh(wil, vअगर, शून्य, false);
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);
पूर्ण

अटल व्योम wil_pm_stop_all_net_queues(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;

	mutex_lock(&wil->vअगर_mutex);
	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[i];

		अगर (vअगर)
			wil_update_net_queues_bh(wil, vअगर, शून्य, true);
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);
पूर्ण

अटल bool
wil_can_suspend_vअगर(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
		    bool is_runसमय)
अणु
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_MONITOR:
		wil_dbg_pm(wil, "Sniffer\n");
		वापस false;

	/* क्रम STA-like पूर्णांकerface, करोn't runसमय suspend */
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (test_bit(wil_vअगर_fwconnecting, vअगर->status)) अणु
			wil_dbg_pm(wil, "Delay suspend when connecting\n");
			वापस false;
		पूर्ण
		अगर (is_runसमय) अणु
			wil_dbg_pm(wil, "STA-like interface\n");
			वापस false;
		पूर्ण
		अवरोध;
	/* AP-like पूर्णांकerface - can't suspend */
	शेष:
		wil_dbg_pm(wil, "AP-like interface\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक wil_can_suspend(काष्ठा wil6210_priv *wil, bool is_runसमय)
अणु
	पूर्णांक rc = 0, i;
	bool wmi_only = test_bit(WMI_FW_CAPABILITY_WMI_ONLY,
				 wil->fw_capabilities);
	bool active_अगरaces;

	wil_dbg_pm(wil, "can_suspend: %s\n", is_runसमय ? "runtime" : "system");

	अगर (wmi_only || debug_fw) अणु
		wil_dbg_pm(wil, "Deny any suspend - %s mode\n",
			   wmi_only ? "wmi_only" : "debug_fw");
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (is_runसमय && !wil->platक्रमm_ops.suspend) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	mutex_lock(&wil->vअगर_mutex);
	active_अगरaces = wil_has_active_अगरaces(wil, true, false);
	mutex_unlock(&wil->vअगर_mutex);

	अगर (!active_अगरaces) अणु
		/* can always sleep when करोwn */
		wil_dbg_pm(wil, "Interface is down\n");
		जाओ out;
	पूर्ण
	अगर (test_bit(wil_status_resetting, wil->status)) अणु
		wil_dbg_pm(wil, "Delay suspend when resetting\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (wil->recovery_state != fw_recovery_idle) अणु
		wil_dbg_pm(wil, "Delay suspend during recovery\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	/* पूर्णांकerface is running */
	mutex_lock(&wil->vअगर_mutex);
	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[i];

		अगर (!vअगर)
			जारी;
		अगर (!wil_can_suspend_vअगर(wil, vअगर, is_runसमय)) अणु
			rc = -EBUSY;
			mutex_unlock(&wil->vअगर_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

out:
	wil_dbg_pm(wil, "can_suspend: %s => %s (%d)\n",
		   is_runसमय ? "runtime" : "system", rc ? "No" : "Yes", rc);

	अगर (rc)
		wil->suspend_stats.rejected_by_host++;

	वापस rc;
पूर्ण

अटल पूर्णांक wil_resume_keep_radio_on(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc = 0;

	/* wil_status_resuming will be cleared when getting
	 * WMI_TRAFFIC_RESUME_EVENTID
	 */
	set_bit(wil_status_resuming, wil->status);
	clear_bit(wil_status_suspended, wil->status);
	wil_c(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_RST_PWGD);
	wil_unmask_irq(wil);

	wil6210_bus_request(wil, wil->bus_request_kbps_pre_suspend);

	/* Send WMI resume request to the device */
	rc = wmi_resume(wil);
	अगर (rc) अणु
		wil_err(wil, "device failed to resume (%d)\n", rc);
		अगर (no_fw_recovery)
			जाओ out;
		rc = wil_करोwn(wil);
		अगर (rc) अणु
			wil_err(wil, "wil_down failed (%d)\n", rc);
			जाओ out;
		पूर्ण
		rc = wil_up(wil);
		अगर (rc) अणु
			wil_err(wil, "wil_up failed (%d)\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Wake all queues */
	wil_pm_wake_connected_net_queues(wil);

out:
	अगर (rc)
		set_bit(wil_status_suspended, wil->status);
	वापस rc;
पूर्ण

अटल पूर्णांक wil_suspend_keep_radio_on(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ data_comp_to;

	wil_dbg_pm(wil, "suspend keep radio on\n");

	/* Prevent handling of new tx and wmi commands */
	rc = करोwn_ग_लिखो_trylock(&wil->mem_lock);
	अगर (!rc) अणु
		wil_err(wil,
			"device is busy. down_write_trylock failed, returned (0x%x)\n",
			rc);
		wil->suspend_stats.rejected_by_host++;
		वापस -EBUSY;
	पूर्ण

	set_bit(wil_status_suspending, wil->status);
	up_ग_लिखो(&wil->mem_lock);

	wil_pm_stop_all_net_queues(wil);

	अगर (!wil_is_tx_idle(wil)) अणु
		wil_dbg_pm(wil, "Pending TX data, reject suspend\n");
		wil->suspend_stats.rejected_by_host++;
		जाओ reject_suspend;
	पूर्ण

	अगर (!wil->txrx_ops.is_rx_idle(wil)) अणु
		wil_dbg_pm(wil, "Pending RX data, reject suspend\n");
		wil->suspend_stats.rejected_by_host++;
		जाओ reject_suspend;
	पूर्ण

	अगर (!wil_is_wmi_idle(wil)) अणु
		wil_dbg_pm(wil, "Pending WMI events, reject suspend\n");
		wil->suspend_stats.rejected_by_host++;
		जाओ reject_suspend;
	पूर्ण

	/* Send WMI suspend request to the device */
	rc = wmi_suspend(wil);
	अगर (rc) अणु
		wil_dbg_pm(wil, "wmi_suspend failed, reject suspend (%d)\n",
			   rc);
		जाओ reject_suspend;
	पूर्ण

	/* Wait क्रम completion of the pending RX packets */
	data_comp_to = jअगरfies + msecs_to_jअगरfies(WIL_DATA_COMPLETION_TO_MS);
	अगर (test_bit(wil_status_napi_en, wil->status)) अणु
		जबतक (!wil->txrx_ops.is_rx_idle(wil)) अणु
			अगर (समय_after(jअगरfies, data_comp_to)) अणु
				अगर (wil->txrx_ops.is_rx_idle(wil))
					अवरोध;
				wil_err(wil,
					"TO waiting for idle RX, suspend failed\n");
				wil->suspend_stats.r_on.failed_suspends++;
				जाओ resume_after_fail;
			पूर्ण
			wil_dbg_ratelimited(wil, "rx vring is not empty -> NAPI\n");
			napi_synchronize(&wil->napi_rx);
			msleep(20);
		पूर्ण
	पूर्ण

	/* In हाल of pending WMI events, reject the suspend
	 * and resume the device.
	 * This can happen अगर the device sent the WMI events beक्रमe
	 * approving the suspend.
	 */
	अगर (!wil_is_wmi_idle(wil)) अणु
		wil_err(wil, "suspend failed due to pending WMI events\n");
		wil->suspend_stats.r_on.failed_suspends++;
		जाओ resume_after_fail;
	पूर्ण

	wil_mask_irq(wil);

	/* Disable device reset on PERST */
	wil_s(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_RST_PWGD);

	अगर (wil->platक्रमm_ops.suspend) अणु
		rc = wil->platक्रमm_ops.suspend(wil->platक्रमm_handle, true);
		अगर (rc) अणु
			wil_err(wil, "platform device failed to suspend (%d)\n",
				rc);
			wil->suspend_stats.r_on.failed_suspends++;
			wil_c(wil, RGF_USER_CLKS_CTL_0, BIT_USER_CLKS_RST_PWGD);
			wil_unmask_irq(wil);
			जाओ resume_after_fail;
		पूर्ण
	पूर्ण

	/* Save the current bus request to वापस to the same in resume */
	wil->bus_request_kbps_pre_suspend = wil->bus_request_kbps;
	wil6210_bus_request(wil, 0);

	set_bit(wil_status_suspended, wil->status);
	clear_bit(wil_status_suspending, wil->status);

	वापस rc;

resume_after_fail:
	set_bit(wil_status_resuming, wil->status);
	clear_bit(wil_status_suspending, wil->status);
	rc = wmi_resume(wil);
	/* अगर resume succeeded, reject the suspend */
	अगर (!rc) अणु
		rc = -EBUSY;
		wil_pm_wake_connected_net_queues(wil);
	पूर्ण
	वापस rc;

reject_suspend:
	clear_bit(wil_status_suspending, wil->status);
	wil_pm_wake_connected_net_queues(wil);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक wil_suspend_radio_off(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc = 0;
	bool active_अगरaces;

	wil_dbg_pm(wil, "suspend radio off\n");

	rc = करोwn_ग_लिखो_trylock(&wil->mem_lock);
	अगर (!rc) अणु
		wil_err(wil,
			"device is busy. down_write_trylock failed, returned (0x%x)\n",
			rc);
		wil->suspend_stats.rejected_by_host++;
		वापस -EBUSY;
	पूर्ण

	set_bit(wil_status_suspending, wil->status);
	up_ग_लिखो(&wil->mem_lock);

	/* अगर netअगर up, hardware is alive, shut it करोwn */
	mutex_lock(&wil->vअगर_mutex);
	active_अगरaces = wil_has_active_अगरaces(wil, true, false);
	mutex_unlock(&wil->vअगर_mutex);

	अगर (active_अगरaces) अणु
		rc = wil_करोwn(wil);
		अगर (rc) अणु
			wil_err(wil, "wil_down : %d\n", rc);
			wil->suspend_stats.r_off.failed_suspends++;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Disable PCIe IRQ to prevent sporadic IRQs when PCIe is suspending */
	wil_dbg_pm(wil, "Disabling PCIe IRQ before suspending\n");
	wil_disable_irq(wil);

	अगर (wil->platक्रमm_ops.suspend) अणु
		rc = wil->platक्रमm_ops.suspend(wil->platक्रमm_handle, false);
		अगर (rc) अणु
			wil_enable_irq(wil);
			wil->suspend_stats.r_off.failed_suspends++;
			जाओ out;
		पूर्ण
	पूर्ण

	set_bit(wil_status_suspended, wil->status);

out:
	clear_bit(wil_status_suspending, wil->status);
	wil_dbg_pm(wil, "suspend radio off: %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_resume_radio_off(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc = 0;
	bool active_अगरaces;

	wil_dbg_pm(wil, "Enabling PCIe IRQ\n");
	wil_enable_irq(wil);
	/* अगर any netअगर up, bring hardware up
	 * During खोलो(), IFF_UP set after actual device method
	 * invocation. This prevent recursive call to wil_up()
	 * wil_status_suspended will be cleared in wil_reset
	 */
	mutex_lock(&wil->vअगर_mutex);
	active_अगरaces = wil_has_active_अगरaces(wil, true, false);
	mutex_unlock(&wil->vअगर_mutex);
	अगर (active_अगरaces)
		rc = wil_up(wil);
	अन्यथा
		clear_bit(wil_status_suspended, wil->status);

	वापस rc;
पूर्ण

पूर्णांक wil_suspend(काष्ठा wil6210_priv *wil, bool is_runसमय, bool keep_radio_on)
अणु
	पूर्णांक rc = 0;

	wil_dbg_pm(wil, "suspend: %s\n", is_runसमय ? "runtime" : "system");

	अगर (test_bit(wil_status_suspended, wil->status)) अणु
		wil_dbg_pm(wil, "trying to suspend while suspended\n");
		वापस 0;
	पूर्ण

	अगर (!keep_radio_on)
		rc = wil_suspend_radio_off(wil);
	अन्यथा
		rc = wil_suspend_keep_radio_on(wil);

	wil_dbg_pm(wil, "suspend: %s => %d\n",
		   is_runसमय ? "runtime" : "system", rc);

	वापस rc;
पूर्ण

पूर्णांक wil_resume(काष्ठा wil6210_priv *wil, bool is_runसमय, bool keep_radio_on)
अणु
	पूर्णांक rc = 0;

	wil_dbg_pm(wil, "resume: %s\n", is_runसमय ? "runtime" : "system");

	अगर (wil->platक्रमm_ops.resume) अणु
		rc = wil->platक्रमm_ops.resume(wil->platक्रमm_handle,
					      keep_radio_on);
		अगर (rc) अणु
			wil_err(wil, "platform_ops.resume : %d\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (keep_radio_on)
		rc = wil_resume_keep_radio_on(wil);
	अन्यथा
		rc = wil_resume_radio_off(wil);

out:
	wil_dbg_pm(wil, "resume: %s => %d\n", is_runसमय ? "runtime" : "system",
		   rc);
	वापस rc;
पूर्ण

व्योम wil_pm_runसमय_allow(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा device *dev = wil_to_dev(wil);

	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, WIL6210_AUTOSUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_allow(dev);
पूर्ण

व्योम wil_pm_runसमय_क्रमbid(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा device *dev = wil_to_dev(wil);

	pm_runसमय_क्रमbid(dev);
	pm_runसमय_get_noresume(dev);
पूर्ण

पूर्णांक wil_pm_runसमय_get(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = wil_to_dev(wil);

	rc = pm_runसमय_get_sync(dev);
	अगर (rc < 0) अणु
		wil_err(wil, "pm_runtime_get_sync() failed, rc = %d\n", rc);
		pm_runसमय_put_noidle(dev);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम wil_pm_runसमय_put(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा device *dev = wil_to_dev(wil);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण
