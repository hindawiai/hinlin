<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_SECTIONS_H
#घोषणा _ASM_ARM_SECTIONS_H

#समावेश <यंत्र-generic/sections.h>

बाह्य अक्षर _exiprom[];

बाह्य अक्षर __idmap_text_start[];
बाह्य अक्षर __idmap_text_end[];
बाह्य अक्षर __entry_text_start[];
बाह्य अक्षर __entry_text_end[];

अटल अंतरभूत bool in_entry_text(अचिन्हित दीर्घ addr)
अणु
	वापस memory_contains(__entry_text_start, __entry_text_end,
			       (व्योम *)addr, 1);
पूर्ण

अटल अंतरभूत bool in_idmap_text(अचिन्हित दीर्घ addr)
अणु
	व्योम *a = (व्योम *)addr;
	वापस memory_contains(__idmap_text_start, __idmap_text_end, a, 1);
पूर्ण

#पूर्ण_अगर	/* _ASM_ARM_SECTIONS_H */
