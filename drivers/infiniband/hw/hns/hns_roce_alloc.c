<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "hns_roce_device.h"
#समावेश <rdma/ib_uस्मृति.स>

पूर्णांक hns_roce_biपंचांगap_alloc(काष्ठा hns_roce_biपंचांगap *biपंचांगap, अचिन्हित दीर्घ *obj)
अणु
	पूर्णांक ret = 0;

	spin_lock(&biपंचांगap->lock);
	*obj = find_next_zero_bit(biपंचांगap->table, biपंचांगap->max, biपंचांगap->last);
	अगर (*obj >= biपंचांगap->max) अणु
		biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
			       & biपंचांगap->mask;
		*obj = find_first_zero_bit(biपंचांगap->table, biपंचांगap->max);
	पूर्ण

	अगर (*obj < biपंचांगap->max) अणु
		set_bit(*obj, biपंचांगap->table);
		biपंचांगap->last = (*obj + 1);
		अगर (biपंचांगap->last == biपंचांगap->max)
			biपंचांगap->last = 0;
		*obj |= biपंचांगap->top;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	spin_unlock(&biपंचांगap->lock);

	वापस ret;
पूर्ण

व्योम hns_roce_biपंचांगap_मुक्त(काष्ठा hns_roce_biपंचांगap *biपंचांगap, अचिन्हित दीर्घ obj,
			  पूर्णांक rr)
अणु
	hns_roce_biपंचांगap_मुक्त_range(biपंचांगap, obj, 1, rr);
पूर्ण

पूर्णांक hns_roce_biपंचांगap_alloc_range(काष्ठा hns_roce_biपंचांगap *biपंचांगap, पूर्णांक cnt,
				पूर्णांक align, अचिन्हित दीर्घ *obj)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (likely(cnt == 1 && align == 1))
		वापस hns_roce_biपंचांगap_alloc(biपंचांगap, obj);

	spin_lock(&biपंचांगap->lock);

	*obj = biपंचांगap_find_next_zero_area(biपंचांगap->table, biपंचांगap->max,
					  biपंचांगap->last, cnt, align - 1);
	अगर (*obj >= biपंचांगap->max) अणु
		biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
			       & biपंचांगap->mask;
		*obj = biपंचांगap_find_next_zero_area(biपंचांगap->table, biपंचांगap->max, 0,
						  cnt, align - 1);
	पूर्ण

	अगर (*obj < biपंचांगap->max) अणु
		क्रम (i = 0; i < cnt; i++)
			set_bit(*obj + i, biपंचांगap->table);

		अगर (*obj == biपंचांगap->last) अणु
			biपंचांगap->last = (*obj + cnt);
			अगर (biपंचांगap->last >= biपंचांगap->max)
				biपंचांगap->last = 0;
		पूर्ण
		*obj |= biपंचांगap->top;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	spin_unlock(&biपंचांगap->lock);

	वापस ret;
पूर्ण

व्योम hns_roce_biपंचांगap_मुक्त_range(काष्ठा hns_roce_biपंचांगap *biपंचांगap,
				अचिन्हित दीर्घ obj, पूर्णांक cnt,
				पूर्णांक rr)
अणु
	पूर्णांक i;

	obj &= biपंचांगap->max + biपंचांगap->reserved_top - 1;

	spin_lock(&biपंचांगap->lock);
	क्रम (i = 0; i < cnt; i++)
		clear_bit(obj + i, biपंचांगap->table);

	अगर (!rr)
		biपंचांगap->last = min(biपंचांगap->last, obj);
	biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
		       & biपंचांगap->mask;
	spin_unlock(&biपंचांगap->lock);
पूर्ण

पूर्णांक hns_roce_biपंचांगap_init(काष्ठा hns_roce_biपंचांगap *biपंचांगap, u32 num, u32 mask,
			 u32 reserved_bot, u32 reserved_top)
अणु
	u32 i;

	अगर (num != roundup_घात_of_two(num))
		वापस -EINVAL;

	biपंचांगap->last = 0;
	biपंचांगap->top = 0;
	biपंचांगap->max = num - reserved_top;
	biपंचांगap->mask = mask;
	biपंचांगap->reserved_top = reserved_top;
	spin_lock_init(&biपंचांगap->lock);
	biपंचांगap->table = kसुस्मृति(BITS_TO_LONGS(biपंचांगap->max), माप(दीर्घ),
				GFP_KERNEL);
	अगर (!biपंचांगap->table)
		वापस -ENOMEM;

	क्रम (i = 0; i < reserved_bot; ++i)
		set_bit(i, biपंचांगap->table);

	वापस 0;
पूर्ण

व्योम hns_roce_biपंचांगap_cleanup(काष्ठा hns_roce_biपंचांगap *biपंचांगap)
अणु
	kमुक्त(biपंचांगap->table);
पूर्ण

व्योम hns_roce_buf_मुक्त(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_buf *buf)
अणु
	काष्ठा hns_roce_buf_list *trunks;
	u32 i;

	अगर (!buf)
		वापस;

	trunks = buf->trunk_list;
	अगर (trunks) अणु
		buf->trunk_list = शून्य;
		क्रम (i = 0; i < buf->ntrunks; i++)
			dma_मुक्त_coherent(hr_dev->dev, 1 << buf->trunk_shअगरt,
					  trunks[i].buf, trunks[i].map);

		kमुक्त(trunks);
	पूर्ण

	kमुक्त(buf);
पूर्ण

/*
 * Allocate the dma buffer क्रम storing ROCEE table entries
 *
 * @size: required size
 * @page_shअगरt: the unit size in a continuous dma address range
 * @flags: HNS_ROCE_BUF_ flags to control the allocation flow.
 */
काष्ठा hns_roce_buf *hns_roce_buf_alloc(काष्ठा hns_roce_dev *hr_dev, u32 size,
					u32 page_shअगरt, u32 flags)
अणु
	u32 trunk_size, page_size, alloced_size;
	काष्ठा hns_roce_buf_list *trunks;
	काष्ठा hns_roce_buf *buf;
	gfp_t gfp_flags;
	u32 ntrunk, i;

	/* The minimum shअगरt of the page accessed by hw is HNS_HW_PAGE_SHIFT */
	अगर (WARN_ON(page_shअगरt < HNS_HW_PAGE_SHIFT))
		वापस ERR_PTR(-EINVAL);

	gfp_flags = (flags & HNS_ROCE_BUF_NOSLEEP) ? GFP_ATOMIC : GFP_KERNEL;
	buf = kzalloc(माप(*buf), gfp_flags);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->page_shअगरt = page_shअगरt;
	page_size = 1 << buf->page_shअगरt;

	/* Calc the trunk size and num by required size and page_shअगरt */
	अगर (flags & HNS_ROCE_BUF_सूचीECT) अणु
		buf->trunk_shअगरt = ilog2(ALIGN(size, PAGE_SIZE));
		ntrunk = 1;
	पूर्ण अन्यथा अणु
		buf->trunk_shअगरt = ilog2(ALIGN(page_size, PAGE_SIZE));
		ntrunk = DIV_ROUND_UP(size, 1 << buf->trunk_shअगरt);
	पूर्ण

	trunks = kसुस्मृति(ntrunk, माप(*trunks), gfp_flags);
	अगर (!trunks) अणु
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	trunk_size = 1 << buf->trunk_shअगरt;
	alloced_size = 0;
	क्रम (i = 0; i < ntrunk; i++) अणु
		trunks[i].buf = dma_alloc_coherent(hr_dev->dev, trunk_size,
						   &trunks[i].map, gfp_flags);
		अगर (!trunks[i].buf)
			अवरोध;

		alloced_size += trunk_size;
	पूर्ण

	buf->ntrunks = i;

	/* In nofail mode, it's only failed when the alloced size is 0 */
	अगर ((flags & HNS_ROCE_BUF_NOFAIL) ? i == 0 : i != ntrunk) अणु
		क्रम (i = 0; i < buf->ntrunks; i++)
			dma_मुक्त_coherent(hr_dev->dev, trunk_size,
					  trunks[i].buf, trunks[i].map);

		kमुक्त(trunks);
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	buf->npages = DIV_ROUND_UP(alloced_size, page_size);
	buf->trunk_list = trunks;

	वापस buf;
पूर्ण

पूर्णांक hns_roce_get_kmem_bufs(काष्ठा hns_roce_dev *hr_dev, dma_addr_t *bufs,
			   पूर्णांक buf_cnt, पूर्णांक start, काष्ठा hns_roce_buf *buf)
अणु
	पूर्णांक i, end;
	पूर्णांक total;

	end = start + buf_cnt;
	अगर (end > buf->npages) अणु
		dev_err(hr_dev->dev,
			"failed to check kmem bufs, end %d + %d total %u!\n",
			start, buf_cnt, buf->npages);
		वापस -EINVAL;
	पूर्ण

	total = 0;
	क्रम (i = start; i < end; i++)
		bufs[total++] = hns_roce_buf_page(buf, i);

	वापस total;
पूर्ण

पूर्णांक hns_roce_get_umem_bufs(काष्ठा hns_roce_dev *hr_dev, dma_addr_t *bufs,
			   पूर्णांक buf_cnt, पूर्णांक start, काष्ठा ib_umem *umem,
			   अचिन्हित पूर्णांक page_shअगरt)
अणु
	काष्ठा ib_block_iter biter;
	पूर्णांक total = 0;
	पूर्णांक idx = 0;
	u64 addr;

	अगर (page_shअगरt < HNS_HW_PAGE_SHIFT) अणु
		dev_err(hr_dev->dev, "failed to check umem page shift %u!\n",
			page_shअगरt);
		वापस -EINVAL;
	पूर्ण

	/* convert प्रणाली page cnt to hw page cnt */
	rdma_umem_क्रम_each_dma_block(umem, &biter, 1 << page_shअगरt) अणु
		addr = rdma_block_iter_dma_address(&biter);
		अगर (idx >= start) अणु
			bufs[total++] = addr;
			अगर (total >= buf_cnt)
				जाओ करोne;
		पूर्ण
		idx++;
	पूर्ण

करोne:
	वापस total;
पूर्ण

व्योम hns_roce_cleanup_biपंचांगap(काष्ठा hns_roce_dev *hr_dev)
अणु
	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_XRC)
		hns_roce_cleanup_xrcd_table(hr_dev);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_SRQ)
		hns_roce_cleanup_srq_table(hr_dev);
	hns_roce_cleanup_qp_table(hr_dev);
	hns_roce_cleanup_cq_table(hr_dev);
	hns_roce_cleanup_mr_table(hr_dev);
	hns_roce_cleanup_pd_table(hr_dev);
	hns_roce_cleanup_uar_table(hr_dev);
पूर्ण
