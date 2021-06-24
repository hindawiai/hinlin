<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Solutions Highlander FPGA I2C/SMBus support.
 *
 * Supported devices: R0P7780LC0011RL, R0P7785LC0011RL
 *
 * Copyright (C) 2008  Paul Mundt
 * Copyright (C) 2008  Renesas Solutions Corp.
 * Copyright (C) 2008  Atom Create Engineering Co., Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#घोषणा SMCR		0x00
#घोषणा SMCR_START	(1 << 0)
#घोषणा SMCR_IRIC	(1 << 1)
#घोषणा SMCR_BBSY	(1 << 2)
#घोषणा SMCR_ACKE	(1 << 3)
#घोषणा SMCR_RST	(1 << 4)
#घोषणा SMCR_IEIC	(1 << 6)

#घोषणा SMSMADR		0x02

#घोषणा SMMR		0x04
#घोषणा SMMR_MODE0	(1 << 0)
#घोषणा SMMR_MODE1	(1 << 1)
#घोषणा SMMR_CAP	(1 << 3)
#घोषणा SMMR_TMMD	(1 << 4)
#घोषणा SMMR_SP		(1 << 7)

#घोषणा SMSADR		0x06
#घोषणा SMTRDR		0x46

काष्ठा highlander_i2c_dev अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा i2c_adapter	adapter;
	काष्ठा completion	cmd_complete;
	अचिन्हित दीर्घ		last_पढ़ो_समय;
	पूर्णांक			irq;
	u8			*buf;
	माप_प्रकार			buf_len;
पूर्ण;

अटल bool iic_क्रमce_poll, iic_क्रमce_normal;
अटल पूर्णांक iic_समयout = 1000, iic_पढ़ो_delay;

अटल अंतरभूत व्योम highlander_i2c_irq_enable(काष्ठा highlander_i2c_dev *dev)
अणु
	ioग_लिखो16(ioपढ़ो16(dev->base + SMCR) | SMCR_IEIC, dev->base + SMCR);
पूर्ण

अटल अंतरभूत व्योम highlander_i2c_irq_disable(काष्ठा highlander_i2c_dev *dev)
अणु
	ioग_लिखो16(ioपढ़ो16(dev->base + SMCR) & ~SMCR_IEIC, dev->base + SMCR);
पूर्ण

अटल अंतरभूत व्योम highlander_i2c_start(काष्ठा highlander_i2c_dev *dev)
अणु
	ioग_लिखो16(ioपढ़ो16(dev->base + SMCR) | SMCR_START, dev->base + SMCR);
पूर्ण

अटल अंतरभूत व्योम highlander_i2c_करोne(काष्ठा highlander_i2c_dev *dev)
अणु
	ioग_लिखो16(ioपढ़ो16(dev->base + SMCR) | SMCR_IRIC, dev->base + SMCR);
पूर्ण

अटल व्योम highlander_i2c_setup(काष्ठा highlander_i2c_dev *dev)
अणु
	u16 smmr;

	smmr = ioपढ़ो16(dev->base + SMMR);
	smmr |= SMMR_TMMD;

	अगर (iic_क्रमce_normal)
		smmr &= ~SMMR_SP;
	अन्यथा
		smmr |= SMMR_SP;

	ioग_लिखो16(smmr, dev->base + SMMR);
पूर्ण

अटल व्योम smbus_ग_लिखो_data(u8 *src, u16 *dst, पूर्णांक len)
अणु
	क्रम (; len > 1; len -= 2) अणु
		*dst++ = be16_to_cpup((__be16 *)src);
		src += 2;
	पूर्ण

	अगर (len)
		*dst = *src << 8;
पूर्ण

अटल व्योम smbus_पढ़ो_data(u16 *src, u8 *dst, पूर्णांक len)
अणु
	क्रम (; len > 1; len -= 2) अणु
		*(__be16 *)dst = cpu_to_be16p(src++);
		dst += 2;
	पूर्ण

	अगर (len)
		*dst = *src >> 8;
पूर्ण

अटल व्योम highlander_i2c_command(काष्ठा highlander_i2c_dev *dev,
				   u8 command, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	u16 cmd = (command << 8) | command;

	क्रम (i = 0; i < len; i += 2) अणु
		अगर (len - i == 1)
			cmd = command << 8;
		ioग_लिखो16(cmd, dev->base + SMSADR + i);
		dev_dbg(dev->dev, "command data[%x] 0x%04x\n", i/2, cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक highlander_i2c_रुको_क्रम_bbsy(काष्ठा highlander_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(iic_समयout);
	जबतक (ioपढ़ो16(dev->base + SMCR) & SMCR_BBSY) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(dev->dev, "timeout waiting for bus ready\n");
			वापस -ETIMEDOUT;
		पूर्ण

		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक highlander_i2c_reset(काष्ठा highlander_i2c_dev *dev)
अणु
	ioग_लिखो16(ioपढ़ो16(dev->base + SMCR) | SMCR_RST, dev->base + SMCR);
	वापस highlander_i2c_रुको_क्रम_bbsy(dev);
पूर्ण

अटल पूर्णांक highlander_i2c_रुको_क्रम_ack(काष्ठा highlander_i2c_dev *dev)
अणु
	u16 पंचांगp = ioपढ़ो16(dev->base + SMCR);

	अगर ((पंचांगp & (SMCR_IRIC | SMCR_ACKE)) == SMCR_ACKE) अणु
		dev_warn(dev->dev, "ack abnormality\n");
		वापस highlander_i2c_reset(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t highlander_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा highlander_i2c_dev *dev = dev_id;

	highlander_i2c_करोne(dev);
	complete(&dev->cmd_complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम highlander_i2c_poll(काष्ठा highlander_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ समयout;
	u16 smcr;

	समयout = jअगरfies + msecs_to_jअगरfies(iic_समयout);
	क्रम (;;) अणु
		smcr = ioपढ़ो16(dev->base + SMCR);

		/*
		 * Don't bother checking ACKE here, this and the reset
		 * are handled in highlander_i2c_रुको_xfer_करोne() when
		 * रुकोing क्रम the ACK.
		 */

		अगर (smcr & SMCR_IRIC)
			वापस;
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		cpu_relax();
		cond_resched();
	पूर्ण

	dev_err(dev->dev, "polling timed out\n");
पूर्ण

अटल अंतरभूत पूर्णांक highlander_i2c_रुको_xfer_करोne(काष्ठा highlander_i2c_dev *dev)
अणु
	अगर (dev->irq)
		रुको_क्रम_completion_समयout(&dev->cmd_complete,
					  msecs_to_jअगरfies(iic_समयout));
	अन्यथा
		/* busy looping, the IRQ of champions */
		highlander_i2c_poll(dev);

	वापस highlander_i2c_रुको_क्रम_ack(dev);
पूर्ण

अटल पूर्णांक highlander_i2c_पढ़ो(काष्ठा highlander_i2c_dev *dev)
अणु
	पूर्णांक i, cnt;
	u16 data[16];

	अगर (highlander_i2c_रुको_क्रम_bbsy(dev))
		वापस -EAGAIN;

	highlander_i2c_start(dev);

	अगर (highlander_i2c_रुको_xfer_करोne(dev)) अणु
		dev_err(dev->dev, "Arbitration loss\n");
		वापस -EAGAIN;
	पूर्ण

	/*
	 * The R0P7780LC0011RL FPGA needs a signअगरicant delay between
	 * data पढ़ो cycles, otherwise the transceiver माला_लो confused and
	 * garbage is वापसed when the पढ़ो is subsequently पातed.
	 *
	 * It is not sufficient to रुको क्रम BBSY.
	 *
	 * While this generally only applies to the older SH7780-based
	 * Highlanders, the same issue can be observed on SH7785 ones,
	 * albeit less frequently. SH7780-based Highlanders may need
	 * this to be as high as 1000 ms.
	 */
	अगर (iic_पढ़ो_delay && समय_beक्रमe(jअगरfies, dev->last_पढ़ो_समय +
				 msecs_to_jअगरfies(iic_पढ़ो_delay)))
		msleep(jअगरfies_to_msecs((dev->last_पढ़ो_समय +
				msecs_to_jअगरfies(iic_पढ़ो_delay)) - jअगरfies));

	cnt = (dev->buf_len + 1) >> 1;
	क्रम (i = 0; i < cnt; i++) अणु
		data[i] = ioपढ़ो16(dev->base + SMTRDR + (i * माप(u16)));
		dev_dbg(dev->dev, "read data[%x] 0x%04x\n", i, data[i]);
	पूर्ण

	smbus_पढ़ो_data(data, dev->buf, dev->buf_len);

	dev->last_पढ़ो_समय = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक highlander_i2c_ग_लिखो(काष्ठा highlander_i2c_dev *dev)
अणु
	पूर्णांक i, cnt;
	u16 data[16];

	smbus_ग_लिखो_data(dev->buf, data, dev->buf_len);

	cnt = (dev->buf_len + 1) >> 1;
	क्रम (i = 0; i < cnt; i++) अणु
		ioग_लिखो16(data[i], dev->base + SMTRDR + (i * माप(u16)));
		dev_dbg(dev->dev, "write data[%x] 0x%04x\n", i, data[i]);
	पूर्ण

	अगर (highlander_i2c_रुको_क्रम_bbsy(dev))
		वापस -EAGAIN;

	highlander_i2c_start(dev);

	वापस highlander_i2c_रुको_xfer_करोne(dev);
पूर्ण

अटल पूर्णांक highlander_i2c_smbus_xfer(काष्ठा i2c_adapter *adap, u16 addr,
				  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				  u8 command, पूर्णांक size,
				  जोड़ i2c_smbus_data *data)
अणु
	काष्ठा highlander_i2c_dev *dev = i2c_get_adapdata(adap);
	u16 पंचांगp;

	init_completion(&dev->cmd_complete);

	dev_dbg(dev->dev, "addr %04x, command %02x, read_write %d, size %d\n",
		addr, command, पढ़ो_ग_लिखो, size);

	/*
	 * Set up the buffer and transfer size
	 */
	चयन (size) अणु
	हाल I2C_SMBUS_BYTE_DATA:
		dev->buf = &data->byte;
		dev->buf_len = 1;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		dev->buf = &data->block[1];
		dev->buf_len = data->block[0];
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported command %d\n", size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Encode the mode setting
	 */
	पंचांगp = ioपढ़ो16(dev->base + SMMR);
	पंचांगp &= ~(SMMR_MODE0 | SMMR_MODE1);

	चयन (dev->buf_len) अणु
	हाल 1:
		/* शेष */
		अवरोध;
	हाल 8:
		पंचांगp |= SMMR_MODE0;
		अवरोध;
	हाल 16:
		पंचांगp |= SMMR_MODE1;
		अवरोध;
	हाल 32:
		पंचांगp |= (SMMR_MODE0 | SMMR_MODE1);
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported xfer size %zu\n", dev->buf_len);
		वापस -EINVAL;
	पूर्ण

	ioग_लिखो16(पंचांगp, dev->base + SMMR);

	/* Ensure we're in a sane state */
	highlander_i2c_करोne(dev);

	/* Set slave address */
	ioग_लिखो16((addr << 1) | पढ़ो_ग_लिखो, dev->base + SMSMADR);

	highlander_i2c_command(dev, command, dev->buf_len);

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		वापस highlander_i2c_पढ़ो(dev);
	अन्यथा
		वापस highlander_i2c_ग_लिखो(dev);
पूर्ण

अटल u32 highlander_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm highlander_i2c_algo = अणु
	.smbus_xfer	= highlander_i2c_smbus_xfer,
	.functionality	= highlander_i2c_func,
पूर्ण;

अटल पूर्णांक highlander_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा highlander_i2c_dev *dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!res)) अणु
		dev_err(&pdev->dev, "no mem resource\n");
		वापस -ENODEV;
	पूर्ण

	dev = kzalloc(माप(काष्ठा highlander_i2c_dev), GFP_KERNEL);
	अगर (unlikely(!dev))
		वापस -ENOMEM;

	dev->base = ioremap(res->start, resource_size(res));
	अगर (unlikely(!dev->base)) अणु
		ret = -ENXIO;
		जाओ err;
	पूर्ण

	dev->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dev);

	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (iic_क्रमce_poll)
		dev->irq = 0;

	अगर (dev->irq) अणु
		ret = request_irq(dev->irq, highlander_i2c_irq, 0,
				  pdev->name, dev);
		अगर (unlikely(ret))
			जाओ err_unmap;

		highlander_i2c_irq_enable(dev);
	पूर्ण अन्यथा अणु
		dev_notice(&pdev->dev, "no IRQ, using polling mode\n");
		highlander_i2c_irq_disable(dev);
	पूर्ण

	dev->last_पढ़ो_समय = jअगरfies;	/* initial पढ़ो jअगरfies */

	highlander_i2c_setup(dev);

	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON;
	strlcpy(adap->name, "HL FPGA I2C adapter", माप(adap->name));
	adap->algo = &highlander_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->nr = pdev->id;

	/*
	 * Reset the adapter
	 */
	ret = highlander_i2c_reset(dev);
	अगर (unlikely(ret)) अणु
		dev_err(&pdev->dev, "controller didn't come up\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	ret = i2c_add_numbered_adapter(adap);
	अगर (unlikely(ret)) अणु
		dev_err(&pdev->dev, "failure adding adapter\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	वापस 0;

err_मुक्त_irq:
	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
err_unmap:
	iounmap(dev->base);
err:
	kमुक्त(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक highlander_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा highlander_i2c_dev *dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);

	iounmap(dev->base);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver highlander_i2c_driver = अणु
	.driver		= अणु
		.name	= "i2c-highlander",
	पूर्ण,

	.probe		= highlander_i2c_probe,
	.हटाओ		= highlander_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(highlander_i2c_driver);

MODULE_AUTHOR("Paul Mundt");
MODULE_DESCRIPTION("Renesas Highlander FPGA I2C/SMBus adapter");
MODULE_LICENSE("GPL v2");

module_param(iic_क्रमce_poll, bool, 0);
module_param(iic_क्रमce_normal, bool, 0);
module_param(iic_समयout, पूर्णांक, 0);
module_param(iic_पढ़ो_delay, पूर्णांक, 0);

MODULE_PARM_DESC(iic_क्रमce_poll, "Force polling mode");
MODULE_PARM_DESC(iic_क्रमce_normal,
		 "Force normal mode (100 kHz), default is fast mode (400 kHz)");
MODULE_PARM_DESC(iic_समयout, "Set timeout value in msecs (default 1000 ms)");
MODULE_PARM_DESC(iic_पढ़ो_delay,
		 "Delay between data read cycles (default 0 ms)");
