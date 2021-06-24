<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2014, The Linux foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>

#घोषणा QUP_CONFIG			0x0000
#घोषणा QUP_STATE			0x0004
#घोषणा QUP_IO_M_MODES			0x0008
#घोषणा QUP_SW_RESET			0x000c
#घोषणा QUP_OPERATIONAL			0x0018
#घोषणा QUP_ERROR_FLAGS			0x001c
#घोषणा QUP_ERROR_FLAGS_EN		0x0020
#घोषणा QUP_OPERATIONAL_MASK		0x0028
#घोषणा QUP_HW_VERSION			0x0030
#घोषणा QUP_MX_OUTPUT_CNT		0x0100
#घोषणा QUP_OUTPUT_FIFO			0x0110
#घोषणा QUP_MX_WRITE_CNT		0x0150
#घोषणा QUP_MX_INPUT_CNT		0x0200
#घोषणा QUP_MX_READ_CNT			0x0208
#घोषणा QUP_INPUT_FIFO			0x0218

#घोषणा SPI_CONFIG			0x0300
#घोषणा SPI_IO_CONTROL			0x0304
#घोषणा SPI_ERROR_FLAGS			0x0308
#घोषणा SPI_ERROR_FLAGS_EN		0x030c

/* QUP_CONFIG fields */
#घोषणा QUP_CONFIG_SPI_MODE		(1 << 8)
#घोषणा QUP_CONFIG_CLOCK_AUTO_GATE	BIT(13)
#घोषणा QUP_CONFIG_NO_INPUT		BIT(7)
#घोषणा QUP_CONFIG_NO_OUTPUT		BIT(6)
#घोषणा QUP_CONFIG_N			0x001f

/* QUP_STATE fields */
#घोषणा QUP_STATE_VALID			BIT(2)
#घोषणा QUP_STATE_RESET			0
#घोषणा QUP_STATE_RUN			1
#घोषणा QUP_STATE_PAUSE			3
#घोषणा QUP_STATE_MASK			3
#घोषणा QUP_STATE_CLEAR			2

#घोषणा QUP_HW_VERSION_2_1_1		0x20010001

/* QUP_IO_M_MODES fields */
#घोषणा QUP_IO_M_PACK_EN		BIT(15)
#घोषणा QUP_IO_M_UNPACK_EN		BIT(14)
#घोषणा QUP_IO_M_INPUT_MODE_MASK_SHIFT	12
#घोषणा QUP_IO_M_OUTPUT_MODE_MASK_SHIFT	10
#घोषणा QUP_IO_M_INPUT_MODE_MASK	(3 << QUP_IO_M_INPUT_MODE_MASK_SHIFT)
#घोषणा QUP_IO_M_OUTPUT_MODE_MASK	(3 << QUP_IO_M_OUTPUT_MODE_MASK_SHIFT)

#घोषणा QUP_IO_M_OUTPUT_BLOCK_SIZE(x)	(((x) & (0x03 << 0)) >> 0)
#घोषणा QUP_IO_M_OUTPUT_FIFO_SIZE(x)	(((x) & (0x07 << 2)) >> 2)
#घोषणा QUP_IO_M_INPUT_BLOCK_SIZE(x)	(((x) & (0x03 << 5)) >> 5)
#घोषणा QUP_IO_M_INPUT_FIFO_SIZE(x)	(((x) & (0x07 << 7)) >> 7)

#घोषणा QUP_IO_M_MODE_FIFO		0
#घोषणा QUP_IO_M_MODE_BLOCK		1
#घोषणा QUP_IO_M_MODE_DMOV		2
#घोषणा QUP_IO_M_MODE_BAM		3

/* QUP_OPERATIONAL fields */
#घोषणा QUP_OP_IN_BLOCK_READ_REQ	BIT(13)
#घोषणा QUP_OP_OUT_BLOCK_WRITE_REQ	BIT(12)
#घोषणा QUP_OP_MAX_INPUT_DONE_FLAG	BIT(11)
#घोषणा QUP_OP_MAX_OUTPUT_DONE_FLAG	BIT(10)
#घोषणा QUP_OP_IN_SERVICE_FLAG		BIT(9)
#घोषणा QUP_OP_OUT_SERVICE_FLAG		BIT(8)
#घोषणा QUP_OP_IN_FIFO_FULL		BIT(7)
#घोषणा QUP_OP_OUT_FIFO_FULL		BIT(6)
#घोषणा QUP_OP_IN_FIFO_NOT_EMPTY	BIT(5)
#घोषणा QUP_OP_OUT_FIFO_NOT_EMPTY	BIT(4)

/* QUP_ERROR_FLAGS and QUP_ERROR_FLAGS_EN fields */
#घोषणा QUP_ERROR_OUTPUT_OVER_RUN	BIT(5)
#घोषणा QUP_ERROR_INPUT_UNDER_RUN	BIT(4)
#घोषणा QUP_ERROR_OUTPUT_UNDER_RUN	BIT(3)
#घोषणा QUP_ERROR_INPUT_OVER_RUN	BIT(2)

/* SPI_CONFIG fields */
#घोषणा SPI_CONFIG_HS_MODE		BIT(10)
#घोषणा SPI_CONFIG_INPUT_FIRST		BIT(9)
#घोषणा SPI_CONFIG_LOOPBACK		BIT(8)

/* SPI_IO_CONTROL fields */
#घोषणा SPI_IO_C_FORCE_CS		BIT(11)
#घोषणा SPI_IO_C_CLK_IDLE_HIGH		BIT(10)
#घोषणा SPI_IO_C_MX_CS_MODE		BIT(8)
#घोषणा SPI_IO_C_CS_N_POLARITY_0	BIT(4)
#घोषणा SPI_IO_C_CS_SELECT(x)		(((x) & 3) << 2)
#घोषणा SPI_IO_C_CS_SELECT_MASK		0x000c
#घोषणा SPI_IO_C_TRISTATE_CS		BIT(1)
#घोषणा SPI_IO_C_NO_TRI_STATE		BIT(0)

/* SPI_ERROR_FLAGS and SPI_ERROR_FLAGS_EN fields */
#घोषणा SPI_ERROR_CLK_OVER_RUN		BIT(1)
#घोषणा SPI_ERROR_CLK_UNDER_RUN		BIT(0)

#घोषणा SPI_NUM_CHIPSELECTS		4

#घोषणा SPI_MAX_XFER			(SZ_64K - 64)

/* high speed mode is when bus rate is greater then 26MHz */
#घोषणा SPI_HS_MIN_RATE			26000000
#घोषणा SPI_MAX_RATE			50000000

#घोषणा SPI_DELAY_THRESHOLD		1
#घोषणा SPI_DELAY_RETRY			10

काष्ठा spi_qup अणु
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा clk		*cclk;	/* core घड़ी */
	काष्ठा clk		*iclk;	/* पूर्णांकerface घड़ी */
	पूर्णांक			irq;
	spinlock_t		lock;

	पूर्णांक			in_fअगरo_sz;
	पूर्णांक			out_fअगरo_sz;
	पूर्णांक			in_blk_sz;
	पूर्णांक			out_blk_sz;

	काष्ठा spi_transfer	*xfer;
	काष्ठा completion	करोne;
	पूर्णांक			error;
	पूर्णांक			w_size;	/* bytes per SPI word */
	पूर्णांक			n_words;
	पूर्णांक			tx_bytes;
	पूर्णांक			rx_bytes;
	स्थिर u8		*tx_buf;
	u8			*rx_buf;
	पूर्णांक			qup_v1;

	पूर्णांक			mode;
	काष्ठा dma_slave_config	rx_conf;
	काष्ठा dma_slave_config	tx_conf;
पूर्ण;

अटल पूर्णांक spi_qup_io_config(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer);

अटल अंतरभूत bool spi_qup_is_flag_set(काष्ठा spi_qup *controller, u32 flag)
अणु
	u32 opflag = पढ़ोl_relaxed(controller->base + QUP_OPERATIONAL);

	वापस (opflag & flag) != 0;
पूर्ण

अटल अंतरभूत bool spi_qup_is_dma_xfer(पूर्णांक mode)
अणु
	अगर (mode == QUP_IO_M_MODE_DMOV || mode == QUP_IO_M_MODE_BAM)
		वापस true;

	वापस false;
पूर्ण

/* get's the transaction size length */
अटल अंतरभूत अचिन्हित पूर्णांक spi_qup_len(काष्ठा spi_qup *controller)
अणु
	वापस controller->n_words * controller->w_size;
पूर्ण

अटल अंतरभूत bool spi_qup_is_valid_state(काष्ठा spi_qup *controller)
अणु
	u32 opstate = पढ़ोl_relaxed(controller->base + QUP_STATE);

	वापस opstate & QUP_STATE_VALID;
पूर्ण

अटल पूर्णांक spi_qup_set_state(काष्ठा spi_qup *controller, u32 state)
अणु
	अचिन्हित दीर्घ loop;
	u32 cur_state;

	loop = 0;
	जबतक (!spi_qup_is_valid_state(controller)) अणु

		usleep_range(SPI_DELAY_THRESHOLD, SPI_DELAY_THRESHOLD * 2);

		अगर (++loop > SPI_DELAY_RETRY)
			वापस -EIO;
	पूर्ण

	अगर (loop)
		dev_dbg(controller->dev, "invalid state for %ld,us %d\n",
			loop, state);

	cur_state = पढ़ोl_relaxed(controller->base + QUP_STATE);
	/*
	 * Per spec: क्रम PAUSE_STATE to RESET_STATE, two ग_लिखोs
	 * of (b10) are required
	 */
	अगर (((cur_state & QUP_STATE_MASK) == QUP_STATE_PAUSE) &&
	    (state == QUP_STATE_RESET)) अणु
		ग_लिखोl_relaxed(QUP_STATE_CLEAR, controller->base + QUP_STATE);
		ग_लिखोl_relaxed(QUP_STATE_CLEAR, controller->base + QUP_STATE);
	पूर्ण अन्यथा अणु
		cur_state &= ~QUP_STATE_MASK;
		cur_state |= state;
		ग_लिखोl_relaxed(cur_state, controller->base + QUP_STATE);
	पूर्ण

	loop = 0;
	जबतक (!spi_qup_is_valid_state(controller)) अणु

		usleep_range(SPI_DELAY_THRESHOLD, SPI_DELAY_THRESHOLD * 2);

		अगर (++loop > SPI_DELAY_RETRY)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spi_qup_पढ़ो_from_fअगरo(काष्ठा spi_qup *controller, u32 num_words)
अणु
	u8 *rx_buf = controller->rx_buf;
	पूर्णांक i, shअगरt, num_bytes;
	u32 word;

	क्रम (; num_words; num_words--) अणु

		word = पढ़ोl_relaxed(controller->base + QUP_INPUT_FIFO);

		num_bytes = min_t(पूर्णांक, spi_qup_len(controller) -
				       controller->rx_bytes,
				       controller->w_size);

		अगर (!rx_buf) अणु
			controller->rx_bytes += num_bytes;
			जारी;
		पूर्ण

		क्रम (i = 0; i < num_bytes; i++, controller->rx_bytes++) अणु
			/*
			 * The data क्रमmat depends on bytes per SPI word:
			 *  4 bytes: 0x12345678
			 *  2 bytes: 0x00001234
			 *  1 byte : 0x00000012
			 */
			shअगरt = BITS_PER_BYTE;
			shअगरt *= (controller->w_size - i - 1);
			rx_buf[controller->rx_bytes] = word >> shअगरt;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम spi_qup_पढ़ो(काष्ठा spi_qup *controller, u32 *opflags)
अणु
	u32 reमुख्यder, words_per_block, num_words;
	bool is_block_mode = controller->mode == QUP_IO_M_MODE_BLOCK;

	reमुख्यder = DIV_ROUND_UP(spi_qup_len(controller) - controller->rx_bytes,
				 controller->w_size);
	words_per_block = controller->in_blk_sz >> 2;

	करो अणु
		/* ACK by clearing service flag */
		ग_लिखोl_relaxed(QUP_OP_IN_SERVICE_FLAG,
			       controller->base + QUP_OPERATIONAL);

		अगर (!reमुख्यder)
			जाओ निकास;

		अगर (is_block_mode) अणु
			num_words = (reमुख्यder > words_per_block) ?
					words_per_block : reमुख्यder;
		पूर्ण अन्यथा अणु
			अगर (!spi_qup_is_flag_set(controller,
						 QUP_OP_IN_FIFO_NOT_EMPTY))
				अवरोध;

			num_words = 1;
		पूर्ण

		/* पढ़ो up to the maximum transfer size available */
		spi_qup_पढ़ो_from_fअगरo(controller, num_words);

		reमुख्यder -= num_words;

		/* अगर block mode, check to see अगर next block is available */
		अगर (is_block_mode && !spi_qup_is_flag_set(controller,
					QUP_OP_IN_BLOCK_READ_REQ))
			अवरोध;

	पूर्ण जबतक (reमुख्यder);

	/*
	 * Due to extra stickiness of the QUP_OP_IN_SERVICE_FLAG during block
	 * पढ़ोs, it has to be cleared again at the very end.  However, be sure
	 * to refresh opflags value because MAX_INPUT_DONE_FLAG may now be
	 * present and this is used to determine अगर transaction is complete
	 */
निकास:
	अगर (!reमुख्यder) अणु
		*opflags = पढ़ोl_relaxed(controller->base + QUP_OPERATIONAL);
		अगर (is_block_mode && *opflags & QUP_OP_MAX_INPUT_DONE_FLAG)
			ग_लिखोl_relaxed(QUP_OP_IN_SERVICE_FLAG,
				       controller->base + QUP_OPERATIONAL);
	पूर्ण
पूर्ण

अटल व्योम spi_qup_ग_लिखो_to_fअगरo(काष्ठा spi_qup *controller, u32 num_words)
अणु
	स्थिर u8 *tx_buf = controller->tx_buf;
	पूर्णांक i, num_bytes;
	u32 word, data;

	क्रम (; num_words; num_words--) अणु
		word = 0;

		num_bytes = min_t(पूर्णांक, spi_qup_len(controller) -
				       controller->tx_bytes,
				       controller->w_size);
		अगर (tx_buf)
			क्रम (i = 0; i < num_bytes; i++) अणु
				data = tx_buf[controller->tx_bytes + i];
				word |= data << (BITS_PER_BYTE * (3 - i));
			पूर्ण

		controller->tx_bytes += num_bytes;

		ग_लिखोl_relaxed(word, controller->base + QUP_OUTPUT_FIFO);
	पूर्ण
पूर्ण

अटल व्योम spi_qup_dma_करोne(व्योम *data)
अणु
	काष्ठा spi_qup *qup = data;

	complete(&qup->करोne);
पूर्ण

अटल व्योम spi_qup_ग_लिखो(काष्ठा spi_qup *controller)
अणु
	bool is_block_mode = controller->mode == QUP_IO_M_MODE_BLOCK;
	u32 reमुख्यder, words_per_block, num_words;

	reमुख्यder = DIV_ROUND_UP(spi_qup_len(controller) - controller->tx_bytes,
				 controller->w_size);
	words_per_block = controller->out_blk_sz >> 2;

	करो अणु
		/* ACK by clearing service flag */
		ग_लिखोl_relaxed(QUP_OP_OUT_SERVICE_FLAG,
			       controller->base + QUP_OPERATIONAL);

		/* make sure the पूर्णांकerrupt is valid */
		अगर (!reमुख्यder)
			वापस;

		अगर (is_block_mode) अणु
			num_words = (reमुख्यder > words_per_block) ?
				words_per_block : reमुख्यder;
		पूर्ण अन्यथा अणु
			अगर (spi_qup_is_flag_set(controller,
						QUP_OP_OUT_FIFO_FULL))
				अवरोध;

			num_words = 1;
		पूर्ण

		spi_qup_ग_लिखो_to_fअगरo(controller, num_words);

		reमुख्यder -= num_words;

		/* अगर block mode, check to see अगर next block is available */
		अगर (is_block_mode && !spi_qup_is_flag_set(controller,
					QUP_OP_OUT_BLOCK_WRITE_REQ))
			अवरोध;

	पूर्ण जबतक (reमुख्यder);
पूर्ण

अटल पूर्णांक spi_qup_prep_sg(काष्ठा spi_master *master, काष्ठा scatterlist *sgl,
			   अचिन्हित पूर्णांक nents, क्रमागत dma_transfer_direction dir,
			   dma_async_tx_callback callback)
अणु
	काष्ठा spi_qup *qup = spi_master_get_devdata(master);
	अचिन्हित दीर्घ flags = DMA_PREP_INTERRUPT | DMA_PREP_FENCE;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan *chan;
	dma_cookie_t cookie;

	अगर (dir == DMA_MEM_TO_DEV)
		chan = master->dma_tx;
	अन्यथा
		chan = master->dma_rx;

	desc = dmaengine_prep_slave_sg(chan, sgl, nents, dir, flags);
	अगर (IS_ERR_OR_शून्य(desc))
		वापस desc ? PTR_ERR(desc) : -EINVAL;

	desc->callback = callback;
	desc->callback_param = qup;

	cookie = dmaengine_submit(desc);

	वापस dma_submit_error(cookie);
पूर्ण

अटल व्योम spi_qup_dma_terminate(काष्ठा spi_master *master,
				  काष्ठा spi_transfer *xfer)
अणु
	अगर (xfer->tx_buf)
		dmaengine_terminate_all(master->dma_tx);
	अगर (xfer->rx_buf)
		dmaengine_terminate_all(master->dma_rx);
पूर्ण

अटल u32 spi_qup_sgl_get_nents_len(काष्ठा scatterlist *sgl, u32 max,
				     u32 *nents)
अणु
	काष्ठा scatterlist *sg;
	u32 total = 0;

	क्रम (sg = sgl; sg; sg = sg_next(sg)) अणु
		अचिन्हित पूर्णांक len = sg_dma_len(sg);

		/* check क्रम overflow as well as limit */
		अगर (((total + len) < total) || ((total + len) > max))
			अवरोध;

		total += len;
		(*nents)++;
	पूर्ण

	वापस total;
पूर्ण

अटल पूर्णांक spi_qup_करो_dma(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer,
			  अचिन्हित दीर्घ समयout)
अणु
	dma_async_tx_callback rx_करोne = शून्य, tx_करोne = शून्य;
	काष्ठा spi_master *master = spi->master;
	काष्ठा spi_qup *qup = spi_master_get_devdata(master);
	काष्ठा scatterlist *tx_sgl, *rx_sgl;
	पूर्णांक ret;

	अगर (xfer->rx_buf)
		rx_करोne = spi_qup_dma_करोne;
	अन्यथा अगर (xfer->tx_buf)
		tx_करोne = spi_qup_dma_करोne;

	rx_sgl = xfer->rx_sg.sgl;
	tx_sgl = xfer->tx_sg.sgl;

	करो अणु
		u32 rx_nents = 0, tx_nents = 0;

		अगर (rx_sgl)
			qup->n_words = spi_qup_sgl_get_nents_len(rx_sgl,
					SPI_MAX_XFER, &rx_nents) / qup->w_size;
		अगर (tx_sgl)
			qup->n_words = spi_qup_sgl_get_nents_len(tx_sgl,
					SPI_MAX_XFER, &tx_nents) / qup->w_size;
		अगर (!qup->n_words)
			वापस -EIO;

		ret = spi_qup_io_config(spi, xfer);
		अगर (ret)
			वापस ret;

		/* beक्रमe issuing the descriptors, set the QUP to run */
		ret = spi_qup_set_state(qup, QUP_STATE_RUN);
		अगर (ret) अणु
			dev_warn(qup->dev, "cannot set RUN state\n");
			वापस ret;
		पूर्ण
		अगर (rx_sgl) अणु
			ret = spi_qup_prep_sg(master, rx_sgl, rx_nents,
					      DMA_DEV_TO_MEM, rx_करोne);
			अगर (ret)
				वापस ret;
			dma_async_issue_pending(master->dma_rx);
		पूर्ण

		अगर (tx_sgl) अणु
			ret = spi_qup_prep_sg(master, tx_sgl, tx_nents,
					      DMA_MEM_TO_DEV, tx_करोne);
			अगर (ret)
				वापस ret;

			dma_async_issue_pending(master->dma_tx);
		पूर्ण

		अगर (!रुको_क्रम_completion_समयout(&qup->करोne, समयout))
			वापस -ETIMEDOUT;

		क्रम (; rx_sgl && rx_nents--; rx_sgl = sg_next(rx_sgl))
			;
		क्रम (; tx_sgl && tx_nents--; tx_sgl = sg_next(tx_sgl))
			;

	पूर्ण जबतक (rx_sgl || tx_sgl);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_qup_करो_pio(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer,
			  अचिन्हित दीर्घ समयout)
अणु
	काष्ठा spi_master *master = spi->master;
	काष्ठा spi_qup *qup = spi_master_get_devdata(master);
	पूर्णांक ret, n_words, iterations, offset = 0;

	n_words = qup->n_words;
	iterations = n_words / SPI_MAX_XFER; /* round करोwn */
	qup->rx_buf = xfer->rx_buf;
	qup->tx_buf = xfer->tx_buf;

	करो अणु
		अगर (iterations)
			qup->n_words = SPI_MAX_XFER;
		अन्यथा
			qup->n_words = n_words % SPI_MAX_XFER;

		अगर (qup->tx_buf && offset)
			qup->tx_buf = xfer->tx_buf + offset * SPI_MAX_XFER;

		अगर (qup->rx_buf && offset)
			qup->rx_buf = xfer->rx_buf + offset * SPI_MAX_XFER;

		/*
		 * अगर the transaction is small enough, we need
		 * to fallback to FIFO mode
		 */
		अगर (qup->n_words <= (qup->in_fअगरo_sz / माप(u32)))
			qup->mode = QUP_IO_M_MODE_FIFO;

		ret = spi_qup_io_config(spi, xfer);
		अगर (ret)
			वापस ret;

		ret = spi_qup_set_state(qup, QUP_STATE_RUN);
		अगर (ret) अणु
			dev_warn(qup->dev, "cannot set RUN state\n");
			वापस ret;
		पूर्ण

		ret = spi_qup_set_state(qup, QUP_STATE_PAUSE);
		अगर (ret) अणु
			dev_warn(qup->dev, "cannot set PAUSE state\n");
			वापस ret;
		पूर्ण

		अगर (qup->mode == QUP_IO_M_MODE_FIFO)
			spi_qup_ग_लिखो(qup);

		ret = spi_qup_set_state(qup, QUP_STATE_RUN);
		अगर (ret) अणु
			dev_warn(qup->dev, "cannot set RUN state\n");
			वापस ret;
		पूर्ण

		अगर (!रुको_क्रम_completion_समयout(&qup->करोne, समयout))
			वापस -ETIMEDOUT;

		offset++;
	पूर्ण जबतक (iterations--);

	वापस 0;
पूर्ण

अटल bool spi_qup_data_pending(काष्ठा spi_qup *controller)
अणु
	अचिन्हित पूर्णांक reमुख्यder_tx, reमुख्यder_rx;

	reमुख्यder_tx = DIV_ROUND_UP(spi_qup_len(controller) -
				    controller->tx_bytes, controller->w_size);

	reमुख्यder_rx = DIV_ROUND_UP(spi_qup_len(controller) -
				    controller->rx_bytes, controller->w_size);

	वापस reमुख्यder_tx || reमुख्यder_rx;
पूर्ण

अटल irqवापस_t spi_qup_qup_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_qup *controller = dev_id;
	u32 opflags, qup_err, spi_err;
	अचिन्हित दीर्घ flags;
	पूर्णांक error = 0;

	qup_err = पढ़ोl_relaxed(controller->base + QUP_ERROR_FLAGS);
	spi_err = पढ़ोl_relaxed(controller->base + SPI_ERROR_FLAGS);
	opflags = पढ़ोl_relaxed(controller->base + QUP_OPERATIONAL);

	ग_लिखोl_relaxed(qup_err, controller->base + QUP_ERROR_FLAGS);
	ग_लिखोl_relaxed(spi_err, controller->base + SPI_ERROR_FLAGS);

	अगर (qup_err) अणु
		अगर (qup_err & QUP_ERROR_OUTPUT_OVER_RUN)
			dev_warn(controller->dev, "OUTPUT_OVER_RUN\n");
		अगर (qup_err & QUP_ERROR_INPUT_UNDER_RUN)
			dev_warn(controller->dev, "INPUT_UNDER_RUN\n");
		अगर (qup_err & QUP_ERROR_OUTPUT_UNDER_RUN)
			dev_warn(controller->dev, "OUTPUT_UNDER_RUN\n");
		अगर (qup_err & QUP_ERROR_INPUT_OVER_RUN)
			dev_warn(controller->dev, "INPUT_OVER_RUN\n");

		error = -EIO;
	पूर्ण

	अगर (spi_err) अणु
		अगर (spi_err & SPI_ERROR_CLK_OVER_RUN)
			dev_warn(controller->dev, "CLK_OVER_RUN\n");
		अगर (spi_err & SPI_ERROR_CLK_UNDER_RUN)
			dev_warn(controller->dev, "CLK_UNDER_RUN\n");

		error = -EIO;
	पूर्ण

	spin_lock_irqsave(&controller->lock, flags);
	अगर (!controller->error)
		controller->error = error;
	spin_unlock_irqrestore(&controller->lock, flags);

	अगर (spi_qup_is_dma_xfer(controller->mode)) अणु
		ग_लिखोl_relaxed(opflags, controller->base + QUP_OPERATIONAL);
	पूर्ण अन्यथा अणु
		अगर (opflags & QUP_OP_IN_SERVICE_FLAG)
			spi_qup_पढ़ो(controller, &opflags);

		अगर (opflags & QUP_OP_OUT_SERVICE_FLAG)
			spi_qup_ग_लिखो(controller);

		अगर (!spi_qup_data_pending(controller))
			complete(&controller->करोne);
	पूर्ण

	अगर (error)
		complete(&controller->करोne);

	अगर (opflags & QUP_OP_MAX_INPUT_DONE_FLAG) अणु
		अगर (!spi_qup_is_dma_xfer(controller->mode)) अणु
			अगर (spi_qup_data_pending(controller))
				वापस IRQ_HANDLED;
		पूर्ण
		complete(&controller->करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* set घड़ी freq ... bits per word, determine mode */
अटल पूर्णांक spi_qup_io_prep(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_qup *controller = spi_master_get_devdata(spi->master);
	पूर्णांक ret;

	अगर (spi->mode & SPI_LOOP && xfer->len > controller->in_fअगरo_sz) अणु
		dev_err(controller->dev, "too big size for loopback %d > %d\n",
			xfer->len, controller->in_fअगरo_sz);
		वापस -EIO;
	पूर्ण

	ret = clk_set_rate(controller->cclk, xfer->speed_hz);
	अगर (ret) अणु
		dev_err(controller->dev, "fail to set frequency %d",
			xfer->speed_hz);
		वापस -EIO;
	पूर्ण

	controller->w_size = DIV_ROUND_UP(xfer->bits_per_word, 8);
	controller->n_words = xfer->len / controller->w_size;

	अगर (controller->n_words <= (controller->in_fअगरo_sz / माप(u32)))
		controller->mode = QUP_IO_M_MODE_FIFO;
	अन्यथा अगर (spi->master->can_dma &&
		 spi->master->can_dma(spi->master, spi, xfer) &&
		 spi->master->cur_msg_mapped)
		controller->mode = QUP_IO_M_MODE_BAM;
	अन्यथा
		controller->mode = QUP_IO_M_MODE_BLOCK;

	वापस 0;
पूर्ण

/* prep qup क्रम another spi transaction of specअगरic type */
अटल पूर्णांक spi_qup_io_config(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_qup *controller = spi_master_get_devdata(spi->master);
	u32 config, iomode, control;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&controller->lock, flags);
	controller->xfer     = xfer;
	controller->error    = 0;
	controller->rx_bytes = 0;
	controller->tx_bytes = 0;
	spin_unlock_irqrestore(&controller->lock, flags);


	अगर (spi_qup_set_state(controller, QUP_STATE_RESET)) अणु
		dev_err(controller->dev, "cannot set RESET state\n");
		वापस -EIO;
	पूर्ण

	चयन (controller->mode) अणु
	हाल QUP_IO_M_MODE_FIFO:
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_READ_CNT);
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_WRITE_CNT);
		/* must be zero क्रम FIFO */
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_INPUT_CNT);
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_OUTPUT_CNT);
		अवरोध;
	हाल QUP_IO_M_MODE_BAM:
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_INPUT_CNT);
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_OUTPUT_CNT);
		/* must be zero क्रम BLOCK and BAM */
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_READ_CNT);
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_WRITE_CNT);

		अगर (!controller->qup_v1) अणु
			व्योम __iomem *input_cnt;

			input_cnt = controller->base + QUP_MX_INPUT_CNT;
			/*
			 * क्रम DMA transfers, both QUP_MX_INPUT_CNT and
			 * QUP_MX_OUTPUT_CNT must be zero to all हालs but one.
			 * That हाल is a non-balanced transfer when there is
			 * only a rx_buf.
			 */
			अगर (xfer->tx_buf)
				ग_लिखोl_relaxed(0, input_cnt);
			अन्यथा
				ग_लिखोl_relaxed(controller->n_words, input_cnt);

			ग_लिखोl_relaxed(0, controller->base + QUP_MX_OUTPUT_CNT);
		पूर्ण
		अवरोध;
	हाल QUP_IO_M_MODE_BLOCK:
		reinit_completion(&controller->करोne);
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_INPUT_CNT);
		ग_लिखोl_relaxed(controller->n_words,
			       controller->base + QUP_MX_OUTPUT_CNT);
		/* must be zero क्रम BLOCK and BAM */
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_READ_CNT);
		ग_लिखोl_relaxed(0, controller->base + QUP_MX_WRITE_CNT);
		अवरोध;
	शेष:
		dev_err(controller->dev, "unknown mode = %d\n",
				controller->mode);
		वापस -EIO;
	पूर्ण

	iomode = पढ़ोl_relaxed(controller->base + QUP_IO_M_MODES);
	/* Set input and output transfer mode */
	iomode &= ~(QUP_IO_M_INPUT_MODE_MASK | QUP_IO_M_OUTPUT_MODE_MASK);

	अगर (!spi_qup_is_dma_xfer(controller->mode))
		iomode &= ~(QUP_IO_M_PACK_EN | QUP_IO_M_UNPACK_EN);
	अन्यथा
		iomode |= QUP_IO_M_PACK_EN | QUP_IO_M_UNPACK_EN;

	iomode |= (controller->mode << QUP_IO_M_OUTPUT_MODE_MASK_SHIFT);
	iomode |= (controller->mode << QUP_IO_M_INPUT_MODE_MASK_SHIFT);

	ग_लिखोl_relaxed(iomode, controller->base + QUP_IO_M_MODES);

	control = पढ़ोl_relaxed(controller->base + SPI_IO_CONTROL);

	अगर (spi->mode & SPI_CPOL)
		control |= SPI_IO_C_CLK_IDLE_HIGH;
	अन्यथा
		control &= ~SPI_IO_C_CLK_IDLE_HIGH;

	ग_लिखोl_relaxed(control, controller->base + SPI_IO_CONTROL);

	config = पढ़ोl_relaxed(controller->base + SPI_CONFIG);

	अगर (spi->mode & SPI_LOOP)
		config |= SPI_CONFIG_LOOPBACK;
	अन्यथा
		config &= ~SPI_CONFIG_LOOPBACK;

	अगर (spi->mode & SPI_CPHA)
		config &= ~SPI_CONFIG_INPUT_FIRST;
	अन्यथा
		config |= SPI_CONFIG_INPUT_FIRST;

	/*
	 * HS_MODE improves संकेत stability क्रम spi-clk high rates,
	 * but is invalid in loop back mode.
	 */
	अगर ((xfer->speed_hz >= SPI_HS_MIN_RATE) && !(spi->mode & SPI_LOOP))
		config |= SPI_CONFIG_HS_MODE;
	अन्यथा
		config &= ~SPI_CONFIG_HS_MODE;

	ग_लिखोl_relaxed(config, controller->base + SPI_CONFIG);

	config = पढ़ोl_relaxed(controller->base + QUP_CONFIG);
	config &= ~(QUP_CONFIG_NO_INPUT | QUP_CONFIG_NO_OUTPUT | QUP_CONFIG_N);
	config |= xfer->bits_per_word - 1;
	config |= QUP_CONFIG_SPI_MODE;

	अगर (spi_qup_is_dma_xfer(controller->mode)) अणु
		अगर (!xfer->tx_buf)
			config |= QUP_CONFIG_NO_OUTPUT;
		अगर (!xfer->rx_buf)
			config |= QUP_CONFIG_NO_INPUT;
	पूर्ण

	ग_लिखोl_relaxed(config, controller->base + QUP_CONFIG);

	/* only ग_लिखो to OPERATIONAL_MASK when रेजिस्टर is present */
	अगर (!controller->qup_v1) अणु
		u32 mask = 0;

		/*
		 * mask INPUT and OUTPUT service flags to prevent IRQs on FIFO
		 * status change in BAM mode
		 */

		अगर (spi_qup_is_dma_xfer(controller->mode))
			mask = QUP_OP_IN_SERVICE_FLAG | QUP_OP_OUT_SERVICE_FLAG;

		ग_लिखोl_relaxed(mask, controller->base + QUP_OPERATIONAL_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_qup_transfer_one(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	अचिन्हित दीर्घ समयout, flags;
	पूर्णांक ret;

	ret = spi_qup_io_prep(spi, xfer);
	अगर (ret)
		वापस ret;

	समयout = DIV_ROUND_UP(xfer->speed_hz, MSEC_PER_SEC);
	समयout = DIV_ROUND_UP(min_t(अचिन्हित दीर्घ, SPI_MAX_XFER,
				     xfer->len) * 8, समयout);
	समयout = 100 * msecs_to_jअगरfies(समयout);

	reinit_completion(&controller->करोne);

	spin_lock_irqsave(&controller->lock, flags);
	controller->xfer     = xfer;
	controller->error    = 0;
	controller->rx_bytes = 0;
	controller->tx_bytes = 0;
	spin_unlock_irqrestore(&controller->lock, flags);

	अगर (spi_qup_is_dma_xfer(controller->mode))
		ret = spi_qup_करो_dma(spi, xfer, समयout);
	अन्यथा
		ret = spi_qup_करो_pio(spi, xfer, समयout);

	spi_qup_set_state(controller, QUP_STATE_RESET);
	spin_lock_irqsave(&controller->lock, flags);
	अगर (!ret)
		ret = controller->error;
	spin_unlock_irqrestore(&controller->lock, flags);

	अगर (ret && spi_qup_is_dma_xfer(controller->mode))
		spi_qup_dma_terminate(master, xfer);

	वापस ret;
पूर्ण

अटल bool spi_qup_can_dma(काष्ठा spi_master *master, काष्ठा spi_device *spi,
			    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_qup *qup = spi_master_get_devdata(master);
	माप_प्रकार dma_align = dma_get_cache_alignment();
	पूर्णांक n_words;

	अगर (xfer->rx_buf) अणु
		अगर (!IS_ALIGNED((माप_प्रकार)xfer->rx_buf, dma_align) ||
		    IS_ERR_OR_शून्य(master->dma_rx))
			वापस false;
		अगर (qup->qup_v1 && (xfer->len % qup->in_blk_sz))
			वापस false;
	पूर्ण

	अगर (xfer->tx_buf) अणु
		अगर (!IS_ALIGNED((माप_प्रकार)xfer->tx_buf, dma_align) ||
		    IS_ERR_OR_शून्य(master->dma_tx))
			वापस false;
		अगर (qup->qup_v1 && (xfer->len % qup->out_blk_sz))
			वापस false;
	पूर्ण

	n_words = xfer->len / DIV_ROUND_UP(xfer->bits_per_word, 8);
	अगर (n_words <= (qup->in_fअगरo_sz / माप(u32)))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम spi_qup_release_dma(काष्ठा spi_master *master)
अणु
	अगर (!IS_ERR_OR_शून्य(master->dma_rx))
		dma_release_channel(master->dma_rx);
	अगर (!IS_ERR_OR_शून्य(master->dma_tx))
		dma_release_channel(master->dma_tx);
पूर्ण

अटल पूर्णांक spi_qup_init_dma(काष्ठा spi_master *master, resource_माप_प्रकार base)
अणु
	काष्ठा spi_qup *spi = spi_master_get_devdata(master);
	काष्ठा dma_slave_config *rx_conf = &spi->rx_conf,
				*tx_conf = &spi->tx_conf;
	काष्ठा device *dev = spi->dev;
	पूर्णांक ret;

	/* allocate dma resources, अगर available */
	master->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(master->dma_rx))
		वापस PTR_ERR(master->dma_rx);

	master->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(master->dma_tx)) अणु
		ret = PTR_ERR(master->dma_tx);
		जाओ err_tx;
	पूर्ण

	/* set DMA parameters */
	rx_conf->direction = DMA_DEV_TO_MEM;
	rx_conf->device_fc = 1;
	rx_conf->src_addr = base + QUP_INPUT_FIFO;
	rx_conf->src_maxburst = spi->in_blk_sz;

	tx_conf->direction = DMA_MEM_TO_DEV;
	tx_conf->device_fc = 1;
	tx_conf->dst_addr = base + QUP_OUTPUT_FIFO;
	tx_conf->dst_maxburst = spi->out_blk_sz;

	ret = dmaengine_slave_config(master->dma_rx, rx_conf);
	अगर (ret) अणु
		dev_err(dev, "failed to configure RX channel\n");
		जाओ err;
	पूर्ण

	ret = dmaengine_slave_config(master->dma_tx, tx_conf);
	अगर (ret) अणु
		dev_err(dev, "failed to configure TX channel\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	dma_release_channel(master->dma_tx);
err_tx:
	dma_release_channel(master->dma_rx);
	वापस ret;
पूर्ण

अटल व्योम spi_qup_set_cs(काष्ठा spi_device *spi, bool val)
अणु
	काष्ठा spi_qup *controller;
	u32 spi_ioc;
	u32 spi_ioc_orig;

	controller = spi_master_get_devdata(spi->master);
	spi_ioc = पढ़ोl_relaxed(controller->base + SPI_IO_CONTROL);
	spi_ioc_orig = spi_ioc;
	अगर (!val)
		spi_ioc |= SPI_IO_C_FORCE_CS;
	अन्यथा
		spi_ioc &= ~SPI_IO_C_FORCE_CS;

	अगर (spi_ioc != spi_ioc_orig)
		ग_लिखोl_relaxed(spi_ioc, controller->base + SPI_IO_CONTROL);
पूर्ण

अटल पूर्णांक spi_qup_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा clk *iclk, *cclk;
	काष्ठा spi_qup *controller;
	काष्ठा resource *res;
	काष्ठा device *dev;
	व्योम __iomem *base;
	u32 max_freq, iomode, num_cs;
	पूर्णांक ret, irq, size;

	dev = &pdev->dev;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	cclk = devm_clk_get(dev, "core");
	अगर (IS_ERR(cclk))
		वापस PTR_ERR(cclk);

	iclk = devm_clk_get(dev, "iface");
	अगर (IS_ERR(iclk))
		वापस PTR_ERR(iclk);

	/* This is optional parameter */
	अगर (of_property_पढ़ो_u32(dev->of_node, "spi-max-frequency", &max_freq))
		max_freq = SPI_MAX_RATE;

	अगर (!max_freq || max_freq > SPI_MAX_RATE) अणु
		dev_err(dev, "invalid clock frequency %d\n", max_freq);
		वापस -ENXIO;
	पूर्ण

	ret = clk_prepare_enable(cclk);
	अगर (ret) अणु
		dev_err(dev, "cannot enable core clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(iclk);
	अगर (ret) अणु
		clk_disable_unprepare(cclk);
		dev_err(dev, "cannot enable iface clock\n");
		वापस ret;
	पूर्ण

	master = spi_alloc_master(dev, माप(काष्ठा spi_qup));
	अगर (!master) अणु
		clk_disable_unprepare(cclk);
		clk_disable_unprepare(iclk);
		dev_err(dev, "cannot allocate master\n");
		वापस -ENOMEM;
	पूर्ण

	/* use num-cs unless not present or out of range */
	अगर (of_property_पढ़ो_u32(dev->of_node, "num-cs", &num_cs) ||
	    num_cs > SPI_NUM_CHIPSELECTS)
		master->num_chipselect = SPI_NUM_CHIPSELECTS;
	अन्यथा
		master->num_chipselect = num_cs;

	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LOOP;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	master->max_speed_hz = max_freq;
	master->transfer_one = spi_qup_transfer_one;
	master->dev.of_node = pdev->dev.of_node;
	master->स्वतः_runसमय_pm = true;
	master->dma_alignment = dma_get_cache_alignment();
	master->max_dma_len = SPI_MAX_XFER;

	platक्रमm_set_drvdata(pdev, master);

	controller = spi_master_get_devdata(master);

	controller->dev = dev;
	controller->base = base;
	controller->iclk = iclk;
	controller->cclk = cclk;
	controller->irq = irq;

	ret = spi_qup_init_dma(master, res->start);
	अगर (ret == -EPROBE_DEFER)
		जाओ error;
	अन्यथा अगर (!ret)
		master->can_dma = spi_qup_can_dma;

	controller->qup_v1 = (uपूर्णांकptr_t)of_device_get_match_data(dev);

	अगर (!controller->qup_v1)
		master->set_cs = spi_qup_set_cs;

	spin_lock_init(&controller->lock);
	init_completion(&controller->करोne);

	iomode = पढ़ोl_relaxed(base + QUP_IO_M_MODES);

	size = QUP_IO_M_OUTPUT_BLOCK_SIZE(iomode);
	अगर (size)
		controller->out_blk_sz = size * 16;
	अन्यथा
		controller->out_blk_sz = 4;

	size = QUP_IO_M_INPUT_BLOCK_SIZE(iomode);
	अगर (size)
		controller->in_blk_sz = size * 16;
	अन्यथा
		controller->in_blk_sz = 4;

	size = QUP_IO_M_OUTPUT_FIFO_SIZE(iomode);
	controller->out_fअगरo_sz = controller->out_blk_sz * (2 << size);

	size = QUP_IO_M_INPUT_FIFO_SIZE(iomode);
	controller->in_fअगरo_sz = controller->in_blk_sz * (2 << size);

	dev_info(dev, "IN:block:%d, fifo:%d, OUT:block:%d, fifo:%d\n",
		 controller->in_blk_sz, controller->in_fअगरo_sz,
		 controller->out_blk_sz, controller->out_fअगरo_sz);

	ग_लिखोl_relaxed(1, base + QUP_SW_RESET);

	ret = spi_qup_set_state(controller, QUP_STATE_RESET);
	अगर (ret) अणु
		dev_err(dev, "cannot set RESET state\n");
		जाओ error_dma;
	पूर्ण

	ग_लिखोl_relaxed(0, base + QUP_OPERATIONAL);
	ग_लिखोl_relaxed(0, base + QUP_IO_M_MODES);

	अगर (!controller->qup_v1)
		ग_लिखोl_relaxed(0, base + QUP_OPERATIONAL_MASK);

	ग_लिखोl_relaxed(SPI_ERROR_CLK_UNDER_RUN | SPI_ERROR_CLK_OVER_RUN,
		       base + SPI_ERROR_FLAGS_EN);

	/* अगर earlier version of the QUP, disable INPUT_OVERRUN */
	अगर (controller->qup_v1)
		ग_लिखोl_relaxed(QUP_ERROR_OUTPUT_OVER_RUN |
			QUP_ERROR_INPUT_UNDER_RUN | QUP_ERROR_OUTPUT_UNDER_RUN,
			base + QUP_ERROR_FLAGS_EN);

	ग_लिखोl_relaxed(0, base + SPI_CONFIG);
	ग_लिखोl_relaxed(SPI_IO_C_NO_TRI_STATE, base + SPI_IO_CONTROL);

	ret = devm_request_irq(dev, irq, spi_qup_qup_irq,
			       IRQF_TRIGGER_HIGH, pdev->name, controller);
	अगर (ret)
		जाओ error_dma;

	pm_runसमय_set_स्वतःsuspend_delay(dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret)
		जाओ disable_pm;

	वापस 0;

disable_pm:
	pm_runसमय_disable(&pdev->dev);
error_dma:
	spi_qup_release_dma(master);
error:
	clk_disable_unprepare(cclk);
	clk_disable_unprepare(iclk);
	spi_master_put(master);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक spi_qup_pm_suspend_runसमय(काष्ठा device *device)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(device);
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	u32 config;

	/* Enable घड़ीs स्वतः gaiting */
	config = पढ़ोl(controller->base + QUP_CONFIG);
	config |= QUP_CONFIG_CLOCK_AUTO_GATE;
	ग_लिखोl_relaxed(config, controller->base + QUP_CONFIG);

	clk_disable_unprepare(controller->cclk);
	clk_disable_unprepare(controller->iclk);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_qup_pm_resume_runसमय(काष्ठा device *device)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(device);
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	u32 config;
	पूर्णांक ret;

	ret = clk_prepare_enable(controller->iclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(controller->cclk);
	अगर (ret)
		वापस ret;

	/* Disable घड़ीs स्वतः gaiting */
	config = पढ़ोl_relaxed(controller->base + QUP_CONFIG);
	config &= ~QUP_CONFIG_CLOCK_AUTO_GATE;
	ग_लिखोl_relaxed(config, controller->base + QUP_CONFIG);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spi_qup_suspend(काष्ठा device *device)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(device);
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	पूर्णांक ret;

	अगर (pm_runसमय_suspended(device)) अणु
		ret = spi_qup_pm_resume_runसमय(device);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	ret = spi_qup_set_state(controller, QUP_STATE_RESET);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(controller->cclk);
	clk_disable_unprepare(controller->iclk);
	वापस 0;
पूर्ण

अटल पूर्णांक spi_qup_resume(काष्ठा device *device)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(device);
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(controller->iclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(controller->cclk);
	अगर (ret)
		वापस ret;

	ret = spi_qup_set_state(controller, QUP_STATE_RESET);
	अगर (ret)
		वापस ret;

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक spi_qup_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(&pdev->dev);
	काष्ठा spi_qup *controller = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	ret = spi_qup_set_state(controller, QUP_STATE_RESET);
	अगर (ret)
		वापस ret;

	spi_qup_release_dma(master);

	clk_disable_unprepare(controller->cclk);
	clk_disable_unprepare(controller->iclk);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spi_qup_dt_match[] = अणु
	अणु .compatible = "qcom,spi-qup-v1.1.1", .data = (व्योम *)1, पूर्ण,
	अणु .compatible = "qcom,spi-qup-v2.1.1", पूर्ण,
	अणु .compatible = "qcom,spi-qup-v2.2.1", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spi_qup_dt_match);

अटल स्थिर काष्ठा dev_pm_ops spi_qup_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(spi_qup_suspend, spi_qup_resume)
	SET_RUNTIME_PM_OPS(spi_qup_pm_suspend_runसमय,
			   spi_qup_pm_resume_runसमय,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver spi_qup_driver = अणु
	.driver = अणु
		.name		= "spi_qup",
		.pm		= &spi_qup_dev_pm_ops,
		.of_match_table = spi_qup_dt_match,
	पूर्ण,
	.probe = spi_qup_probe,
	.हटाओ = spi_qup_हटाओ,
पूर्ण;
module_platक्रमm_driver(spi_qup_driver);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:spi_qup");
