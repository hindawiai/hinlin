<शैली गुरु>
/*
 * Copyright 2011, Netlogic Microप्रणालीs Inc.
 * Copyright 2004, Matt Porter <mporter@kernel.crashing.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>

/* XLR I2C REGISTERS */
#घोषणा XLR_I2C_CFG		0x00
#घोषणा XLR_I2C_CLKDIV		0x01
#घोषणा XLR_I2C_DEVADDR		0x02
#घोषणा XLR_I2C_ADDR		0x03
#घोषणा XLR_I2C_DATAOUT		0x04
#घोषणा XLR_I2C_DATAIN		0x05
#घोषणा XLR_I2C_STATUS		0x06
#घोषणा XLR_I2C_STARTXFR	0x07
#घोषणा XLR_I2C_BYTECNT		0x08
#घोषणा XLR_I2C_HDSTATIM	0x09

/* Sigma Designs additional रेजिस्टरs */
#घोषणा XLR_I2C_INT_EN		0x09
#घोषणा XLR_I2C_INT_STAT	0x0a

/* XLR I2C REGISTERS FLAGS */
#घोषणा XLR_I2C_BUS_BUSY	0x01
#घोषणा XLR_I2C_SDOEMPTY	0x02
#घोषणा XLR_I2C_RXRDY		0x04
#घोषणा XLR_I2C_ACK_ERR		0x08
#घोषणा XLR_I2C_ARB_STARTERR	0x30

/* Register Values */
#घोषणा XLR_I2C_CFG_ADDR	0xF8
#घोषणा XLR_I2C_CFG_NOADDR	0xFA
#घोषणा XLR_I2C_STARTXFR_ND	0x02    /* No Data */
#घोषणा XLR_I2C_STARTXFR_RD	0x01    /* Read */
#घोषणा XLR_I2C_STARTXFR_WR	0x00    /* Write */

#घोषणा XLR_I2C_TIMEOUT		10	/* समयout per byte in msec */

/*
 * On XLR/XLS, we need to use __raw_ IO to पढ़ो the I2C रेजिस्टरs
 * because they are in the big-endian MMIO area on the SoC.
 *
 * The पढ़ोl/ग_लिखोl implementation on XLR/XLS byteswaps, because
 * those are क्रम its little-endian PCI space (see arch/mips/Kconfig).
 */
अटल अंतरभूत व्योम xlr_i2c_wreg(u32 __iomem *base, अचिन्हित पूर्णांक reg, u32 val)
अणु
	__raw_ग_लिखोl(val, base + reg);
पूर्ण

अटल अंतरभूत u32 xlr_i2c_rdreg(u32 __iomem *base, अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(base + reg);
पूर्ण

#घोषणा XLR_I2C_FLAG_IRQ	1

काष्ठा xlr_i2c_config अणु
	u32 flags;		/* optional feature support */
	u32 status_busy;	/* value of STATUS[0] when busy */
	u32 cfg_extra;		/* extra CFG bits to set */
पूर्ण;

काष्ठा xlr_i2c_निजी अणु
	काष्ठा i2c_adapter adap;
	u32 __iomem *iobase;
	पूर्णांक irq;
	पूर्णांक pos;
	काष्ठा i2c_msg *msg;
	स्थिर काष्ठा xlr_i2c_config *cfg;
	रुको_queue_head_t रुको;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक xlr_i2c_busy(काष्ठा xlr_i2c_निजी *priv, u32 status)
अणु
	वापस (status & XLR_I2C_BUS_BUSY) == priv->cfg->status_busy;
पूर्ण

अटल पूर्णांक xlr_i2c_idle(काष्ठा xlr_i2c_निजी *priv)
अणु
	वापस !xlr_i2c_busy(priv, xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS));
पूर्ण

अटल पूर्णांक xlr_i2c_रुको(काष्ठा xlr_i2c_निजी *priv, अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक status;
	पूर्णांक t;

	t = रुको_event_समयout(priv->रुको, xlr_i2c_idle(priv),
				msecs_to_jअगरfies(समयout));
	अगर (!t)
		वापस -ETIMEDOUT;

	status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);

	वापस status & XLR_I2C_ACK_ERR ? -EIO : 0;
पूर्ण

अटल व्योम xlr_i2c_tx_irq(काष्ठा xlr_i2c_निजी *priv, u32 status)
अणु
	काष्ठा i2c_msg *msg = priv->msg;

	अगर (status & XLR_I2C_SDOEMPTY)
		xlr_i2c_wreg(priv->iobase, XLR_I2C_DATAOUT,
				msg->buf[priv->pos++]);
पूर्ण

अटल व्योम xlr_i2c_rx_irq(काष्ठा xlr_i2c_निजी *priv, u32 status)
अणु
	काष्ठा i2c_msg *msg = priv->msg;

	अगर (status & XLR_I2C_RXRDY)
		msg->buf[priv->pos++] =
			xlr_i2c_rdreg(priv->iobase, XLR_I2C_DATAIN);
पूर्ण

अटल irqवापस_t xlr_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xlr_i2c_निजी *priv = dev_id;
	काष्ठा i2c_msg *msg = priv->msg;
	u32 पूर्णांक_stat, status;

	पूर्णांक_stat = xlr_i2c_rdreg(priv->iobase, XLR_I2C_INT_STAT);
	अगर (!पूर्णांक_stat)
		वापस IRQ_NONE;

	xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_STAT, पूर्णांक_stat);

	अगर (!msg)
		वापस IRQ_HANDLED;

	status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);

	अगर (priv->pos < msg->len) अणु
		अगर (msg->flags & I2C_M_RD)
			xlr_i2c_rx_irq(priv, status);
		अन्यथा
			xlr_i2c_tx_irq(priv, status);
	पूर्ण

	अगर (!xlr_i2c_busy(priv, status))
		wake_up(&priv->रुको);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xlr_i2c_tx(काष्ठा xlr_i2c_निजी *priv,  u16 len,
	u8 *buf, u16 addr)
अणु
	काष्ठा i2c_adapter *adap = &priv->adap;
	अचिन्हित दीर्घ समयout, stopसमय, checkसमय;
	u32 i2c_status;
	पूर्णांक pos, समयकरोut;
	u8 offset;
	u32 xfer;

	offset = buf[0];
	xlr_i2c_wreg(priv->iobase, XLR_I2C_ADDR, offset);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_DEVADDR, addr);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_CFG,
			XLR_I2C_CFG_ADDR | priv->cfg->cfg_extra);

	समयout = msecs_to_jअगरfies(XLR_I2C_TIMEOUT);
	stopसमय = jअगरfies + समयout;
	समयकरोut = 0;

	अगर (len == 1) अणु
		xlr_i2c_wreg(priv->iobase, XLR_I2C_BYTECNT, len - 1);
		xfer = XLR_I2C_STARTXFR_ND;
		pos = 1;
	पूर्ण अन्यथा अणु
		xlr_i2c_wreg(priv->iobase, XLR_I2C_BYTECNT, len - 2);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_DATAOUT, buf[1]);
		xfer = XLR_I2C_STARTXFR_WR;
		pos = 2;
	पूर्ण

	priv->pos = pos;

retry:
	/* retry can only happen on the first byte */
	xlr_i2c_wreg(priv->iobase, XLR_I2C_STARTXFR, xfer);

	अगर (priv->irq > 0)
		वापस xlr_i2c_रुको(priv, XLR_I2C_TIMEOUT * len);

	जबतक (!समयकरोut) अणु
		checkसमय = jअगरfies;
		i2c_status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);

		अगर ((i2c_status & XLR_I2C_SDOEMPTY) && pos < len) अणु
			xlr_i2c_wreg(priv->iobase, XLR_I2C_DATAOUT, buf[pos++]);

			/* reset समयout on successful xmit */
			stopसमय = jअगरfies + समयout;
		पूर्ण
		समयकरोut = समय_after(checkसमय, stopसमय);

		अगर (i2c_status & XLR_I2C_ARB_STARTERR) अणु
			अगर (समयकरोut)
				अवरोध;
			जाओ retry;
		पूर्ण

		अगर (i2c_status & XLR_I2C_ACK_ERR)
			वापस -EIO;

		अगर (!xlr_i2c_busy(priv, i2c_status) && pos >= len)
			वापस 0;
	पूर्ण
	dev_err(&adap->dev, "I2C transmit timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक xlr_i2c_rx(काष्ठा xlr_i2c_निजी *priv, u16 len, u8 *buf, u16 addr)
अणु
	काष्ठा i2c_adapter *adap = &priv->adap;
	u32 i2c_status;
	अचिन्हित दीर्घ समयout, stopसमय, checkसमय;
	पूर्णांक nbytes, समयकरोut;

	xlr_i2c_wreg(priv->iobase, XLR_I2C_CFG,
			XLR_I2C_CFG_NOADDR | priv->cfg->cfg_extra);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_BYTECNT, len - 1);
	xlr_i2c_wreg(priv->iobase, XLR_I2C_DEVADDR, addr);

	priv->pos = 0;

	समयout = msecs_to_jअगरfies(XLR_I2C_TIMEOUT);
	stopसमय = jअगरfies + समयout;
	समयकरोut = 0;
	nbytes = 0;
retry:
	xlr_i2c_wreg(priv->iobase, XLR_I2C_STARTXFR, XLR_I2C_STARTXFR_RD);

	अगर (priv->irq > 0)
		वापस xlr_i2c_रुको(priv, XLR_I2C_TIMEOUT * len);

	जबतक (!समयकरोut) अणु
		checkसमय = jअगरfies;
		i2c_status = xlr_i2c_rdreg(priv->iobase, XLR_I2C_STATUS);
		अगर (i2c_status & XLR_I2C_RXRDY) अणु
			अगर (nbytes >= len)
				वापस -EIO;	/* should not happen */

			buf[nbytes++] =
				xlr_i2c_rdreg(priv->iobase, XLR_I2C_DATAIN);

			/* reset समयout on successful पढ़ो */
			stopसमय = jअगरfies + समयout;
		पूर्ण

		समयकरोut = समय_after(checkसमय, stopसमय);
		अगर (i2c_status & XLR_I2C_ARB_STARTERR) अणु
			अगर (समयकरोut)
				अवरोध;
			जाओ retry;
		पूर्ण

		अगर (i2c_status & XLR_I2C_ACK_ERR)
			वापस -EIO;

		अगर (!xlr_i2c_busy(priv, i2c_status))
			वापस 0;
	पूर्ण

	dev_err(&adap->dev, "I2C receive timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक xlr_i2c_xfer(काष्ठा i2c_adapter *adap,
	काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा i2c_msg *msg;
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा xlr_i2c_निजी *priv = i2c_get_adapdata(adap);

	ret = clk_enable(priv->clk);
	अगर (ret)
		वापस ret;

	अगर (priv->irq)
		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_EN, 0xf);


	क्रम (i = 0; ret == 0 && i < num; i++) अणु
		msg = &msgs[i];
		priv->msg = msg;
		अगर (msg->flags & I2C_M_RD)
			ret = xlr_i2c_rx(priv, msg->len, &msg->buf[0],
					msg->addr);
		अन्यथा
			ret = xlr_i2c_tx(priv, msg->len, &msg->buf[0],
					msg->addr);
	पूर्ण

	अगर (priv->irq)
		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_EN, 0);

	clk_disable(priv->clk);
	priv->msg = शून्य;

	वापस (ret != 0) ? ret : num;
पूर्ण

अटल u32 xlr_func(काष्ठा i2c_adapter *adap)
अणु
	/* Emulate SMBUS over I2C */
	वापस (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm xlr_i2c_algo = अणु
	.master_xfer	= xlr_i2c_xfer,
	.functionality	= xlr_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks xlr_i2c_quirks = अणु
	.flags = I2C_AQ_NO_ZERO_LEN,
पूर्ण;

अटल स्थिर काष्ठा xlr_i2c_config xlr_i2c_config_शेष = अणु
	.status_busy	= XLR_I2C_BUS_BUSY,
	.cfg_extra	= 0,
पूर्ण;

अटल स्थिर काष्ठा xlr_i2c_config xlr_i2c_config_tangox = अणु
	.flags		= XLR_I2C_FLAG_IRQ,
	.status_busy	= 0,
	.cfg_extra	= 1 << 8,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xlr_i2c_dt_ids[] = अणु
	अणु
		.compatible	= "sigma,smp8642-i2c",
		.data		= &xlr_i2c_config_tangox,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xlr_i2c_dt_ids);

अटल पूर्णांक xlr_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा xlr_i2c_निजी  *priv;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ clk_भाग;
	u32 busfreq;
	पूर्णांक irq;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	match = of_match_device(xlr_i2c_dt_ids, &pdev->dev);
	अगर (match)
		priv->cfg = match->data;
	अन्यथा
		priv->cfg = &xlr_i2c_config_शेष;

	priv->iobase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->iobase))
		वापस PTR_ERR(priv->iobase);

	irq = platक्रमm_get_irq(pdev, 0);

	अगर (irq > 0 && (priv->cfg->flags & XLR_I2C_FLAG_IRQ)) अणु
		priv->irq = irq;

		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_EN, 0);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_INT_STAT, 0xf);

		ret = devm_request_irq(&pdev->dev, priv->irq, xlr_i2c_irq,
					IRQF_SHARED, dev_name(&pdev->dev),
					priv);
		अगर (ret)
			वापस ret;

		init_रुकोqueue_head(&priv->रुको);
	पूर्ण

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				 &busfreq))
		busfreq = I2C_MAX_STANDARD_MODE_FREQ;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			वापस ret;

		clk_rate = clk_get_rate(clk);
		clk_भाग = DIV_ROUND_UP(clk_rate, 2 * busfreq);
		xlr_i2c_wreg(priv->iobase, XLR_I2C_CLKDIV, clk_भाग);

		clk_disable(clk);
		priv->clk = clk;
	पूर्ण

	priv->adap.dev.parent = &pdev->dev;
	priv->adap.dev.of_node	= pdev->dev.of_node;
	priv->adap.owner	= THIS_MODULE;
	priv->adap.algo_data	= priv;
	priv->adap.algo		= &xlr_i2c_algo;
	priv->adap.quirks	= &xlr_i2c_quirks;
	priv->adap.nr		= pdev->id;
	priv->adap.class	= I2C_CLASS_HWMON;
	snम_लिखो(priv->adap.name, माप(priv->adap.name), "xlr-i2c");

	i2c_set_adapdata(&priv->adap, priv);
	ret = i2c_add_numbered_adapter(&priv->adap);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);
	dev_info(&priv->adap.dev, "Added I2C Bus.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक xlr_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlr_i2c_निजी *priv;

	priv = platक्रमm_get_drvdata(pdev);
	i2c_del_adapter(&priv->adap);
	clk_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xlr_i2c_driver = अणु
	.probe  = xlr_i2c_probe,
	.हटाओ = xlr_i2c_हटाओ,
	.driver = अणु
		.name   = "xlr-i2cbus",
		.of_match_table	= xlr_i2c_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlr_i2c_driver);

MODULE_AUTHOR("Ganesan Ramalingam <ganesanr@netlogicmicro.com>");
MODULE_DESCRIPTION("XLR/XLS SoC I2C Controller driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:xlr-i2cbus");
