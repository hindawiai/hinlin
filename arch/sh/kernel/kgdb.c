<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH KGDB support
 *
 * Copyright (C) 2008 - 2012  Paul Mundt
 *
 * Single stepping taken from the old stub by Henry Bell and Jeremy Siegel.
 */
#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>

/* Macros क्रम single step inकाष्ठाion identअगरication */
#घोषणा OPCODE_BT(op)		(((op) & 0xff00) == 0x8900)
#घोषणा OPCODE_BF(op)		(((op) & 0xff00) == 0x8b00)
#घोषणा OPCODE_BTF_DISP(op)	(((op) & 0x80) ? (((op) | 0xffffff80) << 1) : \
				 (((op) & 0x7f ) << 1))
#घोषणा OPCODE_BFS(op)		(((op) & 0xff00) == 0x8f00)
#घोषणा OPCODE_BTS(op)		(((op) & 0xff00) == 0x8d00)
#घोषणा OPCODE_BRA(op)		(((op) & 0xf000) == 0xa000)
#घोषणा OPCODE_BRA_DISP(op)	(((op) & 0x800) ? (((op) | 0xfffff800) << 1) : \
				 (((op) & 0x7ff) << 1))
#घोषणा OPCODE_BRAF(op)		(((op) & 0xf0ff) == 0x0023)
#घोषणा OPCODE_BRAF_REG(op)	(((op) & 0x0f00) >> 8)
#घोषणा OPCODE_BSR(op)		(((op) & 0xf000) == 0xb000)
#घोषणा OPCODE_BSR_DISP(op)	(((op) & 0x800) ? (((op) | 0xfffff800) << 1) : \
				 (((op) & 0x7ff) << 1))
#घोषणा OPCODE_BSRF(op)		(((op) & 0xf0ff) == 0x0003)
#घोषणा OPCODE_BSRF_REG(op)	(((op) >> 8) & 0xf)
#घोषणा OPCODE_JMP(op)		(((op) & 0xf0ff) == 0x402b)
#घोषणा OPCODE_JMP_REG(op)	(((op) >> 8) & 0xf)
#घोषणा OPCODE_JSR(op)		(((op) & 0xf0ff) == 0x400b)
#घोषणा OPCODE_JSR_REG(op)	(((op) >> 8) & 0xf)
#घोषणा OPCODE_RTS(op)		((op) == 0xb)
#घोषणा OPCODE_RTE(op)		((op) == 0x2b)

#घोषणा SR_T_BIT_MASK           0x1
#घोषणा STEP_OPCODE             0xc33d

/* Calculate the new address क्रम after a step */
अटल लघु *get_step_address(काष्ठा pt_regs *linux_regs)
अणु
	insn_माप_प्रकार op = __raw_पढ़ोw(linux_regs->pc);
	दीर्घ addr;

	/* BT */
	अगर (OPCODE_BT(op)) अणु
		अगर (linux_regs->sr & SR_T_BIT_MASK)
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		अन्यथा
			addr = linux_regs->pc + 2;
	पूर्ण

	/* BTS */
	अन्यथा अगर (OPCODE_BTS(op)) अणु
		अगर (linux_regs->sr & SR_T_BIT_MASK)
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		अन्यथा
			addr = linux_regs->pc + 4;	/* Not in delay slot */
	पूर्ण

	/* BF */
	अन्यथा अगर (OPCODE_BF(op)) अणु
		अगर (!(linux_regs->sr & SR_T_BIT_MASK))
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		अन्यथा
			addr = linux_regs->pc + 2;
	पूर्ण

	/* BFS */
	अन्यथा अगर (OPCODE_BFS(op)) अणु
		अगर (!(linux_regs->sr & SR_T_BIT_MASK))
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		अन्यथा
			addr = linux_regs->pc + 4;	/* Not in delay slot */
	पूर्ण

	/* BRA */
	अन्यथा अगर (OPCODE_BRA(op))
		addr = linux_regs->pc + 4 + OPCODE_BRA_DISP(op);

	/* BRAF */
	अन्यथा अगर (OPCODE_BRAF(op))
		addr = linux_regs->pc + 4
		    + linux_regs->regs[OPCODE_BRAF_REG(op)];

	/* BSR */
	अन्यथा अगर (OPCODE_BSR(op))
		addr = linux_regs->pc + 4 + OPCODE_BSR_DISP(op);

	/* BSRF */
	अन्यथा अगर (OPCODE_BSRF(op))
		addr = linux_regs->pc + 4
		    + linux_regs->regs[OPCODE_BSRF_REG(op)];

	/* JMP */
	अन्यथा अगर (OPCODE_JMP(op))
		addr = linux_regs->regs[OPCODE_JMP_REG(op)];

	/* JSR */
	अन्यथा अगर (OPCODE_JSR(op))
		addr = linux_regs->regs[OPCODE_JSR_REG(op)];

	/* RTS */
	अन्यथा अगर (OPCODE_RTS(op))
		addr = linux_regs->pr;

	/* RTE */
	अन्यथा अगर (OPCODE_RTE(op))
		addr = linux_regs->regs[15];

	/* Other */
	अन्यथा
		addr = linux_regs->pc + inकाष्ठाion_size(op);

	flush_icache_range(addr, addr + inकाष्ठाion_size(op));
	वापस (लघु *)addr;
पूर्ण

/*
 * Replace the inकाष्ठाion immediately after the current inकाष्ठाion
 * (i.e. next in the expected flow of control) with a trap inकाष्ठाion,
 * so that वापसing will cause only a single inकाष्ठाion to be executed.
 * Note that this model is slightly broken क्रम inकाष्ठाions with delay
 * slots (e.g. B[TF]S, BSR, BRA etc), where both the branch and the
 * inकाष्ठाion in the delay slot will be executed.
 */

अटल अचिन्हित दीर्घ stepped_address;
अटल insn_माप_प्रकार stepped_opcode;

अटल व्योम करो_single_step(काष्ठा pt_regs *linux_regs)
अणु
	/* Determine where the target inकाष्ठाion will send us to */
	अचिन्हित लघु *addr = get_step_address(linux_regs);

	stepped_address = (पूर्णांक)addr;

	/* Replace it */
	stepped_opcode = __raw_पढ़ोw((दीर्घ)addr);
	*addr = STEP_OPCODE;

	/* Flush and वापस */
	flush_icache_range((दीर्घ)addr, (दीर्घ)addr +
			   inकाष्ठाion_size(stepped_opcode));
पूर्ण

/* Unकरो a single step */
अटल व्योम unकरो_single_step(काष्ठा pt_regs *linux_regs)
अणु
	/* If we have stepped, put back the old inकाष्ठाion */
	/* Use stepped_address in हाल we stopped अन्यथाwhere */
	अगर (stepped_opcode != 0) अणु
		__raw_ग_लिखोw(stepped_opcode, stepped_address);
		flush_icache_range(stepped_address, stepped_address + 2);
	पूर्ण

	stepped_opcode = 0;
पूर्ण

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] = अणु
	अणु "r0",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[0]) पूर्ण,
	अणु "r1",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[1]) पूर्ण,
	अणु "r2",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[2]) पूर्ण,
	अणु "r3",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[3]) पूर्ण,
	अणु "r4",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[4]) पूर्ण,
	अणु "r5",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[5]) पूर्ण,
	अणु "r6",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[6]) पूर्ण,
	अणु "r7",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[7]) पूर्ण,
	अणु "r8",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[8]) पूर्ण,
	अणु "r9",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[9]) पूर्ण,
	अणु "r10",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[10]) पूर्ण,
	अणु "r11",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[11]) पूर्ण,
	अणु "r12",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[12]) पूर्ण,
	अणु "r13",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[13]) पूर्ण,
	अणु "r14",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[14]) पूर्ण,
	अणु "r15",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[15]) पूर्ण,
	अणु "pc",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, pc) पूर्ण,
	अणु "pr",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, pr) पूर्ण,
	अणु "sr",		GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sr) पूर्ण,
	अणु "gbr",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gbr) पूर्ण,
	अणु "mach",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, mach) पूर्ण,
	अणु "macl",	GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, macl) पूर्ण,
	अणु "vbr",	GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
पूर्ण;

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno < 0 || regno >= DBG_MAX_REG_NUM)
		वापस -EINVAL;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);

	वापस 0;
पूर्ण

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (dbg_reg_def[regno].size != -1)
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);

	चयन (regno) अणु
	हाल GDB_VBR:
		__यंत्र__ __अस्थिर__ ("stc vbr, %0" : "=r" (mem));
		अवरोध;
	पूर्ण

	वापस dbg_reg_def[regno].name;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा pt_regs *thपढ़ो_regs = task_pt_regs(p);
	पूर्णांक reg;

	/* Initialize to zero */
	क्रम (reg = 0; reg < DBG_MAX_REG_NUM; reg++)
		gdb_regs[reg] = 0;

	/*
	 * Copy out GP regs 8 to 14.
	 *
	 * चयन_to() relies on SR.RB toggling, so regs 0->7 are banked
	 * and need privileged inकाष्ठाions to get to. The r15 value we
	 * fetch from the thपढ़ो info directly.
	 */
	क्रम (reg = GDB_R8; reg < GDB_R15; reg++)
		gdb_regs[reg] = thपढ़ो_regs->regs[reg];

	gdb_regs[GDB_R15] = p->thपढ़ो.sp;
	gdb_regs[GDB_PC] = p->thपढ़ो.pc;

	/*
	 * Additional रेजिस्टरs we have context क्रम
	 */
	gdb_regs[GDB_PR] = thपढ़ो_regs->pr;
	gdb_regs[GDB_GBR] = thपढ़ो_regs->gbr;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक e_vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcomInBuffer, अक्षर *remcomOutBuffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	/* Unकरो any stepping we may have करोne */
	unकरो_single_step(linux_regs);

	चयन (remcomInBuffer[0]) अणु
	हाल 'c':
	हाल 's':
		/* try to पढ़ो optional parameter, pc unchanged अगर no parm */
		ptr = &remcomInBuffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			linux_regs->pc = addr;
		fallthrough;
	हाल 'D':
	हाल 'k':
		atomic_set(&kgdb_cpu_करोing_single_step, -1);

		अगर (remcomInBuffer[0] == 's') अणु
			करो_single_step(linux_regs);
			kgdb_single_step = 1;

			atomic_set(&kgdb_cpu_करोing_single_step,
				   raw_smp_processor_id());
		पूर्ण

		वापस 0;
	पूर्ण

	/* this means that we करो not want to निकास from the handler: */
	वापस -1;
पूर्ण

अचिन्हित दीर्घ kgdb_arch_pc(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	अगर (exception == 60)
		वापस inकाष्ठाion_poपूर्णांकer(regs) - 2;
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->pc = ip;
पूर्ण

/*
 * The primary entry poपूर्णांकs क्रम the kgdb debug trap table entries.
 */
BUILD_TRAP_HANDLER(singlestep)
अणु
	अचिन्हित दीर्घ flags;
	TRAP_HANDLER_DECL;

	local_irq_save(flags);
	regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));
	kgdb_handle_exception(0, SIGTRAP, 0, regs);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __kgdb_notअगरy(काष्ठा die_args *args, अचिन्हित दीर्घ cmd)
अणु
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल DIE_BREAKPOINT:
		/*
		 * This means a user thपढ़ो is single stepping
		 * a प्रणाली call which should be ignored
		 */
		अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
			वापस NOTIFY_DONE;

		ret = kgdb_handle_exception(args->trapnr & 0xff, args->signr,
					    args->err, args->regs);
		अगर (ret)
			वापस NOTIFY_DONE;

		अवरोध;
	पूर्ण

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
	 * Lowest-prio notअगरier priority, we want to be notअगरied last:
	 */
	.priority	= -पूर्णांक_उच्च,
पूर्ण;

पूर्णांक kgdb_arch_init(व्योम)
अणु
	वापस रेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: trapa #0x3c */
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
	.gdb_bpt_instr		= अणु 0x3c, 0xc3 पूर्ण,
#अन्यथा
	.gdb_bpt_instr		= अणु 0xc3, 0x3c पूर्ण,
#पूर्ण_अगर
पूर्ण;
