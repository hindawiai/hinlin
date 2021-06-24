<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  thermal_hwmon.h - Generic Thermal Management hwmon support.
 *
 *  Code based on Intel thermal_core.c. Copyrights of the original code:
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 *
 *  Copyright (C) 2013 Texas Instruments
 *  Copyright (C) 2013 Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */
#अगर_अघोषित __THERMAL_HWMON_H__
#घोषणा __THERMAL_HWMON_H__

#समावेश <linux/thermal.h>

#अगर_घोषित CONFIG_THERMAL_HWMON
पूर्णांक thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz);
पूर्णांक devm_thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz);
व्योम thermal_हटाओ_hwmon_sysfs(काष्ठा thermal_zone_device *tz);
#अन्यथा
अटल अंतरभूत पूर्णांक
thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
devm_thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
thermal_हटाओ_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __THERMAL_HWMON_H__ */
