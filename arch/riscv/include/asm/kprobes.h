<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copied from arch/arm64/include/यंत्र/kprobes.h
 *
 * Copyright (C) 2013 Linaro Limited
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_KPROBES_H
#घोषणा _ASM_RISCV_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>

#घोषणा __ARCH_WANT_KPROBES_INSN_SLOT
#घोषणा MAX_INSN_SIZE			2

#घोषणा flush_insn_slot(p)		करो अणु पूर्ण जबतक (0)
#घोषणा kretprobe_blacklist_size	0

#समावेश <यंत्र/probes.h>

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित पूर्णांक status;
पूर्ण;

/* Single step context क्रम kprobe */
काष्ठा kprobe_step_ctx अणु
	अचिन्हित दीर्घ ss_pending;
	अचिन्हित दीर्घ match_addr;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित पूर्णांक kprobe_status;
	अचिन्हित दीर्घ saved_status;
	काष्ठा prev_kprobe prev_kprobe;
	काष्ठा kprobe_step_ctx ss_ctx;
पूर्ण;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);
पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक trapnr);
bool kprobe_अवरोधpoपूर्णांक_handler(काष्ठा pt_regs *regs);
bool kprobe_single_step_handler(काष्ठा pt_regs *regs);
व्योम kretprobe_trampoline(व्योम);
व्योम __kprobes *trampoline_probe_handler(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _ASM_RISCV_KPROBES_H */
