<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2010 Cavium Networks, Inc.
 */

#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/inst.h>

/*
 * Define parameters क्रम the standard MIPS and the microMIPS jump
 * inकाष्ठाion encoding respectively:
 *
 * - the ISA bit of the target, either 0 or 1 respectively,
 *
 * - the amount the jump target address is shअगरted right to fit in the
 *   immediate field of the machine inकाष्ठाion, either 2 or 1,
 *
 * - the mask determining the size of the jump region relative to the
 *   delay-slot inकाष्ठाion, either 256MB or 128MB,
 *
 * - the jump target alignment, either 4 or 2 bytes.
 */
#घोषणा J_ISA_BIT	IS_ENABLED(CONFIG_CPU_MICROMIPS)
#घोषणा J_RANGE_SHIFT	(2 - J_ISA_BIT)
#घोषणा J_RANGE_MASK	((1ul << (26 + J_RANGE_SHIFT)) - 1)
#घोषणा J_ALIGN_MASK	((1ul << J_RANGE_SHIFT) - 1)

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *e,
			       क्रमागत jump_label_type type)
अणु
	जोड़ mips_inकाष्ठाion *insn_p;
	जोड़ mips_inकाष्ठाion insn;
	दीर्घ offset;

	insn_p = (जोड़ mips_inकाष्ठाion *)msk_isa16_mode(e->code);

	/* Target must have the right alignment and ISA must be preserved. */
	BUG_ON((e->target & J_ALIGN_MASK) != J_ISA_BIT);

	अगर (type == JUMP_LABEL_JMP) अणु
		अगर (!IS_ENABLED(CONFIG_CPU_MICROMIPS) && MIPS_ISA_REV >= 6) अणु
			offset = e->target - ((अचिन्हित दीर्घ)insn_p + 4);
			offset >>= 2;

			/*
			 * The branch offset must fit in the inकाष्ठाion's 26
			 * bit field.
			 */
			WARN_ON((offset >= BIT(25)) ||
				(offset < -(दीर्घ)BIT(25)));

			insn.j_क्रमmat.opcode = bc6_op;
			insn.j_क्रमmat.target = offset;
		पूर्ण अन्यथा अणु
			/*
			 * Jump only works within an aligned region its delay
			 * slot is in.
			 */
			WARN_ON((e->target & ~J_RANGE_MASK) !=
				((e->code + 4) & ~J_RANGE_MASK));

			insn.j_क्रमmat.opcode = J_ISA_BIT ? mm_j32_op : j_op;
			insn.j_क्रमmat.target = e->target >> J_RANGE_SHIFT;
		पूर्ण
	पूर्ण अन्यथा अणु
		insn.word = 0; /* nop */
	पूर्ण

	mutex_lock(&text_mutex);
	अगर (IS_ENABLED(CONFIG_CPU_MICROMIPS)) अणु
		insn_p->halfword[0] = insn.word >> 16;
		insn_p->halfword[1] = insn.word;
	पूर्ण अन्यथा
		*insn_p = insn;

	flush_icache_range((अचिन्हित दीर्घ)insn_p,
			   (अचिन्हित दीर्घ)insn_p + माप(*insn_p));

	mutex_unlock(&text_mutex);
पूर्ण
