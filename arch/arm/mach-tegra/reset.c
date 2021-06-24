<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-tegra/reset.c
 *
 * Copyright (C) 2011,2012 NVIDIA Corporation.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <linux/firmware/trusted_foundations.h>

#समावेश <soc/tegra/fuse.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "iomap.h"
#समावेश "irammap.h"
#समावेश "reset.h"
#समावेश "sleep.h"

#घोषणा TEGRA_IRAM_RESET_BASE (TEGRA_IRAM_BASE + \
				TEGRA_IRAM_RESET_HANDLER_OFFSET)

अटल bool is_enabled;

अटल व्योम __init tegra_cpu_reset_handler_set(स्थिर u32 reset_address)
अणु
	व्योम __iomem *evp_cpu_reset =
		IO_ADDRESS(TEGRA_EXCEPTION_VECTORS_BASE + 0x100);
	व्योम __iomem *sb_ctrl = IO_ADDRESS(TEGRA_SB_BASE);
	u32 reg;

	/*
	 * NOTE: This must be the one and only ग_लिखो to the EVP CPU reset
	 *       vector in the entire प्रणाली.
	 */
	ग_लिखोl(reset_address, evp_cpu_reset);
	wmb();
	reg = पढ़ोl(evp_cpu_reset);

	/*
	 * Prevent further modअगरications to the physical reset vector.
	 *  NOTE: Has no effect on chips prior to Tegra30.
	 */
	reg = पढ़ोl(sb_ctrl);
	reg |= 2;
	ग_लिखोl(reg, sb_ctrl);
	wmb();
पूर्ण

अटल व्योम __init tegra_cpu_reset_handler_enable(व्योम)
अणु
	व्योम __iomem *iram_base = IO_ADDRESS(TEGRA_IRAM_RESET_BASE);
	स्थिर u32 reset_address = TEGRA_IRAM_RESET_BASE +
						tegra_cpu_reset_handler_offset;
	पूर्णांक err;

	BUG_ON(is_enabled);
	BUG_ON(tegra_cpu_reset_handler_size > TEGRA_IRAM_RESET_HANDLER_SIZE);

	स_नकल(iram_base, (व्योम *)__tegra_cpu_reset_handler_start,
			tegra_cpu_reset_handler_size);

	err = call_firmware_op(set_cpu_boot_addr, 0, reset_address);
	चयन (err) अणु
	हाल -ENOSYS:
		tegra_cpu_reset_handler_set(reset_address);
		fallthrough;
	हाल 0:
		is_enabled = true;
		अवरोध;
	शेष:
		pr_crit("Cannot set CPU reset handler: %d\n", err);
		BUG();
	पूर्ण
पूर्ण

व्योम __init tegra_cpu_reset_handler_init(व्योम)
अणु
	__tegra_cpu_reset_handler_data[TEGRA_RESET_TF_PRESENT] =
		trusted_foundations_रेजिस्टरed();

#अगर_घोषित CONFIG_SMP
	__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_PRESENT] =
		*((u32 *)cpu_possible_mask);
	__tegra_cpu_reset_handler_data[TEGRA_RESET_STARTUP_SECONDARY] =
		__pa_symbol((व्योम *)secondary_startup);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
	__tegra_cpu_reset_handler_data[TEGRA_RESET_STARTUP_LP1] =
		TEGRA_IRAM_LPx_RESUME_AREA;
	__tegra_cpu_reset_handler_data[TEGRA_RESET_STARTUP_LP2] =
		__pa_symbol((व्योम *)tegra_resume);
#पूर्ण_अगर

	tegra_cpu_reset_handler_enable();
पूर्ण
