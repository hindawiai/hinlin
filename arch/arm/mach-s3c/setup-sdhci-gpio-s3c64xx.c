<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C64XX - Helper functions क्रम setting up SDHCI device(s) GPIO (HSMMC)

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>

#समावेश "gpio-cfg.h"
#समावेश "sdhci.h"
#समावेश "gpio-samsung.h"

व्योम s3c64xx_setup_sdhci0_cfg_gpio(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	काष्ठा s3c_sdhci_platdata *pdata = dev->dev.platक्रमm_data;

	/* Set all the necessary GPG pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPG(0), 2 + width, S3C_GPIO_SFN(2));

	अगर (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) अणु
		s3c_gpio_setpull(S3C64XX_GPG(6), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S3C64XX_GPG(6), S3C_GPIO_SFN(2));
	पूर्ण
पूर्ण

व्योम s3c64xx_setup_sdhci1_cfg_gpio(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	काष्ठा s3c_sdhci_platdata *pdata = dev->dev.platक्रमm_data;

	/* Set all the necessary GPH pins to special-function 2 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPH(0), 2 + width, S3C_GPIO_SFN(2));

	अगर (pdata->cd_type == S3C_SDHCI_CD_INTERNAL) अणु
		s3c_gpio_setpull(S3C64XX_GPG(6), S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(S3C64XX_GPG(6), S3C_GPIO_SFN(3));
	पूर्ण
पूर्ण

व्योम s3c64xx_setup_sdhci2_cfg_gpio(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	/* Set all the necessary GPH pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPH(6), width, S3C_GPIO_SFN(3));

	/* Set all the necessary GPC pins to special-function 3 */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPC(4), 2, S3C_GPIO_SFN(3));
पूर्ण
