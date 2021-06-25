<शैली गुरु>
/*
 *  linux/arch/m68k/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Linux/m68k support by Hamish Macकरोnald
 *
 * 68060 fixes by Jesper Skov
 *
 * 1997-12-01  Modअगरied क्रम POSIX.1b संकेतs by Andreas Schwab
 *
 * mathemu support by Roman Zippel
 *  (Note: fpstate in the संकेत context is completely ignored क्रम the emulator
 *         and the पूर्णांकernal भग्नing poपूर्णांक क्रमmat is put on stack)
 */

/*
 * ++roman (07/09/96): implemented संकेत stacks (specially क्रम tosemu on
 * Atari :-) Current limitation: Only one sigstack can be active at one समय.
 * If a second संकेत with SA_ONSTACK set arrives जबतक working on a sigstack,
 * SA_ONSTACK is ignored. This behaviour aव्योमs lots of trouble with nested
 * संकेत handlers!
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/highuid.h>
#समावेश <linux/personality.h>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/extable.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/cacheflush.h>

#अगर_घोषित CONFIG_MMU

/*
 * Handle the slight dअगरferences in classic 68k and ColdFire trap frames.
 */
#अगर_घोषित CONFIG_COLDFIRE
#घोषणा	FORMAT		4
#घोषणा	FMT4SIZE	0
#अन्यथा
#घोषणा	FORMAT		0
#घोषणा	FMT4SIZE	माप_field(काष्ठा frame, un.fmt4)
#पूर्ण_अगर

अटल स्थिर पूर्णांक frame_size_change[16] = अणु
  [1]	= -1, /* माप_field(काष्ठा frame, un.fmt1), */
  [2]	= माप_field(काष्ठा frame, un.fmt2),
  [3]	= माप_field(काष्ठा frame, un.fmt3),
  [4]	= FMT4SIZE,
  [5]	= -1, /* माप_field(काष्ठा frame, un.fmt5), */
  [6]	= -1, /* माप_field(काष्ठा frame, un.fmt6), */
  [7]	= माप_field(काष्ठा frame, un.fmt7),
  [8]	= -1, /* माप_field(काष्ठा frame, un.fmt8), */
  [9]	= माप_field(काष्ठा frame, un.fmt9),
  [10]	= माप_field(काष्ठा frame, un.fmta),
  [11]	= माप_field(काष्ठा frame, un.fmtb),
  [12]	= -1, /* माप_field(काष्ठा frame, un.fmtc), */
  [13]	= -1, /* माप_field(काष्ठा frame, un.fmtd), */
  [14]	= -1, /* माप_field(काष्ठा frame, un.fmte), */
  [15]	= -1, /* माप_field(काष्ठा frame, un.fmtf), */
पूर्ण;

अटल अंतरभूत पूर्णांक frame_extra_sizes(पूर्णांक f)
अणु
	वापस frame_size_change[f];
पूर्ण

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;
	काष्ठा pt_regs *tregs;

	/* Are we prepared to handle this kernel fault? */
	fixup = search_exception_tables(regs->pc);
	अगर (!fixup)
		वापस 0;

	/* Create a new four word stack frame, discarding the old one. */
	regs->stkadj = frame_extra_sizes(regs->क्रमmat);
	tregs =	(काष्ठा pt_regs *)((दीर्घ)regs + regs->stkadj);
	tregs->vector = regs->vector;
	tregs->क्रमmat = FORMAT;
	tregs->pc = fixup->fixup;
	tregs->sr = regs->sr;

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम push_cache (अचिन्हित दीर्घ vaddr)
अणु
	/*
	 * Using the old cache_push_v() was really a big waste.
	 *
	 * What we are trying to करो is to flush 8 bytes to ram.
	 * Flushing 2 cache lines of 16 bytes is much cheaper than
	 * flushing 1 or 2 pages, as previously करोne in
	 * cache_push_v().
	 *                                                     Jes
	 */
	अगर (CPU_IS_040) अणु
		अचिन्हित दीर्घ temp;

		__यंत्र__ __अस्थिर__ (".chip 68040\n\t"
				      "nop\n\t"
				      "ptestr (%1)\n\t"
				      "movec %%mmusr,%0\n\t"
				      ".chip 68k"
				      : "=r" (temp)
				      : "a" (vaddr));

		temp &= PAGE_MASK;
		temp |= vaddr & ~PAGE_MASK;

		__यंत्र__ __अस्थिर__ (".chip 68040\n\t"
				      "nop\n\t"
				      "cpushl %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (temp));
	पूर्ण
	अन्यथा अगर (CPU_IS_060) अणु
		अचिन्हित दीर्घ temp;
		__यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				      "plpar (%0)\n\t"
				      ".chip 68k"
				      : "=a" (temp)
				      : "0" (vaddr));
		__यंत्र__ __अस्थिर__ (".chip 68060\n\t"
				      "cpushl %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (temp));
	पूर्ण अन्यथा अगर (!CPU_IS_COLDFIRE) अणु
		/*
		 * 68030/68020 have no ग_लिखोback cache;
		 * still need to clear icache.
		 * Note that vaddr is guaranteed to be दीर्घ word aligned.
		 */
		अचिन्हित दीर्घ temp;
		यंत्र अस्थिर ("movec %%cacr,%0" : "=r" (temp));
		temp += 4;
		यंत्र अस्थिर ("movec %0,%%caar\n\t"
			      "movec %1,%%cacr"
			      : : "r" (vaddr), "r" (temp));
		यंत्र अस्थिर ("movec %0,%%caar\n\t"
			      "movec %1,%%cacr"
			      : : "r" (vaddr + 4), "r" (temp));
	पूर्ण अन्यथा अणु
		/* CPU_IS_COLDFIRE */
#अगर defined(CONFIG_CACHE_COPYBACK)
		flush_cf_dcache(0, DCACHE_MAX_ADDR);
#पूर्ण_अगर
		/* Invalidate inकाष्ठाion cache क्रम the pushed bytes */
		clear_cf_icache(vaddr, vaddr + 8);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम adjustक्रमmat(काष्ठा pt_regs *regs)
अणु
पूर्ण

अटल अंतरभूत व्योम save_a5_state(काष्ठा sigcontext *sc, काष्ठा pt_regs *regs)
अणु
पूर्ण

#अन्यथा /* CONFIG_MMU */

व्योम ret_from_user_संकेत(व्योम);
व्योम ret_from_user_rt_संकेत(व्योम);

अटल अंतरभूत पूर्णांक frame_extra_sizes(पूर्णांक f)
अणु
	/* No frame size adjusपंचांगents required on non-MMU CPUs */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adjustक्रमmat(काष्ठा pt_regs *regs)
अणु
	/*
	 * set क्रमmat byte to make stack appear modulo 4, which it will
	 * be when करोing the rte
	 */
	regs->क्रमmat = 0x4;
पूर्ण

अटल अंतरभूत व्योम save_a5_state(काष्ठा sigcontext *sc, काष्ठा pt_regs *regs)
अणु
	sc->sc_a5 = ((काष्ठा चयन_stack *)regs - 1)->a5;
पूर्ण

अटल अंतरभूत व्योम push_cache(अचिन्हित दीर्घ vaddr)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 *
 * Keep the वापस code on the stack quadword aligned!
 * That makes the cache flush below easier.
 */

काष्ठा sigframe
अणु
	अक्षर __user *pretcode;
	पूर्णांक sig;
	पूर्णांक code;
	काष्ठा sigcontext __user *psc;
	अक्षर retcode[8];
	अचिन्हित दीर्घ extramask[_NSIG_WORDS-1];
	काष्ठा sigcontext sc;
पूर्ण;

काष्ठा rt_sigframe
अणु
	अक्षर __user *pretcode;
	पूर्णांक sig;
	काष्ठा siginfo __user *pinfo;
	व्योम __user *puc;
	अक्षर retcode[8];
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

#घोषणा FPCONTEXT_SIZE	216
#घोषणा uc_fpstate	uc_filler[0]
#घोषणा uc_क्रमmatvec	uc_filler[FPCONTEXT_SIZE/4]
#घोषणा uc_extra	uc_filler[FPCONTEXT_SIZE/4+1]

#अगर_घोषित CONFIG_FPU

अटल अचिन्हित अक्षर fpu_version;	/* version number of fpu, set by setup_frame */

अटल अंतरभूत पूर्णांक restore_fpu_state(काष्ठा sigcontext *sc)
अणु
	पूर्णांक err = 1;

	अगर (FPU_IS_EMU) अणु
	    /* restore रेजिस्टरs */
	    स_नकल(current->thपढ़ो.fpcntl, sc->sc_fpcntl, 12);
	    स_नकल(current->thपढ़ो.fp, sc->sc_fpregs, 24);
	    वापस 0;
	पूर्ण

	अगर (CPU_IS_060 ? sc->sc_fpstate[2] : sc->sc_fpstate[0]) अणु
	    /* Verअगरy the frame क्रमmat.  */
	    अगर (!(CPU_IS_060 || CPU_IS_COLDFIRE) &&
		 (sc->sc_fpstate[0] != fpu_version))
		जाओ out;
	    अगर (CPU_IS_020_OR_030) अणु
		अगर (m68k_fputype & FPU_68881 &&
		    !(sc->sc_fpstate[1] == 0x18 || sc->sc_fpstate[1] == 0xb4))
		    जाओ out;
		अगर (m68k_fputype & FPU_68882 &&
		    !(sc->sc_fpstate[1] == 0x38 || sc->sc_fpstate[1] == 0xd4))
		    जाओ out;
	    पूर्ण अन्यथा अगर (CPU_IS_040) अणु
		अगर (!(sc->sc_fpstate[1] == 0x00 ||
                      sc->sc_fpstate[1] == 0x28 ||
                      sc->sc_fpstate[1] == 0x60))
		    जाओ out;
	    पूर्ण अन्यथा अगर (CPU_IS_060) अणु
		अगर (!(sc->sc_fpstate[3] == 0x00 ||
                      sc->sc_fpstate[3] == 0x60 ||
		      sc->sc_fpstate[3] == 0xe0))
		    जाओ out;
	    पूर्ण अन्यथा अगर (CPU_IS_COLDFIRE) अणु
		अगर (!(sc->sc_fpstate[0] == 0x00 ||
		      sc->sc_fpstate[0] == 0x05 ||
		      sc->sc_fpstate[0] == 0xe5))
		    जाओ out;
	    पूर्ण अन्यथा
		जाओ out;

	    अगर (CPU_IS_COLDFIRE) अणु
		__यंत्र__ अस्थिर ("fmovemd %0,%%fp0-%%fp1\n\t"
				  "fmovel %1,%%fpcr\n\t"
				  "fmovel %2,%%fpsr\n\t"
				  "fmovel %3,%%fpiar"
				  : /* no outमाला_दो */
				  : "m" (sc->sc_fpregs[0]),
				    "m" (sc->sc_fpcntl[0]),
				    "m" (sc->sc_fpcntl[1]),
				    "m" (sc->sc_fpcntl[2]));
	    पूर्ण अन्यथा अणु
		__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
				  "fmovemx %0,%%fp0-%%fp1\n\t"
				  "fmoveml %1,%%fpcr/%%fpsr/%%fpiar\n\t"
				  ".chip 68k"
				  : /* no outमाला_दो */
				  : "m" (*sc->sc_fpregs),
				    "m" (*sc->sc_fpcntl));
	    पूर्ण
	पूर्ण

	अगर (CPU_IS_COLDFIRE) अणु
		__यंत्र__ अस्थिर ("frestore %0" : : "m" (*sc->sc_fpstate));
	पूर्ण अन्यथा अणु
		__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
				  "frestore %0\n\t"
				  ".chip 68k"
				  : : "m" (*sc->sc_fpstate));
	पूर्ण
	err = 0;

out:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक rt_restore_fpu_state(काष्ठा ucontext __user *uc)
अणु
	अचिन्हित अक्षर fpstate[FPCONTEXT_SIZE];
	पूर्णांक context_size = CPU_IS_060 ? 8 : (CPU_IS_COLDFIRE ? 12 : 0);
	fpregset_t fpregs;
	पूर्णांक err = 1;

	अगर (FPU_IS_EMU) अणु
		/* restore fpu control रेजिस्टर */
		अगर (__copy_from_user(current->thपढ़ो.fpcntl,
				uc->uc_mcontext.fpregs.f_fpcntl, 12))
			जाओ out;
		/* restore all other fpu रेजिस्टर */
		अगर (__copy_from_user(current->thपढ़ो.fp,
				uc->uc_mcontext.fpregs.f_fpregs, 96))
			जाओ out;
		वापस 0;
	पूर्ण

	अगर (__get_user(*(दीर्घ *)fpstate, (दीर्घ __user *)&uc->uc_fpstate))
		जाओ out;
	अगर (CPU_IS_060 ? fpstate[2] : fpstate[0]) अणु
		अगर (!(CPU_IS_060 || CPU_IS_COLDFIRE))
			context_size = fpstate[1];
		/* Verअगरy the frame क्रमmat.  */
		अगर (!(CPU_IS_060 || CPU_IS_COLDFIRE) &&
		     (fpstate[0] != fpu_version))
			जाओ out;
		अगर (CPU_IS_020_OR_030) अणु
			अगर (m68k_fputype & FPU_68881 &&
			    !(context_size == 0x18 || context_size == 0xb4))
				जाओ out;
			अगर (m68k_fputype & FPU_68882 &&
			    !(context_size == 0x38 || context_size == 0xd4))
				जाओ out;
		पूर्ण अन्यथा अगर (CPU_IS_040) अणु
			अगर (!(context_size == 0x00 ||
			      context_size == 0x28 ||
			      context_size == 0x60))
				जाओ out;
		पूर्ण अन्यथा अगर (CPU_IS_060) अणु
			अगर (!(fpstate[3] == 0x00 ||
			      fpstate[3] == 0x60 ||
			      fpstate[3] == 0xe0))
				जाओ out;
		पूर्ण अन्यथा अगर (CPU_IS_COLDFIRE) अणु
			अगर (!(fpstate[3] == 0x00 ||
			      fpstate[3] == 0x05 ||
			      fpstate[3] == 0xe5))
				जाओ out;
		पूर्ण अन्यथा
			जाओ out;
		अगर (__copy_from_user(&fpregs, &uc->uc_mcontext.fpregs,
				     माप(fpregs)))
			जाओ out;

		अगर (CPU_IS_COLDFIRE) अणु
			__यंत्र__ अस्थिर ("fmovemd %0,%%fp0-%%fp7\n\t"
					  "fmovel %1,%%fpcr\n\t"
					  "fmovel %2,%%fpsr\n\t"
					  "fmovel %3,%%fpiar"
					  : /* no outमाला_दो */
					  : "m" (fpregs.f_fpregs[0]),
					    "m" (fpregs.f_fpcntl[0]),
					    "m" (fpregs.f_fpcntl[1]),
					    "m" (fpregs.f_fpcntl[2]));
		पूर्ण अन्यथा अणु
			__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
					  "fmovemx %0,%%fp0-%%fp7\n\t"
					  "fmoveml %1,%%fpcr/%%fpsr/%%fpiar\n\t"
					  ".chip 68k"
					  : /* no outमाला_दो */
					  : "m" (*fpregs.f_fpregs),
					    "m" (*fpregs.f_fpcntl));
		पूर्ण
	पूर्ण
	अगर (context_size &&
	    __copy_from_user(fpstate + 4, (दीर्घ __user *)&uc->uc_fpstate + 1,
			     context_size))
		जाओ out;

	अगर (CPU_IS_COLDFIRE) अणु
		__यंत्र__ अस्थिर ("frestore %0" : : "m" (*fpstate));
	पूर्ण अन्यथा अणु
		__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
				  "frestore %0\n\t"
				  ".chip 68k"
				  : : "m" (*fpstate));
	पूर्ण
	err = 0;

out:
	वापस err;
पूर्ण

/*
 * Set up a संकेत frame.
 */
अटल अंतरभूत व्योम save_fpu_state(काष्ठा sigcontext *sc, काष्ठा pt_regs *regs)
अणु
	अगर (FPU_IS_EMU) अणु
		/* save रेजिस्टरs */
		स_नकल(sc->sc_fpcntl, current->thपढ़ो.fpcntl, 12);
		स_नकल(sc->sc_fpregs, current->thपढ़ो.fp, 24);
		वापस;
	पूर्ण

	अगर (CPU_IS_COLDFIRE) अणु
		__यंत्र__ अस्थिर ("fsave %0"
				  : : "m" (*sc->sc_fpstate) : "memory");
	पूर्ण अन्यथा अणु
		__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
				  "fsave %0\n\t"
				  ".chip 68k"
				  : : "m" (*sc->sc_fpstate) : "memory");
	पूर्ण

	अगर (CPU_IS_060 ? sc->sc_fpstate[2] : sc->sc_fpstate[0]) अणु
		fpu_version = sc->sc_fpstate[0];
		अगर (CPU_IS_020_OR_030 &&
		    regs->vector >= (VEC_FPBRUC * 4) &&
		    regs->vector <= (VEC_FPन_अंक * 4)) अणु
			/* Clear pending exception in 68882 idle frame */
			अगर (*(अचिन्हित लघु *) sc->sc_fpstate == 0x1f38)
				sc->sc_fpstate[0x38] |= 1 << 3;
		पूर्ण

		अगर (CPU_IS_COLDFIRE) अणु
			__यंत्र__ अस्थिर ("fmovemd %%fp0-%%fp1,%0\n\t"
					  "fmovel %%fpcr,%1\n\t"
					  "fmovel %%fpsr,%2\n\t"
					  "fmovel %%fpiar,%3"
					  : "=m" (sc->sc_fpregs[0]),
					    "=m" (sc->sc_fpcntl[0]),
					    "=m" (sc->sc_fpcntl[1]),
					    "=m" (sc->sc_fpcntl[2])
					  : /* no inमाला_दो */
					  : "memory");
		पूर्ण अन्यथा अणु
			__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
					  "fmovemx %%fp0-%%fp1,%0\n\t"
					  "fmoveml %%fpcr/%%fpsr/%%fpiar,%1\n\t"
					  ".chip 68k"
					  : "=m" (*sc->sc_fpregs),
					    "=m" (*sc->sc_fpcntl)
					  : /* no inमाला_दो */
					  : "memory");
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक rt_save_fpu_state(काष्ठा ucontext __user *uc, काष्ठा pt_regs *regs)
अणु
	अचिन्हित अक्षर fpstate[FPCONTEXT_SIZE];
	पूर्णांक context_size = CPU_IS_060 ? 8 : (CPU_IS_COLDFIRE ? 12 : 0);
	पूर्णांक err = 0;

	अगर (FPU_IS_EMU) अणु
		/* save fpu control रेजिस्टर */
		err |= copy_to_user(uc->uc_mcontext.fpregs.f_fpcntl,
				current->thपढ़ो.fpcntl, 12);
		/* save all other fpu रेजिस्टर */
		err |= copy_to_user(uc->uc_mcontext.fpregs.f_fpregs,
				current->thपढ़ो.fp, 96);
		वापस err;
	पूर्ण

	अगर (CPU_IS_COLDFIRE) अणु
		__यंत्र__ अस्थिर ("fsave %0" : : "m" (*fpstate) : "memory");
	पूर्ण अन्यथा अणु
		__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
				  "fsave %0\n\t"
				  ".chip 68k"
				  : : "m" (*fpstate) : "memory");
	पूर्ण

	err |= __put_user(*(दीर्घ *)fpstate, (दीर्घ __user *)&uc->uc_fpstate);
	अगर (CPU_IS_060 ? fpstate[2] : fpstate[0]) अणु
		fpregset_t fpregs;
		अगर (!(CPU_IS_060 || CPU_IS_COLDFIRE))
			context_size = fpstate[1];
		fpu_version = fpstate[0];
		अगर (CPU_IS_020_OR_030 &&
		    regs->vector >= (VEC_FPBRUC * 4) &&
		    regs->vector <= (VEC_FPन_अंक * 4)) अणु
			/* Clear pending exception in 68882 idle frame */
			अगर (*(अचिन्हित लघु *) fpstate == 0x1f38)
				fpstate[0x38] |= 1 << 3;
		पूर्ण
		अगर (CPU_IS_COLDFIRE) अणु
			__यंत्र__ अस्थिर ("fmovemd %%fp0-%%fp7,%0\n\t"
					  "fmovel %%fpcr,%1\n\t"
					  "fmovel %%fpsr,%2\n\t"
					  "fmovel %%fpiar,%3"
					  : "=m" (fpregs.f_fpregs[0]),
					    "=m" (fpregs.f_fpcntl[0]),
					    "=m" (fpregs.f_fpcntl[1]),
					    "=m" (fpregs.f_fpcntl[2])
					  : /* no inमाला_दो */
					  : "memory");
		पूर्ण अन्यथा अणु
			__यंत्र__ अस्थिर (".chip 68k/68881\n\t"
					  "fmovemx %%fp0-%%fp7,%0\n\t"
					  "fmoveml %%fpcr/%%fpsr/%%fpiar,%1\n\t"
					  ".chip 68k"
					  : "=m" (*fpregs.f_fpregs),
					    "=m" (*fpregs.f_fpcntl)
					  : /* no inमाला_दो */
					  : "memory");
		पूर्ण
		err |= copy_to_user(&uc->uc_mcontext.fpregs, &fpregs,
				    माप(fpregs));
	पूर्ण
	अगर (context_size)
		err |= copy_to_user((दीर्घ __user *)&uc->uc_fpstate + 1, fpstate + 4,
				    context_size);
	वापस err;
पूर्ण

#अन्यथा /* CONFIG_FPU */

/*
 * For the हाल with no FPU configured these all करो nothing.
 */
अटल अंतरभूत पूर्णांक restore_fpu_state(काष्ठा sigcontext *sc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rt_restore_fpu_state(काष्ठा ucontext __user *uc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम save_fpu_state(काष्ठा sigcontext *sc, काष्ठा pt_regs *regs)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक rt_save_fpu_state(काष्ठा ucontext __user *uc, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_FPU */

अटल अंतरभूत व्योम siginfo_build_tests(व्योम)
अणु
	/*
	 * This needs to be tested on m68k as it has a lesser
	 * alignment requirement than x86 and that can cause surprises.
	 */

	/* This is part of the ABI and can never change in size: */
	BUILD_BUG_ON(माप(siginfo_t) != 128);

	/* Ensure the known fields never change in location */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_signo) != 0);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_त्रुटि_सं) != 4);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_code)  != 8);

	/* _समाप्त */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid) != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid) != 0x10);

	/* _समयr */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_tid)     != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_overrun) != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_value)   != 0x14);

	/* _rt */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid)   != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid)   != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_value) != 0x14);

	/* _sigchld */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid)    != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid)    != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_status) != 0x14);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uसमय)  != 0x18);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_sसमय)  != 0x1c);

	/* _sigfault */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_addr) != 0x0c);

	/* _sigfault._mcerr */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_addr_lsb) != 0x10);

	/* _sigfault._addr_bnd */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_lower) != 0x12);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_upper) != 0x16);

	/* _sigfault._addr_pkey */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pkey) != 0x12);

	/* _sigfault._perf */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_perf_data) != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_perf_type) != 0x14);

	/* _sigpoll */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_band)   != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_fd)     != 0x10);

	/* _sigsys */
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_call_addr) != 0x0c);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_syscall)   != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_arch)      != 0x14);

	/* any new si_fields should be added here */
पूर्ण

अटल पूर्णांक mangle_kernel_stack(काष्ठा pt_regs *regs, पूर्णांक क्रमmatvec,
			       व्योम __user *fp)
अणु
	पूर्णांक fsize = frame_extra_sizes(क्रमmatvec >> 12);
	अगर (fsize < 0) अणु
		/*
		 * user process trying to वापस with weird frame क्रमmat
		 */
		pr_debug("user process returning with weird frame format\n");
		वापस 1;
	पूर्ण
	अगर (!fsize) अणु
		regs->क्रमmat = क्रमmatvec >> 12;
		regs->vector = क्रमmatvec & 0xfff;
	पूर्ण अन्यथा अणु
		काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
		/* yes, twice as much as max(माप(frame.un.fmt<x>)) */
		अचिन्हित दीर्घ buf[माप_field(काष्ठा frame, un) / 2];

		/* that'll make sure that expansion won't crap over data */
		अगर (copy_from_user(buf + fsize / 4, fp, fsize))
			वापस 1;

		/* poपूर्णांक of no वापस */
		regs->क्रमmat = क्रमmatvec >> 12;
		regs->vector = क्रमmatvec & 0xfff;
#घोषणा frame_offset (माप(काष्ठा pt_regs)+माप(काष्ठा चयन_stack))
		__यंत्र__ __अस्थिर__ (
#अगर_घोषित CONFIG_COLDFIRE
			 "   movel %0,%/sp\n\t"
			 "   bra ret_from_signal\n"
#अन्यथा
			 "   movel %0,%/a0\n\t"
			 "   subl %1,%/a0\n\t"     /* make room on stack */
			 "   movel %/a0,%/sp\n\t"  /* set stack poपूर्णांकer */
			 /* move चयन_stack and pt_regs */
			 "1: movel %0@+,%/a0@+\n\t"
			 "   dbra %2,1b\n\t"
			 "   lea %/sp@(%c3),%/a0\n\t" /* add offset of fmt */
			 "   lsrl  #2,%1\n\t"
			 "   subql #1,%1\n\t"
			 /* copy to the gap we'd made */
			 "2: movel %4@+,%/a0@+\n\t"
			 "   dbra %1,2b\n\t"
			 "   bral ret_from_signal\n"
#पूर्ण_अगर
			 : /* no outमाला_दो, it करोesn't ever वापस */
			 : "a" (sw), "d" (fsize), "d" (frame_offset/4-1),
			   "n" (frame_offset), "a" (buf + fsize/4)
			 : "a0");
#अघोषित frame_offset
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
restore_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *usc, व्योम __user *fp)
अणु
	पूर्णांक क्रमmatvec;
	काष्ठा sigcontext context;
	पूर्णांक err = 0;

	siginfo_build_tests();

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/* get previous context */
	अगर (copy_from_user(&context, usc, माप(context)))
		जाओ badframe;

	/* restore passed रेजिस्टरs */
	regs->d0 = context.sc_d0;
	regs->d1 = context.sc_d1;
	regs->a0 = context.sc_a0;
	regs->a1 = context.sc_a1;
	regs->sr = (regs->sr & 0xff00) | (context.sc_sr & 0xff);
	regs->pc = context.sc_pc;
	regs->orig_d0 = -1;		/* disable syscall checks */
	wrusp(context.sc_usp);
	क्रमmatvec = context.sc_क्रमmatvec;

	err = restore_fpu_state(&context);

	अगर (err || mangle_kernel_stack(regs, क्रमmatvec, fp))
		जाओ badframe;

	वापस 0;

badframe:
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
rt_restore_ucontext(काष्ठा pt_regs *regs, काष्ठा चयन_stack *sw,
		    काष्ठा ucontext __user *uc)
अणु
	पूर्णांक temp;
	greg_t __user *gregs = uc->uc_mcontext.gregs;
	अचिन्हित दीर्घ usp;
	पूर्णांक err;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	err = __get_user(temp, &uc->uc_mcontext.version);
	अगर (temp != MCONTEXT_VERSION)
		जाओ badframe;
	/* restore passed रेजिस्टरs */
	err |= __get_user(regs->d0, &gregs[0]);
	err |= __get_user(regs->d1, &gregs[1]);
	err |= __get_user(regs->d2, &gregs[2]);
	err |= __get_user(regs->d3, &gregs[3]);
	err |= __get_user(regs->d4, &gregs[4]);
	err |= __get_user(regs->d5, &gregs[5]);
	err |= __get_user(sw->d6, &gregs[6]);
	err |= __get_user(sw->d7, &gregs[7]);
	err |= __get_user(regs->a0, &gregs[8]);
	err |= __get_user(regs->a1, &gregs[9]);
	err |= __get_user(regs->a2, &gregs[10]);
	err |= __get_user(sw->a3, &gregs[11]);
	err |= __get_user(sw->a4, &gregs[12]);
	err |= __get_user(sw->a5, &gregs[13]);
	err |= __get_user(sw->a6, &gregs[14]);
	err |= __get_user(usp, &gregs[15]);
	wrusp(usp);
	err |= __get_user(regs->pc, &gregs[16]);
	err |= __get_user(temp, &gregs[17]);
	regs->sr = (regs->sr & 0xff00) | (temp & 0xff);
	regs->orig_d0 = -1;		/* disable syscall checks */
	err |= __get_user(temp, &uc->uc_क्रमmatvec);

	err |= rt_restore_fpu_state(uc);
	err |= restore_altstack(&uc->uc_stack);

	अगर (err)
		जाओ badframe;

	अगर (mangle_kernel_stack(regs, temp, &uc->uc_extra))
		जाओ badframe;

	वापस 0;

badframe:
	वापस 1;
पूर्ण

यंत्रlinkage पूर्णांक करो_sigवापस(काष्ठा pt_regs *regs, काष्ठा चयन_stack *sw)
अणु
	अचिन्हित दीर्घ usp = rdusp();
	काष्ठा sigframe __user *frame = (काष्ठा sigframe __user *)(usp - 4);
	sigset_t set;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(set.sig[0], &frame->sc.sc_mask) ||
	    (_NSIG_WORDS > 1 &&
	     __copy_from_user(&set.sig[1], &frame->extramask,
			      माप(frame->extramask))))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->sc, frame + 1))
		जाओ badframe;
	वापस regs->d0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक करो_rt_sigवापस(काष्ठा pt_regs *regs, काष्ठा चयन_stack *sw)
अणु
	अचिन्हित दीर्घ usp = rdusp();
	काष्ठा rt_sigframe __user *frame = (काष्ठा rt_sigframe __user *)(usp - 4);
	sigset_t set;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (rt_restore_ucontext(regs, sw, &frame->uc))
		जाओ badframe;
	वापस regs->d0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल व्योम setup_sigcontext(काष्ठा sigcontext *sc, काष्ठा pt_regs *regs,
			     अचिन्हित दीर्घ mask)
अणु
	sc->sc_mask = mask;
	sc->sc_usp = rdusp();
	sc->sc_d0 = regs->d0;
	sc->sc_d1 = regs->d1;
	sc->sc_a0 = regs->a0;
	sc->sc_a1 = regs->a1;
	sc->sc_sr = regs->sr;
	sc->sc_pc = regs->pc;
	sc->sc_क्रमmatvec = regs->क्रमmat << 12 | regs->vector;
	save_a5_state(sc, regs);
	save_fpu_state(sc, regs);
पूर्ण

अटल अंतरभूत पूर्णांक rt_setup_ucontext(काष्ठा ucontext __user *uc, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	greg_t __user *gregs = uc->uc_mcontext.gregs;
	पूर्णांक err = 0;

	err |= __put_user(MCONTEXT_VERSION, &uc->uc_mcontext.version);
	err |= __put_user(regs->d0, &gregs[0]);
	err |= __put_user(regs->d1, &gregs[1]);
	err |= __put_user(regs->d2, &gregs[2]);
	err |= __put_user(regs->d3, &gregs[3]);
	err |= __put_user(regs->d4, &gregs[4]);
	err |= __put_user(regs->d5, &gregs[5]);
	err |= __put_user(sw->d6, &gregs[6]);
	err |= __put_user(sw->d7, &gregs[7]);
	err |= __put_user(regs->a0, &gregs[8]);
	err |= __put_user(regs->a1, &gregs[9]);
	err |= __put_user(regs->a2, &gregs[10]);
	err |= __put_user(sw->a3, &gregs[11]);
	err |= __put_user(sw->a4, &gregs[12]);
	err |= __put_user(sw->a5, &gregs[13]);
	err |= __put_user(sw->a6, &gregs[14]);
	err |= __put_user(rdusp(), &gregs[15]);
	err |= __put_user(regs->pc, &gregs[16]);
	err |= __put_user(regs->sr, &gregs[17]);
	err |= __put_user((regs->क्रमmat << 12) | regs->vector, &uc->uc_क्रमmatvec);
	err |= rt_save_fpu_state(uc, regs);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा kसंकेत *ksig, माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ usp = sigsp(rdusp(), ksig);

	वापस (व्योम __user *)((usp - frame_size) & -8UL);
पूर्ण

अटल पूर्णांक setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe __user *frame;
	पूर्णांक fsize = frame_extra_sizes(regs->क्रमmat);
	काष्ठा sigcontext context;
	पूर्णांक err = 0, sig = ksig->sig;

	अगर (fsize < 0) अणु
		pr_debug("setup_frame: Unknown frame format %#x\n",
			 regs->क्रमmat);
		वापस -EFAULT;
	पूर्ण

	frame = get_sigframe(ksig, माप(*frame) + fsize);

	अगर (fsize)
		err |= copy_to_user (frame + 1, regs + 1, fsize);

	err |= __put_user(sig, &frame->sig);

	err |= __put_user(regs->vector, &frame->code);
	err |= __put_user(&frame->sc, &frame->psc);

	अगर (_NSIG_WORDS > 1)
		err |= copy_to_user(frame->extramask, &set->sig[1],
				    माप(frame->extramask));

	setup_sigcontext(&context, regs, set->sig[0]);
	err |= copy_to_user (&frame->sc, &context, माप(context));

	/* Set up to वापस from userspace.  */
#अगर_घोषित CONFIG_MMU
	err |= __put_user(frame->retcode, &frame->pretcode);
	/* moveq #,d0; trap #0 */
	err |= __put_user(0x70004e40 + (__NR_sigवापस << 16),
			  (दीर्घ __user *)(frame->retcode));
#अन्यथा
	err |= __put_user((दीर्घ) ret_from_user_संकेत,
			  (दीर्घ __user *) &frame->pretcode);
#पूर्ण_अगर

	अगर (err)
		वापस -EFAULT;

	push_cache ((अचिन्हित दीर्घ) &frame->retcode);

	/*
	 * Set up रेजिस्टरs क्रम संकेत handler.  All the state we are about
	 * to destroy is successfully copied to sigframe.
	 */
	wrusp ((अचिन्हित दीर्घ) frame);
	regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	adjustक्रमmat(regs);

	/*
	 * This is subtle; अगर we build more than one sigframe, all but the
	 * first one will see frame क्रमmat 0 and have fsize == 0, so we won't
	 * screw stkadj.
	 */
	अगर (fsize)
		regs->stkadj = fsize;

	/* Prepare to skip over the extra stuff in the exception frame.  */
	अगर (regs->stkadj) अणु
		काष्ठा pt_regs *tregs =
			(काष्ठा pt_regs *)((uदीर्घ)regs + regs->stkadj);
		pr_debug("Performing stackadjust=%04lx\n", regs->stkadj);
		/* This must be copied with decreasing addresses to
                   handle overlaps.  */
		tregs->vector = 0;
		tregs->क्रमmat = 0;
		tregs->pc = regs->pc;
		tregs->sr = regs->sr;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			   काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक fsize = frame_extra_sizes(regs->क्रमmat);
	पूर्णांक err = 0, sig = ksig->sig;

	अगर (fsize < 0) अणु
		pr_debug("setup_frame: Unknown frame format %#x\n",
			 regs->क्रमmat);
		वापस -EFAULT;
	पूर्ण

	frame = get_sigframe(ksig, माप(*frame));

	अगर (fsize)
		err |= copy_to_user (&frame->uc.uc_extra, regs + 1, fsize);

	err |= __put_user(sig, &frame->sig);
	err |= __put_user(&frame->info, &frame->pinfo);
	err |= __put_user(&frame->uc, &frame->puc);
	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, rdusp());
	err |= rt_setup_ucontext(&frame->uc, regs);
	err |= copy_to_user (&frame->uc.uc_sigmask, set, माप(*set));

	/* Set up to वापस from userspace.  */
#अगर_घोषित CONFIG_MMU
	err |= __put_user(frame->retcode, &frame->pretcode);
#अगर_घोषित __mcoldfire__
	/* movel #__NR_rt_sigवापस,d0; trap #0 */
	err |= __put_user(0x203c0000, (दीर्घ __user *)(frame->retcode + 0));
	err |= __put_user(0x00004e40 + (__NR_rt_sigवापस << 16),
			  (दीर्घ __user *)(frame->retcode + 4));
#अन्यथा
	/* moveq #,d0; notb d0; trap #0 */
	err |= __put_user(0x70004600 + ((__NR_rt_sigवापस ^ 0xff) << 16),
			  (दीर्घ __user *)(frame->retcode + 0));
	err |= __put_user(0x4e40, (लघु __user *)(frame->retcode + 4));
#पूर्ण_अगर
#अन्यथा
	err |= __put_user((दीर्घ) ret_from_user_rt_संकेत,
			  (दीर्घ __user *) &frame->pretcode);
#पूर्ण_अगर /* CONFIG_MMU */

	अगर (err)
		वापस -EFAULT;

	push_cache ((अचिन्हित दीर्घ) &frame->retcode);

	/*
	 * Set up रेजिस्टरs क्रम संकेत handler.  All the state we are about
	 * to destroy is successfully copied to sigframe.
	 */
	wrusp ((अचिन्हित दीर्घ) frame);
	regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	adjustक्रमmat(regs);

	/*
	 * This is subtle; अगर we build more than one sigframe, all but the
	 * first one will see frame क्रमmat 0 and have fsize == 0, so we won't
	 * screw stkadj.
	 */
	अगर (fsize)
		regs->stkadj = fsize;

	/* Prepare to skip over the extra stuff in the exception frame.  */
	अगर (regs->stkadj) अणु
		काष्ठा pt_regs *tregs =
			(काष्ठा pt_regs *)((uदीर्घ)regs + regs->stkadj);
		pr_debug("Performing stackadjust=%04lx\n", regs->stkadj);
		/* This must be copied with decreasing addresses to
                   handle overlaps.  */
		tregs->vector = 0;
		tregs->क्रमmat = 0;
		tregs->pc = regs->pc;
		tregs->sr = regs->sr;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
handle_restart(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka, पूर्णांक has_handler)
अणु
	चयन (regs->d0) अणु
	हाल -ERESTARTNOHAND:
		अगर (!has_handler)
			जाओ करो_restart;
		regs->d0 = -EINTR;
		अवरोध;

	हाल -ERESTART_RESTARTBLOCK:
		अगर (!has_handler) अणु
			regs->d0 = __NR_restart_syscall;
			regs->pc -= 2;
			अवरोध;
		पूर्ण
		regs->d0 = -EINTR;
		अवरोध;

	हाल -ERESTARTSYS:
		अगर (has_handler && !(ka->sa.sa_flags & SA_RESTART)) अणु
			regs->d0 = -EINTR;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल -ERESTARTNOINTR:
	करो_restart:
		regs->d0 = regs->orig_d0;
		regs->pc -= 2;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक err;
	/* are we from a प्रणाली call? */
	अगर (regs->orig_d0 >= 0)
		/* If so, check प्रणाली call restarting.. */
		handle_restart(regs, &ksig->ka, 1);

	/* set up the stack frame */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err = setup_rt_frame(ksig, oldset, regs);
	अन्यथा
		err = setup_frame(ksig, oldset, regs);

	संकेत_setup_करोne(err, ksig, 0);

	अगर (test_thपढ़ो_flag(TIF_DELAYED_TRACE)) अणु
		regs->sr &= ~0x8000;
		send_sig(SIGTRAP, current, 1);
	पूर्ण
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	current->thपढ़ो.esp0 = (अचिन्हित दीर्घ) regs;

	अगर (get_संकेत(&ksig)) अणु
		/* Whee!  Actually deliver the संकेत.  */
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (regs->orig_d0 >= 0)
		/* Restart the प्रणाली call - no handlers present */
		handle_restart(regs, शून्य, 0);

	/* If there's no संकेत to deliver, we just restore the saved mask.  */
	restore_saved_sigmask();
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL) ||
	    test_thपढ़ो_flag(TIF_SIGPENDING))
		करो_संकेत(regs);

	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण
