<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
काष्ठा sigscratch अणु
	अचिन्हित दीर्घ scratch_unat;	/* ar.unat क्रम the general रेजिस्टरs saved in pt */
	अचिन्हित दीर्घ ar_pfs;		/* क्रम syscalls, the user-level function-state  */
	काष्ठा pt_regs pt;
पूर्ण;

काष्ठा sigframe अणु
	/*
	 * Place संकेत handler args where user-level unwinder can find them easily.
	 * DO NOT MOVE THESE.  They are part of the IA-64 Linux ABI and there is
	 * user-level code that depends on their presence!
	 */
	अचिन्हित दीर्घ arg0;		/* signum */
	अचिन्हित दीर्घ arg1;		/* siginfo poपूर्णांकer */
	अचिन्हित दीर्घ arg2;		/* sigcontext poपूर्णांकer */
	/*
	 * End of architected state.
	 */

	व्योम __user *handler;		/* poपूर्णांकer to the plabel of the संकेत handler */
	काष्ठा siginfo info;
	काष्ठा sigcontext sc;
पूर्ण;

बाह्य व्योम ia64_करो_संकेत (काष्ठा sigscratch *, दीर्घ);
