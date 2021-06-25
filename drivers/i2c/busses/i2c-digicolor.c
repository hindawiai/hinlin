<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C bus driver क्रम Conexant Digicolor SoCs
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2015 Paraकरोx Innovation Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TIMEOUT_MS		100

#घोषणा II_CONTROL		0x0
#घोषणा II_CONTROL_LOCAL_RESET	BIT(0)

#घोषणा II_CLOCKTIME		0x1

#घोषणा II_COMMAND		0x2
#घोषणा II_CMD_START		1
#घोषणा II_CMD_RESTART		2
#घोषणा II_CMD_SEND_ACK		3
#घोषणा II_CMD_GET_ACK		6
#घोषणा II_CMD_GET_NOACK	7
#घोषणा II_CMD_STOP		10
#घोषणा II_COMMAND_GO		BIT(7)
#घोषणा II_COMMAND_COMPLETION_STATUS(r)	(((r) >> 5) & 3)
#घोषणा II_CMD_STATUS_NORMAL	0
#घोषणा II_CMD_STATUS_ACK_GOOD	1
#घोषणा II_CMD_STATUS_ACK_BAD	2
#घोषणा II_CMD_STATUS_ABORT	3

#घोषणा II_DATA			0x3
#घोषणा II_INTFLAG_CLEAR	0x8
#घोषणा II_INTENABLE		0xa

काष्ठा dc_i2c अणु
	काष्ठा i2c_adapter	adap;
	काष्ठा device		*dev;
	व्योम __iomem		*regs;
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		frequency;

	काष्ठा i2c_msg		*msg;
	अचिन्हित पूर्णांक		msgbuf_ptr;
	पूर्णांक			last;
	spinlock_t		lock;
	काष्ठा completion	करोne;
	पूर्णांक			state;
	पूर्णांक			error;
पूर्ण;

क्रमागत अणु
	STATE_IDLE,
	STATE_START,
	STATE_ADDR,
	STATE_WRITE,
	STATE_READ,
	STATE_STOP,
पूर्ण;

अटल व्योम dc_i2c_cmd(काष्ठा dc_i2c *i2c, u8 cmd)
अणु
	ग_लिखोb_relaxed(cmd | II_COMMAND_GO, i2c->regs + II_COMMAND);
पूर्ण

अटल u8 dc_i2c_addr_cmd(काष्ठा i2c_msg *msg)
अणु
	u8 addr = (msg->addr & 0x7f) << 1;

	अगर (msg->flags & I2C_M_RD)
		addr |= 1;

	वापस addr;
पूर्ण

अटल व्योम dc_i2c_data(काष्ठा dc_i2c *i2c, u8 data)
अणु
	ग_लिखोb_relaxed(data, i2c->regs + II_DATA);
पूर्ण

अटल व्योम dc_i2c_ग_लिखो_byte(काष्ठा dc_i2c *i2c, u8 byte)
अणु
	dc_i2c_data(i2c, byte);
	dc_i2c_cmd(i2c, II_CMD_SEND_ACK);
पूर्ण

अटल व्योम dc_i2c_ग_लिखो_buf(काष्ठा dc_i2c *i2c)
अणु
	dc_i2c_ग_लिखो_byte(i2c, i2c->msg->buf[i2c->msgbuf_ptr++]);
पूर्ण

अटल व्योम dc_i2c_next_पढ़ो(काष्ठा dc_i2c *i2c)
अणु
	bool last = (i2c->msgbuf_ptr + 1 == i2c->msg->len);

	dc_i2c_cmd(i2c, last ? II_CMD_GET_NOACK : II_CMD_GET_ACK);
पूर्ण

अटल व्योम dc_i2c_stop(काष्ठा dc_i2c *i2c)
अणु
	i2c->state = STATE_STOP;
	अगर (i2c->last)
		dc_i2c_cmd(i2c, II_CMD_STOP);
	अन्यथा
		complete(&i2c->करोne);
पूर्ण

अटल u8 dc_i2c_पढ़ो_byte(काष्ठा dc_i2c *i2c)
अणु
	वापस पढ़ोb_relaxed(i2c->regs + II_DATA);
पूर्ण

अटल व्योम dc_i2c_पढ़ो_buf(काष्ठा dc_i2c *i2c)
अणु
	i2c->msg->buf[i2c->msgbuf_ptr++] = dc_i2c_पढ़ो_byte(i2c);
	dc_i2c_next_पढ़ो(i2c);
पूर्ण

अटल व्योम dc_i2c_set_irq(काष्ठा dc_i2c *i2c, पूर्णांक enable)
अणु
	अगर (enable)
		ग_लिखोb_relaxed(1, i2c->regs + II_INTFLAG_CLEAR);
	ग_लिखोb_relaxed(!!enable, i2c->regs + II_INTENABLE);
पूर्ण

अटल पूर्णांक dc_i2c_cmd_status(काष्ठा dc_i2c *i2c)
अणु
	u8 cmd = पढ़ोb_relaxed(i2c->regs + II_COMMAND);

	वापस II_COMMAND_COMPLETION_STATUS(cmd);
पूर्ण

अटल व्योम dc_i2c_start_msg(काष्ठा dc_i2c *i2c, पूर्णांक first)
अणु
	काष्ठा i2c_msg *msg = i2c->msg;

	अगर (!(msg->flags & I2C_M_NOSTART)) अणु
		i2c->state = STATE_START;
		dc_i2c_cmd(i2c, first ? II_CMD_START : II_CMD_RESTART);
	पूर्ण अन्यथा अगर (msg->flags & I2C_M_RD) अणु
		i2c->state = STATE_READ;
		dc_i2c_next_पढ़ो(i2c);
	पूर्ण अन्यथा अणु
		i2c->state = STATE_WRITE;
		dc_i2c_ग_लिखो_buf(i2c);
	पूर्ण
पूर्ण

अटल irqवापस_t dc_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dc_i2c *i2c = dev_id;
	पूर्णांक cmd_status = dc_i2c_cmd_status(i2c);
	u8 addr_cmd;

	ग_लिखोb_relaxed(1, i2c->regs + II_INTFLAG_CLEAR);

	spin_lock(&i2c->lock);

	अगर (cmd_status == II_CMD_STATUS_ACK_BAD
	    || cmd_status == II_CMD_STATUS_ABORT) अणु
		i2c->error = -EIO;
		complete(&i2c->करोne);
		जाओ out;
	पूर्ण

	चयन (i2c->state) अणु
	हाल STATE_START:
		addr_cmd = dc_i2c_addr_cmd(i2c->msg);
		dc_i2c_ग_लिखो_byte(i2c, addr_cmd);
		i2c->state = STATE_ADDR;
		अवरोध;
	हाल STATE_ADDR:
		अगर (i2c->msg->flags & I2C_M_RD) अणु
			dc_i2c_next_पढ़ो(i2c);
			i2c->state = STATE_READ;
			अवरोध;
		पूर्ण
		i2c->state = STATE_WRITE;
		fallthrough;
	हाल STATE_WRITE:
		अगर (i2c->msgbuf_ptr < i2c->msg->len)
			dc_i2c_ग_लिखो_buf(i2c);
		अन्यथा
			dc_i2c_stop(i2c);
		अवरोध;
	हाल STATE_READ:
		अगर (i2c->msgbuf_ptr < i2c->msg->len)
			dc_i2c_पढ़ो_buf(i2c);
		अन्यथा
			dc_i2c_stop(i2c);
		अवरोध;
	हाल STATE_STOP:
		i2c->state = STATE_IDLE;
		complete(&i2c->करोne);
		अवरोध;
	पूर्ण

out:
	spin_unlock(&i2c->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dc_i2c_xfer_msg(काष्ठा dc_i2c *i2c, काष्ठा i2c_msg *msg, पूर्णांक first,
			   पूर्णांक last)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(TIMEOUT_MS);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2c->lock, flags);
	i2c->msg = msg;
	i2c->msgbuf_ptr = 0;
	i2c->last = last;
	i2c->error = 0;

	reinit_completion(&i2c->करोne);
	dc_i2c_set_irq(i2c, 1);
	dc_i2c_start_msg(i2c, first);
	spin_unlock_irqrestore(&i2c->lock, flags);

	समयout = रुको_क्रम_completion_समयout(&i2c->करोne, समयout);
	dc_i2c_set_irq(i2c, 0);
	अगर (समयout == 0) अणु
		i2c->state = STATE_IDLE;
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (i2c->error)
		वापस i2c->error;

	वापस 0;
पूर्ण

अटल पूर्णांक dc_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा dc_i2c *i2c = adap->algo_data;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++) अणु
		ret = dc_i2c_xfer_msg(i2c, &msgs[i], i == 0, i == num - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक dc_i2c_init_hw(काष्ठा dc_i2c *i2c)
अणु
	अचिन्हित दीर्घ clk_rate = clk_get_rate(i2c->clk);
	अचिन्हित पूर्णांक घड़ीसमय;

	ग_लिखोb_relaxed(II_CONTROL_LOCAL_RESET, i2c->regs + II_CONTROL);
	udelay(100);
	ग_लिखोb_relaxed(0, i2c->regs + II_CONTROL);
	udelay(100);

	घड़ीसमय = DIV_ROUND_UP(clk_rate, 64 * i2c->frequency);
	अगर (घड़ीसमय < 1 || घड़ीसमय > 0xff) अणु
		dev_err(i2c->dev, "can't set bus speed of %u Hz\n",
			i2c->frequency);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोb_relaxed(घड़ीसमय - 1, i2c->regs + II_CLOCKTIME);

	वापस 0;
पूर्ण

अटल u32 dc_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_NOSTART;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dc_i2c_algorithm = अणु
	.master_xfer	= dc_i2c_xfer,
	.functionality	= dc_i2c_func,
पूर्ण;

अटल पूर्णांक dc_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा dc_i2c *i2c;
	पूर्णांक ret = 0, irq;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा dc_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				 &i2c->frequency))
		i2c->frequency = I2C_MAX_STANDARD_MODE_FREQ;

	i2c->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, i2c);

	spin_lock_init(&i2c->lock);
	init_completion(&i2c->करोne);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk))
		वापस PTR_ERR(i2c->clk);

	i2c->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->regs))
		वापस PTR_ERR(i2c->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, dc_i2c_irq, 0,
			       dev_name(&pdev->dev), i2c);
	अगर (ret < 0)
		वापस ret;

	strlcpy(i2c->adap.name, "Conexant Digicolor I2C adapter",
		माप(i2c->adap.name));
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.algo = &dc_i2c_algorithm;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.algo_data = i2c;

	ret = dc_i2c_init_hw(i2c);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0) अणु
		clk_disable_unprepare(i2c->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dc_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dc_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);
	clk_disable_unprepare(i2c->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dc_i2c_match[] = अणु
	अणु .compatible = "cnxt,cx92755-i2c" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dc_i2c_match);

अटल काष्ठा platक्रमm_driver dc_i2c_driver = अणु
	.probe   = dc_i2c_probe,
	.हटाओ  = dc_i2c_हटाओ,
	.driver  = अणु
		.name  = "digicolor-i2c",
		.of_match_table = dc_i2c_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dc_i2c_driver);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Conexant Digicolor I2C master driver");
MODULE_LICENSE("GPL v2");
