<शैली गुरु>
/*
 * Copyright (C) 2004 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <sysdep/stub.h>
#समावेश <sysdep/faultinfo.h>
#समावेश <sysdep/mcontext.h>
#समावेश <sys/ucontext.h>

व्योम __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(पूर्णांक sig, siginfo_t *info, व्योम *p)
अणु
	पूर्णांक stack;
	ucontext_t *uc = p;
	काष्ठा faultinfo *f = (व्योम *)(((अचिन्हित दीर्घ)&stack) & ~(UM_KERN_PAGE_SIZE - 1));

	GET_FAULTINFO_FROM_MC(*f, &uc->uc_mcontext);
	trap_myself();
पूर्ण

