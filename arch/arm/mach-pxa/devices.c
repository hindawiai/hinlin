<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/usb-pxa3xx-ulpi.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <mach/irqs.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/platक्रमm_data/media/camera-pxa.h>
#समावेश <mach/audपन.स>
#समावेश <mach/hardware.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

#समावेश "devices.h"
#समावेश "generic.h"

व्योम __init pxa_रेजिस्टर_device(काष्ठा platक्रमm_device *dev, व्योम *data)
अणु
	पूर्णांक ret;

	dev->dev.platक्रमm_data = data;

	ret = platक्रमm_device_रेजिस्टर(dev);
	अगर (ret)
		dev_err(&dev->dev, "unable to register device: %d\n", ret);
पूर्ण

अटल काष्ठा resource pxa_resource_pmu = अणु
	.start	= IRQ_PMU,
	.end	= IRQ_PMU,
	.flags	= IORESOURCE_IRQ,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_pmu = अणु
	.name		= "xscale-pmu",
	.id		= -1,
	.resource	= &pxa_resource_pmu,
	.num_resources	= 1,
पूर्ण;

अटल काष्ठा resource pxamci_resources[] = अणु
	[0] = अणु
		.start	= 0x41100000,
		.end	= 0x41100fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_MMC,
		.end	= IRQ_MMC,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxamci_dmamask = 0xffffffffUL;

काष्ठा platक्रमm_device pxa_device_mci = अणु
	.name		= "pxa2xx-mci",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &pxamci_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxamci_resources),
	.resource	= pxamci_resources,
पूर्ण;

व्योम __init pxa_set_mci_info(काष्ठा pxamci_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_mci, info);
पूर्ण


अटल काष्ठा pxa2xx_udc_mach_info pxa_udc_info = अणु
	.gpio_pullup = -1,
पूर्ण;

व्योम __init pxa_set_udc_info(काष्ठा pxa2xx_udc_mach_info *info)
अणु
	स_नकल(&pxa_udc_info, info, माप *info);
पूर्ण

अटल काष्ठा resource pxa2xx_udc_resources[] = अणु
	[0] = अणु
		.start	= 0x40600000,
		.end	= 0x4060ffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_USB,
		.end	= IRQ_USB,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 udc_dma_mask = ~(u32)0;

काष्ठा platक्रमm_device pxa25x_device_udc = अणु
	.name		= "pxa25x-udc",
	.id		= -1,
	.resource	= pxa2xx_udc_resources,
	.num_resources	= ARRAY_SIZE(pxa2xx_udc_resources),
	.dev		=  अणु
		.platक्रमm_data	= &pxa_udc_info,
		.dma_mask	= &udc_dma_mask,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_udc = अणु
	.name		= "pxa27x-udc",
	.id		= -1,
	.resource	= pxa2xx_udc_resources,
	.num_resources	= ARRAY_SIZE(pxa2xx_udc_resources),
	.dev		=  अणु
		.platक्रमm_data	= &pxa_udc_info,
		.dma_mask	= &udc_dma_mask,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PXA3xx
अटल काष्ठा resource pxa3xx_u2d_resources[] = अणु
	[0] = अणु
		.start	= 0x54100000,
		.end	= 0x54100fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_USB2,
		.end	= IRQ_USB2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_u2d = अणु
	.name		= "pxa3xx-u2d",
	.id		= -1,
	.resource	= pxa3xx_u2d_resources,
	.num_resources	= ARRAY_SIZE(pxa3xx_u2d_resources),
पूर्ण;

व्योम __init pxa3xx_set_u2d_info(काष्ठा pxa3xx_u2d_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa3xx_device_u2d, info);
पूर्ण
#पूर्ण_अगर /* CONFIG_PXA3xx */

अटल काष्ठा resource pxafb_resources[] = अणु
	[0] = अणु
		.start	= 0x44000000,
		.end	= 0x4400ffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_LCD,
		.end	= IRQ_LCD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 fb_dma_mask = ~(u64)0;

काष्ठा platक्रमm_device pxa_device_fb = अणु
	.name		= "pxa2xx-fb",
	.id		= -1,
	.dev		= अणु
		.dma_mask	= &fb_dma_mask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxafb_resources),
	.resource	= pxafb_resources,
पूर्ण;

व्योम __init pxa_set_fb_info(काष्ठा device *parent, काष्ठा pxafb_mach_info *info)
अणु
	pxa_device_fb.dev.parent = parent;
	pxa_रेजिस्टर_device(&pxa_device_fb, info);
पूर्ण

अटल काष्ठा resource pxa_resource_ffuart[] = अणु
	अणु
		.start	= 0x40100000,
		.end	= 0x40100023,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_FFUART,
		.end	= IRQ_FFUART,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa_device_ffuart = अणु
	.name		= "pxa2xx-uart",
	.id		= 0,
	.resource	= pxa_resource_ffuart,
	.num_resources	= ARRAY_SIZE(pxa_resource_ffuart),
पूर्ण;

व्योम __init pxa_set_ffuart_info(व्योम *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_ffuart, info);
पूर्ण

अटल काष्ठा resource pxa_resource_btuart[] = अणु
	अणु
		.start	= 0x40200000,
		.end	= 0x40200023,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_BTUART,
		.end	= IRQ_BTUART,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa_device_btuart = अणु
	.name		= "pxa2xx-uart",
	.id		= 1,
	.resource	= pxa_resource_btuart,
	.num_resources	= ARRAY_SIZE(pxa_resource_btuart),
पूर्ण;

व्योम __init pxa_set_btuart_info(व्योम *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_btuart, info);
पूर्ण

अटल काष्ठा resource pxa_resource_stuart[] = अणु
	अणु
		.start	= 0x40700000,
		.end	= 0x40700023,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_STUART,
		.end	= IRQ_STUART,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa_device_stuart = अणु
	.name		= "pxa2xx-uart",
	.id		= 2,
	.resource	= pxa_resource_stuart,
	.num_resources	= ARRAY_SIZE(pxa_resource_stuart),
पूर्ण;

व्योम __init pxa_set_stuart_info(व्योम *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_stuart, info);
पूर्ण

अटल काष्ठा resource pxa_resource_hwuart[] = अणु
	अणु
		.start	= 0x41600000,
		.end	= 0x4160002F,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_HWUART,
		.end	= IRQ_HWUART,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa_device_hwuart = अणु
	.name		= "pxa2xx-uart",
	.id		= 3,
	.resource	= pxa_resource_hwuart,
	.num_resources	= ARRAY_SIZE(pxa_resource_hwuart),
पूर्ण;

व्योम __init pxa_set_hwuart_info(व्योम *info)
अणु
	अगर (cpu_is_pxa255())
		pxa_रेजिस्टर_device(&pxa_device_hwuart, info);
	अन्यथा
		pr_info("UART: Ignoring attempt to register HWUART on non-PXA255 hardware");
पूर्ण

अटल काष्ठा resource pxai2c_resources[] = अणु
	अणु
		.start	= 0x40301680,
		.end	= 0x403016a3,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_I2C,
		.end	= IRQ_I2C,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_i2c = अणु
	.name		= "pxa2xx-i2c",
	.id		= 0,
	.resource	= pxai2c_resources,
	.num_resources	= ARRAY_SIZE(pxai2c_resources),
पूर्ण;

व्योम __init pxa_set_i2c_info(काष्ठा i2c_pxa_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_i2c, info);
पूर्ण

#अगर_घोषित CONFIG_PXA27x
अटल काष्ठा resource pxa27x_resources_i2c_घातer[] = अणु
	अणु
		.start	= 0x40f00180,
		.end	= 0x40f001a3,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_PWRI2C,
		.end	= IRQ_PWRI2C,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_i2c_घातer = अणु
	.name		= "pxa2xx-i2c",
	.id		= 1,
	.resource	= pxa27x_resources_i2c_घातer,
	.num_resources	= ARRAY_SIZE(pxa27x_resources_i2c_घातer),
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा resource pxai2s_resources[] = अणु
	अणु
		.start	= 0x40400000,
		.end	= 0x40400083,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_I2S,
		.end	= IRQ_I2S,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_i2s = अणु
	.name		= "pxa2xx-i2s",
	.id		= -1,
	.resource	= pxai2s_resources,
	.num_resources	= ARRAY_SIZE(pxai2s_resources),
पूर्ण;

काष्ठा platक्रमm_device pxa_device_asoc_ssp1 = अणु
	.name		= "pxa-ssp-dai",
	.id		= 0,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_asoc_ssp2= अणु
	.name		= "pxa-ssp-dai",
	.id		= 1,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_asoc_ssp3 = अणु
	.name		= "pxa-ssp-dai",
	.id		= 2,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_asoc_ssp4 = अणु
	.name		= "pxa-ssp-dai",
	.id		= 3,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_asoc_platक्रमm = अणु
	.name		= "pxa-pcm-audio",
	.id		= -1,
पूर्ण;

अटल u64 pxaficp_dmamask = ~(u32)0;

अटल काष्ठा resource pxa_ir_resources[] = अणु
	[0] = अणु
		.start  = IRQ_STUART,
		.end    = IRQ_STUART,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_ICP,
		.end    = IRQ_ICP,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[3] = अणु
		.start  = 0x40800000,
		.end	= 0x4080001b,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[4] = अणु
		.start  = 0x40700000,
		.end	= 0x40700023,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_ficp = अणु
	.name		= "pxa2xx-ir",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa_ir_resources),
	.resource	= pxa_ir_resources,
	.dev		= अणु
		.dma_mask = &pxaficp_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
पूर्ण;

व्योम __init pxa_set_ficp_info(काष्ठा pxaficp_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa_device_ficp, info);
पूर्ण

अटल काष्ठा resource pxa_rtc_resources[] = अणु
	[0] = अणु
		.start  = 0x40900000,
		.end	= 0x40900000 + 0x3b,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_RTC1Hz,
		.end    = IRQ_RTC1Hz,
		.name	= "rtc 1Hz",
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start  = IRQ_RTCAlrm,
		.end    = IRQ_RTCAlrm,
		.name	= "rtc alarm",
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa_device_rtc = अणु
	.name		= "pxa-rtc",
	.id		= -1,
	.num_resources  = ARRAY_SIZE(pxa_rtc_resources),
	.resource       = pxa_rtc_resources,
पूर्ण;

काष्ठा platक्रमm_device sa1100_device_rtc = अणु
	.name		= "sa1100-rtc",
	.id		= -1,
	.num_resources  = ARRAY_SIZE(pxa_rtc_resources),
	.resource       = pxa_rtc_resources,
पूर्ण;

अटल काष्ठा resource pxa_ac97_resources[] = अणु
	[0] = अणु
		.start  = 0x40500000,
		.end	= 0x40500000 + 0xfff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_AC97,
		.end    = IRQ_AC97,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxa_ac97_dmamask = 0xffffffffUL;

काष्ठा platक्रमm_device pxa_device_ac97 = अणु
	.name           = "pxa2xx-ac97",
	.id             = -1,
	.dev            = अणु
		.dma_mask = &pxa_ac97_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(pxa_ac97_resources),
	.resource       = pxa_ac97_resources,
पूर्ण;

व्योम __init pxa_set_ac97_info(pxa2xx_audio_ops_t *ops)
अणु
	पूर्णांक ret;

	ret = clk_add_alias("ac97_clk", "pxa2xx-ac97:0", "AC97CLK",
			   &pxa_device_ac97.dev);
	अगर (ret)
		pr_err("PXA AC97 clock1 alias error: %d\n", ret);

	ret = clk_add_alias("ac97_clk", "pxa2xx-ac97:1", "AC97CLK",
			    &pxa_device_ac97.dev);
	अगर (ret)
		pr_err("PXA AC97 clock2 alias error: %d\n", ret);

	pxa_रेजिस्टर_device(&pxa_device_ac97, ops);
पूर्ण

#अगर_घोषित CONFIG_PXA25x

अटल काष्ठा resource pxa25x_resource_pwm0[] = अणु
	[0] = अणु
		.start	= 0x40b00000,
		.end	= 0x40b0000f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_pwm0 = अणु
	.name		= "pxa25x-pwm",
	.id		= 0,
	.resource	= pxa25x_resource_pwm0,
	.num_resources	= ARRAY_SIZE(pxa25x_resource_pwm0),
पूर्ण;

अटल काष्ठा resource pxa25x_resource_pwm1[] = अणु
	[0] = अणु
		.start	= 0x40c00000,
		.end	= 0x40c0000f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_pwm1 = अणु
	.name		= "pxa25x-pwm",
	.id		= 1,
	.resource	= pxa25x_resource_pwm1,
	.num_resources	= ARRAY_SIZE(pxa25x_resource_pwm1),
पूर्ण;

अटल u64 pxa25x_ssp_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa25x_resource_ssp[] = अणु
	[0] = अणु
		.start	= 0x41000000,
		.end	= 0x4100001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SSP,
		.end	= IRQ_SSP,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_ssp = अणु
	.name		= "pxa25x-ssp",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &pxa25x_ssp_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa25x_resource_ssp,
	.num_resources	= ARRAY_SIZE(pxa25x_resource_ssp),
पूर्ण;

अटल u64 pxa25x_nssp_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa25x_resource_nssp[] = अणु
	[0] = अणु
		.start	= 0x41400000,
		.end	= 0x4140002f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_NSSP,
		.end	= IRQ_NSSP,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_nssp = अणु
	.name		= "pxa25x-nssp",
	.id		= 1,
	.dev		= अणु
		.dma_mask = &pxa25x_nssp_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa25x_resource_nssp,
	.num_resources	= ARRAY_SIZE(pxa25x_resource_nssp),
पूर्ण;

अटल u64 pxa25x_assp_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa25x_resource_assp[] = अणु
	[0] = अणु
		.start	= 0x41500000,
		.end	= 0x4150002f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_ASSP,
		.end	= IRQ_ASSP,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_assp = अणु
	/* ASSP is basically equivalent to NSSP */
	.name		= "pxa25x-nssp",
	.id		= 2,
	.dev		= अणु
		.dma_mask = &pxa25x_assp_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa25x_resource_assp,
	.num_resources	= ARRAY_SIZE(pxa25x_resource_assp),
पूर्ण;
#पूर्ण_अगर /* CONFIG_PXA25x */

#अगर defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
अटल काष्ठा resource pxa27x_resource_camera[] = अणु
	[0] = अणु
		.start	= 0x50000000,
		.end	= 0x50000fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_CAMERA,
		.end	= IRQ_CAMERA,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxa27x_dma_mask_camera = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device pxa27x_device_camera = अणु
	.name		= "pxa27x-camera",
	.id		= 0, /* This is used to put cameras on this पूर्णांकerface */
	.dev		= अणु
		.dma_mask      		= &pxa27x_dma_mask_camera,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_camera),
	.resource	= pxa27x_resource_camera,
पूर्ण;

व्योम __init pxa_set_camera_info(काष्ठा pxacamera_platक्रमm_data *info)
अणु
	काष्ठा clk *mclk;

	/* Register a fixed-rate घड़ी क्रम camera sensors. */
	mclk = clk_रेजिस्टर_fixed_rate(शून्य, "pxa_camera_clk", शून्य, 0,
					     info->mclk_10khz * 10000);
	अगर (!IS_ERR(mclk))
		clkdev_create(mclk, "mclk", शून्य);
	pxa_रेजिस्टर_device(&pxa27x_device_camera, info);
पूर्ण

अटल u64 pxa27x_ohci_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa27x_resource_ohci[] = अणु
	[0] = अणु
		.start  = 0x4C000000,
		.end    = 0x4C00ff6f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ_USBH1,
		.end    = IRQ_USBH1,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_ohci = अणु
	.name		= "pxa27x-ohci",
	.id		= -1,
	.dev		= अणु
		.dma_mask = &pxa27x_ohci_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources  = ARRAY_SIZE(pxa27x_resource_ohci),
	.resource       = pxa27x_resource_ohci,
पूर्ण;

व्योम __init pxa_set_ohci_info(काष्ठा pxaohci_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa27x_device_ohci, info);
पूर्ण
#पूर्ण_अगर /* CONFIG_PXA27x || CONFIG_PXA3xx */

#अगर defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
अटल काष्ठा resource pxa27x_resource_keypad[] = अणु
	[0] = अणु
		.start	= 0x41500000,
		.end	= 0x4150004c,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_KEYPAD,
		.end	= IRQ_KEYPAD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_keypad = अणु
	.name		= "pxa27x-keypad",
	.id		= -1,
	.resource	= pxa27x_resource_keypad,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_keypad),
पूर्ण;

व्योम __init pxa_set_keypad_info(काष्ठा pxa27x_keypad_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa27x_device_keypad, info);
पूर्ण

अटल u64 pxa27x_ssp1_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa27x_resource_ssp1[] = अणु
	[0] = अणु
		.start	= 0x41000000,
		.end	= 0x4100003f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SSP,
		.end	= IRQ_SSP,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_ssp1 = अणु
	.name		= "pxa27x-ssp",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp1_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp1,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp1),
पूर्ण;

अटल u64 pxa27x_ssp2_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa27x_resource_ssp2[] = अणु
	[0] = अणु
		.start	= 0x41700000,
		.end	= 0x4170003f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SSP2,
		.end	= IRQ_SSP2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_ssp2 = अणु
	.name		= "pxa27x-ssp",
	.id		= 1,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp2_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp2,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp2),
पूर्ण;

अटल u64 pxa27x_ssp3_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa27x_resource_ssp3[] = अणु
	[0] = अणु
		.start	= 0x41900000,
		.end	= 0x4190003f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SSP3,
		.end	= IRQ_SSP3,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_ssp3 = अणु
	.name		= "pxa27x-ssp",
	.id		= 2,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp3_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp3,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp3),
पूर्ण;

अटल काष्ठा resource pxa27x_resource_pwm0[] = अणु
	[0] = अणु
		.start	= 0x40b00000,
		.end	= 0x40b0001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_pwm0 = अणु
	.name		= "pxa27x-pwm",
	.id		= 0,
	.resource	= pxa27x_resource_pwm0,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_pwm0),
पूर्ण;

अटल काष्ठा resource pxa27x_resource_pwm1[] = अणु
	[0] = अणु
		.start	= 0x40c00000,
		.end	= 0x40c0001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_pwm1 = अणु
	.name		= "pxa27x-pwm",
	.id		= 1,
	.resource	= pxa27x_resource_pwm1,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_pwm1),
पूर्ण;
#पूर्ण_अगर /* CONFIG_PXA27x || CONFIG_PXA3xx */

#अगर_घोषित CONFIG_PXA3xx
अटल काष्ठा resource pxa3xx_resources_mci2[] = अणु
	[0] = अणु
		.start	= 0x42000000,
		.end	= 0x42000fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_MMC2,
		.end	= IRQ_MMC2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_mci2 = अणु
	.name		= "pxa2xx-mci",
	.id		= 1,
	.dev		= अणु
		.dma_mask = &pxamci_dmamask,
		.coherent_dma_mask =	0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxa3xx_resources_mci2),
	.resource	= pxa3xx_resources_mci2,
पूर्ण;

व्योम __init pxa3xx_set_mci2_info(काष्ठा pxamci_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa3xx_device_mci2, info);
पूर्ण

अटल काष्ठा resource pxa3xx_resources_mci3[] = अणु
	[0] = अणु
		.start	= 0x42500000,
		.end	= 0x42500fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_MMC3,
		.end	= IRQ_MMC3,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_mci3 = अणु
	.name		= "pxa2xx-mci",
	.id		= 2,
	.dev		= अणु
		.dma_mask = &pxamci_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxa3xx_resources_mci3),
	.resource	= pxa3xx_resources_mci3,
पूर्ण;

व्योम __init pxa3xx_set_mci3_info(काष्ठा pxamci_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa3xx_device_mci3, info);
पूर्ण

अटल काष्ठा resource pxa3xx_resources_gcu[] = अणु
	अणु
		.start	= 0x54000000,
		.end	= 0x54000fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_GCU,
		.end	= IRQ_GCU,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxa3xx_gcu_dmamask = DMA_BIT_MASK(32);

काष्ठा platक्रमm_device pxa3xx_device_gcu = अणु
	.name		= "pxa3xx-gcu",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa3xx_resources_gcu),
	.resource	= pxa3xx_resources_gcu,
	.dev		= अणु
		.dma_mask = &pxa3xx_gcu_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* CONFIG_PXA3xx */

#अगर defined(CONFIG_PXA3xx)
अटल काष्ठा resource pxa3xx_resources_i2c_घातer[] = अणु
	अणु
		.start  = 0x40f500c0,
		.end    = 0x40f500d3,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_PWRI2C,
		.end	= IRQ_PWRI2C,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_i2c_घातer = अणु
	.name		= "pxa3xx-pwri2c",
	.id		= 1,
	.resource	= pxa3xx_resources_i2c_घातer,
	.num_resources	= ARRAY_SIZE(pxa3xx_resources_i2c_घातer),
पूर्ण;

अटल काष्ठा resource pxa3xx_resources_nand[] = अणु
	[0] = अणु
		.start	= 0x43100000,
		.end	= 0x43100053,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_न_अंकD,
		.end	= IRQ_न_अंकD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxa3xx_nand_dma_mask = DMA_BIT_MASK(32);

काष्ठा platक्रमm_device pxa3xx_device_nand = अणु
	.name		= "pxa3xx-nand",
	.id		= -1,
	.dev		= अणु
		.dma_mask = &pxa3xx_nand_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxa3xx_resources_nand),
	.resource	= pxa3xx_resources_nand,
पूर्ण;

व्योम __init pxa3xx_set_nand_info(काष्ठा pxa3xx_nand_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa3xx_device_nand, info);
पूर्ण

अटल u64 pxa3xx_ssp4_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource pxa3xx_resource_ssp4[] = अणु
	[0] = अणु
		.start	= 0x41a00000,
		.end	= 0x41a0003f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SSP4,
		.end	= IRQ_SSP4,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/*
 * PXA3xx SSP is basically equivalent to PXA27x.
 * However, we need to रेजिस्टर the device by the correct name in order to
 * make the driver set the correct पूर्णांकernal type, hence we provide specअगरic
 * platक्रमm_devices क्रम each of them.
 */
काष्ठा platक्रमm_device pxa3xx_device_ssp1 = अणु
	.name		= "pxa3xx-ssp",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp1_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp1,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp1),
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_ssp2 = अणु
	.name		= "pxa3xx-ssp",
	.id		= 1,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp2_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp2,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp2),
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_ssp3 = अणु
	.name		= "pxa3xx-ssp",
	.id		= 2,
	.dev		= अणु
		.dma_mask = &pxa27x_ssp3_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa27x_resource_ssp3,
	.num_resources	= ARRAY_SIZE(pxa27x_resource_ssp3),
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_ssp4 = अणु
	.name		= "pxa3xx-ssp",
	.id		= 3,
	.dev		= अणु
		.dma_mask = &pxa3xx_ssp4_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= pxa3xx_resource_ssp4,
	.num_resources	= ARRAY_SIZE(pxa3xx_resource_ssp4),
पूर्ण;
#पूर्ण_अगर /* CONFIG_PXA3xx */

काष्ठा resource pxa_resource_gpio[] = अणु
	अणु
		.start	= 0x40e00000,
		.end	= 0x40e0ffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= IRQ_GPIO0,
		.end	= IRQ_GPIO0,
		.name	= "gpio0",
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.start	= IRQ_GPIO1,
		.end	= IRQ_GPIO1,
		.name	= "gpio1",
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.start	= IRQ_GPIO_2_x,
		.end	= IRQ_GPIO_2_x,
		.name	= "gpio_mux",
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device pxa25x_device_gpio = अणु
#अगर_घोषित CONFIG_CPU_PXA26x
	.name		= "pxa26x-gpio",
#अन्यथा
	.name		= "pxa25x-gpio",
#पूर्ण_अगर
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa_resource_gpio),
	.resource	= pxa_resource_gpio,
पूर्ण;

काष्ठा platक्रमm_device pxa27x_device_gpio = अणु
	.name		= "pxa27x-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa_resource_gpio),
	.resource	= pxa_resource_gpio,
पूर्ण;

काष्ठा platक्रमm_device pxa3xx_device_gpio = अणु
	.name		= "pxa3xx-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa_resource_gpio),
	.resource	= pxa_resource_gpio,
पूर्ण;

काष्ठा platक्रमm_device pxa93x_device_gpio = अणु
	.name		= "pxa93x-gpio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pxa_resource_gpio),
	.resource	= pxa_resource_gpio,
पूर्ण;

/* pxa2xx-spi platक्रमm-device ID equals respective SSP platक्रमm-device ID + 1.
 * See comment in arch/arm/mach-pxa/ssp.c::ssp_probe() */
व्योम __init pxa2xx_set_spi_info(अचिन्हित id, काष्ठा pxa2xx_spi_controller *info)
अणु
	काष्ठा platक्रमm_device *pd;

	pd = platक्रमm_device_alloc("pxa2xx-spi", id);
	अगर (pd == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pxa2xx-spi: failed to allocate device id %d\n",
		       id);
		वापस;
	पूर्ण

	pd->dev.platक्रमm_data = info;
	platक्रमm_device_add(pd);
पूर्ण

अटल काष्ठा resource pxa_dma_resource[] = अणु
	[0] = अणु
		.start	= 0x40000000,
		.end	= 0x4000ffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_DMA,
		.end	= IRQ_DMA,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 pxadma_dmamask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device pxa2xx_pxa_dma = अणु
	.name		= "pxa-dma",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &pxadma_dmamask,
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(pxa_dma_resource),
	.resource	= pxa_dma_resource,
पूर्ण;

व्योम __init pxa2xx_set_dmac_info(काष्ठा mmp_dma_platdata *dma_pdata)
अणु
	pxa_रेजिस्टर_device(&pxa2xx_pxa_dma, dma_pdata);
पूर्ण
