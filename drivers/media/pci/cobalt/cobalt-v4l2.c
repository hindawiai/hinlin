<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cobalt V4L2 API
 *
 *  Derived from ivtv-ioctl.c and cx18-fileops.c
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/math64.h>
#समावेश <linux/pci.h>
#समावेश <linux/v4l2-dv-timings.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/i2c/adv7604.h>
#समावेश <media/i2c/adv7842.h>

#समावेश "cobalt-alsa.h"
#समावेश "cobalt-cpld.h"
#समावेश "cobalt-driver.h"
#समावेश "cobalt-v4l2.h"
#समावेश "cobalt-irq.h"
#समावेश "cobalt-omnitek.h"

अटल स्थिर काष्ठा v4l2_dv_timings cea1080p60 = V4L2_DV_BT_CEA_1920X1080P60;

/* vb2 DMA streaming ops */

अटल पूर्णांक cobalt_queue_setup(काष्ठा vb2_queue *q,
			अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cobalt_stream *s = q->drv_priv;
	अचिन्हित size = s->stride * s->height;

	अगर (*num_buffers < 3)
		*num_buffers = 3;
	अगर (*num_buffers > NR_BUFS)
		*num_buffers = NR_BUFS;
	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*num_planes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cobalt_stream *s = vb->vb2_queue->drv_priv;
	काष्ठा cobalt *cobalt = s->cobalt;
	स्थिर माप_प्रकार max_pages_per_line =
		(COBALT_MAX_WIDTH * COBALT_MAX_BPP) / PAGE_SIZE + 2;
	स्थिर माप_प्रकार bytes =
		COBALT_MAX_HEIGHT * max_pages_per_line * 0x20;
	स्थिर माप_प्रकार audio_bytes = ((1920 * 4) / PAGE_SIZE + 1) * 0x20;
	काष्ठा sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	काष्ठा sg_table *sg_desc = vb2_dma_sg_plane_desc(vb, 0);
	अचिन्हित size;
	पूर्णांक ret;

	size = s->stride * s->height;
	अगर (vb2_plane_size(vb, 0) < size) अणु
		cobalt_info("data will not fit into plane (%lu < %u)\n",
					vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	अगर (desc->virt == शून्य) अणु
		desc->dev = &cobalt->pci_dev->dev;
		descriptor_list_allocate(desc,
			s->is_audio ? audio_bytes : bytes);
		अगर (desc->virt == शून्य)
			वापस -ENOMEM;
	पूर्ण
	ret = descriptor_list_create(cobalt, sg_desc->sgl,
			!s->is_output, sg_desc->nents, size,
			s->width * s->bpp, s->stride, desc);
	अगर (ret)
		descriptor_list_मुक्त(desc);
	वापस ret;
पूर्ण

अटल व्योम cobalt_buf_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cobalt_stream *s = vb->vb2_queue->drv_priv;
	काष्ठा sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];

	descriptor_list_मुक्त(desc);
पूर्ण

अटल पूर्णांक cobalt_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cobalt_stream *s = vb->vb2_queue->drv_priv;

	vb2_set_plane_payload(vb, 0, s->stride * s->height);
	vbuf->field = V4L2_FIELD_NONE;
	वापस 0;
पूर्ण

अटल व्योम chain_all_buffers(काष्ठा cobalt_stream *s)
अणु
	काष्ठा sg_dma_desc_info *desc[NR_BUFS];
	काष्ठा cobalt_buffer *cb;
	काष्ठा list_head *p;
	पूर्णांक i = 0;

	list_क्रम_each(p, &s->bufs) अणु
		cb = list_entry(p, काष्ठा cobalt_buffer, list);
		desc[i] = &s->dma_desc_info[cb->vb.vb2_buf.index];
		अगर (i > 0)
			descriptor_list_chain(desc[i-1], desc[i]);
		i++;
	पूर्ण
पूर्ण

अटल व्योम cobalt_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा cobalt_stream *s = q->drv_priv;
	काष्ठा cobalt_buffer *cb = to_cobalt_buffer(vbuf);
	काष्ठा sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	अचिन्हित दीर्घ flags;

	/* Prepare new buffer */
	descriptor_list_loopback(desc);
	descriptor_list_पूर्णांकerrupt_disable(desc);

	spin_lock_irqsave(&s->irqlock, flags);
	list_add_tail(&cb->list, &s->bufs);
	chain_all_buffers(s);
	spin_unlock_irqrestore(&s->irqlock, flags);
पूर्ण

अटल व्योम cobalt_enable_output(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा v4l2_bt_timings *bt = &s->timings.bt;
	काष्ठा m00514_syncgen_flow_evcnt_regmap __iomem *vo =
		COBALT_TX_BASE(cobalt);
	अचिन्हित fmt = s->pixfmt != V4L2_PIX_FMT_BGR32 ?
			M00514_CONTROL_BITMAP_FORMAT_16_BPP_MSK : 0;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	u64 clk = bt->pixelघड़ी;

	अगर (bt->flags & V4L2_DV_FL_REDUCED_FPS)
		clk = भाग_u64(clk * 1000ULL, 1001);
	अगर (!cobalt_cpld_set_freq(cobalt, clk)) अणु
		cobalt_err("pixelclock out of range\n");
		वापस;
	पूर्ण

	sd_fmt.क्रमmat.colorspace = s->colorspace;
	sd_fmt.क्रमmat.xfer_func = s->xfer_func;
	sd_fmt.क्रमmat.ycbcr_enc = s->ycbcr_enc;
	sd_fmt.क्रमmat.quantization = s->quantization;
	sd_fmt.क्रमmat.width = bt->width;
	sd_fmt.क्रमmat.height = bt->height;

	/* Set up FDMA packer */
	चयन (s->pixfmt) अणु
	हाल V4L2_PIX_FMT_YUYV:
		sd_fmt.क्रमmat.code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		sd_fmt.क्रमmat.code = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	पूर्ण
	v4l2_subdev_call(s->sd, pad, set_fmt, शून्य, &sd_fmt);

	ioग_लिखो32(0, &vo->control);
	/* 1080p60 */
	ioग_लिखो32(bt->hsync, &vo->sync_generator_h_sync_length);
	ioग_लिखो32(bt->hbackporch, &vo->sync_generator_h_backporch_length);
	ioग_लिखो32(bt->width, &vo->sync_generator_h_active_length);
	ioग_लिखो32(bt->hfrontporch, &vo->sync_generator_h_frontporch_length);
	ioग_लिखो32(bt->vsync, &vo->sync_generator_v_sync_length);
	ioग_लिखो32(bt->vbackporch, &vo->sync_generator_v_backporch_length);
	ioग_लिखो32(bt->height, &vo->sync_generator_v_active_length);
	ioग_लिखो32(bt->vfrontporch, &vo->sync_generator_v_frontporch_length);
	ioग_लिखो32(0x9900c1, &vo->error_color);

	ioग_लिखो32(M00514_CONTROL_BITMAP_SYNC_GENERATOR_LOAD_PARAM_MSK | fmt,
		  &vo->control);
	ioग_लिखो32(M00514_CONTROL_BITMAP_EVCNT_CLEAR_MSK | fmt, &vo->control);
	ioग_लिखो32(M00514_CONTROL_BITMAP_SYNC_GENERATOR_ENABLE_MSK |
		  M00514_CONTROL_BITMAP_FLOW_CTRL_OUTPUT_ENABLE_MSK |
		  fmt, &vo->control);
पूर्ण

अटल व्योम cobalt_enable_input(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	पूर्णांक ch = (पूर्णांक)s->video_channel;
	काष्ठा m00235_fdma_packer_regmap __iomem *packer;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt_yuyv = अणु
		.pad = s->pad_source,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
	पूर्ण;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt_rgb = अणु
		.pad = s->pad_source,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat.code = MEDIA_BUS_FMT_RGB888_1X24,
	पूर्ण;

	cobalt_dbg(1, "video_channel %d (%s, %s)\n",
		   s->video_channel,
		   s->input == 0 ? "hdmi" : "generator",
		   "YUYV");

	packer = COBALT_CVI_PACKER(cobalt, ch);

	/* Set up FDMA packer */
	चयन (s->pixfmt) अणु
	हाल V4L2_PIX_FMT_YUYV:
		ioग_लिखो32(M00235_CONTROL_BITMAP_ENABLE_MSK |
			  (1 << M00235_CONTROL_BITMAP_PACK_FORMAT_OFST),
			  &packer->control);
		v4l2_subdev_call(s->sd, pad, set_fmt, शून्य,
				 &sd_fmt_yuyv);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		ioग_लिखो32(M00235_CONTROL_BITMAP_ENABLE_MSK |
			  (2 << M00235_CONTROL_BITMAP_PACK_FORMAT_OFST),
			  &packer->control);
		v4l2_subdev_call(s->sd, pad, set_fmt, शून्य,
				 &sd_fmt_rgb);
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		ioग_लिखो32(M00235_CONTROL_BITMAP_ENABLE_MSK |
			  M00235_CONTROL_BITMAP_ENDIAN_FORMAT_MSK |
			  (3 << M00235_CONTROL_BITMAP_PACK_FORMAT_OFST),
			  &packer->control);
		v4l2_subdev_call(s->sd, pad, set_fmt, शून्य,
				 &sd_fmt_rgb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cobalt_dma_start_streaming(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	पूर्णांक rx = s->video_channel;
	काष्ठा m00460_evcnt_regmap __iomem *evcnt =
		COBALT_CVI_EVCNT(cobalt, rx);
	काष्ठा cobalt_buffer *cb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->irqlock, flags);
	अगर (!s->is_output) अणु
		ioग_लिखो32(M00460_CONTROL_BITMAP_CLEAR_MSK, &evcnt->control);
		ioग_लिखो32(M00460_CONTROL_BITMAP_ENABLE_MSK, &evcnt->control);
	पूर्ण अन्यथा अणु
		काष्ठा m00514_syncgen_flow_evcnt_regmap __iomem *vo =
			COBALT_TX_BASE(cobalt);
		u32 ctrl = ioपढ़ो32(&vo->control);

		ctrl &= ~(M00514_CONTROL_BITMAP_EVCNT_ENABLE_MSK |
			  M00514_CONTROL_BITMAP_EVCNT_CLEAR_MSK);
		ioग_लिखो32(ctrl | M00514_CONTROL_BITMAP_EVCNT_CLEAR_MSK,
			  &vo->control);
		ioग_लिखो32(ctrl | M00514_CONTROL_BITMAP_EVCNT_ENABLE_MSK,
			  &vo->control);
	पूर्ण
	cb = list_first_entry(&s->bufs, काष्ठा cobalt_buffer, list);
	omni_sg_dma_start(s, &s->dma_desc_info[cb->vb.vb2_buf.index]);
	spin_unlock_irqrestore(&s->irqlock, flags);
पूर्ण

अटल पूर्णांक cobalt_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cobalt_stream *s = q->drv_priv;
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा m00233_video_measure_regmap __iomem *vmr;
	काष्ठा m00473_मुक्तwheel_regmap __iomem *fw;
	काष्ठा m00479_clk_loss_detector_regmap __iomem *clkloss;
	पूर्णांक rx = s->video_channel;
	काष्ठा m00389_cvi_regmap __iomem *cvi = COBALT_CVI(cobalt, rx);
	काष्ठा m00460_evcnt_regmap __iomem *evcnt = COBALT_CVI_EVCNT(cobalt, rx);
	काष्ठा v4l2_bt_timings *bt = &s->timings.bt;
	u64 tot_size;
	u32 clk_freq;

	अगर (s->is_audio)
		जाओ करोne;
	अगर (s->is_output) अणु
		s->unstable_frame = false;
		cobalt_enable_output(s);
		जाओ करोne;
	पूर्ण

	cobalt_enable_input(s);

	fw = COBALT_CVI_FREEWHEEL(cobalt, rx);
	vmr = COBALT_CVI_VMR(cobalt, rx);
	clkloss = COBALT_CVI_CLK_LOSS(cobalt, rx);

	ioग_लिखो32(M00460_CONTROL_BITMAP_CLEAR_MSK, &evcnt->control);
	ioग_लिखो32(M00460_CONTROL_BITMAP_ENABLE_MSK, &evcnt->control);
	ioग_लिखो32(bt->width, &cvi->frame_width);
	ioग_लिखो32(bt->height, &cvi->frame_height);
	tot_size = V4L2_DV_BT_FRAME_WIDTH(bt) * V4L2_DV_BT_FRAME_HEIGHT(bt);
	ioग_लिखो32(भाग_u64((u64)V4L2_DV_BT_FRAME_WIDTH(bt) * COBALT_CLK * 4,
			  bt->pixelघड़ी), &vmr->hsync_समयout_val);
	ioग_लिखो32(M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK, &vmr->control);
	clk_freq = ioपढ़ो32(&fw->clk_freq);
	ioग_लिखो32(clk_freq / 1000000, &clkloss->ref_clk_cnt_val);
	/* The lower bound क्रम the घड़ी frequency is 0.5% lower as is
	 * allowed by the spec */
	ioग_लिखो32(भाग_u64(bt->pixelघड़ी * 995, 1000000000),
		  &clkloss->test_clk_cnt_val);
	/* will be enabled after the first frame has been received */
	ioग_लिखो32(bt->width * bt->height, &fw->active_length);
	ioग_लिखो32(भाग_u64((u64)clk_freq * tot_size, bt->pixelघड़ी),
		  &fw->total_length);
	ioग_लिखो32(M00233_IRQ_TRIGGERS_BITMAP_VACTIVE_AREA_MSK |
		  M00233_IRQ_TRIGGERS_BITMAP_HACTIVE_AREA_MSK,
		  &vmr->irq_triggers);
	ioग_लिखो32(0, &cvi->control);
	ioग_लिखो32(M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK, &vmr->control);

	ioग_लिखो32(0xff, &fw->output_color);
	ioग_लिखो32(M00479_CTRL_BITMAP_ENABLE_MSK, &clkloss->ctrl);
	ioग_लिखो32(M00473_CTRL_BITMAP_ENABLE_MSK |
		  M00473_CTRL_BITMAP_FORCE_FREEWHEEL_MODE_MSK, &fw->ctrl);
	s->unstable_frame = true;
	s->enable_मुक्तwheel = false;
	s->enable_cvi = false;
	s->skip_first_frames = 0;

करोne:
	s->sequence = 0;
	cobalt_dma_start_streaming(s);
	वापस 0;
पूर्ण

अटल व्योम cobalt_dma_stop_streaming(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा sg_dma_desc_info *desc;
	काष्ठा cobalt_buffer *cb;
	काष्ठा list_head *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout_msec = 100;
	पूर्णांक rx = s->video_channel;
	काष्ठा m00460_evcnt_regmap __iomem *evcnt =
		COBALT_CVI_EVCNT(cobalt, rx);

	अगर (!s->is_output) अणु
		ioग_लिखो32(0, &evcnt->control);
	पूर्ण अन्यथा अगर (!s->is_audio) अणु
		काष्ठा m00514_syncgen_flow_evcnt_regmap __iomem *vo =
			COBALT_TX_BASE(cobalt);

		ioग_लिखो32(M00514_CONTROL_BITMAP_EVCNT_CLEAR_MSK, &vo->control);
		ioग_लिखो32(0, &vo->control);
	पूर्ण

	/* Try to stop the DMA engine gracefully */
	spin_lock_irqsave(&s->irqlock, flags);
	list_क्रम_each(p, &s->bufs) अणु
		cb = list_entry(p, काष्ठा cobalt_buffer, list);
		desc = &s->dma_desc_info[cb->vb.vb2_buf.index];
		/* Stop DMA after this descriptor chain */
		descriptor_list_end_of_chain(desc);
	पूर्ण
	spin_unlock_irqrestore(&s->irqlock, flags);

	/* Wait 100 millisecond क्रम DMA to finish, पात on समयout. */
	अगर (!रुको_event_समयout(s->q.करोne_wq, is_dma_करोne(s),
				msecs_to_jअगरfies(समयout_msec))) अणु
		omni_sg_dma_पात_channel(s);
		pr_warn("aborted\n");
	पूर्ण
	cobalt_ग_लिखो_bar0(cobalt, DMA_INTERRUPT_STATUS_REG,
			1 << s->dma_channel);
पूर्ण

अटल व्योम cobalt_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cobalt_stream *s = q->drv_priv;
	काष्ठा cobalt *cobalt = s->cobalt;
	पूर्णांक rx = s->video_channel;
	काष्ठा m00233_video_measure_regmap __iomem *vmr;
	काष्ठा m00473_मुक्तwheel_regmap __iomem *fw;
	काष्ठा m00479_clk_loss_detector_regmap __iomem *clkloss;
	काष्ठा cobalt_buffer *cb;
	काष्ठा list_head *p, *safe;
	अचिन्हित दीर्घ flags;

	cobalt_dma_stop_streaming(s);

	/* Return all buffers to user space */
	spin_lock_irqsave(&s->irqlock, flags);
	list_क्रम_each_safe(p, safe, &s->bufs) अणु
		cb = list_entry(p, काष्ठा cobalt_buffer, list);
		list_del(&cb->list);
		vb2_buffer_करोne(&cb->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&s->irqlock, flags);

	अगर (s->is_audio || s->is_output)
		वापस;

	fw = COBALT_CVI_FREEWHEEL(cobalt, rx);
	vmr = COBALT_CVI_VMR(cobalt, rx);
	clkloss = COBALT_CVI_CLK_LOSS(cobalt, rx);
	ioग_लिखो32(0, &vmr->control);
	ioग_लिखो32(M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK, &vmr->control);
	ioग_लिखो32(0, &fw->ctrl);
	ioग_लिखो32(0, &clkloss->ctrl);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cobalt_qops = अणु
	.queue_setup = cobalt_queue_setup,
	.buf_init = cobalt_buf_init,
	.buf_cleanup = cobalt_buf_cleanup,
	.buf_prepare = cobalt_buf_prepare,
	.buf_queue = cobalt_buf_queue,
	.start_streaming = cobalt_start_streaming,
	.stop_streaming = cobalt_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

/* V4L2 ioctls */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cobalt_cobaltc(काष्ठा cobalt *cobalt, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा v4l2_dbg_रेजिस्टर *regs = arg;
	व्योम __iomem *adrs = cobalt->bar1 + regs->reg;

	cobalt_info("cobalt_cobaltc: adrs = %p\n", adrs);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	regs->size = 4;
	अगर (cmd == VIDIOC_DBG_S_REGISTER)
		ioग_लिखो32(regs->val, adrs);
	अन्यथा
		regs->val = ioपढ़ो32(adrs);
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_g_रेजिस्टर(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा cobalt *cobalt = s->cobalt;

	वापस cobalt_cobaltc(cobalt, VIDIOC_DBG_G_REGISTER, reg);
पूर्ण

अटल पूर्णांक cobalt_s_रेजिस्टर(काष्ठा file *file, व्योम *priv_fh,
		स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा cobalt *cobalt = s->cobalt;

	वापस cobalt_cobaltc(cobalt, VIDIOC_DBG_S_REGISTER,
			(काष्ठा v4l2_dbg_रेजिस्टर *)reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cobalt_querycap(काष्ठा file *file, व्योम *priv_fh,
				काष्ठा v4l2_capability *vcap)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा cobalt *cobalt = s->cobalt;

	strscpy(vcap->driver, "cobalt", माप(vcap->driver));
	strscpy(vcap->card, "cobalt", माप(vcap->card));
	snम_लिखो(vcap->bus_info, माप(vcap->bus_info),
		 "PCIe:%s", pci_name(cobalt->pci_dev));
	vcap->capabilities = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_DEVICE_CAPS;
	अगर (cobalt->have_hsma_tx)
		vcap->capabilities |= V4L2_CAP_VIDEO_OUTPUT;
	वापस 0;
पूर्ण

अटल व्योम cobalt_video_input_status_show(काष्ठा cobalt_stream *s)
अणु
	काष्ठा m00389_cvi_regmap __iomem *cvi;
	काष्ठा m00233_video_measure_regmap __iomem *vmr;
	काष्ठा m00473_मुक्तwheel_regmap __iomem *fw;
	काष्ठा m00479_clk_loss_detector_regmap __iomem *clkloss;
	काष्ठा m00235_fdma_packer_regmap __iomem *packer;
	पूर्णांक rx = s->video_channel;
	काष्ठा cobalt *cobalt = s->cobalt;
	u32 cvi_ctrl, cvi_stat;
	u32 vmr_ctrl, vmr_stat;

	cvi = COBALT_CVI(cobalt, rx);
	vmr = COBALT_CVI_VMR(cobalt, rx);
	fw = COBALT_CVI_FREEWHEEL(cobalt, rx);
	clkloss = COBALT_CVI_CLK_LOSS(cobalt, rx);
	packer = COBALT_CVI_PACKER(cobalt, rx);
	cvi_ctrl = ioपढ़ो32(&cvi->control);
	cvi_stat = ioपढ़ो32(&cvi->status);
	vmr_ctrl = ioपढ़ो32(&vmr->control);
	vmr_stat = ioपढ़ो32(&vmr->status);
	cobalt_info("rx%d: cvi resolution: %dx%d\n", rx,
		    ioपढ़ो32(&cvi->frame_width), ioपढ़ो32(&cvi->frame_height));
	cobalt_info("rx%d: cvi control: %s%s%s\n", rx,
		(cvi_ctrl & M00389_CONTROL_BITMAP_ENABLE_MSK) ?
			"enable " : "disable ",
		(cvi_ctrl & M00389_CONTROL_BITMAP_HSYNC_POLARITY_LOW_MSK) ?
			"HSync- " : "HSync+ ",
		(cvi_ctrl & M00389_CONTROL_BITMAP_VSYNC_POLARITY_LOW_MSK) ?
			"VSync- " : "VSync+ ");
	cobalt_info("rx%d: cvi status: %s%s\n", rx,
		(cvi_stat & M00389_STATUS_BITMAP_LOCK_MSK) ?
			"lock " : "no-lock ",
		(cvi_stat & M00389_STATUS_BITMAP_ERROR_MSK) ?
			"error " : "no-error ");

	cobalt_info("rx%d: Measurements: %s%s%s%s%s%s%s\n", rx,
		(vmr_ctrl & M00233_CONTROL_BITMAP_HSYNC_POLARITY_LOW_MSK) ?
			"HSync- " : "HSync+ ",
		(vmr_ctrl & M00233_CONTROL_BITMAP_VSYNC_POLARITY_LOW_MSK) ?
			"VSync- " : "VSync+ ",
		(vmr_ctrl & M00233_CONTROL_BITMAP_ENABLE_MEASURE_MSK) ?
			"enabled " : "disabled ",
		(vmr_ctrl & M00233_CONTROL_BITMAP_ENABLE_INTERRUPT_MSK) ?
			"irq-enabled " : "irq-disabled ",
		(vmr_ctrl & M00233_CONTROL_BITMAP_UPDATE_ON_HSYNC_MSK) ?
			"update-on-hsync " : "",
		(vmr_stat & M00233_STATUS_BITMAP_HSYNC_TIMEOUT_MSK) ?
			"hsync-timeout " : "",
		(vmr_stat & M00233_STATUS_BITMAP_INIT_DONE_MSK) ?
			"init-done" : "");
	cobalt_info("rx%d: irq_status: 0x%02x irq_triggers: 0x%02x\n", rx,
			ioपढ़ो32(&vmr->irq_status) & 0xff,
			ioपढ़ो32(&vmr->irq_triggers) & 0xff);
	cobalt_info("rx%d: vsync: %d\n", rx, ioपढ़ो32(&vmr->vsync_समय));
	cobalt_info("rx%d: vbp: %d\n", rx, ioपढ़ो32(&vmr->vback_porch));
	cobalt_info("rx%d: vact: %d\n", rx, ioपढ़ो32(&vmr->vactive_area));
	cobalt_info("rx%d: vfb: %d\n", rx, ioपढ़ो32(&vmr->vfront_porch));
	cobalt_info("rx%d: hsync: %d\n", rx, ioपढ़ो32(&vmr->hsync_समय));
	cobalt_info("rx%d: hbp: %d\n", rx, ioपढ़ो32(&vmr->hback_porch));
	cobalt_info("rx%d: hact: %d\n", rx, ioपढ़ो32(&vmr->hactive_area));
	cobalt_info("rx%d: hfb: %d\n", rx, ioपढ़ो32(&vmr->hfront_porch));
	cobalt_info("rx%d: Freewheeling: %s%s%s\n", rx,
		(ioपढ़ो32(&fw->ctrl) & M00473_CTRL_BITMAP_ENABLE_MSK) ?
			"enabled " : "disabled ",
		(ioपढ़ो32(&fw->ctrl) & M00473_CTRL_BITMAP_FORCE_FREEWHEEL_MODE_MSK) ?
			"forced " : "",
		(ioपढ़ो32(&fw->status) & M00473_STATUS_BITMAP_FREEWHEEL_MODE_MSK) ?
			"freewheeling " : "video-passthrough ");
	ioग_लिखो32(0xff, &vmr->irq_status);
	cobalt_info("rx%d: Clock Loss Detection: %s%s\n", rx,
		(ioपढ़ो32(&clkloss->ctrl) & M00479_CTRL_BITMAP_ENABLE_MSK) ?
			"enabled " : "disabled ",
		(ioपढ़ो32(&clkloss->status) & M00479_STATUS_BITMAP_CLOCK_MISSING_MSK) ?
			"clock-missing " : "found-clock ");
	cobalt_info("rx%d: Packer: %x\n", rx, ioपढ़ो32(&packer->control));
पूर्ण

अटल पूर्णांक cobalt_log_status(काष्ठा file *file, व्योम *priv_fh)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा m00514_syncgen_flow_evcnt_regmap __iomem *vo =
		COBALT_TX_BASE(cobalt);
	u8 stat;

	cobalt_info("%s", cobalt->hdl_info);
	cobalt_info("sysctrl: %08x, sysstat: %08x\n",
			cobalt_g_sysctrl(cobalt),
			cobalt_g_sysstat(cobalt));
	cobalt_info("dma channel: %d, video channel: %d\n",
			s->dma_channel, s->video_channel);
	cobalt_pcie_status_show(cobalt);
	cobalt_cpld_status(cobalt);
	cobalt_irq_log_status(cobalt);
	v4l2_subdev_call(s->sd, core, log_status);
	अगर (!s->is_output) अणु
		cobalt_video_input_status_show(s);
		वापस 0;
	पूर्ण

	stat = ioपढ़ो32(&vo->rd_status);

	cobalt_info("tx: status: %s%s\n",
		(stat & M00514_RD_STATUS_BITMAP_FLOW_CTRL_NO_DATA_ERROR_MSK) ?
			"no_data " : "",
		(stat & M00514_RD_STATUS_BITMAP_READY_BUFFER_FULL_MSK) ?
			"ready_buffer_full " : "");
	cobalt_info("tx: evcnt: %d\n", ioपढ़ो32(&vo->rd_evcnt_count));
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_क्रमागत_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	अगर (s->input == 1) अणु
		अगर (timings->index)
			वापस -EINVAL;
		स_रखो(timings->reserved, 0, माप(timings->reserved));
		timings->timings = cea1080p60;
		वापस 0;
	पूर्ण
	timings->pad = 0;
	वापस v4l2_subdev_call(s->sd,
			pad, क्रमागत_dv_timings, timings);
पूर्ण

अटल पूर्णांक cobalt_s_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	पूर्णांक err;

	अगर (s->input == 1) अणु
		*timings = cea1080p60;
		वापस 0;
	पूर्ण

	अगर (v4l2_match_dv_timings(timings, &s->timings, 0, true))
		वापस 0;

	अगर (vb2_is_busy(&s->q))
		वापस -EBUSY;

	err = v4l2_subdev_call(s->sd,
			video, s_dv_timings, timings);
	अगर (!err) अणु
		s->timings = *timings;
		s->width = timings->bt.width;
		s->height = timings->bt.height;
		s->stride = timings->bt.width * s->bpp;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cobalt_g_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	अगर (s->input == 1) अणु
		*timings = cea1080p60;
		वापस 0;
	पूर्ण
	वापस v4l2_subdev_call(s->sd,
			video, g_dv_timings, timings);
पूर्ण

अटल पूर्णांक cobalt_query_dv_timings(काष्ठा file *file, व्योम *priv_fh,
				    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	अगर (s->input == 1) अणु
		*timings = cea1080p60;
		वापस 0;
	पूर्ण
	वापस v4l2_subdev_call(s->sd,
			video, query_dv_timings, timings);
पूर्ण

अटल पूर्णांक cobalt_dv_timings_cap(काष्ठा file *file, व्योम *priv_fh,
				    काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	cap->pad = 0;
	वापस v4l2_subdev_call(s->sd,
			pad, dv_timings_cap, cap);
पूर्ण

अटल पूर्णांक cobalt_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_fmtdesc *f)
अणु
	चयन (f->index) अणु
	हाल 0:
		f->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	हाल 1:
		f->pixelक्रमmat = V4L2_PIX_FMT_RGB24;
		अवरोध;
	हाल 2:
		f->pixelक्रमmat = V4L2_PIX_FMT_BGR32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytesperline = s->stride;
	pix->field = V4L2_FIELD_NONE;

	अगर (s->input == 1) अणु
		pix->colorspace = V4L2_COLORSPACE_SRGB;
	पूर्ण अन्यथा अणु
		sd_fmt.pad = s->pad_source;
		sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		v4l2_subdev_call(s->sd, pad, get_fmt, शून्य, &sd_fmt);
		v4l2_fill_pix_क्रमmat(pix, &sd_fmt.क्रमmat);
	पूर्ण

	pix->pixelक्रमmat = s->pixfmt;
	pix->sizeimage = pix->bytesperline * pix->height;

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt;

	/* Check क्रम min (QCIF) and max (Full HD) size */
	अगर ((pix->width < 176) || (pix->height < 144)) अणु
		pix->width = 176;
		pix->height = 144;
	पूर्ण

	अगर ((pix->width > 1920) || (pix->height > 1080)) अणु
		pix->width = 1920;
		pix->height = 1080;
	पूर्ण

	/* Make width multiple of 4 */
	pix->width &= ~0x3;

	/* Make height multiple of 2 */
	pix->height &= ~0x1;

	अगर (s->input == 1) अणु
		/* Generator => fixed क्रमmat only */
		pix->width = 1920;
		pix->height = 1080;
		pix->colorspace = V4L2_COLORSPACE_SRGB;
	पूर्ण अन्यथा अणु
		sd_fmt.pad = s->pad_source;
		sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		v4l2_subdev_call(s->sd, pad, get_fmt, शून्य, &sd_fmt);
		v4l2_fill_pix_क्रमmat(pix, &sd_fmt.क्रमmat);
	पूर्ण

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_YUYV);
		pix->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB24);
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB32);
		अवरोध;
	पूर्ण

	pix->sizeimage = pix->bytesperline * pix->height;
	pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	अगर (vb2_is_busy(&s->q))
		वापस -EBUSY;

	अगर (cobalt_try_fmt_vid_cap(file, priv_fh, f))
		वापस -EINVAL;

	s->width = pix->width;
	s->height = pix->height;
	s->stride = pix->bytesperline;
	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		s->bpp = COBALT_BYTES_PER_PIXEL_YUYV;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB24;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	s->pixfmt = pix->pixelक्रमmat;
	cobalt_enable_input(s);

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_try_fmt_vid_out(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	/* Check क्रम min (QCIF) and max (Full HD) size */
	अगर ((pix->width < 176) || (pix->height < 144)) अणु
		pix->width = 176;
		pix->height = 144;
	पूर्ण

	अगर ((pix->width > 1920) || (pix->height > 1080)) अणु
		pix->width = 1920;
		pix->height = 1080;
	पूर्ण

	/* Make width multiple of 4 */
	pix->width &= ~0x3;

	/* Make height multiple of 2 */
	pix->height &= ~0x1;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	शेष:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_YUYV);
		pix->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB32);
		अवरोध;
	पूर्ण

	pix->sizeimage = pix->bytesperline * pix->height;
	pix->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_g_fmt_vid_out(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytesperline = s->stride;
	pix->field = V4L2_FIELD_NONE;
	pix->pixelक्रमmat = s->pixfmt;
	pix->colorspace = s->colorspace;
	pix->xfer_func = s->xfer_func;
	pix->ycbcr_enc = s->ycbcr_enc;
	pix->quantization = s->quantization;
	pix->sizeimage = pix->bytesperline * pix->height;

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_fmtdesc *f)
अणु
	चयन (f->index) अणु
	हाल 0:
		f->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	हाल 1:
		f->pixelक्रमmat = V4L2_PIX_FMT_BGR32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_s_fmt_vid_out(काष्ठा file *file, व्योम *priv_fh,
		काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt = अणु 0 पूर्ण;
	u32 code;

	अगर (cobalt_try_fmt_vid_out(file, priv_fh, f))
		वापस -EINVAL;

	अगर (vb2_is_busy(&s->q) && (pix->pixelक्रमmat != s->pixfmt ||
	    pix->width != s->width || pix->height != s->height ||
	    pix->bytesperline != s->stride))
		वापस -EBUSY;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		s->bpp = COBALT_BYTES_PER_PIXEL_YUYV;
		code = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB32;
		code = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	s->width = pix->width;
	s->height = pix->height;
	s->stride = pix->bytesperline;
	s->pixfmt = pix->pixelक्रमmat;
	s->colorspace = pix->colorspace;
	s->xfer_func = pix->xfer_func;
	s->ycbcr_enc = pix->ycbcr_enc;
	s->quantization = pix->quantization;
	sd_fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	v4l2_fill_mbus_क्रमmat(&sd_fmt.क्रमmat, pix, code);
	v4l2_subdev_call(s->sd, pad, set_fmt, शून्य, &sd_fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_क्रमागत_input(काष्ठा file *file, व्योम *priv_fh,
				 काष्ठा v4l2_input *inp)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	अगर (inp->index > 1)
		वापस -EINVAL;
	अगर (inp->index == 0)
		snम_लिखो(inp->name, माप(inp->name),
				"HDMI-%d", s->video_channel);
	अन्यथा
		snम_लिखो(inp->name, माप(inp->name),
				"Generator-%d", s->video_channel);
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	अगर (inp->index == 1)
		वापस 0;
	वापस v4l2_subdev_call(s->sd,
			video, g_input_status, &inp->status);
पूर्ण

अटल पूर्णांक cobalt_g_input(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	*i = s->input;
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_s_input(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक i)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);

	अगर (i >= 2)
		वापस -EINVAL;
	अगर (vb2_is_busy(&s->q))
		वापस -EBUSY;
	s->input = i;

	cobalt_enable_input(s);

	अगर (s->input == 1) /* Test Pattern Generator */
		वापस 0;

	वापस v4l2_subdev_call(s->sd, video, s_routing,
			ADV76XX_PAD_HDMI_PORT_A, 0, 0);
पूर्ण

अटल पूर्णांक cobalt_क्रमागत_output(काष्ठा file *file, व्योम *priv_fh,
				 काष्ठा v4l2_output *out)
अणु
	अगर (out->index)
		वापस -EINVAL;
	snम_लिखो(out->name, माप(out->name), "HDMI-%d", out->index);
	out->type = V4L2_OUTPUT_TYPE_ANALOG;
	out->capabilities = V4L2_OUT_CAP_DV_TIMINGS;
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_g_output(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_s_output(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक cobalt_g_edid(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	u32 pad = edid->pad;
	पूर्णांक ret;

	अगर (edid->pad >= (s->is_output ? 1 : 2))
		वापस -EINVAL;
	edid->pad = 0;
	ret = v4l2_subdev_call(s->sd, pad, get_edid, edid);
	edid->pad = pad;
	वापस ret;
पूर्ण

अटल पूर्णांक cobalt_s_edid(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	u32 pad = edid->pad;
	पूर्णांक ret;

	अगर (edid->pad >= 2)
		वापस -EINVAL;
	edid->pad = 0;
	ret = v4l2_subdev_call(s->sd, pad, set_edid, edid);
	edid->pad = pad;
	वापस ret;
पूर्ण

अटल पूर्णांक cobalt_subscribe_event(काष्ठा v4l2_fh *fh,
				  स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_event_subscribe(fh, sub, 4, शून्य);
	पूर्ण
	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण

अटल पूर्णांक cobalt_g_parm(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_fract fps;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	fps = v4l2_calc_समयperframe(&s->timings);
	a->parm.capture.समयperframe.numerator = fps.numerator;
	a->parm.capture.समयperframe.denominator = fps.denominator;
	a->parm.capture.पढ़ोbuffers = 3;
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_g_pixelaspect(काष्ठा file *file, व्योम *fh,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_dv_timings timings;
	पूर्णांक err = 0;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (s->input == 1)
		timings = cea1080p60;
	अन्यथा
		err = v4l2_subdev_call(s->sd, video, g_dv_timings, &timings);
	अगर (!err)
		*f = v4l2_dv_timings_aspect_ratio(&timings);
	वापस err;
पूर्ण

अटल पूर्णांक cobalt_g_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा cobalt_stream *s = video_drvdata(file);
	काष्ठा v4l2_dv_timings timings;
	पूर्णांक err = 0;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (s->input == 1)
		timings = cea1080p60;
	अन्यथा
		err = v4l2_subdev_call(s->sd, video, g_dv_timings, &timings);

	अगर (err)
		वापस err;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = timings.bt.width;
		sel->r.height = timings.bt.height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops cobalt_ioctl_ops = अणु
	.vidioc_querycap		= cobalt_querycap,
	.vidioc_g_parm			= cobalt_g_parm,
	.vidioc_log_status		= cobalt_log_status,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_g_pixelaspect		= cobalt_g_pixelaspect,
	.vidioc_g_selection		= cobalt_g_selection,
	.vidioc_क्रमागत_input		= cobalt_क्रमागत_input,
	.vidioc_g_input			= cobalt_g_input,
	.vidioc_s_input			= cobalt_s_input,
	.vidioc_क्रमागत_fmt_vid_cap	= cobalt_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= cobalt_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= cobalt_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= cobalt_try_fmt_vid_cap,
	.vidioc_क्रमागत_output		= cobalt_क्रमागत_output,
	.vidioc_g_output		= cobalt_g_output,
	.vidioc_s_output		= cobalt_s_output,
	.vidioc_क्रमागत_fmt_vid_out	= cobalt_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= cobalt_g_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= cobalt_s_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= cobalt_try_fmt_vid_out,
	.vidioc_s_dv_timings		= cobalt_s_dv_timings,
	.vidioc_g_dv_timings		= cobalt_g_dv_timings,
	.vidioc_query_dv_timings	= cobalt_query_dv_timings,
	.vidioc_क्रमागत_dv_timings		= cobalt_क्रमागत_dv_timings,
	.vidioc_dv_timings_cap		= cobalt_dv_timings_cap,
	.vidioc_g_edid			= cobalt_g_edid,
	.vidioc_s_edid			= cobalt_s_edid,
	.vidioc_subscribe_event		= cobalt_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर              = cobalt_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर              = cobalt_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops cobalt_ioctl_empty_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर              = cobalt_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर              = cobalt_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

/* Register device nodes */

अटल स्थिर काष्ठा v4l2_file_operations cobalt_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.unlocked_ioctl = video_ioctl2,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
	.पढ़ो = vb2_fop_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations cobalt_out_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.unlocked_ioctl = video_ioctl2,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
	.ग_लिखो = vb2_fop_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations cobalt_empty_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.unlocked_ioctl = video_ioctl2,
	.release = v4l2_fh_release,
पूर्ण;

अटल पूर्णांक cobalt_node_रेजिस्टर(काष्ठा cobalt *cobalt, पूर्णांक node)
अणु
	अटल स्थिर काष्ठा v4l2_dv_timings dv1080p60 =
		V4L2_DV_BT_CEA_1920X1080P60;
	काष्ठा cobalt_stream *s = cobalt->streams + node;
	काष्ठा video_device *vdev = &s->vdev;
	काष्ठा vb2_queue *q = &s->q;
	पूर्णांक ret;

	mutex_init(&s->lock);
	spin_lock_init(&s->irqlock);

	snम_लिखो(vdev->name, माप(vdev->name),
			"%s-%d", cobalt->v4l2_dev.name, node);
	s->width = 1920;
	/* Audio frames are just 4 lines of 1920 bytes */
	s->height = s->is_audio ? 4 : 1080;

	अगर (s->is_audio) अणु
		s->bpp = 1;
		s->pixfmt = V4L2_PIX_FMT_GREY;
	पूर्ण अन्यथा अगर (s->is_output) अणु
		s->bpp = COBALT_BYTES_PER_PIXEL_RGB32;
		s->pixfmt = V4L2_PIX_FMT_BGR32;
	पूर्ण अन्यथा अणु
		s->bpp = COBALT_BYTES_PER_PIXEL_YUYV;
		s->pixfmt = V4L2_PIX_FMT_YUYV;
	पूर्ण
	s->colorspace = V4L2_COLORSPACE_SRGB;
	s->stride = s->width * s->bpp;

	अगर (!s->is_audio) अणु
		अगर (s->is_dummy)
			cobalt_warn("Setting up dummy video node %d\n", node);
		vdev->v4l2_dev = &cobalt->v4l2_dev;
		अगर (s->is_dummy)
			vdev->fops = &cobalt_empty_fops;
		अन्यथा
			vdev->fops = s->is_output ? &cobalt_out_fops :
						    &cobalt_fops;
		vdev->release = video_device_release_empty;
		vdev->vfl_dir = s->is_output ? VFL_सूची_TX : VFL_सूची_RX;
		vdev->lock = &s->lock;
		अगर (s->sd)
			vdev->ctrl_handler = s->sd->ctrl_handler;
		s->timings = dv1080p60;
		v4l2_subdev_call(s->sd, video, s_dv_timings, &s->timings);
		अगर (!s->is_output && s->sd)
			cobalt_enable_input(s);
		vdev->ioctl_ops = s->is_dummy ? &cobalt_ioctl_empty_ops :
				  &cobalt_ioctl_ops;
	पूर्ण

	INIT_LIST_HEAD(&s->bufs);
	q->type = s->is_output ? V4L2_BUF_TYPE_VIDEO_OUTPUT :
				 V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->io_modes |= s->is_output ? VB2_WRITE : VB2_READ;
	q->drv_priv = s;
	q->buf_काष्ठा_size = माप(काष्ठा cobalt_buffer);
	q->ops = &cobalt_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->lock = &s->lock;
	q->dev = &cobalt->pci_dev->dev;
	vdev->queue = q;
	vdev->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	अगर (s->is_output)
		vdev->device_caps |= V4L2_CAP_VIDEO_OUTPUT;
	अन्यथा
		vdev->device_caps |= V4L2_CAP_VIDEO_CAPTURE;

	video_set_drvdata(vdev, s);
	ret = vb2_queue_init(q);
	अगर (!s->is_audio && ret == 0)
		ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अन्यथा अगर (!s->is_dummy)
		ret = cobalt_alsa_init(s);

	अगर (ret < 0) अणु
		अगर (!s->is_audio)
			cobalt_err("couldn't register v4l2 device node %d\n",
					node);
		वापस ret;
	पूर्ण
	cobalt_info("registered node %d\n", node);
	वापस 0;
पूर्ण

/* Initialize v4l2 variables and रेजिस्टर v4l2 devices */
पूर्णांक cobalt_nodes_रेजिस्टर(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक node, ret;

	/* Setup V4L2 Devices */
	क्रम (node = 0; node < COBALT_NUM_STREAMS; node++) अणु
		ret = cobalt_node_रेजिस्टर(cobalt, node);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Unरेजिस्टर v4l2 devices */
व्योम cobalt_nodes_unरेजिस्टर(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक node;

	/* Tearकरोwn all streams */
	क्रम (node = 0; node < COBALT_NUM_STREAMS; node++) अणु
		काष्ठा cobalt_stream *s = cobalt->streams + node;
		काष्ठा video_device *vdev = &s->vdev;

		अगर (!s->is_audio)
			video_unरेजिस्टर_device(vdev);
		अन्यथा अगर (!s->is_dummy)
			cobalt_alsa_निकास(s);
	पूर्ण
पूर्ण
