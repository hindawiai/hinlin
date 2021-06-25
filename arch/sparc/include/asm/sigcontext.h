<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_SIGCONTEXT_H
#घोषणा __SPARC_SIGCONTEXT_H

#समावेश <यंत्र/ptrace.h>
#समावेश <uapi/यंत्र/sigcontext.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा __SUNOS_MAXWIN   31

/* This is what SunOS करोes, so shall I unless we use new 32bit संकेतs or rt संकेतs. */
काष्ठा sigcontext32 अणु
	पूर्णांक sigc_onstack;      /* state to restore */
	पूर्णांक sigc_mask;         /* sigmask to restore */
	पूर्णांक sigc_sp;           /* stack poपूर्णांकer */
	पूर्णांक sigc_pc;           /* program counter */
	पूर्णांक sigc_npc;          /* next program counter */
	पूर्णांक sigc_psr;          /* क्रम condition codes etc */
	पूर्णांक sigc_g1;           /* User uses these two रेजिस्टरs */
	पूर्णांक sigc_o0;           /* within the trampoline code. */

	/* Now comes inक्रमmation regarding the users winकरोw set
	 * at the समय of the संकेत.
	 */
	पूर्णांक sigc_oswins;       /* outstanding winकरोws */

	/* stack ptrs क्रम each regwin buf */
	अचिन्हित पूर्णांक sigc_spbuf[__SUNOS_MAXWIN];

	/* Winकरोws to restore after संकेत */
	काष्ठा reg_winकरोw32 sigc_wbuf[__SUNOS_MAXWIN];
पूर्ण;


/* This is what we use क्रम 32bit new non-rt संकेतs. */

प्रकार काष्ठा अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक psr;
		अचिन्हित पूर्णांक pc;
		अचिन्हित पूर्णांक npc;
		अचिन्हित पूर्णांक y;
		अचिन्हित पूर्णांक u_regs[16]; /* globals and ins */
	पूर्ण			si_regs;
	पूर्णांक			si_mask;
पूर्ण __siginfo32_t;

#घोषणा __SIGC_MAXWIN	7

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ locals[8];
	अचिन्हित दीर्घ ins[8];
पूर्ण __siginfo_reg_winकरोw;

प्रकार काष्ठा अणु
	पूर्णांक			wsaved;
	__siginfo_reg_winकरोw	reg_winकरोw[__SIGC_MAXWIN];
	अचिन्हित दीर्घ		rwbuf_stkptrs[__SIGC_MAXWIN];
पूर्ण __siginfo_rwin_t;

#अगर_घोषित CONFIG_SPARC64
प्रकार काष्ठा अणु
	अचिन्हित   पूर्णांक si_भग्न_regs [64];
	अचिन्हित   दीर्घ si_fsr;
	अचिन्हित   दीर्घ si_gsr;
	अचिन्हित   दीर्घ si_fprs;
पूर्ण __siginfo_fpu_t;

/* This is what SunOS करोesn't, so we have to ग_लिखो this alone
   and करो it properly. */
काष्ठा sigcontext अणु
	/* The size of this array has to match SI_MAX_SIZE from siginfo.h */
	अक्षर			sigc_info[128];
	काष्ठा अणु
		अचिन्हित दीर्घ	u_regs[16]; /* globals and ins */
		अचिन्हित दीर्घ	tstate;
		अचिन्हित दीर्घ	tpc;
		अचिन्हित दीर्घ	tnpc;
		अचिन्हित पूर्णांक	y;
		अचिन्हित पूर्णांक	fprs;
	पूर्ण			sigc_regs;
	__siginfo_fpu_t *	sigc_fpu_save;
	काष्ठा अणु
		व्योम	*	ss_sp;
		पूर्णांक		ss_flags;
		अचिन्हित दीर्घ	ss_size;
	पूर्ण			sigc_stack;
	अचिन्हित दीर्घ		sigc_mask;
	__siginfo_rwin_t *	sigc_rwin_save;
पूर्ण;

#अन्यथा

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ si_भग्न_regs [32];
	अचिन्हित दीर्घ si_fsr;
	अचिन्हित दीर्घ si_fpqdepth;
	काष्ठा अणु
		अचिन्हित दीर्घ *insn_addr;
		अचिन्हित दीर्घ insn;
	पूर्ण si_fpqueue [16];
पूर्ण __siginfo_fpu_t;
#पूर्ण_अगर /* (CONFIG_SPARC64) */


#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__SPARC_SIGCONTEXT_H) */
