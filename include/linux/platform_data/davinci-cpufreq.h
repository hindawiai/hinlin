<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * TI DaVinci CPUFreq platक्रमm support.
 *
 * Copyright (C) 2009 Texas Instruments, Inc. https://www.ti.com/
 */

#अगर_अघोषित _MACH_DAVINCI_CPUFREQ_H
#घोषणा _MACH_DAVINCI_CPUFREQ_H

#समावेश <linux/cpufreq.h>

काष्ठा davinci_cpufreq_config अणु
	काष्ठा cpufreq_frequency_table *freq_table;
	पूर्णांक (*set_voltage)(अचिन्हित पूर्णांक index);
	पूर्णांक (*init)(व्योम);
पूर्ण;

#पूर्ण_अगर /* _MACH_DAVINCI_CPUFREQ_H */
