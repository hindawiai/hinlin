<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2011 Thomas Renninger <trenn@suse.de>, Novell Inc.
 */


#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <getopt.h>
#समावेश <sys/utsname.h>

#समावेश "helpers/helpers.h"
#समावेश "helpers/sysfs.h"

अटल काष्ठा option set_opts[] = अणु
     अणु"perf-bias", optional_argument, शून्य, 'b'पूर्ण,
     अणु पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_wrong_arg_निकास(व्योम)
अणु
	म_लिखो(_("invalid or unknown argument\n"));
	निकास(निकास_त्रुटि);
पूर्ण

पूर्णांक cmd_info(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind, opterr, optopt;
	अचिन्हित पूर्णांक cpu;
	काष्ठा utsname uts;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक perf_bias:1;
		पूर्ण;
		पूर्णांक params;
	पूर्ण params = अणुपूर्ण;
	पूर्णांक ret = 0;

	ret = uname(&uts);
	अगर (!ret && (!म_भेद(uts.machine, "ppc64le") ||
		     !म_भेद(uts.machine, "ppc64"))) अणु
		ख_लिखो(मानक_त्रुटि, _("Subcommand not supported on POWER.\n"));
		वापस ret;
	पूर्ण

	रखो_क्षेत्र(LC_ALL, "");
	textकरोमुख्य(PACKAGE);

	/* parameter parsing */
	जबतक ((ret = getopt_दीर्घ(argc, argv, "b", set_opts, शून्य)) != -1) अणु
		चयन (ret) अणु
		हाल 'b':
			अगर (params.perf_bias)
				prपूर्णांक_wrong_arg_निकास();
			params.perf_bias = 1;
			अवरोध;
		शेष:
			prपूर्णांक_wrong_arg_निकास();
		पूर्ण
	पूर्ण

	अगर (!params.params)
		params.params = 0x7;

	/* Default is: show output of CPU 0 only */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setbit(cpus_chosen, 0);

	/* Add more per cpu options here */
	अगर (!params.perf_bias)
		वापस ret;

	अगर (params.perf_bias) अणु
		अगर (!run_as_root) अणु
			params.perf_bias = 0;
			म_लिखो(_("Intel's performance bias setting needs root privileges\n"));
		पूर्ण अन्यथा अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_PERF_BIAS)) अणु
			म_लिखो(_("System does not support Intel's performance"
				 " bias setting\n"));
			params.perf_bias = 0;
		पूर्ण
	पूर्ण

	/* loop over CPUs */
	क्रम (cpu = biपंचांगask_first(cpus_chosen);
	     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (!biपंचांगask_isbitset(cpus_chosen, cpu))
			जारी;

		म_लिखो(_("analyzing CPU %d:\n"), cpu);

		अगर (sysfs_is_cpu_online(cpu) != 1)अणु
			म_लिखो(_(" *is offline\n"));
			जारी;
		पूर्ण

		अगर (params.perf_bias) अणु
			ret = cpuघातer_पूर्णांकel_get_perf_bias(cpu);
			अगर (ret < 0) अणु
				ख_लिखो(मानक_त्रुटि,
			_("Could not read perf-bias value[%d]\n"), ret);
				निकास(निकास_त्रुटि);
			पूर्ण अन्यथा
				म_लिखो(_("perf-bias: %d\n"), ret);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
