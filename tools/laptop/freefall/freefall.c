<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Disk protection क्रम HP/DELL machines.
 *
 * Copyright 2008 Eric Piel
 * Copyright 2009 Pavel Machek <pavel@ucw.cz>
 * Copyright 2012 Sonal Santan
 * Copyright 2014 Pali Rohथँr <pali@kernel.org>
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <sched.h>
#समावेश <syslog.h>

अटल पूर्णांक noled;
अटल अक्षर unload_heads_path[64];
अटल अक्षर device_path[32];
अटल स्थिर अक्षर app_name[] = "FREE FALL";

अटल पूर्णांक set_unload_heads_path(अक्षर *device)
अणु
	अगर (म_माप(device) <= 5 || म_भेदन(device, "/dev/", 5) != 0)
		वापस -EINVAL;
	म_नकलन(device_path, device, माप(device_path) - 1);

	snम_लिखो(unload_heads_path, माप(unload_heads_path) - 1,
				"/sys/block/%s/device/unload_heads", device+5);
	वापस 0;
पूर्ण

अटल पूर्णांक valid_disk(व्योम)
अणु
	पूर्णांक fd = खोलो(unload_heads_path, O_RDONLY);

	अगर (fd < 0) अणु
		लिखो_त्रुटि(unload_heads_path);
		वापस 0;
	पूर्ण

	बंद(fd);
	वापस 1;
पूर्ण

अटल व्योम ग_लिखो_पूर्णांक(अक्षर *path, पूर्णांक i)
अणु
	अक्षर buf[1024];
	पूर्णांक fd = खोलो(path, O_RDWR);

	अगर (fd < 0) अणु
		लिखो_त्रुटि("open");
		निकास(1);
	पूर्ण

	प्र_लिखो(buf, "%d", i);

	अगर (ग_लिखो(fd, buf, म_माप(buf)) != म_माप(buf)) अणु
		लिखो_त्रुटि("write");
		निकास(1);
	पूर्ण

	बंद(fd);
पूर्ण

अटल व्योम set_led(पूर्णांक on)
अणु
	अगर (noled)
		वापस;
	ग_लिखो_पूर्णांक("/sys/class/leds/hp::hddprotect/brightness", on);
पूर्ण

अटल व्योम protect(पूर्णांक seconds)
अणु
	स्थिर अक्षर *str = (seconds == 0) ? "Unparked" : "Parked";

	ग_लिखो_पूर्णांक(unload_heads_path, seconds*1000);
	syslog(LOG_INFO, "%s %s disk head\n", str, device_path);
पूर्ण

अटल पूर्णांक on_ac(व्योम)
अणु
	/* /sys/class/घातer_supply/AC0/online */
	वापस 1;
पूर्ण

अटल पूर्णांक lid_खोलो(व्योम)
अणु
	/* /proc/acpi/button/lid/LID/state */
	वापस 1;
पूर्ण

अटल व्योम ignore_me(पूर्णांक signum)
अणु
	protect(0);
	set_led(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd, ret;
	काष्ठा stat st;
	काष्ठा sched_param param;

	अगर (argc == 1)
		ret = set_unload_heads_path("/dev/sda");
	अन्यथा अगर (argc == 2)
		ret = set_unload_heads_path(argv[1]);
	अन्यथा
		ret = -EINVAL;

	अगर (ret || !valid_disk()) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s <device> (default: /dev/sda)\n",
				argv[0]);
		निकास(1);
	पूर्ण

	fd = खोलो("/dev/freefall", O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("/dev/freefall");
		वापस निकास_त्रुटि;
	पूर्ण

	अगर (stat("/sys/class/leds/hp::hddprotect/brightness", &st))
		noled = 1;

	अगर (daemon(0, 0) != 0) अणु
		लिखो_त्रुटि("daemon");
		वापस निकास_त्रुटि;
	पूर्ण

	खोलोlog(app_name, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &param);
	mlockall(MCL_CURRENT|MCL_FUTURE);

	संकेत(SIGALRM, ignore_me);

	क्रम (;;) अणु
		अचिन्हित अक्षर count;

		ret = पढ़ो(fd, &count, माप(count));
		alarm(0);
		अगर ((ret == -1) && (त्रुटि_सं == EINTR)) अणु
			/* Alarm expired, समय to unpark the heads */
			जारी;
		पूर्ण

		अगर (ret != माप(count)) अणु
			लिखो_त्रुटि("read");
			अवरोध;
		पूर्ण

		protect(21);
		set_led(1);
		अगर (1 || on_ac() || lid_खोलो())
			alarm(2);
		अन्यथा
			alarm(20);
	पूर्ण

	बंदlog();
	बंद(fd);
	वापस निकास_सफल;
पूर्ण
