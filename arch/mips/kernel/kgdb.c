<शैली गुरु>
/*
 *  Originally written by Glenn Engel, Lake Stevens Instrument Division
 *
 *  Contributed by HP Systems
 *
 *  Modअगरied क्रम Linux/MIPS (and MIPS in general) by Andreas Busse
 *  Send complaपूर्णांकs, suggestions etc. to <andy@walकरोrf-gmbh.de>
 *
 *  Copyright (C) 1995 Andreas Busse
 *
 *  Copyright (C) 2003 MontaVista Software Inc.
 *  Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 *  Copyright (C) 2004-2005 MontaVista Software Inc.
 *  Author: Manish Lachwani, mlachwani@mvista.com or manish@koffee-अवरोध.com
 *
 *  Copyright (C) 2007-2008 Wind River Systems, Inc.
 *  Author/Maपूर्णांकainer: Jason Wessel, jason.wessel@windriver.com
 *
 *  This file is licensed under the terms of the GNU General Public License
 *  version 2. This program is licensed "as is" without any warranty of any
 *  kind, whether express or implied.
 */

#समावेश <linux/ptrace.h>		/* क्रम linux pt_regs काष्ठा */
#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/irq_regs.h>

अटल काष्ठा hard_trap_info अणु
	अचिन्हित अक्षर tt;	/* Trap type code क्रम MIPS R3xxx and R4xxx */
	अचिन्हित अक्षर signo;	/* Signal that we map this trap पूर्णांकo */
पूर्ण hard_trap_info[] = अणु
	अणु 6, SIGBUS पूर्ण,		/* inकाष्ठाion bus error */
	अणु 7, SIGBUS पूर्ण,		/* data bus error */
	अणु 9, SIGTRAP पूर्ण,		/* अवरोध */
/*	अणु 11, संक_अवैध पूर्ण, */	/* CPU unusable */
	अणु 12, संक_भ_त्रुटि पूर्ण,		/* overflow */
	अणु 13, SIGTRAP पूर्ण,	/* trap */
	अणु 14, संक_अंश पूर्ण,	/* भव inकाष्ठाion cache coherency */
	अणु 15, संक_भ_त्रुटि पूर्ण,		/* भग्नing poपूर्णांक exception */
	अणु 23, संक_अंश पूर्ण,	/* watch */
	अणु 31, संक_अंश पूर्ण,	/* भव data cache coherency */
	अणु 0, 0पूर्ण			/* Must be last */
पूर्ण;

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] =
अणु
	अणु "zero", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[0]) पूर्ण,
	अणु "at", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[1]) पूर्ण,
	अणु "v0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[2]) पूर्ण,
	अणु "v1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[3]) पूर्ण,
	अणु "a0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[4]) पूर्ण,
	अणु "a1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[5]) पूर्ण,
	अणु "a2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[6]) पूर्ण,
	अणु "a3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[7]) पूर्ण,
	अणु "t0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[8]) पूर्ण,
	अणु "t1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[9]) पूर्ण,
	अणु "t2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[10]) पूर्ण,
	अणु "t3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[11]) पूर्ण,
	अणु "t4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[12]) पूर्ण,
	अणु "t5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[13]) पूर्ण,
	अणु "t6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[14]) पूर्ण,
	अणु "t7", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[15]) पूर्ण,
	अणु "s0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[16]) पूर्ण,
	अणु "s1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[17]) पूर्ण,
	अणु "s2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[18]) पूर्ण,
	अणु "s3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[19]) पूर्ण,
	अणु "s4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[20]) पूर्ण,
	अणु "s5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[21]) पूर्ण,
	अणु "s6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[22]) पूर्ण,
	अणु "s7", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[23]) पूर्ण,
	अणु "t8", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[24]) पूर्ण,
	अणु "t9", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[25]) पूर्ण,
	अणु "k0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[26]) पूर्ण,
	अणु "k1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[27]) पूर्ण,
	अणु "gp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[28]) पूर्ण,
	अणु "sp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[29]) पूर्ण,
	अणु "s8", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[30]) पूर्ण,
	अणु "ra", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, regs[31]) पूर्ण,
	अणु "sr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cp0_status) पूर्ण,
	अणु "lo", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, lo) पूर्ण,
	अणु "hi", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, hi) पूर्ण,
	अणु "bad", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cp0_badvaddr) पूर्ण,
	अणु "cause", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cp0_cause) पूर्ण,
	अणु "pc", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cp0_epc) पूर्ण,
	अणु "f0", GDB_SIZखातापूर्ण_REG, 0 पूर्ण,
	अणु "f1", GDB_SIZखातापूर्ण_REG, 1 पूर्ण,
	अणु "f2", GDB_SIZखातापूर्ण_REG, 2 पूर्ण,
	अणु "f3", GDB_SIZखातापूर्ण_REG, 3 पूर्ण,
	अणु "f4", GDB_SIZखातापूर्ण_REG, 4 पूर्ण,
	अणु "f5", GDB_SIZखातापूर्ण_REG, 5 पूर्ण,
	अणु "f6", GDB_SIZखातापूर्ण_REG, 6 पूर्ण,
	अणु "f7", GDB_SIZखातापूर्ण_REG, 7 पूर्ण,
	अणु "f8", GDB_SIZखातापूर्ण_REG, 8 पूर्ण,
	अणु "f9", GDB_SIZखातापूर्ण_REG, 9 पूर्ण,
	अणु "f10", GDB_SIZखातापूर्ण_REG, 10 पूर्ण,
	अणु "f11", GDB_SIZखातापूर्ण_REG, 11 पूर्ण,
	अणु "f12", GDB_SIZखातापूर्ण_REG, 12 पूर्ण,
	अणु "f13", GDB_SIZखातापूर्ण_REG, 13 पूर्ण,
	अणु "f14", GDB_SIZखातापूर्ण_REG, 14 पूर्ण,
	अणु "f15", GDB_SIZखातापूर्ण_REG, 15 पूर्ण,
	अणु "f16", GDB_SIZखातापूर्ण_REG, 16 पूर्ण,
	अणु "f17", GDB_SIZखातापूर्ण_REG, 17 पूर्ण,
	अणु "f18", GDB_SIZखातापूर्ण_REG, 18 पूर्ण,
	अणु "f19", GDB_SIZखातापूर्ण_REG, 19 पूर्ण,
	अणु "f20", GDB_SIZखातापूर्ण_REG, 20 पूर्ण,
	अणु "f21", GDB_SIZखातापूर्ण_REG, 21 पूर्ण,
	अणु "f22", GDB_SIZखातापूर्ण_REG, 22 पूर्ण,
	अणु "f23", GDB_SIZखातापूर्ण_REG, 23 पूर्ण,
	अणु "f24", GDB_SIZखातापूर्ण_REG, 24 पूर्ण,
	अणु "f25", GDB_SIZखातापूर्ण_REG, 25 पूर्ण,
	अणु "f26", GDB_SIZखातापूर्ण_REG, 26 पूर्ण,
	अणु "f27", GDB_SIZखातापूर्ण_REG, 27 पूर्ण,
	अणु "f28", GDB_SIZखातापूर्ण_REG, 28 पूर्ण,
	अणु "f29", GDB_SIZखातापूर्ण_REG, 29 पूर्ण,
	अणु "f30", GDB_SIZखातापूर्ण_REG, 30 पूर्ण,
	अणु "f31", GDB_SIZखातापूर्ण_REG, 31 पूर्ण,
	अणु "fsr", GDB_SIZखातापूर्ण_REG, 0 पूर्ण,
	अणु "fir", GDB_SIZखातापूर्ण_REG, 0 पूर्ण,
पूर्ण;

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	पूर्णांक fp_reg;

	अगर (regno < 0 || regno >= DBG_MAX_REG_NUM)
		वापस -EINVAL;

	अगर (dbg_reg_def[regno].offset != -1 && regno < 38) अणु
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	पूर्ण अन्यथा अगर (current && dbg_reg_def[regno].offset != -1 && regno < 72) अणु
		/* FP रेजिस्टरs 38 -> 69 */
		अगर (!(regs->cp0_status & ST0_CU1))
			वापस 0;
		अगर (regno == 70) अणु
			/* Process the fcr31/fsr (रेजिस्टर 70) */
			स_नकल((व्योम *)&current->thपढ़ो.fpu.fcr31, mem,
			       dbg_reg_def[regno].size);
			जाओ out_save;
		पूर्ण अन्यथा अगर (regno == 71) अणु
			/* Ignore the fir (रेजिस्टर 71) */
			जाओ out_save;
		पूर्ण
		fp_reg = dbg_reg_def[regno].offset;
		स_नकल((व्योम *)&current->thपढ़ो.fpu.fpr[fp_reg], mem,
		       dbg_reg_def[regno].size);
out_save:
		restore_fp(current);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	पूर्णांक fp_reg;

	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (dbg_reg_def[regno].offset != -1 && regno < 38) अणु
		/* First 38 रेजिस्टरs */
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);
	पूर्ण अन्यथा अगर (current && dbg_reg_def[regno].offset != -1 && regno < 72) अणु
		/* FP रेजिस्टरs 38 -> 69 */
		अगर (!(regs->cp0_status & ST0_CU1))
			जाओ out;
		save_fp(current);
		अगर (regno == 70) अणु
			/* Process the fcr31/fsr (रेजिस्टर 70) */
			स_नकल(mem, (व्योम *)&current->thपढ़ो.fpu.fcr31,
			       dbg_reg_def[regno].size);
			जाओ out;
		पूर्ण अन्यथा अगर (regno == 71) अणु
			/* Ignore the fir (रेजिस्टर 71) */
			स_रखो(mem, 0, dbg_reg_def[regno].size);
			जाओ out;
		पूर्ण
		fp_reg = dbg_reg_def[regno].offset;
		स_नकल(mem, (व्योम *)&current->thपढ़ो.fpu.fpr[fp_reg],
		       dbg_reg_def[regno].size);
	पूर्ण

out:
	वापस dbg_reg_def[regno].name;

पूर्ण

व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".globl breakinst\n\t"
		".set\tnoreorder\n\t"
		"nop\n"
		"breakinst:\tbreak\n\t"
		"nop\n\t"
		".set\treorder");
पूर्ण

अटल पूर्णांक compute_संकेत(पूर्णांक tt)
अणु
	काष्ठा hard_trap_info *ht;

	क्रम (ht = hard_trap_info; ht->tt && ht->signo; ht++)
		अगर (ht->tt == tt)
			वापस ht->signo;

	वापस SIGHUP;		/* शेष क्रम things we करोn't know about */
पूर्ण

/*
 * Similar to regs_to_gdb_regs() except that process is sleeping and so
 * we may not be able to get all the info.
 */
व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक reg;
#अगर (KGDB_GDB_REG_SIZE == 32)
	u32 *ptr = (u32 *)gdb_regs;
#अन्यथा
	u64 *ptr = (u64 *)gdb_regs;
#पूर्ण_अगर

	क्रम (reg = 0; reg < 16; reg++)
		*(ptr++) = 0;

	/* S0 - S7 */
	*(ptr++) = p->thपढ़ो.reg16;
	*(ptr++) = p->thपढ़ो.reg17;
	*(ptr++) = p->thपढ़ो.reg18;
	*(ptr++) = p->thपढ़ो.reg19;
	*(ptr++) = p->thपढ़ो.reg20;
	*(ptr++) = p->thपढ़ो.reg21;
	*(ptr++) = p->thपढ़ो.reg22;
	*(ptr++) = p->thपढ़ो.reg23;

	क्रम (reg = 24; reg < 28; reg++)
		*(ptr++) = 0;

	/* GP, SP, FP, RA */
	*(ptr++) = (दीर्घ)p;
	*(ptr++) = p->thपढ़ो.reg29;
	*(ptr++) = p->thपढ़ो.reg30;
	*(ptr++) = p->thपढ़ो.reg31;

	*(ptr++) = p->thपढ़ो.cp0_status;

	/* lo, hi */
	*(ptr++) = 0;
	*(ptr++) = 0;

	/*
	 * BadVAddr, Cause
	 * Ideally these would come from the last exception frame up the stack
	 * but that requires unwinding, otherwise we can't know much क्रम sure.
	 */
	*(ptr++) = 0;
	*(ptr++) = 0;

	/*
	 * PC
	 * use वापस address (RA), i.e. the moment after वापस from resume()
	 */
	*(ptr++) = p->thपढ़ो.reg31;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->cp0_epc = pc;
पूर्ण

/*
 * Calls linux_debug_hook beक्रमe the kernel dies. If KGDB is enabled,
 * then try to fall पूर्णांकo the debugger
 */
अटल पूर्णांक kgdb_mips_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			    व्योम *ptr)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *)ptr;
	काष्ठा pt_regs *regs = args->regs;
	पूर्णांक trap = (regs->cp0_cause & 0x7c) >> 2;

#अगर_घोषित CONFIG_KPROBES
	/*
	 * Return immediately अगर the kprobes fault notअगरier has set
	 * DIE_PAGE_FAULT.
	 */
	अगर (cmd == DIE_PAGE_FAULT)
		वापस NOTIFY_DONE;
#पूर्ण_अगर /* CONFIG_KPROBES */

	/* Userspace events, ignore. */
	अगर (user_mode(regs))
		वापस NOTIFY_DONE;

	अगर (atomic_पढ़ो(&kgdb_active) != -1)
		kgdb_nmicallback(smp_processor_id(), regs);

	अगर (kgdb_handle_exception(trap, compute_संकेत(trap), cmd, regs))
		वापस NOTIFY_DONE;

	अगर (atomic_पढ़ो(&kgdb_setting_अवरोधpoपूर्णांक))
		अगर ((trap == 9) && (regs->cp0_epc == (अचिन्हित दीर्घ)अवरोधinst))
			regs->cp0_epc += 4;

	/* In SMP mode, __flush_cache_all करोes IPI */
	local_irq_enable();
	__flush_cache_all();

	वापस NOTIFY_STOP;
पूर्ण

#अगर_घोषित CONFIG_KGDB_LOW_LEVEL_TRAP
पूर्णांक kgdb_ll_trap(पूर्णांक cmd, स्थिर अक्षर *str,
		 काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig)
अणु
	काष्ठा die_args args = अणु
		.regs	= regs,
		.str	= str,
		.err	= err,
		.trapnr = trap,
		.signr	= sig,

	पूर्ण;

	अगर (!kgdb_io_module_रेजिस्टरed)
		वापस NOTIFY_DONE;

	वापस kgdb_mips_notअगरy(शून्य, cmd, &args);
पूर्ण
#पूर्ण_अगर /* CONFIG_KGDB_LOW_LEVEL_TRAP */

अटल काष्ठा notअगरier_block kgdb_notअगरier = अणु
	.notअगरier_call = kgdb_mips_notअगरy,
पूर्ण;

/*
 * Handle the 'c' command
 */
पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *regs)
अणु
	अक्षर *ptr;
	अचिन्हित दीर्घ address;

	चयन (remcom_in_buffer[0]) अणु
	हाल 'c':
		/* handle the optional parameter */
		ptr = &remcom_in_buffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &address))
			regs->cp0_epc = address;

		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	.gdb_bpt_instr = अणु spec_op << 2, 0x00, 0x00, अवरोध_op पूर्ण,
#अन्यथा
	.gdb_bpt_instr = अणु अवरोध_op, 0x00, 0x00, spec_op << 2 पूर्ण,
#पूर्ण_अगर
पूर्ण;

पूर्णांक kgdb_arch_init(व्योम)
अणु
	रेजिस्टर_die_notअगरier(&kgdb_notअगरier);

	वापस 0;
पूर्ण

/*
 *	kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 *
 *	This function will handle the uninitalization of any architecture
 *	specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण
