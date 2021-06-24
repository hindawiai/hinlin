<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Luकरोvic Barre <luकरोvic.barre@st.com> क्रम STMicroelectronics.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spi/spi-स्मृति.स>

#घोषणा QSPI_CR			0x00
#घोषणा CR_EN			BIT(0)
#घोषणा CR_ABORT		BIT(1)
#घोषणा CR_DMAEN		BIT(2)
#घोषणा CR_TCEN			BIT(3)
#घोषणा CR_SSHIFT		BIT(4)
#घोषणा CR_DFM			BIT(6)
#घोषणा CR_FSEL			BIT(7)
#घोषणा CR_FTHRES_SHIFT		8
#घोषणा CR_TEIE			BIT(16)
#घोषणा CR_TCIE			BIT(17)
#घोषणा CR_FTIE			BIT(18)
#घोषणा CR_SMIE			BIT(19)
#घोषणा CR_TOIE			BIT(20)
#घोषणा CR_PRESC_MASK		GENMASK(31, 24)

#घोषणा QSPI_DCR		0x04
#घोषणा DCR_FSIZE_MASK		GENMASK(20, 16)

#घोषणा QSPI_SR			0x08
#घोषणा SR_TEF			BIT(0)
#घोषणा SR_TCF			BIT(1)
#घोषणा SR_FTF			BIT(2)
#घोषणा SR_SMF			BIT(3)
#घोषणा SR_TOF			BIT(4)
#घोषणा SR_BUSY			BIT(5)
#घोषणा SR_FLEVEL_MASK		GENMASK(13, 8)

#घोषणा QSPI_FCR		0x0c
#घोषणा FCR_CTEF		BIT(0)
#घोषणा FCR_CTCF		BIT(1)

#घोषणा QSPI_DLR		0x10

#घोषणा QSPI_CCR		0x14
#घोषणा CCR_INST_MASK		GENMASK(7, 0)
#घोषणा CCR_IMODE_MASK		GENMASK(9, 8)
#घोषणा CCR_ADMODE_MASK		GENMASK(11, 10)
#घोषणा CCR_ADSIZE_MASK		GENMASK(13, 12)
#घोषणा CCR_DCYC_MASK		GENMASK(22, 18)
#घोषणा CCR_DMODE_MASK		GENMASK(25, 24)
#घोषणा CCR_FMODE_MASK		GENMASK(27, 26)
#घोषणा CCR_FMODE_INDW		(0U << 26)
#घोषणा CCR_FMODE_INDR		(1U << 26)
#घोषणा CCR_FMODE_APM		(2U << 26)
#घोषणा CCR_FMODE_MM		(3U << 26)
#घोषणा CCR_BUSWIDTH_0		0x0
#घोषणा CCR_BUSWIDTH_1		0x1
#घोषणा CCR_BUSWIDTH_2		0x2
#घोषणा CCR_BUSWIDTH_4		0x3

#घोषणा QSPI_AR			0x18
#घोषणा QSPI_ABR		0x1c
#घोषणा QSPI_DR			0x20
#घोषणा QSPI_PSMKR		0x24
#घोषणा QSPI_PSMAR		0x28
#घोषणा QSPI_PIR		0x2c
#घोषणा QSPI_LPTR		0x30

#घोषणा STM32_QSPI_MAX_MMAP_SZ	SZ_256M
#घोषणा STM32_QSPI_MAX_NORCHIP	2

#घोषणा STM32_FIFO_TIMEOUT_US 30000
#घोषणा STM32_BUSY_TIMEOUT_US 100000
#घोषणा STM32_ABT_TIMEOUT_US 100000
#घोषणा STM32_COMP_TIMEOUT_MS 1000
#घोषणा STM32_AUTOSUSPEND_DELAY -1

काष्ठा sपंचांग32_qspi_flash अणु
	काष्ठा sपंचांग32_qspi *qspi;
	u32 cs;
	u32 presc;
पूर्ण;

काष्ठा sपंचांग32_qspi अणु
	काष्ठा device *dev;
	काष्ठा spi_controller *ctrl;
	phys_addr_t phys_base;
	व्योम __iomem *io_base;
	व्योम __iomem *mm_base;
	resource_माप_प्रकार mm_size;
	काष्ठा clk *clk;
	u32 clk_rate;
	काष्ठा sपंचांग32_qspi_flash flash[STM32_QSPI_MAX_NORCHIP];
	काष्ठा completion data_completion;
	u32 भ_शेषe;

	काष्ठा dma_chan *dma_chtx;
	काष्ठा dma_chan *dma_chrx;
	काष्ठा completion dma_completion;

	u32 cr_reg;
	u32 dcr_reg;

	/*
	 * to protect device configuration, could be dअगरferent between
	 * 2 flash access (bk1, bk2)
	 */
	काष्ठा mutex lock;
पूर्ण;

अटल irqवापस_t sपंचांग32_qspi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांग32_qspi *qspi = (काष्ठा sपंचांग32_qspi *)dev_id;
	u32 cr, sr;

	sr = पढ़ोl_relaxed(qspi->io_base + QSPI_SR);

	अगर (sr & (SR_TEF | SR_TCF)) अणु
		/* disable irq */
		cr = पढ़ोl_relaxed(qspi->io_base + QSPI_CR);
		cr &= ~CR_TCIE & ~CR_TEIE;
		ग_लिखोl_relaxed(cr, qspi->io_base + QSPI_CR);
		complete(&qspi->data_completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांग32_qspi_पढ़ो_fअगरo(u8 *val, व्योम __iomem *addr)
अणु
	*val = पढ़ोb_relaxed(addr);
पूर्ण

अटल व्योम sपंचांग32_qspi_ग_लिखो_fअगरo(u8 *val, व्योम __iomem *addr)
अणु
	ग_लिखोb_relaxed(*val, addr);
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_tx_poll(काष्ठा sपंचांग32_qspi *qspi,
			      स्थिर काष्ठा spi_mem_op *op)
अणु
	व्योम (*tx_fअगरo)(u8 *val, व्योम __iomem *addr);
	u32 len = op->data.nbytes, sr;
	u8 *buf;
	पूर्णांक ret;

	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		tx_fअगरo = sपंचांग32_qspi_पढ़ो_fअगरo;
		buf = op->data.buf.in;

	पूर्ण अन्यथा अणु
		tx_fअगरo = sपंचांग32_qspi_ग_लिखो_fअगरo;
		buf = (u8 *)op->data.buf.out;
	पूर्ण

	जबतक (len--) अणु
		ret = पढ़ोl_relaxed_poll_समयout_atomic(qspi->io_base + QSPI_SR,
							sr, (sr & SR_FTF), 1,
							STM32_FIFO_TIMEOUT_US);
		अगर (ret) अणु
			dev_err(qspi->dev, "fifo timeout (len:%d stat:%#x)\n",
				len, sr);
			वापस ret;
		पूर्ण
		tx_fअगरo(buf++, qspi->io_base + QSPI_DR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_tx_mm(काष्ठा sपंचांग32_qspi *qspi,
			    स्थिर काष्ठा spi_mem_op *op)
अणु
	स_नकल_fromio(op->data.buf.in, qspi->mm_base + op->addr.val,
		      op->data.nbytes);
	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_qspi_dma_callback(व्योम *arg)
अणु
	काष्ठा completion *dma_completion = arg;

	complete(dma_completion);
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_tx_dma(काष्ठा sपंचांग32_qspi *qspi,
			     स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	क्रमागत dma_transfer_direction dma_dir;
	काष्ठा dma_chan *dma_ch;
	काष्ठा sg_table sgt;
	dma_cookie_t cookie;
	u32 cr, t_out;
	पूर्णांक err;

	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		dma_dir = DMA_DEV_TO_MEM;
		dma_ch = qspi->dma_chrx;
	पूर्ण अन्यथा अणु
		dma_dir = DMA_MEM_TO_DEV;
		dma_ch = qspi->dma_chtx;
	पूर्ण

	/*
	 * spi_map_buf वापस -EINVAL अगर the buffer is not DMA-able
	 * (DMA-able: in vदो_स्मृति | kmap | virt_addr_valid)
	 */
	err = spi_controller_dma_map_mem_op_data(qspi->ctrl, op, &sgt);
	अगर (err)
		वापस err;

	desc = dmaengine_prep_slave_sg(dma_ch, sgt.sgl, sgt.nents,
				       dma_dir, DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		err = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	cr = पढ़ोl_relaxed(qspi->io_base + QSPI_CR);

	reinit_completion(&qspi->dma_completion);
	desc->callback = sपंचांग32_qspi_dma_callback;
	desc->callback_param = &qspi->dma_completion;
	cookie = dmaengine_submit(desc);
	err = dma_submit_error(cookie);
	अगर (err)
		जाओ out;

	dma_async_issue_pending(dma_ch);

	ग_लिखोl_relaxed(cr | CR_DMAEN, qspi->io_base + QSPI_CR);

	t_out = sgt.nents * STM32_COMP_TIMEOUT_MS;
	अगर (!रुको_क्रम_completion_समयout(&qspi->dma_completion,
					 msecs_to_jअगरfies(t_out)))
		err = -ETIMEDOUT;

	अगर (err)
		dmaengine_terminate_all(dma_ch);

out:
	ग_लिखोl_relaxed(cr & ~CR_DMAEN, qspi->io_base + QSPI_CR);
out_unmap:
	spi_controller_dma_unmap_mem_op_data(qspi->ctrl, op, &sgt);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_tx(काष्ठा sपंचांग32_qspi *qspi, स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (!op->data.nbytes)
		वापस 0;

	अगर (qspi->भ_शेषe == CCR_FMODE_MM)
		वापस sपंचांग32_qspi_tx_mm(qspi, op);
	अन्यथा अगर (((op->data.dir == SPI_MEM_DATA_IN && qspi->dma_chrx) ||
		 (op->data.dir == SPI_MEM_DATA_OUT && qspi->dma_chtx)) &&
		  op->data.nbytes > 4)
		अगर (!sपंचांग32_qspi_tx_dma(qspi, op))
			वापस 0;

	वापस sपंचांग32_qspi_tx_poll(qspi, op);
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_रुको_nobusy(काष्ठा sपंचांग32_qspi *qspi)
अणु
	u32 sr;

	वापस पढ़ोl_relaxed_poll_समयout_atomic(qspi->io_base + QSPI_SR, sr,
						 !(sr & SR_BUSY), 1,
						 STM32_BUSY_TIMEOUT_US);
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_रुको_cmd(काष्ठा sपंचांग32_qspi *qspi,
			       स्थिर काष्ठा spi_mem_op *op)
अणु
	u32 cr, sr;
	पूर्णांक err = 0;

	अगर (!op->data.nbytes)
		जाओ रुको_nobusy;

	अगर (पढ़ोl_relaxed(qspi->io_base + QSPI_SR) & SR_TCF)
		जाओ out;

	reinit_completion(&qspi->data_completion);
	cr = पढ़ोl_relaxed(qspi->io_base + QSPI_CR);
	ग_लिखोl_relaxed(cr | CR_TCIE | CR_TEIE, qspi->io_base + QSPI_CR);

	अगर (!रुको_क्रम_completion_समयout(&qspi->data_completion,
				msecs_to_jअगरfies(STM32_COMP_TIMEOUT_MS))) अणु
		err = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		sr = पढ़ोl_relaxed(qspi->io_base + QSPI_SR);
		अगर (sr & SR_TEF)
			err = -EIO;
	पूर्ण

out:
	/* clear flags */
	ग_लिखोl_relaxed(FCR_CTCF | FCR_CTEF, qspi->io_base + QSPI_FCR);
रुको_nobusy:
	अगर (!err)
		err = sपंचांग32_qspi_रुको_nobusy(qspi);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_get_mode(काष्ठा sपंचांग32_qspi *qspi, u8 buswidth)
अणु
	अगर (buswidth == 4)
		वापस CCR_BUSWIDTH_4;

	वापस buswidth;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_send(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा sपंचांग32_qspi *qspi = spi_controller_get_devdata(mem->spi->master);
	काष्ठा sपंचांग32_qspi_flash *flash = &qspi->flash[mem->spi->chip_select];
	u32 ccr, cr;
	पूर्णांक समयout, err = 0;

	dev_dbg(qspi->dev, "cmd:%#x mode:%d.%d.%d.%d addr:%#llx len:%#x\n",
		op->cmd.opcode, op->cmd.buswidth, op->addr.buswidth,
		op->dummy.buswidth, op->data.buswidth,
		op->addr.val, op->data.nbytes);

	err = sपंचांग32_qspi_रुको_nobusy(qspi);
	अगर (err)
		जाओ पात;

	cr = पढ़ोl_relaxed(qspi->io_base + QSPI_CR);
	cr &= ~CR_PRESC_MASK & ~CR_FSEL;
	cr |= FIELD_PREP(CR_PRESC_MASK, flash->presc);
	cr |= FIELD_PREP(CR_FSEL, flash->cs);
	ग_लिखोl_relaxed(cr, qspi->io_base + QSPI_CR);

	अगर (op->data.nbytes)
		ग_लिखोl_relaxed(op->data.nbytes - 1,
			       qspi->io_base + QSPI_DLR);

	ccr = qspi->भ_शेषe;
	ccr |= FIELD_PREP(CCR_INST_MASK, op->cmd.opcode);
	ccr |= FIELD_PREP(CCR_IMODE_MASK,
			  sपंचांग32_qspi_get_mode(qspi, op->cmd.buswidth));

	अगर (op->addr.nbytes) अणु
		ccr |= FIELD_PREP(CCR_ADMODE_MASK,
				  sपंचांग32_qspi_get_mode(qspi, op->addr.buswidth));
		ccr |= FIELD_PREP(CCR_ADSIZE_MASK, op->addr.nbytes - 1);
	पूर्ण

	अगर (op->dummy.buswidth && op->dummy.nbytes)
		ccr |= FIELD_PREP(CCR_DCYC_MASK,
				  op->dummy.nbytes * 8 / op->dummy.buswidth);

	अगर (op->data.nbytes) अणु
		ccr |= FIELD_PREP(CCR_DMODE_MASK,
				  sपंचांग32_qspi_get_mode(qspi, op->data.buswidth));
	पूर्ण

	ग_लिखोl_relaxed(ccr, qspi->io_base + QSPI_CCR);

	अगर (op->addr.nbytes && qspi->भ_शेषe != CCR_FMODE_MM)
		ग_लिखोl_relaxed(op->addr.val, qspi->io_base + QSPI_AR);

	err = sपंचांग32_qspi_tx(qspi, op);

	/*
	 * Abort in:
	 * -error हाल
	 * -पढ़ो memory map: prefetching must be stopped अगर we पढ़ो the last
	 *  byte of device (device size - fअगरo size). like device size is not
	 *  knows, the prefetching is always stop.
	 */
	अगर (err || qspi->भ_शेषe == CCR_FMODE_MM)
		जाओ पात;

	/* रुको end of tx in indirect mode */
	err = sपंचांग32_qspi_रुको_cmd(qspi, op);
	अगर (err)
		जाओ पात;

	वापस 0;

पात:
	cr = पढ़ोl_relaxed(qspi->io_base + QSPI_CR) | CR_ABORT;
	ग_लिखोl_relaxed(cr, qspi->io_base + QSPI_CR);

	/* रुको clear of पात bit by hw */
	समयout = पढ़ोl_relaxed_poll_समयout_atomic(qspi->io_base + QSPI_CR,
						    cr, !(cr & CR_ABORT), 1,
						    STM32_ABT_TIMEOUT_US);

	ग_लिखोl_relaxed(FCR_CTCF, qspi->io_base + QSPI_FCR);

	अगर (err || समयout)
		dev_err(qspi->dev, "%s err:%d abort timeout:%d\n",
			__func__, err, समयout);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_exec_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा sपंचांग32_qspi *qspi = spi_controller_get_devdata(mem->spi->master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(qspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(qspi->dev);
		वापस ret;
	पूर्ण

	mutex_lock(&qspi->lock);
	अगर (op->data.dir == SPI_MEM_DATA_IN && op->data.nbytes)
		qspi->भ_शेषe = CCR_FMODE_INDR;
	अन्यथा
		qspi->भ_शेषe = CCR_FMODE_INDW;

	ret = sपंचांग32_qspi_send(mem, op);
	mutex_unlock(&qspi->lock);

	pm_runसमय_mark_last_busy(qspi->dev);
	pm_runसमय_put_स्वतःsuspend(qspi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_dirmap_create(काष्ठा spi_mem_dirmap_desc *desc)
अणु
	काष्ठा sपंचांग32_qspi *qspi = spi_controller_get_devdata(desc->mem->spi->master);

	अगर (desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_OUT)
		वापस -EOPNOTSUPP;

	/* should never happen, as mm_base == null is an error probe निकास condition */
	अगर (!qspi->mm_base && desc->info.op_पंचांगpl.data.dir == SPI_MEM_DATA_IN)
		वापस -EOPNOTSUPP;

	अगर (!qspi->mm_size)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_qspi_dirmap_पढ़ो(काष्ठा spi_mem_dirmap_desc *desc,
				      u64 offs, माप_प्रकार len, व्योम *buf)
अणु
	काष्ठा sपंचांग32_qspi *qspi = spi_controller_get_devdata(desc->mem->spi->master);
	काष्ठा spi_mem_op op;
	u32 addr_max;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(qspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(qspi->dev);
		वापस ret;
	पूर्ण

	mutex_lock(&qspi->lock);
	/* make a local copy of desc op_पंचांगpl and complete dirmap rdesc
	 * spi_mem_op ढाँचा with offs, len and *buf in  order to get
	 * all needed transfer inक्रमmation पूर्णांकo काष्ठा spi_mem_op
	 */
	स_नकल(&op, &desc->info.op_पंचांगpl, माप(काष्ठा spi_mem_op));
	dev_dbg(qspi->dev, "%s len = 0x%zx offs = 0x%llx buf = 0x%p\n", __func__, len, offs, buf);

	op.data.nbytes = len;
	op.addr.val = desc->info.offset + offs;
	op.data.buf.in = buf;

	addr_max = op.addr.val + op.data.nbytes + 1;
	अगर (addr_max < qspi->mm_size && op.addr.buswidth)
		qspi->भ_शेषe = CCR_FMODE_MM;
	अन्यथा
		qspi->भ_शेषe = CCR_FMODE_INDR;

	ret = sपंचांग32_qspi_send(desc->mem, &op);
	mutex_unlock(&qspi->lock);

	pm_runसमय_mark_last_busy(qspi->dev);
	pm_runसमय_put_स्वतःsuspend(qspi->dev);

	वापस ret ?: len;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctrl = spi->master;
	काष्ठा sपंचांग32_qspi *qspi = spi_controller_get_devdata(ctrl);
	काष्ठा sपंचांग32_qspi_flash *flash;
	u32 presc;
	पूर्णांक ret;

	अगर (ctrl->busy)
		वापस -EBUSY;

	अगर (!spi->max_speed_hz)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(qspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(qspi->dev);
		वापस ret;
	पूर्ण

	presc = DIV_ROUND_UP(qspi->clk_rate, spi->max_speed_hz) - 1;

	flash = &qspi->flash[spi->chip_select];
	flash->qspi = qspi;
	flash->cs = spi->chip_select;
	flash->presc = presc;

	mutex_lock(&qspi->lock);
	qspi->cr_reg = 3 << CR_FTHRES_SHIFT | CR_SSHIFT | CR_EN;
	ग_लिखोl_relaxed(qspi->cr_reg, qspi->io_base + QSPI_CR);

	/* set dcr fsize to max address */
	qspi->dcr_reg = DCR_FSIZE_MASK;
	ग_लिखोl_relaxed(qspi->dcr_reg, qspi->io_base + QSPI_DCR);
	mutex_unlock(&qspi->lock);

	pm_runसमय_mark_last_busy(qspi->dev);
	pm_runसमय_put_स्वतःsuspend(qspi->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_dma_setup(काष्ठा sपंचांग32_qspi *qspi)
अणु
	काष्ठा dma_slave_config dma_cfg;
	काष्ठा device *dev = qspi->dev;
	पूर्णांक ret = 0;

	स_रखो(&dma_cfg, 0, माप(dma_cfg));

	dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_cfg.src_addr = qspi->phys_base + QSPI_DR;
	dma_cfg.dst_addr = qspi->phys_base + QSPI_DR;
	dma_cfg.src_maxburst = 4;
	dma_cfg.dst_maxburst = 4;

	qspi->dma_chrx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(qspi->dma_chrx)) अणु
		ret = PTR_ERR(qspi->dma_chrx);
		qspi->dma_chrx = शून्य;
		अगर (ret == -EPROBE_DEFER)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (dmaengine_slave_config(qspi->dma_chrx, &dma_cfg)) अणु
			dev_err(dev, "dma rx config failed\n");
			dma_release_channel(qspi->dma_chrx);
			qspi->dma_chrx = शून्य;
		पूर्ण
	पूर्ण

	qspi->dma_chtx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(qspi->dma_chtx)) अणु
		ret = PTR_ERR(qspi->dma_chtx);
		qspi->dma_chtx = शून्य;
	पूर्ण अन्यथा अणु
		अगर (dmaengine_slave_config(qspi->dma_chtx, &dma_cfg)) अणु
			dev_err(dev, "dma tx config failed\n");
			dma_release_channel(qspi->dma_chtx);
			qspi->dma_chtx = शून्य;
		पूर्ण
	पूर्ण

out:
	init_completion(&qspi->dma_completion);

	अगर (ret != -EPROBE_DEFER)
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_qspi_dma_मुक्त(काष्ठा sपंचांग32_qspi *qspi)
अणु
	अगर (qspi->dma_chtx)
		dma_release_channel(qspi->dma_chtx);
	अगर (qspi->dma_chrx)
		dma_release_channel(qspi->dma_chrx);
पूर्ण

/*
 * no special host स्थिरraपूर्णांक, so use शेष spi_mem_शेष_supports_op
 * to check supported mode.
 */
अटल स्थिर काष्ठा spi_controller_mem_ops sपंचांग32_qspi_mem_ops = अणु
	.exec_op	= sपंचांग32_qspi_exec_op,
	.dirmap_create	= sपंचांग32_qspi_dirmap_create,
	.dirmap_पढ़ो	= sपंचांग32_qspi_dirmap_पढ़ो,
पूर्ण;

अटल पूर्णांक sपंचांग32_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_controller *ctrl;
	काष्ठा reset_control *rstc;
	काष्ठा sपंचांग32_qspi *qspi;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	ctrl = spi_alloc_master(dev, माप(*qspi));
	अगर (!ctrl)
		वापस -ENOMEM;

	qspi = spi_controller_get_devdata(ctrl);
	qspi->ctrl = ctrl;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qspi");
	qspi->io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(qspi->io_base)) अणु
		ret = PTR_ERR(qspi->io_base);
		जाओ err_master_put;
	पूर्ण

	qspi->phys_base = res->start;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_mm");
	qspi->mm_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(qspi->mm_base)) अणु
		ret = PTR_ERR(qspi->mm_base);
		जाओ err_master_put;
	पूर्ण

	qspi->mm_size = resource_size(res);
	अगर (qspi->mm_size > STM32_QSPI_MAX_MMAP_SZ) अणु
		ret = -EINVAL;
		जाओ err_master_put;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_master_put;
	पूर्ण

	ret = devm_request_irq(dev, irq, sपंचांग32_qspi_irq, 0,
			       dev_name(dev), qspi);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ err_master_put;
	पूर्ण

	init_completion(&qspi->data_completion);

	qspi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(qspi->clk)) अणु
		ret = PTR_ERR(qspi->clk);
		जाओ err_master_put;
	पूर्ण

	qspi->clk_rate = clk_get_rate(qspi->clk);
	अगर (!qspi->clk_rate) अणु
		ret = -EINVAL;
		जाओ err_master_put;
	पूर्ण

	ret = clk_prepare_enable(qspi->clk);
	अगर (ret) अणु
		dev_err(dev, "can not enable the clock\n");
		जाओ err_master_put;
	पूर्ण

	rstc = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		अगर (ret == -EPROBE_DEFER)
			जाओ err_clk_disable;
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rstc);
		udelay(2);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	qspi->dev = dev;
	platक्रमm_set_drvdata(pdev, qspi);
	ret = sपंचांग32_qspi_dma_setup(qspi);
	अगर (ret)
		जाओ err_dma_मुक्त;

	mutex_init(&qspi->lock);

	ctrl->mode_bits = SPI_RX_DUAL | SPI_RX_QUAD
		| SPI_TX_DUAL | SPI_TX_QUAD;
	ctrl->setup = sपंचांग32_qspi_setup;
	ctrl->bus_num = -1;
	ctrl->mem_ops = &sपंचांग32_qspi_mem_ops;
	ctrl->num_chipselect = STM32_QSPI_MAX_NORCHIP;
	ctrl->dev.of_node = dev->of_node;

	pm_runसमय_set_स्वतःsuspend_delay(dev, STM32_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_noresume(dev);

	ret = devm_spi_रेजिस्टर_master(dev, ctrl);
	अगर (ret)
		जाओ err_pm_runसमय_मुक्त;

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

err_pm_runसमय_मुक्त:
	pm_runसमय_get_sync(qspi->dev);
	/* disable qspi */
	ग_लिखोl_relaxed(0, qspi->io_base + QSPI_CR);
	mutex_destroy(&qspi->lock);
	pm_runसमय_put_noidle(qspi->dev);
	pm_runसमय_disable(qspi->dev);
	pm_runसमय_set_suspended(qspi->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(qspi->dev);
err_dma_मुक्त:
	sपंचांग32_qspi_dma_मुक्त(qspi);
err_clk_disable:
	clk_disable_unprepare(qspi->clk);
err_master_put:
	spi_master_put(qspi->ctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_qspi *qspi = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(qspi->dev);
	/* disable qspi */
	ग_लिखोl_relaxed(0, qspi->io_base + QSPI_CR);
	sपंचांग32_qspi_dma_मुक्त(qspi);
	mutex_destroy(&qspi->lock);
	pm_runसमय_put_noidle(qspi->dev);
	pm_runसमय_disable(qspi->dev);
	pm_runसमय_set_suspended(qspi->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(qspi->dev);
	clk_disable_unprepare(qspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_qspi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_qspi *qspi = dev_get_drvdata(dev);

	clk_disable_unprepare(qspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_qspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_qspi *qspi = dev_get_drvdata(dev);

	वापस clk_prepare_enable(qspi->clk);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_qspi_suspend(काष्ठा device *dev)
अणु
	pinctrl_pm_select_sleep_state(dev);

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_qspi *qspi = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	ग_लिखोl_relaxed(qspi->cr_reg, qspi->io_base + QSPI_CR);
	ग_लिखोl_relaxed(qspi->dcr_reg, qspi->io_base + QSPI_DCR);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_qspi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग32_qspi_runसमय_suspend,
			   sपंचांग32_qspi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_qspi_suspend, sपंचांग32_qspi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_qspi_match[] = अणु
	अणु.compatible = "st,stm32f469-qspi"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_qspi_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_qspi_driver = अणु
	.probe	= sपंचांग32_qspi_probe,
	.हटाओ	= sपंचांग32_qspi_हटाओ,
	.driver	= अणु
		.name = "stm32-qspi",
		.of_match_table = sपंचांग32_qspi_match,
		.pm = &sपंचांग32_qspi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_qspi_driver);

MODULE_AUTHOR("Ludovic Barre <ludovic.barre@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 quad spi driver");
MODULE_LICENSE("GPL v2");
