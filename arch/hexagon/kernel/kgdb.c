<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/hexagon/kernel/kgdb.c - Hexagon KGDB Support
 *
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/irq.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kgdb.h>

/* All रेजिस्टरs are 4 bytes, क्रम now */
#घोषणा GDB_SIZखातापूर्ण_REG 4

/* The रेजिस्टर names are used during prपूर्णांकing of the regs;
 * Keep these at three letters to pretty-prपूर्णांक. */
काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] = अणु
	अणु " r0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r00)पूर्ण,
	अणु " r1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r01)पूर्ण,
	अणु " r2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r02)पूर्ण,
	अणु " r3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r03)पूर्ण,
	अणु " r4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r04)पूर्ण,
	अणु " r5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r05)पूर्ण,
	अणु " r6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r06)पूर्ण,
	अणु " r7", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r07)पूर्ण,
	अणु " r8", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r08)पूर्ण,
	अणु " r9", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r09)पूर्ण,
	अणु "r10", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r10)पूर्ण,
	अणु "r11", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r11)पूर्ण,
	अणु "r12", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r12)पूर्ण,
	अणु "r13", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r13)पूर्ण,
	अणु "r14", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r14)पूर्ण,
	अणु "r15", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r15)पूर्ण,
	अणु "r16", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r16)पूर्ण,
	अणु "r17", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r17)पूर्ण,
	अणु "r18", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r18)पूर्ण,
	अणु "r19", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r19)पूर्ण,
	अणु "r20", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r20)पूर्ण,
	अणु "r21", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r21)पूर्ण,
	अणु "r22", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r22)पूर्ण,
	अणु "r23", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r23)पूर्ण,
	अणु "r24", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r24)पूर्ण,
	अणु "r25", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r25)पूर्ण,
	अणु "r26", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r26)पूर्ण,
	अणु "r27", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r27)पूर्ण,
	अणु "r28", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r28)पूर्ण,
	अणु "r29", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r29)पूर्ण,
	अणु "r30", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r30)पूर्ण,
	अणु "r31", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r31)पूर्ण,

	अणु "usr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, usr)पूर्ण,
	अणु "preds", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, preds)पूर्ण,
	अणु " m0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, m0)पूर्ण,
	अणु " m1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, m1)पूर्ण,
	अणु "sa0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sa0)पूर्ण,
	अणु "sa1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sa1)पूर्ण,
	अणु "lc0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, lc0)पूर्ण,
	अणु "lc1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, lc1)पूर्ण,
	अणु " gp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gp)पूर्ण,
	अणु "ugp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, ugp)पूर्ण,
	अणु "cs0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cs0)पूर्ण,
	अणु "cs1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cs1)पूर्ण,
	अणु "psp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, hvmer.vmpsp)पूर्ण,
	अणु "elr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, hvmer.vmel)पूर्ण,
	अणु "est", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, hvmer.vmest)पूर्ण,
	अणु "badva", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, hvmer.vmbadva)पूर्ण,
	अणु "restart_r0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, restart_r0)पूर्ण,
	अणु "syscall_nr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, syscall_nr)पूर्ण,
पूर्ण;

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* trap0(#0xDB) 0x0cdb0054 */
	.gdb_bpt_instr = अणु0x54, 0x00, 0xdb, 0x0cपूर्ण,
पूर्ण;

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	*((अचिन्हित दीर्घ *) mem) = *((अचिन्हित दीर्घ *) ((व्योम *)regs +
		dbg_reg_def[regno].offset));

	वापस dbg_reg_def[regno].name;
पूर्ण

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस -EINVAL;

	*((अचिन्हित दीर्घ *) ((व्योम *)regs + dbg_reg_def[regno].offset)) =
		*((अचिन्हित दीर्घ *) mem);

	वापस 0;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	inकाष्ठाion_poपूर्णांकer(regs) = pc;
पूर्ण


/*  Not yet working  */
व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs,
				 काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *thपढ़ो_regs;

	अगर (task == शून्य)
		वापस;

	/* Initialize to zero */
	स_रखो(gdb_regs, 0, NUMREGBYTES);

	/* Otherwise, we have only some रेजिस्टरs from चयन_to() */
	thपढ़ो_regs = task_pt_regs(task);
	gdb_regs[0] = thपढ़ो_regs->r00;
पूर्ण

/**
 * kgdb_arch_handle_exception - Handle architecture specअगरic GDB packets.
 * @vector: The error vector of the exception that happened.
 * @signo: The संकेत number of the exception that happened.
 * @err_code: The error code of the exception that happened.
 * @remcom_in_buffer: The buffer of the packet we have पढ़ो.
 * @remcom_out_buffer: The buffer of %BUFMAX bytes to ग_लिखो a packet पूर्णांकo.
 * @regs: The &काष्ठा pt_regs of the current process.
 *
 * This function MUST handle the 'c' and 's' command packets,
 * as well packets to set / हटाओ a hardware अवरोधpoपूर्णांक, अगर used.
 * If there are additional packets which the hardware needs to handle,
 * they are handled here.  The code should वापस -1 अगर it wants to
 * process more packets, and a %0 or %1 अगर it wants to निकास from the
 * kgdb callback.
 *
 * Not yet working.
 */
पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	चयन (remcom_in_buffer[0]) अणु
	हाल 's':
	हाल 'c':
		वापस 0;
	पूर्ण
	/* Stay in the debugger. */
	वापस -1;
पूर्ण

अटल पूर्णांक __kgdb_notअगरy(काष्ठा die_args *args, अचिन्हित दीर्घ cmd)
अणु
	/* cpu roundup */
	अगर (atomic_पढ़ो(&kgdb_active) != -1) अणु
		kgdb_nmicallback(smp_processor_id(), args->regs);
		वापस NOTIFY_STOP;
	पूर्ण

	अगर (user_mode(args->regs))
		वापस NOTIFY_DONE;

	अगर (kgdb_handle_exception(args->trapnr & 0xff, args->signr, args->err,
				    args->regs))
		वापस NOTIFY_DONE;

	वापस NOTIFY_STOP;
पूर्ण

अटल पूर्णांक
kgdb_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	local_irq_save(flags);
	ret = __kgdb_notअगरy(ptr, cmd);
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block kgdb_notअगरier = अणु
	.notअगरier_call = kgdb_notअगरy,

	/*
	 * Lowest-prio notअगरier priority, we want to be notअगरied last:
	 */
	.priority = -पूर्णांक_उच्च,
पूर्ण;

/**
 * kgdb_arch_init - Perक्रमm any architecture specअगरic initialization.
 *
 * This function will handle the initialization of any architecture
 * specअगरic callbacks.
 */
पूर्णांक kgdb_arch_init(व्योम)
अणु
	वापस रेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

/**
 * kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 *
 * This function will handle the uninitalization of any architecture
 * specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण
