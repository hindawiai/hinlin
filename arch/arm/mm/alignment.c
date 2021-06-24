<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/alignment.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Modअगरications क्रम ARM processor (c) 1995-2001 Russell King
 *  Thumb alignment fault fixups (c) 2004 MontaVista Software, Inc.
 *  - Adapted from gdb/sim/arm/thumbemu.c -- Thumb inकाष्ठाion emulation.
 *    Copyright (C) 1996, Cygnus Software Technologies Ltd.
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/opcodes.h>

#समावेश "fault.h"
#समावेश "mm.h"

/*
 * 32-bit misaligned trap handler (c) 1998 San Mehat (CCC) -July 1998
 * /proc/sys/debug/alignment, modअगरied and पूर्णांकegrated पूर्णांकo
 * Linux 2.1 by Russell King
 *
 * Speed optimisations and better fault handling by Russell King.
 *
 * *** NOTE ***
 * This code is not portable to processors with late data पात handling.
 */
#घोषणा CODING_BITS(i)	(i & 0x0e000000)
#घोषणा COND_BITS(i)	(i & 0xf0000000)

#घोषणा LDST_I_BIT(i)	(i & (1 << 26))		/* Immediate स्थिरant	*/
#घोषणा LDST_P_BIT(i)	(i & (1 << 24))		/* Preindex		*/
#घोषणा LDST_U_BIT(i)	(i & (1 << 23))		/* Add offset		*/
#घोषणा LDST_W_BIT(i)	(i & (1 << 21))		/* Writeback		*/
#घोषणा LDST_L_BIT(i)	(i & (1 << 20))		/* Load			*/

#घोषणा LDST_P_EQ_U(i)	((((i) ^ ((i) >> 1)) & (1 << 23)) == 0)

#घोषणा LDSTHD_I_BIT(i)	(i & (1 << 22))		/* द्विगुन/half-word immed */
#घोषणा LDM_S_BIT(i)	(i & (1 << 22))		/* ग_लिखो CPSR from SPSR	*/

#घोषणा RN_BITS(i)	((i >> 16) & 15)	/* Rn			*/
#घोषणा RD_BITS(i)	((i >> 12) & 15)	/* Rd			*/
#घोषणा RM_BITS(i)	(i & 15)		/* Rm			*/

#घोषणा REGMASK_BITS(i)	(i & 0xffff)
#घोषणा OFFSET_BITS(i)	(i & 0x0fff)

#घोषणा IS_SHIFT(i)	(i & 0x0ff0)
#घोषणा SHIFT_BITS(i)	((i >> 7) & 0x1f)
#घोषणा SHIFT_TYPE(i)	(i & 0x60)
#घोषणा SHIFT_LSL	0x00
#घोषणा SHIFT_LSR	0x20
#घोषणा SHIFT_ASR	0x40
#घोषणा SHIFT_RORRRX	0x60

#घोषणा BAD_INSTR 	0xdeadc0de

/* Thumb-2 32 bit क्रमmat per ARMv7 DDI0406A A6.3, either f800h,e800h,f800h */
#घोषणा IS_T32(hi16) \
	(((hi16) & 0xe000) == 0xe000 && ((hi16) & 0x1800))

अटल अचिन्हित दीर्घ ai_user;
अटल अचिन्हित दीर्घ ai_sys;
अटल व्योम *ai_sys_last_pc;
अटल अचिन्हित दीर्घ ai_skipped;
अटल अचिन्हित दीर्घ ai_half;
अटल अचिन्हित दीर्घ ai_word;
अटल अचिन्हित दीर्घ ai_dword;
अटल अचिन्हित दीर्घ ai_multi;
अटल पूर्णांक ai_usermode;
अटल अचिन्हित दीर्घ cr_no_alignment;

core_param(alignment, ai_usermode, पूर्णांक, 0600);

#घोषणा UM_WARN		(1 << 0)
#घोषणा UM_FIXUP	(1 << 1)
#घोषणा UM_SIGNAL	(1 << 2)

/* Return true अगर and only अगर the ARMv6 unaligned access model is in use. */
अटल bool cpu_is_v6_unaligned(व्योम)
अणु
	वापस cpu_architecture() >= CPU_ARCH_ARMv6 && get_cr() & CR_U;
पूर्ण

अटल पूर्णांक safe_usermode(पूर्णांक new_usermode, bool warn)
अणु
	/*
	 * ARMv6 and later CPUs can perक्रमm unaligned accesses क्रम
	 * most single load and store inकाष्ठाions up to word size.
	 * LDM, STM, LDRD and STRD still need to be handled.
	 *
	 * Ignoring the alignment fault is not an option on these
	 * CPUs since we spin re-faulting the inकाष्ठाion without
	 * making any progress.
	 */
	अगर (cpu_is_v6_unaligned() && !(new_usermode & (UM_FIXUP | UM_SIGNAL))) अणु
		new_usermode |= UM_FIXUP;

		अगर (warn)
			pr_warn("alignment: ignoring faults is unsafe on this CPU.  Defaulting to fixup mode.\n");
	पूर्ण

	वापस new_usermode;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर अक्षर *usermode_action[] = अणु
	"ignored",
	"warn",
	"fixup",
	"fixup+warn",
	"signal",
	"signal+warn"
पूर्ण;

अटल पूर्णांक alignment_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "User:\t\t%lu\n", ai_user);
	seq_म_लिखो(m, "System:\t\t%lu (%pS)\n", ai_sys, ai_sys_last_pc);
	seq_म_लिखो(m, "Skipped:\t%lu\n", ai_skipped);
	seq_म_लिखो(m, "Half:\t\t%lu\n", ai_half);
	seq_म_लिखो(m, "Word:\t\t%lu\n", ai_word);
	अगर (cpu_architecture() >= CPU_ARCH_ARMv5TE)
		seq_म_लिखो(m, "DWord:\t\t%lu\n", ai_dword);
	seq_म_लिखो(m, "Multi:\t\t%lu\n", ai_multi);
	seq_म_लिखो(m, "User faults:\t%i (%s)\n", ai_usermode,
			usermode_action[ai_usermode]);

	वापस 0;
पूर्ण

अटल पूर्णांक alignment_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, alignment_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार alignment_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				    माप_प्रकार count, loff_t *pos)
अणु
	अक्षर mode;

	अगर (count > 0) अणु
		अगर (get_user(mode, buffer))
			वापस -EFAULT;
		अगर (mode >= '0' && mode <= '5')
			ai_usermode = safe_usermode(mode - '0', true);
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops alignment_proc_ops = अणु
	.proc_खोलो	= alignment_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= alignment_proc_ग_लिखो,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

जोड़ offset_जोड़ अणु
	अचिन्हित दीर्घ un;
	  चिन्हित दीर्घ sn;
पूर्ण;

#घोषणा TYPE_ERROR	0
#घोषणा TYPE_FAULT	1
#घोषणा TYPE_LDST	2
#घोषणा TYPE_DONE	3

#अगर_घोषित __ARMEB__
#घोषणा BE		1
#घोषणा FIRST_BYTE_16	"mov	%1, %1, ror #8\n"
#घोषणा FIRST_BYTE_32	"mov	%1, %1, ror #24\n"
#घोषणा NEXT_BYTE	"ror #24"
#अन्यथा
#घोषणा BE		0
#घोषणा FIRST_BYTE_16
#घोषणा FIRST_BYTE_32
#घोषणा NEXT_BYTE	"lsr #8"
#पूर्ण_अगर

#घोषणा __get8_unaligned_check(ins,val,addr,err)	\
	__यंत्र__(					\
 ARM(	"1:	"ins"	%1, [%2], #1\n"	)		\
 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
 THUMB(	"	add	%2, %2, #1\n"	)		\
	"2:\n"						\
	"	.pushsection .text.fixup,\"ax\"\n"	\
	"	.align	2\n"				\
	"3:	mov	%0, #1\n"			\
	"	b	2b\n"				\
	"	.popsection\n"				\
	"	.pushsection __ex_table,\"a\"\n"	\
	"	.align	3\n"				\
	"	.long	1b, 3b\n"			\
	"	.popsection\n"				\
	: "=r" (err), "=&r" (val), "=r" (addr)		\
	: "0" (err), "2" (addr))

#घोषणा __get16_unaligned_check(ins,val,addr)			\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v, a = addr;		\
		__get8_unaligned_check(ins,v,a,err);		\
		val =  v << ((BE) ? 8 : 0);			\
		__get8_unaligned_check(ins,v,a,err);		\
		val |= v << ((BE) ? 0 : 8);			\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक (0)

#घोषणा get16_unaligned_check(val,addr) \
	__get16_unaligned_check("ldrb",val,addr)

#घोषणा get16t_unaligned_check(val,addr) \
	__get16_unaligned_check("ldrbt",val,addr)

#घोषणा __get32_unaligned_check(ins,val,addr)			\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v, a = addr;		\
		__get8_unaligned_check(ins,v,a,err);		\
		val =  v << ((BE) ? 24 :  0);			\
		__get8_unaligned_check(ins,v,a,err);		\
		val |= v << ((BE) ? 16 :  8);			\
		__get8_unaligned_check(ins,v,a,err);		\
		val |= v << ((BE) ?  8 : 16);			\
		__get8_unaligned_check(ins,v,a,err);		\
		val |= v << ((BE) ?  0 : 24);			\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक (0)

#घोषणा get32_unaligned_check(val,addr) \
	__get32_unaligned_check("ldrb",val,addr)

#घोषणा get32t_unaligned_check(val,addr) \
	__get32_unaligned_check("ldrbt",val,addr)

#घोषणा __put16_unaligned_check(ins,val,addr)			\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v = val, a = addr;	\
		__यंत्र__( FIRST_BYTE_16				\
	 ARM(	"1:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
		"2:	"ins"	%1, [%2]\n"			\
		"3:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.align	2\n"				\
		"4:	mov	%0, #1\n"			\
		"	b	3b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_table,\"a\"\n"	\
		"	.align	3\n"				\
		"	.long	1b, 4b\n"			\
		"	.long	2b, 4b\n"			\
		"	.popsection\n"				\
		: "=r" (err), "=&r" (v), "=&r" (a)		\
		: "0" (err), "1" (v), "2" (a));			\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक (0)

#घोषणा put16_unaligned_check(val,addr)  \
	__put16_unaligned_check("strb",val,addr)

#घोषणा put16t_unaligned_check(val,addr) \
	__put16_unaligned_check("strbt",val,addr)

#घोषणा __put32_unaligned_check(ins,val,addr)			\
	करो अणु							\
		अचिन्हित पूर्णांक err = 0, v = val, a = addr;	\
		__यंत्र__( FIRST_BYTE_32				\
	 ARM(	"1:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
	 ARM(	"2:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"2:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
	 ARM(	"3:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"3:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
		"4:	"ins"	%1, [%2]\n"			\
		"5:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.align	2\n"				\
		"6:	mov	%0, #1\n"			\
		"	b	5b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_table,\"a\"\n"	\
		"	.align	3\n"				\
		"	.long	1b, 6b\n"			\
		"	.long	2b, 6b\n"			\
		"	.long	3b, 6b\n"			\
		"	.long	4b, 6b\n"			\
		"	.popsection\n"				\
		: "=r" (err), "=&r" (v), "=&r" (a)		\
		: "0" (err), "1" (v), "2" (a));			\
		अगर (err)					\
			जाओ fault;				\
	पूर्ण जबतक (0)

#घोषणा put32_unaligned_check(val,addr) \
	__put32_unaligned_check("strb", val, addr)

#घोषणा put32t_unaligned_check(val,addr) \
	__put32_unaligned_check("strbt", val, addr)

अटल व्योम
करो_alignment_finish_ldst(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs, जोड़ offset_जोड़ offset)
अणु
	अगर (!LDST_U_BIT(instr))
		offset.un = -offset.un;

	अगर (!LDST_P_BIT(instr))
		addr += offset.un;

	अगर (!LDST_P_BIT(instr) || LDST_W_BIT(instr))
		regs->uregs[RN_BITS(instr)] = addr;
पूर्ण

अटल पूर्णांक
करो_alignment_ldrhstrh(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक rd = RD_BITS(instr);

	ai_half += 1;

	अगर (user_mode(regs))
		जाओ user;

	अगर (LDST_L_BIT(instr)) अणु
		अचिन्हित दीर्घ val;
		get16_unaligned_check(val, addr);

		/* चिन्हित half-word? */
		अगर (instr & 0x40)
			val = (चिन्हित दीर्घ)((चिन्हित लघु) val);

		regs->uregs[rd] = val;
	पूर्ण अन्यथा
		put16_unaligned_check(regs->uregs[rd], addr);

	वापस TYPE_LDST;

 user:
	अगर (LDST_L_BIT(instr)) अणु
		अचिन्हित दीर्घ val;
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();

		get16t_unaligned_check(val, addr);
		uaccess_restore(__ua_flags);

		/* चिन्हित half-word? */
		अगर (instr & 0x40)
			val = (चिन्हित दीर्घ)((चिन्हित लघु) val);

		regs->uregs[rd] = val;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
		put16t_unaligned_check(regs->uregs[rd], addr);
		uaccess_restore(__ua_flags);
	पूर्ण

	वापस TYPE_LDST;

 fault:
	वापस TYPE_FAULT;
पूर्ण

अटल पूर्णांक
करो_alignment_ldrdstrd(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक rd = RD_BITS(instr);
	अचिन्हित पूर्णांक rd2;
	पूर्णांक load;

	अगर ((instr & 0xfe000000) == 0xe8000000) अणु
		/* ARMv7 Thumb-2 32-bit LDRD/STRD */
		rd2 = (instr >> 8) & 0xf;
		load = !!(LDST_L_BIT(instr));
	पूर्ण अन्यथा अगर (((rd & 1) == 1) || (rd == 14))
		जाओ bad;
	अन्यथा अणु
		load = ((instr & 0xf0) == 0xd0);
		rd2 = rd + 1;
	पूर्ण

	ai_dword += 1;

	अगर (user_mode(regs))
		जाओ user;

	अगर (load) अणु
		अचिन्हित दीर्घ val;
		get32_unaligned_check(val, addr);
		regs->uregs[rd] = val;
		get32_unaligned_check(val, addr + 4);
		regs->uregs[rd2] = val;
	पूर्ण अन्यथा अणु
		put32_unaligned_check(regs->uregs[rd], addr);
		put32_unaligned_check(regs->uregs[rd2], addr + 4);
	पूर्ण

	वापस TYPE_LDST;

 user:
	अगर (load) अणु
		अचिन्हित दीर्घ val, val2;
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();

		get32t_unaligned_check(val, addr);
		get32t_unaligned_check(val2, addr + 4);

		uaccess_restore(__ua_flags);

		regs->uregs[rd] = val;
		regs->uregs[rd2] = val2;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
		put32t_unaligned_check(regs->uregs[rd], addr);
		put32t_unaligned_check(regs->uregs[rd2], addr + 4);
		uaccess_restore(__ua_flags);
	पूर्ण

	वापस TYPE_LDST;
 bad:
	वापस TYPE_ERROR;
 fault:
	वापस TYPE_FAULT;
पूर्ण

अटल पूर्णांक
करो_alignment_ldrstr(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक rd = RD_BITS(instr);

	ai_word += 1;

	अगर ((!LDST_P_BIT(instr) && LDST_W_BIT(instr)) || user_mode(regs))
		जाओ trans;

	अगर (LDST_L_BIT(instr)) अणु
		अचिन्हित पूर्णांक val;
		get32_unaligned_check(val, addr);
		regs->uregs[rd] = val;
	पूर्ण अन्यथा
		put32_unaligned_check(regs->uregs[rd], addr);
	वापस TYPE_LDST;

 trans:
	अगर (LDST_L_BIT(instr)) अणु
		अचिन्हित पूर्णांक val;
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
		get32t_unaligned_check(val, addr);
		uaccess_restore(__ua_flags);
		regs->uregs[rd] = val;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
		put32t_unaligned_check(regs->uregs[rd], addr);
		uaccess_restore(__ua_flags);
	पूर्ण
	वापस TYPE_LDST;

 fault:
	वापस TYPE_FAULT;
पूर्ण

/*
 * LDM/STM alignment handler.
 *
 * There are 4 variants of this inकाष्ठाion:
 *
 * B = rn poपूर्णांकer beक्रमe inकाष्ठाion, A = rn poपूर्णांकer after inकाष्ठाion
 *              ------ increasing address ----->
 *	        |    | r0 | r1 | ... | rx |    |
 * PU = 01             B                    A
 * PU = 11        B                    A
 * PU = 00        A                    B
 * PU = 10             A                    B
 */
अटल पूर्णांक
करो_alignment_ldmsपंचांग(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक rd, rn, correction, nr_regs, regbits;
	अचिन्हित दीर्घ eaddr, newaddr;

	अगर (LDM_S_BIT(instr))
		जाओ bad;

	correction = 4; /* processor implementation defined */
	regs->ARM_pc += correction;

	ai_multi += 1;

	/* count the number of रेजिस्टरs in the mask to be transferred */
	nr_regs = hweight16(REGMASK_BITS(instr)) * 4;

	rn = RN_BITS(instr);
	newaddr = eaddr = regs->uregs[rn];

	अगर (!LDST_U_BIT(instr))
		nr_regs = -nr_regs;
	newaddr += nr_regs;
	अगर (!LDST_U_BIT(instr))
		eaddr = newaddr;

	अगर (LDST_P_EQ_U(instr))	/* U = P */
		eaddr += 4;

	/*
	 * For alignment faults on the ARM922T/ARM920T the MMU  makes
	 * the FSR (and hence addr) equal to the updated base address
	 * of the multiple access rather than the restored value.
	 * Switch this message off अगर we've got a ARM92[02], otherwise
	 * [ls]dm alignment faults are noisy!
	 */
#अगर !(defined CONFIG_CPU_ARM922T)  && !(defined CONFIG_CPU_ARM920T)
	/*
	 * This is a "hint" - we alपढ़ोy have eaddr worked out by the
	 * processor क्रम us.
	 */
	अगर (addr != eaddr) अणु
		pr_err("LDMSTM: PC = %08lx, instr = %08x, "
			"addr = %08lx, eaddr = %08lx\n",
			 inकाष्ठाion_poपूर्णांकer(regs), instr, addr, eaddr);
		show_regs(regs);
	पूर्ण
#पूर्ण_अगर

	अगर (user_mode(regs)) अणु
		अचिन्हित पूर्णांक __ua_flags = uaccess_save_and_enable();
		क्रम (regbits = REGMASK_BITS(instr), rd = 0; regbits;
		     regbits >>= 1, rd += 1)
			अगर (regbits & 1) अणु
				अगर (LDST_L_BIT(instr)) अणु
					अचिन्हित पूर्णांक val;
					get32t_unaligned_check(val, eaddr);
					regs->uregs[rd] = val;
				पूर्ण अन्यथा
					put32t_unaligned_check(regs->uregs[rd], eaddr);
				eaddr += 4;
			पूर्ण
		uaccess_restore(__ua_flags);
	पूर्ण अन्यथा अणु
		क्रम (regbits = REGMASK_BITS(instr), rd = 0; regbits;
		     regbits >>= 1, rd += 1)
			अगर (regbits & 1) अणु
				अगर (LDST_L_BIT(instr)) अणु
					अचिन्हित पूर्णांक val;
					get32_unaligned_check(val, eaddr);
					regs->uregs[rd] = val;
				पूर्ण अन्यथा
					put32_unaligned_check(regs->uregs[rd], eaddr);
				eaddr += 4;
			पूर्ण
	पूर्ण

	अगर (LDST_W_BIT(instr))
		regs->uregs[rn] = newaddr;
	अगर (!LDST_L_BIT(instr) || !(REGMASK_BITS(instr) & (1 << 15)))
		regs->ARM_pc -= correction;
	वापस TYPE_DONE;

fault:
	regs->ARM_pc -= correction;
	वापस TYPE_FAULT;

bad:
	pr_err("Alignment trap: not handling ldm with s-bit set\n");
	वापस TYPE_ERROR;
पूर्ण

/*
 * Convert Thumb ld/st inकाष्ठाion क्रमms to equivalent ARM inकाष्ठाions so
 * we can reuse ARM userland alignment fault fixups क्रम Thumb.
 *
 * This implementation was initially based on the algorithm found in
 * gdb/sim/arm/thumbemu.c. It is basically just a code reduction of same
 * to convert only Thumb ld/st inकाष्ठाion क्रमms to equivalent ARM क्रमms.
 *
 * NOTES:
 * 1. Comments below refer to ARM ARM DDI0100E Thumb Inकाष्ठाion sections.
 * 2. If क्रम some reason we're passed an non-ld/st Thumb inकाष्ठाion to
 *    decode, we वापस 0xdeadc0de. This should never happen under normal
 *    circumstances but अगर it करोes, we've got other problems to deal with
 *    अन्यथाwhere and we obviously can't fix those problems here.
 */

अटल अचिन्हित दीर्घ
thumb2arm(u16 tinstr)
अणु
	u32 L = (tinstr & (1<<11)) >> 11;

	चयन ((tinstr & 0xf800) >> 11) अणु
	/* 6.5.1 Format 1: */
	हाल 0x6000 >> 11:				/* 7.1.52 STR(1) */
	हाल 0x6800 >> 11:				/* 7.1.26 LDR(1) */
	हाल 0x7000 >> 11:				/* 7.1.55 STRB(1) */
	हाल 0x7800 >> 11:				/* 7.1.30 LDRB(1) */
		वापस 0xe5800000 |
			((tinstr & (1<<12)) << (22-12)) |	/* fixup */
			(L<<20) |				/* L==1? */
			((tinstr & (7<<0)) << (12-0)) |		/* Rd */
			((tinstr & (7<<3)) << (16-3)) |		/* Rn */
			((tinstr & (31<<6)) >>			/* immed_5 */
				(6 - ((tinstr & (1<<12)) ? 0 : 2)));
	हाल 0x8000 >> 11:				/* 7.1.57 STRH(1) */
	हाल 0x8800 >> 11:				/* 7.1.32 LDRH(1) */
		वापस 0xe1c000b0 |
			(L<<20) |				/* L==1? */
			((tinstr & (7<<0)) << (12-0)) |		/* Rd */
			((tinstr & (7<<3)) << (16-3)) |		/* Rn */
			((tinstr & (7<<6)) >> (6-1)) |	 /* immed_5[2:0] */
			((tinstr & (3<<9)) >> (9-8));	 /* immed_5[4:3] */

	/* 6.5.1 Format 2: */
	हाल 0x5000 >> 11:
	हाल 0x5800 >> 11:
		अणु
			अटल स्थिर u32 subset[8] = अणु
				0xe7800000,		/* 7.1.53 STR(2) */
				0xe18000b0,		/* 7.1.58 STRH(2) */
				0xe7c00000,		/* 7.1.56 STRB(2) */
				0xe19000d0,		/* 7.1.34 LDRSB */
				0xe7900000,		/* 7.1.27 LDR(2) */
				0xe19000b0,		/* 7.1.33 LDRH(2) */
				0xe7d00000,		/* 7.1.31 LDRB(2) */
				0xe19000f0		/* 7.1.35 LDRSH */
			पूर्ण;
			वापस subset[(tinstr & (7<<9)) >> 9] |
			    ((tinstr & (7<<0)) << (12-0)) |	/* Rd */
			    ((tinstr & (7<<3)) << (16-3)) |	/* Rn */
			    ((tinstr & (7<<6)) >> (6-0));	/* Rm */
		पूर्ण

	/* 6.5.1 Format 3: */
	हाल 0x4800 >> 11:				/* 7.1.28 LDR(3) */
		/* NOTE: This हाल is not technically possible. We're
		 *	 loading 32-bit memory data via PC relative
		 *	 addressing mode. So we can and should eliminate
		 *	 this हाल. But I'll leave it here क्रम now.
		 */
		वापस 0xe59f0000 |
		    ((tinstr & (7<<8)) << (12-8)) |		/* Rd */
		    ((tinstr & 255) << (2-0));			/* immed_8 */

	/* 6.5.1 Format 4: */
	हाल 0x9000 >> 11:				/* 7.1.54 STR(3) */
	हाल 0x9800 >> 11:				/* 7.1.29 LDR(4) */
		वापस 0xe58d0000 |
			(L<<20) |				/* L==1? */
			((tinstr & (7<<8)) << (12-8)) |		/* Rd */
			((tinstr & 255) << 2);			/* immed_8 */

	/* 6.6.1 Format 1: */
	हाल 0xc000 >> 11:				/* 7.1.51 STMIA */
	हाल 0xc800 >> 11:				/* 7.1.25 LDMIA */
		अणु
			u32 Rn = (tinstr & (7<<8)) >> 8;
			u32 W = ((L<<Rn) & (tinstr&255)) ? 0 : 1<<21;

			वापस 0xe8800000 | W | (L<<20) | (Rn<<16) |
				(tinstr&255);
		पूर्ण

	/* 6.6.1 Format 2: */
	हाल 0xb000 >> 11:				/* 7.1.48 PUSH */
	हाल 0xb800 >> 11:				/* 7.1.47 POP */
		अगर ((tinstr & (3 << 9)) == 0x0400) अणु
			अटल स्थिर u32 subset[4] = अणु
				0xe92d0000,	/* STMDB sp!,अणुरेजिस्टरsपूर्ण */
				0xe92d4000,	/* STMDB sp!,अणुरेजिस्टरs,lrपूर्ण */
				0xe8bd0000,	/* LDMIA sp!,अणुरेजिस्टरsपूर्ण */
				0xe8bd8000	/* LDMIA sp!,अणुरेजिस्टरs,pcपूर्ण */
			पूर्ण;
			वापस subset[(L<<1) | ((tinstr & (1<<8)) >> 8)] |
			    (tinstr & 255);		/* रेजिस्टर_list */
		पूर्ण
		fallthrough;	/* क्रम illegal inकाष्ठाion हाल */

	शेष:
		वापस BAD_INSTR;
	पूर्ण
पूर्ण

/*
 * Convert Thumb-2 32 bit LDM, STM, LDRD, STRD to equivalent inकाष्ठाion
 * handlable by ARM alignment handler, also find the corresponding handler,
 * so that we can reuse ARM userland alignment fault fixups क्रम Thumb.
 *
 * @pinstr: original Thumb-2 inकाष्ठाion; वापसs new handlable inकाष्ठाion
 * @regs: रेजिस्टर context.
 * @poffset: वापस offset from faulted addr क्रम later ग_लिखोback
 *
 * NOTES:
 * 1. Comments below refer to ARMv7 DDI0406A Thumb Inकाष्ठाion sections.
 * 2. Register name Rt from ARMv7 is same as Rd from ARMv6 (Rd is Rt)
 */
अटल व्योम *
करो_alignment_t32_to_handler(u32 *pinstr, काष्ठा pt_regs *regs,
			    जोड़ offset_जोड़ *poffset)
अणु
	u32 instr = *pinstr;
	u16 tinst1 = (instr >> 16) & 0xffff;
	u16 tinst2 = instr & 0xffff;

	चयन (tinst1 & 0xffe0) अणु
	/* A6.3.5 Load/Store multiple */
	हाल 0xe880:		/* STM/STMIA/STMEA,LDM/LDMIA, PUSH/POP T2 */
	हाल 0xe8a0:		/* ...above ग_लिखोback version */
	हाल 0xe900:		/* STMDB/STMFD, LDMDB/LDMEA */
	हाल 0xe920:		/* ...above ग_लिखोback version */
		/* no need offset decision since handler calculates it */
		वापस करो_alignment_ldmsपंचांग;

	हाल 0xf840:		/* POP/PUSH T3 (single रेजिस्टर) */
		अगर (RN_BITS(instr) == 13 && (tinst2 & 0x09ff) == 0x0904) अणु
			u32 L = !!(LDST_L_BIT(instr));
			स्थिर u32 subset[2] = अणु
				0xe92d0000,	/* STMDB sp!,अणुरेजिस्टरsपूर्ण */
				0xe8bd0000,	/* LDMIA sp!,अणुरेजिस्टरsपूर्ण */
			पूर्ण;
			*pinstr = subset[L] | (1<<RD_BITS(instr));
			वापस करो_alignment_ldmsपंचांग;
		पूर्ण
		/* Else fall through क्रम illegal inकाष्ठाion हाल */
		अवरोध;

	/* A6.3.6 Load/store द्विगुन, STRD/LDRD(immed, lit, reg) */
	हाल 0xe860:
	हाल 0xe960:
	हाल 0xe8e0:
	हाल 0xe9e0:
		poffset->un = (tinst2 & 0xff) << 2;
		fallthrough;

	हाल 0xe940:
	हाल 0xe9c0:
		वापस करो_alignment_ldrdstrd;

	/*
	 * No need to handle load/store inकाष्ठाions up to word size
	 * since ARMv6 and later CPUs can perक्रमm unaligned accesses.
	 */
	शेष:
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक alignment_get_arm(काष्ठा pt_regs *regs, u32 *ip, u32 *inst)
अणु
	u32 instr = 0;
	पूर्णांक fault;

	अगर (user_mode(regs))
		fault = get_user(instr, ip);
	अन्यथा
		fault = get_kernel_nofault(instr, ip);

	*inst = __mem_to_opcode_arm(instr);

	वापस fault;
पूर्ण

अटल पूर्णांक alignment_get_thumb(काष्ठा pt_regs *regs, u16 *ip, u16 *inst)
अणु
	u16 instr = 0;
	पूर्णांक fault;

	अगर (user_mode(regs))
		fault = get_user(instr, ip);
	अन्यथा
		fault = get_kernel_nofault(instr, ip);

	*inst = __mem_to_opcode_thumb16(instr);

	वापस fault;
पूर्ण

अटल पूर्णांक
करो_alignment(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	जोड़ offset_जोड़ offset;
	अचिन्हित दीर्घ instrptr;
	पूर्णांक (*handler)(अचिन्हित दीर्घ addr, u32 instr, काष्ठा pt_regs *regs);
	अचिन्हित पूर्णांक type;
	u32 instr = 0;
	u16 tinstr = 0;
	पूर्णांक isize = 4;
	पूर्णांक thumb2_32b = 0;
	पूर्णांक fault;

	अगर (पूर्णांकerrupts_enabled(regs))
		local_irq_enable();

	instrptr = inकाष्ठाion_poपूर्णांकer(regs);

	अगर (thumb_mode(regs)) अणु
		u16 *ptr = (u16 *)(instrptr & ~1);

		fault = alignment_get_thumb(regs, ptr, &tinstr);
		अगर (!fault) अणु
			अगर (cpu_architecture() >= CPU_ARCH_ARMv7 &&
			    IS_T32(tinstr)) अणु
				/* Thumb-2 32-bit */
				u16 tinst2;
				fault = alignment_get_thumb(regs, ptr + 1, &tinst2);
				instr = __opcode_thumb32_compose(tinstr, tinst2);
				thumb2_32b = 1;
			पूर्ण अन्यथा अणु
				isize = 2;
				instr = thumb2arm(tinstr);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		fault = alignment_get_arm(regs, (व्योम *)instrptr, &instr);
	पूर्ण

	अगर (fault) अणु
		type = TYPE_FAULT;
		जाओ bad_or_fault;
	पूर्ण

	अगर (user_mode(regs))
		जाओ user;

	ai_sys += 1;
	ai_sys_last_pc = (व्योम *)inकाष्ठाion_poपूर्णांकer(regs);

 fixup:

	regs->ARM_pc += isize;

	चयन (CODING_BITS(instr)) अणु
	हाल 0x00000000:	/* 3.13.4 load/store inकाष्ठाion extensions */
		अगर (LDSTHD_I_BIT(instr))
			offset.un = (instr & 0xf00) >> 4 | (instr & 15);
		अन्यथा
			offset.un = regs->uregs[RM_BITS(instr)];

		अगर ((instr & 0x000000f0) == 0x000000b0 || /* LDRH, STRH */
		    (instr & 0x001000f0) == 0x001000f0)   /* LDRSH */
			handler = करो_alignment_ldrhstrh;
		अन्यथा अगर ((instr & 0x001000f0) == 0x000000d0 || /* LDRD */
			 (instr & 0x001000f0) == 0x000000f0)   /* STRD */
			handler = करो_alignment_ldrdstrd;
		अन्यथा अगर ((instr & 0x01f00ff0) == 0x01000090) /* SWP */
			जाओ swp;
		अन्यथा
			जाओ bad;
		अवरोध;

	हाल 0x04000000:	/* ldr or str immediate */
		अगर (COND_BITS(instr) == 0xf0000000) /* NEON VLDn, VSTn */
			जाओ bad;
		offset.un = OFFSET_BITS(instr);
		handler = करो_alignment_ldrstr;
		अवरोध;

	हाल 0x06000000:	/* ldr or str रेजिस्टर */
		offset.un = regs->uregs[RM_BITS(instr)];

		अगर (IS_SHIFT(instr)) अणु
			अचिन्हित पूर्णांक shअगरtval = SHIFT_BITS(instr);

			चयन(SHIFT_TYPE(instr)) अणु
			हाल SHIFT_LSL:
				offset.un <<= shअगरtval;
				अवरोध;

			हाल SHIFT_LSR:
				offset.un >>= shअगरtval;
				अवरोध;

			हाल SHIFT_ASR:
				offset.sn >>= shअगरtval;
				अवरोध;

			हाल SHIFT_RORRRX:
				अगर (shअगरtval == 0) अणु
					offset.un >>= 1;
					अगर (regs->ARM_cpsr & PSR_C_BIT)
						offset.un |= 1 << 31;
				पूर्ण अन्यथा
					offset.un = offset.un >> shअगरtval |
							  offset.un << (32 - shअगरtval);
				अवरोध;
			पूर्ण
		पूर्ण
		handler = करो_alignment_ldrstr;
		अवरोध;

	हाल 0x08000000:	/* ldm or sपंचांग, or thumb-2 32bit inकाष्ठाion */
		अगर (thumb2_32b) अणु
			offset.un = 0;
			handler = करो_alignment_t32_to_handler(&instr, regs, &offset);
		पूर्ण अन्यथा अणु
			offset.un = 0;
			handler = करो_alignment_ldmsपंचांग;
		पूर्ण
		अवरोध;

	शेष:
		जाओ bad;
	पूर्ण

	अगर (!handler)
		जाओ bad;
	type = handler(addr, instr, regs);

	अगर (type == TYPE_ERROR || type == TYPE_FAULT) अणु
		regs->ARM_pc -= isize;
		जाओ bad_or_fault;
	पूर्ण

	अगर (type == TYPE_LDST)
		करो_alignment_finish_ldst(addr, instr, regs, offset);

	वापस 0;

 bad_or_fault:
	अगर (type == TYPE_ERROR)
		जाओ bad;
	/*
	 * We got a fault - fix it up, or die.
	 */
	करो_bad_area(addr, fsr, regs);
	वापस 0;

 swp:
	pr_err("Alignment trap: not handling swp instruction\n");

 bad:
	/*
	 * Oops, we didn't handle the inकाष्ठाion.
	 */
	pr_err("Alignment trap: not handling instruction "
		"%0*x at [<%08lx>]\n",
		isize << 1,
		isize == 2 ? tinstr : instr, instrptr);
	ai_skipped += 1;
	वापस 1;

 user:
	ai_user += 1;

	अगर (ai_usermode & UM_WARN)
		prपूर्णांकk("Alignment trap: %s (%d) PC=0x%08lx Instr=0x%0*x "
		       "Address=0x%08lx FSR 0x%03x\n", current->comm,
			task_pid_nr(current), instrptr,
			isize << 1,
			isize == 2 ? tinstr : instr,
		        addr, fsr);

	अगर (ai_usermode & UM_FIXUP)
		जाओ fixup;

	अगर (ai_usermode & UM_SIGNAL) अणु
		क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *)addr);
	पूर्ण अन्यथा अणु
		/*
		 * We're about to disable the alignment trap and वापस to
		 * user space.  But अगर an पूर्णांकerrupt occurs beक्रमe actually
		 * reaching user space, then the IRQ vector entry code will
		 * notice that we were still in kernel space and thereक्रमe
		 * the alignment trap won't be re-enabled in that हाल as it
		 * is presumed to be always on from kernel space.
		 * Let's prevent that race by disabling पूर्णांकerrupts here (they
		 * are disabled on the way back to user space anyway in
		 * entry-common.S) and disable the alignment trap only अगर
		 * there is no work pending क्रम this thपढ़ो.
		 */
		raw_local_irq_disable();
		अगर (!(current_thपढ़ो_info()->flags & _TIF_WORK_MASK))
			set_cr(cr_no_alignment);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init noalign_setup(अक्षर *__unused)
अणु
	set_cr(__clear_cr(CR_A));
	वापस 1;
पूर्ण
__setup("noalign", noalign_setup);

/*
 * This needs to be करोne after sysctl_init, otherwise sys/ will be
 * overwritten.  Actually, this shouldn't be in sys/ at all since
 * it isn't a sysctl, and it doesn't contain sysctl inक्रमmation.
 * We now locate it in /proc/cpu/alignment instead.
 */
अटल पूर्णांक __init alignment_init(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *res;

	res = proc_create("cpu/alignment", S_IWUSR | S_IRUGO, शून्य,
			  &alignment_proc_ops);
	अगर (!res)
		वापस -ENOMEM;
#पूर्ण_अगर

	अगर (cpu_is_v6_unaligned()) अणु
		set_cr(__clear_cr(CR_A));
		ai_usermode = safe_usermode(ai_usermode, false);
	पूर्ण

	cr_no_alignment = get_cr() & ~CR_A;

	hook_fault_code(FAULT_CODE_ALIGNMENT, करो_alignment, SIGBUS, BUS_ADRALN,
			"alignment exception");

	/*
	 * ARMv6K and ARMv7 use fault status 3 (0b00011) as Access Flag section
	 * fault, not as alignment error.
	 *
	 * TODO: handle ARMv6K properly. Runसमय check क्रम 'K' extension is
	 * needed.
	 */
	अगर (cpu_architecture() <= CPU_ARCH_ARMv6) अणु
		hook_fault_code(3, करो_alignment, SIGBUS, BUS_ADRALN,
				"alignment exception");
	पूर्ण

	वापस 0;
पूर्ण

fs_initcall(alignment_init);
