<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 */


#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <सीमा.स>

#समावेश <getopt.h>

#समावेश "cpufreq.h"
#समावेश "helpers/sysfs.h"
#समावेश "helpers/helpers.h"
#समावेश "helpers/bitmask.h"

#घोषणा LINE_LEN 10

अटल अचिन्हित पूर्णांक count_cpus(व्योम)
अणु
	खाता *fp;
	अक्षर value[LINE_LEN];
	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cpunr = 0;

	fp = ख_खोलो("/proc/stat", "r");
	अगर (!fp) अणु
		म_लिखो(_("Couldn't count the number of CPUs (%s: %s), assuming 1\n"), "/proc/stat", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	जबतक (!ख_पूर्ण(fp)) अणु
		अगर (!ख_माला_लो(value, LINE_LEN, fp))
			जारी;
		value[LINE_LEN - 1] = '\0';
		अगर (म_माप(value) < (LINE_LEN - 2))
			जारी;
		अगर (म_माला(value, "cpu "))
			जारी;
		अगर (माला_पूछो(value, "cpu%d ", &cpunr) != 1)
			जारी;
		अगर (cpunr > ret)
			ret = cpunr;
	पूर्ण
	ख_बंद(fp);

	/* cpu count starts from 0, on error वापस 1 (UP) */
	वापस ret + 1;
पूर्ण


अटल व्योम proc_cpufreq_output(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, nr_cpus;
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक min_pctg = 0;
	अचिन्हित पूर्णांक max_pctg = 0;
	अचिन्हित दीर्घ min, max;

	म_लिखो(_("          minimum CPU frequency  -  maximum CPU frequency  -  governor\n"));

	nr_cpus = count_cpus();
	क्रम (cpu = 0; cpu < nr_cpus; cpu++) अणु
		policy = cpufreq_get_policy(cpu);
		अगर (!policy)
			जारी;

		अगर (cpufreq_get_hardware_limits(cpu, &min, &max)) अणु
			max = 0;
		पूर्ण अन्यथा अणु
			min_pctg = (policy->min * 100) / max;
			max_pctg = (policy->max * 100) / max;
		पूर्ण
		म_लिखो("CPU%3d    %9lu kHz (%3d %%)  -  %9lu kHz (%3d %%)  -  %s\n",
			cpu , policy->min, max ? min_pctg : 0, policy->max,
			max ? max_pctg : 0, policy->governor);

		cpufreq_put_policy(policy);
	पूर्ण
पूर्ण

अटल पूर्णांक no_rounding;
अटल व्योम prपूर्णांक_speed(अचिन्हित दीर्घ speed)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (no_rounding) अणु
		अगर (speed > 1000000)
			म_लिखो("%u.%06u GHz", ((अचिन्हित पूर्णांक) speed/1000000),
				((अचिन्हित पूर्णांक) speed%1000000));
		अन्यथा अगर (speed > 1000)
			म_लिखो("%u.%03u MHz", ((अचिन्हित पूर्णांक) speed/1000),
				(अचिन्हित पूर्णांक) (speed%1000));
		अन्यथा
			म_लिखो("%lu kHz", speed);
	पूर्ण अन्यथा अणु
		अगर (speed > 1000000) अणु
			पंचांगp = speed%10000;
			अगर (पंचांगp >= 5000)
				speed += 10000;
			म_लिखो("%u.%02u GHz", ((अचिन्हित पूर्णांक) speed/1000000),
				((अचिन्हित पूर्णांक) (speed%1000000)/10000));
		पूर्ण अन्यथा अगर (speed > 100000) अणु
			पंचांगp = speed%1000;
			अगर (पंचांगp >= 500)
				speed += 1000;
			म_लिखो("%u MHz", ((अचिन्हित पूर्णांक) speed/1000));
		पूर्ण अन्यथा अगर (speed > 1000) अणु
			पंचांगp = speed%100;
			अगर (पंचांगp >= 50)
				speed += 100;
			म_लिखो("%u.%01u MHz", ((अचिन्हित पूर्णांक) speed/1000),
				((अचिन्हित पूर्णांक) (speed%1000)/100));
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल व्योम prपूर्णांक_duration(अचिन्हित दीर्घ duration)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (no_rounding) अणु
		अगर (duration > 1000000)
			म_लिखो("%u.%06u ms", ((अचिन्हित पूर्णांक) duration/1000000),
				((अचिन्हित पूर्णांक) duration%1000000));
		अन्यथा अगर (duration > 100000)
			म_लिखो("%u us", ((अचिन्हित पूर्णांक) duration/1000));
		अन्यथा अगर (duration > 1000)
			म_लिखो("%u.%03u us", ((अचिन्हित पूर्णांक) duration/1000),
				((अचिन्हित पूर्णांक) duration%1000));
		अन्यथा
			म_लिखो("%lu ns", duration);
	पूर्ण अन्यथा अणु
		अगर (duration > 1000000) अणु
			पंचांगp = duration%10000;
			अगर (पंचांगp >= 5000)
				duration += 10000;
			म_लिखो("%u.%02u ms", ((अचिन्हित पूर्णांक) duration/1000000),
				((अचिन्हित पूर्णांक) (duration%1000000)/10000));
		पूर्ण अन्यथा अगर (duration > 100000) अणु
			पंचांगp = duration%1000;
			अगर (पंचांगp >= 500)
				duration += 1000;
			म_लिखो("%u us", ((अचिन्हित पूर्णांक) duration / 1000));
		पूर्ण अन्यथा अगर (duration > 1000) अणु
			पंचांगp = duration%100;
			अगर (पंचांगp >= 50)
				duration += 100;
			म_लिखो("%u.%01u us", ((अचिन्हित पूर्णांक) duration/1000),
				((अचिन्हित पूर्णांक) (duration%1000)/100));
		पूर्ण अन्यथा
			म_लिखो("%lu ns", duration);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक get_boost_mode_x86(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक support, active, b_states = 0, ret, pstate_no, i;
	/* ToDo: Make this more global */
	अचिन्हित दीर्घ pstates[MAX_HW_PSTATES] = अणु0,पूर्ण;

	ret = cpufreq_has_boost_support(cpu, &support, &active, &b_states);
	अगर (ret) अणु
		म_लिखो(_("Error while evaluating Boost Capabilities"
				" on CPU %d -- are you root?\n"), cpu);
		वापस ret;
	पूर्ण
	/* P state changes via MSR are identअगरied via cpuid 80000007
	   on Intel and AMD, but we assume boost capable machines can करो that
	   अगर (cpuid_eax(0x80000000) >= 0x80000007
	   && (cpuid_edx(0x80000007) & (1 << 7)))
	*/

	म_लिखो(_("  boost state support:\n"));

	म_लिखो(_("    Supported: %s\n"), support ? _("yes") : _("no"));
	म_लिखो(_("    Active: %s\n"), active ? _("yes") : _("no"));

	अगर ((cpuघातer_cpu_info.venकरोr == X86_VENDOR_AMD &&
	     cpuघातer_cpu_info.family >= 0x10) ||
	     cpuघातer_cpu_info.venकरोr == X86_VENDOR_HYGON) अणु
		ret = decode_pstates(cpu, b_states, pstates, &pstate_no);
		अगर (ret)
			वापस ret;

		म_लिखो(_("    Boost States: %d\n"), b_states);
		म_लिखो(_("    Total States: %d\n"), pstate_no);
		क्रम (i = 0; i < pstate_no; i++) अणु
			अगर (!pstates[i])
				जारी;
			अगर (i < b_states)
				म_लिखो(_("    Pstate-Pb%d: %luMHz (boost state)"
					 "\n"), i, pstates[i]);
			अन्यथा
				म_लिखो(_("    Pstate-P%d:  %luMHz\n"),
				       i - b_states, pstates[i]);
		पूर्ण
	पूर्ण अन्यथा अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_HAS_TURBO_RATIO) अणु
		द्विगुन bclk;
		अचिन्हित दीर्घ दीर्घ पूर्णांकel_turbo_ratio = 0;
		अचिन्हित पूर्णांक ratio;

		/* Any way to स्वतःdetect this ? */
		अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_IS_SNB)
			bclk = 100.00;
		अन्यथा
			bclk = 133.33;
		पूर्णांकel_turbo_ratio = msr_पूर्णांकel_get_turbo_ratio(cpu);
		dprपूर्णांक ("    Ratio: 0x%llx - bclk: %f\n",
			पूर्णांकel_turbo_ratio, bclk);

		ratio = (पूर्णांकel_turbo_ratio >> 24) & 0xFF;
		अगर (ratio)
			म_लिखो(_("    %.0f MHz max turbo 4 active cores\n"),
			       ratio * bclk);

		ratio = (पूर्णांकel_turbo_ratio >> 16) & 0xFF;
		अगर (ratio)
			म_लिखो(_("    %.0f MHz max turbo 3 active cores\n"),
			       ratio * bclk);

		ratio = (पूर्णांकel_turbo_ratio >> 8) & 0xFF;
		अगर (ratio)
			म_लिखो(_("    %.0f MHz max turbo 2 active cores\n"),
			       ratio * bclk);

		ratio = (पूर्णांकel_turbo_ratio >> 0) & 0xFF;
		अगर (ratio)
			म_लिखो(_("    %.0f MHz max turbo 1 active cores\n"),
			       ratio * bclk);
	पूर्ण
	वापस 0;
पूर्ण

/* --boost / -b */

अटल पूर्णांक get_boost_mode(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_frequencies *freqs;

	अगर (cpuघातer_cpu_info.venकरोr == X86_VENDOR_AMD ||
	    cpuघातer_cpu_info.venकरोr == X86_VENDOR_HYGON ||
	    cpuघातer_cpu_info.venकरोr == X86_VENDOR_INTEL)
		वापस get_boost_mode_x86(cpu);

	freqs = cpufreq_get_boost_frequencies(cpu);
	अगर (freqs) अणु
		म_लिखो(_("  boost frequency steps: "));
		जबतक (freqs->next) अणु
			prपूर्णांक_speed(freqs->frequency);
			म_लिखो(", ");
			freqs = freqs->next;
		पूर्ण
		prपूर्णांक_speed(freqs->frequency);
		म_लिखो("\n");
		cpufreq_put_available_frequencies(freqs);
	पूर्ण

	वापस 0;
पूर्ण

/* --freq / -f */

अटल पूर्णांक get_freq_kernel(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक human)
अणु
	अचिन्हित दीर्घ freq = cpufreq_get_freq_kernel(cpu);
	म_लिखो(_("  current CPU frequency: "));
	अगर (!freq) अणु
		म_लिखो(_(" Unable to call to kernel\n"));
		वापस -EINVAL;
	पूर्ण
	अगर (human) अणु
		prपूर्णांक_speed(freq);
	पूर्ण अन्यथा
		म_लिखो("%lu", freq);
	म_लिखो(_(" (asserted by call to kernel)\n"));
	वापस 0;
पूर्ण


/* --hwfreq / -w */

अटल पूर्णांक get_freq_hardware(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक human)
अणु
	अचिन्हित दीर्घ freq = cpufreq_get_freq_hardware(cpu);
	म_लिखो(_("  current CPU frequency: "));
	अगर (!freq) अणु
		म_लिखो("Unable to call hardware\n");
		वापस -EINVAL;
	पूर्ण
	अगर (human) अणु
		prपूर्णांक_speed(freq);
	पूर्ण अन्यथा
		म_लिखो("%lu", freq);
	म_लिखो(_(" (asserted by call to hardware)\n"));
	वापस 0;
पूर्ण

/* --hwlimits / -l */

अटल पूर्णांक get_hardware_limits(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक human)
अणु
	अचिन्हित दीर्घ min, max;

	अगर (cpufreq_get_hardware_limits(cpu, &min, &max)) अणु
		म_लिखो(_("Not Available\n"));
		वापस -EINVAL;
	पूर्ण

	अगर (human) अणु
		म_लिखो(_("  hardware limits: "));
		prपूर्णांक_speed(min);
		म_लिखो(" - ");
		prपूर्णांक_speed(max);
		म_लिखो("\n");
	पूर्ण अन्यथा अणु
		म_लिखो("%lu %lu\n", min, max);
	पूर्ण
	वापस 0;
पूर्ण

/* --driver / -d */

अटल पूर्णांक get_driver(अचिन्हित पूर्णांक cpu)
अणु
	अक्षर *driver = cpufreq_get_driver(cpu);
	अगर (!driver) अणु
		म_लिखो(_("  no or unknown cpufreq driver is active on this CPU\n"));
		वापस -EINVAL;
	पूर्ण
	म_लिखो("  driver: %s\n", driver);
	cpufreq_put_driver(driver);
	वापस 0;
पूर्ण

/* --policy / -p */

अटल पूर्णांक get_policy(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_get_policy(cpu);
	अगर (!policy) अणु
		म_लिखो(_("  Unable to determine current policy\n"));
		वापस -EINVAL;
	पूर्ण
	म_लिखो(_("  current policy: frequency should be within "));
	prपूर्णांक_speed(policy->min);
	म_लिखो(_(" and "));
	prपूर्णांक_speed(policy->max);

	म_लिखो(".\n                  ");
	म_लिखो(_("The governor \"%s\" may decide which speed to use\n"
	       "                  within this range.\n"),
	       policy->governor);
	cpufreq_put_policy(policy);
	वापस 0;
पूर्ण

/* --governors / -g */

अटल पूर्णांक get_available_governors(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_governors *governors =
		cpufreq_get_available_governors(cpu);

	म_लिखो(_("  available cpufreq governors: "));
	अगर (!governors) अणु
		म_लिखो(_("Not Available\n"));
		वापस -EINVAL;
	पूर्ण

	जबतक (governors->next) अणु
		म_लिखो("%s ", governors->governor);
		governors = governors->next;
	पूर्ण
	म_लिखो("%s\n", governors->governor);
	cpufreq_put_available_governors(governors);
	वापस 0;
पूर्ण


/* --affected-cpus  / -a */

अटल पूर्णांक get_affected_cpus(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_affected_cpus *cpus = cpufreq_get_affected_cpus(cpu);

	म_लिखो(_("  CPUs which need to have their frequency coordinated by software: "));
	अगर (!cpus) अणु
		म_लिखो(_("Not Available\n"));
		वापस -EINVAL;
	पूर्ण

	जबतक (cpus->next) अणु
		म_लिखो("%d ", cpus->cpu);
		cpus = cpus->next;
	पूर्ण
	म_लिखो("%d\n", cpus->cpu);
	cpufreq_put_affected_cpus(cpus);
	वापस 0;
पूर्ण

/* --related-cpus  / -r */

अटल पूर्णांक get_related_cpus(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_affected_cpus *cpus = cpufreq_get_related_cpus(cpu);

	म_लिखो(_("  CPUs which run at the same hardware frequency: "));
	अगर (!cpus) अणु
		म_लिखो(_("Not Available\n"));
		वापस -EINVAL;
	पूर्ण

	जबतक (cpus->next) अणु
		म_लिखो("%d ", cpus->cpu);
		cpus = cpus->next;
	पूर्ण
	म_लिखो("%d\n", cpus->cpu);
	cpufreq_put_related_cpus(cpus);
	वापस 0;
पूर्ण

/* --stats / -s */

अटल पूर्णांक get_freq_stats(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक human)
अणु
	अचिन्हित दीर्घ total_trans = cpufreq_get_transitions(cpu);
	अचिन्हित दीर्घ दीर्घ total_समय;
	काष्ठा cpufreq_stats *stats = cpufreq_get_stats(cpu, &total_समय);
	जबतक (stats) अणु
		अगर (human) अणु
			prपूर्णांक_speed(stats->frequency);
			म_लिखो(":%.2f%%",
				(100.0 * stats->समय_in_state) / total_समय);
		पूर्ण अन्यथा
			म_लिखो("%lu:%llu",
				stats->frequency, stats->समय_in_state);
		stats = stats->next;
		अगर (stats)
			म_लिखो(", ");
	पूर्ण
	cpufreq_put_stats(stats);
	अगर (total_trans)
		म_लिखो("  (%lu)\n", total_trans);
	वापस 0;
पूर्ण

/* --latency / -y */

अटल पूर्णांक get_latency(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक human)
अणु
	अचिन्हित दीर्घ latency = cpufreq_get_transition_latency(cpu);

	म_लिखो(_("  maximum transition latency: "));
	अगर (!latency || latency == अच_पूर्णांक_उच्च) अणु
		म_लिखो(_(" Cannot determine or is not supported.\n"));
		वापस -EINVAL;
	पूर्ण

	अगर (human) अणु
		prपूर्णांक_duration(latency);
		म_लिखो("\n");
	पूर्ण अन्यथा
		म_लिखो("%lu\n", latency);
	वापस 0;
पूर्ण

अटल व्योम debug_output_one(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_available_frequencies *freqs;

	get_driver(cpu);
	get_related_cpus(cpu);
	get_affected_cpus(cpu);
	get_latency(cpu, 1);
	get_hardware_limits(cpu, 1);

	freqs = cpufreq_get_available_frequencies(cpu);
	अगर (freqs) अणु
		म_लिखो(_("  available frequency steps:  "));
		जबतक (freqs->next) अणु
			prपूर्णांक_speed(freqs->frequency);
			म_लिखो(", ");
			freqs = freqs->next;
		पूर्ण
		prपूर्णांक_speed(freqs->frequency);
		म_लिखो("\n");
		cpufreq_put_available_frequencies(freqs);
	पूर्ण

	get_available_governors(cpu);
	get_policy(cpu);
	अगर (get_freq_hardware(cpu, 1) < 0)
		get_freq_kernel(cpu, 1);
	get_boost_mode(cpu);
पूर्ण

अटल काष्ठा option info_opts[] = अणु
	अणु"debug",	 no_argument,		 शून्य,	 'e'पूर्ण,
	अणु"boost",	 no_argument,		 शून्य,	 'b'पूर्ण,
	अणु"freq",	 no_argument,		 शून्य,	 'f'पूर्ण,
	अणु"hwfreq",	 no_argument,		 शून्य,	 'w'पूर्ण,
	अणु"hwlimits",	 no_argument,		 शून्य,	 'l'पूर्ण,
	अणु"driver",	 no_argument,		 शून्य,	 'd'पूर्ण,
	अणु"policy",	 no_argument,		 शून्य,	 'p'पूर्ण,
	अणु"governors",	 no_argument,		 शून्य,	 'g'पूर्ण,
	अणु"related-cpus",  no_argument,	 शून्य,	 'r'पूर्ण,
	अणु"affected-cpus", no_argument,	 शून्य,	 'a'पूर्ण,
	अणु"stats",	 no_argument,		 शून्य,	 's'पूर्ण,
	अणु"latency",	 no_argument,		 शून्य,	 'y'पूर्ण,
	अणु"proc",	 no_argument,		 शून्य,	 'o'पूर्ण,
	अणु"human",	 no_argument,		 शून्य,	 'm'पूर्ण,
	अणु"no-rounding", no_argument,	 शून्य,	 'n'पूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक cmd_freq_info(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind, opterr, optopt;
	पूर्णांक ret = 0, cont = 1;
	अचिन्हित पूर्णांक cpu = 0;
	अचिन्हित पूर्णांक human = 0;
	पूर्णांक output_param = 0;

	करो अणु
		ret = getopt_दीर्घ(argc, argv, "oefwldpgrasmybn", info_opts,
				  शून्य);
		चयन (ret) अणु
		हाल '?':
			output_param = '?';
			cont = 0;
			अवरोध;
		हाल -1:
			cont = 0;
			अवरोध;
		हाल 'b':
		हाल 'o':
		हाल 'a':
		हाल 'r':
		हाल 'g':
		हाल 'p':
		हाल 'd':
		हाल 'l':
		हाल 'w':
		हाल 'f':
		हाल 'e':
		हाल 's':
		हाल 'y':
			अगर (output_param) अणु
				output_param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			output_param = ret;
			अवरोध;
		हाल 'm':
			अगर (human) अणु
				output_param = -1;
				cont = 0;
				अवरोध;
			पूर्ण
			human = 1;
			अवरोध;
		हाल 'n':
			no_rounding = 1;
			अवरोध;
		शेष:
			ख_लिखो(मानक_त्रुटि, "invalid or unknown argument\n");
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण जबतक (cont);

	चयन (output_param) अणु
	हाल 'o':
		अगर (!biपंचांगask_isallclear(cpus_chosen)) अणु
			म_लिखो(_("The argument passed to this tool can't be "
				 "combined with passing a --cpu argument\n"));
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 0:
		output_param = 'e';
	पूर्ण

	ret = 0;

	/* Default is: show output of CPU 0 only */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setbit(cpus_chosen, 0);

	चयन (output_param) अणु
	हाल -1:
		म_लिखो(_("You can't specify more than one --cpu parameter and/or\n"
		       "more than one output-specific argument\n"));
		वापस -EINVAL;
	हाल '?':
		म_लिखो(_("invalid or unknown argument\n"));
		वापस -EINVAL;
	हाल 'o':
		proc_cpufreq_output();
		वापस निकास_सफल;
	पूर्ण

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
		हाल 'b':
			get_boost_mode(cpu);
			अवरोध;
		हाल 'e':
			debug_output_one(cpu);
			अवरोध;
		हाल 'a':
			ret = get_affected_cpus(cpu);
			अवरोध;
		हाल 'r':
			ret = get_related_cpus(cpu);
			अवरोध;
		हाल 'g':
			ret = get_available_governors(cpu);
			अवरोध;
		हाल 'p':
			ret = get_policy(cpu);
			अवरोध;
		हाल 'd':
			ret = get_driver(cpu);
			अवरोध;
		हाल 'l':
			ret = get_hardware_limits(cpu, human);
			अवरोध;
		हाल 'w':
			ret = get_freq_hardware(cpu, human);
			अवरोध;
		हाल 'f':
			ret = get_freq_kernel(cpu, human);
			अवरोध;
		हाल 's':
			ret = get_freq_stats(cpu, human);
			अवरोध;
		हाल 'y':
			ret = get_latency(cpu, human);
			अवरोध;
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण
