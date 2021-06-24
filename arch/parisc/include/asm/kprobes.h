<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/parisc/include/यंत्र/kprobes.h
 *
 * PA-RISC kprobes implementation
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 */

#अगर_अघोषित _PARISC_KPROBES_H
#घोषणा _PARISC_KPROBES_H

#अगर_घोषित CONFIG_KPROBES

#समावेश <यंत्र-generic/kprobes.h>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/notअगरier.h>

#घोषणा PARISC_KPROBES_BREAK_INSN	0x3ff801f
#घोषणा  __ARCH_WANT_KPROBES_INSN_SLOT
#घोषणा MAX_INSN_SIZE 1

प्रकार u32 kprobe_opcode_t;
काष्ठा kprobe;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);

#घोषणा flush_insn_slot(p) \
	flush_icache_range((अचिन्हित दीर्घ)&(p)->ainsn.insn[0], \
			   (अचिन्हित दीर्घ)&(p)->ainsn.insn[0] + \
			   माप(kprobe_opcode_t))

#घोषणा kretprobe_blacklist_size    0

काष्ठा arch_specअगरic_insn अणु
	kprobe_opcode_t *insn;
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
पूर्ण;

काष्ठा kprobe_ctlblk अणु
	अचिन्हित पूर्णांक kprobe_status;
	काष्ठा prev_kprobe prev_kprobe;
	अचिन्हित दीर्घ iaoq[2];
पूर्ण;

पूर्णांक __kprobes parisc_kprobe_अवरोध_handler(काष्ठा pt_regs *regs);
पूर्णांक __kprobes parisc_kprobe_ss_handler(काष्ठा pt_regs *regs);
अटल अंतरभूत पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _PARISC_KPROBES_H */
