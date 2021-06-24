<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/kernel/probes/decode-insn.h
 *
 * Copyright (C) 2013 Linaro Limited.
 */

#अगर_अघोषित _ARM_KERNEL_KPROBES_ARM64_H
#घोषणा _ARM_KERNEL_KPROBES_ARM64_H

#समावेश <यंत्र/kprobes.h>

/*
 * ARM strongly recommends a limit of 128 bytes between LoadExcl and
 * StoreExcl inकाष्ठाions in a single thपढ़ो of execution. So keep the
 * max atomic context size as 32.
 */
#घोषणा MAX_ATOMIC_CONTEXT_SIZE	(128 / माप(kprobe_opcode_t))

क्रमागत probe_insn अणु
	INSN_REJECTED,
	INSN_GOOD_NO_SLOT,
	INSN_GOOD,
पूर्ण;

#अगर_घोषित CONFIG_KPROBES
क्रमागत probe_insn __kprobes
arm_kprobe_decode_insn(kprobe_opcode_t *addr, काष्ठा arch_specअगरic_insn *asi);
#पूर्ण_अगर
क्रमागत probe_insn __kprobes
arm_probe_decode_insn(probe_opcode_t insn, काष्ठा arch_probe_insn *asi);

#पूर्ण_अगर /* _ARM_KERNEL_KPROBES_ARM64_H */
