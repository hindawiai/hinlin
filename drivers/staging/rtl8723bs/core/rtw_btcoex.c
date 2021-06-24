<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_btcoex.h>
#समावेश <hal_btcoex.h>

व्योम rtw_btcoex_MediaStatusNotअगरy(काष्ठा adapter *padapter, u8 mediaStatus)
अणु
	अगर ((mediaStatus == RT_MEDIA_CONNECT)
		&& (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true)) अणु
		rtw_hal_set_hwreg(padapter, HW_VAR_DL_RSVD_PAGE, शून्य);
	पूर्ण

	hal_btcoex_MediaStatusNotअगरy(padapter, mediaStatus);
पूर्ण

व्योम rtw_btcoex_HaltNotअगरy(काष्ठा adapter *padapter)
अणु
	अगर (!padapter->bup)
		वापस;

	अगर (padapter->bSurpriseRemoved)
		वापस;

	hal_btcoex_HaltNotअगरy(padapter);
पूर्ण

/*  ================================================== */
/*  Below Functions are called by BT-Coex */
/*  ================================================== */
व्योम rtw_btcoex_RejectApAggregatedPacket(काष्ठा adapter *padapter, u8 enable)
अणु
	काष्ठा mlme_ext_info *pmlmeinfo;
	काष्ठा sta_info *psta;

	pmlmeinfo = &padapter->mlmeextpriv.mlmext_info;
	psta = rtw_get_stainfo(&padapter->stapriv, get_bssid(&padapter->mlmepriv));

	अगर (enable) अणु
		pmlmeinfo->accept_addba_req = false;
		अगर (psta)
			send_delba(padapter, 0, psta->hwaddr);
	पूर्ण अन्यथा अणु
		pmlmeinfo->accept_addba_req = true;
	पूर्ण
पूर्ण

व्योम rtw_btcoex_LPS_Enter(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;
	u8 lpsVal;


	pwrpriv = adapter_to_pwrctl(padapter);

	pwrpriv->bघातer_saving = true;
	lpsVal = hal_btcoex_LpsVal(padapter);
	rtw_set_ps_mode(padapter, PS_MODE_MIN, 0, lpsVal, "BTCOEX");
पूर्ण

व्योम rtw_btcoex_LPS_Leave(काष्ठा adapter *padapter)
अणु
	काष्ठा pwrctrl_priv *pwrpriv;


	pwrpriv = adapter_to_pwrctl(padapter);

	अगर (pwrpriv->pwr_mode != PS_MODE_ACTIVE) अणु
		rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0, "BTCOEX");
		LPS_RF_ON_check(padapter, 100);
		pwrpriv->bघातer_saving = false;
	पूर्ण
पूर्ण
