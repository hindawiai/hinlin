<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2006-2010 by Marin Mitov                                *
 *   mitov@issp.bas.bg                                                     *
 *                                                                         *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "dt3155.h"

#घोषणा DT3155_DEVICE_ID 0x1223

/**
 * पढ़ो_i2c_reg - पढ़ोs an पूर्णांकernal i2c रेजिस्टर
 *
 * @addr:	dt3155 mmio base address
 * @index:	index (पूर्णांकernal address) of रेजिस्टर to पढ़ो
 * @data:	poपूर्णांकer to byte the पढ़ो data will be placed in
 *
 * वापसs:	zero on success or error code
 *
 * This function starts पढ़ोing the specअगरied (by index) रेजिस्टर
 * and busy रुकोs क्रम the process to finish. The result is placed
 * in a byte poपूर्णांकed by data.
 */
अटल पूर्णांक पढ़ो_i2c_reg(व्योम __iomem *addr, u8 index, u8 *data)
अणु
	u32 पंचांगp = index;

	ioग_लिखो32((पंचांगp << 17) | IIC_READ, addr + IIC_CSR2);
	udelay(45); /* रुको at least 43 usec क्रम NEW_CYCLE to clear */
	अगर (ioपढ़ो32(addr + IIC_CSR2) & NEW_CYCLE)
		वापस -EIO; /* error: NEW_CYCLE not cleared */
	पंचांगp = ioपढ़ो32(addr + IIC_CSR1);
	अगर (पंचांगp & सूचीECT_ABORT) अणु
		/* reset सूचीECT_ABORT bit */
		ioग_लिखो32(सूचीECT_ABORT, addr + IIC_CSR1);
		वापस -EIO; /* error: सूचीECT_ABORT set */
	पूर्ण
	*data = पंचांगp >> 24;
	वापस 0;
पूर्ण

/**
 * ग_लिखो_i2c_reg - ग_लिखोs to an पूर्णांकernal i2c रेजिस्टर
 *
 * @addr:	dt3155 mmio base address
 * @index:	index (पूर्णांकernal address) of रेजिस्टर to पढ़ो
 * @data:	data to be written
 *
 * वापसs:	zero on success or error code
 *
 * This function starts writing the specअगरied (by index) रेजिस्टर
 * and busy रुकोs क्रम the process to finish.
 */
अटल पूर्णांक ग_लिखो_i2c_reg(व्योम __iomem *addr, u8 index, u8 data)
अणु
	u32 पंचांगp = index;

	ioग_लिखो32((पंचांगp << 17) | IIC_WRITE | data, addr + IIC_CSR2);
	udelay(65); /* रुको at least 63 usec क्रम NEW_CYCLE to clear */
	अगर (ioपढ़ो32(addr + IIC_CSR2) & NEW_CYCLE)
		वापस -EIO; /* error: NEW_CYCLE not cleared */
	अगर (ioपढ़ो32(addr + IIC_CSR1) & सूचीECT_ABORT) अणु
		/* reset सूचीECT_ABORT bit */
		ioग_लिखो32(सूचीECT_ABORT, addr + IIC_CSR1);
		वापस -EIO; /* error: सूचीECT_ABORT set */
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ग_लिखो_i2c_reg_noरुको - ग_लिखोs to an पूर्णांकernal i2c रेजिस्टर
 *
 * @addr:	dt3155 mmio base address
 * @index:	index (पूर्णांकernal address) of रेजिस्टर to पढ़ो
 * @data:	data to be written
 *
 * This function starts writing the specअगरied (by index) रेजिस्टर
 * and then वापसs.
 */
अटल व्योम ग_लिखो_i2c_reg_noरुको(व्योम __iomem *addr, u8 index, u8 data)
अणु
	u32 पंचांगp = index;

	ioग_लिखो32((पंचांगp << 17) | IIC_WRITE | data, addr + IIC_CSR2);
पूर्ण

/**
 * रुको_i2c_reg - रुकोs the पढ़ो/ग_लिखो to finish
 *
 * @addr:	dt3155 mmio base address
 *
 * वापसs:	zero on success or error code
 *
 * This function रुकोs पढ़ोing/writing to finish.
 */
अटल पूर्णांक रुको_i2c_reg(व्योम __iomem *addr)
अणु
	अगर (ioपढ़ो32(addr + IIC_CSR2) & NEW_CYCLE)
		udelay(65); /* रुको at least 63 usec क्रम NEW_CYCLE to clear */
	अगर (ioपढ़ो32(addr + IIC_CSR2) & NEW_CYCLE)
		वापस -EIO; /* error: NEW_CYCLE not cleared */
	अगर (ioपढ़ो32(addr + IIC_CSR1) & सूचीECT_ABORT) अणु
		/* reset सूचीECT_ABORT bit */
		ioग_लिखो32(सूचीECT_ABORT, addr + IIC_CSR1);
		वापस -EIO; /* error: सूचीECT_ABORT set */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
dt3155_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *num_planes,
		अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])

अणु
	काष्ठा dt3155_priv *pd = vb2_get_drv_priv(vq);
	अचिन्हित size = pd->width * pd->height;

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;
	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*num_planes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा dt3155_priv *pd = vb2_get_drv_priv(vb->vb2_queue);

	vb2_set_plane_payload(vb, 0, pd->width * pd->height);
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_start_streaming(काष्ठा vb2_queue *q, अचिन्हित count)
अणु
	काष्ठा dt3155_priv *pd = vb2_get_drv_priv(q);
	काष्ठा vb2_buffer *vb = &pd->curr_buf->vb2_buf;
	dma_addr_t dma_addr;

	pd->sequence = 0;
	dma_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	ioग_लिखो32(dma_addr, pd->regs + EVEN_DMA_START);
	ioग_लिखो32(dma_addr + pd->width, pd->regs + ODD_DMA_START);
	ioग_लिखो32(pd->width, pd->regs + EVEN_DMA_STRIDE);
	ioग_लिखो32(pd->width, pd->regs + ODD_DMA_STRIDE);
	/* enable पूर्णांकerrupts, clear all irq flags */
	ioग_लिखो32(FLD_START_EN | FLD_END_ODD_EN | FLD_START |
			FLD_END_EVEN | FLD_END_ODD, pd->regs + INT_CSR);
	ioग_लिखो32(FIFO_EN | SRST | FLD_CRPT_ODD | FLD_CRPT_EVEN |
		  FLD_DN_ODD | FLD_DN_EVEN | CAP_CONT_EVEN | CAP_CONT_ODD,
							pd->regs + CSR1);
	रुको_i2c_reg(pd->regs);
	ग_लिखो_i2c_reg(pd->regs, CONFIG, pd->config);
	ग_लिखो_i2c_reg(pd->regs, EVEN_CSR, CSR_ERROR | CSR_DONE);
	ग_लिखो_i2c_reg(pd->regs, ODD_CSR, CSR_ERROR | CSR_DONE);

	/*  start the board  */
	ग_लिखो_i2c_reg(pd->regs, CSR2, pd->csr2 | BUSY_EVEN | BUSY_ODD);
	वापस 0;
पूर्ण

अटल व्योम dt3155_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा dt3155_priv *pd = vb2_get_drv_priv(q);
	काष्ठा vb2_buffer *vb;

	spin_lock_irq(&pd->lock);
	/* stop the board */
	ग_लिखो_i2c_reg_noरुको(pd->regs, CSR2, pd->csr2);
	ioग_लिखो32(FIFO_EN | SRST | FLD_CRPT_ODD | FLD_CRPT_EVEN |
		  FLD_DN_ODD | FLD_DN_EVEN, pd->regs + CSR1);
	/* disable पूर्णांकerrupts, clear all irq flags */
	ioग_लिखो32(FLD_START | FLD_END_EVEN | FLD_END_ODD, pd->regs + INT_CSR);
	spin_unlock_irq(&pd->lock);

	/*
	 * It is not clear whether the DMA stops at once or whether it
	 * will finish the current frame or field first. To be on the
	 * safe side we रुको a bit.
	 */
	msleep(45);

	spin_lock_irq(&pd->lock);
	अगर (pd->curr_buf) अणु
		vb2_buffer_करोne(&pd->curr_buf->vb2_buf, VB2_BUF_STATE_ERROR);
		pd->curr_buf = शून्य;
	पूर्ण

	जबतक (!list_empty(&pd->dmaq)) अणु
		vb = list_first_entry(&pd->dmaq, typeof(*vb), करोne_entry);
		list_del(&vb->करोne_entry);
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irq(&pd->lock);
पूर्ण

अटल व्योम dt3155_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा dt3155_priv *pd = vb2_get_drv_priv(vb->vb2_queue);

	/*  pd->vidq.streaming = 1 when dt3155_buf_queue() is invoked  */
	spin_lock_irq(&pd->lock);
	अगर (pd->curr_buf)
		list_add_tail(&vb->करोne_entry, &pd->dmaq);
	अन्यथा
		pd->curr_buf = vbuf;
	spin_unlock_irq(&pd->lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops q_ops = अणु
	.queue_setup = dt3155_queue_setup,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.buf_prepare = dt3155_buf_prepare,
	.start_streaming = dt3155_start_streaming,
	.stop_streaming = dt3155_stop_streaming,
	.buf_queue = dt3155_buf_queue,
पूर्ण;

अटल irqवापस_t dt3155_irq_handler_even(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dt3155_priv *ipd = dev_id;
	काष्ठा vb2_buffer *ivb;
	dma_addr_t dma_addr;
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32(ipd->regs + INT_CSR) & (FLD_START | FLD_END_ODD);
	अगर (!पंचांगp)
		वापस IRQ_NONE;  /* not our irq */
	अगर ((पंचांगp & FLD_START) && !(पंचांगp & FLD_END_ODD)) अणु
		ioग_लिखो32(FLD_START_EN | FLD_END_ODD_EN | FLD_START,
							ipd->regs + INT_CSR);
		वापस IRQ_HANDLED; /* start of field irq */
	पूर्ण
	पंचांगp = ioपढ़ो32(ipd->regs + CSR1) & (FLD_CRPT_EVEN | FLD_CRPT_ODD);
	अगर (पंचांगp) अणु
		ioग_लिखो32(FIFO_EN | SRST | FLD_CRPT_ODD | FLD_CRPT_EVEN |
						FLD_DN_ODD | FLD_DN_EVEN |
						CAP_CONT_EVEN | CAP_CONT_ODD,
							ipd->regs + CSR1);
	पूर्ण

	spin_lock(&ipd->lock);
	अगर (ipd->curr_buf && !list_empty(&ipd->dmaq)) अणु
		ipd->curr_buf->vb2_buf.बारtamp = kसमय_get_ns();
		ipd->curr_buf->sequence = ipd->sequence++;
		ipd->curr_buf->field = V4L2_FIELD_NONE;
		vb2_buffer_करोne(&ipd->curr_buf->vb2_buf, VB2_BUF_STATE_DONE);

		ivb = list_first_entry(&ipd->dmaq, typeof(*ivb), करोne_entry);
		list_del(&ivb->करोne_entry);
		ipd->curr_buf = to_vb2_v4l2_buffer(ivb);
		dma_addr = vb2_dma_contig_plane_dma_addr(ivb, 0);
		ioग_लिखो32(dma_addr, ipd->regs + EVEN_DMA_START);
		ioग_लिखो32(dma_addr + ipd->width, ipd->regs + ODD_DMA_START);
		ioग_लिखो32(ipd->width, ipd->regs + EVEN_DMA_STRIDE);
		ioग_लिखो32(ipd->width, ipd->regs + ODD_DMA_STRIDE);
	पूर्ण

	/* enable पूर्णांकerrupts, clear all irq flags */
	ioग_लिखो32(FLD_START_EN | FLD_END_ODD_EN | FLD_START |
			FLD_END_EVEN | FLD_END_ODD, ipd->regs + INT_CSR);
	spin_unlock(&ipd->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations dt3155_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll
पूर्ण;

अटल पूर्णांक dt3155_querycap(काष्ठा file *filp, व्योम *p,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	strscpy(cap->driver, DT3155_NAME, माप(cap->driver));
	strscpy(cap->card, DT3155_NAME " frame grabber", माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(pd->pdev));
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_क्रमागत_fmt_vid_cap(काष्ठा file *filp,
				   व्योम *p, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;
	f->pixelक्रमmat = V4L2_PIX_FMT_GREY;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_fmt_vid_cap(काष्ठा file *filp, व्योम *p, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	f->fmt.pix.width = pd->width;
	f->fmt.pix.height = pd->height;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = f->fmt.pix.width;
	f->fmt.pix.sizeimage = f->fmt.pix.width * f->fmt.pix.height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_g_std(काष्ठा file *filp, व्योम *p, v4l2_std_id *norm)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	*norm = pd->std;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_s_std(काष्ठा file *filp, व्योम *p, v4l2_std_id norm)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	अगर (pd->std == norm)
		वापस 0;
	अगर (vb2_is_busy(&pd->vidq))
		वापस -EBUSY;
	pd->std = norm;
	अगर (pd->std & V4L2_STD_525_60) अणु
		pd->csr2 = VT_60HZ;
		pd->width = 640;
		pd->height = 480;
	पूर्ण अन्यथा अणु
		pd->csr2 = VT_50HZ;
		pd->width = 768;
		pd->height = 576;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_क्रमागत_input(काष्ठा file *filp, व्योम *p,
			     काष्ठा v4l2_input *input)
अणु
	अगर (input->index > 3)
		वापस -EINVAL;
	अगर (input->index)
		snम_लिखो(input->name, माप(input->name), "VID%d",
			 input->index);
	अन्यथा
		strscpy(input->name, "J2/VID0", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = V4L2_STD_ALL;
	input->status = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_g_input(काष्ठा file *filp, व्योम *p, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	*i = pd->input;
	वापस 0;
पूर्ण

अटल पूर्णांक dt3155_s_input(काष्ठा file *filp, व्योम *p, अचिन्हित पूर्णांक i)
अणु
	काष्ठा dt3155_priv *pd = video_drvdata(filp);

	अगर (i > 3)
		वापस -EINVAL;
	pd->input = i;
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	ग_लिखो_i2c_reg(pd->regs, AD_CMD, (i << 6) | (i << 4) | SYNC_LVL_3);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops dt3155_ioctl_ops = अणु
	.vidioc_querycap = dt3155_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = dt3155_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = dt3155_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = dt3155_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = dt3155_fmt_vid_cap,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_g_std = dt3155_g_std,
	.vidioc_s_std = dt3155_s_std,
	.vidioc_क्रमागत_input = dt3155_क्रमागत_input,
	.vidioc_g_input = dt3155_g_input,
	.vidioc_s_input = dt3155_s_input,
पूर्ण;

अटल पूर्णांक dt3155_init_board(काष्ठा dt3155_priv *pd)
अणु
	काष्ठा pci_dev *pdev = pd->pdev;
	पूर्णांक i;
	u8 पंचांगp = 0;

	pci_set_master(pdev); /* dt3155 needs it */

	/*  resetting the adapter  */
	ioग_लिखो32(ADDR_ERR_ODD | ADDR_ERR_EVEN | FLD_CRPT_ODD | FLD_CRPT_EVEN |
			FLD_DN_ODD | FLD_DN_EVEN, pd->regs + CSR1);
	msleep(20);

	/*  initializing adapter रेजिस्टरs  */
	ioग_लिखो32(FIFO_EN | SRST, pd->regs + CSR1);
	ioग_लिखो32(0xEEEEEE01, pd->regs + EVEN_PIXEL_FMT);
	ioग_लिखो32(0xEEEEEE01, pd->regs + ODD_PIXEL_FMT);
	ioग_लिखो32(0x00000020, pd->regs + FIFO_TRIGGER);
	ioग_लिखो32(0x00000103, pd->regs + XFER_MODE);
	ioग_लिखो32(0, pd->regs + RETRY_WAIT_CNT);
	ioग_लिखो32(0, pd->regs + INT_CSR);
	ioग_लिखो32(1, pd->regs + EVEN_FLD_MASK);
	ioग_लिखो32(1, pd->regs + ODD_FLD_MASK);
	ioग_लिखो32(0, pd->regs + MASK_LENGTH);
	ioग_लिखो32(0x0005007C, pd->regs + FIFO_FLAG_CNT);
	ioग_लिखो32(0x01010101, pd->regs + IIC_CLK_DUR);

	/* verअगरying that we have a DT3155 board (not just a SAA7116 chip) */
	पढ़ो_i2c_reg(pd->regs, DT_ID, &पंचांगp);
	अगर (पंचांगp != DT3155_ID)
		वापस -ENODEV;

	/* initialize AD LUT */
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, 0);
	क्रम (i = 0; i < 256; i++)
		ग_लिखो_i2c_reg(pd->regs, AD_LUT, i);

	/* initialize ADC references */
	/* FIXME: pos_ref & neg_ref depend on VT_50HZ */
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	ग_लिखो_i2c_reg(pd->regs, AD_CMD, VIDEO_CNL_1 | SYNC_CNL_1 | SYNC_LVL_3);
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, AD_POS_REF);
	ग_लिखो_i2c_reg(pd->regs, AD_CMD, 34);
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, AD_NEG_REF);
	ग_लिखो_i2c_reg(pd->regs, AD_CMD, 0);

	/* initialize PM LUT */
	ग_लिखो_i2c_reg(pd->regs, CONFIG, pd->config | PM_LUT_PGM);
	क्रम (i = 0; i < 256; i++) अणु
		ग_लिखो_i2c_reg(pd->regs, PM_LUT_ADDR, i);
		ग_लिखो_i2c_reg(pd->regs, PM_LUT_DATA, i);
	पूर्ण
	ग_लिखो_i2c_reg(pd->regs, CONFIG, pd->config | PM_LUT_PGM | PM_LUT_SEL);
	क्रम (i = 0; i < 256; i++) अणु
		ग_लिखो_i2c_reg(pd->regs, PM_LUT_ADDR, i);
		ग_लिखो_i2c_reg(pd->regs, PM_LUT_DATA, i);
	पूर्ण
	ग_लिखो_i2c_reg(pd->regs, CONFIG, pd->config); /*  ACQ_MODE_EVEN  */

	/* select channel 1 क्रम input and set sync level */
	ग_लिखो_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	ग_लिखो_i2c_reg(pd->regs, AD_CMD, VIDEO_CNL_1 | SYNC_CNL_1 | SYNC_LVL_3);

	/* disable all irqs, clear all irq flags */
	ioग_लिखो32(FLD_START | FLD_END_EVEN | FLD_END_ODD,
			pd->regs + INT_CSR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा video_device dt3155_vdev = अणु
	.name = DT3155_NAME,
	.fops = &dt3155_fops,
	.ioctl_ops = &dt3155_ioctl_ops,
	.minor = -1,
	.release = video_device_release_empty,
	.tvnorms = V4L2_STD_ALL,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
		       V4L2_CAP_READWRITE,
पूर्ण;

अटल पूर्णांक dt3155_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा dt3155_priv *pd;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस -ENODEV;
	pd = devm_kzalloc(&pdev->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	err = v4l2_device_रेजिस्टर(&pdev->dev, &pd->v4l2_dev);
	अगर (err)
		वापस err;
	pd->vdev = dt3155_vdev;
	pd->vdev.v4l2_dev = &pd->v4l2_dev;
	video_set_drvdata(&pd->vdev, pd);  /* क्रम use in video_fops */
	pd->pdev = pdev;
	pd->std = V4L2_STD_625_50;
	pd->csr2 = VT_50HZ;
	pd->width = 768;
	pd->height = 576;
	INIT_LIST_HEAD(&pd->dmaq);
	mutex_init(&pd->mux);
	pd->vdev.lock = &pd->mux; /* क्रम locking v4l2_file_operations */
	pd->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	pd->vidq.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	pd->vidq.io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	pd->vidq.ops = &q_ops;
	pd->vidq.mem_ops = &vb2_dma_contig_memops;
	pd->vidq.drv_priv = pd;
	pd->vidq.min_buffers_needed = 2;
	pd->vidq.gfp_flags = GFP_DMA32;
	pd->vidq.lock = &pd->mux; /* क्रम locking v4l2_file_operations */
	pd->vidq.dev = &pdev->dev;
	pd->vdev.queue = &pd->vidq;
	err = vb2_queue_init(&pd->vidq);
	अगर (err < 0)
		जाओ err_v4l2_dev_unreg;
	spin_lock_init(&pd->lock);
	pd->config = ACQ_MODE_EVEN;
	err = pci_enable_device(pdev);
	अगर (err)
		जाओ err_v4l2_dev_unreg;
	err = pci_request_region(pdev, 0, pci_name(pdev));
	अगर (err)
		जाओ err_pci_disable;
	pd->regs = pci_iomap(pdev, 0, pci_resource_len(pd->pdev, 0));
	अगर (!pd->regs) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण
	err = dt3155_init_board(pd);
	अगर (err)
		जाओ err_iounmap;
	err = request_irq(pd->pdev->irq, dt3155_irq_handler_even,
					IRQF_SHARED, DT3155_NAME, pd);
	अगर (err)
		जाओ err_iounmap;
	err = video_रेजिस्टर_device(&pd->vdev, VFL_TYPE_VIDEO, -1);
	अगर (err)
		जाओ err_मुक्त_irq;
	dev_info(&pdev->dev, "/dev/video%i is ready\n", pd->vdev.minor);
	वापस 0;  /*   success   */

err_मुक्त_irq:
	मुक्त_irq(pd->pdev->irq, pd);
err_iounmap:
	pci_iounmap(pdev, pd->regs);
err_मुक्त_reg:
	pci_release_region(pdev, 0);
err_pci_disable:
	pci_disable_device(pdev);
err_v4l2_dev_unreg:
	v4l2_device_unरेजिस्टर(&pd->v4l2_dev);
	वापस err;
पूर्ण

अटल व्योम dt3155_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा dt3155_priv *pd = container_of(v4l2_dev, काष्ठा dt3155_priv,
					      v4l2_dev);

	vb2_video_unरेजिस्टर_device(&pd->vdev);
	मुक्त_irq(pd->pdev->irq, pd);
	v4l2_device_unरेजिस्टर(&pd->v4l2_dev);
	pci_iounmap(pdev, pd->regs);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, DT3155_DEVICE_ID) पूर्ण,
	अणु 0, /* zero marks the end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

अटल काष्ठा pci_driver pci_driver = अणु
	.name = DT3155_NAME,
	.id_table = pci_ids,
	.probe = dt3155_probe,
	.हटाओ = dt3155_हटाओ,
पूर्ण;

module_pci_driver(pci_driver);

MODULE_DESCRIPTION("video4linux pci-driver for dt3155 frame grabber");
MODULE_AUTHOR("Marin Mitov <mitov@issp.bas.bg>");
MODULE_VERSION(DT3155_VERSION);
MODULE_LICENSE("GPL");
