<शैली गुरु>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/bitops.h>
#समावेश "api/fs/fs.h"
#समावेश "smt.h"

पूर्णांक smt_on(व्योम)
अणु
	अटल bool cached;
	अटल पूर्णांक cached_result;
	पूर्णांक cpu;
	पूर्णांक ncpu;

	अगर (cached)
		वापस cached_result;

	अगर (sysfs__पढ़ो_पूर्णांक("devices/system/cpu/smt/active", &cached_result) > 0)
		जाओ करोne;

	ncpu = sysconf(_SC_NPROCESSORS_CONF);
	क्रम (cpu = 0; cpu < ncpu; cpu++) अणु
		अचिन्हित दीर्घ दीर्घ siblings;
		अक्षर *str;
		माप_प्रकार म_माप;
		अक्षर fn[256];

		snम_लिखो(fn, माप fn,
			"devices/system/cpu/cpu%d/topology/core_cpus", cpu);
		अगर (sysfs__पढ़ो_str(fn, &str, &म_माप) < 0) अणु
			snम_लिखो(fn, माप fn,
				"devices/system/cpu/cpu%d/topology/thread_siblings",
				cpu);
			अगर (sysfs__पढ़ो_str(fn, &str, &म_माप) < 0)
				जारी;
		पूर्ण
		/* Entry is hex, but करोes not have 0x, so need custom parser */
		siblings = म_से_अदीर्घl(str, शून्य, 16);
		मुक्त(str);
		अगर (hweight64(siblings) > 1) अणु
			cached_result = 1;
			cached = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cached) अणु
		cached_result = 0;
करोne:
		cached = true;
	पूर्ण
	वापस cached_result;
पूर्ण
