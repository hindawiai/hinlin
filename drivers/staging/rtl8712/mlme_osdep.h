<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित	__MLME_OSDEP_H_
#घोषणा __MLME_OSDEP_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

व्योम r8712_init_mlme_समयr(काष्ठा _adapter *padapter);
व्योम r8712_os_indicate_disconnect(काष्ठा _adapter *adapter);
व्योम r8712_os_indicate_connect(काष्ठा _adapter *adapter);
व्योम r8712_report_sec_ie(काष्ठा _adapter *adapter, u8 authmode, u8 *sec_ie);
पूर्णांक r8712_recv_indicatepkts_in_order(काष्ठा _adapter *adapter,
				     काष्ठा recv_reorder_ctrl *precvreorder_ctrl,
				     पूर्णांक bक्रमced);
व्योम r8712_indicate_wx_assoc_event(काष्ठा _adapter *padapter);
व्योम r8712_indicate_wx_disassoc_event(काष्ठा _adapter *padapter);

#पूर्ण_अगर	/*_MLME_OSDEP_H_*/

