<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Video Output Unit (VOU) driver
 *
 * Copyright (C) 2010, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>

#समावेश <media/drv-पूर्णांकf/sh_vou.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

/* Mirror addresses are not available क्रम all रेजिस्टरs */
#घोषणा VOUER	0
#घोषणा VOUCR	4
#घोषणा VOUSTR	8
#घोषणा VOUVCR	0xc
#घोषणा VOUISR	0x10
#घोषणा VOUBCR	0x14
#घोषणा VOUDPR	0x18
#घोषणा VOUDSR	0x1c
#घोषणा VOUVPR	0x20
#घोषणा VOUIR	0x24
#घोषणा VOUSRR	0x28
#घोषणा VOUMSR	0x2c
#घोषणा VOUHIR	0x30
#घोषणा VOUDFR	0x34
#घोषणा VOUAD1R	0x38
#घोषणा VOUAD2R	0x3c
#घोषणा VOUAIR	0x40
#घोषणा VOUSWR	0x44
#घोषणा VOURCR	0x48
#घोषणा VOURPR	0x50

क्रमागत sh_vou_status अणु
	SH_VOU_IDLE,
	SH_VOU_INITIALISING,
	SH_VOU_RUNNING,
पूर्ण;

#घोषणा VOU_MIN_IMAGE_WIDTH	16
#घोषणा VOU_MAX_IMAGE_WIDTH	720
#घोषणा VOU_MIN_IMAGE_HEIGHT	16

काष्ठा sh_vou_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत काष्ठा
sh_vou_buffer *to_sh_vou_buffer(काष्ठा vb2_v4l2_buffer *vb2)
अणु
	वापस container_of(vb2, काष्ठा sh_vou_buffer, vb);
पूर्ण

काष्ठा sh_vou_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा sh_vou_pdata *pdata;
	spinlock_t lock;
	व्योम __iomem *base;
	/* State inक्रमmation */
	काष्ठा v4l2_pix_क्रमmat pix;
	काष्ठा v4l2_rect rect;
	काष्ठा list_head buf_list;
	v4l2_std_id std;
	पूर्णांक pix_idx;
	काष्ठा vb2_queue queue;
	काष्ठा sh_vou_buffer *active;
	क्रमागत sh_vou_status status;
	अचिन्हित sequence;
	काष्ठा mutex fop_lock;
पूर्ण;

/* Register access routines क्रम sides A, B and mirror addresses */
अटल व्योम sh_vou_reg_a_ग_लिखो(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
			       u32 value)
अणु
	__raw_ग_लिखोl(value, vou_dev->base + reg);
पूर्ण

अटल व्योम sh_vou_reg_ab_ग_लिखो(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
				u32 value)
अणु
	__raw_ग_लिखोl(value, vou_dev->base + reg);
	__raw_ग_लिखोl(value, vou_dev->base + reg + 0x1000);
पूर्ण

अटल व्योम sh_vou_reg_m_ग_लिखो(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
			       u32 value)
अणु
	__raw_ग_लिखोl(value, vou_dev->base + reg + 0x2000);
पूर्ण

अटल u32 sh_vou_reg_a_पढ़ो(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(vou_dev->base + reg);
पूर्ण

अटल व्योम sh_vou_reg_a_set(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
			     u32 value, u32 mask)
अणु
	u32 old = __raw_पढ़ोl(vou_dev->base + reg);

	value = (value & mask) | (old & ~mask);
	__raw_ग_लिखोl(value, vou_dev->base + reg);
पूर्ण

अटल व्योम sh_vou_reg_b_set(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
			     u32 value, u32 mask)
अणु
	sh_vou_reg_a_set(vou_dev, reg + 0x1000, value, mask);
पूर्ण

अटल व्योम sh_vou_reg_ab_set(काष्ठा sh_vou_device *vou_dev, अचिन्हित पूर्णांक reg,
			      u32 value, u32 mask)
अणु
	sh_vou_reg_a_set(vou_dev, reg, value, mask);
	sh_vou_reg_b_set(vou_dev, reg, value, mask);
पूर्ण

काष्ठा sh_vou_fmt अणु
	u32		pfmt;
	अचिन्हित अक्षर	bpp;
	अचिन्हित अक्षर	bpl;
	अचिन्हित अक्षर	rgb;
	अचिन्हित अक्षर	yf;
	अचिन्हित अक्षर	pkf;
पूर्ण;

/* Further pixel क्रमmats can be added */
अटल काष्ठा sh_vou_fmt vou_fmt[] = अणु
	अणु
		.pfmt	= V4L2_PIX_FMT_NV12,
		.bpp	= 12,
		.bpl	= 1,
		.yf	= 0,
		.rgb	= 0,
	पूर्ण,
	अणु
		.pfmt	= V4L2_PIX_FMT_NV16,
		.bpp	= 16,
		.bpl	= 1,
		.yf	= 1,
		.rgb	= 0,
	पूर्ण,
	अणु
		.pfmt	= V4L2_PIX_FMT_RGB24,
		.bpp	= 24,
		.bpl	= 3,
		.pkf	= 2,
		.rgb	= 1,
	पूर्ण,
	अणु
		.pfmt	= V4L2_PIX_FMT_RGB565,
		.bpp	= 16,
		.bpl	= 2,
		.pkf	= 3,
		.rgb	= 1,
	पूर्ण,
	अणु
		.pfmt	= V4L2_PIX_FMT_RGB565X,
		.bpp	= 16,
		.bpl	= 2,
		.pkf	= 3,
		.rgb	= 1,
	पूर्ण,
पूर्ण;

अटल व्योम sh_vou_schedule_next(काष्ठा sh_vou_device *vou_dev,
				 काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	dma_addr_t addr1, addr2;

	addr1 = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);
	चयन (vou_dev->pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
		addr2 = addr1 + vou_dev->pix.width * vou_dev->pix.height;
		अवरोध;
	शेष:
		addr2 = 0;
	पूर्ण

	sh_vou_reg_m_ग_लिखो(vou_dev, VOUAD1R, addr1);
	sh_vou_reg_m_ग_लिखो(vou_dev, VOUAD2R, addr2);
पूर्ण

अटल व्योम sh_vou_stream_config(काष्ठा sh_vou_device *vou_dev)
अणु
	अचिन्हित पूर्णांक row_coeff;
#अगर_घोषित __LITTLE_ENDIAN
	u32 dataswap = 7;
#अन्यथा
	u32 dataswap = 0;
#पूर्ण_अगर

	चयन (vou_dev->pix.pixelक्रमmat) अणु
	शेष:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
		row_coeff = 1;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		dataswap ^= 1;
		fallthrough;
	हाल V4L2_PIX_FMT_RGB565X:
		row_coeff = 2;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		row_coeff = 3;
		अवरोध;
	पूर्ण

	sh_vou_reg_a_ग_लिखो(vou_dev, VOUSWR, dataswap);
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUAIR, vou_dev->pix.width * row_coeff);
पूर्ण

/* Locking: caller holds fop_lock mutex */
अटल पूर्णांक sh_vou_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा sh_vou_device *vou_dev = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *pix = &vou_dev->pix;
	पूर्णांक bytes_per_line = vou_fmt[vou_dev->pix_idx].bpp * pix->width / 8;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	अगर (*nplanes)
		वापस sizes[0] < pix->height * bytes_per_line ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = pix->height * bytes_per_line;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sh_vou_device *vou_dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_pix_क्रमmat *pix = &vou_dev->pix;
	अचिन्हित bytes_per_line = vou_fmt[vou_dev->pix_idx].bpp * pix->width / 8;
	अचिन्हित size = pix->height * bytes_per_line;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	अगर (vb2_plane_size(vb, 0) < size) अणु
		/* User buffer too small */
		dev_warn(vou_dev->v4l2_dev.dev, "buffer too small (%lu < %u)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	वापस 0;
पूर्ण

/* Locking: caller holds fop_lock mutex and vq->irqlock spinlock */
अटल व्योम sh_vou_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा sh_vou_device *vou_dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा sh_vou_buffer *shbuf = to_sh_vou_buffer(vbuf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vou_dev->lock, flags);
	list_add_tail(&shbuf->list, &vou_dev->buf_list);
	spin_unlock_irqrestore(&vou_dev->lock, flags);
पूर्ण

अटल पूर्णांक sh_vou_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sh_vou_device *vou_dev = vb2_get_drv_priv(vq);
	काष्ठा sh_vou_buffer *buf, *node;
	पूर्णांक ret;

	vou_dev->sequence = 0;
	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0,
					 video, s_stream, 1);
	अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
		list_क्रम_each_entry_safe(buf, node, &vou_dev->buf_list, list) अणु
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
			list_del(&buf->list);
		पूर्ण
		vou_dev->active = शून्य;
		वापस ret;
	पूर्ण

	buf = list_entry(vou_dev->buf_list.next, काष्ठा sh_vou_buffer, list);

	vou_dev->active = buf;

	/* Start from side A: we use mirror addresses, so, set B */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOURPR, 1);
	dev_dbg(vou_dev->v4l2_dev.dev, "%s: first buffer status 0x%x\n",
		__func__, sh_vou_reg_a_पढ़ो(vou_dev, VOUSTR));
	sh_vou_schedule_next(vou_dev, &buf->vb);

	buf = list_entry(buf->list.next, काष्ठा sh_vou_buffer, list);

	/* Second buffer - initialise रेजिस्टर side B */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOURPR, 0);
	sh_vou_schedule_next(vou_dev, &buf->vb);

	/* Register side चयनing with frame VSYNC */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOURCR, 5);

	sh_vou_stream_config(vou_dev);
	/* Enable End-of-Frame (VSYNC) पूर्णांकerrupts */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOUIR, 0x10004);

	/* Two buffers on the queue - activate the hardware */
	vou_dev->status = SH_VOU_RUNNING;
	sh_vou_reg_a_ग_लिखो(vou_dev, VOUER, 0x107);
	वापस 0;
पूर्ण

अटल व्योम sh_vou_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sh_vou_device *vou_dev = vb2_get_drv_priv(vq);
	काष्ठा sh_vou_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0,
					 video, s_stream, 0);
	/* disable output */
	sh_vou_reg_a_set(vou_dev, VOUER, 0, 1);
	/* ...but the current frame will complete */
	sh_vou_reg_a_set(vou_dev, VOUIR, 0, 0x30000);
	msleep(50);
	spin_lock_irqsave(&vou_dev->lock, flags);
	list_क्रम_each_entry_safe(buf, node, &vou_dev->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&buf->list);
	पूर्ण
	vou_dev->active = शून्य;
	spin_unlock_irqrestore(&vou_dev->lock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops sh_vou_qops = अणु
	.queue_setup		= sh_vou_queue_setup,
	.buf_prepare		= sh_vou_buf_prepare,
	.buf_queue		= sh_vou_buf_queue,
	.start_streaming	= sh_vou_start_streaming,
	.stop_streaming		= sh_vou_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/* Video IOCTLs */
अटल पूर्णांक sh_vou_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	strscpy(cap->card, "SuperH VOU", माप(cap->card));
	strscpy(cap->driver, "sh-vou", माप(cap->driver));
	strscpy(cap->bus_info, "platform:sh-vou", माप(cap->bus_info));
	वापस 0;
पूर्ण

/* Enumerate क्रमmats, that the device can accept from the user */
अटल पूर्णांक sh_vou_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	अगर (fmt->index >= ARRAY_SIZE(vou_fmt))
		वापस -EINVAL;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	fmt->pixelक्रमmat = vou_fmt[fmt->index].pfmt;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	fmt->fmt.pix = vou_dev->pix;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर vou_scale_h_num[] = अणु1, 9, 2, 9, 4पूर्ण;
अटल स्थिर अचिन्हित अक्षर vou_scale_h_den[] = अणु1, 8, 1, 4, 1पूर्ण;
अटल स्थिर अचिन्हित अक्षर vou_scale_h_fld[] = अणु0, 2, 1, 3पूर्ण;
अटल स्थिर अचिन्हित अक्षर vou_scale_v_num[] = अणु1, 2, 4पूर्ण;
अटल स्थिर अचिन्हित अक्षर vou_scale_v_den[] = अणु1, 1, 1पूर्ण;
अटल स्थिर अचिन्हित अक्षर vou_scale_v_fld[] = अणु0, 1पूर्ण;

अटल व्योम sh_vou_configure_geometry(काष्ठा sh_vou_device *vou_dev,
				      पूर्णांक pix_idx, पूर्णांक w_idx, पूर्णांक h_idx)
अणु
	काष्ठा sh_vou_fmt *fmt = vou_fmt + pix_idx;
	अचिन्हित पूर्णांक black_left, black_top, width_max,
		frame_in_height, frame_out_height, frame_out_top;
	काष्ठा v4l2_rect *rect = &vou_dev->rect;
	काष्ठा v4l2_pix_क्रमmat *pix = &vou_dev->pix;
	u32 vouvcr = 0, dsr_h, dsr_v;

	अगर (vou_dev->std & V4L2_STD_525_60) अणु
		width_max = 858;
		/* height_max = 262; */
	पूर्ण अन्यथा अणु
		width_max = 864;
		/* height_max = 312; */
	पूर्ण

	frame_in_height = pix->height / 2;
	frame_out_height = rect->height / 2;
	frame_out_top = rect->top / 2;

	/*
	 * Cropping scheme: max useful image is 720x480, and the total video
	 * area is 858x525 (NTSC) or 864x625 (PAL). AK8813 / 8814 starts
	 * sampling data beginning with fixed 276th (NTSC) / 288th (PAL) घड़ी,
	 * of which the first 33 / 25 घड़ीs HSYNC must be held active. This
	 * has to be configured in CR[HW]. 1 pixel equals 2 घड़ी periods.
	 * This gives CR[HW] = 16 / 12, VPR[HVP] = 138 / 144, which gives
	 * exactly 858 - 138 = 864 - 144 = 720! We call the out-of-display area,
	 * beyond DSR, specअगरied on the left and top by the VPR रेजिस्टर "black
	 * pixels" and out-of-image area (DPR) "background pixels." We fix VPR
	 * at 138 / 144 : 20, because that's the HSYNC timing, that our first
	 * client requires, and that's exactly what leaves us 720 pixels क्रम the
	 * image; we leave VPR[VVP] at शेष 20 क्रम now, because the client
	 * करोesn't seem to have any special requirements क्रम it. Otherwise we
	 * could also set it to max - 240 = 22 / 72. Thus VPR depends only on
	 * the selected standard, and DPR and DSR are selected according to
	 * cropping. Q: how करोes the client detect the first valid line? Does
	 * HSYNC stay inactive during invalid (black) lines?
	 */
	black_left = width_max - VOU_MAX_IMAGE_WIDTH;
	black_top = 20;

	dsr_h = rect->width + rect->left;
	dsr_v = frame_out_height + frame_out_top;

	dev_dbg(vou_dev->v4l2_dev.dev,
		"image %ux%u, black %u:%u, offset %u:%u, display %ux%u\n",
		pix->width, frame_in_height, black_left, black_top,
		rect->left, frame_out_top, dsr_h, dsr_v);

	/* VOUISR height - half of a frame height in frame mode */
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUISR, (pix->width << 16) | frame_in_height);
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUVPR, (black_left << 16) | black_top);
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUDPR, (rect->left << 16) | frame_out_top);
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUDSR, (dsr_h << 16) | dsr_v);

	/*
	 * अगर necessary, we could set VOUHIR to
	 * max(black_left + dsr_h, width_max) here
	 */

	अगर (w_idx)
		vouvcr |= (1 << 15) | (vou_scale_h_fld[w_idx - 1] << 4);
	अगर (h_idx)
		vouvcr |= (1 << 14) | vou_scale_v_fld[h_idx - 1];

	dev_dbg(vou_dev->v4l2_dev.dev, "0x%08x: scaling 0x%x\n",
		fmt->pfmt, vouvcr);

	/* To produce a colour bar क्रम testing set bit 23 of VOUVCR */
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUVCR, vouvcr);
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUDFR,
			    fmt->pkf | (fmt->yf << 8) | (fmt->rgb << 16));
पूर्ण

काष्ठा sh_vou_geometry अणु
	काष्ठा v4l2_rect output;
	अचिन्हित पूर्णांक in_width;
	अचिन्हित पूर्णांक in_height;
	पूर्णांक scale_idx_h;
	पूर्णांक scale_idx_v;
पूर्ण;

/*
 * Find input geometry, that we can use to produce output, बंदst to the
 * requested rectangle, using VOU scaling
 */
अटल व्योम vou_adjust_input(काष्ठा sh_vou_geometry *geo, v4l2_std_id std)
अणु
	/* The compiler cannot know, that best and idx will indeed be set */
	अचिन्हित पूर्णांक best_err = अच_पूर्णांक_उच्च, best = 0, img_height_max;
	पूर्णांक i, idx = 0;

	अगर (std & V4L2_STD_525_60)
		img_height_max = 480;
	अन्यथा
		img_height_max = 576;

	/* Image width must be a multiple of 4 */
	v4l_bound_align_image(&geo->in_width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &geo->in_height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	/* Select scales to come as बंद as possible to the output image */
	क्रम (i = ARRAY_SIZE(vou_scale_h_num) - 1; i >= 0; i--) अणु
		अचिन्हित पूर्णांक err;
		अचिन्हित पूर्णांक found = geo->output.width * vou_scale_h_den[i] /
			vou_scale_h_num[i];

		अगर (found > VOU_MAX_IMAGE_WIDTH)
			/* scales increase */
			अवरोध;

		err = असल(found - geo->in_width);
		अगर (err < best_err) अणु
			best_err = err;
			idx = i;
			best = found;
		पूर्ण
		अगर (!err)
			अवरोध;
	पूर्ण

	geo->in_width = best;
	geo->scale_idx_h = idx;

	best_err = अच_पूर्णांक_उच्च;

	/* This loop can be replaced with one भागision */
	क्रम (i = ARRAY_SIZE(vou_scale_v_num) - 1; i >= 0; i--) अणु
		अचिन्हित पूर्णांक err;
		अचिन्हित पूर्णांक found = geo->output.height * vou_scale_v_den[i] /
			vou_scale_v_num[i];

		अगर (found > img_height_max)
			/* scales increase */
			अवरोध;

		err = असल(found - geo->in_height);
		अगर (err < best_err) अणु
			best_err = err;
			idx = i;
			best = found;
		पूर्ण
		अगर (!err)
			अवरोध;
	पूर्ण

	geo->in_height = best;
	geo->scale_idx_v = idx;
पूर्ण

/*
 * Find output geometry, that we can produce, using VOU scaling, बंदst to
 * the requested rectangle
 */
अटल व्योम vou_adjust_output(काष्ठा sh_vou_geometry *geo, v4l2_std_id std)
अणु
	अचिन्हित पूर्णांक best_err = अच_पूर्णांक_उच्च, best = geo->in_width,
		width_max, height_max, img_height_max;
	पूर्णांक i, idx_h = 0, idx_v = 0;

	अगर (std & V4L2_STD_525_60) अणु
		width_max = 858;
		height_max = 262 * 2;
		img_height_max = 480;
	पूर्ण अन्यथा अणु
		width_max = 864;
		height_max = 312 * 2;
		img_height_max = 576;
	पूर्ण

	/* Select scales to come as बंद as possible to the output image */
	क्रम (i = 0; i < ARRAY_SIZE(vou_scale_h_num); i++) अणु
		अचिन्हित पूर्णांक err;
		अचिन्हित पूर्णांक found = geo->in_width * vou_scale_h_num[i] /
			vou_scale_h_den[i];

		अगर (found > VOU_MAX_IMAGE_WIDTH)
			/* scales increase */
			अवरोध;

		err = असल(found - geo->output.width);
		अगर (err < best_err) अणु
			best_err = err;
			idx_h = i;
			best = found;
		पूर्ण
		अगर (!err)
			अवरोध;
	पूर्ण

	geo->output.width = best;
	geo->scale_idx_h = idx_h;
	अगर (geo->output.left + best > width_max)
		geo->output.left = width_max - best;

	pr_debug("%s(): W %u * %u/%u = %u\n", __func__, geo->in_width,
		 vou_scale_h_num[idx_h], vou_scale_h_den[idx_h], best);

	best_err = अच_पूर्णांक_उच्च;

	/* This loop can be replaced with one भागision */
	क्रम (i = 0; i < ARRAY_SIZE(vou_scale_v_num); i++) अणु
		अचिन्हित पूर्णांक err;
		अचिन्हित पूर्णांक found = geo->in_height * vou_scale_v_num[i] /
			vou_scale_v_den[i];

		अगर (found > img_height_max)
			/* scales increase */
			अवरोध;

		err = असल(found - geo->output.height);
		अगर (err < best_err) अणु
			best_err = err;
			idx_v = i;
			best = found;
		पूर्ण
		अगर (!err)
			अवरोध;
	पूर्ण

	geo->output.height = best;
	geo->scale_idx_v = idx_v;
	अगर (geo->output.top + best > height_max)
		geo->output.top = height_max - best;

	pr_debug("%s(): H %u * %u/%u = %u\n", __func__, geo->in_height,
		 vou_scale_v_num[idx_v], vou_scale_v_den[idx_v], best);
पूर्ण

अटल पूर्णांक sh_vou_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &fmt->fmt.pix;
	अचिन्हित पूर्णांक img_height_max;
	पूर्णांक pix_idx;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	pix->field = V4L2_FIELD_INTERLACED;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->ycbcr_enc = pix->quantization = 0;

	क्रम (pix_idx = 0; pix_idx < ARRAY_SIZE(vou_fmt); pix_idx++)
		अगर (vou_fmt[pix_idx].pfmt == pix->pixelक्रमmat)
			अवरोध;

	अगर (pix_idx == ARRAY_SIZE(vou_fmt))
		वापस -EINVAL;

	अगर (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	अन्यथा
		img_height_max = 576;

	v4l_bound_align_image(&pix->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 2,
			      &pix->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);
	pix->bytesperline = pix->width * vou_fmt[pix_idx].bpl;
	pix->sizeimage = pix->height * ((pix->width * vou_fmt[pix_idx].bpp) >> 3);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_set_fmt_vid_out(काष्ठा sh_vou_device *vou_dev,
				काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	अचिन्हित पूर्णांक img_height_max;
	काष्ठा sh_vou_geometry geo;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		/* Revisit: is this the correct code? */
		.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.क्रमmat.field = V4L2_FIELD_INTERLACED,
		.क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mbfmt = &क्रमmat.क्रमmat;
	पूर्णांक pix_idx;
	पूर्णांक ret;

	अगर (vb2_is_busy(&vou_dev->queue))
		वापस -EBUSY;

	क्रम (pix_idx = 0; pix_idx < ARRAY_SIZE(vou_fmt); pix_idx++)
		अगर (vou_fmt[pix_idx].pfmt == pix->pixelक्रमmat)
			अवरोध;

	geo.in_width = pix->width;
	geo.in_height = pix->height;
	geo.output = vou_dev->rect;

	vou_adjust_output(&geo, vou_dev->std);

	mbfmt->width = geo.output.width;
	mbfmt->height = geo.output.height;
	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
					 set_fmt, शून्य, &क्रमmat);
	/* Must be implemented, so, करोn't check क्रम -ENOIOCTLCMD */
	अगर (ret < 0)
		वापस ret;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s(): %ux%u -> %ux%u\n", __func__,
		geo.output.width, geo.output.height, mbfmt->width, mbfmt->height);

	अगर (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	अन्यथा
		img_height_max = 576;

	/* Sanity checks */
	अगर ((अचिन्हित)mbfmt->width > VOU_MAX_IMAGE_WIDTH ||
	    (अचिन्हित)mbfmt->height > img_height_max ||
	    mbfmt->code != MEDIA_BUS_FMT_YUYV8_2X8)
		वापस -EIO;

	अगर (mbfmt->width != geo.output.width ||
	    mbfmt->height != geo.output.height) अणु
		geo.output.width = mbfmt->width;
		geo.output.height = mbfmt->height;

		vou_adjust_input(&geo, vou_dev->std);
	पूर्ण

	/* We tried to preserve output rectangle, but it could have changed */
	vou_dev->rect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s(): %ux%u\n", __func__,
		pix->width, pix->height);

	vou_dev->pix_idx = pix_idx;

	vou_dev->pix = *pix;

	sh_vou_configure_geometry(vou_dev, pix_idx,
				  geo.scale_idx_h, geo.scale_idx_v);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	पूर्णांक ret = sh_vou_try_fmt_vid_out(file, priv, fmt);

	अगर (ret)
		वापस ret;
	वापस sh_vou_set_fmt_vid_out(vou_dev, &fmt->fmt.pix);
पूर्ण

अटल पूर्णांक sh_vou_क्रमागत_output(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_output *a)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	अगर (a->index)
		वापस -EINVAL;
	strscpy(a->name, "Video Out", माप(a->name));
	a->type = V4L2_OUTPUT_TYPE_ANALOG;
	a->std = vou_dev->vdev.tvnorms;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_g_output(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_s_output(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल u32 sh_vou_ntsc_mode(क्रमागत sh_vou_bus_fmt bus_fmt)
अणु
	चयन (bus_fmt) अणु
	शेष:
		pr_warn("%s(): Invalid bus-format code %d, using default 8-bit\n",
			__func__, bus_fmt);
		fallthrough;
	हाल SH_VOU_BUS_8BIT:
		वापस 1;
	हाल SH_VOU_BUS_16BIT:
		वापस 0;
	हाल SH_VOU_BUS_BT656:
		वापस 3;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_vou_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std_id)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s(): 0x%llx\n", __func__, std_id);

	अगर (std_id == vou_dev->std)
		वापस 0;

	अगर (vb2_is_busy(&vou_dev->queue))
		वापस -EBUSY;

	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, video,
					 s_std_output, std_id);
	/* Shall we जारी, अगर the subdev करोesn't support .s_std_output()? */
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	vou_dev->rect.top = vou_dev->rect.left = 0;
	vou_dev->rect.width = VOU_MAX_IMAGE_WIDTH;
	अगर (std_id & V4L2_STD_525_60) अणु
		sh_vou_reg_ab_set(vou_dev, VOUCR,
			sh_vou_ntsc_mode(vou_dev->pdata->bus_fmt) << 29, 7 << 29);
		vou_dev->rect.height = 480;
	पूर्ण अन्यथा अणु
		sh_vou_reg_ab_set(vou_dev, VOUCR, 5 << 29, 7 << 29);
		vou_dev->rect.height = 576;
	पूर्ण

	vou_dev->pix.width = vou_dev->rect.width;
	vou_dev->pix.height = vou_dev->rect.height;
	vou_dev->pix.bytesperline =
		vou_dev->pix.width * vou_fmt[vou_dev->pix_idx].bpl;
	vou_dev->pix.sizeimage = vou_dev->pix.height *
		((vou_dev->pix.width * vou_fmt[vou_dev->pix_idx].bpp) >> 3);
	vou_dev->std = std_id;
	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	*std = vou_dev->std;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	pr_info("VOUER:   0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUER));
	pr_info("VOUCR:   0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUCR));
	pr_info("VOUSTR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUSTR));
	pr_info("VOUVCR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUVCR));
	pr_info("VOUISR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUISR));
	pr_info("VOUBCR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUBCR));
	pr_info("VOUDPR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUDPR));
	pr_info("VOUDSR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUDSR));
	pr_info("VOUVPR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUVPR));
	pr_info("VOUIR:   0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUIR));
	pr_info("VOUSRR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUSRR));
	pr_info("VOUMSR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUMSR));
	pr_info("VOUHIR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUHIR));
	pr_info("VOUDFR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUDFR));
	pr_info("VOUAD1R: 0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUAD1R));
	pr_info("VOUAD2R: 0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUAD2R));
	pr_info("VOUAIR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUAIR));
	pr_info("VOUSWR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOUSWR));
	pr_info("VOURCR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOURCR));
	pr_info("VOURPR:  0x%08x\n", sh_vou_reg_a_पढ़ो(vou_dev, VOURPR));
	वापस 0;
पूर्ण

अटल पूर्णांक sh_vou_g_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_COMPOSE:
		sel->r = vou_dev->rect;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = VOU_MAX_IMAGE_WIDTH;
		अगर (vou_dev->std & V4L2_STD_525_60)
			sel->r.height = 480;
		अन्यथा
			sel->r.height = 576;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Assume a dull encoder, करो all the work ourselves. */
अटल पूर्णांक sh_vou_s_selection(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_selection *sel)
अणु
	काष्ठा v4l2_rect *rect = &sel->r;
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	काष्ठा v4l2_subdev_selection sd_sel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_COMPOSE,
	पूर्ण;
	काष्ठा v4l2_pix_क्रमmat *pix = &vou_dev->pix;
	काष्ठा sh_vou_geometry geo;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		/* Revisit: is this the correct code? */
		.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_2X8,
		.क्रमmat.field = V4L2_FIELD_INTERLACED,
		.क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M,
	पूर्ण;
	अचिन्हित पूर्णांक img_height_max;
	पूर्णांक ret;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    sel->target != V4L2_SEL_TGT_COMPOSE)
		वापस -EINVAL;

	अगर (vb2_is_busy(&vou_dev->queue))
		वापस -EBUSY;

	अगर (vou_dev->std & V4L2_STD_525_60)
		img_height_max = 480;
	अन्यथा
		img_height_max = 576;

	v4l_bound_align_image(&rect->width,
			      VOU_MIN_IMAGE_WIDTH, VOU_MAX_IMAGE_WIDTH, 1,
			      &rect->height,
			      VOU_MIN_IMAGE_HEIGHT, img_height_max, 1, 0);

	अगर (rect->width + rect->left > VOU_MAX_IMAGE_WIDTH)
		rect->left = VOU_MAX_IMAGE_WIDTH - rect->width;

	अगर (rect->height + rect->top > img_height_max)
		rect->top = img_height_max - rect->height;

	geo.output = *rect;
	geo.in_width = pix->width;
	geo.in_height = pix->height;

	/* Configure the encoder one-to-one, position at 0, ignore errors */
	sd_sel.r.width = geo.output.width;
	sd_sel.r.height = geo.output.height;
	/*
	 * We first issue a S_SELECTION, so that the subsequent S_FMT delivers the
	 * final encoder configuration.
	 */
	v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
				   set_selection, शून्य, &sd_sel);
	क्रमmat.क्रमmat.width = geo.output.width;
	क्रमmat.क्रमmat.height = geo.output.height;
	ret = v4l2_device_call_until_err(&vou_dev->v4l2_dev, 0, pad,
					 set_fmt, शून्य, &क्रमmat);
	/* Must be implemented, so, करोn't check क्रम -ENOIOCTLCMD */
	अगर (ret < 0)
		वापस ret;

	/* Sanity checks */
	अगर ((अचिन्हित)क्रमmat.क्रमmat.width > VOU_MAX_IMAGE_WIDTH ||
	    (अचिन्हित)क्रमmat.क्रमmat.height > img_height_max ||
	    क्रमmat.क्रमmat.code != MEDIA_BUS_FMT_YUYV8_2X8)
		वापस -EIO;

	geo.output.width = क्रमmat.क्रमmat.width;
	geo.output.height = क्रमmat.क्रमmat.height;

	/*
	 * No करोwn-scaling. According to the API, current call has precedence:
	 * https://linuxtv.org/करोwnloads/v4l-dvb-apis/uapi/v4l/crop.hपंचांगl#cropping-काष्ठाures
	 */
	vou_adjust_input(&geo, vou_dev->std);

	/* We tried to preserve output rectangle, but it could have changed */
	vou_dev->rect = geo.output;
	pix->width = geo.in_width;
	pix->height = geo.in_height;

	sh_vou_configure_geometry(vou_dev, vou_dev->pix_idx,
				  geo.scale_idx_h, geo.scale_idx_v);

	वापस 0;
पूर्ण

अटल irqवापस_t sh_vou_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_vou_device *vou_dev = dev_id;
	अटल अचिन्हित दीर्घ j;
	काष्ठा sh_vou_buffer *vb;
	अटल पूर्णांक cnt;
	u32 irq_status = sh_vou_reg_a_पढ़ो(vou_dev, VOUIR), masked;
	u32 vou_status = sh_vou_reg_a_पढ़ो(vou_dev, VOUSTR);

	अगर (!(irq_status & 0x300)) अणु
		अगर (prपूर्णांकk_समयd_ratelimit(&j, 500))
			dev_warn(vou_dev->v4l2_dev.dev, "IRQ status 0x%x!\n",
				 irq_status);
		वापस IRQ_NONE;
	पूर्ण

	spin_lock(&vou_dev->lock);
	अगर (!vou_dev->active || list_empty(&vou_dev->buf_list)) अणु
		अगर (prपूर्णांकk_समयd_ratelimit(&j, 500))
			dev_warn(vou_dev->v4l2_dev.dev,
				 "IRQ without active buffer: %x!\n", irq_status);
		/* Just ack: buf_release will disable further पूर्णांकerrupts */
		sh_vou_reg_a_set(vou_dev, VOUIR, 0, 0x300);
		spin_unlock(&vou_dev->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	masked = ~(0x300 & irq_status) & irq_status & 0x30304;
	dev_dbg(vou_dev->v4l2_dev.dev,
		"IRQ status 0x%x -> 0x%x, VOU status 0x%x, cnt %d\n",
		irq_status, masked, vou_status, cnt);

	cnt++;
	/* side = vou_status & 0x10000; */

	/* Clear only set पूर्णांकerrupts */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOUIR, masked);

	vb = vou_dev->active;
	अगर (list_is_singular(&vb->list)) अणु
		/* Keep cycling जबतक no next buffer is available */
		sh_vou_schedule_next(vou_dev, &vb->vb);
		spin_unlock(&vou_dev->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	list_del(&vb->list);

	vb->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb->vb.sequence = vou_dev->sequence++;
	vb->vb.field = V4L2_FIELD_INTERLACED;
	vb2_buffer_करोne(&vb->vb.vb2_buf, VB2_BUF_STATE_DONE);

	vou_dev->active = list_entry(vou_dev->buf_list.next,
				     काष्ठा sh_vou_buffer, list);

	अगर (list_is_singular(&vou_dev->buf_list)) अणु
		/* Keep cycling जबतक no next buffer is available */
		sh_vou_schedule_next(vou_dev, &vou_dev->active->vb);
	पूर्ण अन्यथा अणु
		काष्ठा sh_vou_buffer *new = list_entry(vou_dev->active->list.next,
						काष्ठा sh_vou_buffer, list);
		sh_vou_schedule_next(vou_dev, &new->vb);
	पूर्ण

	spin_unlock(&vou_dev->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sh_vou_hw_init(काष्ठा sh_vou_device *vou_dev)
अणु
	काष्ठा sh_vou_pdata *pdata = vou_dev->pdata;
	u32 voucr = sh_vou_ntsc_mode(pdata->bus_fmt) << 29;
	पूर्णांक i = 100;

	/* Disable all IRQs */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOUIR, 0);

	/* Reset VOU पूर्णांकerfaces - रेजिस्टरs unaffected */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOUSRR, 0x101);
	जबतक (--i && (sh_vou_reg_a_पढ़ो(vou_dev, VOUSRR) & 0x101))
		udelay(1);

	अगर (!i)
		वापस -ETIMEDOUT;

	dev_dbg(vou_dev->v4l2_dev.dev, "Reset took %dus\n", 100 - i);

	अगर (pdata->flags & SH_VOU_PCLK_FALLING)
		voucr |= 1 << 28;
	अगर (pdata->flags & SH_VOU_HSYNC_LOW)
		voucr |= 1 << 27;
	अगर (pdata->flags & SH_VOU_VSYNC_LOW)
		voucr |= 1 << 26;
	sh_vou_reg_ab_set(vou_dev, VOUCR, voucr, 0xfc000000);

	/* Manual रेजिस्टर side चयनing at first */
	sh_vou_reg_a_ग_लिखो(vou_dev, VOURCR, 4);
	/* Default - fixed HSYNC length, can be made configurable is required */
	sh_vou_reg_ab_ग_लिखो(vou_dev, VOUMSR, 0x800000);

	sh_vou_set_fmt_vid_out(vou_dev, &vou_dev->pix);

	वापस 0;
पूर्ण

/* File operations */
अटल पूर्णांक sh_vou_खोलो(काष्ठा file *file)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	पूर्णांक err;

	अगर (mutex_lock_पूर्णांकerruptible(&vou_dev->fop_lock))
		वापस -ERESTARTSYS;

	err = v4l2_fh_खोलो(file);
	अगर (err)
		जाओ करोne_खोलो;
	अगर (v4l2_fh_is_singular_file(file) &&
	    vou_dev->status == SH_VOU_INITIALISING) अणु
		/* First खोलो */
		pm_runसमय_get_sync(vou_dev->v4l2_dev.dev);
		err = sh_vou_hw_init(vou_dev);
		अगर (err < 0) अणु
			pm_runसमय_put(vou_dev->v4l2_dev.dev);
			v4l2_fh_release(file);
		पूर्ण अन्यथा अणु
			vou_dev->status = SH_VOU_IDLE;
		पूर्ण
	पूर्ण
करोne_खोलो:
	mutex_unlock(&vou_dev->fop_lock);
	वापस err;
पूर्ण

अटल पूर्णांक sh_vou_release(काष्ठा file *file)
अणु
	काष्ठा sh_vou_device *vou_dev = video_drvdata(file);
	bool is_last;

	mutex_lock(&vou_dev->fop_lock);
	is_last = v4l2_fh_is_singular_file(file);
	_vb2_fop_release(file, शून्य);
	अगर (is_last) अणु
		/* Last बंद */
		vou_dev->status = SH_VOU_INITIALISING;
		sh_vou_reg_a_set(vou_dev, VOUER, 0, 0x101);
		pm_runसमय_put(vou_dev->v4l2_dev.dev);
	पूर्ण
	mutex_unlock(&vou_dev->fop_lock);
	वापस 0;
पूर्ण

/* sh_vou display ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops sh_vou_ioctl_ops = अणु
	.vidioc_querycap		= sh_vou_querycap,
	.vidioc_क्रमागत_fmt_vid_out	= sh_vou_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= sh_vou_g_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= sh_vou_s_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= sh_vou_try_fmt_vid_out,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_g_output		= sh_vou_g_output,
	.vidioc_s_output		= sh_vou_s_output,
	.vidioc_क्रमागत_output		= sh_vou_क्रमागत_output,
	.vidioc_s_std			= sh_vou_s_std,
	.vidioc_g_std			= sh_vou_g_std,
	.vidioc_g_selection		= sh_vou_g_selection,
	.vidioc_s_selection		= sh_vou_s_selection,
	.vidioc_log_status		= sh_vou_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations sh_vou_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sh_vou_खोलो,
	.release	= sh_vou_release,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll,
	.ग_लिखो		= vb2_fop_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा video_device sh_vou_video_ढाँचा = अणु
	.name		= "sh_vou",
	.fops		= &sh_vou_fops,
	.ioctl_ops	= &sh_vou_ioctl_ops,
	.tvnorms	= V4L2_STD_525_60, /* PAL only supported in 8-bit non-bt656 mode */
	.vfl_dir	= VFL_सूची_TX,
	.device_caps	= V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_READWRITE |
			  V4L2_CAP_STREAMING,
पूर्ण;

अटल पूर्णांक sh_vou_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_vou_pdata *vou_pdata = pdev->dev.platक्रमm_data;
	काष्ठा v4l2_rect *rect;
	काष्ठा v4l2_pix_क्रमmat *pix;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा video_device *vdev;
	काष्ठा sh_vou_device *vou_dev;
	काष्ठा resource *reg_res;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा vb2_queue *q;
	पूर्णांक irq, ret;

	reg_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);

	अगर (!vou_pdata || !reg_res || irq <= 0) अणु
		dev_err(&pdev->dev, "Insufficient VOU platform information.\n");
		वापस -ENODEV;
	पूर्ण

	vou_dev = devm_kzalloc(&pdev->dev, माप(*vou_dev), GFP_KERNEL);
	अगर (!vou_dev)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&vou_dev->buf_list);
	spin_lock_init(&vou_dev->lock);
	mutex_init(&vou_dev->fop_lock);
	vou_dev->pdata = vou_pdata;
	vou_dev->status = SH_VOU_INITIALISING;
	vou_dev->pix_idx = 1;

	rect = &vou_dev->rect;
	pix = &vou_dev->pix;

	/* Fill in शेषs */
	vou_dev->std		= V4L2_STD_NTSC_M;
	rect->left		= 0;
	rect->top		= 0;
	rect->width		= VOU_MAX_IMAGE_WIDTH;
	rect->height		= 480;
	pix->width		= VOU_MAX_IMAGE_WIDTH;
	pix->height		= 480;
	pix->pixelक्रमmat	= V4L2_PIX_FMT_NV16;
	pix->field		= V4L2_FIELD_INTERLACED;
	pix->bytesperline	= VOU_MAX_IMAGE_WIDTH;
	pix->sizeimage		= VOU_MAX_IMAGE_WIDTH * 2 * 480;
	pix->colorspace		= V4L2_COLORSPACE_SMPTE170M;

	vou_dev->base = devm_ioremap_resource(&pdev->dev, reg_res);
	अगर (IS_ERR(vou_dev->base))
		वापस PTR_ERR(vou_dev->base);

	ret = devm_request_irq(&pdev->dev, irq, sh_vou_isr, 0, "vou", vou_dev);
	अगर (ret < 0)
		वापस ret;

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &vou_dev->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Error registering v4l2 device\n");
		वापस ret;
	पूर्ण

	vdev = &vou_dev->vdev;
	*vdev = sh_vou_video_ढाँचा;
	अगर (vou_pdata->bus_fmt == SH_VOU_BUS_8BIT)
		vdev->tvnorms |= V4L2_STD_PAL;
	vdev->v4l2_dev = &vou_dev->v4l2_dev;
	vdev->release = video_device_release_empty;
	vdev->lock = &vou_dev->fop_lock;

	video_set_drvdata(vdev, vou_dev);

	/* Initialize the vb2 queue */
	q = &vou_dev->queue;
	q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WRITE;
	q->drv_priv = vou_dev;
	q->buf_काष्ठा_size = माप(काष्ठा sh_vou_buffer);
	q->ops = &sh_vou_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 2;
	q->lock = &vou_dev->fop_lock;
	q->dev = &pdev->dev;
	ret = vb2_queue_init(q);
	अगर (ret)
		जाओ ei2cgadap;

	vdev->queue = q;
	INIT_LIST_HEAD(&vou_dev->buf_list);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_resume(&pdev->dev);

	i2c_adap = i2c_get_adapter(vou_pdata->i2c_adap);
	अगर (!i2c_adap) अणु
		ret = -ENODEV;
		जाओ ei2cgadap;
	पूर्ण

	ret = sh_vou_hw_init(vou_dev);
	अगर (ret < 0)
		जाओ ereset;

	subdev = v4l2_i2c_new_subdev_board(&vou_dev->v4l2_dev, i2c_adap,
			vou_pdata->board_info, शून्य);
	अगर (!subdev) अणु
		ret = -ENOMEM;
		जाओ ei2cnd;
	पूर्ण

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		जाओ evregdev;

	वापस 0;

evregdev:
ei2cnd:
ereset:
	i2c_put_adapter(i2c_adap);
ei2cgadap:
	pm_runसमय_disable(&pdev->dev);
	v4l2_device_unरेजिस्टर(&vou_dev->v4l2_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_vou_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sh_vou_device *vou_dev = container_of(v4l2_dev,
						काष्ठा sh_vou_device, v4l2_dev);
	काष्ठा v4l2_subdev *sd = list_entry(v4l2_dev->subdevs.next,
					    काष्ठा v4l2_subdev, list);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	pm_runसमय_disable(&pdev->dev);
	video_unरेजिस्टर_device(&vou_dev->vdev);
	i2c_put_adapter(client->adapter);
	v4l2_device_unरेजिस्टर(&vou_dev->v4l2_dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sh_vou = अणु
	.हटाओ  = sh_vou_हटाओ,
	.driver  = अणु
		.name	= "sh-vou",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(sh_vou, sh_vou_probe);

MODULE_DESCRIPTION("SuperH VOU driver");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.1.0");
MODULE_ALIAS("platform:sh-vou");
