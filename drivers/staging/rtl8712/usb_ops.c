<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * usb_ops.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _HCI_OPS_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"
#समावेश "recv_osdep.h"

अटल u8 usb_पढ़ो8(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x01; /* पढ़ो_in */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 1;
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
	वापस (u8)(le32_to_cpu(data) & 0x0ff);
पूर्ण

अटल u16 usb_पढ़ो16(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x01; /* पढ़ो_in */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 2;
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
	वापस (u16)(le32_to_cpu(data) & 0xffff);
पूर्ण

अटल u32 usb_पढ़ो32(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x01; /* पढ़ो_in */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 4;
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
	वापस le32_to_cpu(data);
पूर्ण

अटल व्योम usb_ग_लिखो8(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u8 val)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x00; /* ग_लिखो_out */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 1;
	data = cpu_to_le32((u32)val & 0x000000ff);
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
पूर्ण

अटल व्योम usb_ग_लिखो16(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u16 val)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x00; /* ग_लिखो_out */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 2;
	data = cpu_to_le32((u32)val & 0x0000ffff);
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
पूर्ण

अटल व्योम usb_ग_लिखो32(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl, u32 addr, u32 val)
अणु
	u8 request;
	u8 requesttype;
	u16 wvalue;
	u16 index;
	u16 len;
	__le32 data;
	काष्ठा पूर्णांकf_priv *पूर्णांकfpriv = पूर्णांकfhdl->pपूर्णांकfpriv;

	request = 0x05;
	requesttype = 0x00; /* ग_लिखो_out */
	index = 0;
	wvalue = (u16)(addr & 0x0000ffff);
	len = 4;
	data = cpu_to_le32(val);
	r8712_usbctrl_venकरोrreq(पूर्णांकfpriv, request, wvalue, index, &data, len,
				requesttype);
पूर्ण

व्योम r8712_usb_set_पूर्णांकf_option(u32 *option)
अणु
	*option = ((*option) | _INTF_ASYNC_);
पूर्ण

अटल व्योम usb_पूर्णांकf_hdl_init(u8 *priv)
अणु
पूर्ण

अटल व्योम usb_पूर्णांकf_hdl_unload(u8 *priv)
अणु
पूर्ण

अटल व्योम usb_पूर्णांकf_hdl_खोलो(u8 *priv)
अणु
पूर्ण

अटल व्योम usb_पूर्णांकf_hdl_बंद(u8 *priv)
अणु
पूर्ण

व्योम r8712_usb_set_पूर्णांकf_funs(काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl)
अणु
	पूर्णांकfhdl->पूर्णांकf_hdl_init = usb_पूर्णांकf_hdl_init;
	पूर्णांकfhdl->पूर्णांकf_hdl_unload = usb_पूर्णांकf_hdl_unload;
	पूर्णांकfhdl->पूर्णांकf_hdl_खोलो = usb_पूर्णांकf_hdl_खोलो;
	पूर्णांकfhdl->पूर्णांकf_hdl_बंद = usb_पूर्णांकf_hdl_बंद;
पूर्ण

व्योम r8712_usb_set_पूर्णांकf_ops(काष्ठा _io_ops *ops)
अणु
	स_रखो((u8 *)ops, 0, माप(काष्ठा _io_ops));
	ops->_पढ़ो8 = usb_पढ़ो8;
	ops->_पढ़ो16 = usb_पढ़ो16;
	ops->_पढ़ो32 = usb_पढ़ो32;
	ops->_पढ़ो_port = r8712_usb_पढ़ो_port;
	ops->_ग_लिखो8 = usb_ग_लिखो8;
	ops->_ग_लिखो16 = usb_ग_लिखो16;
	ops->_ग_लिखो32 = usb_ग_लिखो32;
	ops->_ग_लिखो_mem = r8712_usb_ग_लिखो_mem;
	ops->_ग_लिखो_port = r8712_usb_ग_लिखो_port;
पूर्ण
