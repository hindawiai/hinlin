<शैली गुरु>
/*
 *  vectors.c
 *
 *  Copyright (C) 1993, 1994 by Hamish Macकरोnald
 *
 *  68040 fixes by Michael Rausch
 *  68040 fixes by Martin Apel
 *  68040 fixes and ग_लिखोback by Riअक्षरd Zidlicky
 *  68060 fixes by Roman Hodek
 *  68060 fixes by Jesper Skov
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * Sets up all exception vectors
 */
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/traps.h>

/* assembler routines */
यंत्रlinkage व्योम प्रणाली_call(व्योम);
यंत्रlinkage व्योम buserr(व्योम);
यंत्रlinkage व्योम trap(व्योम);
यंत्रlinkage व्योम nmihandler(व्योम);
#अगर_घोषित CONFIG_M68KFPU_EMU
यंत्रlinkage व्योम fpu_emu(व्योम);
#पूर्ण_अगर

e_vector vectors[256];

/* nmi handler क्रम the Amiga */
यंत्र(".text\n"
    __ALIGN_STR "\n"
    "nmihandler: rte");

/*
 * this must be called very early as the kernel might
 * use some inकाष्ठाion that are emulated on the 060
 * and so we're prepared क्रम early probe attempts (e.g. nf_init).
 */
व्योम __init base_trap_init(व्योम)
अणु
	अगर (MACH_IS_SUN3X) अणु
		बाह्य e_vector *sun3x_prom_vbr;

		__यंत्र__ अस्थिर ("movec %%vbr, %0" : "=r" (sun3x_prom_vbr));
	पूर्ण

	/* setup the exception vector table */
	__यंत्र__ अस्थिर ("movec %0,%%vbr" : : "r" ((व्योम*)vectors));

	अगर (CPU_IS_060) अणु
		/* set up ISP entry poपूर्णांकs */
		यंत्रlinkage व्योम unimp_vec(व्योम) यंत्र ("_060_isp_unimp");

		vectors[VEC_UNIMPII] = unimp_vec;
	पूर्ण

	vectors[VEC_BUSERR] = buserr;
	vectors[VEC_ILLEGAL] = trap;
	vectors[VEC_SYS] = प्रणाली_call;
पूर्ण

व्योम __init trap_init (व्योम)
अणु
	पूर्णांक i;

	क्रम (i = VEC_SPUR; i <= VEC_INT7; i++)
		vectors[i] = bad_पूर्णांकhandler;

	क्रम (i = 0; i < VEC_USER; i++)
		अगर (!vectors[i])
			vectors[i] = trap;

	क्रम (i = VEC_USER; i < 256; i++)
		vectors[i] = bad_पूर्णांकhandler;

#अगर_घोषित CONFIG_M68KFPU_EMU
	अगर (FPU_IS_EMU)
		vectors[VEC_LINE11] = fpu_emu;
#पूर्ण_अगर

	अगर (CPU_IS_040 && !FPU_IS_EMU) अणु
		/* set up FPSP entry poपूर्णांकs */
		यंत्रlinkage व्योम dz_vec(व्योम) यंत्र ("dz");
		यंत्रlinkage व्योम inex_vec(व्योम) यंत्र ("inex");
		यंत्रlinkage व्योम ovfl_vec(व्योम) यंत्र ("ovfl");
		यंत्रlinkage व्योम unfl_vec(व्योम) यंत्र ("unfl");
		यंत्रlinkage व्योम snan_vec(व्योम) यंत्र ("snan");
		यंत्रlinkage व्योम operr_vec(व्योम) यंत्र ("operr");
		यंत्रlinkage व्योम bsun_vec(व्योम) यंत्र ("bsun");
		यंत्रlinkage व्योम fline_vec(व्योम) यंत्र ("fline");
		यंत्रlinkage व्योम unsupp_vec(व्योम) यंत्र ("unsupp");

		vectors[VEC_FPDIVZ] = dz_vec;
		vectors[VEC_FPIR] = inex_vec;
		vectors[VEC_FPOVER] = ovfl_vec;
		vectors[VEC_FPUNDER] = unfl_vec;
		vectors[VEC_FPन_अंक] = snan_vec;
		vectors[VEC_FPOE] = operr_vec;
		vectors[VEC_FPBRUC] = bsun_vec;
		vectors[VEC_LINE11] = fline_vec;
		vectors[VEC_FPUNSUP] = unsupp_vec;
	पूर्ण

	अगर (CPU_IS_060 && !FPU_IS_EMU) अणु
		/* set up IFPSP entry poपूर्णांकs */
		यंत्रlinkage व्योम snan_vec6(व्योम) यंत्र ("_060_fpsp_snan");
		यंत्रlinkage व्योम operr_vec6(व्योम) यंत्र ("_060_fpsp_operr");
		यंत्रlinkage व्योम ovfl_vec6(व्योम) यंत्र ("_060_fpsp_ovfl");
		यंत्रlinkage व्योम unfl_vec6(व्योम) यंत्र ("_060_fpsp_unfl");
		यंत्रlinkage व्योम dz_vec6(व्योम) यंत्र ("_060_fpsp_dz");
		यंत्रlinkage व्योम inex_vec6(व्योम) यंत्र ("_060_fpsp_inex");
		यंत्रlinkage व्योम fline_vec6(व्योम) यंत्र ("_060_fpsp_fline");
		यंत्रlinkage व्योम unsupp_vec6(व्योम) यंत्र ("_060_fpsp_unsupp");
		यंत्रlinkage व्योम effadd_vec6(व्योम) यंत्र ("_060_fpsp_effadd");

		vectors[VEC_FPन_अंक] = snan_vec6;
		vectors[VEC_FPOE] = operr_vec6;
		vectors[VEC_FPOVER] = ovfl_vec6;
		vectors[VEC_FPUNDER] = unfl_vec6;
		vectors[VEC_FPDIVZ] = dz_vec6;
		vectors[VEC_FPIR] = inex_vec6;
		vectors[VEC_LINE11] = fline_vec6;
		vectors[VEC_FPUNSUP] = unsupp_vec6;
		vectors[VEC_UNIMPEA] = effadd_vec6;
	पूर्ण

        /* अगर running on an amiga, make the NMI पूर्णांकerrupt करो nothing */
	अगर (MACH_IS_AMIGA) अणु
		vectors[VEC_INT7] = nmihandler;
	पूर्ण
पूर्ण

