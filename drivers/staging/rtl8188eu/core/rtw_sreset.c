<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <rtw_sreset.h>
#समावेश <usb_ops_linux.h>

व्योम rtw_hal_sreset_init(काष्ठा adapter *padapter)
अणु
	काष्ठा sreset_priv *psrtpriv = &padapter->HalData->srestpriv;

	psrtpriv->wअगरi_error_status = WIFI_STATUS_SUCCESS;
पूर्ण

व्योम sreset_set_wअगरi_error_status(काष्ठा adapter *padapter, u32 status)
अणु
	padapter->HalData->srestpriv.wअगरi_error_status = status;
पूर्ण
