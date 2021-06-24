<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/cpu_cooling.h
 *
 *  Copyright (C) 2012	Samsung Electronics Co., Ltd(http://www.samsung.com)
 *  Copyright (C) 2012  Amit Daniel <amit.kachhap@linaro.org>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित __CPU_COOLING_H__
#घोषणा __CPU_COOLING_H__

#समावेश <linux/of.h>
#समावेश <linux/thermal.h>
#समावेश <linux/cpumask.h>

काष्ठा cpufreq_policy;

#अगर_घोषित CONFIG_CPU_FREQ_THERMAL
/**
 * cpufreq_cooling_रेजिस्टर - function to create cpufreq cooling device.
 * @policy: cpufreq policy.
 */
काष्ठा thermal_cooling_device *
cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy);

/**
 * cpufreq_cooling_unरेजिस्टर - function to हटाओ cpufreq cooling device.
 * @cdev: thermal cooling device poपूर्णांकer.
 */
व्योम cpufreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *cdev);

/**
 * of_cpufreq_cooling_रेजिस्टर - create cpufreq cooling device based on DT.
 * @policy: cpufreq policy.
 */
काष्ठा thermal_cooling_device *
of_cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy);

#अन्यथा /* !CONFIG_CPU_FREQ_THERMAL */
अटल अंतरभूत काष्ठा thermal_cooling_device *
cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत
व्योम cpufreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *cdev)
अणु
	वापस;
पूर्ण

अटल अंतरभूत काष्ठा thermal_cooling_device *
of_cpufreq_cooling_रेजिस्टर(काष्ठा cpufreq_policy *policy)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_FREQ_THERMAL */

काष्ठा cpuidle_driver;

#अगर_घोषित CONFIG_CPU_IDLE_THERMAL
व्योम cpuidle_cooling_रेजिस्टर(काष्ठा cpuidle_driver *drv);
#अन्यथा /* CONFIG_CPU_IDLE_THERMAL */
अटल अंतरभूत व्योम cpuidle_cooling_रेजिस्टर(काष्ठा cpuidle_driver *drv)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_IDLE_THERMAL */

#पूर्ण_अगर /* __CPU_COOLING_H__ */
