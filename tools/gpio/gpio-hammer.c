<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio-hammer - example swiss army knअगरe to shake GPIO lines on a प्रणाली
 *
 * Copyright (C) 2016 Linus Walleij
 *
 * Usage:
 *	gpio-hammer -n <device-name> -o <offset1> -o <offset2>
 */

#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <poll.h>
#समावेश <fcntl.h>
#समावेश <getopt.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/gpपन.स>
#समावेश "gpio-utils.h"

पूर्णांक hammer_device(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines, पूर्णांक num_lines,
		  अचिन्हित पूर्णांक loops)
अणु
	काष्ठा gpio_v2_line_values values;
	काष्ठा gpio_v2_line_config config;
	अक्षर swirr[] = "-\\|/";
	पूर्णांक fd;
	पूर्णांक ret;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक iteration = 0;

	स_रखो(&config, 0, माप(config));
	config.flags = GPIO_V2_LINE_FLAG_OUTPUT;

	ret = gpiotools_request_line(device_name, lines, num_lines,
				     &config, "gpio-hammer");
	अगर (ret < 0)
		जाओ निकास_error;
	अन्यथा
		fd = ret;

	values.mask = 0;
	values.bits = 0;
	क्रम (i = 0; i < num_lines; i++)
		gpiotools_set_bit(&values.mask, i);

	ret = gpiotools_get_values(fd, &values);
	अगर (ret < 0)
		जाओ निकास_बंद_error;

	ख_लिखो(मानक_निकास, "Hammer lines [");
	क्रम (i = 0; i < num_lines; i++) अणु
		ख_लिखो(मानक_निकास, "%d", lines[i]);
		अगर (i != (num_lines - 1))
			ख_लिखो(मानक_निकास, ", ");
	पूर्ण
	ख_लिखो(मानक_निकास, "] on %s, initial states: [", device_name);
	क्रम (i = 0; i < num_lines; i++) अणु
		ख_लिखो(मानक_निकास, "%d", gpiotools_test_bit(values.bits, i));
		अगर (i != (num_lines - 1))
			ख_लिखो(मानक_निकास, ", ");
	पूर्ण
	ख_लिखो(मानक_निकास, "]\n");

	/* Hammerसमय! */
	j = 0;
	जबतक (1) अणु
		/* Invert all lines so we blink */
		क्रम (i = 0; i < num_lines; i++)
			gpiotools_change_bit(&values.bits, i);

		ret = gpiotools_set_values(fd, &values);
		अगर (ret < 0)
			जाओ निकास_बंद_error;

		/* Re-पढ़ो values to get status */
		ret = gpiotools_get_values(fd, &values);
		अगर (ret < 0)
			जाओ निकास_बंद_error;

		ख_लिखो(मानक_निकास, "[%c] ", swirr[j]);
		j++;
		अगर (j == माप(swirr) - 1)
			j = 0;

		ख_लिखो(मानक_निकास, "[");
		क्रम (i = 0; i < num_lines; i++) अणु
			ख_लिखो(मानक_निकास, "%d: %d", lines[i],
				gpiotools_test_bit(values.bits, i));
			अगर (i != (num_lines - 1))
				ख_लिखो(मानक_निकास, ", ");
		पूर्ण
		ख_लिखो(मानक_निकास, "]\r");
		ख_साफ(मानक_निकास);
		sleep(1);
		iteration++;
		अगर (loops && iteration == loops)
			अवरोध;
	पूर्ण
	ख_लिखो(मानक_निकास, "\n");
	ret = 0;

निकास_बंद_error:
	gpiotools_release_line(fd);
निकास_error:
	वापस ret;
पूर्ण

व्योम prपूर्णांक_usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: gpio-hammer [options]...\n"
		"Hammer GPIO lines, 0->1->0->1...\n"
		"  -n <name>  Hammer GPIOs on a named device (must be stated)\n"
		"  -o <n>     Offset[s] to hammer, at least one, several can be stated\n"
		" [-c <n>]    Do <n> loops (optional, infinite loop if not stated)\n"
		"  -?         This helptext\n"
		"\n"
		"Example:\n"
		"gpio-hammer -n gpiochip0 -o 4\n"
	);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *device_name = शून्य;
	अचिन्हित पूर्णांक lines[GPIOHANDLES_MAX];
	अचिन्हित पूर्णांक loops = 0;
	पूर्णांक num_lines;
	पूर्णांक c;
	पूर्णांक i;

	i = 0;
	जबतक ((c = getopt(argc, argv, "c:n:o:?")) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			loops = म_से_अदीर्घ(optarg, शून्य, 10);
			अवरोध;
		हाल 'n':
			device_name = optarg;
			अवरोध;
		हाल 'o':
			/*
			 * Aव्योम overflow. Do not immediately error, we want to
			 * be able to accurately report on the amount of बार
			 * '-o' was given to give an accurate error message
			 */
			अगर (i < GPIOHANDLES_MAX)
				lines[i] = म_से_अदीर्घ(optarg, शून्य, 10);

			i++;
			अवरोध;
		हाल '?':
			prपूर्णांक_usage();
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (i >= GPIOHANDLES_MAX) अणु
		ख_लिखो(मानक_त्रुटि,
			"Only %d occurrences of '-o' are allowed, %d were found\n",
			GPIOHANDLES_MAX, i + 1);
		वापस -1;
	पूर्ण

	num_lines = i;

	अगर (!device_name || !num_lines) अणु
		prपूर्णांक_usage();
		वापस -1;
	पूर्ण
	वापस hammer_device(device_name, lines, num_lines, loops);
पूर्ण
