<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित	__MLME_OSDEP_H_
#घोषणा __MLME_OSDEP_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

व्योम rtw_init_mlme_समयr(काष्ठा adapter *padapter);
व्योम rtw_os_indicate_disconnect(काष्ठा adapter *adapter);
व्योम rtw_os_indicate_connect(काष्ठा adapter *adapter);
व्योम rtw_report_sec_ie(काष्ठा adapter *adapter, u8 authmode, u8 *sec_ie);

व्योम rtw_reset_securitypriv(काष्ठा adapter *adapter);
व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter);

#पूर्ण_अगर	/* _MLME_OSDEP_H_ */
