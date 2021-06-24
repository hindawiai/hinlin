<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple sanity tests क्रम inकाष्ठाion emulation infraकाष्ठाure.
 *
 * Copyright IBM Corp. 2016
 */

#घोषणा pr_fmt(fmt) "emulate_step_test: " fmt

#समावेश <linux/ptrace.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/inst.h>

#घोषणा MAX_SUBTESTS	16

#घोषणा IGNORE_GPR(n)	(0x1UL << (n))
#घोषणा IGNORE_XER	(0x1UL << 32)
#घोषणा IGNORE_CCR	(0x1UL << 33)
#घोषणा NEGATIVE_TEST	(0x1UL << 63)

#घोषणा TEST_PLD(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_PLD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PLWZ(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_RAW_LWZ(r, base, i))

#घोषणा TEST_PSTD(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_PSTD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PLFS(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_LFS | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PSTFS(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_STFS | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PLFD(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_LFD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PSTFD(r, base, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_INST_STFD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))

#घोषणा TEST_PADDI(t, a, i, pr) \
	ppc_inst_prefix(PPC_PREFIX_MLS | __PPC_PRFX_R(pr) | IMM_H(i), \
			PPC_RAW_ADDI(t, a, i))


अटल व्योम __init init_pt_regs(काष्ठा pt_regs *regs)
अणु
	अटल अचिन्हित दीर्घ msr;
	अटल bool msr_cached;

	स_रखो(regs, 0, माप(काष्ठा pt_regs));

	अगर (likely(msr_cached)) अणु
		regs->msr = msr;
		वापस;
	पूर्ण

	यंत्र अस्थिर("mfmsr %0" : "=r"(regs->msr));

	regs->msr |= MSR_FP;
	regs->msr |= MSR_VEC;
	regs->msr |= MSR_VSX;

	msr = regs->msr;
	msr_cached = true;
पूर्ण

अटल व्योम __init show_result(अक्षर *mnemonic, अक्षर *result)
अणु
	pr_info("%-14s : %s\n", mnemonic, result);
पूर्ण

अटल व्योम __init show_result_with_descr(अक्षर *mnemonic, अक्षर *descr,
					  अक्षर *result)
अणु
	pr_info("%-14s : %-50s %s\n", mnemonic, descr, result);
पूर्ण

अटल व्योम __init test_ld(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ a = 0x23;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ) &a;

	/* ld r5, 0(r3) */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LD(5, 3, 0)));

	अगर (stepped == 1 && regs.gpr[5] == a)
		show_result("ld", "PASS");
	अन्यथा
		show_result("ld", "FAIL");
पूर्ण

अटल व्योम __init test_pld(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ a = 0x23;
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("pld", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ)&a;

	/* pld r5, 0(r3), 0 */
	stepped = emulate_step(&regs, TEST_PLD(5, 3, 0, 0));

	अगर (stepped == 1 && regs.gpr[5] == a)
		show_result("pld", "PASS");
	अन्यथा
		show_result("pld", "FAIL");
पूर्ण

अटल व्योम __init test_lwz(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित पूर्णांक a = 0x4545;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ) &a;

	/* lwz r5, 0(r3) */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LWZ(5, 3, 0)));

	अगर (stepped == 1 && regs.gpr[5] == a)
		show_result("lwz", "PASS");
	अन्यथा
		show_result("lwz", "FAIL");
पूर्ण

अटल व्योम __init test_plwz(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित पूर्णांक a = 0x4545;
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("plwz", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ)&a;

	/* plwz r5, 0(r3), 0 */

	stepped = emulate_step(&regs, TEST_PLWZ(5, 3, 0, 0));

	अगर (stepped == 1 && regs.gpr[5] == a)
		show_result("plwz", "PASS");
	अन्यथा
		show_result("plwz", "FAIL");
पूर्ण

अटल व्योम __init test_lwzx(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित पूर्णांक a[3] = अणु0x0, 0x0, 0x1234पूर्ण;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ) a;
	regs.gpr[4] = 8;
	regs.gpr[5] = 0x8765;

	/* lwzx r5, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LWZX(5, 3, 4)));
	अगर (stepped == 1 && regs.gpr[5] == a[2])
		show_result("lwzx", "PASS");
	अन्यथा
		show_result("lwzx", "FAIL");
पूर्ण

अटल व्योम __init test_std(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ a = 0x1234;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ) &a;
	regs.gpr[5] = 0x5678;

	/* std r5, 0(r3) */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STD(5, 3, 0)));
	अगर (stepped == 1 && regs.gpr[5] == a)
		show_result("std", "PASS");
	अन्यथा
		show_result("std", "FAIL");
पूर्ण

अटल व्योम __init test_pstd(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ a = 0x1234;
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("pstd", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ)&a;
	regs.gpr[5] = 0x5678;

	/* pstd r5, 0(r3), 0 */
	stepped = emulate_step(&regs, TEST_PSTD(5, 3, 0, 0));
	अगर (stepped == 1 || regs.gpr[5] == a)
		show_result("pstd", "PASS");
	अन्यथा
		show_result("pstd", "FAIL");
पूर्ण

अटल व्योम __init test_ldarx_stdcx(व्योम)
अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ a = 0x1234;
	पूर्णांक stepped = -1;
	अचिन्हित दीर्घ cr0_eq = 0x1 << 29; /* eq bit of CR0 */

	init_pt_regs(&regs);
	यंत्र अस्थिर("mfcr %0" : "=r"(regs.ccr));


	/*** ldarx ***/

	regs.gpr[3] = (अचिन्हित दीर्घ) &a;
	regs.gpr[4] = 0;
	regs.gpr[5] = 0x5678;

	/* ldarx r5, r3, r4, 0 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LDARX(5, 3, 4, 0)));

	/*
	 * Don't touch 'a' here. Touching 'a' can करो Load/store
	 * of 'a' which result in failure of subsequent stdcx.
	 * Instead, use hardcoded value क्रम comparison.
	 */
	अगर (stepped <= 0 || regs.gpr[5] != 0x1234) अणु
		show_result("ldarx / stdcx.", "FAIL (ldarx)");
		वापस;
	पूर्ण


	/*** stdcx. ***/

	regs.gpr[5] = 0x9ABC;

	/* stdcx. r5, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STDCX(5, 3, 4)));

	/*
	 * Two possible scenarios that indicates successful emulation
	 * of stdcx. :
	 *  1. Reservation is active and store is perक्रमmed. In this
	 *     हाल cr0.eq bit will be set to 1.
	 *  2. Reservation is not active and store is not perक्रमmed.
	 *     In this हाल cr0.eq bit will be set to 0.
	 */
	अगर (stepped == 1 && ((regs.gpr[5] == a && (regs.ccr & cr0_eq))
			|| (regs.gpr[5] != a && !(regs.ccr & cr0_eq))))
		show_result("ldarx / stdcx.", "PASS");
	अन्यथा
		show_result("ldarx / stdcx.", "FAIL (stdcx.)");
पूर्ण

#अगर_घोषित CONFIG_PPC_FPU
अटल व्योम __init test_lfsx_stfsx(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		भग्न a;
		पूर्णांक b;
	पूर्ण c;
	पूर्णांक cached_b;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);


	/*** lfsx ***/

	c.a = 123.45;
	cached_b = c.b;

	regs.gpr[3] = (अचिन्हित दीर्घ) &c.a;
	regs.gpr[4] = 0;

	/* lfsx frt10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LFSX(10, 3, 4)));

	अगर (stepped == 1)
		show_result("lfsx", "PASS");
	अन्यथा
		show_result("lfsx", "FAIL");


	/*** stfsx ***/

	c.a = 678.91;

	/* stfsx frs10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STFSX(10, 3, 4)));

	अगर (stepped == 1 && c.b == cached_b)
		show_result("stfsx", "PASS");
	अन्यथा
		show_result("stfsx", "FAIL");
पूर्ण

अटल व्योम __init test_plfs_pstfs(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		भग्न a;
		पूर्णांक b;
	पूर्ण c;
	पूर्णांक cached_b;
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("pld", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);


	/*** plfs ***/

	c.a = 123.45;
	cached_b = c.b;

	regs.gpr[3] = (अचिन्हित दीर्घ)&c.a;

	/* plfs frt10, 0(r3), 0  */
	stepped = emulate_step(&regs, TEST_PLFS(10, 3, 0, 0));

	अगर (stepped == 1)
		show_result("plfs", "PASS");
	अन्यथा
		show_result("plfs", "FAIL");


	/*** pstfs ***/

	c.a = 678.91;

	/* pstfs frs10, 0(r3), 0 */
	stepped = emulate_step(&regs, TEST_PSTFS(10, 3, 0, 0));

	अगर (stepped == 1 && c.b == cached_b)
		show_result("pstfs", "PASS");
	अन्यथा
		show_result("pstfs", "FAIL");
पूर्ण

अटल व्योम __init test_lfdx_stfdx(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		द्विगुन a;
		दीर्घ b;
	पूर्ण c;
	दीर्घ cached_b;
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);


	/*** lfdx ***/

	c.a = 123456.78;
	cached_b = c.b;

	regs.gpr[3] = (अचिन्हित दीर्घ) &c.a;
	regs.gpr[4] = 0;

	/* lfdx frt10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LFDX(10, 3, 4)));

	अगर (stepped == 1)
		show_result("lfdx", "PASS");
	अन्यथा
		show_result("lfdx", "FAIL");


	/*** stfdx ***/

	c.a = 987654.32;

	/* stfdx frs10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STFDX(10, 3, 4)));

	अगर (stepped == 1 && c.b == cached_b)
		show_result("stfdx", "PASS");
	अन्यथा
		show_result("stfdx", "FAIL");
पूर्ण

अटल व्योम __init test_plfd_pstfd(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		द्विगुन a;
		दीर्घ b;
	पूर्ण c;
	दीर्घ cached_b;
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("pld", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);


	/*** plfd ***/

	c.a = 123456.78;
	cached_b = c.b;

	regs.gpr[3] = (अचिन्हित दीर्घ)&c.a;

	/* plfd frt10, 0(r3), 0 */
	stepped = emulate_step(&regs, TEST_PLFD(10, 3, 0, 0));

	अगर (stepped == 1)
		show_result("plfd", "PASS");
	अन्यथा
		show_result("plfd", "FAIL");


	/*** pstfd ***/

	c.a = 987654.32;

	/* pstfd frs10, 0(r3), 0 */
	stepped = emulate_step(&regs, TEST_PSTFD(10, 3, 0, 0));

	अगर (stepped == 1 && c.b == cached_b)
		show_result("pstfd", "PASS");
	अन्यथा
		show_result("pstfd", "FAIL");
पूर्ण
#अन्यथा
अटल व्योम __init test_lfsx_stfsx(व्योम)
अणु
	show_result("lfsx", "SKIP (CONFIG_PPC_FPU is not set)");
	show_result("stfsx", "SKIP (CONFIG_PPC_FPU is not set)");
पूर्ण

अटल व्योम __init test_plfs_pstfs(व्योम)
अणु
	show_result("plfs", "SKIP (CONFIG_PPC_FPU is not set)");
	show_result("pstfs", "SKIP (CONFIG_PPC_FPU is not set)");
पूर्ण

अटल व्योम __init test_lfdx_stfdx(व्योम)
अणु
	show_result("lfdx", "SKIP (CONFIG_PPC_FPU is not set)");
	show_result("stfdx", "SKIP (CONFIG_PPC_FPU is not set)");
पूर्ण

अटल व्योम __init test_plfd_pstfd(व्योम)
अणु
	show_result("plfd", "SKIP (CONFIG_PPC_FPU is not set)");
	show_result("pstfd", "SKIP (CONFIG_PPC_FPU is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FPU */

#अगर_घोषित CONFIG_ALTIVEC
अटल व्योम __init test_lvx_stvx(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		vector128 a;
		u32 b[4];
	पूर्ण c;
	u32 cached_b[4];
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);


	/*** lvx ***/

	cached_b[0] = c.b[0] = 923745;
	cached_b[1] = c.b[1] = 2139478;
	cached_b[2] = c.b[2] = 9012;
	cached_b[3] = c.b[3] = 982134;

	regs.gpr[3] = (अचिन्हित दीर्घ) &c.a;
	regs.gpr[4] = 0;

	/* lvx vrt10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LVX(10, 3, 4)));

	अगर (stepped == 1)
		show_result("lvx", "PASS");
	अन्यथा
		show_result("lvx", "FAIL");


	/*** stvx ***/

	c.b[0] = 4987513;
	c.b[1] = 84313948;
	c.b[2] = 71;
	c.b[3] = 498532;

	/* stvx vrs10, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STVX(10, 3, 4)));

	अगर (stepped == 1 && cached_b[0] == c.b[0] && cached_b[1] == c.b[1] &&
	    cached_b[2] == c.b[2] && cached_b[3] == c.b[3])
		show_result("stvx", "PASS");
	अन्यथा
		show_result("stvx", "FAIL");
पूर्ण
#अन्यथा
अटल व्योम __init test_lvx_stvx(व्योम)
अणु
	show_result("lvx", "SKIP (CONFIG_ALTIVEC is not set)");
	show_result("stvx", "SKIP (CONFIG_ALTIVEC is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित CONFIG_VSX
अटल व्योम __init test_lxvd2x_stxvd2x(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		vector128 a;
		u32 b[4];
	पूर्ण c;
	u32 cached_b[4];
	पूर्णांक stepped = -1;

	init_pt_regs(&regs);


	/*** lxvd2x ***/

	cached_b[0] = c.b[0] = 18233;
	cached_b[1] = c.b[1] = 34863571;
	cached_b[2] = c.b[2] = 834;
	cached_b[3] = c.b[3] = 6138911;

	regs.gpr[3] = (अचिन्हित दीर्घ) &c.a;
	regs.gpr[4] = 0;

	/* lxvd2x vsr39, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LXVD2X(39, R3, R4)));

	अगर (stepped == 1 && cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("lxvd2x", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("lxvd2x", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("lxvd2x", "FAIL");
	पूर्ण


	/*** stxvd2x ***/

	c.b[0] = 21379463;
	c.b[1] = 87;
	c.b[2] = 374234;
	c.b[3] = 4;

	/* stxvd2x vsr39, r3, r4 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STXVD2X(39, R3, R4)));

	अगर (stepped == 1 && cached_b[0] == c.b[0] && cached_b[1] == c.b[1] &&
	    cached_b[2] == c.b[2] && cached_b[3] == c.b[3] &&
	    cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("stxvd2x", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("stxvd2x", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("stxvd2x", "FAIL");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init test_lxvd2x_stxvd2x(व्योम)
अणु
	show_result("lxvd2x", "SKIP (CONFIG_VSX is not set)");
	show_result("stxvd2x", "SKIP (CONFIG_VSX is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_VSX
अटल व्योम __init test_lxvp_stxvp(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		vector128 a;
		u32 b[4];
	पूर्ण c[2];
	u32 cached_b[8];
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("lxvp", "SKIP (!CPU_FTR_ARCH_31)");
		show_result("stxvp", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);

	/*** lxvp ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	regs.gpr[4] = (अचिन्हित दीर्घ)&c[0].a;

	/*
	 * lxvp XTp,DQ(RA)
	 * XTp = 32xTX + 2xTp
	 * let TX=1 Tp=1 RA=4 DQ=0
	 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LXVP(34, 4, 0)));

	अगर (stepped == 1 && cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("lxvp", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("lxvp", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("lxvp", "FAIL");
	पूर्ण

	/*** stxvp ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * stxvp XSp,DQ(RA)
	 * XSp = 32xSX + 2xSp
	 * let SX=1 Sp=1 RA=4 DQ=0
	 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STXVP(34, 4, 0)));

	अगर (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("stxvp", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("stxvp", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("stxvp", "FAIL");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init test_lxvp_stxvp(व्योम)
अणु
	show_result("lxvp", "SKIP (CONFIG_VSX is not set)");
	show_result("stxvp", "SKIP (CONFIG_VSX is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_VSX
अटल व्योम __init test_lxvpx_stxvpx(व्योम)
अणु
	काष्ठा pt_regs regs;
	जोड़ अणु
		vector128 a;
		u32 b[4];
	पूर्ण c[2];
	u32 cached_b[8];
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("lxvpx", "SKIP (!CPU_FTR_ARCH_31)");
		show_result("stxvpx", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	init_pt_regs(&regs);

	/*** lxvpx ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	regs.gpr[3] = (अचिन्हित दीर्घ)&c[0].a;
	regs.gpr[4] = 0;

	/*
	 * lxvpx XTp,RA,RB
	 * XTp = 32xTX + 2xTp
	 * let TX=1 Tp=1 RA=3 RB=4
	 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_LXVPX(34, 3, 4)));

	अगर (stepped == 1 && cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("lxvpx", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("lxvpx", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("lxvpx", "FAIL");
	पूर्ण

	/*** stxvpx ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * stxvpx XSp,RA,RB
	 * XSp = 32xSX + 2xSp
	 * let SX=1 Sp=1 RA=3 RB=4
	 */
	stepped = emulate_step(&regs, ppc_inst(PPC_RAW_STXVPX(34, 3, 4)));

	अगर (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("stxvpx", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("stxvpx", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("stxvpx", "FAIL");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init test_lxvpx_stxvpx(व्योम)
अणु
	show_result("lxvpx", "SKIP (CONFIG_VSX is not set)");
	show_result("stxvpx", "SKIP (CONFIG_VSX is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_VSX
अटल व्योम __init test_plxvp_pstxvp(व्योम)
अणु
	काष्ठा ppc_inst instr;
	काष्ठा pt_regs regs;
	जोड़ अणु
		vector128 a;
		u32 b[4];
	पूर्ण c[2];
	u32 cached_b[8];
	पूर्णांक stepped = -1;

	अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		show_result("plxvp", "SKIP (!CPU_FTR_ARCH_31)");
		show_result("pstxvp", "SKIP (!CPU_FTR_ARCH_31)");
		वापस;
	पूर्ण

	/*** plxvp ***/

	cached_b[0] = c[0].b[0] = 18233;
	cached_b[1] = c[0].b[1] = 34863571;
	cached_b[2] = c[0].b[2] = 834;
	cached_b[3] = c[0].b[3] = 6138911;
	cached_b[4] = c[1].b[0] = 1234;
	cached_b[5] = c[1].b[1] = 5678;
	cached_b[6] = c[1].b[2] = 91011;
	cached_b[7] = c[1].b[3] = 121314;

	init_pt_regs(&regs);
	regs.gpr[3] = (अचिन्हित दीर्घ)&c[0].a;

	/*
	 * plxvp XTp,D(RA),R
	 * XTp = 32xTX + 2xTp
	 * let RA=3 R=0 D=d0||d1=0 R=0 Tp=1 TX=1
	 */
	instr = ppc_inst_prefix(PPC_RAW_PLXVP(34, 0, 3, 0) >> 32,
			PPC_RAW_PLXVP(34, 0, 3, 0) & 0xffffffff);

	stepped = emulate_step(&regs, instr);
	अगर (stepped == 1 && cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("plxvp", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("plxvp", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("plxvp", "FAIL");
	पूर्ण

	/*** pstxvp ***/

	c[0].b[0] = 21379463;
	c[0].b[1] = 87;
	c[0].b[2] = 374234;
	c[0].b[3] = 4;
	c[1].b[0] = 90;
	c[1].b[1] = 122;
	c[1].b[2] = 555;
	c[1].b[3] = 32144;

	/*
	 * pstxvp XSp,D(RA),R
	 * XSp = 32xSX + 2xSp
	 * let RA=3 D=d0||d1=0 R=0 Sp=1 SX=1
	 */
	instr = ppc_inst_prefix(PPC_RAW_PSTXVP(34, 0, 3, 0) >> 32,
			PPC_RAW_PSTXVP(34, 0, 3, 0) & 0xffffffff);

	stepped = emulate_step(&regs, instr);

	अगर (stepped == 1 && cached_b[0] == c[0].b[0] && cached_b[1] == c[0].b[1] &&
	    cached_b[2] == c[0].b[2] && cached_b[3] == c[0].b[3] &&
	    cached_b[4] == c[1].b[0] && cached_b[5] == c[1].b[1] &&
	    cached_b[6] == c[1].b[2] && cached_b[7] == c[1].b[3] &&
	    cpu_has_feature(CPU_FTR_VSX)) अणु
		show_result("pstxvp", "PASS");
	पूर्ण अन्यथा अणु
		अगर (!cpu_has_feature(CPU_FTR_VSX))
			show_result("pstxvp", "PASS (!CPU_FTR_VSX)");
		अन्यथा
			show_result("pstxvp", "FAIL");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init test_plxvp_pstxvp(व्योम)
अणु
	show_result("plxvp", "SKIP (CONFIG_VSX is not set)");
	show_result("pstxvp", "SKIP (CONFIG_VSX is not set)");
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

अटल व्योम __init run_tests_load_store(व्योम)
अणु
	test_ld();
	test_pld();
	test_lwz();
	test_plwz();
	test_lwzx();
	test_std();
	test_pstd();
	test_ldarx_stdcx();
	test_lfsx_stfsx();
	test_plfs_pstfs();
	test_lfdx_stfdx();
	test_plfd_pstfd();
	test_lvx_stvx();
	test_lxvd2x_stxvd2x();
	test_lxvp_stxvp();
	test_lxvpx_stxvpx();
	test_plxvp_pstxvp();
पूर्ण

काष्ठा compute_test अणु
	अक्षर *mnemonic;
	अचिन्हित दीर्घ cpu_feature;
	काष्ठा अणु
		अक्षर *descr;
		अचिन्हित दीर्घ flags;
		काष्ठा ppc_inst instr;
		काष्ठा pt_regs regs;
	पूर्ण subtests[MAX_SUBTESTS + 1];
पूर्ण;

/* Extreme values क्रम si0||si1 (the MLS:D-क्रमm 34 bit immediate field) */
#घोषणा SI_MIN BIT(33)
#घोषणा SI_MAX (BIT(33) - 1)
#घोषणा SI_UMAX (BIT(34) - 1)

अटल काष्ठा compute_test compute_tests[] = अणु
	अणु
		.mnemonic = "nop",
		.subtests = अणु
			अणु
				.descr = "R0 = LONG_MAX",
				.instr = ppc_inst(PPC_INST_NOP),
				.regs = अणु
					.gpr[0] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "add",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = ULONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MAX, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_उच्च,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = UINT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADD(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "add.",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.flags = IGNORE_CCR,
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX, RB = LONG_MAX",
				.flags = IGNORE_CCR,
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = ULONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MAX, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_उच्च,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = UINT_MAX",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADD_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "addc",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = ULONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MAX, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_उच्च,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = UINT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN | INT_MIN, RB = LONG_MIN | INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADDC(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून | (uपूर्णांक)पूर्णांक_न्यून,
					.gpr[22] = दीर्घ_न्यून | (uपूर्णांक)पूर्णांक_न्यून,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "addc.",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.flags = IGNORE_CCR,
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX, RB = LONG_MAX",
				.flags = IGNORE_CCR,
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = ULONG_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_दीर्घ_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_न्यून,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MAX, RB = INT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = पूर्णांक_उच्च,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = UINT_MAX",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, RB = 0x1",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = अच_पूर्णांक_उच्च,
					.gpr[22] = 0x1,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN | INT_MIN, RB = LONG_MIN | INT_MIN",
				.instr = ppc_inst(PPC_RAW_ADDC_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून | (uपूर्णांक)पूर्णांक_न्यून,
					.gpr[22] = दीर्घ_न्यून | (uपूर्णांक)पूर्णांक_न्यून,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "divde",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDE(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = 1L, RB = 0",
				.instr = ppc_inst(PPC_RAW_DIVDE(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = 1L,
					.gpr[22] = 0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDE(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "divde.",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDE_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = 1L, RB = 0",
				.instr = ppc_inst(PPC_RAW_DIVDE_DOT(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = 1L,
					.gpr[22] = 0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDE_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "divdeu",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDEU(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = 1L, RB = 0",
				.instr = ppc_inst(PPC_RAW_DIVDEU(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = 1L,
					.gpr[22] = 0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDEU(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX - 1, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDEU(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च - 1,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN + 1, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDEU(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून + 1,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "divdeu.",
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDEU_DOT(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = 1L, RB = 0",
				.instr = ppc_inst(PPC_RAW_DIVDEU_DOT(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = 1L,
					.gpr[22] = 0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDEU_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX - 1, RB = LONG_MAX",
				.instr = ppc_inst(PPC_RAW_DIVDEU_DOT(20, 21, 22)),
				.regs = अणु
					.gpr[21] = दीर्घ_उच्च - 1,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN + 1, RB = LONG_MIN",
				.instr = ppc_inst(PPC_RAW_DIVDEU_DOT(20, 21, 22)),
				.flags = IGNORE_GPR(20),
				.regs = अणु
					.gpr[21] = दीर्घ_न्यून + 1,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.mnemonic = "paddi",
		.cpu_feature = CPU_FTR_ARCH_31,
		.subtests = अणु
			अणु
				.descr = "RA = LONG_MIN, SI = SI_MIN, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MIN, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MIN, SI = SI_MAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = दीर्घ_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = LONG_MAX, SI = SI_MAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, SI = SI_UMAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_UMAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = ULONG_MAX, SI = 0x1, R = 0",
				.instr = TEST_PADDI(21, 22, 0x1, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = अच_दीर्घ_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, SI = SI_MIN, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MIN, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MIN, SI = SI_MAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = पूर्णांक_न्यून,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = INT_MAX, SI = SI_MAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, SI = 0x1, R = 0",
				.instr = TEST_PADDI(21, 22, 0x1, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = UINT_MAX, SI = SI_MAX, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MAX, 0),
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = अच_पूर्णांक_उच्च,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA is r0, SI = SI_MIN, R = 0",
				.instr = TEST_PADDI(21, 0, SI_MIN, 0),
				.regs = अणु
					.gpr[21] = 0x0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA = 0, SI = SI_MIN, R = 0",
				.instr = TEST_PADDI(21, 22, SI_MIN, 0),
				.regs = अणु
					.gpr[21] = 0x0,
					.gpr[22] = 0x0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA is r0, SI = 0, R = 1",
				.instr = TEST_PADDI(21, 0, 0, 1),
				.regs = अणु
					.gpr[21] = 0,
				पूर्ण
			पूर्ण,
			अणु
				.descr = "RA is r0, SI = SI_MIN, R = 1",
				.instr = TEST_PADDI(21, 0, SI_MIN, 1),
				.regs = अणु
					.gpr[21] = 0,
				पूर्ण
			पूर्ण,
			/* Invalid inकाष्ठाion क्रमm with R = 1 and RA != 0 */
			अणु
				.descr = "RA = R22(0), SI = 0, R = 1",
				.instr = TEST_PADDI(21, 22, 0, 1),
				.flags = NEGATIVE_TEST,
				.regs = अणु
					.gpr[21] = 0,
					.gpr[22] = 0,
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक __init emulate_compute_instr(काष्ठा pt_regs *regs,
					काष्ठा ppc_inst instr,
					bool negative)
अणु
	पूर्णांक analysed;
	काष्ठा inकाष्ठाion_op op;

	अगर (!regs || !ppc_inst_val(instr))
		वापस -EINVAL;

	regs->nip = patch_site_addr(&patch__exec_instr);

	analysed = analyse_instr(&op, regs, instr);
	अगर (analysed != 1 || GETTYPE(op.type) != COMPUTE) अणु
		अगर (negative)
			वापस -EFAULT;
		pr_info("emulation failed, instruction = %s\n", ppc_inst_as_str(instr));
		वापस -EFAULT;
	पूर्ण
	अगर (analysed == 1 && negative)
		pr_info("negative test failed, instruction = %s\n", ppc_inst_as_str(instr));
	अगर (!negative)
		emulate_update_regs(regs, &op);
	वापस 0;
पूर्ण

अटल पूर्णांक __init execute_compute_instr(काष्ठा pt_regs *regs,
					काष्ठा ppc_inst instr)
अणु
	बाह्य पूर्णांक exec_instr(काष्ठा pt_regs *regs);

	अगर (!regs || !ppc_inst_val(instr))
		वापस -EINVAL;

	/* Patch the NOP with the actual inकाष्ठाion */
	patch_inकाष्ठाion_site(&patch__exec_instr, instr);
	अगर (exec_instr(regs)) अणु
		pr_info("execution failed, instruction = %s\n", ppc_inst_as_str(instr));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा gpr_mismatch(gprn, exp, got)	\
	pr_info("GPR%u mismatch, exp = 0x%016lx, got = 0x%016lx\n",	\
		gprn, exp, got)

#घोषणा reg_mismatch(name, exp, got)	\
	pr_info("%s mismatch, exp = 0x%016lx, got = 0x%016lx\n",	\
		name, exp, got)

अटल व्योम __init run_tests_compute(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा compute_test *test;
	काष्ठा pt_regs *regs, exp, got;
	अचिन्हित पूर्णांक i, j, k;
	काष्ठा ppc_inst instr;
	bool ignore_gpr, ignore_xer, ignore_ccr, passed, rc, negative;

	क्रम (i = 0; i < ARRAY_SIZE(compute_tests); i++) अणु
		test = &compute_tests[i];

		अगर (test->cpu_feature && !early_cpu_has_feature(test->cpu_feature)) अणु
			show_result(test->mnemonic, "SKIP (!CPU_FTR)");
			जारी;
		पूर्ण

		क्रम (j = 0; j < MAX_SUBTESTS && test->subtests[j].descr; j++) अणु
			instr = test->subtests[j].instr;
			flags = test->subtests[j].flags;
			regs = &test->subtests[j].regs;
			negative = flags & NEGATIVE_TEST;
			ignore_xer = flags & IGNORE_XER;
			ignore_ccr = flags & IGNORE_CCR;
			passed = true;

			स_नकल(&exp, regs, माप(काष्ठा pt_regs));
			स_नकल(&got, regs, माप(काष्ठा pt_regs));

			/*
			 * Set a compatible MSR value explicitly to ensure
			 * that XER and CR bits are updated appropriately
			 */
			exp.msr = MSR_KERNEL;
			got.msr = MSR_KERNEL;

			rc = emulate_compute_instr(&got, instr, negative) != 0;
			अगर (negative) अणु
				/* skip executing inकाष्ठाion */
				passed = rc;
				जाओ prपूर्णांक;
			पूर्ण अन्यथा अगर (rc || execute_compute_instr(&exp, instr)) अणु
				passed = false;
				जाओ prपूर्णांक;
			पूर्ण

			/* Verअगरy GPR values */
			क्रम (k = 0; k < 32; k++) अणु
				ignore_gpr = flags & IGNORE_GPR(k);
				अगर (!ignore_gpr && exp.gpr[k] != got.gpr[k]) अणु
					passed = false;
					gpr_mismatch(k, exp.gpr[k], got.gpr[k]);
				पूर्ण
			पूर्ण

			/* Verअगरy LR value */
			अगर (exp.link != got.link) अणु
				passed = false;
				reg_mismatch("LR", exp.link, got.link);
			पूर्ण

			/* Verअगरy XER value */
			अगर (!ignore_xer && exp.xer != got.xer) अणु
				passed = false;
				reg_mismatch("XER", exp.xer, got.xer);
			पूर्ण

			/* Verअगरy CR value */
			अगर (!ignore_ccr && exp.ccr != got.ccr) अणु
				passed = false;
				reg_mismatch("CR", exp.ccr, got.ccr);
			पूर्ण

prपूर्णांक:
			show_result_with_descr(test->mnemonic,
					       test->subtests[j].descr,
					       passed ? "PASS" : "FAIL");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init test_emulate_step(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Running instruction emulation self-tests ...\n");
	run_tests_load_store();
	run_tests_compute();

	वापस 0;
पूर्ण
late_initcall(test_emulate_step);
