<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#समावेश "usbip_common.h"
#समावेश "vhci_driver.h"
#समावेश <सीमा.स>
#समावेश <netdb.h>
#समावेश <libudev.h>
#समावेश <dirent.h>
#समावेश "sysfs_utils.h"

#अघोषित  PROGNAME
#घोषणा PROGNAME "libusbip"

काष्ठा usbip_vhci_driver *vhci_driver;
काष्ठा udev *udev_context;

अटल काष्ठा usbip_imported_device *
imported_device_init(काष्ठा usbip_imported_device *idev, अक्षर *busid)
अणु
	काष्ठा udev_device *sudev;

	sudev = udev_device_new_from_subप्रणाली_sysname(udev_context,
						       "usb", busid);
	अगर (!sudev) अणु
		dbg("udev_device_new_from_subsystem_sysname failed: %s", busid);
		जाओ err;
	पूर्ण
	पढ़ो_usb_device(sudev, &idev->udev);
	udev_device_unref(sudev);

	वापस idev;

err:
	वापस शून्य;
पूर्ण

अटल पूर्णांक parse_status(स्थिर अक्षर *value)
अणु
	पूर्णांक ret = 0;
	अक्षर *c;

	/* skip a header line */
	c = म_अक्षर(value, '\n');
	अगर (!c)
		वापस -1;
	c++;

	जबतक (*c != '\0') अणु
		पूर्णांक port, status, speed, devid;
		पूर्णांक sockfd;
		अक्षर lbusid[SYSFS_BUS_ID_SIZE];
		काष्ठा usbip_imported_device *idev;
		अक्षर hub[3];

		ret = माला_पूछो(c, "%2s  %d %d %d %x %u %31s\n",
				hub, &port, &status, &speed,
				&devid, &sockfd, lbusid);

		अगर (ret < 5) अणु
			dbg("sscanf failed: %d", ret);
			BUG();
		पूर्ण

		dbg("hub %s port %d status %d speed %d devid %x",
				hub, port, status, speed, devid);
		dbg("sockfd %u lbusid %s", sockfd, lbusid);

		/* अगर a device is connected, look at it */
		idev = &vhci_driver->idev[port];
		स_रखो(idev, 0, माप(*idev));

		अगर (म_भेदन("hs", hub, 2) == 0)
			idev->hub = HUB_SPEED_HIGH;
		अन्यथा /* म_भेदन("ss", hub, 2) == 0 */
			idev->hub = HUB_SPEED_SUPER;

		idev->port	= port;
		idev->status	= status;

		idev->devid	= devid;

		idev->busnum	= (devid >> 16);
		idev->devnum	= (devid & 0x0000ffff);

		अगर (idev->status != VDEV_ST_शून्य
		    && idev->status != VDEV_ST_NOTASSIGNED) अणु
			idev = imported_device_init(idev, lbusid);
			अगर (!idev) अणु
				dbg("imported_device_init failed");
				वापस -1;
			पूर्ण
		पूर्ण

		/* go to the next line */
		c = म_अक्षर(c, '\n');
		अगर (!c)
			अवरोध;
		c++;
	पूर्ण

	dbg("exit");

	वापस 0;
पूर्ण

#घोषणा MAX_STATUS_NAME 18

अटल पूर्णांक refresh_imported_device_list(व्योम)
अणु
	स्थिर अक्षर *attr_status;
	अक्षर status[MAX_STATUS_NAME+1] = "status";
	पूर्णांक i, ret;

	क्रम (i = 0; i < vhci_driver->ncontrollers; i++) अणु
		अगर (i > 0)
			snम_लिखो(status, माप(status), "status.%d", i);

		attr_status = udev_device_get_sysattr_value(vhci_driver->hc_device,
							    status);
		अगर (!attr_status) अणु
			err("udev_device_get_sysattr_value failed");
			वापस -1;
		पूर्ण

		dbg("controller %d", i);

		ret = parse_status(attr_status);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_nports(काष्ठा udev_device *hc_device)
अणु
	स्थिर अक्षर *attr_nports;

	attr_nports = udev_device_get_sysattr_value(hc_device, "nports");
	अगर (!attr_nports) अणु
		err("udev_device_get_sysattr_value nports failed");
		वापस -1;
	पूर्ण

	वापस (पूर्णांक)म_से_अदीर्घ(attr_nports, शून्य, 10);
पूर्ण

अटल पूर्णांक vhci_hcd_filter(स्थिर काष्ठा dirent *dirent)
अणु
	वापस !म_भेदन(dirent->d_name, "vhci_hcd.", 9);
पूर्ण

अटल पूर्णांक get_ncontrollers(व्योम)
अणु
	काष्ठा dirent **namelist;
	काष्ठा udev_device *platक्रमm;
	पूर्णांक n;

	platक्रमm = udev_device_get_parent(vhci_driver->hc_device);
	अगर (platक्रमm == शून्य)
		वापस -1;

	n = scandir(udev_device_get_syspath(platक्रमm), &namelist, vhci_hcd_filter, शून्य);
	अगर (n < 0)
		err("scandir failed");
	अन्यथा अणु
		क्रम (पूर्णांक i = 0; i < n; i++)
			मुक्त(namelist[i]);
		मुक्त(namelist);
	पूर्ण

	वापस n;
पूर्ण

/*
 * Read the given port's record.
 *
 * To aव्योम buffer overflow we will पढ़ो the entire line and
 * validate each part's size. The initial buffer is padded by 4 to
 * accommodate the 2 spaces, 1 newline and an additional अक्षरacter
 * which is needed to properly validate the 3rd part without it being
 * truncated to an acceptable length.
 */
अटल पूर्णांक पढ़ो_record(पूर्णांक rhport, अक्षर *host, अचिन्हित दीर्घ host_len,
		अक्षर *port, अचिन्हित दीर्घ port_len, अक्षर *busid)
अणु
	पूर्णांक part;
	खाता *file;
	अक्षर path[PATH_MAX+1];
	अक्षर *buffer, *start, *end;
	अक्षर delim[] = अणु' ', ' ', '\n'पूर्ण;
	पूर्णांक max_len[] = अणु(पूर्णांक)host_len, (पूर्णांक)port_len, SYSFS_BUS_ID_SIZEपूर्ण;
	माप_प्रकार buffer_len = host_len + port_len + SYSFS_BUS_ID_SIZE + 4;

	buffer = दो_स्मृति(buffer_len);
	अगर (!buffer)
		वापस -1;

	snम_लिखो(path, PATH_MAX, VHCI_STATE_PATH"/port%d", rhport);

	file = ख_खोलो(path, "r");
	अगर (!file) अणु
		err("fopen");
		मुक्त(buffer);
		वापस -1;
	पूर्ण

	अगर (ख_माला_लो(buffer, buffer_len, file) == शून्य) अणु
		err("fgets");
		मुक्त(buffer);
		ख_बंद(file);
		वापस -1;
	पूर्ण
	ख_बंद(file);

	/* validate the length of each of the 3 parts */
	start = buffer;
	क्रम (part = 0; part < 3; part++) अणु
		end = म_अक्षर(start, delim[part]);
		अगर (end == शून्य || (end - start) > max_len[part]) अणु
			मुक्त(buffer);
			वापस -1;
		पूर्ण
		start = end + 1;
	पूर्ण

	अगर (माला_पूछो(buffer, "%s %s %s\n", host, port, busid) != 3) अणु
		err("sscanf");
		मुक्त(buffer);
		वापस -1;
	पूर्ण

	मुक्त(buffer);

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

पूर्णांक usbip_vhci_driver_खोलो(व्योम)
अणु
	पूर्णांक nports;
	काष्ठा udev_device *hc_device;

	udev_context = udev_new();
	अगर (!udev_context) अणु
		err("udev_new failed");
		वापस -1;
	पूर्ण

	/* will be मुक्तd in usbip_driver_बंद() */
	hc_device =
		udev_device_new_from_subप्रणाली_sysname(udev_context,
						       USBIP_VHCI_BUS_TYPE,
						       USBIP_VHCI_DEVICE_NAME);
	अगर (!hc_device) अणु
		err("udev_device_new_from_subsystem_sysname failed");
		जाओ err;
	पूर्ण

	nports = get_nports(hc_device);
	अगर (nports <= 0) अणु
		err("no available ports");
		जाओ err;
	पूर्ण
	dbg("available ports: %d", nports);

	vhci_driver = सुस्मृति(1, माप(काष्ठा usbip_vhci_driver) +
			nports * माप(काष्ठा usbip_imported_device));
	अगर (!vhci_driver) अणु
		err("vhci_driver allocation failed");
		जाओ err;
	पूर्ण

	vhci_driver->nports = nports;
	vhci_driver->hc_device = hc_device;
	vhci_driver->ncontrollers = get_ncontrollers();
	dbg("available controllers: %d", vhci_driver->ncontrollers);

	अगर (vhci_driver->ncontrollers <=0) अणु
		err("no available usb controllers");
		जाओ err;
	पूर्ण

	अगर (refresh_imported_device_list())
		जाओ err;

	वापस 0;

err:
	udev_device_unref(hc_device);

	अगर (vhci_driver)
		मुक्त(vhci_driver);

	vhci_driver = शून्य;

	udev_unref(udev_context);

	वापस -1;
पूर्ण


व्योम usbip_vhci_driver_बंद(व्योम)
अणु
	अगर (!vhci_driver)
		वापस;

	udev_device_unref(vhci_driver->hc_device);

	मुक्त(vhci_driver);

	vhci_driver = शून्य;

	udev_unref(udev_context);
पूर्ण


पूर्णांक usbip_vhci_refresh_device_list(व्योम)
अणु

	अगर (refresh_imported_device_list())
		जाओ err;

	वापस 0;
err:
	dbg("failed to refresh device list");
	वापस -1;
पूर्ण


पूर्णांक usbip_vhci_get_मुक्त_port(uपूर्णांक32_t speed)
अणु
	क्रम (पूर्णांक i = 0; i < vhci_driver->nports; i++) अणु

		चयन (speed) अणु
		हाल	USB_SPEED_SUPER:
			अगर (vhci_driver->idev[i].hub != HUB_SPEED_SUPER)
				जारी;
		अवरोध;
		शेष:
			अगर (vhci_driver->idev[i].hub != HUB_SPEED_HIGH)
				जारी;
		अवरोध;
		पूर्ण

		अगर (vhci_driver->idev[i].status == VDEV_ST_शून्य)
			वापस vhci_driver->idev[i].port;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक usbip_vhci_attach_device2(uपूर्णांक8_t port, पूर्णांक sockfd, uपूर्णांक32_t devid,
		uपूर्णांक32_t speed) अणु
	अक्षर buff[200]; /* what size should be ? */
	अक्षर attach_attr_path[SYSFS_PATH_MAX];
	अक्षर attr_attach[] = "attach";
	स्थिर अक्षर *path;
	पूर्णांक ret;

	snम_लिखो(buff, माप(buff), "%u %d %u %u",
			port, sockfd, devid, speed);
	dbg("writing: %s", buff);

	path = udev_device_get_syspath(vhci_driver->hc_device);
	snम_लिखो(attach_attr_path, माप(attach_attr_path), "%s/%s",
		 path, attr_attach);
	dbg("attach attribute path: %s", attach_attr_path);

	ret = ग_लिखो_sysfs_attribute(attach_attr_path, buff, म_माप(buff));
	अगर (ret < 0) अणु
		dbg("write_sysfs_attribute failed");
		वापस -1;
	पूर्ण

	dbg("attached port: %d", port);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ get_devid(uपूर्णांक8_t busnum, uपूर्णांक8_t devnum)
अणु
	वापस (busnum << 16) | devnum;
पूर्ण

/* will be हटाओd */
पूर्णांक usbip_vhci_attach_device(uपूर्णांक8_t port, पूर्णांक sockfd, uपूर्णांक8_t busnum,
		uपूर्णांक8_t devnum, uपूर्णांक32_t speed)
अणु
	पूर्णांक devid = get_devid(busnum, devnum);

	वापस usbip_vhci_attach_device2(port, sockfd, devid, speed);
पूर्ण

पूर्णांक usbip_vhci_detach_device(uपूर्णांक8_t port)
अणु
	अक्षर detach_attr_path[SYSFS_PATH_MAX];
	अक्षर attr_detach[] = "detach";
	अक्षर buff[200]; /* what size should be ? */
	स्थिर अक्षर *path;
	पूर्णांक ret;

	snम_लिखो(buff, माप(buff), "%u", port);
	dbg("writing: %s", buff);

	path = udev_device_get_syspath(vhci_driver->hc_device);
	snम_लिखो(detach_attr_path, माप(detach_attr_path), "%s/%s",
		 path, attr_detach);
	dbg("detach attribute path: %s", detach_attr_path);

	ret = ग_लिखो_sysfs_attribute(detach_attr_path, buff, म_माप(buff));
	अगर (ret < 0) अणु
		dbg("write_sysfs_attribute failed");
		वापस -1;
	पूर्ण

	dbg("detached port: %d", port);

	वापस 0;
पूर्ण

पूर्णांक usbip_vhci_imported_device_dump(काष्ठा usbip_imported_device *idev)
अणु
	अक्षर product_name[100];
	अक्षर host[NI_MAXHOST] = "unknown host";
	अक्षर serv[NI_MAXSERV] = "unknown port";
	अक्षर remote_busid[SYSFS_BUS_ID_SIZE];
	पूर्णांक ret;
	पूर्णांक पढ़ो_record_error = 0;

	अगर (idev->status == VDEV_ST_शून्य || idev->status == VDEV_ST_NOTASSIGNED)
		वापस 0;

	ret = पढ़ो_record(idev->port, host, माप(host), serv, माप(serv),
			  remote_busid);
	अगर (ret) अणु
		err("read_record");
		पढ़ो_record_error = 1;
	पूर्ण

	म_लिखो("Port %02d: <%s> at %s\n", idev->port,
	       usbip_status_string(idev->status),
	       usbip_speed_string(idev->udev.speed));

	usbip_names_get_product(product_name, माप(product_name),
				idev->udev.idVenकरोr, idev->udev.idProduct);

	म_लिखो("       %s\n",  product_name);

	अगर (!पढ़ो_record_error) अणु
		म_लिखो("%10s -> usbip://%s:%s/%s\n", idev->udev.busid,
		       host, serv, remote_busid);
		म_लिखो("%10s -> remote bus/dev %03d/%03d\n", " ",
		       idev->busnum, idev->devnum);
	पूर्ण अन्यथा अणु
		म_लिखो("%10s -> unknown host, remote port and remote busid\n",
		       idev->udev.busid);
		म_लिखो("%10s -> remote bus/dev %03d/%03d\n", " ",
		       idev->busnum, idev->devnum);
	पूर्ण

	वापस 0;
पूर्ण
