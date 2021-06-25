<शैली गुरु>
/*
 * This file defines the USB अक्षरger type and state that are needed क्रम
 * USB device APIs.
 */

#अगर_अघोषित _UAPI__LINUX_USB_CHARGER_H
#घोषणा _UAPI__LINUX_USB_CHARGER_H

/*
 * USB अक्षरger type:
 * SDP (Standard Downstream Port)
 * DCP (Dedicated Charging Port)
 * CDP (Charging Downstream Port)
 * ACA (Accessory Charger Adapters)
 */
क्रमागत usb_अक्षरger_type अणु
	UNKNOWN_TYPE = 0,
	SDP_TYPE = 1,
	DCP_TYPE = 2,
	CDP_TYPE = 3,
	ACA_TYPE = 4,
पूर्ण;

/* USB अक्षरger state */
क्रमागत usb_अक्षरger_state अणु
	USB_CHARGER_DEFAULT = 0,
	USB_CHARGER_PRESENT = 1,
	USB_CHARGER_ABSENT = 2,
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_USB_CHARGER_H */
