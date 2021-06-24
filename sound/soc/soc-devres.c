<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-devres.c  --  ALSA SoC Audio Layer devres functions
//
// Copyright (C) 2013 Linaro Ltd

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

अटल व्योम devm_dai_release(काष्ठा device *dev, व्योम *res)
अणु
	snd_soc_unरेजिस्टर_dai(*(काष्ठा snd_soc_dai **)res);
पूर्ण

/**
 * devm_snd_soc_रेजिस्टर_dai - resource-managed dai registration
 * @dev: Device used to manage component
 * @component: The component the DAIs are रेजिस्टरed क्रम
 * @dai_drv: DAI driver to use क्रम the DAI
 * @legacy_dai_naming: अगर %true, use legacy single-name क्रमmat;
 *	अगर %false, use multiple-name क्रमmat;
 */
काष्ठा snd_soc_dai *devm_snd_soc_रेजिस्टर_dai(काष्ठा device *dev,
					      काष्ठा snd_soc_component *component,
					      काष्ठा snd_soc_dai_driver *dai_drv,
					      bool legacy_dai_naming)
अणु
	काष्ठा snd_soc_dai **ptr;
	काष्ठा snd_soc_dai *dai;

	ptr = devres_alloc(devm_dai_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	dai = snd_soc_रेजिस्टर_dai(component, dai_drv, legacy_dai_naming);
	अगर (dai) अणु
		*ptr = dai;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस dai;
पूर्ण
EXPORT_SYMBOL_GPL(devm_snd_soc_रेजिस्टर_dai);

अटल व्योम devm_component_release(काष्ठा device *dev, व्योम *res)
अणु
	स्थिर काष्ठा snd_soc_component_driver **cmpnt_drv = res;

	snd_soc_unरेजिस्टर_component_by_driver(dev, *cmpnt_drv);
पूर्ण

/**
 * devm_snd_soc_रेजिस्टर_component - resource managed component registration
 * @dev: Device used to manage component
 * @cmpnt_drv: Component driver
 * @dai_drv: DAI driver
 * @num_dai: Number of DAIs to रेजिस्टर
 *
 * Register a component with स्वतःmatic unregistration when the device is
 * unरेजिस्टरed.
 */
पूर्णांक devm_snd_soc_रेजिस्टर_component(काष्ठा device *dev,
			 स्थिर काष्ठा snd_soc_component_driver *cmpnt_drv,
			 काष्ठा snd_soc_dai_driver *dai_drv, पूर्णांक num_dai)
अणु
	स्थिर काष्ठा snd_soc_component_driver **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_component_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = snd_soc_रेजिस्टर_component(dev, cmpnt_drv, dai_drv, num_dai);
	अगर (ret == 0) अणु
		*ptr = cmpnt_drv;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_snd_soc_रेजिस्टर_component);

अटल व्योम devm_card_release(काष्ठा device *dev, व्योम *res)
अणु
	snd_soc_unरेजिस्टर_card(*(काष्ठा snd_soc_card **)res);
पूर्ण

/**
 * devm_snd_soc_रेजिस्टर_card - resource managed card registration
 * @dev: Device used to manage card
 * @card: Card to रेजिस्टर
 *
 * Register a card with स्वतःmatic unregistration when the device is
 * unरेजिस्टरed.
 */
पूर्णांक devm_snd_soc_रेजिस्टर_card(काष्ठा device *dev, काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_card **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_card_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret == 0) अणु
		*ptr = card;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_snd_soc_रेजिस्टर_card);

#अगर_घोषित CONFIG_SND_SOC_GENERIC_DMAENGINE_PCM

अटल व्योम devm_dmaengine_pcm_release(काष्ठा device *dev, व्योम *res)
अणु
	snd_dmaengine_pcm_unरेजिस्टर(*(काष्ठा device **)res);
पूर्ण

/**
 * devm_snd_dmaengine_pcm_रेजिस्टर - resource managed dmaengine PCM registration
 * @dev: The parent device क्रम the PCM device
 * @config: Platक्रमm specअगरic PCM configuration
 * @flags: Platक्रमm specअगरic quirks
 *
 * Register a dmaengine based PCM device with स्वतःmatic unregistration when the
 * device is unरेजिस्टरed.
 */
पूर्णांक devm_snd_dmaengine_pcm_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा snd_dmaengine_pcm_config *config, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_dmaengine_pcm_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = snd_dmaengine_pcm_रेजिस्टर(dev, config, flags);
	अगर (ret == 0) अणु
		*ptr = dev;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_snd_dmaengine_pcm_रेजिस्टर);

#पूर्ण_अगर
