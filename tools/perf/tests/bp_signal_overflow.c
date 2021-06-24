<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Originally करोne by Vince Weaver <vincent.weaver@मुख्यe.edu> क्रम
 * perf_event_tests (git://github.com/deater/perf_event_tests)
 */

/*
 * Powerpc needs __SANE_USERSPACE_TYPES__ beक्रमe <linux/types.h> to select
 * 'int-ll64.h' and aव्योम compile warnings when prपूर्णांकing __u64 with %llu.
 */
#घोषणा __SANE_USERSPACE_TYPES__

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <समय.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <linux/compiler.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "../perf-sys.h"
#समावेश "cloexec.h"

अटल पूर्णांक overflows;

अटल noअंतरभूत पूर्णांक test_function(व्योम)
अणु
	वापस समय(शून्य);
पूर्ण

अटल व्योम sig_handler(पूर्णांक signum __maybe_unused,
			siginfo_t *oh __maybe_unused,
			व्योम *uc __maybe_unused)
अणु
	overflows++;
पूर्ण

अटल दीर्घ दीर्घ bp_count(पूर्णांक fd)
अणु
	दीर्घ दीर्घ count;
	पूर्णांक ret;

	ret = पढ़ो(fd, &count, माप(दीर्घ दीर्घ));
	अगर (ret != माप(दीर्घ दीर्घ)) अणु
		pr_debug("failed to read: %d\n", ret);
		वापस TEST_FAIL;
	पूर्ण

	वापस count;
पूर्ण

#घोषणा EXECUTIONS 10000
#घोषणा THRESHOLD  100

पूर्णांक test__bp_संकेत_overflow(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा perf_event_attr pe;
	काष्ठा sigaction sa;
	दीर्घ दीर्घ count;
	पूर्णांक fd, i, fails = 0;

	/* setup SIGIO संकेत handler */
	स_रखो(&sa, 0, माप(काष्ठा sigaction));
	sa.sa_sigaction = (व्योम *) sig_handler;
	sa.sa_flags = SA_SIGINFO;

	अगर (sigaction(SIGIO, &sa, शून्य) < 0) अणु
		pr_debug("failed setting up signal handler\n");
		वापस TEST_FAIL;
	पूर्ण

	स_रखो(&pe, 0, माप(काष्ठा perf_event_attr));
	pe.type = PERF_TYPE_BREAKPOINT;
	pe.size = माप(काष्ठा perf_event_attr);

	pe.config = 0;
	pe.bp_type = HW_BREAKPOINT_X;
	pe.bp_addr = (अचिन्हित दीर्घ) test_function;
	pe.bp_len = माप(दीर्घ);

	pe.sample_period = THRESHOLD;
	pe.sample_type = PERF_SAMPLE_IP;
	pe.wakeup_events = 1;

	pe.disabled = 1;
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;

	fd = sys_perf_event_खोलो(&pe, 0, -1, -1,
				 perf_event_खोलो_cloexec_flag());
	अगर (fd < 0) अणु
		pr_debug("failed opening event %llx\n", pe.config);
		वापस TEST_FAIL;
	पूर्ण

	fcntl(fd, F_SETFL, O_RDWR|O_NONBLOCK|O_ASYNC);
	fcntl(fd, F_SETSIG, SIGIO);
	fcntl(fd, F_SETOWN, getpid());

	ioctl(fd, PERF_EVENT_IOC_RESET, 0);
	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

	क्रम (i = 0; i < EXECUTIONS; i++)
		test_function();

	ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);

	count = bp_count(fd);

	बंद(fd);

	pr_debug("count %lld, overflow %d\n",
		 count, overflows);

	अगर (count != EXECUTIONS) अणु
		pr_debug("\tWrong number of executions %lld != %d\n",
		count, EXECUTIONS);
		fails++;
	पूर्ण

	अगर (overflows != EXECUTIONS / THRESHOLD) अणु
		pr_debug("\tWrong number of overflows %d != %d\n",
		overflows, EXECUTIONS / THRESHOLD);
		fails++;
	पूर्ण

	वापस fails ? TEST_FAIL : TEST_OK;
पूर्ण
