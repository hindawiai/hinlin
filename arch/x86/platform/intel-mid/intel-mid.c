<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel MID platक्रमm setup code
 *
 * (C) Copyright 2008, 2012, 2021 Intel Corporation
 * Author: Jacob Pan (jacob.jun.pan@पूर्णांकel.com)
 * Author: Sathyanarayanan Kuppuswamy <sathyanarayanan.kuppuswamy@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "intel_mid: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>
#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mpspec_def.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>
#समावेश <यंत्र/reboot.h>

#घोषणा IPCMSG_COLD_OFF		0x80	/* Only क्रम Tangier */
#घोषणा IPCMSG_COLD_RESET	0xF1

अटल व्योम पूर्णांकel_mid_घातer_off(व्योम)
अणु
	/* Shut करोwn South Complex via PWRMU */
	पूर्णांकel_mid_pwr_घातer_off();

	/* Only क्रम Tangier, the rest will ignore this command */
	पूर्णांकel_scu_ipc_dev_simple_command(शून्य, IPCMSG_COLD_OFF, 1);
पूर्ण;

अटल व्योम पूर्णांकel_mid_reboot(व्योम)
अणु
	पूर्णांकel_scu_ipc_dev_simple_command(शून्य, IPCMSG_COLD_RESET, 0);
पूर्ण

अटल व्योम __init पूर्णांकel_mid_समय_init(व्योम)
अणु
	/* Lapic only, no apbt */
	x86_init.समयrs.setup_percpu_घड़ीev = setup_boot_APIC_घड़ी;
	x86_cpuinit.setup_percpu_घड़ीev = setup_secondary_APIC_घड़ी;
पूर्ण

अटल व्योम पूर्णांकel_mid_arch_setup(व्योम)
अणु
	चयन (boot_cpu_data.x86_model) अणु
	हाल 0x3C:
	हाल 0x4A:
		x86_platक्रमm.legacy.rtc = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Intel MID platक्रमms are using explicitly defined regulators.
	 *
	 * Let the regulator core know that we करो not have any additional
	 * regulators left. This lets it substitute unprovided regulators with
	 * dummy ones:
	 */
	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

/*
 * Moorestown करोes not have बाह्यal NMI source nor port 0x61 to report
 * NMI status. The possible NMI sources are from pmu as a result of NMI
 * watchकरोg or lock debug. Reading io port 0x61 results in 0xff which
 * misled NMI handler.
 */
अटल अचिन्हित अक्षर पूर्णांकel_mid_get_nmi_reason(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Moorestown specअगरic x86_init function overrides and early setup
 * calls.
 */
व्योम __init x86_पूर्णांकel_mid_early_setup(व्योम)
अणु
	x86_init.resources.probe_roms = x86_init_noop;
	x86_init.resources.reserve_resources = x86_init_noop;

	x86_init.समयrs.समयr_init = पूर्णांकel_mid_समय_init;
	x86_init.समयrs.setup_percpu_घड़ीev = x86_init_noop;

	x86_init.irqs.pre_vector_init = x86_init_noop;

	x86_init.oem.arch_setup = पूर्णांकel_mid_arch_setup;

	x86_platक्रमm.get_nmi_reason = पूर्णांकel_mid_get_nmi_reason;

	x86_init.pci.arch_init = पूर्णांकel_mid_pci_init;
	x86_init.pci.fixup_irqs = x86_init_noop;

	legacy_pic = &null_legacy_pic;

	/*
	 * Do nothing क्रम now as everything needed करोne in
	 * x86_पूर्णांकel_mid_early_setup() below.
	 */
	x86_init.acpi.reduced_hw_early_init = x86_init_noop;

	pm_घातer_off = पूर्णांकel_mid_घातer_off;
	machine_ops.emergency_restart  = पूर्णांकel_mid_reboot;

	/* Aव्योम searching क्रम BIOS MP tables */
	x86_init.mpparse.find_smp_config = x86_init_noop;
	x86_init.mpparse.get_smp_config = x86_init_uपूर्णांक_noop;
	set_bit(MP_BUS_ISA, mp_bus_not_pci);
पूर्ण
