<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cgroup_event_listener.c - Simple listener of cgroup events
 *
 * Copyright (C) Kirill A. Shutemov <kirill@shutemov.name>
 */

#समावेश <निश्चित.स>
#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <libgen.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <sys/eventfd.h>

#घोषणा USAGE_STR "Usage: cgroup_event_listener <path-to-control-file> <args>"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक efd = -1;
	पूर्णांक cfd = -1;
	पूर्णांक event_control = -1;
	अक्षर event_control_path[PATH_MAX];
	अक्षर line[LINE_MAX];
	पूर्णांक ret;

	अगर (argc != 3)
		errx(1, "%s", USAGE_STR);

	cfd = खोलो(argv[1], O_RDONLY);
	अगर (cfd == -1)
		err(1, "Cannot open %s", argv[1]);

	ret = snम_लिखो(event_control_path, PATH_MAX, "%s/cgroup.event_control",
			स_नाम(argv[1]));
	अगर (ret >= PATH_MAX)
		errx(1, "Path to cgroup.event_control is too long");

	event_control = खोलो(event_control_path, O_WRONLY);
	अगर (event_control == -1)
		err(1, "Cannot open %s", event_control_path);

	efd = eventfd(0, 0);
	अगर (efd == -1)
		err(1, "eventfd() failed");

	ret = snम_लिखो(line, LINE_MAX, "%d %d %s", efd, cfd, argv[2]);
	अगर (ret >= LINE_MAX)
		errx(1, "Arguments string is too long");

	ret = ग_लिखो(event_control, line, म_माप(line) + 1);
	अगर (ret == -1)
		err(1, "Cannot write to cgroup.event_control");

	जबतक (1) अणु
		uपूर्णांक64_t result;

		ret = पढ़ो(efd, &result, माप(result));
		अगर (ret == -1) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			err(1, "Cannot read from eventfd");
		पूर्ण
		निश्चित(ret == माप(result));

		ret = access(event_control_path, W_OK);
		अगर ((ret == -1) && (त्रुटि_सं == ENOENT)) अणु
			माला_दो("The cgroup seems to have removed.");
			अवरोध;
		पूर्ण

		अगर (ret == -1)
			err(1, "cgroup.event_control is not accessible any more");

		म_लिखो("%s %s: crossed\n", argv[1], argv[2]);
	पूर्ण

	वापस 0;
पूर्ण
