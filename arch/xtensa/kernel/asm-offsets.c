<शैली गुरु>
/*
 * arch/xtensa/kernel/यंत्र-offsets.c
 *
 * Generates definitions from c-type काष्ठाures used by assembly sources.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 */

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/coprocessor.h>

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mm.h>
#समावेश <linux/kbuild.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* काष्ठा pt_regs */
	DEFINE(PT_PC, दुरत्व (काष्ठा pt_regs, pc));
	DEFINE(PT_PS, दुरत्व (काष्ठा pt_regs, ps));
	DEFINE(PT_DEPC, दुरत्व (काष्ठा pt_regs, depc));
	DEFINE(PT_EXCCAUSE, दुरत्व (काष्ठा pt_regs, exccause));
	DEFINE(PT_EXCVADDR, दुरत्व (काष्ठा pt_regs, excvaddr));
	DEFINE(PT_DEBUGCAUSE, दुरत्व (काष्ठा pt_regs, debugcause));
	DEFINE(PT_WMASK, दुरत्व (काष्ठा pt_regs, wmask));
	DEFINE(PT_LBEG, दुरत्व (काष्ठा pt_regs, lbeg));
	DEFINE(PT_LEND, दुरत्व (काष्ठा pt_regs, lend));
	DEFINE(PT_LCOUNT, दुरत्व (काष्ठा pt_regs, lcount));
	DEFINE(PT_SAR, दुरत्व (काष्ठा pt_regs, sar));
	DEFINE(PT_ICOUNTLEVEL, दुरत्व (काष्ठा pt_regs, icountlevel));
	DEFINE(PT_SYSCALL, दुरत्व (काष्ठा pt_regs, syscall));
	DEFINE(PT_SCOMPARE1, दुरत्व(काष्ठा pt_regs, scompare1));
	DEFINE(PT_THREADPTR, दुरत्व(काष्ठा pt_regs, thपढ़ोptr));
	DEFINE(PT_AREG, दुरत्व (काष्ठा pt_regs, areg[0]));
	DEFINE(PT_AREG0, दुरत्व (काष्ठा pt_regs, areg[0]));
	DEFINE(PT_AREG1, दुरत्व (काष्ठा pt_regs, areg[1]));
	DEFINE(PT_AREG2, दुरत्व (काष्ठा pt_regs, areg[2]));
	DEFINE(PT_AREG3, दुरत्व (काष्ठा pt_regs, areg[3]));
	DEFINE(PT_AREG4, दुरत्व (काष्ठा pt_regs, areg[4]));
	DEFINE(PT_AREG5, दुरत्व (काष्ठा pt_regs, areg[5]));
	DEFINE(PT_AREG6, दुरत्व (काष्ठा pt_regs, areg[6]));
	DEFINE(PT_AREG7, दुरत्व (काष्ठा pt_regs, areg[7]));
	DEFINE(PT_AREG8, दुरत्व (काष्ठा pt_regs, areg[8]));
	DEFINE(PT_AREG9, दुरत्व (काष्ठा pt_regs, areg[9]));
	DEFINE(PT_AREG10, दुरत्व (काष्ठा pt_regs, areg[10]));
	DEFINE(PT_AREG11, दुरत्व (काष्ठा pt_regs, areg[11]));
	DEFINE(PT_AREG12, दुरत्व (काष्ठा pt_regs, areg[12]));
	DEFINE(PT_AREG13, दुरत्व (काष्ठा pt_regs, areg[13]));
	DEFINE(PT_AREG14, दुरत्व (काष्ठा pt_regs, areg[14]));
	DEFINE(PT_AREG15, दुरत्व (काष्ठा pt_regs, areg[15]));
	DEFINE(PT_WINDOWBASE, दुरत्व (काष्ठा pt_regs, winकरोwbase));
	DEFINE(PT_WINDOWSTART, दुरत्व(काष्ठा pt_regs, winकरोwstart));
	DEFINE(PT_SIZE, माप(काष्ठा pt_regs));
	DEFINE(PT_AREG_END, दुरत्व (काष्ठा pt_regs, areg[XCHAL_NUM_AREGS]));
	DEFINE(PT_USER_SIZE, दुरत्व(काष्ठा pt_regs, areg[XCHAL_NUM_AREGS]));
	DEFINE(PT_XTREGS_OPT, दुरत्व(काष्ठा pt_regs, xtregs_opt));
	DEFINE(XTREGS_OPT_SIZE, माप(xtregs_opt_t));

	/* काष्ठा task_काष्ठा */
	DEFINE(TASK_PTRACE, दुरत्व (काष्ठा task_काष्ठा, ptrace));
	DEFINE(TASK_MM, दुरत्व (काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_ACTIVE_MM, दुरत्व (काष्ठा task_काष्ठा, active_mm));
	DEFINE(TASK_PID, दुरत्व (काष्ठा task_काष्ठा, pid));
	DEFINE(TASK_THREAD, दुरत्व (काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(TASK_THREAD_INFO, दुरत्व (काष्ठा task_काष्ठा, stack));
#अगर_घोषित CONFIG_STACKPROTECTOR
	DEFINE(TASK_STACK_CANARY, दुरत्व(काष्ठा task_काष्ठा, stack_canary));
#पूर्ण_अगर
	DEFINE(TASK_STRUCT_SIZE, माप (काष्ठा task_काष्ठा));

	/* offsets in thपढ़ो_info काष्ठा */
	OFFSET(TI_TASK, thपढ़ो_info, task);
	OFFSET(TI_FLAGS, thपढ़ो_info, flags);
	OFFSET(TI_STSTUS, thपढ़ो_info, status);
	OFFSET(TI_CPU, thपढ़ो_info, cpu);
	OFFSET(TI_PRE_COUNT, thपढ़ो_info, preempt_count);
	OFFSET(TI_ADDR_LIMIT, thपढ़ो_info, addr_limit);

	/* काष्ठा thपढ़ो_info (offset from start_काष्ठा) */
	DEFINE(THREAD_RA, दुरत्व (काष्ठा task_काष्ठा, thपढ़ो.ra));
	DEFINE(THREAD_SP, दुरत्व (काष्ठा task_काष्ठा, thपढ़ो.sp));
	DEFINE(THREAD_CPENABLE, दुरत्व (काष्ठा thपढ़ो_info, cpenable));
#अगर XCHAL_HAVE_EXCLUSIVE
	DEFINE(THREAD_ATOMCTL8, दुरत्व (काष्ठा thपढ़ो_info, atomctl8));
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSORS
	DEFINE(THREAD_XTREGS_CP0, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp0));
	DEFINE(THREAD_XTREGS_CP1, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp1));
	DEFINE(THREAD_XTREGS_CP2, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp2));
	DEFINE(THREAD_XTREGS_CP3, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp3));
	DEFINE(THREAD_XTREGS_CP4, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp4));
	DEFINE(THREAD_XTREGS_CP5, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp5));
	DEFINE(THREAD_XTREGS_CP6, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp6));
	DEFINE(THREAD_XTREGS_CP7, दुरत्व(काष्ठा thपढ़ो_info, xtregs_cp.cp7));
#पूर्ण_अगर
	DEFINE(THREAD_XTREGS_USER, दुरत्व (काष्ठा thपढ़ो_info, xtregs_user));
	DEFINE(XTREGS_USER_SIZE, माप(xtregs_user_t));
	DEFINE(THREAD_CURRENT_DS, दुरत्व (काष्ठा task_काष्ठा, \
	       thपढ़ो.current_ds));

	/* काष्ठा mm_काष्ठा */
	DEFINE(MM_USERS, दुरत्व(काष्ठा mm_काष्ठा, mm_users));
	DEFINE(MM_PGD, दुरत्व (काष्ठा mm_काष्ठा, pgd));
	DEFINE(MM_CONTEXT, दुरत्व (काष्ठा mm_काष्ठा, context));

	/* काष्ठा page */
	DEFINE(PAGE_FLAGS, दुरत्व(काष्ठा page, flags));

	/* स्थिरants */
	DEFINE(_CLONE_VM, CLONE_VM);
	DEFINE(_CLONE_UNTRACED, CLONE_UNTRACED);
	DEFINE(PG_ARCH_1, PG_arch_1);

	/* काष्ठा debug_table */
	DEFINE(DT_DEBUG_EXCEPTION,
	       दुरत्व(काष्ठा debug_table, debug_exception));
	DEFINE(DT_DEBUG_SAVE, दुरत्व(काष्ठा debug_table, debug_save));
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	DEFINE(DT_DBREAKC_SAVE, दुरत्व(काष्ठा debug_table, dअवरोधc_save));
	DEFINE(DT_ICOUNT_SAVE, दुरत्व(काष्ठा debug_table, icount_save));
	DEFINE(DT_ICOUNT_LEVEL_SAVE,
	       दुरत्व(काष्ठा debug_table, icount_level_save));
#पूर्ण_अगर

	/* काष्ठा exc_table */
	DEFINE(EXC_TABLE_KSTK, दुरत्व(काष्ठा exc_table, kstk));
	DEFINE(EXC_TABLE_DOUBLE_SAVE, दुरत्व(काष्ठा exc_table, द्विगुन_save));
	DEFINE(EXC_TABLE_FIXUP, दुरत्व(काष्ठा exc_table, fixup));
	DEFINE(EXC_TABLE_PARAM, दुरत्व(काष्ठा exc_table, fixup_param));
	DEFINE(EXC_TABLE_FAST_USER,
	       दुरत्व(काष्ठा exc_table, fast_user_handler));
	DEFINE(EXC_TABLE_FAST_KERNEL,
	       दुरत्व(काष्ठा exc_table, fast_kernel_handler));
	DEFINE(EXC_TABLE_DEFAULT, दुरत्व(काष्ठा exc_table, शेष_handler));

	वापस 0;
पूर्ण
