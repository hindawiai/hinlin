<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arm64 KFENCE support.
 *
 * Copyright (C) 2020, Google LLC.
 */

#अगर_अघोषित __ASM_KFENCE_H
#घोषणा __ASM_KFENCE_H

#समावेश <यंत्र/cacheflush.h>

अटल अंतरभूत bool arch_kfence_init_pool(व्योम) अणु वापस true; पूर्ण

अटल अंतरभूत bool kfence_protect_page(अचिन्हित दीर्घ addr, bool protect)
अणु
	set_memory_valid(addr, 1, !protect);

	वापस true;
पूर्ण

#पूर्ण_अगर /* __ASM_KFENCE_H */
