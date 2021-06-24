<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_UPROBES_H
#घोषणा __ASM_UPROBES_H

#समावेश <linux/notअगरier.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/अवरोध.h>
#समावेश <यंत्र/inst.h>

/*
 * We want this to be defined as जोड़ mips_inकाष्ठाion but that makes the
 * generic code blow up.
 */
प्रकार u32 uprobe_opcode_t;

/*
 * Classic MIPS (note this implementation करोesn't consider microMIPS yet)
 * inकाष्ठाions are always 4 bytes but in order to deal with branches and
 * their delay slots, we treat inकाष्ठाions as having 8 bytes maximum.
 */
#घोषणा MAX_UINSN_BYTES			8
#घोषणा UPROBE_XOL_SLOT_BYTES		128	/* Max. cache line size */

#घोषणा UPROBE_BRK_UPROBE		0x000d000d	/* अवरोध 13 */
#घोषणा UPROBE_BRK_UPROBE_XOL		0x000e000d	/* अवरोध 14 */

#घोषणा UPROBE_SWBP_INSN		UPROBE_BRK_UPROBE
#घोषणा UPROBE_SWBP_INSN_SIZE		4

काष्ठा arch_uprobe अणु
	अचिन्हित दीर्घ	resume_epc;
	u32	insn[2];
	u32	ixol[2];
पूर्ण;

काष्ठा arch_uprobe_task अणु
	अचिन्हित दीर्घ saved_trap_nr;
पूर्ण;

#पूर्ण_अगर /* __ASM_UPROBES_H */
