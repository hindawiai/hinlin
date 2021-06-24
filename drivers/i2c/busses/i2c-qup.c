<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2009-2013, 2016-2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2014, Sony Mobile Communications AB.
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>

/* QUP Registers */
#घोषणा QUP_CONFIG		0x000
#घोषणा QUP_STATE		0x004
#घोषणा QUP_IO_MODE		0x008
#घोषणा QUP_SW_RESET		0x00c
#घोषणा QUP_OPERATIONAL		0x018
#घोषणा QUP_ERROR_FLAGS		0x01c
#घोषणा QUP_ERROR_FLAGS_EN	0x020
#घोषणा QUP_OPERATIONAL_MASK	0x028
#घोषणा QUP_HW_VERSION		0x030
#घोषणा QUP_MX_OUTPUT_CNT	0x100
#घोषणा QUP_OUT_FIFO_BASE	0x110
#घोषणा QUP_MX_WRITE_CNT	0x150
#घोषणा QUP_MX_INPUT_CNT	0x200
#घोषणा QUP_MX_READ_CNT		0x208
#घोषणा QUP_IN_FIFO_BASE	0x218
#घोषणा QUP_I2C_CLK_CTL		0x400
#घोषणा QUP_I2C_STATUS		0x404
#घोषणा QUP_I2C_MASTER_GEN	0x408

/* QUP States and reset values */
#घोषणा QUP_RESET_STATE		0
#घोषणा QUP_RUN_STATE		1
#घोषणा QUP_PAUSE_STATE		3
#घोषणा QUP_STATE_MASK		3

#घोषणा QUP_STATE_VALID		BIT(2)
#घोषणा QUP_I2C_MAST_GEN	BIT(4)
#घोषणा QUP_I2C_FLUSH		BIT(6)

#घोषणा QUP_OPERATIONAL_RESET	0x000ff0
#घोषणा QUP_I2C_STATUS_RESET	0xfffffc

/* QUP OPERATIONAL FLAGS */
#घोषणा QUP_I2C_NACK_FLAG	BIT(3)
#घोषणा QUP_OUT_NOT_EMPTY	BIT(4)
#घोषणा QUP_IN_NOT_EMPTY	BIT(5)
#घोषणा QUP_OUT_FULL		BIT(6)
#घोषणा QUP_OUT_SVC_FLAG	BIT(8)
#घोषणा QUP_IN_SVC_FLAG		BIT(9)
#घोषणा QUP_MX_OUTPUT_DONE	BIT(10)
#घोषणा QUP_MX_INPUT_DONE	BIT(11)
#घोषणा OUT_BLOCK_WRITE_REQ	BIT(12)
#घोषणा IN_BLOCK_READ_REQ	BIT(13)

/* I2C mini core related values */
#घोषणा QUP_NO_INPUT		BIT(7)
#घोषणा QUP_CLOCK_AUTO_GATE	BIT(13)
#घोषणा I2C_MINI_CORE		(2 << 8)
#घोषणा I2C_N_VAL		15
#घोषणा I2C_N_VAL_V2		7

/* Most signअगरicant word offset in FIFO port */
#घोषणा QUP_MSW_SHIFT		(I2C_N_VAL + 1)

/* Packing/Unpacking words in FIFOs, and IO modes */
#घोषणा QUP_OUTPUT_BLK_MODE	(1 << 10)
#घोषणा QUP_OUTPUT_BAM_MODE	(3 << 10)
#घोषणा QUP_INPUT_BLK_MODE	(1 << 12)
#घोषणा QUP_INPUT_BAM_MODE	(3 << 12)
#घोषणा QUP_BAM_MODE		(QUP_OUTPUT_BAM_MODE | QUP_INPUT_BAM_MODE)
#घोषणा QUP_UNPACK_EN		BIT(14)
#घोषणा QUP_PACK_EN		BIT(15)

#घोषणा QUP_REPACK_EN		(QUP_UNPACK_EN | QUP_PACK_EN)
#घोषणा QUP_V2_TAGS_EN		1

#घोषणा QUP_OUTPUT_BLOCK_SIZE(x)(((x) >> 0) & 0x03)
#घोषणा QUP_OUTPUT_FIFO_SIZE(x)	(((x) >> 2) & 0x07)
#घोषणा QUP_INPUT_BLOCK_SIZE(x)	(((x) >> 5) & 0x03)
#घोषणा QUP_INPUT_FIFO_SIZE(x)	(((x) >> 7) & 0x07)

/* QUP tags */
#घोषणा QUP_TAG_START		(1 << 8)
#घोषणा QUP_TAG_DATA		(2 << 8)
#घोषणा QUP_TAG_STOP		(3 << 8)
#घोषणा QUP_TAG_REC		(4 << 8)
#घोषणा QUP_BAM_INPUT_EOT		0x93
#घोषणा QUP_BAM_FLUSH_STOP		0x96

/* QUP v2 tags */
#घोषणा QUP_TAG_V2_START               0x81
#घोषणा QUP_TAG_V2_DATAWR              0x82
#घोषणा QUP_TAG_V2_DATAWR_STOP         0x83
#घोषणा QUP_TAG_V2_DATARD              0x85
#घोषणा QUP_TAG_V2_DATARD_NACK         0x86
#घोषणा QUP_TAG_V2_DATARD_STOP         0x87

/* Status, Error flags */
#घोषणा I2C_STATUS_WR_BUFFER_FULL	BIT(0)
#घोषणा I2C_STATUS_BUS_ACTIVE		BIT(8)
#घोषणा I2C_STATUS_ERROR_MASK		0x38000fc
#घोषणा QUP_STATUS_ERROR_FLAGS		0x7c

#घोषणा QUP_READ_LIMIT			256
#घोषणा SET_BIT				0x1
#घोषणा RESET_BIT			0x0
#घोषणा ONE_BYTE			0x1
#घोषणा QUP_I2C_MX_CONFIG_DURING_RUN   BIT(31)

/* Maximum transfer length क्रम single DMA descriptor */
#घोषणा MX_TX_RX_LEN			SZ_64K
#घोषणा MX_BLOCKS			(MX_TX_RX_LEN / QUP_READ_LIMIT)
/* Maximum transfer length क्रम all DMA descriptors */
#घोषणा MX_DMA_TX_RX_LEN		(2 * MX_TX_RX_LEN)
#घोषणा MX_DMA_BLOCKS			(MX_DMA_TX_RX_LEN / QUP_READ_LIMIT)

/*
 * Minimum transfer समयout क्रम i2c transfers in seconds. It will be added on
 * the top of maximum transfer समय calculated from i2c bus speed to compensate
 * the overheads.
 */
#घोषणा TOUT_MIN			2

/* Default values. Use these अगर FW query fails */
#घोषणा DEFAULT_CLK_FREQ I2C_MAX_STANDARD_MODE_FREQ
#घोषणा DEFAULT_SRC_CLK 20000000

/*
 * Max tags length (start, stop and maximum 2 bytes address) क्रम each QUP
 * data transfer
 */
#घोषणा QUP_MAX_TAGS_LEN		4
/* Max data length क्रम each DATARD tags */
#घोषणा RECV_MAX_DATA_LEN		254
/* TAG length क्रम DATA READ in RX FIFO  */
#घोषणा READ_RX_TAGS_LEN		2

अटल अचिन्हित पूर्णांक scl_freq;
module_param_named(scl_freq, scl_freq, uपूर्णांक, 0444);
MODULE_PARM_DESC(scl_freq, "SCL frequency override");

/*
 * count: no of blocks
 * pos: current block number
 * tx_tag_len: tx tag length क्रम current block
 * rx_tag_len: rx tag length क्रम current block
 * data_len: reमुख्यing data length क्रम current message
 * cur_blk_len: data length क्रम current block
 * total_tx_len: total tx length including tag bytes क्रम current QUP transfer
 * total_rx_len: total rx length including tag bytes क्रम current QUP transfer
 * tx_fअगरo_data_pos: current byte number in TX FIFO word
 * tx_fअगरo_मुक्त: number of मुक्त bytes in current QUP block ग_लिखो.
 * rx_fअगरo_data_pos: current byte number in RX FIFO word
 * fअगरo_available: number of available bytes in RX FIFO क्रम current
 *		   QUP block पढ़ो
 * tx_fअगरo_data: QUP TX FIFO ग_लिखो works on word basis (4 bytes). New byte ग_लिखो
 *		 to TX FIFO will be appended in this data and will be written to
 *		 TX FIFO when all the 4 bytes are available.
 * rx_fअगरo_data: QUP RX FIFO पढ़ो works on word basis (4 bytes). This will
 *		 contains the 4 bytes of RX data.
 * cur_data: poपूर्णांकer to tell cur data position क्रम current message
 * cur_tx_tags: poपूर्णांकer to tell cur position in tags
 * tx_tags_sent: all tx tag bytes have been written in FIFO word
 * send_last_word: क्रम tx FIFO, last word send is pending in current block
 * rx_bytes_पढ़ो: अगर all the bytes have been पढ़ो from rx FIFO.
 * rx_tags_fetched: all the rx tag bytes have been fetched from rx fअगरo word
 * is_tx_blk_mode: whether tx uses block or FIFO mode in हाल of non BAM xfer.
 * is_rx_blk_mode: whether rx uses block or FIFO mode in हाल of non BAM xfer.
 * tags: contains tx tag bytes क्रम current QUP transfer
 */
काष्ठा qup_i2c_block अणु
	पूर्णांक		count;
	पूर्णांक		pos;
	पूर्णांक		tx_tag_len;
	पूर्णांक		rx_tag_len;
	पूर्णांक		data_len;
	पूर्णांक		cur_blk_len;
	पूर्णांक		total_tx_len;
	पूर्णांक		total_rx_len;
	पूर्णांक		tx_fअगरo_data_pos;
	पूर्णांक		tx_fअगरo_मुक्त;
	पूर्णांक		rx_fअगरo_data_pos;
	पूर्णांक		fअगरo_available;
	u32		tx_fअगरo_data;
	u32		rx_fअगरo_data;
	u8		*cur_data;
	u8		*cur_tx_tags;
	bool		tx_tags_sent;
	bool		send_last_word;
	bool		rx_tags_fetched;
	bool		rx_bytes_पढ़ो;
	bool		is_tx_blk_mode;
	bool		is_rx_blk_mode;
	u8		tags[6];
पूर्ण;

काष्ठा qup_i2c_tag अणु
	u8 *start;
	dma_addr_t addr;
पूर्ण;

काष्ठा qup_i2c_bam अणु
	काष्ठा	qup_i2c_tag tag;
	काष्ठा	dma_chan *dma;
	काष्ठा	scatterlist *sg;
	अचिन्हित पूर्णांक sg_cnt;
पूर्ण;

काष्ठा qup_i2c_dev अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	काष्ठा clk		*pclk;
	काष्ठा i2c_adapter	adap;

	पूर्णांक			clk_ctl;
	पूर्णांक			out_fअगरo_sz;
	पूर्णांक			in_fअगरo_sz;
	पूर्णांक			out_blk_sz;
	पूर्णांक			in_blk_sz;

	पूर्णांक			blk_xfer_limit;
	अचिन्हित दीर्घ		one_byte_t;
	अचिन्हित दीर्घ		xfer_समयout;
	काष्ठा qup_i2c_block	blk;

	काष्ठा i2c_msg		*msg;
	/* Current posion in user message buffer */
	पूर्णांक			pos;
	/* I2C protocol errors */
	u32			bus_err;
	/* QUP core errors */
	u32			qup_err;

	/* To check अगर this is the last msg */
	bool			is_last;
	bool			is_smbus_पढ़ो;

	/* To configure when bus is in run state */
	u32			config_run;

	/* dma parameters */
	bool			is_dma;
	/* To check अगर the current transfer is using DMA */
	bool			use_dma;
	अचिन्हित पूर्णांक		max_xfer_sg_len;
	अचिन्हित पूर्णांक		tag_buf_pos;
	/* The threshold length above which block mode will be used */
	अचिन्हित पूर्णांक		blk_mode_threshold;
	काष्ठा			dma_pool *dpool;
	काष्ठा			qup_i2c_tag start_tag;
	काष्ठा			qup_i2c_bam brx;
	काष्ठा			qup_i2c_bam btx;

	काष्ठा completion	xfer;
	/* function to ग_लिखो data in tx fअगरo */
	व्योम (*ग_लिखो_tx_fअगरo)(काष्ठा qup_i2c_dev *qup);
	/* function to पढ़ो data from rx fअगरo */
	व्योम (*पढ़ो_rx_fअगरo)(काष्ठा qup_i2c_dev *qup);
	/* function to ग_लिखो tags in tx fअगरo क्रम i2c पढ़ो transfer */
	व्योम (*ग_लिखो_rx_tags)(काष्ठा qup_i2c_dev *qup);
पूर्ण;

अटल irqवापस_t qup_i2c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qup_i2c_dev *qup = dev;
	काष्ठा qup_i2c_block *blk = &qup->blk;
	u32 bus_err;
	u32 qup_err;
	u32 opflags;

	bus_err = पढ़ोl(qup->base + QUP_I2C_STATUS);
	qup_err = पढ़ोl(qup->base + QUP_ERROR_FLAGS);
	opflags = पढ़ोl(qup->base + QUP_OPERATIONAL);

	अगर (!qup->msg) अणु
		/* Clear Error पूर्णांकerrupt */
		ग_लिखोl(QUP_RESET_STATE, qup->base + QUP_STATE);
		वापस IRQ_HANDLED;
	पूर्ण

	bus_err &= I2C_STATUS_ERROR_MASK;
	qup_err &= QUP_STATUS_ERROR_FLAGS;

	/* Clear the error bits in QUP_ERROR_FLAGS */
	अगर (qup_err)
		ग_लिखोl(qup_err, qup->base + QUP_ERROR_FLAGS);

	/* Clear the error bits in QUP_I2C_STATUS */
	अगर (bus_err)
		ग_लिखोl(bus_err, qup->base + QUP_I2C_STATUS);

	/*
	 * Check क्रम BAM mode and वापसs अगर alपढ़ोy error has come क्रम current
	 * transfer. In Error हाल, someबार, QUP generates more than one
	 * पूर्णांकerrupt.
	 */
	अगर (qup->use_dma && (qup->qup_err || qup->bus_err))
		वापस IRQ_HANDLED;

	/* Reset the QUP State in हाल of error */
	अगर (qup_err || bus_err) अणु
		/*
		 * Donै t reset the QUP state in हाल of BAM mode. The BAM
		 * flush operation needs to be scheduled in transfer function
		 * which will clear the reमुख्यing schedule descriptors in BAM
		 * HW FIFO and generates the BAM पूर्णांकerrupt.
		 */
		अगर (!qup->use_dma)
			ग_लिखोl(QUP_RESET_STATE, qup->base + QUP_STATE);
		जाओ करोne;
	पूर्ण

	अगर (opflags & QUP_OUT_SVC_FLAG) अणु
		ग_लिखोl(QUP_OUT_SVC_FLAG, qup->base + QUP_OPERATIONAL);

		अगर (opflags & OUT_BLOCK_WRITE_REQ) अणु
			blk->tx_fअगरo_मुक्त += qup->out_blk_sz;
			अगर (qup->msg->flags & I2C_M_RD)
				qup->ग_लिखो_rx_tags(qup);
			अन्यथा
				qup->ग_लिखो_tx_fअगरo(qup);
		पूर्ण
	पूर्ण

	अगर (opflags & QUP_IN_SVC_FLAG) अणु
		ग_लिखोl(QUP_IN_SVC_FLAG, qup->base + QUP_OPERATIONAL);

		अगर (!blk->is_rx_blk_mode) अणु
			blk->fअगरo_available += qup->in_fअगरo_sz;
			qup->पढ़ो_rx_fअगरo(qup);
		पूर्ण अन्यथा अगर (opflags & IN_BLOCK_READ_REQ) अणु
			blk->fअगरo_available += qup->in_blk_sz;
			qup->पढ़ो_rx_fअगरo(qup);
		पूर्ण
	पूर्ण

	अगर (qup->msg->flags & I2C_M_RD) अणु
		अगर (!blk->rx_bytes_पढ़ो)
			वापस IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		/*
		 * Ideally, QUP_MAX_OUTPUT_DONE_FLAG should be checked
		 * क्रम FIFO mode also. But, QUP_MAX_OUTPUT_DONE_FLAG lags
		 * behind QUP_OUTPUT_SERVICE_FLAG someबार. The only reason
		 * of पूर्णांकerrupt क्रम ग_लिखो message in FIFO mode is
		 * QUP_MAX_OUTPUT_DONE_FLAG condition.
		 */
		अगर (blk->is_tx_blk_mode && !(opflags & QUP_MX_OUTPUT_DONE))
			वापस IRQ_HANDLED;
	पूर्ण

करोne:
	qup->qup_err = qup_err;
	qup->bus_err = bus_err;
	complete(&qup->xfer);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qup_i2c_poll_state_mask(काष्ठा qup_i2c_dev *qup,
				   u32 req_state, u32 req_mask)
अणु
	पूर्णांक retries = 1;
	u32 state;

	/*
	 * State transition takes 3 AHB घड़ीs cycles + 3 I2C master घड़ी
	 * cycles. So retry once after a 1uS delay.
	 */
	करो अणु
		state = पढ़ोl(qup->base + QUP_STATE);

		अगर (state & QUP_STATE_VALID &&
		    (state & req_mask) == req_state)
			वापस 0;

		udelay(1);
	पूर्ण जबतक (retries--);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक qup_i2c_poll_state(काष्ठा qup_i2c_dev *qup, u32 req_state)
अणु
	वापस qup_i2c_poll_state_mask(qup, req_state, QUP_STATE_MASK);
पूर्ण

अटल व्योम qup_i2c_flush(काष्ठा qup_i2c_dev *qup)
अणु
	u32 val = पढ़ोl(qup->base + QUP_STATE);

	val |= QUP_I2C_FLUSH;
	ग_लिखोl(val, qup->base + QUP_STATE);
पूर्ण

अटल पूर्णांक qup_i2c_poll_state_valid(काष्ठा qup_i2c_dev *qup)
अणु
	वापस qup_i2c_poll_state_mask(qup, 0, 0);
पूर्ण

अटल पूर्णांक qup_i2c_poll_state_i2c_master(काष्ठा qup_i2c_dev *qup)
अणु
	वापस qup_i2c_poll_state_mask(qup, QUP_I2C_MAST_GEN, QUP_I2C_MAST_GEN);
पूर्ण

अटल पूर्णांक qup_i2c_change_state(काष्ठा qup_i2c_dev *qup, u32 state)
अणु
	अगर (qup_i2c_poll_state_valid(qup) != 0)
		वापस -EIO;

	ग_लिखोl(state, qup->base + QUP_STATE);

	अगर (qup_i2c_poll_state(qup, state) != 0)
		वापस -EIO;
	वापस 0;
पूर्ण

/* Check अगर I2C bus वापसs to IDLE state */
अटल पूर्णांक qup_i2c_bus_active(काष्ठा qup_i2c_dev *qup, पूर्णांक len)
अणु
	अचिन्हित दीर्घ समयout;
	u32 status;
	पूर्णांक ret = 0;

	समयout = jअगरfies + len * 4;
	क्रम (;;) अणु
		status = पढ़ोl(qup->base + QUP_I2C_STATUS);
		अगर (!(status & I2C_STATUS_BUS_ACTIVE))
			अवरोध;

		अगर (समय_after(jअगरfies, समयout))
			ret = -ETIMEDOUT;

		usleep_range(len, len * 2);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qup_i2c_ग_लिखो_tx_fअगरo_v1(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	काष्ठा i2c_msg *msg = qup->msg;
	u32 addr = i2c_8bit_addr_from_msg(msg);
	u32 qup_tag;
	पूर्णांक idx;
	u32 val;

	अगर (qup->pos == 0) अणु
		val = QUP_TAG_START | addr;
		idx = 1;
		blk->tx_fअगरo_मुक्त--;
	पूर्ण अन्यथा अणु
		val = 0;
		idx = 0;
	पूर्ण

	जबतक (blk->tx_fअगरo_मुक्त && qup->pos < msg->len) अणु
		अगर (qup->pos == msg->len - 1)
			qup_tag = QUP_TAG_STOP;
		अन्यथा
			qup_tag = QUP_TAG_DATA;

		अगर (idx & 1)
			val |= (qup_tag | msg->buf[qup->pos]) << QUP_MSW_SHIFT;
		अन्यथा
			val = qup_tag | msg->buf[qup->pos];

		/* Write out the pair and the last odd value */
		अगर (idx & 1 || qup->pos == msg->len - 1)
			ग_लिखोl(val, qup->base + QUP_OUT_FIFO_BASE);

		qup->pos++;
		idx++;
		blk->tx_fअगरo_मुक्त--;
	पूर्ण
पूर्ण

अटल व्योम qup_i2c_set_blk_data(काष्ठा qup_i2c_dev *qup,
				 काष्ठा i2c_msg *msg)
अणु
	qup->blk.pos = 0;
	qup->blk.data_len = msg->len;
	qup->blk.count = DIV_ROUND_UP(msg->len, qup->blk_xfer_limit);
पूर्ण

अटल पूर्णांक qup_i2c_get_data_len(काष्ठा qup_i2c_dev *qup)
अणु
	पूर्णांक data_len;

	अगर (qup->blk.data_len > qup->blk_xfer_limit)
		data_len = qup->blk_xfer_limit;
	अन्यथा
		data_len = qup->blk.data_len;

	वापस data_len;
पूर्ण

अटल bool qup_i2c_check_msg_len(काष्ठा i2c_msg *msg)
अणु
	वापस ((msg->flags & I2C_M_RD) && (msg->flags & I2C_M_RECV_LEN));
पूर्ण

अटल पूर्णांक qup_i2c_set_tags_smb(u16 addr, u8 *tags, काष्ठा qup_i2c_dev *qup,
			काष्ठा i2c_msg *msg)
अणु
	पूर्णांक len = 0;

	अगर (qup->is_smbus_पढ़ो) अणु
		tags[len++] = QUP_TAG_V2_DATARD_STOP;
		tags[len++] = qup_i2c_get_data_len(qup);
	पूर्ण अन्यथा अणु
		tags[len++] = QUP_TAG_V2_START;
		tags[len++] = addr & 0xff;

		अगर (msg->flags & I2C_M_TEN)
			tags[len++] = addr >> 8;

		tags[len++] = QUP_TAG_V2_DATARD;
		/* Read 1 byte indicating the length of the SMBus message */
		tags[len++] = 1;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक qup_i2c_set_tags(u8 *tags, काष्ठा qup_i2c_dev *qup,
			    काष्ठा i2c_msg *msg)
अणु
	u16 addr = i2c_8bit_addr_from_msg(msg);
	पूर्णांक len = 0;
	पूर्णांक data_len;

	पूर्णांक last = (qup->blk.pos == (qup->blk.count - 1)) && (qup->is_last);

	/* Handle tags क्रम SMBus block पढ़ो */
	अगर (qup_i2c_check_msg_len(msg))
		वापस qup_i2c_set_tags_smb(addr, tags, qup, msg);

	अगर (qup->blk.pos == 0) अणु
		tags[len++] = QUP_TAG_V2_START;
		tags[len++] = addr & 0xff;

		अगर (msg->flags & I2C_M_TEN)
			tags[len++] = addr >> 8;
	पूर्ण

	/* Send _STOP commands क्रम the last block */
	अगर (last) अणु
		अगर (msg->flags & I2C_M_RD)
			tags[len++] = QUP_TAG_V2_DATARD_STOP;
		अन्यथा
			tags[len++] = QUP_TAG_V2_DATAWR_STOP;
	पूर्ण अन्यथा अणु
		अगर (msg->flags & I2C_M_RD)
			tags[len++] = qup->blk.pos == (qup->blk.count - 1) ?
				      QUP_TAG_V2_DATARD_NACK :
				      QUP_TAG_V2_DATARD;
		अन्यथा
			tags[len++] = QUP_TAG_V2_DATAWR;
	पूर्ण

	data_len = qup_i2c_get_data_len(qup);

	/* 0 implies 256 bytes */
	अगर (data_len == QUP_READ_LIMIT)
		tags[len++] = 0;
	अन्यथा
		tags[len++] = data_len;

	वापस len;
पूर्ण


अटल व्योम qup_i2c_bam_cb(व्योम *data)
अणु
	काष्ठा qup_i2c_dev *qup = data;

	complete(&qup->xfer);
पूर्ण

अटल पूर्णांक qup_sg_set_buf(काष्ठा scatterlist *sg, व्योम *buf,
			  अचिन्हित पूर्णांक buflen, काष्ठा qup_i2c_dev *qup,
			  पूर्णांक dir)
अणु
	पूर्णांक ret;

	sg_set_buf(sg, buf, buflen);
	ret = dma_map_sg(qup->dev, sg, 1, dir);
	अगर (!ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम qup_i2c_rel_dma(काष्ठा qup_i2c_dev *qup)
अणु
	अगर (qup->btx.dma)
		dma_release_channel(qup->btx.dma);
	अगर (qup->brx.dma)
		dma_release_channel(qup->brx.dma);
	qup->btx.dma = शून्य;
	qup->brx.dma = शून्य;
पूर्ण

अटल पूर्णांक qup_i2c_req_dma(काष्ठा qup_i2c_dev *qup)
अणु
	पूर्णांक err;

	अगर (!qup->btx.dma) अणु
		qup->btx.dma = dma_request_chan(qup->dev, "tx");
		अगर (IS_ERR(qup->btx.dma)) अणु
			err = PTR_ERR(qup->btx.dma);
			qup->btx.dma = शून्य;
			dev_err(qup->dev, "\n tx channel not available");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!qup->brx.dma) अणु
		qup->brx.dma = dma_request_chan(qup->dev, "rx");
		अगर (IS_ERR(qup->brx.dma)) अणु
			dev_err(qup->dev, "\n rx channel not available");
			err = PTR_ERR(qup->brx.dma);
			qup->brx.dma = शून्य;
			qup_i2c_rel_dma(qup);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qup_i2c_bam_make_desc(काष्ठा qup_i2c_dev *qup, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक ret = 0, limit = QUP_READ_LIMIT;
	u32 len = 0, blocks, rem;
	u32 i = 0, tlen, tx_len = 0;
	u8 *tags;

	qup->blk_xfer_limit = QUP_READ_LIMIT;
	qup_i2c_set_blk_data(qup, msg);

	blocks = qup->blk.count;
	rem = msg->len - (blocks - 1) * limit;

	अगर (msg->flags & I2C_M_RD) अणु
		जबतक (qup->blk.pos < blocks) अणु
			tlen = (i == (blocks - 1)) ? rem : limit;
			tags = &qup->start_tag.start[qup->tag_buf_pos + len];
			len += qup_i2c_set_tags(tags, qup, msg);
			qup->blk.data_len -= tlen;

			/* scratch buf to पढ़ो the start and len tags */
			ret = qup_sg_set_buf(&qup->brx.sg[qup->brx.sg_cnt++],
					     &qup->brx.tag.start[0],
					     2, qup, DMA_FROM_DEVICE);

			अगर (ret)
				वापस ret;

			ret = qup_sg_set_buf(&qup->brx.sg[qup->brx.sg_cnt++],
					     &msg->buf[limit * i],
					     tlen, qup,
					     DMA_FROM_DEVICE);
			अगर (ret)
				वापस ret;

			i++;
			qup->blk.pos = i;
		पूर्ण
		ret = qup_sg_set_buf(&qup->btx.sg[qup->btx.sg_cnt++],
				     &qup->start_tag.start[qup->tag_buf_pos],
				     len, qup, DMA_TO_DEVICE);
		अगर (ret)
			वापस ret;

		qup->tag_buf_pos += len;
	पूर्ण अन्यथा अणु
		जबतक (qup->blk.pos < blocks) अणु
			tlen = (i == (blocks - 1)) ? rem : limit;
			tags = &qup->start_tag.start[qup->tag_buf_pos + tx_len];
			len = qup_i2c_set_tags(tags, qup, msg);
			qup->blk.data_len -= tlen;

			ret = qup_sg_set_buf(&qup->btx.sg[qup->btx.sg_cnt++],
					     tags, len,
					     qup, DMA_TO_DEVICE);
			अगर (ret)
				वापस ret;

			tx_len += len;
			ret = qup_sg_set_buf(&qup->btx.sg[qup->btx.sg_cnt++],
					     &msg->buf[limit * i],
					     tlen, qup, DMA_TO_DEVICE);
			अगर (ret)
				वापस ret;
			i++;
			qup->blk.pos = i;
		पूर्ण

		qup->tag_buf_pos += tx_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qup_i2c_bam_schedule_desc(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा dma_async_tx_descriptor *txd, *rxd = शून्य;
	पूर्णांक ret = 0;
	dma_cookie_t cookie_rx, cookie_tx;
	u32 len = 0;
	u32 tx_cnt = qup->btx.sg_cnt, rx_cnt = qup->brx.sg_cnt;

	/* schedule the EOT and FLUSH I2C tags */
	len = 1;
	अगर (rx_cnt) अणु
		qup->btx.tag.start[0] = QUP_BAM_INPUT_EOT;
		len++;

		/* scratch buf to पढ़ो the BAM EOT FLUSH tags */
		ret = qup_sg_set_buf(&qup->brx.sg[rx_cnt++],
				     &qup->brx.tag.start[0],
				     1, qup, DMA_FROM_DEVICE);
		अगर (ret)
			वापस ret;
	पूर्ण

	qup->btx.tag.start[len - 1] = QUP_BAM_FLUSH_STOP;
	ret = qup_sg_set_buf(&qup->btx.sg[tx_cnt++], &qup->btx.tag.start[0],
			     len, qup, DMA_TO_DEVICE);
	अगर (ret)
		वापस ret;

	txd = dmaengine_prep_slave_sg(qup->btx.dma, qup->btx.sg, tx_cnt,
				      DMA_MEM_TO_DEV,
				      DMA_PREP_INTERRUPT | DMA_PREP_FENCE);
	अगर (!txd) अणु
		dev_err(qup->dev, "failed to get tx desc\n");
		ret = -EINVAL;
		जाओ desc_err;
	पूर्ण

	अगर (!rx_cnt) अणु
		txd->callback = qup_i2c_bam_cb;
		txd->callback_param = qup;
	पूर्ण

	cookie_tx = dmaengine_submit(txd);
	अगर (dma_submit_error(cookie_tx)) अणु
		ret = -EINVAL;
		जाओ desc_err;
	पूर्ण

	dma_async_issue_pending(qup->btx.dma);

	अगर (rx_cnt) अणु
		rxd = dmaengine_prep_slave_sg(qup->brx.dma, qup->brx.sg,
					      rx_cnt, DMA_DEV_TO_MEM,
					      DMA_PREP_INTERRUPT);
		अगर (!rxd) अणु
			dev_err(qup->dev, "failed to get rx desc\n");
			ret = -EINVAL;

			/* पात TX descriptors */
			dmaengine_terminate_all(qup->btx.dma);
			जाओ desc_err;
		पूर्ण

		rxd->callback = qup_i2c_bam_cb;
		rxd->callback_param = qup;
		cookie_rx = dmaengine_submit(rxd);
		अगर (dma_submit_error(cookie_rx)) अणु
			ret = -EINVAL;
			जाओ desc_err;
		पूर्ण

		dma_async_issue_pending(qup->brx.dma);
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&qup->xfer, qup->xfer_समयout)) अणु
		dev_err(qup->dev, "normal trans timed out\n");
		ret = -ETIMEDOUT;
	पूर्ण

	अगर (ret || qup->bus_err || qup->qup_err) अणु
		reinit_completion(&qup->xfer);

		ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
		अगर (ret) अणु
			dev_err(qup->dev, "change to run state timed out");
			जाओ desc_err;
		पूर्ण

		qup_i2c_flush(qup);

		/* रुको क्रम reमुख्यing पूर्णांकerrupts to occur */
		अगर (!रुको_क्रम_completion_समयout(&qup->xfer, HZ))
			dev_err(qup->dev, "flush timed out\n");

		ret =  (qup->bus_err & QUP_I2C_NACK_FLAG) ? -ENXIO : -EIO;
	पूर्ण

desc_err:
	dma_unmap_sg(qup->dev, qup->btx.sg, tx_cnt, DMA_TO_DEVICE);

	अगर (rx_cnt)
		dma_unmap_sg(qup->dev, qup->brx.sg, rx_cnt,
			     DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल व्योम qup_i2c_bam_clear_tag_buffers(काष्ठा qup_i2c_dev *qup)
अणु
	qup->btx.sg_cnt = 0;
	qup->brx.sg_cnt = 0;
	qup->tag_buf_pos = 0;
पूर्ण

अटल पूर्णांक qup_i2c_bam_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
			    पूर्णांक num)
अणु
	काष्ठा qup_i2c_dev *qup = i2c_get_adapdata(adap);
	पूर्णांक ret = 0;
	पूर्णांक idx = 0;

	enable_irq(qup->irq);
	ret = qup_i2c_req_dma(qup);

	अगर (ret)
		जाओ out;

	ग_लिखोl(0, qup->base + QUP_MX_INPUT_CNT);
	ग_लिखोl(0, qup->base + QUP_MX_OUTPUT_CNT);

	/* set BAM mode */
	ग_लिखोl(QUP_REPACK_EN | QUP_BAM_MODE, qup->base + QUP_IO_MODE);

	/* mask fअगरo irqs */
	ग_लिखोl((0x3 << 8), qup->base + QUP_OPERATIONAL_MASK);

	/* set RUN STATE */
	ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
	अगर (ret)
		जाओ out;

	ग_लिखोl(qup->clk_ctl, qup->base + QUP_I2C_CLK_CTL);
	qup_i2c_bam_clear_tag_buffers(qup);

	क्रम (idx = 0; idx < num; idx++) अणु
		qup->msg = msg + idx;
		qup->is_last = idx == (num - 1);

		ret = qup_i2c_bam_make_desc(qup, qup->msg);
		अगर (ret)
			अवरोध;

		/*
		 * Make DMA descriptor and schedule the BAM transfer अगर its
		 * alपढ़ोy crossed the maximum length. Since the memory क्रम all
		 * tags buffers have been taken क्रम 2 maximum possible
		 * transfers length so it will never cross the buffer actual
		 * length.
		 */
		अगर (qup->btx.sg_cnt > qup->max_xfer_sg_len ||
		    qup->brx.sg_cnt > qup->max_xfer_sg_len ||
		    qup->is_last) अणु
			ret = qup_i2c_bam_schedule_desc(qup);
			अगर (ret)
				अवरोध;

			qup_i2c_bam_clear_tag_buffers(qup);
		पूर्ण
	पूर्ण

out:
	disable_irq(qup->irq);

	qup->msg = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक qup_i2c_रुको_क्रम_complete(काष्ठा qup_i2c_dev *qup,
				     काष्ठा i2c_msg *msg)
अणु
	अचिन्हित दीर्घ left;
	पूर्णांक ret = 0;

	left = रुको_क्रम_completion_समयout(&qup->xfer, qup->xfer_समयout);
	अगर (!left) अणु
		ग_लिखोl(1, qup->base + QUP_SW_RESET);
		ret = -ETIMEDOUT;
	पूर्ण

	अगर (qup->bus_err || qup->qup_err)
		ret =  (qup->bus_err & QUP_I2C_NACK_FLAG) ? -ENXIO : -EIO;

	वापस ret;
पूर्ण

अटल व्योम qup_i2c_पढ़ो_rx_fअगरo_v1(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	काष्ठा i2c_msg *msg = qup->msg;
	u32 val = 0;
	पूर्णांक idx = 0;

	जबतक (blk->fअगरo_available && qup->pos < msg->len) अणु
		अगर ((idx & 1) == 0) अणु
			/* Reading 2 words at समय */
			val = पढ़ोl(qup->base + QUP_IN_FIFO_BASE);
			msg->buf[qup->pos++] = val & 0xFF;
		पूर्ण अन्यथा अणु
			msg->buf[qup->pos++] = val >> QUP_MSW_SHIFT;
		पूर्ण
		idx++;
		blk->fअगरo_available--;
	पूर्ण

	अगर (qup->pos == msg->len)
		blk->rx_bytes_पढ़ो = true;
पूर्ण

अटल व्योम qup_i2c_ग_लिखो_rx_tags_v1(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा i2c_msg *msg = qup->msg;
	u32 addr, len, val;

	addr = i2c_8bit_addr_from_msg(msg);

	/* 0 is used to specअगरy a length 256 (QUP_READ_LIMIT) */
	len = (msg->len == QUP_READ_LIMIT) ? 0 : msg->len;

	val = ((QUP_TAG_REC | len) << QUP_MSW_SHIFT) | QUP_TAG_START | addr;
	ग_लिखोl(val, qup->base + QUP_OUT_FIFO_BASE);
पूर्ण

अटल व्योम qup_i2c_conf_v1(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	u32 qup_config = I2C_MINI_CORE | I2C_N_VAL;
	u32 io_mode = QUP_REPACK_EN;

	blk->is_tx_blk_mode = blk->total_tx_len > qup->out_fअगरo_sz;
	blk->is_rx_blk_mode = blk->total_rx_len > qup->in_fअगरo_sz;

	अगर (blk->is_tx_blk_mode) अणु
		io_mode |= QUP_OUTPUT_BLK_MODE;
		ग_लिखोl(0, qup->base + QUP_MX_WRITE_CNT);
		ग_लिखोl(blk->total_tx_len, qup->base + QUP_MX_OUTPUT_CNT);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, qup->base + QUP_MX_OUTPUT_CNT);
		ग_लिखोl(blk->total_tx_len, qup->base + QUP_MX_WRITE_CNT);
	पूर्ण

	अगर (blk->total_rx_len) अणु
		अगर (blk->is_rx_blk_mode) अणु
			io_mode |= QUP_INPUT_BLK_MODE;
			ग_लिखोl(0, qup->base + QUP_MX_READ_CNT);
			ग_लिखोl(blk->total_rx_len, qup->base + QUP_MX_INPUT_CNT);
		पूर्ण अन्यथा अणु
			ग_लिखोl(0, qup->base + QUP_MX_INPUT_CNT);
			ग_लिखोl(blk->total_rx_len, qup->base + QUP_MX_READ_CNT);
		पूर्ण
	पूर्ण अन्यथा अणु
		qup_config |= QUP_NO_INPUT;
	पूर्ण

	ग_लिखोl(qup_config, qup->base + QUP_CONFIG);
	ग_लिखोl(io_mode, qup->base + QUP_IO_MODE);
पूर्ण

अटल व्योम qup_i2c_clear_blk_v1(काष्ठा qup_i2c_block *blk)
अणु
	blk->tx_fअगरo_मुक्त = 0;
	blk->fअगरo_available = 0;
	blk->rx_bytes_पढ़ो = false;
पूर्ण

अटल पूर्णांक qup_i2c_conf_xfer_v1(काष्ठा qup_i2c_dev *qup, bool is_rx)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	पूर्णांक ret;

	qup_i2c_clear_blk_v1(blk);
	qup_i2c_conf_v1(qup);
	ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
	अगर (ret)
		वापस ret;

	ग_लिखोl(qup->clk_ctl, qup->base + QUP_I2C_CLK_CTL);

	ret = qup_i2c_change_state(qup, QUP_PAUSE_STATE);
	अगर (ret)
		वापस ret;

	reinit_completion(&qup->xfer);
	enable_irq(qup->irq);
	अगर (!blk->is_tx_blk_mode) अणु
		blk->tx_fअगरo_मुक्त = qup->out_fअगरo_sz;

		अगर (is_rx)
			qup_i2c_ग_लिखो_rx_tags_v1(qup);
		अन्यथा
			qup_i2c_ग_लिखो_tx_fअगरo_v1(qup);
	पूर्ण

	ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
	अगर (ret)
		जाओ err;

	ret = qup_i2c_रुको_क्रम_complete(qup, qup->msg);
	अगर (ret)
		जाओ err;

	ret = qup_i2c_bus_active(qup, ONE_BYTE);

err:
	disable_irq(qup->irq);
	वापस ret;
पूर्ण

अटल पूर्णांक qup_i2c_ग_लिखो_one(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा i2c_msg *msg = qup->msg;
	काष्ठा qup_i2c_block *blk = &qup->blk;

	qup->pos = 0;
	blk->total_tx_len = msg->len + 1;
	blk->total_rx_len = 0;

	वापस qup_i2c_conf_xfer_v1(qup, false);
पूर्ण

अटल पूर्णांक qup_i2c_पढ़ो_one(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;

	qup->pos = 0;
	blk->total_tx_len = 2;
	blk->total_rx_len = qup->msg->len;

	वापस qup_i2c_conf_xfer_v1(qup, true);
पूर्ण

अटल पूर्णांक qup_i2c_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg msgs[],
			पूर्णांक num)
अणु
	काष्ठा qup_i2c_dev *qup = i2c_get_adapdata(adap);
	पूर्णांक ret, idx;

	ret = pm_runसमय_get_sync(qup->dev);
	अगर (ret < 0)
		जाओ out;

	qup->bus_err = 0;
	qup->qup_err = 0;

	ग_लिखोl(1, qup->base + QUP_SW_RESET);
	ret = qup_i2c_poll_state(qup, QUP_RESET_STATE);
	अगर (ret)
		जाओ out;

	/* Configure QUP as I2C mini core */
	ग_लिखोl(I2C_MINI_CORE | I2C_N_VAL, qup->base + QUP_CONFIG);

	क्रम (idx = 0; idx < num; idx++) अणु
		अगर (qup_i2c_poll_state_i2c_master(qup)) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण

		अगर (qup_i2c_check_msg_len(&msgs[idx])) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		qup->msg = &msgs[idx];
		अगर (msgs[idx].flags & I2C_M_RD)
			ret = qup_i2c_पढ़ो_one(qup);
		अन्यथा
			ret = qup_i2c_ग_लिखो_one(qup);

		अगर (ret)
			अवरोध;

		ret = qup_i2c_change_state(qup, QUP_RESET_STATE);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret == 0)
		ret = num;
out:

	pm_runसमय_mark_last_busy(qup->dev);
	pm_runसमय_put_स्वतःsuspend(qup->dev);

	वापस ret;
पूर्ण

/*
 * Configure रेजिस्टरs related with reconfiguration during run and call it
 * beक्रमe each i2c sub transfer.
 */
अटल व्योम qup_i2c_conf_count_v2(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	u32 qup_config = I2C_MINI_CORE | I2C_N_VAL_V2;

	अगर (blk->is_tx_blk_mode)
		ग_लिखोl(qup->config_run | blk->total_tx_len,
		       qup->base + QUP_MX_OUTPUT_CNT);
	अन्यथा
		ग_लिखोl(qup->config_run | blk->total_tx_len,
		       qup->base + QUP_MX_WRITE_CNT);

	अगर (blk->total_rx_len) अणु
		अगर (blk->is_rx_blk_mode)
			ग_लिखोl(qup->config_run | blk->total_rx_len,
			       qup->base + QUP_MX_INPUT_CNT);
		अन्यथा
			ग_लिखोl(qup->config_run | blk->total_rx_len,
			       qup->base + QUP_MX_READ_CNT);
	पूर्ण अन्यथा अणु
		qup_config |= QUP_NO_INPUT;
	पूर्ण

	ग_लिखोl(qup_config, qup->base + QUP_CONFIG);
पूर्ण

/*
 * Configure रेजिस्टरs related with transfer mode (FIFO/Block)
 * beक्रमe starting of i2c transfer. It will be called only once in
 * QUP RESET state.
 */
अटल व्योम qup_i2c_conf_mode_v2(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	u32 io_mode = QUP_REPACK_EN;

	अगर (blk->is_tx_blk_mode) अणु
		io_mode |= QUP_OUTPUT_BLK_MODE;
		ग_लिखोl(0, qup->base + QUP_MX_WRITE_CNT);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, qup->base + QUP_MX_OUTPUT_CNT);
	पूर्ण

	अगर (blk->is_rx_blk_mode) अणु
		io_mode |= QUP_INPUT_BLK_MODE;
		ग_लिखोl(0, qup->base + QUP_MX_READ_CNT);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, qup->base + QUP_MX_INPUT_CNT);
	पूर्ण

	ग_लिखोl(io_mode, qup->base + QUP_IO_MODE);
पूर्ण

/* Clear required variables beक्रमe starting of any QUP v2 sub transfer. */
अटल व्योम qup_i2c_clear_blk_v2(काष्ठा qup_i2c_block *blk)
अणु
	blk->send_last_word = false;
	blk->tx_tags_sent = false;
	blk->tx_fअगरo_data = 0;
	blk->tx_fअगरo_data_pos = 0;
	blk->tx_fअगरo_मुक्त = 0;

	blk->rx_tags_fetched = false;
	blk->rx_bytes_पढ़ो = false;
	blk->rx_fअगरo_data = 0;
	blk->rx_fअगरo_data_pos = 0;
	blk->fअगरo_available = 0;
पूर्ण

/* Receive data from RX FIFO क्रम पढ़ो message in QUP v2 i2c transfer. */
अटल व्योम qup_i2c_recv_data(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	पूर्णांक j;

	क्रम (j = blk->rx_fअगरo_data_pos;
	     blk->cur_blk_len && blk->fअगरo_available;
	     blk->cur_blk_len--, blk->fअगरo_available--) अणु
		अगर (j == 0)
			blk->rx_fअगरo_data = पढ़ोl(qup->base + QUP_IN_FIFO_BASE);

		*(blk->cur_data++) = blk->rx_fअगरo_data;
		blk->rx_fअगरo_data >>= 8;

		अगर (j == 3)
			j = 0;
		अन्यथा
			j++;
	पूर्ण

	blk->rx_fअगरo_data_pos = j;
पूर्ण

/* Receive tags क्रम पढ़ो message in QUP v2 i2c transfer. */
अटल व्योम qup_i2c_recv_tags(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;

	blk->rx_fअगरo_data = पढ़ोl(qup->base + QUP_IN_FIFO_BASE);
	blk->rx_fअगरo_data >>= blk->rx_tag_len  * 8;
	blk->rx_fअगरo_data_pos = blk->rx_tag_len;
	blk->fअगरo_available -= blk->rx_tag_len;
पूर्ण

/*
 * Read the data and tags from RX FIFO. Since in पढ़ो हाल, the tags will be
 * preceded by received data bytes so
 * 1. Check अगर rx_tags_fetched is false i.e. the start of QUP block so receive
 *    all tag bytes and discard that.
 * 2. Read the data from RX FIFO. When all the data bytes have been पढ़ो then
 *    set rx_bytes_पढ़ो to true.
 */
अटल व्योम qup_i2c_पढ़ो_rx_fअगरo_v2(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;

	अगर (!blk->rx_tags_fetched) अणु
		qup_i2c_recv_tags(qup);
		blk->rx_tags_fetched = true;
	पूर्ण

	qup_i2c_recv_data(qup);
	अगर (!blk->cur_blk_len)
		blk->rx_bytes_पढ़ो = true;
पूर्ण

/*
 * Write bytes in TX FIFO क्रम ग_लिखो message in QUP v2 i2c transfer. QUP TX FIFO
 * ग_लिखो works on word basis (4 bytes). Append new data byte ग_लिखो क्रम TX FIFO
 * in tx_fअगरo_data and ग_लिखो to TX FIFO when all the 4 bytes are present.
 */
अटल व्योम
qup_i2c_ग_लिखो_blk_data(काष्ठा qup_i2c_dev *qup, u8 **data, अचिन्हित पूर्णांक *len)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	अचिन्हित पूर्णांक j;

	क्रम (j = blk->tx_fअगरo_data_pos; *len && blk->tx_fअगरo_मुक्त;
	     (*len)--, blk->tx_fअगरo_मुक्त--) अणु
		blk->tx_fअगरo_data |= *(*data)++ << (j * 8);
		अगर (j == 3) अणु
			ग_लिखोl(blk->tx_fअगरo_data,
			       qup->base + QUP_OUT_FIFO_BASE);
			blk->tx_fअगरo_data = 0x0;
			j = 0;
		पूर्ण अन्यथा अणु
			j++;
		पूर्ण
	पूर्ण

	blk->tx_fअगरo_data_pos = j;
पूर्ण

/* Transfer tags क्रम पढ़ो message in QUP v2 i2c transfer. */
अटल व्योम qup_i2c_ग_लिखो_rx_tags_v2(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;

	qup_i2c_ग_लिखो_blk_data(qup, &blk->cur_tx_tags, &blk->tx_tag_len);
	अगर (blk->tx_fअगरo_data_pos)
		ग_लिखोl(blk->tx_fअगरo_data, qup->base + QUP_OUT_FIFO_BASE);
पूर्ण

/*
 * Write the data and tags in TX FIFO. Since in ग_लिखो हाल, both tags and data
 * need to be written and QUP ग_लिखो tags can have maximum 256 data length, so
 *
 * 1. Check अगर tx_tags_sent is false i.e. the start of QUP block so ग_लिखो the
 *    tags to TX FIFO and set tx_tags_sent to true.
 * 2. Check अगर send_last_word is true. It will be set when last few data bytes
 *    (less than 4 bytes) are reamining to be written in FIFO because of no FIFO
 *    space. All this data bytes are available in tx_fअगरo_data so ग_लिखो this
 *    in FIFO.
 * 3. Write the data to TX FIFO and check क्रम cur_blk_len. If it is non zero
 *    then more data is pending otherwise following 3 हालs can be possible
 *    a. अगर tx_fअगरo_data_pos is zero i.e. all the data bytes in this block
 *       have been written in TX FIFO so nothing अन्यथा is required.
 *    b. tx_fअगरo_मुक्त is non zero i.e tx FIFO is मुक्त so copy the reमुख्यing data
 *       from tx_fअगरo_data to tx FIFO. Since, qup_i2c_ग_लिखो_blk_data करो ग_लिखो
 *	 in 4 bytes and FIFO space is in multiple of 4 bytes so tx_fअगरo_मुक्त
 *       will be always greater than or equal to 4 bytes.
 *    c. tx_fअगरo_मुक्त is zero. In this हाल, last few bytes (less than 4
 *       bytes) are copied to tx_fअगरo_data but couldn't be sent because of
 *       FIFO full so make send_last_word true.
 */
अटल व्योम qup_i2c_ग_लिखो_tx_fअगरo_v2(काष्ठा qup_i2c_dev *qup)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;

	अगर (!blk->tx_tags_sent) अणु
		qup_i2c_ग_लिखो_blk_data(qup, &blk->cur_tx_tags,
				       &blk->tx_tag_len);
		blk->tx_tags_sent = true;
	पूर्ण

	अगर (blk->send_last_word)
		जाओ send_last_word;

	qup_i2c_ग_लिखो_blk_data(qup, &blk->cur_data, &blk->cur_blk_len);
	अगर (!blk->cur_blk_len) अणु
		अगर (!blk->tx_fअगरo_data_pos)
			वापस;

		अगर (blk->tx_fअगरo_मुक्त)
			जाओ send_last_word;

		blk->send_last_word = true;
	पूर्ण

	वापस;

send_last_word:
	ग_लिखोl(blk->tx_fअगरo_data, qup->base + QUP_OUT_FIFO_BASE);
पूर्ण

/*
 * Main transfer function which पढ़ो or ग_लिखो i2c data.
 * The QUP v2 supports reconfiguration during run in which multiple i2c sub
 * transfers can be scheduled.
 */
अटल पूर्णांक
qup_i2c_conf_xfer_v2(काष्ठा qup_i2c_dev *qup, bool is_rx, bool is_first,
		     bool change_छोड़ो_state)
अणु
	काष्ठा qup_i2c_block *blk = &qup->blk;
	काष्ठा i2c_msg *msg = qup->msg;
	पूर्णांक ret;

	/*
	 * Check अगर its SMBus Block पढ़ो क्रम which the top level पढ़ो will be
	 * करोne पूर्णांकo 2 QUP पढ़ोs. One with message length 1 जबतक other one is
	 * with actual length.
	 */
	अगर (qup_i2c_check_msg_len(msg)) अणु
		अगर (qup->is_smbus_पढ़ो) अणु
			/*
			 * If the message length is alपढ़ोy पढ़ो in
			 * the first byte of the buffer, account क्रम
			 * that by setting the offset
			 */
			blk->cur_data += 1;
			is_first = false;
		पूर्ण अन्यथा अणु
			change_छोड़ो_state = false;
		पूर्ण
	पूर्ण

	qup->config_run = is_first ? 0 : QUP_I2C_MX_CONFIG_DURING_RUN;

	qup_i2c_clear_blk_v2(blk);
	qup_i2c_conf_count_v2(qup);

	/* If it is first sub transfer, then configure i2c bus घड़ीs */
	अगर (is_first) अणु
		ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
		अगर (ret)
			वापस ret;

		ग_लिखोl(qup->clk_ctl, qup->base + QUP_I2C_CLK_CTL);

		ret = qup_i2c_change_state(qup, QUP_PAUSE_STATE);
		अगर (ret)
			वापस ret;
	पूर्ण

	reinit_completion(&qup->xfer);
	enable_irq(qup->irq);
	/*
	 * In FIFO mode, tx FIFO can be written directly जबतक in block mode the
	 * it will be written after getting OUT_BLOCK_WRITE_REQ पूर्णांकerrupt
	 */
	अगर (!blk->is_tx_blk_mode) अणु
		blk->tx_fअगरo_मुक्त = qup->out_fअगरo_sz;

		अगर (is_rx)
			qup_i2c_ग_लिखो_rx_tags_v2(qup);
		अन्यथा
			qup_i2c_ग_लिखो_tx_fअगरo_v2(qup);
	पूर्ण

	ret = qup_i2c_change_state(qup, QUP_RUN_STATE);
	अगर (ret)
		जाओ err;

	ret = qup_i2c_रुको_क्रम_complete(qup, msg);
	अगर (ret)
		जाओ err;

	/* Move to छोड़ो state क्रम all the transfers, except last one */
	अगर (change_छोड़ो_state) अणु
		ret = qup_i2c_change_state(qup, QUP_PAUSE_STATE);
		अगर (ret)
			जाओ err;
	पूर्ण

err:
	disable_irq(qup->irq);
	वापस ret;
पूर्ण

/*
 * Transfer one पढ़ो/ग_लिखो message in i2c transfer. It splits the message पूर्णांकo
 * multiple of blk_xfer_limit data length blocks and schedule each
 * QUP block inभागidually.
 */
अटल पूर्णांक qup_i2c_xfer_v2_msg(काष्ठा qup_i2c_dev *qup, पूर्णांक msg_id, bool is_rx)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक data_len, i;
	काष्ठा i2c_msg *msg = qup->msg;
	काष्ठा qup_i2c_block *blk = &qup->blk;
	u8 *msg_buf = msg->buf;

	qup->blk_xfer_limit = is_rx ? RECV_MAX_DATA_LEN : QUP_READ_LIMIT;
	qup_i2c_set_blk_data(qup, msg);

	क्रम (i = 0; i < blk->count; i++) अणु
		data_len =  qup_i2c_get_data_len(qup);
		blk->pos = i;
		blk->cur_tx_tags = blk->tags;
		blk->cur_blk_len = data_len;
		blk->tx_tag_len =
			qup_i2c_set_tags(blk->cur_tx_tags, qup, qup->msg);

		blk->cur_data = msg_buf;

		अगर (is_rx) अणु
			blk->total_tx_len = blk->tx_tag_len;
			blk->rx_tag_len = 2;
			blk->total_rx_len = blk->rx_tag_len + data_len;
		पूर्ण अन्यथा अणु
			blk->total_tx_len = blk->tx_tag_len + data_len;
			blk->total_rx_len = 0;
		पूर्ण

		ret = qup_i2c_conf_xfer_v2(qup, is_rx, !msg_id && !i,
					   !qup->is_last || i < blk->count - 1);
		अगर (ret)
			वापस ret;

		/* Handle SMBus block पढ़ो length */
		अगर (qup_i2c_check_msg_len(msg) && msg->len == 1 &&
		    !qup->is_smbus_पढ़ो) अणु
			अगर (msg->buf[0] > I2C_SMBUS_BLOCK_MAX)
				वापस -EPROTO;

			msg->len = msg->buf[0];
			qup->is_smbus_पढ़ो = true;
			ret = qup_i2c_xfer_v2_msg(qup, msg_id, true);
			qup->is_smbus_पढ़ो = false;
			अगर (ret)
				वापस ret;

			msg->len += 1;
		पूर्ण

		msg_buf += data_len;
		blk->data_len -= qup->blk_xfer_limit;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * QUP v2 supports 3 modes
 * Programmed IO using FIFO mode : Less than FIFO size
 * Programmed IO using Block mode : Greater than FIFO size
 * DMA using BAM : Appropriate क्रम any transaction size but the address should
 *		   be DMA applicable
 *
 * This function determines the mode which will be used क्रम this transfer. An
 * i2c transfer contains multiple message. Following are the rules to determine
 * the mode used.
 * 1. Determine complete length, maximum tx and rx length क्रम complete transfer.
 * 2. If complete transfer length is greater than fअगरo size then use the DMA
 *    mode.
 * 3. In FIFO or block mode, tx and rx can operate in dअगरferent mode so check
 *    क्रम maximum tx and rx length to determine mode.
 */
अटल पूर्णांक
qup_i2c_determine_mode_v2(काष्ठा qup_i2c_dev *qup,
			  काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	पूर्णांक idx;
	bool no_dma = false;
	अचिन्हित पूर्णांक max_tx_len = 0, max_rx_len = 0, total_len = 0;

	/* All i2c_msgs should be transferred using either dma or cpu */
	क्रम (idx = 0; idx < num; idx++) अणु
		अगर (msgs[idx].flags & I2C_M_RD)
			max_rx_len = max_t(अचिन्हित पूर्णांक, max_rx_len,
					   msgs[idx].len);
		अन्यथा
			max_tx_len = max_t(अचिन्हित पूर्णांक, max_tx_len,
					   msgs[idx].len);

		अगर (is_vदो_स्मृति_addr(msgs[idx].buf))
			no_dma = true;

		total_len += msgs[idx].len;
	पूर्ण

	अगर (!no_dma && qup->is_dma &&
	    (total_len > qup->out_fअगरo_sz || total_len > qup->in_fअगरo_sz)) अणु
		qup->use_dma = true;
	पूर्ण अन्यथा अणु
		qup->blk.is_tx_blk_mode = max_tx_len > qup->out_fअगरo_sz -
			QUP_MAX_TAGS_LEN;
		qup->blk.is_rx_blk_mode = max_rx_len > qup->in_fअगरo_sz -
			READ_RX_TAGS_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qup_i2c_xfer_v2(काष्ठा i2c_adapter *adap,
			   काष्ठा i2c_msg msgs[],
			   पूर्णांक num)
अणु
	काष्ठा qup_i2c_dev *qup = i2c_get_adapdata(adap);
	पूर्णांक ret, idx = 0;

	qup->bus_err = 0;
	qup->qup_err = 0;

	ret = pm_runसमय_get_sync(qup->dev);
	अगर (ret < 0)
		जाओ out;

	ret = qup_i2c_determine_mode_v2(qup, msgs, num);
	अगर (ret)
		जाओ out;

	ग_लिखोl(1, qup->base + QUP_SW_RESET);
	ret = qup_i2c_poll_state(qup, QUP_RESET_STATE);
	अगर (ret)
		जाओ out;

	/* Configure QUP as I2C mini core */
	ग_लिखोl(I2C_MINI_CORE | I2C_N_VAL_V2, qup->base + QUP_CONFIG);
	ग_लिखोl(QUP_V2_TAGS_EN, qup->base + QUP_I2C_MASTER_GEN);

	अगर (qup_i2c_poll_state_i2c_master(qup)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (qup->use_dma) अणु
		reinit_completion(&qup->xfer);
		ret = qup_i2c_bam_xfer(adap, &msgs[0], num);
		qup->use_dma = false;
	पूर्ण अन्यथा अणु
		qup_i2c_conf_mode_v2(qup);

		क्रम (idx = 0; idx < num; idx++) अणु
			qup->msg = &msgs[idx];
			qup->is_last = idx == (num - 1);

			ret = qup_i2c_xfer_v2_msg(qup, idx,
					!!(msgs[idx].flags & I2C_M_RD));
			अगर (ret)
				अवरोध;
		पूर्ण
		qup->msg = शून्य;
	पूर्ण

	अगर (!ret)
		ret = qup_i2c_bus_active(qup, ONE_BYTE);

	अगर (!ret)
		qup_i2c_change_state(qup, QUP_RESET_STATE);

	अगर (ret == 0)
		ret = num;
out:
	pm_runसमय_mark_last_busy(qup->dev);
	pm_runसमय_put_स्वतःsuspend(qup->dev);

	वापस ret;
पूर्ण

अटल u32 qup_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL_ALL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm qup_i2c_algo = अणु
	.master_xfer	= qup_i2c_xfer,
	.functionality	= qup_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm qup_i2c_algo_v2 = अणु
	.master_xfer	= qup_i2c_xfer_v2,
	.functionality	= qup_i2c_func,
पूर्ण;

/*
 * The QUP block will issue a NACK and STOP on the bus when reaching
 * the end of the पढ़ो, the length of the पढ़ो is specअगरied as one byte
 * which limits the possible पढ़ो to 256 (QUP_READ_LIMIT) bytes.
 */
अटल स्थिर काष्ठा i2c_adapter_quirks qup_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
	.max_पढ़ो_len = QUP_READ_LIMIT,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks qup_i2c_quirks_v2 = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल व्योम qup_i2c_enable_घड़ीs(काष्ठा qup_i2c_dev *qup)
अणु
	clk_prepare_enable(qup->clk);
	clk_prepare_enable(qup->pclk);
पूर्ण

अटल व्योम qup_i2c_disable_घड़ीs(काष्ठा qup_i2c_dev *qup)
अणु
	u32 config;

	qup_i2c_change_state(qup, QUP_RESET_STATE);
	clk_disable_unprepare(qup->clk);
	config = पढ़ोl(qup->base + QUP_CONFIG);
	config |= QUP_CLOCK_AUTO_GATE;
	ग_लिखोl(config, qup->base + QUP_CONFIG);
	clk_disable_unprepare(qup->pclk);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id qup_i2c_acpi_match[] = अणु
	अणु "QCOM8010"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, qup_i2c_acpi_match);

अटल पूर्णांक qup_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर पूर्णांक blk_sizes[] = अणु4, 16, 32पूर्ण;
	काष्ठा qup_i2c_dev *qup;
	अचिन्हित दीर्घ one_bit_t;
	u32 io_mode, hw_ver, size;
	पूर्णांक ret, fs_भाग, hs_भाग;
	u32 src_clk_freq = DEFAULT_SRC_CLK;
	u32 clk_freq = DEFAULT_CLK_FREQ;
	पूर्णांक blocks;
	bool is_qup_v1;

	qup = devm_kzalloc(&pdev->dev, माप(*qup), GFP_KERNEL);
	अगर (!qup)
		वापस -ENOMEM;

	qup->dev = &pdev->dev;
	init_completion(&qup->xfer);
	platक्रमm_set_drvdata(pdev, qup);

	अगर (scl_freq) अणु
		dev_notice(qup->dev, "Using override frequency of %u\n", scl_freq);
		clk_freq = scl_freq;
	पूर्ण अन्यथा अणु
		ret = device_property_पढ़ो_u32(qup->dev, "clock-frequency", &clk_freq);
		अगर (ret) अणु
			dev_notice(qup->dev, "using default clock-frequency %d",
				DEFAULT_CLK_FREQ);
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(pdev->dev.of_node, "qcom,i2c-qup-v1.1.1")) अणु
		qup->adap.algo = &qup_i2c_algo;
		qup->adap.quirks = &qup_i2c_quirks;
		is_qup_v1 = true;
	पूर्ण अन्यथा अणु
		qup->adap.algo = &qup_i2c_algo_v2;
		qup->adap.quirks = &qup_i2c_quirks_v2;
		is_qup_v1 = false;
		अगर (acpi_match_device(qup_i2c_acpi_match, qup->dev))
			जाओ nodma;
		अन्यथा
			ret = qup_i2c_req_dma(qup);

		अगर (ret == -EPROBE_DEFER)
			जाओ fail_dma;
		अन्यथा अगर (ret != 0)
			जाओ nodma;

		qup->max_xfer_sg_len = (MX_BLOCKS << 1);
		blocks = (MX_DMA_BLOCKS << 1) + 1;
		qup->btx.sg = devm_kसुस्मृति(&pdev->dev,
					   blocks, माप(*qup->btx.sg),
					   GFP_KERNEL);
		अगर (!qup->btx.sg) अणु
			ret = -ENOMEM;
			जाओ fail_dma;
		पूर्ण
		sg_init_table(qup->btx.sg, blocks);

		qup->brx.sg = devm_kसुस्मृति(&pdev->dev,
					   blocks, माप(*qup->brx.sg),
					   GFP_KERNEL);
		अगर (!qup->brx.sg) अणु
			ret = -ENOMEM;
			जाओ fail_dma;
		पूर्ण
		sg_init_table(qup->brx.sg, blocks);

		/* 2 tag bytes क्रम each block + 5 क्रम start, stop tags */
		size = blocks * 2 + 5;

		qup->start_tag.start = devm_kzalloc(&pdev->dev,
						    size, GFP_KERNEL);
		अगर (!qup->start_tag.start) अणु
			ret = -ENOMEM;
			जाओ fail_dma;
		पूर्ण

		qup->brx.tag.start = devm_kzalloc(&pdev->dev, 2, GFP_KERNEL);
		अगर (!qup->brx.tag.start) अणु
			ret = -ENOMEM;
			जाओ fail_dma;
		पूर्ण

		qup->btx.tag.start = devm_kzalloc(&pdev->dev, 2, GFP_KERNEL);
		अगर (!qup->btx.tag.start) अणु
			ret = -ENOMEM;
			जाओ fail_dma;
		पूर्ण
		qup->is_dma = true;
	पूर्ण

nodma:
	/* We support frequencies up to FAST Mode Plus (1MHz) */
	अगर (!clk_freq || clk_freq > I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		dev_err(qup->dev, "clock frequency not supported %d\n",
			clk_freq);
		वापस -EINVAL;
	पूर्ण

	qup->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(qup->base))
		वापस PTR_ERR(qup->base);

	qup->irq = platक्रमm_get_irq(pdev, 0);
	अगर (qup->irq < 0)
		वापस qup->irq;

	अगर (has_acpi_companion(qup->dev)) अणु
		ret = device_property_पढ़ो_u32(qup->dev,
				"src-clock-hz", &src_clk_freq);
		अगर (ret) अणु
			dev_notice(qup->dev, "using default src-clock-hz %d",
				DEFAULT_SRC_CLK);
		पूर्ण
		ACPI_COMPANION_SET(&qup->adap.dev, ACPI_COMPANION(qup->dev));
	पूर्ण अन्यथा अणु
		qup->clk = devm_clk_get(qup->dev, "core");
		अगर (IS_ERR(qup->clk)) अणु
			dev_err(qup->dev, "Could not get core clock\n");
			वापस PTR_ERR(qup->clk);
		पूर्ण

		qup->pclk = devm_clk_get(qup->dev, "iface");
		अगर (IS_ERR(qup->pclk)) अणु
			dev_err(qup->dev, "Could not get iface clock\n");
			वापस PTR_ERR(qup->pclk);
		पूर्ण
		qup_i2c_enable_घड़ीs(qup);
		src_clk_freq = clk_get_rate(qup->clk);
	पूर्ण

	/*
	 * Bootloaders might leave a pending पूर्णांकerrupt on certain QUP's,
	 * so we reset the core beक्रमe रेजिस्टरing क्रम पूर्णांकerrupts.
	 */
	ग_लिखोl(1, qup->base + QUP_SW_RESET);
	ret = qup_i2c_poll_state_valid(qup);
	अगर (ret)
		जाओ fail;

	ret = devm_request_irq(qup->dev, qup->irq, qup_i2c_पूर्णांकerrupt,
			       IRQF_TRIGGER_HIGH, "i2c_qup", qup);
	अगर (ret) अणु
		dev_err(qup->dev, "Request %d IRQ failed\n", qup->irq);
		जाओ fail;
	पूर्ण
	disable_irq(qup->irq);

	hw_ver = पढ़ोl(qup->base + QUP_HW_VERSION);
	dev_dbg(qup->dev, "Revision %x\n", hw_ver);

	io_mode = पढ़ोl(qup->base + QUP_IO_MODE);

	/*
	 * The block/fअगरo size w.r.t. 'actual data' is 1/2 due to 'tag'
	 * associated with each byte written/received
	 */
	size = QUP_OUTPUT_BLOCK_SIZE(io_mode);
	अगर (size >= ARRAY_SIZE(blk_sizes)) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण
	qup->out_blk_sz = blk_sizes[size];

	size = QUP_INPUT_BLOCK_SIZE(io_mode);
	अगर (size >= ARRAY_SIZE(blk_sizes)) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण
	qup->in_blk_sz = blk_sizes[size];

	अगर (is_qup_v1) अणु
		/*
		 * in QUP v1, QUP_CONFIG uses N as 15 i.e 16 bits स्थिरitutes a
		 * single transfer but the block size is in bytes so भागide the
		 * in_blk_sz and out_blk_sz by 2
		 */
		qup->in_blk_sz /= 2;
		qup->out_blk_sz /= 2;
		qup->ग_लिखो_tx_fअगरo = qup_i2c_ग_लिखो_tx_fअगरo_v1;
		qup->पढ़ो_rx_fअगरo = qup_i2c_पढ़ो_rx_fअगरo_v1;
		qup->ग_लिखो_rx_tags = qup_i2c_ग_लिखो_rx_tags_v1;
	पूर्ण अन्यथा अणु
		qup->ग_लिखो_tx_fअगरo = qup_i2c_ग_लिखो_tx_fअगरo_v2;
		qup->पढ़ो_rx_fअगरo = qup_i2c_पढ़ो_rx_fअगरo_v2;
		qup->ग_लिखो_rx_tags = qup_i2c_ग_लिखो_rx_tags_v2;
	पूर्ण

	size = QUP_OUTPUT_FIFO_SIZE(io_mode);
	qup->out_fअगरo_sz = qup->out_blk_sz * (2 << size);

	size = QUP_INPUT_FIFO_SIZE(io_mode);
	qup->in_fअगरo_sz = qup->in_blk_sz * (2 << size);

	hs_भाग = 3;
	अगर (clk_freq <= I2C_MAX_STANDARD_MODE_FREQ) अणु
		fs_भाग = ((src_clk_freq / clk_freq) / 2) - 3;
		qup->clk_ctl = (hs_भाग << 8) | (fs_भाग & 0xff);
	पूर्ण अन्यथा अणु
		/* 33%/66% duty cycle */
		fs_भाग = ((src_clk_freq / clk_freq) - 6) * 2 / 3;
		qup->clk_ctl = ((fs_भाग / 2) << 16) | (hs_भाग << 8) | (fs_भाग & 0xff);
	पूर्ण

	/*
	 * Time it takes क्रम a byte to be घड़ीed out on the bus.
	 * Each byte takes 9 घड़ी cycles (8 bits + 1 ack).
	 */
	one_bit_t = (USEC_PER_SEC / clk_freq) + 1;
	qup->one_byte_t = one_bit_t * 9;
	qup->xfer_समयout = TOUT_MIN * HZ +
		usecs_to_jअगरfies(MX_DMA_TX_RX_LEN * qup->one_byte_t);

	dev_dbg(qup->dev, "IN:block:%d, fifo:%d, OUT:block:%d, fifo:%d\n",
		qup->in_blk_sz, qup->in_fअगरo_sz,
		qup->out_blk_sz, qup->out_fअगरo_sz);

	i2c_set_adapdata(&qup->adap, qup);
	qup->adap.dev.parent = qup->dev;
	qup->adap.dev.of_node = pdev->dev.of_node;
	qup->is_last = true;

	strlcpy(qup->adap.name, "QUP I2C adapter", माप(qup->adap.name));

	pm_runसमय_set_स्वतःsuspend_delay(qup->dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(qup->dev);
	pm_runसमय_set_active(qup->dev);
	pm_runसमय_enable(qup->dev);

	ret = i2c_add_adapter(&qup->adap);
	अगर (ret)
		जाओ fail_runसमय;

	वापस 0;

fail_runसमय:
	pm_runसमय_disable(qup->dev);
	pm_runसमय_set_suspended(qup->dev);
fail:
	qup_i2c_disable_घड़ीs(qup);
fail_dma:
	अगर (qup->btx.dma)
		dma_release_channel(qup->btx.dma);
	अगर (qup->brx.dma)
		dma_release_channel(qup->brx.dma);
	वापस ret;
पूर्ण

अटल पूर्णांक qup_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qup_i2c_dev *qup = platक्रमm_get_drvdata(pdev);

	अगर (qup->is_dma) अणु
		dma_release_channel(qup->btx.dma);
		dma_release_channel(qup->brx.dma);
	पूर्ण

	disable_irq(qup->irq);
	qup_i2c_disable_घड़ीs(qup);
	i2c_del_adapter(&qup->adap);
	pm_runसमय_disable(qup->dev);
	pm_runसमय_set_suspended(qup->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक qup_i2c_pm_suspend_runसमय(काष्ठा device *device)
अणु
	काष्ठा qup_i2c_dev *qup = dev_get_drvdata(device);

	dev_dbg(device, "pm_runtime: suspending...\n");
	qup_i2c_disable_घड़ीs(qup);
	वापस 0;
पूर्ण

अटल पूर्णांक qup_i2c_pm_resume_runसमय(काष्ठा device *device)
अणु
	काष्ठा qup_i2c_dev *qup = dev_get_drvdata(device);

	dev_dbg(device, "pm_runtime: resuming...\n");
	qup_i2c_enable_घड़ीs(qup);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qup_i2c_suspend(काष्ठा device *device)
अणु
	अगर (!pm_runसमय_suspended(device))
		वापस qup_i2c_pm_suspend_runसमय(device);
	वापस 0;
पूर्ण

अटल पूर्णांक qup_i2c_resume(काष्ठा device *device)
अणु
	qup_i2c_pm_resume_runसमय(device);
	pm_runसमय_mark_last_busy(device);
	pm_request_स्वतःsuspend(device);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops qup_i2c_qup_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(
		qup_i2c_suspend,
		qup_i2c_resume)
	SET_RUNTIME_PM_OPS(
		qup_i2c_pm_suspend_runसमय,
		qup_i2c_pm_resume_runसमय,
		शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id qup_i2c_dt_match[] = अणु
	अणु .compatible = "qcom,i2c-qup-v1.1.1" पूर्ण,
	अणु .compatible = "qcom,i2c-qup-v2.1.1" पूर्ण,
	अणु .compatible = "qcom,i2c-qup-v2.2.1" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qup_i2c_dt_match);

अटल काष्ठा platक्रमm_driver qup_i2c_driver = अणु
	.probe  = qup_i2c_probe,
	.हटाओ = qup_i2c_हटाओ,
	.driver = अणु
		.name = "i2c_qup",
		.pm = &qup_i2c_qup_pm_ops,
		.of_match_table = qup_i2c_dt_match,
		.acpi_match_table = ACPI_PTR(qup_i2c_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qup_i2c_driver);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c_qup");
