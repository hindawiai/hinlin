<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VDSO_EXTABLE_H
#घोषणा __VDSO_EXTABLE_H

/*
 * Inject exception fixup क्रम vDSO code.  Unlike normal exception fixup,
 * vDSO uses a dedicated handler the addresses are relative to the overall
 * exception table, not each inभागidual entry.
 */
#अगर_घोषित __ASSEMBLY__
#घोषणा _ASM_VDSO_EXTABLE_HANDLE(from, to)	\
	ASM_VDSO_EXTABLE_HANDLE from to

.macro ASM_VDSO_EXTABLE_HANDLE from:req to:req
	.pushsection __ex_table, "a"
	.दीर्घ (\पrom) - __ex_table
	.दीर्घ (\टo) - __ex_table
	.popsection
.endm
#अन्यथा
#घोषणा _ASM_VDSO_EXTABLE_HANDLE(from, to)	\
	".pushsection __ex_table, \"a\"\n"      \
	".long (" #from ") - __ex_table\n"      \
	".long (" #to ") - __ex_table\n"        \
	".popsection\n"
#पूर्ण_अगर

#पूर्ण_अगर /* __VDSO_EXTABLE_H */
