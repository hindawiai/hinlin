<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CAN driver क्रम PEAK System PCAN-USB Pro adapter
 * Derived from the PCAN project file driver/src/pcan_usbpro_fw.h
 *
 * Copyright (C) 2003-2011 PEAK System-Technik GmbH
 * Copyright (C) 2011-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 */
#अगर_अघोषित PCAN_USB_PRO_H
#घोषणा PCAN_USB_PRO_H

/*
 * USB Venकरोr request data types
 */
#घोषणा PCAN_USBPRO_REQ_INFO		0
#घोषणा PCAN_USBPRO_REQ_FCT		2

/* Venकरोr Request value क्रम XXX_INFO */
#घोषणा PCAN_USBPRO_INFO_BL		0
#घोषणा PCAN_USBPRO_INFO_FW		1

/* PCAN-USB Pro (FD) Endpoपूर्णांकs */
#घोषणा PCAN_USBPRO_EP_CMDOUT		1
#घोषणा PCAN_USBPRO_EP_CMDIN		(PCAN_USBPRO_EP_CMDOUT | USB_सूची_IN)
#घोषणा PCAN_USBPRO_EP_MSGOUT_0		2
#घोषणा PCAN_USBPRO_EP_MSGIN		(PCAN_USBPRO_EP_MSGOUT_0 | USB_सूची_IN)
#घोषणा PCAN_USBPRO_EP_MSGOUT_1		3
#घोषणा PCAN_USBPRO_EP_UNUSED		(PCAN_USBPRO_EP_MSGOUT_1 | USB_सूची_IN)

/* Venकरोr Request value क्रम XXX_FCT */
#घोषणा PCAN_USBPRO_FCT_DRVLD		5 /* tell device driver is loaded */
#घोषणा PCAN_USBPRO_FCT_DRVLD_REQ_LEN	16

/* PCAN_USBPRO_INFO_BL venकरोr request record type */
काष्ठा __packed pcan_usb_pro_blinfo अणु
	__le32 ctrl_type;
	u8 version[4];
	u8 day;
	u8 month;
	u8 year;
	u8 dummy;
	__le32 serial_num_hi;
	__le32 serial_num_lo;
	__le32 hw_type;
	__le32 hw_rev;
पूर्ण;

/* PCAN_USBPRO_INFO_FW venकरोr request record type */
काष्ठा __packed pcan_usb_pro_fwinfo अणु
	__le32 ctrl_type;
	u8 version[4];
	u8 day;
	u8 month;
	u8 year;
	u8 dummy;
	__le32 fw_type;
पूर्ण;

/*
 * USB Command record types
 */
#घोषणा PCAN_USBPRO_SETBTR	0x02
#घोषणा PCAN_USBPRO_SETBUSACT	0x04
#घोषणा PCAN_USBPRO_SETSILENT	0x05
#घोषणा PCAN_USBPRO_SETFILTR	0x0a
#घोषणा PCAN_USBPRO_SETTS	0x10
#घोषणा PCAN_USBPRO_GETDEVID	0x12
#घोषणा PCAN_USBPRO_SETLED	0x1C
#घोषणा PCAN_USBPRO_RXMSG8	0x80
#घोषणा PCAN_USBPRO_RXMSG4	0x81
#घोषणा PCAN_USBPRO_RXMSG0	0x82
#घोषणा PCAN_USBPRO_RXRTR	0x83
#घोषणा PCAN_USBPRO_RXSTATUS	0x84
#घोषणा PCAN_USBPRO_RXTS	0x85
#घोषणा PCAN_USBPRO_TXMSG8	0x41
#घोषणा PCAN_USBPRO_TXMSG4	0x42
#घोषणा PCAN_USBPRO_TXMSG0	0x43

/* record काष्ठाures */
काष्ठा __packed pcan_usb_pro_btr अणु
	u8 data_type;
	u8 channel;
	__le16 dummy;
	__le32 CCBT;
पूर्ण;

काष्ठा __packed pcan_usb_pro_busact अणु
	u8 data_type;
	u8 channel;
	__le16 onoff;
पूर्ण;

काष्ठा __packed pcan_usb_pro_silent अणु
	u8 data_type;
	u8 channel;
	__le16 onoff;
पूर्ण;

काष्ठा __packed pcan_usb_pro_filter अणु
	u8 data_type;
	u8 dummy;
	__le16 filter_mode;
पूर्ण;

काष्ठा __packed pcan_usb_pro_setts अणु
	u8 data_type;
	u8 dummy;
	__le16 mode;
पूर्ण;

काष्ठा __packed pcan_usb_pro_devid अणु
	u8 data_type;
	u8 channel;
	__le16 dummy;
	__le32 serial_num;
पूर्ण;

#घोषणा PCAN_USBPRO_LED_DEVICE		0x00
#घोषणा PCAN_USBPRO_LED_BLINK_FAST	0x01
#घोषणा PCAN_USBPRO_LED_BLINK_SLOW	0x02
#घोषणा PCAN_USBPRO_LED_ON		0x03
#घोषणा PCAN_USBPRO_LED_OFF		0x04

काष्ठा __packed pcan_usb_pro_setled अणु
	u8 data_type;
	u8 channel;
	__le16 mode;
	__le32 समयout;
पूर्ण;

काष्ठा __packed pcan_usb_pro_rxmsg अणु
	u8 data_type;
	u8 client;
	u8 flags;
	u8 len;
	__le32 ts32;
	__le32 id;

	u8 data[8];
पूर्ण;

#घोषणा PCAN_USBPRO_STATUS_ERROR	0x0001
#घोषणा PCAN_USBPRO_STATUS_BUS		0x0002
#घोषणा PCAN_USBPRO_STATUS_OVERRUN	0x0004
#घोषणा PCAN_USBPRO_STATUS_QOVERRUN	0x0008

काष्ठा __packed pcan_usb_pro_rxstatus अणु
	u8 data_type;
	u8 channel;
	__le16 status;
	__le32 ts32;
	__le32 err_frm;
पूर्ण;

काष्ठा __packed pcan_usb_pro_rxts अणु
	u8 data_type;
	u8 dummy[3];
	__le32 ts64[2];
पूर्ण;

काष्ठा __packed pcan_usb_pro_txmsg अणु
	u8 data_type;
	u8 client;
	u8 flags;
	u8 len;
	__le32 id;
	u8 data[8];
पूर्ण;

जोड़ pcan_usb_pro_rec अणु
	u8				data_type;
	काष्ठा pcan_usb_pro_btr		btr;
	काष्ठा pcan_usb_pro_busact	bus_act;
	काष्ठा pcan_usb_pro_silent	silent_mode;
	काष्ठा pcan_usb_pro_filter	filter_mode;
	काष्ठा pcan_usb_pro_setts	ts;
	काष्ठा pcan_usb_pro_devid	dev_id;
	काष्ठा pcan_usb_pro_setled	set_led;
	काष्ठा pcan_usb_pro_rxmsg	rx_msg;
	काष्ठा pcan_usb_pro_rxstatus	rx_status;
	काष्ठा pcan_usb_pro_rxts	rx_ts;
	काष्ठा pcan_usb_pro_txmsg	tx_msg;
पूर्ण;

पूर्णांक pcan_usb_pro_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक pcan_usb_pro_send_req(काष्ठा peak_usb_device *dev, पूर्णांक req_id,
			  पूर्णांक req_value, व्योम *req_addr, पूर्णांक req_size);
व्योम pcan_usb_pro_restart_complete(काष्ठा urb *urb);

#पूर्ण_अगर
