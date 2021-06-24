<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम I2C adapter in Rockchip RK3xxx SoC
 *
 * Max Schwarz <max.schwarz@online.de>
 * based on the patches by Rockchip Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/math64.h>


/* Register Map */
#घोषणा REG_CON        0x00 /* control रेजिस्टर */
#घोषणा REG_CLKDIV     0x04 /* घड़ी भागisor रेजिस्टर */
#घोषणा REG_MRXADDR    0x08 /* slave address क्रम REGISTER_TX */
#घोषणा REG_MRXRADDR   0x0c /* slave रेजिस्टर address क्रम REGISTER_TX */
#घोषणा REG_MTXCNT     0x10 /* number of bytes to be transmitted */
#घोषणा REG_MRXCNT     0x14 /* number of bytes to be received */
#घोषणा REG_IEN        0x18 /* पूर्णांकerrupt enable */
#घोषणा REG_IPD        0x1c /* पूर्णांकerrupt pending */
#घोषणा REG_FCNT       0x20 /* finished count */

/* Data buffer offsets */
#घोषणा TXBUFFER_BASE 0x100
#घोषणा RXBUFFER_BASE 0x200

/* REG_CON bits */
#घोषणा REG_CON_EN        BIT(0)
क्रमागत अणु
	REG_CON_MOD_TX = 0,      /* transmit data */
	REG_CON_MOD_REGISTER_TX, /* select रेजिस्टर and restart */
	REG_CON_MOD_RX,          /* receive data */
	REG_CON_MOD_REGISTER_RX, /* broken: transmits पढ़ो addr AND ग_लिखोs
				  * रेजिस्टर addr */
पूर्ण;
#घोषणा REG_CON_MOD(mod)  ((mod) << 1)
#घोषणा REG_CON_MOD_MASK  (BIT(1) | BIT(2))
#घोषणा REG_CON_START     BIT(3)
#घोषणा REG_CON_STOP      BIT(4)
#घोषणा REG_CON_LASTACK   BIT(5) /* 1: send NACK after last received byte */
#घोषणा REG_CON_ACTACK    BIT(6) /* 1: stop अगर NACK is received */

#घोषणा REG_CON_TUNING_MASK GENMASK_ULL(15, 8)

#घोषणा REG_CON_SDA_CFG(cfg) ((cfg) << 8)
#घोषणा REG_CON_STA_CFG(cfg) ((cfg) << 12)
#घोषणा REG_CON_STO_CFG(cfg) ((cfg) << 14)

/* REG_MRXADDR bits */
#घोषणा REG_MRXADDR_VALID(x) BIT(24 + (x)) /* [x*8+7:x*8] of MRX[R]ADDR valid */

/* REG_IEN/REG_IPD bits */
#घोषणा REG_INT_BTF       BIT(0) /* a byte was transmitted */
#घोषणा REG_INT_BRF       BIT(1) /* a byte was received */
#घोषणा REG_INT_MBTF      BIT(2) /* master data transmit finished */
#घोषणा REG_INT_MBRF      BIT(3) /* master data receive finished */
#घोषणा REG_INT_START     BIT(4) /* START condition generated */
#घोषणा REG_INT_STOP      BIT(5) /* STOP condition generated */
#घोषणा REG_INT_NAKRCV    BIT(6) /* NACK received */
#घोषणा REG_INT_ALL       0x7f

/* Constants */
#घोषणा WAIT_TIMEOUT      1000 /* ms */
#घोषणा DEFAULT_SCL_RATE  (100 * 1000) /* Hz */

/**
 * काष्ठा i2c_spec_values:
 * @min_hold_start_ns: min hold समय (repeated) START condition
 * @min_low_ns: min LOW period of the SCL घड़ी
 * @min_high_ns: min HIGH period of the SCL cloc
 * @min_setup_start_ns: min set-up समय क्रम a repeated START conditio
 * @max_data_hold_ns: max data hold समय
 * @min_data_setup_ns: min data set-up समय
 * @min_setup_stop_ns: min set-up समय क्रम STOP condition
 * @min_hold_buffer_ns: min bus मुक्त समय between a STOP and
 * START condition
 */
काष्ठा i2c_spec_values अणु
	अचिन्हित दीर्घ min_hold_start_ns;
	अचिन्हित दीर्घ min_low_ns;
	अचिन्हित दीर्घ min_high_ns;
	अचिन्हित दीर्घ min_setup_start_ns;
	अचिन्हित दीर्घ max_data_hold_ns;
	अचिन्हित दीर्घ min_data_setup_ns;
	अचिन्हित दीर्घ min_setup_stop_ns;
	अचिन्हित दीर्घ min_hold_buffer_ns;
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values standard_mode_spec = अणु
	.min_hold_start_ns = 4000,
	.min_low_ns = 4700,
	.min_high_ns = 4000,
	.min_setup_start_ns = 4700,
	.max_data_hold_ns = 3450,
	.min_data_setup_ns = 250,
	.min_setup_stop_ns = 4000,
	.min_hold_buffer_ns = 4700,
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values fast_mode_spec = अणु
	.min_hold_start_ns = 600,
	.min_low_ns = 1300,
	.min_high_ns = 600,
	.min_setup_start_ns = 600,
	.max_data_hold_ns = 900,
	.min_data_setup_ns = 100,
	.min_setup_stop_ns = 600,
	.min_hold_buffer_ns = 1300,
पूर्ण;

अटल स्थिर काष्ठा i2c_spec_values fast_mode_plus_spec = अणु
	.min_hold_start_ns = 260,
	.min_low_ns = 500,
	.min_high_ns = 260,
	.min_setup_start_ns = 260,
	.max_data_hold_ns = 400,
	.min_data_setup_ns = 50,
	.min_setup_stop_ns = 260,
	.min_hold_buffer_ns = 500,
पूर्ण;

/**
 * काष्ठा rk3x_i2c_calced_timings:
 * @भाग_low: Divider output क्रम low
 * @भाग_high: Divider output क्रम high
 * @tuning: Used to adjust setup/hold data समय,
 * setup/hold start समय and setup stop समय क्रम
 * v1's calc_timings, the tuning should all be 0
 * क्रम old hardware anyone using v0's calc_timings.
 */
काष्ठा rk3x_i2c_calced_timings अणु
	अचिन्हित दीर्घ भाग_low;
	अचिन्हित दीर्घ भाग_high;
	अचिन्हित पूर्णांक tuning;
पूर्ण;

क्रमागत rk3x_i2c_state अणु
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE,
	STATE_STOP
पूर्ण;

/**
 * काष्ठा rk3x_i2c_soc_data:
 * @grf_offset: offset inside the grf regmap क्रम setting the i2c type
 * @calc_timings: Callback function क्रम i2c timing inक्रमmation calculated
 */
काष्ठा rk3x_i2c_soc_data अणु
	पूर्णांक grf_offset;
	पूर्णांक (*calc_timings)(अचिन्हित दीर्घ, काष्ठा i2c_timings *,
			    काष्ठा rk3x_i2c_calced_timings *);
पूर्ण;

/**
 * काष्ठा rk3x_i2c - निजी data of the controller
 * @adap: corresponding I2C adapter
 * @dev: device क्रम this controller
 * @soc_data: related soc data काष्ठा
 * @regs: भव memory area
 * @clk: function clk क्रम rk3399 or function & Bus clks क्रम others
 * @pclk: Bus clk क्रम rk3399
 * @clk_rate_nb: i2c clk rate change notअगरy
 * @t: I2C known timing inक्रमmation
 * @lock: spinlock क्रम the i2c bus
 * @रुको: the रुकोqueue to रुको क्रम i2c transfer
 * @busy: the condition क्रम the event to रुको क्रम
 * @msg: current i2c message
 * @addr: addr of i2c slave device
 * @mode: mode of i2c transfer
 * @is_last_msg: flag determines whether it is the last msg in this transfer
 * @state: state of i2c transfer
 * @processed: byte length which has been send or received
 * @error: error code क्रम i2c transfer
 */
काष्ठा rk3x_i2c अणु
	काष्ठा i2c_adapter adap;
	काष्ठा device *dev;
	स्थिर काष्ठा rk3x_i2c_soc_data *soc_data;

	/* Hardware resources */
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	काष्ठा notअगरier_block clk_rate_nb;

	/* Settings */
	काष्ठा i2c_timings t;

	/* Synchronization & notअगरication */
	spinlock_t lock;
	रुको_queue_head_t रुको;
	bool busy;

	/* Current message */
	काष्ठा i2c_msg *msg;
	u8 addr;
	अचिन्हित पूर्णांक mode;
	bool is_last_msg;

	/* I2C state machine */
	क्रमागत rk3x_i2c_state state;
	अचिन्हित पूर्णांक processed;
	पूर्णांक error;
पूर्ण;

अटल अंतरभूत व्योम i2c_ग_लिखोl(काष्ठा rk3x_i2c *i2c, u32 value,
			      अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, i2c->regs + offset);
पूर्ण

अटल अंतरभूत u32 i2c_पढ़ोl(काष्ठा rk3x_i2c *i2c, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(i2c->regs + offset);
पूर्ण

/* Reset all पूर्णांकerrupt pending bits */
अटल अंतरभूत व्योम rk3x_i2c_clean_ipd(काष्ठा rk3x_i2c *i2c)
अणु
	i2c_ग_लिखोl(i2c, REG_INT_ALL, REG_IPD);
पूर्ण

/**
 * Generate a START condition, which triggers a REG_INT_START पूर्णांकerrupt.
 */
अटल व्योम rk3x_i2c_start(काष्ठा rk3x_i2c *i2c)
अणु
	u32 val = i2c_पढ़ोl(i2c, REG_CON) & REG_CON_TUNING_MASK;

	i2c_ग_लिखोl(i2c, REG_INT_START, REG_IEN);

	/* enable adapter with correct mode, send START condition */
	val |= REG_CON_EN | REG_CON_MOD(i2c->mode) | REG_CON_START;

	/* अगर we want to react to NACK, set ACTACK bit */
	अगर (!(i2c->msg->flags & I2C_M_IGNORE_NAK))
		val |= REG_CON_ACTACK;

	i2c_ग_लिखोl(i2c, val, REG_CON);
पूर्ण

/**
 * Generate a STOP condition, which triggers a REG_INT_STOP पूर्णांकerrupt.
 *
 * @error: Error code to वापस in rk3x_i2c_xfer
 */
अटल व्योम rk3x_i2c_stop(काष्ठा rk3x_i2c *i2c, पूर्णांक error)
अणु
	अचिन्हित पूर्णांक ctrl;

	i2c->processed = 0;
	i2c->msg = शून्य;
	i2c->error = error;

	अगर (i2c->is_last_msg) अणु
		/* Enable stop पूर्णांकerrupt */
		i2c_ग_लिखोl(i2c, REG_INT_STOP, REG_IEN);

		i2c->state = STATE_STOP;

		ctrl = i2c_पढ़ोl(i2c, REG_CON);
		ctrl |= REG_CON_STOP;
		i2c_ग_लिखोl(i2c, ctrl, REG_CON);
	पूर्ण अन्यथा अणु
		/* Signal rk3x_i2c_xfer to start the next message. */
		i2c->busy = false;
		i2c->state = STATE_IDLE;

		/*
		 * The HW is actually not capable of REPEATED START. But we can
		 * get the पूर्णांकended effect by resetting its पूर्णांकernal state
		 * and issuing an ordinary START.
		 */
		ctrl = i2c_पढ़ोl(i2c, REG_CON) & REG_CON_TUNING_MASK;
		i2c_ग_लिखोl(i2c, ctrl, REG_CON);

		/* संकेत that we are finished with the current msg */
		wake_up(&i2c->रुको);
	पूर्ण
पूर्ण

/**
 * Setup a पढ़ो according to i2c->msg
 */
अटल व्योम rk3x_i2c_prepare_पढ़ो(काष्ठा rk3x_i2c *i2c)
अणु
	अचिन्हित पूर्णांक len = i2c->msg->len - i2c->processed;
	u32 con;

	con = i2c_पढ़ोl(i2c, REG_CON);

	/*
	 * The hw can पढ़ो up to 32 bytes at a समय. If we need more than one
	 * chunk, send an ACK after the last byte of the current chunk.
	 */
	अगर (len > 32) अणु
		len = 32;
		con &= ~REG_CON_LASTACK;
	पूर्ण अन्यथा अणु
		con |= REG_CON_LASTACK;
	पूर्ण

	/* make sure we are in plain RX mode अगर we पढ़ो a second chunk */
	अगर (i2c->processed != 0) अणु
		con &= ~REG_CON_MOD_MASK;
		con |= REG_CON_MOD(REG_CON_MOD_RX);
	पूर्ण

	i2c_ग_लिखोl(i2c, con, REG_CON);
	i2c_ग_लिखोl(i2c, len, REG_MRXCNT);
पूर्ण

/**
 * Fill the transmit buffer with data from i2c->msg
 */
अटल व्योम rk3x_i2c_fill_transmit_buf(काष्ठा rk3x_i2c *i2c)
अणु
	अचिन्हित पूर्णांक i, j;
	u32 cnt = 0;
	u32 val;
	u8 byte;

	क्रम (i = 0; i < 8; ++i) अणु
		val = 0;
		क्रम (j = 0; j < 4; ++j) अणु
			अगर ((i2c->processed == i2c->msg->len) && (cnt != 0))
				अवरोध;

			अगर (i2c->processed == 0 && cnt == 0)
				byte = (i2c->addr & 0x7f) << 1;
			अन्यथा
				byte = i2c->msg->buf[i2c->processed++];

			val |= byte << (j * 8);
			cnt++;
		पूर्ण

		i2c_ग_लिखोl(i2c, val, TXBUFFER_BASE + 4 * i);

		अगर (i2c->processed == i2c->msg->len)
			अवरोध;
	पूर्ण

	i2c_ग_लिखोl(i2c, cnt, REG_MTXCNT);
पूर्ण


/* IRQ handlers क्रम inभागidual states */

अटल व्योम rk3x_i2c_handle_start(काष्ठा rk3x_i2c *i2c, अचिन्हित पूर्णांक ipd)
अणु
	अगर (!(ipd & REG_INT_START)) अणु
		rk3x_i2c_stop(i2c, -EIO);
		dev_warn(i2c->dev, "unexpected irq in START: 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		वापस;
	पूर्ण

	/* ack पूर्णांकerrupt */
	i2c_ग_लिखोl(i2c, REG_INT_START, REG_IPD);

	/* disable start bit */
	i2c_ग_लिखोl(i2c, i2c_पढ़ोl(i2c, REG_CON) & ~REG_CON_START, REG_CON);

	/* enable appropriate पूर्णांकerrupts and transition */
	अगर (i2c->mode == REG_CON_MOD_TX) अणु
		i2c_ग_लिखोl(i2c, REG_INT_MBTF | REG_INT_NAKRCV, REG_IEN);
		i2c->state = STATE_WRITE;
		rk3x_i2c_fill_transmit_buf(i2c);
	पूर्ण अन्यथा अणु
		/* in any other हाल, we are going to be पढ़ोing. */
		i2c_ग_लिखोl(i2c, REG_INT_MBRF | REG_INT_NAKRCV, REG_IEN);
		i2c->state = STATE_READ;
		rk3x_i2c_prepare_पढ़ो(i2c);
	पूर्ण
पूर्ण

अटल व्योम rk3x_i2c_handle_ग_लिखो(काष्ठा rk3x_i2c *i2c, अचिन्हित पूर्णांक ipd)
अणु
	अगर (!(ipd & REG_INT_MBTF)) अणु
		rk3x_i2c_stop(i2c, -EIO);
		dev_err(i2c->dev, "unexpected irq in WRITE: 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		वापस;
	पूर्ण

	/* ack पूर्णांकerrupt */
	i2c_ग_लिखोl(i2c, REG_INT_MBTF, REG_IPD);

	/* are we finished? */
	अगर (i2c->processed == i2c->msg->len)
		rk3x_i2c_stop(i2c, i2c->error);
	अन्यथा
		rk3x_i2c_fill_transmit_buf(i2c);
पूर्ण

अटल व्योम rk3x_i2c_handle_पढ़ो(काष्ठा rk3x_i2c *i2c, अचिन्हित पूर्णांक ipd)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len = i2c->msg->len - i2c->processed;
	u32 val;
	u8 byte;

	/* we only care क्रम MBRF here. */
	अगर (!(ipd & REG_INT_MBRF))
		वापस;

	/* ack पूर्णांकerrupt */
	i2c_ग_लिखोl(i2c, REG_INT_MBRF, REG_IPD);

	/* Can only handle a maximum of 32 bytes at a समय */
	अगर (len > 32)
		len = 32;

	/* पढ़ो the data from receive buffer */
	क्रम (i = 0; i < len; ++i) अणु
		अगर (i % 4 == 0)
			val = i2c_पढ़ोl(i2c, RXBUFFER_BASE + (i / 4) * 4);

		byte = (val >> ((i % 4) * 8)) & 0xff;
		i2c->msg->buf[i2c->processed++] = byte;
	पूर्ण

	/* are we finished? */
	अगर (i2c->processed == i2c->msg->len)
		rk3x_i2c_stop(i2c, i2c->error);
	अन्यथा
		rk3x_i2c_prepare_पढ़ो(i2c);
पूर्ण

अटल व्योम rk3x_i2c_handle_stop(काष्ठा rk3x_i2c *i2c, अचिन्हित पूर्णांक ipd)
अणु
	अचिन्हित पूर्णांक con;

	अगर (!(ipd & REG_INT_STOP)) अणु
		rk3x_i2c_stop(i2c, -EIO);
		dev_err(i2c->dev, "unexpected irq in STOP: 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		वापस;
	पूर्ण

	/* ack पूर्णांकerrupt */
	i2c_ग_लिखोl(i2c, REG_INT_STOP, REG_IPD);

	/* disable STOP bit */
	con = i2c_पढ़ोl(i2c, REG_CON);
	con &= ~REG_CON_STOP;
	i2c_ग_लिखोl(i2c, con, REG_CON);

	i2c->busy = false;
	i2c->state = STATE_IDLE;

	/* संकेत rk3x_i2c_xfer that we are finished */
	wake_up(&i2c->रुको);
पूर्ण

अटल irqवापस_t rk3x_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा rk3x_i2c *i2c = dev_id;
	अचिन्हित पूर्णांक ipd;

	spin_lock(&i2c->lock);

	ipd = i2c_पढ़ोl(i2c, REG_IPD);
	अगर (i2c->state == STATE_IDLE) अणु
		dev_warn(i2c->dev, "irq in STATE_IDLE, ipd = 0x%x\n", ipd);
		rk3x_i2c_clean_ipd(i2c);
		जाओ out;
	पूर्ण

	dev_dbg(i2c->dev, "IRQ: state %d, ipd: %x\n", i2c->state, ipd);

	/* Clean पूर्णांकerrupt bits we करोn't care about */
	ipd &= ~(REG_INT_BRF | REG_INT_BTF);

	अगर (ipd & REG_INT_NAKRCV) अणु
		/*
		 * We got a NACK in the last operation. Depending on whether
		 * IGNORE_NAK is set, we have to stop the operation and report
		 * an error.
		 */
		i2c_ग_लिखोl(i2c, REG_INT_NAKRCV, REG_IPD);

		ipd &= ~REG_INT_NAKRCV;

		अगर (!(i2c->msg->flags & I2C_M_IGNORE_NAK))
			rk3x_i2c_stop(i2c, -ENXIO);
	पूर्ण

	/* is there anything left to handle? */
	अगर ((ipd & REG_INT_ALL) == 0)
		जाओ out;

	चयन (i2c->state) अणु
	हाल STATE_START:
		rk3x_i2c_handle_start(i2c, ipd);
		अवरोध;
	हाल STATE_WRITE:
		rk3x_i2c_handle_ग_लिखो(i2c, ipd);
		अवरोध;
	हाल STATE_READ:
		rk3x_i2c_handle_पढ़ो(i2c, ipd);
		अवरोध;
	हाल STATE_STOP:
		rk3x_i2c_handle_stop(i2c, ipd);
		अवरोध;
	हाल STATE_IDLE:
		अवरोध;
	पूर्ण

out:
	spin_unlock(&i2c->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * Get timing values of I2C specअगरication
 *
 * @speed: Desired SCL frequency
 *
 * Returns: Matched i2c spec values.
 */
अटल स्थिर काष्ठा i2c_spec_values *rk3x_i2c_get_spec(अचिन्हित पूर्णांक speed)
अणु
	अगर (speed <= I2C_MAX_STANDARD_MODE_FREQ)
		वापस &standard_mode_spec;
	अन्यथा अगर (speed <= I2C_MAX_FAST_MODE_FREQ)
		वापस &fast_mode_spec;
	अन्यथा
		वापस &fast_mode_plus_spec;
पूर्ण

/**
 * Calculate भागider values क्रम desired SCL frequency
 *
 * @clk_rate: I2C input घड़ी rate
 * @t: Known I2C timing inक्रमmation
 * @t_calc: Caculated rk3x निजी timings that would be written पूर्णांकo regs
 *
 * Returns: 0 on success, -EINVAL अगर the goal SCL rate is too slow. In that हाल
 * a best-efक्रमt भागider value is वापसed in भागs. If the target rate is
 * too high, we silently use the highest possible rate.
 */
अटल पूर्णांक rk3x_i2c_v0_calc_timings(अचिन्हित दीर्घ clk_rate,
				    काष्ठा i2c_timings *t,
				    काष्ठा rk3x_i2c_calced_timings *t_calc)
अणु
	अचिन्हित दीर्घ min_low_ns, min_high_ns;
	अचिन्हित दीर्घ max_low_ns, min_total_ns;

	अचिन्हित दीर्घ clk_rate_khz, scl_rate_khz;

	अचिन्हित दीर्घ min_low_भाग, min_high_भाग;
	अचिन्हित दीर्घ max_low_भाग;

	अचिन्हित दीर्घ min_भाग_क्रम_hold, min_total_भाग;
	अचिन्हित दीर्घ extra_भाग, extra_low_भाग, ideal_low_भाग;

	अचिन्हित दीर्घ data_hold_buffer_ns = 50;
	स्थिर काष्ठा i2c_spec_values *spec;
	पूर्णांक ret = 0;

	/* Only support standard-mode and fast-mode */
	अगर (WARN_ON(t->bus_freq_hz > I2C_MAX_FAST_MODE_FREQ))
		t->bus_freq_hz = I2C_MAX_FAST_MODE_FREQ;

	/* prevent scl_rate_khz from becoming 0 */
	अगर (WARN_ON(t->bus_freq_hz < 1000))
		t->bus_freq_hz = 1000;

	/*
	 * min_low_ns:  The minimum number of ns we need to hold low to
	 *		meet I2C specअगरication, should include fall समय.
	 * min_high_ns: The minimum number of ns we need to hold high to
	 *		meet I2C specअगरication, should include rise समय.
	 * max_low_ns:  The maximum number of ns we can hold low to meet
	 *		I2C specअगरication.
	 *
	 * Note: max_low_ns should be (maximum data hold समय * 2 - buffer)
	 *	 This is because the i2c host on Rockchip holds the data line
	 *	 क्रम half the low समय.
	 */
	spec = rk3x_i2c_get_spec(t->bus_freq_hz);
	min_high_ns = t->scl_rise_ns + spec->min_high_ns;

	/*
	 * Timings क्रम repeated start:
	 * - controller appears to drop SDA at .875x (7/8) programmed clk high.
	 * - controller appears to keep SCL high क्रम 2x programmed clk high.
	 *
	 * We need to account क्रम those rules in picking our "high" समय so
	 * we meet tSU;STA and tHD;STA बार.
	 */
	min_high_ns = max(min_high_ns, DIV_ROUND_UP(
		(t->scl_rise_ns + spec->min_setup_start_ns) * 1000, 875));
	min_high_ns = max(min_high_ns, DIV_ROUND_UP(
		(t->scl_rise_ns + spec->min_setup_start_ns + t->sda_fall_ns +
		spec->min_high_ns), 2));

	min_low_ns = t->scl_fall_ns + spec->min_low_ns;
	max_low_ns =  spec->max_data_hold_ns * 2 - data_hold_buffer_ns;
	min_total_ns = min_low_ns + min_high_ns;

	/* Adjust to aव्योम overflow */
	clk_rate_khz = DIV_ROUND_UP(clk_rate, 1000);
	scl_rate_khz = t->bus_freq_hz / 1000;

	/*
	 * We need the total भाग to be >= this number
	 * so we करोn't घड़ी too fast.
	 */
	min_total_भाग = DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

	/* These are the min भागiders needed क्रम min hold बार. */
	min_low_भाग = DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);
	min_high_भाग = DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);
	min_भाग_क्रम_hold = (min_low_भाग + min_high_भाग);

	/*
	 * This is the maximum भागider so we करोn't go over the maximum.
	 * We करोn't round up here (we round करोwn) since this is a maximum.
	 */
	max_low_भाग = clk_rate_khz * max_low_ns / (8 * 1000000);

	अगर (min_low_भाग > max_low_भाग) अणु
		WARN_ONCE(true,
			  "Conflicting, min_low_div %lu, max_low_div %lu\n",
			  min_low_भाग, max_low_भाग);
		max_low_भाग = min_low_भाग;
	पूर्ण

	अगर (min_भाग_क्रम_hold > min_total_भाग) अणु
		/*
		 * Time needed to meet hold requirements is important.
		 * Just use that.
		 */
		t_calc->भाग_low = min_low_भाग;
		t_calc->भाग_high = min_high_भाग;
	पूर्ण अन्यथा अणु
		/*
		 * We've got to distribute some समय among the low and high
		 * so we करोn't run too fast.
		 */
		extra_भाग = min_total_भाग - min_भाग_क्रम_hold;

		/*
		 * We'll try to split things up perfectly evenly,
		 * biasing slightly towards having a higher भाग
		 * क्रम low (spend more समय low).
		 */
		ideal_low_भाग = DIV_ROUND_UP(clk_rate_khz * min_low_ns,
					     scl_rate_khz * 8 * min_total_ns);

		/* Don't allow it to go over the maximum */
		अगर (ideal_low_भाग > max_low_भाग)
			ideal_low_भाग = max_low_भाग;

		/*
		 * Handle when the ideal low भाग is going to take up
		 * more than we have.
		 */
		अगर (ideal_low_भाग > min_low_भाग + extra_भाग)
			ideal_low_भाग = min_low_भाग + extra_भाग;

		/* Give low the "ideal" and give high whatever extra is left */
		extra_low_भाग = ideal_low_भाग - min_low_भाग;
		t_calc->भाग_low = ideal_low_भाग;
		t_calc->भाग_high = min_high_भाग + (extra_भाग - extra_low_भाग);
	पूर्ण

	/*
	 * Adjust to the fact that the hardware has an implicit "+1".
	 * NOTE: Above calculations always produce भाग_low > 0 and भाग_high > 0.
	 */
	t_calc->भाग_low--;
	t_calc->भाग_high--;

	/* Give the tuning value 0, that would not update con रेजिस्टर */
	t_calc->tuning = 0;
	/* Maximum भागider supported by hw is 0xffff */
	अगर (t_calc->भाग_low > 0xffff) अणु
		t_calc->भाग_low = 0xffff;
		ret = -EINVAL;
	पूर्ण

	अगर (t_calc->भाग_high > 0xffff) अणु
		t_calc->भाग_high = 0xffff;
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * Calculate timing values क्रम desired SCL frequency
 *
 * @clk_rate: I2C input घड़ी rate
 * @t: Known I2C timing inक्रमmation
 * @t_calc: Caculated rk3x निजी timings that would be written पूर्णांकo regs
 *
 * Returns: 0 on success, -EINVAL अगर the goal SCL rate is too slow. In that हाल
 * a best-efक्रमt भागider value is वापसed in भागs. If the target rate is
 * too high, we silently use the highest possible rate.
 * The following क्रमmulas are v1's method to calculate timings.
 *
 * l = भागl + 1;
 * h = भागh + 1;
 * s = sda_update_config + 1;
 * u = start_setup_config + 1;
 * p = stop_setup_config + 1;
 * T = Tclk_i2c;
 *
 * tHigh = 8 * h * T;
 * tLow = 8 * l * T;
 *
 * tHD;sda = (l * s + 1) * T;
 * tSU;sda = [(8 - s) * l + 1] * T;
 * tI2C = 8 * (l + h) * T;
 *
 * tSU;sta = (8h * u + 1) * T;
 * tHD;sta = [8h * (u + 1) - 1] * T;
 * tSU;sto = (8h * p + 1) * T;
 */
अटल पूर्णांक rk3x_i2c_v1_calc_timings(अचिन्हित दीर्घ clk_rate,
				    काष्ठा i2c_timings *t,
				    काष्ठा rk3x_i2c_calced_timings *t_calc)
अणु
	अचिन्हित दीर्घ min_low_ns, min_high_ns;
	अचिन्हित दीर्घ min_setup_start_ns, min_setup_data_ns;
	अचिन्हित दीर्घ min_setup_stop_ns, max_hold_data_ns;

	अचिन्हित दीर्घ clk_rate_khz, scl_rate_khz;

	अचिन्हित दीर्घ min_low_भाग, min_high_भाग;

	अचिन्हित दीर्घ min_भाग_क्रम_hold, min_total_भाग;
	अचिन्हित दीर्घ extra_भाग, extra_low_भाग;
	अचिन्हित दीर्घ sda_update_cfg, stp_sta_cfg, stp_sto_cfg;

	स्थिर काष्ठा i2c_spec_values *spec;
	पूर्णांक ret = 0;

	/* Support standard-mode, fast-mode and fast-mode plus */
	अगर (WARN_ON(t->bus_freq_hz > I2C_MAX_FAST_MODE_PLUS_FREQ))
		t->bus_freq_hz = I2C_MAX_FAST_MODE_PLUS_FREQ;

	/* prevent scl_rate_khz from becoming 0 */
	अगर (WARN_ON(t->bus_freq_hz < 1000))
		t->bus_freq_hz = 1000;

	/*
	 * min_low_ns: The minimum number of ns we need to hold low to
	 *	       meet I2C specअगरication, should include fall समय.
	 * min_high_ns: The minimum number of ns we need to hold high to
	 *	        meet I2C specअगरication, should include rise समय.
	 */
	spec = rk3x_i2c_get_spec(t->bus_freq_hz);

	/* calculate min-भागh and min-भागl */
	clk_rate_khz = DIV_ROUND_UP(clk_rate, 1000);
	scl_rate_khz = t->bus_freq_hz / 1000;
	min_total_भाग = DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

	min_high_ns = t->scl_rise_ns + spec->min_high_ns;
	min_high_भाग = DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);

	min_low_ns = t->scl_fall_ns + spec->min_low_ns;
	min_low_भाग = DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);

	/*
	 * Final भागh and भागl must be greater than 0, otherwise the
	 * hardware would not output the i2c clk.
	 */
	min_high_भाग = (min_high_भाग < 1) ? 2 : min_high_भाग;
	min_low_भाग = (min_low_भाग < 1) ? 2 : min_low_भाग;

	/* These are the min भागiders needed क्रम min hold बार. */
	min_भाग_क्रम_hold = (min_low_भाग + min_high_भाग);

	/*
	 * This is the maximum भागider so we करोn't go over the maximum.
	 * We करोn't round up here (we round करोwn) since this is a maximum.
	 */
	अगर (min_भाग_क्रम_hold >= min_total_भाग) अणु
		/*
		 * Time needed to meet hold requirements is important.
		 * Just use that.
		 */
		t_calc->भाग_low = min_low_भाग;
		t_calc->भाग_high = min_high_भाग;
	पूर्ण अन्यथा अणु
		/*
		 * We've got to distribute some समय among the low and high
		 * so we करोn't run too fast.
		 * We'll try to split things up by the scale of min_low_भाग and
		 * min_high_भाग, biasing slightly towards having a higher भाग
		 * क्रम low (spend more समय low).
		 */
		extra_भाग = min_total_भाग - min_भाग_क्रम_hold;
		extra_low_भाग = DIV_ROUND_UP(min_low_भाग * extra_भाग,
					     min_भाग_क्रम_hold);

		t_calc->भाग_low = min_low_भाग + extra_low_भाग;
		t_calc->भाग_high = min_high_भाग + (extra_भाग - extra_low_भाग);
	पूर्ण

	/*
	 * calculate sda data hold count by the rules, data_upd_st:3
	 * is a appropriate value to reduce calculated बार.
	 */
	क्रम (sda_update_cfg = 3; sda_update_cfg > 0; sda_update_cfg--) अणु
		max_hold_data_ns =  DIV_ROUND_UP((sda_update_cfg
						 * (t_calc->भाग_low) + 1)
						 * 1000000, clk_rate_khz);
		min_setup_data_ns =  DIV_ROUND_UP(((8 - sda_update_cfg)
						 * (t_calc->भाग_low) + 1)
						 * 1000000, clk_rate_khz);
		अगर ((max_hold_data_ns < spec->max_data_hold_ns) &&
		    (min_setup_data_ns > spec->min_data_setup_ns))
			अवरोध;
	पूर्ण

	/* calculate setup start config */
	min_setup_start_ns = t->scl_rise_ns + spec->min_setup_start_ns;
	stp_sta_cfg = DIV_ROUND_UP(clk_rate_khz * min_setup_start_ns
			   - 1000000, 8 * 1000000 * (t_calc->भाग_high));

	/* calculate setup stop config */
	min_setup_stop_ns = t->scl_rise_ns + spec->min_setup_stop_ns;
	stp_sto_cfg = DIV_ROUND_UP(clk_rate_khz * min_setup_stop_ns
			   - 1000000, 8 * 1000000 * (t_calc->भाग_high));

	t_calc->tuning = REG_CON_SDA_CFG(--sda_update_cfg) |
			 REG_CON_STA_CFG(--stp_sta_cfg) |
			 REG_CON_STO_CFG(--stp_sto_cfg);

	t_calc->भाग_low--;
	t_calc->भाग_high--;

	/* Maximum भागider supported by hw is 0xffff */
	अगर (t_calc->भाग_low > 0xffff) अणु
		t_calc->भाग_low = 0xffff;
		ret = -EINVAL;
	पूर्ण

	अगर (t_calc->भाग_high > 0xffff) अणु
		t_calc->भाग_high = 0xffff;
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rk3x_i2c_adapt_भाग(काष्ठा rk3x_i2c *i2c, अचिन्हित दीर्घ clk_rate)
अणु
	काष्ठा i2c_timings *t = &i2c->t;
	काष्ठा rk3x_i2c_calced_timings calc;
	u64 t_low_ns, t_high_ns;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	ret = i2c->soc_data->calc_timings(clk_rate, t, &calc);
	WARN_ONCE(ret != 0, "Could not reach SCL freq %u", t->bus_freq_hz);

	clk_enable(i2c->pclk);

	spin_lock_irqsave(&i2c->lock, flags);
	val = i2c_पढ़ोl(i2c, REG_CON);
	val &= ~REG_CON_TUNING_MASK;
	val |= calc.tuning;
	i2c_ग_लिखोl(i2c, val, REG_CON);
	i2c_ग_लिखोl(i2c, (calc.भाग_high << 16) | (calc.भाग_low & 0xffff),
		   REG_CLKDIV);
	spin_unlock_irqrestore(&i2c->lock, flags);

	clk_disable(i2c->pclk);

	t_low_ns = भाग_u64(((u64)calc.भाग_low + 1) * 8 * 1000000000, clk_rate);
	t_high_ns = भाग_u64(((u64)calc.भाग_high + 1) * 8 * 1000000000,
			    clk_rate);
	dev_dbg(i2c->dev,
		"CLK %lukhz, Req %uns, Act low %lluns high %lluns\n",
		clk_rate / 1000,
		1000000000 / t->bus_freq_hz,
		t_low_ns, t_high_ns);
पूर्ण

/**
 * rk3x_i2c_clk_notअगरier_cb - Clock rate change callback
 * @nb:		Poपूर्णांकer to notअगरier block
 * @event:	Notअगरication reason
 * @data:	Poपूर्णांकer to notअगरication data object
 *
 * The callback checks whether a valid bus frequency can be generated after the
 * change. If so, the change is acknowledged, otherwise the change is पातed.
 * New भागiders are written to the HW in the pre- or post change notअगरication
 * depending on the scaling direction.
 *
 * Code adapted from i2c-cadence.c.
 *
 * Return:	NOTIFY_STOP अगर the rate change should be पातed, NOTIFY_OK
 *		to acknowledge the change, NOTIFY_DONE अगर the notअगरication is
 *		considered irrelevant.
 */
अटल पूर्णांक rk3x_i2c_clk_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ
				    event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा rk3x_i2c *i2c = container_of(nb, काष्ठा rk3x_i2c, clk_rate_nb);
	काष्ठा rk3x_i2c_calced_timings calc;

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		/*
		 * Try the calculation (but करोn't store the result) ahead of
		 * समय to see अगर we need to block the घड़ी change.  Timings
		 * shouldn't actually take effect until rk3x_i2c_adapt_भाग().
		 */
		अगर (i2c->soc_data->calc_timings(ndata->new_rate, &i2c->t,
						&calc) != 0)
			वापस NOTIFY_STOP;

		/* scale up */
		अगर (ndata->new_rate > ndata->old_rate)
			rk3x_i2c_adapt_भाग(i2c, ndata->new_rate);

		वापस NOTIFY_OK;
	हाल POST_RATE_CHANGE:
		/* scale करोwn */
		अगर (ndata->new_rate < ndata->old_rate)
			rk3x_i2c_adapt_भाग(i2c, ndata->new_rate);
		वापस NOTIFY_OK;
	हाल ABORT_RATE_CHANGE:
		/* scale up */
		अगर (ndata->new_rate > ndata->old_rate)
			rk3x_i2c_adapt_भाग(i2c, ndata->old_rate);
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

/**
 * Setup I2C रेजिस्टरs क्रम an I2C operation specअगरied by msgs, num.
 *
 * Must be called with i2c->lock held.
 *
 * @msgs: I2C msgs to process
 * @num: Number of msgs
 *
 * वापसs: Number of I2C msgs processed or negative in हाल of error
 */
अटल पूर्णांक rk3x_i2c_setup(काष्ठा rk3x_i2c *i2c, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	u32 addr = (msgs[0].addr & 0x7f) << 1;
	पूर्णांक ret = 0;

	/*
	 * The I2C adapter can issue a small (len < 4) ग_लिखो packet beक्रमe
	 * पढ़ोing. This speeds up SMBus-style रेजिस्टर पढ़ोs.
	 * The MRXADDR/MRXRADDR hold the slave address and the slave रेजिस्टर
	 * address in this हाल.
	 */

	अगर (num >= 2 && msgs[0].len < 4 &&
	    !(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD)) अणु
		u32 reg_addr = 0;
		पूर्णांक i;

		dev_dbg(i2c->dev, "Combined write/read from addr 0x%x\n",
			addr >> 1);

		/* Fill MRXRADDR with the रेजिस्टर address(es) */
		क्रम (i = 0; i < msgs[0].len; ++i) अणु
			reg_addr |= msgs[0].buf[i] << (i * 8);
			reg_addr |= REG_MRXADDR_VALID(i);
		पूर्ण

		/* msgs[0] is handled by hw. */
		i2c->msg = &msgs[1];

		i2c->mode = REG_CON_MOD_REGISTER_TX;

		i2c_ग_लिखोl(i2c, addr | REG_MRXADDR_VALID(0), REG_MRXADDR);
		i2c_ग_लिखोl(i2c, reg_addr, REG_MRXRADDR);

		ret = 2;
	पूर्ण अन्यथा अणु
		/*
		 * We'll have to करो it the boring way and process the msgs
		 * one-by-one.
		 */

		अगर (msgs[0].flags & I2C_M_RD) अणु
			addr |= 1; /* set पढ़ो bit */

			/*
			 * We have to transmit the slave addr first. Use
			 * MOD_REGISTER_TX क्रम that purpose.
			 */
			i2c->mode = REG_CON_MOD_REGISTER_TX;
			i2c_ग_लिखोl(i2c, addr | REG_MRXADDR_VALID(0),
				   REG_MRXADDR);
			i2c_ग_लिखोl(i2c, 0, REG_MRXRADDR);
		पूर्ण अन्यथा अणु
			i2c->mode = REG_CON_MOD_TX;
		पूर्ण

		i2c->msg = &msgs[0];

		ret = 1;
	पूर्ण

	i2c->addr = msgs[0].addr;
	i2c->busy = true;
	i2c->state = STATE_START;
	i2c->processed = 0;
	i2c->error = 0;

	rk3x_i2c_clean_ipd(i2c);

	वापस ret;
पूर्ण

अटल पूर्णांक rk3x_i2c_रुको_xfer_poll(काष्ठा rk3x_i2c *i2c)
अणु
	kसमय_प्रकार समयout = kसमय_add_ms(kसमय_get(), WAIT_TIMEOUT);

	जबतक (READ_ONCE(i2c->busy) &&
	       kसमय_compare(kसमय_get(), समयout) < 0) अणु
		udelay(5);
		rk3x_i2c_irq(0, i2c);
	पूर्ण

	वापस !i2c->busy;
पूर्ण

अटल पूर्णांक rk3x_i2c_xfer_common(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msgs, पूर्णांक num, bool polling)
अणु
	काष्ठा rk3x_i2c *i2c = (काष्ठा rk3x_i2c *)adap->algo_data;
	अचिन्हित दीर्घ समयout, flags;
	u32 val;
	पूर्णांक ret = 0;
	पूर्णांक i;

	spin_lock_irqsave(&i2c->lock, flags);

	clk_enable(i2c->clk);
	clk_enable(i2c->pclk);

	i2c->is_last_msg = false;

	/*
	 * Process msgs. We can handle more than one message at once (see
	 * rk3x_i2c_setup()).
	 */
	क्रम (i = 0; i < num; i += ret) अणु
		ret = rk3x_i2c_setup(i2c, msgs + i, num - i);

		अगर (ret < 0) अणु
			dev_err(i2c->dev, "rk3x_i2c_setup() failed\n");
			अवरोध;
		पूर्ण

		अगर (i + ret >= num)
			i2c->is_last_msg = true;

		spin_unlock_irqrestore(&i2c->lock, flags);

		rk3x_i2c_start(i2c);

		अगर (!polling) अणु
			समयout = रुको_event_समयout(i2c->रुको, !i2c->busy,
						     msecs_to_jअगरfies(WAIT_TIMEOUT));
		पूर्ण अन्यथा अणु
			समयout = rk3x_i2c_रुको_xfer_poll(i2c);
		पूर्ण

		spin_lock_irqsave(&i2c->lock, flags);

		अगर (समयout == 0) अणु
			dev_err(i2c->dev, "timeout, ipd: 0x%02x, state: %d\n",
				i2c_पढ़ोl(i2c, REG_IPD), i2c->state);

			/* Force a STOP condition without पूर्णांकerrupt */
			i2c_ग_लिखोl(i2c, 0, REG_IEN);
			val = i2c_पढ़ोl(i2c, REG_CON) & REG_CON_TUNING_MASK;
			val |= REG_CON_EN | REG_CON_STOP;
			i2c_ग_लिखोl(i2c, val, REG_CON);

			i2c->state = STATE_IDLE;

			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		अगर (i2c->error) अणु
			ret = i2c->error;
			अवरोध;
		पूर्ण
	पूर्ण

	clk_disable(i2c->pclk);
	clk_disable(i2c->clk);

	spin_unlock_irqrestore(&i2c->lock, flags);

	वापस ret < 0 ? ret : num;
पूर्ण

अटल पूर्णांक rk3x_i2c_xfer(काष्ठा i2c_adapter *adap,
			 काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस rk3x_i2c_xfer_common(adap, msgs, num, false);
पूर्ण

अटल पूर्णांक rk3x_i2c_xfer_polling(काष्ठा i2c_adapter *adap,
				 काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस rk3x_i2c_xfer_common(adap, msgs, num, true);
पूर्ण

अटल __maybe_unused पूर्णांक rk3x_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा rk3x_i2c *i2c = dev_get_drvdata(dev);

	rk3x_i2c_adapt_भाग(i2c, clk_get_rate(i2c->clk));

	वापस 0;
पूर्ण

अटल u32 rk3x_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm rk3x_i2c_algorithm = अणु
	.master_xfer		= rk3x_i2c_xfer,
	.master_xfer_atomic	= rk3x_i2c_xfer_polling,
	.functionality		= rk3x_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rv1108_soc_data = अणु
	.grf_offset = -1,
	.calc_timings = rk3x_i2c_v1_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rk3066_soc_data = अणु
	.grf_offset = 0x154,
	.calc_timings = rk3x_i2c_v0_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rk3188_soc_data = अणु
	.grf_offset = 0x0a4,
	.calc_timings = rk3x_i2c_v0_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rk3228_soc_data = अणु
	.grf_offset = -1,
	.calc_timings = rk3x_i2c_v0_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rk3288_soc_data = अणु
	.grf_offset = -1,
	.calc_timings = rk3x_i2c_v0_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा rk3x_i2c_soc_data rk3399_soc_data = अणु
	.grf_offset = -1,
	.calc_timings = rk3x_i2c_v1_calc_timings,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rk3x_i2c_match[] = अणु
	अणु
		.compatible = "rockchip,rv1108-i2c",
		.data = &rv1108_soc_data
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3066-i2c",
		.data = &rk3066_soc_data
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3188-i2c",
		.data = &rk3188_soc_data
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3228-i2c",
		.data = &rk3228_soc_data
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3288-i2c",
		.data = &rk3288_soc_data
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-i2c",
		.data = &rk3399_soc_data
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk3x_i2c_match);

अटल पूर्णांक rk3x_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा rk3x_i2c *i2c;
	पूर्णांक ret = 0;
	पूर्णांक bus_nr;
	u32 value;
	पूर्णांक irq;
	अचिन्हित दीर्घ clk_rate;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा rk3x_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	match = of_match_node(rk3x_i2c_match, np);
	i2c->soc_data = match->data;

	/* use common पूर्णांकerface to get I2C timing properties */
	i2c_parse_fw_timings(&pdev->dev, &i2c->t, true);

	strlcpy(i2c->adap.name, "rk3x-i2c", माप(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &rk3x_i2c_algorithm;
	i2c->adap.retries = 3;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	i2c->dev = &pdev->dev;

	spin_lock_init(&i2c->lock);
	init_रुकोqueue_head(&i2c->रुको);

	i2c->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->regs))
		वापस PTR_ERR(i2c->regs);

	/* Try to set the I2C adapter number from dt */
	bus_nr = of_alias_get_id(np, "i2c");

	/*
	 * Switch to new पूर्णांकerface अगर the SoC also offers the old one.
	 * The control bit is located in the GRF रेजिस्टर space.
	 */
	अगर (i2c->soc_data->grf_offset >= 0) अणु
		काष्ठा regmap *grf;

		grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
		अगर (IS_ERR(grf)) अणु
			dev_err(&pdev->dev,
				"rk3x-i2c needs 'rockchip,grf' property\n");
			वापस PTR_ERR(grf);
		पूर्ण

		अगर (bus_nr < 0) अणु
			dev_err(&pdev->dev, "rk3x-i2c needs i2cX alias");
			वापस -EINVAL;
		पूर्ण

		/* 27+i: ग_लिखो mask, 11+i: value */
		value = BIT(27 + bus_nr) | BIT(11 + bus_nr);

		ret = regmap_ग_लिखो(grf, i2c->soc_data->grf_offset, value);
		अगर (ret != 0) अणु
			dev_err(i2c->dev, "Could not write to GRF: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* IRQ setup */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, rk3x_i2c_irq,
			       0, dev_name(&pdev->dev), i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot request IRQ\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, i2c);

	अगर (i2c->soc_data->calc_timings == rk3x_i2c_v0_calc_timings) अणु
		/* Only one घड़ी to use क्रम bus घड़ी and peripheral घड़ी */
		i2c->clk = devm_clk_get(&pdev->dev, शून्य);
		i2c->pclk = i2c->clk;
	पूर्ण अन्यथा अणु
		i2c->clk = devm_clk_get(&pdev->dev, "i2c");
		i2c->pclk = devm_clk_get(&pdev->dev, "pclk");
	पूर्ण

	अगर (IS_ERR(i2c->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(i2c->clk),
				     "Can't get bus clk\n");

	अगर (IS_ERR(i2c->pclk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(i2c->pclk),
				     "Can't get periph clk\n");

	ret = clk_prepare(i2c->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Can't prepare bus clk: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare(i2c->pclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Can't prepare periph clock: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	i2c->clk_rate_nb.notअगरier_call = rk3x_i2c_clk_notअगरier_cb;
	ret = clk_notअगरier_रेजिस्टर(i2c->clk, &i2c->clk_rate_nb);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Unable to register clock notifier\n");
		जाओ err_pclk;
	पूर्ण

	clk_rate = clk_get_rate(i2c->clk);
	rk3x_i2c_adapt_भाग(i2c, clk_rate);

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ err_clk_notअगरier;

	वापस 0;

err_clk_notअगरier:
	clk_notअगरier_unरेजिस्टर(i2c->clk, &i2c->clk_rate_nb);
err_pclk:
	clk_unprepare(i2c->pclk);
err_clk:
	clk_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक rk3x_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk3x_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);

	clk_notअगरier_unरेजिस्टर(i2c->clk, &i2c->clk_rate_nb);
	clk_unprepare(i2c->pclk);
	clk_unprepare(i2c->clk);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rk3x_i2c_pm_ops, शून्य, rk3x_i2c_resume);

अटल काष्ठा platक्रमm_driver rk3x_i2c_driver = अणु
	.probe   = rk3x_i2c_probe,
	.हटाओ  = rk3x_i2c_हटाओ,
	.driver  = अणु
		.name  = "rk3x-i2c",
		.of_match_table = rk3x_i2c_match,
		.pm = &rk3x_i2c_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rk3x_i2c_driver);

MODULE_DESCRIPTION("Rockchip RK3xxx I2C Bus driver");
MODULE_AUTHOR("Max Schwarz <max.schwarz@online.de>");
MODULE_LICENSE("GPL v2");
