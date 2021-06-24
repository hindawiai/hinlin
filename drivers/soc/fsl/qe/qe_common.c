<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common CPM code
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright 2007-2008,2010 Freescale Semiconductor, Inc.
 *
 * Some parts derived from commproc.c/cpm2_common.c, which is:
 * Copyright (c) 1997 Dan error_act (dmalek@jlc.net)
 * Copyright (c) 1999-2001 Dan Malek <dan@embeddedalley.com>
 * Copyright (c) 2000 MontaVista Software, Inc (source@mvista.com)
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 */
#समावेश <linux/genभाग.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <soc/fsl/qe/qe.h>

अटल काष्ठा gen_pool *muram_pool;
अटल DEFINE_SPINLOCK(cpm_muram_lock);
अटल व्योम __iomem *muram_vbase;
अटल phys_addr_t muram_pbase;

काष्ठा muram_block अणु
	काष्ठा list_head head;
	s32 start;
	पूर्णांक size;
पूर्ण;

अटल LIST_HEAD(muram_block_list);

/* max address size we deal with */
#घोषणा OF_MAX_ADDR_CELLS	4
#घोषणा GENPOOL_OFFSET		(4096 * 8)

पूर्णांक cpm_muram_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;
	__be32 zero[OF_MAX_ADDR_CELLS] = अणुपूर्ण;
	resource_माप_प्रकार max = 0;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	अगर (muram_pbase)
		वापस 0;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,cpm-muram-data");
	अगर (!np) अणु
		/* try legacy bindings */
		np = of_find_node_by_name(शून्य, "data-only");
		अगर (!np) अणु
			pr_err("Cannot find CPM muram data node");
			ret = -ENODEV;
			जाओ out_muram;
		पूर्ण
	पूर्ण

	muram_pool = gen_pool_create(0, -1);
	अगर (!muram_pool) अणु
		pr_err("Cannot allocate memory pool for CPM/QE muram");
		ret = -ENOMEM;
		जाओ out_muram;
	पूर्ण
	muram_pbase = of_translate_address(np, zero);
	अगर (muram_pbase == (phys_addr_t)OF_BAD_ADDR) अणु
		pr_err("Cannot translate zero through CPM muram node");
		ret = -ENODEV;
		जाओ out_pool;
	पूर्ण

	जबतक (of_address_to_resource(np, i++, &r) == 0) अणु
		अगर (r.end > max)
			max = r.end;
		ret = gen_pool_add(muram_pool, r.start - muram_pbase +
				   GENPOOL_OFFSET, resource_size(&r), -1);
		अगर (ret) अणु
			pr_err("QE: couldn't add muram to pool!\n");
			जाओ out_pool;
		पूर्ण
	पूर्ण

	muram_vbase = ioremap(muram_pbase, max - muram_pbase + 1);
	अगर (!muram_vbase) अणु
		pr_err("Cannot map QE muram");
		ret = -ENOMEM;
		जाओ out_pool;
	पूर्ण
	जाओ out_muram;
out_pool:
	gen_pool_destroy(muram_pool);
out_muram:
	of_node_put(np);
	वापस ret;
पूर्ण

/*
 * cpm_muram_alloc_common - cpm_muram_alloc common code
 * @size: number of bytes to allocate
 * @algo: algorithm क्रम alloc.
 * @data: data क्रम genalloc's algorithm.
 *
 * This function वापसs a non-negative offset पूर्णांकo the muram area, or
 * a negative त्रुटि_सं on failure.
 */
अटल s32 cpm_muram_alloc_common(अचिन्हित दीर्घ size,
				  genpool_algo_t algo, व्योम *data)
अणु
	काष्ठा muram_block *entry;
	s32 start;

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;
	start = gen_pool_alloc_algo(muram_pool, size, algo, data);
	अगर (!start) अणु
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण
	start = start - GENPOOL_OFFSET;
	स_रखो_io(cpm_muram_addr(start), 0, size);
	entry->start = start;
	entry->size = size;
	list_add(&entry->head, &muram_block_list);

	वापस start;
पूर्ण

/*
 * cpm_muram_alloc - allocate the requested size worth of multi-user ram
 * @size: number of bytes to allocate
 * @align: requested alignment, in bytes
 *
 * This function वापसs a non-negative offset पूर्णांकo the muram area, or
 * a negative त्रुटि_सं on failure.
 * Use cpm_dpram_addr() to get the भव address of the area.
 * Use cpm_muram_मुक्त() to मुक्त the allocation.
 */
s32 cpm_muram_alloc(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align)
अणु
	s32 start;
	अचिन्हित दीर्घ flags;
	काष्ठा genpool_data_align muram_pool_data;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	muram_pool_data.align = align;
	start = cpm_muram_alloc_common(size, gen_pool_first_fit_align,
				       &muram_pool_data);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);
	वापस start;
पूर्ण
EXPORT_SYMBOL(cpm_muram_alloc);

/**
 * cpm_muram_मुक्त - मुक्त a chunk of multi-user ram
 * @offset: The beginning of the chunk as वापसed by cpm_muram_alloc().
 */
व्योम cpm_muram_मुक्त(s32 offset)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक size;
	काष्ठा muram_block *पंचांगp;

	अगर (offset < 0)
		वापस;

	size = 0;
	spin_lock_irqsave(&cpm_muram_lock, flags);
	list_क्रम_each_entry(पंचांगp, &muram_block_list, head) अणु
		अगर (पंचांगp->start == offset) अणु
			size = पंचांगp->size;
			list_del(&पंचांगp->head);
			kमुक्त(पंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण
	gen_pool_मुक्त(muram_pool, offset + GENPOOL_OFFSET, size);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);
पूर्ण
EXPORT_SYMBOL(cpm_muram_मुक्त);

/*
 * cpm_muram_alloc_fixed - reserve a specअगरic region of multi-user ram
 * @offset: offset of allocation start address
 * @size: number of bytes to allocate
 * This function वापसs @offset अगर the area was available, a negative
 * त्रुटि_सं otherwise.
 * Use cpm_dpram_addr() to get the भव address of the area.
 * Use cpm_muram_मुक्त() to मुक्त the allocation.
 */
s32 cpm_muram_alloc_fixed(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	s32 start;
	अचिन्हित दीर्घ flags;
	काष्ठा genpool_data_fixed muram_pool_data_fixed;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	muram_pool_data_fixed.offset = offset + GENPOOL_OFFSET;
	start = cpm_muram_alloc_common(size, gen_pool_fixed_alloc,
				       &muram_pool_data_fixed);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);
	वापस start;
पूर्ण
EXPORT_SYMBOL(cpm_muram_alloc_fixed);

/**
 * cpm_muram_addr - turn a muram offset पूर्णांकo a भव address
 * @offset: muram offset to convert
 */
व्योम __iomem *cpm_muram_addr(अचिन्हित दीर्घ offset)
अणु
	वापस muram_vbase + offset;
पूर्ण
EXPORT_SYMBOL(cpm_muram_addr);

अचिन्हित दीर्घ cpm_muram_offset(स्थिर व्योम __iomem *addr)
अणु
	वापस addr - muram_vbase;
पूर्ण
EXPORT_SYMBOL(cpm_muram_offset);

/**
 * cpm_muram_dma - turn a muram भव address पूर्णांकo a DMA address
 * @addr: भव address from cpm_muram_addr() to convert
 */
dma_addr_t cpm_muram_dma(व्योम __iomem *addr)
अणु
	वापस muram_pbase + (addr - muram_vbase);
पूर्ण
EXPORT_SYMBOL(cpm_muram_dma);

/*
 * As cpm_muram_मुक्त, but takes the भव address rather than the
 * muram offset.
 */
व्योम cpm_muram_मुक्त_addr(स्थिर व्योम __iomem *addr)
अणु
	अगर (!addr)
		वापस;
	cpm_muram_मुक्त(cpm_muram_offset(addr));
पूर्ण
EXPORT_SYMBOL(cpm_muram_मुक्त_addr);
