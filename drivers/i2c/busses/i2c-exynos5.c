<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c-exynos5.c - Samsung Exynos5 I2C Controller Driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/i2c.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>

/*
 * HSI2C controller from Samsung supports 2 modes of operation
 * 1. Auto mode: Where in master स्वतःmatically controls the whole transaction
 * 2. Manual mode: Software controls the transaction by issuing commands
 *    START, READ, WRITE, STOP, RESTART in I2C_MANUAL_CMD रेजिस्टर.
 *
 * Operation mode can be selected by setting AUTO_MODE bit in I2C_CONF रेजिस्टर
 *
 * Special bits are available क्रम both modes of operation to set commands
 * and क्रम checking transfer status
 */

/* Register Map */
#घोषणा HSI2C_CTL		0x00
#घोषणा HSI2C_FIFO_CTL		0x04
#घोषणा HSI2C_TRAILIG_CTL	0x08
#घोषणा HSI2C_CLK_CTL		0x0C
#घोषणा HSI2C_CLK_SLOT		0x10
#घोषणा HSI2C_INT_ENABLE	0x20
#घोषणा HSI2C_INT_STATUS	0x24
#घोषणा HSI2C_ERR_STATUS	0x2C
#घोषणा HSI2C_FIFO_STATUS	0x30
#घोषणा HSI2C_TX_DATA		0x34
#घोषणा HSI2C_RX_DATA		0x38
#घोषणा HSI2C_CONF		0x40
#घोषणा HSI2C_AUTO_CONF		0x44
#घोषणा HSI2C_TIMEOUT		0x48
#घोषणा HSI2C_MANUAL_CMD	0x4C
#घोषणा HSI2C_TRANS_STATUS	0x50
#घोषणा HSI2C_TIMING_HS1	0x54
#घोषणा HSI2C_TIMING_HS2	0x58
#घोषणा HSI2C_TIMING_HS3	0x5C
#घोषणा HSI2C_TIMING_FS1	0x60
#घोषणा HSI2C_TIMING_FS2	0x64
#घोषणा HSI2C_TIMING_FS3	0x68
#घोषणा HSI2C_TIMING_SLA	0x6C
#घोषणा HSI2C_ADDR		0x70

/* I2C_CTL Register bits */
#घोषणा HSI2C_FUNC_MODE_I2C			(1u << 0)
#घोषणा HSI2C_MASTER				(1u << 3)
#घोषणा HSI2C_RXCHON				(1u << 6)
#घोषणा HSI2C_TXCHON				(1u << 7)
#घोषणा HSI2C_SW_RST				(1u << 31)

/* I2C_FIFO_CTL Register bits */
#घोषणा HSI2C_RXFIFO_EN				(1u << 0)
#घोषणा HSI2C_TXFIFO_EN				(1u << 1)
#घोषणा HSI2C_RXFIFO_TRIGGER_LEVEL(x)		((x) << 4)
#घोषणा HSI2C_TXFIFO_TRIGGER_LEVEL(x)		((x) << 16)

/* I2C_TRAILING_CTL Register bits */
#घोषणा HSI2C_TRAILING_COUNT			(0xf)

/* I2C_INT_EN Register bits */
#घोषणा HSI2C_INT_TX_ALMOSTEMPTY_EN		(1u << 0)
#घोषणा HSI2C_INT_RX_ALMOSTFULL_EN		(1u << 1)
#घोषणा HSI2C_INT_TRAILING_EN			(1u << 6)

/* I2C_INT_STAT Register bits */
#घोषणा HSI2C_INT_TX_ALMOSTEMPTY		(1u << 0)
#घोषणा HSI2C_INT_RX_ALMOSTFULL			(1u << 1)
#घोषणा HSI2C_INT_TX_UNDERRUN			(1u << 2)
#घोषणा HSI2C_INT_TX_OVERRUN			(1u << 3)
#घोषणा HSI2C_INT_RX_UNDERRUN			(1u << 4)
#घोषणा HSI2C_INT_RX_OVERRUN			(1u << 5)
#घोषणा HSI2C_INT_TRAILING			(1u << 6)
#घोषणा HSI2C_INT_I2C				(1u << 9)

#घोषणा HSI2C_INT_TRANS_DONE			(1u << 7)
#घोषणा HSI2C_INT_TRANS_ABORT			(1u << 8)
#घोषणा HSI2C_INT_NO_DEV_ACK			(1u << 9)
#घोषणा HSI2C_INT_NO_DEV			(1u << 10)
#घोषणा HSI2C_INT_TIMEOUT			(1u << 11)
#घोषणा HSI2C_INT_I2C_TRANS			(HSI2C_INT_TRANS_DONE |	\
						HSI2C_INT_TRANS_ABORT |	\
						HSI2C_INT_NO_DEV_ACK |	\
						HSI2C_INT_NO_DEV |	\
						HSI2C_INT_TIMEOUT)

/* I2C_FIFO_STAT Register bits */
#घोषणा HSI2C_RX_FIFO_EMPTY			(1u << 24)
#घोषणा HSI2C_RX_FIFO_FULL			(1u << 23)
#घोषणा HSI2C_RX_FIFO_LVL(x)			((x >> 16) & 0x7f)
#घोषणा HSI2C_TX_FIFO_EMPTY			(1u << 8)
#घोषणा HSI2C_TX_FIFO_FULL			(1u << 7)
#घोषणा HSI2C_TX_FIFO_LVL(x)			((x >> 0) & 0x7f)

/* I2C_CONF Register bits */
#घोषणा HSI2C_AUTO_MODE				(1u << 31)
#घोषणा HSI2C_10BIT_ADDR_MODE			(1u << 30)
#घोषणा HSI2C_HS_MODE				(1u << 29)

/* I2C_AUTO_CONF Register bits */
#घोषणा HSI2C_READ_WRITE			(1u << 16)
#घोषणा HSI2C_STOP_AFTER_TRANS			(1u << 17)
#घोषणा HSI2C_MASTER_RUN			(1u << 31)

/* I2C_TIMEOUT Register bits */
#घोषणा HSI2C_TIMEOUT_EN			(1u << 31)
#घोषणा HSI2C_TIMEOUT_MASK			0xff

/* I2C_MANUAL_CMD रेजिस्टर bits */
#घोषणा HSI2C_CMD_READ_DATA			(1u << 4)
#घोषणा HSI2C_CMD_SEND_STOP			(1u << 2)

/* I2C_TRANS_STATUS रेजिस्टर bits */
#घोषणा HSI2C_MASTER_BUSY			(1u << 17)
#घोषणा HSI2C_SLAVE_BUSY			(1u << 16)

/* I2C_TRANS_STATUS रेजिस्टर bits क्रम Exynos5 variant */
#घोषणा HSI2C_TIMEOUT_AUTO			(1u << 4)
#घोषणा HSI2C_NO_DEV				(1u << 3)
#घोषणा HSI2C_NO_DEV_ACK			(1u << 2)
#घोषणा HSI2C_TRANS_ABORT			(1u << 1)
#घोषणा HSI2C_TRANS_DONE			(1u << 0)

/* I2C_TRANS_STATUS रेजिस्टर bits क्रम Exynos7 variant */
#घोषणा HSI2C_MASTER_ST_MASK			0xf
#घोषणा HSI2C_MASTER_ST_IDLE			0x0
#घोषणा HSI2C_MASTER_ST_START			0x1
#घोषणा HSI2C_MASTER_ST_RESTART			0x2
#घोषणा HSI2C_MASTER_ST_STOP			0x3
#घोषणा HSI2C_MASTER_ST_MASTER_ID		0x4
#घोषणा HSI2C_MASTER_ST_ADDR0			0x5
#घोषणा HSI2C_MASTER_ST_ADDR1			0x6
#घोषणा HSI2C_MASTER_ST_ADDR2			0x7
#घोषणा HSI2C_MASTER_ST_ADDR_SR			0x8
#घोषणा HSI2C_MASTER_ST_READ			0x9
#घोषणा HSI2C_MASTER_ST_WRITE			0xa
#घोषणा HSI2C_MASTER_ST_NO_ACK			0xb
#घोषणा HSI2C_MASTER_ST_LOSE			0xc
#घोषणा HSI2C_MASTER_ST_WAIT			0xd
#घोषणा HSI2C_MASTER_ST_WAIT_CMD		0xe

/* I2C_ADDR रेजिस्टर bits */
#घोषणा HSI2C_SLV_ADDR_SLV(x)			((x & 0x3ff) << 0)
#घोषणा HSI2C_SLV_ADDR_MAS(x)			((x & 0x3ff) << 10)
#घोषणा HSI2C_MASTER_ID(x)			((x & 0xff) << 24)
#घोषणा MASTER_ID(x)				((x & 0x7) + 0x08)

#घोषणा EXYNOS5_I2C_TIMEOUT (msecs_to_jअगरfies(100))

क्रमागत i2c_type_exynos अणु
	I2C_TYPE_EXYNOS5,
	I2C_TYPE_EXYNOS7,
पूर्ण;

काष्ठा exynos5_i2c अणु
	काष्ठा i2c_adapter	adap;

	काष्ठा i2c_msg		*msg;
	काष्ठा completion	msg_complete;
	अचिन्हित पूर्णांक		msg_ptr;

	अचिन्हित पूर्णांक		irq;

	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	काष्ठा device		*dev;
	पूर्णांक			state;

	spinlock_t		lock;		/* IRQ synchronization */

	/*
	 * Since the TRANS_DONE bit is cleared on पढ़ो, and we may पढ़ो it
	 * either during an IRQ or after a transaction, keep track of its
	 * state here.
	 */
	पूर्णांक			trans_करोne;

	/* Controller operating frequency */
	अचिन्हित पूर्णांक		op_घड़ी;

	/* Version of HS-I2C Hardware */
	स्थिर काष्ठा exynos_hsi2c_variant *variant;
पूर्ण;

/**
 * काष्ठा exynos_hsi2c_variant - platक्रमm specअगरic HSI2C driver data
 * @fअगरo_depth: the fअगरo depth supported by the HSI2C module
 * @hw: the hardware variant of Exynos I2C controller
 *
 * Specअगरies platक्रमm specअगरic configuration of HSI2C module.
 * Note: A काष्ठाure क्रम driver specअगरic platक्रमm data is used क्रम future
 * expansion of its usage.
 */
काष्ठा exynos_hsi2c_variant अणु
	अचिन्हित पूर्णांक		fअगरo_depth;
	क्रमागत i2c_type_exynos	hw;
पूर्ण;

अटल स्थिर काष्ठा exynos_hsi2c_variant exynos5250_hsi2c_data = अणु
	.fअगरo_depth	= 64,
	.hw		= I2C_TYPE_EXYNOS5,
पूर्ण;

अटल स्थिर काष्ठा exynos_hsi2c_variant exynos5260_hsi2c_data = अणु
	.fअगरo_depth	= 16,
	.hw		= I2C_TYPE_EXYNOS5,
पूर्ण;

अटल स्थिर काष्ठा exynos_hsi2c_variant exynos7_hsi2c_data = अणु
	.fअगरo_depth	= 16,
	.hw		= I2C_TYPE_EXYNOS7,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos5_i2c_match[] = अणु
	अणु
		.compatible = "samsung,exynos5-hsi2c",
		.data = &exynos5250_hsi2c_data
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-hsi2c",
		.data = &exynos5250_hsi2c_data
	पूर्ण, अणु
		.compatible = "samsung,exynos5260-hsi2c",
		.data = &exynos5260_hsi2c_data
	पूर्ण, अणु
		.compatible = "samsung,exynos7-hsi2c",
		.data = &exynos7_hsi2c_data
	पूर्ण, अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos5_i2c_match);

अटल व्योम exynos5_i2c_clr_pend_irq(काष्ठा exynos5_i2c *i2c)
अणु
	ग_लिखोl(पढ़ोl(i2c->regs + HSI2C_INT_STATUS),
				i2c->regs + HSI2C_INT_STATUS);
पूर्ण

/*
 * exynos5_i2c_set_timing: updates the रेजिस्टरs with appropriate
 * timing values calculated
 *
 * Timing values क्रम operation are calculated against either 100kHz
 * or 1MHz controller operating frequency.
 *
 * Returns 0 on success, -EINVAL अगर the cycle length cannot
 * be calculated.
 */
अटल पूर्णांक exynos5_i2c_set_timing(काष्ठा exynos5_i2c *i2c, bool hs_timings)
अणु
	u32 i2c_timing_s1;
	u32 i2c_timing_s2;
	u32 i2c_timing_s3;
	u32 i2c_timing_sla;
	अचिन्हित पूर्णांक t_start_su, t_start_hd;
	अचिन्हित पूर्णांक t_stop_su;
	अचिन्हित पूर्णांक t_data_su, t_data_hd;
	अचिन्हित पूर्णांक t_scl_l, t_scl_h;
	अचिन्हित पूर्णांक t_sr_release;
	अचिन्हित पूर्णांक t_ftl_cycle;
	अचिन्हित पूर्णांक clkin = clk_get_rate(i2c->clk);
	अचिन्हित पूर्णांक op_clk = hs_timings ? i2c->op_घड़ी :
		(i2c->op_घड़ी >= I2C_MAX_FAST_MODE_PLUS_FREQ) ? I2C_MAX_STANDARD_MODE_FREQ :
		i2c->op_घड़ी;
	पूर्णांक भाग, clk_cycle, temp;

	/*
	 * In हाल of HSI2C controller in Exynos5 series
	 * FPCLK / FI2C =
	 * (CLK_DIV + 1) * (TSCLK_L + TSCLK_H + 2) + 8 + 2 * FLT_CYCLE
	 *
	 * In हाल of HSI2C controllers in Exynos7 series
	 * FPCLK / FI2C =
	 * (CLK_DIV + 1) * (TSCLK_L + TSCLK_H + 2) + 8 + FLT_CYCLE
	 *
	 * clk_cycle := TSCLK_L + TSCLK_H
	 * temp := (CLK_DIV + 1) * (clk_cycle + 2)
	 *
	 * Constraपूर्णांकs: 4 <= temp, 0 <= CLK_DIV < 256, 2 <= clk_cycle <= 510
	 *
	 */
	t_ftl_cycle = (पढ़ोl(i2c->regs + HSI2C_CONF) >> 16) & 0x7;
	temp = clkin / op_clk - 8 - t_ftl_cycle;
	अगर (i2c->variant->hw != I2C_TYPE_EXYNOS7)
		temp -= t_ftl_cycle;
	भाग = temp / 512;
	clk_cycle = temp / (भाग + 1) - 2;
	अगर (temp < 4 || भाग >= 256 || clk_cycle < 2) अणु
		dev_err(i2c->dev, "%s clock set-up failed\n",
			hs_timings ? "HS" : "FS");
		वापस -EINVAL;
	पूर्ण

	t_scl_l = clk_cycle / 2;
	t_scl_h = clk_cycle / 2;
	t_start_su = t_scl_l;
	t_start_hd = t_scl_l;
	t_stop_su = t_scl_l;
	t_data_su = t_scl_l / 2;
	t_data_hd = t_scl_l / 2;
	t_sr_release = clk_cycle;

	i2c_timing_s1 = t_start_su << 24 | t_start_hd << 16 | t_stop_su << 8;
	i2c_timing_s2 = t_data_su << 24 | t_scl_l << 8 | t_scl_h << 0;
	i2c_timing_s3 = भाग << 16 | t_sr_release << 0;
	i2c_timing_sla = t_data_hd << 0;

	dev_dbg(i2c->dev, "tSTART_SU: %X, tSTART_HD: %X, tSTOP_SU: %X\n",
		t_start_su, t_start_hd, t_stop_su);
	dev_dbg(i2c->dev, "tDATA_SU: %X, tSCL_L: %X, tSCL_H: %X\n",
		t_data_su, t_scl_l, t_scl_h);
	dev_dbg(i2c->dev, "nClkDiv: %X, tSR_RELEASE: %X\n",
		भाग, t_sr_release);
	dev_dbg(i2c->dev, "tDATA_HD: %X\n", t_data_hd);

	अगर (hs_timings) अणु
		ग_लिखोl(i2c_timing_s1, i2c->regs + HSI2C_TIMING_HS1);
		ग_लिखोl(i2c_timing_s2, i2c->regs + HSI2C_TIMING_HS2);
		ग_लिखोl(i2c_timing_s3, i2c->regs + HSI2C_TIMING_HS3);
	पूर्ण अन्यथा अणु
		ग_लिखोl(i2c_timing_s1, i2c->regs + HSI2C_TIMING_FS1);
		ग_लिखोl(i2c_timing_s2, i2c->regs + HSI2C_TIMING_FS2);
		ग_लिखोl(i2c_timing_s3, i2c->regs + HSI2C_TIMING_FS3);
	पूर्ण
	ग_लिखोl(i2c_timing_sla, i2c->regs + HSI2C_TIMING_SLA);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_hsi2c_घड़ी_setup(काष्ठा exynos5_i2c *i2c)
अणु
	/* always set Fast Speed timings */
	पूर्णांक ret = exynos5_i2c_set_timing(i2c, false);

	अगर (ret < 0 || i2c->op_घड़ी < I2C_MAX_FAST_MODE_PLUS_FREQ)
		वापस ret;

	वापस exynos5_i2c_set_timing(i2c, true);
पूर्ण

/*
 * exynos5_i2c_init: configures the controller क्रम I2C functionality
 * Programs I2C controller क्रम Master mode operation
 */
अटल व्योम exynos5_i2c_init(काष्ठा exynos5_i2c *i2c)
अणु
	u32 i2c_conf = पढ़ोl(i2c->regs + HSI2C_CONF);
	u32 i2c_समयout = पढ़ोl(i2c->regs + HSI2C_TIMEOUT);

	/* Clear to disable Timeout */
	i2c_समयout &= ~HSI2C_TIMEOUT_EN;
	ग_लिखोl(i2c_समयout, i2c->regs + HSI2C_TIMEOUT);

	ग_लिखोl((HSI2C_FUNC_MODE_I2C | HSI2C_MASTER),
					i2c->regs + HSI2C_CTL);
	ग_लिखोl(HSI2C_TRAILING_COUNT, i2c->regs + HSI2C_TRAILIG_CTL);

	अगर (i2c->op_घड़ी >= I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		ग_लिखोl(HSI2C_MASTER_ID(MASTER_ID(i2c->adap.nr)),
					i2c->regs + HSI2C_ADDR);
		i2c_conf |= HSI2C_HS_MODE;
	पूर्ण

	ग_लिखोl(i2c_conf | HSI2C_AUTO_MODE, i2c->regs + HSI2C_CONF);
पूर्ण

अटल व्योम exynos5_i2c_reset(काष्ठा exynos5_i2c *i2c)
अणु
	u32 i2c_ctl;

	/* Set and clear the bit क्रम reset */
	i2c_ctl = पढ़ोl(i2c->regs + HSI2C_CTL);
	i2c_ctl |= HSI2C_SW_RST;
	ग_लिखोl(i2c_ctl, i2c->regs + HSI2C_CTL);

	i2c_ctl = पढ़ोl(i2c->regs + HSI2C_CTL);
	i2c_ctl &= ~HSI2C_SW_RST;
	ग_लिखोl(i2c_ctl, i2c->regs + HSI2C_CTL);

	/* We करोn't expect calculations to fail during the run */
	exynos5_hsi2c_घड़ी_setup(i2c);
	/* Initialize the configure रेजिस्टरs */
	exynos5_i2c_init(i2c);
पूर्ण

/*
 * exynos5_i2c_irq: top level IRQ servicing routine
 *
 * INT_STATUS रेजिस्टरs gives the पूर्णांकerrupt details. Further,
 * FIFO_STATUS or TRANS_STATUS रेजिस्टरs are to be check क्रम detailed
 * state of the bus.
 */
अटल irqवापस_t exynos5_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा exynos5_i2c *i2c = dev_id;
	u32 fअगरo_level, पूर्णांक_status, fअगरo_status, trans_status;
	अचिन्हित अक्षर byte;
	पूर्णांक len = 0;

	i2c->state = -EINVAL;

	spin_lock(&i2c->lock);

	पूर्णांक_status = पढ़ोl(i2c->regs + HSI2C_INT_STATUS);
	ग_लिखोl(पूर्णांक_status, i2c->regs + HSI2C_INT_STATUS);

	/* handle पूर्णांकerrupt related to the transfer status */
	अगर (i2c->variant->hw == I2C_TYPE_EXYNOS7) अणु
		अगर (पूर्णांक_status & HSI2C_INT_TRANS_DONE) अणु
			i2c->trans_करोne = 1;
			i2c->state = 0;
		पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_TRANS_ABORT) अणु
			dev_dbg(i2c->dev, "Deal with arbitration lose\n");
			i2c->state = -EAGAIN;
			जाओ stop;
		पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_NO_DEV_ACK) अणु
			dev_dbg(i2c->dev, "No ACK from device\n");
			i2c->state = -ENXIO;
			जाओ stop;
		पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_NO_DEV) अणु
			dev_dbg(i2c->dev, "No device\n");
			i2c->state = -ENXIO;
			जाओ stop;
		पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_TIMEOUT) अणु
			dev_dbg(i2c->dev, "Accessing device timed out\n");
			i2c->state = -ETIMEDOUT;
			जाओ stop;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_I2C) अणु
		trans_status = पढ़ोl(i2c->regs + HSI2C_TRANS_STATUS);
		अगर (trans_status & HSI2C_NO_DEV_ACK) अणु
			dev_dbg(i2c->dev, "No ACK from device\n");
			i2c->state = -ENXIO;
			जाओ stop;
		पूर्ण अन्यथा अगर (trans_status & HSI2C_NO_DEV) अणु
			dev_dbg(i2c->dev, "No device\n");
			i2c->state = -ENXIO;
			जाओ stop;
		पूर्ण अन्यथा अगर (trans_status & HSI2C_TRANS_ABORT) अणु
			dev_dbg(i2c->dev, "Deal with arbitration lose\n");
			i2c->state = -EAGAIN;
			जाओ stop;
		पूर्ण अन्यथा अगर (trans_status & HSI2C_TIMEOUT_AUTO) अणु
			dev_dbg(i2c->dev, "Accessing device timed out\n");
			i2c->state = -ETIMEDOUT;
			जाओ stop;
		पूर्ण अन्यथा अगर (trans_status & HSI2C_TRANS_DONE) अणु
			i2c->trans_करोne = 1;
			i2c->state = 0;
		पूर्ण
	पूर्ण

	अगर ((i2c->msg->flags & I2C_M_RD) && (पूर्णांक_status &
			(HSI2C_INT_TRAILING | HSI2C_INT_RX_ALMOSTFULL))) अणु
		fअगरo_status = पढ़ोl(i2c->regs + HSI2C_FIFO_STATUS);
		fअगरo_level = HSI2C_RX_FIFO_LVL(fअगरo_status);
		len = min(fअगरo_level, i2c->msg->len - i2c->msg_ptr);

		जबतक (len > 0) अणु
			byte = (अचिन्हित अक्षर)
				पढ़ोl(i2c->regs + HSI2C_RX_DATA);
			i2c->msg->buf[i2c->msg_ptr++] = byte;
			len--;
		पूर्ण
		i2c->state = 0;
	पूर्ण अन्यथा अगर (पूर्णांक_status & HSI2C_INT_TX_ALMOSTEMPTY) अणु
		fअगरo_status = पढ़ोl(i2c->regs + HSI2C_FIFO_STATUS);
		fअगरo_level = HSI2C_TX_FIFO_LVL(fअगरo_status);

		len = i2c->variant->fअगरo_depth - fअगरo_level;
		अगर (len > (i2c->msg->len - i2c->msg_ptr)) अणु
			u32 पूर्णांक_en = पढ़ोl(i2c->regs + HSI2C_INT_ENABLE);

			पूर्णांक_en &= ~HSI2C_INT_TX_ALMOSTEMPTY_EN;
			ग_लिखोl(पूर्णांक_en, i2c->regs + HSI2C_INT_ENABLE);
			len = i2c->msg->len - i2c->msg_ptr;
		पूर्ण

		जबतक (len > 0) अणु
			byte = i2c->msg->buf[i2c->msg_ptr++];
			ग_लिखोl(byte, i2c->regs + HSI2C_TX_DATA);
			len--;
		पूर्ण
		i2c->state = 0;
	पूर्ण

 stop:
	अगर ((i2c->trans_करोne && (i2c->msg->len == i2c->msg_ptr)) ||
	    (i2c->state < 0)) अणु
		ग_लिखोl(0, i2c->regs + HSI2C_INT_ENABLE);
		exynos5_i2c_clr_pend_irq(i2c);
		complete(&i2c->msg_complete);
	पूर्ण

	spin_unlock(&i2c->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * exynos5_i2c_रुको_bus_idle
 *
 * Wait क्रम the bus to go idle, indicated by the MASTER_BUSY bit being
 * cleared.
 *
 * Returns -EBUSY अगर the bus cannot be bought to idle
 */
अटल पूर्णांक exynos5_i2c_रुको_bus_idle(काष्ठा exynos5_i2c *i2c)
अणु
	अचिन्हित दीर्घ stop_समय;
	u32 trans_status;

	/* रुको क्रम 100 milli seconds क्रम the bus to be idle */
	stop_समय = jअगरfies + msecs_to_jअगरfies(100) + 1;
	करो अणु
		trans_status = पढ़ोl(i2c->regs + HSI2C_TRANS_STATUS);
		अगर (!(trans_status & HSI2C_MASTER_BUSY))
			वापस 0;

		usleep_range(50, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop_समय));

	वापस -EBUSY;
पूर्ण

अटल व्योम exynos5_i2c_bus_recover(काष्ठा exynos5_i2c *i2c)
अणु
	u32 val;

	val = पढ़ोl(i2c->regs + HSI2C_CTL) | HSI2C_RXCHON;
	ग_लिखोl(val, i2c->regs + HSI2C_CTL);
	val = पढ़ोl(i2c->regs + HSI2C_CONF) & ~HSI2C_AUTO_MODE;
	ग_लिखोl(val, i2c->regs + HSI2C_CONF);

	/*
	 * Specअगरication says master should send nine घड़ी pulses. It can be
	 * emulated by sending manual पढ़ो command (nine pulses क्रम पढ़ो eight
	 * bits + one pulse क्रम NACK).
	 */
	ग_लिखोl(HSI2C_CMD_READ_DATA, i2c->regs + HSI2C_MANUAL_CMD);
	exynos5_i2c_रुको_bus_idle(i2c);
	ग_लिखोl(HSI2C_CMD_SEND_STOP, i2c->regs + HSI2C_MANUAL_CMD);
	exynos5_i2c_रुको_bus_idle(i2c);

	val = पढ़ोl(i2c->regs + HSI2C_CTL) & ~HSI2C_RXCHON;
	ग_लिखोl(val, i2c->regs + HSI2C_CTL);
	val = पढ़ोl(i2c->regs + HSI2C_CONF) | HSI2C_AUTO_MODE;
	ग_लिखोl(val, i2c->regs + HSI2C_CONF);
पूर्ण

अटल व्योम exynos5_i2c_bus_check(काष्ठा exynos5_i2c *i2c)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (i2c->variant->hw != I2C_TYPE_EXYNOS7)
		वापस;

	/*
	 * HSI2C_MASTER_ST_LOSE state in EXYNOS7 variant beक्रमe transaction
	 * indicates that bus is stuck (SDA is low). In such हाल bus recovery
	 * can be perक्रमmed.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(100);
	क्रम (;;) अणु
		u32 st = पढ़ोl(i2c->regs + HSI2C_TRANS_STATUS);

		अगर ((st & HSI2C_MASTER_ST_MASK) != HSI2C_MASTER_ST_LOSE)
			वापस;

		अगर (समय_is_beक्रमe_jअगरfies(समयout))
			वापस;

		exynos5_i2c_bus_recover(i2c);
	पूर्ण
पूर्ण

/*
 * exynos5_i2c_message_start: Configures the bus and starts the xfer
 * i2c: काष्ठा exynos5_i2c poपूर्णांकer क्रम the current bus
 * stop: Enables stop after transfer अगर set. Set क्रम last transfer of
 *       in the list of messages.
 *
 * Configures the bus क्रम पढ़ो/ग_लिखो function
 * Sets chip address to talk to, message length to be sent.
 * Enables appropriate पूर्णांकerrupts and sends start xfer command.
 */
अटल व्योम exynos5_i2c_message_start(काष्ठा exynos5_i2c *i2c, पूर्णांक stop)
अणु
	u32 i2c_ctl;
	u32 पूर्णांक_en = 0;
	u32 i2c_स्वतः_conf = 0;
	u32 i2c_addr = 0;
	u32 fअगरo_ctl;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु trig_lvl;

	अगर (i2c->variant->hw == I2C_TYPE_EXYNOS7)
		पूर्णांक_en |= HSI2C_INT_I2C_TRANS;
	अन्यथा
		पूर्णांक_en |= HSI2C_INT_I2C;

	i2c_ctl = पढ़ोl(i2c->regs + HSI2C_CTL);
	i2c_ctl &= ~(HSI2C_TXCHON | HSI2C_RXCHON);
	fअगरo_ctl = HSI2C_RXFIFO_EN | HSI2C_TXFIFO_EN;

	अगर (i2c->msg->flags & I2C_M_RD) अणु
		i2c_ctl |= HSI2C_RXCHON;

		i2c_स्वतः_conf |= HSI2C_READ_WRITE;

		trig_lvl = (i2c->msg->len > i2c->variant->fअगरo_depth) ?
			(i2c->variant->fअगरo_depth * 3 / 4) : i2c->msg->len;
		fअगरo_ctl |= HSI2C_RXFIFO_TRIGGER_LEVEL(trig_lvl);

		पूर्णांक_en |= (HSI2C_INT_RX_ALMOSTFULL_EN |
			HSI2C_INT_TRAILING_EN);
	पूर्ण अन्यथा अणु
		i2c_ctl |= HSI2C_TXCHON;

		trig_lvl = (i2c->msg->len > i2c->variant->fअगरo_depth) ?
			(i2c->variant->fअगरo_depth * 1 / 4) : i2c->msg->len;
		fअगरo_ctl |= HSI2C_TXFIFO_TRIGGER_LEVEL(trig_lvl);

		पूर्णांक_en |= HSI2C_INT_TX_ALMOSTEMPTY_EN;
	पूर्ण

	i2c_addr = HSI2C_SLV_ADDR_MAS(i2c->msg->addr);

	अगर (i2c->op_घड़ी >= I2C_MAX_FAST_MODE_PLUS_FREQ)
		i2c_addr |= HSI2C_MASTER_ID(MASTER_ID(i2c->adap.nr));

	ग_लिखोl(i2c_addr, i2c->regs + HSI2C_ADDR);

	ग_लिखोl(fअगरo_ctl, i2c->regs + HSI2C_FIFO_CTL);
	ग_लिखोl(i2c_ctl, i2c->regs + HSI2C_CTL);

	exynos5_i2c_bus_check(i2c);

	/*
	 * Enable पूर्णांकerrupts beक्रमe starting the transfer so that we करोn't
	 * miss any INT_I2C पूर्णांकerrupts.
	 */
	spin_lock_irqsave(&i2c->lock, flags);
	ग_लिखोl(पूर्णांक_en, i2c->regs + HSI2C_INT_ENABLE);

	अगर (stop == 1)
		i2c_स्वतः_conf |= HSI2C_STOP_AFTER_TRANS;
	i2c_स्वतः_conf |= i2c->msg->len;
	i2c_स्वतः_conf |= HSI2C_MASTER_RUN;
	ग_लिखोl(i2c_स्वतः_conf, i2c->regs + HSI2C_AUTO_CONF);
	spin_unlock_irqrestore(&i2c->lock, flags);
पूर्ण

अटल पूर्णांक exynos5_i2c_xfer_msg(काष्ठा exynos5_i2c *i2c,
			      काष्ठा i2c_msg *msgs, पूर्णांक stop)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	i2c->msg = msgs;
	i2c->msg_ptr = 0;
	i2c->trans_करोne = 0;

	reinit_completion(&i2c->msg_complete);

	exynos5_i2c_message_start(i2c, stop);

	समयout = रुको_क्रम_completion_समयout(&i2c->msg_complete,
					      EXYNOS5_I2C_TIMEOUT);
	अगर (समयout == 0)
		ret = -ETIMEDOUT;
	अन्यथा
		ret = i2c->state;

	/*
	 * If this is the last message to be transfered (stop == 1)
	 * Then check अगर the bus can be brought back to idle.
	 */
	अगर (ret == 0 && stop)
		ret = exynos5_i2c_रुको_bus_idle(i2c);

	अगर (ret < 0) अणु
		exynos5_i2c_reset(i2c);
		अगर (ret == -ETIMEDOUT)
			dev_warn(i2c->dev, "%s timeout\n",
				 (msgs->flags & I2C_M_RD) ? "rx" : "tx");
	पूर्ण

	/* Return the state as in पूर्णांकerrupt routine */
	वापस ret;
पूर्ण

अटल पूर्णांक exynos5_i2c_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा exynos5_i2c *i2c = adap->algo_data;
	पूर्णांक i, ret;

	ret = clk_enable(i2c->clk);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num; ++i) अणु
		ret = exynos5_i2c_xfer_msg(i2c, msgs + i, i + 1 == num);
		अगर (ret)
			अवरोध;
	पूर्ण

	clk_disable(i2c->clk);

	वापस ret ?: num;
पूर्ण

अटल u32 exynos5_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm exynos5_i2c_algorithm = अणु
	.master_xfer		= exynos5_i2c_xfer,
	.functionality		= exynos5_i2c_func,
पूर्ण;

अटल पूर्णांक exynos5_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा exynos5_i2c *i2c;
	पूर्णांक ret;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा exynos5_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &i2c->op_घड़ी))
		i2c->op_घड़ी = I2C_MAX_STANDARD_MODE_FREQ;

	strlcpy(i2c->adap.name, "exynos5-i2c", माप(i2c->adap.name));
	i2c->adap.owner   = THIS_MODULE;
	i2c->adap.algo    = &exynos5_i2c_algorithm;
	i2c->adap.retries = 3;

	i2c->dev = &pdev->dev;
	i2c->clk = devm_clk_get(&pdev->dev, "hsi2c");
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस -ENOENT;
	पूर्ण

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret)
		वापस ret;

	i2c->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->regs)) अणु
		ret = PTR_ERR(i2c->regs);
		जाओ err_clk;
	पूर्ण

	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	/* Clear pending पूर्णांकerrupts from u-boot or misc causes */
	exynos5_i2c_clr_pend_irq(i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->msg_complete);

	i2c->irq = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_clk;

	ret = devm_request_irq(&pdev->dev, i2c->irq, exynos5_i2c_irq,
			       IRQF_NO_SUSPEND, dev_name(&pdev->dev), i2c);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "cannot request HS-I2C IRQ %d\n", i2c->irq);
		जाओ err_clk;
	पूर्ण

	i2c->variant = of_device_get_match_data(&pdev->dev);

	ret = exynos5_hsi2c_घड़ी_setup(i2c);
	अगर (ret)
		जाओ err_clk;

	exynos5_i2c_reset(i2c);

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ err_clk;

	platक्रमm_set_drvdata(pdev, i2c);

	clk_disable(i2c->clk);

	वापस 0;

 err_clk:
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक exynos5_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos5_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);

	clk_unprepare(i2c->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक exynos5_i2c_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा exynos5_i2c *i2c = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&i2c->adap);
	clk_unprepare(i2c->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_i2c_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा exynos5_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret)
		वापस ret;

	ret = exynos5_hsi2c_घड़ी_setup(i2c);
	अगर (ret) अणु
		clk_disable_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	exynos5_i2c_init(i2c);
	clk_disable(i2c->clk);
	i2c_mark_adapter_resumed(&i2c->adap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos5_i2c_dev_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(exynos5_i2c_suspend_noirq,
				      exynos5_i2c_resume_noirq)
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos5_i2c_driver = अणु
	.probe		= exynos5_i2c_probe,
	.हटाओ		= exynos5_i2c_हटाओ,
	.driver		= अणु
		.name	= "exynos5-hsi2c",
		.pm	= &exynos5_i2c_dev_pm_ops,
		.of_match_table = exynos5_i2c_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(exynos5_i2c_driver);

MODULE_DESCRIPTION("Exynos5 HS-I2C Bus driver");
MODULE_AUTHOR("Naveen Krishna Chatradhi <ch.naveen@samsung.com>");
MODULE_AUTHOR("Taekgyun Ko <taeggyun.ko@samsung.com>");
MODULE_LICENSE("GPL v2");
