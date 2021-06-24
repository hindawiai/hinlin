<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * USB roothub wrapper
 *
 * Copyright (C) 2018 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#अगर_अघोषित __USB_CORE_PHY_H_
#घोषणा __USB_CORE_PHY_H_

काष्ठा device;
काष्ठा usb_phy_roothub;

काष्ठा usb_phy_roothub *usb_phy_roothub_alloc(काष्ठा device *dev);

पूर्णांक usb_phy_roothub_init(काष्ठा usb_phy_roothub *phy_roothub);
पूर्णांक usb_phy_roothub_निकास(काष्ठा usb_phy_roothub *phy_roothub);

पूर्णांक usb_phy_roothub_set_mode(काष्ठा usb_phy_roothub *phy_roothub,
			     क्रमागत phy_mode mode);
पूर्णांक usb_phy_roothub_calibrate(काष्ठा usb_phy_roothub *phy_roothub);
पूर्णांक usb_phy_roothub_घातer_on(काष्ठा usb_phy_roothub *phy_roothub);
व्योम usb_phy_roothub_घातer_off(काष्ठा usb_phy_roothub *phy_roothub);

पूर्णांक usb_phy_roothub_suspend(काष्ठा device *controller_dev,
			    काष्ठा usb_phy_roothub *phy_roothub);
पूर्णांक usb_phy_roothub_resume(काष्ठा device *controller_dev,
			   काष्ठा usb_phy_roothub *phy_roothub);

#पूर्ण_अगर /* __USB_CORE_PHY_H_ */
