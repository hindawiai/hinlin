<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_IOCTL_SET_H_
#घोषणा __RTW_IOCTL_SET_H_

#समावेश <drv_types.h>

प्रकार u8 NDIS_802_11_PMKID_VALUE[16];

u8 rtw_set_802_11_authentication_mode(काष्ठा adapter *adapt,
				      क्रमागत ndis_802_11_auth_mode authmode);
u8 rtw_set_802_11_bssid(काष्ठा adapter *adapter, u8 *bssid);
u8 rtw_set_802_11_add_wep(काष्ठा adapter *adapter, काष्ठा ndis_802_11_wep *wep);
u8 rtw_set_802_11_disassociate(काष्ठा adapter *adapter);
u8 rtw_set_802_11_bssid_list_scan(काष्ठा adapter *adapter,
				  काष्ठा ndis_802_11_ssid *pssid,
				  पूर्णांक ssid_max_num);
u8 rtw_set_802_11_infraकाष्ठाure_mode(काष्ठा adapter *adapter,
				      क्रमागत ndis_802_11_network_infra type);
u8 rtw_set_802_11_ssid(काष्ठा adapter *adapt, काष्ठा ndis_802_11_ssid *ssid);
u16 rtw_get_cur_max_rate(काष्ठा adapter *adapter);
पूर्णांक rtw_set_country(काष्ठा adapter *adapter, स्थिर अक्षर *country_code);

#पूर्ण_अगर
