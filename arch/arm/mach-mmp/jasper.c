<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/jasper.c
 *
 *  Support क्रम the Marvell Jasper Development Platक्रमm.
 *
 *  Copyright (C) 2009-2010 Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/max8649.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "irqs.h"
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "addr-map.h"
#समावेश "mfp-mmp2.h"
#समावेश "mmp2.h"

#समावेश "common.h"

#घोषणा JASPER_NR_IRQS		(MMP_NR_IRQS + 48)

अटल अचिन्हित दीर्घ jasper_pin_config[] __initdata = अणु
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

	/* MMC1 */
	GPIO131_MMC1_DAT3,
	GPIO132_MMC1_DAT2,
	GPIO133_MMC1_DAT1,
	GPIO134_MMC1_DAT0,
	GPIO136_MMC1_CMD,
	GPIO139_MMC1_CLK,
	GPIO140_MMC1_CD,
	GPIO141_MMC1_WP,

	/* MMC2 */
	GPIO37_MMC2_DAT3,
	GPIO38_MMC2_DAT2,
	GPIO39_MMC2_DAT1,
	GPIO40_MMC2_DAT0,
	GPIO41_MMC2_CMD,
	GPIO42_MMC2_CLK,

	/* MMC3 */
	GPIO165_MMC3_DAT7,
	GPIO162_MMC3_DAT6,
	GPIO166_MMC3_DAT5,
	GPIO163_MMC3_DAT4,
	GPIO167_MMC3_DAT3,
	GPIO164_MMC3_DAT2,
	GPIO168_MMC3_DAT1,
	GPIO111_MMC3_DAT0,
	GPIO112_MMC3_CMD,
	GPIO151_MMC3_CLK,
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

अटल काष्ठा max8649_platक्रमm_data jasper_max8649_info = अणु
	.mode		= 2,	/* VID1 = 1, VID0 = 0 */
	.extclk		= 0,
	.ramp_timing	= MAX8649_RAMP_32MV,
	.regulator	= &max8649_init_data,
पूर्ण;

अटल काष्ठा max8925_backlight_pdata jasper_backlight_data = अणु
	.dual_string	= 0,
पूर्ण;

अटल काष्ठा max8925_घातer_pdata jasper_घातer_data = अणु
	.batt_detect		= 0,	/* can't detect battery by ID pin */
	.topoff_threshold	= MAX8925_TOPOFF_THR_10PER,
	.fast_अक्षरge		= MAX8925_FCHG_1000MA,
पूर्ण;

अटल काष्ठा max8925_platक्रमm_data jasper_max8925_info = अणु
	.backlight		= &jasper_backlight_data,
	.घातer			= &jasper_घातer_data,
	.irq_base		= MMP_NR_IRQS,
पूर्ण;

अटल काष्ठा i2c_board_info jasper_twsi1_info[] = अणु
	[0] = अणु
		.type		= "max8649",
		.addr		= 0x60,
		.platक्रमm_data	= &jasper_max8649_info,
	पूर्ण,
	[1] = अणु
		.type		= "max8925",
		.addr		= 0x3c,
		.irq		= IRQ_MMP2_PMIC,
		.platक्रमm_data	= &jasper_max8925_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा sdhci_pxa_platdata mmp2_sdh_platdata_mmc0 = अणु
	.clk_delay_cycles = 0x1f,
पूर्ण;

अटल व्योम __init jasper_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(jasper_pin_config));

	/* on-chip devices */
	mmp2_add_uart(1);
	mmp2_add_uart(3);
	mmp2_add_twsi(1, शून्य, ARRAY_AND_SIZE(jasper_twsi1_info));
	platक्रमm_device_add_data(&mmp2_device_gpio, &mmp2_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_device_रेजिस्टर(&mmp2_device_gpio);
	mmp2_add_sdhost(0, &mmp2_sdh_platdata_mmc0); /* SD/MMC */

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

MACHINE_START(MARVELL_JASPER, "Jasper Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= JASPER_NR_IRQS,
	.init_irq       = mmp2_init_irq,
	.init_समय	= mmp2_समयr_init,
	.init_machine   = jasper_init,
	.restart	= mmp_restart,
MACHINE_END
