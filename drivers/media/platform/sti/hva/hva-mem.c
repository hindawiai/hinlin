<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#समावेश "hva.h"
#समावेश "hva-mem.h"

पूर्णांक hva_mem_alloc(काष्ठा hva_ctx *ctx, u32 size, स्थिर अक्षर *name,
		  काष्ठा hva_buffer **buf)
अणु
	काष्ठा device *dev = ctx_to_dev(ctx);
	काष्ठा hva_buffer *b;
	dma_addr_t paddr;
	व्योम *base;

	b = devm_kzalloc(dev, माप(*b), GFP_KERNEL);
	अगर (!b) अणु
		ctx->sys_errors++;
		वापस -ENOMEM;
	पूर्ण

	base = dma_alloc_attrs(dev, size, &paddr, GFP_KERNEL,
			       DMA_ATTR_WRITE_COMBINE);
	अगर (!base) अणु
		dev_err(dev, "%s %s : dma_alloc_attrs failed for %s (size=%d)\n",
			ctx->name, __func__, name, size);
		ctx->sys_errors++;
		devm_kमुक्त(dev, b);
		वापस -ENOMEM;
	पूर्ण

	b->size = size;
	b->paddr = paddr;
	b->vaddr = base;
	b->name = name;

	dev_dbg(dev,
		"%s allocate %d bytes of HW memory @(virt=%p, phy=%pad): %s\n",
		ctx->name, size, b->vaddr, &b->paddr, b->name);

	/* वापस  hva buffer to user */
	*buf = b;

	वापस 0;
पूर्ण

व्योम hva_mem_मुक्त(काष्ठा hva_ctx *ctx, काष्ठा hva_buffer *buf)
अणु
	काष्ठा device *dev = ctx_to_dev(ctx);

	dev_dbg(dev,
		"%s free %d bytes of HW memory @(virt=%p, phy=%pad): %s\n",
		ctx->name, buf->size, buf->vaddr, &buf->paddr, buf->name);

	dma_मुक्त_attrs(dev, buf->size, buf->vaddr, buf->paddr,
		       DMA_ATTR_WRITE_COMBINE);

	devm_kमुक्त(dev, buf);
पूर्ण
