<शैली गुरु>
/*
 * Copyright (C) 2007 Jeff Dike (jdike@अणुaddtoit.com,linux.पूर्णांकel.comपूर्ण)
 * Licensed under the GPL
 */

#समावेश <sys/ptrace.h>
#समावेश <यंत्र/ptrace.h>

पूर्णांक os_arch_prctl(पूर्णांक pid, पूर्णांक option, अचिन्हित दीर्घ *arg2)
अणु
	वापस ptrace(PTRACE_ARCH_PRCTL, pid, (अचिन्हित दीर्घ) arg2, option);
पूर्ण
