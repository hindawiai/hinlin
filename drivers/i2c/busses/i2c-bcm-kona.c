<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

/* Hardware रेजिस्टर offsets and field defपूर्णांकions */
#घोषणा CS_OFFSET				0x00000020
#घोषणा CS_ACK_SHIFT				3
#घोषणा CS_ACK_MASK				0x00000008
#घोषणा CS_ACK_CMD_GEN_START			0x00000000
#घोषणा CS_ACK_CMD_GEN_RESTART			0x00000001
#घोषणा CS_CMD_SHIFT				1
#घोषणा CS_CMD_CMD_NO_ACTION			0x00000000
#घोषणा CS_CMD_CMD_START_RESTART		0x00000001
#घोषणा CS_CMD_CMD_STOP				0x00000002
#घोषणा CS_EN_SHIFT				0
#घोषणा CS_EN_CMD_ENABLE_BSC			0x00000001

#घोषणा TIM_OFFSET				0x00000024
#घोषणा TIM_PRESCALE_SHIFT			6
#घोषणा TIM_P_SHIFT				3
#घोषणा TIM_NO_DIV_SHIFT			2
#घोषणा TIM_DIV_SHIFT				0

#घोषणा DAT_OFFSET				0x00000028

#घोषणा TOUT_OFFSET				0x0000002c

#घोषणा TXFCR_OFFSET				0x0000003c
#घोषणा TXFCR_FIFO_FLUSH_MASK			0x00000080
#घोषणा TXFCR_FIFO_EN_MASK			0x00000040

#घोषणा IER_OFFSET				0x00000044
#घोषणा IER_READ_COMPLETE_INT_MASK		0x00000010
#घोषणा IER_I2C_INT_EN_MASK			0x00000008
#घोषणा IER_FIFO_INT_EN_MASK			0x00000002
#घोषणा IER_NOACK_EN_MASK			0x00000001

#घोषणा ISR_OFFSET				0x00000048
#घोषणा ISR_RESERVED_MASK			0xffffff60
#घोषणा ISR_CMDBUSY_MASK			0x00000080
#घोषणा ISR_READ_COMPLETE_MASK			0x00000010
#घोषणा ISR_SES_DONE_MASK			0x00000008
#घोषणा ISR_ERR_MASK				0x00000004
#घोषणा ISR_TXFIFOEMPTY_MASK			0x00000002
#घोषणा ISR_NOACK_MASK				0x00000001

#घोषणा CLKEN_OFFSET				0x0000004C
#घोषणा CLKEN_AUTOSENSE_OFF_MASK		0x00000080
#घोषणा CLKEN_M_SHIFT				4
#घोषणा CLKEN_N_SHIFT				1
#घोषणा CLKEN_CLKEN_MASK			0x00000001

#घोषणा FIFO_STATUS_OFFSET			0x00000054
#घोषणा FIFO_STATUS_RXFIFO_EMPTY_MASK		0x00000004
#घोषणा FIFO_STATUS_TXFIFO_EMPTY_MASK		0x00000010

#घोषणा HSTIM_OFFSET				0x00000058
#घोषणा HSTIM_HS_MODE_MASK			0x00008000
#घोषणा HSTIM_HS_HOLD_SHIFT			10
#घोषणा HSTIM_HS_HIGH_PHASE_SHIFT		5
#घोषणा HSTIM_HS_SETUP_SHIFT			0

#घोषणा PADCTL_OFFSET				0x0000005c
#घोषणा PADCTL_PAD_OUT_EN_MASK			0x00000004

#घोषणा RXFCR_OFFSET				0x00000068
#घोषणा RXFCR_NACK_EN_SHIFT			7
#घोषणा RXFCR_READ_COUNT_SHIFT			0
#घोषणा RXFIFORDOUT_OFFSET			0x0000006c

/* Locally used स्थिरants */
#घोषणा MAX_RX_FIFO_SIZE		64U /* bytes */
#घोषणा MAX_TX_FIFO_SIZE		64U /* bytes */

#घोषणा STD_EXT_CLK_FREQ		13000000UL
#घोषणा HS_EXT_CLK_FREQ			104000000UL

#घोषणा MASTERCODE			0x08 /* Mastercodes are 0000_1xxxb */

#घोषणा I2C_TIMEOUT			100 /* msecs */

/* Operations that can be commanded to the controller */
क्रमागत bcm_kona_cmd_t अणु
	BCM_CMD_NOACTION = 0,
	BCM_CMD_START,
	BCM_CMD_RESTART,
	BCM_CMD_STOP,
पूर्ण;

क्रमागत bus_speed_index अणु
	BCM_SPD_100K = 0,
	BCM_SPD_400K,
	BCM_SPD_1MHZ,
पूर्ण;

क्रमागत hs_bus_speed_index अणु
	BCM_SPD_3P4MHZ = 0,
पूर्ण;

/* Internal भागider settings क्रम standard mode, fast mode and fast mode plus */
काष्ठा bus_speed_cfg अणु
	uपूर्णांक8_t समय_m;		/* Number of cycles क्रम setup समय */
	uपूर्णांक8_t समय_n;		/* Number of cycles क्रम hold समय */
	uपूर्णांक8_t prescale;	/* Prescale भागider */
	uपूर्णांक8_t समय_p;		/* Timing coefficient */
	uपूर्णांक8_t no_भाग;		/* Disable घड़ी भागider */
	uपूर्णांक8_t समय_भाग;	/* Post-prescale भागider */
पूर्ण;

/* Internal भागider settings क्रम high-speed mode */
काष्ठा hs_bus_speed_cfg अणु
	uपूर्णांक8_t hs_hold;	/* Number of घड़ी cycles SCL stays low until
				   the end of bit period */
	uपूर्णांक8_t hs_high_phase;	/* Number of घड़ी cycles SCL stays high
				   beक्रमe it falls */
	uपूर्णांक8_t hs_setup;	/* Number of घड़ी cycles SCL stays low
				   beक्रमe it rises  */
	uपूर्णांक8_t prescale;	/* Prescale भागider */
	uपूर्णांक8_t समय_p;		/* Timing coefficient */
	uपूर्णांक8_t no_भाग;		/* Disable घड़ी भागider */
	uपूर्णांक8_t समय_भाग;	/* Post-prescale भागider */
पूर्ण;

अटल स्थिर काष्ठा bus_speed_cfg std_cfg_table[] = अणु
	[BCM_SPD_100K] = अणु0x01, 0x01, 0x03, 0x06, 0x00, 0x02पूर्ण,
	[BCM_SPD_400K] = अणु0x05, 0x01, 0x03, 0x05, 0x01, 0x02पूर्ण,
	[BCM_SPD_1MHZ] = अणु0x01, 0x01, 0x03, 0x01, 0x01, 0x03पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hs_bus_speed_cfg hs_cfg_table[] = अणु
	[BCM_SPD_3P4MHZ] = अणु0x01, 0x08, 0x14, 0x00, 0x06, 0x01, 0x00पूर्ण,
पूर्ण;

काष्ठा bcm_kona_i2c_dev अणु
	काष्ठा device *device;

	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *बाह्यal_clk;

	काष्ठा i2c_adapter adapter;

	काष्ठा completion करोne;

	स्थिर काष्ठा bus_speed_cfg *std_cfg;
	स्थिर काष्ठा hs_bus_speed_cfg *hs_cfg;
पूर्ण;

अटल व्योम bcm_kona_i2c_send_cmd_to_ctrl(काष्ठा bcm_kona_i2c_dev *dev,
					  क्रमागत bcm_kona_cmd_t cmd)
अणु
	dev_dbg(dev->device, "%s, %d\n", __func__, cmd);

	चयन (cmd) अणु
	हाल BCM_CMD_NOACTION:
		ग_लिखोl((CS_CMD_CMD_NO_ACTION << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABLE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		अवरोध;

	हाल BCM_CMD_START:
		ग_लिखोl((CS_ACK_CMD_GEN_START << CS_ACK_SHIFT) |
		       (CS_CMD_CMD_START_RESTART << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABLE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		अवरोध;

	हाल BCM_CMD_RESTART:
		ग_लिखोl((CS_ACK_CMD_GEN_RESTART << CS_ACK_SHIFT) |
		       (CS_CMD_CMD_START_RESTART << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABLE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		अवरोध;

	हाल BCM_CMD_STOP:
		ग_लिखोl((CS_CMD_CMD_STOP << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABLE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		अवरोध;

	शेष:
		dev_err(dev->device, "Unknown command %d\n", cmd);
	पूर्ण
पूर्ण

अटल व्योम bcm_kona_i2c_enable_घड़ी(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	ग_लिखोl(पढ़ोl(dev->base + CLKEN_OFFSET) | CLKEN_CLKEN_MASK,
	       dev->base + CLKEN_OFFSET);
पूर्ण

अटल व्योम bcm_kona_i2c_disable_घड़ी(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	ग_लिखोl(पढ़ोl(dev->base + CLKEN_OFFSET) & ~CLKEN_CLKEN_MASK,
	       dev->base + CLKEN_OFFSET);
पूर्ण

अटल irqवापस_t bcm_kona_i2c_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा bcm_kona_i2c_dev *dev = devid;
	uपूर्णांक32_t status = पढ़ोl(dev->base + ISR_OFFSET);

	अगर ((status & ~ISR_RESERVED_MASK) == 0)
		वापस IRQ_NONE;

	/* Must flush the TX FIFO when NAK detected */
	अगर (status & ISR_NOACK_MASK)
		ग_लिखोl(TXFCR_FIFO_FLUSH_MASK | TXFCR_FIFO_EN_MASK,
		       dev->base + TXFCR_OFFSET);

	ग_लिखोl(status & ~ISR_RESERVED_MASK, dev->base + ISR_OFFSET);
	complete(&dev->करोne);

	वापस IRQ_HANDLED;
पूर्ण

/* Wait क्रम ISR_CMDBUSY_MASK to go low beक्रमe writing to CS, DAT, or RCD */
अटल पूर्णांक bcm_kona_i2c_रुको_अगर_busy(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(I2C_TIMEOUT);

	जबतक (पढ़ोl(dev->base + ISR_OFFSET) & ISR_CMDBUSY_MASK)
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(dev->device, "CMDBUSY timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण

	वापस 0;
पूर्ण

/* Send command to I2C bus */
अटल पूर्णांक bcm_kona_send_i2c_cmd(काष्ठा bcm_kona_i2c_dev *dev,
				 क्रमागत bcm_kona_cmd_t cmd)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ समय_left = msecs_to_jअगरfies(I2C_TIMEOUT);

	/* Make sure the hardware is पढ़ोy */
	rc = bcm_kona_i2c_रुको_अगर_busy(dev);
	अगर (rc < 0)
		वापस rc;

	/* Unmask the session करोne पूर्णांकerrupt */
	ग_लिखोl(IER_I2C_INT_EN_MASK, dev->base + IER_OFFSET);

	/* Mark as incomplete beक्रमe sending the command */
	reinit_completion(&dev->करोne);

	/* Send the command */
	bcm_kona_i2c_send_cmd_to_ctrl(dev, cmd);

	/* Wait क्रम transaction to finish or समयout */
	समय_left = रुको_क्रम_completion_समयout(&dev->करोne, समय_left);

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(0, dev->base + IER_OFFSET);

	अगर (!समय_left) अणु
		dev_err(dev->device, "controller timed out\n");
		rc = -ETIMEDOUT;
	पूर्ण

	/* Clear command */
	bcm_kona_i2c_send_cmd_to_ctrl(dev, BCM_CMD_NOACTION);

	वापस rc;
पूर्ण

/* Read a single RX FIFO worth of data from the i2c bus */
अटल पूर्णांक bcm_kona_i2c_पढ़ो_fअगरo_single(काष्ठा bcm_kona_i2c_dev *dev,
					 uपूर्णांक8_t *buf, अचिन्हित पूर्णांक len,
					 अचिन्हित पूर्णांक last_byte_nak)
अणु
	अचिन्हित दीर्घ समय_left = msecs_to_jअगरfies(I2C_TIMEOUT);

	/* Mark as incomplete beक्रमe starting the RX FIFO */
	reinit_completion(&dev->करोne);

	/* Unmask the पढ़ो complete पूर्णांकerrupt */
	ग_लिखोl(IER_READ_COMPLETE_INT_MASK, dev->base + IER_OFFSET);

	/* Start the RX FIFO */
	ग_लिखोl((last_byte_nak << RXFCR_NACK_EN_SHIFT) |
	       (len << RXFCR_READ_COUNT_SHIFT),
		dev->base + RXFCR_OFFSET);

	/* Wait क्रम FIFO पढ़ो to complete */
	समय_left = रुको_क्रम_completion_समयout(&dev->करोne, समय_left);

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(0, dev->base + IER_OFFSET);

	अगर (!समय_left) अणु
		dev_err(dev->device, "RX FIFO time out\n");
		वापस -EREMOTEIO;
	पूर्ण

	/* Read data from FIFO */
	क्रम (; len > 0; len--, buf++)
		*buf = पढ़ोl(dev->base + RXFIFORDOUT_OFFSET);

	वापस 0;
पूर्ण

/* Read any amount of data using the RX FIFO from the i2c bus */
अटल पूर्णांक bcm_kona_i2c_पढ़ो_fअगरo(काष्ठा bcm_kona_i2c_dev *dev,
				  काष्ठा i2c_msg *msg)
अणु
	अचिन्हित पूर्णांक bytes_to_पढ़ो = MAX_RX_FIFO_SIZE;
	अचिन्हित पूर्णांक last_byte_nak = 0;
	अचिन्हित पूर्णांक bytes_पढ़ो = 0;
	पूर्णांक rc;

	uपूर्णांक8_t *पंचांगp_buf = msg->buf;

	जबतक (bytes_पढ़ो < msg->len) अणु
		अगर (msg->len - bytes_पढ़ो <= MAX_RX_FIFO_SIZE) अणु
			last_byte_nak = 1; /* NAK last byte of transfer */
			bytes_to_पढ़ो = msg->len - bytes_पढ़ो;
		पूर्ण

		rc = bcm_kona_i2c_पढ़ो_fअगरo_single(dev, पंचांगp_buf, bytes_to_पढ़ो,
						   last_byte_nak);
		अगर (rc < 0)
			वापस -EREMOTEIO;

		bytes_पढ़ो += bytes_to_पढ़ो;
		पंचांगp_buf += bytes_to_पढ़ो;
	पूर्ण

	वापस 0;
पूर्ण

/* Write a single byte of data to the i2c bus */
अटल पूर्णांक bcm_kona_i2c_ग_लिखो_byte(काष्ठा bcm_kona_i2c_dev *dev, uपूर्णांक8_t data,
				   अचिन्हित पूर्णांक nak_expected)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ समय_left = msecs_to_jअगरfies(I2C_TIMEOUT);
	अचिन्हित पूर्णांक nak_received;

	/* Make sure the hardware is पढ़ोy */
	rc = bcm_kona_i2c_रुको_अगर_busy(dev);
	अगर (rc < 0)
		वापस rc;

	/* Clear pending session करोne पूर्णांकerrupt */
	ग_लिखोl(ISR_SES_DONE_MASK, dev->base + ISR_OFFSET);

	/* Unmask the session करोne पूर्णांकerrupt */
	ग_लिखोl(IER_I2C_INT_EN_MASK, dev->base + IER_OFFSET);

	/* Mark as incomplete beक्रमe sending the data */
	reinit_completion(&dev->करोne);

	/* Send one byte of data */
	ग_लिखोl(data, dev->base + DAT_OFFSET);

	/* Wait क्रम byte to be written */
	समय_left = रुको_क्रम_completion_समयout(&dev->करोne, समय_left);

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(0, dev->base + IER_OFFSET);

	अगर (!समय_left) अणु
		dev_dbg(dev->device, "controller timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	nak_received = पढ़ोl(dev->base + CS_OFFSET) & CS_ACK_MASK ? 1 : 0;

	अगर (nak_received ^ nak_expected) अणु
		dev_dbg(dev->device, "unexpected NAK/ACK\n");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Write a single TX FIFO worth of data to the i2c bus */
अटल पूर्णांक bcm_kona_i2c_ग_लिखो_fअगरo_single(काष्ठा bcm_kona_i2c_dev *dev,
					  uपूर्णांक8_t *buf, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक k;
	अचिन्हित दीर्घ समय_left = msecs_to_jअगरfies(I2C_TIMEOUT);
	अचिन्हित पूर्णांक fअगरo_status;

	/* Mark as incomplete beक्रमe sending data to the TX FIFO */
	reinit_completion(&dev->करोne);

	/* Unmask the fअगरo empty and nak पूर्णांकerrupt */
	ग_लिखोl(IER_FIFO_INT_EN_MASK | IER_NOACK_EN_MASK,
	       dev->base + IER_OFFSET);

	/* Disable IRQ to load a FIFO worth of data without पूर्णांकerruption */
	disable_irq(dev->irq);

	/* Write data पूर्णांकo FIFO */
	क्रम (k = 0; k < len; k++)
		ग_लिखोl(buf[k], (dev->base + DAT_OFFSET));

	/* Enable IRQ now that data has been loaded */
	enable_irq(dev->irq);

	/* Wait क्रम FIFO to empty */
	करो अणु
		समय_left = रुको_क्रम_completion_समयout(&dev->करोne, समय_left);
		fअगरo_status = पढ़ोl(dev->base + FIFO_STATUS_OFFSET);
	पूर्ण जबतक (समय_left && !(fअगरo_status & FIFO_STATUS_TXFIFO_EMPTY_MASK));

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(0, dev->base + IER_OFFSET);

	/* Check अगर there was a NAK */
	अगर (पढ़ोl(dev->base + CS_OFFSET) & CS_ACK_MASK) अणु
		dev_err(dev->device, "unexpected NAK\n");
		वापस -EREMOTEIO;
	पूर्ण

	/* Check अगर a समयout occured */
	अगर (!समय_left) अणु
		dev_err(dev->device, "completion timed out\n");
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण


/* Write any amount of data using TX FIFO to the i2c bus */
अटल पूर्णांक bcm_kona_i2c_ग_लिखो_fअगरo(काष्ठा bcm_kona_i2c_dev *dev,
				   काष्ठा i2c_msg *msg)
अणु
	अचिन्हित पूर्णांक bytes_to_ग_लिखो = MAX_TX_FIFO_SIZE;
	अचिन्हित पूर्णांक bytes_written = 0;
	पूर्णांक rc;

	uपूर्णांक8_t *पंचांगp_buf = msg->buf;

	जबतक (bytes_written < msg->len) अणु
		अगर (msg->len - bytes_written <= MAX_TX_FIFO_SIZE)
			bytes_to_ग_लिखो = msg->len - bytes_written;

		rc = bcm_kona_i2c_ग_लिखो_fअगरo_single(dev, पंचांगp_buf,
						    bytes_to_ग_लिखो);
		अगर (rc < 0)
			वापस -EREMOTEIO;

		bytes_written += bytes_to_ग_लिखो;
		पंचांगp_buf += bytes_to_ग_लिखो;
	पूर्ण

	वापस 0;
पूर्ण

/* Send i2c address */
अटल पूर्णांक bcm_kona_i2c_करो_addr(काष्ठा bcm_kona_i2c_dev *dev,
				     काष्ठा i2c_msg *msg)
अणु
	अचिन्हित अक्षर addr;

	अगर (msg->flags & I2C_M_TEN) अणु
		/* First byte is 11110XX0 where XX is upper 2 bits */
		addr = 0xF0 | ((msg->addr & 0x300) >> 7);
		अगर (bcm_kona_i2c_ग_लिखो_byte(dev, addr, 0) < 0)
			वापस -EREMOTEIO;

		/* Second byte is the reमुख्यing 8 bits */
		addr = msg->addr & 0xFF;
		अगर (bcm_kona_i2c_ग_लिखो_byte(dev, addr, 0) < 0)
			वापस -EREMOTEIO;

		अगर (msg->flags & I2C_M_RD) अणु
			/* For पढ़ो, send restart command */
			अगर (bcm_kona_send_i2c_cmd(dev, BCM_CMD_RESTART) < 0)
				वापस -EREMOTEIO;

			/* Then re-send the first byte with the पढ़ो bit set */
			addr = 0xF0 | ((msg->addr & 0x300) >> 7) | 0x01;
			अगर (bcm_kona_i2c_ग_लिखो_byte(dev, addr, 0) < 0)
				वापस -EREMOTEIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		addr = i2c_8bit_addr_from_msg(msg);

		अगर (bcm_kona_i2c_ग_लिखो_byte(dev, addr, 0) < 0)
			वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm_kona_i2c_enable_स्वतःsense(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	ग_लिखोl(पढ़ोl(dev->base + CLKEN_OFFSET) & ~CLKEN_AUTOSENSE_OFF_MASK,
	       dev->base + CLKEN_OFFSET);
पूर्ण

अटल व्योम bcm_kona_i2c_config_timing(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	ग_लिखोl(पढ़ोl(dev->base + HSTIM_OFFSET) & ~HSTIM_HS_MODE_MASK,
	       dev->base + HSTIM_OFFSET);

	ग_लिखोl((dev->std_cfg->prescale << TIM_PRESCALE_SHIFT) |
	       (dev->std_cfg->समय_p << TIM_P_SHIFT) |
	       (dev->std_cfg->no_भाग << TIM_NO_DIV_SHIFT) |
	       (dev->std_cfg->समय_भाग	<< TIM_DIV_SHIFT),
	       dev->base + TIM_OFFSET);

	ग_लिखोl((dev->std_cfg->समय_m << CLKEN_M_SHIFT) |
	       (dev->std_cfg->समय_n << CLKEN_N_SHIFT) |
	       CLKEN_CLKEN_MASK,
	       dev->base + CLKEN_OFFSET);
पूर्ण

अटल व्योम bcm_kona_i2c_config_timing_hs(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	ग_लिखोl((dev->hs_cfg->prescale << TIM_PRESCALE_SHIFT) |
	       (dev->hs_cfg->समय_p << TIM_P_SHIFT) |
	       (dev->hs_cfg->no_भाग << TIM_NO_DIV_SHIFT) |
	       (dev->hs_cfg->समय_भाग << TIM_DIV_SHIFT),
	       dev->base + TIM_OFFSET);

	ग_लिखोl((dev->hs_cfg->hs_hold << HSTIM_HS_HOLD_SHIFT) |
	       (dev->hs_cfg->hs_high_phase << HSTIM_HS_HIGH_PHASE_SHIFT) |
	       (dev->hs_cfg->hs_setup << HSTIM_HS_SETUP_SHIFT),
	       dev->base + HSTIM_OFFSET);

	ग_लिखोl(पढ़ोl(dev->base + HSTIM_OFFSET) | HSTIM_HS_MODE_MASK,
	       dev->base + HSTIM_OFFSET);
पूर्ण

अटल पूर्णांक bcm_kona_i2c_चयन_to_hs(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	पूर्णांक rc;

	/* Send mastercode at standard speed */
	rc = bcm_kona_i2c_ग_लिखो_byte(dev, MASTERCODE, 1);
	अगर (rc < 0) अणु
		pr_err("High speed handshake failed\n");
		वापस rc;
	पूर्ण

	/* Configure बाह्यal घड़ी to higher frequency */
	rc = clk_set_rate(dev->बाह्यal_clk, HS_EXT_CLK_FREQ);
	अगर (rc) अणु
		dev_err(dev->device, "%s: clk_set_rate returned %d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	/* Reconfigure पूर्णांकernal भागiders */
	bcm_kona_i2c_config_timing_hs(dev);

	/* Send a restart command */
	rc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_RESTART);
	अगर (rc < 0)
		dev_err(dev->device, "High speed restart command failed\n");

	वापस rc;
पूर्ण

अटल पूर्णांक bcm_kona_i2c_चयन_to_std(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	पूर्णांक rc;

	/* Reconfigure पूर्णांकernal भागiders */
	bcm_kona_i2c_config_timing(dev);

	/* Configure बाह्यal घड़ी to lower frequency */
	rc = clk_set_rate(dev->बाह्यal_clk, STD_EXT_CLK_FREQ);
	अगर (rc) अणु
		dev_err(dev->device, "%s: clk_set_rate returned %d\n",
			__func__, rc);
	पूर्ण

	वापस rc;
पूर्ण

/* Master transfer function */
अटल पूर्णांक bcm_kona_i2c_xfer(काष्ठा i2c_adapter *adapter,
			     काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा bcm_kona_i2c_dev *dev = i2c_get_adapdata(adapter);
	काष्ठा i2c_msg *pmsg;
	पूर्णांक rc = 0;
	पूर्णांक i;

	rc = clk_prepare_enable(dev->बाह्यal_clk);
	अगर (rc) अणु
		dev_err(dev->device, "%s: peri clock enable failed. err %d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	/* Enable pad output */
	ग_लिखोl(0, dev->base + PADCTL_OFFSET);

	/* Enable पूर्णांकernal घड़ीs */
	bcm_kona_i2c_enable_घड़ी(dev);

	/* Send start command */
	rc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_START);
	अगर (rc < 0) अणु
		dev_err(dev->device, "Start command failed rc = %d\n", rc);
		जाओ xfer_disable_pad;
	पूर्ण

	/* Switch to high speed अगर applicable */
	अगर (dev->hs_cfg) अणु
		rc = bcm_kona_i2c_चयन_to_hs(dev);
		अगर (rc < 0)
			जाओ xfer_send_stop;
	पूर्ण

	/* Loop through all messages */
	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];

		/* Send restart क्रम subsequent messages */
		अगर ((i != 0) && ((pmsg->flags & I2C_M_NOSTART) == 0)) अणु
			rc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_RESTART);
			अगर (rc < 0) अणु
				dev_err(dev->device,
					"restart cmd failed rc = %d\n", rc);
				जाओ xfer_send_stop;
			पूर्ण
		पूर्ण

		/* Send slave address */
		अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
			rc = bcm_kona_i2c_करो_addr(dev, pmsg);
			अगर (rc < 0) अणु
				dev_err(dev->device,
					"NAK from addr %2.2x msg#%d rc = %d\n",
					pmsg->addr, i, rc);
				जाओ xfer_send_stop;
			पूर्ण
		पूर्ण

		/* Perक्रमm data transfer */
		अगर (pmsg->flags & I2C_M_RD) अणु
			rc = bcm_kona_i2c_पढ़ो_fअगरo(dev, pmsg);
			अगर (rc < 0) अणु
				dev_err(dev->device, "read failure\n");
				जाओ xfer_send_stop;
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = bcm_kona_i2c_ग_लिखो_fअगरo(dev, pmsg);
			अगर (rc < 0) अणु
				dev_err(dev->device, "write failure");
				जाओ xfer_send_stop;
			पूर्ण
		पूर्ण
	पूर्ण

	rc = num;

xfer_send_stop:
	/* Send a STOP command */
	bcm_kona_send_i2c_cmd(dev, BCM_CMD_STOP);

	/* Return from high speed अगर applicable */
	अगर (dev->hs_cfg) अणु
		पूर्णांक hs_rc = bcm_kona_i2c_चयन_to_std(dev);

		अगर (hs_rc)
			rc = hs_rc;
	पूर्ण

xfer_disable_pad:
	/* Disable pad output */
	ग_लिखोl(PADCTL_PAD_OUT_EN_MASK, dev->base + PADCTL_OFFSET);

	/* Stop पूर्णांकernal घड़ी */
	bcm_kona_i2c_disable_घड़ी(dev);

	clk_disable_unprepare(dev->बाह्यal_clk);

	वापस rc;
पूर्ण

अटल uपूर्णांक32_t bcm_kona_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR |
	    I2C_FUNC_NOSTART;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm bcm_algo = अणु
	.master_xfer = bcm_kona_i2c_xfer,
	.functionality = bcm_kona_i2c_functionality,
पूर्ण;

अटल पूर्णांक bcm_kona_i2c_assign_bus_speed(काष्ठा bcm_kona_i2c_dev *dev)
अणु
	अचिन्हित पूर्णांक bus_speed;
	पूर्णांक ret = of_property_पढ़ो_u32(dev->device->of_node, "clock-frequency",
				       &bus_speed);
	अगर (ret < 0) अणु
		dev_err(dev->device, "missing clock-frequency property\n");
		वापस -ENODEV;
	पूर्ण

	चयन (bus_speed) अणु
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		dev->std_cfg = &std_cfg_table[BCM_SPD_100K];
		अवरोध;
	हाल I2C_MAX_FAST_MODE_FREQ:
		dev->std_cfg = &std_cfg_table[BCM_SPD_400K];
		अवरोध;
	हाल I2C_MAX_FAST_MODE_PLUS_FREQ:
		dev->std_cfg = &std_cfg_table[BCM_SPD_1MHZ];
		अवरोध;
	हाल I2C_MAX_HIGH_SPEED_MODE_FREQ:
		/* Send mastercode at 100k */
		dev->std_cfg = &std_cfg_table[BCM_SPD_100K];
		dev->hs_cfg = &hs_cfg_table[BCM_SPD_3P4MHZ];
		अवरोध;
	शेष:
		pr_err("%d hz bus speed not supported\n", bus_speed);
		pr_err("Valid speeds are 100khz, 400khz, 1mhz, and 3.4mhz\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc = 0;
	काष्ठा bcm_kona_i2c_dev *dev;
	काष्ठा i2c_adapter *adap;

	/* Allocate memory क्रम निजी data काष्ठाure */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dev);
	dev->device = &pdev->dev;
	init_completion(&dev->करोne);

	/* Map hardware रेजिस्टरs */
	dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->base))
		वापस -ENOMEM;

	/* Get and enable बाह्यal घड़ी */
	dev->बाह्यal_clk = devm_clk_get(dev->device, शून्य);
	अगर (IS_ERR(dev->बाह्यal_clk)) अणु
		dev_err(dev->device, "couldn't get clock\n");
		वापस -ENODEV;
	पूर्ण

	rc = clk_set_rate(dev->बाह्यal_clk, STD_EXT_CLK_FREQ);
	अगर (rc) अणु
		dev_err(dev->device, "%s: clk_set_rate returned %d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	rc = clk_prepare_enable(dev->बाह्यal_clk);
	अगर (rc) अणु
		dev_err(dev->device, "couldn't enable clock\n");
		वापस rc;
	पूर्ण

	/* Parse bus speed */
	rc = bcm_kona_i2c_assign_bus_speed(dev);
	अगर (rc)
		जाओ probe_disable_clk;

	/* Enable पूर्णांकernal घड़ीs */
	bcm_kona_i2c_enable_घड़ी(dev);

	/* Configure पूर्णांकernal भागiders */
	bcm_kona_i2c_config_timing(dev);

	/* Disable समयout */
	ग_लिखोl(0, dev->base + TOUT_OFFSET);

	/* Enable स्वतःsense */
	bcm_kona_i2c_enable_स्वतःsense(dev);

	/* Enable TX FIFO */
	ग_लिखोl(TXFCR_FIFO_FLUSH_MASK | TXFCR_FIFO_EN_MASK,
	       dev->base + TXFCR_OFFSET);

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(0, dev->base + IER_OFFSET);

	/* Clear all pending पूर्णांकerrupts */
	ग_लिखोl(ISR_CMDBUSY_MASK |
	       ISR_READ_COMPLETE_MASK |
	       ISR_SES_DONE_MASK |
	       ISR_ERR_MASK |
	       ISR_TXFIFOEMPTY_MASK |
	       ISR_NOACK_MASK,
	       dev->base + ISR_OFFSET);

	/* Get the पूर्णांकerrupt number */
	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dev->irq < 0) अणु
		rc = dev->irq;
		जाओ probe_disable_clk;
	पूर्ण

	/* रेजिस्टर the ISR handler */
	rc = devm_request_irq(&pdev->dev, dev->irq, bcm_kona_i2c_isr,
			      IRQF_SHARED, pdev->name, dev);
	अगर (rc) अणु
		dev_err(dev->device, "failed to request irq %i\n", dev->irq);
		जाओ probe_disable_clk;
	पूर्ण

	/* Enable the controller but leave it idle */
	bcm_kona_i2c_send_cmd_to_ctrl(dev, BCM_CMD_NOACTION);

	/* Disable pad output */
	ग_लिखोl(PADCTL_PAD_OUT_EN_MASK, dev->base + PADCTL_OFFSET);

	/* Disable पूर्णांकernal घड़ी */
	bcm_kona_i2c_disable_घड़ी(dev);

	/* Disable बाह्यal घड़ी */
	clk_disable_unprepare(dev->बाह्यal_clk);

	/* Add the i2c adapter */
	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	strlcpy(adap->name, "Broadcom I2C adapter", माप(adap->name));
	adap->algo = &bcm_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	rc = i2c_add_adapter(adap);
	अगर (rc)
		वापस rc;

	dev_info(dev->device, "device registered successfully\n");

	वापस 0;

probe_disable_clk:
	bcm_kona_i2c_disable_घड़ी(dev);
	clk_disable_unprepare(dev->बाह्यal_clk);

	वापस rc;
पूर्ण

अटल पूर्णांक bcm_kona_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_kona_i2c_dev *dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_kona_i2c_of_match[] = अणु
	अणु.compatible = "brcm,kona-i2c",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_kona_i2c_of_match);

अटल काष्ठा platक्रमm_driver bcm_kona_i2c_driver = अणु
	.driver = अणु
		   .name = "bcm-kona-i2c",
		   .of_match_table = bcm_kona_i2c_of_match,
		   पूर्ण,
	.probe = bcm_kona_i2c_probe,
	.हटाओ = bcm_kona_i2c_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm_kona_i2c_driver);

MODULE_AUTHOR("Tim Kryger <tkryger@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Kona I2C Driver");
MODULE_LICENSE("GPL v2");
