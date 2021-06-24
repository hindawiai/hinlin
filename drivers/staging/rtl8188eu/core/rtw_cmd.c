<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <mlme_osdep.h>
#समावेश <rtw_mlme_ext.h>

अटल काष्ठा cmd_hdl wlancmds[] = अणु
	अणुमाप(काष्ठा wlan_bssid_ex), join_cmd_hdlपूर्ण,
	अणुमाप(काष्ठा disconnect_parm), disconnect_hdlपूर्ण,
	अणुमाप(काष्ठा wlan_bssid_ex), createbss_hdlपूर्ण,
	अणुमाप(काष्ठा setopmode_parm), setopmode_hdlपूर्ण,
	अणुमाप(काष्ठा sitesurvey_parm), sitesurvey_cmd_hdlपूर्ण,
	अणुमाप(काष्ठा setauth_parm), setauth_hdlपूर्ण,
	अणुमाप(काष्ठा setkey_parm), setkey_hdlपूर्ण,
	अणुमाप(काष्ठा set_stakey_parm), set_stakey_hdlपूर्ण,
	अणुमाप(काष्ठा set_assocsta_parm), शून्यपूर्ण,
	अणुमाप(काष्ठा addBaReq_parm), add_ba_hdlपूर्ण,
	अणुमाप(काष्ठा set_ch_parm), set_ch_hdlपूर्ण,
	अणुमाप(काष्ठा wlan_bssid_ex), tx_beacon_hdlपूर्ण,
	अणु0, mlme_evt_hdlपूर्ण,
	अणु0, rtw_drvextra_cmd_hdlपूर्ण,
	अणुमाप(काष्ठा SetChannelPlan_param), set_chplan_hdlपूर्ण
पूर्ण;

अटल काष्ठा _cmd_callback rtw_cmd_callback[] = अणु
	अणु_JoinBss_CMD_, &rtw_joinbss_cmd_callbackपूर्ण,
	अणु_DisConnect_CMD_, &rtw_disassoc_cmd_callbackपूर्ण,
	अणु_CreateBss_CMD_, &rtw_createbss_cmd_callbackपूर्ण,
	अणु_SetOpMode_CMD_, शून्यपूर्ण,
	अणु_SiteSurvey_CMD_, &rtw_survey_cmd_callbackपूर्ण,
	अणु_SetAuth_CMD_, शून्यपूर्ण,
	अणु_SetKey_CMD_, शून्यपूर्ण,
	अणु_SetStaKey_CMD_, &rtw_setstaKey_cmdrsp_callbackपूर्ण,
	अणु_SetAssocSta_CMD_, &rtw_setassocsta_cmdrsp_callbackपूर्ण,
	अणु_AddBAReq_CMD_, शून्यपूर्ण,
	अणु_SetChannel_CMD_, शून्यपूर्ण,
	अणु_TX_Beacon_CMD_, शून्यपूर्ण,
	अणु_Set_MLME_EVT_CMD_, शून्यपूर्ण,
	अणु_Set_Drv_Extra_CMD_, शून्यपूर्ण,
	अणु_SetChannelPlan_CMD_, शून्यपूर्ण,
पूर्ण;

/*
 * Caller and the rtw_cmd_thपढ़ो can protect cmd_q by spin_lock.
 * No irqsave is necessary.
 */

पूर्णांक rtw_init_cmd_priv(काष्ठा cmd_priv *pcmdpriv)
अणु
	init_completion(&pcmdpriv->cmd_queue_comp);
	init_completion(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	_rtw_init_queue(&pcmdpriv->cmd_queue);
	वापस _SUCCESS;
पूर्ण

/*
 * Calling Context:
 *
 * rtw_enqueue_cmd can only be called between kernel thपढ़ो,
 * since only spin_lock is used.
 *
 * ISR/Call-Back functions can't call this sub-function.
 */

अटल पूर्णांक _rtw_enqueue_cmd(काष्ठा __queue *queue, काष्ठा cmd_obj *obj)
अणु
	अचिन्हित दीर्घ irqL;

	अगर (!obj)
		जाओ निकास;

	spin_lock_irqsave(&queue->lock, irqL);

	list_add_tail(&obj->list, &queue->queue);

	spin_unlock_irqrestore(&queue->lock, irqL);

निकास:

	वापस _SUCCESS;
पूर्ण

काष्ठा cmd_obj *rtw_dequeue_cmd(काष्ठा __queue *queue)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा cmd_obj *obj;

	spin_lock_irqsave(&queue->lock, irqL);
	obj = list_first_entry_or_null(&queue->queue, काष्ठा cmd_obj, list);
	अगर (obj)
		list_del_init(&obj->list);
	spin_unlock_irqrestore(&queue->lock, irqL);

	वापस obj;
पूर्ण

अटल पूर्णांक rtw_cmd_filter(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *cmd_obj)
अणु
	u8 bAllow = false; /* set to true to allow enqueuing cmd when hw_init_completed is false */

	/* To decide allow or not */
	अगर ((pcmdpriv->padapter->pwrctrlpriv.bHWPwrPindetect) &&
	    (!pcmdpriv->padapter->registrypriv.usbss_enable)) अणु
		अगर (cmd_obj->cmdcode == _Set_Drv_Extra_CMD_) अणु
			काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm = (काष्ठा drvextra_cmd_parm	*)cmd_obj->parmbuf;

			अगर (pdrvextra_cmd_parm->ec_id == POWER_SAVING_CTRL_WK_CID)
				bAllow = true;
		पूर्ण
	पूर्ण

	अगर (cmd_obj->cmdcode == _SetChannelPlan_CMD_)
		bAllow = true;

	अगर ((!pcmdpriv->padapter->hw_init_completed && !bAllow) ||
	    !pcmdpriv->cmdthd_running)	/* com_thपढ़ो not running */
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

u32 rtw_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *cmd_obj)
अणु
	पूर्णांक res = _FAIL;
	काष्ठा adapter *padapter = pcmdpriv->padapter;

	अगर (!cmd_obj)
		जाओ निकास;

	cmd_obj->padapter = padapter;

	res = rtw_cmd_filter(pcmdpriv, cmd_obj);
	अगर (res == _FAIL) अणु
		rtw_मुक्त_cmd_obj(cmd_obj);
		जाओ निकास;
	पूर्ण

	res = _rtw_enqueue_cmd(&pcmdpriv->cmd_queue, cmd_obj);

	अगर (res == _SUCCESS)
		complete(&pcmdpriv->cmd_queue_comp);

निकास:

	वापस res;
पूर्ण

व्योम rtw_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd)
अणु
	अगर ((pcmd->cmdcode != _JoinBss_CMD_) && (pcmd->cmdcode != _CreateBss_CMD_)) अणु
		/* मुक्त parmbuf in cmd_obj */
		kमुक्त(pcmd->parmbuf);
	पूर्ण

	अगर (pcmd->rsp) अणु
		अगर (pcmd->rspsz != 0) अणु
			/* मुक्त rsp in cmd_obj */
			kमुक्त(pcmd->rsp);
		पूर्ण
	पूर्ण

	/* मुक्त cmd_obj */
	kमुक्त(pcmd);
पूर्ण

पूर्णांक rtw_cmd_thपढ़ो(व्योम *context)
अणु
	u8 ret;
	काष्ठा cmd_obj *pcmd;
	u8 (*cmd_hdl)(काष्ठा adapter *padapter, u8 *pbuf);
	व्योम (*pcmd_callback)(काष्ठा adapter *dev, काष्ठा cmd_obj *pcmd);
	काष्ठा adapter *padapter = context;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	allow_संकेत(संक_इति);

	pcmdpriv->cmdthd_running = true;
	complete(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_,
		 ("start r871x %s !!!!\n", __func__));

	जबतक (1) अणु
		अगर (padapter->bDriverStopped ||
		    padapter->bSurpriseRemoved) अणु
			DBG_88E("%s: DriverStopped(%d) SurpriseRemoved(%d) break at line %d\n",
				__func__, padapter->bDriverStopped,
				padapter->bSurpriseRemoved, __LINE__);
			अवरोध;
		पूर्ण

		pcmd = rtw_dequeue_cmd(&pcmdpriv->cmd_queue);
		अगर (!pcmd) अणु
			/* The queue is empty. Wait until someone enqueues a command. */
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(&pcmdpriv->cmd_queue_comp))
				अवरोध;

			जारी;
		पूर्ण

		अगर (rtw_cmd_filter(pcmdpriv, pcmd) == _FAIL) अणु
			pcmd->res = H2C_DROPPED;
		पूर्ण अन्यथा अणु
			अगर (pcmd->cmdcode < ARRAY_SIZE(wlancmds)) अणु
				cmd_hdl = wlancmds[pcmd->cmdcode].h2cfuns;

				अगर (cmd_hdl) अणु
					ret = cmd_hdl(pcmd->padapter, pcmd->parmbuf);
					pcmd->res = ret;
				पूर्ण
			पूर्ण अन्यथा अणु
				pcmd->res = H2C_PARAMETERS_ERROR;
			पूर्ण
		पूर्ण

		/* call callback function क्रम post-processed */
		अगर (pcmd->cmdcode < ARRAY_SIZE(rtw_cmd_callback)) अणु
			pcmd_callback = rtw_cmd_callback[pcmd->cmdcode].callback;
			अगर (!pcmd_callback) अणु
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_,
					 ("mlme_cmd_hdl(): pcmd_callback = 0x%p, cmdcode = 0x%x\n",
					  pcmd_callback, pcmd->cmdcode));
			पूर्ण अन्यथा अणु
				/* toकरो: !!! fill rsp_buf to pcmd->rsp अगर (pcmd->rsp!= शून्य) */
				pcmd_callback(pcmd->padapter, pcmd);
			पूर्ण
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
				 ("%s: cmdcode = 0x%x callback not defined!\n",
				  __func__, pcmd->cmdcode));
		पूर्ण
		rtw_मुक्त_cmd_obj(pcmd);

		अगर (संकेत_pending(current))
			flush_संकेतs(current);
	पूर्ण
	pcmdpriv->cmdthd_running = false;

	/*  मुक्त all cmd_obj resources */
	जबतक ((pcmd = rtw_dequeue_cmd(&pcmdpriv->cmd_queue)))
		rtw_मुक्त_cmd_obj(pcmd);

	complete(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	complete_and_निकास(शून्य, 0);
पूर्ण

/*
 * rtw_sitesurvey_cmd(~)
 * ### NOTE:#### (!!!!)
 * MUST TAKE CARE THAT BEFORE CALLING THIS FUNC, YOU SHOULD HAVE
 * LOCKED pmlmepriv->lock
 */
u8 rtw_sitesurvey_cmd(काष्ठा adapter  *padapter, काष्ठा ndis_802_11_ssid *ssid, पूर्णांक ssid_num,
		      काष्ठा rtw_ieee80211_channel *ch, पूर्णांक ch_num)
अणु
	u8 res = _FAIL;
	काष्ठा cmd_obj		*ph2c;
	काष्ठा sitesurvey_parm	*psurveyPara;
	काष्ठा cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED))
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_SCAN, 1);

	ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस _FAIL;

	psurveyPara = kzalloc(माप(*psurveyPara), GFP_ATOMIC);
	अगर (!psurveyPara) अणु
		kमुक्त(ph2c);
		वापस _FAIL;
	पूर्ण

	rtw_मुक्त_network_queue(padapter, false);

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_, ("%s: flush network queue\n", __func__));

	init_h2fwcmd_w_parm_no_rsp(ph2c, psurveyPara, _SiteSurvey_CMD_);

	psurveyPara->scan_mode = pmlmepriv->scan_mode;

	/* prepare ssid list */
	अगर (ssid) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ssid_num && i < RTW_SSID_SCAN_AMOUNT; i++) अणु
			अगर (ssid[i].ssid_length) अणु
				स_नकल(&psurveyPara->ssid[i], &ssid[i],
				       माप(काष्ठा ndis_802_11_ssid));
				psurveyPara->ssid_num++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* prepare channel list */
	अगर (ch) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ch_num && i < RTW_CHANNEL_SCAN_AMOUNT; i++) अणु
			अगर (ch[i].hw_value && !(ch[i].flags & RTW_IEEE80211_CHAN_DISABLED)) अणु
				स_नकल(&psurveyPara->ch[i], &ch[i],
				       माप(काष्ठा rtw_ieee80211_channel));
				psurveyPara->ch_num++;
			पूर्ण
		पूर्ण
	पूर्ण

	set_fwstate(pmlmepriv, _FW_UNDER_SURVEY);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

	अगर (res == _SUCCESS) अणु
		mod_समयr(&pmlmepriv->scan_to_समयr,
			  jअगरfies + msecs_to_jअगरfies(SCANNING_TIMEOUT));

		led_control_8188eu(padapter, LED_CTL_SITE_SURVEY);

		pmlmepriv->scan_पूर्णांकerval = SCAN_INTERVAL;/*  30*2 sec = 60sec */
	पूर्ण अन्यथा अणु
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण

	वापस res;
पूर्ण

व्योम rtw_पढ़ोtssi_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	kमुक्त(pcmd->parmbuf);
	kमुक्त(pcmd);
पूर्ण

u8 rtw_createbss_cmd(काष्ठा adapter  *padapter)
अणु
	काष्ठा cmd_obj *pcmd;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pdev_network = &padapter->registrypriv.dev_network;
	u8	res = _SUCCESS;

	led_control_8188eu(padapter, LED_CTL_START_TO_LINK);

	अगर (pmlmepriv->assoc_ssid.ssid_length == 0)
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_,
			 (" createbss for Any SSid:%s\n", pmlmepriv->assoc_ssid.ssid));
	अन्यथा
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_,
			 (" createbss for SSid:%s\n", pmlmepriv->assoc_ssid.ssid));

	pcmd = kzalloc(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _CreateBss_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)pdev_network;
	pcmd->cmdsz = get_wlan_bssid_ex_sz(pdev_network);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	pdev_network->Length = pcmd->cmdsz;
	res = rtw_enqueue_cmd(pcmdpriv, pcmd);
निकास:

	वापस res;
पूर्ण

u8 rtw_joinbss_cmd(काष्ठा adapter  *padapter, काष्ठा wlan_network *pnetwork)
अणु
	u8	res = _SUCCESS;
	uपूर्णांक	t_len = 0;
	काष्ठा wlan_bssid_ex		*psecnetwork;
	काष्ठा cmd_obj		*pcmd;
	काष्ठा cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv		*pqospriv = &pmlmepriv->qospriv;
	काष्ठा security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा registry_priv	*pregistrypriv = &padapter->registrypriv;
	काष्ठा ht_priv		*phtpriv = &pmlmepriv->htpriv;
	क्रमागत ndis_802_11_network_infra ndis_network_mode = pnetwork->network.Infraकाष्ठाureMode;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

	led_control_8188eu(padapter, LED_CTL_START_TO_LINK);

	अगर (pmlmepriv->assoc_ssid.ssid_length == 0)
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_info_, ("+Join cmd: Any SSid\n"));
	अन्यथा
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_notice_,
			 ("+Join cmd: SSid =[%s]\n", pmlmepriv->assoc_ssid.ssid));

	pcmd = kzalloc(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	/* क्रम ies is fix buf size */
	t_len = माप(काष्ठा wlan_bssid_ex);

	/* क्रम hidden ap to set fw_state here */
	अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_ADHOC_STATE)) अणु
		चयन (ndis_network_mode) अणु
		हाल Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			अवरोध;
		हाल Ndis802_11Infraकाष्ठाure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			अवरोध;
		हाल Ndis802_11APMode:
		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;
		पूर्ण
	पूर्ण

	psecnetwork = &psecuritypriv->sec_bss;
	अगर (!psecnetwork) अणु
		kमुक्त(pcmd);

		res = _FAIL;

		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("%s :psecnetwork == NULL!!!\n", __func__));

		जाओ निकास;
	पूर्ण

	स_रखो(psecnetwork, 0, t_len);

	स_नकल(psecnetwork, &pnetwork->network, get_wlan_bssid_ex_sz(&pnetwork->network));

	psecuritypriv->authenticator_ie[0] = (अचिन्हित अक्षर)psecnetwork->ie_length;

	अगर (psecnetwork->ie_length - 12 < 255)
		स_नकल(&psecuritypriv->authenticator_ie[1], &psecnetwork->ies[12],
		       psecnetwork->ie_length - 12);
	अन्यथा
		स_नकल(&psecuritypriv->authenticator_ie[1], &psecnetwork->ies[12], 255);

	psecnetwork->ie_length = 0;
	/*  Added by Albert 2009/02/18 */
	/*  If the driver wants to use the bssid to create the connection. */
	/*  If not,  we have to copy the connecting AP's MAC address to it so that */
	/*  the driver just has the bssid inक्रमmation क्रम PMKIDList searching. */

	अगर (!pmlmepriv->assoc_by_bssid)
		स_नकल(&pmlmepriv->assoc_bssid[0], &pnetwork->network.MacAddress[0], ETH_ALEN);

	psecnetwork->ie_length = rtw_reकाष्ठा_sec_ie(padapter, &pnetwork->network.ies[0],
						     &psecnetwork->ies[0],
						     pnetwork->network.ie_length);

	pqospriv->qos_option = 0;

	अगर (pregistrypriv->wmm_enable) अणु
		u32 पंचांगp_len;

		पंचांगp_len = rtw_reकाष्ठा_wmm_ie(padapter, &pnetwork->network.ies[0],
					      &psecnetwork->ies[0],
					      pnetwork->network.ie_length,
					      psecnetwork->ie_length);

		अगर (psecnetwork->ie_length != पंचांगp_len) अणु
			psecnetwork->ie_length = पंचांगp_len;
			pqospriv->qos_option = 1; /* There is WMM IE in this corresp. beacon */
		पूर्ण अन्यथा अणु
			pqospriv->qos_option = 0;/* There is no WMM IE in this corresp. beacon */
		पूर्ण
	पूर्ण

	phtpriv->ht_option = false;
	अगर (pregistrypriv->ht_enable) अणु
		/*
		 * Added by Albert 2010/06/23
		 * For the WEP mode, we will use the bg mode to करो
		 * the connection to aव्योम some IOT issue.
		 * Especially क्रम Realtek 8192u SoftAP.
		 */
		अगर ((padapter->securitypriv.करोt11PrivacyAlgrthm != _WEP40_) &&
		    (padapter->securitypriv.करोt11PrivacyAlgrthm != _WEP104_) &&
		    (padapter->securitypriv.करोt11PrivacyAlgrthm != _TKIP_)) अणु
			/* rtw_reकाष्ठाure_ht_ie */
			rtw_reकाष्ठाure_ht_ie(padapter, &pnetwork->network.ies[0],
					      &psecnetwork->ies[0],
					      pnetwork->network.ie_length, &psecnetwork->ie_length);
		पूर्ण
	पूर्ण

	pmlmeinfo->assoc_AP_venकरोr = check_assoc_AP(pnetwork->network.ies, pnetwork->network.ie_length);

	अगर (pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_TENDA)
		padapter->pwrctrlpriv.smart_ps = 0;
	अन्यथा
		padapter->pwrctrlpriv.smart_ps = padapter->registrypriv.smart_ps;

	DBG_88E("%s: smart_ps =%d\n", __func__, padapter->pwrctrlpriv.smart_ps);

	pcmd->cmdsz = get_wlan_bssid_ex_sz(psecnetwork);/* get cmdsz beक्रमe endian conversion */

	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _JoinBss_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)psecnetwork;
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:

	वापस res;
पूर्ण

u8 rtw_disassoc_cmd(काष्ठा adapter *padapter, u32 deauth_समयout_ms, bool enqueue) /* क्रम sta_mode */
अणु
	काष्ठा cmd_obj *cmकरोbj = शून्य;
	काष्ठा disconnect_parm *param = शून्य;
	काष्ठा cmd_priv *cmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_notice_, ("+%s\n", __func__));

	/* prepare cmd parameter */
	param = kzalloc(माप(*param), GFP_ATOMIC);
	अगर (!param) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	param->deauth_समयout_ms = deauth_समयout_ms;

	अगर (enqueue) अणु
		/* need enqueue, prepare cmd_obj and enqueue */
		cmकरोbj = kzalloc(माप(*cmकरोbj), GFP_ATOMIC);
		अगर (!cmकरोbj) अणु
			res = _FAIL;
			kमुक्त(param);
			जाओ निकास;
		पूर्ण
		init_h2fwcmd_w_parm_no_rsp(cmकरोbj, param, _DisConnect_CMD_);
		res = rtw_enqueue_cmd(cmdpriv, cmकरोbj);
	पूर्ण अन्यथा अणु
		/* no need to enqueue, करो the cmd hdl directly and मुक्त cmd parameter */
		अगर (disconnect_hdl(padapter, (u8 *)param) != H2C_SUCCESS)
			res = _FAIL;
		kमुक्त(param);
	पूर्ण

निकास:

	वापस res;
पूर्ण

u8 rtw_setopmode_cmd(काष्ठा adapter  *padapter, क्रमागत ndis_802_11_network_infra networktype)
अणु
	काष्ठा	cmd_obj *ph2c;
	काष्ठा	setopmode_parm *psetop;

	काष्ठा	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	ph2c = kzalloc(माप(*ph2c), GFP_KERNEL);
	psetop = kzalloc(माप(*psetop), GFP_KERNEL);
	अगर (!ph2c || !psetop) अणु
		kमुक्त(ph2c);
		kमुक्त(psetop);
		वापस false;
	पूर्ण

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
	psetop->mode = (u8)networktype;

	वापस rtw_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

u8 rtw_setstakey_cmd(काष्ठा adapter *padapter, u8 *psta, u8 unicast_key)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm *psetstakey_para;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = शून्य;

	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा sta_info *sta = (काष्ठा sta_info *)psta;

	ph2c = kzalloc(माप(*ph2c), GFP_KERNEL);
	psetstakey_para = kzalloc(माप(*psetstakey_para), GFP_KERNEL);
	psetstakey_rsp = kzalloc(माप(*psetstakey_rsp), GFP_KERNEL);

	अगर (!ph2c || !psetstakey_para || !psetstakey_rsp) अणु
		kमुक्त(ph2c);
		kमुक्त(psetstakey_para);
		kमुक्त(psetstakey_rsp);
		वापस _FAIL;
	पूर्ण

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
	ph2c->rsp = (u8 *)psetstakey_rsp;
	ph2c->rspsz = माप(काष्ठा set_stakey_rsp);

	ether_addr_copy(psetstakey_para->addr, sta->hwaddr);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		psetstakey_para->algorithm = (अचिन्हित अक्षर)psecuritypriv->करोt11PrivacyAlgrthm;
	अन्यथा
		GET_ENCRY_ALGO(psecuritypriv, sta, psetstakey_para->algorithm, false);

	अगर (unicast_key)
		स_नकल(&psetstakey_para->key, &sta->करोt118021x_UncstKey, 16);
	अन्यथा
		स_नकल(&psetstakey_para->key,
		       &psecuritypriv->करोt118021XGrpKey[psecuritypriv->करोt118021XGrpKeyid].skey, 16);

	/* jeff: set this because at least sw key is पढ़ोy */
	padapter->securitypriv.busetkipkey = true;

	वापस rtw_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

u8 rtw_clearstakey_cmd(काष्ठा adapter *padapter, u8 *psta, u8 entry, u8 enqueue)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm	*psetstakey_para;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = शून्य;
	काष्ठा sta_info *sta = (काष्ठा sta_info *)psta;
	u8	res = _SUCCESS;

	अगर (!enqueue) अणु
		clear_cam_entry(padapter, entry);
	पूर्ण अन्यथा अणु
		ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
		अगर (!ph2c) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		psetstakey_para = kzalloc(माप(*psetstakey_para), GFP_ATOMIC);
		अगर (!psetstakey_para) अणु
			kमुक्त(ph2c);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		psetstakey_rsp = kzalloc(माप(*psetstakey_rsp), GFP_ATOMIC);
		अगर (!psetstakey_rsp) अणु
			kमुक्त(ph2c);
			kमुक्त(psetstakey_para);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *)psetstakey_rsp;
		ph2c->rspsz = माप(काष्ठा set_stakey_rsp);

		ether_addr_copy(psetstakey_para->addr, sta->hwaddr);

		psetstakey_para->algorithm = _NO_PRIVACY_;

		psetstakey_para->id = entry;

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण
निकास:

	वापस res;
पूर्ण

u8 rtw_addbareq_cmd(काष्ठा adapter *padapter, u8 tid, u8 *addr)
अणु
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा cmd_obj *ph2c;
	काष्ठा addBaReq_parm *paddbareq_parm;
	u8	res = _SUCCESS;

	ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	paddbareq_parm = kzalloc(माप(*paddbareq_parm), GFP_ATOMIC);
	अगर (!paddbareq_parm) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	paddbareq_parm->tid = tid;
	स_नकल(paddbareq_parm->addr, addr, ETH_ALEN);

	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm, _AddBAReq_CMD_);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;
पूर्ण

u8 rtw_dynamic_chk_wk_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvextra_cmd_parm *pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	res = _SUCCESS;

	ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_ATOMIC);
	अगर (!pdrvextra_cmd_parm) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = DYNAMIC_CHK_WK_CID;
	pdrvextra_cmd_parm->type_size = 0;
	pdrvextra_cmd_parm->pbuf = (u8 *)padapter;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
निकास:
	वापस res;
पूर्ण

u8 rtw_set_chplan_cmd(काष्ठा adapter *padapter, u8 chplan, u8 enqueue)
अणु
	काष्ठा	cmd_obj *pcmकरोbj;
	काष्ठा	SetChannelPlan_param *setChannelPlan_param;
	काष्ठा	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	u8	res = _SUCCESS;

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_notice_, ("+%s\n", __func__));

	/* check input parameter */
	अगर (!rtw_is_channel_plan_valid(chplan)) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	/* prepare cmd parameter */
	setChannelPlan_param = kzalloc(माप(*setChannelPlan_param), GFP_KERNEL);
	अगर (!setChannelPlan_param) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	setChannelPlan_param->channel_plan = chplan;

	अगर (enqueue) अणु
		/* need enqueue, prepare cmd_obj and enqueue */
		pcmकरोbj = kzalloc(माप(*pcmकरोbj), GFP_KERNEL);
		अगर (!pcmकरोbj) अणु
			kमुक्त(setChannelPlan_param);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		init_h2fwcmd_w_parm_no_rsp(pcmकरोbj, setChannelPlan_param, _SetChannelPlan_CMD_);
		res = rtw_enqueue_cmd(pcmdpriv, pcmकरोbj);
	पूर्ण अन्यथा अणु
		/* no need to enqueue, करो the cmd hdl directly and मुक्त cmd parameter */
		अगर (set_chplan_hdl(padapter, (अचिन्हित अक्षर *)setChannelPlan_param) != H2C_SUCCESS)
			res = _FAIL;

		kमुक्त(setChannelPlan_param);
	पूर्ण

	अगर (res == _SUCCESS)
		padapter->mlmepriv.ChannelPlan = chplan;

निकास:

	वापस res;
पूर्ण

अटल व्योम traffic_status_watchकरोg(काष्ठा adapter *padapter)
अणु
	u8	bEnterPS;
	u8	bBusyTraffic = false, bTxBusyTraffic = false, bRxBusyTraffic = false;
	u8	bHigherBusyTraffic = false, bHigherBusyRxTraffic = false, bHigherBusyTxTraffic = false;
	काष्ठा mlme_priv		*pmlmepriv = &padapter->mlmepriv;

	/*  */
	/*  Determine अगर our traffic is busy now */
	/*  */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 100 ||
		    pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 100) अणु
			bBusyTraffic = true;

			अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod >
			    pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bRxBusyTraffic = true;
			अन्यथा
				bTxBusyTraffic = true;
		पूर्ण

		/*  Higher Tx/Rx data. */
		अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 4000 ||
		    pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 4000) अणु
			bHigherBusyTraffic = true;

			अगर (pmlmepriv->LinkDetectInfo.NumRxOkInPeriod >
			    pmlmepriv->LinkDetectInfo.NumTxOkInPeriod)
				bHigherBusyRxTraffic = true;
			अन्यथा
				bHigherBusyTxTraffic = true;
		पूर्ण

		/*  check traffic क्रम  घातersaving. */
		अगर (((pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod + pmlmepriv->LinkDetectInfo.NumTxOkInPeriod) > 8) ||
		    (pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 2))
			bEnterPS = false;
		अन्यथा
			bEnterPS = true;

		/*  LeisurePS only work in infra mode. */
		अगर (bEnterPS)
			LPS_Enter(padapter);
		अन्यथा
			LPS_Leave(padapter);
	पूर्ण अन्यथा अणु
		LPS_Leave(padapter);
	पूर्ण

	pmlmepriv->LinkDetectInfo.NumRxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumTxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.bBusyTraffic = bBusyTraffic;
	pmlmepriv->LinkDetectInfo.bTxBusyTraffic = bTxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bRxBusyTraffic = bRxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTraffic = bHigherBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyRxTraffic = bHigherBusyRxTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTxTraffic = bHigherBusyTxTraffic;
पूर्ण

अटल व्योम dynamic_chk_wk_hdl(काष्ठा adapter *padapter, u8 *pbuf, पूर्णांक sz)
अणु
	काष्ठा mlme_priv *pmlmepriv;

	padapter = (काष्ठा adapter *)pbuf;
	pmlmepriv = &padapter->mlmepriv;

#अगर_घोषित CONFIG_88EU_AP_MODE
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		expire_समयout_chk(padapter);
#पूर्ण_अगर

	linked_status_chk(padapter);
	traffic_status_watchकरोg(padapter);

	rtw_hal_dm_watchकरोg(padapter);
पूर्ण

अटल व्योम lps_ctrl_wk_hdl(काष्ठा adapter *padapter, u8 lps_ctrl_type)
अणु
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8	mstatus;

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_STATE))
		वापस;

	चयन (lps_ctrl_type) अणु
	हाल LPS_CTRL_SCAN:
		अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			/* connect */
			LPS_Leave(padapter);
		पूर्ण
		अवरोध;
	हाल LPS_CTRL_JOINBSS:
		LPS_Leave(padapter);
		अवरोध;
	हाल LPS_CTRL_CONNECT:
		mstatus = 1;/* connect */
		/*  Reset LPS Setting */
		padapter->pwrctrlpriv.LpsIdleCount = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		अवरोध;
	हाल LPS_CTRL_DISCONNECT:
		mstatus = 0;/* disconnect */
		LPS_Leave(padapter);
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		अवरोध;
	हाल LPS_CTRL_SPECIAL_PACKET:
		pwrpriv->DelayLPSLastTimeStamp = jअगरfies;
		LPS_Leave(padapter);
		अवरोध;
	हाल LPS_CTRL_LEAVE:
		LPS_Leave(padapter);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u8 rtw_lps_ctrl_wk_cmd(काष्ठा adapter *padapter, u8 lps_ctrl_type, u8 enqueue)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	res = _SUCCESS;

	अगर (enqueue) अणु
		ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
		अगर (!ph2c) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_ATOMIC);
		अगर (!pdrvextra_cmd_parm) अणु
			kमुक्त(ph2c);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm->ec_id = LPS_CTRL_WK_CID;
		pdrvextra_cmd_parm->type_size = lps_ctrl_type;
		pdrvextra_cmd_parm->pbuf = शून्य;

		init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण अन्यथा अणु
		lps_ctrl_wk_hdl(padapter, lps_ctrl_type);
	पूर्ण

निकास:

	वापस res;
पूर्ण

अटल व्योम rpt_समयr_setting_wk_hdl(काष्ठा adapter *padapter, u16 min_समय)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_RPT_TIMER_SETTING, (u8 *)(&min_समय));
पूर्ण

u8 rtw_rpt_समयr_cfg_cmd(काष्ठा adapter *padapter, u16 min_समय)
अणु
	काष्ठा cmd_obj		*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;

	u8	res = _SUCCESS;

	ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_ATOMIC);
	अगर (!pdrvextra_cmd_parm) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = RTP_TIMER_CFG_WK_CID;
	pdrvextra_cmd_parm->type_size = min_समय;
	pdrvextra_cmd_parm->pbuf = शून्य;
	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
निकास:

	वापस res;
पूर्ण

अटल व्योम antenna_select_wk_hdl(काष्ठा adapter *padapter, u8 antenna)
अणु
	rtw_hal_set_hwreg(padapter, HW_VAR_ANTENNA_DIVERSITY_SELECT, (u8 *)(&antenna));
पूर्ण

u8 rtw_antenna_select_cmd(काष्ठा adapter *padapter, u8 antenna, u8 enqueue)
अणु
	काष्ठा cmd_obj		*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	support_ant_भाग;
	u8	res = _SUCCESS;

	rtw_hal_get_def_var(padapter, HAL_DEF_IS_SUPPORT_ANT_DIV, &support_ant_भाग);
	अगर (!support_ant_भाग)
		वापस res;

	अगर (enqueue) अणु
		ph2c = kzalloc(माप(*ph2c), GFP_KERNEL);
		अगर (!ph2c) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_KERNEL);
		अगर (!pdrvextra_cmd_parm) अणु
			kमुक्त(ph2c);
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pdrvextra_cmd_parm->ec_id = ANT_SELECT_WK_CID;
		pdrvextra_cmd_parm->type_size = antenna;
		pdrvextra_cmd_parm->pbuf = शून्य;
		init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	पूर्ण अन्यथा अणु
		antenna_select_wk_hdl(padapter, antenna);
	पूर्ण
निकास:

	वापस res;
पूर्ण

u8 rtw_ps_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj		*ppscmd;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;

	ppscmd = kzalloc(माप(*ppscmd), GFP_ATOMIC);
	pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_ATOMIC);
	अगर (!ppscmd || !pdrvextra_cmd_parm) अणु
		kमुक्त(ppscmd);
		kमुक्त(pdrvextra_cmd_parm);
		वापस _FAIL;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = POWER_SAVING_CTRL_WK_CID;
	pdrvextra_cmd_parm->pbuf = शून्य;
	init_h2fwcmd_w_parm_no_rsp(ppscmd, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

	वापस rtw_enqueue_cmd(pcmdpriv, ppscmd);
पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE

अटल व्योम rtw_chk_hi_queue_hdl(काष्ठा adapter *padapter)
अणु
	पूर्णांक cnt = 0;
	काष्ठा sta_info *psta_bmc;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	psta_bmc = rtw_get_bcmc_stainfo(padapter);
	अगर (!psta_bmc)
		वापस;

	अगर (psta_bmc->sleepq_len == 0) अणु
		u8 val = 0;

		rtw_hal_get_hwreg(padapter, HW_VAR_CHK_HI_QUEUE_EMPTY, &val);

		जबतक (!val) अणु
			msleep(100);

			cnt++;

			अगर (cnt > 10)
				अवरोध;

			rtw_hal_get_hwreg(padapter, HW_VAR_CHK_HI_QUEUE_EMPTY, &val);
		पूर्ण

		अगर (cnt <= 10) अणु
			pstapriv->tim_biपंचांगap &= ~BIT(0);
			pstapriv->sta_dz_biपंचांगap &= ~BIT(0);

			update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
		पूर्ण अन्यथा अणु /* re check again */
			rtw_chk_hi_queue_cmd(padapter);
		पूर्ण
	पूर्ण
पूर्ण

u8 rtw_chk_hi_queue_cmd(काष्ठा adapter *padapter)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा drvextra_cmd_parm	*pdrvextra_cmd_parm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	res = _SUCCESS;

	ph2c = kzalloc(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm = kzalloc(माप(*pdrvextra_cmd_parm), GFP_ATOMIC);
	अगर (!pdrvextra_cmd_parm) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pdrvextra_cmd_parm->ec_id = CHECK_HIQ_WK_CID;
	pdrvextra_cmd_parm->type_size = 0;
	pdrvextra_cmd_parm->pbuf = शून्य;

	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
निकास:
	वापस res;
पूर्ण
#पूर्ण_अगर

u8 rtw_drvextra_cmd_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf)
अणु
	काष्ठा drvextra_cmd_parm *pdrvextra_cmd;

	अगर (!pbuf)
		वापस H2C_PARAMETERS_ERROR;

	pdrvextra_cmd = (काष्ठा drvextra_cmd_parm *)pbuf;

	चयन (pdrvextra_cmd->ec_id) अणु
	हाल DYNAMIC_CHK_WK_CID:
		dynamic_chk_wk_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);
		अवरोध;
	हाल POWER_SAVING_CTRL_WK_CID:
		rtw_ps_processor(padapter);
		अवरोध;
	हाल LPS_CTRL_WK_CID:
		lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type_size);
		अवरोध;
	हाल RTP_TIMER_CFG_WK_CID:
		rpt_समयr_setting_wk_hdl(padapter, pdrvextra_cmd->type_size);
		अवरोध;
	हाल ANT_SELECT_WK_CID:
		antenna_select_wk_hdl(padapter, pdrvextra_cmd->type_size);
		अवरोध;
#अगर_घोषित CONFIG_88EU_AP_MODE
	हाल CHECK_HIQ_WK_CID:
		rtw_chk_hi_queue_hdl(padapter);
		अवरोध;
#पूर्ण_अगर /* CONFIG_88EU_AP_MODE */
	शेष:
		अवरोध;
	पूर्ण

	अगर (pdrvextra_cmd->pbuf && pdrvextra_cmd->type_size > 0)
		kमुक्त(pdrvextra_cmd->pbuf);

	वापस H2C_SUCCESS;
पूर्ण

व्योम rtw_survey_cmd_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res == H2C_DROPPED) अणु
		/* TODO: cancel समयr and करो समयout handler directly... */
		/* need to make समयout handlerOS independent */
		mod_समयr(&pmlmepriv->scan_to_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	पूर्ण अन्यथा अगर (pcmd->res != H2C_SUCCESS) अणु
		mod_समयr(&pmlmepriv->scan_to_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\n ********Error: MgntActrtw_set_802_11_bssid_LIST_SCAN Fail ************\n\n."));
	पूर्ण
पूर्ण

व्योम rtw_disassoc_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res != H2C_SUCCESS) अणु
		spin_lock_bh(&pmlmepriv->lock);
		set_fwstate(pmlmepriv, _FW_LINKED);
		spin_unlock_bh(&pmlmepriv->lock);

		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\n ***Error: disconnect_cmd_callback Fail ***\n."));
	पूर्ण
पूर्ण

व्योम rtw_joinbss_cmd_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res == H2C_DROPPED) अणु
		/* TODO: cancel समयr and करो समयout handler directly... */
		/* need to make समयout handlerOS independent */
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	पूर्ण अन्यथा अगर (pcmd->res != H2C_SUCCESS) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("********Error:rtw_select_and_join_from_scanned_queue Wait Sema  Fail ************\n"));
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	पूर्ण
पूर्ण

व्योम rtw_createbss_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pnetwork = (काष्ठा wlan_bssid_ex *)pcmd->parmbuf;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	अगर (pcmd->res != H2C_SUCCESS) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\n **** Error: %s  Fail ****\n\n.", __func__));
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	पूर्ण

	del_समयr_sync(&pmlmepriv->assoc_समयr);

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		psta = rtw_get_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		अगर (!psta) अणु
			psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);
			अगर (!psta) अणु
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
					 ("\nCan't alloc sta_info when createbss_cmd_callback\n"));
				जाओ createbss_cmd_fail;
			पूर्ण
		पूर्ण

		rtw_indicate_connect(padapter);
	पूर्ण अन्यथा अणु
		pwlan = rtw_alloc_network(pmlmepriv);
		spin_lock_bh(&pmlmepriv->scanned_queue.lock);
		अगर (!pwlan) अणु
			pwlan = rtw_get_oldest_wlan_network(&pmlmepriv->scanned_queue);
			अगर (!pwlan) अणु
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
					 ("\n Error:  can't get pwlan in rtw_joinbss_event_callback\n"));
				spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
				जाओ createbss_cmd_fail;
			पूर्ण
			pwlan->last_scanned = jअगरfies;
		पूर्ण अन्यथा अणु
			list_add_tail(&pwlan->list,
				      &pmlmepriv->scanned_queue.queue);
		पूर्ण

		pnetwork->Length = get_wlan_bssid_ex_sz(pnetwork);
		स_नकल(&pwlan->network, pnetwork, pnetwork->Length);

		स_नकल(&tgt_network->network, pnetwork, (get_wlan_bssid_ex_sz(pnetwork)));

		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		/*  we will set _FW_LINKED when there is one more sat to
		 *  join us (rtw_stassoc_event_callback)
		 */
	पूर्ण

createbss_cmd_fail:

	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_setstaKey_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = (काष्ठा set_stakey_rsp *)(pcmd->rsp);
	काष्ठा sta_info *psta = rtw_get_stainfo(pstapriv, psetstakey_rsp->addr);

	अगर (!psta) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\nERROR: %s => can't get sta_info\n\n", __func__));
	पूर्ण
पूर्ण

व्योम rtw_setassocsta_cmdrsp_callback(काष्ठा adapter *padapter,  काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा set_assocsta_parm *passocsta_parm = (काष्ठा set_assocsta_parm *)(pcmd->parmbuf);
	काष्ठा set_assocsta_rsp *passocsta_rsp = (काष्ठा set_assocsta_rsp *)(pcmd->rsp);
	काष्ठा sta_info *psta = rtw_get_stainfo(pstapriv, passocsta_parm->addr);

	अगर (!psta) अणु
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_,
			 ("\nERROR: %s => can't get sta_info\n\n", __func__));
		वापस;
	पूर्ण

	psta->aid = passocsta_rsp->cam_id;
	psta->mac_id = passocsta_rsp->cam_id;

	spin_lock_bh(&pmlmepriv->lock);

	set_fwstate(pmlmepriv, _FW_LINKED);
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण
