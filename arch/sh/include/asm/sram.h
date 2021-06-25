<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SRAM_H
#घोषणा __ASM_SRAM_H

#अगर_घोषित CONFIG_HAVE_SRAM_POOL

#समावेश <linux/spinlock.h>
#समावेश <linux/genभाग.स>

/* arch/sh/mm/sram.c */
बाह्य काष्ठा gen_pool *sram_pool;

अटल अंतरभूत अचिन्हित दीर्घ sram_alloc(माप_प्रकार len)
अणु
	अगर (!sram_pool)
		वापस 0UL;

	वापस gen_pool_alloc(sram_pool, len);
पूर्ण

अटल अंतरभूत व्योम sram_मुक्त(अचिन्हित दीर्घ addr, माप_प्रकार len)
अणु
	वापस gen_pool_मुक्त(sram_pool, addr, len);
पूर्ण

#अन्यथा

अटल अंतरभूत अचिन्हित दीर्घ sram_alloc(माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sram_मुक्त(अचिन्हित दीर्घ addr, माप_प्रकार len)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_SRAM_POOL */

#पूर्ण_अगर /* __ASM_SRAM_H */
