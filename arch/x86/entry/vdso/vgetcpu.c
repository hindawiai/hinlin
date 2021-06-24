<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006 Andi Kleen, SUSE Lअसल.
 *
 * Fast user context implementation of अ_लोpu()
 */

#समावेश <linux/kernel.h>
#समावेश <linux/अ_लोpu.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/vgtod.h>

notrace दीर्घ
__vdso_अ_लोpu(अचिन्हित *cpu, अचिन्हित *node, काष्ठा अ_लोpu_cache *unused)
अणु
	vdso_पढ़ो_cpunode(cpu, node);

	वापस 0;
पूर्ण

दीर्घ अ_लोpu(अचिन्हित *cpu, अचिन्हित *node, काष्ठा अ_लोpu_cache *tcache)
	__attribute__((weak, alias("__vdso_getcpu")));
