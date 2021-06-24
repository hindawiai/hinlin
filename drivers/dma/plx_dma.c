<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microsemi Switchtec(पंचांग) PCIe Management Driver
 * Copyright (c) 2019, Logan Gunthorpe <logang@deltatee.com>
 * Copyright (c) 2019, GigaIO Networks, Inc
 */

#समावेश "dmaengine.h"

#समावेश <linux/circ_buf.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

MODULE_DESCRIPTION("PLX ExpressLane PEX PCI Switch DMA Engine");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Logan Gunthorpe");

#घोषणा PLX_REG_DESC_RING_ADDR			0x214
#घोषणा PLX_REG_DESC_RING_ADDR_HI		0x218
#घोषणा PLX_REG_DESC_RING_NEXT_ADDR		0x21C
#घोषणा PLX_REG_DESC_RING_COUNT			0x220
#घोषणा PLX_REG_DESC_RING_LAST_ADDR		0x224
#घोषणा PLX_REG_DESC_RING_LAST_SIZE		0x228
#घोषणा PLX_REG_PREF_LIMIT			0x234
#घोषणा PLX_REG_CTRL				0x238
#घोषणा PLX_REG_CTRL2				0x23A
#घोषणा PLX_REG_INTR_CTRL			0x23C
#घोषणा PLX_REG_INTR_STATUS			0x23E

#घोषणा PLX_REG_PREF_LIMIT_PREF_FOUR		8

#घोषणा PLX_REG_CTRL_GRACEFUL_PAUSE		BIT(0)
#घोषणा PLX_REG_CTRL_ABORT			BIT(1)
#घोषणा PLX_REG_CTRL_WRITE_BACK_EN		BIT(2)
#घोषणा PLX_REG_CTRL_START			BIT(3)
#घोषणा PLX_REG_CTRL_RING_STOP_MODE		BIT(4)
#घोषणा PLX_REG_CTRL_DESC_MODE_BLOCK		(0 << 5)
#घोषणा PLX_REG_CTRL_DESC_MODE_ON_CHIP		(1 << 5)
#घोषणा PLX_REG_CTRL_DESC_MODE_OFF_CHIP		(2 << 5)
#घोषणा PLX_REG_CTRL_DESC_INVALID		BIT(8)
#घोषणा PLX_REG_CTRL_GRACEFUL_PAUSE_DONE	BIT(9)
#घोषणा PLX_REG_CTRL_ABORT_DONE			BIT(10)
#घोषणा PLX_REG_CTRL_IMM_PAUSE_DONE		BIT(12)
#घोषणा PLX_REG_CTRL_IN_PROGRESS		BIT(30)

#घोषणा PLX_REG_CTRL_RESET_VAL	(PLX_REG_CTRL_DESC_INVALID | \
				 PLX_REG_CTRL_GRACEFUL_PAUSE_DONE | \
				 PLX_REG_CTRL_ABORT_DONE | \
				 PLX_REG_CTRL_IMM_PAUSE_DONE)

#घोषणा PLX_REG_CTRL_START_VAL	(PLX_REG_CTRL_WRITE_BACK_EN | \
				 PLX_REG_CTRL_DESC_MODE_OFF_CHIP | \
				 PLX_REG_CTRL_START | \
				 PLX_REG_CTRL_RESET_VAL)

#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_64B		0
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_128B	1
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_256B	2
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_512B	3
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_1KB		4
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_2KB		5
#घोषणा PLX_REG_CTRL2_MAX_TXFR_SIZE_4B		7

#घोषणा PLX_REG_INTR_CRTL_ERROR_EN		BIT(0)
#घोषणा PLX_REG_INTR_CRTL_INV_DESC_EN		BIT(1)
#घोषणा PLX_REG_INTR_CRTL_ABORT_DONE_EN		BIT(3)
#घोषणा PLX_REG_INTR_CRTL_PAUSE_DONE_EN		BIT(4)
#घोषणा PLX_REG_INTR_CRTL_IMM_PAUSE_DONE_EN	BIT(5)

#घोषणा PLX_REG_INTR_STATUS_ERROR		BIT(0)
#घोषणा PLX_REG_INTR_STATUS_INV_DESC		BIT(1)
#घोषणा PLX_REG_INTR_STATUS_DESC_DONE		BIT(2)
#घोषणा PLX_REG_INTR_CRTL_ABORT_DONE		BIT(3)

काष्ठा plx_dma_hw_std_desc अणु
	__le32 flags_and_size;
	__le16 dst_addr_hi;
	__le16 src_addr_hi;
	__le32 dst_addr_lo;
	__le32 src_addr_lo;
पूर्ण;

#घोषणा PLX_DESC_SIZE_MASK		0x7ffffff
#घोषणा PLX_DESC_FLAG_VALID		BIT(31)
#घोषणा PLX_DESC_FLAG_INT_WHEN_DONE	BIT(30)

#घोषणा PLX_DESC_WB_SUCCESS		BIT(30)
#घोषणा PLX_DESC_WB_RD_FAIL		BIT(29)
#घोषणा PLX_DESC_WB_WR_FAIL		BIT(28)

#घोषणा PLX_DMA_RING_COUNT		2048

काष्ठा plx_dma_desc अणु
	काष्ठा dma_async_tx_descriptor txd;
	काष्ठा plx_dma_hw_std_desc *hw;
	u32 orig_size;
पूर्ण;

काष्ठा plx_dma_dev अणु
	काष्ठा dma_device dma_dev;
	काष्ठा dma_chan dma_chan;
	काष्ठा pci_dev __rcu *pdev;
	व्योम __iomem *bar;
	काष्ठा tasklet_काष्ठा desc_task;

	spinlock_t ring_lock;
	bool ring_active;
	पूर्णांक head;
	पूर्णांक tail;
	काष्ठा plx_dma_hw_std_desc *hw_ring;
	dma_addr_t hw_ring_dma;
	काष्ठा plx_dma_desc **desc_ring;
पूर्ण;

अटल काष्ठा plx_dma_dev *chan_to_plx_dma_dev(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा plx_dma_dev, dma_chan);
पूर्ण

अटल काष्ठा plx_dma_desc *to_plx_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा plx_dma_desc, txd);
पूर्ण

अटल काष्ठा plx_dma_desc *plx_dma_get_desc(काष्ठा plx_dma_dev *plxdev, पूर्णांक i)
अणु
	वापस plxdev->desc_ring[i & (PLX_DMA_RING_COUNT - 1)];
पूर्ण

अटल व्योम plx_dma_process_desc(काष्ठा plx_dma_dev *plxdev)
अणु
	काष्ठा dmaengine_result res;
	काष्ठा plx_dma_desc *desc;
	u32 flags;

	spin_lock_bh(&plxdev->ring_lock);

	जबतक (plxdev->tail != plxdev->head) अणु
		desc = plx_dma_get_desc(plxdev, plxdev->tail);

		flags = le32_to_cpu(READ_ONCE(desc->hw->flags_and_size));

		अगर (flags & PLX_DESC_FLAG_VALID)
			अवरोध;

		res.residue = desc->orig_size - (flags & PLX_DESC_SIZE_MASK);

		अगर (flags & PLX_DESC_WB_SUCCESS)
			res.result = DMA_TRANS_NOERROR;
		अन्यथा अगर (flags & PLX_DESC_WB_WR_FAIL)
			res.result = DMA_TRANS_WRITE_FAILED;
		अन्यथा
			res.result = DMA_TRANS_READ_FAILED;

		dma_cookie_complete(&desc->txd);
		dma_descriptor_unmap(&desc->txd);
		dmaengine_desc_get_callback_invoke(&desc->txd, &res);
		desc->txd.callback = शून्य;
		desc->txd.callback_result = शून्य;

		plxdev->tail++;
	पूर्ण

	spin_unlock_bh(&plxdev->ring_lock);
पूर्ण

अटल व्योम plx_dma_पात_desc(काष्ठा plx_dma_dev *plxdev)
अणु
	काष्ठा dmaengine_result res;
	काष्ठा plx_dma_desc *desc;

	plx_dma_process_desc(plxdev);

	spin_lock_bh(&plxdev->ring_lock);

	जबतक (plxdev->tail != plxdev->head) अणु
		desc = plx_dma_get_desc(plxdev, plxdev->tail);

		res.residue = desc->orig_size;
		res.result = DMA_TRANS_ABORTED;

		dma_cookie_complete(&desc->txd);
		dma_descriptor_unmap(&desc->txd);
		dmaengine_desc_get_callback_invoke(&desc->txd, &res);
		desc->txd.callback = शून्य;
		desc->txd.callback_result = शून्य;

		plxdev->tail++;
	पूर्ण

	spin_unlock_bh(&plxdev->ring_lock);
पूर्ण

अटल व्योम __plx_dma_stop(काष्ठा plx_dma_dev *plxdev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	u32 val;

	val = पढ़ोl(plxdev->bar + PLX_REG_CTRL);
	अगर (!(val & ~PLX_REG_CTRL_GRACEFUL_PAUSE))
		वापस;

	ग_लिखोl(PLX_REG_CTRL_RESET_VAL | PLX_REG_CTRL_GRACEFUL_PAUSE,
	       plxdev->bar + PLX_REG_CTRL);

	जबतक (!समय_after(jअगरfies, समयout)) अणु
		val = पढ़ोl(plxdev->bar + PLX_REG_CTRL);
		अगर (val & PLX_REG_CTRL_GRACEFUL_PAUSE_DONE)
			अवरोध;

		cpu_relax();
	पूर्ण

	अगर (!(val & PLX_REG_CTRL_GRACEFUL_PAUSE_DONE))
		dev_err(plxdev->dma_dev.dev,
			"Timeout waiting for graceful pause!\n");

	ग_लिखोl(PLX_REG_CTRL_RESET_VAL | PLX_REG_CTRL_GRACEFUL_PAUSE,
	       plxdev->bar + PLX_REG_CTRL);

	ग_लिखोl(0, plxdev->bar + PLX_REG_DESC_RING_COUNT);
	ग_लिखोl(0, plxdev->bar + PLX_REG_DESC_RING_ADDR);
	ग_लिखोl(0, plxdev->bar + PLX_REG_DESC_RING_ADDR_HI);
	ग_लिखोl(0, plxdev->bar + PLX_REG_DESC_RING_NEXT_ADDR);
पूर्ण

अटल व्योम plx_dma_stop(काष्ठा plx_dma_dev *plxdev)
अणु
	rcu_पढ़ो_lock();
	अगर (!rcu_dereference(plxdev->pdev)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	__plx_dma_stop(plxdev);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम plx_dma_desc_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा plx_dma_dev *plxdev = from_tasklet(plxdev, t, desc_task);

	plx_dma_process_desc(plxdev);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *plx_dma_prep_स_नकल(काष्ठा dma_chan *c,
		dma_addr_t dma_dst, dma_addr_t dma_src, माप_प्रकार len,
		अचिन्हित दीर्घ flags)
	__acquires(plxdev->ring_lock)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(c);
	काष्ठा plx_dma_desc *plxdesc;

	spin_lock_bh(&plxdev->ring_lock);
	अगर (!plxdev->ring_active)
		जाओ err_unlock;

	अगर (!CIRC_SPACE(plxdev->head, plxdev->tail, PLX_DMA_RING_COUNT))
		जाओ err_unlock;

	अगर (len > PLX_DESC_SIZE_MASK)
		जाओ err_unlock;

	plxdesc = plx_dma_get_desc(plxdev, plxdev->head);
	plxdev->head++;

	plxdesc->hw->dst_addr_lo = cpu_to_le32(lower_32_bits(dma_dst));
	plxdesc->hw->dst_addr_hi = cpu_to_le16(upper_32_bits(dma_dst));
	plxdesc->hw->src_addr_lo = cpu_to_le32(lower_32_bits(dma_src));
	plxdesc->hw->src_addr_hi = cpu_to_le16(upper_32_bits(dma_src));

	plxdesc->orig_size = len;

	अगर (flags & DMA_PREP_INTERRUPT)
		len |= PLX_DESC_FLAG_INT_WHEN_DONE;

	plxdesc->hw->flags_and_size = cpu_to_le32(len);
	plxdesc->txd.flags = flags;

	/* वापस with the lock held, it will be released in tx_submit */

	वापस &plxdesc->txd;

err_unlock:
	/*
	 * Keep sparse happy by restoring an even lock count on
	 * this lock.
	 */
	__acquire(plxdev->ring_lock);

	spin_unlock_bh(&plxdev->ring_lock);
	वापस शून्य;
पूर्ण

अटल dma_cookie_t plx_dma_tx_submit(काष्ठा dma_async_tx_descriptor *desc)
	__releases(plxdev->ring_lock)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(desc->chan);
	काष्ठा plx_dma_desc *plxdesc = to_plx_desc(desc);
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(desc);

	/*
	 * Ensure the descriptor updates are visible to the dma device
	 * beक्रमe setting the valid bit.
	 */
	wmb();

	plxdesc->hw->flags_and_size |= cpu_to_le32(PLX_DESC_FLAG_VALID);

	spin_unlock_bh(&plxdev->ring_lock);

	वापस cookie;
पूर्ण

अटल क्रमागत dma_status plx_dma_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(chan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	plx_dma_process_desc(plxdev);

	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल व्योम plx_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(chan);

	rcu_पढ़ो_lock();
	अगर (!rcu_dereference(plxdev->pdev)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/*
	 * Ensure the valid bits are visible beक्रमe starting the
	 * DMA engine.
	 */
	wmb();

	ग_लिखोw(PLX_REG_CTRL_START_VAL, plxdev->bar + PLX_REG_CTRL);

	rcu_पढ़ो_unlock();
पूर्ण

अटल irqवापस_t plx_dma_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा plx_dma_dev *plxdev = devid;
	u32 status;

	status = पढ़ोw(plxdev->bar + PLX_REG_INTR_STATUS);

	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & PLX_REG_INTR_STATUS_DESC_DONE && plxdev->ring_active)
		tasklet_schedule(&plxdev->desc_task);

	ग_लिखोw(status, plxdev->bar + PLX_REG_INTR_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक plx_dma_alloc_desc(काष्ठा plx_dma_dev *plxdev)
अणु
	काष्ठा plx_dma_desc *desc;
	पूर्णांक i;

	plxdev->desc_ring = kसुस्मृति(PLX_DMA_RING_COUNT,
				    माप(*plxdev->desc_ring), GFP_KERNEL);
	अगर (!plxdev->desc_ring)
		वापस -ENOMEM;

	क्रम (i = 0; i < PLX_DMA_RING_COUNT; i++) अणु
		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc)
			जाओ मुक्त_and_निकास;

		dma_async_tx_descriptor_init(&desc->txd, &plxdev->dma_chan);
		desc->txd.tx_submit = plx_dma_tx_submit;
		desc->hw = &plxdev->hw_ring[i];

		plxdev->desc_ring[i] = desc;
	पूर्ण

	वापस 0;

मुक्त_and_निकास:
	क्रम (i = 0; i < PLX_DMA_RING_COUNT; i++)
		kमुक्त(plxdev->desc_ring[i]);
	kमुक्त(plxdev->desc_ring);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक plx_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(chan);
	माप_प्रकार ring_sz = PLX_DMA_RING_COUNT * माप(*plxdev->hw_ring);
	पूर्णांक rc;

	plxdev->head = plxdev->tail = 0;
	plxdev->hw_ring = dma_alloc_coherent(plxdev->dma_dev.dev, ring_sz,
					     &plxdev->hw_ring_dma, GFP_KERNEL);
	अगर (!plxdev->hw_ring)
		वापस -ENOMEM;

	rc = plx_dma_alloc_desc(plxdev);
	अगर (rc)
		जाओ out_मुक्त_hw_ring;

	rcu_पढ़ो_lock();
	अगर (!rcu_dereference(plxdev->pdev)) अणु
		rcu_पढ़ो_unlock();
		rc = -ENODEV;
		जाओ out_मुक्त_hw_ring;
	पूर्ण

	ग_लिखोl(PLX_REG_CTRL_RESET_VAL, plxdev->bar + PLX_REG_CTRL);
	ग_लिखोl(lower_32_bits(plxdev->hw_ring_dma),
	       plxdev->bar + PLX_REG_DESC_RING_ADDR);
	ग_लिखोl(upper_32_bits(plxdev->hw_ring_dma),
	       plxdev->bar + PLX_REG_DESC_RING_ADDR_HI);
	ग_लिखोl(lower_32_bits(plxdev->hw_ring_dma),
	       plxdev->bar + PLX_REG_DESC_RING_NEXT_ADDR);
	ग_लिखोl(PLX_DMA_RING_COUNT, plxdev->bar + PLX_REG_DESC_RING_COUNT);
	ग_लिखोl(PLX_REG_PREF_LIMIT_PREF_FOUR, plxdev->bar + PLX_REG_PREF_LIMIT);

	plxdev->ring_active = true;

	rcu_पढ़ो_unlock();

	वापस PLX_DMA_RING_COUNT;

out_मुक्त_hw_ring:
	dma_मुक्त_coherent(plxdev->dma_dev.dev, ring_sz, plxdev->hw_ring,
			  plxdev->hw_ring_dma);
	वापस rc;
पूर्ण

अटल व्योम plx_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा plx_dma_dev *plxdev = chan_to_plx_dma_dev(chan);
	माप_प्रकार ring_sz = PLX_DMA_RING_COUNT * माप(*plxdev->hw_ring);
	काष्ठा pci_dev *pdev;
	पूर्णांक irq = -1;
	पूर्णांक i;

	spin_lock_bh(&plxdev->ring_lock);
	plxdev->ring_active = false;
	spin_unlock_bh(&plxdev->ring_lock);

	plx_dma_stop(plxdev);

	rcu_पढ़ो_lock();
	pdev = rcu_dereference(plxdev->pdev);
	अगर (pdev)
		irq = pci_irq_vector(pdev, 0);
	rcu_पढ़ो_unlock();

	अगर (irq > 0)
		synchronize_irq(irq);

	tasklet_समाप्त(&plxdev->desc_task);

	plx_dma_पात_desc(plxdev);

	क्रम (i = 0; i < PLX_DMA_RING_COUNT; i++)
		kमुक्त(plxdev->desc_ring[i]);

	kमुक्त(plxdev->desc_ring);
	dma_मुक्त_coherent(plxdev->dma_dev.dev, ring_sz, plxdev->hw_ring,
			  plxdev->hw_ring_dma);

पूर्ण

अटल व्योम plx_dma_release(काष्ठा dma_device *dma_dev)
अणु
	काष्ठा plx_dma_dev *plxdev =
		container_of(dma_dev, काष्ठा plx_dma_dev, dma_dev);

	put_device(dma_dev->dev);
	kमुक्त(plxdev);
पूर्ण

अटल पूर्णांक plx_dma_create(काष्ठा pci_dev *pdev)
अणु
	काष्ठा plx_dma_dev *plxdev;
	काष्ठा dma_device *dma;
	काष्ठा dma_chan *chan;
	पूर्णांक rc;

	plxdev = kzalloc(माप(*plxdev), GFP_KERNEL);
	अगर (!plxdev)
		वापस -ENOMEM;

	rc = request_irq(pci_irq_vector(pdev, 0), plx_dma_isr, 0,
			 KBUILD_MODNAME, plxdev);
	अगर (rc)
		जाओ मुक्त_plx;

	spin_lock_init(&plxdev->ring_lock);
	tasklet_setup(&plxdev->desc_task, plx_dma_desc_task);

	RCU_INIT_POINTER(plxdev->pdev, pdev);
	plxdev->bar = pcim_iomap_table(pdev)[0];

	dma = &plxdev->dma_dev;
	dma->chancnt = 1;
	INIT_LIST_HEAD(&dma->channels);
	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma->copy_align = DMAENGINE_ALIGN_1_BYTE;
	dma->dev = get_device(&pdev->dev);

	dma->device_alloc_chan_resources = plx_dma_alloc_chan_resources;
	dma->device_मुक्त_chan_resources = plx_dma_मुक्त_chan_resources;
	dma->device_prep_dma_स_नकल = plx_dma_prep_स_नकल;
	dma->device_issue_pending = plx_dma_issue_pending;
	dma->device_tx_status = plx_dma_tx_status;
	dma->device_release = plx_dma_release;

	chan = &plxdev->dma_chan;
	chan->device = dma;
	dma_cookie_init(chan);
	list_add_tail(&chan->device_node, &dma->channels);

	rc = dma_async_device_रेजिस्टर(dma);
	अगर (rc) अणु
		pci_err(pdev, "Failed to register dma device: %d\n", rc);
		जाओ put_device;
	पूर्ण

	pci_set_drvdata(pdev, plxdev);

	वापस 0;

put_device:
	put_device(&pdev->dev);
	मुक्त_irq(pci_irq_vector(pdev, 0),  plxdev);
मुक्त_plx:
	kमुक्त(plxdev);

	वापस rc;
पूर्ण

अटल पूर्णांक plx_dma_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (rc)
		rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (rc)
		rc = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, 1, KBUILD_MODNAME);
	अगर (rc)
		वापस rc;

	rc = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (rc <= 0)
		वापस rc;

	pci_set_master(pdev);

	rc = plx_dma_create(pdev);
	अगर (rc)
		जाओ err_मुक्त_irq_vectors;

	pci_info(pdev, "PLX DMA Channel Registered\n");

	वापस 0;

err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
	वापस rc;
पूर्ण

अटल व्योम plx_dma_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा plx_dma_dev *plxdev = pci_get_drvdata(pdev);

	मुक्त_irq(pci_irq_vector(pdev, 0),  plxdev);

	rcu_assign_poपूर्णांकer(plxdev->pdev, शून्य);
	synchronize_rcu();

	spin_lock_bh(&plxdev->ring_lock);
	plxdev->ring_active = false;
	spin_unlock_bh(&plxdev->ring_lock);

	__plx_dma_stop(plxdev);
	plx_dma_पात_desc(plxdev);

	plxdev->bar = शून्य;
	dma_async_device_unरेजिस्टर(&plxdev->dma_dev);

	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id plx_dma_pci_tbl[] = अणु
	अणु
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= 0x87D0,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.class		= PCI_CLASS_SYSTEM_OTHER << 8,
		.class_mask	= 0xFFFFFFFF,
	पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, plx_dma_pci_tbl);

अटल काष्ठा pci_driver plx_dma_pci_driver = अणु
	.name           = KBUILD_MODNAME,
	.id_table       = plx_dma_pci_tbl,
	.probe          = plx_dma_probe,
	.हटाओ		= plx_dma_हटाओ,
पूर्ण;
module_pci_driver(plx_dma_pci_driver);
