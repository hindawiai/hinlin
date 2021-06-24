<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_FRAME_H
#घोषणा _ASM_X86_FRAME_H

#समावेश <यंत्र/यंत्र.h>

/*
 * These are stack frame creation macros.  They should be used by every
 * callable non-leaf यंत्र function to make kernel stack traces more reliable.
 */

#अगर_घोषित CONFIG_FRAME_POINTER

#अगर_घोषित __ASSEMBLY__

.macro FRAME_BEGIN
	push %_ASM_BP
	_ASM_MOV %_ASM_SP, %_ASM_BP
.endm

.macro FRAME_END
	pop %_ASM_BP
.endm

#अगर_घोषित CONFIG_X86_64
/*
 * This is a sneaky trick to help the unwinder find pt_regs on the stack.  The
 * frame poपूर्णांकer is replaced with an encoded poपूर्णांकer to pt_regs.  The encoding
 * is just setting the LSB, which makes it an invalid stack address and is also
 * a संकेत to the unwinder that it's a pt_regs poपूर्णांकer in disguise.
 *
 * NOTE: This macro must be used *after* PUSH_AND_CLEAR_REGS because it corrupts
 * the original rbp.
 */
.macro ENCODE_FRAME_POINTER ptregs_offset=0
	leaq 1+\ptregs_offset(%rsp), %rbp
.endm
#अन्यथा /* !CONFIG_X86_64 */
/*
 * This is a sneaky trick to help the unwinder find pt_regs on the stack.  The
 * frame poपूर्णांकer is replaced with an encoded poपूर्णांकer to pt_regs.  The encoding
 * is just clearing the MSB, which makes it an invalid stack address and is also
 * a संकेत to the unwinder that it's a pt_regs poपूर्णांकer in disguise.
 *
 * NOTE: This macro must be used *after* SAVE_ALL because it corrupts the
 * original ebp.
 */
.macro ENCODE_FRAME_POINTER
	mov %esp, %ebp
	andl $0x7fffffff, %ebp
.endm
#पूर्ण_अगर /* CONFIG_X86_64 */

#अन्यथा /* !__ASSEMBLY__ */

#घोषणा FRAME_BEGIN				\
	"push %" _ASM_BP "\n"			\
	_ASM_MOV "%" _ASM_SP ", %" _ASM_BP "\n"

#घोषणा FRAME_END "pop %" _ASM_BP "\n"

#अगर_घोषित CONFIG_X86_64

#घोषणा ENCODE_FRAME_POINTER			\
	"lea 1(%rsp), %rbp\n\t"

अटल अंतरभूत अचिन्हित दीर्घ encode_frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस (अचिन्हित दीर्घ)regs + 1;
पूर्ण

#अन्यथा /* !CONFIG_X86_64 */

#घोषणा ENCODE_FRAME_POINTER			\
	"movl %esp, %ebp\n\t"			\
	"andl $0x7fffffff, %ebp\n\t"

अटल अंतरभूत अचिन्हित दीर्घ encode_frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस (अचिन्हित दीर्घ)regs & 0x7fffffff;
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_64 */

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा FRAME_OFFSET __ASM_SEL(4, 8)

#अन्यथा /* !CONFIG_FRAME_POINTER */

#अगर_घोषित __ASSEMBLY__

.macro ENCODE_FRAME_POINTER ptregs_offset=0
.endm

#अन्यथा /* !__ASSEMBLY */

#घोषणा ENCODE_FRAME_POINTER

अटल अंतरभूत अचिन्हित दीर्घ encode_frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#घोषणा FRAME_BEGIN
#घोषणा FRAME_END
#घोषणा FRAME_OFFSET 0

#पूर्ण_अगर /* CONFIG_FRAME_POINTER */

#पूर्ण_अगर /* _ASM_X86_FRAME_H */
