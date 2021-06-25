<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*    Signal support क्रम 32-bit kernel builds
 *
 *    Copyright (C) 2001 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2006 Kyle McMartin <kyle at parisc-linux.org>
 *
 *    Code was mostly borrowed from kernel/संकेत.c.
 *    See kernel/संकेत.c क्रम additional Copyrights.
 */

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/unistd.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <linux/uaccess.h>

#समावेश "signal32.h"

#घोषणा DEBUG_COMPAT_SIG 0 
#घोषणा DEBUG_COMPAT_SIG_LEVEL 2

#अगर DEBUG_COMPAT_SIG
#घोषणा DBG(LEVEL, ...) \
	((DEBUG_COMPAT_SIG_LEVEL >= LEVEL) \
	? prपूर्णांकk(__VA_ARGS__) : (व्योम) 0)
#अन्यथा
#घोषणा DBG(LEVEL, ...)
#पूर्ण_अगर

दीर्घ
restore_sigcontext32(काष्ठा compat_sigcontext __user *sc, काष्ठा compat_regfile __user * rf,
		काष्ठा pt_regs *regs)
अणु
	दीर्घ err = 0;
	compat_uपूर्णांक_t compat_reg;
	compat_uपूर्णांक_t compat_regt;
	पूर्णांक regn;
	
	/* When loading 32-bit values पूर्णांकo 64-bit रेजिस्टरs make
	   sure to clear the upper 32-bits */
	DBG(2,"restore_sigcontext32: PER_LINUX32 process\n");
	DBG(2,"restore_sigcontext32: sc = 0x%p, rf = 0x%p, regs = 0x%p\n", sc, rf, regs);
	DBG(2,"restore_sigcontext32: compat_sigcontext is %#lx bytes\n", माप(*sc));
	क्रम(regn=0; regn < 32; regn++)अणु
		err |= __get_user(compat_reg,&sc->sc_gr[regn]);
		regs->gr[regn] = compat_reg;
		/* Load upper half */
		err |= __get_user(compat_regt,&rf->rf_gr[regn]);
		regs->gr[regn] = ((u64)compat_regt << 32) | (u64)compat_reg;
		DBG(3,"restore_sigcontext32: gr%02d = %#lx (%#x / %#x)\n", 
				regn, regs->gr[regn], compat_regt, compat_reg);
	पूर्ण
	DBG(2,"restore_sigcontext32: sc->sc_fr = 0x%p (%#lx)\n",sc->sc_fr, माप(sc->sc_fr));
	/* XXX: BE WARNED FR's are 64-BIT! */
	err |= __copy_from_user(regs->fr, sc->sc_fr, माप(regs->fr));
		
	/* Better safe than sorry, pass __get_user two things of
	   the same size and let gcc करो the upward conversion to 
	   64-bits */		
	err |= __get_user(compat_reg, &sc->sc_iaoq[0]);
	/* Load upper half */
	err |= __get_user(compat_regt, &rf->rf_iaoq[0]);
	regs->iaoq[0] = ((u64)compat_regt << 32) | (u64)compat_reg;
	DBG(2,"restore_sigcontext32: upper half of iaoq[0] = %#lx\n", compat_regt);
	DBG(2,"restore_sigcontext32: sc->sc_iaoq[0] = %p => %#x\n", 
			&sc->sc_iaoq[0], compat_reg);

	err |= __get_user(compat_reg, &sc->sc_iaoq[1]);
	/* Load upper half */
	err |= __get_user(compat_regt, &rf->rf_iaoq[1]);
	regs->iaoq[1] = ((u64)compat_regt << 32) | (u64)compat_reg;
	DBG(2,"restore_sigcontext32: upper half of iaoq[1] = %#lx\n", compat_regt);
	DBG(2,"restore_sigcontext32: sc->sc_iaoq[1] = %p => %#x\n", 
			&sc->sc_iaoq[1],compat_reg);	
	DBG(2,"restore_sigcontext32: iaoq is %#lx / %#lx\n", 
			regs->iaoq[0],regs->iaoq[1]);		
		
	err |= __get_user(compat_reg, &sc->sc_iasq[0]);
	/* Load the upper half क्रम iasq */
	err |= __get_user(compat_regt, &rf->rf_iasq[0]);
	regs->iasq[0] = ((u64)compat_regt << 32) | (u64)compat_reg;
	DBG(2,"restore_sigcontext32: upper half of iasq[0] = %#lx\n", compat_regt);
	
	err |= __get_user(compat_reg, &sc->sc_iasq[1]);
	/* Load the upper half क्रम iasq */
	err |= __get_user(compat_regt, &rf->rf_iasq[1]);
	regs->iasq[1] = ((u64)compat_regt << 32) | (u64)compat_reg;
	DBG(2,"restore_sigcontext32: upper half of iasq[1] = %#lx\n", compat_regt);
	DBG(2,"restore_sigcontext32: iasq is %#lx / %#lx\n", 
		regs->iasq[0],regs->iasq[1]);		

	err |= __get_user(compat_reg, &sc->sc_sar);
	/* Load the upper half क्रम sar */
	err |= __get_user(compat_regt, &rf->rf_sar);
	regs->sar = ((u64)compat_regt << 32) | (u64)compat_reg;	
	DBG(2,"restore_sigcontext32: upper_half & sar = %#lx\n", compat_regt);	
	DBG(2,"restore_sigcontext32: sar is %#lx\n", regs->sar);		
	DBG(2,"restore_sigcontext32: r28 is %ld\n", regs->gr[28]);
	
	वापस err;
पूर्ण

/*
 * Set up the sigcontext काष्ठाure क्रम this process.
 * This is not an easy task अगर the kernel is 64-bit, it will require
 * that we examine the process personality to determine अगर we need to
 * truncate क्रम a 32-bit userspace.
 */
दीर्घ
setup_sigcontext32(काष्ठा compat_sigcontext __user *sc, काष्ठा compat_regfile __user * rf, 
		काष्ठा pt_regs *regs, पूर्णांक in_syscall)		 
अणु
	compat_पूर्णांक_t flags = 0;
	दीर्घ err = 0;
	compat_uपूर्णांक_t compat_reg;
	compat_uपूर्णांक_t compat_regb;
	पूर्णांक regn;
	
	अगर (on_sig_stack((अचिन्हित दीर्घ) sc))
		flags |= PARISC_SC_FLAG_ONSTACK;
	
	अगर (in_syscall) अणु
		
		DBG(1,"setup_sigcontext32: in_syscall\n");
		
		flags |= PARISC_SC_FLAG_IN_SYSCALL;
		/* Truncate gr31 */
		compat_reg = (compat_uपूर्णांक_t)(regs->gr[31]);
		/* regs->iaoq is undefined in the syscall वापस path */
		err |= __put_user(compat_reg, &sc->sc_iaoq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[0] = %p <= %#x\n",
				&sc->sc_iaoq[0], compat_reg);
		
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->gr[31] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iaoq[0]);
		DBG(2,"setup_sigcontext32: upper half iaoq[0] = %#x\n", compat_reg);
		
		
		compat_reg = (compat_uपूर्णांक_t)(regs->gr[31]+4);
		err |= __put_user(compat_reg, &sc->sc_iaoq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[1] = %p <= %#x\n",
				&sc->sc_iaoq[1], compat_reg);
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)((regs->gr[31]+4) >> 32);
		err |= __put_user(compat_reg, &rf->rf_iaoq[1]);
		DBG(2,"setup_sigcontext32: upper half iaoq[1] = %#x\n", compat_reg);
		
		/* Truncate sr3 */
		compat_reg = (compat_uपूर्णांक_t)(regs->sr[3]);
		err |= __put_user(compat_reg, &sc->sc_iasq[0]);
		err |= __put_user(compat_reg, &sc->sc_iasq[1]);		
		
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->sr[3] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iasq[0]);
		err |= __put_user(compat_reg, &rf->rf_iasq[1]);		
		
		DBG(2,"setup_sigcontext32: upper half iasq[0] = %#x\n", compat_reg);
		DBG(2,"setup_sigcontext32: upper half iasq[1] = %#x\n", compat_reg);		
		DBG(1,"setup_sigcontext32: iaoq %#lx / %#lx\n",				
			regs->gr[31], regs->gr[31]+4);
		
	पूर्ण अन्यथा अणु
		
		compat_reg = (compat_uपूर्णांक_t)(regs->iaoq[0]);
		err |= __put_user(compat_reg, &sc->sc_iaoq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[0] = %p <= %#x\n",
				&sc->sc_iaoq[0], compat_reg);
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->iaoq[0] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iaoq[0]);	
		DBG(2,"setup_sigcontext32: upper half iaoq[0] = %#x\n", compat_reg);
		
		compat_reg = (compat_uपूर्णांक_t)(regs->iaoq[1]);
		err |= __put_user(compat_reg, &sc->sc_iaoq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[1] = %p <= %#x\n",
				&sc->sc_iaoq[1], compat_reg);
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->iaoq[1] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iaoq[1]);
		DBG(2,"setup_sigcontext32: upper half iaoq[1] = %#x\n", compat_reg);
		
		
		compat_reg = (compat_uपूर्णांक_t)(regs->iasq[0]);
		err |= __put_user(compat_reg, &sc->sc_iasq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iasq[0] = %p <= %#x\n",
				&sc->sc_iasq[0], compat_reg);
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->iasq[0] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iasq[0]);
		DBG(2,"setup_sigcontext32: upper half iasq[0] = %#x\n", compat_reg);
		
		
		compat_reg = (compat_uपूर्णांक_t)(regs->iasq[1]);
		err |= __put_user(compat_reg, &sc->sc_iasq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iasq[1] = %p <= %#x\n",
				&sc->sc_iasq[1], compat_reg);
		/* Store upper half */
		compat_reg = (compat_uपूर्णांक_t)(regs->iasq[1] >> 32);
		err |= __put_user(compat_reg, &rf->rf_iasq[1]);
		DBG(2,"setup_sigcontext32: upper half iasq[1] = %#x\n", compat_reg);

		/* Prपूर्णांक out the IAOQ क्रम debugging */		
		DBG(1,"setup_sigcontext32: ia0q %#lx / %#lx\n", 
			regs->iaoq[0], regs->iaoq[1]);
	पूर्ण

	err |= __put_user(flags, &sc->sc_flags);
	
	DBG(1,"setup_sigcontext32: Truncating general registers.\n");
	
	क्रम(regn=0; regn < 32; regn++)अणु
		/* Truncate a general रेजिस्टर */
		compat_reg = (compat_uपूर्णांक_t)(regs->gr[regn]);
		err |= __put_user(compat_reg, &sc->sc_gr[regn]);
		/* Store upper half */
		compat_regb = (compat_uपूर्णांक_t)(regs->gr[regn] >> 32);
		err |= __put_user(compat_regb, &rf->rf_gr[regn]);

		/* DEBUG: Write out the "upper / lower" रेजिस्टर data */
		DBG(2,"setup_sigcontext32: gr%02d = %#x / %#x\n", regn, 
				compat_regb, compat_reg);
	पूर्ण
	
	/* Copy the भग्नing poपूर्णांक रेजिस्टरs (same size)
	   XXX: BE WARNED FR's are 64-BIT! */	
	DBG(1,"setup_sigcontext32: Copying from regs to sc, "
	      "sc->sc_fr size = %#lx, regs->fr size = %#lx\n",
		माप(regs->fr), माप(sc->sc_fr));
	err |= __copy_to_user(sc->sc_fr, regs->fr, माप(regs->fr));

	compat_reg = (compat_uपूर्णांक_t)(regs->sar);
	err |= __put_user(compat_reg, &sc->sc_sar);
	DBG(2,"setup_sigcontext32: sar is %#x\n", compat_reg);
	/* Store upper half */
	compat_reg = (compat_uपूर्णांक_t)(regs->sar >> 32);
	err |= __put_user(compat_reg, &rf->rf_sar);	
	DBG(2,"setup_sigcontext32: upper half sar = %#x\n", compat_reg);
	DBG(1,"setup_sigcontext32: r28 is %ld\n", regs->gr[28]);

	वापस err;
पूर्ण
