<शैली गुरु>
/*
 * This is a V4L2 PCI Skeleton Driver. It gives an initial skeleton source
 * क्रम use with other PCI drivers.
 *
 * This skeleton PCI driver assumes that the card has an S-Video connector as
 * input 0 and an HDMI connector as input 1.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

MODULE_DESCRIPTION("V4L2 PCI Skeleton Driver");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL v2");

/**
 * काष्ठा skeleton - All पूर्णांकernal data क्रम one instance of device
 * @pdev: PCI device
 * @v4l2_dev: top-level v4l2 device काष्ठा
 * @vdev: video node काष्ठाure
 * @ctrl_handler: control handler काष्ठाure
 * @lock: ioctl serialization mutex
 * @std: current SDTV standard
 * @timings: current HDTV timings
 * @क्रमmat: current pix क्रमmat
 * @input: current video input (0 = SDTV, 1 = HDTV)
 * @queue: vb2 video capture queue
 * @qlock: spinlock controlling access to buf_list and sequence
 * @buf_list: list of buffers queued क्रम DMA
 * @field: the field (TOP/BOTTOM/other) of the current buffer
 * @sequence: frame sequence counter
 */
काष्ठा skeleton अणु
	काष्ठा pci_dev *pdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा mutex lock;
	v4l2_std_id std;
	काष्ठा v4l2_dv_timings timings;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	अचिन्हित input;

	काष्ठा vb2_queue queue;

	spinlock_t qlock;
	काष्ठा list_head buf_list;
	अचिन्हित field;
	अचिन्हित sequence;
पूर्ण;

काष्ठा skel_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत काष्ठा skel_buffer *to_skel_buffer(काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	वापस container_of(vbuf, काष्ठा skel_buffer, vb);
पूर्ण

अटल स्थिर काष्ठा pci_device_id skeleton_pci_tbl[] = अणु
	/* अणु PCI_DEVICE(PCI_VENDOR_ID_, PCI_DEVICE_ID_) पूर्ण, */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, skeleton_pci_tbl);

/*
 * HDTV: this काष्ठाure has the capabilities of the HDTV receiver.
 * It is used to स्थिरrain the huge list of possible क्रमmats based
 * upon the hardware capabilities.
 */
अटल स्थिर काष्ठा v4l2_dv_timings_cap skel_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,
	V4L2_INIT_BT_TIMINGS(
		720, 1920,		/* min/max width */
		480, 1080,		/* min/max height */
		27000000, 74250000,	/* min/max pixelघड़ी*/
		V4L2_DV_BT_STD_CEA861,	/* Supported standards */
		/* capabilities */
		V4L2_DV_BT_CAP_INTERLACED | V4L2_DV_BT_CAP_PROGRESSIVE
	)
पूर्ण;

/*
 * Supported SDTV standards. This करोes the same job as skel_timings_cap, but
 * क्रम standard TV क्रमmats.
 */
#घोषणा SKEL_TVNORMS V4L2_STD_ALL

/*
 * Interrupt handler: typically पूर्णांकerrupts happen after a new frame has been
 * captured. It is the job of the handler to हटाओ the new frame from the
 * पूर्णांकernal list and give it back to the vb2 framework, updating the sequence
 * counter, field and बारtamp at the same समय.
 */
अटल irqवापस_t skeleton_irq(पूर्णांक irq, व्योम *dev_id)
अणु
#अगर_घोषित TODO
	काष्ठा skeleton *skel = dev_id;

	/* handle पूर्णांकerrupt */

	/* Once a new frame has been captured, mark it as करोne like this: */
	अगर (captured_new_frame) अणु
		...
		spin_lock(&skel->qlock);
		list_del(&new_buf->list);
		spin_unlock(&skel->qlock);
		new_buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		new_buf->vb.sequence = skel->sequence++;
		new_buf->vb.field = skel->field;
		अगर (skel->क्रमmat.field == V4L2_FIELD_ALTERNATE) अणु
			अगर (skel->field == V4L2_FIELD_BOTTOM)
				skel->field = V4L2_FIELD_TOP;
			अन्यथा अगर (skel->field == V4L2_FIELD_TOP)
				skel->field = V4L2_FIELD_BOTTOM;
		पूर्ण
		vb2_buffer_करोne(&new_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	पूर्ण
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Setup the स्थिरraपूर्णांकs of the queue: besides setting the number of planes
 * per buffer and the size and allocation context of each plane, it also
 * checks अगर sufficient buffers have been allocated. Usually 3 is a good
 * minimum number: many DMA engines need a minimum of 2 buffers in the
 * queue and you need to have another available क्रम userspace processing.
 */
अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा skeleton *skel = vb2_get_drv_priv(vq);

	skel->field = skel->क्रमmat.field;
	अगर (skel->field == V4L2_FIELD_ALTERNATE) अणु
		/*
		 * You cannot use पढ़ो() with FIELD_ALTERNATE since the field
		 * inक्रमmation (TOP/BOTTOM) cannot be passed back to the user.
		 */
		अगर (vb2_fileio_is_active(vq))
			वापस -EINVAL;
		skel->field = V4L2_FIELD_TOP;
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	अगर (*nplanes)
		वापस sizes[0] < skel->क्रमmat.sizeimage ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = skel->क्रमmat.sizeimage;
	वापस 0;
पूर्ण

/*
 * Prepare the buffer क्रम queueing to the DMA engine: check and set the
 * payload size.
 */
अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा skeleton *skel = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = skel->क्रमmat.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_err(&skel->pdev->dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	वापस 0;
पूर्ण

/*
 * Queue this buffer to the DMA engine.
 */
अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा skeleton *skel = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा skel_buffer *buf = to_skel_buffer(vbuf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&skel->qlock, flags);
	list_add_tail(&buf->list, &skel->buf_list);

	/* TODO: Update any DMA poपूर्णांकers अगर necessary */

	spin_unlock_irqrestore(&skel->qlock, flags);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा skeleton *skel,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा skel_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&skel->qlock, flags);
	list_क्रम_each_entry_safe(buf, node, &skel->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&skel->qlock, flags);
पूर्ण

/*
 * Start streaming. First check अगर the minimum number of buffers have been
 * queued. If not, then वापस -ENOBUFS and the vb2 framework will call
 * this function again the next समय a buffer has been queued until enough
 * buffers are available to actually start the DMA engine.
 */
अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा skeleton *skel = vb2_get_drv_priv(vq);
	पूर्णांक ret = 0;

	skel->sequence = 0;

	/* TODO: start DMA */

	अगर (ret) अणु
		/*
		 * In हाल of an error, वापस all active buffers to the
		 * QUEUED state
		 */
		वापस_all_buffers(skel, VB2_BUF_STATE_QUEUED);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Stop the DMA engine. Any reमुख्यing buffers in the DMA queue are dequeued
 * and passed on to the vb2 framework marked as STATE_ERROR.
 */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा skeleton *skel = vb2_get_drv_priv(vq);

	/* TODO: stop DMA */

	/* Release all active buffers */
	वापस_all_buffers(skel, VB2_BUF_STATE_ERROR);
पूर्ण

/*
 * The vb2 queue ops. Note that since q->lock is set we can use the standard
 * vb2_ops_रुको_prepare/finish helper functions. If q->lock would be शून्य,
 * then this driver would have to provide these ops.
 */
अटल स्थिर काष्ठा vb2_ops skel_qops = अणु
	.queue_setup		= queue_setup,
	.buf_prepare		= buffer_prepare,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/*
 * Required ioctl querycap. Note that the version field is prefilled with
 * the version of the kernel.
 */
अटल पूर्णांक skeleton_querycap(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_capability *cap)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	strlcpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strlcpy(cap->card, "V4L2 PCI Skeleton", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s",
		 pci_name(skel->pdev));
	वापस 0;
पूर्ण

/*
 * Helper function to check and correct काष्ठा v4l2_pix_क्रमmat. It's used
 * not only in VIDIOC_TRY/S_FMT, but also अन्यथाwhere अगर changes to the SDTV
 * standard, HDTV timings or the video input would require updating the
 * current क्रमmat.
 */
अटल व्योम skeleton_fill_pix_क्रमmat(काष्ठा skeleton *skel,
				     काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	pix->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	अगर (skel->input == 0) अणु
		/* S-Video input */
		pix->width = 720;
		pix->height = (skel->std & V4L2_STD_525_60) ? 480 : 576;
		pix->field = V4L2_FIELD_INTERLACED;
		pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	पूर्ण अन्यथा अणु
		/* HDMI input */
		pix->width = skel->timings.bt.width;
		pix->height = skel->timings.bt.height;
		अगर (skel->timings.bt.पूर्णांकerlaced) अणु
			pix->field = V4L2_FIELD_ALTERNATE;
			pix->height /= 2;
		पूर्ण अन्यथा अणु
			pix->field = V4L2_FIELD_NONE;
		पूर्ण
		pix->colorspace = V4L2_COLORSPACE_REC709;
	पूर्ण

	/*
	 * The YUYV क्रमmat is four bytes क्रम every two pixels, so bytesperline
	 * is width * 2.
	 */
	pix->bytesperline = pix->width * 2;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->priv = 0;
पूर्ण

अटल पूर्णांक skeleton_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	/*
	 * Due to historical reasons providing try_fmt with an unsupported
	 * pixelक्रमmat will वापस -EINVAL क्रम video receivers. Webcam drivers,
	 * however, will silently correct the pixelक्रमmat. Some video capture
	 * applications rely on this behavior...
	 */
	अगर (pix->pixelक्रमmat != V4L2_PIX_FMT_YUYV)
		वापस -EINVAL;
	skeleton_fill_pix_क्रमmat(skel, pix);
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);
	पूर्णांक ret;

	ret = skeleton_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	/*
	 * It is not allowed to change the क्रमmat जबतक buffers क्रम use with
	 * streaming have alपढ़ोy been allocated.
	 */
	अगर (vb2_is_busy(&skel->queue))
		वापस -EBUSY;

	/* TODO: change क्रमmat */
	skel->क्रमmat = f->fmt.pix;
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	f->fmt.pix = skel->क्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* S_STD is not supported on the HDMI input */
	अगर (skel->input)
		वापस -ENODATA;

	/*
	 * No change, so just वापस. Some applications call S_STD again after
	 * the buffers क्रम streaming have been set up, so we have to allow क्रम
	 * this behavior.
	 */
	अगर (std == skel->std)
		वापस 0;

	/*
	 * Changing the standard implies a क्रमmat change, which is not allowed
	 * जबतक buffers क्रम use with streaming have alपढ़ोy been allocated.
	 */
	अगर (vb2_is_busy(&skel->queue))
		वापस -EBUSY;

	/* TODO: handle changing std */

	skel->std = std;

	/* Update the पूर्णांकernal क्रमmat */
	skeleton_fill_pix_क्रमmat(skel, &skel->क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* G_STD is not supported on the HDMI input */
	अगर (skel->input)
		वापस -ENODATA;

	*std = skel->std;
	वापस 0;
पूर्ण

/*
 * Query the current standard as seen by the hardware. This function shall
 * never actually change the standard, it just detects and reports.
 * The framework will initially set *std to tvnorms (i.e. the set of
 * supported standards by this input), and this function should just AND
 * this value. If there is no संकेत, then *std should be set to 0.
 */
अटल पूर्णांक skeleton_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* QUERY_STD is not supported on the HDMI input */
	अगर (skel->input)
		वापस -ENODATA;

#अगर_घोषित TODO
	/*
	 * Query currently seen standard. Initial value of *std is
	 * V4L2_STD_ALL. This function should look something like this:
	 */
	get_संकेत_info();
	अगर (no_संकेत) अणु
		*std = 0;
		वापस 0;
	पूर्ण
	/* Use संकेत inक्रमmation to reduce the number of possible standards */
	अगर (संकेत_has_525_lines)
		*std &= V4L2_STD_525_60;
	अन्यथा
		*std &= V4L2_STD_625_50;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_s_dv_timings(काष्ठा file *file, व्योम *_fh,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* S_DV_TIMINGS is not supported on the S-Video input */
	अगर (skel->input == 0)
		वापस -ENODATA;

	/* Quick sanity check */
	अगर (!v4l2_valid_dv_timings(timings, &skel_timings_cap, शून्य, शून्य))
		वापस -EINVAL;

	/* Check अगर the timings are part of the CEA-861 timings. */
	अगर (!v4l2_find_dv_timings_cap(timings, &skel_timings_cap,
				      0, शून्य, शून्य))
		वापस -EINVAL;

	/* Return 0 अगर the new timings are the same as the current timings. */
	अगर (v4l2_match_dv_timings(timings, &skel->timings, 0, false))
		वापस 0;

	/*
	 * Changing the timings implies a क्रमmat change, which is not allowed
	 * जबतक buffers क्रम use with streaming have alपढ़ोy been allocated.
	 */
	अगर (vb2_is_busy(&skel->queue))
		वापस -EBUSY;

	/* TODO: Configure new timings */

	/* Save timings */
	skel->timings = *timings;

	/* Update the पूर्णांकernal क्रमmat */
	skeleton_fill_pix_क्रमmat(skel, &skel->क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_g_dv_timings(काष्ठा file *file, व्योम *_fh,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* G_DV_TIMINGS is not supported on the S-Video input */
	अगर (skel->input == 0)
		वापस -ENODATA;

	*timings = skel->timings;
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_क्रमागत_dv_timings(काष्ठा file *file, व्योम *_fh,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* ENUM_DV_TIMINGS is not supported on the S-Video input */
	अगर (skel->input == 0)
		वापस -ENODATA;

	वापस v4l2_क्रमागत_dv_timings_cap(timings, &skel_timings_cap,
					शून्य, शून्य);
पूर्ण

/*
 * Query the current timings as seen by the hardware. This function shall
 * never actually change the timings, it just detects and reports.
 * If no संकेत is detected, then वापस -ENOLINK. If the hardware cannot
 * lock to the संकेत, then वापस -ENOLCK. If the संकेत is out of range
 * of the capabilities of the प्रणाली (e.g., it is possible that the receiver
 * can lock but that the DMA engine it is connected to cannot handle
 * pixelघड़ीs above a certain frequency), then -दुस्फल is वापसed.
 */
अटल पूर्णांक skeleton_query_dv_timings(काष्ठा file *file, व्योम *_fh,
				     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* QUERY_DV_TIMINGS is not supported on the S-Video input */
	अगर (skel->input == 0)
		वापस -ENODATA;

#अगर_घोषित TODO
	/*
	 * Query currently seen timings. This function should look
	 * something like this:
	 */
	detect_timings();
	अगर (no_संकेत)
		वापस -ENOLINK;
	अगर (cannot_lock_to_संकेत)
		वापस -ENOLCK;
	अगर (संकेत_out_of_range_of_capabilities)
		वापस -दुस्फल;

	/* Useful क्रम debugging */
	v4l2_prपूर्णांक_dv_timings(skel->v4l2_dev.name, "query_dv_timings:",
			timings, true);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_dv_timings_cap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_dv_timings_cap *cap)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	/* DV_TIMINGS_CAP is not supported on the S-Video input */
	अगर (skel->input == 0)
		वापस -ENODATA;
	*cap = skel_timings_cap;
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_input *i)
अणु
	अगर (i->index > 1)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;
	अगर (i->index == 0) अणु
		i->std = SKEL_TVNORMS;
		strlcpy(i->name, "S-Video", माप(i->name));
		i->capabilities = V4L2_IN_CAP_STD;
	पूर्ण अन्यथा अणु
		i->std = 0;
		strlcpy(i->name, "HDMI", माप(i->name));
		i->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	अगर (i > 1)
		वापस -EINVAL;

	/*
	 * Changing the input implies a क्रमmat change, which is not allowed
	 * जबतक buffers क्रम use with streaming have alपढ़ोy been allocated.
	 */
	अगर (vb2_is_busy(&skel->queue))
		वापस -EBUSY;

	skel->input = i;
	/*
	 * Update tvnorms. The tvnorms value is used by the core to implement
	 * VIDIOC_ENUMSTD so it has to be correct. If tvnorms == 0, then
	 * ENUMSTD will वापस -ENODATA.
	 */
	skel->vdev.tvnorms = i ? 0 : SKEL_TVNORMS;

	/* Update the पूर्णांकernal क्रमmat */
	skeleton_fill_pix_क्रमmat(skel, &skel->क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक skeleton_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा skeleton *skel = video_drvdata(file);

	*i = skel->input;
	वापस 0;
पूर्ण

/* The control handler. */
अटल पूर्णांक skeleton_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	/*काष्ठा skeleton *skel =
		container_of(ctrl->handler, काष्ठा skeleton, ctrl_handler);*/

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		/* TODO: set brightness to ctrl->val */
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		/* TODO: set contrast to ctrl->val */
		अवरोध;
	हाल V4L2_CID_SATURATION:
		/* TODO: set saturation to ctrl->val */
		अवरोध;
	हाल V4L2_CID_HUE:
		/* TODO: set hue to ctrl->val */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------
	File operations क्रम the device
   ------------------------------------------------------------------*/

अटल स्थिर काष्ठा v4l2_ctrl_ops skel_ctrl_ops = अणु
	.s_ctrl = skeleton_s_ctrl,
पूर्ण;

/*
 * The set of all supported ioctls. Note that all the streaming ioctls
 * use the vb2 helper functions that take care of all the locking and
 * that also करो ownership tracking (i.e. only the filehandle that requested
 * the buffers can call the streaming ioctls, all other filehandles will
 * receive -EBUSY अगर they attempt to call the same streaming ioctls).
 *
 * The last three ioctls also use standard helper functions: these implement
 * standard behavior क्रम drivers with controls.
 */
अटल स्थिर काष्ठा v4l2_ioctl_ops skel_ioctl_ops = अणु
	.vidioc_querycap = skeleton_querycap,
	.vidioc_try_fmt_vid_cap = skeleton_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = skeleton_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = skeleton_g_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap = skeleton_क्रमागत_fmt_vid_cap,

	.vidioc_g_std = skeleton_g_std,
	.vidioc_s_std = skeleton_s_std,
	.vidioc_querystd = skeleton_querystd,

	.vidioc_s_dv_timings = skeleton_s_dv_timings,
	.vidioc_g_dv_timings = skeleton_g_dv_timings,
	.vidioc_क्रमागत_dv_timings = skeleton_क्रमागत_dv_timings,
	.vidioc_query_dv_timings = skeleton_query_dv_timings,
	.vidioc_dv_timings_cap = skeleton_dv_timings_cap,

	.vidioc_क्रमागत_input = skeleton_क्रमागत_input,
	.vidioc_g_input = skeleton_g_input,
	.vidioc_s_input = skeleton_s_input,

	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,

	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/*
 * The set of file operations. Note that all these ops are standard core
 * helper functions.
 */
अटल स्थिर काष्ठा v4l2_file_operations skel_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll,
पूर्ण;

/*
 * The initial setup of this device instance. Note that the initial state of
 * the driver should be complete. So the initial क्रमmat, standard, timings
 * and video input should all be initialized to some reasonable value.
 */
अटल पूर्णांक skeleton_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	/* The initial timings are chosen to be 720p60. */
	अटल स्थिर काष्ठा v4l2_dv_timings timings_def =
		V4L2_DV_BT_CEA_1280X720P60;
	काष्ठा skeleton *skel;
	काष्ठा video_device *vdev;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	/* Enable PCI */
	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "no suitable DMA available.\n");
		जाओ disable_pci;
	पूर्ण

	/* Allocate a new instance */
	skel = devm_kzalloc(&pdev->dev, माप(काष्ठा skeleton), GFP_KERNEL);
	अगर (!skel) अणु
		ret = -ENOMEM;
		जाओ disable_pci;
	पूर्ण

	/* Allocate the पूर्णांकerrupt */
	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       skeleton_irq, 0, KBUILD_MODNAME, skel);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ disable_pci;
	पूर्ण
	skel->pdev = pdev;

	/* Fill in the initial क्रमmat-related settings */
	skel->timings = timings_def;
	skel->std = V4L2_STD_625_50;
	skeleton_fill_pix_क्रमmat(skel, &skel->क्रमmat);

	/* Initialize the top-level काष्ठाure */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &skel->v4l2_dev);
	अगर (ret)
		जाओ disable_pci;

	mutex_init(&skel->lock);

	/* Add the controls */
	hdl = &skel->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &skel_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &skel_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 255, 1, 16);
	v4l2_ctrl_new_std(hdl, &skel_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &skel_ctrl_ops,
			  V4L2_CID_HUE, -128, 127, 1, 0);
	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ मुक्त_hdl;
	पूर्ण
	skel->v4l2_dev.ctrl_handler = hdl;

	/* Initialize the vb2 queue */
	q = &skel->queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->dev = &pdev->dev;
	q->drv_priv = skel;
	q->buf_काष्ठा_size = माप(काष्ठा skel_buffer);
	q->ops = &skel_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	/*
	 * Assume that this DMA engine needs to have at least two buffers
	 * available beक्रमe it can be started. The start_streaming() op
	 * won't be called until at least this many buffers are queued up.
	 */
	q->min_buffers_needed = 2;
	/*
	 * The serialization lock क्रम the streaming ioctls. This is the same
	 * as the मुख्य serialization lock, but अगर some of the non-streaming
	 * ioctls could take a दीर्घ समय to execute, then you might want to
	 * have a dअगरferent lock here to prevent VIDIOC_DQBUF from being
	 * blocked जबतक रुकोing क्रम another action to finish. This is
	 * generally not needed क्रम PCI devices, but USB devices usually करो
	 * want a separate lock here.
	 */
	q->lock = &skel->lock;
	/*
	 * Since this driver can only करो 32-bit DMA we must make sure that
	 * the vb2 core will allocate the buffers in 32-bit DMA memory.
	 */
	q->gfp_flags = GFP_DMA32;
	ret = vb2_queue_init(q);
	अगर (ret)
		जाओ मुक्त_hdl;

	INIT_LIST_HEAD(&skel->buf_list);
	spin_lock_init(&skel->qlock);

	/* Initialize the video_device काष्ठाure */
	vdev = &skel->vdev;
	strlcpy(vdev->name, KBUILD_MODNAME, माप(vdev->name));
	/*
	 * There is nothing to clean up, so release is set to an empty release
	 * function. The release callback must be non-शून्य.
	 */
	vdev->release = video_device_release_empty;
	vdev->fops = &skel_fops,
	vdev->ioctl_ops = &skel_ioctl_ops,
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_STREAMING;
	/*
	 * The मुख्य serialization lock. All ioctls are serialized by this
	 * lock. Exception: अगर q->lock is set, then the streaming ioctls
	 * are serialized by that separate lock.
	 */
	vdev->lock = &skel->lock;
	vdev->queue = q;
	vdev->v4l2_dev = &skel->v4l2_dev;
	/* Supported SDTV standards, अगर any */
	vdev->tvnorms = SKEL_TVNORMS;
	video_set_drvdata(vdev, skel);

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ मुक्त_hdl;

	dev_info(&pdev->dev, "V4L2 PCI Skeleton Driver loaded\n");
	वापस 0;

मुक्त_hdl:
	v4l2_ctrl_handler_मुक्त(&skel->ctrl_handler);
	v4l2_device_unरेजिस्टर(&skel->v4l2_dev);
disable_pci:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम skeleton_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा skeleton *skel = container_of(v4l2_dev, काष्ठा skeleton, v4l2_dev);

	video_unरेजिस्टर_device(&skel->vdev);
	v4l2_ctrl_handler_मुक्त(&skel->ctrl_handler);
	v4l2_device_unरेजिस्टर(&skel->v4l2_dev);
	pci_disable_device(skel->pdev);
पूर्ण

अटल काष्ठा pci_driver skeleton_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = skeleton_probe,
	.हटाओ = skeleton_हटाओ,
	.id_table = skeleton_pci_tbl,
पूर्ण;

module_pci_driver(skeleton_driver);
