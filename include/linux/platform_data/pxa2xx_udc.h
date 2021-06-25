<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This supports machine-specअगरic dअगरferences in how the PXA2xx
 * USB Device Controller (UDC) is wired.
 *
 * It is set in linux/arch/arm/mach-pxa/<machine>.c or in
 * linux/arch/mach-ixp4xx/<machine>.c and used in
 * the probe routine of linux/drivers/usb/gadget/pxa2xx_udc.c
 */
#अगर_अघोषित PXA2XX_UDC_H
#घोषणा PXA2XX_UDC_H

काष्ठा pxa2xx_udc_mach_info अणु
        पूर्णांक  (*udc_is_connected)(व्योम);		/* करो we see host? */
        व्योम (*udc_command)(पूर्णांक cmd);
#घोषणा	PXA2XX_UDC_CMD_CONNECT		0	/* let host see us */
#घोषणा	PXA2XX_UDC_CMD_DISCONNECT	1	/* so host won't see us */

	/* Boards following the design guidelines in the developer's manual,
	 * with on-chip GPIOs not Lubbock's weird hardware, can have a sane
	 * VBUS IRQ and omit the methods above.  Store the GPIO number
	 * here.  Note that someबार the संकेतs go through inverters...
	 */
	bool	gpio_pullup_inverted;
	पूर्णांक	gpio_pullup;			/* high == pullup activated */
पूर्ण;

#पूर्ण_अगर
