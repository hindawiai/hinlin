<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __ASM_POWERPC_FEATURE_FIXUPS_H
#घोषणा __ASM_POWERPC_FEATURE_FIXUPS_H

#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 */

/*
 * Feature section common macros
 *
 * Note that the entries now contain offsets between the table entry
 * and the code rather than असलolute code poपूर्णांकers in order to be
 * useable with the vdso shared library. There is also an assumption
 * that values will be negative, that is, the fixup table has to be
 * located after the code it fixes up.
 */
#अगर defined(CONFIG_PPC64) && !defined(__घातerpc64__)
/* 64 bits kernel, 32 bits code (ie. vdso32) */
#घोषणा FTR_ENTRY_LONG		.8byte
#घोषणा FTR_ENTRY_OFFSET	.दीर्घ 0xffffffff; .दीर्घ
#या_अगर defined(CONFIG_PPC64)
#घोषणा FTR_ENTRY_LONG		.8byte
#घोषणा FTR_ENTRY_OFFSET	.8byte
#अन्यथा
#घोषणा FTR_ENTRY_LONG		.दीर्घ
#घोषणा FTR_ENTRY_OFFSET	.दीर्घ
#पूर्ण_अगर

#घोषणा START_FTR_SECTION(label)	label##1:

#घोषणा FTR_SECTION_ELSE_NESTED(label)			\
label##2:						\
	.pushsection __ftr_alt_##label,"a";		\
	.align 2;					\
label##3:


#अगर_अघोषित CONFIG_CC_IS_CLANG
#घोषणा CHECK_ALT_SIZE(अन्यथा_size, body_size)			\
	.अगरgt (अन्यथा_size) - (body_size);			\
	.error "Feature section else case larger than body";	\
	.endअगर;
#अन्यथा
/*
 * If we use the अगरgt syntax above, clang's assembler complains about the
 * expression being non-असलolute when the code appears in an अंतरभूत assembly
 * statement.
 * As a workaround use an .org directive that has no effect अगर the अन्यथा हाल
 * inकाष्ठाions are smaller than the body, but fails otherwise.
 */
#घोषणा CHECK_ALT_SIZE(अन्यथा_size, body_size)			\
	.org . + ((अन्यथा_size) > (body_size));
#पूर्ण_अगर

#घोषणा MAKE_FTR_SECTION_ENTRY(msk, val, label, sect)		\
label##4:							\
	.popsection;						\
	.pushsection sect,"a";					\
	.align 3;						\
label##5:							\
	FTR_ENTRY_LONG msk;					\
	FTR_ENTRY_LONG val;					\
	FTR_ENTRY_OFFSET label##1b-label##5b;			\
	FTR_ENTRY_OFFSET label##2b-label##5b;			\
	FTR_ENTRY_OFFSET label##3b-label##5b;			\
	FTR_ENTRY_OFFSET label##4b-label##5b;			\
	CHECK_ALT_SIZE((label##4b-label##3b), (label##2b-label##1b)); \
	.popsection;


/* CPU feature dependent sections */
#घोषणा BEGIN_FTR_SECTION_NESTED(label)	START_FTR_SECTION(label)
#घोषणा BEGIN_FTR_SECTION		START_FTR_SECTION(97)

#घोषणा END_FTR_SECTION_NESTED(msk, val, label) 		\
	FTR_SECTION_ELSE_NESTED(label)				\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __ftr_fixup)

#घोषणा END_FTR_SECTION(msk, val)		\
	END_FTR_SECTION_NESTED(msk, val, 97)

#घोषणा END_FTR_SECTION_NESTED_IFSET(msk, label)	\
	END_FTR_SECTION_NESTED((msk), (msk), label)

#घोषणा END_FTR_SECTION_IFSET(msk)	END_FTR_SECTION((msk), (msk))
#घोषणा END_FTR_SECTION_IFCLR(msk)	END_FTR_SECTION((msk), 0)

/* CPU feature sections with alternatives, use BEGIN_FTR_SECTION to start */
#घोषणा FTR_SECTION_ELSE	FTR_SECTION_ELSE_NESTED(97)
#घोषणा ALT_FTR_SECTION_END_NESTED(msk, val, label)	\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __ftr_fixup)
#घोषणा ALT_FTR_SECTION_END_NESTED_IFSET(msk, label)	\
	ALT_FTR_SECTION_END_NESTED(msk, msk, label)
#घोषणा ALT_FTR_SECTION_END_NESTED_IFCLR(msk, label)	\
	ALT_FTR_SECTION_END_NESTED(msk, 0, label)
#घोषणा ALT_FTR_SECTION_END(msk, val)	\
	ALT_FTR_SECTION_END_NESTED(msk, val, 97)
#घोषणा ALT_FTR_SECTION_END_IFSET(msk)	\
	ALT_FTR_SECTION_END_NESTED_IFSET(msk, 97)
#घोषणा ALT_FTR_SECTION_END_IFCLR(msk)	\
	ALT_FTR_SECTION_END_NESTED_IFCLR(msk, 97)

/* MMU feature dependent sections */
#घोषणा BEGIN_MMU_FTR_SECTION_NESTED(label)	START_FTR_SECTION(label)
#घोषणा BEGIN_MMU_FTR_SECTION			START_FTR_SECTION(97)

#घोषणा END_MMU_FTR_SECTION_NESTED(msk, val, label) 		\
	FTR_SECTION_ELSE_NESTED(label)				\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __mmu_ftr_fixup)

#घोषणा END_MMU_FTR_SECTION(msk, val)		\
	END_MMU_FTR_SECTION_NESTED(msk, val, 97)

#घोषणा END_MMU_FTR_SECTION_NESTED_IFSET(msk, label)	\
	END_MMU_FTR_SECTION_NESTED((msk), (msk), label)

#घोषणा END_MMU_FTR_SECTION_NESTED_IFCLR(msk, label)	\
	END_MMU_FTR_SECTION_NESTED((msk), 0, label)

#घोषणा END_MMU_FTR_SECTION_IFSET(msk)	END_MMU_FTR_SECTION((msk), (msk))
#घोषणा END_MMU_FTR_SECTION_IFCLR(msk)	END_MMU_FTR_SECTION((msk), 0)

/* MMU feature sections with alternatives, use BEGIN_FTR_SECTION to start */
#घोषणा MMU_FTR_SECTION_ELSE_NESTED(label)	FTR_SECTION_ELSE_NESTED(label)
#घोषणा MMU_FTR_SECTION_ELSE	MMU_FTR_SECTION_ELSE_NESTED(97)
#घोषणा ALT_MMU_FTR_SECTION_END_NESTED(msk, val, label)	\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __mmu_ftr_fixup)
#घोषणा ALT_MMU_FTR_SECTION_END_NESTED_IFSET(msk, label)	\
	ALT_MMU_FTR_SECTION_END_NESTED(msk, msk, label)
#घोषणा ALT_MMU_FTR_SECTION_END_NESTED_IFCLR(msk, label)	\
	ALT_MMU_FTR_SECTION_END_NESTED(msk, 0, label)
#घोषणा ALT_MMU_FTR_SECTION_END(msk, val)	\
	ALT_MMU_FTR_SECTION_END_NESTED(msk, val, 97)
#घोषणा ALT_MMU_FTR_SECTION_END_IFSET(msk)	\
	ALT_MMU_FTR_SECTION_END_NESTED_IFSET(msk, 97)
#घोषणा ALT_MMU_FTR_SECTION_END_IFCLR(msk)	\
	ALT_MMU_FTR_SECTION_END_NESTED_IFCLR(msk, 97)

/* Firmware feature dependent sections */
#घोषणा BEGIN_FW_FTR_SECTION_NESTED(label)	START_FTR_SECTION(label)
#घोषणा BEGIN_FW_FTR_SECTION			START_FTR_SECTION(97)

#घोषणा END_FW_FTR_SECTION_NESTED(msk, val, label) 		\
	FTR_SECTION_ELSE_NESTED(label)				\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __fw_ftr_fixup)

#घोषणा END_FW_FTR_SECTION(msk, val)		\
	END_FW_FTR_SECTION_NESTED(msk, val, 97)

#घोषणा END_FW_FTR_SECTION_IFSET(msk)	END_FW_FTR_SECTION((msk), (msk))
#घोषणा END_FW_FTR_SECTION_IFCLR(msk)	END_FW_FTR_SECTION((msk), 0)

/* Firmware feature sections with alternatives */
#घोषणा FW_FTR_SECTION_ELSE_NESTED(label)	FTR_SECTION_ELSE_NESTED(label)
#घोषणा FW_FTR_SECTION_ELSE	FTR_SECTION_ELSE_NESTED(97)
#घोषणा ALT_FW_FTR_SECTION_END_NESTED(msk, val, label)	\
	MAKE_FTR_SECTION_ENTRY(msk, val, label, __fw_ftr_fixup)
#घोषणा ALT_FW_FTR_SECTION_END_NESTED_IFSET(msk, label)	\
	ALT_FW_FTR_SECTION_END_NESTED(msk, msk, label)
#घोषणा ALT_FW_FTR_SECTION_END_NESTED_IFCLR(msk, label)	\
	ALT_FW_FTR_SECTION_END_NESTED(msk, 0, label)
#घोषणा ALT_FW_FTR_SECTION_END(msk, val)	\
	ALT_FW_FTR_SECTION_END_NESTED(msk, val, 97)
#घोषणा ALT_FW_FTR_SECTION_END_IFSET(msk)	\
	ALT_FW_FTR_SECTION_END_NESTED_IFSET(msk, 97)
#घोषणा ALT_FW_FTR_SECTION_END_IFCLR(msk)	\
	ALT_FW_FTR_SECTION_END_NESTED_IFCLR(msk, 97)

#अगर_अघोषित __ASSEMBLY__

#घोषणा ASM_FTR_IF(section_अगर, section_अन्यथा, msk, val)	\
	stringअगरy_in_c(BEGIN_FTR_SECTION)			\
	section_अगर "; "						\
	stringअगरy_in_c(FTR_SECTION_ELSE)			\
	section_अन्यथा "; "					\
	stringअगरy_in_c(ALT_FTR_SECTION_END((msk), (val)))

#घोषणा ASM_FTR_IFSET(section_अगर, section_अन्यथा, msk)	\
	ASM_FTR_IF(section_अगर, section_अन्यथा, (msk), (msk))

#घोषणा ASM_FTR_IFCLR(section_अगर, section_अन्यथा, msk)	\
	ASM_FTR_IF(section_अगर, section_अन्यथा, (msk), 0)

#घोषणा ASM_MMU_FTR_IF(section_अगर, section_अन्यथा, msk, val)	\
	stringअगरy_in_c(BEGIN_MMU_FTR_SECTION)			\
	section_अगर "; "						\
	stringअगरy_in_c(MMU_FTR_SECTION_ELSE)			\
	section_अन्यथा "; "					\
	stringअगरy_in_c(ALT_MMU_FTR_SECTION_END((msk), (val)))

#घोषणा ASM_MMU_FTR_IFSET(section_अगर, section_अन्यथा, msk)	\
	ASM_MMU_FTR_IF(section_अगर, section_अन्यथा, (msk), (msk))

#घोषणा ASM_MMU_FTR_IFCLR(section_अगर, section_अन्यथा, msk)	\
	ASM_MMU_FTR_IF(section_अगर, section_अन्यथा, (msk), 0)

#पूर्ण_अगर /* __ASSEMBLY__ */

/* LWSYNC feature sections */
#घोषणा START_LWSYNC_SECTION(label)	label##1:
#घोषणा MAKE_LWSYNC_SECTION_ENTRY(label, sect)		\
label##2:						\
	.pushsection sect,"a";				\
	.align 2;					\
label##3:					       	\
	FTR_ENTRY_OFFSET label##1b-label##3b;		\
	.popsection;

#घोषणा STF_ENTRY_BARRIER_FIXUP_SECTION			\
953:							\
	.pushsection __stf_entry_barrier_fixup,"a";	\
	.align 2;					\
954:							\
	FTR_ENTRY_OFFSET 953b-954b;			\
	.popsection;

#घोषणा STF_EXIT_BARRIER_FIXUP_SECTION			\
955:							\
	.pushsection __stf_निकास_barrier_fixup,"a";	\
	.align 2;					\
956:							\
	FTR_ENTRY_OFFSET 955b-956b;			\
	.popsection;

#घोषणा UACCESS_FLUSH_FIXUP_SECTION			\
959:							\
	.pushsection __uaccess_flush_fixup,"a";		\
	.align 2;					\
960:							\
	FTR_ENTRY_OFFSET 959b-960b;			\
	.popsection;

#घोषणा ENTRY_FLUSH_FIXUP_SECTION			\
957:							\
	.pushsection __entry_flush_fixup,"a";		\
	.align 2;					\
958:							\
	FTR_ENTRY_OFFSET 957b-958b;			\
	.popsection;

#घोषणा SCV_ENTRY_FLUSH_FIXUP_SECTION			\
957:							\
	.pushsection __scv_entry_flush_fixup,"a";	\
	.align 2;					\
958:							\
	FTR_ENTRY_OFFSET 957b-958b;			\
	.popsection;

#घोषणा RFI_FLUSH_FIXUP_SECTION				\
951:							\
	.pushsection __rfi_flush_fixup,"a";		\
	.align 2;					\
952:							\
	FTR_ENTRY_OFFSET 951b-952b;			\
	.popsection;

#घोषणा NOSPEC_BARRIER_FIXUP_SECTION			\
953:							\
	.pushsection __barrier_nospec_fixup,"a";	\
	.align 2;					\
954:							\
	FTR_ENTRY_OFFSET 953b-954b;			\
	.popsection;

#घोषणा START_BTB_FLUSH_SECTION			\
955:							\

#घोषणा END_BTB_FLUSH_SECTION			\
956:							\
	.pushsection __btb_flush_fixup,"a";	\
	.align 2;							\
957:						\
	FTR_ENTRY_OFFSET 955b-957b;			\
	FTR_ENTRY_OFFSET 956b-957b;			\
	.popsection;

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

बाह्य दीर्घ stf_barrier_fallback;
बाह्य दीर्घ entry_flush_fallback;
बाह्य दीर्घ scv_entry_flush_fallback;
बाह्य दीर्घ __start___stf_entry_barrier_fixup, __stop___stf_entry_barrier_fixup;
बाह्य दीर्घ __start___stf_निकास_barrier_fixup, __stop___stf_निकास_barrier_fixup;
बाह्य दीर्घ __start___uaccess_flush_fixup, __stop___uaccess_flush_fixup;
बाह्य दीर्घ __start___entry_flush_fixup, __stop___entry_flush_fixup;
बाह्य दीर्घ __start___scv_entry_flush_fixup, __stop___scv_entry_flush_fixup;
बाह्य दीर्घ __start___rfi_flush_fixup, __stop___rfi_flush_fixup;
बाह्य दीर्घ __start___barrier_nospec_fixup, __stop___barrier_nospec_fixup;
बाह्य दीर्घ __start__btb_flush_fixup, __stop__btb_flush_fixup;

व्योम apply_feature_fixups(व्योम);
व्योम setup_feature_keys(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_POWERPC_FEATURE_FIXUPS_H */
