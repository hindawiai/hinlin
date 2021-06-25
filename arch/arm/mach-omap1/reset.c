<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP1 reset support
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#समावेश <mach/hardware.h>

#समावेश "iomap.h"
#समावेश "common.h"

/* ARM_SYSST bit shअगरts related to SoC reset sources */
#घोषणा ARM_SYSST_POR_SHIFT				5
#घोषणा ARM_SYSST_EXT_RST_SHIFT				4
#घोषणा ARM_SYSST_ARM_WDRST_SHIFT			2
#घोषणा ARM_SYSST_GLOB_SWRST_SHIFT			1

/* Standardized reset source bits (across all OMAP SoCs) */
#घोषणा OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT		0
#घोषणा OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT		1
#घोषणा OMAP_MPU_WD_RST_SRC_ID_SHIFT			3
#घोषणा OMAP_EXTWARM_RST_SRC_ID_SHIFT			5


व्योम omap1_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/*
	 * Workaround क्रम 5912/1611b bug mentioned in sprz209d.pdf p. 28
	 * "Global Software Reset Affects Traffic Controller Frequency".
	 */
	अगर (cpu_is_omap5912()) अणु
		omap_ग_लिखोw(omap_पढ़ोw(DPLL_CTL) & ~(1 << 4), DPLL_CTL);
		omap_ग_लिखोw(0x8, ARM_RSTCT1);
	पूर्ण

	omap_ग_लिखोw(1, ARM_RSTCT1);
पूर्ण

/**
 * omap1_get_reset_sources - वापस the source of the SoC's last reset
 *
 * Returns bits that represent the last reset source क्रम the SoC.  The
 * क्रमmat is standardized across OMAPs क्रम use by the OMAP watchकरोg.
 */
u32 omap1_get_reset_sources(व्योम)
अणु
	u32 ret = 0;
	u16 rs;

	rs = __raw_पढ़ोw(OMAP1_IO_ADDRESS(ARM_SYSST));

	अगर (rs & (1 << ARM_SYSST_POR_SHIFT))
		ret |= 1 << OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT;
	अगर (rs & (1 << ARM_SYSST_EXT_RST_SHIFT))
		ret |= 1 << OMAP_EXTWARM_RST_SRC_ID_SHIFT;
	अगर (rs & (1 << ARM_SYSST_ARM_WDRST_SHIFT))
		ret |= 1 << OMAP_MPU_WD_RST_SRC_ID_SHIFT;
	अगर (rs & (1 << ARM_SYSST_GLOB_SWRST_SHIFT))
		ret |= 1 << OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT;

	वापस ret;
पूर्ण
