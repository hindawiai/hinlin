<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * samples/kmemleak/kmemleak-test.c
 *
 * Copyright (C) 2008 ARM Limited
 * Written by Catalin Marinas <catalin.marinas@arm.com>
 */

#घोषणा pr_fmt(fmt) "kmemleak: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/list.h>
#समावेश <linux/percpu.h>
#समावेश <linux/fdtable.h>

#समावेश <linux/kmemleak.h>

काष्ठा test_node अणु
	दीर्घ header[25];
	काष्ठा list_head list;
	दीर्घ footer[25];
पूर्ण;

अटल LIST_HEAD(test_list);
अटल DEFINE_PER_CPU(व्योम *, kmemleak_test_poपूर्णांकer);

/*
 * Some very simple testing. This function needs to be extended क्रम
 * proper testing.
 */
अटल पूर्णांक __init kmemleak_test_init(व्योम)
अणु
	काष्ठा test_node *elem;
	पूर्णांक i;

	pr_info("Kmemleak testing\n");

	/* make some orphan objects */
	pr_info("kmalloc(32) = %p\n", kदो_स्मृति(32, GFP_KERNEL));
	pr_info("kmalloc(32) = %p\n", kदो_स्मृति(32, GFP_KERNEL));
	pr_info("kmalloc(1024) = %p\n", kदो_स्मृति(1024, GFP_KERNEL));
	pr_info("kmalloc(1024) = %p\n", kदो_स्मृति(1024, GFP_KERNEL));
	pr_info("kmalloc(2048) = %p\n", kदो_स्मृति(2048, GFP_KERNEL));
	pr_info("kmalloc(2048) = %p\n", kदो_स्मृति(2048, GFP_KERNEL));
	pr_info("kmalloc(4096) = %p\n", kदो_स्मृति(4096, GFP_KERNEL));
	pr_info("kmalloc(4096) = %p\n", kदो_स्मृति(4096, GFP_KERNEL));
#अगर_अघोषित CONFIG_MODULES
	pr_info("kmem_cache_alloc(files_cachep) = %p\n",
		kmem_cache_alloc(files_cachep, GFP_KERNEL));
	pr_info("kmem_cache_alloc(files_cachep) = %p\n",
		kmem_cache_alloc(files_cachep, GFP_KERNEL));
#पूर्ण_अगर
	pr_info("vmalloc(64) = %p\n", vदो_स्मृति(64));
	pr_info("vmalloc(64) = %p\n", vदो_स्मृति(64));
	pr_info("vmalloc(64) = %p\n", vदो_स्मृति(64));
	pr_info("vmalloc(64) = %p\n", vदो_स्मृति(64));
	pr_info("vmalloc(64) = %p\n", vदो_स्मृति(64));

	/*
	 * Add elements to a list. They should only appear as orphan
	 * after the module is हटाओd.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		elem = kzalloc(माप(*elem), GFP_KERNEL);
		pr_info("kzalloc(sizeof(*elem)) = %p\n", elem);
		अगर (!elem)
			वापस -ENOMEM;
		INIT_LIST_HEAD(&elem->list);
		list_add_tail(&elem->list, &test_list);
	पूर्ण

	क्रम_each_possible_cpu(i) अणु
		per_cpu(kmemleak_test_poपूर्णांकer, i) = kदो_स्मृति(129, GFP_KERNEL);
		pr_info("kmalloc(129) = %p\n",
			per_cpu(kmemleak_test_poपूर्णांकer, i));
	पूर्ण

	वापस 0;
पूर्ण
module_init(kmemleak_test_init);

अटल व्योम __निकास kmemleak_test_निकास(व्योम)
अणु
	काष्ठा test_node *elem, *पंचांगp;

	/*
	 * Remove the list elements without actually मुक्तing the
	 * memory.
	 */
	list_क्रम_each_entry_safe(elem, पंचांगp, &test_list, list)
		list_del(&elem->list);
पूर्ण
module_निकास(kmemleak_test_निकास);

MODULE_LICENSE("GPL");
