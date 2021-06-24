<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/setup.h>


व्योम * __ref zalloc_maybe_booपंचांगem(माप_प्रकार size, gfp_t mask)
अणु
	व्योम *p;

	अगर (slab_is_available())
		p = kzalloc(size, mask);
	अन्यथा अणु
		p = memblock_alloc(size, SMP_CACHE_BYTES);
		अगर (!p)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      size);
	पूर्ण
	वापस p;
पूर्ण
