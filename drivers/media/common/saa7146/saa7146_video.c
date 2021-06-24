<शैली गुरु>
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

अटल पूर्णांक max_memory = 32;

module_param(max_memory, पूर्णांक, 0644);
MODULE_PARM_DESC(max_memory, "maximum memory usage for capture buffers (default: 32Mb)");

#घोषणा IS_CAPTURE_ACTIVE(fh) \
	(((vv->video_status & STATUS_CAPTURE) != 0) && (vv->video_fh == fh))

#घोषणा IS_OVERLAY_ACTIVE(fh) \
	(((vv->video_status & STATUS_OVERLAY) != 0) && (vv->video_fh == fh))

/* क्रमmat descriptions क्रम capture and preview */
अटल काष्ठा saa7146_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB332,
		.trans		= RGB08_COMPOSED,
		.depth		= 8,
		.flags		= 0,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB565,
		.trans		= RGB16_COMPOSED,
		.depth		= 16,
		.flags		= 0,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_BGR24,
		.trans		= RGB24_COMPOSED,
		.depth		= 24,
		.flags		= 0,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_BGR32,
		.trans		= RGB32_COMPOSED,
		.depth		= 32,
		.flags		= 0,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_RGB32,
		.trans		= RGB32_COMPOSED,
		.depth		= 32,
		.flags		= 0,
		.swap		= 0x2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_GREY,
		.trans		= Y8,
		.depth		= 8,
		.flags		= 0,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV422P,
		.trans		= YUV422_DECOMPOSED,
		.depth		= 16,
		.flags		= FORMAT_BYTE_SWAP|FORMAT_IS_PLANAR,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YVU420,
		.trans		= YUV420_DECOMPOSED,
		.depth		= 12,
		.flags		= FORMAT_BYTE_SWAP|FORMAT_IS_PLANAR,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUV420,
		.trans		= YUV420_DECOMPOSED,
		.depth		= 12,
		.flags		= FORMAT_IS_PLANAR,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_UYVY,
		.trans		= YUV422_COMPOSED,
		.depth		= 16,
		.flags		= 0,
	पूर्ण
पूर्ण;

/* unक्रमtunately, the saa7146 contains a bug which prevents it from करोing on-the-fly byte swaps.
   due to this, it's impossible to provide additional *packed* क्रमmats, which are simply byte swapped
   (like V4L2_PIX_FMT_YUYV) ... 8-( */

काष्ठा saa7146_क्रमmat* saa7146_क्रमmat_by_fourcc(काष्ठा saa7146_dev *dev, पूर्णांक fourcc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == fourcc) अणु
			वापस क्रमmats+i;
		पूर्ण
	पूर्ण

	DEB_D("unknown pixelformat:'%4.4s'\n", (अक्षर *)&fourcc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);

पूर्णांक saa7146_start_preview(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा v4l2_क्रमmat fmt;
	पूर्णांक ret = 0, err = 0;

	DEB_EE("dev:%p, fh:%p\n", dev, fh);

	/* check अगर we have overlay inक्रमmation */
	अगर (vv->ov.fh == शून्य) अणु
		DEB_D("no overlay data available. try S_FMT first.\n");
		वापस -EAGAIN;
	पूर्ण

	/* check अगर streaming capture is running */
	अगर (IS_CAPTURE_ACTIVE(fh) != 0) अणु
		DEB_D("streaming capture is active\n");
		वापस -EBUSY;
	पूर्ण

	/* check अगर overlay is running */
	अगर (IS_OVERLAY_ACTIVE(fh) != 0) अणु
		अगर (vv->video_fh == fh) अणु
			DEB_D("overlay is already active\n");
			वापस 0;
		पूर्ण
		DEB_D("overlay is already active in another open\n");
		वापस -EBUSY;
	पूर्ण

	अगर (0 == saa7146_res_get(fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP)) अणु
		DEB_D("cannot get necessary overlay resources\n");
		वापस -EBUSY;
	पूर्ण

	fmt.fmt.win = vv->ov.win;
	err = vidioc_try_fmt_vid_overlay(शून्य, fh, &fmt);
	अगर (0 != err) अणु
		saa7146_res_मुक्त(vv->video_fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP);
		वापस -EBUSY;
	पूर्ण
	vv->ov.win = fmt.fmt.win;

	DEB_D("%dx%d+%d+%d 0x%08x field=%s\n",
	      vv->ov.win.w.width, vv->ov.win.w.height,
	      vv->ov.win.w.left, vv->ov.win.w.top,
	      vv->ov_fmt->pixelक्रमmat, v4l2_field_names[vv->ov.win.field]);

	अगर (0 != (ret = saa7146_enable_overlay(fh))) अणु
		DEB_D("enabling overlay failed: %d\n", ret);
		saa7146_res_मुक्त(vv->video_fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP);
		वापस ret;
	पूर्ण

	vv->video_status = STATUS_OVERLAY;
	vv->video_fh = fh;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_start_preview);

पूर्णांक saa7146_stop_preview(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	DEB_EE("dev:%p, fh:%p\n", dev, fh);

	/* check अगर streaming capture is running */
	अगर (IS_CAPTURE_ACTIVE(fh) != 0) अणु
		DEB_D("streaming capture is active\n");
		वापस -EBUSY;
	पूर्ण

	/* check अगर overlay is running at all */
	अगर ((vv->video_status & STATUS_OVERLAY) == 0) अणु
		DEB_D("no active overlay\n");
		वापस 0;
	पूर्ण

	अगर (vv->video_fh != fh) अणु
		DEB_D("overlay is active, but in another open\n");
		वापस -EBUSY;
	पूर्ण

	vv->video_status = 0;
	vv->video_fh = शून्य;

	saa7146_disable_overlay(fh);

	saa7146_res_मुक्त(fh, RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7146_stop_preview);

/********************************************************************************/
/* common pagetable functions */

अटल पूर्णांक saa7146_pgtable_build(काष्ठा saa7146_dev *dev, काष्ठा saa7146_buf *buf)
अणु
	काष्ठा pci_dev *pci = dev->pci;
	काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);
	काष्ठा scatterlist *list = dma->sglist;
	पूर्णांक length = dma->sglen;
	काष्ठा saa7146_क्रमmat *sfmt = saa7146_क्रमmat_by_fourcc(dev,buf->fmt->pixelक्रमmat);

	DEB_EE("dev:%p, buf:%p, sg_len:%d\n", dev, buf, length);

	अगर( 0 != IS_PLANAR(sfmt->trans)) अणु
		काष्ठा saa7146_pgtable *pt1 = &buf->pt[0];
		काष्ठा saa7146_pgtable *pt2 = &buf->pt[1];
		काष्ठा saa7146_pgtable *pt3 = &buf->pt[2];
		__le32  *ptr1, *ptr2, *ptr3;
		__le32 fill;

		पूर्णांक size = buf->fmt->width*buf->fmt->height;
		पूर्णांक i,p,m1,m2,m3,o1,o2;

		चयन( sfmt->depth ) अणु
			हाल 12: अणु
				/* create some offsets inside the page table */
				m1 = ((size+PAGE_SIZE)/PAGE_SIZE)-1;
				m2 = ((size+(size/4)+PAGE_SIZE)/PAGE_SIZE)-1;
				m3 = ((size+(size/2)+PAGE_SIZE)/PAGE_SIZE)-1;
				o1 = size%PAGE_SIZE;
				o2 = (size+(size/4))%PAGE_SIZE;
				DEB_CAP("size:%d, m1:%d, m2:%d, m3:%d, o1:%d, o2:%d\n",
					size, m1, m2, m3, o1, o2);
				अवरोध;
			पूर्ण
			हाल 16: अणु
				/* create some offsets inside the page table */
				m1 = ((size+PAGE_SIZE)/PAGE_SIZE)-1;
				m2 = ((size+(size/2)+PAGE_SIZE)/PAGE_SIZE)-1;
				m3 = ((2*size+PAGE_SIZE)/PAGE_SIZE)-1;
				o1 = size%PAGE_SIZE;
				o2 = (size+(size/2))%PAGE_SIZE;
				DEB_CAP("size:%d, m1:%d, m2:%d, m3:%d, o1:%d, o2:%d\n",
					size, m1, m2, m3, o1, o2);
				अवरोध;
			पूर्ण
			शेष: अणु
				वापस -1;
			पूर्ण
		पूर्ण

		ptr1 = pt1->cpu;
		ptr2 = pt2->cpu;
		ptr3 = pt3->cpu;

		/* walk all pages, copy all page addresses to ptr1 */
		क्रम (i = 0; i < length; i++, list++) अणु
			क्रम (p = 0; p * 4096 < sg_dma_len(list); p++, ptr1++)
				*ptr1 = cpu_to_le32(sg_dma_address(list) - list->offset);
		पूर्ण
/*
		ptr1 = pt1->cpu;
		क्रम(j=0;j<40;j++) अणु
			prपूर्णांकk("ptr1 %d: 0x%08x\n",j,ptr1[j]);
		पूर्ण
*/

		/* अगर we have a user buffer, the first page may not be
		   aligned to a page boundary. */
		pt1->offset = dma->sglist->offset;
		pt2->offset = pt1->offset+o1;
		pt3->offset = pt1->offset+o2;

		/* create video-dma2 page table */
		ptr1 = pt1->cpu;
		क्रम(i = m1; i <= m2 ; i++, ptr2++) अणु
			*ptr2 = ptr1[i];
		पूर्ण
		fill = *(ptr2-1);
		क्रम(;i<1024;i++,ptr2++) अणु
			*ptr2 = fill;
		पूर्ण
		/* create video-dma3 page table */
		ptr1 = pt1->cpu;
		क्रम(i = m2; i <= m3; i++,ptr3++) अणु
			*ptr3 = ptr1[i];
		पूर्ण
		fill = *(ptr3-1);
		क्रम(;i<1024;i++,ptr3++) अणु
			*ptr3 = fill;
		पूर्ण
		/* finally: finish up video-dma1 page table */
		ptr1 = pt1->cpu+m1;
		fill = pt1->cpu[m1];
		क्रम(i=m1;i<1024;i++,ptr1++) अणु
			*ptr1 = fill;
		पूर्ण
/*
		ptr1 = pt1->cpu;
		ptr2 = pt2->cpu;
		ptr3 = pt3->cpu;
		क्रम(j=0;j<40;j++) अणु
			prपूर्णांकk("ptr1 %d: 0x%08x\n",j,ptr1[j]);
		पूर्ण
		क्रम(j=0;j<40;j++) अणु
			prपूर्णांकk("ptr2 %d: 0x%08x\n",j,ptr2[j]);
		पूर्ण
		क्रम(j=0;j<40;j++) अणु
			prपूर्णांकk("ptr3 %d: 0x%08x\n",j,ptr3[j]);
		पूर्ण
*/
	पूर्ण अन्यथा अणु
		काष्ठा saa7146_pgtable *pt = &buf->pt[0];
		वापस saa7146_pgtable_build_single(pci, pt, list, length);
	पूर्ण

	वापस 0;
पूर्ण


/********************************************************************************/
/* file operations */

अटल पूर्णांक video_begin(काष्ठा saa7146_fh *fh)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_क्रमmat *fmt = शून्य;
	अचिन्हित पूर्णांक resource;
	पूर्णांक ret = 0, err = 0;

	DEB_EE("dev:%p, fh:%p\n", dev, fh);

	अगर ((vv->video_status & STATUS_CAPTURE) != 0) अणु
		अगर (vv->video_fh == fh) अणु
			DEB_S("already capturing\n");
			वापस 0;
		पूर्ण
		DEB_S("already capturing in another open\n");
		वापस -EBUSY;
	पूर्ण

	अगर ((vv->video_status & STATUS_OVERLAY) != 0) अणु
		DEB_S("warning: suspending overlay video for streaming capture\n");
		vv->ov_suspend = vv->video_fh;
		err = saa7146_stop_preview(vv->video_fh); /* side effect: video_status is now 0, video_fh is शून्य */
		अगर (0 != err) अणु
			DEB_D("suspending video failed. aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	fmt = saa7146_क्रमmat_by_fourcc(dev, vv->video_fmt.pixelक्रमmat);
	/* we need to have a valid क्रमmat set here */
	अगर (!fmt)
		वापस -EINVAL;

	अगर (0 != (fmt->flags & FORMAT_IS_PLANAR)) अणु
		resource = RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP|RESOURCE_DMA3_BRS;
	पूर्ण अन्यथा अणु
		resource = RESOURCE_DMA1_HPS;
	पूर्ण

	ret = saa7146_res_get(fh, resource);
	अगर (0 == ret) अणु
		DEB_S("cannot get capture resource %d\n", resource);
		अगर (vv->ov_suspend != शून्य) अणु
			saa7146_start_preview(vv->ov_suspend);
			vv->ov_suspend = शून्य;
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	/* clear out beginning of streaming bit (rps रेजिस्टर 0)*/
	saa7146_ग_लिखो(dev, MC2, MASK_27 );

	/* enable rps0 irqs */
	SAA7146_IER_ENABLE(dev, MASK_27);

	vv->video_fh = fh;
	vv->video_status = STATUS_CAPTURE;

	वापस 0;
पूर्ण

अटल पूर्णांक video_end(काष्ठा saa7146_fh *fh, काष्ठा file *file)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_dmaqueue *q = &vv->video_dmaq;
	काष्ठा saa7146_क्रमmat *fmt = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक resource;
	u32 dmas = 0;
	DEB_EE("dev:%p, fh:%p\n", dev, fh);

	अगर ((vv->video_status & STATUS_CAPTURE) != STATUS_CAPTURE) अणु
		DEB_S("not capturing\n");
		वापस 0;
	पूर्ण

	अगर (vv->video_fh != fh) अणु
		DEB_S("capturing, but in another open\n");
		वापस -EBUSY;
	पूर्ण

	fmt = saa7146_क्रमmat_by_fourcc(dev, vv->video_fmt.pixelक्रमmat);
	/* we need to have a valid क्रमmat set here */
	अगर (!fmt)
		वापस -EINVAL;

	अगर (0 != (fmt->flags & FORMAT_IS_PLANAR)) अणु
		resource = RESOURCE_DMA1_HPS|RESOURCE_DMA2_CLP|RESOURCE_DMA3_BRS;
		dmas = MASK_22 | MASK_21 | MASK_20;
	पूर्ण अन्यथा अणु
		resource = RESOURCE_DMA1_HPS;
		dmas = MASK_22;
	पूर्ण
	spin_lock_irqsave(&dev->slock,flags);

	/* disable rps0  */
	saa7146_ग_लिखो(dev, MC1, MASK_28);

	/* disable rps0 irqs */
	SAA7146_IER_DISABLE(dev, MASK_27);

	/* shut करोwn all used video dma transfers */
	saa7146_ग_लिखो(dev, MC1, dmas);

	अगर (q->curr)
		saa7146_buffer_finish(dev, q, VIDEOBUF_DONE);

	spin_unlock_irqrestore(&dev->slock, flags);

	vv->video_fh = शून्य;
	vv->video_status = 0;

	saa7146_res_मुक्त(fh, resource);

	अगर (vv->ov_suspend != शून्य) अणु
		saa7146_start_preview(vv->ov_suspend);
		vv->ov_suspend = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;

	strscpy((अक्षर *)cap->driver, "saa7146 v4l2", माप(cap->driver));
	strscpy((अक्षर *)cap->card, dev->ext->name, माप(cap->card));
	प्र_लिखो((अक्षर *)cap->bus_info, "PCI:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OVERLAY |
			    V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_DEVICE_CAPS;
	cap->capabilities |= dev->ext_vv_data->capabilities;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	*fb = vv->ov_fb;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	fb->flags = V4L2_FBUF_FLAG_PRIMARY;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fbuf(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_क्रमmat *fmt;

	DEB_EE("VIDIOC_S_FBUF\n");

	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	/* check args */
	fmt = saa7146_क्रमmat_by_fourcc(dev, fb->fmt.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	/* planar क्रमmats are not allowed क्रम overlay video, clipping and video dma would clash */
	अगर (fmt->flags & FORMAT_IS_PLANAR)
		DEB_S("planar pixelformat '%4.4s' not allowed for overlay\n",
		      (अक्षर *)&fmt->pixelक्रमmat);

	/* check अगर overlay is running */
	अगर (IS_OVERLAY_ACTIVE(fh) != 0) अणु
		अगर (vv->video_fh != fh) अणु
			DEB_D("refusing to change framebuffer information while overlay is active in another open\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* ok, accept it */
	vv->ov_fb = *fb;
	vv->ov_fmt = fmt;

	अगर (vv->ov_fb.fmt.bytesperline < vv->ov_fb.fmt.width) अणु
		vv->ov_fb.fmt.bytesperline = vv->ov_fb.fmt.width * fmt->depth / 8;
		DEB_D("setting bytesperline to %d\n", vv->ov_fb.fmt.bytesperline);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;
	वापस 0;
पूर्ण

पूर्णांक saa7146_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa7146_dev *dev = container_of(ctrl->handler,
				काष्ठा saa7146_dev, ctrl_handler);
	काष्ठा saa7146_vv *vv = dev->vv_data;
	u32 val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		val = saa7146_पढ़ो(dev, BCS_CTRL);
		val &= 0x00ffffff;
		val |= (ctrl->val << 24);
		saa7146_ग_लिखो(dev, BCS_CTRL, val);
		saa7146_ग_लिखो(dev, MC2, MASK_22 | MASK_06);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		val = saa7146_पढ़ो(dev, BCS_CTRL);
		val &= 0xff00ffff;
		val |= (ctrl->val << 16);
		saa7146_ग_लिखो(dev, BCS_CTRL, val);
		saa7146_ग_लिखो(dev, MC2, MASK_22 | MASK_06);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		val = saa7146_पढ़ो(dev, BCS_CTRL);
		val &= 0xffffff00;
		val |= (ctrl->val << 0);
		saa7146_ग_लिखो(dev, BCS_CTRL, val);
		saa7146_ग_लिखो(dev, MC2, MASK_22 | MASK_06);
		अवरोध;

	हाल V4L2_CID_HFLIP:
		/* fixme: we can support changing VFLIP and HFLIP here... */
		अगर ((vv->video_status & STATUS_CAPTURE))
			वापस -EBUSY;
		vv->hflip = ctrl->val;
		अवरोध;

	हाल V4L2_CID_VFLIP:
		अगर ((vv->video_status & STATUS_CAPTURE))
			वापस -EBUSY;
		vv->vflip = ctrl->val;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((vv->video_status & STATUS_OVERLAY) != 0) अणु /* CHECK: && (vv->video_fh == fh)) */
		काष्ठा saa7146_fh *fh = vv->video_fh;

		saa7146_stop_preview(fh);
		saa7146_start_preview(fh);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	parm->parm.capture.पढ़ोbuffers = 1;
	v4l2_video_std_frame_period(vv->standard->id,
				    &parm->parm.capture.समयperframe);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	f->fmt.pix = vv->video_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	f->fmt.win = vv->ov.win;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	f->fmt.vbi = vv->vbi_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_क्रमmat *fmt;
	क्रमागत v4l2_field field;
	पूर्णांक maxw, maxh;
	पूर्णांक calc_bpl;

	DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: dev:%p, fh:%p\n", dev, fh);

	fmt = saa7146_क्रमmat_by_fourcc(dev, f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	field = f->fmt.pix.field;
	maxw  = vv->standard->h_max_out;
	maxh  = vv->standard->v_max_out;

	अगर (V4L2_FIELD_ANY == field) अणु
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
	पूर्ण
	चयन (field) अणु
	हाल V4L2_FIELD_ALTERNATE:
		vv->last_field = V4L2_FIELD_TOP;
		maxh = maxh / 2;
		अवरोध;
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		vv->last_field = V4L2_FIELD_INTERLACED;
		maxh = maxh / 2;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		vv->last_field = V4L2_FIELD_INTERLACED;
		अवरोध;
	शेष:
		DEB_D("no known field mode '%d'\n", field);
		वापस -EINVAL;
	पूर्ण

	f->fmt.pix.field = field;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	अगर (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	अगर (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;

	calc_bpl = (f->fmt.pix.width * fmt->depth) / 8;

	अगर (f->fmt.pix.bytesperline < calc_bpl)
		f->fmt.pix.bytesperline = calc_bpl;

	अगर (f->fmt.pix.bytesperline > (2 * PAGE_SIZE * fmt->depth) / 8) /* arbitrary स्थिरraपूर्णांक */
		f->fmt.pix.bytesperline = calc_bpl;

	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * f->fmt.pix.height;
	DEB_D("w:%d, h:%d, bytesperline:%d, sizeimage:%d\n",
	      f->fmt.pix.width, f->fmt.pix.height,
	      f->fmt.pix.bytesperline, f->fmt.pix.sizeimage);

	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;
	क्रमागत v4l2_field field;
	पूर्णांक maxw, maxh;

	DEB_EE("dev:%p\n", dev);

	अगर (शून्य == vv->ov_fb.base) अणु
		DEB_D("no fb base set\n");
		वापस -EINVAL;
	पूर्ण
	अगर (शून्य == vv->ov_fmt) अणु
		DEB_D("no fb fmt set\n");
		वापस -EINVAL;
	पूर्ण
	अगर (win->w.width < 48 || win->w.height < 32) अणु
		DEB_D("min width/height. (%d,%d)\n",
		      win->w.width, win->w.height);
		वापस -EINVAL;
	पूर्ण
	अगर (win->clipcount > 16) अणु
		DEB_D("clipcount too big\n");
		वापस -EINVAL;
	पूर्ण

	field = win->field;
	maxw  = vv->standard->h_max_out;
	maxh  = vv->standard->v_max_out;

	अगर (V4L2_FIELD_ANY == field) अणु
		field = (win->w.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
		पूर्ण
	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_ALTERNATE:
		maxh = maxh / 2;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	शेष:
		DEB_D("no known field mode '%d'\n", field);
		वापस -EINVAL;
	पूर्ण

	win->field = field;
	अगर (win->w.width > maxw)
		win->w.width = maxw;
	अगर (win->w.height > maxh)
		win->w.height = maxh;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_fh *fh = __fh;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	पूर्णांक err;

	DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: dev:%p, fh:%p\n", dev, fh);
	अगर (IS_CAPTURE_ACTIVE(fh) != 0) अणु
		DEB_EE("streaming capture is active\n");
		वापस -EBUSY;
	पूर्ण
	err = vidioc_try_fmt_vid_cap(file, fh, f);
	अगर (0 != err)
		वापस err;
	vv->video_fmt = f->fmt.pix;
	DEB_EE("set to pixelformat '%4.4s'\n",
	       (अक्षर *)&vv->video_fmt.pixelक्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_overlay(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7146_fh *fh = __fh;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	पूर्णांक err;

	DEB_EE("V4L2_BUF_TYPE_VIDEO_OVERLAY: dev:%p, fh:%p\n", dev, fh);
	err = vidioc_try_fmt_vid_overlay(file, fh, f);
	अगर (0 != err)
		वापस err;
	vv->ov.win    = f->fmt.win;
	vv->ov.nclips = f->fmt.win.clipcount;
	अगर (vv->ov.nclips > 16)
		vv->ov.nclips = 16;
	स_नकल(vv->ov.clips, f->fmt.win.clips,
	       माप(काष्ठा v4l2_clip) * vv->ov.nclips);

	/* vv->ov.fh is used to indicate that we have valid overlay inक्रमmation, too */
	vv->ov.fh = fh;

	/* check अगर our current overlay is active */
	अगर (IS_OVERLAY_ACTIVE(fh) != 0) अणु
		saa7146_stop_preview(fh);
		saa7146_start_preview(fh);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *fh, v4l2_std_id *norm)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;

	*norm = vv->standard->id;
	वापस 0;
पूर्ण

	/* the saa7146 supfhrts (used in conjunction with the saa7111a क्रम example)
	   PAL / NTSC / SECAM. अगर your hardware करोes not (or करोes more)
	   -- override this function in your extension */
/*
	हाल VIDIOC_ENUMSTD:
	अणु
		काष्ठा v4l2_standard *e = arg;
		अगर (e->index < 0 )
			वापस -EINVAL;
		अगर( e->index < dev->ext_vv_data->num_stds ) अणु
			DEB_EE("VIDIOC_ENUMSTD: index:%d\n", e->index);
			v4l2_video_std_स्थिरruct(e, dev->ext_vv_data->stds[e->index].id, dev->ext_vv_data->stds[e->index].name);
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	*/

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id id)
अणु
	काष्ठा saa7146_dev *dev = ((काष्ठा saa7146_fh *)fh)->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	पूर्णांक found = 0;
	पूर्णांक err, i;

	DEB_EE("VIDIOC_S_STD\n");

	अगर ((vv->video_status & STATUS_CAPTURE) == STATUS_CAPTURE) अणु
		DEB_D("cannot change video standard while streaming capture is active\n");
		वापस -EBUSY;
	पूर्ण

	अगर ((vv->video_status & STATUS_OVERLAY) != 0) अणु
		vv->ov_suspend = vv->video_fh;
		err = saa7146_stop_preview(vv->video_fh); /* side effect: video_status is now 0, video_fh is शून्य */
		अगर (0 != err) अणु
			DEB_D("suspending video failed. aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dev->ext_vv_data->num_stds; i++)
		अगर (id & dev->ext_vv_data->stds[i].id)
			अवरोध;
	अगर (i != dev->ext_vv_data->num_stds) अणु
		vv->standard = &dev->ext_vv_data->stds[i];
		अगर (शून्य != dev->ext_vv_data->std_callback)
			dev->ext_vv_data->std_callback(dev, vv->standard);
		found = 1;
	पूर्ण

	अगर (vv->ov_suspend != शून्य) अणु
		saa7146_start_preview(vv->ov_suspend);
		vv->ov_suspend = शून्य;
	पूर्ण

	अगर (!found) अणु
		DEB_EE("VIDIOC_S_STD: standard not found\n");
		वापस -EINVAL;
	पूर्ण

	DEB_EE("VIDIOC_S_STD: set to standard to '%s'\n", vv->standard->name);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक on)
अणु
	पूर्णांक err;

	DEB_D("VIDIOC_OVERLAY on:%d\n", on);
	अगर (on)
		err = saa7146_start_preview(fh);
	अन्यथा
		err = saa7146_stop_preview(fh);
	वापस err;
पूर्ण

अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_requestbuffers *b)
अणु
	काष्ठा saa7146_fh *fh = __fh;

	अगर (b->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस videobuf_reqbufs(&fh->video_q, b);
	अगर (b->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		वापस videobuf_reqbufs(&fh->vbi_q, b);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा saa7146_fh *fh = __fh;

	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस videobuf_querybuf(&fh->video_q, buf);
	अगर (buf->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		वापस videobuf_querybuf(&fh->vbi_q, buf);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा saa7146_fh *fh = __fh;

	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस videobuf_qbuf(&fh->video_q, buf);
	अगर (buf->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		वापस videobuf_qbuf(&fh->vbi_q, buf);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा saa7146_fh *fh = __fh;

	अगर (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस videobuf_dqbuf(&fh->video_q, buf, file->f_flags & O_NONBLOCK);
	अगर (buf->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		वापस videobuf_dqbuf(&fh->vbi_q, buf, file->f_flags & O_NONBLOCK);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *__fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा saa7146_fh *fh = __fh;
	पूर्णांक err;

	DEB_D("VIDIOC_STREAMON, type:%d\n", type);

	err = video_begin(fh);
	अगर (err)
		वापस err;
	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस videobuf_streamon(&fh->video_q);
	अगर (type == V4L2_BUF_TYPE_VBI_CAPTURE)
		वापस videobuf_streamon(&fh->vbi_q);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *__fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा saa7146_fh *fh = __fh;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	पूर्णांक err;

	DEB_D("VIDIOC_STREAMOFF, type:%d\n", type);

	/* ugly: we need to copy some checks from video_end(),
	   because videobuf_streamoff() relies on the capture running.
	   check and fix this */
	अगर ((vv->video_status & STATUS_CAPTURE) != STATUS_CAPTURE) अणु
		DEB_S("not capturing\n");
		वापस 0;
	पूर्ण

	अगर (vv->video_fh != fh) अणु
		DEB_S("capturing, but in another open\n");
		वापस -EBUSY;
	पूर्ण

	err = -EINVAL;
	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		err = videobuf_streamoff(&fh->video_q);
	अन्यथा अगर (type == V4L2_BUF_TYPE_VBI_CAPTURE)
		err = videobuf_streamoff(&fh->vbi_q);
	अगर (0 != err) अणु
		DEB_D("warning: videobuf_streamoff() failed\n");
		video_end(fh, file);
	पूर्ण अन्यथा अणु
		err = video_end(fh, file);
	पूर्ण
	वापस err;
पूर्ण

स्थिर काष्ठा v4l2_ioctl_ops saa7146_video_ioctl_ops = अणु
	.vidioc_querycap             = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap     = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_overlay = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap        = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap      = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap        = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_overlay    = vidioc_g_fmt_vid_overlay,
	.vidioc_try_fmt_vid_overlay  = vidioc_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_overlay    = vidioc_s_fmt_vid_overlay,

	.vidioc_overlay		     = vidioc_overlay,
	.vidioc_g_fbuf		     = vidioc_g_fbuf,
	.vidioc_s_fbuf		     = vidioc_s_fbuf,
	.vidioc_reqbufs              = vidioc_reqbufs,
	.vidioc_querybuf             = vidioc_querybuf,
	.vidioc_qbuf                 = vidioc_qbuf,
	.vidioc_dqbuf                = vidioc_dqbuf,
	.vidioc_g_std                = vidioc_g_std,
	.vidioc_s_std                = vidioc_s_std,
	.vidioc_streamon             = vidioc_streamon,
	.vidioc_streamoff            = vidioc_streamoff,
	.vidioc_g_parm		     = vidioc_g_parm,
	.vidioc_subscribe_event      = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event    = v4l2_event_unsubscribe,
पूर्ण;

स्थिर काष्ठा v4l2_ioctl_ops saa7146_vbi_ioctl_ops = अणु
	.vidioc_querycap             = vidioc_querycap,
	.vidioc_g_fmt_vbi_cap        = vidioc_g_fmt_vbi_cap,

	.vidioc_reqbufs              = vidioc_reqbufs,
	.vidioc_querybuf             = vidioc_querybuf,
	.vidioc_qbuf                 = vidioc_qbuf,
	.vidioc_dqbuf                = vidioc_dqbuf,
	.vidioc_g_std                = vidioc_g_std,
	.vidioc_s_std                = vidioc_s_std,
	.vidioc_streamon             = vidioc_streamon,
	.vidioc_streamoff            = vidioc_streamoff,
	.vidioc_g_parm		     = vidioc_g_parm,
	.vidioc_subscribe_event      = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event    = v4l2_event_unsubscribe,
पूर्ण;

/*********************************************************************************/
/* buffer handling functions                                                  */

अटल पूर्णांक buffer_activate (काष्ठा saa7146_dev *dev,
		     काष्ठा saa7146_buf *buf,
		     काष्ठा saa7146_buf *next)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;

	buf->vb.state = VIDEOBUF_ACTIVE;
	saa7146_set_capture(dev,buf,next);

	mod_समयr(&vv->video_dmaq.समयout, jअगरfies+BUFFER_TIMEOUT);
	वापस 0;
पूर्ण

अटल व्योम release_all_pagetables(काष्ठा saa7146_dev *dev, काष्ठा saa7146_buf *buf)
अणु
	saa7146_pgtable_मुक्त(dev->pci, &buf->pt[0]);
	saa7146_pgtable_मुक्त(dev->pci, &buf->pt[1]);
	saa7146_pgtable_मुक्त(dev->pci, &buf->pt[2]);
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा videobuf_queue *q,
			  काष्ठा videobuf_buffer *vb, क्रमागत v4l2_field field)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;
	पूर्णांक size,err = 0;

	DEB_CAP("vbuf:%p\n", vb);

	/* sanity checks */
	अगर (vv->video_fmt.width  < 48 ||
	    vv->video_fmt.height < 32 ||
	    vv->video_fmt.width  > vv->standard->h_max_out ||
	    vv->video_fmt.height > vv->standard->v_max_out) अणु
		DEB_D("w (%d) / h (%d) out of bounds\n",
		      vv->video_fmt.width, vv->video_fmt.height);
		वापस -EINVAL;
	पूर्ण

	size = vv->video_fmt.sizeimage;
	अगर (0 != buf->vb.baddr && buf->vb.bsize < size) अणु
		DEB_D("size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	DEB_CAP("buffer_prepare [size=%dx%d,bytes=%d,fields=%s]\n",
		vv->video_fmt.width, vv->video_fmt.height,
		size, v4l2_field_names[vv->video_fmt.field]);
	अगर (buf->vb.width  != vv->video_fmt.width  ||
	    buf->vb.bytesperline != vv->video_fmt.bytesperline ||
	    buf->vb.height != vv->video_fmt.height ||
	    buf->vb.size   != size ||
	    buf->vb.field  != field      ||
	    buf->vb.field  != vv->video_fmt.field  ||
	    buf->fmt       != &vv->video_fmt) अणु
		saa7146_dma_मुक्त(dev,q,buf);
	पूर्ण

	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		काष्ठा saa7146_क्रमmat *sfmt;

		buf->vb.bytesperline  = vv->video_fmt.bytesperline;
		buf->vb.width  = vv->video_fmt.width;
		buf->vb.height = vv->video_fmt.height;
		buf->vb.size   = size;
		buf->vb.field  = field;
		buf->fmt       = &vv->video_fmt;
		buf->vb.field  = vv->video_fmt.field;

		sfmt = saa7146_क्रमmat_by_fourcc(dev,buf->fmt->pixelक्रमmat);

		release_all_pagetables(dev, buf);
		अगर( 0 != IS_PLANAR(sfmt->trans)) अणु
			saa7146_pgtable_alloc(dev->pci, &buf->pt[0]);
			saa7146_pgtable_alloc(dev->pci, &buf->pt[1]);
			saa7146_pgtable_alloc(dev->pci, &buf->pt[2]);
		पूर्ण अन्यथा अणु
			saa7146_pgtable_alloc(dev->pci, &buf->pt[0]);
		पूर्ण

		err = videobuf_iolock(q,&buf->vb, &vv->ov_fb);
		अगर (err)
			जाओ oops;
		err = saa7146_pgtable_build(dev,buf);
		अगर (err)
			जाओ oops;
	पूर्ण
	buf->vb.state = VIDEOBUF_PREPARED;
	buf->activate = buffer_activate;

	वापस 0;

 oops:
	DEB_D("error out\n");
	saa7146_dma_मुक्त(dev,q,buf);

	वापस err;
पूर्ण

अटल पूर्णांक buffer_setup(काष्ठा videobuf_queue *q, अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_vv *vv = fh->dev->vv_data;

	अगर (0 == *count || *count > MAX_SAA7146_CAPTURE_BUFFERS)
		*count = MAX_SAA7146_CAPTURE_BUFFERS;

	*size = vv->video_fmt.sizeimage;

	/* check अगर we exceed the "max_memory" parameter */
	अगर( (*count * *size) > (max_memory*1048576) ) अणु
		*count = (max_memory*1048576) / *size;
	पूर्ण

	DEB_CAP("%d buffers, %d bytes each\n", *count, *size);

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;

	DEB_CAP("vbuf:%p\n", vb);
	saa7146_buffer_queue(fh->dev, &vv->video_dmaq, buf);
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;

	DEB_CAP("vbuf:%p\n", vb);

	saa7146_dma_मुक्त(dev,q,buf);

	release_all_pagetables(dev, buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops video_qops = अणु
	.buf_setup    = buffer_setup,
	.buf_prepare  = buffer_prepare,
	.buf_queue    = buffer_queue,
	.buf_release  = buffer_release,
पूर्ण;

/********************************************************************************/
/* file operations */

अटल व्योम video_init(काष्ठा saa7146_dev *dev, काष्ठा saa7146_vv *vv)
अणु
	INIT_LIST_HEAD(&vv->video_dmaq.queue);

	समयr_setup(&vv->video_dmaq.समयout, saa7146_buffer_समयout, 0);
	vv->video_dmaq.dev              = dev;

	/* set some शेष values */
	vv->standard = &dev->ext_vv_data->stds[0];

	/* FIXME: what's this? */
	vv->current_hps_source = SAA7146_HPS_SOURCE_PORT_A;
	vv->current_hps_sync = SAA7146_HPS_SYNC_PORT_A;
पूर्ण


अटल पूर्णांक video_खोलो(काष्ठा saa7146_dev *dev, काष्ठा file *file)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;

	videobuf_queue_sg_init(&fh->video_q, &video_qops,
			    &dev->pci->dev, &dev->slock,
			    V4L2_BUF_TYPE_VIDEO_CAPTURE,
			    V4L2_FIELD_INTERLACED,
			    माप(काष्ठा saa7146_buf),
			    file, &dev->v4l2_lock);

	वापस 0;
पूर्ण


अटल व्योम video_बंद(काष्ठा saa7146_dev *dev, काष्ठा file *file)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा videobuf_queue *q = &fh->video_q;

	अगर (IS_CAPTURE_ACTIVE(fh) != 0)
		video_end(fh, file);
	अन्यथा अगर (IS_OVERLAY_ACTIVE(fh) != 0)
		saa7146_stop_preview(fh);

	videobuf_stop(q);
	/* hmm, why is this function declared व्योम? */
पूर्ण


अटल व्योम video_irq_करोne(काष्ठा saa7146_dev *dev, अचिन्हित दीर्घ st)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_dmaqueue *q = &vv->video_dmaq;

	spin_lock(&dev->slock);
	DEB_CAP("called\n");

	/* only finish the buffer अगर we have one... */
	अगर( शून्य != q->curr ) अणु
		saa7146_buffer_finish(dev,q,VIDEOBUF_DONE);
	पूर्ण
	saa7146_buffer_next(dev,q,0);

	spin_unlock(&dev->slock);
पूर्ण

अटल sमाप_प्रकार video_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	sमाप_प्रकार ret = 0;

	DEB_EE("called\n");

	अगर ((vv->video_status & STATUS_CAPTURE) != 0) अणु
		/* fixme: should we allow पढ़ो() captures जबतक streaming capture? */
		अगर (vv->video_fh == fh) अणु
			DEB_S("already capturing\n");
			वापस -EBUSY;
		पूर्ण
		DEB_S("already capturing in another open\n");
		वापस -EBUSY;
	पूर्ण

	ret = video_begin(fh);
	अगर( 0 != ret) अणु
		जाओ out;
	पूर्ण

	ret = videobuf_पढ़ो_one(&fh->video_q , data, count, ppos,
				file->f_flags & O_NONBLOCK);
	अगर (ret != 0) अणु
		video_end(fh, file);
	पूर्ण अन्यथा अणु
		ret = video_end(fh, file);
	पूर्ण
out:
	/* restart overlay अगर it was active beक्रमe */
	अगर (vv->ov_suspend != शून्य) अणु
		saa7146_start_preview(vv->ov_suspend);
		vv->ov_suspend = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा saa7146_use_ops saa7146_video_uops = अणु
	.init = video_init,
	.खोलो = video_खोलो,
	.release = video_बंद,
	.irq_करोne = video_irq_करोne,
	.पढ़ो = video_पढ़ो,
पूर्ण;
