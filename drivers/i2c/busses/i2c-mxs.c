<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale MXS I2C bus driver
 *
 * Copyright (C) 2012-2013 Marek Vasut <marex@denx.de>
 * Copyright (C) 2011-2012 Wolfram Sang, Pengutronix e.K.
 *
 * based on a (non-working) driver which was:
 *
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/mxs-dma.h>

#घोषणा DRIVER_NAME "mxs-i2c"

#घोषणा MXS_I2C_CTRL0		(0x00)
#घोषणा MXS_I2C_CTRL0_SET	(0x04)
#घोषणा MXS_I2C_CTRL0_CLR	(0x08)

#घोषणा MXS_I2C_CTRL0_SFTRST			0x80000000
#घोषणा MXS_I2C_CTRL0_RUN			0x20000000
#घोषणा MXS_I2C_CTRL0_SEND_NAK_ON_LAST		0x02000000
#घोषणा MXS_I2C_CTRL0_PIO_MODE			0x01000000
#घोषणा MXS_I2C_CTRL0_RETAIN_CLOCK		0x00200000
#घोषणा MXS_I2C_CTRL0_POST_SEND_STOP		0x00100000
#घोषणा MXS_I2C_CTRL0_PRE_SEND_START		0x00080000
#घोषणा MXS_I2C_CTRL0_MASTER_MODE		0x00020000
#घोषणा MXS_I2C_CTRL0_सूचीECTION			0x00010000
#घोषणा MXS_I2C_CTRL0_XFER_COUNT(v)		((v) & 0x0000FFFF)

#घोषणा MXS_I2C_TIMING0		(0x10)
#घोषणा MXS_I2C_TIMING1		(0x20)
#घोषणा MXS_I2C_TIMING2		(0x30)

#घोषणा MXS_I2C_CTRL1		(0x40)
#घोषणा MXS_I2C_CTRL1_SET	(0x44)
#घोषणा MXS_I2C_CTRL1_CLR	(0x48)

#घोषणा MXS_I2C_CTRL1_CLR_GOT_A_NAK		0x10000000
#घोषणा MXS_I2C_CTRL1_BUS_FREE_IRQ		0x80
#घोषणा MXS_I2C_CTRL1_DATA_ENGINE_CMPLT_IRQ	0x40
#घोषणा MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ		0x20
#घोषणा MXS_I2C_CTRL1_OVERSIZE_XFER_TERM_IRQ	0x10
#घोषणा MXS_I2C_CTRL1_EARLY_TERM_IRQ		0x08
#घोषणा MXS_I2C_CTRL1_MASTER_LOSS_IRQ		0x04
#घोषणा MXS_I2C_CTRL1_SLAVE_STOP_IRQ		0x02
#घोषणा MXS_I2C_CTRL1_SLAVE_IRQ			0x01

#घोषणा MXS_I2C_STAT		(0x50)
#घोषणा MXS_I2C_STAT_GOT_A_NAK			0x10000000
#घोषणा MXS_I2C_STAT_BUS_BUSY			0x00000800
#घोषणा MXS_I2C_STAT_CLK_GEN_BUSY		0x00000400

#घोषणा MXS_I2C_DATA(i2c)	((i2c->dev_type == MXS_I2C_V1) ? 0x60 : 0xa0)

#घोषणा MXS_I2C_DEBUG0_CLR(i2c)	((i2c->dev_type == MXS_I2C_V1) ? 0x78 : 0xb8)

#घोषणा MXS_I2C_DEBUG0_DMAREQ	0x80000000

#घोषणा MXS_I2C_IRQ_MASK	(MXS_I2C_CTRL1_DATA_ENGINE_CMPLT_IRQ | \
				 MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ | \
				 MXS_I2C_CTRL1_EARLY_TERM_IRQ | \
				 MXS_I2C_CTRL1_MASTER_LOSS_IRQ | \
				 MXS_I2C_CTRL1_SLAVE_STOP_IRQ | \
				 MXS_I2C_CTRL1_SLAVE_IRQ)


#घोषणा MXS_CMD_I2C_SELECT	(MXS_I2C_CTRL0_RETAIN_CLOCK |	\
				 MXS_I2C_CTRL0_PRE_SEND_START |	\
				 MXS_I2C_CTRL0_MASTER_MODE |	\
				 MXS_I2C_CTRL0_सूचीECTION |	\
				 MXS_I2C_CTRL0_XFER_COUNT(1))

#घोषणा MXS_CMD_I2C_WRITE	(MXS_I2C_CTRL0_PRE_SEND_START |	\
				 MXS_I2C_CTRL0_MASTER_MODE |	\
				 MXS_I2C_CTRL0_सूचीECTION)

#घोषणा MXS_CMD_I2C_READ	(MXS_I2C_CTRL0_SEND_NAK_ON_LAST | \
				 MXS_I2C_CTRL0_MASTER_MODE)

क्रमागत mxs_i2c_devtype अणु
	MXS_I2C_UNKNOWN = 0,
	MXS_I2C_V1,
	MXS_I2C_V2,
पूर्ण;

/**
 * काष्ठा mxs_i2c_dev - per device, निजी MXS-I2C data
 *
 * @dev: driver model device node
 * @dev_type: distinguish i.MX23/i.MX28 features
 * @regs: IO रेजिस्टरs poपूर्णांकer
 * @cmd_complete: completion object क्रम transaction रुको
 * @cmd_err: error code क्रम last transaction
 * @adapter: i2c subप्रणाली adapter node
 */
काष्ठा mxs_i2c_dev अणु
	काष्ठा device *dev;
	क्रमागत mxs_i2c_devtype dev_type;
	व्योम __iomem *regs;
	काष्ठा completion cmd_complete;
	पूर्णांक cmd_err;
	काष्ठा i2c_adapter adapter;

	uपूर्णांक32_t timing0;
	uपूर्णांक32_t timing1;
	uपूर्णांक32_t timing2;

	/* DMA support components */
	काष्ठा dma_chan			*dmach;
	uपूर्णांक32_t			pio_data[2];
	uपूर्णांक32_t			addr_data;
	काष्ठा scatterlist		sg_io[2];
	bool				dma_पढ़ो;
पूर्ण;

अटल पूर्णांक mxs_i2c_reset(काष्ठा mxs_i2c_dev *i2c)
अणु
	पूर्णांक ret = sपंचांगp_reset_block(i2c->regs);
	अगर (ret)
		वापस ret;

	/*
	 * Configure timing क्रम the I2C block. The I2C TIMING2 रेजिस्टर has to
	 * be programmed with this particular magic number. The rest is derived
	 * from the XTAL speed and requested I2C speed.
	 *
	 * For details, see i.MX233 [25.4.2 - 25.4.4] and i.MX28 [27.5.2 - 27.5.4].
	 */
	ग_लिखोl(i2c->timing0, i2c->regs + MXS_I2C_TIMING0);
	ग_लिखोl(i2c->timing1, i2c->regs + MXS_I2C_TIMING1);
	ग_लिखोl(i2c->timing2, i2c->regs + MXS_I2C_TIMING2);

	ग_लिखोl(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_SET);

	वापस 0;
पूर्ण

अटल व्योम mxs_i2c_dma_finish(काष्ठा mxs_i2c_dev *i2c)
अणु
	अगर (i2c->dma_पढ़ो) अणु
		dma_unmap_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
		dma_unmap_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम mxs_i2c_dma_irq_callback(व्योम *param)
अणु
	काष्ठा mxs_i2c_dev *i2c = param;

	complete(&i2c->cmd_complete);
	mxs_i2c_dma_finish(i2c);
पूर्ण

अटल पूर्णांक mxs_i2c_dma_setup_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg *msg, uपूर्णांक32_t flags)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा mxs_i2c_dev *i2c = i2c_get_adapdata(adap);

	i2c->addr_data = i2c_8bit_addr_from_msg(msg);

	अगर (msg->flags & I2C_M_RD) अणु
		i2c->dma_पढ़ो = true;

		/*
		 * SELECT command.
		 */

		/* Queue the PIO रेजिस्टर ग_लिखो transfer. */
		i2c->pio_data[0] = MXS_CMD_I2C_SELECT;
		desc = dmaengine_prep_slave_sg(i2c->dmach,
					(काष्ठा scatterlist *)&i2c->pio_data[0],
					1, DMA_TRANS_NONE, 0);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get PIO reg. write descriptor.\n");
			जाओ select_init_pio_fail;
		पूर्ण

		/* Queue the DMA data transfer. */
		sg_init_one(&i2c->sg_io[0], &i2c->addr_data, 1);
		dma_map_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
		desc = dmaengine_prep_slave_sg(i2c->dmach, &i2c->sg_io[0], 1,
					DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT |
					MXS_DMA_CTRL_WAIT4END);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get DMA data write descriptor.\n");
			जाओ select_init_dma_fail;
		पूर्ण

		/*
		 * READ command.
		 */

		/* Queue the PIO रेजिस्टर ग_लिखो transfer. */
		i2c->pio_data[1] = flags | MXS_CMD_I2C_READ |
				MXS_I2C_CTRL0_XFER_COUNT(msg->len);
		desc = dmaengine_prep_slave_sg(i2c->dmach,
					(काष्ठा scatterlist *)&i2c->pio_data[1],
					1, DMA_TRANS_NONE, DMA_PREP_INTERRUPT);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get PIO reg. write descriptor.\n");
			जाओ select_init_dma_fail;
		पूर्ण

		/* Queue the DMA data transfer. */
		sg_init_one(&i2c->sg_io[1], msg->buf, msg->len);
		dma_map_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FROM_DEVICE);
		desc = dmaengine_prep_slave_sg(i2c->dmach, &i2c->sg_io[1], 1,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT |
					MXS_DMA_CTRL_WAIT4END);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get DMA data write descriptor.\n");
			जाओ पढ़ो_init_dma_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		i2c->dma_पढ़ो = false;

		/*
		 * WRITE command.
		 */

		/* Queue the PIO रेजिस्टर ग_लिखो transfer. */
		i2c->pio_data[0] = flags | MXS_CMD_I2C_WRITE |
				MXS_I2C_CTRL0_XFER_COUNT(msg->len + 1);
		desc = dmaengine_prep_slave_sg(i2c->dmach,
					(काष्ठा scatterlist *)&i2c->pio_data[0],
					1, DMA_TRANS_NONE, 0);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get PIO reg. write descriptor.\n");
			जाओ ग_लिखो_init_pio_fail;
		पूर्ण

		/* Queue the DMA data transfer. */
		sg_init_table(i2c->sg_io, 2);
		sg_set_buf(&i2c->sg_io[0], &i2c->addr_data, 1);
		sg_set_buf(&i2c->sg_io[1], msg->buf, msg->len);
		dma_map_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
		desc = dmaengine_prep_slave_sg(i2c->dmach, i2c->sg_io, 2,
					DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT |
					MXS_DMA_CTRL_WAIT4END);
		अगर (!desc) अणु
			dev_err(i2c->dev,
				"Failed to get DMA data write descriptor.\n");
			जाओ ग_लिखो_init_dma_fail;
		पूर्ण
	पूर्ण

	/*
	 * The last descriptor must have this callback,
	 * to finish the DMA transaction.
	 */
	desc->callback = mxs_i2c_dma_irq_callback;
	desc->callback_param = i2c;

	/* Start the transfer. */
	dmaengine_submit(desc);
	dma_async_issue_pending(i2c->dmach);
	वापस 0;

/* Read failpath. */
पढ़ो_init_dma_fail:
	dma_unmap_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FROM_DEVICE);
select_init_dma_fail:
	dma_unmap_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
select_init_pio_fail:
	dmaengine_terminate_all(i2c->dmach);
	वापस -EINVAL;

/* Write failpath. */
ग_लिखो_init_dma_fail:
	dma_unmap_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
ग_लिखो_init_pio_fail:
	dmaengine_terminate_all(i2c->dmach);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mxs_i2c_pio_रुको_xfer_end(काष्ठा mxs_i2c_dev *i2c)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	जबतक (पढ़ोl(i2c->regs + MXS_I2C_CTRL0) & MXS_I2C_CTRL0_RUN) अणु
		अगर (पढ़ोl(i2c->regs + MXS_I2C_CTRL1) &
				MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ)
			वापस -ENXIO;
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_i2c_pio_check_error_state(काष्ठा mxs_i2c_dev *i2c)
अणु
	u32 state;

	state = पढ़ोl(i2c->regs + MXS_I2C_CTRL1_CLR) & MXS_I2C_IRQ_MASK;

	अगर (state & MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ)
		i2c->cmd_err = -ENXIO;
	अन्यथा अगर (state & (MXS_I2C_CTRL1_EARLY_TERM_IRQ |
			  MXS_I2C_CTRL1_MASTER_LOSS_IRQ |
			  MXS_I2C_CTRL1_SLAVE_STOP_IRQ |
			  MXS_I2C_CTRL1_SLAVE_IRQ))
		i2c->cmd_err = -EIO;

	वापस i2c->cmd_err;
पूर्ण

अटल व्योम mxs_i2c_pio_trigger_cmd(काष्ठा mxs_i2c_dev *i2c, u32 cmd)
अणु
	u32 reg;

	ग_लिखोl(cmd, i2c->regs + MXS_I2C_CTRL0);

	/* पढ़ोback makes sure the ग_लिखो is latched पूर्णांकo hardware */
	reg = पढ़ोl(i2c->regs + MXS_I2C_CTRL0);
	reg |= MXS_I2C_CTRL0_RUN;
	ग_लिखोl(reg, i2c->regs + MXS_I2C_CTRL0);
पूर्ण

/*
 * Start WRITE transaction on the I2C bus. By studying i.MX23 datasheet,
 * CTRL0::PIO_MODE bit description clarअगरies the order in which the रेजिस्टरs
 * must be written during PIO mode operation. First, the CTRL0 रेजिस्टर has
 * to be programmed with all the necessary bits but the RUN bit. Then the
 * payload has to be written पूर्णांकo the DATA रेजिस्टर. Finally, the transmission
 * is executed by setting the RUN bit in CTRL0.
 */
अटल व्योम mxs_i2c_pio_trigger_ग_लिखो_cmd(काष्ठा mxs_i2c_dev *i2c, u32 cmd,
					  u32 data)
अणु
	ग_लिखोl(cmd, i2c->regs + MXS_I2C_CTRL0);

	अगर (i2c->dev_type == MXS_I2C_V1)
		ग_लिखोl(MXS_I2C_CTRL0_PIO_MODE, i2c->regs + MXS_I2C_CTRL0_SET);

	ग_लिखोl(data, i2c->regs + MXS_I2C_DATA(i2c));
	ग_लिखोl(MXS_I2C_CTRL0_RUN, i2c->regs + MXS_I2C_CTRL0_SET);
पूर्ण

अटल पूर्णांक mxs_i2c_pio_setup_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg *msg, uपूर्णांक32_t flags)
अणु
	काष्ठा mxs_i2c_dev *i2c = i2c_get_adapdata(adap);
	uपूर्णांक32_t addr_data = i2c_8bit_addr_from_msg(msg);
	uपूर्णांक32_t data = 0;
	पूर्णांक i, ret, xlen = 0, xmit = 0;
	uपूर्णांक32_t start;

	/* Mute IRQs coming from this block. */
	ग_लिखोl(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_CLR);

	/*
	 * MX23 idea:
	 * - Enable CTRL0::PIO_MODE (1 << 24)
	 * - Enable CTRL1::ACK_MODE (1 << 27)
	 *
	 * WARNING! The MX23 is broken in some way, even अगर it claims
	 * to support PIO, when we try to transfer any amount of data
	 * that is not aligned to 4 bytes, the DMA engine will have
	 * bits in DEBUG1::DMA_BYTES_ENABLES still set even after the
	 * transfer. This in turn will mess up the next transfer as
	 * the block it emit one byte ग_लिखो onto the bus terminated
	 * with a NAK+STOP. A possible workaround is to reset the IP
	 * block after every PIO transmission, which might just work.
	 *
	 * NOTE: The CTRL0::PIO_MODE description is important, since
	 * it outlines how the PIO mode is really supposed to work.
	 */
	अगर (msg->flags & I2C_M_RD) अणु
		/*
		 * PIO READ transfer:
		 *
		 * This transfer MUST be limited to 4 bytes maximum. It is not
		 * possible to transfer more than four bytes via PIO, since we
		 * can not in any way make sure we can पढ़ो the data from the
		 * DATA रेजिस्टर fast enough. Besides, the RX FIFO is only four
		 * bytes deep, thus we can only really पढ़ो up to four bytes at
		 * समय. Finally, there is no bit indicating us that new data
		 * arrived at the FIFO and can thus be fetched from the DATA
		 * रेजिस्टर.
		 */
		BUG_ON(msg->len > 4);

		/* SELECT command. */
		mxs_i2c_pio_trigger_ग_लिखो_cmd(i2c, MXS_CMD_I2C_SELECT,
					      addr_data);

		ret = mxs_i2c_pio_रुको_xfer_end(i2c);
		अगर (ret) अणु
			dev_dbg(i2c->dev,
				"PIO: Failed to send SELECT command!\n");
			जाओ cleanup;
		पूर्ण

		/* READ command. */
		mxs_i2c_pio_trigger_cmd(i2c,
					MXS_CMD_I2C_READ | flags |
					MXS_I2C_CTRL0_XFER_COUNT(msg->len));

		ret = mxs_i2c_pio_रुको_xfer_end(i2c);
		अगर (ret) अणु
			dev_dbg(i2c->dev,
				"PIO: Failed to send READ command!\n");
			जाओ cleanup;
		पूर्ण

		data = पढ़ोl(i2c->regs + MXS_I2C_DATA(i2c));
		क्रम (i = 0; i < msg->len; i++) अणु
			msg->buf[i] = data & 0xff;
			data >>= 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * PIO WRITE transfer:
		 *
		 * The code below implements घड़ी stretching to circumvent
		 * the possibility of kernel not being able to supply data
		 * fast enough. It is possible to transfer arbitrary amount
		 * of data using PIO ग_लिखो.
		 */

		/*
		 * The LSB of data buffer is the first byte blasted across
		 * the bus. Higher order bytes follow. Thus the following
		 * filling schematic.
		 */

		data = addr_data << 24;

		/* Start the transfer with START condition. */
		start = MXS_I2C_CTRL0_PRE_SEND_START;

		/* If the transfer is दीर्घ, use घड़ी stretching. */
		अगर (msg->len > 3)
			start |= MXS_I2C_CTRL0_RETAIN_CLOCK;

		क्रम (i = 0; i < msg->len; i++) अणु
			data >>= 8;
			data |= (msg->buf[i] << 24);

			xmit = 0;

			/* This is the last transfer of the message. */
			अगर (i + 1 == msg->len) अणु
				/* Add optional STOP flag. */
				start |= flags;
				/* Remove RETAIN_CLOCK bit. */
				start &= ~MXS_I2C_CTRL0_RETAIN_CLOCK;
				xmit = 1;
			पूर्ण

			/* Four bytes are पढ़ोy in the "data" variable. */
			अगर ((i & 3) == 2)
				xmit = 1;

			/* Nothing पूर्णांकeresting happened, जारी stuffing. */
			अगर (!xmit)
				जारी;

			/*
			 * Compute the size of the transfer and shअगरt the
			 * data accordingly.
			 *
			 * i = (4k + 0) .... xlen = 2
			 * i = (4k + 1) .... xlen = 3
			 * i = (4k + 2) .... xlen = 4
			 * i = (4k + 3) .... xlen = 1
			 */

			अगर ((i % 4) == 3)
				xlen = 1;
			अन्यथा
				xlen = (i % 4) + 2;

			data >>= (4 - xlen) * 8;

			dev_dbg(i2c->dev,
				"PIO: len=%i pos=%i total=%i [W%s%s%s]\n",
				xlen, i, msg->len,
				start & MXS_I2C_CTRL0_PRE_SEND_START ? "S" : "",
				start & MXS_I2C_CTRL0_POST_SEND_STOP ? "E" : "",
				start & MXS_I2C_CTRL0_RETAIN_CLOCK ? "C" : "");

			ग_लिखोl(MXS_I2C_DEBUG0_DMAREQ,
			       i2c->regs + MXS_I2C_DEBUG0_CLR(i2c));

			mxs_i2c_pio_trigger_ग_लिखो_cmd(i2c,
				start | MXS_I2C_CTRL0_MASTER_MODE |
				MXS_I2C_CTRL0_सूचीECTION |
				MXS_I2C_CTRL0_XFER_COUNT(xlen), data);

			/* The START condition is sent only once. */
			start &= ~MXS_I2C_CTRL0_PRE_SEND_START;

			/* Wait क्रम the end of the transfer. */
			ret = mxs_i2c_pio_रुको_xfer_end(i2c);
			अगर (ret) अणु
				dev_dbg(i2c->dev,
					"PIO: Failed to finish WRITE cmd!\n");
				अवरोध;
			पूर्ण

			/* Check NAK here. */
			ret = पढ़ोl(i2c->regs + MXS_I2C_STAT) &
				    MXS_I2C_STAT_GOT_A_NAK;
			अगर (ret) अणु
				ret = -ENXIO;
				जाओ cleanup;
			पूर्ण
		पूर्ण
	पूर्ण

	/* make sure we capture any occurred error पूर्णांकo cmd_err */
	ret = mxs_i2c_pio_check_error_state(i2c);

cleanup:
	/* Clear any dangling IRQs and re-enable पूर्णांकerrupts. */
	ग_लिखोl(MXS_I2C_IRQ_MASK, i2c->regs + MXS_I2C_CTRL1_CLR);
	ग_लिखोl(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_SET);

	/* Clear the PIO_MODE on i.MX23 */
	अगर (i2c->dev_type == MXS_I2C_V1)
		ग_लिखोl(MXS_I2C_CTRL0_PIO_MODE, i2c->regs + MXS_I2C_CTRL0_CLR);

	वापस ret;
पूर्ण

/*
 * Low level master पढ़ो/ग_लिखो transaction.
 */
अटल पूर्णांक mxs_i2c_xfer_msg(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
				पूर्णांक stop)
अणु
	काष्ठा mxs_i2c_dev *i2c = i2c_get_adapdata(adap);
	पूर्णांक ret;
	पूर्णांक flags;
	पूर्णांक use_pio = 0;
	अचिन्हित दीर्घ समय_left;

	flags = stop ? MXS_I2C_CTRL0_POST_SEND_STOP : 0;

	dev_dbg(i2c->dev, "addr: 0x%04x, len: %d, flags: 0x%x, stop: %d\n",
		msg->addr, msg->len, msg->flags, stop);

	/*
	 * The MX28 I2C IP block can only करो PIO READ क्रम transfer of to up
	 * 4 bytes of length. The ग_लिखो transfer is not limited as it can use
	 * घड़ी stretching to aव्योम FIFO underruns.
	 */
	अगर ((msg->flags & I2C_M_RD) && (msg->len <= 4))
		use_pio = 1;
	अगर (!(msg->flags & I2C_M_RD) && (msg->len < 7))
		use_pio = 1;

	i2c->cmd_err = 0;
	अगर (use_pio) अणु
		ret = mxs_i2c_pio_setup_xfer(adap, msg, flags);
		/* No need to reset the block अगर NAK was received. */
		अगर (ret && (ret != -ENXIO))
			mxs_i2c_reset(i2c);
	पूर्ण अन्यथा अणु
		reinit_completion(&i2c->cmd_complete);
		ret = mxs_i2c_dma_setup_xfer(adap, msg, flags);
		अगर (ret)
			वापस ret;

		समय_left = रुको_क्रम_completion_समयout(&i2c->cmd_complete,
						msecs_to_jअगरfies(1000));
		अगर (!समय_left)
			जाओ समयout;

		ret = i2c->cmd_err;
	पूर्ण

	अगर (ret == -ENXIO) अणु
		/*
		 * If the transfer fails with a NAK from the slave the
		 * controller halts until it माला_लो told to वापस to idle state.
		 */
		ग_लिखोl(MXS_I2C_CTRL1_CLR_GOT_A_NAK,
		       i2c->regs + MXS_I2C_CTRL1_SET);
	पूर्ण

	/*
	 * WARNING!
	 * The i.MX23 is strange. After each and every operation, it's I2C IP
	 * block must be reset, otherwise the IP block will misbehave. This can
	 * be observed on the bus by the block sending out one single byte onto
	 * the bus. In हाल such an error happens, bit 27 will be set in the
	 * DEBUG0 रेजिस्टर. This bit is not करोcumented in the i.MX23 datasheet
	 * and is marked as "TBD" instead. To reset this bit to a correct state,
	 * reset the whole block. Since the block reset करोes not take दीर्घ, करो
	 * reset the block after every transfer to play safe.
	 */
	अगर (i2c->dev_type == MXS_I2C_V1)
		mxs_i2c_reset(i2c);

	dev_dbg(i2c->dev, "Done with err=%d\n", ret);

	वापस ret;

समयout:
	dev_dbg(i2c->dev, "Timeout!\n");
	mxs_i2c_dma_finish(i2c);
	ret = mxs_i2c_reset(i2c);
	अगर (ret)
		वापस ret;

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक mxs_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[],
			पूर्णांक num)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < num; i++) अणु
		err = mxs_i2c_xfer_msg(adap, &msgs[i], i == (num - 1));
		अगर (err)
			वापस err;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 mxs_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल irqवापस_t mxs_i2c_isr(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा mxs_i2c_dev *i2c = dev_id;
	u32 stat = पढ़ोl(i2c->regs + MXS_I2C_CTRL1) & MXS_I2C_IRQ_MASK;

	अगर (!stat)
		वापस IRQ_NONE;

	अगर (stat & MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ)
		i2c->cmd_err = -ENXIO;
	अन्यथा अगर (stat & (MXS_I2C_CTRL1_EARLY_TERM_IRQ |
		    MXS_I2C_CTRL1_MASTER_LOSS_IRQ |
		    MXS_I2C_CTRL1_SLAVE_STOP_IRQ | MXS_I2C_CTRL1_SLAVE_IRQ))
		/* MXS_I2C_CTRL1_OVERSIZE_XFER_TERM_IRQ is only क्रम slaves */
		i2c->cmd_err = -EIO;

	ग_लिखोl(stat, i2c->regs + MXS_I2C_CTRL1_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mxs_i2c_algo = अणु
	.master_xfer = mxs_i2c_xfer,
	.functionality = mxs_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mxs_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल व्योम mxs_i2c_derive_timing(काष्ठा mxs_i2c_dev *i2c, uपूर्णांक32_t speed)
अणु
	/* The I2C block घड़ी runs at 24MHz */
	स्थिर uपूर्णांक32_t clk = 24000000;
	uपूर्णांक32_t भागider;
	uपूर्णांक16_t high_count, low_count, rcv_count, xmit_count;
	uपूर्णांक32_t bus_मुक्त, leadin;
	काष्ठा device *dev = i2c->dev;

	भागider = DIV_ROUND_UP(clk, speed);

	अगर (भागider < 25) अणु
		/*
		 * limit the भागider, so that min(low_count, high_count)
		 * is >= 1
		 */
		भागider = 25;
		dev_warn(dev,
			"Speed too high (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			clk / भागider / 1000, clk / भागider % 1000);
	पूर्ण अन्यथा अगर (भागider > 1897) अणु
		/*
		 * limit the भागider, so that max(low_count, high_count)
		 * cannot exceed 1023
		 */
		भागider = 1897;
		dev_warn(dev,
			"Speed too low (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			clk / भागider / 1000, clk / भागider % 1000);
	पूर्ण

	/*
	 * The I2C spec specअगरies the following timing data:
	 *                          standard mode  fast mode Bitfield name
	 * tLOW (SCL LOW period)     4700 ns        1300 ns
	 * tHIGH (SCL HIGH period)   4000 ns         600 ns
	 * tSU;DAT (data setup समय)  250 ns         100 ns
	 * tHD;STA (START hold समय) 4000 ns         600 ns
	 * tBUF (bus मुक्त समय)      4700 ns        1300 ns
	 *
	 * The hardware (of the i.MX28 at least) seems to add 2 additional
	 * घड़ी cycles to the low_count and 7 cycles to the high_count.
	 * This is compensated क्रम by subtracting the respective स्थिरants
	 * from the values written to the timing रेजिस्टरs.
	 */
	अगर (speed > I2C_MAX_STANDARD_MODE_FREQ) अणु
		/* fast mode */
		low_count = DIV_ROUND_CLOSEST(भागider * 13, (13 + 6));
		high_count = DIV_ROUND_CLOSEST(भागider * 6, (13 + 6));
		leadin = DIV_ROUND_UP(600 * (clk / 1000000), 1000);
		bus_मुक्त = DIV_ROUND_UP(1300 * (clk / 1000000), 1000);
	पूर्ण अन्यथा अणु
		/* normal mode */
		low_count = DIV_ROUND_CLOSEST(भागider * 47, (47 + 40));
		high_count = DIV_ROUND_CLOSEST(भागider * 40, (47 + 40));
		leadin = DIV_ROUND_UP(4700 * (clk / 1000000), 1000);
		bus_मुक्त = DIV_ROUND_UP(4700 * (clk / 1000000), 1000);
	पूर्ण
	rcv_count = high_count * 3 / 8;
	xmit_count = low_count * 3 / 8;

	dev_dbg(dev,
		"speed=%u(actual %u) divider=%u low=%u high=%u xmit=%u rcv=%u leadin=%u bus_free=%u\n",
		speed, clk / भागider, भागider, low_count, high_count,
		xmit_count, rcv_count, leadin, bus_मुक्त);

	low_count -= 2;
	high_count -= 7;
	i2c->timing0 = (high_count << 16) | rcv_count;
	i2c->timing1 = (low_count << 16) | xmit_count;
	i2c->timing2 = (bus_मुक्त << 16 | leadin);
पूर्ण

अटल पूर्णांक mxs_i2c_get_ofdata(काष्ठा mxs_i2c_dev *i2c)
अणु
	uपूर्णांक32_t speed;
	काष्ठा device *dev = i2c->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "clock-frequency", &speed);
	अगर (ret) अणु
		dev_warn(dev, "No I2C speed selected, using 100kHz\n");
		speed = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण

	mxs_i2c_derive_timing(i2c, speed);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_i2c_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-i2c", .data = (व्योम *)MXS_I2C_V1, पूर्ण,
	अणु .compatible = "fsl,imx28-i2c", .data = (व्योम *)MXS_I2C_V2, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_i2c_dt_ids);

अटल पूर्णांक mxs_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mxs_i2c_dev *i2c;
	काष्ठा i2c_adapter *adap;
	पूर्णांक err, irq;

	i2c = devm_kzalloc(dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->dev_type = (क्रमागत mxs_i2c_devtype)of_device_get_match_data(&pdev->dev);

	i2c->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->regs))
		वापस PTR_ERR(i2c->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(dev, irq, mxs_i2c_isr, 0, dev_name(dev), i2c);
	अगर (err)
		वापस err;

	i2c->dev = dev;

	init_completion(&i2c->cmd_complete);

	अगर (dev->of_node) अणु
		err = mxs_i2c_get_ofdata(i2c);
		अगर (err)
			वापस err;
	पूर्ण

	/* Setup the DMA */
	i2c->dmach = dma_request_chan(dev, "rx-tx");
	अगर (IS_ERR(i2c->dmach)) अणु
		dev_err(dev, "Failed to request dma\n");
		वापस PTR_ERR(i2c->dmach);
	पूर्ण

	platक्रमm_set_drvdata(pdev, i2c);

	/* Do reset to enक्रमce correct startup after pinmuxing */
	err = mxs_i2c_reset(i2c);
	अगर (err)
		वापस err;

	adap = &i2c->adapter;
	strlcpy(adap->name, "MXS I2C adapter", माप(adap->name));
	adap->owner = THIS_MODULE;
	adap->algo = &mxs_i2c_algo;
	adap->quirks = &mxs_i2c_quirks;
	adap->dev.parent = dev;
	adap->nr = pdev->id;
	adap->dev.of_node = pdev->dev.of_node;
	i2c_set_adapdata(adap, i2c);
	err = i2c_add_numbered_adapter(adap);
	अगर (err) अणु
		ग_लिखोl(MXS_I2C_CTRL0_SFTRST,
				i2c->regs + MXS_I2C_CTRL0_SET);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_i2c_dev *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adapter);

	अगर (i2c->dmach)
		dma_release_channel(i2c->dmach);

	ग_लिखोl(MXS_I2C_CTRL0_SFTRST, i2c->regs + MXS_I2C_CTRL0_SET);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_i2c_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = mxs_i2c_dt_ids,
		   पूर्ण,
	.probe = mxs_i2c_probe,
	.हटाओ = mxs_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init mxs_i2c_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mxs_i2c_driver);
पूर्ण
subsys_initcall(mxs_i2c_init);

अटल व्योम __निकास mxs_i2c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mxs_i2c_driver);
पूर्ण
module_निकास(mxs_i2c_निकास);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("MXS I2C Bus Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
