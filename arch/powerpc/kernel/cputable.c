<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 *  Modअगरications क्रम ppc64:
 *      Copyright (C) 2003 Dave Engebretsen <engebret@us.ibm.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/jump_label.h>

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/prom.h>		/* क्रम PTRRELOC on ARCH=ppc */
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/setup.h>

अटल काष्ठा cpu_spec the_cpu_spec __पढ़ो_mostly;

काष्ठा cpu_spec* cur_cpu_spec __पढ़ो_mostly = शून्य;
EXPORT_SYMBOL(cur_cpu_spec);

/* The platक्रमm string corresponding to the real PVR */
स्थिर अक्षर *घातerpc_base_platक्रमm;

/* NOTE:
 * Unlike ppc32, ppc64 will only call this once क्रम the boot CPU, it's
 * the responsibility of the appropriate CPU save/restore functions to
 * eventually copy these settings over. Those save/restore aren't yet
 * part of the cputable though. That has to be fixed क्रम both ppc32
 * and ppc64
 */
#अगर_घोषित CONFIG_PPC32
बाह्य व्योम __setup_cpu_e500v1(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_e500v2(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_e500mc(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440ep(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440epx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440gx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440grx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440spe(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_440x5(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_460ex(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_460gt(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_460sx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *spec);
बाह्य व्योम __setup_cpu_apm821xx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec *spec);
बाह्य व्योम __setup_cpu_603(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_604(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_750(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_750cx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_750fx(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_7400(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_7410(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_745x(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
#पूर्ण_अगर /* CONFIG_PPC32 */
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/cpu_setup_घातer.h>
बाह्य व्योम __setup_cpu_ppc970(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_ppc970MP(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_pa6t(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __restore_cpu_pa6t(व्योम);
बाह्य व्योम __restore_cpu_ppc970(व्योम);
बाह्य दीर्घ __machine_check_early_realmode_p7(काष्ठा pt_regs *regs);
बाह्य दीर्घ __machine_check_early_realmode_p8(काष्ठा pt_regs *regs);
बाह्य दीर्घ __machine_check_early_realmode_p9(काष्ठा pt_regs *regs);
#पूर्ण_अगर /* CONFIG_PPC64 */
#अगर defined(CONFIG_E500)
बाह्य व्योम __setup_cpu_e5500(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __setup_cpu_e6500(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
बाह्य व्योम __restore_cpu_e5500(व्योम);
बाह्य व्योम __restore_cpu_e6500(व्योम);
#पूर्ण_अगर /* CONFIG_E500 */

/* This table only contains "desktop" CPUs, it need to be filled with embedded
 * ones as well...
 */
#घोषणा COMMON_USER		(PPC_FEATURE_32 | PPC_FEATURE_HAS_FPU | \
				 PPC_FEATURE_HAS_MMU)
#घोषणा COMMON_USER_PPC64	(COMMON_USER | PPC_FEATURE_64)
#घोषणा COMMON_USER_POWER4	(COMMON_USER_PPC64 | PPC_FEATURE_POWER4)
#घोषणा COMMON_USER_POWER5	(COMMON_USER_PPC64 | PPC_FEATURE_POWER5 |\
				 PPC_FEATURE_SMT | PPC_FEATURE_ICACHE_SNOOP)
#घोषणा COMMON_USER_POWER5_PLUS	(COMMON_USER_PPC64 | PPC_FEATURE_POWER5_PLUS|\
				 PPC_FEATURE_SMT | PPC_FEATURE_ICACHE_SNOOP)
#घोषणा COMMON_USER_POWER6	(COMMON_USER_PPC64 | PPC_FEATURE_ARCH_2_05 |\
				 PPC_FEATURE_SMT | PPC_FEATURE_ICACHE_SNOOP | \
				 PPC_FEATURE_TRUE_LE | \
				 PPC_FEATURE_PSERIES_PERFMON_COMPAT)
#घोषणा COMMON_USER_POWER7	(COMMON_USER_PPC64 | PPC_FEATURE_ARCH_2_06 |\
				 PPC_FEATURE_SMT | PPC_FEATURE_ICACHE_SNOOP | \
				 PPC_FEATURE_TRUE_LE | \
				 PPC_FEATURE_PSERIES_PERFMON_COMPAT)
#घोषणा COMMON_USER2_POWER7	(PPC_FEATURE2_DSCR)
#घोषणा COMMON_USER_POWER8	(COMMON_USER_PPC64 | PPC_FEATURE_ARCH_2_06 |\
				 PPC_FEATURE_SMT | PPC_FEATURE_ICACHE_SNOOP | \
				 PPC_FEATURE_TRUE_LE | \
				 PPC_FEATURE_PSERIES_PERFMON_COMPAT)
#घोषणा COMMON_USER2_POWER8	(PPC_FEATURE2_ARCH_2_07 | \
				 PPC_FEATURE2_HTM_COMP | \
				 PPC_FEATURE2_HTM_NOSC_COMP | \
				 PPC_FEATURE2_DSCR | \
				 PPC_FEATURE2_ISEL | PPC_FEATURE2_TAR | \
				 PPC_FEATURE2_VEC_CRYPTO)
#घोषणा COMMON_USER_PA6T	(COMMON_USER_PPC64 | PPC_FEATURE_PA6T |\
				 PPC_FEATURE_TRUE_LE | \
				 PPC_FEATURE_HAS_ALTIVEC_COMP)
#घोषणा COMMON_USER_POWER9	COMMON_USER_POWER8
#घोषणा COMMON_USER2_POWER9	(COMMON_USER2_POWER8 | \
				 PPC_FEATURE2_ARCH_3_00 | \
				 PPC_FEATURE2_HAS_IEEE128 | \
				 PPC_FEATURE2_DARN | \
				 PPC_FEATURE2_SCV)
#घोषणा COMMON_USER_POWER10	COMMON_USER_POWER9
#घोषणा COMMON_USER2_POWER10	(PPC_FEATURE2_ARCH_3_1 | \
				 PPC_FEATURE2_MMA | \
				 PPC_FEATURE2_ARCH_3_00 | \
				 PPC_FEATURE2_HAS_IEEE128 | \
				 PPC_FEATURE2_DARN | \
				 PPC_FEATURE2_SCV | \
				 PPC_FEATURE2_ARCH_2_07 | \
				 PPC_FEATURE2_DSCR | \
				 PPC_FEATURE2_ISEL | PPC_FEATURE2_TAR | \
				 PPC_FEATURE2_VEC_CRYPTO)

#अगर_घोषित CONFIG_PPC_BOOK3E_64
#घोषणा COMMON_USER_BOOKE	(COMMON_USER_PPC64 | PPC_FEATURE_BOOKE)
#अन्यथा
#घोषणा COMMON_USER_BOOKE	(PPC_FEATURE_32 | PPC_FEATURE_HAS_MMU | \
				 PPC_FEATURE_BOOKE)
#पूर्ण_अगर

अटल काष्ठा cpu_spec __initdata cpu_specs[] = अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अणु	/* PPC970 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00390000,
		.cpu_name		= "PPC970",
		.cpu_features		= CPU_FTRS_PPC970,
		.cpu_user_features	= COMMON_USER_POWER4 |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.mmu_features		= MMU_FTRS_PPC970,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 8,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_ppc970,
		.cpu_restore		= __restore_cpu_ppc970,
		.oprofile_cpu_type	= "ppc64/970",
		.platक्रमm		= "ppc970",
	पूर्ण,
	अणु	/* PPC970FX */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x003c0000,
		.cpu_name		= "PPC970FX",
		.cpu_features		= CPU_FTRS_PPC970,
		.cpu_user_features	= COMMON_USER_POWER4 |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.mmu_features		= MMU_FTRS_PPC970,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 8,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_ppc970,
		.cpu_restore		= __restore_cpu_ppc970,
		.oprofile_cpu_type	= "ppc64/970",
		.platक्रमm		= "ppc970",
	पूर्ण,
	अणु	/* PPC970MP DD1.0 - no DEEPNAP, use regular 970 init */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x00440100,
		.cpu_name		= "PPC970MP",
		.cpu_features		= CPU_FTRS_PPC970,
		.cpu_user_features	= COMMON_USER_POWER4 |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.mmu_features		= MMU_FTRS_PPC970,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 8,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_ppc970,
		.cpu_restore		= __restore_cpu_ppc970,
		.oprofile_cpu_type	= "ppc64/970MP",
		.platक्रमm		= "ppc970",
	पूर्ण,
	अणु	/* PPC970MP */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00440000,
		.cpu_name		= "PPC970MP",
		.cpu_features		= CPU_FTRS_PPC970,
		.cpu_user_features	= COMMON_USER_POWER4 |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.mmu_features		= MMU_FTRS_PPC970,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 8,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_ppc970MP,
		.cpu_restore		= __restore_cpu_ppc970,
		.oprofile_cpu_type	= "ppc64/970MP",
		.platक्रमm		= "ppc970",
	पूर्ण,
	अणु	/* PPC970GX */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00450000,
		.cpu_name		= "PPC970GX",
		.cpu_features		= CPU_FTRS_PPC970,
		.cpu_user_features	= COMMON_USER_POWER4 |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.mmu_features		= MMU_FTRS_PPC970,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 8,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_ppc970,
		.oprofile_cpu_type	= "ppc64/970",
		.platक्रमm		= "ppc970",
	पूर्ण,
	अणु	/* Power5 GR */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x003a0000,
		.cpu_name		= "POWER5 (gr)",
		.cpu_features		= CPU_FTRS_POWER5,
		.cpu_user_features	= COMMON_USER_POWER5,
		.mmu_features		= MMU_FTRS_POWER5,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power5",
		.platक्रमm		= "power5",
	पूर्ण,
	अणु	/* Power5++ */
		.pvr_mask		= 0xffffff00,
		.pvr_value		= 0x003b0300,
		.cpu_name		= "POWER5+ (gs)",
		.cpu_features		= CPU_FTRS_POWER5,
		.cpu_user_features	= COMMON_USER_POWER5_PLUS,
		.mmu_features		= MMU_FTRS_POWER5,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.oprofile_cpu_type	= "ppc64/power5++",
		.platक्रमm		= "power5+",
	पूर्ण,
	अणु	/* Power5 GS */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x003b0000,
		.cpu_name		= "POWER5+ (gs)",
		.cpu_features		= CPU_FTRS_POWER5,
		.cpu_user_features	= COMMON_USER_POWER5_PLUS,
		.mmu_features		= MMU_FTRS_POWER5,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power5+",
		.platक्रमm		= "power5+",
	पूर्ण,
	अणु	/* POWER6 in P5+ mode; 2.04-compliant processor */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000001,
		.cpu_name		= "POWER5+",
		.cpu_features		= CPU_FTRS_POWER5,
		.cpu_user_features	= COMMON_USER_POWER5_PLUS,
		.mmu_features		= MMU_FTRS_POWER5,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.platक्रमm		= "power5+",
	पूर्ण,
	अणु	/* Power6 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x003e0000,
		.cpu_name		= "POWER6 (raw)",
		.cpu_features		= CPU_FTRS_POWER6,
		.cpu_user_features	= COMMON_USER_POWER6 |
			PPC_FEATURE_POWER6_EXT,
		.mmu_features		= MMU_FTRS_POWER6,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power6",
		.platक्रमm		= "power6x",
	पूर्ण,
	अणु	/* 2.05-compliant processor, i.e. Power6 "architected" mode */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000002,
		.cpu_name		= "POWER6 (architected)",
		.cpu_features		= CPU_FTRS_POWER6,
		.cpu_user_features	= COMMON_USER_POWER6,
		.mmu_features		= MMU_FTRS_POWER6,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.platक्रमm		= "power6",
	पूर्ण,
	अणु	/* 2.06-compliant processor, i.e. Power7 "architected" mode */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000003,
		.cpu_name		= "POWER7 (architected)",
		.cpu_features		= CPU_FTRS_POWER7,
		.cpu_user_features	= COMMON_USER_POWER7,
		.cpu_user_features2	= COMMON_USER2_POWER7,
		.mmu_features		= MMU_FTRS_POWER7,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.cpu_setup		= __setup_cpu_घातer7,
		.cpu_restore		= __restore_cpu_घातer7,
		.machine_check_early	= __machine_check_early_realmode_p7,
		.platक्रमm		= "power7",
	पूर्ण,
	अणु	/* 2.07-compliant processor, i.e. Power8 "architected" mode */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000004,
		.cpu_name		= "POWER8 (architected)",
		.cpu_features		= CPU_FTRS_POWER8,
		.cpu_user_features	= COMMON_USER_POWER8,
		.cpu_user_features2	= COMMON_USER2_POWER8,
		.mmu_features		= MMU_FTRS_POWER8,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.cpu_setup		= __setup_cpu_घातer8,
		.cpu_restore		= __restore_cpu_घातer8,
		.machine_check_early	= __machine_check_early_realmode_p8,
		.platक्रमm		= "power8",
	पूर्ण,
	अणु	/* 3.00-compliant processor, i.e. Power9 "architected" mode */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000005,
		.cpu_name		= "POWER9 (architected)",
		.cpu_features		= CPU_FTRS_POWER9,
		.cpu_user_features	= COMMON_USER_POWER9,
		.cpu_user_features2	= COMMON_USER2_POWER9,
		.mmu_features		= MMU_FTRS_POWER9,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.cpu_setup		= __setup_cpu_घातer9,
		.cpu_restore		= __restore_cpu_घातer9,
		.platक्रमm		= "power9",
	पूर्ण,
	अणु	/* 3.1-compliant processor, i.e. Power10 "architected" mode */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x0f000006,
		.cpu_name		= "POWER10 (architected)",
		.cpu_features		= CPU_FTRS_POWER10,
		.cpu_user_features	= COMMON_USER_POWER10,
		.cpu_user_features2	= COMMON_USER2_POWER10,
		.mmu_features		= MMU_FTRS_POWER10,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.oprofile_cpu_type	= "ppc64/ibm-compat-v1",
		.cpu_setup		= __setup_cpu_घातer10,
		.cpu_restore		= __restore_cpu_घातer10,
		.platक्रमm		= "power10",
	पूर्ण,
	अणु	/* Power7 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x003f0000,
		.cpu_name		= "POWER7 (raw)",
		.cpu_features		= CPU_FTRS_POWER7,
		.cpu_user_features	= COMMON_USER_POWER7,
		.cpu_user_features2	= COMMON_USER2_POWER7,
		.mmu_features		= MMU_FTRS_POWER7,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power7",
		.cpu_setup		= __setup_cpu_घातer7,
		.cpu_restore		= __restore_cpu_घातer7,
		.machine_check_early	= __machine_check_early_realmode_p7,
		.platक्रमm		= "power7",
	पूर्ण,
	अणु	/* Power7+ */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x004A0000,
		.cpu_name		= "POWER7+ (raw)",
		.cpu_features		= CPU_FTRS_POWER7,
		.cpu_user_features	= COMMON_USER_POWER7,
		.cpu_user_features2	= COMMON_USER2_POWER7,
		.mmu_features		= MMU_FTRS_POWER7,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power7",
		.cpu_setup		= __setup_cpu_घातer7,
		.cpu_restore		= __restore_cpu_घातer7,
		.machine_check_early	= __machine_check_early_realmode_p7,
		.platक्रमm		= "power7+",
	पूर्ण,
	अणु	/* Power8E */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x004b0000,
		.cpu_name		= "POWER8E (raw)",
		.cpu_features		= CPU_FTRS_POWER8E,
		.cpu_user_features	= COMMON_USER_POWER8,
		.cpu_user_features2	= COMMON_USER2_POWER8,
		.mmu_features		= MMU_FTRS_POWER8,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power8",
		.cpu_setup		= __setup_cpu_घातer8,
		.cpu_restore		= __restore_cpu_घातer8,
		.machine_check_early	= __machine_check_early_realmode_p8,
		.platक्रमm		= "power8",
	पूर्ण,
	अणु	/* Power8NVL */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x004c0000,
		.cpu_name		= "POWER8NVL (raw)",
		.cpu_features		= CPU_FTRS_POWER8,
		.cpu_user_features	= COMMON_USER_POWER8,
		.cpu_user_features2	= COMMON_USER2_POWER8,
		.mmu_features		= MMU_FTRS_POWER8,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power8",
		.cpu_setup		= __setup_cpu_घातer8,
		.cpu_restore		= __restore_cpu_घातer8,
		.machine_check_early	= __machine_check_early_realmode_p8,
		.platक्रमm		= "power8",
	पूर्ण,
	अणु	/* Power8 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x004d0000,
		.cpu_name		= "POWER8 (raw)",
		.cpu_features		= CPU_FTRS_POWER8,
		.cpu_user_features	= COMMON_USER_POWER8,
		.cpu_user_features2	= COMMON_USER2_POWER8,
		.mmu_features		= MMU_FTRS_POWER8,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power8",
		.cpu_setup		= __setup_cpu_घातer8,
		.cpu_restore		= __restore_cpu_घातer8,
		.machine_check_early	= __machine_check_early_realmode_p8,
		.platक्रमm		= "power8",
	पूर्ण,
	अणु	/* Power9 DD2.0 */
		.pvr_mask		= 0xffffefff,
		.pvr_value		= 0x004e0200,
		.cpu_name		= "POWER9 (raw)",
		.cpu_features		= CPU_FTRS_POWER9_DD2_0,
		.cpu_user_features	= COMMON_USER_POWER9,
		.cpu_user_features2	= COMMON_USER2_POWER9,
		.mmu_features		= MMU_FTRS_POWER9,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power9",
		.cpu_setup		= __setup_cpu_घातer9,
		.cpu_restore		= __restore_cpu_घातer9,
		.machine_check_early	= __machine_check_early_realmode_p9,
		.platक्रमm		= "power9",
	पूर्ण,
	अणु	/* Power9 DD 2.1 */
		.pvr_mask		= 0xffffefff,
		.pvr_value		= 0x004e0201,
		.cpu_name		= "POWER9 (raw)",
		.cpu_features		= CPU_FTRS_POWER9_DD2_1,
		.cpu_user_features	= COMMON_USER_POWER9,
		.cpu_user_features2	= COMMON_USER2_POWER9,
		.mmu_features		= MMU_FTRS_POWER9,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power9",
		.cpu_setup		= __setup_cpu_घातer9,
		.cpu_restore		= __restore_cpu_घातer9,
		.machine_check_early	= __machine_check_early_realmode_p9,
		.platक्रमm		= "power9",
	पूर्ण,
	अणु	/* Power9 DD2.2 or later */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x004e0000,
		.cpu_name		= "POWER9 (raw)",
		.cpu_features		= CPU_FTRS_POWER9_DD2_2,
		.cpu_user_features	= COMMON_USER_POWER9,
		.cpu_user_features2	= COMMON_USER2_POWER9,
		.mmu_features		= MMU_FTRS_POWER9,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power9",
		.cpu_setup		= __setup_cpu_घातer9,
		.cpu_restore		= __restore_cpu_घातer9,
		.machine_check_early	= __machine_check_early_realmode_p9,
		.platक्रमm		= "power9",
	पूर्ण,
	अणु	/* Power10 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00800000,
		.cpu_name		= "POWER10 (raw)",
		.cpu_features		= CPU_FTRS_POWER10,
		.cpu_user_features	= COMMON_USER_POWER10,
		.cpu_user_features2	= COMMON_USER2_POWER10,
		.mmu_features		= MMU_FTRS_POWER10,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/power10",
		.cpu_setup		= __setup_cpu_घातer10,
		.cpu_restore		= __restore_cpu_घातer10,
		.machine_check_early	= __machine_check_early_realmode_p10,
		.platक्रमm		= "power10",
	पूर्ण,
	अणु	/* Cell Broadband Engine */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00700000,
		.cpu_name		= "Cell Broadband Engine",
		.cpu_features		= CPU_FTRS_CELL,
		.cpu_user_features	= COMMON_USER_PPC64 |
			PPC_FEATURE_CELL | PPC_FEATURE_HAS_ALTIVEC_COMP |
			PPC_FEATURE_SMT,
		.mmu_features		= MMU_FTRS_CELL,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.oprofile_cpu_type	= "ppc64/cell-be",
		.platक्रमm		= "ppc-cell-be",
	पूर्ण,
	अणु	/* PA Semi PA6T */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00900000,
		.cpu_name		= "PA6T",
		.cpu_features		= CPU_FTRS_PA6T,
		.cpu_user_features	= COMMON_USER_PA6T,
		.mmu_features		= MMU_FTRS_PA6T,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_PA6T,
		.cpu_setup		= __setup_cpu_pa6t,
		.cpu_restore		= __restore_cpu_pa6t,
		.oprofile_cpu_type	= "ppc64/pa6t",
		.platक्रमm		= "pa6t",
	पूर्ण,
	अणु	/* शेष match */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "POWER5 (compatible)",
		.cpu_features		= CPU_FTRS_COMPATIBLE,
		.cpu_user_features	= COMMON_USER_PPC64,
		.mmu_features		= MMU_FTRS_POWER,
		.icache_bsize		= 128,
		.dcache_bsize		= 128,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_IBM,
		.platक्रमm		= "power5",
	पूर्ण
#पूर्ण_अगर	/* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC32
#अगर_घोषित CONFIG_PPC_BOOK3S_32
#अगर_घोषित CONFIG_PPC_BOOK3S_604
	अणु	/* 604 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00040000,
		.cpu_name		= "604",
		.cpu_features		= CPU_FTRS_604,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 2,
		.cpu_setup		= __setup_cpu_604,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc604",
	पूर्ण,
	अणु	/* 604e */
		.pvr_mask		= 0xfffff000,
		.pvr_value		= 0x00090000,
		.cpu_name		= "604e",
		.cpu_features		= CPU_FTRS_604,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_604,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc604",
	पूर्ण,
	अणु	/* 604r */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00090000,
		.cpu_name		= "604r",
		.cpu_features		= CPU_FTRS_604,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_604,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc604",
	पूर्ण,
	अणु	/* 604ev */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x000a0000,
		.cpu_name		= "604ev",
		.cpu_features		= CPU_FTRS_604,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_604,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc604",
	पूर्ण,
	अणु	/* 740/750 (0x4202, करोn't support TAU ?) */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x00084202,
		.cpu_name		= "740/750",
		.cpu_features		= CPU_FTRS_740_NOTAU,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750CX (80100 and 8010x?) */
		.pvr_mask		= 0xfffffff0,
		.pvr_value		= 0x00080100,
		.cpu_name		= "750CX",
		.cpu_features		= CPU_FTRS_750,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.cpu_setup		= __setup_cpu_750cx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750CX (82201 and 82202) */
		.pvr_mask		= 0xfffffff0,
		.pvr_value		= 0x00082200,
		.cpu_name		= "750CX",
		.cpu_features		= CPU_FTRS_750,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750cx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750CXe (82214) */
		.pvr_mask		= 0xfffffff0,
		.pvr_value		= 0x00082210,
		.cpu_name		= "750CXe",
		.cpu_features		= CPU_FTRS_750,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750cx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750CXe "Gekko" (83214) */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x00083214,
		.cpu_name		= "750CXe",
		.cpu_features		= CPU_FTRS_750,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750cx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750CL (and "Broadway") */
		.pvr_mask		= 0xfffff0e0,
		.pvr_value		= 0x00087000,
		.cpu_name		= "750CL",
		.cpu_features		= CPU_FTRS_750CL,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
		.oprofile_cpu_type      = "ppc/750",
	पूर्ण,
	अणु	/* 745/755 */
		.pvr_mask		= 0xfffff000,
		.pvr_value		= 0x00083000,
		.cpu_name		= "745/755",
		.cpu_features		= CPU_FTRS_750,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 750FX rev 1.x */
		.pvr_mask		= 0xffffff00,
		.pvr_value		= 0x70000100,
		.cpu_name		= "750FX",
		.cpu_features		= CPU_FTRS_750FX1,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
		.oprofile_cpu_type      = "ppc/750",
	पूर्ण,
	अणु	/* 750FX rev 2.0 must disable HID0[DPM] */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x70000200,
		.cpu_name		= "750FX",
		.cpu_features		= CPU_FTRS_750FX2,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
		.oprofile_cpu_type      = "ppc/750",
	पूर्ण,
	अणु	/* 750FX (All revs except 2.0) */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x70000000,
		.cpu_name		= "750FX",
		.cpu_features		= CPU_FTRS_750FX,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750fx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
		.oprofile_cpu_type      = "ppc/750",
	पूर्ण,
	अणु	/* 750GX */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x70020000,
		.cpu_name		= "750GX",
		.cpu_features		= CPU_FTRS_750GX,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750fx,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
		.oprofile_cpu_type      = "ppc/750",
	पूर्ण,
	अणु	/* 740/750 (L2CR bit need fixup क्रम 740) */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00080000,
		.cpu_name		= "740/750",
		.cpu_features		= CPU_FTRS_740,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_IBM,
		.cpu_setup		= __setup_cpu_750,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc750",
	पूर्ण,
	अणु	/* 7400 rev 1.1 ? (no TAU) */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x000c1101,
		.cpu_name		= "7400 (1.1)",
		.cpu_features		= CPU_FTRS_7400_NOTAU,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_7400,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7400",
	पूर्ण,
	अणु	/* 7400 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x000c0000,
		.cpu_name		= "7400",
		.cpu_features		= CPU_FTRS_7400,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_7400,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7400",
	पूर्ण,
	अणु	/* 7410 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x800c0000,
		.cpu_name		= "7410",
		.cpu_features		= CPU_FTRS_7400,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_7410,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7400",
	पूर्ण,
	अणु	/* 7450 2.0 - no करोze/nap */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x80000200,
		.cpu_name		= "7450",
		.cpu_features		= CPU_FTRS_7450_20,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7450 2.1 */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x80000201,
		.cpu_name		= "7450",
		.cpu_features		= CPU_FTRS_7450_21,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7450 2.3 and newer */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80000000,
		.cpu_name		= "7450",
		.cpu_features		= CPU_FTRS_7450_23,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7455 rev 1.x */
		.pvr_mask		= 0xffffff00,
		.pvr_value		= 0x80010100,
		.cpu_name		= "7455",
		.cpu_features		= CPU_FTRS_7455_1,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7455 rev 2.0 */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x80010200,
		.cpu_name		= "7455",
		.cpu_features		= CPU_FTRS_7455_20,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7455 others */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80010000,
		.cpu_name		= "7455",
		.cpu_features		= CPU_FTRS_7455,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7447/7457 Rev 1.0 */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x80020100,
		.cpu_name		= "7447/7457",
		.cpu_features		= CPU_FTRS_7447_10,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7447/7457 Rev 1.1 */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x80020101,
		.cpu_name		= "7447/7457",
		.cpu_features		= CPU_FTRS_7447_10,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7447/7457 Rev 1.2 and later */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80020000,
		.cpu_name		= "7447/7457",
		.cpu_features		= CPU_FTRS_7447,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7447A */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80030000,
		.cpu_name		= "7447A",
		.cpu_features		= CPU_FTRS_7447A,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
	अणु	/* 7448 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80040000,
		.cpu_name		= "7448",
		.cpu_features		= CPU_FTRS_7448,
		.cpu_user_features	= COMMON_USER |
			PPC_FEATURE_HAS_ALTIVEC_COMP | PPC_FEATURE_PPC_LE,
		.mmu_features		= MMU_FTR_HPTE_TABLE | MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 6,
		.pmc_type		= PPC_PMC_G4,
		.cpu_setup		= __setup_cpu_745x,
		.oprofile_cpu_type      = "ppc/7450",
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc7450",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_604 */
#अगर_घोषित CONFIG_PPC_BOOK3S_603
	अणु	/* 603 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00030000,
		.cpu_name		= "603",
		.cpu_features		= CPU_FTRS_603,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= 0,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* 603e */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00060000,
		.cpu_name		= "603e",
		.cpu_features		= CPU_FTRS_603,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= 0,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* 603ev */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00070000,
		.cpu_name		= "603ev",
		.cpu_features		= CPU_FTRS_603,
		.cpu_user_features	= COMMON_USER | PPC_FEATURE_PPC_LE,
		.mmu_features		= 0,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* 82xx (8240, 8245, 8260 are all 603e cores) */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00810000,
		.cpu_name		= "82xx",
		.cpu_features		= CPU_FTRS_82XX,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= 0,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* All G2_LE (603e core, plus some) have the same pvr */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00820000,
		.cpu_name		= "G2_LE",
		.cpu_features		= CPU_FTRS_G2_LE,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
#अगर_घोषित CONFIG_PPC_83xx
	अणु	/* e300c1 (a 603e core, plus some) on 83xx */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00830000,
		.cpu_name		= "e300c1",
		.cpu_features		= CPU_FTRS_E300,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= MMU_FTR_USE_HIGH_BATS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_83xx,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* e300c2 (an e300c1 core, plus some, minus FPU) on 83xx */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00840000,
		.cpu_name		= "e300c2",
		.cpu_features		= CPU_FTRS_E300C2,
		.cpu_user_features	= PPC_FEATURE_32 | PPC_FEATURE_HAS_MMU,
		.mmu_features		= MMU_FTR_USE_HIGH_BATS |
			MMU_FTR_NEED_DTLB_SW_LRU,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_83xx,
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* e300c3 (e300c1, plus one IU, half cache size) on 83xx */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00850000,
		.cpu_name		= "e300c3",
		.cpu_features		= CPU_FTRS_E300,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= MMU_FTR_USE_HIGH_BATS |
			MMU_FTR_NEED_DTLB_SW_LRU,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_83xx,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e300",
		.platक्रमm		= "ppc603",
	पूर्ण,
	अणु	/* e300c4 (e300c1, plus one IU) */
		.pvr_mask		= 0x7fff0000,
		.pvr_value		= 0x00860000,
		.cpu_name		= "e300c4",
		.cpu_features		= CPU_FTRS_E300,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= MMU_FTR_USE_HIGH_BATS |
			MMU_FTR_NEED_DTLB_SW_LRU,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_603,
		.machine_check		= machine_check_83xx,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e300",
		.platक्रमm		= "ppc603",
	पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_603 */
#अगर_घोषित CONFIG_PPC_BOOK3S_604
	अणु	/* शेष match, we assume split I/D cache & TB (non-601)... */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "(generic PPC)",
		.cpu_features		= CPU_FTRS_CLASSIC32,
		.cpu_user_features	= COMMON_USER,
		.mmu_features		= MMU_FTR_HPTE_TABLE,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_generic,
		.platक्रमm		= "ppc603",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_604 */
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_32 */
#अगर_घोषित CONFIG_PPC_8xx
	अणु	/* 8xx */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= PVR_8xx,
		.cpu_name		= "8xx",
		/* CPU_FTR_MAYBE_CAN_DOZE is possible,
		 * अगर the 8xx code is there.... */
		.cpu_features		= CPU_FTRS_8XX,
		.cpu_user_features	= PPC_FEATURE_32 | PPC_FEATURE_HAS_MMU,
		.mmu_features		= MMU_FTR_TYPE_8xx,
		.icache_bsize		= 16,
		.dcache_bsize		= 16,
		.machine_check		= machine_check_8xx,
		.platक्रमm		= "ppc823",
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC_8xx */
#अगर_घोषित CONFIG_40x
	अणु	/* STB 04xxx */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x41810000,
		.cpu_name		= "STB04xxx",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* NP405L */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x41610000,
		.cpu_name		= "NP405L",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* NP4GS3 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x40B10000,
		.cpu_name		= "NP4GS3",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु   /* NP405H */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x41410000,
		.cpu_name		= "NP405H",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405GPr */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x50910000,
		.cpu_name		= "405GPr",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु   /* STBx25xx */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x51510000,
		.cpu_name		= "STBx25xx",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405LP */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x41F10000,
		.cpu_name		= "405LP",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 | PPC_FEATURE_HAS_MMU,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EP */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x51210000,
		.cpu_name		= "405EP",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EX Rev. A/B with Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910007,
		.cpu_name		= "405EX Rev. A/B",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EX Rev. C without Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x1291000d,
		.cpu_name		= "405EX Rev. C",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EX Rev. C with Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x1291000f,
		.cpu_name		= "405EX Rev. C",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EX Rev. D without Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910003,
		.cpu_name		= "405EX Rev. D",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EX Rev. D with Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910005,
		.cpu_name		= "405EX Rev. D",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EXr Rev. A/B without Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910001,
		.cpu_name		= "405EXr Rev. A/B",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EXr Rev. C without Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910009,
		.cpu_name		= "405EXr Rev. C",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EXr Rev. C with Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x1291000b,
		.cpu_name		= "405EXr Rev. C",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EXr Rev. D without Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910000,
		.cpu_name		= "405EXr Rev. D",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* 405EXr Rev. D with Security */
		.pvr_mask		= 0xffff000f,
		.pvr_value		= 0x12910002,
		.cpu_name		= "405EXr Rev. D",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु
		/* 405EZ */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x41510000,
		.cpu_name		= "405EZ",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* APM8018X */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x7ff11432,
		.cpu_name		= "APM8018X",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण,
	अणु	/* शेष match */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "(generic 40x PPC)",
		.cpu_features		= CPU_FTRS_40X,
		.cpu_user_features	= PPC_FEATURE_32 |
			PPC_FEATURE_HAS_MMU | PPC_FEATURE_HAS_4xxMAC,
		.mmu_features		= MMU_FTR_TYPE_40x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc405",
	पूर्ण

#पूर्ण_अगर /* CONFIG_40x */
#अगर_घोषित CONFIG_44x
#अगर_अघोषित CONFIG_PPC_47x
	अणु
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x40000850,
		.cpu_name		= "440GR Rev. A",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* Use logical PVR क्रम 440EP (logical pvr = pvr | 0x8) */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x40000858,
		.cpu_name		= "440EP Rev. A",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440ep,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x400008d3,
		.cpu_name		= "440GR Rev. B",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* Matches both physical and logical PVR क्रम 440EP (logical pvr = pvr | 0x8) */
		.pvr_mask		= 0xf0000ff7,
		.pvr_value		= 0x400008d4,
		.cpu_name		= "440EP Rev. C",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440ep,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* Use logical PVR क्रम 440EP (logical pvr = pvr | 0x8) */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x400008db,
		.cpu_name		= "440EP Rev. B",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440ep,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440GRX */
		.pvr_mask		= 0xf0000ffb,
		.pvr_value		= 0x200008D0,
		.cpu_name		= "440GRX",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440grx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* Use logical PVR क्रम 440EPx (logical pvr = pvr | 0x8) */
		.pvr_mask		= 0xf0000ffb,
		.pvr_value		= 0x200008D8,
		.cpu_name		= "440EPX",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440epx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु	/* 440GP Rev. B */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x40000440,
		.cpu_name		= "440GP Rev. B",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440gp",
	पूर्ण,
	अणु	/* 440GP Rev. C */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x40000481,
		.cpu_name		= "440GP Rev. C",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440gp",
	पूर्ण,
	अणु /* 440GX Rev. A */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x50000850,
		.cpu_name		= "440GX Rev. A",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440gx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440GX Rev. B */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x50000851,
		.cpu_name		= "440GX Rev. B",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440gx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440GX Rev. C */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x50000892,
		.cpu_name		= "440GX Rev. C",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440gx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440GX Rev. F */
		.pvr_mask		= 0xf0000fff,
		.pvr_value		= 0x50000894,
		.cpu_name		= "440GX Rev. F",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440gx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440SP Rev. A */
		.pvr_mask		= 0xfff00fff,
		.pvr_value		= 0x53200891,
		.cpu_name		= "440SP Rev. A",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 440SPe Rev. A */
		.pvr_mask               = 0xfff00fff,
		.pvr_value              = 0x53400890,
		.cpu_name               = "440SPe Rev. A",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features      = COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize           = 32,
		.dcache_bsize           = 32,
		.cpu_setup		= __setup_cpu_440spe,
		.machine_check		= machine_check_440A,
		.platक्रमm               = "ppc440",
	पूर्ण,
	अणु /* 440SPe Rev. B */
		.pvr_mask		= 0xfff00fff,
		.pvr_value		= 0x53400891,
		.cpu_name		= "440SPe Rev. B",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_440spe,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 460EX */
		.pvr_mask		= 0xffff0006,
		.pvr_value		= 0x13020002,
		.cpu_name		= "460EX",
		.cpu_features		= CPU_FTRS_440x6,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_460ex,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 460EX Rev B */
		.pvr_mask		= 0xffff0007,
		.pvr_value		= 0x13020004,
		.cpu_name		= "460EX Rev. B",
		.cpu_features		= CPU_FTRS_440x6,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_460ex,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 460GT */
		.pvr_mask		= 0xffff0006,
		.pvr_value		= 0x13020000,
		.cpu_name		= "460GT",
		.cpu_features		= CPU_FTRS_440x6,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_460gt,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 460GT Rev B */
		.pvr_mask		= 0xffff0007,
		.pvr_value		= 0x13020005,
		.cpu_name		= "460GT Rev. B",
		.cpu_features		= CPU_FTRS_440x6,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_460gt,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 460SX */
		.pvr_mask		= 0xffffff00,
		.pvr_value		= 0x13541800,
		.cpu_name		= "460SX",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_460sx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु /* 464 in APM821xx */
		.pvr_mask		= 0xfffffff0,
		.pvr_value		= 0x12C41C80,
		.cpu_name		= "APM821XX",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.cpu_setup		= __setup_cpu_apm821xx,
		.machine_check		= machine_check_440A,
		.platक्रमm		= "ppc440",
	पूर्ण,
	अणु	/* शेष match */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "(generic 44x PPC)",
		.cpu_features		= CPU_FTRS_44X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_44x,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_4xx,
		.platक्रमm		= "ppc440",
	पूर्ण
#अन्यथा /* CONFIG_PPC_47x */
	अणु /* 476 DD2 core */
		.pvr_mask		= 0xffffffff,
		.pvr_value		= 0x11a52080,
		.cpu_name		= "476",
		.cpu_features		= CPU_FTRS_47X | CPU_FTR_476_DD2,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_47x |
			MMU_FTR_USE_TLBIVAX_BCAST | MMU_FTR_LOCK_BCAST_INVAL,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.platक्रमm		= "ppc470",
	पूर्ण,
	अणु /* 476fpe */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x7ff50000,
		.cpu_name		= "476fpe",
		.cpu_features		= CPU_FTRS_47X | CPU_FTR_476_DD2,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_47x |
			MMU_FTR_USE_TLBIVAX_BCAST | MMU_FTR_LOCK_BCAST_INVAL,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.platक्रमm		= "ppc470",
	पूर्ण,
	अणु /* 476 iss */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x00050000,
		.cpu_name		= "476",
		.cpu_features		= CPU_FTRS_47X,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_47x |
			MMU_FTR_USE_TLBIVAX_BCAST | MMU_FTR_LOCK_BCAST_INVAL,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.platक्रमm		= "ppc470",
	पूर्ण,
	अणु /* 476 others */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x11a50000,
		.cpu_name		= "476",
		.cpu_features		= CPU_FTRS_47X,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_FPU,
		.mmu_features		= MMU_FTR_TYPE_47x |
			MMU_FTR_USE_TLBIVAX_BCAST | MMU_FTR_LOCK_BCAST_INVAL,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.platक्रमm		= "ppc470",
	पूर्ण,
	अणु	/* शेष match */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "(generic 47x PPC)",
		.cpu_features		= CPU_FTRS_47X,
		.cpu_user_features	= COMMON_USER_BOOKE,
		.mmu_features		= MMU_FTR_TYPE_47x,
		.icache_bsize		= 32,
		.dcache_bsize		= 128,
		.machine_check		= machine_check_47x,
		.platक्रमm		= "ppc470",
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_47x */
#पूर्ण_अगर /* CONFIG_44x */
#पूर्ण_अगर /* CONFIG_PPC32 */
#अगर_घोषित CONFIG_E500
#अगर_घोषित CONFIG_PPC32
#अगर_अघोषित CONFIG_PPC_E500MC
	अणु	/* e500 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80200000,
		.cpu_name		= "e500",
		.cpu_features		= CPU_FTRS_E500,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_SPE_COMP |
			PPC_FEATURE_HAS_EFP_SINGLE_COMP,
		.cpu_user_features2	= PPC_FEATURE2_ISEL,
		.mmu_features		= MMU_FTR_TYPE_FSL_E,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e500",
		.cpu_setup		= __setup_cpu_e500v1,
		.machine_check		= machine_check_e500,
		.platक्रमm		= "ppc8540",
	पूर्ण,
	अणु	/* e500v2 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80210000,
		.cpu_name		= "e500v2",
		.cpu_features		= CPU_FTRS_E500_2,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_SPE_COMP |
			PPC_FEATURE_HAS_EFP_SINGLE_COMP |
			PPC_FEATURE_HAS_EFP_DOUBLE_COMP,
		.cpu_user_features2	= PPC_FEATURE2_ISEL,
		.mmu_features		= MMU_FTR_TYPE_FSL_E | MMU_FTR_BIG_PHYS,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e500",
		.cpu_setup		= __setup_cpu_e500v2,
		.machine_check		= machine_check_e500,
		.platक्रमm		= "ppc8548",
		.cpu_करोwn_flush		= cpu_करोwn_flush_e500v2,
	पूर्ण,
#अन्यथा
	अणु	/* e500mc */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80230000,
		.cpu_name		= "e500mc",
		.cpu_features		= CPU_FTRS_E500MC,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.cpu_user_features2	= PPC_FEATURE2_ISEL,
		.mmu_features		= MMU_FTR_TYPE_FSL_E | MMU_FTR_BIG_PHYS |
			MMU_FTR_USE_TLBILX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e500mc",
		.cpu_setup		= __setup_cpu_e500mc,
		.machine_check		= machine_check_e500mc,
		.platक्रमm		= "ppce500mc",
		.cpu_करोwn_flush		= cpu_करोwn_flush_e500mc,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC_E500MC */
#पूर्ण_अगर /* CONFIG_PPC32 */
#अगर_घोषित CONFIG_PPC_E500MC
	अणु	/* e5500 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80240000,
		.cpu_name		= "e5500",
		.cpu_features		= CPU_FTRS_E5500,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU,
		.cpu_user_features2	= PPC_FEATURE2_ISEL,
		.mmu_features		= MMU_FTR_TYPE_FSL_E | MMU_FTR_BIG_PHYS |
			MMU_FTR_USE_TLBILX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 4,
		.oprofile_cpu_type	= "ppc/e500mc",
		.cpu_setup		= __setup_cpu_e5500,
#अगर_अघोषित CONFIG_PPC32
		.cpu_restore		= __restore_cpu_e5500,
#पूर्ण_अगर
		.machine_check		= machine_check_e500mc,
		.platक्रमm		= "ppce5500",
		.cpu_करोwn_flush		= cpu_करोwn_flush_e5500,
	पूर्ण,
	अणु	/* e6500 */
		.pvr_mask		= 0xffff0000,
		.pvr_value		= 0x80400000,
		.cpu_name		= "e6500",
		.cpu_features		= CPU_FTRS_E6500,
		.cpu_user_features	= COMMON_USER_BOOKE | PPC_FEATURE_HAS_FPU |
			PPC_FEATURE_HAS_ALTIVEC_COMP,
		.cpu_user_features2	= PPC_FEATURE2_ISEL,
		.mmu_features		= MMU_FTR_TYPE_FSL_E | MMU_FTR_BIG_PHYS |
			MMU_FTR_USE_TLBILX,
		.icache_bsize		= 64,
		.dcache_bsize		= 64,
		.num_pmcs		= 6,
		.oprofile_cpu_type	= "ppc/e6500",
		.cpu_setup		= __setup_cpu_e6500,
#अगर_अघोषित CONFIG_PPC32
		.cpu_restore		= __restore_cpu_e6500,
#पूर्ण_अगर
		.machine_check		= machine_check_e500mc,
		.platक्रमm		= "ppce6500",
		.cpu_करोwn_flush		= cpu_करोwn_flush_e6500,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_PPC_E500MC */
#अगर_घोषित CONFIG_PPC32
	अणु	/* शेष match */
		.pvr_mask		= 0x00000000,
		.pvr_value		= 0x00000000,
		.cpu_name		= "(generic E500 PPC)",
		.cpu_features		= CPU_FTRS_E500,
		.cpu_user_features	= COMMON_USER_BOOKE |
			PPC_FEATURE_HAS_SPE_COMP |
			PPC_FEATURE_HAS_EFP_SINGLE_COMP,
		.mmu_features		= MMU_FTR_TYPE_FSL_E,
		.icache_bsize		= 32,
		.dcache_bsize		= 32,
		.machine_check		= machine_check_e500,
		.platक्रमm		= "powerpc",
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */
#पूर्ण_अगर /* CONFIG_E500 */
पूर्ण;

व्योम __init set_cur_cpu_spec(काष्ठा cpu_spec *s)
अणु
	काष्ठा cpu_spec *t = &the_cpu_spec;

	t = PTRRELOC(t);
	/*
	 * use स_नकल() instead of *t = *s so that GCC replaces it
	 * by __स_नकल() when KASAN is active
	 */
	स_नकल(t, s, माप(*t));

	*PTRRELOC(&cur_cpu_spec) = &the_cpu_spec;
पूर्ण

अटल काष्ठा cpu_spec * __init setup_cpu_spec(अचिन्हित दीर्घ offset,
					       काष्ठा cpu_spec *s)
अणु
	काष्ठा cpu_spec *t = &the_cpu_spec;
	काष्ठा cpu_spec old;

	t = PTRRELOC(t);
	old = *t;

	/*
	 * Copy everything, then करो fixups. Use स_नकल() instead of *t = *s
	 * so that GCC replaces it by __स_नकल() when KASAN is active
	 */
	स_नकल(t, s, माप(*t));

	/*
	 * If we are overriding a previous value derived from the real
	 * PVR with a new value obtained using a logical PVR value,
	 * करोn't modअगरy the perक्रमmance monitor fields.
	 */
	अगर (old.num_pmcs && !s->num_pmcs) अणु
		t->num_pmcs = old.num_pmcs;
		t->pmc_type = old.pmc_type;

		/*
		 * If we have passed through this logic once beक्रमe and
		 * have pulled the शेष हाल because the real PVR was
		 * not found inside cpu_specs[], then we are possibly
		 * running in compatibility mode. In that हाल, let the
		 * oprofiler know which set of compatibility counters to
		 * pull from by making sure the oprofile_cpu_type string
		 * is set to that of compatibility mode. If the
		 * oprofile_cpu_type alपढ़ोy has a value, then we are
		 * possibly overriding a real PVR with a logical one,
		 * and, in that हाल, keep the current value क्रम
		 * oprofile_cpu_type. Futhermore, let's ensure that the
		 * fix क्रम the PMAO bug is enabled on compatibility mode.
		 */
		अगर (old.oprofile_cpu_type != शून्य) अणु
			t->oprofile_cpu_type = old.oprofile_cpu_type;
			t->cpu_features |= old.cpu_features & CPU_FTR_PMAO_BUG;
		पूर्ण
	पूर्ण

	*PTRRELOC(&cur_cpu_spec) = &the_cpu_spec;

	/*
	 * Set the base platक्रमm string once; assumes
	 * we're called with real pvr first.
	 */
	अगर (*PTRRELOC(&घातerpc_base_platक्रमm) == शून्य)
		*PTRRELOC(&घातerpc_base_platक्रमm) = t->platक्रमm;

#अगर defined(CONFIG_PPC64) || defined(CONFIG_BOOKE)
	/* ppc64 and booke expect identअगरy_cpu to also call setup_cpu क्रम
	 * that processor. I will consolidate that at a later समय, क्रम now,
	 * just use #अगर_घोषित. We also करोn't need to PTRRELOC the function
	 * poपूर्णांकer on ppc64 and booke as we are running at 0 in real mode
	 * on ppc64 and reloc_offset is always 0 on booke.
	 */
	अगर (t->cpu_setup) अणु
		t->cpu_setup(offset, t);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 || CONFIG_BOOKE */

	वापस t;
पूर्ण

काष्ठा cpu_spec * __init identअगरy_cpu(अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक pvr)
अणु
	काष्ठा cpu_spec *s = cpu_specs;
	पूर्णांक i;

	s = PTRRELOC(s);

	क्रम (i = 0; i < ARRAY_SIZE(cpu_specs); i++,s++) अणु
		अगर ((pvr & s->pvr_mask) == s->pvr_value)
			वापस setup_cpu_spec(offset, s);
	पूर्ण

	BUG();

	वापस शून्य;
पूर्ण

/*
 * Used by cpufeatures to get the name क्रम CPUs with a PVR table.
 * If they करोn't hae a PVR table, cpufeatures माला_लो the name from
 * cpu device-tree node.
 */
व्योम __init identअगरy_cpu_name(अचिन्हित पूर्णांक pvr)
अणु
	काष्ठा cpu_spec *s = cpu_specs;
	काष्ठा cpu_spec *t = &the_cpu_spec;
	पूर्णांक i;

	s = PTRRELOC(s);
	t = PTRRELOC(t);

	क्रम (i = 0; i < ARRAY_SIZE(cpu_specs); i++,s++) अणु
		अगर ((pvr & s->pvr_mask) == s->pvr_value) अणु
			t->cpu_name = s->cpu_name;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECKS
काष्ठा अटल_key_true cpu_feature_keys[NUM_CPU_FTR_KEYS] = अणु
			[0 ... NUM_CPU_FTR_KEYS - 1] = STATIC_KEY_TRUE_INIT
पूर्ण;
EXPORT_SYMBOL_GPL(cpu_feature_keys);

व्योम __init cpu_feature_keys_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CPU_FTR_KEYS; i++) अणु
		अचिन्हित दीर्घ f = 1ul << i;

		अगर (!(cur_cpu_spec->cpu_features & f))
			अटल_branch_disable(&cpu_feature_keys[i]);
	पूर्ण
पूर्ण

काष्ठा अटल_key_true mmu_feature_keys[NUM_MMU_FTR_KEYS] = अणु
			[0 ... NUM_MMU_FTR_KEYS - 1] = STATIC_KEY_TRUE_INIT
पूर्ण;
EXPORT_SYMBOL_GPL(mmu_feature_keys);

व्योम __init mmu_feature_keys_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_MMU_FTR_KEYS; i++) अणु
		अचिन्हित दीर्घ f = 1ul << i;

		अगर (!(cur_cpu_spec->mmu_features & f))
			अटल_branch_disable(&mmu_feature_keys[i]);
	पूर्ण
पूर्ण
#पूर्ण_अगर
