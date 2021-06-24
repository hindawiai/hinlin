<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
* Common Header File क्रम the Elan Digital Systems U132 adapter
* this file should be included by both the "ftdi-u132" and
* the "u132-hcd" modules.
*
* Copyright(C) 2006 Elan Digital Systems Limited
*(http://www.elandigitalप्रणालीs.com)
*
* Author and Maपूर्णांकainer - Tony Olech - Elan Digital Systems
*(tony.olech@elandigitalप्रणालीs.com)
*
* The driver was written by Tony Olech(tony.olech@elandigitalप्रणालीs.com)
* based on various USB client drivers in the 2.6.15 linux kernel
* with स्थिरant reference to the 3rd Edition of Linux Device Drivers
* published by O'Reilly
*
* The U132 adapter is a USB to CardBus adapter specअगरically deचिन्हित
* क्रम PC cards that contain an OHCI host controller. Typical PC cards
* are the Orange Mobile 3G Option GlobeTrotter Fusion card.
*
* The U132 adapter will *NOT *work with PC cards that करो not contain
* an OHCI controller. A simple way to test whether a PC card has an
* OHCI controller as an पूर्णांकerface is to insert the PC card directly
* पूर्णांकo a laptop(or desktop) with a CardBus slot and अगर "lspci" shows
* a new USB controller and "lsusb -v" shows a new OHCI Host Controller
* then there is a good chance that the U132 adapter will support the
* PC card.(you also need the specअगरic client driver क्रम the PC card)
*
* Please inक्रमm the Author and Maपूर्णांकainer about any PC cards that
* contain OHCI Host Controller and work when directly connected to
* an embedded CardBus slot but करो not work when they are connected
* via an ELAN U132 adapter.
*
* The driver consists of two modules, the "ftdi-u132" module is
* a USB client driver that पूर्णांकerfaces to the FTDI chip within
* the U132 adapter manufactured by Elan Digital Systems, and the
* "u132-hcd" module is a USB host controller driver that talks
* to the OHCI controller within CardBus card that are inserted
* in the U132 adapter.
*
* The "ftdi-u132" module should be loaded स्वतःmatically by the
* hot plug प्रणाली when the U132 adapter is plugged in. The module
* initialises the adapter which mostly consists of synchronising
* the FTDI chip, beक्रमe continuously polling the adapter to detect
* PC card insertions. As soon as a PC card containing a recognised
* OHCI controller is seen the "ftdi-u132" module explicitly requests
* the kernel to load the "u132-hcd" module.
*
* The "ftdi-u132" module provides the पूर्णांकerface to the inserted
* PC card and the "u132-hcd" module uses the API to send and receive
* data. The API features call-backs, so that part of the "u132-hcd"
* module code will run in the context of one of the kernel thपढ़ोs
* of the "ftdi-u132" module.
*
*/
पूर्णांक ftdi_elan_चयन_on_diagnostics(पूर्णांक number);
व्योम ftdi_elan_gone_away(काष्ठा platक्रमm_device *pdev);
व्योम start_usb_lock_device_tracing(व्योम);
काष्ठा u132_platक्रमm_data अणु
        u16 venकरोr;
        u16 device;
        u8 potpg;
        व्योम (*port_घातer) (काष्ठा device *dev, पूर्णांक is_on);
        व्योम (*reset) (काष्ठा device *dev);
पूर्ण;
पूर्णांक usb_ftdi_elan_edset_single(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
        पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
         पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null));
पूर्णांक usb_ftdi_elan_edset_output(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
        पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
         पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null));
पूर्णांक usb_ftdi_elan_edset_empty(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
        पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
         पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null));
पूर्णांक usb_ftdi_elan_edset_input(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
        पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
         पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null));
पूर्णांक usb_ftdi_elan_edset_setup(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp, काष्ठा urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        व्योम (*callback) (व्योम *endp, काष्ठा urb *urb, u8 *buf, पूर्णांक len,
        पूर्णांक toggle_bits, पूर्णांक error_count, पूर्णांक condition_code, पूर्णांक repeat_number,
         पूर्णांक halted, पूर्णांक skipped, पूर्णांक actual, पूर्णांक non_null));
पूर्णांक usb_ftdi_elan_edset_flush(काष्ठा platक्रमm_device *pdev, u8 ed_number,
        व्योम *endp);
पूर्णांक usb_ftdi_elan_पढ़ो_pcimem(काष्ठा platक्रमm_device *pdev, पूर्णांक mem_offset,
			      u8 width, u32 *data);
पूर्णांक usb_ftdi_elan_ग_लिखो_pcimem(काष्ठा platक्रमm_device *pdev, पूर्णांक mem_offset,
			       u8 width, u32 data);
