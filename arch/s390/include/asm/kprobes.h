<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित _ASM_S390_KPROBES_H
#घोषणा _ASM_S390_KPROBES_H
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright IBM Corp. 2002, 2006
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation ( includes suggestions from
 *		Rusty Russell).
 * 2004-Nov	Modअगरied क्रम PPC64 by Ananth N Mavinakayanahalli
 *		<ananth@in.ibm.com>
 * 2005-Dec	Used as a ढाँचा क्रम s390 by Mike Grundy
 *		<grundym@us.ibm.com>
 */
#समावेश <linux/types.h>
#समावेश <यंत्र-generic/kprobes.h>

#घोषणा BREAKPOINT_INSTRUCTION	0x0002

#घोषणा FIXUP_PSW_NORMAL	0x08
#घोषणा FIXUP_BRANCH_NOT_TAKEN	0x04
#घोषणा FIXUP_RETURN_REGISTER	0x02
#घोषणा FIXUP_NOT_REQUIRED	0x01

पूर्णांक probe_is_prohibited_opcode(u16 *insn);
पूर्णांक probe_get_fixup_type(u16 *insn);
पूर्णांक probe_is_insn_relative_दीर्घ(u16 *insn);

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched/task_stack.h>

#घोषणा __ARCH_WANT_KPROBES_INSN_SLOT

काष्ठा pt_regs;
काष्ठा kprobe;

प्रकार u16 kprobe_opcode_t;

/* Maximum inकाष्ठाion size is 3 (16bit) halfwords: */
#घोषणा MAX_INSN_SIZE		0x0003
#घोषणा MAX_STACK_SIZE		64
#घोषणा MIN_STACK_SIZE(ADDR) (((MAX_STACK_SIZE) < \
	(((अचिन्हित दीर्घ)task_stack_page(current)) + THREAD_SIZE - (ADDR))) \
	? (MAX_STACK_SIZE) \
	: (((अचिन्हित दीर्घ)task_stack_page(current)) + THREAD_SIZE - (ADDR)))

#घोषणा kretprobe_blacklist_size 0

/* Architecture specअगरic copy of original inकाष्ठाion */
काष्ठा arch_specअगरic_insn अणु
	/* copy of original inकाष्ठाion */
	kprobe_opcode_t *insn;
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ kprobe_saved_imask;
	अचिन्हित दीर्घ kprobe_saved_ctl[3];
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);
व्योम kretprobe_trampoline(व्योम);

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
	अचिन्हित दीर्घ val, व्योम *data);

#घोषणा flush_insn_slot(p)	करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर	/* _ASM_S390_KPROBES_H */
