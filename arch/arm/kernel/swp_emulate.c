<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/swp_emulate.c
 *
 *  Copyright (C) 2009 ARM Limited
 *  __user_* functions adapted from include/यंत्र/uaccess.h
 *
 *  Implements emulation of the SWP/SWPB inकाष्ठाions using load-exclusive and
 *  store-exclusive क्रम processors that have them disabled (or future ones that
 *  might not implement them).
 *
 *  Syntax of SWPअणुBपूर्ण inकाष्ठाion: SWPअणुBपूर्ण<c> <Rt>, <Rt2>, [<Rn>]
 *  Where: Rt  = destination
 *	   Rt2 = source
 *	   Rn  = address
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

/*
 * Error-checking SWP macros implemented using ldrexअणुbपूर्ण/strexअणुbपूर्ण
 */
#घोषणा __user_swpX_यंत्र(data, addr, res, temp, B)		\
	__यंत्र__ __अस्थिर__(					\
	"0:	ldrex"B"	%2, [%3]\n"			\
	"1:	strex"B"	%0, %1, [%3]\n"			\
	"	cmp		%0, #0\n"			\
	"	moveq		%1, %2\n"			\
	"	movne		%0, %4\n"			\
	"2:\n"							\
	"	.section	 .text.fixup,\"ax\"\n"		\
	"	.align		2\n"				\
	"3:	mov		%0, %5\n"			\
	"	b		2b\n"				\
	"	.previous\n"					\
	"	.section	 __ex_table,\"a\"\n"		\
	"	.align		3\n"				\
	"	.long		0b, 3b\n"			\
	"	.long		1b, 3b\n"			\
	"	.previous"					\
	: "=&r" (res), "+r" (data), "=&r" (temp)		\
	: "r" (addr), "i" (-EAGAIN), "i" (-EFAULT)		\
	: "cc", "memory")

#घोषणा __user_swp_यंत्र(data, addr, res, temp) \
	__user_swpX_यंत्र(data, addr, res, temp, "")
#घोषणा __user_swpb_यंत्र(data, addr, res, temp) \
	__user_swpX_यंत्र(data, addr, res, temp, "b")

/*
 * Macros/defines क्रम extracting रेजिस्टर numbers from inकाष्ठाion.
 */
#घोषणा EXTRACT_REG_NUM(inकाष्ठाion, offset) \
	(((inकाष्ठाion) & (0xf << (offset))) >> (offset))
#घोषणा RN_OFFSET  16
#घोषणा RT_OFFSET  12
#घोषणा RT2_OFFSET  0
/*
 * Bit 22 of the inकाष्ठाion encoding distinguishes between
 * the SWP and SWPB variants (bit set means SWPB).
 */
#घोषणा TYPE_SWPB (1 << 22)

अटल अचिन्हित दीर्घ swpcounter;
अटल अचिन्हित दीर्घ swpbcounter;
अटल अचिन्हित दीर्घ abtcounter;
अटल pid_t         previous_pid;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_status_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "Emulated SWP:\t\t%lu\n", swpcounter);
	seq_म_लिखो(m, "Emulated SWPB:\t\t%lu\n", swpbcounter);
	seq_म_लिखो(m, "Aborted SWP{B}:\t\t%lu\n", abtcounter);
	अगर (previous_pid != 0)
		seq_म_लिखो(m, "Last process:\t\t%d\n", previous_pid);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Set up process info to संकेत segmentation fault - called on access error.
 */
अटल व्योम set_segfault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक si_code;

	mmap_पढ़ो_lock(current->mm);
	अगर (find_vma(current->mm, addr) == शून्य)
		si_code = SEGV_MAPERR;
	अन्यथा
		si_code = SEGV_ACCERR;
	mmap_पढ़ो_unlock(current->mm);

	pr_debug("SWP{B} emulation: access caused memory abort!\n");
	arm_notअगरy_die("Illegal memory access", regs,
		       संक_अंश, si_code,
		       (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs),
		       0, 0);

	abtcounter++;
पूर्ण

अटल पूर्णांक emulate_swpX(अचिन्हित पूर्णांक address, अचिन्हित पूर्णांक *data,
			अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक res = 0;

	अगर ((type != TYPE_SWPB) && (address & 0x3)) अणु
		/* SWP to unaligned address not permitted */
		pr_debug("SWP instruction on unaligned pointer!\n");
		वापस -EFAULT;
	पूर्ण

	जबतक (1) अणु
		अचिन्हित दीर्घ temp;
		अचिन्हित पूर्णांक __ua_flags;

		__ua_flags = uaccess_save_and_enable();
		अगर (type == TYPE_SWPB)
			__user_swpb_यंत्र(*data, address, res, temp);
		अन्यथा
			__user_swp_यंत्र(*data, address, res, temp);
		uaccess_restore(__ua_flags);

		अगर (likely(res != -EAGAIN) || संकेत_pending(current))
			अवरोध;

		cond_resched();
	पूर्ण

	अगर (res == 0) अणु
		अगर (type == TYPE_SWPB)
			swpbcounter++;
		अन्यथा
			swpcounter++;
	पूर्ण

	वापस res;
पूर्ण

/*
 * swp_handler logs the id of calling process, dissects the inकाष्ठाion, sanity
 * checks the memory location, calls emulate_swpX क्रम the actual operation and
 * deals with fixup/error handling beक्रमe वापसing
 */
अटल पूर्णांक swp_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	अचिन्हित पूर्णांक address, destreg, data, type;
	अचिन्हित पूर्णांक res = 0;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, regs->ARM_pc);

	res = arm_check_condition(instr, regs->ARM_cpsr);
	चयन (res) अणु
	हाल ARM_OPCODE_CONDTEST_PASS:
		अवरोध;
	हाल ARM_OPCODE_CONDTEST_FAIL:
		/* Condition failed - वापस to next inकाष्ठाion */
		regs->ARM_pc += 4;
		वापस 0;
	हाल ARM_OPCODE_CONDTEST_UNCOND:
		/* If unconditional encoding - not a SWP, undef */
		वापस -EFAULT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (current->pid != previous_pid) अणु
		pr_debug("\"%s\" (%ld) uses deprecated SWP{B} instruction\n",
			 current->comm, (अचिन्हित दीर्घ)current->pid);
		previous_pid = current->pid;
	पूर्ण

	address = regs->uregs[EXTRACT_REG_NUM(instr, RN_OFFSET)];
	data	= regs->uregs[EXTRACT_REG_NUM(instr, RT2_OFFSET)];
	destreg = EXTRACT_REG_NUM(instr, RT_OFFSET);

	type = instr & TYPE_SWPB;

	pr_debug("addr in r%d->0x%08x, dest is r%d, source in r%d->0x%08x)\n",
		 EXTRACT_REG_NUM(instr, RN_OFFSET), address,
		 destreg, EXTRACT_REG_NUM(instr, RT2_OFFSET), data);

	/* Check access in reasonable access range क्रम both SWP and SWPB */
	अगर (!access_ok((address & ~3), 4)) अणु
		pr_debug("SWP{B} emulation: access to %p not allowed!\n",
			 (व्योम *)address);
		res = -EFAULT;
	पूर्ण अन्यथा अणु
		res = emulate_swpX(address, &data, type);
	पूर्ण

	अगर (res == 0) अणु
		/*
		 * On successful emulation, revert the adjusपंचांगent to the PC
		 * made in kernel/traps.c in order to resume execution at the
		 * inकाष्ठाion following the SWPअणुBपूर्ण.
		 */
		regs->ARM_pc += 4;
		regs->uregs[destreg] = data;
	पूर्ण अन्यथा अगर (res == -EFAULT) अणु
		/*
		 * Memory errors करो not mean emulation failed.
		 * Set up संकेत info to वापस SEGV, then वापस OK
		 */
		set_segfault(regs, address);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Only emulate SWP/SWPB executed in ARM state/User mode.
 * The kernel must be SWP मुक्त and SWPअणुBपूर्ण करोes not exist in Thumb/ThumbEE.
 */
अटल काष्ठा undef_hook swp_hook = अणु
	.instr_mask = 0x0fb00ff0,
	.instr_val  = 0x01000090,
	.cpsr_mask  = MODE_MASK | PSR_T_BIT | PSR_J_BIT,
	.cpsr_val   = USR_MODE,
	.fn	    = swp_handler
पूर्ण;

/*
 * Register handler and create status file in /proc/cpu
 * Invoked as late_initcall, since not needed beक्रमe init spawned.
 */
अटल पूर्णांक __init swp_emulation_init(व्योम)
अणु
	अगर (cpu_architecture() < CPU_ARCH_ARMv7)
		वापस 0;

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_single("cpu/swp_emulation", S_IRUGO, शून्य,
			proc_status_show))
		वापस -ENOMEM;
#पूर्ण_अगर /* CONFIG_PROC_FS */

	pr_notice("Registering SWP/SWPB emulation handler\n");
	रेजिस्टर_undef_hook(&swp_hook);

	वापस 0;
पूर्ण

late_initcall(swp_emulation_init);
