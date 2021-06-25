<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <यंत्र/unistd.h>
#समावेश <init.h>
#समावेश <os.h>
#समावेश <mem_user.h>
#समावेश <ptrace_user.h>
#समावेश <रेजिस्टरs.h>
#समावेश <skas.h>

अटल व्योम ptrace_child(व्योम)
अणु
	पूर्णांक ret;
	/* Calling os_getpid because some libcs cached getpid incorrectly */
	पूर्णांक pid = os_getpid(), ppid = getppid();
	पूर्णांक sc_result;

	अगर (change_sig(SIGWINCH, 0) < 0 ||
	    ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) अणु
		लिखो_त्रुटि("ptrace");
		समाप्त(pid, SIGKILL);
	पूर्ण
	समाप्त(pid, SIGSTOP);

	/*
	 * This syscall will be पूर्णांकercepted by the parent. Don't call more than
	 * once, please.
	 */
	sc_result = os_getpid();

	अगर (sc_result == pid)
		/* Nothing modअगरied by the parent, we are running normally. */
		ret = 1;
	अन्यथा अगर (sc_result == ppid)
		/*
		 * Expected in check_ptrace and check_sysemu when they succeed
		 * in modअगरying the stack frame
		 */
		ret = 0;
	अन्यथा
		/* Serious trouble! This could be caused by a bug in host 2.6
		 * SKAS3/2.6 patch beक्रमe release -V6, together with a bug in
		 * the UML code itself.
		 */
		ret = 2;

	निकास(ret);
पूर्ण

अटल व्योम fatal_लिखो_त्रुटि(स्थिर अक्षर *str)
अणु
	लिखो_त्रुटि(str);
	निकास(1);
पूर्ण

अटल व्योम fatal(अक्षर *fmt, ...)
अणु
	बहु_सूची list;

	बहु_शुरू(list, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, list);
	बहु_पूर्ण(list);

	निकास(1);
पूर्ण

अटल व्योम non_fatal(अक्षर *fmt, ...)
अणु
	बहु_सूची list;

	बहु_शुरू(list, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, list);
	बहु_पूर्ण(list);
पूर्ण

अटल पूर्णांक start_ptraced_child(व्योम)
अणु
	पूर्णांक pid, n, status;

	ख_साफ(मानक_निकास);

	pid = विभाजन();
	अगर (pid == 0)
		ptrace_child();
	अन्यथा अगर (pid < 0)
		fatal_लिखो_त्रुटि("start_ptraced_child : fork failed");

	CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED));
	अगर (n < 0)
		fatal_लिखो_त्रुटि("check_ptrace : waitpid failed");
	अगर (!WIFSTOPPED(status) || (WSTOPSIG(status) != SIGSTOP))
		fatal("check_ptrace : expected SIGSTOP, got status = %d",
		      status);

	वापस pid;
पूर्ण

/* When testing क्रम SYSEMU support, अगर it is one of the broken versions, we
 * must just aव्योम using sysemu, not panic, but only अगर SYSEMU features are
 * broken.
 * So only क्रम SYSEMU features we test mustpanic, जबतक normal host features
 * must work anyway!
 */
अटल पूर्णांक stop_ptraced_child(पूर्णांक pid, पूर्णांक निकासcode, पूर्णांक mustनिकास)
अणु
	पूर्णांक status, n, ret = 0;

	अगर (ptrace(PTRACE_CONT, pid, 0, 0) < 0) अणु
		लिखो_त्रुटि("stop_ptraced_child : ptrace failed");
		वापस -1;
	पूर्ण
	CATCH_EINTR(n = रुकोpid(pid, &status, 0));
	अगर (!WIFEXITED(status) || (WEXITSTATUS(status) != निकासcode)) अणु
		पूर्णांक निकास_with = WEXITSTATUS(status);
		अगर (निकास_with == 2)
			non_fatal("check_ptrace : child exited with status 2. "
				  "\nDisabling SYSEMU support.\n");
		non_fatal("check_ptrace : child exited with exitcode %d, while "
			  "expecting %d; status 0x%x\n", निकास_with,
			  निकासcode, status);
		अगर (mustनिकास)
			निकास(1);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

/* Changed only during early boot */
अटल पूर्णांक क्रमce_sysemu_disabled = 0;

अटल पूर्णांक __init nosysemu_cmd_param(अक्षर *str, पूर्णांक* add)
अणु
	क्रमce_sysemu_disabled = 1;
	वापस 0;
पूर्ण

__uml_setup("nosysemu", nosysemu_cmd_param,
"nosysemu\n"
"    Turns off syscall emulation patch for ptrace (SYSEMU).\n"
"    SYSEMU is a performance-patch introduced by Laurent Vivier. It changes\n"
"    behaviour of ptrace() and helps reduce host context switch rates.\n"
"    To make it work, you need a kernel patch for your host, too.\n"
"    See http://perso.wanadoo.fr/laurent.vivier/UML/ for further \n"
"    information.\n\n");

अटल व्योम __init check_sysemu(व्योम)
अणु
	अचिन्हित दीर्घ regs[MAX_REG_NR];
	पूर्णांक pid, n, status, count=0;

	os_info("Checking syscall emulation patch for ptrace...");
	sysemu_supported = 0;
	pid = start_ptraced_child();

	अगर (ptrace(PTRACE_SYSEMU, pid, 0, 0) < 0)
		जाओ fail;

	CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED));
	अगर (n < 0)
		fatal_लिखो_त्रुटि("check_sysemu : wait failed");
	अगर (!WIFSTOPPED(status) || (WSTOPSIG(status) != SIGTRAP))
		fatal("check_sysemu : expected SIGTRAP, got status = %d\n",
		      status);

	अगर (ptrace(PTRACE_GETREGS, pid, 0, regs) < 0)
		fatal_लिखो_त्रुटि("check_sysemu : PTRACE_GETREGS failed");
	अगर (PT_SYSCALL_NR(regs) != __NR_getpid) अणु
		non_fatal("check_sysemu got system call number %d, "
			  "expected %d...", PT_SYSCALL_NR(regs), __NR_getpid);
		जाओ fail;
	पूर्ण

	n = ptrace(PTRACE_POKEUSER, pid, PT_SYSCALL_RET_OFFSET, os_getpid());
	अगर (n < 0) अणु
		non_fatal("check_sysemu : failed to modify system call "
			  "return");
		जाओ fail;
	पूर्ण

	अगर (stop_ptraced_child(pid, 0, 0) < 0)
		जाओ fail_stopped;

	sysemu_supported = 1;
	os_info("OK\n");
	set_using_sysemu(!क्रमce_sysemu_disabled);

	os_info("Checking advanced syscall emulation patch for ptrace...");
	pid = start_ptraced_child();

	अगर ((ptrace(PTRACE_OLDSETOPTIONS, pid, 0,
		   (व्योम *) PTRACE_O_TRACESYSGOOD) < 0))
		fatal_लिखो_त्रुटि("check_sysemu: PTRACE_OLDSETOPTIONS failed");

	जबतक (1) अणु
		count++;
		अगर (ptrace(PTRACE_SYSEMU_SINGLESTEP, pid, 0, 0) < 0)
			जाओ fail;
		CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED));
		अगर (n < 0)
			fatal_लिखो_त्रुटि("check_sysemu: wait failed");

		अगर (WIFSTOPPED(status) &&
		    (WSTOPSIG(status) == (SIGTRAP|0x80))) अणु
			अगर (!count) अणु
				non_fatal("check_sysemu: SYSEMU_SINGLESTEP "
					  "doesn't singlestep");
				जाओ fail;
			पूर्ण
			n = ptrace(PTRACE_POKEUSER, pid, PT_SYSCALL_RET_OFFSET,
				   os_getpid());
			अगर (n < 0)
				fatal_लिखो_त्रुटि("check_sysemu : failed to modify "
					     "system call return");
			अवरोध;
		पूर्ण
		अन्यथा अगर (WIFSTOPPED(status) && (WSTOPSIG(status) == SIGTRAP))
			count++;
		अन्यथा अणु
			non_fatal("check_sysemu: expected SIGTRAP or "
				  "(SIGTRAP | 0x80), got status = %d\n",
				  status);
			जाओ fail;
		पूर्ण
	पूर्ण
	अगर (stop_ptraced_child(pid, 0, 0) < 0)
		जाओ fail_stopped;

	sysemu_supported = 2;
	os_info("OK\n");

	अगर (!क्रमce_sysemu_disabled)
		set_using_sysemu(sysemu_supported);
	वापस;

fail:
	stop_ptraced_child(pid, 1, 0);
fail_stopped:
	non_fatal("missing\n");
पूर्ण

अटल व्योम __init check_ptrace(व्योम)
अणु
	पूर्णांक pid, syscall, n, status;

	os_info("Checking that ptrace can change system call numbers...");
	pid = start_ptraced_child();

	अगर ((ptrace(PTRACE_OLDSETOPTIONS, pid, 0,
		   (व्योम *) PTRACE_O_TRACESYSGOOD) < 0))
		fatal_लिखो_त्रुटि("check_ptrace: PTRACE_OLDSETOPTIONS failed");

	जबतक (1) अणु
		अगर (ptrace(PTRACE_SYSCALL, pid, 0, 0) < 0)
			fatal_लिखो_त्रुटि("check_ptrace : ptrace failed");

		CATCH_EINTR(n = रुकोpid(pid, &status, WUNTRACED));
		अगर (n < 0)
			fatal_लिखो_त्रुटि("check_ptrace : wait failed");

		अगर (!WIFSTOPPED(status) ||
		   (WSTOPSIG(status) != (SIGTRAP | 0x80)))
			fatal("check_ptrace : expected (SIGTRAP|0x80), "
			       "got status = %d", status);

		syscall = ptrace(PTRACE_PEEKUSER, pid, PT_SYSCALL_NR_OFFSET,
				 0);
		अगर (syscall == __NR_getpid) अणु
			n = ptrace(PTRACE_POKEUSER, pid, PT_SYSCALL_NR_OFFSET,
				   __NR_getppid);
			अगर (n < 0)
				fatal_लिखो_त्रुटि("check_ptrace : failed to modify "
					     "system call");
			अवरोध;
		पूर्ण
	पूर्ण
	stop_ptraced_child(pid, 0, 1);
	os_info("OK\n");
	check_sysemu();
पूर्ण

बाह्य व्योम check_पंचांगpexec(व्योम);

अटल व्योम __init check_coredump_limit(व्योम)
अणु
	काष्ठा rlimit lim;
	पूर्णांक err = getrlimit(RLIMIT_CORE, &lim);

	अगर (err) अणु
		लिखो_त्रुटि("Getting core dump limit");
		वापस;
	पूर्ण

	os_info("Core dump limits :\n\tsoft - ");
	अगर (lim.rlim_cur == RLIM_अनन्त)
		os_info("NONE\n");
	अन्यथा
		os_info("%llu\n", (अचिन्हित दीर्घ दीर्घ)lim.rlim_cur);

	os_info("\thard - ");
	अगर (lim.rlim_max == RLIM_अनन्त)
		os_info("NONE\n");
	अन्यथा
		os_info("%llu\n", (अचिन्हित दीर्घ दीर्घ)lim.rlim_max);
पूर्ण

व्योम __init os_early_checks(व्योम)
अणु
	पूर्णांक pid;

	/* Prपूर्णांक out the core dump limits early */
	check_coredump_limit();

	check_ptrace();

	/* Need to check this early because mmapping happens beक्रमe the
	 * kernel is running.
	 */
	check_पंचांगpexec();

	pid = start_ptraced_child();
	अगर (init_रेजिस्टरs(pid))
		fatal("Failed to initialize default registers");
	stop_ptraced_child(pid, 1, 1);
पूर्ण

पूर्णांक __init parse_iomem(अक्षर *str, पूर्णांक *add)
अणु
	काष्ठा iomem_region *new;
	काष्ठा stat64 buf;
	अक्षर *file, *driver;
	पूर्णांक fd, size;

	driver = str;
	file = म_अक्षर(str,',');
	अगर (file == शून्य) अणु
		os_warn("parse_iomem : failed to parse iomem\n");
		जाओ out;
	पूर्ण
	*file = '\0';
	file++;
	fd = खोलो(file, O_RDWR, 0);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("parse_iomem - Couldn't open io file");
		जाओ out;
	पूर्ण

	अगर (ख_स्थिति64(fd, &buf) < 0) अणु
		लिखो_त्रुटि("parse_iomem - cannot stat_fd file");
		जाओ out_बंद;
	पूर्ण

	new = दो_स्मृति(माप(*new));
	अगर (new == शून्य) अणु
		लिखो_त्रुटि("Couldn't allocate iomem_region struct");
		जाओ out_बंद;
	पूर्ण

	size = (buf.st_size + UM_KERN_PAGE_SIZE) & ~(UM_KERN_PAGE_SIZE - 1);

	*new = ((काष्ठा iomem_region) अणु .next		= iomem_regions,
					.driver		= driver,
					.fd		= fd,
					.size		= size,
					.phys		= 0,
					.virt		= 0 पूर्ण);
	iomem_regions = new;
	iomem_size += new->size + UM_KERN_PAGE_SIZE;

	वापस 0;
 out_बंद:
	बंद(fd);
 out:
	वापस 1;
पूर्ण
