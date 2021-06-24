<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl8712_io.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL8712_IO_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "rtl871x_io.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"

u8 r8712_पढ़ो8(काष्ठा _adapter *adapter, u32 addr)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	वापस hdl->io_ops._पढ़ो8(hdl, addr);
पूर्ण

u16 r8712_पढ़ो16(काष्ठा _adapter *adapter, u32 addr)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	वापस hdl->io_ops._पढ़ो16(hdl, addr);
पूर्ण

u32 r8712_पढ़ो32(काष्ठा _adapter *adapter, u32 addr)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	वापस hdl->io_ops._पढ़ो32(hdl, addr);
पूर्ण

व्योम r8712_ग_लिखो8(काष्ठा _adapter *adapter, u32 addr, u8 val)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	hdl->io_ops._ग_लिखो8(hdl, addr, val);
पूर्ण

व्योम r8712_ग_लिखो16(काष्ठा _adapter *adapter, u32 addr, u16 val)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	hdl->io_ops._ग_लिखो16(hdl, addr, val);
पूर्ण

व्योम r8712_ग_लिखो32(काष्ठा _adapter *adapter, u32 addr, u32 val)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	hdl->io_ops._ग_लिखो32(hdl, addr, val);
पूर्ण

व्योम r8712_पढ़ो_mem(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	अगर (adapter->driver_stopped || adapter->surprise_हटाओd)
		वापस;

	hdl->io_ops._पढ़ो_mem(hdl, addr, cnt, pmem);
पूर्ण

व्योम r8712_ग_लिखो_mem(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	hdl->io_ops._ग_लिखो_mem(hdl, addr, cnt, pmem);
पूर्ण

व्योम r8712_पढ़ो_port(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	अगर (adapter->driver_stopped || adapter->surprise_हटाओd)
		वापस;

	hdl->io_ops._पढ़ो_port(hdl, addr, cnt, pmem);
पूर्ण

व्योम r8712_ग_लिखो_port(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem)
अणु
	काष्ठा पूर्णांकf_hdl *hdl = &adapter->pio_queue->पूर्णांकf;

	hdl->io_ops._ग_लिखो_port(hdl, addr, cnt, pmem);
पूर्ण
