<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the enhanced rotary controller on pxa930 and pxa935
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/keyboard-pxa930_rotary.h>

#घोषणा SBCR	(0x04)
#घोषणा ERCR	(0x0c)

#घोषणा SBCR_ERSB	(1 << 5)

काष्ठा pxa930_rotary अणु
	काष्ठा input_dev	*input_dev;
	व्योम __iomem		*mmio_base;
	पूर्णांक			last_ercr;

	काष्ठा pxa930_rotary_platक्रमm_data *pdata;
पूर्ण;

अटल व्योम clear_sbcr(काष्ठा pxa930_rotary *r)
अणु
	uपूर्णांक32_t sbcr = __raw_पढ़ोl(r->mmio_base + SBCR);

	__raw_ग_लिखोl(sbcr | SBCR_ERSB, r->mmio_base + SBCR);
	__raw_ग_लिखोl(sbcr & ~SBCR_ERSB, r->mmio_base + SBCR);
पूर्ण

अटल irqवापस_t rotary_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxa930_rotary *r = dev_id;
	काष्ठा pxa930_rotary_platक्रमm_data *pdata = r->pdata;
	पूर्णांक ercr, delta, key;

	ercr = __raw_पढ़ोl(r->mmio_base + ERCR) & 0xf;
	clear_sbcr(r);

	delta = ercr - r->last_ercr;
	अगर (delta == 0)
		वापस IRQ_HANDLED;

	r->last_ercr = ercr;

	अगर (pdata->up_key && pdata->करोwn_key) अणु
		key = (delta > 0) ? pdata->up_key : pdata->करोwn_key;
		input_report_key(r->input_dev, key, 1);
		input_sync(r->input_dev);
		input_report_key(r->input_dev, key, 0);
	पूर्ण अन्यथा
		input_report_rel(r->input_dev, pdata->rel_code, delta);

	input_sync(r->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pxa930_rotary_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa930_rotary *r = input_get_drvdata(dev);

	clear_sbcr(r);

	वापस 0;
पूर्ण

अटल व्योम pxa930_rotary_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa930_rotary *r = input_get_drvdata(dev);

	clear_sbcr(r);
पूर्ण

अटल पूर्णांक pxa930_rotary_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa930_rotary_platक्रमm_data *pdata =
			dev_get_platdata(&pdev->dev);
	काष्ठा pxa930_rotary *r;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no I/O memory defined\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		वापस -EINVAL;
	पूर्ण

	r = kzalloc(माप(काष्ठा pxa930_rotary), GFP_KERNEL);
	अगर (!r)
		वापस -ENOMEM;

	r->mmio_base = ioremap(res->start, resource_size(res));
	अगर (r->mmio_base == शून्य) अणु
		dev_err(&pdev->dev, "failed to remap IO memory\n");
		err = -ENXIO;
		जाओ failed_मुक्त;
	पूर्ण

	r->pdata = pdata;
	platक्रमm_set_drvdata(pdev, r);

	/* allocate and रेजिस्टर the input device */
	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		err = -ENOMEM;
		जाओ failed_मुक्त_io;
	पूर्ण

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->खोलो = pxa930_rotary_खोलो;
	input_dev->बंद = pxa930_rotary_बंद;
	input_dev->dev.parent = &pdev->dev;

	अगर (pdata->up_key && pdata->करोwn_key) अणु
		__set_bit(pdata->up_key, input_dev->keybit);
		__set_bit(pdata->करोwn_key, input_dev->keybit);
		__set_bit(EV_KEY, input_dev->evbit);
	पूर्ण अन्यथा अणु
		__set_bit(pdata->rel_code, input_dev->relbit);
		__set_bit(EV_REL, input_dev->evbit);
	पूर्ण

	r->input_dev = input_dev;
	input_set_drvdata(input_dev, r);

	err = request_irq(irq, rotary_irq, 0,
			"enhanced rotary", r);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		जाओ failed_मुक्त_input;
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		जाओ failed_मुक्त_irq;
	पूर्ण

	वापस 0;

failed_मुक्त_irq:
	मुक्त_irq(irq, r);
failed_मुक्त_input:
	input_मुक्त_device(input_dev);
failed_मुक्त_io:
	iounmap(r->mmio_base);
failed_मुक्त:
	kमुक्त(r);
	वापस err;
पूर्ण

अटल पूर्णांक pxa930_rotary_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa930_rotary *r = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(platक्रमm_get_irq(pdev, 0), r);
	input_unरेजिस्टर_device(r->input_dev);
	iounmap(r->mmio_base);
	kमुक्त(r);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa930_rotary_driver = अणु
	.driver		= अणु
		.name	= "pxa930-rotary",
	पूर्ण,
	.probe		= pxa930_rotary_probe,
	.हटाओ		= pxa930_rotary_हटाओ,
पूर्ण;
module_platक्रमm_driver(pxa930_rotary_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for PXA93x Enhanced Rotary Controller");
MODULE_AUTHOR("Yao Yong <yaoyong@marvell.com>");
