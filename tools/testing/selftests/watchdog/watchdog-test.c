<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg Driver Test Program
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <getopt.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/watchकरोg.h>

#घोषणा DEFAULT_PING_RATE	1

पूर्णांक fd;
स्थिर अक्षर v = 'V';
अटल स्थिर अक्षर sopts[] = "bdehp:t:Tn:NLf:i";
अटल स्थिर काष्ठा option lopts[] = अणु
	अणु"bootstatus",          no_argument, शून्य, 'b'पूर्ण,
	अणु"disable",             no_argument, शून्य, 'd'पूर्ण,
	अणु"enable",              no_argument, शून्य, 'e'पूर्ण,
	अणु"help",                no_argument, शून्य, 'h'पूर्ण,
	अणु"pingrate",      required_argument, शून्य, 'p'पूर्ण,
	अणु"timeout",       required_argument, शून्य, 't'पूर्ण,
	अणु"gettimeout",          no_argument, शून्य, 'T'पूर्ण,
	अणु"pretimeout",    required_argument, शून्य, 'n'पूर्ण,
	अणु"getpretimeout",       no_argument, शून्य, 'N'पूर्ण,
	अणु"gettimeleft",		no_argument, शून्य, 'L'पूर्ण,
	अणु"file",          required_argument, शून्य, 'f'पूर्ण,
	अणु"info",		no_argument, शून्य, 'i'पूर्ण,
	अणुशून्य,                  no_argument, शून्य, 0x0पूर्ण
पूर्ण;

/*
 * This function simply sends an IOCTL to the driver, which in turn ticks
 * the PC Watchकरोg card to reset its पूर्णांकernal समयr so it करोesn't trigger
 * a computer reset.
 */
अटल व्योम keep_alive(व्योम)
अणु
	पूर्णांक dummy;
	पूर्णांक ret;

	ret = ioctl(fd, WDIOC_KEEPALIVE, &dummy);
	अगर (!ret)
		म_लिखो(".");
पूर्ण

/*
 * The मुख्य program.  Run the program with "-d" to disable the card,
 * or "-e" to enable the card.
 */

अटल व्योम term(पूर्णांक sig)
अणु
	पूर्णांक ret = ग_लिखो(fd, &v, 1);

	बंद(fd);
	अगर (ret < 0)
		म_लिखो("\nStopping watchdog ticks failed (%d)...\n", त्रुटि_सं);
	अन्यथा
		म_लिखो("\nStopping watchdog ticks...\n");
	निकास(0);
पूर्ण

अटल व्योम usage(अक्षर *progname)
अणु
	म_लिखो("Usage: %s [options]\n", progname);
	म_लिखो(" -f, --file\t\tOpen watchdog device file\n");
	म_लिखो("\t\t\tDefault is /dev/watchdog\n");
	म_लिखो(" -i, --info\t\tShow watchdog_info\n");
	म_लिखो(" -b, --bootstatus\tGet last boot status (Watchdog/POR)\n");
	म_लिखो(" -d, --disable\t\tTurn off the watchdog timer\n");
	म_लिखो(" -e, --enable\t\tTurn on the watchdog timer\n");
	म_लिखो(" -h, --help\t\tPrint the help message\n");
	म_लिखो(" -p, --pingrate=P\tSet ping rate to P seconds (default %d)\n",
	       DEFAULT_PING_RATE);
	म_लिखो(" -t, --timeout=T\tSet timeout to T seconds\n");
	म_लिखो(" -T, --gettimeout\tGet the timeout\n");
	म_लिखो(" -n, --pretimeout=T\tSet the pretimeout to T seconds\n");
	म_लिखो(" -N, --getpretimeout\tGet the pretimeout\n");
	म_लिखो(" -L, --gettimeleft\tGet the time left until timer expires\n");
	म_लिखो("\n");
	म_लिखो("Parameters are parsed left-to-right in real-time.\n");
	म_लिखो("Example: %s -d -t 10 -p 5 -e\n", progname);
	म_लिखो("Example: %s -t 12 -T -n 7 -N\n", progname);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक flags;
	अचिन्हित पूर्णांक ping_rate = DEFAULT_PING_RATE;
	पूर्णांक ret;
	पूर्णांक c;
	पूर्णांक oneshot = 0;
	अक्षर *file = "/dev/watchdog";
	काष्ठा watchकरोg_info info;

	रखो_बफ(मानक_निकास, शून्य);

	जबतक ((c = getopt_दीर्घ(argc, argv, sopts, lopts, शून्य)) != -1) अणु
		अगर (c == 'f')
			file = optarg;
	पूर्ण

	fd = खोलो(file, O_WRONLY);

	अगर (fd == -1) अणु
		अगर (त्रुटि_सं == ENOENT)
			म_लिखो("Watchdog device (%s) not found.\n", file);
		अन्यथा अगर (त्रुटि_सं == EACCES)
			म_लिखो("Run watchdog as root.\n");
		अन्यथा
			म_लिखो("Watchdog device open failed %s\n",
				म_त्रुटि(त्रुटि_सं));
		निकास(-1);
	पूर्ण

	/*
	 * Validate that `file` is a watchकरोg device
	 */
	ret = ioctl(fd, WDIOC_GETSUPPORT, &info);
	अगर (ret) अणु
		म_लिखो("WDIOC_GETSUPPORT error '%s'\n", म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		निकास(ret);
	पूर्ण

	optind = 0;

	जबतक ((c = getopt_दीर्घ(argc, argv, sopts, lopts, शून्य)) != -1) अणु
		चयन (c) अणु
		हाल 'b':
			flags = 0;
			oneshot = 1;
			ret = ioctl(fd, WDIOC_GETBOOTSTATUS, &flags);
			अगर (!ret)
				म_लिखो("Last boot is caused by: %s.\n", (flags != 0) ?
					"Watchdog" : "Power-On-Reset");
			अन्यथा
				म_लिखो("WDIOC_GETBOOTSTATUS error '%s'\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		हाल 'd':
			flags = WDIOS_DISABLECARD;
			ret = ioctl(fd, WDIOC_SETOPTIONS, &flags);
			अगर (!ret)
				म_लिखो("Watchdog card disabled.\n");
			अन्यथा अणु
				म_लिखो("WDIOS_DISABLECARD error '%s'\n", म_त्रुटि(त्रुटि_सं));
				oneshot = 1;
			पूर्ण
			अवरोध;
		हाल 'e':
			flags = WDIOS_ENABLECARD;
			ret = ioctl(fd, WDIOC_SETOPTIONS, &flags);
			अगर (!ret)
				म_लिखो("Watchdog card enabled.\n");
			अन्यथा अणु
				म_लिखो("WDIOS_ENABLECARD error '%s'\n", म_त्रुटि(त्रुटि_सं));
				oneshot = 1;
			पूर्ण
			अवरोध;
		हाल 'p':
			ping_rate = म_से_अदीर्घ(optarg, शून्य, 0);
			अगर (!ping_rate)
				ping_rate = DEFAULT_PING_RATE;
			म_लिखो("Watchdog ping rate set to %u seconds.\n", ping_rate);
			अवरोध;
		हाल 't':
			flags = म_से_अदीर्घ(optarg, शून्य, 0);
			ret = ioctl(fd, WDIOC_SETTIMEOUT, &flags);
			अगर (!ret)
				म_लिखो("Watchdog timeout set to %u seconds.\n", flags);
			अन्यथा अणु
				म_लिखो("WDIOC_SETTIMEOUT error '%s'\n", म_त्रुटि(त्रुटि_सं));
				oneshot = 1;
			पूर्ण
			अवरोध;
		हाल 'T':
			oneshot = 1;
			ret = ioctl(fd, WDIOC_GETTIMEOUT, &flags);
			अगर (!ret)
				म_लिखो("WDIOC_GETTIMEOUT returns %u seconds.\n", flags);
			अन्यथा
				म_लिखो("WDIOC_GETTIMEOUT error '%s'\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		हाल 'n':
			flags = म_से_अदीर्घ(optarg, शून्य, 0);
			ret = ioctl(fd, WDIOC_SETPRETIMEOUT, &flags);
			अगर (!ret)
				म_लिखो("Watchdog pretimeout set to %u seconds.\n", flags);
			अन्यथा अणु
				म_लिखो("WDIOC_SETPRETIMEOUT error '%s'\n", म_त्रुटि(त्रुटि_सं));
				oneshot = 1;
			पूर्ण
			अवरोध;
		हाल 'N':
			oneshot = 1;
			ret = ioctl(fd, WDIOC_GETPRETIMEOUT, &flags);
			अगर (!ret)
				म_लिखो("WDIOC_GETPRETIMEOUT returns %u seconds.\n", flags);
			अन्यथा
				म_लिखो("WDIOC_GETPRETIMEOUT error '%s'\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		हाल 'L':
			oneshot = 1;
			ret = ioctl(fd, WDIOC_GETTIMELEFT, &flags);
			अगर (!ret)
				म_लिखो("WDIOC_GETTIMELEFT returns %u seconds.\n", flags);
			अन्यथा
				म_लिखो("WDIOC_GETTIMELEFT error '%s'\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		हाल 'f':
			/* Handled above */
			अवरोध;
		हाल 'i':
			/*
			 * watchकरोg_info was obtained as part of file खोलो
			 * validation. So we just show it here.
			 */
			oneshot = 1;
			म_लिखो("watchdog_info:\n");
			म_लिखो(" identity:\t\t%s\n", info.identity);
			म_लिखो(" firmware_version:\t%u\n",
			       info.firmware_version);
			म_लिखो(" options:\t\t%08x\n", info.options);
			अवरोध;

		शेष:
			usage(argv[0]);
			जाओ end;
		पूर्ण
	पूर्ण

	अगर (oneshot)
		जाओ end;

	म_लिखो("Watchdog Ticking Away!\n");

	संकेत(संक_विघ्न, term);

	जबतक (1) अणु
		keep_alive();
		sleep(ping_rate);
	पूर्ण
end:
	ret = ग_लिखो(fd, &v, 1);
	अगर (ret < 0)
		म_लिखो("Stopping watchdog ticks failed (%d)...\n", त्रुटि_सं);
	बंद(fd);
	वापस 0;
पूर्ण
