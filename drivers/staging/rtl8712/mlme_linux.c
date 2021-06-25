<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * mlme_linux.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _MLME_OSDEP_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "mlme_osdep.h"

अटल व्योम sitesurvey_ctrl_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t,
			   mlmepriv.sitesurveyctrl.sitesurvey_ctrl_समयr);

	_r8712_sitesurvey_ctrl_handler(adapter);
	mod_समयr(&adapter->mlmepriv.sitesurveyctrl.sitesurvey_ctrl_समयr,
		  jअगरfies + msecs_to_jअगरfies(3000));
पूर्ण

अटल व्योम join_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t, mlmepriv.assoc_समयr);

	_r8712_join_समयout_handler(adapter);
पूर्ण

अटल व्योम _scan_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t, mlmepriv.scan_to_समयr);

	r8712_scan_समयout_handler(adapter);
पूर्ण

अटल व्योम dhcp_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t, mlmepriv.dhcp_समयr);

	_r8712_dhcp_समयout_handler(adapter);
पूर्ण

अटल व्योम wdg_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा _adapter *adapter =
		from_समयr(adapter, t, mlmepriv.wdg_समयr);

	r8712_wdg_wk_cmd(adapter);

	mod_समयr(&adapter->mlmepriv.wdg_समयr,
		  jअगरfies + msecs_to_jअगरfies(2000));
पूर्ण

व्योम r8712_init_mlme_समयr(काष्ठा _adapter *adapter)
अणु
	काष्ठा	mlme_priv *mlmepriv = &adapter->mlmepriv;

	समयr_setup(&mlmepriv->assoc_समयr, join_समयout_handler, 0);
	समयr_setup(&mlmepriv->sitesurveyctrl.sitesurvey_ctrl_समयr,
		    sitesurvey_ctrl_handler, 0);
	समयr_setup(&mlmepriv->scan_to_समयr, _scan_समयout_handler, 0);
	समयr_setup(&mlmepriv->dhcp_समयr, dhcp_समयout_handler, 0);
	समयr_setup(&mlmepriv->wdg_समयr, wdg_समयout_handler, 0);
पूर्ण

व्योम r8712_os_indicate_connect(काष्ठा _adapter *adapter)
अणु
	r8712_indicate_wx_assoc_event(adapter);
	netअगर_carrier_on(adapter->pnetdev);
पूर्ण

अटल काष्ठा RT_PMKID_LIST   backupPMKIDList[NUM_PMKID_CACHE];
व्योम r8712_os_indicate_disconnect(काष्ठा _adapter *adapter)
अणु
	u8 backupPMKIDIndex = 0;
	u8 backupTKIPCountermeasure = 0x00;

	r8712_indicate_wx_disassoc_event(adapter);
	netअगर_carrier_off(adapter->pnetdev);
	अगर (adapter->securitypriv.AuthAlgrthm == 2) अणु /*/802.1x*/
		/* We have to backup the PMK inक्रमmation क्रम WiFi PMK Caching
		 * test item. Backup the btkip_countermeasure inक्रमmation.
		 * When the countermeasure is trigger, the driver have to
		 * disconnect with AP क्रम 60 seconds.
		 */

		स_नकल(&backupPMKIDList[0],
		       &adapter->securitypriv.PMKIDList[0],
		       माप(काष्ठा RT_PMKID_LIST) * NUM_PMKID_CACHE);
		backupPMKIDIndex = adapter->securitypriv.PMKIDIndex;
		backupTKIPCountermeasure =
			adapter->securitypriv.btkip_countermeasure;
		स_रखो((अचिन्हित अक्षर *)&adapter->securitypriv, 0,
		       माप(काष्ठा security_priv));
		समयr_setup(&adapter->securitypriv.tkip_समयr,
			    r8712_use_tkipkey_handler, 0);
		/* Restore the PMK inक्रमmation to securitypriv काष्ठाure
		 * क्रम the following connection.
		 */
		स_नकल(&adapter->securitypriv.PMKIDList[0],
		       &backupPMKIDList[0],
		       माप(काष्ठा RT_PMKID_LIST) * NUM_PMKID_CACHE);
		adapter->securitypriv.PMKIDIndex = backupPMKIDIndex;
		adapter->securitypriv.btkip_countermeasure =
					 backupTKIPCountermeasure;
	पूर्ण अन्यथा अणु /*reset values in securitypriv*/
		काष्ठा security_priv *sec_priv = &adapter->securitypriv;

		sec_priv->AuthAlgrthm = 0; /*खोलो प्रणाली*/
		sec_priv->PrivacyAlgrthm = _NO_PRIVACY_;
		sec_priv->PrivacyKeyIndex = 0;
		sec_priv->XGrpPrivacy = _NO_PRIVACY_;
		sec_priv->XGrpKeyid = 1;
		sec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		sec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
		sec_priv->wps_phase = false;
	पूर्ण
पूर्ण

व्योम r8712_report_sec_ie(काष्ठा _adapter *adapter, u8 authmode, u8 *sec_ie)
अणु
	uपूर्णांक len;
	u8 *buff, *p, i;
	जोड़ iwreq_data wrqu;

	buff = शून्य;
	अगर (authmode == _WPA_IE_ID_) अणु
		buff = kzalloc(IW_CUSTOM_MAX, GFP_ATOMIC);
		अगर (!buff)
			वापस;
		p = buff;
		p += प्र_लिखो(p, "ASSOCINFO(ReqIEs=");
		len = sec_ie[1] + 2;
		len =  (len < IW_CUSTOM_MAX) ? len : IW_CUSTOM_MAX;
		क्रम (i = 0; i < len; i++)
			p += प्र_लिखो(p, "%02x", sec_ie[i]);
		p += प्र_लिखो(p, ")");
		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.data.length = p - buff;
		wrqu.data.length = (wrqu.data.length < IW_CUSTOM_MAX) ?
				   wrqu.data.length : IW_CUSTOM_MAX;
		wireless_send_event(adapter->pnetdev, IWEVCUSTOM, &wrqu, buff);
		kमुक्त(buff);
	पूर्ण
पूर्ण
