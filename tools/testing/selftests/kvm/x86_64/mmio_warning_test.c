<शैली गुरु>
/*
 * mmio_warning_test
 *
 * Copyright (C) 2019, Google LLC.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 * Test that we करोn't get a kernel warning when we call KVM_RUN after a
 * triple fault occurs.  To get the triple fault to occur we call KVM_RUN
 * on a VCPU that hasn't been properly setup.
 *
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <kvm_util.h>
#समावेश <linux/kvm.h>
#समावेश <processor.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <test_util.h>
#समावेश <unistd.h>

#घोषणा NTHREAD 4
#घोषणा NPROCESS 5

काष्ठा thपढ़ो_context अणु
	पूर्णांक kvmcpu;
	काष्ठा kvm_run *run;
पूर्ण;

व्योम *thr(व्योम *arg)
अणु
	काष्ठा thपढ़ो_context *tc = (काष्ठा thपढ़ो_context *)arg;
	पूर्णांक res;
	पूर्णांक kvmcpu = tc->kvmcpu;
	काष्ठा kvm_run *run = tc->run;

	res = ioctl(kvmcpu, KVM_RUN, 0);
	pr_info("ret1=%d exit_reason=%d suberror=%d\n",
		res, run->निकास_reason, run->पूर्णांकernal.suberror);

	वापस 0;
पूर्ण

व्योम test(व्योम)
अणु
	पूर्णांक i, kvm, kvmvm, kvmcpu;
	pthपढ़ो_t th[NTHREAD];
	काष्ठा kvm_run *run;
	काष्ठा thपढ़ो_context tc;

	kvm = खोलो("/dev/kvm", O_RDWR);
	TEST_ASSERT(kvm != -1, "failed to open /dev/kvm");
	kvmvm = ioctl(kvm, KVM_CREATE_VM, 0);
	TEST_ASSERT(kvmvm != -1, "KVM_CREATE_VM failed");
	kvmcpu = ioctl(kvmvm, KVM_CREATE_VCPU, 0);
	TEST_ASSERT(kvmcpu != -1, "KVM_CREATE_VCPU failed");
	run = (काष्ठा kvm_run *)mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,
				    kvmcpu, 0);
	tc.kvmcpu = kvmcpu;
	tc.run = run;
	बेक्रम(getpid());
	क्रम (i = 0; i < NTHREAD; i++) अणु
		pthपढ़ो_create(&th[i], शून्य, thr, (व्योम *)(uपूर्णांकptr_t)&tc);
		usleep(अक्रम() % 10000);
	पूर्ण
	क्रम (i = 0; i < NTHREAD; i++)
		pthपढ़ो_join(th[i], शून्य);
पूर्ण

पूर्णांक get_warnings_count(व्योम)
अणु
	पूर्णांक warnings;
	खाता *f;

	f = pखोलो("dmesg | grep \"WARNING:\" | wc -l", "r");
	ख_पूछो(f, "%d", &warnings);
	ख_बंद(f);

	वापस warnings;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक warnings_beक्रमe, warnings_after;

	अगर (!is_पूर्णांकel_cpu()) अणु
		prपूर्णांक_skip("Must be run on an Intel CPU");
		निकास(KSFT_SKIP);
	पूर्ण

	अगर (vm_is_unrestricted_guest(शून्य)) अणु
		prपूर्णांक_skip("Unrestricted guest must be disabled");
		निकास(KSFT_SKIP);
	पूर्ण

	warnings_beक्रमe = get_warnings_count();

	क्रम (पूर्णांक i = 0; i < NPROCESS; ++i) अणु
		पूर्णांक status;
		पूर्णांक pid = विभाजन();

		अगर (pid < 0)
			निकास(1);
		अगर (pid == 0) अणु
			test();
			निकास(0);
		पूर्ण
		जबतक (रुकोpid(pid, &status, __WALL) != pid)
			;
	पूर्ण

	warnings_after = get_warnings_count();
	TEST_ASSERT(warnings_beक्रमe == warnings_after,
		   "Warnings found in kernel.  Run 'dmesg' to inspect them.");

	वापस 0;
पूर्ण
