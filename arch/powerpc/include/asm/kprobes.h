<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_KPROBES_H
#घोषणा _ASM_POWERPC_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित __KERNEL__
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation ( includes suggestions from
 *		Rusty Russell).
 * 2004-Nov	Modअगरied क्रम PPC64 by Ananth N Mavinakayanahalli
 *		<ananth@in.ibm.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/probes.h>
#समावेश <यंत्र/code-patching.h>

#अगर_घोषित CONFIG_KPROBES
#घोषणा  __ARCH_WANT_KPROBES_INSN_SLOT

काष्ठा pt_regs;
काष्ठा kprobe;

प्रकार ppc_opcode_t kprobe_opcode_t;

बाह्य kprobe_opcode_t optinsn_slot;

/* Optinsn ढाँचा address */
बाह्य kprobe_opcode_t optprobe_ढाँचा_entry[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_op_address[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_call_handler[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_insn[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_call_emulate[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_ret[];
बाह्य kprobe_opcode_t optprobe_ढाँचा_end[];

/* Fixed inकाष्ठाion size क्रम घातerpc */
#घोषणा MAX_INSN_SIZE		2
#घोषणा MAX_OPTIMIZED_LENGTH	माप(kprobe_opcode_t)	/* 4 bytes */
#घोषणा MAX_OPTINSN_SIZE	(optprobe_ढाँचा_end - optprobe_ढाँचा_entry)
#घोषणा RELATIVEJUMP_SIZE	माप(kprobe_opcode_t)	/* 4 bytes */

#घोषणा flush_insn_slot(p)	करो अणु पूर्ण जबतक (0)
#घोषणा kretprobe_blacklist_size 0

व्योम kretprobe_trampoline(व्योम);
बाह्य व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);

/* Architecture specअगरic copy of original inकाष्ठाion */
काष्ठा arch_specअगरic_insn अणु
	/* copy of original inकाष्ठाion */
	kprobe_opcode_t *insn;
	/*
	 * Set in kprobes code, initially to 0. If the inकाष्ठाion can be
	 * eumulated, this is set to 1, अगर not, to -1.
	 */
	पूर्णांक boostable;
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ saved_msr;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ kprobe_saved_msr;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

काष्ठा arch_optimized_insn अणु
	kprobe_opcode_t copied_insn[1];
	/* detour buffer */
	kprobe_opcode_t *insn;
पूर्ण;

बाह्य पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
					अचिन्हित दीर्घ val, व्योम *data);
बाह्य पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
बाह्य पूर्णांक kprobe_handler(काष्ठा pt_regs *regs);
बाह्य पूर्णांक kprobe_post_handler(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत पूर्णांक kprobe_handler(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kprobe_post_handler(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_KPROBES_H */
