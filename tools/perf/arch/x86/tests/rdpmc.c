<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश "perf-sys.h"
#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "cloexec.h"
#समावेश "event.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "arch-tests.h"

अटल u64 rdpmc(अचिन्हित पूर्णांक counter)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdpmc" : "=a" (low), "=d" (high) : "c" (counter));

	वापस low | ((u64)high) << 32;
पूर्ण

अटल u64 rdtsc(व्योम)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdtsc" : "=a" (low), "=d" (high));

	वापस low | ((u64)high) << 32;
पूर्ण

अटल u64 mmap_पढ़ो_self(व्योम *addr)
अणु
	काष्ठा perf_event_mmap_page *pc = addr;
	u32 seq, idx, समय_mult = 0, समय_shअगरt = 0;
	u64 count, cyc = 0, समय_offset = 0, enabled, running, delta;

	करो अणु
		seq = pc->lock;
		barrier();

		enabled = pc->समय_enabled;
		running = pc->समय_running;

		अगर (enabled != running) अणु
			cyc = rdtsc();
			समय_mult = pc->समय_mult;
			समय_shअगरt = pc->समय_shअगरt;
			समय_offset = pc->समय_offset;
		पूर्ण

		idx = pc->index;
		count = pc->offset;
		अगर (idx)
			count += rdpmc(idx - 1);

		barrier();
	पूर्ण जबतक (pc->lock != seq);

	अगर (enabled != running) अणु
		u64 quot, rem;

		quot = (cyc >> समय_shअगरt);
		rem = cyc & (((u64)1 << समय_shअगरt) - 1);
		delta = समय_offset + quot * समय_mult +
			((rem * समय_mult) >> समय_shअगरt);

		enabled += delta;
		अगर (idx)
			running += delta;

		quot = count / running;
		rem = count % running;
		count = quot * enabled + (rem * enabled) / running;
	पूर्ण

	वापस count;
पूर्ण

/*
 * If the RDPMC inकाष्ठाion faults then संकेत this back to the test parent task:
 */
अटल व्योम segfault_handler(पूर्णांक sig __maybe_unused,
			     siginfo_t *info __maybe_unused,
			     व्योम *uc __maybe_unused)
अणु
	निकास(-1);
पूर्ण

अटल पूर्णांक __test__rdpmc(व्योम)
अणु
	अस्थिर पूर्णांक पंचांगp = 0;
	u64 i, loops = 1000;
	पूर्णांक n;
	पूर्णांक fd;
	व्योम *addr;
	काष्ठा perf_event_attr attr = अणु
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_INSTRUCTIONS,
		.exclude_kernel = 1,
	पूर्ण;
	u64 delta_sum = 0;
        काष्ठा sigaction sa;
	अक्षर sbuf[STRERR_बफ_मानE];

	sigfillset(&sa.sa_mask);
	sa.sa_sigaction = segfault_handler;
	sa.sa_flags = 0;
	sigaction(संक_अंश, &sa, शून्य);

	fd = sys_perf_event_खोलो(&attr, 0, -1, -1,
				 perf_event_खोलो_cloexec_flag());
	अगर (fd < 0) अणु
		pr_err("Error: sys_perf_event_open() syscall returned "
		       "with %d (%s)\n", fd,
		       str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस -1;
	पूर्ण

	addr = mmap(शून्य, page_size, PROT_READ, MAP_SHARED, fd, 0);
	अगर (addr == (व्योम *)(-1)) अणु
		pr_err("Error: mmap() syscall returned with (%s)\n",
		       str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out_बंद;
	पूर्ण

	क्रम (n = 0; n < 6; n++) अणु
		u64 stamp, now, delta;

		stamp = mmap_पढ़ो_self(addr);

		क्रम (i = 0; i < loops; i++)
			पंचांगp++;

		now = mmap_पढ़ो_self(addr);
		loops *= 10;

		delta = now - stamp;
		pr_debug("%14d: %14Lu\n", n, (दीर्घ दीर्घ)delta);

		delta_sum += delta;
	पूर्ण

	munmap(addr, page_size);
	pr_debug("   ");
out_बंद:
	बंद(fd);

	अगर (!delta_sum)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक test__rdpmc(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक status = 0;
	पूर्णांक wret = 0;
	पूर्णांक ret;
	पूर्णांक pid;

	pid = विभाजन();
	अगर (pid < 0)
		वापस -1;

	अगर (!pid) अणु
		ret = __test__rdpmc();

		निकास(ret);
	पूर्ण

	wret = रुकोpid(pid, &status, 0);
	अगर (wret < 0 || status)
		वापस -1;

	वापस 0;
पूर्ण
