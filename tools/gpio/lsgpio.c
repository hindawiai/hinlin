<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lsgpio - example on how to list the GPIO lines on a प्रणाली
 *
 * Copyright (C) 2015 Linus Walleij
 *
 * Usage:
 *	lsgpio <-n device-name>
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

काष्ठा gpio_flag अणु
	अक्षर *name;
	अचिन्हित दीर्घ दीर्घ mask;
पूर्ण;

काष्ठा gpio_flag flagnames[] = अणु
	अणु
		.name = "used",
		.mask = GPIO_V2_LINE_FLAG_USED,
	पूर्ण,
	अणु
		.name = "input",
		.mask = GPIO_V2_LINE_FLAG_INPUT,
	पूर्ण,
	अणु
		.name = "output",
		.mask = GPIO_V2_LINE_FLAG_OUTPUT,
	पूर्ण,
	अणु
		.name = "active-low",
		.mask = GPIO_V2_LINE_FLAG_ACTIVE_LOW,
	पूर्ण,
	अणु
		.name = "open-drain",
		.mask = GPIO_V2_LINE_FLAG_OPEN_DRAIN,
	पूर्ण,
	अणु
		.name = "open-source",
		.mask = GPIO_V2_LINE_FLAG_OPEN_SOURCE,
	पूर्ण,
	अणु
		.name = "pull-up",
		.mask = GPIO_V2_LINE_FLAG_BIAS_PULL_UP,
	पूर्ण,
	अणु
		.name = "pull-down",
		.mask = GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN,
	पूर्ण,
	अणु
		.name = "bias-disabled",
		.mask = GPIO_V2_LINE_FLAG_BIAS_DISABLED,
	पूर्ण,
	अणु
		.name = "clock-realtime",
		.mask = GPIO_V2_LINE_FLAG_EVENT_CLOCK_REALTIME,
	पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_attributes(काष्ठा gpio_v2_line_info *info)
अणु
	पूर्णांक i;
	स्थिर अक्षर *field_क्रमmat = "%s";

	क्रम (i = 0; i < ARRAY_SIZE(flagnames); i++) अणु
		अगर (info->flags & flagnames[i].mask) अणु
			ख_लिखो(मानक_निकास, field_क्रमmat, flagnames[i].name);
			field_क्रमmat = ", %s";
		पूर्ण
	पूर्ण

	अगर ((info->flags & GPIO_V2_LINE_FLAG_EDGE_RISING) &&
	    (info->flags & GPIO_V2_LINE_FLAG_EDGE_FALLING))
		ख_लिखो(मानक_निकास, field_क्रमmat, "both-edges");
	अन्यथा अगर (info->flags & GPIO_V2_LINE_FLAG_EDGE_RISING)
		ख_लिखो(मानक_निकास, field_क्रमmat, "rising-edge");
	अन्यथा अगर (info->flags & GPIO_V2_LINE_FLAG_EDGE_FALLING)
		ख_लिखो(मानक_निकास, field_क्रमmat, "falling-edge");

	क्रम (i = 0; i < info->num_attrs; i++) अणु
		अगर (info->attrs[i].id == GPIO_V2_LINE_ATTR_ID_DEBOUNCE)
			ख_लिखो(मानक_निकास, ", debounce_period=%dusec",
				info->attrs[0].debounce_period_us);
	पूर्ण
पूर्ण

पूर्णांक list_device(स्थिर अक्षर *device_name)
अणु
	काष्ठा gpiochip_info cinfo;
	अक्षर *chrdev_name;
	पूर्णांक fd;
	पूर्णांक ret;
	पूर्णांक i;

	ret = aप्र_लिखो(&chrdev_name, "/dev/%s", device_name);
	अगर (ret < 0)
		वापस -ENOMEM;

	fd = खोलो(chrdev_name, 0);
	अगर (fd == -1) अणु
		ret = -त्रुटि_सं;
		ख_लिखो(मानक_त्रुटि, "Failed to open %s\n", chrdev_name);
		जाओ निकास_मुक्त_name;
	पूर्ण

	/* Inspect this GPIO chip */
	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
	अगर (ret == -1) अणु
		ret = -त्रुटि_सं;
		लिखो_त्रुटि("Failed to issue CHIPINFO IOCTL\n");
		जाओ निकास_बंद_error;
	पूर्ण
	ख_लिखो(मानक_निकास, "GPIO chip: %s, \"%s\", %u GPIO lines\n",
		cinfo.name, cinfo.label, cinfo.lines);

	/* Loop over the lines and prपूर्णांक info */
	क्रम (i = 0; i < cinfo.lines; i++) अणु
		काष्ठा gpio_v2_line_info linfo;

		स_रखो(&linfo, 0, माप(linfo));
		linfo.offset = i;

		ret = ioctl(fd, GPIO_V2_GET_LINEINFO_IOCTL, &linfo);
		अगर (ret == -1) अणु
			ret = -त्रुटि_सं;
			लिखो_त्रुटि("Failed to issue LINEINFO IOCTL\n");
			जाओ निकास_बंद_error;
		पूर्ण
		ख_लिखो(मानक_निकास, "\tline %2d:", linfo.offset);
		अगर (linfo.name[0])
			ख_लिखो(मानक_निकास, " \"%s\"", linfo.name);
		अन्यथा
			ख_लिखो(मानक_निकास, " unnamed");
		अगर (linfo.consumer[0])
			ख_लिखो(मानक_निकास, " \"%s\"", linfo.consumer);
		अन्यथा
			ख_लिखो(मानक_निकास, " unused");
		अगर (linfo.flags) अणु
			ख_लिखो(मानक_निकास, " [");
			prपूर्णांक_attributes(&linfo);
			ख_लिखो(मानक_निकास, "]");
		पूर्ण
		ख_लिखो(मानक_निकास, "\n");

	पूर्ण

निकास_बंद_error:
	अगर (बंद(fd) == -1)
		लिखो_त्रुटि("Failed to close GPIO character device file");
निकास_मुक्त_name:
	मुक्त(chrdev_name);
	वापस ret;
पूर्ण

व्योम prपूर्णांक_usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: lsgpio [options]...\n"
		"List GPIO chips, lines and states\n"
		"  -n <name>  List GPIOs on a named device\n"
		"  -?         This helptext\n"
	);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *device_name = शून्य;
	पूर्णांक ret;
	पूर्णांक c;

	जबतक ((c = getopt(argc, argv, "n:")) != -1) अणु
		चयन (c) अणु
		हाल 'n':
			device_name = optarg;
			अवरोध;
		हाल '?':
			prपूर्णांक_usage();
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (device_name)
		ret = list_device(device_name);
	अन्यथा अणु
		स्थिर काष्ठा dirent *ent;
		सूची *dp;

		/* List all GPIO devices one at a समय */
		dp = सूची_खोलो("/dev");
		अगर (!dp) अणु
			ret = -त्रुटि_सं;
			जाओ error_out;
		पूर्ण

		ret = -ENOENT;
		जबतक (ent = सूची_पढ़ो(dp), ent) अणु
			अगर (check_prefix(ent->d_name, "gpiochip")) अणु
				ret = list_device(ent->d_name);
				अगर (ret)
					अवरोध;
			पूर्ण
		पूर्ण

		ret = 0;
		अगर (बंद_सूची(dp) == -1) अणु
			लिखो_त्रुटि("scanning devices: Failed to close directory");
			ret = -त्रुटि_सं;
		पूर्ण
	पूर्ण
error_out:
	वापस ret;
पूर्ण
