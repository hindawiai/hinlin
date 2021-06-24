<शैली गुरु>
/*
 * Driver क्रम the i2c controller on the Marvell line of host bridges
 * (e.g, gt642[46]0, mv643[46]0, mv644[46]0, and Orion SoC family).
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * 2005 (c) MontaVista, Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mv643xx_i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#घोषणा MV64XXX_I2C_ADDR_ADDR(val)			((val & 0x7f) << 1)
#घोषणा MV64XXX_I2C_BAUD_DIV_N(val)			(val & 0x7)
#घोषणा MV64XXX_I2C_BAUD_DIV_M(val)			((val & 0xf) << 3)

#घोषणा	MV64XXX_I2C_REG_CONTROL_ACK			BIT(2)
#घोषणा	MV64XXX_I2C_REG_CONTROL_IFLG			BIT(3)
#घोषणा	MV64XXX_I2C_REG_CONTROL_STOP			BIT(4)
#घोषणा	MV64XXX_I2C_REG_CONTROL_START			BIT(5)
#घोषणा	MV64XXX_I2C_REG_CONTROL_TWSIEN			BIT(6)
#घोषणा	MV64XXX_I2C_REG_CONTROL_INTEN			BIT(7)

/* Ctlr status values */
#घोषणा	MV64XXX_I2C_STATUS_BUS_ERR			0x00
#घोषणा	MV64XXX_I2C_STATUS_MAST_START			0x08
#घोषणा	MV64XXX_I2C_STATUS_MAST_REPEAT_START		0x10
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_ADDR_ACK		0x18
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_ADDR_NO_ACK		0x20
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_ACK			0x28
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_NO_ACK		0x30
#घोषणा	MV64XXX_I2C_STATUS_MAST_LOST_ARB		0x38
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_ADDR_ACK		0x40
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_ADDR_NO_ACK		0x48
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK		0x50
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_DATA_NO_ACK		0x58
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_ADDR_2_ACK		0xd0
#घोषणा	MV64XXX_I2C_STATUS_MAST_WR_ADDR_2_NO_ACK	0xd8
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_ADDR_2_ACK		0xe0
#घोषणा	MV64XXX_I2C_STATUS_MAST_RD_ADDR_2_NO_ACK	0xe8
#घोषणा	MV64XXX_I2C_STATUS_NO_STATUS			0xf8

/* Register defines (I2C bridge) */
#घोषणा	MV64XXX_I2C_REG_TX_DATA_LO			0xc0
#घोषणा	MV64XXX_I2C_REG_TX_DATA_HI			0xc4
#घोषणा	MV64XXX_I2C_REG_RX_DATA_LO			0xc8
#घोषणा	MV64XXX_I2C_REG_RX_DATA_HI			0xcc
#घोषणा	MV64XXX_I2C_REG_BRIDGE_CONTROL			0xd0
#घोषणा	MV64XXX_I2C_REG_BRIDGE_STATUS			0xd4
#घोषणा	MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE		0xd8
#घोषणा	MV64XXX_I2C_REG_BRIDGE_INTR_MASK		0xdC
#घोषणा	MV64XXX_I2C_REG_BRIDGE_TIMING			0xe0

/* Bridge Control values */
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_WR			BIT(0)
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_RD			BIT(1)
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_ADDR_SHIFT		2
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_ADDR_EXT		BIT(12)
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT	13
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT	16
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_ENABLE		BIT(19)
#घोषणा	MV64XXX_I2C_BRIDGE_CONTROL_REPEATED_START	BIT(20)

/* Bridge Status values */
#घोषणा	MV64XXX_I2C_BRIDGE_STATUS_ERROR			BIT(0)

/* Driver states */
क्रमागत अणु
	MV64XXX_I2C_STATE_INVALID,
	MV64XXX_I2C_STATE_IDLE,
	MV64XXX_I2C_STATE_WAITING_FOR_START_COND,
	MV64XXX_I2C_STATE_WAITING_FOR_RESTART,
	MV64XXX_I2C_STATE_WAITING_FOR_ADDR_1_ACK,
	MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK,
	MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK,
	MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA,
पूर्ण;

/* Driver actions */
क्रमागत अणु
	MV64XXX_I2C_ACTION_INVALID,
	MV64XXX_I2C_ACTION_CONTINUE,
	MV64XXX_I2C_ACTION_SEND_RESTART,
	MV64XXX_I2C_ACTION_SEND_ADDR_1,
	MV64XXX_I2C_ACTION_SEND_ADDR_2,
	MV64XXX_I2C_ACTION_SEND_DATA,
	MV64XXX_I2C_ACTION_RCV_DATA,
	MV64XXX_I2C_ACTION_RCV_DATA_STOP,
	MV64XXX_I2C_ACTION_SEND_STOP,
पूर्ण;

काष्ठा mv64xxx_i2c_regs अणु
	u8	addr;
	u8	ext_addr;
	u8	data;
	u8	control;
	u8	status;
	u8	घड़ी;
	u8	soft_reset;
पूर्ण;

काष्ठा mv64xxx_i2c_data अणु
	काष्ठा i2c_msg		*msgs;
	पूर्णांक			num_msgs;
	पूर्णांक			irq;
	u32			state;
	u32			action;
	u32			पातing;
	u32			cntl_bits;
	व्योम __iomem		*reg_base;
	काष्ठा mv64xxx_i2c_regs	reg_offsets;
	u32			addr1;
	u32			addr2;
	u32			bytes_left;
	u32			byte_posn;
	u32			send_stop;
	u32			block;
	पूर्णांक			rc;
	u32			freq_m;
	u32			freq_n;
	काष्ठा clk              *clk;
	काष्ठा clk              *reg_clk;
	रुको_queue_head_t	रुकोq;
	spinlock_t		lock;
	काष्ठा i2c_msg		*msg;
	काष्ठा i2c_adapter	adapter;
	bool			offload_enabled;
/* 5us delay in order to aव्योम repeated start timing violation */
	bool			errata_delay;
	काष्ठा reset_control	*rstc;
	bool			irq_clear_inverted;
	/* Clk भाग is 2 to the घातer n, not 2 to the घातer n + 1 */
	bool			clk_n_base_0;
	काष्ठा i2c_bus_recovery_info	rinfo;
पूर्ण;

अटल काष्ठा mv64xxx_i2c_regs mv64xxx_i2c_regs_mv64xxx = अणु
	.addr		= 0x00,
	.ext_addr	= 0x10,
	.data		= 0x04,
	.control	= 0x08,
	.status		= 0x0c,
	.घड़ी		= 0x0c,
	.soft_reset	= 0x1c,
पूर्ण;

अटल काष्ठा mv64xxx_i2c_regs mv64xxx_i2c_regs_sun4i = अणु
	.addr		= 0x00,
	.ext_addr	= 0x04,
	.data		= 0x08,
	.control	= 0x0c,
	.status		= 0x10,
	.घड़ी		= 0x14,
	.soft_reset	= 0x18,
पूर्ण;

अटल व्योम
mv64xxx_i2c_prepare_क्रम_io(काष्ठा mv64xxx_i2c_data *drv_data,
	काष्ठा i2c_msg *msg)
अणु
	u32	dir = 0;

	drv_data->cntl_bits = MV64XXX_I2C_REG_CONTROL_ACK |
		MV64XXX_I2C_REG_CONTROL_INTEN | MV64XXX_I2C_REG_CONTROL_TWSIEN;

	अगर (msg->flags & I2C_M_RD)
		dir = 1;

	अगर (msg->flags & I2C_M_TEN) अणु
		drv_data->addr1 = 0xf0 | (((u32)msg->addr & 0x300) >> 7) | dir;
		drv_data->addr2 = (u32)msg->addr & 0xff;
	पूर्ण अन्यथा अणु
		drv_data->addr1 = MV64XXX_I2C_ADDR_ADDR((u32)msg->addr) | dir;
		drv_data->addr2 = 0;
	पूर्ण
पूर्ण

/*
 *****************************************************************************
 *
 *	Finite State Machine & Interrupt Routines
 *
 *****************************************************************************
 */

/* Reset hardware and initialize FSM */
अटल व्योम
mv64xxx_i2c_hw_init(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	अगर (drv_data->offload_enabled) अणु
		ग_लिखोl(0, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_CONTROL);
		ग_लिखोl(0, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_TIMING);
		ग_लिखोl(0, drv_data->reg_base +
			MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
		ग_लिखोl(0, drv_data->reg_base +
			MV64XXX_I2C_REG_BRIDGE_INTR_MASK);
	पूर्ण

	ग_लिखोl(0, drv_data->reg_base + drv_data->reg_offsets.soft_reset);
	ग_लिखोl(MV64XXX_I2C_BAUD_DIV_M(drv_data->freq_m) | MV64XXX_I2C_BAUD_DIV_N(drv_data->freq_n),
		drv_data->reg_base + drv_data->reg_offsets.घड़ी);
	ग_लिखोl(0, drv_data->reg_base + drv_data->reg_offsets.addr);
	ग_लिखोl(0, drv_data->reg_base + drv_data->reg_offsets.ext_addr);
	ग_लिखोl(MV64XXX_I2C_REG_CONTROL_TWSIEN | MV64XXX_I2C_REG_CONTROL_STOP,
		drv_data->reg_base + drv_data->reg_offsets.control);

	अगर (drv_data->errata_delay)
		udelay(5);

	drv_data->state = MV64XXX_I2C_STATE_IDLE;
पूर्ण

अटल व्योम
mv64xxx_i2c_fsm(काष्ठा mv64xxx_i2c_data *drv_data, u32 status)
अणु
	/*
	 * If state is idle, then this is likely the remnants of an old
	 * operation that driver has given up on or the user has समाप्तed.
	 * If so, issue the stop condition and go to idle.
	 */
	अगर (drv_data->state == MV64XXX_I2C_STATE_IDLE) अणु
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		वापस;
	पूर्ण

	/* The status from the ctlr [mostly] tells us what to करो next */
	चयन (status) अणु
	/* Start condition पूर्णांकerrupt */
	हाल MV64XXX_I2C_STATUS_MAST_START: /* 0x08 */
	हाल MV64XXX_I2C_STATUS_MAST_REPEAT_START: /* 0x10 */
		drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_1;
		drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_ADDR_1_ACK;
		अवरोध;

	/* Perक्रमming a ग_लिखो */
	हाल MV64XXX_I2C_STATUS_MAST_WR_ADDR_ACK: /* 0x18 */
		अगर (drv_data->msg->flags & I2C_M_TEN) अणु
			drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_2;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MV64XXX_I2C_STATUS_MAST_WR_ADDR_2_ACK: /* 0xd0 */
	हाल MV64XXX_I2C_STATUS_MAST_WR_ACK: /* 0x28 */
		अगर ((drv_data->bytes_left == 0)
				|| (drv_data->पातing
					&& (drv_data->byte_posn != 0))) अणु
			अगर (drv_data->send_stop || drv_data->पातing) अणु
				drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
				drv_data->state = MV64XXX_I2C_STATE_IDLE;
			पूर्ण अन्यथा अणु
				drv_data->action =
					MV64XXX_I2C_ACTION_SEND_RESTART;
				drv_data->state =
					MV64XXX_I2C_STATE_WAITING_FOR_RESTART;
			पूर्ण
		पूर्ण अन्यथा अणु
			drv_data->action = MV64XXX_I2C_ACTION_SEND_DATA;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_ACK;
			drv_data->bytes_left--;
		पूर्ण
		अवरोध;

	/* Perक्रमming a पढ़ो */
	हाल MV64XXX_I2C_STATUS_MAST_RD_ADDR_ACK: /* 40 */
		अगर (drv_data->msg->flags & I2C_M_TEN) अणु
			drv_data->action = MV64XXX_I2C_ACTION_SEND_ADDR_2;
			drv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOR_ADDR_2_ACK;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MV64XXX_I2C_STATUS_MAST_RD_ADDR_2_ACK: /* 0xe0 */
		अगर (drv_data->bytes_left == 0) अणु
			drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
			drv_data->state = MV64XXX_I2C_STATE_IDLE;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK: /* 0x50 */
		अगर (status != MV64XXX_I2C_STATUS_MAST_RD_DATA_ACK)
			drv_data->action = MV64XXX_I2C_ACTION_CONTINUE;
		अन्यथा अणु
			drv_data->action = MV64XXX_I2C_ACTION_RCV_DATA;
			drv_data->bytes_left--;
		पूर्ण
		drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_SLAVE_DATA;

		अगर ((drv_data->bytes_left == 1) || drv_data->पातing)
			drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_ACK;
		अवरोध;

	हाल MV64XXX_I2C_STATUS_MAST_RD_DATA_NO_ACK: /* 0x58 */
		drv_data->action = MV64XXX_I2C_ACTION_RCV_DATA_STOP;
		drv_data->state = MV64XXX_I2C_STATE_IDLE;
		अवरोध;

	हाल MV64XXX_I2C_STATUS_MAST_WR_ADDR_NO_ACK: /* 0x20 */
	हाल MV64XXX_I2C_STATUS_MAST_WR_NO_ACK: /* 30 */
	हाल MV64XXX_I2C_STATUS_MAST_RD_ADDR_NO_ACK: /* 48 */
		/* Doesn't seem to be a device at other end */
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		drv_data->state = MV64XXX_I2C_STATE_IDLE;
		drv_data->rc = -ENXIO;
		अवरोध;

	शेष:
		dev_err(&drv_data->adapter.dev,
			"mv64xxx_i2c_fsm: Ctlr Error -- state: 0x%x, "
			"status: 0x%x, addr: 0x%x, flags: 0x%x\n",
			 drv_data->state, status, drv_data->msg->addr,
			 drv_data->msg->flags);
		drv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		mv64xxx_i2c_hw_init(drv_data);
		i2c_recover_bus(&drv_data->adapter);
		drv_data->rc = -EAGAIN;
	पूर्ण
पूर्ण

अटल व्योम mv64xxx_i2c_send_start(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	drv_data->msg = drv_data->msgs;
	drv_data->byte_posn = 0;
	drv_data->bytes_left = drv_data->msg->len;
	drv_data->पातing = 0;
	drv_data->rc = 0;

	mv64xxx_i2c_prepare_क्रम_io(drv_data, drv_data->msgs);
	ग_लिखोl(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_START,
	       drv_data->reg_base + drv_data->reg_offsets.control);
पूर्ण

अटल व्योम
mv64xxx_i2c_करो_action(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	चयन(drv_data->action) अणु
	हाल MV64XXX_I2C_ACTION_SEND_RESTART:
		/* We should only get here अगर we have further messages */
		BUG_ON(drv_data->num_msgs == 0);

		drv_data->msgs++;
		drv_data->num_msgs--;
		mv64xxx_i2c_send_start(drv_data);

		अगर (drv_data->errata_delay)
			udelay(5);

		/*
		 * We're never at the start of the message here, and by this
		 * समय it's alपढ़ोy too late to करो any protocol mangling.
		 * Thankfully, करो not advertise support क्रम that feature.
		 */
		drv_data->send_stop = drv_data->num_msgs == 1;
		अवरोध;

	हाल MV64XXX_I2C_ACTION_CONTINUE:
		ग_लिखोl(drv_data->cntl_bits,
			drv_data->reg_base + drv_data->reg_offsets.control);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_SEND_ADDR_1:
		ग_लिखोl(drv_data->addr1,
			drv_data->reg_base + drv_data->reg_offsets.data);
		ग_लिखोl(drv_data->cntl_bits,
			drv_data->reg_base + drv_data->reg_offsets.control);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_SEND_ADDR_2:
		ग_लिखोl(drv_data->addr2,
			drv_data->reg_base + drv_data->reg_offsets.data);
		ग_लिखोl(drv_data->cntl_bits,
			drv_data->reg_base + drv_data->reg_offsets.control);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_SEND_DATA:
		ग_लिखोl(drv_data->msg->buf[drv_data->byte_posn++],
			drv_data->reg_base + drv_data->reg_offsets.data);
		ग_लिखोl(drv_data->cntl_bits,
			drv_data->reg_base + drv_data->reg_offsets.control);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_RCV_DATA:
		drv_data->msg->buf[drv_data->byte_posn++] =
			पढ़ोl(drv_data->reg_base + drv_data->reg_offsets.data);
		ग_लिखोl(drv_data->cntl_bits,
			drv_data->reg_base + drv_data->reg_offsets.control);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_RCV_DATA_STOP:
		drv_data->msg->buf[drv_data->byte_posn++] =
			पढ़ोl(drv_data->reg_base + drv_data->reg_offsets.data);
		drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_INTEN;
		ग_लिखोl(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_STOP,
			drv_data->reg_base + drv_data->reg_offsets.control);
		drv_data->block = 0;
		अगर (drv_data->errata_delay)
			udelay(5);

		wake_up(&drv_data->रुकोq);
		अवरोध;

	हाल MV64XXX_I2C_ACTION_INVALID:
	शेष:
		dev_err(&drv_data->adapter.dev,
			"mv64xxx_i2c_do_action: Invalid action: %d\n",
			drv_data->action);
		drv_data->rc = -EIO;
		fallthrough;
	हाल MV64XXX_I2C_ACTION_SEND_STOP:
		drv_data->cntl_bits &= ~MV64XXX_I2C_REG_CONTROL_INTEN;
		ग_लिखोl(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_STOP,
			drv_data->reg_base + drv_data->reg_offsets.control);
		drv_data->block = 0;
		wake_up(&drv_data->रुकोq);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mv64xxx_i2c_पढ़ो_offload_rx_data(काष्ठा mv64xxx_i2c_data *drv_data,
				 काष्ठा i2c_msg *msg)
अणु
	u32 buf[2];

	buf[0] = पढ़ोl(drv_data->reg_base + MV64XXX_I2C_REG_RX_DATA_LO);
	buf[1] = पढ़ोl(drv_data->reg_base + MV64XXX_I2C_REG_RX_DATA_HI);

	स_नकल(msg->buf, buf, msg->len);
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_पूर्णांकr_offload(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	u32 cause, status;

	cause = पढ़ोl(drv_data->reg_base +
		      MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
	अगर (!cause)
		वापस IRQ_NONE;

	status = पढ़ोl(drv_data->reg_base +
		       MV64XXX_I2C_REG_BRIDGE_STATUS);

	अगर (status & MV64XXX_I2C_BRIDGE_STATUS_ERROR) अणु
		drv_data->rc = -EIO;
		जाओ out;
	पूर्ण

	drv_data->rc = 0;

	/*
	 * Transaction is a one message पढ़ो transaction, पढ़ो data
	 * क्रम this message.
	 */
	अगर (drv_data->num_msgs == 1 && drv_data->msgs[0].flags & I2C_M_RD) अणु
		mv64xxx_i2c_पढ़ो_offload_rx_data(drv_data, drv_data->msgs);
		drv_data->msgs++;
		drv_data->num_msgs--;
	पूर्ण
	/*
	 * Transaction is a two messages ग_लिखो/पढ़ो transaction, पढ़ो
	 * data क्रम the second (पढ़ो) message.
	 */
	अन्यथा अगर (drv_data->num_msgs == 2 &&
		 !(drv_data->msgs[0].flags & I2C_M_RD) &&
		 drv_data->msgs[1].flags & I2C_M_RD) अणु
		mv64xxx_i2c_पढ़ो_offload_rx_data(drv_data, drv_data->msgs + 1);
		drv_data->msgs += 2;
		drv_data->num_msgs -= 2;
	पूर्ण

out:
	ग_लिखोl(0, drv_data->reg_base +	MV64XXX_I2C_REG_BRIDGE_CONTROL);
	ग_लिखोl(0, drv_data->reg_base +
	       MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
	drv_data->block = 0;

	wake_up(&drv_data->रुकोq);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
mv64xxx_i2c_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv64xxx_i2c_data	*drv_data = dev_id;
	u32		status;
	irqवापस_t	rc = IRQ_NONE;

	spin_lock(&drv_data->lock);

	अगर (drv_data->offload_enabled)
		rc = mv64xxx_i2c_पूर्णांकr_offload(drv_data);

	जबतक (पढ़ोl(drv_data->reg_base + drv_data->reg_offsets.control) &
						MV64XXX_I2C_REG_CONTROL_IFLG) अणु
		status = पढ़ोl(drv_data->reg_base + drv_data->reg_offsets.status);
		mv64xxx_i2c_fsm(drv_data, status);
		mv64xxx_i2c_करो_action(drv_data);

		अगर (drv_data->irq_clear_inverted)
			ग_लिखोl(drv_data->cntl_bits | MV64XXX_I2C_REG_CONTROL_IFLG,
			       drv_data->reg_base + drv_data->reg_offsets.control);

		rc = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&drv_data->lock);

	वापस rc;
पूर्ण

/*
 *****************************************************************************
 *
 *	I2C Msg Execution Routines
 *
 *****************************************************************************
 */
अटल व्योम
mv64xxx_i2c_रुको_क्रम_completion(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	दीर्घ		समय_left;
	अचिन्हित दीर्घ	flags;
	अक्षर		पात = 0;

	समय_left = रुको_event_समयout(drv_data->रुकोq,
		!drv_data->block, drv_data->adapter.समयout);

	spin_lock_irqsave(&drv_data->lock, flags);
	अगर (!समय_left) अणु /* Timed out */
		drv_data->rc = -ETIMEDOUT;
		पात = 1;
	पूर्ण अन्यथा अगर (समय_left < 0) अणु /* Interrupted/Error */
		drv_data->rc = समय_left; /* त्रुटि_सं value */
		पात = 1;
	पूर्ण

	अगर (पात && drv_data->block) अणु
		drv_data->पातing = 1;
		spin_unlock_irqrestore(&drv_data->lock, flags);

		समय_left = रुको_event_समयout(drv_data->रुकोq,
			!drv_data->block, drv_data->adapter.समयout);

		अगर ((समय_left <= 0) && drv_data->block) अणु
			drv_data->state = MV64XXX_I2C_STATE_IDLE;
			dev_err(&drv_data->adapter.dev,
				"mv64xxx: I2C bus locked, block: %d, "
				"time_left: %d\n", drv_data->block,
				(पूर्णांक)समय_left);
			mv64xxx_i2c_hw_init(drv_data);
			i2c_recover_bus(&drv_data->adapter);
		पूर्ण
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&drv_data->lock, flags);
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_execute_msg(काष्ठा mv64xxx_i2c_data *drv_data, काष्ठा i2c_msg *msg,
				पूर्णांक is_last)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&drv_data->lock, flags);

	drv_data->state = MV64XXX_I2C_STATE_WAITING_FOR_START_COND;

	drv_data->send_stop = is_last;
	drv_data->block = 1;
	mv64xxx_i2c_send_start(drv_data);
	spin_unlock_irqrestore(&drv_data->lock, flags);

	mv64xxx_i2c_रुको_क्रम_completion(drv_data);
	वापस drv_data->rc;
पूर्ण

अटल व्योम
mv64xxx_i2c_prepare_tx(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	काष्ठा i2c_msg *msg = drv_data->msgs;
	u32 buf[2];

	स_नकल(buf, msg->buf, msg->len);

	ग_लिखोl(buf[0], drv_data->reg_base + MV64XXX_I2C_REG_TX_DATA_LO);
	ग_लिखोl(buf[1], drv_data->reg_base + MV64XXX_I2C_REG_TX_DATA_HI);
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_offload_xfer(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	काष्ठा i2c_msg *msgs = drv_data->msgs;
	पूर्णांक num = drv_data->num_msgs;
	अचिन्हित दीर्घ ctrl_reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&drv_data->lock, flags);

	/* Build transaction */
	ctrl_reg = MV64XXX_I2C_BRIDGE_CONTROL_ENABLE |
		(msgs[0].addr << MV64XXX_I2C_BRIDGE_CONTROL_ADDR_SHIFT);

	अगर (msgs[0].flags & I2C_M_TEN)
		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_ADDR_EXT;

	/* Single ग_लिखो message transaction */
	अगर (num == 1 && !(msgs[0].flags & I2C_M_RD)) अणु
		माप_प्रकार len = msgs[0].len - 1;

		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_WR |
			(len << MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT);
		mv64xxx_i2c_prepare_tx(drv_data);
	पूर्ण
	/* Single पढ़ो message transaction */
	अन्यथा अगर (num == 1 && msgs[0].flags & I2C_M_RD) अणु
		माप_प्रकार len = msgs[0].len - 1;

		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_RD |
			(len << MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT);
	पूर्ण
	/*
	 * Transaction with one ग_लिखो and one पढ़ो message. This is
	 * guaranteed by the mv64xx_i2c_can_offload() checks.
	 */
	अन्यथा अगर (num == 2) अणु
		माप_प्रकार lentx = msgs[0].len - 1;
		माप_प्रकार lenrx = msgs[1].len - 1;

		ctrl_reg |=
			MV64XXX_I2C_BRIDGE_CONTROL_RD |
			MV64XXX_I2C_BRIDGE_CONTROL_WR |
			(lentx << MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT) |
			(lenrx << MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT) |
			MV64XXX_I2C_BRIDGE_CONTROL_REPEATED_START;
		mv64xxx_i2c_prepare_tx(drv_data);
	पूर्ण

	/* Execute transaction */
	drv_data->block = 1;
	ग_लिखोl(ctrl_reg, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_CONTROL);
	spin_unlock_irqrestore(&drv_data->lock, flags);

	mv64xxx_i2c_रुको_क्रम_completion(drv_data);

	वापस drv_data->rc;
पूर्ण

अटल bool
mv64xxx_i2c_valid_offload_sz(काष्ठा i2c_msg *msg)
अणु
	वापस msg->len <= 8 && msg->len >= 1;
पूर्ण

अटल bool
mv64xxx_i2c_can_offload(काष्ठा mv64xxx_i2c_data *drv_data)
अणु
	काष्ठा i2c_msg *msgs = drv_data->msgs;
	पूर्णांक num = drv_data->num_msgs;

	अगर (!drv_data->offload_enabled)
		वापस false;

	/*
	 * We can offload a transaction consisting of a single
	 * message, as दीर्घ as the message has a length between 1 and
	 * 8 bytes.
	 */
	अगर (num == 1 && mv64xxx_i2c_valid_offload_sz(msgs))
		वापस true;

	/*
	 * We can offload a transaction consisting of two messages, अगर
	 * the first is a ग_लिखो and a second is a पढ़ो, and both have
	 * a length between 1 and 8 bytes.
	 */
	अगर (num == 2 &&
	    mv64xxx_i2c_valid_offload_sz(msgs) &&
	    mv64xxx_i2c_valid_offload_sz(msgs + 1) &&
	    !(msgs[0].flags & I2C_M_RD) &&
	    msgs[1].flags & I2C_M_RD)
		वापस true;

	वापस false;
पूर्ण

/*
 *****************************************************************************
 *
 *	I2C Core Support Routines (Interface to higher level I2C code)
 *
 *****************************************************************************
 */
अटल u32
mv64xxx_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा mv64xxx_i2c_data *drv_data = i2c_get_adapdata(adap);
	पूर्णांक rc, ret = num;

	rc = pm_runसमय_resume_and_get(&adap->dev);
	अगर (rc)
		वापस rc;

	BUG_ON(drv_data->msgs != शून्य);
	drv_data->msgs = msgs;
	drv_data->num_msgs = num;

	अगर (mv64xxx_i2c_can_offload(drv_data))
		rc = mv64xxx_i2c_offload_xfer(drv_data);
	अन्यथा
		rc = mv64xxx_i2c_execute_msg(drv_data, &msgs[0], num == 1);

	अगर (rc < 0)
		ret = rc;

	drv_data->num_msgs = 0;
	drv_data->msgs = शून्य;

	pm_runसमय_mark_last_busy(&adap->dev);
	pm_runसमय_put_स्वतःsuspend(&adap->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mv64xxx_i2c_algo = अणु
	.master_xfer = mv64xxx_i2c_xfer,
	.functionality = mv64xxx_i2c_functionality,
पूर्ण;

/*
 *****************************************************************************
 *
 *	Driver Interface & Early Init Routines
 *
 *****************************************************************************
 */
अटल स्थिर काष्ठा of_device_id mv64xxx_i2c_of_match_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-i2c", .data = &mv64xxx_i2c_regs_sun4iपूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-i2c", .data = &mv64xxx_i2c_regs_sun4iपूर्ण,
	अणु .compatible = "marvell,mv64xxx-i2c", .data = &mv64xxx_i2c_regs_mv64xxxपूर्ण,
	अणु .compatible = "marvell,mv78230-i2c", .data = &mv64xxx_i2c_regs_mv64xxxपूर्ण,
	अणु .compatible = "marvell,mv78230-a0-i2c", .data = &mv64xxx_i2c_regs_mv64xxxपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mv64xxx_i2c_of_match_table);

#अगर_घोषित CONFIG_OF
अटल पूर्णांक
mv64xxx_calc_freq(काष्ठा mv64xxx_i2c_data *drv_data,
		  स्थिर पूर्णांक tclk, स्थिर पूर्णांक n, स्थिर पूर्णांक m)
अणु
	अगर (drv_data->clk_n_base_0)
		वापस tclk / (10 * (m + 1) * (1 << n));
	अन्यथा
		वापस tclk / (10 * (m + 1) * (2 << n));
पूर्ण

अटल bool
mv64xxx_find_baud_factors(काष्ठा mv64xxx_i2c_data *drv_data,
			  स्थिर u32 req_freq, स्थिर u32 tclk)
अणु
	पूर्णांक freq, delta, best_delta = पूर्णांक_उच्च;
	पूर्णांक m, n;

	क्रम (n = 0; n <= 7; n++)
		क्रम (m = 0; m <= 15; m++) अणु
			freq = mv64xxx_calc_freq(drv_data, tclk, n, m);
			delta = req_freq - freq;
			अगर (delta >= 0 && delta < best_delta) अणु
				drv_data->freq_m = m;
				drv_data->freq_n = n;
				best_delta = delta;
			पूर्ण
			अगर (best_delta == 0)
				वापस true;
		पूर्ण
	अगर (best_delta == पूर्णांक_उच्च)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक
mv64xxx_of_config(काष्ठा mv64xxx_i2c_data *drv_data,
		  काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *device;
	काष्ठा device_node *np = dev->of_node;
	u32 bus_freq, tclk;
	पूर्णांक rc = 0;

	/* CLK is mandatory when using DT to describe the i2c bus. We
	 * need to know tclk in order to calculate bus घड़ी
	 * factors.
	 */
	अगर (!drv_data->clk) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण
	tclk = clk_get_rate(drv_data->clk);

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &bus_freq))
		bus_freq = I2C_MAX_STANDARD_MODE_FREQ; /* 100kHz by शेष */

	अगर (of_device_is_compatible(np, "allwinner,sun4i-a10-i2c") ||
	    of_device_is_compatible(np, "allwinner,sun6i-a31-i2c"))
		drv_data->clk_n_base_0 = true;

	अगर (!mv64xxx_find_baud_factors(drv_data, bus_freq, tclk)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	drv_data->rstc = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(drv_data->rstc)) अणु
		rc = PTR_ERR(drv_data->rstc);
		जाओ out;
	पूर्ण

	/* Its not yet defined how समयouts will be specअगरied in device tree.
	 * So hard code the value to 1 second.
	 */
	drv_data->adapter.समयout = HZ;

	device = of_match_device(mv64xxx_i2c_of_match_table, dev);
	अगर (!device)
		वापस -ENODEV;

	स_नकल(&drv_data->reg_offsets, device->data, माप(drv_data->reg_offsets));

	/*
	 * For controllers embedded in new SoCs activate the
	 * Transaction Generator support and the errata fix.
	 */
	अगर (of_device_is_compatible(np, "marvell,mv78230-i2c")) अणु
		drv_data->offload_enabled = true;
		/* The delay is only needed in standard mode (100kHz) */
		अगर (bus_freq <= I2C_MAX_STANDARD_MODE_FREQ)
			drv_data->errata_delay = true;
	पूर्ण

	अगर (of_device_is_compatible(np, "marvell,mv78230-a0-i2c")) अणु
		drv_data->offload_enabled = false;
		/* The delay is only needed in standard mode (100kHz) */
		अगर (bus_freq <= I2C_MAX_STANDARD_MODE_FREQ)
			drv_data->errata_delay = true;
	पूर्ण

	अगर (of_device_is_compatible(np, "allwinner,sun6i-a31-i2c"))
		drv_data->irq_clear_inverted = true;

out:
	वापस rc;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल पूर्णांक
mv64xxx_of_config(काष्ठा mv64xxx_i2c_data *drv_data,
		  काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक mv64xxx_i2c_init_recovery_info(काष्ठा mv64xxx_i2c_data *drv_data,
					  काष्ठा device *dev)
अणु
	काष्ठा i2c_bus_recovery_info *rinfo = &drv_data->rinfo;

	rinfo->pinctrl = devm_pinctrl_get(dev);
	अगर (IS_ERR(rinfo->pinctrl)) अणु
		अगर (PTR_ERR(rinfo->pinctrl) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(dev, "can't get pinctrl, bus recovery not supported\n");
		वापस PTR_ERR(rinfo->pinctrl);
	पूर्ण अन्यथा अगर (!rinfo->pinctrl) अणु
		वापस -ENODEV;
	पूर्ण

	drv_data->adapter.bus_recovery_info = rinfo;
	वापस 0;
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mv64xxx_i2c_data *drv_data = dev_get_drvdata(dev);

	reset_control_निश्चित(drv_data->rstc);
	clk_disable_unprepare(drv_data->reg_clk);
	clk_disable_unprepare(drv_data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mv64xxx_i2c_data *drv_data = dev_get_drvdata(dev);

	clk_prepare_enable(drv_data->clk);
	clk_prepare_enable(drv_data->reg_clk);
	reset_control_reset(drv_data->rstc);

	mv64xxx_i2c_hw_init(drv_data);

	वापस 0;
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा mv64xxx_i2c_data		*drv_data;
	काष्ठा mv64xxx_i2c_pdata	*pdata = dev_get_platdata(&pd->dev);
	पूर्णांक	rc;

	अगर ((!pdata && !pd->dev.of_node))
		वापस -ENODEV;

	drv_data = devm_kzalloc(&pd->dev, माप(काष्ठा mv64xxx_i2c_data),
				GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	drv_data->reg_base = devm_platक्रमm_ioremap_resource(pd, 0);
	अगर (IS_ERR(drv_data->reg_base))
		वापस PTR_ERR(drv_data->reg_base);

	strlcpy(drv_data->adapter.name, MV64XXX_I2C_CTLR_NAME " adapter",
		माप(drv_data->adapter.name));

	init_रुकोqueue_head(&drv_data->रुकोq);
	spin_lock_init(&drv_data->lock);

	/* Not all platक्रमms have घड़ीs */
	drv_data->clk = devm_clk_get(&pd->dev, शून्य);
	अगर (IS_ERR(drv_data->clk)) अणु
		अगर (PTR_ERR(drv_data->clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		drv_data->clk = शून्य;
	पूर्ण

	drv_data->reg_clk = devm_clk_get(&pd->dev, "reg");
	अगर (IS_ERR(drv_data->reg_clk)) अणु
		अगर (PTR_ERR(drv_data->reg_clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		drv_data->reg_clk = शून्य;
	पूर्ण

	drv_data->irq = platक्रमm_get_irq(pd, 0);
	अगर (drv_data->irq < 0)
		वापस drv_data->irq;

	अगर (pdata) अणु
		drv_data->freq_m = pdata->freq_m;
		drv_data->freq_n = pdata->freq_n;
		drv_data->adapter.समयout = msecs_to_jअगरfies(pdata->समयout);
		drv_data->offload_enabled = false;
		स_नकल(&drv_data->reg_offsets, &mv64xxx_i2c_regs_mv64xxx, माप(drv_data->reg_offsets));
	पूर्ण अन्यथा अगर (pd->dev.of_node) अणु
		rc = mv64xxx_of_config(drv_data, &pd->dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = mv64xxx_i2c_init_recovery_info(drv_data, &pd->dev);
	अगर (rc == -EPROBE_DEFER)
		वापस rc;

	drv_data->adapter.dev.parent = &pd->dev;
	drv_data->adapter.algo = &mv64xxx_i2c_algo;
	drv_data->adapter.owner = THIS_MODULE;
	drv_data->adapter.class = I2C_CLASS_DEPRECATED;
	drv_data->adapter.nr = pd->id;
	drv_data->adapter.dev.of_node = pd->dev.of_node;
	platक्रमm_set_drvdata(pd, drv_data);
	i2c_set_adapdata(&drv_data->adapter, drv_data);

	pm_runसमय_set_स्वतःsuspend_delay(&pd->dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(&pd->dev);
	pm_runसमय_enable(&pd->dev);
	अगर (!pm_runसमय_enabled(&pd->dev)) अणु
		rc = mv64xxx_i2c_runसमय_resume(&pd->dev);
		अगर (rc)
			जाओ निकास_disable_pm;
	पूर्ण

	rc = request_irq(drv_data->irq, mv64xxx_i2c_पूर्णांकr, 0,
			 MV64XXX_I2C_CTLR_NAME, drv_data);
	अगर (rc) अणु
		dev_err(&drv_data->adapter.dev,
			"mv64xxx: Can't register intr handler irq%d: %d\n",
			drv_data->irq, rc);
		जाओ निकास_disable_pm;
	पूर्ण अन्यथा अगर ((rc = i2c_add_numbered_adapter(&drv_data->adapter)) != 0) अणु
		dev_err(&drv_data->adapter.dev,
			"mv64xxx: Can't add i2c adapter, rc: %d\n", -rc);
		जाओ निकास_मुक्त_irq;
	पूर्ण

	वापस 0;

निकास_मुक्त_irq:
	मुक्त_irq(drv_data->irq, drv_data);
निकास_disable_pm:
	pm_runसमय_disable(&pd->dev);
	अगर (!pm_runसमय_status_suspended(&pd->dev))
		mv64xxx_i2c_runसमय_suspend(&pd->dev);

	वापस rc;
पूर्ण

अटल पूर्णांक
mv64xxx_i2c_हटाओ(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा mv64xxx_i2c_data		*drv_data = platक्रमm_get_drvdata(pd);

	i2c_del_adapter(&drv_data->adapter);
	मुक्त_irq(drv_data->irq, drv_data);
	pm_runसमय_disable(&pd->dev);
	अगर (!pm_runसमय_status_suspended(&pd->dev))
		mv64xxx_i2c_runसमय_suspend(&pd->dev);

	वापस 0;
पूर्ण

अटल व्योम
mv64xxx_i2c_shutकरोwn(काष्ठा platक्रमm_device *pd)
अणु
	pm_runसमय_disable(&pd->dev);
	अगर (!pm_runसमय_status_suspended(&pd->dev))
		mv64xxx_i2c_runसमय_suspend(&pd->dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mv64xxx_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mv64xxx_i2c_runसमय_suspend,
			   mv64xxx_i2c_runसमय_resume, शून्य)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mv64xxx_i2c_driver = अणु
	.probe	= mv64xxx_i2c_probe,
	.हटाओ	= mv64xxx_i2c_हटाओ,
	.shutकरोwn = mv64xxx_i2c_shutकरोwn,
	.driver	= अणु
		.name	= MV64XXX_I2C_CTLR_NAME,
		.pm     = &mv64xxx_i2c_pm_ops,
		.of_match_table = mv64xxx_i2c_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mv64xxx_i2c_driver);

MODULE_AUTHOR("Mark A. Greer <mgreer@mvista.com>");
MODULE_DESCRIPTION("Marvell mv64xxx host bridge i2c ctlr driver");
MODULE_LICENSE("GPL");
