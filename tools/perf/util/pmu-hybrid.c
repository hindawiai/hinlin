<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/list.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <क्षेत्र.स>
#समावेश <api/fs/fs.h>
#समावेश "fncache.h"
#समावेश "pmu-hybrid.h"

LIST_HEAD(perf_pmu__hybrid_pmus);

bool perf_pmu__hybrid_mounted(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	स्थिर अक्षर *sysfs;
	खाता *file;
	पूर्णांक n, cpu;

	अगर (म_भेदन(name, "cpu_", 4))
		वापस false;

	sysfs = sysfs__mountpoपूर्णांक();
	अगर (!sysfs)
		वापस false;

	snम_लिखो(path, PATH_MAX, CPUS_TEMPLATE_CPU, sysfs, name);
	अगर (!file_available(path))
		वापस false;

	file = ख_खोलो(path, "r");
	अगर (!file)
		वापस false;

	n = ख_पूछो(file, "%u", &cpu);
	ख_बंद(file);
	अगर (n <= 0)
		वापस false;

	वापस true;
पूर्ण

काष्ठा perf_pmu *perf_pmu__find_hybrid_pmu(स्थिर अक्षर *name)
अणु
	काष्ठा perf_pmu *pmu;

	अगर (!name)
		वापस शून्य;

	perf_pmu__क्रम_each_hybrid_pmu(pmu) अणु
		अगर (!म_भेद(name, pmu->name))
			वापस pmu;
	पूर्ण

	वापस शून्य;
पूर्ण

bool perf_pmu__is_hybrid(स्थिर अक्षर *name)
अणु
	वापस perf_pmu__find_hybrid_pmu(name) != शून्य;
पूर्ण

अक्षर *perf_pmu__hybrid_type_to_pmu(स्थिर अक्षर *type)
अणु
	अक्षर *pmu_name = शून्य;

	अगर (aप्र_लिखो(&pmu_name, "cpu_%s", type) < 0)
		वापस शून्य;

	अगर (perf_pmu__is_hybrid(pmu_name))
		वापस pmu_name;

	/*
	 * pmu may be not scanned, check the sysfs.
	 */
	अगर (perf_pmu__hybrid_mounted(pmu_name))
		वापस pmu_name;

	मुक्त(pmu_name);
	वापस शून्य;
पूर्ण
