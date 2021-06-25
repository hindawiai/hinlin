<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core functions क्रम:
 *  Philips UCB1400 multअगरunction chip
 *
 * Based on ucb1400_ts.c:
 *  Author:	Nicolas Pitre
 *  Created:	September 25, 2006
 *  Copyright:	MontaVista Software, Inc.
 *
 * Spliting करोne by: Marek Vasut <marek.vasut@gmail.com>
 * If something करोesn't work and it worked beक्रमe spliting, e-mail me,
 * करोnt bother Nicolas please ;-)
 *
 * This code is heavily based on ucb1x00-*.c copyrighted by Russell King
 * covering the UCB1100, UCB1200 and UCB1300..  Support क्रम the UCB1400 has
 * been made separate from ucb1x00-core/ucb1x00-ts on Russell's request.
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/ucb1400.h>

अचिन्हित पूर्णांक ucb1400_adc_पढ़ो(काष्ठा snd_ac97 *ac97, u16 adc_channel,
		पूर्णांक adcsync)
अणु
	अचिन्हित पूर्णांक val;

	अगर (adcsync)
		adc_channel |= UCB_ADC_SYNC_ENA;

	ucb1400_reg_ग_लिखो(ac97, UCB_ADC_CR, UCB_ADC_ENA | adc_channel);
	ucb1400_reg_ग_लिखो(ac97, UCB_ADC_CR, UCB_ADC_ENA | adc_channel |
			UCB_ADC_START);

	जबतक (!((val = ucb1400_reg_पढ़ो(ac97, UCB_ADC_DATA))
				& UCB_ADC_DAT_VALID))
		schedule_समयout_unपूर्णांकerruptible(1);

	वापस val & UCB_ADC_DAT_MASK;
पूर्ण
EXPORT_SYMBOL_GPL(ucb1400_adc_पढ़ो);

अटल पूर्णांक ucb1400_core_probe(काष्ठा device *dev)
अणु
	पूर्णांक err;
	काष्ठा ucb1400 *ucb;
	काष्ठा ucb1400_ts ucb_ts;
	काष्ठा ucb1400_gpio ucb_gpio;
	काष्ठा snd_ac97 *ac97;
	काष्ठा ucb1400_pdata *pdata = dev_get_platdata(dev);

	स_रखो(&ucb_ts, 0, माप(ucb_ts));
	स_रखो(&ucb_gpio, 0, माप(ucb_gpio));

	ucb = kzalloc(माप(काष्ठा ucb1400), GFP_KERNEL);
	अगर (!ucb) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	dev_set_drvdata(dev, ucb);

	ac97 = to_ac97_t(dev);

	ucb_ts.id = ucb1400_reg_पढ़ो(ac97, UCB_ID);
	अगर (ucb_ts.id != UCB_ID_1400) अणु
		err = -ENODEV;
		जाओ err0;
	पूर्ण

	/* GPIO */
	ucb_gpio.ac97 = ac97;
	अगर (pdata) अणु
		ucb_gpio.gpio_setup = pdata->gpio_setup;
		ucb_gpio.gpio_tearकरोwn = pdata->gpio_tearकरोwn;
		ucb_gpio.gpio_offset = pdata->gpio_offset;
	पूर्ण
	ucb->ucb1400_gpio = platक्रमm_device_alloc("ucb1400_gpio", -1);
	अगर (!ucb->ucb1400_gpio) अणु
		err = -ENOMEM;
		जाओ err0;
	पूर्ण
	err = platक्रमm_device_add_data(ucb->ucb1400_gpio, &ucb_gpio,
					माप(ucb_gpio));
	अगर (err)
		जाओ err1;
	err = platक्रमm_device_add(ucb->ucb1400_gpio);
	अगर (err)
		जाओ err1;

	/* TOUCHSCREEN */
	ucb_ts.ac97 = ac97;

	अगर (pdata != शून्य && pdata->irq >= 0)
		ucb_ts.irq = pdata->irq;
	अन्यथा
		ucb_ts.irq = -1;

	ucb->ucb1400_ts = platक्रमm_device_alloc("ucb1400_ts", -1);
	अगर (!ucb->ucb1400_ts) अणु
		err = -ENOMEM;
		जाओ err2;
	पूर्ण
	err = platक्रमm_device_add_data(ucb->ucb1400_ts, &ucb_ts,
					माप(ucb_ts));
	अगर (err)
		जाओ err3;
	err = platक्रमm_device_add(ucb->ucb1400_ts);
	अगर (err)
		जाओ err3;

	वापस 0;

err3:
	platक्रमm_device_put(ucb->ucb1400_ts);
err2:
	platक्रमm_device_del(ucb->ucb1400_gpio);
err1:
	platक्रमm_device_put(ucb->ucb1400_gpio);
err0:
	kमुक्त(ucb);
err:
	वापस err;
पूर्ण

अटल पूर्णांक ucb1400_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ucb1400 *ucb = dev_get_drvdata(dev);

	platक्रमm_device_unरेजिस्टर(ucb->ucb1400_ts);
	platक्रमm_device_unरेजिस्टर(ucb->ucb1400_gpio);

	kमुक्त(ucb);
	वापस 0;
पूर्ण

अटल काष्ठा device_driver ucb1400_core_driver = अणु
	.name	= "ucb1400_core",
	.bus	= &ac97_bus_type,
	.probe	= ucb1400_core_probe,
	.हटाओ	= ucb1400_core_हटाओ,
पूर्ण;

अटल पूर्णांक __init ucb1400_core_init(व्योम)
अणु
	वापस driver_रेजिस्टर(&ucb1400_core_driver);
पूर्ण

अटल व्योम __निकास ucb1400_core_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&ucb1400_core_driver);
पूर्ण

module_init(ucb1400_core_init);
module_निकास(ucb1400_core_निकास);

MODULE_DESCRIPTION("Philips UCB1400 driver");
MODULE_LICENSE("GPL");
