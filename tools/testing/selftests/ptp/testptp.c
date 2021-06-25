<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी support - User space test program
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#घोषणा _GNU_SOURCE
#घोषणा __SANE_USERSPACE_TYPES__        /* For PPC64, to get LL64 types */
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <गणित.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश <linux/ptp_घड़ी.h>

#घोषणा DEVICE "/dev/ptp0"

#अगर_अघोषित ADJ_SETOFFSET
#घोषणा ADJ_SETOFFSET 0x0100
#पूर्ण_अगर

#अगर_अघोषित CLOCK_INVALID
#घोषणा CLOCK_INVALID -1
#पूर्ण_अगर

#घोषणा NSEC_PER_SEC 1000000000LL

/* घड़ी_adjसमय is not available in GLIBC < 2.14 */
#अगर !__GLIBC_PREREQ(2, 14)
#समावेश <sys/syscall.h>
अटल पूर्णांक घड़ी_adjसमय(घड़ीid_t id, काष्ठा समयx *tx)
अणु
	वापस syscall(__NR_घड़ी_adjसमय, id, tx);
पूर्ण
#पूर्ण_अगर

अटल व्योम show_flag_test(पूर्णांक rq_index, अचिन्हित पूर्णांक flags, पूर्णांक err)
अणु
	म_लिखो("PTP_EXTTS_REQUEST%c flags 0x%08x : (%d) %s\n",
	       rq_index ? '1' + rq_index : ' ',
	       flags, err, म_त्रुटि(त्रुटि_सं));
	/* sigh, uClibc ... */
	त्रुटि_सं = 0;
पूर्ण

अटल व्योम करो_flag_test(पूर्णांक fd, अचिन्हित पूर्णांक index)
अणु
	काष्ठा ptp_extts_request extts_request;
	अचिन्हित दीर्घ request[2] = अणु
		PTP_EXTTS_REQUEST,
		PTP_EXTTS_REQUEST2,
	पूर्ण;
	अचिन्हित पूर्णांक enable_flags[5] = अणु
		PTP_ENABLE_FEATURE,
		PTP_ENABLE_FEATURE | PTP_RISING_EDGE,
		PTP_ENABLE_FEATURE | PTP_FALLING_EDGE,
		PTP_ENABLE_FEATURE | PTP_RISING_EDGE | PTP_FALLING_EDGE,
		PTP_ENABLE_FEATURE | (PTP_EXTTS_VALID_FLAGS + 1),
	पूर्ण;
	पूर्णांक err, i, j;

	स_रखो(&extts_request, 0, माप(extts_request));
	extts_request.index = index;

	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < 5; j++) अणु
			extts_request.flags = enable_flags[j];
			err = ioctl(fd, request[i], &extts_request);
			show_flag_test(i, extts_request.flags, err);

			extts_request.flags = 0;
			err = ioctl(fd, request[i], &extts_request);
		पूर्ण
	पूर्ण
पूर्ण

अटल घड़ीid_t get_घड़ीid(पूर्णांक fd)
अणु
#घोषणा CLOCKFD 3
	वापस (((अचिन्हित पूर्णांक) ~fd) << 3) | CLOCKFD;
पूर्ण

अटल दीर्घ ppb_to_scaled_ppm(पूर्णांक ppb)
अणु
	/*
	 * The 'freq' field in the 'struct timex' is in parts per
	 * million, but with a 16 bit binary fractional field.
	 * Instead of calculating either one of
	 *
	 *    scaled_ppm = (ppb / 1000) << 16  [1]
	 *    scaled_ppm = (ppb << 16) / 1000  [2]
	 *
	 * we simply use द्विगुन precision math, in order to aव्योम the
	 * truncation in [1] and the possible overflow in [2].
	 */
	वापस (दीर्घ) (ppb * 65.536);
पूर्ण

अटल पूर्णांक64_t pctns(काष्ठा ptp_घड़ी_प्रकारime *t)
अणु
	वापस t->sec * 1000000000LL + t->nsec;
पूर्ण

अटल व्योम usage(अक्षर *progname)
अणु
	ख_लिखो(मानक_त्रुटि,
		"usage: %s [options]\n"
		" -c         query the ptp clock's capabilities\n"
		" -d name    device to open\n"
		" -e val     read 'val' external time stamp events\n"
		" -f val     adjust the ptp clock frequency by 'val' ppb\n"
		" -g         get the ptp clock time\n"
		" -h         prints this message\n"
		" -i val     index for event/trigger\n"
		" -k val     measure the time offset between system and phc clock\n"
		"            for 'val' times (Maximum 25)\n"
		" -l         list the current pin configuration\n"
		" -L pin,val configure pin index 'pin' with function 'val'\n"
		"            the channel index is taken from the '-i' option\n"
		"            'val' specifies the auxiliary function:\n"
		"            0 - none\n"
		"            1 - external time stamp\n"
		"            2 - periodic output\n"
		" -p val     enable output with a period of 'val' nanoseconds\n"
		" -H val     set output phase to 'val' nanoseconds (requires -p)\n"
		" -w val     set output pulse width to 'val' nanoseconds (requires -p)\n"
		" -P val     enable or disable (val=1|0) the system clock PPS\n"
		" -s         set the ptp clock time from the system time\n"
		" -S         set the system time from the ptp clock time\n"
		" -t val     shift the ptp clock time by 'val' seconds\n"
		" -T val     set the ptp clock time to 'val' seconds\n"
		" -z         test combinations of rising/falling external time stamp flags\n",
		progname);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा ptp_घड़ी_caps caps;
	काष्ठा ptp_extts_event event;
	काष्ठा ptp_extts_request extts_request;
	काष्ठा ptp_perout_request perout_request;
	काष्ठा ptp_pin_desc desc;
	काष्ठा बारpec ts;
	काष्ठा समयx tx;
	काष्ठा ptp_घड़ी_प्रकारime *pct;
	काष्ठा ptp_sys_offset *sysoff;

	अक्षर *progname;
	अचिन्हित पूर्णांक i;
	पूर्णांक c, cnt, fd;

	अक्षर *device = DEVICE;
	घड़ीid_t clkid;
	पूर्णांक adjfreq = 0x7fffffff;
	पूर्णांक adjसमय = 0;
	पूर्णांक capabilities = 0;
	पूर्णांक extts = 0;
	पूर्णांक flagtest = 0;
	पूर्णांक समय_लो = 0;
	पूर्णांक index = 0;
	पूर्णांक list_pins = 0;
	पूर्णांक pct_offset = 0;
	पूर्णांक n_samples = 0;
	पूर्णांक pin_index = -1, pin_func;
	पूर्णांक pps = -1;
	पूर्णांक seconds = 0;
	पूर्णांक समय_रखो = 0;

	पूर्णांक64_t t1, t2, tp;
	पूर्णांक64_t पूर्णांकerval, offset;
	पूर्णांक64_t perout_phase = -1;
	पूर्णांक64_t pulsewidth = -1;
	पूर्णांक64_t perout = -1;

	progname = म_खोजप(argv[0], '/');
	progname = progname ? 1+progname : argv[0];
	जबतक (खातापूर्ण != (c = getopt(argc, argv, "cd:e:f:ghH:i:k:lL:p:P:sSt:T:w:z"))) अणु
		चयन (c) अणु
		हाल 'c':
			capabilities = 1;
			अवरोध;
		हाल 'd':
			device = optarg;
			अवरोध;
		हाल 'e':
			extts = म_से_प(optarg);
			अवरोध;
		हाल 'f':
			adjfreq = म_से_प(optarg);
			अवरोध;
		हाल 'g':
			समय_लो = 1;
			अवरोध;
		हाल 'H':
			perout_phase = म_से_दl(optarg);
			अवरोध;
		हाल 'i':
			index = म_से_प(optarg);
			अवरोध;
		हाल 'k':
			pct_offset = 1;
			n_samples = म_से_प(optarg);
			अवरोध;
		हाल 'l':
			list_pins = 1;
			अवरोध;
		हाल 'L':
			cnt = माला_पूछो(optarg, "%d,%d", &pin_index, &pin_func);
			अगर (cnt != 2) अणु
				usage(progname);
				वापस -1;
			पूर्ण
			अवरोध;
		हाल 'p':
			perout = म_से_दl(optarg);
			अवरोध;
		हाल 'P':
			pps = म_से_प(optarg);
			अवरोध;
		हाल 's':
			समय_रखो = 1;
			अवरोध;
		हाल 'S':
			समय_रखो = 2;
			अवरोध;
		हाल 't':
			adjसमय = म_से_प(optarg);
			अवरोध;
		हाल 'T':
			समय_रखो = 3;
			seconds = म_से_प(optarg);
			अवरोध;
		हाल 'w':
			pulsewidth = म_से_प(optarg);
			अवरोध;
		हाल 'z':
			flagtest = 1;
			अवरोध;
		हाल 'h':
			usage(progname);
			वापस 0;
		हाल '?':
		शेष:
			usage(progname);
			वापस -1;
		पूर्ण
	पूर्ण

	fd = खोलो(device, O_RDWR);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "opening %s: %s\n", device, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	clkid = get_घड़ीid(fd);
	अगर (CLOCK_INVALID == clkid) अणु
		ख_लिखो(मानक_त्रुटि, "failed to read clock id\n");
		वापस -1;
	पूर्ण

	अगर (capabilities) अणु
		अगर (ioctl(fd, PTP_CLOCK_GETCAPS, &caps)) अणु
			लिखो_त्रुटि("PTP_CLOCK_GETCAPS");
		पूर्ण अन्यथा अणु
			म_लिखो("capabilities:\n"
			       "  %d maximum frequency adjustment (ppb)\n"
			       "  %d programmable alarms\n"
			       "  %d external time stamp channels\n"
			       "  %d programmable periodic signals\n"
			       "  %d pulse per second\n"
			       "  %d programmable pins\n"
			       "  %d cross timestamping\n"
			       "  %d adjust_phase\n",
			       caps.max_adj,
			       caps.n_alarm,
			       caps.n_ext_ts,
			       caps.n_per_out,
			       caps.pps,
			       caps.n_pins,
			       caps.cross_बारtamping,
			       caps.adjust_phase);
		पूर्ण
	पूर्ण

	अगर (0x7fffffff != adjfreq) अणु
		स_रखो(&tx, 0, माप(tx));
		tx.modes = ADJ_FREQUENCY;
		tx.freq = ppb_to_scaled_ppm(adjfreq);
		अगर (घड़ी_adjसमय(clkid, &tx)) अणु
			लिखो_त्रुटि("clock_adjtime");
		पूर्ण अन्यथा अणु
			माला_दो("frequency adjustment okay");
		पूर्ण
	पूर्ण

	अगर (adjसमय) अणु
		स_रखो(&tx, 0, माप(tx));
		tx.modes = ADJ_SETOFFSET;
		tx.समय.tv_sec = adjसमय;
		tx.समय.tv_usec = 0;
		अगर (घड़ी_adjसमय(clkid, &tx) < 0) अणु
			लिखो_त्रुटि("clock_adjtime");
		पूर्ण अन्यथा अणु
			माला_दो("time shift okay");
		पूर्ण
	पूर्ण

	अगर (समय_लो) अणु
		अगर (घड़ी_समय_लो(clkid, &ts)) अणु
			लिखो_त्रुटि("clock_gettime");
		पूर्ण अन्यथा अणु
			म_लिखो("clock time: %ld.%09ld or %s",
			       ts.tv_sec, ts.tv_nsec, स_समय(&ts.tv_sec));
		पूर्ण
	पूर्ण

	अगर (समय_रखो == 1) अणु
		घड़ी_समय_लो(CLOCK_REALTIME, &ts);
		अगर (घड़ी_समय_रखो(clkid, &ts)) अणु
			लिखो_त्रुटि("clock_settime");
		पूर्ण अन्यथा अणु
			माला_दो("set time okay");
		पूर्ण
	पूर्ण

	अगर (समय_रखो == 2) अणु
		घड़ी_समय_लो(clkid, &ts);
		अगर (घड़ी_समय_रखो(CLOCK_REALTIME, &ts)) अणु
			लिखो_त्रुटि("clock_settime");
		पूर्ण अन्यथा अणु
			माला_दो("set time okay");
		पूर्ण
	पूर्ण

	अगर (समय_रखो == 3) अणु
		ts.tv_sec = seconds;
		ts.tv_nsec = 0;
		अगर (घड़ी_समय_रखो(clkid, &ts)) अणु
			लिखो_त्रुटि("clock_settime");
		पूर्ण अन्यथा अणु
			माला_दो("set time okay");
		पूर्ण
	पूर्ण

	अगर (extts) अणु
		स_रखो(&extts_request, 0, माप(extts_request));
		extts_request.index = index;
		extts_request.flags = PTP_ENABLE_FEATURE;
		अगर (ioctl(fd, PTP_EXTTS_REQUEST, &extts_request)) अणु
			लिखो_त्रुटि("PTP_EXTTS_REQUEST");
			extts = 0;
		पूर्ण अन्यथा अणु
			माला_दो("external time stamp request okay");
		पूर्ण
		क्रम (; extts; extts--) अणु
			cnt = पढ़ो(fd, &event, माप(event));
			अगर (cnt != माप(event)) अणु
				लिखो_त्रुटि("read");
				अवरोध;
			पूर्ण
			म_लिखो("event index %u at %lld.%09u\n", event.index,
			       event.t.sec, event.t.nsec);
			ख_साफ(मानक_निकास);
		पूर्ण
		/* Disable the feature again. */
		extts_request.flags = 0;
		अगर (ioctl(fd, PTP_EXTTS_REQUEST, &extts_request)) अणु
			लिखो_त्रुटि("PTP_EXTTS_REQUEST");
		पूर्ण
	पूर्ण

	अगर (flagtest) अणु
		करो_flag_test(fd, index);
	पूर्ण

	अगर (list_pins) अणु
		पूर्णांक n_pins = 0;
		अगर (ioctl(fd, PTP_CLOCK_GETCAPS, &caps)) अणु
			लिखो_त्रुटि("PTP_CLOCK_GETCAPS");
		पूर्ण अन्यथा अणु
			n_pins = caps.n_pins;
		पूर्ण
		क्रम (i = 0; i < n_pins; i++) अणु
			desc.index = i;
			अगर (ioctl(fd, PTP_PIN_GETFUNC, &desc)) अणु
				लिखो_त्रुटि("PTP_PIN_GETFUNC");
				अवरोध;
			पूर्ण
			म_लिखो("name %s index %u func %u chan %u\n",
			       desc.name, desc.index, desc.func, desc.chan);
		पूर्ण
	पूर्ण

	अगर (pulsewidth >= 0 && perout < 0) अणु
		माला_दो("-w can only be specified together with -p");
		वापस -1;
	पूर्ण

	अगर (perout_phase >= 0 && perout < 0) अणु
		माला_दो("-H can only be specified together with -p");
		वापस -1;
	पूर्ण

	अगर (perout >= 0) अणु
		अगर (घड़ी_समय_लो(clkid, &ts)) अणु
			लिखो_त्रुटि("clock_gettime");
			वापस -1;
		पूर्ण
		स_रखो(&perout_request, 0, माप(perout_request));
		perout_request.index = index;
		perout_request.period.sec = perout / NSEC_PER_SEC;
		perout_request.period.nsec = perout % NSEC_PER_SEC;
		perout_request.flags = 0;
		अगर (pulsewidth >= 0) अणु
			perout_request.flags |= PTP_PEROUT_DUTY_CYCLE;
			perout_request.on.sec = pulsewidth / NSEC_PER_SEC;
			perout_request.on.nsec = pulsewidth % NSEC_PER_SEC;
		पूर्ण
		अगर (perout_phase >= 0) अणु
			perout_request.flags |= PTP_PEROUT_PHASE;
			perout_request.phase.sec = perout_phase / NSEC_PER_SEC;
			perout_request.phase.nsec = perout_phase % NSEC_PER_SEC;
		पूर्ण अन्यथा अणु
			perout_request.start.sec = ts.tv_sec + 2;
			perout_request.start.nsec = 0;
		पूर्ण

		अगर (ioctl(fd, PTP_PEROUT_REQUEST2, &perout_request)) अणु
			लिखो_त्रुटि("PTP_PEROUT_REQUEST");
		पूर्ण अन्यथा अणु
			माला_दो("periodic output request okay");
		पूर्ण
	पूर्ण

	अगर (pin_index >= 0) अणु
		स_रखो(&desc, 0, माप(desc));
		desc.index = pin_index;
		desc.func = pin_func;
		desc.chan = index;
		अगर (ioctl(fd, PTP_PIN_SETFUNC, &desc)) अणु
			लिखो_त्रुटि("PTP_PIN_SETFUNC");
		पूर्ण अन्यथा अणु
			माला_दो("set pin function okay");
		पूर्ण
	पूर्ण

	अगर (pps != -1) अणु
		पूर्णांक enable = pps ? 1 : 0;
		अगर (ioctl(fd, PTP_ENABLE_PPS, enable)) अणु
			लिखो_त्रुटि("PTP_ENABLE_PPS");
		पूर्ण अन्यथा अणु
			माला_दो("pps for system time request okay");
		पूर्ण
	पूर्ण

	अगर (pct_offset) अणु
		अगर (n_samples <= 0 || n_samples > 25) अणु
			माला_दो("n_samples should be between 1 and 25");
			usage(progname);
			वापस -1;
		पूर्ण

		sysoff = सुस्मृति(1, माप(*sysoff));
		अगर (!sysoff) अणु
			लिखो_त्रुटि("calloc");
			वापस -1;
		पूर्ण
		sysoff->n_samples = n_samples;

		अगर (ioctl(fd, PTP_SYS_OFFSET, sysoff))
			लिखो_त्रुटि("PTP_SYS_OFFSET");
		अन्यथा
			माला_दो("system and phc clock time offset request okay");

		pct = &sysoff->ts[0];
		क्रम (i = 0; i < sysoff->n_samples; i++) अणु
			t1 = pctns(pct+2*i);
			tp = pctns(pct+2*i+1);
			t2 = pctns(pct+2*i+2);
			पूर्णांकerval = t2 - t1;
			offset = (t2 + t1) / 2 - tp;

			म_लिखो("system time: %lld.%u\n",
				(pct+2*i)->sec, (pct+2*i)->nsec);
			म_लिखो("phc    time: %lld.%u\n",
				(pct+2*i+1)->sec, (pct+2*i+1)->nsec);
			म_लिखो("system time: %lld.%u\n",
				(pct+2*i+2)->sec, (pct+2*i+2)->nsec);
			म_लिखो("system/phc clock time offset is %" PRId64 " ns\n"
			       "system     clock time delay  is %" PRId64 " ns\n",
				offset, पूर्णांकerval);
		पूर्ण

		मुक्त(sysoff);
	पूर्ण

	बंद(fd);
	वापस 0;
पूर्ण
