<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <प्रकार.स>
#समावेश <सीमा.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <getopt.h>
#समावेश <unistd.h>

#समावेश "vhci_driver.h"
#समावेश "usbip_common.h"
#समावेश "usbip_network.h"
#समावेश "usbip.h"

अटल स्थिर अक्षर usbip_detach_usage_string[] =
	"usbip detach <args>\n"
	"    -p, --port=<port>    " USBIP_VHCI_DRV_NAME
	" port the device is on\n";

व्योम usbip_detach_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_detach_usage_string);
पूर्ण

अटल पूर्णांक detach_port(अक्षर *port)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक8_t portnum;
	अक्षर path[PATH_MAX+1];
	पूर्णांक i;
	काष्ठा usbip_imported_device *idev;
	पूर्णांक found = 0;

	अचिन्हित पूर्णांक port_len = म_माप(port);

	क्रम (अचिन्हित पूर्णांक i = 0; i < port_len; i++)
		अगर (!है_अंक(port[i])) अणु
			err("invalid port %s", port);
			वापस -1;
		पूर्ण

	portnum = म_से_प(port);

	ret = usbip_vhci_driver_खोलो();
	अगर (ret < 0) अणु
		err("open vhci_driver");
		वापस -1;
	पूर्ण

	/* check क्रम invalid port */
	क्रम (i = 0; i < vhci_driver->nports; i++) अणु
		idev = &vhci_driver->idev[i];

		अगर (idev->port == portnum) अणु
			found = 1;
			अगर (idev->status != VDEV_ST_शून्य)
				अवरोध;
			info("Port %d is already detached!\n", idev->port);
			जाओ call_driver_बंद;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		err("Invalid port %s > maxports %d",
			port, vhci_driver->nports);
		जाओ call_driver_बंद;
	पूर्ण

	/* हटाओ the port state file */
	snम_लिखो(path, PATH_MAX, VHCI_STATE_PATH"/port%d", portnum);

	हटाओ(path);
	सूची_हटाओ(VHCI_STATE_PATH);

	ret = usbip_vhci_detach_device(portnum);
	अगर (ret < 0) अणु
		ret = -1;
		err("Port %d detach request failed!\n", portnum);
		जाओ call_driver_बंद;
	पूर्ण
	info("Port %d is now detached!\n", portnum);

call_driver_बंद:
	usbip_vhci_driver_बंद();

	वापस ret;
पूर्ण

पूर्णांक usbip_detach(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option opts[] = अणु
		अणु "port", required_argument, शून्य, 'p' पूर्ण,
		अणु शून्य, 0, शून्य, 0 पूर्ण
	पूर्ण;
	पूर्णांक opt;
	पूर्णांक ret = -1;

	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "p:", opts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'p':
			ret = detach_port(optarg);
			जाओ out;
		शेष:
			जाओ err_out;
		पूर्ण
	पूर्ण

err_out:
	usbip_detach_usage();
out:
	वापस ret;
पूर्ण
