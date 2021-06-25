<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DWARF2_H
#घोषणा _ASM_X86_DWARF2_H

#अगर_अघोषित __ASSEMBLY__
#warning "asm/dwarf2.h should be only included in pure assembly files"
#पूर्ण_अगर

#घोषणा CFI_STARTPROC		.cfi_startproc
#घोषणा CFI_ENDPROC		.cfi_endproc
#घोषणा CFI_DEF_CFA		.cfi_def_cfa
#घोषणा CFI_DEF_CFA_REGISTER	.cfi_def_cfa_रेजिस्टर
#घोषणा CFI_DEF_CFA_OFFSET	.cfi_def_cfa_offset
#घोषणा CFI_ADJUST_CFA_OFFSET	.cfi_adjust_cfa_offset
#घोषणा CFI_OFFSET		.cfi_offset
#घोषणा CFI_REL_OFFSET		.cfi_rel_offset
#घोषणा CFI_REGISTER		.cfi_रेजिस्टर
#घोषणा CFI_RESTORE		.cfi_restore
#घोषणा CFI_REMEMBER_STATE	.cfi_remember_state
#घोषणा CFI_RESTORE_STATE	.cfi_restore_state
#घोषणा CFI_UNDEFINED		.cfi_undefined
#घोषणा CFI_ESCAPE		.cfi_escape

#अगर_अघोषित BUILD_VDSO
	/*
	 * Emit CFI data in .debug_frame sections, not .eh_frame sections.
	 * The latter we currently just discard since we करोn't करो DWARF
	 * unwinding at runसमय.  So only the offline DWARF inक्रमmation is
	 * useful to anyone.  Note we should not use this directive अगर we
	 * ever decide to enable DWARF unwinding at runसमय.
	 */
	.cfi_sections .debug_frame
#अन्यथा
	 /*
	  * For the vDSO, emit both runसमय unwind inक्रमmation and debug
	  * symbols क्रम the .dbg file.
	  */
	.cfi_sections .eh_frame, .debug_frame
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_DWARF2_H */
