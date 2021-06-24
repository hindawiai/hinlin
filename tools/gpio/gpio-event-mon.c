<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio-event-mon - monitor GPIO line events from userspace
 *
 * Copyright (C) 2016 Linus Walleij
 *
 * Usage:
 *	gpio-event-mon -n <device-name> -o <offset>
 */

#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <poll.h>
#समावेश <fcntl.h>
#समावेश <getopt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/types.h>
#समावेश <linux/gpपन.स>
#समावेश "gpio-utils.h"

पूर्णांक monitor_device(स्थिर अक्षर *device_name,
		   अचिन्हित पूर्णांक *lines,
		   अचिन्हित पूर्णांक num_lines,
		   काष्ठा gpio_v2_line_config *config,
		   अचिन्हित पूर्णांक loops)
अणु
	काष्ठा gpio_v2_line_values values;
	अक्षर *chrdev_name;
	पूर्णांक cfd, lfd;
	पूर्णांक ret;
	पूर्णांक i = 0;

	ret = aप्र_लिखो(&chrdev_name, "/dev/%s", device_name);
	अगर (ret < 0)
		वापस -ENOMEM;

	cfd = खोलो(chrdev_name, 0);
	अगर (cfd == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to open %s\n", chrdev_name);
		जाओ निकास_मुक्त_name;
	पूर्ण

	ret = gpiotools_request_line(device_name, lines, num_lines, config,
				     "gpio-event-mon");
	अगर (ret < 0)
		जाओ निकास_device_बंद;
	अन्यथा
		lfd = ret;

	/* Read initial states */
	values.mask = 0;
	values.bits = 0;
	क्रम (i = 0; i < num_lines; i++)
		gpiotools_set_bit(&values.mask, i);
	ret = gpiotools_get_values(lfd, &values);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि,
			"Failed to issue GPIO LINE GET VALUES IOCTL (%d)\n",
			ret);
		जाओ निकास_line_बंद;
	पूर्ण

	अगर (num_lines == 1) अणु
		ख_लिखो(मानक_निकास, "Monitoring line %d on %s\n", lines[0], device_name);
		ख_लिखो(मानक_निकास, "Initial line value: %d\n",
			gpiotools_test_bit(values.bits, 0));
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_निकास, "Monitoring lines %d", lines[0]);
		क्रम (i = 1; i < num_lines - 1; i++)
			ख_लिखो(मानक_निकास, ", %d", lines[i]);
		ख_लिखो(मानक_निकास, " and %d on %s\n", lines[i], device_name);
		ख_लिखो(मानक_निकास, "Initial line values: %d",
			gpiotools_test_bit(values.bits, 0));
		क्रम (i = 1; i < num_lines - 1; i++)
			ख_लिखो(मानक_निकास, ", %d",
				gpiotools_test_bit(values.bits, i));
		ख_लिखो(मानक_निकास, " and %d\n",
			gpiotools_test_bit(values.bits, i));
	पूर्ण

	जबतक (1) अणु
		काष्ठा gpio_v2_line_event event;

		ret = पढ़ो(lfd, &event, माप(event));
		अगर (ret == -1) अणु
			अगर (त्रुटि_सं == -EAGAIN) अणु
				ख_लिखो(मानक_त्रुटि, "nothing available\n");
				जारी;
			पूर्ण अन्यथा अणु
				ret = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि, "Failed to read event (%d)\n",
					ret);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret != माप(event)) अणु
			ख_लिखो(मानक_त्रुटि, "Reading event failed\n");
			ret = -EIO;
			अवरोध;
		पूर्ण
		ख_लिखो(मानक_निकास, "GPIO EVENT at %" PRIu64 " on line %d (%d|%d) ",
			(uपूर्णांक64_t)event.बारtamp_ns, event.offset, event.line_seqno,
			event.seqno);
		चयन (event.id) अणु
		हाल GPIO_V2_LINE_EVENT_RISING_EDGE:
			ख_लिखो(मानक_निकास, "rising edge");
			अवरोध;
		हाल GPIO_V2_LINE_EVENT_FALLING_EDGE:
			ख_लिखो(मानक_निकास, "falling edge");
			अवरोध;
		शेष:
			ख_लिखो(मानक_निकास, "unknown event");
		पूर्ण
		ख_लिखो(मानक_निकास, "\n");

		i++;
		अगर (i == loops)
			अवरोध;
	पूर्ण

निकास_line_बंद:
	अगर (बंद(lfd) == -1)
		लिखो_त्रुटि("Failed to close line file");
निकास_device_बंद:
	अगर (बंद(cfd) == -1)
		लिखो_त्रुटि("Failed to close GPIO character device file");
निकास_मुक्त_name:
	मुक्त(chrdev_name);
	वापस ret;
पूर्ण

व्योम prपूर्णांक_usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: gpio-event-mon [options]...\n"
		"Listen to events on GPIO lines, 0->1 1->0\n"
		"  -n <name>  Listen on GPIOs on a named device (must be stated)\n"
		"  -o <n>     Offset of line to monitor (may be repeated)\n"
		"  -d         Set line as open drain\n"
		"  -s         Set line as open source\n"
		"  -r         Listen for rising edges\n"
		"  -f         Listen for falling edges\n"
		"  -w         Report the wall-clock time for events\n"
		"  -b <n>     Debounce the line with period n microseconds\n"
		" [-c <n>]    Do <n> loops (optional, infinite loop if not stated)\n"
		"  -?         This helptext\n"
		"\n"
		"Example:\n"
		"gpio-event-mon -n gpiochip0 -o 4 -r -f -b 10000\n"
	);
पूर्ण

#घोषणा EDGE_FLAGS \
	(GPIO_V2_LINE_FLAG_EDGE_RISING | \
	 GPIO_V2_LINE_FLAG_EDGE_FALLING)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *device_name = शून्य;
	अचिन्हित पूर्णांक lines[GPIO_V2_LINES_MAX];
	अचिन्हित पूर्णांक num_lines = 0;
	अचिन्हित पूर्णांक loops = 0;
	काष्ठा gpio_v2_line_config config;
	पूर्णांक c, attr, i;
	अचिन्हित दीर्घ debounce_period_us = 0;

	स_रखो(&config, 0, माप(config));
	config.flags = GPIO_V2_LINE_FLAG_INPUT;
	जबतक ((c = getopt(argc, argv, "c:n:o:b:dsrfw?")) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			loops = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'n':
			device_name = optarg;
			अवरोध;
		हाल 'o':
			अगर (num_lines >= GPIO_V2_LINES_MAX) अणु
				prपूर्णांक_usage();
				वापस -1;
			पूर्ण
			lines[num_lines] = म_से_अदीर्घ(optarg, शून्य, 10);
			num_lines++;
			अवरोध;
		हाल 'b':
			debounce_period_us = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'd':
			config.flags |= GPIO_V2_LINE_FLAG_OPEN_DRAIN;
			अवरोध;
		हाल 's':
			config.flags |= GPIO_V2_LINE_FLAG_OPEN_SOURCE;
			अवरोध;
		हाल 'r':
			config.flags |= GPIO_V2_LINE_FLAG_EDGE_RISING;
			अवरोध;
		हाल 'f':
			config.flags |= GPIO_V2_LINE_FLAG_EDGE_FALLING;
			अवरोध;
		हाल 'w':
			config.flags |= GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME;
			अवरोध;
		हाल '?':
			prपूर्णांक_usage();
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (debounce_period_us) अणु
		attr = config.num_attrs;
		config.num_attrs++;
		क्रम (i = 0; i < num_lines; i++)
			gpiotools_set_bit(&config.attrs[attr].mask, i);
		config.attrs[attr].attr.id = GPIO_V2_LINE_ATTR_ID_DEBOUNCE;
		config.attrs[attr].attr.debounce_period_us = debounce_period_us;
	पूर्ण

	अगर (!device_name || num_lines == 0) अणु
		prपूर्णांक_usage();
		वापस -1;
	पूर्ण
	अगर (!(config.flags & EDGE_FLAGS)) अणु
		म_लिखो("No flags specified, listening on both rising and "
		       "falling edges\n");
		config.flags |= EDGE_FLAGS;
	पूर्ण
	वापस monitor_device(device_name, lines, num_lines, &config, loops);
पूर्ण
