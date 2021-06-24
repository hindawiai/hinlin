<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 VanguardiaSur - www.vanguardiasur.com.ar
 *
 * Based on original driver by Krzysztof Ha?asa:
 * Copyright (C) 2015 Industrial Research Institute क्रम Automation
 * and Measurements PIAP
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश "tw686x.h"
#समावेश "tw686x-regs.h"

#घोषणा TW686X_INPUTS_PER_CH		4
#घोषणा TW686X_VIDEO_WIDTH		720
#घोषणा TW686X_VIDEO_HEIGHT(id)		((id & V4L2_STD_525_60) ? 480 : 576)
#घोषणा TW686X_MAX_FPS(id)		((id & V4L2_STD_525_60) ? 30 : 25)

#घोषणा TW686X_MAX_SG_ENTRY_SIZE	4096
#घोषणा TW686X_MAX_SG_DESC_COUNT	256 /* PAL 720x576 needs 203 4-KB pages */
#घोषणा TW686X_SG_TABLE_SIZE		(TW686X_MAX_SG_DESC_COUNT * माप(काष्ठा tw686x_sg_desc))

अटल स्थिर काष्ठा tw686x_क्रमmat क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.mode = 0,
		.depth = 16,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_RGB565,
		.mode = 5,
		.depth = 16,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.mode = 6,
		.depth = 16,
	पूर्ण
पूर्ण;

अटल व्योम tw686x_buf_करोne(काष्ठा tw686x_video_channel *vc,
			    अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dma_desc *desc = &vc->dma_descs[pb];
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा vb2_v4l2_buffer *vb;
	काष्ठा vb2_buffer *vb2_buf;

	अगर (vc->curr_bufs[pb]) अणु
		vb = &vc->curr_bufs[pb]->vb;

		vb->field = dev->dma_ops->field;
		vb->sequence = vc->sequence++;
		vb2_buf = &vb->vb2_buf;

		अगर (dev->dma_mode == TW686X_DMA_MODE_MEMCPY)
			स_नकल(vb2_plane_vaddr(vb2_buf, 0), desc->virt,
			       desc->size);
		vb2_buf->बारtamp = kसमय_get_ns();
		vb2_buffer_करोne(vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	vc->pb = !pb;
पूर्ण

/*
 * We can call this even when alloc_dma failed क्रम the given channel
 */
अटल व्योम tw686x_स_नकल_dma_मुक्त(काष्ठा tw686x_video_channel *vc,
				   अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dma_desc *desc = &vc->dma_descs[pb];
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ flags;

	/* Check device presence. Shouldn't really happen! */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (!pci_dev) अणु
		WARN(1, "trying to deallocate on missing device\n");
		वापस;
	पूर्ण

	अगर (desc->virt) अणु
		dma_मुक्त_coherent(&dev->pci_dev->dev, desc->size, desc->virt,
				  desc->phys);
		desc->virt = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tw686x_स_नकल_dma_alloc(काष्ठा tw686x_video_channel *vc,
				   अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dev *dev = vc->dev;
	u32 reg = pb ? VDMA_B_ADDR[vc->ch] : VDMA_P_ADDR[vc->ch];
	अचिन्हित पूर्णांक len;
	व्योम *virt;

	WARN(vc->dma_descs[pb].virt,
	     "Allocating buffer but previous still here\n");

	len = (vc->width * vc->height * vc->क्रमmat->depth) >> 3;
	virt = dma_alloc_coherent(&dev->pci_dev->dev, len,
				  &vc->dma_descs[pb].phys, GFP_KERNEL);
	अगर (!virt) अणु
		v4l2_err(&dev->v4l2_dev,
			 "dma%d: unable to allocate %s-buffer\n",
			 vc->ch, pb ? "B" : "P");
		वापस -ENOMEM;
	पूर्ण
	vc->dma_descs[pb].size = len;
	vc->dma_descs[pb].virt = virt;
	reg_ग_लिखो(dev, reg, vc->dma_descs[pb].phys);

	वापस 0;
पूर्ण

अटल व्योम tw686x_स_नकल_buf_refill(काष्ठा tw686x_video_channel *vc,
				     अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_v4l2_buf *buf;

	जबतक (!list_empty(&vc->vidq_queued)) अणु

		buf = list_first_entry(&vc->vidq_queued,
			काष्ठा tw686x_v4l2_buf, list);
		list_del(&buf->list);

		vc->curr_bufs[pb] = buf;
		वापस;
	पूर्ण
	vc->curr_bufs[pb] = शून्य;
पूर्ण

अटल स्थिर काष्ठा tw686x_dma_ops स_नकल_dma_ops = अणु
	.alloc		= tw686x_स_नकल_dma_alloc,
	.मुक्त		= tw686x_स_नकल_dma_मुक्त,
	.buf_refill	= tw686x_स_नकल_buf_refill,
	.mem_ops	= &vb2_vदो_स्मृति_memops,
	.hw_dma_mode	= TW686X_FRAME_MODE,
	.field		= V4L2_FIELD_INTERLACED,
पूर्ण;

अटल व्योम tw686x_contig_buf_refill(काष्ठा tw686x_video_channel *vc,
				     अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_v4l2_buf *buf;

	जबतक (!list_empty(&vc->vidq_queued)) अणु
		u32 reg = pb ? VDMA_B_ADDR[vc->ch] : VDMA_P_ADDR[vc->ch];
		dma_addr_t phys;

		buf = list_first_entry(&vc->vidq_queued,
			काष्ठा tw686x_v4l2_buf, list);
		list_del(&buf->list);

		phys = vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);
		reg_ग_लिखो(vc->dev, reg, phys);

		buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		vc->curr_bufs[pb] = buf;
		वापस;
	पूर्ण
	vc->curr_bufs[pb] = शून्य;
पूर्ण

अटल स्थिर काष्ठा tw686x_dma_ops contig_dma_ops = अणु
	.buf_refill	= tw686x_contig_buf_refill,
	.mem_ops	= &vb2_dma_contig_memops,
	.hw_dma_mode	= TW686X_FRAME_MODE,
	.field		= V4L2_FIELD_INTERLACED,
पूर्ण;

अटल पूर्णांक tw686x_sg_desc_fill(काष्ठा tw686x_sg_desc *descs,
			       काष्ठा tw686x_v4l2_buf *buf,
			       अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा sg_table *vbuf = vb2_dma_sg_plane_desc(&buf->vb.vb2_buf, 0);
	अचिन्हित पूर्णांक len, entry_len;
	काष्ठा scatterlist *sg;
	पूर्णांक i, count;

	/* Clear the scatter-gather table */
	स_रखो(descs, 0, TW686X_SG_TABLE_SIZE);

	count = 0;
	क्रम_each_sg(vbuf->sgl, sg, vbuf->nents, i) अणु
		dma_addr_t phys = sg_dma_address(sg);
		len = sg_dma_len(sg);

		जबतक (len && buf_len) अणु

			अगर (count == TW686X_MAX_SG_DESC_COUNT)
				वापस -ENOMEM;

			entry_len = min_t(अचिन्हित पूर्णांक, len,
					  TW686X_MAX_SG_ENTRY_SIZE);
			entry_len = min_t(अचिन्हित पूर्णांक, entry_len, buf_len);
			descs[count].phys = cpu_to_le32(phys);
			descs[count++].flags_length =
					cpu_to_le32(BIT(30) | entry_len);
			phys += entry_len;
			len -= entry_len;
			buf_len -= entry_len;
		पूर्ण

		अगर (!buf_len)
			वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम tw686x_sg_buf_refill(काष्ठा tw686x_video_channel *vc,
				 अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा tw686x_v4l2_buf *buf;

	जबतक (!list_empty(&vc->vidq_queued)) अणु
		अचिन्हित पूर्णांक buf_len;

		buf = list_first_entry(&vc->vidq_queued,
			काष्ठा tw686x_v4l2_buf, list);
		list_del(&buf->list);

		buf_len = (vc->width * vc->height * vc->क्रमmat->depth) >> 3;
		अगर (tw686x_sg_desc_fill(vc->sg_descs[pb], buf, buf_len)) अणु
			v4l2_err(&dev->v4l2_dev,
				 "dma%d: unable to fill %s-buffer\n",
				 vc->ch, pb ? "B" : "P");
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			जारी;
		पूर्ण

		buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		vc->curr_bufs[pb] = buf;
		वापस;
	पूर्ण

	vc->curr_bufs[pb] = शून्य;
पूर्ण

अटल व्योम tw686x_sg_dma_मुक्त(काष्ठा tw686x_video_channel *vc,
			       अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dma_desc *desc = &vc->dma_descs[pb];
	काष्ठा tw686x_dev *dev = vc->dev;

	अगर (desc->size) अणु
		dma_मुक्त_coherent(&dev->pci_dev->dev, desc->size, desc->virt,
				  desc->phys);
		desc->virt = शून्य;
	पूर्ण

	vc->sg_descs[pb] = शून्य;
पूर्ण

अटल पूर्णांक tw686x_sg_dma_alloc(काष्ठा tw686x_video_channel *vc,
			       अचिन्हित पूर्णांक pb)
अणु
	काष्ठा tw686x_dma_desc *desc = &vc->dma_descs[pb];
	काष्ठा tw686x_dev *dev = vc->dev;
	u32 reg = pb ? DMA_PAGE_TABLE1_ADDR[vc->ch] :
		       DMA_PAGE_TABLE0_ADDR[vc->ch];
	व्योम *virt;

	अगर (desc->size) अणु
		virt = dma_alloc_coherent(&dev->pci_dev->dev, desc->size,
					  &desc->phys, GFP_KERNEL);
		अगर (!virt) अणु
			v4l2_err(&dev->v4l2_dev,
				 "dma%d: unable to allocate %s-buffer\n",
				 vc->ch, pb ? "B" : "P");
			वापस -ENOMEM;
		पूर्ण
		desc->virt = virt;
		reg_ग_लिखो(dev, reg, desc->phys);
	पूर्ण अन्यथा अणु
		virt = dev->video_channels[0].dma_descs[pb].virt +
		       vc->ch * TW686X_SG_TABLE_SIZE;
	पूर्ण

	vc->sg_descs[pb] = virt;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_sg_setup(काष्ठा tw686x_dev *dev)
अणु
	अचिन्हित पूर्णांक sg_table_size, pb, ch, channels;

	अगर (is_second_gen(dev)) अणु
		/*
		 * TW6865/TW6869: each channel needs a pair of
		 * P-B descriptor tables.
		 */
		channels = max_channels(dev);
		sg_table_size = TW686X_SG_TABLE_SIZE;
	पूर्ण अन्यथा अणु
		/*
		 * TW6864/TW6868: we need to allocate a pair of
		 * P-B descriptor tables, common क्रम all channels.
		 * Each table will be bigger than 4 KB.
		 */
		channels = 1;
		sg_table_size = max_channels(dev) * TW686X_SG_TABLE_SIZE;
	पूर्ण

	क्रम (ch = 0; ch < channels; ch++) अणु
		काष्ठा tw686x_video_channel *vc = &dev->video_channels[ch];

		क्रम (pb = 0; pb < 2; pb++)
			vc->dma_descs[pb].size = sg_table_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tw686x_dma_ops sg_dma_ops = अणु
	.setup		= tw686x_sg_setup,
	.alloc		= tw686x_sg_dma_alloc,
	.मुक्त		= tw686x_sg_dma_मुक्त,
	.buf_refill	= tw686x_sg_buf_refill,
	.mem_ops	= &vb2_dma_sg_memops,
	.hw_dma_mode	= TW686X_SG_MODE,
	.field		= V4L2_FIELD_SEQ_TB,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक fps_map[15] = अणु
	/*
	 * bit 31 enables selecting the field control रेजिस्टर
	 * bits 0-29 are a biपंचांगask with fields that will be output.
	 * For NTSC (and PAL-M, PAL-60), all 30 bits are used.
	 * For other PAL standards, only the first 25 bits are used.
	 */
	0x00000000, /* output all fields */
	0x80000006, /* 2 fps (60Hz), 2 fps (50Hz) */
	0x80018006, /* 4 fps (60Hz), 4 fps (50Hz) */
	0x80618006, /* 6 fps (60Hz), 6 fps (50Hz) */
	0x81818186, /* 8 fps (60Hz), 8 fps (50Hz) */
	0x86186186, /* 10 fps (60Hz), 8 fps (50Hz) */
	0x86619866, /* 12 fps (60Hz), 10 fps (50Hz) */
	0x86666666, /* 14 fps (60Hz), 12 fps (50Hz) */
	0x9999999e, /* 16 fps (60Hz), 14 fps (50Hz) */
	0x99e6799e, /* 18 fps (60Hz), 16 fps (50Hz) */
	0x9e79e79e, /* 20 fps (60Hz), 16 fps (50Hz) */
	0x9e7e7e7e, /* 22 fps (60Hz), 18 fps (50Hz) */
	0x9fe7f9fe, /* 24 fps (60Hz), 20 fps (50Hz) */
	0x9ffe7ffe, /* 26 fps (60Hz), 22 fps (50Hz) */
	0x9ffffffe, /* 28 fps (60Hz), 24 fps (50Hz) */
पूर्ण;

अटल अचिन्हित पूर्णांक tw686x_real_fps(अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक max_fps)
अणु
	अचिन्हित दीर्घ mask;

	अगर (!index || index >= ARRAY_SIZE(fps_map))
		वापस max_fps;

	mask = GENMASK(max_fps - 1, 0);
	वापस hweight_दीर्घ(fps_map[index] & mask);
पूर्ण

अटल अचिन्हित पूर्णांक tw686x_fps_idx(अचिन्हित पूर्णांक fps, अचिन्हित पूर्णांक max_fps)
अणु
	अचिन्हित पूर्णांक idx, real_fps;
	पूर्णांक delta;

	/* First guess */
	idx = (12 + 15 * fps) / max_fps;

	/* Minimal possible framerate is 2 frames per second */
	अगर (!idx)
		वापस 1;

	/* Check अगर the dअगरference is bigger than असल(1) and adjust */
	real_fps = tw686x_real_fps(idx, max_fps);
	delta = real_fps - fps;
	अगर (delta < -1)
		idx++;
	अन्यथा अगर (delta > 1)
		idx--;

	/* Max framerate */
	अगर (idx >= 15)
		वापस 0;

	वापस idx;
पूर्ण

अटल व्योम tw686x_set_framerate(काष्ठा tw686x_video_channel *vc,
				 अचिन्हित पूर्णांक fps)
अणु
	अचिन्हित पूर्णांक i;

	i = tw686x_fps_idx(fps, TW686X_MAX_FPS(vc->video_standard));
	reg_ग_लिखो(vc->dev, VIDEO_FIELD_CTRL[vc->ch], fps_map[i]);
	vc->fps = tw686x_real_fps(i, TW686X_MAX_FPS(vc->video_standard));
पूर्ण

अटल स्थिर काष्ठा tw686x_क्रमmat *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक cnt;

	क्रम (cnt = 0; cnt < ARRAY_SIZE(क्रमmats); cnt++)
		अगर (क्रमmats[cnt].fourcc == fourcc)
			वापस &क्रमmats[cnt];
	वापस शून्य;
पूर्ण

अटल पूर्णांक tw686x_queue_setup(काष्ठा vb2_queue *vq,
			      अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			      अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक szimage =
		(vc->width * vc->height * vc->क्रमmat->depth) >> 3;

	/*
	 * Let's request at least three buffers: two क्रम the
	 * DMA engine and one क्रम userspace.
	 */
	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	अगर (*nplanes) अणु
		अगर (*nplanes != 1 || sizes[0] < szimage)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	sizes[0] = szimage;
	*nplanes = 1;
	वापस 0;
पूर्ण

अटल व्योम tw686x_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा tw686x_video_channel *vc = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ flags;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा tw686x_v4l2_buf *buf =
		container_of(vbuf, काष्ठा tw686x_v4l2_buf, vb);

	/* Check device presence */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (!pci_dev) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&vc->qlock, flags);
	list_add_tail(&buf->list, &vc->vidq_queued);
	spin_unlock_irqrestore(&vc->qlock, flags);
पूर्ण

अटल व्योम tw686x_clear_queue(काष्ठा tw686x_video_channel *vc,
			       क्रमागत vb2_buffer_state state)
अणु
	अचिन्हित पूर्णांक pb;

	जबतक (!list_empty(&vc->vidq_queued)) अणु
		काष्ठा tw686x_v4l2_buf *buf;

		buf = list_first_entry(&vc->vidq_queued,
			काष्ठा tw686x_v4l2_buf, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण

	क्रम (pb = 0; pb < 2; pb++) अणु
		अगर (vc->curr_bufs[pb])
			vb2_buffer_करोne(&vc->curr_bufs[pb]->vb.vb2_buf, state);
		vc->curr_bufs[pb] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tw686x_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक pb, err;

	/* Check device presence */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (!pci_dev) अणु
		err = -ENODEV;
		जाओ err_clear_queue;
	पूर्ण

	spin_lock_irqsave(&vc->qlock, flags);

	/* Sanity check */
	अगर (dev->dma_mode == TW686X_DMA_MODE_MEMCPY &&
	    (!vc->dma_descs[0].virt || !vc->dma_descs[1].virt)) अणु
		spin_unlock_irqrestore(&vc->qlock, flags);
		v4l2_err(&dev->v4l2_dev,
			 "video%d: refusing to start without DMA buffers\n",
			 vc->num);
		err = -ENOMEM;
		जाओ err_clear_queue;
	पूर्ण

	क्रम (pb = 0; pb < 2; pb++)
		dev->dma_ops->buf_refill(vc, pb);
	spin_unlock_irqrestore(&vc->qlock, flags);

	vc->sequence = 0;
	vc->pb = 0;

	spin_lock_irqsave(&dev->lock, flags);
	tw686x_enable_channel(dev, vc->ch);
	spin_unlock_irqrestore(&dev->lock, flags);

	mod_समयr(&dev->dma_delay_समयr, jअगरfies + msecs_to_jअगरfies(100));

	वापस 0;

err_clear_queue:
	spin_lock_irqsave(&vc->qlock, flags);
	tw686x_clear_queue(vc, VB2_BUF_STATE_QUEUED);
	spin_unlock_irqrestore(&vc->qlock, flags);
	वापस err;
पूर्ण

अटल व्योम tw686x_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा tw686x_video_channel *vc = vb2_get_drv_priv(vq);
	काष्ठा tw686x_dev *dev = vc->dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित दीर्घ flags;

	/* Check device presence */
	spin_lock_irqsave(&dev->lock, flags);
	pci_dev = dev->pci_dev;
	spin_unlock_irqrestore(&dev->lock, flags);
	अगर (pci_dev)
		tw686x_disable_channel(dev, vc->ch);

	spin_lock_irqsave(&vc->qlock, flags);
	tw686x_clear_queue(vc, VB2_BUF_STATE_ERROR);
	spin_unlock_irqrestore(&vc->qlock, flags);
पूर्ण

अटल पूर्णांक tw686x_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा tw686x_video_channel *vc = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित पूर्णांक size =
		(vc->width * vc->height * vc->क्रमmat->depth) >> 3;

	अगर (vb2_plane_size(vb, 0) < size)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, size);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vb2_ops tw686x_video_qops = अणु
	.queue_setup		= tw686x_queue_setup,
	.buf_queue		= tw686x_buf_queue,
	.buf_prepare		= tw686x_buf_prepare,
	.start_streaming	= tw686x_start_streaming,
	.stop_streaming		= tw686x_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक tw686x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा tw686x_video_channel *vc;
	काष्ठा tw686x_dev *dev;
	अचिन्हित पूर्णांक ch;

	vc = container_of(ctrl->handler, काष्ठा tw686x_video_channel,
			  ctrl_handler);
	dev = vc->dev;
	ch = vc->ch;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		reg_ग_लिखो(dev, BRIGHT[ch], ctrl->val & 0xff);
		वापस 0;

	हाल V4L2_CID_CONTRAST:
		reg_ग_लिखो(dev, CONTRAST[ch], ctrl->val);
		वापस 0;

	हाल V4L2_CID_SATURATION:
		reg_ग_लिखो(dev, SAT_U[ch], ctrl->val);
		reg_ग_लिखो(dev, SAT_V[ch], ctrl->val);
		वापस 0;

	हाल V4L2_CID_HUE:
		reg_ग_लिखो(dev, HUE[ch], ctrl->val & 0xff);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ctrl_ops = अणु
	.s_ctrl = tw686x_s_ctrl,
पूर्ण;

अटल पूर्णांक tw686x_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा tw686x_dev *dev = vc->dev;

	f->fmt.pix.width = vc->width;
	f->fmt.pix.height = vc->height;
	f->fmt.pix.field = dev->dma_ops->field;
	f->fmt.pix.pixelक्रमmat = vc->क्रमmat->fourcc;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * vc->क्रमmat->depth) / 8;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा tw686x_dev *dev = vc->dev;
	अचिन्हित पूर्णांक video_height = TW686X_VIDEO_HEIGHT(vc->video_standard);
	स्थिर काष्ठा tw686x_क्रमmat *क्रमmat;

	क्रमmat = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!क्रमmat) अणु
		क्रमmat = &क्रमmats[0];
		f->fmt.pix.pixelक्रमmat = क्रमmat->fourcc;
	पूर्ण

	अगर (f->fmt.pix.width <= TW686X_VIDEO_WIDTH / 2)
		f->fmt.pix.width = TW686X_VIDEO_WIDTH / 2;
	अन्यथा
		f->fmt.pix.width = TW686X_VIDEO_WIDTH;

	अगर (f->fmt.pix.height <= video_height / 2)
		f->fmt.pix.height = video_height / 2;
	अन्यथा
		f->fmt.pix.height = video_height;

	f->fmt.pix.bytesperline = (f->fmt.pix.width * क्रमmat->depth) / 8;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.field = dev->dma_ops->field;

	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_set_क्रमmat(काष्ठा tw686x_video_channel *vc,
			     अचिन्हित पूर्णांक pixelक्रमmat, अचिन्हित पूर्णांक width,
			     अचिन्हित पूर्णांक height, bool पुनः_स्मृति)
अणु
	काष्ठा tw686x_dev *dev = vc->dev;
	u32 val, dma_width, dma_height, dma_line_width;
	पूर्णांक err, pb;

	vc->क्रमmat = क्रमmat_by_fourcc(pixelक्रमmat);
	vc->width = width;
	vc->height = height;

	/* We need new DMA buffers अगर the framesize has changed */
	अगर (dev->dma_ops->alloc && पुनः_स्मृति) अणु
		क्रम (pb = 0; pb < 2; pb++)
			dev->dma_ops->मुक्त(vc, pb);

		क्रम (pb = 0; pb < 2; pb++) अणु
			err = dev->dma_ops->alloc(vc, pb);
			अगर (err) अणु
				अगर (pb > 0)
					dev->dma_ops->मुक्त(vc, 0);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	val = reg_पढ़ो(vc->dev, VDMA_CHANNEL_CONFIG[vc->ch]);

	अगर (vc->width <= TW686X_VIDEO_WIDTH / 2)
		val |= BIT(23);
	अन्यथा
		val &= ~BIT(23);

	अगर (vc->height <= TW686X_VIDEO_HEIGHT(vc->video_standard) / 2)
		val |= BIT(24);
	अन्यथा
		val &= ~BIT(24);

	val &= ~0x7ffff;

	/* Program the DMA scatter-gather */
	अगर (dev->dma_mode == TW686X_DMA_MODE_SG) अणु
		u32 start_idx, end_idx;

		start_idx = is_second_gen(dev) ?
				0 : vc->ch * TW686X_MAX_SG_DESC_COUNT;
		end_idx = start_idx + TW686X_MAX_SG_DESC_COUNT - 1;

		val |= (end_idx << 10) | start_idx;
	पूर्ण

	val &= ~(0x7 << 20);
	val |= vc->क्रमmat->mode << 20;
	reg_ग_लिखो(vc->dev, VDMA_CHANNEL_CONFIG[vc->ch], val);

	/* Program the DMA frame size */
	dma_width = (vc->width * 2) & 0x7ff;
	dma_height = vc->height / 2;
	dma_line_width = (vc->width * 2) & 0x7ff;
	val = (dma_height << 22) | (dma_line_width << 11)  | dma_width;
	reg_ग_लिखो(vc->dev, VDMA_WHP[vc->ch], val);
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	अचिन्हित दीर्घ area;
	bool पुनः_स्मृति;
	पूर्णांक err;

	अगर (vb2_is_busy(&vc->vidq))
		वापस -EBUSY;

	area = vc->width * vc->height;
	err = tw686x_try_fmt_vid_cap(file, priv, f);
	अगर (err)
		वापस err;

	पुनः_स्मृति = area != (f->fmt.pix.width * f->fmt.pix.height);
	वापस tw686x_set_क्रमmat(vc, f->fmt.pix.pixelक्रमmat,
				 f->fmt.pix.width, f->fmt.pix.height,
				 पुनः_स्मृति);
पूर्ण

अटल पूर्णांक tw686x_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा tw686x_dev *dev = vc->dev;

	strscpy(cap->driver, "tw686x", माप(cap->driver));
	strscpy(cap->card, dev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "PCI:%s", pci_name(dev->pci_dev));
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_set_standard(काष्ठा tw686x_video_channel *vc, v4l2_std_id id)
अणु
	u32 val;

	अगर (id & V4L2_STD_NTSC)
		val = 0;
	अन्यथा अगर (id & V4L2_STD_PAL)
		val = 1;
	अन्यथा अगर (id & V4L2_STD_SECAM)
		val = 2;
	अन्यथा अगर (id & V4L2_STD_NTSC_443)
		val = 3;
	अन्यथा अगर (id & V4L2_STD_PAL_M)
		val = 4;
	अन्यथा अगर (id & V4L2_STD_PAL_Nc)
		val = 5;
	अन्यथा अगर (id & V4L2_STD_PAL_60)
		val = 6;
	अन्यथा
		वापस -EINVAL;

	vc->video_standard = id;
	reg_ग_लिखो(vc->dev, SDT[vc->ch], val);

	val = reg_पढ़ो(vc->dev, VIDEO_CONTROL1);
	अगर (id & V4L2_STD_525_60)
		val &= ~(1 << (SYS_MODE_DMA_SHIFT + vc->ch));
	अन्यथा
		val |= (1 << (SYS_MODE_DMA_SHIFT + vc->ch));
	reg_ग_लिखो(vc->dev, VIDEO_CONTROL1, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा v4l2_क्रमmat f;
	पूर्णांक ret;

	अगर (vc->video_standard == id)
		वापस 0;

	अगर (vb2_is_busy(&vc->vidq))
		वापस -EBUSY;

	ret = tw686x_set_standard(vc, id);
	अगर (ret)
		वापस ret;
	/*
	 * Adjust क्रमmat after V4L2_STD_525_60/V4L2_STD_625_50 change,
	 * calling g_fmt and s_fmt will sanitize the height
	 * according to the standard.
	 */
	tw686x_g_fmt_vid_cap(file, priv, &f);
	tw686x_s_fmt_vid_cap(file, priv, &f);

	/*
	 * Frame decimation depends on the chosen standard,
	 * so reset it to the current value.
	 */
	tw686x_set_framerate(vc, vc->fps);
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा tw686x_dev *dev = vc->dev;
	अचिन्हित पूर्णांक old_std, detected_std = 0;
	अचिन्हित दीर्घ end;

	अगर (vb2_is_streaming(&vc->vidq))
		वापस -EBUSY;

	/* Enable and start standard detection */
	old_std = reg_पढ़ो(dev, SDT[vc->ch]);
	reg_ग_लिखो(dev, SDT[vc->ch], 0x7);
	reg_ग_लिखो(dev, SDT_EN[vc->ch], 0xff);

	end = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (समय_is_after_jअगरfies(end)) अणु

		detected_std = reg_पढ़ो(dev, SDT[vc->ch]);
		अगर (!(detected_std & BIT(7)))
			अवरोध;
		msleep(100);
	पूर्ण
	reg_ग_लिखो(dev, SDT[vc->ch], old_std);

	/* Exit अगर still busy */
	अगर (detected_std & BIT(7))
		वापस 0;

	detected_std = (detected_std >> 4) & 0x7;
	चयन (detected_std) अणु
	हाल TW686X_STD_NTSC_M:
		*std &= V4L2_STD_NTSC;
		अवरोध;
	हाल TW686X_STD_NTSC_443:
		*std &= V4L2_STD_NTSC_443;
		अवरोध;
	हाल TW686X_STD_PAL_M:
		*std &= V4L2_STD_PAL_M;
		अवरोध;
	हाल TW686X_STD_PAL_60:
		*std &= V4L2_STD_PAL_60;
		अवरोध;
	हाल TW686X_STD_PAL:
		*std &= V4L2_STD_PAL;
		अवरोध;
	हाल TW686X_STD_PAL_CN:
		*std &= V4L2_STD_PAL_Nc;
		अवरोध;
	हाल TW686X_STD_SECAM:
		*std &= V4L2_STD_SECAM;
		अवरोध;
	शेष:
		*std = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);

	*id = vc->video_standard;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);

	अगर (fsize->index)
		वापस -EINVAL;
	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.max_width = TW686X_VIDEO_WIDTH;
	fsize->stepwise.min_width = fsize->stepwise.max_width / 2;
	fsize->stepwise.step_width = fsize->stepwise.min_width;
	fsize->stepwise.max_height = TW686X_VIDEO_HEIGHT(vc->video_standard);
	fsize->stepwise.min_height = fsize->stepwise.max_height / 2;
	fsize->stepwise.step_height = fsize->stepwise.min_height;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_frmivalक्रमागत *ival)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	पूर्णांक max_fps = TW686X_MAX_FPS(vc->video_standard);
	पूर्णांक max_rates = DIV_ROUND_UP(max_fps, 2);

	अगर (ival->index >= max_rates)
		वापस -EINVAL;

	ival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	ival->discrete.numerator = 1;
	अगर (ival->index < (max_rates - 1))
		ival->discrete.denominator = (ival->index + 1) * 2;
	अन्यथा
		ival->discrete.denominator = max_fps;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_g_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा v4l2_captureparm *cp = &sp->parm.capture;

	अगर (sp->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	sp->parm.capture.पढ़ोbuffers = 3;

	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->समयperframe.numerator = 1;
	cp->समयperframe.denominator = vc->fps;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_s_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	काष्ठा v4l2_captureparm *cp = &sp->parm.capture;
	अचिन्हित पूर्णांक denominator = cp->समयperframe.denominator;
	अचिन्हित पूर्णांक numerator = cp->समयperframe.numerator;
	अचिन्हित पूर्णांक fps;

	अगर (vb2_is_busy(&vc->vidq))
		वापस -EBUSY;

	fps = (!numerator || !denominator) ? 0 : denominator / numerator;
	अगर (vc->fps != fps)
		tw686x_set_framerate(vc, fps);
	वापस tw686x_g_parm(file, priv, sp);
पूर्ण

अटल पूर्णांक tw686x_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[f->index].fourcc;
	वापस 0;
पूर्ण

अटल व्योम tw686x_set_input(काष्ठा tw686x_video_channel *vc, अचिन्हित पूर्णांक i)
अणु
	u32 val;

	vc->input = i;

	val = reg_पढ़ो(vc->dev, VDMA_CHANNEL_CONFIG[vc->ch]);
	val &= ~(0x3 << 30);
	val |= i << 30;
	reg_ग_लिखो(vc->dev, VDMA_CHANNEL_CONFIG[vc->ch], val);
पूर्ण

अटल पूर्णांक tw686x_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);

	अगर (i >= TW686X_INPUTS_PER_CH)
		वापस -EINVAL;
	अगर (i == vc->input)
		वापस 0;
	/*
	 * Not sure we are able to support on the fly input change
	 */
	अगर (vb2_is_busy(&vc->vidq))
		वापस -EBUSY;

	tw686x_set_input(vc, i);
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);

	*i = vc->input;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i)
अणु
	काष्ठा tw686x_video_channel *vc = video_drvdata(file);
	अचिन्हित पूर्णांक vidstat;

	अगर (i->index >= TW686X_INPUTS_PER_CH)
		वापस -EINVAL;

	snम_लिखो(i->name, माप(i->name), "Composite%d", i->index);
	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = vc->device->tvnorms;
	i->capabilities = V4L2_IN_CAP_STD;

	vidstat = reg_पढ़ो(vc->dev, VIDSTAT[vc->ch]);
	i->status = 0;
	अगर (vidstat & TW686X_VIDSTAT_VDLOSS)
		i->status |= V4L2_IN_ST_NO_SIGNAL;
	अगर (!(vidstat & TW686X_VIDSTAT_HLOCK))
		i->status |= V4L2_IN_ST_NO_H_LOCK;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations tw686x_video_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.unlocked_ioctl	= video_ioctl2,
	.release	= vb2_fop_release,
	.poll		= vb2_fop_poll,
	.पढ़ो		= vb2_fop_पढ़ो,
	.mmap		= vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops tw686x_video_ioctl_ops = अणु
	.vidioc_querycap		= tw686x_querycap,
	.vidioc_g_fmt_vid_cap		= tw686x_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= tw686x_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap	= tw686x_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= tw686x_try_fmt_vid_cap,

	.vidioc_querystd		= tw686x_querystd,
	.vidioc_g_std			= tw686x_g_std,
	.vidioc_s_std			= tw686x_s_std,

	.vidioc_g_parm			= tw686x_g_parm,
	.vidioc_s_parm			= tw686x_s_parm,
	.vidioc_क्रमागत_framesizes		= tw686x_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals	= tw686x_क्रमागत_frameपूर्णांकervals,

	.vidioc_क्रमागत_input		= tw686x_क्रमागत_input,
	.vidioc_g_input			= tw686x_g_input,
	.vidioc_s_input			= tw686x_s_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,

	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

व्योम tw686x_video_irq(काष्ठा tw686x_dev *dev, अचिन्हित दीर्घ requests,
		      अचिन्हित पूर्णांक pb_status, अचिन्हित पूर्णांक fअगरo_status,
		      अचिन्हित पूर्णांक *reset_ch)
अणु
	काष्ठा tw686x_video_channel *vc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ch, pb;

	क्रम_each_set_bit(ch, &requests, max_channels(dev)) अणु
		vc = &dev->video_channels[ch];

		/*
		 * This can either be a blue frame (with संकेत-lost bit set)
		 * or a good frame (with संकेत-lost bit clear). If we have just
		 * got संकेत, then this channel needs resetting.
		 */
		अगर (vc->no_संकेत && !(fअगरo_status & BIT(ch))) अणु
			v4l2_prपूर्णांकk(KERN_DEBUG, &dev->v4l2_dev,
				    "video%d: signal recovered\n", vc->num);
			vc->no_संकेत = false;
			*reset_ch |= BIT(ch);
			vc->pb = 0;
			जारी;
		पूर्ण
		vc->no_संकेत = !!(fअगरo_status & BIT(ch));

		/* Check FIFO errors only अगर there's संकेत */
		अगर (!vc->no_संकेत) अणु
			u32 fअगरo_ov, fअगरo_bad;

			fअगरo_ov = (fअगरo_status >> 24) & BIT(ch);
			fअगरo_bad = (fअगरo_status >> 16) & BIT(ch);
			अगर (fअगरo_ov || fअगरo_bad) अणु
				/* Mark this channel क्रम reset */
				v4l2_prपूर्णांकk(KERN_DEBUG, &dev->v4l2_dev,
					    "video%d: FIFO error\n", vc->num);
				*reset_ch |= BIT(ch);
				vc->pb = 0;
				जारी;
			पूर्ण
		पूर्ण

		pb = !!(pb_status & BIT(ch));
		अगर (vc->pb != pb) अणु
			/* Mark this channel क्रम reset */
			v4l2_prपूर्णांकk(KERN_DEBUG, &dev->v4l2_dev,
				    "video%d: unexpected p-b buffer!\n",
				    vc->num);
			*reset_ch |= BIT(ch);
			vc->pb = 0;
			जारी;
		पूर्ण

		spin_lock_irqsave(&vc->qlock, flags);
		tw686x_buf_करोne(vc, pb);
		dev->dma_ops->buf_refill(vc, pb);
		spin_unlock_irqrestore(&vc->qlock, flags);
	पूर्ण
पूर्ण

व्योम tw686x_video_मुक्त(काष्ठा tw686x_dev *dev)
अणु
	अचिन्हित पूर्णांक ch, pb;

	क्रम (ch = 0; ch < max_channels(dev); ch++) अणु
		काष्ठा tw686x_video_channel *vc = &dev->video_channels[ch];

		video_unरेजिस्टर_device(vc->device);

		अगर (dev->dma_ops->मुक्त)
			क्रम (pb = 0; pb < 2; pb++)
				dev->dma_ops->मुक्त(vc, pb);
	पूर्ण
पूर्ण

पूर्णांक tw686x_video_init(काष्ठा tw686x_dev *dev)
अणु
	अचिन्हित पूर्णांक ch, val;
	पूर्णांक err;

	अगर (dev->dma_mode == TW686X_DMA_MODE_MEMCPY)
		dev->dma_ops = &स_नकल_dma_ops;
	अन्यथा अगर (dev->dma_mode == TW686X_DMA_MODE_CONTIG)
		dev->dma_ops = &contig_dma_ops;
	अन्यथा अगर (dev->dma_mode == TW686X_DMA_MODE_SG)
		dev->dma_ops = &sg_dma_ops;
	अन्यथा
		वापस -EINVAL;

	err = v4l2_device_रेजिस्टर(&dev->pci_dev->dev, &dev->v4l2_dev);
	अगर (err)
		वापस err;

	अगर (dev->dma_ops->setup) अणु
		err = dev->dma_ops->setup(dev);
		अगर (err)
			वापस err;
	पूर्ण

	/* Initialize vc->dev and vc->ch क्रम the error path */
	क्रम (ch = 0; ch < max_channels(dev); ch++) अणु
		काष्ठा tw686x_video_channel *vc = &dev->video_channels[ch];

		vc->dev = dev;
		vc->ch = ch;
	पूर्ण

	क्रम (ch = 0; ch < max_channels(dev); ch++) अणु
		काष्ठा tw686x_video_channel *vc = &dev->video_channels[ch];
		काष्ठा video_device *vdev;

		mutex_init(&vc->vb_mutex);
		spin_lock_init(&vc->qlock);
		INIT_LIST_HEAD(&vc->vidq_queued);

		/* शेष settings */
		err = tw686x_set_standard(vc, V4L2_STD_NTSC);
		अगर (err)
			जाओ error;

		err = tw686x_set_क्रमmat(vc, क्रमmats[0].fourcc,
				TW686X_VIDEO_WIDTH,
				TW686X_VIDEO_HEIGHT(vc->video_standard),
				true);
		अगर (err)
			जाओ error;

		tw686x_set_input(vc, 0);
		tw686x_set_framerate(vc, 30);
		reg_ग_लिखो(dev, VDELAY_LO[ch], 0x14);
		reg_ग_लिखो(dev, HACTIVE_LO[ch], 0xd0);
		reg_ग_लिखो(dev, VIDEO_SIZE[ch], 0);

		vc->vidq.io_modes = VB2_READ | VB2_MMAP | VB2_DMABUF;
		vc->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		vc->vidq.drv_priv = vc;
		vc->vidq.buf_काष्ठा_size = माप(काष्ठा tw686x_v4l2_buf);
		vc->vidq.ops = &tw686x_video_qops;
		vc->vidq.mem_ops = dev->dma_ops->mem_ops;
		vc->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		vc->vidq.min_buffers_needed = 2;
		vc->vidq.lock = &vc->vb_mutex;
		vc->vidq.gfp_flags = dev->dma_mode != TW686X_DMA_MODE_MEMCPY ?
				     GFP_DMA32 : 0;
		vc->vidq.dev = &dev->pci_dev->dev;

		err = vb2_queue_init(&vc->vidq);
		अगर (err) अणु
			v4l2_err(&dev->v4l2_dev,
				 "dma%d: cannot init vb2 queue\n", ch);
			जाओ error;
		पूर्ण

		err = v4l2_ctrl_handler_init(&vc->ctrl_handler, 4);
		अगर (err) अणु
			v4l2_err(&dev->v4l2_dev,
				 "dma%d: cannot init ctrl handler\n", ch);
			जाओ error;
		पूर्ण
		v4l2_ctrl_new_std(&vc->ctrl_handler, &ctrl_ops,
				  V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
		v4l2_ctrl_new_std(&vc->ctrl_handler, &ctrl_ops,
				  V4L2_CID_CONTRAST, 0, 255, 1, 100);
		v4l2_ctrl_new_std(&vc->ctrl_handler, &ctrl_ops,
				  V4L2_CID_SATURATION, 0, 255, 1, 128);
		v4l2_ctrl_new_std(&vc->ctrl_handler, &ctrl_ops,
				  V4L2_CID_HUE, -128, 127, 1, 0);
		err = vc->ctrl_handler.error;
		अगर (err)
			जाओ error;

		err = v4l2_ctrl_handler_setup(&vc->ctrl_handler);
		अगर (err)
			जाओ error;

		vdev = video_device_alloc();
		अगर (!vdev) अणु
			v4l2_err(&dev->v4l2_dev,
				 "dma%d: unable to allocate device\n", ch);
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		snम_लिखो(vdev->name, माप(vdev->name), "%s video", dev->name);
		vdev->fops = &tw686x_video_fops;
		vdev->ioctl_ops = &tw686x_video_ioctl_ops;
		vdev->release = video_device_release;
		vdev->v4l2_dev = &dev->v4l2_dev;
		vdev->queue = &vc->vidq;
		vdev->tvnorms = V4L2_STD_525_60 | V4L2_STD_625_50;
		vdev->minor = -1;
		vdev->lock = &vc->vb_mutex;
		vdev->ctrl_handler = &vc->ctrl_handler;
		vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE |
				    V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		vc->device = vdev;
		video_set_drvdata(vdev, vc);

		err = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
		अगर (err < 0)
			जाओ error;
		vc->num = vdev->num;
	पूर्ण

	val = TW686X_DEF_PHASE_REF;
	क्रम (ch = 0; ch < max_channels(dev); ch++)
		val |= dev->dma_ops->hw_dma_mode << (16 + ch * 2);
	reg_ग_लिखो(dev, PHASE_REF, val);

	reg_ग_लिखो(dev, MISC2[0], 0xe7);
	reg_ग_लिखो(dev, VCTRL1[0], 0xcc);
	reg_ग_लिखो(dev, LOOP[0], 0xa5);
	अगर (max_channels(dev) > 4) अणु
		reg_ग_लिखो(dev, VCTRL1[1], 0xcc);
		reg_ग_लिखो(dev, LOOP[1], 0xa5);
		reg_ग_लिखो(dev, MISC2[1], 0xe7);
	पूर्ण
	वापस 0;

error:
	tw686x_video_मुक्त(dev);
	वापस err;
पूर्ण
