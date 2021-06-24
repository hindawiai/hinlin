<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C adapter क्रम the IMG Serial Control Bus (SCB) IP block.
 *
 * Copyright (C) 2009, 2010, 2012, 2014 Imagination Technologies Ltd.
 *
 * There are three ways that this I2C controller can be driven:
 *
 * - Raw control of the SDA and SCK संकेतs.
 *
 *   This corresponds to MODE_RAW, which takes control of the संकेतs
 *   directly क्रम a certain number of घड़ी cycles (the INT_TIMING
 *   पूर्णांकerrupt can be used क्रम timing).
 *
 * - Atomic commands. A low level I2C symbol (such as generate
 *   start/stop/ack/nack bit, generate byte, receive byte, and receive
 *   ACK) is given to the hardware, with detection of completion by bits
 *   in the LINESTAT रेजिस्टर.
 *
 *   This mode of operation is used by MODE_ATOMIC, which uses an I2C
 *   state machine in the पूर्णांकerrupt handler to compose/react to I2C
 *   transactions using atomic mode commands, and also by MODE_SEQUENCE,
 *   which emits a simple fixed sequence of atomic mode commands.
 *
 *   Due to software control, the use of atomic commands usually results
 *   in suboptimal use of the bus, with gaps between the I2C symbols जबतक
 *   the driver decides what to करो next.
 *
 * - Automatic mode. A bus address, and whether to पढ़ो/ग_लिखो is
 *   specअगरied, and the hardware takes care of the I2C state machine,
 *   using a FIFO to send/receive bytes of data to an I2C slave. The
 *   driver just has to keep the FIFO drained or filled in response to the
 *   appropriate FIFO पूर्णांकerrupts.
 *
 *   This corresponds to MODE_AUTOMATIC, which manages the FIFOs and deals
 *   with control of repeated start bits between I2C messages.
 *
 *   Use of स्वतःmatic mode and the FIFO can make much more efficient use
 *   of the bus compared to inभागidual atomic commands, with potentially
 *   no wasted समय between I2C symbols or I2C messages.
 *
 * In most हालs MODE_AUTOMATIC is used, however अगर any of the messages in
 * a transaction are zero byte ग_लिखोs (e.g. used by i2cdetect क्रम probing
 * the bus), MODE_ATOMIC must be used since स्वतःmatic mode is normally
 * started by the writing of data पूर्णांकo the FIFO.
 *
 * The other modes are used in specअगरic circumstances where MODE_ATOMIC and
 * MODE_AUTOMATIC aren't appropriate. MODE_RAW is used to implement a bus
 * recovery routine. MODE_SEQUENCE is used to reset the bus and make sure
 * it is in a sane state.
 *
 * Notice that the driver implements a समयr-based समयout mechanism.
 * The reason क्रम this mechanism is to reduce the number of पूर्णांकerrupts
 * received in स्वतःmatic mode.
 *
 * The driver would get a slave event and transaction करोne पूर्णांकerrupts क्रम
 * each atomic mode command that माला_लो completed. However, these events are
 * not needed in स्वतःmatic mode, beहाल those atomic mode commands are
 * managed स्वतःmatically by the hardware.
 *
 * In practice, normal I2C transactions will be complete well beक्रमe you
 * get the समयr पूर्णांकerrupt, as the समयr is re-scheduled during FIFO
 * मुख्यtenance and disabled after the transaction is complete.
 *
 * In this way normal स्वतःmatic mode operation isn't impacted by
 * unnecessary पूर्णांकerrupts, but the exceptional पात condition can still be
 * detected (with a slight delay).
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

/* Register offsets */

#घोषणा SCB_STATUS_REG			0x00
#घोषणा SCB_OVERRIDE_REG		0x04
#घोषणा SCB_READ_ADDR_REG		0x08
#घोषणा SCB_READ_COUNT_REG		0x0c
#घोषणा SCB_WRITE_ADDR_REG		0x10
#घोषणा SCB_READ_DATA_REG		0x14
#घोषणा SCB_WRITE_DATA_REG		0x18
#घोषणा SCB_FIFO_STATUS_REG		0x1c
#घोषणा SCB_CONTROL_SOFT_RESET		0x1f
#घोषणा SCB_CLK_SET_REG			0x3c
#घोषणा SCB_INT_STATUS_REG		0x40
#घोषणा SCB_INT_CLEAR_REG		0x44
#घोषणा SCB_INT_MASK_REG		0x48
#घोषणा SCB_CONTROL_REG			0x4c
#घोषणा SCB_TIME_TPL_REG		0x50
#घोषणा SCB_TIME_TPH_REG		0x54
#घोषणा SCB_TIME_TP2S_REG		0x58
#घोषणा SCB_TIME_TBI_REG		0x60
#घोषणा SCB_TIME_TSL_REG		0x64
#घोषणा SCB_TIME_TDL_REG		0x68
#घोषणा SCB_TIME_TSDL_REG		0x6c
#घोषणा SCB_TIME_TSDH_REG		0x70
#घोषणा SCB_READ_XADDR_REG		0x74
#घोषणा SCB_WRITE_XADDR_REG		0x78
#घोषणा SCB_WRITE_COUNT_REG		0x7c
#घोषणा SCB_CORE_REV_REG		0x80
#घोषणा SCB_TIME_TCKH_REG		0x84
#घोषणा SCB_TIME_TCKL_REG		0x88
#घोषणा SCB_FIFO_FLUSH_REG		0x8c
#घोषणा SCB_READ_FIFO_REG		0x94
#घोषणा SCB_CLEAR_REG			0x98

/* SCB_CONTROL_REG bits */

#घोषणा SCB_CONTROL_CLK_ENABLE		0x1e0
#घोषणा SCB_CONTROL_TRANSACTION_HALT	0x200

#घोषणा FIFO_READ_FULL			BIT(0)
#घोषणा FIFO_READ_EMPTY			BIT(1)
#घोषणा FIFO_WRITE_FULL			BIT(2)
#घोषणा FIFO_WRITE_EMPTY		BIT(3)

/* SCB_CLK_SET_REG bits */
#घोषणा SCB_FILT_DISABLE		BIT(31)
#घोषणा SCB_FILT_BYPASS			BIT(30)
#घोषणा SCB_FILT_INC_MASK		0x7f
#घोषणा SCB_FILT_INC_SHIFT		16
#घोषणा SCB_INC_MASK			0x7f
#घोषणा SCB_INC_SHIFT			8

/* SCB_INT_*_REG bits */

#घोषणा INT_BUS_INACTIVE		BIT(0)
#घोषणा INT_UNEXPECTED_START		BIT(1)
#घोषणा INT_SCLK_LOW_TIMEOUT		BIT(2)
#घोषणा INT_SDAT_LOW_TIMEOUT		BIT(3)
#घोषणा INT_WRITE_ACK_ERR		BIT(4)
#घोषणा INT_ADDR_ACK_ERR		BIT(5)
#घोषणा INT_FIFO_FULL			BIT(9)
#घोषणा INT_FIFO_FILLING		BIT(10)
#घोषणा INT_FIFO_EMPTY			BIT(11)
#घोषणा INT_FIFO_EMPTYING		BIT(12)
#घोषणा INT_TRANSACTION_DONE		BIT(15)
#घोषणा INT_SLAVE_EVENT			BIT(16)
#घोषणा INT_MASTER_HALTED		BIT(17)
#घोषणा INT_TIMING			BIT(18)
#घोषणा INT_STOP_DETECTED		BIT(19)

#घोषणा INT_FIFO_FULL_FILLING	(INT_FIFO_FULL  | INT_FIFO_FILLING)

/* Level पूर्णांकerrupts need clearing after handling instead of beक्रमe */
#घोषणा INT_LEVEL			0x01e00

/* Don't allow any पूर्णांकerrupts जबतक the घड़ी may be off */
#घोषणा INT_ENABLE_MASK_INACTIVE	0x00000

/* Interrupt masks क्रम the dअगरferent driver modes */

#घोषणा INT_ENABLE_MASK_RAW		INT_TIMING

#घोषणा INT_ENABLE_MASK_ATOMIC		(INT_TRANSACTION_DONE | \
					 INT_SLAVE_EVENT      | \
					 INT_ADDR_ACK_ERR     | \
					 INT_WRITE_ACK_ERR)

#घोषणा INT_ENABLE_MASK_AUTOMATIC	(INT_SCLK_LOW_TIMEOUT | \
					 INT_ADDR_ACK_ERR     | \
					 INT_WRITE_ACK_ERR    | \
					 INT_FIFO_FULL        | \
					 INT_FIFO_FILLING     | \
					 INT_FIFO_EMPTY       | \
					 INT_MASTER_HALTED    | \
					 INT_STOP_DETECTED)

#घोषणा INT_ENABLE_MASK_WAITSTOP	(INT_SLAVE_EVENT      | \
					 INT_ADDR_ACK_ERR     | \
					 INT_WRITE_ACK_ERR)

/* SCB_STATUS_REG fields */

#घोषणा LINESTAT_SCLK_LINE_STATUS	BIT(0)
#घोषणा LINESTAT_SCLK_EN		BIT(1)
#घोषणा LINESTAT_SDAT_LINE_STATUS	BIT(2)
#घोषणा LINESTAT_SDAT_EN		BIT(3)
#घोषणा LINESTAT_DET_START_STATUS	BIT(4)
#घोषणा LINESTAT_DET_STOP_STATUS	BIT(5)
#घोषणा LINESTAT_DET_ACK_STATUS		BIT(6)
#घोषणा LINESTAT_DET_NACK_STATUS	BIT(7)
#घोषणा LINESTAT_BUS_IDLE		BIT(8)
#घोषणा LINESTAT_T_DONE_STATUS		BIT(9)
#घोषणा LINESTAT_SCLK_OUT_STATUS	BIT(10)
#घोषणा LINESTAT_SDAT_OUT_STATUS	BIT(11)
#घोषणा LINESTAT_GEN_LINE_MASK_STATUS	BIT(12)
#घोषणा LINESTAT_START_BIT_DET		BIT(13)
#घोषणा LINESTAT_STOP_BIT_DET		BIT(14)
#घोषणा LINESTAT_ACK_DET		BIT(15)
#घोषणा LINESTAT_NACK_DET		BIT(16)
#घोषणा LINESTAT_INPUT_HELD_V		BIT(17)
#घोषणा LINESTAT_ABORT_DET		BIT(18)
#घोषणा LINESTAT_ACK_OR_NACK_DET	(LINESTAT_ACK_DET | LINESTAT_NACK_DET)
#घोषणा LINESTAT_INPUT_DATA		0xff000000
#घोषणा LINESTAT_INPUT_DATA_SHIFT	24

#घोषणा LINESTAT_CLEAR_SHIFT		13
#घोषणा LINESTAT_LATCHED		(0x3f << LINESTAT_CLEAR_SHIFT)

/* SCB_OVERRIDE_REG fields */

#घोषणा OVERRIDE_SCLK_OVR		BIT(0)
#घोषणा OVERRIDE_SCLKEN_OVR		BIT(1)
#घोषणा OVERRIDE_SDAT_OVR		BIT(2)
#घोषणा OVERRIDE_SDATEN_OVR		BIT(3)
#घोषणा OVERRIDE_MASTER			BIT(9)
#घोषणा OVERRIDE_LINE_OVR_EN		BIT(10)
#घोषणा OVERRIDE_सूचीECT			BIT(11)
#घोषणा OVERRIDE_CMD_SHIFT		4
#घोषणा OVERRIDE_CMD_MASK		0x1f
#घोषणा OVERRIDE_DATA_SHIFT		24

#घोषणा OVERRIDE_SCLK_DOWN		(OVERRIDE_LINE_OVR_EN | \
					 OVERRIDE_SCLKEN_OVR)
#घोषणा OVERRIDE_SCLK_UP		(OVERRIDE_LINE_OVR_EN | \
					 OVERRIDE_SCLKEN_OVR | \
					 OVERRIDE_SCLK_OVR)
#घोषणा OVERRIDE_SDAT_DOWN		(OVERRIDE_LINE_OVR_EN | \
					 OVERRIDE_SDATEN_OVR)
#घोषणा OVERRIDE_SDAT_UP		(OVERRIDE_LINE_OVR_EN | \
					 OVERRIDE_SDATEN_OVR | \
					 OVERRIDE_SDAT_OVR)

/* OVERRIDE_CMD values */

#घोषणा CMD_PAUSE			0x00
#घोषणा CMD_GEN_DATA			0x01
#घोषणा CMD_GEN_START			0x02
#घोषणा CMD_GEN_STOP			0x03
#घोषणा CMD_GEN_ACK			0x04
#घोषणा CMD_GEN_NACK			0x05
#घोषणा CMD_RET_DATA			0x08
#घोषणा CMD_RET_ACK			0x09

/* Fixed timing values */

#घोषणा TIMEOUT_TBI			0x0
#घोषणा TIMEOUT_TSL			0xffff
#घोषणा TIMEOUT_TDL			0x0

/* Transaction समयout */

#घोषणा IMG_I2C_TIMEOUT			(msecs_to_jअगरfies(1000))

/*
 * Worst incs are 1 (innacurate) and 16*256 (irregular).
 * So a sensible inc is the logarithmic mean: 64 (2^6), which is
 * in the middle of the valid range (0-127).
 */
#घोषणा SCB_OPT_INC		64

/* Setup the घड़ी enable filtering क्रम 25 ns */
#घोषणा SCB_FILT_GLITCH		25

/*
 * Bits to वापस from पूर्णांकerrupt handler functions क्रम dअगरferent modes.
 * This delays completion until we've finished with the रेजिस्टरs, so that the
 * function रुकोing क्रम completion can safely disable the घड़ी to save घातer.
 */
#घोषणा ISR_COMPLETE_M		BIT(31)
#घोषणा ISR_FATAL_M		BIT(30)
#घोषणा ISR_WAITSTOP		BIT(29)
#घोषणा ISR_STATUS_M		0x0000ffff	/* contains +ve त्रुटि_सं */
#घोषणा ISR_COMPLETE(err)	(ISR_COMPLETE_M | (ISR_STATUS_M & (err)))
#घोषणा ISR_FATAL(err)		(ISR_COMPLETE(err) | ISR_FATAL_M)

#घोषणा IMG_I2C_PM_TIMEOUT	1000 /* ms */

क्रमागत img_i2c_mode अणु
	MODE_INACTIVE,
	MODE_RAW,
	MODE_ATOMIC,
	MODE_AUTOMATIC,
	MODE_SEQUENCE,
	MODE_FATAL,
	MODE_WAITSTOP,
	MODE_SUSPEND,
पूर्ण;

/* Timing parameters क्रम i2c modes (in ns) */
काष्ठा img_i2c_timings अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक max_bitrate;
	अचिन्हित पूर्णांक tckh, tckl, tsdh, tsdl;
	अचिन्हित पूर्णांक tp2s, tpl, tph;
पूर्ण;

/* The timings array must be ordered from slower to faster */
अटल काष्ठा img_i2c_timings timings[] = अणु
	/* Standard mode */
	अणु
		.name = "standard",
		.max_bitrate = I2C_MAX_STANDARD_MODE_FREQ,
		.tckh = 4000,
		.tckl = 4700,
		.tsdh = 4700,
		.tsdl = 8700,
		.tp2s = 4700,
		.tpl = 4700,
		.tph = 4000,
	पूर्ण,
	/* Fast mode */
	अणु
		.name = "fast",
		.max_bitrate = I2C_MAX_FAST_MODE_FREQ,
		.tckh = 600,
		.tckl = 1300,
		.tsdh = 600,
		.tsdl = 1200,
		.tp2s = 1300,
		.tpl = 600,
		.tph = 600,
	पूर्ण,
पूर्ण;

/* Reset dance */
अटल u8 img_i2c_reset_seq[] = अणु CMD_GEN_START,
				  CMD_GEN_DATA, 0xff,
				  CMD_RET_ACK,
				  CMD_GEN_START,
				  CMD_GEN_STOP,
				  0 पूर्ण;
/* Just issue a stop (after an पात condition) */
अटल u8 img_i2c_stop_seq[] = अणु  CMD_GEN_STOP,
				  0 पूर्ण;

/* We're पूर्णांकerested in dअगरferent पूर्णांकerrupts depending on the mode */
अटल अचिन्हित पूर्णांक img_i2c_पूर्णांक_enable_by_mode[] = अणु
	[MODE_INACTIVE]  = INT_ENABLE_MASK_INACTIVE,
	[MODE_RAW]       = INT_ENABLE_MASK_RAW,
	[MODE_ATOMIC]    = INT_ENABLE_MASK_ATOMIC,
	[MODE_AUTOMATIC] = INT_ENABLE_MASK_AUTOMATIC,
	[MODE_SEQUENCE]  = INT_ENABLE_MASK_ATOMIC,
	[MODE_FATAL]     = 0,
	[MODE_WAITSTOP]  = INT_ENABLE_MASK_WAITSTOP,
	[MODE_SUSPEND]   = 0,
पूर्ण;

/* Atomic command names */
अटल स्थिर अक्षर * स्थिर img_i2c_atomic_cmd_names[] = अणु
	[CMD_PAUSE]	= "PAUSE",
	[CMD_GEN_DATA]	= "GEN_DATA",
	[CMD_GEN_START]	= "GEN_START",
	[CMD_GEN_STOP]	= "GEN_STOP",
	[CMD_GEN_ACK]	= "GEN_ACK",
	[CMD_GEN_NACK]	= "GEN_NACK",
	[CMD_RET_DATA]	= "RET_DATA",
	[CMD_RET_ACK]	= "RET_ACK",
पूर्ण;

काष्ठा img_i2c अणु
	काष्ठा i2c_adapter adap;

	व्योम __iomem *base;

	/*
	 * The scb core घड़ी is used to get the input frequency, and to disable
	 * it after every set of transactions to save some घातer.
	 */
	काष्ठा clk *scb_clk, *sys_clk;
	अचिन्हित पूर्णांक bitrate;
	bool need_wr_rd_fence;

	/* state */
	काष्ठा completion msg_complete;
	spinlock_t lock;	/* lock beक्रमe करोing anything with the state */
	काष्ठा i2c_msg msg;

	/* After the last transaction, रुको क्रम a stop bit */
	bool last_msg;
	पूर्णांक msg_status;

	क्रमागत img_i2c_mode mode;
	u32 पूर्णांक_enable;		/* depends on mode */
	u32 line_status;	/* line status over command */

	/*
	 * To aव्योम slave event पूर्णांकerrupts in स्वतःmatic mode, use a समयr to
	 * poll the पात condition अगर we करोn't get an पूर्णांकerrupt क्रम too दीर्घ.
	 */
	काष्ठा समयr_list check_समयr;
	bool t_halt;

	/* atomic mode state */
	bool at_t_करोne;
	bool at_slave_event;
	पूर्णांक at_cur_cmd;
	u8 at_cur_data;

	/* Sequence: either reset or stop. See img_i2c_sequence. */
	u8 *seq;

	/* raw mode */
	अचिन्हित पूर्णांक raw_समयout;
पूर्ण;

अटल पूर्णांक img_i2c_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक img_i2c_runसमय_resume(काष्ठा device *dev);

अटल व्योम img_i2c_ग_लिखोl(काष्ठा img_i2c *i2c, u32 offset, u32 value)
अणु
	ग_लिखोl(value, i2c->base + offset);
पूर्ण

अटल u32 img_i2c_पढ़ोl(काष्ठा img_i2c *i2c, u32 offset)
अणु
	वापस पढ़ोl(i2c->base + offset);
पूर्ण

/*
 * The code to पढ़ो from the master पढ़ो fअगरo, and ग_लिखो to the master
 * ग_लिखो fअगरo, checks a bit in an SCB रेजिस्टर beक्रमe every byte to
 * ensure that the fअगरo is not full (ग_लिखो fअगरo) or empty (पढ़ो fअगरo).
 * Due to घड़ी करोमुख्य crossing inside the SCB block the updated value
 * of this bit is only visible after 2 cycles.
 *
 * The scb_wr_rd_fence() function करोes 2 dummy ग_लिखोs (to the पढ़ो-only
 * revision रेजिस्टर), and it's called after पढ़ोing from or writing to the
 * fअगरos to ensure that subsequent पढ़ोs of the fअगरo status bits करो not पढ़ो
 * stale values.
 */
अटल व्योम img_i2c_wr_rd_fence(काष्ठा img_i2c *i2c)
अणु
	अगर (i2c->need_wr_rd_fence) अणु
		img_i2c_ग_लिखोl(i2c, SCB_CORE_REV_REG, 0);
		img_i2c_ग_लिखोl(i2c, SCB_CORE_REV_REG, 0);
	पूर्ण
पूर्ण

अटल व्योम img_i2c_चयन_mode(काष्ठा img_i2c *i2c, क्रमागत img_i2c_mode mode)
अणु
	i2c->mode = mode;
	i2c->पूर्णांक_enable = img_i2c_पूर्णांक_enable_by_mode[mode];
	i2c->line_status = 0;
पूर्ण

अटल व्योम img_i2c_raw_op(काष्ठा img_i2c *i2c)
अणु
	i2c->raw_समयout = 0;
	img_i2c_ग_लिखोl(i2c, SCB_OVERRIDE_REG,
		OVERRIDE_SCLKEN_OVR |
		OVERRIDE_SDATEN_OVR |
		OVERRIDE_MASTER |
		OVERRIDE_LINE_OVR_EN |
		OVERRIDE_सूचीECT |
		((i2c->at_cur_cmd & OVERRIDE_CMD_MASK) << OVERRIDE_CMD_SHIFT) |
		(i2c->at_cur_data << OVERRIDE_DATA_SHIFT));
पूर्ण

अटल स्थिर अक्षर *img_i2c_atomic_op_name(अचिन्हित पूर्णांक cmd)
अणु
	अगर (unlikely(cmd >= ARRAY_SIZE(img_i2c_atomic_cmd_names)))
		वापस "UNKNOWN";
	वापस img_i2c_atomic_cmd_names[cmd];
पूर्ण

/* Send a single atomic mode command to the hardware */
अटल व्योम img_i2c_atomic_op(काष्ठा img_i2c *i2c, पूर्णांक cmd, u8 data)
अणु
	i2c->at_cur_cmd = cmd;
	i2c->at_cur_data = data;

	/* work around lack of data setup समय when generating data */
	अगर (cmd == CMD_GEN_DATA && i2c->mode == MODE_ATOMIC) अणु
		u32 line_status = img_i2c_पढ़ोl(i2c, SCB_STATUS_REG);

		अगर (line_status & LINESTAT_SDAT_LINE_STATUS && !(data & 0x80)) अणु
			/* hold the data line करोwn क्रम a moment */
			img_i2c_चयन_mode(i2c, MODE_RAW);
			img_i2c_raw_op(i2c);
			वापस;
		पूर्ण
	पूर्ण

	dev_dbg(i2c->adap.dev.parent,
		"atomic cmd=%s (%d) data=%#x\n",
		img_i2c_atomic_op_name(cmd), cmd, data);
	i2c->at_t_करोne = (cmd == CMD_RET_DATA || cmd == CMD_RET_ACK);
	i2c->at_slave_event = false;
	i2c->line_status = 0;

	img_i2c_ग_लिखोl(i2c, SCB_OVERRIDE_REG,
		((cmd & OVERRIDE_CMD_MASK) << OVERRIDE_CMD_SHIFT) |
		OVERRIDE_MASTER |
		OVERRIDE_सूचीECT |
		(data << OVERRIDE_DATA_SHIFT));
पूर्ण

/* Start a transaction in atomic mode */
अटल व्योम img_i2c_atomic_start(काष्ठा img_i2c *i2c)
अणु
	img_i2c_चयन_mode(i2c, MODE_ATOMIC);
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);
	img_i2c_atomic_op(i2c, CMD_GEN_START, 0x00);
पूर्ण

अटल व्योम img_i2c_soft_reset(काष्ठा img_i2c *i2c)
अणु
	i2c->t_halt = false;
	img_i2c_ग_लिखोl(i2c, SCB_CONTROL_REG, 0);
	img_i2c_ग_लिखोl(i2c, SCB_CONTROL_REG,
		       SCB_CONTROL_CLK_ENABLE | SCB_CONTROL_SOFT_RESET);
पूर्ण

/*
 * Enable or release transaction halt क्रम control of repeated starts.
 * In version 3.3 of the IP when transaction halt is set, an पूर्णांकerrupt
 * will be generated after each byte of a transfer instead of after
 * every transfer but beक्रमe the stop bit.
 * Due to this behaviour we have to be careful that every समय we
 * release the transaction halt we have to re-enable it straight away
 * so that we only process a single byte, not करोing so will result in
 * all reमुख्यing bytes been processed and a stop bit being issued,
 * which will prevent us having a repeated start.
 */
अटल व्योम img_i2c_transaction_halt(काष्ठा img_i2c *i2c, bool t_halt)
अणु
	u32 val;

	अगर (i2c->t_halt == t_halt)
		वापस;
	i2c->t_halt = t_halt;
	val = img_i2c_पढ़ोl(i2c, SCB_CONTROL_REG);
	अगर (t_halt)
		val |= SCB_CONTROL_TRANSACTION_HALT;
	अन्यथा
		val &= ~SCB_CONTROL_TRANSACTION_HALT;
	img_i2c_ग_लिखोl(i2c, SCB_CONTROL_REG, val);
पूर्ण

/* Drain data from the FIFO पूर्णांकo the buffer (स्वतःmatic mode) */
अटल व्योम img_i2c_पढ़ो_fअगरo(काष्ठा img_i2c *i2c)
अणु
	जबतक (i2c->msg.len) अणु
		u32 fअगरo_status;
		u8 data;

		img_i2c_wr_rd_fence(i2c);
		fअगरo_status = img_i2c_पढ़ोl(i2c, SCB_FIFO_STATUS_REG);
		अगर (fअगरo_status & FIFO_READ_EMPTY)
			अवरोध;

		data = img_i2c_पढ़ोl(i2c, SCB_READ_DATA_REG);
		*i2c->msg.buf = data;

		img_i2c_ग_लिखोl(i2c, SCB_READ_FIFO_REG, 0xff);
		i2c->msg.len--;
		i2c->msg.buf++;
	पूर्ण
पूर्ण

/* Fill the FIFO with data from the buffer (स्वतःmatic mode) */
अटल व्योम img_i2c_ग_लिखो_fअगरo(काष्ठा img_i2c *i2c)
अणु
	जबतक (i2c->msg.len) अणु
		u32 fअगरo_status;

		img_i2c_wr_rd_fence(i2c);
		fअगरo_status = img_i2c_पढ़ोl(i2c, SCB_FIFO_STATUS_REG);
		अगर (fअगरo_status & FIFO_WRITE_FULL)
			अवरोध;

		img_i2c_ग_लिखोl(i2c, SCB_WRITE_DATA_REG, *i2c->msg.buf);
		i2c->msg.len--;
		i2c->msg.buf++;
	पूर्ण

	/* Disable fअगरo emptying पूर्णांकerrupt अगर nothing more to ग_लिखो */
	अगर (!i2c->msg.len)
		i2c->पूर्णांक_enable &= ~INT_FIFO_EMPTYING;
पूर्ण

/* Start a पढ़ो transaction in स्वतःmatic mode */
अटल व्योम img_i2c_पढ़ो(काष्ठा img_i2c *i2c)
अणु
	img_i2c_चयन_mode(i2c, MODE_AUTOMATIC);
	अगर (!i2c->last_msg)
		i2c->पूर्णांक_enable |= INT_SLAVE_EVENT;

	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);
	img_i2c_ग_लिखोl(i2c, SCB_READ_ADDR_REG, i2c->msg.addr);
	img_i2c_ग_लिखोl(i2c, SCB_READ_COUNT_REG, i2c->msg.len);

	mod_समयr(&i2c->check_समयr, jअगरfies + msecs_to_jअगरfies(1));
पूर्ण

/* Start a ग_लिखो transaction in स्वतःmatic mode */
अटल व्योम img_i2c_ग_लिखो(काष्ठा img_i2c *i2c)
अणु
	img_i2c_चयन_mode(i2c, MODE_AUTOMATIC);
	अगर (!i2c->last_msg)
		i2c->पूर्णांक_enable |= INT_SLAVE_EVENT;

	img_i2c_ग_लिखोl(i2c, SCB_WRITE_ADDR_REG, i2c->msg.addr);
	img_i2c_ग_लिखोl(i2c, SCB_WRITE_COUNT_REG, i2c->msg.len);

	mod_समयr(&i2c->check_समयr, jअगरfies + msecs_to_jअगरfies(1));
	img_i2c_ग_लिखो_fअगरo(i2c);

	/* img_i2c_ग_लिखो_fअगरo() may modअगरy पूर्णांक_enable */
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);
पूर्ण

/*
 * Indicate that the transaction is complete. This is called from the
 * ISR to wake up the रुकोing thपढ़ो, after which the ISR must not
 * access any more SCB रेजिस्टरs.
 */
अटल व्योम img_i2c_complete_transaction(काष्ठा img_i2c *i2c, पूर्णांक status)
अणु
	img_i2c_चयन_mode(i2c, MODE_INACTIVE);
	अगर (status) अणु
		i2c->msg_status = status;
		img_i2c_transaction_halt(i2c, false);
	पूर्ण
	complete(&i2c->msg_complete);
पूर्ण

अटल अचिन्हित पूर्णांक img_i2c_raw_atomic_delay_handler(काष्ठा img_i2c *i2c,
					u32 पूर्णांक_status, u32 line_status)
अणु
	/* Stay in raw mode क्रम this, so we करोn't just loop infinitely */
	img_i2c_atomic_op(i2c, i2c->at_cur_cmd, i2c->at_cur_data);
	img_i2c_चयन_mode(i2c, MODE_ATOMIC);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक img_i2c_raw(काष्ठा img_i2c *i2c, u32 पूर्णांक_status,
				u32 line_status)
अणु
	अगर (पूर्णांक_status & INT_TIMING) अणु
		अगर (i2c->raw_समयout == 0)
			वापस img_i2c_raw_atomic_delay_handler(i2c,
				पूर्णांक_status, line_status);
		--i2c->raw_समयout;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक img_i2c_sequence(काष्ठा img_i2c *i2c, u32 पूर्णांक_status)
अणु
	अटल स्थिर अचिन्हित पूर्णांक जारी_bits[] = अणु
		[CMD_GEN_START] = LINESTAT_START_BIT_DET,
		[CMD_GEN_DATA]  = LINESTAT_INPUT_HELD_V,
		[CMD_RET_ACK]   = LINESTAT_ACK_DET | LINESTAT_NACK_DET,
		[CMD_RET_DATA]  = LINESTAT_INPUT_HELD_V,
		[CMD_GEN_STOP]  = LINESTAT_STOP_BIT_DET,
	पूर्ण;
	पूर्णांक next_cmd = -1;
	u8 next_data = 0x00;

	अगर (पूर्णांक_status & INT_SLAVE_EVENT)
		i2c->at_slave_event = true;
	अगर (पूर्णांक_status & INT_TRANSACTION_DONE)
		i2c->at_t_करोne = true;

	अगर (!i2c->at_slave_event || !i2c->at_t_करोne)
		वापस 0;

	/* रुको अगर no जारी bits are set */
	अगर (i2c->at_cur_cmd >= 0 &&
	    i2c->at_cur_cmd < ARRAY_SIZE(जारी_bits)) अणु
		अचिन्हित पूर्णांक cont_bits = जारी_bits[i2c->at_cur_cmd];

		अगर (cont_bits) अणु
			cont_bits |= LINESTAT_ABORT_DET;
			अगर (!(i2c->line_status & cont_bits))
				वापस 0;
		पूर्ण
	पूर्ण

	/* follow the sequence of commands in i2c->seq */
	next_cmd = *i2c->seq;
	/* stop on a nil */
	अगर (!next_cmd) अणु
		img_i2c_ग_लिखोl(i2c, SCB_OVERRIDE_REG, 0);
		वापस ISR_COMPLETE(0);
	पूर्ण
	/* when generating data, the next byte is the data */
	अगर (next_cmd == CMD_GEN_DATA) अणु
		++i2c->seq;
		next_data = *i2c->seq;
	पूर्ण
	++i2c->seq;
	img_i2c_atomic_op(i2c, next_cmd, next_data);

	वापस 0;
पूर्ण

अटल व्योम img_i2c_reset_start(काष्ठा img_i2c *i2c)
अणु
	/* Initiate the magic dance */
	img_i2c_चयन_mode(i2c, MODE_SEQUENCE);
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);
	i2c->seq = img_i2c_reset_seq;
	i2c->at_slave_event = true;
	i2c->at_t_करोne = true;
	i2c->at_cur_cmd = -1;

	/* img_i2c_reset_seq isn't empty so the following won't fail */
	img_i2c_sequence(i2c, 0);
पूर्ण

अटल व्योम img_i2c_stop_start(काष्ठा img_i2c *i2c)
अणु
	/* Initiate a stop bit sequence */
	img_i2c_चयन_mode(i2c, MODE_SEQUENCE);
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);
	i2c->seq = img_i2c_stop_seq;
	i2c->at_slave_event = true;
	i2c->at_t_करोne = true;
	i2c->at_cur_cmd = -1;

	/* img_i2c_stop_seq isn't empty so the following won't fail */
	img_i2c_sequence(i2c, 0);
पूर्ण

अटल अचिन्हित पूर्णांक img_i2c_atomic(काष्ठा img_i2c *i2c,
				   u32 पूर्णांक_status,
				   u32 line_status)
अणु
	पूर्णांक next_cmd = -1;
	u8 next_data = 0x00;

	अगर (पूर्णांक_status & INT_SLAVE_EVENT)
		i2c->at_slave_event = true;
	अगर (पूर्णांक_status & INT_TRANSACTION_DONE)
		i2c->at_t_करोne = true;

	अगर (!i2c->at_slave_event || !i2c->at_t_करोne)
		जाओ next_atomic_cmd;
	अगर (i2c->line_status & LINESTAT_ABORT_DET) अणु
		dev_dbg(i2c->adap.dev.parent, "abort condition detected\n");
		next_cmd = CMD_GEN_STOP;
		i2c->msg_status = -EIO;
		जाओ next_atomic_cmd;
	पूर्ण

	/* i2c->at_cur_cmd may have completed */
	चयन (i2c->at_cur_cmd) अणु
	हाल CMD_GEN_START:
		next_cmd = CMD_GEN_DATA;
		next_data = i2c_8bit_addr_from_msg(&i2c->msg);
		अवरोध;
	हाल CMD_GEN_DATA:
		अगर (i2c->line_status & LINESTAT_INPUT_HELD_V)
			next_cmd = CMD_RET_ACK;
		अवरोध;
	हाल CMD_RET_ACK:
		अगर (i2c->line_status & LINESTAT_ACK_DET ||
		    (i2c->line_status & LINESTAT_NACK_DET &&
		    i2c->msg.flags & I2C_M_IGNORE_NAK)) अणु
			अगर (i2c->msg.len == 0) अणु
				next_cmd = CMD_GEN_STOP;
			पूर्ण अन्यथा अगर (i2c->msg.flags & I2C_M_RD) अणु
				next_cmd = CMD_RET_DATA;
			पूर्ण अन्यथा अणु
				next_cmd = CMD_GEN_DATA;
				next_data = *i2c->msg.buf;
				--i2c->msg.len;
				++i2c->msg.buf;
			पूर्ण
		पूर्ण अन्यथा अगर (i2c->line_status & LINESTAT_NACK_DET) अणु
			i2c->msg_status = -EIO;
			next_cmd = CMD_GEN_STOP;
		पूर्ण
		अवरोध;
	हाल CMD_RET_DATA:
		अगर (i2c->line_status & LINESTAT_INPUT_HELD_V) अणु
			*i2c->msg.buf = (i2c->line_status &
						LINESTAT_INPUT_DATA)
					>> LINESTAT_INPUT_DATA_SHIFT;
			--i2c->msg.len;
			++i2c->msg.buf;
			अगर (i2c->msg.len)
				next_cmd = CMD_GEN_ACK;
			अन्यथा
				next_cmd = CMD_GEN_NACK;
		पूर्ण
		अवरोध;
	हाल CMD_GEN_ACK:
		अगर (i2c->line_status & LINESTAT_ACK_DET) अणु
			next_cmd = CMD_RET_DATA;
		पूर्ण अन्यथा अणु
			i2c->msg_status = -EIO;
			next_cmd = CMD_GEN_STOP;
		पूर्ण
		अवरोध;
	हाल CMD_GEN_NACK:
		next_cmd = CMD_GEN_STOP;
		अवरोध;
	हाल CMD_GEN_STOP:
		img_i2c_ग_लिखोl(i2c, SCB_OVERRIDE_REG, 0);
		वापस ISR_COMPLETE(0);
	शेष:
		dev_err(i2c->adap.dev.parent, "bad atomic command %d\n",
			i2c->at_cur_cmd);
		i2c->msg_status = -EIO;
		next_cmd = CMD_GEN_STOP;
		अवरोध;
	पूर्ण

next_atomic_cmd:
	अगर (next_cmd != -1) अणु
		/* करोn't actually stop unless we're the last transaction */
		अगर (next_cmd == CMD_GEN_STOP && !i2c->msg_status &&
						!i2c->last_msg)
			वापस ISR_COMPLETE(0);
		img_i2c_atomic_op(i2c, next_cmd, next_data);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Timer function to check अगर something has gone wrong in स्वतःmatic mode (so we
 * करोn't have to handle so many पूर्णांकerrupts just to catch an exception).
 */
अटल व्योम img_i2c_check_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा img_i2c *i2c = from_समयr(i2c, t, check_समयr);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक line_status;

	spin_lock_irqsave(&i2c->lock, flags);
	line_status = img_i2c_पढ़ोl(i2c, SCB_STATUS_REG);

	/* check क्रम an पात condition */
	अगर (line_status & LINESTAT_ABORT_DET) अणु
		dev_dbg(i2c->adap.dev.parent,
			"abort condition detected by check timer\n");
		/* enable slave event पूर्णांकerrupt mask to trigger irq */
		img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG,
			       i2c->पूर्णांक_enable | INT_SLAVE_EVENT);
	पूर्ण

	spin_unlock_irqrestore(&i2c->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक img_i2c_स्वतः(काष्ठा img_i2c *i2c,
				 अचिन्हित पूर्णांक पूर्णांक_status,
				 अचिन्हित पूर्णांक line_status)
अणु
	अगर (पूर्णांक_status & (INT_WRITE_ACK_ERR | INT_ADDR_ACK_ERR))
		वापस ISR_COMPLETE(EIO);

	अगर (line_status & LINESTAT_ABORT_DET) अणु
		dev_dbg(i2c->adap.dev.parent, "abort condition detected\n");
		/* empty the पढ़ो fअगरo */
		अगर ((i2c->msg.flags & I2C_M_RD) &&
		    (पूर्णांक_status & INT_FIFO_FULL_FILLING))
			img_i2c_पढ़ो_fअगरo(i2c);
		/* use atomic mode and try to क्रमce a stop bit */
		i2c->msg_status = -EIO;
		img_i2c_stop_start(i2c);
		वापस 0;
	पूर्ण

	/* Enable transaction halt on start bit */
	अगर (!i2c->last_msg && line_status & LINESTAT_START_BIT_DET) अणु
		img_i2c_transaction_halt(i2c, !i2c->last_msg);
		/* we're no दीर्घer पूर्णांकerested in the slave event */
		i2c->पूर्णांक_enable &= ~INT_SLAVE_EVENT;
	पूर्ण

	mod_समयr(&i2c->check_समयr, jअगरfies + msecs_to_jअगरfies(1));

	अगर (पूर्णांक_status & INT_STOP_DETECTED) अणु
		/* Drain reमुख्यing data in FIFO and complete transaction */
		अगर (i2c->msg.flags & I2C_M_RD)
			img_i2c_पढ़ो_fअगरo(i2c);
		वापस ISR_COMPLETE(0);
	पूर्ण

	अगर (i2c->msg.flags & I2C_M_RD) अणु
		अगर (पूर्णांक_status & (INT_FIFO_FULL_FILLING | INT_MASTER_HALTED)) अणु
			img_i2c_पढ़ो_fअगरo(i2c);
			अगर (i2c->msg.len == 0)
				वापस ISR_WAITSTOP;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पूर्णांक_status & (INT_FIFO_EMPTY | INT_MASTER_HALTED)) अणु
			अगर ((पूर्णांक_status & INT_FIFO_EMPTY) &&
			    i2c->msg.len == 0)
				वापस ISR_WAITSTOP;
			img_i2c_ग_लिखो_fअगरo(i2c);
		पूर्ण
	पूर्ण
	अगर (पूर्णांक_status & INT_MASTER_HALTED) अणु
		/*
		 * Release and then enable transaction halt, to
		 * allow only a single byte to proceed.
		 */
		img_i2c_transaction_halt(i2c, false);
		img_i2c_transaction_halt(i2c, !i2c->last_msg);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t img_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा img_i2c *i2c = (काष्ठा img_i2c *)dev_id;
	u32 पूर्णांक_status, line_status;
	/* We handle transaction completion AFTER accessing रेजिस्टरs */
	अचिन्हित पूर्णांक hret;

	/* Read पूर्णांकerrupt status रेजिस्टर. */
	पूर्णांक_status = img_i2c_पढ़ोl(i2c, SCB_INT_STATUS_REG);
	/* Clear detected पूर्णांकerrupts. */
	img_i2c_ग_लिखोl(i2c, SCB_INT_CLEAR_REG, पूर्णांक_status);

	/*
	 * Read line status and clear it until it actually is clear.  We have
	 * to be careful not to lose any line status bits that get latched.
	 */
	line_status = img_i2c_पढ़ोl(i2c, SCB_STATUS_REG);
	अगर (line_status & LINESTAT_LATCHED) अणु
		img_i2c_ग_लिखोl(i2c, SCB_CLEAR_REG,
			      (line_status & LINESTAT_LATCHED)
				>> LINESTAT_CLEAR_SHIFT);
		img_i2c_wr_rd_fence(i2c);
	पूर्ण

	spin_lock(&i2c->lock);

	/* Keep track of line status bits received */
	i2c->line_status &= ~LINESTAT_INPUT_DATA;
	i2c->line_status |= line_status;

	/*
	 * Certain पूर्णांकerrupts indicate that sclk low समयout is not
	 * a problem. If any of these are set, just जारी.
	 */
	अगर ((पूर्णांक_status & INT_SCLK_LOW_TIMEOUT) &&
	    !(पूर्णांक_status & (INT_SLAVE_EVENT |
			    INT_FIFO_EMPTY |
			    INT_FIFO_FULL))) अणु
		dev_crit(i2c->adap.dev.parent,
			 "fatal: clock low timeout occurred %s addr 0x%02x\n",
			 (i2c->msg.flags & I2C_M_RD) ? "reading" : "writing",
			 i2c->msg.addr);
		hret = ISR_FATAL(EIO);
		जाओ out;
	पूर्ण

	अगर (i2c->mode == MODE_ATOMIC)
		hret = img_i2c_atomic(i2c, पूर्णांक_status, line_status);
	अन्यथा अगर (i2c->mode == MODE_AUTOMATIC)
		hret = img_i2c_स्वतः(i2c, पूर्णांक_status, line_status);
	अन्यथा अगर (i2c->mode == MODE_SEQUENCE)
		hret = img_i2c_sequence(i2c, पूर्णांक_status);
	अन्यथा अगर (i2c->mode == MODE_WAITSTOP && (पूर्णांक_status & INT_SLAVE_EVENT) &&
			 (line_status & LINESTAT_STOP_BIT_DET))
		hret = ISR_COMPLETE(0);
	अन्यथा अगर (i2c->mode == MODE_RAW)
		hret = img_i2c_raw(i2c, पूर्णांक_status, line_status);
	अन्यथा
		hret = 0;

	/* Clear detected level पूर्णांकerrupts. */
	img_i2c_ग_लिखोl(i2c, SCB_INT_CLEAR_REG, पूर्णांक_status & INT_LEVEL);

out:
	अगर (hret & ISR_WAITSTOP) अणु
		/*
		 * Only रुको क्रम stop on last message.
		 * Also we may alपढ़ोy have detected the stop bit.
		 */
		अगर (!i2c->last_msg || i2c->line_status & LINESTAT_STOP_BIT_DET)
			hret = ISR_COMPLETE(0);
		अन्यथा
			img_i2c_चयन_mode(i2c, MODE_WAITSTOP);
	पूर्ण

	/* now we've finished using regs, handle transaction completion */
	अगर (hret & ISR_COMPLETE_M) अणु
		पूर्णांक status = -(hret & ISR_STATUS_M);

		img_i2c_complete_transaction(i2c, status);
		अगर (hret & ISR_FATAL_M)
			img_i2c_चयन_mode(i2c, MODE_FATAL);
	पूर्ण

	/* Enable पूर्णांकerrupts (पूर्णांक_enable may be altered by changing mode) */
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);

	spin_unlock(&i2c->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* Force a bus reset sequence and रुको क्रम it to complete */
अटल पूर्णांक img_i2c_reset_bus(काष्ठा img_i2c *i2c)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समय_left;

	spin_lock_irqsave(&i2c->lock, flags);
	reinit_completion(&i2c->msg_complete);
	img_i2c_reset_start(i2c);
	spin_unlock_irqrestore(&i2c->lock, flags);

	समय_left = रुको_क्रम_completion_समयout(&i2c->msg_complete,
					      IMG_I2C_TIMEOUT);
	अगर (समय_left == 0)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक img_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			पूर्णांक num)
अणु
	काष्ठा img_i2c *i2c = i2c_get_adapdata(adap);
	bool atomic = false;
	पूर्णांक i, ret;
	अचिन्हित दीर्घ समय_left;

	अगर (i2c->mode == MODE_SUSPEND) अणु
		WARN(1, "refusing to service transaction in suspended state\n");
		वापस -EIO;
	पूर्ण

	अगर (i2c->mode == MODE_FATAL)
		वापस -EIO;

	क्रम (i = 0; i < num; i++) अणु
		/*
		 * 0 byte पढ़ोs are not possible because the slave could try
		 * and pull the data line low, preventing a stop bit.
		 */
		अगर (!msgs[i].len && msgs[i].flags & I2C_M_RD)
			वापस -EIO;
		/*
		 * 0 byte ग_लिखोs are possible and used क्रम probing, but we
		 * cannot करो them in स्वतःmatic mode, so use atomic mode
		 * instead.
		 *
		 * Also, the I2C_M_IGNORE_NAK mode can only be implemented
		 * in atomic mode.
		 */
		अगर (!msgs[i].len ||
		    (msgs[i].flags & I2C_M_IGNORE_NAK))
			atomic = true;
	पूर्ण

	ret = pm_runसमय_resume_and_get(adap->dev.parent);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा i2c_msg *msg = &msgs[i];
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&i2c->lock, flags);

		/*
		 * Make a copy of the message काष्ठा. We mustn't modअगरy the
		 * original or we'll confuse drivers and i2c-dev.
		 */
		i2c->msg = *msg;
		i2c->msg_status = 0;

		/*
		 * After the last message we must have रुकोed क्रम a stop bit.
		 * Not रुकोing can cause problems when the घड़ी is disabled
		 * beक्रमe the stop bit is sent, and the linux I2C पूर्णांकerface
		 * requires separate transfers not to joined with repeated
		 * start.
		 */
		i2c->last_msg = (i == num - 1);
		reinit_completion(&i2c->msg_complete);

		/*
		 * Clear line status and all पूर्णांकerrupts beक्रमe starting a
		 * transfer, as we may have unserviced पूर्णांकerrupts from
		 * previous transfers that might be handled in the context
		 * of the new transfer.
		 */
		img_i2c_ग_लिखोl(i2c, SCB_INT_CLEAR_REG, ~0);
		img_i2c_ग_लिखोl(i2c, SCB_CLEAR_REG, ~0);

		अगर (atomic) अणु
			img_i2c_atomic_start(i2c);
		पूर्ण अन्यथा अणु
			/*
			 * Enable transaction halt अगर not the last message in
			 * the queue so that we can control repeated starts.
			 */
			img_i2c_transaction_halt(i2c, !i2c->last_msg);

			अगर (msg->flags & I2C_M_RD)
				img_i2c_पढ़ो(i2c);
			अन्यथा
				img_i2c_ग_लिखो(i2c);

			/*
			 * Release and then enable transaction halt, to
			 * allow only a single byte to proceed.
			 * This करोesn't have an effect on the initial transfer
			 * but will allow the following transfers to start
			 * processing अगर the previous transfer was marked as
			 * complete जबतक the i2c block was halted.
			 */
			img_i2c_transaction_halt(i2c, false);
			img_i2c_transaction_halt(i2c, !i2c->last_msg);
		पूर्ण
		spin_unlock_irqrestore(&i2c->lock, flags);

		समय_left = रुको_क्रम_completion_समयout(&i2c->msg_complete,
						      IMG_I2C_TIMEOUT);
		del_समयr_sync(&i2c->check_समयr);

		अगर (समय_left == 0) अणु
			dev_err(adap->dev.parent, "i2c transfer timed out\n");
			i2c->msg_status = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		अगर (i2c->msg_status)
			अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(adap->dev.parent);
	pm_runसमय_put_स्वतःsuspend(adap->dev.parent);

	वापस i2c->msg_status ? i2c->msg_status : num;
पूर्ण

अटल u32 img_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm img_i2c_algo = अणु
	.master_xfer = img_i2c_xfer,
	.functionality = img_i2c_func,
पूर्ण;

अटल पूर्णांक img_i2c_init(काष्ठा img_i2c *i2c)
अणु
	अचिन्हित पूर्णांक clk_khz, bitrate_khz, clk_period, tckh, tckl, tsdh;
	अचिन्हित पूर्णांक i, data, prescale, inc, पूर्णांक_bitrate, filt;
	काष्ठा img_i2c_timings timing;
	u32 rev;
	पूर्णांक ret;

	ret = pm_runसमय_resume_and_get(i2c->adap.dev.parent);
	अगर (ret < 0)
		वापस ret;

	rev = img_i2c_पढ़ोl(i2c, SCB_CORE_REV_REG);
	अगर ((rev & 0x00ffffff) < 0x00020200) अणु
		dev_info(i2c->adap.dev.parent,
			 "Unknown hardware revision (%d.%d.%d.%d)\n",
			 (rev >> 24) & 0xff, (rev >> 16) & 0xff,
			 (rev >> 8) & 0xff, rev & 0xff);
		pm_runसमय_mark_last_busy(i2c->adap.dev.parent);
		pm_runसमय_put_स्वतःsuspend(i2c->adap.dev.parent);
		वापस -EINVAL;
	पूर्ण

	/* Fencing enabled by शेष. */
	i2c->need_wr_rd_fence = true;

	/* Determine what mode we're in from the bitrate */
	timing = timings[0];
	क्रम (i = 0; i < ARRAY_SIZE(timings); i++) अणु
		अगर (i2c->bitrate <= timings[i].max_bitrate) अणु
			timing = timings[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i2c->bitrate > timings[ARRAY_SIZE(timings) - 1].max_bitrate) अणु
		dev_warn(i2c->adap.dev.parent,
			 "requested bitrate (%u) is higher than the max bitrate supported (%u)\n",
			 i2c->bitrate,
			 timings[ARRAY_SIZE(timings) - 1].max_bitrate);
		timing = timings[ARRAY_SIZE(timings) - 1];
		i2c->bitrate = timing.max_bitrate;
	पूर्ण

	bitrate_khz = i2c->bitrate / 1000;
	clk_khz = clk_get_rate(i2c->scb_clk) / 1000;

	/* Find the prescale that would give us that inc (approx delay = 0) */
	prescale = SCB_OPT_INC * clk_khz / (256 * 16 * bitrate_khz);
	prescale = clamp_t(अचिन्हित पूर्णांक, prescale, 1, 8);
	clk_khz /= prescale;

	/* Setup the घड़ी increment value */
	inc = (256 * 16 * bitrate_khz) / clk_khz;

	/*
	 * The घड़ी generation logic allows to filter glitches on the bus.
	 * This filter is able to हटाओ bus glitches लघुer than 50ns.
	 * If the घड़ी enable rate is greater than 20 MHz, no filtering
	 * is required, so we need to disable it.
	 * If it's between the 20-40 MHz range, there's no need to भागide
	 * the घड़ी to get a filter.
	 */
	अगर (clk_khz < 20000) अणु
		filt = SCB_FILT_DISABLE;
	पूर्ण अन्यथा अगर (clk_khz < 40000) अणु
		filt = SCB_FILT_BYPASS;
	पूर्ण अन्यथा अणु
		/* Calculate filter घड़ी */
		filt = (64000 / ((clk_khz / 1000) * SCB_FILT_GLITCH));

		/* Scale up अगर needed */
		अगर (64000 % ((clk_khz / 1000) * SCB_FILT_GLITCH))
			inc++;

		अगर (filt > SCB_FILT_INC_MASK)
			filt = SCB_FILT_INC_MASK;

		filt = (filt & SCB_FILT_INC_MASK) << SCB_FILT_INC_SHIFT;
	पूर्ण
	data = filt | ((inc & SCB_INC_MASK) << SCB_INC_SHIFT) | (prescale - 1);
	img_i2c_ग_लिखोl(i2c, SCB_CLK_SET_REG, data);

	/* Obtain the घड़ी period of the fx16 घड़ी in ns */
	clk_period = (256 * 1000000) / (clk_khz * inc);

	/* Calculate the bitrate in terms of पूर्णांकernal घड़ी pulses */
	पूर्णांक_bitrate = 1000000 / (bitrate_khz * clk_period);
	अगर ((1000000 % (bitrate_khz * clk_period)) >=
	    ((bitrate_khz * clk_period) / 2))
		पूर्णांक_bitrate++;

	/*
	 * Setup घड़ी duty cycle, start with 50% and adjust TCKH and TCKL
	 * values from there अगर they करोn't meet minimum timing requirements
	 */
	tckh = पूर्णांक_bitrate / 2;
	tckl = पूर्णांक_bitrate - tckh;

	/* Adjust TCKH and TCKL values */
	data = DIV_ROUND_UP(timing.tckl, clk_period);

	अगर (tckl < data) अणु
		tckl = data;
		tckh = पूर्णांक_bitrate - tckl;
	पूर्ण

	अगर (tckh > 0)
		--tckh;

	अगर (tckl > 0)
		--tckl;

	img_i2c_ग_लिखोl(i2c, SCB_TIME_TCKH_REG, tckh);
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TCKL_REG, tckl);

	/* Setup TSDH value */
	tsdh = DIV_ROUND_UP(timing.tsdh, clk_period);

	अगर (tsdh > 1)
		data = tsdh - 1;
	अन्यथा
		data = 0x01;
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TSDH_REG, data);

	/* This value is used later */
	tsdh = data;

	/* Setup TPL value */
	data = timing.tpl / clk_period;
	अगर (data > 0)
		--data;
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TPL_REG, data);

	/* Setup TPH value */
	data = timing.tph / clk_period;
	अगर (data > 0)
		--data;
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TPH_REG, data);

	/* Setup TSDL value to TPL + TSDH + 2 */
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TSDL_REG, data + tsdh + 2);

	/* Setup TP2S value */
	data = timing.tp2s / clk_period;
	अगर (data > 0)
		--data;
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TP2S_REG, data);

	img_i2c_ग_लिखोl(i2c, SCB_TIME_TBI_REG, TIMEOUT_TBI);
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TSL_REG, TIMEOUT_TSL);
	img_i2c_ग_लिखोl(i2c, SCB_TIME_TDL_REG, TIMEOUT_TDL);

	/* Take module out of soft reset and enable घड़ीs */
	img_i2c_soft_reset(i2c);

	/* Disable all पूर्णांकerrupts */
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, 0);

	/* Clear all पूर्णांकerrupts */
	img_i2c_ग_लिखोl(i2c, SCB_INT_CLEAR_REG, ~0);

	/* Clear the scb_line_status events */
	img_i2c_ग_लिखोl(i2c, SCB_CLEAR_REG, ~0);

	/* Enable पूर्णांकerrupts */
	img_i2c_ग_लिखोl(i2c, SCB_INT_MASK_REG, i2c->पूर्णांक_enable);

	/* Perक्रमm a synchronous sequence to reset the bus */
	ret = img_i2c_reset_bus(i2c);

	pm_runसमय_mark_last_busy(i2c->adap.dev.parent);
	pm_runसमय_put_स्वतःsuspend(i2c->adap.dev.parent);

	वापस ret;
पूर्ण

अटल पूर्णांक img_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा img_i2c *i2c;
	पूर्णांक irq, ret;
	u32 val;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा img_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	i2c->sys_clk = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(i2c->sys_clk)) अणु
		dev_err(&pdev->dev, "can't get system clock\n");
		वापस PTR_ERR(i2c->sys_clk);
	पूर्ण

	i2c->scb_clk = devm_clk_get(&pdev->dev, "scb");
	अगर (IS_ERR(i2c->scb_clk)) अणु
		dev_err(&pdev->dev, "can't get core clock\n");
		वापस PTR_ERR(i2c->scb_clk);
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, img_i2c_isr, 0,
			       pdev->name, i2c);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't request irq %d\n", irq);
		वापस ret;
	पूर्ण

	/* Set up the exception check समयr */
	समयr_setup(&i2c->check_समयr, img_i2c_check_समयr, 0);

	i2c->bitrate = timings[0].max_bitrate;
	अगर (!of_property_पढ़ो_u32(node, "clock-frequency", &val))
		i2c->bitrate = val;

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = node;
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &img_i2c_algo;
	i2c->adap.retries = 5;
	i2c->adap.nr = pdev->id;
	snम_लिखो(i2c->adap.name, माप(i2c->adap.name), "IMG SCB I2C");

	img_i2c_चयन_mode(i2c, MODE_INACTIVE);
	spin_lock_init(&i2c->lock);
	init_completion(&i2c->msg_complete);

	platक्रमm_set_drvdata(pdev, i2c);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, IMG_I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_i2c_runसमय_resume(&pdev->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = img_i2c_init(i2c);
	अगर (ret)
		जाओ rpm_disable;

	ret = i2c_add_numbered_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ rpm_disable;

	वापस 0;

rpm_disable:
	अगर (!pm_runसमय_enabled(&pdev->dev))
		img_i2c_runसमय_suspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक img_i2c_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा img_i2c *i2c = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);
	pm_runसमय_disable(&dev->dev);
	अगर (!pm_runसमय_status_suspended(&dev->dev))
		img_i2c_runसमय_suspend(&dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2c *i2c = dev_get_drvdata(dev);

	clk_disable_unprepare(i2c->scb_clk);
	clk_disable_unprepare(i2c->sys_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2c->sys_clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable sys clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(i2c->scb_clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable scb clock\n");
		clk_disable_unprepare(i2c->sys_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		वापस ret;

	img_i2c_चयन_mode(i2c, MODE_SUSPEND);

	वापस 0;
पूर्ण

अटल पूर्णांक img_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा img_i2c *i2c = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		वापस ret;

	img_i2c_init(i2c);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops img_i2c_pm = अणु
	SET_RUNTIME_PM_OPS(img_i2c_runसमय_suspend,
			   img_i2c_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_i2c_suspend, img_i2c_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id img_scb_i2c_match[] = अणु
	अणु .compatible = "img,scb-i2c" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_scb_i2c_match);

अटल काष्ठा platक्रमm_driver img_scb_i2c_driver = अणु
	.driver = अणु
		.name		= "img-i2c-scb",
		.of_match_table	= img_scb_i2c_match,
		.pm		= &img_i2c_pm,
	पूर्ण,
	.probe = img_i2c_probe,
	.हटाओ = img_i2c_हटाओ,
पूर्ण;
module_platक्रमm_driver(img_scb_i2c_driver);

MODULE_AUTHOR("James Hogan <jhogan@kernel.org>");
MODULE_DESCRIPTION("IMG host I2C driver");
MODULE_LICENSE("GPL v2");
