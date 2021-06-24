<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
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

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा IDM_CTRL_सूचीECT_OFFSET       0x00
#घोषणा CFG_OFFSET                   0x00
#घोषणा CFG_RESET_SHIFT              31
#घोषणा CFG_EN_SHIFT                 30
#घोषणा CFG_SLAVE_ADDR_0_SHIFT       28
#घोषणा CFG_M_RETRY_CNT_SHIFT        16
#घोषणा CFG_M_RETRY_CNT_MASK         0x0f

#घोषणा TIM_CFG_OFFSET               0x04
#घोषणा TIM_CFG_MODE_400_SHIFT       31
#घोषणा TIM_RAND_SLAVE_STRETCH_SHIFT      24
#घोषणा TIM_RAND_SLAVE_STRETCH_MASK       0x7f
#घोषणा TIM_PERIODIC_SLAVE_STRETCH_SHIFT  16
#घोषणा TIM_PERIODIC_SLAVE_STRETCH_MASK   0x7f

#घोषणा S_CFG_SMBUS_ADDR_OFFSET           0x08
#घोषणा S_CFG_EN_NIC_SMB_ADDR3_SHIFT      31
#घोषणा S_CFG_NIC_SMB_ADDR3_SHIFT         24
#घोषणा S_CFG_NIC_SMB_ADDR3_MASK          0x7f
#घोषणा S_CFG_EN_NIC_SMB_ADDR2_SHIFT      23
#घोषणा S_CFG_NIC_SMB_ADDR2_SHIFT         16
#घोषणा S_CFG_NIC_SMB_ADDR2_MASK          0x7f
#घोषणा S_CFG_EN_NIC_SMB_ADDR1_SHIFT      15
#घोषणा S_CFG_NIC_SMB_ADDR1_SHIFT         8
#घोषणा S_CFG_NIC_SMB_ADDR1_MASK          0x7f
#घोषणा S_CFG_EN_NIC_SMB_ADDR0_SHIFT      7
#घोषणा S_CFG_NIC_SMB_ADDR0_SHIFT         0
#घोषणा S_CFG_NIC_SMB_ADDR0_MASK          0x7f

#घोषणा M_FIFO_CTRL_OFFSET           0x0c
#घोषणा M_FIFO_RX_FLUSH_SHIFT        31
#घोषणा M_FIFO_TX_FLUSH_SHIFT        30
#घोषणा M_FIFO_RX_CNT_SHIFT          16
#घोषणा M_FIFO_RX_CNT_MASK           0x7f
#घोषणा M_FIFO_RX_THLD_SHIFT         8
#घोषणा M_FIFO_RX_THLD_MASK          0x3f

#घोषणा S_FIFO_CTRL_OFFSET           0x10
#घोषणा S_FIFO_RX_FLUSH_SHIFT        31
#घोषणा S_FIFO_TX_FLUSH_SHIFT        30
#घोषणा S_FIFO_RX_CNT_SHIFT          16
#घोषणा S_FIFO_RX_CNT_MASK           0x7f
#घोषणा S_FIFO_RX_THLD_SHIFT         8
#घोषणा S_FIFO_RX_THLD_MASK          0x3f

#घोषणा M_CMD_OFFSET                 0x30
#घोषणा M_CMD_START_BUSY_SHIFT       31
#घोषणा M_CMD_STATUS_SHIFT           25
#घोषणा M_CMD_STATUS_MASK            0x07
#घोषणा M_CMD_STATUS_SUCCESS         0x0
#घोषणा M_CMD_STATUS_LOST_ARB        0x1
#घोषणा M_CMD_STATUS_NACK_ADDR       0x2
#घोषणा M_CMD_STATUS_NACK_DATA       0x3
#घोषणा M_CMD_STATUS_TIMEOUT         0x4
#घोषणा M_CMD_STATUS_FIFO_UNDERRUN   0x5
#घोषणा M_CMD_STATUS_RX_FIFO_FULL    0x6
#घोषणा M_CMD_PROTOCOL_SHIFT         9
#घोषणा M_CMD_PROTOCOL_MASK          0xf
#घोषणा M_CMD_PROTOCOL_QUICK         0x0
#घोषणा M_CMD_PROTOCOL_BLK_WR        0x7
#घोषणा M_CMD_PROTOCOL_BLK_RD        0x8
#घोषणा M_CMD_PROTOCOL_PROCESS       0xa
#घोषणा M_CMD_PEC_SHIFT              8
#घोषणा M_CMD_RD_CNT_SHIFT           0
#घोषणा M_CMD_RD_CNT_MASK            0xff

#घोषणा S_CMD_OFFSET                 0x34
#घोषणा S_CMD_START_BUSY_SHIFT       31
#घोषणा S_CMD_STATUS_SHIFT           23
#घोषणा S_CMD_STATUS_MASK            0x07
#घोषणा S_CMD_STATUS_SUCCESS         0x0
#घोषणा S_CMD_STATUS_TIMEOUT         0x5
#घोषणा S_CMD_STATUS_MASTER_ABORT    0x7

#घोषणा IE_OFFSET                    0x38
#घोषणा IE_M_RX_FIFO_FULL_SHIFT      31
#घोषणा IE_M_RX_THLD_SHIFT           30
#घोषणा IE_M_START_BUSY_SHIFT        28
#घोषणा IE_M_TX_UNDERRUN_SHIFT       27
#घोषणा IE_S_RX_FIFO_FULL_SHIFT      26
#घोषणा IE_S_RX_THLD_SHIFT           25
#घोषणा IE_S_RX_EVENT_SHIFT          24
#घोषणा IE_S_START_BUSY_SHIFT        23
#घोषणा IE_S_TX_UNDERRUN_SHIFT       22
#घोषणा IE_S_RD_EVENT_SHIFT          21

#घोषणा IS_OFFSET                    0x3c
#घोषणा IS_M_RX_FIFO_FULL_SHIFT      31
#घोषणा IS_M_RX_THLD_SHIFT           30
#घोषणा IS_M_START_BUSY_SHIFT        28
#घोषणा IS_M_TX_UNDERRUN_SHIFT       27
#घोषणा IS_S_RX_FIFO_FULL_SHIFT      26
#घोषणा IS_S_RX_THLD_SHIFT           25
#घोषणा IS_S_RX_EVENT_SHIFT          24
#घोषणा IS_S_START_BUSY_SHIFT        23
#घोषणा IS_S_TX_UNDERRUN_SHIFT       22
#घोषणा IS_S_RD_EVENT_SHIFT          21

#घोषणा M_TX_OFFSET                  0x40
#घोषणा M_TX_WR_STATUS_SHIFT         31
#घोषणा M_TX_DATA_SHIFT              0
#घोषणा M_TX_DATA_MASK               0xff

#घोषणा M_RX_OFFSET                  0x44
#घोषणा M_RX_STATUS_SHIFT            30
#घोषणा M_RX_STATUS_MASK             0x03
#घोषणा M_RX_PEC_ERR_SHIFT           29
#घोषणा M_RX_DATA_SHIFT              0
#घोषणा M_RX_DATA_MASK               0xff

#घोषणा S_TX_OFFSET                  0x48
#घोषणा S_TX_WR_STATUS_SHIFT         31
#घोषणा S_TX_DATA_SHIFT              0
#घोषणा S_TX_DATA_MASK               0xff

#घोषणा S_RX_OFFSET                  0x4c
#घोषणा S_RX_STATUS_SHIFT            30
#घोषणा S_RX_STATUS_MASK             0x03
#घोषणा S_RX_PEC_ERR_SHIFT           29
#घोषणा S_RX_DATA_SHIFT              0
#घोषणा S_RX_DATA_MASK               0xff

#घोषणा I2C_TIMEOUT_MSEC             50000
#घोषणा M_TX_RX_FIFO_SIZE            64
#घोषणा M_RX_FIFO_MAX_THLD_VALUE     (M_TX_RX_FIFO_SIZE - 1)

#घोषणा M_RX_MAX_READ_LEN            255
#घोषणा M_RX_FIFO_THLD_VALUE         50

#घोषणा IE_M_ALL_INTERRUPT_SHIFT     27
#घोषणा IE_M_ALL_INTERRUPT_MASK      0x1e

#घोषणा SLAVE_READ_WRITE_BIT_MASK    0x1
#घोषणा SLAVE_READ_WRITE_BIT_SHIFT   0x1
#घोषणा SLAVE_MAX_SIZE_TRANSACTION   64
#घोषणा SLAVE_CLOCK_STRETCH_TIME     25

#घोषणा IE_S_ALL_INTERRUPT_SHIFT     21
#घोषणा IE_S_ALL_INTERRUPT_MASK      0x3f
/*
 * It takes ~18us to पढ़ोing 10bytes of data, hence to keep tasklet
 * running क्रम less समय, max slave पढ़ो per tasklet is set to 10 bytes.
 */
#घोषणा MAX_SLAVE_RX_PER_INT         10

क्रमागत i2c_slave_पढ़ो_status अणु
	I2C_SLAVE_RX_FIFO_EMPTY = 0,
	I2C_SLAVE_RX_START,
	I2C_SLAVE_RX_DATA,
	I2C_SLAVE_RX_END,
पूर्ण;

क्रमागत bus_speed_index अणु
	I2C_SPD_100K = 0,
	I2C_SPD_400K,
पूर्ण;

क्रमागत bcm_iproc_i2c_type अणु
	IPROC_I2C,
	IPROC_I2C_NIC
पूर्ण;

काष्ठा bcm_iproc_i2c_dev अणु
	काष्ठा device *device;
	क्रमागत bcm_iproc_i2c_type type;
	पूर्णांक irq;

	व्योम __iomem *base;
	व्योम __iomem *idm_base;

	u32 ape_addr_mask;

	/* lock क्रम indirect access through IDM */
	spinlock_t idm_lock;

	काष्ठा i2c_adapter adapter;
	अचिन्हित पूर्णांक bus_speed;

	काष्ठा completion करोne;
	पूर्णांक xfer_is_करोne;

	काष्ठा i2c_msg *msg;

	काष्ठा i2c_client *slave;

	/* bytes that have been transferred */
	अचिन्हित पूर्णांक tx_bytes;
	/* bytes that have been पढ़ो */
	अचिन्हित पूर्णांक rx_bytes;
	अचिन्हित पूर्णांक thld_bytes;

	bool slave_rx_only;
	bool rx_start_rcvd;
	bool slave_पढ़ो_complete;
	u32 tx_underrun;
	u32 slave_पूर्णांक_mask;
	काष्ठा tasklet_काष्ठा slave_rx_tasklet;
पूर्ण;

/* tasklet to process slave rx data */
अटल व्योम slave_rx_tasklet_fn(अचिन्हित दीर्घ);

/*
 * Can be expanded in the future अगर more पूर्णांकerrupt status bits are utilized
 */
#घोषणा ISR_MASK (BIT(IS_M_START_BUSY_SHIFT) | BIT(IS_M_TX_UNDERRUN_SHIFT)\
		| BIT(IS_M_RX_THLD_SHIFT))

#घोषणा ISR_MASK_SLAVE (BIT(IS_S_START_BUSY_SHIFT)\
		| BIT(IS_S_RX_EVENT_SHIFT) | BIT(IS_S_RD_EVENT_SHIFT)\
		| BIT(IS_S_TX_UNDERRUN_SHIFT) | BIT(IS_S_RX_FIFO_FULL_SHIFT)\
		| BIT(IS_S_RX_THLD_SHIFT))

अटल पूर्णांक bcm_iproc_i2c_reg_slave(काष्ठा i2c_client *slave);
अटल पूर्णांक bcm_iproc_i2c_unreg_slave(काष्ठा i2c_client *slave);
अटल व्योम bcm_iproc_i2c_enable_disable(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
					 bool enable);

अटल अंतरभूत u32 iproc_i2c_rd_reg(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
				   u32 offset)
अणु
	u32 val;

	अगर (iproc_i2c->idm_base) अणु
		spin_lock(&iproc_i2c->idm_lock);
		ग_लिखोl(iproc_i2c->ape_addr_mask,
		       iproc_i2c->idm_base + IDM_CTRL_सूचीECT_OFFSET);
		val = पढ़ोl(iproc_i2c->base + offset);
		spin_unlock(&iproc_i2c->idm_lock);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(iproc_i2c->base + offset);
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत व्योम iproc_i2c_wr_reg(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
				    u32 offset, u32 val)
अणु
	अगर (iproc_i2c->idm_base) अणु
		spin_lock(&iproc_i2c->idm_lock);
		ग_लिखोl(iproc_i2c->ape_addr_mask,
		       iproc_i2c->idm_base + IDM_CTRL_सूचीECT_OFFSET);
		ग_लिखोl(val, iproc_i2c->base + offset);
		spin_unlock(&iproc_i2c->idm_lock);
	पूर्ण अन्यथा अणु
		ग_लिखोl(val, iproc_i2c->base + offset);
	पूर्ण
पूर्ण

अटल व्योम bcm_iproc_i2c_slave_init(
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c, bool need_reset)
अणु
	u32 val;

	iproc_i2c->tx_underrun = 0;
	अगर (need_reset) अणु
		/* put controller in reset */
		val = iproc_i2c_rd_reg(iproc_i2c, CFG_OFFSET);
		val |= BIT(CFG_RESET_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

		/* रुको 100 usec per spec */
		udelay(100);

		/* bring controller out of reset */
		val &= ~(BIT(CFG_RESET_SHIFT));
		iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);
	पूर्ण

	/* flush TX/RX FIFOs */
	val = (BIT(S_FIFO_RX_FLUSH_SHIFT) | BIT(S_FIFO_TX_FLUSH_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, S_FIFO_CTRL_OFFSET, val);

	/* Maximum slave stretch समय */
	val = iproc_i2c_rd_reg(iproc_i2c, TIM_CFG_OFFSET);
	val &= ~(TIM_RAND_SLAVE_STRETCH_MASK << TIM_RAND_SLAVE_STRETCH_SHIFT);
	val |= (SLAVE_CLOCK_STRETCH_TIME << TIM_RAND_SLAVE_STRETCH_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, TIM_CFG_OFFSET, val);

	/* Configure the slave address */
	val = iproc_i2c_rd_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET);
	val |= BIT(S_CFG_EN_NIC_SMB_ADDR3_SHIFT);
	val &= ~(S_CFG_NIC_SMB_ADDR3_MASK << S_CFG_NIC_SMB_ADDR3_SHIFT);
	val |= (iproc_i2c->slave->addr << S_CFG_NIC_SMB_ADDR3_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET, val);

	/* clear all pending slave पूर्णांकerrupts */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, ISR_MASK_SLAVE);

	/* Enable पूर्णांकerrupt रेजिस्टर to indicate a valid byte in receive fअगरo */
	val = BIT(IE_S_RX_EVENT_SHIFT);
	/* Enable पूर्णांकerrupt रेजिस्टर to indicate Slave Rx FIFO Full */
	val |= BIT(IE_S_RX_FIFO_FULL_SHIFT);
	/* Enable पूर्णांकerrupt रेजिस्टर to indicate a Master पढ़ो transaction */
	val |= BIT(IE_S_RD_EVENT_SHIFT);
	/* Enable पूर्णांकerrupt रेजिस्टर क्रम the Slave BUSY command */
	val |= BIT(IE_S_START_BUSY_SHIFT);
	iproc_i2c->slave_पूर्णांक_mask = val;
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);
पूर्ण

अटल व्योम bcm_iproc_i2c_check_slave_status(
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	u32 val;

	val = iproc_i2c_rd_reg(iproc_i2c, S_CMD_OFFSET);
	/* status is valid only when START_BUSY is cleared after it was set */
	अगर (val & BIT(S_CMD_START_BUSY_SHIFT))
		वापस;

	val = (val >> S_CMD_STATUS_SHIFT) & S_CMD_STATUS_MASK;
	अगर (val == S_CMD_STATUS_TIMEOUT || val == S_CMD_STATUS_MASTER_ABORT) अणु
		dev_err(iproc_i2c->device, (val == S_CMD_STATUS_TIMEOUT) ?
			"slave random stretch time timeout\n" :
			"Master aborted read transaction\n");
		/* re-initialize i2c क्रम recovery */
		bcm_iproc_i2c_enable_disable(iproc_i2c, false);
		bcm_iproc_i2c_slave_init(iproc_i2c, true);
		bcm_iproc_i2c_enable_disable(iproc_i2c, true);
	पूर्ण
पूर्ण

अटल व्योम bcm_iproc_i2c_slave_पढ़ो(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	u8 rx_data, rx_status;
	u32 rx_bytes = 0;
	u32 val;

	जबतक (rx_bytes < MAX_SLAVE_RX_PER_INT) अणु
		val = iproc_i2c_rd_reg(iproc_i2c, S_RX_OFFSET);
		rx_status = (val >> S_RX_STATUS_SHIFT) & S_RX_STATUS_MASK;
		rx_data = ((val >> S_RX_DATA_SHIFT) & S_RX_DATA_MASK);

		अगर (rx_status == I2C_SLAVE_RX_START) अणु
			/* Start of SMBUS Master ग_लिखो */
			i2c_slave_event(iproc_i2c->slave,
					I2C_SLAVE_WRITE_REQUESTED, &rx_data);
			iproc_i2c->rx_start_rcvd = true;
			iproc_i2c->slave_पढ़ो_complete = false;
		पूर्ण अन्यथा अगर (rx_status == I2C_SLAVE_RX_DATA &&
			   iproc_i2c->rx_start_rcvd) अणु
			/* Middle of SMBUS Master ग_लिखो */
			i2c_slave_event(iproc_i2c->slave,
					I2C_SLAVE_WRITE_RECEIVED, &rx_data);
		पूर्ण अन्यथा अगर (rx_status == I2C_SLAVE_RX_END &&
			   iproc_i2c->rx_start_rcvd) अणु
			/* End of SMBUS Master ग_लिखो */
			अगर (iproc_i2c->slave_rx_only)
				i2c_slave_event(iproc_i2c->slave,
						I2C_SLAVE_WRITE_RECEIVED,
						&rx_data);

			i2c_slave_event(iproc_i2c->slave, I2C_SLAVE_STOP,
					&rx_data);
		पूर्ण अन्यथा अगर (rx_status == I2C_SLAVE_RX_FIFO_EMPTY) अणु
			iproc_i2c->rx_start_rcvd = false;
			iproc_i2c->slave_पढ़ो_complete = true;
			अवरोध;
		पूर्ण

		rx_bytes++;
	पूर्ण
पूर्ण

अटल व्योम slave_rx_tasklet_fn(अचिन्हित दीर्घ data)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = (काष्ठा bcm_iproc_i2c_dev *)data;
	u32 पूर्णांक_clr;

	bcm_iproc_i2c_slave_पढ़ो(iproc_i2c);

	/* clear pending IS_S_RX_EVENT_SHIFT पूर्णांकerrupt */
	पूर्णांक_clr = BIT(IS_S_RX_EVENT_SHIFT);

	अगर (!iproc_i2c->slave_rx_only && iproc_i2c->slave_पढ़ो_complete) अणु
		/*
		 * In हाल of single byte master-पढ़ो request,
		 * IS_S_TX_UNDERRUN_SHIFT event is generated beक्रमe
		 * IS_S_START_BUSY_SHIFT event. Hence start slave data send
		 * from first IS_S_TX_UNDERRUN_SHIFT event.
		 *
		 * This means करोn't send any data from slave when
		 * IS_S_RD_EVENT_SHIFT event is generated अन्यथा it will increment
		 * eeprom or other backend slave driver पढ़ो poपूर्णांकer twice.
		 */
		iproc_i2c->tx_underrun = 0;
		iproc_i2c->slave_पूर्णांक_mask |= BIT(IE_S_TX_UNDERRUN_SHIFT);

		/* clear IS_S_RD_EVENT_SHIFT पूर्णांकerrupt */
		पूर्णांक_clr |= BIT(IS_S_RD_EVENT_SHIFT);
	पूर्ण

	/* clear slave पूर्णांकerrupt */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, पूर्णांक_clr);
	/* enable slave पूर्णांकerrupts */
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, iproc_i2c->slave_पूर्णांक_mask);
पूर्ण

अटल bool bcm_iproc_i2c_slave_isr(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
				    u32 status)
अणु
	u32 val;
	u8 value;

	/*
	 * Slave events in हाल of master-ग_लिखो, master-ग_लिखो-पढ़ो and,
	 * master-पढ़ो
	 *
	 * Master-ग_लिखो     : only IS_S_RX_EVENT_SHIFT event
	 * Master-ग_लिखो-पढ़ो: both IS_S_RX_EVENT_SHIFT and IS_S_RD_EVENT_SHIFT
	 *                    events
	 * Master-पढ़ो      : both IS_S_RX_EVENT_SHIFT and IS_S_RD_EVENT_SHIFT
	 *                    events or only IS_S_RD_EVENT_SHIFT
	 *
	 * iproc has a slave rx fअगरo size of 64 bytes. Rx fअगरo full पूर्णांकerrupt
	 * (IS_S_RX_FIFO_FULL_SHIFT) will be generated when RX fअगरo becomes
	 * full. This can happen अगर Master issues ग_लिखो requests of more than
	 * 64 bytes.
	 */
	अगर (status & BIT(IS_S_RX_EVENT_SHIFT) ||
	    status & BIT(IS_S_RD_EVENT_SHIFT) ||
	    status & BIT(IS_S_RX_FIFO_FULL_SHIFT)) अणु
		/* disable slave पूर्णांकerrupts */
		val = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		val &= ~iproc_i2c->slave_पूर्णांक_mask;
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);

		अगर (status & BIT(IS_S_RD_EVENT_SHIFT))
			/* Master-ग_लिखो-पढ़ो request */
			iproc_i2c->slave_rx_only = false;
		अन्यथा
			/* Master-ग_लिखो request only */
			iproc_i2c->slave_rx_only = true;

		/* schedule tasklet to पढ़ो data later */
		tasklet_schedule(&iproc_i2c->slave_rx_tasklet);

		/*
		 * clear only IS_S_RX_EVENT_SHIFT and
		 * IS_S_RX_FIFO_FULL_SHIFT पूर्णांकerrupt.
		 */
		val = BIT(IS_S_RX_EVENT_SHIFT);
		अगर (status & BIT(IS_S_RX_FIFO_FULL_SHIFT))
			val |= BIT(IS_S_RX_FIFO_FULL_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, val);
	पूर्ण

	अगर (status & BIT(IS_S_TX_UNDERRUN_SHIFT)) अणु
		iproc_i2c->tx_underrun++;
		अगर (iproc_i2c->tx_underrun == 1)
			/* Start of SMBUS क्रम Master Read */
			i2c_slave_event(iproc_i2c->slave,
					I2C_SLAVE_READ_REQUESTED,
					&value);
		अन्यथा
			/* Master पढ़ो other than start */
			i2c_slave_event(iproc_i2c->slave,
					I2C_SLAVE_READ_PROCESSED,
					&value);

		iproc_i2c_wr_reg(iproc_i2c, S_TX_OFFSET, value);
		/* start transfer */
		val = BIT(S_CMD_START_BUSY_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, S_CMD_OFFSET, val);

		/* clear पूर्णांकerrupt */
		iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET,
				 BIT(IS_S_TX_UNDERRUN_SHIFT));
	पूर्ण

	/* Stop received from master in हाल of master पढ़ो transaction */
	अगर (status & BIT(IS_S_START_BUSY_SHIFT)) अणु
		/*
		 * Disable पूर्णांकerrupt क्रम TX FIFO becomes empty and
		 * less than PKT_LENGTH bytes were output on the SMBUS
		 */
		iproc_i2c->slave_पूर्णांक_mask &= ~BIT(IE_S_TX_UNDERRUN_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET,
				 iproc_i2c->slave_पूर्णांक_mask);

		/* End of SMBUS क्रम Master Read */
		val = BIT(S_TX_WR_STATUS_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, S_TX_OFFSET, val);

		val = BIT(S_CMD_START_BUSY_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, S_CMD_OFFSET, val);

		/* flush TX FIFOs */
		val = iproc_i2c_rd_reg(iproc_i2c, S_FIFO_CTRL_OFFSET);
		val |= (BIT(S_FIFO_TX_FLUSH_SHIFT));
		iproc_i2c_wr_reg(iproc_i2c, S_FIFO_CTRL_OFFSET, val);

		i2c_slave_event(iproc_i2c->slave, I2C_SLAVE_STOP, &value);

		/* clear पूर्णांकerrupt */
		iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET,
				 BIT(IS_S_START_BUSY_SHIFT));
	पूर्ण

	/* check slave transmit status only अगर slave is transmitting */
	अगर (!iproc_i2c->slave_rx_only)
		bcm_iproc_i2c_check_slave_status(iproc_i2c);

	वापस true;
पूर्ण

अटल व्योम bcm_iproc_i2c_पढ़ो_valid_bytes(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	काष्ठा i2c_msg *msg = iproc_i2c->msg;
	uपूर्णांक32_t val;

	/* Read valid data from RX FIFO */
	जबतक (iproc_i2c->rx_bytes < msg->len) अणु
		val = iproc_i2c_rd_reg(iproc_i2c, M_RX_OFFSET);

		/* rx fअगरo empty */
		अगर (!((val >> M_RX_STATUS_SHIFT) & M_RX_STATUS_MASK))
			अवरोध;

		msg->buf[iproc_i2c->rx_bytes] =
			(val >> M_RX_DATA_SHIFT) & M_RX_DATA_MASK;
		iproc_i2c->rx_bytes++;
	पूर्ण
पूर्ण

अटल व्योम bcm_iproc_i2c_send(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	काष्ठा i2c_msg *msg = iproc_i2c->msg;
	अचिन्हित पूर्णांक tx_bytes = msg->len - iproc_i2c->tx_bytes;
	अचिन्हित पूर्णांक i;
	u32 val;

	/* can only fill up to the FIFO size */
	tx_bytes = min_t(अचिन्हित पूर्णांक, tx_bytes, M_TX_RX_FIFO_SIZE);
	क्रम (i = 0; i < tx_bytes; i++) अणु
		/* start from where we left over */
		अचिन्हित पूर्णांक idx = iproc_i2c->tx_bytes + i;

		val = msg->buf[idx];

		/* mark the last byte */
		अगर (idx == msg->len - 1) अणु
			val |= BIT(M_TX_WR_STATUS_SHIFT);

			अगर (iproc_i2c->irq) अणु
				u32 पंचांगp;

				/*
				 * Since this is the last byte, we should now
				 * disable TX FIFO underrun पूर्णांकerrupt
				 */
				पंचांगp = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
				पंचांगp &= ~BIT(IE_M_TX_UNDERRUN_SHIFT);
				iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET,
						 पंचांगp);
			पूर्ण
		पूर्ण

		/* load data पूर्णांकo TX FIFO */
		iproc_i2c_wr_reg(iproc_i2c, M_TX_OFFSET, val);
	पूर्ण

	/* update number of transferred bytes */
	iproc_i2c->tx_bytes += tx_bytes;
पूर्ण

अटल व्योम bcm_iproc_i2c_पढ़ो(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	काष्ठा i2c_msg *msg = iproc_i2c->msg;
	u32 bytes_left, val;

	bcm_iproc_i2c_पढ़ो_valid_bytes(iproc_i2c);
	bytes_left = msg->len - iproc_i2c->rx_bytes;
	अगर (bytes_left == 0) अणु
		अगर (iproc_i2c->irq) अणु
			/* finished पढ़ोing all data, disable rx thld event */
			val = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
			val &= ~BIT(IS_M_RX_THLD_SHIFT);
			iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);
		पूर्ण
	पूर्ण अन्यथा अगर (bytes_left < iproc_i2c->thld_bytes) अणु
		/* set bytes left as threshold */
		val = iproc_i2c_rd_reg(iproc_i2c, M_FIFO_CTRL_OFFSET);
		val &= ~(M_FIFO_RX_THLD_MASK << M_FIFO_RX_THLD_SHIFT);
		val |= (bytes_left << M_FIFO_RX_THLD_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
		iproc_i2c->thld_bytes = bytes_left;
	पूर्ण
	/*
	 * bytes_left >= iproc_i2c->thld_bytes,
	 * hence no need to change the THRESHOLD SET.
	 * It will reमुख्य as iproc_i2c->thld_bytes itself
	 */
पूर्ण

अटल व्योम bcm_iproc_i2c_process_m_event(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
					  u32 status)
अणु
	/* TX FIFO is empty and we have more data to send */
	अगर (status & BIT(IS_M_TX_UNDERRUN_SHIFT))
		bcm_iproc_i2c_send(iproc_i2c);

	/* RX FIFO threshold is reached and data needs to be पढ़ो out */
	अगर (status & BIT(IS_M_RX_THLD_SHIFT))
		bcm_iproc_i2c_पढ़ो(iproc_i2c);

	/* transfer is करोne */
	अगर (status & BIT(IS_M_START_BUSY_SHIFT)) अणु
		iproc_i2c->xfer_is_करोne = 1;
		अगर (iproc_i2c->irq)
			complete(&iproc_i2c->करोne);
	पूर्ण
पूर्ण

अटल irqवापस_t bcm_iproc_i2c_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = data;
	u32 slave_status;
	u32 status;
	bool ret;

	status = iproc_i2c_rd_reg(iproc_i2c, IS_OFFSET);
	/* process only slave पूर्णांकerrupt which are enabled */
	slave_status = status & iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET) &
		       ISR_MASK_SLAVE;

	अगर (slave_status) अणु
		ret = bcm_iproc_i2c_slave_isr(iproc_i2c, slave_status);
		अगर (ret)
			वापस IRQ_HANDLED;
		अन्यथा
			वापस IRQ_NONE;
	पूर्ण

	status &= ISR_MASK;
	अगर (!status)
		वापस IRQ_NONE;

	/* process all master based events */
	bcm_iproc_i2c_process_m_event(iproc_i2c, status);
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_init(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	u32 val;

	/* put controller in reset */
	val = iproc_i2c_rd_reg(iproc_i2c, CFG_OFFSET);
	val |= BIT(CFG_RESET_SHIFT);
	val &= ~(BIT(CFG_EN_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

	/* रुको 100 usec per spec */
	udelay(100);

	/* bring controller out of reset */
	val &= ~(BIT(CFG_RESET_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);

	/* flush TX/RX FIFOs and set RX FIFO threshold to zero */
	val = (BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
	/* disable all पूर्णांकerrupts */
	val = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
	val &= ~(IE_M_ALL_INTERRUPT_MASK <<
			IE_M_ALL_INTERRUPT_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val);

	/* clear all pending पूर्णांकerrupts */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, 0xffffffff);

	वापस 0;
पूर्ण

अटल व्योम bcm_iproc_i2c_enable_disable(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
					 bool enable)
अणु
	u32 val;

	val = iproc_i2c_rd_reg(iproc_i2c, CFG_OFFSET);
	अगर (enable)
		val |= BIT(CFG_EN_SHIFT);
	अन्यथा
		val &= ~BIT(CFG_EN_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, CFG_OFFSET, val);
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_check_status(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
				      काष्ठा i2c_msg *msg)
अणु
	u32 val;

	val = iproc_i2c_rd_reg(iproc_i2c, M_CMD_OFFSET);
	val = (val >> M_CMD_STATUS_SHIFT) & M_CMD_STATUS_MASK;

	चयन (val) अणु
	हाल M_CMD_STATUS_SUCCESS:
		वापस 0;

	हाल M_CMD_STATUS_LOST_ARB:
		dev_dbg(iproc_i2c->device, "lost bus arbitration\n");
		वापस -EAGAIN;

	हाल M_CMD_STATUS_NACK_ADDR:
		dev_dbg(iproc_i2c->device, "NAK addr:0x%02x\n", msg->addr);
		वापस -ENXIO;

	हाल M_CMD_STATUS_NACK_DATA:
		dev_dbg(iproc_i2c->device, "NAK data\n");
		वापस -ENXIO;

	हाल M_CMD_STATUS_TIMEOUT:
		dev_dbg(iproc_i2c->device, "bus timeout\n");
		वापस -ETIMEDOUT;

	हाल M_CMD_STATUS_FIFO_UNDERRUN:
		dev_dbg(iproc_i2c->device, "FIFO under-run\n");
		वापस -ENXIO;

	हाल M_CMD_STATUS_RX_FIFO_FULL:
		dev_dbg(iproc_i2c->device, "RX FIFO full\n");
		वापस -ETIMEDOUT;

	शेष:
		dev_dbg(iproc_i2c->device, "unknown error code=%d\n", val);

		/* re-initialize i2c क्रम recovery */
		bcm_iproc_i2c_enable_disable(iproc_i2c, false);
		bcm_iproc_i2c_init(iproc_i2c);
		bcm_iproc_i2c_enable_disable(iproc_i2c, true);

		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_xfer_रुको(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
				   काष्ठा i2c_msg *msg,
				   u32 cmd)
अणु
	अचिन्हित दीर्घ समय_left = msecs_to_jअगरfies(I2C_TIMEOUT_MSEC);
	u32 val, status;
	पूर्णांक ret;

	iproc_i2c_wr_reg(iproc_i2c, M_CMD_OFFSET, cmd);

	अगर (iproc_i2c->irq) अणु
		समय_left = रुको_क्रम_completion_समयout(&iproc_i2c->करोne,
							समय_left);
		/* disable all पूर्णांकerrupts */
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, 0);
		/* पढ़ो it back to flush the ग_लिखो */
		iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		/* make sure the पूर्णांकerrupt handler isn't running */
		synchronize_irq(iproc_i2c->irq);

	पूर्ण अन्यथा अणु /* polling mode */
		अचिन्हित दीर्घ समयout = jअगरfies + समय_left;

		करो अणु
			status = iproc_i2c_rd_reg(iproc_i2c,
						  IS_OFFSET) & ISR_MASK;
			bcm_iproc_i2c_process_m_event(iproc_i2c, status);
			iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, status);

			अगर (समय_after(jअगरfies, समयout)) अणु
				समय_left = 0;
				अवरोध;
			पूर्ण

			cpu_relax();
			cond_resched();
		पूर्ण जबतक (!iproc_i2c->xfer_is_करोne);
	पूर्ण

	अगर (!समय_left && !iproc_i2c->xfer_is_करोne) अणु
		dev_err(iproc_i2c->device, "transaction timed out\n");

		/* flush both TX/RX FIFOs */
		val = BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
		वापस -ETIMEDOUT;
	पूर्ण

	ret = bcm_iproc_i2c_check_status(iproc_i2c, msg);
	अगर (ret) अणु
		/* flush both TX/RX FIFOs */
		val = BIT(M_FIFO_RX_FLUSH_SHIFT) | BIT(M_FIFO_TX_FLUSH_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, val);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If 'process_call' is true, then this is a multi-msg transfer that requires
 * a repeated start between the messages.
 * More specअगरically, it must be a ग_लिखो (reg) followed by a पढ़ो (data).
 * The i2c quirks are set to enक्रमce this rule.
 */
अटल पूर्णांक bcm_iproc_i2c_xfer_पूर्णांकernal(काष्ठा bcm_iproc_i2c_dev *iproc_i2c,
					काष्ठा i2c_msg *msgs, bool process_call)
अणु
	पूर्णांक i;
	u8 addr;
	u32 val, पंचांगp, val_पूर्णांकr_en;
	अचिन्हित पूर्णांक tx_bytes;
	काष्ठा i2c_msg *msg = &msgs[0];

	/* check अगर bus is busy */
	अगर (!!(iproc_i2c_rd_reg(iproc_i2c,
				M_CMD_OFFSET) & BIT(M_CMD_START_BUSY_SHIFT))) अणु
		dev_warn(iproc_i2c->device, "bus is busy\n");
		वापस -EBUSY;
	पूर्ण

	iproc_i2c->msg = msg;

	/* क्रमmat and load slave address पूर्णांकo the TX FIFO */
	addr = i2c_8bit_addr_from_msg(msg);
	iproc_i2c_wr_reg(iproc_i2c, M_TX_OFFSET, addr);

	/*
	 * For a ग_लिखो transaction, load data पूर्णांकo the TX FIFO. Only allow
	 * loading up to TX FIFO size - 1 bytes of data since the first byte
	 * has been used up by the slave address
	 */
	tx_bytes = min_t(अचिन्हित पूर्णांक, msg->len, M_TX_RX_FIFO_SIZE - 1);
	अगर (!(msg->flags & I2C_M_RD)) अणु
		क्रम (i = 0; i < tx_bytes; i++) अणु
			val = msg->buf[i];

			/* mark the last byte */
			अगर (!process_call && (i == msg->len - 1))
				val |= BIT(M_TX_WR_STATUS_SHIFT);

			iproc_i2c_wr_reg(iproc_i2c, M_TX_OFFSET, val);
		पूर्ण
		iproc_i2c->tx_bytes = tx_bytes;
	पूर्ण

	/* Process the पढ़ो message अगर this is process call */
	अगर (process_call) अणु
		msg++;
		iproc_i2c->msg = msg;  /* poपूर्णांक to second msg */

		/*
		 * The last byte to be sent out should be a slave
		 * address with पढ़ो operation
		 */
		addr = i2c_8bit_addr_from_msg(msg);
		/* mark it the last byte out */
		val = addr | BIT(M_TX_WR_STATUS_SHIFT);
		iproc_i2c_wr_reg(iproc_i2c, M_TX_OFFSET, val);
	पूर्ण

	/* mark as incomplete beक्रमe starting the transaction */
	अगर (iproc_i2c->irq)
		reinit_completion(&iproc_i2c->करोne);

	iproc_i2c->xfer_is_करोne = 0;

	/*
	 * Enable the "start busy" पूर्णांकerrupt, which will be triggered after the
	 * transaction is करोne, i.e., the पूर्णांकernal start_busy bit, transitions
	 * from 1 to 0.
	 */
	val_पूर्णांकr_en = BIT(IE_M_START_BUSY_SHIFT);

	/*
	 * If TX data size is larger than the TX FIFO, need to enable TX
	 * underrun पूर्णांकerrupt, which will be triggerred when the TX FIFO is
	 * empty. When that happens we can then pump more data पूर्णांकo the FIFO
	 */
	अगर (!process_call && !(msg->flags & I2C_M_RD) &&
	    msg->len > iproc_i2c->tx_bytes)
		val_पूर्णांकr_en |= BIT(IE_M_TX_UNDERRUN_SHIFT);

	/*
	 * Now we can activate the transfer. For a पढ़ो operation, specअगरy the
	 * number of bytes to पढ़ो
	 */
	val = BIT(M_CMD_START_BUSY_SHIFT);

	अगर (msg->len == 0) अणु
		/* SMBUS QUICK Command (Read/Write) */
		val |= (M_CMD_PROTOCOL_QUICK << M_CMD_PROTOCOL_SHIFT);
	पूर्ण अन्यथा अगर (msg->flags & I2C_M_RD) अणु
		u32 protocol;

		iproc_i2c->rx_bytes = 0;
		अगर (msg->len > M_RX_FIFO_MAX_THLD_VALUE)
			iproc_i2c->thld_bytes = M_RX_FIFO_THLD_VALUE;
		अन्यथा
			iproc_i2c->thld_bytes = msg->len;

		/* set threshold value */
		पंचांगp = iproc_i2c_rd_reg(iproc_i2c, M_FIFO_CTRL_OFFSET);
		पंचांगp &= ~(M_FIFO_RX_THLD_MASK << M_FIFO_RX_THLD_SHIFT);
		पंचांगp |= iproc_i2c->thld_bytes << M_FIFO_RX_THLD_SHIFT;
		iproc_i2c_wr_reg(iproc_i2c, M_FIFO_CTRL_OFFSET, पंचांगp);

		/* enable the RX threshold पूर्णांकerrupt */
		val_पूर्णांकr_en |= BIT(IE_M_RX_THLD_SHIFT);

		protocol = process_call ?
				M_CMD_PROTOCOL_PROCESS : M_CMD_PROTOCOL_BLK_RD;

		val |= (protocol << M_CMD_PROTOCOL_SHIFT) |
		       (msg->len << M_CMD_RD_CNT_SHIFT);
	पूर्ण अन्यथा अणु
		val |= (M_CMD_PROTOCOL_BLK_WR << M_CMD_PROTOCOL_SHIFT);
	पूर्ण

	अगर (iproc_i2c->irq)
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, val_पूर्णांकr_en);

	वापस bcm_iproc_i2c_xfer_रुको(iproc_i2c, msg, val);
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_xfer(काष्ठा i2c_adapter *adapter,
			      काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = i2c_get_adapdata(adapter);
	bool process_call = false;
	पूर्णांक ret;

	अगर (num == 2) अणु
		/* Repeated start, use process call */
		process_call = true;
		अगर (msgs[1].flags & I2C_M_NOSTART) अणु
			dev_err(iproc_i2c->device, "Invalid repeated start\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	ret = bcm_iproc_i2c_xfer_पूर्णांकernal(iproc_i2c, msgs, process_call);
	अगर (ret) अणु
		dev_dbg(iproc_i2c->device, "xfer failed\n");
		वापस ret;
	पूर्ण

	वापस num;
पूर्ण

अटल uपूर्णांक32_t bcm_iproc_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	u32 val;

	val = I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;

	अगर (adap->algo->reg_slave)
		val |= I2C_FUNC_SLAVE;

	वापस val;
पूर्ण

अटल काष्ठा i2c_algorithm bcm_iproc_algo = अणु
	.master_xfer = bcm_iproc_i2c_xfer,
	.functionality = bcm_iproc_i2c_functionality,
	.reg_slave = bcm_iproc_i2c_reg_slave,
	.unreg_slave = bcm_iproc_i2c_unreg_slave,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks bcm_iproc_i2c_quirks = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
	.max_comb_1st_msg_len = M_TX_RX_FIFO_SIZE,
	.max_पढ़ो_len = M_RX_MAX_READ_LEN,
पूर्ण;

अटल पूर्णांक bcm_iproc_i2c_cfg_speed(काष्ठा bcm_iproc_i2c_dev *iproc_i2c)
अणु
	अचिन्हित पूर्णांक bus_speed;
	u32 val;
	पूर्णांक ret = of_property_पढ़ो_u32(iproc_i2c->device->of_node,
				       "clock-frequency", &bus_speed);
	अगर (ret < 0) अणु
		dev_info(iproc_i2c->device,
			"unable to interpret clock-frequency DT property\n");
		bus_speed = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण

	अगर (bus_speed < I2C_MAX_STANDARD_MODE_FREQ) अणु
		dev_err(iproc_i2c->device, "%d Hz bus speed not supported\n",
			bus_speed);
		dev_err(iproc_i2c->device,
			"valid speeds are 100khz and 400khz\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (bus_speed < I2C_MAX_FAST_MODE_FREQ) अणु
		bus_speed = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण अन्यथा अणु
		bus_speed = I2C_MAX_FAST_MODE_FREQ;
	पूर्ण

	iproc_i2c->bus_speed = bus_speed;
	val = iproc_i2c_rd_reg(iproc_i2c, TIM_CFG_OFFSET);
	val &= ~BIT(TIM_CFG_MODE_400_SHIFT);
	val |= (bus_speed == I2C_MAX_FAST_MODE_FREQ) << TIM_CFG_MODE_400_SHIFT;
	iproc_i2c_wr_reg(iproc_i2c, TIM_CFG_OFFSET, val);

	dev_info(iproc_i2c->device, "bus set to %u Hz\n", bus_speed);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq, ret = 0;
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *res;

	iproc_i2c = devm_kzalloc(&pdev->dev, माप(*iproc_i2c),
				 GFP_KERNEL);
	अगर (!iproc_i2c)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, iproc_i2c);
	iproc_i2c->device = &pdev->dev;
	iproc_i2c->type =
		(क्रमागत bcm_iproc_i2c_type)of_device_get_match_data(&pdev->dev);
	init_completion(&iproc_i2c->करोne);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iproc_i2c->base = devm_ioremap_resource(iproc_i2c->device, res);
	अगर (IS_ERR(iproc_i2c->base))
		वापस PTR_ERR(iproc_i2c->base);

	अगर (iproc_i2c->type == IPROC_I2C_NIC) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		iproc_i2c->idm_base = devm_ioremap_resource(iproc_i2c->device,
							    res);
		अगर (IS_ERR(iproc_i2c->idm_base))
			वापस PTR_ERR(iproc_i2c->idm_base);

		ret = of_property_पढ़ो_u32(iproc_i2c->device->of_node,
					   "brcm,ape-hsls-addr-mask",
					   &iproc_i2c->ape_addr_mask);
		अगर (ret < 0) अणु
			dev_err(iproc_i2c->device,
				"'brcm,ape-hsls-addr-mask' missing\n");
			वापस -EINVAL;
		पूर्ण

		spin_lock_init(&iproc_i2c->idm_lock);

		/* no slave support */
		bcm_iproc_algo.reg_slave = शून्य;
		bcm_iproc_algo.unreg_slave = शून्य;
	पूर्ण

	ret = bcm_iproc_i2c_init(iproc_i2c);
	अगर (ret)
		वापस ret;

	ret = bcm_iproc_i2c_cfg_speed(iproc_i2c);
	अगर (ret)
		वापस ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq > 0) अणु
		ret = devm_request_irq(iproc_i2c->device, irq,
				       bcm_iproc_i2c_isr, 0, pdev->name,
				       iproc_i2c);
		अगर (ret < 0) अणु
			dev_err(iproc_i2c->device,
				"unable to request irq %i\n", irq);
			वापस ret;
		पूर्ण

		iproc_i2c->irq = irq;
	पूर्ण अन्यथा अणु
		dev_warn(iproc_i2c->device,
			 "no irq resource, falling back to poll mode\n");
	पूर्ण

	bcm_iproc_i2c_enable_disable(iproc_i2c, true);

	adap = &iproc_i2c->adapter;
	i2c_set_adapdata(adap, iproc_i2c);
	snम_लिखो(adap->name, माप(adap->name),
		"Broadcom iProc (%s)",
		of_node_full_name(iproc_i2c->device->of_node));
	adap->algo = &bcm_iproc_algo;
	adap->quirks = &bcm_iproc_i2c_quirks;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	वापस i2c_add_adapter(adap);
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = platक्रमm_get_drvdata(pdev);

	अगर (iproc_i2c->irq) अणु
		/*
		 * Make sure there's no pending पूर्णांकerrupt when we हटाओ the
		 * adapter
		 */
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, 0);
		iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		synchronize_irq(iproc_i2c->irq);
	पूर्ण

	i2c_del_adapter(&iproc_i2c->adapter);
	bcm_iproc_i2c_enable_disable(iproc_i2c, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक bcm_iproc_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = dev_get_drvdata(dev);

	अगर (iproc_i2c->irq) अणु
		/*
		 * Make sure there's no pending पूर्णांकerrupt when we go पूर्णांकo
		 * suspend
		 */
		iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, 0);
		iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
		synchronize_irq(iproc_i2c->irq);
	पूर्ण

	/* now disable the controller */
	bcm_iproc_i2c_enable_disable(iproc_i2c, false);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 val;

	/*
	 * Power करोमुख्य could have been shut off completely in प्रणाली deep
	 * sleep, so re-initialize the block here
	 */
	ret = bcm_iproc_i2c_init(iproc_i2c);
	अगर (ret)
		वापस ret;

	/* configure to the desired bus speed */
	val = iproc_i2c_rd_reg(iproc_i2c, TIM_CFG_OFFSET);
	val &= ~BIT(TIM_CFG_MODE_400_SHIFT);
	val |= (iproc_i2c->bus_speed == I2C_MAX_FAST_MODE_FREQ) << TIM_CFG_MODE_400_SHIFT;
	iproc_i2c_wr_reg(iproc_i2c, TIM_CFG_OFFSET, val);

	bcm_iproc_i2c_enable_disable(iproc_i2c, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bcm_iproc_i2c_pm_ops = अणु
	.suspend_late = &bcm_iproc_i2c_suspend,
	.resume_early = &bcm_iproc_i2c_resume
पूर्ण;

#घोषणा BCM_IPROC_I2C_PM_OPS (&bcm_iproc_i2c_pm_ops)
#अन्यथा
#घोषणा BCM_IPROC_I2C_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */


अटल पूर्णांक bcm_iproc_i2c_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = i2c_get_adapdata(slave->adapter);

	अगर (iproc_i2c->slave)
		वापस -EBUSY;

	अगर (slave->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	iproc_i2c->slave = slave;

	tasklet_init(&iproc_i2c->slave_rx_tasklet, slave_rx_tasklet_fn,
		     (अचिन्हित दीर्घ)iproc_i2c);

	bcm_iproc_i2c_slave_init(iproc_i2c, false);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_iproc_i2c_unreg_slave(काष्ठा i2c_client *slave)
अणु
	u32 पंचांगp;
	काष्ठा bcm_iproc_i2c_dev *iproc_i2c = i2c_get_adapdata(slave->adapter);

	अगर (!iproc_i2c->slave)
		वापस -EINVAL;

	disable_irq(iproc_i2c->irq);

	/* disable all slave पूर्णांकerrupts */
	पंचांगp = iproc_i2c_rd_reg(iproc_i2c, IE_OFFSET);
	पंचांगp &= ~(IE_S_ALL_INTERRUPT_MASK <<
			IE_S_ALL_INTERRUPT_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, IE_OFFSET, पंचांगp);

	tasklet_समाप्त(&iproc_i2c->slave_rx_tasklet);

	/* Erase the slave address programmed */
	पंचांगp = iproc_i2c_rd_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET);
	पंचांगp &= ~BIT(S_CFG_EN_NIC_SMB_ADDR3_SHIFT);
	iproc_i2c_wr_reg(iproc_i2c, S_CFG_SMBUS_ADDR_OFFSET, पंचांगp);

	/* flush TX/RX FIFOs */
	पंचांगp = (BIT(S_FIFO_RX_FLUSH_SHIFT) | BIT(S_FIFO_TX_FLUSH_SHIFT));
	iproc_i2c_wr_reg(iproc_i2c, S_FIFO_CTRL_OFFSET, पंचांगp);

	/* clear all pending slave पूर्णांकerrupts */
	iproc_i2c_wr_reg(iproc_i2c, IS_OFFSET, ISR_MASK_SLAVE);

	iproc_i2c->slave = शून्य;

	enable_irq(iproc_i2c->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_iproc_i2c_of_match[] = अणु
	अणु
		.compatible = "brcm,iproc-i2c",
		.data = (पूर्णांक *)IPROC_I2C,
	पूर्ण, अणु
		.compatible = "brcm,iproc-nic-i2c",
		.data = (पूर्णांक *)IPROC_I2C_NIC,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_iproc_i2c_of_match);

अटल काष्ठा platक्रमm_driver bcm_iproc_i2c_driver = अणु
	.driver = अणु
		.name = "bcm-iproc-i2c",
		.of_match_table = bcm_iproc_i2c_of_match,
		.pm = BCM_IPROC_I2C_PM_OPS,
	पूर्ण,
	.probe = bcm_iproc_i2c_probe,
	.हटाओ = bcm_iproc_i2c_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm_iproc_i2c_driver);

MODULE_AUTHOR("Ray Jui <rjui@broadcom.com>");
MODULE_DESCRIPTION("Broadcom iProc I2C Driver");
MODULE_LICENSE("GPL v2");
