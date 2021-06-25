<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_ioctl_set.c
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

#घोषणा _RTL871X_IOCTL_SET_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "rtl871x_ioctl_set.h"
#समावेश "usb_osintf.h"
#समावेश "usb_ops.h"


अटल u8 validate_ssid(काष्ठा ndis_802_11_ssid *ssid)
अणु
	u8 i;

	अगर (ssid->SsidLength > 32)
		वापस false;
	क्रम (i = 0; i < ssid->SsidLength; i++) अणु
		/* wअगरi, prपूर्णांकable ascii code must be supported */
		अगर (!((ssid->Ssid[i] >= 0x20) && (ssid->Ssid[i] <= 0x7e)))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल u8 करो_join(काष्ठा _adapter *padapter)
अणु
	काष्ठा list_head *plist, *phead;
	u8 *pibss = शून्य;
	काष्ठा	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	काष्ठा  __queue	*queue	= &(pmlmepriv->scanned_queue);
	पूर्णांक ret;

	phead = &queue->queue;
	plist = phead->next;
	pmlmepriv->cur_network.join_res = -2;
	pmlmepriv->fw_state |= _FW_UNDER_LINKING;
	pmlmepriv->pscanned = plist;
	pmlmepriv->to_join = true;

	/* adhoc mode will start with an empty queue, but skip checking */
	अगर (!check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) &&
	    list_empty(&queue->queue)) अणु
		अगर (pmlmepriv->fw_state & _FW_UNDER_LINKING)
			pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
		/* when set_ssid/set_bssid क्रम करो_join(), but scanning queue
		 * is empty we try to issue sitesurvey firstly
		 */
		अगर (!pmlmepriv->sitesurveyctrl.traffic_busy)
			r8712_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid);
		वापस true;
	पूर्ण

	ret = r8712_select_and_join_from_scan(pmlmepriv);
	अगर (!ret) अणु
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
	पूर्ण अन्यथा अणु
		अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
			/* submit r8712_createbss_cmd to change to an
			 * ADHOC_MASTER pmlmepriv->lock has been
			 * acquired by caller...
			 */
			काष्ठा wlan_bssid_ex *pdev_network =
				&(padapter->registrypriv.dev_network);
			pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;
			pibss = padapter->registrypriv.dev_network.MacAddress;
			स_नकल(&pdev_network->Ssid,
			       &pmlmepriv->assoc_ssid,
			       माप(काष्ठा ndis_802_11_ssid));
			r8712_update_registrypriv_dev_network(padapter);
			r8712_generate_अक्रमom_ibss(pibss);
			अगर (r8712_createbss_cmd(padapter))
				वापस false;
			pmlmepriv->to_join = false;
		पूर्ण अन्यथा अणु
			/* can't associate ; reset under-linking */
			अगर (pmlmepriv->fw_state & _FW_UNDER_LINKING)
				pmlmepriv->fw_state ^=
					_FW_UNDER_LINKING;
			/* when set_ssid/set_bssid क्रम करो_join(), but
			 * there are no desired bss in scanning queue
			 * we try to issue sitesurvey first
			 */
			अगर (!pmlmepriv->sitesurveyctrl.traffic_busy)
				r8712_sitesurvey_cmd(padapter,
						     &pmlmepriv->assoc_ssid);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

u8 r8712_set_802_11_bssid(काष्ठा _adapter *padapter, u8 *bssid)
अणु
	अचिन्हित दीर्घ irqL;
	u8 status = true;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (is_zero_ether_addr(bssid) || is_broadcast_ether_addr(bssid)) अणु
		status = false;
		वापस status;
	पूर्ण
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
	    _FW_UNDER_LINKING)) अणु
		status = check_fwstate(pmlmepriv, _FW_UNDER_LINKING);
		जाओ _Abort_Set_BSSID;
	पूर्ण
	अगर (check_fwstate(pmlmepriv,
	    _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		अगर (!स_भेद(&pmlmepriv->cur_network.network.MacAddress, bssid,
		    ETH_ALEN)) अणु
			अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				/* driver is in
				 * WIFI_ADHOC_MASTER_STATE
				 */
				जाओ _Abort_Set_BSSID;
		पूर्ण अन्यथा अणु
			r8712_disassoc_cmd(padapter);
			अगर (check_fwstate(pmlmepriv, _FW_LINKED))
				r8712_ind_disconnect(padapter);
			r8712_मुक्त_assoc_resources(padapter);
			अगर ((check_fwstate(pmlmepriv,
			     WIFI_ADHOC_MASTER_STATE))) अणु
				_clr_fwstate_(pmlmepriv,
					      WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण
	स_नकल(&pmlmepriv->assoc_bssid, bssid, ETH_ALEN);
	pmlmepriv->assoc_by_bssid = true;
	status = करो_join(padapter);
	जाओ करोne;
_Abort_Set_BSSID:
करोne:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	वापस status;
पूर्ण

व्योम r8712_set_802_11_ssid(काष्ठा _adapter *padapter,
			   काष्ठा ndis_802_11_ssid *ssid)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *pnetwork = &pmlmepriv->cur_network;

	अगर (!padapter->hw_init_completed)
		वापस;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING)) अणु
		check_fwstate(pmlmepriv, _FW_UNDER_LINKING);
		जाओ _Abort_Set_SSID;
	पूर्ण
	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		अगर ((pmlmepriv->assoc_ssid.SsidLength == ssid->SsidLength) &&
		    (!स_भेद(&pmlmepriv->assoc_ssid.Ssid, ssid->Ssid,
		    ssid->SsidLength))) अणु
			अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
				अगर (!r8712_is_same_ibss(padapter,
				     pnetwork)) अणु
					/* अगर in WIFI_ADHOC_MASTER_STATE or
					 *  WIFI_ADHOC_STATE, create bss or
					 * rejoin again
					 */
					r8712_disassoc_cmd(padapter);
					अगर (check_fwstate(pmlmepriv,
					    _FW_LINKED))
						r8712_ind_disconnect(padapter);
					r8712_मुक्त_assoc_resources(padapter);
					अगर (check_fwstate(pmlmepriv,
					     WIFI_ADHOC_MASTER_STATE)) अणु
						_clr_fwstate_(pmlmepriv,
						    WIFI_ADHOC_MASTER_STATE);
						set_fwstate(pmlmepriv,
							    WIFI_ADHOC_STATE);
					पूर्ण
				पूर्ण अन्यथा अणु
					/* driver is in
					 * WIFI_ADHOC_MASTER_STATE
					 */
					जाओ _Abort_Set_SSID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			r8712_disassoc_cmd(padapter);
			अगर (check_fwstate(pmlmepriv, _FW_LINKED))
				r8712_ind_disconnect(padapter);
			r8712_मुक्त_assoc_resources(padapter);
			अगर (check_fwstate(pmlmepriv,
			    WIFI_ADHOC_MASTER_STATE)) अणु
				_clr_fwstate_(pmlmepriv,
					      WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (padapter->securitypriv.btkip_countermeasure)
		जाओ _Abort_Set_SSID;
	अगर (!validate_ssid(ssid))
		जाओ _Abort_Set_SSID;
	स_नकल(&pmlmepriv->assoc_ssid, ssid, माप(काष्ठा ndis_802_11_ssid));
	pmlmepriv->assoc_by_bssid = false;
	करो_join(padapter);
	जाओ करोne;
_Abort_Set_SSID:
करोne:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

व्योम r8712_set_802_11_infraकाष्ठाure_mode(काष्ठा _adapter *padapter,
	क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network	*cur_network = &pmlmepriv->cur_network;
	क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE *pold_state =
				&(cur_network->network.Infraकाष्ठाureMode);

	अगर (*pold_state != networktype) अणु
		spin_lock_irqsave(&pmlmepriv->lock, irqL);
		अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    (*pold_state == Ndis802_11IBSS))
			r8712_disassoc_cmd(padapter);
		अगर (check_fwstate(pmlmepriv,
		    _FW_LINKED | WIFI_ADHOC_MASTER_STATE))
			r8712_मुक्त_assoc_resources(padapter);
		अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    (*pold_state == Ndis802_11Infraकाष्ठाure) ||
		    (*pold_state == Ndis802_11IBSS)) अणु
			/* will clr Linked_state beक्रमe this function,
			 * we must have checked whether issue dis-assoc_cmd or
			 * not
			 */
			r8712_ind_disconnect(padapter);
		पूर्ण
		*pold_state = networktype;
		/* clear WIFI_STATION_STATE; WIFI_AP_STATE; WIFI_ADHOC_STATE;
		 * WIFI_ADHOC_MASTER_STATE
		 */
		_clr_fwstate_(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE |
			      WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE);
		चयन (networktype) अणु
		हाल Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			अवरोध;
		हाल Ndis802_11Infraकाष्ठाure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			अवरोध;
		हाल Ndis802_11APMode:
			set_fwstate(pmlmepriv, WIFI_AP_STATE);
			अवरोध;
		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	पूर्ण
पूर्ण

u8 r8712_set_802_11_disassociate(काष्ठा _adapter *padapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		r8712_disassoc_cmd(padapter);
		r8712_ind_disconnect(padapter);
		r8712_मुक्त_assoc_resources(padapter);
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	वापस true;
पूर्ण

u8 r8712_set_802_11_bssid_list_scan(काष्ठा _adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = शून्य;
	अचिन्हित दीर्घ irqL;
	u8 ret = true;

	अगर (!padapter)
		वापस false;
	pmlmepriv = &padapter->mlmepriv;
	अगर (!padapter->hw_init_completed)
		वापस false;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING) ||
	    pmlmepriv->sitesurveyctrl.traffic_busy) अणु
		/* Scan or linking is in progress, करो nothing. */
		ret = (u8)check_fwstate(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण अन्यथा अणु
		r8712_मुक्त_network_queue(padapter);
		ret = r8712_sitesurvey_cmd(padapter, शून्य);
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	वापस ret;
पूर्ण

u8 r8712_set_802_11_authentication_mode(काष्ठा _adapter *padapter,
				क्रमागत NDIS_802_11_AUTHENTICATION_MODE authmode)
अणु
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u8 ret;

	psecuritypriv->ndisauthtype = authmode;
	अगर (psecuritypriv->ndisauthtype > 3)
		psecuritypriv->AuthAlgrthm = 2; /* 802.1x */
	अगर (r8712_set_auth(padapter, psecuritypriv))
		ret = false;
	अन्यथा
		ret = true;
	वापस ret;
पूर्ण

पूर्णांक r8712_set_802_11_add_wep(काष्ठा _adapter *padapter,
			     काष्ठा NDIS_802_11_WEP *wep)
अणु
	sपूर्णांक	keyid;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	keyid = wep->KeyIndex & 0x3fffffff;
	अगर (keyid >= WEP_KEYS)
		वापस -EINVAL;
	चयन (wep->KeyLength) अणु
	हाल 5:
		psecuritypriv->PrivacyAlgrthm = _WEP40_;
		अवरोध;
	हाल 13:
		psecuritypriv->PrivacyAlgrthm = _WEP104_;
		अवरोध;
	शेष:
		psecuritypriv->PrivacyAlgrthm = _NO_PRIVACY_;
		अवरोध;
	पूर्ण
	स_नकल(psecuritypriv->DefKey[keyid].skey, &wep->KeyMaterial,
		wep->KeyLength);
	psecuritypriv->DefKeylen[keyid] = wep->KeyLength;
	psecuritypriv->PrivacyKeyIndex = keyid;
	वापस r8712_set_key(padapter, psecuritypriv, keyid);
पूर्ण
