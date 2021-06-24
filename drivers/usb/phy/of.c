<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB of helper code
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/otg.h>

अटल स्थिर अक्षर *स्थिर usbphy_modes[] = अणु
	[USBPHY_INTERFACE_MODE_UNKNOWN]	= "",
	[USBPHY_INTERFACE_MODE_UTMI]	= "utmi",
	[USBPHY_INTERFACE_MODE_UTMIW]	= "utmi_wide",
	[USBPHY_INTERFACE_MODE_ULPI]	= "ulpi",
	[USBPHY_INTERFACE_MODE_SERIAL]	= "serial",
	[USBPHY_INTERFACE_MODE_HSIC]	= "hsic",
पूर्ण;

/**
 * of_usb_get_phy_mode - Get phy mode क्रम given device_node
 * @np:	Poपूर्णांकer to the given device_node
 *
 * The function माला_लो phy पूर्णांकerface string from property 'phy_type',
 * and वापसs the corresponding क्रमागत usb_phy_पूर्णांकerface
 */
क्रमागत usb_phy_पूर्णांकerface of_usb_get_phy_mode(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *phy_type;
	पूर्णांक err, i;

	err = of_property_पढ़ो_string(np, "phy_type", &phy_type);
	अगर (err < 0)
		वापस USBPHY_INTERFACE_MODE_UNKNOWN;

	क्रम (i = 0; i < ARRAY_SIZE(usbphy_modes); i++)
		अगर (!म_भेद(phy_type, usbphy_modes[i]))
			वापस i;

	वापस USBPHY_INTERFACE_MODE_UNKNOWN;
पूर्ण
EXPORT_SYMBOL_GPL(of_usb_get_phy_mode);
