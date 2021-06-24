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
#समावेश "helpers/bitmask.h"

अटल काष्ठा option set_opts[] = अणु
	अणु"perf-bias", required_argument, शून्य, 'b'पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_wrong_arg_निकास(व्योम)
अणु
	म_लिखो(_("invalid or unknown argument\n"));
	निकास(निकास_त्रुटि);
पूर्ण

पूर्णांक cmd_set(पूर्णांक argc, अक्षर **argv)
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
	पूर्ण params;
	पूर्णांक perf_bias = 0;
	पूर्णांक ret = 0;

	ret = uname(&uts);
	अगर (!ret && (!म_भेद(uts.machine, "ppc64le") ||
		     !म_भेद(uts.machine, "ppc64"))) अणु
		ख_लिखो(मानक_त्रुटि, _("Subcommand not supported on POWER.\n"));
		वापस ret;
	पूर्ण

	रखो_क्षेत्र(LC_ALL, "");
	textकरोमुख्य(PACKAGE);

	params.params = 0;
	/* parameter parsing */
	जबतक ((ret = getopt_दीर्घ(argc, argv, "b:",
						set_opts, शून्य)) != -1) अणु
		चयन (ret) अणु
		हाल 'b':
			अगर (params.perf_bias)
				prपूर्णांक_wrong_arg_निकास();
			perf_bias = म_से_प(optarg);
			अगर (perf_bias < 0 || perf_bias > 15) अणु
				म_लिखो(_("--perf-bias param out "
					 "of range [0-%d]\n"), 15);
				prपूर्णांक_wrong_arg_निकास();
			पूर्ण
			params.perf_bias = 1;
			अवरोध;
		शेष:
			prपूर्णांक_wrong_arg_निकास();
		पूर्ण
	पूर्ण

	अगर (!params.params)
		prपूर्णांक_wrong_arg_निकास();

	/* Default is: set all CPUs */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setall(cpus_chosen);

	/* loop over CPUs */
	क्रम (cpu = biपंचांगask_first(cpus_chosen);
	     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (!biपंचांगask_isbitset(cpus_chosen, cpu))
			जारी;

		अगर (sysfs_is_cpu_online(cpu) != 1)अणु
			ख_लिखो(मानक_त्रुटि, _("Cannot set values on CPU %d:"), cpu);
			ख_लिखो(मानक_त्रुटि, _(" *is offline\n"));
			जारी;
		पूर्ण

		अगर (params.perf_bias) अणु
			ret = cpuघातer_पूर्णांकel_set_perf_bias(cpu, perf_bias);
			अगर (ret) अणु
				ख_लिखो(मानक_त्रुटि, _("Error setting perf-bias "
						  "value on CPU %d\n"), cpu);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
