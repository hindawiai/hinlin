<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश "vhci_driver.h"
#समावेश "usbip_common.h"

अटल पूर्णांक list_imported_devices(व्योम)
अणु
	पूर्णांक i;
	काष्ठा usbip_imported_device *idev;
	पूर्णांक ret;

	अगर (usbip_names_init(USBIDS_खाता))
		err("failed to open %s", USBIDS_खाता);

	ret = usbip_vhci_driver_खोलो();
	अगर (ret < 0) अणु
		err("open vhci_driver");
		जाओ err_names_मुक्त;
	पूर्ण

	म_लिखो("Imported USB devices\n");
	म_लिखो("====================\n");

	क्रम (i = 0; i < vhci_driver->nports; i++) अणु
		idev = &vhci_driver->idev[i];

		अगर (usbip_vhci_imported_device_dump(idev) < 0)
			जाओ err_driver_बंद;
	पूर्ण

	usbip_vhci_driver_बंद();
	usbip_names_मुक्त();

	वापस ret;

err_driver_बंद:
	usbip_vhci_driver_बंद();
err_names_मुक्त:
	usbip_names_मुक्त();
	वापस -1;
पूर्ण

पूर्णांक usbip_port_show(__attribute__((unused)) पूर्णांक argc,
		    __attribute__((unused)) अक्षर *argv[])
अणु
	पूर्णांक ret;

	ret = list_imported_devices();
	अगर (ret < 0)
		err("list imported devices");

	वापस ret;
पूर्ण
