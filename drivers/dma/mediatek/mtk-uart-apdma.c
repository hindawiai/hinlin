<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek UART APDMA driver.
 *
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Long Cheng <दीर्घ.cheng@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../virt-dma.h"

/* The शेष number of भव channel */
#घोषणा MTK_UART_APDMA_NR_VCHANS	8

#घोषणा VFF_EN_B		BIT(0)
#घोषणा VFF_STOP_B		BIT(0)
#घोषणा VFF_FLUSH_B		BIT(0)
#घोषणा VFF_4G_EN_B		BIT(0)
/* rx valid size >=  vff thre */
#घोषणा VFF_RX_INT_EN_B		(BIT(0) | BIT(1))
/* tx left size >= vff thre */
#घोषणा VFF_TX_INT_EN_B		BIT(0)
#घोषणा VFF_WARM_RST_B		BIT(0)
#घोषणा VFF_RX_INT_CLR_B	(BIT(0) | BIT(1))
#घोषणा VFF_TX_INT_CLR_B	0
#घोषणा VFF_STOP_CLR_B		0
#घोषणा VFF_EN_CLR_B		0
#घोषणा VFF_INT_EN_CLR_B	0
#घोषणा VFF_4G_SUPPORT_CLR_B	0

/*
 * पूर्णांकerrupt trigger level क्रम tx
 * अगर threshold is n, no polling is required to start tx.
 * otherwise need polling VFF_FLUSH.
 */
#घोषणा VFF_TX_THRE(n)		(n)
/* पूर्णांकerrupt trigger level क्रम rx */
#घोषणा VFF_RX_THRE(n)		((n) * 3 / 4)

#घोषणा VFF_RING_SIZE	0xffff
/* invert this bit when wrap ring head again */
#घोषणा VFF_RING_WRAP	0x10000

#घोषणा VFF_INT_FLAG		0x00
#घोषणा VFF_INT_EN		0x04
#घोषणा VFF_EN			0x08
#घोषणा VFF_RST			0x0c
#घोषणा VFF_STOP		0x10
#घोषणा VFF_FLUSH		0x14
#घोषणा VFF_ADDR		0x1c
#घोषणा VFF_LEN			0x24
#घोषणा VFF_THRE		0x28
#घोषणा VFF_WPT			0x2c
#घोषणा VFF_RPT			0x30
/* TX: the buffer size HW can पढ़ो. RX: the buffer size SW can पढ़ो. */
#घोषणा VFF_VALID_SIZE		0x3c
/* TX: the buffer size SW can ग_लिखो. RX: the buffer size HW can ग_लिखो. */
#घोषणा VFF_LEFT_SIZE		0x40
#घोषणा VFF_DEBUG_STATUS	0x50
#घोषणा VFF_4G_SUPPORT		0x54

काष्ठा mtk_uart_apdmadev अणु
	काष्ठा dma_device ddev;
	काष्ठा clk *clk;
	bool support_33bits;
	अचिन्हित पूर्णांक dma_requests;
पूर्ण;

काष्ठा mtk_uart_apdma_desc अणु
	काष्ठा virt_dma_desc vd;

	dma_addr_t addr;
	अचिन्हित पूर्णांक avail_len;
पूर्ण;

काष्ठा mtk_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा dma_slave_config	cfg;
	काष्ठा mtk_uart_apdma_desc *desc;
	क्रमागत dma_transfer_direction dir;

	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;

	अचिन्हित पूर्णांक rx_status;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_uart_apdmadev *
to_mtk_uart_apdma_dev(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा mtk_uart_apdmadev, ddev);
पूर्ण

अटल अंतरभूत काष्ठा mtk_chan *to_mtk_uart_apdma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा mtk_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा mtk_uart_apdma_desc *to_mtk_uart_apdma_desc
	(काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा mtk_uart_apdma_desc, vd.tx);
पूर्ण

अटल व्योम mtk_uart_apdma_ग_लिखो(काष्ठा mtk_chan *c,
			       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, c->base + reg);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_uart_apdma_पढ़ो(काष्ठा mtk_chan *c, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(c->base + reg);
पूर्ण

अटल व्योम mtk_uart_apdma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(container_of(vd, काष्ठा mtk_uart_apdma_desc, vd));
पूर्ण

अटल व्योम mtk_uart_apdma_start_tx(काष्ठा mtk_chan *c)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd =
				to_mtk_uart_apdma_dev(c->vc.chan.device);
	काष्ठा mtk_uart_apdma_desc *d = c->desc;
	अचिन्हित पूर्णांक wpt, vff_sz;

	vff_sz = c->cfg.dst_port_winकरोw_size;
	अगर (!mtk_uart_apdma_पढ़ो(c, VFF_LEN)) अणु
		mtk_uart_apdma_ग_लिखो(c, VFF_ADDR, d->addr);
		mtk_uart_apdma_ग_लिखो(c, VFF_LEN, vff_sz);
		mtk_uart_apdma_ग_लिखो(c, VFF_THRE, VFF_TX_THRE(vff_sz));
		mtk_uart_apdma_ग_लिखो(c, VFF_WPT, 0);
		mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_TX_INT_CLR_B);

		अगर (mtkd->support_33bits)
			mtk_uart_apdma_ग_लिखो(c, VFF_4G_SUPPORT, VFF_4G_EN_B);
	पूर्ण

	mtk_uart_apdma_ग_लिखो(c, VFF_EN, VFF_EN_B);
	अगर (mtk_uart_apdma_पढ़ो(c, VFF_EN) != VFF_EN_B)
		dev_err(c->vc.chan.device->dev, "Enable TX fail\n");

	अगर (!mtk_uart_apdma_पढ़ो(c, VFF_LEFT_SIZE)) अणु
		mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_TX_INT_EN_B);
		वापस;
	पूर्ण

	wpt = mtk_uart_apdma_पढ़ो(c, VFF_WPT);

	wpt += c->desc->avail_len;
	अगर ((wpt & VFF_RING_SIZE) == vff_sz)
		wpt = (wpt & VFF_RING_WRAP) ^ VFF_RING_WRAP;

	/* Let DMA start moving data */
	mtk_uart_apdma_ग_लिखो(c, VFF_WPT, wpt);

	/* HW स्वतः set to 0 when left size >= threshold */
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_TX_INT_EN_B);
	अगर (!mtk_uart_apdma_पढ़ो(c, VFF_FLUSH))
		mtk_uart_apdma_ग_लिखो(c, VFF_FLUSH, VFF_FLUSH_B);
पूर्ण

अटल व्योम mtk_uart_apdma_start_rx(काष्ठा mtk_chan *c)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd =
				to_mtk_uart_apdma_dev(c->vc.chan.device);
	काष्ठा mtk_uart_apdma_desc *d = c->desc;
	अचिन्हित पूर्णांक vff_sz;

	vff_sz = c->cfg.src_port_winकरोw_size;
	अगर (!mtk_uart_apdma_पढ़ो(c, VFF_LEN)) अणु
		mtk_uart_apdma_ग_लिखो(c, VFF_ADDR, d->addr);
		mtk_uart_apdma_ग_लिखो(c, VFF_LEN, vff_sz);
		mtk_uart_apdma_ग_लिखो(c, VFF_THRE, VFF_RX_THRE(vff_sz));
		mtk_uart_apdma_ग_लिखो(c, VFF_RPT, 0);
		mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_RX_INT_CLR_B);

		अगर (mtkd->support_33bits)
			mtk_uart_apdma_ग_लिखो(c, VFF_4G_SUPPORT, VFF_4G_EN_B);
	पूर्ण

	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_RX_INT_EN_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_EN, VFF_EN_B);
	अगर (mtk_uart_apdma_पढ़ो(c, VFF_EN) != VFF_EN_B)
		dev_err(c->vc.chan.device->dev, "Enable RX fail\n");
पूर्ण

अटल व्योम mtk_uart_apdma_tx_handler(काष्ठा mtk_chan *c)
अणु
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_TX_INT_CLR_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_INT_EN_CLR_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_EN, VFF_EN_CLR_B);
पूर्ण

अटल व्योम mtk_uart_apdma_rx_handler(काष्ठा mtk_chan *c)
अणु
	काष्ठा mtk_uart_apdma_desc *d = c->desc;
	अचिन्हित पूर्णांक len, wg, rg;
	पूर्णांक cnt;

	mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_RX_INT_CLR_B);

	अगर (!mtk_uart_apdma_पढ़ो(c, VFF_VALID_SIZE))
		वापस;

	mtk_uart_apdma_ग_लिखो(c, VFF_EN, VFF_EN_CLR_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_INT_EN_CLR_B);

	len = c->cfg.src_port_winकरोw_size;
	rg = mtk_uart_apdma_पढ़ो(c, VFF_RPT);
	wg = mtk_uart_apdma_पढ़ो(c, VFF_WPT);
	cnt = (wg & VFF_RING_SIZE) - (rg & VFF_RING_SIZE);

	/*
	 * The buffer is ring buffer. If wrap bit dअगरferent,
	 * represents the start of the next cycle क्रम WPT
	 */
	अगर ((rg ^ wg) & VFF_RING_WRAP)
		cnt += len;

	c->rx_status = d->avail_len - cnt;
	mtk_uart_apdma_ग_लिखो(c, VFF_RPT, wg);
पूर्ण

अटल व्योम mtk_uart_apdma_chan_complete_handler(काष्ठा mtk_chan *c)
अणु
	काष्ठा mtk_uart_apdma_desc *d = c->desc;

	अगर (d) अणु
		list_del(&d->vd.node);
		vchan_cookie_complete(&d->vd);
		c->desc = शून्य;
	पूर्ण
पूर्ण

अटल irqवापस_t mtk_uart_apdma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dma_chan *chan = (काष्ठा dma_chan *)dev_id;
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (c->dir == DMA_DEV_TO_MEM)
		mtk_uart_apdma_rx_handler(c);
	अन्यथा अगर (c->dir == DMA_MEM_TO_DEV)
		mtk_uart_apdma_tx_handler(c);
	mtk_uart_apdma_chan_complete_handler(c);
	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = to_mtk_uart_apdma_dev(chan->device);
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(mtkd->ddev.dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(chan->device->dev);
		वापस ret;
	पूर्ण

	mtk_uart_apdma_ग_लिखो(c, VFF_ADDR, 0);
	mtk_uart_apdma_ग_लिखो(c, VFF_THRE, 0);
	mtk_uart_apdma_ग_लिखो(c, VFF_LEN, 0);
	mtk_uart_apdma_ग_लिखो(c, VFF_RST, VFF_WARM_RST_B);

	ret = पढ़ोx_poll_समयout(पढ़ोl, c->base + VFF_EN,
			  status, !status, 10, 100);
	अगर (ret)
		वापस ret;

	ret = request_irq(c->irq, mtk_uart_apdma_irq_handler,
			  IRQF_TRIGGER_NONE, KBUILD_MODNAME, chan);
	अगर (ret < 0) अणु
		dev_err(chan->device->dev, "Can't request dma IRQ\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mtkd->support_33bits)
		mtk_uart_apdma_ग_लिखो(c, VFF_4G_SUPPORT, VFF_4G_SUPPORT_CLR_B);

	वापस ret;
पूर्ण

अटल व्योम mtk_uart_apdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = to_mtk_uart_apdma_dev(chan->device);
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);

	मुक्त_irq(c->irq, chan);

	tasklet_समाप्त(&c->vc.task);

	vchan_मुक्त_chan_resources(&c->vc);

	pm_runसमय_put_sync(mtkd->ddev.dev);
पूर्ण

अटल क्रमागत dma_status mtk_uart_apdma_tx_status(काष्ठा dma_chan *chan,
					 dma_cookie_t cookie,
					 काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (!txstate)
		वापस ret;

	dma_set_residue(txstate, c->rx_status);

	वापस ret;
पूर्ण

/*
 * dmaengine_prep_slave_single will call the function. and sglen is 1.
 * 8250 uart using one ring buffer, and deal with one sg.
 */
अटल काष्ठा dma_async_tx_descriptor *mtk_uart_apdma_prep_slave_sg
	(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
	अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
	अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	काष्ठा mtk_uart_apdma_desc *d;

	अगर (!is_slave_direction(dir) || sglen != 1)
		वापस शून्य;

	/* Now allocate and setup the descriptor */
	d = kzalloc(माप(*d), GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	d->avail_len = sg_dma_len(sgl);
	d->addr = sg_dma_address(sgl);
	c->dir = dir;

	वापस vchan_tx_prep(&c->vc, &d->vd, tx_flags);
पूर्ण

अटल व्योम mtk_uart_apdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (vchan_issue_pending(&c->vc) && !c->desc) अणु
		vd = vchan_next_desc(&c->vc);
		c->desc = to_mtk_uart_apdma_desc(&vd->tx);

		अगर (c->dir == DMA_DEV_TO_MEM)
			mtk_uart_apdma_start_rx(c);
		अन्यथा अगर (c->dir == DMA_MEM_TO_DEV)
			mtk_uart_apdma_start_tx(c);
	पूर्ण

	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल पूर्णांक mtk_uart_apdma_slave_config(काष्ठा dma_chan *chan,
				   काष्ठा dma_slave_config *config)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);

	स_नकल(&c->cfg, config, माप(*config));

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;
	LIST_HEAD(head);
	पूर्णांक ret;

	mtk_uart_apdma_ग_लिखो(c, VFF_FLUSH, VFF_FLUSH_B);

	ret = पढ़ोx_poll_समयout(पढ़ोl, c->base + VFF_FLUSH,
			  status, status != VFF_FLUSH_B, 10, 100);
	अगर (ret)
		dev_err(c->vc.chan.device->dev, "flush: fail, status=0x%x\n",
			mtk_uart_apdma_पढ़ो(c, VFF_DEBUG_STATUS));

	/*
	 * Stop need 3 steps.
	 * 1. set stop to 1
	 * 2. रुको en to 0
	 * 3. set stop as 0
	 */
	mtk_uart_apdma_ग_लिखो(c, VFF_STOP, VFF_STOP_B);
	ret = पढ़ोx_poll_समयout(पढ़ोl, c->base + VFF_EN,
			  status, !status, 10, 100);
	अगर (ret)
		dev_err(c->vc.chan.device->dev, "stop: fail, status=0x%x\n",
			mtk_uart_apdma_पढ़ो(c, VFF_DEBUG_STATUS));

	mtk_uart_apdma_ग_लिखो(c, VFF_STOP, VFF_STOP_CLR_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_INT_EN_CLR_B);

	अगर (c->dir == DMA_DEV_TO_MEM)
		mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_RX_INT_CLR_B);
	अन्यथा अगर (c->dir == DMA_MEM_TO_DEV)
		mtk_uart_apdma_ग_लिखो(c, VFF_INT_FLAG, VFF_TX_INT_CLR_B);

	synchronize_irq(c->irq);

	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);
	spin_unlock_irqrestore(&c->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&c->vc, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_device_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा mtk_chan *c = to_mtk_uart_apdma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);

	mtk_uart_apdma_ग_लिखो(c, VFF_EN, VFF_EN_CLR_B);
	mtk_uart_apdma_ग_लिखो(c, VFF_INT_EN, VFF_INT_EN_CLR_B);

	synchronize_irq(c->irq);

	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mtk_uart_apdma_मुक्त(काष्ठा mtk_uart_apdmadev *mtkd)
अणु
	जबतक (!list_empty(&mtkd->ddev.channels)) अणु
		काष्ठा mtk_chan *c = list_first_entry(&mtkd->ddev.channels,
			काष्ठा mtk_chan, vc.chan.device_node);

		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_uart_apdma_match[] = अणु
	अणु .compatible = "mediatek,mt6577-uart-dma", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_uart_apdma_match);

अटल पूर्णांक mtk_uart_apdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mtk_uart_apdmadev *mtkd;
	पूर्णांक bit_mask = 32, rc;
	काष्ठा mtk_chan *c;
	अचिन्हित पूर्णांक i;

	mtkd = devm_kzalloc(&pdev->dev, माप(*mtkd), GFP_KERNEL);
	अगर (!mtkd)
		वापस -ENOMEM;

	mtkd->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mtkd->clk)) अणु
		dev_err(&pdev->dev, "No clock specified\n");
		rc = PTR_ERR(mtkd->clk);
		वापस rc;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "mediatek,dma-33bits"))
		mtkd->support_33bits = true;

	अगर (mtkd->support_33bits)
		bit_mask = 33;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(bit_mask));
	अगर (rc)
		वापस rc;

	dma_cap_set(DMA_SLAVE, mtkd->ddev.cap_mask);
	mtkd->ddev.device_alloc_chan_resources =
				mtk_uart_apdma_alloc_chan_resources;
	mtkd->ddev.device_मुक्त_chan_resources =
				mtk_uart_apdma_मुक्त_chan_resources;
	mtkd->ddev.device_tx_status = mtk_uart_apdma_tx_status;
	mtkd->ddev.device_issue_pending = mtk_uart_apdma_issue_pending;
	mtkd->ddev.device_prep_slave_sg = mtk_uart_apdma_prep_slave_sg;
	mtkd->ddev.device_config = mtk_uart_apdma_slave_config;
	mtkd->ddev.device_छोड़ो = mtk_uart_apdma_device_छोड़ो;
	mtkd->ddev.device_terminate_all = mtk_uart_apdma_terminate_all;
	mtkd->ddev.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE);
	mtkd->ddev.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE);
	mtkd->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mtkd->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	mtkd->ddev.dev = &pdev->dev;
	INIT_LIST_HEAD(&mtkd->ddev.channels);

	mtkd->dma_requests = MTK_UART_APDMA_NR_VCHANS;
	अगर (of_property_पढ़ो_u32(np, "dma-requests", &mtkd->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Using %u as missing dma-requests property\n",
			 MTK_UART_APDMA_NR_VCHANS);
	पूर्ण

	क्रम (i = 0; i < mtkd->dma_requests; i++) अणु
		c = devm_kzalloc(mtkd->ddev.dev, माप(*c), GFP_KERNEL);
		अगर (!c) अणु
			rc = -ENODEV;
			जाओ err_no_dma;
		पूर्ण

		c->base = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR(c->base)) अणु
			rc = PTR_ERR(c->base);
			जाओ err_no_dma;
		पूर्ण
		c->vc.desc_मुक्त = mtk_uart_apdma_desc_मुक्त;
		vchan_init(&c->vc, &mtkd->ddev);

		rc = platक्रमm_get_irq(pdev, i);
		अगर (rc < 0)
			जाओ err_no_dma;
		c->irq = rc;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);

	rc = dma_async_device_रेजिस्टर(&mtkd->ddev);
	अगर (rc)
		जाओ rpm_disable;

	platक्रमm_set_drvdata(pdev, mtkd);

	/* Device-tree DMA controller registration */
	rc = of_dma_controller_रेजिस्टर(np, of_dma_xlate_by_chan_id, mtkd);
	अगर (rc)
		जाओ dma_हटाओ;

	वापस rc;

dma_हटाओ:
	dma_async_device_unरेजिस्टर(&mtkd->ddev);
rpm_disable:
	pm_runसमय_disable(&pdev->dev);
err_no_dma:
	mtk_uart_apdma_मुक्त(mtkd);
	वापस rc;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);

	mtk_uart_apdma_मुक्त(mtkd);

	dma_async_device_unरेजिस्टर(&mtkd->ddev);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_uart_apdma_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = dev_get_drvdata(dev);

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(mtkd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा mtk_uart_apdmadev *mtkd = dev_get_drvdata(dev);

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = clk_prepare_enable(mtkd->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mtk_uart_apdma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = dev_get_drvdata(dev);

	clk_disable_unprepare(mtkd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_uart_apdma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_uart_apdmadev *mtkd = dev_get_drvdata(dev);

	वापस clk_prepare_enable(mtkd->clk);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops mtk_uart_apdma_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_uart_apdma_suspend, mtk_uart_apdma_resume)
	SET_RUNTIME_PM_OPS(mtk_uart_apdma_runसमय_suspend,
			   mtk_uart_apdma_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_uart_apdma_driver = अणु
	.probe	= mtk_uart_apdma_probe,
	.हटाओ	= mtk_uart_apdma_हटाओ,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.pm		= &mtk_uart_apdma_pm_ops,
		.of_match_table = of_match_ptr(mtk_uart_apdma_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_uart_apdma_driver);

MODULE_DESCRIPTION("MediaTek UART APDMA Controller Driver");
MODULE_AUTHOR("Long Cheng <long.cheng@mediatek.com>");
MODULE_LICENSE("GPL v2");
