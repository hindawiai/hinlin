<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO mockup cdev test helper
 *
 * Copyright (C) 2020 Kent Gibson
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/gpपन.स>

#घोषणा CONSUMER	"gpio-mockup-cdev"

अटल पूर्णांक request_line_v2(पूर्णांक cfd, अचिन्हित पूर्णांक offset,
			   uपूर्णांक64_t flags, अचिन्हित पूर्णांक val)
अणु
	काष्ठा gpio_v2_line_request req;
	पूर्णांक ret;

	स_रखो(&req, 0, माप(req));
	req.num_lines = 1;
	req.offsets[0] = offset;
	req.config.flags = flags;
	म_नकल(req.consumer, CONSUMER);
	अगर (flags & GPIO_V2_LINE_FLAG_OUTPUT) अणु
		req.config.num_attrs = 1;
		req.config.attrs[0].mask = 1;
		req.config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES;
		अगर (val)
			req.config.attrs[0].attr.values = 1;
	पूर्ण
	ret = ioctl(cfd, GPIO_V2_GET_LINE_IOCTL, &req);
	अगर (ret == -1)
		वापस -त्रुटि_सं;
	वापस req.fd;
पूर्ण


अटल पूर्णांक get_value_v2(पूर्णांक lfd)
अणु
	काष्ठा gpio_v2_line_values vals;
	पूर्णांक ret;

	स_रखो(&vals, 0, माप(vals));
	vals.mask = 1;
	ret = ioctl(lfd, GPIO_V2_LINE_GET_VALUES_IOCTL, &vals);
	अगर (ret == -1)
		वापस -त्रुटि_सं;
	वापस vals.bits & 0x1;
पूर्ण

अटल पूर्णांक request_line_v1(पूर्णांक cfd, अचिन्हित पूर्णांक offset,
			   uपूर्णांक32_t flags, अचिन्हित पूर्णांक val)
अणु
	काष्ठा gpiohandle_request req;
	पूर्णांक ret;

	स_रखो(&req, 0, माप(req));
	req.lines = 1;
	req.lineoffsets[0] = offset;
	req.flags = flags;
	म_नकल(req.consumer_label, CONSUMER);
	अगर (flags & GPIOHANDLE_REQUEST_OUTPUT)
		req.शेष_values[0] = val;

	ret = ioctl(cfd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	अगर (ret == -1)
		वापस -त्रुटि_सं;
	वापस req.fd;
पूर्ण

अटल पूर्णांक get_value_v1(पूर्णांक lfd)
अणु
	काष्ठा gpiohandle_data vals;
	पूर्णांक ret;

	स_रखो(&vals, 0, माप(vals));
	ret = ioctl(lfd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &vals);
	अगर (ret == -1)
		वापस -त्रुटि_सं;
	वापस vals.values[0];
पूर्ण

अटल व्योम usage(अक्षर *prog)
अणु
	म_लिखो("Usage: %s [-l] [-b <bias>] [-s <value>] [-u <uAPI>] <gpiochip> <offset>\n", prog);
	म_लिखो("        -b: set line bias to one of pull-down, pull-up, disabled\n");
	म_लिखो("               (default is to leave bias unchanged):\n");
	म_लिखो("        -l: set line active low (default is active high)\n");
	म_लिखो("        -s: set line value (default is to get line value)\n");
	म_लिखो("        -u: uAPI version to use (default is 2)\n");
	निकास(-1);
पूर्ण

अटल पूर्णांक रुको_संकेत(व्योम)
अणु
	पूर्णांक sig;
	sigset_t wset;

	sigemptyset(&wset);
	sigaddset(&wset, SIGHUP);
	sigaddset(&wset, संक_विघ्न);
	sigaddset(&wset, संक_इति);
	sigरुको(&wset, &sig);

	वापस sig;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर *chip;
	पूर्णांक opt, ret, cfd, lfd;
	अचिन्हित पूर्णांक offset, val, abiv;
	uपूर्णांक32_t flags_v1;
	uपूर्णांक64_t flags_v2;

	abiv = 2;
	ret = 0;
	flags_v1 = GPIOHANDLE_REQUEST_INPUT;
	flags_v2 = GPIO_V2_LINE_FLAG_INPUT;

	जबतक ((opt = getopt(argc, argv, "lb:s:u:")) != -1) अणु
		चयन (opt) अणु
		हाल 'l':
			flags_v1 |= GPIOHANDLE_REQUEST_ACTIVE_LOW;
			flags_v2 |= GPIO_V2_LINE_FLAG_ACTIVE_LOW;
			अवरोध;
		हाल 'b':
			अगर (म_भेद("pull-up", optarg) == 0) अणु
				flags_v1 |= GPIOHANDLE_REQUEST_BIAS_PULL_UP;
				flags_v2 |= GPIO_V2_LINE_FLAG_BIAS_PULL_UP;
			पूर्ण अन्यथा अगर (म_भेद("pull-down", optarg) == 0) अणु
				flags_v1 |= GPIOHANDLE_REQUEST_BIAS_PULL_DOWN;
				flags_v2 |= GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN;
			पूर्ण अन्यथा अगर (म_भेद("disabled", optarg) == 0) अणु
				flags_v1 |= GPIOHANDLE_REQUEST_BIAS_DISABLE;
				flags_v2 |= GPIO_V2_LINE_FLAG_BIAS_DISABLED;
			पूर्ण
			अवरोध;
		हाल 's':
			val = म_से_प(optarg);
			flags_v1 &= ~GPIOHANDLE_REQUEST_INPUT;
			flags_v1 |= GPIOHANDLE_REQUEST_OUTPUT;
			flags_v2 &= ~GPIO_V2_LINE_FLAG_INPUT;
			flags_v2 |= GPIO_V2_LINE_FLAG_OUTPUT;
			अवरोध;
		हाल 'u':
			abiv = म_से_प(optarg);
			अवरोध;
		शेष:
			usage(argv[0]);
		पूर्ण
	पूर्ण

	अगर (argc < optind + 2)
		usage(argv[0]);

	chip = argv[optind];
	offset = म_से_प(argv[optind + 1]);

	cfd = खोलो(chip, 0);
	अगर (cfd == -1) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open %s: %s\n", chip, म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (abiv == 1)
		lfd = request_line_v1(cfd, offset, flags_v1, val);
	अन्यथा
		lfd = request_line_v2(cfd, offset, flags_v2, val);

	बंद(cfd);

	अगर (lfd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to request %s:%d: %s\n", chip, offset, म_त्रुटि(-lfd));
		वापस lfd;
	पूर्ण

	अगर (flags_v2 & GPIO_V2_LINE_FLAG_OUTPUT) अणु
		रुको_संकेत();
	पूर्ण अन्यथा अणु
		अगर (abiv == 1)
			ret = get_value_v1(lfd);
		अन्यथा
			ret = get_value_v2(lfd);
	पूर्ण

	बंद(lfd);

	वापस ret;
पूर्ण
