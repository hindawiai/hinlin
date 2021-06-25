<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LINKAGE_H
#घोषणा _LINUX_LINKAGE_H

#समावेश <linux/compiler_types.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/linkage.h>

/* Some toolchains use other अक्षरacters (e.g. '`') to mark new line in macro */
#अगर_अघोषित ASM_NL
#घोषणा ASM_NL		 ;
#पूर्ण_अगर

#अगर_घोषित __cplusplus
#घोषणा CPP_ASMLINKAGE बाह्य "C"
#अन्यथा
#घोषणा CPP_ASMLINKAGE
#पूर्ण_अगर

#अगर_अघोषित यंत्रlinkage
#घोषणा यंत्रlinkage CPP_ASMLINKAGE
#पूर्ण_अगर

#अगर_अघोषित cond_syscall
#घोषणा cond_syscall(x)	यंत्र(				\
	".weak " __stringअगरy(x) "\n\t"			\
	".set  " __stringअगरy(x) ","			\
		 __stringअगरy(sys_ni_syscall))
#पूर्ण_अगर

#अगर_अघोषित SYSCALL_ALIAS
#घोषणा SYSCALL_ALIAS(alias, name) यंत्र(			\
	".globl " __stringअगरy(alias) "\n\t"		\
	".set   " __stringअगरy(alias) ","		\
		  __stringअगरy(name))
#पूर्ण_अगर

#घोषणा __page_aligned_data	__section(".data..page_aligned") __aligned(PAGE_SIZE)
#घोषणा __page_aligned_bss	__section(".bss..page_aligned") __aligned(PAGE_SIZE)

/*
 * For assembly routines.
 *
 * Note when using these that you must specअगरy the appropriate
 * alignment directives yourself
 */
#घोषणा __PAGE_ALIGNED_DATA	.section ".data..page_aligned", "aw"
#घोषणा __PAGE_ALIGNED_BSS	.section ".bss..page_aligned", "aw"

/*
 * This is used by architectures to keep arguments on the stack
 * untouched by the compiler by keeping them live until the end.
 * The argument stack may be owned by the assembly-language
 * caller, not the callee, and gcc करोesn't always understand
 * that.
 *
 * We have the वापस value, and a maximum of six arguments.
 *
 * This should always be followed by a "return ret" क्रम the
 * protection to work (ie no more work that the compiler might
 * end up needing stack temporaries क्रम).
 */
/* Assembly files may be compiled with -traditional .. */
#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित यंत्रlinkage_protect
# define यंत्रlinkage_protect(n, ret, args...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित __ALIGN
#घोषणा __ALIGN		.align 4,0x90
#घोषणा __ALIGN_STR	".align 4,0x90"
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

/* SYM_T_FUNC -- type used by assembler to mark functions */
#अगर_अघोषित SYM_T_FUNC
#घोषणा SYM_T_FUNC				STT_FUNC
#पूर्ण_अगर

/* SYM_T_OBJECT -- type used by assembler to mark data */
#अगर_अघोषित SYM_T_OBJECT
#घोषणा SYM_T_OBJECT				STT_OBJECT
#पूर्ण_अगर

/* SYM_T_NONE -- type used by assembler to mark entries of unknown type */
#अगर_अघोषित SYM_T_NONE
#घोषणा SYM_T_NONE				STT_NOTYPE
#पूर्ण_अगर

/* SYM_A_* -- align the symbol? */
#घोषणा SYM_A_ALIGN				ALIGN
#घोषणा SYM_A_NONE				/* nothing */

/* SYM_L_* -- linkage of symbols */
#घोषणा SYM_L_GLOBAL(name)			.globl name
#घोषणा SYM_L_WEAK(name)			.weak name
#घोषणा SYM_L_LOCAL(name)			/* nothing */

#अगर_अघोषित LINKER_SCRIPT
#घोषणा ALIGN __ALIGN
#घोषणा ALIGN_STR __ALIGN_STR

/* === DEPRECATED annotations === */

#अगर_अघोषित CONFIG_ARCH_USE_SYM_ANNOTATIONS
#अगर_अघोषित GLOBAL
/* deprecated, use SYM_DATA*, SYM_ENTRY, or similar */
#घोषणा GLOBAL(name) \
	.globl name ASM_NL \
	name:
#पूर्ण_अगर

#अगर_अघोषित ENTRY
/* deprecated, use SYM_FUNC_START */
#घोषणा ENTRY(name) \
	SYM_FUNC_START(name)
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_USE_SYM_ANNOTATIONS */
#पूर्ण_अगर /* LINKER_SCRIPT */

#अगर_अघोषित CONFIG_ARCH_USE_SYM_ANNOTATIONS
#अगर_अघोषित WEAK
/* deprecated, use SYM_FUNC_START_WEAK* */
#घोषणा WEAK(name)	   \
	SYM_FUNC_START_WEAK(name)
#पूर्ण_अगर

#अगर_अघोषित END
/* deprecated, use SYM_FUNC_END, SYM_DATA_END, or SYM_END */
#घोषणा END(name) \
	.size name, .-name
#पूर्ण_अगर

/* If symbol 'name' is treated as a subroutine (माला_लो called, and वापसs)
 * then please use ENDPROC to mark 'name' as STT_FUNC क्रम the benefit of
 * अटल analysis tools such as stack depth analyzer.
 */
#अगर_अघोषित ENDPROC
/* deprecated, use SYM_FUNC_END */
#घोषणा ENDPROC(name) \
	SYM_FUNC_END(name)
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_USE_SYM_ANNOTATIONS */

/* === generic annotations === */

/* SYM_ENTRY -- use only अगर you have to क्रम non-paired symbols */
#अगर_अघोषित SYM_ENTRY
#घोषणा SYM_ENTRY(name, linkage, align...)		\
	linkage(name) ASM_NL				\
	align ASM_NL					\
	name:
#पूर्ण_अगर

/* SYM_START -- use only अगर you have to */
#अगर_अघोषित SYM_START
#घोषणा SYM_START(name, linkage, align...)		\
	SYM_ENTRY(name, linkage, align)
#पूर्ण_अगर

/* SYM_END -- use only अगर you have to */
#अगर_अघोषित SYM_END
#घोषणा SYM_END(name, sym_type)				\
	.type name sym_type ASM_NL			\
	.size name, .-name
#पूर्ण_अगर

/* === code annotations === */

/*
 * FUNC -- C-like functions (proper stack frame etc.)
 * CODE -- non-C code (e.g. irq handlers with dअगरferent, special stack etc.)
 *
 * Objtool validates stack क्रम FUNC, but not क्रम CODE.
 * Objtool generates debug info क्रम both FUNC & CODE, but needs special
 * annotations क्रम each CODE's start (to describe the actual stack frame).
 *
 * Objtool requires that all code must be contained in an ELF symbol. Symbol
 * names that have a  .L prefix करो not emit symbol table entries. .L
 * prefixed symbols can be used within a code region, but should be aव्योमed क्रम
 * denoting a range of code via ``SYM_*_START/END`` annotations.
 *
 * ALIAS -- करोes not generate debug info -- the aliased function will
 */

/* SYM_INNER_LABEL_ALIGN -- only क्रम labels in the middle of code */
#अगर_अघोषित SYM_INNER_LABEL_ALIGN
#घोषणा SYM_INNER_LABEL_ALIGN(name, linkage)	\
	.type name SYM_T_NONE ASM_NL			\
	SYM_ENTRY(name, linkage, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_INNER_LABEL -- only क्रम labels in the middle of code */
#अगर_अघोषित SYM_INNER_LABEL
#घोषणा SYM_INNER_LABEL(name, linkage)		\
	.type name SYM_T_NONE ASM_NL			\
	SYM_ENTRY(name, linkage, SYM_A_NONE)
#पूर्ण_अगर

/*
 * SYM_FUNC_START_LOCAL_ALIAS -- use where there are two local names क्रम one
 * function
 */
#अगर_अघोषित SYM_FUNC_START_LOCAL_ALIAS
#घोषणा SYM_FUNC_START_LOCAL_ALIAS(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#पूर्ण_अगर

/*
 * SYM_FUNC_START_ALIAS -- use where there are two global names क्रम one
 * function
 */
#अगर_अघोषित SYM_FUNC_START_ALIAS
#घोषणा SYM_FUNC_START_ALIAS(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_FUNC_START -- use क्रम global functions */
#अगर_अघोषित SYM_FUNC_START
/*
 * The same as SYM_FUNC_START_ALIAS, but we will need to distinguish these two
 * later.
 */
#घोषणा SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_FUNC_START_NOALIGN -- use क्रम global functions, w/o alignment */
#अगर_अघोषित SYM_FUNC_START_NOALIGN
#घोषणा SYM_FUNC_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_FUNC_START_LOCAL -- use क्रम local functions */
#अगर_अघोषित SYM_FUNC_START_LOCAL
/* the same as SYM_FUNC_START_LOCAL_ALIAS, see comment near SYM_FUNC_START */
#घोषणा SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_FUNC_START_LOCAL_NOALIGN -- use क्रम local functions, w/o alignment */
#अगर_अघोषित SYM_FUNC_START_LOCAL_NOALIGN
#घोषणा SYM_FUNC_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_FUNC_START_WEAK -- use क्रम weak functions */
#अगर_अघोषित SYM_FUNC_START_WEAK
#घोषणा SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_FUNC_START_WEAK_NOALIGN -- use क्रम weak functions, w/o alignment */
#अगर_अघोषित SYM_FUNC_START_WEAK_NOALIGN
#घोषणा SYM_FUNC_START_WEAK_NOALIGN(name)		\
	SYM_START(name, SYM_L_WEAK, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_FUNC_END_ALIAS -- the end of LOCAL_ALIASed or ALIASed function */
#अगर_अघोषित SYM_FUNC_END_ALIAS
#घोषणा SYM_FUNC_END_ALIAS(name)			\
	SYM_END(name, SYM_T_FUNC)
#पूर्ण_अगर

/*
 * SYM_FUNC_END -- the end of SYM_FUNC_START_LOCAL, SYM_FUNC_START,
 * SYM_FUNC_START_WEAK, ...
 */
#अगर_अघोषित SYM_FUNC_END
/* the same as SYM_FUNC_END_ALIAS, see comment near SYM_FUNC_START */
#घोषणा SYM_FUNC_END(name)				\
	SYM_END(name, SYM_T_FUNC)
#पूर्ण_अगर

/* SYM_CODE_START -- use क्रम non-C (special) functions */
#अगर_अघोषित SYM_CODE_START
#घोषणा SYM_CODE_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_CODE_START_NOALIGN -- use क्रम non-C (special) functions, w/o alignment */
#अगर_अघोषित SYM_CODE_START_NOALIGN
#घोषणा SYM_CODE_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_CODE_START_LOCAL -- use क्रम local non-C (special) functions */
#अगर_अघोषित SYM_CODE_START_LOCAL
#घोषणा SYM_CODE_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#पूर्ण_अगर

/*
 * SYM_CODE_START_LOCAL_NOALIGN -- use क्रम local non-C (special) functions,
 * w/o alignment
 */
#अगर_अघोषित SYM_CODE_START_LOCAL_NOALIGN
#घोषणा SYM_CODE_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_CODE_END -- the end of SYM_CODE_START_LOCAL, SYM_CODE_START, ... */
#अगर_अघोषित SYM_CODE_END
#घोषणा SYM_CODE_END(name)				\
	SYM_END(name, SYM_T_NONE)
#पूर्ण_अगर

/* === data annotations === */

/* SYM_DATA_START -- global data symbol */
#अगर_अघोषित SYM_DATA_START
#घोषणा SYM_DATA_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_DATA_START -- local data symbol */
#अगर_अघोषित SYM_DATA_START_LOCAL
#घोषणा SYM_DATA_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)
#पूर्ण_अगर

/* SYM_DATA_END -- the end of SYM_DATA_START symbol */
#अगर_अघोषित SYM_DATA_END
#घोषणा SYM_DATA_END(name)				\
	SYM_END(name, SYM_T_OBJECT)
#पूर्ण_अगर

/* SYM_DATA_END_LABEL -- the labeled end of SYM_DATA_START symbol */
#अगर_अघोषित SYM_DATA_END_LABEL
#घोषणा SYM_DATA_END_LABEL(name, linkage, label)	\
	linkage(label) ASM_NL				\
	.type label SYM_T_OBJECT ASM_NL			\
	label:						\
	SYM_END(name, SYM_T_OBJECT)
#पूर्ण_अगर

/* SYM_DATA -- start+end wrapper around simple global data */
#अगर_अघोषित SYM_DATA
#घोषणा SYM_DATA(name, data...)				\
	SYM_DATA_START(name) ASM_NL				\
	data ASM_NL						\
	SYM_DATA_END(name)
#पूर्ण_अगर

/* SYM_DATA_LOCAL -- start+end wrapper around simple local data */
#अगर_अघोषित SYM_DATA_LOCAL
#घोषणा SYM_DATA_LOCAL(name, data...)			\
	SYM_DATA_START_LOCAL(name) ASM_NL			\
	data ASM_NL						\
	SYM_DATA_END(name)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _LINUX_LINKAGE_H */
