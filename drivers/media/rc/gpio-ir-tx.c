<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Sean Young <sean@mess.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME	"gpio-ir-tx"
#घोषणा DEVICE_NAME	"GPIO IR Bit Banging Transmitter"

काष्ठा gpio_ir अणु
	काष्ठा gpio_desc *gpio;
	अचिन्हित पूर्णांक carrier;
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

अटल स्थिर काष्ठा of_device_id gpio_ir_tx_of_match[] = अणु
	अणु .compatible = "gpio-ir-tx", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_ir_tx_of_match);

अटल पूर्णांक gpio_ir_tx_set_duty_cycle(काष्ठा rc_dev *dev, u32 duty_cycle)
अणु
	काष्ठा gpio_ir *gpio_ir = dev->priv;

	gpio_ir->duty_cycle = duty_cycle;

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_ir_tx_set_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा gpio_ir *gpio_ir = dev->priv;

	अगर (carrier > 500000)
		वापस -EINVAL;

	gpio_ir->carrier = carrier;

	वापस 0;
पूर्ण

अटल व्योम gpio_ir_tx_unmodulated(काष्ठा gpio_ir *gpio_ir, uपूर्णांक *txbuf,
				   uपूर्णांक count)
अणु
	kसमय_प्रकार edge;
	s32 delta;
	पूर्णांक i;

	local_irq_disable();

	edge = kसमय_get();

	क्रम (i = 0; i < count; i++) अणु
		gpiod_set_value(gpio_ir->gpio, !(i % 2));

		edge = kसमय_add_us(edge, txbuf[i]);
		delta = kसमय_us_delta(edge, kसमय_get());
		अगर (delta > 0)
			udelay(delta);
	पूर्ण

	gpiod_set_value(gpio_ir->gpio, 0);
पूर्ण

अटल व्योम gpio_ir_tx_modulated(काष्ठा gpio_ir *gpio_ir, uपूर्णांक *txbuf,
				 uपूर्णांक count)
अणु
	kसमय_प्रकार edge;
	/*
	 * delta should never exceed 0.5 seconds (IR_MAX_DURATION) and on
	 * m68k ndelay(s64) करोes not compile; so use s32 rather than s64.
	 */
	s32 delta;
	पूर्णांक i;
	अचिन्हित पूर्णांक pulse, space;

	/* Ensure the भागidend fits पूर्णांकo 32 bit */
	pulse = DIV_ROUND_CLOSEST(gpio_ir->duty_cycle * (NSEC_PER_SEC / 100),
				  gpio_ir->carrier);
	space = DIV_ROUND_CLOSEST((100 - gpio_ir->duty_cycle) *
				  (NSEC_PER_SEC / 100), gpio_ir->carrier);

	local_irq_disable();

	edge = kसमय_get();

	क्रम (i = 0; i < count; i++) अणु
		अगर (i % 2) अणु
			// space
			edge = kसमय_add_us(edge, txbuf[i]);
			delta = kसमय_us_delta(edge, kसमय_get());
			अगर (delta > 0)
				udelay(delta);
		पूर्ण अन्यथा अणु
			// pulse
			kसमय_प्रकार last = kसमय_add_us(edge, txbuf[i]);

			जबतक (kसमय_beक्रमe(kसमय_get(), last)) अणु
				gpiod_set_value(gpio_ir->gpio, 1);
				edge = kसमय_add_ns(edge, pulse);
				delta = kसमय_प्रकारo_ns(kसमय_sub(edge,
							      kसमय_get()));
				अगर (delta > 0)
					ndelay(delta);
				gpiod_set_value(gpio_ir->gpio, 0);
				edge = kसमय_add_ns(edge, space);
				delta = kसमय_प्रकारo_ns(kसमय_sub(edge,
							      kसमय_get()));
				अगर (delta > 0)
					ndelay(delta);
			पूर्ण

			edge = last;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_ir_tx(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *txbuf,
		      अचिन्हित पूर्णांक count)
अणु
	काष्ठा gpio_ir *gpio_ir = dev->priv;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (gpio_ir->carrier)
		gpio_ir_tx_modulated(gpio_ir, txbuf, count);
	अन्यथा
		gpio_ir_tx_unmodulated(gpio_ir, txbuf, count);
	local_irq_restore(flags);

	वापस count;
पूर्ण

अटल पूर्णांक gpio_ir_tx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_ir *gpio_ir;
	काष्ठा rc_dev *rcdev;
	पूर्णांक rc;

	gpio_ir = devm_kदो_स्मृति(&pdev->dev, माप(*gpio_ir), GFP_KERNEL);
	अगर (!gpio_ir)
		वापस -ENOMEM;

	rcdev = devm_rc_allocate_device(&pdev->dev, RC_DRIVER_IR_RAW_TX);
	अगर (!rcdev)
		वापस -ENOMEM;

	gpio_ir->gpio = devm_gpiod_get(&pdev->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio_ir->gpio)) अणु
		अगर (PTR_ERR(gpio_ir->gpio) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get gpio (%ld)\n",
				PTR_ERR(gpio_ir->gpio));
		वापस PTR_ERR(gpio_ir->gpio);
	पूर्ण

	rcdev->priv = gpio_ir;
	rcdev->driver_name = DRIVER_NAME;
	rcdev->device_name = DEVICE_NAME;
	rcdev->tx_ir = gpio_ir_tx;
	rcdev->s_tx_duty_cycle = gpio_ir_tx_set_duty_cycle;
	rcdev->s_tx_carrier = gpio_ir_tx_set_carrier;

	gpio_ir->carrier = 38000;
	gpio_ir->duty_cycle = 50;

	rc = devm_rc_रेजिस्टर_device(&pdev->dev, rcdev);
	अगर (rc < 0)
		dev_err(&pdev->dev, "failed to register rc device\n");

	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver gpio_ir_tx_driver = अणु
	.probe	= gpio_ir_tx_probe,
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(gpio_ir_tx_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(gpio_ir_tx_driver);

MODULE_DESCRIPTION("GPIO IR Bit Banging Transmitter");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
