<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Jailhouse paravirt_ops implementation
 *
 * Copyright (c) Siemens AG, 2015-2017
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 */

#समावेश <linux/acpi_pmपंचांगr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/serial_8250.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/jailhouse_para.h>

अटल काष्ठा jailhouse_setup_data setup_data;
#घोषणा SETUP_DATA_V1_LEN	(माप(setup_data.hdr) + माप(setup_data.v1))
#घोषणा SETUP_DATA_V2_LEN	(SETUP_DATA_V1_LEN + माप(setup_data.v2))

अटल अचिन्हित पूर्णांक precalibrated_tsc_khz;

अटल व्योम jailhouse_setup_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा mpc_पूर्णांकsrc mp_irq = अणु
		.type		= MP_INTSRC,
		.irqtype	= mp_INT,
		.irqflag	= MP_IRQPOL_ACTIVE_HIGH | MP_IRQTRIG_EDGE,
		.srcbusirq	= irq,
		.dstirq		= irq,
	पूर्ण;
	mp_save_irq(&mp_irq);
पूर्ण

अटल uपूर्णांक32_t jailhouse_cpuid_base(व्योम)
अणु
	अगर (boot_cpu_data.cpuid_level < 0 ||
	    !boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस 0;

	वापस hypervisor_cpuid_base("Jailhouse\0\0\0", 0);
पूर्ण

अटल uपूर्णांक32_t __init jailhouse_detect(व्योम)
अणु
	वापस jailhouse_cpuid_base();
पूर्ण

अटल व्योम jailhouse_get_wallघड़ी(काष्ठा बारpec64 *now)
अणु
	स_रखो(now, 0, माप(*now));
पूर्ण

अटल व्योम __init jailhouse_समयr_init(व्योम)
अणु
	lapic_समयr_period = setup_data.v1.apic_khz * (1000 / HZ);
पूर्ण

अटल अचिन्हित दीर्घ jailhouse_get_tsc(व्योम)
अणु
	वापस precalibrated_tsc_khz;
पूर्ण

अटल व्योम __init jailhouse_x2apic_init(व्योम)
अणु
#अगर_घोषित CONFIG_X86_X2APIC
	अगर (!x2apic_enabled())
		वापस;
	/*
	 * We करो not have access to IR inside Jailhouse non-root cells.  So
	 * we have to run in physical mode.
	 */
	x2apic_phys = 1;
	/*
	 * This will trigger the चयन to apic_x2apic_phys.  Empty OEM IDs
	 * ensure that only this APIC driver picks up the call.
	 */
	शेष_acpi_madt_oem_check("", "");
#पूर्ण_अगर
पूर्ण

अटल व्योम __init jailhouse_get_smp_config(अचिन्हित पूर्णांक early)
अणु
	काष्ठा ioapic_करोमुख्य_cfg ioapic_cfg = अणु
		.type = IOAPIC_DOMAIN_STRICT,
		.ops = &mp_ioapic_irqकरोमुख्य_ops,
	पूर्ण;
	अचिन्हित पूर्णांक cpu;

	jailhouse_x2apic_init();

	रेजिस्टर_lapic_address(0xfee00000);

	क्रम (cpu = 0; cpu < setup_data.v1.num_cpus; cpu++) अणु
		generic_processor_info(setup_data.v1.cpu_ids[cpu],
				       boot_cpu_apic_version);
	पूर्ण

	smp_found_config = 1;

	अगर (setup_data.v1.standard_ioapic) अणु
		mp_रेजिस्टर_ioapic(0, 0xfec00000, gsi_top, &ioapic_cfg);

		अगर (IS_ENABLED(CONFIG_SERIAL_8250) &&
		    setup_data.hdr.version < 2) अणु
			/* Register 1:1 mapping क्रम legacy UART IRQs 3 and 4 */
			jailhouse_setup_irq(3);
			jailhouse_setup_irq(4);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम jailhouse_no_restart(व्योम)
अणु
	pr_notice("Jailhouse: Restart not supported, halting\n");
	machine_halt();
पूर्ण

अटल पूर्णांक __init jailhouse_pci_arch_init(व्योम)
अणु
	pci_direct_init(1);

	/*
	 * There are no bridges on the भव PCI root bus under Jailhouse,
	 * thus no other way to discover all devices than a full scan.
	 * Respect any overrides via the command line, though.
	 */
	अगर (pcibios_last_bus < 0)
		pcibios_last_bus = 0xff;

#अगर_घोषित CONFIG_PCI_MMCONFIG
	अगर (setup_data.v1.pci_mmconfig_base) अणु
		pci_mmconfig_add(0, 0, pcibios_last_bus,
				 setup_data.v1.pci_mmconfig_base);
		pci_mmcfg_arch_init();
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250
अटल अंतरभूत bool jailhouse_uart_enabled(अचिन्हित पूर्णांक uart_nr)
अणु
	वापस setup_data.v2.flags & BIT(uart_nr);
पूर्ण

अटल व्योम jailhouse_serial_fixup(पूर्णांक port, काष्ठा uart_port *up,
				   u32 *capabilities)
अणु
	अटल स्थिर u16 pcuart_base[] = अणु0x3f8, 0x2f8, 0x3e8, 0x2e8पूर्ण;
	अचिन्हित पूर्णांक n;

	क्रम (n = 0; n < ARRAY_SIZE(pcuart_base); n++) अणु
		अगर (pcuart_base[n] != up->iobase)
			जारी;

		अगर (jailhouse_uart_enabled(n)) अणु
			pr_info("Enabling UART%u (port 0x%lx)\n", n,
				up->iobase);
			jailhouse_setup_irq(up->irq);
		पूर्ण अन्यथा अणु
			/* Deactivate UART अगर access isn't allowed */
			up->iobase = 0;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init jailhouse_serial_workaround(व्योम)
अणु
	/*
	 * There are flags inside setup_data that indicate availability of
	 * platक्रमm UARTs since setup data version 2.
	 *
	 * In हाल of version 1, we करोn't know which UARTs beदीर्घ Linux. In
	 * this हाल, unconditionally रेजिस्टर 1:1 mapping क्रम legacy UART IRQs
	 * 3 and 4.
	 */
	अगर (setup_data.hdr.version > 1)
		serial8250_set_isa_configurator(jailhouse_serial_fixup);
पूर्ण
#अन्यथा /* !CONFIG_SERIAL_8250 */
अटल अंतरभूत व्योम jailhouse_serial_workaround(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_8250 */

अटल व्योम __init jailhouse_init_platक्रमm(व्योम)
अणु
	u64 pa_data = boot_params.hdr.setup_data;
	अचिन्हित दीर्घ setup_data_len;
	काष्ठा setup_data header;
	व्योम *mapping;

	x86_init.irqs.pre_vector_init	= x86_init_noop;
	x86_init.समयrs.समयr_init	= jailhouse_समयr_init;
	x86_init.mpparse.get_smp_config	= jailhouse_get_smp_config;
	x86_init.pci.arch_init		= jailhouse_pci_arch_init;

	x86_platक्रमm.calibrate_cpu	= jailhouse_get_tsc;
	x86_platक्रमm.calibrate_tsc	= jailhouse_get_tsc;
	x86_platक्रमm.get_wallघड़ी	= jailhouse_get_wallघड़ी;
	x86_platक्रमm.legacy.rtc		= 0;
	x86_platक्रमm.legacy.warm_reset	= 0;
	x86_platक्रमm.legacy.i8042	= X86_LEGACY_I8042_PLATFORM_ABSENT;

	legacy_pic			= &null_legacy_pic;

	machine_ops.emergency_restart	= jailhouse_no_restart;

	जबतक (pa_data) अणु
		mapping = early_memremap(pa_data, माप(header));
		स_नकल(&header, mapping, माप(header));
		early_memunmap(mapping, माप(header));

		अगर (header.type == SETUP_JAILHOUSE)
			अवरोध;

		pa_data = header.next;
	पूर्ण

	अगर (!pa_data)
		panic("Jailhouse: No valid setup data found");

	/* setup data must at least contain the header */
	अगर (header.len < माप(setup_data.hdr))
		जाओ unsupported;

	pa_data += दुरत्व(काष्ठा setup_data, data);
	setup_data_len = min_t(अचिन्हित दीर्घ, माप(setup_data),
			       (अचिन्हित दीर्घ)header.len);
	mapping = early_memremap(pa_data, setup_data_len);
	स_नकल(&setup_data, mapping, setup_data_len);
	early_memunmap(mapping, setup_data_len);

	अगर (setup_data.hdr.version == 0 ||
	    setup_data.hdr.compatible_version !=
		JAILHOUSE_SETUP_REQUIRED_VERSION ||
	    (setup_data.hdr.version == 1 && header.len < SETUP_DATA_V1_LEN) ||
	    (setup_data.hdr.version >= 2 && header.len < SETUP_DATA_V2_LEN))
		जाओ unsupported;

	pmपंचांगr_ioport = setup_data.v1.pm_समयr_address;
	pr_debug("Jailhouse: PM-Timer IO Port: %#x\n", pmपंचांगr_ioport);

	precalibrated_tsc_khz = setup_data.v1.tsc_khz;
	setup_क्रमce_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	pci_probe = 0;

	/*
	 * Aव्योम that the kernel complains about missing ACPI tables - there
	 * are none in a non-root cell.
	 */
	disable_acpi();

	jailhouse_serial_workaround();
	वापस;

unsupported:
	panic("Jailhouse: Unsupported setup data structure");
पूर्ण

bool jailhouse_paravirt(व्योम)
अणु
	वापस jailhouse_cpuid_base() != 0;
पूर्ण

अटल bool __init jailhouse_x2apic_available(व्योम)
अणु
	/*
	 * The x2APIC is only available अगर the root cell enabled it. Jailhouse
	 * करोes not support चयनing between xAPIC and x2APIC.
	 */
	वापस x2apic_enabled();
पूर्ण

स्थिर काष्ठा hypervisor_x86 x86_hyper_jailhouse __refस्थिर = अणु
	.name			= "Jailhouse",
	.detect			= jailhouse_detect,
	.init.init_platक्रमm	= jailhouse_init_platक्रमm,
	.init.x2apic_available	= jailhouse_x2apic_available,
	.ignore_nopv		= true,
पूर्ण;
