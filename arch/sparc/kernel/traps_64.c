<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* arch/sparc64/kernel/traps.c
 *
 * Copyright (C) 1995,1997,2008,2009,2012 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997,1999,2000 Jakub Jelinek (jakub@redhat.com)
 */

/*
 * I like traps on v9, :))))
 */

#समावेश <linux/extable.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/linkage.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/reboot.h>
#समावेश <linux/gfp.h>
#समावेश <linux/context_tracking.h>

#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/lsu.h>
#समावेश <यंत्र/dcu.h>
#समावेश <यंत्र/estate.h>
#समावेश <यंत्र/chafsr.h>
#समावेश <यंत्र/sfafsr.h>
#समावेश <यंत्र/psrcompat.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/memctrl.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/setup.h>

#समावेश "entry.h"
#समावेश "kernel.h"
#समावेश "kstack.h"

/* When an irrecoverable trap occurs at tl > 0, the trap entry
 * code logs the trap state रेजिस्टरs at every level in the trap
 * stack.  It is found at (pt_regs + माप(pt_regs)) and the layout
 * is as follows:
 */
काष्ठा tl1_traplog अणु
	काष्ठा अणु
		अचिन्हित दीर्घ tstate;
		अचिन्हित दीर्घ tpc;
		अचिन्हित दीर्घ tnpc;
		अचिन्हित दीर्घ tt;
	पूर्ण trapstack[4];
	अचिन्हित दीर्घ tl;
पूर्ण;

अटल व्योम dump_tl1_traplog(काष्ठा tl1_traplog *p)
अणु
	पूर्णांक i, limit;

	prपूर्णांकk(KERN_EMERG "TRAPLOG: Error at trap level 0x%lx, "
	       "dumping track stack.\n", p->tl);

	limit = (tlb_type == hypervisor) ? 2 : 4;
	क्रम (i = 0; i < limit; i++) अणु
		prपूर्णांकk(KERN_EMERG
		       "TRAPLOG: Trap level %d TSTATE[%016lx] TPC[%016lx] "
		       "TNPC[%016lx] TT[%lx]\n",
		       i + 1,
		       p->trapstack[i].tstate, p->trapstack[i].tpc,
		       p->trapstack[i].tnpc, p->trapstack[i].tt);
		prपूर्णांकk("TRAPLOG: TPC<%pS>\n", (व्योम *) p->trapstack[i].tpc);
	पूर्ण
पूर्ण

व्योम bad_trap(काष्ठा pt_regs *regs, दीर्घ lvl)
अणु
	अक्षर buffer[36];

	अगर (notअगरy_die(DIE_TRAP, "bad trap", regs,
		       0, lvl, SIGTRAP) == NOTIFY_STOP)
		वापस;

	अगर (lvl < 0x100) अणु
		प्र_लिखो(buffer, "Bad hw trap %lx at tl0\n", lvl);
		die_अगर_kernel(buffer, regs);
	पूर्ण

	lvl -= 0x100;
	अगर (regs->tstate & TSTATE_PRIV) अणु
		प्र_लिखो(buffer, "Kernel bad sw trap %lx", lvl);
		die_अगर_kernel(buffer, regs);
	पूर्ण
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_अवैध, ILL_ILLTRP,
			(व्योम __user *)regs->tpc, lvl);
पूर्ण

व्योम bad_trap_tl1(काष्ठा pt_regs *regs, दीर्घ lvl)
अणु
	अक्षर buffer[36];
	
	अगर (notअगरy_die(DIE_TRAP_TL1, "bad trap tl1", regs,
		       0, lvl, SIGTRAP) == NOTIFY_STOP)
		वापस;

	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));

	प्र_लिखो (buffer, "Bad trap %lx at tl>0", lvl);
	die_अगर_kernel (buffer, regs);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
व्योम करो_BUG(स्थिर अक्षर *file, पूर्णांक line)
अणु
	bust_spinlocks(1);
	prपूर्णांकk("kernel BUG at %s:%d!\n", file, line);
पूर्ण
EXPORT_SYMBOL(करो_BUG);
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(dimm_handler_lock);
अटल dimm_prपूर्णांकer_t dimm_handler;

अटल पूर्णांक प्र_लिखो_dimm(पूर्णांक synd_code, अचिन्हित दीर्घ paddr, अक्षर *buf, पूर्णांक buflen)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENODEV;

	spin_lock_irqsave(&dimm_handler_lock, flags);
	अगर (dimm_handler) अणु
		ret = dimm_handler(synd_code, paddr, buf, buflen);
	पूर्ण अन्यथा अगर (tlb_type == spitfire) अणु
		अगर (prom_getunumber(synd_code, paddr, buf, buflen) == -1)
			ret = -EINVAL;
		अन्यथा
			ret = 0;
	पूर्ण अन्यथा
		ret = -ENODEV;
	spin_unlock_irqrestore(&dimm_handler_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक रेजिस्टर_dimm_prपूर्णांकer(dimm_prपूर्णांकer_t func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&dimm_handler_lock, flags);
	अगर (!dimm_handler)
		dimm_handler = func;
	अन्यथा
		ret = -EEXIST;
	spin_unlock_irqrestore(&dimm_handler_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_dimm_prपूर्णांकer);

व्योम unरेजिस्टर_dimm_prपूर्णांकer(dimm_prपूर्णांकer_t func)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dimm_handler_lock, flags);
	अगर (dimm_handler == func)
		dimm_handler = शून्य;
	spin_unlock_irqrestore(&dimm_handler_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_dimm_prपूर्णांकer);

व्योम spitfire_insn_access_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfsr, अचिन्हित दीर्घ sfar)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "instruction access exception", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		जाओ out;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		prपूर्णांकk("spitfire_insn_access_exception: SFSR[%016lx] "
		       "SFAR[%016lx], going.\n", sfsr, sfar);
		die_अगर_kernel("Iax", regs);
	पूर्ण
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_अंश, SEGV_MAPERR,
			(व्योम __user *)regs->tpc, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम spitfire_insn_access_exception_tl1(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfsr, अचिन्हित दीर्घ sfar)
अणु
	अगर (notअगरy_die(DIE_TRAP_TL1, "instruction access exception tl1", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		वापस;

	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	spitfire_insn_access_exception(regs, sfsr, sfar);
पूर्ण

व्योम sun4v_insn_access_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ type_ctx)
अणु
	अचिन्हित लघु type = (type_ctx >> 16);
	अचिन्हित लघु ctx  = (type_ctx & 0xffff);

	अगर (notअगरy_die(DIE_TRAP, "instruction access exception", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		वापस;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		prपूर्णांकk("sun4v_insn_access_exception: ADDR[%016lx] "
		       "CTX[%04x] TYPE[%04x], going.\n",
		       addr, ctx, type);
		die_अगर_kernel("Iax", regs);
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_अंश, SEGV_MAPERR, (व्योम __user *) addr, 0);
पूर्ण

व्योम sun4v_insn_access_exception_tl1(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ type_ctx)
अणु
	अगर (notअगरy_die(DIE_TRAP_TL1, "instruction access exception tl1", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		वापस;

	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	sun4v_insn_access_exception(regs, addr, type_ctx);
पूर्ण

bool is_no_fault_exception(काष्ठा pt_regs *regs)
अणु
	अचिन्हित अक्षर asi;
	u32 insn;

	अगर (get_user(insn, (u32 __user *)regs->tpc) == -EFAULT)
		वापस false;

	/*
	 * Must करो a little inकाष्ठाion decoding here in order to
	 * decide on a course of action. The bits of पूर्णांकerest are:
	 *  insn[31:30] = op, where 3 indicates the load/store group
	 *  insn[24:19] = op3, which identअगरies inभागidual opcodes
	 *  insn[13] indicates an immediate offset
	 *  op3[4]=1 identअगरies alternate space inकाष्ठाions
	 *  op3[5:4]=3 identअगरies भग्नing poपूर्णांक inकाष्ठाions
	 *  op3[2]=1 identअगरies stores
	 * See "Opcode Maps" in the appendix of any Sparc V9
	 * architecture spec क्रम full details.
	 */
	अगर ((insn & 0xc0800000) == 0xc0800000) अणु    /* op=3, op3[4]=1   */
		अगर (insn & 0x2000)		    /* immediate offset */
			asi = (regs->tstate >> 24); /* saved %asi       */
		अन्यथा
			asi = (insn >> 5);	    /* immediate asi    */
		अगर ((asi & 0xf6) == ASI_PNF) अणु
			अगर (insn & 0x200000)        /* op3[2], stores   */
				वापस false;
			अगर (insn & 0x1000000)       /* op3[5:4]=3 (fp)  */
				handle_ldf_stq(insn, regs);
			अन्यथा
				handle_ld_nf(insn, regs);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

व्योम spitfire_data_access_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfsr, अचिन्हित दीर्घ sfar)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "data access exception", regs,
		       0, 0x30, SIGTRAP) == NOTIFY_STOP)
		जाओ out;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		/* Test अगर this comes from uaccess places. */
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			/* Ouch, somebody is trying VM hole tricks on us... */
#अगर_घोषित DEBUG_EXCEPTIONS
			prपूर्णांकk("Exception: PC<%016lx> faddr<UNKNOWN>\n", regs->tpc);
			prपूर्णांकk("EX_TABLE: insn<%016lx> fixup<%016lx>\n",
			       regs->tpc, entry->fixup);
#पूर्ण_अगर
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			जाओ out;
		पूर्ण
		/* Shit... */
		prपूर्णांकk("spitfire_data_access_exception: SFSR[%016lx] "
		       "SFAR[%016lx], going.\n", sfsr, sfar);
		die_अगर_kernel("Dax", regs);
	पूर्ण

	अगर (is_no_fault_exception(regs))
		वापस;

	क्रमce_sig_fault(संक_अंश, SEGV_MAPERR, (व्योम __user *)sfar, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम spitfire_data_access_exception_tl1(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfsr, अचिन्हित दीर्घ sfar)
अणु
	अगर (notअगरy_die(DIE_TRAP_TL1, "data access exception tl1", regs,
		       0, 0x30, SIGTRAP) == NOTIFY_STOP)
		वापस;

	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	spitfire_data_access_exception(regs, sfsr, sfar);
पूर्ण

व्योम sun4v_data_access_exception(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ type_ctx)
अणु
	अचिन्हित लघु type = (type_ctx >> 16);
	अचिन्हित लघु ctx  = (type_ctx & 0xffff);

	अगर (notअगरy_die(DIE_TRAP, "data access exception", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		वापस;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		/* Test अगर this comes from uaccess places. */
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			/* Ouch, somebody is trying VM hole tricks on us... */
#अगर_घोषित DEBUG_EXCEPTIONS
			prपूर्णांकk("Exception: PC<%016lx> faddr<UNKNOWN>\n", regs->tpc);
			prपूर्णांकk("EX_TABLE: insn<%016lx> fixup<%016lx>\n",
			       regs->tpc, entry->fixup);
#पूर्ण_अगर
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस;
		पूर्ण
		prपूर्णांकk("sun4v_data_access_exception: ADDR[%016lx] "
		       "CTX[%04x] TYPE[%04x], going.\n",
		       addr, ctx, type);
		die_अगर_kernel("Dax", regs);
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	अगर (is_no_fault_exception(regs))
		वापस;

	/* MCD (Memory Corruption Detection) disabled trap (TT=0x19) in HV
	 * is vectored thorugh data access exception trap with fault type
	 * set to HV_FAULT_TYPE_MCD_DIS. Check क्रम MCD disabled trap.
	 * Accessing an address with invalid ASI क्रम the address, क्रम
	 * example setting an ADI tag on an address with ASI_MCD_PRIMARY
	 * when TTE.mcd is not set क्रम the VA, is also vectored पूर्णांकo
	 * kerbel by HV as data access exception with fault type set to
	 * HV_FAULT_TYPE_INV_ASI.
	 */
	चयन (type) अणु
	हाल HV_FAULT_TYPE_INV_ASI:
		क्रमce_sig_fault(संक_अवैध, ILL_ILLADR, (व्योम __user *)addr, 0);
		अवरोध;
	हाल HV_FAULT_TYPE_MCD_DIS:
		क्रमce_sig_fault(संक_अंश, SEGV_ACCADI, (व्योम __user *)addr, 0);
		अवरोध;
	शेष:
		क्रमce_sig_fault(संक_अंश, SEGV_MAPERR, (व्योम __user *)addr, 0);
		अवरोध;
	पूर्ण
पूर्ण

व्योम sun4v_data_access_exception_tl1(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ type_ctx)
अणु
	अगर (notअगरy_die(DIE_TRAP_TL1, "data access exception tl1", regs,
		       0, 0x8, SIGTRAP) == NOTIFY_STOP)
		वापस;

	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	sun4v_data_access_exception(regs, addr, type_ctx);
पूर्ण

#अगर_घोषित CONFIG_PCI
#समावेश "pci_impl.h"
#पूर्ण_अगर

/* When access exceptions happen, we must करो this. */
अटल व्योम spitfire_clean_and_reenable_l1_caches(व्योम)
अणु
	अचिन्हित दीर्घ va;

	अगर (tlb_type != spitfire)
		BUG();

	/* Clean 'em. */
	क्रम (va =  0; va < (PAGE_SIZE << 1); va += 32) अणु
		spitfire_put_icache_tag(va, 0x0);
		spitfire_put_dcache_tag(va, 0x0);
	पूर्ण

	/* Re-enable in LSU. */
	__यंत्र__ __अस्थिर__("flush %%g6\n\t"
			     "membar #Sync\n\t"
			     "stxa %0, [%%g0] %1\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (LSU_CONTROL_IC | LSU_CONTROL_DC |
				    LSU_CONTROL_IM | LSU_CONTROL_DM),
			     "i" (ASI_LSU_CONTROL)
			     : "memory");
पूर्ण

अटल व्योम spitfire_enable_estate_errors(व्योम)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%%g0] %1\n\t"
			     "membar	#Sync"
			     : /* no outमाला_दो */
			     : "r" (ESTATE_ERR_ALL),
			       "i" (ASI_ESTATE_ERROR_EN));
पूर्ण

अटल अक्षर ecc_syndrome_table[] = अणु
	0x4c, 0x40, 0x41, 0x48, 0x42, 0x48, 0x48, 0x49,
	0x43, 0x48, 0x48, 0x49, 0x48, 0x49, 0x49, 0x4a,
	0x44, 0x48, 0x48, 0x20, 0x48, 0x39, 0x4b, 0x48,
	0x48, 0x25, 0x31, 0x48, 0x28, 0x48, 0x48, 0x2c,
	0x45, 0x48, 0x48, 0x21, 0x48, 0x3d, 0x04, 0x48,
	0x48, 0x4b, 0x35, 0x48, 0x2d, 0x48, 0x48, 0x29,
	0x48, 0x00, 0x01, 0x48, 0x0a, 0x48, 0x48, 0x4b,
	0x0f, 0x48, 0x48, 0x4b, 0x48, 0x49, 0x49, 0x48,
	0x46, 0x48, 0x48, 0x2a, 0x48, 0x3b, 0x27, 0x48,
	0x48, 0x4b, 0x33, 0x48, 0x22, 0x48, 0x48, 0x2e,
	0x48, 0x19, 0x1d, 0x48, 0x1b, 0x4a, 0x48, 0x4b,
	0x1f, 0x48, 0x4a, 0x4b, 0x48, 0x4b, 0x4b, 0x48,
	0x48, 0x4b, 0x24, 0x48, 0x07, 0x48, 0x48, 0x36,
	0x4b, 0x48, 0x48, 0x3e, 0x48, 0x30, 0x38, 0x48,
	0x49, 0x48, 0x48, 0x4b, 0x48, 0x4b, 0x16, 0x48,
	0x48, 0x12, 0x4b, 0x48, 0x49, 0x48, 0x48, 0x4b,
	0x47, 0x48, 0x48, 0x2f, 0x48, 0x3f, 0x4b, 0x48,
	0x48, 0x06, 0x37, 0x48, 0x23, 0x48, 0x48, 0x2b,
	0x48, 0x05, 0x4b, 0x48, 0x4b, 0x48, 0x48, 0x32,
	0x26, 0x48, 0x48, 0x3a, 0x48, 0x34, 0x3c, 0x48,
	0x48, 0x11, 0x15, 0x48, 0x13, 0x4a, 0x48, 0x4b,
	0x17, 0x48, 0x4a, 0x4b, 0x48, 0x4b, 0x4b, 0x48,
	0x49, 0x48, 0x48, 0x4b, 0x48, 0x4b, 0x1e, 0x48,
	0x48, 0x1a, 0x4b, 0x48, 0x49, 0x48, 0x48, 0x4b,
	0x48, 0x08, 0x0d, 0x48, 0x02, 0x48, 0x48, 0x49,
	0x03, 0x48, 0x48, 0x49, 0x48, 0x4b, 0x4b, 0x48,
	0x49, 0x48, 0x48, 0x49, 0x48, 0x4b, 0x10, 0x48,
	0x48, 0x14, 0x4b, 0x48, 0x4b, 0x48, 0x48, 0x4b,
	0x49, 0x48, 0x48, 0x49, 0x48, 0x4b, 0x18, 0x48,
	0x48, 0x1c, 0x4b, 0x48, 0x4b, 0x48, 0x48, 0x4b,
	0x4a, 0x0c, 0x09, 0x48, 0x0e, 0x48, 0x48, 0x4b,
	0x0b, 0x48, 0x48, 0x4b, 0x48, 0x4b, 0x4b, 0x4a
पूर्ण;

अटल अक्षर *syndrome_unknown = "<Unknown>";

अटल व्योम spitfire_log_udb_syndrome(अचिन्हित दीर्घ afar, अचिन्हित दीर्घ udbh, अचिन्हित दीर्घ udbl, अचिन्हित दीर्घ bit)
अणु
	अचिन्हित लघु scode;
	अक्षर memmod_str[64], *p;

	अगर (udbl & bit) अणु
		scode = ecc_syndrome_table[udbl & 0xff];
		अगर (प्र_लिखो_dimm(scode, afar, memmod_str, माप(memmod_str)) < 0)
			p = syndrome_unknown;
		अन्यथा
			p = memmod_str;
		prपूर्णांकk(KERN_WARNING "CPU[%d]: UDBL Syndrome[%x] "
		       "Memory Module \"%s\"\n",
		       smp_processor_id(), scode, p);
	पूर्ण

	अगर (udbh & bit) अणु
		scode = ecc_syndrome_table[udbh & 0xff];
		अगर (प्र_लिखो_dimm(scode, afar, memmod_str, माप(memmod_str)) < 0)
			p = syndrome_unknown;
		अन्यथा
			p = memmod_str;
		prपूर्णांकk(KERN_WARNING "CPU[%d]: UDBH Syndrome[%x] "
		       "Memory Module \"%s\"\n",
		       smp_processor_id(), scode, p);
	पूर्ण

पूर्ण

अटल व्योम spitfire_cee_log(अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar, अचिन्हित दीर्घ udbh, अचिन्हित दीर्घ udbl, पूर्णांक tl1, काष्ठा pt_regs *regs)
अणु

	prपूर्णांकk(KERN_WARNING "CPU[%d]: Correctable ECC Error "
	       "AFSR[%lx] AFAR[%016lx] UDBL[%lx] UDBH[%lx] TL>1[%d]\n",
	       smp_processor_id(), afsr, afar, udbl, udbh, tl1);

	spitfire_log_udb_syndrome(afar, udbh, udbl, UDBE_CE);

	/* We always log it, even अगर someone is listening क्रम this
	 * trap.
	 */
	notअगरy_die(DIE_TRAP, "Correctable ECC Error", regs,
		   0, TRAP_TYPE_CEE, SIGTRAP);

	/* The Correctable ECC Error trap करोes not disable I/D caches.  So
	 * we only have to restore the ESTATE Error Enable रेजिस्टर.
	 */
	spitfire_enable_estate_errors();
पूर्ण

अटल व्योम spitfire_ue_log(अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar, अचिन्हित दीर्घ udbh, अचिन्हित दीर्घ udbl, अचिन्हित दीर्घ tt, पूर्णांक tl1, काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk(KERN_WARNING "CPU[%d]: Uncorrectable Error AFSR[%lx] "
	       "AFAR[%lx] UDBL[%lx] UDBH[%ld] TT[%lx] TL>1[%d]\n",
	       smp_processor_id(), afsr, afar, udbl, udbh, tt, tl1);

	/* XXX add more human मित्रly logging of the error status
	 * XXX as is implemented क्रम cheetah
	 */

	spitfire_log_udb_syndrome(afar, udbh, udbl, UDBE_UE);

	/* We always log it, even अगर someone is listening क्रम this
	 * trap.
	 */
	notअगरy_die(DIE_TRAP, "Uncorrectable Error", regs,
		   0, tt, SIGTRAP);

	अगर (regs->tstate & TSTATE_PRIV) अणु
		अगर (tl1)
			dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
		die_अगर_kernel("UE", regs);
	पूर्ण

	/* XXX need more पूर्णांकelligent processing here, such as is implemented
	 * XXX क्रम cheetah errors, in fact अगर the E-cache still holds the
	 * XXX line with bad parity this will loop
	 */

	spitfire_clean_and_reenable_l1_caches();
	spitfire_enable_estate_errors();

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(SIGBUS, BUS_OBJERR, (व्योम *)0, 0);
पूर्ण

व्योम spitfire_access_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ status_encoded, अचिन्हित दीर्घ afar)
अणु
	अचिन्हित दीर्घ afsr, tt, udbh, udbl;
	पूर्णांक tl1;

	afsr = (status_encoded & SFSTAT_AFSR_MASK) >> SFSTAT_AFSR_SHIFT;
	tt = (status_encoded & SFSTAT_TRAP_TYPE) >> SFSTAT_TRAP_TYPE_SHIFT;
	tl1 = (status_encoded & SFSTAT_TL_GT_ONE) ? 1 : 0;
	udbl = (status_encoded & SFSTAT_UDBL_MASK) >> SFSTAT_UDBL_SHIFT;
	udbh = (status_encoded & SFSTAT_UDBH_MASK) >> SFSTAT_UDBH_SHIFT;

#अगर_घोषित CONFIG_PCI
	अगर (tt == TRAP_TYPE_DAE &&
	    pci_poke_in_progress && pci_poke_cpu == smp_processor_id()) अणु
		spitfire_clean_and_reenable_l1_caches();
		spitfire_enable_estate_errors();

		pci_poke_faulted = 1;
		regs->tnpc = regs->tpc + 4;
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (afsr & SFAFSR_UE)
		spitfire_ue_log(afsr, afar, udbh, udbl, tt, tl1, regs);

	अगर (tt == TRAP_TYPE_CEE) अणु
		/* Handle the हाल where we took a CEE trap, but ACK'd
		 * only the UE state in the UDB error रेजिस्टरs.
		 */
		अगर (afsr & SFAFSR_UE) अणु
			अगर (udbh & UDBE_CE) अणु
				__यंत्र__ __अस्थिर__(
					"stxa	%0, [%1] %2\n\t"
					"membar	#Sync"
					: /* no outमाला_दो */
					: "r" (udbh & UDBE_CE),
					  "r" (0x0), "i" (ASI_UDB_ERROR_W));
			पूर्ण
			अगर (udbl & UDBE_CE) अणु
				__यंत्र__ __अस्थिर__(
					"stxa	%0, [%1] %2\n\t"
					"membar	#Sync"
					: /* no outमाला_दो */
					: "r" (udbl & UDBE_CE),
					  "r" (0x18), "i" (ASI_UDB_ERROR_W));
			पूर्ण
		पूर्ण

		spitfire_cee_log(afsr, afar, udbh, udbl, tl1, regs);
	पूर्ण
पूर्ण

पूर्णांक cheetah_pcache_क्रमced_on;

व्योम cheetah_enable_pcache(व्योम)
अणु
	अचिन्हित दीर्घ dcr;

	prपूर्णांकk("CHEETAH: Enabling P-Cache on cpu %d.\n",
	       smp_processor_id());

	__यंत्र__ __अस्थिर__("ldxa [%%g0] %1, %0"
			     : "=r" (dcr)
			     : "i" (ASI_DCU_CONTROL_REG));
	dcr |= (DCU_PE | DCU_HPE | DCU_SPE | DCU_SL);
	__यंत्र__ __अस्थिर__("stxa %0, [%%g0] %1\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (dcr), "i" (ASI_DCU_CONTROL_REG));
पूर्ण

/* Cheetah error trap handling. */
अटल अचिन्हित दीर्घ ecache_flush_physbase;
अटल अचिन्हित दीर्घ ecache_flush_linesize;
अटल अचिन्हित दीर्घ ecache_flush_size;

/* This table is ordered in priority of errors and matches the
 * AFAR overग_लिखो policy as well.
 */

काष्ठा afsr_error_table अणु
	अचिन्हित दीर्घ mask;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर अक्षर CHAFSR_PERR_msg[] =
	"System interface protocol error";
अटल स्थिर अक्षर CHAFSR_IERR_msg[] =
	"Internal processor error";
अटल स्थिर अक्षर CHAFSR_ISAP_msg[] =
	"System request parity error on incoming address";
अटल स्थिर अक्षर CHAFSR_UCU_msg[] =
	"Uncorrectable E-cache ECC error for ifetch/data";
अटल स्थिर अक्षर CHAFSR_UCC_msg[] =
	"SW Correctable E-cache ECC error for ifetch/data";
अटल स्थिर अक्षर CHAFSR_UE_msg[] =
	"Uncorrectable system bus data ECC error for read";
अटल स्थिर अक्षर CHAFSR_EDU_msg[] =
	"Uncorrectable E-cache ECC error for stmerge/blkld";
अटल स्थिर अक्षर CHAFSR_EMU_msg[] =
	"Uncorrectable system bus MTAG error";
अटल स्थिर अक्षर CHAFSR_WDU_msg[] =
	"Uncorrectable E-cache ECC error for writeback";
अटल स्थिर अक्षर CHAFSR_CPU_msg[] =
	"Uncorrectable ECC error for copyout";
अटल स्थिर अक्षर CHAFSR_CE_msg[] =
	"HW corrected system bus data ECC error for read";
अटल स्थिर अक्षर CHAFSR_EDC_msg[] =
	"HW corrected E-cache ECC error for stmerge/blkld";
अटल स्थिर अक्षर CHAFSR_EMC_msg[] =
	"HW corrected system bus MTAG ECC error";
अटल स्थिर अक्षर CHAFSR_WDC_msg[] =
	"HW corrected E-cache ECC error for writeback";
अटल स्थिर अक्षर CHAFSR_CPC_msg[] =
	"HW corrected ECC error for copyout";
अटल स्थिर अक्षर CHAFSR_TO_msg[] =
	"Unmapped error from system bus";
अटल स्थिर अक्षर CHAFSR_BERR_msg[] =
	"Bus error response from system bus";
अटल स्थिर अक्षर CHAFSR_IVC_msg[] =
	"HW corrected system bus data ECC error for ivec read";
अटल स्थिर अक्षर CHAFSR_IVU_msg[] =
	"Uncorrectable system bus data ECC error for ivec read";
अटल काष्ठा afsr_error_table __cheetah_error_table[] = अणु
	अणु	CHAFSR_PERR,	CHAFSR_PERR_msg		पूर्ण,
	अणु	CHAFSR_IERR,	CHAFSR_IERR_msg		पूर्ण,
	अणु	CHAFSR_ISAP,	CHAFSR_ISAP_msg		पूर्ण,
	अणु	CHAFSR_UCU,	CHAFSR_UCU_msg		पूर्ण,
	अणु	CHAFSR_UCC,	CHAFSR_UCC_msg		पूर्ण,
	अणु	CHAFSR_UE,	CHAFSR_UE_msg		पूर्ण,
	अणु	CHAFSR_EDU,	CHAFSR_EDU_msg		पूर्ण,
	अणु	CHAFSR_EMU,	CHAFSR_EMU_msg		पूर्ण,
	अणु	CHAFSR_WDU,	CHAFSR_WDU_msg		पूर्ण,
	अणु	CHAFSR_CPU,	CHAFSR_CPU_msg		पूर्ण,
	अणु	CHAFSR_CE,	CHAFSR_CE_msg		पूर्ण,
	अणु	CHAFSR_EDC,	CHAFSR_EDC_msg		पूर्ण,
	अणु	CHAFSR_EMC,	CHAFSR_EMC_msg		पूर्ण,
	अणु	CHAFSR_WDC,	CHAFSR_WDC_msg		पूर्ण,
	अणु	CHAFSR_CPC,	CHAFSR_CPC_msg		पूर्ण,
	अणु	CHAFSR_TO,	CHAFSR_TO_msg		पूर्ण,
	अणु	CHAFSR_BERR,	CHAFSR_BERR_msg		पूर्ण,
	/* These two करो not update the AFAR. */
	अणु	CHAFSR_IVC,	CHAFSR_IVC_msg		पूर्ण,
	अणु	CHAFSR_IVU,	CHAFSR_IVU_msg		पूर्ण,
	अणु	0,		शून्य			पूर्ण,
पूर्ण;
अटल स्थिर अक्षर CHPAFSR_DTO_msg[] =
	"System bus unmapped error for prefetch/storequeue-read";
अटल स्थिर अक्षर CHPAFSR_DBERR_msg[] =
	"System bus error for prefetch/storequeue-read";
अटल स्थिर अक्षर CHPAFSR_THCE_msg[] =
	"Hardware corrected E-cache Tag ECC error";
अटल स्थिर अक्षर CHPAFSR_TSCE_msg[] =
	"SW handled correctable E-cache Tag ECC error";
अटल स्थिर अक्षर CHPAFSR_TUE_msg[] =
	"Uncorrectable E-cache Tag ECC error";
अटल स्थिर अक्षर CHPAFSR_DUE_msg[] =
	"System bus uncorrectable data ECC error due to prefetch/store-fill";
अटल काष्ठा afsr_error_table __cheetah_plus_error_table[] = अणु
	अणु	CHAFSR_PERR,	CHAFSR_PERR_msg		पूर्ण,
	अणु	CHAFSR_IERR,	CHAFSR_IERR_msg		पूर्ण,
	अणु	CHAFSR_ISAP,	CHAFSR_ISAP_msg		पूर्ण,
	अणु	CHAFSR_UCU,	CHAFSR_UCU_msg		पूर्ण,
	अणु	CHAFSR_UCC,	CHAFSR_UCC_msg		पूर्ण,
	अणु	CHAFSR_UE,	CHAFSR_UE_msg		पूर्ण,
	अणु	CHAFSR_EDU,	CHAFSR_EDU_msg		पूर्ण,
	अणु	CHAFSR_EMU,	CHAFSR_EMU_msg		पूर्ण,
	अणु	CHAFSR_WDU,	CHAFSR_WDU_msg		पूर्ण,
	अणु	CHAFSR_CPU,	CHAFSR_CPU_msg		पूर्ण,
	अणु	CHAFSR_CE,	CHAFSR_CE_msg		पूर्ण,
	अणु	CHAFSR_EDC,	CHAFSR_EDC_msg		पूर्ण,
	अणु	CHAFSR_EMC,	CHAFSR_EMC_msg		पूर्ण,
	अणु	CHAFSR_WDC,	CHAFSR_WDC_msg		पूर्ण,
	अणु	CHAFSR_CPC,	CHAFSR_CPC_msg		पूर्ण,
	अणु	CHAFSR_TO,	CHAFSR_TO_msg		पूर्ण,
	अणु	CHAFSR_BERR,	CHAFSR_BERR_msg		पूर्ण,
	अणु	CHPAFSR_DTO,	CHPAFSR_DTO_msg		पूर्ण,
	अणु	CHPAFSR_DBERR,	CHPAFSR_DBERR_msg	पूर्ण,
	अणु	CHPAFSR_THCE,	CHPAFSR_THCE_msg	पूर्ण,
	अणु	CHPAFSR_TSCE,	CHPAFSR_TSCE_msg	पूर्ण,
	अणु	CHPAFSR_TUE,	CHPAFSR_TUE_msg		पूर्ण,
	अणु	CHPAFSR_DUE,	CHPAFSR_DUE_msg		पूर्ण,
	/* These two करो not update the AFAR. */
	अणु	CHAFSR_IVC,	CHAFSR_IVC_msg		पूर्ण,
	अणु	CHAFSR_IVU,	CHAFSR_IVU_msg		पूर्ण,
	अणु	0,		शून्य			पूर्ण,
पूर्ण;
अटल स्थिर अक्षर JPAFSR_JETO_msg[] =
	"System interface protocol error, hw timeout caused";
अटल स्थिर अक्षर JPAFSR_SCE_msg[] =
	"Parity error on system snoop results";
अटल स्थिर अक्षर JPAFSR_JEIC_msg[] =
	"System interface protocol error, illegal command detected";
अटल स्थिर अक्षर JPAFSR_JEIT_msg[] =
	"System interface protocol error, illegal ADTYPE detected";
अटल स्थिर अक्षर JPAFSR_OM_msg[] =
	"Out of range memory error has occurred";
अटल स्थिर अक्षर JPAFSR_ETP_msg[] =
	"Parity error on L2 cache tag SRAM";
अटल स्थिर अक्षर JPAFSR_UMS_msg[] =
	"Error due to unsupported store";
अटल स्थिर अक्षर JPAFSR_RUE_msg[] =
	"Uncorrectable ECC error from remote cache/memory";
अटल स्थिर अक्षर JPAFSR_RCE_msg[] =
	"Correctable ECC error from remote cache/memory";
अटल स्थिर अक्षर JPAFSR_BP_msg[] =
	"JBUS parity error on returned read data";
अटल स्थिर अक्षर JPAFSR_WBP_msg[] =
	"JBUS parity error on data for writeback or block store";
अटल स्थिर अक्षर JPAFSR_FRC_msg[] =
	"Foreign read to DRAM incurring correctable ECC error";
अटल स्थिर अक्षर JPAFSR_FRU_msg[] =
	"Foreign read to DRAM incurring uncorrectable ECC error";
अटल काष्ठा afsr_error_table __jalapeno_error_table[] = अणु
	अणु	JPAFSR_JETO,	JPAFSR_JETO_msg		पूर्ण,
	अणु	JPAFSR_SCE,	JPAFSR_SCE_msg		पूर्ण,
	अणु	JPAFSR_JEIC,	JPAFSR_JEIC_msg		पूर्ण,
	अणु	JPAFSR_JEIT,	JPAFSR_JEIT_msg		पूर्ण,
	अणु	CHAFSR_PERR,	CHAFSR_PERR_msg		पूर्ण,
	अणु	CHAFSR_IERR,	CHAFSR_IERR_msg		पूर्ण,
	अणु	CHAFSR_ISAP,	CHAFSR_ISAP_msg		पूर्ण,
	अणु	CHAFSR_UCU,	CHAFSR_UCU_msg		पूर्ण,
	अणु	CHAFSR_UCC,	CHAFSR_UCC_msg		पूर्ण,
	अणु	CHAFSR_UE,	CHAFSR_UE_msg		पूर्ण,
	अणु	CHAFSR_EDU,	CHAFSR_EDU_msg		पूर्ण,
	अणु	JPAFSR_OM,	JPAFSR_OM_msg		पूर्ण,
	अणु	CHAFSR_WDU,	CHAFSR_WDU_msg		पूर्ण,
	अणु	CHAFSR_CPU,	CHAFSR_CPU_msg		पूर्ण,
	अणु	CHAFSR_CE,	CHAFSR_CE_msg		पूर्ण,
	अणु	CHAFSR_EDC,	CHAFSR_EDC_msg		पूर्ण,
	अणु	JPAFSR_ETP,	JPAFSR_ETP_msg		पूर्ण,
	अणु	CHAFSR_WDC,	CHAFSR_WDC_msg		पूर्ण,
	अणु	CHAFSR_CPC,	CHAFSR_CPC_msg		पूर्ण,
	अणु	CHAFSR_TO,	CHAFSR_TO_msg		पूर्ण,
	अणु	CHAFSR_BERR,	CHAFSR_BERR_msg		पूर्ण,
	अणु	JPAFSR_UMS,	JPAFSR_UMS_msg		पूर्ण,
	अणु	JPAFSR_RUE,	JPAFSR_RUE_msg		पूर्ण,
	अणु	JPAFSR_RCE,	JPAFSR_RCE_msg		पूर्ण,
	अणु	JPAFSR_BP,	JPAFSR_BP_msg		पूर्ण,
	अणु	JPAFSR_WBP,	JPAFSR_WBP_msg		पूर्ण,
	अणु	JPAFSR_FRC,	JPAFSR_FRC_msg		पूर्ण,
	अणु	JPAFSR_FRU,	JPAFSR_FRU_msg		पूर्ण,
	/* These two करो not update the AFAR. */
	अणु	CHAFSR_IVU,	CHAFSR_IVU_msg		पूर्ण,
	अणु	0,		शून्य			पूर्ण,
पूर्ण;
अटल काष्ठा afsr_error_table *cheetah_error_table;
अटल अचिन्हित दीर्घ cheetah_afsr_errors;

काष्ठा cheetah_err_info *cheetah_error_log;

अटल अंतरभूत काष्ठा cheetah_err_info *cheetah_get_error_log(अचिन्हित दीर्घ afsr)
अणु
	काष्ठा cheetah_err_info *p;
	पूर्णांक cpu = smp_processor_id();

	अगर (!cheetah_error_log)
		वापस शून्य;

	p = cheetah_error_log + (cpu * 2);
	अगर ((afsr & CHAFSR_TL1) != 0UL)
		p++;

	वापस p;
पूर्ण

बाह्य अचिन्हित पूर्णांक tl0_icpe[], tl1_icpe[];
बाह्य अचिन्हित पूर्णांक tl0_dcpe[], tl1_dcpe[];
बाह्य अचिन्हित पूर्णांक tl0_fecc[], tl1_fecc[];
बाह्य अचिन्हित पूर्णांक tl0_cee[], tl1_cee[];
बाह्य अचिन्हित पूर्णांक tl0_iae[], tl1_iae[];
बाह्य अचिन्हित पूर्णांक tl0_dae[], tl1_dae[];
बाह्य अचिन्हित पूर्णांक cheetah_plus_icpe_trap_vector[], cheetah_plus_icpe_trap_vector_tl1[];
बाह्य अचिन्हित पूर्णांक cheetah_plus_dcpe_trap_vector[], cheetah_plus_dcpe_trap_vector_tl1[];
बाह्य अचिन्हित पूर्णांक cheetah_fecc_trap_vector[], cheetah_fecc_trap_vector_tl1[];
बाह्य अचिन्हित पूर्णांक cheetah_cee_trap_vector[], cheetah_cee_trap_vector_tl1[];
बाह्य अचिन्हित पूर्णांक cheetah_deferred_trap_vector[], cheetah_deferred_trap_vector_tl1[];

व्योम __init cheetah_ecache_flush_init(व्योम)
अणु
	अचिन्हित दीर्घ largest_size, smallest_linesize, order, ver;
	पूर्णांक i, sz;

	/* Scan all cpu device tree nodes, note two values:
	 * 1) largest E-cache size
	 * 2) smallest E-cache line size
	 */
	largest_size = 0UL;
	smallest_linesize = ~0UL;

	क्रम (i = 0; i < NR_CPUS; i++) अणु
		अचिन्हित दीर्घ val;

		val = cpu_data(i).ecache_size;
		अगर (!val)
			जारी;

		अगर (val > largest_size)
			largest_size = val;

		val = cpu_data(i).ecache_line_size;
		अगर (val < smallest_linesize)
			smallest_linesize = val;

	पूर्ण

	अगर (largest_size == 0UL || smallest_linesize == ~0UL) अणु
		prom_म_लिखो("cheetah_ecache_flush_init: Cannot probe cpu E-cache "
			    "parameters.\n");
		prom_halt();
	पूर्ण

	ecache_flush_size = (2 * largest_size);
	ecache_flush_linesize = smallest_linesize;

	ecache_flush_physbase = find_ecache_flush_span(ecache_flush_size);

	अगर (ecache_flush_physbase == ~0UL) अणु
		prom_म_लिखो("cheetah_ecache_flush_init: Cannot find %ld byte "
			    "contiguous physical memory.\n",
			    ecache_flush_size);
		prom_halt();
	पूर्ण

	/* Now allocate error trap reporting scoreboard. */
	sz = NR_CPUS * (2 * माप(काष्ठा cheetah_err_info));
	क्रम (order = 0; order < MAX_ORDER; order++) अणु
		अगर ((PAGE_SIZE << order) >= sz)
			अवरोध;
	पूर्ण
	cheetah_error_log = (काष्ठा cheetah_err_info *)
		__get_मुक्त_pages(GFP_KERNEL, order);
	अगर (!cheetah_error_log) अणु
		prom_म_लिखो("cheetah_ecache_flush_init: Failed to allocate "
			    "error logging scoreboard (%d bytes).\n", sz);
		prom_halt();
	पूर्ण
	स_रखो(cheetah_error_log, 0, PAGE_SIZE << order);

	/* Mark all AFSRs as invalid so that the trap handler will
	 * log new new inक्रमmation there.
	 */
	क्रम (i = 0; i < 2 * NR_CPUS; i++)
		cheetah_error_log[i].afsr = CHAFSR_INVALID;

	__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
	अगर ((ver >> 32) == __JALAPENO_ID ||
	    (ver >> 32) == __SERRANO_ID) अणु
		cheetah_error_table = &__jalapeno_error_table[0];
		cheetah_afsr_errors = JPAFSR_ERRORS;
	पूर्ण अन्यथा अगर ((ver >> 32) == 0x003e0015) अणु
		cheetah_error_table = &__cheetah_plus_error_table[0];
		cheetah_afsr_errors = CHPAFSR_ERRORS;
	पूर्ण अन्यथा अणु
		cheetah_error_table = &__cheetah_error_table[0];
		cheetah_afsr_errors = CHAFSR_ERRORS;
	पूर्ण

	/* Now patch trap tables. */
	स_नकल(tl0_fecc, cheetah_fecc_trap_vector, (8 * 4));
	स_नकल(tl1_fecc, cheetah_fecc_trap_vector_tl1, (8 * 4));
	स_नकल(tl0_cee, cheetah_cee_trap_vector, (8 * 4));
	स_नकल(tl1_cee, cheetah_cee_trap_vector_tl1, (8 * 4));
	स_नकल(tl0_iae, cheetah_deferred_trap_vector, (8 * 4));
	स_नकल(tl1_iae, cheetah_deferred_trap_vector_tl1, (8 * 4));
	स_नकल(tl0_dae, cheetah_deferred_trap_vector, (8 * 4));
	स_नकल(tl1_dae, cheetah_deferred_trap_vector_tl1, (8 * 4));
	अगर (tlb_type == cheetah_plus) अणु
		स_नकल(tl0_dcpe, cheetah_plus_dcpe_trap_vector, (8 * 4));
		स_नकल(tl1_dcpe, cheetah_plus_dcpe_trap_vector_tl1, (8 * 4));
		स_नकल(tl0_icpe, cheetah_plus_icpe_trap_vector, (8 * 4));
		स_नकल(tl1_icpe, cheetah_plus_icpe_trap_vector_tl1, (8 * 4));
	पूर्ण
	flushi(PAGE_OFFSET);
पूर्ण

अटल व्योम cheetah_flush_ecache(व्योम)
अणु
	अचिन्हित दीर्घ flush_base = ecache_flush_physbase;
	अचिन्हित दीर्घ flush_linesize = ecache_flush_linesize;
	अचिन्हित दीर्घ flush_size = ecache_flush_size;

	__यंत्र__ __अस्थिर__("1: subcc	%0, %4, %0\n\t"
			     "   bne,pt	%%xcc, 1b\n\t"
			     "    ldxa	[%2 + %0] %3, %%g0\n\t"
			     : "=&r" (flush_size)
			     : "0" (flush_size), "r" (flush_base),
			       "i" (ASI_PHYS_USE_EC), "r" (flush_linesize));
पूर्ण

अटल व्योम cheetah_flush_ecache_line(अचिन्हित दीर्घ physaddr)
अणु
	अचिन्हित दीर्घ alias;

	physaddr &= ~(8UL - 1UL);
	physaddr = (ecache_flush_physbase +
		    (physaddr & ((ecache_flush_size>>1UL) - 1UL)));
	alias = physaddr + (ecache_flush_size >> 1UL);
	__यंत्र__ __अस्थिर__("ldxa [%0] %2, %%g0\n\t"
			     "ldxa [%1] %2, %%g0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (physaddr), "r" (alias),
			       "i" (ASI_PHYS_USE_EC));
पूर्ण

/* Unक्रमtunately, the diagnostic access to the I-cache tags we need to
 * use to clear the thing पूर्णांकerferes with I-cache coherency transactions.
 *
 * So we must only flush the I-cache when it is disabled.
 */
अटल व्योम __cheetah_flush_icache(व्योम)
अणु
	अचिन्हित पूर्णांक icache_size, icache_line_size;
	अचिन्हित दीर्घ addr;

	icache_size = local_cpu_data().icache_size;
	icache_line_size = local_cpu_data().icache_line_size;

	/* Clear the valid bits in all the tags. */
	क्रम (addr = 0; addr < icache_size; addr += icache_line_size) अणु
		__यंत्र__ __अस्थिर__("stxa %%g0, [%0] %1\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "r" (addr | (2 << 3)),
				       "i" (ASI_IC_TAG));
	पूर्ण
पूर्ण

अटल व्योम cheetah_flush_icache(व्योम)
अणु
	अचिन्हित दीर्घ dcu_save;

	/* Save current DCU, disable I-cache. */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %1, %0\n\t"
			     "or %0, %2, %%g1\n\t"
			     "stxa %%g1, [%%g0] %1\n\t"
			     "membar #Sync"
			     : "=r" (dcu_save)
			     : "i" (ASI_DCU_CONTROL_REG), "i" (DCU_IC)
			     : "g1");

	__cheetah_flush_icache();

	/* Restore DCU रेजिस्टर */
	__यंत्र__ __अस्थिर__("stxa %0, [%%g0] %1\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "r" (dcu_save), "i" (ASI_DCU_CONTROL_REG));
पूर्ण

अटल व्योम cheetah_flush_dcache(व्योम)
अणु
	अचिन्हित पूर्णांक dcache_size, dcache_line_size;
	अचिन्हित दीर्घ addr;

	dcache_size = local_cpu_data().dcache_size;
	dcache_line_size = local_cpu_data().dcache_line_size;

	क्रम (addr = 0; addr < dcache_size; addr += dcache_line_size) अणु
		__यंत्र__ __अस्थिर__("stxa %%g0, [%0] %1\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "r" (addr), "i" (ASI_DCACHE_TAG));
	पूर्ण
पूर्ण

/* In order to make the even parity correct we must करो two things.
 * First, we clear DC_data_parity and set DC_utag to an appropriate value.
 * Next, we clear out all 32-bytes of data क्रम that line.  Data of
 * all-zero + tag parity value of zero == correct parity.
 */
अटल व्योम cheetah_plus_zap_dcache_parity(व्योम)
अणु
	अचिन्हित पूर्णांक dcache_size, dcache_line_size;
	अचिन्हित दीर्घ addr;

	dcache_size = local_cpu_data().dcache_size;
	dcache_line_size = local_cpu_data().dcache_line_size;

	क्रम (addr = 0; addr < dcache_size; addr += dcache_line_size) अणु
		अचिन्हित दीर्घ tag = (addr >> 14);
		अचिन्हित दीर्घ line;

		__यंत्र__ __अस्थिर__("membar	#Sync\n\t"
				     "stxa	%0, [%1] %2\n\t"
				     "membar	#Sync"
				     : /* no outमाला_दो */
				     : "r" (tag), "r" (addr),
				       "i" (ASI_DCACHE_UTAG));
		क्रम (line = addr; line < addr + dcache_line_size; line += 8)
			__यंत्र__ __अस्थिर__("membar	#Sync\n\t"
					     "stxa	%%g0, [%0] %1\n\t"
					     "membar	#Sync"
					     : /* no outमाला_दो */
					     : "r" (line),
					       "i" (ASI_DCACHE_DATA));
	पूर्ण
पूर्ण

/* Conversion tables used to frob Cheetah AFSR syndrome values पूर्णांकo
 * something palatable to the memory controller driver get_unumber
 * routine.
 */
#घोषणा MT0	137
#घोषणा MT1	138
#घोषणा MT2	139
#घोषणा NONE	254
#घोषणा MTC0	140
#घोषणा MTC1	141
#घोषणा MTC2	142
#घोषणा MTC3	143
#घोषणा C0	128
#घोषणा C1	129
#घोषणा C2	130
#घोषणा C3	131
#घोषणा C4	132
#घोषणा C5	133
#घोषणा C6	134
#घोषणा C7	135
#घोषणा C8	136
#घोषणा M2	144
#घोषणा M3	145
#घोषणा M4	146
#घोषणा M	147
अटल अचिन्हित अक्षर cheetah_ecc_syntab[] = अणु
/*00*/NONE, C0, C1, M2, C2, M2, M3, 47, C3, M2, M2, 53, M2, 41, 29, M,
/*01*/C4, M, M, 50, M2, 38, 25, M2, M2, 33, 24, M2, 11, M, M2, 16,
/*02*/C5, M, M, 46, M2, 37, 19, M2, M, 31, 32, M, 7, M2, M2, 10,
/*03*/M2, 40, 13, M2, 59, M, M2, 66, M, M2, M2, 0, M2, 67, 71, M,
/*04*/C6, M, M, 43, M, 36, 18, M, M2, 49, 15, M, 63, M2, M2, 6,
/*05*/M2, 44, 28, M2, M, M2, M2, 52, 68, M2, M2, 62, M2, M3, M3, M4,
/*06*/M2, 26, 106, M2, 64, M, M2, 2, 120, M, M2, M3, M, M3, M3, M4,
/*07*/116, M2, M2, M3, M2, M3, M, M4, M2, 58, 54, M2, M, M4, M4, M3,
/*08*/C7, M2, M, 42, M, 35, 17, M2, M, 45, 14, M2, 21, M2, M2, 5,
/*09*/M, 27, M, M, 99, M, M, 3, 114, M2, M2, 20, M2, M3, M3, M,
/*0a*/M2, 23, 113, M2, 112, M2, M, 51, 95, M, M2, M3, M2, M3, M3, M2,
/*0b*/103, M, M2, M3, M2, M3, M3, M4, M2, 48, M, M, 73, M2, M, M3,
/*0c*/M2, 22, 110, M2, 109, M2, M, 9, 108, M2, M, M3, M2, M3, M3, M,
/*0d*/102, M2, M, M, M2, M3, M3, M, M2, M3, M3, M2, M, M4, M, M3,
/*0e*/98, M, M2, M3, M2, M, M3, M4, M2, M3, M3, M4, M3, M, M, M,
/*0f*/M2, M3, M3, M, M3, M, M, M, 56, M4, M, M3, M4, M, M, M,
/*10*/C8, M, M2, 39, M, 34, 105, M2, M, 30, 104, M, 101, M, M, 4,
/*11*/M, M, 100, M, 83, M, M2, 12, 87, M, M, 57, M2, M, M3, M,
/*12*/M2, 97, 82, M2, 78, M2, M2, 1, 96, M, M, M, M, M, M3, M2,
/*13*/94, M, M2, M3, M2, M, M3, M, M2, M, 79, M, 69, M, M4, M,
/*14*/M2, 93, 92, M, 91, M, M2, 8, 90, M2, M2, M, M, M, M, M4,
/*15*/89, M, M, M3, M2, M3, M3, M, M, M, M3, M2, M3, M2, M, M3,
/*16*/86, M, M2, M3, M2, M, M3, M, M2, M, M3, M, M3, M, M, M3,
/*17*/M, M, M3, M2, M3, M2, M4, M, 60, M, M2, M3, M4, M, M, M2,
/*18*/M2, 88, 85, M2, 84, M, M2, 55, 81, M2, M2, M3, M2, M3, M3, M4,
/*19*/77, M, M, M, M2, M3, M, M, M2, M3, M3, M4, M3, M2, M, M,
/*1a*/74, M, M2, M3, M, M, M3, M, M, M, M3, M, M3, M, M4, M3,
/*1b*/M2, 70, 107, M4, 65, M2, M2, M, 127, M, M, M, M2, M3, M3, M,
/*1c*/80, M2, M2, 72, M, 119, 118, M, M2, 126, 76, M, 125, M, M4, M3,
/*1d*/M2, 115, 124, M, 75, M, M, M3, 61, M, M4, M, M4, M, M, M,
/*1e*/M, 123, 122, M4, 121, M4, M, M3, 117, M2, M2, M3, M4, M3, M, M,
/*1f*/111, M, M, M, M4, M3, M3, M, M, M, M3, M, M3, M2, M, M
पूर्ण;
अटल अचिन्हित अक्षर cheetah_mtag_syntab[] = अणु
       NONE, MTC0,
       MTC1, NONE,
       MTC2, NONE,
       NONE, MT0,
       MTC3, NONE,
       NONE, MT1,
       NONE, MT2,
       NONE, NONE
पूर्ण;

/* Return the highest priority error conditon mentioned. */
अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_hipri(अचिन्हित दीर्घ afsr)
अणु
	अचिन्हित दीर्घ पंचांगp = 0;
	पूर्णांक i;

	क्रम (i = 0; cheetah_error_table[i].mask; i++) अणु
		अगर ((पंचांगp = (afsr & cheetah_error_table[i].mask)) != 0UL)
			वापस पंचांगp;
	पूर्ण
	वापस पंचांगp;
पूर्ण

अटल स्थिर अक्षर *cheetah_get_string(अचिन्हित दीर्घ bit)
अणु
	पूर्णांक i;

	क्रम (i = 0; cheetah_error_table[i].mask; i++) अणु
		अगर ((bit & cheetah_error_table[i].mask) != 0UL)
			वापस cheetah_error_table[i].name;
	पूर्ण
	वापस "???";
पूर्ण

अटल व्योम cheetah_log_errors(काष्ठा pt_regs *regs, काष्ठा cheetah_err_info *info,
			       अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar, पूर्णांक recoverable)
अणु
	अचिन्हित दीर्घ hipri;
	अक्षर unum[256];

	prपूर्णांकk("%s" "ERROR(%d): Cheetah error trap taken afsr[%016lx] afar[%016lx] TL1(%d)\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       afsr, afar,
	       (afsr & CHAFSR_TL1) ? 1 : 0);
	prपूर्णांकk("%s" "ERROR(%d): TPC[%lx] TNPC[%lx] O7[%lx] TSTATE[%lx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       regs->tpc, regs->tnpc, regs->u_regs[UREG_I7], regs->tstate);
	prपूर्णांकk("%s" "ERROR(%d): ",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id());
	prपूर्णांकk("TPC<%pS>\n", (व्योम *) regs->tpc);
	prपूर्णांकk("%s" "ERROR(%d): M_SYND(%lx),  E_SYND(%lx)%s%s\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       (afsr & CHAFSR_M_SYNDROME) >> CHAFSR_M_SYNDROME_SHIFT,
	       (afsr & CHAFSR_E_SYNDROME) >> CHAFSR_E_SYNDROME_SHIFT,
	       (afsr & CHAFSR_ME) ? ", Multiple Errors" : "",
	       (afsr & CHAFSR_PRIV) ? ", Privileged" : "");
	hipri = cheetah_get_hipri(afsr);
	prपूर्णांकk("%s" "ERROR(%d): Highest priority error (%016lx) \"%s\"\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       hipri, cheetah_get_string(hipri));

	/* Try to get unumber अगर relevant. */
#घोषणा ESYND_ERRORS	(CHAFSR_IVC | CHAFSR_IVU | \
			 CHAFSR_CPC | CHAFSR_CPU | \
			 CHAFSR_UE  | CHAFSR_CE  | \
			 CHAFSR_EDC | CHAFSR_EDU  | \
			 CHAFSR_UCC | CHAFSR_UCU  | \
			 CHAFSR_WDU | CHAFSR_WDC)
#घोषणा MSYND_ERRORS	(CHAFSR_EMC | CHAFSR_EMU)
	अगर (afsr & ESYND_ERRORS) अणु
		पूर्णांक syndrome;
		पूर्णांक ret;

		syndrome = (afsr & CHAFSR_E_SYNDROME) >> CHAFSR_E_SYNDROME_SHIFT;
		syndrome = cheetah_ecc_syntab[syndrome];
		ret = प्र_लिखो_dimm(syndrome, afar, unum, माप(unum));
		अगर (ret != -1)
			prपूर्णांकk("%s" "ERROR(%d): AFAR E-syndrome [%s]\n",
			       (recoverable ? KERN_WARNING : KERN_CRIT),
			       smp_processor_id(), unum);
	पूर्ण अन्यथा अगर (afsr & MSYND_ERRORS) अणु
		पूर्णांक syndrome;
		पूर्णांक ret;

		syndrome = (afsr & CHAFSR_M_SYNDROME) >> CHAFSR_M_SYNDROME_SHIFT;
		syndrome = cheetah_mtag_syntab[syndrome];
		ret = प्र_लिखो_dimm(syndrome, afar, unum, माप(unum));
		अगर (ret != -1)
			prपूर्णांकk("%s" "ERROR(%d): AFAR M-syndrome [%s]\n",
			       (recoverable ? KERN_WARNING : KERN_CRIT),
			       smp_processor_id(), unum);
	पूर्ण

	/* Now dump the cache snapshots. */
	prपूर्णांकk("%s" "ERROR(%d): D-cache idx[%x] tag[%016llx] utag[%016llx] stag[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       (पूर्णांक) info->dcache_index,
	       info->dcache_tag,
	       info->dcache_utag,
	       info->dcache_stag);
	prपूर्णांकk("%s" "ERROR(%d): D-cache data0[%016llx] data1[%016llx] data2[%016llx] data3[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       info->dcache_data[0],
	       info->dcache_data[1],
	       info->dcache_data[2],
	       info->dcache_data[3]);
	prपूर्णांकk("%s" "ERROR(%d): I-cache idx[%x] tag[%016llx] utag[%016llx] stag[%016llx] "
	       "u[%016llx] l[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       (पूर्णांक) info->icache_index,
	       info->icache_tag,
	       info->icache_utag,
	       info->icache_stag,
	       info->icache_upper,
	       info->icache_lower);
	prपूर्णांकk("%s" "ERROR(%d): I-cache INSN0[%016llx] INSN1[%016llx] INSN2[%016llx] INSN3[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       info->icache_data[0],
	       info->icache_data[1],
	       info->icache_data[2],
	       info->icache_data[3]);
	prपूर्णांकk("%s" "ERROR(%d): I-cache INSN4[%016llx] INSN5[%016llx] INSN6[%016llx] INSN7[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       info->icache_data[4],
	       info->icache_data[5],
	       info->icache_data[6],
	       info->icache_data[7]);
	prपूर्णांकk("%s" "ERROR(%d): E-cache idx[%x] tag[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       (पूर्णांक) info->ecache_index, info->ecache_tag);
	prपूर्णांकk("%s" "ERROR(%d): E-cache data0[%016llx] data1[%016llx] data2[%016llx] data3[%016llx]\n",
	       (recoverable ? KERN_WARNING : KERN_CRIT), smp_processor_id(),
	       info->ecache_data[0],
	       info->ecache_data[1],
	       info->ecache_data[2],
	       info->ecache_data[3]);

	afsr = (afsr & ~hipri) & cheetah_afsr_errors;
	जबतक (afsr != 0UL) अणु
		अचिन्हित दीर्घ bit = cheetah_get_hipri(afsr);

		prपूर्णांकk("%s" "ERROR: Multiple-error (%016lx) \"%s\"\n",
		       (recoverable ? KERN_WARNING : KERN_CRIT),
		       bit, cheetah_get_string(bit));

		afsr &= ~bit;
	पूर्ण

	अगर (!recoverable)
		prपूर्णांकk(KERN_CRIT "ERROR: This condition is not recoverable.\n");
पूर्ण

अटल पूर्णांक cheetah_recheck_errors(काष्ठा cheetah_err_info *logp)
अणु
	अचिन्हित दीर्घ afsr, afar;
	पूर्णांक ret = 0;

	__यंत्र__ __अस्थिर__("ldxa [%%g0] %1, %0\n\t"
			     : "=r" (afsr)
			     : "i" (ASI_AFSR));
	अगर ((afsr & cheetah_afsr_errors) != 0) अणु
		अगर (logp != शून्य) अणु
			__यंत्र__ __अस्थिर__("ldxa [%%g0] %1, %0\n\t"
					     : "=r" (afar)
					     : "i" (ASI_AFAR));
			logp->afsr = afsr;
			logp->afar = afar;
		पूर्ण
		ret = 1;
	पूर्ण
	__यंत्र__ __अस्थिर__("stxa %0, [%%g0] %1\n\t"
			     "membar #Sync\n\t"
			     : : "r" (afsr), "i" (ASI_AFSR));

	वापस ret;
पूर्ण

व्योम cheetah_fecc_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar)
अणु
	काष्ठा cheetah_err_info local_snapshot, *p;
	पूर्णांक recoverable;

	/* Flush E-cache */
	cheetah_flush_ecache();

	p = cheetah_get_error_log(afsr);
	अगर (!p) अणु
		prom_म_लिखो("ERROR: Early Fast-ECC error afsr[%016lx] afar[%016lx]\n",
			    afsr, afar);
		prom_म_लिखो("ERROR: CPU(%d) TPC[%016lx] TNPC[%016lx] TSTATE[%016lx]\n",
			    smp_processor_id(), regs->tpc, regs->tnpc, regs->tstate);
		prom_halt();
	पूर्ण

	/* Grab snapshot of logged error. */
	स_नकल(&local_snapshot, p, माप(local_snapshot));

	/* If the current trap snapshot करोes not match what the
	 * trap handler passed aदीर्घ पूर्णांकo our args, big trouble.
	 * In such a हाल, mark the local copy as invalid.
	 *
	 * Else, it matches and we mark the afsr in the non-local
	 * copy as invalid so we may log new error traps there.
	 */
	अगर (p->afsr != afsr || p->afar != afar)
		local_snapshot.afsr = CHAFSR_INVALID;
	अन्यथा
		p->afsr = CHAFSR_INVALID;

	cheetah_flush_icache();
	cheetah_flush_dcache();

	/* Re-enable I-cache/D-cache */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
			     "or %%g1, %1, %%g1\n\t"
			     "stxa %%g1, [%%g0] %0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "i" (ASI_DCU_CONTROL_REG),
			       "i" (DCU_DC | DCU_IC)
			     : "g1");

	/* Re-enable error reporting */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
			     "or %%g1, %1, %%g1\n\t"
			     "stxa %%g1, [%%g0] %0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "i" (ASI_ESTATE_ERROR_EN),
			       "i" (ESTATE_ERROR_NCEEN | ESTATE_ERROR_CEEN)
			     : "g1");

	/* Decide अगर we can जारी after handling this trap and
	 * logging the error.
	 */
	recoverable = 1;
	अगर (afsr & (CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP))
		recoverable = 0;

	/* Re-check AFSR/AFAR.  What we are looking क्रम here is whether a new
	 * error was logged जबतक we had error reporting traps disabled.
	 */
	अगर (cheetah_recheck_errors(&local_snapshot)) अणु
		अचिन्हित दीर्घ new_afsr = local_snapshot.afsr;

		/* If we got a new asynchronous error, die... */
		अगर (new_afsr & (CHAFSR_EMU | CHAFSR_EDU |
				CHAFSR_WDU | CHAFSR_CPU |
				CHAFSR_IVU | CHAFSR_UE |
				CHAFSR_BERR | CHAFSR_TO))
			recoverable = 0;
	पूर्ण

	/* Log errors. */
	cheetah_log_errors(regs, &local_snapshot, afsr, afar, recoverable);

	अगर (!recoverable)
		panic("Irrecoverable Fast-ECC error trap.\n");

	/* Flush E-cache to kick the error trap handlers out. */
	cheetah_flush_ecache();
पूर्ण

/* Try to fix a correctable error by pushing the line out from
 * the E-cache.  Recheck error reporting रेजिस्टरs to see अगर the
 * problem is पूर्णांकermittent.
 */
अटल पूर्णांक cheetah_fix_ce(अचिन्हित दीर्घ physaddr)
अणु
	अचिन्हित दीर्घ orig_estate;
	अचिन्हित दीर्घ alias1, alias2;
	पूर्णांक ret;

	/* Make sure correctable error traps are disabled. */
	__यंत्र__ __अस्थिर__("ldxa	[%%g0] %2, %0\n\t"
			     "andn	%0, %1, %%g1\n\t"
			     "stxa	%%g1, [%%g0] %2\n\t"
			     "membar	#Sync"
			     : "=&r" (orig_estate)
			     : "i" (ESTATE_ERROR_CEEN),
			       "i" (ASI_ESTATE_ERROR_EN)
			     : "g1");

	/* We calculate alias addresses that will क्रमce the
	 * cache line in question out of the E-cache.  Then
	 * we bring it back in with an atomic inकाष्ठाion so
	 * that we get it in some modअगरied/exclusive state,
	 * then we displace it again to try and get proper ECC
	 * pushed back पूर्णांकo the प्रणाली.
	 */
	physaddr &= ~(8UL - 1UL);
	alias1 = (ecache_flush_physbase +
		  (physaddr & ((ecache_flush_size >> 1) - 1)));
	alias2 = alias1 + (ecache_flush_size >> 1);
	__यंत्र__ __अस्थिर__("ldxa	[%0] %3, %%g0\n\t"
			     "ldxa	[%1] %3, %%g0\n\t"
			     "casxa	[%2] %3, %%g0, %%g0\n\t"
			     "ldxa	[%0] %3, %%g0\n\t"
			     "ldxa	[%1] %3, %%g0\n\t"
			     "membar	#Sync"
			     : /* no outमाला_दो */
			     : "r" (alias1), "r" (alias2),
			       "r" (physaddr), "i" (ASI_PHYS_USE_EC));

	/* Did that trigger another error? */
	अगर (cheetah_recheck_errors(शून्य)) अणु
		/* Try one more समय. */
		__यंत्र__ __अस्थिर__("ldxa [%0] %1, %%g0\n\t"
				     "membar #Sync"
				     : : "r" (physaddr), "i" (ASI_PHYS_USE_EC));
		अगर (cheetah_recheck_errors(शून्य))
			ret = 2;
		अन्यथा
			ret = 1;
	पूर्ण अन्यथा अणु
		/* No new error, पूर्णांकermittent problem. */
		ret = 0;
	पूर्ण

	/* Restore error enables. */
	__यंत्र__ __अस्थिर__("stxa	%0, [%%g0] %1\n\t"
			     "membar	#Sync"
			     : : "r" (orig_estate), "i" (ASI_ESTATE_ERROR_EN));

	वापस ret;
पूर्ण

/* Return non-zero अगर PADDR is a valid physical memory address. */
अटल पूर्णांक cheetah_check_मुख्य_memory(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ vaddr = PAGE_OFFSET + paddr;

	अगर (vaddr > (अचिन्हित दीर्घ) high_memory)
		वापस 0;

	वापस kern_addr_valid(vaddr);
पूर्ण

व्योम cheetah_cee_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar)
अणु
	काष्ठा cheetah_err_info local_snapshot, *p;
	पूर्णांक recoverable, is_memory;

	p = cheetah_get_error_log(afsr);
	अगर (!p) अणु
		prom_म_लिखो("ERROR: Early CEE error afsr[%016lx] afar[%016lx]\n",
			    afsr, afar);
		prom_म_लिखो("ERROR: CPU(%d) TPC[%016lx] TNPC[%016lx] TSTATE[%016lx]\n",
			    smp_processor_id(), regs->tpc, regs->tnpc, regs->tstate);
		prom_halt();
	पूर्ण

	/* Grab snapshot of logged error. */
	स_नकल(&local_snapshot, p, माप(local_snapshot));

	/* If the current trap snapshot करोes not match what the
	 * trap handler passed aदीर्घ पूर्णांकo our args, big trouble.
	 * In such a हाल, mark the local copy as invalid.
	 *
	 * Else, it matches and we mark the afsr in the non-local
	 * copy as invalid so we may log new error traps there.
	 */
	अगर (p->afsr != afsr || p->afar != afar)
		local_snapshot.afsr = CHAFSR_INVALID;
	अन्यथा
		p->afsr = CHAFSR_INVALID;

	is_memory = cheetah_check_मुख्य_memory(afar);

	अगर (is_memory && (afsr & CHAFSR_CE) != 0UL) अणु
		/* XXX Might want to log the results of this operation
		 * XXX somewhere... -DaveM
		 */
		cheetah_fix_ce(afar);
	पूर्ण

	अणु
		पूर्णांक flush_all, flush_line;

		flush_all = flush_line = 0;
		अगर ((afsr & CHAFSR_EDC) != 0UL) अणु
			अगर ((afsr & cheetah_afsr_errors) == CHAFSR_EDC)
				flush_line = 1;
			अन्यथा
				flush_all = 1;
		पूर्ण अन्यथा अगर ((afsr & CHAFSR_CPC) != 0UL) अणु
			अगर ((afsr & cheetah_afsr_errors) == CHAFSR_CPC)
				flush_line = 1;
			अन्यथा
				flush_all = 1;
		पूर्ण

		/* Trap handler only disabled I-cache, flush it. */
		cheetah_flush_icache();

		/* Re-enable I-cache */
		__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
				     "or %%g1, %1, %%g1\n\t"
				     "stxa %%g1, [%%g0] %0\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "i" (ASI_DCU_CONTROL_REG),
				     "i" (DCU_IC)
				     : "g1");

		अगर (flush_all)
			cheetah_flush_ecache();
		अन्यथा अगर (flush_line)
			cheetah_flush_ecache_line(afar);
	पूर्ण

	/* Re-enable error reporting */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
			     "or %%g1, %1, %%g1\n\t"
			     "stxa %%g1, [%%g0] %0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "i" (ASI_ESTATE_ERROR_EN),
			       "i" (ESTATE_ERROR_CEEN)
			     : "g1");

	/* Decide अगर we can जारी after handling this trap and
	 * logging the error.
	 */
	recoverable = 1;
	अगर (afsr & (CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP))
		recoverable = 0;

	/* Re-check AFSR/AFAR */
	(व्योम) cheetah_recheck_errors(&local_snapshot);

	/* Log errors. */
	cheetah_log_errors(regs, &local_snapshot, afsr, afar, recoverable);

	अगर (!recoverable)
		panic("Irrecoverable Correctable-ECC error trap.\n");
पूर्ण

व्योम cheetah_deferred_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ afsr, अचिन्हित दीर्घ afar)
अणु
	काष्ठा cheetah_err_info local_snapshot, *p;
	पूर्णांक recoverable, is_memory;

#अगर_घोषित CONFIG_PCI
	/* Check क्रम the special PCI poke sequence. */
	अगर (pci_poke_in_progress && pci_poke_cpu == smp_processor_id()) अणु
		cheetah_flush_icache();
		cheetah_flush_dcache();

		/* Re-enable I-cache/D-cache */
		__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
				     "or %%g1, %1, %%g1\n\t"
				     "stxa %%g1, [%%g0] %0\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "i" (ASI_DCU_CONTROL_REG),
				       "i" (DCU_DC | DCU_IC)
				     : "g1");

		/* Re-enable error reporting */
		__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
				     "or %%g1, %1, %%g1\n\t"
				     "stxa %%g1, [%%g0] %0\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "i" (ASI_ESTATE_ERROR_EN),
				       "i" (ESTATE_ERROR_NCEEN | ESTATE_ERROR_CEEN)
				     : "g1");

		(व्योम) cheetah_recheck_errors(शून्य);

		pci_poke_faulted = 1;
		regs->tpc += 4;
		regs->tnpc = regs->tpc + 4;
		वापस;
	पूर्ण
#पूर्ण_अगर

	p = cheetah_get_error_log(afsr);
	अगर (!p) अणु
		prom_म_लिखो("ERROR: Early deferred error afsr[%016lx] afar[%016lx]\n",
			    afsr, afar);
		prom_म_लिखो("ERROR: CPU(%d) TPC[%016lx] TNPC[%016lx] TSTATE[%016lx]\n",
			    smp_processor_id(), regs->tpc, regs->tnpc, regs->tstate);
		prom_halt();
	पूर्ण

	/* Grab snapshot of logged error. */
	स_नकल(&local_snapshot, p, माप(local_snapshot));

	/* If the current trap snapshot करोes not match what the
	 * trap handler passed aदीर्घ पूर्णांकo our args, big trouble.
	 * In such a हाल, mark the local copy as invalid.
	 *
	 * Else, it matches and we mark the afsr in the non-local
	 * copy as invalid so we may log new error traps there.
	 */
	अगर (p->afsr != afsr || p->afar != afar)
		local_snapshot.afsr = CHAFSR_INVALID;
	अन्यथा
		p->afsr = CHAFSR_INVALID;

	is_memory = cheetah_check_मुख्य_memory(afar);

	अणु
		पूर्णांक flush_all, flush_line;

		flush_all = flush_line = 0;
		अगर ((afsr & CHAFSR_EDU) != 0UL) अणु
			अगर ((afsr & cheetah_afsr_errors) == CHAFSR_EDU)
				flush_line = 1;
			अन्यथा
				flush_all = 1;
		पूर्ण अन्यथा अगर ((afsr & CHAFSR_BERR) != 0UL) अणु
			अगर ((afsr & cheetah_afsr_errors) == CHAFSR_BERR)
				flush_line = 1;
			अन्यथा
				flush_all = 1;
		पूर्ण

		cheetah_flush_icache();
		cheetah_flush_dcache();

		/* Re-enable I/D caches */
		__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
				     "or %%g1, %1, %%g1\n\t"
				     "stxa %%g1, [%%g0] %0\n\t"
				     "membar #Sync"
				     : /* no outमाला_दो */
				     : "i" (ASI_DCU_CONTROL_REG),
				     "i" (DCU_IC | DCU_DC)
				     : "g1");

		अगर (flush_all)
			cheetah_flush_ecache();
		अन्यथा अगर (flush_line)
			cheetah_flush_ecache_line(afar);
	पूर्ण

	/* Re-enable error reporting */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
			     "or %%g1, %1, %%g1\n\t"
			     "stxa %%g1, [%%g0] %0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "i" (ASI_ESTATE_ERROR_EN),
			     "i" (ESTATE_ERROR_NCEEN | ESTATE_ERROR_CEEN)
			     : "g1");

	/* Decide अगर we can जारी after handling this trap and
	 * logging the error.
	 */
	recoverable = 1;
	अगर (afsr & (CHAFSR_PERR | CHAFSR_IERR | CHAFSR_ISAP))
		recoverable = 0;

	/* Re-check AFSR/AFAR.  What we are looking क्रम here is whether a new
	 * error was logged जबतक we had error reporting traps disabled.
	 */
	अगर (cheetah_recheck_errors(&local_snapshot)) अणु
		अचिन्हित दीर्घ new_afsr = local_snapshot.afsr;

		/* If we got a new asynchronous error, die... */
		अगर (new_afsr & (CHAFSR_EMU | CHAFSR_EDU |
				CHAFSR_WDU | CHAFSR_CPU |
				CHAFSR_IVU | CHAFSR_UE |
				CHAFSR_BERR | CHAFSR_TO))
			recoverable = 0;
	पूर्ण

	/* Log errors. */
	cheetah_log_errors(regs, &local_snapshot, afsr, afar, recoverable);

	/* "Recoverable" here means we try to yank the page from ever
	 * being newly used again.  This depends upon a few things:
	 * 1) Must be मुख्य memory, and AFAR must be valid.
	 * 2) If we trapped from user, OK.
	 * 3) Else, अगर we trapped from kernel we must find exception
	 *    table entry (ie. we have to have been accessing user
	 *    space).
	 *
	 * If AFAR is not in मुख्य memory, or we trapped from kernel
	 * and cannot find an exception table entry, it is unacceptable
	 * to try and जारी.
	 */
	अगर (recoverable && is_memory) अणु
		अगर ((regs->tstate & TSTATE_PRIV) == 0UL) अणु
			/* OK, usermode access. */
			recoverable = 1;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा exception_table_entry *entry;

			entry = search_exception_tables(regs->tpc);
			अगर (entry) अणु
				/* OK, kernel access to userspace. */
				recoverable = 1;

			पूर्ण अन्यथा अणु
				/* BAD, privileged state is corrupted. */
				recoverable = 0;
			पूर्ण

			अगर (recoverable) अणु
				अगर (pfn_valid(afar >> PAGE_SHIFT))
					get_page(pfn_to_page(afar >> PAGE_SHIFT));
				अन्यथा
					recoverable = 0;

				/* Only perक्रमm fixup अगर we still have a
				 * recoverable condition.
				 */
				अगर (recoverable) अणु
					regs->tpc = entry->fixup;
					regs->tnpc = regs->tpc + 4;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		recoverable = 0;
	पूर्ण

	अगर (!recoverable)
		panic("Irrecoverable deferred error trap.\n");
पूर्ण

/* Handle a D/I cache parity error trap.  TYPE is encoded as:
 *
 * Bit0:	0=dcache,1=icache
 * Bit1:	0=recoverable,1=unrecoverable
 *
 * The hardware has disabled both the I-cache and D-cache in
 * the %dcr रेजिस्टर.  
 */
व्योम cheetah_plus_parity_error(पूर्णांक type, काष्ठा pt_regs *regs)
अणु
	अगर (type & 0x1)
		__cheetah_flush_icache();
	अन्यथा
		cheetah_plus_zap_dcache_parity();
	cheetah_flush_dcache();

	/* Re-enable I-cache/D-cache */
	__यंत्र__ __अस्थिर__("ldxa [%%g0] %0, %%g1\n\t"
			     "or %%g1, %1, %%g1\n\t"
			     "stxa %%g1, [%%g0] %0\n\t"
			     "membar #Sync"
			     : /* no outमाला_दो */
			     : "i" (ASI_DCU_CONTROL_REG),
			       "i" (DCU_DC | DCU_IC)
			     : "g1");

	अगर (type & 0x2) अणु
		prपूर्णांकk(KERN_EMERG "CPU[%d]: Cheetah+ %c-cache parity error at TPC[%016lx]\n",
		       smp_processor_id(),
		       (type & 0x1) ? 'I' : 'D',
		       regs->tpc);
		prपूर्णांकk(KERN_EMERG "TPC<%pS>\n", (व्योम *) regs->tpc);
		panic("Irrecoverable Cheetah+ parity error.");
	पूर्ण

	prपूर्णांकk(KERN_WARNING "CPU[%d]: Cheetah+ %c-cache parity error at TPC[%016lx]\n",
	       smp_processor_id(),
	       (type & 0x1) ? 'I' : 'D',
	       regs->tpc);
	prपूर्णांकk(KERN_WARNING "TPC<%pS>\n", (व्योम *) regs->tpc);
पूर्ण

काष्ठा sun4v_error_entry अणु
	/* Unique error handle */
/*0x00*/u64		err_handle;

	/* %stick value at the समय of the error */
/*0x08*/u64		err_stick;

/*0x10*/u8		reserved_1[3];

	/* Error type */
/*0x13*/u8		err_type;
#घोषणा SUN4V_ERR_TYPE_UNDEFINED	0
#घोषणा SUN4V_ERR_TYPE_UNCORRECTED_RES	1
#घोषणा SUN4V_ERR_TYPE_PRECISE_NONRES	2
#घोषणा SUN4V_ERR_TYPE_DEFERRED_NONRES	3
#घोषणा SUN4V_ERR_TYPE_SHUTDOWN_RQST	4
#घोषणा SUN4V_ERR_TYPE_DUMP_CORE	5
#घोषणा SUN4V_ERR_TYPE_SP_STATE_CHANGE	6
#घोषणा SUN4V_ERR_TYPE_NUM		7

	/* Error attributes */
/*0x14*/u32		err_attrs;
#घोषणा SUN4V_ERR_ATTRS_PROCESSOR	0x00000001
#घोषणा SUN4V_ERR_ATTRS_MEMORY		0x00000002
#घोषणा SUN4V_ERR_ATTRS_PIO		0x00000004
#घोषणा SUN4V_ERR_ATTRS_INT_REGISTERS	0x00000008
#घोषणा SUN4V_ERR_ATTRS_FPU_REGISTERS	0x00000010
#घोषणा SUN4V_ERR_ATTRS_SHUTDOWN_RQST	0x00000020
#घोषणा SUN4V_ERR_ATTRS_ASR		0x00000040
#घोषणा SUN4V_ERR_ATTRS_ASI		0x00000080
#घोषणा SUN4V_ERR_ATTRS_PRIV_REG	0x00000100
#घोषणा SUN4V_ERR_ATTRS_SPSTATE_MSK	0x00000600
#घोषणा SUN4V_ERR_ATTRS_MCD		0x00000800
#घोषणा SUN4V_ERR_ATTRS_SPSTATE_SHFT	9
#घोषणा SUN4V_ERR_ATTRS_MODE_MSK	0x03000000
#घोषणा SUN4V_ERR_ATTRS_MODE_SHFT	24
#घोषणा SUN4V_ERR_ATTRS_RES_QUEUE_FULL	0x80000000

#घोषणा SUN4V_ERR_SPSTATE_FAULTED	0
#घोषणा SUN4V_ERR_SPSTATE_AVAILABLE	1
#घोषणा SUN4V_ERR_SPSTATE_NOT_PRESENT	2

#घोषणा SUN4V_ERR_MODE_USER		1
#घोषणा SUN4V_ERR_MODE_PRIV		2

	/* Real address of the memory region or PIO transaction */
/*0x18*/u64		err_raddr;

	/* Size of the operation triggering the error, in bytes */
/*0x20*/u32		err_size;

	/* ID of the CPU */
/*0x24*/u16		err_cpu;

	/* Grace periof क्रम shutकरोwn, in seconds */
/*0x26*/u16		err_secs;

	/* Value of the %asi रेजिस्टर */
/*0x28*/u8		err_asi;

/*0x29*/u8		reserved_2;

	/* Value of the ASR रेजिस्टर number */
/*0x2a*/u16		err_asr;
#घोषणा SUN4V_ERR_ASR_VALID		0x8000

/*0x2c*/u32		reserved_3;
/*0x30*/u64		reserved_4;
/*0x38*/u64		reserved_5;
पूर्ण;

अटल atomic_t sun4v_resum_oflow_cnt = ATOMIC_INIT(0);
अटल atomic_t sun4v_nonresum_oflow_cnt = ATOMIC_INIT(0);

अटल स्थिर अक्षर *sun4v_err_type_to_str(u8 type)
अणु
	अटल स्थिर अक्षर *types[SUN4V_ERR_TYPE_NUM] = अणु
		"undefined",
		"uncorrected resumable",
		"precise nonresumable",
		"deferred nonresumable",
		"shutdown request",
		"dump core",
		"SP state change",
	पूर्ण;

	अगर (type < SUN4V_ERR_TYPE_NUM)
		वापस types[type];

	वापस "unknown";
पूर्ण

अटल व्योम sun4v_emit_err_attr_strings(u32 attrs)
अणु
	अटल स्थिर अक्षर *attr_names[] = अणु
		"processor",
		"memory",
		"PIO",
		"int-registers",
		"fpu-registers",
		"shutdown-request",
		"ASR",
		"ASI",
		"priv-reg",
	पूर्ण;
	अटल स्थिर अक्षर *sp_states[] = अणु
		"sp-faulted",
		"sp-available",
		"sp-not-present",
		"sp-state-reserved",
	पूर्ण;
	अटल स्थिर अक्षर *modes[] = अणु
		"mode-reserved0",
		"user",
		"priv",
		"mode-reserved1",
	पूर्ण;
	u32 sp_state, mode;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(attr_names); i++) अणु
		अगर (attrs & (1U << i)) अणु
			स्थिर अक्षर *s = attr_names[i];

			pr_cont("%s ", s);
		पूर्ण
	पूर्ण

	sp_state = ((attrs & SUN4V_ERR_ATTRS_SPSTATE_MSK) >>
		    SUN4V_ERR_ATTRS_SPSTATE_SHFT);
	pr_cont("%s ", sp_states[sp_state]);

	mode = ((attrs & SUN4V_ERR_ATTRS_MODE_MSK) >>
		SUN4V_ERR_ATTRS_MODE_SHFT);
	pr_cont("%s ", modes[mode]);

	अगर (attrs & SUN4V_ERR_ATTRS_RES_QUEUE_FULL)
		pr_cont("res-queue-full ");
पूर्ण

/* When the report contains a real-address of "-1" it means that the
 * hardware did not provide the address.  So we compute the effective
 * address of the load or store inकाष्ठाion at regs->tpc and report
 * that.  Usually when this happens it's a PIO and in such a हाल we
 * are using physical addresses with bypass ASIs anyways, so what we
 * report here is exactly what we want.
 */
अटल व्योम sun4v_report_real_raddr(स्थिर अक्षर *pfx, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक insn;
	u64 addr;

	अगर (!(regs->tstate & TSTATE_PRIV))
		वापस;

	insn = *(अचिन्हित पूर्णांक *) regs->tpc;

	addr = compute_effective_address(regs, insn, 0);

	prपूर्णांकk("%s: insn effective address [0x%016llx]\n",
	       pfx, addr);
पूर्ण

अटल व्योम sun4v_log_error(काष्ठा pt_regs *regs, काष्ठा sun4v_error_entry *ent,
			    पूर्णांक cpu, स्थिर अक्षर *pfx, atomic_t *ocnt)
अणु
	u64 *raw_ptr = (u64 *) ent;
	u32 attrs;
	पूर्णांक cnt;

	prपूर्णांकk("%s: Reporting on cpu %d\n", pfx, cpu);
	prपूर्णांकk("%s: TPC [0x%016lx] <%pS>\n",
	       pfx, regs->tpc, (व्योम *) regs->tpc);

	prपूर्णांकk("%s: RAW [%016llx:%016llx:%016llx:%016llx\n",
	       pfx, raw_ptr[0], raw_ptr[1], raw_ptr[2], raw_ptr[3]);
	prपूर्णांकk("%s:      %016llx:%016llx:%016llx:%016llx]\n",
	       pfx, raw_ptr[4], raw_ptr[5], raw_ptr[6], raw_ptr[7]);

	prपूर्णांकk("%s: handle [0x%016llx] stick [0x%016llx]\n",
	       pfx, ent->err_handle, ent->err_stick);

	prपूर्णांकk("%s: type [%s]\n", pfx, sun4v_err_type_to_str(ent->err_type));

	attrs = ent->err_attrs;
	prपूर्णांकk("%s: attrs [0x%08x] < ", pfx, attrs);
	sun4v_emit_err_attr_strings(attrs);
	pr_cont(">\n");

	/* Various fields in the error report are only valid अगर
	 * certain attribute bits are set.
	 */
	अगर (attrs & (SUN4V_ERR_ATTRS_MEMORY |
		     SUN4V_ERR_ATTRS_PIO |
		     SUN4V_ERR_ATTRS_ASI)) अणु
		prपूर्णांकk("%s: raddr [0x%016llx]\n", pfx, ent->err_raddr);

		अगर (ent->err_raddr == ~(u64)0)
			sun4v_report_real_raddr(pfx, regs);
	पूर्ण

	अगर (attrs & (SUN4V_ERR_ATTRS_MEMORY | SUN4V_ERR_ATTRS_ASI))
		prपूर्णांकk("%s: size [0x%x]\n", pfx, ent->err_size);

	अगर (attrs & (SUN4V_ERR_ATTRS_PROCESSOR |
		     SUN4V_ERR_ATTRS_INT_REGISTERS |
		     SUN4V_ERR_ATTRS_FPU_REGISTERS |
		     SUN4V_ERR_ATTRS_PRIV_REG))
		prपूर्णांकk("%s: cpu[%u]\n", pfx, ent->err_cpu);

	अगर (attrs & SUN4V_ERR_ATTRS_ASI)
		prपूर्णांकk("%s: asi [0x%02x]\n", pfx, ent->err_asi);

	अगर ((attrs & (SUN4V_ERR_ATTRS_INT_REGISTERS |
		      SUN4V_ERR_ATTRS_FPU_REGISTERS |
		      SUN4V_ERR_ATTRS_PRIV_REG)) &&
	    (ent->err_asr & SUN4V_ERR_ASR_VALID) != 0)
		prपूर्णांकk("%s: reg [0x%04x]\n",
		       pfx, ent->err_asr & ~SUN4V_ERR_ASR_VALID);

	show_regs(regs);

	अगर ((cnt = atomic_पढ़ो(ocnt)) != 0) अणु
		atomic_set(ocnt, 0);
		wmb();
		prपूर्णांकk("%s: Queue overflowed %d times.\n",
		       pfx, cnt);
	पूर्ण
पूर्ण

/* Handle memory corruption detected error which is vectored in
 * through resumable error trap.
 */
व्योम करो_mcd_err(काष्ठा pt_regs *regs, काष्ठा sun4v_error_entry ent)
अणु
	अगर (notअगरy_die(DIE_TRAP, "MCD error", regs, 0, 0x34,
		       संक_अंश) == NOTIFY_STOP)
		वापस;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		/* MCD exception could happen because the task was
		 * running a प्रणाली call with MCD enabled and passed a
		 * non-versioned poपूर्णांकer or poपूर्णांकer with bad version
		 * tag to the प्रणाली call. In such हालs, hypervisor
		 * places the address of offending inकाष्ठाion in the
		 * resumable error report. This is a deferred error,
		 * so the पढ़ो/ग_लिखो that caused the trap was potentially
		 * retired दीर्घ समय back and we may have no choice
		 * but to send संक_अंश to the process.
		 */
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			/* Looks like a bad syscall parameter */
#अगर_घोषित DEBUG_EXCEPTIONS
			pr_emerg("Exception: PC<%016lx> faddr<UNKNOWN>\n",
				 regs->tpc);
			pr_emerg("EX_TABLE: insn<%016lx> fixup<%016lx>\n",
				 ent.err_raddr, entry->fixup);
#पूर्ण_अगर
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस;
		पूर्ण
	पूर्ण

	/* Send संक_अंश to the userspace process with the right संकेत
	 * code
	 */
	क्रमce_sig_fault(संक_अंश, SEGV_ADIDERR, (व्योम __user *)ent.err_raddr,
			0);
पूर्ण

/* We run with %pil set to PIL_NORMAL_MAX and PSTATE_IE enabled in %pstate.
 * Log the event and clear the first word of the entry.
 */
व्योम sun4v_resum_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ offset)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	काष्ठा sun4v_error_entry *ent, local_copy;
	काष्ठा trap_per_cpu *tb;
	अचिन्हित दीर्घ paddr;
	पूर्णांक cpu;

	cpu = get_cpu();

	tb = &trap_block[cpu];
	paddr = tb->resum_kernel_buf_pa + offset;
	ent = __va(paddr);

	स_नकल(&local_copy, ent, माप(काष्ठा sun4v_error_entry));

	/* We have a local copy now, so release the entry.  */
	ent->err_handle = 0;
	wmb();

	put_cpu();

	अगर (local_copy.err_type == SUN4V_ERR_TYPE_SHUTDOWN_RQST) अणु
		/* We should really take the seconds field of
		 * the error report and use it क्रम the shutकरोwn
		 * invocation, but क्रम now करो the same thing we
		 * करो क्रम a DS shutकरोwn request.
		 */
		pr_info("Shutdown request, %u seconds...\n",
			local_copy.err_secs);
		orderly_घातeroff(true);
		जाओ out;
	पूर्ण

	/* If this is a memory corruption detected error vectored in
	 * by HV through resumable error trap, call the handler
	 */
	अगर (local_copy.err_attrs & SUN4V_ERR_ATTRS_MCD) अणु
		करो_mcd_err(regs, local_copy);
		वापस;
	पूर्ण

	sun4v_log_error(regs, &local_copy, cpu,
			KERN_ERR "RESUMABLE ERROR",
			&sun4v_resum_oflow_cnt);
out:
	exception_निकास(prev_state);
पूर्ण

/* If we try to prपूर्णांकk() we'll probably make matters worse, by trying
 * to retake locks this cpu alपढ़ोy holds or causing more errors. So
 * just bump a counter, and we'll report these counter bumps above.
 */
व्योम sun4v_resum_overflow(काष्ठा pt_regs *regs)
अणु
	atomic_inc(&sun4v_resum_oflow_cnt);
पूर्ण

/* Given a set of रेजिस्टरs, get the भव addressi that was being accessed
 * by the faulting inकाष्ठाions at tpc.
 */
अटल अचिन्हित दीर्घ sun4v_get_vaddr(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक insn;

	अगर (!copy_from_user(&insn, (व्योम __user *)regs->tpc, 4)) अणु
		वापस compute_effective_address(regs, insn,
						 (insn >> 25) & 0x1f);
	पूर्ण
	वापस 0;
पूर्ण

/* Attempt to handle non-resumable errors generated from userspace.
 * Returns true अगर the संकेत was handled, false otherwise.
 */
bool sun4v_nonresum_error_user_handled(काष्ठा pt_regs *regs,
				  काष्ठा sun4v_error_entry *ent) अणु

	अचिन्हित पूर्णांक attrs = ent->err_attrs;

	अगर (attrs & SUN4V_ERR_ATTRS_MEMORY) अणु
		अचिन्हित दीर्घ addr = ent->err_raddr;

		अगर (addr == ~(u64)0) अणु
			/* This seems highly unlikely to ever occur */
			pr_emerg("SUN4V NON-RECOVERABLE ERROR: Memory error detected in unknown location!\n");
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ page_cnt = DIV_ROUND_UP(ent->err_size,
							      PAGE_SIZE);

			/* Break the unक्रमtunate news. */
			pr_emerg("SUN4V NON-RECOVERABLE ERROR: Memory failed at %016lX\n",
				 addr);
			pr_emerg("SUN4V NON-RECOVERABLE ERROR:   Claiming %lu ages.\n",
				 page_cnt);

			जबतक (page_cnt-- > 0) अणु
				अगर (pfn_valid(addr >> PAGE_SHIFT))
					get_page(pfn_to_page(addr >> PAGE_SHIFT));
				addr += PAGE_SIZE;
			पूर्ण
		पूर्ण
		क्रमce_sig(SIGKILL);

		वापस true;
	पूर्ण
	अगर (attrs & SUN4V_ERR_ATTRS_PIO) अणु
		क्रमce_sig_fault(SIGBUS, BUS_ADRERR,
				(व्योम __user *)sun4v_get_vaddr(regs), 0);
		वापस true;
	पूर्ण

	/* Default to करोing nothing */
	वापस false;
पूर्ण

/* We run with %pil set to PIL_NORMAL_MAX and PSTATE_IE enabled in %pstate.
 * Log the event, clear the first word of the entry, and die.
 */
व्योम sun4v_nonresum_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ offset)
अणु
	काष्ठा sun4v_error_entry *ent, local_copy;
	काष्ठा trap_per_cpu *tb;
	अचिन्हित दीर्घ paddr;
	पूर्णांक cpu;

	cpu = get_cpu();

	tb = &trap_block[cpu];
	paddr = tb->nonresum_kernel_buf_pa + offset;
	ent = __va(paddr);

	स_नकल(&local_copy, ent, माप(काष्ठा sun4v_error_entry));

	/* We have a local copy now, so release the entry.  */
	ent->err_handle = 0;
	wmb();

	put_cpu();

	अगर (!(regs->tstate & TSTATE_PRIV) &&
	    sun4v_nonresum_error_user_handled(regs, &local_copy)) अणु
		/* DON'T PANIC: This userspace error was handled. */
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_PCI
	/* Check क्रम the special PCI poke sequence. */
	अगर (pci_poke_in_progress && pci_poke_cpu == cpu) अणु
		pci_poke_faulted = 1;
		regs->tpc += 4;
		regs->tnpc = regs->tpc + 4;
		वापस;
	पूर्ण
#पूर्ण_अगर

	sun4v_log_error(regs, &local_copy, cpu,
			KERN_EMERG "NON-RESUMABLE ERROR",
			&sun4v_nonresum_oflow_cnt);

	panic("Non-resumable error.");
पूर्ण

/* If we try to prपूर्णांकk() we'll probably make matters worse, by trying
 * to retake locks this cpu alपढ़ोy holds or causing more errors. So
 * just bump a counter, and we'll report these counter bumps above.
 */
व्योम sun4v_nonresum_overflow(काष्ठा pt_regs *regs)
अणु
	/* XXX Actually even this can make not that much sense.  Perhaps
	 * XXX we should just pull the plug and panic directly from here?
	 */
	atomic_inc(&sun4v_nonresum_oflow_cnt);
पूर्ण

अटल व्योम sun4v_tlb_error(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("TLB/TSB error", regs);
पूर्ण

अचिन्हित दीर्घ sun4v_err_itlb_vaddr;
अचिन्हित दीर्घ sun4v_err_itlb_ctx;
अचिन्हित दीर्घ sun4v_err_itlb_pte;
अचिन्हित दीर्घ sun4v_err_itlb_error;

व्योम sun4v_itlb_error_report(काष्ठा pt_regs *regs, पूर्णांक tl)
अणु
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));

	prपूर्णांकk(KERN_EMERG "SUN4V-ITLB: Error at TPC[%lx], tl %d\n",
	       regs->tpc, tl);
	prपूर्णांकk(KERN_EMERG "SUN4V-ITLB: TPC<%pS>\n", (व्योम *) regs->tpc);
	prपूर्णांकk(KERN_EMERG "SUN4V-ITLB: O7[%lx]\n", regs->u_regs[UREG_I7]);
	prपूर्णांकk(KERN_EMERG "SUN4V-ITLB: O7<%pS>\n",
	       (व्योम *) regs->u_regs[UREG_I7]);
	prपूर्णांकk(KERN_EMERG "SUN4V-ITLB: vaddr[%lx] ctx[%lx] "
	       "pte[%lx] error[%lx]\n",
	       sun4v_err_itlb_vaddr, sun4v_err_itlb_ctx,
	       sun4v_err_itlb_pte, sun4v_err_itlb_error);

	sun4v_tlb_error(regs);
पूर्ण

अचिन्हित दीर्घ sun4v_err_dtlb_vaddr;
अचिन्हित दीर्घ sun4v_err_dtlb_ctx;
अचिन्हित दीर्घ sun4v_err_dtlb_pte;
अचिन्हित दीर्घ sun4v_err_dtlb_error;

व्योम sun4v_dtlb_error_report(काष्ठा pt_regs *regs, पूर्णांक tl)
अणु
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));

	prपूर्णांकk(KERN_EMERG "SUN4V-DTLB: Error at TPC[%lx], tl %d\n",
	       regs->tpc, tl);
	prपूर्णांकk(KERN_EMERG "SUN4V-DTLB: TPC<%pS>\n", (व्योम *) regs->tpc);
	prपूर्णांकk(KERN_EMERG "SUN4V-DTLB: O7[%lx]\n", regs->u_regs[UREG_I7]);
	prपूर्णांकk(KERN_EMERG "SUN4V-DTLB: O7<%pS>\n",
	       (व्योम *) regs->u_regs[UREG_I7]);
	prपूर्णांकk(KERN_EMERG "SUN4V-DTLB: vaddr[%lx] ctx[%lx] "
	       "pte[%lx] error[%lx]\n",
	       sun4v_err_dtlb_vaddr, sun4v_err_dtlb_ctx,
	       sun4v_err_dtlb_pte, sun4v_err_dtlb_error);

	sun4v_tlb_error(regs);
पूर्ण

व्योम hypervisor_tlbop_error(अचिन्हित दीर्घ err, अचिन्हित दीर्घ op)
अणु
	prपूर्णांकk(KERN_CRIT "SUN4V: TLB hv call error %lu for op %lu\n",
	       err, op);
पूर्ण

व्योम hypervisor_tlbop_error_xcall(अचिन्हित दीर्घ err, अचिन्हित दीर्घ op)
अणु
	prपूर्णांकk(KERN_CRIT "SUN4V: XCALL TLB hv call error %lu for op %lu\n",
	       err, op);
पूर्ण

अटल व्योम करो_fpe_common(काष्ठा pt_regs *regs)
अणु
	अगर (regs->tstate & TSTATE_PRIV) अणु
		regs->tpc = regs->tnpc;
		regs->tnpc += 4;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ fsr = current_thपढ़ो_info()->xfsr[0];
		पूर्णांक code;

		अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
			regs->tpc &= 0xffffffff;
			regs->tnpc &= 0xffffffff;
		पूर्ण
		code = FPE_FLTUNK;
		अगर ((fsr & 0x1c000) == (1 << 14)) अणु
			अगर (fsr & 0x10)
				code = FPE_FLTINV;
			अन्यथा अगर (fsr & 0x08)
				code = FPE_FLTOVF;
			अन्यथा अगर (fsr & 0x04)
				code = FPE_FLTUND;
			अन्यथा अगर (fsr & 0x02)
				code = FPE_FLTDIV;
			अन्यथा अगर (fsr & 0x01)
				code = FPE_FLTRES;
		पूर्ण
		क्रमce_sig_fault(संक_भ_त्रुटि, code,
				(व्योम __user *)regs->tpc, 0);
	पूर्ण
पूर्ण

व्योम करो_fpieee(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "fpu exception ieee", regs,
		       0, 0x24, संक_भ_त्रुटि) == NOTIFY_STOP)
		जाओ out;

	करो_fpe_common(regs);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम करो_fpother(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	काष्ठा fpustate *f = FPUSTATE;
	पूर्णांक ret = 0;

	अगर (notअगरy_die(DIE_TRAP, "fpu exception other", regs,
		       0, 0x25, संक_भ_त्रुटि) == NOTIFY_STOP)
		जाओ out;

	चयन ((current_thपढ़ो_info()->xfsr[0] & 0x1c000)) अणु
	हाल (2 << 14): /* unfinished_FPop */
	हाल (3 << 14): /* unimplemented_FPop */
		ret = करो_mathemu(regs, f, false);
		अवरोध;
	पूर्ण
	अगर (ret)
		जाओ out;
	करो_fpe_common(regs);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम करो_tof(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "tagged arithmetic overflow", regs,
		       0, 0x26, SIGEMT) == NOTIFY_STOP)
		जाओ out;

	अगर (regs->tstate & TSTATE_PRIV)
		die_अगर_kernel("Penguin overflow trap from kernel mode", regs);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(SIGEMT, EMT_TAGOVF,
			(व्योम __user *)regs->tpc, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम करो_भाग0(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "integer division by zero", regs,
		       0, 0x28, संक_भ_त्रुटि) == NOTIFY_STOP)
		जाओ out;

	अगर (regs->tstate & TSTATE_PRIV)
		die_अगर_kernel("TL0: Kernel divide by zero.", regs);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_भ_त्रुटि, FPE_INTDIV,
			(व्योम __user *)regs->tpc, 0);
out:
	exception_निकास(prev_state);
पूर्ण

अटल व्योम inकाष्ठाion_dump(अचिन्हित पूर्णांक *pc)
अणु
	पूर्णांक i;

	अगर ((((अचिन्हित दीर्घ) pc) & 3))
		वापस;

	prपूर्णांकk("Instruction DUMP:");
	क्रम (i = -3; i < 6; i++)
		prपूर्णांकk("%c%08x%c",i?' ':'<',pc[i],i?' ':'>');
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम user_inकाष्ठाion_dump(अचिन्हित पूर्णांक __user *pc)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक buf[9];
	
	अगर ((((अचिन्हित दीर्घ) pc) & 3))
		वापस;
		
	अगर (copy_from_user(buf, pc - 3, माप(buf)))
		वापस;

	prपूर्णांकk("Instruction DUMP:");
	क्रम (i = 0; i < 9; i++)
		prपूर्णांकk("%c%08x%c",i==3?' ':'<',buf[i],i==3?' ':'>');
	prपूर्णांकk("\n");
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *_ksp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ fp, ksp;
	काष्ठा thपढ़ो_info *tp;
	पूर्णांक count = 0;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	पूर्णांक graph = 0;
#पूर्ण_अगर

	ksp = (अचिन्हित दीर्घ) _ksp;
	अगर (!tsk)
		tsk = current;
	tp = task_thपढ़ो_info(tsk);
	अगर (ksp == 0UL) अणु
		अगर (tsk == current)
			यंत्र("mov %%fp, %0" : "=r" (ksp));
		अन्यथा
			ksp = tp->ksp;
	पूर्ण
	अगर (tp == current_thपढ़ो_info())
		flushw_all();

	fp = ksp + STACK_BIAS;

	prपूर्णांकk("%sCall Trace:\n", loglvl);
	करो अणु
		काष्ठा sparc_stackf *sf;
		काष्ठा pt_regs *regs;
		अचिन्हित दीर्घ pc;

		अगर (!kstack_valid(tp, fp))
			अवरोध;
		sf = (काष्ठा sparc_stackf *) fp;
		regs = (काष्ठा pt_regs *) (sf + 1);

		अगर (kstack_is_trap_frame(tp, regs)) अणु
			अगर (!(regs->tstate & TSTATE_PRIV))
				अवरोध;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		पूर्ण अन्यथा अणु
			pc = sf->callers_pc;
			fp = (अचिन्हित दीर्घ)sf->fp + STACK_BIAS;
		पूर्ण

		prपूर्णांक_ip_sym(loglvl, pc);
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
		अगर ((pc + 8UL) == (अचिन्हित दीर्घ) &वापस_to_handler) अणु
			काष्ठा ftrace_ret_stack *ret_stack;
			ret_stack = ftrace_graph_get_ret_stack(tsk, graph);
			अगर (ret_stack) अणु
				pc = ret_stack->ret;
				prपूर्णांक_ip_sym(loglvl, pc);
				graph++;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण जबतक (++count < 16);
पूर्ण

अटल अंतरभूत काष्ठा reg_winकरोw *kernel_stack_up(काष्ठा reg_winकरोw *rw)
अणु
	अचिन्हित दीर्घ fp = rw->ins[6];

	अगर (!fp)
		वापस शून्य;

	वापस (काष्ठा reg_winकरोw *) (fp + STACK_BIAS);
पूर्ण

व्योम __noवापस die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक die_counter;
	पूर्णांक count = 0;
	
	/* Amuse the user. */
	prपूर्णांकk(
"              \\|/ ____ \\|/\n"
"              \"@'/ .. \\`@\"\n"
"              /_| \\__/ |_\\\n"
"                 \\__U_/\n");

	prपूर्णांकk("%s(%d): %s [#%d]\n", current->comm, task_pid_nr(current), str, ++die_counter);
	notअगरy_die(DIE_OOPS, str, regs, 0, 255, संक_अंश);
	__यंत्र__ __अस्थिर__("flushw");
	show_regs(regs);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	अगर (regs->tstate & TSTATE_PRIV) अणु
		काष्ठा thपढ़ो_info *tp = current_thपढ़ो_info();
		काष्ठा reg_winकरोw *rw = (काष्ठा reg_winकरोw *)
			(regs->u_regs[UREG_FP] + STACK_BIAS);

		/* Stop the back trace when we hit userland or we
		 * find some badly aligned kernel stack.
		 */
		जबतक (rw &&
		       count++ < 30 &&
		       kstack_valid(tp, (अचिन्हित दीर्घ) rw)) अणु
			prपूर्णांकk("Caller[%016lx]: %pS\n", rw->ins[7],
			       (व्योम *) rw->ins[7]);

			rw = kernel_stack_up(rw);
		पूर्ण
		inकाष्ठाion_dump ((अचिन्हित पूर्णांक *) regs->tpc);
	पूर्ण अन्यथा अणु
		अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
			regs->tpc &= 0xffffffff;
			regs->tnpc &= 0xffffffff;
		पूर्ण
		user_inकाष्ठाion_dump ((अचिन्हित पूर्णांक __user *) regs->tpc);
	पूर्ण
	अगर (panic_on_oops)
		panic("Fatal exception");
	अगर (regs->tstate & TSTATE_PRIV)
		करो_निकास(SIGKILL);
	करो_निकास(संक_अंश);
पूर्ण
EXPORT_SYMBOL(die_अगर_kernel);

#घोषणा VIS_OPCODE_MASK	((0x3 << 30) | (0x3f << 19))
#घोषणा VIS_OPCODE_VAL	((0x2 << 30) | (0x36 << 19))

व्योम करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	अचिन्हित दीर्घ pc = regs->tpc;
	अचिन्हित दीर्घ tstate = regs->tstate;
	u32 insn;

	अगर (notअगरy_die(DIE_TRAP, "illegal instruction", regs,
		       0, 0x10, संक_अवैध) == NOTIFY_STOP)
		जाओ out;

	अगर (tstate & TSTATE_PRIV)
		die_अगर_kernel("Kernel illegal instruction", regs);
	अगर (test_thपढ़ो_flag(TIF_32BIT))
		pc = (u32)pc;
	अगर (get_user(insn, (u32 __user *) pc) != -EFAULT) अणु
		अगर ((insn & 0xc1ffc000) == 0x81700000) /* POPC */ अणु
			अगर (handle_popc(insn, regs))
				जाओ out;
		पूर्ण अन्यथा अगर ((insn & 0xc1580000) == 0xc1100000) /* LDQ/STQ */ अणु
			अगर (handle_ldf_stq(insn, regs))
				जाओ out;
		पूर्ण अन्यथा अगर (tlb_type == hypervisor) अणु
			अगर ((insn & VIS_OPCODE_MASK) == VIS_OPCODE_VAL) अणु
				अगर (!vis_emul(regs, insn))
					जाओ out;
			पूर्ण अन्यथा अणु
				काष्ठा fpustate *f = FPUSTATE;

				/* On UltraSPARC T2 and later, FPU insns which
				 * are not implemented in HW संकेत an illegal
				 * inकाष्ठाion trap and करो not set the FP Trap
				 * Trap in the %fsr to unimplemented_FPop.
				 */
				अगर (करो_mathemu(regs, f, true))
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रमce_sig_fault(संक_अवैध, ILL_ILLOPC, (व्योम __user *)pc, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम mem_address_unaligned(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfar, अचिन्हित दीर्घ sfsr)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "memory address unaligned", regs,
		       0, 0x34, संक_अंश) == NOTIFY_STOP)
		जाओ out;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		kernel_unaligned_trap(regs, *((अचिन्हित पूर्णांक *)regs->tpc));
		जाओ out;
	पूर्ण
	अगर (is_no_fault_exception(regs))
		वापस;

	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *)sfar, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम sun4v_करो_mna(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ type_ctx)
अणु
	अगर (notअगरy_die(DIE_TRAP, "memory address unaligned", regs,
		       0, 0x34, संक_अंश) == NOTIFY_STOP)
		वापस;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		kernel_unaligned_trap(regs, *((अचिन्हित पूर्णांक *)regs->tpc));
		वापस;
	पूर्ण
	अगर (is_no_fault_exception(regs))
		वापस;

	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *) addr, 0);
पूर्ण

/* sun4v_mem_corrupt_detect_precise() - Handle precise exception on an ADI
 * tag mismatch.
 *
 * ADI version tag mismatch on a load from memory always results in a
 * precise exception. Tag mismatch on a store to memory will result in
 * precise exception अगर MCDPER or PMCDPER is set to 1.
 */
व्योम sun4v_mem_corrupt_detect_precise(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ context)
अणु
	अगर (notअगरy_die(DIE_TRAP, "memory corruption precise exception", regs,
		       0, 0x8, संक_अंश) == NOTIFY_STOP)
		वापस;

	अगर (regs->tstate & TSTATE_PRIV) अणु
		/* MCD exception could happen because the task was running
		 * a प्रणाली call with MCD enabled and passed a non-versioned
		 * poपूर्णांकer or poपूर्णांकer with bad version tag to  the प्रणाली
		 * call.
		 */
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			/* Looks like a bad syscall parameter */
#अगर_घोषित DEBUG_EXCEPTIONS
			pr_emerg("Exception: PC<%016lx> faddr<UNKNOWN>\n",
				 regs->tpc);
			pr_emerg("EX_TABLE: insn<%016lx> fixup<%016lx>\n",
				 regs->tpc, entry->fixup);
#पूर्ण_अगर
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस;
		पूर्ण
		pr_emerg("%s: ADDR[%016lx] CTX[%lx], going.\n",
			 __func__, addr, context);
		die_अगर_kernel("MCD precise", regs);
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_अंश, SEGV_ADIPERR, (व्योम __user *)addr, 0);
पूर्ण

व्योम करो_privop(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (notअगरy_die(DIE_TRAP, "privileged operation", regs,
		       0, 0x11, संक_अवैध) == NOTIFY_STOP)
		जाओ out;

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	क्रमce_sig_fault(संक_अवैध, ILL_PRVOPC,
			(व्योम __user *)regs->tpc, 0);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम करो_privact(काष्ठा pt_regs *regs)
अणु
	करो_privop(regs);
पूर्ण

/* Trap level 1 stuff or other traps we should never see... */
व्योम करो_cee(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	die_अगर_kernel("TL0: Cache Error Exception", regs);
पूर्ण

व्योम करो_भाग0_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: DIV0 Exception", regs);
पूर्ण

व्योम करो_fpieee_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: FPU IEEE Exception", regs);
पूर्ण

व्योम करो_fpother_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: FPU Other Exception", regs);
पूर्ण

व्योम करो_ill_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: Illegal Instruction Exception", regs);
पूर्ण

व्योम करो_irq_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: IRQ Exception", regs);
पूर्ण

व्योम करो_lddfmna_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: LDDF Exception", regs);
पूर्ण

व्योम करो_stdfmna_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: STDF Exception", regs);
पूर्ण

व्योम करो_paw(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	die_अगर_kernel("TL0: Phys Watchpoint Exception", regs);
पूर्ण

व्योम करो_paw_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: Phys Watchpoint Exception", regs);
पूर्ण

व्योम करो_vaw(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	die_अगर_kernel("TL0: Virt Watchpoint Exception", regs);
पूर्ण

व्योम करो_vaw_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: Virt Watchpoint Exception", regs);
पूर्ण

व्योम करो_tof_tl1(काष्ठा pt_regs *regs)
अणु
	exception_enter();
	dump_tl1_traplog((काष्ठा tl1_traplog *)(regs + 1));
	die_अगर_kernel("TL1: Tag Overflow Exception", regs);
पूर्ण

व्योम करो_getpsr(काष्ठा pt_regs *regs)
अणु
	regs->u_regs[UREG_I0] = tstate_to_psr(regs->tstate);
	regs->tpc   = regs->tnpc;
	regs->tnpc += 4;
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
पूर्ण

u64 cpu_monकरो_counter[NR_CPUS] = अणु0पूर्ण;
काष्ठा trap_per_cpu trap_block[NR_CPUS];
EXPORT_SYMBOL(trap_block);

/* This can get invoked beक्रमe sched_init() so play it super safe
 * and use hard_smp_processor_id().
 */
व्योम notrace init_cur_cpu_trap(काष्ठा thपढ़ो_info *t)
अणु
	पूर्णांक cpu = hard_smp_processor_id();
	काष्ठा trap_per_cpu *p = &trap_block[cpu];

	p->thपढ़ो = t;
	p->pgd_paddr = 0;
पूर्ण

बाह्य व्योम thपढ़ो_info_offsets_are_bolixed_dave(व्योम);
बाह्य व्योम trap_per_cpu_offsets_are_bolixed_dave(व्योम);
बाह्य व्योम tsb_config_offsets_are_bolixed_dave(व्योम);

/* Only invoked on boot processor. */
व्योम __init trap_init(व्योम)
अणु
	/* Compile समय sanity check. */
	BUILD_BUG_ON(TI_TASK != दुरत्व(काष्ठा thपढ़ो_info, task) ||
		     TI_FLAGS != दुरत्व(काष्ठा thपढ़ो_info, flags) ||
		     TI_CPU != दुरत्व(काष्ठा thपढ़ो_info, cpu) ||
		     TI_FPSAVED != दुरत्व(काष्ठा thपढ़ो_info, fpsaved) ||
		     TI_KSP != दुरत्व(काष्ठा thपढ़ो_info, ksp) ||
		     TI_FAULT_ADDR != दुरत्व(काष्ठा thपढ़ो_info,
					       fault_address) ||
		     TI_KREGS != दुरत्व(काष्ठा thपढ़ो_info, kregs) ||
		     TI_UTRAPS != दुरत्व(काष्ठा thपढ़ो_info, utraps) ||
		     TI_REG_WINDOW != दुरत्व(काष्ठा thपढ़ो_info,
					       reg_winकरोw) ||
		     TI_RWIN_SPTRS != दुरत्व(काष्ठा thपढ़ो_info,
					       rwbuf_stkptrs) ||
		     TI_GSR != दुरत्व(काष्ठा thपढ़ो_info, gsr) ||
		     TI_XFSR != दुरत्व(काष्ठा thपढ़ो_info, xfsr) ||
		     TI_PRE_COUNT != दुरत्व(काष्ठा thपढ़ो_info,
					      preempt_count) ||
		     TI_NEW_CHILD != दुरत्व(काष्ठा thपढ़ो_info, new_child) ||
		     TI_CURRENT_DS != दुरत्व(काष्ठा thपढ़ो_info,
						current_ds) ||
		     TI_KUNA_REGS != दुरत्व(काष्ठा thपढ़ो_info,
					      kern_una_regs) ||
		     TI_KUNA_INSN != दुरत्व(काष्ठा thपढ़ो_info,
					      kern_una_insn) ||
		     TI_FPREGS != दुरत्व(काष्ठा thपढ़ो_info, fpregs) ||
		     (TI_FPREGS & (64 - 1)));

	BUILD_BUG_ON(TRAP_PER_CPU_THREAD != दुरत्व(काष्ठा trap_per_cpu,
						     thपढ़ो) ||
		     (TRAP_PER_CPU_PGD_PADDR !=
		      दुरत्व(काष्ठा trap_per_cpu, pgd_paddr)) ||
		     (TRAP_PER_CPU_CPU_MONDO_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, cpu_monकरो_pa)) ||
		     (TRAP_PER_CPU_DEV_MONDO_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, dev_monकरो_pa)) ||
		     (TRAP_PER_CPU_RESUM_MONDO_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, resum_monकरो_pa)) ||
		     (TRAP_PER_CPU_RESUM_KBUF_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, resum_kernel_buf_pa)) ||
		     (TRAP_PER_CPU_NONRESUM_MONDO_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, nonresum_monकरो_pa)) ||
		     (TRAP_PER_CPU_NONRESUM_KBUF_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, nonresum_kernel_buf_pa)) ||
		     (TRAP_PER_CPU_FAULT_INFO !=
		      दुरत्व(काष्ठा trap_per_cpu, fault_info)) ||
		     (TRAP_PER_CPU_CPU_MONDO_BLOCK_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, cpu_monकरो_block_pa)) ||
		     (TRAP_PER_CPU_CPU_LIST_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, cpu_list_pa)) ||
		     (TRAP_PER_CPU_TSB_HUGE !=
		      दुरत्व(काष्ठा trap_per_cpu, tsb_huge)) ||
		     (TRAP_PER_CPU_TSB_HUGE_TEMP !=
		      दुरत्व(काष्ठा trap_per_cpu, tsb_huge_temp)) ||
		     (TRAP_PER_CPU_IRQ_WORKLIST_PA !=
		      दुरत्व(काष्ठा trap_per_cpu, irq_worklist_pa)) ||
		     (TRAP_PER_CPU_CPU_MONDO_QMASK !=
		      दुरत्व(काष्ठा trap_per_cpu, cpu_monकरो_qmask)) ||
		     (TRAP_PER_CPU_DEV_MONDO_QMASK !=
		      दुरत्व(काष्ठा trap_per_cpu, dev_monकरो_qmask)) ||
		     (TRAP_PER_CPU_RESUM_QMASK !=
		      दुरत्व(काष्ठा trap_per_cpu, resum_qmask)) ||
		     (TRAP_PER_CPU_NONRESUM_QMASK !=
		      दुरत्व(काष्ठा trap_per_cpu, nonresum_qmask)) ||
		     (TRAP_PER_CPU_PER_CPU_BASE !=
		      दुरत्व(काष्ठा trap_per_cpu, __per_cpu_base)));

	BUILD_BUG_ON((TSB_CONFIG_TSB !=
		      दुरत्व(काष्ठा tsb_config, tsb)) ||
		     (TSB_CONFIG_RSS_LIMIT !=
		      दुरत्व(काष्ठा tsb_config, tsb_rss_limit)) ||
		     (TSB_CONFIG_NENTRIES !=
		      दुरत्व(काष्ठा tsb_config, tsb_nentries)) ||
		     (TSB_CONFIG_REG_VAL !=
		      दुरत्व(काष्ठा tsb_config, tsb_reg_val)) ||
		     (TSB_CONFIG_MAP_VADDR !=
		      दुरत्व(काष्ठा tsb_config, tsb_map_vaddr)) ||
		     (TSB_CONFIG_MAP_PTE !=
		      दुरत्व(काष्ठा tsb_config, tsb_map_pte)));

	/* Attach to the address space of init_task.  On SMP we
	 * करो this in smp.c:smp_callin क्रम other cpus.
	 */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;
पूर्ण
