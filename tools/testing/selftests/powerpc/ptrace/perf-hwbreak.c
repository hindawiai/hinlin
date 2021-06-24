<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * perf events self profiling example test हाल क्रम hw अवरोधpoपूर्णांकs.
 *
 * This tests perf PERF_TYPE_BREAKPOINT parameters
 * 1) tests all variants of the अवरोध on पढ़ो/ग_लिखो flags
 * 2) tests exclude_user == 0 and 1
 * 3) test array matches (अगर DAWR is supported))
 * 4) test dअगरferent numbers of अवरोधpoपूर्णांकs matches
 *
 * Configure this अवरोधpoपूर्णांक, then पढ़ो and ग_लिखो the data a number of
 * बार. Then check the output count from perf is as expected.
 *
 * Based on:
 *   http://ozद_असल.org/~anton/junkcode/perf_events_example1.c
 *
 * Copyright (C) 2018 Michael Neuling, IBM Corporation.
 */

#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/रुको.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/sysinfo.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <elf.h>
#समावेश <pthपढ़ो.h>
#समावेश <sys/syscall.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश "utils.h"

#अगर_अघोषित PPC_DEBUG_FEATURE_DATA_BP_ARCH_31
#घोषणा PPC_DEBUG_FEATURE_DATA_BP_ARCH_31	0x20
#पूर्ण_अगर

#घोषणा MAX_LOOPS 10000

#घोषणा DAWR_LENGTH_MAX ((0x3f + 1) * 8)

पूर्णांक nprocs;

अटल अस्थिर पूर्णांक a = 10;
अटल अस्थिर पूर्णांक b = 10;
अटल अस्थिर अक्षर c[512 + 8] __attribute__((aligned(512)));

अटल व्योम perf_event_attr_set(काष्ठा perf_event_attr *attr,
				__u32 type, __u64 addr, __u64 len,
				bool exclude_user)
अणु
	स_रखो(attr, 0, माप(काष्ठा perf_event_attr));
	attr->type           = PERF_TYPE_BREAKPOINT;
	attr->size           = माप(काष्ठा perf_event_attr);
	attr->bp_type        = type;
	attr->bp_addr        = addr;
	attr->bp_len         = len;
	attr->exclude_kernel = 1;
	attr->exclude_hv     = 1;
	attr->exclude_guest  = 1;
	attr->exclude_user   = exclude_user;
	attr->disabled       = 1;
पूर्ण

अटल पूर्णांक
perf_process_event_खोलो_exclude_user(__u32 type, __u64 addr, __u64 len, bool exclude_user)
अणु
	काष्ठा perf_event_attr attr;

	perf_event_attr_set(&attr, type, addr, len, exclude_user);
	वापस syscall(__NR_perf_event_खोलो, &attr, getpid(), -1, -1, 0);
पूर्ण

अटल पूर्णांक perf_process_event_खोलो(__u32 type, __u64 addr, __u64 len)
अणु
	काष्ठा perf_event_attr attr;

	perf_event_attr_set(&attr, type, addr, len, 0);
	वापस syscall(__NR_perf_event_खोलो, &attr, getpid(), -1, -1, 0);
पूर्ण

अटल पूर्णांक perf_cpu_event_खोलो(दीर्घ cpu, __u32 type, __u64 addr, __u64 len)
अणु
	काष्ठा perf_event_attr attr;

	perf_event_attr_set(&attr, type, addr, len, 0);
	वापस syscall(__NR_perf_event_खोलो, &attr, -1, cpu, -1, 0);
पूर्ण

अटल व्योम बंद_fds(पूर्णांक *fd, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		बंद(fd[i]);
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_fds(पूर्णांक *fd, पूर्णांक n)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ c = 0;
	अचिन्हित दीर्घ count = 0;
	माप_प्रकार res;

	क्रम (i = 0; i < n; i++) अणु
		res = पढ़ो(fd[i], &c, माप(c));
		निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
		count += c;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम reset_fds(पूर्णांक *fd, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		ioctl(fd[i], PERF_EVENT_IOC_RESET);
पूर्ण

अटल व्योम enable_fds(पूर्णांक *fd, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		ioctl(fd[i], PERF_EVENT_IOC_ENABLE);
पूर्ण

अटल व्योम disable_fds(पूर्णांक *fd, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		ioctl(fd[i], PERF_EVENT_IOC_DISABLE);
पूर्ण

अटल पूर्णांक perf_प्रणालीwide_event_खोलो(पूर्णांक *fd, __u32 type, __u64 addr, __u64 len)
अणु
	पूर्णांक i = 0;

	/* Assume online processors are 0 to nprocs क्रम simplisity */
	क्रम (i = 0; i < nprocs; i++) अणु
		fd[i] = perf_cpu_event_खोलो(i, type, addr, len);
		अगर (fd[i] < 0) अणु
			बंद_fds(fd, i);
			वापस fd[i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool अवरोधpoपूर्णांक_test(पूर्णांक len)
अणु
	पूर्णांक fd;

	/* bp_addr can poपूर्णांक anywhere but needs to be aligned */
	fd = perf_process_event_खोलो(HW_BREAKPOINT_R, (__u64)(&fd) & 0xfffffffffffff800, len);
	अगर (fd < 0)
		वापस false;
	बंद(fd);
	वापस true;
पूर्ण

अटल अंतरभूत bool perf_अवरोधpoपूर्णांक_supported(व्योम)
अणु
	वापस अवरोधpoपूर्णांक_test(4);
पूर्ण

अटल अंतरभूत bool dawr_supported(व्योम)
अणु
	वापस अवरोधpoपूर्णांक_test(DAWR_LENGTH_MAX);
पूर्ण

अटल पूर्णांक runtestsingle(पूर्णांक पढ़ोग_लिखोflag, पूर्णांक exclude_user, पूर्णांक arraytest)
अणु
	पूर्णांक i,j;
	माप_प्रकार res;
	अचिन्हित दीर्घ दीर्घ अवरोधs, needed;
	पूर्णांक पढ़ोपूर्णांक;
	पूर्णांक पढ़ोपूर्णांकarraybig[2*DAWR_LENGTH_MAX/माप(पूर्णांक)];
	पूर्णांक *पढ़ोपूर्णांकalign;
	अस्थिर पूर्णांक *ptr;
	पूर्णांक अवरोध_fd;
	पूर्णांक loop_num = MAX_LOOPS - (अक्रम() % 100); /* provide some variability */
	अस्थिर पूर्णांक *k;
	__u64 len;

	/* align to 0x400 boundary as required by DAWR */
	पढ़ोपूर्णांकalign = (पूर्णांक *)(((अचिन्हित दीर्घ)पढ़ोपूर्णांकarraybig + 0x7ff) &
			       0xfffffffffffff800);

	ptr = &पढ़ोपूर्णांक;
	अगर (arraytest)
		ptr = &पढ़ोपूर्णांकalign[0];

	len = arraytest ? DAWR_LENGTH_MAX : माप(पूर्णांक);
	अवरोध_fd = perf_process_event_खोलो_exclude_user(पढ़ोग_लिखोflag, (__u64)ptr,
							len, exclude_user);
	अगर (अवरोध_fd < 0) अणु
		लिखो_त्रुटि("perf_process_event_open_exclude_user");
		निकास(1);
	पूर्ण

	/* start counters */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);

	/* Test a bunch of पढ़ोs and ग_लिखोs */
	k = &पढ़ोपूर्णांक;
	क्रम (i = 0; i < loop_num; i++) अणु
		अगर (arraytest)
			k = &(पढ़ोपूर्णांकalign[i % (DAWR_LENGTH_MAX/माप(पूर्णांक))]);

		j = *k;
		*k = j;
	पूर्ण

	/* stop counters */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);

	/* पढ़ो and check counters */
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	/* we पढ़ो and ग_लिखो each loop, so subtract the ones we are counting */
	needed = 0;
	अगर (पढ़ोग_लिखोflag & HW_BREAKPOINT_R)
		needed += loop_num;
	अगर (पढ़ोग_लिखोflag & HW_BREAKPOINT_W)
		needed += loop_num;
	needed = needed * (1 - exclude_user);
	म_लिखो("TESTED: addr:0x%lx brks:% 8lld loops:% 8i rw:%i !user:%i array:%i\n",
	       (अचिन्हित दीर्घ पूर्णांक)ptr, अवरोधs, loop_num, पढ़ोग_लिखोflag, exclude_user, arraytest);
	अगर (अवरोधs != needed) अणु
		म_लिखो("FAILED: 0x%lx brks:%lld needed:%lli %i %i %i\n\n",
		       (अचिन्हित दीर्घ पूर्णांक)ptr, अवरोधs, needed, loop_num, पढ़ोग_लिखोflag, exclude_user);
		वापस 1;
	पूर्ण
	बंद(अवरोध_fd);

	वापस 0;
पूर्ण

अटल पूर्णांक runtest_dar_outside(व्योम)
अणु
	व्योम *target;
	अस्थिर __u16 temp16;
	अस्थिर __u64 temp64;
	पूर्णांक अवरोध_fd;
	अचिन्हित दीर्घ दीर्घ अवरोधs;
	पूर्णांक fail = 0;
	माप_प्रकार res;

	target = दो_स्मृति(8);
	अगर (!target) अणु
		लिखो_त्रुटि("malloc failed");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* watch middle half of target array */
	अवरोध_fd = perf_process_event_खोलो(HW_BREAKPOINT_RW, (__u64)(target + 2), 4);
	अगर (अवरोध_fd < 0) अणु
		मुक्त(target);
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Shouldn't hit. */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_RESET);
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);
	temp16 = *((__u16 *)target);
	*((__u16 *)target) = temp16;
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	अगर (अवरोधs == 0) अणु
		म_लिखो("TESTED: No overlap\n");
	पूर्ण अन्यथा अणु
		म_लिखो("FAILED: No overlap: %lld != 0\n", अवरोधs);
		fail = 1;
	पूर्ण

	/* Hit */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_RESET);
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);
	temp16 = *((__u16 *)(target + 1));
	*((__u16 *)(target + 1)) = temp16;
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	अगर (अवरोधs == 2) अणु
		म_लिखो("TESTED: Partial overlap\n");
	पूर्ण अन्यथा अणु
		म_लिखो("FAILED: Partial overlap: %lld != 2\n", अवरोधs);
		fail = 1;
	पूर्ण

	/* Hit */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_RESET);
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);
	temp16 = *((__u16 *)(target + 5));
	*((__u16 *)(target + 5)) = temp16;
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	अगर (अवरोधs == 2) अणु
		म_लिखो("TESTED: Partial overlap\n");
	पूर्ण अन्यथा अणु
		म_लिखो("FAILED: Partial overlap: %lld != 2\n", अवरोधs);
		fail = 1;
	पूर्ण

	/* Shouldn't Hit */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_RESET);
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);
	temp16 = *((__u16 *)(target + 6));
	*((__u16 *)(target + 6)) = temp16;
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	अगर (अवरोधs == 0) अणु
		म_लिखो("TESTED: No overlap\n");
	पूर्ण अन्यथा अणु
		म_लिखो("FAILED: No overlap: %lld != 0\n", अवरोधs);
		fail = 1;
	पूर्ण

	/* Hit */
	ioctl(अवरोध_fd, PERF_EVENT_IOC_RESET);
	ioctl(अवरोध_fd, PERF_EVENT_IOC_ENABLE);
	temp64 = *((__u64 *)target);
	*((__u64 *)target) = temp64;
	ioctl(अवरोध_fd, PERF_EVENT_IOC_DISABLE);
	res = पढ़ो(अवरोध_fd, &अवरोधs, माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	अगर (अवरोधs == 2) अणु
		म_लिखो("TESTED: Full overlap\n");
	पूर्ण अन्यथा अणु
		म_लिखो("FAILED: Full overlap: %lld != 2\n", अवरोधs);
		fail = 1;
	पूर्ण

	मुक्त(target);
	बंद(अवरोध_fd);
	वापस fail;
पूर्ण

अटल व्योम multi_dawr_workload(व्योम)
अणु
	a += 10;
	b += 10;
	c[512 + 1] += 'a';
पूर्ण

अटल पूर्णांक test_process_multi_dअगरf_addr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक fd1, fd2;
	अक्षर *desc = "Process specific, Two events, diff addr";
	माप_प्रकार res;

	fd1 = perf_process_event_खोलो(HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (fd1 < 0) अणु
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	fd2 = perf_process_event_खोलो(HW_BREAKPOINT_RW, (__u64)&b, (__u64)माप(b));
	अगर (fd2 < 0) अणु
		बंद(fd1);
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ioctl(fd1, PERF_EVENT_IOC_RESET);
	ioctl(fd2, PERF_EVENT_IOC_RESET);
	ioctl(fd1, PERF_EVENT_IOC_ENABLE);
	ioctl(fd2, PERF_EVENT_IOC_ENABLE);
	multi_dawr_workload();
	ioctl(fd1, PERF_EVENT_IOC_DISABLE);
	ioctl(fd2, PERF_EVENT_IOC_DISABLE);

	res = पढ़ो(fd1, &अवरोधs1, माप(अवरोधs1));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	res = पढ़ो(fd2, &अवरोधs2, माप(अवरोधs2));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));

	बंद(fd1);
	बंद(fd2);

	अगर (अवरोधs1 != 2 || अवरोधs2 != 2) अणु
		म_लिखो("FAILED: %s: %lld != 2 || %lld != 2\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_process_multi_same_addr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक fd1, fd2;
	अक्षर *desc = "Process specific, Two events, same addr";
	माप_प्रकार res;

	fd1 = perf_process_event_खोलो(HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (fd1 < 0) अणु
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	fd2 = perf_process_event_खोलो(HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (fd2 < 0) अणु
		बंद(fd1);
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ioctl(fd1, PERF_EVENT_IOC_RESET);
	ioctl(fd2, PERF_EVENT_IOC_RESET);
	ioctl(fd1, PERF_EVENT_IOC_ENABLE);
	ioctl(fd2, PERF_EVENT_IOC_ENABLE);
	multi_dawr_workload();
	ioctl(fd1, PERF_EVENT_IOC_DISABLE);
	ioctl(fd2, PERF_EVENT_IOC_DISABLE);

	res = पढ़ो(fd1, &अवरोधs1, माप(अवरोधs1));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	res = पढ़ो(fd2, &अवरोधs2, माप(अवरोधs2));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));

	बंद(fd1);
	बंद(fd2);

	अगर (अवरोधs1 != 2 || अवरोधs2 != 2) अणु
		म_लिखो("FAILED: %s: %lld != 2 || %lld != 2\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_process_multi_dअगरf_addr_ro_wo(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक fd1, fd2;
	अक्षर *desc = "Process specific, Two events, diff addr, one is RO, other is WO";
	माप_प्रकार res;

	fd1 = perf_process_event_खोलो(HW_BREAKPOINT_W, (__u64)&a, (__u64)माप(a));
	अगर (fd1 < 0) अणु
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	fd2 = perf_process_event_खोलो(HW_BREAKPOINT_R, (__u64)&b, (__u64)माप(b));
	अगर (fd2 < 0) अणु
		बंद(fd1);
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ioctl(fd1, PERF_EVENT_IOC_RESET);
	ioctl(fd2, PERF_EVENT_IOC_RESET);
	ioctl(fd1, PERF_EVENT_IOC_ENABLE);
	ioctl(fd2, PERF_EVENT_IOC_ENABLE);
	multi_dawr_workload();
	ioctl(fd1, PERF_EVENT_IOC_DISABLE);
	ioctl(fd2, PERF_EVENT_IOC_DISABLE);

	res = पढ़ो(fd1, &अवरोधs1, माप(अवरोधs1));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	res = पढ़ो(fd2, &अवरोधs2, माप(अवरोधs2));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));

	बंद(fd1);
	बंद(fd2);

	अगर (अवरोधs1 != 1 || अवरोधs2 != 1) अणु
		म_लिखो("FAILED: %s: %lld != 1 || %lld != 1\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_process_multi_same_addr_ro_wo(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक fd1, fd2;
	अक्षर *desc = "Process specific, Two events, same addr, one is RO, other is WO";
	माप_प्रकार res;

	fd1 = perf_process_event_खोलो(HW_BREAKPOINT_R, (__u64)&a, (__u64)माप(a));
	अगर (fd1 < 0) अणु
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	fd2 = perf_process_event_खोलो(HW_BREAKPOINT_W, (__u64)&a, (__u64)माप(a));
	अगर (fd2 < 0) अणु
		बंद(fd1);
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ioctl(fd1, PERF_EVENT_IOC_RESET);
	ioctl(fd2, PERF_EVENT_IOC_RESET);
	ioctl(fd1, PERF_EVENT_IOC_ENABLE);
	ioctl(fd2, PERF_EVENT_IOC_ENABLE);
	multi_dawr_workload();
	ioctl(fd1, PERF_EVENT_IOC_DISABLE);
	ioctl(fd2, PERF_EVENT_IOC_DISABLE);

	res = पढ़ो(fd1, &अवरोधs1, माप(अवरोधs1));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));
	res = पढ़ो(fd2, &अवरोधs2, माप(अवरोधs2));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));

	बंद(fd1);
	बंद(fd2);

	अगर (अवरोधs1 != 1 || अवरोधs2 != 1) अणु
		म_लिखो("FAILED: %s: %lld != 1 || %lld != 1\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_syswide_multi_dअगरf_addr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक *fd1 = दो_स्मृति(nprocs * माप(पूर्णांक));
	पूर्णांक *fd2 = दो_स्मृति(nprocs * माप(पूर्णांक));
	अक्षर *desc = "Systemwide, Two events, diff addr";
	पूर्णांक ret;

	ret = perf_प्रणालीwide_event_खोलो(fd1, HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = perf_प्रणालीwide_event_खोलो(fd2, HW_BREAKPOINT_RW, (__u64)&b, (__u64)माप(b));
	अगर (ret) अणु
		बंद_fds(fd1, nprocs);
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	reset_fds(fd1, nprocs);
	reset_fds(fd2, nprocs);
	enable_fds(fd1, nprocs);
	enable_fds(fd2, nprocs);
	multi_dawr_workload();
	disable_fds(fd1, nprocs);
	disable_fds(fd2, nprocs);

	अवरोधs1 = पढ़ो_fds(fd1, nprocs);
	अवरोधs2 = पढ़ो_fds(fd2, nprocs);

	बंद_fds(fd1, nprocs);
	बंद_fds(fd2, nprocs);

	मुक्त(fd1);
	मुक्त(fd2);

	अगर (अवरोधs1 != 2 || अवरोधs2 != 2) अणु
		म_लिखो("FAILED: %s: %lld != 2 || %lld != 2\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_syswide_multi_same_addr(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक *fd1 = दो_स्मृति(nprocs * माप(पूर्णांक));
	पूर्णांक *fd2 = दो_स्मृति(nprocs * माप(पूर्णांक));
	अक्षर *desc = "Systemwide, Two events, same addr";
	पूर्णांक ret;

	ret = perf_प्रणालीwide_event_खोलो(fd1, HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = perf_प्रणालीwide_event_खोलो(fd2, HW_BREAKPOINT_RW, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		बंद_fds(fd1, nprocs);
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	reset_fds(fd1, nprocs);
	reset_fds(fd2, nprocs);
	enable_fds(fd1, nprocs);
	enable_fds(fd2, nprocs);
	multi_dawr_workload();
	disable_fds(fd1, nprocs);
	disable_fds(fd2, nprocs);

	अवरोधs1 = पढ़ो_fds(fd1, nprocs);
	अवरोधs2 = पढ़ो_fds(fd2, nprocs);

	बंद_fds(fd1, nprocs);
	बंद_fds(fd2, nprocs);

	मुक्त(fd1);
	मुक्त(fd2);

	अगर (अवरोधs1 != 2 || अवरोधs2 != 2) अणु
		म_लिखो("FAILED: %s: %lld != 2 || %lld != 2\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_syswide_multi_dअगरf_addr_ro_wo(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक *fd1 = दो_स्मृति(nprocs * माप(पूर्णांक));
	पूर्णांक *fd2 = दो_स्मृति(nprocs * माप(पूर्णांक));
	अक्षर *desc = "Systemwide, Two events, diff addr, one is RO, other is WO";
	पूर्णांक ret;

	ret = perf_प्रणालीwide_event_खोलो(fd1, HW_BREAKPOINT_W, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = perf_प्रणालीwide_event_खोलो(fd2, HW_BREAKPOINT_R, (__u64)&b, (__u64)माप(b));
	अगर (ret) अणु
		बंद_fds(fd1, nprocs);
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	reset_fds(fd1, nprocs);
	reset_fds(fd2, nprocs);
	enable_fds(fd1, nprocs);
	enable_fds(fd2, nprocs);
	multi_dawr_workload();
	disable_fds(fd1, nprocs);
	disable_fds(fd2, nprocs);

	अवरोधs1 = पढ़ो_fds(fd1, nprocs);
	अवरोधs2 = पढ़ो_fds(fd2, nprocs);

	बंद_fds(fd1, nprocs);
	बंद_fds(fd2, nprocs);

	मुक्त(fd1);
	मुक्त(fd2);

	अगर (अवरोधs1 != 1 || अवरोधs2 != 1) अणु
		म_लिखो("FAILED: %s: %lld != 1 || %lld != 1\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक test_syswide_multi_same_addr_ro_wo(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs1 = 0, अवरोधs2 = 0;
	पूर्णांक *fd1 = दो_स्मृति(nprocs * माप(पूर्णांक));
	पूर्णांक *fd2 = दो_स्मृति(nprocs * माप(पूर्णांक));
	अक्षर *desc = "Systemwide, Two events, same addr, one is RO, other is WO";
	पूर्णांक ret;

	ret = perf_प्रणालीwide_event_खोलो(fd1, HW_BREAKPOINT_W, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = perf_प्रणालीwide_event_खोलो(fd2, HW_BREAKPOINT_R, (__u64)&a, (__u64)माप(a));
	अगर (ret) अणु
		बंद_fds(fd1, nprocs);
		लिखो_त्रुटि("perf_systemwide_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	reset_fds(fd1, nprocs);
	reset_fds(fd2, nprocs);
	enable_fds(fd1, nprocs);
	enable_fds(fd2, nprocs);
	multi_dawr_workload();
	disable_fds(fd1, nprocs);
	disable_fds(fd2, nprocs);

	अवरोधs1 = पढ़ो_fds(fd1, nprocs);
	अवरोधs2 = पढ़ो_fds(fd2, nprocs);

	बंद_fds(fd1, nprocs);
	बंद_fds(fd2, nprocs);

	मुक्त(fd1);
	मुक्त(fd2);

	अगर (अवरोधs1 != 1 || अवरोधs2 != 1) अणु
		म_लिखो("FAILED: %s: %lld != 1 || %lld != 1\n", desc, अवरोधs1, अवरोधs2);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

अटल पूर्णांक runtest_multi_dawr(व्योम)
अणु
	पूर्णांक ret = 0;

	ret |= test_process_multi_dअगरf_addr();
	ret |= test_process_multi_same_addr();
	ret |= test_process_multi_dअगरf_addr_ro_wo();
	ret |= test_process_multi_same_addr_ro_wo();
	ret |= test_syswide_multi_dअगरf_addr();
	ret |= test_syswide_multi_same_addr();
	ret |= test_syswide_multi_dअगरf_addr_ro_wo();
	ret |= test_syswide_multi_same_addr_ro_wo();

	वापस ret;
पूर्ण

अटल पूर्णांक runtest_unaligned_512bytes(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ अवरोधs = 0;
	पूर्णांक fd;
	अक्षर *desc = "Process specific, 512 bytes, unaligned";
	__u64 addr = (__u64)&c + 8;
	माप_प्रकार res;

	fd = perf_process_event_खोलो(HW_BREAKPOINT_RW, addr, 512);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("perf_process_event_open");
		निकास(निकास_त्रुटि);
	पूर्ण

	ioctl(fd, PERF_EVENT_IOC_RESET);
	ioctl(fd, PERF_EVENT_IOC_ENABLE);
	multi_dawr_workload();
	ioctl(fd, PERF_EVENT_IOC_DISABLE);

	res = पढ़ो(fd, &अवरोधs, माप(अवरोधs));
	निश्चित(res == माप(अचिन्हित दीर्घ दीर्घ));

	बंद(fd);

	अगर (अवरोधs != 2) अणु
		म_लिखो("FAILED: %s: %lld != 2\n", desc, अवरोधs);
		वापस 1;
	पूर्ण

	म_लिखो("TESTED: %s\n", desc);
	वापस 0;
पूर्ण

/* There is no perf api to find number of available watchpoपूर्णांकs. Use ptrace. */
अटल पूर्णांक get_nr_wps(bool *arch_31)
अणु
	काष्ठा ppc_debug_info dbginfo;
	पूर्णांक child_pid;

	child_pid = विभाजन();
	अगर (!child_pid) अणु
		पूर्णांक ret = ptrace(PTRACE_TRACEME, 0, शून्य, 0);
		अगर (ret) अणु
			लिखो_त्रुटि("PTRACE_TRACEME failed\n");
			निकास(निकास_त्रुटि);
		पूर्ण
		समाप्त(getpid(), SIGUSR1);

		sleep(1);
		निकास(निकास_सफल);
	पूर्ण

	रुको(शून्य);
	अगर (ptrace(PPC_PTRACE_GETHWDBGINFO, child_pid, शून्य, &dbginfo)) अणु
		लिखो_त्रुटि("Can't get breakpoint info");
		निकास(निकास_त्रुटि);
	पूर्ण

	*arch_31 = !!(dbginfo.features & PPC_DEBUG_FEATURE_DATA_BP_ARCH_31);
	वापस dbginfo.num_data_bps;
पूर्ण

अटल पूर्णांक runtest(व्योम)
अणु
	पूर्णांक rwflag;
	पूर्णांक exclude_user;
	पूर्णांक ret;
	bool dawr = dawr_supported();
	bool arch_31 = false;
	पूर्णांक nr_wps = get_nr_wps(&arch_31);

	/*
	 * perf defines rwflag as two bits पढ़ो and ग_लिखो and at least
	 * one must be set.  So range 1-3.
	 */
	क्रम (rwflag = 1 ; rwflag < 4; rwflag++) अणु
		क्रम (exclude_user = 0 ; exclude_user < 2; exclude_user++) अणु
			ret = runtestsingle(rwflag, exclude_user, 0);
			अगर (ret)
				वापस ret;

			/* अगर we have the dawr, we can करो an array test */
			अगर (!dawr)
				जारी;
			ret = runtestsingle(rwflag, exclude_user, 1);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = runtest_dar_outside();
	अगर (ret)
		वापस ret;

	अगर (dawr && nr_wps > 1) अणु
		nprocs = get_nprocs();
		ret = runtest_multi_dawr();
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dawr && arch_31)
		ret = runtest_unaligned_512bytes();

	वापस ret;
पूर्ण


अटल पूर्णांक perf_hwअवरोध(व्योम)
अणु
	बेक्रम ( समय(शून्य) );

	SKIP_IF(!perf_अवरोधpoपूर्णांक_supported());

	वापस runtest();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[], अक्षर **envp)
अणु
	वापस test_harness(perf_hwअवरोध, "perf_hwbreak");
पूर्ण
