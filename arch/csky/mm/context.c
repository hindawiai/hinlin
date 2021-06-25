<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/asid.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/tlbflush.h>

अटल DEFINE_PER_CPU(atomic64_t, active_asids);
अटल DEFINE_PER_CPU(u64, reserved_asids);

काष्ठा asid_info asid_info;

व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	asid_check_context(&asid_info, &mm->context.asid, cpu, mm);
पूर्ण

अटल व्योम asid_flush_cpu_ctxt(व्योम)
अणु
	local_tlb_invalid_all();
पूर्ण

अटल पूर्णांक asids_init(व्योम)
अणु
	BUG_ON(((1 << CONFIG_CPU_ASID_BITS) - 1) <= num_possible_cpus());

	अगर (asid_allocator_init(&asid_info, CONFIG_CPU_ASID_BITS, 1,
				asid_flush_cpu_ctxt))
		panic("Unable to initialize ASID allocator for %lu ASIDs\n",
		      NUM_ASIDS(&asid_info));

	asid_info.active = &active_asids;
	asid_info.reserved = &reserved_asids;

	pr_info("ASID allocator initialised with %lu entries\n",
		NUM_CTXT_ASIDS(&asid_info));

	वापस 0;
पूर्ण
early_initcall(asids_init);
