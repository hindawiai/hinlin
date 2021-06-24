<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AArch64 KGDB support
 *
 * Based on arch/arm/kernel/kgdb.c
 *
 * Copyright (C) 2013 Cavium Inc.
 * Author: Vijaya Kumar K <vijaya.kumar@caviumnetworks.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/irq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/traps.h>

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] = अणु
	अणु "x0", 8, दुरत्व(काष्ठा pt_regs, regs[0])पूर्ण,
	अणु "x1", 8, दुरत्व(काष्ठा pt_regs, regs[1])पूर्ण,
	अणु "x2", 8, दुरत्व(काष्ठा pt_regs, regs[2])पूर्ण,
	अणु "x3", 8, दुरत्व(काष्ठा pt_regs, regs[3])पूर्ण,
	अणु "x4", 8, दुरत्व(काष्ठा pt_regs, regs[4])पूर्ण,
	अणु "x5", 8, दुरत्व(काष्ठा pt_regs, regs[5])पूर्ण,
	अणु "x6", 8, दुरत्व(काष्ठा pt_regs, regs[6])पूर्ण,
	अणु "x7", 8, दुरत्व(काष्ठा pt_regs, regs[7])पूर्ण,
	अणु "x8", 8, दुरत्व(काष्ठा pt_regs, regs[8])पूर्ण,
	अणु "x9", 8, दुरत्व(काष्ठा pt_regs, regs[9])पूर्ण,
	अणु "x10", 8, दुरत्व(काष्ठा pt_regs, regs[10])पूर्ण,
	अणु "x11", 8, दुरत्व(काष्ठा pt_regs, regs[11])पूर्ण,
	अणु "x12", 8, दुरत्व(काष्ठा pt_regs, regs[12])पूर्ण,
	अणु "x13", 8, दुरत्व(काष्ठा pt_regs, regs[13])पूर्ण,
	अणु "x14", 8, दुरत्व(काष्ठा pt_regs, regs[14])पूर्ण,
	अणु "x15", 8, दुरत्व(काष्ठा pt_regs, regs[15])पूर्ण,
	अणु "x16", 8, दुरत्व(काष्ठा pt_regs, regs[16])पूर्ण,
	अणु "x17", 8, दुरत्व(काष्ठा pt_regs, regs[17])पूर्ण,
	अणु "x18", 8, दुरत्व(काष्ठा pt_regs, regs[18])पूर्ण,
	अणु "x19", 8, दुरत्व(काष्ठा pt_regs, regs[19])पूर्ण,
	अणु "x20", 8, दुरत्व(काष्ठा pt_regs, regs[20])पूर्ण,
	अणु "x21", 8, दुरत्व(काष्ठा pt_regs, regs[21])पूर्ण,
	अणु "x22", 8, दुरत्व(काष्ठा pt_regs, regs[22])पूर्ण,
	अणु "x23", 8, दुरत्व(काष्ठा pt_regs, regs[23])पूर्ण,
	अणु "x24", 8, दुरत्व(काष्ठा pt_regs, regs[24])पूर्ण,
	अणु "x25", 8, दुरत्व(काष्ठा pt_regs, regs[25])पूर्ण,
	अणु "x26", 8, दुरत्व(काष्ठा pt_regs, regs[26])पूर्ण,
	अणु "x27", 8, दुरत्व(काष्ठा pt_regs, regs[27])पूर्ण,
	अणु "x28", 8, दुरत्व(काष्ठा pt_regs, regs[28])पूर्ण,
	अणु "x29", 8, दुरत्व(काष्ठा pt_regs, regs[29])पूर्ण,
	अणु "x30", 8, दुरत्व(काष्ठा pt_regs, regs[30])पूर्ण,
	अणु "sp", 8, दुरत्व(काष्ठा pt_regs, sp)पूर्ण,
	अणु "pc", 8, दुरत्व(काष्ठा pt_regs, pc)पूर्ण,
	/*
	 * काष्ठा pt_regs thinks PSTATE is 64-bits wide but gdb remote
	 * protocol disagrees. Thereक्रमe we must extract only the lower
	 * 32-bits. Look क्रम the big comment in यंत्र/kgdb.h क्रम more
	 * detail.
	 */
	अणु "pstate", 4, दुरत्व(काष्ठा pt_regs, pstate)
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
							+ 4
#पूर्ण_अगर
	पूर्ण,
	अणु "v0", 16, -1 पूर्ण,
	अणु "v1", 16, -1 पूर्ण,
	अणु "v2", 16, -1 पूर्ण,
	अणु "v3", 16, -1 पूर्ण,
	अणु "v4", 16, -1 पूर्ण,
	अणु "v5", 16, -1 पूर्ण,
	अणु "v6", 16, -1 पूर्ण,
	अणु "v7", 16, -1 पूर्ण,
	अणु "v8", 16, -1 पूर्ण,
	अणु "v9", 16, -1 पूर्ण,
	अणु "v10", 16, -1 पूर्ण,
	अणु "v11", 16, -1 पूर्ण,
	अणु "v12", 16, -1 पूर्ण,
	अणु "v13", 16, -1 पूर्ण,
	अणु "v14", 16, -1 पूर्ण,
	अणु "v15", 16, -1 पूर्ण,
	अणु "v16", 16, -1 पूर्ण,
	अणु "v17", 16, -1 पूर्ण,
	अणु "v18", 16, -1 पूर्ण,
	अणु "v19", 16, -1 पूर्ण,
	अणु "v20", 16, -1 पूर्ण,
	अणु "v21", 16, -1 पूर्ण,
	अणु "v22", 16, -1 पूर्ण,
	अणु "v23", 16, -1 पूर्ण,
	अणु "v24", 16, -1 पूर्ण,
	अणु "v25", 16, -1 पूर्ण,
	अणु "v26", 16, -1 पूर्ण,
	अणु "v27", 16, -1 पूर्ण,
	अणु "v28", 16, -1 पूर्ण,
	अणु "v29", 16, -1 पूर्ण,
	अणु "v30", 16, -1 पूर्ण,
	अणु "v31", 16, -1 पूर्ण,
	अणु "fpsr", 4, -1 पूर्ण,
	अणु "fpcr", 4, -1 पूर्ण,
पूर्ण;

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);
	अन्यथा
		स_रखो(mem, 0, dbg_reg_def[regno].size);
	वापस dbg_reg_def[regno].name;
पूर्ण

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस -EINVAL;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	वापस 0;
पूर्ण

व्योम
sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cpu_context *cpu_context = &task->thपढ़ो.cpu_context;

	/* Initialize to zero */
	स_रखो((अक्षर *)gdb_regs, 0, NUMREGBYTES);

	gdb_regs[19] = cpu_context->x19;
	gdb_regs[20] = cpu_context->x20;
	gdb_regs[21] = cpu_context->x21;
	gdb_regs[22] = cpu_context->x22;
	gdb_regs[23] = cpu_context->x23;
	gdb_regs[24] = cpu_context->x24;
	gdb_regs[25] = cpu_context->x25;
	gdb_regs[26] = cpu_context->x26;
	gdb_regs[27] = cpu_context->x27;
	gdb_regs[28] = cpu_context->x28;
	gdb_regs[29] = cpu_context->fp;

	gdb_regs[31] = cpu_context->sp;
	gdb_regs[32] = cpu_context->pc;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->pc = pc;
पूर्ण

अटल पूर्णांक compiled_अवरोध;

अटल व्योम kgdb_arch_update_addr(काष्ठा pt_regs *regs,
				अक्षर *remcom_in_buffer)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	ptr = &remcom_in_buffer[1];
	अगर (kgdb_hex2दीर्घ(&ptr, &addr))
		kgdb_arch_set_pc(regs, addr);
	अन्यथा अगर (compiled_अवरोध == 1)
		kgdb_arch_set_pc(regs, regs->pc + 4);

	compiled_अवरोध = 0;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक exception_vector, पूर्णांक signo,
			       पूर्णांक err_code, अक्षर *remcom_in_buffer,
			       अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	पूर्णांक err;

	चयन (remcom_in_buffer[0]) अणु
	हाल 'D':
	हाल 'k':
		/*
		 * Packet D (Detach), k (समाप्त). No special handling
		 * is required here. Handle same as c packet.
		 */
	हाल 'c':
		/*
		 * Packet c (Continue) to जारी executing.
		 * Set pc to required address.
		 * Try to पढ़ो optional parameter and set pc.
		 * If this was a compiled अवरोधpoपूर्णांक, we need to move
		 * to the next inकाष्ठाion अन्यथा we will just अवरोधpoपूर्णांक
		 * over and over again.
		 */
		kgdb_arch_update_addr(linux_regs, remcom_in_buffer);
		atomic_set(&kgdb_cpu_करोing_single_step, -1);
		kgdb_single_step =  0;

		/*
		 * Received जारी command, disable single step
		 */
		अगर (kernel_active_single_step())
			kernel_disable_single_step();

		err = 0;
		अवरोध;
	हाल 's':
		/*
		 * Update step address value with address passed
		 * with step packet.
		 * On debug exception वापस PC is copied to ELR
		 * So just update PC.
		 * If no step address is passed, resume from the address
		 * poपूर्णांकed by PC. Do not update PC
		 */
		kgdb_arch_update_addr(linux_regs, remcom_in_buffer);
		atomic_set(&kgdb_cpu_करोing_single_step, raw_smp_processor_id());
		kgdb_single_step =  1;

		/*
		 * Enable single step handling
		 */
		अगर (!kernel_active_single_step())
			kernel_enable_single_step(linux_regs);
		err = 0;
		अवरोध;
	शेष:
		err = -1;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक kgdb_brk_fn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	kgdb_handle_exception(1, SIGTRAP, 0, regs);
	वापस DBG_HOOK_HANDLED;
पूर्ण
NOKPROBE_SYMBOL(kgdb_brk_fn)

अटल पूर्णांक kgdb_compiled_brk_fn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	compiled_अवरोध = 1;
	kgdb_handle_exception(1, SIGTRAP, 0, regs);

	वापस DBG_HOOK_HANDLED;
पूर्ण
NOKPROBE_SYMBOL(kgdb_compiled_brk_fn);

अटल पूर्णांक kgdb_step_brk_fn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	अगर (!kgdb_single_step)
		वापस DBG_HOOK_ERROR;

	kgdb_handle_exception(0, SIGTRAP, 0, regs);
	वापस DBG_HOOK_HANDLED;
पूर्ण
NOKPROBE_SYMBOL(kgdb_step_brk_fn);

अटल काष्ठा अवरोध_hook kgdb_brkpt_hook = अणु
	.fn		= kgdb_brk_fn,
	.imm		= KGDB_DYN_DBG_BRK_IMM,
पूर्ण;

अटल काष्ठा अवरोध_hook kgdb_compiled_brkpt_hook = अणु
	.fn		= kgdb_compiled_brk_fn,
	.imm		= KGDB_COMPILED_DBG_BRK_IMM,
पूर्ण;

अटल काष्ठा step_hook kgdb_step_hook = अणु
	.fn		= kgdb_step_brk_fn
पूर्ण;

अटल पूर्णांक __kgdb_notअगरy(काष्ठा die_args *args, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा pt_regs *regs = args->regs;

	अगर (kgdb_handle_exception(1, args->signr, cmd, regs))
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
	.notअगरier_call	= kgdb_notअगरy,
	/*
	 * Want to be lowest priority
	 */
	.priority	= -पूर्णांक_उच्च,
पूर्ण;

/*
 * kgdb_arch_init - Perक्रमm any architecture specअगरic initialization.
 * This function will handle the initialization of any architecture
 * specअगरic callbacks.
 */
पूर्णांक kgdb_arch_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_die_notअगरier(&kgdb_notअगरier);

	अगर (ret != 0)
		वापस ret;

	रेजिस्टर_kernel_अवरोध_hook(&kgdb_brkpt_hook);
	रेजिस्टर_kernel_अवरोध_hook(&kgdb_compiled_brkpt_hook);
	रेजिस्टर_kernel_step_hook(&kgdb_step_hook);
	वापस 0;
पूर्ण

/*
 * kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 * This function will handle the uninitalization of any architecture
 * specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_kernel_अवरोध_hook(&kgdb_brkpt_hook);
	unरेजिस्टर_kernel_अवरोध_hook(&kgdb_compiled_brkpt_hook);
	unरेजिस्टर_kernel_step_hook(&kgdb_step_hook);
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops;

पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(AARCH64_INSN_SIZE != BREAK_INSTR_SIZE);

	err = aarch64_insn_पढ़ो((व्योम *)bpt->bpt_addr, (u32 *)bpt->saved_instr);
	अगर (err)
		वापस err;

	वापस aarch64_insn_ग_लिखो((व्योम *)bpt->bpt_addr,
			(u32)AARCH64_BREAK_KGDB_DYN_DBG);
पूर्ण

पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	वापस aarch64_insn_ग_लिखो((व्योम *)bpt->bpt_addr,
			*(u32 *)bpt->saved_instr);
पूर्ण
