<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 - Google LLC
 * Author: David Brazdil <dbrazdil@google.com>
 */

#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

/*
 * nVHE copy of data काष्ठाures tracking available CPU cores.
 * Only entries क्रम CPUs that were online at KVM init are populated.
 * Other CPUs should not be allowed to boot because their features were
 * not checked against the finalized प्रणाली capabilities.
 */
u64 __ro_after_init hyp_cpu_logical_map[NR_CPUS] = अणु [0 ... NR_CPUS-1] = INVALID_HWID पूर्ण;

u64 cpu_logical_map(अचिन्हित पूर्णांक cpu)
अणु
	BUG_ON(cpu >= ARRAY_SIZE(hyp_cpu_logical_map));

	वापस hyp_cpu_logical_map[cpu];
पूर्ण

अचिन्हित दीर्घ __hyp_per_cpu_offset(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ *cpu_base_array;
	अचिन्हित दीर्घ this_cpu_base;
	अचिन्हित दीर्घ elf_base;

	BUG_ON(cpu >= ARRAY_SIZE(kvm_arm_hyp_percpu_base));

	cpu_base_array = (अचिन्हित दीर्घ *)&kvm_arm_hyp_percpu_base;
	this_cpu_base = kern_hyp_va(cpu_base_array[cpu]);
	elf_base = (अचिन्हित दीर्घ)&__per_cpu_start;
	वापस this_cpu_base - elf_base;
पूर्ण
