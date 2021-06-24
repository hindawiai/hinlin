<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * x86_energy_perf_policy -- set the energy versus perक्रमmance
 * policy preference bias on recent X86 processors.
 */
/*
 * Copyright (c) 2010 - 2017 Intel Corporation.
 * Len Brown <len.brown@पूर्णांकel.com>
 */

#घोषणा _GNU_SOURCE
#समावेश MSRHEADER
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sched.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/resource.h>
#समावेश <getopt.h>
#समावेश <err.h>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <sys/समय.स>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <cpuid.h>
#समावेश <त्रुटिसं.स>

#घोषणा	OPTARG_NORMAL			(पूर्णांक_उच्च - 1)
#घोषणा	OPTARG_POWER			(पूर्णांक_उच्च - 2)
#घोषणा	OPTARG_BALANCE_POWER		(पूर्णांक_उच्च - 3)
#घोषणा	OPTARG_BALANCE_PERFORMANCE	(पूर्णांक_उच्च - 4)
#घोषणा	OPTARG_PERFORMANCE		(पूर्णांक_उच्च - 5)

काष्ठा msr_hwp_cap अणु
	अचिन्हित अक्षर highest;
	अचिन्हित अक्षर guaranteed;
	अचिन्हित अक्षर efficient;
	अचिन्हित अक्षर lowest;
पूर्ण;

काष्ठा msr_hwp_request अणु
	अचिन्हित अक्षर hwp_min;
	अचिन्हित अक्षर hwp_max;
	अचिन्हित अक्षर hwp_desired;
	अचिन्हित अक्षर hwp_epp;
	अचिन्हित पूर्णांक hwp_winकरोw;
	अचिन्हित अक्षर hwp_use_pkg;
पूर्ण req_update;

अचिन्हित पूर्णांक debug;
अचिन्हित पूर्णांक verbose;
अचिन्हित पूर्णांक क्रमce;
अक्षर *progname;
पूर्णांक base_cpu;
अचिन्हित अक्षर update_epb;
अचिन्हित दीर्घ दीर्घ new_epb;
अचिन्हित अक्षर turbo_is_enabled;
अचिन्हित अक्षर update_turbo;
अचिन्हित अक्षर turbo_update_value;
अचिन्हित अक्षर update_hwp_epp;
अचिन्हित अक्षर update_hwp_min;
अचिन्हित अक्षर update_hwp_max;
अचिन्हित अक्षर update_hwp_desired;
अचिन्हित अक्षर update_hwp_winकरोw;
अचिन्हित अक्षर update_hwp_use_pkg;
अचिन्हित अक्षर update_hwp_enable;
#घोषणा hwp_update_enabled() (update_hwp_enable | update_hwp_epp | update_hwp_max | update_hwp_min | update_hwp_desired | update_hwp_winकरोw | update_hwp_use_pkg)
पूर्णांक max_cpu_num;
पूर्णांक max_pkg_num;
#घोषणा MAX_PACKAGES 64
अचिन्हित पूर्णांक first_cpu_in_pkg[MAX_PACKAGES];
अचिन्हित दीर्घ दीर्घ pkg_present_set;
अचिन्हित दीर्घ दीर्घ pkg_selected_set;
cpu_set_t *cpu_present_set;
cpu_set_t *cpu_selected_set;
पूर्णांक genuine_पूर्णांकel;

माप_प्रकार cpu_setsize;

अक्षर *proc_stat = "/proc/stat";

अचिन्हित पूर्णांक has_epb;	/* MSR_IA32_ENERGY_PERF_BIAS */
अचिन्हित पूर्णांक has_hwp;	/* IA32_PM_ENABLE, IA32_HWP_CAPABILITIES */
			/* IA32_HWP_REQUEST, IA32_HWP_STATUS */
अचिन्हित पूर्णांक has_hwp_notअगरy;		/* IA32_HWP_INTERRUPT */
अचिन्हित पूर्णांक has_hwp_activity_winकरोw;	/* IA32_HWP_REQUEST[bits 41:32] */
अचिन्हित पूर्णांक has_hwp_epp;	/* IA32_HWP_REQUEST[bits 31:24] */
अचिन्हित पूर्णांक has_hwp_request_pkg;	/* IA32_HWP_REQUEST_PKG */

अचिन्हित पूर्णांक bdx_highest_ratio;

#घोषणा PATH_TO_CPU "/sys/devices/system/cpu/"
#घोषणा SYSFS_PATH_MAX 255

/*
 * मुख्यtain compatibility with original implementation, but करोn't करोcument it:
 */
व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "%s [options] [scope][field value]\n", progname);
	ख_लिखो(मानक_त्रुटि, "scope: --cpu cpu-list [--hwp-use-pkg #] | --pkg pkg-list\n");
	ख_लिखो(मानक_त्रुटि, "field: --all | --epb | --hwp-epp | --hwp-min | --hwp-max | --hwp-desired\n");
	ख_लिखो(मानक_त्रुटि, "other: --hwp-enable | --turbo-enable (0 | 1) | --help | --force\n");
	ख_लिखो(मानक_त्रुटि,
		"value: ( # | \"normal\" | \"performance\" | \"balance-performance\" | \"balance-power\"| \"power\")\n");
	ख_लिखो(मानक_त्रुटि, "--hwp-window usec\n");

	ख_लिखो(मानक_त्रुटि, "Specify only Energy Performance BIAS (legacy usage):\n");
	ख_लिखो(मानक_त्रुटि, "%s: [-c cpu] [-v] (-r | policy-value )\n", progname);

	निकास(1);
पूर्ण

/*
 * If bdx_highest_ratio is set,
 * then we must translate between MSR क्रमmat and simple ratio
 * used on the cmdline.
 */
पूर्णांक ratio_2_msr_perf(पूर्णांक ratio)
अणु
	पूर्णांक msr_perf;

	अगर (!bdx_highest_ratio)
		वापस ratio;

	msr_perf = ratio * 255 / bdx_highest_ratio;

	अगर (debug)
		ख_लिखो(मानक_त्रुटि, "%d = ratio_to_msr_perf(%d)\n", msr_perf, ratio);

	वापस msr_perf;
पूर्ण
पूर्णांक msr_perf_2_ratio(पूर्णांक msr_perf)
अणु
	पूर्णांक ratio;
	द्विगुन d;

	अगर (!bdx_highest_ratio)
		वापस msr_perf;

	d = (द्विगुन)msr_perf * (द्विगुन) bdx_highest_ratio / 255.0;
	d = d + 0.5;	/* round */
	ratio = (पूर्णांक)d;

	अगर (debug)
		ख_लिखो(मानक_त्रुटि, "%d = msr_perf_ratio(%d) {%f}\n", ratio, msr_perf, d);

	वापस ratio;
पूर्ण
पूर्णांक parse_cmdline_epb(पूर्णांक i)
अणु
	अगर (!has_epb)
		errx(1, "EPB not enabled on this platform");

	update_epb = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
		वापस ENERGY_PERF_BIAS_POWERSAVE;
	हाल OPTARG_BALANCE_POWER:
		वापस ENERGY_PERF_BIAS_BALANCE_POWERSAVE;
	हाल OPTARG_NORMAL:
		वापस ENERGY_PERF_BIAS_NORMAL;
	हाल OPTARG_BALANCE_PERFORMANCE:
		वापस ENERGY_PERF_BIAS_BALANCE_PERFORMANCE;
	हाल OPTARG_PERFORMANCE:
		वापस ENERGY_PERF_BIAS_PERFORMANCE;
	पूर्ण
	अगर (i < 0 || i > ENERGY_PERF_BIAS_POWERSAVE)
		errx(1, "--epb must be from 0 to 15");
	वापस i;
पूर्ण

#घोषणा HWP_CAP_LOWEST 0
#घोषणा HWP_CAP_HIGHEST 255

/*
 * "performance" changes hwp_min to cap.highest
 * All others leave it at cap.lowest
 */
पूर्णांक parse_cmdline_hwp_min(पूर्णांक i)
अणु
	update_hwp_min = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
	हाल OPTARG_BALANCE_POWER:
	हाल OPTARG_NORMAL:
	हाल OPTARG_BALANCE_PERFORMANCE:
		वापस HWP_CAP_LOWEST;
	हाल OPTARG_PERFORMANCE:
		वापस HWP_CAP_HIGHEST;
	पूर्ण
	वापस i;
पूर्ण
/*
 * "power" changes hwp_max to cap.lowest
 * All others leave it at cap.highest
 */
पूर्णांक parse_cmdline_hwp_max(पूर्णांक i)
अणु
	update_hwp_max = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
		वापस HWP_CAP_LOWEST;
	हाल OPTARG_NORMAL:
	हाल OPTARG_BALANCE_POWER:
	हाल OPTARG_BALANCE_PERFORMANCE:
	हाल OPTARG_PERFORMANCE:
		वापस HWP_CAP_HIGHEST;
	पूर्ण
	वापस i;
पूर्ण
/*
 * क्रम --hwp-des, all strings leave it in स्वतःnomous mode
 * If you want to change it, you need to explicitly pick a value
 */
पूर्णांक parse_cmdline_hwp_desired(पूर्णांक i)
अणु
	update_hwp_desired = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
	हाल OPTARG_BALANCE_POWER:
	हाल OPTARG_BALANCE_PERFORMANCE:
	हाल OPTARG_NORMAL:
	हाल OPTARG_PERFORMANCE:
		वापस 0;	/* स्वतःnomous */
	पूर्ण
	वापस i;
पूर्ण

पूर्णांक parse_cmdline_hwp_winकरोw(पूर्णांक i)
अणु
	अचिन्हित पूर्णांक exponent;

	update_hwp_winकरोw = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
	हाल OPTARG_BALANCE_POWER:
	हाल OPTARG_NORMAL:
	हाल OPTARG_BALANCE_PERFORMANCE:
	हाल OPTARG_PERFORMANCE:
		वापस 0;
	पूर्ण
	अगर (i < 0 || i > 1270000000) अणु
		ख_लिखो(मानक_त्रुटि, "--hwp-window: 0 for auto; 1 - 1270000000 usec for window duration\n");
		usage();
	पूर्ण
	क्रम (exponent = 0; ; ++exponent) अणु
		अगर (debug)
			म_लिखो("%d 10^%d\न", i, exponent);

		अगर (i <= 127)
			अवरोध;

		i = i / 10;
	पूर्ण
	अगर (debug)
		ख_लिखो(मानक_त्रुटि, "%d*10^%d: 0x%x\न", i, exponent, (exponent << 7) | i);

	वापस (exponent << 7) | i;
पूर्ण
पूर्णांक parse_cmdline_hwp_epp(पूर्णांक i)
अणु
	update_hwp_epp = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
		वापस HWP_EPP_POWERSAVE;
	हाल OPTARG_BALANCE_POWER:
		वापस HWP_EPP_BALANCE_POWERSAVE;
	हाल OPTARG_NORMAL:
	हाल OPTARG_BALANCE_PERFORMANCE:
		वापस HWP_EPP_BALANCE_PERFORMANCE;
	हाल OPTARG_PERFORMANCE:
		वापस HWP_EPP_PERFORMANCE;
	पूर्ण
	अगर (i < 0 || i > 0xff) अणु
		ख_लिखो(मानक_त्रुटि, "--hwp-epp must be from 0 to 0xff\n");
		usage();
	पूर्ण
	वापस i;
पूर्ण
पूर्णांक parse_cmdline_turbo(पूर्णांक i)
अणु
	update_turbo = 1;

	चयन (i) अणु
	हाल OPTARG_POWER:
		वापस 0;
	हाल OPTARG_NORMAL:
	हाल OPTARG_BALANCE_POWER:
	हाल OPTARG_BALANCE_PERFORMANCE:
	हाल OPTARG_PERFORMANCE:
		वापस 1;
	पूर्ण
	अगर (i < 0 || i > 1) अणु
		ख_लिखो(मानक_त्रुटि, "--turbo-enable: 1 to enable, 0 to disable\n");
		usage();
	पूर्ण
	वापस i;
पूर्ण

पूर्णांक parse_optarg_string(अक्षर *s)
अणु
	पूर्णांक i;
	अक्षर *endptr;

	अगर (!म_भेदन(s, "default", 7))
		वापस OPTARG_NORMAL;

	अगर (!म_भेदन(s, "normal", 6))
		वापस OPTARG_NORMAL;

	अगर (!म_भेदन(s, "power", 9))
		वापस OPTARG_POWER;

	अगर (!म_भेदन(s, "balance-power", 17))
		वापस OPTARG_BALANCE_POWER;

	अगर (!म_भेदन(s, "balance-performance", 19))
		वापस OPTARG_BALANCE_PERFORMANCE;

	अगर (!म_भेदन(s, "performance", 11))
		वापस OPTARG_PERFORMANCE;

	i = म_से_दीर्घ(s, &endptr, 0);
	अगर (s == endptr) अणु
		ख_लिखो(मानक_त्रुटि, "no digits in \"%s\"\n", s);
		usage();
	पूर्ण
	अगर (i == दीर्घ_न्यून || i == दीर्घ_उच्च)
		errx(-1, "%s", s);

	अगर (i > 0xFF)
		errx(-1, "%d (0x%x) must be < 256", i, i);

	अगर (i < 0)
		errx(-1, "%d (0x%x) must be >= 0", i, i);
	वापस i;
पूर्ण

व्योम parse_cmdline_all(अक्षर *s)
अणु
	क्रमce++;
	update_hwp_enable = 1;
	req_update.hwp_min = parse_cmdline_hwp_min(parse_optarg_string(s));
	req_update.hwp_max = parse_cmdline_hwp_max(parse_optarg_string(s));
	req_update.hwp_epp = parse_cmdline_hwp_epp(parse_optarg_string(s));
	अगर (has_epb)
		new_epb = parse_cmdline_epb(parse_optarg_string(s));
	turbo_update_value = parse_cmdline_turbo(parse_optarg_string(s));
	req_update.hwp_desired = parse_cmdline_hwp_desired(parse_optarg_string(s));
	req_update.hwp_winकरोw = parse_cmdline_hwp_winकरोw(parse_optarg_string(s));
पूर्ण

व्योम validate_cpu_selected_set(व्योम)
अणु
	पूर्णांक cpu;

	अगर (CPU_COUNT_S(cpu_setsize, cpu_selected_set) == 0)
		errx(0, "no CPUs requested");

	क्रम (cpu = 0; cpu <= max_cpu_num; ++cpu) अणु
		अगर (CPU_ISSET_S(cpu, cpu_setsize, cpu_selected_set))
			अगर (!CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
				errx(1, "Requested cpu% is not present", cpu);
	पूर्ण
पूर्ण

व्योम parse_cmdline_cpu(अक्षर *s)
अणु
	अक्षर *startp, *endp;
	पूर्णांक cpu = 0;

	अगर (pkg_selected_set) अणु
		usage();
		errx(1, "--cpu | --pkg");
	पूर्ण
	cpu_selected_set = CPU_ALLOC((max_cpu_num + 1));
	अगर (cpu_selected_set == शून्य)
		err(1, "cpu_selected_set");
	CPU_ZERO_S(cpu_setsize, cpu_selected_set);

	क्रम (startp = s; startp && *startp;) अणु

		अगर (*startp == ',') अणु
			startp++;
			जारी;
		पूर्ण

		अगर (*startp == '-') अणु
			पूर्णांक end_cpu;

			startp++;
			end_cpu = म_से_दीर्घ(startp, &endp, 10);
			अगर (startp == endp)
				जारी;

			जबतक (cpu <= end_cpu) अणु
				अगर (cpu > max_cpu_num)
					errx(1, "Requested cpu%d exceeds max cpu%d", cpu, max_cpu_num);
				CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
				cpu++;
			पूर्ण
			startp = endp;
			जारी;
		पूर्ण

		अगर (म_भेदन(startp, "all", 3) == 0) अणु
			क्रम (cpu = 0; cpu <= max_cpu_num; cpu += 1) अणु
				अगर (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			पूर्ण
			startp += 3;
			अगर (*startp == 0)
				अवरोध;
		पूर्ण
		/* "--cpu even" is not करोcumented */
		अगर (म_भेदन(startp, "even", 4) == 0) अणु
			क्रम (cpu = 0; cpu <= max_cpu_num; cpu += 2) अणु
				अगर (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			पूर्ण
			startp += 4;
			अगर (*startp == 0)
				अवरोध;
		पूर्ण

		/* "--cpu odd" is not करोcumented */
		अगर (म_भेदन(startp, "odd", 3) == 0) अणु
			क्रम (cpu = 1; cpu <= max_cpu_num; cpu += 2) अणु
				अगर (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			पूर्ण
			startp += 3;
			अगर (*startp == 0)
				अवरोध;
		पूर्ण

		cpu = म_से_दीर्घ(startp, &endp, 10);
		अगर (startp == endp)
			errx(1, "--cpu cpu-set: confused by '%s'", startp);
		अगर (cpu > max_cpu_num)
			errx(1, "Requested cpu%d exceeds max cpu%d", cpu, max_cpu_num);
		CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
		startp = endp;
	पूर्ण

	validate_cpu_selected_set();

पूर्ण

व्योम parse_cmdline_pkg(अक्षर *s)
अणु
	अक्षर *startp, *endp;
	पूर्णांक pkg = 0;

	अगर (cpu_selected_set) अणु
		usage();
		errx(1, "--pkg | --cpu");
	पूर्ण
	pkg_selected_set = 0;

	क्रम (startp = s; startp && *startp;) अणु

		अगर (*startp == ',') अणु
			startp++;
			जारी;
		पूर्ण

		अगर (*startp == '-') अणु
			पूर्णांक end_pkg;

			startp++;
			end_pkg = म_से_दीर्घ(startp, &endp, 10);
			अगर (startp == endp)
				जारी;

			जबतक (pkg <= end_pkg) अणु
				अगर (pkg > max_pkg_num)
					errx(1, "Requested pkg%d exceeds max pkg%d", pkg, max_pkg_num);
				pkg_selected_set |= 1 << pkg;
				pkg++;
			पूर्ण
			startp = endp;
			जारी;
		पूर्ण

		अगर (म_भेदन(startp, "all", 3) == 0) अणु
			pkg_selected_set = pkg_present_set;
			वापस;
		पूर्ण

		pkg = म_से_दीर्घ(startp, &endp, 10);
		अगर (pkg > max_pkg_num)
			errx(1, "Requested pkg%d Exceeds max pkg%d", pkg, max_pkg_num);
		pkg_selected_set |= 1 << pkg;
		startp = endp;
	पूर्ण
पूर्ण

व्योम क्रम_packages(अचिन्हित दीर्घ दीर्घ pkg_set, पूर्णांक (func)(पूर्णांक))
अणु
	पूर्णांक pkg_num;

	क्रम (pkg_num = 0; pkg_num <= max_pkg_num; ++pkg_num) अणु
		अगर (pkg_set & (1UL << pkg_num))
			func(pkg_num);
	पूर्ण
पूर्ण

व्योम prपूर्णांक_version(व्योम)
अणु
	म_लिखो("x86_energy_perf_policy 17.05.11 (C) Len Brown <len.brown@intel.com>\n");
पूर्ण

व्योम cmdline(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;
	पूर्णांक option_index = 0;

	अटल काष्ठा option दीर्घ_options[] = अणु
		अणु"all",		required_argument,	0, 'a'पूर्ण,
		अणु"cpu",		required_argument,	0, 'c'पूर्ण,
		अणु"pkg",		required_argument,	0, 'p'पूर्ण,
		अणु"debug",	no_argument,		0, 'd'पूर्ण,
		अणु"hwp-desired",	required_argument,	0, 'D'पूर्ण,
		अणु"epb",	required_argument,	0, 'B'पूर्ण,
		अणु"force",	no_argument,	0, 'f'पूर्ण,
		अणु"hwp-enable",	no_argument,	0, 'e'पूर्ण,
		अणु"help",	no_argument,	0, 'h'पूर्ण,
		अणु"hwp-epp",	required_argument,	0, 'P'पूर्ण,
		अणु"hwp-min",	required_argument,	0, 'm'पूर्ण,
		अणु"hwp-max",	required_argument,	0, 'M'पूर्ण,
		अणु"read",	no_argument,		0, 'r'पूर्ण,
		अणु"turbo-enable",	required_argument,	0, 't'पूर्ण,
		अणु"hwp-use-pkg",	required_argument,	0, 'u'पूर्ण,
		अणु"version",	no_argument,		0, 'v'पूर्ण,
		अणु"hwp-window",	required_argument,	0, 'w'पूर्ण,
		अणु0,		0,			0, 0 पूर्ण
	पूर्ण;

	progname = argv[0];

	जबतक ((opt = getopt_दीर्घ_only(argc, argv, "+a:c:dD:E:e:f:m:M:rt:u:vw:",
				दीर्घ_options, &option_index)) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			parse_cmdline_all(optarg);
			अवरोध;
		हाल 'B':
			new_epb = parse_cmdline_epb(parse_optarg_string(optarg));
			अवरोध;
		हाल 'c':
			parse_cmdline_cpu(optarg);
			अवरोध;
		हाल 'e':
			update_hwp_enable = 1;
			अवरोध;
		हाल 'h':
			usage();
			अवरोध;
		हाल 'd':
			debug++;
			verbose++;
			अवरोध;
		हाल 'f':
			क्रमce++;
			अवरोध;
		हाल 'D':
			req_update.hwp_desired = parse_cmdline_hwp_desired(parse_optarg_string(optarg));
			अवरोध;
		हाल 'm':
			req_update.hwp_min = parse_cmdline_hwp_min(parse_optarg_string(optarg));
			अवरोध;
		हाल 'M':
			req_update.hwp_max = parse_cmdline_hwp_max(parse_optarg_string(optarg));
			अवरोध;
		हाल 'p':
			parse_cmdline_pkg(optarg);
			अवरोध;
		हाल 'P':
			req_update.hwp_epp = parse_cmdline_hwp_epp(parse_optarg_string(optarg));
			अवरोध;
		हाल 'r':
			/* v1 used -r to specअगरy पढ़ो-only mode, now the शेष */
			अवरोध;
		हाल 't':
			turbo_update_value = parse_cmdline_turbo(parse_optarg_string(optarg));
			अवरोध;
		हाल 'u':
			update_hwp_use_pkg++;
			अगर (म_से_प(optarg) == 0)
				req_update.hwp_use_pkg = 0;
			अन्यथा
				req_update.hwp_use_pkg = 1;
			अवरोध;
		हाल 'v':
			prपूर्णांक_version();
			निकास(0);
			अवरोध;
		हाल 'w':
			req_update.hwp_winकरोw = parse_cmdline_hwp_winकरोw(parse_optarg_string(optarg));
			अवरोध;
		शेष:
			usage();
		पूर्ण
	पूर्ण
	/*
	 * v1 allowed "performance"|"normal"|"power" with no policy specअगरier
	 * to update BIAS.  Continue to support that, even though no दीर्घer करोcumented.
	 */
	अगर (argc == optind + 1)
		new_epb = parse_cmdline_epb(parse_optarg_string(argv[optind]));

	अगर (argc > optind + 1) अणु
		ख_लिखो(मानक_त्रुटि, "stray parameter '%s'\n", argv[optind + 1]);
		usage();
	पूर्ण
पूर्ण

/*
 * Open a file, and निकास on failure
 */
खाता *ख_खोलो_or_die(स्थिर अक्षर *path, स्थिर अक्षर *mode)
अणु
	खाता *filep = ख_खोलो(path, "r");

	अगर (!filep)
		err(1, "%s: open failed", path);
	वापस filep;
पूर्ण

व्योम err_on_hypervisor(व्योम)
अणु
	खाता *cpuinfo;
	अक्षर *flags, *hypervisor;
	अक्षर *buffer;

	/* On VMs /proc/cpuinfo contains a "flags" entry क्रम hypervisor */
	cpuinfo = ख_खोलो_or_die("/proc/cpuinfo", "ro");

	buffer = दो_स्मृति(4096);
	अगर (!buffer) अणु
		ख_बंद(cpuinfo);
		err(-ENOMEM, "buffer malloc fail");
	पूर्ण

	अगर (!ख_पढ़ो(buffer, 1024, 1, cpuinfo)) अणु
		ख_बंद(cpuinfo);
		मुक्त(buffer);
		err(1, "Reading /proc/cpuinfo failed");
	पूर्ण

	flags = म_माला(buffer, "flags");
	शुरुआत(cpuinfo);
	ख_जाओ(cpuinfo, flags - buffer, शुरू_से);
	अगर (!ख_माला_लो(buffer, 4096, cpuinfo)) अणु
		ख_बंद(cpuinfo);
		मुक्त(buffer);
		err(1, "Reading /proc/cpuinfo failed");
	पूर्ण
	ख_बंद(cpuinfo);

	hypervisor = म_माला(buffer, "hypervisor");

	मुक्त(buffer);

	अगर (hypervisor)
		err(-1,
		    "not supported on this virtual machine");
पूर्ण

पूर्णांक get_msr(पूर्णांक cpu, पूर्णांक offset, अचिन्हित दीर्घ दीर्घ *msr)
अणु
	पूर्णांक retval;
	अक्षर pathname[32];
	पूर्णांक fd;

	प्र_लिखो(pathname, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(pathname, O_RDONLY);
	अगर (fd < 0)
		err(-1, "%s open failed, try chown or chmod +r /dev/cpu/*/msr, or run as root", pathname);

	retval = pपढ़ो(fd, msr, माप(*msr), offset);
	अगर (retval != माप(*msr)) अणु
		err_on_hypervisor();
		err(-1, "%s offset 0x%llx read failed", pathname, (अचिन्हित दीर्घ दीर्घ)offset);
	पूर्ण

	अगर (debug > 1)
		ख_लिखो(मानक_त्रुटि, "get_msr(cpu%d, 0x%X, 0x%llX)\n", cpu, offset, *msr);

	बंद(fd);
	वापस 0;
पूर्ण

पूर्णांक put_msr(पूर्णांक cpu, पूर्णांक offset, अचिन्हित दीर्घ दीर्घ new_msr)
अणु
	अक्षर pathname[32];
	पूर्णांक retval;
	पूर्णांक fd;

	प्र_लिखो(pathname, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(pathname, O_RDWR);
	अगर (fd < 0)
		err(-1, "%s open failed, try chown or chmod +r /dev/cpu/*/msr, or run as root", pathname);

	retval = pग_लिखो(fd, &new_msr, माप(new_msr), offset);
	अगर (retval != माप(new_msr))
		err(-2, "pwrite(cpu%d, offset 0x%x, 0x%llx) = %d", cpu, offset, new_msr, retval);

	बंद(fd);

	अगर (debug > 1)
		ख_लिखो(मानक_त्रुटि, "put_msr(cpu%d, 0x%X, 0x%llX)\n", cpu, offset, new_msr);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_sysfs(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen)
अणु
	sमाप_प्रकार numपढ़ो;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस 0;

	numपढ़ो = पढ़ो(fd, buf, buflen - 1);
	अगर (numपढ़ो < 1) अणु
		बंद(fd);
		वापस 0;
	पूर्ण

	buf[numपढ़ो] = '\0';
	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numपढ़ो;
पूर्ण

अटल अचिन्हित पूर्णांक ग_लिखो_sysfs(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen)
अणु
	sमाप_प्रकार numwritten;
	पूर्णांक fd;

	fd = खोलो(path, O_WRONLY);
	अगर (fd == -1)
		वापस 0;

	numwritten = ग_लिखो(fd, buf, buflen - 1);
	अगर (numwritten < 1) अणु
		लिखो_त्रुटि("write failed\n");
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numwritten;
पूर्ण

व्योम prपूर्णांक_hwp_cap(पूर्णांक cpu, काष्ठा msr_hwp_cap *cap, अक्षर *str)
अणु
	अगर (cpu != -1)
		म_लिखो("cpu%d: ", cpu);

	म_लिखो("HWP_CAP: low %d eff %d guar %d high %d\n",
		cap->lowest, cap->efficient, cap->guaranteed, cap->highest);
पूर्ण
व्योम पढ़ो_hwp_cap(पूर्णांक cpu, काष्ठा msr_hwp_cap *cap, अचिन्हित पूर्णांक msr_offset)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(cpu, msr_offset, &msr);

	cap->highest = msr_perf_2_ratio(HWP_HIGHEST_PERF(msr));
	cap->guaranteed = msr_perf_2_ratio(HWP_GUARANTEED_PERF(msr));
	cap->efficient = msr_perf_2_ratio(HWP_MOSTEFFICIENT_PERF(msr));
	cap->lowest = msr_perf_2_ratio(HWP_LOWEST_PERF(msr));
पूर्ण

व्योम prपूर्णांक_hwp_request(पूर्णांक cpu, काष्ठा msr_hwp_request *h, अक्षर *str)
अणु
	अगर (cpu != -1)
		म_लिखो("cpu%d: ", cpu);

	अगर (str)
		म_लिखो("%s", str);

	म_लिखो("HWP_REQ: min %d max %d des %d epp %d winकरोw 0x%x (%d*10^%dus) use_pkg %d\न",
		h->hwp_min, h->hwp_max, h->hwp_desired, h->hwp_epp,
		h->hwp_winकरोw, h->hwp_winकरोw & 0x7F, (h->hwp_winकरोw >> 7) & 0x7, h->hwp_use_pkg);
पूर्ण
व्योम prपूर्णांक_hwp_request_pkg(पूर्णांक pkg, काष्ठा msr_hwp_request *h, अक्षर *str)
अणु
	म_लिखो("pkg%d: ", pkg);

	अगर (str)
		म_लिखो("%s", str);

	म_लिखो("HWP_REQ_PKG: min %d max %d des %d epp %d winकरोw 0x%x (%d*10^%dus)\न",
		h->hwp_min, h->hwp_max, h->hwp_desired, h->hwp_epp,
		h->hwp_winकरोw, h->hwp_winकरोw & 0x7F, (h->hwp_winकरोw >> 7) & 0x7);
पूर्ण
व्योम पढ़ो_hwp_request(पूर्णांक cpu, काष्ठा msr_hwp_request *hwp_req, अचिन्हित पूर्णांक msr_offset)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(cpu, msr_offset, &msr);

	hwp_req->hwp_min = msr_perf_2_ratio((((msr) >> 0) & 0xff));
	hwp_req->hwp_max = msr_perf_2_ratio((((msr) >> 8) & 0xff));
	hwp_req->hwp_desired = msr_perf_2_ratio((((msr) >> 16) & 0xff));
	hwp_req->hwp_epp = (((msr) >> 24) & 0xff);
	hwp_req->hwp_winकरोw = (((msr) >> 32) & 0x3ff);
	hwp_req->hwp_use_pkg = (((msr) >> 42) & 0x1);
पूर्ण

व्योम ग_लिखो_hwp_request(पूर्णांक cpu, काष्ठा msr_hwp_request *hwp_req, अचिन्हित पूर्णांक msr_offset)
अणु
	अचिन्हित दीर्घ दीर्घ msr = 0;

	अगर (debug > 1)
		म_लिखो("cpu%d: requesting min %d max %d des %d epp %d window 0x%0x use_pkg %d\n",
			cpu, hwp_req->hwp_min, hwp_req->hwp_max,
			hwp_req->hwp_desired, hwp_req->hwp_epp,
			hwp_req->hwp_winकरोw, hwp_req->hwp_use_pkg);

	msr |= HWP_MIN_PERF(ratio_2_msr_perf(hwp_req->hwp_min));
	msr |= HWP_MAX_PERF(ratio_2_msr_perf(hwp_req->hwp_max));
	msr |= HWP_DESIRED_PERF(ratio_2_msr_perf(hwp_req->hwp_desired));
	msr |= HWP_ENERGY_PERF_PREFERENCE(hwp_req->hwp_epp);
	msr |= HWP_ACTIVITY_WINDOW(hwp_req->hwp_winकरोw);
	msr |= HWP_PACKAGE_CONTROL(hwp_req->hwp_use_pkg);

	put_msr(cpu, msr_offset, msr);
पूर्ण

अटल पूर्णांक get_epb(पूर्णांक cpu)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	अक्षर linebuf[3];
	अक्षर *endp;
	दीर्घ val;

	अगर (!has_epb)
		वापस -1;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/power/energy_perf_bias", cpu);

	अगर (!पढ़ो_sysfs(path, linebuf, 3))
		वापस -1;

	val = म_से_दीर्घ(linebuf, &endp, 0);
	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस -1;

	वापस (पूर्णांक)val;
पूर्ण

अटल पूर्णांक set_epb(पूर्णांक cpu, पूर्णांक val)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	अक्षर linebuf[3];
	अक्षर *endp;
	पूर्णांक ret;

	अगर (!has_epb)
		वापस -1;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/power/energy_perf_bias", cpu);
	snम_लिखो(linebuf, माप(linebuf), "%d", val);

	ret = ग_लिखो_sysfs(path, linebuf, 3);
	अगर (ret <= 0)
		वापस -1;

	val = म_से_दीर्घ(linebuf, &endp, 0);
	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस -1;

	वापस (पूर्णांक)val;
पूर्ण

पूर्णांक prपूर्णांक_cpu_msrs(पूर्णांक cpu)
अणु
	काष्ठा msr_hwp_request req;
	काष्ठा msr_hwp_cap cap;
	पूर्णांक epb;

	epb = get_epb(cpu);
	अगर (epb >= 0)
		म_लिखो("cpu%d: EPB %u\n", cpu, (अचिन्हित पूर्णांक) epb);

	अगर (!has_hwp)
		वापस 0;

	पढ़ो_hwp_request(cpu, &req, MSR_HWP_REQUEST);
	prपूर्णांक_hwp_request(cpu, &req, "");

	पढ़ो_hwp_cap(cpu, &cap, MSR_HWP_CAPABILITIES);
	prपूर्णांक_hwp_cap(cpu, &cap, "");

	वापस 0;
पूर्ण

पूर्णांक prपूर्णांक_pkg_msrs(पूर्णांक pkg)
अणु
	काष्ठा msr_hwp_request req;
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!has_hwp)
		वापस 0;

	पढ़ो_hwp_request(first_cpu_in_pkg[pkg], &req, MSR_HWP_REQUEST_PKG);
	prपूर्णांक_hwp_request_pkg(pkg, &req, "");

	अगर (has_hwp_notअगरy) अणु
		get_msr(first_cpu_in_pkg[pkg], MSR_HWP_INTERRUPT, &msr);
		ख_लिखो(मानक_त्रुटि,
		"pkg%d: MSR_HWP_INTERRUPT: 0x%08llx (Excursion_Min-%sabled, Guaranteed_Perf_Change-%sabled)\n",
		pkg, msr,
		((msr) & 0x2) ? "EN" : "Dis",
		((msr) & 0x1) ? "EN" : "Dis");
	पूर्ण
	get_msr(first_cpu_in_pkg[pkg], MSR_HWP_STATUS, &msr);
	ख_लिखो(मानक_त्रुटि,
		"pkg%d: MSR_HWP_STATUS: 0x%08llx (%sExcursion_Min, %sGuaranteed_Perf_Change)\n",
		pkg, msr,
		((msr) & 0x4) ? "" : "No-",
		((msr) & 0x1) ? "" : "No-");

	वापस 0;
पूर्ण

/*
 * Assumption: All HWP प्रणालीs have 100 MHz bus घड़ी
 */
पूर्णांक ratio_2_sysfs_khz(पूर्णांक ratio)
अणु
	पूर्णांक bclk_khz = 100 * 1000;	/* 100,000 KHz = 100 MHz */

	वापस ratio * bclk_khz;
पूर्ण
/*
 * If HWP is enabled and cpufreq sysfs attribtes are present,
 * then update sysfs, so that it will not become
 * stale when we ग_लिखो to MSRs.
 * (पूर्णांकel_pstate's max_perf_pct and min_perf_pct will follow cpufreq,
 *  so we करोn't have to touch that.)
 */
व्योम update_cpufreq_scaling_freq(पूर्णांक is_max, पूर्णांक cpu, अचिन्हित पूर्णांक ratio)
अणु
	अक्षर pathname[64];
	खाता *fp;
	पूर्णांक retval;
	पूर्णांक khz;

	प्र_लिखो(pathname, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_%s_freq",
		cpu, is_max ? "max" : "min");

	fp = ख_खोलो(pathname, "w");
	अगर (!fp) अणु
		अगर (debug)
			लिखो_त्रुटि(pathname);
		वापस;
	पूर्ण

	khz = ratio_2_sysfs_khz(ratio);
	retval = ख_लिखो(fp, "%d", khz);
	अगर (retval < 0)
		अगर (debug)
			लिखो_त्रुटि("fprintf");
	अगर (debug)
		म_लिखो("echo %d > %s\n", khz, pathname);

	ख_बंद(fp);
पूर्ण

/*
 * We update all sysfs beक्रमe updating any MSRs because of
 * bugs in cpufreq/पूर्णांकel_pstate where the sysfs ग_लिखोs
 * क्रम a CPU may change the min/max values on other CPUS.
 */

पूर्णांक update_sysfs(पूर्णांक cpu)
अणु
	अगर (!has_hwp)
		वापस 0;

	अगर (!hwp_update_enabled())
		वापस 0;

	अगर (access("/sys/devices/system/cpu/cpu0/cpufreq", F_OK))
		वापस 0;

	अगर (update_hwp_min)
		update_cpufreq_scaling_freq(0, cpu, req_update.hwp_min);

	अगर (update_hwp_max)
		update_cpufreq_scaling_freq(1, cpu, req_update.hwp_max);

	वापस 0;
पूर्ण

पूर्णांक verअगरy_hwp_req_self_consistency(पूर्णांक cpu, काष्ठा msr_hwp_request *req)
अणु
	/* fail अगर min > max requested */
	अगर (req->hwp_min > req->hwp_max) अणु
		errx(1, "cpu%d: requested hwp-min %d > hwp_max %d",
			cpu, req->hwp_min, req->hwp_max);
	पूर्ण

	/* fail अगर desired > max requestd */
	अगर (req->hwp_desired && (req->hwp_desired > req->hwp_max)) अणु
		errx(1, "cpu%d: requested hwp-desired %d > hwp_max %d",
			cpu, req->hwp_desired, req->hwp_max);
	पूर्ण
	/* fail अगर desired < min requestd */
	अगर (req->hwp_desired && (req->hwp_desired < req->hwp_min)) अणु
		errx(1, "cpu%d: requested hwp-desired %d < requested hwp_min %d",
			cpu, req->hwp_desired, req->hwp_min);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक check_hwp_request_v_hwp_capabilities(पूर्णांक cpu, काष्ठा msr_hwp_request *req, काष्ठा msr_hwp_cap *cap)
अणु
	अगर (update_hwp_max) अणु
		अगर (req->hwp_max > cap->highest)
			errx(1, "cpu%d: requested max %d > capabilities highest %d, use --force?",
				cpu, req->hwp_max, cap->highest);
		अगर (req->hwp_max < cap->lowest)
			errx(1, "cpu%d: requested max %d < capabilities lowest %d, use --force?",
				cpu, req->hwp_max, cap->lowest);
	पूर्ण

	अगर (update_hwp_min) अणु
		अगर (req->hwp_min > cap->highest)
			errx(1, "cpu%d: requested min %d > capabilities highest %d, use --force?",
				cpu, req->hwp_min, cap->highest);
		अगर (req->hwp_min < cap->lowest)
			errx(1, "cpu%d: requested min %d < capabilities lowest %d, use --force?",
				cpu, req->hwp_min, cap->lowest);
	पूर्ण

	अगर (update_hwp_min && update_hwp_max && (req->hwp_min > req->hwp_max))
		errx(1, "cpu%d: requested min %d > requested max %d",
			cpu, req->hwp_min, req->hwp_max);

	अगर (update_hwp_desired && req->hwp_desired) अणु
		अगर (req->hwp_desired > req->hwp_max)
			errx(1, "cpu%d: requested desired %d > requested max %d, use --force?",
				cpu, req->hwp_desired, req->hwp_max);
		अगर (req->hwp_desired < req->hwp_min)
			errx(1, "cpu%d: requested desired %d < requested min %d, use --force?",
				cpu, req->hwp_desired, req->hwp_min);
		अगर (req->hwp_desired < cap->lowest)
			errx(1, "cpu%d: requested desired %d < capabilities lowest %d, use --force?",
				cpu, req->hwp_desired, cap->lowest);
		अगर (req->hwp_desired > cap->highest)
			errx(1, "cpu%d: requested desired %d > capabilities highest %d, use --force?",
				cpu, req->hwp_desired, cap->highest);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक update_hwp_request(पूर्णांक cpu)
अणु
	काष्ठा msr_hwp_request req;
	काष्ठा msr_hwp_cap cap;

	पूर्णांक msr_offset = MSR_HWP_REQUEST;

	पढ़ो_hwp_request(cpu, &req, msr_offset);
	अगर (debug)
		prपूर्णांक_hwp_request(cpu, &req, "old: ");

	अगर (update_hwp_min)
		req.hwp_min = req_update.hwp_min;

	अगर (update_hwp_max)
		req.hwp_max = req_update.hwp_max;

	अगर (update_hwp_desired)
		req.hwp_desired = req_update.hwp_desired;

	अगर (update_hwp_winकरोw)
		req.hwp_winकरोw = req_update.hwp_winकरोw;

	अगर (update_hwp_epp)
		req.hwp_epp = req_update.hwp_epp;

	req.hwp_use_pkg = req_update.hwp_use_pkg;

	पढ़ो_hwp_cap(cpu, &cap, MSR_HWP_CAPABILITIES);
	अगर (debug)
		prपूर्णांक_hwp_cap(cpu, &cap, "");

	अगर (!क्रमce)
		check_hwp_request_v_hwp_capabilities(cpu, &req, &cap);

	verअगरy_hwp_req_self_consistency(cpu, &req);

	ग_लिखो_hwp_request(cpu, &req, msr_offset);

	अगर (debug) अणु
		पढ़ो_hwp_request(cpu, &req, msr_offset);
		prपूर्णांक_hwp_request(cpu, &req, "new: ");
	पूर्ण
	वापस 0;
पूर्ण
पूर्णांक update_hwp_request_pkg(पूर्णांक pkg)
अणु
	काष्ठा msr_hwp_request req;
	काष्ठा msr_hwp_cap cap;
	पूर्णांक cpu = first_cpu_in_pkg[pkg];

	पूर्णांक msr_offset = MSR_HWP_REQUEST_PKG;

	पढ़ो_hwp_request(cpu, &req, msr_offset);
	अगर (debug)
		prपूर्णांक_hwp_request_pkg(pkg, &req, "old: ");

	अगर (update_hwp_min)
		req.hwp_min = req_update.hwp_min;

	अगर (update_hwp_max)
		req.hwp_max = req_update.hwp_max;

	अगर (update_hwp_desired)
		req.hwp_desired = req_update.hwp_desired;

	अगर (update_hwp_winकरोw)
		req.hwp_winकरोw = req_update.hwp_winकरोw;

	अगर (update_hwp_epp)
		req.hwp_epp = req_update.hwp_epp;

	पढ़ो_hwp_cap(cpu, &cap, MSR_HWP_CAPABILITIES);
	अगर (debug)
		prपूर्णांक_hwp_cap(cpu, &cap, "");

	अगर (!क्रमce)
		check_hwp_request_v_hwp_capabilities(cpu, &req, &cap);

	verअगरy_hwp_req_self_consistency(cpu, &req);

	ग_लिखो_hwp_request(cpu, &req, msr_offset);

	अगर (debug) अणु
		पढ़ो_hwp_request(cpu, &req, msr_offset);
		prपूर्णांक_hwp_request_pkg(pkg, &req, "new: ");
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक enable_hwp_on_cpu(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	get_msr(cpu, MSR_PM_ENABLE, &msr);
	put_msr(cpu, MSR_PM_ENABLE, 1);

	अगर (verbose)
		म_लिखो("cpu%d: MSR_PM_ENABLE old: %d new: %d\n", cpu, (अचिन्हित पूर्णांक) msr, 1);

	वापस 0;
पूर्ण

पूर्णांक update_cpu_msrs(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ msr;
	पूर्णांक epb;

	अगर (update_epb) अणु
		epb = get_epb(cpu);
		set_epb(cpu, new_epb);

		अगर (verbose)
			म_लिखो("cpu%d: ENERGY_PERF_BIAS old: %d new: %d\n",
				cpu, epb, (अचिन्हित पूर्णांक) new_epb);
	पूर्ण

	अगर (update_turbo) अणु
		पूर्णांक turbo_is_present_and_disabled;

		get_msr(cpu, MSR_IA32_MISC_ENABLE, &msr);

		turbo_is_present_and_disabled = ((msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE) != 0);

		अगर (turbo_update_value == 1)	अणु
			अगर (turbo_is_present_and_disabled) अणु
				msr &= ~MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
				put_msr(cpu, MSR_IA32_MISC_ENABLE, msr);
				अगर (verbose)
					म_लिखो("cpu%d: turbo ENABLE\n", cpu);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * अगर "turbo_is_enabled" were known to be describe this cpu
			 * then we could use it here to skip redundant disable requests.
			 * but cpu may be in a dअगरferent package, so we always ग_लिखो.
			 */
			msr |= MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
			put_msr(cpu, MSR_IA32_MISC_ENABLE, msr);
			अगर (verbose)
				म_लिखो("cpu%d: turbo DISABLE\n", cpu);
		पूर्ण
	पूर्ण

	अगर (!has_hwp)
		वापस 0;

	अगर (!hwp_update_enabled())
		वापस 0;

	update_hwp_request(cpu);
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक get_pkg_num(पूर्णांक cpu)
अणु
	खाता *fp;
	अक्षर pathname[128];
	अचिन्हित पूर्णांक pkg;
	पूर्णांक retval;

	प्र_लिखो(pathname, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id", cpu);

	fp = ख_खोलो_or_die(pathname, "r");
	retval = ख_पूछो(fp, "%d\n", &pkg);
	अगर (retval != 1)
		errx(1, "%s: failed to parse", pathname);
	वापस pkg;
पूर्ण

पूर्णांक set_max_cpu_pkg_num(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक pkg;

	अगर (max_cpu_num < cpu)
		max_cpu_num = cpu;

	pkg = get_pkg_num(cpu);

	अगर (pkg >= MAX_PACKAGES)
		errx(1, "cpu%d: %d >= MAX_PACKAGES (%d)", cpu, pkg, MAX_PACKAGES);

	अगर (pkg > max_pkg_num)
		max_pkg_num = pkg;

	अगर ((pkg_present_set & (1ULL << pkg)) == 0) अणु
		pkg_present_set |= (1ULL << pkg);
		first_cpu_in_pkg[pkg] = cpu;
	पूर्ण

	वापस 0;
पूर्ण
पूर्णांक mark_cpu_present(पूर्णांक cpu)
अणु
	CPU_SET_S(cpu, cpu_setsize, cpu_present_set);
	वापस 0;
पूर्ण

/*
 * run func(cpu) on every cpu in /proc/stat
 * वापस max_cpu number
 */
पूर्णांक क्रम_all_proc_cpus(पूर्णांक (func)(पूर्णांक))
अणु
	खाता *fp;
	पूर्णांक cpu_num;
	पूर्णांक retval;

	fp = ख_खोलो_or_die(proc_stat, "r");

	retval = ख_पूछो(fp, "cpu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\n");
	अगर (retval != 0)
		err(1, "%s: failed to parse format", proc_stat);

	जबतक (1) अणु
		retval = ख_पूछो(fp, "cpu%u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d\n", &cpu_num);
		अगर (retval != 1)
			अवरोध;

		retval = func(cpu_num);
		अगर (retval) अणु
			ख_बंद(fp);
			वापस retval;
		पूर्ण
	पूर्ण
	ख_बंद(fp);
	वापस 0;
पूर्ण

व्योम क्रम_all_cpus_in_set(माप_प्रकार set_size, cpu_set_t *cpu_set, पूर्णांक (func)(पूर्णांक))
अणु
	पूर्णांक cpu_num;

	क्रम (cpu_num = 0; cpu_num <= max_cpu_num; ++cpu_num)
		अगर (CPU_ISSET_S(cpu_num, set_size, cpu_set))
			func(cpu_num);
पूर्ण

व्योम init_data_काष्ठाures(व्योम)
अणु
	क्रम_all_proc_cpus(set_max_cpu_pkg_num);

	cpu_setsize = CPU_ALLOC_SIZE((max_cpu_num + 1));

	cpu_present_set = CPU_ALLOC((max_cpu_num + 1));
	अगर (cpu_present_set == शून्य)
		err(3, "CPU_ALLOC");
	CPU_ZERO_S(cpu_setsize, cpu_present_set);
	क्रम_all_proc_cpus(mark_cpu_present);
पूर्ण

/* clear has_hwp अगर it is not enable (or being enabled) */

व्योम verअगरy_hwp_is_enabled(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ msr;

	अगर (!has_hwp)	/* set in early_cpuid() */
		वापस;

	/* MSR_PM_ENABLE[1] == 1 अगर HWP is enabled and MSRs visible */
	get_msr(base_cpu, MSR_PM_ENABLE, &msr);
	अगर ((msr & 1) == 0) अणु
		ख_लिखो(मानक_त्रुटि, "HWP can be enabled using '--hwp-enable'\n");
		has_hwp = 0;
		वापस;
	पूर्ण
पूर्ण

पूर्णांक req_update_bounds_check(व्योम)
अणु
	अगर (!hwp_update_enabled())
		वापस 0;

	/* fail अगर min > max requested */
	अगर ((update_hwp_max && update_hwp_min) &&
	    (req_update.hwp_min > req_update.hwp_max)) अणु
		म_लिखो("hwp-min %d > hwp_max %d\n", req_update.hwp_min, req_update.hwp_max);
		वापस -EINVAL;
	पूर्ण

	/* fail अगर desired > max requestd */
	अगर (req_update.hwp_desired && update_hwp_max &&
	    (req_update.hwp_desired > req_update.hwp_max)) अणु
		म_लिखो("hwp-desired cannot be greater than hwp_max\n");
		वापस -EINVAL;
	पूर्ण
	/* fail अगर desired < min requestd */
	अगर (req_update.hwp_desired && update_hwp_min &&
	    (req_update.hwp_desired < req_update.hwp_min)) अणु
		म_लिखो("hwp-desired cannot be less than hwp_min\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम set_base_cpu(व्योम)
अणु
	base_cpu = sched_अ_लोpu();
	अगर (base_cpu < 0)
		err(-ENODEV, "No valid cpus found");
पूर्ण


व्योम probe_dev_msr(व्योम)
अणु
	काष्ठा stat sb;
	अक्षर pathname[32];

	प्र_लिखो(pathname, "/dev/cpu/%d/msr", base_cpu);
	अगर (stat(pathname, &sb))
		अगर (प्रणाली("/sbin/modprobe msr > /dev/null 2>&1"))
			err(-5, "no /dev/cpu/0/msr, Try \"# modprobe msr\" ");
पूर्ण

अटल व्योम get_cpuid_or_निकास(अचिन्हित पूर्णांक leaf,
			     अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
			     अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	अगर (!__get_cpuid(leaf, eax, ebx, ecx, edx))
		errx(1, "Processor not supported\n");
पूर्ण

/*
 * early_cpuid()
 * initialize turbo_is_enabled, has_hwp, has_epb
 * beक्रमe cmdline is parsed
 */
व्योम early_cpuid(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक fms, family, model;

	get_cpuid_or_निकास(1, &fms, &ebx, &ecx, &edx);
	family = (fms >> 8) & 0xf;
	model = (fms >> 4) & 0xf;
	अगर (family == 6 || family == 0xf)
		model += ((fms >> 16) & 0xf) << 4;

	अगर (model == 0x4F) अणु
		अचिन्हित दीर्घ दीर्घ msr;

		get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);

		bdx_highest_ratio = msr & 0xFF;
	पूर्ण

	get_cpuid_or_निकास(0x6, &eax, &ebx, &ecx, &edx);
	turbo_is_enabled = (eax >> 1) & 1;
	has_hwp = (eax >> 7) & 1;
	has_epb = (ecx >> 3) & 1;
पूर्ण

/*
 * parse_cpuid()
 * set
 * has_hwp, has_hwp_notअगरy, has_hwp_activity_winकरोw, has_hwp_epp, has_hwp_request_pkg, has_epb
 */
व्योम parse_cpuid(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx, max_level;
	अचिन्हित पूर्णांक fms, family, model, stepping;

	eax = ebx = ecx = edx = 0;

	get_cpuid_or_निकास(0, &max_level, &ebx, &ecx, &edx);

	अगर (ebx == 0x756e6547 && edx == 0x49656e69 && ecx == 0x6c65746e)
		genuine_पूर्णांकel = 1;

	अगर (debug)
		ख_लिखो(मानक_त्रुटि, "CPUID(0): %.4s%.4s%.4s ",
			(अक्षर *)&ebx, (अक्षर *)&edx, (अक्षर *)&ecx);

	get_cpuid_or_निकास(1, &fms, &ebx, &ecx, &edx);
	family = (fms >> 8) & 0xf;
	model = (fms >> 4) & 0xf;
	stepping = fms & 0xf;
	अगर (family == 6 || family == 0xf)
		model += ((fms >> 16) & 0xf) << 4;

	अगर (debug) अणु
		ख_लिखो(मानक_त्रुटि, "%d CPUID levels; family:model:stepping 0x%x:%x:%x (%d:%d:%d)\n",
			max_level, family, model, stepping, family, model, stepping);
		ख_लिखो(मानक_त्रुटि, "CPUID(1): %s %s %s %s %s %s %s %s\n",
			ecx & (1 << 0) ? "SSE3" : "-",
			ecx & (1 << 3) ? "MONITOR" : "-",
			ecx & (1 << 7) ? "EIST" : "-",
			ecx & (1 << 8) ? "TM2" : "-",
			edx & (1 << 4) ? "TSC" : "-",
			edx & (1 << 5) ? "MSR" : "-",
			edx & (1 << 22) ? "ACPI-TM" : "-",
			edx & (1 << 29) ? "TM" : "-");
	पूर्ण

	अगर (!(edx & (1 << 5)))
		errx(1, "CPUID: no MSR");


	get_cpuid_or_निकास(0x6, &eax, &ebx, &ecx, &edx);
	/* turbo_is_enabled alपढ़ोy set */
	/* has_hwp alपढ़ोy set */
	has_hwp_notअगरy = eax & (1 << 8);
	has_hwp_activity_winकरोw = eax & (1 << 9);
	has_hwp_epp = eax & (1 << 10);
	has_hwp_request_pkg = eax & (1 << 11);

	अगर (!has_hwp_request_pkg && update_hwp_use_pkg)
		errx(1, "--hwp-use-pkg is not available on this hardware");

	/* has_epb alपढ़ोy set */

	अगर (debug)
		ख_लिखो(मानक_त्रुटि,
			"CPUID(6): %sTURBO, %sHWP, %sHWPnotify, %sHWPwindow, %sHWPepp, %sHWPpkg, %sEPB\n",
			turbo_is_enabled ? "" : "No-",
			has_hwp ? "" : "No-",
			has_hwp_notअगरy ? "" : "No-",
			has_hwp_activity_winकरोw ? "" : "No-",
			has_hwp_epp ? "" : "No-",
			has_hwp_request_pkg ? "" : "No-",
			has_epb ? "" : "No-");

	वापस;	/* success */
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	set_base_cpu();
	probe_dev_msr();
	init_data_काष्ठाures();

	early_cpuid();	/* initial cpuid parse beक्रमe cmdline */

	cmdline(argc, argv);

	अगर (debug)
		prपूर्णांक_version();

	parse_cpuid();

	 /* If CPU-set and PKG-set are not initialized, शेष to all CPUs */
	अगर ((cpu_selected_set == 0) && (pkg_selected_set == 0))
		cpu_selected_set = cpu_present_set;

	/*
	 * If HWP is being enabled, करो it now, so that subsequent operations
	 * that access HWP रेजिस्टरs can work.
	 */
	अगर (update_hwp_enable)
		क्रम_all_cpus_in_set(cpu_setsize, cpu_selected_set, enable_hwp_on_cpu);

	/* If HWP present, but disabled, warn and ignore from here क्रमward */
	verअगरy_hwp_is_enabled();

	अगर (req_update_bounds_check())
		वापस -EINVAL;

	/* display inक्रमmation only, no updates to settings */
	अगर (!update_epb && !update_turbo && !hwp_update_enabled()) अणु
		अगर (cpu_selected_set)
			क्रम_all_cpus_in_set(cpu_setsize, cpu_selected_set, prपूर्णांक_cpu_msrs);

		अगर (has_hwp_request_pkg) अणु
			अगर (pkg_selected_set == 0)
				pkg_selected_set = pkg_present_set;

			क्रम_packages(pkg_selected_set, prपूर्णांक_pkg_msrs);
		पूर्ण

		वापस 0;
	पूर्ण

	/* update CPU set */
	अगर (cpu_selected_set) अणु
		क्रम_all_cpus_in_set(cpu_setsize, cpu_selected_set, update_sysfs);
		क्रम_all_cpus_in_set(cpu_setsize, cpu_selected_set, update_cpu_msrs);
	पूर्ण अन्यथा अगर (pkg_selected_set)
		क्रम_packages(pkg_selected_set, update_hwp_request_pkg);

	वापस 0;
पूर्ण
