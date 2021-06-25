<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>

व्योम check(व्योम)
अणु
	/*
	 * These kconfig symbols must be set to "m" क्रम nfit_test to
	 * load and operate.
	 */
	BUILD_BUG_ON(!IS_MODULE(CONFIG_LIBNVDIMM));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_BLK_DEV_PMEM));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_BTT));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_PFN));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_ND_BLK));
	अगर (IS_ENABLED(CONFIG_ACPI_NFIT))
		BUILD_BUG_ON(!IS_MODULE(CONFIG_ACPI_NFIT));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_DEV_DAX));
	BUILD_BUG_ON(!IS_MODULE(CONFIG_DEV_DAX_PMEM));
पूर्ण
