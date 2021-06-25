<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_KPROBES_H
#घोषणा _ASM_X86_KPROBES_H
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * See arch/x86/kernel/kprobes.c क्रम x86 kprobes history.
 */

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित CONFIG_KPROBES
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/insn.h>

#घोषणा  __ARCH_WANT_KPROBES_INSN_SLOT

काष्ठा pt_regs;
काष्ठा kprobe;

प्रकार u8 kprobe_opcode_t;

#घोषणा MAX_STACK_SIZE 64
#घोषणा CUR_STACK_SIZE(ADDR) \
	(current_top_of_stack() - (अचिन्हित दीर्घ)(ADDR))
#घोषणा MIN_STACK_SIZE(ADDR)				\
	(MAX_STACK_SIZE < CUR_STACK_SIZE(ADDR) ?	\
	 MAX_STACK_SIZE : CUR_STACK_SIZE(ADDR))

#घोषणा flush_insn_slot(p)	करो अणु पूर्ण जबतक (0)

/* optinsn ढाँचा addresses */
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_entry[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_clac[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_val[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_call[];
बाह्य __visible kprobe_opcode_t optprobe_ढाँचा_end[];
#घोषणा MAX_OPTIMIZED_LENGTH (MAX_INSN_SIZE + DISP32_SIZE)
#घोषणा MAX_OPTINSN_SIZE 				\
	(((अचिन्हित दीर्घ)optprobe_ढाँचा_end -	\
	  (अचिन्हित दीर्घ)optprobe_ढाँचा_entry) +	\
	 MAX_OPTIMIZED_LENGTH + JMP32_INSN_SIZE)

बाह्य स्थिर पूर्णांक kretprobe_blacklist_size;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);
यंत्रlinkage व्योम kretprobe_trampoline(व्योम);

बाह्य व्योम arch_kprobe_override_function(काष्ठा pt_regs *regs);

/* Architecture specअगरic copy of original inकाष्ठाion*/
काष्ठा arch_specअगरic_insn अणु
	/* copy of the original inकाष्ठाion */
	kprobe_opcode_t *insn;
	/*
	 * boostable = 0: This inकाष्ठाion type is not boostable.
	 * boostable = 1: This inकाष्ठाion has been boosted: we have
	 * added a relative jump after the inकाष्ठाion copy in insn,
	 * so no single-step and fixup are needed (unless there's
	 * a post_handler).
	 */
	अचिन्हित boostable:1;
	अचिन्हित अक्षर size;	/* The size of insn */
	जोड़ अणु
		अचिन्हित अक्षर opcode;
		काष्ठा अणु
			अचिन्हित अक्षर type;
		पूर्ण jcc;
		काष्ठा अणु
			अचिन्हित अक्षर type;
			अचिन्हित अक्षर asize;
		पूर्ण loop;
		काष्ठा अणु
			अचिन्हित अक्षर reg;
		पूर्ण indirect;
	पूर्ण;
	s32 rel32;	/* relative offset must be s32, s16, or s8 */
	व्योम (*emulate_op)(काष्ठा kprobe *p, काष्ठा pt_regs *regs);
	/* Number of bytes of text poked */
	पूर्णांक tp_len;
पूर्ण;

काष्ठा arch_optimized_insn अणु
	/* copy of the original inकाष्ठाions */
	kprobe_opcode_t copied_insn[DISP32_SIZE];
	/* detour code buffer */
	kprobe_opcode_t *insn;
	/* the size of inकाष्ठाions copied to detour code buffer */
	माप_प्रकार size;
पूर्ण;

/* Return true (!0) अगर optinsn is prepared क्रम optimization. */
अटल अंतरभूत पूर्णांक arch_prepared_optinsn(काष्ठा arch_optimized_insn *optinsn)
अणु
	वापस optinsn->size;
पूर्ण

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ old_flags;
	अचिन्हित दीर्घ saved_flags;
पूर्ण;

/* per-cpu kprobe control block */
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ kprobe_old_flags;
	अचिन्हित दीर्घ kprobe_saved_flags;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

बाह्य पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
बाह्य पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ val, व्योम *data);
बाह्य पूर्णांक kprobe_पूर्णांक3_handler(काष्ठा pt_regs *regs);

#अन्यथा

अटल अंतरभूत पूर्णांक kprobe_debug_handler(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _ASM_X86_KPROBES_H */
