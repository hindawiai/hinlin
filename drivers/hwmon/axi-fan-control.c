<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fan Control HDL CORE driver
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/fpga/adi-axi-common.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/* रेजिस्टर map */
#घोषणा ADI_REG_RSTN		0x0080
#घोषणा ADI_REG_PWM_WIDTH	0x0084
#घोषणा ADI_REG_TACH_PERIOD	0x0088
#घोषणा ADI_REG_TACH_TOLERANCE	0x008c
#घोषणा ADI_REG_PWM_PERIOD	0x00c0
#घोषणा ADI_REG_TACH_MEASUR	0x00c4
#घोषणा ADI_REG_TEMPERATURE	0x00c8

#घोषणा ADI_REG_IRQ_MASK	0x0040
#घोषणा ADI_REG_IRQ_PENDING	0x0044
#घोषणा ADI_REG_IRQ_SRC		0x0048

/* IRQ sources */
#घोषणा ADI_IRQ_SRC_PWM_CHANGED		BIT(0)
#घोषणा ADI_IRQ_SRC_TACH_ERR		BIT(1)
#घोषणा ADI_IRQ_SRC_TEMP_INCREASE	BIT(2)
#घोषणा ADI_IRQ_SRC_NEW_MEASUR		BIT(3)
#घोषणा ADI_IRQ_SRC_MASK		GENMASK(3, 0)
#घोषणा ADI_IRQ_MASK_OUT_ALL		0xFFFFFFFFU

#घोषणा SYSFS_PWM_MAX			255

काष्ठा axi_fan_control_data अणु
	व्योम __iomem *base;
	काष्ठा device *hdev;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक irq;
	/* pulses per revolution */
	u32 ppr;
	bool hw_pwm_req;
	bool update_tacho_params;
	u8 fan_fault;
पूर्ण;

अटल अंतरभूत व्योम axi_ioग_लिखो(स्थिर u32 val, स्थिर u32 reg,
			       स्थिर काष्ठा axi_fan_control_data *ctl)
अणु
	ioग_लिखो32(val, ctl->base + reg);
पूर्ण

अटल अंतरभूत u32 axi_ioपढ़ो(स्थिर u32 reg,
			     स्थिर काष्ठा axi_fan_control_data *ctl)
अणु
	वापस ioपढ़ो32(ctl->base + reg);
पूर्ण

अटल दीर्घ axi_fan_control_get_pwm_duty(स्थिर काष्ठा axi_fan_control_data *ctl)
अणु
	u32 pwm_width = axi_ioपढ़ो(ADI_REG_PWM_WIDTH, ctl);
	u32 pwm_period = axi_ioपढ़ो(ADI_REG_PWM_PERIOD, ctl);
	/*
	 * PWM_PERIOD is a RO रेजिस्टर set by the core. It should never be 0.
	 * For now we are trusting the HW...
	 */
	वापस DIV_ROUND_CLOSEST(pwm_width * SYSFS_PWM_MAX, pwm_period);
पूर्ण

अटल पूर्णांक axi_fan_control_set_pwm_duty(स्थिर दीर्घ val,
					काष्ठा axi_fan_control_data *ctl)
अणु
	u32 pwm_period = axi_ioपढ़ो(ADI_REG_PWM_PERIOD, ctl);
	u32 new_width;
	दीर्घ __val = clamp_val(val, 0, SYSFS_PWM_MAX);

	new_width = DIV_ROUND_CLOSEST(__val * pwm_period, SYSFS_PWM_MAX);

	axi_ioग_लिखो(new_width, ADI_REG_PWM_WIDTH, ctl);

	वापस 0;
पूर्ण

अटल दीर्घ axi_fan_control_get_fan_rpm(स्थिर काष्ठा axi_fan_control_data *ctl)
अणु
	स्थिर u32 tach = axi_ioपढ़ो(ADI_REG_TACH_MEASUR, ctl);

	अगर (tach == 0)
		/* should we वापस error, EAGAIN maybe? */
		वापस 0;
	/*
	 * The tacho period should be:
	 *      TACH = 60/(ppr * rpm), where rpm is revolutions per second
	 *      and ppr is pulses per revolution.
	 * Given the tacho period, we can multiply it by the input घड़ी
	 * so that we know how many घड़ीs we need to have this period.
	 * From this, we can derive the RPM value.
	 */
	वापस DIV_ROUND_CLOSEST(60 * ctl->clk_rate, ctl->ppr * tach);
पूर्ण

अटल पूर्णांक axi_fan_control_पढ़ो_temp(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा axi_fan_control_data *ctl = dev_get_drvdata(dev);
	दीर्घ raw_temp;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		raw_temp = axi_ioपढ़ो(ADI_REG_TEMPERATURE, ctl);
		/*
		 * The क्रमmula क्रम the temperature is:
		 *      T = (ADC * 501.3743 / 2^bits) - 273.6777
		 * It's multiplied by 1000 to have millidegrees as
		 * specअगरied by the hwmon sysfs पूर्णांकerface.
		 */
		*val = ((raw_temp * 501374) >> 16) - 273677;
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_पढ़ो_fan(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा axi_fan_control_data *ctl = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_fan_fault:
		*val = ctl->fan_fault;
		/* clear it now */
		ctl->fan_fault = 0;
		वापस 0;
	हाल hwmon_fan_input:
		*val = axi_fan_control_get_fan_rpm(ctl);
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_पढ़ो_pwm(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा axi_fan_control_data *ctl = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		*val = axi_fan_control_get_pwm_duty(ctl);
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_ग_लिखो_pwm(काष्ठा device *dev, u32 attr, दीर्घ val)
अणु
	काष्ठा axi_fan_control_data *ctl = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		वापस axi_fan_control_set_pwm_duty(val, ctl);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_पढ़ो_labels(काष्ठा device *dev,
				       क्रमागत hwmon_sensor_types type,
				       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		*str = "FAN";
		वापस 0;
	हाल hwmon_temp:
		*str = "SYSMON4";
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_पढ़ो(काष्ठा device *dev,
				क्रमागत hwmon_sensor_types type,
				u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		वापस axi_fan_control_पढ़ो_fan(dev, attr, val);
	हाल hwmon_pwm:
		वापस axi_fan_control_पढ़ो_pwm(dev, attr, val);
	हाल hwmon_temp:
		वापस axi_fan_control_पढ़ो_temp(dev, attr, val);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक axi_fan_control_ग_लिखो(काष्ठा device *dev,
				 क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_pwm:
		वापस axi_fan_control_ग_लिखो_pwm(dev, attr, val);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t axi_fan_control_fan_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_fan_input:
	हाल hwmon_fan_fault:
	हाल hwmon_fan_label:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t axi_fan_control_pwm_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_pwm_input:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t axi_fan_control_temp_is_visible(स्थिर u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_label:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t axi_fan_control_is_visible(स्थिर व्योम *data,
					  क्रमागत hwmon_sensor_types type,
					  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		वापस axi_fan_control_fan_is_visible(attr);
	हाल hwmon_pwm:
		वापस axi_fan_control_pwm_is_visible(attr);
	हाल hwmon_temp:
		वापस axi_fan_control_temp_is_visible(attr);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * This core has two मुख्य ways of changing the PWM duty cycle. It is करोne,
 * either by a request from userspace (writing on pwm1_input) or by the
 * core itself. When the change is करोne by the core, it will use predefined
 * parameters to evaluate the tach संकेत and, on that हाल we cannot set them.
 * On the other hand, when the request is करोne by the user, with some arbitrary
 * value that the core करोes not now about, we have to provide the tach
 * parameters so that, the core can evaluate the संकेत. On the IRQ handler we
 * distinguish this by using the ADI_IRQ_SRC_TEMP_INCREASE पूर्णांकerrupt. This tell
 * us that the CORE requested a new duty cycle. After this, there is 5s delay
 * on which the core रुकोs क्रम the fan rotation speed to stabilize. After this
 * we get ADI_IRQ_SRC_PWM_CHANGED irq where we will decide अगर we need to set
 * the tach parameters or not on the next tach measurement cycle (corresponding
 * alपढ़ोy to the ney duty cycle) based on the %ctl->hw_pwm_req flag.
 */
अटल irqवापस_t axi_fan_control_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा axi_fan_control_data *ctl = (काष्ठा axi_fan_control_data *)data;
	u32 irq_pending = axi_ioपढ़ो(ADI_REG_IRQ_PENDING, ctl);
	u32 clear_mask;

	अगर (irq_pending & ADI_IRQ_SRC_NEW_MEASUR) अणु
		अगर (ctl->update_tacho_params) अणु
			u32 new_tach = axi_ioपढ़ो(ADI_REG_TACH_MEASUR, ctl);

			/* get 25% tolerance */
			u32 tach_tol = DIV_ROUND_CLOSEST(new_tach * 25, 100);
			/* set new tacho parameters */
			axi_ioग_लिखो(new_tach, ADI_REG_TACH_PERIOD, ctl);
			axi_ioग_लिखो(tach_tol, ADI_REG_TACH_TOLERANCE, ctl);
			ctl->update_tacho_params = false;
		पूर्ण
	पूर्ण

	अगर (irq_pending & ADI_IRQ_SRC_PWM_CHANGED) अणु
		/*
		 * अगर the pwm changes on behalf of software,
		 * we need to provide new tacho parameters to the core.
		 * Wait क्रम the next measurement क्रम that...
		 */
		अगर (!ctl->hw_pwm_req) अणु
			ctl->update_tacho_params = true;
		पूर्ण अन्यथा अणु
			ctl->hw_pwm_req = false;
			sysfs_notअगरy(&ctl->hdev->kobj, शून्य, "pwm1");
		पूर्ण
	पूर्ण

	अगर (irq_pending & ADI_IRQ_SRC_TEMP_INCREASE)
		/* hardware requested a new pwm */
		ctl->hw_pwm_req = true;

	अगर (irq_pending & ADI_IRQ_SRC_TACH_ERR)
		ctl->fan_fault = 1;

	/* clear all पूर्णांकerrupts */
	clear_mask = irq_pending & ADI_IRQ_SRC_MASK;
	axi_ioग_लिखो(clear_mask, ADI_REG_IRQ_PENDING, ctl);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक axi_fan_control_init(काष्ठा axi_fan_control_data *ctl,
				स्थिर काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	/* get fan pulses per revolution */
	ret = of_property_पढ़ो_u32(np, "pulses-per-revolution", &ctl->ppr);
	अगर (ret)
		वापस ret;

	/* 1, 2 and 4 are the typical and accepted values */
	अगर (ctl->ppr != 1 && ctl->ppr != 2 && ctl->ppr != 4)
		वापस -EINVAL;
	/*
	 * Enable all IRQs
	 */
	axi_ioग_लिखो(ADI_IRQ_MASK_OUT_ALL &
		    ~(ADI_IRQ_SRC_NEW_MEASUR | ADI_IRQ_SRC_TACH_ERR |
		      ADI_IRQ_SRC_PWM_CHANGED | ADI_IRQ_SRC_TEMP_INCREASE),
		    ADI_REG_IRQ_MASK, ctl);

	/* bring the device out of reset */
	axi_ioग_लिखो(0x01, ADI_REG_RSTN, ctl);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *axi_fan_control_info[] = अणु
	HWMON_CHANNEL_INFO(pwm, HWMON_PWM_INPUT),
	HWMON_CHANNEL_INFO(fan, HWMON_F_INPUT | HWMON_F_FAULT | HWMON_F_LABEL),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT | HWMON_T_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops axi_fan_control_hwmon_ops = अणु
	.is_visible = axi_fan_control_is_visible,
	.पढ़ो = axi_fan_control_पढ़ो,
	.ग_लिखो = axi_fan_control_ग_लिखो,
	.पढ़ो_string = axi_fan_control_पढ़ो_labels,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info axi_chip_info = अणु
	.ops = &axi_fan_control_hwmon_ops,
	.info = axi_fan_control_info,
पूर्ण;

अटल स्थिर u32 version_1_0_0 = ADI_AXI_PCORE_VER(1, 0, 'a');

अटल स्थिर काष्ठा of_device_id axi_fan_control_of_match[] = अणु
	अणु .compatible = "adi,axi-fan-control-1.00.a",
		.data = (व्योम *)&version_1_0_0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axi_fan_control_of_match);

अटल पूर्णांक axi_fan_control_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_fan_control_data *ctl;
	काष्ठा clk *clk;
	स्थिर काष्ठा of_device_id *id;
	स्थिर अक्षर *name = "axi_fan_control";
	u32 version;
	पूर्णांक ret;

	id = of_match_node(axi_fan_control_of_match, pdev->dev.of_node);
	अगर (!id)
		वापस -EINVAL;

	ctl = devm_kzalloc(&pdev->dev, माप(*ctl), GFP_KERNEL);
	अगर (!ctl)
		वापस -ENOMEM;

	ctl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctl->base))
		वापस PTR_ERR(ctl->base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "clk_get failed with %ld\n", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	ctl->clk_rate = clk_get_rate(clk);
	अगर (!ctl->clk_rate)
		वापस -EINVAL;

	version = axi_ioपढ़ो(ADI_AXI_REG_VERSION, ctl);
	अगर (ADI_AXI_PCORE_VER_MAJOR(version) !=
	    ADI_AXI_PCORE_VER_MAJOR((*(u32 *)id->data))) अणु
		dev_err(&pdev->dev, "Major version mismatch. Expected %d.%.2d.%c, Reported %d.%.2d.%c\n",
			ADI_AXI_PCORE_VER_MAJOR((*(u32 *)id->data)),
			ADI_AXI_PCORE_VER_MINOR((*(u32 *)id->data)),
			ADI_AXI_PCORE_VER_PATCH((*(u32 *)id->data)),
			ADI_AXI_PCORE_VER_MAJOR(version),
			ADI_AXI_PCORE_VER_MINOR(version),
			ADI_AXI_PCORE_VER_PATCH(version));
		वापस -ENODEV;
	पूर्ण

	ctl->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ctl->irq < 0)
		वापस ctl->irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, ctl->irq, शून्य,
					axi_fan_control_irq_handler,
					IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
					pdev->driver_override, ctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request an irq, %d", ret);
		वापस ret;
	पूर्ण

	ret = axi_fan_control_init(ctl, pdev->dev.of_node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize device\n");
		वापस ret;
	पूर्ण

	ctl->hdev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
							 name,
							 ctl,
							 &axi_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(ctl->hdev);
पूर्ण

अटल काष्ठा platक्रमm_driver axi_fan_control_driver = अणु
	.driver = अणु
		.name = "axi_fan_control_driver",
		.of_match_table = axi_fan_control_of_match,
	पूर्ण,
	.probe = axi_fan_control_probe,
पूर्ण;
module_platक्रमm_driver(axi_fan_control_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("Analog Devices Fan Control HDL CORE driver");
MODULE_LICENSE("GPL");
