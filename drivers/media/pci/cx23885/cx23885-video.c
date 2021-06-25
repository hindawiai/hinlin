<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-video.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश "cx23885-ioctl.h"
#समावेश "tuner-xc2028.h"

#समावेश <media/drv-पूर्णांकf/cx25840.h>

MODULE_DESCRIPTION("v4l2 driver module for cx23885 based TV cards");
MODULE_AUTHOR("Steven Toth <stoth@linuxtv.org>");
MODULE_LICENSE("GPL");

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (CX23885_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक vbi_nr[]   = अणु[0 ... (CX23885_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(video_nr, पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr,   पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(video_nr, "video device numbers");
MODULE_PARM_DESC(vbi_nr, "vbi device numbers");

अटल अचिन्हित पूर्णांक video_debug;
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug, "enable debug messages [video]");

अटल अचिन्हित पूर्णांक irq_debug;
module_param(irq_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(irq_debug, "enable debug messages [IRQ handler]");

अटल अचिन्हित पूर्णांक vid_limit = 16;
module_param(vid_limit, पूर्णांक, 0644);
MODULE_PARM_DESC(vid_limit, "capture memory limit in megabytes");

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (video_debug >= level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: video:" fmt), \
			__func__, ##arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------- */
/* अटल data                                                         */

#घोषणा FORMAT_FLAGS_PACKED       0x01
अटल काष्ठा cx23885_fmt क्रमmats[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण
पूर्ण;

अटल काष्ठा cx23885_fmt *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats+i;
	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------- */

व्योम cx23885_video_wakeup(काष्ठा cx23885_dev *dev,
	काष्ठा cx23885_dmaqueue *q, u32 count)
अणु
	काष्ठा cx23885_buffer *buf;

	अगर (list_empty(&q->active))
		वापस;
	buf = list_entry(q->active.next,
			काष्ठा cx23885_buffer, queue);

	buf->vb.sequence = q->count++;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	dprपूर्णांकk(2, "[%p/%d] wakeup reg=%d buf=%d\n", buf,
			buf->vb.vb2_buf.index, count, q->count);
	list_del(&buf->queue);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

पूर्णांक cx23885_set_tvnorm(काष्ठा cx23885_dev *dev, v4l2_std_id norm)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat.code = MEDIA_BUS_FMT_FIXED,
	पूर्ण;

	dprपूर्णांकk(1, "%s(norm = 0x%08x) name: [%s]\n",
		__func__,
		(अचिन्हित पूर्णांक)norm,
		v4l2_norm_to_name(norm));

	अगर (dev->tvnorm == norm)
		वापस 0;

	अगर (dev->tvnorm != norm) अणु
		अगर (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq) ||
		    vb2_is_busy(&dev->vb2_mpegq))
			वापस -EBUSY;
	पूर्ण

	dev->tvnorm = norm;
	dev->width = 720;
	dev->height = norm_maxh(norm);
	dev->field = V4L2_FIELD_INTERLACED;

	call_all(dev, video, s_std, norm);

	क्रमmat.क्रमmat.width = dev->width;
	क्रमmat.क्रमmat.height = dev->height;
	क्रमmat.क्रमmat.field = dev->field;
	call_all(dev, pad, set_fmt, शून्य, &क्रमmat);

	वापस 0;
पूर्ण

अटल काष्ठा video_device *cx23885_vdev_init(काष्ठा cx23885_dev *dev,
				    काष्ठा pci_dev *pci,
				    काष्ठा video_device *ढाँचा,
				    अक्षर *type)
अणु
	काष्ठा video_device *vfd;
	dprपूर्णांकk(1, "%s()\n", __func__);

	vfd = video_device_alloc();
	अगर (शून्य == vfd)
		वापस शून्य;
	*vfd = *ढाँचा;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release;
	vfd->lock = &dev->lock;
	snम_लिखो(vfd->name, माप(vfd->name), "%s (%s)",
		 cx23885_boards[dev->board].name, type);
	video_set_drvdata(vfd, dev);
	वापस vfd;
पूर्ण

पूर्णांक cx23885_flatiron_ग_लिखो(काष्ठा cx23885_dev *dev, u8 reg, u8 data)
अणु
	/* 8 bit रेजिस्टरs, 8 bit values */
	u8 buf[] = अणु reg, data पूर्ण;

	काष्ठा i2c_msg msg = अणु .addr = 0x98 >> 1,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;

	वापस i2c_transfer(&dev->i2c_bus[2].i2c_adap, &msg, 1);
पूर्ण

u8 cx23885_flatiron_पढ़ो(काष्ठा cx23885_dev *dev, u8 reg)
अणु
	/* 8 bit रेजिस्टरs, 8 bit values */
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = 0x98 >> 1, .flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .addr = 0x98 >> 1, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(&dev->i2c_bus[2].i2c_adap, &msg[0], 2);
	अगर (ret != 2)
		pr_err("%s() error\n", __func__);

	वापस b1[0];
पूर्ण

अटल व्योम cx23885_flatiron_dump(काष्ठा cx23885_dev *dev)
अणु
	पूर्णांक i;
	dprपूर्णांकk(1, "Flatiron dump\n");
	क्रम (i = 0; i < 0x24; i++) अणु
		dprपूर्णांकk(1, "FI[%02x] = %02x\n", i,
			cx23885_flatiron_पढ़ो(dev, i));
	पूर्ण
पूर्ण

अटल पूर्णांक cx23885_flatiron_mux(काष्ठा cx23885_dev *dev, पूर्णांक input)
अणु
	u8 val;
	dprपूर्णांकk(1, "%s(input = %d)\n", __func__, input);

	अगर (input == 1)
		val = cx23885_flatiron_पढ़ो(dev, CH_PWR_CTRL1) & ~FLD_CH_SEL;
	अन्यथा अगर (input == 2)
		val = cx23885_flatiron_पढ़ो(dev, CH_PWR_CTRL1) | FLD_CH_SEL;
	अन्यथा
		वापस -EINVAL;

	val |= 0x20; /* Enable घड़ी to delta-sigma and dec filter */

	cx23885_flatiron_ग_लिखो(dev, CH_PWR_CTRL1, val);

	/* Wake up */
	cx23885_flatiron_ग_लिखो(dev, CH_PWR_CTRL2, 0);

	अगर (video_debug)
		cx23885_flatiron_dump(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_video_mux(काष्ठा cx23885_dev *dev, अचिन्हित पूर्णांक input)
अणु
	dprपूर्णांकk(1, "%s() video_mux: %d [vmux=%d, gpio=0x%x,0x%x,0x%x,0x%x]\n",
		__func__,
		input, INPUT(input)->vmux,
		INPUT(input)->gpio0, INPUT(input)->gpio1,
		INPUT(input)->gpio2, INPUT(input)->gpio3);
	dev->input = input;

	अगर (dev->board == CX23885_BOARD_MYGICA_X8506 ||
		dev->board == CX23885_BOARD_MAGICPRO_PROHDTVE2 ||
		dev->board == CX23885_BOARD_MYGICA_X8507) अणु
		/* Select Analog TV */
		अगर (INPUT(input)->type == CX23885_VMUX_TELEVISION)
			cx23885_gpio_clear(dev, GPIO_0);
	पूर्ण

	/* Tell the पूर्णांकernal A/V decoder */
	v4l2_subdev_call(dev->sd_cx25840, video, s_routing,
			INPUT(input)->vmux, 0, 0);

	अगर ((dev->board == CX23885_BOARD_HAUPPAUGE_HVR1800) ||
		(dev->board == CX23885_BOARD_MPX885) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR1250) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_IMPACTVCBE) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR1255) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR1255_22111) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR1265_K4) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_DVB) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR1850) ||
		(dev->board == CX23885_BOARD_HAUPPAUGE_HVR5525) ||
		(dev->board == CX23885_BOARD_MYGICA_X8507) ||
		(dev->board == CX23885_BOARD_AVERMEDIA_HC81R) ||
		(dev->board == CX23885_BOARD_VIEWCAST_260E) ||
		(dev->board == CX23885_BOARD_VIEWCAST_460E) ||
		(dev->board == CX23885_BOARD_AVERMEDIA_CE310B)) अणु
		/* Configure audio routing */
		v4l2_subdev_call(dev->sd_cx25840, audio, s_routing,
			INPUT(input)->amux, 0, 0);

		अगर (INPUT(input)->amux == CX25840_AUDIO7)
			cx23885_flatiron_mux(dev, 1);
		अन्यथा अगर (INPUT(input)->amux == CX25840_AUDIO6)
			cx23885_flatiron_mux(dev, 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_audio_mux(काष्ठा cx23885_dev *dev, अचिन्हित पूर्णांक input)
अणु
	dprपूर्णांकk(1, "%s(input=%d)\n", __func__, input);

	/* The baseband video core of the cx23885 has two audio inमाला_दो.
	 * LR1 and LR2. In almost every single हाल so far only HVR1xxx
	 * cards we've only ever supported LR1. Time to support LR2,
	 * which is available via the optional white अवरोधout header on
	 * the board.
	 * We'll use a could of existing क्रमागतs in the card काष्ठा to allow
	 * devs to specअगरy which baseband input they need, or just शेष
	 * to what we've always used.
	 */
	अगर (INPUT(input)->amux == CX25840_AUDIO7)
		cx23885_flatiron_mux(dev, 1);
	अन्यथा अगर (INPUT(input)->amux == CX25840_AUDIO6)
		cx23885_flatiron_mux(dev, 2);
	अन्यथा अणु
		/* Not specअगरically defined, assume the शेष. */
		cx23885_flatiron_mux(dev, 1);
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
अटल पूर्णांक cx23885_start_video_dma(काष्ठा cx23885_dev *dev,
			   काष्ठा cx23885_dmaqueue *q,
			   काष्ठा cx23885_buffer *buf)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Stop the dma/fअगरo beक्रमe we tamper with it's risc programs */
	cx_clear(VID_A_DMA_CTL, 0x11);

	/* setup fअगरo + क्रमmat */
	cx23885_sram_channel_setup(dev, &dev->sram_channels[SRAM_CH01],
				buf->bpl, buf->risc.dma);

	/* reset counter */
	cx_ग_लिखो(VID_A_GPCNT_CTL, 3);
	q->count = 0;

	/* enable irq */
	cx23885_irq_add_enable(dev, 0x01);
	cx_set(VID_A_INT_MSK, 0x000011);

	/* start dma */
	cx_set(DEV_CNTRL2, (1<<5));
	cx_set(VID_A_DMA_CTL, 0x11); /* FIFO and RISC enable */

	वापस 0;
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;

	*num_planes = 1;
	sizes[0] = (dev->fmt->depth * dev->width * dev->height) >> 3;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf =
		container_of(vbuf, काष्ठा cx23885_buffer, vb);
	u32 line0_offset, line1_offset;
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);
	पूर्णांक field_tff;

	buf->bpl = (dev->width * dev->fmt->depth) >> 3;

	अगर (vb2_plane_size(vb, 0) < dev->height * buf->bpl)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, dev->height * buf->bpl);

	चयन (dev->field) अणु
	हाल V4L2_FIELD_TOP:
		cx23885_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, 0, UNSET,
				buf->bpl, 0, dev->height);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		cx23885_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, UNSET, 0,
				buf->bpl, 0, dev->height);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		अगर (dev->tvnorm & V4L2_STD_525_60)
			/* NTSC or  */
			field_tff = 1;
		अन्यथा
			field_tff = 0;

		अगर (cx23885_boards[dev->board].क्रमce_bff)
			/* PAL / SECAM OR 888 in NTSC MODE */
			field_tff = 0;

		अगर (field_tff) अणु
			/* cx25840 transmits NTSC bottom field first */
			dprपूर्णांकk(1, "%s() Creating TFF/NTSC risc\n",
					__func__);
			line0_offset = buf->bpl;
			line1_offset = 0;
		पूर्ण अन्यथा अणु
			/* All other क्रमmats are top field first */
			dprपूर्णांकk(1, "%s() Creating BFF/PAL/SECAM risc\n",
					__func__);
			line0_offset = 0;
			line1_offset = buf->bpl;
		पूर्ण
		cx23885_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl, line0_offset,
				line1_offset,
				buf->bpl, buf->bpl,
				dev->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		cx23885_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl,
				0, buf->bpl * (dev->height >> 1),
				buf->bpl, 0,
				dev->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_BT:
		cx23885_risc_buffer(dev->pci, &buf->risc,
				sgt->sgl,
				buf->bpl * (dev->height >> 1), 0,
				buf->bpl, 0,
				dev->height >> 1);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	dprपूर्णांकk(2, "[%p/%d] buffer_init - %dx%d %dbpp 0x%08x - dma=0x%08lx\n",
		buf, buf->vb.vb2_buf.index,
		dev->width, dev->height, dev->fmt->depth, dev->fmt->fourcc,
		(अचिन्हित दीर्घ)buf->risc.dma);
	वापस 0;
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_मुक्त_buffer(vb->vb2_queue->drv_priv, buf);
पूर्ण

/*
 * The risc program क्रम each buffer works as follows: it starts with a simple
 * 'JUMP to addr + 12', which is effectively a NOP. Then the code to DMA the
 * buffer follows and at the end we have a JUMP back to the start + 12 (skipping
 * the initial JUMP).
 *
 * This is the risc program of the first buffer to be queued अगर the active list
 * is empty and it just keeps DMAing this buffer without generating any
 * पूर्णांकerrupts.
 *
 * If a new buffer is added then the initial JUMP in the code क्रम that buffer
 * will generate an पूर्णांकerrupt which संकेतs that the previous buffer has been
 * DMAed successfully and that it can be वापसed to userspace.
 *
 * It also sets the final jump of the previous buffer to the start of the new
 * buffer, thus chaining the new buffer पूर्णांकo the DMA chain. This is a single
 * atomic u32 ग_लिखो, so there is no race condition.
 *
 * The end-result of all this that you only get an पूर्णांकerrupt when a buffer
 * is पढ़ोy, so the control flow is very easy.
 */
अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer   *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);
	काष्ठा cx23885_buffer   *prev;
	काष्ठा cx23885_dmaqueue *q    = &dev->vidq;
	अचिन्हित दीर्घ flags;

	/* add jump to start */
	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 12);
	buf->risc.jmp[2] = cpu_to_le32(0); /* bits 63-32 */

	spin_lock_irqsave(&dev->slock, flags);
	अगर (list_empty(&q->active)) अणु
		list_add_tail(&buf->queue, &q->active);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - first active\n",
			buf, buf->vb.vb2_buf.index);
	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, काष्ठा cx23885_buffer,
			queue);
		list_add_tail(&buf->queue, &q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to active\n",
				buf, buf->vb.vb2_buf.index);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल पूर्णांक cx23885_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &dev->vidq;
	काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

	cx23885_start_video_dma(dev, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम cx23885_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &dev->vidq;
	अचिन्हित दीर्घ flags;

	cx_clear(VID_A_DMA_CTL, 0x11);
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cx23885_video_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = cx23885_start_streaming,
	.stop_streaming = cx23885_stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */
/* VIDEO IOCTLS                                                       */

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	f->fmt.pix.width        = dev->width;
	f->fmt.pix.height       = dev->height;
	f->fmt.pix.field        = dev->field;
	f->fmt.pix.pixelक्रमmat  = dev->fmt->fourcc;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * dev->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	काष्ठा cx23885_fmt *fmt;
	क्रमागत v4l2_field   field;
	अचिन्हित पूर्णांक      maxw, maxh;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	field = f->fmt.pix.field;
	maxw  = 720;
	maxh  = norm_maxh(dev->tvnorm);

	अगर (V4L2_FIELD_ANY == field) अणु
		field = (f->fmt.pix.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
	पूर्ण

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		अवरोध;
	शेष:
		field = V4L2_FIELD_INTERLACED;
		अवरोध;
	पूर्ण

	f->fmt.pix.field = field;
	v4l_bound_align_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक err;

	dprपूर्णांकk(2, "%s()\n", __func__);
	err = vidioc_try_fmt_vid_cap(file, priv, f);

	अगर (0 != err)
		वापस err;

	अगर (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq) ||
	    vb2_is_busy(&dev->vb2_mpegq))
		वापस -EBUSY;

	dev->fmt        = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	dev->width      = f->fmt.pix.width;
	dev->height     = f->fmt.pix.height;
	dev->field	= f->fmt.pix.field;
	dprपूर्णांकk(2, "%s() width=%d height=%d field=%d\n", __func__,
		dev->width, dev->height, dev->field);
	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	call_all(dev, pad, set_fmt, शून्य, &क्रमmat);
	v4l2_fill_pix_क्रमmat(&f->fmt.pix, &क्रमmat.क्रमmat);
	/* set_fmt overग_लिखोs f->fmt.pix.field, restore it */
	f->fmt.pix.field = dev->field;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	strscpy(cap->driver, "cx23885", माप(cap->driver));
	strscpy(cap->card, cx23885_boards[dev->board].name,
		माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_AUDIO | V4L2_CAP_VBI_CAPTURE |
			    V4L2_CAP_VIDEO_CAPTURE |
			    V4L2_CAP_DEVICE_CAPS;
	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		cap->capabilities |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			cap->capabilities |= V4L2_CAP_TUNER;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (unlikely(f->index >= ARRAY_SIZE(क्रमmats)))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	bool is_50hz = dev->tvnorm & V4L2_STD_625_50;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f->numerator = is_50hz ? 54 : 11;
	f->denominator = is_50hz ? 59 : 10;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = 0;
		sel->r.left = 0;
		sel->r.width = 720;
		sel->r.height = norm_maxh(dev->tvnorm);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	dprपूर्णांकk(1, "%s()\n", __func__);

	*id = dev->tvnorm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id tvnorms)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	dprपूर्णांकk(1, "%s()\n", __func__);

	वापस cx23885_set_tvnorm(dev, tvnorms);
पूर्ण

पूर्णांक cx23885_क्रमागत_input(काष्ठा cx23885_dev *dev, काष्ठा v4l2_input *i)
अणु
	अटल स्थिर अक्षर *iname[] = अणु
		[CX23885_VMUX_COMPOSITE1] = "Composite1",
		[CX23885_VMUX_COMPOSITE2] = "Composite2",
		[CX23885_VMUX_COMPOSITE3] = "Composite3",
		[CX23885_VMUX_COMPOSITE4] = "Composite4",
		[CX23885_VMUX_SVIDEO]     = "S-Video",
		[CX23885_VMUX_COMPONENT]  = "Component",
		[CX23885_VMUX_TELEVISION] = "Television",
		[CX23885_VMUX_CABLE]      = "Cable TV",
		[CX23885_VMUX_DVB]        = "DVB",
		[CX23885_VMUX_DEBUG]      = "for debug only",
	पूर्ण;
	अचिन्हित पूर्णांक n;
	dprपूर्णांकk(1, "%s()\n", __func__);

	n = i->index;
	अगर (n >= MAX_CX23885_INPUT)
		वापस -EINVAL;

	अगर (0 == INPUT(n)->type)
		वापस -EINVAL;

	i->index = n;
	i->type  = V4L2_INPUT_TYPE_CAMERA;
	strscpy(i->name, iname[INPUT(n)->type], माप(i->name));
	i->std = CX23885_NORMS;
	अगर ((CX23885_VMUX_TELEVISION == INPUT(n)->type) ||
		(CX23885_VMUX_CABLE == INPUT(n)->type)) अणु
		i->type = V4L2_INPUT_TYPE_TUNER;
		i->audioset = 4;
	पूर्ण अन्यथा अणु
		/* Two selectable audio inमाला_दो क्रम non-tv inमाला_दो */
		i->audioset = 3;
	पूर्ण

	अगर (dev->input == n) अणु
		/* क्रमागत'd input matches our configured input.
		 * Ask the video decoder to process the call
		 * and give it an oppertunity to update the
		 * status field.
		 */
		call_all(dev, video, g_input_status, &i->status);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	dprपूर्णांकk(1, "%s()\n", __func__);
	वापस cx23885_क्रमागत_input(dev, i);
पूर्ण

पूर्णांक cx23885_get_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	*i = dev->input;
	dprपूर्णांकk(1, "%s() returns %d\n", __func__, *i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	वापस cx23885_get_input(file, priv, i);
पूर्ण

पूर्णांक cx23885_set_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	dprपूर्णांकk(1, "%s(%d)\n", __func__, i);

	अगर (i >= MAX_CX23885_INPUT) अणु
		dprपूर्णांकk(1, "%s() -EINVAL\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (INPUT(i)->type == 0)
		वापस -EINVAL;

	cx23885_video_mux(dev, i);

	/* By शेष establish the शेष audio input क्रम the card also */
	/* Caller is मुक्त to use VIDIOC_S_AUDIO to override afterwards */
	cx23885_audio_mux(dev, i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस cx23885_set_input(file, priv, i);
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	call_all(dev, core, log_status);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_query_audinput(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_audio *i)
अणु
	अटल स्थिर अक्षर *iname[] = अणु
		[0] = "Baseband L/R 1",
		[1] = "Baseband L/R 2",
		[2] = "TV",
	पूर्ण;
	अचिन्हित पूर्णांक n;
	dprपूर्णांकk(1, "%s()\n", __func__);

	n = i->index;
	अगर (n >= 3)
		वापस -EINVAL;

	स_रखो(i, 0, माप(*i));
	i->index = n;
	strscpy(i->name, iname[n], माप(i->name));
	i->capability = V4L2_AUDCAP_STEREO;
	वापस 0;

पूर्ण

अटल पूर्णांक vidioc_क्रमागत_audinput(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_audio *i)
अणु
	वापस cx23885_query_audinput(file, priv, i);
पूर्ण

अटल पूर्णांक vidioc_g_audinput(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_audio *i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर ((CX23885_VMUX_TELEVISION == INPUT(dev->input)->type) ||
		(CX23885_VMUX_CABLE == INPUT(dev->input)->type))
		i->index = 2;
	अन्यथा
		i->index = dev->audinput;
	dprपूर्णांकk(1, "%s(input=%d)\n", __func__, i->index);

	वापस cx23885_query_audinput(file, priv, i);
पूर्ण

अटल पूर्णांक vidioc_s_audinput(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_audio *i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर ((CX23885_VMUX_TELEVISION == INPUT(dev->input)->type) ||
		(CX23885_VMUX_CABLE == INPUT(dev->input)->type)) अणु
		वापस i->index != 2 ? -EINVAL : 0;
	पूर्ण
	अगर (i->index > 1)
		वापस -EINVAL;

	dprपूर्णांकk(1, "%s(%d)\n", __func__, i->index);

	dev->audinput = i->index;

	/* Skip the audio शेषs from the cards काष्ठा, caller wants
	 * directly touch the audio mux hardware. */
	cx23885_flatiron_mux(dev, dev->audinput + 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		अवरोध;
	शेष:
		अगर (dev->tuner_type == TUNER_ABSENT)
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	अगर (0 != t->index)
		वापस -EINVAL;

	strscpy(t->name, "Television", माप(t->name));

	call_all(dev, tuner, g_tuner, t);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		अवरोध;
	शेष:
		अगर (dev->tuner_type == TUNER_ABSENT)
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	अगर (0 != t->index)
		वापस -EINVAL;
	/* Update the A/V core */
	call_all(dev, tuner, s_tuner, t);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		अवरोध;
	शेष:
		अगर (dev->tuner_type == TUNER_ABSENT)
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	f->type = V4L2_TUNER_ANALOG_TV;
	f->frequency = dev->freq;

	call_all(dev, tuner, g_frequency, f);

	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_set_freq(काष्ठा cx23885_dev *dev, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा v4l2_ctrl *mute;
	पूर्णांक old_mute_val = 1;

	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		अवरोध;
	शेष:
		अगर (dev->tuner_type == TUNER_ABSENT)
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	अगर (unlikely(f->tuner != 0))
		वापस -EINVAL;

	dev->freq = f->frequency;

	/* I need to mute audio here */
	mute = v4l2_ctrl_find(&dev->ctrl_handler, V4L2_CID_AUDIO_MUTE);
	अगर (mute) अणु
		old_mute_val = v4l2_ctrl_g_ctrl(mute);
		अगर (!old_mute_val)
			v4l2_ctrl_s_ctrl(mute, 1);
	पूर्ण

	call_all(dev, tuner, s_frequency, f);

	/* When changing channels it is required to reset TVAUDIO */
	msleep(100);

	/* I need to unmute audio here */
	अगर (old_mute_val == 0)
		v4l2_ctrl_s_ctrl(mute, old_mute_val);

	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_set_freq_via_ops(काष्ठा cx23885_dev *dev,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा v4l2_ctrl *mute;
	पूर्णांक old_mute_val = 1;
	काष्ठा vb2_dvb_frontend *vfe;
	काष्ठा dvb_frontend *fe;

	काष्ठा analog_parameters params = अणु
		.mode      = V4L2_TUNER_ANALOG_TV,
		.audmode   = V4L2_TUNER_MODE_STEREO,
		.std       = dev->tvnorm,
		.frequency = f->frequency
	पूर्ण;

	dev->freq = f->frequency;

	/* I need to mute audio here */
	mute = v4l2_ctrl_find(&dev->ctrl_handler, V4L2_CID_AUDIO_MUTE);
	अगर (mute) अणु
		old_mute_val = v4l2_ctrl_g_ctrl(mute);
		अगर (!old_mute_val)
			v4l2_ctrl_s_ctrl(mute, 1);
	पूर्ण

	/* If HVR1850 */
	dprपूर्णांकk(1, "%s() frequency=%d tuner=%d std=0x%llx\n", __func__,
		params.frequency, f->tuner, params.std);

	vfe = vb2_dvb_get_frontend(&dev->ts2.frontends, 1);
	अगर (!vfe) अणु
		वापस -EINVAL;
	पूर्ण

	fe = vfe->dvb.frontend;

	अगर ((dev->board == CX23885_BOARD_HAUPPAUGE_HVR1850) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_HVR1255) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_HVR1255_22111) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_HVR1265_K4) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_HVR5525) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_DVB) ||
	    (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC))
		fe = &dev->ts1.analog_fe;

	अगर (fe && fe->ops.tuner_ops.set_analog_params) अणु
		call_all(dev, video, s_std, dev->tvnorm);
		fe->ops.tuner_ops.set_analog_params(fe, &params);
	पूर्ण
	अन्यथा
		pr_err("%s() No analog tuner, aborting\n", __func__);

	/* When changing channels it is required to reset TVAUDIO */
	msleep(100);

	/* I need to unmute audio here */
	अगर (old_mute_val == 0)
		v4l2_ctrl_s_ctrl(mute, old_mute_val);

	वापस 0;
पूर्ण

पूर्णांक cx23885_set_frequency(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		ret = cx23885_set_freq_via_ops(dev, f);
		अवरोध;
	शेष:
		ret = cx23885_set_freq(dev, f);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	वापस cx23885_set_frequency(file, priv, f);
पूर्ण

/* ----------------------------------------------------------- */

पूर्णांक cx23885_video_irq(काष्ठा cx23885_dev *dev, u32 status)
अणु
	u32 mask, count;
	पूर्णांक handled = 0;

	mask   = cx_पढ़ो(VID_A_INT_MSK);
	अगर (0 == (status & mask))
		वापस handled;

	cx_ग_लिखो(VID_A_INT_STAT, status);

	/* risc op code error, fअगरo overflow or line sync detection error */
	अगर ((status & VID_BC_MSK_OPC_ERR) ||
		(status & VID_BC_MSK_SYNC) ||
		(status & VID_BC_MSK_OF)) अणु

		अगर (status & VID_BC_MSK_OPC_ERR) अणु
			dprपूर्णांकk(7, " (VID_BC_MSK_OPC_ERR 0x%08x)\n",
				VID_BC_MSK_OPC_ERR);
			pr_warn("%s: video risc op code error\n",
				dev->name);
			cx23885_sram_channel_dump(dev,
				&dev->sram_channels[SRAM_CH01]);
		पूर्ण

		अगर (status & VID_BC_MSK_SYNC)
			dprपूर्णांकk(7, " (VID_BC_MSK_SYNC 0x%08x) video lines miss-match\n",
				VID_BC_MSK_SYNC);

		अगर (status & VID_BC_MSK_OF)
			dprपूर्णांकk(7, " (VID_BC_MSK_OF 0x%08x) fifo overflow\n",
				VID_BC_MSK_OF);

	पूर्ण

	/* Video */
	अगर (status & VID_BC_MSK_RISCI1) अणु
		spin_lock(&dev->slock);
		count = cx_पढ़ो(VID_A_GPCNT);
		cx23885_video_wakeup(dev, &dev->vidq, count);
		spin_unlock(&dev->slock);
		handled++;
	पूर्ण

	/* Allow the VBI framework to process it's payload */
	handled += cx23885_vbi_irq(dev, status);

	वापस handled;
पूर्ण

/* ----------------------------------------------------------- */
/* exported stuff                                              */

अटल स्थिर काष्ठा v4l2_file_operations video_fops = अणु
	.owner	       = THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = vb2_fop_release,
	.पढ़ो           = vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap     = cx23885_vbi_fmt,
	.vidioc_try_fmt_vbi_cap   = cx23885_vbi_fmt,
	.vidioc_s_fmt_vbi_cap     = cx23885_vbi_fmt,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_g_pixelaspect = vidioc_g_pixelaspect,
	.vidioc_g_selection   = vidioc_g_selection,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_log_status    = vidioc_log_status,
	.vidioc_g_tuner       = vidioc_g_tuner,
	.vidioc_s_tuner       = vidioc_s_tuner,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_s_frequency   = vidioc_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info   = cx23885_g_chip_info,
	.vidioc_g_रेजिस्टर    = cx23885_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर    = cx23885_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_क्रमागतaudio     = vidioc_क्रमागत_audinput,
	.vidioc_g_audio       = vidioc_g_audinput,
	.vidioc_s_audio       = vidioc_s_audinput,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device cx23885_vbi_ढाँचा;
अटल काष्ठा video_device cx23885_video_ढाँचा = अणु
	.name                 = "cx23885-video",
	.fops                 = &video_fops,
	.ioctl_ops	      = &video_ioctl_ops,
	.tvnorms              = CX23885_NORMS,
पूर्ण;

व्योम cx23885_video_unरेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	cx23885_irq_हटाओ(dev, 0x01);

	अगर (dev->vbi_dev) अणु
		अगर (video_is_रेजिस्टरed(dev->vbi_dev))
			video_unरेजिस्टर_device(dev->vbi_dev);
		अन्यथा
			video_device_release(dev->vbi_dev);
		dev->vbi_dev = शून्य;
	पूर्ण
	अगर (dev->video_dev) अणु
		अगर (video_is_रेजिस्टरed(dev->video_dev))
			video_unरेजिस्टर_device(dev->video_dev);
		अन्यथा
			video_device_release(dev->video_dev);
		dev->video_dev = शून्य;
	पूर्ण

	अगर (dev->audio_dev)
		cx23885_audio_unरेजिस्टर(dev);
पूर्ण

पूर्णांक cx23885_video_रेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा vb2_queue *q;
	पूर्णांक err;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Initialize VBI ढाँचा */
	cx23885_vbi_ढाँचा = cx23885_video_ढाँचा;
	strscpy(cx23885_vbi_ढाँचा.name, "cx23885-vbi",
		माप(cx23885_vbi_ढाँचा.name));

	dev->tvnorm = V4L2_STD_NTSC_M;
	dev->fmt = क्रमmat_by_fourcc(V4L2_PIX_FMT_YUYV);
	dev->field = V4L2_FIELD_INTERLACED;
	dev->width = 720;
	dev->height = norm_maxh(dev->tvnorm);

	/* init video dma queues */
	INIT_LIST_HEAD(&dev->vidq.active);

	/* init vbi dma queues */
	INIT_LIST_HEAD(&dev->vbiq.active);

	cx23885_irq_add_enable(dev, 0x01);

	अगर ((TUNER_ABSENT != dev->tuner_type) &&
			((dev->tuner_bus == 0) || (dev->tuner_bus == 1))) अणु
		काष्ठा v4l2_subdev *sd = शून्य;

		अगर (dev->tuner_addr)
			sd = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[dev->tuner_bus].i2c_adap,
				"tuner", dev->tuner_addr, शून्य);
		अन्यथा
			sd = v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_bus[dev->tuner_bus].i2c_adap,
				"tuner", 0, v4l2_i2c_tuner_addrs(ADDRS_TV));
		अगर (sd) अणु
			काष्ठा tuner_setup tun_setup;

			स_रखो(&tun_setup, 0, माप(tun_setup));
			tun_setup.mode_mask = T_ANALOG_TV;
			tun_setup.type = dev->tuner_type;
			tun_setup.addr = v4l2_i2c_subdev_addr(sd);
			tun_setup.tuner_callback = cx23885_tuner_callback;

			v4l2_subdev_call(sd, tuner, s_type_addr, &tun_setup);

			अगर ((dev->board == CX23885_BOARD_LEADTEK_WINFAST_PXTV1200) ||
			    (dev->board == CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200)) अणु
				काष्ठा xc2028_ctrl ctrl = अणु
					.fname = XC2028_DEFAULT_FIRMWARE,
					.max_len = 64
				पूर्ण;
				काष्ठा v4l2_priv_tun_config cfg = अणु
					.tuner = dev->tuner_type,
					.priv = &ctrl
				पूर्ण;
				v4l2_subdev_call(sd, tuner, s_config, &cfg);
			पूर्ण

			अगर (dev->board == CX23885_BOARD_AVERMEDIA_HC81R) अणु
				काष्ठा xc2028_ctrl ctrl = अणु
					.fname = "xc3028L-v36.fw",
					.max_len = 64
				पूर्ण;
				काष्ठा v4l2_priv_tun_config cfg = अणु
					.tuner = dev->tuner_type,
					.priv = &ctrl
				पूर्ण;
				v4l2_subdev_call(sd, tuner, s_config, &cfg);
			पूर्ण
		पूर्ण
	पूर्ण

	/* initial device configuration */
	mutex_lock(&dev->lock);
	cx23885_set_tvnorm(dev, dev->tvnorm);
	cx23885_video_mux(dev, 0);
	cx23885_audio_mux(dev, 0);
	mutex_unlock(&dev->lock);

	q = &dev->vb2_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->gfp_flags = GFP_DMA32;
	q->min_buffers_needed = 2;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx23885_buffer);
	q->ops = &cx23885_video_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;

	err = vb2_queue_init(q);
	अगर (err < 0)
		जाओ fail_unreg;

	q = &dev->vb2_vbiq;
	q->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->gfp_flags = GFP_DMA32;
	q->min_buffers_needed = 2;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx23885_buffer);
	q->ops = &cx23885_vbi_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;

	err = vb2_queue_init(q);
	अगर (err < 0)
		जाओ fail_unreg;

	/* रेजिस्टर Video device */
	dev->video_dev = cx23885_vdev_init(dev, dev->pci,
		&cx23885_video_ढाँचा, "video");
	dev->video_dev->queue = &dev->vb2_vidq;
	dev->video_dev->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				      V4L2_CAP_AUDIO | V4L2_CAP_VIDEO_CAPTURE;
	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		dev->video_dev->device_caps |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			dev->video_dev->device_caps |= V4L2_CAP_TUNER;
	पूर्ण

	err = video_रेजिस्टर_device(dev->video_dev, VFL_TYPE_VIDEO,
				    video_nr[dev->nr]);
	अगर (err < 0) अणु
		pr_info("%s: can't register video device\n",
			dev->name);
		जाओ fail_unreg;
	पूर्ण
	pr_info("%s: registered device %s [v4l2]\n",
	       dev->name, video_device_node_name(dev->video_dev));

	/* रेजिस्टर VBI device */
	dev->vbi_dev = cx23885_vdev_init(dev, dev->pci,
		&cx23885_vbi_ढाँचा, "vbi");
	dev->vbi_dev->queue = &dev->vb2_vbiq;
	dev->vbi_dev->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				    V4L2_CAP_AUDIO | V4L2_CAP_VBI_CAPTURE;
	चयन (dev->board) अणु /* i2c device tuners */
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
		dev->vbi_dev->device_caps |= V4L2_CAP_TUNER;
		अवरोध;
	शेष:
		अगर (dev->tuner_type != TUNER_ABSENT)
			dev->vbi_dev->device_caps |= V4L2_CAP_TUNER;
	पूर्ण
	err = video_रेजिस्टर_device(dev->vbi_dev, VFL_TYPE_VBI,
				    vbi_nr[dev->nr]);
	अगर (err < 0) अणु
		pr_info("%s: can't register vbi device\n",
			dev->name);
		जाओ fail_unreg;
	पूर्ण
	pr_info("%s: registered device %s\n",
	       dev->name, video_device_node_name(dev->vbi_dev));

	/* Register ALSA audio device */
	dev->audio_dev = cx23885_audio_रेजिस्टर(dev);

	वापस 0;

fail_unreg:
	cx23885_video_unरेजिस्टर(dev);
	वापस err;
पूर्ण
