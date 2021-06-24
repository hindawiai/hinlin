<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2009 Wolfson Microelectronics
//      Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/export.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"

#समावेश "devs.h"
#समावेश <linux/platक्रमm_data/asoc-s3c.h>
#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

अटल पूर्णांक s3c64xx_i2s_cfg_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक base;

	चयन (pdev->id) अणु
	हाल 0:
		base = S3C64XX_GPD(0);
		अवरोध;
	हाल 1:
		base = S3C64XX_GPE(0);
		अवरोध;
	हाल 2:
		s3c_gpio_cfgpin(S3C64XX_GPC(4), S3C_GPIO_SFN(5));
		s3c_gpio_cfgpin(S3C64XX_GPC(5), S3C_GPIO_SFN(5));
		s3c_gpio_cfgpin(S3C64XX_GPC(7), S3C_GPIO_SFN(5));
		s3c_gpio_cfgpin_range(S3C64XX_GPH(6), 4, S3C_GPIO_SFN(5));
		वापस 0;
	शेष:
		prपूर्णांकk(KERN_DEBUG "Invalid I2S Controller number: %d\n",
			pdev->id);
		वापस -EINVAL;
	पूर्ण

	s3c_gpio_cfgpin_range(base, 5, S3C_GPIO_SFN(3));

	वापस 0;
पूर्ण

अटल काष्ठा resource s3c64xx_iis0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_IIS0, SZ_256),
पूर्ण;

अटल काष्ठा s3c_audio_pdata i2s0_pdata = अणु
	.cfg_gpio = s3c64xx_i2s_cfg_gpio,
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_iis0 = अणु
	.name		  = "samsung-i2s",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s3c64xx_iis0_resource),
	.resource	  = s3c64xx_iis0_resource,
	.dev = अणु
		.platक्रमm_data = &i2s0_pdata,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_iis0);

अटल काष्ठा resource s3c64xx_iis1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_IIS1, SZ_256),
पूर्ण;

अटल काष्ठा s3c_audio_pdata i2s1_pdata = अणु
	.cfg_gpio = s3c64xx_i2s_cfg_gpio,
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_iis1 = अणु
	.name		  = "samsung-i2s",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s3c64xx_iis1_resource),
	.resource	  = s3c64xx_iis1_resource,
	.dev = अणु
		.platक्रमm_data = &i2s1_pdata,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_iis1);

अटल काष्ठा resource s3c64xx_iisv4_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_IISV4, SZ_256),
पूर्ण;

अटल काष्ठा s3c_audio_pdata i2sv4_pdata = अणु
	.cfg_gpio = s3c64xx_i2s_cfg_gpio,
	.type = अणु
		.quirks = QUIRK_PRI_6CHAN,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_iisv4 = अणु
	.name = "samsung-i2s",
	.id = 2,
	.num_resources	  = ARRAY_SIZE(s3c64xx_iisv4_resource),
	.resource	  = s3c64xx_iisv4_resource,
	.dev = अणु
		.platक्रमm_data = &i2sv4_pdata,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_iisv4);


/* PCM Controller platक्रमm_devices */

अटल पूर्णांक s3c64xx_pcm_cfg_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक base;

	चयन (pdev->id) अणु
	हाल 0:
		base = S3C64XX_GPD(0);
		अवरोध;
	हाल 1:
		base = S3C64XX_GPE(0);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "Invalid PCM Controller number: %d\n",
			pdev->id);
		वापस -EINVAL;
	पूर्ण

	s3c_gpio_cfgpin_range(base, 5, S3C_GPIO_SFN(2));
	वापस 0;
पूर्ण

अटल काष्ठा resource s3c64xx_pcm0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_PCM0, SZ_256),
पूर्ण;

अटल काष्ठा s3c_audio_pdata s3c_pcm0_pdata = अणु
	.cfg_gpio = s3c64xx_pcm_cfg_gpio,
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_pcm0 = अणु
	.name		  = "samsung-pcm",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s3c64xx_pcm0_resource),
	.resource	  = s3c64xx_pcm0_resource,
	.dev = अणु
		.platक्रमm_data = &s3c_pcm0_pdata,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_pcm0);

अटल काष्ठा resource s3c64xx_pcm1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_PCM1, SZ_256),
पूर्ण;

अटल काष्ठा s3c_audio_pdata s3c_pcm1_pdata = अणु
	.cfg_gpio = s3c64xx_pcm_cfg_gpio,
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_pcm1 = अणु
	.name		  = "samsung-pcm",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s3c64xx_pcm1_resource),
	.resource	  = s3c64xx_pcm1_resource,
	.dev = अणु
		.platक्रमm_data = &s3c_pcm1_pdata,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_pcm1);

/* AC97 Controller platक्रमm devices */

अटल पूर्णांक s3c64xx_ac97_cfg_gpd(काष्ठा platक्रमm_device *pdev)
अणु
	वापस s3c_gpio_cfgpin_range(S3C64XX_GPD(0), 5, S3C_GPIO_SFN(4));
पूर्ण

अटल पूर्णांक s3c64xx_ac97_cfg_gpe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस s3c_gpio_cfgpin_range(S3C64XX_GPE(0), 5, S3C_GPIO_SFN(4));
पूर्ण

अटल काष्ठा resource s3c64xx_ac97_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_AC97, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_AC97),
पूर्ण;

अटल काष्ठा s3c_audio_pdata s3c_ac97_pdata = अणु
पूर्ण;

अटल u64 s3c64xx_ac97_dmamask = DMA_BIT_MASK(32);

काष्ठा platक्रमm_device s3c64xx_device_ac97 = अणु
	.name		  = "samsung-ac97",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3c64xx_ac97_resource),
	.resource	  = s3c64xx_ac97_resource,
	.dev = अणु
		.platक्रमm_data = &s3c_ac97_pdata,
		.dma_mask = &s3c64xx_ac97_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL(s3c64xx_device_ac97);

व्योम __init s3c64xx_ac97_setup_gpio(पूर्णांक num)
अणु
	अगर (num == S3C64XX_AC97_GPD)
		s3c_ac97_pdata.cfg_gpio = s3c64xx_ac97_cfg_gpd;
	अन्यथा
		s3c_ac97_pdata.cfg_gpio = s3c64xx_ac97_cfg_gpe;
पूर्ण
