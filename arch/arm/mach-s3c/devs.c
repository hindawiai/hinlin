<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Base Samsung platक्रमm device definitions

#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fb.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sizes.h>
#समावेश <linux/platक्रमm_data/s3c-hsudc.h>
#समावेश <linux/platक्रमm_data/s3c-hsotg.h>
#समावेश <linux/platक्रमm_data/dma-s3c24xx.h>

#समावेश <linux/platक्रमm_data/media/s5p_hdmi.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/irqs.h>
#समावेश "map.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#अगर_घोषित CONFIG_PLAT_S3C24XX
#समावेश "regs-s3c2443-clock.h"
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश <linux/platक्रमm_data/ata-samsung_cf.h>
#समावेश "fb.h"
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <linux/platक्रमm_data/hwmon-s3c.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "keypad.h"
#समावेश <linux/platक्रमm_data/mmc-s3cmci.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश "pwm-core.h"
#समावेश "sdhci.h"
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>
#समावेश <linux/platक्रमm_data/usb-ohci-s3c2410.h>
#समावेश "usb-phy.h"
#समावेश <linux/platक्रमm_data/asoc-s3c.h>
#समावेश <linux/platक्रमm_data/spi-s3c64xx.h>

#घोषणा samsung_device_dma_mask (*((u64[]) अणु DMA_BIT_MASK(32) पूर्ण))

/* AC97 */
#अगर_घोषित CONFIG_CPU_S3C2440
अटल काष्ठा resource s3c_ac97_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2440_PA_AC97, S3C2440_SZ_AC97),
	[1] = DEFINE_RES_IRQ(IRQ_S3C244X_AC97),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_ac97 = अणु
	.name		= "samsung-ac97",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_ac97_resource),
	.resource	= s3c_ac97_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_CPU_S3C2440 */

/* ADC */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_adc_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_ADC, S3C24XX_SZ_ADC),
	[1] = DEFINE_RES_IRQ(IRQ_TC),
	[2] = DEFINE_RES_IRQ(IRQ_ADC),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_adc = अणु
	.name		= "s3c24xx-adc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_adc_resource),
	.resource	= s3c_adc_resource,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

#अगर defined(CONFIG_SAMSUNG_DEV_ADC)
अटल काष्ठा resource s3c_adc_resource[] = अणु
	[0] = DEFINE_RES_MEM(SAMSUNG_PA_ADC, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_ADC),
	[2] = DEFINE_RES_IRQ(IRQ_TC),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_adc = अणु
	.name		= "exynos-adc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_adc_resource),
	.resource	= s3c_adc_resource,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SAMSUNG_DEV_ADC */

/* Camअगर Controller */

#अगर_घोषित CONFIG_CPU_S3C2440
अटल काष्ठा resource s3c_camअगर_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2440_PA_CAMIF, S3C2440_SZ_CAMIF),
	[1] = DEFINE_RES_IRQ(IRQ_S3C2440_CAM_C),
	[2] = DEFINE_RES_IRQ(IRQ_S3C2440_CAM_P),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_camअगर = अणु
	.name		= "s3c2440-camif",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_camअगर_resource),
	.resource	= s3c_camअगर_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_CPU_S3C2440 */

/* FB */

#अगर_घोषित CONFIG_S3C_DEV_FB
अटल काष्ठा resource s3c_fb_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_FB, SZ_16K),
	[1] = DEFINE_RES_IRQ(IRQ_LCD_VSYNC),
	[2] = DEFINE_RES_IRQ(IRQ_LCD_FIFO),
	[3] = DEFINE_RES_IRQ(IRQ_LCD_SYSTEM),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_fb = अणु
	.name		= "s3c-fb",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_fb_resource),
	.resource	= s3c_fb_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init s3c_fb_set_platdata(काष्ठा s3c_fb_platdata *pd)
अणु
	s3c_set_platdata(pd, माप(काष्ठा s3c_fb_platdata),
			 &s3c_device_fb);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_FB */

/* HWMON */

#अगर_घोषित CONFIG_S3C_DEV_HWMON
काष्ठा platक्रमm_device s3c_device_hwmon = अणु
	.name		= "s3c-hwmon",
	.id		= -1,
	.dev.parent	= &s3c_device_adc.dev,
पूर्ण;

व्योम __init s3c_hwmon_set_platdata(काष्ठा s3c_hwmon_pdata *pd)
अणु
	s3c_set_platdata(pd, माप(काष्ठा s3c_hwmon_pdata),
			 &s3c_device_hwmon);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_HWMON */

/* HSMMC */

#अगर_घोषित CONFIG_S3C_DEV_HSMMC
अटल काष्ठा resource s3c_hsmmc_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_HSMMC0, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_HSMMC0),
पूर्ण;

काष्ठा s3c_sdhci_platdata s3c_hsmmc0_def_platdata = अणु
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_hsmmc0 = अणु
	.name		= "s3c-sdhci",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c_hsmmc_resource),
	.resource	= s3c_hsmmc_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &s3c_hsmmc0_def_platdata,
	पूर्ण,
पूर्ण;

व्योम s3c_sdhci0_set_platdata(काष्ठा s3c_sdhci_platdata *pd)
अणु
	s3c_sdhci_set_platdata(pd, &s3c_hsmmc0_def_platdata);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC */

#अगर_घोषित CONFIG_S3C_DEV_HSMMC1
अटल काष्ठा resource s3c_hsmmc1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_HSMMC1, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_HSMMC1),
पूर्ण;

काष्ठा s3c_sdhci_platdata s3c_hsmmc1_def_platdata = अणु
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_hsmmc1 = अणु
	.name		= "s3c-sdhci",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(s3c_hsmmc1_resource),
	.resource	= s3c_hsmmc1_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &s3c_hsmmc1_def_platdata,
	पूर्ण,
पूर्ण;

व्योम s3c_sdhci1_set_platdata(काष्ठा s3c_sdhci_platdata *pd)
अणु
	s3c_sdhci_set_platdata(pd, &s3c_hsmmc1_def_platdata);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC1 */

/* HSMMC2 */

#अगर_घोषित CONFIG_S3C_DEV_HSMMC2
अटल काष्ठा resource s3c_hsmmc2_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_HSMMC2, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_HSMMC2),
पूर्ण;

काष्ठा s3c_sdhci_platdata s3c_hsmmc2_def_platdata = अणु
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_hsmmc2 = अणु
	.name		= "s3c-sdhci",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(s3c_hsmmc2_resource),
	.resource	= s3c_hsmmc2_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &s3c_hsmmc2_def_platdata,
	पूर्ण,
पूर्ण;

व्योम s3c_sdhci2_set_platdata(काष्ठा s3c_sdhci_platdata *pd)
अणु
	s3c_sdhci_set_platdata(pd, &s3c_hsmmc2_def_platdata);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC2 */

#अगर_घोषित CONFIG_S3C_DEV_HSMMC3
अटल काष्ठा resource s3c_hsmmc3_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_HSMMC3, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_HSMMC3),
पूर्ण;

काष्ठा s3c_sdhci_platdata s3c_hsmmc3_def_platdata = अणु
	.max_width	= 4,
	.host_caps	= (MMC_CAP_4_BIT_DATA |
			   MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_hsmmc3 = अणु
	.name		= "s3c-sdhci",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(s3c_hsmmc3_resource),
	.resource	= s3c_hsmmc3_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &s3c_hsmmc3_def_platdata,
	पूर्ण,
पूर्ण;

व्योम s3c_sdhci3_set_platdata(काष्ठा s3c_sdhci_platdata *pd)
अणु
	s3c_sdhci_set_platdata(pd, &s3c_hsmmc3_def_platdata);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_HSMMC3 */

/* I2C */

अटल काष्ठा resource s3c_i2c0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c0 = अणु
	.name		= "s3c2410-i2c",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c_i2c0_resource),
	.resource	= s3c_i2c0_resource,
पूर्ण;

काष्ठा s3c2410_platक्रमm_i2c शेष_i2c_data __initdata = अणु
	.flags		= 0,
	.slave_addr	= 0x10,
	.frequency	= 100*1000,
	.sda_delay	= 100,
पूर्ण;

व्योम __init s3c_i2c0_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 0;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c0);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c0_cfg_gpio;
पूर्ण

#अगर_घोषित CONFIG_S3C_DEV_I2C1
अटल काष्ठा resource s3c_i2c1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC1, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC1),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c1 = अणु
	.name		= "s3c2410-i2c",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(s3c_i2c1_resource),
	.resource	= s3c_i2c1_resource,
पूर्ण;

व्योम __init s3c_i2c1_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 1;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c1);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c1_cfg_gpio;
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_I2C1 */

#अगर_घोषित CONFIG_S3C_DEV_I2C2
अटल काष्ठा resource s3c_i2c2_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC2, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC2),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c2 = अणु
	.name		= "s3c2410-i2c",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(s3c_i2c2_resource),
	.resource	= s3c_i2c2_resource,
पूर्ण;

व्योम __init s3c_i2c2_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 2;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c2);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c2_cfg_gpio;
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_I2C2 */

#अगर_घोषित CONFIG_S3C_DEV_I2C3
अटल काष्ठा resource s3c_i2c3_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC3, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC3),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c3 = अणु
	.name		= "s3c2440-i2c",
	.id		= 3,
	.num_resources	= ARRAY_SIZE(s3c_i2c3_resource),
	.resource	= s3c_i2c3_resource,
पूर्ण;

व्योम __init s3c_i2c3_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 3;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c3);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c3_cfg_gpio;
पूर्ण
#पूर्ण_अगर /*CONFIG_S3C_DEV_I2C3 */

#अगर_घोषित CONFIG_S3C_DEV_I2C4
अटल काष्ठा resource s3c_i2c4_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC4, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC4),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c4 = अणु
	.name		= "s3c2440-i2c",
	.id		= 4,
	.num_resources	= ARRAY_SIZE(s3c_i2c4_resource),
	.resource	= s3c_i2c4_resource,
पूर्ण;

व्योम __init s3c_i2c4_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 4;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c4);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c4_cfg_gpio;
पूर्ण
#पूर्ण_अगर /*CONFIG_S3C_DEV_I2C4 */

#अगर_घोषित CONFIG_S3C_DEV_I2C5
अटल काष्ठा resource s3c_i2c5_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC5, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC5),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c5 = अणु
	.name		= "s3c2440-i2c",
	.id		= 5,
	.num_resources	= ARRAY_SIZE(s3c_i2c5_resource),
	.resource	= s3c_i2c5_resource,
पूर्ण;

व्योम __init s3c_i2c5_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 5;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c5);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c5_cfg_gpio;
पूर्ण
#पूर्ण_अगर /*CONFIG_S3C_DEV_I2C5 */

#अगर_घोषित CONFIG_S3C_DEV_I2C6
अटल काष्ठा resource s3c_i2c6_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC6, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC6),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c6 = अणु
	.name		= "s3c2440-i2c",
	.id		= 6,
	.num_resources	= ARRAY_SIZE(s3c_i2c6_resource),
	.resource	= s3c_i2c6_resource,
पूर्ण;

व्योम __init s3c_i2c6_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 6;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c6);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c6_cfg_gpio;
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_I2C6 */

#अगर_घोषित CONFIG_S3C_DEV_I2C7
अटल काष्ठा resource s3c_i2c7_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_IIC7, SZ_4K),
	[1] = DEFINE_RES_IRQ(IRQ_IIC7),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_i2c7 = अणु
	.name		= "s3c2440-i2c",
	.id		= 7,
	.num_resources	= ARRAY_SIZE(s3c_i2c7_resource),
	.resource	= s3c_i2c7_resource,
पूर्ण;

व्योम __init s3c_i2c7_set_platdata(काष्ठा s3c2410_platक्रमm_i2c *pd)
अणु
	काष्ठा s3c2410_platक्रमm_i2c *npd;

	अगर (!pd) अणु
		pd = &शेष_i2c_data;
		pd->bus_num = 7;
	पूर्ण

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_i2c7);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c7_cfg_gpio;
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_I2C7 */

/* I2S */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_iis_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_IIS, S3C24XX_SZ_IIS),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_iis = अणु
	.name		= "s3c24xx-iis",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_iis_resource),
	.resource	= s3c_iis_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* IDE CFCON */

#अगर_घोषित CONFIG_SAMSUNG_DEV_IDE
अटल काष्ठा resource s3c_cfcon_resource[] = अणु
	[0] = DEFINE_RES_MEM(SAMSUNG_PA_CFCON, SZ_16K),
	[1] = DEFINE_RES_IRQ(IRQ_CFCON),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_cfcon = अणु
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c_cfcon_resource),
	.resource	= s3c_cfcon_resource,
पूर्ण;

व्योम __init s3c_ide_set_platdata(काष्ठा s3c_ide_platdata *pdata)
अणु
	s3c_set_platdata(pdata, माप(काष्ठा s3c_ide_platdata),
			 &s3c_device_cfcon);
पूर्ण
#पूर्ण_अगर /* CONFIG_SAMSUNG_DEV_IDE */

/* KEYPAD */

#अगर_घोषित CONFIG_SAMSUNG_DEV_KEYPAD
अटल काष्ठा resource samsung_keypad_resources[] = अणु
	[0] = DEFINE_RES_MEM(SAMSUNG_PA_KEYPAD, SZ_32),
	[1] = DEFINE_RES_IRQ(IRQ_KEYPAD),
पूर्ण;

काष्ठा platक्रमm_device samsung_device_keypad = अणु
	.name		= "samsung-keypad",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(samsung_keypad_resources),
	.resource	= samsung_keypad_resources,
पूर्ण;

व्योम __init samsung_keypad_set_platdata(काष्ठा samsung_keypad_platdata *pd)
अणु
	काष्ठा samsung_keypad_platdata *npd;

	npd = s3c_set_platdata(pd, माप(*npd), &samsung_device_keypad);

	अगर (!npd->cfg_gpio)
		npd->cfg_gpio = samsung_keypad_cfg_gpio;
पूर्ण
#पूर्ण_अगर /* CONFIG_SAMSUNG_DEV_KEYPAD */

/* LCD Controller */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_lcd_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_LCD, S3C24XX_SZ_LCD),
	[1] = DEFINE_RES_IRQ(IRQ_LCD),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_lcd = अणु
	.name		= "s3c2410-lcd",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_lcd_resource),
	.resource	= s3c_lcd_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

व्योम __init s3c24xx_fb_set_platdata(काष्ठा s3c2410fb_mach_info *pd)
अणु
	काष्ठा s3c2410fb_mach_info *npd;

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_lcd);
	अगर (npd) अणु
		npd->displays = kmemdup(pd->displays,
			माप(काष्ठा s3c2410fb_display) * npd->num_displays,
			GFP_KERNEL);
		अगर (!npd->displays)
			prपूर्णांकk(KERN_ERR "no memory for LCD display data\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "no memory for LCD platform data\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* न_अंकD */

#अगर_घोषित CONFIG_S3C_DEV_न_अंकD
अटल काष्ठा resource s3c_nand_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_न_अंकD, SZ_1M),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_nand = अणु
	.name		= "s3c2410-nand",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_nand_resource),
	.resource	= s3c_nand_resource,
पूर्ण;

/*
 * s3c_nand_copy_set() - copy nand set data
 * @set: The new काष्ठाure, directly copied from the old.
 *
 * Copy all the fields from the न_अंकD set field from what is probably __initdata
 * to new kernel memory. The code वापसs 0 अगर the copy happened correctly or
 * an error code क्रम the calling function to display.
 *
 * Note, we currently करो not try and look to see अगर we've alपढ़ोy copied the
 * data in a previous set.
 */
अटल पूर्णांक __init s3c_nand_copy_set(काष्ठा s3c2410_nand_set *set)
अणु
	व्योम *ptr;
	पूर्णांक size;

	size = माप(काष्ठा mtd_partition) * set->nr_partitions;
	अगर (size) अणु
		ptr = kmemdup(set->partitions, size, GFP_KERNEL);
		set->partitions = ptr;

		अगर (!ptr)
			वापस -ENOMEM;
	पूर्ण

	अगर (set->nr_map && set->nr_chips) अणु
		size = माप(पूर्णांक) * set->nr_chips;
		ptr = kmemdup(set->nr_map, size, GFP_KERNEL);
		set->nr_map = ptr;

		अगर (!ptr)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __init s3c_nand_set_platdata(काष्ठा s3c2410_platक्रमm_nand *nand)
अणु
	काष्ठा s3c2410_platक्रमm_nand *npd;
	पूर्णांक size;
	पूर्णांक ret;

	/* note, अगर we get a failure in allocation, we simply drop out of the
	 * function. If there is so little memory available at initialisation
	 * समय then there is little chance the प्रणाली is going to run.
	 */

	npd = s3c_set_platdata(nand, माप(*npd), &s3c_device_nand);
	अगर (!npd)
		वापस;

	/* now see अगर we need to copy any of the nand set data */

	size = माप(काष्ठा s3c2410_nand_set) * npd->nr_sets;
	अगर (size) अणु
		काष्ठा s3c2410_nand_set *from = npd->sets;
		काष्ठा s3c2410_nand_set *to;
		पूर्णांक i;

		to = kmemdup(from, size, GFP_KERNEL);
		npd->sets = to;	/* set, even अगर we failed */

		अगर (!to) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for sets\n", __func__);
			वापस;
		पूर्ण

		क्रम (i = 0; i < npd->nr_sets; i++) अणु
			ret = s3c_nand_copy_set(to);
			अगर (ret) अणु
				prपूर्णांकk(KERN_ERR "%s: failed to copy set %d\n",
				__func__, i);
				वापस;
			पूर्ण
			to++;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_न_अंकD */

/* ONEन_अंकD */

#अगर_घोषित CONFIG_S3C_DEV_ONEन_अंकD
अटल काष्ठा resource s3c_onenand_resources[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_ONEन_अंकD, SZ_1K),
	[1] = DEFINE_RES_MEM(S3C_PA_ONEन_अंकD_BUF, S3C_SZ_ONEन_अंकD_BUF),
	[2] = DEFINE_RES_IRQ(IRQ_ONEन_अंकD),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_onenand = अणु
	.name		= "samsung-onenand",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c_onenand_resources),
	.resource	= s3c_onenand_resources,
पूर्ण;
#पूर्ण_अगर /* CONFIG_S3C_DEV_ONEन_अंकD */

#अगर_घोषित CONFIG_S3C64XX_DEV_ONEन_अंकD1
अटल काष्ठा resource s3c64xx_onenand1_resources[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_ONEन_अंकD1, SZ_1K),
	[1] = DEFINE_RES_MEM(S3C64XX_PA_ONEन_अंकD1_BUF, S3C64XX_SZ_ONEन_अंकD1_BUF),
	[2] = DEFINE_RES_IRQ(IRQ_ONEन_अंकD1),
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_onenand1 = अणु
	.name		= "samsung-onenand",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(s3c64xx_onenand1_resources),
	.resource	= s3c64xx_onenand1_resources,
पूर्ण;

व्योम __init s3c64xx_onenand1_set_platdata(काष्ठा onenand_platक्रमm_data *pdata)
अणु
	s3c_set_platdata(pdata, माप(काष्ठा onenand_platक्रमm_data),
			 &s3c64xx_device_onenand1);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C64XX_DEV_ONEन_अंकD1 */

/* PWM Timer */

#अगर_घोषित CONFIG_SAMSUNG_DEV_PWM
अटल काष्ठा resource samsung_pwm_resource[] = अणु
	DEFINE_RES_MEM(SAMSUNG_PA_TIMER, SZ_4K),
पूर्ण;

काष्ठा platक्रमm_device samsung_device_pwm = अणु
	.name		= "samsung-pwm",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(samsung_pwm_resource),
	.resource	= samsung_pwm_resource,
पूर्ण;

व्योम __init samsung_pwm_set_platdata(काष्ठा samsung_pwm_variant *pd)
अणु
	samsung_device_pwm.dev.platक्रमm_data = pd;
पूर्ण
#पूर्ण_अगर /* CONFIG_SAMSUNG_DEV_PWM */

/* RTC */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_rtc_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_RTC, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_RTC),
	[2] = DEFINE_RES_IRQ(IRQ_TICK),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_rtc = अणु
	.name		= "s3c2410-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_rtc_resource),
	.resource	= s3c_rtc_resource,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

#अगर_घोषित CONFIG_S3C_DEV_RTC
अटल काष्ठा resource s3c_rtc_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_RTC, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_RTC_ALARM),
	[2] = DEFINE_RES_IRQ(IRQ_RTC_TIC),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_rtc = अणु
	.name		= "s3c64xx-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_rtc_resource),
	.resource	= s3c_rtc_resource,
पूर्ण;
#पूर्ण_अगर /* CONFIG_S3C_DEV_RTC */

/* SDI */

#अगर_घोषित CONFIG_PLAT_S3C24XX
व्योम s3c24xx_mci_def_set_घातer(अचिन्हित अक्षर घातer_mode, अचिन्हित लघु vdd)
अणु
	चयन (घातer_mode) अणु
	हाल MMC_POWER_ON:
	हाल MMC_POWER_UP:
		/* Configure GPE5...GPE10 pins in SD mode */
		s3c_gpio_cfgall_range(S3C2410_GPE(5), 6, S3C_GPIO_SFN(2),
				      S3C_GPIO_PULL_NONE);
		अवरोध;

	हाल MMC_POWER_OFF:
	शेष:
		gpio_direction_output(S3C2410_GPE(5), 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा resource s3c_sdi_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_SDI, S3C24XX_SZ_SDI),
	[1] = DEFINE_RES_IRQ(IRQ_SDI),
पूर्ण;

अटल काष्ठा s3c24xx_mci_pdata s3cmci_def_pdata = अणु
	/* This is currently here to aव्योम a number of अगर (host->pdata)
	 * checks. Any zero fields to ensure reasonable शेषs are picked. */
	.no_wprotect = 1,
	.no_detect = 1,
	.set_घातer = s3c24xx_mci_def_set_घातer,
पूर्ण;

काष्ठा platक्रमm_device s3c_device_sdi = अणु
	.name		= "s3c2410-sdi",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_sdi_resource),
	.resource	= s3c_sdi_resource,
	.dev.platक्रमm_data = &s3cmci_def_pdata,
पूर्ण;

व्योम __init s3c24xx_mci_set_platdata(काष्ठा s3c24xx_mci_pdata *pdata)
अणु
	s3c_set_platdata(pdata, माप(काष्ठा s3c24xx_mci_pdata),
			 &s3c_device_sdi);
पूर्ण
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* SPI */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_spi0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_SPI, SZ_32),
	[1] = DEFINE_RES_IRQ(IRQ_SPI0),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_spi0 = अणु
	.name		= "s3c2410-spi",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c_spi0_resource),
	.resource	= s3c_spi0_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

अटल काष्ठा resource s3c_spi1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_SPI1, SZ_32),
	[1] = DEFINE_RES_IRQ(IRQ_SPI1),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_spi1 = अणु
	.name		= "s3c2410-spi",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(s3c_spi1_resource),
	.resource	= s3c_spi1_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* Touchscreen */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_ts_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_ADC, S3C24XX_SZ_ADC),
	[1] = DEFINE_RES_IRQ(IRQ_TC),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_ts = अणु
	.name		= "s3c2410-ts",
	.id		= -1,
	.dev.parent	= &s3c_device_adc.dev,
	.num_resources	= ARRAY_SIZE(s3c_ts_resource),
	.resource	= s3c_ts_resource,
पूर्ण;

व्योम __init s3c24xx_ts_set_platdata(काष्ठा s3c2410_ts_mach_info *hard_s3c2410ts_info)
अणु
	s3c_set_platdata(hard_s3c2410ts_info,
			 माप(काष्ठा s3c2410_ts_mach_info), &s3c_device_ts);
पूर्ण
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

#अगर_घोषित CONFIG_SAMSUNG_DEV_TS
अटल काष्ठा s3c2410_ts_mach_info शेष_ts_data __initdata = अणु
	.delay			= 10000,
	.presc			= 49,
	.oversampling_shअगरt	= 2,
पूर्ण;

व्योम __init s3c64xx_ts_set_platdata(काष्ठा s3c2410_ts_mach_info *pd)
अणु
	अगर (!pd)
		pd = &शेष_ts_data;

	s3c_set_platdata(pd, माप(काष्ठा s3c2410_ts_mach_info),
			 &s3c_device_adc);
पूर्ण
#पूर्ण_अगर /* CONFIG_SAMSUNG_DEV_TS */

/* USB */

#अगर_घोषित CONFIG_S3C_DEV_USB_HOST
अटल काष्ठा resource s3c_usb_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_USBHOST, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_USBH),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_ohci = अणु
	.name		= "s3c2410-ohci",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_usb_resource),
	.resource	= s3c_usb_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

/*
 * s3c_ohci_set_platdata - initialise OHCI device platक्रमm data
 * @info: The platक्रमm data.
 *
 * This call copies the @info passed in and sets the device .platक्रमm_data
 * field to that copy. The @info is copied so that the original can be marked
 * __initdata.
 */

व्योम __init s3c_ohci_set_platdata(काष्ठा s3c2410_hcd_info *info)
अणु
	s3c_set_platdata(info, माप(काष्ठा s3c2410_hcd_info),
			 &s3c_device_ohci);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_USB_HOST */

/* USB Device (Gadget) */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_usbgadget_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_USBDEV, S3C24XX_SZ_USBDEV),
	[1] = DEFINE_RES_IRQ(IRQ_USBD),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_usbgadget = अणु
	.name		= "s3c2410-usbgadget",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_usbgadget_resource),
	.resource	= s3c_usbgadget_resource,
पूर्ण;

व्योम __init s3c24xx_udc_set_platdata(काष्ठा s3c2410_udc_mach_info *pd)
अणु
	s3c_set_platdata(pd, माप(*pd), &s3c_device_usbgadget);
पूर्ण
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* USB HSOTG */

#अगर_घोषित CONFIG_S3C_DEV_USB_HSOTG
अटल काष्ठा resource s3c_usb_hsotg_resources[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_USB_HSOTG, SZ_128K),
	[1] = DEFINE_RES_IRQ(IRQ_OTG),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_usb_hsotg = अणु
	.name		= "s3c-hsotg",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_usb_hsotg_resources),
	.resource	= s3c_usb_hsotg_resources,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init dwc2_hsotg_set_platdata(काष्ठा dwc2_hsotg_plat *pd)
अणु
	काष्ठा dwc2_hsotg_plat *npd;

	npd = s3c_set_platdata(pd, माप(*npd), &s3c_device_usb_hsotg);

	अगर (!npd->phy_init)
		npd->phy_init = s3c_usb_phy_init;
	अगर (!npd->phy_निकास)
		npd->phy_निकास = s3c_usb_phy_निकास;
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C_DEV_USB_HSOTG */

/* USB High Spped 2.0 Device (Gadget) */

#अगर_घोषित CONFIG_PLAT_S3C24XX
अटल काष्ठा resource s3c_hsudc_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2416_PA_HSUDC, S3C2416_SZ_HSUDC),
	[1] = DEFINE_RES_IRQ(IRQ_USBD),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_usb_hsudc = अणु
	.name		= "s3c-hsudc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_hsudc_resource),
	.resource	= s3c_hsudc_resource,
	.dev		= अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init s3c24xx_hsudc_set_platdata(काष्ठा s3c24xx_hsudc_platdata *pd)
अणु
	s3c_set_platdata(pd, माप(*pd), &s3c_device_usb_hsudc);
	pd->phy_init = s3c_hsudc_init_phy;
	pd->phy_uninit = s3c_hsudc_uninit_phy;
पूर्ण
#पूर्ण_अगर /* CONFIG_PLAT_S3C24XX */

/* WDT */

#अगर_घोषित CONFIG_S3C_DEV_WDT
अटल काष्ठा resource s3c_wdt_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_WDT, SZ_1K),
	[1] = DEFINE_RES_IRQ(IRQ_WDT),
पूर्ण;

काष्ठा platक्रमm_device s3c_device_wdt = अणु
	.name		= "s3c2410-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s3c_wdt_resource),
	.resource	= s3c_wdt_resource,
पूर्ण;
#पूर्ण_अगर /* CONFIG_S3C_DEV_WDT */

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI0
अटल काष्ठा resource s3c64xx_spi0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_SPI0, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_SPI0),
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_spi0 = अणु
	.name		= "s3c6410-spi",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c64xx_spi0_resource),
	.resource	= s3c64xx_spi0_resource,
	.dev = अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init s3c64xx_spi0_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs)
अणु
	काष्ठा s3c64xx_spi_info pd;

	/* Reject invalid configuration */
	अगर (!num_cs || src_clk_nr < 0) अणु
		pr_err("%s: Invalid SPI configuration\n", __func__);
		वापस;
	पूर्ण

	pd.num_cs = num_cs;
	pd.src_clk_nr = src_clk_nr;
	pd.cfg_gpio = (cfg_gpio) ? cfg_gpio : s3c64xx_spi0_cfg_gpio;

	s3c_set_platdata(&pd, माप(pd), &s3c64xx_device_spi0);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C64XX_DEV_SPI0 */

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI1
अटल काष्ठा resource s3c64xx_spi1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_SPI1, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_SPI1),
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_spi1 = अणु
	.name		= "s3c6410-spi",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(s3c64xx_spi1_resource),
	.resource	= s3c64xx_spi1_resource,
	.dev = अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init s3c64xx_spi1_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs)
अणु
	काष्ठा s3c64xx_spi_info pd;

	/* Reject invalid configuration */
	अगर (!num_cs || src_clk_nr < 0) अणु
		pr_err("%s: Invalid SPI configuration\n", __func__);
		वापस;
	पूर्ण

	pd.num_cs = num_cs;
	pd.src_clk_nr = src_clk_nr;
	pd.cfg_gpio = (cfg_gpio) ? cfg_gpio : s3c64xx_spi1_cfg_gpio;

	s3c_set_platdata(&pd, माप(pd), &s3c64xx_device_spi1);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C64XX_DEV_SPI1 */

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI2
अटल काष्ठा resource s3c64xx_spi2_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_SPI2, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_SPI2),
पूर्ण;

काष्ठा platक्रमm_device s3c64xx_device_spi2 = अणु
	.name		= "s3c6410-spi",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(s3c64xx_spi2_resource),
	.resource	= s3c64xx_spi2_resource,
	.dev = अणु
		.dma_mask		= &samsung_device_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

व्योम __init s3c64xx_spi2_set_platdata(पूर्णांक (*cfg_gpio)(व्योम), पूर्णांक src_clk_nr,
						पूर्णांक num_cs)
अणु
	काष्ठा s3c64xx_spi_info pd;

	/* Reject invalid configuration */
	अगर (!num_cs || src_clk_nr < 0) अणु
		pr_err("%s: Invalid SPI configuration\n", __func__);
		वापस;
	पूर्ण

	pd.num_cs = num_cs;
	pd.src_clk_nr = src_clk_nr;
	pd.cfg_gpio = (cfg_gpio) ? cfg_gpio : s3c64xx_spi2_cfg_gpio;

	s3c_set_platdata(&pd, माप(pd), &s3c64xx_device_spi2);
पूर्ण
#पूर्ण_अगर /* CONFIG_S3C64XX_DEV_SPI2 */
