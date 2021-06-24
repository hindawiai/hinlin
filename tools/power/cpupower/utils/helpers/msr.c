<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानक_निवेशt.h>

#समावेश "helpers/helpers.h"

/* Intel specअगरic MSRs */
#घोषणा MSR_IA32_PERF_STATUS		0x198
#घोषणा MSR_IA32_MISC_ENABLES		0x1a0
#घोषणा MSR_NEHALEM_TURBO_RATIO_LIMIT	0x1ad

/*
 * पढ़ो_msr
 *
 * Will वापस 0 on success and -1 on failure.
 * Possible त्रुटि_सं values could be:
 * EFAULT -If the पढ़ो/ग_लिखो did not fully complete
 * EIO    -If the CPU करोes not support MSRs
 * ENXIO  -If the CPU करोes not exist
 */

पूर्णांक पढ़ो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ *val)
अणु
	पूर्णांक fd;
	अक्षर msr_file_name[64];

	प्र_लिखो(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(msr_file_name, O_RDONLY);
	अगर (fd < 0)
		वापस -1;
	अगर (lseek(fd, idx, प्रस्तुत_से) == -1)
		जाओ err;
	अगर (पढ़ो(fd, val, माप *val) != माप *val)
		जाओ err;
	बंद(fd);
	वापस 0;
 err:
	बंद(fd);
	वापस -1;
पूर्ण

/*
 * ग_लिखो_msr
 *
 * Will वापस 0 on success and -1 on failure.
 * Possible त्रुटि_सं values could be:
 * EFAULT -If the पढ़ो/ग_लिखो did not fully complete
 * EIO    -If the CPU करोes not support MSRs
 * ENXIO  -If the CPU करोes not exist
 */
पूर्णांक ग_लिखो_msr(पूर्णांक cpu, अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ दीर्घ val)
अणु
	पूर्णांक fd;
	अक्षर msr_file_name[64];

	प्र_लिखो(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(msr_file_name, O_WRONLY);
	अगर (fd < 0)
		वापस -1;
	अगर (lseek(fd, idx, प्रस्तुत_से) == -1)
		जाओ err;
	अगर (ग_लिखो(fd, &val, माप val) != माप val)
		जाओ err;
	बंद(fd);
	वापस 0;
 err:
	बंद(fd);
	वापस -1;
पूर्ण

अचिन्हित दीर्घ दीर्घ msr_पूर्णांकel_get_turbo_ratio(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	पूर्णांक ret;

	अगर (!(cpuघातer_cpu_info.caps & CPUPOWER_CAP_HAS_TURBO_RATIO))
		वापस -1;

	ret = पढ़ो_msr(cpu, MSR_NEHALEM_TURBO_RATIO_LIMIT, &val);
	अगर (ret)
		वापस ret;
	वापस val;
पूर्ण
#पूर्ण_अगर
