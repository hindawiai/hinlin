<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2021 Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 * For more inक्रमmation on Raspberry Pi's PoE hat see:
 * https://www.raspberrypi.org/products/poe-hat/
 *
 * Limitations:
 *  - No disable bit, so a disabled PWM is simulated by duty_cycle 0
 *  - Only normal polarity
 *  - Fixed 12.5 kHz period
 *
 * The current period is completed when HW is reconfigured.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#समावेश <soc/bcm2835/raspberrypi-firmware.h>
#समावेश <dt-bindings/pwm/raspberrypi,firmware-poe-pwm.h>

#घोषणा RPI_PWM_MAX_DUTY		255
#घोषणा RPI_PWM_PERIOD_NS		80000 /* 12.5 kHz */

#घोषणा RPI_PWM_CUR_DUTY_REG		0x0

काष्ठा raspberrypi_pwm अणु
	काष्ठा rpi_firmware *firmware;
	काष्ठा pwm_chip chip;
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

काष्ठा raspberrypi_pwm_prop अणु
	__le32 reg;
	__le32 val;
	__le32 ret;
पूर्ण __packed;

अटल अंतरभूत
काष्ठा raspberrypi_pwm *raspberrypi_pwm_from_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा raspberrypi_pwm, chip);
पूर्ण

अटल पूर्णांक raspberrypi_pwm_set_property(काष्ठा rpi_firmware *firmware,
					u32 reg, u32 val)
अणु
	काष्ठा raspberrypi_pwm_prop msg = अणु
		.reg = cpu_to_le32(reg),
		.val = cpu_to_le32(val),
	पूर्ण;
	पूर्णांक ret;

	ret = rpi_firmware_property(firmware, RPI_FIRMWARE_SET_POE_HAT_VAL,
				    &msg, माप(msg));
	अगर (ret)
		वापस ret;
	अगर (msg.ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक raspberrypi_pwm_get_property(काष्ठा rpi_firmware *firmware,
					u32 reg, u32 *val)
अणु
	काष्ठा raspberrypi_pwm_prop msg = अणु
		.reg = reg
	पूर्ण;
	पूर्णांक ret;

	ret = rpi_firmware_property(firmware, RPI_FIRMWARE_GET_POE_HAT_VAL,
				    &msg, माप(msg));
	अगर (ret)
		वापस ret;
	अगर (msg.ret)
		वापस -EIO;

	*val = le32_to_cpu(msg.val);

	वापस 0;
पूर्ण

अटल व्योम raspberrypi_pwm_get_state(काष्ठा pwm_chip *chip,
				      काष्ठा pwm_device *pwm,
				      काष्ठा pwm_state *state)
अणु
	काष्ठा raspberrypi_pwm *rpipwm = raspberrypi_pwm_from_chip(chip);

	state->period = RPI_PWM_PERIOD_NS;
	state->duty_cycle = DIV_ROUND_UP(rpipwm->duty_cycle * RPI_PWM_PERIOD_NS,
					 RPI_PWM_MAX_DUTY);
	state->enabled = !!(rpipwm->duty_cycle);
	state->polarity = PWM_POLARITY_NORMAL;
पूर्ण

अटल पूर्णांक raspberrypi_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा raspberrypi_pwm *rpipwm = raspberrypi_pwm_from_chip(chip);
	अचिन्हित पूर्णांक duty_cycle;
	पूर्णांक ret;

	अगर (state->period < RPI_PWM_PERIOD_NS ||
	    state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	अगर (!state->enabled)
		duty_cycle = 0;
	अन्यथा अगर (state->duty_cycle < RPI_PWM_PERIOD_NS)
		duty_cycle = DIV_ROUND_DOWN_ULL(state->duty_cycle * RPI_PWM_MAX_DUTY,
						RPI_PWM_PERIOD_NS);
	अन्यथा
		duty_cycle = RPI_PWM_MAX_DUTY;

	अगर (duty_cycle == rpipwm->duty_cycle)
		वापस 0;

	ret = raspberrypi_pwm_set_property(rpipwm->firmware, RPI_PWM_CUR_DUTY_REG,
					   duty_cycle);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to set duty cycle: %pe\n",
			ERR_PTR(ret));
		वापस ret;
	पूर्ण

	rpipwm->duty_cycle = duty_cycle;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops raspberrypi_pwm_ops = अणु
	.get_state = raspberrypi_pwm_get_state,
	.apply = raspberrypi_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक raspberrypi_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *firmware_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_firmware *firmware;
	काष्ठा raspberrypi_pwm *rpipwm;
	पूर्णांक ret;

	firmware_node = of_get_parent(dev->of_node);
	अगर (!firmware_node) अणु
		dev_err(dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	firmware = devm_rpi_firmware_get(&pdev->dev, firmware_node);
	of_node_put(firmware_node);
	अगर (!firmware)
		वापस dev_err_probe(dev, -EPROBE_DEFER,
				     "Failed to get firmware handle\n");

	rpipwm = devm_kzalloc(&pdev->dev, माप(*rpipwm), GFP_KERNEL);
	अगर (!rpipwm)
		वापस -ENOMEM;

	rpipwm->firmware = firmware;
	rpipwm->chip.dev = dev;
	rpipwm->chip.ops = &raspberrypi_pwm_ops;
	rpipwm->chip.base = -1;
	rpipwm->chip.npwm = RASPBERRYPI_FIRMWARE_PWM_NUM;

	platक्रमm_set_drvdata(pdev, rpipwm);

	ret = raspberrypi_pwm_get_property(rpipwm->firmware, RPI_PWM_CUR_DUTY_REG,
					   &rpipwm->duty_cycle);
	अगर (ret) अणु
		dev_err(dev, "Failed to get duty cycle: %pe\n", ERR_PTR(ret));
		वापस ret;
	पूर्ण

	वापस pwmchip_add(&rpipwm->chip);
पूर्ण

अटल पूर्णांक raspberrypi_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा raspberrypi_pwm *rpipwm = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&rpipwm->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id raspberrypi_pwm_of_match[] = अणु
	अणु .compatible = "raspberrypi,firmware-poe-pwm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, raspberrypi_pwm_of_match);

अटल काष्ठा platक्रमm_driver raspberrypi_pwm_driver = अणु
	.driver = अणु
		.name = "raspberrypi-poe-pwm",
		.of_match_table = raspberrypi_pwm_of_match,
	पूर्ण,
	.probe = raspberrypi_pwm_probe,
	.हटाओ = raspberrypi_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(raspberrypi_pwm_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de>");
MODULE_DESCRIPTION("Raspberry Pi Firmware Based PWM Bus Driver");
MODULE_LICENSE("GPL v2");
