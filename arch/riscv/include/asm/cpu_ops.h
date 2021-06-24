<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 * Based on arch/arm64/include/यंत्र/cpu_ops.h
 */
#अगर_अघोषित __ASM_CPU_OPS_H
#घोषणा __ASM_CPU_OPS_H

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>

/**
 * काष्ठा cpu_operations - Callback operations क्रम hotplugging CPUs.
 *
 * @name:		Name of the boot protocol.
 * @cpu_prepare:	Early one-समय preparation step क्रम a cpu. If there
 *			is a mechanism क्रम करोing so, tests whether it is
 *			possible to boot the given HART.
 * @cpu_start:		Boots a cpu पूर्णांकo the kernel.
 * @cpu_disable:	Prepares a cpu to die. May fail क्रम some
 *			mechanism-specअगरic reason, which will cause the hot
 *			unplug to be पातed. Called from the cpu to be समाप्तed.
 * @cpu_stop:		Makes a cpu leave the kernel. Must not fail. Called from
 *			the cpu being stopped.
 * @cpu_is_stopped:	Ensures a cpu has left the kernel. Called from another
 *			cpu.
 */
काष्ठा cpu_operations अणु
	स्थिर अक्षर	*name;
	पूर्णांक		(*cpu_prepare)(अचिन्हित पूर्णांक cpu);
	पूर्णांक		(*cpu_start)(अचिन्हित पूर्णांक cpu,
				     काष्ठा task_काष्ठा *tidle);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक		(*cpu_disable)(अचिन्हित पूर्णांक cpu);
	व्योम		(*cpu_stop)(व्योम);
	पूर्णांक		(*cpu_is_stopped)(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर
पूर्ण;

बाह्य स्थिर काष्ठा cpu_operations *cpu_ops[NR_CPUS];
व्योम __init cpu_set_ops(पूर्णांक cpu);
व्योम cpu_update_secondary_bootdata(अचिन्हित पूर्णांक cpuid,
				   काष्ठा task_काष्ठा *tidle);

#पूर्ण_अगर /* अगरndef __ASM_CPU_OPS_H */
