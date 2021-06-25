<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CYPRESS_M8_H
#घोषणा CYPRESS_M8_H

/*
 * definitions and function prototypes used क्रम the cypress USB to Serial
 * controller
 */

/*
 * For sending our feature buffer - controlling serial communication states.
 * Linux HID has no support क्रम serial devices so we करो this through the driver
 */
#घोषणा HID_REQ_GET_REPORT	0x01
#घोषणा HID_REQ_SET_REPORT	0x09

/* List other cypress USB to Serial devices here, and add them to the id_table */

/* DeLorme Earthmate USB - a GPS device */
#घोषणा VENDOR_ID_DELORME		0x1163
#घोषणा PRODUCT_ID_EARTHMATEUSB		0x0100
#घोषणा PRODUCT_ID_EARTHMATEUSB_LT20	0x0200

/* Cypress HID->COM RS232 Adapter */
#घोषणा VENDOR_ID_CYPRESS		0x04b4
#घोषणा PRODUCT_ID_CYPHIDCOM		0x5500

/* Simply Automated HID->COM UPB PIM (using Cypress PID 0x5500) */
#घोषणा VENDOR_ID_SAI			0x17dd

/* FRWD Dongle - a GPS sports watch */
#घोषणा VENDOR_ID_FRWD			0x6737
#घोषणा PRODUCT_ID_CYPHIDCOM_FRWD	0x0001

/* Powercom UPS, chip CY7C63723 */
#घोषणा VENDOR_ID_POWERCOM		0x0d9f
#घोषणा PRODUCT_ID_UPS			0x0002

/* Nokia CA-42 USB to serial cable */
#घोषणा VENDOR_ID_DAZZLE		0x07d0
#घोषणा PRODUCT_ID_CA42			0x4101
/* End of device listing */

/* Used क्रम setting / requesting serial line settings */
#घोषणा CYPRESS_SET_CONFIG	0x01
#घोषणा CYPRESS_GET_CONFIG	0x02

/* Used क्रम throttle control */
#घोषणा THROTTLED		0x1
#घोषणा ACTUALLY_THROTTLED	0x2

/*
 * chiptypes - used in हाल firmware dअगरfers from the generic क्रमm ... offering
 * dअगरferent baud speeds/etc.
 */
#घोषणा CT_EARTHMATE	0x01
#घोषणा CT_CYPHIDCOM	0x02
#घोषणा CT_CA42V2	0x03
#घोषणा CT_GENERIC	0x0F
/* End of chiptype definitions */

/*
 * RS-232 serial data communication protocol definitions.
 *
 * These are sent / पढ़ो at byte 0 of the input/output hid reports.
 * You can find these values defined in the CY4601 USB to Serial design notes.
 */

#घोषणा CONTROL_DTR	0x20	/* data terminal पढ़ोy */
#घोषणा CONTROL_RTS	0x10	/* request to send */
#घोषणा CONTROL_RESET	0x08	/* sent with output report */

#घोषणा UART_MSR_MASK	0xf0
#घोषणा UART_RI		0x80	/* ring indicator */
#घोषणा UART_CD		0x40	/* carrier detect */
#घोषणा UART_DSR	0x20	/* data set पढ़ोy */
#घोषणा UART_CTS	0x10	/* clear to send */
#घोषणा CYP_ERROR	0x08	/* received from input report */

/* End of RS-232 protocol definitions */

#पूर्ण_अगर /* CYPRESS_M8_H */
