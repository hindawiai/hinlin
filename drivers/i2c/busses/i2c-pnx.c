<शैली गुरु>
/*
 * Provides I2C support क्रम Philips PNX010x/PNX4008 boards.
 *
 * Authors: Dennis Kovalev <dkovalev@ru.mvista.com>
 *	    Vitaly Wool <vwool@ru.mvista.com>
 *
 * 2004-2006 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#घोषणा I2C_PNX_TIMEOUT_DEFAULT		10 /* msec */
#घोषणा I2C_PNX_SPEED_KHZ_DEFAULT	100
#घोषणा I2C_PNX_REGION_SIZE		0x100

काष्ठा i2c_pnx_mअगर अणु
	पूर्णांक			ret;		/* Return value */
	पूर्णांक			mode;		/* Interface mode */
	काष्ठा completion	complete;	/* I/O completion */
	काष्ठा समयr_list	समयr;		/* Timeout */
	u8 *			buf;		/* Data buffer */
	पूर्णांक			len;		/* Length of data buffer */
	पूर्णांक			order;		/* RX Bytes to order via TX */
पूर्ण;

काष्ठा i2c_pnx_algo_data अणु
	व्योम __iomem		*ioaddr;
	काष्ठा i2c_pnx_mअगर	mअगर;
	पूर्णांक			last;
	काष्ठा clk		*clk;
	काष्ठा i2c_adapter	adapter;
	पूर्णांक			irq;
	u32			समयout;
पूर्ण;

क्रमागत अणु
	mstatus_tdi = 0x00000001,
	mstatus_afi = 0x00000002,
	mstatus_nai = 0x00000004,
	mstatus_drmi = 0x00000008,
	mstatus_active = 0x00000020,
	mstatus_scl = 0x00000040,
	mstatus_sda = 0x00000080,
	mstatus_rff = 0x00000100,
	mstatus_rfe = 0x00000200,
	mstatus_tff = 0x00000400,
	mstatus_tfe = 0x00000800,
पूर्ण;

क्रमागत अणु
	mcntrl_tdie = 0x00000001,
	mcntrl_afie = 0x00000002,
	mcntrl_naie = 0x00000004,
	mcntrl_drmie = 0x00000008,
	mcntrl_drsie = 0x00000010,
	mcntrl_rffie = 0x00000020,
	mcntrl_daie = 0x00000040,
	mcntrl_tffie = 0x00000080,
	mcntrl_reset = 0x00000100,
	mcntrl_cdbmode = 0x00000400,
पूर्ण;

क्रमागत अणु
	rw_bit = 1 << 0,
	start_bit = 1 << 8,
	stop_bit = 1 << 9,
पूर्ण;

#घोषणा I2C_REG_RX(a)	((a)->ioaddr)		/* Rx FIFO reg (RO) */
#घोषणा I2C_REG_TX(a)	((a)->ioaddr)		/* Tx FIFO reg (WO) */
#घोषणा I2C_REG_STS(a)	((a)->ioaddr + 0x04)	/* Status reg (RO) */
#घोषणा I2C_REG_CTL(a)	((a)->ioaddr + 0x08)	/* Ctl reg */
#घोषणा I2C_REG_CKL(a)	((a)->ioaddr + 0x0c)	/* Clock भागider low */
#घोषणा I2C_REG_CKH(a)	((a)->ioaddr + 0x10)	/* Clock भागider high */
#घोषणा I2C_REG_ADR(a)	((a)->ioaddr + 0x14)	/* I2C address */
#घोषणा I2C_REG_RFL(a)	((a)->ioaddr + 0x18)	/* Rx FIFO level (RO) */
#घोषणा I2C_REG_TFL(a)	((a)->ioaddr + 0x1c)	/* Tx FIFO level (RO) */
#घोषणा I2C_REG_RXB(a)	((a)->ioaddr + 0x20)	/* Num of bytes Rx-ed (RO) */
#घोषणा I2C_REG_TXB(a)	((a)->ioaddr + 0x24)	/* Num of bytes Tx-ed (RO) */
#घोषणा I2C_REG_TXS(a)	((a)->ioaddr + 0x28)	/* Tx slave FIFO (RO) */
#घोषणा I2C_REG_STFL(a)	((a)->ioaddr + 0x2c)	/* Tx slave FIFO level (RO) */

अटल अंतरभूत पूर्णांक रुको_समयout(काष्ठा i2c_pnx_algo_data *data)
अणु
	दीर्घ समयout = data->समयout;
	जबतक (समयout > 0 &&
			(ioपढ़ो32(I2C_REG_STS(data)) & mstatus_active)) अणु
		mdelay(1);
		समयout--;
	पूर्ण
	वापस (समयout <= 0);
पूर्ण

अटल अंतरभूत पूर्णांक रुको_reset(काष्ठा i2c_pnx_algo_data *data)
अणु
	दीर्घ समयout = data->समयout;
	जबतक (समयout > 0 &&
			(ioपढ़ो32(I2C_REG_CTL(data)) & mcntrl_reset)) अणु
		mdelay(1);
		समयout--;
	पूर्ण
	वापस (समयout <= 0);
पूर्ण

अटल अंतरभूत व्योम i2c_pnx_arm_समयr(काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	काष्ठा समयr_list *समयr = &alg_data->mअगर.समयr;
	अचिन्हित दीर्घ expires = msecs_to_jअगरfies(alg_data->समयout);

	अगर (expires <= 1)
		expires = 2;

	del_समयr_sync(समयr);

	dev_dbg(&alg_data->adapter.dev, "Timer armed at %lu plus %lu jiffies.\n",
		jअगरfies, expires);

	समयr->expires = jअगरfies + expires;

	add_समयr(समयr);
पूर्ण

/**
 * i2c_pnx_start - start a device
 * @slave_addr:		slave address
 * @alg_data:		poपूर्णांकer to local driver data काष्ठाure
 *
 * Generate a START संकेत in the desired mode.
 */
अटल पूर्णांक i2c_pnx_start(अचिन्हित अक्षर slave_addr,
	काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	dev_dbg(&alg_data->adapter.dev, "%s(): addr 0x%x mode %d\n", __func__,
		slave_addr, alg_data->mअगर.mode);

	/* Check क्रम 7 bit slave addresses only */
	अगर (slave_addr & ~0x7f) अणु
		dev_err(&alg_data->adapter.dev,
			"%s: Invalid slave address %x. Only 7-bit addresses are supported\n",
			alg_data->adapter.name, slave_addr);
		वापस -EINVAL;
	पूर्ण

	/* First, make sure bus is idle */
	अगर (रुको_समयout(alg_data)) अणु
		/* Somebody अन्यथा is monopolizing the bus */
		dev_err(&alg_data->adapter.dev,
			"%s: Bus busy. Slave addr = %02x, cntrl = %x, stat = %x\n",
			alg_data->adapter.name, slave_addr,
			ioपढ़ो32(I2C_REG_CTL(alg_data)),
			ioपढ़ो32(I2C_REG_STS(alg_data)));
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (ioपढ़ो32(I2C_REG_STS(alg_data)) & mstatus_afi) अणु
		/* Sorry, we lost the bus */
		dev_err(&alg_data->adapter.dev,
		        "%s: Arbitration failure. Slave addr = %02x\n",
			alg_data->adapter.name, slave_addr);
		वापस -EIO;
	पूर्ण

	/*
	 * OK, I2C is enabled and we have the bus.
	 * Clear the current TDI and AFI status flags.
	 */
	ioग_लिखो32(ioपढ़ो32(I2C_REG_STS(alg_data)) | mstatus_tdi | mstatus_afi,
		  I2C_REG_STS(alg_data));

	dev_dbg(&alg_data->adapter.dev, "%s(): sending %#x\n", __func__,
		(slave_addr << 1) | start_bit | alg_data->mअगर.mode);

	/* Write the slave address, START bit and R/W bit */
	ioग_लिखो32((slave_addr << 1) | start_bit | alg_data->mअगर.mode,
		  I2C_REG_TX(alg_data));

	dev_dbg(&alg_data->adapter.dev, "%s(): exit\n", __func__);

	वापस 0;
पूर्ण

/**
 * i2c_pnx_stop - stop a device
 * @alg_data:		poपूर्णांकer to local driver data काष्ठाure
 *
 * Generate a STOP संकेत to terminate the master transaction.
 */
अटल व्योम i2c_pnx_stop(काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	/* Only 1 msec max समयout due to पूर्णांकerrupt context */
	दीर्घ समयout = 1000;

	dev_dbg(&alg_data->adapter.dev, "%s(): entering: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	/* Write a STOP bit to TX FIFO */
	ioग_लिखो32(0xff | stop_bit, I2C_REG_TX(alg_data));

	/* Wait until the STOP is seen. */
	जबतक (समयout > 0 &&
	       (ioपढ़ो32(I2C_REG_STS(alg_data)) & mstatus_active)) अणु
		/* may be called from पूर्णांकerrupt context */
		udelay(1);
		समयout--;
	पूर्ण

	dev_dbg(&alg_data->adapter.dev, "%s(): exiting: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));
पूर्ण

/**
 * i2c_pnx_master_xmit - transmit data to slave
 * @alg_data:		poपूर्णांकer to local driver data काष्ठाure
 *
 * Sends one byte of data to the slave
 */
अटल पूर्णांक i2c_pnx_master_xmit(काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	u32 val;

	dev_dbg(&alg_data->adapter.dev, "%s(): entering: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	अगर (alg_data->mअगर.len > 0) अणु
		/* We still have something to talk about... */
		val = *alg_data->mअगर.buf++;

		अगर (alg_data->mअगर.len == 1)
			val |= stop_bit;

		alg_data->mअगर.len--;
		ioग_लिखो32(val, I2C_REG_TX(alg_data));

		dev_dbg(&alg_data->adapter.dev, "%s(): xmit %#x [%d]\n",
			__func__, val, alg_data->mअगर.len + 1);

		अगर (alg_data->mअगर.len == 0) अणु
			अगर (alg_data->last) अणु
				/* Wait until the STOP is seen. */
				अगर (रुको_समयout(alg_data))
					dev_err(&alg_data->adapter.dev,
						"The bus is still active after timeout\n");
			पूर्ण
			/* Disable master पूर्णांकerrupts */
			ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) &
				~(mcntrl_afie | mcntrl_naie | mcntrl_drmie),
				  I2C_REG_CTL(alg_data));

			del_समयr_sync(&alg_data->mअगर.समयr);

			dev_dbg(&alg_data->adapter.dev,
				"%s(): Waking up xfer routine.\n",
				__func__);

			complete(&alg_data->mअगर.complete);
		पूर्ण
	पूर्ण अन्यथा अगर (alg_data->mअगर.len == 0) अणु
		/* zero-sized transfer */
		i2c_pnx_stop(alg_data);

		/* Disable master पूर्णांकerrupts. */
		ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) &
			~(mcntrl_afie | mcntrl_naie | mcntrl_drmie),
			  I2C_REG_CTL(alg_data));

		/* Stop समयr. */
		del_समयr_sync(&alg_data->mअगर.समयr);
		dev_dbg(&alg_data->adapter.dev,
			"%s(): Waking up xfer routine after zero-xfer.\n",
			__func__);

		complete(&alg_data->mअगर.complete);
	पूर्ण

	dev_dbg(&alg_data->adapter.dev, "%s(): exiting: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	वापस 0;
पूर्ण

/**
 * i2c_pnx_master_rcv - receive data from slave
 * @alg_data:		poपूर्णांकer to local driver data काष्ठाure
 *
 * Reads one byte data from the slave
 */
अटल पूर्णांक i2c_pnx_master_rcv(काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	अचिन्हित पूर्णांक val = 0;
	u32 ctl = 0;

	dev_dbg(&alg_data->adapter.dev, "%s(): entering: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	/* Check, whether there is alपढ़ोy data,
	 * or we didn't 'ask' क्रम it yet.
	 */
	अगर (ioपढ़ो32(I2C_REG_STS(alg_data)) & mstatus_rfe) अणु
		/* 'Asking' is करोne asynchronously, e.g. dummy TX of several
		 * bytes is करोne beक्रमe the first actual RX arrives in FIFO.
		 * Thereक्रमe, ordered bytes (via TX) are counted separately.
		 */
		अगर (alg_data->mअगर.order) अणु
			dev_dbg(&alg_data->adapter.dev,
				"%s(): Write dummy data to fill Rx-fifo...\n",
				__func__);

			अगर (alg_data->mअगर.order == 1) अणु
				/* Last byte, करो not acknowledge next rcv. */
				val |= stop_bit;

				/*
				 * Enable पूर्णांकerrupt RFDAIE (data in Rx fअगरo),
				 * and disable DRMIE (need data क्रम Tx)
				 */
				ctl = ioपढ़ो32(I2C_REG_CTL(alg_data));
				ctl |= mcntrl_rffie | mcntrl_daie;
				ctl &= ~mcntrl_drmie;
				ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));
			पूर्ण

			/*
			 * Now we'll 'ask' क्रम data:
			 * For each byte we want to receive, we must
			 * ग_लिखो a (dummy) byte to the Tx-FIFO.
			 */
			ioग_लिखो32(val, I2C_REG_TX(alg_data));
			alg_data->mअगर.order--;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Handle data. */
	अगर (alg_data->mअगर.len > 0) अणु
		val = ioपढ़ो32(I2C_REG_RX(alg_data));
		*alg_data->mअगर.buf++ = (u8) (val & 0xff);
		dev_dbg(&alg_data->adapter.dev, "%s(): rcv 0x%x [%d]\n",
			__func__, val, alg_data->mअगर.len);

		alg_data->mअगर.len--;
		अगर (alg_data->mअगर.len == 0) अणु
			अगर (alg_data->last)
				/* Wait until the STOP is seen. */
				अगर (रुको_समयout(alg_data))
					dev_err(&alg_data->adapter.dev,
						"The bus is still active after timeout\n");

			/* Disable master पूर्णांकerrupts */
			ctl = ioपढ़ो32(I2C_REG_CTL(alg_data));
			ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie |
				 mcntrl_drmie | mcntrl_daie);
			ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));

			/* Kill समयr. */
			del_समयr_sync(&alg_data->mअगर.समयr);
			complete(&alg_data->mअगर.complete);
		पूर्ण
	पूर्ण

	dev_dbg(&alg_data->adapter.dev, "%s(): exiting: stat = %04x.\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	वापस 0;
पूर्ण

अटल irqवापस_t i2c_pnx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_pnx_algo_data *alg_data = dev_id;
	u32 stat, ctl;

	dev_dbg(&alg_data->adapter.dev,
		"%s(): mstat = %x mctrl = %x, mode = %d\n",
		__func__,
		ioपढ़ो32(I2C_REG_STS(alg_data)),
		ioपढ़ो32(I2C_REG_CTL(alg_data)),
		alg_data->mअगर.mode);
	stat = ioपढ़ो32(I2C_REG_STS(alg_data));

	/* let's see what kind of event this is */
	अगर (stat & mstatus_afi) अणु
		/* We lost arbitration in the midst of a transfer */
		alg_data->mअगर.ret = -EIO;

		/* Disable master पूर्णांकerrupts. */
		ctl = ioपढ़ो32(I2C_REG_CTL(alg_data));
		ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie |
			 mcntrl_drmie);
		ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));

		/* Stop समयr, to prevent समयout. */
		del_समयr_sync(&alg_data->mअगर.समयr);
		complete(&alg_data->mअगर.complete);
	पूर्ण अन्यथा अगर (stat & mstatus_nai) अणु
		/* Slave did not acknowledge, generate a STOP */
		dev_dbg(&alg_data->adapter.dev,
			"%s(): Slave did not acknowledge, generating a STOP.\n",
			__func__);
		i2c_pnx_stop(alg_data);

		/* Disable master पूर्णांकerrupts. */
		ctl = ioपढ़ो32(I2C_REG_CTL(alg_data));
		ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie |
			 mcntrl_drmie);
		ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));

		/* Our वापस value. */
		alg_data->mअगर.ret = -EIO;

		/* Stop समयr, to prevent समयout. */
		del_समयr_sync(&alg_data->mअगर.समयr);
		complete(&alg_data->mअगर.complete);
	पूर्ण अन्यथा अणु
		/*
		 * Two options:
		 * - Master Tx needs data.
		 * - There is data in the Rx-fअगरo
		 * The latter is only the हाल अगर we have requested क्रम data,
		 * via a dummy ग_लिखो. (See 'i2c_pnx_master_rcv'.)
		 * We thereक्रमe check, as a sanity check, whether that पूर्णांकerrupt
		 * has been enabled.
		 */
		अगर ((stat & mstatus_drmi) || !(stat & mstatus_rfe)) अणु
			अगर (alg_data->mअगर.mode == I2C_SMBUS_WRITE) अणु
				i2c_pnx_master_xmit(alg_data);
			पूर्ण अन्यथा अगर (alg_data->mअगर.mode == I2C_SMBUS_READ) अणु
				i2c_pnx_master_rcv(alg_data);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Clear TDI and AFI bits */
	stat = ioपढ़ो32(I2C_REG_STS(alg_data));
	ioग_लिखो32(stat | mstatus_tdi | mstatus_afi, I2C_REG_STS(alg_data));

	dev_dbg(&alg_data->adapter.dev,
		"%s(): exiting, stat = %x ctrl = %x.\n",
		 __func__, ioपढ़ो32(I2C_REG_STS(alg_data)),
		 ioपढ़ो32(I2C_REG_CTL(alg_data)));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम i2c_pnx_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा i2c_pnx_algo_data *alg_data = from_समयr(alg_data, t, mअगर.समयr);
	u32 ctl;

	dev_err(&alg_data->adapter.dev,
		"Master timed out. stat = %04x, cntrl = %04x. Resetting master...\n",
		ioपढ़ो32(I2C_REG_STS(alg_data)),
		ioपढ़ो32(I2C_REG_CTL(alg_data)));

	/* Reset master and disable पूर्णांकerrupts */
	ctl = ioपढ़ो32(I2C_REG_CTL(alg_data));
	ctl &= ~(mcntrl_afie | mcntrl_naie | mcntrl_rffie | mcntrl_drmie);
	ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));

	ctl |= mcntrl_reset;
	ioग_लिखो32(ctl, I2C_REG_CTL(alg_data));
	रुको_reset(alg_data);
	alg_data->mअगर.ret = -EIO;
	complete(&alg_data->mअगर.complete);
पूर्ण

अटल अंतरभूत व्योम bus_reset_अगर_active(काष्ठा i2c_pnx_algo_data *alg_data)
अणु
	u32 stat;

	अगर ((stat = ioपढ़ो32(I2C_REG_STS(alg_data))) & mstatus_active) अणु
		dev_err(&alg_data->adapter.dev,
			"%s: Bus is still active after xfer. Reset it...\n",
			alg_data->adapter.name);
		ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		रुको_reset(alg_data);
	पूर्ण अन्यथा अगर (!(stat & mstatus_rfe) || !(stat & mstatus_tfe)) अणु
		/* If there is data in the fअगरo's after transfer,
		 * flush fअगरo's by reset.
		 */
		ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		रुको_reset(alg_data);
	पूर्ण अन्यथा अगर (stat & mstatus_nai) अणु
		ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) | mcntrl_reset,
			  I2C_REG_CTL(alg_data));
		रुको_reset(alg_data);
	पूर्ण
पूर्ण

/**
 * i2c_pnx_xfer - generic transfer entry poपूर्णांक
 * @adap:		poपूर्णांकer to I2C adapter काष्ठाure
 * @msgs:		array of messages
 * @num:		number of messages
 *
 * Initiates the transfer
 */
अटल पूर्णांक
i2c_pnx_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg *pmsg;
	पूर्णांक rc = 0, completed = 0, i;
	काष्ठा i2c_pnx_algo_data *alg_data = adap->algo_data;
	u32 stat;

	dev_dbg(&alg_data->adapter.dev,
		"%s(): entering: %d messages, stat = %04x.\n",
		__func__, num, ioपढ़ो32(I2C_REG_STS(alg_data)));

	bus_reset_अगर_active(alg_data);

	/* Process transactions in a loop. */
	क्रम (i = 0; rc >= 0 && i < num; i++) अणु
		u8 addr;

		pmsg = &msgs[i];
		addr = pmsg->addr;

		अगर (pmsg->flags & I2C_M_TEN) अणु
			dev_err(&alg_data->adapter.dev,
				"%s: 10 bits addr not supported!\n",
				alg_data->adapter.name);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		alg_data->mअगर.buf = pmsg->buf;
		alg_data->mअगर.len = pmsg->len;
		alg_data->mअगर.order = pmsg->len;
		alg_data->mअगर.mode = (pmsg->flags & I2C_M_RD) ?
			I2C_SMBUS_READ : I2C_SMBUS_WRITE;
		alg_data->mअगर.ret = 0;
		alg_data->last = (i == num - 1);

		dev_dbg(&alg_data->adapter.dev, "%s(): mode %d, %d bytes\n",
			__func__, alg_data->mअगर.mode, alg_data->mअगर.len);

		i2c_pnx_arm_समयr(alg_data);

		/* initialize the completion var */
		init_completion(&alg_data->mअगर.complete);

		/* Enable master पूर्णांकerrupt */
		ioग_लिखो32(ioपढ़ो32(I2C_REG_CTL(alg_data)) | mcntrl_afie |
				mcntrl_naie | mcntrl_drmie,
			  I2C_REG_CTL(alg_data));

		/* Put start-code and slave-address on the bus. */
		rc = i2c_pnx_start(addr, alg_data);
		अगर (rc < 0)
			अवरोध;

		/* Wait क्रम completion */
		रुको_क्रम_completion(&alg_data->mअगर.complete);

		अगर (!(rc = alg_data->mअगर.ret))
			completed++;
		dev_dbg(&alg_data->adapter.dev,
			"%s(): Complete, return code = %d.\n",
			__func__, rc);

		/* Clear TDI and AFI bits in हाल they are set. */
		अगर ((stat = ioपढ़ो32(I2C_REG_STS(alg_data))) & mstatus_tdi) अणु
			dev_dbg(&alg_data->adapter.dev,
				"%s: TDI still set... clearing now.\n",
				alg_data->adapter.name);
			ioग_लिखो32(stat, I2C_REG_STS(alg_data));
		पूर्ण
		अगर ((stat = ioपढ़ो32(I2C_REG_STS(alg_data))) & mstatus_afi) अणु
			dev_dbg(&alg_data->adapter.dev,
				"%s: AFI still set... clearing now.\n",
				alg_data->adapter.name);
			ioग_लिखो32(stat, I2C_REG_STS(alg_data));
		पूर्ण
	पूर्ण

	bus_reset_अगर_active(alg_data);

	/* Cleanup to be sure... */
	alg_data->mअगर.buf = शून्य;
	alg_data->mअगर.len = 0;
	alg_data->mअगर.order = 0;

	dev_dbg(&alg_data->adapter.dev, "%s(): exiting, stat = %x\n",
		__func__, ioपढ़ो32(I2C_REG_STS(alg_data)));

	अगर (completed != num)
		वापस ((rc < 0) ? rc : -EREMOTEIO);

	वापस num;
पूर्ण

अटल u32 i2c_pnx_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm pnx_algorithm = अणु
	.master_xfer = i2c_pnx_xfer,
	.functionality = i2c_pnx_func,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक i2c_pnx_controller_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_pnx_algo_data *alg_data = dev_get_drvdata(dev);

	clk_disable_unprepare(alg_data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pnx_controller_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_pnx_algo_data *alg_data = dev_get_drvdata(dev);

	वापस clk_prepare_enable(alg_data->clk);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(i2c_pnx_pm,
			 i2c_pnx_controller_suspend, i2c_pnx_controller_resume);
#घोषणा PNX_I2C_PM	(&i2c_pnx_pm)
#अन्यथा
#घोषणा PNX_I2C_PM	शून्य
#पूर्ण_अगर

अटल पूर्णांक i2c_pnx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret = 0;
	काष्ठा i2c_pnx_algo_data *alg_data;
	अचिन्हित दीर्घ freq;
	काष्ठा resource *res;
	u32 speed = I2C_PNX_SPEED_KHZ_DEFAULT * 1000;

	alg_data = devm_kzalloc(&pdev->dev, माप(*alg_data), GFP_KERNEL);
	अगर (!alg_data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, alg_data);

	alg_data->adapter.dev.parent = &pdev->dev;
	alg_data->adapter.algo = &pnx_algorithm;
	alg_data->adapter.algo_data = alg_data;
	alg_data->adapter.nr = pdev->id;

	alg_data->समयout = I2C_PNX_TIMEOUT_DEFAULT;
#अगर_घोषित CONFIG_OF
	alg_data->adapter.dev.of_node = of_node_get(pdev->dev.of_node);
	अगर (pdev->dev.of_node) अणु
		of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				     &speed);
		/*
		 * At this poपूर्णांक, it is planned to add an OF समयout property.
		 * As soon as there is a consensus about how to call and handle
		 * this, sth. like the following can be put here:
		 *
		 * of_property_पढ़ो_u32(pdev->dev.of_node, "timeout",
		 *                      &alg_data->समयout);
		 */
	पूर्ण
#पूर्ण_अगर
	alg_data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(alg_data->clk))
		वापस PTR_ERR(alg_data->clk);

	समयr_setup(&alg_data->mअगर.समयr, i2c_pnx_समयout, 0);

	snम_लिखो(alg_data->adapter.name, माप(alg_data->adapter.name),
		 "%s", pdev->name);

	/* Register I/O resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	alg_data->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(alg_data->ioaddr))
		वापस PTR_ERR(alg_data->ioaddr);

	ret = clk_prepare_enable(alg_data->clk);
	अगर (ret)
		वापस ret;

	freq = clk_get_rate(alg_data->clk);

	/*
	 * Clock Divisor High This value is the number of प्रणाली घड़ीs
	 * the serial घड़ी (SCL) will be high.
	 * For example, अगर the प्रणाली घड़ी period is 50 ns and the maximum
	 * desired serial period is 10000 ns (100 kHz), then CLKHI would be
	 * set to 0.5*(f_sys/f_i2c)-2=0.5*(20e6/100e3)-2=98. The actual value
	 * programmed पूर्णांकo CLKHI will vary from this slightly due to
	 * variations in the output pad's rise and fall बार as well as
	 * the deglitching filter length.
	 */

	पंचांगp = (freq / speed) / 2 - 2;
	अगर (पंचांगp > 0x3FF)
		पंचांगp = 0x3FF;
	ioग_लिखो32(पंचांगp, I2C_REG_CKH(alg_data));
	ioग_लिखो32(पंचांगp, I2C_REG_CKL(alg_data));

	ioग_लिखो32(mcntrl_reset, I2C_REG_CTL(alg_data));
	अगर (रुको_reset(alg_data)) अणु
		ret = -ENODEV;
		जाओ out_घड़ी;
	पूर्ण
	init_completion(&alg_data->mअगर.complete);

	alg_data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (alg_data->irq < 0) अणु
		ret = alg_data->irq;
		जाओ out_घड़ी;
	पूर्ण
	ret = devm_request_irq(&pdev->dev, alg_data->irq, i2c_pnx_पूर्णांकerrupt,
			       0, pdev->name, alg_data);
	अगर (ret)
		जाओ out_घड़ी;

	/* Register this adapter with the I2C subप्रणाली */
	ret = i2c_add_numbered_adapter(&alg_data->adapter);
	अगर (ret < 0)
		जाओ out_घड़ी;

	dev_dbg(&pdev->dev, "%s: Master at %pap, irq %d.\n",
		alg_data->adapter.name, &res->start, alg_data->irq);

	वापस 0;

out_घड़ी:
	clk_disable_unprepare(alg_data->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_pnx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_pnx_algo_data *alg_data = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&alg_data->adapter);
	clk_disable_unprepare(alg_data->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id i2c_pnx_of_match[] = अणु
	अणु .compatible = "nxp,pnx-i2c" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_pnx_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver i2c_pnx_driver = अणु
	.driver = अणु
		.name = "pnx-i2c",
		.of_match_table = of_match_ptr(i2c_pnx_of_match),
		.pm = PNX_I2C_PM,
	पूर्ण,
	.probe = i2c_pnx_probe,
	.हटाओ = i2c_pnx_हटाओ,
पूर्ण;

अटल पूर्णांक __init i2c_adap_pnx_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&i2c_pnx_driver);
पूर्ण

अटल व्योम __निकास i2c_adap_pnx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&i2c_pnx_driver);
पूर्ण

MODULE_AUTHOR("Vitaly Wool");
MODULE_AUTHOR("Dennis Kovalev <source@mvista.com>");
MODULE_DESCRIPTION("I2C driver for Philips IP3204-based I2C busses");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pnx-i2c");

/* We need to make sure I2C is initialized beक्रमe USB */
subsys_initcall(i2c_adap_pnx_init);
module_निकास(i2c_adap_pnx_निकास);
