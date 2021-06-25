<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI AM33XX and AM43XX PM Assembly Offsets
 *
 * Copyright (C) 2017-2018 Texas Instruments Inc.
 */

#समावेश <linux/kbuild.h>
#समावेश <linux/platक्रमm_data/pm33xx.h>
#समावेश <linux/ti-emअगर-sram.h>

पूर्णांक मुख्य(व्योम)
अणु
	ti_emअगर_यंत्र_offsets();

	DEFINE(AMX3_PM_WFI_FLAGS_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_sram_data, wfi_flags));
	DEFINE(AMX3_PM_L2_AUX_CTRL_VAL_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_sram_data, l2_aux_ctrl_val));
	DEFINE(AMX3_PM_L2_PREFETCH_CTRL_VAL_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_sram_data, l2_prefetch_ctrl_val));
	DEFINE(AMX3_PM_SRAM_DATA_SIZE, माप(काष्ठा am33xx_pm_sram_data));

	BLANK();

	DEFINE(AMX3_PM_RO_SRAM_DATA_VIRT_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_ro_sram_data, amx3_pm_sram_data_virt));
	DEFINE(AMX3_PM_RO_SRAM_DATA_PHYS_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_ro_sram_data, amx3_pm_sram_data_phys));
	DEFINE(AMX3_PM_RTC_BASE_VIRT_OFFSET,
	       दुरत्व(काष्ठा am33xx_pm_ro_sram_data, rtc_base_virt));
	DEFINE(AMX3_PM_RO_SRAM_DATA_SIZE,
	       माप(काष्ठा am33xx_pm_ro_sram_data));

	वापस 0;
पूर्ण
