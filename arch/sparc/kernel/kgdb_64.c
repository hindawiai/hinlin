<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* kgdb.c: KGDB support क्रम 64-bit sparc.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/context_tracking.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq.h>

#समावेश "kernel.h"

व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw *win;
	पूर्णांक i;

	gdb_regs[GDB_G0] = 0;
	क्रम (i = 0; i < 15; i++)
		gdb_regs[GDB_G1 + i] = regs->u_regs[UREG_G1 + i];

	win = (काष्ठा reg_winकरोw *) (regs->u_regs[UREG_FP] + STACK_BIAS);
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	क्रम (i = GDB_F0; i <= GDB_F62; i++)
		gdb_regs[i] = 0;

	gdb_regs[GDB_PC] = regs->tpc;
	gdb_regs[GDB_NPC] = regs->tnpc;
	gdb_regs[GDB_STATE] = regs->tstate;
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_FPRS] = 0;
	gdb_regs[GDB_Y] = regs->y;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(p);
	बाह्य अचिन्हित पूर्णांक चयन_to_pc;
	बाह्य अचिन्हित पूर्णांक ret_from_विभाजन;
	काष्ठा reg_winकरोw *win;
	अचिन्हित दीर्घ pc, cwp;
	पूर्णांक i;

	क्रम (i = GDB_G0; i < GDB_G6; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_G6] = (अचिन्हित दीर्घ) t;
	gdb_regs[GDB_G7] = (अचिन्हित दीर्घ) p;
	क्रम (i = GDB_O0; i < GDB_SP; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_SP] = t->ksp;
	gdb_regs[GDB_O7] = 0;

	win = (काष्ठा reg_winकरोw *) (t->ksp + STACK_BIAS);
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	क्रम (i = GDB_F0; i <= GDB_F62; i++)
		gdb_regs[i] = 0;

	अगर (t->new_child)
		pc = (अचिन्हित दीर्घ) &ret_from_विभाजन;
	अन्यथा
		pc = (अचिन्हित दीर्घ) &चयन_to_pc;

	gdb_regs[GDB_PC] = pc;
	gdb_regs[GDB_NPC] = pc + 4;

	cwp = __thपढ़ो_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP];

	gdb_regs[GDB_STATE] = (TSTATE_PRIV | TSTATE_IE | cwp);
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_FPRS] = 0;
	gdb_regs[GDB_Y] = 0;
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw *win;
	पूर्णांक i;

	क्रम (i = 0; i < 15; i++)
		regs->u_regs[UREG_G1 + i] = gdb_regs[GDB_G1 + i];

	/* If the TSTATE रेजिस्टर is changing, we have to preserve
	 * the CWP field, otherwise winकरोw save/restore explodes.
	 */
	अगर (regs->tstate != gdb_regs[GDB_STATE]) अणु
		अचिन्हित दीर्घ cwp = regs->tstate & TSTATE_CWP;

		regs->tstate = (gdb_regs[GDB_STATE] & ~TSTATE_CWP) | cwp;
	पूर्ण

	regs->tpc = gdb_regs[GDB_PC];
	regs->tnpc = gdb_regs[GDB_NPC];
	regs->y = gdb_regs[GDB_Y];

	win = (काष्ठा reg_winकरोw *) (regs->u_regs[UREG_FP] + STACK_BIAS);
	क्रम (i = 0; i < 8; i++)
		win->locals[i] = gdb_regs[GDB_L0 + i];
	क्रम (i = 0; i < 8; i++)
		win->ins[i] = gdb_regs[GDB_I0 + i];
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम __irq_entry smp_kgdb_capture_client(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;

	__यंत्र__ __अस्थिर__("rdpr      %%pstate, %0\n\t"
			     "wrpr      %0, %1, %%pstate"
			     : "=r" (flags)
			     : "i" (PSTATE_IE));

	flushw_all();

	अगर (atomic_पढ़ो(&kgdb_active) != -1)
		kgdb_nmicallback(raw_smp_processor_id(), regs);

	__यंत्र__ __अस्थिर__("wrpr	%0, 0, %%pstate"
			     : : "r" (flags));
पूर्ण
#पूर्ण_अगर

पूर्णांक kgdb_arch_handle_exception(पूर्णांक e_vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcomInBuffer, अक्षर *remcomOutBuffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	चयन (remcomInBuffer[0]) अणु
	हाल 'c':
		/* try to पढ़ो optional parameter, pc unchanged अगर no parm */
		ptr = &remcomInBuffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr)) अणु
			linux_regs->tpc = addr;
			linux_regs->tnpc = addr + 4;
		पूर्ण
		fallthrough;

	हाल 'D':
	हाल 'k':
		अगर (linux_regs->tpc == (अचिन्हित दीर्घ) arch_kgdb_अवरोधpoपूर्णांक) अणु
			linux_regs->tpc = linux_regs->tnpc;
			linux_regs->tnpc += 4;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

यंत्रlinkage व्योम kgdb_trap(अचिन्हित दीर्घ trap_level, काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	अचिन्हित दीर्घ flags;

	अगर (user_mode(regs)) अणु
		bad_trap(regs, trap_level);
		जाओ out;
	पूर्ण

	flushw_all();

	local_irq_save(flags);
	kgdb_handle_exception(0x172, SIGTRAP, 0, regs);
	local_irq_restore(flags);
out:
	exception_निकास(prev_state);
पूर्ण

पूर्णांक kgdb_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->tpc = ip;
	regs->tnpc = regs->tpc + 4;
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: ta 0x72 */
	.gdb_bpt_instr		= अणु 0x91, 0xd0, 0x20, 0x72 पूर्ण,
पूर्ण;
