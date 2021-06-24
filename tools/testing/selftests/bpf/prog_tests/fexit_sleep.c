<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <test_progs.h>
#समावेश <समय.स>
#समावेश <sys/mman.h>
#समावेश <sys/syscall.h>
#समावेश "fexit_sleep.skel.h"

अटल पूर्णांक करो_sleep(व्योम *skel)
अणु
	काष्ठा fनिकास_sleep *fनिकास_skel = skel;
	काष्ठा बारpec ts1 = अणु .tv_nsec = 1 पूर्ण;
	काष्ठा बारpec ts2 = अणु .tv_sec = 10 पूर्ण;

	fनिकास_skel->bss->pid = getpid();
	(व्योम)syscall(__NR_nanosleep, &ts1, शून्य);
	(व्योम)syscall(__NR_nanosleep, &ts2, शून्य);
	वापस 0;
पूर्ण

#घोषणा STACK_SIZE (1024 * 1024)
अटल अक्षर child_stack[STACK_SIZE];

व्योम test_fनिकास_sleep(व्योम)
अणु
	काष्ठा fनिकास_sleep *fनिकास_skel = शून्य;
	पूर्णांक wstatus, duration = 0;
	pid_t cpid;
	पूर्णांक err, fनिकास_cnt;

	fनिकास_skel = fनिकास_sleep__खोलो_and_load();
	अगर (CHECK(!fनिकास_skel, "fexit_skel_load", "fexit skeleton failed\n"))
		जाओ cleanup;

	err = fनिकास_sleep__attach(fनिकास_skel);
	अगर (CHECK(err, "fexit_attach", "fexit attach failed: %d\n", err))
		जाओ cleanup;

	cpid = clone(करो_sleep, child_stack + STACK_SIZE, CLONE_खाताS | SIGCHLD, fनिकास_skel);
	अगर (CHECK(cpid == -1, "clone", "%s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ cleanup;

	/* रुको until first sys_nanosleep ends and second sys_nanosleep starts */
	जबतक (READ_ONCE(fनिकास_skel->bss->fentry_cnt) != 2);
	fनिकास_cnt = READ_ONCE(fनिकास_skel->bss->fनिकास_cnt);
	अगर (CHECK(fनिकास_cnt != 1, "fexit_cnt", "%d", fनिकास_cnt))
		जाओ cleanup;

	/* बंद progs and detach them. That will trigger two nop5->jmp5 reग_लिखोs
	 * in the trampolines to skip nanosleep_fनिकास prog.
	 * The nanosleep_fentry prog will get detached first.
	 * The nanosleep_fनिकास prog will get detached second.
	 * Detaching will trigger मुक्तing of both progs JITed images.
	 * There will be two dying bpf_tramp_image-s, but only the initial
	 * bpf_tramp_image (with both _fentry and _fनिकास progs will be stuck
	 * रुकोing क्रम percpu_ref_समाप्त to confirm). The other one
	 * will be मुक्तd quickly.
	 */
	बंद(bpf_program__fd(fनिकास_skel->progs.nanosleep_fentry));
	बंद(bpf_program__fd(fनिकास_skel->progs.nanosleep_fनिकास));
	fनिकास_sleep__detach(fनिकास_skel);

	/* समाप्त the thपढ़ो to unwind sys_nanosleep stack through the trampoline */
	समाप्त(cpid, 9);

	अगर (CHECK(रुकोpid(cpid, &wstatus, 0) == -1, "waitpid", "%s\n", म_त्रुटि(त्रुटि_सं)))
		जाओ cleanup;
	अगर (CHECK(WEXITSTATUS(wstatus) != 0, "exitstatus", "failed"))
		जाओ cleanup;

	/* The bypassed nanosleep_fनिकास prog shouldn't have executed.
	 * Unlike progs the maps were not मुक्तd and directly accessible.
	 */
	fनिकास_cnt = READ_ONCE(fनिकास_skel->bss->fनिकास_cnt);
	अगर (CHECK(fनिकास_cnt != 1, "fexit_cnt", "%d", fनिकास_cnt))
		जाओ cleanup;

cleanup:
	fनिकास_sleep__destroy(fनिकास_skel);
पूर्ण
