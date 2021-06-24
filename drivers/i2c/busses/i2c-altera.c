<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright Intel Corporation (C) 2017.
 *
 * Based on the i2c-axxia.c driver.
 */
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा ALTR_I2C_TFR_CMD	0x00	/* Transfer Command रेजिस्टर */
#घोषणा     ALTR_I2C_TFR_CMD_STA	BIT(9)	/* send START beक्रमe byte */
#घोषणा     ALTR_I2C_TFR_CMD_STO	BIT(8)	/* send STOP after byte */
#घोषणा     ALTR_I2C_TFR_CMD_RW_D	BIT(0)	/* Direction of transfer */
#घोषणा ALTR_I2C_RX_DATA	0x04	/* RX data FIFO रेजिस्टर */
#घोषणा ALTR_I2C_CTRL		0x08	/* Control रेजिस्टर */
#घोषणा     ALTR_I2C_CTRL_RXT_SHFT	4	/* RX FIFO Threshold */
#घोषणा     ALTR_I2C_CTRL_TCT_SHFT	2	/* TFER CMD FIFO Threshold */
#घोषणा     ALTR_I2C_CTRL_BSPEED	BIT(1)	/* Bus Speed (1=Fast) */
#घोषणा     ALTR_I2C_CTRL_EN	BIT(0)	/* Enable Core (1=Enable) */
#घोषणा ALTR_I2C_ISER		0x0C	/* Interrupt Status Enable रेजिस्टर */
#घोषणा     ALTR_I2C_ISER_RXOF_EN	BIT(4)	/* Enable RX OVERFLOW IRQ */
#घोषणा     ALTR_I2C_ISER_ARB_EN	BIT(3)	/* Enable ARB LOST IRQ */
#घोषणा     ALTR_I2C_ISER_NACK_EN	BIT(2)	/* Enable NACK DET IRQ */
#घोषणा     ALTR_I2C_ISER_RXRDY_EN	BIT(1)	/* Enable RX Ready IRQ */
#घोषणा     ALTR_I2C_ISER_TXRDY_EN	BIT(0)	/* Enable TX Ready IRQ */
#घोषणा ALTR_I2C_ISR		0x10	/* Interrupt Status रेजिस्टर */
#घोषणा     ALTR_I2C_ISR_RXOF		BIT(4)	/* RX OVERFLOW IRQ */
#घोषणा     ALTR_I2C_ISR_ARB		BIT(3)	/* ARB LOST IRQ */
#घोषणा     ALTR_I2C_ISR_NACK		BIT(2)	/* NACK DET IRQ */
#घोषणा     ALTR_I2C_ISR_RXRDY		BIT(1)	/* RX Ready IRQ */
#घोषणा     ALTR_I2C_ISR_TXRDY		BIT(0)	/* TX Ready IRQ */
#घोषणा ALTR_I2C_STATUS		0x14	/* Status रेजिस्टर */
#घोषणा     ALTR_I2C_STAT_CORE		BIT(0)	/* Core Status (0=idle) */
#घोषणा ALTR_I2C_TC_FIFO_LVL	0x18	/* Transfer FIFO LVL रेजिस्टर */
#घोषणा ALTR_I2C_RX_FIFO_LVL	0x1C	/* Receive FIFO LVL रेजिस्टर */
#घोषणा ALTR_I2C_SCL_LOW	0x20	/* SCL low count रेजिस्टर */
#घोषणा ALTR_I2C_SCL_HIGH	0x24	/* SCL high count रेजिस्टर */
#घोषणा ALTR_I2C_SDA_HOLD	0x28	/* SDA hold count रेजिस्टर */

#घोषणा ALTR_I2C_ALL_IRQ	(ALTR_I2C_ISR_RXOF | ALTR_I2C_ISR_ARB | \
				 ALTR_I2C_ISR_NACK | ALTR_I2C_ISR_RXRDY | \
				 ALTR_I2C_ISR_TXRDY)

#घोषणा ALTR_I2C_THRESHOLD	0	/* IRQ Threshold at 1 element */
#घोषणा ALTR_I2C_DFLT_FIFO_SZ	4
#घोषणा ALTR_I2C_TIMEOUT	100000	/* 100ms */
#घोषणा ALTR_I2C_XFER_TIMEOUT	(msecs_to_jअगरfies(250))

/**
 * काष्ठा altr_i2c_dev - I2C device context
 * @base: poपूर्णांकer to रेजिस्टर काष्ठा
 * @msg: poपूर्णांकer to current message
 * @msg_len: number of bytes transferred in msg
 * @msg_err: error code क्रम completed message
 * @msg_complete: xfer completion object
 * @dev: device reference
 * @adapter: core i2c असलtraction
 * @i2c_clk: घड़ी reference क्रम i2c input घड़ी
 * @bus_clk_rate: current i2c bus घड़ी rate
 * @buf: ptr to msg buffer क्रम easier use.
 * @fअगरo_size: size of the FIFO passed in.
 * @isr_mask: cached copy of local ISR enables.
 * @isr_status: cached copy of local ISR status.
 * @isr_mutex: mutex क्रम IRQ thपढ़ो.
 */
काष्ठा altr_i2c_dev अणु
	व्योम __iomem *base;
	काष्ठा i2c_msg *msg;
	माप_प्रकार msg_len;
	पूर्णांक msg_err;
	काष्ठा completion msg_complete;
	काष्ठा device *dev;
	काष्ठा i2c_adapter adapter;
	काष्ठा clk *i2c_clk;
	u32 bus_clk_rate;
	u8 *buf;
	u32 fअगरo_size;
	u32 isr_mask;
	u32 isr_status;
	काष्ठा mutex isr_mutex;
पूर्ण;

अटल व्योम
altr_i2c_पूर्णांक_enable(काष्ठा altr_i2c_dev *idev, u32 mask, bool enable)
अणु
	u32 पूर्णांक_en;

	पूर्णांक_en = पढ़ोl(idev->base + ALTR_I2C_ISER);
	अगर (enable)
		idev->isr_mask = पूर्णांक_en | mask;
	अन्यथा
		idev->isr_mask = पूर्णांक_en & ~mask;

	ग_लिखोl(idev->isr_mask, idev->base + ALTR_I2C_ISER);
पूर्ण

अटल व्योम altr_i2c_पूर्णांक_clear(काष्ठा altr_i2c_dev *idev, u32 mask)
अणु
	u32 पूर्णांक_en = पढ़ोl(idev->base + ALTR_I2C_ISR);

	ग_लिखोl(पूर्णांक_en | mask, idev->base + ALTR_I2C_ISR);
पूर्ण

अटल व्योम altr_i2c_core_disable(काष्ठा altr_i2c_dev *idev)
अणु
	u32 पंचांगp = पढ़ोl(idev->base + ALTR_I2C_CTRL);

	ग_लिखोl(पंचांगp & ~ALTR_I2C_CTRL_EN, idev->base + ALTR_I2C_CTRL);
पूर्ण

अटल व्योम altr_i2c_core_enable(काष्ठा altr_i2c_dev *idev)
अणु
	u32 पंचांगp = पढ़ोl(idev->base + ALTR_I2C_CTRL);

	ग_लिखोl(पंचांगp | ALTR_I2C_CTRL_EN, idev->base + ALTR_I2C_CTRL);
पूर्ण

अटल व्योम altr_i2c_reset(काष्ठा altr_i2c_dev *idev)
अणु
	altr_i2c_core_disable(idev);
	altr_i2c_core_enable(idev);
पूर्ण

अटल अंतरभूत व्योम altr_i2c_stop(काष्ठा altr_i2c_dev *idev)
अणु
	ग_लिखोl(ALTR_I2C_TFR_CMD_STO, idev->base + ALTR_I2C_TFR_CMD);
पूर्ण

अटल व्योम altr_i2c_init(काष्ठा altr_i2c_dev *idev)
अणु
	u32 भागisor = clk_get_rate(idev->i2c_clk) / idev->bus_clk_rate;
	u32 clk_mhz = clk_get_rate(idev->i2c_clk) / 1000000;
	u32 पंचांगp = (ALTR_I2C_THRESHOLD << ALTR_I2C_CTRL_RXT_SHFT) |
		  (ALTR_I2C_THRESHOLD << ALTR_I2C_CTRL_TCT_SHFT);
	u32 t_high, t_low;

	अगर (idev->bus_clk_rate <= I2C_MAX_STANDARD_MODE_FREQ) अणु
		पंचांगp &= ~ALTR_I2C_CTRL_BSPEED;
		/* Standard mode SCL 50/50 */
		t_high = भागisor * 1 / 2;
		t_low = भागisor * 1 / 2;
	पूर्ण अन्यथा अणु
		पंचांगp |= ALTR_I2C_CTRL_BSPEED;
		/* Fast mode SCL 33/66 */
		t_high = भागisor * 1 / 3;
		t_low = भागisor * 2 / 3;
	पूर्ण
	ग_लिखोl(पंचांगp, idev->base + ALTR_I2C_CTRL);

	dev_dbg(idev->dev, "rate=%uHz per_clk=%uMHz -> ratio=1:%u\n",
		idev->bus_clk_rate, clk_mhz, भागisor);

	/* Reset controller */
	altr_i2c_reset(idev);

	/* SCL High Time */
	ग_लिखोl(t_high, idev->base + ALTR_I2C_SCL_HIGH);
	/* SCL Low Time */
	ग_लिखोl(t_low, idev->base + ALTR_I2C_SCL_LOW);
	/* SDA Hold Time, 300ns */
	ग_लिखोl(3 * clk_mhz / 10, idev->base + ALTR_I2C_SDA_HOLD);

	/* Mask all master पूर्णांकerrupt bits */
	altr_i2c_पूर्णांक_enable(idev, ALTR_I2C_ALL_IRQ, false);
पूर्ण

/*
 * altr_i2c_transfer - On the last byte to be transmitted, send
 * a Stop bit on the last byte.
 */
अटल व्योम altr_i2c_transfer(काष्ठा altr_i2c_dev *idev, u32 data)
अणु
	/* On the last byte to be transmitted, send STOP */
	अगर (idev->msg_len == 1)
		data |= ALTR_I2C_TFR_CMD_STO;
	अगर (idev->msg_len > 0)
		ग_लिखोl(data, idev->base + ALTR_I2C_TFR_CMD);
पूर्ण

/*
 * altr_i2c_empty_rx_fअगरo - Fetch data from RX FIFO until end of
 * transfer. Send a Stop bit on the last byte.
 */
अटल व्योम altr_i2c_empty_rx_fअगरo(काष्ठा altr_i2c_dev *idev)
अणु
	माप_प्रकार rx_fअगरo_avail = पढ़ोl(idev->base + ALTR_I2C_RX_FIFO_LVL);
	पूर्णांक bytes_to_transfer = min(rx_fअगरo_avail, idev->msg_len);

	जबतक (bytes_to_transfer-- > 0) अणु
		*idev->buf++ = पढ़ोl(idev->base + ALTR_I2C_RX_DATA);
		idev->msg_len--;
		altr_i2c_transfer(idev, 0);
	पूर्ण
पूर्ण

/*
 * altr_i2c_fill_tx_fअगरo - Fill TX FIFO from current message buffer.
 */
अटल पूर्णांक altr_i2c_fill_tx_fअगरo(काष्ठा altr_i2c_dev *idev)
अणु
	माप_प्रकार tx_fअगरo_avail = idev->fअगरo_size - पढ़ोl(idev->base +
						       ALTR_I2C_TC_FIFO_LVL);
	पूर्णांक bytes_to_transfer = min(tx_fअगरo_avail, idev->msg_len);
	पूर्णांक ret = idev->msg_len - bytes_to_transfer;

	जबतक (bytes_to_transfer-- > 0) अणु
		altr_i2c_transfer(idev, *idev->buf++);
		idev->msg_len--;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t altr_i2c_isr_quick(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा altr_i2c_dev *idev = _dev;
	irqवापस_t ret = IRQ_HANDLED;

	/* Read IRQ status but only पूर्णांकerested in Enabled IRQs. */
	idev->isr_status = पढ़ोl(idev->base + ALTR_I2C_ISR) & idev->isr_mask;
	अगर (idev->isr_status)
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल irqवापस_t altr_i2c_isr(पूर्णांक irq, व्योम *_dev)
अणु
	पूर्णांक ret;
	bool पढ़ो, finish = false;
	काष्ठा altr_i2c_dev *idev = _dev;
	u32 status = idev->isr_status;

	mutex_lock(&idev->isr_mutex);
	अगर (!idev->msg) अणु
		dev_warn(idev->dev, "unexpected interrupt\n");
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ALL_IRQ);
		जाओ out;
	पूर्ण
	पढ़ो = (idev->msg->flags & I2C_M_RD) != 0;

	/* handle Lost Arbitration */
	अगर (unlikely(status & ALTR_I2C_ISR_ARB)) अणु
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ISR_ARB);
		idev->msg_err = -EAGAIN;
		finish = true;
	पूर्ण अन्यथा अगर (unlikely(status & ALTR_I2C_ISR_NACK)) अणु
		dev_dbg(idev->dev, "Could not get ACK\n");
		idev->msg_err = -ENXIO;
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ISR_NACK);
		altr_i2c_stop(idev);
		finish = true;
	पूर्ण अन्यथा अगर (पढ़ो && unlikely(status & ALTR_I2C_ISR_RXOF)) अणु
		/* handle RX FIFO Overflow */
		altr_i2c_empty_rx_fअगरo(idev);
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ISR_RXRDY);
		altr_i2c_stop(idev);
		dev_err(idev->dev, "RX FIFO Overflow\n");
		finish = true;
	पूर्ण अन्यथा अगर (पढ़ो && (status & ALTR_I2C_ISR_RXRDY)) अणु
		/* RX FIFO needs service? */
		altr_i2c_empty_rx_fअगरo(idev);
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ISR_RXRDY);
		अगर (!idev->msg_len)
			finish = true;
	पूर्ण अन्यथा अगर (!पढ़ो && (status & ALTR_I2C_ISR_TXRDY)) अणु
		/* TX FIFO needs service? */
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ISR_TXRDY);
		अगर (idev->msg_len > 0)
			altr_i2c_fill_tx_fअगरo(idev);
		अन्यथा
			finish = true;
	पूर्ण अन्यथा अणु
		dev_warn(idev->dev, "Unexpected interrupt: 0x%x\n", status);
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ALL_IRQ);
	पूर्ण

	अगर (finish) अणु
		/* Wait क्रम the Core to finish */
		ret = पढ़ोl_poll_समयout_atomic(idev->base + ALTR_I2C_STATUS,
						status,
						!(status & ALTR_I2C_STAT_CORE),
						1, ALTR_I2C_TIMEOUT);
		अगर (ret)
			dev_err(idev->dev, "message timeout\n");
		altr_i2c_पूर्णांक_enable(idev, ALTR_I2C_ALL_IRQ, false);
		altr_i2c_पूर्णांक_clear(idev, ALTR_I2C_ALL_IRQ);
		complete(&idev->msg_complete);
		dev_dbg(idev->dev, "Message Complete\n");
	पूर्ण
out:
	mutex_unlock(&idev->isr_mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक altr_i2c_xfer_msg(काष्ठा altr_i2c_dev *idev, काष्ठा i2c_msg *msg)
अणु
	u32 imask = ALTR_I2C_ISR_RXOF | ALTR_I2C_ISR_ARB | ALTR_I2C_ISR_NACK;
	अचिन्हित दीर्घ समय_left;
	u32 value;
	u8 addr = i2c_8bit_addr_from_msg(msg);

	mutex_lock(&idev->isr_mutex);
	idev->msg = msg;
	idev->msg_len = msg->len;
	idev->buf = msg->buf;
	idev->msg_err = 0;
	reinit_completion(&idev->msg_complete);
	altr_i2c_core_enable(idev);

	/* Make sure RX FIFO is empty */
	करो अणु
		पढ़ोl(idev->base + ALTR_I2C_RX_DATA);
	पूर्ण जबतक (पढ़ोl(idev->base + ALTR_I2C_RX_FIFO_LVL));

	ग_लिखोl(ALTR_I2C_TFR_CMD_STA | addr, idev->base + ALTR_I2C_TFR_CMD);

	अगर ((msg->flags & I2C_M_RD) != 0) अणु
		imask |= ALTR_I2C_ISER_RXOF_EN | ALTR_I2C_ISER_RXRDY_EN;
		altr_i2c_पूर्णांक_enable(idev, imask, true);
		/* ग_लिखो the first byte to start the RX */
		altr_i2c_transfer(idev, 0);
	पूर्ण अन्यथा अणु
		imask |= ALTR_I2C_ISR_TXRDY;
		altr_i2c_पूर्णांक_enable(idev, imask, true);
		altr_i2c_fill_tx_fअगरo(idev);
	पूर्ण
	mutex_unlock(&idev->isr_mutex);

	समय_left = रुको_क्रम_completion_समयout(&idev->msg_complete,
						ALTR_I2C_XFER_TIMEOUT);
	mutex_lock(&idev->isr_mutex);
	altr_i2c_पूर्णांक_enable(idev, imask, false);

	value = पढ़ोl(idev->base + ALTR_I2C_STATUS) & ALTR_I2C_STAT_CORE;
	अगर (value)
		dev_err(idev->dev, "Core Status not IDLE...\n");

	अगर (समय_left == 0) अणु
		idev->msg_err = -ETIMEDOUT;
		dev_dbg(idev->dev, "Transaction timed out.\n");
	पूर्ण

	altr_i2c_core_disable(idev);
	mutex_unlock(&idev->isr_mutex);

	वापस idev->msg_err;
पूर्ण

अटल पूर्णांक
altr_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा altr_i2c_dev *idev = i2c_get_adapdata(adap);
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++) अणु
		ret = altr_i2c_xfer_msg(idev, msgs++);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस num;
पूर्ण

अटल u32 altr_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm altr_i2c_algo = अणु
	.master_xfer = altr_i2c_xfer,
	.functionality = altr_i2c_func,
पूर्ण;

अटल पूर्णांक altr_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_i2c_dev *idev = शून्य;
	पूर्णांक irq, ret;

	idev = devm_kzalloc(&pdev->dev, माप(*idev), GFP_KERNEL);
	अगर (!idev)
		वापस -ENOMEM;

	idev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(idev->base))
		वापस PTR_ERR(idev->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	idev->i2c_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(idev->i2c_clk)) अणु
		dev_err(&pdev->dev, "missing clock\n");
		वापस PTR_ERR(idev->i2c_clk);
	पूर्ण

	idev->dev = &pdev->dev;
	init_completion(&idev->msg_complete);
	mutex_init(&idev->isr_mutex);

	ret = device_property_पढ़ो_u32(idev->dev, "fifo-size",
				       &idev->fअगरo_size);
	अगर (ret) अणु
		dev_err(&pdev->dev, "FIFO size set to default of %d\n",
			ALTR_I2C_DFLT_FIFO_SZ);
		idev->fअगरo_size = ALTR_I2C_DFLT_FIFO_SZ;
	पूर्ण

	ret = device_property_पढ़ो_u32(idev->dev, "clock-frequency",
				       &idev->bus_clk_rate);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Default to 100kHz\n");
		idev->bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;	/* शेष घड़ी rate */
	पूर्ण

	अगर (idev->bus_clk_rate > I2C_MAX_FAST_MODE_FREQ) अणु
		dev_err(&pdev->dev, "invalid clock-frequency %d\n",
			idev->bus_clk_rate);
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, altr_i2c_isr_quick,
					altr_i2c_isr, IRQF_ONESHOT,
					pdev->name, idev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim IRQ %d\n", irq);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(idev->i2c_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	mutex_lock(&idev->isr_mutex);
	altr_i2c_init(idev);
	mutex_unlock(&idev->isr_mutex);

	i2c_set_adapdata(&idev->adapter, idev);
	strlcpy(idev->adapter.name, pdev->name, माप(idev->adapter.name));
	idev->adapter.owner = THIS_MODULE;
	idev->adapter.algo = &altr_i2c_algo;
	idev->adapter.dev.parent = &pdev->dev;
	idev->adapter.dev.of_node = pdev->dev.of_node;

	platक्रमm_set_drvdata(pdev, idev);

	ret = i2c_add_adapter(&idev->adapter);
	अगर (ret) अणु
		clk_disable_unprepare(idev->i2c_clk);
		वापस ret;
	पूर्ण
	dev_info(&pdev->dev, "Altera SoftIP I2C Probe Complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक altr_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_i2c_dev *idev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(idev->i2c_clk);
	i2c_del_adapter(&idev->adapter);

	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id altr_i2c_of_match[] = अणु
	अणु .compatible = "altr,softip-i2c-v1.0" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_i2c_of_match);

अटल काष्ठा platक्रमm_driver altr_i2c_driver = अणु
	.probe = altr_i2c_probe,
	.हटाओ = altr_i2c_हटाओ,
	.driver = अणु
		.name = "altera-i2c",
		.of_match_table = altr_i2c_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altr_i2c_driver);

MODULE_DESCRIPTION("Altera Soft IP I2C bus driver");
MODULE_AUTHOR("Thor Thayer <thor.thayer@linux.intel.com>");
MODULE_LICENSE("GPL v2");
