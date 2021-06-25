<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Exynos ARMv8 specअगरic support क्रम Samsung pinctrl/gpiolib driver
// with eपूर्णांक support.
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
// Copyright (c) 2012 Linaro Ltd
//		http://www.linaro.org
// Copyright (c) 2017 Krzysztof Kozlowski <krzk@kernel.org>
//
// This file contains the Samsung Exynos specअगरic inक्रमmation required by the
// the Samsung pinctrl/gpiolib driver. It also includes the implementation of
// बाह्यal gpio and wakeup पूर्णांकerrupt support.

#समावेश <linux/slab.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश "pinctrl-samsung.h"
#समावेश "pinctrl-exynos.h"

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_off = अणु
	.fld_width = अणु 4, 1, 2, 2, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_alive = अणु
	.fld_width = अणु 4, 1, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0x0c, पूर्ण,
पूर्ण;

/* Exynos5433 has the 4bit widths क्रम PINCFG_TYPE_DRV bitfields. */
अटल स्थिर काष्ठा samsung_pin_bank_type exynos5433_bank_type_off = अणु
	.fld_width = अणु 4, 1, 2, 4, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type exynos5433_bank_type_alive = अणु
	.fld_width = अणु 4, 1, 2, 4, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0x0c, पूर्ण,
पूर्ण;

/* Pad retention control code क्रम accessing PMU regmap */
अटल atomic_t exynos_shared_retention_refcnt;

/* pin banks of exynos5433 pin-controller - ALIVE */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks0[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x020, "gpa1", 0x04),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x040, "gpa2", 0x08),
	EXYNOS5433_PIN_BANK_EINTW(8, 0x060, "gpa3", 0x0c),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x020, "gpf1", 0x1004, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(4, 0x040, "gpf2", 0x1008, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(4, 0x060, "gpf3", 0x100c, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x080, "gpf4", 0x1010, 1),
	EXYNOS5433_PIN_BANK_EINTW_EXT(8, 0x0a0, "gpf5", 0x1014, 1),
पूर्ण;

/* pin banks of exynos5433 pin-controller - AUD */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks1[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(7, 0x000, "gpz0", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(4, 0x020, "gpz1", 0x04),
पूर्ण;

/* pin banks of exynos5433 pin-controller - CPIF */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks2[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(2, 0x000, "gpv6", 0x00),
पूर्ण;

/* pin banks of exynos5433 pin-controller - eSE */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks3[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj2", 0x00),
पूर्ण;

/* pin banks of exynos5433 pin-controller - FINGER */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks4[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(4, 0x000, "gpd5", 0x00),
पूर्ण;

/* pin banks of exynos5433 pin-controller - FSYS */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks5[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(6, 0x000, "gph1", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(7, 0x020, "gpr4", 0x04),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x040, "gpr0", 0x08),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x060, "gpr1", 0x0c),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x080, "gpr2", 0x10),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x0a0, "gpr3", 0x14),
पूर्ण;

/* pin banks of exynos5433 pin-controller - IMEM */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks6[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(8, 0x000, "gpf0", 0x00),
पूर्ण;

/* pin banks of exynos5433 pin-controller - NFC */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks7[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj0", 0x00),
पूर्ण;

/* pin banks of exynos5433 pin-controller - PERIC */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks8[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(6, 0x000, "gpv7", 0x00),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x020, "gpb0", 0x04),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x040, "gpc0", 0x08),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x060, "gpc1", 0x0c),
	EXYNOS5433_PIN_BANK_EINTG(6, 0x080, "gpc2", 0x10),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x0a0, "gpc3", 0x14),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x0c0, "gpg0", 0x18),
	EXYNOS5433_PIN_BANK_EINTG(4, 0x0e0, "gpd0", 0x1c),
	EXYNOS5433_PIN_BANK_EINTG(6, 0x100, "gpd1", 0x20),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x120, "gpd2", 0x24),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x140, "gpd4", 0x28),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x160, "gpd8", 0x2c),
	EXYNOS5433_PIN_BANK_EINTG(7, 0x180, "gpd6", 0x30),
	EXYNOS5433_PIN_BANK_EINTG(3, 0x1a0, "gpd7", 0x34),
	EXYNOS5433_PIN_BANK_EINTG(5, 0x1c0, "gpg1", 0x38),
	EXYNOS5433_PIN_BANK_EINTG(2, 0x1e0, "gpg2", 0x3c),
	EXYNOS5433_PIN_BANK_EINTG(8, 0x200, "gpg3", 0x40),
पूर्ण;

/* pin banks of exynos5433 pin-controller - TOUCH */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos5433_pin_banks9[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS5433_PIN_BANK_EINTG(3, 0x000, "gpj1", 0x00),
पूर्ण;

/* PMU pin retention groups रेजिस्टरs क्रम Exynos5433 (without audio & fsys) */
अटल स्थिर u32 exynos5433_retention_regs[] = अणु
	EXYNOS5433_PAD_RETENTION_TOP_OPTION,
	EXYNOS5433_PAD_RETENTION_UART_OPTION,
	EXYNOS5433_PAD_RETENTION_EBIA_OPTION,
	EXYNOS5433_PAD_RETENTION_EBIB_OPTION,
	EXYNOS5433_PAD_RETENTION_SPI_OPTION,
	EXYNOS5433_PAD_RETENTION_MIF_OPTION,
	EXYNOS5433_PAD_RETENTION_USBXTI_OPTION,
	EXYNOS5433_PAD_RETENTION_BOOTLDO_OPTION,
	EXYNOS5433_PAD_RETENTION_UFS_OPTION,
	EXYNOS5433_PAD_RETENTION_FSYSGENIO_OPTION,
पूर्ण;

अटल स्थिर काष्ठा samsung_retention_data exynos5433_retention_data __initस्थिर = अणु
	.regs	 = exynos5433_retention_regs,
	.nr_regs = ARRAY_SIZE(exynos5433_retention_regs),
	.value	 = EXYNOS_WAKEUP_FROM_LOWPWR,
	.refcnt	 = &exynos_shared_retention_refcnt,
	.init	 = exynos_retention_init,
पूर्ण;

/* PMU retention control क्रम audio pins can be tied to audio pin bank */
अटल स्थिर u32 exynos5433_audio_retention_regs[] = अणु
	EXYNOS5433_PAD_RETENTION_AUD_OPTION,
पूर्ण;

अटल स्थिर काष्ठा samsung_retention_data exynos5433_audio_retention_data __initस्थिर = अणु
	.regs	 = exynos5433_audio_retention_regs,
	.nr_regs = ARRAY_SIZE(exynos5433_audio_retention_regs),
	.value	 = EXYNOS_WAKEUP_FROM_LOWPWR,
	.init	 = exynos_retention_init,
पूर्ण;

/* PMU retention control क्रम mmc pins can be tied to fsys pin bank */
अटल स्थिर u32 exynos5433_fsys_retention_regs[] = अणु
	EXYNOS5433_PAD_RETENTION_MMC0_OPTION,
	EXYNOS5433_PAD_RETENTION_MMC1_OPTION,
	EXYNOS5433_PAD_RETENTION_MMC2_OPTION,
पूर्ण;

अटल स्थिर काष्ठा samsung_retention_data exynos5433_fsys_retention_data __initस्थिर = अणु
	.regs	 = exynos5433_fsys_retention_regs,
	.nr_regs = ARRAY_SIZE(exynos5433_fsys_retention_regs),
	.value	 = EXYNOS_WAKEUP_FROM_LOWPWR,
	.init	 = exynos_retention_init,
पूर्ण;

/*
 * Samsung pinctrl driver data क्रम Exynos5433 SoC. Exynos5433 SoC includes
 * ten gpio/pin-mux/pinconfig controllers.
 */
अटल स्थिर काष्ठा samsung_pin_ctrl exynos5433_pin_ctrl[] __initस्थिर = अणु
	अणु
		/* pin-controller instance 0 data */
		.pin_banks	= exynos5433_pin_banks0,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks0),
		.eपूर्णांक_wkup_init = exynos_eपूर्णांक_wkup_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.nr_ext_resources = 1,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 1 data */
		.pin_banks	= exynos5433_pin_banks1,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks1),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_audio_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 2 data */
		.pin_banks	= exynos5433_pin_banks2,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks2),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 3 data */
		.pin_banks	= exynos5433_pin_banks3,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks3),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 4 data */
		.pin_banks	= exynos5433_pin_banks4,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks4),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 5 data */
		.pin_banks	= exynos5433_pin_banks5,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks5),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_fsys_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 6 data */
		.pin_banks	= exynos5433_pin_banks6,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks6),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 7 data */
		.pin_banks	= exynos5433_pin_banks7,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks7),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 8 data */
		.pin_banks	= exynos5433_pin_banks8,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks8),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण, अणु
		/* pin-controller instance 9 data */
		.pin_banks	= exynos5433_pin_banks9,
		.nr_banks	= ARRAY_SIZE(exynos5433_pin_banks9),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
		.suspend	= exynos_pinctrl_suspend,
		.resume		= exynos_pinctrl_resume,
		.retention_data	= &exynos5433_retention_data,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5433_of_data __initस्थिर = अणु
	.ctrl		= exynos5433_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(exynos5433_pin_ctrl),
पूर्ण;

/* pin banks of exynos7 pin-controller - ALIVE */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks0[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTW(8, 0x000, "gpa0", 0x00),
	EXYNOS_PIN_BANK_EINTW(8, 0x020, "gpa1", 0x04),
	EXYNOS_PIN_BANK_EINTW(8, 0x040, "gpa2", 0x08),
	EXYNOS_PIN_BANK_EINTW(8, 0x060, "gpa3", 0x0c),
पूर्ण;

/* pin banks of exynos7 pin-controller - BUS0 */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks1[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(5, 0x000, "gpb0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpc0", 0x04),
	EXYNOS_PIN_BANK_EINTG(2, 0x040, "gpc1", 0x08),
	EXYNOS_PIN_BANK_EINTG(6, 0x060, "gpc2", 0x0c),
	EXYNOS_PIN_BANK_EINTG(8, 0x080, "gpc3", 0x10),
	EXYNOS_PIN_BANK_EINTG(4, 0x0a0, "gpd0", 0x14),
	EXYNOS_PIN_BANK_EINTG(6, 0x0c0, "gpd1", 0x18),
	EXYNOS_PIN_BANK_EINTG(8, 0x0e0, "gpd2", 0x1c),
	EXYNOS_PIN_BANK_EINTG(5, 0x100, "gpd4", 0x20),
	EXYNOS_PIN_BANK_EINTG(4, 0x120, "gpd5", 0x24),
	EXYNOS_PIN_BANK_EINTG(6, 0x140, "gpd6", 0x28),
	EXYNOS_PIN_BANK_EINTG(3, 0x160, "gpd7", 0x2c),
	EXYNOS_PIN_BANK_EINTG(2, 0x180, "gpd8", 0x30),
	EXYNOS_PIN_BANK_EINTG(2, 0x1a0, "gpg0", 0x34),
	EXYNOS_PIN_BANK_EINTG(4, 0x1c0, "gpg3", 0x38),
पूर्ण;

/* pin banks of exynos7 pin-controller - NFC */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks2[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(3, 0x000, "gpj0", 0x00),
पूर्ण;

/* pin banks of exynos7 pin-controller - TOUCH */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks3[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(3, 0x000, "gpj1", 0x00),
पूर्ण;

/* pin banks of exynos7 pin-controller - FF */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks4[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(4, 0x000, "gpg4", 0x00),
पूर्ण;

/* pin banks of exynos7 pin-controller - ESE */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks5[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(5, 0x000, "gpv7", 0x00),
पूर्ण;

/* pin banks of exynos7 pin-controller - FSYS0 */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks6[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(7, 0x000, "gpr4", 0x00),
पूर्ण;

/* pin banks of exynos7 pin-controller - FSYS1 */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks7[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(4, 0x000, "gpr0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpr1", 0x04),
	EXYNOS_PIN_BANK_EINTG(5, 0x040, "gpr2", 0x08),
	EXYNOS_PIN_BANK_EINTG(8, 0x060, "gpr3", 0x0c),
पूर्ण;

/* pin banks of exynos7 pin-controller - BUS1 */
अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks8[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(8, 0x020, "gpf0", 0x00),
	EXYNOS_PIN_BANK_EINTG(8, 0x040, "gpf1", 0x04),
	EXYNOS_PIN_BANK_EINTG(4, 0x060, "gpf2", 0x08),
	EXYNOS_PIN_BANK_EINTG(5, 0x080, "gpf3", 0x0c),
	EXYNOS_PIN_BANK_EINTG(8, 0x0a0, "gpf4", 0x10),
	EXYNOS_PIN_BANK_EINTG(8, 0x0c0, "gpf5", 0x14),
	EXYNOS_PIN_BANK_EINTG(5, 0x0e0, "gpg1", 0x18),
	EXYNOS_PIN_BANK_EINTG(5, 0x100, "gpg2", 0x1c),
	EXYNOS_PIN_BANK_EINTG(6, 0x120, "gph1", 0x20),
	EXYNOS_PIN_BANK_EINTG(3, 0x140, "gpv6", 0x24),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_data exynos7_pin_banks9[] __initस्थिर = अणु
	/* Must start with EINTG banks, ordered by EINT group number. */
	EXYNOS_PIN_BANK_EINTG(7, 0x000, "gpz0", 0x00),
	EXYNOS_PIN_BANK_EINTG(4, 0x020, "gpz1", 0x04),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_ctrl exynos7_pin_ctrl[] __initस्थिर = अणु
	अणु
		/* pin-controller instance 0 Alive data */
		.pin_banks	= exynos7_pin_banks0,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks0),
		.eपूर्णांक_wkup_init = exynos_eपूर्णांक_wkup_init,
	पूर्ण, अणु
		/* pin-controller instance 1 BUS0 data */
		.pin_banks	= exynos7_pin_banks1,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks1),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 2 NFC data */
		.pin_banks	= exynos7_pin_banks2,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks2),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 3 TOUCH data */
		.pin_banks	= exynos7_pin_banks3,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks3),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 4 FF data */
		.pin_banks	= exynos7_pin_banks4,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks4),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 5 ESE data */
		.pin_banks	= exynos7_pin_banks5,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks5),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 6 FSYS0 data */
		.pin_banks	= exynos7_pin_banks6,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks6),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 7 FSYS1 data */
		.pin_banks	= exynos7_pin_banks7,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks7),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 8 BUS1 data */
		.pin_banks	= exynos7_pin_banks8,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks8),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण, अणु
		/* pin-controller instance 9 AUD data */
		.pin_banks	= exynos7_pin_banks9,
		.nr_banks	= ARRAY_SIZE(exynos7_pin_banks9),
		.eपूर्णांक_gpio_init = exynos_eपूर्णांक_gpio_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data exynos7_of_data __initस्थिर = अणु
	.ctrl		= exynos7_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(exynos7_pin_ctrl),
पूर्ण;
