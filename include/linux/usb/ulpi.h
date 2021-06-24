<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ulpi.h -- ULPI defines and function prorotypes
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * This software is distributed under the terms of the GNU General
 * Public License ("GPL") as published by the Free Software Foundation,
 * version 2 of that License.
 */

#अगर_अघोषित __LINUX_USB_ULPI_H
#घोषणा __LINUX_USB_ULPI_H

#समावेश <linux/usb/otg.h>
#समावेश <linux/ulpi/regs.h>

/*-------------------------------------------------------------------------*/

/*
 * ULPI Flags
 */
#घोषणा ULPI_OTG_ID_PULLUP		(1 << 0)
#घोषणा ULPI_OTG_DP_PULLDOWN_DIS	(1 << 1)
#घोषणा ULPI_OTG_DM_PULLDOWN_DIS	(1 << 2)
#घोषणा ULPI_OTG_DISCHRGVBUS		(1 << 3)
#घोषणा ULPI_OTG_CHRGVBUS		(1 << 4)
#घोषणा ULPI_OTG_DRVVBUS		(1 << 5)
#घोषणा ULPI_OTG_DRVVBUS_EXT		(1 << 6)
#घोषणा ULPI_OTG_EXTVBUSIND		(1 << 7)

#घोषणा ULPI_IC_6PIN_SERIAL		(1 << 8)
#घोषणा ULPI_IC_3PIN_SERIAL		(1 << 9)
#घोषणा ULPI_IC_CARKIT			(1 << 10)
#घोषणा ULPI_IC_CLKSUSPM		(1 << 11)
#घोषणा ULPI_IC_AUTORESUME		(1 << 12)
#घोषणा ULPI_IC_EXTVBUS_INDINV		(1 << 13)
#घोषणा ULPI_IC_IND_PASSTHRU		(1 << 14)
#घोषणा ULPI_IC_PROTECT_DIS		(1 << 15)

#घोषणा ULPI_FC_HS			(1 << 16)
#घोषणा ULPI_FC_FS			(1 << 17)
#घोषणा ULPI_FC_LS			(1 << 18)
#घोषणा ULPI_FC_FS4LS			(1 << 19)
#घोषणा ULPI_FC_TERMSEL			(1 << 20)
#घोषणा ULPI_FC_OP_NORM			(1 << 21)
#घोषणा ULPI_FC_OP_NODRV		(1 << 22)
#घोषणा ULPI_FC_OP_DIS_NRZI		(1 << 23)
#घोषणा ULPI_FC_OP_NSYNC_NEOP		(1 << 24)
#घोषणा ULPI_FC_RST			(1 << 25)
#घोषणा ULPI_FC_SUSPM			(1 << 26)

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_USB_ULPI)
काष्ठा usb_phy *otg_ulpi_create(काष्ठा usb_phy_io_ops *ops,
					अचिन्हित पूर्णांक flags);

काष्ठा usb_phy *devm_otg_ulpi_create(काष्ठा device *dev,
				     काष्ठा usb_phy_io_ops *ops,
				     अचिन्हित पूर्णांक flags);
#अन्यथा
अटल अंतरभूत काष्ठा usb_phy *otg_ulpi_create(काष्ठा usb_phy_io_ops *ops,
					      अचिन्हित पूर्णांक flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा usb_phy *devm_otg_ulpi_create(काष्ठा device *dev,
						   काष्ठा usb_phy_io_ops *ops,
						   अचिन्हित पूर्णांक flags)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_ULPI_VIEWPORT
/* access ops क्रम controllers with a viewport रेजिस्टर */
बाह्य काष्ठा usb_phy_io_ops ulpi_viewport_access_ops;
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_ULPI_H */
