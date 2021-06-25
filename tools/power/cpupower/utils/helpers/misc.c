<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>

#समावेश "helpers/helpers.h"
#समावेश "helpers/sysfs.h"

#अगर defined(__i386__) || defined(__x86_64__)

#समावेश "cpupower_intern.h"

#घोषणा MSR_AMD_HWCR	0xc0010015

पूर्णांक cpufreq_has_boost_support(अचिन्हित पूर्णांक cpu, पूर्णांक *support, पूर्णांक *active,
			पूर्णांक *states)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ val;

	*support = *active = *states = 0;

	अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_CPB) अणु
		*support = 1;

		/* AMD Family 0x17 करोes not utilize PCI D18F4 like prior
		 * families and has no fixed discrete boost states but
		 * has Hardware determined variable increments instead.
		 */

		अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_AMD_CPB_MSR) अणु
			अगर (!पढ़ो_msr(cpu, MSR_AMD_HWCR, &val)) अणु
				अगर (!(val & CPUPOWER_AMD_CPBDIS))
					*active = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = amd_pci_get_num_boost_states(active, states);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (cpuघातer_cpu_info.caps & CPUPOWER_CAP_INTEL_IDA)
		*support = *active = 1;
	वापस 0;
पूर्ण

पूर्णांक cpuघातer_पूर्णांकel_get_perf_bias(अचिन्हित पूर्णांक cpu)
अणु
	अक्षर linebuf[MAX_LINE_LEN];
	अक्षर path[SYSFS_PATH_MAX];
	अचिन्हित दीर्घ val;
	अक्षर *endp;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_PERF_BIAS))
		वापस -1;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/power/energy_perf_bias", cpu);

	अगर (cpuघातer_पढ़ो_sysfs(path, linebuf, MAX_LINE_LEN) == 0)
		वापस -1;

	val = म_से_दीर्घ(linebuf, &endp, 0);
	अगर (endp == linebuf || त्रुटि_सं == दुस्फल)
		वापस -1;

	वापस val;
पूर्ण

पूर्णांक cpuघातer_पूर्णांकel_set_perf_bias(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक val)
अणु
	अक्षर path[SYSFS_PATH_MAX];
	अक्षर linebuf[3] = अणुपूर्ण;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_PERF_BIAS))
		वापस -1;

	snम_लिखो(path, माप(path), PATH_TO_CPU "cpu%u/power/energy_perf_bias", cpu);
	snम_लिखो(linebuf, माप(linebuf), "%d", val);

	अगर (cpuघातer_ग_लिखो_sysfs(path, linebuf, 3) <= 0)
		वापस -1;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* #अगर defined(__i386__) || defined(__x86_64__) */

/* get_cpustate
 *
 * Gather the inक्रमmation of all online CPUs पूर्णांकo biपंचांगask काष्ठा
 */
व्योम get_cpustate(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = 0;

	biपंचांगask_clearall(online_cpus);
	biपंचांगask_clearall(offline_cpus);

	क्रम (cpu = biपंचांगask_first(cpus_chosen);
		cpu <= biपंचांगask_last(cpus_chosen); cpu++) अणु

		अगर (cpuघातer_is_cpu_online(cpu) == 1)
			biपंचांगask_setbit(online_cpus, cpu);
		अन्यथा
			biपंचांगask_setbit(offline_cpus, cpu);

		जारी;
	पूर्ण
पूर्ण

/* prपूर्णांक_online_cpus
 *
 * Prपूर्णांक the CPU numbers of all CPUs that are online currently
 */
व्योम prपूर्णांक_online_cpus(व्योम)
अणु
	पूर्णांक str_len = 0;
	अक्षर *online_cpus_str = शून्य;

	str_len = online_cpus->size * 5;
	online_cpus_str = (व्योम *)दो_स्मृति(माप(अक्षर) * str_len);

	अगर (!biपंचांगask_isallclear(online_cpus)) अणु
		biपंचांगask_displaylist(online_cpus_str, str_len, online_cpus);
		म_लिखो(_("Following CPUs are online:\n%s\n"), online_cpus_str);
	पूर्ण
पूर्ण

/* prपूर्णांक_offline_cpus
 *
 * Prपूर्णांक the CPU numbers of all CPUs that are offline currently
 */
व्योम prपूर्णांक_offline_cpus(व्योम)
अणु
	पूर्णांक str_len = 0;
	अक्षर *offline_cpus_str = शून्य;

	str_len = offline_cpus->size * 5;
	offline_cpus_str = (व्योम *)दो_स्मृति(माप(अक्षर) * str_len);

	अगर (!biपंचांगask_isallclear(offline_cpus)) अणु
		biपंचांगask_displaylist(offline_cpus_str, str_len, offline_cpus);
		म_लिखो(_("Following CPUs are offline:\n%s\n"), offline_cpus_str);
		म_लिखो(_("cpupower set operation was not performed on them\n"));
	पूर्ण
पूर्ण
