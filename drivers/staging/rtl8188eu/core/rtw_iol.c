<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <rtw_iol.h>

bool rtw_iol_applied(काष्ठा adapter *adapter)
अणु
	अगर (adapter->registrypriv.fw_iol == 1)
		वापस true;

	अगर (adapter->registrypriv.fw_iol == 2 &&
	    !adapter_to_dvobj(adapter)->ishighspeed)
		वापस true;
	वापस false;
पूर्ण
