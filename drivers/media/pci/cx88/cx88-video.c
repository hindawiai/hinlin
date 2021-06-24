<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम Conexant 2388x based TV cards
 * video4linux video पूर्णांकerface
 *
 * (c) 2003-04 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 *
 * (c) 2005-2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 *	- Multituner support
 *	- video_ioctl2 conversion
 *	- PAL/M fixes
 */

#समावेश "cx88.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/i2c/wm8775.h>

MODULE_DESCRIPTION("v4l2 driver module for cx2388x based TV cards");
MODULE_AUTHOR("Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(CX88_VERSION);

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक vbi_nr[]   = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;
अटल अचिन्हित पूर्णांक radio_nr[] = अणु[0 ... (CX88_MAXBOARDS - 1)] = UNSET पूर्ण;

module_param_array(video_nr, पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr,   पूर्णांक, शून्य, 0444);
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(video_nr, "video device numbers");
MODULE_PARM_DESC(vbi_nr, "vbi device numbers");
MODULE_PARM_DESC(radio_nr, "radio device numbers");

अटल अचिन्हित पूर्णांक video_debug;
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug, "enable debug messages [video]");

अटल अचिन्हित पूर्णांक irq_debug;
module_param(irq_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(irq_debug, "enable debug messages [IRQ handler]");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु			\
	अगर (video_debug >= level)				\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: video:" fmt),	\
			__func__, ##arg);			\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------- */
/* अटल data                                                         */

अटल स्थिर काष्ठा cx8800_fmt क्रमmats[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_GREY,
		.cxक्रमmat = ColorFormatY8,
		.depth    = 8,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB555,
		.cxक्रमmat = ColorFormatRGB15,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB555X,
		.cxक्रमmat = ColorFormatRGB15 | ColorFormatBSWAP,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB565,
		.cxक्रमmat = ColorFormatRGB16,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB565X,
		.cxक्रमmat = ColorFormatRGB16 | ColorFormatBSWAP,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_BGR24,
		.cxक्रमmat = ColorFormatRGB24,
		.depth    = 24,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_BGR32,
		.cxक्रमmat = ColorFormatRGB32,
		.depth    = 32,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB32,
		.cxक्रमmat = ColorFormatRGB32 | ColorFormatBSWAP |
			    ColorFormatWSWAP,
		.depth    = 32,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.cxक्रमmat = ColorFormatYUY2,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.cxक्रमmat = ColorFormatYUY2 | ColorFormatBSWAP,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cx8800_fmt *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats + i;
	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------- */

काष्ठा cx88_ctrl अणु
	/* control inक्रमmation */
	u32 id;
	s32 minimum;
	s32 maximum;
	u32 step;
	s32 शेष_value;

	/* control रेजिस्टर inक्रमmation */
	u32 off;
	u32 reg;
	u32 sreg;
	u32 mask;
	u32 shअगरt;
पूर्ण;

अटल स्थिर काष्ठा cx88_ctrl cx8800_vid_ctls[] = अणु
	/* --- video --- */
	अणु
		.id            = V4L2_CID_BRIGHTNESS,
		.minimum       = 0x00,
		.maximum       = 0xff,
		.step          = 1,
		.शेष_value = 0x7f,
		.off           = 128,
		.reg           = MO_CONTR_BRIGHT,
		.mask          = 0x00ff,
		.shअगरt         = 0,
	पूर्ण, अणु
		.id            = V4L2_CID_CONTRAST,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.शेष_value = 0x3f,
		.off           = 0,
		.reg           = MO_CONTR_BRIGHT,
		.mask          = 0xff00,
		.shअगरt         = 8,
	पूर्ण, अणु
		.id            = V4L2_CID_HUE,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.शेष_value = 0x7f,
		.off           = 128,
		.reg           = MO_HUE,
		.mask          = 0x00ff,
		.shअगरt         = 0,
	पूर्ण, अणु
		/* strictly, this only describes only U saturation.
		 * V saturation is handled specially through code.
		 */
		.id            = V4L2_CID_SATURATION,
		.minimum       = 0,
		.maximum       = 0xff,
		.step          = 1,
		.शेष_value = 0x7f,
		.off           = 0,
		.reg           = MO_UV_SATURATION,
		.mask          = 0x00ff,
		.shअगरt         = 0,
	पूर्ण, अणु
		.id            = V4L2_CID_SHARPNESS,
		.minimum       = 0,
		.maximum       = 4,
		.step          = 1,
		.शेष_value = 0x0,
		.off           = 0,
		/*
		 * NOTE: the value is converted and written to both even
		 * and odd रेजिस्टरs in the code
		 */
		.reg           = MO_FILTER_ODD,
		.mask          = 7 << 7,
		.shअगरt         = 7,
	पूर्ण, अणु
		.id            = V4L2_CID_CHROMA_AGC,
		.minimum       = 0,
		.maximum       = 1,
		.शेष_value = 0x1,
		.reg           = MO_INPUT_FORMAT,
		.mask          = 1 << 10,
		.shअगरt         = 10,
	पूर्ण, अणु
		.id            = V4L2_CID_COLOR_KILLER,
		.minimum       = 0,
		.maximum       = 1,
		.शेष_value = 0x1,
		.reg           = MO_INPUT_FORMAT,
		.mask          = 1 << 9,
		.shअगरt         = 9,
	पूर्ण, अणु
		.id            = V4L2_CID_BAND_STOP_FILTER,
		.minimum       = 0,
		.maximum       = 1,
		.step          = 1,
		.शेष_value = 0x0,
		.off           = 0,
		.reg           = MO_HTOTAL,
		.mask          = 3 << 11,
		.shअगरt         = 11,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cx88_ctrl cx8800_aud_ctls[] = अणु
	अणु
		/* --- audio --- */
		.id            = V4L2_CID_AUDIO_MUTE,
		.minimum       = 0,
		.maximum       = 1,
		.शेष_value = 1,
		.reg           = AUD_VOL_CTL,
		.sreg          = SHADOW_AUD_VOL_CTL,
		.mask          = (1 << 6),
		.shअगरt         = 6,
	पूर्ण, अणु
		.id            = V4L2_CID_AUDIO_VOLUME,
		.minimum       = 0,
		.maximum       = 0x3f,
		.step          = 1,
		.शेष_value = 0x3f,
		.reg           = AUD_VOL_CTL,
		.sreg          = SHADOW_AUD_VOL_CTL,
		.mask          = 0x3f,
		.shअगरt         = 0,
	पूर्ण, अणु
		.id            = V4L2_CID_AUDIO_BALANCE,
		.minimum       = 0,
		.maximum       = 0x7f,
		.step          = 1,
		.शेष_value = 0x40,
		.reg           = AUD_BAL_CTL,
		.sreg          = SHADOW_AUD_BAL_CTL,
		.mask          = 0x7f,
		.shअगरt         = 0,
	पूर्ण
पूर्ण;

क्रमागत अणु
	CX8800_VID_CTLS = ARRAY_SIZE(cx8800_vid_ctls),
	CX8800_AUD_CTLS = ARRAY_SIZE(cx8800_aud_ctls),
पूर्ण;

/* ------------------------------------------------------------------ */

पूर्णांक cx88_video_mux(काष्ठा cx88_core *core, अचिन्हित पूर्णांक input)
अणु
	/* काष्ठा cx88_core *core = dev->core; */

	dprपूर्णांकk(1, "video_mux: %d [vmux=%d,gpio=0x%x,0x%x,0x%x,0x%x]\n",
		input, INPUT(input).vmux,
		INPUT(input).gpio0, INPUT(input).gpio1,
		INPUT(input).gpio2, INPUT(input).gpio3);
	core->input = input;
	cx_anकरोr(MO_INPUT_FORMAT, 0x03 << 14, INPUT(input).vmux << 14);
	cx_ग_लिखो(MO_GP3_IO, INPUT(input).gpio3);
	cx_ग_लिखो(MO_GP0_IO, INPUT(input).gpio0);
	cx_ग_लिखो(MO_GP1_IO, INPUT(input).gpio1);
	cx_ग_लिखो(MO_GP2_IO, INPUT(input).gpio2);

	चयन (INPUT(input).type) अणु
	हाल CX88_VMUX_SVIDEO:
		cx_set(MO_AFECFG_IO,    0x00000001);
		cx_set(MO_INPUT_FORMAT, 0x00010010);
		cx_set(MO_FILTER_EVEN,  0x00002020);
		cx_set(MO_FILTER_ODD,   0x00002020);
		अवरोध;
	शेष:
		cx_clear(MO_AFECFG_IO,    0x00000001);
		cx_clear(MO_INPUT_FORMAT, 0x00010010);
		cx_clear(MO_FILTER_EVEN,  0x00002020);
		cx_clear(MO_FILTER_ODD,   0x00002020);
		अवरोध;
	पूर्ण

	/*
	 * अगर there are audioroutes defined, we have an बाह्यal
	 * ADC to deal with audio
	 */
	अगर (INPUT(input).audioroute) अणु
		/*
		 * The wm8775 module has the "2" route hardwired पूर्णांकo
		 * the initialization. Some boards may use dअगरferent
		 * routes क्रम dअगरferent inमाला_दो. HVR-1300 surely करोes
		 */
		अगर (core->sd_wm8775) अणु
			call_all(core, audio, s_routing,
				 INPUT(input).audioroute, 0, 0);
		पूर्ण
		/*
		 * cx2388's C-ADC is connected to the tuner only.
		 * When used with S-Video, that ADC is busy dealing with
		 * chroma, so an बाह्यal must be used क्रम baseband audio
		 */
		अगर (INPUT(input).type != CX88_VMUX_TELEVISION &&
		    INPUT(input).type != CX88_VMUX_CABLE) अणु
			/* "I2S ADC mode" */
			core->tvaudio = WW_I2SADC;
			cx88_set_tvaudio(core);
		पूर्ण अन्यथा अणु
			/* Normal mode */
			cx_ग_लिखो(AUD_I2SCNTL, 0x0);
			cx_clear(AUD_CTL, EN_I2SIN_ENABLE);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_video_mux);

/* ------------------------------------------------------------------ */

अटल पूर्णांक start_video_dma(काष्ठा cx8800_dev    *dev,
			   काष्ठा cx88_dmaqueue *q,
			   काष्ठा cx88_buffer   *buf)
अणु
	काष्ठा cx88_core *core = dev->core;

	/* setup fअगरo + क्रमmat */
	cx88_sram_channel_setup(core, &cx88_sram_channels[SRAM_CH21],
				buf->bpl, buf->risc.dma);
	cx88_set_scale(core, core->width, core->height, core->field);
	cx_ग_लिखो(MO_COLOR_CTRL, dev->fmt->cxक्रमmat | ColorFormatGamma);

	/* reset counter */
	cx_ग_लिखो(MO_VIDY_GPCNTRL, GP_COUNT_CONTROL_RESET);
	q->count = 0;

	/* enable irqs */
	cx_set(MO_PCI_INTMSK, core->pci_irqmask | PCI_INT_VIDINT);

	/*
	 * Enables corresponding bits at PCI_INT_STAT:
	 *	bits 0 to 4: video, audio, transport stream, VIP, Host
	 *	bit 7: समयr
	 *	bits 8 and 9: DMA complete क्रम: SRC, DST
	 *	bits 10 and 11: BERR संकेत निश्चितed क्रम RISC: RD, WR
	 *	bits 12 to 15: BERR संकेत निश्चितed क्रम: BRDG, SRC, DST, IPB
	 */
	cx_set(MO_VID_INTMSK, 0x0f0011);

	/* enable capture */
	cx_set(VID_CAPTURE_CONTROL, 0x06);

	/* start dma */
	cx_set(MO_DEV_CNTRL2, (1 << 5));
	cx_set(MO_VID_DMACNTRL, 0x11); /* Planar Y and packed FIFO and RISC enable */

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused stop_video_dma(काष्ठा cx8800_dev    *dev)
अणु
	काष्ठा cx88_core *core = dev->core;

	/* stop dma */
	cx_clear(MO_VID_DMACNTRL, 0x11);

	/* disable capture */
	cx_clear(VID_CAPTURE_CONTROL, 0x06);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_VIDINT);
	cx_clear(MO_VID_INTMSK, 0x0f0011);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused restart_video_queue(काष्ठा cx8800_dev *dev,
					      काष्ठा cx88_dmaqueue *q)
अणु
	काष्ठा cx88_buffer *buf;

	अगर (!list_empty(&q->active)) अणु
		buf = list_entry(q->active.next, काष्ठा cx88_buffer, list);
		dprपूर्णांकk(2, "restart_queue [%p/%d]: restart dma\n",
			buf, buf->vb.vb2_buf.index);
		start_video_dma(dev, q, buf);
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;
	काष्ठा cx88_core *core = dev->core;

	*num_planes = 1;
	sizes[0] = (dev->fmt->depth * core->width * core->height) >> 3;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_core *core = dev->core;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा sg_table *sgt = vb2_dma_sg_plane_desc(vb, 0);

	buf->bpl = core->width * dev->fmt->depth >> 3;

	अगर (vb2_plane_size(vb, 0) < core->height * buf->bpl)
		वापस -EINVAL;
	vb2_set_plane_payload(vb, 0, core->height * buf->bpl);

	चयन (core->field) अणु
	हाल V4L2_FIELD_TOP:
		cx88_risc_buffer(dev->pci, &buf->risc,
				 sgt->sgl, 0, UNSET,
				 buf->bpl, 0, core->height);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		cx88_risc_buffer(dev->pci, &buf->risc,
				 sgt->sgl, UNSET, 0,
				 buf->bpl, 0, core->height);
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		cx88_risc_buffer(dev->pci, &buf->risc,
				 sgt->sgl,
				 0, buf->bpl * (core->height >> 1),
				 buf->bpl, 0,
				 core->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_SEQ_BT:
		cx88_risc_buffer(dev->pci, &buf->risc,
				 sgt->sgl,
				 buf->bpl * (core->height >> 1), 0,
				 buf->bpl, 0,
				 core->height >> 1);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
	शेष:
		cx88_risc_buffer(dev->pci, &buf->risc,
				 sgt->sgl, 0, buf->bpl,
				 buf->bpl, buf->bpl,
				 core->height >> 1);
		अवरोध;
	पूर्ण
	dprपूर्णांकk(2,
		"[%p/%d] %s - %dx%d %dbpp 0x%08x - dma=0x%08lx\n",
		buf, buf->vb.vb2_buf.index, __func__,
		core->width, core->height, dev->fmt->depth, dev->fmt->fourcc,
		(अचिन्हित दीर्घ)buf->risc.dma);
	वापस 0;
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_riscmem *risc = &buf->risc;

	अगर (risc->cpu)
		pci_मुक्त_consistent(dev->pci, risc->size, risc->cpu, risc->dma);
	स_रखो(risc, 0, माप(*risc));
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8800_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer    *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_buffer    *prev;
	काष्ठा cx88_dmaqueue  *q    = &dev->vidq;

	/* add jump to start */
	buf->risc.cpu[1] = cpu_to_le32(buf->risc.dma + 8);
	buf->risc.jmp[0] = cpu_to_le32(RISC_JUMP | RISC_CNT_INC);
	buf->risc.jmp[1] = cpu_to_le32(buf->risc.dma + 8);

	अगर (list_empty(&q->active)) अणु
		list_add_tail(&buf->list, &q->active);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - first active\n",
			buf, buf->vb.vb2_buf.index);

	पूर्ण अन्यथा अणु
		buf->risc.cpu[0] |= cpu_to_le32(RISC_IRQ1);
		prev = list_entry(q->active.prev, काष्ठा cx88_buffer, list);
		list_add_tail(&buf->list, &q->active);
		prev->risc.jmp[1] = cpu_to_le32(buf->risc.dma);
		dprपूर्णांकk(2, "[%p/%d] buffer_queue - append to active\n",
			buf, buf->vb.vb2_buf.index);
	पूर्ण
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->vidq;
	काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

	start_video_dma(dev, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx8800_dev *dev = q->drv_priv;
	काष्ठा cx88_core *core = dev->core;
	काष्ठा cx88_dmaqueue *dmaq = &dev->vidq;
	अचिन्हित दीर्घ flags;

	cx_clear(MO_VID_DMACNTRL, 0x11);
	cx_clear(VID_CAPTURE_CONTROL, 0x06);
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cx8800_video_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक radio_खोलो(काष्ठा file *file)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	पूर्णांक ret = v4l2_fh_खोलो(file);

	अगर (ret)
		वापस ret;

	cx_ग_लिखो(MO_GP3_IO, core->board.radio.gpio3);
	cx_ग_लिखो(MO_GP0_IO, core->board.radio.gpio0);
	cx_ग_लिखो(MO_GP1_IO, core->board.radio.gpio1);
	cx_ग_लिखो(MO_GP2_IO, core->board.radio.gpio2);
	अगर (core->board.radio.audioroute) अणु
		अगर (core->sd_wm8775) अणु
			call_all(core, audio, s_routing,
				 core->board.radio.audioroute, 0, 0);
		पूर्ण
		/* "I2S ADC mode" */
		core->tvaudio = WW_I2SADC;
		cx88_set_tvaudio(core);
	पूर्ण अन्यथा अणु
		/* FM Mode */
		core->tvaudio = WW_FM;
		cx88_set_tvaudio(core);
		cx88_set_stereo(core, V4L2_TUNER_MODE_STEREO, 1);
	पूर्ण
	call_all(core, tuner, s_radio);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* VIDEO CTRL IOCTLS                                                  */

अटल पूर्णांक cx8800_s_vid_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा cx88_core *core =
		container_of(ctrl->handler, काष्ठा cx88_core, video_hdl);
	स्थिर काष्ठा cx88_ctrl *cc = ctrl->priv;
	u32 value, mask;

	mask = cc->mask;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_SATURATION:
		/* special v_sat handling */

		value = ((ctrl->val - cc->off) << cc->shअगरt) & cc->mask;

		अगर (core->tvnorm & V4L2_STD_SECAM) अणु
			/* For SECAM, both U and V sat should be equal */
			value = value << 8 | value;
		पूर्ण अन्यथा अणु
			/* Keeps U Saturation proportional to V Sat */
			value = (value * 0x5a) / 0x7f << 8 | value;
		पूर्ण
		mask = 0xffff;
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		/* 0b000, 0b100, 0b101, 0b110, or 0b111 */
		value = (ctrl->val < 1 ? 0 : ((ctrl->val + 3) << 7));
		/* needs to be set क्रम both fields */
		cx_anकरोr(MO_FILTER_EVEN, mask, value);
		अवरोध;
	हाल V4L2_CID_CHROMA_AGC:
		value = ((ctrl->val - cc->off) << cc->shअगरt) & cc->mask;
		अवरोध;
	शेष:
		value = ((ctrl->val - cc->off) << cc->shअगरt) & cc->mask;
		अवरोध;
	पूर्ण
	dprपूर्णांकk(1,
		"set_control id=0x%X(%s) ctrl=0x%02x, reg=0x%02x val=0x%02x (mask 0x%02x)%s\n",
		ctrl->id, ctrl->name, ctrl->val, cc->reg, value,
		mask, cc->sreg ? " [shadowed]" : "");
	अगर (cc->sreg)
		cx_sanकरोr(cc->sreg, cc->reg, mask, value);
	अन्यथा
		cx_anकरोr(cc->reg, mask, value);
	वापस 0;
पूर्ण

अटल पूर्णांक cx8800_s_aud_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा cx88_core *core =
		container_of(ctrl->handler, काष्ठा cx88_core, audio_hdl);
	स्थिर काष्ठा cx88_ctrl *cc = ctrl->priv;
	u32 value, mask;

	/* Pass changes onto any WM8775 */
	अगर (core->sd_wm8775) अणु
		चयन (ctrl->id) अणु
		हाल V4L2_CID_AUDIO_MUTE:
			wm8775_s_ctrl(core, ctrl->id, ctrl->val);
			अवरोध;
		हाल V4L2_CID_AUDIO_VOLUME:
			wm8775_s_ctrl(core, ctrl->id, (ctrl->val) ?
						(0x90 + ctrl->val) << 8 : 0);
			अवरोध;
		हाल V4L2_CID_AUDIO_BALANCE:
			wm8775_s_ctrl(core, ctrl->id, ctrl->val << 9);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	mask = cc->mask;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_BALANCE:
		value = (ctrl->val < 0x40) ?
			(0x7f - ctrl->val) : (ctrl->val - 0x40);
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		value = 0x3f - (ctrl->val & 0x3f);
		अवरोध;
	शेष:
		value = ((ctrl->val - cc->off) << cc->shअगरt) & cc->mask;
		अवरोध;
	पूर्ण
	dprपूर्णांकk(1,
		"set_control id=0x%X(%s) ctrl=0x%02x, reg=0x%02x val=0x%02x (mask 0x%02x)%s\n",
		ctrl->id, ctrl->name, ctrl->val, cc->reg, value,
		mask, cc->sreg ? " [shadowed]" : "");
	अगर (cc->sreg)
		cx_sanकरोr(cc->sreg, cc->reg, mask, value);
	अन्यथा
		cx_anकरोr(cc->reg, mask, value);
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* VIDEO IOCTLS                                                       */

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	f->fmt.pix.width        = core->width;
	f->fmt.pix.height       = core->height;
	f->fmt.pix.field        = core->field;
	f->fmt.pix.pixelक्रमmat  = dev->fmt->fourcc;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * dev->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	स्थिर काष्ठा cx8800_fmt *fmt;
	क्रमागत v4l2_field   field;
	अचिन्हित पूर्णांक      maxw, maxh;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt)
		वापस -EINVAL;

	maxw = norm_maxw(core->tvnorm);
	maxh = norm_maxh(core->tvnorm);

	field = f->fmt.pix.field;

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_SEQ_TB:
		अवरोध;
	शेष:
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		अवरोध;
	पूर्ण
	अगर (V4L2_FIELD_HAS_T_OR_B(field))
		maxh /= 2;

	v4l_bound_align_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.field = field;
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
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	पूर्णांक err = vidioc_try_fmt_vid_cap(file, priv, f);

	अगर (err != 0)
		वापस err;
	अगर (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq))
		वापस -EBUSY;
	अगर (core->dvbdev && vb2_is_busy(&core->dvbdev->vb2_mpegq))
		वापस -EBUSY;
	dev->fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	core->width = f->fmt.pix.width;
	core->height = f->fmt.pix.height;
	core->field = f->fmt.pix.field;
	वापस 0;
पूर्ण

पूर्णांक cx88_querycap(काष्ठा file *file, काष्ठा cx88_core *core,
		  काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->card, core->board.name, माप(cap->card));
	cap->capabilities = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VBI_CAPTURE |
			    V4L2_CAP_DEVICE_CAPS;
	अगर (core->board.tuner_type != UNSET)
		cap->capabilities |= V4L2_CAP_TUNER;
	अगर (core->board.radio.type == CX88_RADIO)
		cap->capabilities |= V4L2_CAP_RADIO;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_querycap);

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	strscpy(cap->driver, "cx8800", माप(cap->driver));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	वापस cx88_querycap(file, core, cap);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (unlikely(f->index >= ARRAY_SIZE(क्रमmats)))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *tvnorm)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	*tvnorm = core->tvnorm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id tvnorms)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	वापस cx88_set_tvnorm(core, tvnorms);
पूर्ण

/* only one input in this sample driver */
पूर्णांक cx88_क्रमागत_input(काष्ठा cx88_core  *core, काष्ठा v4l2_input *i)
अणु
	अटल स्थिर अक्षर * स्थिर iname[] = अणु
		[CX88_VMUX_COMPOSITE1] = "Composite1",
		[CX88_VMUX_COMPOSITE2] = "Composite2",
		[CX88_VMUX_COMPOSITE3] = "Composite3",
		[CX88_VMUX_COMPOSITE4] = "Composite4",
		[CX88_VMUX_SVIDEO] = "S-Video",
		[CX88_VMUX_TELEVISION] = "Television",
		[CX88_VMUX_CABLE] = "Cable TV",
		[CX88_VMUX_DVB] = "DVB",
		[CX88_VMUX_DEBUG] = "for debug only",
	पूर्ण;
	अचिन्हित पूर्णांक n = i->index;

	अगर (n >= 4)
		वापस -EINVAL;
	अगर (!INPUT(n).type)
		वापस -EINVAL;
	i->type  = V4L2_INPUT_TYPE_CAMERA;
	strscpy(i->name, iname[INPUT(n).type], माप(i->name));
	अगर ((INPUT(n).type == CX88_VMUX_TELEVISION) ||
	    (INPUT(n).type == CX88_VMUX_CABLE))
		i->type = V4L2_INPUT_TYPE_TUNER;

	i->std = CX88_NORMS;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_क्रमागत_input);

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	वापस cx88_क्रमागत_input(core, i);
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	*i = core->input;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (i >= 4)
		वापस -EINVAL;
	अगर (!INPUT(i).type)
		वापस -EINVAL;

	cx88_newstation(core);
	cx88_video_mux(core, i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	u32 reg;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (t->index != 0)
		वापस -EINVAL;

	strscpy(t->name, "Television", माप(t->name));
	t->capability = V4L2_TUNER_CAP_NORM;
	t->rangehigh  = 0xffffffffUL;
	call_all(core, tuner, g_tuner, t);

	cx88_get_stereo(core, t);
	reg = cx_पढ़ो(MO_DEVICE_STATUS);
	t->संकेत = (reg & (1 << 5)) ? 0xffff : 0x0000;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
			  स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (core->board.tuner_type == UNSET)
		वापस -EINVAL;
	अगर (t->index != 0)
		वापस -EINVAL;

	cx88_set_stereo(core, t->audmode, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (f->tuner)
		वापस -EINVAL;

	f->frequency = core->freq;

	call_all(core, tuner, g_frequency, f);

	वापस 0;
पूर्ण

पूर्णांक cx88_set_freq(काष्ठा cx88_core  *core,
		  स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा v4l2_frequency new_freq = *f;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (unlikely(f->tuner != 0))
		वापस -EINVAL;

	cx88_newstation(core);
	call_all(core, tuner, s_frequency, f);
	call_all(core, tuner, g_frequency, &new_freq);
	core->freq = new_freq.frequency;

	/* When changing channels it is required to reset TVAUDIO */
	usleep_range(10000, 20000);
	cx88_set_tvaudio(core);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_set_freq);

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	वापस cx88_set_freq(core, f);
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	/* cx2388x has a 24-bit रेजिस्टर space */
	reg->val = cx_पढ़ो(reg->reg & 0xfffffc);
	reg->size = 4;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *fh,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	cx_ग_लिखो(reg->reg & 0xfffffc, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ----------------------------------------------------------- */
/* RADIO ESPECIFIC IOCTLS                                      */
/* ----------------------------------------------------------- */

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (unlikely(t->index > 0))
		वापस -EINVAL;

	strscpy(t->name, "Radio", माप(t->name));

	call_all(core, tuner, g_tuner, t);
	वापस 0;
पूर्ण

अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv,
			 स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8800_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (t->index != 0)
		वापस -EINVAL;

	call_all(core, tuner, s_tuner, t);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------- */

अटल स्थिर अक्षर *cx88_vid_irqs[32] = अणु
	"y_risci1", "u_risci1", "v_risci1", "vbi_risc1",
	"y_risci2", "u_risci2", "v_risci2", "vbi_risc2",
	"y_oflow",  "u_oflow",  "v_oflow",  "vbi_oflow",
	"y_sync",   "u_sync",   "v_sync",   "vbi_sync",
	"opc_err",  "par_err",  "rip_err",  "pci_abort",
पूर्ण;

अटल व्योम cx8800_vid_irq(काष्ठा cx8800_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	u32 status, mask, count;

	status = cx_पढ़ो(MO_VID_INTSTAT);
	mask   = cx_पढ़ो(MO_VID_INTMSK);
	अगर (0 == (status & mask))
		वापस;
	cx_ग_लिखो(MO_VID_INTSTAT, status);
	अगर (irq_debug  ||  (status & mask & ~0xff))
		cx88_prपूर्णांक_irqbits("irq vid",
				   cx88_vid_irqs, ARRAY_SIZE(cx88_vid_irqs),
				   status, mask);

	/* risc op code error */
	अगर (status & (1 << 16)) अणु
		pr_warn("video risc op code error\n");
		cx_clear(MO_VID_DMACNTRL, 0x11);
		cx_clear(VID_CAPTURE_CONTROL, 0x06);
		cx88_sram_channel_dump(core, &cx88_sram_channels[SRAM_CH21]);
	पूर्ण

	/* risc1 y */
	अगर (status & 0x01) अणु
		spin_lock(&dev->slock);
		count = cx_पढ़ो(MO_VIDY_GPCNT);
		cx88_wakeup(core, &dev->vidq, count);
		spin_unlock(&dev->slock);
	पूर्ण

	/* risc1 vbi */
	अगर (status & 0x08) अणु
		spin_lock(&dev->slock);
		count = cx_पढ़ो(MO_VBI_GPCNT);
		cx88_wakeup(core, &dev->vbiq, count);
		spin_unlock(&dev->slock);
	पूर्ण
पूर्ण

अटल irqवापस_t cx8800_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cx8800_dev *dev = dev_id;
	काष्ठा cx88_core *core = dev->core;
	u32 status;
	पूर्णांक loop, handled = 0;

	क्रम (loop = 0; loop < 10; loop++) अणु
		status = cx_पढ़ो(MO_PCI_INTSTAT) &
			(core->pci_irqmask | PCI_INT_VIDINT);
		अगर (status == 0)
			जाओ out;
		cx_ग_लिखो(MO_PCI_INTSTAT, status);
		handled = 1;

		अगर (status & core->pci_irqmask)
			cx88_core_irq(core, status);
		अगर (status & PCI_INT_VIDINT)
			cx8800_vid_irq(dev);
	पूर्ण
	अगर (loop == 10) अणु
		pr_warn("irq loop -- clearing mask\n");
		cx_ग_लिखो(MO_PCI_INTMSK, 0);
	पूर्ण

 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

/* ----------------------------------------------------------- */
/* exported stuff                                              */

अटल स्थिर काष्ठा v4l2_file_operations video_fops = अणु
	.owner	       = THIS_MODULE,
	.खोलो	       = v4l2_fh_खोलो,
	.release       = vb2_fop_release,
	.पढ़ो	       = vb2_fop_पढ़ो,
	.poll          = vb2_fop_poll,
	.mmap	       = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_g_tuner       = vidioc_g_tuner,
	.vidioc_s_tuner       = vidioc_s_tuner,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_s_frequency   = vidioc_s_frequency,
	.vidioc_subscribe_event      = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event    = v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर    = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर    = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा video_device cx8800_video_ढाँचा = अणु
	.name                 = "cx8800-video",
	.fops                 = &video_fops,
	.ioctl_ops	      = &video_ioctl_ops,
	.tvnorms              = CX88_NORMS,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops vbi_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_g_fmt_vbi_cap     = cx8800_vbi_fmt,
	.vidioc_try_fmt_vbi_cap   = cx8800_vbi_fmt,
	.vidioc_s_fmt_vbi_cap     = cx8800_vbi_fmt,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_g_tuner       = vidioc_g_tuner,
	.vidioc_s_tuner       = vidioc_s_tuner,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_s_frequency   = vidioc_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर    = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर    = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा video_device cx8800_vbi_ढाँचा = अणु
	.name                 = "cx8800-vbi",
	.fops                 = &video_fops,
	.ioctl_ops	      = &vbi_ioctl_ops,
	.tvnorms              = CX88_NORMS,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_fops = अणु
	.owner         = THIS_MODULE,
	.खोलो          = radio_खोलो,
	.poll          = v4l2_ctrl_poll,
	.release       = v4l2_fh_release,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_g_tuner       = radio_g_tuner,
	.vidioc_s_tuner       = radio_s_tuner,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_s_frequency   = vidioc_s_frequency,
	.vidioc_subscribe_event      = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event    = v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर    = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर    = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा video_device cx8800_radio_ढाँचा = अणु
	.name                 = "cx8800-radio",
	.fops                 = &radio_fops,
	.ioctl_ops	      = &radio_ioctl_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops cx8800_ctrl_vid_ops = अणु
	.s_ctrl = cx8800_s_vid_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops cx8800_ctrl_aud_ops = अणु
	.s_ctrl = cx8800_s_aud_ctrl,
पूर्ण;

/* ----------------------------------------------------------- */

अटल व्योम cx8800_unरेजिस्टर_video(काष्ठा cx8800_dev *dev)
अणु
	video_unरेजिस्टर_device(&dev->radio_dev);
	video_unरेजिस्टर_device(&dev->vbi_dev);
	video_unरेजिस्टर_device(&dev->video_dev);
पूर्ण

अटल पूर्णांक cx8800_initdev(काष्ठा pci_dev *pci_dev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा cx8800_dev *dev;
	काष्ठा cx88_core *core;
	काष्ठा vb2_queue *q;
	पूर्णांक err;
	पूर्णांक i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ fail_मुक्त;
	पूर्ण
	core = cx88_core_get(dev->pci);
	अगर (!core) अणु
		err = -EINVAL;
		जाओ fail_disable;
	पूर्ण
	dev->core = core;

	/* prपूर्णांक pci info */
	dev->pci_rev = pci_dev->revision;
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
		dev->pci_lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));

	pci_set_master(pci_dev);
	err = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		pr_err("Oops: no 32bit PCI DMA ???\n");
		जाओ fail_core;
	पूर्ण

	/* initialize driver काष्ठा */
	spin_lock_init(&dev->slock);

	/* init video dma queues */
	INIT_LIST_HEAD(&dev->vidq.active);

	/* init vbi dma queues */
	INIT_LIST_HEAD(&dev->vbiq.active);

	/* get irq */
	err = request_irq(pci_dev->irq, cx8800_irq,
			  IRQF_SHARED, core->name, dev);
	अगर (err < 0) अणु
		pr_err("can't get IRQ %d\n", pci_dev->irq);
		जाओ fail_core;
	पूर्ण
	cx_set(MO_PCI_INTMSK, core->pci_irqmask);

	क्रम (i = 0; i < CX8800_AUD_CTLS; i++) अणु
		स्थिर काष्ठा cx88_ctrl *cc = &cx8800_aud_ctls[i];
		काष्ठा v4l2_ctrl *vc;

		vc = v4l2_ctrl_new_std(&core->audio_hdl, &cx8800_ctrl_aud_ops,
				       cc->id, cc->minimum, cc->maximum,
				       cc->step, cc->शेष_value);
		अगर (!vc) अणु
			err = core->audio_hdl.error;
			जाओ fail_irq;
		पूर्ण
		vc->priv = (व्योम *)cc;
	पूर्ण

	क्रम (i = 0; i < CX8800_VID_CTLS; i++) अणु
		स्थिर काष्ठा cx88_ctrl *cc = &cx8800_vid_ctls[i];
		काष्ठा v4l2_ctrl *vc;

		vc = v4l2_ctrl_new_std(&core->video_hdl, &cx8800_ctrl_vid_ops,
				       cc->id, cc->minimum, cc->maximum,
				       cc->step, cc->शेष_value);
		अगर (!vc) अणु
			err = core->video_hdl.error;
			जाओ fail_irq;
		पूर्ण
		vc->priv = (व्योम *)cc;
		अगर (vc->id == V4L2_CID_CHROMA_AGC)
			core->chroma_agc = vc;
	पूर्ण
	v4l2_ctrl_add_handler(&core->video_hdl, &core->audio_hdl, शून्य, false);

	/* load and configure helper modules */

	अगर (core->board.audio_chip == CX88_AUDIO_WM8775) अणु
		काष्ठा i2c_board_info wm8775_info = अणु
			.type = "wm8775",
			.addr = 0x36 >> 1,
			.platक्रमm_data = &core->wm8775_data,
		पूर्ण;
		काष्ठा v4l2_subdev *sd;

		अगर (core->boardnr == CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1)
			core->wm8775_data.is_nova_s = true;
		अन्यथा
			core->wm8775_data.is_nova_s = false;

		sd = v4l2_i2c_new_subdev_board(&core->v4l2_dev, &core->i2c_adap,
					       &wm8775_info, शून्य);
		अगर (sd) अणु
			core->sd_wm8775 = sd;
			sd->grp_id = WM8775_GID;
		पूर्ण
	पूर्ण

	अगर (core->board.audio_chip == CX88_AUDIO_TVAUDIO) अणु
		/*
		 * This probes क्रम a tda9874 as is used on some
		 * Pixelview Ultra boards.
		 */
		v4l2_i2c_new_subdev(&core->v4l2_dev, &core->i2c_adap,
				    "tvaudio", 0, I2C_ADDRS(0xb0 >> 1));
	पूर्ण

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD:
	हाल CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD: अणु
		अटल स्थिर काष्ठा i2c_board_info rtc_info = अणु
			I2C_BOARD_INFO("isl1208", 0x6f)
		पूर्ण;

		request_module("rtc-isl1208");
		core->i2c_rtc = i2c_new_client_device(&core->i2c_adap, &rtc_info);
	पूर्ण
		fallthrough;
	हाल CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO:
		request_module("ir-kbd-i2c");
	पूर्ण

	/* Sets device info at pci_dev */
	pci_set_drvdata(pci_dev, dev);

	dev->fmt = क्रमmat_by_fourcc(V4L2_PIX_FMT_BGR24);

	/* Maपूर्णांकain a reference so cx88-blackbird can query the 8800 device. */
	core->v4ldev = dev;

	/* initial device configuration */
	mutex_lock(&core->lock);
	cx88_set_tvnorm(core, V4L2_STD_NTSC_M);
	v4l2_ctrl_handler_setup(&core->video_hdl);
	v4l2_ctrl_handler_setup(&core->audio_hdl);
	cx88_video_mux(core, 0);

	q = &dev->vb2_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->gfp_flags = GFP_DMA32;
	q->min_buffers_needed = 2;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx88_buffer);
	q->ops = &cx8800_video_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &core->lock;
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
	q->buf_काष्ठा_size = माप(काष्ठा cx88_buffer);
	q->ops = &cx8800_vbi_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &core->lock;
	q->dev = &dev->pci->dev;

	err = vb2_queue_init(q);
	अगर (err < 0)
		जाओ fail_unreg;

	/* रेजिस्टर v4l devices */
	cx88_vdev_init(core, dev->pci, &dev->video_dev,
		       &cx8800_video_ढाँचा, "video");
	video_set_drvdata(&dev->video_dev, dev);
	dev->video_dev.ctrl_handler = &core->video_hdl;
	dev->video_dev.queue = &dev->vb2_vidq;
	dev->video_dev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				     V4L2_CAP_VIDEO_CAPTURE;
	अगर (core->board.tuner_type != UNSET)
		dev->video_dev.device_caps |= V4L2_CAP_TUNER;
	err = video_रेजिस्टर_device(&dev->video_dev, VFL_TYPE_VIDEO,
				    video_nr[core->nr]);
	अगर (err < 0) अणु
		pr_err("can't register video device\n");
		जाओ fail_unreg;
	पूर्ण
	pr_info("registered device %s [v4l2]\n",
		video_device_node_name(&dev->video_dev));

	cx88_vdev_init(core, dev->pci, &dev->vbi_dev,
		       &cx8800_vbi_ढाँचा, "vbi");
	video_set_drvdata(&dev->vbi_dev, dev);
	dev->vbi_dev.queue = &dev->vb2_vbiq;
	dev->vbi_dev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				   V4L2_CAP_VBI_CAPTURE;
	अगर (core->board.tuner_type != UNSET)
		dev->vbi_dev.device_caps |= V4L2_CAP_TUNER;
	err = video_रेजिस्टर_device(&dev->vbi_dev, VFL_TYPE_VBI,
				    vbi_nr[core->nr]);
	अगर (err < 0) अणु
		pr_err("can't register vbi device\n");
		जाओ fail_unreg;
	पूर्ण
	pr_info("registered device %s\n",
		video_device_node_name(&dev->vbi_dev));

	अगर (core->board.radio.type == CX88_RADIO) अणु
		cx88_vdev_init(core, dev->pci, &dev->radio_dev,
			       &cx8800_radio_ढाँचा, "radio");
		video_set_drvdata(&dev->radio_dev, dev);
		dev->radio_dev.ctrl_handler = &core->audio_hdl;
		dev->radio_dev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		err = video_रेजिस्टर_device(&dev->radio_dev, VFL_TYPE_RADIO,
					    radio_nr[core->nr]);
		अगर (err < 0) अणु
			pr_err("can't register radio device\n");
			जाओ fail_unreg;
		पूर्ण
		pr_info("registered device %s\n",
			video_device_node_name(&dev->radio_dev));
	पूर्ण

	/* start tvaudio thपढ़ो */
	अगर (core->board.tuner_type != UNSET) अणु
		core->kthपढ़ो = kthपढ़ो_run(cx88_audio_thपढ़ो,
					    core, "cx88 tvaudio");
		अगर (IS_ERR(core->kthपढ़ो)) अणु
			err = PTR_ERR(core->kthपढ़ो);
			pr_err("failed to create cx88 audio thread, err=%d\n",
			       err);
		पूर्ण
	पूर्ण
	mutex_unlock(&core->lock);

	वापस 0;

fail_unreg:
	cx8800_unरेजिस्टर_video(dev);
	mutex_unlock(&core->lock);
fail_irq:
	मुक्त_irq(pci_dev->irq, dev);
fail_core:
	core->v4ldev = शून्य;
	cx88_core_put(core, dev->pci);
fail_disable:
	pci_disable_device(pci_dev);
fail_मुक्त:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम cx8800_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा cx8800_dev *dev = pci_get_drvdata(pci_dev);
	काष्ठा cx88_core *core = dev->core;

	/* stop thपढ़ो */
	अगर (core->kthपढ़ो) अणु
		kthपढ़ो_stop(core->kthपढ़ो);
		core->kthपढ़ो = शून्य;
	पूर्ण

	अगर (core->ir)
		cx88_ir_stop(core);

	cx88_shutकरोwn(core); /* FIXME */

	/* unरेजिस्टर stuff */

	मुक्त_irq(pci_dev->irq, dev);
	cx8800_unरेजिस्टर_video(dev);
	pci_disable_device(pci_dev);

	core->v4ldev = शून्य;

	/* मुक्त memory */
	cx88_core_put(core, dev->pci);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक __maybe_unused cx8800_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा cx8800_dev *dev = dev_get_drvdata(dev_d);
	काष्ठा cx88_core *core = dev->core;
	अचिन्हित दीर्घ flags;

	/* stop video+vbi capture */
	spin_lock_irqsave(&dev->slock, flags);
	अगर (!list_empty(&dev->vidq.active)) अणु
		pr_info("suspend video\n");
		stop_video_dma(dev);
	पूर्ण
	अगर (!list_empty(&dev->vbiq.active)) अणु
		pr_info("suspend vbi\n");
		cx8800_stop_vbi_dma(dev);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);

	अगर (core->ir)
		cx88_ir_stop(core);
	/* FIXME -- shutकरोwn device */
	cx88_shutकरोwn(core);

	dev->state.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cx8800_resume(काष्ठा device *dev_d)
अणु
	काष्ठा cx8800_dev *dev = dev_get_drvdata(dev_d);
	काष्ठा cx88_core *core = dev->core;
	अचिन्हित दीर्घ flags;

	dev->state.disabled = 0;

	/* FIXME: re-initialize hardware */
	cx88_reset(core);
	अगर (core->ir)
		cx88_ir_start(core);

	cx_set(MO_PCI_INTMSK, core->pci_irqmask);

	/* restart video+vbi capture */
	spin_lock_irqsave(&dev->slock, flags);
	अगर (!list_empty(&dev->vidq.active)) अणु
		pr_info("resume video\n");
		restart_video_queue(dev, &dev->vidq);
	पूर्ण
	अगर (!list_empty(&dev->vbiq.active)) अणु
		pr_info("resume vbi\n");
		cx8800_restart_vbi_queue(dev, &dev->vbiq);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------- */

अटल स्थिर काष्ठा pci_device_id cx8800_pci_tbl[] = अणु
	अणु
		.venकरोr       = 0x14f1,
		.device       = 0x8800,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	पूर्ण, अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cx8800_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(cx8800_pm_ops, cx8800_suspend, cx8800_resume);

अटल काष्ठा pci_driver cx8800_pci_driver = अणु
	.name      = "cx8800",
	.id_table  = cx8800_pci_tbl,
	.probe     = cx8800_initdev,
	.हटाओ    = cx8800_finidev,
	.driver.pm = &cx8800_pm_ops,
पूर्ण;

module_pci_driver(cx8800_pci_driver);
