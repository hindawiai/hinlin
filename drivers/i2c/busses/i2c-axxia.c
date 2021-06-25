<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This driver implements I2C master functionality using the LSI API2C
 * controller.
 *
 * NOTE: The controller has a limitation in that it can only करो transfers of
 * maximum 255 bytes at a समय. If a larger transfer is attempted, error code
 * (-EINVAL) is वापसed.
 */
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SCL_WAIT_TIMEOUT_NS 25000000
#घोषणा I2C_XFER_TIMEOUT    (msecs_to_jअगरfies(250))
#घोषणा I2C_STOP_TIMEOUT    (msecs_to_jअगरfies(100))
#घोषणा FIFO_SIZE           8
#घोषणा SEQ_LEN             2

#घोषणा GLOBAL_CONTROL		0x00
#घोषणा   GLOBAL_MST_EN         BIT(0)
#घोषणा   GLOBAL_SLV_EN         BIT(1)
#घोषणा   GLOBAL_IBML_EN        BIT(2)
#घोषणा INTERRUPT_STATUS	0x04
#घोषणा INTERRUPT_ENABLE	0x08
#घोषणा   INT_SLV               BIT(1)
#घोषणा   INT_MST               BIT(0)
#घोषणा WAIT_TIMER_CONTROL	0x0c
#घोषणा   WT_EN			BIT(15)
#घोषणा   WT_VALUE(_x)		((_x) & 0x7fff)
#घोषणा IBML_TIMEOUT		0x10
#घोषणा IBML_LOW_MEXT		0x14
#घोषणा IBML_LOW_SEXT		0x18
#घोषणा TIMER_CLOCK_DIV		0x1c
#घोषणा I2C_BUS_MONITOR		0x20
#घोषणा   BM_SDAC		BIT(3)
#घोषणा   BM_SCLC		BIT(2)
#घोषणा   BM_SDAS		BIT(1)
#घोषणा   BM_SCLS		BIT(0)
#घोषणा SOFT_RESET		0x24
#घोषणा MST_COMMAND		0x28
#घोषणा   CMD_BUSY		(1<<3)
#घोषणा   CMD_MANUAL		(0x00 | CMD_BUSY)
#घोषणा   CMD_AUTO		(0x01 | CMD_BUSY)
#घोषणा   CMD_SEQUENCE		(0x02 | CMD_BUSY)
#घोषणा MST_RX_XFER		0x2c
#घोषणा MST_TX_XFER		0x30
#घोषणा MST_ADDR_1		0x34
#घोषणा MST_ADDR_2		0x38
#घोषणा MST_DATA		0x3c
#घोषणा MST_TX_FIFO		0x40
#घोषणा MST_RX_FIFO		0x44
#घोषणा MST_INT_ENABLE		0x48
#घोषणा MST_INT_STATUS		0x4c
#घोषणा   MST_STATUS_RFL	(1 << 13) /* RX FIFO serivce */
#घोषणा   MST_STATUS_TFL	(1 << 12) /* TX FIFO service */
#घोषणा   MST_STATUS_SNS	(1 << 11) /* Manual mode करोne */
#घोषणा   MST_STATUS_SS		(1 << 10) /* Automatic mode करोne */
#घोषणा   MST_STATUS_SCC	(1 << 9)  /* Stop complete */
#घोषणा   MST_STATUS_IP		(1 << 8)  /* Invalid parameter */
#घोषणा   MST_STATUS_TSS	(1 << 7)  /* Timeout */
#घोषणा   MST_STATUS_AL		(1 << 6)  /* Arbitration lost */
#घोषणा   MST_STATUS_ND		(1 << 5)  /* NAK on data phase */
#घोषणा   MST_STATUS_NA		(1 << 4)  /* NAK on address phase */
#घोषणा   MST_STATUS_NAK	(MST_STATUS_NA | \
				 MST_STATUS_ND)
#घोषणा   MST_STATUS_ERR	(MST_STATUS_NAK | \
				 MST_STATUS_AL  | \
				 MST_STATUS_IP)
#घोषणा MST_TX_BYTES_XFRD	0x50
#घोषणा MST_RX_BYTES_XFRD	0x54
#घोषणा SLV_ADDR_DEC_CTL	0x58
#घोषणा   SLV_ADDR_DEC_GCE	BIT(0)  /* ACK to General Call Address from own master (loopback) */
#घोषणा   SLV_ADDR_DEC_OGCE	BIT(1)  /* ACK to General Call Address from बाह्यal masters */
#घोषणा   SLV_ADDR_DEC_SA1E	BIT(2)  /* ACK to addr_1 enabled */
#घोषणा   SLV_ADDR_DEC_SA1M	BIT(3)  /* 10-bit addressing क्रम addr_1 enabled */
#घोषणा   SLV_ADDR_DEC_SA2E	BIT(4)  /* ACK to addr_2 enabled */
#घोषणा   SLV_ADDR_DEC_SA2M	BIT(5)  /* 10-bit addressing क्रम addr_2 enabled */
#घोषणा SLV_ADDR_1		0x5c
#घोषणा SLV_ADDR_2		0x60
#घोषणा SLV_RX_CTL		0x64
#घोषणा   SLV_RX_ACSA1		BIT(0)  /* Generate ACK क्रम ग_लिखोs to addr_1 */
#घोषणा   SLV_RX_ACSA2		BIT(1)  /* Generate ACK क्रम ग_लिखोs to addr_2 */
#घोषणा   SLV_RX_ACGCA		BIT(2)  /* ACK data phase transfers to General Call Address */
#घोषणा SLV_DATA		0x68
#घोषणा SLV_RX_FIFO		0x6c
#घोषणा   SLV_FIFO_DV1		BIT(0)  /* Data Valid क्रम addr_1 */
#घोषणा   SLV_FIFO_DV2		BIT(1)  /* Data Valid क्रम addr_2 */
#घोषणा   SLV_FIFO_AS		BIT(2)  /* (N)ACK Sent */
#घोषणा   SLV_FIFO_TNAK		BIT(3)  /* Timeout NACK */
#घोषणा   SLV_FIFO_STRC		BIT(4)  /* First byte after start condition received */
#घोषणा   SLV_FIFO_RSC		BIT(5)  /* Repeated Start Condition */
#घोषणा   SLV_FIFO_STPC		BIT(6)  /* Stop Condition */
#घोषणा   SLV_FIFO_DV		(SLV_FIFO_DV1 | SLV_FIFO_DV2)
#घोषणा SLV_INT_ENABLE		0x70
#घोषणा SLV_INT_STATUS		0x74
#घोषणा   SLV_STATUS_RFH	BIT(0)  /* FIFO service */
#घोषणा   SLV_STATUS_WTC	BIT(1)  /* Write transfer complete */
#घोषणा   SLV_STATUS_SRS1	BIT(2)  /* Slave पढ़ो from addr 1 */
#घोषणा   SLV_STATUS_SRRS1	BIT(3)  /* Repeated start from addr 1 */
#घोषणा   SLV_STATUS_SRND1	BIT(4)  /* Read request not following start condition */
#घोषणा   SLV_STATUS_SRC1	BIT(5)  /* Read canceled */
#घोषणा   SLV_STATUS_SRAT1	BIT(6)  /* Slave Read समयd out */
#घोषणा   SLV_STATUS_SRDRE1	BIT(7)  /* Data written after समयd out */
#घोषणा SLV_READ_DUMMY		0x78
#घोषणा SCL_HIGH_PERIOD		0x80
#घोषणा SCL_LOW_PERIOD		0x84
#घोषणा SPIKE_FLTR_LEN		0x88
#घोषणा SDA_SETUP_TIME		0x8c
#घोषणा SDA_HOLD_TIME		0x90

/**
 * axxia_i2c_dev - I2C device context
 * @base: poपूर्णांकer to रेजिस्टर काष्ठा
 * @msg: poपूर्णांकer to current message
 * @msg_r: poपूर्णांकer to current पढ़ो message (sequence transfer)
 * @msg_xfrd: number of bytes transferred in tx_fअगरo
 * @msg_xfrd_r: number of bytes transferred in rx_fअगरo
 * @msg_err: error code क्रम completed message
 * @msg_complete: xfer completion object
 * @dev: device reference
 * @adapter: core i2c असलtraction
 * @i2c_clk: घड़ी reference क्रम i2c input घड़ी
 * @bus_clk_rate: current i2c bus घड़ी rate
 * @last: a flag indicating is this is last message in transfer
 */
काष्ठा axxia_i2c_dev अणु
	व्योम __iomem *base;
	काष्ठा i2c_msg *msg;
	काष्ठा i2c_msg *msg_r;
	माप_प्रकार msg_xfrd;
	माप_प्रकार msg_xfrd_r;
	पूर्णांक msg_err;
	काष्ठा completion msg_complete;
	काष्ठा device *dev;
	काष्ठा i2c_adapter adapter;
	काष्ठा clk *i2c_clk;
	u32 bus_clk_rate;
	bool last;
	काष्ठा i2c_client *slave;
	पूर्णांक irq;
पूर्ण;

अटल व्योम i2c_पूर्णांक_disable(काष्ठा axxia_i2c_dev *idev, u32 mask)
अणु
	u32 पूर्णांक_en;

	पूर्णांक_en = पढ़ोl(idev->base + MST_INT_ENABLE);
	ग_लिखोl(पूर्णांक_en & ~mask, idev->base + MST_INT_ENABLE);
पूर्ण

अटल व्योम i2c_पूर्णांक_enable(काष्ठा axxia_i2c_dev *idev, u32 mask)
अणु
	u32 पूर्णांक_en;

	पूर्णांक_en = पढ़ोl(idev->base + MST_INT_ENABLE);
	ग_लिखोl(पूर्णांक_en | mask, idev->base + MST_INT_ENABLE);
पूर्ण

/**
 * ns_to_clk - Convert समय (ns) to घड़ी cycles क्रम the given घड़ी frequency.
 */
अटल u32 ns_to_clk(u64 ns, u32 clk_mhz)
अणु
	वापस भाग_u64(ns * clk_mhz, 1000);
पूर्ण

अटल पूर्णांक axxia_i2c_init(काष्ठा axxia_i2c_dev *idev)
अणु
	u32 भागisor = clk_get_rate(idev->i2c_clk) / idev->bus_clk_rate;
	u32 clk_mhz = clk_get_rate(idev->i2c_clk) / 1000000;
	u32 t_setup;
	u32 t_high, t_low;
	u32 पंचांगo_clk;
	u32 prescale;
	अचिन्हित दीर्घ समयout;

	dev_dbg(idev->dev, "rate=%uHz per_clk=%uMHz -> ratio=1:%u\n",
		idev->bus_clk_rate, clk_mhz, भागisor);

	/* Reset controller */
	ग_लिखोl(0x01, idev->base + SOFT_RESET);
	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (पढ़ोl(idev->base + SOFT_RESET) & 1) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(idev->dev, "Soft reset failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Enable Master Mode */
	ग_लिखोl(0x1, idev->base + GLOBAL_CONTROL);

	अगर (idev->bus_clk_rate <= I2C_MAX_STANDARD_MODE_FREQ) अणु
		/* Standard mode SCL 50/50, tSU:DAT = 250 ns */
		t_high = भागisor * 1 / 2;
		t_low = भागisor * 1 / 2;
		t_setup = ns_to_clk(250, clk_mhz);
	पूर्ण अन्यथा अणु
		/* Fast mode SCL 33/66, tSU:DAT = 100 ns */
		t_high = भागisor * 1 / 3;
		t_low = भागisor * 2 / 3;
		t_setup = ns_to_clk(100, clk_mhz);
	पूर्ण

	/* SCL High Time */
	ग_लिखोl(t_high, idev->base + SCL_HIGH_PERIOD);
	/* SCL Low Time */
	ग_लिखोl(t_low, idev->base + SCL_LOW_PERIOD);
	/* SDA Setup Time */
	ग_लिखोl(t_setup, idev->base + SDA_SETUP_TIME);
	/* SDA Hold Time, 300ns */
	ग_लिखोl(ns_to_clk(300, clk_mhz), idev->base + SDA_HOLD_TIME);
	/* Filter <50ns spikes */
	ग_लिखोl(ns_to_clk(50, clk_mhz), idev->base + SPIKE_FLTR_LEN);

	/* Configure Time-Out Registers */
	पंचांगo_clk = ns_to_clk(SCL_WAIT_TIMEOUT_NS, clk_mhz);

	/* Find prescaler value that makes पंचांगo_clk fit in 15-bits counter. */
	क्रम (prescale = 0; prescale < 15; ++prescale) अणु
		अगर (पंचांगo_clk <= 0x7fff)
			अवरोध;
		पंचांगo_clk >>= 1;
	पूर्ण
	अगर (पंचांगo_clk > 0x7fff)
		पंचांगo_clk = 0x7fff;

	/* Prescale भागider (log2) */
	ग_लिखोl(prescale, idev->base + TIMER_CLOCK_DIV);
	/* Timeout in भागided घड़ीs */
	ग_लिखोl(WT_EN | WT_VALUE(पंचांगo_clk), idev->base + WAIT_TIMER_CONTROL);

	/* Mask all master पूर्णांकerrupt bits */
	i2c_पूर्णांक_disable(idev, ~0);

	/* Interrupt enable */
	ग_लिखोl(0x01, idev->base + INTERRUPT_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_m_rd(स्थिर काष्ठा i2c_msg *msg)
अणु
	वापस (msg->flags & I2C_M_RD) != 0;
पूर्ण

अटल पूर्णांक i2c_m_ten(स्थिर काष्ठा i2c_msg *msg)
अणु
	वापस (msg->flags & I2C_M_TEN) != 0;
पूर्ण

अटल पूर्णांक i2c_m_recv_len(स्थिर काष्ठा i2c_msg *msg)
अणु
	वापस (msg->flags & I2C_M_RECV_LEN) != 0;
पूर्ण

/**
 * axxia_i2c_empty_rx_fअगरo - Fetch data from RX FIFO and update SMBus block
 * transfer length अगर this is the first byte of such a transfer.
 */
अटल पूर्णांक axxia_i2c_empty_rx_fअगरo(काष्ठा axxia_i2c_dev *idev)
अणु
	काष्ठा i2c_msg *msg = idev->msg_r;
	माप_प्रकार rx_fअगरo_avail = पढ़ोl(idev->base + MST_RX_FIFO);
	पूर्णांक bytes_to_transfer = min(rx_fअगरo_avail, msg->len - idev->msg_xfrd_r);

	जबतक (bytes_to_transfer-- > 0) अणु
		पूर्णांक c = पढ़ोl(idev->base + MST_DATA);

		अगर (idev->msg_xfrd_r == 0 && i2c_m_recv_len(msg)) अणु
			/*
			 * Check length byte क्रम SMBus block पढ़ो
			 */
			अगर (c <= 0 || c > I2C_SMBUS_BLOCK_MAX) अणु
				idev->msg_err = -EPROTO;
				i2c_पूर्णांक_disable(idev, ~MST_STATUS_TSS);
				complete(&idev->msg_complete);
				अवरोध;
			पूर्ण
			msg->len = 1 + c;
			ग_लिखोl(msg->len, idev->base + MST_RX_XFER);
		पूर्ण
		msg->buf[idev->msg_xfrd_r++] = c;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * axxia_i2c_fill_tx_fअगरo - Fill TX FIFO from current message buffer.
 * @वापस: Number of bytes left to transfer.
 */
अटल पूर्णांक axxia_i2c_fill_tx_fअगरo(काष्ठा axxia_i2c_dev *idev)
अणु
	काष्ठा i2c_msg *msg = idev->msg;
	माप_प्रकार tx_fअगरo_avail = FIFO_SIZE - पढ़ोl(idev->base + MST_TX_FIFO);
	पूर्णांक bytes_to_transfer = min(tx_fअगरo_avail, msg->len - idev->msg_xfrd);
	पूर्णांक ret = msg->len - idev->msg_xfrd - bytes_to_transfer;

	जबतक (bytes_to_transfer-- > 0)
		ग_लिखोl(msg->buf[idev->msg_xfrd++], idev->base + MST_DATA);

	वापस ret;
पूर्ण

अटल व्योम axxia_i2c_slv_fअगरo_event(काष्ठा axxia_i2c_dev *idev)
अणु
	u32 fअगरo_status = पढ़ोl(idev->base + SLV_RX_FIFO);
	u8 val;

	dev_dbg(idev->dev, "slave irq fifo_status=0x%x\n", fअगरo_status);

	अगर (fअगरo_status & SLV_FIFO_DV1) अणु
		अगर (fअगरo_status & SLV_FIFO_STRC)
			i2c_slave_event(idev->slave,
					I2C_SLAVE_WRITE_REQUESTED, &val);

		val = पढ़ोl(idev->base + SLV_DATA);
		i2c_slave_event(idev->slave, I2C_SLAVE_WRITE_RECEIVED, &val);
	पूर्ण
	अगर (fअगरo_status & SLV_FIFO_STPC) अणु
		पढ़ोl(idev->base + SLV_DATA); /* dummy पढ़ो */
		i2c_slave_event(idev->slave, I2C_SLAVE_STOP, &val);
	पूर्ण
	अगर (fअगरo_status & SLV_FIFO_RSC)
		पढ़ोl(idev->base + SLV_DATA); /* dummy पढ़ो */
पूर्ण

अटल irqवापस_t axxia_i2c_slv_isr(काष्ठा axxia_i2c_dev *idev)
अणु
	u32 status = पढ़ोl(idev->base + SLV_INT_STATUS);
	u8 val;

	dev_dbg(idev->dev, "slave irq status=0x%x\n", status);

	अगर (status & SLV_STATUS_RFH)
		axxia_i2c_slv_fअगरo_event(idev);
	अगर (status & SLV_STATUS_SRS1) अणु
		i2c_slave_event(idev->slave, I2C_SLAVE_READ_REQUESTED, &val);
		ग_लिखोl(val, idev->base + SLV_DATA);
	पूर्ण
	अगर (status & SLV_STATUS_SRND1) अणु
		i2c_slave_event(idev->slave, I2C_SLAVE_READ_PROCESSED, &val);
		ग_लिखोl(val, idev->base + SLV_DATA);
	पूर्ण
	अगर (status & SLV_STATUS_SRC1)
		i2c_slave_event(idev->slave, I2C_SLAVE_STOP, &val);

	ग_लिखोl(INT_SLV, idev->base + INTERRUPT_STATUS);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t axxia_i2c_isr(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा axxia_i2c_dev *idev = _dev;
	irqवापस_t ret = IRQ_NONE;
	u32 status;

	status = पढ़ोl(idev->base + INTERRUPT_STATUS);

	अगर (status & INT_SLV)
		ret = axxia_i2c_slv_isr(idev);
	अगर (!(status & INT_MST))
		वापस ret;

	/* Read पूर्णांकerrupt status bits */
	status = पढ़ोl(idev->base + MST_INT_STATUS);

	अगर (!idev->msg) अणु
		dev_warn(idev->dev, "unexpected interrupt\n");
		जाओ out;
	पूर्ण

	/* RX FIFO needs service? */
	अगर (i2c_m_rd(idev->msg_r) && (status & MST_STATUS_RFL))
		axxia_i2c_empty_rx_fअगरo(idev);

	/* TX FIFO needs service? */
	अगर (!i2c_m_rd(idev->msg) && (status & MST_STATUS_TFL)) अणु
		अगर (axxia_i2c_fill_tx_fअगरo(idev) == 0)
			i2c_पूर्णांक_disable(idev, MST_STATUS_TFL);
	पूर्ण

	अगर (unlikely(status & MST_STATUS_ERR)) अणु
		/* Transfer error */
		i2c_पूर्णांक_disable(idev, ~0);
		अगर (status & MST_STATUS_AL)
			idev->msg_err = -EAGAIN;
		अन्यथा अगर (status & MST_STATUS_NAK)
			idev->msg_err = -ENXIO;
		अन्यथा
			idev->msg_err = -EIO;
		dev_dbg(idev->dev, "error %#x, addr=%#x rx=%u/%u tx=%u/%u\n",
			status,
			idev->msg->addr,
			पढ़ोl(idev->base + MST_RX_BYTES_XFRD),
			पढ़ोl(idev->base + MST_RX_XFER),
			पढ़ोl(idev->base + MST_TX_BYTES_XFRD),
			पढ़ोl(idev->base + MST_TX_XFER));
		complete(&idev->msg_complete);
	पूर्ण अन्यथा अगर (status & MST_STATUS_SCC) अणु
		/* Stop completed */
		i2c_पूर्णांक_disable(idev, ~MST_STATUS_TSS);
		complete(&idev->msg_complete);
	पूर्ण अन्यथा अगर (status & (MST_STATUS_SNS | MST_STATUS_SS)) अणु
		/* Transfer करोne */
		पूर्णांक mask = idev->last ? ~0 : ~MST_STATUS_TSS;

		i2c_पूर्णांक_disable(idev, mask);
		अगर (i2c_m_rd(idev->msg_r) && idev->msg_xfrd_r < idev->msg_r->len)
			axxia_i2c_empty_rx_fअगरo(idev);
		complete(&idev->msg_complete);
	पूर्ण अन्यथा अगर (status & MST_STATUS_TSS) अणु
		/* Transfer समयout */
		idev->msg_err = -ETIMEDOUT;
		i2c_पूर्णांक_disable(idev, ~MST_STATUS_TSS);
		complete(&idev->msg_complete);
	पूर्ण

out:
	/* Clear पूर्णांकerrupt */
	ग_लिखोl(INT_MST, idev->base + INTERRUPT_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम axxia_i2c_set_addr(काष्ठा axxia_i2c_dev *idev, काष्ठा i2c_msg *msg)
अणु
	u32 addr_1, addr_2;

	अगर (i2c_m_ten(msg)) अणु
		/* 10-bit address
		 *   addr_1: 5'b11110 | addr[9:8] | (R/nW)
		 *   addr_2: addr[7:0]
		 */
		addr_1 = 0xF0 | ((msg->addr >> 7) & 0x06);
		अगर (i2c_m_rd(msg))
			addr_1 |= 1;	/* Set the R/nW bit of the address */
		addr_2 = msg->addr & 0xFF;
	पूर्ण अन्यथा अणु
		/* 7-bit address
		 *   addr_1: addr[6:0] | (R/nW)
		 *   addr_2: करोnt care
		 */
		addr_1 = i2c_8bit_addr_from_msg(msg);
		addr_2 = 0;
	पूर्ण

	ग_लिखोl(addr_1, idev->base + MST_ADDR_1);
	ग_लिखोl(addr_2, idev->base + MST_ADDR_2);
पूर्ण

/* The NAK पूर्णांकerrupt will be sent _beक्रमe_ issuing STOP command
 * so the controller might still be busy processing it. No
 * पूर्णांकerrupt will be sent at the end so we have to poll क्रम it
 */
अटल पूर्णांक axxia_i2c_handle_seq_nak(काष्ठा axxia_i2c_dev *idev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + I2C_XFER_TIMEOUT;

	करो अणु
		अगर ((पढ़ोl(idev->base + MST_COMMAND) & CMD_BUSY) == 0)
			वापस 0;
		usleep_range(1, 100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक axxia_i2c_xfer_seq(काष्ठा axxia_i2c_dev *idev, काष्ठा i2c_msg msgs[])
अणु
	u32 पूर्णांक_mask = MST_STATUS_ERR | MST_STATUS_SS | MST_STATUS_RFL;
	u32 rlen = i2c_m_recv_len(&msgs[1]) ? I2C_SMBUS_BLOCK_MAX : msgs[1].len;
	अचिन्हित दीर्घ समय_left;

	axxia_i2c_set_addr(idev, &msgs[0]);

	ग_लिखोl(msgs[0].len, idev->base + MST_TX_XFER);
	ग_लिखोl(rlen, idev->base + MST_RX_XFER);

	idev->msg = &msgs[0];
	idev->msg_r = &msgs[1];
	idev->msg_xfrd = 0;
	idev->msg_xfrd_r = 0;
	idev->last = true;
	axxia_i2c_fill_tx_fअगरo(idev);

	ग_लिखोl(CMD_SEQUENCE, idev->base + MST_COMMAND);

	reinit_completion(&idev->msg_complete);
	i2c_पूर्णांक_enable(idev, पूर्णांक_mask);

	समय_left = रुको_क्रम_completion_समयout(&idev->msg_complete,
						I2C_XFER_TIMEOUT);

	अगर (idev->msg_err == -ENXIO) अणु
		अगर (axxia_i2c_handle_seq_nak(idev))
			axxia_i2c_init(idev);
	पूर्ण अन्यथा अगर (पढ़ोl(idev->base + MST_COMMAND) & CMD_BUSY) अणु
		dev_warn(idev->dev, "busy after xfer\n");
	पूर्ण

	अगर (समय_left == 0) अणु
		idev->msg_err = -ETIMEDOUT;
		i2c_recover_bus(&idev->adapter);
		axxia_i2c_init(idev);
	पूर्ण

	अगर (unlikely(idev->msg_err) && idev->msg_err != -ENXIO)
		axxia_i2c_init(idev);

	वापस idev->msg_err;
पूर्ण

अटल पूर्णांक axxia_i2c_xfer_msg(काष्ठा axxia_i2c_dev *idev, काष्ठा i2c_msg *msg,
			      bool last)
अणु
	u32 पूर्णांक_mask = MST_STATUS_ERR;
	u32 rx_xfer, tx_xfer;
	अचिन्हित दीर्घ समय_left;
	अचिन्हित पूर्णांक wt_value;

	idev->msg = msg;
	idev->msg_r = msg;
	idev->msg_xfrd = 0;
	idev->msg_xfrd_r = 0;
	idev->last = last;
	reinit_completion(&idev->msg_complete);

	axxia_i2c_set_addr(idev, msg);

	अगर (i2c_m_rd(msg)) अणु
		/* I2C पढ़ो transfer */
		rx_xfer = i2c_m_recv_len(msg) ? I2C_SMBUS_BLOCK_MAX : msg->len;
		tx_xfer = 0;
	पूर्ण अन्यथा अणु
		/* I2C ग_लिखो transfer */
		rx_xfer = 0;
		tx_xfer = msg->len;
	पूर्ण

	ग_लिखोl(rx_xfer, idev->base + MST_RX_XFER);
	ग_लिखोl(tx_xfer, idev->base + MST_TX_XFER);

	अगर (i2c_m_rd(msg))
		पूर्णांक_mask |= MST_STATUS_RFL;
	अन्यथा अगर (axxia_i2c_fill_tx_fअगरo(idev) != 0)
		पूर्णांक_mask |= MST_STATUS_TFL;

	wt_value = WT_VALUE(पढ़ोl(idev->base + WAIT_TIMER_CONTROL));
	/* Disable रुको समयr temporarly */
	ग_लिखोl(wt_value, idev->base + WAIT_TIMER_CONTROL);
	/* Check अगर समयout error happened */
	अगर (idev->msg_err)
		जाओ out;

	अगर (!last) अणु
		ग_लिखोl(CMD_MANUAL, idev->base + MST_COMMAND);
		पूर्णांक_mask |= MST_STATUS_SNS;
	पूर्ण अन्यथा अणु
		ग_लिखोl(CMD_AUTO, idev->base + MST_COMMAND);
		पूर्णांक_mask |= MST_STATUS_SS;
	पूर्ण

	ग_लिखोl(WT_EN | wt_value, idev->base + WAIT_TIMER_CONTROL);

	i2c_पूर्णांक_enable(idev, पूर्णांक_mask);

	समय_left = रुको_क्रम_completion_समयout(&idev->msg_complete,
					      I2C_XFER_TIMEOUT);

	i2c_पूर्णांक_disable(idev, पूर्णांक_mask);

	अगर (पढ़ोl(idev->base + MST_COMMAND) & CMD_BUSY)
		dev_warn(idev->dev, "busy after xfer\n");

	अगर (समय_left == 0) अणु
		idev->msg_err = -ETIMEDOUT;
		i2c_recover_bus(&idev->adapter);
		axxia_i2c_init(idev);
	पूर्ण

out:
	अगर (unlikely(idev->msg_err) && idev->msg_err != -ENXIO &&
			idev->msg_err != -ETIMEDOUT)
		axxia_i2c_init(idev);

	वापस idev->msg_err;
पूर्ण

/* This function checks अगर the msgs[] array contains messages compatible with
 * Sequence mode of operation. This mode assumes there will be exactly one
 * ग_लिखो of non-zero length followed by exactly one पढ़ो of non-zero length,
 * both targeted at the same client device.
 */
अटल bool axxia_i2c_sequence_ok(काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	वापस num == SEQ_LEN && !i2c_m_rd(&msgs[0]) && i2c_m_rd(&msgs[1]) &&
	       msgs[0].len > 0 && msgs[0].len <= FIFO_SIZE &&
	       msgs[1].len > 0 && msgs[0].addr == msgs[1].addr;
पूर्ण

अटल पूर्णांक
axxia_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	पूर्णांक i;
	पूर्णांक ret = 0;

	idev->msg_err = 0;

	अगर (axxia_i2c_sequence_ok(msgs, num)) अणु
		ret = axxia_i2c_xfer_seq(idev, msgs);
		वापस ret ? : SEQ_LEN;
	पूर्ण

	i2c_पूर्णांक_enable(idev, MST_STATUS_TSS);

	क्रम (i = 0; ret == 0 && i < num; ++i)
		ret = axxia_i2c_xfer_msg(idev, &msgs[i], i == (num - 1));

	वापस ret ? : i;
पूर्ण

अटल पूर्णांक axxia_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(idev->base + I2C_BUS_MONITOR) & BM_SCLS);
पूर्ण

अटल व्योम axxia_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	u32 पंचांगp;

	/* Preserve SDA Control */
	पंचांगp = पढ़ोl(idev->base + I2C_BUS_MONITOR) & BM_SDAC;
	अगर (!val)
		पंचांगp |= BM_SCLC;
	ग_लिखोl(पंचांगp, idev->base + I2C_BUS_MONITOR);
पूर्ण

अटल पूर्णांक axxia_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(adap);

	वापस !!(पढ़ोl(idev->base + I2C_BUS_MONITOR) & BM_SDAS);
पूर्ण

अटल काष्ठा i2c_bus_recovery_info axxia_i2c_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.get_scl = axxia_i2c_get_scl,
	.set_scl = axxia_i2c_set_scl,
	.get_sda = axxia_i2c_get_sda,
पूर्ण;

अटल u32 axxia_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	u32 caps = (I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR |
		    I2C_FUNC_SMBUS_EMUL | I2C_FUNC_SMBUS_BLOCK_DATA);
	वापस caps;
पूर्ण

अटल पूर्णांक axxia_i2c_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(slave->adapter);
	u32 slv_पूर्णांक_mask = SLV_STATUS_RFH;
	u32 dec_ctl;

	अगर (idev->slave)
		वापस -EBUSY;

	idev->slave = slave;

	/* Enable slave mode as well */
	ग_लिखोl(GLOBAL_MST_EN | GLOBAL_SLV_EN, idev->base + GLOBAL_CONTROL);
	ग_लिखोl(INT_MST | INT_SLV, idev->base + INTERRUPT_ENABLE);

	/* Set slave address */
	dec_ctl = SLV_ADDR_DEC_SA1E;
	अगर (slave->flags & I2C_CLIENT_TEN)
		dec_ctl |= SLV_ADDR_DEC_SA1M;

	ग_लिखोl(SLV_RX_ACSA1, idev->base + SLV_RX_CTL);
	ग_लिखोl(dec_ctl, idev->base + SLV_ADDR_DEC_CTL);
	ग_लिखोl(slave->addr, idev->base + SLV_ADDR_1);

	/* Enable पूर्णांकerrupts */
	slv_पूर्णांक_mask |= SLV_STATUS_SRS1 | SLV_STATUS_SRRS1 | SLV_STATUS_SRND1;
	slv_पूर्णांक_mask |= SLV_STATUS_SRC1;
	ग_लिखोl(slv_पूर्णांक_mask, idev->base + SLV_INT_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक axxia_i2c_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा axxia_i2c_dev *idev = i2c_get_adapdata(slave->adapter);

	/* Disable slave mode */
	ग_लिखोl(GLOBAL_MST_EN, idev->base + GLOBAL_CONTROL);
	ग_लिखोl(INT_MST, idev->base + INTERRUPT_ENABLE);

	synchronize_irq(idev->irq);

	idev->slave = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm axxia_i2c_algo = अणु
	.master_xfer = axxia_i2c_xfer,
	.functionality = axxia_i2c_func,
	.reg_slave = axxia_i2c_reg_slave,
	.unreg_slave = axxia_i2c_unreg_slave,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks axxia_i2c_quirks = अणु
	.max_पढ़ो_len = 255,
	.max_ग_लिखो_len = 255,
पूर्ण;

अटल पूर्णांक axxia_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा axxia_i2c_dev *idev = शून्य;
	व्योम __iomem *base;
	पूर्णांक ret = 0;

	idev = devm_kzalloc(&pdev->dev, माप(*idev), GFP_KERNEL);
	अगर (!idev)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	idev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (idev->irq < 0)
		वापस idev->irq;

	idev->i2c_clk = devm_clk_get(&pdev->dev, "i2c");
	अगर (IS_ERR(idev->i2c_clk)) अणु
		dev_err(&pdev->dev, "missing clock\n");
		वापस PTR_ERR(idev->i2c_clk);
	पूर्ण

	idev->base = base;
	idev->dev = &pdev->dev;
	init_completion(&idev->msg_complete);

	of_property_पढ़ो_u32(np, "clock-frequency", &idev->bus_clk_rate);
	अगर (idev->bus_clk_rate == 0)
		idev->bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;	/* शेष घड़ी rate */

	ret = clk_prepare_enable(idev->i2c_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	ret = axxia_i2c_init(idev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to initialize\n");
		जाओ error_disable_clk;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, idev->irq, axxia_i2c_isr, 0,
			       pdev->name, idev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim IRQ%d\n", idev->irq);
		जाओ error_disable_clk;
	पूर्ण

	i2c_set_adapdata(&idev->adapter, idev);
	strlcpy(idev->adapter.name, pdev->name, माप(idev->adapter.name));
	idev->adapter.owner = THIS_MODULE;
	idev->adapter.algo = &axxia_i2c_algo;
	idev->adapter.bus_recovery_info = &axxia_i2c_recovery_info;
	idev->adapter.quirks = &axxia_i2c_quirks;
	idev->adapter.dev.parent = &pdev->dev;
	idev->adapter.dev.of_node = pdev->dev.of_node;

	platक्रमm_set_drvdata(pdev, idev);

	ret = i2c_add_adapter(&idev->adapter);
	अगर (ret)
		जाओ error_disable_clk;

	वापस 0;

error_disable_clk:
	clk_disable_unprepare(idev->i2c_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक axxia_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axxia_i2c_dev *idev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(idev->i2c_clk);
	i2c_del_adapter(&idev->adapter);

	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id axxia_i2c_of_match[] = अणु
	अणु .compatible = "lsi,api2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, axxia_i2c_of_match);

अटल काष्ठा platक्रमm_driver axxia_i2c_driver = अणु
	.probe = axxia_i2c_probe,
	.हटाओ = axxia_i2c_हटाओ,
	.driver = अणु
		.name = "axxia-i2c",
		.of_match_table = axxia_i2c_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axxia_i2c_driver);

MODULE_DESCRIPTION("Axxia I2C Bus driver");
MODULE_AUTHOR("Anders Berg <anders.berg@lsi.com>");
MODULE_LICENSE("GPL v2");
