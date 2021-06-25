<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "solo6x10.h"
#समावेश "solo6x10-tw28.h"

/* Image size is two fields, SOLO_HW_BPL is one horizontal line in hardware */
#घोषणा SOLO_HW_BPL		2048
#घोषणा solo_vlines(__solo)	(__solo->video_vsize * 2)
#घोषणा solo_image_size(__solo) (solo_bytesperline(__solo) * \
				 solo_vlines(__solo))
#घोषणा solo_bytesperline(__solo) (__solo->video_hsize * 2)

#घोषणा MIN_VID_BUFFERS		2

अटल अंतरभूत व्योम erase_on(काष्ठा solo_dev *solo_dev)
अणु
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_DISP_ERASE, SOLO_VO_DISP_ERASE_ON);
	solo_dev->erasing = 1;
	solo_dev->frame_blank = 0;
पूर्ण

अटल अंतरभूत पूर्णांक erase_off(काष्ठा solo_dev *solo_dev)
अणु
	अगर (!solo_dev->erasing)
		वापस 0;

	/* First समय around, निश्चित erase off */
	अगर (!solo_dev->frame_blank)
		solo_reg_ग_लिखो(solo_dev, SOLO_VO_DISP_ERASE, 0);
	/* Keep the erasing flag on क्रम 8 frames minimum */
	अगर (solo_dev->frame_blank++ >= 8)
		solo_dev->erasing = 0;

	वापस 1;
पूर्ण

व्योम solo_video_in_isr(काष्ठा solo_dev *solo_dev)
अणु
	wake_up_पूर्णांकerruptible_all(&solo_dev->disp_thपढ़ो_रुको);
पूर्ण

अटल व्योम solo_win_setup(काष्ठा solo_dev *solo_dev, u8 ch,
			   पूर्णांक sx, पूर्णांक sy, पूर्णांक ex, पूर्णांक ey, पूर्णांक scale)
अणु
	अगर (ch >= solo_dev->nr_chans)
		वापस;

	/* Here, we just keep winकरोw/channel the same */
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_CTRL0(ch),
		       SOLO_VI_WIN_CHANNEL(ch) |
		       SOLO_VI_WIN_SX(sx) |
		       SOLO_VI_WIN_EX(ex) |
		       SOLO_VI_WIN_SCALE(scale));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_CTRL1(ch),
		       SOLO_VI_WIN_SY(sy) |
		       SOLO_VI_WIN_EY(ey));
पूर्ण

अटल पूर्णांक solo_v4l2_ch_ext_4up(काष्ठा solo_dev *solo_dev, u8 idx, पूर्णांक on)
अणु
	u8 ch = idx * 4;

	अगर (ch >= solo_dev->nr_chans)
		वापस -EINVAL;

	अगर (!on) अणु
		u8 i;

		क्रम (i = ch; i < ch + 4; i++)
			solo_win_setup(solo_dev, i, solo_dev->video_hsize,
				       solo_vlines(solo_dev),
				       solo_dev->video_hsize,
				       solo_vlines(solo_dev), 0);
		वापस 0;
	पूर्ण

	/* Row 1 */
	solo_win_setup(solo_dev, ch, 0, 0, solo_dev->video_hsize / 2,
		       solo_vlines(solo_dev) / 2, 3);
	solo_win_setup(solo_dev, ch + 1, solo_dev->video_hsize / 2, 0,
		       solo_dev->video_hsize, solo_vlines(solo_dev) / 2, 3);
	/* Row 2 */
	solo_win_setup(solo_dev, ch + 2, 0, solo_vlines(solo_dev) / 2,
		       solo_dev->video_hsize / 2, solo_vlines(solo_dev), 3);
	solo_win_setup(solo_dev, ch + 3, solo_dev->video_hsize / 2,
		       solo_vlines(solo_dev) / 2, solo_dev->video_hsize,
		       solo_vlines(solo_dev), 3);

	वापस 0;
पूर्ण

अटल पूर्णांक solo_v4l2_ch_ext_16up(काष्ठा solo_dev *solo_dev, पूर्णांक on)
अणु
	पूर्णांक sy, ysize, hsize, i;

	अगर (!on) अणु
		क्रम (i = 0; i < 16; i++)
			solo_win_setup(solo_dev, i, solo_dev->video_hsize,
				       solo_vlines(solo_dev),
				       solo_dev->video_hsize,
				       solo_vlines(solo_dev), 0);
		वापस 0;
	पूर्ण

	ysize = solo_vlines(solo_dev) / 4;
	hsize = solo_dev->video_hsize / 4;

	क्रम (sy = 0, i = 0; i < 4; i++, sy += ysize) अणु
		solo_win_setup(solo_dev, i * 4, 0, sy, hsize,
			       sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 1, hsize, sy,
			       hsize * 2, sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 2, hsize * 2, sy,
			       hsize * 3, sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 3, hsize * 3, sy,
			       solo_dev->video_hsize, sy + ysize, 5);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक solo_v4l2_ch(काष्ठा solo_dev *solo_dev, u8 ch, पूर्णांक on)
अणु
	u8 ext_ch;

	अगर (ch < solo_dev->nr_chans) अणु
		solo_win_setup(solo_dev, ch, on ? 0 : solo_dev->video_hsize,
			       on ? 0 : solo_vlines(solo_dev),
			       solo_dev->video_hsize, solo_vlines(solo_dev),
			       on ? 1 : 0);
		वापस 0;
	पूर्ण

	अगर (ch >= solo_dev->nr_chans + solo_dev->nr_ext)
		वापस -EINVAL;

	ext_ch = ch - solo_dev->nr_chans;

	/* 4up's first */
	अगर (ext_ch < 4)
		वापस solo_v4l2_ch_ext_4up(solo_dev, ext_ch, on);

	/* Reमुख्यing हाल is 16up क्रम 16-port */
	वापस solo_v4l2_ch_ext_16up(solo_dev, on);
पूर्ण

अटल पूर्णांक solo_v4l2_set_ch(काष्ठा solo_dev *solo_dev, u8 ch)
अणु
	अगर (ch >= solo_dev->nr_chans + solo_dev->nr_ext)
		वापस -EINVAL;

	erase_on(solo_dev);

	solo_v4l2_ch(solo_dev, solo_dev->cur_disp_ch, 0);
	solo_v4l2_ch(solo_dev, ch, 1);

	solo_dev->cur_disp_ch = ch;

	वापस 0;
पूर्ण

अटल व्योम solo_fillbuf(काष्ठा solo_dev *solo_dev,
			 काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	dma_addr_t addr;
	अचिन्हित पूर्णांक fdma_addr;
	पूर्णांक error = -1;
	पूर्णांक i;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	अगर (!addr)
		जाओ finish_buf;

	अगर (erase_off(solo_dev)) अणु
		व्योम *p = vb2_plane_vaddr(vb, 0);
		पूर्णांक image_size = solo_image_size(solo_dev);

		क्रम (i = 0; i < image_size; i += 2) अणु
			((u8 *)p)[i] = 0x80;
			((u8 *)p)[i + 1] = 0x00;
		पूर्ण
		error = 0;
	पूर्ण अन्यथा अणु
		fdma_addr = SOLO_DISP_EXT_ADDR + (solo_dev->old_ग_लिखो *
				(SOLO_HW_BPL * solo_vlines(solo_dev)));

		error = solo_p2m_dma_t(solo_dev, 0, addr, fdma_addr,
				       solo_bytesperline(solo_dev),
				       solo_vlines(solo_dev), SOLO_HW_BPL);
	पूर्ण

finish_buf:
	अगर (!error) अणु
		vb2_set_plane_payload(vb, 0,
			solo_vlines(solo_dev) * solo_bytesperline(solo_dev));
		vbuf->sequence = solo_dev->sequence++;
		vb->बारtamp = kसमय_get_ns();
	पूर्ण

	vb2_buffer_करोne(vb, error ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
पूर्ण

अटल व्योम solo_thपढ़ो_try(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा solo_vb2_buf *vb;

	/* Only "break" from this loop अगर slock is held, otherwise
	 * just वापस. */
	क्रम (;;) अणु
		अचिन्हित पूर्णांक cur_ग_लिखो;

		cur_ग_लिखो = SOLO_VI_STATUS0_PAGE(
			solo_reg_पढ़ो(solo_dev, SOLO_VI_STATUS0));
		अगर (cur_ग_लिखो == solo_dev->old_ग_लिखो)
			वापस;

		spin_lock(&solo_dev->slock);

		अगर (list_empty(&solo_dev->vidq_active))
			अवरोध;

		vb = list_first_entry(&solo_dev->vidq_active, काष्ठा solo_vb2_buf,
				      list);

		solo_dev->old_ग_लिखो = cur_ग_लिखो;
		list_del(&vb->list);

		spin_unlock(&solo_dev->slock);

		solo_fillbuf(solo_dev, &vb->vb.vb2_buf);
	पूर्ण

	निश्चित_spin_locked(&solo_dev->slock);
	spin_unlock(&solo_dev->slock);
पूर्ण

अटल पूर्णांक solo_thपढ़ो(व्योम *data)
अणु
	काष्ठा solo_dev *solo_dev = data;
	DECLARE_WAITQUEUE(रुको, current);

	set_मुक्तzable();
	add_रुको_queue(&solo_dev->disp_thपढ़ो_रुको, &रुको);

	क्रम (;;) अणु
		दीर्घ समयout = schedule_समयout_पूर्णांकerruptible(HZ);

		अगर (समयout == -ERESTARTSYS || kthपढ़ो_should_stop())
			अवरोध;
		solo_thपढ़ो_try(solo_dev);
		try_to_मुक्तze();
	पूर्ण

	हटाओ_रुको_queue(&solo_dev->disp_thपढ़ो_रुको, &रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक solo_start_thपढ़ो(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक ret = 0;

	solo_dev->kthपढ़ो = kthपढ़ो_run(solo_thपढ़ो, solo_dev, SOLO6X10_NAME "_disp");

	अगर (IS_ERR(solo_dev->kthपढ़ो)) अणु
		ret = PTR_ERR(solo_dev->kthपढ़ो);
		solo_dev->kthपढ़ो = शून्य;
		वापस ret;
	पूर्ण
	solo_irq_on(solo_dev, SOLO_IRQ_VIDEO_IN);

	वापस ret;
पूर्ण

अटल व्योम solo_stop_thपढ़ो(काष्ठा solo_dev *solo_dev)
अणु
	अगर (!solo_dev->kthपढ़ो)
		वापस;

	solo_irq_off(solo_dev, SOLO_IRQ_VIDEO_IN);
	kthपढ़ो_stop(solo_dev->kthपढ़ो);
	solo_dev->kthपढ़ो = शून्य;
पूर्ण

अटल पूर्णांक solo_queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा solo_dev *solo_dev = vb2_get_drv_priv(q);

	sizes[0] = solo_image_size(solo_dev);
	*num_planes = 1;

	अगर (*num_buffers < MIN_VID_BUFFERS)
		*num_buffers = MIN_VID_BUFFERS;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा solo_dev *solo_dev = vb2_get_drv_priv(q);

	solo_dev->sequence = 0;
	वापस solo_start_thपढ़ो(solo_dev);
पूर्ण

अटल व्योम solo_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा solo_dev *solo_dev = vb2_get_drv_priv(q);

	solo_stop_thपढ़ो(solo_dev);

	spin_lock(&solo_dev->slock);
	जबतक (!list_empty(&solo_dev->vidq_active)) अणु
		काष्ठा solo_vb2_buf *buf = list_entry(
				solo_dev->vidq_active.next,
				काष्ठा solo_vb2_buf, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock(&solo_dev->slock);
	INIT_LIST_HEAD(&solo_dev->vidq_active);
पूर्ण

अटल व्योम solo_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा solo_dev *solo_dev = vb2_get_drv_priv(vq);
	काष्ठा solo_vb2_buf *solo_vb =
		container_of(vbuf, काष्ठा solo_vb2_buf, vb);

	spin_lock(&solo_dev->slock);
	list_add_tail(&solo_vb->list, &solo_dev->vidq_active);
	spin_unlock(&solo_dev->slock);
	wake_up_पूर्णांकerruptible(&solo_dev->disp_thपढ़ो_रुको);
पूर्ण

अटल स्थिर काष्ठा vb2_ops solo_video_qops = अणु
	.queue_setup	= solo_queue_setup,
	.buf_queue	= solo_buf_queue,
	.start_streaming = solo_start_streaming,
	.stop_streaming = solo_stop_streaming,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक solo_querycap(काष्ठा file *file, व्योम  *priv,
			 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	strscpy(cap->driver, SOLO6X10_NAME, माप(cap->driver));
	strscpy(cap->card, "Softlogic 6x10", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s",
		 pci_name(solo_dev->pdev));
	वापस 0;
पूर्ण

अटल पूर्णांक solo_क्रमागत_ext_input(काष्ठा solo_dev *solo_dev,
			       काष्ठा v4l2_input *input)
अणु
	पूर्णांक ext = input->index - solo_dev->nr_chans;
	अचिन्हित पूर्णांक nup, first;

	अगर (ext >= solo_dev->nr_ext)
		वापस -EINVAL;

	nup   = (ext == 4) ? 16 : 4;
	first = (ext & 3) << 2; /* first channel in the n-up */
	snम_लिखो(input->name, माप(input->name),
		 "Multi %d-up (cameras %d-%d)",
		 nup, first + 1, first + nup);
	/* Possible outमाला_दो:
	 *  Multi 4-up (cameras 1-4)
	 *  Multi 4-up (cameras 5-8)
	 *  Multi 4-up (cameras 9-12)
	 *  Multi 4-up (cameras 13-16)
	 *  Multi 16-up (cameras 1-16)
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक solo_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_input *input)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	अगर (input->index >= solo_dev->nr_chans) अणु
		पूर्णांक ret = solo_क्रमागत_ext_input(solo_dev, input);

		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		snम_लिखो(input->name, माप(input->name), "Camera %d",
			 input->index + 1);

		/* We can only check this क्रम normal inमाला_दो */
		अगर (!tw28_get_video_status(solo_dev, input->index))
			input->status = V4L2_IN_ST_NO_SIGNAL;
	पूर्ण

	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = solo_dev->vfd->tvnorms;
	वापस 0;
पूर्ण

अटल पूर्णांक solo_set_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);
	पूर्णांक ret = solo_v4l2_set_ch(solo_dev, index);

	अगर (!ret) अणु
		जबतक (erase_off(solo_dev))
			/* Do nothing */;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक solo_get_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *index)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	*index = solo_dev->cur_disp_ch;

	वापस 0;
पूर्ण

अटल पूर्णांक solo_क्रमागत_fmt_cap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	वापस 0;
पूर्ण

अटल पूर्णांक solo_try_fmt_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	पूर्णांक image_size = solo_image_size(solo_dev);

	अगर (pix->pixelक्रमmat != V4L2_PIX_FMT_UYVY)
		वापस -EINVAL;

	pix->width = solo_dev->video_hsize;
	pix->height = solo_vlines(solo_dev);
	pix->sizeimage = image_size;
	pix->field = V4L2_FIELD_INTERLACED;
	pix->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक solo_set_fmt_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	अगर (vb2_is_busy(&solo_dev->vidq))
		वापस -EBUSY;

	/* For right now, अगर it करोesn't match our running config,
	 * then fail */
	वापस solo_try_fmt_cap(file, priv, f);
पूर्ण

अटल पूर्णांक solo_get_fmt_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	pix->width = solo_dev->video_hsize;
	pix->height = solo_vlines(solo_dev);
	pix->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	pix->field = V4L2_FIELD_INTERLACED;
	pix->sizeimage = solo_image_size(solo_dev);
	pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	pix->bytesperline = solo_bytesperline(solo_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक solo_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *i)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC)
		*i = V4L2_STD_NTSC_M;
	अन्यथा
		*i = V4L2_STD_PAL;
	वापस 0;
पूर्ण

पूर्णांक solo_set_video_type(काष्ठा solo_dev *solo_dev, bool is_50hz)
अणु
	पूर्णांक i;

	/* Make sure all video nodes are idle */
	अगर (vb2_is_busy(&solo_dev->vidq))
		वापस -EBUSY;
	क्रम (i = 0; i < solo_dev->nr_chans; i++)
		अगर (vb2_is_busy(&solo_dev->v4l2_enc[i]->vidq))
			वापस -EBUSY;
	solo_dev->video_type = is_50hz ? SOLO_VO_FMT_TYPE_PAL :
					 SOLO_VO_FMT_TYPE_NTSC;
	/* Reconfigure क्रम the new standard */
	solo_disp_init(solo_dev);
	solo_enc_init(solo_dev);
	solo_tw28_init(solo_dev);
	क्रम (i = 0; i < solo_dev->nr_chans; i++)
		solo_update_mode(solo_dev->v4l2_enc[i]);
	वापस solo_v4l2_set_ch(solo_dev, solo_dev->cur_disp_ch);
पूर्ण

अटल पूर्णांक solo_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा solo_dev *solo_dev = video_drvdata(file);

	वापस solo_set_video_type(solo_dev, std & V4L2_STD_625_50);
पूर्ण

अटल पूर्णांक solo_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा solo_dev *solo_dev =
		container_of(ctrl->handler, काष्ठा solo_dev, disp_hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MOTION_TRACE:
		अगर (ctrl->val) अणु
			solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BORDER,
					SOLO_VI_MOTION_Y_ADD |
					SOLO_VI_MOTION_Y_VALUE(0x20) |
					SOLO_VI_MOTION_CB_VALUE(0x10) |
					SOLO_VI_MOTION_CR_VALUE(0x10));
			solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BAR,
					SOLO_VI_MOTION_CR_ADD |
					SOLO_VI_MOTION_Y_VALUE(0x10) |
					SOLO_VI_MOTION_CB_VALUE(0x80) |
					SOLO_VI_MOTION_CR_VALUE(0x10));
		पूर्ण अन्यथा अणु
			solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BORDER, 0);
			solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BAR, 0);
		पूर्ण
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations solo_v4l2_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= v4l2_fh_खोलो,
	.release		= vb2_fop_release,
	.पढ़ो			= vb2_fop_पढ़ो,
	.poll			= vb2_fop_poll,
	.mmap			= vb2_fop_mmap,
	.unlocked_ioctl		= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops solo_v4l2_ioctl_ops = अणु
	.vidioc_querycap		= solo_querycap,
	.vidioc_s_std			= solo_s_std,
	.vidioc_g_std			= solo_g_std,
	/* Input callbacks */
	.vidioc_क्रमागत_input		= solo_क्रमागत_input,
	.vidioc_s_input			= solo_set_input,
	.vidioc_g_input			= solo_get_input,
	/* Video capture क्रमmat callbacks */
	.vidioc_क्रमागत_fmt_vid_cap	= solo_क्रमागत_fmt_cap,
	.vidioc_try_fmt_vid_cap		= solo_try_fmt_cap,
	.vidioc_s_fmt_vid_cap		= solo_set_fmt_cap,
	.vidioc_g_fmt_vid_cap		= solo_get_fmt_cap,
	/* Streaming I/O */
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	/* Logging and events */
	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device solo_v4l2_ढाँचा = अणु
	.name			= SOLO6X10_NAME,
	.fops			= &solo_v4l2_fops,
	.ioctl_ops		= &solo_v4l2_ioctl_ops,
	.minor			= -1,
	.release		= video_device_release,
	.tvnorms		= V4L2_STD_NTSC_M | V4L2_STD_PAL,
	.device_caps		= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				  V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops solo_ctrl_ops = अणु
	.s_ctrl = solo_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config solo_motion_trace_ctrl = अणु
	.ops = &solo_ctrl_ops,
	.id = V4L2_CID_MOTION_TRACE,
	.name = "Motion Detection Trace",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
पूर्ण;

पूर्णांक solo_v4l2_init(काष्ठा solo_dev *solo_dev, अचिन्हित nr)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	init_रुकोqueue_head(&solo_dev->disp_thपढ़ो_रुको);
	spin_lock_init(&solo_dev->slock);
	mutex_init(&solo_dev->lock);
	INIT_LIST_HEAD(&solo_dev->vidq_active);

	solo_dev->vfd = video_device_alloc();
	अगर (!solo_dev->vfd)
		वापस -ENOMEM;

	*solo_dev->vfd = solo_v4l2_ढाँचा;
	solo_dev->vfd->v4l2_dev = &solo_dev->v4l2_dev;
	solo_dev->vfd->queue = &solo_dev->vidq;
	solo_dev->vfd->lock = &solo_dev->lock;
	v4l2_ctrl_handler_init(&solo_dev->disp_hdl, 1);
	v4l2_ctrl_new_custom(&solo_dev->disp_hdl, &solo_motion_trace_ctrl, शून्य);
	अगर (solo_dev->disp_hdl.error) अणु
		ret = solo_dev->disp_hdl.error;
		जाओ fail;
	पूर्ण
	solo_dev->vfd->ctrl_handler = &solo_dev->disp_hdl;

	video_set_drvdata(solo_dev->vfd, solo_dev);

	solo_dev->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	solo_dev->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	solo_dev->vidq.ops = &solo_video_qops;
	solo_dev->vidq.mem_ops = &vb2_dma_contig_memops;
	solo_dev->vidq.drv_priv = solo_dev;
	solo_dev->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	solo_dev->vidq.gfp_flags = __GFP_DMA32 | __GFP_KSWAPD_RECLAIM;
	solo_dev->vidq.buf_काष्ठा_size = माप(काष्ठा solo_vb2_buf);
	solo_dev->vidq.lock = &solo_dev->lock;
	solo_dev->vidq.dev = &solo_dev->pdev->dev;
	ret = vb2_queue_init(&solo_dev->vidq);
	अगर (ret < 0)
		जाओ fail;

	/* Cycle all the channels and clear */
	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_v4l2_set_ch(solo_dev, i);
		जबतक (erase_off(solo_dev))
			/* Do nothing */;
	पूर्ण

	/* Set the शेष display channel */
	solo_v4l2_set_ch(solo_dev, 0);
	जबतक (erase_off(solo_dev))
		/* Do nothing */;

	ret = video_रेजिस्टर_device(solo_dev->vfd, VFL_TYPE_VIDEO, nr);
	अगर (ret < 0)
		जाओ fail;

	snम_लिखो(solo_dev->vfd->name, माप(solo_dev->vfd->name), "%s (%i)",
		 SOLO6X10_NAME, solo_dev->vfd->num);

	dev_info(&solo_dev->pdev->dev, "Display as /dev/video%d with %d inputs (%d extended)\n",
		 solo_dev->vfd->num,
		 solo_dev->nr_chans, solo_dev->nr_ext);

	वापस 0;

fail:
	video_device_release(solo_dev->vfd);
	v4l2_ctrl_handler_मुक्त(&solo_dev->disp_hdl);
	solo_dev->vfd = शून्य;
	वापस ret;
पूर्ण

व्योम solo_v4l2_निकास(काष्ठा solo_dev *solo_dev)
अणु
	अगर (solo_dev->vfd == शून्य)
		वापस;

	video_unरेजिस्टर_device(solo_dev->vfd);
	v4l2_ctrl_handler_मुक्त(&solo_dev->disp_hdl);
	solo_dev->vfd = शून्य;
पूर्ण
