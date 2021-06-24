<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/qcom-geni-se.h>
#समावेश <linux/spinlock.h>

#घोषणा SE_I2C_TX_TRANS_LEN		0x26c
#घोषणा SE_I2C_RX_TRANS_LEN		0x270
#घोषणा SE_I2C_SCL_COUNTERS		0x278

#घोषणा SE_I2C_ERR  (M_CMD_OVERRUN_EN | M_ILLEGAL_CMD_EN | M_CMD_FAILURE_EN |\
			M_GP_IRQ_1_EN | M_GP_IRQ_3_EN | M_GP_IRQ_4_EN)
#घोषणा SE_I2C_ABORT		BIT(1)

/* M_CMD OP codes क्रम I2C */
#घोषणा I2C_WRITE		0x1
#घोषणा I2C_READ		0x2
#घोषणा I2C_WRITE_READ		0x3
#घोषणा I2C_ADDR_ONLY		0x4
#घोषणा I2C_BUS_CLEAR		0x6
#घोषणा I2C_STOP_ON_BUS		0x7
/* M_CMD params क्रम I2C */
#घोषणा PRE_CMD_DELAY		BIT(0)
#घोषणा TIMESTAMP_BEFORE	BIT(1)
#घोषणा STOP_STRETCH		BIT(2)
#घोषणा TIMESTAMP_AFTER		BIT(3)
#घोषणा POST_COMMAND_DELAY	BIT(4)
#घोषणा IGNORE_ADD_NACK		BIT(6)
#घोषणा READ_FINISHED_WITH_ACK	BIT(7)
#घोषणा BYPASS_ADDR_PHASE	BIT(8)
#घोषणा SLV_ADDR_MSK		GENMASK(15, 9)
#घोषणा SLV_ADDR_SHFT		9
/* I2C SCL COUNTER fields */
#घोषणा HIGH_COUNTER_MSK	GENMASK(29, 20)
#घोषणा HIGH_COUNTER_SHFT	20
#घोषणा LOW_COUNTER_MSK		GENMASK(19, 10)
#घोषणा LOW_COUNTER_SHFT	10
#घोषणा CYCLE_COUNTER_MSK	GENMASK(9, 0)

क्रमागत geni_i2c_err_code अणु
	GP_IRQ0,
	NACK,
	GP_IRQ2,
	BUS_PROTO,
	ARB_LOST,
	GP_IRQ5,
	GENI_OVERRUN,
	GENI_ILLEGAL_CMD,
	GENI_ABORT_DONE,
	GENI_TIMEOUT,
पूर्ण;

#घोषणा DM_I2C_CB_ERR		((BIT(NACK) | BIT(BUS_PROTO) | BIT(ARB_LOST)) \
									<< 5)

#घोषणा I2C_AUTO_SUSPEND_DELAY	250
#घोषणा KHZ(freq)		(1000 * freq)
#घोषणा PACKING_BYTES_PW	4

#घोषणा ABORT_TIMEOUT		HZ
#घोषणा XFER_TIMEOUT		HZ
#घोषणा RST_TIMEOUT		HZ

काष्ठा geni_i2c_dev अणु
	काष्ठा geni_se se;
	u32 tx_wm;
	पूर्णांक irq;
	पूर्णांक err;
	काष्ठा i2c_adapter adap;
	काष्ठा completion करोne;
	काष्ठा i2c_msg *cur;
	पूर्णांक cur_wr;
	पूर्णांक cur_rd;
	spinlock_t lock;
	u32 clk_freq_out;
	स्थिर काष्ठा geni_i2c_clk_fld *clk_fld;
	पूर्णांक suspended;
	व्योम *dma_buf;
	माप_प्रकार xfer_len;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा geni_i2c_err_log अणु
	पूर्णांक err;
	स्थिर अक्षर *msg;
पूर्ण;

अटल स्थिर काष्ठा geni_i2c_err_log gi2c_log[] = अणु
	[GP_IRQ0] = अणु-EIO, "Unknown I2C err GP_IRQ0"पूर्ण,
	[NACK] = अणु-ENXIO, "NACK: slv unresponsive, check its power/reset-ln"पूर्ण,
	[GP_IRQ2] = अणु-EIO, "Unknown I2C err GP IRQ2"पूर्ण,
	[BUS_PROTO] = अणु-EPROTO, "Bus proto err, noisy/unexpected start/stop"पूर्ण,
	[ARB_LOST] = अणु-EAGAIN, "Bus arbitration lost, clock line undriveable"पूर्ण,
	[GP_IRQ5] = अणु-EIO, "Unknown I2C err GP IRQ5"पूर्ण,
	[GENI_OVERRUN] = अणु-EIO, "Cmd overrun, check GENI cmd-state machine"पूर्ण,
	[GENI_ILLEGAL_CMD] = अणु-EIO, "Illegal cmd, check GENI cmd-state machine"पूर्ण,
	[GENI_ABORT_DONE] = अणु-ETIMEDOUT, "Abort after timeout successful"पूर्ण,
	[GENI_TIMEOUT] = अणु-ETIMEDOUT, "I2C TXN timed out"पूर्ण,
पूर्ण;

काष्ठा geni_i2c_clk_fld अणु
	u32	clk_freq_out;
	u8	clk_भाग;
	u8	t_high_cnt;
	u8	t_low_cnt;
	u8	t_cycle_cnt;
पूर्ण;

/*
 * Hardware uses the underlying क्रमmula to calculate समय periods of
 * SCL घड़ी cycle. Firmware uses some additional cycles excluded from the
 * below क्रमmula and it is confirmed that the समय periods are within
 * specअगरication limits.
 *
 * समय of high period of SCL: t_high = (t_high_cnt * clk_भाग) / source_घड़ी
 * समय of low period of SCL: t_low = (t_low_cnt * clk_भाग) / source_घड़ी
 * समय of full period of SCL: t_cycle = (t_cycle_cnt * clk_भाग) / source_घड़ी
 * clk_freq_out = t / t_cycle
 * source_घड़ी = 19.2 MHz
 */
अटल स्थिर काष्ठा geni_i2c_clk_fld geni_i2c_clk_map[] = अणु
	अणुKHZ(100), 7, 10, 11, 26पूर्ण,
	अणुKHZ(400), 2,  5, 12, 24पूर्ण,
	अणुKHZ(1000), 1, 3,  9, 18पूर्ण,
पूर्ण;

अटल पूर्णांक geni_i2c_clk_map_idx(काष्ठा geni_i2c_dev *gi2c)
अणु
	पूर्णांक i;
	स्थिर काष्ठा geni_i2c_clk_fld *itr = geni_i2c_clk_map;

	क्रम (i = 0; i < ARRAY_SIZE(geni_i2c_clk_map); i++, itr++) अणु
		अगर (itr->clk_freq_out == gi2c->clk_freq_out) अणु
			gi2c->clk_fld = itr;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम qcom_geni_i2c_conf(काष्ठा geni_i2c_dev *gi2c)
अणु
	स्थिर काष्ठा geni_i2c_clk_fld *itr = gi2c->clk_fld;
	u32 val;

	ग_लिखोl_relaxed(0, gi2c->se.base + SE_GENI_CLK_SEL);

	val = (itr->clk_भाग << CLK_DIV_SHFT) | SER_CLK_EN;
	ग_लिखोl_relaxed(val, gi2c->se.base + GENI_SER_M_CLK_CFG);

	val = itr->t_high_cnt << HIGH_COUNTER_SHFT;
	val |= itr->t_low_cnt << LOW_COUNTER_SHFT;
	val |= itr->t_cycle_cnt;
	ग_लिखोl_relaxed(val, gi2c->se.base + SE_I2C_SCL_COUNTERS);
पूर्ण

अटल व्योम geni_i2c_err_misc(काष्ठा geni_i2c_dev *gi2c)
अणु
	u32 m_cmd = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_M_CMD0);
	u32 m_stat = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_M_IRQ_STATUS);
	u32 geni_s = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_STATUS);
	u32 geni_ios = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_IOS);
	u32 dma = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_DMA_MODE_EN);
	u32 rx_st, tx_st;

	अगर (dma) अणु
		rx_st = पढ़ोl_relaxed(gi2c->se.base + SE_DMA_RX_IRQ_STAT);
		tx_st = पढ़ोl_relaxed(gi2c->se.base + SE_DMA_TX_IRQ_STAT);
	पूर्ण अन्यथा अणु
		rx_st = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_RX_FIFO_STATUS);
		tx_st = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_TX_FIFO_STATUS);
	पूर्ण
	dev_dbg(gi2c->se.dev, "DMA:%d tx_stat:0x%x, rx_stat:0x%x, irq-stat:0x%x\n",
		dma, tx_st, rx_st, m_stat);
	dev_dbg(gi2c->se.dev, "m_cmd:0x%x, geni_status:0x%x, geni_ios:0x%x\n",
		m_cmd, geni_s, geni_ios);
पूर्ण

अटल व्योम geni_i2c_err(काष्ठा geni_i2c_dev *gi2c, पूर्णांक err)
अणु
	अगर (!gi2c->err)
		gi2c->err = gi2c_log[err].err;
	अगर (gi2c->cur)
		dev_dbg(gi2c->se.dev, "len:%d, slv-addr:0x%x, RD/WR:%d\n",
			gi2c->cur->len, gi2c->cur->addr, gi2c->cur->flags);

	अगर (err != NACK && err != GENI_ABORT_DONE) अणु
		dev_err(gi2c->se.dev, "%s\n", gi2c_log[err].msg);
		geni_i2c_err_misc(gi2c);
	पूर्ण
पूर्ण

अटल irqवापस_t geni_i2c_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा geni_i2c_dev *gi2c = dev;
	व्योम __iomem *base = gi2c->se.base;
	पूर्णांक j, p;
	u32 m_stat;
	u32 rx_st;
	u32 dm_tx_st;
	u32 dm_rx_st;
	u32 dma;
	u32 val;
	काष्ठा i2c_msg *cur;

	spin_lock(&gi2c->lock);
	m_stat = पढ़ोl_relaxed(base + SE_GENI_M_IRQ_STATUS);
	rx_st = पढ़ोl_relaxed(base + SE_GENI_RX_FIFO_STATUS);
	dm_tx_st = पढ़ोl_relaxed(base + SE_DMA_TX_IRQ_STAT);
	dm_rx_st = पढ़ोl_relaxed(base + SE_DMA_RX_IRQ_STAT);
	dma = पढ़ोl_relaxed(base + SE_GENI_DMA_MODE_EN);
	cur = gi2c->cur;

	अगर (!cur ||
	    m_stat & (M_CMD_FAILURE_EN | M_CMD_ABORT_EN) ||
	    dm_rx_st & (DM_I2C_CB_ERR)) अणु
		अगर (m_stat & M_GP_IRQ_1_EN)
			geni_i2c_err(gi2c, NACK);
		अगर (m_stat & M_GP_IRQ_3_EN)
			geni_i2c_err(gi2c, BUS_PROTO);
		अगर (m_stat & M_GP_IRQ_4_EN)
			geni_i2c_err(gi2c, ARB_LOST);
		अगर (m_stat & M_CMD_OVERRUN_EN)
			geni_i2c_err(gi2c, GENI_OVERRUN);
		अगर (m_stat & M_ILLEGAL_CMD_EN)
			geni_i2c_err(gi2c, GENI_ILLEGAL_CMD);
		अगर (m_stat & M_CMD_ABORT_EN)
			geni_i2c_err(gi2c, GENI_ABORT_DONE);
		अगर (m_stat & M_GP_IRQ_0_EN)
			geni_i2c_err(gi2c, GP_IRQ0);

		/* Disable the TX Watermark पूर्णांकerrupt to stop TX */
		अगर (!dma)
			ग_लिखोl_relaxed(0, base + SE_GENI_TX_WATERMARK_REG);
	पूर्ण अन्यथा अगर (dma) अणु
		dev_dbg(gi2c->se.dev, "i2c dma tx:0x%x, dma rx:0x%x\n",
			dm_tx_st, dm_rx_st);
	पूर्ण अन्यथा अगर (cur->flags & I2C_M_RD &&
		   m_stat & (M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN)) अणु
		u32 rxcnt = rx_st & RX_FIFO_WC_MSK;

		क्रम (j = 0; j < rxcnt; j++) अणु
			p = 0;
			val = पढ़ोl_relaxed(base + SE_GENI_RX_FIFOn);
			जबतक (gi2c->cur_rd < cur->len && p < माप(val)) अणु
				cur->buf[gi2c->cur_rd++] = val & 0xff;
				val >>= 8;
				p++;
			पूर्ण
			अगर (gi2c->cur_rd == cur->len)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!(cur->flags & I2C_M_RD) &&
		   m_stat & M_TX_FIFO_WATERMARK_EN) अणु
		क्रम (j = 0; j < gi2c->tx_wm; j++) अणु
			u32 temp;

			val = 0;
			p = 0;
			जबतक (gi2c->cur_wr < cur->len && p < माप(val)) अणु
				temp = cur->buf[gi2c->cur_wr++];
				val |= temp << (p * 8);
				p++;
			पूर्ण
			ग_लिखोl_relaxed(val, base + SE_GENI_TX_FIFOn);
			/* TX Complete, Disable the TX Watermark पूर्णांकerrupt */
			अगर (gi2c->cur_wr == cur->len) अणु
				ग_लिखोl_relaxed(0, base + SE_GENI_TX_WATERMARK_REG);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (m_stat)
		ग_लिखोl_relaxed(m_stat, base + SE_GENI_M_IRQ_CLEAR);

	अगर (dma && dm_tx_st)
		ग_लिखोl_relaxed(dm_tx_st, base + SE_DMA_TX_IRQ_CLR);
	अगर (dma && dm_rx_st)
		ग_लिखोl_relaxed(dm_rx_st, base + SE_DMA_RX_IRQ_CLR);

	/* अगर this is err with करोne-bit not set, handle that through समयout. */
	अगर (m_stat & M_CMD_DONE_EN || m_stat & M_CMD_ABORT_EN ||
	    dm_tx_st & TX_DMA_DONE || dm_tx_st & TX_RESET_DONE ||
	    dm_rx_st & RX_DMA_DONE || dm_rx_st & RX_RESET_DONE)
		complete(&gi2c->करोne);

	spin_unlock(&gi2c->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम geni_i2c_पात_xfer(काष्ठा geni_i2c_dev *gi2c)
अणु
	u32 val;
	अचिन्हित दीर्घ समय_left = ABORT_TIMEOUT;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gi2c->lock, flags);
	geni_i2c_err(gi2c, GENI_TIMEOUT);
	gi2c->cur = शून्य;
	geni_se_पात_m_cmd(&gi2c->se);
	spin_unlock_irqrestore(&gi2c->lock, flags);
	करो अणु
		समय_left = रुको_क्रम_completion_समयout(&gi2c->करोne, समय_left);
		val = पढ़ोl_relaxed(gi2c->se.base + SE_GENI_M_IRQ_STATUS);
	पूर्ण जबतक (!(val & M_CMD_ABORT_EN) && समय_left);

	अगर (!(val & M_CMD_ABORT_EN))
		dev_err(gi2c->se.dev, "Timeout abort_m_cmd\n");
पूर्ण

अटल व्योम geni_i2c_rx_fsm_rst(काष्ठा geni_i2c_dev *gi2c)
अणु
	u32 val;
	अचिन्हित दीर्घ समय_left = RST_TIMEOUT;

	ग_लिखोl_relaxed(1, gi2c->se.base + SE_DMA_RX_FSM_RST);
	करो अणु
		समय_left = रुको_क्रम_completion_समयout(&gi2c->करोne, समय_left);
		val = पढ़ोl_relaxed(gi2c->se.base + SE_DMA_RX_IRQ_STAT);
	पूर्ण जबतक (!(val & RX_RESET_DONE) && समय_left);

	अगर (!(val & RX_RESET_DONE))
		dev_err(gi2c->se.dev, "Timeout resetting RX_FSM\n");
पूर्ण

अटल व्योम geni_i2c_tx_fsm_rst(काष्ठा geni_i2c_dev *gi2c)
अणु
	u32 val;
	अचिन्हित दीर्घ समय_left = RST_TIMEOUT;

	ग_लिखोl_relaxed(1, gi2c->se.base + SE_DMA_TX_FSM_RST);
	करो अणु
		समय_left = रुको_क्रम_completion_समयout(&gi2c->करोne, समय_left);
		val = पढ़ोl_relaxed(gi2c->se.base + SE_DMA_TX_IRQ_STAT);
	पूर्ण जबतक (!(val & TX_RESET_DONE) && समय_left);

	अगर (!(val & TX_RESET_DONE))
		dev_err(gi2c->se.dev, "Timeout resetting TX_FSM\n");
पूर्ण

अटल व्योम geni_i2c_rx_msg_cleanup(काष्ठा geni_i2c_dev *gi2c,
				     काष्ठा i2c_msg *cur)
अणु
	gi2c->cur_rd = 0;
	अगर (gi2c->dma_buf) अणु
		अगर (gi2c->err)
			geni_i2c_rx_fsm_rst(gi2c);
		geni_se_rx_dma_unprep(&gi2c->se, gi2c->dma_addr, gi2c->xfer_len);
		i2c_put_dma_safe_msg_buf(gi2c->dma_buf, cur, !gi2c->err);
	पूर्ण
पूर्ण

अटल व्योम geni_i2c_tx_msg_cleanup(काष्ठा geni_i2c_dev *gi2c,
				     काष्ठा i2c_msg *cur)
अणु
	gi2c->cur_wr = 0;
	अगर (gi2c->dma_buf) अणु
		अगर (gi2c->err)
			geni_i2c_tx_fsm_rst(gi2c);
		geni_se_tx_dma_unprep(&gi2c->se, gi2c->dma_addr, gi2c->xfer_len);
		i2c_put_dma_safe_msg_buf(gi2c->dma_buf, cur, !gi2c->err);
	पूर्ण
पूर्ण

अटल पूर्णांक geni_i2c_rx_one_msg(काष्ठा geni_i2c_dev *gi2c, काष्ठा i2c_msg *msg,
				u32 m_param)
अणु
	dma_addr_t rx_dma = 0;
	अचिन्हित दीर्घ समय_left;
	व्योम *dma_buf;
	काष्ठा geni_se *se = &gi2c->se;
	माप_प्रकार len = msg->len;
	काष्ठा i2c_msg *cur;

	dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);
	अगर (dma_buf)
		geni_se_select_mode(se, GENI_SE_DMA);
	अन्यथा
		geni_se_select_mode(se, GENI_SE_FIFO);

	ग_लिखोl_relaxed(len, se->base + SE_I2C_RX_TRANS_LEN);
	geni_se_setup_m_cmd(se, I2C_READ, m_param);

	अगर (dma_buf && geni_se_rx_dma_prep(se, dma_buf, len, &rx_dma)) अणु
		geni_se_select_mode(se, GENI_SE_FIFO);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, false);
		dma_buf = शून्य;
	पूर्ण अन्यथा अणु
		gi2c->xfer_len = len;
		gi2c->dma_addr = rx_dma;
		gi2c->dma_buf = dma_buf;
	पूर्ण

	cur = gi2c->cur;
	समय_left = रुको_क्रम_completion_समयout(&gi2c->करोne, XFER_TIMEOUT);
	अगर (!समय_left)
		geni_i2c_पात_xfer(gi2c);

	geni_i2c_rx_msg_cleanup(gi2c, cur);

	वापस gi2c->err;
पूर्ण

अटल पूर्णांक geni_i2c_tx_one_msg(काष्ठा geni_i2c_dev *gi2c, काष्ठा i2c_msg *msg,
				u32 m_param)
अणु
	dma_addr_t tx_dma = 0;
	अचिन्हित दीर्घ समय_left;
	व्योम *dma_buf;
	काष्ठा geni_se *se = &gi2c->se;
	माप_प्रकार len = msg->len;
	काष्ठा i2c_msg *cur;

	dma_buf = i2c_get_dma_safe_msg_buf(msg, 32);
	अगर (dma_buf)
		geni_se_select_mode(se, GENI_SE_DMA);
	अन्यथा
		geni_se_select_mode(se, GENI_SE_FIFO);

	ग_लिखोl_relaxed(len, se->base + SE_I2C_TX_TRANS_LEN);
	geni_se_setup_m_cmd(se, I2C_WRITE, m_param);

	अगर (dma_buf && geni_se_tx_dma_prep(se, dma_buf, len, &tx_dma)) अणु
		geni_se_select_mode(se, GENI_SE_FIFO);
		i2c_put_dma_safe_msg_buf(dma_buf, msg, false);
		dma_buf = शून्य;
	पूर्ण अन्यथा अणु
		gi2c->xfer_len = len;
		gi2c->dma_addr = tx_dma;
		gi2c->dma_buf = dma_buf;
	पूर्ण

	अगर (!dma_buf) /* Get FIFO IRQ */
		ग_लिखोl_relaxed(1, se->base + SE_GENI_TX_WATERMARK_REG);

	cur = gi2c->cur;
	समय_left = रुको_क्रम_completion_समयout(&gi2c->करोne, XFER_TIMEOUT);
	अगर (!समय_left)
		geni_i2c_पात_xfer(gi2c);

	geni_i2c_tx_msg_cleanup(gi2c, cur);

	वापस gi2c->err;
पूर्ण

अटल पूर्णांक geni_i2c_xfer(काष्ठा i2c_adapter *adap,
			 काष्ठा i2c_msg msgs[],
			 पूर्णांक num)
अणु
	काष्ठा geni_i2c_dev *gi2c = i2c_get_adapdata(adap);
	पूर्णांक i, ret;

	gi2c->err = 0;
	reinit_completion(&gi2c->करोne);
	ret = pm_runसमय_get_sync(gi2c->se.dev);
	अगर (ret < 0) अणु
		dev_err(gi2c->se.dev, "error turning SE resources:%d\n", ret);
		pm_runसमय_put_noidle(gi2c->se.dev);
		/* Set device in suspended since resume failed */
		pm_runसमय_set_suspended(gi2c->se.dev);
		वापस ret;
	पूर्ण

	qcom_geni_i2c_conf(gi2c);
	क्रम (i = 0; i < num; i++) अणु
		u32 m_param = i < (num - 1) ? STOP_STRETCH : 0;

		m_param |= ((msgs[i].addr << SLV_ADDR_SHFT) & SLV_ADDR_MSK);

		gi2c->cur = &msgs[i];
		अगर (msgs[i].flags & I2C_M_RD)
			ret = geni_i2c_rx_one_msg(gi2c, &msgs[i], m_param);
		अन्यथा
			ret = geni_i2c_tx_one_msg(gi2c, &msgs[i], m_param);

		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (ret == 0)
		ret = num;

	pm_runसमय_mark_last_busy(gi2c->se.dev);
	pm_runसमय_put_स्वतःsuspend(gi2c->se.dev);
	gi2c->cur = शून्य;
	gi2c->err = 0;
	वापस ret;
पूर्ण

अटल u32 geni_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm geni_i2c_algo = अणु
	.master_xfer	= geni_i2c_xfer,
	.functionality	= geni_i2c_func,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id geni_i2c_acpi_match[] = अणु
	अणु "QCOM0220"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, geni_i2c_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक geni_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा geni_i2c_dev *gi2c;
	काष्ठा resource *res;
	u32 proto, tx_depth;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;

	gi2c = devm_kzalloc(dev, माप(*gi2c), GFP_KERNEL);
	अगर (!gi2c)
		वापस -ENOMEM;

	gi2c->se.dev = dev;
	gi2c->se.wrapper = dev_get_drvdata(dev->parent);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gi2c->se.base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(gi2c->se.base))
		वापस PTR_ERR(gi2c->se.base);

	gi2c->se.clk = devm_clk_get(dev, "se");
	अगर (IS_ERR(gi2c->se.clk) && !has_acpi_companion(dev))
		वापस PTR_ERR(gi2c->se.clk);

	ret = device_property_पढ़ो_u32(dev, "clock-frequency",
				       &gi2c->clk_freq_out);
	अगर (ret) अणु
		dev_info(dev, "Bus frequency not specified, default to 100kHz.\n");
		gi2c->clk_freq_out = KHZ(100);
	पूर्ण

	अगर (has_acpi_companion(dev))
		ACPI_COMPANION_SET(&gi2c->adap.dev, ACPI_COMPANION(dev));

	gi2c->irq = platक्रमm_get_irq(pdev, 0);
	अगर (gi2c->irq < 0)
		वापस gi2c->irq;

	ret = geni_i2c_clk_map_idx(gi2c);
	अगर (ret) अणु
		dev_err(dev, "Invalid clk frequency %d Hz: %d\n",
			gi2c->clk_freq_out, ret);
		वापस ret;
	पूर्ण

	gi2c->adap.algo = &geni_i2c_algo;
	init_completion(&gi2c->करोne);
	spin_lock_init(&gi2c->lock);
	platक्रमm_set_drvdata(pdev, gi2c);
	ret = devm_request_irq(dev, gi2c->irq, geni_i2c_irq, 0,
			       dev_name(dev), gi2c);
	अगर (ret) अणु
		dev_err(dev, "Request_irq failed:%d: err:%d\n",
			gi2c->irq, ret);
		वापस ret;
	पूर्ण
	/* Disable the पूर्णांकerrupt so that the प्रणाली can enter low-घातer mode */
	disable_irq(gi2c->irq);
	i2c_set_adapdata(&gi2c->adap, gi2c);
	gi2c->adap.dev.parent = dev;
	gi2c->adap.dev.of_node = dev->of_node;
	strlcpy(gi2c->adap.name, "Geni-I2C", माप(gi2c->adap.name));

	ret = geni_icc_get(&gi2c->se, "qup-memory");
	अगर (ret)
		वापस ret;
	/*
	 * Set the bus quota क्रम core and cpu to a reasonable value क्रम
	 * रेजिस्टर access.
	 * Set quota क्रम DDR based on bus speed.
	 */
	gi2c->se.icc_paths[GENI_TO_CORE].avg_bw = GENI_DEFAULT_BW;
	gi2c->se.icc_paths[CPU_TO_GENI].avg_bw = GENI_DEFAULT_BW;
	gi2c->se.icc_paths[GENI_TO_DDR].avg_bw = Bps_to_icc(gi2c->clk_freq_out);

	ret = geni_icc_set_bw(&gi2c->se);
	अगर (ret)
		वापस ret;

	ret = geni_se_resources_on(&gi2c->se);
	अगर (ret) अणु
		dev_err(dev, "Error turning on resources %d\n", ret);
		वापस ret;
	पूर्ण
	proto = geni_se_पढ़ो_proto(&gi2c->se);
	tx_depth = geni_se_get_tx_fअगरo_depth(&gi2c->se);
	अगर (proto != GENI_SE_I2C) अणु
		dev_err(dev, "Invalid proto %d\n", proto);
		geni_se_resources_off(&gi2c->se);
		वापस -ENXIO;
	पूर्ण
	gi2c->tx_wm = tx_depth - 1;
	geni_se_init(&gi2c->se, gi2c->tx_wm, tx_depth);
	geni_se_config_packing(&gi2c->se, BITS_PER_BYTE, PACKING_BYTES_PW,
							true, true, true);
	ret = geni_se_resources_off(&gi2c->se);
	अगर (ret) अणु
		dev_err(dev, "Error turning off resources %d\n", ret);
		वापस ret;
	पूर्ण

	ret = geni_icc_disable(&gi2c->se);
	अगर (ret)
		वापस ret;

	dev_dbg(dev, "i2c fifo/se-dma mode. fifo depth:%d\n", tx_depth);

	gi2c->suspended = 1;
	pm_runसमय_set_suspended(gi2c->se.dev);
	pm_runसमय_set_स्वतःsuspend_delay(gi2c->se.dev, I2C_AUTO_SUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(gi2c->se.dev);
	pm_runसमय_enable(gi2c->se.dev);

	ret = i2c_add_adapter(&gi2c->adap);
	अगर (ret) अणु
		dev_err(dev, "Error adding i2c adapter %d\n", ret);
		pm_runसमय_disable(gi2c->se.dev);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "Geni-I2C adaptor successfully added\n");

	वापस 0;
पूर्ण

अटल पूर्णांक geni_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा geni_i2c_dev *gi2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&gi2c->adap);
	pm_runसमय_disable(gi2c->se.dev);
	वापस 0;
पूर्ण

अटल व्योम geni_i2c_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा geni_i2c_dev *gi2c = platक्रमm_get_drvdata(pdev);

	/* Make client i2c transfers start failing */
	i2c_mark_adapter_suspended(&gi2c->adap);
पूर्ण

अटल पूर्णांक __maybe_unused geni_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा geni_i2c_dev *gi2c = dev_get_drvdata(dev);

	disable_irq(gi2c->irq);
	ret = geni_se_resources_off(&gi2c->se);
	अगर (ret) अणु
		enable_irq(gi2c->irq);
		वापस ret;

	पूर्ण अन्यथा अणु
		gi2c->suspended = 1;
	पूर्ण

	वापस geni_icc_disable(&gi2c->se);
पूर्ण

अटल पूर्णांक __maybe_unused geni_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा geni_i2c_dev *gi2c = dev_get_drvdata(dev);

	ret = geni_icc_enable(&gi2c->se);
	अगर (ret)
		वापस ret;

	ret = geni_se_resources_on(&gi2c->se);
	अगर (ret)
		वापस ret;

	enable_irq(gi2c->irq);
	gi2c->suspended = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused geni_i2c_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा geni_i2c_dev *gi2c = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&gi2c->adap);

	अगर (!gi2c->suspended) अणु
		geni_i2c_runसमय_suspend(dev);
		pm_runसमय_disable(dev);
		pm_runसमय_set_suspended(dev);
		pm_runसमय_enable(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused geni_i2c_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा geni_i2c_dev *gi2c = dev_get_drvdata(dev);

	i2c_mark_adapter_resumed(&gi2c->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops geni_i2c_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(geni_i2c_suspend_noirq, geni_i2c_resume_noirq)
	SET_RUNTIME_PM_OPS(geni_i2c_runसमय_suspend, geni_i2c_runसमय_resume,
									शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id geni_i2c_dt_match[] = अणु
	अणु .compatible = "qcom,geni-i2c" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, geni_i2c_dt_match);

अटल काष्ठा platक्रमm_driver geni_i2c_driver = अणु
	.probe  = geni_i2c_probe,
	.हटाओ = geni_i2c_हटाओ,
	.shutकरोwn = geni_i2c_shutकरोwn,
	.driver = अणु
		.name = "geni_i2c",
		.pm = &geni_i2c_pm_ops,
		.of_match_table = geni_i2c_dt_match,
		.acpi_match_table = ACPI_PTR(geni_i2c_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(geni_i2c_driver);

MODULE_DESCRIPTION("I2C Controller Driver for GENI based QUP cores");
MODULE_LICENSE("GPL v2");
