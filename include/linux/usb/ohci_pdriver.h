<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2012 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __USB_CORE_OHCI_PDRIVER_H
#घोषणा __USB_CORE_OHCI_PDRIVER_H

/**
 * काष्ठा usb_ohci_pdata - platक्रमm_data क्रम generic ohci driver
 *
 * @big_endian_desc:	BE descriptors
 * @big_endian_mmio:	BE रेजिस्टरs
 * @no_big_frame_no:	no big endian frame_no shअगरt
 * @num_ports:		number of ports
 *
 * These are general configuration options क्रम the OHCI controller. All of
 * these options are activating more or less workarounds क्रम some hardware.
 */
काष्ठा usb_ohci_pdata अणु
	अचिन्हित	big_endian_desc:1;
	अचिन्हित	big_endian_mmio:1;
	अचिन्हित	no_big_frame_no:1;
	अचिन्हित पूर्णांक	num_ports;

	/* Turn on all घातer and घड़ीs */
	पूर्णांक (*घातer_on)(काष्ठा platक्रमm_device *pdev);
	/* Turn off all घातer and घड़ीs */
	व्योम (*घातer_off)(काष्ठा platक्रमm_device *pdev);
	/* Turn on only VBUS suspend घातer and hotplug detection,
	 * turn off everything अन्यथा */
	व्योम (*घातer_suspend)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

#पूर्ण_अगर /* __USB_CORE_OHCI_PDRIVER_H */
