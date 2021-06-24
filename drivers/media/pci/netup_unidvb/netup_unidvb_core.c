<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netup_unidvb_core.c
 *
 * Main module क्रम NetUP Universal Dual DVB-CI
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश "netup_unidvb.h"
#समावेश "cxd2841er.h"
#समावेश "horus3a.h"
#समावेश "ascot2e.h"
#समावेश "helene.h"
#समावेश "lnbh25.h"

अटल पूर्णांक spi_enable;
module_param(spi_enable, पूर्णांक, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

MODULE_DESCRIPTION("Driver for NetUP Dual Universal DVB CI PCIe card");
MODULE_AUTHOR("info@netup.ru");
MODULE_VERSION(NETUP_UNIDVB_VERSION);
MODULE_LICENSE("GPL");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* Avalon-MM PCI-E रेजिस्टरs */
#घोषणा	AVL_PCIE_IENR		0x50
#घोषणा AVL_PCIE_ISR		0x40
#घोषणा AVL_IRQ_ENABLE		0x80
#घोषणा AVL_IRQ_ASSERTED	0x80
/* GPIO रेजिस्टरs */
#घोषणा GPIO_REG_IO		0x4880
#घोषणा GPIO_REG_IO_TOGGLE	0x4882
#घोषणा GPIO_REG_IO_SET		0x4884
#घोषणा GPIO_REG_IO_CLEAR	0x4886
/* GPIO bits */
#घोषणा GPIO_FEA_RESET		(1 << 0)
#घोषणा GPIO_FEB_RESET		(1 << 1)
#घोषणा GPIO_RFA_CTL		(1 << 2)
#घोषणा GPIO_RFB_CTL		(1 << 3)
#घोषणा GPIO_FEA_TU_RESET	(1 << 4)
#घोषणा GPIO_FEB_TU_RESET	(1 << 5)
/* DMA base address */
#घोषणा NETUP_DMA0_ADDR		0x4900
#घोषणा NETUP_DMA1_ADDR		0x4940
/* 8 DMA blocks * 128 packets * 188 bytes*/
#घोषणा NETUP_DMA_BLOCKS_COUNT	8
#घोषणा NETUP_DMA_PACKETS_COUNT	128
/* DMA status bits */
#घोषणा BIT_DMA_RUN		1
#घोषणा BIT_DMA_ERROR		2
#घोषणा BIT_DMA_IRQ		0x200

/**
 * काष्ठा netup_dma_regs - the map of DMA module रेजिस्टरs
 * @ctrlstat_set:	Control रेजिस्टर, ग_लिखो to set control bits
 * @ctrlstat_clear:	Control रेजिस्टर, ग_लिखो to clear control bits
 * @start_addr_lo:	DMA ring buffer start address, lower part
 * @start_addr_hi:	DMA ring buffer start address, higher part
 * @size:		DMA ring buffer size रेजिस्टर
 *			* Bits [0-7]:	DMA packet size, 188 bytes
 *			* Bits [16-23]:	packets count in block, 128 packets
 *			* Bits [24-31]:	blocks count, 8 blocks
 * @समयout:		DMA समयout in units of 8ns
 *			For example, value of 375000000 equals to 3 sec
 * @curr_addr_lo:	Current ring buffer head address, lower part
 * @curr_addr_hi:	Current ring buffer head address, higher part
 * @stat_pkt_received:	Statistic रेजिस्टर, not tested
 * @stat_pkt_accepted:	Statistic रेजिस्टर, not tested
 * @stat_pkt_overruns:	Statistic रेजिस्टर, not tested
 * @stat_pkt_underruns:	Statistic रेजिस्टर, not tested
 * @stat_fअगरo_overruns:	Statistic रेजिस्टर, not tested
 */
काष्ठा netup_dma_regs अणु
	__le32	ctrlstat_set;
	__le32	ctrlstat_clear;
	__le32	start_addr_lo;
	__le32	start_addr_hi;
	__le32	size;
	__le32	समयout;
	__le32	curr_addr_lo;
	__le32	curr_addr_hi;
	__le32	stat_pkt_received;
	__le32	stat_pkt_accepted;
	__le32	stat_pkt_overruns;
	__le32	stat_pkt_underruns;
	__le32	stat_fअगरo_overruns;
पूर्ण __packed __aligned(1);

काष्ठा netup_unidvb_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head	list;
	u32			size;
पूर्ण;

अटल पूर्णांक netup_unidvb_tuner_ctrl(व्योम *priv, पूर्णांक is_dvb_tc);
अटल व्योम netup_unidvb_queue_cleanup(काष्ठा netup_dma *dma);

अटल काष्ठा cxd2841er_config demod_config = अणु
	.i2c_addr = 0xc8,
	.xtal = SONY_XTAL_24000,
	.flags = CXD2841ER_USE_GATECTRL | CXD2841ER_ASCOT
पूर्ण;

अटल काष्ठा horus3a_config horus3a_conf = अणु
	.i2c_address = 0xc0,
	.xtal_freq_mhz = 16,
	.set_tuner_callback = netup_unidvb_tuner_ctrl
पूर्ण;

अटल काष्ठा ascot2e_config ascot2e_conf = अणु
	.i2c_address = 0xc2,
	.set_tuner_callback = netup_unidvb_tuner_ctrl
पूर्ण;

अटल काष्ठा helene_config helene_conf = अणु
	.i2c_address = 0xc0,
	.xtal = SONY_HELENE_XTAL_24000,
	.set_tuner_callback = netup_unidvb_tuner_ctrl
पूर्ण;

अटल काष्ठा lnbh25_config lnbh25_conf = अणु
	.i2c_address = 0x10,
	.data2_config = LNBH25_TEN | LNBH25_EXTM
पूर्ण;

अटल पूर्णांक netup_unidvb_tuner_ctrl(व्योम *priv, पूर्णांक is_dvb_tc)
अणु
	u8 reg, mask;
	काष्ठा netup_dma *dma = priv;
	काष्ठा netup_unidvb_dev *ndev;

	अगर (!priv)
		वापस -EINVAL;
	ndev = dma->ndev;
	dev_dbg(&ndev->pci_dev->dev, "%s(): num %d is_dvb_tc %d\n",
		__func__, dma->num, is_dvb_tc);
	reg = पढ़ोb(ndev->bmmio0 + GPIO_REG_IO);
	mask = (dma->num == 0) ? GPIO_RFA_CTL : GPIO_RFB_CTL;

	/* inverted tuner control in hw rev. 1.4 */
	अगर (ndev->rev == NETUP_HW_REV_1_4)
		is_dvb_tc = !is_dvb_tc;

	अगर (!is_dvb_tc)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	ग_लिखोb(reg, ndev->bmmio0 + GPIO_REG_IO);
	वापस 0;
पूर्ण

अटल व्योम netup_unidvb_dev_enable(काष्ठा netup_unidvb_dev *ndev)
अणु
	u16 gpio_reg;

	/* enable PCI-E पूर्णांकerrupts */
	ग_लिखोl(AVL_IRQ_ENABLE, ndev->bmmio0 + AVL_PCIE_IENR);
	/* unreset frontends bits[0:1] */
	ग_लिखोb(0x00, ndev->bmmio0 + GPIO_REG_IO);
	msleep(100);
	gpio_reg =
		GPIO_FEA_RESET | GPIO_FEB_RESET |
		GPIO_FEA_TU_RESET | GPIO_FEB_TU_RESET |
		GPIO_RFA_CTL | GPIO_RFB_CTL;
	ग_लिखोb(gpio_reg, ndev->bmmio0 + GPIO_REG_IO);
	dev_dbg(&ndev->pci_dev->dev,
		"%s(): AVL_PCIE_IENR 0x%x GPIO_REG_IO 0x%x\n",
		__func__, पढ़ोl(ndev->bmmio0 + AVL_PCIE_IENR),
		(पूर्णांक)पढ़ोb(ndev->bmmio0 + GPIO_REG_IO));

पूर्ण

अटल व्योम netup_unidvb_dma_enable(काष्ठा netup_dma *dma, पूर्णांक enable)
अणु
	u32 irq_mask = (dma->num == 0 ?
		NETUP_UNIDVB_IRQ_DMA1 : NETUP_UNIDVB_IRQ_DMA2);

	dev_dbg(&dma->ndev->pci_dev->dev,
		"%s(): DMA%d enable %d\n", __func__, dma->num, enable);
	अगर (enable) अणु
		ग_लिखोl(BIT_DMA_RUN, &dma->regs->ctrlstat_set);
		ग_लिखोw(irq_mask, dma->ndev->bmmio0 + REG_IMASK_SET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(BIT_DMA_RUN, &dma->regs->ctrlstat_clear);
		ग_लिखोw(irq_mask, dma->ndev->bmmio0 + REG_IMASK_CLEAR);
	पूर्ण
पूर्ण

अटल irqवापस_t netup_dma_पूर्णांकerrupt(काष्ठा netup_dma *dma)
अणु
	u64 addr_curr;
	u32 size;
	अचिन्हित दीर्घ flags;
	काष्ठा device *dev = &dma->ndev->pci_dev->dev;

	spin_lock_irqsave(&dma->lock, flags);
	addr_curr = ((u64)पढ़ोl(&dma->regs->curr_addr_hi) << 32) |
		(u64)पढ़ोl(&dma->regs->curr_addr_lo) | dma->high_addr;
	/* clear IRQ */
	ग_लिखोl(BIT_DMA_IRQ, &dma->regs->ctrlstat_clear);
	/* sanity check */
	अगर (addr_curr < dma->addr_phys ||
			addr_curr > dma->addr_phys +  dma->ring_buffer_size) अणु
		अगर (addr_curr != 0) अणु
			dev_err(dev,
				"%s(): addr 0x%llx not from 0x%llx:0x%llx\n",
				__func__, addr_curr, (u64)dma->addr_phys,
				(u64)(dma->addr_phys + dma->ring_buffer_size));
		पूर्ण
		जाओ irq_handled;
	पूर्ण
	size = (addr_curr >= dma->addr_last) ?
		(u32)(addr_curr - dma->addr_last) :
		(u32)(dma->ring_buffer_size - (dma->addr_last - addr_curr));
	अगर (dma->data_size != 0) अणु
		prपूर्णांकk_ratelimited("%s(): lost interrupt, data size %d\n",
			__func__, dma->data_size);
		dma->data_size += size;
	पूर्ण
	अगर (dma->data_size == 0 || dma->data_size > dma->ring_buffer_size) अणु
		dma->data_size = size;
		dma->data_offset = (u32)(dma->addr_last - dma->addr_phys);
	पूर्ण
	dma->addr_last = addr_curr;
	queue_work(dma->ndev->wq, &dma->work);
irq_handled:
	spin_unlock_irqrestore(&dma->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t netup_unidvb_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_dev *pci_dev = (काष्ठा pci_dev *)dev_id;
	काष्ठा netup_unidvb_dev *ndev = pci_get_drvdata(pci_dev);
	u32 reg40, reg_isr;
	irqवापस_t iret = IRQ_NONE;

	/* disable पूर्णांकerrupts */
	ग_लिखोl(0, ndev->bmmio0 + AVL_PCIE_IENR);
	/* check IRQ source */
	reg40 = पढ़ोl(ndev->bmmio0 + AVL_PCIE_ISR);
	अगर ((reg40 & AVL_IRQ_ASSERTED) != 0) अणु
		/* IRQ is being संकेतed */
		reg_isr = पढ़ोw(ndev->bmmio0 + REG_ISR);
		अगर (reg_isr & NETUP_UNIDVB_IRQ_I2C0) अणु
			iret = netup_i2c_पूर्णांकerrupt(&ndev->i2c[0]);
		पूर्ण अन्यथा अगर (reg_isr & NETUP_UNIDVB_IRQ_I2C1) अणु
			iret = netup_i2c_पूर्णांकerrupt(&ndev->i2c[1]);
		पूर्ण अन्यथा अगर (reg_isr & NETUP_UNIDVB_IRQ_SPI) अणु
			iret = netup_spi_पूर्णांकerrupt(ndev->spi);
		पूर्ण अन्यथा अगर (reg_isr & NETUP_UNIDVB_IRQ_DMA1) अणु
			iret = netup_dma_पूर्णांकerrupt(&ndev->dma[0]);
		पूर्ण अन्यथा अगर (reg_isr & NETUP_UNIDVB_IRQ_DMA2) अणु
			iret = netup_dma_पूर्णांकerrupt(&ndev->dma[1]);
		पूर्ण अन्यथा अगर (reg_isr & NETUP_UNIDVB_IRQ_CI) अणु
			iret = netup_ci_पूर्णांकerrupt(ndev);
		पूर्ण अन्यथा अणु
			dev_err(&pci_dev->dev,
				"%s(): unknown interrupt 0x%x\n",
				__func__, reg_isr);
		पूर्ण
	पूर्ण
	/* re-enable पूर्णांकerrupts */
	ग_लिखोl(AVL_IRQ_ENABLE, ndev->bmmio0 + AVL_PCIE_IENR);
	वापस iret;
पूर्ण

अटल पूर्णांक netup_unidvb_queue_setup(काष्ठा vb2_queue *vq,
				    अचिन्हित पूर्णांक *nbuffers,
				    अचिन्हित पूर्णांक *nplanes,
				    अचिन्हित पूर्णांक sizes[],
				    काष्ठा device *alloc_devs[])
अणु
	काष्ठा netup_dma *dma = vb2_get_drv_priv(vq);

	dev_dbg(&dma->ndev->pci_dev->dev, "%s()\n", __func__);

	*nplanes = 1;
	अगर (vq->num_buffers + *nbuffers < VIDEO_MAX_FRAME)
		*nbuffers = VIDEO_MAX_FRAME - vq->num_buffers;
	sizes[0] = PAGE_ALIGN(NETUP_DMA_PACKETS_COUNT * 188);
	dev_dbg(&dma->ndev->pci_dev->dev, "%s() nbuffers=%d sizes[0]=%d\n",
		__func__, *nbuffers, sizes[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा netup_dma *dma = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा netup_unidvb_buffer *buf = container_of(vbuf,
				काष्ठा netup_unidvb_buffer, vb);

	dev_dbg(&dma->ndev->pci_dev->dev, "%s(): buf 0x%p\n", __func__, buf);
	buf->size = 0;
	वापस 0;
पूर्ण

अटल व्योम netup_unidvb_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा netup_dma *dma = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा netup_unidvb_buffer *buf = container_of(vbuf,
				काष्ठा netup_unidvb_buffer, vb);

	dev_dbg(&dma->ndev->pci_dev->dev, "%s(): %p\n", __func__, buf);
	spin_lock_irqsave(&dma->lock, flags);
	list_add_tail(&buf->list, &dma->मुक्त_buffers);
	spin_unlock_irqrestore(&dma->lock, flags);
	mod_समयr(&dma->समयout, jअगरfies + msecs_to_jअगरfies(1000));
पूर्ण

अटल पूर्णांक netup_unidvb_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा netup_dma *dma = vb2_get_drv_priv(q);

	dev_dbg(&dma->ndev->pci_dev->dev, "%s()\n", __func__);
	netup_unidvb_dma_enable(dma, 1);
	वापस 0;
पूर्ण

अटल व्योम netup_unidvb_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा netup_dma *dma = vb2_get_drv_priv(q);

	dev_dbg(&dma->ndev->pci_dev->dev, "%s()\n", __func__);
	netup_unidvb_dma_enable(dma, 0);
	netup_unidvb_queue_cleanup(dma);
पूर्ण

अटल स्थिर काष्ठा vb2_ops dvb_qops = अणु
	.queue_setup		= netup_unidvb_queue_setup,
	.buf_prepare		= netup_unidvb_buf_prepare,
	.buf_queue		= netup_unidvb_buf_queue,
	.start_streaming	= netup_unidvb_start_streaming,
	.stop_streaming		= netup_unidvb_stop_streaming,
पूर्ण;

अटल पूर्णांक netup_unidvb_queue_init(काष्ठा netup_dma *dma,
				   काष्ठा vb2_queue *vb_queue)
अणु
	पूर्णांक res;

	/* Init videobuf2 queue काष्ठाure */
	vb_queue->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vb_queue->io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	vb_queue->drv_priv = dma;
	vb_queue->buf_काष्ठा_size = माप(काष्ठा netup_unidvb_buffer);
	vb_queue->ops = &dvb_qops;
	vb_queue->mem_ops = &vb2_vदो_स्मृति_memops;
	vb_queue->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	res = vb2_queue_init(vb_queue);
	अगर (res != 0) अणु
		dev_err(&dma->ndev->pci_dev->dev,
			"%s(): vb2_queue_init failed (%d)\n", __func__, res);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक netup_unidvb_dvb_init(काष्ठा netup_unidvb_dev *ndev,
				 पूर्णांक num)
अणु
	पूर्णांक fe_count = 2;
	पूर्णांक i = 0;
	काष्ठा vb2_dvb_frontend *fes[2];
	u8 fe_name[32];

	अगर (ndev->rev == NETUP_HW_REV_1_3)
		demod_config.xtal = SONY_XTAL_20500;
	अन्यथा
		demod_config.xtal = SONY_XTAL_24000;

	अगर (num < 0 || num > 1) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): unable to init DVB bus %d\n", __func__, num);
		वापस -ENODEV;
	पूर्ण
	mutex_init(&ndev->frontends[num].lock);
	INIT_LIST_HEAD(&ndev->frontends[num].felist);

	क्रम (i = 0; i < fe_count; i++) अणु
		अगर (vb2_dvb_alloc_frontend(&ndev->frontends[num], i+1)
				== शून्य) अणु
			dev_err(&ndev->pci_dev->dev,
					"%s(): unable to allocate vb2_dvb_frontend\n",
					__func__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fe_count; i++) अणु
		fes[i] = vb2_dvb_get_frontend(&ndev->frontends[num], i+1);
		अगर (fes[i] == शून्य) अणु
			dev_err(&ndev->pci_dev->dev,
				"%s(): frontends has not been allocated\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fe_count; i++) अणु
		netup_unidvb_queue_init(&ndev->dma[num], &fes[i]->dvb.dvbq);
		snम_लिखो(fe_name, माप(fe_name), "netup_fe%d", i);
		fes[i]->dvb.name = fe_name;
	पूर्ण

	fes[0]->dvb.frontend = dvb_attach(cxd2841er_attach_s,
		&demod_config, &ndev->i2c[num].adap);
	अगर (fes[0]->dvb.frontend == शून्य) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): unable to attach DVB-S/S2 frontend\n",
			__func__);
		जाओ frontend_detach;
	पूर्ण

	अगर (ndev->rev == NETUP_HW_REV_1_3) अणु
		horus3a_conf.set_tuner_priv = &ndev->dma[num];
		अगर (!dvb_attach(horus3a_attach, fes[0]->dvb.frontend,
					&horus3a_conf, &ndev->i2c[num].adap)) अणु
			dev_dbg(&ndev->pci_dev->dev,
					"%s(): unable to attach HORUS3A DVB-S/S2 tuner frontend\n",
					__func__);
			जाओ frontend_detach;
		पूर्ण
	पूर्ण अन्यथा अणु
		helene_conf.set_tuner_priv = &ndev->dma[num];
		अगर (!dvb_attach(helene_attach_s, fes[0]->dvb.frontend,
					&helene_conf, &ndev->i2c[num].adap)) अणु
			dev_err(&ndev->pci_dev->dev,
					"%s(): unable to attach HELENE DVB-S/S2 tuner frontend\n",
					__func__);
			जाओ frontend_detach;
		पूर्ण
	पूर्ण

	अगर (!dvb_attach(lnbh25_attach, fes[0]->dvb.frontend,
			&lnbh25_conf, &ndev->i2c[num].adap)) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): unable to attach SEC frontend\n", __func__);
		जाओ frontend_detach;
	पूर्ण

	/* DVB-T/T2 frontend */
	fes[1]->dvb.frontend = dvb_attach(cxd2841er_attach_t_c,
		&demod_config, &ndev->i2c[num].adap);
	अगर (fes[1]->dvb.frontend == शून्य) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): unable to attach Ter frontend\n", __func__);
		जाओ frontend_detach;
	पूर्ण
	fes[1]->dvb.frontend->id = 1;
	अगर (ndev->rev == NETUP_HW_REV_1_3) अणु
		ascot2e_conf.set_tuner_priv = &ndev->dma[num];
		अगर (!dvb_attach(ascot2e_attach, fes[1]->dvb.frontend,
					&ascot2e_conf, &ndev->i2c[num].adap)) अणु
			dev_dbg(&ndev->pci_dev->dev,
					"%s(): unable to attach Ter tuner frontend\n",
					__func__);
			जाओ frontend_detach;
		पूर्ण
	पूर्ण अन्यथा अणु
		helene_conf.set_tuner_priv = &ndev->dma[num];
		अगर (!dvb_attach(helene_attach, fes[1]->dvb.frontend,
					&helene_conf, &ndev->i2c[num].adap)) अणु
			dev_err(&ndev->pci_dev->dev,
					"%s(): unable to attach HELENE Ter tuner frontend\n",
					__func__);
			जाओ frontend_detach;
		पूर्ण
	पूर्ण

	अगर (vb2_dvb_रेजिस्टर_bus(&ndev->frontends[num],
				 THIS_MODULE, शून्य,
				 &ndev->pci_dev->dev, शून्य, adapter_nr, 1)) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): unable to register DVB bus %d\n",
			__func__, num);
		जाओ frontend_detach;
	पूर्ण
	dev_info(&ndev->pci_dev->dev, "DVB init done, num=%d\n", num);
	वापस 0;
frontend_detach:
	vb2_dvb_dealloc_frontends(&ndev->frontends[num]);
	वापस -EINVAL;
पूर्ण

अटल व्योम netup_unidvb_dvb_fini(काष्ठा netup_unidvb_dev *ndev, पूर्णांक num)
अणु
	अगर (num < 0 || num > 1) अणु
		dev_err(&ndev->pci_dev->dev,
			"%s(): unable to unregister DVB bus %d\n",
			__func__, num);
		वापस;
	पूर्ण
	vb2_dvb_unरेजिस्टर_bus(&ndev->frontends[num]);
	dev_info(&ndev->pci_dev->dev,
		"%s(): DVB bus %d unregistered\n", __func__, num);
पूर्ण

अटल पूर्णांक netup_unidvb_dvb_setup(काष्ठा netup_unidvb_dev *ndev)
अणु
	पूर्णांक res;

	res = netup_unidvb_dvb_init(ndev, 0);
	अगर (res)
		वापस res;
	res = netup_unidvb_dvb_init(ndev, 1);
	अगर (res) अणु
		netup_unidvb_dvb_fini(ndev, 0);
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_ring_copy(काष्ठा netup_dma *dma,
				  काष्ठा netup_unidvb_buffer *buf)
अणु
	u32 copy_bytes, ring_bytes;
	u32 buff_bytes = NETUP_DMA_PACKETS_COUNT * 188 - buf->size;
	u8 *p = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	काष्ठा netup_unidvb_dev *ndev = dma->ndev;

	अगर (p == शून्य) अणु
		dev_err(&ndev->pci_dev->dev,
			"%s(): buffer is NULL\n", __func__);
		वापस -EINVAL;
	पूर्ण
	p += buf->size;
	अगर (dma->data_offset + dma->data_size > dma->ring_buffer_size) अणु
		ring_bytes = dma->ring_buffer_size - dma->data_offset;
		copy_bytes = (ring_bytes > buff_bytes) ?
			buff_bytes : ring_bytes;
		स_नकल_fromio(p, (u8 __iomem *)(dma->addr_virt + dma->data_offset), copy_bytes);
		p += copy_bytes;
		buf->size += copy_bytes;
		buff_bytes -= copy_bytes;
		dma->data_size -= copy_bytes;
		dma->data_offset += copy_bytes;
		अगर (dma->data_offset == dma->ring_buffer_size)
			dma->data_offset = 0;
	पूर्ण
	अगर (buff_bytes > 0) अणु
		ring_bytes = dma->data_size;
		copy_bytes = (ring_bytes > buff_bytes) ?
				buff_bytes : ring_bytes;
		स_नकल_fromio(p, (u8 __iomem *)(dma->addr_virt + dma->data_offset), copy_bytes);
		buf->size += copy_bytes;
		dma->data_size -= copy_bytes;
		dma->data_offset += copy_bytes;
		अगर (dma->data_offset == dma->ring_buffer_size)
			dma->data_offset = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम netup_unidvb_dma_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netup_dma *dma = container_of(work, काष्ठा netup_dma, work);
	काष्ठा netup_unidvb_dev *ndev = dma->ndev;
	काष्ठा netup_unidvb_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dma->lock, flags);
	अगर (dma->data_size == 0) अणु
		dev_dbg(&ndev->pci_dev->dev,
			"%s(): data_size == 0\n", __func__);
		जाओ work_करोne;
	पूर्ण
	जबतक (dma->data_size > 0) अणु
		अगर (list_empty(&dma->मुक्त_buffers)) अणु
			dev_dbg(&ndev->pci_dev->dev,
				"%s(): no free buffers\n", __func__);
			जाओ work_करोne;
		पूर्ण
		buf = list_first_entry(&dma->मुक्त_buffers,
			काष्ठा netup_unidvb_buffer, list);
		अगर (buf->size >= NETUP_DMA_PACKETS_COUNT * 188) अणु
			dev_dbg(&ndev->pci_dev->dev,
				"%s(): buffer overflow, size %d\n",
				__func__, buf->size);
			जाओ work_करोne;
		पूर्ण
		अगर (netup_unidvb_ring_copy(dma, buf))
			जाओ work_करोne;
		अगर (buf->size == NETUP_DMA_PACKETS_COUNT * 188) अणु
			list_del(&buf->list);
			dev_dbg(&ndev->pci_dev->dev,
				"%s(): buffer %p done, size %d\n",
				__func__, buf, buf->size);
			buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0, buf->size);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		पूर्ण
	पूर्ण
work_करोne:
	dma->data_size = 0;
	spin_unlock_irqrestore(&dma->lock, flags);
पूर्ण

अटल व्योम netup_unidvb_queue_cleanup(काष्ठा netup_dma *dma)
अणु
	काष्ठा netup_unidvb_buffer *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dma->lock, flags);
	जबतक (!list_empty(&dma->मुक्त_buffers)) अणु
		buf = list_first_entry(&dma->मुक्त_buffers,
			काष्ठा netup_unidvb_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dma->lock, flags);
पूर्ण

अटल व्योम netup_unidvb_dma_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा netup_dma *dma = from_समयr(dma, t, समयout);
	काष्ठा netup_unidvb_dev *ndev = dma->ndev;

	dev_dbg(&ndev->pci_dev->dev, "%s()\n", __func__);
	netup_unidvb_queue_cleanup(dma);
पूर्ण

अटल पूर्णांक netup_unidvb_dma_init(काष्ठा netup_unidvb_dev *ndev, पूर्णांक num)
अणु
	काष्ठा netup_dma *dma;
	काष्ठा device *dev = &ndev->pci_dev->dev;

	अगर (num < 0 || num > 1) अणु
		dev_err(dev, "%s(): unable to register DMA%d\n",
			__func__, num);
		वापस -ENODEV;
	पूर्ण
	dma = &ndev->dma[num];
	dev_info(dev, "%s(): starting DMA%d\n", __func__, num);
	dma->num = num;
	dma->ndev = ndev;
	spin_lock_init(&dma->lock);
	INIT_WORK(&dma->work, netup_unidvb_dma_worker);
	INIT_LIST_HEAD(&dma->मुक्त_buffers);
	समयr_setup(&dma->समयout, netup_unidvb_dma_समयout, 0);
	dma->ring_buffer_size = ndev->dma_size / 2;
	dma->addr_virt = ndev->dma_virt + dma->ring_buffer_size * num;
	dma->addr_phys = (dma_addr_t)((u64)ndev->dma_phys +
		dma->ring_buffer_size * num);
	dev_info(dev, "%s(): DMA%d buffer virt/phys 0x%p/0x%llx size %d\n",
		__func__, num, dma->addr_virt,
		(अचिन्हित दीर्घ दीर्घ)dma->addr_phys,
		dma->ring_buffer_size);
	स_रखो_io((u8 __iomem *)dma->addr_virt, 0, dma->ring_buffer_size);
	dma->addr_last = dma->addr_phys;
	dma->high_addr = (u32)(dma->addr_phys & 0xC0000000);
	dma->regs = (काष्ठा netup_dma_regs __iomem *)(num == 0 ?
		ndev->bmmio0 + NETUP_DMA0_ADDR :
		ndev->bmmio0 + NETUP_DMA1_ADDR);
	ग_लिखोl((NETUP_DMA_BLOCKS_COUNT << 24) |
		(NETUP_DMA_PACKETS_COUNT << 8) | 188, &dma->regs->size);
	ग_लिखोl((u32)(dma->addr_phys & 0x3FFFFFFF), &dma->regs->start_addr_lo);
	ग_लिखोl(0, &dma->regs->start_addr_hi);
	ग_लिखोl(dma->high_addr, ndev->bmmio0 + 0x1000);
	ग_लिखोl(375000000, &dma->regs->समयout);
	msleep(1000);
	ग_लिखोl(BIT_DMA_IRQ, &dma->regs->ctrlstat_clear);
	वापस 0;
पूर्ण

अटल व्योम netup_unidvb_dma_fini(काष्ठा netup_unidvb_dev *ndev, पूर्णांक num)
अणु
	काष्ठा netup_dma *dma;

	अगर (num < 0 || num > 1)
		वापस;
	dev_dbg(&ndev->pci_dev->dev, "%s(): num %d\n", __func__, num);
	dma = &ndev->dma[num];
	netup_unidvb_dma_enable(dma, 0);
	msleep(50);
	cancel_work_sync(&dma->work);
	del_समयr(&dma->समयout);
पूर्ण

अटल पूर्णांक netup_unidvb_dma_setup(काष्ठा netup_unidvb_dev *ndev)
अणु
	पूर्णांक res;

	res = netup_unidvb_dma_init(ndev, 0);
	अगर (res)
		वापस res;
	res = netup_unidvb_dma_init(ndev, 1);
	अगर (res) अणु
		netup_unidvb_dma_fini(ndev, 0);
		वापस res;
	पूर्ण
	netup_unidvb_dma_enable(&ndev->dma[0], 0);
	netup_unidvb_dma_enable(&ndev->dma[1], 0);
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_ci_setup(काष्ठा netup_unidvb_dev *ndev,
				 काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक res;

	ग_लिखोw(NETUP_UNIDVB_IRQ_CI, ndev->bmmio0 + REG_IMASK_SET);
	res = netup_unidvb_ci_रेजिस्टर(ndev, 0, pci_dev);
	अगर (res)
		वापस res;
	res = netup_unidvb_ci_रेजिस्टर(ndev, 1, pci_dev);
	अगर (res)
		netup_unidvb_ci_unरेजिस्टर(ndev, 0);
	वापस res;
पूर्ण

अटल पूर्णांक netup_unidvb_request_mmio(काष्ठा pci_dev *pci_dev)
अणु
	अगर (!request_mem_region(pci_resource_start(pci_dev, 0),
			pci_resource_len(pci_dev, 0), NETUP_UNIDVB_NAME)) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to request MMIO bar 0 at 0x%llx\n",
			__func__,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));
		वापस -EBUSY;
	पूर्ण
	अगर (!request_mem_region(pci_resource_start(pci_dev, 1),
			pci_resource_len(pci_dev, 1), NETUP_UNIDVB_NAME)) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to request MMIO bar 1 at 0x%llx\n",
			__func__,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 1));
		release_mem_region(pci_resource_start(pci_dev, 0),
			pci_resource_len(pci_dev, 0));
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_request_modules(काष्ठा device *dev)
अणु
	अटल स्थिर अक्षर * स्थिर modules[] = अणु
		"lnbh25", "ascot2e", "horus3a", "cxd2841er", "helene", शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर *curr_mod = modules;
	पूर्णांक err;

	जबतक (*curr_mod != शून्य) अणु
		err = request_module(*curr_mod);
		अगर (err) अणु
			dev_warn(dev, "request_module(%s) failed: %d\n",
				*curr_mod, err);
		पूर्ण
		++curr_mod;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netup_unidvb_initdev(काष्ठा pci_dev *pci_dev,
				स्थिर काष्ठा pci_device_id *pci_id)
अणु
	u8 board_revision;
	u16 board_venकरोr;
	काष्ठा netup_unidvb_dev *ndev;
	पूर्णांक old_firmware = 0;

	netup_unidvb_request_modules(&pci_dev->dev);

	/* Check card revision */
	अगर (pci_dev->revision != NETUP_PCI_DEV_REVISION) अणु
		dev_err(&pci_dev->dev,
			"netup_unidvb: expected card revision %d, got %d\n",
			NETUP_PCI_DEV_REVISION, pci_dev->revision);
		dev_err(&pci_dev->dev,
			"Please upgrade firmware!\n");
		dev_err(&pci_dev->dev,
			"Instructions on http://www.netup.tv\n");
		old_firmware = 1;
		spi_enable = 1;
	पूर्ण

	/* allocate device context */
	ndev = kzalloc(माप(*ndev), GFP_KERNEL);
	अगर (!ndev)
		जाओ dev_alloc_err;

	/* detect hardware revision */
	अगर (pci_dev->device == NETUP_HW_REV_1_3)
		ndev->rev = NETUP_HW_REV_1_3;
	अन्यथा
		ndev->rev = NETUP_HW_REV_1_4;

	dev_info(&pci_dev->dev,
		"%s(): board (0x%x) hardware revision 0x%x\n",
		__func__, pci_dev->device, ndev->rev);

	ndev->old_fw = old_firmware;
	ndev->wq = create_singlethपढ़ो_workqueue(NETUP_UNIDVB_NAME);
	अगर (!ndev->wq) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to create workqueue\n", __func__);
		जाओ wq_create_err;
	पूर्ण
	ndev->pci_dev = pci_dev;
	ndev->pci_bus = pci_dev->bus->number;
	ndev->pci_slot = PCI_SLOT(pci_dev->devfn);
	ndev->pci_func = PCI_FUNC(pci_dev->devfn);
	ndev->board_num = ndev->pci_bus*10 + ndev->pci_slot;
	pci_set_drvdata(pci_dev, ndev);
	/* PCI init */
	dev_info(&pci_dev->dev, "%s(): PCI device (%d). Bus:0x%x Slot:0x%x\n",
		__func__, ndev->board_num, ndev->pci_bus, ndev->pci_slot);

	अगर (pci_enable_device(pci_dev)) अणु
		dev_err(&pci_dev->dev, "%s(): pci_enable_device failed\n",
			__func__);
		जाओ pci_enable_err;
	पूर्ण
	/* पढ़ो PCI info */
	pci_पढ़ो_config_byte(pci_dev, PCI_CLASS_REVISION, &board_revision);
	pci_पढ़ो_config_word(pci_dev, PCI_VENDOR_ID, &board_venकरोr);
	अगर (board_venकरोr != NETUP_VENDOR_ID) अणु
		dev_err(&pci_dev->dev, "%s(): unknown board vendor 0x%x",
			__func__, board_venकरोr);
		जाओ pci_detect_err;
	पूर्ण
	dev_info(&pci_dev->dev,
		"%s(): board vendor 0x%x, revision 0x%x\n",
		__func__, board_venकरोr, board_revision);
	pci_set_master(pci_dev);
	अगर (pci_set_dma_mask(pci_dev, 0xffffffff) < 0) अणु
		dev_err(&pci_dev->dev,
			"%s(): 32bit PCI DMA is not supported\n", __func__);
		जाओ pci_detect_err;
	पूर्ण
	dev_info(&pci_dev->dev, "%s(): using 32bit PCI DMA\n", __func__);
	/* Clear "no snoop" and "relaxed ordering" bits, use शेष MRRS. */
	pcie_capability_clear_and_set_word(pci_dev, PCI_EXP_DEVCTL,
		PCI_EXP_DEVCTL_READRQ | PCI_EXP_DEVCTL_RELAX_EN |
		PCI_EXP_DEVCTL_NOSNOOP_EN, 0);
	/* Adjust PCIe completion समयout. */
	pcie_capability_clear_and_set_word(pci_dev,
		PCI_EXP_DEVCTL2, PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0x2);

	अगर (netup_unidvb_request_mmio(pci_dev)) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to request MMIO regions\n", __func__);
		जाओ pci_detect_err;
	पूर्ण
	ndev->lmmio0 = ioremap(pci_resource_start(pci_dev, 0),
		pci_resource_len(pci_dev, 0));
	अगर (!ndev->lmmio0) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to remap MMIO bar 0\n", __func__);
		जाओ pci_bar0_error;
	पूर्ण
	ndev->lmmio1 = ioremap(pci_resource_start(pci_dev, 1),
		pci_resource_len(pci_dev, 1));
	अगर (!ndev->lmmio1) अणु
		dev_err(&pci_dev->dev,
			"%s(): unable to remap MMIO bar 1\n", __func__);
		जाओ pci_bar1_error;
	पूर्ण
	ndev->bmmio0 = (u8 __iomem *)ndev->lmmio0;
	ndev->bmmio1 = (u8 __iomem *)ndev->lmmio1;
	dev_info(&pci_dev->dev,
		"%s(): PCI MMIO at 0x%p (%d); 0x%p (%d); IRQ %d",
		__func__,
		ndev->lmmio0, (u32)pci_resource_len(pci_dev, 0),
		ndev->lmmio1, (u32)pci_resource_len(pci_dev, 1),
		pci_dev->irq);
	अगर (request_irq(pci_dev->irq, netup_unidvb_isr, IRQF_SHARED,
			"netup_unidvb", pci_dev) < 0) अणु
		dev_err(&pci_dev->dev,
			"%s(): can't get IRQ %d\n", __func__, pci_dev->irq);
		जाओ irq_request_err;
	पूर्ण
	ndev->dma_size = 2 * 188 *
		NETUP_DMA_BLOCKS_COUNT * NETUP_DMA_PACKETS_COUNT;
	ndev->dma_virt = dma_alloc_coherent(&pci_dev->dev,
		ndev->dma_size, &ndev->dma_phys, GFP_KERNEL);
	अगर (!ndev->dma_virt) अणु
		dev_err(&pci_dev->dev, "%s(): unable to allocate DMA buffer\n",
			__func__);
		जाओ dma_alloc_err;
	पूर्ण
	netup_unidvb_dev_enable(ndev);
	अगर (spi_enable && netup_spi_init(ndev)) अणु
		dev_warn(&pci_dev->dev,
			"netup_unidvb: SPI flash setup failed\n");
		जाओ spi_setup_err;
	पूर्ण
	अगर (old_firmware) अणु
		dev_err(&pci_dev->dev,
			"netup_unidvb: card initialization was incomplete\n");
		वापस 0;
	पूर्ण
	अगर (netup_i2c_रेजिस्टर(ndev)) अणु
		dev_err(&pci_dev->dev, "netup_unidvb: I2C setup failed\n");
		जाओ i2c_setup_err;
	पूर्ण
	/* enable I2C IRQs */
	ग_लिखोw(NETUP_UNIDVB_IRQ_I2C0 | NETUP_UNIDVB_IRQ_I2C1,
		ndev->bmmio0 + REG_IMASK_SET);
	usleep_range(5000, 10000);
	अगर (netup_unidvb_dvb_setup(ndev)) अणु
		dev_err(&pci_dev->dev, "netup_unidvb: DVB setup failed\n");
		जाओ dvb_setup_err;
	पूर्ण
	अगर (netup_unidvb_ci_setup(ndev, pci_dev)) अणु
		dev_err(&pci_dev->dev, "netup_unidvb: CI setup failed\n");
		जाओ ci_setup_err;
	पूर्ण
	अगर (netup_unidvb_dma_setup(ndev)) अणु
		dev_err(&pci_dev->dev, "netup_unidvb: DMA setup failed\n");
		जाओ dma_setup_err;
	पूर्ण
	dev_info(&pci_dev->dev,
		"netup_unidvb: device has been initialized\n");
	वापस 0;
dma_setup_err:
	netup_unidvb_ci_unरेजिस्टर(ndev, 0);
	netup_unidvb_ci_unरेजिस्टर(ndev, 1);
ci_setup_err:
	netup_unidvb_dvb_fini(ndev, 0);
	netup_unidvb_dvb_fini(ndev, 1);
dvb_setup_err:
	netup_i2c_unरेजिस्टर(ndev);
i2c_setup_err:
	अगर (ndev->spi)
		netup_spi_release(ndev);
spi_setup_err:
	dma_मुक्त_coherent(&pci_dev->dev, ndev->dma_size,
			ndev->dma_virt, ndev->dma_phys);
dma_alloc_err:
	मुक्त_irq(pci_dev->irq, pci_dev);
irq_request_err:
	iounmap(ndev->lmmio1);
pci_bar1_error:
	iounmap(ndev->lmmio0);
pci_bar0_error:
	release_mem_region(pci_resource_start(pci_dev, 0),
		pci_resource_len(pci_dev, 0));
	release_mem_region(pci_resource_start(pci_dev, 1),
		pci_resource_len(pci_dev, 1));
pci_detect_err:
	pci_disable_device(pci_dev);
pci_enable_err:
	pci_set_drvdata(pci_dev, शून्य);
	destroy_workqueue(ndev->wq);
wq_create_err:
	kमुक्त(ndev);
dev_alloc_err:
	dev_err(&pci_dev->dev,
		"%s(): failed to initialize device\n", __func__);
	वापस -EIO;
पूर्ण

अटल व्योम netup_unidvb_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा netup_unidvb_dev *ndev = pci_get_drvdata(pci_dev);

	dev_info(&pci_dev->dev, "%s(): trying to stop device\n", __func__);
	अगर (!ndev->old_fw) अणु
		netup_unidvb_dma_fini(ndev, 0);
		netup_unidvb_dma_fini(ndev, 1);
		netup_unidvb_ci_unरेजिस्टर(ndev, 0);
		netup_unidvb_ci_unरेजिस्टर(ndev, 1);
		netup_unidvb_dvb_fini(ndev, 0);
		netup_unidvb_dvb_fini(ndev, 1);
		netup_i2c_unरेजिस्टर(ndev);
	पूर्ण
	अगर (ndev->spi)
		netup_spi_release(ndev);
	ग_लिखोw(0xffff, ndev->bmmio0 + REG_IMASK_CLEAR);
	dma_मुक्त_coherent(&ndev->pci_dev->dev, ndev->dma_size,
			ndev->dma_virt, ndev->dma_phys);
	मुक्त_irq(pci_dev->irq, pci_dev);
	iounmap(ndev->lmmio0);
	iounmap(ndev->lmmio1);
	release_mem_region(pci_resource_start(pci_dev, 0),
		pci_resource_len(pci_dev, 0));
	release_mem_region(pci_resource_start(pci_dev, 1),
		pci_resource_len(pci_dev, 1));
	pci_disable_device(pci_dev);
	pci_set_drvdata(pci_dev, शून्य);
	destroy_workqueue(ndev->wq);
	kमुक्त(ndev);
	dev_info(&pci_dev->dev,
		"%s(): device has been successfully stopped\n", __func__);
पूर्ण


अटल स्थिर काष्ठा pci_device_id netup_unidvb_pci_tbl[] = अणु
	अणु PCI_DEVICE(0x1b55, 0x18f6) पूर्ण, /* hw rev. 1.3 */
	अणु PCI_DEVICE(0x1b55, 0x18f7) पूर्ण, /* hw rev. 1.4 */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, netup_unidvb_pci_tbl);

अटल काष्ठा pci_driver netup_unidvb_pci_driver = अणु
	.name     = "netup_unidvb",
	.id_table = netup_unidvb_pci_tbl,
	.probe    = netup_unidvb_initdev,
	.हटाओ   = netup_unidvb_finidev,
पूर्ण;

module_pci_driver(netup_unidvb_pci_driver);
