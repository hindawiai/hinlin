<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kgdb support क्रम ARC
 *
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <यंत्र/disयंत्र.h>
#समावेश <यंत्र/cacheflush.h>

अटल व्योम to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *kernel_regs,
			काष्ठा callee_regs *cregs)
अणु
	पूर्णांक regno;

	क्रम (regno = 0; regno <= 26; regno++)
		gdb_regs[_R0 + regno] = get_reg(regno, kernel_regs, cregs);

	क्रम (regno = 27; regno < GDB_MAX_REGS; regno++)
		gdb_regs[regno] = 0;

	gdb_regs[_FP]		= kernel_regs->fp;
	gdb_regs[__SP]		= kernel_regs->sp;
	gdb_regs[_BLINK]	= kernel_regs->blink;
	gdb_regs[_RET]		= kernel_regs->ret;
	gdb_regs[_STATUS32]	= kernel_regs->status32;
	gdb_regs[_LP_COUNT]	= kernel_regs->lp_count;
	gdb_regs[_LP_END]	= kernel_regs->lp_end;
	gdb_regs[_LP_START]	= kernel_regs->lp_start;
	gdb_regs[_BTA]		= kernel_regs->bta;
	gdb_regs[_STOP_PC]	= kernel_regs->ret;
पूर्ण

अटल व्योम from_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *kernel_regs,
			काष्ठा callee_regs *cregs)
अणु
	पूर्णांक regno;

	क्रम (regno = 0; regno <= 26; regno++)
		set_reg(regno, gdb_regs[regno + _R0], kernel_regs, cregs);

	kernel_regs->fp		= gdb_regs[_FP];
	kernel_regs->sp		= gdb_regs[__SP];
	kernel_regs->blink	= gdb_regs[_BLINK];
	kernel_regs->ret	= gdb_regs[_RET];
	kernel_regs->status32	= gdb_regs[_STATUS32];
	kernel_regs->lp_count	= gdb_regs[_LP_COUNT];
	kernel_regs->lp_end	= gdb_regs[_LP_END];
	kernel_regs->lp_start	= gdb_regs[_LP_START];
	kernel_regs->bta	= gdb_regs[_BTA];
पूर्ण


व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *kernel_regs)
अणु
	to_gdb_regs(gdb_regs, kernel_regs, (काष्ठा callee_regs *)
		current->thपढ़ो.callee_reg);
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *kernel_regs)
अणु
	from_gdb_regs(gdb_regs, kernel_regs, (काष्ठा callee_regs *)
		current->thपढ़ो.callee_reg);
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs,
				 काष्ठा task_काष्ठा *task)
अणु
	अगर (task)
		to_gdb_regs(gdb_regs, task_pt_regs(task),
			(काष्ठा callee_regs *) task->thपढ़ो.callee_reg);
पूर्ण

काष्ठा single_step_data_t अणु
	uपूर्णांक16_t opcode[2];
	अचिन्हित दीर्घ address[2];
	पूर्णांक is_branch;
	पूर्णांक armed;
पूर्ण single_step_data;

अटल व्योम unकरो_single_step(काष्ठा pt_regs *regs)
अणु
	अगर (single_step_data.armed) अणु
		पूर्णांक i;

		क्रम (i = 0; i < (single_step_data.is_branch ? 2 : 1); i++) अणु
			स_नकल((व्योम *) single_step_data.address[i],
				&single_step_data.opcode[i],
				BREAK_INSTR_SIZE);

			flush_icache_range(single_step_data.address[i],
				single_step_data.address[i] +
				BREAK_INSTR_SIZE);
		पूर्ण
		single_step_data.armed = 0;
	पूर्ण
पूर्ण

अटल व्योम place_trap(अचिन्हित दीर्घ address, व्योम *save)
अणु
	स_नकल(save, (व्योम *) address, BREAK_INSTR_SIZE);
	स_नकल((व्योम *) address, &arch_kgdb_ops.gdb_bpt_instr,
		BREAK_INSTR_SIZE);
	flush_icache_range(address, address + BREAK_INSTR_SIZE);
पूर्ण

अटल व्योम करो_single_step(काष्ठा pt_regs *regs)
अणु
	single_step_data.is_branch = disयंत्र_next_pc((अचिन्हित दीर्घ)
		regs->ret, regs, (काष्ठा callee_regs *)
		current->thपढ़ो.callee_reg,
		&single_step_data.address[0],
		&single_step_data.address[1]);

	place_trap(single_step_data.address[0], &single_step_data.opcode[0]);

	अगर (single_step_data.is_branch) अणु
		place_trap(single_step_data.address[1],
			&single_step_data.opcode[1]);
	पूर्ण

	single_step_data.armed++;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक e_vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcomInBuffer, अक्षर *remcomOutBuffer,
			       काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	unकरो_single_step(regs);

	चयन (remcomInBuffer[0]) अणु
	हाल 's':
	हाल 'c':
		ptr = &remcomInBuffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			regs->ret = addr;
		fallthrough;

	हाल 'D':
	हाल 'k':
		atomic_set(&kgdb_cpu_करोing_single_step, -1);

		अगर (remcomInBuffer[0] == 's') अणु
			करो_single_step(regs);
			atomic_set(&kgdb_cpu_करोing_single_step,
				   smp_processor_id());
		पूर्ण

		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक kgdb_arch_init(व्योम)
अणु
	single_step_data.armed = 0;
	वापस 0;
पूर्ण

व्योम kgdb_trap(काष्ठा pt_regs *regs)
अणु
	/* trap_s 3 is used क्रम अवरोधpoपूर्णांकs that overग_लिखो existing
	 * inकाष्ठाions, जबतक trap_s 4 is used क्रम compiled अवरोधpoपूर्णांकs.
	 *
	 * with trap_s 3 अवरोधpoपूर्णांकs the original inकाष्ठाion needs to be
	 * restored and continuation needs to start at the location of the
	 * अवरोधpoपूर्णांक.
	 *
	 * with trap_s 4 (compiled) अवरोधpoपूर्णांकs, continuation needs to
	 * start after the अवरोधpoपूर्णांक.
	 */
	अगर (regs->ecr_param == 3)
		inकाष्ठाion_poपूर्णांकer(regs) -= BREAK_INSTR_SIZE;

	kgdb_handle_exception(1, SIGTRAP, 0, regs);
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	inकाष्ठाion_poपूर्णांकer(regs) = ip;
पूर्ण

व्योम kgdb_call_nmi_hook(व्योम *ignored)
अणु
	/* Default implementation passes get_irq_regs() but we करोn't */
	kgdb_nmicallback(raw_smp_processor_id(), शून्य);
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* अवरोधpoपूर्णांक inकाष्ठाion: TRAP_S 0x3 */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	.gdb_bpt_instr		= अणु0x78, 0x7eपूर्ण,
#अन्यथा
	.gdb_bpt_instr		= अणु0x7e, 0x78पूर्ण,
#पूर्ण_अगर
पूर्ण;
