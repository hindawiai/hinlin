<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC subप्रणाली, nvmem पूर्णांकerface
 *
 * Copyright (C) 2017 Alexandre Belloni
 */

#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/rtc.h>

पूर्णांक devm_rtc_nvmem_रेजिस्टर(काष्ठा rtc_device *rtc,
		       काष्ठा nvmem_config *nvmem_config)
अणु
	काष्ठा device *dev = rtc->dev.parent;
	काष्ठा nvmem_device *nvmem;

	अगर (!nvmem_config)
		वापस -ENODEV;

	nvmem_config->dev = dev;
	nvmem_config->owner = rtc->owner;
	nvmem = devm_nvmem_रेजिस्टर(dev, nvmem_config);
	अगर (IS_ERR(nvmem))
		dev_err(dev, "failed to register nvmem device for RTC\n");

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण
EXPORT_SYMBOL_GPL(devm_rtc_nvmem_रेजिस्टर);
