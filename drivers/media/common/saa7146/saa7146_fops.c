<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>
#समावेश <linux/module.h>

/****************************************************************************/
/* resource management functions, shamelessly stolen from saa7134 driver */

पूर्णांक saa7146_res_get(काष्ठा saa7146_fh *fh, अचिन्हित पूर्णांक bit)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	अगर (fh->resources & bit) अणु
		DEB_D("already allocated! want: 0x%02x, cur:0x%02x\n",
		      bit, vv->resources);
		/* have it alपढ़ोy allocated */
		वापस 1;
	पूर्ण

	/* is it मुक्त? */
	अगर (vv->resources & bit) अणु
		DEB_D("locked! vv->resources:0x%02x, we want:0x%02x\n",
		      vv->resources, bit);
		/* no, someone अन्यथा uses it */
		वापस 0;
	पूर्ण
	/* it's मुक्त, grab it */
	fh->resources |= bit;
	vv->resources |= bit;
	DEB_D("res: get 0x%02x, cur:0x%02x\n", bit, vv->resources);
	वापस 1;
पूर्ण

व्योम saa7146_res_मुक्त(काष्ठा saa7146_fh *fh, अचिन्हित पूर्णांक bits)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	BUG_ON((fh->resources & bits) != bits);

	fh->resources &= ~bits;
	vv->resources &= ~bits;
	DEB_D("res: put 0x%02x, cur:0x%02x\n", bits, vv->resources);
पूर्ण


/********************************************************************************/
/* common dma functions */

व्योम saa7146_dma_मुक्त(काष्ठा saa7146_dev *dev,काष्ठा videobuf_queue *q,
						काष्ठा saa7146_buf *buf)
अणु
	काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);
	DEB_EE("dev:%p, buf:%p\n", dev, buf);

	videobuf_रुकोon(q, &buf->vb, 0, 0);
	videobuf_dma_unmap(q->dev, dma);
	videobuf_dma_मुक्त(dma);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण


/********************************************************************************/
/* common buffer functions */

पूर्णांक saa7146_buffer_queue(काष्ठा saa7146_dev *dev,
			 काष्ठा saa7146_dmaqueue *q,
			 काष्ठा saa7146_buf *buf)
अणु
	निश्चित_spin_locked(&dev->slock);
	DEB_EE("dev:%p, dmaq:%p, buf:%p\n", dev, q, buf);

	BUG_ON(!q);

	अगर (शून्य == q->curr) अणु
		q->curr = buf;
		DEB_D("immediately activating buffer %p\n", buf);
		buf->activate(dev,buf,शून्य);
	पूर्ण अन्यथा अणु
		list_add_tail(&buf->vb.queue,&q->queue);
		buf->vb.state = VIDEOBUF_QUEUED;
		DEB_D("adding buffer %p to queue. (active buffer present)\n",
		      buf);
	पूर्ण
	वापस 0;
पूर्ण

व्योम saa7146_buffer_finish(काष्ठा saa7146_dev *dev,
			   काष्ठा saa7146_dmaqueue *q,
			   पूर्णांक state)
अणु
	निश्चित_spin_locked(&dev->slock);
	DEB_EE("dev:%p, dmaq:%p, state:%d\n", dev, q, state);
	DEB_EE("q->curr:%p\n", q->curr);

	/* finish current buffer */
	अगर (शून्य == q->curr) अणु
		DEB_D("aiii. no current buffer\n");
		वापस;
	पूर्ण

	q->curr->vb.state = state;
	q->curr->vb.ts = kसमय_get_ns();
	wake_up(&q->curr->vb.करोne);

	q->curr = शून्य;
पूर्ण

व्योम saa7146_buffer_next(काष्ठा saa7146_dev *dev,
			 काष्ठा saa7146_dmaqueue *q, पूर्णांक vbi)
अणु
	काष्ठा saa7146_buf *buf,*next = शून्य;

	BUG_ON(!q);

	DEB_INT("dev:%p, dmaq:%p, vbi:%d\n", dev, q, vbi);

	निश्चित_spin_locked(&dev->slock);
	अगर (!list_empty(&q->queue)) अणु
		/* activate next one from queue */
		buf = list_entry(q->queue.next,काष्ठा saa7146_buf,vb.queue);
		list_del(&buf->vb.queue);
		अगर (!list_empty(&q->queue))
			next = list_entry(q->queue.next,काष्ठा saa7146_buf, vb.queue);
		q->curr = buf;
		DEB_INT("next buffer: buf:%p, prev:%p, next:%p\n",
			buf, q->queue.prev, q->queue.next);
		buf->activate(dev,buf,next);
	पूर्ण अन्यथा अणु
		DEB_INT("no next buffer. stopping.\n");
		अगर( 0 != vbi ) अणु
			/* turn off video-dma3 */
			saa7146_ग_लिखो(dev,MC1, MASK_20);
		पूर्ण अन्यथा अणु
			/* nothing to करो -- just prevent next video-dma1 transfer
			   by lowering the protection address */

			// fixme: fix this क्रम vflip != 0

			saa7146_ग_लिखो(dev, PROT_ADDR1, 0);
			saa7146_ग_लिखो(dev, MC2, (MASK_02|MASK_18));

			/* ग_लिखो the address of the rps-program */
			saa7146_ग_लिखो(dev, RPS_ADDR0, dev->d_rps0.dma_handle);
			/* turn on rps */
			saa7146_ग_लिखो(dev, MC1, (MASK_12 | MASK_28));

/*
			prपूर्णांकk("vdma%d.base_even:     0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_EVEN1));
			prपूर्णांकk("vdma%d.base_odd:      0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_ODD1));
			prपूर्णांकk("vdma%d.prot_addr:     0x%08x\n", 1,saa7146_पढ़ो(dev,PROT_ADDR1));
			prपूर्णांकk("vdma%d.base_page:     0x%08x\n", 1,saa7146_पढ़ो(dev,BASE_PAGE1));
			prपूर्णांकk("vdma%d.pitch:         0x%08x\n", 1,saa7146_पढ़ो(dev,PITCH1));
			prपूर्णांकk("vdma%d.num_line_byte: 0x%08x\n", 1,saa7146_पढ़ो(dev,NUM_LINE_BYTE1));
*/
		पूर्ण
		del_समयr(&q->समयout);
	पूर्ण
पूर्ण

व्योम saa7146_buffer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा saa7146_dmaqueue *q = from_समयr(q, t, समयout);
	काष्ठा saa7146_dev *dev = q->dev;
	अचिन्हित दीर्घ flags;

	DEB_EE("dev:%p, dmaq:%p\n", dev, q);

	spin_lock_irqsave(&dev->slock,flags);
	अगर (q->curr) अणु
		DEB_D("timeout on %p\n", q->curr);
		saa7146_buffer_finish(dev,q,VIDEOBUF_ERROR);
	पूर्ण

	/* we करोn't restart the transfer here like other drivers करो. when
	   a streaming capture is disabled, the समयout function will be
	   called क्रम the current buffer. अगर we activate the next buffer now,
	   we mess up our capture logic. अगर a समयout occurs on another buffer,
	   then something is seriously broken beक्रमe, so no need to buffer the
	   next capture IMHO... */
/*
	saa7146_buffer_next(dev,q);
*/
	spin_unlock_irqrestore(&dev->slock,flags);
पूर्ण

/********************************************************************************/
/* file operations */

अटल पूर्णांक fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_dev *dev = video_drvdata(file);
	काष्ठा saa7146_fh *fh = शून्य;
	पूर्णांक result = 0;

	DEB_EE("file:%p, dev:%s\n", file, video_device_node_name(vdev));

	अगर (mutex_lock_पूर्णांकerruptible(vdev->lock))
		वापस -ERESTARTSYS;

	DEB_D("using: %p\n", dev);

	/* check अगर an extension is रेजिस्टरed */
	अगर( शून्य == dev->ext ) अणु
		DEB_S("no extension registered for this device\n");
		result = -ENODEV;
		जाओ out;
	पूर्ण

	/* allocate per खोलो data */
	fh = kzalloc(माप(*fh),GFP_KERNEL);
	अगर (शून्य == fh) अणु
		DEB_S("cannot allocate memory for per open data\n");
		result = -ENOMEM;
		जाओ out;
	पूर्ण

	v4l2_fh_init(&fh->fh, vdev);

	file->निजी_data = &fh->fh;
	fh->dev = dev;

	अगर (vdev->vfl_type == VFL_TYPE_VBI) अणु
		DEB_S("initializing vbi...\n");
		अगर (dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE)
			result = saa7146_vbi_uops.खोलो(dev,file);
		अगर (dev->ext_vv_data->vbi_fops.खोलो)
			dev->ext_vv_data->vbi_fops.खोलो(file);
	पूर्ण अन्यथा अणु
		DEB_S("initializing video...\n");
		result = saa7146_video_uops.खोलो(dev,file);
	पूर्ण

	अगर (0 != result) अणु
		जाओ out;
	पूर्ण

	अगर( 0 == try_module_get(dev->ext->module)) अणु
		result = -EINVAL;
		जाओ out;
	पूर्ण

	result = 0;
	v4l2_fh_add(&fh->fh);
out:
	अगर (fh && result != 0) अणु
		kमुक्त(fh);
		file->निजी_data = शून्य;
	पूर्ण
	mutex_unlock(vdev->lock);
	वापस result;
पूर्ण

अटल पूर्णांक fops_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_fh  *fh  = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;

	DEB_EE("file:%p\n", file);

	mutex_lock(vdev->lock);

	अगर (vdev->vfl_type == VFL_TYPE_VBI) अणु
		अगर (dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE)
			saa7146_vbi_uops.release(dev,file);
		अगर (dev->ext_vv_data->vbi_fops.release)
			dev->ext_vv_data->vbi_fops.release(file);
	पूर्ण अन्यथा अणु
		saa7146_video_uops.release(dev,file);
	पूर्ण

	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	module_put(dev->ext->module);
	file->निजी_data = शून्य;
	kमुक्त(fh);

	mutex_unlock(vdev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक fops_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा * vma)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा videobuf_queue *q;
	पूर्णांक res;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO: अणु
		DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, vma:%p\n",
		       file, vma);
		q = &fh->video_q;
		अवरोध;
		पूर्ण
	हाल VFL_TYPE_VBI: अणु
		DEB_EE("V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, vma:%p\n",
		       file, vma);
		अगर (fh->dev->ext_vv_data->capabilities & V4L2_CAP_SLICED_VBI_OUTPUT)
			वापस -ENODEV;
		q = &fh->vbi_q;
		अवरोध;
		पूर्ण
	शेष:
		BUG();
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(vdev->lock))
		वापस -ERESTARTSYS;
	res = videobuf_mmap_mapper(q, vma);
	mutex_unlock(vdev->lock);
	वापस res;
पूर्ण

अटल __poll_t __fops_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा videobuf_buffer *buf = शून्य;
	काष्ठा videobuf_queue *q;
	__poll_t res = v4l2_ctrl_poll(file, रुको);

	DEB_EE("file:%p, poll:%p\n", file, रुको);

	अगर (vdev->vfl_type == VFL_TYPE_VBI) अणु
		अगर (fh->dev->ext_vv_data->capabilities & V4L2_CAP_SLICED_VBI_OUTPUT)
			वापस res | EPOLLOUT | EPOLLWRNORM;
		अगर( 0 == fh->vbi_q.streaming )
			वापस res | videobuf_poll_stream(file, &fh->vbi_q, रुको);
		q = &fh->vbi_q;
	पूर्ण अन्यथा अणु
		DEB_D("using video queue\n");
		q = &fh->video_q;
	पूर्ण

	अगर (!list_empty(&q->stream))
		buf = list_entry(q->stream.next, काष्ठा videobuf_buffer, stream);

	अगर (!buf) अणु
		DEB_D("buf == NULL!\n");
		वापस res | EPOLLERR;
	पूर्ण

	poll_रुको(file, &buf->करोne, रुको);
	अगर (buf->state == VIDEOBUF_DONE || buf->state == VIDEOBUF_ERROR) अणु
		DEB_D("poll succeeded!\n");
		वापस res | EPOLLIN | EPOLLRDNORM;
	पूर्ण

	DEB_D("nothing to poll for, buf->state:%d\n", buf->state);
	वापस res;
पूर्ण

अटल __poll_t fops_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	__poll_t res;

	mutex_lock(vdev->lock);
	res = __fops_poll(file, रुको);
	mutex_unlock(vdev->lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार fops_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_fh *fh = file->निजी_data;
	पूर्णांक ret;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
/*
		DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, data:%p, count:%lun",
		       file, data, (अचिन्हित दीर्घ)count);
*/
		वापस saa7146_video_uops.पढ़ो(file,data,count,ppos);
	हाल VFL_TYPE_VBI:
/*
		DEB_EE("V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, data:%p, count:%lu\n",
		       file, data, (अचिन्हित दीर्घ)count);
*/
		अगर (fh->dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE) अणु
			अगर (mutex_lock_पूर्णांकerruptible(vdev->lock))
				वापस -ERESTARTSYS;
			ret = saa7146_vbi_uops.पढ़ो(file, data, count, ppos);
			mutex_unlock(vdev->lock);
			वापस ret;
		पूर्ण
		वापस -EINVAL;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल sमाप_प्रकार fops_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7146_fh *fh = file->निजी_data;
	पूर्णांक ret;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		वापस -EINVAL;
	हाल VFL_TYPE_VBI:
		अगर (fh->dev->ext_vv_data->vbi_fops.ग_लिखो) अणु
			अगर (mutex_lock_पूर्णांकerruptible(vdev->lock))
				वापस -ERESTARTSYS;
			ret = fh->dev->ext_vv_data->vbi_fops.ग_लिखो(file, data, count, ppos);
			mutex_unlock(vdev->lock);
			वापस ret;
		पूर्ण
		वापस -EINVAL;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations video_fops =
अणु
	.owner		= THIS_MODULE,
	.खोलो		= fops_खोलो,
	.release	= fops_release,
	.पढ़ो		= fops_पढ़ो,
	.ग_लिखो		= fops_ग_लिखो,
	.poll		= fops_poll,
	.mmap		= fops_mmap,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल व्योम vv_callback(काष्ठा saa7146_dev *dev, अचिन्हित दीर्घ status)
अणु
	u32 isr = status;

	DEB_INT("dev:%p, isr:0x%08x\n", dev, (u32)status);

	अगर (0 != (isr & (MASK_27))) अणु
		DEB_INT("irq: RPS0 (0x%08x)\n", isr);
		saa7146_video_uops.irq_करोne(dev,isr);
	पूर्ण

	अगर (0 != (isr & (MASK_28))) अणु
		u32 mc2 = saa7146_पढ़ो(dev, MC2);
		अगर( 0 != (mc2 & MASK_15)) अणु
			DEB_INT("irq: RPS1 vbi workaround (0x%08x)\n", isr);
			wake_up(&dev->vv_data->vbi_wq);
			saa7146_ग_लिखो(dev,MC2, MASK_31);
			वापस;
		पूर्ण
		DEB_INT("irq: RPS1 (0x%08x)\n", isr);
		saa7146_vbi_uops.irq_करोne(dev,isr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops saa7146_ctrl_ops = अणु
	.s_ctrl = saa7146_s_ctrl,
पूर्ण;

पूर्णांक saa7146_vv_init(काष्ठा saa7146_dev* dev, काष्ठा saa7146_ext_vv *ext_vv)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->ctrl_handler;
	काष्ठा v4l2_pix_क्रमmat *fmt;
	काष्ठा v4l2_vbi_क्रमmat *vbi;
	काष्ठा saa7146_vv *vv;
	पूर्णांक err;

	err = v4l2_device_रेजिस्टर(&dev->pci->dev, &dev->v4l2_dev);
	अगर (err)
		वापस err;

	v4l2_ctrl_handler_init(hdl, 6);
	v4l2_ctrl_new_std(hdl, &saa7146_ctrl_ops,
		V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa7146_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa7146_ctrl_ops,
		V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa7146_ctrl_ops,
		V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa7146_ctrl_ops,
		V4L2_CID_HFLIP, 0, 1, 1, 0);
	अगर (hdl->error) अणु
		err = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण
	dev->v4l2_dev.ctrl_handler = hdl;

	vv = kzalloc(माप(काष्ठा saa7146_vv), GFP_KERNEL);
	अगर (vv == शून्य) अणु
		ERR("out of memory. aborting.\n");
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस -ENOMEM;
	पूर्ण
	ext_vv->vid_ops = saa7146_video_ioctl_ops;
	ext_vv->vbi_ops = saa7146_vbi_ioctl_ops;
	ext_vv->core_ops = &saa7146_video_ioctl_ops;

	DEB_EE("dev:%p\n", dev);

	/* set शेष values क्रम video parts of the saa7146 */
	saa7146_ग_लिखो(dev, BCS_CTRL, 0x80400040);

	/* enable video-port pins */
	saa7146_ग_लिखो(dev, MC1, (MASK_10 | MASK_26));

	/* save per-device extension data (one extension can
	   handle dअगरferent devices that might need dअगरferent
	   configuration data) */
	dev->ext_vv_data = ext_vv;

	vv->d_clipping.cpu_addr =
		dma_alloc_coherent(&dev->pci->dev, SAA7146_CLIPPING_MEM,
				   &vv->d_clipping.dma_handle, GFP_KERNEL);
	अगर( शून्य == vv->d_clipping.cpu_addr ) अणु
		ERR("out of memory. aborting.\n");
		kमुक्त(vv);
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस -1;
	पूर्ण

	saa7146_video_uops.init(dev,vv);
	अगर (dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE)
		saa7146_vbi_uops.init(dev,vv);

	vv->ov_fb.fmt.width = vv->standard->h_max_out;
	vv->ov_fb.fmt.height = vv->standard->v_max_out;
	vv->ov_fb.fmt.pixelक्रमmat = V4L2_PIX_FMT_RGB565;
	vv->ov_fb.fmt.bytesperline = 2 * vv->ov_fb.fmt.width;
	vv->ov_fb.fmt.sizeimage = vv->ov_fb.fmt.bytesperline * vv->ov_fb.fmt.height;
	vv->ov_fb.fmt.colorspace = V4L2_COLORSPACE_SRGB;

	fmt = &vv->video_fmt;
	fmt->width = 384;
	fmt->height = 288;
	fmt->pixelक्रमmat = V4L2_PIX_FMT_BGR24;
	fmt->field = V4L2_FIELD_ANY;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	fmt->bytesperline = 3 * fmt->width;
	fmt->sizeimage = fmt->bytesperline * fmt->height;

	vbi = &vv->vbi_fmt;
	vbi->sampling_rate	= 27000000;
	vbi->offset		= 248; /* toकरो */
	vbi->samples_per_line	= 720 * 2;
	vbi->sample_क्रमmat	= V4L2_PIX_FMT_GREY;

	/* fixme: this only works क्रम PAL */
	vbi->start[0] = 5;
	vbi->count[0] = 16;
	vbi->start[1] = 312;
	vbi->count[1] = 16;

	समयr_setup(&vv->vbi_पढ़ो_समयout, शून्य, 0);

	vv->ov_fb.capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	vv->ov_fb.flags = V4L2_FBUF_FLAG_PRIMARY;
	dev->vv_data = vv;
	dev->vv_callback = &vv_callback;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_vv_init);

पूर्णांक saa7146_vv_release(काष्ठा saa7146_dev* dev)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;

	DEB_EE("dev:%p\n", dev);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	dma_मुक्त_coherent(&dev->pci->dev, SAA7146_CLIPPING_MEM,
			  vv->d_clipping.cpu_addr, vv->d_clipping.dma_handle);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	kमुक्त(vv);
	dev->vv_data = शून्य;
	dev->vv_callback = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_vv_release);

पूर्णांक saa7146_रेजिस्टर_device(काष्ठा video_device *vfd, काष्ठा saa7146_dev *dev,
			    अक्षर *name, पूर्णांक type)
अणु
	पूर्णांक err;
	पूर्णांक i;

	DEB_EE("dev:%p, name:'%s', type:%d\n", dev, name, type);

	vfd->fops = &video_fops;
	अगर (type == VFL_TYPE_VIDEO)
		vfd->ioctl_ops = &dev->ext_vv_data->vid_ops;
	अन्यथा
		vfd->ioctl_ops = &dev->ext_vv_data->vbi_ops;
	vfd->release = video_device_release_empty;
	vfd->lock = &dev->v4l2_lock;
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->tvnorms = 0;
	क्रम (i = 0; i < dev->ext_vv_data->num_stds; i++)
		vfd->tvnorms |= dev->ext_vv_data->stds[i].id;
	strscpy(vfd->name, name, माप(vfd->name));
	vfd->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OVERLAY |
			   V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	vfd->device_caps |= dev->ext_vv_data->capabilities;
	अगर (type == VFL_TYPE_VIDEO)
		vfd->device_caps &=
			~(V4L2_CAP_VBI_CAPTURE | V4L2_CAP_SLICED_VBI_OUTPUT);
	अन्यथा
		vfd->device_caps &=
			~(V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OVERLAY | V4L2_CAP_AUDIO);
	video_set_drvdata(vfd, dev);

	err = video_रेजिस्टर_device(vfd, type, -1);
	अगर (err < 0) अणु
		ERR("cannot register v4l2 device. skipping.\n");
		वापस err;
	पूर्ण

	pr_info("%s: registered device %s [v4l2]\n",
		dev->name, video_device_node_name(vfd));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_रेजिस्टर_device);

पूर्णांक saa7146_unरेजिस्टर_device(काष्ठा video_device *vfd, काष्ठा saa7146_dev *dev)
अणु
	DEB_EE("dev:%p\n", dev);

	video_unरेजिस्टर_device(vfd);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_unरेजिस्टर_device);

अटल पूर्णांक __init saa7146_vv_init_module(व्योम)
अणु
	वापस 0;
पूर्ण


अटल व्योम __निकास saa7146_vv_cleanup_module(व्योम)
अणु
पूर्ण

module_init(saa7146_vv_init_module);
module_निकास(saa7146_vv_cleanup_module);

MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_DESCRIPTION("video4linux driver for saa7146-based hardware");
MODULE_LICENSE("GPL");
