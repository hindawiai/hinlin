<शैली गुरु>
/*
 * Copyright (C) 2004 PathScale, Inc
 * Copyright (C) 2004 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <sys/ptrace.h>
#अगर_घोषित __i386__
#समावेश <sys/user.h>
#पूर्ण_अगर
#समावेश <दीर्घ_लाँघ.h>
#समावेश <sysdep/ptrace_user.h>
#समावेश <sys/uपन.स>
#समावेश <यंत्र/sigcontext.h>
#समावेश <linux/elf.h>

पूर्णांक have_xstate_support;

पूर्णांक save_i387_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
	अगर (ptrace(PTRACE_GETFPREGS, pid, 0, fp_regs) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक save_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
#अगर_घोषित PTRACE_GETREGSET
	काष्ठा iovec iov;

	अगर (have_xstate_support) अणु
		iov.iov_base = fp_regs;
		iov.iov_len = FP_SIZE * माप(अचिन्हित दीर्घ);
		अगर (ptrace(PTRACE_GETREGSET, pid, NT_X86_XSTATE, &iov) < 0)
			वापस -त्रुटि_सं;
		वापस 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
		वापस save_i387_रेजिस्टरs(pid, fp_regs);
पूर्ण

पूर्णांक restore_i387_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
	अगर (ptrace(PTRACE_SETFPREGS, pid, 0, fp_regs) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक restore_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
#अगर_घोषित PTRACE_SETREGSET
	काष्ठा iovec iov;
	अगर (have_xstate_support) अणु
		iov.iov_base = fp_regs;
		iov.iov_len = FP_SIZE * माप(अचिन्हित दीर्घ);
		अगर (ptrace(PTRACE_SETREGSET, pid, NT_X86_XSTATE, &iov) < 0)
			वापस -त्रुटि_सं;
		वापस 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
		वापस restore_i387_रेजिस्टरs(pid, fp_regs);
पूर्ण

#अगर_घोषित __i386__
पूर्णांक have_fpx_regs = 1;
पूर्णांक save_fpx_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
	अगर (ptrace(PTRACE_GETFPXREGS, pid, 0, fp_regs) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक restore_fpx_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *fp_regs)
अणु
	अगर (ptrace(PTRACE_SETFPXREGS, pid, 0, fp_regs) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक get_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *regs)
अणु
	अगर (have_fpx_regs)
		वापस save_fpx_रेजिस्टरs(pid, regs);
	अन्यथा
		वापस save_fp_रेजिस्टरs(pid, regs);
पूर्ण

पूर्णांक put_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *regs)
अणु
	अगर (have_fpx_regs)
		वापस restore_fpx_रेजिस्टरs(pid, regs);
	अन्यथा
		वापस restore_fp_रेजिस्टरs(pid, regs);
पूर्ण

व्योम arch_init_रेजिस्टरs(पूर्णांक pid)
अणु
	काष्ठा user_fpxregs_काष्ठा fpx_regs;
	पूर्णांक err;

	err = ptrace(PTRACE_GETFPXREGS, pid, 0, &fpx_regs);
	अगर (!err)
		वापस;

	अगर (त्रुटि_सं != EIO)
		panic("check_ptrace : PTRACE_GETFPXREGS failed, errno = %d",
		      त्रुटि_सं);

	have_fpx_regs = 0;
पूर्ण
#अन्यथा

पूर्णांक get_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *regs)
अणु
	वापस save_fp_रेजिस्टरs(pid, regs);
पूर्ण

पूर्णांक put_fp_रेजिस्टरs(पूर्णांक pid, अचिन्हित दीर्घ *regs)
अणु
	वापस restore_fp_रेजिस्टरs(pid, regs);
पूर्ण

व्योम arch_init_रेजिस्टरs(पूर्णांक pid)
अणु
#अगर_घोषित PTRACE_GETREGSET
	व्योम * fp_regs;
	काष्ठा iovec iov;

	fp_regs = दो_स्मृति(FP_SIZE * माप(अचिन्हित दीर्घ));
	अगर(fp_regs == शून्य)
		वापस;

	iov.iov_base = fp_regs;
	iov.iov_len = FP_SIZE * माप(अचिन्हित दीर्घ);
	अगर (ptrace(PTRACE_GETREGSET, pid, NT_X86_XSTATE, &iov) == 0)
		have_xstate_support = 1;

	मुक्त(fp_regs);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ get_thपढ़ो_reg(पूर्णांक reg, लाँघ_बफ *buf)
अणु
	चयन (reg) अणु
#अगर_घोषित __i386__
	हाल HOST_IP:
		वापस buf[0]->__eip;
	हाल HOST_SP:
		वापस buf[0]->__esp;
	हाल HOST_BP:
		वापस buf[0]->__ebp;
#अन्यथा
	हाल HOST_IP:
		वापस buf[0]->__rip;
	हाल HOST_SP:
		वापस buf[0]->__rsp;
	हाल HOST_BP:
		वापस buf[0]->__rbp;
#पूर्ण_अगर
	शेष:
		prपूर्णांकk(UM_KERN_ERR "get_thread_regs - unknown register %d\n",
		       reg);
		वापस 0;
	पूर्ण
पूर्ण
