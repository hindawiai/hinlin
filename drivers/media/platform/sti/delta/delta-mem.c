<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#समावेश "delta.h"
#समावेश "delta-mem.h"

पूर्णांक hw_alloc(काष्ठा delta_ctx *ctx, u32 size, स्थिर अक्षर *name,
	     काष्ठा delta_buf *buf)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	dma_addr_t dma_addr;
	व्योम *addr;
	अचिन्हित दीर्घ attrs = DMA_ATTR_WRITE_COMBINE;

	addr = dma_alloc_attrs(delta->dev, size, &dma_addr,
			       GFP_KERNEL | __GFP_NOWARN, attrs);
	अगर (!addr) अणु
		dev_err(delta->dev,
			"%s hw_alloc:dma_alloc_coherent failed for %s (size=%d)\n",
			ctx->name, name, size);
		ctx->sys_errors++;
		वापस -ENOMEM;
	पूर्ण

	buf->size = size;
	buf->paddr = dma_addr;
	buf->vaddr = addr;
	buf->name = name;
	buf->attrs = attrs;

	dev_dbg(delta->dev,
		"%s allocate %d bytes of HW memory @(virt=0x%p, phy=0x%pad): %s\n",
		ctx->name, size, buf->vaddr, &buf->paddr, buf->name);

	वापस 0;
पूर्ण

व्योम hw_मुक्त(काष्ठा delta_ctx *ctx, काष्ठा delta_buf *buf)
अणु
	काष्ठा delta_dev *delta = ctx->dev;

	dev_dbg(delta->dev,
		"%s     free %d bytes of HW memory @(virt=0x%p, phy=0x%pad): %s\n",
		ctx->name, buf->size, buf->vaddr, &buf->paddr, buf->name);

	dma_मुक्त_attrs(delta->dev, buf->size,
		       buf->vaddr, buf->paddr, buf->attrs);
पूर्ण
