<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* kgdb.c: KGDB support क्रम 32-bit sparc.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "kernel.h"
#समावेश "entry.h"

व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 *win;
	पूर्णांक i;

	gdb_regs[GDB_G0] = 0;
	क्रम (i = 0; i < 15; i++)
		gdb_regs[GDB_G1 + i] = regs->u_regs[UREG_G1 + i];

	win = (काष्ठा reg_winकरोw32 *) regs->u_regs[UREG_FP];
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	क्रम (i = GDB_F0; i <= GDB_F31; i++)
		gdb_regs[i] = 0;

	gdb_regs[GDB_Y] = regs->y;
	gdb_regs[GDB_PSR] = regs->psr;
	gdb_regs[GDB_WIM] = 0;
	gdb_regs[GDB_TBR] = (अचिन्हित दीर्घ) &trapbase;
	gdb_regs[GDB_PC] = regs->pc;
	gdb_regs[GDB_NPC] = regs->npc;
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_CSR] = 0;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा thपढ़ो_info *t = task_thपढ़ो_info(p);
	काष्ठा reg_winकरोw32 *win;
	पूर्णांक i;

	क्रम (i = GDB_G0; i < GDB_G6; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_G6] = (अचिन्हित दीर्घ) t;
	gdb_regs[GDB_G7] = 0;
	क्रम (i = GDB_O0; i < GDB_SP; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_SP] = t->ksp;
	gdb_regs[GDB_O7] = 0;

	win = (काष्ठा reg_winकरोw32 *) t->ksp;
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	क्रम (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	क्रम (i = GDB_F0; i <= GDB_F31; i++)
		gdb_regs[i] = 0;

	gdb_regs[GDB_Y] = 0;

	gdb_regs[GDB_PSR] = t->kpsr;
	gdb_regs[GDB_WIM] = t->kwim;
	gdb_regs[GDB_TBR] = (अचिन्हित दीर्घ) &trapbase;
	gdb_regs[GDB_PC] = t->kpc;
	gdb_regs[GDB_NPC] = t->kpc + 4;
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_CSR] = 0;
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 *win;
	पूर्णांक i;

	क्रम (i = 0; i < 15; i++)
		regs->u_regs[UREG_G1 + i] = gdb_regs[GDB_G1 + i];

	/* If the PSR रेजिस्टर is changing, we have to preserve
	 * the CWP field, otherwise winकरोw save/restore explodes.
	 */
	अगर (regs->psr != gdb_regs[GDB_PSR]) अणु
		अचिन्हित दीर्घ cwp = regs->psr & PSR_CWP;

		regs->psr = (gdb_regs[GDB_PSR] & ~PSR_CWP) | cwp;
	पूर्ण

	regs->pc = gdb_regs[GDB_PC];
	regs->npc = gdb_regs[GDB_NPC];
	regs->y = gdb_regs[GDB_Y];

	win = (काष्ठा reg_winकरोw32 *) regs->u_regs[UREG_FP];
	क्रम (i = 0; i < 8; i++)
		win->locals[i] = gdb_regs[GDB_L0 + i];
	क्रम (i = 0; i < 8; i++)
		win->ins[i] = gdb_regs[GDB_I0 + i];
पूर्ण

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
			linux_regs->pc = addr;
			linux_regs->npc = addr + 4;
		पूर्ण
		fallthrough;

	हाल 'D':
	हाल 'k':
		अगर (linux_regs->pc == (अचिन्हित दीर्घ) arch_kgdb_अवरोधpoपूर्णांक) अणु
			linux_regs->pc = linux_regs->npc;
			linux_regs->npc += 4;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

यंत्रlinkage व्योम kgdb_trap(अचिन्हित दीर्घ trap_level, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (user_mode(regs)) अणु
		करो_hw_पूर्णांकerrupt(regs, trap_level);
		वापस;
	पूर्ण

	flushw_all();

	local_irq_save(flags);
	kgdb_handle_exception(trap_level, SIGTRAP, 0, regs);
	local_irq_restore(flags);
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
	regs->pc = ip;
	regs->npc = regs->pc + 4;
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: ta 0x7d */
	.gdb_bpt_instr		= अणु 0x91, 0xd0, 0x20, 0x7d पूर्ण,
पूर्ण;
