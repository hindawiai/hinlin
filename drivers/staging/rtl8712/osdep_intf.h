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
#अगर_अघोषित __OSDEP_INTF_H_
#घोषणा __OSDEP_INTF_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#घोषणा RND4(x)	(((x >> 2) + ((x & 3) != 0)) << 2)

काष्ठा पूर्णांकf_priv अणु
	u8 *पूर्णांकf_dev;
	/* when in USB, IO is through पूर्णांकerrupt in/out endpoपूर्णांकs */
	काष्ठा usb_device *udev;
	काष्ठा urb *piorw_urb;
	काष्ठा completion io_retevt_comp;
पूर्ण;

पूर्णांक r871x_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);

#पूर्ण_अगर	/*_OSDEP_INTF_H_*/
