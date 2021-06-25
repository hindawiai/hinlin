<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * GCC stack protector support.
 *
 * Stack protector works by putting predefined pattern at the start of
 * the stack frame and verअगरying that it hasn't been overwritten when
 * वापसing from the function.  The pattern is called stack canary
 * and unक्रमtunately gcc historically required it to be at a fixed offset
 * from the percpu segment base.  On x86_64, the offset is 40 bytes.
 *
 * The same segment is shared by percpu area and stack canary.  On
 * x86_64, percpu symbols are zero based and %gs (64-bit) poपूर्णांकs to the
 * base of percpu area.  The first occupant of the percpu area is always
 * fixed_percpu_data which contains stack_canary at the approproate
 * offset.  On x86_32, the stack canary is just a regular percpu
 * variable.
 *
 * Putting percpu data in %fs on 32-bit is a minor optimization compared to
 * using %gs.  Since 32-bit userspace normally has %fs == 0, we are likely
 * to load 0 पूर्णांकo %fs on निकास to usermode, whereas with percpu data in
 * %gs, we are likely to load a non-null %gs on वापस to user mode.
 *
 * Once we are willing to require GCC 8.1 or better क्रम 64-bit stackprotector
 * support, we can हटाओ some of this complनिकासy.
 */

#अगर_अघोषित _ASM_STACKPROTECTOR_H
#घोषणा _ASM_STACKPROTECTOR_H 1

#अगर_घोषित CONFIG_STACKPROTECTOR

#समावेश <यंत्र/tsc.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/desc.h>

#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>

/*
 * Initialize the stackprotector canary value.
 *
 * NOTE: this must only be called from functions that never वापस
 * and it must always be अंतरभूतd.
 *
 * In addition, it should be called from a compilation unit क्रम which
 * stack protector is disabled. Alternatively, the caller should not end
 * with a function call which माला_लो tail-call optimized as that would
 * lead to checking a modअगरied canary value.
 */
अटल __always_अंतरभूत व्योम boot_init_stack_canary(व्योम)
अणु
	u64 canary;
	u64 tsc;

#अगर_घोषित CONFIG_X86_64
	BUILD_BUG_ON(दुरत्व(काष्ठा fixed_percpu_data, stack_canary) != 40);
#पूर्ण_अगर
	/*
	 * We both use the अक्रमom pool and the current TSC as a source
	 * of अक्रमomness. The TSC only matters क्रम very early init,
	 * there it alपढ़ोy has some अक्रमomness on most प्रणालीs. Later
	 * on during the bootup the अक्रमom pool has true entropy too.
	 */
	get_अक्रमom_bytes(&canary, माप(canary));
	tsc = rdtsc();
	canary += tsc + (tsc << 32UL);
	canary &= CANARY_MASK;

	current->stack_canary = canary;
#अगर_घोषित CONFIG_X86_64
	this_cpu_ग_लिखो(fixed_percpu_data.stack_canary, canary);
#अन्यथा
	this_cpu_ग_लिखो(__stack_chk_guard, canary);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम cpu_init_stack_canary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
#अगर_घोषित CONFIG_X86_64
	per_cpu(fixed_percpu_data.stack_canary, cpu) = idle->stack_canary;
#अन्यथा
	per_cpu(__stack_chk_guard, cpu) = idle->stack_canary;
#पूर्ण_अगर
पूर्ण

#अन्यथा	/* STACKPROTECTOR */

/* dummy boot_init_stack_canary() is defined in linux/stackprotector.h */

अटल अंतरभूत व्योम cpu_init_stack_canary(पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु पूर्ण

#पूर्ण_अगर	/* STACKPROTECTOR */
#पूर्ण_अगर	/* _ASM_STACKPROTECTOR_H */
