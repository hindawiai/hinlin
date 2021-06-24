<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 * Author: Leonid Yegoshin <Leonid.Yegoshin@imgtec.com>
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 *
 *      MIPS R2 user space inकाष्ठाion emulator क्रम MIPS R6
 *
 */
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/अवरोध.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/mips-r2-to-r6-emul.h>
#समावेश <यंत्र/local.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा ADDIU	"daddiu "
#घोषणा INS	"dins "
#घोषणा EXT	"dext "
#अन्यथा
#घोषणा ADDIU	"addiu "
#घोषणा INS	"ins "
#घोषणा EXT	"ext "
#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा SB	"sb "
#घोषणा LB	"lb "
#घोषणा LL	"ll "
#घोषणा SC	"sc "

#अगर_घोषित CONFIG_DEBUG_FS
अटल DEFINE_PER_CPU(काष्ठा mips_r2_emulator_stats, mipsr2emustats);
अटल DEFINE_PER_CPU(काष्ठा mips_r2_emulator_stats, mipsr2bdemustats);
अटल DEFINE_PER_CPU(काष्ठा mips_r2br_emulator_stats, mipsr2bremustats);
#पूर्ण_अगर

बाह्य स्थिर अचिन्हित पूर्णांक fpucondbit[8];

#घोषणा MIPS_R2_EMUL_TOTAL_PASS	10

पूर्णांक mipsr2_emulation = 0;

अटल पूर्णांक __init mipsr2emu_enable(अक्षर *s)
अणु
	mipsr2_emulation = 1;

	pr_info("MIPS R2-to-R6 Emulator Enabled!");

	वापस 1;
पूर्ण
__setup("mipsr2emu", mipsr2emu_enable);

/**
 * mipsr6_emul - Emulate some frequent R2/R5/R6 inकाष्ठाions in delay slot
 * क्रम perक्रमmance instead of the traditional way of using a stack trampoline
 * which is rather slow.
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 */
अटल अंतरभूत पूर्णांक mipsr6_emul(काष्ठा pt_regs *regs, u32 ir)
अणु
	चयन (MIPSInst_OPCODE(ir)) अणु
	हाल addiu_op:
		अगर (MIPSInst_RT(ir))
			regs->regs[MIPSInst_RT(ir)] =
				(s32)regs->regs[MIPSInst_RS(ir)] +
				(s32)MIPSInst_SIMM(ir);
		वापस 0;
	हाल daddiu_op:
		अगर (IS_ENABLED(CONFIG_32BIT))
			अवरोध;

		अगर (MIPSInst_RT(ir))
			regs->regs[MIPSInst_RT(ir)] =
				(s64)regs->regs[MIPSInst_RS(ir)] +
				(s64)MIPSInst_SIMM(ir);
		वापस 0;
	हाल lwc1_op:
	हाल swc1_op:
	हाल cop1_op:
	हाल cop1x_op:
		/* FPU inकाष्ठाions in delay slot */
		वापस -संक_भ_त्रुटि;
	हाल spec_op:
		चयन (MIPSInst_FUNC(ir)) अणु
		हाल or_op:
			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					regs->regs[MIPSInst_RS(ir)] |
					regs->regs[MIPSInst_RT(ir)];
			वापस 0;
		हाल sll_op:
			अगर (MIPSInst_RS(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s32)(((u32)regs->regs[MIPSInst_RT(ir)]) <<
						MIPSInst_FD(ir));
			वापस 0;
		हाल srl_op:
			अगर (MIPSInst_RS(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s32)(((u32)regs->regs[MIPSInst_RT(ir)]) >>
						MIPSInst_FD(ir));
			वापस 0;
		हाल addu_op:
			अगर (MIPSInst_FD(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s32)((u32)regs->regs[MIPSInst_RS(ir)] +
					      (u32)regs->regs[MIPSInst_RT(ir)]);
			वापस 0;
		हाल subu_op:
			अगर (MIPSInst_FD(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s32)((u32)regs->regs[MIPSInst_RS(ir)] -
					      (u32)regs->regs[MIPSInst_RT(ir)]);
			वापस 0;
		हाल dsll_op:
			अगर (IS_ENABLED(CONFIG_32BIT) || MIPSInst_RS(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s64)(((u64)regs->regs[MIPSInst_RT(ir)]) <<
						MIPSInst_FD(ir));
			वापस 0;
		हाल dsrl_op:
			अगर (IS_ENABLED(CONFIG_32BIT) || MIPSInst_RS(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s64)(((u64)regs->regs[MIPSInst_RT(ir)]) >>
						MIPSInst_FD(ir));
			वापस 0;
		हाल daddu_op:
			अगर (IS_ENABLED(CONFIG_32BIT) || MIPSInst_FD(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(u64)regs->regs[MIPSInst_RS(ir)] +
					(u64)regs->regs[MIPSInst_RT(ir)];
			वापस 0;
		हाल dsubu_op:
			अगर (IS_ENABLED(CONFIG_32BIT) || MIPSInst_FD(ir))
				अवरोध;

			अगर (MIPSInst_RD(ir))
				regs->regs[MIPSInst_RD(ir)] =
					(s64)((u64)regs->regs[MIPSInst_RS(ir)] -
					      (u64)regs->regs[MIPSInst_RT(ir)]);
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		pr_debug("No fastpath BD emulation for instruction 0x%08x (op: %02x)\n",
			 ir, MIPSInst_OPCODE(ir));
	पूर्ण

	वापस संक_अवैध;
पूर्ण

/**
 * movf_func - Emulate a MOVF inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक movf_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u32 csr;
	u32 cond;

	csr = current->thपढ़ो.fpu.fcr31;
	cond = fpucondbit[MIPSInst_RT(ir) >> 2];

	अगर (((csr & cond) == 0) && MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(movs);

	वापस 0;
पूर्ण

/**
 * movt_func - Emulate a MOVT inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक movt_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u32 csr;
	u32 cond;

	csr = current->thपढ़ो.fpu.fcr31;
	cond = fpucondbit[MIPSInst_RT(ir) >> 2];

	अगर (((csr & cond) != 0) && MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(movs);

	वापस 0;
पूर्ण

/**
 * jr_func - Emulate a JR inकाष्ठाion.
 * @pt_regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns संक_अवैध अगर JR was in delay slot, SIGEMT अगर we
 * can't compute the EPC, SIGSEGV if we can't access the
 * userland inकाष्ठाion or 0 on success.
 */
अटल पूर्णांक jr_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ cepc, epc, nepc;
	u32 nir;

	अगर (delay_slot(regs))
		वापस संक_अवैध;

	/* EPC after the RI/JR inकाष्ठाion */
	nepc = regs->cp0_epc;
	/* Roll back to the reserved R2 JR inकाष्ठाion */
	regs->cp0_epc -= 4;
	epc = regs->cp0_epc;
	err = __compute_वापस_epc(regs);

	अगर (err < 0)
		वापस SIGEMT;


	/* Computed EPC */
	cepc = regs->cp0_epc;

	/* Get DS inकाष्ठाion */
	err = __get_user(nir, (u32 __user *)nepc);
	अगर (err)
		वापस संक_अंश;

	MIPS_R2BR_STATS(jrs);

	/* If nir == 0(NOP), then nothing अन्यथा to करो */
	अगर (nir) अणु
		/*
		 * Negative err means FPU inकाष्ठाion in BD-slot,
		 * Zero err means 'BD-slot emulation done'
		 * For anything अन्यथा we go back to trampoline emulation.
		 */
		err = mipsr6_emul(regs, nir);
		अगर (err > 0) अणु
			regs->cp0_epc = nepc;
			err = mips_dsemul(regs, nir, epc, cepc);
			अगर (err == संक_अवैध)
				err = SIGEMT;
			MIPS_R2_STATS(dsemul);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * movz_func - Emulate a MOVZ inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक movz_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	अगर (((regs->regs[MIPSInst_RT(ir)]) == 0) && MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->regs[MIPSInst_RS(ir)];
	MIPS_R2_STATS(movs);

	वापस 0;
पूर्ण

/**
 * movn_func - Emulate a MOVZ inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक movn_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	अगर (((regs->regs[MIPSInst_RT(ir)]) != 0) && MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->regs[MIPSInst_RS(ir)];
	MIPS_R2_STATS(movs);

	वापस 0;
पूर्ण

/**
 * mfhi_func - Emulate a MFHI inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mfhi_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	अगर (MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->hi;

	MIPS_R2_STATS(hilo);

	वापस 0;
पूर्ण

/**
 * mthi_func - Emulate a MTHI inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mthi_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	regs->hi = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(hilo);

	वापस 0;
पूर्ण

/**
 * mflo_func - Emulate a MFLO inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mflo_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	अगर (MIPSInst_RD(ir))
		regs->regs[MIPSInst_RD(ir)] = regs->lo;

	MIPS_R2_STATS(hilo);

	वापस 0;
पूर्ण

/**
 * mtlo_func - Emulate a MTLO inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mtlo_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	regs->lo = regs->regs[MIPSInst_RS(ir)];

	MIPS_R2_STATS(hilo);

	वापस 0;
पूर्ण

/**
 * mult_func - Emulate a MULT inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mult_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 res;
	s32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (s64)rt * (s64)rs;

	rs = res;
	regs->lo = (s64)rs;
	rt = res >> 32;
	res = (s64)rt;
	regs->hi = res;

	MIPS_R2_STATS(muls);

	वापस 0;
पूर्ण

/**
 * multu_func - Emulate a MULTU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक multu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (u64)rt * (u64)rs;
	rt = res;
	regs->lo = (s64)(s32)rt;
	regs->hi = (s64)(s32)(res >> 32);

	MIPS_R2_STATS(muls);

	वापस 0;
पूर्ण

/**
 * भाग_func - Emulate a DIV inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक भाग_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];

	regs->lo = (s64)(rs / rt);
	regs->hi = (s64)(rs % rt);

	MIPS_R2_STATS(भागs);

	वापस 0;
पूर्ण

/**
 * भागu_func - Emulate a DIVU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक भागu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];

	regs->lo = (s64)(rs / rt);
	regs->hi = (s64)(rs % rt);

	MIPS_R2_STATS(भागs);

	वापस 0;
पूर्ण

/**
 * dmult_func - Emulate a DMULT inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 on success or संक_अवैध क्रम 32-bit kernels.
 */
अटल पूर्णांक dmult_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 res;
	s64 rt, rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = rt * rs;

	regs->lo = res;
	__यंत्र__ __अस्थिर__(
		"dmuh %0, %1, %2\t\n"
		: "=r"(res)
		: "r"(rt), "r"(rs));

	regs->hi = res;

	MIPS_R2_STATS(muls);

	वापस 0;
पूर्ण

/**
 * dmultu_func - Emulate a DMULTU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 on success or संक_अवैध क्रम 32-bit kernels.
 */
अटल पूर्णांक dmultu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u64 rt, rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = rt * rs;

	regs->lo = res;
	__यंत्र__ __अस्थिर__(
		"dmuhu %0, %1, %2\t\n"
		: "=r"(res)
		: "r"(rt), "r"(rs));

	regs->hi = res;

	MIPS_R2_STATS(muls);

	वापस 0;
पूर्ण

/**
 * dभाग_func - Emulate a DDIV inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 on success or संक_अवैध क्रम 32-bit kernels.
 */
अटल पूर्णांक dभाग_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 rt, rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];

	regs->lo = rs / rt;
	regs->hi = rs % rt;

	MIPS_R2_STATS(भागs);

	वापस 0;
पूर्ण

/**
 * dभागu_func - Emulate a DDIVU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 on success or संक_अवैध क्रम 32-bit kernels.
 */
अटल पूर्णांक dभागu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 rt, rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];

	regs->lo = rs / rt;
	regs->hi = rs % rt;

	MIPS_R2_STATS(भागs);

	वापस 0;
पूर्ण

/* R6 हटाओd inकाष्ठाions क्रम the SPECIAL opcode */
अटल स्थिर काष्ठा r2_decoder_table spec_op_table[] = अणु
	अणु 0xfc1ff83f, 0x00000008, jr_func पूर्ण,
	अणु 0xfc00ffff, 0x00000018, mult_func पूर्ण,
	अणु 0xfc00ffff, 0x00000019, multu_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001c, dmult_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001d, dmultu_func पूर्ण,
	अणु 0xffff07ff, 0x00000010, mfhi_func पूर्ण,
	अणु 0xfc1fffff, 0x00000011, mthi_func पूर्ण,
	अणु 0xffff07ff, 0x00000012, mflo_func पूर्ण,
	अणु 0xfc1fffff, 0x00000013, mtlo_func पूर्ण,
	अणु 0xfc0307ff, 0x00000001, movf_func पूर्ण,
	अणु 0xfc0307ff, 0x00010001, movt_func पूर्ण,
	अणु 0xfc0007ff, 0x0000000a, movz_func पूर्ण,
	अणु 0xfc0007ff, 0x0000000b, movn_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001a, भाग_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001b, भागu_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001e, dभाग_func पूर्ण,
	अणु 0xfc00ffff, 0x0000001f, dभागu_func पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * madd_func - Emulate a MADD inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक madd_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 res;
	s32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (s64)rt * (s64)rs;
	rt = regs->hi;
	rs = regs->lo;
	res += ((((s64)rt) << 32) | (u32)rs);

	rt = res;
	regs->lo = (s64)rt;
	rs = res >> 32;
	regs->hi = (s64)rs;

	MIPS_R2_STATS(dsps);

	वापस 0;
पूर्ण

/**
 * maddu_func - Emulate a MADDU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक maddu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (u64)rt * (u64)rs;
	rt = regs->hi;
	rs = regs->lo;
	res += ((((s64)rt) << 32) | (u32)rs);

	rt = res;
	regs->lo = (s64)(s32)rt;
	rs = res >> 32;
	regs->hi = (s64)(s32)rs;

	MIPS_R2_STATS(dsps);

	वापस 0;
पूर्ण

/**
 * msub_func - Emulate a MSUB inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक msub_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 res;
	s32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (s64)rt * (s64)rs;
	rt = regs->hi;
	rs = regs->lo;
	res = ((((s64)rt) << 32) | (u32)rs) - res;

	rt = res;
	regs->lo = (s64)rt;
	rs = res >> 32;
	regs->hi = (s64)rs;

	MIPS_R2_STATS(dsps);

	वापस 0;
पूर्ण

/**
 * msubu_func - Emulate a MSUBU inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक msubu_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u32 rt, rs;

	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (u64)rt * (u64)rs;
	rt = regs->hi;
	rs = regs->lo;
	res = ((((s64)rt) << 32) | (u32)rs) - res;

	rt = res;
	regs->lo = (s64)(s32)rt;
	rs = res >> 32;
	regs->hi = (s64)(s32)rs;

	MIPS_R2_STATS(dsps);

	वापस 0;
पूर्ण

/**
 * mul_func - Emulate a MUL inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक mul_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	s64 res;
	s32 rt, rs;

	अगर (!MIPSInst_RD(ir))
		वापस 0;
	rt = regs->regs[MIPSInst_RT(ir)];
	rs = regs->regs[MIPSInst_RS(ir)];
	res = (s64)rt * (s64)rs;

	rs = res;
	regs->regs[MIPSInst_RD(ir)] = (s64)rs;

	MIPS_R2_STATS(muls);

	वापस 0;
पूर्ण

/**
 * clz_func - Emulate a CLZ inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक clz_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u32 res;
	u32 rs;

	अगर (!MIPSInst_RD(ir))
		वापस 0;

	rs = regs->regs[MIPSInst_RS(ir)];
	__यंत्र__ __अस्थिर__("clz %0, %1" : "=r"(res) : "r"(rs));
	regs->regs[MIPSInst_RD(ir)] = res;

	MIPS_R2_STATS(bops);

	वापस 0;
पूर्ण

/**
 * clo_func - Emulate a CLO inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */

अटल पूर्णांक clo_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u32 res;
	u32 rs;

	अगर (!MIPSInst_RD(ir))
		वापस 0;

	rs = regs->regs[MIPSInst_RS(ir)];
	__यंत्र__ __अस्थिर__("clo %0, %1" : "=r"(res) : "r"(rs));
	regs->regs[MIPSInst_RD(ir)] = res;

	MIPS_R2_STATS(bops);

	वापस 0;
पूर्ण

/**
 * dclz_func - Emulate a DCLZ inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक dclz_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u64 rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	अगर (!MIPSInst_RD(ir))
		वापस 0;

	rs = regs->regs[MIPSInst_RS(ir)];
	__यंत्र__ __अस्थिर__("dclz %0, %1" : "=r"(res) : "r"(rs));
	regs->regs[MIPSInst_RD(ir)] = res;

	MIPS_R2_STATS(bops);

	वापस 0;
पूर्ण

/**
 * dclo_func - Emulate a DCLO inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @ir: Inकाष्ठाion
 *
 * Returns 0 since it always succeeds.
 */
अटल पूर्णांक dclo_func(काष्ठा pt_regs *regs, u32 ir)
अणु
	u64 res;
	u64 rs;

	अगर (IS_ENABLED(CONFIG_32BIT))
		वापस संक_अवैध;

	अगर (!MIPSInst_RD(ir))
		वापस 0;

	rs = regs->regs[MIPSInst_RS(ir)];
	__यंत्र__ __अस्थिर__("dclo %0, %1" : "=r"(res) : "r"(rs));
	regs->regs[MIPSInst_RD(ir)] = res;

	MIPS_R2_STATS(bops);

	वापस 0;
पूर्ण

/* R6 हटाओd inकाष्ठाions क्रम the SPECIAL2 opcode */
अटल स्थिर काष्ठा r2_decoder_table spec2_op_table[] = अणु
	अणु 0xfc00ffff, 0x70000000, madd_func पूर्ण,
	अणु 0xfc00ffff, 0x70000001, maddu_func पूर्ण,
	अणु 0xfc0007ff, 0x70000002, mul_func पूर्ण,
	अणु 0xfc00ffff, 0x70000004, msub_func पूर्ण,
	अणु 0xfc00ffff, 0x70000005, msubu_func पूर्ण,
	अणु 0xfc0007ff, 0x70000020, clz_func पूर्ण,
	अणु 0xfc0007ff, 0x70000021, clo_func पूर्ण,
	अणु 0xfc0007ff, 0x70000024, dclz_func पूर्ण,
	अणु 0xfc0007ff, 0x70000025, dclo_func पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक mipsr2_find_op_func(काष्ठा pt_regs *regs, u32 inst,
				      स्थिर काष्ठा r2_decoder_table *table)
अणु
	स्थिर काष्ठा r2_decoder_table *p;
	पूर्णांक err;

	क्रम (p = table; p->func; p++) अणु
		अगर ((inst & p->mask) == p->code) अणु
			err = (p->func)(regs, inst);
			वापस err;
		पूर्ण
	पूर्ण
	वापस संक_अवैध;
पूर्ण

/**
 * mipsr2_decoder: Decode and emulate a MIPS R2 inकाष्ठाion
 * @regs: Process रेजिस्टर set
 * @inst: Inकाष्ठाion to decode and emulate
 * @fcr31: Floating Poपूर्णांक Control and Status Register Cause bits वापसed
 */
पूर्णांक mipsr2_decoder(काष्ठा pt_regs *regs, u32 inst, अचिन्हित दीर्घ *fcr31)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ vaddr;
	u32 nir;
	अचिन्हित दीर्घ cpc, epc, nepc, r31, res, rs, rt;

	व्योम __user *fault_addr = शून्य;
	पूर्णांक pass = 0;

repeat:
	r31 = regs->regs[31];
	epc = regs->cp0_epc;
	err = compute_वापस_epc(regs);
	अगर (err < 0) अणु
		BUG();
		वापस SIGEMT;
	पूर्ण
	pr_debug("Emulating the 0x%08x R2 instruction @ 0x%08lx (pass=%d))\n",
		 inst, epc, pass);

	चयन (MIPSInst_OPCODE(inst)) अणु
	हाल spec_op:
		err = mipsr2_find_op_func(regs, inst, spec_op_table);
		अगर (err < 0) अणु
			/* FPU inकाष्ठाion under JR */
			regs->cp0_cause |= CAUSEF_BD;
			जाओ fpu_emul;
		पूर्ण
		अवरोध;
	हाल spec2_op:
		err = mipsr2_find_op_func(regs, inst, spec2_op_table);
		अवरोध;
	हाल bcond_op:
		rt = MIPSInst_RT(inst);
		rs = MIPSInst_RS(inst);
		चयन (rt) अणु
		हाल tgei_op:
			अगर ((दीर्घ)regs->regs[rs] >= MIPSInst_SIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TGEI");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल tgeiu_op:
			अगर (regs->regs[rs] >= MIPSInst_UIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TGEIU");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल tlti_op:
			अगर ((दीर्घ)regs->regs[rs] < MIPSInst_SIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TLTI");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल tltiu_op:
			अगर (regs->regs[rs] < MIPSInst_UIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TLTIU");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल teqi_op:
			अगर (regs->regs[rs] == MIPSInst_SIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TEQI");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल tnei_op:
			अगर (regs->regs[rs] != MIPSInst_SIMM(inst))
				करो_trap_or_bp(regs, 0, 0, "TNEI");

			MIPS_R2_STATS(traps);

			अवरोध;
		हाल bltzl_op:
		हाल bgezl_op:
		हाल bltzall_op:
		हाल bgezall_op:
			अगर (delay_slot(regs)) अणु
				err = संक_अवैध;
				अवरोध;
			पूर्ण
			regs->regs[31] = r31;
			regs->cp0_epc = epc;
			err = __compute_वापस_epc(regs);
			अगर (err < 0)
				वापस SIGEMT;
			अगर (err != BRANCH_LIKELY_TAKEN)
				अवरोध;
			cpc = regs->cp0_epc;
			nepc = epc + 4;
			err = __get_user(nir, (u32 __user *)nepc);
			अगर (err) अणु
				err = संक_अंश;
				अवरोध;
			पूर्ण
			/*
			 * This will probably be optimized away when
			 * CONFIG_DEBUG_FS is not enabled
			 */
			चयन (rt) अणु
			हाल bltzl_op:
				MIPS_R2BR_STATS(bltzl);
				अवरोध;
			हाल bgezl_op:
				MIPS_R2BR_STATS(bgezl);
				अवरोध;
			हाल bltzall_op:
				MIPS_R2BR_STATS(bltzall);
				अवरोध;
			हाल bgezall_op:
				MIPS_R2BR_STATS(bgezall);
				अवरोध;
			पूर्ण

			चयन (MIPSInst_OPCODE(nir)) अणु
			हाल cop1_op:
			हाल cop1x_op:
			हाल lwc1_op:
			हाल swc1_op:
				regs->cp0_cause |= CAUSEF_BD;
				जाओ fpu_emul;
			पूर्ण
			अगर (nir) अणु
				err = mipsr6_emul(regs, nir);
				अगर (err > 0) अणु
					err = mips_dsemul(regs, nir, epc, cpc);
					अगर (err == संक_अवैध)
						err = SIGEMT;
					MIPS_R2_STATS(dsemul);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल bltzal_op:
		हाल bgezal_op:
			अगर (delay_slot(regs)) अणु
				err = संक_अवैध;
				अवरोध;
			पूर्ण
			regs->regs[31] = r31;
			regs->cp0_epc = epc;
			err = __compute_वापस_epc(regs);
			अगर (err < 0)
				वापस SIGEMT;
			cpc = regs->cp0_epc;
			nepc = epc + 4;
			err = __get_user(nir, (u32 __user *)nepc);
			अगर (err) अणु
				err = संक_अंश;
				अवरोध;
			पूर्ण
			/*
			 * This will probably be optimized away when
			 * CONFIG_DEBUG_FS is not enabled
			 */
			चयन (rt) अणु
			हाल bltzal_op:
				MIPS_R2BR_STATS(bltzal);
				अवरोध;
			हाल bgezal_op:
				MIPS_R2BR_STATS(bgezal);
				अवरोध;
			पूर्ण

			चयन (MIPSInst_OPCODE(nir)) अणु
			हाल cop1_op:
			हाल cop1x_op:
			हाल lwc1_op:
			हाल swc1_op:
				regs->cp0_cause |= CAUSEF_BD;
				जाओ fpu_emul;
			पूर्ण
			अगर (nir) अणु
				err = mipsr6_emul(regs, nir);
				अगर (err > 0) अणु
					err = mips_dsemul(regs, nir, epc, cpc);
					अगर (err == संक_अवैध)
						err = SIGEMT;
					MIPS_R2_STATS(dsemul);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			regs->regs[31] = r31;
			regs->cp0_epc = epc;
			err = संक_अवैध;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल blezl_op:
	हाल bgtzl_op:
		/*
		 * For BLEZL and BGTZL, rt field must be set to 0. If this
		 * is not the हाल, this may be an encoding of a MIPS R6
		 * inकाष्ठाion, so वापस to CPU execution अगर this occurs
		 */
		अगर (MIPSInst_RT(inst)) अणु
			err = संक_अवैध;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल beql_op:
	हाल bnel_op:
		अगर (delay_slot(regs)) अणु
			err = संक_अवैध;
			अवरोध;
		पूर्ण
		regs->regs[31] = r31;
		regs->cp0_epc = epc;
		err = __compute_वापस_epc(regs);
		अगर (err < 0)
			वापस SIGEMT;
		अगर (err != BRANCH_LIKELY_TAKEN)
			अवरोध;
		cpc = regs->cp0_epc;
		nepc = epc + 4;
		err = __get_user(nir, (u32 __user *)nepc);
		अगर (err) अणु
			err = संक_अंश;
			अवरोध;
		पूर्ण
		/*
		 * This will probably be optimized away when
		 * CONFIG_DEBUG_FS is not enabled
		 */
		चयन (MIPSInst_OPCODE(inst)) अणु
		हाल beql_op:
			MIPS_R2BR_STATS(beql);
			अवरोध;
		हाल bnel_op:
			MIPS_R2BR_STATS(bnel);
			अवरोध;
		हाल blezl_op:
			MIPS_R2BR_STATS(blezl);
			अवरोध;
		हाल bgtzl_op:
			MIPS_R2BR_STATS(bgtzl);
			अवरोध;
		पूर्ण

		चयन (MIPSInst_OPCODE(nir)) अणु
		हाल cop1_op:
		हाल cop1x_op:
		हाल lwc1_op:
		हाल swc1_op:
			regs->cp0_cause |= CAUSEF_BD;
			जाओ fpu_emul;
		पूर्ण
		अगर (nir) अणु
			err = mipsr6_emul(regs, nir);
			अगर (err > 0) अणु
				err = mips_dsemul(regs, nir, epc, cpc);
				अगर (err == संक_अवैध)
					err = SIGEMT;
				MIPS_R2_STATS(dsemul);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल lwc1_op:
	हाल swc1_op:
	हाल cop1_op:
	हाल cop1x_op:
fpu_emul:
		regs->regs[31] = r31;
		regs->cp0_epc = epc;

		err = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 0,
					       &fault_addr);

		/*
		 * We can't allow the emulated inकाष्ठाion to leave any
		 * enabled Cause bits set in $fcr31.
		 */
		*fcr31 = res = mask_fcr31_x(current->thपढ़ो.fpu.fcr31);
		current->thपढ़ो.fpu.fcr31 &= ~res;

		/*
		 * this is a tricky issue - lose_fpu() uses LL/SC atomics
		 * अगर FPU is owned and effectively cancels user level LL/SC.
		 * So, it could be logical to करोn't restore FPU ownership here.
		 * But the sequence of multiple FPU inकाष्ठाions is much much
		 * more often than LL-FPU-SC and I prefer loop here until
		 * next scheduler cycle cancels FPU ownership
		 */
		own_fpu(1);	/* Restore FPU state. */

		अगर (err)
			current->thपढ़ो.cp0_baduaddr = (अचिन्हित दीर्घ)fault_addr;

		MIPS_R2_STATS(fpus);

		अवरोध;

	हाल lwl_op:
		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set	push\n"
			"	.set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"1:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 24, 8\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"2:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 16, 8\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"3:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 8, 8\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"4:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 0, 8\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"1:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 24, 8\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
			"2:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 16, 8\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
			"3:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 8, 8\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
			"4:"	LB	"%1, 0(%2)\n"
				INS	"%0, %1, 0, 8\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:	sll	%0, %0, 0\n"
			"10:\n"
			"	.insn\n"
			"	.section	.fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	10b\n"
			"	.previous\n"
			"	.section	__ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश));

		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = rt;

		MIPS_R2_STATS(loads);

		अवरोध;

	हाल lwr_op:
		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"       .set	push\n"
			"       .set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"1:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 0, 8\n"
				ADDIU	"%2, %2, 1\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
			"2:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 8, 8\n"
				ADDIU	"%2, %2, 1\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
			"3:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 16, 8\n"
				ADDIU	"%2, %2, 1\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
			"4:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 24, 8\n"
			"       sll	%0, %0, 0\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"1:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 0, 8\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"2:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 8, 8\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"3:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 16, 8\n"
			"       andi	%1, %2, 0x3\n"
			"       beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
			"4:"    LB	"%1, 0(%2)\n"
				INS	"%0, %1, 24, 8\n"
			"       sll	%0, %0, 0\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"10:\n"
			"	.insn\n"
			"	.section	.fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	10b\n"
			"       .previous\n"
			"	.section	__ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश));
		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = rt;

		MIPS_R2_STATS(loads);

		अवरोध;

	हाल swl_op:
		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set	push\n"
			"	.set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
				EXT	"%1, %0, 24, 8\n"
			"1:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 16, 8\n"
			"2:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 8, 8\n"
			"3:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 0, 8\n"
			"4:"	SB	"%1, 0(%2)\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
				EXT	"%1, %0, 24, 8\n"
			"1:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 16, 8\n"
			"2:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 8, 8\n"
			"3:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 0, 8\n"
			"4:"	SB	"%1, 0(%2)\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"	.insn\n"
			"       .section        .fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	9b\n"
			"	.previous\n"
			"	.section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश)
			: "memory");

		MIPS_R2_STATS(stores);

		अवरोध;

	हाल swr_op:
		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set	push\n"
			"	.set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
				EXT	"%1, %0, 0, 8\n"
			"1:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 8, 8\n"
			"2:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 16, 8\n"
			"3:"	SB	"%1, 0(%2)\n"
				ADDIU	"%2, %2, 1\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				EXT	"%1, %0, 24, 8\n"
			"4:"	SB	"%1, 0(%2)\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
				EXT	"%1, %0, 0, 8\n"
			"1:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 8, 8\n"
			"2:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 16, 8\n"
			"3:"	SB	"%1, 0(%2)\n"
			"	andi	%1, %2, 0x3\n"
			"	beq	$0, %1, 9f\n"
				ADDIU	"%2, %2, -1\n"
				EXT	"%1, %0, 24, 8\n"
			"4:"	SB	"%1, 0(%2)\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"	.insn\n"
			"	.section        .fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	9b\n"
			"	.previous\n"
			"	.section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश)
			: "memory");

		MIPS_R2_STATS(stores);

		अवरोध;

	हाल ldl_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set    push\n"
			"	.set    reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"1:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 56, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"2:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 48, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"3:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 40, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"4:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 32, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"5:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 24, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"6:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 16, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"7:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 8, 8\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"0:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 0, 8\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"1:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 56, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"2:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 48, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"3:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 40, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"4:	lb	%1, 0(%2)\n"
			"	dinsu	%0, %1, 32, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"5:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 24, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"6:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 16, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"7:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 8, 8\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"0:	lb	%1, 0(%2)\n"
			"	dins	%0, %1, 0, 8\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"	.insn\n"
			"	.section        .fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	9b\n"
			"	.previous\n"
			"	.section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			STR(PTR) " 5b,8b\n"
			STR(PTR) " 6b,8b\n"
			STR(PTR) " 7b,8b\n"
			STR(PTR) " 0b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश));
		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = rt;

		MIPS_R2_STATS(loads);
		अवरोध;

	हाल ldr_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set    push\n"
			"	.set    reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"1:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 0, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"2:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 8, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"3:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 16, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"4:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 24, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"5:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 32, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"6:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 40, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"7:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 48, 8\n"
			"	daddiu  %2, %2, 1\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"0:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 56, 8\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"1:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 0, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"2:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 8, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"3:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 16, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"4:	lb      %1, 0(%2)\n"
			"	dins   %0, %1, 24, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"5:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 32, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"6:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 40, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"7:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 48, 8\n"
			"	andi    %1, %2, 0x7\n"
			"	beq     $0, %1, 9f\n"
			"	daddiu  %2, %2, -1\n"
			"0:	lb      %1, 0(%2)\n"
			"	dinsu    %0, %1, 56, 8\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"	.insn\n"
			"	.section        .fixup,\"ax\"\n"
			"8:	li     %3,%4\n"
			"	j      9b\n"
			"	.previous\n"
			"	.section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			STR(PTR) " 5b,8b\n"
			STR(PTR) " 6b,8b\n"
			STR(PTR) " 7b,8b\n"
			STR(PTR) " 0b,8b\n"
			"	.previous\n"
			"	.set    pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश));
		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = rt;

		MIPS_R2_STATS(loads);
		अवरोध;

	हाल sdl_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"	.set	push\n"
			"	.set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"	dextu	%1, %0, 56, 8\n"
			"1:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dextu	%1, %0, 48, 8\n"
			"2:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dextu	%1, %0, 40, 8\n"
			"3:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dextu	%1, %0, 32, 8\n"
			"4:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dext	%1, %0, 24, 8\n"
			"5:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dext	%1, %0, 16, 8\n"
			"6:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dext	%1, %0, 8, 8\n"
			"7:	sb	%1, 0(%2)\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	daddiu	%2, %2, -1\n"
			"	dext	%1, %0, 0, 8\n"
			"0:	sb	%1, 0(%2)\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"	dextu	%1, %0, 56, 8\n"
			"1:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dextu	%1, %0, 48, 8\n"
			"2:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dextu	%1, %0, 40, 8\n"
			"3:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dextu	%1, %0, 32, 8\n"
			"4:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dext	%1, %0, 24, 8\n"
			"5:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dext	%1, %0, 16, 8\n"
			"6:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dext	%1, %0, 8, 8\n"
			"7:	sb	%1, 0(%2)\n"
			"	daddiu	%2, %2, 1\n"
			"	andi	%1, %2, 0x7\n"
			"	beq	$0, %1, 9f\n"
			"	dext	%1, %0, 0, 8\n"
			"0:	sb	%1, 0(%2)\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"	.insn\n"
			"	.section        .fixup,\"ax\"\n"
			"8:	li	%3,%4\n"
			"	j	9b\n"
			"	.previous\n"
			"	.section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			STR(PTR) " 5b,8b\n"
			STR(PTR) " 6b,8b\n"
			STR(PTR) " 7b,8b\n"
			STR(PTR) " 0b,8b\n"
			"	.previous\n"
			"	.set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश)
			: "memory");

		MIPS_R2_STATS(stores);
		अवरोध;

	हाल sdr_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		rt = regs->regs[MIPSInst_RT(inst)];
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = संक_अंश;
			अवरोध;
		पूर्ण
		__यंत्र__ __अस्थिर__(
			"       .set	push\n"
			"       .set	reorder\n"
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			"       dext	%1, %0, 0, 8\n"
			"1:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dext	%1, %0, 8, 8\n"
			"2:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dext	%1, %0, 16, 8\n"
			"3:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dext	%1, %0, 24, 8\n"
			"4:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dextu	%1, %0, 32, 8\n"
			"5:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dextu	%1, %0, 40, 8\n"
			"6:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dextu	%1, %0, 48, 8\n"
			"7:     sb	%1, 0(%2)\n"
			"       daddiu	%2, %2, 1\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       dextu	%1, %0, 56, 8\n"
			"0:     sb	%1, 0(%2)\n"
#अन्यथा /* !CONFIG_CPU_LITTLE_ENDIAN */
			"       dext	%1, %0, 0, 8\n"
			"1:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dext	%1, %0, 8, 8\n"
			"2:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dext	%1, %0, 16, 8\n"
			"3:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dext	%1, %0, 24, 8\n"
			"4:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dextu	%1, %0, 32, 8\n"
			"5:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dextu	%1, %0, 40, 8\n"
			"6:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dextu	%1, %0, 48, 8\n"
			"7:     sb	%1, 0(%2)\n"
			"       andi	%1, %2, 0x7\n"
			"       beq	$0, %1, 9f\n"
			"       daddiu	%2, %2, -1\n"
			"       dextu	%1, %0, 56, 8\n"
			"0:     sb	%1, 0(%2)\n"
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
			"9:\n"
			"       .insn\n"
			"       .section        .fixup,\"ax\"\n"
			"8:     li	%3,%4\n"
			"       j	9b\n"
			"       .previous\n"
			"       .section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,8b\n"
			STR(PTR) " 2b,8b\n"
			STR(PTR) " 3b,8b\n"
			STR(PTR) " 4b,8b\n"
			STR(PTR) " 5b,8b\n"
			STR(PTR) " 6b,8b\n"
			STR(PTR) " 7b,8b\n"
			STR(PTR) " 0b,8b\n"
			"       .previous\n"
			"       .set	pop\n"
			: "+&r"(rt), "=&r"(rs),
			  "+&r"(vaddr), "+&r"(err)
			: "i"(संक_अंश)
			: "memory");

		MIPS_R2_STATS(stores);

		अवरोध;
	हाल ll_op:
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (vaddr & 0x3) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण

		अगर (!cpu_has_rw_llb) अणु
			/*
			 * An LL/SC block can't be safely emulated without
			 * a Config5/LLB availability. So it's probably समय to
			 * समाप्त our process beक्रमe things get any worse. This is
			 * because Config5/LLB allows us to use ERETNC so that
			 * the LLAddr/LLB bit is not cleared when we वापस from
			 * an exception. MIPS R2 LL/SC inकाष्ठाions trap with an
			 * RI exception so once we emulate them here, we वापस
			 * back to userland with ERETNC. That preserves the
			 * LLAddr/LLB so the subsequent SC inकाष्ठाion will
			 * succeed preserving the atomic semantics of the LL/SC
			 * block. Without that, there is no safe way to emulate
			 * an LL/SC block in MIPSR2 userland.
			 */
			pr_err("Can't emulate MIPSR2 LL/SC without Config5/LLB\n");
			err = SIGKILL;
			अवरोध;
		पूर्ण

		__यंत्र__ __अस्थिर__(
			"1:\n"
			"ll	%0, 0(%2)\n"
			"2:\n"
			".insn\n"
			".section        .fixup,\"ax\"\n"
			"3:\n"
			"li	%1, %3\n"
			"j	2b\n"
			".previous\n"
			".section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,3b\n"
			".previous\n"
			: "=&r"(res), "+&r"(err)
			: "r"(vaddr), "i"(संक_अंश)
			: "memory");

		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = res;
		MIPS_R2_STATS(llsc);

		अवरोध;

	हाल sc_op:
		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (vaddr & 0x3) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण
		अगर (!access_ok((व्योम __user *)vaddr, 4)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण

		अगर (!cpu_has_rw_llb) अणु
			/*
			 * An LL/SC block can't be safely emulated without
			 * a Config5/LLB availability. So it's probably समय to
			 * समाप्त our process beक्रमe things get any worse. This is
			 * because Config5/LLB allows us to use ERETNC so that
			 * the LLAddr/LLB bit is not cleared when we वापस from
			 * an exception. MIPS R2 LL/SC inकाष्ठाions trap with an
			 * RI exception so once we emulate them here, we वापस
			 * back to userland with ERETNC. That preserves the
			 * LLAddr/LLB so the subsequent SC inकाष्ठाion will
			 * succeed preserving the atomic semantics of the LL/SC
			 * block. Without that, there is no safe way to emulate
			 * an LL/SC block in MIPSR2 userland.
			 */
			pr_err("Can't emulate MIPSR2 LL/SC without Config5/LLB\n");
			err = SIGKILL;
			अवरोध;
		पूर्ण

		res = regs->regs[MIPSInst_RT(inst)];

		__यंत्र__ __अस्थिर__(
			"1:\n"
			"sc	%0, 0(%2)\n"
			"2:\n"
			".insn\n"
			".section        .fixup,\"ax\"\n"
			"3:\n"
			"li	%1, %3\n"
			"j	2b\n"
			".previous\n"
			".section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,3b\n"
			".previous\n"
			: "+&r"(res), "+&r"(err)
			: "r"(vaddr), "i"(संक_अंश));

		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = res;

		MIPS_R2_STATS(llsc);

		अवरोध;

	हाल lld_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (vaddr & 0x7) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण

		अगर (!cpu_has_rw_llb) अणु
			/*
			 * An LL/SC block can't be safely emulated without
			 * a Config5/LLB availability. So it's probably समय to
			 * समाप्त our process beक्रमe things get any worse. This is
			 * because Config5/LLB allows us to use ERETNC so that
			 * the LLAddr/LLB bit is not cleared when we वापस from
			 * an exception. MIPS R2 LL/SC inकाष्ठाions trap with an
			 * RI exception so once we emulate them here, we वापस
			 * back to userland with ERETNC. That preserves the
			 * LLAddr/LLB so the subsequent SC inकाष्ठाion will
			 * succeed preserving the atomic semantics of the LL/SC
			 * block. Without that, there is no safe way to emulate
			 * an LL/SC block in MIPSR2 userland.
			 */
			pr_err("Can't emulate MIPSR2 LL/SC without Config5/LLB\n");
			err = SIGKILL;
			अवरोध;
		पूर्ण

		__यंत्र__ __अस्थिर__(
			"1:\n"
			"lld	%0, 0(%2)\n"
			"2:\n"
			".insn\n"
			".section        .fixup,\"ax\"\n"
			"3:\n"
			"li	%1, %3\n"
			"j	2b\n"
			".previous\n"
			".section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,3b\n"
			".previous\n"
			: "=&r"(res), "+&r"(err)
			: "r"(vaddr), "i"(संक_अंश)
			: "memory");
		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = res;

		MIPS_R2_STATS(llsc);

		अवरोध;

	हाल scd_op:
		अगर (IS_ENABLED(CONFIG_32BIT)) अणु
		    err = संक_अवैध;
		    अवरोध;
		पूर्ण

		vaddr = regs->regs[MIPSInst_RS(inst)] + MIPSInst_SIMM(inst);
		अगर (vaddr & 0x7) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण
		अगर (!access_ok((व्योम __user *)vaddr, 8)) अणु
			current->thपढ़ो.cp0_baduaddr = vaddr;
			err = SIGBUS;
			अवरोध;
		पूर्ण

		अगर (!cpu_has_rw_llb) अणु
			/*
			 * An LL/SC block can't be safely emulated without
			 * a Config5/LLB availability. So it's probably समय to
			 * समाप्त our process beक्रमe things get any worse. This is
			 * because Config5/LLB allows us to use ERETNC so that
			 * the LLAddr/LLB bit is not cleared when we वापस from
			 * an exception. MIPS R2 LL/SC inकाष्ठाions trap with an
			 * RI exception so once we emulate them here, we वापस
			 * back to userland with ERETNC. That preserves the
			 * LLAddr/LLB so the subsequent SC inकाष्ठाion will
			 * succeed preserving the atomic semantics of the LL/SC
			 * block. Without that, there is no safe way to emulate
			 * an LL/SC block in MIPSR2 userland.
			 */
			pr_err("Can't emulate MIPSR2 LL/SC without Config5/LLB\n");
			err = SIGKILL;
			अवरोध;
		पूर्ण

		res = regs->regs[MIPSInst_RT(inst)];

		__यंत्र__ __अस्थिर__(
			"1:\n"
			"scd	%0, 0(%2)\n"
			"2:\n"
			".insn\n"
			".section        .fixup,\"ax\"\n"
			"3:\n"
			"li	%1, %3\n"
			"j	2b\n"
			".previous\n"
			".section        __ex_table,\"a\"\n"
			STR(PTR) " 1b,3b\n"
			".previous\n"
			: "+&r"(res), "+&r"(err)
			: "r"(vaddr), "i"(संक_अंश));

		अगर (MIPSInst_RT(inst) && !err)
			regs->regs[MIPSInst_RT(inst)] = res;

		MIPS_R2_STATS(llsc);

		अवरोध;
	हाल pref_op:
		/* skip it */
		अवरोध;
	शेष:
		err = संक_अवैध;
	पूर्ण

	/*
	 * Let's not return to userland just yet. It's costly and
	 * it's likely we have more R2 inकाष्ठाions to emulate
	 */
	अगर (!err && (pass++ < MIPS_R2_EMUL_TOTAL_PASS)) अणु
		regs->cp0_cause &= ~CAUSEF_BD;
		err = get_user(inst, (u32 __user *)regs->cp0_epc);
		अगर (!err)
			जाओ repeat;

		अगर (err < 0)
			err = संक_अंश;
	पूर्ण

	अगर (err && (err != SIGEMT)) अणु
		regs->regs[31] = r31;
		regs->cp0_epc = epc;
	पूर्ण

	/* Likely a MIPS R6 compatible inकाष्ठाion */
	अगर (pass && (err == संक_अवैध))
		err = 0;

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक mipsr2_emul_show(काष्ठा seq_file *s, व्योम *unused)
अणु

	seq_म_लिखो(s, "Instruction\tTotal\tBDslot\n------------------------------\n");
	seq_म_लिखो(s, "movs\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.movs),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.movs));
	seq_म_लिखो(s, "hilo\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.hilo),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.hilo));
	seq_म_लिखो(s, "muls\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.muls),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.muls));
	seq_म_लिखो(s, "divs\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.भागs),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.भागs));
	seq_म_लिखो(s, "dsps\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.dsps),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.dsps));
	seq_म_लिखो(s, "bops\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.bops),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.bops));
	seq_म_लिखो(s, "traps\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.traps),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.traps));
	seq_म_लिखो(s, "fpus\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.fpus),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.fpus));
	seq_म_लिखो(s, "loads\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.loads),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.loads));
	seq_म_लिखो(s, "stores\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.stores),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.stores));
	seq_म_लिखो(s, "llsc\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.llsc),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.llsc));
	seq_म_लिखो(s, "dsemul\t\t%ld\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2emustats.dsemul),
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bdemustats.dsemul));
	seq_म_लिखो(s, "jr\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.jrs));
	seq_म_लिखो(s, "bltzl\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bltzl));
	seq_म_लिखो(s, "bgezl\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bgezl));
	seq_म_लिखो(s, "bltzll\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bltzll));
	seq_म_लिखो(s, "bgezll\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bgezll));
	seq_म_लिखो(s, "bltzal\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bltzal));
	seq_म_लिखो(s, "bgezal\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bgezal));
	seq_म_लिखो(s, "beql\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.beql));
	seq_म_लिखो(s, "bnel\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bnel));
	seq_म_लिखो(s, "blezl\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.blezl));
	seq_म_लिखो(s, "bgtzl\t\t%ld\n",
		   (अचिन्हित दीर्घ)__this_cpu_पढ़ो(mipsr2bremustats.bgtzl));

	वापस 0;
पूर्ण

अटल पूर्णांक mipsr2_clear_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	mipsr2_emul_show(s, unused);

	__this_cpu_ग_लिखो((mipsr2emustats).movs, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).movs, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).hilo, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).hilo, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).muls, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).muls, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).भागs, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).भागs, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).dsps, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).dsps, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).bops, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).bops, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).traps, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).traps, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).fpus, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).fpus, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).loads, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).loads, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).stores, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).stores, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).llsc, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).llsc, 0);
	__this_cpu_ग_लिखो((mipsr2emustats).dsemul, 0);
	__this_cpu_ग_लिखो((mipsr2bdemustats).dsemul, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).jrs, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bltzl, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bgezl, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bltzll, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bgezll, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bltzall, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bgezall, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bltzal, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bgezal, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).beql, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bnel, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).blezl, 0);
	__this_cpu_ग_लिखो((mipsr2bremustats).bgtzl, 0);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mipsr2_emul);
DEFINE_SHOW_ATTRIBUTE(mipsr2_clear);

अटल पूर्णांक __init mipsr2_init_debugfs(व्योम)
अणु
	debugfs_create_file("r2_emul_stats", S_IRUGO, mips_debugfs_dir, शून्य,
			    &mipsr2_emul_fops);
	debugfs_create_file("r2_emul_stats_clear", S_IRUGO, mips_debugfs_dir,
			    शून्य, &mipsr2_clear_fops);
	वापस 0;
पूर्ण

device_initcall(mipsr2_init_debugfs);

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
