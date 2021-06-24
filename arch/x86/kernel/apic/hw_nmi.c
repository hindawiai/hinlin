<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  HW NMI watchकरोg support
 *
 *  started by Don Zickus, Copyright (C) 2010 Red Hat, Inc.
 *
 *  Arch specअगरic calls to support NMI watchकरोg
 *
 *  Bits copied from original nmi.c file
 *
 */
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/nmi.h>

#समावेश <linux/cpumask.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/nmi.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR_PERF
u64 hw_nmi_get_sample_period(पूर्णांक watchकरोg_thresh)
अणु
	वापस (u64)(cpu_khz) * 1000 * watchकरोg_thresh;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित arch_trigger_cpumask_backtrace
अटल व्योम nmi_उठाओ_cpu_backtrace(cpumask_t *mask)
अणु
	apic->send_IPI_mask(mask, NMI_VECTOR);
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask, bool exclude_self)
अणु
	nmi_trigger_cpumask_backtrace(mask, exclude_self,
				      nmi_उठाओ_cpu_backtrace);
पूर्ण

अटल पूर्णांक nmi_cpu_backtrace_handler(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	अगर (nmi_cpu_backtrace(regs))
		वापस NMI_HANDLED;

	वापस NMI_DONE;
पूर्ण
NOKPROBE_SYMBOL(nmi_cpu_backtrace_handler);

अटल पूर्णांक __init रेजिस्टर_nmi_cpu_backtrace_handler(व्योम)
अणु
	रेजिस्टर_nmi_handler(NMI_LOCAL, nmi_cpu_backtrace_handler,
				0, "arch_bt");
	वापस 0;
पूर्ण
early_initcall(रेजिस्टर_nmi_cpu_backtrace_handler);
#पूर्ण_अगर
