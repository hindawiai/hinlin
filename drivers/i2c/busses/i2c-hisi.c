<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HiSilicon I2C Controller Driver क्रम Kunpeng SoC
 *
 * Copyright (c) 2021 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#घोषणा HISI_I2C_FRAME_CTRL		0x0000
#घोषणा   HISI_I2C_FRAME_CTRL_SPEED_MODE	GENMASK(1, 0)
#घोषणा   HISI_I2C_FRAME_CTRL_ADDR_TEN	BIT(2)
#घोषणा HISI_I2C_SLV_ADDR		0x0004
#घोषणा   HISI_I2C_SLV_ADDR_VAL		GENMASK(9, 0)
#घोषणा   HISI_I2C_SLV_ADDR_GC_S_MODE	BIT(10)
#घोषणा   HISI_I2C_SLV_ADDR_GC_S_EN	BIT(11)
#घोषणा HISI_I2C_CMD_TXDATA		0x0008
#घोषणा   HISI_I2C_CMD_TXDATA_DATA	GENMASK(7, 0)
#घोषणा   HISI_I2C_CMD_TXDATA_RW	BIT(8)
#घोषणा   HISI_I2C_CMD_TXDATA_P_EN	BIT(9)
#घोषणा   HISI_I2C_CMD_TXDATA_SR_EN	BIT(10)
#घोषणा HISI_I2C_RXDATA			0x000c
#घोषणा   HISI_I2C_RXDATA_DATA		GENMASK(7, 0)
#घोषणा HISI_I2C_SS_SCL_HCNT		0x0010
#घोषणा HISI_I2C_SS_SCL_LCNT		0x0014
#घोषणा HISI_I2C_FS_SCL_HCNT		0x0018
#घोषणा HISI_I2C_FS_SCL_LCNT		0x001c
#घोषणा HISI_I2C_HS_SCL_HCNT		0x0020
#घोषणा HISI_I2C_HS_SCL_LCNT		0x0024
#घोषणा HISI_I2C_FIFO_CTRL		0x0028
#घोषणा   HISI_I2C_FIFO_RX_CLR		BIT(0)
#घोषणा   HISI_I2C_FIFO_TX_CLR		BIT(1)
#घोषणा   HISI_I2C_FIFO_RX_AF_THRESH	GENMASK(7, 2)
#घोषणा   HISI_I2C_FIFO_TX_AE_THRESH	GENMASK(13, 8)
#घोषणा HISI_I2C_FIFO_STATE		0x002c
#घोषणा   HISI_I2C_FIFO_STATE_RX_RERR	BIT(0)
#घोषणा   HISI_I2C_FIFO_STATE_RX_WERR	BIT(1)
#घोषणा   HISI_I2C_FIFO_STATE_RX_EMPTY	BIT(3)
#घोषणा   HISI_I2C_FIFO_STATE_TX_RERR	BIT(6)
#घोषणा   HISI_I2C_FIFO_STATE_TX_WERR	BIT(7)
#घोषणा   HISI_I2C_FIFO_STATE_TX_FULL	BIT(11)
#घोषणा HISI_I2C_SDA_HOLD		0x0030
#घोषणा   HISI_I2C_SDA_HOLD_TX		GENMASK(15, 0)
#घोषणा   HISI_I2C_SDA_HOLD_RX		GENMASK(23, 16)
#घोषणा HISI_I2C_FS_SPK_LEN		0x0038
#घोषणा   HISI_I2C_FS_SPK_LEN_CNT	GENMASK(7, 0)
#घोषणा HISI_I2C_HS_SPK_LEN		0x003c
#घोषणा   HISI_I2C_HS_SPK_LEN_CNT	GENMASK(7, 0)
#घोषणा HISI_I2C_INT_MSTAT		0x0044
#घोषणा HISI_I2C_INT_CLR		0x0048
#घोषणा HISI_I2C_INT_MASK		0x004C
#घोषणा HISI_I2C_TRANS_STATE		0x0050
#घोषणा HISI_I2C_TRANS_ERR		0x0054
#घोषणा HISI_I2C_VERSION		0x0058

#घोषणा HISI_I2C_INT_ALL	GENMASK(4, 0)
#घोषणा HISI_I2C_INT_TRANS_CPLT	BIT(0)
#घोषणा HISI_I2C_INT_TRANS_ERR	BIT(1)
#घोषणा HISI_I2C_INT_FIFO_ERR	BIT(2)
#घोषणा HISI_I2C_INT_RX_FULL	BIT(3)
#घोषणा HISI_I2C_INT_TX_EMPTY	BIT(4)
#घोषणा HISI_I2C_INT_ERR \
	(HISI_I2C_INT_TRANS_ERR | HISI_I2C_INT_FIFO_ERR)

#घोषणा HISI_I2C_STD_SPEED_MODE		0
#घोषणा HISI_I2C_FAST_SPEED_MODE	1
#घोषणा HISI_I2C_HIGH_SPEED_MODE	2

#घोषणा HISI_I2C_TX_FIFO_DEPTH		64
#घोषणा HISI_I2C_RX_FIFO_DEPTH		64
#घोषणा HISI_I2C_TX_F_AE_THRESH		1
#घोषणा HISI_I2C_RX_F_AF_THRESH		60

#घोषणा HZ_PER_KHZ	1000

#घोषणा NSEC_TO_CYCLES(ns, clk_rate_khz) \
	DIV_ROUND_UP_ULL((clk_rate_khz) * (ns), NSEC_PER_MSEC)

काष्ठा hisi_i2c_controller अणु
	काष्ठा i2c_adapter adapter;
	व्योम __iomem *iobase;
	काष्ठा device *dev;
	पूर्णांक irq;

	/* Intermediates क्रम recording the transfer process */
	काष्ठा completion *completion;
	काष्ठा i2c_msg *msgs;
	पूर्णांक msg_num;
	पूर्णांक msg_tx_idx;
	पूर्णांक buf_tx_idx;
	पूर्णांक msg_rx_idx;
	पूर्णांक buf_rx_idx;
	u16 tar_addr;
	u32 xfer_err;

	/* I2C bus configuration */
	काष्ठा i2c_timings t;
	u32 clk_rate_khz;
	u32 spk_len;
पूर्ण;

अटल व्योम hisi_i2c_enable_पूर्णांक(काष्ठा hisi_i2c_controller *ctlr, u32 mask)
अणु
	ग_लिखोl_relaxed(mask, ctlr->iobase + HISI_I2C_INT_MASK);
पूर्ण

अटल व्योम hisi_i2c_disable_पूर्णांक(काष्ठा hisi_i2c_controller *ctlr, u32 mask)
अणु
	ग_लिखोl_relaxed((~mask) & HISI_I2C_INT_ALL, ctlr->iobase + HISI_I2C_INT_MASK);
पूर्ण

अटल व्योम hisi_i2c_clear_पूर्णांक(काष्ठा hisi_i2c_controller *ctlr, u32 mask)
अणु
	ग_लिखोl_relaxed(mask, ctlr->iobase + HISI_I2C_INT_CLR);
पूर्ण

अटल व्योम hisi_i2c_handle_errors(काष्ठा hisi_i2c_controller *ctlr)
अणु
	u32 पूर्णांक_err = ctlr->xfer_err, reg;

	अगर (पूर्णांक_err & HISI_I2C_INT_FIFO_ERR) अणु
		reg = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_STATE);

		अगर (reg & HISI_I2C_FIFO_STATE_RX_RERR)
			dev_err(ctlr->dev, "rx fifo error read\n");

		अगर (reg & HISI_I2C_FIFO_STATE_RX_WERR)
			dev_err(ctlr->dev, "rx fifo error write\n");

		अगर (reg & HISI_I2C_FIFO_STATE_TX_RERR)
			dev_err(ctlr->dev, "tx fifo error read\n");

		अगर (reg & HISI_I2C_FIFO_STATE_TX_WERR)
			dev_err(ctlr->dev, "tx fifo error write\n");
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_i2c_start_xfer(काष्ठा hisi_i2c_controller *ctlr)
अणु
	काष्ठा i2c_msg *msg = ctlr->msgs;
	u32 reg;

	reg = पढ़ोl(ctlr->iobase + HISI_I2C_FRAME_CTRL);
	reg &= ~HISI_I2C_FRAME_CTRL_ADDR_TEN;
	अगर (msg->flags & I2C_M_TEN)
		reg |= HISI_I2C_FRAME_CTRL_ADDR_TEN;
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_FRAME_CTRL);

	reg = पढ़ोl(ctlr->iobase + HISI_I2C_SLV_ADDR);
	reg &= ~HISI_I2C_SLV_ADDR_VAL;
	reg |= FIELD_PREP(HISI_I2C_SLV_ADDR_VAL, msg->addr);
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_SLV_ADDR);

	reg = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_CTRL);
	reg |= HISI_I2C_FIFO_RX_CLR | HISI_I2C_FIFO_TX_CLR;
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_FIFO_CTRL);
	reg &= ~(HISI_I2C_FIFO_RX_CLR | HISI_I2C_FIFO_TX_CLR);
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_FIFO_CTRL);

	hisi_i2c_clear_पूर्णांक(ctlr, HISI_I2C_INT_ALL);
	hisi_i2c_enable_पूर्णांक(ctlr, HISI_I2C_INT_ALL);

	वापस 0;
पूर्ण

अटल व्योम hisi_i2c_reset_xfer(काष्ठा hisi_i2c_controller *ctlr)
अणु
	ctlr->msg_num = 0;
	ctlr->xfer_err = 0;
	ctlr->msg_tx_idx = 0;
	ctlr->msg_rx_idx = 0;
	ctlr->buf_tx_idx = 0;
	ctlr->buf_rx_idx = 0;
पूर्ण

/*
 * Initialize the transfer inक्रमmation and start the I2C bus transfer.
 * We only configure the transfer and करो some pre/post works here, and
 * रुको क्रम the transfer करोne. The major transfer process is perक्रमmed
 * in the IRQ handler.
 */
अटल पूर्णांक hisi_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा hisi_i2c_controller *ctlr = i2c_get_adapdata(adap);
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret = num;

	hisi_i2c_reset_xfer(ctlr);
	ctlr->completion = &करोne;
	ctlr->msg_num = num;
	ctlr->msgs = msgs;

	hisi_i2c_start_xfer(ctlr);

	अगर (!रुको_क्रम_completion_समयout(ctlr->completion, adap->समयout)) अणु
		hisi_i2c_disable_पूर्णांक(ctlr, HISI_I2C_INT_ALL);
		synchronize_irq(ctlr->irq);
		i2c_recover_bus(&ctlr->adapter);
		dev_err(ctlr->dev, "bus transfer timeout\n");
		ret = -EIO;
	पूर्ण

	अगर (ctlr->xfer_err) अणु
		hisi_i2c_handle_errors(ctlr);
		ret = -EIO;
	पूर्ण

	hisi_i2c_reset_xfer(ctlr);
	ctlr->completion = शून्य;

	वापस ret;
पूर्ण

अटल u32 hisi_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm hisi_i2c_algo = अणु
	.master_xfer	= hisi_i2c_master_xfer,
	.functionality	= hisi_i2c_functionality,
पूर्ण;

अटल पूर्णांक hisi_i2c_पढ़ो_rx_fअगरo(काष्ठा hisi_i2c_controller *ctlr)
अणु
	काष्ठा i2c_msg *cur_msg;
	u32 fअगरo_state;

	जबतक (ctlr->msg_rx_idx < ctlr->msg_num) अणु
		cur_msg = ctlr->msgs + ctlr->msg_rx_idx;

		अगर (!(cur_msg->flags & I2C_M_RD)) अणु
			ctlr->msg_rx_idx++;
			जारी;
		पूर्ण

		fअगरo_state = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_STATE);
		जबतक (!(fअगरo_state & HISI_I2C_FIFO_STATE_RX_EMPTY) &&
		       ctlr->buf_rx_idx < cur_msg->len) अणु
			cur_msg->buf[ctlr->buf_rx_idx++] = पढ़ोl(ctlr->iobase + HISI_I2C_RXDATA);
			fअगरo_state = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_STATE);
		पूर्ण

		अगर (ctlr->buf_rx_idx == cur_msg->len) अणु
			ctlr->buf_rx_idx = 0;
			ctlr->msg_rx_idx++;
		पूर्ण

		अगर (fअगरo_state & HISI_I2C_FIFO_STATE_RX_EMPTY)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hisi_i2c_xfer_msg(काष्ठा hisi_i2c_controller *ctlr)
अणु
	पूर्णांक max_ग_लिखो = HISI_I2C_TX_FIFO_DEPTH;
	bool need_restart = false, last_msg;
	काष्ठा i2c_msg *cur_msg;
	u32 cmd, fअगरo_state;

	जबतक (ctlr->msg_tx_idx < ctlr->msg_num) अणु
		cur_msg = ctlr->msgs + ctlr->msg_tx_idx;
		last_msg = (ctlr->msg_tx_idx == ctlr->msg_num - 1);

		/* Signal the SR bit when we start transferring a new message */
		अगर (ctlr->msg_tx_idx && !ctlr->buf_tx_idx)
			need_restart = true;

		fअगरo_state = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_STATE);
		जबतक (!(fअगरo_state & HISI_I2C_FIFO_STATE_TX_FULL) &&
		       ctlr->buf_tx_idx < cur_msg->len && max_ग_लिखो) अणु
			cmd = 0;

			अगर (need_restart) अणु
				cmd |= HISI_I2C_CMD_TXDATA_SR_EN;
				need_restart = false;
			पूर्ण

			/* Signal the STOP bit at the last frame of the last message */
			अगर (ctlr->buf_tx_idx == cur_msg->len - 1 && last_msg)
				cmd |= HISI_I2C_CMD_TXDATA_P_EN;

			अगर (cur_msg->flags & I2C_M_RD)
				cmd |= HISI_I2C_CMD_TXDATA_RW;
			अन्यथा
				cmd |= FIELD_PREP(HISI_I2C_CMD_TXDATA_DATA,
						  cur_msg->buf[ctlr->buf_tx_idx]);

			ग_लिखोl(cmd, ctlr->iobase + HISI_I2C_CMD_TXDATA);
			ctlr->buf_tx_idx++;
			max_ग_लिखो--;

			fअगरo_state = पढ़ोl(ctlr->iobase + HISI_I2C_FIFO_STATE);
		पूर्ण

		/* Update the transfer index after per message transfer is करोne. */
		अगर (ctlr->buf_tx_idx == cur_msg->len) अणु
			ctlr->buf_tx_idx = 0;
			ctlr->msg_tx_idx++;
		पूर्ण

		अगर ((fअगरo_state & HISI_I2C_FIFO_STATE_TX_FULL) ||
		    max_ग_लिखो == 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t hisi_i2c_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा hisi_i2c_controller *ctlr = context;
	u32 पूर्णांक_stat;

	पूर्णांक_stat = पढ़ोl(ctlr->iobase + HISI_I2C_INT_MSTAT);
	hisi_i2c_clear_पूर्णांक(ctlr, पूर्णांक_stat);
	अगर (!(पूर्णांक_stat & HISI_I2C_INT_ALL))
		वापस IRQ_NONE;

	अगर (पूर्णांक_stat & HISI_I2C_INT_TX_EMPTY)
		hisi_i2c_xfer_msg(ctlr);

	अगर (पूर्णांक_stat & HISI_I2C_INT_ERR) अणु
		ctlr->xfer_err = पूर्णांक_stat;
		जाओ out;
	पूर्ण

	/* Drain the rx fअगरo beक्रमe finish the transfer */
	अगर (पूर्णांक_stat & (HISI_I2C_INT_TRANS_CPLT | HISI_I2C_INT_RX_FULL))
		hisi_i2c_पढ़ो_rx_fअगरo(ctlr);

out:
	अगर (पूर्णांक_stat & HISI_I2C_INT_TRANS_CPLT || ctlr->xfer_err) अणु
		hisi_i2c_disable_पूर्णांक(ctlr, HISI_I2C_INT_ALL);
		hisi_i2c_clear_पूर्णांक(ctlr, HISI_I2C_INT_ALL);
		complete(ctlr->completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Helper function क्रम calculating and configuring the HIGH and LOW
 * periods of SCL घड़ी. The caller will pass the ratio of the
 * counts (भागide / भागisor) according to the target speed mode,
 * and the target रेजिस्टरs.
 */
अटल व्योम hisi_i2c_set_scl(काष्ठा hisi_i2c_controller *ctlr,
			     u32 भागide, u32 भागisor,
			     u32 reg_hcnt, u32 reg_lcnt)
अणु
	u32 total_cnt, t_scl_hcnt, t_scl_lcnt, scl_fall_cnt, scl_rise_cnt;
	u32 scl_hcnt, scl_lcnt;

	/* Total SCL घड़ी cycles per speed period */
	total_cnt = DIV_ROUND_UP_ULL(ctlr->clk_rate_khz * HZ_PER_KHZ, ctlr->t.bus_freq_hz);
	/* Total HIGH level SCL घड़ी cycles including edges */
	t_scl_hcnt = DIV_ROUND_UP_ULL(total_cnt * भागide, भागisor);
	/* Total LOW level SCL घड़ी cycles including edges */
	t_scl_lcnt = total_cnt - t_scl_hcnt;
	/* Fall edge SCL घड़ी cycles */
	scl_fall_cnt = NSEC_TO_CYCLES(ctlr->t.scl_fall_ns, ctlr->clk_rate_khz);
	/* Rise edge SCL घड़ी cycles */
	scl_rise_cnt = NSEC_TO_CYCLES(ctlr->t.scl_rise_ns, ctlr->clk_rate_khz);

	/* Calculated HIGH and LOW periods of SCL घड़ी */
	scl_hcnt = t_scl_hcnt - ctlr->spk_len - 7 - scl_fall_cnt;
	scl_lcnt = t_scl_lcnt - 1 - scl_rise_cnt;

	ग_लिखोl(scl_hcnt, ctlr->iobase + reg_hcnt);
	ग_लिखोl(scl_lcnt, ctlr->iobase + reg_lcnt);
पूर्ण

अटल व्योम hisi_i2c_configure_bus(काष्ठा hisi_i2c_controller *ctlr)
अणु
	u32 reg, sda_hold_cnt, speed_mode;

	i2c_parse_fw_timings(ctlr->dev, &ctlr->t, true);
	ctlr->spk_len = NSEC_TO_CYCLES(ctlr->t.digital_filter_width_ns, ctlr->clk_rate_khz);

	चयन (ctlr->t.bus_freq_hz) अणु
	हाल I2C_MAX_FAST_MODE_FREQ:
		speed_mode = HISI_I2C_FAST_SPEED_MODE;
		hisi_i2c_set_scl(ctlr, 26, 76, HISI_I2C_FS_SCL_HCNT, HISI_I2C_FS_SCL_LCNT);
		अवरोध;
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		speed_mode = HISI_I2C_HIGH_SPEED_MODE;
		hisi_i2c_set_scl(ctlr, 6, 22, HISI_I2C_HS_SCL_HCNT, HISI_I2C_HS_SCL_LCNT);
		अवरोध;
	हाल I2C_MAX_STANDARD_MODE_FREQ:
	शेष:
		speed_mode = HISI_I2C_STD_SPEED_MODE;

		/* For शेष condition क्रमce the bus speed to standard mode. */
		ctlr->t.bus_freq_hz = I2C_MAX_STANDARD_MODE_FREQ;
		hisi_i2c_set_scl(ctlr, 40, 87, HISI_I2C_SS_SCL_HCNT, HISI_I2C_SS_SCL_LCNT);
		अवरोध;
	पूर्ण

	reg = पढ़ोl(ctlr->iobase + HISI_I2C_FRAME_CTRL);
	reg &= ~HISI_I2C_FRAME_CTRL_SPEED_MODE;
	reg |= FIELD_PREP(HISI_I2C_FRAME_CTRL_SPEED_MODE, speed_mode);
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_FRAME_CTRL);

	sda_hold_cnt = NSEC_TO_CYCLES(ctlr->t.sda_hold_ns, ctlr->clk_rate_khz);

	reg = FIELD_PREP(HISI_I2C_SDA_HOLD_TX, sda_hold_cnt);
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_SDA_HOLD);

	ग_लिखोl(ctlr->spk_len, ctlr->iobase + HISI_I2C_FS_SPK_LEN);

	reg = FIELD_PREP(HISI_I2C_FIFO_RX_AF_THRESH, HISI_I2C_RX_F_AF_THRESH);
	reg |= FIELD_PREP(HISI_I2C_FIFO_TX_AE_THRESH, HISI_I2C_TX_F_AE_THRESH);
	ग_लिखोl(reg, ctlr->iobase + HISI_I2C_FIFO_CTRL);
पूर्ण

अटल पूर्णांक hisi_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_i2c_controller *ctlr;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा i2c_adapter *adapter;
	u64 clk_rate_hz;
	u32 hw_version;
	पूर्णांक ret;

	ctlr = devm_kzalloc(dev, माप(*ctlr), GFP_KERNEL);
	अगर (!ctlr)
		वापस -ENOMEM;

	ctlr->iobase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctlr->iobase))
		वापस PTR_ERR(ctlr->iobase);

	ctlr->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ctlr->irq < 0)
		वापस ctlr->irq;

	ctlr->dev = dev;

	hisi_i2c_disable_पूर्णांक(ctlr, HISI_I2C_INT_ALL);

	ret = devm_request_irq(dev, ctlr->irq, hisi_i2c_irq, 0, "hisi-i2c", ctlr);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq handler, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u64(dev, "clk_rate", &clk_rate_hz);
	अगर (ret) अणु
		dev_err(dev, "failed to get clock frequency, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ctlr->clk_rate_khz = DIV_ROUND_UP_ULL(clk_rate_hz, HZ_PER_KHZ);

	hisi_i2c_configure_bus(ctlr);

	adapter = &ctlr->adapter;
	snम_लिखो(adapter->name, माप(adapter->name),
		 "HiSilicon I2C Controller %s", dev_name(dev));
	adapter->owner = THIS_MODULE;
	adapter->algo = &hisi_i2c_algo;
	adapter->dev.parent = dev;
	i2c_set_adapdata(adapter, ctlr);

	ret = devm_i2c_add_adapter(dev, adapter);
	अगर (ret)
		वापस ret;

	hw_version = पढ़ोl(ctlr->iobase + HISI_I2C_VERSION);
	dev_info(ctlr->dev, "speed mode is %s. hw version 0x%x\n",
		 i2c_freq_mode_string(ctlr->t.bus_freq_hz), hw_version);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_i2c_acpi_ids[] = अणु
	अणु "HISI03D1", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_i2c_acpi_ids);

अटल काष्ठा platक्रमm_driver hisi_i2c_driver = अणु
	.probe		= hisi_i2c_probe,
	.driver		= अणु
		.name	= "hisi-i2c",
		.acpi_match_table = hisi_i2c_acpi_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hisi_i2c_driver);

MODULE_AUTHOR("Yicong Yang <yangyicong@hisilicon.com>");
MODULE_DESCRIPTION("HiSilicon I2C Controller Driver");
MODULE_LICENSE("GPL");
