<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Generic Bluetooth USB driver
 *
 *  Copyright (C) 2005-2008  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/firmware.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/suspend.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btintel.h"
#समावेश "btbcm.h"
#समावेश "btrtl.h"

#घोषणा VERSION "0.8"

अटल bool disable_scofix;
अटल bool क्रमce_scofix;
अटल bool enable_स्वतःsuspend = IS_ENABLED(CONFIG_BT_HCIBTUSB_AUTOSUSPEND);

अटल bool reset = true;

अटल काष्ठा usb_driver btusb_driver;

#घोषणा BTUSB_IGNORE		0x01
#घोषणा BTUSB_DIGIANSWER	0x02
#घोषणा BTUSB_CSR		0x04
#घोषणा BTUSB_SNIFFER		0x08
#घोषणा BTUSB_BCM92035		0x10
#घोषणा BTUSB_BROKEN_ISOC	0x20
#घोषणा BTUSB_WRONG_SCO_MTU	0x40
#घोषणा BTUSB_ATH3012		0x80
#घोषणा BTUSB_INTEL		0x100
#घोषणा BTUSB_INTEL_BOOT	0x200
#घोषणा BTUSB_BCM_PATCHRAM	0x400
#घोषणा BTUSB_MARVELL		0x800
#घोषणा BTUSB_SWAVE		0x1000
#घोषणा BTUSB_INTEL_NEW		0x2000
#घोषणा BTUSB_AMP		0x4000
#घोषणा BTUSB_QCA_ROME		0x8000
#घोषणा BTUSB_BCM_APPLE		0x10000
#घोषणा BTUSB_REALTEK		0x20000
#घोषणा BTUSB_BCM2045		0x40000
#घोषणा BTUSB_IFNUM_2		0x80000
#घोषणा BTUSB_CW6622		0x100000
#घोषणा BTUSB_MEDIATEK		0x200000
#घोषणा BTUSB_WIDEBAND_SPEECH	0x400000
#घोषणा BTUSB_VALID_LE_STATES   0x800000
#घोषणा BTUSB_QCA_WCN6855	0x1000000
#घोषणा BTUSB_INTEL_NEWGEN	0x2000000

अटल स्थिर काष्ठा usb_device_id btusb_table[] = अणु
	/* Generic Bluetooth USB device */
	अणु USB_DEVICE_INFO(0xe0, 0x01, 0x01) पूर्ण,

	/* Generic Bluetooth AMP device */
	अणु USB_DEVICE_INFO(0xe0, 0x01, 0x04), .driver_info = BTUSB_AMP पूर्ण,

	/* Generic Bluetooth USB पूर्णांकerface */
	अणु USB_INTERFACE_INFO(0xe0, 0x01, 0x01) पूर्ण,

	/* Apple-specअगरic (Broadcom) devices */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x05ac, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_APPLE | BTUSB_IFNUM_2 पूर्ण,

	/* MediaTek MT76x0E */
	अणु USB_DEVICE(0x0e8d, 0x763f) पूर्ण,

	/* Broadcom SoftSailing reporting venकरोr specअगरic */
	अणु USB_DEVICE(0x0a5c, 0x21e1) पूर्ण,

	/* Apple MacBookPro 7,1 */
	अणु USB_DEVICE(0x05ac, 0x8213) पूर्ण,

	/* Apple iMac11,1 */
	अणु USB_DEVICE(0x05ac, 0x8215) पूर्ण,

	/* Apple MacBookPro6,2 */
	अणु USB_DEVICE(0x05ac, 0x8218) पूर्ण,

	/* Apple MacBookAir3,1, MacBookAir3,2 */
	अणु USB_DEVICE(0x05ac, 0x821b) पूर्ण,

	/* Apple MacBookAir4,1 */
	अणु USB_DEVICE(0x05ac, 0x821f) पूर्ण,

	/* Apple MacBookPro8,2 */
	अणु USB_DEVICE(0x05ac, 0x821a) पूर्ण,

	/* Apple MacMini5,1 */
	अणु USB_DEVICE(0x05ac, 0x8281) पूर्ण,

	/* AVM BlueFRITZ! USB v2.0 */
	अणु USB_DEVICE(0x057c, 0x3800), .driver_info = BTUSB_SWAVE पूर्ण,

	/* Bluetooth Ultraport Module from IBM */
	अणु USB_DEVICE(0x04bf, 0x030a) पूर्ण,

	/* ALPS Modules with non-standard id */
	अणु USB_DEVICE(0x044e, 0x3001) पूर्ण,
	अणु USB_DEVICE(0x044e, 0x3002) पूर्ण,

	/* Ericsson with non-standard id */
	अणु USB_DEVICE(0x0bdb, 0x1002) पूर्ण,

	/* Canyon CN-BTU1 with HID पूर्णांकerfaces */
	अणु USB_DEVICE(0x0c10, 0x0000) पूर्ण,

	/* Broadcom BCM20702A0 */
	अणु USB_DEVICE(0x413c, 0x8197) पूर्ण,

	/* Broadcom BCM20702B0 (Dynex/Insignia) */
	अणु USB_DEVICE(0x19ff, 0x0239), .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Broadcom BCM43142A0 (Foxconn/Lenovo) */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x105b, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Broadcom BCM920703 (HTC Vive) */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0bb4, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Foxconn - Hon Hai */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0489, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Lite-On Technology - Broadcom based */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x04ca, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Broadcom devices with venकरोr specअगरic id */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0a5c, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* ASUSTek Computer - Broadcom based */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0b05, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Belkin F8065bf - Broadcom based */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x050d, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* IMC Networks - Broadcom based */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x13d3, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Dell Computer - Broadcom based  */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x413c, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Toshiba Corp - Broadcom based */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0930, 0xff, 0x01, 0x01),
	  .driver_info = BTUSB_BCM_PATCHRAM पूर्ण,

	/* Intel Bluetooth USB Bootloader (RAM module) */
	अणु USB_DEVICE(0x8087, 0x0a5a),
	  .driver_info = BTUSB_INTEL_BOOT | BTUSB_BROKEN_ISOC पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, btusb_table);

अटल स्थिर काष्ठा usb_device_id blacklist_table[] = अणु
	/* CSR BlueCore devices */
	अणु USB_DEVICE(0x0a12, 0x0001), .driver_info = BTUSB_CSR पूर्ण,

	/* Broadcom BCM2033 without firmware */
	अणु USB_DEVICE(0x0a5c, 0x2033), .driver_info = BTUSB_IGNORE पूर्ण,

	/* Broadcom BCM2045 devices */
	अणु USB_DEVICE(0x0a5c, 0x2045), .driver_info = BTUSB_BCM2045 पूर्ण,

	/* Atheros 3011 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xe027), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe03d), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x04f2, 0xaff1), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0215), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3002), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe019), .driver_info = BTUSB_IGNORE पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3304), .driver_info = BTUSB_IGNORE पूर्ण,

	/* Atheros AR9285 Malbec with sflash firmware */
	अणु USB_DEVICE(0x03f0, 0x311d), .driver_info = BTUSB_IGNORE पूर्ण,

	/* Atheros 3012 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xe04d), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe04e), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe056), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe057), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe05f), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe076), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe078), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe095), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04c5, 0x1330), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3005), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3006), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3007), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3008), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300b), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300d), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x300f), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3010), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3014), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3018), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0219), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x021c), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0220), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0227), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x17d0), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x0036), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3008), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311d), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311e), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x311f), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x3121), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x817a), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0x817b), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe003), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe004), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe005), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe006), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3362), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3375), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3393), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3395), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3402), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3408), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3423), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3432), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3472), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3474), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3487), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3490), .driver_info = BTUSB_ATH3012 पूर्ण,

	/* Atheros AR5BBU12 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xe02c), .driver_info = BTUSB_IGNORE पूर्ण,

	/* Atheros AR5BBU12 with sflash firmware */
	अणु USB_DEVICE(0x0489, 0xe036), .driver_info = BTUSB_ATH3012 पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe03c), .driver_info = BTUSB_ATH3012 पूर्ण,

	/* QCA ROME chipset */
	अणु USB_DEVICE(0x0cf3, 0x535b), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe007), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe009), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe010), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe300), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe301), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cf3, 0xe360), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe092), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe09f), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe0a2), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3011), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3015), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3016), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x301a), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04ca, 0x3021), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3491), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3496), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3501), .driver_info = BTUSB_QCA_ROME |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,

	/* QCA WCN6855 chipset */
	अणु USB_DEVICE(0x0cf3, 0xe600), .driver_info = BTUSB_QCA_WCN6855 |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,

	/* Broadcom BCM2035 */
	अणु USB_DEVICE(0x0a5c, 0x2009), .driver_info = BTUSB_BCM92035 पूर्ण,
	अणु USB_DEVICE(0x0a5c, 0x200a), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,
	अणु USB_DEVICE(0x0a5c, 0x2035), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Broadcom BCM2045 */
	अणु USB_DEVICE(0x0a5c, 0x2039), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,
	अणु USB_DEVICE(0x0a5c, 0x2101), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* IBM/Lenovo ThinkPad with Broadcom chip */
	अणु USB_DEVICE(0x0a5c, 0x201e), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,
	अणु USB_DEVICE(0x0a5c, 0x2110), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* HP laptop with Broadcom chip */
	अणु USB_DEVICE(0x03f0, 0x171d), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Dell laptop with Broadcom chip */
	अणु USB_DEVICE(0x413c, 0x8126), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Dell Wireless 370 and 410 devices */
	अणु USB_DEVICE(0x413c, 0x8152), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,
	अणु USB_DEVICE(0x413c, 0x8156), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Belkin F8T012 and F8T013 devices */
	अणु USB_DEVICE(0x050d, 0x0012), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,
	अणु USB_DEVICE(0x050d, 0x0013), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Asus WL-BTD202 device */
	अणु USB_DEVICE(0x0b05, 0x1715), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* Kensington Bluetooth USB adapter */
	अणु USB_DEVICE(0x047d, 0x105e), .driver_info = BTUSB_WRONG_SCO_MTU पूर्ण,

	/* RTX Telecom based adapters with buggy SCO support */
	अणु USB_DEVICE(0x0400, 0x0807), .driver_info = BTUSB_BROKEN_ISOC पूर्ण,
	अणु USB_DEVICE(0x0400, 0x080a), .driver_info = BTUSB_BROKEN_ISOC पूर्ण,

	/* CONWISE Technology based adapters with buggy SCO support */
	अणु USB_DEVICE(0x0e5e, 0x6622),
	  .driver_info = BTUSB_BROKEN_ISOC | BTUSB_CW6622पूर्ण,

	/* Roper Class 1 Bluetooth Dongle (Silicon Wave based) */
	अणु USB_DEVICE(0x1310, 0x0001), .driver_info = BTUSB_SWAVE पूर्ण,

	/* Digianswer devices */
	अणु USB_DEVICE(0x08fd, 0x0001), .driver_info = BTUSB_DIGIANSWER पूर्ण,
	अणु USB_DEVICE(0x08fd, 0x0002), .driver_info = BTUSB_IGNORE पूर्ण,

	/* CSR BlueCore Bluetooth Snअगरfer */
	अणु USB_DEVICE(0x0a12, 0x0002),
	  .driver_info = BTUSB_SNIFFER | BTUSB_BROKEN_ISOC पूर्ण,

	/* Frontline ComProbe Bluetooth Snअगरfer */
	अणु USB_DEVICE(0x16d3, 0x0002),
	  .driver_info = BTUSB_SNIFFER | BTUSB_BROKEN_ISOC पूर्ण,

	/* Marvell Bluetooth devices */
	अणु USB_DEVICE(0x1286, 0x2044), .driver_info = BTUSB_MARVELL पूर्ण,
	अणु USB_DEVICE(0x1286, 0x2046), .driver_info = BTUSB_MARVELL पूर्ण,
	अणु USB_DEVICE(0x1286, 0x204e), .driver_info = BTUSB_MARVELL पूर्ण,

	/* Intel Bluetooth devices */
	अणु USB_DEVICE(0x8087, 0x0025), .driver_info = BTUSB_INTEL_NEW |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VALID_LE_STATES पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0026), .driver_info = BTUSB_INTEL_NEW |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0029), .driver_info = BTUSB_INTEL_NEW |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0032), .driver_info = BTUSB_INTEL_NEWGEN |
						     BTUSB_WIDEBAND_SPEECHपूर्ण,
	अणु USB_DEVICE(0x8087, 0x0033), .driver_info = BTUSB_INTEL_NEWGEN |
						     BTUSB_WIDEBAND_SPEECHपूर्ण,
	अणु USB_DEVICE(0x8087, 0x07da), .driver_info = BTUSB_CSR पूर्ण,
	अणु USB_DEVICE(0x8087, 0x07dc), .driver_info = BTUSB_INTEL पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0a2a), .driver_info = BTUSB_INTEL पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0a2b), .driver_info = BTUSB_INTEL_NEW |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0aa7), .driver_info = BTUSB_INTEL |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x8087, 0x0aaa), .driver_info = BTUSB_INTEL_NEW |
						     BTUSB_WIDEBAND_SPEECH |
						     BTUSB_VALID_LE_STATES पूर्ण,

	/* Other Intel Bluetooth devices */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x8087, 0xe0, 0x01, 0x01),
	  .driver_info = BTUSB_IGNORE पूर्ण,

	/* Realtek 8822CE Bluetooth devices */
	अणु USB_DEVICE(0x0bda, 0xb00c), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0bda, 0xc822), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,

	/* Realtek 8852AE Bluetooth devices */
	अणु USB_DEVICE(0x0bda, 0xc852), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,

	/* Realtek Bluetooth devices */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0bda, 0xe0, 0x01, 0x01),
	  .driver_info = BTUSB_REALTEK पूर्ण,

	/* MediaTek Bluetooth devices */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0e8d, 0xe0, 0x01, 0x01),
	  .driver_info = BTUSB_MEDIATEK |
			 BTUSB_WIDEBAND_SPEECH |
			 BTUSB_VALID_LE_STATES पूर्ण,

	/* Additional MediaTek MT7615E Bluetooth devices */
	अणु USB_DEVICE(0x13d3, 0x3560), .driver_info = BTUSB_MEDIATEKपूर्ण,

	/* Additional Realtek 8723AE Bluetooth devices */
	अणु USB_DEVICE(0x0930, 0x021d), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3394), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8723BE Bluetooth devices */
	अणु USB_DEVICE(0x0489, 0xe085), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x0489, 0xe08b), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3410), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3416), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3459), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3494), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8723BU Bluetooth devices */
	अणु USB_DEVICE(0x7392, 0xa611), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8723DE Bluetooth devices */
	अणु USB_DEVICE(0x0bda, 0xb009), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x2ff8, 0xb011), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8821AE Bluetooth devices */
	अणु USB_DEVICE(0x0b05, 0x17dc), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3414), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3458), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3461), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3462), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8822BE Bluetooth devices */
	अणु USB_DEVICE(0x13d3, 0x3526), .driver_info = BTUSB_REALTEK पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x185c), .driver_info = BTUSB_REALTEK पूर्ण,

	/* Additional Realtek 8822CE Bluetooth devices */
	अणु USB_DEVICE(0x04ca, 0x4005), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x04c5, 0x161f), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x18ef), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3548), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3549), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3553), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3555), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x2ff8, 0x3051), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x1358, 0xc123), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0bda, 0xc123), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,
	अणु USB_DEVICE(0x0cb5, 0xc547), .driver_info = BTUSB_REALTEK |
						     BTUSB_WIDEBAND_SPEECH पूर्ण,

	/* Silicon Wave based devices */
	अणु USB_DEVICE(0x0c10, 0x0000), .driver_info = BTUSB_SWAVE पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

/* The Bluetooth USB module build पूर्णांकo some devices needs to be reset on resume,
 * this is a problem with the platक्रमm (likely shutting off all घातer) not with
 * the module itself. So we use a DMI list to match known broken platक्रमms.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id btusb_needs_reset_resume_table[] = अणु
	अणु
		/* Dell OptiPlex 3060 (QCA ROME device 0cf3:e007) */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 3060"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell XPS 9360 (QCA ROME device 0cf3:e300) */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS 13 9360"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Inspiron 5565 (QCA ROME device 0cf3:e009) */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5565"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

#घोषणा BTUSB_MAX_ISOC_FRAMES	10

#घोषणा BTUSB_INTR_RUNNING	0
#घोषणा BTUSB_BULK_RUNNING	1
#घोषणा BTUSB_ISOC_RUNNING	2
#घोषणा BTUSB_SUSPENDING	3
#घोषणा BTUSB_DID_ISO_RESUME	4
#घोषणा BTUSB_BOOTLOADER	5
#घोषणा BTUSB_DOWNLOADING	6
#घोषणा BTUSB_FIRMWARE_LOADED	7
#घोषणा BTUSB_FIRMWARE_FAILED	8
#घोषणा BTUSB_BOOTING		9
#घोषणा BTUSB_DIAG_RUNNING	10
#घोषणा BTUSB_OOB_WAKE_ENABLED	11
#घोषणा BTUSB_HW_RESET_ACTIVE	12
#घोषणा BTUSB_TX_WAIT_VND_EVT	13
#घोषणा BTUSB_WAKEUP_DISABLE	14

काष्ठा btusb_data अणु
	काष्ठा hci_dev       *hdev;
	काष्ठा usb_device    *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_पूर्णांकerface *isoc;
	काष्ठा usb_पूर्णांकerface *diag;
	अचिन्हित isoc_अगरnum;

	अचिन्हित दीर्घ flags;

	काष्ठा work_काष्ठा work;
	काष्ठा work_काष्ठा waker;

	काष्ठा usb_anchor deferred;
	काष्ठा usb_anchor tx_anchor;
	पूर्णांक tx_in_flight;
	spinlock_t txlock;

	काष्ठा usb_anchor पूर्णांकr_anchor;
	काष्ठा usb_anchor bulk_anchor;
	काष्ठा usb_anchor isoc_anchor;
	काष्ठा usb_anchor diag_anchor;
	काष्ठा usb_anchor ctrl_anchor;
	spinlock_t rxlock;

	काष्ठा sk_buff *evt_skb;
	काष्ठा sk_buff *acl_skb;
	काष्ठा sk_buff *sco_skb;

	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकr_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_tx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_rx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *isoc_tx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *isoc_rx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *diag_tx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *diag_rx_ep;

	काष्ठा gpio_desc *reset_gpio;

	__u8 cmdreq_type;
	__u8 cmdreq;

	अचिन्हित पूर्णांक sco_num;
	अचिन्हित पूर्णांक air_mode;
	bool usb_alt6_packet_flow;
	पूर्णांक isoc_altsetting;
	पूर्णांक suspend_count;

	पूर्णांक (*recv_event)(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
	पूर्णांक (*recv_bulk)(काष्ठा btusb_data *data, व्योम *buffer, पूर्णांक count);

	पूर्णांक (*setup_on_usb)(काष्ठा hci_dev *hdev);

	पूर्णांक oob_wake_irq;   /* irq क्रम out-of-band wake-on-bt */
	अचिन्हित cmd_समयout_cnt;
पूर्ण;

अटल व्योम btusb_पूर्णांकel_cmd_समयout(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा gpio_desc *reset_gpio = data->reset_gpio;

	अगर (++data->cmd_समयout_cnt < 5)
		वापस;

	अगर (!reset_gpio) अणु
		bt_dev_err(hdev, "No way to reset. Ignoring and continuing");
		वापस;
	पूर्ण

	/*
	 * Toggle the hard reset line अगर the platक्रमm provides one. The reset
	 * is going to yank the device off the USB and then replug. So करोing
	 * once is enough. The cleanup is handled correctly on the way out
	 * (standard USB disconnect), and the new device is detected cleanly
	 * and bound to the driver again like it should be.
	 */
	अगर (test_and_set_bit(BTUSB_HW_RESET_ACTIVE, &data->flags)) अणु
		bt_dev_err(hdev, "last reset failed? Not resetting again");
		वापस;
	पूर्ण

	bt_dev_err(hdev, "Initiating HW reset via gpio");
	gpiod_set_value_cansleep(reset_gpio, 1);
	msleep(100);
	gpiod_set_value_cansleep(reset_gpio, 0);
पूर्ण

अटल व्योम btusb_rtl_cmd_समयout(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा gpio_desc *reset_gpio = data->reset_gpio;

	अगर (++data->cmd_समयout_cnt < 5)
		वापस;

	अगर (!reset_gpio) अणु
		bt_dev_err(hdev, "No gpio to reset Realtek device, ignoring");
		वापस;
	पूर्ण

	/* Toggle the hard reset line. The Realtek device is going to
	 * yank itself off the USB and then replug. The cleanup is handled
	 * correctly on the way out (standard USB disconnect), and the new
	 * device is detected cleanly and bound to the driver again like
	 * it should be.
	 */
	अगर (test_and_set_bit(BTUSB_HW_RESET_ACTIVE, &data->flags)) अणु
		bt_dev_err(hdev, "last reset failed? Not resetting again");
		वापस;
	पूर्ण

	bt_dev_err(hdev, "Reset Realtek device via gpio");
	gpiod_set_value_cansleep(reset_gpio, 1);
	msleep(200);
	gpiod_set_value_cansleep(reset_gpio, 0);
पूर्ण

अटल व्योम btusb_qca_cmd_समयout(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	अगर (++data->cmd_समयout_cnt < 5)
		वापस;

	bt_dev_err(hdev, "Multiple cmd timeouts seen. Resetting usb device.");
	/* This is not an unbalanced PM reference since the device will reset */
	err = usb_स्वतःpm_get_पूर्णांकerface(data->पूर्णांकf);
	अगर (!err)
		usb_queue_reset_device(data->पूर्णांकf);
	अन्यथा
		bt_dev_err(hdev, "Failed usb_autopm_get_interface with %d", err);
पूर्ण

अटल अंतरभूत व्योम btusb_मुक्त_frags(काष्ठा btusb_data *data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->rxlock, flags);

	kमुक्त_skb(data->evt_skb);
	data->evt_skb = शून्य;

	kमुक्त_skb(data->acl_skb);
	data->acl_skb = शून्य;

	kमुक्त_skb(data->sco_skb);
	data->sco_skb = शून्य;

	spin_unlock_irqrestore(&data->rxlock, flags);
पूर्ण

अटल पूर्णांक btusb_recv_पूर्णांकr(काष्ठा btusb_data *data, व्योम *buffer, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&data->rxlock, flags);
	skb = data->evt_skb;

	जबतक (count) अणु
		पूर्णांक len;

		अगर (!skb) अणु
			skb = bt_skb_alloc(HCI_MAX_EVENT_SIZE, GFP_ATOMIC);
			अगर (!skb) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
			hci_skb_expect(skb) = HCI_EVENT_HDR_SIZE;
		पूर्ण

		len = min_t(uपूर्णांक, hci_skb_expect(skb), count);
		skb_put_data(skb, buffer, len);

		count -= len;
		buffer += len;
		hci_skb_expect(skb) -= len;

		अगर (skb->len == HCI_EVENT_HDR_SIZE) अणु
			/* Complete event header */
			hci_skb_expect(skb) = hci_event_hdr(skb)->plen;

			अगर (skb_tailroom(skb) < hci_skb_expect(skb)) अणु
				kमुक्त_skb(skb);
				skb = शून्य;

				err = -EILSEQ;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!hci_skb_expect(skb)) अणु
			/* Complete frame */
			data->recv_event(data->hdev, skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	data->evt_skb = skb;
	spin_unlock_irqrestore(&data->rxlock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_recv_bulk(काष्ठा btusb_data *data, व्योम *buffer, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&data->rxlock, flags);
	skb = data->acl_skb;

	जबतक (count) अणु
		पूर्णांक len;

		अगर (!skb) अणु
			skb = bt_skb_alloc(HCI_MAX_FRAME_SIZE, GFP_ATOMIC);
			अगर (!skb) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			hci_skb_pkt_type(skb) = HCI_ACLDATA_PKT;
			hci_skb_expect(skb) = HCI_ACL_HDR_SIZE;
		पूर्ण

		len = min_t(uपूर्णांक, hci_skb_expect(skb), count);
		skb_put_data(skb, buffer, len);

		count -= len;
		buffer += len;
		hci_skb_expect(skb) -= len;

		अगर (skb->len == HCI_ACL_HDR_SIZE) अणु
			__le16 dlen = hci_acl_hdr(skb)->dlen;

			/* Complete ACL header */
			hci_skb_expect(skb) = __le16_to_cpu(dlen);

			अगर (skb_tailroom(skb) < hci_skb_expect(skb)) अणु
				kमुक्त_skb(skb);
				skb = शून्य;

				err = -EILSEQ;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!hci_skb_expect(skb)) अणु
			/* Complete frame */
			hci_recv_frame(data->hdev, skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	data->acl_skb = skb;
	spin_unlock_irqrestore(&data->rxlock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_recv_isoc(काष्ठा btusb_data *data, व्योम *buffer, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&data->rxlock, flags);
	skb = data->sco_skb;

	जबतक (count) अणु
		पूर्णांक len;

		अगर (!skb) अणु
			skb = bt_skb_alloc(HCI_MAX_SCO_SIZE, GFP_ATOMIC);
			अगर (!skb) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			hci_skb_pkt_type(skb) = HCI_SCODATA_PKT;
			hci_skb_expect(skb) = HCI_SCO_HDR_SIZE;
		पूर्ण

		len = min_t(uपूर्णांक, hci_skb_expect(skb), count);
		skb_put_data(skb, buffer, len);

		count -= len;
		buffer += len;
		hci_skb_expect(skb) -= len;

		अगर (skb->len == HCI_SCO_HDR_SIZE) अणु
			/* Complete SCO header */
			hci_skb_expect(skb) = hci_sco_hdr(skb)->dlen;

			अगर (skb_tailroom(skb) < hci_skb_expect(skb)) अणु
				kमुक्त_skb(skb);
				skb = शून्य;

				err = -EILSEQ;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!hci_skb_expect(skb)) अणु
			/* Complete frame */
			hci_recv_frame(data->hdev, skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	data->sco_skb = skb;
	spin_unlock_irqrestore(&data->rxlock, flags);

	वापस err;
पूर्ण

अटल व्योम btusb_पूर्णांकr_complete(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस;

	अगर (urb->status == 0) अणु
		hdev->stat.byte_rx += urb->actual_length;

		अगर (btusb_recv_पूर्णांकr(data, urb->transfer_buffer,
				    urb->actual_length) < 0) अणु
			bt_dev_err(hdev, "corrupted event packet");
			hdev->stat.err_rx++;
		पूर्ण
	पूर्ण अन्यथा अगर (urb->status == -ENOENT) अणु
		/* Aव्योम suspend failed when usb_समाप्त_urb */
		वापस;
	पूर्ण

	अगर (!test_bit(BTUSB_INTR_RUNNING, &data->flags))
		वापस;

	usb_mark_last_busy(data->udev);
	usb_anchor_urb(urb, &data->पूर्णांकr_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक btusb_submit_पूर्णांकr_urb(काष्ठा hci_dev *hdev, gfp_t mem_flags)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size;

	BT_DBG("%s", hdev->name);

	अगर (!data->पूर्णांकr_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	अगर (!urb)
		वापस -ENOMEM;

	size = le16_to_cpu(data->पूर्णांकr_ep->wMaxPacketSize);

	buf = kदो_स्मृति(size, mem_flags);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvपूर्णांकpipe(data->udev, data->पूर्णांकr_ep->bEndpoपूर्णांकAddress);

	usb_fill_पूर्णांक_urb(urb, data->udev, pipe, buf, size,
			 btusb_पूर्णांकr_complete, hdev, data->पूर्णांकr_ep->bInterval);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->पूर्णांकr_anchor);

	err = usb_submit_urb(urb, mem_flags);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम btusb_bulk_complete(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस;

	अगर (urb->status == 0) अणु
		hdev->stat.byte_rx += urb->actual_length;

		अगर (data->recv_bulk(data, urb->transfer_buffer,
				    urb->actual_length) < 0) अणु
			bt_dev_err(hdev, "corrupted ACL packet");
			hdev->stat.err_rx++;
		पूर्ण
	पूर्ण अन्यथा अगर (urb->status == -ENOENT) अणु
		/* Aव्योम suspend failed when usb_समाप्त_urb */
		वापस;
	पूर्ण

	अगर (!test_bit(BTUSB_BULK_RUNNING, &data->flags))
		वापस;

	usb_anchor_urb(urb, &data->bulk_anchor);
	usb_mark_last_busy(data->udev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक btusb_submit_bulk_urb(काष्ठा hci_dev *hdev, gfp_t mem_flags)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size = HCI_MAX_FRAME_SIZE;

	BT_DBG("%s", hdev->name);

	अगर (!data->bulk_rx_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	अगर (!urb)
		वापस -ENOMEM;

	buf = kदो_स्मृति(size, mem_flags);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvbulkpipe(data->udev, data->bulk_rx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe, buf, size,
			  btusb_bulk_complete, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_mark_last_busy(data->udev);
	usb_anchor_urb(urb, &data->bulk_anchor);

	err = usb_submit_urb(urb, mem_flags);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम btusb_isoc_complete(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक i, err;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस;

	अगर (urb->status == 0) अणु
		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			अचिन्हित पूर्णांक offset = urb->iso_frame_desc[i].offset;
			अचिन्हित पूर्णांक length = urb->iso_frame_desc[i].actual_length;

			अगर (urb->iso_frame_desc[i].status)
				जारी;

			hdev->stat.byte_rx += length;

			अगर (btusb_recv_isoc(data, urb->transfer_buffer + offset,
					    length) < 0) अणु
				bt_dev_err(hdev, "corrupted SCO packet");
				hdev->stat.err_rx++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (urb->status == -ENOENT) अणु
		/* Aव्योम suspend failed when usb_समाप्त_urb */
		वापस;
	पूर्ण

	अगर (!test_bit(BTUSB_ISOC_RUNNING, &data->flags))
		वापस;

	usb_anchor_urb(urb, &data->isoc_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __fill_isoc_descriptor_msbc(काष्ठा urb *urb, पूर्णांक len,
					       पूर्णांक mtu, काष्ठा btusb_data *data)
अणु
	पूर्णांक i, offset = 0;
	अचिन्हित पूर्णांक पूर्णांकerval;

	BT_DBG("len %d mtu %d", len, mtu);

	/* For mSBC ALT 6 setting the host will send the packet at continuous
	 * flow. As per core spec 5, vol 4, part B, table 2.1. For ALT setting
	 * 6 the HCI PACKET INTERVAL should be 7.5ms क्रम every usb packets.
	 * To मुख्यtain the rate we send 63bytes of usb packets alternatively क्रम
	 * 7ms and 8ms to मुख्यtain the rate as 7.5ms.
	 */
	अगर (data->usb_alt6_packet_flow) अणु
		पूर्णांकerval = 7;
		data->usb_alt6_packet_flow = false;
	पूर्ण अन्यथा अणु
		पूर्णांकerval = 6;
		data->usb_alt6_packet_flow = true;
	पूर्ण

	क्रम (i = 0; i < पूर्णांकerval; i++) अणु
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = offset;
	पूर्ण

	अगर (len && i < BTUSB_MAX_ISOC_FRAMES) अणु
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = len;
		i++;
	पूर्ण

	urb->number_of_packets = i;
पूर्ण

अटल अंतरभूत व्योम __fill_isoc_descriptor(काष्ठा urb *urb, पूर्णांक len, पूर्णांक mtu)
अणु
	पूर्णांक i, offset = 0;

	BT_DBG("len %d mtu %d", len, mtu);

	क्रम (i = 0; i < BTUSB_MAX_ISOC_FRAMES && len >= mtu;
					i++, offset += mtu, len -= mtu) अणु
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = mtu;
	पूर्ण

	अगर (len && i < BTUSB_MAX_ISOC_FRAMES) अणु
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = len;
		i++;
	पूर्ण

	urb->number_of_packets = i;
पूर्ण

अटल पूर्णांक btusb_submit_isoc_urb(काष्ठा hci_dev *hdev, gfp_t mem_flags)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size;

	BT_DBG("%s", hdev->name);

	अगर (!data->isoc_rx_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, mem_flags);
	अगर (!urb)
		वापस -ENOMEM;

	size = le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize) *
						BTUSB_MAX_ISOC_FRAMES;

	buf = kदो_स्मृति(size, mem_flags);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvisocpipe(data->udev, data->isoc_rx_ep->bEndpoपूर्णांकAddress);

	usb_fill_पूर्णांक_urb(urb, data->udev, pipe, buf, size, btusb_isoc_complete,
			 hdev, data->isoc_rx_ep->bInterval);

	urb->transfer_flags = URB_FREE_BUFFER | URB_ISO_ASAP;

	__fill_isoc_descriptor(urb, size,
			       le16_to_cpu(data->isoc_rx_ep->wMaxPacketSize));

	usb_anchor_urb(urb, &data->isoc_anchor);

	err = usb_submit_urb(urb, mem_flags);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम btusb_diag_complete(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (urb->status == 0) अणु
		काष्ठा sk_buff *skb;

		skb = bt_skb_alloc(urb->actual_length, GFP_ATOMIC);
		अगर (skb) अणु
			skb_put_data(skb, urb->transfer_buffer,
				     urb->actual_length);
			hci_recv_diag(hdev, skb);
		पूर्ण
	पूर्ण अन्यथा अगर (urb->status == -ENOENT) अणु
		/* Aव्योम suspend failed when usb_समाप्त_urb */
		वापस;
	पूर्ण

	अगर (!test_bit(BTUSB_DIAG_RUNNING, &data->flags))
		वापस;

	usb_anchor_urb(urb, &data->diag_anchor);
	usb_mark_last_busy(data->udev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक btusb_submit_diag_urb(काष्ठा hci_dev *hdev, gfp_t mem_flags)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size = HCI_MAX_FRAME_SIZE;

	BT_DBG("%s", hdev->name);

	अगर (!data->diag_rx_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	अगर (!urb)
		वापस -ENOMEM;

	buf = kदो_स्मृति(size, mem_flags);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvbulkpipe(data->udev, data->diag_rx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe, buf, size,
			  btusb_diag_complete, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_mark_last_busy(data->udev);
	usb_anchor_urb(urb, &data->diag_anchor);

	err = usb_submit_urb(urb, mem_flags);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम btusb_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा hci_dev *hdev = (काष्ठा hci_dev *)skb->dev;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		जाओ करोne;

	अगर (!urb->status)
		hdev->stat.byte_tx += urb->transfer_buffer_length;
	अन्यथा
		hdev->stat.err_tx++;

करोne:
	spin_lock_irqsave(&data->txlock, flags);
	data->tx_in_flight--;
	spin_unlock_irqrestore(&data->txlock, flags);

	kमुक्त(urb->setup_packet);

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम btusb_isoc_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा hci_dev *hdev = (काष्ठा hci_dev *)skb->dev;

	BT_DBG("%s urb %p status %d count %d", hdev->name, urb, urb->status,
	       urb->actual_length);

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		जाओ करोne;

	अगर (!urb->status)
		hdev->stat.byte_tx += urb->transfer_buffer_length;
	अन्यथा
		hdev->stat.err_tx++;

करोne:
	kमुक्त(urb->setup_packet);

	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक btusb_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	err = usb_स्वतःpm_get_पूर्णांकerface(data->पूर्णांकf);
	अगर (err < 0)
		वापस err;

	/* Patching USB firmware files prior to starting any URBs of HCI path
	 * It is more safe to use USB bulk channel क्रम करोwnloading USB patch
	 */
	अगर (data->setup_on_usb) अणु
		err = data->setup_on_usb(hdev);
		अगर (err < 0)
			जाओ setup_fail;
	पूर्ण

	data->पूर्णांकf->needs_remote_wakeup = 1;

	/* Disable device remote wakeup when host is suspended
	 * For Realtek chips, global suspend without
	 * SET_FEATURE (DEVICE_REMOTE_WAKEUP) can save more घातer in device.
	 */
	अगर (test_bit(BTUSB_WAKEUP_DISABLE, &data->flags))
		device_wakeup_disable(&data->udev->dev);

	अगर (test_and_set_bit(BTUSB_INTR_RUNNING, &data->flags))
		जाओ करोne;

	err = btusb_submit_पूर्णांकr_urb(hdev, GFP_KERNEL);
	अगर (err < 0)
		जाओ failed;

	err = btusb_submit_bulk_urb(hdev, GFP_KERNEL);
	अगर (err < 0) अणु
		usb_समाप्त_anchored_urbs(&data->पूर्णांकr_anchor);
		जाओ failed;
	पूर्ण

	set_bit(BTUSB_BULK_RUNNING, &data->flags);
	btusb_submit_bulk_urb(hdev, GFP_KERNEL);

	अगर (data->diag) अणु
		अगर (!btusb_submit_diag_urb(hdev, GFP_KERNEL))
			set_bit(BTUSB_DIAG_RUNNING, &data->flags);
	पूर्ण

करोne:
	usb_स्वतःpm_put_पूर्णांकerface(data->पूर्णांकf);
	वापस 0;

failed:
	clear_bit(BTUSB_INTR_RUNNING, &data->flags);
setup_fail:
	usb_स्वतःpm_put_पूर्णांकerface(data->पूर्णांकf);
	वापस err;
पूर्ण

अटल व्योम btusb_stop_traffic(काष्ठा btusb_data *data)
अणु
	usb_समाप्त_anchored_urbs(&data->पूर्णांकr_anchor);
	usb_समाप्त_anchored_urbs(&data->bulk_anchor);
	usb_समाप्त_anchored_urbs(&data->isoc_anchor);
	usb_समाप्त_anchored_urbs(&data->diag_anchor);
	usb_समाप्त_anchored_urbs(&data->ctrl_anchor);
पूर्ण

अटल पूर्णांक btusb_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	cancel_work_sync(&data->work);
	cancel_work_sync(&data->waker);

	clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
	clear_bit(BTUSB_BULK_RUNNING, &data->flags);
	clear_bit(BTUSB_INTR_RUNNING, &data->flags);
	clear_bit(BTUSB_DIAG_RUNNING, &data->flags);

	btusb_stop_traffic(data);
	btusb_मुक्त_frags(data);

	err = usb_स्वतःpm_get_पूर्णांकerface(data->पूर्णांकf);
	अगर (err < 0)
		जाओ failed;

	data->पूर्णांकf->needs_remote_wakeup = 0;

	/* Enable remote wake up क्रम स्वतः-suspend */
	अगर (test_bit(BTUSB_WAKEUP_DISABLE, &data->flags))
		data->पूर्णांकf->needs_remote_wakeup = 1;

	usb_स्वतःpm_put_पूर्णांकerface(data->पूर्णांकf);

failed:
	usb_scuttle_anchored_urbs(&data->deferred);
	वापस 0;
पूर्ण

अटल पूर्णांक btusb_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_समाप्त_anchored_urbs(&data->tx_anchor);
	btusb_मुक्त_frags(data);

	वापस 0;
पूर्ण

अटल काष्ठा urb *alloc_ctrl_urb(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा usb_ctrlrequest *dr;
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस ERR_PTR(-ENOMEM);

	dr = kदो_स्मृति(माप(*dr), GFP_KERNEL);
	अगर (!dr) अणु
		usb_मुक्त_urb(urb);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dr->bRequestType = data->cmdreq_type;
	dr->bRequest     = data->cmdreq;
	dr->wIndex       = 0;
	dr->wValue       = 0;
	dr->wLength      = __cpu_to_le16(skb->len);

	pipe = usb_sndctrlpipe(data->udev, 0x00);

	usb_fill_control_urb(urb, data->udev, pipe, (व्योम *)dr,
			     skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (व्योम *)hdev;

	वापस urb;
पूर्ण

अटल काष्ठा urb *alloc_bulk_urb(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;

	अगर (!data->bulk_tx_ep)
		वापस ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस ERR_PTR(-ENOMEM);

	pipe = usb_sndbulkpipe(data->udev, data->bulk_tx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe,
			  skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (व्योम *)hdev;

	वापस urb;
पूर्ण

अटल काष्ठा urb *alloc_isoc_urb(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;

	अगर (!data->isoc_tx_ep)
		वापस ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, GFP_KERNEL);
	अगर (!urb)
		वापस ERR_PTR(-ENOMEM);

	pipe = usb_sndisocpipe(data->udev, data->isoc_tx_ep->bEndpoपूर्णांकAddress);

	usb_fill_पूर्णांक_urb(urb, data->udev, pipe,
			 skb->data, skb->len, btusb_isoc_tx_complete,
			 skb, data->isoc_tx_ep->bInterval);

	urb->transfer_flags  = URB_ISO_ASAP;

	अगर (data->isoc_altsetting == 6)
		__fill_isoc_descriptor_msbc(urb, skb->len,
					    le16_to_cpu(data->isoc_tx_ep->wMaxPacketSize),
					    data);
	अन्यथा
		__fill_isoc_descriptor(urb, skb->len,
				       le16_to_cpu(data->isoc_tx_ep->wMaxPacketSize));
	skb->dev = (व्योम *)hdev;

	वापस urb;
पूर्ण

अटल पूर्णांक submit_tx_urb(काष्ठा hci_dev *hdev, काष्ठा urb *urb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	usb_anchor_urb(urb, &data->tx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		kमुक्त(urb->setup_packet);
		usb_unanchor_urb(urb);
	पूर्ण अन्यथा अणु
		usb_mark_last_busy(data->udev);
	पूर्ण

	usb_मुक्त_urb(urb);
	वापस err;
पूर्ण

अटल पूर्णांक submit_or_queue_tx_urb(काष्ठा hci_dev *hdev, काष्ठा urb *urb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;
	bool suspending;

	spin_lock_irqsave(&data->txlock, flags);
	suspending = test_bit(BTUSB_SUSPENDING, &data->flags);
	अगर (!suspending)
		data->tx_in_flight++;
	spin_unlock_irqrestore(&data->txlock, flags);

	अगर (!suspending)
		वापस submit_tx_urb(hdev, urb);

	usb_anchor_urb(urb, &data->deferred);
	schedule_work(&data->waker);

	usb_मुक्त_urb(urb);
	वापस 0;
पूर्ण

अटल पूर्णांक btusb_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा urb *urb;

	BT_DBG("%s", hdev->name);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		urb = alloc_ctrl_urb(hdev, skb);
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.cmd_tx++;
		वापस submit_or_queue_tx_urb(hdev, urb);

	हाल HCI_ACLDATA_PKT:
		urb = alloc_bulk_urb(hdev, skb);
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.acl_tx++;
		वापस submit_or_queue_tx_urb(hdev, urb);

	हाल HCI_SCODATA_PKT:
		अगर (hci_conn_num(hdev, SCO_LINK) < 1)
			वापस -ENODEV;

		urb = alloc_isoc_urb(hdev, skb);
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.sco_tx++;
		वापस submit_tx_urb(hdev, urb);
	पूर्ण

	वापस -EILSEQ;
पूर्ण

अटल व्योम btusb_notअगरy(काष्ठा hci_dev *hdev, अचिन्हित पूर्णांक evt)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s evt %d", hdev->name, evt);

	अगर (hci_conn_num(hdev, SCO_LINK) != data->sco_num) अणु
		data->sco_num = hci_conn_num(hdev, SCO_LINK);
		data->air_mode = evt;
		schedule_work(&data->work);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __set_isoc_पूर्णांकerface(काष्ठा hci_dev *hdev, पूर्णांक altsetting)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = data->isoc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक i, err;

	अगर (!data->isoc)
		वापस -ENODEV;

	err = usb_set_पूर्णांकerface(data->udev, data->isoc_अगरnum, altsetting);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "setting interface failed (%d)", -err);
		वापस err;
	पूर्ण

	data->isoc_altsetting = altsetting;

	data->isoc_tx_ep = शून्य;
	data->isoc_rx_ep = शून्य;

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (!data->isoc_tx_ep && usb_endpoपूर्णांक_is_isoc_out(ep_desc)) अणु
			data->isoc_tx_ep = ep_desc;
			जारी;
		पूर्ण

		अगर (!data->isoc_rx_ep && usb_endpoपूर्णांक_is_isoc_in(ep_desc)) अणु
			data->isoc_rx_ep = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!data->isoc_tx_ep || !data->isoc_rx_ep) अणु
		bt_dev_err(hdev, "invalid SCO descriptors");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_चयन_alt_setting(काष्ठा hci_dev *hdev, पूर्णांक new_alts)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	अगर (data->isoc_altsetting != new_alts) अणु
		अचिन्हित दीर्घ flags;

		clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
		usb_समाप्त_anchored_urbs(&data->isoc_anchor);

		/* When isochronous alternate setting needs to be
		 * changed, because SCO connection has been added
		 * or हटाओd, a packet fragment may be left in the
		 * reassembling state. This could lead to wrongly
		 * assembled fragments.
		 *
		 * Clear outstanding fragment when selecting a new
		 * alternate setting.
		 */
		spin_lock_irqsave(&data->rxlock, flags);
		kमुक्त_skb(data->sco_skb);
		data->sco_skb = शून्य;
		spin_unlock_irqrestore(&data->rxlock, flags);

		err = __set_isoc_पूर्णांकerface(hdev, new_alts);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!test_and_set_bit(BTUSB_ISOC_RUNNING, &data->flags)) अणु
		अगर (btusb_submit_isoc_urb(hdev, GFP_KERNEL) < 0)
			clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
		अन्यथा
			btusb_submit_isoc_urb(hdev, GFP_KERNEL);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usb_host_पूर्णांकerface *btusb_find_altsetting(काष्ठा btusb_data *data,
							पूर्णांक alt)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = data->isoc;
	पूर्णांक i;

	BT_DBG("Looking for Alt no :%d", alt);

	अगर (!पूर्णांकf)
		वापस शून्य;

	क्रम (i = 0; i < पूर्णांकf->num_altsetting; i++) अणु
		अगर (पूर्णांकf->altsetting[i].desc.bAlternateSetting == alt)
			वापस &पूर्णांकf->altsetting[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम btusb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btusb_data *data = container_of(work, काष्ठा btusb_data, work);
	काष्ठा hci_dev *hdev = data->hdev;
	पूर्णांक new_alts = 0;
	पूर्णांक err;

	अगर (data->sco_num > 0) अणु
		अगर (!test_bit(BTUSB_DID_ISO_RESUME, &data->flags)) अणु
			err = usb_स्वतःpm_get_पूर्णांकerface(data->isoc ? data->isoc : data->पूर्णांकf);
			अगर (err < 0) अणु
				clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
				usb_समाप्त_anchored_urbs(&data->isoc_anchor);
				वापस;
			पूर्ण

			set_bit(BTUSB_DID_ISO_RESUME, &data->flags);
		पूर्ण

		अगर (data->air_mode == HCI_NOTIFY_ENABLE_SCO_CVSD) अणु
			अगर (hdev->voice_setting & 0x0020) अणु
				अटल स्थिर पूर्णांक alts[3] = अणु 2, 4, 5 पूर्ण;

				new_alts = alts[data->sco_num - 1];
			पूर्ण अन्यथा अणु
				new_alts = data->sco_num;
			पूर्ण
		पूर्ण अन्यथा अगर (data->air_mode == HCI_NOTIFY_ENABLE_SCO_TRANSP) अणु
			/* Bluetooth USB spec recommends alt 6 (63 bytes), but
			 * many adapters करो not support it.  Alt 1 appears to
			 * work क्रम all adapters that करो not have alt 6, and
			 * which work with WBS at all.
			 */
			new_alts = btusb_find_altsetting(data, 6) ? 6 : 1;
		पूर्ण

		अगर (btusb_चयन_alt_setting(hdev, new_alts) < 0)
			bt_dev_err(hdev, "set USB alt:(%d) failed!", new_alts);
	पूर्ण अन्यथा अणु
		clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
		usb_समाप्त_anchored_urbs(&data->isoc_anchor);

		__set_isoc_पूर्णांकerface(hdev, 0);
		अगर (test_and_clear_bit(BTUSB_DID_ISO_RESUME, &data->flags))
			usb_स्वतःpm_put_पूर्णांकerface(data->isoc ? data->isoc : data->पूर्णांकf);
	पूर्ण
पूर्ण

अटल व्योम btusb_waker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btusb_data *data = container_of(work, काष्ठा btusb_data, waker);
	पूर्णांक err;

	err = usb_स्वतःpm_get_पूर्णांकerface(data->पूर्णांकf);
	अगर (err < 0)
		वापस;

	usb_स्वतःpm_put_पूर्णांकerface(data->पूर्णांकf);
पूर्ण

अटल पूर्णांक btusb_setup_bcm92035(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	u8 val = 0x00;

	BT_DBG("%s", hdev->name);

	skb = __hci_cmd_sync(hdev, 0xfc3b, 1, &val, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		bt_dev_err(hdev, "BCM92035 command failed (%ld)", PTR_ERR(skb));
	अन्यथा
		kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_setup_csr(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	u16 bcdDevice = le16_to_cpu(data->udev->descriptor.bcdDevice);
	काष्ठा hci_rp_पढ़ो_local_version *rp;
	काष्ठा sk_buff *skb;
	bool is_fake = false;
	पूर्णांक ret;

	BT_DBG("%s", hdev->name);

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);
		bt_dev_err(hdev, "CSR: Local version failed (%d)", err);
		वापस err;
	पूर्ण

	अगर (skb->len != माप(काष्ठा hci_rp_पढ़ो_local_version)) अणु
		bt_dev_err(hdev, "CSR: Local version length mismatch");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	rp = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;

	/* Detect a wide host of Chinese controllers that aren't CSR.
	 *
	 * Known fake bcdDevices: 0x0100, 0x0134, 0x1915, 0x2520, 0x7558, 0x8891
	 *
	 * The मुख्य thing they have in common is that these are really popular low-cost
	 * options that support newer Bluetooth versions but rely on heavy VID/PID
	 * squatting of this poor old Bluetooth 1.1 device. Even sold as such.
	 *
	 * We detect actual CSR devices by checking that the HCI manufacturer code
	 * is Cambridge Silicon Radio (10) and ensuring that LMP sub-version and
	 * HCI rev values always match. As they both store the firmware number.
	 */
	अगर (le16_to_cpu(rp->manufacturer) != 10 ||
	    le16_to_cpu(rp->hci_rev) != le16_to_cpu(rp->lmp_subver))
		is_fake = true;

	/* Known legit CSR firmware build numbers and their supported BT versions:
	 * - 1.1 (0x1) -> 0x0073, 0x020d, 0x033c, 0x034e
	 * - 1.2 (0x2) ->                 0x04d9, 0x0529
	 * - 2.0 (0x3) ->         0x07a6, 0x07ad, 0x0c5c
	 * - 2.1 (0x4) ->         0x149c, 0x1735, 0x1899 (0x1899 is a BlueCore4-External)
	 * - 4.0 (0x6) ->         0x1d86, 0x2031, 0x22bb
	 *
	 * e.g. Real CSR करोngles with LMP subversion 0x73 are old enough that
	 *      support BT 1.1 only; so it's a dead giveaway when some
	 *      third-party BT 4.0 करोngle reuses it.
	 */
	अन्यथा अगर (le16_to_cpu(rp->lmp_subver) <= 0x034e &&
		 le16_to_cpu(rp->hci_ver) > BLUETOOTH_VER_1_1)
		is_fake = true;

	अन्यथा अगर (le16_to_cpu(rp->lmp_subver) <= 0x0529 &&
		 le16_to_cpu(rp->hci_ver) > BLUETOOTH_VER_1_2)
		is_fake = true;

	अन्यथा अगर (le16_to_cpu(rp->lmp_subver) <= 0x0c5c &&
		 le16_to_cpu(rp->hci_ver) > BLUETOOTH_VER_2_0)
		is_fake = true;

	अन्यथा अगर (le16_to_cpu(rp->lmp_subver) <= 0x1899 &&
		 le16_to_cpu(rp->hci_ver) > BLUETOOTH_VER_2_1)
		is_fake = true;

	अन्यथा अगर (le16_to_cpu(rp->lmp_subver) <= 0x22bb &&
		 le16_to_cpu(rp->hci_ver) > BLUETOOTH_VER_4_0)
		is_fake = true;

	/* Other clones which beat all the above checks */
	अन्यथा अगर (bcdDevice == 0x0134 &&
		 le16_to_cpu(rp->lmp_subver) == 0x0c5c &&
		 le16_to_cpu(rp->hci_ver) == BLUETOOTH_VER_2_0)
		is_fake = true;

	अगर (is_fake) अणु
		bt_dev_warn(hdev, "CSR: Unbranded CSR clone detected; adding workarounds...");

		/* Generally these clones have big discrepancies between
		 * advertised features and what's actually supported.
		 * Probably will need to be expanded in the future;
		 * without these the controller will lock up.
		 */
		set_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks);
		set_bit(HCI_QUIRK_BROKEN_ERR_DATA_REPORTING, &hdev->quirks);

		/* Clear the reset quirk since this is not an actual
		 * early Bluetooth 1.1 device from CSR.
		 */
		clear_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);
		clear_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

		/*
		 * Special workaround क्रम clones with a Barrot 8041a02 chip,
		 * these clones are really messed-up:
		 * 1. Their bulk rx endpoपूर्णांक will never report any data unless
		 * the device was suspended at least once (yes really).
		 * 2. They will not wakeup when स्वतःsuspended and receiving data
		 * on their bulk rx endpoपूर्णांक from e.g. a keyboard or mouse
		 * (IOW remote-wakeup support is broken क्रम the bulk endpoपूर्णांक).
		 *
		 * To fix 1. enable runसमय-suspend, क्रमce-suspend the
		 * hci and then wake-it up by disabling runसमय-suspend.
		 *
		 * To fix 2. clear the hci's can_wake flag, this way the hci
		 * will still be स्वतःsuspended when it is not खोलो.
		 */
		अगर (bcdDevice == 0x8891 &&
		    le16_to_cpu(rp->lmp_subver) == 0x1012 &&
		    le16_to_cpu(rp->hci_rev) == 0x0810 &&
		    le16_to_cpu(rp->hci_ver) == BLUETOOTH_VER_4_0) अणु
			bt_dev_warn(hdev, "CSR: detected a fake CSR dongle using a Barrot 8041a02 chip, this chip is very buggy and may have issues");

			pm_runसमय_allow(&data->udev->dev);

			ret = pm_runसमय_suspend(&data->udev->dev);
			अगर (ret >= 0)
				msleep(200);
			अन्यथा
				bt_dev_err(hdev, "Failed to suspend the device for Barrot 8041a02 receive-issue workaround");

			pm_runसमय_क्रमbid(&data->udev->dev);

			device_set_wakeup_capable(&data->udev->dev, false);
			/* Re-enable स्वतःsuspend अगर this was requested */
			अगर (enable_स्वतःsuspend)
				usb_enable_स्वतःsuspend(data->udev);
		पूर्ण
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा firmware *btusb_setup_पूर्णांकel_get_fw(काष्ठा hci_dev *hdev,
						       काष्ठा पूर्णांकel_version *ver)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर fwname[64];
	पूर्णांक ret;

	snम_लिखो(fwname, माप(fwname),
		 "intel/ibt-hw-%x.%x.%x-fw-%x.%x.%x.%x.%x.bseq",
		 ver->hw_platक्रमm, ver->hw_variant, ver->hw_revision,
		 ver->fw_variant,  ver->fw_revision, ver->fw_build_num,
		 ver->fw_build_ww, ver->fw_build_yy);

	ret = request_firmware(&fw, fwname, &hdev->dev);
	अगर (ret < 0) अणु
		अगर (ret == -EINVAL) अणु
			bt_dev_err(hdev, "Intel firmware file request failed (%d)",
				   ret);
			वापस शून्य;
		पूर्ण

		bt_dev_err(hdev, "failed to open Intel firmware file: %s (%d)",
			   fwname, ret);

		/* If the correct firmware patch file is not found, use the
		 * शेष firmware patch file instead
		 */
		snम_लिखो(fwname, माप(fwname), "intel/ibt-hw-%x.%x.bseq",
			 ver->hw_platक्रमm, ver->hw_variant);
		अगर (request_firmware(&fw, fwname, &hdev->dev) < 0) अणु
			bt_dev_err(hdev, "failed to open default fw file: %s",
				   fwname);
			वापस शून्य;
		पूर्ण
	पूर्ण

	bt_dev_info(hdev, "Intel Bluetooth firmware file: %s", fwname);

	वापस fw;
पूर्ण

अटल पूर्णांक btusb_setup_पूर्णांकel_patching(काष्ठा hci_dev *hdev,
				      स्थिर काष्ठा firmware *fw,
				      स्थिर u8 **fw_ptr, पूर्णांक *disable_patch)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hci_command_hdr *cmd;
	स्थिर u8 *cmd_param;
	काष्ठा hci_event_hdr *evt = शून्य;
	स्थिर u8 *evt_param = शून्य;
	पूर्णांक reमुख्य = fw->size - (*fw_ptr - fw->data);

	/* The first byte indicates the types of the patch command or event.
	 * 0x01 means HCI command and 0x02 is HCI event. If the first bytes
	 * in the current firmware buffer करोesn't start with 0x01 or
	 * the size of reमुख्य buffer is smaller than HCI command header,
	 * the firmware file is corrupted and it should stop the patching
	 * process.
	 */
	अगर (reमुख्य > HCI_COMMAND_HDR_SIZE && *fw_ptr[0] != 0x01) अणु
		bt_dev_err(hdev, "Intel fw corrupted: invalid cmd read");
		वापस -EINVAL;
	पूर्ण
	(*fw_ptr)++;
	reमुख्य--;

	cmd = (काष्ठा hci_command_hdr *)(*fw_ptr);
	*fw_ptr += माप(*cmd);
	reमुख्य -= माप(*cmd);

	/* Ensure that the reमुख्य firmware data is दीर्घ enough than the length
	 * of command parameter. If not, the firmware file is corrupted.
	 */
	अगर (reमुख्य < cmd->plen) अणु
		bt_dev_err(hdev, "Intel fw corrupted: invalid cmd len");
		वापस -EFAULT;
	पूर्ण

	/* If there is a command that loads a patch in the firmware
	 * file, then enable the patch upon success, otherwise just
	 * disable the manufacturer mode, क्रम example patch activation
	 * is not required when the शेष firmware patch file is used
	 * because there are no patch data to load.
	 */
	अगर (*disable_patch && le16_to_cpu(cmd->opcode) == 0xfc8e)
		*disable_patch = 0;

	cmd_param = *fw_ptr;
	*fw_ptr += cmd->plen;
	reमुख्य -= cmd->plen;

	/* This पढ़ोs the expected events when the above command is sent to the
	 * device. Some venकरोr commands expects more than one events, क्रम
	 * example command status event followed by venकरोr specअगरic event.
	 * For this हाल, it only keeps the last expected event. so the command
	 * can be sent with __hci_cmd_sync_ev() which वापसs the sk_buff of
	 * last expected event.
	 */
	जबतक (reमुख्य > HCI_EVENT_HDR_SIZE && *fw_ptr[0] == 0x02) अणु
		(*fw_ptr)++;
		reमुख्य--;

		evt = (काष्ठा hci_event_hdr *)(*fw_ptr);
		*fw_ptr += माप(*evt);
		reमुख्य -= माप(*evt);

		अगर (reमुख्य < evt->plen) अणु
			bt_dev_err(hdev, "Intel fw corrupted: invalid evt len");
			वापस -EFAULT;
		पूर्ण

		evt_param = *fw_ptr;
		*fw_ptr += evt->plen;
		reमुख्य -= evt->plen;
	पूर्ण

	/* Every HCI commands in the firmware file has its correspond event.
	 * If event is not found or reमुख्य is smaller than zero, the firmware
	 * file is corrupted.
	 */
	अगर (!evt || !evt_param || reमुख्य < 0) अणु
		bt_dev_err(hdev, "Intel fw corrupted: invalid evt read");
		वापस -EFAULT;
	पूर्ण

	skb = __hci_cmd_sync_ev(hdev, le16_to_cpu(cmd->opcode), cmd->plen,
				cmd_param, evt->evt, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "sending Intel patch command (0x%4.4x) failed (%ld)",
			   cmd->opcode, PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	/* It ensures that the वापसed event matches the event data पढ़ो from
	 * the firmware file. At fist, it checks the length and then
	 * the contents of the event.
	 */
	अगर (skb->len != evt->plen) अणु
		bt_dev_err(hdev, "mismatch event length (opcode 0x%4.4x)",
			   le16_to_cpu(cmd->opcode));
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण

	अगर (स_भेद(skb->data, evt_param, evt->plen)) अणु
		bt_dev_err(hdev, "mismatch event parameter (opcode 0x%4.4x)",
			   le16_to_cpu(cmd->opcode));
		kमुक्त_skb(skb);
		वापस -EFAULT;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_setup_पूर्णांकel(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	पूर्णांक disable_patch, err;
	काष्ठा पूर्णांकel_version ver;

	BT_DBG("%s", hdev->name);

	/* The controller has a bug with the first HCI command sent to it
	 * वापसing number of completed commands as zero. This would stall the
	 * command processing in the Bluetooth core.
	 *
	 * As a workaround, send HCI Reset command first which will reset the
	 * number of completed commands and allow normal command processing
	 * from now on.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "sending initial HCI reset command failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	/* Read Intel specअगरic controller version first to allow selection of
	 * which firmware file to load.
	 *
	 * The वापसed inक्रमmation are hardware variant and revision plus
	 * firmware variant, revision and build number.
	 */
	err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
	अगर (err)
		वापस err;

	bt_dev_info(hdev, "read Intel version: %02x%02x%02x%02x%02x%02x%02x%02x%02x",
		    ver.hw_platक्रमm, ver.hw_variant, ver.hw_revision,
		    ver.fw_variant,  ver.fw_revision, ver.fw_build_num,
		    ver.fw_build_ww, ver.fw_build_yy, ver.fw_patch_num);

	/* fw_patch_num indicates the version of patch the device currently
	 * have. If there is no patch data in the device, it is always 0x00.
	 * So, अगर it is other than 0x00, no need to patch the device again.
	 */
	अगर (ver.fw_patch_num) अणु
		bt_dev_info(hdev, "Intel device is already patched. "
			    "patch num: %02x", ver.fw_patch_num);
		जाओ complete;
	पूर्ण

	/* Opens the firmware patch file based on the firmware version पढ़ो
	 * from the controller. If it fails to खोलो the matching firmware
	 * patch file, it tries to खोलो the शेष firmware patch file.
	 * If no patch file is found, allow the device to operate without
	 * a patch.
	 */
	fw = btusb_setup_पूर्णांकel_get_fw(hdev, &ver);
	अगर (!fw)
		जाओ complete;
	fw_ptr = fw->data;

	/* Enable the manufacturer mode of the controller.
	 * Only जबतक this mode is enabled, the driver can करोwnload the
	 * firmware patch data and configuration parameters.
	 */
	err = btपूर्णांकel_enter_mfg(hdev);
	अगर (err) अणु
		release_firmware(fw);
		वापस err;
	पूर्ण

	disable_patch = 1;

	/* The firmware data file consists of list of Intel specअगरic HCI
	 * commands and its expected events. The first byte indicates the
	 * type of the message, either HCI command or HCI event.
	 *
	 * It पढ़ोs the command and its expected event from the firmware file,
	 * and send to the controller. Once __hci_cmd_sync_ev() वापसs,
	 * the वापसed event is compared with the event पढ़ो from the firmware
	 * file and it will जारी until all the messages are करोwnloaded to
	 * the controller.
	 *
	 * Once the firmware patching is completed successfully,
	 * the manufacturer mode is disabled with reset and activating the
	 * करोwnloaded patch.
	 *
	 * If the firmware patching fails, the manufacturer mode is
	 * disabled with reset and deactivating the patch.
	 *
	 * If the शेष patch file is used, no reset is करोne when disabling
	 * the manufacturer.
	 */
	जबतक (fw->size > fw_ptr - fw->data) अणु
		पूर्णांक ret;

		ret = btusb_setup_पूर्णांकel_patching(hdev, fw, &fw_ptr,
						 &disable_patch);
		अगर (ret < 0)
			जाओ निकास_mfg_deactivate;
	पूर्ण

	release_firmware(fw);

	अगर (disable_patch)
		जाओ निकास_mfg_disable;

	/* Patching completed successfully and disable the manufacturer mode
	 * with reset and activate the करोwnloaded firmware patches.
	 */
	err = btपूर्णांकel_निकास_mfg(hdev, true, true);
	अगर (err)
		वापस err;

	/* Need build number क्रम करोwnloaded fw patches in
	 * every घातer-on boot
	 */
       err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
       अगर (err)
               वापस err;
       bt_dev_info(hdev, "Intel BT fw patch 0x%02x completed & activated",
		   ver.fw_patch_num);

	जाओ complete;

निकास_mfg_disable:
	/* Disable the manufacturer mode without reset */
	err = btपूर्णांकel_निकास_mfg(hdev, false, false);
	अगर (err)
		वापस err;

	bt_dev_info(hdev, "Intel firmware patch completed");

	जाओ complete;

निकास_mfg_deactivate:
	release_firmware(fw);

	/* Patching failed. Disable the manufacturer mode with reset and
	 * deactivate the करोwnloaded firmware patches.
	 */
	err = btपूर्णांकel_निकास_mfg(hdev, true, false);
	अगर (err)
		वापस err;

	bt_dev_info(hdev, "Intel firmware patch completed and deactivated");

complete:
	/* Set the event mask क्रम Intel specअगरic venकरोr events. This enables
	 * a few extra events that are useful during general operation.
	 */
	btपूर्णांकel_set_event_mask_mfg(hdev, false);

	btपूर्णांकel_check_bdaddr(hdev);
	वापस 0;
पूर्ण

अटल पूर्णांक inject_cmd_complete(काष्ठा hci_dev *hdev, __u16 opcode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hci_event_hdr *hdr;
	काष्ठा hci_ev_cmd_complete *evt;

	skb = bt_skb_alloc(माप(*hdr) + माप(*evt) + 1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));
	hdr->evt = HCI_EV_CMD_COMPLETE;
	hdr->plen = माप(*evt) + 1;

	evt = skb_put(skb, माप(*evt));
	evt->ncmd = 0x01;
	evt->opcode = cpu_to_le16(opcode);

	skb_put_u8(skb, 0x00);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक btusb_recv_bulk_पूर्णांकel(काष्ठा btusb_data *data, व्योम *buffer,
				 पूर्णांक count)
अणु
	/* When the device is in bootloader mode, then it can send
	 * events via the bulk endpoपूर्णांक. These events are treated the
	 * same way as the ones received from the पूर्णांकerrupt endpoपूर्णांक.
	 */
	अगर (test_bit(BTUSB_BOOTLOADER, &data->flags))
		वापस btusb_recv_पूर्णांकr(data, buffer, count);

	वापस btusb_recv_bulk(data, buffer, count);
पूर्ण

अटल व्योम btusb_पूर्णांकel_bootup(काष्ठा btusb_data *data, स्थिर व्योम *ptr,
			       अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा पूर्णांकel_bootup *evt = ptr;

	अगर (len != माप(*evt))
		वापस;

	अगर (test_and_clear_bit(BTUSB_BOOTING, &data->flags))
		wake_up_bit(&data->flags, BTUSB_BOOTING);
पूर्ण

अटल व्योम btusb_पूर्णांकel_secure_send_result(काष्ठा btusb_data *data,
					   स्थिर व्योम *ptr, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा पूर्णांकel_secure_send_result *evt = ptr;

	अगर (len != माप(*evt))
		वापस;

	अगर (evt->result)
		set_bit(BTUSB_FIRMWARE_FAILED, &data->flags);

	अगर (test_and_clear_bit(BTUSB_DOWNLOADING, &data->flags) &&
	    test_bit(BTUSB_FIRMWARE_LOADED, &data->flags))
		wake_up_bit(&data->flags, BTUSB_DOWNLOADING);
पूर्ण

अटल पूर्णांक btusb_recv_event_पूर्णांकel(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);

	अगर (test_bit(BTUSB_BOOTLOADER, &data->flags)) अणु
		काष्ठा hci_event_hdr *hdr = (व्योम *)skb->data;

		अगर (skb->len > HCI_EVENT_HDR_SIZE && hdr->evt == 0xff &&
		    hdr->plen > 0) अणु
			स्थिर व्योम *ptr = skb->data + HCI_EVENT_HDR_SIZE + 1;
			अचिन्हित पूर्णांक len = skb->len - HCI_EVENT_HDR_SIZE - 1;

			चयन (skb->data[2]) अणु
			हाल 0x02:
				/* When चयनing to the operational firmware
				 * the device sends a venकरोr specअगरic event
				 * indicating that the bootup completed.
				 */
				btusb_पूर्णांकel_bootup(data, ptr, len);
				अवरोध;
			हाल 0x06:
				/* When the firmware loading completes the
				 * device sends out a venकरोr specअगरic event
				 * indicating the result of the firmware
				 * loading.
				 */
				btusb_पूर्णांकel_secure_send_result(data, ptr, len);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक btusb_send_frame_पूर्णांकel(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;

	BT_DBG("%s", hdev->name);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		अगर (test_bit(BTUSB_BOOTLOADER, &data->flags)) अणु
			काष्ठा hci_command_hdr *cmd = (व्योम *)skb->data;
			__u16 opcode = le16_to_cpu(cmd->opcode);

			/* When in bootloader mode and the command 0xfc09
			 * is received, it needs to be send करोwn the
			 * bulk endpoपूर्णांक. So allocate a bulk URB instead.
			 */
			अगर (opcode == 0xfc09)
				urb = alloc_bulk_urb(hdev, skb);
			अन्यथा
				urb = alloc_ctrl_urb(hdev, skb);

			/* When the 0xfc01 command is issued to boot पूर्णांकo
			 * the operational firmware, it will actually not
			 * send a command complete event. To keep the flow
			 * control working inject that event here.
			 */
			अगर (opcode == 0xfc01)
				inject_cmd_complete(hdev, opcode);
		पूर्ण अन्यथा अणु
			urb = alloc_ctrl_urb(hdev, skb);
		पूर्ण
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.cmd_tx++;
		वापस submit_or_queue_tx_urb(hdev, urb);

	हाल HCI_ACLDATA_PKT:
		urb = alloc_bulk_urb(hdev, skb);
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.acl_tx++;
		वापस submit_or_queue_tx_urb(hdev, urb);

	हाल HCI_SCODATA_PKT:
		अगर (hci_conn_num(hdev, SCO_LINK) < 1)
			वापस -ENODEV;

		urb = alloc_isoc_urb(hdev, skb);
		अगर (IS_ERR(urb))
			वापस PTR_ERR(urb);

		hdev->stat.sco_tx++;
		वापस submit_tx_urb(hdev, urb);
	पूर्ण

	वापस -EILSEQ;
पूर्ण

अटल पूर्णांक btusb_setup_पूर्णांकel_new_get_fw_name(काष्ठा पूर्णांकel_version *ver,
					     काष्ठा पूर्णांकel_boot_params *params,
					     अक्षर *fw_name, माप_प्रकार len,
					     स्थिर अक्षर *suffix)
अणु
	चयन (ver->hw_variant) अणु
	हाल 0x0b:	/* SfP */
	हाल 0x0c:	/* WsP */
		snम_लिखो(fw_name, len, "intel/ibt-%u-%u.%s",
			le16_to_cpu(ver->hw_variant),
			le16_to_cpu(params->dev_revid),
			suffix);
		अवरोध;
	हाल 0x11:	/* JfP */
	हाल 0x12:	/* ThP */
	हाल 0x13:	/* HrP */
	हाल 0x14:	/* CcP */
		snम_लिखो(fw_name, len, "intel/ibt-%u-%u-%u.%s",
			le16_to_cpu(ver->hw_variant),
			le16_to_cpu(ver->hw_revision),
			le16_to_cpu(ver->fw_revision),
			suffix);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम btusb_setup_पूर्णांकel_newgen_get_fw_name(स्थिर काष्ठा पूर्णांकel_version_tlv *ver_tlv,
						 अक्षर *fw_name, माप_प्रकार len,
						 स्थिर अक्षर *suffix)
अणु
	/* The firmware file name क्रम new generation controllers will be
	 * ibt-<cnvi_top type+cnvi_top step>-<cnvr_top type+cnvr_top step>
	 */
	snम_लिखो(fw_name, len, "intel/ibt-%04x-%04x.%s",
		 INTEL_CNVX_TOP_PACK_SWAB(INTEL_CNVX_TOP_TYPE(ver_tlv->cnvi_top),
					  INTEL_CNVX_TOP_STEP(ver_tlv->cnvi_top)),
		 INTEL_CNVX_TOP_PACK_SWAB(INTEL_CNVX_TOP_TYPE(ver_tlv->cnvr_top),
					  INTEL_CNVX_TOP_STEP(ver_tlv->cnvr_top)),
		 suffix);
पूर्ण

अटल पूर्णांक btusb_करोwnload_रुको(काष्ठा hci_dev *hdev, kसमय_प्रकार callसमय, पूर्णांक msec)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	kसमय_प्रकार delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);

	bt_dev_info(hdev, "Waiting for firmware download to complete");

	err = रुको_on_bit_समयout(&data->flags, BTUSB_DOWNLOADING,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jअगरfies(msec));
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Firmware loading interrupted");
		वापस err;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Firmware loading timeout");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (test_bit(BTUSB_FIRMWARE_FAILED, &data->flags)) अणु
		bt_dev_err(hdev, "Firmware loading failed");
		वापस -ENOEXEC;
	पूर्ण

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Firmware loaded in %llu usecs", duration);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_पूर्णांकel_करोwnload_firmware_newgen(काष्ठा hci_dev *hdev,
						काष्ठा पूर्णांकel_version_tlv *ver,
						u32 *boot_param)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर fwname[64];
	पूर्णांक err;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	kसमय_प्रकार callसमय;

	अगर (!ver || !boot_param)
		वापस -EINVAL;

	/* The firmware variant determines अगर the device is in bootloader
	 * mode or is running operational firmware. The value 0x03 identअगरies
	 * the bootloader and the value 0x23 identअगरies the operational
	 * firmware.
	 *
	 * When the operational firmware is alपढ़ोy present, then only
	 * the check क्रम valid Bluetooth device address is needed. This
	 * determines अगर the device will be added as configured or
	 * unconfigured controller.
	 *
	 * It is not possible to use the Secure Boot Parameters in this
	 * हाल since that command is only available in bootloader mode.
	 */
	अगर (ver->img_type == 0x03) अणु
		clear_bit(BTUSB_BOOTLOADER, &data->flags);
		btपूर्णांकel_check_bdaddr(hdev);
	पूर्ण

	/* If the OTP has no valid Bluetooth device address, then there will
	 * also be no valid address क्रम the operational firmware.
	 */
	अगर (!bacmp(&ver->otp_bd_addr, BDADDR_ANY)) अणु
		bt_dev_info(hdev, "No device address configured");
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
	पूर्ण

	btusb_setup_पूर्णांकel_newgen_get_fw_name(ver, fwname, माप(fwname), "sfi");
	err = firmware_request_nowarn(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		अगर (!test_bit(BTUSB_BOOTLOADER, &data->flags)) अणु
			/* Firmware has alपढ़ोy been loaded */
			set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);
			वापस 0;
		पूर्ण

		bt_dev_err(hdev, "Failed to load Intel firmware file %s (%d)",
			   fwname, err);

		वापस err;
	पूर्ण

	bt_dev_info(hdev, "Found device firmware: %s", fwname);

	अगर (fw->size < 644) अणु
		bt_dev_err(hdev, "Invalid size of firmware file (%zu)",
			   fw->size);
		err = -EBADF;
		जाओ करोne;
	पूर्ण

	callसमय = kसमय_get();

	set_bit(BTUSB_DOWNLOADING, &data->flags);

	/* Start firmware करोwnloading and get boot parameter */
	err = btपूर्णांकel_करोwnload_firmware_newgen(hdev, ver, fw, boot_param,
					       INTEL_HW_VARIANT(ver->cnvi_bt),
					       ver->sbe_type);
	अगर (err < 0) अणु
		अगर (err == -EALREADY) अणु
			/* Firmware has alपढ़ोy been loaded */
			set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);
			err = 0;
			जाओ करोne;
		पूर्ण

		/* When FW करोwnload fails, send Intel Reset to retry
		 * FW करोwnload.
		 */
		btपूर्णांकel_reset_to_bootloader(hdev);
		जाओ करोne;
	पूर्ण

	/* Beक्रमe चयनing the device पूर्णांकo operational mode and with that
	 * booting the loaded firmware, रुको क्रम the bootloader notअगरication
	 * that all fragments have been successfully received.
	 *
	 * When the event processing receives the notअगरication, then the
	 * BTUSB_DOWNLOADING flag will be cleared.
	 *
	 * The firmware loading should not take दीर्घer than 5 seconds
	 * and thus just समयout अगर that happens and fail the setup
	 * of this device.
	 */
	err = btusb_करोwnload_रुको(hdev, callसमय, 5000);
	अगर (err == -ETIMEDOUT)
		btपूर्णांकel_reset_to_bootloader(hdev);

करोne:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक btusb_पूर्णांकel_करोwnload_firmware(काष्ठा hci_dev *hdev,
					 काष्ठा पूर्णांकel_version *ver,
					 काष्ठा पूर्णांकel_boot_params *params,
					 u32 *boot_param)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर fwname[64];
	पूर्णांक err;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	kसमय_प्रकार callसमय;

	अगर (!ver || !params)
		वापस -EINVAL;

	/* The firmware variant determines अगर the device is in bootloader
	 * mode or is running operational firmware. The value 0x06 identअगरies
	 * the bootloader and the value 0x23 identअगरies the operational
	 * firmware.
	 *
	 * When the operational firmware is alपढ़ोy present, then only
	 * the check क्रम valid Bluetooth device address is needed. This
	 * determines अगर the device will be added as configured or
	 * unconfigured controller.
	 *
	 * It is not possible to use the Secure Boot Parameters in this
	 * हाल since that command is only available in bootloader mode.
	 */
	अगर (ver->fw_variant == 0x23) अणु
		clear_bit(BTUSB_BOOTLOADER, &data->flags);
		btपूर्णांकel_check_bdaddr(hdev);

		/* SfP and WsP करोn't seem to update the firmware version on file
		 * so version checking is currently possible.
		 */
		चयन (ver->hw_variant) अणु
		हाल 0x0b:	/* SfP */
		हाल 0x0c:	/* WsP */
			वापस 0;
		पूर्ण

		/* Proceed to करोwnload to check अगर the version matches */
		जाओ करोwnload;
	पूर्ण

	/* Read the secure boot parameters to identअगरy the operating
	 * details of the bootloader.
	 */
	err = btपूर्णांकel_पढ़ो_boot_params(hdev, params);
	अगर (err)
		वापस err;

	/* It is required that every single firmware fragment is acknowledged
	 * with a command complete event. If the boot parameters indicate
	 * that this bootloader करोes not send them, then पात the setup.
	 */
	अगर (params->limited_cce != 0x00) अणु
		bt_dev_err(hdev, "Unsupported Intel firmware loading method (%u)",
			   params->limited_cce);
		वापस -EINVAL;
	पूर्ण

	/* If the OTP has no valid Bluetooth device address, then there will
	 * also be no valid address क्रम the operational firmware.
	 */
	अगर (!bacmp(&params->otp_bdaddr, BDADDR_ANY)) अणु
		bt_dev_info(hdev, "No device address configured");
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
	पूर्ण

करोwnload:
	/* With this Intel bootloader only the hardware variant and device
	 * revision inक्रमmation are used to select the right firmware क्रम SfP
	 * and WsP.
	 *
	 * The firmware filename is ibt-<hw_variant>-<dev_revid>.sfi.
	 *
	 * Currently the supported hardware variants are:
	 *   11 (0x0b) क्रम iBT3.0 (LnP/SfP)
	 *   12 (0x0c) क्रम iBT3.5 (WsP)
	 *
	 * For ThP/JfP and क्रम future SKU's, the FW name varies based on HW
	 * variant, HW revision and FW revision, as these are dependent on CNVi
	 * and RF Combination.
	 *
	 *   17 (0x11) क्रम iBT3.5 (JfP)
	 *   18 (0x12) क्रम iBT3.5 (ThP)
	 *
	 * The firmware file name क्रम these will be
	 * ibt-<hw_variant>-<hw_revision>-<fw_revision>.sfi.
	 *
	 */
	err = btusb_setup_पूर्णांकel_new_get_fw_name(ver, params, fwname,
						माप(fwname), "sfi");
	अगर (err < 0) अणु
		अगर (!test_bit(BTUSB_BOOTLOADER, &data->flags)) अणु
			/* Firmware has alपढ़ोy been loaded */
			set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);
			वापस 0;
		पूर्ण

		bt_dev_err(hdev, "Unsupported Intel firmware naming");
		वापस -EINVAL;
	पूर्ण

	err = firmware_request_nowarn(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		अगर (!test_bit(BTUSB_BOOTLOADER, &data->flags)) अणु
			/* Firmware has alपढ़ोy been loaded */
			set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);
			वापस 0;
		पूर्ण

		bt_dev_err(hdev, "Failed to load Intel firmware file %s (%d)",
			   fwname, err);
		वापस err;
	पूर्ण

	bt_dev_info(hdev, "Found device firmware: %s", fwname);

	अगर (fw->size < 644) अणु
		bt_dev_err(hdev, "Invalid size of firmware file (%zu)",
			   fw->size);
		err = -EBADF;
		जाओ करोne;
	पूर्ण

	callसमय = kसमय_get();

	set_bit(BTUSB_DOWNLOADING, &data->flags);

	/* Start firmware करोwnloading and get boot parameter */
	err = btपूर्णांकel_करोwnload_firmware(hdev, ver, fw, boot_param);
	अगर (err < 0) अणु
		अगर (err == -EALREADY) अणु
			/* Firmware has alपढ़ोy been loaded */
			set_bit(BTUSB_FIRMWARE_LOADED, &data->flags);
			err = 0;
			जाओ करोne;
		पूर्ण

		/* When FW करोwnload fails, send Intel Reset to retry
		 * FW करोwnload.
		 */
		btपूर्णांकel_reset_to_bootloader(hdev);
		जाओ करोne;
	पूर्ण

	/* Beक्रमe चयनing the device पूर्णांकo operational mode and with that
	 * booting the loaded firmware, रुको क्रम the bootloader notअगरication
	 * that all fragments have been successfully received.
	 *
	 * When the event processing receives the notअगरication, then the
	 * BTUSB_DOWNLOADING flag will be cleared.
	 *
	 * The firmware loading should not take दीर्घer than 5 seconds
	 * and thus just समयout अगर that happens and fail the setup
	 * of this device.
	 */
	err = btusb_करोwnload_रुको(hdev, callसमय, 5000);
	अगर (err == -ETIMEDOUT)
		btपूर्णांकel_reset_to_bootloader(hdev);

करोne:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक btusb_boot_रुको(काष्ठा hci_dev *hdev, kसमय_प्रकार callसमय, पूर्णांक msec)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	kसमय_प्रकार delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	bt_dev_info(hdev, "Waiting for device to boot");

	err = रुको_on_bit_समयout(&data->flags, BTUSB_BOOTING,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jअगरfies(msec));
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Device boot interrupted");
		वापस -EINTR;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Device boot timeout");
		वापस -ETIMEDOUT;
	पूर्ण

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Device booted in %llu usecs", duration);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_पूर्णांकel_boot(काष्ठा hci_dev *hdev, u32 boot_addr)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	kसमय_प्रकार callसमय;
	पूर्णांक err;

	callसमय = kसमय_get();

	set_bit(BTUSB_BOOTING, &data->flags);

	err = btपूर्णांकel_send_पूर्णांकel_reset(hdev, boot_addr);
	अगर (err) अणु
		bt_dev_err(hdev, "Intel Soft Reset failed (%d)", err);
		btपूर्णांकel_reset_to_bootloader(hdev);
		वापस err;
	पूर्ण

	/* The bootloader will not indicate when the device is पढ़ोy. This
	 * is करोne by the operational firmware sending bootup notअगरication.
	 *
	 * Booting पूर्णांकo operational firmware should not take दीर्घer than
	 * 1 second. However अगर that happens, then just fail the setup
	 * since something went wrong.
	 */
	err = btusb_boot_रुको(hdev, callसमय, 1000);
	अगर (err == -ETIMEDOUT)
		btपूर्णांकel_reset_to_bootloader(hdev);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_setup_पूर्णांकel_new(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा पूर्णांकel_version ver;
	काष्ठा पूर्णांकel_boot_params params;
	u32 boot_param;
	अक्षर ddcname[64];
	पूर्णांक err;
	काष्ठा पूर्णांकel_debug_features features;

	BT_DBG("%s", hdev->name);

	/* Set the शेष boot parameter to 0x0 and it is updated to
	 * SKU specअगरic boot parameter after पढ़ोing Intel_Write_Boot_Params
	 * command जबतक करोwnloading the firmware.
	 */
	boot_param = 0x00000000;

	/* Read the Intel version inक्रमmation to determine अगर the device
	 * is in bootloader mode or अगर it alपढ़ोy has operational firmware
	 * loaded.
	 */
	err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
	अगर (err) अणु
		bt_dev_err(hdev, "Intel Read version failed (%d)", err);
		btपूर्णांकel_reset_to_bootloader(hdev);
		वापस err;
	पूर्ण

	err = btपूर्णांकel_version_info(hdev, &ver);
	अगर (err)
		वापस err;

	err = btusb_पूर्णांकel_करोwnload_firmware(hdev, &ver, &params, &boot_param);
	अगर (err)
		वापस err;

	/* controller is alपढ़ोy having an operational firmware */
	अगर (ver.fw_variant == 0x23)
		जाओ finish;

	err = btusb_पूर्णांकel_boot(hdev, boot_param);
	अगर (err)
		वापस err;

	clear_bit(BTUSB_BOOTLOADER, &data->flags);

	err = btusb_setup_पूर्णांकel_new_get_fw_name(&ver, &params, ddcname,
						माप(ddcname), "ddc");

	अगर (err < 0) अणु
		bt_dev_err(hdev, "Unsupported Intel firmware naming");
	पूर्ण अन्यथा अणु
		/* Once the device is running in operational mode, it needs to
		 * apply the device configuration (DDC) parameters.
		 *
		 * The device can work without DDC parameters, so even अगर it
		 * fails to load the file, no need to fail the setup.
		 */
		btपूर्णांकel_load_ddc_config(hdev, ddcname);
	पूर्ण

	/* Read the Intel supported features and अगर new exception क्रमmats
	 * supported, need to load the additional DDC config to enable.
	 */
	btपूर्णांकel_पढ़ो_debug_features(hdev, &features);

	/* Set DDC mask क्रम available debug features */
	btपूर्णांकel_set_debug_features(hdev, &features);

	/* Read the Intel version inक्रमmation after loading the FW  */
	err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
	अगर (err)
		वापस err;

	btपूर्णांकel_version_info(hdev, &ver);

finish:
	/* All Intel controllers that support the Microsoft venकरोr
	 * extension are using 0xFC1E क्रम VsMsftOpCode.
	 */
	चयन (ver.hw_variant) अणु
	हाल 0x11:	/* JfP */
	हाल 0x12:	/* ThP */
	हाल 0x13:	/* HrP */
	हाल 0x14:	/* CcP */
		hci_set_msft_opcode(hdev, 0xFC1E);
		अवरोध;
	पूर्ण

	/* Set the event mask क्रम Intel specअगरic venकरोr events. This enables
	 * a few extra events that are useful during general operation. It
	 * करोes not enable any debugging related events.
	 *
	 * The device will function correctly without these events enabled
	 * and thus no need to fail the setup.
	 */
	btपूर्णांकel_set_event_mask(hdev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_setup_पूर्णांकel_newgen(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	u32 boot_param;
	अक्षर ddcname[64];
	पूर्णांक err;
	काष्ठा पूर्णांकel_debug_features features;
	काष्ठा पूर्णांकel_version_tlv version;

	bt_dev_dbg(hdev, "");

	/* Set the शेष boot parameter to 0x0 and it is updated to
	 * SKU specअगरic boot parameter after पढ़ोing Intel_Write_Boot_Params
	 * command जबतक करोwnloading the firmware.
	 */
	boot_param = 0x00000000;

	/* Read the Intel version inक्रमmation to determine अगर the device
	 * is in bootloader mode or अगर it alपढ़ोy has operational firmware
	 * loaded.
	 */
	err = btपूर्णांकel_पढ़ो_version_tlv(hdev, &version);
	अगर (err) अणु
		bt_dev_err(hdev, "Intel Read version failed (%d)", err);
		btपूर्णांकel_reset_to_bootloader(hdev);
		वापस err;
	पूर्ण

	err = btपूर्णांकel_version_info_tlv(hdev, &version);
	अगर (err)
		वापस err;

	err = btusb_पूर्णांकel_करोwnload_firmware_newgen(hdev, &version, &boot_param);
	अगर (err)
		वापस err;

	/* check अगर controller is alपढ़ोy having an operational firmware */
	अगर (version.img_type == 0x03)
		जाओ finish;

	err = btusb_पूर्णांकel_boot(hdev, boot_param);
	अगर (err)
		वापस err;

	clear_bit(BTUSB_BOOTLOADER, &data->flags);

	btusb_setup_पूर्णांकel_newgen_get_fw_name(&version, ddcname, माप(ddcname),
					     "ddc");
	/* Once the device is running in operational mode, it needs to
	 * apply the device configuration (DDC) parameters.
	 *
	 * The device can work without DDC parameters, so even अगर it
	 * fails to load the file, no need to fail the setup.
	 */
	btपूर्णांकel_load_ddc_config(hdev, ddcname);

	/* Read the Intel supported features and अगर new exception क्रमmats
	 * supported, need to load the additional DDC config to enable.
	 */
	btपूर्णांकel_पढ़ो_debug_features(hdev, &features);

	/* Set DDC mask क्रम available debug features */
	btपूर्णांकel_set_debug_features(hdev, &features);

	/* Read the Intel version inक्रमmation after loading the FW  */
	err = btपूर्णांकel_पढ़ो_version_tlv(hdev, &version);
	अगर (err)
		वापस err;

	btपूर्णांकel_version_info_tlv(hdev, &version);

finish:
	/* Set the event mask क्रम Intel specअगरic venकरोr events. This enables
	 * a few extra events that are useful during general operation. It
	 * करोes not enable any debugging related events.
	 *
	 * The device will function correctly without these events enabled
	 * and thus no need to fail the setup.
	 */
	btपूर्णांकel_set_event_mask(hdev, false);

	वापस 0;
पूर्ण
अटल पूर्णांक btusb_shutकरोwn_पूर्णांकel(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	दीर्घ ret;

	/* In the shutकरोwn sequence where Bluetooth is turned off followed
	 * by WiFi being turned off, turning WiFi back on causes issue with
	 * the RF calibration.
	 *
	 * To ensure that any RF activity has been stopped, issue HCI Reset
	 * command to clear all ongoing activity including advertising,
	 * scanning etc.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	/* Some platक्रमms have an issue with BT LED when the पूर्णांकerface is
	 * करोwn or BT radio is turned off, which takes 5 seconds to BT LED
	 * goes off. This command turns off the BT LED immediately.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc3f, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "turning off Intel device LED failed");
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_shutकरोwn_पूर्णांकel_new(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Send HCI Reset to the controller to stop any BT activity which
	 * were triggered. This will help to save घातer and मुख्यtain the
	 * sync b/w Host and controller
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

#घोषणा FIRMWARE_MT7663		"mediatek/mt7663pr2h.bin"
#घोषणा FIRMWARE_MT7668		"mediatek/mt7668pr2h.bin"

#घोषणा HCI_WMT_MAX_EVENT_SIZE		64
/* It is क्रम mt79xx करोwnload rom patch*/
#घोषणा MTK_FW_ROM_PATCH_HEADER_SIZE	32
#घोषणा MTK_FW_ROM_PATCH_GD_SIZE	64
#घोषणा MTK_FW_ROM_PATCH_SEC_MAP_SIZE	64
#घोषणा MTK_SEC_MAP_COMMON_SIZE	12
#घोषणा MTK_SEC_MAP_NEED_SEND_SIZE	52

क्रमागत अणु
	BTMTK_WMT_PATCH_DWNLD = 0x1,
	BTMTK_WMT_FUNC_CTRL = 0x6,
	BTMTK_WMT_RST = 0x7,
	BTMTK_WMT_SEMAPHORE = 0x17,
पूर्ण;

क्रमागत अणु
	BTMTK_WMT_INVALID,
	BTMTK_WMT_PATCH_UNDONE,
	BTMTK_WMT_PATCH_PROGRESS,
	BTMTK_WMT_PATCH_DONE,
	BTMTK_WMT_ON_UNDONE,
	BTMTK_WMT_ON_DONE,
	BTMTK_WMT_ON_PROGRESS,
पूर्ण;

काष्ठा bपंचांगtk_wmt_hdr अणु
	u8	dir;
	u8	op;
	__le16	dlen;
	u8	flag;
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_cmd अणु
	काष्ठा bपंचांगtk_wmt_hdr hdr;
	u8 data[];
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_evt अणु
	काष्ठा hci_event_hdr hhdr;
	काष्ठा bपंचांगtk_wmt_hdr whdr;
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_evt_funcc अणु
	काष्ठा bपंचांगtk_hci_wmt_evt hwhdr;
	__be16 status;
पूर्ण __packed;

काष्ठा bपंचांगtk_tci_sleep अणु
	u8 mode;
	__le16 duration;
	__le16 host_duration;
	u8 host_wakeup_pin;
	u8 समय_compensation;
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_params अणु
	u8 op;
	u8 flag;
	u16 dlen;
	स्थिर व्योम *data;
	u32 *status;
पूर्ण;

काष्ठा bपंचांगtk_patch_header अणु
	u8 dateसमय[16];
	u8 platक्रमm[4];
	__le16 hwver;
	__le16 swver;
	__le32 magicnum;
पूर्ण __packed;

काष्ठा bपंचांगtk_global_desc अणु
	__le32 patch_ver;
	__le32 sub_sys;
	__le32 feature_opt;
	__le32 section_num;
पूर्ण __packed;

काष्ठा bपंचांगtk_section_map अणु
	__le32 sectype;
	__le32 secoffset;
	__le32 secsize;
	जोड़ अणु
		__le32 u4SecSpec[13];
		काष्ठा अणु
			__le32 dlAddr;
			__le32 dlsize;
			__le32 seckeyidx;
			__le32 alignlen;
			__le32 sectype;
			__le32 dlmodecrctype;
			__le32 crc;
			__le32 reserved[6];
		पूर्ण bin_info_spec;
	पूर्ण;
पूर्ण __packed;

अटल व्योम btusb_mtk_wmt_recv(काष्ठा urb *urb)
अणु
	काष्ठा hci_dev *hdev = urb->context;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा hci_event_hdr *hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (urb->status == 0 && urb->actual_length > 0) अणु
		hdev->stat.byte_rx += urb->actual_length;

		/* WMT event shouldn't be fragmented and the size should be
		 * less than HCI_WMT_MAX_EVENT_SIZE.
		 */
		skb = bt_skb_alloc(HCI_WMT_MAX_EVENT_SIZE, GFP_ATOMIC);
		अगर (!skb) अणु
			hdev->stat.err_rx++;
			वापस;
		पूर्ण

		hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
		skb_put_data(skb, urb->transfer_buffer, urb->actual_length);

		hdr = (व्योम *)skb->data;
		/* Fix up the venकरोr event id with 0xff क्रम venकरोr specअगरic
		 * instead of 0xe4 so that event send via monitoring socket can
		 * be parsed properly.
		 */
		hdr->evt = 0xff;

		/* When someone रुकोs क्रम the WMT event, the skb is being cloned
		 * and being processed the events from there then.
		 */
		अगर (test_bit(BTUSB_TX_WAIT_VND_EVT, &data->flags)) अणु
			data->evt_skb = skb_clone(skb, GFP_ATOMIC);
			अगर (!data->evt_skb) अणु
				kमुक्त_skb(skb);
				वापस;
			पूर्ण
		पूर्ण

		err = hci_recv_frame(hdev, skb);
		अगर (err < 0) अणु
			kमुक्त_skb(data->evt_skb);
			data->evt_skb = शून्य;
			वापस;
		पूर्ण

		अगर (test_and_clear_bit(BTUSB_TX_WAIT_VND_EVT,
				       &data->flags)) अणु
			/* Barrier to sync with other CPUs */
			smp_mb__after_atomic();
			wake_up_bit(&data->flags,
				    BTUSB_TX_WAIT_VND_EVT);
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (urb->status == -ENOENT) अणु
		/* Aव्योम suspend failed when usb_समाप्त_urb */
		वापस;
	पूर्ण

	usb_mark_last_busy(data->udev);

	/* The URB complete handler is still called with urb->actual_length = 0
	 * when the event is not available, so we should keep re-submitting
	 * URB until WMT event वापसs, Also, It's necessary to रुको some समय
	 * between the two consecutive control URBs to relax the target device
	 * to generate the event. Otherwise, the WMT event cannot वापस from
	 * the device successfully.
	 */
	udelay(500);

	usb_anchor_urb(urb, &data->ctrl_anchor);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p failed to resubmit (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक btusb_mtk_submit_wmt_recv_urb(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा usb_ctrlrequest *dr;
	अचिन्हित अक्षर *buf;
	पूर्णांक err, size = 64;
	अचिन्हित पूर्णांक pipe;
	काष्ठा urb *urb;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	dr = kदो_स्मृति(माप(*dr), GFP_KERNEL);
	अगर (!dr) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	dr->bRequestType = USB_TYPE_VENDOR | USB_सूची_IN;
	dr->bRequest     = 1;
	dr->wIndex       = cpu_to_le16(0);
	dr->wValue       = cpu_to_le16(48);
	dr->wLength      = cpu_to_le16(size);

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		kमुक्त(dr);
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvctrlpipe(data->udev, 0);

	usb_fill_control_urb(urb, data->udev, pipe, (व्योम *)dr,
			     buf, size, btusb_mtk_wmt_recv, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->ctrl_anchor);
	err = usb_submit_urb(urb, GFP_KERNEL);
	अगर (err < 0) अणु
		अगर (err != -EPERM && err != -ENODEV)
			bt_dev_err(hdev, "urb %p submission failed (%d)",
				   urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_mtk_hci_wmt_sync(काष्ठा hci_dev *hdev,
				  काष्ठा bपंचांगtk_hci_wmt_params *wmt_params)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	u32 hlen, status = BTMTK_WMT_INVALID;
	काष्ठा bपंचांगtk_hci_wmt_evt *wmt_evt;
	काष्ठा bपंचांगtk_hci_wmt_cmd *wc;
	काष्ठा bपंचांगtk_wmt_hdr *hdr;
	पूर्णांक err;

	/* Submit control IN URB on demand to process the WMT event */
	err = btusb_mtk_submit_wmt_recv_urb(hdev);
	अगर (err < 0)
		वापस err;

	/* Send the WMT command and रुको until the WMT event वापसs */
	hlen = माप(*hdr) + wmt_params->dlen;
	अगर (hlen > 255)
		वापस -EINVAL;

	wc = kzalloc(hlen, GFP_KERNEL);
	अगर (!wc)
		वापस -ENOMEM;

	hdr = &wc->hdr;
	hdr->dir = 1;
	hdr->op = wmt_params->op;
	hdr->dlen = cpu_to_le16(wmt_params->dlen + 1);
	hdr->flag = wmt_params->flag;
	स_नकल(wc->data, wmt_params->data, wmt_params->dlen);

	set_bit(BTUSB_TX_WAIT_VND_EVT, &data->flags);

	err = __hci_cmd_send(hdev, 0xfc6f, hlen, wc);

	अगर (err < 0) अणु
		clear_bit(BTUSB_TX_WAIT_VND_EVT, &data->flags);
		जाओ err_मुक्त_wc;
	पूर्ण

	/* The venकरोr specअगरic WMT commands are all answered by a venकरोr
	 * specअगरic event and will have the Command Status or Command
	 * Complete as with usual HCI command flow control.
	 *
	 * After sending the command, रुको क्रम BTUSB_TX_WAIT_VND_EVT
	 * state to be cleared. The driver specअगरic event receive routine
	 * will clear that state and with that indicate completion of the
	 * WMT command.
	 */
	err = रुको_on_bit_समयout(&data->flags, BTUSB_TX_WAIT_VND_EVT,
				  TASK_INTERRUPTIBLE, HCI_INIT_TIMEOUT);
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Execution of wmt command interrupted");
		clear_bit(BTUSB_TX_WAIT_VND_EVT, &data->flags);
		जाओ err_मुक्त_wc;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Execution of wmt command timed out");
		clear_bit(BTUSB_TX_WAIT_VND_EVT, &data->flags);
		err = -ETIMEDOUT;
		जाओ err_मुक्त_wc;
	पूर्ण

	/* Parse and handle the वापस WMT event */
	wmt_evt = (काष्ठा bपंचांगtk_hci_wmt_evt *)data->evt_skb->data;
	अगर (wmt_evt->whdr.op != hdr->op) अणु
		bt_dev_err(hdev, "Wrong op received %d expected %d",
			   wmt_evt->whdr.op, hdr->op);
		err = -EIO;
		जाओ err_मुक्त_skb;
	पूर्ण

	चयन (wmt_evt->whdr.op) अणु
	हाल BTMTK_WMT_SEMAPHORE:
		अगर (wmt_evt->whdr.flag == 2)
			status = BTMTK_WMT_PATCH_UNDONE;
		अन्यथा
			status = BTMTK_WMT_PATCH_DONE;
		अवरोध;
	हाल BTMTK_WMT_FUNC_CTRL:
		wmt_evt_funcc = (काष्ठा bपंचांगtk_hci_wmt_evt_funcc *)wmt_evt;
		अगर (be16_to_cpu(wmt_evt_funcc->status) == 0x404)
			status = BTMTK_WMT_ON_DONE;
		अन्यथा अगर (be16_to_cpu(wmt_evt_funcc->status) == 0x420)
			status = BTMTK_WMT_ON_PROGRESS;
		अन्यथा
			status = BTMTK_WMT_ON_UNDONE;
		अवरोध;
	हाल BTMTK_WMT_PATCH_DWNLD:
		अगर (wmt_evt->whdr.flag == 2)
			status = BTMTK_WMT_PATCH_DONE;
		अन्यथा अगर (wmt_evt->whdr.flag == 1)
			status = BTMTK_WMT_PATCH_PROGRESS;
		अन्यथा
			status = BTMTK_WMT_PATCH_UNDONE;
		अवरोध;
	पूर्ण

	अगर (wmt_params->status)
		*wmt_params->status = status;

err_मुक्त_skb:
	kमुक्त_skb(data->evt_skb);
	data->evt_skb = शून्य;
err_मुक्त_wc:
	kमुक्त(wc);
	वापस err;
पूर्ण

अटल पूर्णांक btusb_mtk_setup_firmware_79xx(काष्ठा hci_dev *hdev, स्थिर अक्षर *fwname)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	काष्ठा bपंचांगtk_global_desc *globaldesc = शून्य;
	काष्ठा bपंचांगtk_section_map *sectionmap;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	स्थिर u8 *fw_bin_ptr;
	पूर्णांक err, dlen, i, status;
	u8 flag, first_block, retry;
	u32 section_num, dl_size, section_offset;
	u8 cmd[64];

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load firmware file (%d)", err);
		वापस err;
	पूर्ण

	fw_ptr = fw->data;
	fw_bin_ptr = fw_ptr;
	globaldesc = (काष्ठा bपंचांगtk_global_desc *)(fw_ptr + MTK_FW_ROM_PATCH_HEADER_SIZE);
	section_num = le32_to_cpu(globaldesc->section_num);

	क्रम (i = 0; i < section_num; i++) अणु
		first_block = 1;
		fw_ptr = fw_bin_ptr;
		sectionmap = (काष्ठा bपंचांगtk_section_map *)(fw_ptr + MTK_FW_ROM_PATCH_HEADER_SIZE +
			      MTK_FW_ROM_PATCH_GD_SIZE + MTK_FW_ROM_PATCH_SEC_MAP_SIZE * i);

		section_offset = le32_to_cpu(sectionmap->secoffset);
		dl_size = le32_to_cpu(sectionmap->bin_info_spec.dlsize);

		अगर (dl_size > 0) अणु
			retry = 20;
			जबतक (retry > 0) अणु
				cmd[0] = 0; /* 0 means legacy dl mode. */
				स_नकल(cmd + 1,
				       fw_ptr + MTK_FW_ROM_PATCH_HEADER_SIZE +
				       MTK_FW_ROM_PATCH_GD_SIZE + MTK_FW_ROM_PATCH_SEC_MAP_SIZE * i +
				       MTK_SEC_MAP_COMMON_SIZE,
				       MTK_SEC_MAP_NEED_SEND_SIZE + 1);

				wmt_params.op = BTMTK_WMT_PATCH_DWNLD;
				wmt_params.status = &status;
				wmt_params.flag = 0;
				wmt_params.dlen = MTK_SEC_MAP_NEED_SEND_SIZE + 1;
				wmt_params.data = &cmd;

				err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
				अगर (err < 0) अणु
					bt_dev_err(hdev, "Failed to send wmt patch dwnld (%d)",
						   err);
					जाओ err_release_fw;
				पूर्ण

				अगर (status == BTMTK_WMT_PATCH_UNDONE) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (status == BTMTK_WMT_PATCH_PROGRESS) अणु
					msleep(100);
					retry--;
				पूर्ण अन्यथा अगर (status == BTMTK_WMT_PATCH_DONE) अणु
					जाओ next_section;
				पूर्ण अन्यथा अणु
					bt_dev_err(hdev, "Failed wmt patch dwnld status (%d)",
						   status);
					जाओ err_release_fw;
				पूर्ण
			पूर्ण

			fw_ptr += section_offset;
			wmt_params.op = BTMTK_WMT_PATCH_DWNLD;
			wmt_params.status = शून्य;

			जबतक (dl_size > 0) अणु
				dlen = min_t(पूर्णांक, 250, dl_size);
				अगर (first_block == 1) अणु
					flag = 1;
					first_block = 0;
				पूर्ण अन्यथा अगर (dl_size - dlen <= 0) अणु
					flag = 3;
				पूर्ण अन्यथा अणु
					flag = 2;
				पूर्ण

				wmt_params.flag = flag;
				wmt_params.dlen = dlen;
				wmt_params.data = fw_ptr;

				err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
				अगर (err < 0) अणु
					bt_dev_err(hdev, "Failed to send wmt patch dwnld (%d)",
						   err);
					जाओ err_release_fw;
				पूर्ण

				dl_size -= dlen;
				fw_ptr += dlen;
			पूर्ण
		पूर्ण
next_section:
		जारी;
	पूर्ण
	/* Wait a few moments क्रम firmware activation करोne */
	usleep_range(100000, 120000);

err_release_fw:
	release_firmware(fw);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_mtk_setup_firmware(काष्ठा hci_dev *hdev, स्थिर अक्षर *fwname)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	माप_प्रकार fw_size;
	पूर्णांक err, dlen;
	u8 flag, param;

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load firmware file (%d)", err);
		वापस err;
	पूर्ण

	/* Power on data RAM the firmware relies on. */
	param = 1;
	wmt_params.op = BTMTK_WMT_FUNC_CTRL;
	wmt_params.flag = 3;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to power on data RAM (%d)", err);
		जाओ err_release_fw;
	पूर्ण

	fw_ptr = fw->data;
	fw_size = fw->size;

	/* The size of patch header is 30 bytes, should be skip */
	अगर (fw_size < 30) अणु
		err = -EINVAL;
		जाओ err_release_fw;
	पूर्ण

	fw_size -= 30;
	fw_ptr += 30;
	flag = 1;

	wmt_params.op = BTMTK_WMT_PATCH_DWNLD;
	wmt_params.status = शून्य;

	जबतक (fw_size > 0) अणु
		dlen = min_t(पूर्णांक, 250, fw_size);

		/* Tell device the position in sequence */
		अगर (fw_size - dlen <= 0)
			flag = 3;
		अन्यथा अगर (fw_size < fw->size - 30)
			flag = 2;

		wmt_params.flag = flag;
		wmt_params.dlen = dlen;
		wmt_params.data = fw_ptr;

		err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to send wmt patch dwnld (%d)",
				   err);
			जाओ err_release_fw;
		पूर्ण

		fw_size -= dlen;
		fw_ptr += dlen;
	पूर्ण

	wmt_params.op = BTMTK_WMT_RST;
	wmt_params.flag = 4;
	wmt_params.dlen = 0;
	wmt_params.data = शून्य;
	wmt_params.status = शून्य;

	/* Activate funciton the firmware providing to */
	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt rst (%d)", err);
		जाओ err_release_fw;
	पूर्ण

	/* Wait a few moments क्रम firmware activation करोne */
	usleep_range(10000, 12000);

err_release_fw:
	release_firmware(fw);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_mtk_func_query(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	पूर्णांक status, err;
	u8 param = 0;

	/* Query whether the function is enabled */
	wmt_params.op = BTMTK_WMT_FUNC_CTRL;
	wmt_params.flag = 4;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = &status;

	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to query function status (%d)", err);
		वापस err;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक btusb_mtk_reg_पढ़ो(काष्ठा btusb_data *data, u32 reg, u32 *val)
अणु
	पूर्णांक pipe, err, size = माप(u32);
	व्योम *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pipe = usb_rcvctrlpipe(data->udev, 0);
	err = usb_control_msg(data->udev, pipe, 0x63,
			      USB_TYPE_VENDOR | USB_सूची_IN,
			      reg >> 16, reg & 0xffff,
			      buf, size, USB_CTRL_SET_TIMEOUT);
	अगर (err < 0)
		जाओ err_मुक्त_buf;

	*val = get_unaligned_le32(buf);

err_मुक्त_buf:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_mtk_id_get(काष्ठा btusb_data *data, u32 reg, u32 *id)
अणु
	वापस btusb_mtk_reg_पढ़ो(data, reg, id);
पूर्ण

अटल पूर्णांक btusb_mtk_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	kसमय_प्रकार callसमय, delta, retसमय;
	काष्ठा bपंचांगtk_tci_sleep tci_sleep;
	अचिन्हित दीर्घ दीर्घ duration;
	काष्ठा sk_buff *skb;
	स्थिर अक्षर *fwname;
	पूर्णांक err, status;
	u32 dev_id;
	अक्षर fw_bin_name[64];
	u32 fw_version = 0;
	u8 param;

	callसमय = kसमय_get();

	err = btusb_mtk_id_get(data, 0x80000008, &dev_id);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to get device id (%d)", err);
		वापस err;
	पूर्ण

	अगर (!dev_id) अणु
		err = btusb_mtk_id_get(data, 0x70010200, &dev_id);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to get device id (%d)", err);
			वापस err;
		पूर्ण
		err = btusb_mtk_id_get(data, 0x80021004, &fw_version);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to get fw version (%d)", err);
			वापस err;
		पूर्ण
	पूर्ण

	चयन (dev_id) अणु
	हाल 0x7663:
		fwname = FIRMWARE_MT7663;
		अवरोध;
	हाल 0x7668:
		fwname = FIRMWARE_MT7668;
		अवरोध;
	हाल 0x7961:
		snम_लिखो(fw_bin_name, माप(fw_bin_name),
			"mediatek/BT_RAM_CODE_MT%04x_1_%x_hdr.bin",
			 dev_id & 0xffff, (fw_version & 0xff) + 1);
		err = btusb_mtk_setup_firmware_79xx(hdev, fw_bin_name);

		/* Enable Bluetooth protocol */
		param = 1;
		wmt_params.op = BTMTK_WMT_FUNC_CTRL;
		wmt_params.flag = 0;
		wmt_params.dlen = माप(param);
		wmt_params.data = &param;
		wmt_params.status = शून्य;

		err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
			वापस err;
		पूर्ण
		जाओ करोne;
	शेष:
		bt_dev_err(hdev, "Unsupported hardware variant (%08x)",
			   dev_id);
		वापस -ENODEV;
	पूर्ण

	/* Query whether the firmware is alपढ़ोy करोwnload */
	wmt_params.op = BTMTK_WMT_SEMAPHORE;
	wmt_params.flag = 1;
	wmt_params.dlen = 0;
	wmt_params.data = शून्य;
	wmt_params.status = &status;

	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to query firmware status (%d)", err);
		वापस err;
	पूर्ण

	अगर (status == BTMTK_WMT_PATCH_DONE) अणु
		bt_dev_info(hdev, "firmware already downloaded");
		जाओ ignore_setup_fw;
	पूर्ण

	/* Setup a firmware which the device definitely requires */
	err = btusb_mtk_setup_firmware(hdev, fwname);
	अगर (err < 0)
		वापस err;

ignore_setup_fw:
	err = पढ़ोx_poll_समयout(btusb_mtk_func_query, hdev, status,
				 status < 0 || status != BTMTK_WMT_ON_PROGRESS,
				 2000, 5000000);
	/* -ETIMEDOUT happens */
	अगर (err < 0)
		वापस err;

	/* The other errors happen in btusb_mtk_func_query */
	अगर (status < 0)
		वापस status;

	अगर (status == BTMTK_WMT_ON_DONE) अणु
		bt_dev_info(hdev, "function already on");
		जाओ ignore_func_on;
	पूर्ण

	/* Enable Bluetooth protocol */
	param = 1;
	wmt_params.op = BTMTK_WMT_FUNC_CTRL;
	wmt_params.flag = 0;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		वापस err;
	पूर्ण

ignore_func_on:
	/* Apply the low घातer environment setup */
	tci_sleep.mode = 0x5;
	tci_sleep.duration = cpu_to_le16(0x640);
	tci_sleep.host_duration = cpu_to_le16(0x640);
	tci_sleep.host_wakeup_pin = 0;
	tci_sleep.समय_compensation = 0;

	skb = __hci_cmd_sync(hdev, 0xfc7a, माप(tci_sleep), &tci_sleep,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Failed to apply low power setting (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

करोne:
	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Device setup in %llu usecs", duration);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_mtk_shutकरोwn(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	u8 param = 0;
	पूर्णांक err;

	/* Disable the device */
	wmt_params.op = BTMTK_WMT_FUNC_CTRL;
	wmt_params.flag = 0;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = btusb_mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

MODULE_FIRMWARE(FIRMWARE_MT7663);
MODULE_FIRMWARE(FIRMWARE_MT7668);

#अगर_घोषित CONFIG_PM
/* Configure an out-of-band gpio as wake-up pin, अगर specअगरied in device tree */
अटल पूर्णांक marvell_config_oob_wake(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा device *dev = &data->udev->dev;
	u16 pin, gap, opcode;
	पूर्णांक ret;
	u8 cmd[5];

	/* Move on अगर no wakeup pin specअगरied */
	अगर (of_property_पढ़ो_u16(dev->of_node, "marvell,wakeup-pin", &pin) ||
	    of_property_पढ़ो_u16(dev->of_node, "marvell,wakeup-gap-ms", &gap))
		वापस 0;

	/* Venकरोr specअगरic command to configure a GPIO as wake-up pin */
	opcode = hci_opcode_pack(0x3F, 0x59);
	cmd[0] = opcode & 0xFF;
	cmd[1] = opcode >> 8;
	cmd[2] = 2; /* length of parameters that follow */
	cmd[3] = pin;
	cmd[4] = gap; /* समय in ms, क्रम which wakeup pin should be निश्चितed */

	skb = bt_skb_alloc(माप(cmd), GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hdev, "%s: No memory", __func__);
		वापस -ENOMEM;
	पूर्ण

	skb_put_data(skb, cmd, माप(cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	ret = btusb_send_frame(hdev, skb);
	अगर (ret) अणु
		bt_dev_err(hdev, "%s: configuration failed", __func__);
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक btusb_set_bdaddr_marvell(काष्ठा hci_dev *hdev,
				    स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	u8 buf[8];
	दीर्घ ret;

	buf[0] = 0xfe;
	buf[1] = माप(bdaddr_t);
	स_नकल(buf + 2, bdaddr, माप(bdaddr_t));

	skb = __hci_cmd_sync(hdev, 0xfc22, माप(buf), buf, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "changing Marvell device address failed (%ld)",
			   ret);
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_set_bdaddr_ath3012(काष्ठा hci_dev *hdev,
				    स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	u8 buf[10];
	दीर्घ ret;

	buf[0] = 0x01;
	buf[1] = 0x01;
	buf[2] = 0x00;
	buf[3] = माप(bdaddr_t);
	स_नकल(buf + 4, bdaddr, माप(bdaddr_t));

	skb = __hci_cmd_sync(hdev, 0xfc0b, माप(buf), buf, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "Change address command failed (%ld)", ret);
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_set_bdaddr_wcn6855(काष्ठा hci_dev *hdev,
				स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	u8 buf[6];
	दीर्घ ret;

	स_नकल(buf, bdaddr, माप(bdaddr_t));

	skb = __hci_cmd_sync_ev(hdev, 0xfc14, माप(buf), buf,
				HCI_EV_CMD_COMPLETE, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "Change address command failed (%ld)", ret);
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

#घोषणा QCA_DFU_PACKET_LEN	4096

#घोषणा QCA_GET_TARGET_VERSION	0x09
#घोषणा QCA_CHECK_STATUS	0x05
#घोषणा QCA_DFU_DOWNLOAD	0x01

#घोषणा QCA_SYSCFG_UPDATED	0x40
#घोषणा QCA_PATCH_UPDATED	0x80
#घोषणा QCA_DFU_TIMEOUT		3000
#घोषणा QCA_FLAG_MULTI_NVM      0x80

काष्ठा qca_version अणु
	__le32	rom_version;
	__le32	patch_version;
	__le32	ram_version;
	__le16	board_id;
	__le16	flag;
	__u8	reserved[4];
पूर्ण __packed;

काष्ठा qca_rampatch_version अणु
	__le16	rom_version_high;
	__le16  rom_version_low;
	__le16	patch_version;
पूर्ण __packed;

काष्ठा qca_device_info अणु
	u32	rom_version;
	u8	rampatch_hdr;	/* length of header in rampatch */
	u8	nvm_hdr;	/* length of header in NVM */
	u8	ver_offset;	/* offset of version काष्ठाure in rampatch */
पूर्ण;

अटल स्थिर काष्ठा qca_device_info qca_devices_table[] = अणु
	अणु 0x00000100, 20, 4,  8 पूर्ण, /* Rome 1.0 */
	अणु 0x00000101, 20, 4,  8 पूर्ण, /* Rome 1.1 */
	अणु 0x00000200, 28, 4, 16 पूर्ण, /* Rome 2.0 */
	अणु 0x00000201, 28, 4, 16 पूर्ण, /* Rome 2.1 */
	अणु 0x00000300, 28, 4, 16 पूर्ण, /* Rome 3.0 */
	अणु 0x00000302, 28, 4, 16 पूर्ण, /* Rome 3.2 */
	अणु 0x00130100, 40, 4, 16 पूर्ण, /* WCN6855 1.0 */
	अणु 0x00130200, 40, 4, 16 पूर्ण, /* WCN6855 2.0 */
पूर्ण;

अटल पूर्णांक btusb_qca_send_venकरोr_req(काष्ठा usb_device *udev, u8 request,
				     व्योम *data, u16 size)
अणु
	पूर्णांक pipe, err;
	u8 *buf;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Found some of USB hosts have IOT issues with ours so that we should
	 * not रुको until HCI layer is पढ़ोy.
	 */
	pipe = usb_rcvctrlpipe(udev, 0);
	err = usb_control_msg(udev, pipe, request, USB_TYPE_VENDOR | USB_सूची_IN,
			      0, 0, buf, size, USB_CTRL_SET_TIMEOUT);
	अगर (err < 0) अणु
		dev_err(&udev->dev, "Failed to access otp area (%d)", err);
		जाओ करोne;
	पूर्ण

	स_नकल(data, buf, size);

करोne:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_setup_qca_करोwnload_fw(काष्ठा hci_dev *hdev,
				       स्थिर काष्ठा firmware *firmware,
				       माप_प्रकार hdr_size)
अणु
	काष्ठा btusb_data *btdata = hci_get_drvdata(hdev);
	काष्ठा usb_device *udev = btdata->udev;
	माप_प्रकार count, size, sent = 0;
	पूर्णांक pipe, len, err;
	u8 *buf;

	buf = kदो_स्मृति(QCA_DFU_PACKET_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	count = firmware->size;

	size = min_t(माप_प्रकार, count, hdr_size);
	स_नकल(buf, firmware->data, size);

	/* USB patches should go करोwn to controller through USB path
	 * because binary क्रमmat fits to go करोwn through USB channel.
	 * USB control path is क्रम patching headers and USB bulk is क्रम
	 * patch body.
	 */
	pipe = usb_sndctrlpipe(udev, 0);
	err = usb_control_msg(udev, pipe, QCA_DFU_DOWNLOAD, USB_TYPE_VENDOR,
			      0, 0, buf, size, USB_CTRL_SET_TIMEOUT);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send headers (%d)", err);
		जाओ करोne;
	पूर्ण

	sent += size;
	count -= size;

	जबतक (count) अणु
		size = min_t(माप_प्रकार, count, QCA_DFU_PACKET_LEN);

		स_नकल(buf, firmware->data + sent, size);

		pipe = usb_sndbulkpipe(udev, 0x02);
		err = usb_bulk_msg(udev, pipe, buf, size, &len,
				   QCA_DFU_TIMEOUT);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to send body at %zd of %zd (%d)",
				   sent, firmware->size, err);
			अवरोध;
		पूर्ण

		अगर (size != len) अणु
			bt_dev_err(hdev, "Failed to get bulk buffer");
			err = -EILSEQ;
			अवरोध;
		पूर्ण

		sent  += size;
		count -= size;
	पूर्ण

करोne:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक btusb_setup_qca_load_rampatch(काष्ठा hci_dev *hdev,
					 काष्ठा qca_version *ver,
					 स्थिर काष्ठा qca_device_info *info)
अणु
	काष्ठा qca_rampatch_version *rver;
	स्थिर काष्ठा firmware *fw;
	u32 ver_rom, ver_patch, rver_rom;
	u16 rver_rom_low, rver_rom_high, rver_patch;
	अक्षर fwname[64];
	पूर्णांक err;

	ver_rom = le32_to_cpu(ver->rom_version);
	ver_patch = le32_to_cpu(ver->patch_version);

	snम_लिखो(fwname, माप(fwname), "qca/rampatch_usb_%08x.bin", ver_rom);

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err) अणु
		bt_dev_err(hdev, "failed to request rampatch file: %s (%d)",
			   fwname, err);
		वापस err;
	पूर्ण

	bt_dev_info(hdev, "using rampatch file: %s", fwname);

	rver = (काष्ठा qca_rampatch_version *)(fw->data + info->ver_offset);
	rver_rom_low = le16_to_cpu(rver->rom_version_low);
	rver_patch = le16_to_cpu(rver->patch_version);

	अगर (ver_rom & ~0xffffU) अणु
		rver_rom_high = le16_to_cpu(rver->rom_version_high);
		rver_rom = le32_to_cpu(rver_rom_high << 16 | rver_rom_low);
	पूर्ण अन्यथा अणु
		rver_rom = rver_rom_low;
	पूर्ण

	bt_dev_info(hdev, "QCA: patch rome 0x%x build 0x%x, "
		    "firmware rome 0x%x build 0x%x",
		    rver_rom, rver_patch, ver_rom, ver_patch);

	अगर (rver_rom != ver_rom || rver_patch <= ver_patch) अणु
		bt_dev_err(hdev, "rampatch file version did not match with firmware");
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	err = btusb_setup_qca_करोwnload_fw(hdev, fw, info->rampatch_hdr);

करोne:
	release_firmware(fw);

	वापस err;
पूर्ण

अटल पूर्णांक btusb_setup_qca_load_nvm(काष्ठा hci_dev *hdev,
				    काष्ठा qca_version *ver,
				    स्थिर काष्ठा qca_device_info *info)
अणु
	स्थिर काष्ठा firmware *fw;
	अक्षर fwname[64];
	पूर्णांक err;

	अगर (((ver->flag >> 8) & 0xff) == QCA_FLAG_MULTI_NVM) अणु
		snम_लिखो(fwname, माप(fwname), "qca/nvm_usb_%08x_%04x.bin",
			 le32_to_cpu(ver->rom_version),
			 le16_to_cpu(ver->board_id));
	पूर्ण अन्यथा अणु
		snम_लिखो(fwname, माप(fwname), "qca/nvm_usb_%08x.bin",
			 le32_to_cpu(ver->rom_version));
	पूर्ण

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err) अणु
		bt_dev_err(hdev, "failed to request NVM file: %s (%d)",
			   fwname, err);
		वापस err;
	पूर्ण

	bt_dev_info(hdev, "using NVM file: %s", fwname);

	err = btusb_setup_qca_करोwnload_fw(hdev, fw, info->nvm_hdr);

	release_firmware(fw);

	वापस err;
पूर्ण

/* identअगरy the ROM version and check whether patches are needed */
अटल bool btusb_qca_need_patch(काष्ठा usb_device *udev)
अणु
	काष्ठा qca_version ver;

	अगर (btusb_qca_send_venकरोr_req(udev, QCA_GET_TARGET_VERSION, &ver,
				      माप(ver)) < 0)
		वापस false;
	/* only low ROM versions need patches */
	वापस !(le32_to_cpu(ver.rom_version) & ~0xffffU);
पूर्ण

अटल पूर्णांक btusb_setup_qca(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *btdata = hci_get_drvdata(hdev);
	काष्ठा usb_device *udev = btdata->udev;
	स्थिर काष्ठा qca_device_info *info = शून्य;
	काष्ठा qca_version ver;
	u32 ver_rom;
	u8 status;
	पूर्णांक i, err;

	err = btusb_qca_send_venकरोr_req(udev, QCA_GET_TARGET_VERSION, &ver,
					माप(ver));
	अगर (err < 0)
		वापस err;

	ver_rom = le32_to_cpu(ver.rom_version);

	क्रम (i = 0; i < ARRAY_SIZE(qca_devices_table); i++) अणु
		अगर (ver_rom == qca_devices_table[i].rom_version)
			info = &qca_devices_table[i];
	पूर्ण
	अगर (!info) अणु
		/* If the rom_version is not matched in the qca_devices_table
		 * and the high ROM version is not zero, we assume this chip no
		 * need to load the rampatch and nvm.
		 */
		अगर (ver_rom & ~0xffffU)
			वापस 0;

		bt_dev_err(hdev, "don't support firmware rome 0x%x", ver_rom);
		वापस -ENODEV;
	पूर्ण

	err = btusb_qca_send_venकरोr_req(udev, QCA_CHECK_STATUS, &status,
					माप(status));
	अगर (err < 0)
		वापस err;

	अगर (!(status & QCA_PATCH_UPDATED)) अणु
		err = btusb_setup_qca_load_rampatch(hdev, &ver, info);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = btusb_qca_send_venकरोr_req(udev, QCA_GET_TARGET_VERSION, &ver,
					माप(ver));
	अगर (err < 0)
		वापस err;

	अगर (!(status & QCA_SYSCFG_UPDATED)) अणु
		err = btusb_setup_qca_load_nvm(hdev, &ver, info);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __set_diag_पूर्णांकerface(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = data->diag;
	पूर्णांक i;

	अगर (!data->diag)
		वापस -ENODEV;

	data->diag_tx_ep = शून्य;
	data->diag_rx_ep = शून्य;

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;

		ep_desc = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (!data->diag_tx_ep && usb_endpoपूर्णांक_is_bulk_out(ep_desc)) अणु
			data->diag_tx_ep = ep_desc;
			जारी;
		पूर्ण

		अगर (!data->diag_rx_ep && usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			data->diag_rx_ep = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!data->diag_tx_ep || !data->diag_rx_ep) अणु
		bt_dev_err(hdev, "invalid diagnostic descriptors");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा urb *alloc_diag_urb(काष्ठा hci_dev *hdev, bool enable)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा sk_buff *skb;
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;

	अगर (!data->diag_tx_ep)
		वापस ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस ERR_PTR(-ENOMEM);

	skb = bt_skb_alloc(2, GFP_KERNEL);
	अगर (!skb) अणु
		usb_मुक्त_urb(urb);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	skb_put_u8(skb, 0xf0);
	skb_put_u8(skb, enable);

	pipe = usb_sndbulkpipe(data->udev, data->diag_tx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe,
			  skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (व्योम *)hdev;

	वापस urb;
पूर्ण

अटल पूर्णांक btusb_bcm_set_diag(काष्ठा hci_dev *hdev, bool enable)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा urb *urb;

	अगर (!data->diag)
		वापस -ENODEV;

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस -ENETDOWN;

	urb = alloc_diag_urb(hdev, enable);
	अगर (IS_ERR(urb))
		वापस PTR_ERR(urb);

	वापस submit_or_queue_tx_urb(hdev, urb);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल irqवापस_t btusb_oob_wake_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा btusb_data *data = priv;

	pm_wakeup_event(&data->udev->dev, 0);
	pm_प्रणाली_wakeup();

	/* Disable only अगर not alपढ़ोy disabled (keep it balanced) */
	अगर (test_and_clear_bit(BTUSB_OOB_WAKE_ENABLED, &data->flags)) अणु
		disable_irq_nosync(irq);
		disable_irq_wake(irq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id btusb_match_table[] = अणु
	अणु .compatible = "usb1286,204e" पूर्ण,
	अणु .compatible = "usbcf3,e300" पूर्ण, /* QCA6174A */
	अणु .compatible = "usb4ca,301a" पूर्ण, /* QCA6174A (Lite-On) */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, btusb_match_table);

/* Use an oob wakeup pin? */
अटल पूर्णांक btusb_config_oob_wake(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);
	काष्ठा device *dev = &data->udev->dev;
	पूर्णांक irq, ret;

	clear_bit(BTUSB_OOB_WAKE_ENABLED, &data->flags);

	अगर (!of_match_device(btusb_match_table, dev))
		वापस 0;

	/* Move on अगर no IRQ specअगरied */
	irq = of_irq_get_byname(dev->of_node, "wakeup");
	अगर (irq <= 0) अणु
		bt_dev_dbg(hdev, "%s: no OOB Wakeup IRQ in DT", __func__);
		वापस 0;
	पूर्ण

	irq_set_status_flags(irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&hdev->dev, irq, btusb_oob_wake_handler,
			       0, "OOB Wake-on-BT", data);
	अगर (ret) अणु
		bt_dev_err(hdev, "%s: IRQ request failed", __func__);
		वापस ret;
	पूर्ण

	ret = device_init_wakeup(dev, true);
	अगर (ret) अणु
		bt_dev_err(hdev, "%s: failed to init_wakeup", __func__);
		वापस ret;
	पूर्ण

	data->oob_wake_irq = irq;
	bt_dev_info(hdev, "OOB Wake-on-BT configured at IRQ %u", irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम btusb_check_needs_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (dmi_check_प्रणाली(btusb_needs_reset_resume_table))
		पूर्णांकerface_to_usbdev(पूर्णांकf)->quirks |= USB_QUIRK_RESET_RESUME;
पूर्ण

अटल bool btusb_prevent_wake(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btusb_data *data = hci_get_drvdata(hdev);

	अगर (test_bit(BTUSB_WAKEUP_DISABLE, &data->flags))
		वापस true;

	वापस !device_may_wakeup(&data->udev->dev);
पूर्ण

अटल पूर्णांक btusb_shutकरोwn_qca(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा btusb_data *data;
	काष्ठा hci_dev *hdev;
	अचिन्हित अगरnum_base;
	पूर्णांक i, err;

	BT_DBG("intf %p id %p", पूर्णांकf, id);

	/* पूर्णांकerface numbers are hardcoded in the spec */
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0) अणु
		अगर (!(id->driver_info & BTUSB_IFNUM_2))
			वापस -ENODEV;
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 2)
			वापस -ENODEV;
	पूर्ण

	अगरnum_base = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	अगर (!id->driver_info) अणु
		स्थिर काष्ठा usb_device_id *match;

		match = usb_match_id(पूर्णांकf, blacklist_table);
		अगर (match)
			id = match;
	पूर्ण

	अगर (id->driver_info == BTUSB_IGNORE)
		वापस -ENODEV;

	अगर (id->driver_info & BTUSB_ATH3012) अणु
		काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

		/* Old firmware would otherwise let ath3k driver load
		 * patch and sysconfig files
		 */
		अगर (le16_to_cpu(udev->descriptor.bcdDevice) <= 0x0001 &&
		    !btusb_qca_need_patch(udev))
			वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&पूर्णांकf->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (!data->पूर्णांकr_ep && usb_endpoपूर्णांक_is_पूर्णांक_in(ep_desc)) अणु
			data->पूर्णांकr_ep = ep_desc;
			जारी;
		पूर्ण

		अगर (!data->bulk_tx_ep && usb_endpoपूर्णांक_is_bulk_out(ep_desc)) अणु
			data->bulk_tx_ep = ep_desc;
			जारी;
		पूर्ण

		अगर (!data->bulk_rx_ep && usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			data->bulk_rx_ep = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!data->पूर्णांकr_ep || !data->bulk_tx_ep || !data->bulk_rx_ep)
		वापस -ENODEV;

	अगर (id->driver_info & BTUSB_AMP) अणु
		data->cmdreq_type = USB_TYPE_CLASS | 0x01;
		data->cmdreq = 0x2b;
	पूर्ण अन्यथा अणु
		data->cmdreq_type = USB_TYPE_CLASS;
		data->cmdreq = 0x00;
	पूर्ण

	data->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	data->पूर्णांकf = पूर्णांकf;

	INIT_WORK(&data->work, btusb_work);
	INIT_WORK(&data->waker, btusb_waker);
	init_usb_anchor(&data->deferred);
	init_usb_anchor(&data->tx_anchor);
	spin_lock_init(&data->txlock);

	init_usb_anchor(&data->पूर्णांकr_anchor);
	init_usb_anchor(&data->bulk_anchor);
	init_usb_anchor(&data->isoc_anchor);
	init_usb_anchor(&data->diag_anchor);
	init_usb_anchor(&data->ctrl_anchor);
	spin_lock_init(&data->rxlock);

	अगर (id->driver_info & BTUSB_INTEL_NEW) अणु
		data->recv_event = btusb_recv_event_पूर्णांकel;
		data->recv_bulk = btusb_recv_bulk_पूर्णांकel;
		set_bit(BTUSB_BOOTLOADER, &data->flags);
	पूर्ण अन्यथा अणु
		data->recv_event = hci_recv_frame;
		data->recv_bulk = btusb_recv_bulk;
	पूर्ण

	hdev = hci_alloc_dev();
	अगर (!hdev)
		वापस -ENOMEM;

	hdev->bus = HCI_USB;
	hci_set_drvdata(hdev, data);

	अगर (id->driver_info & BTUSB_AMP)
		hdev->dev_type = HCI_AMP;
	अन्यथा
		hdev->dev_type = HCI_PRIMARY;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &पूर्णांकf->dev);

	reset_gpio = gpiod_get_optional(&data->udev->dev, "reset",
					GPIOD_OUT_LOW);
	अगर (IS_ERR(reset_gpio)) अणु
		err = PTR_ERR(reset_gpio);
		जाओ out_मुक्त_dev;
	पूर्ण अन्यथा अगर (reset_gpio) अणु
		data->reset_gpio = reset_gpio;
	पूर्ण

	hdev->खोलो   = btusb_खोलो;
	hdev->बंद  = btusb_बंद;
	hdev->flush  = btusb_flush;
	hdev->send   = btusb_send_frame;
	hdev->notअगरy = btusb_notअगरy;
	hdev->prevent_wake = btusb_prevent_wake;

#अगर_घोषित CONFIG_PM
	err = btusb_config_oob_wake(hdev);
	अगर (err)
		जाओ out_मुक्त_dev;

	/* Marvell devices may need a specअगरic chip configuration */
	अगर (id->driver_info & BTUSB_MARVELL && data->oob_wake_irq) अणु
		err = marvell_config_oob_wake(hdev);
		अगर (err)
			जाओ out_मुक्त_dev;
	पूर्ण
#पूर्ण_अगर
	अगर (id->driver_info & BTUSB_CW6622)
		set_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks);

	अगर (id->driver_info & BTUSB_BCM2045)
		set_bit(HCI_QUIRK_BROKEN_STORED_LINK_KEY, &hdev->quirks);

	अगर (id->driver_info & BTUSB_BCM92035)
		hdev->setup = btusb_setup_bcm92035;

	अगर (IS_ENABLED(CONFIG_BT_HCIBTUSB_BCM) &&
	    (id->driver_info & BTUSB_BCM_PATCHRAM)) अणु
		hdev->manufacturer = 15;
		hdev->setup = btbcm_setup_patchram;
		hdev->set_diag = btusb_bcm_set_diag;
		hdev->set_bdaddr = btbcm_set_bdaddr;

		/* Broadcom LM_DIAG Interface numbers are hardcoded */
		data->diag = usb_अगरnum_to_अगर(data->udev, अगरnum_base + 2);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_BT_HCIBTUSB_BCM) &&
	    (id->driver_info & BTUSB_BCM_APPLE)) अणु
		hdev->manufacturer = 15;
		hdev->setup = btbcm_setup_apple;
		hdev->set_diag = btusb_bcm_set_diag;

		/* Broadcom LM_DIAG Interface numbers are hardcoded */
		data->diag = usb_अगरnum_to_अगर(data->udev, अगरnum_base + 2);
	पूर्ण

	अगर (id->driver_info & BTUSB_INTEL) अणु
		hdev->manufacturer = 2;
		hdev->setup = btusb_setup_पूर्णांकel;
		hdev->shutकरोwn = btusb_shutकरोwn_पूर्णांकel;
		hdev->set_diag = btपूर्णांकel_set_diag_mfg;
		hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;
		hdev->cmd_समयout = btusb_पूर्णांकel_cmd_समयout;
		set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
		set_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_INTEL_NEW) अणु
		hdev->manufacturer = 2;
		hdev->send = btusb_send_frame_पूर्णांकel;
		hdev->setup = btusb_setup_पूर्णांकel_new;
		hdev->shutकरोwn = btusb_shutकरोwn_पूर्णांकel_new;
		hdev->hw_error = btपूर्णांकel_hw_error;
		hdev->set_diag = btपूर्णांकel_set_diag;
		hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;
		hdev->cmd_समयout = btusb_पूर्णांकel_cmd_समयout;
		set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
		set_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_INTEL_NEWGEN) अणु
		hdev->manufacturer = 2;
		hdev->send = btusb_send_frame_पूर्णांकel;
		hdev->setup = btusb_setup_पूर्णांकel_newgen;
		hdev->shutकरोwn = btusb_shutकरोwn_पूर्णांकel_new;
		hdev->hw_error = btपूर्णांकel_hw_error;
		hdev->set_diag = btपूर्णांकel_set_diag;
		hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;
		hdev->cmd_समयout = btusb_पूर्णांकel_cmd_समयout;
		set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
		set_bit(HCI_QUIRK_NON_PERSISTENT_DIAG, &hdev->quirks);

		data->recv_event = btusb_recv_event_पूर्णांकel;
		data->recv_bulk = btusb_recv_bulk_पूर्णांकel;
		set_bit(BTUSB_BOOTLOADER, &data->flags);
	पूर्ण

	अगर (id->driver_info & BTUSB_MARVELL)
		hdev->set_bdaddr = btusb_set_bdaddr_marvell;

	अगर (IS_ENABLED(CONFIG_BT_HCIBTUSB_MTK) &&
	    (id->driver_info & BTUSB_MEDIATEK)) अणु
		hdev->setup = btusb_mtk_setup;
		hdev->shutकरोwn = btusb_mtk_shutकरोwn;
		hdev->manufacturer = 70;
		set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_SWAVE) अणु
		set_bit(HCI_QUIRK_FIXUP_INQUIRY_MODE, &hdev->quirks);
		set_bit(HCI_QUIRK_BROKEN_LOCAL_COMMANDS, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_INTEL_BOOT) अणु
		hdev->manufacturer = 2;
		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_ATH3012) अणु
		data->setup_on_usb = btusb_setup_qca;
		hdev->set_bdaddr = btusb_set_bdaddr_ath3012;
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
		set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_QCA_ROME) अणु
		data->setup_on_usb = btusb_setup_qca;
		hdev->set_bdaddr = btusb_set_bdaddr_ath3012;
		hdev->cmd_समयout = btusb_qca_cmd_समयout;
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
		btusb_check_needs_reset_resume(पूर्णांकf);
	पूर्ण

	अगर (id->driver_info & BTUSB_QCA_WCN6855) अणु
		data->setup_on_usb = btusb_setup_qca;
		hdev->shutकरोwn = btusb_shutकरोwn_qca;
		hdev->set_bdaddr = btusb_set_bdaddr_wcn6855;
		hdev->cmd_समयout = btusb_qca_cmd_समयout;
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_AMP) अणु
		/* AMP controllers करो not support SCO packets */
		data->isoc = शून्य;
	पूर्ण अन्यथा अणु
		/* Interface orders are hardcoded in the specअगरication */
		data->isoc = usb_अगरnum_to_अगर(data->udev, अगरnum_base + 1);
		data->isoc_अगरnum = अगरnum_base + 1;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_BT_HCIBTUSB_RTL) &&
	    (id->driver_info & BTUSB_REALTEK)) अणु
		hdev->setup = btrtl_setup_realtek;
		hdev->shutकरोwn = btrtl_shutकरोwn_realtek;
		hdev->cmd_समयout = btusb_rtl_cmd_समयout;

		/* Realtek devices lose their updated firmware over global
		 * suspend that means host करोesn't send SET_FEATURE
		 * (DEVICE_REMOTE_WAKEUP)
		 */
		set_bit(BTUSB_WAKEUP_DISABLE, &data->flags);
	पूर्ण

	अगर (!reset)
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	अगर (क्रमce_scofix || id->driver_info & BTUSB_WRONG_SCO_MTU) अणु
		अगर (!disable_scofix)
			set_bit(HCI_QUIRK_FIXUP_BUFFER_SIZE, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_BROKEN_ISOC)
		data->isoc = शून्य;

	अगर (id->driver_info & BTUSB_WIDEBAND_SPEECH)
		set_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED, &hdev->quirks);

	अगर (id->driver_info & BTUSB_VALID_LE_STATES)
		set_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks);

	अगर (id->driver_info & BTUSB_DIGIANSWER) अणु
		data->cmdreq_type = USB_TYPE_VENDOR;
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_CSR) अणु
		काष्ठा usb_device *udev = data->udev;
		u16 bcdDevice = le16_to_cpu(udev->descriptor.bcdDevice);

		/* Old firmware would otherwise execute USB reset */
		अगर (bcdDevice < 0x117)
			set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

		/* This must be set first in हाल we disable it क्रम fakes */
		set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

		/* Fake CSR devices with broken commands */
		अगर (le16_to_cpu(udev->descriptor.idVenकरोr)  == 0x0a12 &&
		    le16_to_cpu(udev->descriptor.idProduct) == 0x0001)
			hdev->setup = btusb_setup_csr;
	पूर्ण

	अगर (id->driver_info & BTUSB_SNIFFER) अणु
		काष्ठा usb_device *udev = data->udev;

		/* New snअगरfer firmware has crippled HCI पूर्णांकerface */
		अगर (le16_to_cpu(udev->descriptor.bcdDevice) > 0x997)
			set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);
	पूर्ण

	अगर (id->driver_info & BTUSB_INTEL_BOOT) अणु
		/* A bug in the bootloader causes that पूर्णांकerrupt पूर्णांकerface is
		 * only enabled after receiving SetInterface(0, AltSetting=0).
		 */
		err = usb_set_पूर्णांकerface(data->udev, 0, 0);
		अगर (err < 0) अणु
			BT_ERR("failed to set interface 0, alt 0 %d", err);
			जाओ out_मुक्त_dev;
		पूर्ण
	पूर्ण

	अगर (data->isoc) अणु
		err = usb_driver_claim_पूर्णांकerface(&btusb_driver,
						 data->isoc, data);
		अगर (err < 0)
			जाओ out_मुक्त_dev;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_BT_HCIBTUSB_BCM) && data->diag) अणु
		अगर (!usb_driver_claim_पूर्णांकerface(&btusb_driver,
						data->diag, data))
			__set_diag_पूर्णांकerface(hdev);
		अन्यथा
			data->diag = शून्य;
	पूर्ण

	अगर (enable_स्वतःsuspend)
		usb_enable_स्वतःsuspend(data->udev);

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0)
		जाओ out_मुक्त_dev;

	usb_set_पूर्णांकfdata(पूर्णांकf, data);

	वापस 0;

out_मुक्त_dev:
	अगर (data->reset_gpio)
		gpiod_put(data->reset_gpio);
	hci_मुक्त_dev(hdev);
	वापस err;
पूर्ण

अटल व्योम btusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा btusb_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा hci_dev *hdev;

	BT_DBG("intf %p", पूर्णांकf);

	अगर (!data)
		वापस;

	hdev = data->hdev;
	usb_set_पूर्णांकfdata(data->पूर्णांकf, शून्य);

	अगर (data->isoc)
		usb_set_पूर्णांकfdata(data->isoc, शून्य);

	अगर (data->diag)
		usb_set_पूर्णांकfdata(data->diag, शून्य);

	hci_unरेजिस्टर_dev(hdev);

	अगर (पूर्णांकf == data->पूर्णांकf) अणु
		अगर (data->isoc)
			usb_driver_release_पूर्णांकerface(&btusb_driver, data->isoc);
		अगर (data->diag)
			usb_driver_release_पूर्णांकerface(&btusb_driver, data->diag);
	पूर्ण अन्यथा अगर (पूर्णांकf == data->isoc) अणु
		अगर (data->diag)
			usb_driver_release_पूर्णांकerface(&btusb_driver, data->diag);
		usb_driver_release_पूर्णांकerface(&btusb_driver, data->पूर्णांकf);
	पूर्ण अन्यथा अगर (पूर्णांकf == data->diag) अणु
		usb_driver_release_पूर्णांकerface(&btusb_driver, data->पूर्णांकf);
		अगर (data->isoc)
			usb_driver_release_पूर्णांकerface(&btusb_driver, data->isoc);
	पूर्ण

	अगर (data->oob_wake_irq)
		device_init_wakeup(&data->udev->dev, false);

	अगर (data->reset_gpio)
		gpiod_put(data->reset_gpio);

	hci_मुक्त_dev(hdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक btusb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा btusb_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);

	BT_DBG("intf %p", पूर्णांकf);

	अगर (data->suspend_count++)
		वापस 0;

	spin_lock_irq(&data->txlock);
	अगर (!(PMSG_IS_AUTO(message) && data->tx_in_flight)) अणु
		set_bit(BTUSB_SUSPENDING, &data->flags);
		spin_unlock_irq(&data->txlock);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&data->txlock);
		data->suspend_count--;
		वापस -EBUSY;
	पूर्ण

	cancel_work_sync(&data->work);

	btusb_stop_traffic(data);
	usb_समाप्त_anchored_urbs(&data->tx_anchor);

	अगर (data->oob_wake_irq && device_may_wakeup(&data->udev->dev)) अणु
		set_bit(BTUSB_OOB_WAKE_ENABLED, &data->flags);
		enable_irq_wake(data->oob_wake_irq);
		enable_irq(data->oob_wake_irq);
	पूर्ण

	/* For global suspend, Realtek devices lose the loaded fw
	 * in them. But क्रम स्वतःsuspend, firmware should reमुख्य.
	 * Actually, it depends on whether the usb host sends
	 * set feature (enable wakeup) or not.
	 */
	अगर (test_bit(BTUSB_WAKEUP_DISABLE, &data->flags)) अणु
		अगर (PMSG_IS_AUTO(message) &&
		    device_can_wakeup(&data->udev->dev))
			data->udev->करो_remote_wakeup = 1;
		अन्यथा अगर (!PMSG_IS_AUTO(message))
			data->udev->reset_resume = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम play_deferred(काष्ठा btusb_data *data)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;

	जबतक ((urb = usb_get_from_anchor(&data->deferred))) अणु
		usb_anchor_urb(urb, &data->tx_anchor);

		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err < 0) अणु
			अगर (err != -EPERM && err != -ENODEV)
				BT_ERR("%s urb %p submission failed (%d)",
				       data->hdev->name, urb, -err);
			kमुक्त(urb->setup_packet);
			usb_unanchor_urb(urb);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		data->tx_in_flight++;
		usb_मुक्त_urb(urb);
	पूर्ण

	/* Cleanup the rest deferred urbs. */
	जबतक ((urb = usb_get_from_anchor(&data->deferred))) अणु
		kमुक्त(urb->setup_packet);
		usb_मुक्त_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक btusb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा btusb_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा hci_dev *hdev = data->hdev;
	पूर्णांक err = 0;

	BT_DBG("intf %p", पूर्णांकf);

	अगर (--data->suspend_count)
		वापस 0;

	/* Disable only अगर not alपढ़ोy disabled (keep it balanced) */
	अगर (test_and_clear_bit(BTUSB_OOB_WAKE_ENABLED, &data->flags)) अणु
		disable_irq(data->oob_wake_irq);
		disable_irq_wake(data->oob_wake_irq);
	पूर्ण

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		जाओ करोne;

	अगर (test_bit(BTUSB_INTR_RUNNING, &data->flags)) अणु
		err = btusb_submit_पूर्णांकr_urb(hdev, GFP_NOIO);
		अगर (err < 0) अणु
			clear_bit(BTUSB_INTR_RUNNING, &data->flags);
			जाओ failed;
		पूर्ण
	पूर्ण

	अगर (test_bit(BTUSB_BULK_RUNNING, &data->flags)) अणु
		err = btusb_submit_bulk_urb(hdev, GFP_NOIO);
		अगर (err < 0) अणु
			clear_bit(BTUSB_BULK_RUNNING, &data->flags);
			जाओ failed;
		पूर्ण

		btusb_submit_bulk_urb(hdev, GFP_NOIO);
	पूर्ण

	अगर (test_bit(BTUSB_ISOC_RUNNING, &data->flags)) अणु
		अगर (btusb_submit_isoc_urb(hdev, GFP_NOIO) < 0)
			clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
		अन्यथा
			btusb_submit_isoc_urb(hdev, GFP_NOIO);
	पूर्ण

	spin_lock_irq(&data->txlock);
	play_deferred(data);
	clear_bit(BTUSB_SUSPENDING, &data->flags);
	spin_unlock_irq(&data->txlock);
	schedule_work(&data->work);

	वापस 0;

failed:
	usb_scuttle_anchored_urbs(&data->deferred);
करोne:
	spin_lock_irq(&data->txlock);
	clear_bit(BTUSB_SUSPENDING, &data->flags);
	spin_unlock_irq(&data->txlock);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा usb_driver btusb_driver = अणु
	.name		= "btusb",
	.probe		= btusb_probe,
	.disconnect	= btusb_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend	= btusb_suspend,
	.resume		= btusb_resume,
#पूर्ण_अगर
	.id_table	= btusb_table,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(btusb_driver);

module_param(disable_scofix, bool, 0644);
MODULE_PARM_DESC(disable_scofix, "Disable fixup of wrong SCO buffer size");

module_param(क्रमce_scofix, bool, 0644);
MODULE_PARM_DESC(क्रमce_scofix, "Force fixup of wrong SCO buffers size");

module_param(enable_स्वतःsuspend, bool, 0644);
MODULE_PARM_DESC(enable_स्वतःsuspend, "Enable USB autosuspend by default");

module_param(reset, bool, 0644);
MODULE_PARM_DESC(reset, "Send HCI reset command on initialization");

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Generic Bluetooth USB driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
