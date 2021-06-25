<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Industrial I/O - generic पूर्णांकerrupt based trigger support
 *
 * Copyright (c) 2008-2013 Jonathan Cameron
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>


काष्ठा iio_पूर्णांकerrupt_trigger_info अणु
	अचिन्हित पूर्णांक irq;
पूर्ण;

अटल irqवापस_t iio_पूर्णांकerrupt_trigger_poll(पूर्णांक irq, व्योम *निजी)
अणु
	iio_trigger_poll(निजी);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops iio_पूर्णांकerrupt_trigger_ops = अणु
पूर्ण;

अटल पूर्णांक iio_पूर्णांकerrupt_trigger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_पूर्णांकerrupt_trigger_info *trig_info;
	काष्ठा iio_trigger *trig;
	अचिन्हित दीर्घ irqflags;
	काष्ठा resource *irq_res;
	पूर्णांक irq, ret = 0;

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	अगर (irq_res == शून्य)
		वापस -ENODEV;

	irqflags = (irq_res->flags & IRQF_TRIGGER_MASK) | IRQF_SHARED;

	irq = irq_res->start;

	trig = iio_trigger_alloc(शून्य, "irqtrig%d", irq);
	अगर (!trig) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण

	trig_info = kzalloc(माप(*trig_info), GFP_KERNEL);
	अगर (!trig_info) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_trigger;
	पूर्ण
	iio_trigger_set_drvdata(trig, trig_info);
	trig_info->irq = irq;
	trig->ops = &iio_पूर्णांकerrupt_trigger_ops;
	ret = request_irq(irq, iio_पूर्णांकerrupt_trigger_poll,
			  irqflags, trig->name, trig);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"request IRQ-%d failed", irq);
		जाओ error_मुक्त_trig_info;
	पूर्ण

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret)
		जाओ error_release_irq;
	platक्रमm_set_drvdata(pdev, trig);

	वापस 0;

/* First clean up the partly allocated trigger */
error_release_irq:
	मुक्त_irq(irq, trig);
error_मुक्त_trig_info:
	kमुक्त(trig_info);
error_मुक्त_trigger:
	iio_trigger_मुक्त(trig);
error_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक iio_पूर्णांकerrupt_trigger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_trigger *trig;
	काष्ठा iio_पूर्णांकerrupt_trigger_info *trig_info;

	trig = platक्रमm_get_drvdata(pdev);
	trig_info = iio_trigger_get_drvdata(trig);
	iio_trigger_unरेजिस्टर(trig);
	मुक्त_irq(trig_info->irq, trig);
	kमुक्त(trig_info);
	iio_trigger_मुक्त(trig);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver iio_पूर्णांकerrupt_trigger_driver = अणु
	.probe = iio_पूर्णांकerrupt_trigger_probe,
	.हटाओ = iio_पूर्णांकerrupt_trigger_हटाओ,
	.driver = अणु
		.name = "iio_interrupt_trigger",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iio_पूर्णांकerrupt_trigger_driver);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Interrupt trigger for the iio subsystem");
MODULE_LICENSE("GPL v2");
