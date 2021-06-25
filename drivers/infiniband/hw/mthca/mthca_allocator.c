<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "mthca_dev.h"

/* Trivial biपंचांगap-based allocator */
u32 mthca_alloc(काष्ठा mthca_alloc *alloc)
अणु
	अचिन्हित दीर्घ flags;
	u32 obj;

	spin_lock_irqsave(&alloc->lock, flags);

	obj = find_next_zero_bit(alloc->table, alloc->max, alloc->last);
	अगर (obj >= alloc->max) अणु
		alloc->top = (alloc->top + alloc->max) & alloc->mask;
		obj = find_first_zero_bit(alloc->table, alloc->max);
	पूर्ण

	अगर (obj < alloc->max) अणु
		set_bit(obj, alloc->table);
		obj |= alloc->top;
	पूर्ण अन्यथा
		obj = -1;

	spin_unlock_irqrestore(&alloc->lock, flags);

	वापस obj;
पूर्ण

व्योम mthca_मुक्त(काष्ठा mthca_alloc *alloc, u32 obj)
अणु
	अचिन्हित दीर्घ flags;

	obj &= alloc->max - 1;

	spin_lock_irqsave(&alloc->lock, flags);

	clear_bit(obj, alloc->table);
	alloc->last = min(alloc->last, obj);
	alloc->top = (alloc->top + alloc->max) & alloc->mask;

	spin_unlock_irqrestore(&alloc->lock, flags);
पूर्ण

पूर्णांक mthca_alloc_init(काष्ठा mthca_alloc *alloc, u32 num, u32 mask,
		     u32 reserved)
अणु
	पूर्णांक i;

	/* num must be a घातer of 2 */
	अगर (num != 1 << (ffs(num) - 1))
		वापस -EINVAL;

	alloc->last = 0;
	alloc->top  = 0;
	alloc->max  = num;
	alloc->mask = mask;
	spin_lock_init(&alloc->lock);
	alloc->table = kदो_स्मृति_array(BITS_TO_LONGS(num), माप(दीर्घ),
				     GFP_KERNEL);
	अगर (!alloc->table)
		वापस -ENOMEM;

	biपंचांगap_zero(alloc->table, num);
	क्रम (i = 0; i < reserved; ++i)
		set_bit(i, alloc->table);

	वापस 0;
पूर्ण

व्योम mthca_alloc_cleanup(काष्ठा mthca_alloc *alloc)
अणु
	kमुक्त(alloc->table);
पूर्ण

/*
 * Array of poपूर्णांकers with lazy allocation of leaf pages.  Callers of
 * _get, _set and _clear methods must use a lock or otherwise
 * serialize access to the array.
 */

#घोषणा MTHCA_ARRAY_MASK (PAGE_SIZE / माप (व्योम *) - 1)

व्योम *mthca_array_get(काष्ठा mthca_array *array, पूर्णांक index)
अणु
	पूर्णांक p = (index * माप (व्योम *)) >> PAGE_SHIFT;

	अगर (array->page_list[p].page)
		वापस array->page_list[p].page[index & MTHCA_ARRAY_MASK];
	अन्यथा
		वापस शून्य;
पूर्ण

पूर्णांक mthca_array_set(काष्ठा mthca_array *array, पूर्णांक index, व्योम *value)
अणु
	पूर्णांक p = (index * माप (व्योम *)) >> PAGE_SHIFT;

	/* Allocate with GFP_ATOMIC because we'll be called with locks held. */
	अगर (!array->page_list[p].page)
		array->page_list[p].page = (व्योम **) get_zeroed_page(GFP_ATOMIC);

	अगर (!array->page_list[p].page)
		वापस -ENOMEM;

	array->page_list[p].page[index & MTHCA_ARRAY_MASK] = value;
	++array->page_list[p].used;

	वापस 0;
पूर्ण

व्योम mthca_array_clear(काष्ठा mthca_array *array, पूर्णांक index)
अणु
	पूर्णांक p = (index * माप (व्योम *)) >> PAGE_SHIFT;

	अगर (--array->page_list[p].used == 0) अणु
		मुक्त_page((अचिन्हित दीर्घ) array->page_list[p].page);
		array->page_list[p].page = शून्य;
	पूर्ण अन्यथा
		array->page_list[p].page[index & MTHCA_ARRAY_MASK] = शून्य;

	अगर (array->page_list[p].used < 0)
		pr_debug("Array %p index %d page %d with ref count %d < 0\n",
			 array, index, p, array->page_list[p].used);
पूर्ण

पूर्णांक mthca_array_init(काष्ठा mthca_array *array, पूर्णांक nent)
अणु
	पूर्णांक npage = (nent * माप (व्योम *) + PAGE_SIZE - 1) / PAGE_SIZE;
	पूर्णांक i;

	array->page_list = kदो_स्मृति_array(npage, माप(*array->page_list),
					 GFP_KERNEL);
	अगर (!array->page_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < npage; ++i) अणु
		array->page_list[i].page = शून्य;
		array->page_list[i].used = 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mthca_array_cleanup(काष्ठा mthca_array *array, पूर्णांक nent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (nent * माप (व्योम *) + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
		मुक्त_page((अचिन्हित दीर्घ) array->page_list[i].page);

	kमुक्त(array->page_list);
पूर्ण

/*
 * Handling क्रम queue buffers -- we allocate a bunch of memory and
 * रेजिस्टर it in a memory region at HCA भव address 0.  If the
 * requested size is > max_direct, we split the allocation पूर्णांकo
 * multiple pages, so we करोn't require too much contiguous memory.
 */

पूर्णांक mthca_buf_alloc(काष्ठा mthca_dev *dev, पूर्णांक size, पूर्णांक max_direct,
		    जोड़ mthca_buf *buf, पूर्णांक *is_direct, काष्ठा mthca_pd *pd,
		    पूर्णांक hca_ग_लिखो, काष्ठा mthca_mr *mr)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक npages, shअगरt;
	u64 *dma_list = शून्य;
	dma_addr_t t;
	पूर्णांक i;

	अगर (size <= max_direct) अणु
		*is_direct = 1;
		npages     = 1;
		shअगरt      = get_order(size) + PAGE_SHIFT;

		buf->direct.buf = dma_alloc_coherent(&dev->pdev->dev,
						     size, &t, GFP_KERNEL);
		अगर (!buf->direct.buf)
			वापस -ENOMEM;

		dma_unmap_addr_set(&buf->direct, mapping, t);

		जबतक (t & ((1 << shअगरt) - 1)) अणु
			--shअगरt;
			npages *= 2;
		पूर्ण

		dma_list = kदो_स्मृति_array(npages, माप(*dma_list),
					 GFP_KERNEL);
		अगर (!dma_list)
			जाओ err_मुक्त;

		क्रम (i = 0; i < npages; ++i)
			dma_list[i] = t + i * (1 << shअगरt);
	पूर्ण अन्यथा अणु
		*is_direct = 0;
		npages     = (size + PAGE_SIZE - 1) / PAGE_SIZE;
		shअगरt      = PAGE_SHIFT;

		dma_list = kदो_स्मृति_array(npages, माप(*dma_list),
					 GFP_KERNEL);
		अगर (!dma_list)
			वापस -ENOMEM;

		buf->page_list = kदो_स्मृति_array(npages,
					       माप(*buf->page_list),
					       GFP_KERNEL);
		अगर (!buf->page_list)
			जाओ err_out;

		क्रम (i = 0; i < npages; ++i)
			buf->page_list[i].buf = शून्य;

		क्रम (i = 0; i < npages; ++i) अणु
			buf->page_list[i].buf =
				dma_alloc_coherent(&dev->pdev->dev, PAGE_SIZE,
						   &t, GFP_KERNEL);
			अगर (!buf->page_list[i].buf)
				जाओ err_मुक्त;

			dma_list[i] = t;
			dma_unmap_addr_set(&buf->page_list[i], mapping, t);

			clear_page(buf->page_list[i].buf);
		पूर्ण
	पूर्ण

	err = mthca_mr_alloc_phys(dev, pd->pd_num,
				  dma_list, shअगरt, npages,
				  0, size,
				  MTHCA_MPT_FLAG_LOCAL_READ |
				  (hca_ग_लिखो ? MTHCA_MPT_FLAG_LOCAL_WRITE : 0),
				  mr);
	अगर (err)
		जाओ err_मुक्त;

	kमुक्त(dma_list);

	वापस 0;

err_मुक्त:
	mthca_buf_मुक्त(dev, size, buf, *is_direct, शून्य);

err_out:
	kमुक्त(dma_list);

	वापस err;
पूर्ण

व्योम mthca_buf_मुक्त(काष्ठा mthca_dev *dev, पूर्णांक size, जोड़ mthca_buf *buf,
		    पूर्णांक is_direct, काष्ठा mthca_mr *mr)
अणु
	पूर्णांक i;

	अगर (mr)
		mthca_मुक्त_mr(dev, mr);

	अगर (is_direct)
		dma_मुक्त_coherent(&dev->pdev->dev, size, buf->direct.buf,
				  dma_unmap_addr(&buf->direct, mapping));
	अन्यथा अणु
		क्रम (i = 0; i < (size + PAGE_SIZE - 1) / PAGE_SIZE; ++i)
			dma_मुक्त_coherent(&dev->pdev->dev, PAGE_SIZE,
					  buf->page_list[i].buf,
					  dma_unmap_addr(&buf->page_list[i],
							 mapping));
		kमुक्त(buf->page_list);
	पूर्ण
पूर्ण
