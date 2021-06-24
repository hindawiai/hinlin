<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_PWRCTRL_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>
#समावेश <linux/jअगरfies.h>


व्योम _ips_enter(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	pwrpriv->bips_processing = true;

	/*  syn ips_mode with request */
	pwrpriv->ips_mode = pwrpriv->ips_mode_req;

	pwrpriv->ips_enter_cnts++;

	अगर (rf_off == pwrpriv->change_rfpwrstate) अणु
		pwrpriv->bघातer_saving = true;

		अगर (pwrpriv->ips_mode == IPS_LEVEL_2)
			pwrpriv->bkeepfwalive = true;

		rtw_ips_pwr_करोwn(padapter);
		pwrpriv->rf_pwrstate = rf_off;
	पूर्ण
	pwrpriv->bips_processing = false;

पूर्ण

व्योम ips_enter(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);


	hal_btcoex_IpsNotअगरy(padapter, pwrpriv->ips_mode_req);

	mutex_lock(&pwrpriv->lock);
	_ips_enter(padapter);
	mutex_unlock(&pwrpriv->lock);
पूर्ण

पूर्णांक _ips_leave(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	पूर्णांक result = _SUCCESS;

	अगर ((pwrpriv->rf_pwrstate == rf_off) && (!pwrpriv->bips_processing)) अणु
		pwrpriv->bips_processing = true;
		pwrpriv->change_rfpwrstate = rf_on;
		pwrpriv->ips_leave_cnts++;

		result = rtw_ips_pwr_up(padapter);
		अगर (result == _SUCCESS) अणु
			pwrpriv->rf_pwrstate = rf_on;
		पूर्ण
		pwrpriv->bips_processing = false;

		pwrpriv->bkeepfwalive = false;
		pwrpriv->bघातer_saving = false;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक ips_leave(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	पूर्णांक ret;

	अगर (!is_primary_adapter(padapter))
		वापस _SUCCESS;

	mutex_lock(&pwrpriv->lock);
	ret = _ips_leave(padapter);
	mutex_unlock(&pwrpriv->lock);

	अगर (ret == _SUCCESS)
		hal_btcoex_IpsNotअगरy(padapter, IPS_NONE);

	वापस ret;
पूर्ण

अटल bool rtw_pwr_unassociated_idle(काष्ठा adapter *adapter)
अणु
	काष्ठा adapter *buddy = adapter->pbuddy_adapter;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा xmit_priv *pxmit_priv = &adapter->xmitpriv;

	bool ret = false;

	अगर (adapter_to_pwrctl(adapter)->bघातer_saving)
		जाओ निकास;

	अगर (समय_beक्रमe(jअगरfies, adapter_to_pwrctl(adapter)->ips_deny_समय))
		जाओ निकास;

	अगर (check_fwstate(pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR)
		|| check_fwstate(pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
		|| check_fwstate(pmlmepriv, WIFI_AP_STATE)
		|| check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
	)
		जाओ निकास;

	/* consider buddy, अगर exist */
	अगर (buddy) अणु
		काष्ठा mlme_priv *b_pmlmepriv = &(buddy->mlmepriv);

		अगर (check_fwstate(b_pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR)
			|| check_fwstate(b_pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
			|| check_fwstate(b_pmlmepriv, WIFI_AP_STATE)
			|| check_fwstate(b_pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
		)
			जाओ निकास;
	पूर्ण

	अगर (pxmit_priv->मुक्त_xmitbuf_cnt != NR_XMITBUFF ||
		pxmit_priv->मुक्त_xmit_extbuf_cnt != NR_XMIT_EXTBUFF) अणु
		netdev_dbg(adapter->pnetdev,
			   "There are some pkts to transmit\n");
		netdev_dbg(adapter->pnetdev,
			   "free_xmitbuf_cnt: %d, free_xmit_extbuf_cnt: %d\n",
			   pxmit_priv->मुक्त_xmitbuf_cnt,
			   pxmit_priv->मुक्त_xmit_extbuf_cnt);
		जाओ निकास;
	पूर्ण

	ret = true;

निकास:
	वापस ret;
पूर्ण


/*
 * ATTENTION:
 *rtw_ps_processor() करोesn't handle LPS.
 */
व्योम rtw_ps_processor(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	u32 ps_deny = 0;

	mutex_lock(&adapter_to_pwrctl(padapter)->lock);
	ps_deny = rtw_ps_deny_get(padapter);
	mutex_unlock(&adapter_to_pwrctl(padapter)->lock);
	अगर (ps_deny != 0)
		जाओ निकास;

	अगर (pwrpriv->bInSuspend) अणु/* प्रणाली suspend or स्वतःsuspend */
		pdbgpriv->dbg_ps_insuspend_cnt++;
		वापस;
	पूर्ण

	pwrpriv->ps_processing = true;

	अगर (pwrpriv->ips_mode_req == IPS_NONE)
		जाओ निकास;

	अगर (!rtw_pwr_unassociated_idle(padapter))
		जाओ निकास;

	अगर ((pwrpriv->rf_pwrstate == rf_on) && ((pwrpriv->pwr_state_check_cnts%4) == 0)) अणु
		pwrpriv->change_rfpwrstate = rf_off;
		अणु
			ips_enter(padapter);
		पूर्ण
	पूर्ण
निकास:
	pwrpriv->ps_processing = false;
पूर्ण

अटल व्योम pwr_state_check_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv =
		from_समयr(pwrctrlpriv, t, pwr_state_check_समयr);
	काष्ठा adapter *padapter = pwrctrlpriv->adapter;

	rtw_ps_cmd(padapter);
पूर्ण

व्योम traffic_check_क्रम_leave_lps(काष्ठा adapter *padapter, u8 tx, u32 tx_packets)
अणु
	अटल अचिन्हित दीर्घ start_समय;
	अटल u32 xmit_cnt;
	u8 bLeaveLPS = false;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;



	अगर (tx) अणु /* from tx */
		xmit_cnt += tx_packets;

		अगर (start_समय == 0)
			start_समय = jअगरfies;

		अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > 2000) अणु /*  2 sec == watch करोg समयr */
			अगर (xmit_cnt > 8) अणु
				अगर (adapter_to_pwrctl(padapter)->bLeisurePs
				    && (adapter_to_pwrctl(padapter)->pwr_mode != PS_MODE_ACTIVE)
				    && !(hal_btcoex_IsBtControlLps(padapter))) अणु
					bLeaveLPS = true;
				पूर्ण
			पूर्ण

			start_समय = jअगरfies;
			xmit_cnt = 0;
		पूर्ण

	पूर्ण अन्यथा अणु /*  from rx path */
		अगर (pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 4/*2*/) अणु
			अगर (adapter_to_pwrctl(padapter)->bLeisurePs
			    && (adapter_to_pwrctl(padapter)->pwr_mode != PS_MODE_ACTIVE)
			    && !(hal_btcoex_IsBtControlLps(padapter)))
				bLeaveLPS = true;
		पूर्ण
	पूर्ण

	अगर (bLeaveLPS)
		/* rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1); */
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, tx?0:1);
पूर्ण

/*
 * Description:
 *This function MUST be called under घातer lock protect
 *
 * Parameters
 *padapter
 *pslv			घातer state level, only could be PS_STATE_S0 ~ PS_STATE_S4
 *
 */
व्योम rtw_set_rpwm(काष्ठा adapter *padapter, u8 pslv)
अणु
	u8 rpwm;
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	u8 cpwm_orig;

	pslv = PS_STATE(pslv);

	अगर (!pwrpriv->brpwmसमयout) अणु
		अगर (pwrpriv->rpwm == pslv ||
		    (pwrpriv->rpwm >= PS_STATE_S2 && pslv >= PS_STATE_S2))
			वापस;

	पूर्ण

	अगर ((padapter->bSurpriseRemoved) || !(padapter->hw_init_completed)) अणु
		pwrpriv->cpwm = PS_STATE_S4;

		वापस;
	पूर्ण

	अगर (padapter->bDriverStopped) अणु
		अगर (pslv < PS_STATE_S2)
			वापस;
	पूर्ण

	rpwm = pslv | pwrpriv->tog;
	/*  only when from PS_STATE S0/S1 to S2 and higher needs ACK */
	अगर ((pwrpriv->cpwm < PS_STATE_S2) && (pslv >= PS_STATE_S2))
		rpwm |= PS_ACK;

	pwrpriv->rpwm = pslv;

	cpwm_orig = 0;
	अगर (rpwm & PS_ACK)
		rtw_hal_get_hwreg(padapter, HW_VAR_CPWM, &cpwm_orig);

	अगर (rpwm & PS_ACK)
		_set_समयr(&pwrpriv->pwr_rpwm_समयr, LPS_RPWM_WAIT_MS);
	rtw_hal_set_hwreg(padapter, HW_VAR_SET_RPWM, (u8 *)(&rpwm));

	pwrpriv->tog += 0x80;

	/*  No LPS 32K, No Ack */
	अगर (rpwm & PS_ACK) अणु
		अचिन्हित दीर्घ start_समय;
		u8 cpwm_now;
		u8 poll_cnt = 0;

		start_समय = jअगरfies;

		/*  polling cpwm */
		करो अणु
			mdelay(1);
			poll_cnt++;
			rtw_hal_get_hwreg(padapter, HW_VAR_CPWM, &cpwm_now);
			अगर ((cpwm_orig ^ cpwm_now) & 0x80) अणु
				pwrpriv->cpwm = PS_STATE_S4;
				pwrpriv->cpwm_tog = cpwm_now & PS_TOGGLE;
				अवरोध;
			पूर्ण

			अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > LPS_RPWM_WAIT_MS) अणु
				_set_समयr(&pwrpriv->pwr_rpwm_समयr, 1);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (1);
	पूर्ण अन्यथा
		pwrpriv->cpwm = pslv;
पूर्ण

अटल u8 PS_RDY_CHECK(काष्ठा adapter *padapter)
अणु
	अचिन्हित दीर्घ curr_समय, delta_समय;
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (pwrpriv->bInSuspend)
		वापस false;

	curr_समय = jअगरfies;

	delta_समय = curr_समय - pwrpriv->DelayLPSLastTimeStamp;

	अगर (delta_समय < LPS_DELAY_TIME)
		वापस false;

	अगर (check_fwstate(pmlmepriv, WIFI_SITE_MONITOR)
		|| check_fwstate(pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
		|| check_fwstate(pmlmepriv, WIFI_AP_STATE)
		|| check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
		|| rtw_is_scan_deny(padapter)
	)
		वापस false;

	अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X &&
	    !padapter->securitypriv.binstallGrpkey)
		वापस false;

	अगर (!rtw_cfg80211_pwr_mgmt(padapter))
		वापस false;

	वापस true;
पूर्ण

व्योम rtw_set_ps_mode(काष्ठा adapter *padapter, u8 ps_mode, u8 smart_ps, u8 bcn_ant_mode, स्थिर अक्षर *msg)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	अगर (ps_mode > PM_Card_Disable)
		वापस;

	अगर (pwrpriv->pwr_mode == ps_mode)
		अगर (ps_mode == PS_MODE_ACTIVE)
			वापस;


	mutex_lock(&pwrpriv->lock);

	/* अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE) */
	अगर (ps_mode == PS_MODE_ACTIVE) अणु
		अगर (!(hal_btcoex_IsBtControlLps(padapter))
				|| (hal_btcoex_IsBtControlLps(padapter)
					&& !(hal_btcoex_IsLpsOn(padapter)))) अणु
			pwrpriv->pwr_mode = ps_mode;
			rtw_set_rpwm(padapter, PS_STATE_S4);

			rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));
			pwrpriv->fw_current_in_ps_mode = false;

			hal_btcoex_LpsNotअगरy(padapter, ps_mode);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((PS_RDY_CHECK(padapter) && check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE)) ||
		    ((hal_btcoex_IsBtControlLps(padapter)) && (hal_btcoex_IsLpsOn(padapter)))
			) अणु
			u8 pslv;

			hal_btcoex_LpsNotअगरy(padapter, ps_mode);

			pwrpriv->fw_current_in_ps_mode = true;
			pwrpriv->pwr_mode = ps_mode;
			pwrpriv->smart_ps = smart_ps;
			pwrpriv->bcn_ant_mode = bcn_ant_mode;
			rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_PWRMODE, (u8 *)(&ps_mode));

			pslv = PS_STATE_S2;
			अगर (pwrpriv->alives == 0)
				pslv = PS_STATE_S0;

			अगर (!(hal_btcoex_IsBtDisabled(padapter)) &&
			    (hal_btcoex_IsBtControlLps(padapter))) अणु
				u8 val8;

				val8 = hal_btcoex_LpsVal(padapter);
				अगर (val8 & BIT(4))
					pslv = PS_STATE_S2;
			पूर्ण

			rtw_set_rpwm(padapter, pslv);
		पूर्ण
	पूर्ण

	mutex_unlock(&pwrpriv->lock);
पूर्ण

/*
 * Return:
 *0:	Leave OK
 *-1:	Timeout
 *-2:	Other error
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
			अवरोध;
		पूर्ण

		अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > delay_ms) अणु
			err = -1;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस err;
पूर्ण

/*  */
/* 	Description: */
/* 		Enter the leisure घातer save mode. */
/*  */
व्योम LPS_Enter(काष्ठा adapter *padapter, स्थिर अक्षर *msg)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	काष्ठा pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(dvobj);
	पूर्णांक n_assoc_अगरace = 0;
	अक्षर buf[32] = अणु0पूर्ण;

	अगर (hal_btcoex_IsBtControlLps(padapter))
		वापस;

	/* Skip lps enter request अगर number of assocated adapters is not 1 */
	अगर (check_fwstate(&(dvobj->padapters->mlmepriv), WIFI_ASOC_STATE))
		n_assoc_अगरace++;
	अगर (n_assoc_अगरace != 1)
		वापस;

	/* Skip lps enter request क्रम adapter not port0 */
	अगर (get_अगरace_type(padapter) != IFACE_PORT0)
		वापस;

	अगर (!PS_RDY_CHECK(dvobj->padapters))
		वापस;

	अगर (pwrpriv->bLeisurePs) अणु
		/*  Idle क्रम a जबतक अगर we connect to AP a जबतक ago. */
		अगर (pwrpriv->LpsIdleCount >= 2) अणु /*   4 Sec */
			अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE) अणु
				scnम_लिखो(buf, माप(buf), "WIFI-%s", msg);
				pwrpriv->bघातer_saving = true;
				rtw_set_ps_mode(padapter, pwrpriv->घातer_mgnt, padapter->registrypriv.smart_ps, 0, buf);
			पूर्ण
		पूर्ण अन्यथा
			pwrpriv->LpsIdleCount++;
	पूर्ण
पूर्ण

/*  */
/* 	Description: */
/* 		Leave the leisure घातer save mode. */
/*  */
व्योम LPS_Leave(काष्ठा adapter *padapter, स्थिर अक्षर *msg)
अणु
#घोषणा LPS_LEAVE_TIMEOUT_MS 100

	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	काष्ठा pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(dvobj);
	अक्षर buf[32] = अणु0पूर्ण;

	अगर (hal_btcoex_IsBtControlLps(padapter))
		वापस;

	अगर (pwrpriv->bLeisurePs) अणु
		अगर (pwrpriv->pwr_mode != PS_MODE_ACTIVE) अणु
			scnम_लिखो(buf, माप(buf), "WIFI-%s", msg);
			rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0, buf);

			अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
				LPS_RF_ON_check(padapter, LPS_LEAVE_TIMEOUT_MS);
		पूर्ण
	पूर्ण

	pwrpriv->bघातer_saving = false;
पूर्ण

व्योम LeaveAllPowerSaveModeDirect(काष्ठा adapter *Adapter)
अणु
	काष्ठा adapter *pri_padapter = GET_PRIMARY_ADAPTER(Adapter);
	काष्ठा mlme_priv *pmlmepriv = &(Adapter->mlmepriv);
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(Adapter);

	अगर (Adapter->bSurpriseRemoved)
		वापस;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु /* connect */

		अगर (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
			वापस;

		mutex_lock(&pwrpriv->lock);

		rtw_set_rpwm(Adapter, PS_STATE_S4);

		mutex_unlock(&pwrpriv->lock);

		rtw_lps_ctrl_wk_cmd(pri_padapter, LPS_CTRL_LEAVE, 0);
	पूर्ण अन्यथा अणु
		अगर (pwrpriv->rf_pwrstate == rf_off)
			ips_leave(pri_padapter);
	पूर्ण
पूर्ण

/*  */
/*  Description: Leave all घातer save mode: LPS, FwLPS, IPS अगर needed. */
/*  Move code to function by tynli. 2010.03.26. */
/*  */
व्योम LeaveAllPowerSaveMode(काष्ठा adapter *Adapter)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(Adapter);
	u8 enqueue = 0;
	पूर्णांक n_assoc_अगरace = 0;

	अगर (!Adapter->bup)
		वापस;

	अगर (Adapter->bSurpriseRemoved)
		वापस;

	अगर (check_fwstate(&(dvobj->padapters->mlmepriv), WIFI_ASOC_STATE))
		n_assoc_अगरace++;

	अगर (n_assoc_अगरace) अणु /* connect */
		enqueue = 1;

		rtw_lps_ctrl_wk_cmd(Adapter, LPS_CTRL_LEAVE, enqueue);

		LPS_Leave_check(Adapter);
	पूर्ण अन्यथा अणु
		अगर (adapter_to_pwrctl(Adapter)->rf_pwrstate == rf_off) अणु
			ips_leave(Adapter);
		पूर्ण
	पूर्ण
पूर्ण

व्योम LPS_Leave_check(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;
	अचिन्हित दीर्घ	start_समय;
	u8 bReady;

	pwrpriv = adapter_to_pwrctl(padapter);

	bReady = false;
	start_समय = jअगरfies;

	cond_resched();

	जबतक (1) अणु
		mutex_lock(&pwrpriv->lock);

		अगर (padapter->bSurpriseRemoved ||
		    !(padapter->hw_init_completed) ||
		    (pwrpriv->pwr_mode == PS_MODE_ACTIVE))
			bReady = true;

		mutex_unlock(&pwrpriv->lock);

		अगर (bReady)
			अवरोध;

		अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > 100)
			अवरोध;

		msleep(1);
	पूर्ण
पूर्ण

/*
 * Caller:ISR handler...
 *
 * This will be called when CPWM पूर्णांकerrupt is up.
 *
 * using to update cpwn of drv; and drv willl make a decision to up or करोwn pwr level
 */
व्योम cpwm_पूर्णांक_hdl(काष्ठा adapter *padapter, काष्ठा reportpwrstate_parm *preportpwrstate)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;

	pwrpriv = adapter_to_pwrctl(padapter);

	mutex_lock(&pwrpriv->lock);

	अगर (pwrpriv->rpwm < PS_STATE_S2)
		जाओ निकास;

	pwrpriv->cpwm = PS_STATE(preportpwrstate->state);
	pwrpriv->cpwm_tog = preportpwrstate->state & PS_TOGGLE;

	अगर (pwrpriv->cpwm >= PS_STATE_S2) अणु
		अगर (pwrpriv->alives & CMD_ALIVE)
			complete(&padapter->cmdpriv.cmd_queue_comp);

		अगर (pwrpriv->alives & XMIT_ALIVE)
			complete(&padapter->xmitpriv.xmit_comp);
	पूर्ण

निकास:
	mutex_unlock(&pwrpriv->lock);

पूर्ण

अटल व्योम cpwm_event_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = container_of(work, काष्ठा pwrctrl_priv, cpwm_event);
	काष्ठा dvobj_priv *dvobj = pwrctl_to_dvobj(pwrpriv);
	काष्ठा adapter *adapter = dvobj->अगर1;
	काष्ठा reportpwrstate_parm report;

	report.state = PS_STATE_S2;
	cpwm_पूर्णांक_hdl(adapter, &report);
पूर्ण

अटल व्योम rpwmसमयout_workitem_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *dvobj;
	काष्ठा pwrctrl_priv *pwrpriv;


	pwrpriv = container_of(work, काष्ठा pwrctrl_priv, rpwmसमयoutwi);
	dvobj = pwrctl_to_dvobj(pwrpriv);
	padapter = dvobj->अगर1;

	mutex_lock(&pwrpriv->lock);
	अगर ((pwrpriv->rpwm == pwrpriv->cpwm) || (pwrpriv->cpwm >= PS_STATE_S2))
		जाओ निकास;

	mutex_unlock(&pwrpriv->lock);

	अगर (rtw_पढ़ो8(padapter, 0x100) != 0xEA) अणु
		काष्ठा reportpwrstate_parm report;

		report.state = PS_STATE_S2;
		cpwm_पूर्णांक_hdl(padapter, &report);

		वापस;
	पूर्ण

	mutex_lock(&pwrpriv->lock);

	अगर ((pwrpriv->rpwm == pwrpriv->cpwm) || (pwrpriv->cpwm >= PS_STATE_S2))
		जाओ निकास;

	pwrpriv->brpwmसमयout = true;
	rtw_set_rpwm(padapter, pwrpriv->rpwm);
	pwrpriv->brpwmसमयout = false;

निकास:
	mutex_unlock(&pwrpriv->lock);
पूर्ण

/*
 * This function is a समयr handler, can't करो any IO in it.
 */
अटल व्योम pwr_rpwm_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = from_समयr(pwrpriv, t, pwr_rpwm_समयr);

	अगर ((pwrpriv->rpwm == pwrpriv->cpwm) || (pwrpriv->cpwm >= PS_STATE_S2))
		वापस;

	_set_workitem(&pwrpriv->rpwmसमयoutwi);
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_task_alive(काष्ठा pwrctrl_priv *pwrctrl, u32 tag)
अणु
	pwrctrl->alives |= tag;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_task_alive(काष्ठा pwrctrl_priv *pwrctrl, u32 tag)
अणु
	pwrctrl->alives &= ~tag;
पूर्ण


/*
 * Description:
 *Check अगर the fw_pwrstate is okay क्रम I/O.
 *If not (cpwm is less than S2), then the sub-routine
 *will उठाओ the cpwm to be greater than or equal to S2.
 *
 *Calling Context: Passive
 *
 *Constraपूर्णांक:
 *	1. this function will request pwrctrl->lock
 *
 * Return Value:
 *_SUCCESS	hardware is पढ़ोy क्रम I/O
 *_FAIL		can't I/O right now
 */
s32 rtw_रेजिस्टर_task_alive(काष्ठा adapter *padapter, u32 task)
अणु
	s32 res;
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	res = _SUCCESS;
	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S2;

	mutex_lock(&pwrctrl->lock);

	रेजिस्टर_task_alive(pwrctrl, task);

	अगर (pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm < pslv) अणु
			अगर (pwrctrl->cpwm < PS_STATE_S2)
				res = _FAIL;
			अगर (pwrctrl->rpwm < pslv)
				rtw_set_rpwm(padapter, pslv);
		पूर्ण
	पूर्ण

	mutex_unlock(&pwrctrl->lock);

	अगर (res == _FAIL)
		अगर (pwrctrl->cpwm >= PS_STATE_S2)
			res = _SUCCESS;

	वापस res;
पूर्ण

/*
 * Description:
 *If task is करोne, call this func. to घातer करोwn firmware again.
 *
 *Constraपूर्णांक:
 *	1. this function will request pwrctrl->lock
 *
 * Return Value:
 *none
 */
व्योम rtw_unरेजिस्टर_task_alive(काष्ठा adapter *padapter, u32 task)
अणु
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S0;

	अगर (!(hal_btcoex_IsBtDisabled(padapter)) && hal_btcoex_IsBtControlLps(padapter)) अणु
		u8 val8;

		val8 = hal_btcoex_LpsVal(padapter);
		अगर (val8 & BIT(4))
			pslv = PS_STATE_S2;
	पूर्ण

	mutex_lock(&pwrctrl->lock);

	unरेजिस्टर_task_alive(pwrctrl, task);

	अगर ((pwrctrl->pwr_mode != PS_MODE_ACTIVE) && pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm > pslv)
			अगर ((pslv >= PS_STATE_S2) || (pwrctrl->alives == 0))
				rtw_set_rpwm(padapter, pslv);

	पूर्ण

	mutex_unlock(&pwrctrl->lock);
पूर्ण

/*
 * Caller: rtw_xmit_thपढ़ो
 *
 * Check अगर the fw_pwrstate is okay क्रम xmit.
 * If not (cpwm is less than S3), then the sub-routine
 * will उठाओ the cpwm to be greater than or equal to S3.
 *
 * Calling Context: Passive
 *
 * Return Value:
 * _SUCCESS	rtw_xmit_thपढ़ो can ग_लिखो fअगरo/txcmd afterwards.
 * _FAIL		rtw_xmit_thपढ़ो can not करो anything.
 */
s32 rtw_रेजिस्टर_tx_alive(काष्ठा adapter *padapter)
अणु
	s32 res;
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	res = _SUCCESS;
	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S2;

	mutex_lock(&pwrctrl->lock);

	रेजिस्टर_task_alive(pwrctrl, XMIT_ALIVE);

	अगर (pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm < pslv) अणु
			अगर (pwrctrl->cpwm < PS_STATE_S2)
				res = _FAIL;
			अगर (pwrctrl->rpwm < pslv)
				rtw_set_rpwm(padapter, pslv);
		पूर्ण
	पूर्ण

	mutex_unlock(&pwrctrl->lock);

	अगर (res == _FAIL)
		अगर (pwrctrl->cpwm >= PS_STATE_S2)
			res = _SUCCESS;

	वापस res;
पूर्ण

/*
 * Caller: rtw_cmd_thपढ़ो
 *
 * Check अगर the fw_pwrstate is okay क्रम issuing cmd.
 * If not (cpwm should be is less than S2), then the sub-routine
 * will उठाओ the cpwm to be greater than or equal to S2.
 *
 * Calling Context: Passive
 *
 * Return Value:
 *_SUCCESS	rtw_cmd_thपढ़ो can issue cmds to firmware afterwards.
 *_FAIL		rtw_cmd_thपढ़ो can not करो anything.
 */
s32 rtw_रेजिस्टर_cmd_alive(काष्ठा adapter *padapter)
अणु
	s32 res;
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	res = _SUCCESS;
	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S2;

	mutex_lock(&pwrctrl->lock);

	रेजिस्टर_task_alive(pwrctrl, CMD_ALIVE);

	अगर (pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm < pslv) अणु
			अगर (pwrctrl->cpwm < PS_STATE_S2)
				res = _FAIL;
			अगर (pwrctrl->rpwm < pslv)
				rtw_set_rpwm(padapter, pslv);
		पूर्ण
	पूर्ण

	mutex_unlock(&pwrctrl->lock);

	अगर (res == _FAIL)
		अगर (pwrctrl->cpwm >= PS_STATE_S2)
			res = _SUCCESS;

	वापस res;
पूर्ण

/*
 * Caller: ISR
 *
 * If ISR's txकरोne,
 * No more pkts क्रम TX,
 * Then driver shall call this fun. to घातer करोwn firmware again.
 */
व्योम rtw_unरेजिस्टर_tx_alive(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S0;

	अगर (!(hal_btcoex_IsBtDisabled(padapter)) && hal_btcoex_IsBtControlLps(padapter)) अणु
		u8 val8;

		val8 = hal_btcoex_LpsVal(padapter);
		अगर (val8 & BIT(4))
			pslv = PS_STATE_S2;
	पूर्ण

	mutex_lock(&pwrctrl->lock);

	unरेजिस्टर_task_alive(pwrctrl, XMIT_ALIVE);

	अगर ((pwrctrl->pwr_mode != PS_MODE_ACTIVE) && pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm > pslv)
			अगर ((pslv >= PS_STATE_S2) || (pwrctrl->alives == 0))
				rtw_set_rpwm(padapter, pslv);
	पूर्ण

	mutex_unlock(&pwrctrl->lock);
पूर्ण

/*
 * Caller: ISR
 *
 * If all commands have been करोne,
 * and no more command to करो,
 * then driver shall call this fun. to घातer करोwn firmware again.
 */
व्योम rtw_unरेजिस्टर_cmd_alive(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrl;
	u8 pslv;

	pwrctrl = adapter_to_pwrctl(padapter);
	pslv = PS_STATE_S0;

	अगर (!(hal_btcoex_IsBtDisabled(padapter)) && hal_btcoex_IsBtControlLps(padapter)) अणु
		u8 val8;

		val8 = hal_btcoex_LpsVal(padapter);
		अगर (val8 & BIT(4))
			pslv = PS_STATE_S2;
	पूर्ण

	mutex_lock(&pwrctrl->lock);

	unरेजिस्टर_task_alive(pwrctrl, CMD_ALIVE);

	अगर ((pwrctrl->pwr_mode != PS_MODE_ACTIVE) && pwrctrl->fw_current_in_ps_mode) अणु
		अगर (pwrctrl->cpwm > pslv) अणु
			अगर ((pslv >= PS_STATE_S2) || (pwrctrl->alives == 0))
				rtw_set_rpwm(padapter, pslv);
		पूर्ण
	पूर्ण

	mutex_unlock(&pwrctrl->lock);
पूर्ण

व्योम rtw_init_pwrctrl_priv(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	mutex_init(&pwrctrlpriv->lock);
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
	pwrctrlpriv->घातer_mgnt = padapter->registrypriv.घातer_mgnt;/*  PS_MODE_MIN; */
	pwrctrlpriv->bLeisurePs = pwrctrlpriv->घातer_mgnt != PS_MODE_ACTIVE;

	pwrctrlpriv->fw_current_in_ps_mode = false;

	pwrctrlpriv->rpwm = 0;
	pwrctrlpriv->cpwm = PS_STATE_S4;

	pwrctrlpriv->pwr_mode = PS_MODE_ACTIVE;
	pwrctrlpriv->smart_ps = padapter->registrypriv.smart_ps;
	pwrctrlpriv->bcn_ant_mode = 0;
	pwrctrlpriv->dtim = 0;

	pwrctrlpriv->tog = 0x80;

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_RPWM, (u8 *)(&pwrctrlpriv->rpwm));

	_init_workitem(&pwrctrlpriv->cpwm_event, cpwm_event_callback, शून्य);

	pwrctrlpriv->brpwmसमयout = false;
	pwrctrlpriv->adapter = padapter;
	_init_workitem(&pwrctrlpriv->rpwmसमयoutwi, rpwmसमयout_workitem_callback, शून्य);
	समयr_setup(&pwrctrlpriv->pwr_rpwm_समयr, pwr_rpwm_समयout_handler, 0);
	समयr_setup(&pwrctrlpriv->pwr_state_check_समयr,
		    pwr_state_check_handler, 0);

	pwrctrlpriv->wowlan_mode = false;
	pwrctrlpriv->wowlan_ap_mode = false;
पूर्ण


व्योम rtw_मुक्त_pwrctrl_priv(काष्ठा adapter *adapter)
अणु
पूर्ण

अंतरभूत व्योम rtw_set_ips_deny(काष्ठा adapter *padapter, u32 ms)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	pwrpriv->ips_deny_समय = jअगरfies + msecs_to_jअगरfies(ms);
पूर्ण

/*
* rtw_pwr_wakeup - Wake the NIC up from: 1)IPS. 2)USB स्वतःsuspend
* @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
* @ips_deffer_ms: the ms will prevent from falling पूर्णांकo IPS after wakeup
* Return _SUCCESS or _FAIL
*/

पूर्णांक _rtw_pwr_wakeup(काष्ठा adapter *padapter, u32 ips_deffer_ms, स्थिर अक्षर *caller)
अणु
	काष्ठा dvobj_priv *dvobj = adapter_to_dvobj(padapter);
	काष्ठा pwrctrl_priv *pwrpriv = dvobj_to_pwrctl(dvobj);
	काष्ठा mlme_priv *pmlmepriv;
	पूर्णांक ret = _SUCCESS;
	अचिन्हित दीर्घ start = jअगरfies;
	अचिन्हित दीर्घ deny_समय = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);

	/* क्रम LPS */
	LeaveAllPowerSaveMode(padapter);

	/* IPS still bound with primary adapter */
	padapter = GET_PRIMARY_ADAPTER(padapter);
	pmlmepriv = &padapter->mlmepriv;

	अगर (समय_beक्रमe(pwrpriv->ips_deny_समय, deny_समय))
		pwrpriv->ips_deny_समय = deny_समय;


	अगर (pwrpriv->ps_processing)
		जबतक (pwrpriv->ps_processing && jअगरfies_to_msecs(jअगरfies - start) <= 3000)
			mdelay(10);

	अगर (!(pwrpriv->bInternalAutoSuspend) && pwrpriv->bInSuspend)
		जबतक (pwrpriv->bInSuspend && jअगरfies_to_msecs(jअगरfies - start) <= 3000
		)
			mdelay(10);

	/* System suspend is not allowed to wakeup */
	अगर (!(pwrpriv->bInternalAutoSuspend) && pwrpriv->bInSuspend) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* block??? */
	अगर (pwrpriv->bInternalAutoSuspend  && padapter->net_बंदd) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* I think this should be check in IPS, LPS, स्वतःsuspend functions... */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		ret = _SUCCESS;
		जाओ निकास;
	पूर्ण

	अगर (rf_off == pwrpriv->rf_pwrstate) अणु
		अणु
			अगर (ips_leave(padapter) == _FAIL) अणु
				ret = _FAIL;
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	/* TODO: the following checking need to be merged... */
	अगर (padapter->bDriverStopped || !padapter->bup || !padapter->hw_init_completed) अणु
		ret = false;
		जाओ निकास;
	पूर्ण

निकास:
	deny_समय = jअगरfies + msecs_to_jअगरfies(ips_deffer_ms);
	अगर (समय_beक्रमe(pwrpriv->ips_deny_समय, deny_समय))
		pwrpriv->ips_deny_समय = deny_समय;
	वापस ret;

पूर्ण

पूर्णांक rtw_pm_set_lps(काष्ठा adapter *padapter, u8 mode)
अणु
	पूर्णांक	ret = 0;
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	अगर (mode < PS_MODE_NUM) अणु
		अगर (pwrctrlpriv->घातer_mgnt != mode) अणु
			अगर (mode == PS_MODE_ACTIVE)
				LeaveAllPowerSaveMode(padapter);
			अन्यथा
				pwrctrlpriv->LpsIdleCount = 2;

			pwrctrlpriv->घातer_mgnt = mode;
			pwrctrlpriv->bLeisurePs =
				pwrctrlpriv->घातer_mgnt != PS_MODE_ACTIVE;
		पूर्ण
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

पूर्णांक rtw_pm_set_ips(काष्ठा adapter *padapter, u8 mode)
अणु
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(padapter);

	अगर (mode == IPS_NORMAL || mode == IPS_LEVEL_2) अणु
		rtw_ips_mode_req(pwrctrlpriv, mode);
		वापस 0;
	पूर्ण अन्यथा अगर (mode == IPS_NONE) अणु
		rtw_ips_mode_req(pwrctrlpriv, mode);
		अगर ((padapter->bSurpriseRemoved == 0) && (rtw_pwr_wakeup(padapter) == _FAIL))
			वापस -EFAULT;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * ATTENTION:
 *This function will request pwrctrl LOCK!
 */
व्योम rtw_ps_deny(काष्ठा adapter *padapter, क्रमागत ps_deny_reason reason)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;

	pwrpriv = adapter_to_pwrctl(padapter);

	mutex_lock(&pwrpriv->lock);
	pwrpriv->ps_deny |= BIT(reason);
	mutex_unlock(&pwrpriv->lock);
पूर्ण

/*
 * ATTENTION:
 *This function will request pwrctrl LOCK!
 */
व्योम rtw_ps_deny_cancel(काष्ठा adapter *padapter, क्रमागत ps_deny_reason reason)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;

	pwrpriv = adapter_to_pwrctl(padapter);

	mutex_lock(&pwrpriv->lock);
	pwrpriv->ps_deny &= ~BIT(reason);
	mutex_unlock(&pwrpriv->lock);
पूर्ण

/*
 * ATTENTION:
 *Beक्रमe calling this function pwrctrl lock should be occupied alपढ़ोy,
 *otherwise it may वापस incorrect value.
 */
u32 rtw_ps_deny_get(काष्ठा adapter *padapter)
अणु
	वापस adapter_to_pwrctl(padapter)->ps_deny;
पूर्ण
