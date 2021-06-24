<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>

#समावेश "cpu.h"
#समावेश "fs/fs.h"

पूर्णांक cpu__get_max_freq(अचिन्हित दीर्घ दीर्घ *freq)
अणु
	अक्षर entry[PATH_MAX];
	पूर्णांक cpu;

	अगर (sysfs__पढ़ो_पूर्णांक("devices/system/cpu/online", &cpu) < 0)
		वापस -1;

	snम_लिखो(entry, माप(entry),
		 "devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", cpu);

	वापस sysfs__पढ़ो_ull(entry, freq);
पूर्ण
