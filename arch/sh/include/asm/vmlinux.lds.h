<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_VMLINUX_LDS_H
#घोषणा __ASM_SH_VMLINUX_LDS_H

#समावेश <यंत्र-generic/vmlinux.lds.h>

#अगर_घोषित CONFIG_DWARF_UNWINDER
#घोषणा DWARF_EH_FRAME							\
	.eh_frame : AT(ADDR(.eh_frame) - LOAD_OFFSET) अणु			\
		  __start_eh_frame = .;					\
		  *(.eh_frame)						\
		  __stop_eh_frame = .;					\
	पूर्ण
#अन्यथा
#घोषणा DWARF_EH_FRAME
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_VMLINUX_LDS_H */
