<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Wondermedia I2C Master Mode Driver
 *
 *  Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 *
 *  Derived from GPLv2+ licensed source:
 *  - Copyright (C) 2008 WonderMedia Technologies, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा REG_CR		0x00
#घोषणा REG_TCR		0x02
#घोषणा REG_CSR		0x04
#घोषणा REG_ISR		0x06
#घोषणा REG_IMR		0x08
#घोषणा REG_CDR		0x0A
#घोषणा REG_TR		0x0C
#घोषणा REG_MCR		0x0E
#घोषणा REG_SLAVE_CR	0x10
#घोषणा REG_SLAVE_SR	0x12
#घोषणा REG_SLAVE_ISR	0x14
#घोषणा REG_SLAVE_IMR	0x16
#घोषणा REG_SLAVE_DR	0x18
#घोषणा REG_SLAVE_TR	0x1A

/* REG_CR Bit fields */
#घोषणा CR_TX_NEXT_ACK		0x0000
#घोषणा CR_ENABLE		0x0001
#घोषणा CR_TX_NEXT_NO_ACK	0x0002
#घोषणा CR_TX_END		0x0004
#घोषणा CR_CPU_RDY		0x0008
#घोषणा SLAV_MODE_SEL		0x8000

/* REG_TCR Bit fields */
#घोषणा TCR_STANDARD_MODE	0x0000
#घोषणा TCR_MASTER_WRITE	0x0000
#घोषणा TCR_HS_MODE		0x2000
#घोषणा TCR_MASTER_READ		0x4000
#घोषणा TCR_FAST_MODE		0x8000
#घोषणा TCR_SLAVE_ADDR_MASK	0x007F

/* REG_ISR Bit fields */
#घोषणा ISR_NACK_ADDR		0x0001
#घोषणा ISR_BYTE_END		0x0002
#घोषणा ISR_SCL_TIMEOUT		0x0004
#घोषणा ISR_WRITE_ALL		0x0007

/* REG_IMR Bit fields */
#घोषणा IMR_ENABLE_ALL		0x0007

/* REG_CSR Bit fields */
#घोषणा CSR_RCV_NOT_ACK		0x0001
#घोषणा CSR_RCV_ACK_MASK	0x0001
#घोषणा CSR_READY_MASK		0x0002

/* REG_TR */
#घोषणा SCL_TIMEOUT(x)		(((x) & 0xFF) << 8)
#घोषणा TR_STD			0x0064
#घोषणा TR_HS			0x0019

/* REG_MCR */
#घोषणा MCR_APB_96M		7
#घोषणा MCR_APB_166M		12

#घोषणा I2C_MODE_STANDARD	0
#घोषणा I2C_MODE_FAST		1

#घोषणा WMT_I2C_TIMEOUT		(msecs_to_jअगरfies(1000))

काष्ठा wmt_i2c_dev अणु
	काष्ठा i2c_adapter	adapter;
	काष्ठा completion	complete;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	पूर्णांक			mode;
	पूर्णांक			irq;
	u16			cmd_status;
पूर्ण;

अटल पूर्णांक wmt_i2c_रुको_bus_not_busy(काष्ठा wmt_i2c_dev *i2c_dev)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + WMT_I2C_TIMEOUT;
	जबतक (!(पढ़ोw(i2c_dev->base + REG_CSR) & CSR_READY_MASK)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(i2c_dev->dev, "timeout waiting for bus ready\n");
			वापस -EBUSY;
		पूर्ण
		msleep(20);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_check_status(काष्ठा wmt_i2c_dev *i2c_dev)
अणु
	पूर्णांक ret = 0;

	अगर (i2c_dev->cmd_status & ISR_NACK_ADDR)
		ret = -EIO;

	अगर (i2c_dev->cmd_status & ISR_SCL_TIMEOUT)
		ret = -ETIMEDOUT;

	वापस ret;
पूर्ण

अटल पूर्णांक wmt_i2c_ग_लिखो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *pmsg,
			 पूर्णांक last)
अणु
	काष्ठा wmt_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u16 val, tcr_val;
	पूर्णांक ret;
	अचिन्हित दीर्घ रुको_result;
	पूर्णांक xfer_len = 0;

	अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
		ret = wmt_i2c_रुको_bus_not_busy(i2c_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (pmsg->len == 0) अणु
		/*
		 * We still need to run through the जबतक (..) once, so
		 * start at -1 and अवरोध out early from the loop
		 */
		xfer_len = -1;
		ग_लिखोw(0, i2c_dev->base + REG_CDR);
	पूर्ण अन्यथा अणु
		ग_लिखोw(pmsg->buf[0] & 0xFF, i2c_dev->base + REG_CDR);
	पूर्ण

	अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
		val = पढ़ोw(i2c_dev->base + REG_CR);
		val &= ~CR_TX_END;
		ग_लिखोw(val, i2c_dev->base + REG_CR);

		val = पढ़ोw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		ग_लिखोw(val, i2c_dev->base + REG_CR);
	पूर्ण

	reinit_completion(&i2c_dev->complete);

	अगर (i2c_dev->mode == I2C_MODE_STANDARD)
		tcr_val = TCR_STANDARD_MODE;
	अन्यथा
		tcr_val = TCR_FAST_MODE;

	tcr_val |= (TCR_MASTER_WRITE | (pmsg->addr & TCR_SLAVE_ADDR_MASK));

	ग_लिखोw(tcr_val, i2c_dev->base + REG_TCR);

	अगर (pmsg->flags & I2C_M_NOSTART) अणु
		val = पढ़ोw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		ग_लिखोw(val, i2c_dev->base + REG_CR);
	पूर्ण

	जबतक (xfer_len < pmsg->len) अणु
		रुको_result = रुको_क्रम_completion_समयout(&i2c_dev->complete,
							msecs_to_jअगरfies(500));

		अगर (रुको_result == 0)
			वापस -ETIMEDOUT;

		ret = wmt_check_status(i2c_dev);
		अगर (ret)
			वापस ret;

		xfer_len++;

		val = पढ़ोw(i2c_dev->base + REG_CSR);
		अगर ((val & CSR_RCV_ACK_MASK) == CSR_RCV_NOT_ACK) अणु
			dev_dbg(i2c_dev->dev, "write RCV NACK error\n");
			वापस -EIO;
		पूर्ण

		अगर (pmsg->len == 0) अणु
			val = CR_TX_END | CR_CPU_RDY | CR_ENABLE;
			ग_लिखोw(val, i2c_dev->base + REG_CR);
			अवरोध;
		पूर्ण

		अगर (xfer_len == pmsg->len) अणु
			अगर (last != 1)
				ग_लिखोw(CR_ENABLE, i2c_dev->base + REG_CR);
		पूर्ण अन्यथा अणु
			ग_लिखोw(pmsg->buf[xfer_len] & 0xFF, i2c_dev->base +
								REG_CDR);
			ग_लिखोw(CR_CPU_RDY | CR_ENABLE, i2c_dev->base + REG_CR);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_i2c_पढ़ो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *pmsg,
			पूर्णांक last)
अणु
	काष्ठा wmt_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	u16 val, tcr_val;
	पूर्णांक ret;
	अचिन्हित दीर्घ रुको_result;
	u32 xfer_len = 0;

	अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
		ret = wmt_i2c_रुको_bus_not_busy(i2c_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = पढ़ोw(i2c_dev->base + REG_CR);
	val &= ~CR_TX_END;
	ग_लिखोw(val, i2c_dev->base + REG_CR);

	val = पढ़ोw(i2c_dev->base + REG_CR);
	val &= ~CR_TX_NEXT_NO_ACK;
	ग_लिखोw(val, i2c_dev->base + REG_CR);

	अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
		val = पढ़ोw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		ग_लिखोw(val, i2c_dev->base + REG_CR);
	पूर्ण

	अगर (pmsg->len == 1) अणु
		val = पढ़ोw(i2c_dev->base + REG_CR);
		val |= CR_TX_NEXT_NO_ACK;
		ग_लिखोw(val, i2c_dev->base + REG_CR);
	पूर्ण

	reinit_completion(&i2c_dev->complete);

	अगर (i2c_dev->mode == I2C_MODE_STANDARD)
		tcr_val = TCR_STANDARD_MODE;
	अन्यथा
		tcr_val = TCR_FAST_MODE;

	tcr_val |= TCR_MASTER_READ | (pmsg->addr & TCR_SLAVE_ADDR_MASK);

	ग_लिखोw(tcr_val, i2c_dev->base + REG_TCR);

	अगर (pmsg->flags & I2C_M_NOSTART) अणु
		val = पढ़ोw(i2c_dev->base + REG_CR);
		val |= CR_CPU_RDY;
		ग_लिखोw(val, i2c_dev->base + REG_CR);
	पूर्ण

	जबतक (xfer_len < pmsg->len) अणु
		रुको_result = रुको_क्रम_completion_समयout(&i2c_dev->complete,
							msecs_to_jअगरfies(500));

		अगर (!रुको_result)
			वापस -ETIMEDOUT;

		ret = wmt_check_status(i2c_dev);
		अगर (ret)
			वापस ret;

		pmsg->buf[xfer_len] = पढ़ोw(i2c_dev->base + REG_CDR) >> 8;
		xfer_len++;

		अगर (xfer_len == pmsg->len - 1) अणु
			val = पढ़ोw(i2c_dev->base + REG_CR);
			val |= (CR_TX_NEXT_NO_ACK | CR_CPU_RDY);
			ग_लिखोw(val, i2c_dev->base + REG_CR);
		पूर्ण अन्यथा अणु
			val = पढ़ोw(i2c_dev->base + REG_CR);
			val |= CR_CPU_RDY;
			ग_लिखोw(val, i2c_dev->base + REG_CR);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_i2c_xfer(काष्ठा i2c_adapter *adap,
			काष्ठा i2c_msg msgs[],
			पूर्णांक num)
अणु
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i, is_last;
	पूर्णांक ret = 0;

	क्रम (i = 0; ret >= 0 && i < num; i++) अणु
		is_last = ((i + 1) == num);

		pmsg = &msgs[i];
		अगर (pmsg->flags & I2C_M_RD)
			ret = wmt_i2c_पढ़ो(adap, pmsg, is_last);
		अन्यथा
			ret = wmt_i2c_ग_लिखो(adap, pmsg, is_last);
	पूर्ण

	वापस (ret < 0) ? ret : i;
पूर्ण

अटल u32 wmt_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_NOSTART;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm wmt_i2c_algo = अणु
	.master_xfer	= wmt_i2c_xfer,
	.functionality	= wmt_i2c_func,
पूर्ण;

अटल irqवापस_t wmt_i2c_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wmt_i2c_dev *i2c_dev = data;

	/* save the status and ग_लिखो-clear it */
	i2c_dev->cmd_status = पढ़ोw(i2c_dev->base + REG_ISR);
	ग_लिखोw(i2c_dev->cmd_status, i2c_dev->base + REG_ISR);

	complete(&i2c_dev->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wmt_i2c_reset_hardware(काष्ठा wmt_i2c_dev *i2c_dev)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(i2c_dev->clk);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to enable clock\n");
		वापस err;
	पूर्ण

	err = clk_set_rate(i2c_dev->clk, 20000000);
	अगर (err) अणु
		dev_err(i2c_dev->dev, "failed to set clock = 20Mhz\n");
		clk_disable_unprepare(i2c_dev->clk);
		वापस err;
	पूर्ण

	ग_लिखोw(0, i2c_dev->base + REG_CR);
	ग_लिखोw(MCR_APB_166M, i2c_dev->base + REG_MCR);
	ग_लिखोw(ISR_WRITE_ALL, i2c_dev->base + REG_ISR);
	ग_लिखोw(IMR_ENABLE_ALL, i2c_dev->base + REG_IMR);
	ग_लिखोw(CR_ENABLE, i2c_dev->base + REG_CR);
	पढ़ोw(i2c_dev->base + REG_CSR);		/* पढ़ो clear */
	ग_लिखोw(ISR_WRITE_ALL, i2c_dev->base + REG_ISR);

	अगर (i2c_dev->mode == I2C_MODE_STANDARD)
		ग_लिखोw(SCL_TIMEOUT(128) | TR_STD, i2c_dev->base + REG_TR);
	अन्यथा
		ग_लिखोw(SCL_TIMEOUT(128) | TR_HS, i2c_dev->base + REG_TR);

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा wmt_i2c_dev *i2c_dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *res;
	पूर्णांक err;
	u32 clk_rate;

	i2c_dev = devm_kzalloc(&pdev->dev, माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(i2c_dev->base))
		वापस PTR_ERR(i2c_dev->base);

	i2c_dev->irq = irq_of_parse_and_map(np, 0);
	अगर (!i2c_dev->irq) अणु
		dev_err(&pdev->dev, "irq missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	i2c_dev->clk = of_clk_get(np, 0);
	अगर (IS_ERR(i2c_dev->clk)) अणु
		dev_err(&pdev->dev, "unable to request clock\n");
		वापस PTR_ERR(i2c_dev->clk);
	पूर्ण

	i2c_dev->mode = I2C_MODE_STANDARD;
	err = of_property_पढ़ो_u32(np, "clock-frequency", &clk_rate);
	अगर (!err && (clk_rate == I2C_MAX_FAST_MODE_FREQ))
		i2c_dev->mode = I2C_MODE_FAST;

	i2c_dev->dev = &pdev->dev;

	err = devm_request_irq(&pdev->dev, i2c_dev->irq, wmt_i2c_isr, 0,
							"i2c", i2c_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request irq %i\n", i2c_dev->irq);
		वापस err;
	पूर्ण

	adap = &i2c_dev->adapter;
	i2c_set_adapdata(adap, i2c_dev);
	strlcpy(adap->name, "WMT I2C adapter", माप(adap->name));
	adap->owner = THIS_MODULE;
	adap->algo = &wmt_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_completion(&i2c_dev->complete);

	err = wmt_i2c_reset_hardware(i2c_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "error initializing hardware\n");
		वापस err;
	पूर्ण

	err = i2c_add_adapter(adap);
	अगर (err)
		वापस err;

	platक्रमm_set_drvdata(pdev, i2c_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wmt_i2c_dev *i2c_dev = platक्रमm_get_drvdata(pdev);

	/* Disable पूर्णांकerrupts, घड़ी and delete adapter */
	ग_लिखोw(0, i2c_dev->base + REG_IMR);
	clk_disable_unprepare(i2c_dev->clk);
	i2c_del_adapter(&i2c_dev->adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wmt_i2c_dt_ids[] = अणु
	अणु .compatible = "wm,wm8505-i2c" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver wmt_i2c_driver = अणु
	.probe		= wmt_i2c_probe,
	.हटाओ		= wmt_i2c_हटाओ,
	.driver		= अणु
		.name	= "wmt-i2c",
		.of_match_table = wmt_i2c_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wmt_i2c_driver);

MODULE_DESCRIPTION("Wondermedia I2C master-mode bus adapter");
MODULE_AUTHOR("Tony Prisk <linux@prisktech.co.nz>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, wmt_i2c_dt_ids);
