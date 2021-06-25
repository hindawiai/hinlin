<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 *  (C) 2010       Thomas Renninger <trenn@suse.de>
 */


#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <getopt.h>

#समावेश <cpuidle.h>

#समावेश "helpers/sysfs.h"
#समावेश "helpers/helpers.h"
#समावेश "helpers/bitmask.h"

#घोषणा LINE_LEN 10

अटल व्योम cpuidle_cpu_output(अचिन्हित पूर्णांक cpu, पूर्णांक verbose)
अणु
	अचिन्हित पूर्णांक idlestates, idlestate;
	अक्षर *पंचांगp;

	idlestates = cpuidle_state_count(cpu);
	अगर (idlestates == 0) अणु
		म_लिखो(_("CPU %u: No idle states\n"), cpu);
		वापस;
	पूर्ण

	म_लिखो(_("Number of idle states: %d\n"), idlestates);
	म_लिखो(_("Available idle states:"));
	क्रम (idlestate = 0; idlestate < idlestates; idlestate++) अणु
		पंचांगp = cpuidle_state_name(cpu, idlestate);
		अगर (!पंचांगp)
			जारी;
		म_लिखो(" %s", पंचांगp);
		मुक्त(पंचांगp);
	पूर्ण
	म_लिखो("\n");

	अगर (!verbose)
		वापस;

	क्रम (idlestate = 0; idlestate < idlestates; idlestate++) अणु
		पूर्णांक disabled = cpuidle_is_state_disabled(cpu, idlestate);
		/* Disabled पूर्णांकerface not supported on older kernels */
		अगर (disabled < 0)
			disabled = 0;
		पंचांगp = cpuidle_state_name(cpu, idlestate);
		अगर (!पंचांगp)
			जारी;
		म_लिखो("%s%s:\n", पंचांगp, (disabled) ? " (DISABLED) " : "");
		मुक्त(पंचांगp);

		पंचांगp = cpuidle_state_desc(cpu, idlestate);
		अगर (!पंचांगp)
			जारी;
		म_लिखो(_("Flags/Description: %s\n"), पंचांगp);
		मुक्त(पंचांगp);

		म_लिखो(_("Latency: %lu\n"),
		       cpuidle_state_latency(cpu, idlestate));
		म_लिखो(_("Usage: %lu\n"),
		       cpuidle_state_usage(cpu, idlestate));
		म_लिखो(_("Duration: %llu\n"),
		       cpuidle_state_समय(cpu, idlestate));
	पूर्ण
पूर्ण

अटल व्योम cpuidle_general_output(व्योम)
अणु
	अक्षर *पंचांगp;

	पंचांगp = cpuidle_get_driver();
	अगर (!पंचांगp) अणु
		म_लिखो(_("Could not determine cpuidle driver\n"));
		वापस;
	पूर्ण

	म_लिखो(_("CPUidle driver: %s\n"), पंचांगp);
	मुक्त(पंचांगp);

	पंचांगp = cpuidle_get_governor();
	अगर (!पंचांगp) अणु
		म_लिखो(_("Could not determine cpuidle governor\n"));
		वापस;
	पूर्ण

	म_लिखो(_("CPUidle governor: %s\n"), पंचांगp);
	मुक्त(पंचांगp);
पूर्ण

अटल व्योम proc_cpuidle_cpu_output(अचिन्हित पूर्णांक cpu)
अणु
	दीर्घ max_allowed_cstate = 2000000000;
	अचिन्हित पूर्णांक cstate, cstates;

	cstates = cpuidle_state_count(cpu);
	अगर (cstates == 0) अणु
		म_लिखो(_("CPU %u: No C-states info\n"), cpu);
		वापस;
	पूर्ण

	म_लिखो(_("active state:            C0\n"));
	म_लिखो(_("max_cstate:              C%u\n"), cstates-1);
	म_लिखो(_("maximum allowed latency: %lu usec\n"), max_allowed_cstate);
	म_लिखो(_("states:\t\n"));
	क्रम (cstate = 1; cstate < cstates; cstate++) अणु
		म_लिखो(_("    C%d:                  "
			 "type[C%d] "), cstate, cstate);
		म_लिखो(_("promotion[--] demotion[--] "));
		म_लिखो(_("latency[%03lu] "),
		       cpuidle_state_latency(cpu, cstate));
		म_लिखो(_("usage[%08lu] "),
		       cpuidle_state_usage(cpu, cstate));
		म_लिखो(_("duration[%020Lu] \n"),
		       cpuidle_state_समय(cpu, cstate));
	पूर्ण
पूर्ण

अटल काष्ठा option info_opts[] = अणु
	अणु"silent", no_argument, शून्य, 's'पूर्ण,
	अणु"proc", no_argument, शून्य, 'o'पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम cpuidle_निकास(पूर्णांक fail)
अणु
	निकास(निकास_त्रुटि);
पूर्ण

पूर्णांक cmd_idle_info(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind, opterr, optopt;
	पूर्णांक ret = 0, cont = 1, output_param = 0, verbose = 1;
	अचिन्हित पूर्णांक cpu = 0;

	करो अणु
		ret = getopt_दीर्घ(argc, argv, "os", info_opts, शून्य);
		अगर (ret == -1)
			अवरोध;
		चयन (ret) अणु
		हाल '?':
			output_param = '?';
			cont = 0;
			अवरोध;
		हाल 's':
			verbose = 0;
			अवरोध;
		हाल -1:
			cont = 0;
			अवरोध;
		हाल 'o':
			अगर (output_param) अणु
				output_param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			output_param = ret;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (cont);

	चयन (output_param) अणु
	हाल -1:
		म_लिखो(_("You can't specify more than one "
			 "output-specific argument\n"));
		cpuidle_निकास(निकास_त्रुटि);
	हाल '?':
		म_लिखो(_("invalid or unknown argument\n"));
		cpuidle_निकास(निकास_त्रुटि);
	पूर्ण

	/* Default is: show output of CPU 0 only */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setbit(cpus_chosen, 0);

	अगर (output_param == 0)
		cpuidle_general_output();

	क्रम (cpu = biपंचांगask_first(cpus_chosen);
	     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (!biपंचांगask_isbitset(cpus_chosen, cpu))
			जारी;

		म_लिखो(_("analyzing CPU %d:\n"), cpu);

		अगर (sysfs_is_cpu_online(cpu) != 1) अणु
			म_लिखो(_(" *is offline\n"));
			म_लिखो("\n");
			जारी;
		पूर्ण

		चयन (output_param) अणु

		हाल 'o':
			proc_cpuidle_cpu_output(cpu);
			अवरोध;
		हाल 0:
			म_लिखो("\n");
			cpuidle_cpu_output(cpu, verbose);
			अवरोध;
		पूर्ण
		म_लिखो("\n");
	पूर्ण
	वापस निकास_सफल;
पूर्ण
