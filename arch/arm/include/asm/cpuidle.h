<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_CPUIDLE_H
#घोषणा __ASM_ARM_CPUIDLE_H

#समावेश <यंत्र/proc-fns.h>

#अगर_घोषित CONFIG_CPU_IDLE
बाह्य पूर्णांक arm_cpuidle_simple_enter(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक index);
#घोषणा __cpuidle_method_section __used __section("__cpuidle_method_of_table")
#अन्यथा
अटल अंतरभूत पूर्णांक arm_cpuidle_simple_enter(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक index) अणु वापस -ENODEV; पूर्ण
#घोषणा __cpuidle_method_section __maybe_unused /* drop silently */
#पूर्ण_अगर

/* Common ARM WFI state */
#घोषणा ARM_CPUIDLE_WFI_STATE_PWR(p) अणु\
	.enter                  = arm_cpuidle_simple_enter,\
	.निकास_latency           = 1,\
	.target_residency       = 1,\
	.घातer_usage		= p,\
	.name                   = "WFI",\
	.desc                   = "ARM WFI",\
पूर्ण

/*
 * in हाल घातer_specअगरied == 1, give a शेष WFI घातer value needed
 * by some governors
 */
#घोषणा ARM_CPUIDLE_WFI_STATE ARM_CPUIDLE_WFI_STATE_PWR(अच_पूर्णांक_उच्च)

काष्ठा device_node;

काष्ठा cpuidle_ops अणु
	पूर्णांक (*suspend)(अचिन्हित दीर्घ arg);
	पूर्णांक (*init)(काष्ठा device_node *, पूर्णांक cpu);
पूर्ण;

काष्ठा of_cpuidle_method अणु
	स्थिर अक्षर *method;
	स्थिर काष्ठा cpuidle_ops *ops;
पूर्ण;

#घोषणा CPUIDLE_METHOD_OF_DECLARE(name, _method, _ops)			\
	अटल स्थिर काष्ठा of_cpuidle_method __cpuidle_method_of_table_##name \
	__cpuidle_method_section = अणु .method = _method, .ops = _ops पूर्ण

बाह्य पूर्णांक arm_cpuidle_suspend(पूर्णांक index);

बाह्य पूर्णांक arm_cpuidle_init(पूर्णांक cpu);

#पूर्ण_अगर
