<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@linuxtv.org> cx25821 driver
 *  Parts adapted/taken from Eduarकरो Moscoso Rubino
 *  Copyright (C) 2009 Eduarकरो Moscoso Rubino <moscoso@TopoLogica.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "cx25821-video.h"

MODULE_DESCRIPTION("v4l2 driver module for cx25821 based TV cards");
MODULE_AUTHOR("Hiep Huynh <hiep.huynh@conexant.com>");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (CX25821_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(video_nr, पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(video_nr, "video device numbers");

अटल अचिन्हित पूर्णांक video_debug = VIDEO_DEBUG;
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug, "enable debug messages [video]");

अटल अचिन्हित पूर्णांक irq_debug;
module_param(irq_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(irq_debug, "enable debug messages [IRQ handler]");

#घोषणा FORMAT_FLAGS_PACKED       0x01

अटल स्थिर काष्ठा cx25821_fmt क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_Y41P,
		.depth = 12,
		.flags = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.depth = 16,
		.flags = FORMAT_FLAGS_PACKED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cx25821_fmt *cx25821_क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats + i;
	वापस शून्य;
पूर्ण

पूर्णांक cx25821_start_video_dma(काष्ठा cx25821_dev *dev,
			    काष्ठा cx25821_dmaqueue *q,
			    काष्ठा cx25821_buffer *buf,
			    स्थिर काष्ठा sram_channel *channel)
अणु
	पूर्णांक पंचांगp = 0;

	/* setup fअगरo + क्रमmat */
	cx25821_sram_channel_setup(dev, channel, buf->bpl, buf->risc.dma);

	/* reset counter */
	cx_ग_लिखो(channel->gpcnt_ctl, 3);

	/* enable irq */
	cx_set(PCI_INT_MSK, cx_पढ़ो(PCI_INT_MSK) | (1 << channel->i));
	cx_set(channel->पूर्णांक_msk, 0x11);

	/* start dma */
	cx_ग_लिखो(channel->dma_ctl, 0x11);	/* FIFO and RISC enable */

	/* make sure upstream setting अगर any is reversed */
	पंचांगp = cx_पढ़ो(VID_CH_MODE_SEL);
	cx_ग_लिखो(VID_CH_MODE_SEL, पंचांगp & 0xFFFFFE00);

	वापस 0;
पूर्ण

पूर्णांक cx25821_video_irq(काष्ठा cx25821_dev *dev, पूर्णांक chan_num, u32 status)
अणु
	पूर्णांक handled = 0;
	u32 mask;
	स्थिर काष्ठा sram_channel *channel = dev->channels[chan_num].sram_channels;

	mask = cx_पढ़ो(channel->पूर्णांक_msk);
	अगर (0 == (status & mask))
		वापस handled;

	cx_ग_लिखो(channel->पूर्णांक_stat, status);

	/* risc op code error */
	अगर (status & (1 << 16)) अणु
		pr_warn("%s, %s: video risc op code error\n",
			dev->name, channel->name);
		cx_clear(channel->dma_ctl, 0x11);
		cx25821_sram_channel_dump(dev, channel);
	पूर्ण

	/* risc1 y */
	अगर (status & FLD_VID_DST_RISC1) अणु
		काष्ठा cx25821_dmaqueue *dmaq =
			&dev->channels[channel->i].dma_vidq;
		काष्ठा cx25821_buffer *buf;

		spin_lock(&dev->slock);
		अगर (!list_empty(&dmaq->active)) अणु
			buf = list_entry(dmaq->active.next,
					 काष्ठा cx25821_buffer, queue);

			buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
			buf->vb.sequence = dmaq->count++;
			list_del(&buf->queue);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		पूर्ण
		spin_unlock(&dev->slock);
		handled++;
	पूर्ण
	वापस handled;
पूर्ण

अटल पूर्णांक cx25821_queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx25821_channel *chan = q->drv_priv;
	अचिन्हित size = (chan->fmt->depth * chan->width * chan->height) >> 3;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx25821_channel *chan = vb->vb2_queue->drv_priv;
	काष्ठा cx25821_dev *dev = chan->dev;
	काष्ठा cx25821_buffer *buf =
		container_of(vbuf, काष्ठा cx25821_buffer, vb);
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	u32 line0_offset;
	पूर्णांक bpl_local = LINE_SIZE_D1;
	पूर्णांक ret;

	अगर (chan->pixel_क्रमmats == PIXEL_FRMT_411)
		buf->bpl = (chan->fmt->depth * chan->width) >> 3;
	अन्यथा
		buf->bpl = (chan->fmt->depth >> 3) * chan->width;

	अगर (vb2_plane_size(vb, 0) < chan->height * buf->bpl)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, chan->height * buf->bpl);
	buf->vb.field = chan->field;

	अगर (chan->pixel_क्रमmats == PIXEL_FRMT_411) अणु
		bpl_local = buf->bpl;
	पूर्ण अन्यथा अणु
		bpl_local = buf->bpl;   /* Default */

		अगर (chan->use_cअगर_resolution) अणु
			अगर (dev->tvnorm & V4L2_STD_625_50)
				bpl_local = 352 << 1;
			अन्यथा
				bpl_local = chan->cअगर_width << 1;
		पूर्ण
	पूर्ण

	चयन (chan->field) अणु
	हाल V4L2_FIELD_TOP:
		ret = cx25821_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, 0, UNSET,
				buf->bpl, 0, chan->height);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		ret = cx25821_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, UNSET, 0,
				buf->bpl, 0, chan->height);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		/* All other क्रमmats are top field first */
		line0_offset = 0;
		dprपूर्णांकk(1, "top field first\n");

		ret = cx25821_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, line0_offset,
				bpl_local, bpl_local, bpl_local,
				chan->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		ret = cx25821_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl,
				0, buf->bpl * (chan->height >> 1),
				buf->bpl, 0, chan->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_BT:
		ret = cx25821_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl,
				buf->bpl * (chan->height >> 1), 0,
				buf->bpl, 0, chan->height >> 1);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	dprपूर्णांकk(2, "[%p/%d] buffer_prep - %dx%d %dbpp 0x%08x - dma=0x%08lx\n",
		buf, buf->vb.vb2_buf.index, chan->width, chan->height,
		chan->fmt->depth, chan->fmt->fourcc,
		(अचिन्हित दीर्घ)buf->risc.dma);

	वापस ret;
पूर्ण

अटल व्योम cx25821_buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx25821_buffer *buf =
		container_of(vbuf, काष्ठा cx25821_buffer, vb);
	काष्ठा cx25821_channel *chan = vb->vb2_queue->drv_priv;
	काष्ठा cx25821_dev *dev = chan->dev;

	cx25821_मुक्त_buffer(dev, buf);
पूर्ण

अटल व्योम cx25821_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx25821_buffer *buf =
		container_of(vbuf, काष्ठा cx25821_buffer, vb);
	काष्ठा cx25821_channel *chan = vb->vb2_queue->drv_priv;
	काष्ठा cx25821_dev *dev = chan->dev;
	काष्ठा cx25821_buffer *prev;
	काष्ठा cx25821_dmaqueue *q = &dev->channels[chan->id].dma_vidq;

	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[2] = cpu_to_le32(0); /* bits 63-32 */

	अगर (list_empty(&q->active)) अणु
		list_add_tail(&buf->queue, &q->active);
	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, काष्ठा cx25821_buffer,
				queue);
		list_add_tail(&buf->queue, &q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
	पूर्ण
पूर्ण

अटल पूर्णांक cx25821_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx25821_channel *chan = q->drv_priv;
	काष्ठा cx25821_dev *dev = chan->dev;
	काष्ठा cx25821_dmaqueue *dmaq = &dev->channels[chan->id].dma_vidq;
	काष्ठा cx25821_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx25821_buffer, queue);

	dmaq->count = 0;
	cx25821_start_video_dma(dev, dmaq, buf, chan->sram_channels);
	वापस 0;
पूर्ण

अटल व्योम cx25821_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx25821_channel *chan = q->drv_priv;
	काष्ठा cx25821_dev *dev = chan->dev;
	काष्ठा cx25821_dmaqueue *dmaq = &dev->channels[chan->id].dma_vidq;
	अचिन्हित दीर्घ flags;

	cx_ग_लिखो(chan->sram_channels->dma_ctl, 0); /* FIFO and RISC disable */
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx25821_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx25821_buffer, queue);

		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cx25821_video_qops = अणु
	.queue_setup    = cx25821_queue_setup,
	.buf_prepare  = cx25821_buffer_prepare,
	.buf_finish = cx25821_buffer_finish,
	.buf_queue    = cx25821_buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = cx25821_start_streaming,
	.stop_streaming = cx25821_stop_streaming,
पूर्ण;

/* VIDEO IOCTLS */

अटल पूर्णांक cx25821_vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (unlikely(f->index >= ARRAY_SIZE(क्रमmats)))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);

	f->fmt.pix.width = chan->width;
	f->fmt.pix.height = chan->height;
	f->fmt.pix.field = chan->field;
	f->fmt.pix.pixelक्रमmat = chan->fmt->fourcc;
	f->fmt.pix.bytesperline = (chan->width * chan->fmt->depth) >> 3;
	f->fmt.pix.sizeimage = chan->height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;
	स्थिर काष्ठा cx25821_fmt *fmt;
	क्रमागत v4l2_field field = f->fmt.pix.field;
	अचिन्हित पूर्णांक maxh;
	अचिन्हित w;

	fmt = cx25821_क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;
	maxh = (dev->tvnorm & V4L2_STD_625_50) ? 576 : 480;

	w = f->fmt.pix.width;
	अगर (field != V4L2_FIELD_BOTTOM)
		field = V4L2_FIELD_TOP;
	अगर (w < 352) अणु
		w = 176;
		f->fmt.pix.height = maxh / 4;
	पूर्ण अन्यथा अगर (w < 720) अणु
		w = 352;
		f->fmt.pix.height = maxh / 2;
	पूर्ण अन्यथा अणु
		w = 720;
		f->fmt.pix.height = maxh;
		field = V4L2_FIELD_INTERLACED;
	पूर्ण
	f->fmt.pix.field = field;
	f->fmt.pix.width = w;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;
	पूर्णांक pix_क्रमmat = PIXEL_FRMT_422;
	पूर्णांक err;

	err = cx25821_vidioc_try_fmt_vid_cap(file, priv, f);

	अगर (0 != err)
		वापस err;

	chan->fmt = cx25821_क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	chan->field = f->fmt.pix.field;
	chan->width = f->fmt.pix.width;
	chan->height = f->fmt.pix.height;

	अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_Y41P)
		pix_क्रमmat = PIXEL_FRMT_411;
	अन्यथा
		pix_क्रमmat = PIXEL_FRMT_422;

	cx25821_set_pixel_क्रमmat(dev, SRAM_CH00, pix_क्रमmat);

	/* check अगर cअगर resolution */
	अगर (chan->width == 320 || chan->width == 352)
		chan->use_cअगर_resolution = 1;
	अन्यथा
		chan->use_cअगर_resolution = 0;

	chan->cअगर_width = chan->width;
	medusa_set_resolution(dev, chan->width, SRAM_CH00);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;
	स्थिर काष्ठा sram_channel *sram_ch = chan->sram_channels;
	u32 पंचांगp = 0;

	पंचांगp = cx_पढ़ो(sram_ch->dma_ctl);
	pr_info("Video input 0 is %s\n",
		(पंचांगp & 0x11) ? "streaming" : "stopped");
	वापस 0;
पूर्ण


अटल पूर्णांक cx25821_vidioc_querycap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;

	strscpy(cap->driver, "cx25821", माप(cap->driver));
	strscpy(cap->card, cx25821_boards[dev->board].name, माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OUTPUT |
			    V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *tvnorms)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);

	*tvnorms = chan->dev->tvnorm;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_s_std(काष्ठा file *file, व्योम *priv,
				v4l2_std_id tvnorms)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;

	अगर (dev->tvnorm == tvnorms)
		वापस 0;

	dev->tvnorm = tvnorms;
	chan->width = 720;
	chan->height = (dev->tvnorm & V4L2_STD_625_50) ? 576 : 480;

	medusa_set_videostandard(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_input *i)
अणु
	अगर (i->index)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = CX25821_NORMS;
	strscpy(i->name, "Composite", माप(i->name));
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक cx25821_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा cx25821_channel *chan =
		container_of(ctrl->handler, काष्ठा cx25821_channel, hdl);
	काष्ठा cx25821_dev *dev = chan->dev;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		medusa_set_brightness(dev, ctrl->val, chan->id);
		अवरोध;
	हाल V4L2_CID_HUE:
		medusa_set_hue(dev, ctrl->val, chan->id);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		medusa_set_contrast(dev, ctrl->val, chan->id);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		medusa_set_saturation(dev, ctrl->val, chan->id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_क्रमागत_output(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_output *o)
अणु
	अगर (o->index)
		वापस -EINVAL;

	o->type = V4L2_INPUT_TYPE_CAMERA;
	o->std = CX25821_NORMS;
	strscpy(o->name, "Composite", माप(o->name));
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_g_output(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *o)
अणु
	*o = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_s_output(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक o)
अणु
	वापस o ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक cx25821_vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	काष्ठा cx25821_dev *dev = chan->dev;
	स्थिर काष्ठा cx25821_fmt *fmt;

	fmt = cx25821_क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;
	f->fmt.pix.width = 720;
	f->fmt.pix.height = (dev->tvnorm & V4L2_STD_625_50) ? 576 : 480;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx25821_channel *chan = video_drvdata(file);
	पूर्णांक err;

	err = cx25821_vidioc_try_fmt_vid_out(file, priv, f);

	अगर (0 != err)
		वापस err;

	chan->fmt = cx25821_क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	chan->field = f->fmt.pix.field;
	chan->width = f->fmt.pix.width;
	chan->height = f->fmt.pix.height;
	अगर (f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_Y41P)
		chan->pixel_क्रमmats = PIXEL_FRMT_411;
	अन्यथा
		chan->pixel_क्रमmats = PIXEL_FRMT_422;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops cx25821_ctrl_ops = अणु
	.s_ctrl = cx25821_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations video_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release        = vb2_fop_release,
	.पढ़ो           = vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap = cx25821_vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = cx25821_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = cx25821_vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = cx25821_vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_create_bufs   = vb2_ioctl_create_bufs,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_g_std = cx25821_vidioc_g_std,
	.vidioc_s_std = cx25821_vidioc_s_std,
	.vidioc_क्रमागत_input = cx25821_vidioc_क्रमागत_input,
	.vidioc_g_input = cx25821_vidioc_g_input,
	.vidioc_s_input = cx25821_vidioc_s_input,
	.vidioc_log_status = vidioc_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device cx25821_video_device = अणु
	.name = "cx25821-video",
	.fops = &video_fops,
	.release = video_device_release_empty,
	.minor = -1,
	.ioctl_ops = &video_ioctl_ops,
	.tvnorms = CX25821_NORMS,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		       V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations video_out_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release        = vb2_fop_release,
	.ग_लिखो          = vb2_fop_ग_लिखो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_out_ioctl_ops = अणु
	.vidioc_querycap = cx25821_vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_out = cx25821_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = cx25821_vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_out = cx25821_vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out = vidioc_s_fmt_vid_out,
	.vidioc_g_std = cx25821_vidioc_g_std,
	.vidioc_s_std = cx25821_vidioc_s_std,
	.vidioc_क्रमागत_output = cx25821_vidioc_क्रमागत_output,
	.vidioc_g_output = cx25821_vidioc_g_output,
	.vidioc_s_output = cx25821_vidioc_s_output,
	.vidioc_log_status = vidioc_log_status,
पूर्ण;

अटल स्थिर काष्ठा video_device cx25821_video_out_device = अणु
	.name = "cx25821-video",
	.fops = &video_out_fops,
	.release = video_device_release_empty,
	.minor = -1,
	.ioctl_ops = &video_out_ioctl_ops,
	.tvnorms = CX25821_NORMS,
	.device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_READWRITE,
पूर्ण;

व्योम cx25821_video_unरेजिस्टर(काष्ठा cx25821_dev *dev, पूर्णांक chan_num)
अणु
	cx_clear(PCI_INT_MSK, 1);

	अगर (video_is_रेजिस्टरed(&dev->channels[chan_num].vdev)) अणु
		video_unरेजिस्टर_device(&dev->channels[chan_num].vdev);
		v4l2_ctrl_handler_मुक्त(&dev->channels[chan_num].hdl);
	पूर्ण
पूर्ण

पूर्णांक cx25821_video_रेजिस्टर(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक err;
	पूर्णांक i;

	/* initial device configuration */
	dev->tvnorm = V4L2_STD_NTSC_M;

	spin_lock_init(&dev->slock);

	क्रम (i = 0; i < MAX_VID_CAP_CHANNEL_NUM - 1; ++i) अणु
		काष्ठा cx25821_channel *chan = &dev->channels[i];
		काष्ठा video_device *vdev = &chan->vdev;
		काष्ठा v4l2_ctrl_handler *hdl = &chan->hdl;
		काष्ठा vb2_queue *q;
		bool is_output = i > SRAM_CH08;

		अगर (i == SRAM_CH08) /* audio channel */
			जारी;

		अगर (!is_output) अणु
			v4l2_ctrl_handler_init(hdl, 4);
			v4l2_ctrl_new_std(hdl, &cx25821_ctrl_ops,
					V4L2_CID_BRIGHTNESS, 0, 10000, 1, 6200);
			v4l2_ctrl_new_std(hdl, &cx25821_ctrl_ops,
					V4L2_CID_CONTRAST, 0, 10000, 1, 5000);
			v4l2_ctrl_new_std(hdl, &cx25821_ctrl_ops,
					V4L2_CID_SATURATION, 0, 10000, 1, 5000);
			v4l2_ctrl_new_std(hdl, &cx25821_ctrl_ops,
					V4L2_CID_HUE, 0, 10000, 1, 5000);
			अगर (hdl->error) अणु
				err = hdl->error;
				जाओ fail_unreg;
			पूर्ण
			err = v4l2_ctrl_handler_setup(hdl);
			अगर (err)
				जाओ fail_unreg;
		पूर्ण अन्यथा अणु
			chan->out = &dev->vid_out_data[i - SRAM_CH09];
			chan->out->chan = chan;
		पूर्ण

		chan->sram_channels = &cx25821_sram_channels[i];
		chan->width = 720;
		chan->field = V4L2_FIELD_INTERLACED;
		अगर (dev->tvnorm & V4L2_STD_625_50)
			chan->height = 576;
		अन्यथा
			chan->height = 480;

		अगर (chan->pixel_क्रमmats == PIXEL_FRMT_411)
			chan->fmt = cx25821_क्रमmat_by_fourcc(V4L2_PIX_FMT_Y41P);
		अन्यथा
			chan->fmt = cx25821_क्रमmat_by_fourcc(V4L2_PIX_FMT_YUYV);

		cx_ग_लिखो(chan->sram_channels->पूर्णांक_stat, 0xffffffff);

		INIT_LIST_HEAD(&chan->dma_vidq.active);

		q = &chan->vidq;

		q->type = is_output ? V4L2_BUF_TYPE_VIDEO_OUTPUT :
				      V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
		q->io_modes |= is_output ? VB2_WRITE : VB2_READ;
		q->gfp_flags = GFP_DMA32;
		q->min_buffers_needed = 2;
		q->drv_priv = chan;
		q->buf_काष्ठा_size = माप(काष्ठा cx25821_buffer);
		q->ops = &cx25821_video_qops;
		q->mem_ops = &vb2_dma_sg_memops;
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->lock = &dev->lock;
		q->dev = &dev->pci->dev;

		अगर (!is_output) अणु
			err = vb2_queue_init(q);
			अगर (err < 0)
				जाओ fail_unreg;
		पूर्ण

		/* रेजिस्टर v4l devices */
		*vdev = is_output ? cx25821_video_out_device : cx25821_video_device;
		vdev->v4l2_dev = &dev->v4l2_dev;
		अगर (!is_output)
			vdev->ctrl_handler = hdl;
		अन्यथा
			vdev->vfl_dir = VFL_सूची_TX;
		vdev->lock = &dev->lock;
		vdev->queue = q;
		snम_लिखो(vdev->name, माप(vdev->name), "%s #%d", dev->name, i);
		video_set_drvdata(vdev, chan);

		err = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO,
					    video_nr[dev->nr]);

		अगर (err < 0)
			जाओ fail_unreg;
	पूर्ण

	/* set PCI पूर्णांकerrupt */
	cx_set(PCI_INT_MSK, 0xff);

	वापस 0;

fail_unreg:
	जबतक (i >= 0)
		cx25821_video_unरेजिस्टर(dev, i--);
	वापस err;
पूर्ण
