<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@संकेत11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using hidraw.
 */

/* Linux */
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/hidraw.h>

/*
 * Ugly hack to work around failing compilation on प्रणालीs that करोn't
 * yet populate new version of hidraw.h to userspace.
 */
#अगर_अघोषित HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#घोषणा HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
#घोषणा HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
#पूर्ण_अगर

/* Unix */
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

/* C */
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>

स्थिर अक्षर *bus_str(पूर्णांक bus);

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd;
	पूर्णांक i, res, desc_size = 0;
	अक्षर buf[256];
	काष्ठा hidraw_report_descriptor rpt_desc;
	काष्ठा hidraw_devinfo info;
	अक्षर *device = "/dev/hidraw0";

	अगर (argc > 1)
		device = argv[1];

	/* Open the Device with non-blocking पढ़ोs. In real lअगरe,
	   करोn't use a hard coded path; use libudev instead. */
	fd = खोलो(device, O_RDWR|O_NONBLOCK);

	अगर (fd < 0) अणु
		लिखो_त्रुटि("Unable to open device");
		वापस 1;
	पूर्ण

	स_रखो(&rpt_desc, 0x0, माप(rpt_desc));
	स_रखो(&info, 0x0, माप(info));
	स_रखो(buf, 0x0, माप(buf));

	/* Get Report Descriptor Size */
	res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
	अगर (res < 0)
		लिखो_त्रुटि("HIDIOCGRDESCSIZE");
	अन्यथा
		म_लिखो("Report Descriptor Size: %d\n", desc_size);

	/* Get Report Descriptor */
	rpt_desc.size = desc_size;
	res = ioctl(fd, HIDIOCGRDESC, &rpt_desc);
	अगर (res < 0) अणु
		लिखो_त्रुटि("HIDIOCGRDESC");
	पूर्ण अन्यथा अणु
		म_लिखो("Report Descriptor:\n");
		क्रम (i = 0; i < rpt_desc.size; i++)
			म_लिखो("%hhx ", rpt_desc.value[i]);
		माला_दो("\n");
	पूर्ण

	/* Get Raw Name */
	res = ioctl(fd, HIDIOCGRAWNAME(256), buf);
	अगर (res < 0)
		लिखो_त्रुटि("HIDIOCGRAWNAME");
	अन्यथा
		म_लिखो("Raw Name: %s\n", buf);

	/* Get Physical Location */
	res = ioctl(fd, HIDIOCGRAWPHYS(256), buf);
	अगर (res < 0)
		लिखो_त्रुटि("HIDIOCGRAWPHYS");
	अन्यथा
		म_लिखो("Raw Phys: %s\n", buf);

	/* Get Raw Info */
	res = ioctl(fd, HIDIOCGRAWINFO, &info);
	अगर (res < 0) अणु
		लिखो_त्रुटि("HIDIOCGRAWINFO");
	पूर्ण अन्यथा अणु
		म_लिखो("Raw Info:\n");
		म_लिखो("\tbustype: %d (%s)\n",
			info.bustype, bus_str(info.bustype));
		म_लिखो("\tvendor: 0x%04hx\n", info.venकरोr);
		म_लिखो("\tproduct: 0x%04hx\n", info.product);
	पूर्ण

	/* Set Feature */
	buf[0] = 0x9; /* Report Number */
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	res = ioctl(fd, HIDIOCSFEATURE(4), buf);
	अगर (res < 0)
		लिखो_त्रुटि("HIDIOCSFEATURE");
	अन्यथा
		म_लिखो("ioctl HIDIOCSFEATURE returned: %d\n", res);

	/* Get Feature */
	buf[0] = 0x9; /* Report Number */
	res = ioctl(fd, HIDIOCGFEATURE(256), buf);
	अगर (res < 0) अणु
		लिखो_त्रुटि("HIDIOCGFEATURE");
	पूर्ण अन्यथा अणु
		म_लिखो("ioctl HIDIOCGFEATURE returned: %d\n", res);
		म_लिखो("Report data:\n\t");
		क्रम (i = 0; i < res; i++)
			म_लिखो("%hhx ", buf[i]);
		माला_दो("\n");
	पूर्ण

	/* Send a Report to the Device */
	buf[0] = 0x1; /* Report Number */
	buf[1] = 0x77;
	res = ग_लिखो(fd, buf, 2);
	अगर (res < 0) अणु
		म_लिखो("Error: %d\n", त्रुटि_सं);
		लिखो_त्रुटि("write");
	पूर्ण अन्यथा अणु
		म_लिखो("write() wrote %d bytes\n", res);
	पूर्ण

	/* Get a report from the device */
	res = पढ़ो(fd, buf, 16);
	अगर (res < 0) अणु
		लिखो_त्रुटि("read");
	पूर्ण अन्यथा अणु
		म_लिखो("read() read %d bytes:\n\t", res);
		क्रम (i = 0; i < res; i++)
			म_लिखो("%hhx ", buf[i]);
		माला_दो("\n");
	पूर्ण
	बंद(fd);
	वापस 0;
पूर्ण

स्थिर अक्षर *
bus_str(पूर्णांक bus)
अणु
	चयन (bus) अणु
	हाल BUS_USB:
		वापस "USB";
		अवरोध;
	हाल BUS_HIL:
		वापस "HIL";
		अवरोध;
	हाल BUS_BLUETOOTH:
		वापस "Bluetooth";
		अवरोध;
	हाल BUS_VIRTUAL:
		वापस "Virtual";
		अवरोध;
	शेष:
		वापस "Other";
		अवरोध;
	पूर्ण
पूर्ण
