<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#अगर_अघोषित __ASM_MIPS_R2_TO_R6_EMUL_H
#घोषणा __ASM_MIPS_R2_TO_R6_EMUL_H

काष्ठा mips_r2_emulator_stats अणु
	u64 movs;
	u64 hilo;
	u64 muls;
	u64 भागs;
	u64 dsps;
	u64 bops;
	u64 traps;
	u64 fpus;
	u64 loads;
	u64 stores;
	u64 llsc;
	u64 dsemul;
पूर्ण;

काष्ठा mips_r2br_emulator_stats अणु
	u64 jrs;
	u64 bltzl;
	u64 bgezl;
	u64 bltzll;
	u64 bgezll;
	u64 bltzall;
	u64 bgezall;
	u64 bltzal;
	u64 bgezal;
	u64 beql;
	u64 bnel;
	u64 blezl;
	u64 bgtzl;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा MIPS_R2_STATS(M)						\
करो अणु									\
	u32 nir;							\
	पूर्णांक err;							\
									\
	preempt_disable();						\
	__this_cpu_inc(mipsr2emustats.M);				\
	err = __get_user(nir, (u32 __user *)regs->cp0_epc);		\
	अगर (!err) अणु							\
		अगर (nir == BREAK_MATH(0))				\
			__this_cpu_inc(mipsr2bdemustats.M);		\
	पूर्ण								\
	preempt_enable();						\
पूर्ण जबतक (0)

#घोषणा MIPS_R2BR_STATS(M)					\
करो अणु								\
	preempt_disable();					\
	__this_cpu_inc(mipsr2bremustats.M);			\
	preempt_enable();					\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा MIPS_R2_STATS(M)          करो अणु पूर्ण जबतक (0)
#घोषणा MIPS_R2BR_STATS(M)        करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

काष्ठा r2_decoder_table अणु
	u32     mask;
	u32     code;
	पूर्णांक     (*func)(काष्ठा pt_regs *regs, u32 inst);
पूर्ण;


बाह्य व्योम करो_trap_or_bp(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक code, पूर्णांक si_code,
			  स्थिर अक्षर *str);

#अगर_अघोषित CONFIG_MIPSR2_TO_R6_EMULATOR
अटल पूर्णांक mipsr2_emulation;
अटल अंतरभूत पूर्णांक mipsr2_decoder(काष्ठा pt_regs *regs, u32 inst,
				 अचिन्हित दीर्घ *fcr31)
अणु
	वापस 0;
पूर्ण;
#अन्यथा
/* MIPS R2 Emulator ON/OFF */
बाह्य पूर्णांक mipsr2_emulation;
बाह्य पूर्णांक mipsr2_decoder(काष्ठा pt_regs *regs, u32 inst,
			  अचिन्हित दीर्घ *fcr31);
#पूर्ण_अगर /* CONFIG_MIPSR2_TO_R6_EMULATOR */

#घोषणा NO_R6EMU	(cpu_has_mips_r6 && !mipsr2_emulation)

#पूर्ण_अगर /* __ASM_MIPS_R2_TO_R6_EMUL_H */
