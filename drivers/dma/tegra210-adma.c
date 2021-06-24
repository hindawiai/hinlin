<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADMA driver क्रम Nvidia's Tegra210 ADMA controller.
 *
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश "virt-dma.h"

#घोषणा ADMA_CH_CMD					0x00
#घोषणा ADMA_CH_STATUS					0x0c
#घोषणा ADMA_CH_STATUS_XFER_EN				BIT(0)
#घोषणा ADMA_CH_STATUS_XFER_PAUSED			BIT(1)

#घोषणा ADMA_CH_INT_STATUS				0x10
#घोषणा ADMA_CH_INT_STATUS_XFER_DONE			BIT(0)

#घोषणा ADMA_CH_INT_CLEAR				0x1c
#घोषणा ADMA_CH_CTRL					0x24
#घोषणा ADMA_CH_CTRL_सूची(val)				(((val) & 0xf) << 12)
#घोषणा ADMA_CH_CTRL_सूची_AHUB2MEM			2
#घोषणा ADMA_CH_CTRL_सूची_MEM2AHUB			4
#घोषणा ADMA_CH_CTRL_MODE_CONTINUOUS			(2 << 8)
#घोषणा ADMA_CH_CTRL_FLOWCTRL_EN			BIT(1)
#घोषणा ADMA_CH_CTRL_XFER_PAUSE_SHIFT			0

#घोषणा ADMA_CH_CONFIG					0x28
#घोषणा ADMA_CH_CONFIG_SRC_BUF(val)			(((val) & 0x7) << 28)
#घोषणा ADMA_CH_CONFIG_TRG_BUF(val)			(((val) & 0x7) << 24)
#घोषणा ADMA_CH_CONFIG_BURST_SIZE_SHIFT			20
#घोषणा ADMA_CH_CONFIG_MAX_BURST_SIZE                   16
#घोषणा ADMA_CH_CONFIG_WEIGHT_FOR_WRR(val)		((val) & 0xf)
#घोषणा ADMA_CH_CONFIG_MAX_BUFS				8
#घोषणा TEGRA186_ADMA_CH_CONFIG_OUTSTANDING_REQS(reqs)	(reqs << 4)

#घोषणा ADMA_CH_FIFO_CTRL				0x2c
#घोषणा TEGRA210_ADMA_CH_FIFO_CTRL_TXSIZE(val)		(((val) & 0xf) << 8)
#घोषणा TEGRA210_ADMA_CH_FIFO_CTRL_RXSIZE(val)		((val) & 0xf)
#घोषणा TEGRA186_ADMA_CH_FIFO_CTRL_TXSIZE(val)		(((val) & 0x1f) << 8)
#घोषणा TEGRA186_ADMA_CH_FIFO_CTRL_RXSIZE(val)		((val) & 0x1f)

#घोषणा ADMA_CH_LOWER_SRC_ADDR				0x34
#घोषणा ADMA_CH_LOWER_TRG_ADDR				0x3c
#घोषणा ADMA_CH_TC					0x44
#घोषणा ADMA_CH_TC_COUNT_MASK				0x3ffffffc

#घोषणा ADMA_CH_XFER_STATUS				0x54
#घोषणा ADMA_CH_XFER_STATUS_COUNT_MASK			0xffff

#घोषणा ADMA_GLOBAL_CMD					0x00
#घोषणा ADMA_GLOBAL_SOFT_RESET				0x04

#घोषणा TEGRA_ADMA_BURST_COMPLETE_TIME			20

#घोषणा TEGRA210_FIFO_CTRL_DEFAULT (TEGRA210_ADMA_CH_FIFO_CTRL_TXSIZE(3) | \
				    TEGRA210_ADMA_CH_FIFO_CTRL_RXSIZE(3))

#घोषणा TEGRA186_FIFO_CTRL_DEFAULT (TEGRA186_ADMA_CH_FIFO_CTRL_TXSIZE(3) | \
				    TEGRA186_ADMA_CH_FIFO_CTRL_RXSIZE(3))

#घोषणा ADMA_CH_REG_FIELD_VAL(val, mask, shअगरt)	(((val) & mask) << shअगरt)

काष्ठा tegra_adma;

/*
 * काष्ठा tegra_adma_chip_data - Tegra chip specअगरic data
 * @global_reg_offset: Register offset of DMA global रेजिस्टर.
 * @global_पूर्णांक_clear: Register offset of DMA global पूर्णांकerrupt clear.
 * @ch_req_tx_shअगरt: Register offset क्रम AHUB transmit channel select.
 * @ch_req_rx_shअगरt: Register offset क्रम AHUB receive channel select.
 * @ch_base_offset: Register offset of DMA channel रेजिस्टरs.
 * @has_outstanding_reqs: If DMA channel can have outstanding requests.
 * @ch_fअगरo_ctrl: Default value क्रम channel FIFO CTRL रेजिस्टर.
 * @ch_req_mask: Mask क्रम Tx or Rx channel select.
 * @ch_req_max: Maximum number of Tx or Rx channels available.
 * @ch_reg_size: Size of DMA channel रेजिस्टर space.
 * @nr_channels: Number of DMA channels available.
 */
काष्ठा tegra_adma_chip_data अणु
	अचिन्हित पूर्णांक (*adma_get_burst_config)(अचिन्हित पूर्णांक burst_size);
	अचिन्हित पूर्णांक global_reg_offset;
	अचिन्हित पूर्णांक global_पूर्णांक_clear;
	अचिन्हित पूर्णांक ch_req_tx_shअगरt;
	अचिन्हित पूर्णांक ch_req_rx_shअगरt;
	अचिन्हित पूर्णांक ch_base_offset;
	अचिन्हित पूर्णांक ch_fअगरo_ctrl;
	अचिन्हित पूर्णांक ch_req_mask;
	अचिन्हित पूर्णांक ch_req_max;
	अचिन्हित पूर्णांक ch_reg_size;
	अचिन्हित पूर्णांक nr_channels;
	bool has_outstanding_reqs;
पूर्ण;

/*
 * काष्ठा tegra_adma_chan_regs - Tegra ADMA channel रेजिस्टरs
 */
काष्ठा tegra_adma_chan_regs अणु
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक config;
	अचिन्हित पूर्णांक src_addr;
	अचिन्हित पूर्णांक trg_addr;
	अचिन्हित पूर्णांक fअगरo_ctrl;
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक tc;
पूर्ण;

/*
 * काष्ठा tegra_adma_desc - Tegra ADMA descriptor to manage transfer requests.
 */
काष्ठा tegra_adma_desc अणु
	काष्ठा virt_dma_desc		vd;
	काष्ठा tegra_adma_chan_regs	ch_regs;
	माप_प्रकार				buf_len;
	माप_प्रकार				period_len;
	माप_प्रकार				num_periods;
पूर्ण;

/*
 * काष्ठा tegra_adma_chan - Tegra ADMA channel inक्रमmation
 */
काष्ठा tegra_adma_chan अणु
	काष्ठा virt_dma_chan		vc;
	काष्ठा tegra_adma_desc		*desc;
	काष्ठा tegra_adma		*tdma;
	पूर्णांक				irq;
	व्योम __iomem			*chan_addr;

	/* Slave channel configuration info */
	काष्ठा dma_slave_config		sconfig;
	क्रमागत dma_transfer_direction	sreq_dir;
	अचिन्हित पूर्णांक			sreq_index;
	bool				sreq_reserved;
	काष्ठा tegra_adma_chan_regs	ch_regs;

	/* Transfer count and position info */
	अचिन्हित पूर्णांक			tx_buf_count;
	अचिन्हित पूर्णांक			tx_buf_pos;
पूर्ण;

/*
 * काष्ठा tegra_adma - Tegra ADMA controller inक्रमmation
 */
काष्ठा tegra_adma अणु
	काष्ठा dma_device		dma_dev;
	काष्ठा device			*dev;
	व्योम __iomem			*base_addr;
	काष्ठा clk			*ahub_clk;
	अचिन्हित पूर्णांक			nr_channels;
	अचिन्हित दीर्घ			rx_requests_reserved;
	अचिन्हित दीर्घ			tx_requests_reserved;

	/* Used to store global command रेजिस्टर state when suspending */
	अचिन्हित पूर्णांक			global_cmd;

	स्थिर काष्ठा tegra_adma_chip_data *cdata;

	/* Last member of the काष्ठाure */
	काष्ठा tegra_adma_chan		channels[];
पूर्ण;

अटल अंतरभूत व्योम tdma_ग_लिखो(काष्ठा tegra_adma *tdma, u32 reg, u32 val)
अणु
	ग_लिखोl(val, tdma->base_addr + tdma->cdata->global_reg_offset + reg);
पूर्ण

अटल अंतरभूत u32 tdma_पढ़ो(काष्ठा tegra_adma *tdma, u32 reg)
अणु
	वापस पढ़ोl(tdma->base_addr + tdma->cdata->global_reg_offset + reg);
पूर्ण

अटल अंतरभूत व्योम tdma_ch_ग_लिखो(काष्ठा tegra_adma_chan *tdc, u32 reg, u32 val)
अणु
	ग_लिखोl(val, tdc->chan_addr + reg);
पूर्ण

अटल अंतरभूत u32 tdma_ch_पढ़ो(काष्ठा tegra_adma_chan *tdc, u32 reg)
अणु
	वापस पढ़ोl(tdc->chan_addr + reg);
पूर्ण

अटल अंतरभूत काष्ठा tegra_adma_chan *to_tegra_adma_chan(काष्ठा dma_chan *dc)
अणु
	वापस container_of(dc, काष्ठा tegra_adma_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा tegra_adma_desc *to_tegra_adma_desc(
		काष्ठा dma_async_tx_descriptor *td)
अणु
	वापस container_of(td, काष्ठा tegra_adma_desc, vd.tx);
पूर्ण

अटल अंतरभूत काष्ठा device *tdc2dev(काष्ठा tegra_adma_chan *tdc)
अणु
	वापस tdc->tdma->dev;
पूर्ण

अटल व्योम tegra_adma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(container_of(vd, काष्ठा tegra_adma_desc, vd));
पूर्ण

अटल पूर्णांक tegra_adma_slave_config(काष्ठा dma_chan *dc,
				   काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);

	स_नकल(&tdc->sconfig, sconfig, माप(*sconfig));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_adma_init(काष्ठा tegra_adma *tdma)
अणु
	u32 status;
	पूर्णांक ret;

	/* Clear any पूर्णांकerrupts */
	tdma_ग_लिखो(tdma, tdma->cdata->global_पूर्णांक_clear, 0x1);

	/* Assert soft reset */
	tdma_ग_लिखो(tdma, ADMA_GLOBAL_SOFT_RESET, 0x1);

	/* Wait क्रम reset to clear */
	ret = पढ़ोx_poll_समयout(पढ़ोl,
				 tdma->base_addr +
				 tdma->cdata->global_reg_offset +
				 ADMA_GLOBAL_SOFT_RESET,
				 status, status == 0, 20, 10000);
	अगर (ret)
		वापस ret;

	/* Enable global ADMA रेजिस्टरs */
	tdma_ग_लिखो(tdma, ADMA_GLOBAL_CMD, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_adma_request_alloc(काष्ठा tegra_adma_chan *tdc,
				    क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा tegra_adma *tdma = tdc->tdma;
	अचिन्हित पूर्णांक sreq_index = tdc->sreq_index;

	अगर (tdc->sreq_reserved)
		वापस tdc->sreq_dir == direction ? 0 : -EINVAL;

	अगर (sreq_index > tdma->cdata->ch_req_max) अणु
		dev_err(tdma->dev, "invalid DMA request\n");
		वापस -EINVAL;
	पूर्ण

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		अगर (test_and_set_bit(sreq_index, &tdma->tx_requests_reserved)) अणु
			dev_err(tdma->dev, "DMA request reserved\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		अगर (test_and_set_bit(sreq_index, &tdma->rx_requests_reserved)) अणु
			dev_err(tdma->dev, "DMA request reserved\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		dev_WARN(tdma->dev, "channel %s has invalid transfer type\n",
			 dma_chan_name(&tdc->vc.chan));
		वापस -EINVAL;
	पूर्ण

	tdc->sreq_dir = direction;
	tdc->sreq_reserved = true;

	वापस 0;
पूर्ण

अटल व्योम tegra_adma_request_मुक्त(काष्ठा tegra_adma_chan *tdc)
अणु
	काष्ठा tegra_adma *tdma = tdc->tdma;

	अगर (!tdc->sreq_reserved)
		वापस;

	चयन (tdc->sreq_dir) अणु
	हाल DMA_MEM_TO_DEV:
		clear_bit(tdc->sreq_index, &tdma->tx_requests_reserved);
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		clear_bit(tdc->sreq_index, &tdma->rx_requests_reserved);
		अवरोध;

	शेष:
		dev_WARN(tdma->dev, "channel %s has invalid transfer type\n",
			 dma_chan_name(&tdc->vc.chan));
		वापस;
	पूर्ण

	tdc->sreq_reserved = false;
पूर्ण

अटल u32 tegra_adma_irq_status(काष्ठा tegra_adma_chan *tdc)
अणु
	u32 status = tdma_ch_पढ़ो(tdc, ADMA_CH_INT_STATUS);

	वापस status & ADMA_CH_INT_STATUS_XFER_DONE;
पूर्ण

अटल u32 tegra_adma_irq_clear(काष्ठा tegra_adma_chan *tdc)
अणु
	u32 status = tegra_adma_irq_status(tdc);

	अगर (status)
		tdma_ch_ग_लिखो(tdc, ADMA_CH_INT_CLEAR, status);

	वापस status;
पूर्ण

अटल व्योम tegra_adma_stop(काष्ठा tegra_adma_chan *tdc)
अणु
	अचिन्हित पूर्णांक status;

	/* Disable ADMA */
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CMD, 0);

	/* Clear पूर्णांकerrupt status */
	tegra_adma_irq_clear(tdc);

	अगर (पढ़ोx_poll_समयout_atomic(पढ़ोl, tdc->chan_addr + ADMA_CH_STATUS,
			status, !(status & ADMA_CH_STATUS_XFER_EN),
			20, 10000)) अणु
		dev_err(tdc2dev(tdc), "unable to stop DMA channel\n");
		वापस;
	पूर्ण

	kमुक्त(tdc->desc);
	tdc->desc = शून्य;
पूर्ण

अटल व्योम tegra_adma_start(काष्ठा tegra_adma_chan *tdc)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&tdc->vc);
	काष्ठा tegra_adma_chan_regs *ch_regs;
	काष्ठा tegra_adma_desc *desc;

	अगर (!vd)
		वापस;

	list_del(&vd->node);

	desc = to_tegra_adma_desc(&vd->tx);

	अगर (!desc) अणु
		dev_warn(tdc2dev(tdc), "unable to start DMA, no descriptor\n");
		वापस;
	पूर्ण

	ch_regs = &desc->ch_regs;

	tdc->tx_buf_pos = 0;
	tdc->tx_buf_count = 0;
	tdma_ch_ग_लिखो(tdc, ADMA_CH_TC, ch_regs->tc);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CTRL, ch_regs->ctrl);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_LOWER_SRC_ADDR, ch_regs->src_addr);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_LOWER_TRG_ADDR, ch_regs->trg_addr);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_FIFO_CTRL, ch_regs->fअगरo_ctrl);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CONFIG, ch_regs->config);

	/* Start ADMA */
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CMD, 1);

	tdc->desc = desc;
पूर्ण

अटल अचिन्हित पूर्णांक tegra_adma_get_residue(काष्ठा tegra_adma_chan *tdc)
अणु
	काष्ठा tegra_adma_desc *desc = tdc->desc;
	अचिन्हित पूर्णांक max = ADMA_CH_XFER_STATUS_COUNT_MASK + 1;
	अचिन्हित पूर्णांक pos = tdma_ch_पढ़ो(tdc, ADMA_CH_XFER_STATUS);
	अचिन्हित पूर्णांक periods_reमुख्यing;

	/*
	 * Handle wrap around of buffer count रेजिस्टर
	 */
	अगर (pos < tdc->tx_buf_pos)
		tdc->tx_buf_count += pos + (max - tdc->tx_buf_pos);
	अन्यथा
		tdc->tx_buf_count += pos - tdc->tx_buf_pos;

	periods_reमुख्यing = tdc->tx_buf_count % desc->num_periods;
	tdc->tx_buf_pos = pos;

	वापस desc->buf_len - (periods_reमुख्यing * desc->period_len);
पूर्ण

अटल irqवापस_t tegra_adma_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tegra_adma_chan *tdc = dev_id;
	अचिन्हित दीर्घ status;

	spin_lock(&tdc->vc.lock);

	status = tegra_adma_irq_clear(tdc);
	अगर (status == 0 || !tdc->desc) अणु
		spin_unlock(&tdc->vc.lock);
		वापस IRQ_NONE;
	पूर्ण

	vchan_cyclic_callback(&tdc->desc->vd);

	spin_unlock(&tdc->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_adma_issue_pending(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdc->vc.lock, flags);

	अगर (vchan_issue_pending(&tdc->vc)) अणु
		अगर (!tdc->desc)
			tegra_adma_start(tdc);
	पूर्ण

	spin_unlock_irqrestore(&tdc->vc.lock, flags);
पूर्ण

अटल bool tegra_adma_is_छोड़ोd(काष्ठा tegra_adma_chan *tdc)
अणु
	u32 csts;

	csts = tdma_ch_पढ़ो(tdc, ADMA_CH_STATUS);
	csts &= ADMA_CH_STATUS_XFER_PAUSED;

	वापस csts ? true : false;
पूर्ण

अटल पूर्णांक tegra_adma_छोड़ो(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	काष्ठा tegra_adma_desc *desc = tdc->desc;
	काष्ठा tegra_adma_chan_regs *ch_regs = &desc->ch_regs;
	पूर्णांक dcnt = 10;

	ch_regs->ctrl = tdma_ch_पढ़ो(tdc, ADMA_CH_CTRL);
	ch_regs->ctrl |= (1 << ADMA_CH_CTRL_XFER_PAUSE_SHIFT);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CTRL, ch_regs->ctrl);

	जबतक (dcnt-- && !tegra_adma_is_छोड़ोd(tdc))
		udelay(TEGRA_ADMA_BURST_COMPLETE_TIME);

	अगर (dcnt < 0) अणु
		dev_err(tdc2dev(tdc), "unable to pause DMA channel\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_adma_resume(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	काष्ठा tegra_adma_desc *desc = tdc->desc;
	काष्ठा tegra_adma_chan_regs *ch_regs = &desc->ch_regs;

	ch_regs->ctrl = tdma_ch_पढ़ो(tdc, ADMA_CH_CTRL);
	ch_regs->ctrl &= ~(1 << ADMA_CH_CTRL_XFER_PAUSE_SHIFT);
	tdma_ch_ग_लिखो(tdc, ADMA_CH_CTRL, ch_regs->ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_adma_terminate_all(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&tdc->vc.lock, flags);

	अगर (tdc->desc)
		tegra_adma_stop(tdc);

	tegra_adma_request_मुक्त(tdc);
	vchan_get_all_descriptors(&tdc->vc, &head);
	spin_unlock_irqrestore(&tdc->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&tdc->vc, &head);

	वापस 0;
पूर्ण

अटल क्रमागत dma_status tegra_adma_tx_status(काष्ठा dma_chan *dc,
					    dma_cookie_t cookie,
					    काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	काष्ठा tegra_adma_desc *desc;
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक residual;

	ret = dma_cookie_status(dc, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&tdc->vc.lock, flags);

	vd = vchan_find_desc(&tdc->vc, cookie);
	अगर (vd) अणु
		desc = to_tegra_adma_desc(&vd->tx);
		residual = desc->ch_regs.tc;
	पूर्ण अन्यथा अगर (tdc->desc && tdc->desc->vd.tx.cookie == cookie) अणु
		residual = tegra_adma_get_residue(tdc);
	पूर्ण अन्यथा अणु
		residual = 0;
	पूर्ण

	spin_unlock_irqrestore(&tdc->vc.lock, flags);

	dma_set_residue(txstate, residual);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक tegra210_adma_get_burst_config(अचिन्हित पूर्णांक burst_size)
अणु
	अगर (!burst_size || burst_size > ADMA_CH_CONFIG_MAX_BURST_SIZE)
		burst_size = ADMA_CH_CONFIG_MAX_BURST_SIZE;

	वापस fls(burst_size) << ADMA_CH_CONFIG_BURST_SIZE_SHIFT;
पूर्ण

अटल अचिन्हित पूर्णांक tegra186_adma_get_burst_config(अचिन्हित पूर्णांक burst_size)
अणु
	अगर (!burst_size || burst_size > ADMA_CH_CONFIG_MAX_BURST_SIZE)
		burst_size = ADMA_CH_CONFIG_MAX_BURST_SIZE;

	वापस (burst_size - 1) << ADMA_CH_CONFIG_BURST_SIZE_SHIFT;
पूर्ण

अटल पूर्णांक tegra_adma_set_xfer_params(काष्ठा tegra_adma_chan *tdc,
				      काष्ठा tegra_adma_desc *desc,
				      dma_addr_t buf_addr,
				      क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा tegra_adma_chan_regs *ch_regs = &desc->ch_regs;
	स्थिर काष्ठा tegra_adma_chip_data *cdata = tdc->tdma->cdata;
	अचिन्हित पूर्णांक burst_size, adma_dir;

	अगर (desc->num_periods > ADMA_CH_CONFIG_MAX_BUFS)
		वापस -EINVAL;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		adma_dir = ADMA_CH_CTRL_सूची_MEM2AHUB;
		burst_size = tdc->sconfig.dst_maxburst;
		ch_regs->config = ADMA_CH_CONFIG_SRC_BUF(desc->num_periods - 1);
		ch_regs->ctrl = ADMA_CH_REG_FIELD_VAL(tdc->sreq_index,
						      cdata->ch_req_mask,
						      cdata->ch_req_tx_shअगरt);
		ch_regs->src_addr = buf_addr;
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		adma_dir = ADMA_CH_CTRL_सूची_AHUB2MEM;
		burst_size = tdc->sconfig.src_maxburst;
		ch_regs->config = ADMA_CH_CONFIG_TRG_BUF(desc->num_periods - 1);
		ch_regs->ctrl = ADMA_CH_REG_FIELD_VAL(tdc->sreq_index,
						      cdata->ch_req_mask,
						      cdata->ch_req_rx_shअगरt);
		ch_regs->trg_addr = buf_addr;
		अवरोध;

	शेष:
		dev_err(tdc2dev(tdc), "DMA direction is not supported\n");
		वापस -EINVAL;
	पूर्ण

	ch_regs->ctrl |= ADMA_CH_CTRL_सूची(adma_dir) |
			 ADMA_CH_CTRL_MODE_CONTINUOUS |
			 ADMA_CH_CTRL_FLOWCTRL_EN;
	ch_regs->config |= cdata->adma_get_burst_config(burst_size);
	ch_regs->config |= ADMA_CH_CONFIG_WEIGHT_FOR_WRR(1);
	अगर (cdata->has_outstanding_reqs)
		ch_regs->config |= TEGRA186_ADMA_CH_CONFIG_OUTSTANDING_REQS(8);
	ch_regs->fअगरo_ctrl = cdata->ch_fअगरo_ctrl;
	ch_regs->tc = desc->period_len & ADMA_CH_TC_COUNT_MASK;

	वापस tegra_adma_request_alloc(tdc, direction);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *tegra_adma_prep_dma_cyclic(
	काष्ठा dma_chan *dc, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	काष्ठा tegra_adma_desc *desc = शून्य;

	अगर (!buf_len || !period_len || period_len > ADMA_CH_TC_COUNT_MASK) अणु
		dev_err(tdc2dev(tdc), "invalid buffer/period len\n");
		वापस शून्य;
	पूर्ण

	अगर (buf_len % period_len) अणु
		dev_err(tdc2dev(tdc), "buf_len not a multiple of period_len\n");
		वापस शून्य;
	पूर्ण

	अगर (!IS_ALIGNED(buf_addr, 4)) अणु
		dev_err(tdc2dev(tdc), "invalid buffer alignment\n");
		वापस शून्य;
	पूर्ण

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->buf_len = buf_len;
	desc->period_len = period_len;
	desc->num_periods = buf_len / period_len;

	अगर (tegra_adma_set_xfer_params(tdc, desc, buf_addr, direction)) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	वापस vchan_tx_prep(&tdc->vc, &desc->vd, flags);
पूर्ण

अटल पूर्णांक tegra_adma_alloc_chan_resources(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	पूर्णांक ret;

	ret = request_irq(tdc->irq, tegra_adma_isr, 0, dma_chan_name(dc), tdc);
	अगर (ret) अणु
		dev_err(tdc2dev(tdc), "failed to get interrupt for %s\n",
			dma_chan_name(dc));
		वापस ret;
	पूर्ण

	ret = pm_runसमय_get_sync(tdc2dev(tdc));
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(tdc2dev(tdc));
		मुक्त_irq(tdc->irq, tdc);
		वापस ret;
	पूर्ण

	dma_cookie_init(&tdc->vc.chan);

	वापस 0;
पूर्ण

अटल व्योम tegra_adma_मुक्त_chan_resources(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_adma_chan *tdc = to_tegra_adma_chan(dc);

	tegra_adma_terminate_all(dc);
	vchan_मुक्त_chan_resources(&tdc->vc);
	tasklet_समाप्त(&tdc->vc.task);
	मुक्त_irq(tdc->irq, tdc);
	pm_runसमय_put(tdc2dev(tdc));

	tdc->sreq_index = 0;
	tdc->sreq_dir = DMA_TRANS_NONE;
पूर्ण

अटल काष्ठा dma_chan *tegra_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा tegra_adma *tdma = ofdma->of_dma_data;
	काष्ठा tegra_adma_chan *tdc;
	काष्ठा dma_chan *chan;
	अचिन्हित पूर्णांक sreq_index;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	sreq_index = dma_spec->args[0];

	अगर (sreq_index == 0) अणु
		dev_err(tdma->dev, "DMA request must not be 0\n");
		वापस शून्य;
	पूर्ण

	chan = dma_get_any_slave_channel(&tdma->dma_dev);
	अगर (!chan)
		वापस शून्य;

	tdc = to_tegra_adma_chan(chan);
	tdc->sreq_index = sreq_index;

	वापस chan;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_adma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_adma *tdma = dev_get_drvdata(dev);
	काष्ठा tegra_adma_chan_regs *ch_reg;
	काष्ठा tegra_adma_chan *tdc;
	पूर्णांक i;

	tdma->global_cmd = tdma_पढ़ो(tdma, ADMA_GLOBAL_CMD);
	अगर (!tdma->global_cmd)
		जाओ clk_disable;

	क्रम (i = 0; i < tdma->nr_channels; i++) अणु
		tdc = &tdma->channels[i];
		ch_reg = &tdc->ch_regs;
		ch_reg->cmd = tdma_ch_पढ़ो(tdc, ADMA_CH_CMD);
		/* skip अगर channel is not active */
		अगर (!ch_reg->cmd)
			जारी;
		ch_reg->tc = tdma_ch_पढ़ो(tdc, ADMA_CH_TC);
		ch_reg->src_addr = tdma_ch_पढ़ो(tdc, ADMA_CH_LOWER_SRC_ADDR);
		ch_reg->trg_addr = tdma_ch_पढ़ो(tdc, ADMA_CH_LOWER_TRG_ADDR);
		ch_reg->ctrl = tdma_ch_पढ़ो(tdc, ADMA_CH_CTRL);
		ch_reg->fअगरo_ctrl = tdma_ch_पढ़ो(tdc, ADMA_CH_FIFO_CTRL);
		ch_reg->config = tdma_ch_पढ़ो(tdc, ADMA_CH_CONFIG);
	पूर्ण

clk_disable:
	clk_disable_unprepare(tdma->ahub_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_adma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_adma *tdma = dev_get_drvdata(dev);
	काष्ठा tegra_adma_chan_regs *ch_reg;
	काष्ठा tegra_adma_chan *tdc;
	पूर्णांक ret, i;

	ret = clk_prepare_enable(tdma->ahub_clk);
	अगर (ret) अणु
		dev_err(dev, "ahub clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण
	tdma_ग_लिखो(tdma, ADMA_GLOBAL_CMD, tdma->global_cmd);

	अगर (!tdma->global_cmd)
		वापस 0;

	क्रम (i = 0; i < tdma->nr_channels; i++) अणु
		tdc = &tdma->channels[i];
		ch_reg = &tdc->ch_regs;
		/* skip अगर channel was not active earlier */
		अगर (!ch_reg->cmd)
			जारी;
		tdma_ch_ग_लिखो(tdc, ADMA_CH_TC, ch_reg->tc);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_LOWER_SRC_ADDR, ch_reg->src_addr);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_LOWER_TRG_ADDR, ch_reg->trg_addr);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_CTRL, ch_reg->ctrl);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_FIFO_CTRL, ch_reg->fअगरo_ctrl);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_CONFIG, ch_reg->config);
		tdma_ch_ग_लिखो(tdc, ADMA_CH_CMD, ch_reg->cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_adma_chip_data tegra210_chip_data = अणु
	.adma_get_burst_config  = tegra210_adma_get_burst_config,
	.global_reg_offset	= 0xc00,
	.global_पूर्णांक_clear	= 0x20,
	.ch_req_tx_shअगरt	= 28,
	.ch_req_rx_shअगरt	= 24,
	.ch_base_offset		= 0,
	.has_outstanding_reqs	= false,
	.ch_fअगरo_ctrl		= TEGRA210_FIFO_CTRL_DEFAULT,
	.ch_req_mask		= 0xf,
	.ch_req_max		= 10,
	.ch_reg_size		= 0x80,
	.nr_channels		= 22,
पूर्ण;

अटल स्थिर काष्ठा tegra_adma_chip_data tegra186_chip_data = अणु
	.adma_get_burst_config  = tegra186_adma_get_burst_config,
	.global_reg_offset	= 0,
	.global_पूर्णांक_clear	= 0x402c,
	.ch_req_tx_shअगरt	= 27,
	.ch_req_rx_shअगरt	= 22,
	.ch_base_offset		= 0x10000,
	.has_outstanding_reqs	= true,
	.ch_fअगरo_ctrl		= TEGRA186_FIFO_CTRL_DEFAULT,
	.ch_req_mask		= 0x1f,
	.ch_req_max		= 20,
	.ch_reg_size		= 0x100,
	.nr_channels		= 32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_adma_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-adma", .data = &tegra210_chip_data पूर्ण,
	अणु .compatible = "nvidia,tegra186-adma", .data = &tegra186_chip_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_adma_of_match);

अटल पूर्णांक tegra_adma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा tegra_adma_chip_data *cdata;
	काष्ठा tegra_adma *tdma;
	काष्ठा resource	*res;
	पूर्णांक ret, i;

	cdata = of_device_get_match_data(&pdev->dev);
	अगर (!cdata) अणु
		dev_err(&pdev->dev, "device match data not found\n");
		वापस -ENODEV;
	पूर्ण

	tdma = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(tdma, channels, cdata->nr_channels),
			    GFP_KERNEL);
	अगर (!tdma)
		वापस -ENOMEM;

	tdma->dev = &pdev->dev;
	tdma->cdata = cdata;
	tdma->nr_channels = cdata->nr_channels;
	platक्रमm_set_drvdata(pdev, tdma);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tdma->base_addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(tdma->base_addr))
		वापस PTR_ERR(tdma->base_addr);

	tdma->ahub_clk = devm_clk_get(&pdev->dev, "d_audio");
	अगर (IS_ERR(tdma->ahub_clk)) अणु
		dev_err(&pdev->dev, "Error: Missing ahub controller clock\n");
		वापस PTR_ERR(tdma->ahub_clk);
	पूर्ण

	INIT_LIST_HEAD(&tdma->dma_dev.channels);
	क्रम (i = 0; i < tdma->nr_channels; i++) अणु
		काष्ठा tegra_adma_chan *tdc = &tdma->channels[i];

		tdc->chan_addr = tdma->base_addr + cdata->ch_base_offset
				 + (cdata->ch_reg_size * i);

		tdc->irq = of_irq_get(pdev->dev.of_node, i);
		अगर (tdc->irq <= 0) अणु
			ret = tdc->irq ?: -ENXIO;
			जाओ irq_dispose;
		पूर्ण

		vchan_init(&tdc->vc, &tdma->dma_dev);
		tdc->vc.desc_मुक्त = tegra_adma_desc_मुक्त;
		tdc->tdma = tdma;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ rpm_disable;
	पूर्ण

	ret = tegra_adma_init(tdma);
	अगर (ret)
		जाओ rpm_put;

	dma_cap_set(DMA_SLAVE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PRIVATE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, tdma->dma_dev.cap_mask);

	tdma->dma_dev.dev = &pdev->dev;
	tdma->dma_dev.device_alloc_chan_resources =
					tegra_adma_alloc_chan_resources;
	tdma->dma_dev.device_मुक्त_chan_resources =
					tegra_adma_मुक्त_chan_resources;
	tdma->dma_dev.device_issue_pending = tegra_adma_issue_pending;
	tdma->dma_dev.device_prep_dma_cyclic = tegra_adma_prep_dma_cyclic;
	tdma->dma_dev.device_config = tegra_adma_slave_config;
	tdma->dma_dev.device_tx_status = tegra_adma_tx_status;
	tdma->dma_dev.device_terminate_all = tegra_adma_terminate_all;
	tdma->dma_dev.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	tdma->dma_dev.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	tdma->dma_dev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	tdma->dma_dev.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	tdma->dma_dev.device_छोड़ो = tegra_adma_छोड़ो;
	tdma->dma_dev.device_resume = tegra_adma_resume;

	ret = dma_async_device_रेजिस्टर(&tdma->dma_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "ADMA registration failed: %d\n", ret);
		जाओ rpm_put;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 tegra_dma_of_xlate, tdma);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "ADMA OF registration failed %d\n", ret);
		जाओ dma_हटाओ;
	पूर्ण

	pm_runसमय_put(&pdev->dev);

	dev_info(&pdev->dev, "Tegra210 ADMA driver registered %d channels\n",
		 tdma->nr_channels);

	वापस 0;

dma_हटाओ:
	dma_async_device_unरेजिस्टर(&tdma->dma_dev);
rpm_put:
	pm_runसमय_put_sync(&pdev->dev);
rpm_disable:
	pm_runसमय_disable(&pdev->dev);
irq_dispose:
	जबतक (--i >= 0)
		irq_dispose_mapping(tdma->channels[i].irq);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_adma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_adma *tdma = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&tdma->dma_dev);

	क्रम (i = 0; i < tdma->nr_channels; ++i)
		irq_dispose_mapping(tdma->channels[i].irq);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_adma_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_adma_runसमय_suspend,
			   tegra_adma_runसमय_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_admac_driver = अणु
	.driver = अणु
		.name	= "tegra-adma",
		.pm	= &tegra_adma_dev_pm_ops,
		.of_match_table = tegra_adma_of_match,
	पूर्ण,
	.probe		= tegra_adma_probe,
	.हटाओ		= tegra_adma_हटाओ,
पूर्ण;

module_platक्रमm_driver(tegra_admac_driver);

MODULE_ALIAS("platform:tegra210-adma");
MODULE_DESCRIPTION("NVIDIA Tegra ADMA driver");
MODULE_AUTHOR("Dara Ramesh <dramesh@nvidia.com>");
MODULE_AUTHOR("Jon Hunter <jonathanh@nvidia.com>");
MODULE_LICENSE("GPL v2");
