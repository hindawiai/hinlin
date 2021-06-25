<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright (c) 2020 Intel Corporation. All rights reserved.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/dma-mapping.h>

#समावेश "uverbs.h"

पूर्णांक ib_umem_dmabuf_map_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf)
अणु
	काष्ठा sg_table *sgt;
	काष्ठा scatterlist *sg;
	काष्ठा dma_fence *fence;
	अचिन्हित दीर्घ start, end, cur = 0;
	अचिन्हित पूर्णांक nmap = 0;
	पूर्णांक i;

	dma_resv_निश्चित_held(umem_dmabuf->attach->dmabuf->resv);

	अगर (umem_dmabuf->sgt)
		जाओ रुको_fence;

	sgt = dma_buf_map_attachment(umem_dmabuf->attach, DMA_BIसूचीECTIONAL);
	अगर (IS_ERR(sgt))
		वापस PTR_ERR(sgt);

	/* modअगरy the sg list in-place to match umem address and length */

	start = ALIGN_DOWN(umem_dmabuf->umem.address, PAGE_SIZE);
	end = ALIGN(umem_dmabuf->umem.address + umem_dmabuf->umem.length,
		    PAGE_SIZE);
	क्रम_each_sgtable_dma_sg(sgt, sg, i) अणु
		अगर (start < cur + sg_dma_len(sg) && cur < end)
			nmap++;
		अगर (cur <= start && start < cur + sg_dma_len(sg)) अणु
			अचिन्हित दीर्घ offset = start - cur;

			umem_dmabuf->first_sg = sg;
			umem_dmabuf->first_sg_offset = offset;
			sg_dma_address(sg) += offset;
			sg_dma_len(sg) -= offset;
			cur += offset;
		पूर्ण
		अगर (cur < end && end <= cur + sg_dma_len(sg)) अणु
			अचिन्हित दीर्घ trim = cur + sg_dma_len(sg) - end;

			umem_dmabuf->last_sg = sg;
			umem_dmabuf->last_sg_trim = trim;
			sg_dma_len(sg) -= trim;
			अवरोध;
		पूर्ण
		cur += sg_dma_len(sg);
	पूर्ण

	umem_dmabuf->umem.sg_head.sgl = umem_dmabuf->first_sg;
	umem_dmabuf->umem.sg_head.nents = nmap;
	umem_dmabuf->umem.nmap = nmap;
	umem_dmabuf->sgt = sgt;

रुको_fence:
	/*
	 * Although the sg list is valid now, the content of the pages
	 * may be not up-to-date. Wait क्रम the exporter to finish
	 * the migration.
	 */
	fence = dma_resv_get_excl(umem_dmabuf->attach->dmabuf->resv);
	अगर (fence)
		वापस dma_fence_रुको(fence, false);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_umem_dmabuf_map_pages);

व्योम ib_umem_dmabuf_unmap_pages(काष्ठा ib_umem_dmabuf *umem_dmabuf)
अणु
	dma_resv_निश्चित_held(umem_dmabuf->attach->dmabuf->resv);

	अगर (!umem_dmabuf->sgt)
		वापस;

	/* retore the original sg list */
	अगर (umem_dmabuf->first_sg) अणु
		sg_dma_address(umem_dmabuf->first_sg) -=
			umem_dmabuf->first_sg_offset;
		sg_dma_len(umem_dmabuf->first_sg) +=
			umem_dmabuf->first_sg_offset;
		umem_dmabuf->first_sg = शून्य;
		umem_dmabuf->first_sg_offset = 0;
	पूर्ण
	अगर (umem_dmabuf->last_sg) अणु
		sg_dma_len(umem_dmabuf->last_sg) +=
			umem_dmabuf->last_sg_trim;
		umem_dmabuf->last_sg = शून्य;
		umem_dmabuf->last_sg_trim = 0;
	पूर्ण

	dma_buf_unmap_attachment(umem_dmabuf->attach, umem_dmabuf->sgt,
				 DMA_BIसूचीECTIONAL);

	umem_dmabuf->sgt = शून्य;
पूर्ण
EXPORT_SYMBOL(ib_umem_dmabuf_unmap_pages);

काष्ठा ib_umem_dmabuf *ib_umem_dmabuf_get(काष्ठा ib_device *device,
					  अचिन्हित दीर्घ offset, माप_प्रकार size,
					  पूर्णांक fd, पूर्णांक access,
					  स्थिर काष्ठा dma_buf_attach_ops *ops)
अणु
	काष्ठा dma_buf *dmabuf;
	काष्ठा ib_umem_dmabuf *umem_dmabuf;
	काष्ठा ib_umem *umem;
	अचिन्हित दीर्घ end;
	काष्ठा ib_umem_dmabuf *ret = ERR_PTR(-EINVAL);

	अगर (check_add_overflow(offset, (अचिन्हित दीर्घ)size, &end))
		वापस ret;

	अगर (unlikely(!ops || !ops->move_notअगरy))
		वापस ret;

	dmabuf = dma_buf_get(fd);
	अगर (IS_ERR(dmabuf))
		वापस ERR_CAST(dmabuf);

	अगर (dmabuf->size < end)
		जाओ out_release_dmabuf;

	umem_dmabuf = kzalloc(माप(*umem_dmabuf), GFP_KERNEL);
	अगर (!umem_dmabuf) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ out_release_dmabuf;
	पूर्ण

	umem = &umem_dmabuf->umem;
	umem->ibdev = device;
	umem->length = size;
	umem->address = offset;
	umem->writable = ib_access_writable(access);
	umem->is_dmabuf = 1;

	अगर (!ib_umem_num_pages(umem))
		जाओ out_मुक्त_umem;

	umem_dmabuf->attach = dma_buf_dynamic_attach(
					dmabuf,
					device->dma_device,
					ops,
					umem_dmabuf);
	अगर (IS_ERR(umem_dmabuf->attach)) अणु
		ret = ERR_CAST(umem_dmabuf->attach);
		जाओ out_मुक्त_umem;
	पूर्ण
	वापस umem_dmabuf;

out_मुक्त_umem:
	kमुक्त(umem_dmabuf);

out_release_dmabuf:
	dma_buf_put(dmabuf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_umem_dmabuf_get);

व्योम ib_umem_dmabuf_release(काष्ठा ib_umem_dmabuf *umem_dmabuf)
अणु
	काष्ठा dma_buf *dmabuf = umem_dmabuf->attach->dmabuf;

	dma_resv_lock(dmabuf->resv, शून्य);
	ib_umem_dmabuf_unmap_pages(umem_dmabuf);
	dma_resv_unlock(dmabuf->resv);

	dma_buf_detach(dmabuf, umem_dmabuf->attach);
	dma_buf_put(dmabuf);
	kमुक्त(umem_dmabuf);
पूर्ण
