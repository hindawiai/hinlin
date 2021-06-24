<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Marcin Nowakowski <marcin.nowakowski@mips.com>
 */

#अगर_अघोषित __PROBES_COMMON_H
#घोषणा __PROBES_COMMON_H

#समावेश <यंत्र/inst.h>

पूर्णांक __insn_is_compact_branch(जोड़ mips_inकाष्ठाion insn);

अटल अंतरभूत पूर्णांक __insn_has_delay_slot(स्थिर जोड़ mips_inकाष्ठाion insn)
अणु
	चयन (insn.i_क्रमmat.opcode) अणु
	/*
	 * jr and jalr are in r_क्रमmat क्रमmat.
	 */
	हाल spec_op:
		चयन (insn.r_क्रमmat.func) अणु
		हाल jalr_op:
		हाल jr_op:
			वापस 1;
		पूर्ण
		अवरोध;

	/*
	 * This group contains:
	 * bltz_op, bgez_op, bltzl_op, bgezl_op,
	 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
	 */
	हाल bcond_op:
		चयन (insn.i_क्रमmat.rt) अणु
		हाल bltz_op:
		हाल bltzl_op:
		हाल bgez_op:
		हाल bgezl_op:
		हाल bltzal_op:
		हाल bltzall_op:
		हाल bgezal_op:
		हाल bgezall_op:
		हाल bposge32_op:
			वापस 1;
		पूर्ण
		अवरोध;

	/*
	 * These are unconditional and in j_क्रमmat.
	 */
	हाल jal_op:
	हाल j_op:
	हाल beq_op:
	हाल beql_op:
	हाल bne_op:
	हाल bnel_op:
	हाल blez_op: /* not really i_क्रमmat */
	हाल blezl_op:
	हाल bgtz_op:
	हाल bgtzl_op:
		वापस 1;

	/*
	 * And now the FPA/cp1 branch inकाष्ठाions.
	 */
	हाल cop1_op:
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	हाल lwc2_op: /* This is bbit0 on Octeon */
	हाल ldc2_op: /* This is bbit032 on Octeon */
	हाल swc2_op: /* This is bbit1 on Octeon */
	हाल sdc2_op: /* This is bbit132 on Octeon */
#पूर्ण_अगर
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर  /* __PROBES_COMMON_H */
