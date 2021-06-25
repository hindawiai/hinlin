<शैली गुरु>
/*
 * (C) Copyright 2009-2010
 * Nokia Siemens Networks, michael.lawnick.ext@nsn.com
 *
 * Portions Copyright (C) 2010 - 2016 Cavium, Inc.
 *
 * This is a driver क्रम the i2c adapter in Cavium Networks' OCTEON processors.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश "i2c-octeon-core.h"

#घोषणा DRV_NAME "i2c-octeon"

/**
 * octeon_i2c_पूर्णांक_enable - enable the CORE पूर्णांकerrupt
 * @i2c: The काष्ठा octeon_i2c
 *
 * The पूर्णांकerrupt will be निश्चितed when there is non-STAT_IDLE state in
 * the SW_TWSI_EOP_TWSI_STAT रेजिस्टर.
 */
अटल व्योम octeon_i2c_पूर्णांक_enable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, TWSI_INT_CORE_EN);
पूर्ण

/* disable the CORE पूर्णांकerrupt */
अटल व्योम octeon_i2c_पूर्णांक_disable(काष्ठा octeon_i2c *i2c)
अणु
	/* clear TS/ST/IFLG events */
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, 0);
पूर्ण

/**
 * octeon_i2c_पूर्णांक_enable78 - enable the CORE पूर्णांकerrupt
 * @i2c: The काष्ठा octeon_i2c
 *
 * The पूर्णांकerrupt will be निश्चितed when there is non-STAT_IDLE state in the
 * SW_TWSI_EOP_TWSI_STAT रेजिस्टर.
 */
अटल व्योम octeon_i2c_पूर्णांक_enable78(काष्ठा octeon_i2c *i2c)
अणु
	atomic_inc_वापस(&i2c->पूर्णांक_enable_cnt);
	enable_irq(i2c->irq);
पूर्ण

अटल व्योम __octeon_i2c_irq_disable(atomic_t *cnt, पूर्णांक irq)
अणु
	पूर्णांक count;

	/*
	 * The पूर्णांकerrupt can be disabled in two places, but we only
	 * want to make the disable_irq_nosync() call once, so keep
	 * track with the atomic variable.
	 */
	count = atomic_dec_अगर_positive(cnt);
	अगर (count >= 0)
		disable_irq_nosync(irq);
पूर्ण

/* disable the CORE पूर्णांकerrupt */
अटल व्योम octeon_i2c_पूर्णांक_disable78(काष्ठा octeon_i2c *i2c)
अणु
	__octeon_i2c_irq_disable(&i2c->पूर्णांक_enable_cnt, i2c->irq);
पूर्ण

/**
 * octeon_i2c_hlc_पूर्णांक_enable78 - enable the ST पूर्णांकerrupt
 * @i2c: The काष्ठा octeon_i2c
 *
 * The पूर्णांकerrupt will be निश्चितed when there is non-STAT_IDLE state in
 * the SW_TWSI_EOP_TWSI_STAT रेजिस्टर.
 */
अटल व्योम octeon_i2c_hlc_पूर्णांक_enable78(काष्ठा octeon_i2c *i2c)
अणु
	atomic_inc_वापस(&i2c->hlc_पूर्णांक_enable_cnt);
	enable_irq(i2c->hlc_irq);
पूर्ण

/* disable the ST पूर्णांकerrupt */
अटल व्योम octeon_i2c_hlc_पूर्णांक_disable78(काष्ठा octeon_i2c *i2c)
अणु
	__octeon_i2c_irq_disable(&i2c->hlc_पूर्णांक_enable_cnt, i2c->hlc_irq);
पूर्ण

/* HLC पूर्णांकerrupt service routine */
अटल irqवापस_t octeon_i2c_hlc_isr78(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा octeon_i2c *i2c = dev_id;

	i2c->hlc_पूर्णांक_disable(i2c);
	wake_up(&i2c->queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम octeon_i2c_hlc_पूर्णांक_enable(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, TWSI_INT_ST_EN);
पूर्ण

अटल u32 octeon_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA | I2C_SMBUS_BLOCK_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm octeon_i2c_algo = अणु
	.master_xfer = octeon_i2c_xfer,
	.functionality = octeon_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter octeon_i2c_ops = अणु
	.owner = THIS_MODULE,
	.name = "OCTEON adapter",
	.algo = &octeon_i2c_algo,
पूर्ण;

अटल पूर्णांक octeon_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक irq, result = 0, hlc_irq = 0;
	काष्ठा octeon_i2c *i2c;
	bool cn78xx_style;

	cn78xx_style = of_device_is_compatible(node, "cavium,octeon-7890-twsi");
	अगर (cn78xx_style) अणु
		hlc_irq = platक्रमm_get_irq(pdev, 0);
		अगर (hlc_irq < 0)
			वापस hlc_irq;

		irq = platक्रमm_get_irq(pdev, 2);
		अगर (irq < 0)
			वापस irq;
	पूर्ण अन्यथा अणु
		/* All adaptors have an irq.  */
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;
	पूर्ण

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c) अणु
		result = -ENOMEM;
		जाओ out;
	पूर्ण
	i2c->dev = &pdev->dev;

	i2c->roff.sw_twsi = 0x00;
	i2c->roff.twsi_पूर्णांक = 0x10;
	i2c->roff.sw_twsi_ext = 0x18;

	i2c->twsi_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->twsi_base)) अणु
		result = PTR_ERR(i2c->twsi_base);
		जाओ out;
	पूर्ण

	/*
	 * "clock-rate" is a legacy binding, the official binding is
	 * "clock-frequency".  Try the official one first and then
	 * fall back अगर it करोesn't exist.
	 */
	अगर (of_property_पढ़ो_u32(node, "clock-frequency", &i2c->twsi_freq) &&
	    of_property_पढ़ो_u32(node, "clock-rate", &i2c->twsi_freq)) अणु
		dev_err(i2c->dev,
			"no I2C 'clock-rate' or 'clock-frequency' property\n");
		result = -ENXIO;
		जाओ out;
	पूर्ण

	i2c->sys_freq = octeon_get_io_घड़ी_rate();

	init_रुकोqueue_head(&i2c->queue);

	i2c->irq = irq;

	अगर (cn78xx_style) अणु
		i2c->hlc_irq = hlc_irq;

		i2c->पूर्णांक_enable = octeon_i2c_पूर्णांक_enable78;
		i2c->पूर्णांक_disable = octeon_i2c_पूर्णांक_disable78;
		i2c->hlc_पूर्णांक_enable = octeon_i2c_hlc_पूर्णांक_enable78;
		i2c->hlc_पूर्णांक_disable = octeon_i2c_hlc_पूर्णांक_disable78;

		irq_set_status_flags(i2c->irq, IRQ_NOAUTOEN);
		irq_set_status_flags(i2c->hlc_irq, IRQ_NOAUTOEN);

		result = devm_request_irq(&pdev->dev, i2c->hlc_irq,
					  octeon_i2c_hlc_isr78, 0,
					  DRV_NAME, i2c);
		अगर (result < 0) अणु
			dev_err(i2c->dev, "failed to attach interrupt\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		i2c->पूर्णांक_enable = octeon_i2c_पूर्णांक_enable;
		i2c->पूर्णांक_disable = octeon_i2c_पूर्णांक_disable;
		i2c->hlc_पूर्णांक_enable = octeon_i2c_hlc_पूर्णांक_enable;
		i2c->hlc_पूर्णांक_disable = octeon_i2c_पूर्णांक_disable;
	पूर्ण

	result = devm_request_irq(&pdev->dev, i2c->irq,
				  octeon_i2c_isr, 0, DRV_NAME, i2c);
	अगर (result < 0) अणु
		dev_err(i2c->dev, "failed to attach interrupt\n");
		जाओ out;
	पूर्ण

	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX))
		i2c->broken_irq_check = true;

	result = octeon_i2c_init_lowlevel(i2c);
	अगर (result) अणु
		dev_err(i2c->dev, "init low level failed\n");
		जाओ  out;
	पूर्ण

	octeon_i2c_set_घड़ी(i2c);

	i2c->adap = octeon_i2c_ops;
	i2c->adap.समयout = msecs_to_jअगरfies(2);
	i2c->adap.retries = 5;
	i2c->adap.bus_recovery_info = &octeon_i2c_recovery_info;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = node;
	i2c_set_adapdata(&i2c->adap, i2c);
	platक्रमm_set_drvdata(pdev, i2c);

	result = i2c_add_adapter(&i2c->adap);
	अगर (result < 0)
		जाओ out;
	dev_info(i2c->dev, "probed\n");
	वापस 0;

out:
	वापस result;
पूर्ण;

अटल पूर्णांक octeon_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा octeon_i2c *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);
	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id octeon_i2c_match[] = अणु
	अणु .compatible = "cavium,octeon-3860-twsi", पूर्ण,
	अणु .compatible = "cavium,octeon-7890-twsi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_i2c_match);

अटल काष्ठा platक्रमm_driver octeon_i2c_driver = अणु
	.probe		= octeon_i2c_probe,
	.हटाओ		= octeon_i2c_हटाओ,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = octeon_i2c_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(octeon_i2c_driver);

MODULE_AUTHOR("Michael Lawnick <michael.lawnick.ext@nsn.com>");
MODULE_DESCRIPTION("I2C-Bus adapter for Cavium OCTEON processors");
MODULE_LICENSE("GPL");
