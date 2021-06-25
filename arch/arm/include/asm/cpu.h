<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/cpu.h
 *
 *  Copyright (C) 2004-2005 ARM Ltd.
 */
#अगर_अघोषित __ASM_ARM_CPU_H
#घोषणा __ASM_ARM_CPU_H

#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>

काष्ठा cpuinfo_arm अणु
	काष्ठा cpu	cpu;
	u32		cpuid;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक	loops_per_jअगरfy;
#पूर्ण_अगर
पूर्ण;

DECLARE_PER_CPU(काष्ठा cpuinfo_arm, cpu_data);

#पूर्ण_अगर
