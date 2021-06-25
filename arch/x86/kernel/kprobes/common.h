<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __X86_KERNEL_KPROBES_COMMON_H
#घोषणा __X86_KERNEL_KPROBES_COMMON_H

/* Kprobes and Optprobes common header */

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/frame.h>

#अगर_घोषित CONFIG_X86_64

#घोषणा SAVE_REGS_STRING			\
	/* Skip cs, ip, orig_ax. */		\
	"	subq $24, %rsp\n"		\
	"	pushq %rdi\n"			\
	"	pushq %rsi\n"			\
	"	pushq %rdx\n"			\
	"	pushq %rcx\n"			\
	"	pushq %rax\n"			\
	"	pushq %r8\n"			\
	"	pushq %r9\n"			\
	"	pushq %r10\n"			\
	"	pushq %r11\n"			\
	"	pushq %rbx\n"			\
	"	pushq %rbp\n"			\
	"	pushq %r12\n"			\
	"	pushq %r13\n"			\
	"	pushq %r14\n"			\
	"	pushq %r15\n"			\
	ENCODE_FRAME_POINTER

#घोषणा RESTORE_REGS_STRING			\
	"	popq %r15\n"			\
	"	popq %r14\n"			\
	"	popq %r13\n"			\
	"	popq %r12\n"			\
	"	popq %rbp\n"			\
	"	popq %rbx\n"			\
	"	popq %r11\n"			\
	"	popq %r10\n"			\
	"	popq %r9\n"			\
	"	popq %r8\n"			\
	"	popq %rax\n"			\
	"	popq %rcx\n"			\
	"	popq %rdx\n"			\
	"	popq %rsi\n"			\
	"	popq %rdi\n"			\
	/* Skip orig_ax, ip, cs */		\
	"	addq $24, %rsp\n"
#अन्यथा

#घोषणा SAVE_REGS_STRING			\
	/* Skip cs, ip, orig_ax and gs. */	\
	"	subl $4*4, %esp\n"		\
	"	pushl %fs\n"			\
	"	pushl %es\n"			\
	"	pushl %ds\n"			\
	"	pushl %eax\n"			\
	"	pushl %ebp\n"			\
	"	pushl %edi\n"			\
	"	pushl %esi\n"			\
	"	pushl %edx\n"			\
	"	pushl %ecx\n"			\
	"	pushl %ebx\n"			\
	ENCODE_FRAME_POINTER

#घोषणा RESTORE_REGS_STRING			\
	"	popl %ebx\n"			\
	"	popl %ecx\n"			\
	"	popl %edx\n"			\
	"	popl %esi\n"			\
	"	popl %edi\n"			\
	"	popl %ebp\n"			\
	"	popl %eax\n"			\
	/* Skip ds, es, fs, gs, orig_ax, ip, and cs. */\
	"	addl $7*4, %esp\n"
#पूर्ण_अगर

/* Ensure अगर the inकाष्ठाion can be boostable */
बाह्य पूर्णांक can_boost(काष्ठा insn *insn, व्योम *orig_addr);
/* Recover inकाष्ठाion अगर given address is probed */
बाह्य अचिन्हित दीर्घ recover_probed_inकाष्ठाion(kprobe_opcode_t *buf,
					 अचिन्हित दीर्घ addr);
/*
 * Copy an inकाष्ठाion and adjust the displacement अगर the inकाष्ठाion
 * uses the %rip-relative addressing mode.
 */
बाह्य पूर्णांक __copy_inकाष्ठाion(u8 *dest, u8 *src, u8 *real, काष्ठा insn *insn);

/* Generate a relative-jump/call inकाष्ठाion */
बाह्य व्योम synthesize_reljump(व्योम *dest, व्योम *from, व्योम *to);
बाह्य व्योम synthesize_relcall(व्योम *dest, व्योम *from, व्योम *to);

#अगर_घोषित	CONFIG_OPTPROBES
बाह्य पूर्णांक setup_detour_execution(काष्ठा kprobe *p, काष्ठा pt_regs *regs, पूर्णांक reenter);
बाह्य अचिन्हित दीर्घ __recover_optprobed_insn(kprobe_opcode_t *buf, अचिन्हित दीर्घ addr);
#अन्यथा	/* !CONFIG_OPTPROBES */
अटल अंतरभूत पूर्णांक setup_detour_execution(काष्ठा kprobe *p, काष्ठा pt_regs *regs, पूर्णांक reenter)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ __recover_optprobed_insn(kprobe_opcode_t *buf, अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
