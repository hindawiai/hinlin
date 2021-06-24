<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C bus driver क्रम Amlogic Meson SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

/* Meson I2C रेजिस्टर map */
#घोषणा REG_CTRL		0x00
#घोषणा REG_SLAVE_ADDR		0x04
#घोषणा REG_TOK_LIST0		0x08
#घोषणा REG_TOK_LIST1		0x0c
#घोषणा REG_TOK_WDATA0		0x10
#घोषणा REG_TOK_WDATA1		0x14
#घोषणा REG_TOK_RDATA0		0x18
#घोषणा REG_TOK_RDATA1		0x1c

/* Control रेजिस्टर fields */
#घोषणा REG_CTRL_START		BIT(0)
#घोषणा REG_CTRL_ACK_IGNORE	BIT(1)
#घोषणा REG_CTRL_STATUS		BIT(2)
#घोषणा REG_CTRL_ERROR		BIT(3)
#घोषणा REG_CTRL_CLKDIV		GENMASK(21, 12)
#घोषणा REG_CTRL_CLKDIVEXT	GENMASK(29, 28)

#घोषणा REG_SLV_ADDR		GENMASK(7, 0)
#घोषणा REG_SLV_SDA_FILTER	GENMASK(10, 8)
#घोषणा REG_SLV_SCL_FILTER	GENMASK(13, 11)
#घोषणा REG_SLV_SCL_LOW		GENMASK(27, 16)
#घोषणा REG_SLV_SCL_LOW_EN	BIT(28)

#घोषणा I2C_TIMEOUT_MS		500
#घोषणा FILTER_DELAY		15

क्रमागत अणु
	TOKEN_END = 0,
	TOKEN_START,
	TOKEN_SLAVE_ADDR_WRITE,
	TOKEN_SLAVE_ADDR_READ,
	TOKEN_DATA,
	TOKEN_DATA_LAST,
	TOKEN_STOP,
पूर्ण;

क्रमागत अणु
	STATE_IDLE,
	STATE_READ,
	STATE_WRITE,
पूर्ण;

काष्ठा meson_i2c_data अणु
	अचिन्हित अक्षर भाग_factor;
पूर्ण;

/**
 * काष्ठा meson_i2c - Meson I2C device निजी data
 *
 * @adap:	I2C adapter instance
 * @dev:	Poपूर्णांकer to device काष्ठाure
 * @regs:	Base address of the device memory mapped रेजिस्टरs
 * @clk:	Poपूर्णांकer to घड़ी काष्ठाure
 * @msg:	Poपूर्णांकer to the current I2C message
 * @state:	Current state in the driver state machine
 * @last:	Flag set क्रम the last message in the transfer
 * @count:	Number of bytes to be sent/received in current transfer
 * @pos:	Current position in the send/receive buffer
 * @error:	Flag set when an error is received
 * @lock:	To aव्योम race conditions between irq handler and xfer code
 * @करोne:	Completion used to रुको क्रम transfer termination
 * @tokens:	Sequence of tokens to be written to the device
 * @num_tokens:	Number of tokens
 * @data:	Poपूर्णांकer to the controlller's platक्रमm data
 */
काष्ठा meson_i2c अणु
	काष्ठा i2c_adapter	adap;
	काष्ठा device		*dev;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;

	काष्ठा i2c_msg		*msg;
	पूर्णांक			state;
	bool			last;
	पूर्णांक			count;
	पूर्णांक			pos;
	पूर्णांक			error;

	spinlock_t		lock;
	काष्ठा completion	करोne;
	u32			tokens[2];
	पूर्णांक			num_tokens;

	स्थिर काष्ठा meson_i2c_data *data;
पूर्ण;

अटल व्योम meson_i2c_set_mask(काष्ठा meson_i2c *i2c, पूर्णांक reg, u32 mask,
			       u32 val)
अणु
	u32 data;

	data = पढ़ोl(i2c->regs + reg);
	data &= ~mask;
	data |= val & mask;
	ग_लिखोl(data, i2c->regs + reg);
पूर्ण

अटल व्योम meson_i2c_reset_tokens(काष्ठा meson_i2c *i2c)
अणु
	i2c->tokens[0] = 0;
	i2c->tokens[1] = 0;
	i2c->num_tokens = 0;
पूर्ण

अटल व्योम meson_i2c_add_token(काष्ठा meson_i2c *i2c, पूर्णांक token)
अणु
	अगर (i2c->num_tokens < 8)
		i2c->tokens[0] |= (token & 0xf) << (i2c->num_tokens * 4);
	अन्यथा
		i2c->tokens[1] |= (token & 0xf) << ((i2c->num_tokens % 8) * 4);

	i2c->num_tokens++;
पूर्ण

अटल व्योम meson_i2c_set_clk_भाग(काष्ठा meson_i2c *i2c, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित दीर्घ clk_rate = clk_get_rate(i2c->clk);
	अचिन्हित पूर्णांक भाग;

	भाग = DIV_ROUND_UP(clk_rate, freq);
	भाग -= FILTER_DELAY;
	भाग = DIV_ROUND_UP(भाग, i2c->data->भाग_factor);

	/* घड़ी भागider has 12 bits */
	अगर (भाग > GENMASK(11, 0)) अणु
		dev_err(i2c->dev, "requested bus frequency too low\n");
		भाग = GENMASK(11, 0);
	पूर्ण

	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_CLKDIV,
			   FIELD_PREP(REG_CTRL_CLKDIV, भाग & GENMASK(9, 0)));

	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_CLKDIVEXT,
			   FIELD_PREP(REG_CTRL_CLKDIVEXT, भाग >> 10));

	/* Disable HIGH/LOW mode */
	meson_i2c_set_mask(i2c, REG_SLAVE_ADDR, REG_SLV_SCL_LOW_EN, 0);

	dev_dbg(i2c->dev, "%s: clk %lu, freq %u, div %u\n", __func__,
		clk_rate, freq, भाग);
पूर्ण

अटल व्योम meson_i2c_get_data(काष्ठा meson_i2c *i2c, अक्षर *buf, पूर्णांक len)
अणु
	u32 rdata0, rdata1;
	पूर्णांक i;

	rdata0 = पढ़ोl(i2c->regs + REG_TOK_RDATA0);
	rdata1 = पढ़ोl(i2c->regs + REG_TOK_RDATA1);

	dev_dbg(i2c->dev, "%s: data %08x %08x len %d\n", __func__,
		rdata0, rdata1, len);

	क्रम (i = 0; i < min(4, len); i++)
		*buf++ = (rdata0 >> i * 8) & 0xff;

	क्रम (i = 4; i < min(8, len); i++)
		*buf++ = (rdata1 >> (i - 4) * 8) & 0xff;
पूर्ण

अटल व्योम meson_i2c_put_data(काष्ठा meson_i2c *i2c, अक्षर *buf, पूर्णांक len)
अणु
	u32 wdata0 = 0, wdata1 = 0;
	पूर्णांक i;

	क्रम (i = 0; i < min(4, len); i++)
		wdata0 |= *buf++ << (i * 8);

	क्रम (i = 4; i < min(8, len); i++)
		wdata1 |= *buf++ << ((i - 4) * 8);

	ग_लिखोl(wdata0, i2c->regs + REG_TOK_WDATA0);
	ग_लिखोl(wdata1, i2c->regs + REG_TOK_WDATA1);

	dev_dbg(i2c->dev, "%s: data %08x %08x len %d\n", __func__,
		wdata0, wdata1, len);
पूर्ण

अटल व्योम meson_i2c_prepare_xfer(काष्ठा meson_i2c *i2c)
अणु
	bool ग_लिखो = !(i2c->msg->flags & I2C_M_RD);
	पूर्णांक i;

	i2c->count = min(i2c->msg->len - i2c->pos, 8);

	क्रम (i = 0; i < i2c->count - 1; i++)
		meson_i2c_add_token(i2c, TOKEN_DATA);

	अगर (i2c->count) अणु
		अगर (ग_लिखो || i2c->pos + i2c->count < i2c->msg->len)
			meson_i2c_add_token(i2c, TOKEN_DATA);
		अन्यथा
			meson_i2c_add_token(i2c, TOKEN_DATA_LAST);
	पूर्ण

	अगर (ग_लिखो)
		meson_i2c_put_data(i2c, i2c->msg->buf + i2c->pos, i2c->count);

	अगर (i2c->last && i2c->pos + i2c->count >= i2c->msg->len)
		meson_i2c_add_token(i2c, TOKEN_STOP);

	ग_लिखोl(i2c->tokens[0], i2c->regs + REG_TOK_LIST0);
	ग_लिखोl(i2c->tokens[1], i2c->regs + REG_TOK_LIST1);
पूर्ण

अटल व्योम meson_i2c_transfer_complete(काष्ठा meson_i2c *i2c, u32 ctrl)
अणु
	अगर (ctrl & REG_CTRL_ERROR) अणु
		/*
		 * The bit is set when the IGNORE_NAK bit is cleared
		 * and the device didn't respond. In this हाल, the
		 * I2C controller स्वतःmatically generates a STOP
		 * condition.
		 */
		dev_dbg(i2c->dev, "error bit set\n");
		i2c->error = -ENXIO;
		i2c->state = STATE_IDLE;
	पूर्ण अन्यथा अणु
		अगर (i2c->state == STATE_READ && i2c->count)
			meson_i2c_get_data(i2c, i2c->msg->buf + i2c->pos,
					   i2c->count);

		i2c->pos += i2c->count;

		अगर (i2c->pos >= i2c->msg->len)
			i2c->state = STATE_IDLE;
	पूर्ण
पूर्ण

अटल irqवापस_t meson_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा meson_i2c *i2c = dev_id;
	अचिन्हित पूर्णांक ctrl;

	spin_lock(&i2c->lock);

	meson_i2c_reset_tokens(i2c);
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, 0);
	ctrl = पढ़ोl(i2c->regs + REG_CTRL);

	dev_dbg(i2c->dev, "irq: state %d, pos %d, count %d, ctrl %08x\n",
		i2c->state, i2c->pos, i2c->count, ctrl);

	अगर (i2c->state == STATE_IDLE) अणु
		spin_unlock(&i2c->lock);
		वापस IRQ_NONE;
	पूर्ण

	meson_i2c_transfer_complete(i2c, ctrl);

	अगर (i2c->state == STATE_IDLE) अणु
		complete(&i2c->करोne);
		जाओ out;
	पूर्ण

	/* Restart the processing */
	meson_i2c_prepare_xfer(i2c);
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, REG_CTRL_START);
out:
	spin_unlock(&i2c->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम meson_i2c_करो_start(काष्ठा meson_i2c *i2c, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक token;

	token = (msg->flags & I2C_M_RD) ? TOKEN_SLAVE_ADDR_READ :
		TOKEN_SLAVE_ADDR_WRITE;


	meson_i2c_set_mask(i2c, REG_SLAVE_ADDR, REG_SLV_ADDR,
			   FIELD_PREP(REG_SLV_ADDR, msg->addr << 1));

	meson_i2c_add_token(i2c, TOKEN_START);
	meson_i2c_add_token(i2c, token);
पूर्ण

अटल पूर्णांक meson_i2c_xfer_msg(काष्ठा meson_i2c *i2c, काष्ठा i2c_msg *msg,
			      पूर्णांक last, bool atomic)
अणु
	अचिन्हित दीर्घ समय_left, flags;
	पूर्णांक ret = 0;
	u32 ctrl;

	i2c->msg = msg;
	i2c->last = last;
	i2c->pos = 0;
	i2c->count = 0;
	i2c->error = 0;

	meson_i2c_reset_tokens(i2c);

	flags = (msg->flags & I2C_M_IGNORE_NAK) ? REG_CTRL_ACK_IGNORE : 0;
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_ACK_IGNORE, flags);

	अगर (!(msg->flags & I2C_M_NOSTART))
		meson_i2c_करो_start(i2c, msg);

	i2c->state = (msg->flags & I2C_M_RD) ? STATE_READ : STATE_WRITE;
	meson_i2c_prepare_xfer(i2c);

	अगर (!atomic)
		reinit_completion(&i2c->करोne);

	/* Start the transfer */
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, REG_CTRL_START);

	अगर (atomic) अणु
		ret = पढ़ोl_poll_समयout_atomic(i2c->regs + REG_CTRL, ctrl,
						!(ctrl & REG_CTRL_STATUS),
						10, I2C_TIMEOUT_MS * 1000);
	पूर्ण अन्यथा अणु
		समय_left = msecs_to_jअगरfies(I2C_TIMEOUT_MS);
		समय_left = रुको_क्रम_completion_समयout(&i2c->करोne, समय_left);

		अगर (!समय_left)
			ret = -ETIMEDOUT;
	पूर्ण

	/*
	 * Protect access to i2c काष्ठा and रेजिस्टरs from पूर्णांकerrupt
	 * handlers triggered by a transfer terminated after the
	 * समयout period
	 */
	spin_lock_irqsave(&i2c->lock, flags);

	अगर (atomic && !ret)
		meson_i2c_transfer_complete(i2c, ctrl);

	/* Abort any active operation */
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, 0);

	अगर (ret)
		i2c->state = STATE_IDLE;

	अगर (i2c->error)
		ret = i2c->error;

	spin_unlock_irqrestore(&i2c->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_i2c_xfer_messages(काष्ठा i2c_adapter *adap,
				   काष्ठा i2c_msg *msgs, पूर्णांक num, bool atomic)
अणु
	काष्ठा meson_i2c *i2c = adap->algo_data;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < num; i++) अणु
		ret = meson_i2c_xfer_msg(i2c, msgs + i, i == num - 1, atomic);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret ?: i;
पूर्ण

अटल पूर्णांक meson_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			  पूर्णांक num)
अणु
	वापस meson_i2c_xfer_messages(adap, msgs, num, false);
पूर्ण

अटल पूर्णांक meson_i2c_xfer_atomic(काष्ठा i2c_adapter *adap,
				 काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	वापस meson_i2c_xfer_messages(adap, msgs, num, true);
पूर्ण

अटल u32 meson_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm meson_i2c_algorithm = अणु
	.master_xfer = meson_i2c_xfer,
	.master_xfer_atomic = meson_i2c_xfer_atomic,
	.functionality = meson_i2c_func,
पूर्ण;

अटल पूर्णांक meson_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा meson_i2c *i2c;
	काष्ठा i2c_timings timings;
	पूर्णांक irq, ret = 0;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा meson_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c_parse_fw_timings(&pdev->dev, &timings, true);

	i2c->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->करोne);

	i2c->data = (स्थिर काष्ठा meson_i2c_data *)
		of_device_get_match_data(&pdev->dev);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk)) अणु
		dev_err(&pdev->dev, "can't get device clock\n");
		वापस PTR_ERR(i2c->clk);
	पूर्ण

	i2c->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->regs))
		वापस PTR_ERR(i2c->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, meson_i2c_irq, 0, शून्य, i2c);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can't request IRQ\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "can't prepare clock\n");
		वापस ret;
	पूर्ण

	strlcpy(i2c->adap.name, "Meson I2C adapter",
		माप(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &meson_i2c_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;

	/*
	 * A transfer is triggered when START bit changes from 0 to 1.
	 * Ensure that the bit is set to 0 after probe
	 */
	meson_i2c_set_mask(i2c, REG_CTRL, REG_CTRL_START, 0);

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0) अणु
		clk_disable_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	/* Disable filtering */
	meson_i2c_set_mask(i2c, REG_SLAVE_ADDR,
			   REG_SLV_SDA_FILTER | REG_SLV_SCL_FILTER, 0);

	meson_i2c_set_clk_भाग(i2c, timings.bus_freq_hz);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);
	clk_disable_unprepare(i2c->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा meson_i2c_data i2c_meson6_data = अणु
	.भाग_factor = 4,
पूर्ण;

अटल स्थिर काष्ठा meson_i2c_data i2c_gxbb_data = अणु
	.भाग_factor = 4,
पूर्ण;

अटल स्थिर काष्ठा meson_i2c_data i2c_axg_data = अणु
	.भाग_factor = 3,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_i2c_match[] = अणु
	अणु .compatible = "amlogic,meson6-i2c", .data = &i2c_meson6_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-i2c", .data = &i2c_gxbb_data पूर्ण,
	अणु .compatible = "amlogic,meson-axg-i2c", .data = &i2c_axg_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, meson_i2c_match);

अटल काष्ठा platक्रमm_driver meson_i2c_driver = अणु
	.probe   = meson_i2c_probe,
	.हटाओ  = meson_i2c_हटाओ,
	.driver  = अणु
		.name  = "meson-i2c",
		.of_match_table = meson_i2c_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_i2c_driver);

MODULE_DESCRIPTION("Amlogic Meson I2C Bus driver");
MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_LICENSE("GPL v2");
