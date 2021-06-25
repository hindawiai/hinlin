<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <api/fs/fs.h>
#समावेश "header.h"

#घोषणा STR_LEN 1024

अक्षर *get_cpuid_str(काष्ठा perf_pmu *pmu)
अणु
	/* In nds32, we only have one cpu */
	अक्षर *buf = शून्य;
	काष्ठा cpu_map *cpus;
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (!sysfs || !pmu || !pmu->cpus)
		वापस शून्य;

	buf = दो_स्मृति(STR_LEN);
	अगर (!buf)
		वापस शून्य;

	cpus = cpu_map__get(pmu->cpus);
	प्र_लिखो(buf, "0x%x", cpus->nr - 1);
	cpu_map__put(cpus);
	वापस buf;
पूर्ण
