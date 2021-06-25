<शैली गुरु>
/*
 * USB related definitions
 *
 * Copyright (C) 2009 MontaVista Software, Inc. <source@mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_USB_H
#घोषणा __ASM_ARCH_USB_H

/* Passed as the platक्रमm data to the OHCI driver */
काष्ठा	da8xx_ohci_root_hub अणु
	/* Time from घातer on to घातer good (in 2 ms units) */
	u8	potpgt;
पूर्ण;

व्योम davinci_setup_usb(अचिन्हित mA, अचिन्हित potpgt_ms);

#पूर्ण_अगर	/* अगरndef __ASM_ARCH_USB_H */
