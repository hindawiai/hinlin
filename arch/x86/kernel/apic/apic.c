<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Local APIC handling, local APIC समयrs
 *
 *	(c) 1999, 2000, 2009 Ingo Molnar <mingo@redhat.com>
 *
 *	Fixes
 *	Maciej W. Rozycki	:	Bits क्रम genuine 82489DX APICs;
 *					thanks to Eric Gilmore
 *					and Rolf G. Tews
 *					क्रम testing these extensively.
 *	Maciej W. Rozycki	:	Various updates and fixes.
 *	Mikael Pettersson	:	Power Management क्रम UP-APIC.
 *	Pavel Machek and
 *	Mikael Pettersson	:	PM converted to driver model.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/acpi_pmपंचांगr.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयx.h>
#समावेश <linux/i8253.h>
#समावेश <linux/dmar.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/dmi.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/trace/irq_vectors.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/tsc.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/irq_regs.h>

अचिन्हित पूर्णांक num_processors;

अचिन्हित disabled_cpus;

/* Processor that is करोing the boot up */
अचिन्हित पूर्णांक boot_cpu_physical_apicid __ro_after_init = -1U;
EXPORT_SYMBOL_GPL(boot_cpu_physical_apicid);

u8 boot_cpu_apic_version __ro_after_init;

/*
 * The highest APIC ID seen during क्रमागतeration.
 */
अटल अचिन्हित पूर्णांक max_physical_apicid;

/*
 * Biपंचांगask of physically existing CPUs:
 */
physid_mask_t phys_cpu_present_map;

/*
 * Processor to be disabled specअगरied by kernel parameter
 * disable_cpu_apicid=<पूर्णांक>, mostly used क्रम the kdump 2nd kernel to
 * aव्योम undefined behaviour caused by sending INIT from AP to BSP.
 */
अटल अचिन्हित पूर्णांक disabled_cpu_apicid __ro_after_init = BAD_APICID;

/*
 * This variable controls which CPUs receive बाह्यal NMIs.  By शेष,
 * बाह्यal NMIs are delivered only to the BSP.
 */
अटल पूर्णांक apic_extnmi __ro_after_init = APIC_EXTNMI_BSP;

/*
 * Hypervisor supports 15 bits of APIC ID in MSI Extended Destination ID
 */
अटल bool virt_ext_dest_id __ro_after_init;

/*
 * Map cpu index to physical APIC ID
 */
DEFINE_EARLY_PER_CPU_READ_MOSTLY(u16, x86_cpu_to_apicid, BAD_APICID);
DEFINE_EARLY_PER_CPU_READ_MOSTLY(u16, x86_bios_cpu_apicid, BAD_APICID);
DEFINE_EARLY_PER_CPU_READ_MOSTLY(u32, x86_cpu_to_acpiid, U32_MAX);
EXPORT_EARLY_PER_CPU_SYMBOL(x86_cpu_to_apicid);
EXPORT_EARLY_PER_CPU_SYMBOL(x86_bios_cpu_apicid);
EXPORT_EARLY_PER_CPU_SYMBOL(x86_cpu_to_acpiid);

#अगर_घोषित CONFIG_X86_32

/*
 * On x86_32, the mapping between cpu and logical apicid may vary
 * depending on apic in use.  The following early percpu variable is
 * used क्रम the mapping.  This is where the behaviors of x86_64 and 32
 * actually भागerge.  Let's keep it ugly क्रम now.
 */
DEFINE_EARLY_PER_CPU_READ_MOSTLY(पूर्णांक, x86_cpu_to_logical_apicid, BAD_APICID);

/* Local APIC was disabled by the BIOS and enabled by the kernel */
अटल पूर्णांक enabled_via_apicbase __ro_after_init;

/*
 * Handle पूर्णांकerrupt mode configuration रेजिस्टर (IMCR).
 * This रेजिस्टर controls whether the पूर्णांकerrupt संकेतs
 * that reach the BSP come from the master PIC or from the
 * local APIC. Beक्रमe entering Symmetric I/O Mode, either
 * the BIOS or the operating प्रणाली must चयन out of
 * PIC Mode by changing the IMCR.
 */
अटल अंतरभूत व्योम imcr_pic_to_apic(व्योम)
अणु
	/* select IMCR रेजिस्टर */
	outb(0x70, 0x22);
	/* NMI and 8259 INTR go through APIC */
	outb(0x01, 0x23);
पूर्ण

अटल अंतरभूत व्योम imcr_apic_to_pic(व्योम)
अणु
	/* select IMCR रेजिस्टर */
	outb(0x70, 0x22);
	/* NMI and 8259 INTR go directly to BSP */
	outb(0x00, 0x23);
पूर्ण
#पूर्ण_अगर

/*
 * Knob to control our willingness to enable the local APIC.
 *
 * +1=क्रमce-enable
 */
अटल पूर्णांक क्रमce_enable_local_apic __initdata;

/*
 * APIC command line parameters
 */
अटल पूर्णांक __init parse_lapic(अक्षर *arg)
अणु
	अगर (IS_ENABLED(CONFIG_X86_32) && !arg)
		क्रमce_enable_local_apic = 1;
	अन्यथा अगर (arg && !म_भेदन(arg, "notscdeadline", 13))
		setup_clear_cpu_cap(X86_FEATURE_TSC_DEADLINE_TIMER);
	वापस 0;
पूर्ण
early_param("lapic", parse_lapic);

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक apic_calibrate_pmपंचांगr __initdata;
अटल __init पूर्णांक setup_apicpmसमयr(अक्षर *s)
अणु
	apic_calibrate_pmपंचांगr = 1;
	notsc_setup(शून्य);
	वापस 0;
पूर्ण
__setup("apicpmtimer", setup_apicpmसमयr);
#पूर्ण_अगर

अचिन्हित दीर्घ mp_lapic_addr __ro_after_init;
पूर्णांक disable_apic __ro_after_init;
/* Disable local APIC समयr from the kernel commandline or via dmi quirk */
अटल पूर्णांक disable_apic_समयr __initdata;
/* Local APIC समयr works in C2 */
पूर्णांक local_apic_समयr_c2_ok __ro_after_init;
EXPORT_SYMBOL_GPL(local_apic_समयr_c2_ok);

/*
 * Debug level, exported क्रम io_apic.c
 */
पूर्णांक apic_verbosity __ro_after_init;

पूर्णांक pic_mode __ro_after_init;

/* Have we found an MP table */
पूर्णांक smp_found_config __ro_after_init;

अटल काष्ठा resource lapic_resource = अणु
	.name = "Local APIC",
	.flags = IORESOURCE_MEM | IORESOURCE_BUSY,
पूर्ण;

अचिन्हित पूर्णांक lapic_समयr_period = 0;

अटल व्योम apic_pm_activate(व्योम);

अटल अचिन्हित दीर्घ apic_phys __ro_after_init;

/*
 * Get the LAPIC version
 */
अटल अंतरभूत पूर्णांक lapic_get_version(व्योम)
अणु
	वापस GET_APIC_VERSION(apic_पढ़ो(APIC_LVR));
पूर्ण

/*
 * Check, अगर the APIC is पूर्णांकegrated or a separate chip
 */
अटल अंतरभूत पूर्णांक lapic_is_पूर्णांकegrated(व्योम)
अणु
	वापस APIC_INTEGRATED(lapic_get_version());
पूर्ण

/*
 * Check, whether this is a modern or a first generation APIC
 */
अटल पूर्णांक modern_apic(व्योम)
अणु
	/* AMD प्रणालीs use old APIC versions, so check the CPU */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD &&
	    boot_cpu_data.x86 >= 0xf)
		वापस 1;

	/* Hygon प्रणालीs use modern APIC */
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		वापस 1;

	वापस lapic_get_version() >= 0x14;
पूर्ण

/*
 * right after this call apic become NOOP driven
 * so apic->ग_लिखो/पढ़ो करोesn't करो anything
 */
अटल व्योम __init apic_disable(व्योम)
अणु
	pr_info("APIC: switched to apic NOOP\n");
	apic = &apic_noop;
पूर्ण

व्योम native_apic_रुको_icr_idle(व्योम)
अणु
	जबतक (apic_पढ़ो(APIC_ICR) & APIC_ICR_BUSY)
		cpu_relax();
पूर्ण

u32 native_safe_apic_रुको_icr_idle(व्योम)
अणु
	u32 send_status;
	पूर्णांक समयout;

	समयout = 0;
	करो अणु
		send_status = apic_पढ़ो(APIC_ICR) & APIC_ICR_BUSY;
		अगर (!send_status)
			अवरोध;
		inc_irq_stat(icr_पढ़ो_retry_count);
		udelay(100);
	पूर्ण जबतक (समयout++ < 1000);

	वापस send_status;
पूर्ण

व्योम native_apic_icr_ग_लिखो(u32 low, u32 id)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	apic_ग_लिखो(APIC_ICR2, SET_APIC_DEST_FIELD(id));
	apic_ग_लिखो(APIC_ICR, low);
	local_irq_restore(flags);
पूर्ण

u64 native_apic_icr_पढ़ो(व्योम)
अणु
	u32 icr1, icr2;

	icr2 = apic_पढ़ो(APIC_ICR2);
	icr1 = apic_पढ़ो(APIC_ICR);

	वापस icr1 | ((u64)icr2 << 32);
पूर्ण

#अगर_घोषित CONFIG_X86_32
/**
 * get_physical_broadcast - Get number of physical broadcast IDs
 */
पूर्णांक get_physical_broadcast(व्योम)
अणु
	वापस modern_apic() ? 0xff : 0xf;
पूर्ण
#पूर्ण_अगर

/**
 * lapic_get_maxlvt - get the maximum number of local vector table entries
 */
पूर्णांक lapic_get_maxlvt(व्योम)
अणु
	/*
	 * - we always have APIC पूर्णांकegrated on 64bit mode
	 * - 82489DXs करो not report # of LVT entries
	 */
	वापस lapic_is_पूर्णांकegrated() ? GET_APIC_MAXLVT(apic_पढ़ो(APIC_LVR)) : 2;
पूर्ण

/*
 * Local APIC समयr
 */

/* Clock भागisor */
#घोषणा APIC_DIVISOR 16
#घोषणा TSC_DIVISOR  8

/*
 * This function sets up the local APIC समयr, with a समयout of
 * 'clocks' APIC bus घड़ी. During calibration we actually call
 * this function twice on the boot CPU, once with a bogus समयout
 * value, second समय क्रम real. The other (noncalibrating) CPUs
 * call this function only once, with the real, calibrated value.
 *
 * We करो पढ़ोs beक्रमe ग_लिखोs even अगर unnecessary, to get around the
 * P5 APIC द्विगुन ग_लिखो bug.
 */
अटल व्योम __setup_APIC_LVTT(अचिन्हित पूर्णांक घड़ीs, पूर्णांक oneshot, पूर्णांक irqen)
अणु
	अचिन्हित पूर्णांक lvtt_value, पंचांगp_value;

	lvtt_value = LOCAL_TIMER_VECTOR;
	अगर (!oneshot)
		lvtt_value |= APIC_LVT_TIMER_PERIODIC;
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		lvtt_value |= APIC_LVT_TIMER_TSCDEADLINE;

	अगर (!lapic_is_पूर्णांकegrated())
		lvtt_value |= SET_APIC_TIMER_BASE(APIC_TIMER_BASE_DIV);

	अगर (!irqen)
		lvtt_value |= APIC_LVT_MASKED;

	apic_ग_लिखो(APIC_LVTT, lvtt_value);

	अगर (lvtt_value & APIC_LVT_TIMER_TSCDEADLINE) अणु
		/*
		 * See Intel SDM: TSC-Deadline Mode chapter. In xAPIC mode,
		 * writing to the APIC LVTT and TSC_DEADLINE MSR isn't serialized.
		 * According to Intel, MFENCE can करो the serialization here.
		 */
		यंत्र अस्थिर("mfence" : : : "memory");
		वापस;
	पूर्ण

	/*
	 * Divide PICLK by 16
	 */
	पंचांगp_value = apic_पढ़ो(APIC_TDCR);
	apic_ग_लिखो(APIC_TDCR,
		(पंचांगp_value & ~(APIC_TDR_DIV_1 | APIC_TDR_DIV_TMBASE)) |
		APIC_TDR_DIV_16);

	अगर (!oneshot)
		apic_ग_लिखो(APIC_TMICT, घड़ीs / APIC_DIVISOR);
पूर्ण

/*
 * Setup extended LVT, AMD specअगरic
 *
 * Software should use the LVT offsets the BIOS provides.  The offsets
 * are determined by the subप्रणालीs using it like those क्रम MCE
 * threshold or IBS.  On K8 only offset 0 (APIC500) and MCE पूर्णांकerrupts
 * are supported. Beginning with family 10h at least 4 offsets are
 * available.
 *
 * Since the offsets must be consistent क्रम all cores, we keep track
 * of the LVT offsets in software and reserve the offset क्रम the same
 * vector also to be used on other cores. An offset is मुक्तd by
 * setting the entry to APIC_EILVT_MASKED.
 *
 * If the BIOS is right, there should be no conflicts. Otherwise a
 * "[Firmware Bug]: ..." error message is generated. However, अगर
 * software करोes not properly determines the offsets, it is not
 * necessarily a BIOS bug.
 */

अटल atomic_t eilvt_offsets[APIC_EILVT_NR_MAX];

अटल अंतरभूत पूर्णांक eilvt_entry_is_changeable(अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new)
अणु
	वापस (old & APIC_EILVT_MASKED)
		|| (new == APIC_EILVT_MASKED)
		|| ((new & ~APIC_EILVT_MASKED) == old);
पूर्ण

अटल अचिन्हित पूर्णांक reserve_eilvt_offset(पूर्णांक offset, अचिन्हित पूर्णांक new)
अणु
	अचिन्हित पूर्णांक rsvd, vector;

	अगर (offset >= APIC_EILVT_NR_MAX)
		वापस ~0;

	rsvd = atomic_पढ़ो(&eilvt_offsets[offset]);
	करो अणु
		vector = rsvd & ~APIC_EILVT_MASKED;	/* 0: unasचिन्हित */
		अगर (vector && !eilvt_entry_is_changeable(vector, new))
			/* may not change अगर vectors are dअगरferent */
			वापस rsvd;
		rsvd = atomic_cmpxchg(&eilvt_offsets[offset], rsvd, new);
	पूर्ण जबतक (rsvd != new);

	rsvd &= ~APIC_EILVT_MASKED;
	अगर (rsvd && rsvd != vector)
		pr_info("LVT offset %d assigned for vector 0x%02x\n",
			offset, rsvd);

	वापस new;
पूर्ण

/*
 * If mask=1, the LVT entry करोes not generate पूर्णांकerrupts जबतक mask=0
 * enables the vector. See also the BKDGs. Must be called with
 * preemption disabled.
 */

पूर्णांक setup_APIC_eilvt(u8 offset, u8 vector, u8 msg_type, u8 mask)
अणु
	अचिन्हित दीर्घ reg = APIC_EILVTn(offset);
	अचिन्हित पूर्णांक new, old, reserved;

	new = (mask << 16) | (msg_type << 8) | vector;
	old = apic_पढ़ो(reg);
	reserved = reserve_eilvt_offset(offset, new);

	अगर (reserved != new) अणु
		pr_err(FW_BUG "cpu %d, try to use APIC%lX (LVT offset %d) for "
		       "vector 0x%x, but the register is already in use for "
		       "vector 0x%x on another cpu\n",
		       smp_processor_id(), reg, offset, new, reserved);
		वापस -EINVAL;
	पूर्ण

	अगर (!eilvt_entry_is_changeable(old, new)) अणु
		pr_err(FW_BUG "cpu %d, try to use APIC%lX (LVT offset %d) for "
		       "vector 0x%x, but the register is already in use for "
		       "vector 0x%x on this cpu\n",
		       smp_processor_id(), reg, offset, new, old);
		वापस -EBUSY;
	पूर्ण

	apic_ग_लिखो(reg, new);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(setup_APIC_eilvt);

/*
 * Program the next event, relative to now
 */
अटल पूर्णांक lapic_next_event(अचिन्हित दीर्घ delta,
			    काष्ठा घड़ी_event_device *evt)
अणु
	apic_ग_लिखो(APIC_TMICT, delta);
	वापस 0;
पूर्ण

अटल पूर्णांक lapic_next_deadline(अचिन्हित दीर्घ delta,
			       काष्ठा घड़ी_event_device *evt)
अणु
	u64 tsc;

	/* This MSR is special and need a special fence: */
	weak_wrmsr_fence();

	tsc = rdtsc();
	wrmsrl(MSR_IA32_TSC_DEADLINE, tsc + (((u64) delta) * TSC_DIVISOR));
	वापस 0;
पूर्ण

अटल पूर्णांक lapic_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक v;

	/* Lapic used as dummy क्रम broadcast ? */
	अगर (evt->features & CLOCK_EVT_FEAT_DUMMY)
		वापस 0;

	v = apic_पढ़ो(APIC_LVTT);
	v |= (APIC_LVT_MASKED | LOCAL_TIMER_VECTOR);
	apic_ग_लिखो(APIC_LVTT, v);
	apic_ग_लिखो(APIC_TMICT, 0);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
lapic_समयr_set_periodic_oneshot(काष्ठा घड़ी_event_device *evt, bool oneshot)
अणु
	/* Lapic used as dummy क्रम broadcast ? */
	अगर (evt->features & CLOCK_EVT_FEAT_DUMMY)
		वापस 0;

	__setup_APIC_LVTT(lapic_समयr_period, oneshot, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक lapic_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	वापस lapic_समयr_set_periodic_oneshot(evt, false);
पूर्ण

अटल पूर्णांक lapic_समयr_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	वापस lapic_समयr_set_periodic_oneshot(evt, true);
पूर्ण

/*
 * Local APIC समयr broadcast function
 */
अटल व्योम lapic_समयr_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
#अगर_घोषित CONFIG_SMP
	apic->send_IPI_mask(mask, LOCAL_TIMER_VECTOR);
#पूर्ण_अगर
पूर्ण


/*
 * The local apic समयr can be used क्रम any function which is CPU local.
 */
अटल काष्ठा घड़ी_event_device lapic_घड़ीevent = अणु
	.name				= "lapic",
	.features			= CLOCK_EVT_FEAT_PERIODIC |
					  CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_C3STOP
					  | CLOCK_EVT_FEAT_DUMMY,
	.shअगरt				= 32,
	.set_state_shutकरोwn		= lapic_समयr_shutकरोwn,
	.set_state_periodic		= lapic_समयr_set_periodic,
	.set_state_oneshot		= lapic_समयr_set_oneshot,
	.set_state_oneshot_stopped	= lapic_समयr_shutकरोwn,
	.set_next_event			= lapic_next_event,
	.broadcast			= lapic_समयr_broadcast,
	.rating				= 100,
	.irq				= -1,
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, lapic_events);

अटल स्थिर काष्ठा x86_cpu_id deadline_match[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(HASWELL_X, X86_STEPPINGS(0x2, 0x2), 0x3a), /* EP */
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(HASWELL_X, X86_STEPPINGS(0x4, 0x4), 0x0f), /* EX */

	X86_MATCH_INTEL_FAM6_MODEL( BROADWELL_X,	0x0b000020),

	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(BROADWELL_D, X86_STEPPINGS(0x2, 0x2), 0x00000011),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(BROADWELL_D, X86_STEPPINGS(0x3, 0x3), 0x0700000e),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(BROADWELL_D, X86_STEPPINGS(0x4, 0x4), 0x0f00000c),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(BROADWELL_D, X86_STEPPINGS(0x5, 0x5), 0x0e000003),

	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(SKYLAKE_X, X86_STEPPINGS(0x3, 0x3), 0x01000136),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(SKYLAKE_X, X86_STEPPINGS(0x4, 0x4), 0x02000014),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(SKYLAKE_X, X86_STEPPINGS(0x5, 0xf), 0),

	X86_MATCH_INTEL_FAM6_MODEL( HASWELL,		0x22),
	X86_MATCH_INTEL_FAM6_MODEL( HASWELL_L,		0x20),
	X86_MATCH_INTEL_FAM6_MODEL( HASWELL_G,		0x17),

	X86_MATCH_INTEL_FAM6_MODEL( BROADWELL,		0x25),
	X86_MATCH_INTEL_FAM6_MODEL( BROADWELL_G,	0x17),

	X86_MATCH_INTEL_FAM6_MODEL( SKYLAKE_L,		0xb2),
	X86_MATCH_INTEL_FAM6_MODEL( SKYLAKE,		0xb2),

	X86_MATCH_INTEL_FAM6_MODEL( KABYLAKE_L,		0x52),
	X86_MATCH_INTEL_FAM6_MODEL( KABYLAKE,		0x52),

	अणुपूर्ण,
पूर्ण;

अटल __init bool apic_validate_deadline_समयr(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *m;
	u32 rev;

	अगर (!boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		वापस false;
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस true;

	m = x86_match_cpu(deadline_match);
	अगर (!m)
		वापस true;

	rev = (u32)m->driver_data;

	अगर (boot_cpu_data.microcode >= rev)
		वापस true;

	setup_clear_cpu_cap(X86_FEATURE_TSC_DEADLINE_TIMER);
	pr_err(FW_BUG "TSC_DEADLINE disabled due to Errata; "
	       "please update microcode to version: 0x%x (or later)\n", rev);
	वापस false;
पूर्ण

/*
 * Setup the local APIC समयr क्रम this CPU. Copy the initialized values
 * of the boot CPU and रेजिस्टर the घड़ी event in the framework.
 */
अटल व्योम setup_APIC_समयr(व्योम)
अणु
	काष्ठा घड़ी_event_device *levt = this_cpu_ptr(&lapic_events);

	अगर (this_cpu_has(X86_FEATURE_ARAT)) अणु
		lapic_घड़ीevent.features &= ~CLOCK_EVT_FEAT_C3STOP;
		/* Make LAPIC समयr preferable over percpu HPET */
		lapic_घड़ीevent.rating = 150;
	पूर्ण

	स_नकल(levt, &lapic_घड़ीevent, माप(*levt));
	levt->cpumask = cpumask_of(smp_processor_id());

	अगर (this_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER)) अणु
		levt->name = "lapic-deadline";
		levt->features &= ~(CLOCK_EVT_FEAT_PERIODIC |
				    CLOCK_EVT_FEAT_DUMMY);
		levt->set_next_event = lapic_next_deadline;
		घड़ीevents_config_and_रेजिस्टर(levt,
						tsc_khz * (1000 / TSC_DIVISOR),
						0xF, ~0UL);
	पूर्ण अन्यथा
		घड़ीevents_रेजिस्टर_device(levt);
पूर्ण

/*
 * Install the updated TSC frequency from recalibration at the TSC
 * deadline घड़ीevent devices.
 */
अटल व्योम __lapic_update_tsc_freq(व्योम *info)
अणु
	काष्ठा घड़ी_event_device *levt = this_cpu_ptr(&lapic_events);

	अगर (!this_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		वापस;

	घड़ीevents_update_freq(levt, tsc_khz * (1000 / TSC_DIVISOR));
पूर्ण

व्योम lapic_update_tsc_freq(व्योम)
अणु
	/*
	 * The घड़ीevent device's ->mult and ->shअगरt can both be
	 * changed. In order to aव्योम races, schedule the frequency
	 * update code on each CPU.
	 */
	on_each_cpu(__lapic_update_tsc_freq, शून्य, 0);
पूर्ण

/*
 * In this functions we calibrate APIC bus घड़ीs to the बाह्यal समयr.
 *
 * We want to करो the calibration only once since we want to have local समयr
 * irqs synchronous. CPUs connected by the same APIC bus have the very same bus
 * frequency.
 *
 * This was previously करोne by पढ़ोing the PIT/HPET and रुकोing क्रम a wrap
 * around to find out, that a tick has elapsed. I have a box, where the PIT
 * पढ़ोout is broken, so it never माला_लो out of the रुको loop again. This was
 * also reported by others.
 *
 * Monitoring the jअगरfies value is inaccurate and the घड़ीevents
 * infraकाष्ठाure allows us to करो a simple substitution of the पूर्णांकerrupt
 * handler.
 *
 * The calibration routine also uses the pm_समयr when possible, as the PIT
 * happens to run way too slow (factor 2.3 on my VAIO CoreDuo, which goes
 * back to normal later in the boot process).
 */

#घोषणा LAPIC_CAL_LOOPS		(HZ/10)

अटल __initdata पूर्णांक lapic_cal_loops = -1;
अटल __initdata दीर्घ lapic_cal_t1, lapic_cal_t2;
अटल __initdata अचिन्हित दीर्घ दीर्घ lapic_cal_tsc1, lapic_cal_tsc2;
अटल __initdata अचिन्हित दीर्घ lapic_cal_pm1, lapic_cal_pm2;
अटल __initdata अचिन्हित दीर्घ lapic_cal_j1, lapic_cal_j2;

/*
 * Temporary पूर्णांकerrupt handler and polled calibration function.
 */
अटल व्योम __init lapic_cal_handler(काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ दीर्घ tsc = 0;
	दीर्घ tapic = apic_पढ़ो(APIC_TMCCT);
	अचिन्हित दीर्घ pm = acpi_pm_पढ़ो_early();

	अगर (boot_cpu_has(X86_FEATURE_TSC))
		tsc = rdtsc();

	चयन (lapic_cal_loops++) अणु
	हाल 0:
		lapic_cal_t1 = tapic;
		lapic_cal_tsc1 = tsc;
		lapic_cal_pm1 = pm;
		lapic_cal_j1 = jअगरfies;
		अवरोध;

	हाल LAPIC_CAL_LOOPS:
		lapic_cal_t2 = tapic;
		lapic_cal_tsc2 = tsc;
		अगर (pm < lapic_cal_pm1)
			pm += ACPI_PM_OVRRUN;
		lapic_cal_pm2 = pm;
		lapic_cal_j2 = jअगरfies;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __init
calibrate_by_pmसमयr(दीर्घ deltapm, दीर्घ *delta, दीर्घ *deltatsc)
अणु
	स्थिर दीर्घ pm_100ms = PMTMR_TICKS_PER_SEC / 10;
	स्थिर दीर्घ pm_thresh = pm_100ms / 100;
	अचिन्हित दीर्घ mult;
	u64 res;

#अगर_अघोषित CONFIG_X86_PM_TIMER
	वापस -1;
#पूर्ण_अगर

	apic_prपूर्णांकk(APIC_VERBOSE, "... PM-Timer delta = %ld\n", deltapm);

	/* Check, अगर the PM समयr is available */
	अगर (!deltapm)
		वापस -1;

	mult = घड़ीsource_hz2mult(PMTMR_TICKS_PER_SEC, 22);

	अगर (deltapm > (pm_100ms - pm_thresh) &&
	    deltapm < (pm_100ms + pm_thresh)) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, "... PM-Timer result ok\n");
		वापस 0;
	पूर्ण

	res = (((u64)deltapm) *  mult) >> 22;
	करो_भाग(res, 1000000);
	pr_warn("APIC calibration not consistent "
		"with PM-Timer: %ldms instead of 100ms\n", (दीर्घ)res);

	/* Correct the lapic counter value */
	res = (((u64)(*delta)) * pm_100ms);
	करो_भाग(res, deltapm);
	pr_info("APIC delta adjusted to PM-Timer: "
		"%lu (%ld)\n", (अचिन्हित दीर्घ)res, *delta);
	*delta = (दीर्घ)res;

	/* Correct the tsc counter value */
	अगर (boot_cpu_has(X86_FEATURE_TSC)) अणु
		res = (((u64)(*deltatsc)) * pm_100ms);
		करो_भाग(res, deltapm);
		apic_prपूर्णांकk(APIC_VERBOSE, "TSC delta adjusted to "
					  "PM-Timer: %lu (%ld)\n",
					(अचिन्हित दीर्घ)res, *deltatsc);
		*deltatsc = (दीर्घ)res;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init lapic_init_घड़ीevent(व्योम)
अणु
	अगर (!lapic_समयr_period)
		वापस -1;

	/* Calculate the scaled math multiplication factor */
	lapic_घड़ीevent.mult = भाग_sc(lapic_समयr_period/APIC_DIVISOR,
					TICK_NSEC, lapic_घड़ीevent.shअगरt);
	lapic_घड़ीevent.max_delta_ns =
		घड़ीevent_delta2ns(0x7FFFFFFF, &lapic_घड़ीevent);
	lapic_घड़ीevent.max_delta_ticks = 0x7FFFFFFF;
	lapic_घड़ीevent.min_delta_ns =
		घड़ीevent_delta2ns(0xF, &lapic_घड़ीevent);
	lapic_घड़ीevent.min_delta_ticks = 0xF;

	वापस 0;
पूर्ण

bool __init apic_needs_pit(व्योम)
अणु
	/*
	 * If the frequencies are not known, PIT is required क्रम both TSC
	 * and apic समयr calibration.
	 */
	अगर (!tsc_khz || !cpu_khz)
		वापस true;

	/* Is there an APIC at all or is it disabled? */
	अगर (!boot_cpu_has(X86_FEATURE_APIC) || disable_apic)
		वापस true;

	/*
	 * If पूर्णांकerrupt delivery mode is legacy PIC or भव wire without
	 * configuration, the local APIC समयr wont be set up. Make sure
	 * that the PIT is initialized.
	 */
	अगर (apic_पूर्णांकr_mode == APIC_PIC ||
	    apic_पूर्णांकr_mode == APIC_VIRTUAL_WIRE_NO_CONFIG)
		वापस true;

	/* Virt guests may lack ARAT, but still have DEADLINE */
	अगर (!boot_cpu_has(X86_FEATURE_ARAT))
		वापस true;

	/* Deadline समयr is based on TSC so no further PIT action required */
	अगर (boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		वापस false;

	/* APIC समयr disabled? */
	अगर (disable_apic_समयr)
		वापस true;
	/*
	 * The APIC समयr frequency is known alपढ़ोy, no PIT calibration
	 * required. If unknown, let the PIT be initialized.
	 */
	वापस lapic_समयr_period == 0;
पूर्ण

अटल पूर्णांक __init calibrate_APIC_घड़ी(व्योम)
अणु
	काष्ठा घड़ी_event_device *levt = this_cpu_ptr(&lapic_events);
	u64 tsc_perj = 0, tsc_start = 0;
	अचिन्हित दीर्घ jअगर_start;
	अचिन्हित दीर्घ deltaj;
	दीर्घ delta, deltatsc;
	पूर्णांक pm_referenced = 0;

	अगर (boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER))
		वापस 0;

	/*
	 * Check अगर lapic समयr has alपढ़ोy been calibrated by platक्रमm
	 * specअगरic routine, such as tsc calibration code. If so just fill
	 * in the घड़ीevent काष्ठाure and वापस.
	 */
	अगर (!lapic_init_घड़ीevent()) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, "lapic timer already calibrated %d\n",
			    lapic_समयr_period);
		/*
		 * Direct calibration methods must have an always running
		 * local APIC समयr, no need क्रम broadcast समयr.
		 */
		lapic_घड़ीevent.features &= ~CLOCK_EVT_FEAT_DUMMY;
		वापस 0;
	पूर्ण

	apic_prपूर्णांकk(APIC_VERBOSE, "Using local APIC timer interrupts.\n"
		    "calibrating APIC timer ...\n");

	/*
	 * There are platक्रमms w/o global घड़ीevent devices. Instead of
	 * making the calibration conditional on that, use a polling based
	 * approach everywhere.
	 */
	local_irq_disable();

	/*
	 * Setup the APIC counter to maximum. There is no way the lapic
	 * can underflow in the 100ms detection समय frame
	 */
	__setup_APIC_LVTT(0xffffffff, 0, 0);

	/*
	 * Methods to terminate the calibration loop:
	 *  1) Global घड़ीevent अगर available (jअगरfies)
	 *  2) TSC अगर available and frequency is known
	 */
	jअगर_start = READ_ONCE(jअगरfies);

	अगर (tsc_khz) अणु
		tsc_start = rdtsc();
		tsc_perj = भाग_u64((u64)tsc_khz * 1000, HZ);
	पूर्ण

	/*
	 * Enable पूर्णांकerrupts so the tick can fire, अगर a global
	 * घड़ीevent device is available
	 */
	local_irq_enable();

	जबतक (lapic_cal_loops <= LAPIC_CAL_LOOPS) अणु
		/* Wait क्रम a tick to elapse */
		जबतक (1) अणु
			अगर (tsc_khz) अणु
				u64 tsc_now = rdtsc();
				अगर ((tsc_now - tsc_start) >= tsc_perj) अणु
					tsc_start += tsc_perj;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ jअगर_now = READ_ONCE(jअगरfies);

				अगर (समय_after(jअगर_now, jअगर_start)) अणु
					jअगर_start = jअगर_now;
					अवरोध;
				पूर्ण
			पूर्ण
			cpu_relax();
		पूर्ण

		/* Invoke the calibration routine */
		local_irq_disable();
		lapic_cal_handler(शून्य);
		local_irq_enable();
	पूर्ण

	local_irq_disable();

	/* Build delta t1-t2 as apic समयr counts करोwn */
	delta = lapic_cal_t1 - lapic_cal_t2;
	apic_prपूर्णांकk(APIC_VERBOSE, "... lapic delta = %ld\n", delta);

	deltatsc = (दीर्घ)(lapic_cal_tsc2 - lapic_cal_tsc1);

	/* we trust the PM based calibration अगर possible */
	pm_referenced = !calibrate_by_pmसमयr(lapic_cal_pm2 - lapic_cal_pm1,
					&delta, &deltatsc);

	lapic_समयr_period = (delta * APIC_DIVISOR) / LAPIC_CAL_LOOPS;
	lapic_init_घड़ीevent();

	apic_prपूर्णांकk(APIC_VERBOSE, "..... delta %ld\n", delta);
	apic_prपूर्णांकk(APIC_VERBOSE, "..... mult: %u\n", lapic_घड़ीevent.mult);
	apic_prपूर्णांकk(APIC_VERBOSE, "..... calibration result: %u\n",
		    lapic_समयr_period);

	अगर (boot_cpu_has(X86_FEATURE_TSC)) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, "..... CPU clock speed is "
			    "%ld.%04ld MHz.\n",
			    (deltatsc / LAPIC_CAL_LOOPS) / (1000000 / HZ),
			    (deltatsc / LAPIC_CAL_LOOPS) % (1000000 / HZ));
	पूर्ण

	apic_prपूर्णांकk(APIC_VERBOSE, "..... host bus clock speed is "
		    "%u.%04u MHz.\n",
		    lapic_समयr_period / (1000000 / HZ),
		    lapic_समयr_period % (1000000 / HZ));

	/*
	 * Do a sanity check on the APIC calibration result
	 */
	अगर (lapic_समयr_period < (1000000 / HZ)) अणु
		local_irq_enable();
		pr_warn("APIC frequency too slow, disabling apic timer\n");
		वापस -1;
	पूर्ण

	levt->features &= ~CLOCK_EVT_FEAT_DUMMY;

	/*
	 * PM समयr calibration failed or not turned on so lets try APIC
	 * समयr based calibration, अगर a global घड़ीevent device is
	 * available.
	 */
	अगर (!pm_referenced && global_घड़ी_event) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, "... verify APIC timer\n");

		/*
		 * Setup the apic समयr manually
		 */
		levt->event_handler = lapic_cal_handler;
		lapic_समयr_set_periodic(levt);
		lapic_cal_loops = -1;

		/* Let the पूर्णांकerrupts run */
		local_irq_enable();

		जबतक (lapic_cal_loops <= LAPIC_CAL_LOOPS)
			cpu_relax();

		/* Stop the lapic समयr */
		local_irq_disable();
		lapic_समयr_shutकरोwn(levt);

		/* Jअगरfies delta */
		deltaj = lapic_cal_j2 - lapic_cal_j1;
		apic_prपूर्णांकk(APIC_VERBOSE, "... jiffies delta = %lu\n", deltaj);

		/* Check, अगर the jअगरfies result is consistent */
		अगर (deltaj >= LAPIC_CAL_LOOPS-2 && deltaj <= LAPIC_CAL_LOOPS+2)
			apic_prपूर्णांकk(APIC_VERBOSE, "... jiffies result ok\n");
		अन्यथा
			levt->features |= CLOCK_EVT_FEAT_DUMMY;
	पूर्ण
	local_irq_enable();

	अगर (levt->features & CLOCK_EVT_FEAT_DUMMY) अणु
		pr_warn("APIC timer disabled due to verification failure\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Setup the boot APIC
 *
 * Calibrate and verअगरy the result.
 */
व्योम __init setup_boot_APIC_घड़ी(व्योम)
अणु
	/*
	 * The local apic समयr can be disabled via the kernel
	 * commandline or from the CPU detection code. Register the lapic
	 * समयr as a dummy घड़ी event source on SMP प्रणालीs, so the
	 * broadcast mechanism is used. On UP प्रणालीs simply ignore it.
	 */
	अगर (disable_apic_समयr) अणु
		pr_info("Disabling APIC timer\n");
		/* No broadcast on UP ! */
		अगर (num_possible_cpus() > 1) अणु
			lapic_घड़ीevent.mult = 1;
			setup_APIC_समयr();
		पूर्ण
		वापस;
	पूर्ण

	अगर (calibrate_APIC_घड़ी()) अणु
		/* No broadcast on UP ! */
		अगर (num_possible_cpus() > 1)
			setup_APIC_समयr();
		वापस;
	पूर्ण

	/*
	 * If nmi_watchकरोg is set to IO_APIC, we need the
	 * PIT/HPET going.  Otherwise रेजिस्टर lapic as a dummy
	 * device.
	 */
	lapic_घड़ीevent.features &= ~CLOCK_EVT_FEAT_DUMMY;

	/* Setup the lapic or request the broadcast */
	setup_APIC_समयr();
	amd_e400_c1e_apic_setup();
पूर्ण

व्योम setup_secondary_APIC_घड़ी(व्योम)
अणु
	setup_APIC_समयr();
	amd_e400_c1e_apic_setup();
पूर्ण

/*
 * The guts of the apic समयr पूर्णांकerrupt
 */
अटल व्योम local_apic_समयr_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&lapic_events);

	/*
	 * Normally we should not be here till LAPIC has been initialized but
	 * in some हालs like kdump, its possible that there is a pending LAPIC
	 * समयr पूर्णांकerrupt from previous kernel's context and is delivered in
	 * new kernel the moment पूर्णांकerrupts are enabled.
	 *
	 * Interrupts are enabled early and LAPIC is setup much later, hence
	 * its possible that when we get here evt->event_handler is शून्य.
	 * Check क्रम event_handler being शून्य and discard the पूर्णांकerrupt as
	 * spurious.
	 */
	अगर (!evt->event_handler) अणु
		pr_warn("Spurious LAPIC timer interrupt on cpu %d\n",
			smp_processor_id());
		/* Switch it off */
		lapic_समयr_shutकरोwn(evt);
		वापस;
	पूर्ण

	/*
	 * the NMI deadlock-detector uses this.
	 */
	inc_irq_stat(apic_समयr_irqs);

	evt->event_handler(evt);
पूर्ण

/*
 * Local APIC समयr पूर्णांकerrupt. This is the most natural way क्रम करोing
 * local पूर्णांकerrupts, but local समयr पूर्णांकerrupts can be emulated by
 * broadcast पूर्णांकerrupts too. [in हाल the hw करोesn't support APIC समयrs]
 *
 * [ अगर a single-CPU प्रणाली runs an SMP kernel then we call the local
 *   पूर्णांकerrupt as well. Thus we cannot अंतरभूत the local irq ... ]
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_apic_समयr_पूर्णांकerrupt)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	ack_APIC_irq();
	trace_local_समयr_entry(LOCAL_TIMER_VECTOR);
	local_apic_समयr_पूर्णांकerrupt();
	trace_local_समयr_निकास(LOCAL_TIMER_VECTOR);

	set_irq_regs(old_regs);
पूर्ण

पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

/*
 * Local APIC start and shutकरोwn
 */

/**
 * clear_local_APIC - shutकरोwn the local APIC
 *
 * This is called, when a CPU is disabled and beक्रमe rebooting, so the state of
 * the local APIC has no dangling leftovers. Also used to cleanout any BIOS
 * leftovers during boot.
 */
व्योम clear_local_APIC(व्योम)
अणु
	पूर्णांक maxlvt;
	u32 v;

	/* APIC hasn't been mapped yet */
	अगर (!x2apic_mode && !apic_phys)
		वापस;

	maxlvt = lapic_get_maxlvt();
	/*
	 * Masking an LVT entry can trigger a local APIC error
	 * अगर the vector is zero. Mask LVTERR first to prevent this.
	 */
	अगर (maxlvt >= 3) अणु
		v = ERROR_APIC_VECTOR; /* any non-zero vector will करो */
		apic_ग_लिखो(APIC_LVTERR, v | APIC_LVT_MASKED);
	पूर्ण
	/*
	 * Careful: we have to set masks only first to deनिश्चित
	 * any level-triggered sources.
	 */
	v = apic_पढ़ो(APIC_LVTT);
	apic_ग_लिखो(APIC_LVTT, v | APIC_LVT_MASKED);
	v = apic_पढ़ो(APIC_LVT0);
	apic_ग_लिखो(APIC_LVT0, v | APIC_LVT_MASKED);
	v = apic_पढ़ो(APIC_LVT1);
	apic_ग_लिखो(APIC_LVT1, v | APIC_LVT_MASKED);
	अगर (maxlvt >= 4) अणु
		v = apic_पढ़ो(APIC_LVTPC);
		apic_ग_लिखो(APIC_LVTPC, v | APIC_LVT_MASKED);
	पूर्ण

	/* lets not touch this अगर we didn't frob it */
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	अगर (maxlvt >= 5) अणु
		v = apic_पढ़ो(APIC_LVTTHMR);
		apic_ग_लिखो(APIC_LVTTHMR, v | APIC_LVT_MASKED);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_INTEL
	अगर (maxlvt >= 6) अणु
		v = apic_पढ़ो(APIC_LVTCMCI);
		अगर (!(v & APIC_LVT_MASKED))
			apic_ग_लिखो(APIC_LVTCMCI, v | APIC_LVT_MASKED);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Clean APIC state क्रम other OSs:
	 */
	apic_ग_लिखो(APIC_LVTT, APIC_LVT_MASKED);
	apic_ग_लिखो(APIC_LVT0, APIC_LVT_MASKED);
	apic_ग_लिखो(APIC_LVT1, APIC_LVT_MASKED);
	अगर (maxlvt >= 3)
		apic_ग_लिखो(APIC_LVTERR, APIC_LVT_MASKED);
	अगर (maxlvt >= 4)
		apic_ग_लिखो(APIC_LVTPC, APIC_LVT_MASKED);

	/* Integrated APIC (!82489DX) ? */
	अगर (lapic_is_पूर्णांकegrated()) अणु
		अगर (maxlvt > 3)
			/* Clear ESR due to Pentium errata 3AP and 11AP */
			apic_ग_लिखो(APIC_ESR, 0);
		apic_पढ़ो(APIC_ESR);
	पूर्ण
पूर्ण

/**
 * apic_soft_disable - Clears and software disables the local APIC on hotplug
 *
 * Contrary to disable_local_APIC() this करोes not touch the enable bit in
 * MSR_IA32_APICBASE. Clearing that bit on प्रणालीs based on the 3 wire APIC
 * bus would require a hardware reset as the APIC would lose track of bus
 * arbitration. On प्रणालीs with FSB delivery APICBASE could be disabled,
 * but it has to be guaranteed that no पूर्णांकerrupt is sent to the APIC जबतक
 * in that state and it's not clear from the SDM whether it still responds
 * to INIT/SIPI messages. Stay on the safe side and use software disable.
 */
व्योम apic_soft_disable(व्योम)
अणु
	u32 value;

	clear_local_APIC();

	/* Soft disable APIC (implies clearing of रेजिस्टरs क्रम 82489DX!). */
	value = apic_पढ़ो(APIC_SPIV);
	value &= ~APIC_SPIV_APIC_ENABLED;
	apic_ग_लिखो(APIC_SPIV, value);
पूर्ण

/**
 * disable_local_APIC - clear and disable the local APIC
 */
व्योम disable_local_APIC(व्योम)
अणु
	/* APIC hasn't been mapped yet */
	अगर (!x2apic_mode && !apic_phys)
		वापस;

	apic_soft_disable();

#अगर_घोषित CONFIG_X86_32
	/*
	 * When LAPIC was disabled by the BIOS and enabled by the kernel,
	 * restore the disabled state.
	 */
	अगर (enabled_via_apicbase) अणु
		अचिन्हित पूर्णांक l, h;

		rdmsr(MSR_IA32_APICBASE, l, h);
		l &= ~MSR_IA32_APICBASE_ENABLE;
		wrmsr(MSR_IA32_APICBASE, l, h);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * If Linux enabled the LAPIC against the BIOS शेष disable it करोwn beक्रमe
 * re-entering the BIOS on shutकरोwn.  Otherwise the BIOS may get confused and
 * not घातer-off.  Additionally clear all LVT entries beक्रमe disable_local_APIC
 * क्रम the हाल where Linux didn't enable the LAPIC.
 */
व्योम lapic_shutकरोwn(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!boot_cpu_has(X86_FEATURE_APIC) && !apic_from_smp_config())
		वापस;

	local_irq_save(flags);

#अगर_घोषित CONFIG_X86_32
	अगर (!enabled_via_apicbase)
		clear_local_APIC();
	अन्यथा
#पूर्ण_अगर
		disable_local_APIC();


	local_irq_restore(flags);
पूर्ण

/**
 * sync_Arb_IDs - synchronize APIC bus arbitration IDs
 */
व्योम __init sync_Arb_IDs(व्योम)
अणु
	/*
	 * Unsupported on P4 - see Intel Dev. Manual Vol. 3, Ch. 8.6.1 And not
	 * needed on AMD.
	 */
	अगर (modern_apic() || boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD)
		वापस;

	/*
	 * Wait क्रम idle.
	 */
	apic_रुको_icr_idle();

	apic_prपूर्णांकk(APIC_DEBUG, "Synchronizing Arb IDs.\n");
	apic_ग_लिखो(APIC_ICR, APIC_DEST_ALLINC |
			APIC_INT_LEVELTRIG | APIC_DM_INIT);
पूर्ण

क्रमागत apic_पूर्णांकr_mode_id apic_पूर्णांकr_mode __ro_after_init;

अटल पूर्णांक __init __apic_पूर्णांकr_mode_select(व्योम)
अणु
	/* Check kernel option */
	अगर (disable_apic) अणु
		pr_info("APIC disabled via kernel command line\n");
		वापस APIC_PIC;
	पूर्ण

	/* Check BIOS */
#अगर_घोषित CONFIG_X86_64
	/* On 64-bit, the APIC must be पूर्णांकegrated, Check local APIC only */
	अगर (!boot_cpu_has(X86_FEATURE_APIC)) अणु
		disable_apic = 1;
		pr_info("APIC disabled by BIOS\n");
		वापस APIC_PIC;
	पूर्ण
#अन्यथा
	/* On 32-bit, the APIC may be पूर्णांकegrated APIC or 82489DX */

	/* Neither 82489DX nor पूर्णांकegrated APIC ? */
	अगर (!boot_cpu_has(X86_FEATURE_APIC) && !smp_found_config) अणु
		disable_apic = 1;
		वापस APIC_PIC;
	पूर्ण

	/* If the BIOS pretends there is an पूर्णांकegrated APIC ? */
	अगर (!boot_cpu_has(X86_FEATURE_APIC) &&
		APIC_INTEGRATED(boot_cpu_apic_version)) अणु
		disable_apic = 1;
		pr_err(FW_BUG "Local APIC %d not detected, force emulation\n",
				       boot_cpu_physical_apicid);
		वापस APIC_PIC;
	पूर्ण
#पूर्ण_अगर

	/* Check MP table or ACPI MADT configuration */
	अगर (!smp_found_config) अणु
		disable_ioapic_support();
		अगर (!acpi_lapic) अणु
			pr_info("APIC: ACPI MADT or MP tables are not detected\n");
			वापस APIC_VIRTUAL_WIRE_NO_CONFIG;
		पूर्ण
		वापस APIC_VIRTUAL_WIRE;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/* If SMP should be disabled, then really disable it! */
	अगर (!setup_max_cpus) अणु
		pr_info("APIC: SMP mode deactivated\n");
		वापस APIC_SYMMETRIC_IO_NO_ROUTING;
	पूर्ण

	अगर (पढ़ो_apic_id() != boot_cpu_physical_apicid) अणु
		panic("Boot APIC ID in local APIC unexpected (%d vs %d)",
		     पढ़ो_apic_id(), boot_cpu_physical_apicid);
		/* Or can we चयन back to PIC here? */
	पूर्ण
#पूर्ण_अगर

	वापस APIC_SYMMETRIC_IO;
पूर्ण

/* Select the पूर्णांकerrupt delivery mode क्रम the BSP */
व्योम __init apic_पूर्णांकr_mode_select(व्योम)
अणु
	apic_पूर्णांकr_mode = __apic_पूर्णांकr_mode_select();
पूर्ण

/*
 * An initial setup of the भव wire mode.
 */
व्योम __init init_bsp_APIC(व्योम)
अणु
	अचिन्हित पूर्णांक value;

	/*
	 * Don't करो the setup now अगर we have a SMP BIOS as the
	 * through-I/O-APIC भव wire mode might be active.
	 */
	अगर (smp_found_config || !boot_cpu_has(X86_FEATURE_APIC))
		वापस;

	/*
	 * Do not trust the local APIC being empty at bootup.
	 */
	clear_local_APIC();

	/*
	 * Enable APIC.
	 */
	value = apic_पढ़ो(APIC_SPIV);
	value &= ~APIC_VECTOR_MASK;
	value |= APIC_SPIV_APIC_ENABLED;

#अगर_घोषित CONFIG_X86_32
	/* This bit is reserved on P4/Xeon and should be cleared */
	अगर ((boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL) &&
	    (boot_cpu_data.x86 == 15))
		value &= ~APIC_SPIV_FOCUS_DISABLED;
	अन्यथा
#पूर्ण_अगर
		value |= APIC_SPIV_FOCUS_DISABLED;
	value |= SPURIOUS_APIC_VECTOR;
	apic_ग_लिखो(APIC_SPIV, value);

	/*
	 * Set up the भव wire mode.
	 */
	apic_ग_लिखो(APIC_LVT0, APIC_DM_EXTINT);
	value = APIC_DM_NMI;
	अगर (!lapic_is_पूर्णांकegrated())		/* 82489DX */
		value |= APIC_LVT_LEVEL_TRIGGER;
	अगर (apic_extnmi == APIC_EXTNMI_NONE)
		value |= APIC_LVT_MASKED;
	apic_ग_लिखो(APIC_LVT1, value);
पूर्ण

अटल व्योम __init apic_bsp_setup(bool upmode);

/* Init the पूर्णांकerrupt delivery mode क्रम the BSP */
व्योम __init apic_पूर्णांकr_mode_init(व्योम)
अणु
	bool upmode = IS_ENABLED(CONFIG_UP_LATE_INIT);

	चयन (apic_पूर्णांकr_mode) अणु
	हाल APIC_PIC:
		pr_info("APIC: Keep in PIC mode(8259)\n");
		वापस;
	हाल APIC_VIRTUAL_WIRE:
		pr_info("APIC: Switch to virtual wire mode setup\n");
		शेष_setup_apic_routing();
		अवरोध;
	हाल APIC_VIRTUAL_WIRE_NO_CONFIG:
		pr_info("APIC: Switch to virtual wire mode setup with no configuration\n");
		upmode = true;
		शेष_setup_apic_routing();
		अवरोध;
	हाल APIC_SYMMETRIC_IO:
		pr_info("APIC: Switch to symmetric I/O mode setup\n");
		शेष_setup_apic_routing();
		अवरोध;
	हाल APIC_SYMMETRIC_IO_NO_ROUTING:
		pr_info("APIC: Switch to symmetric I/O mode setup in no SMP routine\n");
		अवरोध;
	पूर्ण

	अगर (x86_platक्रमm.apic_post_init)
		x86_platक्रमm.apic_post_init();

	apic_bsp_setup(upmode);
पूर्ण

अटल व्योम lapic_setup_esr(व्योम)
अणु
	अचिन्हित पूर्णांक oldvalue, value, maxlvt;

	अगर (!lapic_is_पूर्णांकegrated()) अणु
		pr_info("No ESR for 82489DX.\n");
		वापस;
	पूर्ण

	अगर (apic->disable_esr) अणु
		/*
		 * Something untraceable is creating bad पूर्णांकerrupts on
		 * secondary quads ... क्रम the moment, just leave the
		 * ESR disabled - we can't करो anything useful with the
		 * errors anyway - mbligh
		 */
		pr_info("Leaving ESR disabled.\n");
		वापस;
	पूर्ण

	maxlvt = lapic_get_maxlvt();
	अगर (maxlvt > 3)		/* Due to the Pentium erratum 3AP. */
		apic_ग_लिखो(APIC_ESR, 0);
	oldvalue = apic_पढ़ो(APIC_ESR);

	/* enables sending errors */
	value = ERROR_APIC_VECTOR;
	apic_ग_लिखो(APIC_LVTERR, value);

	/*
	 * spec says clear errors after enabling vector.
	 */
	अगर (maxlvt > 3)
		apic_ग_लिखो(APIC_ESR, 0);
	value = apic_पढ़ो(APIC_ESR);
	अगर (value != oldvalue)
		apic_prपूर्णांकk(APIC_VERBOSE, "ESR value before enabling "
			"vector: 0x%08x  after: 0x%08x\n",
			oldvalue, value);
पूर्ण

#घोषणा APIC_IR_REGS		APIC_ISR_NR
#घोषणा APIC_IR_BITS		(APIC_IR_REGS * 32)
#घोषणा APIC_IR_MAPSIZE		(APIC_IR_BITS / BITS_PER_LONG)

जोड़ apic_ir अणु
	अचिन्हित दीर्घ	map[APIC_IR_MAPSIZE];
	u32		regs[APIC_IR_REGS];
पूर्ण;

अटल bool apic_check_and_ack(जोड़ apic_ir *irr, जोड़ apic_ir *isr)
अणु
	पूर्णांक i, bit;

	/* Read the IRRs */
	क्रम (i = 0; i < APIC_IR_REGS; i++)
		irr->regs[i] = apic_पढ़ो(APIC_IRR + i * 0x10);

	/* Read the ISRs */
	क्रम (i = 0; i < APIC_IR_REGS; i++)
		isr->regs[i] = apic_पढ़ो(APIC_ISR + i * 0x10);

	/*
	 * If the ISR map is not empty. ACK the APIC and run another round
	 * to verअगरy whether a pending IRR has been unblocked and turned
	 * पूर्णांकo a ISR.
	 */
	अगर (!biपंचांगap_empty(isr->map, APIC_IR_BITS)) अणु
		/*
		 * There can be multiple ISR bits set when a high priority
		 * पूर्णांकerrupt preempted a lower priority one. Issue an ACK
		 * per set bit.
		 */
		क्रम_each_set_bit(bit, isr->map, APIC_IR_BITS)
			ack_APIC_irq();
		वापस true;
	पूर्ण

	वापस !biपंचांगap_empty(irr->map, APIC_IR_BITS);
पूर्ण

/*
 * After a crash, we no दीर्घer service the पूर्णांकerrupts and a pending
 * पूर्णांकerrupt from previous kernel might still have ISR bit set.
 *
 * Most probably by now the CPU has serviced that pending पूर्णांकerrupt and it
 * might not have करोne the ack_APIC_irq() because it thought, पूर्णांकerrupt
 * came from i8259 as ExtInt. LAPIC did not get EOI so it करोes not clear
 * the ISR bit and cpu thinks it has alपढ़ोy serviced the पूर्णांकerrupt. Hence
 * a vector might get locked. It was noticed क्रम समयr irq (vector
 * 0x31). Issue an extra EOI to clear ISR.
 *
 * If there are pending IRR bits they turn पूर्णांकo ISR bits after a higher
 * priority ISR bit has been acked.
 */
अटल व्योम apic_pending_पूर्णांकr_clear(व्योम)
अणु
	जोड़ apic_ir irr, isr;
	अचिन्हित पूर्णांक i;

	/* 512 loops are way oversized and give the APIC a chance to obey. */
	क्रम (i = 0; i < 512; i++) अणु
		अगर (!apic_check_and_ack(&irr, &isr))
			वापस;
	पूर्ण
	/* Dump the IRR/ISR content अगर that failed */
	pr_warn("APIC: Stale IRR: %256pb ISR: %256pb\n", irr.map, isr.map);
पूर्ण

/**
 * setup_local_APIC - setup the local APIC
 *
 * Used to setup local APIC जबतक initializing BSP or bringing up APs.
 * Always called with preemption disabled.
 */
अटल व्योम setup_local_APIC(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक value;

	अगर (disable_apic) अणु
		disable_ioapic_support();
		वापस;
	पूर्ण

	/*
	 * If this comes from kexec/kcrash the APIC might be enabled in
	 * SPIV. Soft disable it beक्रमe करोing further initialization.
	 */
	value = apic_पढ़ो(APIC_SPIV);
	value &= ~APIC_SPIV_APIC_ENABLED;
	apic_ग_लिखो(APIC_SPIV, value);

#अगर_घोषित CONFIG_X86_32
	/* Pound the ESR really hard over the head with a big hammer - mbligh */
	अगर (lapic_is_पूर्णांकegrated() && apic->disable_esr) अणु
		apic_ग_लिखो(APIC_ESR, 0);
		apic_ग_लिखो(APIC_ESR, 0);
		apic_ग_लिखो(APIC_ESR, 0);
		apic_ग_लिखो(APIC_ESR, 0);
	पूर्ण
#पूर्ण_अगर
	/*
	 * Double-check whether this APIC is really रेजिस्टरed.
	 * This is meaningless in clustered apic mode, so we skip it.
	 */
	BUG_ON(!apic->apic_id_रेजिस्टरed());

	/*
	 * Intel recommends to set DFR, LDR and TPR beक्रमe enabling
	 * an APIC.  See e.g. "AP-388 82489DX User's Manual" (Intel
	 * करोcument number 292116).  So here it goes...
	 */
	apic->init_apic_ldr();

#अगर_घोषित CONFIG_X86_32
	अगर (apic->dest_mode_logical) अणु
		पूर्णांक logical_apicid, ldr_apicid;

		/*
		 * APIC LDR is initialized.  If logical_apicid mapping was
		 * initialized during get_smp_config(), make sure it matches
		 * the actual value.
		 */
		logical_apicid = early_per_cpu(x86_cpu_to_logical_apicid, cpu);
		ldr_apicid = GET_APIC_LOGICAL_ID(apic_पढ़ो(APIC_LDR));
		अगर (logical_apicid != BAD_APICID)
			WARN_ON(logical_apicid != ldr_apicid);
		/* Always use the value from LDR. */
		early_per_cpu(x86_cpu_to_logical_apicid, cpu) = ldr_apicid;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Set Task Priority to 'accept all except vectors 0-31'.  An APIC
	 * vector in the 16-31 range could be delivered अगर TPR == 0, but we
	 * would think it's an exception and terrible things will happen.  We
	 * never change this later on.
	 */
	value = apic_पढ़ो(APIC_TASKPRI);
	value &= ~APIC_TPRI_MASK;
	value |= 0x10;
	apic_ग_लिखो(APIC_TASKPRI, value);

	/* Clear eventually stale ISR/IRR bits */
	apic_pending_पूर्णांकr_clear();

	/*
	 * Now that we are all set up, enable the APIC
	 */
	value = apic_पढ़ो(APIC_SPIV);
	value &= ~APIC_VECTOR_MASK;
	/*
	 * Enable APIC
	 */
	value |= APIC_SPIV_APIC_ENABLED;

#अगर_घोषित CONFIG_X86_32
	/*
	 * Some unknown Intel IO/APIC (or APIC) errata is biting us with
	 * certain networking cards. If high frequency पूर्णांकerrupts are
	 * happening on a particular IOAPIC pin, plus the IOAPIC routing
	 * entry is masked/unmasked at a high rate as well then sooner or
	 * later IOAPIC line माला_लो 'stuck', no more पूर्णांकerrupts are received
	 * from the device. If focus CPU is disabled then the hang goes
	 * away, oh well :-(
	 *
	 * [ This bug can be reproduced easily with a level-triggered
	 *   PCI Ne2000 networking cards and PII/PIII processors, dual
	 *   BX chipset. ]
	 */
	/*
	 * Actually disabling the focus CPU check just makes the hang less
	 * frequent as it makes the पूर्णांकerrupt distribution model be more
	 * like LRU than MRU (the लघु-term load is more even across CPUs).
	 */

	/*
	 * - enable focus processor (bit==0)
	 * - 64bit mode always use processor focus
	 *   so no need to set it
	 */
	value &= ~APIC_SPIV_FOCUS_DISABLED;
#पूर्ण_अगर

	/*
	 * Set spurious IRQ vector
	 */
	value |= SPURIOUS_APIC_VECTOR;
	apic_ग_लिखो(APIC_SPIV, value);

	perf_events_lapic_init();

	/*
	 * Set up LVT0, LVT1:
	 *
	 * set up through-local-APIC on the boot CPU's LINT0. This is not
	 * strictly necessary in pure symmetric-IO mode, but someबार
	 * we delegate पूर्णांकerrupts to the 8259A.
	 */
	/*
	 * TODO: set up through-local-APIC from through-I/O-APIC? --macro
	 */
	value = apic_पढ़ो(APIC_LVT0) & APIC_LVT_MASKED;
	अगर (!cpu && (pic_mode || !value || skip_ioapic_setup)) अणु
		value = APIC_DM_EXTINT;
		apic_prपूर्णांकk(APIC_VERBOSE, "enabled ExtINT on CPU#%d\n", cpu);
	पूर्ण अन्यथा अणु
		value = APIC_DM_EXTINT | APIC_LVT_MASKED;
		apic_prपूर्णांकk(APIC_VERBOSE, "masked ExtINT on CPU#%d\n", cpu);
	पूर्ण
	apic_ग_लिखो(APIC_LVT0, value);

	/*
	 * Only the BSP sees the LINT1 NMI संकेत by शेष. This can be
	 * modअगरied by apic_extnmi= boot option.
	 */
	अगर ((!cpu && apic_extnmi != APIC_EXTNMI_NONE) ||
	    apic_extnmi == APIC_EXTNMI_ALL)
		value = APIC_DM_NMI;
	अन्यथा
		value = APIC_DM_NMI | APIC_LVT_MASKED;

	/* Is 82489DX ? */
	अगर (!lapic_is_पूर्णांकegrated())
		value |= APIC_LVT_LEVEL_TRIGGER;
	apic_ग_लिखो(APIC_LVT1, value);

#अगर_घोषित CONFIG_X86_MCE_INTEL
	/* Recheck CMCI inक्रमmation after local APIC is up on CPU #0 */
	अगर (!cpu)
		cmci_recheck();
#पूर्ण_अगर
पूर्ण

अटल व्योम end_local_APIC_setup(व्योम)
अणु
	lapic_setup_esr();

#अगर_घोषित CONFIG_X86_32
	अणु
		अचिन्हित पूर्णांक value;
		/* Disable the local apic समयr */
		value = apic_पढ़ो(APIC_LVTT);
		value |= (APIC_LVT_MASKED | LOCAL_TIMER_VECTOR);
		apic_ग_लिखो(APIC_LVTT, value);
	पूर्ण
#पूर्ण_अगर

	apic_pm_activate();
पूर्ण

/*
 * APIC setup function क्रम application processors. Called from smpboot.c
 */
व्योम apic_ap_setup(व्योम)
अणु
	setup_local_APIC();
	end_local_APIC_setup();
पूर्ण

#अगर_घोषित CONFIG_X86_X2APIC
पूर्णांक x2apic_mode;
EXPORT_SYMBOL_GPL(x2apic_mode);

क्रमागत अणु
	X2APIC_OFF,
	X2APIC_ON,
	X2APIC_DISABLED,
पूर्ण;
अटल पूर्णांक x2apic_state;

अटल व्योम __x2apic_disable(व्योम)
अणु
	u64 msr;

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस;

	rdmsrl(MSR_IA32_APICBASE, msr);
	अगर (!(msr & X2APIC_ENABLE))
		वापस;
	/* Disable xapic and x2apic first and then reenable xapic mode */
	wrmsrl(MSR_IA32_APICBASE, msr & ~(X2APIC_ENABLE | XAPIC_ENABLE));
	wrmsrl(MSR_IA32_APICBASE, msr & ~X2APIC_ENABLE);
	prपूर्णांकk_once(KERN_INFO "x2apic disabled\n");
पूर्ण

अटल व्योम __x2apic_enable(व्योम)
अणु
	u64 msr;

	rdmsrl(MSR_IA32_APICBASE, msr);
	अगर (msr & X2APIC_ENABLE)
		वापस;
	wrmsrl(MSR_IA32_APICBASE, msr | X2APIC_ENABLE);
	prपूर्णांकk_once(KERN_INFO "x2apic enabled\n");
पूर्ण

अटल पूर्णांक __init setup_nox2apic(अक्षर *str)
अणु
	अगर (x2apic_enabled()) अणु
		पूर्णांक apicid = native_apic_msr_पढ़ो(APIC_ID);

		अगर (apicid >= 255) अणु
			pr_warn("Apicid: %08x, cannot enforce nox2apic\n",
				apicid);
			वापस 0;
		पूर्ण
		pr_warn("x2apic already enabled.\n");
		__x2apic_disable();
	पूर्ण
	setup_clear_cpu_cap(X86_FEATURE_X2APIC);
	x2apic_state = X2APIC_DISABLED;
	x2apic_mode = 0;
	वापस 0;
पूर्ण
early_param("nox2apic", setup_nox2apic);

/* Called from cpu_init() to enable x2apic on (secondary) cpus */
व्योम x2apic_setup(व्योम)
अणु
	/*
	 * If x2apic is not in ON state, disable it अगर alपढ़ोy enabled
	 * from BIOS.
	 */
	अगर (x2apic_state != X2APIC_ON) अणु
		__x2apic_disable();
		वापस;
	पूर्ण
	__x2apic_enable();
पूर्ण

अटल __init व्योम x2apic_disable(व्योम)
अणु
	u32 x2apic_id, state = x2apic_state;

	x2apic_mode = 0;
	x2apic_state = X2APIC_DISABLED;

	अगर (state != X2APIC_ON)
		वापस;

	x2apic_id = पढ़ो_apic_id();
	अगर (x2apic_id >= 255)
		panic("Cannot disable x2apic, id: %08x\n", x2apic_id);

	__x2apic_disable();
	रेजिस्टर_lapic_address(mp_lapic_addr);
पूर्ण

अटल __init व्योम x2apic_enable(व्योम)
अणु
	अगर (x2apic_state != X2APIC_OFF)
		वापस;

	x2apic_mode = 1;
	x2apic_state = X2APIC_ON;
	__x2apic_enable();
पूर्ण

अटल __init व्योम try_to_enable_x2apic(पूर्णांक remap_mode)
अणु
	अगर (x2apic_state == X2APIC_DISABLED)
		वापस;

	अगर (remap_mode != IRQ_REMAP_X2APIC_MODE) अणु
		u32 apic_limit = 255;

		/*
		 * Using X2APIC without IR is not architecturally supported
		 * on bare metal but may be supported in guests.
		 */
		अगर (!x86_init.hyper.x2apic_available()) अणु
			pr_info("x2apic: IRQ remapping doesn't support X2APIC mode\n");
			x2apic_disable();
			वापस;
		पूर्ण

		/*
		 * If the hypervisor supports extended destination ID in
		 * MSI, that increases the maximum APIC ID that can be
		 * used क्रम non-remapped IRQ करोमुख्यs.
		 */
		अगर (x86_init.hyper.msi_ext_dest_id()) अणु
			virt_ext_dest_id = 1;
			apic_limit = 32767;
		पूर्ण

		/*
		 * Without IR, all CPUs can be addressed by IOAPIC/MSI only
		 * in physical mode, and CPUs with an APIC ID that cannot
		 * be addressed must not be brought online.
		 */
		x2apic_set_max_apicid(apic_limit);
		x2apic_phys = 1;
	पूर्ण
	x2apic_enable();
पूर्ण

व्योम __init check_x2apic(व्योम)
अणु
	अगर (x2apic_enabled()) अणु
		pr_info("x2apic: enabled by BIOS, switching to x2apic ops\n");
		x2apic_mode = 1;
		x2apic_state = X2APIC_ON;
	पूर्ण अन्यथा अगर (!boot_cpu_has(X86_FEATURE_X2APIC)) अणु
		x2apic_state = X2APIC_DISABLED;
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_X86_X2APIC */
अटल पूर्णांक __init validate_x2apic(व्योम)
अणु
	अगर (!apic_is_x2apic_enabled())
		वापस 0;
	/*
	 * Checkme: Can we simply turn off x2apic here instead of panic?
	 */
	panic("BIOS has enabled x2apic but kernel doesn't support x2apic, please disable x2apic in BIOS.\n");
पूर्ण
early_initcall(validate_x2apic);

अटल अंतरभूत व्योम try_to_enable_x2apic(पूर्णांक remap_mode) अणु पूर्ण
अटल अंतरभूत व्योम __x2apic_enable(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_X86_X2APIC */

व्योम __init enable_IR_x2apic(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, ir_stat;

	अगर (skip_ioapic_setup) अणु
		pr_info("Not enabling interrupt remapping due to skipped IO-APIC setup\n");
		वापस;
	पूर्ण

	ir_stat = irq_remapping_prepare();
	अगर (ir_stat < 0 && !x2apic_supported())
		वापस;

	ret = save_ioapic_entries();
	अगर (ret) अणु
		pr_info("Saving IO-APIC state failed: %d\n", ret);
		वापस;
	पूर्ण

	local_irq_save(flags);
	legacy_pic->mask_all();
	mask_ioapic_entries();

	/* If irq_remapping_prepare() succeeded, try to enable it */
	अगर (ir_stat >= 0)
		ir_stat = irq_remapping_enable();
	/* ir_stat contains the remap mode or an error code */
	try_to_enable_x2apic(ir_stat);

	अगर (ir_stat < 0)
		restore_ioapic_entries();
	legacy_pic->restore_mask();
	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * Detect and enable local APICs on non-SMP boards.
 * Original code written by Keir Fraser.
 * On AMD64 we trust the BIOS - अगर it says no APIC it is likely
 * not correctly set up (usually the APIC समयr won't work etc.)
 */
अटल पूर्णांक __init detect_init_APIC(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_APIC)) अणु
		pr_info("No local APIC present\n");
		वापस -1;
	पूर्ण

	mp_lapic_addr = APIC_DEFAULT_PHYS_BASE;
	वापस 0;
पूर्ण
#अन्यथा

अटल पूर्णांक __init apic_verअगरy(व्योम)
अणु
	u32 features, h, l;

	/*
	 * The APIC feature bit should now be enabled
	 * in `cpuid'
	 */
	features = cpuid_edx(1);
	अगर (!(features & (1 << X86_FEATURE_APIC))) अणु
		pr_warn("Could not enable APIC!\n");
		वापस -1;
	पूर्ण
	set_cpu_cap(&boot_cpu_data, X86_FEATURE_APIC);
	mp_lapic_addr = APIC_DEFAULT_PHYS_BASE;

	/* The BIOS may have set up the APIC at some other address */
	अगर (boot_cpu_data.x86 >= 6) अणु
		rdmsr(MSR_IA32_APICBASE, l, h);
		अगर (l & MSR_IA32_APICBASE_ENABLE)
			mp_lapic_addr = l & MSR_IA32_APICBASE_BASE;
	पूर्ण

	pr_info("Found and enabled local APIC!\n");
	वापस 0;
पूर्ण

पूर्णांक __init apic_क्रमce_enable(अचिन्हित दीर्घ addr)
अणु
	u32 h, l;

	अगर (disable_apic)
		वापस -1;

	/*
	 * Some BIOSes disable the local APIC in the APIC_BASE
	 * MSR. This can only be करोne in software क्रम Intel P6 or later
	 * and AMD K7 (Model > 1) or later.
	 */
	अगर (boot_cpu_data.x86 >= 6) अणु
		rdmsr(MSR_IA32_APICBASE, l, h);
		अगर (!(l & MSR_IA32_APICBASE_ENABLE)) अणु
			pr_info("Local APIC disabled by BIOS -- reenabling.\n");
			l &= ~MSR_IA32_APICBASE_BASE;
			l |= MSR_IA32_APICBASE_ENABLE | addr;
			wrmsr(MSR_IA32_APICBASE, l, h);
			enabled_via_apicbase = 1;
		पूर्ण
	पूर्ण
	वापस apic_verअगरy();
पूर्ण

/*
 * Detect and initialize APIC
 */
अटल पूर्णांक __init detect_init_APIC(व्योम)
अणु
	/* Disabled by kernel option? */
	अगर (disable_apic)
		वापस -1;

	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_AMD:
		अगर ((boot_cpu_data.x86 == 6 && boot_cpu_data.x86_model > 1) ||
		    (boot_cpu_data.x86 >= 15))
			अवरोध;
		जाओ no_apic;
	हाल X86_VENDOR_HYGON:
		अवरोध;
	हाल X86_VENDOR_INTEL:
		अगर (boot_cpu_data.x86 == 6 || boot_cpu_data.x86 == 15 ||
		    (boot_cpu_data.x86 == 5 && boot_cpu_has(X86_FEATURE_APIC)))
			अवरोध;
		जाओ no_apic;
	शेष:
		जाओ no_apic;
	पूर्ण

	अगर (!boot_cpu_has(X86_FEATURE_APIC)) अणु
		/*
		 * Over-ride BIOS and try to enable the local APIC only अगर
		 * "lapic" specअगरied.
		 */
		अगर (!क्रमce_enable_local_apic) अणु
			pr_info("Local APIC disabled by BIOS -- "
				"you can enable it with \"lapic\"\n");
			वापस -1;
		पूर्ण
		अगर (apic_क्रमce_enable(APIC_DEFAULT_PHYS_BASE))
			वापस -1;
	पूर्ण अन्यथा अणु
		अगर (apic_verअगरy())
			वापस -1;
	पूर्ण

	apic_pm_activate();

	वापस 0;

no_apic:
	pr_info("No local APIC present or hardware disabled\n");
	वापस -1;
पूर्ण
#पूर्ण_अगर

/**
 * init_apic_mappings - initialize APIC mappings
 */
व्योम __init init_apic_mappings(व्योम)
अणु
	अचिन्हित पूर्णांक new_apicid;

	अगर (apic_validate_deadline_समयr())
		pr_info("TSC deadline timer available\n");

	अगर (x2apic_mode) अणु
		boot_cpu_physical_apicid = पढ़ो_apic_id();
		वापस;
	पूर्ण

	/* If no local APIC can be found वापस early */
	अगर (!smp_found_config && detect_init_APIC()) अणु
		/* lets NOP'अगरy apic operations */
		pr_info("APIC: disable apic facility\n");
		apic_disable();
	पूर्ण अन्यथा अणु
		apic_phys = mp_lapic_addr;

		/*
		 * If the प्रणाली has ACPI MADT tables or MP info, the LAPIC
		 * address is alपढ़ोy रेजिस्टरed.
		 */
		अगर (!acpi_lapic && !smp_found_config)
			रेजिस्टर_lapic_address(apic_phys);
	पूर्ण

	/*
	 * Fetch the APIC ID of the BSP in हाल we have a
	 * शेष configuration (or the MP table is broken).
	 */
	new_apicid = पढ़ो_apic_id();
	अगर (boot_cpu_physical_apicid != new_apicid) अणु
		boot_cpu_physical_apicid = new_apicid;
		/*
		 * yeah -- we lie about apic_version
		 * in हाल अगर apic was disabled via boot option
		 * but it's not a problem क्रम SMP compiled kernel
		 * since apic_पूर्णांकr_mode_select is prepared क्रम such
		 * a हाल and disable smp mode
		 */
		boot_cpu_apic_version = GET_APIC_VERSION(apic_पढ़ो(APIC_LVR));
	पूर्ण
पूर्ण

व्योम __init रेजिस्टर_lapic_address(अचिन्हित दीर्घ address)
अणु
	mp_lapic_addr = address;

	अगर (!x2apic_mode) अणु
		set_fixmap_nocache(FIX_APIC_BASE, address);
		apic_prपूर्णांकk(APIC_VERBOSE, "mapped APIC to %16lx (%16lx)\n",
			    APIC_BASE, address);
	पूर्ण
	अगर (boot_cpu_physical_apicid == -1U) अणु
		boot_cpu_physical_apicid  = पढ़ो_apic_id();
		boot_cpu_apic_version = GET_APIC_VERSION(apic_पढ़ो(APIC_LVR));
	पूर्ण
पूर्ण

/*
 * Local APIC पूर्णांकerrupts
 */

/*
 * Common handling code क्रम spurious_पूर्णांकerrupt and spurious_vector entry
 * poपूर्णांकs below. No poपूर्णांक in allowing the compiler to अंतरभूत it twice.
 */
अटल noअंतरभूत व्योम handle_spurious_पूर्णांकerrupt(u8 vector)
अणु
	u32 v;

	trace_spurious_apic_entry(vector);

	inc_irq_stat(irq_spurious_count);

	/*
	 * If this is a spurious पूर्णांकerrupt then करो not acknowledge
	 */
	अगर (vector == SPURIOUS_APIC_VECTOR) अणु
		/* See SDM vol 3 */
		pr_info("Spurious APIC interrupt (vector 0xFF) on CPU#%d, should never happen.\n",
			smp_processor_id());
		जाओ out;
	पूर्ण

	/*
	 * If it is a vectored one, verअगरy it's set in the ISR. If set,
	 * acknowledge it.
	 */
	v = apic_पढ़ो(APIC_ISR + ((vector & ~0x1f) >> 1));
	अगर (v & (1 << (vector & 0x1f))) अणु
		pr_info("Spurious interrupt (vector 0x%02x) on CPU#%d. Acked\n",
			vector, smp_processor_id());
		ack_APIC_irq();
	पूर्ण अन्यथा अणु
		pr_info("Spurious interrupt (vector 0x%02x) on CPU#%d. Not pending!\n",
			vector, smp_processor_id());
	पूर्ण
out:
	trace_spurious_apic_निकास(vector);
पूर्ण

/**
 * spurious_पूर्णांकerrupt - Catch all क्रम पूर्णांकerrupts उठाओd on unused vectors
 * @regs:	Poपूर्णांकer to pt_regs on stack
 * @vector:	The vector number
 *
 * This is invoked from ASM entry code to catch all पूर्णांकerrupts which
 * trigger on an entry which is routed to the common_spurious idtentry
 * poपूर्णांक.
 */
DEFINE_IDTENTRY_IRQ(spurious_पूर्णांकerrupt)
अणु
	handle_spurious_पूर्णांकerrupt(vector);
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_spurious_apic_पूर्णांकerrupt)
अणु
	handle_spurious_पूर्णांकerrupt(SPURIOUS_APIC_VECTOR);
पूर्ण

/*
 * This पूर्णांकerrupt should never happen with our APIC/SMP architecture
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_error_पूर्णांकerrupt)
अणु
	अटल स्थिर अक्षर * स्थिर error_पूर्णांकerrupt_reason[] = अणु
		"Send CS error",		/* APIC Error Bit 0 */
		"Receive CS error",		/* APIC Error Bit 1 */
		"Send accept error",		/* APIC Error Bit 2 */
		"Receive accept error",		/* APIC Error Bit 3 */
		"Redirectable IPI",		/* APIC Error Bit 4 */
		"Send illegal vector",		/* APIC Error Bit 5 */
		"Received illegal vector",	/* APIC Error Bit 6 */
		"Illegal register address",	/* APIC Error Bit 7 */
	पूर्ण;
	u32 v, i = 0;

	trace_error_apic_entry(ERROR_APIC_VECTOR);

	/* First tickle the hardware, only then report what went on. -- REW */
	अगर (lapic_get_maxlvt() > 3)	/* Due to the Pentium erratum 3AP. */
		apic_ग_लिखो(APIC_ESR, 0);
	v = apic_पढ़ो(APIC_ESR);
	ack_APIC_irq();
	atomic_inc(&irq_err_count);

	apic_prपूर्णांकk(APIC_DEBUG, KERN_DEBUG "APIC error on CPU%d: %02x",
		    smp_processor_id(), v);

	v &= 0xff;
	जबतक (v) अणु
		अगर (v & 0x1)
			apic_prपूर्णांकk(APIC_DEBUG, KERN_CONT " : %s", error_पूर्णांकerrupt_reason[i]);
		i++;
		v >>= 1;
	पूर्ण

	apic_prपूर्णांकk(APIC_DEBUG, KERN_CONT "\n");

	trace_error_apic_निकास(ERROR_APIC_VECTOR);
पूर्ण

/**
 * connect_bsp_APIC - attach the APIC to the पूर्णांकerrupt प्रणाली
 */
अटल व्योम __init connect_bsp_APIC(व्योम)
अणु
#अगर_घोषित CONFIG_X86_32
	अगर (pic_mode) अणु
		/*
		 * Do not trust the local APIC being empty at bootup.
		 */
		clear_local_APIC();
		/*
		 * PIC mode, enable APIC mode in the IMCR, i.e.  connect BSP's
		 * local APIC to INT and NMI lines.
		 */
		apic_prपूर्णांकk(APIC_VERBOSE, "leaving PIC mode, "
				"enabling APIC mode.\n");
		imcr_pic_to_apic();
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**
 * disconnect_bsp_APIC - detach the APIC from the पूर्णांकerrupt प्रणाली
 * @virt_wire_setup:	indicates, whether भव wire mode is selected
 *
 * Virtual wire mode is necessary to deliver legacy पूर्णांकerrupts even when the
 * APIC is disabled.
 */
व्योम disconnect_bsp_APIC(पूर्णांक virt_wire_setup)
अणु
	अचिन्हित पूर्णांक value;

#अगर_घोषित CONFIG_X86_32
	अगर (pic_mode) अणु
		/*
		 * Put the board back पूर्णांकo PIC mode (has an effect only on
		 * certain older boards).  Note that APIC पूर्णांकerrupts, including
		 * IPIs, won't work beyond this poपूर्णांक!  The only exception are
		 * INIT IPIs.
		 */
		apic_prपूर्णांकk(APIC_VERBOSE, "disabling APIC mode, "
				"entering PIC mode.\n");
		imcr_apic_to_pic();
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Go back to Virtual Wire compatibility mode */

	/* For the spurious पूर्णांकerrupt use vector F, and enable it */
	value = apic_पढ़ो(APIC_SPIV);
	value &= ~APIC_VECTOR_MASK;
	value |= APIC_SPIV_APIC_ENABLED;
	value |= 0xf;
	apic_ग_लिखो(APIC_SPIV, value);

	अगर (!virt_wire_setup) अणु
		/*
		 * For LVT0 make it edge triggered, active high,
		 * बाह्यal and enabled
		 */
		value = apic_पढ़ो(APIC_LVT0);
		value &= ~(APIC_MODE_MASK | APIC_SEND_PENDING |
			APIC_INPUT_POLARITY | APIC_LVT_REMOTE_IRR |
			APIC_LVT_LEVEL_TRIGGER | APIC_LVT_MASKED);
		value |= APIC_LVT_REMOTE_IRR | APIC_SEND_PENDING;
		value = SET_APIC_DELIVERY_MODE(value, APIC_MODE_EXTINT);
		apic_ग_लिखो(APIC_LVT0, value);
	पूर्ण अन्यथा अणु
		/* Disable LVT0 */
		apic_ग_लिखो(APIC_LVT0, APIC_LVT_MASKED);
	पूर्ण

	/*
	 * For LVT1 make it edge triggered, active high,
	 * nmi and enabled
	 */
	value = apic_पढ़ो(APIC_LVT1);
	value &= ~(APIC_MODE_MASK | APIC_SEND_PENDING |
			APIC_INPUT_POLARITY | APIC_LVT_REMOTE_IRR |
			APIC_LVT_LEVEL_TRIGGER | APIC_LVT_MASKED);
	value |= APIC_LVT_REMOTE_IRR | APIC_SEND_PENDING;
	value = SET_APIC_DELIVERY_MODE(value, APIC_MODE_NMI);
	apic_ग_लिखो(APIC_LVT1, value);
पूर्ण

/*
 * The number of allocated logical CPU IDs. Since logical CPU IDs are allocated
 * contiguously, it equals to current allocated max logical CPU ID plus 1.
 * All allocated CPU IDs should be in the [0, nr_logical_cpuids) range,
 * so the maximum of nr_logical_cpuids is nr_cpu_ids.
 *
 * NOTE: Reserve 0 क्रम BSP.
 */
अटल पूर्णांक nr_logical_cpuids = 1;

/*
 * Used to store mapping between logical CPU IDs and APIC IDs.
 */
अटल पूर्णांक cpuid_to_apicid[] = अणु
	[0 ... NR_CPUS - 1] = -1,
पूर्ण;

bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
	वापस phys_id == cpuid_to_apicid[cpu];
पूर्ण

#अगर_घोषित CONFIG_SMP
/**
 * apic_id_is_primary_thपढ़ो - Check whether APIC ID beदीर्घs to a primary thपढ़ो
 * @apicid: APIC ID to check
 */
bool apic_id_is_primary_thपढ़ो(अचिन्हित पूर्णांक apicid)
अणु
	u32 mask;

	अगर (smp_num_siblings == 1)
		वापस true;
	/* Isolate the SMT bit(s) in the APICID and check क्रम 0 */
	mask = (1U << (fls(smp_num_siblings) - 1)) - 1;
	वापस !(apicid & mask);
पूर्ण
#पूर्ण_अगर

/*
 * Should use this API to allocate logical CPU IDs to keep nr_logical_cpuids
 * and cpuid_to_apicid[] synchronized.
 */
अटल पूर्णांक allocate_logical_cpuid(पूर्णांक apicid)
अणु
	पूर्णांक i;

	/*
	 * cpuid <-> apicid mapping is persistent, so when a cpu is up,
	 * check अगर the kernel has allocated a cpuid क्रम it.
	 */
	क्रम (i = 0; i < nr_logical_cpuids; i++) अणु
		अगर (cpuid_to_apicid[i] == apicid)
			वापस i;
	पूर्ण

	/* Allocate a new cpuid. */
	अगर (nr_logical_cpuids >= nr_cpu_ids) अणु
		WARN_ONCE(1, "APIC: NR_CPUS/possible_cpus limit of %u reached. "
			     "Processor %d/0x%x and the rest are ignored.\n",
			     nr_cpu_ids, nr_logical_cpuids, apicid);
		वापस -EINVAL;
	पूर्ण

	cpuid_to_apicid[nr_logical_cpuids] = apicid;
	वापस nr_logical_cpuids++;
पूर्ण

पूर्णांक generic_processor_info(पूर्णांक apicid, पूर्णांक version)
अणु
	पूर्णांक cpu, max = nr_cpu_ids;
	bool boot_cpu_detected = physid_isset(boot_cpu_physical_apicid,
				phys_cpu_present_map);

	/*
	 * boot_cpu_physical_apicid is deचिन्हित to have the apicid
	 * वापसed by पढ़ो_apic_id(), i.e, the apicid of the
	 * currently booting-up processor. However, on some platक्रमms,
	 * it is temporarily modअगरied by the apicid reported as BSP
	 * through MP table. Concretely:
	 *
	 * - arch/x86/kernel/mpparse.c: MP_processor_info()
	 * - arch/x86/mm/amdtopology.c: amd_numa_init()
	 *
	 * This function is executed with the modअगरied
	 * boot_cpu_physical_apicid. So, disabled_cpu_apicid kernel
	 * parameter करोesn't work to disable APs on kdump 2nd kernel.
	 *
	 * Since fixing handling of boot_cpu_physical_apicid requires
	 * another discussion and tests on each platक्रमm, we leave it
	 * क्रम now and here we use पढ़ो_apic_id() directly in this
	 * function, generic_processor_info().
	 */
	अगर (disabled_cpu_apicid != BAD_APICID &&
	    disabled_cpu_apicid != पढ़ो_apic_id() &&
	    disabled_cpu_apicid == apicid) अणु
		पूर्णांक thiscpu = num_processors + disabled_cpus;

		pr_warn("APIC: Disabling requested cpu."
			" Processor %d/0x%x ignored.\n", thiscpu, apicid);

		disabled_cpus++;
		वापस -ENODEV;
	पूर्ण

	/*
	 * If boot cpu has not been detected yet, then only allow upto
	 * nr_cpu_ids - 1 processors and keep one slot मुक्त क्रम boot cpu
	 */
	अगर (!boot_cpu_detected && num_processors >= nr_cpu_ids - 1 &&
	    apicid != boot_cpu_physical_apicid) अणु
		पूर्णांक thiscpu = max + disabled_cpus - 1;

		pr_warn("APIC: NR_CPUS/possible_cpus limit of %i almost"
			" reached. Keeping one slot for boot cpu."
			"  Processor %d/0x%x ignored.\n", max, thiscpu, apicid);

		disabled_cpus++;
		वापस -ENODEV;
	पूर्ण

	अगर (num_processors >= nr_cpu_ids) अणु
		पूर्णांक thiscpu = max + disabled_cpus;

		pr_warn("APIC: NR_CPUS/possible_cpus limit of %i reached. "
			"Processor %d/0x%x ignored.\n", max, thiscpu, apicid);

		disabled_cpus++;
		वापस -EINVAL;
	पूर्ण

	अगर (apicid == boot_cpu_physical_apicid) अणु
		/*
		 * x86_bios_cpu_apicid is required to have processors listed
		 * in same order as logical cpu numbers. Hence the first
		 * entry is BSP, and so on.
		 * boot_cpu_init() alपढ़ोy hold bit 0 in cpu_present_mask
		 * क्रम BSP.
		 */
		cpu = 0;

		/* Logical cpuid 0 is reserved क्रम BSP. */
		cpuid_to_apicid[0] = apicid;
	पूर्ण अन्यथा अणु
		cpu = allocate_logical_cpuid(apicid);
		अगर (cpu < 0) अणु
			disabled_cpus++;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Validate version
	 */
	अगर (version == 0x0) अणु
		pr_warn("BIOS bug: APIC version is 0 for CPU %d/0x%x, fixing up to 0x10\n",
			cpu, apicid);
		version = 0x10;
	पूर्ण

	अगर (version != boot_cpu_apic_version) अणु
		pr_warn("BIOS bug: APIC version mismatch, boot CPU: %x, CPU %d: version %x\n",
			boot_cpu_apic_version, cpu, version);
	पूर्ण

	अगर (apicid > max_physical_apicid)
		max_physical_apicid = apicid;

#अगर defined(CONFIG_SMP) || defined(CONFIG_X86_64)
	early_per_cpu(x86_cpu_to_apicid, cpu) = apicid;
	early_per_cpu(x86_bios_cpu_apicid, cpu) = apicid;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_32
	early_per_cpu(x86_cpu_to_logical_apicid, cpu) =
		apic->x86_32_early_logical_apicid(cpu);
#पूर्ण_अगर
	set_cpu_possible(cpu, true);
	physid_set(apicid, phys_cpu_present_map);
	set_cpu_present(cpu, true);
	num_processors++;

	वापस cpu;
पूर्ण

पूर्णांक hard_smp_processor_id(व्योम)
अणु
	वापस पढ़ो_apic_id();
पूर्ण

व्योम __irq_msi_compose_msg(काष्ठा irq_cfg *cfg, काष्ठा msi_msg *msg,
			   bool dmar)
अणु
	स_रखो(msg, 0, माप(*msg));

	msg->arch_addr_lo.base_address = X86_MSI_BASE_ADDRESS_LOW;
	msg->arch_addr_lo.dest_mode_logical = apic->dest_mode_logical;
	msg->arch_addr_lo.destid_0_7 = cfg->dest_apicid & 0xFF;

	msg->arch_data.delivery_mode = APIC_DELIVERY_MODE_FIXED;
	msg->arch_data.vector = cfg->vector;

	msg->address_hi = X86_MSI_BASE_ADDRESS_HIGH;
	/*
	 * Only the IOMMU itself can use the trick of putting destination
	 * APIC ID पूर्णांकo the high bits of the address. Anything अन्यथा would
	 * just be writing to memory अगर it tried that, and needs IR to
	 * address APICs which can't be addressed in the normal 32-bit
	 * address range at 0xFFExxxxx. That is typically just 8 bits, but
	 * some hypervisors allow the extended destination ID field in bits
	 * 5-11 to be used, giving support क्रम 15 bits of APIC IDs in total.
	 */
	अगर (dmar)
		msg->arch_addr_hi.destid_8_31 = cfg->dest_apicid >> 8;
	अन्यथा अगर (virt_ext_dest_id && cfg->dest_apicid < 0x8000)
		msg->arch_addr_lo.virt_destid_8_14 = cfg->dest_apicid >> 8;
	अन्यथा
		WARN_ON_ONCE(cfg->dest_apicid > 0xFF);
पूर्ण

u32 x86_msi_msg_get_destid(काष्ठा msi_msg *msg, bool extid)
अणु
	u32 dest = msg->arch_addr_lo.destid_0_7;

	अगर (extid)
		dest |= msg->arch_addr_hi.destid_8_31 << 8;
	वापस dest;
पूर्ण
EXPORT_SYMBOL_GPL(x86_msi_msg_get_destid);

/*
 * Override the generic EOI implementation with an optimized version.
 * Only called during early boot when only one CPU is active and with
 * पूर्णांकerrupts disabled, so we know this करोes not race with actual APIC driver
 * use.
 */
व्योम __init apic_set_eoi_ग_लिखो(व्योम (*eoi_ग_लिखो)(u32 reg, u32 v))
अणु
	काष्ठा apic **drv;

	क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
		/* Should happen once क्रम each apic */
		WARN_ON((*drv)->eoi_ग_लिखो == eoi_ग_लिखो);
		(*drv)->native_eoi_ग_लिखो = (*drv)->eoi_ग_लिखो;
		(*drv)->eoi_ग_लिखो = eoi_ग_लिखो;
	पूर्ण
पूर्ण

अटल व्योम __init apic_bsp_up_setup(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	apic_ग_लिखो(APIC_ID, apic->set_apic_id(boot_cpu_physical_apicid));
#अन्यथा
	/*
	 * Hack: In हाल of kdump, after a crash, kernel might be booting
	 * on a cpu with non-zero lapic id. But boot_cpu_physical_apicid
	 * might be zero अगर पढ़ो from MP tables. Get it from LAPIC.
	 */
# अगरdef CONFIG_CRASH_DUMP
	boot_cpu_physical_apicid = पढ़ो_apic_id();
# endअगर
#पूर्ण_अगर
	physid_set_mask_of_physid(boot_cpu_physical_apicid, &phys_cpu_present_map);
पूर्ण

/**
 * apic_bsp_setup - Setup function क्रम local apic and io-apic
 * @upmode:		Force UP mode (क्रम APIC_init_uniprocessor)
 */
अटल व्योम __init apic_bsp_setup(bool upmode)
अणु
	connect_bsp_APIC();
	अगर (upmode)
		apic_bsp_up_setup();
	setup_local_APIC();

	enable_IO_APIC();
	end_local_APIC_setup();
	irq_remap_enable_fault_handling();
	setup_IO_APIC();
	lapic_update_legacy_vectors();
पूर्ण

#अगर_घोषित CONFIG_UP_LATE_INIT
व्योम __init up_late_init(व्योम)
अणु
	अगर (apic_पूर्णांकr_mode == APIC_PIC)
		वापस;

	/* Setup local समयr */
	x86_init.समयrs.setup_percpu_घड़ीev();
पूर्ण
#पूर्ण_अगर

/*
 * Power management
 */
#अगर_घोषित CONFIG_PM

अटल काष्ठा अणु
	/*
	 * 'active' is true अगर the local APIC was enabled by us and
	 * not the BIOS; this signअगरies that we are also responsible
	 * क्रम disabling it beक्रमe entering apm/acpi suspend
	 */
	पूर्णांक active;
	/* r/w apic fields */
	अचिन्हित पूर्णांक apic_id;
	अचिन्हित पूर्णांक apic_taskpri;
	अचिन्हित पूर्णांक apic_ldr;
	अचिन्हित पूर्णांक apic_dfr;
	अचिन्हित पूर्णांक apic_spiv;
	अचिन्हित पूर्णांक apic_lvtt;
	अचिन्हित पूर्णांक apic_lvtpc;
	अचिन्हित पूर्णांक apic_lvt0;
	अचिन्हित पूर्णांक apic_lvt1;
	अचिन्हित पूर्णांक apic_lvterr;
	अचिन्हित पूर्णांक apic_पंचांगict;
	अचिन्हित पूर्णांक apic_tdcr;
	अचिन्हित पूर्णांक apic_thmr;
	अचिन्हित पूर्णांक apic_cmci;
पूर्ण apic_pm_state;

अटल पूर्णांक lapic_suspend(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक maxlvt;

	अगर (!apic_pm_state.active)
		वापस 0;

	maxlvt = lapic_get_maxlvt();

	apic_pm_state.apic_id = apic_पढ़ो(APIC_ID);
	apic_pm_state.apic_taskpri = apic_पढ़ो(APIC_TASKPRI);
	apic_pm_state.apic_ldr = apic_पढ़ो(APIC_LDR);
	apic_pm_state.apic_dfr = apic_पढ़ो(APIC_DFR);
	apic_pm_state.apic_spiv = apic_पढ़ो(APIC_SPIV);
	apic_pm_state.apic_lvtt = apic_पढ़ो(APIC_LVTT);
	अगर (maxlvt >= 4)
		apic_pm_state.apic_lvtpc = apic_पढ़ो(APIC_LVTPC);
	apic_pm_state.apic_lvt0 = apic_पढ़ो(APIC_LVT0);
	apic_pm_state.apic_lvt1 = apic_पढ़ो(APIC_LVT1);
	apic_pm_state.apic_lvterr = apic_पढ़ो(APIC_LVTERR);
	apic_pm_state.apic_पंचांगict = apic_पढ़ो(APIC_TMICT);
	apic_pm_state.apic_tdcr = apic_पढ़ो(APIC_TDCR);
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	अगर (maxlvt >= 5)
		apic_pm_state.apic_thmr = apic_पढ़ो(APIC_LVTTHMR);
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_INTEL
	अगर (maxlvt >= 6)
		apic_pm_state.apic_cmci = apic_पढ़ो(APIC_LVTCMCI);
#पूर्ण_अगर

	local_irq_save(flags);

	/*
	 * Mask IOAPIC beक्रमe disabling the local APIC to prevent stale IRR
	 * entries on some implementations.
	 */
	mask_ioapic_entries();

	disable_local_APIC();

	irq_remapping_disable();

	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल व्योम lapic_resume(व्योम)
अणु
	अचिन्हित पूर्णांक l, h;
	अचिन्हित दीर्घ flags;
	पूर्णांक maxlvt;

	अगर (!apic_pm_state.active)
		वापस;

	local_irq_save(flags);

	/*
	 * IO-APIC and PIC have their own resume routines.
	 * We just mask them here to make sure the पूर्णांकerrupt
	 * subप्रणाली is completely quiet जबतक we enable x2apic
	 * and पूर्णांकerrupt-remapping.
	 */
	mask_ioapic_entries();
	legacy_pic->mask_all();

	अगर (x2apic_mode) अणु
		__x2apic_enable();
	पूर्ण अन्यथा अणु
		/*
		 * Make sure the APICBASE poपूर्णांकs to the right address
		 *
		 * FIXME! This will be wrong अगर we ever support suspend on
		 * SMP! We'll need to करो this as part of the CPU restore!
		 */
		अगर (boot_cpu_data.x86 >= 6) अणु
			rdmsr(MSR_IA32_APICBASE, l, h);
			l &= ~MSR_IA32_APICBASE_BASE;
			l |= MSR_IA32_APICBASE_ENABLE | mp_lapic_addr;
			wrmsr(MSR_IA32_APICBASE, l, h);
		पूर्ण
	पूर्ण

	maxlvt = lapic_get_maxlvt();
	apic_ग_लिखो(APIC_LVTERR, ERROR_APIC_VECTOR | APIC_LVT_MASKED);
	apic_ग_लिखो(APIC_ID, apic_pm_state.apic_id);
	apic_ग_लिखो(APIC_DFR, apic_pm_state.apic_dfr);
	apic_ग_लिखो(APIC_LDR, apic_pm_state.apic_ldr);
	apic_ग_लिखो(APIC_TASKPRI, apic_pm_state.apic_taskpri);
	apic_ग_लिखो(APIC_SPIV, apic_pm_state.apic_spiv);
	apic_ग_लिखो(APIC_LVT0, apic_pm_state.apic_lvt0);
	apic_ग_लिखो(APIC_LVT1, apic_pm_state.apic_lvt1);
#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
	अगर (maxlvt >= 5)
		apic_ग_लिखो(APIC_LVTTHMR, apic_pm_state.apic_thmr);
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_MCE_INTEL
	अगर (maxlvt >= 6)
		apic_ग_लिखो(APIC_LVTCMCI, apic_pm_state.apic_cmci);
#पूर्ण_अगर
	अगर (maxlvt >= 4)
		apic_ग_लिखो(APIC_LVTPC, apic_pm_state.apic_lvtpc);
	apic_ग_लिखो(APIC_LVTT, apic_pm_state.apic_lvtt);
	apic_ग_लिखो(APIC_TDCR, apic_pm_state.apic_tdcr);
	apic_ग_लिखो(APIC_TMICT, apic_pm_state.apic_पंचांगict);
	apic_ग_लिखो(APIC_ESR, 0);
	apic_पढ़ो(APIC_ESR);
	apic_ग_लिखो(APIC_LVTERR, apic_pm_state.apic_lvterr);
	apic_ग_लिखो(APIC_ESR, 0);
	apic_पढ़ो(APIC_ESR);

	irq_remapping_reenable(x2apic_mode);

	local_irq_restore(flags);
पूर्ण

/*
 * This device has no shutकरोwn method - fully functioning local APICs
 * are needed on every CPU up until machine_halt/restart/घातeroff.
 */

अटल काष्ठा syscore_ops lapic_syscore_ops = अणु
	.resume		= lapic_resume,
	.suspend	= lapic_suspend,
पूर्ण;

अटल व्योम apic_pm_activate(व्योम)
अणु
	apic_pm_state.active = 1;
पूर्ण

अटल पूर्णांक __init init_lapic_sysfs(व्योम)
अणु
	/* XXX: हटाओ suspend/resume procs अगर !apic_pm_state.active? */
	अगर (boot_cpu_has(X86_FEATURE_APIC))
		रेजिस्टर_syscore_ops(&lapic_syscore_ops);

	वापस 0;
पूर्ण

/* local apic needs to resume beक्रमe other devices access its रेजिस्टरs. */
core_initcall(init_lapic_sysfs);

#अन्यथा	/* CONFIG_PM */

अटल व्योम apic_pm_activate(व्योम) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

#अगर_घोषित CONFIG_X86_64

अटल पूर्णांक multi_checked;
अटल पूर्णांक multi;

अटल पूर्णांक set_multi(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (multi)
		वापस 0;
	pr_info("APIC: %s detected, Multi Chassis\n", d->ident);
	multi = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id multi_dmi_table[] = अणु
	अणु
		.callback = set_multi,
		.ident = "IBM System Summit2",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Summit2"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम dmi_check_multi(व्योम)
अणु
	अगर (multi_checked)
		वापस;

	dmi_check_प्रणाली(multi_dmi_table);
	multi_checked = 1;
पूर्ण

/*
 * apic_is_clustered_box() -- Check अगर we can expect good TSC
 *
 * Thus far, the major user of this is IBM's Summit2 series:
 * Clustered boxes may have unsynced TSC problems अगर they are
 * multi-chassis.
 * Use DMI to check them
 */
पूर्णांक apic_is_clustered_box(व्योम)
अणु
	dmi_check_multi();
	वापस multi;
पूर्ण
#पूर्ण_अगर

/*
 * APIC command line parameters
 */
अटल पूर्णांक __init setup_disableapic(अक्षर *arg)
अणु
	disable_apic = 1;
	setup_clear_cpu_cap(X86_FEATURE_APIC);
	वापस 0;
पूर्ण
early_param("disableapic", setup_disableapic);

/* same as disableapic, क्रम compatibility */
अटल पूर्णांक __init setup_nolapic(अक्षर *arg)
अणु
	वापस setup_disableapic(arg);
पूर्ण
early_param("nolapic", setup_nolapic);

अटल पूर्णांक __init parse_lapic_समयr_c2_ok(अक्षर *arg)
अणु
	local_apic_समयr_c2_ok = 1;
	वापस 0;
पूर्ण
early_param("lapic_timer_c2_ok", parse_lapic_समयr_c2_ok);

अटल पूर्णांक __init parse_disable_apic_समयr(अक्षर *arg)
अणु
	disable_apic_समयr = 1;
	वापस 0;
पूर्ण
early_param("noapictimer", parse_disable_apic_समयr);

अटल पूर्णांक __init parse_nolapic_समयr(अक्षर *arg)
अणु
	disable_apic_समयr = 1;
	वापस 0;
पूर्ण
early_param("nolapic_timer", parse_nolapic_समयr);

अटल पूर्णांक __init apic_set_verbosity(अक्षर *arg)
अणु
	अगर (!arg)  अणु
#अगर_घोषित CONFIG_X86_64
		skip_ioapic_setup = 0;
		वापस 0;
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद("debug", arg) == 0)
		apic_verbosity = APIC_DEBUG;
	अन्यथा अगर (म_भेद("verbose", arg) == 0)
		apic_verbosity = APIC_VERBOSE;
#अगर_घोषित CONFIG_X86_64
	अन्यथा अणु
		pr_warn("APIC Verbosity level %s not recognised"
			" use apic=verbose or apic=debug\n", arg);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
early_param("apic", apic_set_verbosity);

अटल पूर्णांक __init lapic_insert_resource(व्योम)
अणु
	अगर (!apic_phys)
		वापस -1;

	/* Put local APIC पूर्णांकo the resource map. */
	lapic_resource.start = apic_phys;
	lapic_resource.end = lapic_resource.start + PAGE_SIZE - 1;
	insert_resource(&iomem_resource, &lapic_resource);

	वापस 0;
पूर्ण

/*
 * need call insert after e820__reserve_resources()
 * that is using request_resource
 */
late_initcall(lapic_insert_resource);

अटल पूर्णांक __init apic_set_disabled_cpu_apicid(अक्षर *arg)
अणु
	अगर (!arg || !get_option(&arg, &disabled_cpu_apicid))
		वापस -EINVAL;

	वापस 0;
पूर्ण
early_param("disable_cpu_apicid", apic_set_disabled_cpu_apicid);

अटल पूर्णांक __init apic_set_extnmi(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (!म_भेदन("all", arg, 3))
		apic_extnmi = APIC_EXTNMI_ALL;
	अन्यथा अगर (!म_भेदन("none", arg, 4))
		apic_extnmi = APIC_EXTNMI_NONE;
	अन्यथा अगर (!म_भेदन("bsp", arg, 3))
		apic_extnmi = APIC_EXTNMI_BSP;
	अन्यथा अणु
		pr_warn("Unknown external NMI delivery mode `%s' ignored\n", arg);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
early_param("apic_extnmi", apic_set_extnmi);
