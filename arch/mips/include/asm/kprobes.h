<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Kernel Probes (KProbes)
 *  include/यंत्र-mips/kprobes.h
 *
 *  Copyright 2006 Sony Corp.
 *  Copyright 2010 Cavium Networks
 */

#अगर_अघोषित _ASM_KPROBES_H
#घोषणा _ASM_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/ptrace.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/inst.h>

#घोषणा	 __ARCH_WANT_KPROBES_INSN_SLOT

काष्ठा kprobe;
काष्ठा pt_regs;

प्रकार जोड़ mips_inकाष्ठाion kprobe_opcode_t;

#घोषणा MAX_INSN_SIZE 2

#घोषणा flush_insn_slot(p)						\
करो अणु									\
	अगर (p->addr)							\
		flush_icache_range((अचिन्हित दीर्घ)p->addr,		\
			   (अचिन्हित दीर्घ)p->addr +			\
			   (MAX_INSN_SIZE * माप(kprobe_opcode_t)));	\
पूर्ण जबतक (0)


#घोषणा kretprobe_blacklist_size 0

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);
पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);

/* Architecture specअगरic copy of original inकाष्ठाion*/
काष्ठा arch_specअगरic_insn अणु
	/* copy of the original inकाष्ठाion */
	kprobe_opcode_t *insn;
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ old_SR;
	अचिन्हित दीर्घ saved_SR;
	अचिन्हित दीर्घ saved_epc;
पूर्ण;

#घोषणा SKIP_DELAYSLOT 0x0001

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ kprobe_old_SR;
	अचिन्हित दीर्घ kprobe_saved_SR;
	अचिन्हित दीर्घ kprobe_saved_epc;
	/* Per-thपढ़ो fields, used जबतक emulating branches */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ target_epc;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

बाह्य पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ val, व्योम *data);

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _ASM_KPROBES_H */
