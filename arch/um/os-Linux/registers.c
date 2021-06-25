<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2004 PathScale, Inc
 * Copyright (C) 2004 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <sys/ptrace.h>
#समावेश <sysdep/ptrace.h>
#समावेश <sysdep/ptrace_user.h>
#समावेश <रेजिस्टरs.h>

पूर्णांक save_रेजिस्टरs(पूर्णांक pid, काष्ठा uml_pt_regs *regs)
अणु
	पूर्णांक err;

	err = ptrace(PTRACE_GETREGS, pid, 0, regs->gp);
	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक restore_रेजिस्टरs(पूर्णांक pid, काष्ठा uml_pt_regs *regs)
अणु
	पूर्णांक err;

	err = ptrace(PTRACE_SETREGS, pid, 0, regs->gp);
	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

/* This is set once at boot समय and not changed thereafter */

अटल अचिन्हित दीर्घ exec_regs[MAX_REG_NR];
अटल अचिन्हित दीर्घ exec_fp_regs[FP_SIZE];

पूर्णांक init_रेजिस्टरs(पूर्णांक pid)
अणु
	पूर्णांक err;

	err = ptrace(PTRACE_GETREGS, pid, 0, exec_regs);
	अगर (err < 0)
		वापस -त्रुटि_सं;

	arch_init_रेजिस्टरs(pid);
	get_fp_रेजिस्टरs(pid, exec_fp_regs);
	वापस 0;
पूर्ण

व्योम get_safe_रेजिस्टरs(अचिन्हित दीर्घ *regs, अचिन्हित दीर्घ *fp_regs)
अणु
	स_नकल(regs, exec_regs, माप(exec_regs));

	अगर (fp_regs)
		स_नकल(fp_regs, exec_fp_regs, माप(exec_fp_regs));
पूर्ण
