<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020, Gustavo Luiz Duarte, IBM Corp.
 *
 * This test starts a transaction and triggers a संकेत, क्रमcing a pagefault to
 * happen when the kernel संकेत handling code touches the user संकेत stack.
 *
 * In order to aव्योम pre-faulting the संकेत stack memory and to क्रमce the
 * pagefault to happen precisely in the kernel संकेत handling code, the
 * pagefault handling is करोne in userspace using the userfaultfd facility.
 *
 * Further pagefaults are triggered by crafting the संकेत handler's ucontext
 * to poपूर्णांक to additional memory regions managed by the userfaultfd, so using
 * the same mechanism used to aव्योम pre-faulting the संकेत stack memory.
 *
 * On failure (bug is present) kernel crashes or never वापसs control back to
 * userspace. If bug is not present, tests completes almost immediately.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/userfaultfd.h>
#समावेश <poll.h>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>

#समावेश "tm.h"


#घोषणा UF_MEM_SIZE 655360	/* 10 x 64k pages */

/* Memory handled by userfaultfd */
अटल अक्षर *uf_mem;
अटल माप_प्रकार uf_mem_offset = 0;

/*
 * Data that will be copied पूर्णांकo the faulting pages (instead of zero-filled
 * pages). This is used to make the test more reliable and aव्योम segfaulting
 * when we वापस from the संकेत handler. Since we are making the संकेत
 * handler's ucontext poपूर्णांक to newly allocated memory, when that memory is
 * paged-in it will contain the expected content.
 */
अटल अक्षर backing_mem[UF_MEM_SIZE];

अटल माप_प्रकार pagesize;

/*
 * Return a chunk of at least 'size' bytes of memory that will be handled by
 * userfaultfd. If 'backing_data' is not शून्य, its content will be save to
 * 'backing_mem' and then copied पूर्णांकo the faulting pages when the page fault
 * is handled.
 */
व्योम *get_uf_mem(माप_प्रकार size, व्योम *backing_data)
अणु
	व्योम *ret;

	अगर (uf_mem_offset + size > UF_MEM_SIZE) अणु
		ख_लिखो(मानक_त्रुटि, "Requesting more uf_mem than expected!\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = &uf_mem[uf_mem_offset];

	/* Save the data that will be copied पूर्णांकo the faulting page */
	अगर (backing_data != शून्य)
		स_नकल(&backing_mem[uf_mem_offset], backing_data, size);

	/* Reserve the requested amount of uf_mem */
	uf_mem_offset += size;
	/* Keep uf_mem_offset aligned to the page size (round up) */
	uf_mem_offset = (uf_mem_offset + pagesize - 1) & ~(pagesize - 1);

	वापस ret;
पूर्ण

व्योम *fault_handler_thपढ़ो(व्योम *arg)
अणु
	काष्ठा uffd_msg msg;	/* Data पढ़ो from userfaultfd */
	दीर्घ uffd;		/* userfaultfd file descriptor */
	काष्ठा uffdio_copy uffdio_copy;
	काष्ठा pollfd pollfd;
	sमाप_प्रकार nपढ़ो, offset;

	uffd = (दीर्घ) arg;

	क्रम (;;) अणु
		pollfd.fd = uffd;
		pollfd.events = POLLIN;
		अगर (poll(&pollfd, 1, -1) == -1) अणु
			लिखो_त्रुटि("poll() failed");
			निकास(निकास_त्रुटि);
		पूर्ण

		nपढ़ो = पढ़ो(uffd, &msg, माप(msg));
		अगर (nपढ़ो == 0) अणु
			ख_लिखो(मानक_त्रुटि, "read(): EOF on userfaultfd\n");
			निकास(निकास_त्रुटि);
		पूर्ण

		अगर (nपढ़ो == -1) अणु
			लिखो_त्रुटि("read() failed");
			निकास(निकास_त्रुटि);
		पूर्ण

		/* We expect only one kind of event */
		अगर (msg.event != UFFD_EVENT_PAGEFAULT) अणु
			ख_लिखो(मानक_त्रुटि, "Unexpected event on userfaultfd\n");
			निकास(निकास_त्रुटि);
		पूर्ण

		/*
		 * We need to handle page faults in units of pages(!).
		 * So, round faulting address करोwn to page boundary.
		 */
		uffdio_copy.dst = msg.arg.pagefault.address & ~(pagesize-1);

		offset = (अक्षर *) uffdio_copy.dst - uf_mem;
		uffdio_copy.src = (अचिन्हित दीर्घ) &backing_mem[offset];

		uffdio_copy.len = pagesize;
		uffdio_copy.mode = 0;
		uffdio_copy.copy = 0;
		अगर (ioctl(uffd, UFFDIO_COPY, &uffdio_copy) == -1) अणु
			लिखो_त्रुटि("ioctl-UFFDIO_COPY failed");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण
पूर्ण

व्योम setup_uf_mem(व्योम)
अणु
	दीर्घ uffd;		/* userfaultfd file descriptor */
	pthपढ़ो_t thr;
	काष्ठा uffdio_api uffdio_api;
	काष्ठा uffdio_रेजिस्टर uffdio_रेजिस्टर;
	पूर्णांक ret;

	pagesize = sysconf(_SC_PAGE_SIZE);

	/* Create and enable userfaultfd object */
	uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
	अगर (uffd == -1) अणु
		लिखो_त्रुटि("userfaultfd() failed");
		निकास(निकास_त्रुटि);
	पूर्ण
	uffdio_api.api = UFFD_API;
	uffdio_api.features = 0;
	अगर (ioctl(uffd, UFFDIO_API, &uffdio_api) == -1) अणु
		लिखो_त्रुटि("ioctl-UFFDIO_API failed");
		निकास(निकास_त्रुटि);
	पूर्ण

	/*
	 * Create a निजी anonymous mapping. The memory will be demand-zero
	 * paged, that is, not yet allocated. When we actually touch the memory
	 * the related page will be allocated via the userfaultfd mechanism.
	 */
	uf_mem = mmap(शून्य, UF_MEM_SIZE, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	अगर (uf_mem == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap() failed");
		निकास(निकास_त्रुटि);
	पूर्ण

	/*
	 * Register the memory range of the mapping we've just mapped to be
	 * handled by the userfaultfd object. In 'mode' we request to track
	 * missing pages (i.e. pages that have not yet been faulted-in).
	 */
	uffdio_रेजिस्टर.range.start = (अचिन्हित दीर्घ) uf_mem;
	uffdio_रेजिस्टर.range.len = UF_MEM_SIZE;
	uffdio_रेजिस्टर.mode = UFFDIO_REGISTER_MODE_MISSING;
	अगर (ioctl(uffd, UFFDIO_REGISTER, &uffdio_रेजिस्टर) == -1) अणु
		लिखो_त्रुटि("ioctl-UFFDIO_REGISTER");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Create a thपढ़ो that will process the userfaultfd events */
	ret = pthपढ़ो_create(&thr, शून्य, fault_handler_thपढ़ो, (व्योम *) uffd);
	अगर (ret != 0) अणु
		ख_लिखो(मानक_त्रुटि, "pthread_create(): Error. Returned %d\n", ret);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

/*
 * Assumption: the संकेत was delivered जबतक userspace was in transactional or
 * suspended state, i.e. uc->uc_link != शून्य.
 */
व्योम संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	ucontext_t *ucp = uc;

	/* Skip 'trap' after वापसing, otherwise we get a SIGTRAP again */
	ucp->uc_link->uc_mcontext.regs->nip += 4;

	ucp->uc_mcontext.v_regs =
		get_uf_mem(माप(elf_vrreg_t), ucp->uc_mcontext.v_regs);

	ucp->uc_link->uc_mcontext.v_regs =
		get_uf_mem(माप(elf_vrreg_t), ucp->uc_link->uc_mcontext.v_regs);

	ucp->uc_link = get_uf_mem(माप(ucontext_t), ucp->uc_link);
पूर्ण

bool have_userfaultfd(व्योम)
अणु
	दीर्घ rc;

	त्रुटि_सं = 0;
	rc = syscall(__NR_userfaultfd, -1);

	वापस rc == 0 || त्रुटि_सं != ENOSYS;
पूर्ण

पूर्णांक पंचांग_संकेत_pagefault(व्योम)
अणु
	काष्ठा sigaction sa;
	stack_t ss;

	SKIP_IF(!have_hपंचांग());
	SKIP_IF(!have_userfaultfd());

	setup_uf_mem();

	/*
	 * Set an alternative stack that will generate a page fault when the
	 * संकेत is उठाओd. The page fault will be treated via userfaultfd,
	 * i.e. via fault_handler_thपढ़ो.
	 */
	ss.ss_sp = get_uf_mem(SIGSTKSZ, शून्य);
	ss.ss_size = SIGSTKSZ;
	ss.ss_flags = 0;
	अगर (sigaltstack(&ss, शून्य) == -1) अणु
		लिखो_त्रुटि("sigaltstack() failed");
		निकास(निकास_त्रुटि);
	पूर्ण

	sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
	sa.sa_sigaction = संकेत_handler;
	अगर (sigaction(SIGTRAP, &sa, शून्य) == -1) अणु
		लिखो_त्रुटि("sigaction() failed");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* Trigger a SIGTRAP in transactional state */
	यंत्र __अस्थिर__(
			"tbegin.;"
			"beq    1f;"
			"trap;"
			"1: ;"
			: : : "memory");

	/* Trigger a SIGTRAP in suspended state */
	यंत्र __अस्थिर__(
			"tbegin.;"
			"beq    1f;"
			"tsuspend.;"
			"trap;"
			"tresume.;"
			"1: ;"
			: : : "memory");

	वापस निकास_सफल;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	/*
	 * Depending on kernel config, the TM Bad Thing might not result in a
	 * crash, instead the kernel never वापसs control back to userspace, so
	 * set a tight समयout. If the test passes it completes almost
	 * immediately.
	 */
	test_harness_set_समयout(2);
	वापस test_harness(पंचांग_संकेत_pagefault, "tm_signal_pagefault");
पूर्ण
