<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/kernel/kprobes.h
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 *
 * Some contents moved here from arch/arm/include/यंत्र/kprobes.h which is
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#अगर_अघोषित _ARM_KERNEL_KPROBES_H
#घोषणा _ARM_KERNEL_KPROBES_H

#समावेश <यंत्र/kprobes.h>
#समावेश "../decode.h"

/*
 * These undefined inकाष्ठाions must be unique and
 * reserved solely क्रम kprobes' use.
 */
#घोषणा KPROBE_ARM_BREAKPOINT_INSTRUCTION	0x07f001f8
#घोषणा KPROBE_THUMB16_BREAKPOINT_INSTRUCTION	0xde18
#घोषणा KPROBE_THUMB32_BREAKPOINT_INSTRUCTION	0xf7f0a018

बाह्य व्योम kprobes_हटाओ_अवरोधpoपूर्णांक(व्योम *addr, अचिन्हित पूर्णांक insn);

क्रमागत probes_insn __kprobes
kprobe_decode_ldmsपंचांग(kprobe_opcode_t insn, काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h);

प्रकार क्रमागत probes_insn (kprobe_decode_insn_t)(probes_opcode_t,
						काष्ठा arch_probes_insn *,
						bool,
						स्थिर जोड़ decode_action *,
						स्थिर काष्ठा decode_checker *[]);

#अगर_घोषित CONFIG_THUMB2_KERNEL

बाह्य स्थिर जोड़ decode_action kprobes_t32_actions[];
बाह्य स्थिर जोड़ decode_action kprobes_t16_actions[];
बाह्य स्थिर काष्ठा decode_checker *kprobes_t32_checkers[];
बाह्य स्थिर काष्ठा decode_checker *kprobes_t16_checkers[];
#अन्यथा /* !CONFIG_THUMB2_KERNEL */

बाह्य स्थिर जोड़ decode_action kprobes_arm_actions[];
बाह्य स्थिर काष्ठा decode_checker *kprobes_arm_checkers[];

#पूर्ण_अगर

#पूर्ण_अगर /* _ARM_KERNEL_KPROBES_H */
