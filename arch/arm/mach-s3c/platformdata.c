<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2010 Ben Dooks <ben-linux <at> fluff.org>
//
// Helper क्रम platक्रमm data setting

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "devs.h"
#समावेश "sdhci.h"

व्योम __init *s3c_set_platdata(व्योम *pd, माप_प्रकार pdsize,
			      काष्ठा platक्रमm_device *pdev)
अणु
	व्योम *npd;

	अगर (!pd) अणु
		/* too early to use dev_name(), may not be रेजिस्टरed */
		prपूर्णांकk(KERN_ERR "%s: no platform data supplied\n", pdev->name);
		वापस शून्य;
	पूर्ण

	npd = kmemdup(pd, pdsize, GFP_KERNEL);
	अगर (!npd)
		वापस शून्य;

	pdev->dev.platक्रमm_data = npd;
	वापस npd;
पूर्ण

व्योम s3c_sdhci_set_platdata(काष्ठा s3c_sdhci_platdata *pd,
			     काष्ठा s3c_sdhci_platdata *set)
अणु
	set->cd_type = pd->cd_type;
	set->ext_cd_init = pd->ext_cd_init;
	set->ext_cd_cleanup = pd->ext_cd_cleanup;
	set->ext_cd_gpio = pd->ext_cd_gpio;
	set->ext_cd_gpio_invert = pd->ext_cd_gpio_invert;

	अगर (pd->max_width)
		set->max_width = pd->max_width;
	अगर (pd->cfg_gpio)
		set->cfg_gpio = pd->cfg_gpio;
	अगर (pd->host_caps)
		set->host_caps |= pd->host_caps;
	अगर (pd->host_caps2)
		set->host_caps2 |= pd->host_caps2;
	अगर (pd->pm_caps)
		set->pm_caps |= pd->pm_caps;
पूर्ण
