<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_IDLE_H
#घोषणा __ASM_IDLE_H

#समावेश <linux/cpuidle.h>
#समावेश <linux/linkage.h>

बाह्य व्योम (*cpu_रुको)(व्योम);
बाह्य व्योम r4k_रुको(व्योम);
बाह्य यंत्रlinkage व्योम __r4k_रुको(व्योम);
बाह्य व्योम r4k_रुको_irqoff(व्योम);

अटल अंतरभूत पूर्णांक using_rollback_handler(व्योम)
अणु
	वापस cpu_रुको == r4k_रुको;
पूर्ण

बाह्य व्योम __init check_रुको(व्योम);

बाह्य पूर्णांक mips_cpuidle_रुको_enter(काष्ठा cpuidle_device *dev,
				   काष्ठा cpuidle_driver *drv, पूर्णांक index);

#घोषणा MIPS_CPUIDLE_WAIT_STATE अणु\
	.enter			= mips_cpuidle_रुको_enter,\
	.निकास_latency		= 1,\
	.target_residency	= 1,\
	.घातer_usage		= अच_पूर्णांक_उच्च,\
	.name			= "wait",\
	.desc			= "MIPS wait",\
पूर्ण

#पूर्ण_अगर /* __ASM_IDLE_H  */
