<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MIPS specअगरic sysrq operations.
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 */
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/tlbdebug.h>

/*
 * Dump TLB entries on all CPUs.
 */

अटल DEFINE_SPINLOCK(show_lock);

अटल व्योम sysrq_tlbdump_single(व्योम *dummy)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&show_lock, flags);

	pr_info("CPU%d:\n", smp_processor_id());
	dump_tlb_regs();
	pr_info("\n");
	dump_tlb_all();
	pr_info("\n");

	spin_unlock_irqrestore(&show_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम sysrq_tlbdump_othercpus(काष्ठा work_काष्ठा *dummy)
अणु
	smp_call_function(sysrq_tlbdump_single, शून्य, 0);
पूर्ण

अटल DECLARE_WORK(sysrq_tlbdump, sysrq_tlbdump_othercpus);
#पूर्ण_अगर

अटल व्योम sysrq_handle_tlbdump(पूर्णांक key)
अणु
	sysrq_tlbdump_single(शून्य);
#अगर_घोषित CONFIG_SMP
	schedule_work(&sysrq_tlbdump);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_tlbdump_op = अणु
	.handler        = sysrq_handle_tlbdump,
	.help_msg       = "show-tlbs(x)",
	.action_msg     = "Show TLB entries",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

अटल पूर्णांक __init mips_sysrq_init(व्योम)
अणु
	वापस रेजिस्टर_sysrq_key('x', &sysrq_tlbdump_op);
पूर्ण
arch_initcall(mips_sysrq_init);
