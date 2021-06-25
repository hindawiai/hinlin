<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/kprobes.h
 *
 * Copyright (C) 2006, 2007 Motorola Inc.
 */

#अगर_अघोषित _ARM_KPROBES_H
#घोषणा _ARM_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/notअगरier.h>

#घोषणा __ARCH_WANT_KPROBES_INSN_SLOT
#घोषणा MAX_INSN_SIZE			2

#घोषणा flush_insn_slot(p)		करो अणु पूर्ण जबतक (0)
#घोषणा kretprobe_blacklist_size	0

प्रकार u32 kprobe_opcode_t;
काष्ठा kprobe;
#समावेश <यंत्र/probes.h>

#घोषणा	arch_specअगरic_insn	arch_probes_insn

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित पूर्णांक status;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित पूर्णांक kprobe_status;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *);
पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक fsr);
पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ val, व्योम *data);

/* optinsn ढाँचा addresses */
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_entry[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_val[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_call[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_end[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_sub_sp[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_add_sp[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_restore_begin[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_restore_orig_insn[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_restore_end[];

#घोषणा MAX_OPTIMIZED_LENGTH	4
#घोषणा MAX_OPTINSN_SIZE				\
	((अचिन्हित दीर्घ)optprobe_ढाँचा_end -	\
	 (अचिन्हित दीर्घ)optprobe_ढाँचा_entry)
#घोषणा RELATIVEJUMP_SIZE	4

काष्ठा arch_optimized_insn अणु
	/*
	 * copy of the original inकाष्ठाions.
	 * Dअगरferent from x86, ARM kprobe_opcode_t is u32.
	 */
#घोषणा MAX_COPIED_INSN	DIV_ROUND_UP(RELATIVEJUMP_SIZE, माप(kprobe_opcode_t))
	kprobe_opcode_t copied_insn[MAX_COPIED_INSN];
	/* detour code buffer */
	kprobe_opcode_t *insn;
	/*
	 * We always copy one inकाष्ठाion on ARM,
	 * so size will always be 4, and unlike x86, there is no
	 * need क्रम a size field.
	 */
पूर्ण;

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _ARM_KPROBES_H */
