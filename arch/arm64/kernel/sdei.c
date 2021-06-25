<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2017 Arm Ltd.
#घोषणा pr_fmt(fmt) "sdei: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/arm_sdei.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/scs.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/vmap_stack.h>

अचिन्हित दीर्घ sdei_निकास_mode;

/*
 * VMAP'd stacks checking क्रम stack overflow on exception using sp as a scratch
 * रेजिस्टर, meaning SDEI has to चयन to its own stack. We need two stacks as
 * a critical event may पूर्णांकerrupt a normal event that has just taken a
 * synchronous exception, and is using sp as scratch रेजिस्टर. For a critical
 * event पूर्णांकerrupting a normal event, we can't reliably tell अगर we were on the
 * sdei stack.
 * For now, we allocate stacks when the driver is probed.
 */
DECLARE_PER_CPU(अचिन्हित दीर्घ *, sdei_stack_normal_ptr);
DECLARE_PER_CPU(अचिन्हित दीर्घ *, sdei_stack_critical_ptr);

#अगर_घोषित CONFIG_VMAP_STACK
DEFINE_PER_CPU(अचिन्हित दीर्घ *, sdei_stack_normal_ptr);
DEFINE_PER_CPU(अचिन्हित दीर्घ *, sdei_stack_critical_ptr);
#पूर्ण_अगर

DECLARE_PER_CPU(अचिन्हित दीर्घ *, sdei_shaकरोw_call_stack_normal_ptr);
DECLARE_PER_CPU(अचिन्हित दीर्घ *, sdei_shaकरोw_call_stack_critical_ptr);

#अगर_घोषित CONFIG_SHADOW_CALL_STACK
DEFINE_PER_CPU(अचिन्हित दीर्घ *, sdei_shaकरोw_call_stack_normal_ptr);
DEFINE_PER_CPU(अचिन्हित दीर्घ *, sdei_shaकरोw_call_stack_critical_ptr);
#पूर्ण_अगर

अटल व्योम _मुक्त_sdei_stack(अचिन्हित दीर्घ * __percpu *ptr, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ *p;

	p = per_cpu(*ptr, cpu);
	अगर (p) अणु
		per_cpu(*ptr, cpu) = शून्य;
		vमुक्त(p);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_sdei_stacks(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!IS_ENABLED(CONFIG_VMAP_STACK))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		_मुक्त_sdei_stack(&sdei_stack_normal_ptr, cpu);
		_मुक्त_sdei_stack(&sdei_stack_critical_ptr, cpu);
	पूर्ण
पूर्ण

अटल पूर्णांक _init_sdei_stack(अचिन्हित दीर्घ * __percpu *ptr, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ *p;

	p = arch_alloc_vmap_stack(SDEI_STACK_SIZE, cpu_to_node(cpu));
	अगर (!p)
		वापस -ENOMEM;
	per_cpu(*ptr, cpu) = p;

	वापस 0;
पूर्ण

अटल पूर्णांक init_sdei_stacks(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक err = 0;

	अगर (!IS_ENABLED(CONFIG_VMAP_STACK))
		वापस 0;

	क्रम_each_possible_cpu(cpu) अणु
		err = _init_sdei_stack(&sdei_stack_normal_ptr, cpu);
		अगर (err)
			अवरोध;
		err = _init_sdei_stack(&sdei_stack_critical_ptr, cpu);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err)
		मुक्त_sdei_stacks();

	वापस err;
पूर्ण

अटल व्योम _मुक्त_sdei_scs(अचिन्हित दीर्घ * __percpu *ptr, पूर्णांक cpu)
अणु
	व्योम *s;

	s = per_cpu(*ptr, cpu);
	अगर (s) अणु
		per_cpu(*ptr, cpu) = शून्य;
		scs_मुक्त(s);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_sdei_scs(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		_मुक्त_sdei_scs(&sdei_shaकरोw_call_stack_normal_ptr, cpu);
		_मुक्त_sdei_scs(&sdei_shaकरोw_call_stack_critical_ptr, cpu);
	पूर्ण
पूर्ण

अटल पूर्णांक _init_sdei_scs(अचिन्हित दीर्घ * __percpu *ptr, पूर्णांक cpu)
अणु
	व्योम *s;

	s = scs_alloc(cpu_to_node(cpu));
	अगर (!s)
		वापस -ENOMEM;
	per_cpu(*ptr, cpu) = s;

	वापस 0;
पूर्ण

अटल पूर्णांक init_sdei_scs(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक err = 0;

	अगर (!IS_ENABLED(CONFIG_SHADOW_CALL_STACK))
		वापस 0;

	क्रम_each_possible_cpu(cpu) अणु
		err = _init_sdei_scs(&sdei_shaकरोw_call_stack_normal_ptr, cpu);
		अगर (err)
			अवरोध;
		err = _init_sdei_scs(&sdei_shaकरोw_call_stack_critical_ptr, cpu);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (err)
		मुक्त_sdei_scs();

	वापस err;
पूर्ण

अटल bool on_sdei_normal_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)raw_cpu_पढ़ो(sdei_stack_normal_ptr);
	अचिन्हित दीर्घ high = low + SDEI_STACK_SIZE;

	वापस on_stack(sp, low, high, STACK_TYPE_SDEI_NORMAL, info);
पूर्ण

अटल bool on_sdei_critical_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ low = (अचिन्हित दीर्घ)raw_cpu_पढ़ो(sdei_stack_critical_ptr);
	अचिन्हित दीर्घ high = low + SDEI_STACK_SIZE;

	वापस on_stack(sp, low, high, STACK_TYPE_SDEI_CRITICAL, info);
पूर्ण

bool _on_sdei_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अगर (!IS_ENABLED(CONFIG_VMAP_STACK))
		वापस false;

	अगर (on_sdei_critical_stack(sp, info))
		वापस true;

	अगर (on_sdei_normal_stack(sp, info))
		वापस true;

	वापस false;
पूर्ण

अचिन्हित दीर्घ sdei_arch_get_entry_poपूर्णांक(पूर्णांक conduit)
अणु
	/*
	 * SDEI works between adjacent exception levels. If we booted at EL1 we
	 * assume a hypervisor is marshalling events. If we booted at EL2 and
	 * dropped to EL1 because we करोn't support VHE, then we can't support
	 * SDEI.
	 */
	अगर (is_hyp_mode_available() && !is_kernel_in_hyp_mode()) अणु
		pr_err("Not supported on this hardware/boot configuration\n");
		जाओ out_err;
	पूर्ण

	अगर (init_sdei_stacks())
		जाओ out_err;

	अगर (init_sdei_scs())
		जाओ out_err_मुक्त_stacks;

	sdei_निकास_mode = (conduit == SMCCC_CONDUIT_HVC) ? SDEI_EXIT_HVC : SDEI_EXIT_SMC;

#अगर_घोषित CONFIG_UNMAP_KERNEL_AT_EL0
	अगर (arm64_kernel_unmapped_at_el0()) अणु
		अचिन्हित दीर्घ offset;

		offset = (अचिन्हित दीर्घ)__sdei_यंत्र_entry_trampoline -
			 (अचिन्हित दीर्घ)__entry_tramp_text_start;
		वापस TRAMP_VALIAS + offset;
	पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_UNMAP_KERNEL_AT_EL0 */
		वापस (अचिन्हित दीर्घ)__sdei_यंत्र_handler;

out_err_मुक्त_stacks:
	मुक्त_sdei_stacks();
out_err:
	वापस 0;
पूर्ण

/*
 * __sdei_handler() वापसs one of:
 *  SDEI_EV_HANDLED -  success, वापस to the पूर्णांकerrupted context.
 *  SDEI_EV_FAILED  -  failure, वापस this error code to firmare.
 *  भव-address -  success, वापस to this address.
 */
अटल __kprobes अचिन्हित दीर्घ _sdei_handler(काष्ठा pt_regs *regs,
					     काष्ठा sdei_रेजिस्टरed_event *arg)
अणु
	u32 mode;
	पूर्णांक i, err = 0;
	पूर्णांक clobbered_रेजिस्टरs = 4;
	u64 elr = पढ़ो_sysreg(elr_el1);
	u32 kernel_mode = पढ़ो_sysreg(CurrentEL) | 1;	/* +SPSel */
	अचिन्हित दीर्घ vbar = पढ़ो_sysreg(vbar_el1);

	अगर (arm64_kernel_unmapped_at_el0())
		clobbered_रेजिस्टरs++;

	/* Retrieve the missing रेजिस्टरs values */
	क्रम (i = 0; i < clobbered_रेजिस्टरs; i++) अणु
		/* from within the handler, this call always succeeds */
		sdei_api_event_context(i, &regs->regs[i]);
	पूर्ण

	err = sdei_event_handler(regs, arg);
	अगर (err)
		वापस SDEI_EV_FAILED;

	अगर (elr != पढ़ो_sysreg(elr_el1)) अणु
		/*
		 * We took a synchronous exception from the SDEI handler.
		 * This could deadlock, and अगर you पूर्णांकerrupt KVM it will
		 * hyp-panic instead.
		 */
		pr_warn("unsafe: exception during handler\n");
	पूर्ण

	mode = regs->pstate & (PSR_MODE32_BIT | PSR_MODE_MASK);

	/*
	 * If we पूर्णांकerrupted the kernel with पूर्णांकerrupts masked, we always go
	 * back to wherever we came from.
	 */
	अगर (mode == kernel_mode && !पूर्णांकerrupts_enabled(regs))
		वापस SDEI_EV_HANDLED;

	/*
	 * Otherwise, we pretend this was an IRQ. This lets user space tasks
	 * receive संकेतs beक्रमe we वापस to them, and KVM to invoke it's
	 * world चयन to करो the same.
	 *
	 * See DDI0487B.a Table D1-7 'Vector offsets from vector table base
	 * address'.
	 */
	अगर (mode == kernel_mode)
		वापस vbar + 0x280;
	अन्यथा अगर (mode & PSR_MODE32_BIT)
		वापस vbar + 0x680;

	वापस vbar + 0x480;
पूर्ण

अटल व्योम __kprobes notrace __sdei_pstate_entry(व्योम)
अणु
	/*
	 * The original SDEI spec (ARM DEN 0054A) can be पढ़ो ambiguously as to
	 * whether PSTATE bits are inherited unchanged or generated from
	 * scratch, and the TF-A implementation always clears PAN and always
	 * clears UAO. There are no other known implementations.
	 *
	 * Subsequent revisions (ARM DEN 0054B) follow the usual rules क्रम how
	 * PSTATE is modअगरied upon architectural exceptions, and so PAN is
	 * either inherited or set per SCTLR_ELx.SPAN, and UAO is always
	 * cleared.
	 *
	 * We must explicitly reset PAN to the expected state, including
	 * clearing it when the host isn't using it, in हाल a VM had it set.
	 */
	अगर (प्रणाली_uses_hw_pan())
		set_pstate_pan(1);
	अन्यथा अगर (cpu_has_pan())
		set_pstate_pan(0);
पूर्ण

यंत्रlinkage noinstr अचिन्हित दीर्घ
__sdei_handler(काष्ठा pt_regs *regs, काष्ठा sdei_रेजिस्टरed_event *arg)
अणु
	अचिन्हित दीर्घ ret;

	/*
	 * We didn't take an exception to get here, so the HW hasn't
	 * set/cleared bits in PSTATE that we may rely on. Initialize PAN.
	 */
	__sdei_pstate_entry();

	arm64_enter_nmi(regs);

	ret = _sdei_handler(regs, arg);

	arm64_निकास_nmi(regs);

	वापस ret;
पूर्ण
