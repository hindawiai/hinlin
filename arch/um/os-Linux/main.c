<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <sys/resource.h>
#समावेश <as-layout.h>
#समावेश <init.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <um_दो_स्मृति.h>

#घोषणा PGD_BOUND (4 * 1024 * 1024)
#घोषणा STACKSIZE (8 * 1024 * 1024)
#घोषणा THREAD_NAME_LEN (256)

दीर्घ elf_aux_hwcap;

अटल व्योम set_stklim(व्योम)
अणु
	काष्ठा rlimit lim;

	अगर (getrlimit(RLIMIT_STACK, &lim) < 0) अणु
		लिखो_त्रुटि("getrlimit");
		निकास(1);
	पूर्ण
	अगर ((lim.rlim_cur == RLIM_अनन्त) || (lim.rlim_cur > STACKSIZE)) अणु
		lim.rlim_cur = STACKSIZE;
		अगर (setrlimit(RLIMIT_STACK, &lim) < 0) अणु
			लिखो_त्रुटि("setrlimit");
			निकास(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम last_ditch_निकास(पूर्णांक sig)
अणु
	uml_cleanup();
	निकास(1);
पूर्ण

अटल व्योम install_fatal_handler(पूर्णांक sig)
अणु
	काष्ठा sigaction action;

	/* All संकेतs are enabled in this handler ... */
	sigemptyset(&action.sa_mask);

	/*
	 * ... including the संकेत being handled, plus we want the
	 * handler reset to the शेष behavior, so that अगर an निकास
	 * handler is hanging क्रम some reason, the UML will just die
	 * after this संकेत is sent a second समय.
	 */
	action.sa_flags = SA_RESETHAND | SA_NODEFER;
	action.sa_restorer = शून्य;
	action.sa_handler = last_ditch_निकास;
	अगर (sigaction(sig, &action, शून्य) < 0) अणु
		os_warn("failed to install handler for signal %d "
			"- errno = %d\n", sig, त्रुटि_सं);
		निकास(1);
	पूर्ण
पूर्ण

#घोषणा UML_LIB_PATH	":" OS_LIB_PATH "/uml"

अटल व्योम setup_env_path(व्योम)
अणु
	अक्षर *new_path = शून्य;
	अक्षर *old_path = शून्य;
	पूर्णांक path_len = 0;

	old_path = दो_पर्या("PATH");
	/*
	 * अगर no PATH variable is set or it has an empty value
	 * just use the शेष + /usr/lib/uml
	 */
	अगर (!old_path || (path_len = म_माप(old_path)) == 0) अणु
		अगर (putenv("PATH=:/bin:/usr/bin/" UML_LIB_PATH))
			लिखो_त्रुटि("couldn't putenv");
		वापस;
	पूर्ण

	/* append /usr/lib/uml to the existing path */
	path_len += म_माप("PATH=" UML_LIB_PATH) + 1;
	new_path = दो_स्मृति(path_len);
	अगर (!new_path) अणु
		लिखो_त्रुटि("couldn't malloc to set a new PATH");
		वापस;
	पूर्ण
	snम_लिखो(new_path, path_len, "PATH=%s" UML_LIB_PATH, old_path);
	अगर (putenv(new_path)) अणु
		लिखो_त्रुटि("couldn't putenv to set a new PATH");
		मुक्त(new_path);
	पूर्ण
पूर्ण

बाह्य व्योम scan_elf_aux( अक्षर **envp);

पूर्णांक __init मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	अक्षर **new_argv;
	पूर्णांक ret, i, err;

	set_stklim();

	setup_env_path();

	setsid();

	new_argv = दो_स्मृति((argc + 1) * माप(अक्षर *));
	अगर (new_argv == शून्य) अणु
		लिखो_त्रुटि("Mallocing argv");
		निकास(1);
	पूर्ण
	क्रम (i = 0; i < argc; i++) अणु
		new_argv[i] = strdup(argv[i]);
		अगर (new_argv[i] == शून्य) अणु
			लिखो_त्रुटि("Mallocing an arg");
			निकास(1);
		पूर्ण
	पूर्ण
	new_argv[argc] = शून्य;

	/*
	 * Allow these संकेतs to bring करोwn a UML अगर all other
	 * methods of control fail.
	 */
	install_fatal_handler(संक_विघ्न);
	install_fatal_handler(संक_इति);

#अगर_घोषित CONFIG_ARCH_REUSE_HOST_VSYSCALL_AREA
	scan_elf_aux(envp);
#पूर्ण_अगर

	change_sig(SIGPIPE, 0);
	ret = linux_मुख्य(argc, argv);

	/*
	 * Disable SIGPROF - I have no idea why libc करोesn't करो this or turn
	 * off the profiling समय, but UML dies with a SIGPROF just beक्रमe
	 * निकासing when profiling is active.
	 */
	change_sig(SIGPROF, 0);

	/*
	 * This संकेत stuff used to be in the reboot हाल.  However,
	 * someबार a समयr संकेत can come in when we're halting (reproducably
	 * when writing out gcov inक्रमmation, presumably because that takes
	 * some समय) and cause a segfault.
	 */

	/* stop समयrs and set समयr संकेत to be ignored */
	os_समयr_disable();

	/* disable SIGIO क्रम the fds and set SIGIO to be ignored */
	err = deactivate_all_fds();
	अगर (err)
		os_warn("deactivate_all_fds failed, errno = %d\n", -err);

	/*
	 * Let any pending संकेतs fire now.  This ensures
	 * that they won't be delivered after the exec, when
	 * they are definitely not expected.
	 */
	unblock_संकेतs();

	os_info("\n");
	/* Reboot */
	अगर (ret) अणु
		execvp(new_argv[0], new_argv);
		लिखो_त्रुटि("Failed to exec kernel");
		ret = 1;
	पूर्ण
	वापस uml_निकासcode;
पूर्ण

बाह्य व्योम *__real_दो_स्मृति(पूर्णांक);

व्योम *__wrap_दो_स्मृति(पूर्णांक size)
अणु
	व्योम *ret;

	अगर (!kदो_स्मृति_ok)
		वापस __real_दो_स्मृति(size);
	अन्यथा अगर (size <= UM_KERN_PAGE_SIZE)
		/* finding contiguous pages can be hard*/
		ret = uml_kदो_स्मृति(size, UM_GFP_KERNEL);
	अन्यथा ret = vदो_स्मृति(size);

	/*
	 * glibc people insist that अगर दो_स्मृति fails, त्रुटि_सं should be
	 * set by दो_स्मृति as well. So we करो.
	 */
	अगर (ret == शून्य)
		त्रुटि_सं = ENOMEM;

	वापस ret;
पूर्ण

व्योम *__wrap_सुस्मृति(पूर्णांक n, पूर्णांक size)
अणु
	व्योम *ptr = __wrap_दो_स्मृति(n * size);

	अगर (ptr == शून्य)
		वापस शून्य;
	स_रखो(ptr, 0, n * size);
	वापस ptr;
पूर्ण

बाह्य व्योम __real_मुक्त(व्योम *);

बाह्य अचिन्हित दीर्घ high_physmem;

व्योम __wrap_मुक्त(व्योम *ptr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) ptr;

	/*
	 * We need to know how the allocation happened, so it can be correctly
	 * मुक्तd.  This is करोne by seeing what region of memory the poपूर्णांकer is
	 * in -
	 * 	physical memory - kदो_स्मृति/kमुक्त
	 *	kernel भव memory - vदो_स्मृति/vमुक्त
	 * 	anywhere अन्यथा - दो_स्मृति/मुक्त
	 * If kदो_स्मृति is not yet possible, then either high_physmem and/or
	 * end_vm are still 0 (as at startup), in which हाल we call मुक्त, or
	 * we have set them, but anyway addr has not been allocated from those
	 * areas. So, in both हालs __real_मुक्त is called.
	 *
	 * CAN_KMALLOC is checked because it would be bad to मुक्त a buffer
	 * with kदो_स्मृति/vदो_स्मृति after they have been turned off during
	 * shutकरोwn.
	 * XXX: However, we someबार shutकरोwn CAN_KMALLOC temporarily, so
	 * there is a possibility क्रम memory leaks.
	 */

	अगर ((addr >= uml_physmem) && (addr < high_physmem)) अणु
		अगर (kदो_स्मृति_ok)
			kमुक्त(ptr);
	पूर्ण
	अन्यथा अगर ((addr >= start_vm) && (addr < end_vm)) अणु
		अगर (kदो_स्मृति_ok)
			vमुक्त(ptr);
	पूर्ण
	अन्यथा __real_मुक्त(ptr);
पूर्ण
