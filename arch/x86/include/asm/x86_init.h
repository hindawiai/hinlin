<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PLATFORM_H
#घोषणा _ASM_X86_PLATFORM_H

#समावेश <यंत्र/bootparam.h>

काष्ठा ghcb;
काष्ठा mpc_bus;
काष्ठा mpc_cpu;
काष्ठा pt_regs;
काष्ठा mpc_table;
काष्ठा cpuinfo_x86;
काष्ठा irq_करोमुख्य;

/**
 * काष्ठा x86_init_mpparse - platक्रमm specअगरic mpparse ops
 * @setup_ioapic_ids:		platक्रमm specअगरic ioapic id override
 * @find_smp_config:		find the smp configuration
 * @get_smp_config:		get the smp configuration
 */
काष्ठा x86_init_mpparse अणु
	व्योम (*setup_ioapic_ids)(व्योम);
	व्योम (*find_smp_config)(व्योम);
	व्योम (*get_smp_config)(अचिन्हित पूर्णांक early);
पूर्ण;

/**
 * काष्ठा x86_init_resources - platक्रमm specअगरic resource related ops
 * @probe_roms:			probe BIOS roms
 * @reserve_resources:		reserve the standard resources क्रम the
 *				platक्रमm
 * @memory_setup:		platक्रमm specअगरic memory setup
 *
 */
काष्ठा x86_init_resources अणु
	व्योम (*probe_roms)(व्योम);
	व्योम (*reserve_resources)(व्योम);
	अक्षर *(*memory_setup)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_irqs - platक्रमm specअगरic पूर्णांकerrupt setup
 * @pre_vector_init:		init code to run beक्रमe पूर्णांकerrupt vectors
 *				are set up.
 * @पूर्णांकr_init:			पूर्णांकerrupt init code
 * @पूर्णांकr_mode_select:		पूर्णांकerrupt delivery mode selection
 * @पूर्णांकr_mode_init:		पूर्णांकerrupt delivery mode setup
 * @create_pci_msi_करोमुख्य:	Create the PCI/MSI पूर्णांकerrupt करोमुख्य
 */
काष्ठा x86_init_irqs अणु
	व्योम (*pre_vector_init)(व्योम);
	व्योम (*पूर्णांकr_init)(व्योम);
	व्योम (*पूर्णांकr_mode_select)(व्योम);
	व्योम (*पूर्णांकr_mode_init)(व्योम);
	काष्ठा irq_करोमुख्य *(*create_pci_msi_करोमुख्य)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_oem - oem platक्रमm specअगरic customizing functions
 * @arch_setup:			platक्रमm specअगरic architecture setup
 * @banner:			prपूर्णांक a platक्रमm specअगरic banner
 */
काष्ठा x86_init_oem अणु
	व्योम (*arch_setup)(व्योम);
	व्योम (*banner)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_paging - platक्रमm specअगरic paging functions
 * @pagetable_init:	platक्रमm specअगरic paging initialization call to setup
 *			the kernel pagetables and prepare accessors functions.
 *			Callback must call paging_init(). Called once after the
 *			direct mapping क्रम phys memory is available.
 */
काष्ठा x86_init_paging अणु
	व्योम (*pagetable_init)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_समयrs - platक्रमm specअगरic समयr setup
 * @setup_perpcu_घड़ीev:	set up the per cpu घड़ी event device क्रम the
 *				boot cpu
 * @समयr_init:			initialize the platक्रमm समयr (शेष PIT/HPET)
 * @wallघड़ी_init:		init the wallघड़ी device
 */
काष्ठा x86_init_समयrs अणु
	व्योम (*setup_percpu_घड़ीev)(व्योम);
	व्योम (*समयr_init)(व्योम);
	व्योम (*wallघड़ी_init)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_iommu - platक्रमm specअगरic iommu setup
 * @iommu_init:			platक्रमm specअगरic iommu setup
 */
काष्ठा x86_init_iommu अणु
	पूर्णांक (*iommu_init)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_pci - platक्रमm specअगरic pci init functions
 * @arch_init:			platक्रमm specअगरic pci arch init call
 * @init:			platक्रमm specअगरic pci subप्रणाली init
 * @init_irq:			platक्रमm specअगरic pci irq init
 * @fixup_irqs:			platक्रमm specअगरic pci irq fixup
 */
काष्ठा x86_init_pci अणु
	पूर्णांक (*arch_init)(व्योम);
	पूर्णांक (*init)(व्योम);
	व्योम (*init_irq)(व्योम);
	व्योम (*fixup_irqs)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_hyper_init - x86 hypervisor init functions
 * @init_platक्रमm:		platक्रमm setup
 * @guest_late_init:		guest late init
 * @x2apic_available:		X2APIC detection
 * @msi_ext_dest_id:		MSI supports 15-bit APIC IDs
 * @init_mem_mapping:		setup early mappings during init_mem_mapping()
 * @init_after_booपंचांगem:		guest init after boot allocator is finished
 */
काष्ठा x86_hyper_init अणु
	व्योम (*init_platक्रमm)(व्योम);
	व्योम (*guest_late_init)(व्योम);
	bool (*x2apic_available)(व्योम);
	bool (*msi_ext_dest_id)(व्योम);
	व्योम (*init_mem_mapping)(व्योम);
	व्योम (*init_after_booपंचांगem)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_acpi - x86 ACPI init functions
 * @set_root_poitner:		set RSDP address
 * @get_root_poपूर्णांकer:		get RSDP address
 * @reduced_hw_early_init:	hardware reduced platक्रमm early init
 */
काष्ठा x86_init_acpi अणु
	व्योम (*set_root_poपूर्णांकer)(u64 addr);
	u64 (*get_root_poपूर्णांकer)(व्योम);
	व्योम (*reduced_hw_early_init)(व्योम);
पूर्ण;

/**
 * काष्ठा x86_init_ops - functions क्रम platक्रमm specअगरic setup
 *
 */
काष्ठा x86_init_ops अणु
	काष्ठा x86_init_resources	resources;
	काष्ठा x86_init_mpparse		mpparse;
	काष्ठा x86_init_irqs		irqs;
	काष्ठा x86_init_oem		oem;
	काष्ठा x86_init_paging		paging;
	काष्ठा x86_init_समयrs		समयrs;
	काष्ठा x86_init_iommu		iommu;
	काष्ठा x86_init_pci		pci;
	काष्ठा x86_hyper_init		hyper;
	काष्ठा x86_init_acpi		acpi;
पूर्ण;

/**
 * काष्ठा x86_cpuinit_ops - platक्रमm specअगरic cpu hotplug setups
 * @setup_percpu_घड़ीev:	set up the per cpu घड़ी event device
 * @early_percpu_घड़ी_init:	early init of the per cpu घड़ी event device
 */
काष्ठा x86_cpuinit_ops अणु
	व्योम (*setup_percpu_घड़ीev)(व्योम);
	व्योम (*early_percpu_घड़ी_init)(व्योम);
	व्योम (*fixup_cpu_id)(काष्ठा cpuinfo_x86 *c, पूर्णांक node);
पूर्ण;

काष्ठा बारpec64;

/**
 * काष्ठा x86_legacy_devices - legacy x86 devices
 *
 * @pnpbios: this platक्रमm can have a PNPBIOS. If this is disabled the platक्रमm
 * 	is known to never have a PNPBIOS.
 *
 * These are devices known to require LPC or ISA bus. The definition of legacy
 * devices adheres to the ACPI 5.2.9.3 IA-PC Boot Architecture flag
 * ACPI_FADT_LEGACY_DEVICES. These devices consist of user visible devices on
 * the LPC or ISA bus. User visible devices are devices that have end-user
 * accessible connectors (क्रम example, LPT parallel port). Legacy devices on
 * the LPC bus consist क्रम example of serial and parallel ports, PS/2 keyboard
 * / mouse, and the floppy disk controller. A प्रणाली that lacks all known
 * legacy devices can assume all devices can be detected exclusively via
 * standard device क्रमागतeration mechanisms including the ACPI namespace.
 *
 * A प्रणाली which has करोes not have ACPI_FADT_LEGACY_DEVICES enabled must not
 * have any of the legacy devices क्रमागतerated below present.
 */
काष्ठा x86_legacy_devices अणु
	पूर्णांक pnpbios;
पूर्ण;

/**
 * क्रमागत x86_legacy_i8042_state - i8042 keyboard controller state
 * @X86_LEGACY_I8042_PLATFORM_ABSENT: the controller is always असलent on
 *	given platक्रमm/subarch.
 * @X86_LEGACY_I8042_FIRMWARE_ABSENT: firmware reports that the controller
 *	is असलent.
 * @X86_LEGACY_i8042_EXPECTED_PRESENT: the controller is likely to be
 *	present, the i8042 driver should probe क्रम controller existence.
 */
क्रमागत x86_legacy_i8042_state अणु
	X86_LEGACY_I8042_PLATFORM_ABSENT,
	X86_LEGACY_I8042_FIRMWARE_ABSENT,
	X86_LEGACY_I8042_EXPECTED_PRESENT,
पूर्ण;

/**
 * काष्ठा x86_legacy_features - legacy x86 features
 *
 * @i8042: indicated अगर we expect the device to have i8042 controller
 *	present.
 * @rtc: this device has a CMOS real-समय घड़ी present
 * @reserve_bios_regions: boot code will search क्रम the EBDA address and the
 * 	start of the 640k - 1M BIOS region.  If false, the platक्रमm must
 * 	ensure that its memory map correctly reserves sub-1MB regions as needed.
 * @devices: legacy x86 devices, refer to काष्ठा x86_legacy_devices
 * 	करोcumentation क्रम further details.
 */
काष्ठा x86_legacy_features अणु
	क्रमागत x86_legacy_i8042_state i8042;
	पूर्णांक rtc;
	पूर्णांक warm_reset;
	पूर्णांक no_vga;
	पूर्णांक reserve_bios_regions;
	काष्ठा x86_legacy_devices devices;
पूर्ण;

/**
 * काष्ठा x86_hyper_runसमय - x86 hypervisor specअगरic runसमय callbacks
 *
 * @pin_vcpu:			pin current vcpu to specअगरied physical
 *				cpu (run rarely)
 * @sev_es_hcall_prepare:	Load additional hypervisor-specअगरic
 *				state पूर्णांकo the GHCB when करोing a VMMCALL under
 *				SEV-ES. Called from the #VC exception handler.
 * @sev_es_hcall_finish:	Copies state from the GHCB back पूर्णांकo the
 *				processor (or pt_regs). Also runs checks on the
 *				state वापसed from the hypervisor after a
 *				VMMCALL under SEV-ES.  Needs to वापस 'false'
 *				अगर the checks fail.  Called from the #VC
 *				exception handler.
 */
काष्ठा x86_hyper_runसमय अणु
	व्योम (*pin_vcpu)(पूर्णांक cpu);
	व्योम (*sev_es_hcall_prepare)(काष्ठा ghcb *ghcb, काष्ठा pt_regs *regs);
	bool (*sev_es_hcall_finish)(काष्ठा ghcb *ghcb, काष्ठा pt_regs *regs);
पूर्ण;

/**
 * काष्ठा x86_platक्रमm_ops - platक्रमm specअगरic runसमय functions
 * @calibrate_cpu:		calibrate CPU
 * @calibrate_tsc:		calibrate TSC, अगर dअगरferent from CPU
 * @get_wallघड़ी:		get समय from HW घड़ी like RTC etc.
 * @set_wallघड़ी:		set समय back to HW घड़ी
 * @is_untracked_pat_range	exclude from PAT logic
 * @nmi_init			enable NMI on cpus
 * @save_sched_घड़ी_state:	save state क्रम sched_घड़ी() on suspend
 * @restore_sched_घड़ी_state:	restore state क्रम sched_घड़ी() on resume
 * @apic_post_init:		adjust apic अगर needed
 * @legacy:			legacy features
 * @set_legacy_features:	override legacy features. Use of this callback
 * 				is highly discouraged. You should only need
 * 				this अगर your hardware platक्रमm requires further
 * 				custom fine tuning far beyond what may be
 * 				possible in x86_early_init_platक्रमm_quirks() by
 * 				only using the current x86_hardware_subarch
 * 				semantics.
 * @hyper:			x86 hypervisor specअगरic runसमय callbacks
 */
काष्ठा x86_platक्रमm_ops अणु
	अचिन्हित दीर्घ (*calibrate_cpu)(व्योम);
	अचिन्हित दीर्घ (*calibrate_tsc)(व्योम);
	व्योम (*get_wallघड़ी)(काष्ठा बारpec64 *ts);
	पूर्णांक (*set_wallघड़ी)(स्थिर काष्ठा बारpec64 *ts);
	व्योम (*iommu_shutकरोwn)(व्योम);
	bool (*is_untracked_pat_range)(u64 start, u64 end);
	व्योम (*nmi_init)(व्योम);
	अचिन्हित अक्षर (*get_nmi_reason)(व्योम);
	व्योम (*save_sched_घड़ी_state)(व्योम);
	व्योम (*restore_sched_घड़ी_state)(व्योम);
	व्योम (*apic_post_init)(व्योम);
	काष्ठा x86_legacy_features legacy;
	व्योम (*set_legacy_features)(व्योम);
	काष्ठा x86_hyper_runसमय hyper;
पूर्ण;

काष्ठा pci_dev;

काष्ठा x86_msi_ops अणु
	व्योम (*restore_msi_irqs)(काष्ठा pci_dev *dev);
पूर्ण;

काष्ठा x86_apic_ops अणु
	अचिन्हित पूर्णांक	(*io_apic_पढ़ो)   (अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक reg);
	व्योम		(*restore)(व्योम);
पूर्ण;

बाह्य काष्ठा x86_init_ops x86_init;
बाह्य काष्ठा x86_cpuinit_ops x86_cpuinit;
बाह्य काष्ठा x86_platक्रमm_ops x86_platक्रमm;
बाह्य काष्ठा x86_msi_ops x86_msi;
बाह्य काष्ठा x86_apic_ops x86_apic_ops;

बाह्य व्योम x86_early_init_platक्रमm_quirks(व्योम);
बाह्य व्योम x86_init_noop(व्योम);
बाह्य व्योम x86_init_uपूर्णांक_noop(अचिन्हित पूर्णांक unused);
बाह्य bool bool_x86_init_noop(व्योम);
बाह्य व्योम x86_op_पूर्णांक_noop(पूर्णांक cpu);
बाह्य bool x86_pnpbios_disabled(व्योम);

#पूर्ण_अगर
