<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common USB debugging functions
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/usb/ch9.h>

अटल व्योम usb_decode_get_status(__u8 bRequestType, __u16 wIndex,
				  __u16 wLength, अक्षर *str, माप_प्रकार size)
अणु
	चयन (bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		snम_लिखो(str, size, "Get Device Status(Length = %d)", wLength);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		snम_लिखो(str, size,
			 "Get Interface Status(Intf = %d, Length = %d)",
			 wIndex, wLength);
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		snम_लिखो(str, size, "Get Endpoint Status(ep%d%s)",
			 wIndex & ~USB_सूची_IN,
			 wIndex & USB_सूची_IN ? "in" : "out");
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *usb_decode_device_feature(u16 wValue)
अणु
	चयन (wValue) अणु
	हाल USB_DEVICE_SELF_POWERED:
		वापस "Self Powered";
	हाल USB_DEVICE_REMOTE_WAKEUP:
		वापस "Remote Wakeup";
	हाल USB_DEVICE_TEST_MODE:
		वापस "Test Mode";
	हाल USB_DEVICE_U1_ENABLE:
		वापस "U1 Enable";
	हाल USB_DEVICE_U2_ENABLE:
		वापस "U2 Enable";
	हाल USB_DEVICE_LTM_ENABLE:
		वापस "LTM Enable";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *usb_decode_test_mode(u16 wIndex)
अणु
	चयन (wIndex) अणु
	हाल USB_TEST_J:
		वापस ": TEST_J";
	हाल USB_TEST_K:
		वापस ": TEST_K";
	हाल USB_TEST_SE0_NAK:
		वापस ": TEST_SE0_NAK";
	हाल USB_TEST_PACKET:
		वापस ": TEST_PACKET";
	हाल USB_TEST_FORCE_ENABLE:
		वापस ": TEST_FORCE_EN";
	शेष:
		वापस ": UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम usb_decode_set_clear_feature(__u8 bRequestType,
					 __u8 bRequest, __u16 wValue,
					 __u16 wIndex, अक्षर *str, माप_प्रकार size)
अणु
	चयन (bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		snम_लिखो(str, size, "%s Device Feature(%s%s)",
			 bRequest == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			 usb_decode_device_feature(wValue),
			 wValue == USB_DEVICE_TEST_MODE ?
			 usb_decode_test_mode(wIndex) : "");
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		snम_लिखो(str, size, "%s Interface Feature(%s)",
			 bRequest == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			 wValue == USB_INTRF_FUNC_SUSPEND ?
			 "Function Suspend" : "UNKNOWN");
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		snम_लिखो(str, size, "%s Endpoint Feature(%s ep%d%s)",
			 bRequest == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			 wValue == USB_ENDPOINT_HALT ? "Halt" : "UNKNOWN",
			 wIndex & ~USB_सूची_IN,
			 wIndex & USB_सूची_IN ? "in" : "out");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम usb_decode_set_address(__u16 wValue, अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Set Address(Addr = %02x)", wValue);
पूर्ण

अटल व्योम usb_decode_get_set_descriptor(__u8 bRequestType, __u8 bRequest,
					  __u16 wValue, __u16 wIndex,
					  __u16 wLength, अक्षर *str, माप_प्रकार size)
अणु
	अक्षर *s;

	चयन (wValue >> 8) अणु
	हाल USB_DT_DEVICE:
		s = "Device";
		अवरोध;
	हाल USB_DT_CONFIG:
		s = "Configuration";
		अवरोध;
	हाल USB_DT_STRING:
		s = "String";
		अवरोध;
	हाल USB_DT_INTERFACE:
		s = "Interface";
		अवरोध;
	हाल USB_DT_ENDPOINT:
		s = "Endpoint";
		अवरोध;
	हाल USB_DT_DEVICE_QUALIFIER:
		s = "Device Qualifier";
		अवरोध;
	हाल USB_DT_OTHER_SPEED_CONFIG:
		s = "Other Speed Config";
		अवरोध;
	हाल USB_DT_INTERFACE_POWER:
		s = "Interface Power";
		अवरोध;
	हाल USB_DT_OTG:
		s = "OTG";
		अवरोध;
	हाल USB_DT_DEBUG:
		s = "Debug";
		अवरोध;
	हाल USB_DT_INTERFACE_ASSOCIATION:
		s = "Interface Association";
		अवरोध;
	हाल USB_DT_BOS:
		s = "BOS";
		अवरोध;
	हाल USB_DT_DEVICE_CAPABILITY:
		s = "Device Capability";
		अवरोध;
	हाल USB_DT_PIPE_USAGE:
		s = "Pipe Usage";
		अवरोध;
	हाल USB_DT_SS_ENDPOINT_COMP:
		s = "SS Endpoint Companion";
		अवरोध;
	हाल USB_DT_SSP_ISOC_ENDPOINT_COMP:
		s = "SSP Isochronous Endpoint Companion";
		अवरोध;
	शेष:
		s = "UNKNOWN";
		अवरोध;
	पूर्ण

	snम_लिखो(str, size, "%s %s Descriptor(Index = %d, Length = %d)",
		bRequest == USB_REQ_GET_DESCRIPTOR ? "Get" : "Set",
		s, wValue & 0xff, wLength);
पूर्ण

अटल व्योम usb_decode_get_configuration(__u16 wLength, अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Get Configuration(Length = %d)", wLength);
पूर्ण

अटल व्योम usb_decode_set_configuration(__u8 wValue, अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Set Configuration(Config = %d)", wValue);
पूर्ण

अटल व्योम usb_decode_get_पूर्णांकf(__u16 wIndex, __u16 wLength, अक्षर *str,
				माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Get Interface(Intf = %d, Length = %d)",
		 wIndex, wLength);
पूर्ण

अटल व्योम usb_decode_set_पूर्णांकf(__u8 wValue, __u16 wIndex, अक्षर *str,
				माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Set Interface(Intf = %d, Alt.Setting = %d)",
		 wIndex, wValue);
पूर्ण

अटल व्योम usb_decode_synch_frame(__u16 wIndex, __u16 wLength,
				   अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Synch Frame(Endpoint = %d, Length = %d)",
		 wIndex, wLength);
पूर्ण

अटल व्योम usb_decode_set_sel(__u16 wLength, अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Set SEL(Length = %d)", wLength);
पूर्ण

अटल व्योम usb_decode_set_isoch_delay(__u8 wValue, अक्षर *str, माप_प्रकार size)
अणु
	snम_लिखो(str, size, "Set Isochronous Delay(Delay = %d ns)", wValue);
पूर्ण

/**
 * usb_decode_ctrl - Returns human पढ़ोable representation of control request.
 * @str: buffer to वापस a human-पढ़ोable representation of control request.
 *       This buffer should have about 200 bytes.
 * @size: size of str buffer.
 * @bRequestType: matches the USB bmRequestType field
 * @bRequest: matches the USB bRequest field
 * @wValue: matches the USB wValue field (CPU byte order)
 * @wIndex: matches the USB wIndex field (CPU byte order)
 * @wLength: matches the USB wLength field (CPU byte order)
 *
 * Function वापसs decoded, क्रमmatted and human-पढ़ोable description of
 * control request packet.
 *
 * The usage scenario क्रम this is क्रम tracepoपूर्णांकs, so function as a वापस
 * use the same value as in parameters. This approach allows to use this
 * function in TP_prपूर्णांकk
 *
 * Important: wValue, wIndex, wLength parameters beक्रमe invoking this function
 * should be processed by le16_to_cpu macro.
 */
स्थिर अक्षर *usb_decode_ctrl(अक्षर *str, माप_प्रकार size, __u8 bRequestType,
			    __u8 bRequest, __u16 wValue, __u16 wIndex,
			    __u16 wLength)
अणु
	चयन (bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		usb_decode_get_status(bRequestType, wIndex, wLength, str, size);
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		usb_decode_set_clear_feature(bRequestType, bRequest, wValue,
					     wIndex, str, size);
		अवरोध;
	हाल USB_REQ_SET_ADDRESS:
		usb_decode_set_address(wValue, str, size);
		अवरोध;
	हाल USB_REQ_GET_DESCRIPTOR:
	हाल USB_REQ_SET_DESCRIPTOR:
		usb_decode_get_set_descriptor(bRequestType, bRequest, wValue,
					      wIndex, wLength, str, size);
		अवरोध;
	हाल USB_REQ_GET_CONFIGURATION:
		usb_decode_get_configuration(wLength, str, size);
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		usb_decode_set_configuration(wValue, str, size);
		अवरोध;
	हाल USB_REQ_GET_INTERFACE:
		usb_decode_get_पूर्णांकf(wIndex, wLength, str, size);
		अवरोध;
	हाल USB_REQ_SET_INTERFACE:
		usb_decode_set_पूर्णांकf(wValue, wIndex, str, size);
		अवरोध;
	हाल USB_REQ_SYNCH_FRAME:
		usb_decode_synch_frame(wIndex, wLength, str, size);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		usb_decode_set_sel(wLength, str, size);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		usb_decode_set_isoch_delay(wValue, str, size);
		अवरोध;
	शेष:
		snम_लिखो(str, size, "%02x %02x %02x %02x %02x %02x %02x %02x",
			 bRequestType, bRequest,
			 (u8)(cpu_to_le16(wValue) & 0xff),
			 (u8)(cpu_to_le16(wValue) >> 8),
			 (u8)(cpu_to_le16(wIndex) & 0xff),
			 (u8)(cpu_to_le16(wIndex) >> 8),
			 (u8)(cpu_to_le16(wLength) & 0xff),
			 (u8)(cpu_to_le16(wLength) >> 8));
	पूर्ण

	वापस str;
पूर्ण
EXPORT_SYMBOL_GPL(usb_decode_ctrl);
