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
#अगर_अघोषित __USB_OSINTF_H
#घोषणा __USB_OSINTF_H

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

बाह्य अक्षर *r8712_iniपंचांगac;

अचिन्हित पूर्णांक r8712_usb_inirp_init(काष्ठा _adapter *padapter);
अचिन्हित पूर्णांक r8712_usb_inirp_deinit(काष्ठा _adapter *padapter);
uपूर्णांक rtl871x_hal_init(काष्ठा _adapter *padapter);
uपूर्णांक rtl8712_hal_deinit(काष्ठा _adapter *padapter);

व्योम rtl871x_पूर्णांकf_stop(काष्ठा _adapter *padapter);
व्योम r871x_dev_unload(काष्ठा _adapter *padapter);
व्योम r8712_stop_drv_thपढ़ोs(काष्ठा _adapter *padapter);
व्योम r8712_stop_drv_समयrs(काष्ठा _adapter *padapter);
पूर्णांक r8712_init_drv_sw(काष्ठा _adapter *padapter);
व्योम r8712_मुक्त_drv_sw(काष्ठा _adapter *padapter);
काष्ठा net_device *r8712_init_netdev(व्योम);

#पूर्ण_अगर
