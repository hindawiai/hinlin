<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <getopt.h>

#समावेश <cpufreq.h>
#समावेश <cpuidle.h>

#समावेश "helpers/helpers.h"

अटल काष्ठा option info_opts[] = अणु
     अणु"disable",	required_argument,		शून्य, 'd'पूर्ण,
     अणु"enable",		required_argument,		शून्य, 'e'पूर्ण,
     अणु"disable-by-latency", required_argument,		शून्य, 'D'पूर्ण,
     अणु"enable-all",	no_argument,			शून्य, 'E'पूर्ण,
     अणु पूर्ण,
पूर्ण;


पूर्णांक cmd_idle_set(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind, opterr, optopt;
	पूर्णांक ret = 0, cont = 1, param = 0, disabled;
	अचिन्हित दीर्घ दीर्घ latency = 0, state_latency;
	अचिन्हित पूर्णांक cpu = 0, idlestate = 0, idlestates = 0;
	अक्षर *endptr;

	करो अणु
		ret = getopt_दीर्घ(argc, argv, "d:e:ED:", info_opts, शून्य);
		अगर (ret == -1)
			अवरोध;
		चयन (ret) अणु
		हाल '?':
			param = '?';
			cont = 0;
			अवरोध;
		हाल 'd':
			अगर (param) अणु
				param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			param = ret;
			idlestate = म_से_प(optarg);
			अवरोध;
		हाल 'e':
			अगर (param) अणु
				param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			param = ret;
			idlestate = म_से_प(optarg);
			अवरोध;
		हाल 'D':
			अगर (param) अणु
				param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			param = ret;
			latency = म_से_अदीर्घl(optarg, &endptr, 10);
			अगर (*endptr != '\0') अणु
				म_लिखो(_("Bad latency value: %s\n"), optarg);
				निकास(निकास_त्रुटि);
			पूर्ण
			अवरोध;
		हाल 'E':
			अगर (param) अणु
				param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			param = ret;
			अवरोध;
		हाल -1:
			cont = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (cont);

	चयन (param) अणु
	हाल -1:
		म_लिखो(_("You can't specify more than one "
			 "output-specific argument\n"));
		निकास(निकास_त्रुटि);
	हाल '?':
		म_लिखो(_("invalid or unknown argument\n"));
		निकास(निकास_त्रुटि);
	पूर्ण

	get_cpustate();

	/* Default is: set all CPUs */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setall(cpus_chosen);

	क्रम (cpu = biपंचांगask_first(cpus_chosen);
	     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (!biपंचांगask_isbitset(cpus_chosen, cpu))
			जारी;

		अगर (cpuघातer_is_cpu_online(cpu) != 1)
			जारी;

		idlestates = cpuidle_state_count(cpu);
		अगर (idlestates <= 0)
			जारी;

		चयन (param) अणु
		हाल 'd':
			ret = cpuidle_state_disable(cpu, idlestate, 1);
			अगर (ret == 0)
		म_लिखो(_("Idlestate %u disabled on CPU %u\n"),  idlestate, cpu);
			अन्यथा अगर (ret == -1)
		म_लिखो(_("Idlestate %u not available on CPU %u\n"),
		       idlestate, cpu);
			अन्यथा अगर (ret == -2)
		म_लिखो(_("Idlestate disabling not supported by kernel\n"));
			अन्यथा
		म_लिखो(_("Idlestate %u not disabled on CPU %u\n"),
		       idlestate, cpu);
			अवरोध;
		हाल 'e':
			ret = cpuidle_state_disable(cpu, idlestate, 0);
			अगर (ret == 0)
		म_लिखो(_("Idlestate %u enabled on CPU %u\n"),  idlestate, cpu);
			अन्यथा अगर (ret == -1)
		म_लिखो(_("Idlestate %u not available on CPU %u\n"),
		       idlestate, cpu);
			अन्यथा अगर (ret == -2)
		म_लिखो(_("Idlestate enabling not supported by kernel\n"));
			अन्यथा
		म_लिखो(_("Idlestate %u not enabled on CPU %u\n"),
		       idlestate, cpu);
			अवरोध;
		हाल 'D':
			क्रम (idlestate = 0; idlestate < idlestates; idlestate++) अणु
				disabled = cpuidle_is_state_disabled
					(cpu, idlestate);
				state_latency = cpuidle_state_latency
					(cpu, idlestate);
				अगर (disabled == 1) अणु
					अगर (latency > state_latency)अणु
						ret = cpuidle_state_disable
							(cpu, idlestate, 0);
						अगर (ret == 0)
		म_लिखो(_("Idlestate %u enabled on CPU %u\n"),  idlestate, cpu);
					पूर्ण
					जारी;
				पूर्ण
				अगर (latency <= state_latency)अणु
					ret = cpuidle_state_disable
						(cpu, idlestate, 1);
					अगर (ret == 0)
		म_लिखो(_("Idlestate %u disabled on CPU %u\n"), idlestate, cpu);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'E':
			क्रम (idlestate = 0; idlestate < idlestates; idlestate++) अणु
				disabled = cpuidle_is_state_disabled
					(cpu, idlestate);
				अगर (disabled == 1) अणु
					ret = cpuidle_state_disable
						(cpu, idlestate, 0);
					अगर (ret == 0)
		म_लिखो(_("Idlestate %u enabled on CPU %u\n"), idlestate, cpu);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			/* Not reachable with proper args checking */
			म_लिखो(_("Invalid or unknown argument\n"));
			निकास(निकास_त्रुटि);
			अवरोध;
		पूर्ण
	पूर्ण

	prपूर्णांक_offline_cpus();
	वापस निकास_सफल;
पूर्ण
