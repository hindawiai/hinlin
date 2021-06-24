<शैली गुरु>
/*
 * Copyright IBM Corp.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/syscall.h>
#समावेश <ucontext.h>
#समावेश <unistd.h>

#समावेश "utils.h"

अक्षर *file_name;

पूर्णांक in_test;
अस्थिर पूर्णांक faulted;
अस्थिर व्योम *dar;
पूर्णांक errors;

अटल व्योम segv(पूर्णांक signum, siginfo_t *info, व्योम *ctxt_v)
अणु
	ucontext_t *ctxt = (ucontext_t *)ctxt_v;
	काष्ठा pt_regs *regs = ctxt->uc_mcontext.regs;

	अगर (!in_test) अणु
		ख_लिखो(मानक_त्रुटि, "Segfault outside of test !\n");
		निकास(1);
	पूर्ण

	faulted = 1;
	dar = (व्योम *)regs->dar;
	regs->nip += 4;
पूर्ण

अटल अंतरभूत व्योम करो_पढ़ो(स्थिर अस्थिर व्योम *addr)
अणु
	पूर्णांक ret;

	यंत्र अस्थिर("lwz %0,0(%1); twi 0,%0,0; isync;\n"
		     : "=r" (ret) : "r" (addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम करो_ग_लिखो(स्थिर अस्थिर व्योम *addr)
अणु
	पूर्णांक val = 0x1234567;

	यंत्र अस्थिर("stw %0,0(%1); sync; \n"
		     : : "r" (val), "r" (addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम check_faulted(व्योम *addr, दीर्घ page, दीर्घ subpage, पूर्णांक ग_लिखो)
अणु
	पूर्णांक want_fault = (subpage == ((page + 3) % 16));

	अगर (ग_लिखो)
		want_fault |= (subpage == ((page + 1) % 16));

	अगर (faulted != want_fault) अणु
		म_लिखो("Failed at %p (p=%ld,sp=%ld,w=%d), want=%s, got=%s !\n",
		       addr, page, subpage, ग_लिखो,
		       want_fault ? "fault" : "pass",
		       faulted ? "fault" : "pass");
		++errors;
	पूर्ण

	अगर (faulted) अणु
		अगर (dar != addr) अणु
			म_लिखो("Fault expected at %p and happened at %p !\n",
			       addr, dar);
		पूर्ण
		faulted = 0;
		यंत्र अस्थिर("sync" : : : "memory");
	पूर्ण
पूर्ण

अटल पूर्णांक run_test(व्योम *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक *map;
	दीर्घ i, j, pages, err;

	pages = size / 0x10000;
	map = दो_स्मृति(pages * 4);
	निश्चित(map);

	/*
	 * क्रम each page, mark subpage i % 16 पढ़ो only and subpage
	 * (i + 3) % 16 inaccessible
	 */
	क्रम (i = 0; i < pages; i++) अणु
		map[i] = (0x40000000 >> (((i + 1) * 2) % 32)) |
			(0xc0000000 >> (((i + 3) * 2) % 32));
	पूर्ण

	err = syscall(__NR_subpage_prot, addr, size, map);
	अगर (err) अणु
		लिखो_त्रुटि("subpage_perm");
		वापस 1;
	पूर्ण
	मुक्त(map);

	in_test = 1;
	errors = 0;
	क्रम (i = 0; i < pages; i++) अणु
		क्रम (j = 0; j < 16; j++, addr += 0x1000) अणु
			करो_पढ़ो(addr);
			check_faulted(addr, i, j, 0);
			करो_ग_लिखो(addr);
			check_faulted(addr, i, j, 1);
		पूर्ण
	पूर्ण

	in_test = 0;
	अगर (errors) अणु
		म_लिखो("%d errors detected\n", errors);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक syscall_available(व्योम)
अणु
	पूर्णांक rc;

	त्रुटि_सं = 0;
	rc = syscall(__NR_subpage_prot, 0, 0, 0);

	वापस rc == 0 || (त्रुटि_सं != ENOENT && त्रुटि_सं != ENOSYS);
पूर्ण

पूर्णांक test_anon(व्योम)
अणु
	अचिन्हित दीर्घ align;
	काष्ठा sigaction act = अणु
		.sa_sigaction = segv,
		.sa_flags = SA_SIGINFO
	पूर्ण;
	व्योम *दो_स्मृतिblock;
	अचिन्हित दीर्घ दो_स्मृतिsize;

	SKIP_IF(!syscall_available());

	अगर (getpagesize() != 0x10000) अणु
		ख_लिखो(मानक_त्रुटि, "Kernel page size must be 64K!\n");
		वापस 1;
	पूर्ण

	sigaction(संक_अंश, &act, शून्य);

	दो_स्मृतिsize = 4 * 16 * 1024 * 1024;

	FAIL_IF(posix_memalign(&दो_स्मृतिblock, 64 * 1024, दो_स्मृतिsize));

	align = (अचिन्हित दीर्घ)दो_स्मृतिblock;
	अगर (align & 0xffff)
		align = (align | 0xffff) + 1;

	दो_स्मृतिblock = (व्योम *)align;

	म_लिखो("allocated malloc block of 0x%lx bytes at %p\n",
	       दो_स्मृतिsize, दो_स्मृतिblock);

	म_लिखो("testing malloc block...\n");

	वापस run_test(दो_स्मृतिblock, दो_स्मृतिsize);
पूर्ण

पूर्णांक test_file(व्योम)
अणु
	काष्ठा sigaction act = अणु
		.sa_sigaction = segv,
		.sa_flags = SA_SIGINFO
	पूर्ण;
	व्योम *fileblock;
	off_t filesize;
	पूर्णांक fd;

	SKIP_IF(!syscall_available());

	fd = खोलो(file_name, O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("failed to open file");
		वापस 1;
	पूर्ण
	sigaction(संक_अंश, &act, शून्य);

	filesize = lseek(fd, 0, अंत_से);
	अगर (filesize & 0xffff)
		filesize &= ~0xfffful;

	fileblock = mmap(शून्य, filesize, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fd, 0);
	अगर (fileblock == MAP_FAILED) अणु
		लिखो_त्रुटि("failed to map file");
		वापस 1;
	पूर्ण
	म_लिखो("allocated %s for 0x%lx bytes at %p\n",
	       file_name, filesize, fileblock);

	म_लिखो("testing file map...\n");

	वापस run_test(fileblock, filesize);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक rc;

	rc = test_harness(test_anon, "subpage_prot_anon");
	अगर (rc)
		वापस rc;

	अगर (argc > 1)
		file_name = argv[1];
	अन्यथा
		file_name = "tempfile";

	वापस test_harness(test_file, "subpage_prot_file");
पूर्ण
