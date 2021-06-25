<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_cmd.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_CMD_C_

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/rtnetlink.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "mlme_osdep.h"

/*
 * Caller and the r8712_cmd_thपढ़ो can protect cmd_q by spin_lock.
 * No irqsave is necessary.
 */

पूर्णांक r8712_init_cmd_priv(काष्ठा cmd_priv *pcmdpriv)
अणु
	init_completion(&pcmdpriv->cmd_queue_comp);
	init_completion(&pcmdpriv->terminate_cmdthपढ़ो_comp);

	_init_queue(&(pcmdpriv->cmd_queue));

	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */
	pcmdpriv->cmd_seq = 1;
	pcmdpriv->cmd_allocated_buf = kदो_स्मृति(MAX_CMDSZ + CMDBUFF_ALIGN_SZ,
					      GFP_ATOMIC);
	अगर (!pcmdpriv->cmd_allocated_buf)
		वापस -ENOMEM;
	pcmdpriv->cmd_buf = pcmdpriv->cmd_allocated_buf  +  CMDBUFF_ALIGN_SZ -
			    ((addr_t)(pcmdpriv->cmd_allocated_buf) &
			    (CMDBUFF_ALIGN_SZ - 1));
	pcmdpriv->rsp_allocated_buf = kदो_स्मृति(MAX_RSPSZ + 4, GFP_ATOMIC);
	अगर (!pcmdpriv->rsp_allocated_buf) अणु
		kमुक्त(pcmdpriv->cmd_allocated_buf);
		pcmdpriv->cmd_allocated_buf = शून्य;
		वापस -ENOMEM;
	पूर्ण
	pcmdpriv->rsp_buf = pcmdpriv->rsp_allocated_buf  +  4 -
			    ((addr_t)(pcmdpriv->rsp_allocated_buf) & 3);
	pcmdpriv->cmd_issued_cnt = 0;
	pcmdpriv->cmd_करोne_cnt = 0;
	pcmdpriv->rsp_cnt = 0;
	वापस 0;
पूर्ण

पूर्णांक r8712_init_evt_priv(काष्ठा evt_priv *pevtpriv)
अणु
	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */
	pevtpriv->event_seq = 0;
	pevtpriv->evt_allocated_buf = kदो_स्मृति(MAX_EVTSZ + 4, GFP_ATOMIC);

	अगर (!pevtpriv->evt_allocated_buf)
		वापस -ENOMEM;
	pevtpriv->evt_buf = pevtpriv->evt_allocated_buf  +  4 -
			    ((addr_t)(pevtpriv->evt_allocated_buf) & 3);
	pevtpriv->evt_करोne_cnt = 0;
	वापस 0;
पूर्ण

व्योम r8712_मुक्त_evt_priv(काष्ठा evt_priv *pevtpriv)
अणु
	kमुक्त(pevtpriv->evt_allocated_buf);
पूर्ण

व्योम r8712_मुक्त_cmd_priv(काष्ठा cmd_priv *pcmdpriv)
अणु
	अगर (pcmdpriv) अणु
		kमुक्त(pcmdpriv->cmd_allocated_buf);
		kमुक्त(pcmdpriv->rsp_allocated_buf);
	पूर्ण
पूर्ण

/*
 * Calling Context:
 *
 * r8712_enqueue_cmd can only be called between kernel thपढ़ो,
 * since only spin_lock is used.
 *
 * ISR/Call-Back functions can't call this sub-function.
 *
 */

व्योम r8712_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj)
अणु
	काष्ठा __queue *queue;
	अचिन्हित दीर्घ irqL;

	अगर (pcmdpriv->padapter->eeprompriv.bस्वतःload_fail_flag)
		वापस;
	अगर (!obj)
		वापस;
	queue = &pcmdpriv->cmd_queue;
	spin_lock_irqsave(&queue->lock, irqL);
	list_add_tail(&obj->list, &queue->queue);
	spin_unlock_irqrestore(&queue->lock, irqL);
	complete(&pcmdpriv->cmd_queue_comp);
पूर्ण

काष्ठा cmd_obj *r8712_dequeue_cmd(काष्ठा  __queue *queue)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा cmd_obj *obj;

	spin_lock_irqsave(&queue->lock, irqL);
	obj = list_first_entry_or_null(&queue->queue,
				       काष्ठा cmd_obj, list);
	अगर (obj)
		list_del_init(&obj->list);
	spin_unlock_irqrestore(&queue->lock, irqL);
	वापस obj;
पूर्ण

व्योम r8712_enqueue_cmd_ex(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा  __queue *queue;

	अगर (!obj)
		वापस;
	अगर (pcmdpriv->padapter->eeprompriv.bस्वतःload_fail_flag)
		वापस;
	queue = &pcmdpriv->cmd_queue;
	spin_lock_irqsave(&queue->lock, irqL);
	list_add_tail(&obj->list, &queue->queue);
	spin_unlock_irqrestore(&queue->lock, irqL);
	complete(&pcmdpriv->cmd_queue_comp);
पूर्ण

व्योम r8712_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd)
अणु
	अगर ((pcmd->cmdcode != _JoinBss_CMD_) &&
	    (pcmd->cmdcode != _CreateBss_CMD_))
		kमुक्त(pcmd->parmbuf);
	अगर (pcmd->rsp) अणु
		अगर (pcmd->rspsz != 0)
			kमुक्त(pcmd->rsp);
	पूर्ण
	kमुक्त(pcmd);
पूर्ण

u8 r8712_sitesurvey_cmd(काष्ठा _adapter *padapter,
			काष्ठा ndis_802_11_ssid *pssid)
	__must_hold(&padapter->mlmepriv.lock)
अणु
	काष्ठा cmd_obj	*ph2c;
	काष्ठा sitesurvey_parm	*psurveyPara;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस _FAIL;
	psurveyPara = kदो_स्मृति(माप(*psurveyPara), GFP_ATOMIC);
	अगर (!psurveyPara) अणु
		kमुक्त(ph2c);
		वापस _FAIL;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, psurveyPara,
				   GEN_CMD_CODE(_SiteSurvey));
	psurveyPara->bsslimit = cpu_to_le32(48);
	psurveyPara->passive_mode = cpu_to_le32(pmlmepriv->passive_mode);
	psurveyPara->ss_ssidlen = 0;
	स_रखो(psurveyPara->ss_ssid, 0, IW_ESSID_MAX_SIZE + 1);
	अगर (pssid && pssid->SsidLength) अणु
		पूर्णांक len = min_t(पूर्णांक, pssid->SsidLength, IW_ESSID_MAX_SIZE);

		स_नकल(psurveyPara->ss_ssid, pssid->Ssid, len);
		psurveyPara->ss_ssidlen = cpu_to_le32(len);
	पूर्ण
	set_fwstate(pmlmepriv, _FW_UNDER_SURVEY);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	mod_समयr(&pmlmepriv->scan_to_समयr,
		  jअगरfies + msecs_to_jअगरfies(SCANNING_TIMEOUT));
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_SITE_SURVEY);
	padapter->blnEnableRxFF0Filter = 0;
	वापस _SUCCESS;
पूर्ण

पूर्णांक r8712_setdatarate_cmd(काष्ठा _adapter *padapter, u8 *rateset)
अणु
	काष्ठा cmd_obj		*ph2c;
	काष्ठा setdatarate_parm	*pbsetdataratepara;
	काष्ठा cmd_priv		*pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस -ENOMEM;
	pbsetdataratepara = kदो_स्मृति(माप(*pbsetdataratepara), GFP_ATOMIC);
	अगर (!pbsetdataratepara) अणु
		kमुक्त(ph2c);
		वापस -ENOMEM;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, pbsetdataratepara,
				   GEN_CMD_CODE(_SetDataRate));
	pbsetdataratepara->mac_id = 5;
	स_नकल(pbsetdataratepara->datarates, rateset, NumRates);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	वापस 0;
पूर्ण

व्योम r8712_set_chplan_cmd(काष्ठा _adapter *padapter, पूर्णांक chplan)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा SetChannelPlan_param *psetchplanpara;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	psetchplanpara = kदो_स्मृति(माप(*psetchplanpara), GFP_ATOMIC);
	अगर (!psetchplanpara) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetchplanpara,
				GEN_CMD_CODE(_SetChannelPlan));
	psetchplanpara->ChannelPlan = chplan;
	r8712_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

पूर्णांक r8712_setrfreg_cmd(काष्ठा _adapter  *padapter, u8 offset, u32 val)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा ग_लिखोRF_parm *pग_लिखोrfparm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस -ENOMEM;
	pग_लिखोrfparm = kदो_स्मृति(माप(*pग_लिखोrfparm), GFP_ATOMIC);
	अगर (!pग_लिखोrfparm) अणु
		kमुक्त(ph2c);
		वापस -ENOMEM;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, pग_लिखोrfparm, GEN_CMD_CODE(_SetRFReg));
	pग_लिखोrfparm->offset = offset;
	pग_लिखोrfparm->value = val;
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	वापस 0;
पूर्ण

पूर्णांक r8712_getrfreg_cmd(काष्ठा _adapter *padapter, u8 offset, u8 *pval)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा पढ़ोRF_parm *prdrfparm;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस -ENOMEM;
	prdrfparm = kदो_स्मृति(माप(*prdrfparm), GFP_ATOMIC);
	अगर (!prdrfparm) अणु
		kमुक्त(ph2c);
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&ph2c->list);
	ph2c->cmdcode = GEN_CMD_CODE(_GetRFReg);
	ph2c->parmbuf = (अचिन्हित अक्षर *)prdrfparm;
	ph2c->cmdsz =  माप(काष्ठा पढ़ोRF_parm);
	ph2c->rsp = pval;
	ph2c->rspsz = माप(काष्ठा पढ़ोRF_rsp);
	prdrfparm->offset = offset;
	r8712_enqueue_cmd(pcmdpriv, ph2c);
	वापस 0;
पूर्ण

व्योम r8712_getbbrfreg_cmdrsp_callback(काष्ठा _adapter *padapter,
				      काष्ठा cmd_obj *pcmd)
अणु
	kमुक्त(pcmd->parmbuf);
	kमुक्त(pcmd);
	padapter->mppriv.workparam.bcompleted = true;
पूर्ण

व्योम r8712_पढ़ोtssi_cmdrsp_callback(काष्ठा _adapter *padapter,
				काष्ठा cmd_obj *pcmd)
अणु
	kमुक्त(pcmd->parmbuf);
	kमुक्त(pcmd);

	padapter->mppriv.workparam.bcompleted = true;
पूर्ण

पूर्णांक r8712_createbss_cmd(काष्ठा _adapter *padapter)
अणु
	काष्ठा cmd_obj *pcmd;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा wlan_bssid_ex *pdev_network =
				 &padapter->registrypriv.dev_network;

	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_START_TO_LINK);
	pcmd = kदो_स्मृति(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _CreateBss_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)pdev_network;
	pcmd->cmdsz = r8712_get_wlan_bssid_ex_sz(pdev_network);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	/* notes: translate IELength & Length after assign to cmdsz; */
	pdev_network->Length = pcmd->cmdsz;
	pdev_network->IELength = pdev_network->IELength;
	pdev_network->Ssid.SsidLength =	pdev_network->Ssid.SsidLength;
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	वापस 0;
पूर्ण

पूर्णांक r8712_joinbss_cmd(काष्ठा _adapter  *padapter, काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा wlan_bssid_ex *psecnetwork;
	काष्ठा cmd_obj		*pcmd;
	काष्ठा cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv		*pqospriv = &pmlmepriv->qospriv;
	काष्ठा security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा registry_priv	*pregistrypriv = &padapter->registrypriv;
	क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE ndis_network_mode =
		pnetwork->network.Infraकाष्ठाureMode;

	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_START_TO_LINK);
	pcmd = kदो_स्मृति(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd)
		वापस -ENOMEM;

	/* क्रम hidden ap to set fw_state here */
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_ADHOC_STATE) !=
	    true) अणु
		चयन (ndis_network_mode) अणु
		हाल Ndis802_11IBSS:
			pmlmepriv->fw_state |= WIFI_ADHOC_STATE;
			अवरोध;
		हाल Ndis802_11Infraकाष्ठाure:
			pmlmepriv->fw_state |= WIFI_STATION_STATE;
			अवरोध;
		हाल Ndis802_11APMode:
		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;
		पूर्ण
	पूर्ण
	psecnetwork = &psecuritypriv->sec_bss;
	स_नकल(psecnetwork, &pnetwork->network, माप(*psecnetwork));
	psecuritypriv->authenticator_ie[0] = (अचिन्हित अक्षर)
					     psecnetwork->IELength;
	अगर ((psecnetwork->IELength - 12) < (256 - 1))
		स_नकल(&psecuritypriv->authenticator_ie[1],
			&psecnetwork->IEs[12], psecnetwork->IELength - 12);
	अन्यथा
		स_नकल(&psecuritypriv->authenticator_ie[1],
			&psecnetwork->IEs[12], (256 - 1));
	psecnetwork->IELength = 0;
	/*
	 * If the driver wants to use the bssid to create the connection.
	 * If not, we copy the connecting AP's MAC address to it so that
	 * the driver just has the bssid inक्रमmation क्रम PMKIDList searching.
	 */
	अगर (!pmlmepriv->assoc_by_bssid)
		ether_addr_copy(&pmlmepriv->assoc_bssid[0],
				&pnetwork->network.MacAddress[0]);
	psecnetwork->IELength = r8712_reकाष्ठा_sec_ie(padapter,
						&pnetwork->network.IEs[0],
						&psecnetwork->IEs[0],
						pnetwork->network.IELength);
	pqospriv->qos_option = 0;
	अगर (pregistrypriv->wmm_enable) अणु
		u32 पंचांगp_len;

		पंचांगp_len = r8712_reकाष्ठा_wmm_ie(padapter,
					  &pnetwork->network.IEs[0],
					  &psecnetwork->IEs[0],
					  pnetwork->network.IELength,
					  psecnetwork->IELength);
		अगर (psecnetwork->IELength != पंचांगp_len) अणु
			psecnetwork->IELength = पंचांगp_len;
			pqospriv->qos_option = 1; /* WMM IE in beacon */
		पूर्ण अन्यथा अणु
			pqospriv->qos_option = 0; /* no WMM IE in beacon */
		पूर्ण
	पूर्ण
	अगर (pregistrypriv->ht_enable) अणु
		/*
		 * For WEP mode, we will use the bg mode to करो the connection
		 * to aव्योम some IOT issues, especially क्रम Realtek 8192u
		 * SoftAP.
		 */
		अगर ((padapter->securitypriv.PrivacyAlgrthm != _WEP40_) &&
		    (padapter->securitypriv.PrivacyAlgrthm != _WEP104_)) अणु
			/* reकाष्ठाure_ht_ie */
			r8712_reकाष्ठाure_ht_ie(padapter,
						&pnetwork->network.IEs[0],
						&psecnetwork->IEs[0],
						pnetwork->network.IELength,
						&psecnetwork->IELength);
		पूर्ण
	पूर्ण
	psecuritypriv->supplicant_ie[0] = (u8)psecnetwork->IELength;
	अगर (psecnetwork->IELength < 255)
		स_नकल(&psecuritypriv->supplicant_ie[1], &psecnetwork->IEs[0],
			psecnetwork->IELength);
	अन्यथा
		स_नकल(&psecuritypriv->supplicant_ie[1], &psecnetwork->IEs[0],
			255);
	/* get cmdsz beक्रमe endian conversion */
	pcmd->cmdsz = r8712_get_wlan_bssid_ex_sz(psecnetwork);
#अगर_घोषित __BIG_ENDIAN
	/* wlan_network endian conversion */
	psecnetwork->Length = cpu_to_le32(psecnetwork->Length);
	psecnetwork->Ssid.SsidLength = cpu_to_le32(
				       psecnetwork->Ssid.SsidLength);
	psecnetwork->Privacy = cpu_to_le32(psecnetwork->Privacy);
	psecnetwork->Rssi = cpu_to_le32(psecnetwork->Rssi);
	psecnetwork->NetworkTypeInUse = cpu_to_le32(
					psecnetwork->NetworkTypeInUse);
	psecnetwork->Configuration.ATIMWinकरोw = cpu_to_le32(
				psecnetwork->Configuration.ATIMWinकरोw);
	psecnetwork->Configuration.BeaconPeriod = cpu_to_le32(
				 psecnetwork->Configuration.BeaconPeriod);
	psecnetwork->Configuration.DSConfig = cpu_to_le32(
				psecnetwork->Configuration.DSConfig);
	psecnetwork->Configuration.FHConfig.DwellTime = cpu_to_le32(
				psecnetwork->Configuration.FHConfig.DwellTime);
	psecnetwork->Configuration.FHConfig.HopPattern = cpu_to_le32(
				psecnetwork->Configuration.FHConfig.HopPattern);
	psecnetwork->Configuration.FHConfig.HopSet = cpu_to_le32(
				psecnetwork->Configuration.FHConfig.HopSet);
	psecnetwork->Configuration.FHConfig.Length = cpu_to_le32(
				psecnetwork->Configuration.FHConfig.Length);
	psecnetwork->Configuration.Length = cpu_to_le32(
				psecnetwork->Configuration.Length);
	psecnetwork->Infraकाष्ठाureMode = cpu_to_le32(
				psecnetwork->Infraकाष्ठाureMode);
	psecnetwork->IELength = cpu_to_le32(psecnetwork->IELength);
#पूर्ण_अगर
	INIT_LIST_HEAD(&pcmd->list);
	pcmd->cmdcode = _JoinBss_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)psecnetwork;
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	वापस 0;
पूर्ण

व्योम r8712_disassoc_cmd(काष्ठा _adapter *padapter) /* क्रम sta_mode */
अणु
	काष्ठा cmd_obj *pdisconnect_cmd;
	काष्ठा disconnect_parm *pdisconnect;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pdisconnect_cmd = kदो_स्मृति(माप(*pdisconnect_cmd), GFP_ATOMIC);
	अगर (!pdisconnect_cmd)
		वापस;
	pdisconnect = kदो_स्मृति(माप(*pdisconnect), GFP_ATOMIC);
	अगर (!pdisconnect) अणु
		kमुक्त(pdisconnect_cmd);
		वापस;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(pdisconnect_cmd, pdisconnect,
				   _DisConnect_CMD_);
	r8712_enqueue_cmd(pcmdpriv, pdisconnect_cmd);
पूर्ण

व्योम r8712_setopmode_cmd(काष्ठा _adapter *padapter,
		 क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा setopmode_parm *psetop;

	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	psetop = kदो_स्मृति(माप(*psetop), GFP_ATOMIC);
	अगर (!psetop) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
	psetop->mode = (u8)networktype;
	r8712_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

व्योम r8712_setstakey_cmd(काष्ठा _adapter *padapter, u8 *psta, u8 unicast_key)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm *psetstakey_para;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा sta_info *sta = (काष्ठा sta_info *)psta;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	psetstakey_para = kदो_स्मृति(माप(*psetstakey_para), GFP_ATOMIC);
	अगर (!psetstakey_para) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	psetstakey_rsp = kदो_स्मृति(माप(*psetstakey_rsp), GFP_ATOMIC);
	अगर (!psetstakey_rsp) अणु
		kमुक्त(ph2c);
		kमुक्त(psetstakey_para);
		वापस;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
	ph2c->rsp = (u8 *) psetstakey_rsp;
	ph2c->rspsz = माप(काष्ठा set_stakey_rsp);
	ether_addr_copy(psetstakey_para->addr, sta->hwaddr);
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		psetstakey_para->algorithm = (अचिन्हित अक्षर)
					    psecuritypriv->PrivacyAlgrthm;
	अन्यथा
		GET_ENCRY_ALGO(psecuritypriv, sta,
			       psetstakey_para->algorithm, false);
	अगर (unicast_key)
		स_नकल(&psetstakey_para->key, &sta->x_UncstKey, 16);
	अन्यथा
		स_नकल(&psetstakey_para->key,
			&psecuritypriv->XGrpKey[
			psecuritypriv->XGrpKeyid - 1]. skey, 16);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

व्योम r8712_setMacAddr_cmd(काष्ठा _adapter *padapter, u8 *mac_addr)
अणु
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	काष्ठा cmd_obj *ph2c;
	काष्ठा SetMacAddr_param	*psetMacAddr_para;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	psetMacAddr_para = kदो_स्मृति(माप(*psetMacAddr_para), GFP_ATOMIC);
	अगर (!psetMacAddr_para) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetMacAddr_para,
				   _SetMacAddress_CMD_);
	ether_addr_copy(psetMacAddr_para->MacAddr, mac_addr);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण

व्योम r8712_addbareq_cmd(काष्ठा _adapter *padapter, u8 tid)
अणु
	काष्ठा cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	काष्ठा cmd_obj		*ph2c;
	काष्ठा addBaReq_parm	*paddbareq_parm;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	paddbareq_parm = kदो_स्मृति(माप(*paddbareq_parm), GFP_ATOMIC);
	अगर (!paddbareq_parm) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	paddbareq_parm->tid = tid;
	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm,
				   GEN_CMD_CODE(_AddBAReq));
	r8712_enqueue_cmd_ex(pcmdpriv, ph2c);
पूर्ण

व्योम r8712_wdg_wk_cmd(काष्ठा _adapter *padapter)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा drvपूर्णांक_cmd_parm  *pdrvपूर्णांकcmd_param;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	pdrvपूर्णांकcmd_param = kदो_स्मृति(माप(*pdrvपूर्णांकcmd_param), GFP_ATOMIC);
	अगर (!pdrvपूर्णांकcmd_param) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण
	pdrvपूर्णांकcmd_param->i_cid = WDG_WK_CID;
	pdrvपूर्णांकcmd_param->sz = 0;
	pdrvपूर्णांकcmd_param->pbuf = शून्य;
	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvपूर्णांकcmd_param, _DRV_INT_CMD_);
	r8712_enqueue_cmd_ex(pcmdpriv, ph2c);
पूर्ण

व्योम r8712_survey_cmd_callback(काष्ठा _adapter *padapter, काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res != H2C_SUCCESS)
		clr_fwstate(pmlmepriv, _FW_UNDER_SURVEY);
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_disassoc_cmd_callback(काष्ठा _adapter *padapter,
				 काष्ठा cmd_obj *pcmd)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res != H2C_SUCCESS) अणु
		spin_lock_irqsave(&pmlmepriv->lock, irqL);
		set_fwstate(pmlmepriv, _FW_LINKED);
		spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
		वापस;
	पूर्ण
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_joinbss_cmd_callback(काष्ठा _adapter *padapter, काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (pcmd->res != H2C_SUCCESS)
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_createbss_cmd_callback(काष्ठा _adapter *padapter,
				  काष्ठा cmd_obj *pcmd)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pnetwork = (काष्ठा wlan_bssid_ex *)pcmd->parmbuf;
	काष्ठा wlan_network *tgt_network = &(pmlmepriv->cur_network);

	अगर (pcmd->res != H2C_SUCCESS)
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
	del_समयr(&pmlmepriv->assoc_समयr);
#अगर_घोषित __BIG_ENDIAN
	/* endian_convert */
	pnetwork->Length = le32_to_cpu(pnetwork->Length);
	pnetwork->Ssid.SsidLength = le32_to_cpu(pnetwork->Ssid.SsidLength);
	pnetwork->Privacy = le32_to_cpu(pnetwork->Privacy);
	pnetwork->Rssi = le32_to_cpu(pnetwork->Rssi);
	pnetwork->NetworkTypeInUse = le32_to_cpu(pnetwork->NetworkTypeInUse);
	pnetwork->Configuration.ATIMWinकरोw =
		le32_to_cpu(pnetwork->Configuration.ATIMWinकरोw);
	pnetwork->Configuration.DSConfig =
		le32_to_cpu(pnetwork->Configuration.DSConfig);
	pnetwork->Configuration.FHConfig.DwellTime =
		le32_to_cpu(pnetwork->Configuration.FHConfig.DwellTime);
	pnetwork->Configuration.FHConfig.HopPattern =
		le32_to_cpu(pnetwork->Configuration.FHConfig.HopPattern);
	pnetwork->Configuration.FHConfig.HopSet =
		le32_to_cpu(pnetwork->Configuration.FHConfig.HopSet);
	pnetwork->Configuration.FHConfig.Length =
		le32_to_cpu(pnetwork->Configuration.FHConfig.Length);
	pnetwork->Configuration.Length =
		le32_to_cpu(pnetwork->Configuration.Length);
	pnetwork->Infraकाष्ठाureMode =
		le32_to_cpu(pnetwork->Infraकाष्ठाureMode);
	pnetwork->IELength = le32_to_cpu(pnetwork->IELength);
#पूर्ण_अगर
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर ((pmlmepriv->fw_state) & WIFI_AP_STATE) अणु
		psta = r8712_get_stainfo(&padapter->stapriv,
					 pnetwork->MacAddress);
		अगर (!psta) अणु
			psta = r8712_alloc_stainfo(&padapter->stapriv,
						   pnetwork->MacAddress);
			अगर (!psta)
				जाओ createbss_cmd_fail;
		पूर्ण
		r8712_indicate_connect(padapter);
	पूर्ण अन्यथा अणु
		pwlan = _r8712_alloc_network(pmlmepriv);
		अगर (!pwlan) अणु
			pwlan = r8712_get_oldest_wlan_network(
				&pmlmepriv->scanned_queue);
			अगर (!pwlan)
				जाओ createbss_cmd_fail;
			pwlan->last_scanned = jअगरfies;
		पूर्ण अन्यथा अणु
			list_add_tail(&(pwlan->list),
					 &pmlmepriv->scanned_queue.queue);
		पूर्ण
		pnetwork->Length = r8712_get_wlan_bssid_ex_sz(pnetwork);
		स_नकल(&(pwlan->network), pnetwork, pnetwork->Length);
		pwlan->fixed = true;
		स_नकल(&tgt_network->network, pnetwork,
			(r8712_get_wlan_bssid_ex_sz(pnetwork)));
		अगर (pmlmepriv->fw_state & _FW_UNDER_LINKING)
			pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
		/*
		 * we will set _FW_LINKED when there is one more sat to
		 * join us (stassoc_event_callback)
		 */
	पूर्ण
createbss_cmd_fail:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_setstaKey_cmdrsp_callback(काष्ठा _adapter *padapter,
				     काष्ठा cmd_obj *pcmd)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा set_stakey_rsp *psetstakey_rsp = (काष्ठा set_stakey_rsp *)
						(pcmd->rsp);
	काष्ठा sta_info *psta = r8712_get_stainfo(pstapriv,
						  psetstakey_rsp->addr);

	अगर (!psta)
		जाओ निकास;
	psta->aid = psta->mac_id = psetstakey_rsp->keyid; /*CAM_ID(CAM_ENTRY)*/
निकास:
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_setassocsta_cmdrsp_callback(काष्ठा _adapter *padapter,
				       काष्ठा cmd_obj *pcmd)
अणु
	अचिन्हित दीर्घ	irqL;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा set_assocsta_parm *passocsta_parm =
				(काष्ठा set_assocsta_parm *)(pcmd->parmbuf);
	काष्ठा set_assocsta_rsp *passocsta_rsp =
				(काष्ठा set_assocsta_rsp *) (pcmd->rsp);
	काष्ठा sta_info *psta = r8712_get_stainfo(pstapriv,
						  passocsta_parm->addr);

	अगर (!psta)
		वापस;
	psta->aid = psta->mac_id = passocsta_rsp->cam_id;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर ((check_fwstate(pmlmepriv, WIFI_MP_STATE)) &&
	    (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)))
		pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
	set_fwstate(pmlmepriv, _FW_LINKED);
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	r8712_मुक्त_cmd_obj(pcmd);
पूर्ण

व्योम r8712_disconnectCtrlEx_cmd(काष्ठा _adapter *adapter, u32 enableDrvCtrl,
			u32 tryPktCnt, u32 tryPktInterval, u32 firstStageTO)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा DisconnectCtrlEx_param *param;
	काष्ठा cmd_priv *pcmdpriv = &adapter->cmdpriv;

	ph2c = kदो_स्मृति(माप(*ph2c), GFP_ATOMIC);
	अगर (!ph2c)
		वापस;
	param = kzalloc(माप(*param), GFP_ATOMIC);
	अगर (!param) अणु
		kमुक्त(ph2c);
		वापस;
	पूर्ण

	param->EnableDrvCtrl = (अचिन्हित अक्षर)enableDrvCtrl;
	param->TryPktCnt = (अचिन्हित अक्षर)tryPktCnt;
	param->TryPktInterval = (अचिन्हित अक्षर)tryPktInterval;
	param->FirstStageTO = (अचिन्हित पूर्णांक)firstStageTO;

	init_h2fwcmd_w_parm_no_rsp(ph2c, param,
				GEN_CMD_CODE(_DisconnectCtrlEx));
	r8712_enqueue_cmd(pcmdpriv, ph2c);
पूर्ण
