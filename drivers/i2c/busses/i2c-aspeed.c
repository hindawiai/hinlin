<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Aspeed 24XX/25XX I2C Controller.
 *
 *  Copyright (C) 2012-2017 ASPEED Technology Inc.
 *  Copyright 2017 IBM Corporation
 *  Copyright 2017 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

/* I2C Register */
#घोषणा ASPEED_I2C_FUN_CTRL_REG				0x00
#घोषणा ASPEED_I2C_AC_TIMING_REG1			0x04
#घोषणा ASPEED_I2C_AC_TIMING_REG2			0x08
#घोषणा ASPEED_I2C_INTR_CTRL_REG			0x0c
#घोषणा ASPEED_I2C_INTR_STS_REG				0x10
#घोषणा ASPEED_I2C_CMD_REG				0x14
#घोषणा ASPEED_I2C_DEV_ADDR_REG				0x18
#घोषणा ASPEED_I2C_BYTE_BUF_REG				0x20

/* Global Register Definition */
/* 0x00 : I2C Interrupt Status Register  */
/* 0x08 : I2C Interrupt Target Assignment  */

/* Device Register Definition */
/* 0x00 : I2CD Function Control Register  */
#घोषणा ASPEED_I2CD_MULTI_MASTER_DIS			BIT(15)
#घोषणा ASPEED_I2CD_SDA_DRIVE_1T_EN			BIT(8)
#घोषणा ASPEED_I2CD_M_SDA_DRIVE_1T_EN			BIT(7)
#घोषणा ASPEED_I2CD_M_HIGH_SPEED_EN			BIT(6)
#घोषणा ASPEED_I2CD_SLAVE_EN				BIT(1)
#घोषणा ASPEED_I2CD_MASTER_EN				BIT(0)

/* 0x04 : I2CD Clock and AC Timing Control Register #1 */
#घोषणा ASPEED_I2CD_TIME_TBUF_MASK			GENMASK(31, 28)
#घोषणा ASPEED_I2CD_TIME_THDSTA_MASK			GENMASK(27, 24)
#घोषणा ASPEED_I2CD_TIME_TACST_MASK			GENMASK(23, 20)
#घोषणा ASPEED_I2CD_TIME_SCL_HIGH_SHIFT			16
#घोषणा ASPEED_I2CD_TIME_SCL_HIGH_MASK			GENMASK(19, 16)
#घोषणा ASPEED_I2CD_TIME_SCL_LOW_SHIFT			12
#घोषणा ASPEED_I2CD_TIME_SCL_LOW_MASK			GENMASK(15, 12)
#घोषणा ASPEED_I2CD_TIME_BASE_DIVISOR_MASK		GENMASK(3, 0)
#घोषणा ASPEED_I2CD_TIME_SCL_REG_MAX			GENMASK(3, 0)
/* 0x08 : I2CD Clock and AC Timing Control Register #2 */
#घोषणा ASPEED_NO_TIMEOUT_CTRL				0

/* 0x0c : I2CD Interrupt Control Register &
 * 0x10 : I2CD Interrupt Status Register
 *
 * These share bit definitions, so use the same values क्रम the enable &
 * status bits.
 */
#घोषणा ASPEED_I2CD_INTR_RECV_MASK			0xf000ffff
#घोषणा ASPEED_I2CD_INTR_SDA_DL_TIMEOUT			BIT(14)
#घोषणा ASPEED_I2CD_INTR_BUS_RECOVER_DONE		BIT(13)
#घोषणा ASPEED_I2CD_INTR_SLAVE_MATCH			BIT(7)
#घोषणा ASPEED_I2CD_INTR_SCL_TIMEOUT			BIT(6)
#घोषणा ASPEED_I2CD_INTR_ABNORMAL			BIT(5)
#घोषणा ASPEED_I2CD_INTR_NORMAL_STOP			BIT(4)
#घोषणा ASPEED_I2CD_INTR_ARBIT_LOSS			BIT(3)
#घोषणा ASPEED_I2CD_INTR_RX_DONE			BIT(2)
#घोषणा ASPEED_I2CD_INTR_TX_NAK				BIT(1)
#घोषणा ASPEED_I2CD_INTR_TX_ACK				BIT(0)
#घोषणा ASPEED_I2CD_INTR_MASTER_ERRORS					       \
		(ASPEED_I2CD_INTR_SDA_DL_TIMEOUT |			       \
		 ASPEED_I2CD_INTR_SCL_TIMEOUT |				       \
		 ASPEED_I2CD_INTR_ABNORMAL |				       \
		 ASPEED_I2CD_INTR_ARBIT_LOSS)
#घोषणा ASPEED_I2CD_INTR_ALL						       \
		(ASPEED_I2CD_INTR_SDA_DL_TIMEOUT |			       \
		 ASPEED_I2CD_INTR_BUS_RECOVER_DONE |			       \
		 ASPEED_I2CD_INTR_SCL_TIMEOUT |				       \
		 ASPEED_I2CD_INTR_ABNORMAL |				       \
		 ASPEED_I2CD_INTR_NORMAL_STOP |				       \
		 ASPEED_I2CD_INTR_ARBIT_LOSS |				       \
		 ASPEED_I2CD_INTR_RX_DONE |				       \
		 ASPEED_I2CD_INTR_TX_NAK |				       \
		 ASPEED_I2CD_INTR_TX_ACK)

/* 0x14 : I2CD Command/Status Register   */
#घोषणा ASPEED_I2CD_SCL_LINE_STS			BIT(18)
#घोषणा ASPEED_I2CD_SDA_LINE_STS			BIT(17)
#घोषणा ASPEED_I2CD_BUS_BUSY_STS			BIT(16)
#घोषणा ASPEED_I2CD_BUS_RECOVER_CMD			BIT(11)

/* Command Bit */
#घोषणा ASPEED_I2CD_M_STOP_CMD				BIT(5)
#घोषणा ASPEED_I2CD_M_S_RX_CMD_LAST			BIT(4)
#घोषणा ASPEED_I2CD_M_RX_CMD				BIT(3)
#घोषणा ASPEED_I2CD_S_TX_CMD				BIT(2)
#घोषणा ASPEED_I2CD_M_TX_CMD				BIT(1)
#घोषणा ASPEED_I2CD_M_START_CMD				BIT(0)
#घोषणा ASPEED_I2CD_MASTER_CMDS_MASK					       \
		(ASPEED_I2CD_M_STOP_CMD |				       \
		 ASPEED_I2CD_M_S_RX_CMD_LAST |				       \
		 ASPEED_I2CD_M_RX_CMD |					       \
		 ASPEED_I2CD_M_TX_CMD |					       \
		 ASPEED_I2CD_M_START_CMD)

/* 0x18 : I2CD Slave Device Address Register   */
#घोषणा ASPEED_I2CD_DEV_ADDR_MASK			GENMASK(6, 0)

क्रमागत aspeed_i2c_master_state अणु
	ASPEED_I2C_MASTER_INACTIVE,
	ASPEED_I2C_MASTER_PENDING,
	ASPEED_I2C_MASTER_START,
	ASPEED_I2C_MASTER_TX_FIRST,
	ASPEED_I2C_MASTER_TX,
	ASPEED_I2C_MASTER_RX_FIRST,
	ASPEED_I2C_MASTER_RX,
	ASPEED_I2C_MASTER_STOP,
पूर्ण;

क्रमागत aspeed_i2c_slave_state अणु
	ASPEED_I2C_SLAVE_INACTIVE,
	ASPEED_I2C_SLAVE_START,
	ASPEED_I2C_SLAVE_READ_REQUESTED,
	ASPEED_I2C_SLAVE_READ_PROCESSED,
	ASPEED_I2C_SLAVE_WRITE_REQUESTED,
	ASPEED_I2C_SLAVE_WRITE_RECEIVED,
	ASPEED_I2C_SLAVE_STOP,
पूर्ण;

काष्ठा aspeed_i2c_bus अणु
	काष्ठा i2c_adapter		adap;
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	काष्ठा reset_control		*rst;
	/* Synchronizes I/O mem access to base. */
	spinlock_t			lock;
	काष्ठा completion		cmd_complete;
	u32				(*get_clk_reg_val)(काष्ठा device *dev,
							   u32 भागisor);
	अचिन्हित दीर्घ			parent_clk_frequency;
	u32				bus_frequency;
	/* Transaction state. */
	क्रमागत aspeed_i2c_master_state	master_state;
	काष्ठा i2c_msg			*msgs;
	माप_प्रकार				buf_index;
	माप_प्रकार				msgs_index;
	माप_प्रकार				msgs_count;
	bool				send_stop;
	पूर्णांक				cmd_err;
	/* Protected only by i2c_lock_bus */
	पूर्णांक				master_xfer_result;
	/* Multi-master */
	bool				multi_master;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	काष्ठा i2c_client		*slave;
	क्रमागत aspeed_i2c_slave_state	slave_state;
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */
पूर्ण;

अटल पूर्णांक aspeed_i2c_reset(काष्ठा aspeed_i2c_bus *bus);

अटल पूर्णांक aspeed_i2c_recover_bus(काष्ठा aspeed_i2c_bus *bus)
अणु
	अचिन्हित दीर्घ समय_left, flags;
	पूर्णांक ret = 0;
	u32 command;

	spin_lock_irqsave(&bus->lock, flags);
	command = पढ़ोl(bus->base + ASPEED_I2C_CMD_REG);

	अगर (command & ASPEED_I2CD_SDA_LINE_STS) अणु
		/* Bus is idle: no recovery needed. */
		अगर (command & ASPEED_I2CD_SCL_LINE_STS)
			जाओ out;
		dev_dbg(bus->dev, "SCL hung (state %x), attempting recovery\n",
			command);

		reinit_completion(&bus->cmd_complete);
		ग_लिखोl(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_REG);
		spin_unlock_irqrestore(&bus->lock, flags);

		समय_left = रुको_क्रम_completion_समयout(
				&bus->cmd_complete, bus->adap.समयout);

		spin_lock_irqsave(&bus->lock, flags);
		अगर (समय_left == 0)
			जाओ reset_out;
		अन्यथा अगर (bus->cmd_err)
			जाओ reset_out;
		/* Recovery failed. */
		अन्यथा अगर (!(पढ़ोl(bus->base + ASPEED_I2C_CMD_REG) &
			   ASPEED_I2CD_SCL_LINE_STS))
			जाओ reset_out;
	/* Bus error. */
	पूर्ण अन्यथा अणु
		dev_dbg(bus->dev, "SDA hung (state %x), attempting recovery\n",
			command);

		reinit_completion(&bus->cmd_complete);
		/* Writes 1 to 8 SCL घड़ी cycles until SDA is released. */
		ग_लिखोl(ASPEED_I2CD_BUS_RECOVER_CMD,
		       bus->base + ASPEED_I2C_CMD_REG);
		spin_unlock_irqrestore(&bus->lock, flags);

		समय_left = रुको_क्रम_completion_समयout(
				&bus->cmd_complete, bus->adap.समयout);

		spin_lock_irqsave(&bus->lock, flags);
		अगर (समय_left == 0)
			जाओ reset_out;
		अन्यथा अगर (bus->cmd_err)
			जाओ reset_out;
		/* Recovery failed. */
		अन्यथा अगर (!(पढ़ोl(bus->base + ASPEED_I2C_CMD_REG) &
			   ASPEED_I2CD_SDA_LINE_STS))
			जाओ reset_out;
	पूर्ण

out:
	spin_unlock_irqrestore(&bus->lock, flags);

	वापस ret;

reset_out:
	spin_unlock_irqrestore(&bus->lock, flags);

	वापस aspeed_i2c_reset(bus);
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
अटल u32 aspeed_i2c_slave_irq(काष्ठा aspeed_i2c_bus *bus, u32 irq_status)
अणु
	u32 command, irq_handled = 0;
	काष्ठा i2c_client *slave = bus->slave;
	u8 value;

	अगर (!slave)
		वापस 0;

	command = पढ़ोl(bus->base + ASPEED_I2C_CMD_REG);

	/* Slave was requested, restart state machine. */
	अगर (irq_status & ASPEED_I2CD_INTR_SLAVE_MATCH) अणु
		irq_handled |= ASPEED_I2CD_INTR_SLAVE_MATCH;
		bus->slave_state = ASPEED_I2C_SLAVE_START;
	पूर्ण

	/* Slave is not currently active, irq was क्रम someone अन्यथा. */
	अगर (bus->slave_state == ASPEED_I2C_SLAVE_INACTIVE)
		वापस irq_handled;

	dev_dbg(bus->dev, "slave irq status 0x%08x, cmd 0x%08x\n",
		irq_status, command);

	/* Slave was sent something. */
	अगर (irq_status & ASPEED_I2CD_INTR_RX_DONE) अणु
		value = पढ़ोl(bus->base + ASPEED_I2C_BYTE_BUF_REG) >> 8;
		/* Handle address frame. */
		अगर (bus->slave_state == ASPEED_I2C_SLAVE_START) अणु
			अगर (value & 0x1)
				bus->slave_state =
						ASPEED_I2C_SLAVE_READ_REQUESTED;
			अन्यथा
				bus->slave_state =
						ASPEED_I2C_SLAVE_WRITE_REQUESTED;
		पूर्ण
		irq_handled |= ASPEED_I2CD_INTR_RX_DONE;
	पूर्ण

	/* Slave was asked to stop. */
	अगर (irq_status & ASPEED_I2CD_INTR_NORMAL_STOP) अणु
		irq_handled |= ASPEED_I2CD_INTR_NORMAL_STOP;
		bus->slave_state = ASPEED_I2C_SLAVE_STOP;
	पूर्ण
	अगर (irq_status & ASPEED_I2CD_INTR_TX_NAK &&
	    bus->slave_state == ASPEED_I2C_SLAVE_READ_PROCESSED) अणु
		irq_handled |= ASPEED_I2CD_INTR_TX_NAK;
		bus->slave_state = ASPEED_I2C_SLAVE_STOP;
	पूर्ण

	चयन (bus->slave_state) अणु
	हाल ASPEED_I2C_SLAVE_READ_REQUESTED:
		अगर (unlikely(irq_status & ASPEED_I2CD_INTR_TX_ACK))
			dev_err(bus->dev, "Unexpected ACK on read request.\n");
		bus->slave_state = ASPEED_I2C_SLAVE_READ_PROCESSED;
		i2c_slave_event(slave, I2C_SLAVE_READ_REQUESTED, &value);
		ग_लिखोl(value, bus->base + ASPEED_I2C_BYTE_BUF_REG);
		ग_लिखोl(ASPEED_I2CD_S_TX_CMD, bus->base + ASPEED_I2C_CMD_REG);
		अवरोध;
	हाल ASPEED_I2C_SLAVE_READ_PROCESSED:
		अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_TX_ACK))) अणु
			dev_err(bus->dev,
				"Expected ACK after processed read.\n");
			अवरोध;
		पूर्ण
		irq_handled |= ASPEED_I2CD_INTR_TX_ACK;
		i2c_slave_event(slave, I2C_SLAVE_READ_PROCESSED, &value);
		ग_लिखोl(value, bus->base + ASPEED_I2C_BYTE_BUF_REG);
		ग_लिखोl(ASPEED_I2CD_S_TX_CMD, bus->base + ASPEED_I2C_CMD_REG);
		अवरोध;
	हाल ASPEED_I2C_SLAVE_WRITE_REQUESTED:
		bus->slave_state = ASPEED_I2C_SLAVE_WRITE_RECEIVED;
		i2c_slave_event(slave, I2C_SLAVE_WRITE_REQUESTED, &value);
		अवरोध;
	हाल ASPEED_I2C_SLAVE_WRITE_RECEIVED:
		i2c_slave_event(slave, I2C_SLAVE_WRITE_RECEIVED, &value);
		अवरोध;
	हाल ASPEED_I2C_SLAVE_STOP:
		i2c_slave_event(slave, I2C_SLAVE_STOP, &value);
		bus->slave_state = ASPEED_I2C_SLAVE_INACTIVE;
		अवरोध;
	हाल ASPEED_I2C_SLAVE_START:
		/* Slave was just started. Waiting क्रम the next event. */;
		अवरोध;
	शेष:
		dev_err(bus->dev, "unknown slave_state: %d\n",
			bus->slave_state);
		bus->slave_state = ASPEED_I2C_SLAVE_INACTIVE;
		अवरोध;
	पूर्ण

	वापस irq_handled;
पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

/* precondition: bus.lock has been acquired. */
अटल व्योम aspeed_i2c_करो_start(काष्ठा aspeed_i2c_bus *bus)
अणु
	u32 command = ASPEED_I2CD_M_START_CMD | ASPEED_I2CD_M_TX_CMD;
	काष्ठा i2c_msg *msg = &bus->msgs[bus->msgs_index];
	u8 slave_addr = i2c_8bit_addr_from_msg(msg);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/*
	 * If it's requested in the middle of a slave session, set the master
	 * state to 'pending' then H/W will जारी handling this master
	 * command when the bus comes back to the idle state.
	 */
	अगर (bus->slave_state != ASPEED_I2C_SLAVE_INACTIVE) अणु
		bus->master_state = ASPEED_I2C_MASTER_PENDING;
		वापस;
	पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

	bus->master_state = ASPEED_I2C_MASTER_START;
	bus->buf_index = 0;

	अगर (msg->flags & I2C_M_RD) अणु
		command |= ASPEED_I2CD_M_RX_CMD;
		/* Need to let the hardware know to NACK after RX. */
		अगर (msg->len == 1 && !(msg->flags & I2C_M_RECV_LEN))
			command |= ASPEED_I2CD_M_S_RX_CMD_LAST;
	पूर्ण

	ग_लिखोl(slave_addr, bus->base + ASPEED_I2C_BYTE_BUF_REG);
	ग_लिखोl(command, bus->base + ASPEED_I2C_CMD_REG);
पूर्ण

/* precondition: bus.lock has been acquired. */
अटल व्योम aspeed_i2c_करो_stop(काष्ठा aspeed_i2c_bus *bus)
अणु
	bus->master_state = ASPEED_I2C_MASTER_STOP;
	ग_लिखोl(ASPEED_I2CD_M_STOP_CMD, bus->base + ASPEED_I2C_CMD_REG);
पूर्ण

/* precondition: bus.lock has been acquired. */
अटल व्योम aspeed_i2c_next_msg_or_stop(काष्ठा aspeed_i2c_bus *bus)
अणु
	अगर (bus->msgs_index + 1 < bus->msgs_count) अणु
		bus->msgs_index++;
		aspeed_i2c_करो_start(bus);
	पूर्ण अन्यथा अणु
		aspeed_i2c_करो_stop(bus);
	पूर्ण
पूर्ण

अटल पूर्णांक aspeed_i2c_is_irq_error(u32 irq_status)
अणु
	अगर (irq_status & ASPEED_I2CD_INTR_ARBIT_LOSS)
		वापस -EAGAIN;
	अगर (irq_status & (ASPEED_I2CD_INTR_SDA_DL_TIMEOUT |
			  ASPEED_I2CD_INTR_SCL_TIMEOUT))
		वापस -EBUSY;
	अगर (irq_status & (ASPEED_I2CD_INTR_ABNORMAL))
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल u32 aspeed_i2c_master_irq(काष्ठा aspeed_i2c_bus *bus, u32 irq_status)
अणु
	u32 irq_handled = 0, command = 0;
	काष्ठा i2c_msg *msg;
	u8 recv_byte;
	पूर्णांक ret;

	अगर (irq_status & ASPEED_I2CD_INTR_BUS_RECOVER_DONE) अणु
		bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
		irq_handled |= ASPEED_I2CD_INTR_BUS_RECOVER_DONE;
		जाओ out_complete;
	पूर्ण

	/*
	 * We encountered an पूर्णांकerrupt that reports an error: the hardware
	 * should clear the command queue effectively taking us back to the
	 * INACTIVE state.
	 */
	ret = aspeed_i2c_is_irq_error(irq_status);
	अगर (ret) अणु
		dev_dbg(bus->dev, "received error interrupt: 0x%08x\n",
			irq_status);
		irq_handled |= (irq_status & ASPEED_I2CD_INTR_MASTER_ERRORS);
		अगर (bus->master_state != ASPEED_I2C_MASTER_INACTIVE) अणु
			bus->cmd_err = ret;
			bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
			जाओ out_complete;
		पूर्ण
	पूर्ण

	/* Master is not currently active, irq was क्रम someone अन्यथा. */
	अगर (bus->master_state == ASPEED_I2C_MASTER_INACTIVE ||
	    bus->master_state == ASPEED_I2C_MASTER_PENDING)
		जाओ out_no_complete;

	/* We are in an invalid state; reset bus to a known state. */
	अगर (!bus->msgs) अणु
		dev_err(bus->dev, "bus in unknown state. irq_status: 0x%x\n",
			irq_status);
		bus->cmd_err = -EIO;
		अगर (bus->master_state != ASPEED_I2C_MASTER_STOP &&
		    bus->master_state != ASPEED_I2C_MASTER_INACTIVE)
			aspeed_i2c_करो_stop(bus);
		जाओ out_no_complete;
	पूर्ण
	msg = &bus->msgs[bus->msgs_index];

	/*
	 * START is a special हाल because we still have to handle a subsequent
	 * TX or RX immediately after we handle it, so we handle it here and
	 * then update the state and handle the new state below.
	 */
	अगर (bus->master_state == ASPEED_I2C_MASTER_START) अणु
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
		/*
		 * If a peer master starts a xfer immediately after it queues a
		 * master command, clear the queued master command and change
		 * its state to 'pending'. To simplअगरy handling of pending
		 * हालs, it uses S/W solution instead of H/W command queue
		 * handling.
		 */
		अगर (unlikely(irq_status & ASPEED_I2CD_INTR_SLAVE_MATCH)) अणु
			ग_लिखोl(पढ़ोl(bus->base + ASPEED_I2C_CMD_REG) &
				~ASPEED_I2CD_MASTER_CMDS_MASK,
			       bus->base + ASPEED_I2C_CMD_REG);
			bus->master_state = ASPEED_I2C_MASTER_PENDING;
			dev_dbg(bus->dev,
				"master goes pending due to a slave start\n");
			जाओ out_no_complete;
		पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */
		अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_TX_ACK))) अणु
			अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_TX_NAK))) अणु
				bus->cmd_err = -ENXIO;
				bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
				जाओ out_complete;
			पूर्ण
			pr_devel("no slave present at %02x\n", msg->addr);
			irq_handled |= ASPEED_I2CD_INTR_TX_NAK;
			bus->cmd_err = -ENXIO;
			aspeed_i2c_करो_stop(bus);
			जाओ out_no_complete;
		पूर्ण
		irq_handled |= ASPEED_I2CD_INTR_TX_ACK;
		अगर (msg->len == 0) अणु /* SMBUS_QUICK */
			aspeed_i2c_करो_stop(bus);
			जाओ out_no_complete;
		पूर्ण
		अगर (msg->flags & I2C_M_RD)
			bus->master_state = ASPEED_I2C_MASTER_RX_FIRST;
		अन्यथा
			bus->master_state = ASPEED_I2C_MASTER_TX_FIRST;
	पूर्ण

	चयन (bus->master_state) अणु
	हाल ASPEED_I2C_MASTER_TX:
		अगर (unlikely(irq_status & ASPEED_I2CD_INTR_TX_NAK)) अणु
			dev_dbg(bus->dev, "slave NACKed TX\n");
			irq_handled |= ASPEED_I2CD_INTR_TX_NAK;
			जाओ error_and_stop;
		पूर्ण अन्यथा अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_TX_ACK))) अणु
			dev_err(bus->dev, "slave failed to ACK TX\n");
			जाओ error_and_stop;
		पूर्ण
		irq_handled |= ASPEED_I2CD_INTR_TX_ACK;
		fallthrough;
	हाल ASPEED_I2C_MASTER_TX_FIRST:
		अगर (bus->buf_index < msg->len) अणु
			bus->master_state = ASPEED_I2C_MASTER_TX;
			ग_लिखोl(msg->buf[bus->buf_index++],
			       bus->base + ASPEED_I2C_BYTE_BUF_REG);
			ग_लिखोl(ASPEED_I2CD_M_TX_CMD,
			       bus->base + ASPEED_I2C_CMD_REG);
		पूर्ण अन्यथा अणु
			aspeed_i2c_next_msg_or_stop(bus);
		पूर्ण
		जाओ out_no_complete;
	हाल ASPEED_I2C_MASTER_RX_FIRST:
		/* RX may not have completed yet (only address cycle) */
		अगर (!(irq_status & ASPEED_I2CD_INTR_RX_DONE))
			जाओ out_no_complete;
		fallthrough;
	हाल ASPEED_I2C_MASTER_RX:
		अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_RX_DONE))) अणु
			dev_err(bus->dev, "master failed to RX\n");
			जाओ error_and_stop;
		पूर्ण
		irq_handled |= ASPEED_I2CD_INTR_RX_DONE;

		recv_byte = पढ़ोl(bus->base + ASPEED_I2C_BYTE_BUF_REG) >> 8;
		msg->buf[bus->buf_index++] = recv_byte;

		अगर (msg->flags & I2C_M_RECV_LEN) अणु
			अगर (unlikely(recv_byte > I2C_SMBUS_BLOCK_MAX)) अणु
				bus->cmd_err = -EPROTO;
				aspeed_i2c_करो_stop(bus);
				जाओ out_no_complete;
			पूर्ण
			msg->len = recv_byte +
					((msg->flags & I2C_CLIENT_PEC) ? 2 : 1);
			msg->flags &= ~I2C_M_RECV_LEN;
		पूर्ण

		अगर (bus->buf_index < msg->len) अणु
			bus->master_state = ASPEED_I2C_MASTER_RX;
			command = ASPEED_I2CD_M_RX_CMD;
			अगर (bus->buf_index + 1 == msg->len)
				command |= ASPEED_I2CD_M_S_RX_CMD_LAST;
			ग_लिखोl(command, bus->base + ASPEED_I2C_CMD_REG);
		पूर्ण अन्यथा अणु
			aspeed_i2c_next_msg_or_stop(bus);
		पूर्ण
		जाओ out_no_complete;
	हाल ASPEED_I2C_MASTER_STOP:
		अगर (unlikely(!(irq_status & ASPEED_I2CD_INTR_NORMAL_STOP))) अणु
			dev_err(bus->dev,
				"master failed to STOP. irq_status:0x%x\n",
				irq_status);
			bus->cmd_err = -EIO;
			/* Do not STOP as we have alपढ़ोy tried. */
		पूर्ण अन्यथा अणु
			irq_handled |= ASPEED_I2CD_INTR_NORMAL_STOP;
		पूर्ण

		bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
		जाओ out_complete;
	हाल ASPEED_I2C_MASTER_INACTIVE:
		dev_err(bus->dev,
			"master received interrupt 0x%08x, but is inactive\n",
			irq_status);
		bus->cmd_err = -EIO;
		/* Do not STOP as we should be inactive. */
		जाओ out_complete;
	शेष:
		WARN(1, "unknown master state\n");
		bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
		bus->cmd_err = -EINVAL;
		जाओ out_complete;
	पूर्ण
error_and_stop:
	bus->cmd_err = -EIO;
	aspeed_i2c_करो_stop(bus);
	जाओ out_no_complete;
out_complete:
	bus->msgs = शून्य;
	अगर (bus->cmd_err)
		bus->master_xfer_result = bus->cmd_err;
	अन्यथा
		bus->master_xfer_result = bus->msgs_index + 1;
	complete(&bus->cmd_complete);
out_no_complete:
	वापस irq_handled;
पूर्ण

अटल irqवापस_t aspeed_i2c_bus_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aspeed_i2c_bus *bus = dev_id;
	u32 irq_received, irq_reमुख्यing, irq_handled;

	spin_lock(&bus->lock);
	irq_received = पढ़ोl(bus->base + ASPEED_I2C_INTR_STS_REG);
	/* Ack all पूर्णांकerrupts except क्रम Rx करोne */
	ग_लिखोl(irq_received & ~ASPEED_I2CD_INTR_RX_DONE,
	       bus->base + ASPEED_I2C_INTR_STS_REG);
	पढ़ोl(bus->base + ASPEED_I2C_INTR_STS_REG);
	irq_received &= ASPEED_I2CD_INTR_RECV_MASK;
	irq_reमुख्यing = irq_received;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/*
	 * In most हालs, पूर्णांकerrupt bits will be set one by one, although
	 * multiple पूर्णांकerrupt bits could be set at the same समय. It's also
	 * possible that master पूर्णांकerrupt bits could be set aदीर्घ with slave
	 * पूर्णांकerrupt bits. Each हाल needs to be handled using corresponding
	 * handlers depending on the current state.
	 */
	अगर (bus->master_state != ASPEED_I2C_MASTER_INACTIVE &&
	    bus->master_state != ASPEED_I2C_MASTER_PENDING) अणु
		irq_handled = aspeed_i2c_master_irq(bus, irq_reमुख्यing);
		irq_reमुख्यing &= ~irq_handled;
		अगर (irq_reमुख्यing)
			irq_handled |= aspeed_i2c_slave_irq(bus, irq_reमुख्यing);
	पूर्ण अन्यथा अणु
		irq_handled = aspeed_i2c_slave_irq(bus, irq_reमुख्यing);
		irq_reमुख्यing &= ~irq_handled;
		अगर (irq_reमुख्यing)
			irq_handled |= aspeed_i2c_master_irq(bus,
							     irq_reमुख्यing);
	पूर्ण

	/*
	 * Start a pending master command at here अगर a slave operation is
	 * completed.
	 */
	अगर (bus->master_state == ASPEED_I2C_MASTER_PENDING &&
	    bus->slave_state == ASPEED_I2C_SLAVE_INACTIVE)
		aspeed_i2c_करो_start(bus);
#अन्यथा
	irq_handled = aspeed_i2c_master_irq(bus, irq_reमुख्यing);
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

	irq_reमुख्यing &= ~irq_handled;
	अगर (irq_reमुख्यing)
		dev_err(bus->dev,
			"irq handled != irq. expected 0x%08x, but was 0x%08x\n",
			irq_received, irq_handled);

	/* Ack Rx करोne */
	अगर (irq_received & ASPEED_I2CD_INTR_RX_DONE) अणु
		ग_लिखोl(ASPEED_I2CD_INTR_RX_DONE,
		       bus->base + ASPEED_I2C_INTR_STS_REG);
		पढ़ोl(bus->base + ASPEED_I2C_INTR_STS_REG);
	पूर्ण
	spin_unlock(&bus->lock);
	वापस irq_reमुख्यing ? IRQ_NONE : IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aspeed_i2c_master_xfer(काष्ठा i2c_adapter *adap,
				  काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा aspeed_i2c_bus *bus = i2c_get_adapdata(adap);
	अचिन्हित दीर्घ समय_left, flags;

	spin_lock_irqsave(&bus->lock, flags);
	bus->cmd_err = 0;

	/* If bus is busy in a single master environment, attempt recovery. */
	अगर (!bus->multi_master &&
	    (पढ़ोl(bus->base + ASPEED_I2C_CMD_REG) &
	     ASPEED_I2CD_BUS_BUSY_STS)) अणु
		पूर्णांक ret;

		spin_unlock_irqrestore(&bus->lock, flags);
		ret = aspeed_i2c_recover_bus(bus);
		अगर (ret)
			वापस ret;
		spin_lock_irqsave(&bus->lock, flags);
	पूर्ण

	bus->cmd_err = 0;
	bus->msgs = msgs;
	bus->msgs_index = 0;
	bus->msgs_count = num;

	reinit_completion(&bus->cmd_complete);
	aspeed_i2c_करो_start(bus);
	spin_unlock_irqrestore(&bus->lock, flags);

	समय_left = रुको_क्रम_completion_समयout(&bus->cmd_complete,
						bus->adap.समयout);

	अगर (समय_left == 0) अणु
		/*
		 * If समयd out and bus is still busy in a multi master
		 * environment, attempt recovery at here.
		 */
		अगर (bus->multi_master &&
		    (पढ़ोl(bus->base + ASPEED_I2C_CMD_REG) &
		     ASPEED_I2CD_BUS_BUSY_STS))
			aspeed_i2c_recover_bus(bus);

		/*
		 * If समयd out and the state is still pending, drop the pending
		 * master command.
		 */
		spin_lock_irqsave(&bus->lock, flags);
		अगर (bus->master_state == ASPEED_I2C_MASTER_PENDING)
			bus->master_state = ASPEED_I2C_MASTER_INACTIVE;
		spin_unlock_irqrestore(&bus->lock, flags);

		वापस -ETIMEDOUT;
	पूर्ण

	वापस bus->master_xfer_result;
पूर्ण

अटल u32 aspeed_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
/* precondition: bus.lock has been acquired. */
अटल व्योम __aspeed_i2c_reg_slave(काष्ठा aspeed_i2c_bus *bus, u16 slave_addr)
अणु
	u32 addr_reg_val, func_ctrl_reg_val;

	/* Set slave addr. */
	addr_reg_val = पढ़ोl(bus->base + ASPEED_I2C_DEV_ADDR_REG);
	addr_reg_val &= ~ASPEED_I2CD_DEV_ADDR_MASK;
	addr_reg_val |= slave_addr & ASPEED_I2CD_DEV_ADDR_MASK;
	ग_लिखोl(addr_reg_val, bus->base + ASPEED_I2C_DEV_ADDR_REG);

	/* Turn on slave mode. */
	func_ctrl_reg_val = पढ़ोl(bus->base + ASPEED_I2C_FUN_CTRL_REG);
	func_ctrl_reg_val |= ASPEED_I2CD_SLAVE_EN;
	ग_लिखोl(func_ctrl_reg_val, bus->base + ASPEED_I2C_FUN_CTRL_REG);
पूर्ण

अटल पूर्णांक aspeed_i2c_reg_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा aspeed_i2c_bus *bus = i2c_get_adapdata(client->adapter);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bus->lock, flags);
	अगर (bus->slave) अणु
		spin_unlock_irqrestore(&bus->lock, flags);
		वापस -EINVAL;
	पूर्ण

	__aspeed_i2c_reg_slave(bus, client->addr);

	bus->slave = client;
	bus->slave_state = ASPEED_I2C_SLAVE_INACTIVE;
	spin_unlock_irqrestore(&bus->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_i2c_unreg_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा aspeed_i2c_bus *bus = i2c_get_adapdata(client->adapter);
	u32 func_ctrl_reg_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bus->lock, flags);
	अगर (!bus->slave) अणु
		spin_unlock_irqrestore(&bus->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* Turn off slave mode. */
	func_ctrl_reg_val = पढ़ोl(bus->base + ASPEED_I2C_FUN_CTRL_REG);
	func_ctrl_reg_val &= ~ASPEED_I2CD_SLAVE_EN;
	ग_लिखोl(func_ctrl_reg_val, bus->base + ASPEED_I2C_FUN_CTRL_REG);

	bus->slave = शून्य;
	spin_unlock_irqrestore(&bus->lock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

अटल स्थिर काष्ठा i2c_algorithm aspeed_i2c_algo = अणु
	.master_xfer	= aspeed_i2c_master_xfer,
	.functionality	= aspeed_i2c_functionality,
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	.reg_slave	= aspeed_i2c_reg_slave,
	.unreg_slave	= aspeed_i2c_unreg_slave,
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */
पूर्ण;

अटल u32 aspeed_i2c_get_clk_reg_val(काष्ठा device *dev,
				      u32 clk_high_low_mask,
				      u32 भागisor)
अणु
	u32 base_clk_भागisor, clk_high_low_max, clk_high, clk_low, पंचांगp;

	/*
	 * SCL_high and SCL_low represent a value 1 greater than what is stored
	 * since a zero भागider is meaningless. Thus, the max value each can
	 * store is every bit set + 1. Since SCL_high and SCL_low are added
	 * together (see below), the max value of both is the max value of one
	 * them बार two.
	 */
	clk_high_low_max = (clk_high_low_mask + 1) * 2;

	/*
	 * The actual घड़ी frequency of SCL is:
	 *	SCL_freq = APB_freq / (base_freq * (SCL_high + SCL_low))
	 *		 = APB_freq / भागisor
	 * where base_freq is a programmable घड़ी भागider; its value is
	 *	base_freq = 1 << base_clk_भागisor
	 * SCL_high is the number of base_freq घड़ी cycles that SCL stays high
	 * and SCL_low is the number of base_freq घड़ी cycles that SCL stays
	 * low क्रम a period of SCL.
	 * The actual रेजिस्टर has a minimum SCL_high and SCL_low minimum of 1;
	 * thus, they start counting at zero. So
	 *	SCL_high = clk_high + 1
	 *	SCL_low	 = clk_low + 1
	 * Thus,
	 *	SCL_freq = APB_freq /
	 *		((1 << base_clk_भागisor) * (clk_high + 1 + clk_low + 1))
	 * The करोcumentation recommends clk_high >= clk_high_max / 2 and
	 * clk_low >= clk_low_max / 2 - 1 when possible; this last स्थिरraपूर्णांक
	 * gives us the following solution:
	 */
	base_clk_भागisor = भागisor > clk_high_low_max ?
			ilog2((भागisor - 1) / clk_high_low_max) + 1 : 0;

	अगर (base_clk_भागisor > ASPEED_I2CD_TIME_BASE_DIVISOR_MASK) अणु
		base_clk_भागisor = ASPEED_I2CD_TIME_BASE_DIVISOR_MASK;
		clk_low = clk_high_low_mask;
		clk_high = clk_high_low_mask;
		dev_err(dev,
			"clamping clock divider: divider requested, %u, is greater than largest possible divider, %u.\n",
			भागisor, (1 << base_clk_भागisor) * clk_high_low_max);
	पूर्ण अन्यथा अणु
		पंचांगp = (भागisor + (1 << base_clk_भागisor) - 1)
				>> base_clk_भागisor;
		clk_low = पंचांगp / 2;
		clk_high = पंचांगp - clk_low;

		अगर (clk_high)
			clk_high--;

		अगर (clk_low)
			clk_low--;
	पूर्ण


	वापस ((clk_high << ASPEED_I2CD_TIME_SCL_HIGH_SHIFT)
		& ASPEED_I2CD_TIME_SCL_HIGH_MASK)
			| ((clk_low << ASPEED_I2CD_TIME_SCL_LOW_SHIFT)
			   & ASPEED_I2CD_TIME_SCL_LOW_MASK)
			| (base_clk_भागisor
			   & ASPEED_I2CD_TIME_BASE_DIVISOR_MASK);
पूर्ण

अटल u32 aspeed_i2c_24xx_get_clk_reg_val(काष्ठा device *dev, u32 भागisor)
अणु
	/*
	 * clk_high and clk_low are each 3 bits wide, so each can hold a max
	 * value of 8 giving a clk_high_low_max of 16.
	 */
	वापस aspeed_i2c_get_clk_reg_val(dev, GENMASK(2, 0), भागisor);
पूर्ण

अटल u32 aspeed_i2c_25xx_get_clk_reg_val(काष्ठा device *dev, u32 भागisor)
अणु
	/*
	 * clk_high and clk_low are each 4 bits wide, so each can hold a max
	 * value of 16 giving a clk_high_low_max of 32.
	 */
	वापस aspeed_i2c_get_clk_reg_val(dev, GENMASK(3, 0), भागisor);
पूर्ण

/* precondition: bus.lock has been acquired. */
अटल पूर्णांक aspeed_i2c_init_clk(काष्ठा aspeed_i2c_bus *bus)
अणु
	u32 भागisor, clk_reg_val;

	भागisor = DIV_ROUND_UP(bus->parent_clk_frequency, bus->bus_frequency);
	clk_reg_val = पढ़ोl(bus->base + ASPEED_I2C_AC_TIMING_REG1);
	clk_reg_val &= (ASPEED_I2CD_TIME_TBUF_MASK |
			ASPEED_I2CD_TIME_THDSTA_MASK |
			ASPEED_I2CD_TIME_TACST_MASK);
	clk_reg_val |= bus->get_clk_reg_val(bus->dev, भागisor);
	ग_लिखोl(clk_reg_val, bus->base + ASPEED_I2C_AC_TIMING_REG1);
	ग_लिखोl(ASPEED_NO_TIMEOUT_CTRL, bus->base + ASPEED_I2C_AC_TIMING_REG2);

	वापस 0;
पूर्ण

/* precondition: bus.lock has been acquired. */
अटल पूर्णांक aspeed_i2c_init(काष्ठा aspeed_i2c_bus *bus,
			     काष्ठा platक्रमm_device *pdev)
अणु
	u32 fun_ctrl_reg = ASPEED_I2CD_MASTER_EN;
	पूर्णांक ret;

	/* Disable everything. */
	ग_लिखोl(0, bus->base + ASPEED_I2C_FUN_CTRL_REG);

	ret = aspeed_i2c_init_clk(bus);
	अगर (ret < 0)
		वापस ret;

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "multi-master"))
		bus->multi_master = true;
	अन्यथा
		fun_ctrl_reg |= ASPEED_I2CD_MULTI_MASTER_DIS;

	/* Enable Master Mode */
	ग_लिखोl(पढ़ोl(bus->base + ASPEED_I2C_FUN_CTRL_REG) | fun_ctrl_reg,
	       bus->base + ASPEED_I2C_FUN_CTRL_REG);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/* If slave has alपढ़ोy been रेजिस्टरed, re-enable it. */
	अगर (bus->slave)
		__aspeed_i2c_reg_slave(bus, bus->slave->addr);
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

	/* Set पूर्णांकerrupt generation of I2C controller */
	ग_लिखोl(ASPEED_I2CD_INTR_ALL, bus->base + ASPEED_I2C_INTR_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_i2c_reset(काष्ठा aspeed_i2c_bus *bus)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(bus->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&bus->lock, flags);

	/* Disable and ack all पूर्णांकerrupts. */
	ग_लिखोl(0, bus->base + ASPEED_I2C_INTR_CTRL_REG);
	ग_लिखोl(0xffffffff, bus->base + ASPEED_I2C_INTR_STS_REG);

	ret = aspeed_i2c_init(bus, pdev);

	spin_unlock_irqrestore(&bus->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_i2c_bus_of_table[] = अणु
	अणु
		.compatible = "aspeed,ast2400-i2c-bus",
		.data = aspeed_i2c_24xx_get_clk_reg_val,
	पूर्ण,
	अणु
		.compatible = "aspeed,ast2500-i2c-bus",
		.data = aspeed_i2c_25xx_get_clk_reg_val,
	पूर्ण,
	अणु
		.compatible = "aspeed,ast2600-i2c-bus",
		.data = aspeed_i2c_25xx_get_clk_reg_val,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_i2c_bus_of_table);

अटल पूर्णांक aspeed_i2c_probe_bus(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aspeed_i2c_bus *bus;
	काष्ठा clk *parent_clk;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	bus = devm_kzalloc(&pdev->dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	bus->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(bus->base))
		वापस PTR_ERR(bus->base);

	parent_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(parent_clk))
		वापस PTR_ERR(parent_clk);
	bus->parent_clk_frequency = clk_get_rate(parent_clk);
	/* We just need the घड़ी rate, we करोn't actually use the clk object. */
	devm_clk_put(&pdev->dev, parent_clk);

	bus->rst = devm_reset_control_get_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(bus->rst)) अणु
		dev_err(&pdev->dev,
			"missing or invalid reset controller device tree entry\n");
		वापस PTR_ERR(bus->rst);
	पूर्ण
	reset_control_deनिश्चित(bus->rst);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node,
				   "bus-frequency", &bus->bus_frequency);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Could not read bus-frequency property\n");
		bus->bus_frequency = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण

	match = of_match_node(aspeed_i2c_bus_of_table, pdev->dev.of_node);
	अगर (!match)
		bus->get_clk_reg_val = aspeed_i2c_24xx_get_clk_reg_val;
	अन्यथा
		bus->get_clk_reg_val = (u32 (*)(काष्ठा device *, u32))
				match->data;

	/* Initialize the I2C adapter */
	spin_lock_init(&bus->lock);
	init_completion(&bus->cmd_complete);
	bus->adap.owner = THIS_MODULE;
	bus->adap.retries = 0;
	bus->adap.algo = &aspeed_i2c_algo;
	bus->adap.dev.parent = &pdev->dev;
	bus->adap.dev.of_node = pdev->dev.of_node;
	strlcpy(bus->adap.name, pdev->name, माप(bus->adap.name));
	i2c_set_adapdata(&bus->adap, bus);

	bus->dev = &pdev->dev;

	/* Clean up any left over पूर्णांकerrupt state. */
	ग_लिखोl(0, bus->base + ASPEED_I2C_INTR_CTRL_REG);
	ग_लिखोl(0xffffffff, bus->base + ASPEED_I2C_INTR_STS_REG);
	/*
	 * bus.lock करोes not need to be held because the पूर्णांकerrupt handler has
	 * not been enabled yet.
	 */
	ret = aspeed_i2c_init(bus, pdev);
	अगर (ret < 0)
		वापस ret;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	ret = devm_request_irq(&pdev->dev, irq, aspeed_i2c_bus_irq,
			       0, dev_name(&pdev->dev), bus);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_add_adapter(&bus->adap);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, bus);

	dev_info(bus->dev, "i2c bus %d registered, irq %d\n",
		 bus->adap.nr, irq);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_i2c_हटाओ_bus(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_i2c_bus *bus = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bus->lock, flags);

	/* Disable everything. */
	ग_लिखोl(0, bus->base + ASPEED_I2C_FUN_CTRL_REG);
	ग_लिखोl(0, bus->base + ASPEED_I2C_INTR_CTRL_REG);

	spin_unlock_irqrestore(&bus->lock, flags);

	reset_control_निश्चित(bus->rst);

	i2c_del_adapter(&bus->adap);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_i2c_bus_driver = अणु
	.probe		= aspeed_i2c_probe_bus,
	.हटाओ		= aspeed_i2c_हटाओ_bus,
	.driver		= अणु
		.name		= "aspeed-i2c-bus",
		.of_match_table	= aspeed_i2c_bus_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aspeed_i2c_bus_driver);

MODULE_AUTHOR("Brendan Higgins <brendanhiggins@google.com>");
MODULE_DESCRIPTION("Aspeed I2C Bus Driver");
MODULE_LICENSE("GPL v2");
