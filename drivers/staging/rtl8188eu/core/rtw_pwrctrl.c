<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_PWRCTRL_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <usb_ops_linux.h>
#समावेश <linux/usb.h>

अटल पूर्णांक rtw_hw_suspend(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	अगर ((!padapter->bup) || (padapter->bDriverStopped) ||
	    (padapter->bSurpriseRemoved)) अणु
		DBG_88E("padapter->bup=%d bDriverStopped=%d bSurpriseRemoved = %d\n",
			padapter->bup, padapter->bDriverStopped,
			padapter->bSurpriseRemoved);
		जाओ error_निकास;
	पूर्ण

	/* प्रणाली suspend */
	LeaveAllPowerSaveMode(padapter);

	DBG_88E("==> %s\n", __func__);
	mutex_lock(&pwrpriv->mutex_lock);
	pwrpriv->bips_processing = true;
	/* s1. */
	अगर (pnetdev) अणु
		netअगर_carrier_off(pnetdev);
		netअगर_tx_stop_all_queues(pnetdev);
	पूर्ण

	/* s2. */
	rtw_disassoc_cmd(padapter, 500, false);

	/* s2-2.  indicate disconnect to os */
	अणु
		काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

		अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			_clr_fwstate_(pmlmepriv, _FW_LINKED);

			led_control_8188eu(padapter, LED_CTL_NO_LINK);

			rtw_os_indicate_disconnect(padapter);

			/* करोnnot enqueue cmd */
			rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_DISCONNECT, 0);
		पूर्ण
	पूर्ण
	/* s2-3. */
	rtw_मुक्त_assoc_resources(padapter);

	/* s2-4. */
	rtw_मुक्त_network_queue(padapter, true);
	rtw_ips_dev_unload(padapter);
	pwrpriv->rf_pwrstate = rf_off;
	pwrpriv->bips_processing = false;

	mutex_unlock(&pwrpriv->mutex_lock);

	वापस 0;

error_निकास:
	DBG_88E("%s, failed\n", __func__);
	वापस -1;
पूर्ण

अटल पूर्णांक rtw_hw_resume(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	/* प्रणाली resume */
	DBG_88E("==> %s\n", __func__);
	mutex_lock(&pwrpriv->mutex_lock);
	pwrpriv->bips_processing = true;
	rtw_reset_drv_sw(padapter);

	अगर (ips_netdrv_खोलो(netdev_priv(pnetdev)) != _SUCCESS) अणु
		mutex_unlock(&pwrpriv->mutex_lock);
		जाओ error_निकास;
	पूर्ण

	netअगर_device_attach(pnetdev);
	netअगर_carrier_on(pnetdev);

	अगर (!netअगर_queue_stopped(pnetdev))
		netअगर_start_queue(pnetdev);
	अन्यथा
		netअगर_wake_queue(pnetdev);

	pwrpriv->bkeepfwalive = false;
	pwrpriv->brfoffbyhw = false;

	pwrpriv->rf_pwrstate = rf_on;
	pwrpriv->bips_processing = false;

	mutex_unlock(&pwrpriv->mutex_lock);

	वापस 0;
error_निकास:
	DBG_88E("%s, Open net dev failed\n", __func__);
	वापस -1;
पूर्ण

व्योम ips_enter(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा xmit_priv *pxmit_priv = &padapter->xmitpriv;

	अगर (padapter->registrypriv.mp_mode == 1)
		वापस;

	अगर (pxmit_priv->मुक्त_xmitbuf_cnt != NR_XMITBUFF ||
	    pxmit_priv->मुक्त_xmit_extbuf_cnt != NR_XMIT_EXTBUFF) अणु
		DBG_88E_LEVEL(_drv_info_, "There are some pkts to transmit\n");
		DBG_88E_LEVEL(_drv_info_, "free_xmitbuf_cnt: %d, free_xmit_extbuf_cnt: %d\n",
			      pxmit_priv->मुक्त_xmitbuf_cnt, pxmit_priv->मुक्त_xmit_extbuf_cnt);
		वापस;
	पूर्ण

	mutex_lock(&pwrpriv->mutex_lock);

	pwrpriv->bips_processing = true;

	/*  syn ips_mode with request */
	pwrpriv->ips_mode = pwrpriv->ips_mode_req;

	pwrpriv->ips_enter_cnts++;
	DBG_88E("==>%s:%d\n", __func__, pwrpriv->ips_enter_cnts);
	अगर (rf_off == pwrpriv->change_rfpwrstate) अणु
		pwrpriv->bघातer_saving = true;
		DBG_88E_LEVEL(_drv_info_, "nolinked power save enter\n");

		अगर (pwrpriv->ips_mode == IPS_LEVEL_2)
			pwrpriv->bkeepfwalive = true;

		rtw_ips_pwr_करोwn(padapter);
		pwrpriv->rf_pwrstate = rf_off;
	पूर्ण
	pwrpriv->bips_processing = false;

	mutex_unlock(&pwrpriv->mutex_lock);
पूर्ण

पूर्णांक ips_leave(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक result = _SUCCESS;
	पूर्णांक keyid;

	mutex_lock(&pwrpriv->mutex_lock);

	अगर ((pwrpriv->rf_pwrstate == rf_off) && (!pwrpriv->bips_processing)) अणु
		pwrpriv->bips_processing = true;
		pwrpriv->change_rfpwrstate = rf_on;
		pwrpriv->ips_leave_cnts++;
		DBG_88E("==>%s:%d\n", __func__, pwrpriv->ips_leave_cnts);

		result = rtw_ips_pwr_up(padapter);
		अगर (result == _SUCCESS)
			pwrpriv->rf_pwrstate = rf_on;

		DBG_88E_LEVEL(_drv_info_, "nolinked power save leave\n");

		अगर ((psecuritypriv->करोt11PrivacyAlgrthm == _WEP40_) || (psecuritypriv->करोt11PrivacyAlgrthm == _WEP104_)) अणु
			DBG_88E("==>%s, channel(%d), processing(%x)\n", __func__, padapter->mlmeextpriv.cur_channel, pwrpriv->bips_processing);
			set_channel_bwmode(padapter, padapter->mlmeextpriv.cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);
			क्रम (keyid = 0; keyid < 4; keyid++) अणु
				अगर (pmlmepriv->key_mask & BIT(keyid)) अणु
					अगर (keyid == psecuritypriv->करोt11PrivacyKeyIndex)
						result = rtw_set_key(padapter, psecuritypriv, keyid, 1);
					अन्यथा
						result = rtw_set_key(padapter, psecuritypriv, keyid, 0);
				पूर्ण
			पूर्ण
		पूर्ण

		DBG_88E("==> %s.....LED(0x%08x)...\n", __func__, usb_पढ़ो32(padapter, 0x4c));
		pwrpriv->bips_processing = false;

		pwrpriv->bkeepfwalive = false;
		pwrpriv->bघातer_saving = false;
	पूर्ण

	mutex_unlock(&pwrpriv->mutex_lock);

	वापस result;
पूर्ण

अटल bool rtw_pwr_unassociated_idle(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	अगर (समय_after_eq(adapter->pwrctrlpriv.ips_deny_समय, jअगरfies))
		वापस false;

	अगर (check_fwstate(pmlmepriv, WIFI_ASOC_STATE | WIFI_SITE_MONITOR) ||
	    check_fwstate(pmlmepriv, WIFI_UNDER_LINKING | WIFI_UNDER_WPS) ||
	    check_fwstate(pmlmepriv, WIFI_AP_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE))
		वापस false;

	वापस true;
पूर्ण

व्योम rtw_ps_processor(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	क्रमागत rt_rf_घातer_state rfpwrstate;

	pwrpriv->ps_processing = true;

	अगर (pwrpriv->bips_processing)
		जाओ निकास;

	अगर (padapter->pwrctrlpriv.bHWPwrPindetect) अणु
		rfpwrstate = RfOnOffDetect(padapter);
		DBG_88E("@@@@- #2  %s==> rfstate:%s\n", __func__, (rfpwrstate == rf_on) ? "rf_on" : "rf_off");

		अगर (rfpwrstate != pwrpriv->rf_pwrstate) अणु
			अगर (rfpwrstate == rf_off) अणु
				pwrpriv->change_rfpwrstate = rf_off;
				pwrpriv->brfoffbyhw = true;
				rtw_hw_suspend(padapter);
			पूर्ण अन्यथा अणु
				pwrpriv->change_rfpwrstate = rf_on;
				rtw_hw_resume(padapter);
			पूर्ण
			DBG_88E("current rf_pwrstate(%s)\n", (pwrpriv->rf_pwrstate == rf_off) ? "rf_off" : "rf_on");
		पूर्ण
		pwrpriv->pwr_state_check_cnts++;
	पूर्ण

	अगर (pwrpriv->ips_mode_req == IPS_NONE)
		जाओ निकास;

	अगर (!rtw_pwr_unassociated_idle(padapter))
		जाओ निकास;

	अगर ((pwrpriv->rf_pwrstate == rf_on) && ((pwrpriv->pwr_state_check_cnts % 4) == 0)) अणु
		DBG_88E("==>%s .fw_state(%x)\n", __func__, get_fwstate(pmlmepriv));
		pwrpriv->change_rfpwrstate = rf_off;

		ips_enter(padapter);
	पूर्ण
निकास:
	rtw_set_pwr_state_check_समयr(&padapter->pwrctrlpriv);
	pwrpriv->ps_processing = false;
पूर्ण

अटल व्योम pwr_state_check_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *padapter =
		from_समयr(padapter, t,
			   pwrctrlpriv.pwr_state_check_समयr);

	rtw_ps_cmd(padapter);
पूर्ण

/*
 *
 * Parameters
 *	padapter
 *	pslv			घातer state level, only could be PS_STATE_S0 ~ PS_STATE_S4
 *
 */
व्योम rtw_set_rpwm(काष्ठा adapter *padapter, u8 pslv)
अणु
	u8 rpwm;
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	pslv = PS_STATE(pslv);

	अगर (pwrpriv->btcoex_rfon) अणु
		अगर (pslv < PS_STATE_S4)
			pslv = PS_STATE_S3;
	पूर्ण

	अगर (pwrpriv->rpwm == pslv) अणु
		RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_err_,
			 ("%s: Already set rpwm[0x%02X], new=0x%02X!\n", __func__, pwrpriv->rpwm, pslv));
		वापस;
	पूर्ण

	अगर ((padapter->bSurpriseRemoved) ||
	    (!padapter->hw_init_completed)) अणु
		RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_err_,
			 ("%s: SurpriseRemoved(%d) hw_init_completed(%d)\n",
			 __func__, padapter->bSurpriseRemoved, padapter->hw_init_completed));

		pwrpriv->cpwm = PS_STATE_S4;

		वापस;
	पूर्ण

	अगर (padapter->bDriverStopped) अणु
		RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_err_,
			 ("%s: change power state(0x%02X) when DriverStopped\n", __func__, pslv));

		अगर (pslv < PS_STATE_S2) अणु
			RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_err_,
				 ("%s: Reject to enter PS_STATE(0x%02X) lower than S2 when DriverStopped!!\n", __func__, pslv));
			वापस;
		पूर्ण
	पूर्ण

	rpwm = pslv | pwrpriv->tog;
	RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_notice_,
		 ("%s: rpwm=0x%02x cpwm=0x%02x\n", __func__, rpwm, pwrpriv->cpwm));

	pwrpriv->rpwm = pslv;

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_RPWM, (u8 *)(&rpwm));

	pwrpriv->tog += 0x80;
	pwrpriv->cpwm = pslv;
पूर्ण

अटल u8 PS_RDY_CHECK(काष्ठा adapter *padapter)
अणु
	अचिन्हित दीर्घ curr_समय, delta_समय;
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	curr_समय = jअगरfies;
	delta_समय = curr_समय - pwrpriv->DelayLPSLastTimeStamp;

	अगर (delta_समय < LPS_DELAY_TIME)
		वापस false;

	अगर ((!check_fwstate(pmlmepriv, _FW_LINKED)) ||
	    (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) ||
	    (check_fwstate(pmlmepriv, WIFI_AP_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		वापस false;
	अगर (pwrpriv->bInSuspend)
		वापस false;
	अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X &&
	    !padapter->securitypriv.binstallGrpkey) अणु
		DBG_88E("Group handshake still in progress !!!\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtw_set_ps_mode(काष्ठा adapter *padapter, u8 ps_mode, u8 smart_ps, u8 bcn_ant_mode)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_notice_,
		 ("%s: PowerMode=%d Smart_PS=%d\n",
		  __func__, ps_mode, smart_ps));

	अगर (ps_mode > PM_Card_Disable) अणु
		RT_TRACE(_module_rtl871x_pwrctrl_c_, _drv_err_, ("ps_mode:%d error\n", ps_mode));
		वापस;
	पूर्ण

	अगर (pwrpriv->pwr_mode == ps_mode) अणु
		अगर (ps_mode == PS_MODE_ACTIVE)
			वापस;

		अगर ((pwrpriv->smart_ps == smart_ps) &&
		    (pwrpriv->bcn_ant_mode == bcn_ant_mode))
			वापस;
	पूर्ण

	/* अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE) */
	अगर (ps_mode == PS_MODE_ACTIVE) अणु
		अगर (PS_RDY_CHECK(padapter)) अणु
			DBG_88E("%s: Enter 802.11 power save\n", __func__);
			pwrpriv->bFwCurrentInPSMode = true;
			pwrpriv->pwr_mode = ps_mode;
			pwrpriv->smart_ps = smart_ps;
			pwrpriv->bcn_ant_mode = bcn_ant_mode;
			rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));
			rtw_set_rpwm(padapter, PS_STATE_S2);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return:
 *	0:	Leave OK
 *	-1:	Timeout
 *	-2:	Other error
 */
s32 LPS_RF_ON_check(काष्ठा adapter *padapter, u32 delay_ms)
अणु
	अचिन्हित दीर्घ start_समय;
	u8 bAwake = false;
	s32 err = 0;

	start_समय = jअगरfies;
	जबतक (1) अणु
		rtw_hal_get_hwreg(padapter, HW_VAR_FWLPS_RF_ON, &bAwake);
		अगर (bAwake)
			अवरोध;

		अगर (padapter->bSurpriseRemoved) अणु
			err = -2;
			DBG_88E("%s: device surprise removed!!\n", __func__);
			अवरोध;
		पूर्ण

		अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > delay_ms) अणु
			err = -1;
			DBG_88E("%s: Wait for FW LPS leave more than %u ms!!!\n", __func__, delay_ms);
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस err;
पूर्ण

/*  */
/*	Description: */
/*		Enter the leisure घातer save mode. */
/*  */
व्योम LPS_Enter(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	अगर (!PS_RDY_CHECK(padapter))
		वापस;

	अगर (pwrpriv->bLeisurePs) अणु
		/*  Idle क्रम a जबतक अगर we connect to AP a जबतक ago. */
		अगर (pwrpriv->LpsIdleCount >= 2) अणु /*   4 Sec */
			अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE) अणु
				pwrpriv->bघातer_saving = true;
				DBG_88E("%s smart_ps:%d\n", __func__, pwrpriv->smart_ps);
				/* For Tenda W311R IOT issue */
				rtw_set_ps_mode(padapter, pwrpriv->घातer_mgnt, pwrpriv->smart_ps, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			pwrpriv->LpsIdleCount++;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा LPS_LEAVE_TIMEOUT_MS 100

/*	Description: */
/*		Leave the leisure घातer save mode. */
व्योम LPS_Leave(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	अगर (pwrpriv->bLeisurePs) अणु
		अगर (pwrpriv->pwr_mode != PS_MODE_ACTIVE) अणु
			rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0);

			अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
				LPS_RF_ON_check(padapter, LPS_LEAVE_TIMEOUT_MS);
		पूर्ण
	पूर्ण

	pwrpriv->bघातer_saving = false;
पूर्ण

/*  */
/*  Description: Leave all घातer save mode: LPS, FwLPS, IPS अगर needed. */
/*  Move code to function by tynli. 2010.03.26. */
/*  */
व्योम LeaveAllPowerSaveMode(काष्ठा adapter *Adapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_lps_ctrl_wk_cmd(Adapter, LPS_CTRL_LEAVE, 0);
पूर्ण

व्योम rtw_init_pwrctrl_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	mutex_init(&pwrctrlpriv->mutex_lock);
	pwrctrlpriv->rf_pwrstate = rf_on;
	pwrctrlpriv->ips_enter_cnts = 0;
	pwrctrlpriv->ips_leave_cnts = 0;
	pwrctrlpriv->bips_processing = false;

	pwrctrlpriv->ips_mode = padapter->registrypriv.ips_mode;
	pwrctrlpriv->ips_mode_req = padapter->registrypriv.ips_mode;

	pwrctrlpriv->pwr_state_check_पूर्णांकerval = RTW_PWR_STATE_CHK_INTERVAL;
	pwrctrlpriv->pwr_state_check_cnts = 0;
	pwrctrlpriv->bInternalAutoSuspend = false;
	pwrctrlpriv->bInSuspend = false;
	pwrctrlpriv->bkeepfwalive = false;

	pwrctrlpriv->LpsIdleCount = 0;
	अगर (padapter->registrypriv.mp_mode == 1)
		pwrctrlpriv->घातer_mgnt = PS_MODE_ACTIVE;
	अन्यथा
		pwrctrlpriv->घातer_mgnt = padapter->registrypriv.घातer_mgnt;/*  PS_MODE_MIN; */
	pwrctrlpriv->bLeisurePs = (pwrctrlpriv->घातer_mgnt != PS_MODE_ACTIVE);

	pwrctrlpriv->bFwCurrentInPSMode = false;

	pwrctrlpriv->rpwm = 0;
	pwrctrlpriv->cpwm = PS_STATE_S4;

	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;
	pwrctrlpriv->smart_ps = padapter->registrypriv.smart_ps;
	pwrctrlpriv->bcn_ant_mode = 0;

	pwrctrlpriv->tog = 0x80;

	pwrctrlpriv->btcoex_rfon = false;

	समयr_setup(&pwrctrlpriv->pwr_state_check_समयr,
		    pwr_state_check_handler, 0);
पूर्ण

/*
 * rtw_pwr_wakeup - Wake the NIC up from: 1)IPS. 2)USB स्वतःsuspend
 * @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
 * @ips_deffer_ms: the ms will prevent from falling पूर्णांकo IPS after wakeup
 * Return _SUCCESS or _FAIL
 */

पूर्णांक _rtw_pwr_wakeup(काष्ठा adapter *padapter, u32 ips_deffer_ms, स्थिर अक्षर *caller)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	अचिन्हित दीर्घ expires;
	अचिन्हित दीर्घ start;
	पूर्णांक ret = _SUCCESS;

	expires = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);
	अगर (समय_beक्रमe(pwrpriv->ips_deny_समय, expires))
		pwrpriv->ips_deny_समय = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);

	start = jअगरfies;
	अगर (pwrpriv->ps_processing) अणु
		DBG_88E("%s wait ps_processing...\n", __func__);
		जबतक (pwrpriv->ps_processing &&
		       jअगरfies_to_msecs(jअगरfies - start) <= 3000)
			udelay(1500);
		अगर (pwrpriv->ps_processing)
			DBG_88E("%s wait ps_processing timeout\n", __func__);
		अन्यथा
			DBG_88E("%s wait ps_processing done\n", __func__);
	पूर्ण

	/* System suspend is not allowed to wakeup */
	अगर ((!pwrpriv->bInternalAutoSuspend) && (pwrpriv->bInSuspend)) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* block??? */
	अगर ((pwrpriv->bInternalAutoSuspend)  && (padapter->net_बंदd)) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* I think this should be check in IPS, LPS, स्वतःsuspend functions... */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण
	अगर (rf_off == pwrpriv->rf_pwrstate) अणु
		DBG_88E("%s call ips_leave....\n", __func__);
		अगर (ips_leave(padapter) ==  _FAIL) अणु
			DBG_88E("======> ips_leave fail.............\n");
			ret = _FAIL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* TODO: the following checking need to be merged... */
	अगर (padapter->bDriverStopped || !padapter->bup ||
	    !padapter->hw_init_completed) अणु
		DBG_88E("%s: bDriverStopped=%d, bup=%d, hw_init_completed =%u\n"
			, caller
			, padapter->bDriverStopped
			, padapter->bup
			, padapter->hw_init_completed);
		ret = false;
		जाओ निकास;
	पूर्ण

निकास:
	expires = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);
	अगर (समय_beक्रमe(pwrpriv->ips_deny_समय, expires))
		pwrpriv->ips_deny_समय = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);
	वापस ret;
पूर्ण

पूर्णांक rtw_pm_set_lps(काष्ठा adapter *padapter, u8 mode)
अणु
	पूर्णांक ret = 0;
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	अगर (mode < PS_MODE_NUM) अणु
		अगर (pwrctrlpriv->घातer_mgnt != mode) अणु
			अगर (mode == PS_MODE_ACTIVE)
				LeaveAllPowerSaveMode(padapter);
			अन्यथा
				pwrctrlpriv->LpsIdleCount = 2;
			pwrctrlpriv->घातer_mgnt = mode;
			pwrctrlpriv->bLeisurePs = (pwrctrlpriv->घातer_mgnt != PS_MODE_ACTIVE);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक rtw_pm_set_ips(काष्ठा adapter *padapter, u8 mode)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	अगर (mode == IPS_NORMAL || mode == IPS_LEVEL_2) अणु
		rtw_ips_mode_req(pwrctrlpriv, mode);
		DBG_88E("%s %s\n", __func__, mode == IPS_NORMAL ? "IPS_NORMAL" : "IPS_LEVEL_2");
		वापस 0;
	पूर्ण अन्यथा अगर (mode == IPS_NONE) अणु
		rtw_ips_mode_req(pwrctrlpriv, mode);
		DBG_88E("%s %s\n", __func__, "IPS_NONE");
		अगर ((padapter->bSurpriseRemoved == 0) && (rtw_pwr_wakeup(padapter) == _FAIL))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
