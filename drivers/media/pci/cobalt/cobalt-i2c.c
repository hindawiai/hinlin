<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cobalt I2C functions
 *
 *  Derived from cx18-i2c.c
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश "cobalt-driver.h"
#समावेश "cobalt-i2c.h"

काष्ठा cobalt_i2c_regs अणु
	/* Clock prescaler रेजिस्टर lo-byte */
	u8 prerlo;
	u8 dummy0[3];
	/* Clock prescaler रेजिस्टर high-byte */
	u8 prerhi;
	u8 dummy1[3];
	/* Control रेजिस्टर */
	u8 ctr;
	u8 dummy2[3];
	/* Transmit/Receive रेजिस्टर */
	u8 txr_rxr;
	u8 dummy3[3];
	/* Command and Status रेजिस्टर */
	u8 cr_sr;
	u8 dummy4[3];
पूर्ण;

/* CTR[7:0] - Control रेजिस्टर */

/* I2C Core enable bit */
#घोषणा M00018_CTR_BITMAP_EN_MSK	(1 << 7)

/* I2C Core पूर्णांकerrupt enable bit */
#घोषणा M00018_CTR_BITMAP_IEN_MSK	(1 << 6)

/* CR[7:0] - Command रेजिस्टर */

/* I2C start condition */
#घोषणा M00018_CR_BITMAP_STA_MSK	(1 << 7)

/* I2C stop condition */
#घोषणा M00018_CR_BITMAP_STO_MSK	(1 << 6)

/* I2C पढ़ो from slave */
#घोषणा M00018_CR_BITMAP_RD_MSK		(1 << 5)

/* I2C ग_लिखो to slave */
#घोषणा M00018_CR_BITMAP_WR_MSK		(1 << 4)

/* I2C ack */
#घोषणा M00018_CR_BITMAP_ACK_MSK	(1 << 3)

/* I2C Interrupt ack */
#घोषणा M00018_CR_BITMAP_IACK_MSK	(1 << 0)

/* SR[7:0] - Status रेजिस्टर */

/* Receive acknowledge from slave */
#घोषणा M00018_SR_BITMAP_RXACK_MSK	(1 << 7)

/* Busy, I2C bus busy (as defined by start / stop bits) */
#घोषणा M00018_SR_BITMAP_BUSY_MSK	(1 << 6)

/* Arbitration lost - core lost arbitration */
#घोषणा M00018_SR_BITMAP_AL_MSK		(1 << 5)

/* Transfer in progress */
#घोषणा M00018_SR_BITMAP_TIP_MSK	(1 << 1)

/* Interrupt flag */
#घोषणा M00018_SR_BITMAP_IF_MSK		(1 << 0)

/* Frequency, in Hz */
#घोषणा I2C_FREQUENCY			400000
#घोषणा ALT_CPU_FREQ			83333333

अटल काष्ठा cobalt_i2c_regs __iomem *
cobalt_i2c_regs(काष्ठा cobalt *cobalt, अचिन्हित idx)
अणु
	चयन (idx) अणु
	हाल 0:
	शेष:
		वापस (काष्ठा cobalt_i2c_regs __iomem *)
			(cobalt->bar1 + COBALT_I2C_0_BASE);
	हाल 1:
		वापस (काष्ठा cobalt_i2c_regs __iomem *)
			(cobalt->bar1 + COBALT_I2C_1_BASE);
	हाल 2:
		वापस (काष्ठा cobalt_i2c_regs __iomem *)
			(cobalt->bar1 + COBALT_I2C_2_BASE);
	हाल 3:
		वापस (काष्ठा cobalt_i2c_regs __iomem *)
			(cobalt->bar1 + COBALT_I2C_3_BASE);
	हाल 4:
		वापस (काष्ठा cobalt_i2c_regs __iomem *)
			(cobalt->bar1 + COBALT_I2C_HSMA_BASE);
	पूर्ण
पूर्ण

/* Do low-level i2c byte transfer.
 * Returns -1 in हाल of an error or 0 otherwise.
 */
अटल पूर्णांक cobalt_tx_bytes(काष्ठा cobalt_i2c_regs __iomem *regs,
		काष्ठा i2c_adapter *adap, bool start, bool stop,
		u8 *data, u16 len)
अणु
	अचिन्हित दीर्घ start_समय;
	पूर्णांक status;
	पूर्णांक cmd;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		/* Setup data */
		ioग_लिखो8(data[i], &regs->txr_rxr);

		/* Setup command */
		अगर (i == 0 && start) अणु
			/* Write + Start */
			cmd = M00018_CR_BITMAP_WR_MSK |
			      M00018_CR_BITMAP_STA_MSK;
		पूर्ण अन्यथा अगर (i == len - 1 && stop) अणु
			/* Write + Stop */
			cmd = M00018_CR_BITMAP_WR_MSK |
			      M00018_CR_BITMAP_STO_MSK;
		पूर्ण अन्यथा अणु
			/* Write only */
			cmd = M00018_CR_BITMAP_WR_MSK;
		पूर्ण

		/* Execute command */
		ioग_लिखो8(cmd, &regs->cr_sr);

		/* Wait क्रम transfer to complete (TIP = 0) */
		start_समय = jअगरfies;
		status = ioपढ़ो8(&regs->cr_sr);
		जबतक (status & M00018_SR_BITMAP_TIP_MSK) अणु
			अगर (समय_after(jअगरfies, start_समय + adap->समयout))
				वापस -ETIMEDOUT;
			cond_resched();
			status = ioपढ़ो8(&regs->cr_sr);
		पूर्ण

		/* Verअगरy ACK */
		अगर (status & M00018_SR_BITMAP_RXACK_MSK) अणु
			/* NO ACK! */
			वापस -EIO;
		पूर्ण

		/* Verअगरy arbitration */
		अगर (status & M00018_SR_BITMAP_AL_MSK) अणु
			/* Arbitration lost! */
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Do low-level i2c byte पढ़ो.
 * Returns -1 in हाल of an error or 0 otherwise.
 */
अटल पूर्णांक cobalt_rx_bytes(काष्ठा cobalt_i2c_regs __iomem *regs,
		काष्ठा i2c_adapter *adap, bool start, bool stop,
		u8 *data, u16 len)
अणु
	अचिन्हित दीर्घ start_समय;
	पूर्णांक status;
	पूर्णांक cmd;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		/* Setup command */
		अगर (i == 0 && start) अणु
			/* Read + Start */
			cmd = M00018_CR_BITMAP_RD_MSK |
			      M00018_CR_BITMAP_STA_MSK;
		पूर्ण अन्यथा अगर (i == len - 1 && stop) अणु
			/* Read + Stop */
			cmd = M00018_CR_BITMAP_RD_MSK |
			      M00018_CR_BITMAP_STO_MSK;
		पूर्ण अन्यथा अणु
			/* Read only */
			cmd = M00018_CR_BITMAP_RD_MSK;
		पूर्ण

		/* Last byte to पढ़ो, no ACK */
		अगर (i == len - 1)
			cmd |= M00018_CR_BITMAP_ACK_MSK;

		/* Execute command */
		ioग_लिखो8(cmd, &regs->cr_sr);

		/* Wait क्रम transfer to complete (TIP = 0) */
		start_समय = jअगरfies;
		status = ioपढ़ो8(&regs->cr_sr);
		जबतक (status & M00018_SR_BITMAP_TIP_MSK) अणु
			अगर (समय_after(jअगरfies, start_समय + adap->समयout))
				वापस -ETIMEDOUT;
			cond_resched();
			status = ioपढ़ो8(&regs->cr_sr);
		पूर्ण

		/* Verअगरy arbitration */
		अगर (status & M00018_SR_BITMAP_AL_MSK) अणु
			/* Arbitration lost! */
			वापस -EIO;
		पूर्ण

		/* Store data */
		data[i] = ioपढ़ो8(&regs->txr_rxr);
	पूर्ण
	वापस 0;
पूर्ण

/* Generate stop condition on i2c bus.
 * The m00018 stop isn't करोing the right thing (wrong timing).
 * So instead send a start condition, 8 zeroes and a stop condition.
 */
अटल पूर्णांक cobalt_stop(काष्ठा cobalt_i2c_regs __iomem *regs,
		काष्ठा i2c_adapter *adap)
अणु
	u8 data = 0;

	वापस cobalt_tx_bytes(regs, adap, true, true, &data, 1);
पूर्ण

अटल पूर्णांक cobalt_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा cobalt_i2c_data *data = adap->algo_data;
	काष्ठा cobalt_i2c_regs __iomem *regs = data->regs;
	काष्ठा i2c_msg *pmsg;
	अचिन्हित लघु flags;
	पूर्णांक ret = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < num; i++) अणु
		पूर्णांक stop = (i == num - 1);

		pmsg = &msgs[i];
		flags = pmsg->flags;

		अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
			u8 addr = pmsg->addr << 1;

			अगर (flags & I2C_M_RD)
				addr |= 1;
			अगर (flags & I2C_M_REV_सूची_ADDR)
				addr ^= 1;
			क्रम (j = 0; j < adap->retries; j++) अणु
				ret = cobalt_tx_bytes(regs, adap, true, false,
						      &addr, 1);
				अगर (!ret)
					अवरोध;
				cobalt_stop(regs, adap);
			पूर्ण
			अगर (ret < 0)
				वापस ret;
			ret = 0;
		पूर्ण
		अगर (pmsg->flags & I2C_M_RD) अणु
			/* पढ़ो bytes पूर्णांकo buffer */
			ret = cobalt_rx_bytes(regs, adap, false, stop,
					pmsg->buf, pmsg->len);
			अगर (ret < 0)
				जाओ bailout;
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes from buffer */
			ret = cobalt_tx_bytes(regs, adap, false, stop,
					pmsg->buf, pmsg->len);
			अगर (ret < 0)
				जाओ bailout;
		पूर्ण
	पूर्ण
	ret = i;

bailout:
	अगर (ret < 0)
		cobalt_stop(regs, adap);
	वापस ret;
पूर्ण

अटल u32 cobalt_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

/* ढाँचा क्रम i2c-bit-algo */
अटल स्थिर काष्ठा i2c_adapter cobalt_i2c_adap_ढाँचा = अणु
	.name = "cobalt i2c driver",
	.algo = शून्य,                   /* set by i2c-algo-bit */
	.algo_data = शून्य,              /* filled from ढाँचा */
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm cobalt_algo = अणु
	.master_xfer	= cobalt_xfer,
	.functionality	= cobalt_func,
पूर्ण;

/* init + रेजिस्टर i2c algo-bit adapter */
पूर्णांक cobalt_i2c_init(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक i, err;
	पूर्णांक status;
	पूर्णांक prescale;
	अचिन्हित दीर्घ start_समय;

	cobalt_dbg(1, "i2c init\n");

	/* Define I2C घड़ी prescaler */
	prescale = ((ALT_CPU_FREQ) / (5 * I2C_FREQUENCY)) - 1;

	क्रम (i = 0; i < COBALT_NUM_ADAPTERS; i++) अणु
		काष्ठा cobalt_i2c_regs __iomem *regs =
			cobalt_i2c_regs(cobalt, i);
		काष्ठा i2c_adapter *adap = &cobalt->i2c_adap[i];

		/* Disable I2C */
		ioग_लिखो8(M00018_CTR_BITMAP_EN_MSK, &regs->cr_sr);
		ioग_लिखो8(0, &regs->ctr);
		ioग_लिखो8(0, &regs->cr_sr);

		start_समय = jअगरfies;
		करो अणु
			अगर (समय_after(jअगरfies, start_समय + HZ)) अणु
				अगर (cobalt_ignore_err) अणु
					adap->dev.parent = शून्य;
					वापस 0;
				पूर्ण
				वापस -ETIMEDOUT;
			पूर्ण
			status = ioपढ़ो8(&regs->cr_sr);
		पूर्ण जबतक (status & M00018_SR_BITMAP_TIP_MSK);

		/* Disable I2C */
		ioग_लिखो8(0, &regs->ctr);
		ioग_लिखो8(0, &regs->cr_sr);

		/* Calculate i2c prescaler */
		ioग_लिखो8(prescale & 0xff, &regs->prerlo);
		ioग_लिखो8((prescale >> 8) & 0xff, &regs->prerhi);
		/* Enable I2C, पूर्णांकerrupts disabled */
		ioग_लिखो8(M00018_CTR_BITMAP_EN_MSK, &regs->ctr);
		/* Setup algorithm क्रम adapter */
		cobalt->i2c_data[i].cobalt = cobalt;
		cobalt->i2c_data[i].regs = regs;
		*adap = cobalt_i2c_adap_ढाँचा;
		adap->algo = &cobalt_algo;
		adap->algo_data = &cobalt->i2c_data[i];
		adap->retries = 3;
		प्र_लिखो(adap->name + म_माप(adap->name),
				" #%d-%d", cobalt->instance, i);
		i2c_set_adapdata(adap, &cobalt->v4l2_dev);
		adap->dev.parent = &cobalt->pci_dev->dev;
		err = i2c_add_adapter(adap);
		अगर (err) अणु
			अगर (cobalt_ignore_err) अणु
				adap->dev.parent = शून्य;
				वापस 0;
			पूर्ण
			जबतक (i--)
				i2c_del_adapter(&cobalt->i2c_adap[i]);
			वापस err;
		पूर्ण
		cobalt_info("registered bus %s\n", adap->name);
	पूर्ण
	वापस 0;
पूर्ण

व्योम cobalt_i2c_निकास(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक i;

	cobalt_dbg(1, "i2c exit\n");

	क्रम (i = 0; i < COBALT_NUM_ADAPTERS; i++) अणु
		cobalt_err("unregistered bus %s\n", cobalt->i2c_adap[i].name);
		i2c_del_adapter(&cobalt->i2c_adap[i]);
	पूर्ण
पूर्ण
