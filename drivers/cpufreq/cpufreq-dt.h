<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Linaro
 * Viresh Kumar <viresh.kumar@linaro.org>
 */

#अगर_अघोषित __CPUFREQ_DT_H__
#घोषणा __CPUFREQ_DT_H__

#समावेश <linux/types.h>

काष्ठा cpufreq_policy;

काष्ठा cpufreq_dt_platक्रमm_data अणु
	bool have_governor_per_policy;

	अचिन्हित पूर्णांक	(*get_पूर्णांकermediate)(काष्ठा cpufreq_policy *policy,
					    अचिन्हित पूर्णांक index);
	पूर्णांक		(*target_पूर्णांकermediate)(काष्ठा cpufreq_policy *policy,
					       अचिन्हित पूर्णांक index);
	पूर्णांक (*suspend)(काष्ठा cpufreq_policy *policy);
	पूर्णांक (*resume)(काष्ठा cpufreq_policy *policy);
पूर्ण;

#पूर्ण_अगर /* __CPUFREQ_DT_H__ */
