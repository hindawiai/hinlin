<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * omap_usb.h -- omap usb2 phy header file
 *
 * Copyright (C) 2012-2020 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __DRIVERS_OMAP_USB2_H
#घोषणा __DRIVERS_OMAP_USB2_H

#समावेश <linux/usb/phy_companion.h>

#घोषणा	phy_to_omapusb(x)	container_of((x), काष्ठा omap_usb, phy)

#अगर defined(CONFIG_OMAP_USB2) || defined(CONFIG_OMAP_USB2_MODULE)
बाह्य पूर्णांक omap_usb2_set_comparator(काष्ठा phy_companion *comparator);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_usb2_set_comparator(काष्ठा phy_companion *comparator)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DRIVERS_OMAP_USB_H */
