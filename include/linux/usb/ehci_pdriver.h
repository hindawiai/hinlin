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

#अगर_अघोषित __USB_CORE_EHCI_PDRIVER_H
#घोषणा __USB_CORE_EHCI_PDRIVER_H

काष्ठा platक्रमm_device;
काष्ठा usb_hcd;

/**
 * काष्ठा usb_ehci_pdata - platक्रमm_data क्रम generic ehci driver
 *
 * @caps_offset:	offset of the EHCI Capability Registers to the start of
 *			the io memory region provided to the driver.
 * @has_tt:		set to 1 अगर TT is पूर्णांकegrated in root hub.
 * @port_घातer_on:	set to 1 अगर the controller needs a घातer up after
 *			initialization.
 * @port_घातer_off:	set to 1 अगर the controller needs to be घातered करोwn
 *			after initialization.
 * @no_io_watchकरोg:	set to 1 अगर the controller करोes not need the I/O
 *			watchकरोg to run.
 * @reset_on_resume:	set to 1 अगर the controller needs to be reset after
 * 			a suspend / resume cycle (but can't detect that itself).
 *
 * These are general configuration options क्रम the EHCI controller. All of
 * these options are activating more or less workarounds क्रम some hardware.
 */
काष्ठा usb_ehci_pdata अणु
	पूर्णांक		caps_offset;
	अचिन्हित	has_tt:1;
	अचिन्हित	has_synopsys_hc_bug:1;
	अचिन्हित	big_endian_desc:1;
	अचिन्हित	big_endian_mmio:1;
	अचिन्हित	no_io_watchकरोg:1;
	अचिन्हित	reset_on_resume:1;
	अचिन्हित	dma_mask_64:1;
	अचिन्हित	spurious_oc:1;

	/* Turn on all घातer and घड़ीs */
	पूर्णांक (*घातer_on)(काष्ठा platक्रमm_device *pdev);
	/* Turn off all घातer and घड़ीs */
	व्योम (*घातer_off)(काष्ठा platक्रमm_device *pdev);
	/* Turn on only VBUS suspend घातer and hotplug detection,
	 * turn off everything अन्यथा */
	व्योम (*घातer_suspend)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*pre_setup)(काष्ठा usb_hcd *hcd);
पूर्ण;

#पूर्ण_अगर /* __USB_CORE_EHCI_PDRIVER_H */
