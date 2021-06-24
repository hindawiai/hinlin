<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* USB OTG (On The Go) defines */
/*
 *
 * These APIs may be used between USB controllers.  USB device drivers
 * (क्रम either host or peripheral roles) करोn't use these calls; they
 * जारी to use just usb_device and usb_gadget.
 */

#अगर_अघोषित __LINUX_USB_OTG_H
#घोषणा __LINUX_USB_OTG_H

#समावेश <linux/phy/phy.h>
#समावेश <linux/usb/phy.h>

काष्ठा usb_otg अणु
	u8			शेष_a;

	काष्ठा phy		*phy;
	/* old usb_phy पूर्णांकerface */
	काष्ठा usb_phy		*usb_phy;
	काष्ठा usb_bus		*host;
	काष्ठा usb_gadget	*gadget;

	क्रमागत usb_otg_state	state;

	/* bind/unbind the host controller */
	पूर्णांक	(*set_host)(काष्ठा usb_otg *otg, काष्ठा usb_bus *host);

	/* bind/unbind the peripheral controller */
	पूर्णांक	(*set_peripheral)(काष्ठा usb_otg *otg,
					काष्ठा usb_gadget *gadget);

	/* effective क्रम A-peripheral, ignored क्रम B devices */
	पूर्णांक	(*set_vbus)(काष्ठा usb_otg *otg, bool enabled);

	/* क्रम B devices only:  start session with A-Host */
	पूर्णांक	(*start_srp)(काष्ठा usb_otg *otg);

	/* start or जारी HNP role चयन */
	पूर्णांक	(*start_hnp)(काष्ठा usb_otg *otg);

पूर्ण;

/**
 * काष्ठा usb_otg_caps - describes the otg capabilities of the device
 * @otg_rev: The OTG revision number the device is compliant with, it's
 *		in binary-coded decimal (i.e. 2.0 is 0200H).
 * @hnp_support: Indicates अगर the device supports HNP.
 * @srp_support: Indicates अगर the device supports SRP.
 * @adp_support: Indicates अगर the device supports ADP.
 */
काष्ठा usb_otg_caps अणु
	u16 otg_rev;
	bool hnp_support;
	bool srp_support;
	bool adp_support;
पूर्ण;

बाह्य स्थिर अक्षर *usb_otg_state_string(क्रमागत usb_otg_state state);

/* Context: can sleep */
अटल अंतरभूत पूर्णांक
otg_start_hnp(काष्ठा usb_otg *otg)
अणु
	अगर (otg && otg->start_hnp)
		वापस otg->start_hnp(otg);

	वापस -ENOTSUPP;
पूर्ण

/* Context: can sleep */
अटल अंतरभूत पूर्णांक
otg_set_vbus(काष्ठा usb_otg *otg, bool enabled)
अणु
	अगर (otg && otg->set_vbus)
		वापस otg->set_vbus(otg, enabled);

	वापस -ENOTSUPP;
पूर्ण

/* क्रम HCDs */
अटल अंतरभूत पूर्णांक
otg_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	अगर (otg && otg->set_host)
		वापस otg->set_host(otg, host);

	वापस -ENOTSUPP;
पूर्ण

/* क्रम usb peripheral controller drivers */

/* Context: can sleep */
अटल अंतरभूत पूर्णांक
otg_set_peripheral(काष्ठा usb_otg *otg, काष्ठा usb_gadget *periph)
अणु
	अगर (otg && otg->set_peripheral)
		वापस otg->set_peripheral(otg, periph);

	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
otg_start_srp(काष्ठा usb_otg *otg)
अणु
	अगर (otg && otg->start_srp)
		वापस otg->start_srp(otg);

	वापस -ENOTSUPP;
पूर्ण

/* क्रम OTG controller drivers (and maybe other stuff) */
बाह्य पूर्णांक usb_bus_start_क्रमागत(काष्ठा usb_bus *bus, अचिन्हित port_num);

क्रमागत usb_dr_mode अणु
	USB_DR_MODE_UNKNOWN,
	USB_DR_MODE_HOST,
	USB_DR_MODE_PERIPHERAL,
	USB_DR_MODE_OTG,
पूर्ण;

/**
 * usb_get_dr_mode - Get dual role mode क्रम given device
 * @dev: Poपूर्णांकer to the given device
 *
 * The function माला_लो phy पूर्णांकerface string from property 'dr_mode',
 * and वापसs the correspondig क्रमागत usb_dr_mode
 */
बाह्य क्रमागत usb_dr_mode usb_get_dr_mode(काष्ठा device *dev);

#पूर्ण_अगर /* __LINUX_USB_OTG_H */
