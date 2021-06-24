<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_CPU_H_
#घोषणा _ASM_IA64_CPU_H_

#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/topology.h>
#समावेश <linux/percpu.h>

काष्ठा ia64_cpu अणु
	काष्ठा cpu cpu;
पूर्ण;

DECLARE_PER_CPU(काष्ठा ia64_cpu, cpu_devices);

DECLARE_PER_CPU(पूर्णांक, cpu_state);

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य पूर्णांक arch_रेजिस्टर_cpu(पूर्णांक num);
बाह्य व्योम arch_unरेजिस्टर_cpu(पूर्णांक);
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IA64_CPU_H_ */
