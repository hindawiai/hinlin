<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Low-Power Timer Trigger driver
 *
 * Copyright (C) STMicroelectronics 2017
 *
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 *
 * Inspired by Benjamin Gaignard's sपंचांग32-समयr-trigger driver
 */

#समावेश <linux/iio/समयr/sपंचांग32-lptim-trigger.h>
#समावेश <linux/mfd/sपंचांग32-lpसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

/* List Low-Power Timer triggers */
अटल स्थिर अक्षर * स्थिर sपंचांग32_lptim_triggers[] = अणु
	LPTIM1_OUT,
	LPTIM2_OUT,
	LPTIM3_OUT,
पूर्ण;

काष्ठा sपंचांग32_lptim_trigger अणु
	काष्ठा device *dev;
	स्थिर अक्षर *trg;
पूर्ण;

अटल पूर्णांक sपंचांग32_lptim_validate_device(काष्ठा iio_trigger *trig,
				       काष्ठा iio_dev *indio_dev)
अणु
	अगर (indio_dev->modes & INDIO_HARDWARE_TRIGGERED)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops sपंचांग32_lptim_trigger_ops = अणु
	.validate_device = sपंचांग32_lptim_validate_device,
पूर्ण;

/**
 * is_sपंचांग32_lptim_trigger
 * @trig: trigger to be checked
 *
 * वापस true अगर the trigger is a valid STM32 IIO Low-Power Timer Trigger
 * either वापस false
 */
bool is_sपंचांग32_lptim_trigger(काष्ठा iio_trigger *trig)
अणु
	वापस (trig->ops == &sपंचांग32_lptim_trigger_ops);
पूर्ण
EXPORT_SYMBOL(is_sपंचांग32_lptim_trigger);

अटल पूर्णांक sपंचांग32_lptim_setup_trig(काष्ठा sपंचांग32_lptim_trigger *priv)
अणु
	काष्ठा iio_trigger *trig;

	trig = devm_iio_trigger_alloc(priv->dev, "%s", priv->trg);
	अगर  (!trig)
		वापस -ENOMEM;

	trig->dev.parent = priv->dev->parent;
	trig->ops = &sपंचांग32_lptim_trigger_ops;
	iio_trigger_set_drvdata(trig, priv);

	वापस devm_iio_trigger_रेजिस्टर(priv->dev, trig);
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_trigger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_lptim_trigger *priv;
	u32 index;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "reg", &index))
		वापस -EINVAL;

	अगर (index >= ARRAY_SIZE(sपंचांग32_lptim_triggers))
		वापस -EINVAL;

	priv->dev = &pdev->dev;
	priv->trg = sपंचांग32_lptim_triggers[index];

	ret = sपंचांग32_lptim_setup_trig(priv);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_lptim_trig_of_match[] = अणु
	अणु .compatible = "st,stm32-lptimer-trigger", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_lptim_trig_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_lptim_trigger_driver = अणु
	.probe = sपंचांग32_lptim_trigger_probe,
	.driver = अणु
		.name = "stm32-lptimer-trigger",
		.of_match_table = sपंचांग32_lptim_trig_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_lptim_trigger_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_ALIAS("platform:stm32-lptimer-trigger");
MODULE_DESCRIPTION("STMicroelectronics STM32 LPTIM trigger driver");
MODULE_LICENSE("GPL v2");
