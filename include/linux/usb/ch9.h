<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file holds USB स्थिरants and काष्ठाures that are needed क्रम
 * USB device APIs.  These are used by the USB device model, which is
 * defined in chapter 9 of the USB 2.0 specअगरication and in the
 * Wireless USB 1.0 (spपढ़ो around).  Linux has several APIs in C that
 * need these:
 *
 * - the host side Linux-USB kernel driver API;
 * - the "usbfs" user space API; and
 * - the Linux "gadget" device/peripheral side driver API.
 *
 * USB 2.0 adds an additional "On The Go" (OTG) mode, which lets प्रणालीs
 * act either as a USB host or as a USB device.  That means the host and
 * device side APIs benefit from working well together.
 *
 * There's also "Wireless USB", using low घातer लघु range radios क्रम
 * peripheral पूर्णांकerconnection but otherwise building on the USB framework.
 *
 * Note all descriptors are declared '__attribute__((packed))' so that:
 *
 * [a] they never get padded, either पूर्णांकernally (USB spec ग_लिखोrs
 *     probably handled that) or बाह्यally;
 *
 * [b] so that accessing bigger-than-a-bytes fields will never
 *     generate bus errors on any platक्रमm, even when the location of
 *     its descriptor inside a bundle isn't "naturally aligned", and
 *
 * [c] क्रम consistency, removing all करोubt even when it appears to
 *     someone that the two other poपूर्णांकs are non-issues क्रम that
 *     particular descriptor type.
 */
#अगर_अघोषित __LINUX_USB_CH9_H
#घोषणा __LINUX_USB_CH9_H

#समावेश <linux/device.h>
#समावेश <uapi/linux/usb/ch9.h>

/* USB 3.2 SuperSpeed Plus phy संकेतing rate generation and lane count */

क्रमागत usb_ssp_rate अणु
	USB_SSP_GEN_UNKNOWN = 0,
	USB_SSP_GEN_2x1,
	USB_SSP_GEN_1x2,
	USB_SSP_GEN_2x2,
पूर्ण;

बाह्य स्थिर अक्षर *usb_ep_type_string(पूर्णांक ep_type);
बाह्य स्थिर अक्षर *usb_speed_string(क्रमागत usb_device_speed speed);
बाह्य क्रमागत usb_device_speed usb_get_maximum_speed(काष्ठा device *dev);
बाह्य क्रमागत usb_ssp_rate usb_get_maximum_ssp_rate(काष्ठा device *dev);
बाह्य स्थिर अक्षर *usb_state_string(क्रमागत usb_device_state state);
अचिन्हित पूर्णांक usb_decode_पूर्णांकerval(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd,
				 क्रमागत usb_device_speed speed);

#अगर_घोषित CONFIG_TRACING
बाह्य स्थिर अक्षर *usb_decode_ctrl(अक्षर *str, माप_प्रकार size, __u8 bRequestType,
				   __u8 bRequest, __u16 wValue, __u16 wIndex,
				   __u16 wLength);
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_CH9_H */
