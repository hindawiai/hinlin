<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_KPROBES_H
#घोषणा __ASM_SH_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#घोषणा BREAKPOINT_INSTRUCTION	0xc33a

#अगर_घोषित CONFIG_KPROBES

#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>

प्रकार insn_माप_प्रकार kprobe_opcode_t;

#घोषणा MAX_INSN_SIZE 16
#घोषणा MAX_STACK_SIZE 64
#घोषणा MIN_STACK_SIZE(ADDR) (((MAX_STACK_SIZE) < \
	(((अचिन्हित दीर्घ)current_thपढ़ो_info()) + THREAD_SIZE - (ADDR))) \
	? (MAX_STACK_SIZE) \
	: (((अचिन्हित दीर्घ)current_thपढ़ो_info()) + THREAD_SIZE - (ADDR)))

#घोषणा flush_insn_slot(p)		करो अणु पूर्ण जबतक (0)
#घोषणा kretprobe_blacklist_size	0

काष्ठा kprobe;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *);
व्योम kretprobe_trampoline(व्योम);

/* Architecture specअगरic copy of original inकाष्ठाion*/
काष्ठा arch_specअगरic_insn अणु
	/* copy of the original inकाष्ठाion */
	kprobe_opcode_t insn[MAX_INSN_SIZE];
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

बाह्य पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
बाह्य पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ val, व्योम *data);
बाह्य पूर्णांक kprobe_handle_illslot(अचिन्हित दीर्घ pc);
#अन्यथा

#घोषणा kprobe_handle_illslot(pc)	(-1)

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* __ASM_SH_KPROBES_H */
