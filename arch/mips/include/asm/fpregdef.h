<शैली गुरु>
/*
 * Definitions क्रम the FPU रेजिस्टर names
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1999 Ralf Baechle
 * Copyright (C) 1985 MIPS Computer Systems, Inc.
 * Copyright (C) 1990 - 1992, 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_FPREGDEF_H
#घोषणा _ASM_FPREGDEF_H

#समावेश <यंत्र/sgidefs.h>

/*
 * starting with binutils 2.24.51.20140729, MIPS binutils warn about mixing
 * hardभग्न and softभग्न object files.  The kernel build uses soft-भग्न by
 * शेष, so we also need to pass -msoft-भग्न aदीर्घ to GAS अगर it supports it.
 * But this in turn causes assembler errors in files which access hardभग्न
 * रेजिस्टरs.  We detect अगर GAS supports "-msoft-float" in the Makefile and
 * explicitly put ".set hardfloat" where भग्नing poपूर्णांक रेजिस्टरs are touched.
 */
#अगर_घोषित GAS_HAS_SET_HARDFLOAT
#घोषणा SET_HARDFLOAT .set hardभग्न
#अन्यथा
#घोषणा SET_HARDFLOAT
#पूर्ण_अगर

#अगर _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * These definitions only cover the R3000-ish 16/32 रेजिस्टर model.
 * But we're trying to be R3000 मित्रly anyway ...
 */
#घोषणा fv0	$f0	 /* वापस value */
#घोषणा fv0f	$f1
#घोषणा fv1	$f2
#घोषणा fv1f	$f3
#घोषणा fa0	$f12	 /* argument रेजिस्टरs */
#घोषणा fa0f	$f13
#घोषणा fa1	$f14
#घोषणा fa1f	$f15
#घोषणा ft0	$f4	 /* caller saved */
#घोषणा ft0f	$f5
#घोषणा ft1	$f6
#घोषणा ft1f	$f7
#घोषणा ft2	$f8
#घोषणा ft2f	$f9
#घोषणा ft3	$f10
#घोषणा ft3f	$f11
#घोषणा ft4	$f16
#घोषणा ft4f	$f17
#घोषणा ft5	$f18
#घोषणा ft5f	$f19
#घोषणा fs0	$f20	 /* callee saved */
#घोषणा fs0f	$f21
#घोषणा fs1	$f22
#घोषणा fs1f	$f23
#घोषणा fs2	$f24
#घोषणा fs2f	$f25
#घोषणा fs3	$f26
#घोषणा fs3f	$f27
#घोषणा fs4	$f28
#घोषणा fs4f	$f29
#घोषणा fs5	$f30
#घोषणा fs5f	$f31

#घोषणा fcr31	$31	 /* FPU status रेजिस्टर */

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#घोषणा fv0	$f0	/* वापस value */
#घोषणा fv1	$f2
#घोषणा fa0	$f12	/* argument रेजिस्टरs */
#घोषणा fa1	$f13
#घोषणा fa2	$f14
#घोषणा fa3	$f15
#घोषणा fa4	$f16
#घोषणा fa5	$f17
#घोषणा fa6	$f18
#घोषणा fa7	$f19
#घोषणा ft0	$f4	/* caller saved */
#घोषणा ft1	$f5
#घोषणा ft2	$f6
#घोषणा ft3	$f7
#घोषणा ft4	$f8
#घोषणा ft5	$f9
#घोषणा ft6	$f10
#घोषणा ft7	$f11
#घोषणा ft8	$f20
#घोषणा ft9	$f21
#घोषणा ft10	$f22
#घोषणा ft11	$f23
#घोषणा ft12	$f1
#घोषणा ft13	$f3
#घोषणा fs0	$f24	/* callee saved */
#घोषणा fs1	$f25
#घोषणा fs2	$f26
#घोषणा fs3	$f27
#घोषणा fs4	$f28
#घोषणा fs5	$f29
#घोषणा fs6	$f30
#घोषणा fs7	$f31

#घोषणा fcr31	$31

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#पूर्ण_अगर /* _ASM_FPREGDEF_H */
