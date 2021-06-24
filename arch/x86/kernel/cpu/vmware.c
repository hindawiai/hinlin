<शैली गुरु>
/*
 * VMware Detection code.
 *
 * Copyright (C) 2008, VMware, Inc.
 * Author : Alok N Kataria <akataria@vmware.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 */

#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/cpu.h>
#समावेश <linux/reboot.h>
#समावेश <linux/अटल_call.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/vmware.h>
#समावेश <यंत्र/svm.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"vmware: " fmt

#घोषणा CPUID_VMWARE_INFO_LEAF               0x40000000
#घोषणा CPUID_VMWARE_FEATURES_LEAF           0x40000010
#घोषणा CPUID_VMWARE_FEATURES_ECX_VMMCALL    BIT(0)
#घोषणा CPUID_VMWARE_FEATURES_ECX_VMCALL     BIT(1)

#घोषणा VMWARE_HYPERVISOR_MAGIC	0x564D5868

#घोषणा VMWARE_CMD_GETVERSION    10
#घोषणा VMWARE_CMD_GETHZ         45
#घोषणा VMWARE_CMD_GETVCPU_INFO  68
#घोषणा VMWARE_CMD_LEGACY_X2APIC  3
#घोषणा VMWARE_CMD_VCPU_RESERVED 31
#घोषणा VMWARE_CMD_STEALCLOCK    91

#घोषणा STEALCLOCK_NOT_AVAILABLE (-1)
#घोषणा STEALCLOCK_DISABLED        0
#घोषणा STEALCLOCK_ENABLED         1

#घोषणा VMWARE_PORT(cmd, eax, ebx, ecx, edx)				\
	__यंत्र__("inl (%%dx), %%eax" :					\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWARE_HYPERVISOR_MAGIC),				\
		"c"(VMWARE_CMD_##cmd),					\
		"d"(VMWARE_HYPERVISOR_PORT), "b"(अच_पूर्णांक_उच्च) :		\
		"memory")

#घोषणा VMWARE_VMCALL(cmd, eax, ebx, ecx, edx)				\
	__यंत्र__("vmcall" :						\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWARE_HYPERVISOR_MAGIC),				\
		"c"(VMWARE_CMD_##cmd),					\
		"d"(0), "b"(अच_पूर्णांक_उच्च) :					\
		"memory")

#घोषणा VMWARE_VMMCALL(cmd, eax, ebx, ecx, edx)                         \
	__यंत्र__("vmmcall" :						\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWARE_HYPERVISOR_MAGIC),				\
		"c"(VMWARE_CMD_##cmd),					\
		"d"(0), "b"(अच_पूर्णांक_उच्च) :					\
		"memory")

#घोषणा VMWARE_CMD(cmd, eax, ebx, ecx, edx) करो अणु		\
	चयन (vmware_hypercall_mode) अणु			\
	हाल CPUID_VMWARE_FEATURES_ECX_VMCALL:			\
		VMWARE_VMCALL(cmd, eax, ebx, ecx, edx);		\
		अवरोध;						\
	हाल CPUID_VMWARE_FEATURES_ECX_VMMCALL:			\
		VMWARE_VMMCALL(cmd, eax, ebx, ecx, edx);	\
		अवरोध;						\
	शेष:						\
		VMWARE_PORT(cmd, eax, ebx, ecx, edx);		\
		अवरोध;						\
	पूर्ण							\
	पूर्ण जबतक (0)

काष्ठा vmware_steal_समय अणु
	जोड़ अणु
		uपूर्णांक64_t घड़ी;	/* stolen समय counter in units of vtsc */
		काष्ठा अणु
			/* only क्रम little-endian */
			uपूर्णांक32_t घड़ी_low;
			uपूर्णांक32_t घड़ी_high;
		पूर्ण;
	पूर्ण;
	uपूर्णांक64_t reserved[7];
पूर्ण;

अटल अचिन्हित दीर्घ vmware_tsc_khz __ro_after_init;
अटल u8 vmware_hypercall_mode     __ro_after_init;

अटल अंतरभूत पूर्णांक __vmware_platक्रमm(व्योम)
अणु
	uपूर्णांक32_t eax, ebx, ecx, edx;
	VMWARE_CMD(GETVERSION, eax, ebx, ecx, edx);
	वापस eax != (uपूर्णांक32_t)-1 && ebx == VMWARE_HYPERVISOR_MAGIC;
पूर्ण

अटल अचिन्हित दीर्घ vmware_get_tsc_khz(व्योम)
अणु
	वापस vmware_tsc_khz;
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT
अटल काष्ठा cyc2ns_data vmware_cyc2ns __ro_after_init;
अटल bool vmw_sched_घड़ी __initdata = true;
अटल DEFINE_PER_CPU_DECRYPTED(काष्ठा vmware_steal_समय, vmw_steal_समय) __aligned(64);
अटल bool has_steal_घड़ी;
अटल bool steal_acc __initdata = true; /* steal समय accounting */

अटल __init पूर्णांक setup_vmw_sched_घड़ी(अक्षर *s)
अणु
	vmw_sched_घड़ी = false;
	वापस 0;
पूर्ण
early_param("no-vmw-sched-clock", setup_vmw_sched_घड़ी);

अटल __init पूर्णांक parse_no_stealacc(अक्षर *arg)
अणु
	steal_acc = false;
	वापस 0;
पूर्ण
early_param("no-steal-acc", parse_no_stealacc);

अटल अचिन्हित दीर्घ दीर्घ notrace vmware_sched_घड़ी(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ ns;

	ns = mul_u64_u32_shr(rdtsc(), vmware_cyc2ns.cyc2ns_mul,
			     vmware_cyc2ns.cyc2ns_shअगरt);
	ns -= vmware_cyc2ns.cyc2ns_offset;
	वापस ns;
पूर्ण

अटल व्योम __init vmware_cyc2ns_setup(व्योम)
अणु
	काष्ठा cyc2ns_data *d = &vmware_cyc2ns;
	अचिन्हित दीर्घ दीर्घ tsc_now = rdtsc();

	घड़ीs_calc_mult_shअगरt(&d->cyc2ns_mul, &d->cyc2ns_shअगरt,
			       vmware_tsc_khz, NSEC_PER_MSEC, 0);
	d->cyc2ns_offset = mul_u64_u32_shr(tsc_now, d->cyc2ns_mul,
					   d->cyc2ns_shअगरt);

	pr_info("using clock offset of %llu ns\n", d->cyc2ns_offset);
पूर्ण

अटल पूर्णांक vmware_cmd_stealघड़ी(uपूर्णांक32_t arg1, uपूर्णांक32_t arg2)
अणु
	uपूर्णांक32_t result, info;

	यंत्र अस्थिर (VMWARE_HYPERCALL :
		"=a"(result),
		"=c"(info) :
		"a"(VMWARE_HYPERVISOR_MAGIC),
		"b"(0),
		"c"(VMWARE_CMD_STEALCLOCK),
		"d"(0),
		"S"(arg1),
		"D"(arg2) :
		"memory");
	वापस result;
पूर्ण

अटल bool stealघड़ी_enable(phys_addr_t pa)
अणु
	वापस vmware_cmd_stealघड़ी(upper_32_bits(pa),
				     lower_32_bits(pa)) == STEALCLOCK_ENABLED;
पूर्ण

अटल पूर्णांक __stealघड़ी_disable(व्योम)
अणु
	वापस vmware_cmd_stealघड़ी(0, 1);
पूर्ण

अटल व्योम stealघड़ी_disable(व्योम)
अणु
	__stealघड़ी_disable();
पूर्ण

अटल bool vmware_is_stealघड़ी_available(व्योम)
अणु
	वापस __stealघड़ी_disable() != STEALCLOCK_NOT_AVAILABLE;
पूर्ण

/**
 * vmware_steal_घड़ी() - पढ़ो the per-cpu steal घड़ी
 * @cpu:            the cpu number whose steal घड़ी we want to पढ़ो
 *
 * The function पढ़ोs the steal घड़ी अगर we are on a 64-bit प्रणाली, otherwise
 * पढ़ोs it in parts, checking that the high part didn't change in the
 * meanसमय.
 *
 * Return:
 *      The steal घड़ी पढ़ोing in ns.
 */
अटल uपूर्णांक64_t vmware_steal_घड़ी(पूर्णांक cpu)
अणु
	काष्ठा vmware_steal_समय *steal = &per_cpu(vmw_steal_समय, cpu);
	uपूर्णांक64_t घड़ी;

	अगर (IS_ENABLED(CONFIG_64BIT))
		घड़ी = READ_ONCE(steal->घड़ी);
	अन्यथा अणु
		uपूर्णांक32_t initial_high, low, high;

		करो अणु
			initial_high = READ_ONCE(steal->घड़ी_high);
			/* Do not reorder initial_high and high पढ़ोings */
			virt_rmb();
			low = READ_ONCE(steal->घड़ी_low);
			/* Keep low पढ़ोing in between */
			virt_rmb();
			high = READ_ONCE(steal->घड़ी_high);
		पूर्ण जबतक (initial_high != high);

		घड़ी = ((uपूर्णांक64_t)high << 32) | low;
	पूर्ण

	वापस mul_u64_u32_shr(घड़ी, vmware_cyc2ns.cyc2ns_mul,
			     vmware_cyc2ns.cyc2ns_shअगरt);
पूर्ण

अटल व्योम vmware_रेजिस्टर_steal_समय(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा vmware_steal_समय *st = &per_cpu(vmw_steal_समय, cpu);

	अगर (!has_steal_घड़ी)
		वापस;

	अगर (!stealघड़ी_enable(slow_virt_to_phys(st))) अणु
		has_steal_घड़ी = false;
		वापस;
	पूर्ण

	pr_info("vmware-stealtime: cpu %d, pa %llx\n",
		cpu, (अचिन्हित दीर्घ दीर्घ) slow_virt_to_phys(st));
पूर्ण

अटल व्योम vmware_disable_steal_समय(व्योम)
अणु
	अगर (!has_steal_घड़ी)
		वापस;

	stealघड़ी_disable();
पूर्ण

अटल व्योम vmware_guest_cpu_init(व्योम)
अणु
	अगर (has_steal_घड़ी)
		vmware_रेजिस्टर_steal_समय();
पूर्ण

अटल व्योम vmware_pv_guest_cpu_reboot(व्योम *unused)
अणु
	vmware_disable_steal_समय();
पूर्ण

अटल पूर्णांक vmware_pv_reboot_notअगरy(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ code, व्योम *unused)
अणु
	अगर (code == SYS_RESTART)
		on_each_cpu(vmware_pv_guest_cpu_reboot, शून्य, 1);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vmware_pv_reboot_nb = अणु
	.notअगरier_call = vmware_pv_reboot_notअगरy,
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल व्योम __init vmware_smp_prepare_boot_cpu(व्योम)
अणु
	vmware_guest_cpu_init();
	native_smp_prepare_boot_cpu();
पूर्ण

अटल पूर्णांक vmware_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	local_irq_disable();
	vmware_guest_cpu_init();
	local_irq_enable();
	वापस 0;
पूर्ण

अटल पूर्णांक vmware_cpu_करोwn_prepare(अचिन्हित पूर्णांक cpu)
अणु
	local_irq_disable();
	vmware_disable_steal_समय();
	local_irq_enable();
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल __init पूर्णांक activate_jump_labels(व्योम)
अणु
	अगर (has_steal_घड़ी) अणु
		अटल_key_slow_inc(&paravirt_steal_enabled);
		अगर (steal_acc)
			अटल_key_slow_inc(&paravirt_steal_rq_enabled);
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(activate_jump_labels);

अटल व्योम __init vmware_paravirt_ops_setup(व्योम)
अणु
	pv_info.name = "VMware hypervisor";
	pv_ops.cpu.io_delay = paravirt_nop;

	अगर (vmware_tsc_khz == 0)
		वापस;

	vmware_cyc2ns_setup();

	अगर (vmw_sched_घड़ी)
		paravirt_set_sched_घड़ी(vmware_sched_घड़ी);

	अगर (vmware_is_stealघड़ी_available()) अणु
		has_steal_घड़ी = true;
		अटल_call_update(pv_steal_घड़ी, vmware_steal_घड़ी);

		/* We use reboot notअगरier only to disable steal घड़ी */
		रेजिस्टर_reboot_notअगरier(&vmware_pv_reboot_nb);

#अगर_घोषित CONFIG_SMP
		smp_ops.smp_prepare_boot_cpu =
			vmware_smp_prepare_boot_cpu;
		अगर (cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					      "x86/vmware:online",
					      vmware_cpu_online,
					      vmware_cpu_करोwn_prepare) < 0)
			pr_err("vmware_guest: Failed to install cpu hotplug callbacks\n");
#अन्यथा
		vmware_guest_cpu_init();
#पूर्ण_अगर
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा vmware_paravirt_ops_setup() करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * VMware hypervisor takes care of exporting a reliable TSC to the guest.
 * Still, due to timing dअगरference when running on भव cpus, the TSC can
 * be marked as unstable in some हालs. For example, the TSC sync check at
 * bootup can fail due to a marginal offset between vcpus' TSCs (though the
 * TSCs करो not drअगरt from each other).  Also, the ACPI PM समयr घड़ीsource
 * is not suitable as a watchकरोg when running on a hypervisor because the
 * kernel may miss a wrap of the counter अगर the vcpu is descheduled क्रम a
 * दीर्घ समय. To skip these checks at runसमय we set these capability bits,
 * so that the kernel could just trust the hypervisor with providing a
 * reliable भव TSC that is suitable क्रम समयkeeping.
 */
अटल व्योम __init vmware_set_capabilities(व्योम)
अणु
	setup_क्रमce_cpu_cap(X86_FEATURE_CONSTANT_TSC);
	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_RELIABLE);
	अगर (vmware_tsc_khz)
		setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);
	अगर (vmware_hypercall_mode == CPUID_VMWARE_FEATURES_ECX_VMCALL)
		setup_क्रमce_cpu_cap(X86_FEATURE_VMCALL);
	अन्यथा अगर (vmware_hypercall_mode == CPUID_VMWARE_FEATURES_ECX_VMMCALL)
		setup_क्रमce_cpu_cap(X86_FEATURE_VMW_VMMCALL);
पूर्ण

अटल व्योम __init vmware_platक्रमm_setup(व्योम)
अणु
	uपूर्णांक32_t eax, ebx, ecx, edx;
	uपूर्णांक64_t lpj, tsc_khz;

	VMWARE_CMD(GETHZ, eax, ebx, ecx, edx);

	अगर (ebx != अच_पूर्णांक_उच्च) अणु
		lpj = tsc_khz = eax | (((uपूर्णांक64_t)ebx) << 32);
		करो_भाग(tsc_khz, 1000);
		WARN_ON(tsc_khz >> 32);
		pr_info("TSC freq read from hypervisor : %lu.%03lu MHz\n",
			(अचिन्हित दीर्घ) tsc_khz / 1000,
			(अचिन्हित दीर्घ) tsc_khz % 1000);

		अगर (!preset_lpj) अणु
			करो_भाग(lpj, HZ);
			preset_lpj = lpj;
		पूर्ण

		vmware_tsc_khz = tsc_khz;
		x86_platक्रमm.calibrate_tsc = vmware_get_tsc_khz;
		x86_platक्रमm.calibrate_cpu = vmware_get_tsc_khz;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
		/* Skip lapic calibration since we know the bus frequency. */
		lapic_समयr_period = ecx / HZ;
		pr_info("Host bus clock speed read from hypervisor : %u Hz\n",
			ecx);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_warn("Failed to get TSC freq from the hypervisor\n");
	पूर्ण

	vmware_paravirt_ops_setup();

#अगर_घोषित CONFIG_X86_IO_APIC
	no_समयr_check = 1;
#पूर्ण_अगर

	vmware_set_capabilities();
पूर्ण

अटल u8 __init vmware_select_hypercall(व्योम)
अणु
	पूर्णांक eax, ebx, ecx, edx;

	cpuid(CPUID_VMWARE_FEATURES_LEAF, &eax, &ebx, &ecx, &edx);
	वापस (ecx & (CPUID_VMWARE_FEATURES_ECX_VMMCALL |
		       CPUID_VMWARE_FEATURES_ECX_VMCALL));
पूर्ण

/*
 * While checking the dmi string inक्रमmation, just checking the product
 * serial key should be enough, as this will always have a VMware
 * specअगरic string when running under VMware hypervisor.
 * If !boot_cpu_has(X86_FEATURE_HYPERVISOR), vmware_hypercall_mode
 * पूर्णांकentionally शेषs to 0.
 */
अटल uपूर्णांक32_t __init vmware_platक्रमm(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		अचिन्हित पूर्णांक eax;
		अचिन्हित पूर्णांक hyper_venकरोr_id[3];

		cpuid(CPUID_VMWARE_INFO_LEAF, &eax, &hyper_venकरोr_id[0],
		      &hyper_venकरोr_id[1], &hyper_venकरोr_id[2]);
		अगर (!स_भेद(hyper_venकरोr_id, "VMwareVMware", 12)) अणु
			अगर (eax >= CPUID_VMWARE_FEATURES_LEAF)
				vmware_hypercall_mode =
					vmware_select_hypercall();

			pr_info("hypercall mode: 0x%02x\n",
				(अचिन्हित पूर्णांक) vmware_hypercall_mode);

			वापस CPUID_VMWARE_INFO_LEAF;
		पूर्ण
	पूर्ण अन्यथा अगर (dmi_available && dmi_name_in_serial("VMware") &&
		   __vmware_platक्रमm())
		वापस 1;

	वापस 0;
पूर्ण

/* Checks अगर hypervisor supports x2apic without VT-D पूर्णांकerrupt remapping. */
अटल bool __init vmware_legacy_x2apic_available(व्योम)
अणु
	uपूर्णांक32_t eax, ebx, ecx, edx;
	VMWARE_CMD(GETVCPU_INFO, eax, ebx, ecx, edx);
	वापस (eax & (1 << VMWARE_CMD_VCPU_RESERVED)) == 0 &&
	       (eax & (1 << VMWARE_CMD_LEGACY_X2APIC)) != 0;
पूर्ण

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
अटल व्योम vmware_sev_es_hcall_prepare(काष्ठा ghcb *ghcb,
					काष्ठा pt_regs *regs)
अणु
	/* Copy VMWARE specअगरic Hypercall parameters to the GHCB */
	ghcb_set_rip(ghcb, regs->ip);
	ghcb_set_rbx(ghcb, regs->bx);
	ghcb_set_rcx(ghcb, regs->cx);
	ghcb_set_rdx(ghcb, regs->dx);
	ghcb_set_rsi(ghcb, regs->si);
	ghcb_set_rdi(ghcb, regs->di);
	ghcb_set_rbp(ghcb, regs->bp);
पूर्ण

अटल bool vmware_sev_es_hcall_finish(काष्ठा ghcb *ghcb, काष्ठा pt_regs *regs)
अणु
	अगर (!(ghcb_rbx_is_valid(ghcb) &&
	      ghcb_rcx_is_valid(ghcb) &&
	      ghcb_rdx_is_valid(ghcb) &&
	      ghcb_rsi_is_valid(ghcb) &&
	      ghcb_rdi_is_valid(ghcb) &&
	      ghcb_rbp_is_valid(ghcb)))
		वापस false;

	regs->bx = ghcb_get_rbx(ghcb);
	regs->cx = ghcb_get_rcx(ghcb);
	regs->dx = ghcb_get_rdx(ghcb);
	regs->si = ghcb_get_rsi(ghcb);
	regs->di = ghcb_get_rdi(ghcb);
	regs->bp = ghcb_get_rbp(ghcb);

	वापस true;
पूर्ण
#पूर्ण_अगर

स्थिर __initस्थिर काष्ठा hypervisor_x86 x86_hyper_vmware = अणु
	.name				= "VMware",
	.detect				= vmware_platक्रमm,
	.type				= X86_HYPER_VMWARE,
	.init.init_platक्रमm		= vmware_platक्रमm_setup,
	.init.x2apic_available		= vmware_legacy_x2apic_available,
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	.runसमय.sev_es_hcall_prepare	= vmware_sev_es_hcall_prepare,
	.runसमय.sev_es_hcall_finish	= vmware_sev_es_hcall_finish,
#पूर्ण_अगर
पूर्ण;
