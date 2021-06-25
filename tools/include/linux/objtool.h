<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_OBJTOOL_H
#घोषणा _LINUX_OBJTOOL_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/*
 * This काष्ठा is used by यंत्र and अंतरभूत यंत्र code to manually annotate the
 * location of रेजिस्टरs on the stack.
 */
काष्ठा unwind_hपूर्णांक अणु
	u32		ip;
	s16		sp_offset;
	u8		sp_reg;
	u8		type;
	u8		end;
पूर्ण;
#पूर्ण_अगर

/*
 * UNWIND_HINT_TYPE_CALL: Indicates that sp_reg+sp_offset resolves to PREV_SP
 * (the caller's SP right beक्रमe it made the call).  Used क्रम all callable
 * functions, i.e. all C code and all callable यंत्र functions.
 *
 * UNWIND_HINT_TYPE_REGS: Used in entry code to indicate that sp_reg+sp_offset
 * poपूर्णांकs to a fully populated pt_regs from a syscall, पूर्णांकerrupt, or exception.
 *
 * UNWIND_HINT_TYPE_REGS_PARTIAL: Used in entry code to indicate that
 * sp_reg+sp_offset poपूर्णांकs to the iret वापस frame.
 *
 * UNWIND_HINT_FUNC: Generate the unwind metadata of a callable function.
 * Useful क्रम code which करोesn't have an ELF function annotation.
 */
#घोषणा UNWIND_HINT_TYPE_CALL		0
#घोषणा UNWIND_HINT_TYPE_REGS		1
#घोषणा UNWIND_HINT_TYPE_REGS_PARTIAL	2
#घोषणा UNWIND_HINT_TYPE_FUNC		3

#अगर_घोषित CONFIG_STACK_VALIDATION

#अगर_अघोषित __ASSEMBLY__

#घोषणा UNWIND_HINT(sp_reg, sp_offset, type, end)		\
	"987: \n\t"						\
	".pushsection .discard.unwind_hints\n\t"		\
	/* काष्ठा unwind_hपूर्णांक */				\
	".long 987b - .\n\t"					\
	".short " __stringअगरy(sp_offset) "\n\t"			\
	".byte " __stringअगरy(sp_reg) "\n\t"			\
	".byte " __stringअगरy(type) "\n\t"			\
	".byte " __stringअगरy(end) "\n\t"			\
	".balign 4 \n\t"					\
	".popsection\n\t"

/*
 * This macro marks the given function's stack frame as "non-standard", which
 * tells objtool to ignore the function when करोing stack metadata validation.
 * It should only be used in special हालs where you're 100% sure it won't
 * affect the reliability of frame poपूर्णांकers and kernel stack traces.
 *
 * For more inक्रमmation, see tools/objtool/Documentation/stack-validation.txt.
 */
#घोषणा STACK_FRAME_NON_STANDARD(func) \
	अटल व्योम __used __section(".discard.func_stack_frame_non_standard") \
		*__func_stack_frame_non_standard_##func = func

#अन्यथा /* __ASSEMBLY__ */

/*
 * This macro indicates that the following पूर्णांकra-function call is valid.
 * Any non-annotated पूर्णांकra-function call will cause objtool to issue a warning.
 */
#घोषणा ANNOTATE_INTRA_FUNCTION_CALL				\
	999:							\
	.pushsection .discard.पूर्णांकra_function_calls;		\
	.दीर्घ 999b;						\
	.popsection;

/*
 * In यंत्र, there are two kinds of code: normal C-type callable functions and
 * the rest.  The normal callable functions can be called by other code, and
 * करोn't करो anything unusual with the stack.  Such normal callable functions
 * are annotated with the ENTRY/ENDPROC macros.  Most यंत्र code falls in this
 * category.  In this हाल, no special debugging annotations are needed because
 * objtool can स्वतःmatically generate the ORC data क्रम the ORC unwinder to पढ़ो
 * at runसमय.
 *
 * Anything which करोesn't fall पूर्णांकo the above category, such as syscall and
 * पूर्णांकerrupt handlers, tends to not be called directly by other functions, and
 * often करोes unusual non-C-function-type things with the stack poपूर्णांकer.  Such
 * code needs to be annotated such that objtool can understand it.  The
 * following CFI hपूर्णांक macros are क्रम this type of code.
 *
 * These macros provide hपूर्णांकs to objtool about the state of the stack at each
 * inकाष्ठाion.  Objtool starts from the hपूर्णांकs and follows the code flow,
 * making स्वतःmatic CFI adjusपंचांगents when it sees pushes and pops, filling out
 * the debuginfo as necessary.  It will also warn अगर it sees any
 * inconsistencies.
 */
.macro UNWIND_HINT sp_reg:req sp_offset=0 type:req end=0
.Lunwind_hपूर्णांक_ip_\@:
	.pushsection .discard.unwind_hपूर्णांकs
		/* काष्ठा unwind_hपूर्णांक */
		.दीर्घ .Lunwind_hपूर्णांक_ip_\@ - .
		.लघु \sp_offset
		.byte \sp_reg
		.byte \टype
		.byte \end
		.balign 4
	.popsection
.endm

.macro STACK_FRAME_NON_STANDARD func:req
	.pushsection .discard.func_stack_frame_non_standard, "aw"
		.दीर्घ \पunc - .
	.popsection
.endm

#पूर्ण_अगर /* __ASSEMBLY__ */

#अन्यथा /* !CONFIG_STACK_VALIDATION */

#अगर_अघोषित __ASSEMBLY__

#घोषणा UNWIND_HINT(sp_reg, sp_offset, type, end)	\
	"\n\t"
#घोषणा STACK_FRAME_NON_STANDARD(func)
#अन्यथा
#घोषणा ANNOTATE_INTRA_FUNCTION_CALL
.macro UNWIND_HINT sp_reg:req sp_offset=0 type:req end=0
.endm
.macro STACK_FRAME_NON_STANDARD func:req
.endm
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_STACK_VALIDATION */

#पूर्ण_अगर /* _LINUX_OBJTOOL_H */
