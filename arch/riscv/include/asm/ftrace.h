<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2017 Andes Technology Corporation */

#अगर_अघोषित _ASM_RISCV_FTRACE_H
#घोषणा _ASM_RISCV_FTRACE_H

/*
 * The graph frame test is not possible अगर CONFIG_FRAME_POINTER is not enabled.
 * Check arch/riscv/kernel/mcount.S क्रम detail.
 */
#अगर defined(CONFIG_FUNCTION_GRAPH_TRACER) && defined(CONFIG_FRAME_POINTER)
#घोषणा HAVE_FUNCTION_GRAPH_FP_TEST
#पूर्ण_अगर
#घोषणा HAVE_FUNCTION_GRAPH_RET_ADDR_PTR

/*
 * Clang prior to 13 had "mcount" instead of "_mcount":
 * https://reviews.llvm.org/D98881
 */
#अगर defined(CONFIG_CC_IS_GCC) || CONFIG_CLANG_VERSION >= 130000
#घोषणा MCOUNT_NAME _mcount
#अन्यथा
#घोषणा MCOUNT_NAME mcount
#पूर्ण_अगर

#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#अगर_अघोषित __ASSEMBLY__
व्योम MCOUNT_NAME(व्योम);
अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/*
 * A general call in RISC-V is a pair of insts:
 * 1) auipc: setting high-20 pc-related bits to ra रेजिस्टर
 * 2) jalr: setting low-12 offset to ra, jump to ra, and set ra to
 *          वापस address (original pc + 4)
 *
 * Dynamic ftrace generates probes to call sites, so we must deal with
 * both auipc and jalr at the same समय.
 */

#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)MCOUNT_NAME)
#घोषणा JALR_SIGN_MASK		(0x00000800)
#घोषणा JALR_OFFSET_MASK	(0x00000fff)
#घोषणा AUIPC_OFFSET_MASK	(0xfffff000)
#घोषणा AUIPC_PAD		(0x00001000)
#घोषणा JALR_SHIFT		20
#घोषणा JALR_BASIC		(0x000080e7)
#घोषणा AUIPC_BASIC		(0x00000097)
#घोषणा NOP4			(0x00000013)

#घोषणा make_call(caller, callee, call)					\
करो अणु									\
	call[0] = to_auipc_insn((अचिन्हित पूर्णांक)((अचिन्हित दीर्घ)callee -	\
				(अचिन्हित दीर्घ)caller));		\
	call[1] = to_jalr_insn((अचिन्हित पूर्णांक)((अचिन्हित दीर्घ)callee -	\
			       (अचिन्हित दीर्घ)caller));			\
पूर्ण जबतक (0)

#घोषणा to_jalr_insn(offset)						\
	(((offset & JALR_OFFSET_MASK) << JALR_SHIFT) | JALR_BASIC)

#घोषणा to_auipc_insn(offset)						\
	((offset & JALR_SIGN_MASK) ?					\
	(((offset & AUIPC_OFFSET_MASK) + AUIPC_PAD) | AUIPC_BASIC) :	\
	((offset & AUIPC_OFFSET_MASK) | AUIPC_BASIC))

/*
 * Let auipc+jalr be the basic *mcount unit*, so we make it 8 bytes here.
 */
#घोषणा MCOUNT_INSN_SIZE 8

#अगर_अघोषित __ASSEMBLY__
काष्ठा dyn_ftrace;
पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec);
#घोषणा ftrace_init_nop ftrace_init_nop
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_FTRACE_H */
