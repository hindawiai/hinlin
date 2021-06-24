<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  lpc_ich.c - LPC पूर्णांकerface क्रम Intel ICH
 *
 *  LPC bridge function of the Intel ICH contains many other
 *  functional units, such as Interrupt controllers, Timers,
 *  Power Management, System Management, GPIO, RTC, and LPC
 *  Configuration Registers.
 *
 *  This driver is derived from lpc_sch.

 *  Copyright (c) 2011 Extreme Engineering Solution, Inc.
 *  Author: Aaron Sierra <asierra@xes-inc.com>
 *
 *  This driver supports the following I/O Controller hubs:
 *	(See the पूर्णांकel करोcumentation on http://developer.पूर्णांकel.com.)
 *	करोcument number 290655-003, 290677-014: 82801AA (ICH), 82801AB (ICHO)
 *	करोcument number 290687-002, 298242-027: 82801BA (ICH2)
 *	करोcument number 290733-003, 290739-013: 82801CA (ICH3-S)
 *	करोcument number 290716-001, 290718-007: 82801CAM (ICH3-M)
 *	करोcument number 290744-001, 290745-025: 82801DB (ICH4)
 *	करोcument number 252337-001, 252663-008: 82801DBM (ICH4-M)
 *	करोcument number 273599-001, 273645-002: 82801E (C-ICH)
 *	करोcument number 252516-001, 252517-028: 82801EB (ICH5), 82801ER (ICH5R)
 *	करोcument number 300641-004, 300884-013: 6300ESB
 *	करोcument number 301473-002, 301474-026: 82801F (ICH6)
 *	करोcument number 313082-001, 313075-006: 631xESB, 632xESB
 *	करोcument number 307013-003, 307014-024: 82801G (ICH7)
 *	करोcument number 322896-001, 322897-001: NM10
 *	करोcument number 313056-003, 313057-017: 82801H (ICH8)
 *	करोcument number 316972-004, 316973-012: 82801I (ICH9)
 *	करोcument number 319973-002, 319974-002: 82801J (ICH10)
 *	करोcument number 322169-001, 322170-003: 5 Series, 3400 Series (PCH)
 *	करोcument number 320066-003, 320257-008: EP80597 (IICH)
 *	करोcument number 324645-001, 324646-001: Cougar Poपूर्णांक (CPT)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/lpc_ich.h>
#समावेश <linux/platक्रमm_data/itco_wdt.h>

#घोषणा ACPIBASE		0x40
#घोषणा ACPIBASE_GPE_OFF	0x28
#घोषणा ACPIBASE_GPE_END	0x2f
#घोषणा ACPIBASE_SMI_OFF	0x30
#घोषणा ACPIBASE_SMI_END	0x33
#घोषणा ACPIBASE_PMC_OFF	0x08
#घोषणा ACPIBASE_PMC_END	0x0c
#घोषणा ACPIBASE_TCO_OFF	0x60
#घोषणा ACPIBASE_TCO_END	0x7f
#घोषणा ACPICTRL_PMCBASE	0x44

#घोषणा ACPIBASE_GCS_OFF	0x3410
#घोषणा ACPIBASE_GCS_END	0x3414

#घोषणा SPIBASE_BYT		0x54
#घोषणा SPIBASE_BYT_SZ		512
#घोषणा SPIBASE_BYT_EN		BIT(1)

#घोषणा SPIBASE_LPT		0x3800
#घोषणा SPIBASE_LPT_SZ		512
#घोषणा BCR			0xdc
#घोषणा BCR_WPD			BIT(0)

#घोषणा SPIBASE_APL_SZ		4096

#घोषणा GPIOBASE_ICH0		0x58
#घोषणा GPIOCTRL_ICH0		0x5C
#घोषणा GPIOBASE_ICH6		0x48
#घोषणा GPIOCTRL_ICH6		0x4C

#घोषणा RCBABASE		0xf0

#घोषणा wdt_io_res(i) wdt_res(0, i)
#घोषणा wdt_mem_res(i) wdt_res(ICH_RES_MEM_OFF, i)
#घोषणा wdt_res(b, i) (&wdt_ich_res[(b) + (i)])

काष्ठा lpc_ich_priv अणु
	पूर्णांक chipset;

	पूर्णांक abase;		/* ACPI base */
	पूर्णांक actrl_pbase;	/* ACPI control or PMC base */
	पूर्णांक gbase;		/* GPIO base */
	पूर्णांक gctrl;		/* GPIO control */

	पूर्णांक abase_save;		/* Cached ACPI base value */
	पूर्णांक actrl_pbase_save;		/* Cached ACPI control or PMC base value */
	पूर्णांक gctrl_save;		/* Cached GPIO control value */
पूर्ण;

अटल काष्ठा resource wdt_ich_res[] = अणु
	/* ACPI - TCO */
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
	/* ACPI - SMI */
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
	/* GCS or PMC */
	अणु
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource gpio_ich_res[] = अणु
	/* GPIO */
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
	/* ACPI - GPE0 */
	अणु
		.flags = IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource पूर्णांकel_spi_res[] = अणु
	अणु
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा mfd_cell lpc_ich_wdt_cell = अणु
	.name = "iTCO_wdt",
	.num_resources = ARRAY_SIZE(wdt_ich_res),
	.resources = wdt_ich_res,
	.ignore_resource_conflicts = true,
पूर्ण;

अटल काष्ठा mfd_cell lpc_ich_gpio_cell = अणु
	.name = "gpio_ich",
	.num_resources = ARRAY_SIZE(gpio_ich_res),
	.resources = gpio_ich_res,
	.ignore_resource_conflicts = true,
पूर्ण;


अटल काष्ठा mfd_cell lpc_ich_spi_cell = अणु
	.name = "intel-spi",
	.num_resources = ARRAY_SIZE(पूर्णांकel_spi_res),
	.resources = पूर्णांकel_spi_res,
	.ignore_resource_conflicts = true,
पूर्ण;

/* chipset related info */
क्रमागत lpc_chipsets अणु
	LPC_ICH = 0,	/* ICH */
	LPC_ICH0,	/* ICH0 */
	LPC_ICH2,	/* ICH2 */
	LPC_ICH2M,	/* ICH2-M */
	LPC_ICH3,	/* ICH3-S */
	LPC_ICH3M,	/* ICH3-M */
	LPC_ICH4,	/* ICH4 */
	LPC_ICH4M,	/* ICH4-M */
	LPC_CICH,	/* C-ICH */
	LPC_ICH5,	/* ICH5 & ICH5R */
	LPC_6300ESB,	/* 6300ESB */
	LPC_ICH6,	/* ICH6 & ICH6R */
	LPC_ICH6M,	/* ICH6-M */
	LPC_ICH6W,	/* ICH6W & ICH6RW */
	LPC_631XESB,	/* 631xESB/632xESB */
	LPC_ICH7,	/* ICH7 & ICH7R */
	LPC_ICH7DH,	/* ICH7DH */
	LPC_ICH7M,	/* ICH7-M & ICH7-U */
	LPC_ICH7MDH,	/* ICH7-M DH */
	LPC_NM10,	/* NM10 */
	LPC_ICH8,	/* ICH8 & ICH8R */
	LPC_ICH8DH,	/* ICH8DH */
	LPC_ICH8DO,	/* ICH8DO */
	LPC_ICH8M,	/* ICH8M */
	LPC_ICH8ME,	/* ICH8M-E */
	LPC_ICH9,	/* ICH9 */
	LPC_ICH9R,	/* ICH9R */
	LPC_ICH9DH,	/* ICH9DH */
	LPC_ICH9DO,	/* ICH9DO */
	LPC_ICH9M,	/* ICH9M */
	LPC_ICH9ME,	/* ICH9M-E */
	LPC_ICH10,	/* ICH10 */
	LPC_ICH10R,	/* ICH10R */
	LPC_ICH10D,	/* ICH10D */
	LPC_ICH10DO,	/* ICH10DO */
	LPC_PCH,	/* PCH Desktop Full Featured */
	LPC_PCHM,	/* PCH Mobile Full Featured */
	LPC_P55,	/* P55 */
	LPC_PM55,	/* PM55 */
	LPC_H55,	/* H55 */
	LPC_QM57,	/* QM57 */
	LPC_H57,	/* H57 */
	LPC_HM55,	/* HM55 */
	LPC_Q57,	/* Q57 */
	LPC_HM57,	/* HM57 */
	LPC_PCHMSFF,	/* PCH Mobile SFF Full Featured */
	LPC_QS57,	/* QS57 */
	LPC_3400,	/* 3400 */
	LPC_3420,	/* 3420 */
	LPC_3450,	/* 3450 */
	LPC_EP80579,	/* EP80579 */
	LPC_CPT,	/* Cougar Poपूर्णांक */
	LPC_CPTD,	/* Cougar Poपूर्णांक Desktop */
	LPC_CPTM,	/* Cougar Poपूर्णांक Mobile */
	LPC_PBG,	/* Patsburg */
	LPC_DH89XXCC,	/* DH89xxCC */
	LPC_PPT,	/* Panther Poपूर्णांक */
	LPC_LPT,	/* Lynx Poपूर्णांक */
	LPC_LPT_LP,	/* Lynx Poपूर्णांक-LP */
	LPC_WBG,	/* Wellsburg */
	LPC_AVN,	/* Avoton SoC */
	LPC_BAYTRAIL,   /* Bay Trail SoC */
	LPC_COLETO,	/* Coleto Creek */
	LPC_WPT_LP,	/* Wildcat Poपूर्णांक-LP */
	LPC_BRASWELL,	/* Braswell SoC */
	LPC_LEWISBURG,	/* Lewisburg */
	LPC_9S,		/* 9 Series */
	LPC_APL,	/* Apollo Lake SoC */
	LPC_GLK,	/* Gemini Lake SoC */
	LPC_COUGARMOUNTAIN,/* Cougar Mountain SoC*/
पूर्ण;

अटल काष्ठा lpc_ich_info lpc_chipset_info[] = अणु
	[LPC_ICH] = अणु
		.name = "ICH",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH0] = अणु
		.name = "ICH0",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH2] = अणु
		.name = "ICH2",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH2M] = अणु
		.name = "ICH2-M",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH3] = अणु
		.name = "ICH3-S",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH3M] = अणु
		.name = "ICH3-M",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH4] = अणु
		.name = "ICH4",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH4M] = अणु
		.name = "ICH4-M",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_CICH] = अणु
		.name = "C-ICH",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH5] = अणु
		.name = "ICH5 or ICH5R",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_6300ESB] = अणु
		.name = "6300ESB",
		.iTCO_version = 1,
	पूर्ण,
	[LPC_ICH6] = अणु
		.name = "ICH6 or ICH6R",
		.iTCO_version = 2,
		.gpio_version = ICH_V6_GPIO,
	पूर्ण,
	[LPC_ICH6M] = अणु
		.name = "ICH6-M",
		.iTCO_version = 2,
		.gpio_version = ICH_V6_GPIO,
	पूर्ण,
	[LPC_ICH6W] = अणु
		.name = "ICH6W or ICH6RW",
		.iTCO_version = 2,
		.gpio_version = ICH_V6_GPIO,
	पूर्ण,
	[LPC_631XESB] = अणु
		.name = "631xESB/632xESB",
		.iTCO_version = 2,
		.gpio_version = ICH_V6_GPIO,
	पूर्ण,
	[LPC_ICH7] = अणु
		.name = "ICH7 or ICH7R",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH7DH] = अणु
		.name = "ICH7DH",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH7M] = अणु
		.name = "ICH7-M or ICH7-U",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH7MDH] = अणु
		.name = "ICH7-M DH",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_NM10] = अणु
		.name = "NM10",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH8] = अणु
		.name = "ICH8 or ICH8R",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH8DH] = अणु
		.name = "ICH8DH",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH8DO] = अणु
		.name = "ICH8DO",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH8M] = अणु
		.name = "ICH8M",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH8ME] = अणु
		.name = "ICH8M-E",
		.iTCO_version = 2,
		.gpio_version = ICH_V7_GPIO,
	पूर्ण,
	[LPC_ICH9] = अणु
		.name = "ICH9",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH9R] = अणु
		.name = "ICH9R",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH9DH] = अणु
		.name = "ICH9DH",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH9DO] = अणु
		.name = "ICH9DO",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH9M] = अणु
		.name = "ICH9M",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH9ME] = अणु
		.name = "ICH9M-E",
		.iTCO_version = 2,
		.gpio_version = ICH_V9_GPIO,
	पूर्ण,
	[LPC_ICH10] = अणु
		.name = "ICH10",
		.iTCO_version = 2,
		.gpio_version = ICH_V10CONS_GPIO,
	पूर्ण,
	[LPC_ICH10R] = अणु
		.name = "ICH10R",
		.iTCO_version = 2,
		.gpio_version = ICH_V10CONS_GPIO,
	पूर्ण,
	[LPC_ICH10D] = अणु
		.name = "ICH10D",
		.iTCO_version = 2,
		.gpio_version = ICH_V10CORP_GPIO,
	पूर्ण,
	[LPC_ICH10DO] = अणु
		.name = "ICH10DO",
		.iTCO_version = 2,
		.gpio_version = ICH_V10CORP_GPIO,
	पूर्ण,
	[LPC_PCH] = अणु
		.name = "PCH Desktop Full Featured",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_PCHM] = अणु
		.name = "PCH Mobile Full Featured",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_P55] = अणु
		.name = "P55",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_PM55] = अणु
		.name = "PM55",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_H55] = अणु
		.name = "H55",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_QM57] = अणु
		.name = "QM57",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_H57] = अणु
		.name = "H57",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_HM55] = अणु
		.name = "HM55",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_Q57] = अणु
		.name = "Q57",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_HM57] = अणु
		.name = "HM57",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_PCHMSFF] = अणु
		.name = "PCH Mobile SFF Full Featured",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_QS57] = अणु
		.name = "QS57",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_3400] = अणु
		.name = "3400",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_3420] = अणु
		.name = "3420",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_3450] = अणु
		.name = "3450",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_EP80579] = अणु
		.name = "EP80579",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_CPT] = अणु
		.name = "Cougar Point",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_CPTD] = अणु
		.name = "Cougar Point Desktop",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_CPTM] = अणु
		.name = "Cougar Point Mobile",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_PBG] = अणु
		.name = "Patsburg",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_DH89XXCC] = अणु
		.name = "DH89xxCC",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_PPT] = अणु
		.name = "Panther Point",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_LPT] = अणु
		.name = "Lynx Point",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
		.spi_type = INTEL_SPI_LPT,
	पूर्ण,
	[LPC_LPT_LP] = अणु
		.name = "Lynx Point_LP",
		.iTCO_version = 2,
		.spi_type = INTEL_SPI_LPT,
	पूर्ण,
	[LPC_WBG] = अणु
		.name = "Wellsburg",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_AVN] = अणु
		.name = "Avoton SoC",
		.iTCO_version = 3,
		.gpio_version = AVOTON_GPIO,
		.spi_type = INTEL_SPI_BYT,
	पूर्ण,
	[LPC_BAYTRAIL] = अणु
		.name = "Bay Trail SoC",
		.iTCO_version = 3,
		.spi_type = INTEL_SPI_BYT,
	पूर्ण,
	[LPC_COLETO] = अणु
		.name = "Coleto Creek",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_WPT_LP] = अणु
		.name = "Wildcat Point_LP",
		.iTCO_version = 2,
		.spi_type = INTEL_SPI_LPT,
	पूर्ण,
	[LPC_BRASWELL] = अणु
		.name = "Braswell SoC",
		.iTCO_version = 3,
		.spi_type = INTEL_SPI_BYT,
	पूर्ण,
	[LPC_LEWISBURG] = अणु
		.name = "Lewisburg",
		.iTCO_version = 2,
	पूर्ण,
	[LPC_9S] = अणु
		.name = "9 Series",
		.iTCO_version = 2,
		.gpio_version = ICH_V5_GPIO,
	पूर्ण,
	[LPC_APL] = अणु
		.name = "Apollo Lake SoC",
		.iTCO_version = 5,
		.spi_type = INTEL_SPI_BXT,
	पूर्ण,
	[LPC_GLK] = अणु
		.name = "Gemini Lake SoC",
		.spi_type = INTEL_SPI_BXT,
	पूर्ण,
	[LPC_COUGARMOUNTAIN] = अणु
		.name = "Cougar Mountain SoC",
		.iTCO_version = 3,
	पूर्ण,
पूर्ण;

/*
 * This data only exists क्रम exporting the supported PCI ids
 * via MODULE_DEVICE_TABLE.  We करो not actually रेजिस्टर a
 * pci_driver, because the I/O Controller Hub has also other
 * functions that probably will be रेजिस्टरed by other drivers.
 */
अटल स्थिर काष्ठा pci_device_id lpc_ich_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0f1c), LPC_BAYTRAILपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c41), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c42), LPC_CPTDपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c43), LPC_CPTMपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c44), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c45), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c46), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c47), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c48), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c49), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4a), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4b), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4c), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4d), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4e), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c4f), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c50), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c51), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c52), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c53), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c54), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c55), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c56), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c57), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c58), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c59), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5a), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5b), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5c), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5d), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5e), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1c5f), LPC_CPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1d40), LPC_PBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1d41), LPC_PBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e40), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e41), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e42), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e43), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e44), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e45), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e46), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e47), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e48), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e49), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4a), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4b), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4c), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4d), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4e), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e4f), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e50), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e51), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e52), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e53), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e54), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e55), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e56), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e57), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e58), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e59), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5a), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5b), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5c), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5d), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5e), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1e5f), LPC_PPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1f38), LPC_AVNपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1f39), LPC_AVNपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1f3a), LPC_AVNपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1f3b), LPC_AVNपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x229c), LPC_BRASWELLपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2310), LPC_DH89XXCCपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2390), LPC_COLETOपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2410), LPC_ICHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2420), LPC_ICH0पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2440), LPC_ICH2पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x244c), LPC_ICH2Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2450), LPC_CICHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2480), LPC_ICH3पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x248c), LPC_ICH3Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x24c0), LPC_ICH4पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x24cc), LPC_ICH4Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x24d0), LPC_ICH5पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x25a1), LPC_6300ESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2640), LPC_ICH6पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2641), LPC_ICH6Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2642), LPC_ICH6Wपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2670), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2671), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2672), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2673), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2674), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2675), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2676), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2677), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2678), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2679), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267a), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267b), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267c), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267d), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267e), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x267f), LPC_631XESBपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x27b0), LPC_ICH7DHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x27b8), LPC_ICH7पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x27b9), LPC_ICH7Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x27bc), LPC_NM10पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x27bd), LPC_ICH7MDHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2810), LPC_ICH8पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2811), LPC_ICH8MEपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2812), LPC_ICH8DHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2814), LPC_ICH8DOपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2815), LPC_ICH8Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2912), LPC_ICH9DHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2914), LPC_ICH9DOपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2916), LPC_ICH9Rपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2917), LPC_ICH9MEपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2918), LPC_ICH9पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2919), LPC_ICH9Mपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3197), LPC_GLKपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x2b9c), LPC_COUGARMOUNTAINपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3a14), LPC_ICH10DOपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3a16), LPC_ICH10Rपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3a18), LPC_ICH10पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3a1a), LPC_ICH10Dपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b00), LPC_PCHपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b01), LPC_PCHMपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b02), LPC_P55पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b03), LPC_PM55पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b06), LPC_H55पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b07), LPC_QM57पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b08), LPC_H57पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b09), LPC_HM55पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b0a), LPC_Q57पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b0b), LPC_HM57पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b0d), LPC_PCHMSFFपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b0f), LPC_QS57पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b12), LPC_3400पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b14), LPC_3420पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3b16), LPC_3450पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5031), LPC_EP80579पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ae8), LPC_APLपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c40), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c41), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c42), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c43), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c44), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c45), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c46), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c47), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c48), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c49), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4a), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4b), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4c), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4d), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4e), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c4f), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c50), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c51), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c52), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c53), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c54), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c55), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c56), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c57), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c58), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c59), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5a), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5b), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5c), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5d), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5e), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8c5f), LPC_LPTपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8cc1), LPC_9Sपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8cc2), LPC_9Sपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8cc3), LPC_9Sपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8cc4), LPC_9Sपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8cc6), LPC_9Sपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d40), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d41), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d42), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d43), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d44), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d45), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d46), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d47), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d48), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d49), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4a), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4b), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4c), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4d), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4e), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d4f), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d50), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d51), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d52), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d53), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d54), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d55), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d56), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d57), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d58), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d59), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5a), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5b), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5c), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5d), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5e), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x8d5f), LPC_WBGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c40), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c41), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c42), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c43), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c44), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c45), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c46), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9c47), LPC_LPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc1), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc2), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc3), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc5), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc6), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc7), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9cc9), LPC_WPT_LPपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c1), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c2), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c3), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c4), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c5), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c6), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1c7), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa242), LPC_LEWISBURGपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa243), LPC_LEWISBURGपूर्ण,
	अणु 0, पूर्ण,			/* End of list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, lpc_ich_ids);

अटल व्योम lpc_ich_restore_config_space(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);

	अगर (priv->abase_save >= 0) अणु
		pci_ग_लिखो_config_byte(dev, priv->abase, priv->abase_save);
		priv->abase_save = -1;
	पूर्ण

	अगर (priv->actrl_pbase_save >= 0) अणु
		pci_ग_लिखो_config_byte(dev, priv->actrl_pbase,
			priv->actrl_pbase_save);
		priv->actrl_pbase_save = -1;
	पूर्ण

	अगर (priv->gctrl_save >= 0) अणु
		pci_ग_लिखो_config_byte(dev, priv->gctrl, priv->gctrl_save);
		priv->gctrl_save = -1;
	पूर्ण
पूर्ण

अटल व्योम lpc_ich_enable_acpi_space(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	u8 reg_save;

	चयन (lpc_chipset_info[priv->chipset].iTCO_version) अणु
	हाल 3:
		/*
		 * Some chipsets (eg Avoton) enable the ACPI space in the
		 * ACPI BASE रेजिस्टर.
		 */
		pci_पढ़ो_config_byte(dev, priv->abase, &reg_save);
		pci_ग_लिखो_config_byte(dev, priv->abase, reg_save | 0x2);
		priv->abase_save = reg_save;
		अवरोध;
	शेष:
		/*
		 * Most chipsets enable the ACPI space in the ACPI control
		 * रेजिस्टर.
		 */
		pci_पढ़ो_config_byte(dev, priv->actrl_pbase, &reg_save);
		pci_ग_लिखो_config_byte(dev, priv->actrl_pbase, reg_save | 0x80);
		priv->actrl_pbase_save = reg_save;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lpc_ich_enable_gpio_space(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	u8 reg_save;

	pci_पढ़ो_config_byte(dev, priv->gctrl, &reg_save);
	pci_ग_लिखो_config_byte(dev, priv->gctrl, reg_save | 0x10);
	priv->gctrl_save = reg_save;
पूर्ण

अटल व्योम lpc_ich_enable_pmc_space(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	u8 reg_save;

	pci_पढ़ो_config_byte(dev, priv->actrl_pbase, &reg_save);
	pci_ग_लिखो_config_byte(dev, priv->actrl_pbase, reg_save | 0x2);

	priv->actrl_pbase_save = reg_save;
पूर्ण

अटल पूर्णांक lpc_ich_finalize_wdt_cell(काष्ठा pci_dev *dev)
अणु
	काष्ठा itco_wdt_platक्रमm_data *pdata;
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	काष्ठा lpc_ich_info *info;
	काष्ठा mfd_cell *cell = &lpc_ich_wdt_cell;

	pdata = devm_kzalloc(&dev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	info = &lpc_chipset_info[priv->chipset];

	pdata->version = info->iTCO_version;
	strlcpy(pdata->name, info->name, माप(pdata->name));

	cell->platक्रमm_data = pdata;
	cell->pdata_size = माप(*pdata);
	वापस 0;
पूर्ण

अटल व्योम lpc_ich_finalize_gpio_cell(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	काष्ठा mfd_cell *cell = &lpc_ich_gpio_cell;

	cell->platक्रमm_data = &lpc_chipset_info[priv->chipset];
	cell->pdata_size = माप(काष्ठा lpc_ich_info);
पूर्ण

/*
 * We करोn't check क्रम resource conflict globally. There are 2 or 3 independent
 * GPIO groups and it's enough to have access to one of these to instantiate
 * the device.
 */
अटल पूर्णांक lpc_ich_check_conflict_gpio(काष्ठा resource *res)
अणु
	पूर्णांक ret;
	u8 use_gpio = 0;

	अगर (resource_size(res) >= 0x50 &&
	    !acpi_check_region(res->start + 0x40, 0x10, "LPC ICH GPIO3"))
		use_gpio |= 1 << 2;

	अगर (!acpi_check_region(res->start + 0x30, 0x10, "LPC ICH GPIO2"))
		use_gpio |= 1 << 1;

	ret = acpi_check_region(res->start + 0x00, 0x30, "LPC ICH GPIO1");
	अगर (!ret)
		use_gpio |= 1 << 0;

	वापस use_gpio ? use_gpio : ret;
पूर्ण

अटल पूर्णांक lpc_ich_init_gpio(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	u32 base_addr_cfg;
	u32 base_addr;
	पूर्णांक ret;
	bool acpi_conflict = false;
	काष्ठा resource *res;

	/* Setup घातer management base रेजिस्टर */
	pci_पढ़ो_config_dword(dev, priv->abase, &base_addr_cfg);
	base_addr = base_addr_cfg & 0x0000ff80;
	अगर (!base_addr) अणु
		dev_notice(&dev->dev, "I/O space for ACPI uninitialized\n");
		lpc_ich_gpio_cell.num_resources--;
		जाओ gpe0_करोne;
	पूर्ण

	res = &gpio_ich_res[ICH_RES_GPE0];
	res->start = base_addr + ACPIBASE_GPE_OFF;
	res->end = base_addr + ACPIBASE_GPE_END;
	ret = acpi_check_resource_conflict(res);
	अगर (ret) अणु
		/*
		 * This isn't fatal क्रम the GPIO, but we have to make sure that
		 * the platक्रमm_device subप्रणाली करोesn't see this resource
		 * or it will रेजिस्टर an invalid region.
		 */
		lpc_ich_gpio_cell.num_resources--;
		acpi_conflict = true;
	पूर्ण अन्यथा अणु
		lpc_ich_enable_acpi_space(dev);
	पूर्ण

gpe0_करोne:
	/* Setup GPIO base रेजिस्टर */
	pci_पढ़ो_config_dword(dev, priv->gbase, &base_addr_cfg);
	base_addr = base_addr_cfg & 0x0000ff80;
	अगर (!base_addr) अणु
		dev_notice(&dev->dev, "I/O space for GPIO uninitialized\n");
		ret = -ENODEV;
		जाओ gpio_करोne;
	पूर्ण

	/* Older devices provide fewer GPIO and have a smaller resource size. */
	res = &gpio_ich_res[ICH_RES_GPIO];
	res->start = base_addr;
	चयन (lpc_chipset_info[priv->chipset].gpio_version) अणु
	हाल ICH_V5_GPIO:
	हाल ICH_V10CORP_GPIO:
		res->end = res->start + 128 - 1;
		अवरोध;
	शेष:
		res->end = res->start + 64 - 1;
		अवरोध;
	पूर्ण

	ret = lpc_ich_check_conflict_gpio(res);
	अगर (ret < 0) अणु
		/* this isn't necessarily fatal क्रम the GPIO */
		acpi_conflict = true;
		जाओ gpio_करोne;
	पूर्ण
	lpc_chipset_info[priv->chipset].use_gpio = ret;
	lpc_ich_enable_gpio_space(dev);

	lpc_ich_finalize_gpio_cell(dev);
	ret = mfd_add_devices(&dev->dev, PLATFORM_DEVID_AUTO,
			      &lpc_ich_gpio_cell, 1, शून्य, 0, शून्य);

gpio_करोne:
	अगर (acpi_conflict)
		pr_warn("Resource conflict(s) found affecting %s\n",
				lpc_ich_gpio_cell.name);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc_ich_init_wdt(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	u32 base_addr_cfg;
	u32 base_addr;
	पूर्णांक ret;
	काष्ठा resource *res;

	/* If we have ACPI based watchकरोg use that instead */
	अगर (acpi_has_watchकरोg())
		वापस -ENODEV;

	/* Setup घातer management base रेजिस्टर */
	pci_पढ़ो_config_dword(dev, priv->abase, &base_addr_cfg);
	base_addr = base_addr_cfg & 0x0000ff80;
	अगर (!base_addr) अणु
		dev_notice(&dev->dev, "I/O space for ACPI uninitialized\n");
		ret = -ENODEV;
		जाओ wdt_करोne;
	पूर्ण

	res = wdt_io_res(ICH_RES_IO_TCO);
	res->start = base_addr + ACPIBASE_TCO_OFF;
	res->end = base_addr + ACPIBASE_TCO_END;

	res = wdt_io_res(ICH_RES_IO_SMI);
	res->start = base_addr + ACPIBASE_SMI_OFF;
	res->end = base_addr + ACPIBASE_SMI_END;

	lpc_ich_enable_acpi_space(dev);

	/*
	 * iTCO v2:
	 * Get the Memory-Mapped GCS रेजिस्टर. To get access to it
	 * we have to पढ़ो RCBA from PCI Config space 0xf0 and use
	 * it as base. GCS = RCBA + ICH6_GCS(0x3410).
	 *
	 * iTCO v3:
	 * Get the Power Management Configuration रेजिस्टर.  To get access
	 * to it we have to पढ़ो the PMC BASE from config space and address
	 * the रेजिस्टर at offset 0x8.
	 */
	अगर (lpc_chipset_info[priv->chipset].iTCO_version == 1) अणु
		/* Don't रेजिस्टर iomem क्रम TCO ver 1 */
		lpc_ich_wdt_cell.num_resources--;
	पूर्ण अन्यथा अगर (lpc_chipset_info[priv->chipset].iTCO_version == 2) अणु
		pci_पढ़ो_config_dword(dev, RCBABASE, &base_addr_cfg);
		base_addr = base_addr_cfg & 0xffffc000;
		अगर (!(base_addr_cfg & 1)) अणु
			dev_notice(&dev->dev, "RCBA is disabled by "
					"hardware/BIOS, device disabled\n");
			ret = -ENODEV;
			जाओ wdt_करोne;
		पूर्ण
		res = wdt_mem_res(ICH_RES_MEM_GCS_PMC);
		res->start = base_addr + ACPIBASE_GCS_OFF;
		res->end = base_addr + ACPIBASE_GCS_END;
	पूर्ण अन्यथा अगर (lpc_chipset_info[priv->chipset].iTCO_version == 3) अणु
		lpc_ich_enable_pmc_space(dev);
		pci_पढ़ो_config_dword(dev, ACPICTRL_PMCBASE, &base_addr_cfg);
		base_addr = base_addr_cfg & 0xfffffe00;

		res = wdt_mem_res(ICH_RES_MEM_GCS_PMC);
		res->start = base_addr + ACPIBASE_PMC_OFF;
		res->end = base_addr + ACPIBASE_PMC_END;
	पूर्ण

	ret = lpc_ich_finalize_wdt_cell(dev);
	अगर (ret)
		जाओ wdt_करोne;

	ret = mfd_add_devices(&dev->dev, PLATFORM_DEVID_AUTO,
			      &lpc_ich_wdt_cell, 1, शून्य, 0, शून्य);

wdt_करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक lpc_ich_init_spi(काष्ठा pci_dev *dev)
अणु
	काष्ठा lpc_ich_priv *priv = pci_get_drvdata(dev);
	काष्ठा resource *res = &पूर्णांकel_spi_res[0];
	काष्ठा पूर्णांकel_spi_boardinfo *info;
	u32 spi_base, rcba, bcr;

	info = devm_kzalloc(&dev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->type = lpc_chipset_info[priv->chipset].spi_type;

	चयन (info->type) अणु
	हाल INTEL_SPI_BYT:
		pci_पढ़ो_config_dword(dev, SPIBASE_BYT, &spi_base);
		अगर (spi_base & SPIBASE_BYT_EN) अणु
			res->start = spi_base & ~(SPIBASE_BYT_SZ - 1);
			res->end = res->start + SPIBASE_BYT_SZ - 1;
		पूर्ण
		अवरोध;

	हाल INTEL_SPI_LPT:
		pci_पढ़ो_config_dword(dev, RCBABASE, &rcba);
		अगर (rcba & 1) अणु
			spi_base = round_करोwn(rcba, SPIBASE_LPT_SZ);
			res->start = spi_base + SPIBASE_LPT;
			res->end = res->start + SPIBASE_LPT_SZ - 1;

			pci_पढ़ो_config_dword(dev, BCR, &bcr);
			info->ग_लिखोable = !!(bcr & BCR_WPD);
		पूर्ण
		अवरोध;

	हाल INTEL_SPI_BXT: अणु
		अचिन्हित पूर्णांक p2sb = PCI_DEVFN(13, 0);
		अचिन्हित पूर्णांक spi = PCI_DEVFN(13, 2);
		काष्ठा pci_bus *bus = dev->bus;

		/*
		 * The P2SB is hidden by BIOS and we need to unhide it in
		 * order to पढ़ो BAR of the SPI flash device. Once that is
		 * करोne we hide it again.
		 */
		pci_bus_ग_लिखो_config_byte(bus, p2sb, 0xe1, 0x0);
		pci_bus_पढ़ो_config_dword(bus, spi, PCI_BASE_ADDRESS_0,
					  &spi_base);
		अगर (spi_base != ~0) अणु
			res->start = spi_base & 0xfffffff0;
			res->end = res->start + SPIBASE_APL_SZ - 1;

			pci_bus_पढ़ो_config_dword(bus, spi, BCR, &bcr);
			info->ग_लिखोable = !!(bcr & BCR_WPD);
		पूर्ण

		pci_bus_ग_लिखो_config_byte(bus, p2sb, 0xe1, 0x1);
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!res->start)
		वापस -ENODEV;

	lpc_ich_spi_cell.platक्रमm_data = info;
	lpc_ich_spi_cell.pdata_size = माप(*info);

	वापस mfd_add_devices(&dev->dev, PLATFORM_DEVID_NONE,
			       &lpc_ich_spi_cell, 1, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक lpc_ich_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा lpc_ich_priv *priv;
	पूर्णांक ret;
	bool cell_added = false;

	priv = devm_kzalloc(&dev->dev,
			    माप(काष्ठा lpc_ich_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->chipset = id->driver_data;

	priv->actrl_pbase_save = -1;
	priv->abase_save = -1;

	priv->abase = ACPIBASE;
	priv->actrl_pbase = ACPICTRL_PMCBASE;

	priv->gctrl_save = -1;
	अगर (priv->chipset <= LPC_ICH5) अणु
		priv->gbase = GPIOBASE_ICH0;
		priv->gctrl = GPIOCTRL_ICH0;
	पूर्ण अन्यथा अणु
		priv->gbase = GPIOBASE_ICH6;
		priv->gctrl = GPIOCTRL_ICH6;
	पूर्ण

	pci_set_drvdata(dev, priv);

	अगर (lpc_chipset_info[priv->chipset].iTCO_version) अणु
		ret = lpc_ich_init_wdt(dev);
		अगर (!ret)
			cell_added = true;
	पूर्ण

	अगर (lpc_chipset_info[priv->chipset].gpio_version) अणु
		ret = lpc_ich_init_gpio(dev);
		अगर (!ret)
			cell_added = true;
	पूर्ण

	अगर (lpc_chipset_info[priv->chipset].spi_type) अणु
		ret = lpc_ich_init_spi(dev);
		अगर (!ret)
			cell_added = true;
	पूर्ण

	/*
	 * We only care अगर at least one or none of the cells रेजिस्टरed
	 * successfully.
	 */
	अगर (!cell_added) अणु
		dev_warn(&dev->dev, "No MFD cells added\n");
		lpc_ich_restore_config_space(dev);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lpc_ich_हटाओ(काष्ठा pci_dev *dev)
अणु
	mfd_हटाओ_devices(&dev->dev);
	lpc_ich_restore_config_space(dev);
पूर्ण

अटल काष्ठा pci_driver lpc_ich_driver = अणु
	.name		= "lpc_ich",
	.id_table	= lpc_ich_ids,
	.probe		= lpc_ich_probe,
	.हटाओ		= lpc_ich_हटाओ,
पूर्ण;

module_pci_driver(lpc_ich_driver);

MODULE_AUTHOR("Aaron Sierra <asierra@xes-inc.com>");
MODULE_DESCRIPTION("LPC interface for Intel ICH");
MODULE_LICENSE("GPL");
