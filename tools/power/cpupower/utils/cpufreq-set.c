<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2004-2009  Dominik Broकरोwski <linux@करोminikbroकरोwski.de>
 */


#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>

#समावेश <getopt.h>

#समावेश "cpufreq.h"
#समावेश "cpuidle.h"
#समावेश "helpers/helpers.h"

#घोषणा NORM_FREQ_LEN 32

अटल काष्ठा option set_opts[] = अणु
	अणु"min",		required_argument,	शून्य, 'd'पूर्ण,
	अणु"max",		required_argument,	शून्य, 'u'पूर्ण,
	अणु"governor",	required_argument,	शून्य, 'g'पूर्ण,
	अणु"freq",	required_argument,	शून्य, 'f'पूर्ण,
	अणु"related",	no_argument,		शून्य, 'r'पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम prपूर्णांक_error(व्योम)
अणु
	म_लिखो(_("Error setting new values. Common errors:\n"
			"- Do you have proper administration rights? (super-user?)\n"
			"- Is the governor you requested available and modprobed?\n"
			"- Trying to set an invalid policy?\n"
			"- Trying to set a specific frequency, but userspace governor is not available,\n"
			"   for example because of hardware which cannot be set to a specific frequency\n"
			"   or because the userspace governor isn't loaded?\n"));
पूर्ण;

काष्ठा freq_units अणु
	अक्षर		*str_unit;
	पूर्णांक		घातer_of_ten;
पूर्ण;

स्थिर काष्ठा freq_units def_units[] = अणु
	अणु"hz", -3पूर्ण,
	अणु"khz", 0पूर्ण, /* शेष */
	अणु"mhz", 3पूर्ण,
	अणु"ghz", 6पूर्ण,
	अणु"thz", 9पूर्ण,
	अणुशून्य, 0पूर्ण
पूर्ण;

अटल व्योम prपूर्णांक_unknown_arg(व्योम)
अणु
	म_लिखो(_("invalid or unknown argument\n"));
पूर्ण

अटल अचिन्हित दीर्घ string_to_frequency(स्थिर अक्षर *str)
अणु
	अक्षर normalized[NORM_FREQ_LEN];
	स्थिर काष्ठा freq_units *unit;
	स्थिर अक्षर *scan;
	अक्षर *end;
	अचिन्हित दीर्घ freq;
	पूर्णांक घातer = 0, match_count = 0, i, cp, pad;

	जबतक (*str == '0')
		str++;

	क्रम (scan = str; है_अंक(*scan) || *scan == '.'; scan++) अणु
		अगर (*scan == '.' && match_count == 0)
			match_count = 1;
		अन्यथा अगर (*scan == '.' && match_count == 1)
			वापस 0;
	पूर्ण

	अगर (*scan) अणु
		match_count = 0;
		क्रम (unit = def_units; unit->str_unit; unit++) अणु
			क्रम (i = 0;
			     scan[i] && छोटे(scan[i]) == unit->str_unit[i];
			     ++i)
				जारी;
			अगर (scan[i])
				जारी;
			match_count++;
			घातer = unit->घातer_of_ten;
		पूर्ण
		अगर (match_count != 1)
			वापस 0;
	पूर्ण

	/* count the number of digits to be copied */
	क्रम (cp = 0; है_अंक(str[cp]); cp++)
		जारी;

	अगर (str[cp] == '.') अणु
		जबतक (घातer > -1 && है_अंक(str[cp+1])) अणु
			cp++;
			घातer--;
		पूर्ण
	पूर्ण
	अगर (घातer >= -1) अणु		/* not enough => pad */
		pad = घातer + 1;
	पूर्ण अन्यथा अणु			/* too much => strip */
		pad = 0;
		cp += घातer + 1;
	पूर्ण
	/* check bounds */
	अगर (cp <= 0 || cp + pad > NORM_FREQ_LEN - 1)
		वापस 0;

	/* copy digits */
	क्रम (i = 0; i < cp; i++, str++) अणु
		अगर (*str == '.')
			str++;
		normalized[i] = *str;
	पूर्ण
	/* and pad */
	क्रम (; i < cp + pad; i++)
		normalized[i] = '0';

	/* round up, करोwn ? */
	match_count = (normalized[i-1] >= '5');
	/* and drop the decimal part */
	normalized[i-1] = 0; /* cp > 0 && pad >= 0 ==> i > 0 */

	/* final conversion (and applying rounding) */
	त्रुटि_सं = 0;
	freq = म_से_अदीर्घ(normalized, &end, 10);
	अगर (त्रुटि_सं)
		वापस 0;
	अन्यथा अणु
		अगर (match_count && freq != अच_दीर्घ_उच्च)
			freq++;
		वापस freq;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_new_policy(अचिन्हित पूर्णांक cpu, काष्ठा cpufreq_policy *new_pol)
अणु
	काष्ठा cpufreq_policy *cur_pol = cpufreq_get_policy(cpu);
	पूर्णांक ret;

	अगर (!cur_pol) अणु
		म_लिखो(_("wrong, unknown or unhandled CPU?\n"));
		वापस -EINVAL;
	पूर्ण

	अगर (!new_pol->min)
		new_pol->min = cur_pol->min;

	अगर (!new_pol->max)
		new_pol->max = cur_pol->max;

	अगर (!new_pol->governor)
		new_pol->governor = cur_pol->governor;

	ret = cpufreq_set_policy(cpu, new_pol);

	cpufreq_put_policy(cur_pol);

	वापस ret;
पूर्ण


अटल पूर्णांक करो_one_cpu(अचिन्हित पूर्णांक cpu, काष्ठा cpufreq_policy *new_pol,
		अचिन्हित दीर्घ freq, अचिन्हित पूर्णांक pc)
अणु
	चयन (pc) अणु
	हाल 0:
		वापस cpufreq_set_frequency(cpu, freq);

	हाल 1:
		/* अगर only one value of a policy is to be changed, we can
		 * use a "fast path".
		 */
		अगर (new_pol->min)
			वापस cpufreq_modअगरy_policy_min(cpu, new_pol->min);
		अन्यथा अगर (new_pol->max)
			वापस cpufreq_modअगरy_policy_max(cpu, new_pol->max);
		अन्यथा अगर (new_pol->governor)
			वापस cpufreq_modअगरy_policy_governor(cpu,
							new_pol->governor);

	शेष:
		/* slow path */
		वापस करो_new_policy(cpu, new_pol);
	पूर्ण
पूर्ण

पूर्णांक cmd_freq_set(पूर्णांक argc, अक्षर **argv)
अणु
	बाह्य अक्षर *optarg;
	बाह्य पूर्णांक optind, opterr, optopt;
	पूर्णांक ret = 0, cont = 1;
	पूर्णांक द्विगुन_parm = 0, related = 0, policychange = 0;
	अचिन्हित दीर्घ freq = 0;
	अक्षर gov[20];
	अचिन्हित पूर्णांक cpu;

	काष्ठा cpufreq_policy new_pol = अणु
		.min = 0,
		.max = 0,
		.governor = शून्य,
	पूर्ण;

	/* parameter parsing */
	करो अणु
		ret = getopt_दीर्घ(argc, argv, "d:u:g:f:r", set_opts, शून्य);
		चयन (ret) अणु
		हाल '?':
			prपूर्णांक_unknown_arg();
			वापस -EINVAL;
		हाल -1:
			cont = 0;
			अवरोध;
		हाल 'r':
			अगर (related)
				द्विगुन_parm++;
			related++;
			अवरोध;
		हाल 'd':
			अगर (new_pol.min)
				द्विगुन_parm++;
			policychange++;
			new_pol.min = string_to_frequency(optarg);
			अगर (new_pol.min == 0) अणु
				prपूर्णांक_unknown_arg();
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 'u':
			अगर (new_pol.max)
				द्विगुन_parm++;
			policychange++;
			new_pol.max = string_to_frequency(optarg);
			अगर (new_pol.max == 0) अणु
				prपूर्णांक_unknown_arg();
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 'f':
			अगर (freq)
				द्विगुन_parm++;
			freq = string_to_frequency(optarg);
			अगर (freq == 0) अणु
				prपूर्णांक_unknown_arg();
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल 'g':
			अगर (new_pol.governor)
				द्विगुन_parm++;
			policychange++;
			अगर ((म_माप(optarg) < 3) || (म_माप(optarg) > 18)) अणु
				prपूर्णांक_unknown_arg();
				वापस -EINVAL;
			पूर्ण
			अगर ((माला_पूछो(optarg, "%19s", gov)) != 1) अणु
				prपूर्णांक_unknown_arg();
				वापस -EINVAL;
			पूर्ण
			new_pol.governor = gov;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (cont);

	/* parameter checking */
	अगर (द्विगुन_parm) अणु
		म_लिखो("the same parameter was passed more than once\n");
		वापस -EINVAL;
	पूर्ण

	अगर (freq && policychange) अणु
		म_लिखो(_("the -f/--freq parameter cannot be combined with -d/--min, -u/--max or\n"
				"-g/--governor parameters\n"));
		वापस -EINVAL;
	पूर्ण

	अगर (!freq && !policychange) अणु
		म_लिखो(_("At least one parameter out of -f/--freq, -d/--min, -u/--max, and\n"
				"-g/--governor must be passed\n"));
		वापस -EINVAL;
	पूर्ण

	/* Default is: set all CPUs */
	अगर (biपंचांगask_isallclear(cpus_chosen))
		biपंचांगask_setall(cpus_chosen);

	/* Also set frequency settings क्रम related CPUs अगर -r is passed */
	अगर (related) अणु
		क्रम (cpu = biपंचांगask_first(cpus_chosen);
		     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु
			काष्ठा cpufreq_affected_cpus *cpus;

			अगर (!biपंचांगask_isbitset(cpus_chosen, cpu) ||
			    cpuघातer_is_cpu_online(cpu) != 1)
				जारी;

			cpus = cpufreq_get_related_cpus(cpu);
			अगर (!cpus)
				अवरोध;
			जबतक (cpus->next) अणु
				biपंचांगask_setbit(cpus_chosen, cpus->cpu);
				cpus = cpus->next;
			पूर्ण
			/* Set the last cpu in related cpus list */
			biपंचांगask_setbit(cpus_chosen, cpus->cpu);
			cpufreq_put_related_cpus(cpus);
		पूर्ण
	पूर्ण

	get_cpustate();

	/* loop over CPUs */
	क्रम (cpu = biपंचांगask_first(cpus_chosen);
	     cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (!biपंचांगask_isbitset(cpus_chosen, cpu) ||
		    cpuघातer_is_cpu_online(cpu) != 1)
			जारी;

		म_लिखो(_("Setting cpu: %d\n"), cpu);
		ret = करो_one_cpu(cpu, &new_pol, freq, policychange);
		अगर (ret) अणु
			prपूर्णांक_error();
			वापस ret;
		पूर्ण
	पूर्ण

	prपूर्णांक_offline_cpus();

	वापस 0;
पूर्ण
