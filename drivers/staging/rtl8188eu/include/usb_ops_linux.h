<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __USB_OPS_LINUX_H__
#घोषणा __USB_OPS_LINUX_H__

#घोषणा USB_HIGH_SPEED_BULK_SIZE	512
#घोषणा USB_FULL_SPEED_BULK_SIZE	64

u8 usb_पढ़ो8(काष्ठा adapter *adapter, u32 addr);
u16 usb_पढ़ो16(काष्ठा adapter *adapter, u32 addr);
u32 usb_पढ़ो32(काष्ठा adapter *adapter, u32 addr);

u32 usb_पढ़ो_port(काष्ठा adapter *adapter, u32 addr, काष्ठा recv_buf *precvbuf);

पूर्णांक usb_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val);
पूर्णांक usb_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val);
पूर्णांक usb_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val);

u32 usb_ग_लिखो_port(काष्ठा adapter *adapter, u32 addr, u32 cnt, काष्ठा xmit_buf *pmem);
व्योम usb_ग_लिखो_port_cancel(काष्ठा adapter *adapter);

#पूर्ण_अगर
