<शैली गुरु>
#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#घोषणा __ALIGN		.align 2
#घोषणा __ALIGN_STR	".align 2"

#अगर defined(CONFIG_ARM64_BTI_KERNEL) && defined(__aarch64__)

/*
 * Since current versions of gas reject the BTI inकाष्ठाion unless we
 * set the architecture version to v8.5 we use the hपूर्णांक inकाष्ठाion
 * instead.
 */
#घोषणा BTI_C hपूर्णांक 34 ;

/*
 * When using in-kernel BTI we need to ensure that PCS-conक्रमmant assembly
 * functions have suitable annotations.  Override SYM_FUNC_START to insert
 * a BTI landing pad at the start of everything.
 */
#घोषणा SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)	\
	BTI_C

#घोषणा SYM_FUNC_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)	\
	BTI_C

#घोषणा SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)	\
	BTI_C

#घोषणा SYM_FUNC_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)	\
	BTI_C

#घोषणा SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)	\
	BTI_C

#घोषणा SYM_FUNC_START_WEAK_NOALIGN(name)		\
	SYM_START(name, SYM_L_WEAK, SYM_A_NONE)		\
	BTI_C

#पूर्ण_अगर

/*
 * Annotate a function as position independent, i.e., safe to be called beक्रमe
 * the kernel भव mapping is activated.
 */
#घोषणा SYM_FUNC_START_PI(x)			\
		SYM_FUNC_START_ALIAS(__pi_##x);	\
		SYM_FUNC_START(x)

#घोषणा SYM_FUNC_START_WEAK_PI(x)		\
		SYM_FUNC_START_ALIAS(__pi_##x);	\
		SYM_FUNC_START_WEAK(x)

#घोषणा SYM_FUNC_END_PI(x)			\
		SYM_FUNC_END(x);		\
		SYM_FUNC_END_ALIAS(__pi_##x)

#पूर्ण_अगर
