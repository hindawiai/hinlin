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
#अगर_अघोषित __USB_OPS_H_
#घोषणा __USB_OPS_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"

व्योम r8712_usb_ग_लिखो_mem(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr,
			 u32 cnt, u8 *wmem);
u32 r8712_usb_ग_लिखो_port(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr,
			 u32 cnt, u8 *wmem);
u32 r8712_usb_पढ़ो_port(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr,
			u32 cnt, u8 *rmem);
व्योम r8712_usb_set_पूर्णांकf_option(u32 *poption);
व्योम r8712_usb_set_पूर्णांकf_funs(काष्ठा पूर्णांकf_hdl *pपूर्णांकf_hdl);
uपूर्णांक r8712_usb_init_पूर्णांकf_priv(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv);
व्योम r8712_usb_unload_पूर्णांकf_priv(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv);
व्योम r8712_usb_set_पूर्णांकf_ops(काष्ठा _io_ops *pops);
व्योम r8712_usb_पढ़ो_port_cancel(काष्ठा _adapter *padapter);
व्योम r8712_usb_ग_लिखो_port_cancel(काष्ठा _adapter *padapter);
पूर्णांक r8712_usbctrl_venकरोrreq(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u8 request, u16 value,
			    u16 index, व्योम *pdata, u16 len, u8 requesttype);

#पूर्ण_अगर

