<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This test is पूर्णांकended to reproduce a crash that happens when
 * kvm_arch_hardware_disable is called and it attempts to unरेजिस्टर the user
 * वापस notअगरiers.
 */

#घोषणा _GNU_SOURCE

#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <semaphore.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/रुको.h>

#समावेश <test_util.h>

#समावेश "kvm_util.h"

#घोषणा VCPU_NUM 4
#घोषणा SLEEPING_THREAD_NUM (1 << 4)
#घोषणा FORK_NUM (1ULL << 9)
#घोषणा DELAY_US_MAX 2000
#घोषणा GUEST_CODE_PIO_PORT 4

sem_t *sem;

/* Arguments क्रम the pthपढ़ोs */
काष्ठा payload अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक32_t index;
पूर्ण;

अटल व्योम guest_code(व्योम)
अणु
	क्रम (;;)
		;  /* Some busy work */
	म_लिखो("Should not be reached.\n");
पूर्ण

अटल व्योम *run_vcpu(व्योम *arg)
अणु
	काष्ठा payload *payload = (काष्ठा payload *)arg;
	काष्ठा kvm_run *state = vcpu_state(payload->vm, payload->index);

	vcpu_run(payload->vm, payload->index);

	TEST_ASSERT(false, "%s: exited with reason %d: %s\n",
		    __func__, state->निकास_reason,
		    निकास_reason_str(state->निकास_reason));
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल व्योम *sleeping_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक fd;

	जबतक (true) अणु
		fd = खोलो("/dev/null", O_RDWR);
		बंद(fd);
	पूर्ण
	TEST_ASSERT(false, "%s: exited\n", __func__);
	pthपढ़ो_निकास(शून्य);
पूर्ण

अटल अंतरभूत व्योम check_create_thपढ़ो(pthपढ़ो_t *thपढ़ो, pthपढ़ो_attr_t *attr,
				       व्योम *(*f)(व्योम *), व्योम *arg)
अणु
	पूर्णांक r;

	r = pthपढ़ो_create(thपढ़ो, attr, f, arg);
	TEST_ASSERT(r == 0, "%s: failed to create thread", __func__);
पूर्ण

अटल अंतरभूत व्योम check_set_affinity(pthपढ़ो_t thपढ़ो, cpu_set_t *cpu_set)
अणु
	पूर्णांक r;

	r = pthपढ़ो_setaffinity_np(thपढ़ो, माप(cpu_set_t), cpu_set);
	TEST_ASSERT(r == 0, "%s: failed set affinity", __func__);
पूर्ण

अटल अंतरभूत व्योम check_join(pthपढ़ो_t thपढ़ो, व्योम **retval)
अणु
	पूर्णांक r;

	r = pthपढ़ो_join(thपढ़ो, retval);
	TEST_ASSERT(r == 0, "%s: failed to join thread", __func__);
पूर्ण

अटल व्योम run_test(uपूर्णांक32_t run)
अणु
	काष्ठा kvm_vm *vm;
	cpu_set_t cpu_set;
	pthपढ़ो_t thपढ़ोs[VCPU_NUM];
	pthपढ़ो_t throw_away;
	काष्ठा payload payloads[VCPU_NUM];
	व्योम *b;
	uपूर्णांक32_t i, j;

	CPU_ZERO(&cpu_set);
	क्रम (i = 0; i < VCPU_NUM; i++)
		CPU_SET(i, &cpu_set);

	vm = vm_create(VM_MODE_DEFAULT, DEFAULT_GUEST_PHY_PAGES, O_RDWR);
	kvm_vm_elf_load(vm, program_invocation_name, 0, 0);
	vm_create_irqchip(vm);

	pr_debug("%s: [%d] start vcpus\n", __func__, run);
	क्रम (i = 0; i < VCPU_NUM; ++i) अणु
		vm_vcpu_add_शेष(vm, i, guest_code);
		payloads[i].vm = vm;
		payloads[i].index = i;

		check_create_thपढ़ो(&thपढ़ोs[i], शून्य, run_vcpu,
				    (व्योम *)&payloads[i]);
		check_set_affinity(thपढ़ोs[i], &cpu_set);

		क्रम (j = 0; j < SLEEPING_THREAD_NUM; ++j) अणु
			check_create_thपढ़ो(&throw_away, शून्य, sleeping_thपढ़ो,
					    (व्योम *)शून्य);
			check_set_affinity(throw_away, &cpu_set);
		पूर्ण
	पूर्ण
	pr_debug("%s: [%d] all threads launched\n", __func__, run);
	sem_post(sem);
	क्रम (i = 0; i < VCPU_NUM; ++i)
		check_join(thपढ़ोs[i], &b);
	/* Should not be reached */
	TEST_ASSERT(false, "%s: [%d] child escaped the ninja\n", __func__, run);
पूर्ण

व्योम रुको_क्रम_child_setup(pid_t pid)
अणु
	/*
	 * Wait क्रम the child to post to the semaphore, but wake up periodically
	 * to check अगर the child निकासed prematurely.
	 */
	क्रम (;;) अणु
		स्थिर काष्ठा बारpec रुको_period = अणु .tv_sec = 1 पूर्ण;
		पूर्णांक status;

		अगर (!sem_समयdरुको(sem, &रुको_period))
			वापस;

		/* Child is still running, keep रुकोing. */
		अगर (pid != रुकोpid(pid, &status, WNOHANG))
			जारी;

		/*
		 * Child is no दीर्घer running, which is not expected.
		 *
		 * If it निकासed with a non-zero status, we explicitly क्रमward
		 * the child's status in हाल it निकासed with KSFT_SKIP.
		 */
		अगर (WIFEXITED(status))
			निकास(WEXITSTATUS(status));
		अन्यथा
			TEST_ASSERT(false, "Child exited unexpectedly");
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	uपूर्णांक32_t i;
	पूर्णांक s, r;
	pid_t pid;

	sem = sem_खोलो("vm_sem", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("vm_sem");

	क्रम (i = 0; i < FORK_NUM; ++i) अणु
		pid = विभाजन();
		TEST_ASSERT(pid >= 0, "%s: unable to fork", __func__);
		अगर (pid == 0)
			run_test(i); /* This function always निकासs */

		pr_debug("%s: [%d] waiting semaphore\n", __func__, i);
		रुको_क्रम_child_setup(pid);
		r = (अक्रम() % DELAY_US_MAX) + 1;
		pr_debug("%s: [%d] waiting %dus\n", __func__, i, r);
		usleep(r);
		r = रुकोpid(pid, &s, WNOHANG);
		TEST_ASSERT(r != pid,
			    "%s: [%d] child exited unexpectedly status: [%d]",
			    __func__, i, s);
		pr_debug("%s: [%d] killing child\n", __func__, i);
		समाप्त(pid, SIGKILL);
	पूर्ण

	sem_destroy(sem);
	निकास(0);
पूर्ण
