<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/kernel/kgdb.c
 *
 * ARM KGDB support
 *
 * Copyright (c) 2002-2004 MontaVista Software, Inc
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * Authors:  George Davis <davis_g@mvista.com>
 *           Deepak Saxena <dsaxena@plनिकासy.net>
 */
#समावेश <linux/irq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/traps.h>

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] =
अणु
	अणु "r0", 4, दुरत्व(काष्ठा pt_regs, ARM_r0)पूर्ण,
	अणु "r1", 4, दुरत्व(काष्ठा pt_regs, ARM_r1)पूर्ण,
	अणु "r2", 4, दुरत्व(काष्ठा pt_regs, ARM_r2)पूर्ण,
	अणु "r3", 4, दुरत्व(काष्ठा pt_regs, ARM_r3)पूर्ण,
	अणु "r4", 4, दुरत्व(काष्ठा pt_regs, ARM_r4)पूर्ण,
	अणु "r5", 4, दुरत्व(काष्ठा pt_regs, ARM_r5)पूर्ण,
	अणु "r6", 4, दुरत्व(काष्ठा pt_regs, ARM_r6)पूर्ण,
	अणु "r7", 4, दुरत्व(काष्ठा pt_regs, ARM_r7)पूर्ण,
	अणु "r8", 4, दुरत्व(काष्ठा pt_regs, ARM_r8)पूर्ण,
	अणु "r9", 4, दुरत्व(काष्ठा pt_regs, ARM_r9)पूर्ण,
	अणु "r10", 4, दुरत्व(काष्ठा pt_regs, ARM_r10)पूर्ण,
	अणु "fp", 4, दुरत्व(काष्ठा pt_regs, ARM_fp)पूर्ण,
	अणु "ip", 4, दुरत्व(काष्ठा pt_regs, ARM_ip)पूर्ण,
	अणु "sp", 4, दुरत्व(काष्ठा pt_regs, ARM_sp)पूर्ण,
	अणु "lr", 4, दुरत्व(काष्ठा pt_regs, ARM_lr)पूर्ण,
	अणु "pc", 4, दुरत्व(काष्ठा pt_regs, ARM_pc)पूर्ण,
	अणु "f0", 12, -1 पूर्ण,
	अणु "f1", 12, -1 पूर्ण,
	अणु "f2", 12, -1 पूर्ण,
	अणु "f3", 12, -1 पूर्ण,
	अणु "f4", 12, -1 पूर्ण,
	अणु "f5", 12, -1 पूर्ण,
	अणु "f6", 12, -1 पूर्ण,
	अणु "f7", 12, -1 पूर्ण,
	अणु "fps", 4, -1 पूर्ण,
	अणु "cpsr", 4, दुरत्व(काष्ठा pt_regs, ARM_cpsr)पूर्ण,
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
	काष्ठा thपढ़ो_info *ti;
	पूर्णांक regno;

	/* Just making sure... */
	अगर (task == शून्य)
		वापस;

	/* Initialize to zero */
	क्रम (regno = 0; regno < GDB_MAX_REGS; regno++)
		gdb_regs[regno] = 0;

	/* Otherwise, we have only some रेजिस्टरs from चयन_to() */
	ti			= task_thपढ़ो_info(task);
	gdb_regs[_R4]		= ti->cpu_context.r4;
	gdb_regs[_R5]		= ti->cpu_context.r5;
	gdb_regs[_R6]		= ti->cpu_context.r6;
	gdb_regs[_R7]		= ti->cpu_context.r7;
	gdb_regs[_R8]		= ti->cpu_context.r8;
	gdb_regs[_R9]		= ti->cpu_context.r9;
	gdb_regs[_R10]		= ti->cpu_context.sl;
	gdb_regs[_FP]		= ti->cpu_context.fp;
	gdb_regs[_SPT]		= ti->cpu_context.sp;
	gdb_regs[_PC]		= ti->cpu_context.pc;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->ARM_pc = pc;
पूर्ण

अटल पूर्णांक compiled_अवरोध;

पूर्णांक kgdb_arch_handle_exception(पूर्णांक exception_vector, पूर्णांक signo,
			       पूर्णांक err_code, अक्षर *remcom_in_buffer,
			       अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	चयन (remcom_in_buffer[0]) अणु
	हाल 'D':
	हाल 'k':
	हाल 'c':
		/*
		 * Try to पढ़ो optional parameter, pc unchanged अगर no parm.
		 * If this was a compiled अवरोधpoपूर्णांक, we need to move
		 * to the next inकाष्ठाion or we will just अवरोधpoपूर्णांक
		 * over and over again.
		 */
		ptr = &remcom_in_buffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			linux_regs->ARM_pc = addr;
		अन्यथा अगर (compiled_अवरोध == 1)
			linux_regs->ARM_pc += 4;

		compiled_अवरोध = 0;

		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक kgdb_brk_fn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	kgdb_handle_exception(1, SIGTRAP, 0, regs);

	वापस 0;
पूर्ण

अटल पूर्णांक kgdb_compiled_brk_fn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	compiled_अवरोध = 1;
	kgdb_handle_exception(1, SIGTRAP, 0, regs);

	वापस 0;
पूर्ण

अटल काष्ठा undef_hook kgdb_brkpt_hook = अणु
	.instr_mask		= 0xffffffff,
	.instr_val		= KGDB_BREAKINST,
	.cpsr_mask		= MODE_MASK,
	.cpsr_val		= SVC_MODE,
	.fn			= kgdb_brk_fn
पूर्ण;

अटल काष्ठा undef_hook kgdb_compiled_brkpt_hook = अणु
	.instr_mask		= 0xffffffff,
	.instr_val		= KGDB_COMPILED_BREAK,
	.cpsr_mask		= MODE_MASK,
	.cpsr_val		= SVC_MODE,
	.fn			= kgdb_compiled_brk_fn
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
	.priority	= -पूर्णांक_उच्च,
पूर्ण;


/**
 *	kgdb_arch_init - Perक्रमm any architecture specअगरic initalization.
 *
 *	This function will handle the initalization of any architecture
 *	specअगरic callbacks.
 */
पूर्णांक kgdb_arch_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_die_notअगरier(&kgdb_notअगरier);

	अगर (ret != 0)
		वापस ret;

	रेजिस्टर_undef_hook(&kgdb_brkpt_hook);
	रेजिस्टर_undef_hook(&kgdb_compiled_brkpt_hook);

	वापस 0;
पूर्ण

/**
 *	kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 *
 *	This function will handle the uninitalization of any architecture
 *	specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_undef_hook(&kgdb_brkpt_hook);
	unरेजिस्टर_undef_hook(&kgdb_compiled_brkpt_hook);
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;

	/* patch_text() only supports पूर्णांक-sized अवरोधpoपूर्णांकs */
	BUILD_BUG_ON(माप(पूर्णांक) != BREAK_INSTR_SIZE);

	err = copy_from_kernel_nofault(bpt->saved_instr, (अक्षर *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	अगर (err)
		वापस err;

	/* Machine is alपढ़ोy stopped, so we can use __patch_text() directly */
	__patch_text((व्योम *)bpt->bpt_addr,
		     *(अचिन्हित पूर्णांक *)arch_kgdb_ops.gdb_bpt_instr);

	वापस err;
पूर्ण

पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	/* Machine is alपढ़ोy stopped, so we can use __patch_text() directly */
	__patch_text((व्योम *)bpt->bpt_addr, *(अचिन्हित पूर्णांक *)bpt->saved_instr);

	वापस 0;
पूर्ण

/*
 * Register our undef inकाष्ठाion hooks with ARM undef core.
 * We रेजिस्टर a hook specअगरically looking क्रम the KGB अवरोध inst
 * and we handle the normal undef हाल within the करो_undefinstr
 * handler.
 */
स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
#अगर_अघोषित __ARMEB__
	.gdb_bpt_instr		= अणु0xfe, 0xde, 0xff, 0xe7पूर्ण
#अन्यथा /* ! __ARMEB__ */
	.gdb_bpt_instr		= अणु0xe7, 0xff, 0xde, 0xfeपूर्ण
#पूर्ण_अगर
पूर्ण;
