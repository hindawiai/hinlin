<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <memory.h>
#समावेश <दो_स्मृति.h>
#समावेश <समय.स>
#समावेश <प्रकार.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/समय.स>
#समावेश <linux/hpet.h>


बाह्य व्योम hpet_खोलो_बंद(पूर्णांक, स्थिर अक्षर **);
बाह्य व्योम hpet_info(पूर्णांक, स्थिर अक्षर **);
बाह्य व्योम hpet_poll(पूर्णांक, स्थिर अक्षर **);
बाह्य व्योम hpet_fasync(पूर्णांक, स्थिर अक्षर **);
बाह्य व्योम hpet_पढ़ो(पूर्णांक, स्थिर अक्षर **);

#समावेश <sys/poll.h>
#समावेश <sys/ioctl.h>

काष्ठा hpet_command अणु
	अक्षर		*command;
	व्योम		(*func)(पूर्णांक argc, स्थिर अक्षर ** argv);
पूर्ण hpet_command[] = अणु
	अणु
		"open-close",
		hpet_खोलो_बंद
	पूर्ण,
	अणु
		"info",
		hpet_info
	पूर्ण,
	अणु
		"poll",
		hpet_poll
	पूर्ण,
	अणु
		"fasync",
		hpet_fasync
	पूर्ण,
पूर्ण;

पूर्णांक
मुख्य(पूर्णांक argc, स्थिर अक्षर ** argv)
अणु
	अचिन्हित पूर्णांक	i;

	argc--;
	argv++;

	अगर (!argc) अणु
		ख_लिखो(मानक_त्रुटि, "-hpet: requires command\n");
		वापस -1;
	पूर्ण


	क्रम (i = 0; i < (माप (hpet_command) / माप (hpet_command[0])); i++)
		अगर (!म_भेद(argv[0], hpet_command[i].command)) अणु
			argc--;
			argv++;
			ख_लिखो(मानक_त्रुटि, "-hpet: executing %s\n",
				hpet_command[i].command);
			hpet_command[i].func(argc, argv);
			वापस 0;
		पूर्ण

	ख_लिखो(मानक_त्रुटि, "do_hpet: command %s not implemented\n", argv[0]);

	वापस -1;
पूर्ण

व्योम
hpet_खोलो_बंद(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक	fd;

	अगर (argc != 1) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_open_close: device-name\n");
		वापस;
	पूर्ण

	fd = खोलो(argv[0], O_RDONLY);
	अगर (fd < 0)
		ख_लिखो(मानक_त्रुटि, "hpet_open_close: open failed\n");
	अन्यथा
		बंद(fd);

	वापस;
पूर्ण

व्योम
hpet_info(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा hpet_info	info;
	पूर्णांक			fd;

	अगर (argc != 1) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_info: device-name\n");
		वापस;
	पूर्ण

	fd = खोलो(argv[0], O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_info: open of %s failed\n", argv[0]);
		वापस;
	पूर्ण

	अगर (ioctl(fd, HPET_INFO, &info) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_info: failed to get info\n");
		जाओ out;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "hpet_info: hi_irqfreq 0x%lx hi_flags 0x%lx ",
		info.hi_ireqfreq, info.hi_flags);
	ख_लिखो(मानक_त्रुटि, "hi_hpet %d hi_timer %d\n",
		info.hi_hpet, info.hi_समयr);

out:
	बंद(fd);
	वापस;
पूर्ण

व्योम
hpet_poll(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित दीर्घ		freq;
	पूर्णांक			iterations, i, fd;
	काष्ठा pollfd		pfd;
	काष्ठा hpet_info	info;
	काष्ठा समयval		stv, etv;
	काष्ठा समयzone		tz;
	दीर्घ			usec;

	अगर (argc != 3) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll: device-name freq iterations\n");
		वापस;
	पूर्ण

	freq = म_से_प(argv[1]);
	iterations = म_से_प(argv[2]);

	fd = खोलो(argv[0], O_RDONLY);

	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll: open of %s failed\n", argv[0]);
		वापस;
	पूर्ण

	अगर (ioctl(fd, HPET_IRQFREQ, freq) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll: HPET_IRQFREQ failed\n");
		जाओ out;
	पूर्ण

	अगर (ioctl(fd, HPET_INFO, &info) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll: failed to get info\n");
		जाओ out;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "hpet_poll: info.hi_flags 0x%lx\n", info.hi_flags);

	अगर (info.hi_flags && (ioctl(fd, HPET_EPI, 0) < 0)) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll: HPET_EPI failed\n");
		जाओ out;
	पूर्ण

	अगर (ioctl(fd, HPET_IE_ON, 0) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_poll, HPET_IE_ON failed\n");
		जाओ out;
	पूर्ण

	pfd.fd = fd;
	pfd.events = POLLIN;

	क्रम (i = 0; i < iterations; i++) अणु
		pfd.revents = 0;
		समय_लोofday(&stv, &tz);
		अगर (poll(&pfd, 1, -1) < 0)
			ख_लिखो(मानक_त्रुटि, "hpet_poll: poll failed\n");
		अन्यथा अणु
			दीर्घ 	data;

			समय_लोofday(&etv, &tz);
			usec = stv.tv_sec * 1000000 + stv.tv_usec;
			usec = (etv.tv_sec * 1000000 + etv.tv_usec) - usec;

			ख_लिखो(मानक_त्रुटि,
				"hpet_poll: expired time = 0x%lx\n", usec);

			ख_लिखो(मानक_त्रुटि, "hpet_poll: revents = 0x%x\n",
				pfd.revents);

			अगर (पढ़ो(fd, &data, माप(data)) != माप(data)) अणु
				ख_लिखो(मानक_त्रुटि, "hpet_poll: read failed\n");
			पूर्ण
			अन्यथा
				ख_लिखो(मानक_त्रुटि, "hpet_poll: data 0x%lx\n",
					data);
		पूर्ण
	पूर्ण

out:
	बंद(fd);
	वापस;
पूर्ण

अटल पूर्णांक hpet_sigio_count;

अटल व्योम
hpet_sigio(पूर्णांक val)
अणु
	ख_लिखो(मानक_त्रुटि, "hpet_sigio: called\n");
	hpet_sigio_count++;
पूर्ण

व्योम
hpet_fasync(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित दीर्घ		freq;
	पूर्णांक			iterations, i, fd, value;
	sig_t			oldsig;
	काष्ठा hpet_info	info;

	hpet_sigio_count = 0;
	fd = -1;

	अगर ((oldsig = संकेत(SIGIO, hpet_sigio)) == संक_त्रुटि) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: failed to set signal handler\n");
		वापस;
	पूर्ण

	अगर (argc != 3) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: device-name freq iterations\n");
		जाओ out;
	पूर्ण

	fd = खोलो(argv[0], O_RDONLY);

	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: failed to open %s\n", argv[0]);
		वापस;
	पूर्ण


	अगर ((fcntl(fd, F_SETOWN, getpid()) == 1) ||
		((value = fcntl(fd, F_GETFL)) == 1) ||
		(fcntl(fd, F_SETFL, value | O_ASYNC) == 1)) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: fcntl failed\n");
		जाओ out;
	पूर्ण

	freq = म_से_प(argv[1]);
	iterations = म_से_प(argv[2]);

	अगर (ioctl(fd, HPET_IRQFREQ, freq) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: HPET_IRQFREQ failed\n");
		जाओ out;
	पूर्ण

	अगर (ioctl(fd, HPET_INFO, &info) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: failed to get info\n");
		जाओ out;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "hpet_fasync: info.hi_flags 0x%lx\n", info.hi_flags);

	अगर (info.hi_flags && (ioctl(fd, HPET_EPI, 0) < 0)) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: HPET_EPI failed\n");
		जाओ out;
	पूर्ण

	अगर (ioctl(fd, HPET_IE_ON, 0) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "hpet_fasync, HPET_IE_ON failed\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < iterations; i++) अणु
		(व्योम) छोड़ो();
		ख_लिखो(मानक_त्रुटि, "hpet_fasync: count = %d\n", hpet_sigio_count);
	पूर्ण

out:
	संकेत(SIGIO, oldsig);

	अगर (fd >= 0)
		बंद(fd);

	वापस;
पूर्ण
