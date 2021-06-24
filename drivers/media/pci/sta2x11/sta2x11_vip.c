<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the driver क्रम the STA2x11 Video Input Port.
 *
 * Copyright (C) 2012       ST Microelectronics
 *     author: Federico Vaga <federico.vaga@gmail.com>
 * Copyright (C) 2010       WindRiver Systems, Inc.
 *     authors: Andreas Kies <andreas.kies@windriver.com>
 *              Vlad Lungu   <vlad.lungu@windriver.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kmod.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "sta2x11_vip.h"

#घोषणा DRV_VERSION "1.3"

#अगर_अघोषित PCI_DEVICE_ID_STMICRO_VIP
#घोषणा PCI_DEVICE_ID_STMICRO_VIP 0xCC0D
#पूर्ण_अगर

#घोषणा MAX_FRAMES 4

/*Register offsets*/
#घोषणा DVP_CTL		0x00
#घोषणा DVP_TFO		0x04
#घोषणा DVP_TFS		0x08
#घोषणा DVP_BFO		0x0C
#घोषणा DVP_BFS		0x10
#घोषणा DVP_VTP		0x14
#घोषणा DVP_VBP		0x18
#घोषणा DVP_VMP		0x1C
#घोषणा DVP_ITM		0x98
#घोषणा DVP_ITS		0x9C
#घोषणा DVP_STA		0xA0
#घोषणा DVP_HLFLN	0xA8
#घोषणा DVP_RGB		0xC0
#घोषणा DVP_PKZ		0xF0

/*Register fields*/
#घोषणा DVP_CTL_ENA	0x00000001
#घोषणा DVP_CTL_RST	0x80000000
#घोषणा DVP_CTL_DIS	(~0x00040001)

#घोषणा DVP_IT_VSB	0x00000008
#घोषणा DVP_IT_VST	0x00000010
#घोषणा DVP_IT_FIFO	0x00000020

#घोषणा DVP_HLFLN_SD	0x00000001

#घोषणा SAVE_COUNT 8
#घोषणा AUX_COUNT 3
#घोषणा IRQ_COUNT 1


काष्ठा vip_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head	list;
	dma_addr_t		dma;
पूर्ण;
अटल अंतरभूत काष्ठा vip_buffer *to_vip_buffer(काष्ठा vb2_v4l2_buffer *vb2)
अणु
	वापस container_of(vb2, काष्ठा vip_buffer, vb);
पूर्ण

/**
 * काष्ठा sta2x11_vip - All पूर्णांकernal data क्रम one instance of device
 * @v4l2_dev: device रेजिस्टरed in v4l layer
 * @video_dev: properties of our device
 * @pdev: PCI device
 * @adapter: contains I2C adapter inक्रमmation
 * @रेजिस्टर_save_area: All relevant रेजिस्टर are saved here during suspend
 * @decoder: contains inक्रमmation about video DAC
 * @ctrl_hdl: handler क्रम control framework
 * @क्रमmat: pixel क्रमmat, fixed UYVY
 * @std: video standard (e.g. PAL/NTSC)
 * @input: input line क्रम video संकेत ( 0 or 1 )
 * @disabled: Device is in घातer करोwn state
 * @slock: क्रम excluse access of रेजिस्टरs
 * @vb_vidq: queue मुख्यtained by videobuf2 layer
 * @buffer_list: list of buffer in use
 * @sequence: sequence number of acquired buffer
 * @active: current active buffer
 * @lock: used in videobuf2 callback
 * @v4l_lock: serialize its video4linux ioctls
 * @tcount: Number of top frames
 * @bcount: Number of bottom frames
 * @overflow: Number of FIFO overflows
 * @iomem: hardware base address
 * @config: I2C and gpio config from platक्रमm
 *
 * All non-local data is accessed via this काष्ठाure.
 */
काष्ठा sta2x11_vip अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device video_dev;
	काष्ठा pci_dev *pdev;
	काष्ठा i2c_adapter *adapter;
	अचिन्हित पूर्णांक रेजिस्टर_save_area[IRQ_COUNT + SAVE_COUNT + AUX_COUNT];
	काष्ठा v4l2_subdev *decoder;
	काष्ठा v4l2_ctrl_handler ctrl_hdl;


	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	v4l2_std_id std;
	अचिन्हित पूर्णांक input;
	पूर्णांक disabled;
	spinlock_t slock;

	काष्ठा vb2_queue vb_vidq;
	काष्ठा list_head buffer_list;
	अचिन्हित पूर्णांक sequence;
	काष्ठा vip_buffer *active; /* current active buffer */
	spinlock_t lock; /* Used in videobuf2 callback */
	काष्ठा mutex v4l_lock;

	/* Interrupt counters */
	पूर्णांक tcount, bcount;
	पूर्णांक overflow;

	व्योम __iomem *iomem;	/* I/O Memory */
	काष्ठा vip_config *config;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक रेजिस्टरs_to_save[AUX_COUNT] = अणु
	DVP_HLFLN, DVP_RGB, DVP_PKZ
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat क्रमmats_50[] = अणु
	अणु			/*PAL पूर्णांकerlaced */
	 .width = 720,
	 .height = 576,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_INTERLACED,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 576,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,
	अणु			/*PAL top */
	 .width = 720,
	 .height = 288,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_TOP,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 288,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,
	अणु			/*PAL bottom */
	 .width = 720,
	 .height = 288,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_BOTTOM,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 288,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,

पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat क्रमmats_60[] = अणु
	अणु			/*NTSC पूर्णांकerlaced */
	 .width = 720,
	 .height = 480,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_INTERLACED,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 480,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,
	अणु			/*NTSC top */
	 .width = 720,
	 .height = 240,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_TOP,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 240,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,
	अणु			/*NTSC bottom */
	 .width = 720,
	 .height = 240,
	 .pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	 .field = V4L2_FIELD_BOTTOM,
	 .bytesperline = 720 * 2,
	 .sizeimage = 720 * 2 * 240,
	 .colorspace = V4L2_COLORSPACE_SMPTE170Mपूर्ण,
पूर्ण;

/* Write VIP रेजिस्टर */
अटल अंतरभूत व्योम reg_ग_लिखो(काष्ठा sta2x11_vip *vip, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ioग_लिखो32((val), (vip->iomem)+(reg));
पूर्ण
/* Read VIP रेजिस्टर */
अटल अंतरभूत u32 reg_पढ़ो(काष्ठा sta2x11_vip *vip, अचिन्हित पूर्णांक reg)
अणु
	वापस  ioपढ़ो32((vip->iomem)+(reg));
पूर्ण
/* Start DMA acquisition */
अटल व्योम start_dma(काष्ठा sta2x11_vip *vip, काष्ठा vip_buffer *vip_buf)
अणु
	अचिन्हित दीर्घ offset = 0;

	अगर (vip->क्रमmat.field == V4L2_FIELD_INTERLACED)
		offset = vip->क्रमmat.width * 2;

	spin_lock_irq(&vip->slock);
	/* Enable acquisition */
	reg_ग_लिखो(vip, DVP_CTL, reg_पढ़ो(vip, DVP_CTL) | DVP_CTL_ENA);
	/* Set Top and Bottom Field memory address */
	reg_ग_लिखो(vip, DVP_VTP, (u32)vip_buf->dma);
	reg_ग_लिखो(vip, DVP_VBP, (u32)vip_buf->dma + offset);
	spin_unlock_irq(&vip->slock);
पूर्ण

/* Fetch the next buffer to activate */
अटल व्योम vip_active_buf_next(काष्ठा sta2x11_vip *vip)
अणु
	/* Get the next buffer */
	spin_lock(&vip->lock);
	अगर (list_empty(&vip->buffer_list)) अणु/* No available buffer */
		spin_unlock(&vip->lock);
		वापस;
	पूर्ण
	vip->active = list_first_entry(&vip->buffer_list,
				       काष्ठा vip_buffer,
				       list);
	/* Reset Top and Bottom counter */
	vip->tcount = 0;
	vip->bcount = 0;
	spin_unlock(&vip->lock);
	अगर (vb2_is_streaming(&vip->vb_vidq)) अणु	/* streaming is on */
		start_dma(vip, vip->active);	/* start dma capture */
	पूर्ण
पूर्ण


/* Videobuf2 Operations */
अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vq);

	अगर (!(*nbuffers) || *nbuffers < MAX_FRAMES)
		*nbuffers = MAX_FRAMES;

	*nplanes = 1;
	sizes[0] = vip->क्रमmat.sizeimage;

	vip->sequence = 0;
	vip->active = शून्य;
	vip->tcount = 0;
	vip->bcount = 0;

	वापस 0;
पूर्ण;
अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vip_buffer *vip_buf = to_vip_buffer(vbuf);

	vip_buf->dma = vb2_dma_contig_plane_dma_addr(vb, 0);
	INIT_LIST_HEAD(&vip_buf->list);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vip_buffer *vip_buf = to_vip_buffer(vbuf);
	अचिन्हित दीर्घ size;

	size = vip->क्रमmat.sizeimage;
	अगर (vb2_plane_size(vb, 0) < size) अणु
		v4l2_err(&vip->v4l2_dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(&vip_buf->vb.vb2_buf, 0, size);

	वापस 0;
पूर्ण
अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vip_buffer *vip_buf = to_vip_buffer(vbuf);

	spin_lock(&vip->lock);
	list_add_tail(&vip_buf->list, &vip->buffer_list);
	अगर (!vip->active) अणु	/* No active buffer, active the first one */
		vip->active = list_first_entry(&vip->buffer_list,
					       काष्ठा vip_buffer,
					       list);
		अगर (vb2_is_streaming(&vip->vb_vidq))	/* streaming is on */
			start_dma(vip, vip_buf);	/* start dma capture */
	पूर्ण
	spin_unlock(&vip->lock);
पूर्ण
अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vip_buffer *vip_buf = to_vip_buffer(vbuf);

	/* Buffer handled, हटाओ it from the list */
	spin_lock(&vip->lock);
	list_del_init(&vip_buf->list);
	spin_unlock(&vip->lock);

	अगर (vb2_is_streaming(vb->vb2_queue))
		vip_active_buf_next(vip);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vq);

	spin_lock_irq(&vip->slock);
	/* Enable पूर्णांकerrupt VSYNC Top and Bottom*/
	reg_ग_लिखो(vip, DVP_ITM, DVP_IT_VSB | DVP_IT_VST);
	spin_unlock_irq(&vip->slock);

	अगर (count)
		start_dma(vip, vip->active);

	वापस 0;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sta2x11_vip *vip = vb2_get_drv_priv(vq);
	काष्ठा vip_buffer *vip_buf, *node;

	/* Disable acquisition */
	reg_ग_लिखो(vip, DVP_CTL, reg_पढ़ो(vip, DVP_CTL) & ~DVP_CTL_ENA);
	/* Disable all पूर्णांकerrupts */
	reg_ग_लिखो(vip, DVP_ITM, 0);

	/* Release all active buffers */
	spin_lock(&vip->lock);
	list_क्रम_each_entry_safe(vip_buf, node, &vip->buffer_list, list) अणु
		vb2_buffer_करोne(&vip_buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&vip_buf->list);
	पूर्ण
	spin_unlock(&vip->lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vip_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_init		= buffer_init,
	.buf_prepare		= buffer_prepare,
	.buf_finish		= buffer_finish,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;


/* File Operations */
अटल स्थिर काष्ठा v4l2_file_operations vip_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll
पूर्ण;


/**
 * vidioc_querycap - वापस capabilities of device
 * @file: descriptor of device
 * @cap: contains वापस values
 * @priv: unused
 *
 * the capabilities of the device are वापसed
 *
 * वापस value: 0, no error.
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, KBUILD_MODNAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s",
		 pci_name(vip->pdev));
	वापस 0;
पूर्ण

/**
 * vidioc_s_std - set video standard
 * @file: descriptor of device
 * @std: contains standard to be set
 * @priv: unused
 *
 * the video standard is set
 *
 * वापस value: 0, no error.
 *
 * -EIO, no input संकेत detected
 *
 * other, वापसed from video DAC.
 */
अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	/*
	 * This is here क्रम backwards compatibility only.
	 * The use of V4L2_STD_ALL to trigger a querystd is non-standard.
	 */
	अगर (std == V4L2_STD_ALL) अणु
		v4l2_subdev_call(vip->decoder, video, querystd, &std);
		अगर (std == V4L2_STD_UNKNOWN)
			वापस -EIO;
	पूर्ण

	अगर (vip->std != std) अणु
		vip->std = std;
		अगर (V4L2_STD_525_60 & std)
			vip->क्रमmat = क्रमmats_60[0];
		अन्यथा
			vip->क्रमmat = क्रमmats_50[0];
	पूर्ण

	वापस v4l2_subdev_call(vip->decoder, video, s_std, std);
पूर्ण

/**
 * vidioc_g_std - get video standard
 * @file: descriptor of device
 * @priv: unused
 * @std: contains वापस values
 *
 * the current video standard is वापसed
 *
 * वापस value: 0, no error.
 */
अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	*std = vip->std;
	वापस 0;
पूर्ण

/**
 * vidioc_querystd - get possible video standards
 * @file: descriptor of device
 * @priv: unused
 * @std: contains वापस values
 *
 * all possible video standards are वापसed
 *
 * वापस value: delivered by video DAC routine.
 */
अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	वापस v4l2_subdev_call(vip->decoder, video, querystd, std);
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index > 1)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = V4L2_STD_ALL;
	प्र_लिखो(inp->name, "Camera %u", inp->index);

	वापस 0;
पूर्ण

/**
 * vidioc_s_input - set input line
 * @file: descriptor of device
 * @priv: unused
 * @i: new input line number
 *
 * the current active input line is set
 *
 * वापस value: 0, no error.
 *
 * -EINVAL, line number out of range
 */
अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);
	पूर्णांक ret;

	अगर (i > 1)
		वापस -EINVAL;
	ret = v4l2_subdev_call(vip->decoder, video, s_routing, i, 0, 0);

	अगर (!ret)
		vip->input = i;

	वापस 0;
पूर्ण

/**
 * vidioc_g_input - वापस input line
 * @file: descriptor of device
 * @priv: unused
 * @i: वापसed input line number
 *
 * the current active input line is वापसed
 *
 * वापस value: always 0.
 */
अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	*i = vip->input;
	वापस 0;
पूर्ण

/**
 * vidioc_क्रमागत_fmt_vid_cap - वापस video capture क्रमmat
 * @file: descriptor of device
 * @priv: unused
 * @f: वापसed क्रमmat inक्रमmation
 *
 * वापसs name and क्रमmat of video capture
 * Only UYVY is supported by hardware.
 *
 * वापस value: always 0.
 */
अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु

	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	वापस 0;
पूर्ण

/**
 * vidioc_try_fmt_vid_cap - set video capture क्रमmat
 * @file: descriptor of device
 * @priv: unused
 * @f: new क्रमmat
 *
 * new video क्रमmat is set which includes width and
 * field type. width is fixed to 720, no scaling.
 * Only UYVY is supported by this hardware.
 * the minimum height is 200, the maximum is 576 (PAL)
 *
 * वापस value: 0, no error
 *
 * -EINVAL, pixel or field क्रमmat not supported
 *
 */
अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);
	पूर्णांक पूर्णांकerlace_lim;

	अगर (V4L2_PIX_FMT_UYVY != f->fmt.pix.pixelक्रमmat) अणु
		v4l2_warn(&vip->v4l2_dev, "Invalid format, only UYVY supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (V4L2_STD_525_60 & vip->std)
		पूर्णांकerlace_lim = 240;
	अन्यथा
		पूर्णांकerlace_lim = 288;

	चयन (f->fmt.pix.field) अणु
	शेष:
	हाल V4L2_FIELD_ANY:
		अगर (पूर्णांकerlace_lim < f->fmt.pix.height)
			f->fmt.pix.field = V4L2_FIELD_INTERLACED;
		अन्यथा
			f->fmt.pix.field = V4L2_FIELD_BOTTOM;
		अवरोध;
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		अगर (पूर्णांकerlace_lim < f->fmt.pix.height)
			f->fmt.pix.height = पूर्णांकerlace_lim;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	पूर्ण

	/* It is the only supported क्रमmat */
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.height &= ~1;
	अगर (2 * पूर्णांकerlace_lim < f->fmt.pix.height)
		f->fmt.pix.height = 2 * पूर्णांकerlace_lim;
	अगर (200 > f->fmt.pix.height)
		f->fmt.pix.height = 200;
	f->fmt.pix.width = 720;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.width * 2 * f->fmt.pix.height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

/**
 * vidioc_s_fmt_vid_cap - set current video क्रमmat parameters
 * @file: descriptor of device
 * @priv: unused
 * @f: वापसed क्रमmat inक्रमmation
 *
 * set new capture क्रमmat
 * वापस value: 0, no error
 *
 * other, delivered by video DAC routine.
 */
अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);
	अचिन्हित पूर्णांक t_stop, b_stop, pitch;
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	अगर (vb2_is_busy(&vip->vb_vidq)) अणु
		/* Can't change क्रमmat during acquisition */
		v4l2_err(&vip->v4l2_dev, "device busy\n");
		वापस -EBUSY;
	पूर्ण
	vip->क्रमmat = f->fmt.pix;
	चयन (vip->क्रमmat.field) अणु
	हाल V4L2_FIELD_INTERLACED:
		t_stop = ((vip->क्रमmat.height / 2 - 1) << 16) |
			 (2 * vip->क्रमmat.width - 1);
		b_stop = t_stop;
		pitch = 4 * vip->क्रमmat.width;
		अवरोध;
	हाल V4L2_FIELD_TOP:
		t_stop = ((vip->क्रमmat.height - 1) << 16) |
			 (2 * vip->क्रमmat.width - 1);
		b_stop = (0 << 16) | (2 * vip->क्रमmat.width - 1);
		pitch = 2 * vip->क्रमmat.width;
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		t_stop = (0 << 16) | (2 * vip->क्रमmat.width - 1);
		b_stop = (vip->क्रमmat.height << 16) |
			 (2 * vip->क्रमmat.width - 1);
		pitch = 2 * vip->क्रमmat.width;
		अवरोध;
	शेष:
		v4l2_err(&vip->v4l2_dev, "unknown field format\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&vip->slock);
	/* Y-X Top Field Offset */
	reg_ग_लिखो(vip, DVP_TFO, 0);
	/* Y-X Bottom Field Offset */
	reg_ग_लिखो(vip, DVP_BFO, 0);
	/* Y-X Top Field Stop*/
	reg_ग_लिखो(vip, DVP_TFS, t_stop);
	/* Y-X Bottom Field Stop */
	reg_ग_लिखो(vip, DVP_BFS, b_stop);
	/* Video Memory Pitch */
	reg_ग_लिखो(vip, DVP_VMP, pitch);
	spin_unlock_irq(&vip->slock);

	वापस 0;
पूर्ण

/**
 * vidioc_g_fmt_vid_cap - get current video क्रमmat parameters
 * @file: descriptor of device
 * @priv: unused
 * @f: contains क्रमmat inक्रमmation
 *
 * वापसs current video क्रमmat parameters
 *
 * वापस value: 0, always successful
 */
अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sta2x11_vip *vip = video_drvdata(file);

	f->fmt.pix = vip->क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vip_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	/* FMT handling */
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt_vid_cap,
	/* Buffer handlers */
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	/* Stream on/off */
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	/* Standard handling */
	.vidioc_g_std = vidioc_g_std,
	.vidioc_s_std = vidioc_s_std,
	.vidioc_querystd = vidioc_querystd,
	/* Input handling */
	.vidioc_क्रमागत_input = vidioc_क्रमागत_input,
	.vidioc_g_input = vidioc_g_input,
	.vidioc_s_input = vidioc_s_input,
	/* Log status ioctl */
	.vidioc_log_status = v4l2_ctrl_log_status,
	/* Event handling */
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device video_dev_ढाँचा = अणु
	.name = KBUILD_MODNAME,
	.release = video_device_release_empty,
	.fops = &vip_fops,
	.ioctl_ops = &vip_ioctl_ops,
	.tvnorms = V4L2_STD_ALL,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		       V4L2_CAP_STREAMING,
पूर्ण;

/**
 * vip_irq - पूर्णांकerrupt routine
 * @irq: Number of पूर्णांकerrupt ( not used, correct number is assumed )
 * @vip: local data काष्ठाure containing all inक्रमmation
 *
 * check क्रम both frame पूर्णांकerrupts set ( top and bottom ).
 * check FIFO overflow, but limit number of log messages after खोलो.
 * संकेत a complete buffer अगर करोne
 *
 * वापस value: IRQ_NONE, पूर्णांकerrupt was not generated by VIP
 *
 * IRQ_HANDLED, पूर्णांकerrupt करोne.
 */
अटल irqवापस_t vip_irq(पूर्णांक irq, काष्ठा sta2x11_vip *vip)
अणु
	अचिन्हित पूर्णांक status;

	status = reg_पढ़ो(vip, DVP_ITS);

	अगर (!status)		/* No पूर्णांकerrupt to handle */
		वापस IRQ_NONE;

	अगर (status & DVP_IT_FIFO)
		अगर (vip->overflow++ > 5)
			pr_info("VIP: fifo overflow\n");

	अगर ((status & DVP_IT_VST) && (status & DVP_IT_VSB)) अणु
		/* this is bad, we are too slow, hope the condition is gone
		 * on the next frame */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & DVP_IT_VST)
		अगर ((++vip->tcount) < 2)
			वापस IRQ_HANDLED;
	अगर (status & DVP_IT_VSB) अणु
		vip->bcount++;
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (vip->active) अणु /* Acquisition is over on this buffer */
		/* Disable acquisition */
		reg_ग_लिखो(vip, DVP_CTL, reg_पढ़ो(vip, DVP_CTL) & ~DVP_CTL_ENA);
		/* Remove the active buffer from the list */
		vip->active->vb.vb2_buf.बारtamp = kसमय_get_ns();
		vip->active->vb.sequence = vip->sequence++;
		vb2_buffer_करोne(&vip->active->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sta2x11_vip_init_रेजिस्टर(काष्ठा sta2x11_vip *vip)
अणु
	/* Register initialization */
	spin_lock_irq(&vip->slock);
	/* Clean पूर्णांकerrupt */
	reg_पढ़ो(vip, DVP_ITS);
	/* Enable Half Line per vertical */
	reg_ग_लिखो(vip, DVP_HLFLN, DVP_HLFLN_SD);
	/* Reset VIP control */
	reg_ग_लिखो(vip, DVP_CTL, DVP_CTL_RST);
	/* Clear VIP control */
	reg_ग_लिखो(vip, DVP_CTL, 0);
	spin_unlock_irq(&vip->slock);
पूर्ण
अटल व्योम sta2x11_vip_clear_रेजिस्टर(काष्ठा sta2x11_vip *vip)
अणु
	spin_lock_irq(&vip->slock);
	/* Disable पूर्णांकerrupt */
	reg_ग_लिखो(vip, DVP_ITM, 0);
	/* Reset VIP Control */
	reg_ग_लिखो(vip, DVP_CTL, DVP_CTL_RST);
	/* Clear VIP Control */
	reg_ग_लिखो(vip, DVP_CTL, 0);
	/* Clean VIP Interrupt */
	reg_पढ़ो(vip, DVP_ITS);
	spin_unlock_irq(&vip->slock);
पूर्ण
अटल पूर्णांक sta2x11_vip_init_buffer(काष्ठा sta2x11_vip *vip)
अणु
	पूर्णांक err;

	err = dma_set_coherent_mask(&vip->pdev->dev, DMA_BIT_MASK(29));
	अगर (err) अणु
		v4l2_err(&vip->v4l2_dev, "Cannot configure coherent mask");
		वापस err;
	पूर्ण
	स_रखो(&vip->vb_vidq, 0, माप(काष्ठा vb2_queue));
	vip->vb_vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vip->vb_vidq.io_modes = VB2_MMAP | VB2_READ;
	vip->vb_vidq.drv_priv = vip;
	vip->vb_vidq.buf_काष्ठा_size = माप(काष्ठा vip_buffer);
	vip->vb_vidq.ops = &vip_video_qops;
	vip->vb_vidq.mem_ops = &vb2_dma_contig_memops;
	vip->vb_vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vip->vb_vidq.dev = &vip->pdev->dev;
	vip->vb_vidq.lock = &vip->v4l_lock;
	err = vb2_queue_init(&vip->vb_vidq);
	अगर (err)
		वापस err;
	INIT_LIST_HEAD(&vip->buffer_list);
	spin_lock_init(&vip->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sta2x11_vip_init_controls(काष्ठा sta2x11_vip *vip)
अणु
	/*
	 * Inititialize an empty control so VIP can inerithing controls
	 * from ADV7180
	 */
	v4l2_ctrl_handler_init(&vip->ctrl_hdl, 0);

	vip->v4l2_dev.ctrl_handler = &vip->ctrl_hdl;
	अगर (vip->ctrl_hdl.error) अणु
		पूर्णांक err = vip->ctrl_hdl.error;

		v4l2_ctrl_handler_मुक्त(&vip->ctrl_hdl);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vip_gpio_reserve - reserve gpio pin
 * @dev: device
 * @pin: GPIO pin number
 * @dir: direction, input or output
 * @name: GPIO pin name
 *
 */
अटल पूर्णांक vip_gpio_reserve(काष्ठा device *dev, पूर्णांक pin, पूर्णांक dir,
			    स्थिर अक्षर *name)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (!gpio_is_valid(pin))
		वापस ret;

	ret = gpio_request(pin, name);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate pin %d (%s)\n", pin, name);
		वापस ret;
	पूर्ण

	ret = gpio_direction_output(pin, dir);
	अगर (ret) अणु
		dev_err(dev, "Failed to set direction for pin %d (%s)\n",
			pin, name);
		gpio_मुक्त(pin);
		वापस ret;
	पूर्ण

	ret = gpio_export(pin, false);
	अगर (ret) अणु
		dev_err(dev, "Failed to export pin %d (%s)\n", pin, name);
		gpio_मुक्त(pin);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vip_gpio_release - release gpio pin
 * @dev: device
 * @pin: GPIO pin number
 * @name: GPIO pin name
 *
 */
अटल व्योम vip_gpio_release(काष्ठा device *dev, पूर्णांक pin, स्थिर अक्षर *name)
अणु
	अगर (gpio_is_valid(pin)) अणु
		dev_dbg(dev, "releasing pin %d (%s)\n",	pin, name);
		gpio_unexport(pin);
		gpio_मुक्त(pin);
	पूर्ण
पूर्ण

/**
 * sta2x11_vip_init_one - init one instance of video device
 * @pdev: PCI device
 * @ent: (not used)
 *
 * allocate reset pins क्रम DAC.
 * Reset video DAC, this is करोne via reset line.
 * allocate memory क्रम managing device
 * request पूर्णांकerrupt
 * map IO region
 * रेजिस्टर device
 * find and initialize video DAC
 *
 * वापस value: 0, no error
 *
 * -ENOMEM, no memory
 *
 * -ENODEV, device could not be detected or रेजिस्टरed
 */
अटल पूर्णांक sta2x11_vip_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	काष्ठा sta2x11_vip *vip;
	काष्ठा vip_config *config;

	/* Check अगर hardware support 26-bit DMA */
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(26))) अणु
		dev_err(&pdev->dev, "26-bit DMA addressing not available\n");
		वापस -EINVAL;
	पूर्ण
	/* Enable PCI */
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	/* Get VIP platक्रमm data */
	config = dev_get_platdata(&pdev->dev);
	अगर (!config) अणु
		dev_info(&pdev->dev, "VIP slot disabled\n");
		ret = -EINVAL;
		जाओ disable;
	पूर्ण

	/* Power configuration */
	ret = vip_gpio_reserve(&pdev->dev, config->pwr_pin, 0,
			       config->pwr_name);
	अगर (ret)
		जाओ disable;

	ret = vip_gpio_reserve(&pdev->dev, config->reset_pin, 0,
			       config->reset_name);
	अगर (ret) अणु
		vip_gpio_release(&pdev->dev, config->pwr_pin,
				 config->pwr_name);
		जाओ disable;
	पूर्ण

	अगर (gpio_is_valid(config->pwr_pin)) अणु
		/* Datasheet says 5ms between PWR and RST */
		usleep_range(5000, 25000);
		gpio_direction_output(config->pwr_pin, 1);
	पूर्ण

	अगर (gpio_is_valid(config->reset_pin)) अणु
		/* Datasheet says 5ms between PWR and RST */
		usleep_range(5000, 25000);
		gpio_direction_output(config->reset_pin, 1);
	पूर्ण
	usleep_range(5000, 25000);

	/* Allocate a new VIP instance */
	vip = kzalloc(माप(काष्ठा sta2x11_vip), GFP_KERNEL);
	अगर (!vip) अणु
		ret = -ENOMEM;
		जाओ release_gpios;
	पूर्ण
	vip->pdev = pdev;
	vip->std = V4L2_STD_PAL;
	vip->क्रमmat = क्रमmats_50[0];
	vip->config = config;
	mutex_init(&vip->v4l_lock);

	ret = sta2x11_vip_init_controls(vip);
	अगर (ret)
		जाओ मुक्त_mem;
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &vip->v4l2_dev);
	अगर (ret)
		जाओ मुक्त_mem;

	dev_dbg(&pdev->dev, "BAR #0 at 0x%lx 0x%lx irq %d\n",
		(अचिन्हित दीर्घ)pci_resource_start(pdev, 0),
		(अचिन्हित दीर्घ)pci_resource_len(pdev, 0), pdev->irq);

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret)
		जाओ unreg;

	vip->iomem = pci_iomap(pdev, 0, 0x100);
	अगर (!vip->iomem) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	pci_enable_msi(pdev);

	/* Initialize buffer */
	ret = sta2x11_vip_init_buffer(vip);
	अगर (ret)
		जाओ unmap;

	spin_lock_init(&vip->slock);

	ret = request_irq(pdev->irq,
			  (irq_handler_t) vip_irq,
			  IRQF_SHARED, KBUILD_MODNAME, vip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		ret = -ENODEV;
		जाओ release_buf;
	पूर्ण

	/* Initialize and रेजिस्टर video device */
	vip->video_dev = video_dev_ढाँचा;
	vip->video_dev.v4l2_dev = &vip->v4l2_dev;
	vip->video_dev.queue = &vip->vb_vidq;
	vip->video_dev.lock = &vip->v4l_lock;
	video_set_drvdata(&vip->video_dev, vip);

	ret = video_रेजिस्टर_device(&vip->video_dev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ vrelease;

	/* Get ADV7180 subdevice */
	vip->adapter = i2c_get_adapter(vip->config->i2c_id);
	अगर (!vip->adapter) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev, "no I2C adapter found\n");
		जाओ vunreg;
	पूर्ण

	vip->decoder = v4l2_i2c_new_subdev(&vip->v4l2_dev, vip->adapter,
					   "adv7180", vip->config->i2c_addr,
					   शून्य);
	अगर (!vip->decoder) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev, "no decoder found\n");
		जाओ vunreg;
	पूर्ण

	i2c_put_adapter(vip->adapter);
	v4l2_subdev_call(vip->decoder, core, init, 0);

	sta2x11_vip_init_रेजिस्टर(vip);

	dev_info(&pdev->dev, "STA2X11 Video Input Port (VIP) loaded\n");
	वापस 0;

vunreg:
	video_set_drvdata(&vip->video_dev, शून्य);
vrelease:
	vb2_video_unरेजिस्टर_device(&vip->video_dev);
	मुक्त_irq(pdev->irq, vip);
release_buf:
	pci_disable_msi(pdev);
unmap:
	pci_iounmap(pdev, vip->iomem);
release:
	pci_release_regions(pdev);
unreg:
	v4l2_device_unरेजिस्टर(&vip->v4l2_dev);
मुक्त_mem:
	kमुक्त(vip);
release_gpios:
	vip_gpio_release(&pdev->dev, config->reset_pin, config->reset_name);
	vip_gpio_release(&pdev->dev, config->pwr_pin, config->pwr_name);
disable:
	/*
	 * करो not call pci_disable_device on sta2x11 because it अवरोध all
	 * other Bus masters on this EP
	 */
	वापस ret;
पूर्ण

/**
 * sta2x11_vip_हटाओ_one - release device
 * @pdev: PCI device
 *
 * Unकरो everything करोne in .._init_one
 *
 * unरेजिस्टर video device
 * मुक्त पूर्णांकerrupt
 * unmap ioadresses
 * मुक्त memory
 * मुक्त GPIO pins
 */
अटल व्योम sta2x11_vip_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा sta2x11_vip *vip =
	    container_of(v4l2_dev, काष्ठा sta2x11_vip, v4l2_dev);

	sta2x11_vip_clear_रेजिस्टर(vip);

	video_set_drvdata(&vip->video_dev, शून्य);
	vb2_video_unरेजिस्टर_device(&vip->video_dev);
	मुक्त_irq(pdev->irq, vip);
	pci_disable_msi(pdev);
	pci_iounmap(pdev, vip->iomem);
	pci_release_regions(pdev);

	v4l2_device_unरेजिस्टर(&vip->v4l2_dev);

	vip_gpio_release(&pdev->dev, vip->config->pwr_pin,
			 vip->config->pwr_name);
	vip_gpio_release(&pdev->dev, vip->config->reset_pin,
			 vip->config->reset_name);

	kमुक्त(vip);
	/*
	 * करो not call pci_disable_device on sta2x11 because it अवरोध all
	 * other Bus masters on this EP
	 */
पूर्ण

/**
 * sta2x11_vip_suspend - set device पूर्णांकo घातer save mode
 * @dev_d: PCI device
 *
 * all relevant रेजिस्टरs are saved and an attempt to set a new state is made.
 *
 * वापस value: 0 always indicate success,
 * even अगर device could not be disabled. (workaround क्रम hardware problem)
 */
अटल पूर्णांक __maybe_unused sta2x11_vip_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev_d);
	काष्ठा sta2x11_vip *vip =
	    container_of(v4l2_dev, काष्ठा sta2x11_vip, v4l2_dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&vip->slock, flags);
	vip->रेजिस्टर_save_area[0] = reg_पढ़ो(vip, DVP_CTL);
	reg_ग_लिखो(vip, DVP_CTL, vip->रेजिस्टर_save_area[0] & DVP_CTL_DIS);
	vip->रेजिस्टर_save_area[SAVE_COUNT] = reg_पढ़ो(vip, DVP_ITM);
	reg_ग_लिखो(vip, DVP_ITM, 0);
	क्रम (i = 1; i < SAVE_COUNT; i++)
		vip->रेजिस्टर_save_area[i] = reg_पढ़ो(vip, 4 * i);
	क्रम (i = 0; i < AUX_COUNT; i++)
		vip->रेजिस्टर_save_area[SAVE_COUNT + IRQ_COUNT + i] =
		    reg_पढ़ो(vip, रेजिस्टरs_to_save[i]);
	spin_unlock_irqrestore(&vip->slock, flags);

	vip->disabled = 1;

	pr_info("VIP: suspend\n");
	वापस 0;
पूर्ण

/**
 * sta2x11_vip_resume - resume device operation
 * @dev_d : PCI device
 *
 * वापस value: 0, no error.
 *
 * other, could not set device to घातer on state.
 */
अटल पूर्णांक __maybe_unused sta2x11_vip_resume(काष्ठा device *dev_d)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev_d);
	काष्ठा sta2x11_vip *vip =
	    container_of(v4l2_dev, काष्ठा sta2x11_vip, v4l2_dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	pr_info("VIP: resume\n");

	vip->disabled = 0;

	spin_lock_irqsave(&vip->slock, flags);
	क्रम (i = 1; i < SAVE_COUNT; i++)
		reg_ग_लिखो(vip, 4 * i, vip->रेजिस्टर_save_area[i]);
	क्रम (i = 0; i < AUX_COUNT; i++)
		reg_ग_लिखो(vip, रेजिस्टरs_to_save[i],
			  vip->रेजिस्टर_save_area[SAVE_COUNT + IRQ_COUNT + i]);
	reg_ग_लिखो(vip, DVP_CTL, vip->रेजिस्टर_save_area[0]);
	reg_ग_लिखो(vip, DVP_ITM, vip->रेजिस्टर_save_area[SAVE_COUNT]);
	spin_unlock_irqrestore(&vip->slock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sta2x11_vip_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_STMICRO, PCI_DEVICE_ID_STMICRO_VIP)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(sta2x11_vip_pm_ops,
			 sta2x11_vip_suspend,
			 sta2x11_vip_resume);

अटल काष्ठा pci_driver sta2x11_vip_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = sta2x11_vip_init_one,
	.हटाओ = sta2x11_vip_हटाओ_one,
	.id_table = sta2x11_vip_pci_tbl,
	.driver.pm = &sta2x11_vip_pm_ops,
पूर्ण;

अटल पूर्णांक __init sta2x11_vip_init_module(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&sta2x11_vip_driver);
पूर्ण

अटल व्योम __निकास sta2x11_vip_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sta2x11_vip_driver);
पूर्ण

#अगर_घोषित MODULE
module_init(sta2x11_vip_init_module);
module_निकास(sta2x11_vip_निकास_module);
#अन्यथा
late_initcall_sync(sta2x11_vip_init_module);
#पूर्ण_अगर

MODULE_DESCRIPTION("STA2X11 Video Input Port driver");
MODULE_AUTHOR("Wind River");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, sta2x11_vip_pci_tbl);
