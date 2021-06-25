<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_DWARF_H
#घोषणा _ASM_S390_DWARF_H

#अगर_घोषित __ASSEMBLY__

#घोषणा CFI_STARTPROC		.cfi_startproc
#घोषणा CFI_ENDPROC		.cfi_endproc
#घोषणा CFI_DEF_CFA_OFFSET	.cfi_def_cfa_offset
#घोषणा CFI_ADJUST_CFA_OFFSET	.cfi_adjust_cfa_offset
#घोषणा CFI_RESTORE		.cfi_restore

#अगर_घोषित CONFIG_AS_CFI_VAL_OFFSET
#घोषणा CFI_VAL_OFFSET		.cfi_val_offset
#अन्यथा
#घोषणा CFI_VAL_OFFSET		#
#पूर्ण_अगर

#अगर_अघोषित BUILD_VDSO
	/*
	 * Emit CFI data in .debug_frame sections and not in .eh_frame
	 * sections.  The .eh_frame CFI is used क्रम runसमय unwind
	 * inक्रमmation that is not being used.  Hence, vmlinux.lds.S
	 * can discard the .eh_frame sections.
	 */
	.cfi_sections .debug_frame
#अन्यथा
	/*
	 * For vDSO, emit CFI data in both, .eh_frame and .debug_frame
	 * sections.
	 */
	.cfi_sections .eh_frame, .debug_frame
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_S390_DWARF_H */
