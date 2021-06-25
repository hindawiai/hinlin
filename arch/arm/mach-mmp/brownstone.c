<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/brownstone.c
 *
 *  Support क्रम the Marvell Brownstone Development Platक्रमm.
 *
 *  Copyright (C) 2009-2010 Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/max8649.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/mfd/max8925.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-mmp2.h"
#समावेश "mmp2.h"
#समावेश "irqs.h"

#समावेश "common.h"

#घोषणा BROWNSTONE_NR_IRQS	(MMP_NR_IRQS + 40)

#घोषणा GPIO_5V_ENABLE		(89)

अटल अचिन्हित दीर्घ brownstone_pin_config[] __initdata = अणु
	/* UART1 */
	GPIO29_UART1_RXD,
	GPIO30_UART1_TXD,

	/* UART3 */
	GPIO51_UART3_RXD,
	GPIO52_UART3_TXD,

	/* DFI */
	GPIO168_DFI_D0,
	GPIO167_DFI_D1,
	GPIO166_DFI_D2,
	GPIO165_DFI_D3,
	GPIO107_DFI_D4,
	GPIO106_DFI_D5,
	GPIO105_DFI_D6,
	GPIO104_DFI_D7,
	GPIO111_DFI_D8,
	GPIO164_DFI_D9,
	GPIO163_DFI_D10,
	GPIO162_DFI_D11,
	GPIO161_DFI_D12,
	GPIO110_DFI_D13,
	GPIO109_DFI_D14,
	GPIO108_DFI_D15,
	GPIO143_ND_nCS0,
	GPIO144_ND_nCS1,
	GPIO147_ND_nWE,
	GPIO148_ND_nRE,
	GPIO150_ND_ALE,
	GPIO149_ND_CLE,
	GPIO112_ND_RDY0,
	GPIO160_ND_RDY1,

	/* PMIC */
	PMIC_PMIC_INT | MFP_LPM_EDGE_FALL,

	/* MMC0 */
	GPIO131_MMC1_DAT3 | MFP_PULL_HIGH,
	GPIO132_MMC1_DAT2 | MFP_PULL_HIGH,
	GPIO133_MMC1_DAT1 | MFP_PULL_HIGH,
	GPIO134_MMC1_DAT0 | MFP_PULL_HIGH,
	GPIO136_MMC1_CMD | MFP_PULL_HIGH,
	GPIO139_MMC1_CLK,
	GPIO140_MMC1_CD | MFP_PULL_LOW,
	GPIO141_MMC1_WP | MFP_PULL_LOW,

	/* MMC1 */
	GPIO37_MMC2_DAT3 | MFP_PULL_HIGH,
	GPIO38_MMC2_DAT2 | MFP_PULL_HIGH,
	GPIO39_MMC2_DAT1 | MFP_PULL_HIGH,
	GPIO40_MMC2_DAT0 | MFP_PULL_HIGH,
	GPIO41_MMC2_CMD | MFP_PULL_HIGH,
	GPIO42_MMC2_CLK,

	/* MMC2 */
	GPIO165_MMC3_DAT7 | MFP_PULL_HIGH,
	GPIO162_MMC3_DAT6 | MFP_PULL_HIGH,
	GPIO166_MMC3_DAT5 | MFP_PULL_HIGH,
	GPIO163_MMC3_DAT4 | MFP_PULL_HIGH,
	GPIO167_MMC3_DAT3 | MFP_PULL_HIGH,
	GPIO164_MMC3_DAT2 | MFP_PULL_HIGH,
	GPIO168_MMC3_DAT1 | MFP_PULL_HIGH,
	GPIO111_MMC3_DAT0 | MFP_PULL_HIGH,
	GPIO112_MMC3_CMD | MFP_PULL_HIGH,
	GPIO151_MMC3_CLK,

	/* 5V regulator */
	GPIO89_GPIO,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data mmp2_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा regulator_consumer_supply max8649_supply[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data max8649_init_data = अणु
	.स्थिरraपूर्णांकs	= अणु
		.name		= "vcc_core range",
		.min_uV		= 1150000,
		.max_uV		= 1280000,
		.always_on	= 1,
		.boot_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &max8649_supply[0],
पूर्ण;

अटल काष्ठा max8649_platक्रमm_data brownstone_max8649_info = अणु
	.mode		= 2,	/* VID1 = 1, VID0 = 0 */
	.extclk		= 0,
	.ramp_timing	= MAX8649_RAMP_32MV,
	.regulator	= &max8649_init_data,
पूर्ण;

अटल काष्ठा regulator_consumer_supply brownstone_v_5vp_supplies[] = अणु
	REGULATOR_SUPPLY("v_5vp", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data brownstone_v_5vp_data = अणु
	.स्थिरraपूर्णांकs	= अणु
		.valid_ops_mask		= REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies	= ARRAY_SIZE(brownstone_v_5vp_supplies),
	.consumer_supplies	= brownstone_v_5vp_supplies,
पूर्ण;

अटल काष्ठा fixed_voltage_config brownstone_v_5vp = अणु
	.supply_name		= "v_5vp",
	.microvolts		= 5000000,
	.enabled_at_boot	= 1,
	.init_data		= &brownstone_v_5vp_data,
पूर्ण;

अटल काष्ठा platक्रमm_device brownstone_v_5vp_device = अणु
	.name		= "reg-fixed-voltage",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data = &brownstone_v_5vp,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table brownstone_v_5vp_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage.1", /* .id set to 1 above */
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_5V_ENABLE,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा max8925_platक्रमm_data brownstone_max8925_info = अणु
	.irq_base		= MMP_NR_IRQS,
पूर्ण;

अटल काष्ठा i2c_board_info brownstone_twsi1_info[] = अणु
	[0] = अणु
		.type		= "max8649",
		.addr		= 0x60,
		.platक्रमm_data	= &brownstone_max8649_info,
	पूर्ण,
	[1] = अणु
		.type		= "max8925",
		.addr		= 0x3c,
		.irq		= IRQ_MMP2_PMIC,
		.platक्रमm_data	= &brownstone_max8925_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा sdhci_pxa_platdata mmp2_sdh_platdata_mmc0 = अणु
	.clk_delay_cycles = 0x1f,
पूर्ण;

अटल काष्ठा sdhci_pxa_platdata mmp2_sdh_platdata_mmc2 = अणु
	.clk_delay_cycles = 0x1f,
	.flags = PXA_FLAG_CARD_PERMANENT
		| PXA_FLAG_SD_8_BIT_CAPABLE_SLOT,
पूर्ण;

अटल काष्ठा sram_platdata mmp2_asram_platdata = अणु
	.pool_name	= "asram",
	.granularity	= SRAM_GRANULARITY,
पूर्ण;

अटल काष्ठा sram_platdata mmp2_isram_platdata = अणु
	.pool_name	= "isram",
	.granularity	= SRAM_GRANULARITY,
पूर्ण;

अटल व्योम __init brownstone_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(brownstone_pin_config));

	/* on-chip devices */
	mmp2_add_uart(1);
	mmp2_add_uart(3);
	platक्रमm_device_add_data(&mmp2_device_gpio, &mmp2_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&mmp2_device_gpio);
	mmp2_add_twsi(1, शून्य, ARRAY_AND_SIZE(brownstone_twsi1_info));
	mmp2_add_sdhost(0, &mmp2_sdh_platdata_mmc0); /* SD/MMC */
	mmp2_add_sdhost(2, &mmp2_sdh_platdata_mmc2); /* eMMC */
	mmp2_add_asram(&mmp2_asram_platdata);
	mmp2_add_isram(&mmp2_isram_platdata);

	/* enable 5v regulator */
	gpiod_add_lookup_table(&brownstone_v_5vp_gpiod_table);
	platक्रमm_device_रेजिस्टर(&brownstone_v_5vp_device);
पूर्ण

MACHINE_START(BROWNSTONE, "Brownstone Development Platform")
	/* Maपूर्णांकainer: Haojian Zhuang <haojian.zhuang@marvell.com> */
	.map_io		= mmp_map_io,
	.nr_irqs	= BROWNSTONE_NR_IRQS,
	.init_irq	= mmp2_init_irq,
	.init_समय	= mmp2_समयr_init,
	.init_machine	= brownstone_init,
	.restart	= mmp_restart,
MACHINE_END
