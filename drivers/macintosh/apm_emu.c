<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM emulation क्रम PMU-based machines
 *
 * Copyright 2001 Benjamin Herrenschmidt (benh@kernel.crashing.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/apm-emulation.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>

#घोषणा APM_CRITICAL		10
#घोषणा APM_LOW			30

अटल व्योम pmu_apm_get_घातer_status(काष्ठा apm_घातer_info *info)
अणु
	पूर्णांक percentage = -1;
	पूर्णांक batteries = 0;
	पूर्णांक समय_units = -1;
	पूर्णांक real_count = 0;
	पूर्णांक i;
	अक्षर अक्षरging = 0;
	दीर्घ अक्षरge = -1;
	दीर्घ amperage = 0;
	अचिन्हित दीर्घ btype = 0;

	info->battery_status = APM_BATTERY_STATUS_UNKNOWN;
	info->battery_flag = APM_BATTERY_FLAG_UNKNOWN;
	info->units = APM_UNITS_MINS;

	अगर (pmu_घातer_flags & PMU_PWR_AC_PRESENT)
		info->ac_line_status = APM_AC_ONLINE;
	अन्यथा
		info->ac_line_status = APM_AC_OFFLINE;

	क्रम (i=0; i<pmu_battery_count; i++) अणु
		अगर (pmu_batteries[i].flags & PMU_BATT_PRESENT) अणु
			batteries++;
			अगर (percentage < 0)
				percentage = 0;
			अगर (अक्षरge < 0)
				अक्षरge = 0;
			percentage += (pmu_batteries[i].अक्षरge * 100) /
				pmu_batteries[i].max_अक्षरge;
			अक्षरge += pmu_batteries[i].अक्षरge;
			amperage += pmu_batteries[i].amperage;
			अगर (btype == 0)
				btype = (pmu_batteries[i].flags & PMU_BATT_TYPE_MASK);
			real_count++;
			अगर ((pmu_batteries[i].flags & PMU_BATT_CHARGING))
				अक्षरging++;
		पूर्ण
	पूर्ण
	अगर (batteries == 0)
		info->ac_line_status = APM_AC_ONLINE;

	अगर (real_count) अणु
		अगर (amperage < 0) अणु
			अगर (btype == PMU_BATT_TYPE_SMART)
				समय_units = (अक्षरge * 59) / (amperage * -1);
			अन्यथा
				समय_units = (अक्षरge * 16440) / (amperage * -60);
		पूर्ण
		percentage /= real_count;
		अगर (अक्षरging > 0) अणु
			info->battery_status = APM_BATTERY_STATUS_CHARGING;
			info->battery_flag = APM_BATTERY_FLAG_CHARGING;
		पूर्ण अन्यथा अगर (percentage <= APM_CRITICAL) अणु
			info->battery_status = APM_BATTERY_STATUS_CRITICAL;
			info->battery_flag = APM_BATTERY_FLAG_CRITICAL;
		पूर्ण अन्यथा अगर (percentage <= APM_LOW) अणु
			info->battery_status = APM_BATTERY_STATUS_LOW;
			info->battery_flag = APM_BATTERY_FLAG_LOW;
		पूर्ण अन्यथा अणु
			info->battery_status = APM_BATTERY_STATUS_HIGH;
			info->battery_flag = APM_BATTERY_FLAG_HIGH;
		पूर्ण
	पूर्ण

	info->battery_lअगरe = percentage;
	info->समय = समय_units;
पूर्ण

अटल पूर्णांक __init apm_emu_init(व्योम)
अणु
	apm_get_घातer_status = pmu_apm_get_घातer_status;

	prपूर्णांकk(KERN_INFO "apm_emu: PMU APM Emulation initialized.\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास apm_emu_निकास(व्योम)
अणु
	अगर (apm_get_घातer_status == pmu_apm_get_घातer_status)
		apm_get_घातer_status = शून्य;

	prपूर्णांकk(KERN_INFO "apm_emu: PMU APM Emulation removed.\n");
पूर्ण

module_init(apm_emu_init);
module_निकास(apm_emu_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt");
MODULE_DESCRIPTION("APM emulation for PowerMac");
MODULE_LICENSE("GPL");
