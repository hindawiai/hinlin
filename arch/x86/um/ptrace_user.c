<शैली गुरु>
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <त्रुटिसं.स>
#समावेश <ptrace_user.h>

पूर्णांक ptrace_getregs(दीर्घ pid, अचिन्हित दीर्घ *regs_out)
अणु
	अगर (ptrace(PTRACE_GETREGS, pid, 0, regs_out) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक ptrace_setregs(दीर्घ pid, अचिन्हित दीर्घ *regs)
अणु
	अगर (ptrace(PTRACE_SETREGS, pid, 0, regs) < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण
