<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OF helpers क्रम usb devices.
 *
 * This file is released under the GPLv2
 */

#अगर_अघोषित __LINUX_USB_OF_H
#घोषणा __LINUX_USB_OF_H

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/phy.h>

काष्ठा usb_device;

#अगर IS_ENABLED(CONFIG_OF)
क्रमागत usb_dr_mode of_usb_get_dr_mode_by_phy(काष्ठा device_node *np, पूर्णांक arg0);
bool of_usb_host_tpl_support(काष्ठा device_node *np);
पूर्णांक of_usb_update_otg_caps(काष्ठा device_node *np,
			काष्ठा usb_otg_caps *otg_caps);
काष्ठा device_node *usb_of_get_device_node(काष्ठा usb_device *hub, पूर्णांक port1);
bool usb_of_has_combined_node(काष्ठा usb_device *udev);
काष्ठा device_node *usb_of_get_पूर्णांकerface_node(काष्ठा usb_device *udev,
		u8 config, u8 अगरnum);
काष्ठा device *usb_of_get_companion_dev(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत क्रमागत usb_dr_mode
of_usb_get_dr_mode_by_phy(काष्ठा device_node *np, पूर्णांक arg0)
अणु
	वापस USB_DR_MODE_UNKNOWN;
पूर्ण
अटल अंतरभूत bool of_usb_host_tpl_support(काष्ठा device_node *np)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक of_usb_update_otg_caps(काष्ठा device_node *np,
				काष्ठा usb_otg_caps *otg_caps)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा device_node *
usb_of_get_device_node(काष्ठा usb_device *hub, पूर्णांक port1)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool usb_of_has_combined_node(काष्ठा usb_device *udev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत काष्ठा device_node *
usb_of_get_पूर्णांकerface_node(काष्ठा usb_device *udev, u8 config, u8 अगरnum)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा device *usb_of_get_companion_dev(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_USB_SUPPORT)
क्रमागत usb_phy_पूर्णांकerface of_usb_get_phy_mode(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत क्रमागत usb_phy_पूर्णांकerface of_usb_get_phy_mode(काष्ठा device_node *np)
अणु
	वापस USBPHY_INTERFACE_MODE_UNKNOWN;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_OF_H */
