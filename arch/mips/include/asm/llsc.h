<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Macros क्रम 32/64-bit neutral अंतरभूत assembler
 */

#अगर_अघोषित __ASM_LLSC_H
#घोषणा __ASM_LLSC_H

#समावेश <यंत्र/isa-rev.h>

#अगर _MIPS_SZLONG == 32
#घोषणा __LL		"ll	"
#घोषणा __SC		"sc	"
#घोषणा __INS		"ins	"
#घोषणा __EXT		"ext	"
#या_अगर _MIPS_SZLONG == 64
#घोषणा __LL		"lld	"
#घोषणा __SC		"scd	"
#घोषणा __INS		"dins	"
#घोषणा __EXT		"dext	"
#पूर्ण_अगर

/*
 * Using a branch-likely inकाष्ठाion to check the result of an sc inकाष्ठाion
 * works around a bug present in R10000 CPUs prior to revision 3.0 that could
 * cause ll-sc sequences to execute non-atomically.
 */
#अगर_घोषित CONFIG_WAR_R10000_LLSC
# define __SC_BEQZ "beqzl	"
#या_अगर MIPS_ISA_REV >= 6
# define __SC_BEQZ "beqzc	"
#अन्यथा
# define __SC_BEQZ "beqz	"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_LLSC_H  */
