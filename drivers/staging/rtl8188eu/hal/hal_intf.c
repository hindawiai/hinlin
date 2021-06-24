<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#घोषणा _HAL_INTF_C_
#समावेश <hal_पूर्णांकf.h>

uपूर्णांक rtw_hal_init(काष्ठा adapter *adapt)
अणु
	uपूर्णांक status = _SUCCESS;

	adapt->hw_init_completed = false;

	status = rtl8188eu_hal_init(adapt);

	अगर (status == _SUCCESS) अणु
		adapt->hw_init_completed = true;

		अगर (adapt->registrypriv.notch_filter == 1)
			rtw_hal_notch_filter(adapt, 1);
	पूर्ण अन्यथा अणु
		adapt->hw_init_completed = false;
		DBG_88E("%s: hal__init fail\n", __func__);
	पूर्ण

	RT_TRACE(_module_hal_init_c_, _drv_err_,
		 ("-rtl871x_hal_init:status=0x%x\n", status));

	वापस status;
पूर्ण

uपूर्णांक rtw_hal_deinit(काष्ठा adapter *adapt)
अणु
	uपूर्णांक status = _SUCCESS;

	status = rtl8188eu_hal_deinit(adapt);

	अगर (status == _SUCCESS)
		adapt->hw_init_completed = false;
	अन्यथा
		DBG_88E("\n %s: hal_init fail\n", __func__);

	वापस status;
पूर्ण

व्योम rtw_hal_update_ra_mask(काष्ठा adapter *adapt, u32 mac_id, u8 rssi_level)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapt->mlmepriv;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
#अगर_घोषित CONFIG_88EU_AP_MODE
		काष्ठा sta_info *psta = शून्य;
		काष्ठा sta_priv *pstapriv = &adapt->stapriv;

		अगर (mac_id - 1 > 0)
			psta = pstapriv->sta_aid[mac_id - 2];
		अगर (psta)
			add_RATid(adapt, psta, 0);/* toकरो: based on rssi_level*/
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		UpdateHalRAMask8188EUsb(adapt, mac_id, rssi_level);
	पूर्ण
पूर्ण
