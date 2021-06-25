<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CMA DebugFS Interface
 *
 * Copyright (c) 2015 Sasha Levin <sasha.levin@oracle.com>
 */


#समावेश <linux/debugfs.h>
#समावेश <linux/cma.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>

#समावेश "cma.h"

काष्ठा cma_mem अणु
	काष्ठा hlist_node node;
	काष्ठा page *p;
	अचिन्हित दीर्घ n;
पूर्ण;

अटल पूर्णांक cma_debugfs_get(व्योम *data, u64 *val)
अणु
	अचिन्हित दीर्घ *p = data;

	*val = *p;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(cma_debugfs_fops, cma_debugfs_get, शून्य, "%llu\n");

अटल पूर्णांक cma_used_get(व्योम *data, u64 *val)
अणु
	काष्ठा cma *cma = data;
	अचिन्हित दीर्घ used;

	spin_lock_irq(&cma->lock);
	/* pages counter is smaller than माप(पूर्णांक) */
	used = biपंचांगap_weight(cma->biपंचांगap, (पूर्णांक)cma_biपंचांगap_maxno(cma));
	spin_unlock_irq(&cma->lock);
	*val = (u64)used << cma->order_per_bit;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(cma_used_fops, cma_used_get, शून्य, "%llu\n");

अटल पूर्णांक cma_maxchunk_get(व्योम *data, u64 *val)
अणु
	काष्ठा cma *cma = data;
	अचिन्हित दीर्घ maxchunk = 0;
	अचिन्हित दीर्घ start, end = 0;
	अचिन्हित दीर्घ biपंचांगap_maxno = cma_biपंचांगap_maxno(cma);

	spin_lock_irq(&cma->lock);
	क्रम (;;) अणु
		start = find_next_zero_bit(cma->biपंचांगap, biपंचांगap_maxno, end);
		अगर (start >= biपंचांगap_maxno)
			अवरोध;
		end = find_next_bit(cma->biपंचांगap, biपंचांगap_maxno, start);
		maxchunk = max(end - start, maxchunk);
	पूर्ण
	spin_unlock_irq(&cma->lock);
	*val = (u64)maxchunk << cma->order_per_bit;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(cma_maxchunk_fops, cma_maxchunk_get, शून्य, "%llu\n");

अटल व्योम cma_add_to_cma_mem_list(काष्ठा cma *cma, काष्ठा cma_mem *mem)
अणु
	spin_lock(&cma->mem_head_lock);
	hlist_add_head(&mem->node, &cma->mem_head);
	spin_unlock(&cma->mem_head_lock);
पूर्ण

अटल काष्ठा cma_mem *cma_get_entry_from_list(काष्ठा cma *cma)
अणु
	काष्ठा cma_mem *mem = शून्य;

	spin_lock(&cma->mem_head_lock);
	अगर (!hlist_empty(&cma->mem_head)) अणु
		mem = hlist_entry(cma->mem_head.first, काष्ठा cma_mem, node);
		hlist_del_init(&mem->node);
	पूर्ण
	spin_unlock(&cma->mem_head_lock);

	वापस mem;
पूर्ण

अटल पूर्णांक cma_मुक्त_mem(काष्ठा cma *cma, पूर्णांक count)
अणु
	काष्ठा cma_mem *mem = शून्य;

	जबतक (count) अणु
		mem = cma_get_entry_from_list(cma);
		अगर (mem == शून्य)
			वापस 0;

		अगर (mem->n <= count) अणु
			cma_release(cma, mem->p, mem->n);
			count -= mem->n;
			kमुक्त(mem);
		पूर्ण अन्यथा अगर (cma->order_per_bit == 0) अणु
			cma_release(cma, mem->p, count);
			mem->p += count;
			mem->n -= count;
			count = 0;
			cma_add_to_cma_mem_list(cma, mem);
		पूर्ण अन्यथा अणु
			pr_debug("cma: cannot release partial block when order_per_bit != 0\n");
			cma_add_to_cma_mem_list(cma, mem);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक cma_मुक्त_ग_लिखो(व्योम *data, u64 val)
अणु
	पूर्णांक pages = val;
	काष्ठा cma *cma = data;

	वापस cma_मुक्त_mem(cma, pages);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(cma_मुक्त_fops, शून्य, cma_मुक्त_ग_लिखो, "%llu\n");

अटल पूर्णांक cma_alloc_mem(काष्ठा cma *cma, पूर्णांक count)
अणु
	काष्ठा cma_mem *mem;
	काष्ठा page *p;

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	p = cma_alloc(cma, count, 0, false);
	अगर (!p) अणु
		kमुक्त(mem);
		वापस -ENOMEM;
	पूर्ण

	mem->p = p;
	mem->n = count;

	cma_add_to_cma_mem_list(cma, mem);

	वापस 0;
पूर्ण

अटल पूर्णांक cma_alloc_ग_लिखो(व्योम *data, u64 val)
अणु
	पूर्णांक pages = val;
	काष्ठा cma *cma = data;

	वापस cma_alloc_mem(cma, pages);
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(cma_alloc_fops, शून्य, cma_alloc_ग_लिखो, "%llu\n");

अटल व्योम cma_debugfs_add_one(काष्ठा cma *cma, काष्ठा dentry *root_dentry)
अणु
	काष्ठा dentry *पंचांगp;
	अक्षर name[16];

	scnम_लिखो(name, माप(name), "cma-%s", cma->name);

	पंचांगp = debugfs_create_dir(name, root_dentry);

	debugfs_create_file("alloc", 0200, पंचांगp, cma, &cma_alloc_fops);
	debugfs_create_file("free", 0200, पंचांगp, cma, &cma_मुक्त_fops);
	debugfs_create_file("base_pfn", 0444, पंचांगp,
			    &cma->base_pfn, &cma_debugfs_fops);
	debugfs_create_file("count", 0444, पंचांगp, &cma->count, &cma_debugfs_fops);
	debugfs_create_file("order_per_bit", 0444, पंचांगp,
			    &cma->order_per_bit, &cma_debugfs_fops);
	debugfs_create_file("used", 0444, पंचांगp, cma, &cma_used_fops);
	debugfs_create_file("maxchunk", 0444, पंचांगp, cma, &cma_maxchunk_fops);

	cma->dfs_biपंचांगap.array = (u32 *)cma->biपंचांगap;
	cma->dfs_biपंचांगap.n_elements = DIV_ROUND_UP(cma_biपंचांगap_maxno(cma),
						  BITS_PER_BYTE * माप(u32));
	debugfs_create_u32_array("bitmap", 0444, पंचांगp, &cma->dfs_biपंचांगap);
पूर्ण

अटल पूर्णांक __init cma_debugfs_init(व्योम)
अणु
	काष्ठा dentry *cma_debugfs_root;
	पूर्णांक i;

	cma_debugfs_root = debugfs_create_dir("cma", शून्य);

	क्रम (i = 0; i < cma_area_count; i++)
		cma_debugfs_add_one(&cma_areas[i], cma_debugfs_root);

	वापस 0;
पूर्ण
late_initcall(cma_debugfs_init);
