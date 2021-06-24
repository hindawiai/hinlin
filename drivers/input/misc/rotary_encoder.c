<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rotary_encoder.c
 *
 * (c) 2009 Daniel Mack <daniel@caiaq.de>
 * Copyright (C) 2011 Johan Hovold <jhovold@gmail.com>
 *
 * state machine code inspired by code from Tim Ruetz
 *
 * A generic driver क्रम rotary encoders connected to GPIO lines.
 * See file:Documentation/input/devices/rotary-encoder.rst क्रम more inक्रमmation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/property.h>

#घोषणा DRV_NAME "rotary-encoder"

क्रमागत rotary_encoder_encoding अणु
	ROTENC_GRAY,
	ROTENC_BINARY,
पूर्ण;

काष्ठा rotary_encoder अणु
	काष्ठा input_dev *input;

	काष्ठा mutex access_mutex;

	u32 steps;
	u32 axis;
	bool relative_axis;
	bool rollover;
	क्रमागत rotary_encoder_encoding encoding;

	अचिन्हित पूर्णांक pos;

	काष्ठा gpio_descs *gpios;

	अचिन्हित पूर्णांक *irq;

	bool armed;
	चिन्हित अक्षर dir;	/* 1 - घड़ीwise, -1 - CCW */

	अचिन्हित पूर्णांक last_stable;
पूर्ण;

अटल अचिन्हित पूर्णांक rotary_encoder_get_state(काष्ठा rotary_encoder *encoder)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक ret = 0;

	क्रम (i = 0; i < encoder->gpios->ndescs; ++i) अणु
		पूर्णांक val = gpiod_get_value_cansleep(encoder->gpios->desc[i]);

		/* convert from gray encoding to normal */
		अगर (encoder->encoding == ROTENC_GRAY && ret & 1)
			val = !val;

		ret = ret << 1 | val;
	पूर्ण

	वापस ret & 3;
पूर्ण

अटल व्योम rotary_encoder_report_event(काष्ठा rotary_encoder *encoder)
अणु
	अगर (encoder->relative_axis) अणु
		input_report_rel(encoder->input,
				 encoder->axis, encoder->dir);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pos = encoder->pos;

		अगर (encoder->dir < 0) अणु
			/* turning counter-घड़ीwise */
			अगर (encoder->rollover)
				pos += encoder->steps;
			अगर (pos)
				pos--;
		पूर्ण अन्यथा अणु
			/* turning घड़ीwise */
			अगर (encoder->rollover || pos < encoder->steps)
				pos++;
		पूर्ण

		अगर (encoder->rollover)
			pos %= encoder->steps;

		encoder->pos = pos;
		input_report_असल(encoder->input, encoder->axis, encoder->pos);
	पूर्ण

	input_sync(encoder->input);
पूर्ण

अटल irqवापस_t rotary_encoder_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rotary_encoder *encoder = dev_id;
	अचिन्हित पूर्णांक state;

	mutex_lock(&encoder->access_mutex);

	state = rotary_encoder_get_state(encoder);

	चयन (state) अणु
	हाल 0x0:
		अगर (encoder->armed) अणु
			rotary_encoder_report_event(encoder);
			encoder->armed = false;
		पूर्ण
		अवरोध;

	हाल 0x1:
	हाल 0x3:
		अगर (encoder->armed)
			encoder->dir = 2 - state;
		अवरोध;

	हाल 0x2:
		encoder->armed = true;
		अवरोध;
	पूर्ण

	mutex_unlock(&encoder->access_mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rotary_encoder_half_period_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rotary_encoder *encoder = dev_id;
	अचिन्हित पूर्णांक state;

	mutex_lock(&encoder->access_mutex);

	state = rotary_encoder_get_state(encoder);

	अगर (state & 1) अणु
		encoder->dir = ((encoder->last_stable - state + 1) % 4) - 1;
	पूर्ण अन्यथा अणु
		अगर (state != encoder->last_stable) अणु
			rotary_encoder_report_event(encoder);
			encoder->last_stable = state;
		पूर्ण
	पूर्ण

	mutex_unlock(&encoder->access_mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rotary_encoder_quarter_period_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rotary_encoder *encoder = dev_id;
	अचिन्हित पूर्णांक state;

	mutex_lock(&encoder->access_mutex);

	state = rotary_encoder_get_state(encoder);

	अगर ((encoder->last_stable + 1) % 4 == state)
		encoder->dir = 1;
	अन्यथा अगर (encoder->last_stable == (state + 1) % 4)
		encoder->dir = -1;
	अन्यथा
		जाओ out;

	rotary_encoder_report_event(encoder);

out:
	encoder->last_stable = state;
	mutex_unlock(&encoder->access_mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rotary_encoder_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rotary_encoder *encoder;
	काष्ठा input_dev *input;
	irq_handler_t handler;
	u32 steps_per_period;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	encoder = devm_kzalloc(dev, माप(काष्ठा rotary_encoder), GFP_KERNEL);
	अगर (!encoder)
		वापस -ENOMEM;

	mutex_init(&encoder->access_mutex);

	device_property_पढ़ो_u32(dev, "rotary-encoder,steps", &encoder->steps);

	err = device_property_पढ़ो_u32(dev, "rotary-encoder,steps-per-period",
				       &steps_per_period);
	अगर (err) अणु
		/*
		 * The 'half-period' property has been deprecated, you must
		 * use 'steps-per-period' and set an appropriate value, but
		 * we still need to parse it to मुख्यtain compatibility. If
		 * neither property is present we fall back to the one step
		 * per period behavior.
		 */
		steps_per_period = device_property_पढ़ो_bool(dev,
					"rotary-encoder,half-period") ? 2 : 1;
	पूर्ण

	encoder->rollover =
		device_property_पढ़ो_bool(dev, "rotary-encoder,rollover");

	अगर (!device_property_present(dev, "rotary-encoder,encoding") ||
	    !device_property_match_string(dev, "rotary-encoder,encoding",
					  "gray")) अणु
		dev_info(dev, "gray");
		encoder->encoding = ROTENC_GRAY;
	पूर्ण अन्यथा अगर (!device_property_match_string(dev, "rotary-encoder,encoding",
						 "binary")) अणु
		dev_info(dev, "binary");
		encoder->encoding = ROTENC_BINARY;
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown encoding setting\n");
		वापस -EINVAL;
	पूर्ण

	device_property_पढ़ो_u32(dev, "linux,axis", &encoder->axis);
	encoder->relative_axis =
		device_property_पढ़ो_bool(dev, "rotary-encoder,relative-axis");

	encoder->gpios = devm_gpiod_get_array(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(encoder->gpios)) अणु
		err = PTR_ERR(encoder->gpios);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "unable to get gpios: %d\n", err);
		वापस err;
	पूर्ण
	अगर (encoder->gpios->ndescs < 2) अणु
		dev_err(dev, "not enough gpios found\n");
		वापस -EINVAL;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	encoder->input = input;

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->dev.parent = dev;

	अगर (encoder->relative_axis)
		input_set_capability(input, EV_REL, encoder->axis);
	अन्यथा
		input_set_असल_params(input,
				     encoder->axis, 0, encoder->steps, 0, 1);

	चयन (steps_per_period >> (encoder->gpios->ndescs - 2)) अणु
	हाल 4:
		handler = &rotary_encoder_quarter_period_irq;
		encoder->last_stable = rotary_encoder_get_state(encoder);
		अवरोध;
	हाल 2:
		handler = &rotary_encoder_half_period_irq;
		encoder->last_stable = rotary_encoder_get_state(encoder);
		अवरोध;
	हाल 1:
		handler = &rotary_encoder_irq;
		अवरोध;
	शेष:
		dev_err(dev, "'%d' is not a valid steps-per-period value\n",
			steps_per_period);
		वापस -EINVAL;
	पूर्ण

	encoder->irq =
		devm_kसुस्मृति(dev,
			     encoder->gpios->ndescs, माप(*encoder->irq),
			     GFP_KERNEL);
	अगर (!encoder->irq)
		वापस -ENOMEM;

	क्रम (i = 0; i < encoder->gpios->ndescs; ++i) अणु
		encoder->irq[i] = gpiod_to_irq(encoder->gpios->desc[i]);

		err = devm_request_thपढ़ोed_irq(dev, encoder->irq[i],
				शून्य, handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
				IRQF_ONESHOT,
				DRV_NAME, encoder);
		अगर (err) अणु
			dev_err(dev, "unable to request IRQ %d (gpio#%d)\n",
				encoder->irq[i], i);
			वापस err;
		पूर्ण
	पूर्ण

	err = input_रेजिस्टर_device(input);
	अगर (err) अणु
		dev_err(dev, "failed to register input device\n");
		वापस err;
	पूर्ण

	device_init_wakeup(dev,
			   device_property_पढ़ो_bool(dev, "wakeup-source"));

	platक्रमm_set_drvdata(pdev, encoder);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rotary_encoder_suspend(काष्ठा device *dev)
अणु
	काष्ठा rotary_encoder *encoder = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	अगर (device_may_wakeup(dev)) अणु
		क्रम (i = 0; i < encoder->gpios->ndescs; ++i)
			enable_irq_wake(encoder->irq[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rotary_encoder_resume(काष्ठा device *dev)
अणु
	काष्ठा rotary_encoder *encoder = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	अगर (device_may_wakeup(dev)) अणु
		क्रम (i = 0; i < encoder->gpios->ndescs; ++i)
			disable_irq_wake(encoder->irq[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rotary_encoder_pm_ops,
			 rotary_encoder_suspend, rotary_encoder_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rotary_encoder_of_match[] = अणु
	अणु .compatible = "rotary-encoder", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rotary_encoder_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rotary_encoder_driver = अणु
	.probe		= rotary_encoder_probe,
	.driver		= अणु
		.name	= DRV_NAME,
		.pm	= &rotary_encoder_pm_ops,
		.of_match_table = of_match_ptr(rotary_encoder_of_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(rotary_encoder_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DESCRIPTION("GPIO rotary encoder driver");
MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>, Johan Hovold");
MODULE_LICENSE("GPL v2");
