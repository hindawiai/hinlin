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
#अगर_अघोषित __IOCTL_SET_H
#घोषणा __IOCTL_SET_H

#समावेश "drv_types.h"

प्रकार u8 NDIS_802_11_PMKID_VALUE[16];

काष्ठा BSSIDInfo अणु
	अचिन्हित अक्षर BSSID[6];
	NDIS_802_11_PMKID_VALUE PMKID;
पूर्ण;

u8 r8712_set_802_11_authentication_mode(काष्ठा _adapter *pdapter,
			क्रमागत NDIS_802_11_AUTHENTICATION_MODE authmode);

u8 r8712_set_802_11_bssid(काष्ठा _adapter *padapter, u8 *bssid);

पूर्णांक r8712_set_802_11_add_wep(काष्ठा _adapter *padapter,
			     काष्ठा NDIS_802_11_WEP *wep);

u8 r8712_set_802_11_disassociate(काष्ठा _adapter *padapter);

u8 r8712_set_802_11_bssid_list_scan(काष्ठा _adapter *padapter);

व्योम r8712_set_802_11_infraकाष्ठाure_mode(काष्ठा _adapter *padapter,
			क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE networktype);

व्योम r8712_set_802_11_ssid(काष्ठा _adapter *padapter,
			   काष्ठा ndis_802_11_ssid *ssid);

#पूर्ण_अगर

