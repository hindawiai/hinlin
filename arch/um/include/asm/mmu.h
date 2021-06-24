<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __ARCH_UM_MMU_H
#घोषणा __ARCH_UM_MMU_H

#समावेश <mm_id.h>
#समावेश <यंत्र/mm_context.h>

प्रकार काष्ठा mm_context अणु
	काष्ठा mm_id id;
	काष्ठा uml_arch_mm_context arch;
	काष्ठा page *stub_pages[2];
पूर्ण mm_context_t;

बाह्य व्योम __चयन_mm(काष्ठा mm_id * mm_idp);

/* Aव्योम tangled inclusion with यंत्र/ldt.h */
बाह्य दीर्घ init_new_ldt(काष्ठा mm_context *to_mm, काष्ठा mm_context *from_mm);
बाह्य व्योम मुक्त_ldt(काष्ठा mm_context *mm);

#पूर्ण_अगर
