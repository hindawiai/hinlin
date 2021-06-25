<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * पंचांगon.c Thermal Monitor (TMON) मुख्य function and entry poपूर्णांक
 *
 * Copyright (C) 2012 Intel Corporation. All rights reserved.
 *
 * Author: Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 */

#समावेश <getopt.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <ncurses.h>
#समावेश <प्रकार.स>
#समावेश <समय.स>
#समावेश <संकेत.स>
#समावेश <सीमा.स>
#समावेश <sys/समय.स>
#समावेश <pthपढ़ो.h>
#समावेश <गणित.स>
#समावेश <मानकतर्क.स>
#समावेश <syslog.h>

#समावेश "tmon.h"

अचिन्हित दीर्घ tickसमय = 1; /* seconds */
अचिन्हित दीर्घ no_control = 1; /* monitoring only or use cooling device क्रम
			       * temperature control.
			       */
द्विगुन समय_elapsed = 0.0;
अचिन्हित दीर्घ target_temp_user = 65; /* can be select by tui later */
पूर्णांक dialogue_on;
पूर्णांक पंचांगon_निकास;
अटल लघु	daemon_mode;
अटल पूर्णांक logging; /* क्रम recording thermal data to a file */
अटल पूर्णांक debug_on;
खाता *पंचांगon_log;
/*cooling device used क्रम the PID controller */
अक्षर ctrl_cdev[CDEV_NAME_SIZE] = "None";
पूर्णांक target_thermal_zone; /* user selected target zone instance */
अटल व्योम	start_daemon_mode(व्योम);

pthपढ़ो_t event_tid;
pthपढ़ो_mutex_t input_lock;
व्योम usage(व्योम)
अणु
	म_लिखो("Usage: tmon [OPTION...]\n");
	म_लिखो("  -c, --control         cooling device in control\n");
	म_लिखो("  -d, --daemon          run as daemon, no TUI\n");
	म_लिखो("  -g, --debug           debug message in syslog\n");
	म_लिखो("  -h, --help            show this help message\n");
	म_लिखो("  -l, --log             log data to /var/tmp/tmon.log\n");
	म_लिखो("  -t, --time-interval   sampling time interval, > 1 sec.\n");
	म_लिखो("  -T, --target-temp     initial target temperature\n");
	म_लिखो("  -v, --version         show version\n");
	म_लिखो("  -z, --zone            target thermal zone id\n");

	निकास(0);
पूर्ण

व्योम version(व्योम)
अणु
	म_लिखो("TMON version %s\n", VERSION);
	निकास(निकास_सफल);
पूर्ण

अटल व्योम पंचांगon_cleanup(व्योम)
अणु
	syslog(LOG_INFO, "TMON exit cleanup\n");
	ख_साफ(मानक_निकास);
	refresh();
	अगर (पंचांगon_log)
		ख_बंद(पंचांगon_log);
	अगर (event_tid) अणु
		pthपढ़ो_mutex_lock(&input_lock);
		pthपढ़ो_cancel(event_tid);
		pthपढ़ो_mutex_unlock(&input_lock);
		pthपढ़ो_mutex_destroy(&input_lock);
	पूर्ण
	बंदlog();
	/* relax control knobs, unकरो throttling */
	set_ctrl_state(0);

	keypad(stdscr, FALSE);
	echo();
	nocअवरोध();
	बंद_winकरोws();
	endwin();
	मुक्त_thermal_data();

	निकास(1);
पूर्ण

अटल व्योम पंचांगon_sig_handler(पूर्णांक sig)
अणु
	syslog(LOG_INFO, "TMON caught signal %d\n", sig);
	refresh();
	चयन (sig) अणु
	हाल संक_इति:
		म_लिखो("sigterm, exit and clean up\n");
		ख_साफ(मानक_निकास);
		अवरोध;
	हाल SIGKILL:
		म_लिखो("sigkill, exit and clean up\n");
		ख_साफ(मानक_निकास);
		अवरोध;
	हाल संक_विघ्न:
		म_लिखो("ctrl-c, exit and clean up\n");
		ख_साफ(मानक_निकास);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	पंचांगon_निकास = true;
पूर्ण

अटल व्योम start_syslog(व्योम)
अणु
	अगर (debug_on)
		setlogmask(LOG_UPTO(LOG_DEBUG));
	अन्यथा
		setlogmask(LOG_UPTO(LOG_ERR));
	खोलोlog("tmon.log", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
	syslog(LOG_NOTICE, "TMON started by User %d", getuid());
पूर्ण

अटल व्योम prepare_logging(व्योम)
अणु
	पूर्णांक i;
	काष्ठा stat logstat;

	अगर (!logging)
		वापस;
	/* खोलो local data log file */
	पंचांगon_log = ख_खोलो(TMON_LOG_खाता, "w+");
	अगर (!पंचांगon_log) अणु
		syslog(LOG_ERR, "failed to open log file %s\n", TMON_LOG_खाता);
		वापस;
	पूर्ण

	अगर (lstat(TMON_LOG_खाता, &logstat) < 0) अणु
		syslog(LOG_ERR, "Unable to stat log file %s\n", TMON_LOG_खाता);
		ख_बंद(पंचांगon_log);
		पंचांगon_log = शून्य;
		वापस;
	पूर्ण

	/* The log file must be a regular file owned by us */
	अगर (S_ISLNK(logstat.st_mode)) अणु
		syslog(LOG_ERR, "Log file is a symlink.  Will not log\n");
		ख_बंद(पंचांगon_log);
		पंचांगon_log = शून्य;
		वापस;
	पूर्ण

	अगर (logstat.st_uid != getuid()) अणु
		syslog(LOG_ERR, "We don't own the log file.  Not logging\n");
		ख_बंद(पंचांगon_log);
		पंचांगon_log = शून्य;
		वापस;
	पूर्ण

	ख_लिखो(पंचांगon_log, "#----------- THERMAL SYSTEM CONFIG -------------\n");
	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		अक्षर binding_str[33]; /* size of दीर्घ + 1 */
		पूर्णांक j;

		स_रखो(binding_str, 0, माप(binding_str));
		क्रम (j = 0; j < 32; j++)
			binding_str[j] = (ptdata.tzi[i].cdev_binding & (1 << j)) ?
				'1' : '0';

		ख_लिखो(पंचांगon_log, "#thermal zone %s%02d cdevs binding: %32s\n",
			ptdata.tzi[i].type,
			ptdata.tzi[i].instance,
			binding_str);
		क्रम (j = 0; j <	ptdata.tzi[i].nr_trip_pts; j++) अणु
			ख_लिखो(पंचांगon_log, "#\tTP%02d type:%s, temp:%lu\n", j,
				trip_type_name[ptdata.tzi[i].tp[j].type],
				ptdata.tzi[i].tp[j].temp);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <	ptdata.nr_cooling_dev; i++)
		ख_लिखो(पंचांगon_log, "#cooling devices%02d: %s\n",
			i, ptdata.cdi[i].type);

	ख_लिखो(पंचांगon_log, "#---------- THERMAL DATA LOG STARTED -----------\n");
	ख_लिखो(पंचांगon_log, "Samples TargetTemp ");
	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		ख_लिखो(पंचांगon_log, "%s%d    ", ptdata.tzi[i].type,
			ptdata.tzi[i].instance);
	पूर्ण
	क्रम (i = 0; i <	ptdata.nr_cooling_dev; i++)
		ख_लिखो(पंचांगon_log, "%s%d ", ptdata.cdi[i].type,
			ptdata.cdi[i].instance);

	ख_लिखो(पंचांगon_log, "\n");
पूर्ण

अटल काष्ठा option opts[] = अणु
	अणु "control", 1, शून्य, 'c' पूर्ण,
	अणु "daemon", 0, शून्य, 'd' पूर्ण,
	अणु "time-interval", 1, शून्य, 't' पूर्ण,
	अणु "target-temp", 1, शून्य, 'T' पूर्ण,
	अणु "log", 0, शून्य, 'l' पूर्ण,
	अणु "help", 0, शून्य, 'h' पूर्ण,
	अणु "version", 0, शून्य, 'v' पूर्ण,
	अणु "debug", 0, शून्य, 'g' पूर्ण,
	अणु 0, 0, शून्य, 0 पूर्ण
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक err = 0;
	पूर्णांक id2 = 0, c;
	द्विगुन yk = 0.0, temp; /* controller output */
	पूर्णांक target_tz_index;

	अगर (geteuid() != 0) अणु
		म_लिखो("TMON needs to be run as root\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	जबतक ((c = getopt_दीर्घ(argc, argv, "c:dlht:T:vgz:", opts, &id2)) != -1) अणु
		चयन (c) अणु
		हाल 'c':
			no_control = 0;
			म_नकलन(ctrl_cdev, optarg, CDEV_NAME_SIZE);
			अवरोध;
		हाल 'd':
			start_daemon_mode();
			म_लिखो("Run TMON in daemon mode\n");
			अवरोध;
		हाल 't':
			tickसमय = म_से_भग्न(optarg, शून्य);
			अगर (tickसमय < 1)
				tickसमय = 1;
			अवरोध;
		हाल 'T':
			temp = म_से_भग्न(optarg, शून्य);
			अगर (temp < 0) अणु
				ख_लिखो(मानक_त्रुटि, "error: temperature must be positive\n");
				वापस 1;
			पूर्ण
			target_temp_user = temp;
			अवरोध;
		हाल 'l':
			म_लिखो("Logging data to /var/tmp/tmon.log\n");
			logging = 1;
			अवरोध;
		हाल 'h':
			usage();
			अवरोध;
		हाल 'v':
			version();
			अवरोध;
		हाल 'g':
			debug_on = 1;
			अवरोध;
		हाल 'z':
			target_thermal_zone = म_से_भग्न(optarg, शून्य);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pthपढ़ो_mutex_init(&input_lock, शून्य) != 0) अणु
		ख_लिखो(मानक_त्रुटि, "\n mutex init failed, exit\n");
		वापस 1;
	पूर्ण
	start_syslog();
	अगर (संकेत(संक_विघ्न, पंचांगon_sig_handler) == संक_त्रुटि)
		syslog(LOG_DEBUG, "Cannot handle SIGINT\n");
	अगर (संकेत(संक_इति, पंचांगon_sig_handler) == संक_त्रुटि)
		syslog(LOG_DEBUG, "Cannot handle SIGTERM\n");

	अगर (probe_thermal_sysfs()) अणु
		pthपढ़ो_mutex_destroy(&input_lock);
		बंदlog();
		वापस -1;
	पूर्ण
	initialize_curses();
	setup_winकरोws();
	संकेत(SIGWINCH, resize_handler);
	show_title_bar();
	show_sensors_w();
	show_cooling_device();
	update_thermal_data();
	show_data_w();
	prepare_logging();
	init_thermal_controller();

	nodelay(stdscr, TRUE);
	err = pthपढ़ो_create(&event_tid, शून्य, &handle_tui_events, शून्य);
	अगर (err != 0) अणु
		म_लिखो("\ncan't create thread :[%s]", म_त्रुटि(err));
		पंचांगon_cleanup();
		निकास(निकास_त्रुटि);
	पूर्ण

	/* validate range of user selected target zone, शेष to the first
	 * instance अगर out of range
	 */
	target_tz_index = zone_instance_to_index(target_thermal_zone);
	अगर (target_tz_index < 0) अणु
		target_thermal_zone = ptdata.tzi[0].instance;
		syslog(LOG_ERR, "target zone is not found, default to %d\n",
			target_thermal_zone);
	पूर्ण
	जबतक (1) अणु
		sleep(tickसमय);
		show_title_bar();
		show_sensors_w();
		update_thermal_data();
		अगर (!dialogue_on) अणु
			show_data_w();
			show_cooling_device();
		पूर्ण
		समय_elapsed += tickसमय;
		controller_handler(trec[0].temp[target_tz_index] / 1000, &yk);
		trec[0].pid_out_pct = yk;
		अगर (!dialogue_on)
			show_control_w();
		अगर (पंचांगon_निकास)
			अवरोध;
	पूर्ण
	पंचांगon_cleanup();
	वापस 0;
पूर्ण

अटल व्योम start_daemon_mode(व्योम)
अणु
	daemon_mode = 1;
	/* विभाजन */
	pid_t	sid, pid = विभाजन();

	अगर (pid < 0)
		निकास(निकास_त्रुटि);
	अन्यथा अगर (pid > 0)
		/* समाप्त parent */
		निकास(निकास_सफल);

	/* disable TUI, it may not be necessary, but saves some resource */
	disable_tui();

	/* change the file mode mask */
	umask(S_IWGRP | S_IWOTH);

	/* new SID क्रम the daemon process */
	sid = setsid();
	अगर (sid < 0)
		निकास(निकास_त्रुटि);

	/* change working directory */
	अगर ((स_बदलो("/")) < 0)
		निकास(निकास_त्रुटि);

	sleep(10);

	बंद(STDIN_खाताNO);
	बंद(STDOUT_खाताNO);
	बंद(STDERR_खाताNO);
पूर्ण
