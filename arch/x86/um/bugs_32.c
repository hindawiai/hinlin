<शैली गुरु>
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <संकेत.स>
#समावेश <kern_util.h>
#समावेश <दीर्घ_लाँघ.h>
#समावेश <sysdep/ptrace.h>
#समावेश <generated/यंत्र-offsets.h>

/* Set during early boot */
अटल पूर्णांक host_has_cmov = 1;
अटल लाँघ_बफ cmov_test_वापस;

अटल व्योम cmov_sigill_test_handler(पूर्णांक sig)
अणु
	host_has_cmov = 0;
	दीर्घ_लाँघ(cmov_test_वापस, 1);
पूर्ण

व्योम arch_check_bugs(व्योम)
अणु
	काष्ठा sigaction old, new;

	prपूर्णांकk(UM_KERN_INFO "Checking for host processor cmov support...");
	new.sa_handler = cmov_sigill_test_handler;

	/* Make sure that संक_अवैध is enabled after the handler दीर्घ_लाँघs back */
	new.sa_flags = SA_NODEFER;
	sigemptyset(&new.sa_mask);
	sigaction(संक_अवैध, &new, &old);

	अगर (बनाओ_लाँघ(cmov_test_वापस) == 0) अणु
		अचिन्हित दीर्घ foo = 0;
		__यंत्र__ __अस्थिर__("cmovz %0, %1" : "=r" (foo) : "0" (foo));
		prपूर्णांकk(UM_KERN_CONT "Yes\n");
	पूर्ण अन्यथा
		prपूर्णांकk(UM_KERN_CONT "No\n");

	sigaction(संक_अवैध, &old, &new);
पूर्ण

व्योम arch_examine_संकेत(पूर्णांक sig, काष्ठा uml_pt_regs *regs)
अणु
	अचिन्हित अक्षर पंचांगp[2];

	/*
	 * This is testing क्रम a cmov (0x0f 0x4x) inकाष्ठाion causing a
	 * संक_अवैध in init.
	 */
	अगर ((sig != संक_अवैध) || (get_current_pid() != 1))
		वापस;

	अगर (copy_from_user_proc(पंचांगp, (व्योम *) UPT_IP(regs), 2)) अणु
		prपूर्णांकk(UM_KERN_ERR "SIGILL in init, could not read "
		       "instructions!\n");
		वापस;
	पूर्ण

	अगर ((पंचांगp[0] != 0x0f) || ((पंचांगp[1] & 0xf0) != 0x40))
		वापस;

	अगर (host_has_cmov == 0)
		prपूर्णांकk(UM_KERN_ERR "SIGILL caused by cmov, which this "
		       "processor doesn't implement.  Boot a filesystem "
		       "compiled for older processors");
	अन्यथा अगर (host_has_cmov == 1)
		prपूर्णांकk(UM_KERN_ERR "SIGILL caused by cmov, which this "
		       "processor claims to implement");
	अन्यथा
		prपूर्णांकk(UM_KERN_ERR "Bad value for host_has_cmov (%d)",
			host_has_cmov);
पूर्ण
