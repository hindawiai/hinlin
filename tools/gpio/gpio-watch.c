<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * gpio-watch - monitor unrequested lines क्रम property changes using the
 *              अक्षरacter device
 *
 * Copyright (C) 2019 BayLibre SAS
 * Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/gpपन.स>
#समावेश <poll.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <unistd.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा gpio_v2_line_info_changed chg;
	काष्ठा gpio_v2_line_info req;
	काष्ठा pollfd pfd;
	पूर्णांक fd, i, j, ret;
	अक्षर *event, *end;
	sमाप_प्रकार rd;

	अगर (argc < 3)
		जाओ err_usage;

	fd = खोलो(argv[1], O_RDWR | O_CLOEXEC);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("unable to open gpiochip");
		वापस निकास_त्रुटि;
	पूर्ण

	क्रम (i = 0, j = 2; i < argc - 2; i++, j++) अणु
		स_रखो(&req, 0, माप(req));

		req.offset = म_से_अदीर्घ(argv[j], &end, 0);
		अगर (*end != '\0')
			जाओ err_usage;

		ret = ioctl(fd, GPIO_V2_GET_LINEINFO_WATCH_IOCTL, &req);
		अगर (ret) अणु
			लिखो_त्रुटि("unable to set up line watch");
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण

	pfd.fd = fd;
	pfd.events = POLLIN | POLLPRI;

	क्रम (;;) अणु
		ret = poll(&pfd, 1, 5000);
		अगर (ret < 0) अणु
			लिखो_त्रुटि("error polling the linechanged fd");
			वापस निकास_त्रुटि;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			स_रखो(&chg, 0, माप(chg));
			rd = पढ़ो(pfd.fd, &chg, माप(chg));
			अगर (rd < 0 || rd != माप(chg)) अणु
				अगर (rd != माप(chg))
					त्रुटि_सं = EIO;

				लिखो_त्रुटि("error reading line change event");
				वापस निकास_त्रुटि;
			पूर्ण

			चयन (chg.event_type) अणु
			हाल GPIO_V2_LINE_CHANGED_REQUESTED:
				event = "requested";
				अवरोध;
			हाल GPIO_V2_LINE_CHANGED_RELEASED:
				event = "released";
				अवरोध;
			हाल GPIO_V2_LINE_CHANGED_CONFIG:
				event = "config changed";
				अवरोध;
			शेष:
				ख_लिखो(मानक_त्रुटि,
					"invalid event type received from the kernel\n");
				वापस निकास_त्रुटि;
			पूर्ण

			म_लिखो("line %u: %s at %" PRIu64 "\n",
			       chg.info.offset, event, (uपूर्णांक64_t)chg.बारtamp_ns);
		पूर्ण
	पूर्ण

	वापस 0;

err_usage:
	म_लिखो("%s: <gpiochip> <line0> <line1> ...\n", argv[0]);
	वापस निकास_त्रुटि;
पूर्ण
