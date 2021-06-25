<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright(c) 2019 HiSilicon Limited. */
#समावेश <linux/bitfield.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश "virt-dma.h"

#घोषणा HISI_DMA_SQ_BASE_L		0x0
#घोषणा HISI_DMA_SQ_BASE_H		0x4
#घोषणा HISI_DMA_SQ_DEPTH		0x8
#घोषणा HISI_DMA_SQ_TAIL_PTR		0xc
#घोषणा HISI_DMA_CQ_BASE_L		0x10
#घोषणा HISI_DMA_CQ_BASE_H		0x14
#घोषणा HISI_DMA_CQ_DEPTH		0x18
#घोषणा HISI_DMA_CQ_HEAD_PTR		0x1c
#घोषणा HISI_DMA_CTRL0			0x20
#घोषणा HISI_DMA_CTRL0_QUEUE_EN_S	0
#घोषणा HISI_DMA_CTRL0_QUEUE_PAUSE_S	4
#घोषणा HISI_DMA_CTRL1			0x24
#घोषणा HISI_DMA_CTRL1_QUEUE_RESET_S	0
#घोषणा HISI_DMA_Q_FSM_STS		0x30
#घोषणा HISI_DMA_FSM_STS_MASK		GENMASK(3, 0)
#घोषणा HISI_DMA_INT_STS		0x40
#घोषणा HISI_DMA_INT_STS_MASK		GENMASK(12, 0)
#घोषणा HISI_DMA_INT_MSK		0x44
#घोषणा HISI_DMA_MODE			0x217c
#घोषणा HISI_DMA_OFFSET			0x100

#घोषणा HISI_DMA_MSI_NUM		30
#घोषणा HISI_DMA_CHAN_NUM		30
#घोषणा HISI_DMA_Q_DEPTH_VAL		1024

#घोषणा PCI_BAR_2			2

क्रमागत hisi_dma_mode अणु
	EP = 0,
	RC,
पूर्ण;

क्रमागत hisi_dma_chan_status अणु
	DISABLE = -1,
	IDLE = 0,
	RUN,
	CPL,
	PAUSE,
	HALT,
	ABORT,
	WAIT,
	BUFFCLR,
पूर्ण;

काष्ठा hisi_dma_sqe अणु
	__le32 dw0;
#घोषणा OPCODE_MASK			GENMASK(3, 0)
#घोषणा OPCODE_SMALL_PACKAGE		0x1
#घोषणा OPCODE_M2M			0x4
#घोषणा LOCAL_IRQ_EN			BIT(8)
#घोषणा ATTR_SRC_MASK			GENMASK(14, 12)
	__le32 dw1;
	__le32 dw2;
#घोषणा ATTR_DST_MASK			GENMASK(26, 24)
	__le32 length;
	__le64 src_addr;
	__le64 dst_addr;
पूर्ण;

काष्ठा hisi_dma_cqe अणु
	__le32 rsv0;
	__le32 rsv1;
	__le16 sq_head;
	__le16 rsv2;
	__le16 rsv3;
	__le16 w0;
#घोषणा STATUS_MASK			GENMASK(15, 1)
#घोषणा STATUS_SUCC			0x0
#घोषणा VALID_BIT			BIT(0)
पूर्ण;

काष्ठा hisi_dma_desc अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा hisi_dma_sqe sqe;
पूर्ण;

काष्ठा hisi_dma_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा hisi_dma_dev *hdma_dev;
	काष्ठा hisi_dma_sqe *sq;
	काष्ठा hisi_dma_cqe *cq;
	dma_addr_t sq_dma;
	dma_addr_t cq_dma;
	u32 sq_tail;
	u32 cq_head;
	u32 qp_num;
	क्रमागत hisi_dma_chan_status status;
	काष्ठा hisi_dma_desc *desc;
पूर्ण;

काष्ठा hisi_dma_dev अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *base;
	काष्ठा dma_device dma_dev;
	u32 chan_num;
	u32 chan_depth;
	काष्ठा hisi_dma_chan chan[];
पूर्ण;

अटल अंतरभूत काष्ठा hisi_dma_chan *to_hisi_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा hisi_dma_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा hisi_dma_desc *to_hisi_dma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा hisi_dma_desc, vd);
पूर्ण

अटल अंतरभूत व्योम hisi_dma_chan_ग_लिखो(व्योम __iomem *base, u32 reg, u32 index,
				       u32 val)
अणु
	ग_लिखोl_relaxed(val, base + reg + index * HISI_DMA_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hisi_dma_update_bit(व्योम __iomem *addr, u32 pos, bool val)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(addr);
	पंचांगp = val ? पंचांगp | BIT(pos) : पंचांगp & ~BIT(pos);
	ग_लिखोl_relaxed(पंचांगp, addr);
पूर्ण

अटल व्योम hisi_dma_मुक्त_irq_vectors(व्योम *data)
अणु
	pci_मुक्त_irq_vectors(data);
पूर्ण

अटल व्योम hisi_dma_छोड़ो_dma(काष्ठा hisi_dma_dev *hdma_dev, u32 index,
			       bool छोड़ो)
अणु
	व्योम __iomem *addr = hdma_dev->base + HISI_DMA_CTRL0 + index *
			     HISI_DMA_OFFSET;

	hisi_dma_update_bit(addr, HISI_DMA_CTRL0_QUEUE_PAUSE_S, छोड़ो);
पूर्ण

अटल व्योम hisi_dma_enable_dma(काष्ठा hisi_dma_dev *hdma_dev, u32 index,
				bool enable)
अणु
	व्योम __iomem *addr = hdma_dev->base + HISI_DMA_CTRL0 + index *
			     HISI_DMA_OFFSET;

	hisi_dma_update_bit(addr, HISI_DMA_CTRL0_QUEUE_EN_S, enable);
पूर्ण

अटल व्योम hisi_dma_mask_irq(काष्ठा hisi_dma_dev *hdma_dev, u32 qp_index)
अणु
	hisi_dma_chan_ग_लिखो(hdma_dev->base, HISI_DMA_INT_MSK, qp_index,
			    HISI_DMA_INT_STS_MASK);
पूर्ण

अटल व्योम hisi_dma_unmask_irq(काष्ठा hisi_dma_dev *hdma_dev, u32 qp_index)
अणु
	व्योम __iomem *base = hdma_dev->base;

	hisi_dma_chan_ग_लिखो(base, HISI_DMA_INT_STS, qp_index,
			    HISI_DMA_INT_STS_MASK);
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_INT_MSK, qp_index, 0);
पूर्ण

अटल व्योम hisi_dma_करो_reset(काष्ठा hisi_dma_dev *hdma_dev, u32 index)
अणु
	व्योम __iomem *addr = hdma_dev->base + HISI_DMA_CTRL1 + index *
			     HISI_DMA_OFFSET;

	hisi_dma_update_bit(addr, HISI_DMA_CTRL1_QUEUE_RESET_S, 1);
पूर्ण

अटल व्योम hisi_dma_reset_qp_poपूर्णांक(काष्ठा hisi_dma_dev *hdma_dev, u32 index)
अणु
	hisi_dma_chan_ग_लिखो(hdma_dev->base, HISI_DMA_SQ_TAIL_PTR, index, 0);
	hisi_dma_chan_ग_लिखो(hdma_dev->base, HISI_DMA_CQ_HEAD_PTR, index, 0);
पूर्ण

अटल व्योम hisi_dma_reset_hw_chan(काष्ठा hisi_dma_chan *chan)
अणु
	काष्ठा hisi_dma_dev *hdma_dev = chan->hdma_dev;
	u32 index = chan->qp_num, पंचांगp;
	पूर्णांक ret;

	hisi_dma_छोड़ो_dma(hdma_dev, index, true);
	hisi_dma_enable_dma(hdma_dev, index, false);
	hisi_dma_mask_irq(hdma_dev, index);

	ret = पढ़ोl_relaxed_poll_समयout(hdma_dev->base +
		HISI_DMA_Q_FSM_STS + index * HISI_DMA_OFFSET, पंचांगp,
		FIELD_GET(HISI_DMA_FSM_STS_MASK, पंचांगp) != RUN, 10, 1000);
	अगर (ret) अणु
		dev_err(&hdma_dev->pdev->dev, "disable channel timeout!\n");
		WARN_ON(1);
	पूर्ण

	hisi_dma_करो_reset(hdma_dev, index);
	hisi_dma_reset_qp_poपूर्णांक(hdma_dev, index);
	hisi_dma_छोड़ो_dma(hdma_dev, index, false);
	hisi_dma_enable_dma(hdma_dev, index, true);
	hisi_dma_unmask_irq(hdma_dev, index);

	ret = पढ़ोl_relaxed_poll_समयout(hdma_dev->base +
		HISI_DMA_Q_FSM_STS + index * HISI_DMA_OFFSET, पंचांगp,
		FIELD_GET(HISI_DMA_FSM_STS_MASK, पंचांगp) == IDLE, 10, 1000);
	अगर (ret) अणु
		dev_err(&hdma_dev->pdev->dev, "reset channel timeout!\n");
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम hisi_dma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा hisi_dma_chan *chan = to_hisi_dma_chan(c);
	काष्ठा hisi_dma_dev *hdma_dev = chan->hdma_dev;

	hisi_dma_reset_hw_chan(chan);
	vchan_मुक्त_chan_resources(&chan->vc);

	स_रखो(chan->sq, 0, माप(काष्ठा hisi_dma_sqe) * hdma_dev->chan_depth);
	स_रखो(chan->cq, 0, माप(काष्ठा hisi_dma_cqe) * hdma_dev->chan_depth);
	chan->sq_tail = 0;
	chan->cq_head = 0;
	chan->status = DISABLE;
पूर्ण

अटल व्योम hisi_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(to_hisi_dma_desc(vd));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
hisi_dma_prep_dma_स_नकल(काष्ठा dma_chan *c, dma_addr_t dst, dma_addr_t src,
			 माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hisi_dma_chan *chan = to_hisi_dma_chan(c);
	काष्ठा hisi_dma_desc *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->sqe.length = cpu_to_le32(len);
	desc->sqe.src_addr = cpu_to_le64(src);
	desc->sqe.dst_addr = cpu_to_le64(dst);

	वापस vchan_tx_prep(&chan->vc, &desc->vd, flags);
पूर्ण

अटल क्रमागत dma_status
hisi_dma_tx_status(काष्ठा dma_chan *c, dma_cookie_t cookie,
		   काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(c, cookie, txstate);
पूर्ण

अटल व्योम hisi_dma_start_transfer(काष्ठा hisi_dma_chan *chan)
अणु
	काष्ठा hisi_dma_sqe *sqe = chan->sq + chan->sq_tail;
	काष्ठा hisi_dma_dev *hdma_dev = chan->hdma_dev;
	काष्ठा hisi_dma_desc *desc;
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	अगर (!vd) अणु
		dev_err(&hdma_dev->pdev->dev, "no issued task!\n");
		chan->desc = शून्य;
		वापस;
	पूर्ण
	list_del(&vd->node);
	desc = to_hisi_dma_desc(vd);
	chan->desc = desc;

	स_नकल(sqe, &desc->sqe, माप(काष्ठा hisi_dma_sqe));

	/* update other field in sqe */
	sqe->dw0 = cpu_to_le32(FIELD_PREP(OPCODE_MASK, OPCODE_M2M));
	sqe->dw0 |= cpu_to_le32(LOCAL_IRQ_EN);

	/* make sure data has been updated in sqe */
	wmb();

	/* update sq tail, poपूर्णांक to new sqe position */
	chan->sq_tail = (chan->sq_tail + 1) % hdma_dev->chan_depth;

	/* update sq_tail to trigger a new task */
	hisi_dma_chan_ग_लिखो(hdma_dev->base, HISI_DMA_SQ_TAIL_PTR, chan->qp_num,
			    chan->sq_tail);
पूर्ण

अटल व्योम hisi_dma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा hisi_dma_chan *chan = to_hisi_dma_chan(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);

	अगर (vchan_issue_pending(&chan->vc))
		hisi_dma_start_transfer(chan);

	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल पूर्णांक hisi_dma_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा hisi_dma_chan *chan = to_hisi_dma_chan(c);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vc.lock, flags);

	hisi_dma_छोड़ो_dma(chan->hdma_dev, chan->qp_num, true);
	अगर (chan->desc) अणु
		vchan_terminate_vdesc(&chan->desc->vd);
		chan->desc = शून्य;
	पूर्ण

	vchan_get_all_descriptors(&chan->vc, &head);

	spin_unlock_irqrestore(&chan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vc, &head);
	hisi_dma_छोड़ो_dma(chan->hdma_dev, chan->qp_num, false);

	वापस 0;
पूर्ण

अटल व्योम hisi_dma_synchronize(काष्ठा dma_chan *c)
अणु
	काष्ठा hisi_dma_chan *chan = to_hisi_dma_chan(c);

	vchan_synchronize(&chan->vc);
पूर्ण

अटल पूर्णांक hisi_dma_alloc_qps_mem(काष्ठा hisi_dma_dev *hdma_dev)
अणु
	माप_प्रकार sq_size = माप(काष्ठा hisi_dma_sqe) * hdma_dev->chan_depth;
	माप_प्रकार cq_size = माप(काष्ठा hisi_dma_cqe) * hdma_dev->chan_depth;
	काष्ठा device *dev = &hdma_dev->pdev->dev;
	काष्ठा hisi_dma_chan *chan;
	पूर्णांक i;

	क्रम (i = 0; i < hdma_dev->chan_num; i++) अणु
		chan = &hdma_dev->chan[i];
		chan->sq = dmam_alloc_coherent(dev, sq_size, &chan->sq_dma,
					       GFP_KERNEL);
		अगर (!chan->sq)
			वापस -ENOMEM;

		chan->cq = dmam_alloc_coherent(dev, cq_size, &chan->cq_dma,
					       GFP_KERNEL);
		अगर (!chan->cq)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hisi_dma_init_hw_qp(काष्ठा hisi_dma_dev *hdma_dev, u32 index)
अणु
	काष्ठा hisi_dma_chan *chan = &hdma_dev->chan[index];
	u32 hw_depth = hdma_dev->chan_depth - 1;
	व्योम __iomem *base = hdma_dev->base;

	/* set sq, cq base */
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_SQ_BASE_L, index,
			    lower_32_bits(chan->sq_dma));
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_SQ_BASE_H, index,
			    upper_32_bits(chan->sq_dma));
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_CQ_BASE_L, index,
			    lower_32_bits(chan->cq_dma));
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_CQ_BASE_H, index,
			    upper_32_bits(chan->cq_dma));

	/* set sq, cq depth */
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_SQ_DEPTH, index, hw_depth);
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_CQ_DEPTH, index, hw_depth);

	/* init sq tail and cq head */
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_SQ_TAIL_PTR, index, 0);
	hisi_dma_chan_ग_लिखो(base, HISI_DMA_CQ_HEAD_PTR, index, 0);
पूर्ण

अटल व्योम hisi_dma_enable_qp(काष्ठा hisi_dma_dev *hdma_dev, u32 qp_index)
अणु
	hisi_dma_init_hw_qp(hdma_dev, qp_index);
	hisi_dma_unmask_irq(hdma_dev, qp_index);
	hisi_dma_enable_dma(hdma_dev, qp_index, true);
पूर्ण

अटल व्योम hisi_dma_disable_qp(काष्ठा hisi_dma_dev *hdma_dev, u32 qp_index)
अणु
	hisi_dma_reset_hw_chan(&hdma_dev->chan[qp_index]);
पूर्ण

अटल व्योम hisi_dma_enable_qps(काष्ठा hisi_dma_dev *hdma_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdma_dev->chan_num; i++) अणु
		hdma_dev->chan[i].qp_num = i;
		hdma_dev->chan[i].hdma_dev = hdma_dev;
		hdma_dev->chan[i].vc.desc_मुक्त = hisi_dma_desc_मुक्त;
		vchan_init(&hdma_dev->chan[i].vc, &hdma_dev->dma_dev);
		hisi_dma_enable_qp(hdma_dev, i);
	पूर्ण
पूर्ण

अटल व्योम hisi_dma_disable_qps(काष्ठा hisi_dma_dev *hdma_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdma_dev->chan_num; i++) अणु
		hisi_dma_disable_qp(hdma_dev, i);
		tasklet_समाप्त(&hdma_dev->chan[i].vc.task);
	पूर्ण
पूर्ण

अटल irqवापस_t hisi_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hisi_dma_chan *chan = data;
	काष्ठा hisi_dma_dev *hdma_dev = chan->hdma_dev;
	काष्ठा hisi_dma_desc *desc;
	काष्ठा hisi_dma_cqe *cqe;

	spin_lock(&chan->vc.lock);

	desc = chan->desc;
	cqe = chan->cq + chan->cq_head;
	अगर (desc) अणु
		अगर (FIELD_GET(STATUS_MASK, cqe->w0) == STATUS_SUCC) अणु
			chan->cq_head = (chan->cq_head + 1) %
					hdma_dev->chan_depth;
			hisi_dma_chan_ग_लिखो(hdma_dev->base,
					    HISI_DMA_CQ_HEAD_PTR, chan->qp_num,
					    chan->cq_head);
			vchan_cookie_complete(&desc->vd);
		पूर्ण अन्यथा अणु
			dev_err(&hdma_dev->pdev->dev, "task error!\n");
		पूर्ण

		chan->desc = शून्य;
	पूर्ण

	spin_unlock(&chan->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_dma_request_qps_irq(काष्ठा hisi_dma_dev *hdma_dev)
अणु
	काष्ठा pci_dev *pdev = hdma_dev->pdev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < hdma_dev->chan_num; i++) अणु
		ret = devm_request_irq(&pdev->dev, pci_irq_vector(pdev, i),
				       hisi_dma_irq, IRQF_SHARED, "hisi_dma",
				       &hdma_dev->chan[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* This function enables all hw channels in a device */
अटल पूर्णांक hisi_dma_enable_hw_channels(काष्ठा hisi_dma_dev *hdma_dev)
अणु
	पूर्णांक ret;

	ret = hisi_dma_alloc_qps_mem(hdma_dev);
	अगर (ret) अणु
		dev_err(&hdma_dev->pdev->dev, "fail to allocate qp memory!\n");
		वापस ret;
	पूर्ण

	ret = hisi_dma_request_qps_irq(hdma_dev);
	अगर (ret) अणु
		dev_err(&hdma_dev->pdev->dev, "fail to request qp irq!\n");
		वापस ret;
	पूर्ण

	hisi_dma_enable_qps(hdma_dev);

	वापस 0;
पूर्ण

अटल व्योम hisi_dma_disable_hw_channels(व्योम *data)
अणु
	hisi_dma_disable_qps(data);
पूर्ण

अटल व्योम hisi_dma_set_mode(काष्ठा hisi_dma_dev *hdma_dev,
			      क्रमागत hisi_dma_mode mode)
अणु
	ग_लिखोl_relaxed(mode == RC ? 1 : 0, hdma_dev->base + HISI_DMA_MODE);
पूर्ण

अटल पूर्णांक hisi_dma_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hisi_dma_dev *hdma_dev;
	काष्ठा dma_device *dma_dev;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "failed to enable device mem!\n");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, 1 << PCI_BAR_2, pci_name(pdev));
	अगर (ret) अणु
		dev_err(dev, "failed to remap I/O region!\n");
		वापस ret;
	पूर्ण

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret)
		वापस ret;

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret)
		वापस ret;

	hdma_dev = devm_kzalloc(dev, काष्ठा_size(hdma_dev, chan, HISI_DMA_CHAN_NUM), GFP_KERNEL);
	अगर (!hdma_dev)
		वापस -EINVAL;

	hdma_dev->base = pcim_iomap_table(pdev)[PCI_BAR_2];
	hdma_dev->pdev = pdev;
	hdma_dev->chan_num = HISI_DMA_CHAN_NUM;
	hdma_dev->chan_depth = HISI_DMA_Q_DEPTH_VAL;

	pci_set_drvdata(pdev, hdma_dev);
	pci_set_master(pdev);

	ret = pci_alloc_irq_vectors(pdev, HISI_DMA_MSI_NUM, HISI_DMA_MSI_NUM,
				    PCI_IRQ_MSI);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to allocate MSI vectors!\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, hisi_dma_मुक्त_irq_vectors, pdev);
	अगर (ret)
		वापस ret;

	dma_dev = &hdma_dev->dma_dev;
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_dev->device_मुक्त_chan_resources = hisi_dma_मुक्त_chan_resources;
	dma_dev->device_prep_dma_स_नकल = hisi_dma_prep_dma_स_नकल;
	dma_dev->device_tx_status = hisi_dma_tx_status;
	dma_dev->device_issue_pending = hisi_dma_issue_pending;
	dma_dev->device_terminate_all = hisi_dma_terminate_all;
	dma_dev->device_synchronize = hisi_dma_synchronize;
	dma_dev->directions = BIT(DMA_MEM_TO_MEM);
	dma_dev->dev = dev;
	INIT_LIST_HEAD(&dma_dev->channels);

	hisi_dma_set_mode(hdma_dev, RC);

	ret = hisi_dma_enable_hw_channels(hdma_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable hw channel!\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, hisi_dma_disable_hw_channels,
				       hdma_dev);
	अगर (ret)
		वापस ret;

	ret = dmaenginem_async_device_रेजिस्टर(dma_dev);
	अगर (ret < 0)
		dev_err(dev, "failed to register device!\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id hisi_dma_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUAWEI, 0xa122) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver hisi_dma_pci_driver = अणु
	.name		= "hisi_dma",
	.id_table	= hisi_dma_pci_tbl,
	.probe		= hisi_dma_probe,
पूर्ण;

module_pci_driver(hisi_dma_pci_driver);

MODULE_AUTHOR("Zhou Wang <wangzhou1@hisilicon.com>");
MODULE_AUTHOR("Zhenfa Qiu <qiuzhenfa@hisilicon.com>");
MODULE_DESCRIPTION("HiSilicon Kunpeng DMA controller driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, hisi_dma_pci_tbl);
