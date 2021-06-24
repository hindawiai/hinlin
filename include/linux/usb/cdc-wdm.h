<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB CDC Device Management subdriver
 *
 * Copyright (c) 2012  Bjथचrn Mork <bjorn@mork.no>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#अगर_अघोषित __LINUX_USB_CDC_WDM_H
#घोषणा __LINUX_USB_CDC_WDM_H

#समावेश <uapi/linux/usb/cdc-wdm.h>

बाह्य काष्ठा usb_driver *usb_cdc_wdm_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					काष्ठा usb_endpoपूर्णांक_descriptor *ep,
					पूर्णांक bufsize,
					पूर्णांक (*manage_घातer)(काष्ठा usb_पूर्णांकerface *, पूर्णांक));

#पूर्ण_अगर /* __LINUX_USB_CDC_WDM_H */
