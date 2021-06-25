<शैली गुरु>
/*
 * Copyright (C) 2004, 2007  Maciej W. Rozycki
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित _ASM_COMPILER_H
#घोषणा _ASM_COMPILER_H

/*
 * With GCC 4.5 onwards we can use __builtin_unreachable to indicate to the
 * compiler that a particular code path will never be hit. This allows it to be
 * optimised out of the generated binary.
 *
 * Unक्रमtunately at least GCC 4.6.3 through 7.3.0 inclusive suffer from a bug
 * that can lead to inकाष्ठाions from beyond an unreachable statement being
 * incorrectly reordered पूर्णांकo earlier delay slots अगर the unreachable statement
 * is the only content of a हाल in a चयन statement. This can lead to
 * seemingly अक्रमom behaviour, such as invalid memory accesses from incorrectly
 * reordered loads or stores. See this potential GCC fix क्रम details:
 *
 *   https://gcc.gnu.org/ml/gcc-patches/2015-09/msg00360.hपंचांगl
 *
 * It is unclear whether GCC 8 onwards suffer from the same issue - nothing
 * relevant is mentioned in GCC 8 release notes and nothing obviously relevant
 * stands out in GCC commit logs, but these newer GCC versions generate very
 * dअगरferent code क्रम the testहाल which करोesn't exhibit the bug.
 *
 * GCC also handles stack allocation suboptimally when calling noवापस
 * functions or calling __builtin_unreachable():
 *
 *   https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82365
 *
 * We work around both of these issues by placing a अस्थिर यंत्र statement,
 * which GCC is prevented from reordering past, prior to __builtin_unreachable
 * calls.
 *
 * The .insn statement is required to ensure that any branches to the
 * statement, which sadly must be kept due to the यंत्र statement, are known to
 * be branches to code and satisfy linker requirements क्रम microMIPS kernels.
 */
#अघोषित barrier_beक्रमe_unreachable
#घोषणा barrier_beक्रमe_unreachable() यंत्र अस्थिर(".insn")

#घोषणा GCC_OFF_SMALL_ASM() "ZC"

#अगर_घोषित CONFIG_CPU_MIPSR6
#घोषणा MIPS_ISA_LEVEL "mips64r6"
#घोषणा MIPS_ISA_ARCH_LEVEL MIPS_ISA_LEVEL
#घोषणा MIPS_ISA_LEVEL_RAW mips64r6
#घोषणा MIPS_ISA_ARCH_LEVEL_RAW MIPS_ISA_LEVEL_RAW
#या_अगर defined(CONFIG_CPU_MIPSR5)
#घोषणा MIPS_ISA_LEVEL "mips64r5"
#घोषणा MIPS_ISA_ARCH_LEVEL MIPS_ISA_LEVEL
#घोषणा MIPS_ISA_LEVEL_RAW mips64r5
#घोषणा MIPS_ISA_ARCH_LEVEL_RAW MIPS_ISA_LEVEL_RAW
#अन्यथा
/* MIPS64 is a superset of MIPS32 */
#घोषणा MIPS_ISA_LEVEL "mips64r2"
#घोषणा MIPS_ISA_ARCH_LEVEL "arch=r4000"
#घोषणा MIPS_ISA_LEVEL_RAW mips64r2
#घोषणा MIPS_ISA_ARCH_LEVEL_RAW MIPS_ISA_LEVEL_RAW
#पूर्ण_अगर /* CONFIG_CPU_MIPSR6 */

#पूर्ण_अगर /* _ASM_COMPILER_H */
