<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 ARM Ltd.
 */
#अगर_अघोषित __ASM_CPU_OPS_H
#घोषणा __ASM_CPU_OPS_H

#समावेश <linux/init.h>
#समावेश <linux/thपढ़ोs.h>

/**
 * काष्ठा cpu_operations - Callback operations क्रम hotplugging CPUs.
 *
 * @name:	Name of the property as appears in a devicetree cpu node's
 *		enable-method property. On प्रणालीs booting with ACPI, @name
 *		identअगरies the काष्ठा cpu_operations entry corresponding to
 *		the boot protocol specअगरied in the ACPI MADT table.
 * @cpu_init:	Reads any data necessary क्रम a specअगरic enable-method क्रम a
 *		proposed logical id.
 * @cpu_prepare: Early one-समय preparation step क्रम a cpu. If there is a
 *		mechanism क्रम करोing so, tests whether it is possible to boot
 *		the given CPU.
 * @cpu_boot:	Boots a cpu पूर्णांकo the kernel.
 * @cpu_postboot: Optionally, perक्रमm any post-boot cleanup or necessary
 *		synchronisation. Called from the cpu being booted.
 * @cpu_can_disable: Determines whether a CPU can be disabled based on
 *		mechanism-specअगरic inक्रमmation.
 * @cpu_disable: Prepares a cpu to die. May fail क्रम some mechanism-specअगरic
 * 		reason, which will cause the hot unplug to be पातed. Called
 * 		from the cpu to be समाप्तed.
 * @cpu_die:	Makes a cpu leave the kernel. Must not fail. Called from the
 *		cpu being समाप्तed.
 * @cpu_समाप्त:  Ensures a cpu has left the kernel. Called from another cpu.
 * @cpu_init_idle: Reads any data necessary to initialize CPU idle states क्रम
 *		   a proposed logical id.
 * @cpu_suspend: Suspends a cpu and saves the required context. May fail owing
 *               to wrong parameters or error conditions. Called from the
 *               CPU being suspended. Must be called with IRQs disabled.
 */
काष्ठा cpu_operations अणु
	स्थिर अक्षर	*name;
	पूर्णांक		(*cpu_init)(अचिन्हित पूर्णांक);
	पूर्णांक		(*cpu_prepare)(अचिन्हित पूर्णांक);
	पूर्णांक		(*cpu_boot)(अचिन्हित पूर्णांक);
	व्योम		(*cpu_postboot)(व्योम);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	bool		(*cpu_can_disable)(अचिन्हित पूर्णांक cpu);
	पूर्णांक		(*cpu_disable)(अचिन्हित पूर्णांक cpu);
	व्योम		(*cpu_die)(अचिन्हित पूर्णांक cpu);
	पूर्णांक		(*cpu_समाप्त)(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_IDLE
	पूर्णांक		(*cpu_init_idle)(अचिन्हित पूर्णांक);
	पूर्णांक		(*cpu_suspend)(अचिन्हित दीर्घ);
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init init_cpu_ops(पूर्णांक cpu);
बाह्य स्थिर काष्ठा cpu_operations *get_cpu_ops(पूर्णांक cpu);

अटल अंतरभूत व्योम __init init_bootcpu_ops(व्योम)
अणु
	init_cpu_ops(0);
पूर्ण

#पूर्ण_अगर /* अगरndef __ASM_CPU_OPS_H */
