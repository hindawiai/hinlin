<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Interrupt descriptor table related code
 */
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/hw_irq.h>

#घोषणा DPL0		0x0
#घोषणा DPL3		0x3

#घोषणा DEFAULT_STACK	0

#घोषणा G(_vector, _addr, _ist, _type, _dpl, _segment)	\
	अणु						\
		.vector		= _vector,		\
		.bits.ist	= _ist,			\
		.bits.type	= _type,		\
		.bits.dpl	= _dpl,			\
		.bits.p		= 1,			\
		.addr		= _addr,		\
		.segment	= _segment,		\
	पूर्ण

/* Interrupt gate */
#घोषणा INTG(_vector, _addr)				\
	G(_vector, _addr, DEFAULT_STACK, GATE_INTERRUPT, DPL0, __KERNEL_CS)

/* System पूर्णांकerrupt gate */
#घोषणा SYSG(_vector, _addr)				\
	G(_vector, _addr, DEFAULT_STACK, GATE_INTERRUPT, DPL3, __KERNEL_CS)

/*
 * Interrupt gate with पूर्णांकerrupt stack. The _ist index is the index in
 * the tss.ist[] array, but क्रम the descriptor it needs to start at 1.
 */
#घोषणा ISTG(_vector, _addr, _ist)			\
	G(_vector, _addr, _ist + 1, GATE_INTERRUPT, DPL0, __KERNEL_CS)

/* Task gate */
#घोषणा TSKG(_vector, _gdt)				\
	G(_vector, शून्य, DEFAULT_STACK, GATE_TASK, DPL0, _gdt << 3)

#घोषणा IDT_TABLE_SIZE		(IDT_ENTRIES * माप(gate_desc))

अटल bool idt_setup_करोne __initdata;

/*
 * Early traps running on the DEFAULT_STACK because the other पूर्णांकerrupt
 * stacks work only after cpu_init().
 */
अटल स्थिर __initस्थिर काष्ठा idt_data early_idts[] = अणु
	INTG(X86_TRAP_DB,		यंत्र_exc_debug),
	SYSG(X86_TRAP_BP,		यंत्र_exc_पूर्णांक3),

#अगर_घोषित CONFIG_X86_32
	/*
	 * Not possible on 64-bit. See idt_setup_early_pf() क्रम details.
	 */
	INTG(X86_TRAP_PF,		यंत्र_exc_page_fault),
#पूर्ण_अगर
पूर्ण;

/*
 * The शेष IDT entries which are set up in trap_init() beक्रमe
 * cpu_init() is invoked. Interrupt stacks cannot be used at that poपूर्णांक and
 * the traps which use them are reinitialized with IST after cpu_init() has
 * set up TSS.
 */
अटल स्थिर __initस्थिर काष्ठा idt_data def_idts[] = अणु
	INTG(X86_TRAP_DE,		यंत्र_exc_भागide_error),
	INTG(X86_TRAP_NMI,		यंत्र_exc_nmi),
	INTG(X86_TRAP_BR,		यंत्र_exc_bounds),
	INTG(X86_TRAP_UD,		यंत्र_exc_invalid_op),
	INTG(X86_TRAP_NM,		यंत्र_exc_device_not_available),
	INTG(X86_TRAP_OLD_MF,		यंत्र_exc_coproc_segment_overrun),
	INTG(X86_TRAP_TS,		यंत्र_exc_invalid_tss),
	INTG(X86_TRAP_NP,		यंत्र_exc_segment_not_present),
	INTG(X86_TRAP_SS,		यंत्र_exc_stack_segment),
	INTG(X86_TRAP_GP,		यंत्र_exc_general_protection),
	INTG(X86_TRAP_SPURIOUS,		यंत्र_exc_spurious_पूर्णांकerrupt_bug),
	INTG(X86_TRAP_MF,		यंत्र_exc_coprocessor_error),
	INTG(X86_TRAP_AC,		यंत्र_exc_alignment_check),
	INTG(X86_TRAP_XF,		यंत्र_exc_simd_coprocessor_error),

#अगर_घोषित CONFIG_X86_32
	TSKG(X86_TRAP_DF,		GDT_ENTRY_DOUBLEFAULT_TSS),
#अन्यथा
	INTG(X86_TRAP_DF,		यंत्र_exc_द्विगुन_fault),
#पूर्ण_अगर
	INTG(X86_TRAP_DB,		यंत्र_exc_debug),

#अगर_घोषित CONFIG_X86_MCE
	INTG(X86_TRAP_MC,		यंत्र_exc_machine_check),
#पूर्ण_अगर

	SYSG(X86_TRAP_OF,		यंत्र_exc_overflow),
#अगर defined(CONFIG_IA32_EMULATION)
	SYSG(IA32_SYSCALL_VECTOR,	entry_INT80_compat),
#या_अगर defined(CONFIG_X86_32)
	SYSG(IA32_SYSCALL_VECTOR,	entry_INT80_32),
#पूर्ण_अगर
पूर्ण;

/*
 * The APIC and SMP idt entries
 */
अटल स्थिर __initस्थिर काष्ठा idt_data apic_idts[] = अणु
#अगर_घोषित CONFIG_SMP
	INTG(RESCHEDULE_VECTOR,			यंत्र_sysvec_reschedule_ipi),
	INTG(CALL_FUNCTION_VECTOR,		यंत्र_sysvec_call_function),
	INTG(CALL_FUNCTION_SINGLE_VECTOR,	यंत्र_sysvec_call_function_single),
	INTG(IRQ_MOVE_CLEANUP_VECTOR,		यंत्र_sysvec_irq_move_cleanup),
	INTG(REBOOT_VECTOR,			यंत्र_sysvec_reboot),
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	INTG(THERMAL_APIC_VECTOR,		यंत्र_sysvec_thermal),
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_MCE_THRESHOLD
	INTG(THRESHOLD_APIC_VECTOR,		यंत्र_sysvec_threshold),
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_MCE_AMD
	INTG(DEFERRED_ERROR_VECTOR,		यंत्र_sysvec_deferred_error),
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	INTG(LOCAL_TIMER_VECTOR,		यंत्र_sysvec_apic_समयr_पूर्णांकerrupt),
	INTG(X86_PLATFORM_IPI_VECTOR,		यंत्र_sysvec_x86_platक्रमm_ipi),
# अगरdef CONFIG_HAVE_KVM
	INTG(POSTED_INTR_VECTOR,		यंत्र_sysvec_kvm_posted_पूर्णांकr_ipi),
	INTG(POSTED_INTR_WAKEUP_VECTOR,		यंत्र_sysvec_kvm_posted_पूर्णांकr_wakeup_ipi),
	INTG(POSTED_INTR_NESTED_VECTOR,		यंत्र_sysvec_kvm_posted_पूर्णांकr_nested_ipi),
# endअगर
# अगरdef CONFIG_IRQ_WORK
	INTG(IRQ_WORK_VECTOR,			यंत्र_sysvec_irq_work),
# endअगर
	INTG(SPURIOUS_APIC_VECTOR,		यंत्र_sysvec_spurious_apic_पूर्णांकerrupt),
	INTG(ERROR_APIC_VECTOR,			यंत्र_sysvec_error_पूर्णांकerrupt),
#पूर्ण_अगर
पूर्ण;

/* Must be page-aligned because the real IDT is used in the cpu entry area */
अटल gate_desc idt_table[IDT_ENTRIES] __page_aligned_bss;

अटल काष्ठा desc_ptr idt_descr __ro_after_init = अणु
	.size		= IDT_TABLE_SIZE - 1,
	.address	= (अचिन्हित दीर्घ) idt_table,
पूर्ण;

व्योम load_current_idt(व्योम)
अणु
	lockdep_निश्चित_irqs_disabled();
	load_idt(&idt_descr);
पूर्ण

#अगर_घोषित CONFIG_X86_F00F_BUG
bool idt_is_f00f_address(अचिन्हित दीर्घ address)
अणु
	वापस ((address - idt_descr.address) >> 3) == 6;
पूर्ण
#पूर्ण_अगर

अटल __init व्योम
idt_setup_from_table(gate_desc *idt, स्थिर काष्ठा idt_data *t, पूर्णांक size, bool sys)
अणु
	gate_desc desc;

	क्रम (; size > 0; t++, size--) अणु
		idt_init_desc(&desc, t);
		ग_लिखो_idt_entry(idt, t->vector, &desc);
		अगर (sys)
			set_bit(t->vector, प्रणाली_vectors);
	पूर्ण
पूर्ण

अटल __init व्योम set_पूर्णांकr_gate(अचिन्हित पूर्णांक n, स्थिर व्योम *addr)
अणु
	काष्ठा idt_data data;

	init_idt_data(&data, n, addr);

	idt_setup_from_table(idt_table, &data, 1, false);
पूर्ण

/**
 * idt_setup_early_traps - Initialize the idt table with early traps
 *
 * On X8664 these traps करो not use पूर्णांकerrupt stacks as they can't work
 * beक्रमe cpu_init() is invoked and sets up TSS. The IST variants are
 * installed after that.
 */
व्योम __init idt_setup_early_traps(व्योम)
अणु
	idt_setup_from_table(idt_table, early_idts, ARRAY_SIZE(early_idts),
			     true);
	load_idt(&idt_descr);
पूर्ण

/**
 * idt_setup_traps - Initialize the idt table with शेष traps
 */
व्योम __init idt_setup_traps(व्योम)
अणु
	idt_setup_from_table(idt_table, def_idts, ARRAY_SIZE(def_idts), true);
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * Early traps running on the DEFAULT_STACK because the other पूर्णांकerrupt
 * stacks work only after cpu_init().
 */
अटल स्थिर __initस्थिर काष्ठा idt_data early_pf_idts[] = अणु
	INTG(X86_TRAP_PF,		यंत्र_exc_page_fault),
पूर्ण;

/*
 * The exceptions which use Interrupt stacks. They are setup after
 * cpu_init() when the TSS has been initialized.
 */
अटल स्थिर __initस्थिर काष्ठा idt_data ist_idts[] = अणु
	ISTG(X86_TRAP_DB,	यंत्र_exc_debug,			IST_INDEX_DB),
	ISTG(X86_TRAP_NMI,	यंत्र_exc_nmi,			IST_INDEX_NMI),
	ISTG(X86_TRAP_DF,	यंत्र_exc_द्विगुन_fault,		IST_INDEX_DF),
#अगर_घोषित CONFIG_X86_MCE
	ISTG(X86_TRAP_MC,	यंत्र_exc_machine_check,		IST_INDEX_MCE),
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	ISTG(X86_TRAP_VC,	यंत्र_exc_vmm_communication,	IST_INDEX_VC),
#पूर्ण_अगर
पूर्ण;

/**
 * idt_setup_early_pf - Initialize the idt table with early pagefault handler
 *
 * On X8664 this करोes not use पूर्णांकerrupt stacks as they can't work beक्रमe
 * cpu_init() is invoked and sets up TSS. The IST variant is installed
 * after that.
 *
 * Note, that X86_64 cannot install the real #PF handler in
 * idt_setup_early_traps() because the memory initialization needs the #PF
 * handler from the early_idt_handler_array to initialize the early page
 * tables.
 */
व्योम __init idt_setup_early_pf(व्योम)
अणु
	idt_setup_from_table(idt_table, early_pf_idts,
			     ARRAY_SIZE(early_pf_idts), true);
पूर्ण

/**
 * idt_setup_ist_traps - Initialize the idt table with traps using IST
 */
व्योम __init idt_setup_ist_traps(व्योम)
अणु
	idt_setup_from_table(idt_table, ist_idts, ARRAY_SIZE(ist_idts), true);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init idt_map_in_cea(व्योम)
अणु
	/*
	 * Set the IDT descriptor to a fixed पढ़ो-only location in the cpu
	 * entry area, so that the "sidt" inकाष्ठाion will not leak the
	 * location of the kernel, and to defend the IDT against arbitrary
	 * memory ग_लिखो vulnerabilities.
	 */
	cea_set_pte(CPU_ENTRY_AREA_RO_IDT_VADDR, __pa_symbol(idt_table),
		    PAGE_KERNEL_RO);
	idt_descr.address = CPU_ENTRY_AREA_RO_IDT;
पूर्ण

/**
 * idt_setup_apic_and_irq_gates - Setup APIC/SMP and normal पूर्णांकerrupt gates
 */
व्योम __init idt_setup_apic_and_irq_gates(व्योम)
अणु
	पूर्णांक i = FIRST_EXTERNAL_VECTOR;
	व्योम *entry;

	idt_setup_from_table(idt_table, apic_idts, ARRAY_SIZE(apic_idts), true);

	क्रम_each_clear_bit_from(i, प्रणाली_vectors, FIRST_SYSTEM_VECTOR) अणु
		entry = irq_entries_start + 8 * (i - FIRST_EXTERNAL_VECTOR);
		set_पूर्णांकr_gate(i, entry);
	पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	क्रम_each_clear_bit_from(i, प्रणाली_vectors, NR_VECTORS) अणु
		/*
		 * Don't set the non asचिन्हित प्रणाली vectors in the
		 * प्रणाली_vectors biपंचांगap. Otherwise they show up in
		 * /proc/पूर्णांकerrupts.
		 */
		entry = spurious_entries_start + 8 * (i - FIRST_SYSTEM_VECTOR);
		set_पूर्णांकr_gate(i, entry);
	पूर्ण
#पूर्ण_अगर
	/* Map IDT पूर्णांकo CPU entry area and reload it. */
	idt_map_in_cea();
	load_idt(&idt_descr);

	/* Make the IDT table पढ़ो only */
	set_memory_ro((अचिन्हित दीर्घ)&idt_table, 1);

	idt_setup_करोne = true;
पूर्ण

/**
 * idt_setup_early_handler - Initializes the idt table with early handlers
 */
व्योम __init idt_setup_early_handler(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_EXCEPTION_VECTORS; i++)
		set_पूर्णांकr_gate(i, early_idt_handler_array[i]);
#अगर_घोषित CONFIG_X86_32
	क्रम ( ; i < NR_VECTORS; i++)
		set_पूर्णांकr_gate(i, early_ignore_irq);
#पूर्ण_अगर
	load_idt(&idt_descr);
पूर्ण

/**
 * idt_invalidate - Invalidate पूर्णांकerrupt descriptor table
 * @addr:	The भव address of the 'invalid' IDT
 */
व्योम idt_invalidate(व्योम *addr)
अणु
	काष्ठा desc_ptr idt = अणु .address = (अचिन्हित दीर्घ) addr, .size = 0 पूर्ण;

	load_idt(&idt);
पूर्ण

व्योम __init alloc_पूर्णांकr_gate(अचिन्हित पूर्णांक n, स्थिर व्योम *addr)
अणु
	अगर (WARN_ON(n < FIRST_SYSTEM_VECTOR))
		वापस;

	अगर (WARN_ON(idt_setup_करोne))
		वापस;

	अगर (!WARN_ON(test_and_set_bit(n, प्रणाली_vectors)))
		set_पूर्णांकr_gate(n, addr);
पूर्ण
