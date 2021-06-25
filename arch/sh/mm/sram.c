<शैली गुरु>
/*
 * SRAM pool क्रम tiny memories not otherwise managed.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/sram.h>

/*
 * This provides a standard SRAM pool क्रम tiny memories that can be
 * added either by the CPU or the platक्रमm code. Typical SRAM sizes
 * to be inserted in to the pool will generally be less than the page
 * size, with anything more reasonably sized handled as a NUMA memory
 * node.
 */
काष्ठा gen_pool *sram_pool;

अटल पूर्णांक __init sram_pool_init(व्योम)
अणु
	/*
	 * This is a global pool, we करोn't care about node locality.
	 */
	sram_pool = gen_pool_create(1, -1);
	अगर (unlikely(!sram_pool))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
core_initcall(sram_pool_init);
