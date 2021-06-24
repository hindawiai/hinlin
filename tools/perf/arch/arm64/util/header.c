<शैली गुरु>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <perf/cpumap.h>
#समावेश <util/cpumap.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <api/fs/fs.h>
#समावेश <त्रुटिसं.स>
#समावेश "debug.h"
#समावेश "header.h"

#घोषणा MIDR "/regs/identification/midr_el1"
#घोषणा MIDR_SIZE 19
#घोषणा MIDR_REVISION_MASK      0xf
#घोषणा MIDR_VARIANT_SHIFT      20
#घोषणा MIDR_VARIANT_MASK       (0xf << MIDR_VARIANT_SHIFT)

अटल पूर्णांक _get_cpuid(अक्षर *buf, माप_प्रकार sz, काष्ठा perf_cpu_map *cpus)
अणु
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();
	u64 midr = 0;
	पूर्णांक cpu;

	अगर (!sysfs || sz < MIDR_SIZE)
		वापस EINVAL;

	cpus = perf_cpu_map__get(cpus);

	क्रम (cpu = 0; cpu < perf_cpu_map__nr(cpus); cpu++) अणु
		अक्षर path[PATH_MAX];
		खाता *file;

		scnम_लिखो(path, PATH_MAX, "%s/devices/system/cpu/cpu%d"MIDR,
				sysfs, cpus->map[cpu]);

		file = ख_खोलो(path, "r");
		अगर (!file) अणु
			pr_debug("fopen failed for file %s\n", path);
			जारी;
		पूर्ण

		अगर (!ख_माला_लो(buf, MIDR_SIZE, file)) अणु
			ख_बंद(file);
			जारी;
		पूर्ण
		ख_बंद(file);

		/* Ignore/clear Variant[23:20] and
		 * Revision[3:0] of MIDR
		 */
		midr = म_से_अदीर्घ(buf, शून्य, 16);
		midr &= (~(MIDR_VARIANT_MASK | MIDR_REVISION_MASK));
		scnम_लिखो(buf, MIDR_SIZE, "0x%016lx", midr);
		/* got midr अवरोध loop */
		अवरोध;
	पूर्ण

	perf_cpu_map__put(cpus);

	अगर (!midr)
		वापस EINVAL;

	वापस 0;
पूर्ण

पूर्णांक get_cpuid(अक्षर *buf, माप_प्रकार sz)
अणु
	काष्ठा perf_cpu_map *cpus = perf_cpu_map__new(शून्य);
	पूर्णांक ret;

	अगर (!cpus)
		वापस EINVAL;

	ret = _get_cpuid(buf, sz, cpus);

	perf_cpu_map__put(cpus);

	वापस ret;
पूर्ण

अक्षर *get_cpuid_str(काष्ठा perf_pmu *pmu)
अणु
	अक्षर *buf = शून्य;
	पूर्णांक res;

	अगर (!pmu || !pmu->cpus)
		वापस शून्य;

	buf = दो_स्मृति(MIDR_SIZE);
	अगर (!buf)
		वापस शून्य;

	/* पढ़ो midr from list of cpus mapped to this pmu */
	res = _get_cpuid(buf, MIDR_SIZE, pmu->cpus);
	अगर (res) अणु
		pr_err("failed to get cpuid string for PMU %s\n", pmu->name);
		मुक्त(buf);
		buf = शून्य;
	पूर्ण

	वापस buf;
पूर्ण
