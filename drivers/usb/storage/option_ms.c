<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Option High Speed Mobile Devices.
 *
 *   (c) 2008 Dan Williams <dcbw@redhat.com>
 *
 * Inspiration taken from sierra_ms.c by Kevin Lloyd <klloyd@sierrawireless.com>
 */

#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "option_ms.h"
#समावेश "debug.h"

#घोषणा ZCD_FORCE_MODEM			0x01
#घोषणा ZCD_ALLOW_MS 			0x02

अटल अचिन्हित पूर्णांक option_zero_cd = ZCD_FORCE_MODEM;
module_param(option_zero_cd, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(option_zero_cd, "ZeroCD mode (1=Force Modem (default),"
		 " 2=Allow CD-Rom");

#घोषणा RESPONSE_LEN 1024

अटल पूर्णांक option_rezero(काष्ठा us_data *us)
अणु
	अटल स्थिर अचिन्हित अक्षर rezero_msg[] = अणु
	  0x55, 0x53, 0x42, 0x43, 0x78, 0x56, 0x34, 0x12,
	  0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x06, 0x01,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अक्षर *buffer;
	पूर्णांक result;

	usb_stor_dbg(us, "Option MS: %s\n", "DEVICE MODE SWITCH");

	buffer = kzalloc(RESPONSE_LEN, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_नकल(buffer, rezero_msg, माप(rezero_msg));
	result = usb_stor_bulk_transfer_buf(us,
			us->send_bulk_pipe,
			buffer, माप(rezero_msg), शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		result = USB_STOR_XFER_ERROR;
		जाओ out;
	पूर्ण

	/*
	 * Some of the devices need to be asked क्रम a response, but we करोn't
	 * care what that response is.
	 */
	usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, RESPONSE_LEN, शून्य);

	/* Read the CSW */
	usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, 13, शून्य);

	result = USB_STOR_XFER_GOOD;

out:
	kमुक्त(buffer);
	वापस result;
पूर्ण

अटल पूर्णांक option_inquiry(काष्ठा us_data *us)
अणु
	अटल स्थिर अचिन्हित अक्षर inquiry_msg[] = अणु
	  0x55, 0x53, 0x42, 0x43, 0x12, 0x34, 0x56, 0x78,
	  0x24, 0x00, 0x00, 0x00, 0x80, 0x00, 0x06, 0x12,
	  0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	अक्षर *buffer;
	पूर्णांक result;

	usb_stor_dbg(us, "Option MS: %s\n", "device inquiry for vendor name");

	buffer = kzalloc(0x24, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस USB_STOR_TRANSPORT_ERROR;

	स_नकल(buffer, inquiry_msg, माप(inquiry_msg));
	result = usb_stor_bulk_transfer_buf(us,
			us->send_bulk_pipe,
			buffer, माप(inquiry_msg), शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		result = USB_STOR_XFER_ERROR;
		जाओ out;
	पूर्ण

	result = usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, 0x24, शून्य);
	अगर (result != USB_STOR_XFER_GOOD) अणु
		result = USB_STOR_XFER_ERROR;
		जाओ out;
	पूर्ण

	result = स_भेद(buffer+8, "Option", 6);

	अगर (result != 0)
		result = स_भेद(buffer+8, "ZCOPTION", 8);

	/* Read the CSW */
	usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, 13, शून्य);

out:
	kमुक्त(buffer);
	वापस result;
पूर्ण


पूर्णांक option_ms_init(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	usb_stor_dbg(us, "Option MS: %s\n", "option_ms_init called");

	/*
	 * Additional test क्रम venकरोr inक्रमmation via INQUIRY,
	 * because some venकरोr/product IDs are ambiguous
	 */
	result = option_inquiry(us);
	अगर (result != 0) अणु
		usb_stor_dbg(us, "Option MS: %s\n",
			     "vendor is not Option or not determinable, no action taken");
		वापस 0;
	पूर्ण अन्यथा
		usb_stor_dbg(us, "Option MS: %s\n",
			     "this is a genuine Option device, proceeding");

	/* Force Modem mode */
	अगर (option_zero_cd == ZCD_FORCE_MODEM) अणु
		usb_stor_dbg(us, "Option MS: %s\n", "Forcing Modem Mode");
		result = option_rezero(us);
		अगर (result != USB_STOR_XFER_GOOD)
			usb_stor_dbg(us, "Option MS: %s\n",
				     "Failed to switch to modem mode");
		वापस -EIO;
	पूर्ण अन्यथा अगर (option_zero_cd == ZCD_ALLOW_MS) अणु
		/* Allow Mass Storage mode (keep CD-Rom) */
		usb_stor_dbg(us, "Option MS: %s\n",
			     "Allowing Mass Storage Mode if device requests it");
	पूर्ण

	वापस 0;
पूर्ण

