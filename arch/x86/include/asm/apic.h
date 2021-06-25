<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_X86_APIC_H
#घोषणा _ASM_X86_APIC_H

#समावेश <linux/cpumask.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/hardirq.h>

#घोषणा ARCH_APICTIMER_STOPS_ON_C3	1

/*
 * Debugging macros
 */
#घोषणा APIC_QUIET   0
#घोषणा APIC_VERBOSE 1
#घोषणा APIC_DEBUG   2

/* Macros क्रम apic_extnmi which controls बाह्यal NMI masking */
#घोषणा APIC_EXTNMI_BSP		0 /* Default */
#घोषणा APIC_EXTNMI_ALL		1
#घोषणा APIC_EXTNMI_NONE	2

/*
 * Define the शेष level of output to be very little
 * This can be turned up by using apic=verbose क्रम more
 * inक्रमmation and apic=debug क्रम _lots_ of inक्रमmation.
 * apic_verbosity is defined in apic.c
 */
#घोषणा apic_prपूर्णांकk(v, s, a...) करो अणु       \
		अगर ((v) <= apic_verbosity) \
			prपूर्णांकk(s, ##a);    \
	पूर्ण जबतक (0)


#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_X86_32)
बाह्य व्योम generic_apic_probe(व्योम);
#अन्यथा
अटल अंतरभूत व्योम generic_apic_probe(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_LOCAL_APIC

बाह्य पूर्णांक apic_verbosity;
बाह्य पूर्णांक local_apic_समयr_c2_ok;

बाह्य पूर्णांक disable_apic;
बाह्य अचिन्हित पूर्णांक lapic_समयr_period;

बाह्य क्रमागत apic_पूर्णांकr_mode_id apic_पूर्णांकr_mode;
क्रमागत apic_पूर्णांकr_mode_id अणु
	APIC_PIC,
	APIC_VIRTUAL_WIRE,
	APIC_VIRTUAL_WIRE_NO_CONFIG,
	APIC_SYMMETRIC_IO,
	APIC_SYMMETRIC_IO_NO_ROUTING
पूर्ण;

#अगर_घोषित CONFIG_SMP
बाह्य व्योम __inquire_remote_apic(पूर्णांक apicid);
#अन्यथा /* CONFIG_SMP */
अटल अंतरभूत व्योम __inquire_remote_apic(पूर्णांक apicid)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल अंतरभूत व्योम शेष_inquire_remote_apic(पूर्णांक apicid)
अणु
	अगर (apic_verbosity >= APIC_DEBUG)
		__inquire_remote_apic(apicid);
पूर्ण

/*
 * With 82489DX we can't rely on apic feature bit
 * retrieved via cpuid but still have to deal with
 * such an apic chip so we assume that SMP configuration
 * is found from MP table (64bit हाल uses ACPI mostly
 * which set smp presence flag as well so we are safe
 * to use this helper too).
 */
अटल अंतरभूत bool apic_from_smp_config(व्योम)
अणु
	वापस smp_found_config && !disable_apic;
पूर्ण

/*
 * Basic functions accessing APICs.
 */
#अगर_घोषित CONFIG_PARAVIRT
#समावेश <यंत्र/paravirt.h>
#पूर्ण_अगर

बाह्य पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक);

अटल अंतरभूत व्योम native_apic_mem_ग_लिखो(u32 reg, u32 v)
अणु
	अस्थिर u32 *addr = (अस्थिर u32 *)(APIC_BASE + reg);

	alternative_io("movl %0, %P1", "xchgl %0, %P1", X86_BUG_11AP,
		       ASM_OUTPUT2("=r" (v), "=m" (*addr)),
		       ASM_OUTPUT2("0" (v), "m" (*addr)));
पूर्ण

अटल अंतरभूत u32 native_apic_mem_पढ़ो(u32 reg)
अणु
	वापस *((अस्थिर u32 *)(APIC_BASE + reg));
पूर्ण

बाह्य व्योम native_apic_रुको_icr_idle(व्योम);
बाह्य u32 native_safe_apic_रुको_icr_idle(व्योम);
बाह्य व्योम native_apic_icr_ग_लिखो(u32 low, u32 id);
बाह्य u64 native_apic_icr_पढ़ो(व्योम);

अटल अंतरभूत bool apic_is_x2apic_enabled(व्योम)
अणु
	u64 msr;

	अगर (rdmsrl_safe(MSR_IA32_APICBASE, &msr))
		वापस false;
	वापस msr & X2APIC_ENABLE;
पूर्ण

बाह्य व्योम enable_IR_x2apic(व्योम);

बाह्य पूर्णांक get_physical_broadcast(व्योम);

बाह्य पूर्णांक lapic_get_maxlvt(व्योम);
बाह्य व्योम clear_local_APIC(व्योम);
बाह्य व्योम disconnect_bsp_APIC(पूर्णांक virt_wire_setup);
बाह्य व्योम disable_local_APIC(व्योम);
बाह्य व्योम apic_soft_disable(व्योम);
बाह्य व्योम lapic_shutकरोwn(व्योम);
बाह्य व्योम sync_Arb_IDs(व्योम);
बाह्य व्योम init_bsp_APIC(व्योम);
बाह्य व्योम apic_पूर्णांकr_mode_select(व्योम);
बाह्य व्योम apic_पूर्णांकr_mode_init(व्योम);
बाह्य व्योम init_apic_mappings(व्योम);
व्योम रेजिस्टर_lapic_address(अचिन्हित दीर्घ address);
बाह्य व्योम setup_boot_APIC_घड़ी(व्योम);
बाह्य व्योम setup_secondary_APIC_घड़ी(व्योम);
बाह्य व्योम lapic_update_tsc_freq(व्योम);

#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत पूर्णांक apic_क्रमce_enable(अचिन्हित दीर्घ addr)
अणु
	वापस -1;
पूर्ण
#अन्यथा
बाह्य पूर्णांक apic_क्रमce_enable(अचिन्हित दीर्घ addr);
#पूर्ण_अगर

बाह्य व्योम apic_ap_setup(व्योम);

/*
 * On 32bit this is mach-xxx local
 */
#अगर_घोषित CONFIG_X86_64
बाह्य पूर्णांक apic_is_clustered_box(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक apic_is_clustered_box(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक setup_APIC_eilvt(u8 lvt_off, u8 vector, u8 msg_type, u8 mask);
बाह्य व्योम lapic_assign_प्रणाली_vectors(व्योम);
बाह्य व्योम lapic_assign_legacy_vector(अचिन्हित पूर्णांक isairq, bool replace);
बाह्य व्योम lapic_update_legacy_vectors(व्योम);
बाह्य व्योम lapic_online(व्योम);
बाह्य व्योम lapic_offline(व्योम);
बाह्य bool apic_needs_pit(व्योम);

बाह्य व्योम apic_send_IPI_allbutself(अचिन्हित पूर्णांक vector);

#अन्यथा /* !CONFIG_X86_LOCAL_APIC */
अटल अंतरभूत व्योम lapic_shutकरोwn(व्योम) अणु पूर्ण
#घोषणा local_apic_समयr_c2_ok		1
अटल अंतरभूत व्योम init_apic_mappings(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम disable_local_APIC(व्योम) अणु पूर्ण
# define setup_boot_APIC_घड़ी x86_init_noop
# define setup_secondary_APIC_घड़ी x86_init_noop
अटल अंतरभूत व्योम lapic_update_tsc_freq(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम init_bsp_APIC(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम apic_पूर्णांकr_mode_select(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम apic_पूर्णांकr_mode_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम lapic_assign_प्रणाली_vectors(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम lapic_assign_legacy_vector(अचिन्हित पूर्णांक i, bool r) अणु पूर्ण
अटल अंतरभूत bool apic_needs_pit(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर /* !CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_X86_X2APIC
अटल अंतरभूत व्योम native_apic_msr_ग_लिखो(u32 reg, u32 v)
अणु
	अगर (reg == APIC_DFR || reg == APIC_ID || reg == APIC_LDR ||
	    reg == APIC_LVR)
		वापस;

	wrmsr(APIC_BASE_MSR + (reg >> 4), v, 0);
पूर्ण

अटल अंतरभूत व्योम native_apic_msr_eoi_ग_लिखो(u32 reg, u32 v)
अणु
	__wrmsr(APIC_BASE_MSR + (APIC_EOI >> 4), APIC_EOI_ACK, 0);
पूर्ण

अटल अंतरभूत u32 native_apic_msr_पढ़ो(u32 reg)
अणु
	u64 msr;

	अगर (reg == APIC_DFR)
		वापस -1;

	rdmsrl(APIC_BASE_MSR + (reg >> 4), msr);
	वापस (u32)msr;
पूर्ण

अटल अंतरभूत व्योम native_x2apic_रुको_icr_idle(व्योम)
अणु
	/* no need to रुको क्रम icr idle in x2apic */
	वापस;
पूर्ण

अटल अंतरभूत u32 native_safe_x2apic_रुको_icr_idle(व्योम)
अणु
	/* no need to रुको क्रम icr idle in x2apic */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम native_x2apic_icr_ग_लिखो(u32 low, u32 id)
अणु
	wrmsrl(APIC_BASE_MSR + (APIC_ICR >> 4), ((__u64) id) << 32 | low);
पूर्ण

अटल अंतरभूत u64 native_x2apic_icr_पढ़ो(व्योम)
अणु
	अचिन्हित दीर्घ val;

	rdmsrl(APIC_BASE_MSR + (APIC_ICR >> 4), val);
	वापस val;
पूर्ण

बाह्य पूर्णांक x2apic_mode;
बाह्य पूर्णांक x2apic_phys;
बाह्य व्योम __init x2apic_set_max_apicid(u32 apicid);
बाह्य व्योम __init check_x2apic(व्योम);
बाह्य व्योम x2apic_setup(व्योम);
अटल अंतरभूत पूर्णांक x2apic_enabled(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_X2APIC) && apic_is_x2apic_enabled();
पूर्ण

#घोषणा x2apic_supported()	(boot_cpu_has(X86_FEATURE_X2APIC))
#अन्यथा /* !CONFIG_X86_X2APIC */
अटल अंतरभूत व्योम check_x2apic(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम x2apic_setup(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक x2apic_enabled(व्योम) अणु वापस 0; पूर्ण

#घोषणा x2apic_mode		(0)
#घोषणा	x2apic_supported()	(0)
#पूर्ण_अगर /* !CONFIG_X86_X2APIC */

काष्ठा irq_data;

/*
 * Copyright 2004 James Cleverकरोn, IBM.
 *
 * Generic APIC sub-arch data काष्ठा.
 *
 * Hacked क्रम x86-64 by James Cleverकरोn from i386 architecture code by
 * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and
 * James Cleverकरोn.
 */
काष्ठा apic अणु
	/* Hotpath functions first */
	व्योम	(*eoi_ग_लिखो)(u32 reg, u32 v);
	व्योम	(*native_eoi_ग_लिखो)(u32 reg, u32 v);
	व्योम	(*ग_लिखो)(u32 reg, u32 v);
	u32	(*पढ़ो)(u32 reg);

	/* IPI related functions */
	व्योम	(*रुको_icr_idle)(व्योम);
	u32	(*safe_रुको_icr_idle)(व्योम);

	व्योम	(*send_IPI)(पूर्णांक cpu, पूर्णांक vector);
	व्योम	(*send_IPI_mask)(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
	व्योम	(*send_IPI_mask_allbutself)(स्थिर काष्ठा cpumask *msk, पूर्णांक vec);
	व्योम	(*send_IPI_allbutself)(पूर्णांक vector);
	व्योम	(*send_IPI_all)(पूर्णांक vector);
	व्योम	(*send_IPI_self)(पूर्णांक vector);

	u32	disable_esr;

	क्रमागत apic_delivery_modes delivery_mode;
	bool	dest_mode_logical;

	u32	(*calc_dest_apicid)(अचिन्हित पूर्णांक cpu);

	/* ICR related functions */
	u64	(*icr_पढ़ो)(व्योम);
	व्योम	(*icr_ग_लिखो)(u32 low, u32 high);

	/* Probe, setup and smpboot functions */
	पूर्णांक	(*probe)(व्योम);
	पूर्णांक	(*acpi_madt_oem_check)(अक्षर *oem_id, अक्षर *oem_table_id);
	पूर्णांक	(*apic_id_valid)(u32 apicid);
	पूर्णांक	(*apic_id_रेजिस्टरed)(व्योम);

	bool	(*check_apicid_used)(physid_mask_t *map, पूर्णांक apicid);
	व्योम	(*init_apic_ldr)(व्योम);
	व्योम	(*ioapic_phys_id_map)(physid_mask_t *phys_map, physid_mask_t *reपंचांगap);
	व्योम	(*setup_apic_routing)(व्योम);
	पूर्णांक	(*cpu_present_to_apicid)(पूर्णांक mps_cpu);
	व्योम	(*apicid_to_cpu_present)(पूर्णांक phys_apicid, physid_mask_t *reपंचांगap);
	पूर्णांक	(*check_phys_apicid_present)(पूर्णांक phys_apicid);
	पूर्णांक	(*phys_pkg_id)(पूर्णांक cpuid_apic, पूर्णांक index_msb);

	u32	(*get_apic_id)(अचिन्हित दीर्घ x);
	u32	(*set_apic_id)(अचिन्हित पूर्णांक id);

	/* wakeup_secondary_cpu */
	पूर्णांक	(*wakeup_secondary_cpu)(पूर्णांक apicid, अचिन्हित दीर्घ start_eip);

	व्योम	(*inquire_remote_apic)(पूर्णांक apicid);

#अगर_घोषित CONFIG_X86_32
	/*
	 * Called very early during boot from get_smp_config().  It should
	 * वापस the logical apicid.  x86_[bios]_cpu_to_apicid is
	 * initialized beक्रमe this function is called.
	 *
	 * If logical apicid can't be determined that early, the function
	 * may वापस BAD_APICID.  Logical apicid will be configured after
	 * init_apic_ldr() जबतक bringing up CPUs.  Note that NUMA affinity
	 * won't be applied properly during early boot in this हाल.
	 */
	पूर्णांक (*x86_32_early_logical_apicid)(पूर्णांक cpu);
#पूर्ण_अगर
	अक्षर	*name;
पूर्ण;

/*
 * Poपूर्णांकer to the local APIC driver in use on this प्रणाली (there's
 * always just one such driver in use - the kernel decides via an
 * early probing process which one it picks - and then sticks to it):
 */
बाह्य काष्ठा apic *apic;

/*
 * APIC drivers are probed based on how they are listed in the .apicdrivers
 * section. So the order is important and enक्रमced by the ordering
 * of dअगरferent apic driver files in the Makefile.
 *
 * For the files having two apic drivers, we use apic_drivers()
 * to enक्रमce the order with in them.
 */
#घोषणा apic_driver(sym)					\
	अटल स्थिर काष्ठा apic *__apicdrivers_##sym __used		\
	__aligned(माप(काष्ठा apic *))			\
	__section(".apicdrivers") = अणु &sym पूर्ण

#घोषणा apic_drivers(sym1, sym2)					\
	अटल काष्ठा apic *__apicdrivers_##sym1##sym2[2] __used	\
	__aligned(माप(काष्ठा apic *))				\
	__section(".apicdrivers") = अणु &sym1, &sym2 पूर्ण

बाह्य काष्ठा apic *__apicdrivers[], *__apicdrivers_end[];

/*
 * APIC functionality to boot other CPUs - only used on SMP:
 */
#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक wakeup_secondary_cpu_via_nmi(पूर्णांक apicid, अचिन्हित दीर्घ start_eip);
बाह्य पूर्णांक lapic_can_unplug_cpu(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_LOCAL_APIC

अटल अंतरभूत u32 apic_पढ़ो(u32 reg)
अणु
	वापस apic->पढ़ो(reg);
पूर्ण

अटल अंतरभूत व्योम apic_ग_लिखो(u32 reg, u32 val)
अणु
	apic->ग_लिखो(reg, val);
पूर्ण

अटल अंतरभूत व्योम apic_eoi(व्योम)
अणु
	apic->eoi_ग_लिखो(APIC_EOI, APIC_EOI_ACK);
पूर्ण

अटल अंतरभूत u64 apic_icr_पढ़ो(व्योम)
अणु
	वापस apic->icr_पढ़ो();
पूर्ण

अटल अंतरभूत व्योम apic_icr_ग_लिखो(u32 low, u32 high)
अणु
	apic->icr_ग_लिखो(low, high);
पूर्ण

अटल अंतरभूत व्योम apic_रुको_icr_idle(व्योम)
अणु
	apic->रुको_icr_idle();
पूर्ण

अटल अंतरभूत u32 safe_apic_रुको_icr_idle(व्योम)
अणु
	वापस apic->safe_रुको_icr_idle();
पूर्ण

बाह्य व्योम __init apic_set_eoi_ग_लिखो(व्योम (*eoi_ग_लिखो)(u32 reg, u32 v));

#अन्यथा /* CONFIG_X86_LOCAL_APIC */

अटल अंतरभूत u32 apic_पढ़ो(u32 reg) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम apic_ग_लिखो(u32 reg, u32 val) अणु पूर्ण
अटल अंतरभूत व्योम apic_eoi(व्योम) अणु पूर्ण
अटल अंतरभूत u64 apic_icr_पढ़ो(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम apic_icr_ग_लिखो(u32 low, u32 high) अणु पूर्ण
अटल अंतरभूत व्योम apic_रुको_icr_idle(व्योम) अणु पूर्ण
अटल अंतरभूत u32 safe_apic_रुको_icr_idle(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम apic_set_eoi_ग_लिखो(व्योम (*eoi_ग_लिखो)(u32 reg, u32 v)) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

बाह्य व्योम apic_ack_irq(काष्ठा irq_data *data);

अटल अंतरभूत व्योम ack_APIC_irq(व्योम)
अणु
	/*
	 * ack_APIC_irq() actually माला_लो compiled as a single inकाष्ठाion
	 * ... yummie.
	 */
	apic_eoi();
पूर्ण


अटल अंतरभूत bool lapic_vector_set_in_irr(अचिन्हित पूर्णांक vector)
अणु
	u32 irr = apic_पढ़ो(APIC_IRR + (vector / 32 * 0x10));

	वापस !!(irr & (1U << (vector % 32)));
पूर्ण

अटल अंतरभूत अचिन्हित शेष_get_apic_id(अचिन्हित दीर्घ x)
अणु
	अचिन्हित पूर्णांक ver = GET_APIC_VERSION(apic_पढ़ो(APIC_LVR));

	अगर (APIC_XAPIC(ver) || boot_cpu_has(X86_FEATURE_EXTD_APICID))
		वापस (x >> 24) & 0xFF;
	अन्यथा
		वापस (x >> 24) & 0x0F;
पूर्ण

/*
 * Warm reset vector position:
 */
#घोषणा TRAMPOLINE_PHYS_LOW		0x467
#घोषणा TRAMPOLINE_PHYS_HIGH		0x469

बाह्य व्योम generic_bigsmp_probe(व्योम);

#अगर_घोषित CONFIG_X86_LOCAL_APIC

#समावेश <यंत्र/smp.h>

#घोषणा APIC_DFR_VALUE	(APIC_DFR_FLAT)

DECLARE_EARLY_PER_CPU_READ_MOSTLY(u16, x86_bios_cpu_apicid);

बाह्य काष्ठा apic apic_noop;

अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_apic_id(व्योम)
अणु
	अचिन्हित पूर्णांक reg = apic_पढ़ो(APIC_ID);

	वापस apic->get_apic_id(reg);
पूर्ण

बाह्य पूर्णांक शेष_apic_id_valid(u32 apicid);
बाह्य पूर्णांक शेष_acpi_madt_oem_check(अक्षर *, अक्षर *);
बाह्य व्योम शेष_setup_apic_routing(व्योम);

बाह्य u32 apic_शेष_calc_apicid(अचिन्हित पूर्णांक cpu);
बाह्य u32 apic_flat_calc_apicid(अचिन्हित पूर्णांक cpu);

बाह्य bool शेष_check_apicid_used(physid_mask_t *map, पूर्णांक apicid);
बाह्य व्योम शेष_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *reपंचांगap);
बाह्य पूर्णांक शेष_cpu_present_to_apicid(पूर्णांक mps_cpu);
बाह्य पूर्णांक शेष_check_phys_apicid_present(पूर्णांक phys_apicid);

#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_SMP
bool apic_id_is_primary_thपढ़ो(अचिन्हित पूर्णांक id);
व्योम apic_smt_update(व्योम);
#अन्यथा
अटल अंतरभूत bool apic_id_is_primary_thपढ़ो(अचिन्हित पूर्णांक id) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम apic_smt_update(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा msi_msg;
काष्ठा irq_cfg;

बाह्य व्योम __irq_msi_compose_msg(काष्ठा irq_cfg *cfg, काष्ठा msi_msg *msg,
				  bool dmar);

बाह्य व्योम ioapic_zap_locks(व्योम);

#पूर्ण_अगर /* _ASM_X86_APIC_H */
