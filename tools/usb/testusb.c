<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* $(CROSS_COMPILE)cc -Wall -Wextra -g -lpthपढ़ो -o testusb testusb.c */

/*
 * Copyright (c) 2002 by David Brownell
 * Copyright (c) 2010 by Samsung Electronics
 * Author: Michal Nazarewicz <mina86@mina86.com>
 */

/*
 * This program issues ioctls to perक्रमm the tests implemented by the
 * kernel driver.  It can generate a variety of transfer patterns; you
 * should make sure to test both regular streaming and mixes of
 * transfer sizes (including लघु transfers).
 *
 * For more inक्रमmation on how this can be used and on USB testing
 * refer to <URL:http://www.linux-usb.org/usbtest/>.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <ftw.h>
#समावेश <मानककोष.स>
#समावेश <pthपढ़ो.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश <sys/ioctl.h>
#समावेश <linux/usbdevice_fs.h>

/*-------------------------------------------------------------------------*/

#घोषणा	TEST_CASES	30

// FIXME make these खुला somewhere; usbdevfs.h?

काष्ठा usbtest_param अणु
	// inमाला_दो
	अचिन्हित		test_num;	/* 0..(TEST_CASES-1) */
	अचिन्हित		iterations;
	अचिन्हित		length;
	अचिन्हित		vary;
	अचिन्हित		sglen;

	// outमाला_दो
	काष्ठा समयval		duration;
पूर्ण;
#घोषणा USBTEST_REQUEST	_IOWR('U', 100, काष्ठा usbtest_param)

/*-------------------------------------------------------------------------*/

/* #समावेश <linux/usb_ch9.h> */

#घोषणा USB_DT_DEVICE			0x01
#घोषणा USB_DT_INTERFACE		0x04

#घोषणा USB_CLASS_PER_INTERFACE		0	/* क्रम DeviceClass */
#घोषणा USB_CLASS_VENDOR_SPEC		0xff


काष्ठा usb_device_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u16 bcdUSB;
	__u8  bDeviceClass;
	__u8  bDeviceSubClass;
	__u8  bDeviceProtocol;
	__u8  bMaxPacketSize0;
	__u16 idVenकरोr;
	__u16 idProduct;
	__u16 bcdDevice;
	__u8  iManufacturer;
	__u8  iProduct;
	__u8  iSerialNumber;
	__u8  bNumConfigurations;
पूर्ण __attribute__ ((packed));

काष्ठा usb_पूर्णांकerface_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bInterfaceNumber;
	__u8  bAlternateSetting;
	__u8  bNumEndpoपूर्णांकs;
	__u8  bInterfaceClass;
	__u8  bInterfaceSubClass;
	__u8  bInterfaceProtocol;
	__u8  iInterface;
पूर्ण __attribute__ ((packed));

क्रमागत usb_device_speed अणु
	USB_SPEED_UNKNOWN = 0,			/* क्रमागतerating */
	USB_SPEED_LOW, USB_SPEED_FULL,		/* usb 1.1 */
	USB_SPEED_HIGH				/* usb 2.0 */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल अक्षर *speed (क्रमागत usb_device_speed s)
अणु
	चयन (s) अणु
	हाल USB_SPEED_UNKNOWN:	वापस "unknown";
	हाल USB_SPEED_LOW:	वापस "low";
	हाल USB_SPEED_FULL:	वापस "full";
	हाल USB_SPEED_HIGH:	वापस "high";
	शेष:		वापस "??";
	पूर्ण
पूर्ण

काष्ठा testdev अणु
	काष्ठा testdev		*next;
	अक्षर			*name;
	pthपढ़ो_t		thपढ़ो;
	क्रमागत usb_device_speed	speed;
	अचिन्हित		अगरnum : 8;
	अचिन्हित		क्रमever : 1;
	पूर्णांक			test;

	काष्ठा usbtest_param	param;
पूर्ण;
अटल काष्ठा testdev		*testdevs;

अटल पूर्णांक testdev_ffs_अगरnum(खाता *fd)
अणु
	जोड़ अणु
		अक्षर buf[255];
		काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf;
	पूर्ण u;

	क्रम (;;) अणु
		अगर (ख_पढ़ो(u.buf, 1, 1, fd) != 1)
			वापस -1;
		अगर (ख_पढ़ो(u.buf + 1, (अचिन्हित अक्षर)u.buf[0] - 1, 1, fd) != 1)
			वापस -1;

		अगर (u.पूर्णांकf.bLength == माप u.पूर्णांकf
		 && u.पूर्णांकf.bDescriptorType == USB_DT_INTERFACE
		 && u.पूर्णांकf.bNumEndpoपूर्णांकs == 2
		 && u.पूर्णांकf.bInterfaceClass == USB_CLASS_VENDOR_SPEC
		 && u.पूर्णांकf.bInterfaceSubClass == 0
		 && u.पूर्णांकf.bInterfaceProtocol == 0)
			वापस (अचिन्हित अक्षर)u.पूर्णांकf.bInterfaceNumber;
	पूर्ण
पूर्ण

अटल पूर्णांक testdev_अगरnum(खाता *fd)
अणु
	काष्ठा usb_device_descriptor dev;

	अगर (ख_पढ़ो(&dev, माप dev, 1, fd) != 1)
		वापस -1;

	अगर (dev.bLength != माप dev || dev.bDescriptorType != USB_DT_DEVICE)
		वापस -1;

	/* FX2 with (tweaked) bulksrc firmware */
	अगर (dev.idVenकरोr == 0x0547 && dev.idProduct == 0x1002)
		वापस 0;

	/*----------------------------------------------------*/

	/* devices that start up using the EZ-USB शेष device and
	 * which we can use after loading simple firmware.  hotplug
	 * can fxload it, and then run this test driver.
	 *
	 * we वापस false positives in two हालs:
	 * - the device has a "real" driver (maybe usb-serial) that
	 *   rक्रमागतerates.  the device should vanish quickly.
	 * - the device करोesn't have the test firmware installed.
	 */

	/* generic EZ-USB FX controller */
	अगर (dev.idVenकरोr == 0x0547 && dev.idProduct == 0x2235)
		वापस 0;

	/* generic EZ-USB FX2 controller */
	अगर (dev.idVenकरोr == 0x04b4 && dev.idProduct == 0x8613)
		वापस 0;

	/* CY3671 development board with EZ-USB FX */
	अगर (dev.idVenकरोr == 0x0547 && dev.idProduct == 0x0080)
		वापस 0;

	/* Keyspan 19Qi uses an21xx (original EZ-USB) */
	अगर (dev.idVenकरोr == 0x06cd && dev.idProduct == 0x010b)
		वापस 0;

	/*----------------------------------------------------*/

	/* "gadget zero", Linux-USB test software */
	अगर (dev.idVenकरोr == 0x0525 && dev.idProduct == 0xa4a0)
		वापस 0;

	/* user mode subset of that */
	अगर (dev.idVenकरोr == 0x0525 && dev.idProduct == 0xa4a4)
		वापस testdev_ffs_अगरnum(fd);
		/* वापस 0; */

	/* iso version of usermode code */
	अगर (dev.idVenकरोr == 0x0525 && dev.idProduct == 0xa4a3)
		वापस 0;

	/* some GPL'd test firmware uses these IDs */

	अगर (dev.idVenकरोr == 0xfff0 && dev.idProduct == 0xfff0)
		वापस 0;

	/*----------------------------------------------------*/

	/* iBOT2 high speed webcam */
	अगर (dev.idVenकरोr == 0x0b62 && dev.idProduct == 0x0059)
		वापस 0;

	/*----------------------------------------------------*/

	/* the FunctionFS gadget can have the source/sink पूर्णांकerface
	 * anywhere.  We look क्रम an पूर्णांकerface descriptor that match
	 * what we expect.  We ignore configuratiens thou. */

	अगर (dev.idVenकरोr == 0x0525 && dev.idProduct == 0xa4ac
	 && (dev.bDeviceClass == USB_CLASS_PER_INTERFACE
	  || dev.bDeviceClass == USB_CLASS_VENDOR_SPEC))
		वापस testdev_ffs_अगरnum(fd);

	वापस -1;
पूर्ण

अटल पूर्णांक find_testdev(स्थिर अक्षर *name, स्थिर काष्ठा stat *sb, पूर्णांक flag)
अणु
	खाता				*fd;
	पूर्णांक				अगरnum;
	काष्ठा testdev			*entry;

	(व्योम)sb; /* unused */

	अगर (flag != FTW_F)
		वापस 0;

	fd = ख_खोलो(name, "rb");
	अगर (!fd) अणु
		लिखो_त्रुटि(name);
		वापस 0;
	पूर्ण

	अगरnum = testdev_अगरnum(fd);
	ख_बंद(fd);
	अगर (अगरnum < 0)
		वापस 0;

	entry = सुस्मृति(1, माप *entry);
	अगर (!entry)
		जाओ nomem;

	entry->name = strdup(name);
	अगर (!entry->name) अणु
		मुक्त(entry);
nomem:
		लिखो_त्रुटि("malloc");
		वापस 0;
	पूर्ण

	entry->अगरnum = अगरnum;

	/* FIXME update USBDEVFS_CONNECTINFO so it tells about high speed etc */

	ख_लिखो(मानक_त्रुटि, "%s speed\t%s\t%u\n",
		speed(entry->speed), entry->name, entry->अगरnum);

	entry->next = testdevs;
	testdevs = entry;
	वापस 0;
पूर्ण

अटल पूर्णांक
usbdev_ioctl (पूर्णांक fd, पूर्णांक अगरno, अचिन्हित request, व्योम *param)
अणु
	काष्ठा usbdevfs_ioctl	wrapper;

	wrapper.अगरno = अगरno;
	wrapper.ioctl_code = request;
	wrapper.data = param;

	वापस ioctl (fd, USBDEVFS_IOCTL, &wrapper);
पूर्ण

अटल व्योम *handle_testdev (व्योम *arg)
अणु
	काष्ठा testdev		*dev = arg;
	पूर्णांक			fd, i;
	पूर्णांक			status;

	अगर ((fd = खोलो (dev->name, O_RDWR)) < 0) अणु
		लिखो_त्रुटि ("can't open dev file r/w");
		वापस 0;
	पूर्ण

restart:
	क्रम (i = 0; i < TEST_CASES; i++) अणु
		अगर (dev->test != -1 && dev->test != i)
			जारी;
		dev->param.test_num = i;

		status = usbdev_ioctl (fd, dev->अगरnum,
				USBTEST_REQUEST, &dev->param);
		अगर (status < 0 && त्रुटि_सं == EOPNOTSUPP)
			जारी;

		/* FIXME need a "syslog it" option क्रम background testing */

		/* NOTE: each thपढ़ो emits complete lines; no fragments! */
		अगर (status < 0) अणु
			अक्षर	buf [80];
			पूर्णांक	err = त्रुटि_सं;

			अगर (म_त्रुटि_r (त्रुटि_सं, buf, माप buf)) अणु
				snम_लिखो (buf, माप buf, "error %d", err);
				त्रुटि_सं = err;
			पूर्ण
			म_लिखो ("%s test %d --> %d (%s)\n",
				dev->name, i, त्रुटि_सं, buf);
		पूर्ण अन्यथा
			म_लिखो ("%s test %d, %4d.%.06d secs\n", dev->name, i,
				(पूर्णांक) dev->param.duration.tv_sec,
				(पूर्णांक) dev->param.duration.tv_usec);

		ख_साफ (मानक_निकास);
	पूर्ण
	अगर (dev->क्रमever)
		जाओ restart;

	बंद (fd);
	वापस arg;
पूर्ण

अटल स्थिर अक्षर *usb_dir_find(व्योम)
अणु
	अटल अक्षर udev_usb_path[] = "/dev/bus/usb";

	अगर (access(udev_usb_path, F_OK) == 0)
		वापस udev_usb_path;

	वापस शून्य;
पूर्ण

अटल पूर्णांक parse_num(अचिन्हित *num, स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ val;
	अक्षर *end;

	त्रुटि_सं = 0;
	val = म_से_अदीर्घ(str, &end, 0);
	अगर (त्रुटि_सं || *end || val > अच_पूर्णांक_उच्च)
		वापस -1;
	*num = val;
	वापस 0;
पूर्ण

पूर्णांक मुख्य (पूर्णांक argc, अक्षर **argv)
अणु

	पूर्णांक			c;
	काष्ठा testdev		*entry;
	अक्षर			*device;
	स्थिर अक्षर		*usb_dir = शून्य;
	पूर्णांक			all = 0, क्रमever = 0, not = 0;
	पूर्णांक			test = -1 /* all */;
	काष्ठा usbtest_param	param;

	/* pick शेषs that works with all speeds, without लघु packets.
	 *
	 * Best per-frame data rates:
	 *     super speed,bulk      1024 * 16 * 8 = 131072
	 *                 पूर्णांकerrupt 1024 *  3 * 8 =  24576
	 *     high speed, bulk       512 * 13 * 8 =  53248
	 *                 पूर्णांकerrupt 1024 *  3 * 8 =  24576
	 *     full speed, bulk/पूर्णांकr   64 * 19     =   1216
	 *                 पूर्णांकerrupt   64 *  1     =     64
	 *      low speed, पूर्णांकerrupt    8 *  1     =      8
	 */
	param.iterations = 1000;
	param.length = 1024;
	param.vary = 1024;
	param.sglen = 32;

	/* क्रम easy use when hotplugging */
	device = दो_पर्या ("DEVICE");

	जबतक ((c = getopt (argc, argv, "D:aA:c:g:hlns:t:v:")) != खातापूर्ण)
	चयन (c) अणु
	हाल 'D':	/* device, अगर only one */
		device = optarg;
		जारी;
	हाल 'A':	/* use all devices with specअगरied USB dir */
		usb_dir = optarg;
		/* FALL THROUGH */
	हाल 'a':	/* use all devices */
		device = शून्य;
		all = 1;
		जारी;
	हाल 'c':	/* count iterations */
		अगर (parse_num(&param.iterations, optarg))
			जाओ usage;
		जारी;
	हाल 'g':	/* scatter/gather entries */
		अगर (parse_num(&param.sglen, optarg))
			जाओ usage;
		जारी;
	हाल 'l':	/* loop क्रमever */
		क्रमever = 1;
		जारी;
	हाल 'n':	/* no test running! */
		not = 1;
		जारी;
	हाल 's':	/* size of packet */
		अगर (parse_num(&param.length, optarg))
			जाओ usage;
		जारी;
	हाल 't':	/* run just one test */
		test = म_से_प (optarg);
		अगर (test < 0)
			जाओ usage;
		जारी;
	हाल 'v':	/* vary packet size by ... */
		अगर (parse_num(&param.vary, optarg))
			जाओ usage;
		जारी;
	हाल '?':
	हाल 'h':
	शेष:
usage:
		ख_लिखो (मानक_त्रुटि,
			"usage: %s [options]\n"
			"Options:\n"
			"\t-D dev		only test specific device\n"
			"\t-A usb-dir\n"
			"\t-a		test all recognized devices\n"
			"\t-l		loop forever(for stress test)\n"
			"\t-t testnum	only run specified case\n"
			"\t-n		no test running, show devices to be tested\n"
			"Case arguments:\n"
			"\t-c iterations		default 1000\n"
			"\t-s transfer length	default 1024\n"
			"\t-g sglen		default 32\n"
			"\t-v vary			default 1024\n",
			argv[0]);
		वापस 1;
	पूर्ण
	अगर (optind != argc)
		जाओ usage;
	अगर (!all && !device) अणु
		ख_लिखो (मानक_त्रुटि, "must specify '-a' or '-D dev', "
			"or DEVICE=/dev/bus/usb/BBB/DDD in env\n");
		जाओ usage;
	पूर्ण

	/* Find usb device subdirectory */
	अगर (!usb_dir) अणु
		usb_dir = usb_dir_find();
		अगर (!usb_dir) अणु
			ख_माला_दो ("USB device files are missing\n", मानक_त्रुटि);
			वापस -1;
		पूर्ण
	पूर्ण

	/* collect and list the test devices */
	अगर (ftw (usb_dir, find_testdev, 3) != 0) अणु
		ख_माला_दो ("ftw failed; are USB device files missing?\n", मानक_त्रुटि);
		वापस -1;
	पूर्ण

	/* quit, run single test, or create test thपढ़ोs */
	अगर (!testdevs && !device) अणु
		ख_माला_दो ("no test devices recognized\n", मानक_त्रुटि);
		वापस -1;
	पूर्ण
	अगर (not)
		वापस 0;
	अगर (testdevs && testdevs->next == 0 && !device)
		device = testdevs->name;
	क्रम (entry = testdevs; entry; entry = entry->next) अणु
		पूर्णांक	status;

		entry->param = param;
		entry->क्रमever = क्रमever;
		entry->test = test;

		अगर (device) अणु
			अगर (म_भेद (entry->name, device))
				जारी;
			वापस handle_testdev (entry) != entry;
		पूर्ण
		status = pthपढ़ो_create (&entry->thपढ़ो, 0, handle_testdev, entry);
		अगर (status)
			लिखो_त्रुटि ("pthread_create");
	पूर्ण
	अगर (device) अणु
		काष्ठा testdev		dev;

		/* kernel can recognize test devices we करोn't */
		ख_लिखो (मानक_त्रुटि, "%s: %s may see only control tests\n",
				argv [0], device);

		स_रखो (&dev, 0, माप dev);
		dev.name = device;
		dev.param = param;
		dev.क्रमever = क्रमever;
		dev.test = test;
		वापस handle_testdev (&dev) != &dev;
	पूर्ण

	/* रुको क्रम tests to complete */
	क्रम (entry = testdevs; entry; entry = entry->next) अणु
		व्योम	*retval;

		अगर (pthपढ़ो_join (entry->thपढ़ो, &retval))
			लिखो_त्रुटि ("pthread_join");
		/* testing errors discarded! */
	पूर्ण

	वापस 0;
पूर्ण
