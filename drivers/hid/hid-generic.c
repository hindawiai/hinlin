<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID support क्रम Linux
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2007-2008 Oliver Neukum
 *  Copyright (c) 2006-2012 Jiri Kosina
 *  Copyright (c) 2012 Henrik Rydberg
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/hid.h>

अटल काष्ठा hid_driver hid_generic;

अटल पूर्णांक __check_hid_generic(काष्ठा device_driver *drv, व्योम *data)
अणु
	काष्ठा hid_driver *hdrv = to_hid_driver(drv);
	काष्ठा hid_device *hdev = data;

	अगर (hdrv == &hid_generic)
		वापस 0;

	वापस hid_match_device(hdev, hdrv) != शून्य;
पूर्ण

अटल bool hid_generic_match(काष्ठा hid_device *hdev,
			      bool ignore_special_driver)
अणु
	अगर (ignore_special_driver)
		वापस true;

	अगर (hdev->quirks & HID_QUIRK_HAVE_SPECIAL_DRIVER)
		वापस false;

	/*
	 * If any other driver wants the device, leave the device to this other
	 * driver.
	 */
	अगर (bus_क्रम_each_drv(&hid_bus_type, शून्य, hdev, __check_hid_generic))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hid_generic_probe(काष्ठा hid_device *hdev,
			     स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
पूर्ण

अटल स्थिर काष्ठा hid_device_id hid_table[] = अणु
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY, HID_ANY_ID, HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, hid_table);

अटल काष्ठा hid_driver hid_generic = अणु
	.name = "hid-generic",
	.id_table = hid_table,
	.match = hid_generic_match,
	.probe = hid_generic_probe,
पूर्ण;
module_hid_driver(hid_generic);

MODULE_AUTHOR("Henrik Rydberg");
MODULE_DESCRIPTION("HID generic driver");
MODULE_LICENSE("GPL");
