<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/platक्रमm/s5p-mfc/s5p_mfc_opr.c
 *
 * Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains hw related functions.
 *
 * Kamil Debski, Copyright (c) 2012 Samsung Electronics Co., Ltd.
 * http://www.samsung.com/
 */

#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_opr_v5.h"
#समावेश "s5p_mfc_opr_v6.h"

अटल काष्ठा s5p_mfc_hw_ops *s5p_mfc_ops;

व्योम s5p_mfc_init_hw_ops(काष्ठा s5p_mfc_dev *dev)
अणु
	अगर (IS_MFCV6_PLUS(dev)) अणु
		s5p_mfc_ops = s5p_mfc_init_hw_ops_v6();
		dev->warn_start = S5P_FIMV_ERR_WARNINGS_START_V6;
	पूर्ण अन्यथा अणु
		s5p_mfc_ops = s5p_mfc_init_hw_ops_v5();
		dev->warn_start = S5P_FIMV_ERR_WARNINGS_START;
	पूर्ण
	dev->mfc_ops = s5p_mfc_ops;
पूर्ण

व्योम s5p_mfc_init_regs(काष्ठा s5p_mfc_dev *dev)
अणु
	अगर (IS_MFCV6_PLUS(dev))
		dev->mfc_regs = s5p_mfc_init_regs_v6_plus(dev);
पूर्ण

पूर्णांक s5p_mfc_alloc_priv_buf(काष्ठा s5p_mfc_dev *dev, अचिन्हित पूर्णांक mem_ctx,
			   काष्ठा s5p_mfc_priv_buf *b)
अणु
	अचिन्हित पूर्णांक bits = dev->mem_size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक count = b->size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक align = (SZ_64K >> PAGE_SHIFT) - 1;
	अचिन्हित पूर्णांक start, offset;

	mfc_debug(3, "Allocating priv: %zu\n", b->size);

	अगर (dev->mem_virt) अणु
		start = biपंचांगap_find_next_zero_area(dev->mem_biपंचांगap, bits, 0, count, align);
		अगर (start > bits)
			जाओ no_mem;

		biपंचांगap_set(dev->mem_biपंचांगap, start, count);
		offset = start << PAGE_SHIFT;
		b->virt = dev->mem_virt + offset;
		b->dma = dev->mem_base + offset;
	पूर्ण अन्यथा अणु
		काष्ठा device *mem_dev = dev->mem_dev[mem_ctx];
		dma_addr_t base = dev->dma_base[mem_ctx];

		b->ctx = mem_ctx;
		b->virt = dma_alloc_coherent(mem_dev, b->size, &b->dma, GFP_KERNEL);
		अगर (!b->virt)
			जाओ no_mem;
		अगर (b->dma < base) अणु
			mfc_err("Invalid memory configuration - buffer (%pad) is below base memory address(%pad)\n",
				&b->dma, &base);
			dma_मुक्त_coherent(mem_dev, b->size, b->virt, b->dma);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	mfc_debug(3, "Allocated addr %p %pad\n", b->virt, &b->dma);
	वापस 0;
no_mem:
	mfc_err("Allocating private buffer of size %zu failed\n", b->size);
	वापस -ENOMEM;
पूर्ण

पूर्णांक s5p_mfc_alloc_generic_buf(काष्ठा s5p_mfc_dev *dev, अचिन्हित पूर्णांक mem_ctx,
			   काष्ठा s5p_mfc_priv_buf *b)
अणु
	काष्ठा device *mem_dev = dev->mem_dev[mem_ctx];

	mfc_debug(3, "Allocating generic buf: %zu\n", b->size);

	b->ctx = mem_ctx;
	b->virt = dma_alloc_coherent(mem_dev, b->size, &b->dma, GFP_KERNEL);
	अगर (!b->virt)
		जाओ no_mem;

	mfc_debug(3, "Allocated addr %p %pad\n", b->virt, &b->dma);
	वापस 0;
no_mem:
	mfc_err("Allocating generic buffer of size %zu failed\n", b->size);
	वापस -ENOMEM;
पूर्ण

व्योम s5p_mfc_release_priv_buf(काष्ठा s5p_mfc_dev *dev,
			      काष्ठा s5p_mfc_priv_buf *b)
अणु
	अगर (dev->mem_virt) अणु
		अचिन्हित पूर्णांक start = (b->dma - dev->mem_base) >> PAGE_SHIFT;
		अचिन्हित पूर्णांक count = b->size >> PAGE_SHIFT;

		biपंचांगap_clear(dev->mem_biपंचांगap, start, count);
	पूर्ण अन्यथा अणु
		काष्ठा device *mem_dev = dev->mem_dev[b->ctx];

		dma_मुक्त_coherent(mem_dev, b->size, b->virt, b->dma);
	पूर्ण
	b->virt = शून्य;
	b->dma = 0;
	b->size = 0;
पूर्ण

व्योम s5p_mfc_release_generic_buf(काष्ठा s5p_mfc_dev *dev,
			      काष्ठा s5p_mfc_priv_buf *b)
अणु
	काष्ठा device *mem_dev = dev->mem_dev[b->ctx];
	dma_मुक्त_coherent(mem_dev, b->size, b->virt, b->dma);
	b->virt = शून्य;
	b->dma = 0;
	b->size = 0;
पूर्ण
