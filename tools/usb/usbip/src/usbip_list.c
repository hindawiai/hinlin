<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <sys/types.h>
#समावेश <libudev.h>

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <getopt.h>
#समावेश <netdb.h>
#समावेश <unistd.h>

#समावेश <dirent.h>

#समावेश <linux/usb/ch9.h>

#समावेश "usbip_common.h"
#समावेश "usbip_network.h"
#समावेश "usbip.h"

अटल स्थिर अक्षर usbip_list_usage_string[] =
	"usbip list [-p|--parsable] <args>\n"
	"    -p, --parsable         Parsable list format\n"
	"    -r, --remote=<host>    List the exportable USB devices on <host>\n"
	"    -l, --local            List the local USB devices\n"
	"    -d, --device           List the local USB gadgets bound to usbip-vudc\n";

व्योम usbip_list_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_list_usage_string);
पूर्ण

अटल पूर्णांक get_exported_devices(अक्षर *host, पूर्णांक sockfd)
अणु
	अक्षर product_name[100];
	अक्षर class_name[100];
	काष्ठा op_devlist_reply reply;
	uपूर्णांक16_t code = OP_REP_DEVLIST;
	काष्ठा usbip_usb_device udev;
	काष्ठा usbip_usb_पूर्णांकerface uपूर्णांकf;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc, j;
	पूर्णांक status;

	rc = usbip_net_send_op_common(sockfd, OP_REQ_DEVLIST, 0);
	अगर (rc < 0) अणु
		dbg("usbip_net_send_op_common failed");
		वापस -1;
	पूर्ण

	rc = usbip_net_recv_op_common(sockfd, &code, &status);
	अगर (rc < 0) अणु
		err("Exported Device List Request failed - %s\n",
		    usbip_op_common_status_string(status));
		वापस -1;
	पूर्ण

	स_रखो(&reply, 0, माप(reply));
	rc = usbip_net_recv(sockfd, &reply, माप(reply));
	अगर (rc < 0) अणु
		dbg("usbip_net_recv_op_devlist failed");
		वापस -1;
	पूर्ण
	PACK_OP_DEVLIST_REPLY(0, &reply);
	dbg("exportable devices: %d\n", reply.ndev);

	अगर (reply.ndev == 0) अणु
		info("no exportable devices found on %s", host);
		वापस 0;
	पूर्ण

	म_लिखो("Exportable USB devices\n");
	म_लिखो("======================\n");
	म_लिखो(" - %s\n", host);

	क्रम (i = 0; i < reply.ndev; i++) अणु
		स_रखो(&udev, 0, माप(udev));
		rc = usbip_net_recv(sockfd, &udev, माप(udev));
		अगर (rc < 0) अणु
			dbg("usbip_net_recv failed: usbip_usb_device[%d]", i);
			वापस -1;
		पूर्ण
		usbip_net_pack_usb_device(0, &udev);

		usbip_names_get_product(product_name, माप(product_name),
					udev.idVenकरोr, udev.idProduct);
		usbip_names_get_class(class_name, माप(class_name),
				      udev.bDeviceClass, udev.bDeviceSubClass,
				      udev.bDeviceProtocol);
		म_लिखो("%11s: %s\n", udev.busid, product_name);
		म_लिखो("%11s: %s\n", "", udev.path);
		म_लिखो("%11s: %s\n", "", class_name);

		क्रम (j = 0; j < udev.bNumInterfaces; j++) अणु
			rc = usbip_net_recv(sockfd, &uपूर्णांकf, माप(uपूर्णांकf));
			अगर (rc < 0) अणु
				err("usbip_net_recv failed: usbip_usb_intf[%d]",
						j);

				वापस -1;
			पूर्ण
			usbip_net_pack_usb_पूर्णांकerface(0, &uपूर्णांकf);

			usbip_names_get_class(class_name, माप(class_name),
					uपूर्णांकf.bInterfaceClass,
					uपूर्णांकf.bInterfaceSubClass,
					uपूर्णांकf.bInterfaceProtocol);
			म_लिखो("%11s: %2d - %s\n", "", j, class_name);
		पूर्ण

		म_लिखो("\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक list_exported_devices(अक्षर *host)
अणु
	पूर्णांक rc;
	पूर्णांक sockfd;

	sockfd = usbip_net_tcp_connect(host, usbip_port_string);
	अगर (sockfd < 0) अणु
		err("could not connect to %s:%s: %s", host,
		    usbip_port_string, gai_म_त्रुटि(sockfd));
		वापस -1;
	पूर्ण
	dbg("connected to %s:%s", host, usbip_port_string);

	rc = get_exported_devices(host, sockfd);
	अगर (rc < 0) अणु
		err("failed to get device list from %s", host);
		वापस -1;
	पूर्ण

	बंद(sockfd);

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_device(स्थिर अक्षर *busid, स्थिर अक्षर *venकरोr,
			 स्थिर अक्षर *product, bool parsable)
अणु
	अगर (parsable)
		म_लिखो("busid=%s#usbid=%.4s:%.4s#", busid, venकरोr, product);
	अन्यथा
		म_लिखो(" - busid %s (%.4s:%.4s)\n", busid, venकरोr, product);
पूर्ण

अटल व्योम prपूर्णांक_product_name(अक्षर *product_name, bool parsable)
अणु
	अगर (!parsable)
		म_लिखो("   %s\n", product_name);
पूर्ण

अटल पूर्णांक list_devices(bool parsable)
अणु
	काष्ठा udev *udev;
	काष्ठा udev_क्रमागतerate *क्रमागतerate;
	काष्ठा udev_list_entry *devices, *dev_list_entry;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *path;
	स्थिर अक्षर *idVenकरोr;
	स्थिर अक्षर *idProduct;
	स्थिर अक्षर *bConfValue;
	स्थिर अक्षर *bNumIntfs;
	स्थिर अक्षर *busid;
	अक्षर product_name[128];
	पूर्णांक ret = -1;
	स्थिर अक्षर *devpath;

	/* Create libudev context. */
	udev = udev_new();

	/* Create libudev device क्रमागतeration. */
	क्रमागतerate = udev_क्रमागतerate_new(udev);

	/* Take only USB devices that are not hubs and करो not have
	 * the bInterfaceNumber attribute, i.e. are not पूर्णांकerfaces.
	 */
	udev_क्रमागतerate_add_match_subप्रणाली(क्रमागतerate, "usb");
	udev_क्रमागतerate_add_nomatch_sysattr(क्रमागतerate, "bDeviceClass", "09");
	udev_क्रमागतerate_add_nomatch_sysattr(क्रमागतerate, "bInterfaceNumber", शून्य);
	udev_क्रमागतerate_scan_devices(क्रमागतerate);

	devices = udev_क्रमागतerate_get_list_entry(क्रमागतerate);

	/* Show inक्रमmation about each device. */
	udev_list_entry_क्रमeach(dev_list_entry, devices) अणु
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		/* Ignore devices attached to vhci_hcd */
		devpath = udev_device_get_devpath(dev);
		अगर (म_माला(devpath, USBIP_VHCI_DRV_NAME)) अणु
			dbg("Skip the device %s already attached to %s\n",
			    devpath, USBIP_VHCI_DRV_NAME);
			जारी;
		पूर्ण

		/* Get device inक्रमmation. */
		idVenकरोr = udev_device_get_sysattr_value(dev, "idVendor");
		idProduct = udev_device_get_sysattr_value(dev, "idProduct");
		bConfValue = udev_device_get_sysattr_value(dev,
				"bConfigurationValue");
		bNumIntfs = udev_device_get_sysattr_value(dev,
				"bNumInterfaces");
		busid = udev_device_get_sysname(dev);
		अगर (!idVenकरोr || !idProduct || !bConfValue || !bNumIntfs) अणु
			err("problem getting device attributes: %s",
			    म_त्रुटि(त्रुटि_सं));
			जाओ err_out;
		पूर्ण

		/* Get product name. */
		usbip_names_get_product(product_name, माप(product_name),
					म_से_दीर्घ(idVenकरोr, शून्य, 16),
					म_से_दीर्घ(idProduct, शून्य, 16));

		/* Prपूर्णांक inक्रमmation. */
		prपूर्णांक_device(busid, idVenकरोr, idProduct, parsable);
		prपूर्णांक_product_name(product_name, parsable);

		म_लिखो("\n");

		udev_device_unref(dev);
	पूर्ण

	ret = 0;

err_out:
	udev_क्रमागतerate_unref(क्रमागतerate);
	udev_unref(udev);

	वापस ret;
पूर्ण

अटल पूर्णांक list_gadget_devices(bool parsable)
अणु
	पूर्णांक ret = -1;
	काष्ठा udev *udev;
	काष्ठा udev_क्रमागतerate *क्रमागतerate;
	काष्ठा udev_list_entry *devices, *dev_list_entry;
	काष्ठा udev_device *dev;
	स्थिर अक्षर *path;
	स्थिर अक्षर *driver;

	स्थिर काष्ठा usb_device_descriptor *d_desc;
	स्थिर अक्षर *descriptors;
	अक्षर product_name[128];

	uपूर्णांक16_t idVenकरोr;
	अक्षर idVenकरोr_buf[8];
	uपूर्णांक16_t idProduct;
	अक्षर idProduct_buf[8];
	स्थिर अक्षर *busid;

	udev = udev_new();
	क्रमागतerate = udev_क्रमागतerate_new(udev);

	udev_क्रमागतerate_add_match_subप्रणाली(क्रमागतerate, "platform");

	udev_क्रमागतerate_scan_devices(क्रमागतerate);
	devices = udev_क्रमागतerate_get_list_entry(क्रमागतerate);

	udev_list_entry_क्रमeach(dev_list_entry, devices) अणु
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);

		driver = udev_device_get_driver(dev);
		/* We only have mechanism to क्रमागतerate gadमाला_लो bound to vudc */
		अगर (driver == शून्य || म_भेद(driver, USBIP_DEVICE_DRV_NAME))
			जारी;

		/* Get device inक्रमmation. */
		descriptors = udev_device_get_sysattr_value(dev,
				VUDC_DEVICE_DESCR_खाता);

		अगर (!descriptors) अणु
			err("problem getting device attributes: %s",
			    म_त्रुटि(त्रुटि_सं));
			जाओ err_out;
		पूर्ण

		d_desc = (स्थिर काष्ठा usb_device_descriptor *) descriptors;

		idVenकरोr = le16toh(d_desc->idVenकरोr);
		प्र_लिखो(idVenकरोr_buf, "0x%4x", idVenकरोr);
		idProduct = le16toh(d_desc->idProduct);
		प्र_लिखो(idProduct_buf, "0x%4x", idVenकरोr);
		busid = udev_device_get_sysname(dev);

		/* Get product name. */
		usbip_names_get_product(product_name, माप(product_name),
					le16toh(idVenकरोr),
					le16toh(idProduct));

		/* Prपूर्णांक inक्रमmation. */
		prपूर्णांक_device(busid, idVenकरोr_buf, idProduct_buf, parsable);
		prपूर्णांक_product_name(product_name, parsable);

		म_लिखो("\n");

		udev_device_unref(dev);
	पूर्ण
	ret = 0;

err_out:
	udev_क्रमागतerate_unref(क्रमागतerate);
	udev_unref(udev);

	वापस ret;
पूर्ण

पूर्णांक usbip_list(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option opts[] = अणु
		अणु "parsable", no_argument,       शून्य, 'p' पूर्ण,
		अणु "remote",   required_argument, शून्य, 'r' पूर्ण,
		अणु "local",    no_argument,       शून्य, 'l' पूर्ण,
		अणु "device",    no_argument,       शून्य, 'd' पूर्ण,
		अणु शून्य,       0,                 शून्य,  0  पूर्ण
	पूर्ण;

	bool parsable = false;
	पूर्णांक opt;
	पूर्णांक ret = -1;

	अगर (usbip_names_init(USBIDS_खाता))
		err("failed to open %s", USBIDS_खाता);

	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "pr:ld", opts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'p':
			parsable = true;
			अवरोध;
		हाल 'r':
			ret = list_exported_devices(optarg);
			जाओ out;
		हाल 'l':
			ret = list_devices(parsable);
			जाओ out;
		हाल 'd':
			ret = list_gadget_devices(parsable);
			जाओ out;
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

err_out:
	usbip_list_usage();
out:
	usbip_names_मुक्त();

	वापस ret;
पूर्ण
