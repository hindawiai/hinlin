<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2002, 2004, 2007 by Ralf Baechle
 * Copyright (C) 2007  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_WAR_H
#घोषणा _ASM_WAR_H

/*
 * Work around certain R4000 CPU errata (as implemented by GCC):
 *
 * - A द्विगुन-word or a variable shअगरt may give an incorrect result
 *   अगर executed immediately after starting an पूर्णांकeger भागision:
 *   "MIPS R4000PC/SC Errata, Processor Revision 2.2 and 3.0",
 *   erratum #28
 *   "MIPS R4000MC Errata, Processor Revision 2.2 and 3.0", erratum
 *   #19
 *
 * - A द्विगुन-word or a variable shअगरt may give an incorrect result
 *   अगर executed जबतक an पूर्णांकeger multiplication is in progress:
 *   "MIPS R4000PC/SC Errata, Processor Revision 2.2 and 3.0",
 *   errata #16 & #28
 *
 * - An पूर्णांकeger भागision may give an incorrect result अगर started in
 *   a delay slot of a taken branch or a jump:
 *   "MIPS R4000PC/SC Errata, Processor Revision 2.2 and 3.0",
 *   erratum #52
 */
#अगर_घोषित CONFIG_CPU_R4000_WORKAROUNDS
#घोषणा R4000_WAR 1
#अन्यथा
#घोषणा R4000_WAR 0
#पूर्ण_अगर

/*
 * Work around certain R4400 CPU errata (as implemented by GCC):
 *
 * - A द्विगुन-word or a variable shअगरt may give an incorrect result
 *   अगर executed immediately after starting an पूर्णांकeger भागision:
 *   "MIPS R4400MC Errata, Processor Revision 1.0", erratum #10
 *   "MIPS R4400MC Errata, Processor Revision 2.0 & 3.0", erratum #4
 */
#अगर_घोषित CONFIG_CPU_R4400_WORKAROUNDS
#घोषणा R4400_WAR 1
#अन्यथा
#घोषणा R4400_WAR 0
#पूर्ण_अगर

/*
 * Work around the "daddi" and "daddiu" CPU errata:
 *
 * - The `daddi' inकाष्ठाion fails to trap on overflow.
 *   "MIPS R4000PC/SC Errata, Processor Revision 2.2 and 3.0",
 *   erratum #23
 *
 * - The `daddiu' inकाष्ठाion can produce an incorrect result.
 *   "MIPS R4000PC/SC Errata, Processor Revision 2.2 and 3.0",
 *   erratum #41
 *   "MIPS R4000MC Errata, Processor Revision 2.2 and 3.0", erratum
 *   #15
 *   "MIPS R4400PC/SC Errata, Processor Revision 1.0", erratum #7
 *   "MIPS R4400MC Errata, Processor Revision 1.0", erratum #5
 */
#अगर_घोषित CONFIG_CPU_DADDI_WORKAROUNDS
#घोषणा DADDI_WAR 1
#अन्यथा
#घोषणा DADDI_WAR 0
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_WAR_H */
