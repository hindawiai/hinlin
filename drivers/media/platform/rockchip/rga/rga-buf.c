<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co.Ltd
 * Author: Jacob Chen <jacob-chen@iotwrt.com>
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "rga-hw.h"
#समावेश "rga.h"

अटल पूर्णांक
rga_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा rga_frame *f = rga_get_frame(ctx, vq->type);

	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	अगर (*nplanes)
		वापस sizes[0] < f->size ? -EINVAL : 0;

	sizes[0] = f->size;
	*nplanes = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rga_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा rga_frame *f = rga_get_frame(ctx, vb->vb2_queue->type);

	अगर (IS_ERR(f))
		वापस PTR_ERR(f);

	vb2_set_plane_payload(vb, 0, f->size);

	वापस 0;
पूर्ण

अटल व्योम rga_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल व्योम rga_buf_वापस_buffers(काष्ठा vb2_queue *q,
				   क्रमागत vb2_buffer_state state)
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा vb2_v4l2_buffer *vbuf;

	क्रम (;;) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_हटाओ(ctx->fh.m2m_ctx);
		अन्यथा
			vbuf = v4l2_m2m_dst_buf_हटाओ(ctx->fh.m2m_ctx);
		अगर (!vbuf)
			अवरोध;
		v4l2_m2m_buf_करोne(vbuf, state);
	पूर्ण
पूर्ण

अटल पूर्णांक rga_buf_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा rockchip_rga *rga = ctx->rga;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(rga->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(rga->dev);
		rga_buf_वापस_buffers(q, VB2_BUF_STATE_QUEUED);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rga_buf_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(q);
	काष्ठा rockchip_rga *rga = ctx->rga;

	rga_buf_वापस_buffers(q, VB2_BUF_STATE_ERROR);
	pm_runसमय_put(rga->dev);
पूर्ण

स्थिर काष्ठा vb2_ops rga_qops = अणु
	.queue_setup = rga_queue_setup,
	.buf_prepare = rga_buf_prepare,
	.buf_queue = rga_buf_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = rga_buf_start_streaming,
	.stop_streaming = rga_buf_stop_streaming,
पूर्ण;

/* RGA MMU is a 1-Level MMU, so it can't be used through the IOMMU API.
 * We use it more like a scatter-gather list.
 */
व्योम rga_buf_map(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rga_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा rockchip_rga *rga = ctx->rga;
	काष्ठा sg_table *sgt;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक *pages;
	अचिन्हित पूर्णांक address, len, i, p;
	अचिन्हित पूर्णांक mapped_size = 0;

	अगर (vb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pages = rga->src_mmu_pages;
	अन्यथा
		pages = rga->dst_mmu_pages;

	/* Create local MMU table क्रम RGA */
	sgt = vb2_plane_cookie(vb, 0);

	क्रम_each_sg(sgt->sgl, sgl, sgt->nents, i) अणु
		len = sg_dma_len(sgl) >> PAGE_SHIFT;
		address = sg_phys(sgl);

		क्रम (p = 0; p < len; p++) अणु
			dma_addr_t phys = address +
					  ((dma_addr_t)p << PAGE_SHIFT);

			pages[mapped_size + p] = phys;
		पूर्ण

		mapped_size += len;
	पूर्ण

	/* sync local MMU table क्रम RGA */
	dma_sync_single_क्रम_device(rga->dev, virt_to_phys(pages),
				   8 * PAGE_SIZE, DMA_BIसूचीECTIONAL);
पूर्ण
