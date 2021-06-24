<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/probes.h
 *
 * Original contents copied from arch/arm/include/यंत्र/kprobes.h
 * which contains the following notice...
 *
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#अगर_अघोषित _ASM_PROBES_H
#घोषणा _ASM_PROBES_H

#अगर_अघोषित __ASSEMBLY__

प्रकार u32 probes_opcode_t;

काष्ठा arch_probes_insn;
प्रकार व्योम (probes_insn_handler_t)(probes_opcode_t,
				     काष्ठा arch_probes_insn *,
				     काष्ठा pt_regs *);
प्रकार अचिन्हित दीर्घ (probes_check_cc)(अचिन्हित दीर्घ);
प्रकार व्योम (probes_insn_singlestep_t)(probes_opcode_t,
					काष्ठा arch_probes_insn *,
					काष्ठा pt_regs *);
प्रकार व्योम (probes_insn_fn_t)(व्योम);

/* Architecture specअगरic copy of original inकाष्ठाion. */
काष्ठा arch_probes_insn अणु
	probes_opcode_t			*insn;
	probes_insn_handler_t		*insn_handler;
	probes_check_cc			*insn_check_cc;
	probes_insn_singlestep_t	*insn_singlestep;
	probes_insn_fn_t		*insn_fn;
	पूर्णांक				stack_space;
	अचिन्हित दीर्घ			रेजिस्टर_usage_flags;
	bool				kprobe_direct_exec;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * We assume one inकाष्ठाion can consume at most 64 bytes stack, which is
 * 'push {r0-r15}'. Inकाष्ठाions consume more or unknown stack space like
 * 'str r0, [sp, #-80]' and 'str r0, [sp, r1]' should be prohibit to probe.
 */
#घोषणा MAX_STACK_SIZE			64

#पूर्ण_अगर
