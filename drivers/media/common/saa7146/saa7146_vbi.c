<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>

अटल पूर्णांक vbi_pixel_to_capture = 720 * 2;

अटल पूर्णांक vbi_workaround(काष्ठा saa7146_dev *dev)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;

	u32          *cpu;
	dma_addr_t   dma_addr;

	पूर्णांक count = 0;
	पूर्णांक i;

	DECLARE_WAITQUEUE(रुको, current);

	DEB_VBI("dev:%p\n", dev);

	/* once again, a bug in the saa7146: the brs acquisition
	   is buggy and especially the BXO-counter करोes not work
	   as specअगरied. there is this workaround, but please
	   करोn't let me explain it. ;-) */

	cpu = dma_alloc_coherent(&dev->pci->dev, 4096, &dma_addr, GFP_KERNEL);
	अगर (शून्य == cpu)
		वापस -ENOMEM;

	/* setup some basic programming, just क्रम the workaround */
	saa7146_ग_लिखो(dev, BASE_EVEN3,	dma_addr);
	saa7146_ग_लिखो(dev, BASE_ODD3,	dma_addr+vbi_pixel_to_capture);
	saa7146_ग_लिखो(dev, PROT_ADDR3,	dma_addr+4096);
	saa7146_ग_लिखो(dev, PITCH3,	vbi_pixel_to_capture);
	saa7146_ग_लिखो(dev, BASE_PAGE3,	0x0);
	saa7146_ग_लिखो(dev, NUM_LINE_BYTE3, (2<<16)|((vbi_pixel_to_capture)<<0));
	saa7146_ग_लिखो(dev, MC2, MASK_04|MASK_20);

	/* load brs-control रेजिस्टर */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (BRS_CTRL/4));
	/* BXO = 1h, BRS to outbound */
	WRITE_RPS1(0xc000008c);
	/* रुको क्रम vbi_a or vbi_b*/
	अगर ( 0 != (SAA7146_USE_PORT_B_FOR_VBI & dev->ext_vv_data->flags)) अणु
		DEB_D("...using port b\n");
		WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | CMD_E_FID_B);
		WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | CMD_O_FID_B);
/*
		WRITE_RPS1(CMD_PAUSE | MASK_09);
*/
	पूर्ण अन्यथा अणु
		DEB_D("...using port a\n");
		WRITE_RPS1(CMD_PAUSE | MASK_10);
	पूर्ण
	/* upload brs */
	WRITE_RPS1(CMD_UPLOAD | MASK_08);
	/* load brs-control रेजिस्टर */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (BRS_CTRL/4));
	/* BYO = 1, BXO = NQBIL (=1728 क्रम PAL, क्रम NTSC this is 858*2) - NumByte3 (=1440) = 288 */
	WRITE_RPS1(((1728-(vbi_pixel_to_capture)) << 7) | MASK_19);
	/* रुको क्रम brs_करोne */
	WRITE_RPS1(CMD_PAUSE | MASK_08);
	/* upload brs */
	WRITE_RPS1(CMD_UPLOAD | MASK_08);
	/* load video-dma3 NumLines3 and NumBytes3 */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (NUM_LINE_BYTE3/4));
	/* dev->vbi_count*2 lines, 720 pixel (= 1440 Bytes) */
	WRITE_RPS1((2 << 16) | (vbi_pixel_to_capture));
	/* load brs-control रेजिस्टर */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (BRS_CTRL/4));
	/* Set BRS right: note: this is an experimental value क्रम BXO (=> PAL!) */
	WRITE_RPS1((540 << 7) | (5 << 19));  // 5 == vbi_start
	/* रुको क्रम brs_करोne */
	WRITE_RPS1(CMD_PAUSE | MASK_08);
	/* upload brs and video-dma3*/
	WRITE_RPS1(CMD_UPLOAD | MASK_08 | MASK_04);
	/* load mc2 रेजिस्टर: enable dma3 */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (MC1/4));
	WRITE_RPS1(MASK_20 | MASK_04);
	/* generate पूर्णांकerrupt */
	WRITE_RPS1(CMD_INTERRUPT);
	/* stop rps1 */
	WRITE_RPS1(CMD_STOP);

	/* we have to करो the workaround twice to be sure that
	   everything is ok */
	क्रम(i = 0; i < 2; i++) अणु

		/* indicate to the irq handler that we करो the workaround */
		saa7146_ग_लिखो(dev, MC2, MASK_31|MASK_15);

		saa7146_ग_लिखो(dev, NUM_LINE_BYTE3, (1<<16)|(2<<0));
		saa7146_ग_लिखो(dev, MC2, MASK_04|MASK_20);

		/* enable rps1 irqs */
		SAA7146_IER_ENABLE(dev,MASK_28);

		/* prepare to रुको to be woken up by the irq-handler */
		add_रुको_queue(&vv->vbi_wq, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);

		/* start rps1 to enable workaround */
		saa7146_ग_लिखो(dev, RPS_ADDR1, dev->d_rps1.dma_handle);
		saa7146_ग_लिखो(dev, MC1, (MASK_13 | MASK_29));

		schedule();

		DEB_VBI("brs bug workaround %d/1\n", i);

		हटाओ_रुको_queue(&vv->vbi_wq, &रुको);
		__set_current_state(TASK_RUNNING);

		/* disable rps1 irqs */
		SAA7146_IER_DISABLE(dev,MASK_28);

		/* stop video-dma3 */
		saa7146_ग_लिखो(dev, MC1, MASK_20);

		अगर(संकेत_pending(current)) अणु

			DEB_VBI("aborted (rps:0x%08x)\n",
				saa7146_पढ़ो(dev, RPS_ADDR1));

			/* stop rps1 क्रम sure */
			saa7146_ग_लिखो(dev, MC1, MASK_29);

			dma_मुक्त_coherent(&dev->pci->dev, 4096, cpu, dma_addr);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&dev->pci->dev, 4096, cpu, dma_addr);
	वापस 0;
पूर्ण

अटल व्योम saa7146_set_vbi_capture(काष्ठा saa7146_dev *dev, काष्ठा saa7146_buf *buf, काष्ठा saa7146_buf *next)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;

	काष्ठा saa7146_video_dma vdma3;

	पूर्णांक count = 0;
	अचिन्हित दीर्घ e_रुको = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_E_FID_A : CMD_E_FID_B;
	अचिन्हित दीर्घ o_रुको = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_O_FID_A : CMD_O_FID_B;

/*
	vdma3.base_even	= 0xc8000000+2560*70;
	vdma3.base_odd	= 0xc8000000;
	vdma3.prot_addr	= 0xc8000000+2560*164;
	vdma3.pitch	= 2560;
	vdma3.base_page	= 0;
	vdma3.num_line_byte = (64<<16)|((vbi_pixel_to_capture)<<0); // set above!
*/
	vdma3.base_even	= buf->pt[2].offset;
	vdma3.base_odd	= buf->pt[2].offset + 16 * vbi_pixel_to_capture;
	vdma3.prot_addr	= buf->pt[2].offset + 16 * 2 * vbi_pixel_to_capture;
	vdma3.pitch	= vbi_pixel_to_capture;
	vdma3.base_page	= buf->pt[2].dma | ME1;
	vdma3.num_line_byte = (16 << 16) | vbi_pixel_to_capture;

	saa7146_ग_लिखो_out_dma(dev, 3, &vdma3);

	/* ग_लिखो beginning of rps-program */
	count = 0;

	/* रुको क्रम o_fid_a/b / e_fid_a/b toggle only अगर bit 1 is not set */

	/* we करोn't रुको here क्रम the first field anymore. this is dअगरferent from the video
	   capture and might cause that the first buffer is only half filled (with only
	   one field). but since this is some sort of streaming data, this is not that negative.
	   but by करोing this, we can use the whole engine from videobuf-dma-sg.c... */

/*
	WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | e_रुको);
	WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | o_रुको);
*/
	/* set bit 1 */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (MC2/4));
	WRITE_RPS1(MASK_28 | MASK_12);

	/* turn on video-dma3 */
	WRITE_RPS1(CMD_WR_REG_MASK | (MC1/4));
	WRITE_RPS1(MASK_04 | MASK_20);			/* => mask */
	WRITE_RPS1(MASK_04 | MASK_20);			/* => values */

	/* रुको क्रम o_fid_a/b / e_fid_a/b toggle */
	WRITE_RPS1(CMD_PAUSE | o_रुको);
	WRITE_RPS1(CMD_PAUSE | e_रुको);

	/* generate पूर्णांकerrupt */
	WRITE_RPS1(CMD_INTERRUPT);

	/* stop */
	WRITE_RPS1(CMD_STOP);

	/* enable rps1 irqs */
	SAA7146_IER_ENABLE(dev, MASK_28);

	/* ग_लिखो the address of the rps-program */
	saa7146_ग_लिखो(dev, RPS_ADDR1, dev->d_rps1.dma_handle);

	/* turn on rps */
	saa7146_ग_लिखो(dev, MC1, (MASK_13 | MASK_29));
पूर्ण

अटल पूर्णांक buffer_activate(काष्ठा saa7146_dev *dev,
			   काष्ठा saa7146_buf *buf,
			   काष्ठा saa7146_buf *next)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	buf->vb.state = VIDEOBUF_ACTIVE;

	DEB_VBI("dev:%p, buf:%p, next:%p\n", dev, buf, next);
	saa7146_set_vbi_capture(dev,buf,next);

	mod_समयr(&vv->vbi_dmaq.समयout, jअगरfies+BUFFER_TIMEOUT);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,क्रमागत v4l2_field field)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;

	पूर्णांक err = 0;
	पूर्णांक lines, llength, size;

	lines   = 16 * 2 ; /* 2 fields */
	llength = vbi_pixel_to_capture;
	size = lines * llength;

	DEB_VBI("vb:%p\n", vb);

	अगर (0 != buf->vb.baddr  &&  buf->vb.bsize < size) अणु
		DEB_VBI("size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (buf->vb.size != size)
		saa7146_dma_मुक्त(dev,q,buf);

	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		काष्ठा videobuf_dmabuf *dma=videobuf_to_dma(&buf->vb);

		buf->vb.width  = llength;
		buf->vb.height = lines;
		buf->vb.size   = size;
		buf->vb.field  = field;	// FIXME: check this

		saa7146_pgtable_मुक्त(dev->pci, &buf->pt[2]);
		saa7146_pgtable_alloc(dev->pci, &buf->pt[2]);

		err = videobuf_iolock(q,&buf->vb, शून्य);
		अगर (err)
			जाओ oops;
		err = saa7146_pgtable_build_single(dev->pci, &buf->pt[2],
						 dma->sglist, dma->sglen);
		अगर (0 != err)
			वापस err;
	पूर्ण
	buf->vb.state = VIDEOBUF_PREPARED;
	buf->activate = buffer_activate;

	वापस 0;

 oops:
	DEB_VBI("error out\n");
	saa7146_dma_मुक्त(dev,q,buf);

	वापस err;
पूर्ण

अटल पूर्णांक buffer_setup(काष्ठा videobuf_queue *q, अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	पूर्णांक llength,lines;

	lines   = 16 * 2 ; /* 2 fields */
	llength = vbi_pixel_to_capture;

	*size = lines * llength;
	*count = 2;

	DEB_VBI("count:%d, size:%d\n", *count, *size);

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;

	DEB_VBI("vb:%p\n", vb);
	saa7146_buffer_queue(dev, &vv->vbi_dmaq, buf);
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा file *file = q->priv_data;
	काष्ठा saa7146_fh *fh   = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_buf *buf = (काष्ठा saa7146_buf *)vb;

	DEB_VBI("vb:%p\n", vb);
	saa7146_dma_मुक्त(dev,q,buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops vbi_qops = अणु
	.buf_setup    = buffer_setup,
	.buf_prepare  = buffer_prepare,
	.buf_queue    = buffer_queue,
	.buf_release  = buffer_release,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल व्योम vbi_stop(काष्ठा saa7146_fh *fh, काष्ठा file *file)
अणु
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	अचिन्हित दीर्घ flags;
	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	spin_lock_irqsave(&dev->slock,flags);

	/* disable rps1  */
	saa7146_ग_लिखो(dev, MC1, MASK_29);

	/* disable rps1 irqs */
	SAA7146_IER_DISABLE(dev, MASK_28);

	/* shut करोwn dma 3 transfers */
	saa7146_ग_लिखो(dev, MC1, MASK_20);

	अगर (vv->vbi_dmaq.curr)
		saa7146_buffer_finish(dev, &vv->vbi_dmaq, VIDEOBUF_DONE);

	videobuf_queue_cancel(&fh->vbi_q);

	vv->vbi_streaming = शून्य;

	del_समयr(&vv->vbi_dmaq.समयout);
	del_समयr(&vv->vbi_पढ़ो_समयout);

	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल व्योम vbi_पढ़ो_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा saa7146_vv *vv = from_समयr(vv, t, vbi_पढ़ो_समयout);
	काष्ठा file *file = vv->vbi_पढ़ो_समयout_file;
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;

	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	vbi_stop(fh, file);
पूर्ण

अटल व्योम vbi_init(काष्ठा saa7146_dev *dev, काष्ठा saa7146_vv *vv)
अणु
	DEB_VBI("dev:%p\n", dev);

	INIT_LIST_HEAD(&vv->vbi_dmaq.queue);

	समयr_setup(&vv->vbi_dmaq.समयout, saa7146_buffer_समयout, 0);
	vv->vbi_dmaq.dev              = dev;

	init_रुकोqueue_head(&vv->vbi_wq);
पूर्ण

अटल पूर्णांक vbi_खोलो(काष्ठा saa7146_dev *dev, काष्ठा file *file)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_vv *vv = fh->dev->vv_data;

	u32 arbtr_ctrl	= saa7146_पढ़ो(dev, PCI_BT_V1);
	पूर्णांक ret = 0;

	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	ret = saa7146_res_get(fh, RESOURCE_DMA3_BRS);
	अगर (0 == ret) अणु
		DEB_S("cannot get vbi RESOURCE_DMA3_BRS resource\n");
		वापस -EBUSY;
	पूर्ण

	/* adjust arbitrition control क्रम video dma 3 */
	arbtr_ctrl &= ~0x1f0000;
	arbtr_ctrl |=  0x1d0000;
	saa7146_ग_लिखो(dev, PCI_BT_V1, arbtr_ctrl);
	saa7146_ग_लिखो(dev, MC2, (MASK_04|MASK_20));

	videobuf_queue_sg_init(&fh->vbi_q, &vbi_qops,
			    &dev->pci->dev, &dev->slock,
			    V4L2_BUF_TYPE_VBI_CAPTURE,
			    V4L2_FIELD_SEQ_TB, // FIXME: करोes this really work?
			    माप(काष्ठा saa7146_buf),
			    file, &dev->v4l2_lock);

	vv->vbi_पढ़ो_समयout.function = vbi_पढ़ो_समयout;
	vv->vbi_पढ़ो_समयout_file = file;

	/* initialize the brs */
	अगर ( 0 != (SAA7146_USE_PORT_B_FOR_VBI & dev->ext_vv_data->flags)) अणु
		saa7146_ग_लिखो(dev, BRS_CTRL, MASK_30|MASK_29 | (7 << 19));
	पूर्ण अन्यथा अणु
		saa7146_ग_लिखो(dev, BRS_CTRL, 0x00000001);

		अगर (0 != (ret = vbi_workaround(dev))) अणु
			DEB_VBI("vbi workaround failed!\n");
			/* वापस ret;*/
		पूर्ण
	पूर्ण

	/* upload brs रेजिस्टर */
	saa7146_ग_लिखो(dev, MC2, (MASK_08|MASK_24));
	वापस 0;
पूर्ण

अटल व्योम vbi_बंद(काष्ठा saa7146_dev *dev, काष्ठा file *file)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	अगर( fh == vv->vbi_streaming ) अणु
		vbi_stop(fh, file);
	पूर्ण
	saa7146_res_मुक्त(fh, RESOURCE_DMA3_BRS);
पूर्ण

अटल व्योम vbi_irq_करोne(काष्ठा saa7146_dev *dev, अचिन्हित दीर्घ status)
अणु
	काष्ठा saa7146_vv *vv = dev->vv_data;
	spin_lock(&dev->slock);

	अगर (vv->vbi_dmaq.curr) अणु
		DEB_VBI("dev:%p, curr:%p\n", dev, vv->vbi_dmaq.curr);
		/* this must be += 2, one count क्रम each field */
		vv->vbi_fieldcount+=2;
		vv->vbi_dmaq.curr->vb.field_count = vv->vbi_fieldcount;
		saa7146_buffer_finish(dev, &vv->vbi_dmaq, VIDEOBUF_DONE);
	पूर्ण अन्यथा अणु
		DEB_VBI("dev:%p\n", dev);
	पूर्ण
	saa7146_buffer_next(dev, &vv->vbi_dmaq, 1);

	spin_unlock(&dev->slock);
पूर्ण

अटल sमाप_प्रकार vbi_पढ़ो(काष्ठा file *file, अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा saa7146_fh *fh = file->निजी_data;
	काष्ठा saa7146_dev *dev = fh->dev;
	काष्ठा saa7146_vv *vv = dev->vv_data;
	sमाप_प्रकार ret = 0;

	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	अगर( शून्य == vv->vbi_streaming ) अणु
		// fixme: check अगर dma3 is available
		// fixme: activate vbi engine here अगर necessary. (really?)
		vv->vbi_streaming = fh;
	पूर्ण

	अगर( fh != vv->vbi_streaming ) अणु
		DEB_VBI("open %p is already using vbi capture\n",
			vv->vbi_streaming);
		वापस -EBUSY;
	पूर्ण

	mod_समयr(&vv->vbi_पढ़ो_समयout, jअगरfies+BUFFER_TIMEOUT);
	ret = videobuf_पढ़ो_stream(&fh->vbi_q, data, count, ppos, 1,
				   file->f_flags & O_NONBLOCK);
/*
	prपूर्णांकk("BASE_ODD3:      0x%08x\n", saa7146_पढ़ो(dev, BASE_ODD3));
	prपूर्णांकk("BASE_EVEN3:     0x%08x\n", saa7146_पढ़ो(dev, BASE_EVEN3));
	prपूर्णांकk("PROT_ADDR3:     0x%08x\n", saa7146_पढ़ो(dev, PROT_ADDR3));
	prपूर्णांकk("PITCH3:         0x%08x\n", saa7146_पढ़ो(dev, PITCH3));
	prपूर्णांकk("BASE_PAGE3:     0x%08x\n", saa7146_पढ़ो(dev, BASE_PAGE3));
	prपूर्णांकk("NUM_LINE_BYTE3: 0x%08x\n", saa7146_पढ़ो(dev, NUM_LINE_BYTE3));
	prपूर्णांकk("BRS_CTRL:       0x%08x\n", saa7146_पढ़ो(dev, BRS_CTRL));
*/
	वापस ret;
पूर्ण

स्थिर काष्ठा saa7146_use_ops saa7146_vbi_uops = अणु
	.init		= vbi_init,
	.खोलो		= vbi_खोलो,
	.release	= vbi_बंद,
	.irq_करोne	= vbi_irq_करोne,
	.पढ़ो		= vbi_पढ़ो,
पूर्ण;
