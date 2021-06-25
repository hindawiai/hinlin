<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "mock_dmabuf.h"

अटल काष्ठा sg_table *mock_map_dma_buf(काष्ठा dma_buf_attachment *attachment,
					 क्रमागत dma_data_direction dir)
अणु
	काष्ठा mock_dmabuf *mock = to_mock(attachment->dmabuf);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	पूर्णांक i, err;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस ERR_PTR(-ENOMEM);

	err = sg_alloc_table(st, mock->npages, GFP_KERNEL);
	अगर (err)
		जाओ err_मुक्त;

	sg = st->sgl;
	क्रम (i = 0; i < mock->npages; i++) अणु
		sg_set_page(sg, mock->pages[i], PAGE_SIZE, 0);
		sg = sg_next(sg);
	पूर्ण

	err = dma_map_sgtable(attachment->dev, st, dir, 0);
	अगर (err)
		जाओ err_st;

	वापस st;

err_st:
	sg_मुक्त_table(st);
err_मुक्त:
	kमुक्त(st);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mock_unmap_dma_buf(काष्ठा dma_buf_attachment *attachment,
			       काष्ठा sg_table *st,
			       क्रमागत dma_data_direction dir)
अणु
	dma_unmap_sgtable(attachment->dev, st, dir, 0);
	sg_मुक्त_table(st);
	kमुक्त(st);
पूर्ण

अटल व्योम mock_dmabuf_release(काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा mock_dmabuf *mock = to_mock(dma_buf);
	पूर्णांक i;

	क्रम (i = 0; i < mock->npages; i++)
		put_page(mock->pages[i]);

	kमुक्त(mock);
पूर्ण

अटल पूर्णांक mock_dmabuf_vmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा mock_dmabuf *mock = to_mock(dma_buf);
	व्योम *vaddr;

	vaddr = vm_map_ram(mock->pages, mock->npages, 0);
	अगर (!vaddr)
		वापस -ENOMEM;
	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

अटल व्योम mock_dmabuf_vunmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा mock_dmabuf *mock = to_mock(dma_buf);

	vm_unmap_ram(map->vaddr, mock->npages);
पूर्ण

अटल पूर्णांक mock_dmabuf_mmap(काष्ठा dma_buf *dma_buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops mock_dmabuf_ops =  अणु
	.map_dma_buf = mock_map_dma_buf,
	.unmap_dma_buf = mock_unmap_dma_buf,
	.release = mock_dmabuf_release,
	.mmap = mock_dmabuf_mmap,
	.vmap = mock_dmabuf_vmap,
	.vunmap = mock_dmabuf_vunmap,
पूर्ण;

अटल काष्ठा dma_buf *mock_dmabuf(पूर्णांक npages)
अणु
	काष्ठा mock_dmabuf *mock;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	काष्ठा dma_buf *dmabuf;
	पूर्णांक i;

	mock = kदो_स्मृति(माप(*mock) + npages * माप(काष्ठा page *),
		       GFP_KERNEL);
	अगर (!mock)
		वापस ERR_PTR(-ENOMEM);

	mock->npages = npages;
	क्रम (i = 0; i < npages; i++) अणु
		mock->pages[i] = alloc_page(GFP_KERNEL);
		अगर (!mock->pages[i])
			जाओ err;
	पूर्ण

	exp_info.ops = &mock_dmabuf_ops;
	exp_info.size = npages * PAGE_SIZE;
	exp_info.flags = O_CLOEXEC;
	exp_info.priv = mock;

	dmabuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(dmabuf))
		जाओ err;

	वापस dmabuf;

err:
	जबतक (i--)
		put_page(mock->pages[i]);
	kमुक्त(mock);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
