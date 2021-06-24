<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_KPROBES_H
#घोषणा _SPARC64_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#घोषणा BREAKPOINT_INSTRUCTION   0x91d02070 /* ta 0x70 */
#घोषणा BREAKPOINT_INSTRUCTION_2 0x91d02071 /* ta 0x71 */

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/types.h>
#समावेश <linux/percpu.h>

प्रकार u32 kprobe_opcode_t;

#घोषणा MAX_INSN_SIZE 2

#घोषणा kretprobe_blacklist_size 0

#घोषणा arch_हटाओ_kprobe(p)	करो अणुपूर्ण जबतक (0)

#घोषणा flush_insn_slot(p)		\
करो अणु 	flushi(&(p)->ainsn.insn[0]);	\
	flushi(&(p)->ainsn.insn[1]);	\
पूर्ण जबतक (0)

व्योम kretprobe_trampoline(व्योम);

/* Architecture specअगरic copy of original inकाष्ठाion*/
काष्ठा arch_specअगरic_insn अणु
	/* copy of the original inकाष्ठाion */
	kprobe_opcode_t insn[MAX_INSN_SIZE];
पूर्ण;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ orig_tnpc;
	अचिन्हित दीर्घ orig_tstate_pil;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ kprobe_orig_tnpc;
	अचिन्हित दीर्घ kprobe_orig_tstate_pil;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ val, व्योम *data);
पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
यंत्रlinkage व्योम __kprobes kprobe_trap(अचिन्हित दीर्घ trap_level,
				      काष्ठा pt_regs *regs);

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _SPARC64_KPROBES_H */
