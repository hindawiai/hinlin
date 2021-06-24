<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */
#अगर_अघोषित _AS102_USB_DRV_H_
#घोषणा _AS102_USB_DRV_H_

#घोषणा AS102_USB_DEVICE_TX_CTRL_CMD	0xF1
#घोषणा AS102_USB_DEVICE_RX_CTRL_CMD	0xF2

/* define these values to match the supported devices */

/* Abilis प्रणाली: "TITAN" */
#घोषणा AS102_REFERENCE_DESIGN		"Abilis Systems DVB-Titan"
#घोषणा AS102_USB_DEVICE_VENDOR_ID	0x1BA6
#घोषणा AS102_USB_DEVICE_PID_0001	0x0001

/* PCTV Systems: PCTV picoStick (74e) */
#घोषणा AS102_PCTV_74E			"PCTV Systems picoStick (74e)"
#घोषणा PCTV_74E_USB_VID		0x2013
#घोषणा PCTV_74E_USB_PID		0x0246

/* Elgato: EyeTV DTT Deluxe */
#घोषणा AS102_ELGATO_EYETV_DTT_NAME	"Elgato EyeTV DTT Deluxe"
#घोषणा ELGATO_EYETV_DTT_USB_VID	0x0fd9
#घोषणा ELGATO_EYETV_DTT_USB_PID	0x002c

/* nBox: nBox DVB-T Dongle */
#घोषणा AS102_NBOX_DVBT_DONGLE_NAME	"nBox DVB-T Dongle"
#घोषणा NBOX_DVBT_DONGLE_USB_VID	0x0b89
#घोषणा NBOX_DVBT_DONGLE_USB_PID	0x0007

/* Sky Italia: Digital Key (green led) */
#घोषणा AS102_SKY_IT_DIGITAL_KEY_NAME	"Sky IT Digital Key (green led)"
#घोषणा SKY_IT_DIGITAL_KEY_USB_VID	0x2137
#घोषणा SKY_IT_DIGITAL_KEY_USB_PID	0x0001

व्योम as102_urb_stream_irq(काष्ठा urb *urb);

काष्ठा as10x_usb_token_cmd_t अणु
	/* token cmd */
	काष्ठा as10x_cmd_t c;
	/* token response */
	काष्ठा as10x_cmd_t r;
पूर्ण;
#पूर्ण_अगर
