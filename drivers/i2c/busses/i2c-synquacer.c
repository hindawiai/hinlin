<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 FUJITSU SEMICONDUCTOR LIMITED
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा WAIT_PCLK(n, rate)	\
	ndelay(DIV_ROUND_UP(DIV_ROUND_UP(1000000000, rate), n) + 10)

/* I2C रेजिस्टर address definitions */
#घोषणा SYNQUACER_I2C_REG_BSR		(0x00 << 2) // Bus Status
#घोषणा SYNQUACER_I2C_REG_BCR		(0x01 << 2) // Bus Control
#घोषणा SYNQUACER_I2C_REG_CCR		(0x02 << 2) // Clock Control
#घोषणा SYNQUACER_I2C_REG_ADR		(0x03 << 2) // Address
#घोषणा SYNQUACER_I2C_REG_DAR		(0x04 << 2) // Data
#घोषणा SYNQUACER_I2C_REG_CSR		(0x05 << 2) // Expansion CS
#घोषणा SYNQUACER_I2C_REG_FSR		(0x06 << 2) // Bus Clock Freq
#घोषणा SYNQUACER_I2C_REG_BC2R		(0x07 << 2) // Bus Control 2

/* I2C रेजिस्टर bit definitions */
#घोषणा SYNQUACER_I2C_BSR_FBT		BIT(0)	// First Byte Transfer
#घोषणा SYNQUACER_I2C_BSR_GCA		BIT(1)	// General Call Address
#घोषणा SYNQUACER_I2C_BSR_AAS		BIT(2)	// Address as Slave
#घोषणा SYNQUACER_I2C_BSR_TRX		BIT(3)	// Transfer/Receive
#घोषणा SYNQUACER_I2C_BSR_LRB		BIT(4)	// Last Received Bit
#घोषणा SYNQUACER_I2C_BSR_AL		BIT(5)	// Arbitration Lost
#घोषणा SYNQUACER_I2C_BSR_RSC		BIT(6)	// Repeated Start Cond.
#घोषणा SYNQUACER_I2C_BSR_BB		BIT(7)	// Bus Busy

#घोषणा SYNQUACER_I2C_BCR_INT		BIT(0)	// Interrupt
#घोषणा SYNQUACER_I2C_BCR_INTE		BIT(1)	// Interrupt Enable
#घोषणा SYNQUACER_I2C_BCR_GCAA		BIT(2)	// Gen. Call Access Ack.
#घोषणा SYNQUACER_I2C_BCR_ACK		BIT(3)	// Acknowledge
#घोषणा SYNQUACER_I2C_BCR_MSS		BIT(4)	// Master Slave Select
#घोषणा SYNQUACER_I2C_BCR_SCC		BIT(5)	// Start Condition Cont.
#घोषणा SYNQUACER_I2C_BCR_BEIE		BIT(6)	// Bus Error Int Enable
#घोषणा SYNQUACER_I2C_BCR_BER		BIT(7)	// Bus Error

#घोषणा SYNQUACER_I2C_CCR_CS_MASK	(0x1f)	// CCR Clock Period Sel.
#घोषणा SYNQUACER_I2C_CCR_EN		BIT(5)	// Enable
#घोषणा SYNQUACER_I2C_CCR_FM		BIT(6)	// Speed Mode Select

#घोषणा SYNQUACER_I2C_CSR_CS_MASK	(0x3f)	// CSR Clock Period Sel.

#घोषणा SYNQUACER_I2C_BC2R_SCLL		BIT(0)	// SCL Low Drive
#घोषणा SYNQUACER_I2C_BC2R_SDAL		BIT(1)	// SDA Low Drive
#घोषणा SYNQUACER_I2C_BC2R_SCLS		BIT(4)	// SCL Status
#घोषणा SYNQUACER_I2C_BC2R_SDAS		BIT(5)	// SDA Status

/* PCLK frequency */
#घोषणा SYNQUACER_I2C_BUS_CLK_FR(rate)	(((rate) / 20000000) + 1)

/* STANDARD MODE frequency */
#घोषणा SYNQUACER_I2C_CLK_MASTER_STD(rate)			\
	DIV_ROUND_UP(DIV_ROUND_UP((rate), I2C_MAX_STANDARD_MODE_FREQ) - 2, 2)
/* FAST MODE frequency */
#घोषणा SYNQUACER_I2C_CLK_MASTER_FAST(rate)			\
	DIV_ROUND_UP((DIV_ROUND_UP((rate), I2C_MAX_FAST_MODE_FREQ) - 2) * 2, 3)

/* (clkrate <= 18000000) */
/* calculate the value of CS bits in CCR रेजिस्टर on standard mode */
#घोषणा SYNQUACER_I2C_CCR_CS_STD_MAX_18M(rate)			\
	   ((SYNQUACER_I2C_CLK_MASTER_STD(rate) - 65)		\
					& SYNQUACER_I2C_CCR_CS_MASK)

/* calculate the value of CS bits in CSR रेजिस्टर on standard mode */
#घोषणा SYNQUACER_I2C_CSR_CS_STD_MAX_18M(rate)		0x00

/* calculate the value of CS bits in CCR रेजिस्टर on fast mode */
#घोषणा SYNQUACER_I2C_CCR_CS_FAST_MAX_18M(rate)			\
	   ((SYNQUACER_I2C_CLK_MASTER_FAST(rate) - 1)		\
					& SYNQUACER_I2C_CCR_CS_MASK)

/* calculate the value of CS bits in CSR रेजिस्टर on fast mode */
#घोषणा SYNQUACER_I2C_CSR_CS_FAST_MAX_18M(rate)		0x00

/* (clkrate > 18000000) */
/* calculate the value of CS bits in CCR रेजिस्टर on standard mode */
#घोषणा SYNQUACER_I2C_CCR_CS_STD_MIN_18M(rate)			\
	   ((SYNQUACER_I2C_CLK_MASTER_STD(rate) - 1)		\
					& SYNQUACER_I2C_CCR_CS_MASK)

/* calculate the value of CS bits in CSR रेजिस्टर on standard mode */
#घोषणा SYNQUACER_I2C_CSR_CS_STD_MIN_18M(rate)			\
	   (((SYNQUACER_I2C_CLK_MASTER_STD(rate) - 1) >> 5)	\
					& SYNQUACER_I2C_CSR_CS_MASK)

/* calculate the value of CS bits in CCR रेजिस्टर on fast mode */
#घोषणा SYNQUACER_I2C_CCR_CS_FAST_MIN_18M(rate)			\
	   ((SYNQUACER_I2C_CLK_MASTER_FAST(rate) - 1)		\
					& SYNQUACER_I2C_CCR_CS_MASK)

/* calculate the value of CS bits in CSR रेजिस्टर on fast mode */
#घोषणा SYNQUACER_I2C_CSR_CS_FAST_MIN_18M(rate)			\
	   (((SYNQUACER_I2C_CLK_MASTER_FAST(rate) - 1) >> 5)	\
					& SYNQUACER_I2C_CSR_CS_MASK)

/* min I2C घड़ी frequency 14M */
#घोषणा SYNQUACER_I2C_MIN_CLK_RATE	(14 * 1000000)
/* max I2C घड़ी frequency 200M */
#घोषणा SYNQUACER_I2C_MAX_CLK_RATE	(200 * 1000000)
/* I2C घड़ी frequency 18M */
#घोषणा SYNQUACER_I2C_CLK_RATE_18M	(18 * 1000000)

#घोषणा SYNQUACER_I2C_SPEED_FM		400	// Fast Mode
#घोषणा SYNQUACER_I2C_SPEED_SM		100	// Standard Mode

क्रमागत i2c_state अणु
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE
पूर्ण;

काष्ठा synquacer_i2c अणु
	काष्ठा completion	completion;

	काष्ठा i2c_msg		*msg;
	u32			msg_num;
	u32			msg_idx;
	u32			msg_ptr;

	पूर्णांक			irq;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा clk		*pclk;
	u32			pclkrate;
	u32			speed_khz;
	u32			समयout_ms;
	क्रमागत i2c_state		state;
	काष्ठा i2c_adapter	adapter;
पूर्ण;

अटल अंतरभूत पूर्णांक is_lasपंचांगsg(काष्ठा synquacer_i2c *i2c)
अणु
	वापस i2c->msg_idx >= (i2c->msg_num - 1);
पूर्ण

अटल अंतरभूत पूर्णांक is_msglast(काष्ठा synquacer_i2c *i2c)
अणु
	वापस i2c->msg_ptr == (i2c->msg->len - 1);
पूर्ण

अटल अंतरभूत पूर्णांक is_msgend(काष्ठा synquacer_i2c *i2c)
अणु
	वापस i2c->msg_ptr >= i2c->msg->len;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ calc_समयout_ms(काष्ठा synquacer_i2c *i2c,
					    काष्ठा i2c_msg *msgs,
					    पूर्णांक num)
अणु
	अचिन्हित दीर्घ bit_count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, msgs++)
		bit_count += msgs->len;

	वापस DIV_ROUND_UP((bit_count * 9 + num * 10) * 3, 200) + 10;
पूर्ण

अटल व्योम synquacer_i2c_stop(काष्ठा synquacer_i2c *i2c, पूर्णांक ret)
अणु
	/*
	 * clear IRQ (INT=0, BER=0)
	 * set Stop Condition (MSS=0)
	 * Interrupt Disable
	 */
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_BCR);

	i2c->state = STATE_IDLE;

	i2c->msg_ptr = 0;
	i2c->msg = शून्य;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	अगर (ret)
		i2c->msg_idx = ret;

	complete(&i2c->completion);
पूर्ण

अटल व्योम synquacer_i2c_hw_init(काष्ठा synquacer_i2c *i2c)
अणु
	अचिन्हित अक्षर ccr_cs, csr_cs;
	u32 rt = i2c->pclkrate;

	/* Set own Address */
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_ADR);

	/* Set PCLK frequency */
	ग_लिखोb(SYNQUACER_I2C_BUS_CLK_FR(i2c->pclkrate),
	       i2c->base + SYNQUACER_I2C_REG_FSR);

	चयन (i2c->speed_khz) अणु
	हाल SYNQUACER_I2C_SPEED_FM:
		अगर (i2c->pclkrate <= SYNQUACER_I2C_CLK_RATE_18M) अणु
			ccr_cs = SYNQUACER_I2C_CCR_CS_FAST_MAX_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_FAST_MAX_18M(rt);
		पूर्ण अन्यथा अणु
			ccr_cs = SYNQUACER_I2C_CCR_CS_FAST_MIN_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_FAST_MIN_18M(rt);
		पूर्ण

		/* Set Clock and enable, Set fast mode */
		ग_लिखोb(ccr_cs | SYNQUACER_I2C_CCR_FM |
		       SYNQUACER_I2C_CCR_EN,
		       i2c->base + SYNQUACER_I2C_REG_CCR);
		ग_लिखोb(csr_cs, i2c->base + SYNQUACER_I2C_REG_CSR);
		अवरोध;
	हाल SYNQUACER_I2C_SPEED_SM:
		अगर (i2c->pclkrate <= SYNQUACER_I2C_CLK_RATE_18M) अणु
			ccr_cs = SYNQUACER_I2C_CCR_CS_STD_MAX_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_STD_MAX_18M(rt);
		पूर्ण अन्यथा अणु
			ccr_cs = SYNQUACER_I2C_CCR_CS_STD_MIN_18M(rt);
			csr_cs = SYNQUACER_I2C_CSR_CS_STD_MIN_18M(rt);
		पूर्ण

		/* Set Clock and enable, Set standard mode */
		ग_लिखोb(ccr_cs | SYNQUACER_I2C_CCR_EN,
		      i2c->base + SYNQUACER_I2C_REG_CCR);
		ग_लिखोb(csr_cs, i2c->base + SYNQUACER_I2C_REG_CSR);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	/* clear IRQ (INT=0, BER=0), Interrupt Disable */
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_BCR);
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_BC2R);
पूर्ण

अटल व्योम synquacer_i2c_hw_reset(काष्ठा synquacer_i2c *i2c)
अणु
	/* Disable घड़ी */
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_CCR);
	ग_लिखोb(0, i2c->base + SYNQUACER_I2C_REG_CSR);

	WAIT_PCLK(100, i2c->pclkrate);
पूर्ण

अटल पूर्णांक synquacer_i2c_master_start(काष्ठा synquacer_i2c *i2c,
				      काष्ठा i2c_msg *pmsg)
अणु
	अचिन्हित अक्षर bsr, bcr;

	ग_लिखोb(i2c_8bit_addr_from_msg(pmsg), i2c->base + SYNQUACER_I2C_REG_DAR);

	dev_dbg(i2c->dev, "slave:0x%02x\n", pmsg->addr);

	/* Generate Start Condition */
	bsr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BSR);
	bcr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BCR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	अगर ((bsr & SYNQUACER_I2C_BSR_BB) &&
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) अणु
		dev_dbg(i2c->dev, "bus is busy");
		वापस -EBUSY;
	पूर्ण

	अगर (bsr & SYNQUACER_I2C_BSR_BB) अणु /* Bus is busy */
		dev_dbg(i2c->dev, "Continuous Start");
		ग_लिखोb(bcr | SYNQUACER_I2C_BCR_SCC,
		       i2c->base + SYNQUACER_I2C_REG_BCR);
	पूर्ण अन्यथा अणु
		अगर (bcr & SYNQUACER_I2C_BCR_MSS) अणु
			dev_dbg(i2c->dev, "not in master mode");
			वापस -EAGAIN;
		पूर्ण
		dev_dbg(i2c->dev, "Start Condition");
		/* Start Condition + Enable Interrupts */
		ग_लिखोb(bcr | SYNQUACER_I2C_BCR_MSS |
		       SYNQUACER_I2C_BCR_INTE | SYNQUACER_I2C_BCR_BEIE,
		       i2c->base + SYNQUACER_I2C_REG_BCR);
	पूर्ण

	WAIT_PCLK(10, i2c->pclkrate);

	/* get BSR & BCR रेजिस्टरs */
	bsr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BSR);
	bcr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BCR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	अगर ((bsr & SYNQUACER_I2C_BSR_AL) ||
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) अणु
		dev_dbg(i2c->dev, "arbitration lost\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक synquacer_i2c_करोxfer(काष्ठा synquacer_i2c *i2c,
				काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	अचिन्हित अक्षर bsr;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	synquacer_i2c_hw_init(i2c);
	bsr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BSR);
	अगर (bsr & SYNQUACER_I2C_BSR_BB) अणु
		dev_err(i2c->dev, "cannot get bus (bus busy)\n");
		वापस -EBUSY;
	पूर्ण

	reinit_completion(&i2c->completion);

	i2c->msg = msgs;
	i2c->msg_num = num;
	i2c->msg_ptr = 0;
	i2c->msg_idx = 0;
	i2c->state = STATE_START;

	ret = synquacer_i2c_master_start(i2c, i2c->msg);
	अगर (ret < 0) अणु
		dev_dbg(i2c->dev, "Address failed: (%d)\n", ret);
		वापस ret;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&i2c->completion,
					msecs_to_jअगरfies(i2c->समयout_ms));
	अगर (समयout == 0) अणु
		dev_dbg(i2c->dev, "timeout\n");
		वापस -EAGAIN;
	पूर्ण

	ret = i2c->msg_idx;
	अगर (ret != num) अणु
		dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);
		वापस -EAGAIN;
	पूर्ण

	/* रुको 2 घड़ी periods to ensure the stop has been through the bus */
	udelay(DIV_ROUND_UP(2 * 1000, i2c->speed_khz));

	वापस ret;
पूर्ण

अटल irqवापस_t synquacer_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा synquacer_i2c *i2c = dev_id;

	अचिन्हित अक्षर byte;
	अचिन्हित अक्षर bsr, bcr;
	पूर्णांक ret;

	bcr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BCR);
	bsr = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_BSR);
	dev_dbg(i2c->dev, "bsr:0x%02x, bcr:0x%02x\n", bsr, bcr);

	अगर (bcr & SYNQUACER_I2C_BCR_BER) अणु
		dev_err(i2c->dev, "bus error\n");
		synquacer_i2c_stop(i2c, -EAGAIN);
		जाओ out;
	पूर्ण
	अगर ((bsr & SYNQUACER_I2C_BSR_AL) ||
	    !(bcr & SYNQUACER_I2C_BCR_MSS)) अणु
		dev_dbg(i2c->dev, "arbitration lost\n");
		synquacer_i2c_stop(i2c, -EAGAIN);
		जाओ out;
	पूर्ण

	चयन (i2c->state) अणु
	हाल STATE_START:
		अगर (bsr & SYNQUACER_I2C_BSR_LRB) अणु
			dev_dbg(i2c->dev, "ack was not received\n");
			synquacer_i2c_stop(i2c, -EAGAIN);
			जाओ out;
		पूर्ण

		अगर (i2c->msg->flags & I2C_M_RD)
			i2c->state = STATE_READ;
		अन्यथा
			i2c->state = STATE_WRITE;

		अगर (is_lasपंचांगsg(i2c) && i2c->msg->len == 0) अणु
			synquacer_i2c_stop(i2c, 0);
			जाओ out;
		पूर्ण

		अगर (i2c->state == STATE_READ)
			जाओ prepare_पढ़ो;
		fallthrough;

	हाल STATE_WRITE:
		अगर (bsr & SYNQUACER_I2C_BSR_LRB) अणु
			dev_dbg(i2c->dev, "WRITE: No Ack\n");
			synquacer_i2c_stop(i2c, -EAGAIN);
			जाओ out;
		पूर्ण

		अगर (!is_msgend(i2c)) अणु
			ग_लिखोb(i2c->msg->buf[i2c->msg_ptr++],
			       i2c->base + SYNQUACER_I2C_REG_DAR);

			/* clear IRQ, and जारी */
			ग_लिखोb(SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_INTE,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			अवरोध;
		पूर्ण
		अगर (is_lasपंचांगsg(i2c)) अणु
			synquacer_i2c_stop(i2c, 0);
			अवरोध;
		पूर्ण
		dev_dbg(i2c->dev, "WRITE: Next Message\n");

		i2c->msg_ptr = 0;
		i2c->msg_idx++;
		i2c->msg++;

		/* send the new start */
		ret = synquacer_i2c_master_start(i2c, i2c->msg);
		अगर (ret < 0) अणु
			dev_dbg(i2c->dev, "restart error (%d)\n", ret);
			synquacer_i2c_stop(i2c, -EAGAIN);
			अवरोध;
		पूर्ण
		i2c->state = STATE_START;
		अवरोध;

	हाल STATE_READ:
		byte = पढ़ोb(i2c->base + SYNQUACER_I2C_REG_DAR);
		अगर (!(bsr & SYNQUACER_I2C_BSR_FBT)) /* data */
			i2c->msg->buf[i2c->msg_ptr++] = byte;
		अन्यथा /* address */
			dev_dbg(i2c->dev, "address:0x%02x. ignore it.\n", byte);

prepare_पढ़ो:
		अगर (is_msglast(i2c)) अणु
			ग_लिखोb(SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_INTE,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			अवरोध;
		पूर्ण
		अगर (!is_msgend(i2c)) अणु
			ग_लिखोb(SYNQUACER_I2C_BCR_MSS |
			       SYNQUACER_I2C_BCR_BEIE |
			       SYNQUACER_I2C_BCR_INTE |
			       SYNQUACER_I2C_BCR_ACK,
			       i2c->base + SYNQUACER_I2C_REG_BCR);
			अवरोध;
		पूर्ण
		अगर (is_lasपंचांगsg(i2c)) अणु
			/* last message, send stop and complete */
			dev_dbg(i2c->dev, "READ: Send Stop\n");
			synquacer_i2c_stop(i2c, 0);
			अवरोध;
		पूर्ण
		dev_dbg(i2c->dev, "READ: Next Transfer\n");

		i2c->msg_ptr = 0;
		i2c->msg_idx++;
		i2c->msg++;

		ret = synquacer_i2c_master_start(i2c, i2c->msg);
		अगर (ret < 0) अणु
			dev_dbg(i2c->dev, "restart error (%d)\n", ret);
			synquacer_i2c_stop(i2c, -EAGAIN);
		पूर्ण अन्यथा अणु
			i2c->state = STATE_START;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(i2c->dev, "called in err STATE (%d)\n", i2c->state);
		अवरोध;
	पूर्ण

out:
	WAIT_PCLK(10, i2c->pclkrate);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक synquacer_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			      पूर्णांक num)
अणु
	काष्ठा synquacer_i2c *i2c;
	पूर्णांक retry;
	पूर्णांक ret;

	i2c = i2c_get_adapdata(adap);
	i2c->समयout_ms = calc_समयout_ms(i2c, msgs, num);

	dev_dbg(i2c->dev, "calculated timeout %d ms\n", i2c->समयout_ms);

	क्रम (retry = 0; retry <= adap->retries; retry++) अणु
		ret = synquacer_i2c_करोxfer(i2c, msgs, num);
		अगर (ret != -EAGAIN)
			वापस ret;

		dev_dbg(i2c->dev, "Retrying transmission (%d)\n", retry);

		synquacer_i2c_hw_reset(i2c);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल u32 synquacer_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm synquacer_i2c_algo = अणु
	.master_xfer	= synquacer_i2c_xfer,
	.functionality	= synquacer_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter synquacer_i2c_ops = अणु
	.owner		= THIS_MODULE,
	.name		= "synquacer_i2c-adapter",
	.algo		= &synquacer_i2c_algo,
	.retries	= 5,
पूर्ण;

अटल पूर्णांक synquacer_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा synquacer_i2c *i2c;
	u32 bus_speed;
	पूर्णांक ret;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	bus_speed = i2c_acpi_find_bus_speed(&pdev->dev);
	अगर (!bus_speed)
		device_property_पढ़ो_u32(&pdev->dev, "clock-frequency",
					 &bus_speed);

	device_property_पढ़ो_u32(&pdev->dev, "socionext,pclk-rate",
				 &i2c->pclkrate);

	i2c->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (PTR_ERR(i2c->pclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (!IS_ERR_OR_शून्य(i2c->pclk)) अणु
		dev_dbg(&pdev->dev, "clock source %p\n", i2c->pclk);

		ret = clk_prepare_enable(i2c->pclk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to enable clock (%d)\n",
				ret);
			वापस ret;
		पूर्ण
		i2c->pclkrate = clk_get_rate(i2c->pclk);
	पूर्ण

	अगर (i2c->pclkrate < SYNQUACER_I2C_MIN_CLK_RATE ||
	    i2c->pclkrate > SYNQUACER_I2C_MAX_CLK_RATE) अणु
		dev_err(&pdev->dev, "PCLK missing or out of range (%d)\n",
			i2c->pclkrate);
		वापस -EINVAL;
	पूर्ण

	i2c->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	i2c->irq = platक्रमm_get_irq(pdev, 0);
	अगर (i2c->irq < 0)
		वापस -ENODEV;

	ret = devm_request_irq(&pdev->dev, i2c->irq, synquacer_i2c_isr,
			       0, dev_name(&pdev->dev), i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", i2c->irq);
		वापस ret;
	पूर्ण

	i2c->state = STATE_IDLE;
	i2c->dev = &pdev->dev;
	i2c->adapter = synquacer_i2c_ops;
	i2c_set_adapdata(&i2c->adapter, i2c);
	i2c->adapter.dev.parent = &pdev->dev;
	i2c->adapter.dev.of_node = pdev->dev.of_node;
	ACPI_COMPANION_SET(&i2c->adapter.dev, ACPI_COMPANION(&pdev->dev));
	i2c->adapter.nr = pdev->id;
	init_completion(&i2c->completion);

	अगर (bus_speed < I2C_MAX_FAST_MODE_FREQ)
		i2c->speed_khz = SYNQUACER_I2C_SPEED_SM;
	अन्यथा
		i2c->speed_khz = SYNQUACER_I2C_SPEED_FM;

	synquacer_i2c_hw_init(i2c);

	ret = i2c_add_numbered_adapter(&i2c->adapter);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add bus to i2c core\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, i2c);

	dev_info(&pdev->dev, "%s: synquacer_i2c adapter\n",
		 dev_name(&i2c->adapter.dev));

	वापस 0;
पूर्ण

अटल पूर्णांक synquacer_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा synquacer_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adapter);
	अगर (!IS_ERR(i2c->pclk))
		clk_disable_unprepare(i2c->pclk);

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id synquacer_i2c_dt_ids[] = अणु
	अणु .compatible = "socionext,synquacer-i2c" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, synquacer_i2c_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id synquacer_i2c_acpi_ids[] = अणु
	अणु "SCX0003" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, synquacer_i2c_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver synquacer_i2c_driver = अणु
	.probe	= synquacer_i2c_probe,
	.हटाओ	= synquacer_i2c_हटाओ,
	.driver	= अणु
		.name = "synquacer_i2c",
		.of_match_table = of_match_ptr(synquacer_i2c_dt_ids),
		.acpi_match_table = ACPI_PTR(synquacer_i2c_acpi_ids),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(synquacer_i2c_driver);

MODULE_AUTHOR("Fujitsu Semiconductor Ltd");
MODULE_DESCRIPTION("Socionext SynQuacer I2C Driver");
MODULE_LICENSE("GPL v2");
