<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO tools - helpers library क्रम the GPIO tools
 *
 * Copyright (C) 2015 Linus Walleij
 * Copyright (C) 2016 Bamvor Jian Zhang
 */

#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <getopt.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/gpपन.स>
#समावेश "gpio-utils.h"

#घोषणा CONSUMER "gpio-utils"

/**
 * DOC: Operation of gpio
 *
 * Provide the api of gpiochip क्रम अक्षरdev पूर्णांकerface. There are two
 * types of api.  The first one provide as same function as each
 * ioctl, including request and release क्रम lines of gpio, पढ़ो/ग_लिखो
 * the value of gpio. If the user want to करो lots of पढ़ो and ग_लिखो of
 * lines of gpio, user should use this type of api.
 *
 * The second one provide the easy to use api क्रम user. Each of the
 * following api will request gpio lines, करो the operation and then
 * release these lines.
 */

/**
 * gpiotools_request_line() - request gpio lines in a gpiochip
 * @device_name:	The name of gpiochip without prefix "/dev/",
 *			such as "gpiochip0"
 * @lines:		An array desired lines, specअगरied by offset
 *			index क्रम the associated GPIO device.
 * @num_lines:		The number of lines to request.
 * @config:		The new config क्रम requested gpio. Reference
 *			"linux/gpio.h" क्रम config details.
 * @consumer:		The name of consumer, such as "sysfs",
 *			"powerkey". This is useful क्रम other users to
 *			know who is using.
 *
 * Request gpio lines through the ioctl provided by अक्षरdev. User
 * could call gpiotools_set_values() and gpiotools_get_values() to
 * पढ़ो and ग_लिखो respectively through the वापसed fd. Call
 * gpiotools_release_line() to release these lines after that.
 *
 * Return:		On success वापस the fd;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_request_line(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines,
			   अचिन्हित पूर्णांक num_lines,
			   काष्ठा gpio_v2_line_config *config,
			   स्थिर अक्षर *consumer)
अणु
	काष्ठा gpio_v2_line_request req;
	अक्षर *chrdev_name;
	पूर्णांक fd;
	पूर्णांक i;
	पूर्णांक ret;

	ret = aप्र_लिखो(&chrdev_name, "/dev/%s", device_name);
	अगर (ret < 0)
		वापस -ENOMEM;

	fd = खोलो(chrdev_name, 0);
	अगर (fd == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to open %s, %s\n",
			chrdev_name, म_त्रुटि(त्रुटि_सं));
		जाओ निकास_मुक्त_name;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	क्रम (i = 0; i < num_lines; i++)
		req.offsets[i] = lines[i];

	req.config = *config;
	म_नकल(req.consumer, consumer);
	req.num_lines = num_lines;

	ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &req);
	अगर (ret == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to issue %s (%d), %s\n",
			"GPIO_GET_LINE_IOCTL", ret, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	अगर (बंद(fd) == -1)
		लिखो_त्रुटि("Failed to close GPIO character device file");
निकास_मुक्त_name:
	मुक्त(chrdev_name);
	वापस ret < 0 ? ret : req.fd;
पूर्ण

/**
 * gpiotools_set_values() - Set the value of gpio(s)
 * @fd:			The fd वापसed by
 *			gpiotools_request_line().
 * @values:		The array of values want to set.
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_set_values(स्थिर पूर्णांक fd, काष्ठा gpio_v2_line_values *values)
अणु
	पूर्णांक ret;

	ret = ioctl(fd, GPIO_V2_LINE_SET_VALUES_IOCTL, values);
	अगर (ret == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to issue %s (%d), %s\n",
			"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret,
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * gpiotools_get_values() - Get the value of gpio(s)
 * @fd:			The fd वापसed by
 *			gpiotools_request_line().
 * @values:		The array of values get from hardware.
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_get_values(स्थिर पूर्णांक fd, काष्ठा gpio_v2_line_values *values)
अणु
	पूर्णांक ret;

	ret = ioctl(fd, GPIO_V2_LINE_GET_VALUES_IOCTL, values);
	अगर (ret == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to issue %s (%d), %s\n",
			"GPIOHANDLE_GET_LINE_VALUES_IOCTL", ret,
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * gpiotools_release_line() - Release the line(s) of gpiochip
 * @fd:			The fd वापसed by
 *			gpiotools_request_line().
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_release_line(स्थिर पूर्णांक fd)
अणु
	पूर्णांक ret;

	ret = बंद(fd);
	अगर (ret == -1) अणु
		लिखो_त्रुटि("Failed to close GPIO LINE device file");
		ret = -त्रुटि_सं;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * gpiotools_get() - Get value from specअगरic line
 * @device_name:	The name of gpiochip without prefix "/dev/",
 *			such as "gpiochip0"
 * @line:		number of line, such as 2.
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_get(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक line)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक lines[] = अणुlineपूर्ण;

	ret = gpiotools_माला_लो(device_name, lines, 1, &value);
	अगर (ret)
		वापस ret;
	वापस value;
पूर्ण


/**
 * gpiotools_माला_लो() - Get values from specअगरic lines.
 * @device_name:	The name of gpiochip without prefix "/dev/",
 *			such as "gpiochip0".
 * @lines:		An array desired lines, specअगरied by offset
 *			index क्रम the associated GPIO device.
 * @num_lines:		The number of lines to request.
 * @values:		The array of values get from gpiochip.
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_माला_लो(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines,
		   अचिन्हित पूर्णांक num_lines, अचिन्हित पूर्णांक *values)
अणु
	पूर्णांक fd, i;
	पूर्णांक ret;
	पूर्णांक ret_बंद;
	काष्ठा gpio_v2_line_config config;
	काष्ठा gpio_v2_line_values lv;

	स_रखो(&config, 0, माप(config));
	config.flags = GPIO_V2_LINE_FLAG_INPUT;
	ret = gpiotools_request_line(device_name, lines, num_lines,
				     &config, CONSUMER);
	अगर (ret < 0)
		वापस ret;

	fd = ret;
	क्रम (i = 0; i < num_lines; i++)
		gpiotools_set_bit(&lv.mask, i);
	ret = gpiotools_get_values(fd, &lv);
	अगर (!ret)
		क्रम (i = 0; i < num_lines; i++)
			values[i] = gpiotools_test_bit(lv.bits, i);
	ret_बंद = gpiotools_release_line(fd);
	वापस ret < 0 ? ret : ret_बंद;
पूर्ण

/**
 * gpiotools_set() - Set value to specअगरic line
 * @device_name:	The name of gpiochip without prefix "/dev/",
 *			such as "gpiochip0"
 * @line:		number of line, such as 2.
 * @value:		The value of gpio, must be 0(low) or 1(high).
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_set(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक line,
		  अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक lines[] = अणुlineपूर्ण;

	वापस gpiotools_sets(device_name, lines, 1, &value);
पूर्ण

/**
 * gpiotools_sets() - Set values to specअगरic lines.
 * @device_name:	The name of gpiochip without prefix "/dev/",
 *			such as "gpiochip0".
 * @lines:		An array desired lines, specअगरied by offset
 *			index क्रम the associated GPIO device.
 * @num_lines:		The number of lines to request.
 * @values:		The array of values set to gpiochip, must be
 *			0(low) or 1(high).
 *
 * Return:		On success वापस 0;
 *			On failure वापस the त्रुटि_सं.
 */
पूर्णांक gpiotools_sets(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines,
		   अचिन्हित पूर्णांक num_lines, अचिन्हित पूर्णांक *values)
अणु
	पूर्णांक ret, i;
	काष्ठा gpio_v2_line_config config;

	स_रखो(&config, 0, माप(config));
	config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
	config.num_attrs = 1;
	config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES;
	क्रम (i = 0; i < num_lines; i++) अणु
		gpiotools_set_bit(&config.attrs[0].mask, i);
		gpiotools_assign_bit(&config.attrs[0].attr.values,
				     i, values[i]);
	पूर्ण
	ret = gpiotools_request_line(device_name, lines, num_lines,
				     &config, CONSUMER);
	अगर (ret < 0)
		वापस ret;

	वापस gpiotools_release_line(ret);
पूर्ण
