<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UHID Example
 *
 * Copyright (c) 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using uhid.
 */

/*
 * UHID Example
 * This example emulates a basic 3 buttons mouse with wheel over UHID. Run this
 * program as root and then use the following keys to control the mouse:
 *   q: Quit the application
 *   1: Toggle left button (करोwn, up, ...)
 *   2: Toggle right button
 *   3: Toggle middle button
 *   a: Move mouse left
 *   d: Move mouse right
 *   w: Move mouse up
 *   s: Move mouse करोwn
 *   r: Move wheel up
 *   f: Move wheel करोwn
 *
 * Additionally to 3 button mouse, 3 keyboard LEDs are also supported (LED_NUML,
 * LED_CAPSL and LED_SCROLLL). The device करोesn't generate any related keyboard
 * events, though. You need to manually ग_लिखो the EV_LED/LED_XY/1 activation
 * input event to the evdev device to see it being sent to this device.
 *
 * If uhid is not available as /dev/uhid, then you can pass a dअगरferent path as
 * first argument.
 * If <linux/uhid.h> is not installed in /usr, then compile this with:
 *   gcc -o ./uhid_test -Wall -I./include ./samples/uhid/uhid-example.c
 * And ignore the warning about kernel headers. However, it is recommended to
 * use the installed uhid.h अगर available.
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <termios.h>
#समावेश <unistd.h>
#समावेश <linux/uhid.h>

/*
 * HID Report Desciptor
 * We emulate a basic 3 button mouse with wheel and 3 keyboard LEDs. This is
 * the report-descriptor as the kernel will parse it:
 *
 * INPUT(1)[INPUT]
 *   Field(0)
 *     Physical(GenericDesktop.Poपूर्णांकer)
 *     Application(GenericDesktop.Mouse)
 *     Usage(3)
 *       Button.0001
 *       Button.0002
 *       Button.0003
 *     Logical Minimum(0)
 *     Logical Maximum(1)
 *     Report Size(1)
 *     Report Count(3)
 *     Report Offset(0)
 *     Flags( Variable Absolute )
 *   Field(1)
 *     Physical(GenericDesktop.Poपूर्णांकer)
 *     Application(GenericDesktop.Mouse)
 *     Usage(3)
 *       GenericDesktop.X
 *       GenericDesktop.Y
 *       GenericDesktop.Wheel
 *     Logical Minimum(-128)
 *     Logical Maximum(127)
 *     Report Size(8)
 *     Report Count(3)
 *     Report Offset(8)
 *     Flags( Variable Relative )
 * OUTPUT(2)[OUTPUT]
 *   Field(0)
 *     Application(GenericDesktop.Keyboard)
 *     Usage(3)
 *       LED.NumLock
 *       LED.CapsLock
 *       LED.ScrollLock
 *     Logical Minimum(0)
 *     Logical Maximum(1)
 *     Report Size(1)
 *     Report Count(3)
 *     Report Offset(0)
 *     Flags( Variable Absolute )
 *
 * This is the mapping that we expect:
 *   Button.0001 ---> Key.LeftBtn
 *   Button.0002 ---> Key.RightBtn
 *   Button.0003 ---> Key.MiddleBtn
 *   GenericDesktop.X ---> Relative.X
 *   GenericDesktop.Y ---> Relative.Y
 *   GenericDesktop.Wheel ---> Relative.Wheel
 *   LED.NumLock ---> LED.NumLock
 *   LED.CapsLock ---> LED.CapsLock
 *   LED.ScrollLock ---> LED.ScrollLock
 *
 * This inक्रमmation can be verअगरied by पढ़ोing /sys/kernel/debug/hid/<dev>/rdesc
 * This file should prपूर्णांक the same inक्रमmation as showed above.
 */

अटल अचिन्हित अक्षर rdesc[] = अणु
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x02,	/* USAGE (Mouse) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x09, 0x01,		/* USAGE (Poपूर्णांकer) */
	0xa1, 0x00,		/* COLLECTION (Physical) */
	0x85, 0x01,			/* REPORT_ID (1) */
	0x05, 0x09,			/* USAGE_PAGE (Button) */
	0x19, 0x01,			/* USAGE_MINIMUM (Button 1) */
	0x29, 0x03,			/* USAGE_MAXIMUM (Button 3) */
	0x15, 0x00,			/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,			/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x75, 0x01,			/* REPORT_SIZE (1) */
	0x81, 0x02,			/* INPUT (Data,Var,Abs) */
	0x95, 0x01,			/* REPORT_COUNT (1) */
	0x75, 0x05,			/* REPORT_SIZE (5) */
	0x81, 0x01,			/* INPUT (Cnst,Var,Abs) */
	0x05, 0x01,			/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x30,			/* USAGE (X) */
	0x09, 0x31,			/* USAGE (Y) */
	0x09, 0x38,			/* USAGE (WHEEL) */
	0x15, 0x81,			/* LOGICAL_MINIMUM (-127) */
	0x25, 0x7f,			/* LOGICAL_MAXIMUM (127) */
	0x75, 0x08,			/* REPORT_SIZE (8) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x81, 0x06,			/* INPUT (Data,Var,Rel) */
	0xc0,			/* END_COLLECTION */
	0xc0,		/* END_COLLECTION */
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x06,	/* USAGE (Keyboard) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x85, 0x02,		/* REPORT_ID (2) */
	0x05, 0x08,		/* USAGE_PAGE (Led) */
	0x19, 0x01,		/* USAGE_MINIMUM (1) */
	0x29, 0x03,		/* USAGE_MAXIMUM (3) */
	0x15, 0x00,		/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,		/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,		/* REPORT_COUNT (3) */
	0x75, 0x01,		/* REPORT_SIZE (1) */
	0x91, 0x02,		/* Output (Data,Var,Abs) */
	0x95, 0x01,		/* REPORT_COUNT (1) */
	0x75, 0x05,		/* REPORT_SIZE (5) */
	0x91, 0x01,		/* Output (Cnst,Var,Abs) */
	0xc0,		/* END_COLLECTION */
पूर्ण;

अटल पूर्णांक uhid_ग_लिखो(पूर्णांक fd, स्थिर काष्ठा uhid_event *ev)
अणु
	sमाप_प्रकार ret;

	ret = ग_लिखो(fd, ev, माप(*ev));
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot write to uhid: %m\n");
		वापस -त्रुटि_सं;
	पूर्ण अन्यथा अगर (ret != माप(*ev)) अणु
		ख_लिखो(मानक_त्रुटि, "Wrong size written to uhid: %zd != %zu\n",
			ret, माप(ev));
		वापस -EFAULT;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक create(पूर्णांक fd)
अणु
	काष्ठा uhid_event ev;

	स_रखो(&ev, 0, माप(ev));
	ev.type = UHID_CREATE;
	म_नकल((अक्षर*)ev.u.create.name, "test-uhid-device");
	ev.u.create.rd_data = rdesc;
	ev.u.create.rd_size = माप(rdesc);
	ev.u.create.bus = BUS_USB;
	ev.u.create.venकरोr = 0x15d9;
	ev.u.create.product = 0x0a37;
	ev.u.create.version = 0;
	ev.u.create.country = 0;

	वापस uhid_ग_लिखो(fd, &ev);
पूर्ण

अटल व्योम destroy(पूर्णांक fd)
अणु
	काष्ठा uhid_event ev;

	स_रखो(&ev, 0, माप(ev));
	ev.type = UHID_DESTROY;

	uhid_ग_लिखो(fd, &ev);
पूर्ण

/* This parses raw output reports sent by the kernel to the device. A normal
 * uhid program shouldn't करो this but instead just क्रमward the raw report.
 * However, क्रम ducomentational purposes, we try to detect LED events here and
 * prपूर्णांक debug messages क्रम it. */
अटल व्योम handle_output(काष्ठा uhid_event *ev)
अणु
	/* LED messages are adverised via OUTPUT reports; ignore the rest */
	अगर (ev->u.output.rtype != UHID_OUTPUT_REPORT)
		वापस;
	/* LED reports have length 2 bytes */
	अगर (ev->u.output.size != 2)
		वापस;
	/* first byte is report-id which is 0x02 क्रम LEDs in our rdesc */
	अगर (ev->u.output.data[0] != 0x2)
		वापस;

	/* prपूर्णांक flags payload */
	ख_लिखो(मानक_त्रुटि, "LED output report received with flags %x\n",
		ev->u.output.data[1]);
पूर्ण

अटल पूर्णांक event(पूर्णांक fd)
अणु
	काष्ठा uhid_event ev;
	sमाप_प्रकार ret;

	स_रखो(&ev, 0, माप(ev));
	ret = पढ़ो(fd, &ev, माप(ev));
	अगर (ret == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Read HUP on uhid-cdev\n");
		वापस -EFAULT;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot read uhid-cdev: %m\n");
		वापस -त्रुटि_सं;
	पूर्ण अन्यथा अगर (ret != माप(ev)) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid size read from uhid-dev: %zd != %zu\n",
			ret, माप(ev));
		वापस -EFAULT;
	पूर्ण

	चयन (ev.type) अणु
	हाल UHID_START:
		ख_लिखो(मानक_त्रुटि, "UHID_START from uhid-dev\n");
		अवरोध;
	हाल UHID_STOP:
		ख_लिखो(मानक_त्रुटि, "UHID_STOP from uhid-dev\n");
		अवरोध;
	हाल UHID_OPEN:
		ख_लिखो(मानक_त्रुटि, "UHID_OPEN from uhid-dev\n");
		अवरोध;
	हाल UHID_CLOSE:
		ख_लिखो(मानक_त्रुटि, "UHID_CLOSE from uhid-dev\n");
		अवरोध;
	हाल UHID_OUTPUT:
		ख_लिखो(मानक_त्रुटि, "UHID_OUTPUT from uhid-dev\n");
		handle_output(&ev);
		अवरोध;
	हाल UHID_OUTPUT_EV:
		ख_लिखो(मानक_त्रुटि, "UHID_OUTPUT_EV from uhid-dev\n");
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "Invalid event from uhid-dev: %u\n", ev.type);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool btn1_करोwn;
अटल bool btn2_करोwn;
अटल bool btn3_करोwn;
अटल चिन्हित अक्षर असल_hor;
अटल चिन्हित अक्षर असल_ver;
अटल चिन्हित अक्षर wheel;

अटल पूर्णांक send_event(पूर्णांक fd)
अणु
	काष्ठा uhid_event ev;

	स_रखो(&ev, 0, माप(ev));
	ev.type = UHID_INPUT;
	ev.u.input.size = 5;

	ev.u.input.data[0] = 0x1;
	अगर (btn1_करोwn)
		ev.u.input.data[1] |= 0x1;
	अगर (btn2_करोwn)
		ev.u.input.data[1] |= 0x2;
	अगर (btn3_करोwn)
		ev.u.input.data[1] |= 0x4;

	ev.u.input.data[2] = असल_hor;
	ev.u.input.data[3] = असल_ver;
	ev.u.input.data[4] = wheel;

	वापस uhid_ग_लिखो(fd, &ev);
पूर्ण

अटल पूर्णांक keyboard(पूर्णांक fd)
अणु
	अक्षर buf[128];
	sमाप_प्रकार ret, i;

	ret = पढ़ो(STDIN_खाताNO, buf, माप(buf));
	अगर (ret == 0) अणु
		ख_लिखो(मानक_त्रुटि, "Read HUP on stdin\n");
		वापस -EFAULT;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot read stdin: %m\n");
		वापस -त्रुटि_सं;
	पूर्ण

	क्रम (i = 0; i < ret; ++i) अणु
		चयन (buf[i]) अणु
		हाल '1':
			btn1_करोwn = !btn1_करोwn;
			ret = send_event(fd);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल '2':
			btn2_करोwn = !btn2_करोwn;
			ret = send_event(fd);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल '3':
			btn3_करोwn = !btn3_करोwn;
			ret = send_event(fd);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'a':
			असल_hor = -20;
			ret = send_event(fd);
			असल_hor = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'd':
			असल_hor = 20;
			ret = send_event(fd);
			असल_hor = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'w':
			असल_ver = -20;
			ret = send_event(fd);
			असल_ver = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 's':
			असल_ver = 20;
			ret = send_event(fd);
			असल_ver = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'r':
			wheel = 1;
			ret = send_event(fd);
			wheel = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'f':
			wheel = -1;
			ret = send_event(fd);
			wheel = 0;
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल 'q':
			वापस -ECANCELED;
		शेष:
			ख_लिखो(मानक_त्रुटि, "Invalid input: %c\n", buf[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd;
	स्थिर अक्षर *path = "/dev/uhid";
	काष्ठा pollfd pfds[2];
	पूर्णांक ret;
	काष्ठा termios state;

	ret = tcgetattr(STDIN_खाताNO, &state);
	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot get tty state\n");
	पूर्ण अन्यथा अणु
		state.c_lflag &= ~ICANON;
		state.c_cc[VMIN] = 1;
		ret = tcsetattr(STDIN_खाताNO, TCSANOW, &state);
		अगर (ret)
			ख_लिखो(मानक_त्रुटि, "Cannot set tty state\n");
	पूर्ण

	अगर (argc >= 2) अणु
		अगर (!म_भेद(argv[1], "-h") || !म_भेद(argv[1], "--help")) अणु
			ख_लिखो(मानक_त्रुटि, "Usage: %s [%s]\n", argv[0], path);
			वापस निकास_सफल;
		पूर्ण अन्यथा अणु
			path = argv[1];
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Open uhid-cdev %s\n", path);
	fd = खोलो(path, O_RDWR | O_CLOEXEC);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot open uhid-cdev %s: %m\n", path);
		वापस निकास_त्रुटि;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Create uhid device\n");
	ret = create(fd);
	अगर (ret) अणु
		बंद(fd);
		वापस निकास_त्रुटि;
	पूर्ण

	pfds[0].fd = STDIN_खाताNO;
	pfds[0].events = POLLIN;
	pfds[1].fd = fd;
	pfds[1].events = POLLIN;

	ख_लिखो(मानक_त्रुटि, "Press 'q' to quit...\n");
	जबतक (1) अणु
		ret = poll(pfds, 2, -1);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Cannot poll for fds: %m\n");
			अवरोध;
		पूर्ण
		अगर (pfds[0].revents & POLLHUP) अणु
			ख_लिखो(मानक_त्रुटि, "Received HUP on stdin\n");
			अवरोध;
		पूर्ण
		अगर (pfds[1].revents & POLLHUP) अणु
			ख_लिखो(मानक_त्रुटि, "Received HUP on uhid-cdev\n");
			अवरोध;
		पूर्ण

		अगर (pfds[0].revents & POLLIN) अणु
			ret = keyboard(fd);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (pfds[1].revents & POLLIN) अणु
			ret = event(fd);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Destroy uhid device\n");
	destroy(fd);
	वापस निकास_सफल;
पूर्ण
