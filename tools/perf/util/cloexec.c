<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश "util.h" // क्रम sched_अ_लोpu()
#समावेश "../perf-sys.h"
#समावेश "cloexec.h"
#समावेश "event.h"
#समावेश "asm/bug.h"
#समावेश "debug.h"
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <linux/माला.स>

अटल अचिन्हित दीर्घ flag = PERF_FLAG_FD_CLOEXEC;

पूर्णांक __weak sched_अ_लोpu(व्योम)
अणु
#अगर_घोषित __NR_अ_लोpu
	अचिन्हित cpu;
	पूर्णांक err = syscall(__NR_अ_लोpu, &cpu, शून्य, शून्य);
	अगर (!err)
		वापस cpu;
#अन्यथा
	त्रुटि_सं = ENOSYS;
#पूर्ण_अगर
	वापस -1;
पूर्ण

अटल पूर्णांक perf_flag_probe(व्योम)
अणु
	/* use 'safest' configuration as used in evsel__fallback() */
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_CPU_CLOCK,
		.exclude_kernel = 1,
	पूर्ण;
	पूर्णांक fd;
	पूर्णांक err;
	पूर्णांक cpu;
	pid_t pid = -1;
	अक्षर sbuf[STRERR_बफ_मानE];

	cpu = sched_अ_लोpu();
	अगर (cpu < 0)
		cpu = 0;

	/*
	 * Using -1 क्रम the pid is a workaround to aव्योम gratuitous jump label
	 * changes.
	 */
	जबतक (1) अणु
		/* check cloexec flag */
		fd = sys_perf_event_खोलो(&attr, pid, cpu, -1,
					 PERF_FLAG_FD_CLOEXEC);
		अगर (fd < 0 && pid == -1 && त्रुटि_सं == EACCES) अणु
			pid = 0;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	err = त्रुटि_सं;

	अगर (fd >= 0) अणु
		बंद(fd);
		वापस 1;
	पूर्ण

	WARN_ONCE(err != EINVAL && err != EBUSY && err != EACCES,
		  "perf_event_open(..., PERF_FLAG_FD_CLOEXEC) failed with unexpected error %d (%s)\n",
		  err, str_error_r(err, sbuf, माप(sbuf)));

	/* not supported, confirm error related to PERF_FLAG_FD_CLOEXEC */
	जबतक (1) अणु
		fd = sys_perf_event_खोलो(&attr, pid, cpu, -1, 0);
		अगर (fd < 0 && pid == -1 && त्रुटि_सं == EACCES) अणु
			pid = 0;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	err = त्रुटि_सं;

	अगर (fd >= 0)
		बंद(fd);

	अगर (WARN_ONCE(fd < 0 && err != EBUSY && err != EACCES,
		      "perf_event_open(..., 0) failed unexpectedly with error %d (%s)\n",
		      err, str_error_r(err, sbuf, माप(sbuf))))
		वापस -1;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ perf_event_खोलो_cloexec_flag(व्योम)
अणु
	अटल bool probed;

	अगर (!probed) अणु
		अगर (perf_flag_probe() <= 0)
			flag = 0;
		probed = true;
	पूर्ण

	वापस flag;
पूर्ण
