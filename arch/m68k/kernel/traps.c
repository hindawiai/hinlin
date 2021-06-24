<शैली गुरु>
/*
 *  linux/arch/m68k/kernel/traps.c
 *
 *  Copyright (C) 1993, 1994 by Hamish Macकरोnald
 *
 *  68040 fixes by Michael Rausch
 *  68040 fixes by Martin Apel
 *  68040 fixes and ग_लिखोback by Riअक्षरd Zidlicky
 *  68060 fixes by Roman Hodek
 *  68060 fixes by Jesper Skov
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Sets up all exception vectors
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/user.h>
#समावेश <linux/माला.स>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kallsyms.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/fpu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/tlbflush.h>

अटल स्थिर अक्षर *vec_names[] = अणु
	[VEC_RESETSP]	= "RESET SP",
	[VEC_RESETPC]	= "RESET PC",
	[VEC_BUSERR]	= "BUS ERROR",
	[VEC_ADDRERR]	= "ADDRESS ERROR",
	[VEC_ILLEGAL]	= "ILLEGAL INSTRUCTION",
	[VEC_ZERODIV]	= "ZERO DIVIDE",
	[VEC_CHK]	= "CHK",
	[VEC_TRAP]	= "TRAPcc",
	[VEC_PRIV]	= "PRIVILEGE VIOLATION",
	[VEC_TRACE]	= "TRACE",
	[VEC_LINE10]	= "LINE 1010",
	[VEC_LINE11]	= "LINE 1111",
	[VEC_RESV12]	= "UNASSIGNED RESERVED 12",
	[VEC_COPROC]	= "COPROCESSOR PROTOCOL VIOLATION",
	[VEC_FORMAT]	= "FORMAT ERROR",
	[VEC_UNINT]	= "UNINITIALIZED INTERRUPT",
	[VEC_RESV16]	= "UNASSIGNED RESERVED 16",
	[VEC_RESV17]	= "UNASSIGNED RESERVED 17",
	[VEC_RESV18]	= "UNASSIGNED RESERVED 18",
	[VEC_RESV19]	= "UNASSIGNED RESERVED 19",
	[VEC_RESV20]	= "UNASSIGNED RESERVED 20",
	[VEC_RESV21]	= "UNASSIGNED RESERVED 21",
	[VEC_RESV22]	= "UNASSIGNED RESERVED 22",
	[VEC_RESV23]	= "UNASSIGNED RESERVED 23",
	[VEC_SPUR]	= "SPURIOUS INTERRUPT",
	[VEC_INT1]	= "LEVEL 1 INT",
	[VEC_INT2]	= "LEVEL 2 INT",
	[VEC_INT3]	= "LEVEL 3 INT",
	[VEC_INT4]	= "LEVEL 4 INT",
	[VEC_INT5]	= "LEVEL 5 INT",
	[VEC_INT6]	= "LEVEL 6 INT",
	[VEC_INT7]	= "LEVEL 7 INT",
	[VEC_SYS]	= "SYSCALL",
	[VEC_TRAP1]	= "TRAP #1",
	[VEC_TRAP2]	= "TRAP #2",
	[VEC_TRAP3]	= "TRAP #3",
	[VEC_TRAP4]	= "TRAP #4",
	[VEC_TRAP5]	= "TRAP #5",
	[VEC_TRAP6]	= "TRAP #6",
	[VEC_TRAP7]	= "TRAP #7",
	[VEC_TRAP8]	= "TRAP #8",
	[VEC_TRAP9]	= "TRAP #9",
	[VEC_TRAP10]	= "TRAP #10",
	[VEC_TRAP11]	= "TRAP #11",
	[VEC_TRAP12]	= "TRAP #12",
	[VEC_TRAP13]	= "TRAP #13",
	[VEC_TRAP14]	= "TRAP #14",
	[VEC_TRAP15]	= "TRAP #15",
	[VEC_FPBRUC]	= "FPCP BSUN",
	[VEC_FPIR]	= "FPCP INEXACT",
	[VEC_FPDIVZ]	= "FPCP DIV BY 0",
	[VEC_FPUNDER]	= "FPCP UNDERFLOW",
	[VEC_FPOE]	= "FPCP OPERAND ERROR",
	[VEC_FPOVER]	= "FPCP OVERFLOW",
	[VEC_FPन_अंक]	= "FPCP SNAN",
	[VEC_FPUNSUP]	= "FPCP UNSUPPORTED OPERATION",
	[VEC_MMUCFG]	= "MMU CONFIGURATION ERROR",
	[VEC_MMUILL]	= "MMU ILLEGAL OPERATION ERROR",
	[VEC_MMUACC]	= "MMU ACCESS LEVEL VIOLATION ERROR",
	[VEC_RESV59]	= "UNASSIGNED RESERVED 59",
	[VEC_UNIMPEA]	= "UNASSIGNED RESERVED 60",
	[VEC_UNIMPII]	= "UNASSIGNED RESERVED 61",
	[VEC_RESV62]	= "UNASSIGNED RESERVED 62",
	[VEC_RESV63]	= "UNASSIGNED RESERVED 63",
पूर्ण;

अटल स्थिर अक्षर *space_names[] = अणु
	[0]		= "Space 0",
	[USER_DATA]	= "User Data",
	[USER_PROGRAM]	= "User Program",
#अगर_अघोषित CONFIG_SUN3
	[3]		= "Space 3",
#अन्यथा
	[FC_CONTROL]	= "Control",
#पूर्ण_अगर
	[4]		= "Space 4",
	[SUPER_DATA]	= "Super Data",
	[SUPER_PROGRAM]	= "Super Program",
	[CPU_SPACE]	= "CPU"
पूर्ण;

व्योम die_अगर_kernel(अक्षर *,काष्ठा pt_regs *,पूर्णांक);
यंत्रlinkage पूर्णांक करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
                             अचिन्हित दीर्घ error_code);
पूर्णांक send_fault_sig(काष्ठा pt_regs *regs);

यंत्रlinkage व्योम trap_c(काष्ठा frame *fp);

#अगर defined (CONFIG_M68060)
अटल अंतरभूत व्योम access_error060 (काष्ठा frame *fp)
अणु
	अचिन्हित दीर्घ fslw = fp->un.fmt4.pc; /* is really FSLW क्रम access error */

	pr_debug("fslw=%#lx, fa=%#lx\n", fslw, fp->un.fmt4.effaddr);

	अगर (fslw & MMU060_BPE) अणु
		/* branch prediction error -> clear branch cache */
		__यंत्र__ __अस्थिर__ ("movec %/cacr,%/d0\n\t"
				      "orl   #0x00400000,%/d0\n\t"
				      "movec %/d0,%/cacr"
				      : : : "d0" );
		/* वापस अगर there's no other error */
		अगर (!(fslw & MMU060_ERR_BITS) && !(fslw & MMU060_SEE))
			वापस;
	पूर्ण

	अगर (fslw & (MMU060_DESC_ERR | MMU060_WP | MMU060_SP)) अणु
		अचिन्हित दीर्घ errorcode;
		अचिन्हित दीर्घ addr = fp->un.fmt4.effaddr;

		अगर (fslw & MMU060_MA)
			addr = (addr + PAGE_SIZE - 1) & PAGE_MASK;

		errorcode = 1;
		अगर (fslw & MMU060_DESC_ERR) अणु
			__flush_tlb040_one(addr);
			errorcode = 0;
		पूर्ण
		अगर (fslw & MMU060_W)
			errorcode |= 2;
		pr_debug("errorcode = %ld\n", errorcode);
		करो_page_fault(&fp->ptregs, addr, errorcode);
	पूर्ण अन्यथा अगर (fslw & (MMU060_SEE))अणु
		/* Software Emulation Error.
		 * fault during mem_पढ़ो/mem_ग_लिखो in अगरpsp060/os.S
		 */
		send_fault_sig(&fp->ptregs);
	पूर्ण अन्यथा अगर (!(fslw & (MMU060_RE|MMU060_WE)) ||
		   send_fault_sig(&fp->ptregs) > 0) अणु
		pr_err("pc=%#lx, fa=%#lx\n", fp->ptregs.pc,
		       fp->un.fmt4.effaddr);
		pr_err("68060 access error, fslw=%lx\n", fslw);
		trap_c( fp );
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_M68060 */

#अगर defined (CONFIG_M68040)
अटल अंतरभूत अचिन्हित दीर्घ probe040(पूर्णांक isग_लिखो, अचिन्हित दीर्घ addr, पूर्णांक wbs)
अणु
	अचिन्हित दीर्घ mmusr;
	mm_segment_t old_fs = get_fs();

	set_fs(MAKE_MM_SEG(wbs));

	अगर (isग_लिखो)
		यंत्र अस्थिर (".chip 68040; ptestw (%0); .chip 68k" : : "a" (addr));
	अन्यथा
		यंत्र अस्थिर (".chip 68040; ptestr (%0); .chip 68k" : : "a" (addr));

	यंत्र अस्थिर (".chip 68040; movec %%mmusr,%0; .chip 68k" : "=r" (mmusr));

	set_fs(old_fs);

	वापस mmusr;
पूर्ण

अटल अंतरभूत पूर्णांक करो_040ग_लिखोback1(अचिन्हित लघु wbs, अचिन्हित दीर्घ wba,
				   अचिन्हित दीर्घ wbd)
अणु
	पूर्णांक res = 0;
	mm_segment_t old_fs = get_fs();

	/* set_fs can not be moved, otherwise put_user() may oops */
	set_fs(MAKE_MM_SEG(wbs));

	चयन (wbs & WBSIZ_040) अणु
	हाल BA_SIZE_BYTE:
		res = put_user(wbd & 0xff, (अक्षर __user *)wba);
		अवरोध;
	हाल BA_SIZE_WORD:
		res = put_user(wbd & 0xffff, (लघु __user *)wba);
		अवरोध;
	हाल BA_SIZE_LONG:
		res = put_user(wbd, (पूर्णांक __user *)wba);
		अवरोध;
	पूर्ण

	/* set_fs can not be moved, otherwise put_user() may oops */
	set_fs(old_fs);


	pr_debug("do_040writeback1, res=%d\n", res);

	वापस res;
पूर्ण

/* after an exception in a ग_लिखोback the stack frame corresponding
 * to that exception is discarded, set a few bits in the old frame
 * to simulate what it should look like
 */
अटल अंतरभूत व्योम fix_xframe040(काष्ठा frame *fp, अचिन्हित दीर्घ wba, अचिन्हित लघु wbs)
अणु
	fp->un.fmt7.faddr = wba;
	fp->un.fmt7.ssw = wbs & 0xff;
	अगर (wba != current->thपढ़ो.faddr)
	    fp->un.fmt7.ssw |= MA_040;
पूर्ण

अटल अंतरभूत व्योम करो_040ग_लिखोbacks(काष्ठा frame *fp)
अणु
	पूर्णांक res = 0;
#अगर 0
	अगर (fp->un.fmt7.wb1s & WBV_040)
		pr_err("access_error040: cannot handle 1st writeback. oops.\n");
#पूर्ण_अगर

	अगर ((fp->un.fmt7.wb2s & WBV_040) &&
	    !(fp->un.fmt7.wb2s & WBTT_040)) अणु
		res = करो_040ग_लिखोback1(fp->un.fmt7.wb2s, fp->un.fmt7.wb2a,
				       fp->un.fmt7.wb2d);
		अगर (res)
			fix_xframe040(fp, fp->un.fmt7.wb2a, fp->un.fmt7.wb2s);
		अन्यथा
			fp->un.fmt7.wb2s = 0;
	पूर्ण

	/* करो the 2nd wb only अगर the first one was successful (except क्रम a kernel wb) */
	अगर (fp->un.fmt7.wb3s & WBV_040 && (!res || fp->un.fmt7.wb3s & 4)) अणु
		res = करो_040ग_लिखोback1(fp->un.fmt7.wb3s, fp->un.fmt7.wb3a,
				       fp->un.fmt7.wb3d);
		अगर (res)
		    अणु
			fix_xframe040(fp, fp->un.fmt7.wb3a, fp->un.fmt7.wb3s);

			fp->un.fmt7.wb2s = fp->un.fmt7.wb3s;
			fp->un.fmt7.wb3s &= (~WBV_040);
			fp->un.fmt7.wb2a = fp->un.fmt7.wb3a;
			fp->un.fmt7.wb2d = fp->un.fmt7.wb3d;
		    पूर्ण
		अन्यथा
			fp->un.fmt7.wb3s = 0;
	पूर्ण

	अगर (res)
		send_fault_sig(&fp->ptregs);
पूर्ण

/*
 * called from sigवापस(), must ensure userspace code didn't
 * manipulate exception frame to circumvent protection, then complete
 * pending ग_लिखोbacks
 * we just clear TM2 to turn it पूर्णांकo a userspace access
 */
यंत्रlinkage व्योम berr_040cleanup(काष्ठा frame *fp)
अणु
	fp->un.fmt7.wb2s &= ~4;
	fp->un.fmt7.wb3s &= ~4;

	करो_040ग_लिखोbacks(fp);
पूर्ण

अटल अंतरभूत व्योम access_error040(काष्ठा frame *fp)
अणु
	अचिन्हित लघु ssw = fp->un.fmt7.ssw;
	अचिन्हित दीर्घ mmusr;

	pr_debug("ssw=%#x, fa=%#lx\n", ssw, fp->un.fmt7.faddr);
	pr_debug("wb1s=%#x, wb2s=%#x, wb3s=%#x\n", fp->un.fmt7.wb1s,
		fp->un.fmt7.wb2s, fp->un.fmt7.wb3s);
	pr_debug("wb2a=%lx, wb3a=%lx, wb2d=%lx, wb3d=%lx\n",
		fp->un.fmt7.wb2a, fp->un.fmt7.wb3a,
		fp->un.fmt7.wb2d, fp->un.fmt7.wb3d);

	अगर (ssw & ATC_040) अणु
		अचिन्हित दीर्घ addr = fp->un.fmt7.faddr;
		अचिन्हित दीर्घ errorcode;

		/*
		 * The MMU status has to be determined AFTER the address
		 * has been corrected अगर there was a misaligned access (MA).
		 */
		अगर (ssw & MA_040)
			addr = (addr + 7) & -8;

		/* MMU error, get the MMUSR info क्रम this access */
		mmusr = probe040(!(ssw & RW_040), addr, ssw);
		pr_debug("mmusr = %lx\n", mmusr);
		errorcode = 1;
		अगर (!(mmusr & MMU_R_040)) अणु
			/* clear the invalid atc entry */
			__flush_tlb040_one(addr);
			errorcode = 0;
		पूर्ण

		/* despite what करोcumentation seems to say, RMW
		 * accesses have always both the LK and RW bits set */
		अगर (!(ssw & RW_040) || (ssw & LK_040))
			errorcode |= 2;

		अगर (करो_page_fault(&fp->ptregs, addr, errorcode)) अणु
			pr_debug("do_page_fault() !=0\n");
			अगर (user_mode(&fp->ptregs))अणु
				/* delay ग_लिखोbacks after संकेत delivery */
				pr_debug(".. was usermode - return\n");
				वापस;
			पूर्ण
			/* disable ग_लिखोback पूर्णांकo user space from kernel
			 * (अगर करो_page_fault didn't fix the mapping,
                         * the ग_लिखोback won't करो good)
			 */
disable_wb:
			pr_debug(".. disabling wb2\n");
			अगर (fp->un.fmt7.wb2a == fp->un.fmt7.faddr)
				fp->un.fmt7.wb2s &= ~WBV_040;
			अगर (fp->un.fmt7.wb3a == fp->un.fmt7.faddr)
				fp->un.fmt7.wb3s &= ~WBV_040;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In हाल of a bus error we either समाप्त the process or expect
		 * the kernel to catch the fault, which then is also responsible
		 * क्रम cleaning up the mess.
		 */
		current->thपढ़ो.signo = SIGBUS;
		current->thपढ़ो.faddr = fp->un.fmt7.faddr;
		अगर (send_fault_sig(&fp->ptregs) >= 0)
			pr_err("68040 bus error (ssw=%x, faddr=%lx)\n", ssw,
			       fp->un.fmt7.faddr);
		जाओ disable_wb;
	पूर्ण

	करो_040ग_लिखोbacks(fp);
पूर्ण
#पूर्ण_अगर /* CONFIG_M68040 */

#अगर defined(CONFIG_SUN3)
#समावेश <यंत्र/sun3mmu.h>

बाह्य पूर्णांक mmu_emu_handle_fault (अचिन्हित दीर्घ, पूर्णांक, पूर्णांक);

/* sun3 version of bus_error030 */

अटल अंतरभूत व्योम bus_error030 (काष्ठा frame *fp)
अणु
	अचिन्हित अक्षर buserr_type = sun3_get_buserr ();
	अचिन्हित दीर्घ addr, errorcode;
	अचिन्हित लघु ssw = fp->un.fmtb.ssw;
	बाह्य अचिन्हित दीर्घ _sun3_map_test_start, _sun3_map_test_end;

	अगर (ssw & (FC | FB))
		pr_debug("Instruction fault at %#010lx\n",
			ssw & FC ?
			fp->ptregs.क्रमmat == 0xa ? fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2
			:
			fp->ptregs.क्रमmat == 0xa ? fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
	अगर (ssw & DF)
		pr_debug("Data %s fault at %#010lx in %s (pc=%#lx)\n",
			ssw & RW ? "read" : "write",
			fp->un.fmtb.daddr,
			space_names[ssw & DFC], fp->ptregs.pc);

	/*
	 * Check अगर this page should be demand-mapped. This needs to go beक्रमe
	 * the testing क्रम a bad kernel-space access (demand-mapping applies
	 * to kernel accesses too).
	 */

	अगर ((ssw & DF)
	    && (buserr_type & (SUN3_BUSERR_PROTERR | SUN3_BUSERR_INVALID))) अणु
		अगर (mmu_emu_handle_fault (fp->un.fmtb.daddr, ssw & RW, 0))
			वापस;
	पूर्ण

	/* Check क्रम kernel-space pagefault (BAD). */
	अगर (fp->ptregs.sr & PS_S) अणु
		/* kernel fault must be a data fault to user space */
		अगर (! ((ssw & DF) && ((ssw & DFC) == USER_DATA))) अणु
		     // try checking the kernel mappings beक्रमe surrender
		     अगर (mmu_emu_handle_fault (fp->un.fmtb.daddr, ssw & RW, 1))
			  वापस;
			/* inकाष्ठाion fault or kernel data fault! */
			अगर (ssw & (FC | FB))
				pr_err("Instruction fault at %#010lx\n",
					fp->ptregs.pc);
			अगर (ssw & DF) अणु
				/* was this fault incurred testing bus mappings? */
				अगर((fp->ptregs.pc >= (अचिन्हित दीर्घ)&_sun3_map_test_start) &&
				   (fp->ptregs.pc <= (अचिन्हित दीर्घ)&_sun3_map_test_end)) अणु
					send_fault_sig(&fp->ptregs);
					वापस;
				पूर्ण

				pr_err("Data %s fault at %#010lx in %s (pc=%#lx)\n",
					ssw & RW ? "read" : "write",
					fp->un.fmtb.daddr,
					space_names[ssw & DFC], fp->ptregs.pc);
			पूर्ण
			pr_err("BAD KERNEL BUSERR\n");

			die_अगर_kernel("Oops", &fp->ptregs,0);
			क्रमce_sig(SIGKILL);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* user fault */
		अगर (!(ssw & (FC | FB)) && !(ssw & DF))
			/* not an inकाष्ठाion fault or data fault! BAD */
			panic ("USER BUSERR w/o instruction or data fault");
	पूर्ण


	/* First handle the data fault, अगर any.  */
	अगर (ssw & DF) अणु
		addr = fp->un.fmtb.daddr;

// errorcode bit 0:	0 -> no page		1 -> protection fault
// errorcode bit 1:	0 -> पढ़ो fault		1 -> ग_लिखो fault

// (buserr_type & SUN3_BUSERR_PROTERR)	-> protection fault
// (buserr_type & SUN3_BUSERR_INVALID)	-> invalid page fault

		अगर (buserr_type & SUN3_BUSERR_PROTERR)
			errorcode = 0x01;
		अन्यथा अगर (buserr_type & SUN3_BUSERR_INVALID)
			errorcode = 0x00;
		अन्यथा अणु
			pr_debug("*** unexpected busfault type=%#04x\n",
				 buserr_type);
			pr_debug("invalid %s access at %#lx from pc %#lx\n",
				 !(ssw & RW) ? "write" : "read", addr,
				 fp->ptregs.pc);
			die_अगर_kernel ("Oops", &fp->ptregs, buserr_type);
			क्रमce_sig (SIGBUS);
			वापस;
		पूर्ण

//toकरो: wtf is RM bit? --m
		अगर (!(ssw & RW) || ssw & RM)
			errorcode |= 0x02;

		/* Handle page fault. */
		करो_page_fault (&fp->ptregs, addr, errorcode);

		/* Retry the data fault now. */
		वापस;
	पूर्ण

	/* Now handle the inकाष्ठाion fault. */

	/* Get the fault address. */
	अगर (fp->ptregs.क्रमmat == 0xA)
		addr = fp->ptregs.pc + 4;
	अन्यथा
		addr = fp->un.fmtb.baddr;
	अगर (ssw & FC)
		addr -= 2;

	अगर (buserr_type & SUN3_BUSERR_INVALID) अणु
		अगर (!mmu_emu_handle_fault(addr, 1, 0))
			करो_page_fault (&fp->ptregs, addr, 0);
       पूर्ण अन्यथा अणु
		pr_debug("protection fault on insn access (segv).\n");
		क्रमce_sig (संक_अंश);
       पूर्ण
पूर्ण
#अन्यथा
#अगर defined(CPU_M68020_OR_M68030)
अटल अंतरभूत व्योम bus_error030 (काष्ठा frame *fp)
अणु
	अस्थिर अचिन्हित लघु temp;
	अचिन्हित लघु mmusr;
	अचिन्हित दीर्घ addr, errorcode;
	अचिन्हित लघु ssw = fp->un.fmtb.ssw;
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ desc;
#पूर्ण_अगर

	pr_debug("pid = %x  ", current->pid);
	pr_debug("SSW=%#06x  ", ssw);

	अगर (ssw & (FC | FB))
		pr_debug("Instruction fault at %#010lx\n",
			ssw & FC ?
			fp->ptregs.क्रमmat == 0xa ? fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2
			:
			fp->ptregs.क्रमmat == 0xa ? fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
	अगर (ssw & DF)
		pr_debug("Data %s fault at %#010lx in %s (pc=%#lx)\n",
			ssw & RW ? "read" : "write",
			fp->un.fmtb.daddr,
			space_names[ssw & DFC], fp->ptregs.pc);

	/* ++andreas: If a data fault and an inकाष्ठाion fault happen
	   at the same समय map in both pages.  */

	/* First handle the data fault, अगर any.  */
	अगर (ssw & DF) अणु
		addr = fp->un.fmtb.daddr;

#अगर_घोषित DEBUG
		यंत्र अस्थिर ("ptestr %3,%2@,#7,%0\n\t"
			      "pmove %%psr,%1"
			      : "=a&" (desc), "=m" (temp)
			      : "a" (addr), "d" (ssw));
		pr_debug("mmusr is %#x for addr %#lx in task %p\n",
			 temp, addr, current);
		pr_debug("descriptor address is 0x%p, contents %#lx\n",
			 __va(desc), *(अचिन्हित दीर्घ *)__va(desc));
#अन्यथा
		यंत्र अस्थिर ("ptestr %2,%1@,#7\n\t"
			      "pmove %%psr,%0"
			      : "=m" (temp) : "a" (addr), "d" (ssw));
#पूर्ण_अगर
		mmusr = temp;
		errorcode = (mmusr & MMU_I) ? 0 : 1;
		अगर (!(ssw & RW) || (ssw & RM))
			errorcode |= 2;

		अगर (mmusr & (MMU_I | MMU_WP)) अणु
			अगर (ssw & 4) अणु
				pr_err("Data %s fault at %#010lx in %s (pc=%#lx)\n",
				       ssw & RW ? "read" : "write",
				       fp->un.fmtb.daddr,
				       space_names[ssw & DFC], fp->ptregs.pc);
				जाओ buserr;
			पूर्ण
			/* Don't try to करो anything further अगर an exception was
			   handled. */
			अगर (करो_page_fault (&fp->ptregs, addr, errorcode) < 0)
				वापस;
		पूर्ण अन्यथा अगर (!(mmusr & MMU_I)) अणु
			/* probably a 020 cas fault */
			अगर (!(ssw & RM) && send_fault_sig(&fp->ptregs) > 0)
				pr_err("unexpected bus error (%#x,%#x)\n", ssw,
				       mmusr);
		पूर्ण अन्यथा अगर (mmusr & (MMU_B|MMU_L|MMU_S)) अणु
			pr_err("invalid %s access at %#lx from pc %#lx\n",
			       !(ssw & RW) ? "write" : "read", addr,
			       fp->ptregs.pc);
			die_अगर_kernel("Oops",&fp->ptregs,mmusr);
			क्रमce_sig(संक_अंश);
			वापस;
		पूर्ण अन्यथा अणु
#अगर 0
			अटल अस्थिर दीर्घ tदीर्घ;
#पूर्ण_अगर

			pr_err("weird %s access at %#lx from pc %#lx (ssw is %#x)\n",
			       !(ssw & RW) ? "write" : "read", addr,
			       fp->ptregs.pc, ssw);
			यंत्र अस्थिर ("ptestr #1,%1@,#0\n\t"
				      "pmove %%psr,%0"
				      : "=m" (temp)
				      : "a" (addr));
			mmusr = temp;

			pr_err("level 0 mmusr is %#x\n", mmusr);
#अगर 0
			यंत्र अस्थिर ("pmove %%tt0,%0"
				      : "=m" (tदीर्घ));
			pr_debug("tt0 is %#lx, ", tदीर्घ);
			यंत्र अस्थिर ("pmove %%tt1,%0"
				      : "=m" (tदीर्घ));
			pr_debug("tt1 is %#lx\n", tदीर्घ);
#पूर्ण_अगर
			pr_debug("Unknown SIGSEGV - 1\n");
			die_अगर_kernel("Oops",&fp->ptregs,mmusr);
			क्रमce_sig(संक_अंश);
			वापस;
		पूर्ण

		/* setup an ATC entry क्रम the access about to be retried */
		अगर (!(ssw & RW) || (ssw & RM))
			यंत्र अस्थिर ("ploadw %1,%0@" : /* no outमाला_दो */
				      : "a" (addr), "d" (ssw));
		अन्यथा
			यंत्र अस्थिर ("ploadr %1,%0@" : /* no outमाला_दो */
				      : "a" (addr), "d" (ssw));
	पूर्ण

	/* Now handle the inकाष्ठाion fault. */

	अगर (!(ssw & (FC|FB)))
		वापस;

	अगर (fp->ptregs.sr & PS_S) अणु
		pr_err("Instruction fault at %#010lx\n", fp->ptregs.pc);
	buserr:
		pr_err("BAD KERNEL BUSERR\n");
		die_अगर_kernel("Oops",&fp->ptregs,0);
		क्रमce_sig(SIGKILL);
		वापस;
	पूर्ण

	/* get the fault address */
	अगर (fp->ptregs.क्रमmat == 10)
		addr = fp->ptregs.pc + 4;
	अन्यथा
		addr = fp->un.fmtb.baddr;
	अगर (ssw & FC)
		addr -= 2;

	अगर ((ssw & DF) && ((addr ^ fp->un.fmtb.daddr) & PAGE_MASK) == 0)
		/* Insn fault on same page as data fault.  But we
		   should still create the ATC entry.  */
		जाओ create_atc_entry;

#अगर_घोषित DEBUG
	यंत्र अस्थिर ("ptestr #1,%2@,#7,%0\n\t"
		      "pmove %%psr,%1"
		      : "=a&" (desc), "=m" (temp)
		      : "a" (addr));
	pr_debug("mmusr is %#x for addr %#lx in task %p\n",
		temp, addr, current);
	pr_debug("descriptor address is 0x%p, contents %#lx\n",
		__va(desc), *(अचिन्हित दीर्घ *)__va(desc));
#अन्यथा
	यंत्र अस्थिर ("ptestr #1,%1@,#7\n\t"
		      "pmove %%psr,%0"
		      : "=m" (temp) : "a" (addr));
#पूर्ण_अगर
	mmusr = temp;
	अगर (mmusr & MMU_I)
		करो_page_fault (&fp->ptregs, addr, 0);
	अन्यथा अगर (mmusr & (MMU_B|MMU_L|MMU_S)) अणु
		pr_err("invalid insn access at %#lx from pc %#lx\n",
			addr, fp->ptregs.pc);
		pr_debug("Unknown SIGSEGV - 2\n");
		die_अगर_kernel("Oops",&fp->ptregs,mmusr);
		क्रमce_sig(संक_अंश);
		वापस;
	पूर्ण

create_atc_entry:
	/* setup an ATC entry क्रम the access about to be retried */
	यंत्र अस्थिर ("ploadr #2,%0@" : /* no outमाला_दो */
		      : "a" (addr));
पूर्ण
#पूर्ण_अगर /* CPU_M68020_OR_M68030 */
#पूर्ण_अगर /* !CONFIG_SUN3 */

#अगर defined(CONFIG_COLDFIRE) && defined(CONFIG_MMU)
#समावेश <यंत्र/mcfmmu.h>

/*
 *	The following table converts the FS encoding of a ColdFire
 *	exception stack frame पूर्णांकo the error_code value needed by
 *	करो_fault.
*/
अटल स्थिर अचिन्हित अक्षर fs_err_code[] = अणु
	0,  /* 0000 */
	0,  /* 0001 */
	0,  /* 0010 */
	0,  /* 0011 */
	1,  /* 0100 */
	0,  /* 0101 */
	0,  /* 0110 */
	0,  /* 0111 */
	2,  /* 1000 */
	3,  /* 1001 */
	2,  /* 1010 */
	0,  /* 1011 */
	1,  /* 1100 */
	1,  /* 1101 */
	0,  /* 1110 */
	0   /* 1111 */
पूर्ण;

अटल अंतरभूत व्योम access_errorcf(अचिन्हित पूर्णांक fs, काष्ठा frame *fp)
अणु
	अचिन्हित दीर्घ mmusr, addr;
	अचिन्हित पूर्णांक err_code;
	पूर्णांक need_page_fault;

	mmusr = mmu_पढ़ो(MMUSR);
	addr = mmu_पढ़ो(MMUAR);

	/*
	 * error_code:
	 *	bit 0 == 0 means no page found, 1 means protection fault
	 *	bit 1 == 0 means पढ़ो, 1 means ग_लिखो
	 */
	चयन (fs) अणु
	हाल  5:  /* 0101 TLB opword X miss */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 0, 0);
		addr = fp->ptregs.pc;
		अवरोध;
	हाल  6:  /* 0110 TLB extension word X miss */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 0, 1);
		addr = fp->ptregs.pc + माप(दीर्घ);
		अवरोध;
	हाल 10:  /* 1010 TLB W miss */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 1, 1, 0);
		अवरोध;
	हाल 14: /* 1110 TLB R miss */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 1, 0);
		अवरोध;
	शेष:
		/* 0000 Normal  */
		/* 0001 Reserved */
		/* 0010 Interrupt during debug service routine */
		/* 0011 Reserved */
		/* 0100 X Protection */
		/* 0111 IFP in emulator mode */
		/* 1000 W Protection*/
		/* 1001 Write error*/
		/* 1011 Reserved*/
		/* 1100 R Protection*/
		/* 1101 R Protection*/
		/* 1111 OEP in emulator mode*/
		need_page_fault = 1;
		अवरोध;
	पूर्ण

	अगर (need_page_fault) अणु
		err_code = fs_err_code[fs];
		अगर ((fs == 13) && (mmusr & MMUSR_WF)) /* rd-mod-wr access */
			err_code |= 2; /* bit1 - ग_लिखो, bit0 - protection */
		करो_page_fault(&fp->ptregs, addr, err_code);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_COLDFIRE CONFIG_MMU */

यंत्रlinkage व्योम buserr_c(काष्ठा frame *fp)
अणु
	/* Only set esp0 अगर coming from user mode */
	अगर (user_mode(&fp->ptregs))
		current->thपढ़ो.esp0 = (अचिन्हित दीर्घ) fp;

	pr_debug("*** Bus Error *** Format is %x\n", fp->ptregs.क्रमmat);

#अगर defined(CONFIG_COLDFIRE) && defined(CONFIG_MMU)
	अगर (CPU_IS_COLDFIRE) अणु
		अचिन्हित पूर्णांक fs;
		fs = (fp->ptregs.vector & 0x3) |
			((fp->ptregs.vector & 0xc00) >> 8);
		चयन (fs) अणु
		हाल 0x5:
		हाल 0x6:
		हाल 0x7:
		हाल 0x9:
		हाल 0xa:
		हाल 0xd:
		हाल 0xe:
		हाल 0xf:
			access_errorcf(fs, fp);
			वापस;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_COLDFIRE && CONFIG_MMU */

	चयन (fp->ptregs.क्रमmat) अणु
#अगर defined (CONFIG_M68060)
	हाल 4:				/* 68060 access error */
	  access_error060 (fp);
	  अवरोध;
#पूर्ण_अगर
#अगर defined (CONFIG_M68040)
	हाल 0x7:			/* 68040 access error */
	  access_error040 (fp);
	  अवरोध;
#पूर्ण_अगर
#अगर defined (CPU_M68020_OR_M68030)
	हाल 0xa:
	हाल 0xb:
	  bus_error030 (fp);
	  अवरोध;
#पूर्ण_अगर
	शेष:
	  die_अगर_kernel("bad frame format",&fp->ptregs,0);
	  pr_debug("Unknown SIGSEGV - 4\n");
	  क्रमce_sig(संक_अंश);
	पूर्ण
पूर्ण


अटल पूर्णांक kstack_depth_to_prपूर्णांक = 48;

अटल व्योम show_trace(अचिन्हित दीर्घ *stack, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *endstack;
	अचिन्हित दीर्घ addr;
	पूर्णांक i;

	prपूर्णांकk("%sCall Trace:", loglvl);
	addr = (अचिन्हित दीर्घ)stack + THREAD_SIZE - 1;
	endstack = (अचिन्हित दीर्घ *)(addr & -THREAD_SIZE);
	i = 0;
	जबतक (stack + 1 <= endstack) अणु
		addr = *stack++;
		/*
		 * If the address is either in the text segment of the
		 * kernel, or in the region which contains vदो_स्मृति'ed
		 * memory, it *may* be the address of a calling
		 * routine; अगर so, prपूर्णांक it so that someone tracing
		 * करोwn the cause of the crash will be able to figure
		 * out the call path that was taken.
		 */
		अगर (__kernel_text_address(addr)) अणु
#अगर_अघोषित CONFIG_KALLSYMS
			अगर (i % 5 == 0)
				pr_cont("\n       ");
#पूर्ण_अगर
			pr_cont(" [<%08lx>] %pS\n", addr, (व्योम *)addr);
			i++;
		पूर्ण
	पूर्ण
	pr_cont("\n");
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs)
अणु
	काष्ठा frame *fp = (काष्ठा frame *)regs;
	u16 c, *cp;
	अचिन्हित दीर्घ addr;
	पूर्णांक i;

	prपूर्णांक_modules();
	pr_info("PC: [<%08lx>] %pS\n", regs->pc, (व्योम *)regs->pc);
	pr_info("SR: %04x  SP: %p  a2: %08lx\n", regs->sr, regs, regs->a2);
	pr_info("d0: %08lx    d1: %08lx    d2: %08lx    d3: %08lx\n",
	       regs->d0, regs->d1, regs->d2, regs->d3);
	pr_info("d4: %08lx    d5: %08lx    a0: %08lx    a1: %08lx\n",
	       regs->d4, regs->d5, regs->a0, regs->a1);

	pr_info("Process %s (pid: %d, task=%p)\n",
		current->comm, task_pid_nr(current), current);
	addr = (अचिन्हित दीर्घ)&fp->un;
	pr_info("Frame format=%X ", regs->क्रमmat);
	चयन (regs->क्रमmat) अणु
	हाल 0x2:
		pr_cont("instr addr=%08lx\n", fp->un.fmt2.iaddr);
		addr += माप(fp->un.fmt2);
		अवरोध;
	हाल 0x3:
		pr_cont("eff addr=%08lx\n", fp->un.fmt3.effaddr);
		addr += माप(fp->un.fmt3);
		अवरोध;
	हाल 0x4:
		अगर (CPU_IS_060)
			pr_cont("fault addr=%08lx fslw=%08lx\n",
				fp->un.fmt4.effaddr, fp->un.fmt4.pc);
		अन्यथा
			pr_cont("eff addr=%08lx pc=%08lx\n",
				fp->un.fmt4.effaddr, fp->un.fmt4.pc);
		addr += माप(fp->un.fmt4);
		अवरोध;
	हाल 0x7:
		pr_cont("eff addr=%08lx ssw=%04x faddr=%08lx\n",
			fp->un.fmt7.effaddr, fp->un.fmt7.ssw, fp->un.fmt7.faddr);
		pr_info("wb 1 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb1s, fp->un.fmt7.wb1a, fp->un.fmt7.wb1dpd0);
		pr_info("wb 2 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb2s, fp->un.fmt7.wb2a, fp->un.fmt7.wb2d);
		pr_info("wb 3 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb3s, fp->un.fmt7.wb3a, fp->un.fmt7.wb3d);
		pr_info("push data: %08lx %08lx %08lx %08lx\n",
			fp->un.fmt7.wb1dpd0, fp->un.fmt7.pd1, fp->un.fmt7.pd2,
			fp->un.fmt7.pd3);
		addr += माप(fp->un.fmt7);
		अवरोध;
	हाल 0x9:
		pr_cont("instr addr=%08lx\n", fp->un.fmt9.iaddr);
		addr += माप(fp->un.fmt9);
		अवरोध;
	हाल 0xa:
		pr_cont("ssw=%04x isc=%04x isb=%04x daddr=%08lx dobuf=%08lx\n",
			fp->un.fmta.ssw, fp->un.fmta.isc, fp->un.fmta.isb,
			fp->un.fmta.daddr, fp->un.fmta.करोbuf);
		addr += माप(fp->un.fmta);
		अवरोध;
	हाल 0xb:
		pr_cont("ssw=%04x isc=%04x isb=%04x daddr=%08lx dobuf=%08lx\n",
			fp->un.fmtb.ssw, fp->un.fmtb.isc, fp->un.fmtb.isb,
			fp->un.fmtb.daddr, fp->un.fmtb.करोbuf);
		pr_info("baddr=%08lx dibuf=%08lx ver=%x\n",
			fp->un.fmtb.baddr, fp->un.fmtb.dibuf, fp->un.fmtb.ver);
		addr += माप(fp->un.fmtb);
		अवरोध;
	शेष:
		pr_cont("\n");
	पूर्ण
	show_stack(शून्य, (अचिन्हित दीर्घ *)addr, KERN_INFO);

	pr_info("Code:");
	cp = (u16 *)regs->pc;
	क्रम (i = -8; i < 16; i++) अणु
		अगर (get_kernel_nofault(c, cp + i) && i >= 0) अणु
			pr_cont(" Bad PC value.");
			अवरोध;
		पूर्ण
		अगर (i)
			pr_cont(" %04x", c);
		अन्यथा
			pr_cont(" <%04x>", c);
	पूर्ण
	pr_cont("\n");
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *stack,
		स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *p;
	अचिन्हित दीर्घ *endstack;
	पूर्णांक i;

	अगर (!stack) अणु
		अगर (task)
			stack = (अचिन्हित दीर्घ *)task->thपढ़ो.esp0;
		अन्यथा
			stack = (अचिन्हित दीर्घ *)&stack;
	पूर्ण
	endstack = (अचिन्हित दीर्घ *)(((अचिन्हित दीर्घ)stack + THREAD_SIZE - 1) & -THREAD_SIZE);

	prपूर्णांकk("%sStack from %08lx:", loglvl, (अचिन्हित दीर्घ)stack);
	p = stack;
	क्रम (i = 0; i < kstack_depth_to_prपूर्णांक; i++) अणु
		अगर (p + 1 > endstack)
			अवरोध;
		अगर (i % 8 == 0)
			pr_cont("\n       ");
		pr_cont(" %08lx", *p++);
	पूर्ण
	pr_cont("\n");
	show_trace(stack, loglvl);
पूर्ण

/*
 * The vector number वापसed in the frame poपूर्णांकer may also contain
 * the "fs" (Fault Status) bits on ColdFire. These are in the bottom
 * 2 bits, and upper 2 bits. So we need to mask out the real vector
 * number beक्रमe using it in comparisons. You करोn't need to करो this on
 * real 68k parts, but it won't hurt either.
 */

व्योम bad_super_trap (काष्ठा frame *fp)
अणु
	पूर्णांक vector = (fp->ptregs.vector >> 2) & 0xff;

	console_verbose();
	अगर (vector < ARRAY_SIZE(vec_names))
		pr_err("*** %s ***   FORMAT=%X\n",
			vec_names[vector],
			fp->ptregs.क्रमmat);
	अन्यथा
		pr_err("*** Exception %d ***   FORMAT=%X\n",
			vector, fp->ptregs.क्रमmat);
	अगर (vector == VEC_ADDRERR && CPU_IS_020_OR_030) अणु
		अचिन्हित लघु ssw = fp->un.fmtb.ssw;

		pr_err("SSW=%#06x  ", ssw);

		अगर (ssw & RC)
			pr_err("Pipe stage C instruction fault at %#010lx\n",
				(fp->ptregs.क्रमmat) == 0xA ?
				fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2);
		अगर (ssw & RB)
			pr_err("Pipe stage B instruction fault at %#010lx\n",
				(fp->ptregs.क्रमmat) == 0xA ?
				fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
		अगर (ssw & DF)
			pr_err("Data %s fault at %#010lx in %s (pc=%#lx)\n",
				ssw & RW ? "read" : "write",
				fp->un.fmtb.daddr, space_names[ssw & DFC],
				fp->ptregs.pc);
	पूर्ण
	pr_err("Current process id is %d\n", task_pid_nr(current));
	die_अगर_kernel("BAD KERNEL TRAP", &fp->ptregs, 0);
पूर्ण

यंत्रlinkage व्योम trap_c(काष्ठा frame *fp)
अणु
	पूर्णांक sig, si_code;
	व्योम __user *addr;
	पूर्णांक vector = (fp->ptregs.vector >> 2) & 0xff;

	अगर (fp->ptregs.sr & PS_S) अणु
		अगर (vector == VEC_TRACE) अणु
			/* traced a trapping inकाष्ठाion on a 68020/30,
			 * real exception will be executed afterwards.
			 */
			वापस;
		पूर्ण
#अगर_घोषित CONFIG_MMU
		अगर (fixup_exception(&fp->ptregs))
			वापस;
#पूर्ण_अगर
		bad_super_trap(fp);
		वापस;
	पूर्ण

	/* send the appropriate संकेत to the user program */
	चयन (vector) अणु
	    हाल VEC_ADDRERR:
		si_code = BUS_ADRALN;
		sig = SIGBUS;
		अवरोध;
	    हाल VEC_ILLEGAL:
	    हाल VEC_LINE10:
	    हाल VEC_LINE11:
		si_code = ILL_ILLOPC;
		sig = संक_अवैध;
		अवरोध;
	    हाल VEC_PRIV:
		si_code = ILL_PRVOPC;
		sig = संक_अवैध;
		अवरोध;
	    हाल VEC_COPROC:
		si_code = ILL_COPROC;
		sig = संक_अवैध;
		अवरोध;
	    हाल VEC_TRAP1:
	    हाल VEC_TRAP2:
	    हाल VEC_TRAP3:
	    हाल VEC_TRAP4:
	    हाल VEC_TRAP5:
	    हाल VEC_TRAP6:
	    हाल VEC_TRAP7:
	    हाल VEC_TRAP8:
	    हाल VEC_TRAP9:
	    हाल VEC_TRAP10:
	    हाल VEC_TRAP11:
	    हाल VEC_TRAP12:
	    हाल VEC_TRAP13:
	    हाल VEC_TRAP14:
		si_code = ILL_ILLTRP;
		sig = संक_अवैध;
		अवरोध;
	    हाल VEC_FPBRUC:
	    हाल VEC_FPOE:
	    हाल VEC_FPन_अंक:
		si_code = FPE_FLTINV;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_FPIR:
		si_code = FPE_FLTRES;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_FPDIVZ:
		si_code = FPE_FLTDIV;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_FPUNDER:
		si_code = FPE_FLTUND;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_FPOVER:
		si_code = FPE_FLTOVF;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_ZERODIV:
		si_code = FPE_INTDIV;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_CHK:
	    हाल VEC_TRAP:
		si_code = FPE_INTOVF;
		sig = संक_भ_त्रुटि;
		अवरोध;
	    हाल VEC_TRACE:		/* ptrace single step */
		si_code = TRAP_TRACE;
		sig = SIGTRAP;
		अवरोध;
	    हाल VEC_TRAP15:		/* अवरोधpoपूर्णांक */
		si_code = TRAP_BRKPT;
		sig = SIGTRAP;
		अवरोध;
	    शेष:
		si_code = ILL_ILLOPC;
		sig = संक_अवैध;
		अवरोध;
	पूर्ण
	चयन (fp->ptregs.क्रमmat) अणु
	    शेष:
		addr = (व्योम __user *) fp->ptregs.pc;
		अवरोध;
	    हाल 2:
		addr = (व्योम __user *) fp->un.fmt2.iaddr;
		अवरोध;
	    हाल 7:
		addr = (व्योम __user *) fp->un.fmt7.effaddr;
		अवरोध;
	    हाल 9:
		addr = (व्योम __user *) fp->un.fmt9.iaddr;
		अवरोध;
	    हाल 10:
		addr = (व्योम __user *) fp->un.fmta.daddr;
		अवरोध;
	    हाल 11:
		addr = (व्योम __user*) fp->un.fmtb.daddr;
		अवरोध;
	पूर्ण
	क्रमce_sig_fault(sig, si_code, addr);
पूर्ण

व्योम die_अगर_kernel (अक्षर *str, काष्ठा pt_regs *fp, पूर्णांक nr)
अणु
	अगर (!(fp->sr & PS_S))
		वापस;

	console_verbose();
	pr_crit("%s: %08x\n", str, nr);
	show_रेजिस्टरs(fp);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	करो_निकास(संक_अंश);
पूर्ण

यंत्रlinkage व्योम set_esp0(अचिन्हित दीर्घ ssp)
अणु
	current->thपढ़ो.esp0 = ssp;
पूर्ण

/*
 * This function is called अगर an error occur जबतक accessing
 * user-space from the fpsp040 code.
 */
यंत्रlinkage व्योम fpsp040_die(व्योम)
अणु
	करो_निकास(संक_अंश);
पूर्ण

#अगर_घोषित CONFIG_M68KFPU_EMU
यंत्रlinkage व्योम fpemu_संकेत(पूर्णांक संकेत, पूर्णांक code, व्योम *addr)
अणु
	क्रमce_sig_fault(संकेत, code, addr);
पूर्ण
#पूर्ण_अगर
