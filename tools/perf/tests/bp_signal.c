<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Inspired by अवरोधpoपूर्णांक overflow test करोne by
 * Vince Weaver <vincent.weaver@मुख्यe.edu> क्रम perf_event_tests
 * (git://github.com/deater/perf_event_tests)
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
#समावेश "perf-sys.h"
#समावेश "cloexec.h"

अटल पूर्णांक fd1;
अटल पूर्णांक fd2;
अटल पूर्णांक fd3;
अटल पूर्णांक overflows;
अटल पूर्णांक overflows_2;

अस्थिर दीर्घ the_var;


/*
 * Use ASM to ensure watchpoपूर्णांक and अवरोधpoपूर्णांक can be triggered
 * at one inकाष्ठाion.
 */
#अगर defined (__x86_64__)
बाह्य व्योम __test_function(अस्थिर दीर्घ *ptr);
यंत्र (
	".pushsection .text;"
	".globl __test_function\n"
	".type __test_function, @function;"
	"__test_function:\n"
	"incq (%rdi)\n"
	"ret\n"
	".popsection\n");
#अन्यथा
अटल व्योम __test_function(अस्थिर दीर्घ *ptr)
अणु
	*ptr = 0x1234;
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत पूर्णांक test_function(व्योम)
अणु
	__test_function(&the_var);
	the_var++;
	वापस समय(शून्य);
पूर्ण

अटल व्योम sig_handler_2(पूर्णांक signum __maybe_unused,
			  siginfo_t *oh __maybe_unused,
			  व्योम *uc __maybe_unused)
अणु
	overflows_2++;
	अगर (overflows_2 > 10) अणु
		ioctl(fd1, PERF_EVENT_IOC_DISABLE, 0);
		ioctl(fd2, PERF_EVENT_IOC_DISABLE, 0);
		ioctl(fd3, PERF_EVENT_IOC_DISABLE, 0);
	पूर्ण
पूर्ण

अटल व्योम sig_handler(पूर्णांक signum __maybe_unused,
			siginfo_t *oh __maybe_unused,
			व्योम *uc __maybe_unused)
अणु
	overflows++;

	अगर (overflows > 10) अणु
		/*
		 * This should be executed only once during
		 * this test, अगर we are here क्रम the 10th
		 * समय, consider this the recursive issue.
		 *
		 * We can get out of here by disable events,
		 * so no new SIGIO is delivered.
		 */
		ioctl(fd1, PERF_EVENT_IOC_DISABLE, 0);
		ioctl(fd2, PERF_EVENT_IOC_DISABLE, 0);
		ioctl(fd3, PERF_EVENT_IOC_DISABLE, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक __event(bool is_x, व्योम *addr, पूर्णांक sig)
अणु
	काष्ठा perf_event_attr pe;
	पूर्णांक fd;

	स_रखो(&pe, 0, माप(काष्ठा perf_event_attr));
	pe.type = PERF_TYPE_BREAKPOINT;
	pe.size = माप(काष्ठा perf_event_attr);

	pe.config = 0;
	pe.bp_type = is_x ? HW_BREAKPOINT_X : HW_BREAKPOINT_W;
	pe.bp_addr = (अचिन्हित दीर्घ) addr;
	pe.bp_len = माप(दीर्घ);

	pe.sample_period = 1;
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
	fcntl(fd, F_SETSIG, sig);
	fcntl(fd, F_SETOWN, getpid());

	ioctl(fd, PERF_EVENT_IOC_RESET, 0);

	वापस fd;
पूर्ण

अटल पूर्णांक bp_event(व्योम *addr, पूर्णांक sig)
अणु
	वापस __event(true, addr, sig);
पूर्ण

अटल पूर्णांक wp_event(व्योम *addr, पूर्णांक sig)
अणु
	वापस __event(false, addr, sig);
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

पूर्णांक test__bp_संकेत(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा sigaction sa;
	दीर्घ दीर्घ count1, count2, count3;

	/* setup SIGIO संकेत handler */
	स_रखो(&sa, 0, माप(काष्ठा sigaction));
	sa.sa_sigaction = (व्योम *) sig_handler;
	sa.sa_flags = SA_SIGINFO;

	अगर (sigaction(SIGIO, &sa, शून्य) < 0) अणु
		pr_debug("failed setting up signal handler\n");
		वापस TEST_FAIL;
	पूर्ण

	sa.sa_sigaction = (व्योम *) sig_handler_2;
	अगर (sigaction(SIGUSR1, &sa, शून्य) < 0) अणु
		pr_debug("failed setting up signal handler 2\n");
		वापस TEST_FAIL;
	पूर्ण

	/*
	 * We create following events:
	 *
	 * fd1 - अवरोधpoपूर्णांक event on __test_function with SIGIO
	 *       संकेत configured. We should get संकेत
	 *       notअगरication each समय the अवरोधpoपूर्णांक is hit
	 *
	 * fd2 - अवरोधpoपूर्णांक event on sig_handler with SIGUSR1
	 *       configured. We should get SIGUSR1 each समय when
	 *       अवरोधpoपूर्णांक is hit
	 *
	 * fd3 - watchpoपूर्णांक event on __test_function with SIGIO
	 *       configured.
	 *
	 * Following processing should happen:
	 *   Exec:               Action:                       Result:
	 *   incq (%rdi)       - fd1 event अवरोधpoपूर्णांक hit   -> count1 == 1
	 *                     - SIGIO is delivered
	 *   sig_handler       - fd2 event अवरोधpoपूर्णांक hit   -> count2 == 1
	 *                     - SIGUSR1 is delivered
	 *   sig_handler_2                                  -> overflows_2 == 1  (nested संकेत)
	 *   sys_rt_sigवापस  - वापस from sig_handler_2
	 *   overflows++                                    -> overflows = 1
	 *   sys_rt_sigवापस  - वापस from sig_handler
	 *   incq (%rdi)       - fd3 event watchpoपूर्णांक hit   -> count3 == 1       (wp and bp in one insn)
	 *                     - SIGIO is delivered
	 *   sig_handler       - fd2 event अवरोधpoपूर्णांक hit   -> count2 == 2
	 *                     - SIGUSR1 is delivered
	 *   sig_handler_2                                  -> overflows_2 == 2  (nested संकेत)
	 *   sys_rt_sigवापस  - वापस from sig_handler_2
	 *   overflows++                                    -> overflows = 2
	 *   sys_rt_sigवापस  - वापस from sig_handler
	 *   the_var++         - fd3 event watchpoपूर्णांक hit   -> count3 == 2       (standalone watchpoपूर्णांक)
	 *                     - SIGIO is delivered
	 *   sig_handler       - fd2 event अवरोधpoपूर्णांक hit   -> count2 == 3
	 *                     - SIGUSR1 is delivered
	 *   sig_handler_2                                  -> overflows_2 == 3  (nested संकेत)
	 *   sys_rt_sigवापस  - वापस from sig_handler_2
	 *   overflows++                                    -> overflows == 3
	 *   sys_rt_sigवापस  - वापस from sig_handler
	 *
	 * The test हाल check following error conditions:
	 * - we get stuck in संकेत handler because of debug
	 *   exception being triggered recursively due to
	 *   the wrong RF EFLAG management
	 *
	 * - we never trigger the sig_handler अवरोधpoपूर्णांक due
	 *   to the wrong RF EFLAG management
	 *
	 */

	fd1 = bp_event(__test_function, SIGIO);
	fd2 = bp_event(sig_handler, SIGUSR1);
	fd3 = wp_event((व्योम *)&the_var, SIGIO);

	ioctl(fd1, PERF_EVENT_IOC_ENABLE, 0);
	ioctl(fd2, PERF_EVENT_IOC_ENABLE, 0);
	ioctl(fd3, PERF_EVENT_IOC_ENABLE, 0);

	/*
	 * Kick off the test by triggering 'fd1'
	 * अवरोधpoपूर्णांक.
	 */
	test_function();

	ioctl(fd1, PERF_EVENT_IOC_DISABLE, 0);
	ioctl(fd2, PERF_EVENT_IOC_DISABLE, 0);
	ioctl(fd3, PERF_EVENT_IOC_DISABLE, 0);

	count1 = bp_count(fd1);
	count2 = bp_count(fd2);
	count3 = bp_count(fd3);

	बंद(fd1);
	बंद(fd2);
	बंद(fd3);

	pr_debug("count1 %lld, count2 %lld, count3 %lld, overflow %d, overflows_2 %d\n",
		 count1, count2, count3, overflows, overflows_2);

	अगर (count1 != 1) अणु
		अगर (count1 == 11)
			pr_debug("failed: RF EFLAG recursion issue detected\n");
		अन्यथा
			pr_debug("failed: wrong count for bp1: %lld, expected 1\n", count1);
	पूर्ण

	अगर (overflows != 3)
		pr_debug("failed: wrong overflow (%d) hit, expected 3\n", overflows);

	अगर (overflows_2 != 3)
		pr_debug("failed: wrong overflow_2 (%d) hit, expected 3\n", overflows_2);

	अगर (count2 != 3)
		pr_debug("failed: wrong count for bp2 (%lld), expected 3\n", count2);

	अगर (count3 != 2)
		pr_debug("failed: wrong count for bp3 (%lld), expected 2\n", count3);

	वापस count1 == 1 && overflows == 3 && count2 == 3 && overflows_2 == 3 && count3 == 2 ?
		TEST_OK : TEST_FAIL;
पूर्ण

bool test__bp_संकेत_is_supported(व्योम)
अणु
	/*
	 * PowerPC and S390 करो not support creation of inकाष्ठाion
	 * अवरोधpoपूर्णांकs using the perf_event पूर्णांकerface.
	 *
	 * ARM requires explicit rounding करोwn of the inकाष्ठाion
	 * poपूर्णांकer in Thumb mode, and then requires the single-step
	 * to be handled explicitly in the overflow handler to aव्योम
	 * stepping पूर्णांकo the SIGIO handler and getting stuck on the
	 * अवरोधpoपूर्णांकed inकाष्ठाion.
	 *
	 * Since arm64 has the same issue with arm क्रम the single-step
	 * handling, this हाल also माला_लो stuck on the अवरोधpoपूर्णांकed
	 * inकाष्ठाion.
	 *
	 * Just disable the test क्रम these architectures until these
	 * issues are resolved.
	 */
#अगर defined(__घातerpc__) || defined(__s390x__) || defined(__arm__) || \
    defined(__aarch64__)
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण
