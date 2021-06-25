<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_EXTABLE_H
#घोषणा _ASM_IA64_EXTABLE_H

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

काष्ठा exception_table_entry अणु
	पूर्णांक insn;	/* location-relative address of insn this fixup is क्रम */
	पूर्णांक fixup;	/* location-relative continuation addr.; अगर bit 2 is set, r9 is set to 0 */
पूर्ण;

#पूर्ण_अगर
