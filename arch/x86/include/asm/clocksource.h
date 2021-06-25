<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* x86-specअगरic घड़ीsource additions */

#अगर_अघोषित _ASM_X86_CLOCKSOURCE_H
#घोषणा _ASM_X86_CLOCKSOURCE_H

#समावेश <यंत्र/vdso/घड़ीsource.h>

बाह्य अचिन्हित पूर्णांक vघड़ीs_used;

अटल अंतरभूत bool vघड़ी_was_used(पूर्णांक vघड़ी)
अणु
	वापस READ_ONCE(vघड़ीs_used) & (1U << vघड़ी);
पूर्ण

अटल अंतरभूत व्योम vघड़ीs_set_used(अचिन्हित पूर्णांक which)
अणु
	WRITE_ONCE(vघड़ीs_used, READ_ONCE(vघड़ीs_used) | (1 << which));
पूर्ण

#पूर्ण_अगर /* _ASM_X86_CLOCKSOURCE_H */
