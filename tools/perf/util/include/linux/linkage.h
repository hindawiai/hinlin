<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित PERF_LINUX_LINKAGE_H_
#घोषणा PERF_LINUX_LINKAGE_H_

/* linkage.h ... क्रम including arch/x86/lib/स_नकल_64.S */

/* Some toolchains use other अक्षरacters (e.g. '`') to mark new line in macro */
#अगर_अघोषित ASM_NL
#घोषणा ASM_NL		 ;
#पूर्ण_अगर

#अगर_अघोषित __ALIGN
#घोषणा __ALIGN		.align 4,0x90
#घोषणा __ALIGN_STR	".align 4,0x90"
#पूर्ण_अगर

/* SYM_T_FUNC -- type used by assembler to mark functions */
#अगर_अघोषित SYM_T_FUNC
#घोषणा SYM_T_FUNC				STT_FUNC
#पूर्ण_अगर

/* SYM_A_* -- align the symbol? */
#घोषणा SYM_A_ALIGN				ALIGN

/* SYM_L_* -- linkage of symbols */
#घोषणा SYM_L_GLOBAL(name)			.globl name
#घोषणा SYM_L_WEAK(name)			.weak name
#घोषणा SYM_L_LOCAL(name)			/* nothing */

#घोषणा ALIGN __ALIGN

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

/* SYM_FUNC_START_LOCAL -- use क्रम local functions */
#अगर_अघोषित SYM_FUNC_START_LOCAL
/* the same as SYM_FUNC_START_LOCAL_ALIAS, see comment near SYM_FUNC_START */
#घोषणा SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)
#पूर्ण_अगर

/* SYM_FUNC_END_ALIAS -- the end of LOCAL_ALIASed or ALIASed function */
#अगर_अघोषित SYM_FUNC_END_ALIAS
#घोषणा SYM_FUNC_END_ALIAS(name)			\
	SYM_END(name, SYM_T_FUNC)
#पूर्ण_अगर

/* SYM_FUNC_START_WEAK -- use क्रम weak functions */
#अगर_अघोषित SYM_FUNC_START_WEAK
#घोषणा SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)
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

#पूर्ण_अगर	/* PERF_LINUX_LINKAGE_H_ */
