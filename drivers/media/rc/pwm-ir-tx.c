<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Sean Young <sean@mess.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pwm.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME	"pwm-ir-tx"
#घोषणा DEVICE_NAME	"PWM IR Transmitter"

काष्ठा pwm_ir अणु
	काष्ठा pwm_device *pwm;
	अचिन्हित पूर्णांक carrier;
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

अटल स्थिर काष्ठा of_device_id pwm_ir_of_match[] = अणु
	अणु .compatible = "pwm-ir-tx", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_ir_of_match);

अटल पूर्णांक pwm_ir_set_duty_cycle(काष्ठा rc_dev *dev, u32 duty_cycle)
अणु
	काष्ठा pwm_ir *pwm_ir = dev->priv;

	pwm_ir->duty_cycle = duty_cycle;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_ir_set_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा pwm_ir *pwm_ir = dev->priv;

	अगर (!carrier)
		वापस -EINVAL;

	pwm_ir->carrier = carrier;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_ir_tx(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *txbuf,
		     अचिन्हित पूर्णांक count)
अणु
	काष्ठा pwm_ir *pwm_ir = dev->priv;
	काष्ठा pwm_device *pwm = pwm_ir->pwm;
	पूर्णांक i, duty, period;
	kसमय_प्रकार edge;
	दीर्घ delta;

	period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, pwm_ir->carrier);
	duty = DIV_ROUND_CLOSEST(pwm_ir->duty_cycle * period, 100);

	pwm_config(pwm, duty, period);

	edge = kसमय_get();

	क्रम (i = 0; i < count; i++) अणु
		अगर (i % 2) // space
			pwm_disable(pwm);
		अन्यथा
			pwm_enable(pwm);

		edge = kसमय_add_us(edge, txbuf[i]);
		delta = kसमय_us_delta(edge, kसमय_get());
		अगर (delta > 0)
			usleep_range(delta, delta + 10);
	पूर्ण

	pwm_disable(pwm);

	वापस count;
पूर्ण

अटल पूर्णांक pwm_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_ir *pwm_ir;
	काष्ठा rc_dev *rcdev;
	पूर्णांक rc;

	pwm_ir = devm_kदो_स्मृति(&pdev->dev, माप(*pwm_ir), GFP_KERNEL);
	अगर (!pwm_ir)
		वापस -ENOMEM;

	pwm_ir->pwm = devm_pwm_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm_ir->pwm))
		वापस PTR_ERR(pwm_ir->pwm);

	pwm_ir->carrier = 38000;
	pwm_ir->duty_cycle = 50;

	rcdev = devm_rc_allocate_device(&pdev->dev, RC_DRIVER_IR_RAW_TX);
	अगर (!rcdev)
		वापस -ENOMEM;

	rcdev->priv = pwm_ir;
	rcdev->driver_name = DRIVER_NAME;
	rcdev->device_name = DEVICE_NAME;
	rcdev->tx_ir = pwm_ir_tx;
	rcdev->s_tx_duty_cycle = pwm_ir_set_duty_cycle;
	rcdev->s_tx_carrier = pwm_ir_set_carrier;

	rc = devm_rc_रेजिस्टर_device(&pdev->dev, rcdev);
	अगर (rc < 0)
		dev_err(&pdev->dev, "failed to register rc device\n");

	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver pwm_ir_driver = अणु
	.probe = pwm_ir_probe,
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(pwm_ir_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pwm_ir_driver);

MODULE_DESCRIPTION("PWM IR Transmitter");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
