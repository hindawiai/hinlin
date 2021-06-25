<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* linux/drivers/i2c/busses/i2c-s3c2410.c
 *
 * Copyright (C) 2004,2005,2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 I2C Controller
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/irq.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

/* see s3c2410x user guide, v1.1, section 9 (p447) क्रम more info */

#घोषणा S3C2410_IICCON			0x00
#घोषणा S3C2410_IICSTAT			0x04
#घोषणा S3C2410_IICADD			0x08
#घोषणा S3C2410_IICDS			0x0C
#घोषणा S3C2440_IICLC			0x10

#घोषणा S3C2410_IICCON_ACKEN		(1 << 7)
#घोषणा S3C2410_IICCON_TXDIV_16		(0 << 6)
#घोषणा S3C2410_IICCON_TXDIV_512	(1 << 6)
#घोषणा S3C2410_IICCON_IRQEN		(1 << 5)
#घोषणा S3C2410_IICCON_IRQPEND		(1 << 4)
#घोषणा S3C2410_IICCON_SCALE(x)		((x) & 0xf)
#घोषणा S3C2410_IICCON_SCALEMASK	(0xf)

#घोषणा S3C2410_IICSTAT_MASTER_RX	(2 << 6)
#घोषणा S3C2410_IICSTAT_MASTER_TX	(3 << 6)
#घोषणा S3C2410_IICSTAT_SLAVE_RX	(0 << 6)
#घोषणा S3C2410_IICSTAT_SLAVE_TX	(1 << 6)
#घोषणा S3C2410_IICSTAT_MODEMASK	(3 << 6)

#घोषणा S3C2410_IICSTAT_START		(1 << 5)
#घोषणा S3C2410_IICSTAT_BUSBUSY		(1 << 5)
#घोषणा S3C2410_IICSTAT_TXRXEN		(1 << 4)
#घोषणा S3C2410_IICSTAT_ARBITR		(1 << 3)
#घोषणा S3C2410_IICSTAT_ASSLAVE		(1 << 2)
#घोषणा S3C2410_IICSTAT_ADDR0		(1 << 1)
#घोषणा S3C2410_IICSTAT_LASTBIT		(1 << 0)

#घोषणा S3C2410_IICLC_SDA_DELAY0	(0 << 0)
#घोषणा S3C2410_IICLC_SDA_DELAY5	(1 << 0)
#घोषणा S3C2410_IICLC_SDA_DELAY10	(2 << 0)
#घोषणा S3C2410_IICLC_SDA_DELAY15	(3 << 0)
#घोषणा S3C2410_IICLC_SDA_DELAY_MASK	(3 << 0)

#घोषणा S3C2410_IICLC_FILTER_ON		(1 << 2)

/* Treat S3C2410 as baseline hardware, anything अन्यथा is supported via quirks */
#घोषणा QUIRK_S3C2440		(1 << 0)
#घोषणा QUIRK_HDMIPHY		(1 << 1)
#घोषणा QUIRK_NO_GPIO		(1 << 2)
#घोषणा QUIRK_POLL		(1 << 3)

/* Max समय to रुको क्रम bus to become idle after a xfer (in us) */
#घोषणा S3C2410_IDLE_TIMEOUT	5000

/* Exynos5 Sysreg offset */
#घोषणा EXYNOS5_SYS_I2C_CFG	0x0234

/* i2c controller state */
क्रमागत s3c24xx_i2c_state अणु
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE,
	STATE_STOP
पूर्ण;

काष्ठा s3c24xx_i2c अणु
	रुको_queue_head_t	रुको;
	kernel_uदीर्घ_t		quirks;

	काष्ठा i2c_msg		*msg;
	अचिन्हित पूर्णांक		msg_num;
	अचिन्हित पूर्णांक		msg_idx;
	अचिन्हित पूर्णांक		msg_ptr;

	अचिन्हित पूर्णांक		tx_setup;
	अचिन्हित पूर्णांक		irq;

	क्रमागत s3c24xx_i2c_state	state;
	अचिन्हित दीर्घ		clkrate;

	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	काष्ठा device		*dev;
	काष्ठा i2c_adapter	adap;

	काष्ठा s3c2410_platक्रमm_i2c	*pdata;
	काष्ठा gpio_desc	*gpios[2];
	काष्ठा pinctrl          *pctrl;
#अगर defined(CONFIG_ARM_S3C24XX_CPUFREQ)
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
	काष्ठा regmap		*sysreg;
	अचिन्हित पूर्णांक		sys_i2c_cfg;
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id s3c24xx_driver_ids[] = अणु
	अणु
		.name		= "s3c2410-i2c",
		.driver_data	= 0,
	पूर्ण, अणु
		.name		= "s3c2440-i2c",
		.driver_data	= QUIRK_S3C2440,
	पूर्ण, अणु
		.name		= "s3c2440-hdmiphy-i2c",
		.driver_data	= QUIRK_S3C2440 | QUIRK_HDMIPHY | QUIRK_NO_GPIO,
	पूर्ण, अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s3c24xx_driver_ids);

अटल पूर्णांक i2c_s3c_irq_nextbyte(काष्ठा s3c24xx_i2c *i2c, अचिन्हित दीर्घ iicstat);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s3c24xx_i2c_match[] = अणु
	अणु .compatible = "samsung,s3c2410-i2c", .data = (व्योम *)0 पूर्ण,
	अणु .compatible = "samsung,s3c2440-i2c", .data = (व्योम *)QUIRK_S3C2440 पूर्ण,
	अणु .compatible = "samsung,s3c2440-hdmiphy-i2c",
	  .data = (व्योम *)(QUIRK_S3C2440 | QUIRK_HDMIPHY | QUIRK_NO_GPIO) पूर्ण,
	अणु .compatible = "samsung,exynos5-sata-phy-i2c",
	  .data = (व्योम *)(QUIRK_S3C2440 | QUIRK_POLL | QUIRK_NO_GPIO) पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c24xx_i2c_match);
#पूर्ण_अगर

/*
 * Get controller type either from device tree or platक्रमm device variant.
 */
अटल अंतरभूत kernel_uदीर्घ_t s3c24xx_get_device_quirks(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node)
		वापस (kernel_uदीर्घ_t)of_device_get_match_data(&pdev->dev);

	वापस platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

/*
 * Complete the message and wake up the caller, using the given वापस code,
 * or zero to mean ok.
 */
अटल अंतरभूत व्योम s3c24xx_i2c_master_complete(काष्ठा s3c24xx_i2c *i2c, पूर्णांक ret)
अणु
	dev_dbg(i2c->dev, "master_complete %d\n", ret);

	i2c->msg_ptr = 0;
	i2c->msg = शून्य;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	अगर (ret)
		i2c->msg_idx = ret;

	अगर (!(i2c->quirks & QUIRK_POLL))
		wake_up(&i2c->रुको);
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_disable_ack(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	ग_लिखोl(पंचांगp & ~S3C2410_IICCON_ACKEN, i2c->regs + S3C2410_IICCON);
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_enable_ack(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	ग_लिखोl(पंचांगp | S3C2410_IICCON_ACKEN, i2c->regs + S3C2410_IICCON);
पूर्ण

/* irq enable/disable functions */
अटल अंतरभूत व्योम s3c24xx_i2c_disable_irq(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	ग_लिखोl(पंचांगp & ~S3C2410_IICCON_IRQEN, i2c->regs + S3C2410_IICCON);
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_enable_irq(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	ग_लिखोl(पंचांगp | S3C2410_IICCON_IRQEN, i2c->regs + S3C2410_IICCON);
पूर्ण

अटल bool is_ack(काष्ठा s3c24xx_i2c *i2c)
अणु
	पूर्णांक tries;

	क्रम (tries = 50; tries; --tries) अणु
		अगर (पढ़ोl(i2c->regs + S3C2410_IICCON)
			& S3C2410_IICCON_IRQPEND) अणु
			अगर (!(पढ़ोl(i2c->regs + S3C2410_IICSTAT)
				& S3C2410_IICSTAT_LASTBIT))
				वापस true;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण
	dev_err(i2c->dev, "ack was not received\n");
	वापस false;
पूर्ण

/*
 * put the start of a message onto the bus
 */
अटल व्योम s3c24xx_i2c_message_start(काष्ठा s3c24xx_i2c *i2c,
				      काष्ठा i2c_msg *msg)
अणु
	अचिन्हित पूर्णांक addr = (msg->addr & 0x7f) << 1;
	अचिन्हित दीर्घ stat;
	अचिन्हित दीर्घ iiccon;

	stat = 0;
	stat |=  S3C2410_IICSTAT_TXRXEN;

	अगर (msg->flags & I2C_M_RD) अणु
		stat |= S3C2410_IICSTAT_MASTER_RX;
		addr |= 1;
	पूर्ण अन्यथा
		stat |= S3C2410_IICSTAT_MASTER_TX;

	अगर (msg->flags & I2C_M_REV_सूची_ADDR)
		addr ^= 1;

	/* toकरो - check क्रम whether ack wanted or not */
	s3c24xx_i2c_enable_ack(i2c);

	iiccon = पढ़ोl(i2c->regs + S3C2410_IICCON);
	ग_लिखोl(stat, i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "START: %08lx to IICSTAT, %02x to DS\n", stat, addr);
	ग_लिखोb(addr, i2c->regs + S3C2410_IICDS);

	/*
	 * delay here to ensure the data byte has gotten onto the bus
	 * beक्रमe the transaction is started
	 */
	ndelay(i2c->tx_setup);

	dev_dbg(i2c->dev, "iiccon, %08lx\n", iiccon);
	ग_लिखोl(iiccon, i2c->regs + S3C2410_IICCON);

	stat |= S3C2410_IICSTAT_START;
	ग_लिखोl(stat, i2c->regs + S3C2410_IICSTAT);

	अगर (i2c->quirks & QUIRK_POLL) अणु
		जबतक ((i2c->msg_num != 0) && is_ack(i2c)) अणु
			i2c_s3c_irq_nextbyte(i2c, stat);
			stat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);

			अगर (stat & S3C2410_IICSTAT_ARBITR)
				dev_err(i2c->dev, "deal with arbitration loss\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_stop(काष्ठा s3c24xx_i2c *i2c, पूर्णांक ret)
अणु
	अचिन्हित दीर्घ iicstat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STOP\n");

	/*
	 * The datasheet says that the STOP sequence should be:
	 *  1) I2CSTAT.5 = 0	- Clear BUSY (or 'generate STOP')
	 *  2) I2CCON.4 = 0	- Clear IRQPEND
	 *  3) Wait until the stop condition takes effect.
	 *  4*) I2CSTAT.4 = 0	- Clear TXRXEN
	 *
	 * Where, step "4*" is only क्रम buses with the "HDMIPHY" quirk.
	 *
	 * However, after much experimentation, it appears that:
	 * a) normal buses स्वतःmatically clear BUSY and transition from
	 *    Master->Slave when they complete generating a STOP condition.
	 *    Thereक्रमe, step (3) can be करोne in करोxfer() by polling I2CCON.4
	 *    after starting the STOP generation here.
	 * b) HDMIPHY bus करोes neither, so there is no way to करो step 3.
	 *    There is no indication when this bus has finished generating
	 *    STOP.
	 *
	 * In fact, we have found that as soon as the IRQPEND bit is cleared in
	 * step 2, the HDMIPHY bus generates the STOP condition, and then
	 * immediately starts transferring another data byte, even though the
	 * bus is supposedly stopped.  This is presumably because the bus is
	 * still in "Master" mode, and its BUSY bit is still set.
	 *
	 * To aव्योम these extra post-STOP transactions on HDMI phy devices, we
	 * just disable Serial Output on the bus (I2CSTAT.4 = 0) directly,
	 * instead of first generating a proper STOP condition.  This should
	 * भग्न SDA & SCK terminating the transfer.  Subsequent transfers
	 *  start with a proper START condition, and proceed normally.
	 *
	 * The HDMIPHY bus is an पूर्णांकernal bus that always has exactly two
	 * devices, the host as Master and the HDMIPHY device as the slave.
	 * Skipping the STOP condition has been tested on this bus and works.
	 */
	अगर (i2c->quirks & QUIRK_HDMIPHY) अणु
		/* Stop driving the I2C pins */
		iicstat &= ~S3C2410_IICSTAT_TXRXEN;
	पूर्ण अन्यथा अणु
		/* stop the transfer */
		iicstat &= ~S3C2410_IICSTAT_START;
	पूर्ण
	ग_लिखोl(iicstat, i2c->regs + S3C2410_IICSTAT);

	i2c->state = STATE_STOP;

	s3c24xx_i2c_master_complete(i2c, ret);
	s3c24xx_i2c_disable_irq(i2c);
पूर्ण

/*
 * helper functions to determine the current state in the set of
 * messages we are sending
 */

/*
 * वापसs TRUE अगर the current message is the last in the set
 */
अटल अंतरभूत पूर्णांक is_lasपंचांगsg(काष्ठा s3c24xx_i2c *i2c)
अणु
	वापस i2c->msg_idx >= (i2c->msg_num - 1);
पूर्ण

/*
 * वापसs TRUE अगर we this is the last byte in the current message
 */
अटल अंतरभूत पूर्णांक is_msglast(काष्ठा s3c24xx_i2c *i2c)
अणु
	/*
	 * msg->len is always 1 क्रम the first byte of smbus block पढ़ो.
	 * Actual length will be पढ़ो from slave. More bytes will be
	 * पढ़ो according to the length then.
	 */
	अगर (i2c->msg->flags & I2C_M_RECV_LEN && i2c->msg->len == 1)
		वापस 0;

	वापस i2c->msg_ptr == i2c->msg->len-1;
पूर्ण

/*
 * वापसs TRUE अगर we reached the end of the current message
 */
अटल अंतरभूत पूर्णांक is_msgend(काष्ठा s3c24xx_i2c *i2c)
अणु
	वापस i2c->msg_ptr >= i2c->msg->len;
पूर्ण

/*
 * process an पूर्णांकerrupt and work out what to करो
 */
अटल पूर्णांक i2c_s3c_irq_nextbyte(काष्ठा s3c24xx_i2c *i2c, अचिन्हित दीर्घ iicstat)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित अक्षर byte;
	पूर्णांक ret = 0;

	चयन (i2c->state) अणु

	हाल STATE_IDLE:
		dev_err(i2c->dev, "%s: called in STATE_IDLE\n", __func__);
		जाओ out;

	हाल STATE_STOP:
		dev_err(i2c->dev, "%s: called in STATE_STOP\n", __func__);
		s3c24xx_i2c_disable_irq(i2c);
		जाओ out_ack;

	हाल STATE_START:
		/*
		 * last thing we did was send a start condition on the
		 * bus, or started a new i2c message
		 */
		अगर (iicstat & S3C2410_IICSTAT_LASTBIT &&
		    !(i2c->msg->flags & I2C_M_IGNORE_NAK)) अणु
			/* ack was not received... */
			dev_dbg(i2c->dev, "ack was not received\n");
			s3c24xx_i2c_stop(i2c, -ENXIO);
			जाओ out_ack;
		पूर्ण

		अगर (i2c->msg->flags & I2C_M_RD)
			i2c->state = STATE_READ;
		अन्यथा
			i2c->state = STATE_WRITE;

		/*
		 * Terminate the transfer अगर there is nothing to करो
		 * as this is used by the i2c probe to find devices.
		 */
		अगर (is_lasपंचांगsg(i2c) && i2c->msg->len == 0) अणु
			s3c24xx_i2c_stop(i2c, 0);
			जाओ out_ack;
		पूर्ण

		अगर (i2c->state == STATE_READ)
			जाओ prepare_पढ़ो;

		/*
		 * fall through to the ग_लिखो state, as we will need to
		 * send a byte as well
		 */
		fallthrough;
	हाल STATE_WRITE:
		/*
		 * we are writing data to the device... check क्रम the
		 * end of the message, and अगर so, work out what to करो
		 */
		अगर (!(i2c->msg->flags & I2C_M_IGNORE_NAK)) अणु
			अगर (iicstat & S3C2410_IICSTAT_LASTBIT) अणु
				dev_dbg(i2c->dev, "WRITE: No Ack\n");

				s3c24xx_i2c_stop(i2c, -ECONNREFUSED);
				जाओ out_ack;
			पूर्ण
		पूर्ण

 retry_ग_लिखो:

		अगर (!is_msgend(i2c)) अणु
			byte = i2c->msg->buf[i2c->msg_ptr++];
			ग_लिखोb(byte, i2c->regs + S3C2410_IICDS);

			/*
			 * delay after writing the byte to allow the
			 * data setup समय on the bus, as writing the
			 * data to the रेजिस्टर causes the first bit
			 * to appear on SDA, and SCL will change as
			 * soon as the पूर्णांकerrupt is acknowledged
			 */
			ndelay(i2c->tx_setup);

		पूर्ण अन्यथा अगर (!is_lasपंचांगsg(i2c)) अणु
			/* we need to go to the next i2c message */

			dev_dbg(i2c->dev, "WRITE: Next Message\n");

			i2c->msg_ptr = 0;
			i2c->msg_idx++;
			i2c->msg++;

			/* check to see अगर we need to करो another message */
			अगर (i2c->msg->flags & I2C_M_NOSTART) अणु

				अगर (i2c->msg->flags & I2C_M_RD) अणु
					/*
					 * cannot करो this, the controller
					 * क्रमces us to send a new START
					 * when we change direction
					 */
					dev_dbg(i2c->dev,
						"missing START before write->read\n");
					s3c24xx_i2c_stop(i2c, -EINVAL);
					अवरोध;
				पूर्ण

				जाओ retry_ग_लिखो;
			पूर्ण अन्यथा अणु
				/* send the new start */
				s3c24xx_i2c_message_start(i2c, i2c->msg);
				i2c->state = STATE_START;
			पूर्ण

		पूर्ण अन्यथा अणु
			/* send stop */
			s3c24xx_i2c_stop(i2c, 0);
		पूर्ण
		अवरोध;

	हाल STATE_READ:
		/*
		 * we have a byte of data in the data रेजिस्टर, करो
		 * something with it, and then work out whether we are
		 * going to करो any more पढ़ो/ग_लिखो
		 */
		byte = पढ़ोb(i2c->regs + S3C2410_IICDS);
		i2c->msg->buf[i2c->msg_ptr++] = byte;

		/* Add actual length to पढ़ो क्रम smbus block पढ़ो */
		अगर (i2c->msg->flags & I2C_M_RECV_LEN && i2c->msg->len == 1)
			i2c->msg->len += byte;
 prepare_पढ़ो:
		अगर (is_msglast(i2c)) अणु
			/* last byte of buffer */

			अगर (is_lasपंचांगsg(i2c))
				s3c24xx_i2c_disable_ack(i2c);

		पूर्ण अन्यथा अगर (is_msgend(i2c)) अणु
			/*
			 * ok, we've पढ़ो the entire buffer, see अगर there
			 * is anything अन्यथा we need to करो
			 */
			अगर (is_lasपंचांगsg(i2c)) अणु
				/* last message, send stop and complete */
				dev_dbg(i2c->dev, "READ: Send Stop\n");

				s3c24xx_i2c_stop(i2c, 0);
			पूर्ण अन्यथा अणु
				/* go to the next transfer */
				dev_dbg(i2c->dev, "READ: Next Transfer\n");

				i2c->msg_ptr = 0;
				i2c->msg_idx++;
				i2c->msg++;
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	/* acknowlegde the IRQ and get back on with the work */

 out_ack:
	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	पंचांगp &= ~S3C2410_IICCON_IRQPEND;
	ग_लिखोl(पंचांगp, i2c->regs + S3C2410_IICCON);
 out:
	वापस ret;
पूर्ण

/*
 * top level IRQ servicing routine
 */
अटल irqवापस_t s3c24xx_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा s3c24xx_i2c *i2c = dev_id;
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ पंचांगp;

	status = पढ़ोl(i2c->regs + S3C2410_IICSTAT);

	अगर (status & S3C2410_IICSTAT_ARBITR) अणु
		/* deal with arbitration loss */
		dev_err(i2c->dev, "deal with arbitration loss\n");
	पूर्ण

	अगर (i2c->state == STATE_IDLE) अणु
		dev_dbg(i2c->dev, "IRQ: error i2c->state == IDLE\n");

		पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
		पंचांगp &= ~S3C2410_IICCON_IRQPEND;
		ग_लिखोl(पंचांगp, i2c->regs +  S3C2410_IICCON);
		जाओ out;
	पूर्ण

	/*
	 * pretty much this leaves us with the fact that we've
	 * transmitted or received whatever byte we last sent
	 */
	i2c_s3c_irq_nextbyte(i2c, status);

 out:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Disable the bus so that we won't get any पूर्णांकerrupts from now on, or try
 * to drive any lines. This is the शेष state when we करोn't have
 * anything to send/receive.
 *
 * If there is an event on the bus, or we have a pre-existing event at
 * kernel boot समय, we may not notice the event and the I2C controller
 * will lock the bus with the I2C घड़ी line low indefinitely.
 */
अटल अंतरभूत व्योम s3c24xx_i2c_disable_bus(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* Stop driving the I2C pins */
	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICSTAT);
	पंचांगp &= ~S3C2410_IICSTAT_TXRXEN;
	ग_लिखोl(पंचांगp, i2c->regs + S3C2410_IICSTAT);

	/* We करोn't expect any interrupts now, and don't want send acks */
	पंचांगp = पढ़ोl(i2c->regs + S3C2410_IICCON);
	पंचांगp &= ~(S3C2410_IICCON_IRQEN | S3C2410_IICCON_IRQPEND |
		S3C2410_IICCON_ACKEN);
	ग_लिखोl(पंचांगp, i2c->regs + S3C2410_IICCON);
पूर्ण


/*
 * get the i2c bus क्रम a master transaction
 */
अटल पूर्णांक s3c24xx_i2c_set_master(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ iicstat;
	पूर्णांक समयout = 400;

	जबतक (समयout-- > 0) अणु
		iicstat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);

		अगर (!(iicstat & S3C2410_IICSTAT_BUSBUSY))
			वापस 0;

		msleep(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/*
 * रुको क्रम the i2c bus to become idle.
 */
अटल व्योम s3c24xx_i2c_रुको_idle(काष्ठा s3c24xx_i2c *i2c)
अणु
	अचिन्हित दीर्घ iicstat;
	kसमय_प्रकार start, now;
	अचिन्हित दीर्घ delay;
	पूर्णांक spins;

	/* ensure the stop has been through the bus */

	dev_dbg(i2c->dev, "waiting for bus idle\n");

	start = now = kसमय_get();

	/*
	 * Most of the समय, the bus is alपढ़ोy idle within a few usec of the
	 * end of a transaction.  However, really slow i2c devices can stretch
	 * the घड़ी, delaying STOP generation.
	 *
	 * On slower SoCs this typically happens within a very small number of
	 * inकाष्ठाions so busy रुको briefly to aव्योम scheduling overhead.
	 */
	spins = 3;
	iicstat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);
	जबतक ((iicstat & S3C2410_IICSTAT_START) && --spins) अणु
		cpu_relax();
		iicstat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);
	पूर्ण

	/*
	 * If we करो get an appreciable delay as a compromise between idle
	 * detection latency क्रम the normal, fast हाल, and प्रणाली load in the
	 * slow device हाल, use an exponential back off in the polling loop,
	 * up to 1/10th of the total समयout, then जारी to poll at a
	 * स्थिरant rate up to the समयout.
	 */
	delay = 1;
	जबतक ((iicstat & S3C2410_IICSTAT_START) &&
	       kसमय_us_delta(now, start) < S3C2410_IDLE_TIMEOUT) अणु
		usleep_range(delay, 2 * delay);
		अगर (delay < S3C2410_IDLE_TIMEOUT / 10)
			delay <<= 1;
		now = kसमय_get();
		iicstat = पढ़ोl(i2c->regs + S3C2410_IICSTAT);
	पूर्ण

	अगर (iicstat & S3C2410_IICSTAT_START)
		dev_warn(i2c->dev, "timeout waiting for bus idle\n");
पूर्ण

/*
 * this starts an i2c transfer
 */
अटल पूर्णांक s3c24xx_i2c_करोxfer(काष्ठा s3c24xx_i2c *i2c,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	ret = s3c24xx_i2c_set_master(i2c);
	अगर (ret != 0) अणु
		dev_err(i2c->dev, "cannot get bus (error %d)\n", ret);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	i2c->msg     = msgs;
	i2c->msg_num = num;
	i2c->msg_ptr = 0;
	i2c->msg_idx = 0;
	i2c->state   = STATE_START;

	s3c24xx_i2c_enable_irq(i2c);
	s3c24xx_i2c_message_start(i2c, msgs);

	अगर (i2c->quirks & QUIRK_POLL) अणु
		ret = i2c->msg_idx;

		अगर (ret != num)
			dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);

		जाओ out;
	पूर्ण

	समयout = रुको_event_समयout(i2c->रुको, i2c->msg_num == 0, HZ * 5);

	ret = i2c->msg_idx;

	/*
	 * Having these next two as dev_err() makes lअगरe very
	 * noisy when करोing an i2cdetect
	 */
	अगर (समयout == 0)
		dev_dbg(i2c->dev, "timeout\n");
	अन्यथा अगर (ret != num)
		dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);

	/* For QUIRK_HDMIPHY, bus is alपढ़ोy disabled */
	अगर (i2c->quirks & QUIRK_HDMIPHY)
		जाओ out;

	s3c24xx_i2c_रुको_idle(i2c);

	s3c24xx_i2c_disable_bus(i2c);

 out:
	i2c->state = STATE_IDLE;

	वापस ret;
पूर्ण

/*
 * first port of call from the i2c bus code when an message needs
 * transferring across the i2c bus.
 */
अटल पूर्णांक s3c24xx_i2c_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा s3c24xx_i2c *i2c = (काष्ठा s3c24xx_i2c *)adap->algo_data;
	पूर्णांक retry;
	पूर्णांक ret;

	ret = clk_enable(i2c->clk);
	अगर (ret)
		वापस ret;

	क्रम (retry = 0; retry < adap->retries; retry++) अणु

		ret = s3c24xx_i2c_करोxfer(i2c, msgs, num);

		अगर (ret != -EAGAIN) अणु
			clk_disable(i2c->clk);
			वापस ret;
		पूर्ण

		dev_dbg(i2c->dev, "Retrying transmission (%d)\n", retry);

		udelay(100);
	पूर्ण

	clk_disable(i2c->clk);
	वापस -EREMOTEIO;
पूर्ण

/* declare our i2c functionality */
अटल u32 s3c24xx_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL_ALL | I2C_FUNC_NOSTART |
		I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

/* i2c bus registration info */
अटल स्थिर काष्ठा i2c_algorithm s3c24xx_i2c_algorithm = अणु
	.master_xfer		= s3c24xx_i2c_xfer,
	.functionality		= s3c24xx_i2c_func,
पूर्ण;

/*
 * वापस the भागisor settings क्रम a given frequency
 */
अटल पूर्णांक s3c24xx_i2c_calcभागisor(अचिन्हित दीर्घ clkin, अचिन्हित पूर्णांक wanted,
				   अचिन्हित पूर्णांक *भाग1, अचिन्हित पूर्णांक *भागs)
अणु
	अचिन्हित पूर्णांक calc_भागs = clkin / wanted;
	अचिन्हित पूर्णांक calc_भाग1;

	अगर (calc_भागs > (16*16))
		calc_भाग1 = 512;
	अन्यथा
		calc_भाग1 = 16;

	calc_भागs += calc_भाग1-1;
	calc_भागs /= calc_भाग1;

	अगर (calc_भागs == 0)
		calc_भागs = 1;
	अगर (calc_भागs > 17)
		calc_भागs = 17;

	*भागs = calc_भागs;
	*भाग1 = calc_भाग1;

	वापस clkin / (calc_भागs * calc_भाग1);
पूर्ण

/*
 * work out a भागisor क्रम the user requested frequency setting,
 * either by the requested frequency, or scanning the acceptable
 * range of frequencies until something is found
 */
अटल पूर्णांक s3c24xx_i2c_घड़ीrate(काष्ठा s3c24xx_i2c *i2c, अचिन्हित पूर्णांक *got)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *pdata = i2c->pdata;
	अचिन्हित दीर्घ clkin = clk_get_rate(i2c->clk);
	अचिन्हित पूर्णांक भागs, भाग1;
	अचिन्हित दीर्घ target_frequency;
	u32 iiccon;
	पूर्णांक freq;

	i2c->clkrate = clkin;
	clkin /= 1000;	/* clkin now in KHz */

	dev_dbg(i2c->dev, "pdata desired frequency %lu\n", pdata->frequency);

	target_frequency = pdata->frequency ?: I2C_MAX_STANDARD_MODE_FREQ;

	target_frequency /= 1000; /* Target frequency now in KHz */

	freq = s3c24xx_i2c_calcभागisor(clkin, target_frequency, &भाग1, &भागs);

	अगर (freq > target_frequency) अणु
		dev_err(i2c->dev,
			"Unable to achieve desired frequency %luKHz."	\
			" Lowest achievable %dKHz\n", target_frequency, freq);
		वापस -EINVAL;
	पूर्ण

	*got = freq;

	iiccon = पढ़ोl(i2c->regs + S3C2410_IICCON);
	iiccon &= ~(S3C2410_IICCON_SCALEMASK | S3C2410_IICCON_TXDIV_512);
	iiccon |= (भागs-1);

	अगर (भाग1 == 512)
		iiccon |= S3C2410_IICCON_TXDIV_512;

	अगर (i2c->quirks & QUIRK_POLL)
		iiccon |= S3C2410_IICCON_SCALE(2);

	ग_लिखोl(iiccon, i2c->regs + S3C2410_IICCON);

	अगर (i2c->quirks & QUIRK_S3C2440) अणु
		अचिन्हित दीर्घ sda_delay;

		अगर (pdata->sda_delay) अणु
			sda_delay = clkin * pdata->sda_delay;
			sda_delay = DIV_ROUND_UP(sda_delay, 1000000);
			sda_delay = DIV_ROUND_UP(sda_delay, 5);
			अगर (sda_delay > 3)
				sda_delay = 3;
			sda_delay |= S3C2410_IICLC_FILTER_ON;
		पूर्ण अन्यथा
			sda_delay = 0;

		dev_dbg(i2c->dev, "IICLC=%08lx\n", sda_delay);
		ग_लिखोl(sda_delay, i2c->regs + S3C2440_IICLC);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_ARM_S3C24XX_CPUFREQ)

#घोषणा freq_to_i2c(_n) container_of(_n, काष्ठा s3c24xx_i2c, freq_transition)

अटल पूर्णांक s3c24xx_i2c_cpufreq_transition(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा s3c24xx_i2c *i2c = freq_to_i2c(nb);
	अचिन्हित पूर्णांक got;
	पूर्णांक delta_f;
	पूर्णांक ret;

	delta_f = clk_get_rate(i2c->clk) - i2c->clkrate;

	/* अगर we're post-change and the input घड़ी has slowed करोwn
	 * or at pre-change and the घड़ी is about to speed up, then
	 * adjust our घड़ी rate. <0 is slow, >0 speedup.
	 */

	अगर ((val == CPUFREQ_POSTCHANGE && delta_f < 0) ||
	    (val == CPUFREQ_PRECHANGE && delta_f > 0)) अणु
		i2c_lock_bus(&i2c->adap, I2C_LOCK_ROOT_ADAPTER);
		ret = s3c24xx_i2c_घड़ीrate(i2c, &got);
		i2c_unlock_bus(&i2c->adap, I2C_LOCK_ROOT_ADAPTER);

		अगर (ret < 0)
			dev_err(i2c->dev, "cannot find frequency (%d)\n", ret);
		अन्यथा
			dev_info(i2c->dev, "setting freq %d\n", got);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3c24xx_i2c_रेजिस्टर_cpufreq(काष्ठा s3c24xx_i2c *i2c)
अणु
	i2c->freq_transition.notअगरier_call = s3c24xx_i2c_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&i2c->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_deरेजिस्टर_cpufreq(काष्ठा s3c24xx_i2c *i2c)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&i2c->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक s3c24xx_i2c_रेजिस्टर_cpufreq(काष्ठा s3c24xx_i2c *i2c)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s3c24xx_i2c_deरेजिस्टर_cpufreq(काष्ठा s3c24xx_i2c *i2c)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल पूर्णांक s3c24xx_i2c_parse_dt_gpio(काष्ठा s3c24xx_i2c *i2c)
अणु
	पूर्णांक i;

	अगर (i2c->quirks & QUIRK_NO_GPIO)
		वापस 0;

	क्रम (i = 0; i < 2; i++) अणु
		i2c->gpios[i] = devm_gpiod_get_index(i2c->dev, शून्य,
						     i, GPIOD_ASIS);
		अगर (IS_ERR(i2c->gpios[i])) अणु
			dev_err(i2c->dev, "i2c gpio invalid at index %d\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक s3c24xx_i2c_parse_dt_gpio(काष्ठा s3c24xx_i2c *i2c)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * initialise the controller, set the IO lines and frequency
 */
अटल पूर्णांक s3c24xx_i2c_init(काष्ठा s3c24xx_i2c *i2c)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *pdata;
	अचिन्हित पूर्णांक freq;

	/* get the plafrom data */

	pdata = i2c->pdata;

	/* ग_लिखो slave address */

	ग_लिखोb(pdata->slave_addr, i2c->regs + S3C2410_IICADD);

	dev_info(i2c->dev, "slave address 0x%02x\n", pdata->slave_addr);

	ग_लिखोl(0, i2c->regs + S3C2410_IICCON);
	ग_लिखोl(0, i2c->regs + S3C2410_IICSTAT);

	/* we need to work out the भागisors क्रम the घड़ी... */

	अगर (s3c24xx_i2c_घड़ीrate(i2c, &freq) != 0) अणु
		dev_err(i2c->dev, "cannot meet bus frequency required\n");
		वापस -EINVAL;
	पूर्ण

	/* toकरो - check that the i2c lines aren't being dragged anywhere */

	dev_info(i2c->dev, "bus frequency set to %d KHz\n", freq);
	dev_dbg(i2c->dev, "S3C2410_IICCON=0x%02x\n",
		पढ़ोl(i2c->regs + S3C2410_IICCON));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
/*
 * Parse the device tree node and retreive the platक्रमm data.
 */
अटल व्योम
s3c24xx_i2c_parse_dt(काष्ठा device_node *np, काष्ठा s3c24xx_i2c *i2c)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *pdata = i2c->pdata;
	पूर्णांक id;

	अगर (!np)
		वापस;

	pdata->bus_num = -1; /* i2c bus number is dynamically asचिन्हित */
	of_property_पढ़ो_u32(np, "samsung,i2c-sda-delay", &pdata->sda_delay);
	of_property_पढ़ो_u32(np, "samsung,i2c-slave-addr", &pdata->slave_addr);
	of_property_पढ़ो_u32(np, "samsung,i2c-max-bus-freq",
				(u32 *)&pdata->frequency);
	/*
	 * Exynos5's legacy i2c controller and new high speed i2c
	 * controller have muxed पूर्णांकerrupt sources. By शेष the
	 * पूर्णांकerrupts क्रम 4-channel HS-I2C controller are enabled.
	 * If nodes क्रम first four channels of legacy i2c controller
	 * are available then re-configure the पूर्णांकerrupts via the
	 * प्रणाली रेजिस्टर.
	 */
	id = of_alias_get_id(np, "i2c");
	i2c->sysreg = syscon_regmap_lookup_by_phandle(np,
			"samsung,sysreg-phandle");
	अगर (IS_ERR(i2c->sysreg))
		वापस;

	regmap_update_bits(i2c->sysreg, EXYNOS5_SYS_I2C_CFG, BIT(id), 0);
पूर्ण
#अन्यथा
अटल व्योम
s3c24xx_i2c_parse_dt(काष्ठा device_node *np, काष्ठा s3c24xx_i2c *i2c) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक s3c24xx_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c24xx_i2c *i2c;
	काष्ठा s3c2410_platक्रमm_i2c *pdata = शून्य;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node) अणु
		pdata = dev_get_platdata(&pdev->dev);
		अगर (!pdata) अणु
			dev_err(&pdev->dev, "no platform data\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा s3c24xx_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!i2c->pdata)
		वापस -ENOMEM;

	i2c->quirks = s3c24xx_get_device_quirks(pdev);
	i2c->sysreg = ERR_PTR(-ENOENT);
	अगर (pdata)
		स_नकल(i2c->pdata, pdata, माप(*pdata));
	अन्यथा
		s3c24xx_i2c_parse_dt(pdev->dev.of_node, i2c);

	strlcpy(i2c->adap.name, "s3c2410-i2c", माप(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &s3c24xx_i2c_algorithm;
	i2c->adap.retries = 2;
	i2c->adap.class = I2C_CLASS_DEPRECATED;
	i2c->tx_setup = 50;

	init_रुकोqueue_head(&i2c->रुको);

	/* find the घड़ी and enable it */
	i2c->dev = &pdev->dev;
	i2c->clk = devm_clk_get(&pdev->dev, "i2c");
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस -ENOENT;
	पूर्ण

	dev_dbg(&pdev->dev, "clock source %p\n", i2c->clk);

	/* map the रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c->regs = devm_ioremap_resource(&pdev->dev, res);

	अगर (IS_ERR(i2c->regs))
		वापस PTR_ERR(i2c->regs);

	dev_dbg(&pdev->dev, "registers %p (%p)\n",
		i2c->regs, res);

	/* setup info block क्रम the i2c core */
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->pctrl = devm_pinctrl_get_select_शेष(i2c->dev);

	/* inititalise the i2c gpio lines */
	अगर (i2c->pdata->cfg_gpio)
		i2c->pdata->cfg_gpio(to_platक्रमm_device(i2c->dev));
	अन्यथा अगर (IS_ERR(i2c->pctrl) && s3c24xx_i2c_parse_dt_gpio(i2c))
		वापस -EINVAL;

	/* initialise the i2c controller */
	ret = clk_prepare_enable(i2c->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "I2C clock enable failed\n");
		वापस ret;
	पूर्ण

	ret = s3c24xx_i2c_init(i2c);
	clk_disable(i2c->clk);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "I2C controller init failed\n");
		clk_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	/*
	 * find the IRQ क्रम this unit (note, this relies on the init call to
	 * ensure no current IRQs pending
	 */
	अगर (!(i2c->quirks & QUIRK_POLL)) अणु
		i2c->irq = ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret <= 0) अणु
			dev_err(&pdev->dev, "cannot find IRQ\n");
			clk_unprepare(i2c->clk);
			वापस ret;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, i2c->irq, s3c24xx_i2c_irq,
				       0, dev_name(&pdev->dev), i2c);
		अगर (ret != 0) अणु
			dev_err(&pdev->dev, "cannot claim IRQ %d\n", i2c->irq);
			clk_unprepare(i2c->clk);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = s3c24xx_i2c_रेजिस्टर_cpufreq(i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register cpufreq notifier\n");
		clk_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	/*
	 * Note, previous versions of the driver used i2c_add_adapter()
	 * to add the bus at any number. We now pass the bus number via
	 * the platक्रमm data, so अगर unset it will now शेष to always
	 * being bus 0.
	 */
	i2c->adap.nr = i2c->pdata->bus_num;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	platक्रमm_set_drvdata(pdev, i2c);

	pm_runसमय_enable(&pdev->dev);

	ret = i2c_add_numbered_adapter(&i2c->adap);
	अगर (ret < 0) अणु
		pm_runसमय_disable(&pdev->dev);
		s3c24xx_i2c_deरेजिस्टर_cpufreq(i2c);
		clk_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "%s: S3C I2C adapter\n", dev_name(&i2c->adap.dev));
	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c24xx_i2c *i2c = platक्रमm_get_drvdata(pdev);

	clk_unprepare(i2c->clk);

	pm_runसमय_disable(&pdev->dev);

	s3c24xx_i2c_deरेजिस्टर_cpufreq(i2c);

	i2c_del_adapter(&i2c->adap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक s3c24xx_i2c_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_i2c *i2c = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&i2c->adap);

	अगर (!IS_ERR(i2c->sysreg))
		regmap_पढ़ो(i2c->sysreg, EXYNOS5_SYS_I2C_CFG, &i2c->sys_i2c_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_i2c_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा s3c24xx_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!IS_ERR(i2c->sysreg))
		regmap_ग_लिखो(i2c->sysreg, EXYNOS5_SYS_I2C_CFG, i2c->sys_i2c_cfg);

	ret = clk_enable(i2c->clk);
	अगर (ret)
		वापस ret;
	s3c24xx_i2c_init(i2c);
	clk_disable(i2c->clk);
	i2c_mark_adapter_resumed(&i2c->adap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops s3c24xx_i2c_dev_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(s3c24xx_i2c_suspend_noirq,
				      s3c24xx_i2c_resume_noirq)
पूर्ण;

#घोषणा S3C24XX_DEV_PM_OPS (&s3c24xx_i2c_dev_pm_ops)
#अन्यथा
#घोषणा S3C24XX_DEV_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver s3c24xx_i2c_driver = अणु
	.probe		= s3c24xx_i2c_probe,
	.हटाओ		= s3c24xx_i2c_हटाओ,
	.id_table	= s3c24xx_driver_ids,
	.driver		= अणु
		.name	= "s3c-i2c",
		.pm	= S3C24XX_DEV_PM_OPS,
		.of_match_table = of_match_ptr(s3c24xx_i2c_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init i2c_adap_s3c_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s3c24xx_i2c_driver);
पूर्ण
subsys_initcall(i2c_adap_s3c_init);

अटल व्योम __निकास i2c_adap_s3c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&s3c24xx_i2c_driver);
पूर्ण
module_निकास(i2c_adap_s3c_निकास);

MODULE_DESCRIPTION("S3C24XX I2C Bus driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");
