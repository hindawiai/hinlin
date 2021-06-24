<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <यंत्र/sections.h>

#समावेश "decode-insn.h"
#समावेश "simulate-insn.h"

/* Return:
 *   INSN_REJECTED     If inकाष्ठाion is one not allowed to kprobe,
 *   INSN_GOOD_NO_SLOT If inकाष्ठाion is supported but करोesn't use its slot.
 */
क्रमागत probe_insn __kprobes
csky_probe_decode_insn(probe_opcode_t *addr, काष्ठा arch_probe_insn *api)
अणु
	probe_opcode_t insn = le32_to_cpu(*addr);

	CSKY_INSN_SET_SIMULATE(br16,		insn);
	CSKY_INSN_SET_SIMULATE(bt16,		insn);
	CSKY_INSN_SET_SIMULATE(bf16,		insn);
	CSKY_INSN_SET_SIMULATE(jmp16,		insn);
	CSKY_INSN_SET_SIMULATE(jsr16,		insn);
	CSKY_INSN_SET_SIMULATE(lrw16,		insn);
	CSKY_INSN_SET_SIMULATE(pop16,		insn);

	CSKY_INSN_SET_SIMULATE(br32,		insn);
	CSKY_INSN_SET_SIMULATE(bt32,		insn);
	CSKY_INSN_SET_SIMULATE(bf32,		insn);
	CSKY_INSN_SET_SIMULATE(jmp32,		insn);
	CSKY_INSN_SET_SIMULATE(jsr32,		insn);
	CSKY_INSN_SET_SIMULATE(lrw32,		insn);
	CSKY_INSN_SET_SIMULATE(pop32,		insn);

	CSKY_INSN_SET_SIMULATE(bez32,		insn);
	CSKY_INSN_SET_SIMULATE(bnez32,		insn);
	CSKY_INSN_SET_SIMULATE(bnezad32,	insn);
	CSKY_INSN_SET_SIMULATE(bhsz32,		insn);
	CSKY_INSN_SET_SIMULATE(bhz32,		insn);
	CSKY_INSN_SET_SIMULATE(blsz32,		insn);
	CSKY_INSN_SET_SIMULATE(blz32,		insn);
	CSKY_INSN_SET_SIMULATE(bsr32,		insn);
	CSKY_INSN_SET_SIMULATE(jmpi32,		insn);
	CSKY_INSN_SET_SIMULATE(jsri32,		insn);

	वापस INSN_GOOD;
पूर्ण
