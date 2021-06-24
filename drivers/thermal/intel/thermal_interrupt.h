<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INTEL_THERMAL_INTERRUPT_H
#घोषणा _INTEL_THERMAL_INTERRUPT_H

/* Interrupt Handler क्रम package thermal thresholds */
बाह्य पूर्णांक (*platक्रमm_thermal_package_notअगरy)(__u64 msr_val);

/* Interrupt Handler क्रम core thermal thresholds */
बाह्य पूर्णांक (*platक्रमm_thermal_notअगरy)(__u64 msr_val);

/* Callback support of rate control, वापस true, अगर
 * callback has rate control */
बाह्य bool (*platक्रमm_thermal_package_rate_control)(व्योम);

#पूर्ण_अगर /* _INTEL_THERMAL_INTERRUPT_H */
