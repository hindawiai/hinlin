<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/types.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/stringअगरy.h>
#समावेश "header.h"
#समावेश "utils_header.h"
#समावेश "metricgroup.h"
#समावेश <api/fs/fs.h>

पूर्णांक
get_cpuid(अक्षर *buffer, माप_प्रकार sz)
अणु
	अचिन्हित दीर्घ pvr;
	पूर्णांक nb;

	pvr = mfspr(SPRN_PVR);

	nb = scnम_लिखो(buffer, sz, "%lu,%lu$", PVR_VER(pvr), PVR_REV(pvr));

	/* look क्रम end marker to ensure the entire data fit */
	अगर (म_अक्षर(buffer, '$')) अणु
		buffer[nb-1] = '\0';
		वापस 0;
	पूर्ण
	वापस ENOBUFS;
पूर्ण

अक्षर *
get_cpuid_str(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
	अक्षर *bufp;

	अगर (aप्र_लिखो(&bufp, "%.8lx", mfspr(SPRN_PVR)) < 0)
		bufp = शून्य;

	वापस bufp;
पूर्ण

पूर्णांक arch_get_runसमयparam(काष्ठा pmu_event *pe)
अणु
	पूर्णांक count;
	अक्षर path[PATH_MAX] = "/devices/hv_24x7/interface/";

	म_से_प(pe->aggr_mode) == PerChip ? म_जोड़ो(path, "sockets") : म_जोड़ो(path, "coresperchip");
	वापस sysfs__पढ़ो_पूर्णांक(path, &count) < 0 ? 1 : count;
पूर्ण
