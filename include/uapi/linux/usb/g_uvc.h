<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * g_uvc.h  --  USB Video Class Gadget driver API
 *
 * Copyright (C) 2009-2010 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __LINUX_USB_G_UVC_H
#घोषणा __LINUX_USB_G_UVC_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/ch9.h>

#घोषणा UVC_EVENT_FIRST			(V4L2_EVENT_PRIVATE_START + 0)
#घोषणा UVC_EVENT_CONNECT		(V4L2_EVENT_PRIVATE_START + 0)
#घोषणा UVC_EVENT_DISCONNECT		(V4L2_EVENT_PRIVATE_START + 1)
#घोषणा UVC_EVENT_STREAMON		(V4L2_EVENT_PRIVATE_START + 2)
#घोषणा UVC_EVENT_STREAMOFF		(V4L2_EVENT_PRIVATE_START + 3)
#घोषणा UVC_EVENT_SETUP			(V4L2_EVENT_PRIVATE_START + 4)
#घोषणा UVC_EVENT_DATA			(V4L2_EVENT_PRIVATE_START + 5)
#घोषणा UVC_EVENT_LAST			(V4L2_EVENT_PRIVATE_START + 5)

काष्ठा uvc_request_data अणु
	__s32 length;
	__u8 data[60];
पूर्ण;

काष्ठा uvc_event अणु
	जोड़ अणु
		क्रमागत usb_device_speed speed;
		काष्ठा usb_ctrlrequest req;
		काष्ठा uvc_request_data data;
	पूर्ण;
पूर्ण;

#घोषणा UVCIOC_SEND_RESPONSE		_IOW('U', 1, काष्ठा uvc_request_data)

#पूर्ण_अगर /* __LINUX_USB_G_UVC_H */
