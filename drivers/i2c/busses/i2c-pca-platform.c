<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  i2c_pca_platक्रमm.c
 *
 *  Platक्रमm driver क्रम the PCA9564 I2C controller.
 *
 *  Copyright (C) 2008 Pengutronix
 *

 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c-algo-pca.h>
#समावेश <linux/platक्रमm_data/i2c-pca-platक्रमm.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/irq.h>

काष्ठा i2c_pca_pf_data अणु
	व्योम __iomem			*reg_base;
	पूर्णांक				irq;	/* अगर 0, use polling */
	काष्ठा gpio_desc		*gpio;
	रुको_queue_head_t		रुको;
	काष्ठा i2c_adapter		adap;
	काष्ठा i2c_algo_pca_data	algo_data;
पूर्ण;

/* Read/Write functions क्रम dअगरferent रेजिस्टर alignments */

अटल पूर्णांक i2c_pca_pf_पढ़ोbyte8(व्योम *pd, पूर्णांक reg)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	वापस ioपढ़ो8(i2c->reg_base + reg);
पूर्ण

अटल पूर्णांक i2c_pca_pf_पढ़ोbyte16(व्योम *pd, पूर्णांक reg)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	वापस ioपढ़ो8(i2c->reg_base + reg * 2);
पूर्ण

अटल पूर्णांक i2c_pca_pf_पढ़ोbyte32(व्योम *pd, पूर्णांक reg)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	वापस ioपढ़ो8(i2c->reg_base + reg * 4);
पूर्ण

अटल व्योम i2c_pca_pf_ग_लिखोbyte8(व्योम *pd, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	ioग_लिखो8(val, i2c->reg_base + reg);
पूर्ण

अटल व्योम i2c_pca_pf_ग_लिखोbyte16(व्योम *pd, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	ioग_लिखो8(val, i2c->reg_base + reg * 2);
पूर्ण

अटल व्योम i2c_pca_pf_ग_लिखोbyte32(व्योम *pd, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	ioग_लिखो8(val, i2c->reg_base + reg * 4);
पूर्ण


अटल पूर्णांक i2c_pca_pf_रुकोक्रमcompletion(व्योम *pd)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;
	अचिन्हित दीर्घ समयout;
	दीर्घ ret;

	अगर (i2c->irq) अणु
		ret = रुको_event_समयout(i2c->रुको,
			i2c->algo_data.पढ़ो_byte(i2c, I2C_PCA_CON)
			& I2C_PCA_CON_SI, i2c->adap.समयout);
	पूर्ण अन्यथा अणु
		/* Do polling */
		समयout = jअगरfies + i2c->adap.समयout;
		करो अणु
			ret = समय_beक्रमe(jअगरfies, समयout);
			अगर (i2c->algo_data.पढ़ो_byte(i2c, I2C_PCA_CON)
					& I2C_PCA_CON_SI)
				अवरोध;
			udelay(100);
		पूर्ण जबतक (ret);
	पूर्ण

	वापस ret > 0;
पूर्ण

अटल व्योम i2c_pca_pf_dummyreset(व्योम *pd)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;

	dev_warn(&i2c->adap.dev, "No reset-pin found. Chip may get stuck!\n");
पूर्ण

अटल व्योम i2c_pca_pf_resetchip(व्योम *pd)
अणु
	काष्ठा i2c_pca_pf_data *i2c = pd;

	gpiod_set_value(i2c->gpio, 1);
	ndelay(100);
	gpiod_set_value(i2c->gpio, 0);
पूर्ण

अटल irqवापस_t i2c_pca_pf_handler(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा i2c_pca_pf_data *i2c = dev_id;

	अगर ((i2c->algo_data.पढ़ो_byte(i2c, I2C_PCA_CON) & I2C_PCA_CON_SI) == 0)
		वापस IRQ_NONE;

	wake_up(&i2c->रुको);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक i2c_pca_pf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_pca_pf_data *i2c;
	काष्ठा resource *res;
	काष्ठा i2c_pca9564_pf_platक्रमm_data *platक्रमm_data =
				dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret = 0;
	पूर्णांक irq;

	irq = platक्रमm_get_irq_optional(pdev, 0);
	/* If irq is 0, we करो polling. */
	अगर (irq < 0)
		irq = 0;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->reg_base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(i2c->reg_base))
		वापस PTR_ERR(i2c->reg_base);


	init_रुकोqueue_head(&i2c->रुको);

	i2c->irq = irq;

	i2c->adap.nr = pdev->id;
	i2c->adap.owner = THIS_MODULE;
	snम_लिखो(i2c->adap.name, माप(i2c->adap.name),
		 "PCA9564/PCA9665 at 0x%08lx",
		 (अचिन्हित दीर्घ) res->start);
	i2c->adap.algo_data = &i2c->algo_data;
	i2c->adap.dev.parent = &pdev->dev;
	i2c->adap.dev.of_node = np;

	i2c->gpio = devm_gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(i2c->gpio))
		वापस PTR_ERR(i2c->gpio);

	i2c->adap.समयout = HZ;
	ret = device_property_पढ़ो_u32(&pdev->dev, "clock-frequency",
				       &i2c->algo_data.i2c_घड़ी);
	अगर (ret)
		i2c->algo_data.i2c_घड़ी = 59000;

	अगर (platक्रमm_data) अणु
		i2c->adap.समयout = platक्रमm_data->समयout;
		i2c->algo_data.i2c_घड़ी = platक्रमm_data->i2c_घड़ी_speed;
	पूर्ण

	i2c->algo_data.data = i2c;
	i2c->algo_data.रुको_क्रम_completion = i2c_pca_pf_रुकोक्रमcompletion;
	अगर (i2c->gpio)
		i2c->algo_data.reset_chip = i2c_pca_pf_resetchip;
	अन्यथा
		i2c->algo_data.reset_chip = i2c_pca_pf_dummyreset;

	चयन (res->flags & IORESOURCE_MEM_TYPE_MASK) अणु
	हाल IORESOURCE_MEM_32BIT:
		i2c->algo_data.ग_लिखो_byte = i2c_pca_pf_ग_लिखोbyte32;
		i2c->algo_data.पढ़ो_byte = i2c_pca_pf_पढ़ोbyte32;
		अवरोध;
	हाल IORESOURCE_MEM_16BIT:
		i2c->algo_data.ग_लिखो_byte = i2c_pca_pf_ग_लिखोbyte16;
		i2c->algo_data.पढ़ो_byte = i2c_pca_pf_पढ़ोbyte16;
		अवरोध;
	हाल IORESOURCE_MEM_8BIT:
	शेष:
		i2c->algo_data.ग_लिखो_byte = i2c_pca_pf_ग_लिखोbyte8;
		i2c->algo_data.पढ़ो_byte = i2c_pca_pf_पढ़ोbyte8;
		अवरोध;
	पूर्ण

	अगर (irq) अणु
		ret = devm_request_irq(&pdev->dev, irq, i2c_pca_pf_handler,
			IRQF_TRIGGER_FALLING, pdev->name, i2c);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = i2c_pca_add_numbered_bus(&i2c->adap);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, i2c);

	dev_info(&pdev->dev, "registered.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_pca_pf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_pca_pf_data *i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id i2c_pca_of_match_table[] = अणु
	अणु .compatible = "nxp,pca9564" पूर्ण,
	अणु .compatible = "nxp,pca9665" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_pca_of_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver i2c_pca_pf_driver = अणु
	.probe = i2c_pca_pf_probe,
	.हटाओ = i2c_pca_pf_हटाओ,
	.driver = अणु
		.name = "i2c-pca-platform",
		.of_match_table = of_match_ptr(i2c_pca_of_match_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(i2c_pca_pf_driver);

MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("I2C-PCA9564/PCA9665 platform driver");
MODULE_LICENSE("GPL");
