<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम CPUFreq ondemand governor and related code.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश "cpufreq_governor.h"

काष्ठा od_policy_dbs_info अणु
	काष्ठा policy_dbs_info policy_dbs;
	अचिन्हित पूर्णांक freq_lo;
	अचिन्हित पूर्णांक freq_lo_delay_us;
	अचिन्हित पूर्णांक freq_hi_delay_us;
	अचिन्हित पूर्णांक sample_type:1;
पूर्ण;

अटल अंतरभूत काष्ठा od_policy_dbs_info *to_dbs_info(काष्ठा policy_dbs_info *policy_dbs)
अणु
	वापस container_of(policy_dbs, काष्ठा od_policy_dbs_info, policy_dbs);
पूर्ण

काष्ठा od_dbs_tuners अणु
	अचिन्हित पूर्णांक घातersave_bias;
पूर्ण;
