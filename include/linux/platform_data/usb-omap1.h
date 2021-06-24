<शैली गुरु>
/*
 * Platक्रमm data क्रम OMAP1 USB
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive क्रम
 * more details.
 */
#अगर_अघोषित __LINUX_USB_OMAP1_H
#घोषणा __LINUX_USB_OMAP1_H

#समावेश <linux/platक्रमm_device.h>

काष्ठा omap_usb_config अणु
	/* Configure drivers according to the connectors on your board:
	 *  - "A" connector (rectagular)
	 *	... क्रम host/OHCI use, set "register_host".
	 *  - "B" connector (squarish) or "Mini-B"
	 *	... क्रम device/gadget use, set "register_dev".
	 *  - "Mini-AB" connector (very similar to Mini-B)
	 *	... क्रम OTG use as device OR host, initialize "otg"
	 */
	अचिन्हित	रेजिस्टर_host:1;
	अचिन्हित	रेजिस्टर_dev:1;
	u8		otg;	/* port number, 1-based:  usb1 == 2 */

	स्थिर अक्षर	*extcon;	/* extcon device क्रम OTG */

	u8		hmc_mode;

	/* implicitly true अगर otg:  host supports remote wakeup? */
	u8		rwc;

	/* संकेतing pins used to talk to transceiver on usbN:
	 *  0 == usbN unused
	 *  2 == usb0-only, using पूर्णांकernal transceiver
	 *  3 == 3 wire bidirectional
	 *  4 == 4 wire bidirectional
	 *  6 == 6 wire unidirectional (or TLL)
	 */
	u8		pins[3];

	काष्ठा platक्रमm_device *udc_device;
	काष्ठा platक्रमm_device *ohci_device;
	काष्ठा platक्रमm_device *otg_device;

	u32 (*usb0_init)(अचिन्हित nwires, अचिन्हित is_device);
	u32 (*usb1_init)(अचिन्हित nwires);
	u32 (*usb2_init)(अचिन्हित nwires, अचिन्हित alt_pingroup);

	पूर्णांक (*ocpi_enable)(व्योम);
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_OMAP1_H */
