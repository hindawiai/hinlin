<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Gembird Joypad, "PC Game Controller"
 *
 *  Copyright (c) 2015 Red Hat, Inc
 *  Copyright (c) 2015 Benjamin Tissoires
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा GEMBIRD_START_FAULTY_RDESC	8

अटल स्थिर __u8 gembird_jpd_faulty_rdesc[] = अणु
	0x75, 0x08,			/*   Report Size (8)		*/
	0x95, 0x05,			/*   Report Count (5)		*/
	0x15, 0x00,			/*   Logical Minimum (0)	*/
	0x26, 0xff, 0x00,		/*   Logical Maximum (255)	*/
	0x35, 0x00,			/*   Physical Minimum (0)	*/
	0x46, 0xff, 0x00,		/*   Physical Maximum (255)	*/
	0x09, 0x30,			/*   Usage (X)			*/
	0x09, 0x31,			/*   Usage (Y)			*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x09, 0x35,			/*   Usage (Rz)			*/
	0x81, 0x02,			/*   Input (Data,Var,Abs)	*/
पूर्ण;

/*
 * we fix the report descriptor by:
 * - marking the first Z axis as स्थिरant (so it is ignored by HID)
 * - assign the original second Z to Rx
 * - assign the original Rz to Ry
 */
अटल स्थिर __u8 gembird_jpd_fixed_rdesc[] = अणु
	0x75, 0x08,			/*   Report Size (8)		*/
	0x95, 0x02,			/*   Report Count (2)		*/
	0x15, 0x00,			/*   Logical Minimum (0)	*/
	0x26, 0xff, 0x00,		/*   Logical Maximum (255)	*/
	0x35, 0x00,			/*   Physical Minimum (0)	*/
	0x46, 0xff, 0x00,		/*   Physical Maximum (255)	*/
	0x09, 0x30,			/*   Usage (X)			*/
	0x09, 0x31,			/*   Usage (Y)			*/
	0x81, 0x02,			/*   Input (Data,Var,Abs)	*/
	0x95, 0x01,			/*   Report Count (1)		*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x81, 0x01,			/*   Input (Cnst,Arr,Abs)	*/
	0x95, 0x02,			/*   Report Count (2)		*/
	0x09, 0x33,			/*   Usage (Rx)			*/
	0x09, 0x34,			/*   Usage (Ry)			*/
	0x81, 0x02,			/*   Input (Data,Var,Abs)	*/
पूर्ण;

अटल __u8 *gembird_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	__u8 *new_rdesc;
	/* delta_size is > 0 */
	माप_प्रकार delta_size = माप(gembird_jpd_fixed_rdesc) -
			    माप(gembird_jpd_faulty_rdesc);
	माप_प्रकार new_size = *rsize + delta_size;

	अगर (*rsize >= 31 && !स_भेद(&rdesc[GEMBIRD_START_FAULTY_RDESC],
				    gembird_jpd_faulty_rdesc,
				    माप(gembird_jpd_faulty_rdesc))) अणु
		new_rdesc = devm_kzalloc(&hdev->dev, new_size, GFP_KERNEL);
		अगर (new_rdesc == शून्य)
			वापस rdesc;

		dev_info(&hdev->dev,
			 "fixing Gembird JPD-DualForce 2 report descriptor.\n");

		/* start by copying the end of the rdesc */
		स_नकल(new_rdesc + delta_size, rdesc, *rsize);

		/* add the correct beginning */
		स_नकल(new_rdesc, rdesc, GEMBIRD_START_FAULTY_RDESC);

		/* replace the faulty part with the fixed one */
		स_नकल(new_rdesc + GEMBIRD_START_FAULTY_RDESC,
		       gembird_jpd_fixed_rdesc,
		       माप(gembird_jpd_fixed_rdesc));

		*rsize = new_size;
		rdesc = new_rdesc;
	पूर्ण

	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id gembird_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GEMBIRD,
			 USB_DEVICE_ID_GEMBIRD_JPD_DUALFORCE2) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, gembird_devices);

अटल काष्ठा hid_driver gembird_driver = अणु
	.name = "gembird",
	.id_table = gembird_devices,
	.report_fixup = gembird_report_fixup,
पूर्ण;
module_hid_driver(gembird_driver);

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_DESCRIPTION("HID Gembird joypad driver");
MODULE_LICENSE("GPL");
