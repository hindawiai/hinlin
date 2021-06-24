<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <linux/efi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/sched.h>
#समावेश <linux/tboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/objtool.h>
#समावेश <linux/pgtable.h>
#समावेश <acpi/reboot.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/reboot_fixups.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/virtext.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/smp.h>

#समावेश <linux/प्रकार.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/efi.h>

/*
 * Power off function, अगर any
 */
व्योम (*pm_घातer_off)(व्योम);
EXPORT_SYMBOL(pm_घातer_off);

/*
 * This is set अगर we need to go through the 'emergency' path.
 * When machine_emergency_restart() is called, we may be on
 * an inconsistent state and won't be able to करो a clean cleanup
 */
अटल पूर्णांक reboot_emergency;

/* This is set by the PCI code अगर either type 1 or type 2 PCI is detected */
bool port_cf9_safe = false;

/*
 * Reboot options and प्रणाली स्वतः-detection code provided by
 * Dell Inc. so their प्रणालीs "just work". :-)
 */

/*
 * Some machines require the "reboot=a" commandline options
 */
अटल पूर्णांक __init set_acpi_reboot(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (reboot_type != BOOT_ACPI) अणु
		reboot_type = BOOT_ACPI;
		pr_info("%s series board detected. Selecting %s-method for reboots.\n",
			d->ident, "ACPI");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Some machines require the "reboot=b" or "reboot=k"  commandline options,
 * this quirk makes that स्वतःmatic.
 */
अटल पूर्णांक __init set_bios_reboot(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (reboot_type != BOOT_BIOS) अणु
		reboot_type = BOOT_BIOS;
		pr_info("%s series board detected. Selecting %s-method for reboots.\n",
			d->ident, "BIOS");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Some machines करोn't handle the शेष ACPI reboot method and
 * require the EFI reboot method:
 */
अटल पूर्णांक __init set_efi_reboot(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (reboot_type != BOOT_EFI && !efi_runसमय_disabled()) अणु
		reboot_type = BOOT_EFI;
		pr_info("%s series board detected. Selecting EFI-method for reboot.\n", d->ident);
	पूर्ण
	वापस 0;
पूर्ण

व्योम __noवापस machine_real_restart(अचिन्हित पूर्णांक type)
अणु
	local_irq_disable();

	/*
	 * Write zero to CMOS रेजिस्टर number 0x0f, which the BIOS POST
	 * routine will recognize as telling it to करो a proper reboot.  (Well
	 * that's what this book in front of me says -- it may only apply to
	 * the Phoenix BIOS though, it's not clear).  At the same समय,
	 * disable NMIs by setting the top bit in the CMOS address रेजिस्टर,
	 * as we're about to do peculiar things to the CPU.  I'm not sure अगर
	 * `outb_p' is needed instead of just `outb'.  Use it to be on the
	 * safe side.  (Yes, CMOS_WRITE करोes outb_p's. -  Paul G.)
	 */
	spin_lock(&rtc_lock);
	CMOS_WRITE(0x00, 0x8f);
	spin_unlock(&rtc_lock);

	/*
	 * Switch back to the initial page table.
	 */
#अगर_घोषित CONFIG_X86_32
	load_cr3(initial_page_table);
#अन्यथा
	ग_लिखो_cr3(real_mode_header->trampoline_pgd);

	/* Exiting दीर्घ mode will fail अगर CR4.PCIDE is set. */
	अगर (boot_cpu_has(X86_FEATURE_PCID))
		cr4_clear_bits(X86_CR4_PCIDE);
#पूर्ण_अगर

	/* Jump to the identity-mapped low memory code */
#अगर_घोषित CONFIG_X86_32
	यंत्र अस्थिर("jmpl *%0" : :
		     "rm" (real_mode_header->machine_real_restart_यंत्र),
		     "a" (type));
#अन्यथा
	यंत्र अस्थिर("ljmpl *%0" : :
		     "m" (real_mode_header->machine_real_restart_यंत्र),
		     "D" (type));
#पूर्ण_अगर
	unreachable();
पूर्ण
#अगर_घोषित CONFIG_APM_MODULE
EXPORT_SYMBOL(machine_real_restart);
#पूर्ण_अगर
STACK_FRAME_NON_STANDARD(machine_real_restart);

/*
 * Some Apple MacBook and MacBookPro's needs reboot=p to be able to reboot
 */
अटल पूर्णांक __init set_pci_reboot(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (reboot_type != BOOT_CF9_FORCE) अणु
		reboot_type = BOOT_CF9_FORCE;
		pr_info("%s series board detected. Selecting %s-method for reboots.\n",
			d->ident, "PCI");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init set_kbd_reboot(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (reboot_type != BOOT_KBD) अणु
		reboot_type = BOOT_KBD;
		pr_info("%s series board detected. Selecting %s-method for reboot.\n",
			d->ident, "KBD");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This is a single dmi_table handling all reboot quirks.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id reboot_dmi_table[] __initस्थिर = अणु

	/* Acer */
	अणु	/* Handle reboot issue on Acer Aspire one */
		.callback = set_kbd_reboot,
		.ident = "Acer Aspire One A110",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AOA110"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle reboot issue on Acer TravelMate X514-51T */
		.callback = set_efi_reboot,
		.ident = "Acer TravelMate X514-51T",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate X514-51T"),
		पूर्ण,
	पूर्ण,

	/* Apple */
	अणु	/* Handle problems with rebooting on Apple MacBook5 */
		.callback = set_pci_reboot,
		.ident = "Apple MacBook5",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBook5"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Apple MacBook6,1 */
		.callback = set_pci_reboot,
		.ident = "Apple MacBook6,1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBook6,1"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Apple MacBookPro5 */
		.callback = set_pci_reboot,
		.ident = "Apple MacBookPro5",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro5"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Apple Macmini3,1 */
		.callback = set_pci_reboot,
		.ident = "Apple Macmini3,1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Macmini3,1"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the iMac9,1. */
		.callback = set_pci_reboot,
		.ident = "Apple iMac9,1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "iMac9,1"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the iMac10,1. */
		.callback = set_pci_reboot,
		.ident = "Apple iMac10,1",
		.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "iMac10,1"),
		पूर्ण,
	पूर्ण,

	/* ASRock */
	अणु	/* Handle problems with rebooting on ASRock Q1900DC-ITX */
		.callback = set_pci_reboot,
		.ident = "ASRock Q1900DC-ITX",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASRock"),
			DMI_MATCH(DMI_BOARD_NAME, "Q1900DC-ITX"),
		पूर्ण,
	पूर्ण,

	/* ASUS */
	अणु	/* Handle problems with rebooting on ASUS P4S800 */
		.callback = set_bios_reboot,
		.ident = "ASUS P4S800",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "P4S800"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on ASUS EeeBook X205TA */
		.callback = set_acpi_reboot,
		.ident = "ASUS EeeBook X205TA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X205TA"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on ASUS EeeBook X205TAW */
		.callback = set_acpi_reboot,
		.ident = "ASUS EeeBook X205TAW",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X205TAW"),
		पूर्ण,
	पूर्ण,

	/* Certec */
	अणु       /* Handle problems with rebooting on Certec BPC600 */
		.callback = set_pci_reboot,
		.ident = "Certec BPC600",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Certec"),
			DMI_MATCH(DMI_PRODUCT_NAME, "BPC600"),
		पूर्ण,
	पूर्ण,

	/* Dell */
	अणु	/* Handle problems with rebooting on Dell DXP061 */
		.callback = set_bios_reboot,
		.ident = "Dell DXP061",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Dell DXP061"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell E520's */
		.callback = set_bios_reboot,
		.ident = "Dell E520",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Dell DM061"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Latitude E5410. */
		.callback = set_pci_reboot,
		.ident = "Dell Latitude E5410",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude E5410"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Latitude E5420. */
		.callback = set_pci_reboot,
		.ident = "Dell Latitude E5420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude E5420"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Latitude E6320. */
		.callback = set_pci_reboot,
		.ident = "Dell Latitude E6320",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude E6320"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Latitude E6420. */
		.callback = set_pci_reboot,
		.ident = "Dell Latitude E6420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude E6420"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 330 with 0KP561 */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 330",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 330"),
			DMI_MATCH(DMI_BOARD_NAME, "0KP561"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 360 with 0T656F */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 360"),
			DMI_MATCH(DMI_BOARD_NAME, "0T656F"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 745's SFF */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 745",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 745"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 745's DFF */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 745",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 745"),
			DMI_MATCH(DMI_BOARD_NAME, "0MM599"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 745 with 0KW626 */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 745",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 745"),
			DMI_MATCH(DMI_BOARD_NAME, "0KW626"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell OptiPlex 760 with 0G919G */
		.callback = set_bios_reboot,
		.ident = "Dell OptiPlex 760",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 760"),
			DMI_MATCH(DMI_BOARD_NAME, "0G919G"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the OptiPlex 990. */
		.callback = set_pci_reboot,
		.ident = "Dell OptiPlex 990",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 990"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell 300's */
		.callback = set_bios_reboot,
		.ident = "Dell PowerEdge 300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 300/"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell 1300's */
		.callback = set_bios_reboot,
		.ident = "Dell PowerEdge 1300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 1300/"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell 2400's */
		.callback = set_bios_reboot,
		.ident = "Dell PowerEdge 2400",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PowerEdge 2400"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Dell PowerEdge C6100. */
		.callback = set_pci_reboot,
		.ident = "Dell PowerEdge C6100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell"),
			DMI_MATCH(DMI_PRODUCT_NAME, "C6100"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on the Precision M6600. */
		.callback = set_pci_reboot,
		.ident = "Dell Precision M6600",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Precision M6600"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell T5400's */
		.callback = set_bios_reboot,
		.ident = "Dell Precision T5400",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Precision WorkStation T5400"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell T7400's */
		.callback = set_bios_reboot,
		.ident = "Dell Precision T7400",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Precision WorkStation T7400"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell XPS710 */
		.callback = set_bios_reboot,
		.ident = "Dell XPS710",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Dell XPS710"),
		पूर्ण,
	पूर्ण,
	अणु	/* Handle problems with rebooting on Dell Optiplex 7450 AIO */
		.callback = set_acpi_reboot,
		.ident = "Dell OptiPlex 7450 AIO",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 7450 AIO"),
		पूर्ण,
	पूर्ण,

	/* Hewlett-Packard */
	अणु	/* Handle problems with rebooting on HP laptops */
		.callback = set_bios_reboot,
		.ident = "HP Compaq Laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq"),
		पूर्ण,
	पूर्ण,

	अणु	/* PCIe Wअगरi card isn't detected after reboot otherwise */
		.callback = set_pci_reboot,
		.ident = "Zotac ZBOX CI327 nano",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "NA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ZBOX-CI327NANO-GS-01"),
		पूर्ण,
	पूर्ण,

	/* Sony */
	अणु	/* Handle problems with rebooting on Sony VGN-Z540N */
		.callback = set_bios_reboot,
		.ident = "Sony VGN-Z540N",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "VGN-Z540N"),
		पूर्ण,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init reboot_init(व्योम)
अणु
	पूर्णांक rv;

	/*
	 * Only करो the DMI check अगर reboot_type hasn't been overridden
	 * on the command line
	 */
	अगर (!reboot_शेष)
		वापस 0;

	/*
	 * The DMI quirks table takes precedence. If no quirks entry
	 * matches and the ACPI Hardware Reduced bit is set and EFI
	 * runसमय services are enabled, क्रमce EFI reboot.
	 */
	rv = dmi_check_प्रणाली(reboot_dmi_table);

	अगर (!rv && efi_reboot_required() && !efi_runसमय_disabled())
		reboot_type = BOOT_EFI;

	वापस 0;
पूर्ण
core_initcall(reboot_init);

अटल अंतरभूत व्योम kb_रुको(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x10000; i++) अणु
		अगर ((inb(0x64) & 0x02) == 0)
			अवरोध;
		udelay(2);
	पूर्ण
पूर्ण

अटल व्योम vmxoff_nmi(पूर्णांक cpu, काष्ठा pt_regs *regs)
अणु
	cpu_emergency_vmxoff();
पूर्ण

/* Use NMIs as IPIs to tell all CPUs to disable भवization */
अटल व्योम emergency_vmx_disable_all(व्योम)
अणु
	/* Just make sure we won't change CPUs जबतक करोing this */
	local_irq_disable();

	/*
	 * Disable VMX on all CPUs beक्रमe rebooting, otherwise we risk hanging
	 * the machine, because the CPU blocks INIT when it's in VMX root.
	 *
	 * We can't take any locks and we may be on an inconsistent state, so
	 * use NMIs as IPIs to tell the other CPUs to निकास VMX root and halt.
	 *
	 * Do the NMI shootकरोwn even अगर VMX अगर off on _this_ CPU, as that
	 * करोesn't prevent a dअगरferent CPU from being in VMX root operation.
	 */
	अगर (cpu_has_vmx()) अणु
		/* Safely क्रमce _this_ CPU out of VMX root operation. */
		__cpu_emergency_vmxoff();

		/* Halt and निकास VMX root operation on the other CPUs. */
		nmi_shootकरोwn_cpus(vmxoff_nmi);
	पूर्ण
पूर्ण


व्योम __attribute__((weak)) mach_reboot_fixups(व्योम)
अणु
पूर्ण

/*
 * To the best of our knowledge Winकरोws compatible x86 hardware expects
 * the following on reboot:
 *
 * 1) If the FADT has the ACPI reboot रेजिस्टर flag set, try it
 * 2) If still alive, ग_लिखो to the keyboard controller
 * 3) If still alive, ग_लिखो to the ACPI reboot रेजिस्टर again
 * 4) If still alive, ग_लिखो to the keyboard controller again
 * 5) If still alive, call the EFI runसमय service to reboot
 * 6) If no EFI runसमय service, call the BIOS to करो a reboot
 *
 * We शेष to following the same pattern. We also have
 * two other reboot methods: 'triple fault' and 'PCI', which
 * can be triggered via the reboot= kernel boot option or
 * via quirks.
 *
 * This means that this function can never वापस, it can misbehave
 * by not rebooting properly and hanging.
 */
अटल व्योम native_machine_emergency_restart(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक attempt = 0;
	पूर्णांक orig_reboot_type = reboot_type;
	अचिन्हित लघु mode;

	अगर (reboot_emergency)
		emergency_vmx_disable_all();

	tboot_shutकरोwn(TB_SHUTDOWN_REBOOT);

	/* Tell the BIOS अगर we want cold or warm reboot */
	mode = reboot_mode == REBOOT_WARM ? 0x1234 : 0;
	*((अचिन्हित लघु *)__va(0x472)) = mode;

	/*
	 * If an EFI capsule has been रेजिस्टरed with the firmware then
	 * override the reboot= parameter.
	 */
	अगर (efi_capsule_pending(शून्य)) अणु
		pr_info("EFI capsule is pending, forcing EFI reboot.\n");
		reboot_type = BOOT_EFI;
	पूर्ण

	क्रम (;;) अणु
		/* Could also try the reset bit in the Hammer NB */
		चयन (reboot_type) अणु
		हाल BOOT_ACPI:
			acpi_reboot();
			reboot_type = BOOT_KBD;
			अवरोध;

		हाल BOOT_KBD:
			mach_reboot_fixups(); /* For board specअगरic fixups */

			क्रम (i = 0; i < 10; i++) अणु
				kb_रुको();
				udelay(50);
				outb(0xfe, 0x64); /* Pulse reset low */
				udelay(50);
			पूर्ण
			अगर (attempt == 0 && orig_reboot_type == BOOT_ACPI) अणु
				attempt = 1;
				reboot_type = BOOT_ACPI;
			पूर्ण अन्यथा अणु
				reboot_type = BOOT_EFI;
			पूर्ण
			अवरोध;

		हाल BOOT_EFI:
			efi_reboot(reboot_mode, शून्य);
			reboot_type = BOOT_BIOS;
			अवरोध;

		हाल BOOT_BIOS:
			machine_real_restart(MRR_BIOS);

			/* We're probably dead after this, but... */
			reboot_type = BOOT_CF9_SAFE;
			अवरोध;

		हाल BOOT_CF9_FORCE:
			port_cf9_safe = true;
			fallthrough;

		हाल BOOT_CF9_SAFE:
			अगर (port_cf9_safe) अणु
				u8 reboot_code = reboot_mode == REBOOT_WARM ?  0x06 : 0x0E;
				u8 cf9 = inb(0xcf9) & ~reboot_code;
				outb(cf9|2, 0xcf9); /* Request hard reset */
				udelay(50);
				/* Actually करो the reset */
				outb(cf9|reboot_code, 0xcf9);
				udelay(50);
			पूर्ण
			reboot_type = BOOT_TRIPLE;
			अवरोध;

		हाल BOOT_TRIPLE:
			idt_invalidate(शून्य);
			__यंत्र__ __अस्थिर__("int3");

			/* We're probably dead after this, but... */
			reboot_type = BOOT_KBD;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम native_machine_shutकरोwn(व्योम)
अणु
	/* Stop the cpus and apics */
#अगर_घोषित CONFIG_X86_IO_APIC
	/*
	 * Disabling IO APIC beक्रमe local APIC is a workaround क्रम
	 * erratum AVR31 in "Intel Atom Processor C2000 Product Family
	 * Specअगरication Update". In this situation, पूर्णांकerrupts that target
	 * a Logical Processor whose Local APIC is either in the process of
	 * being hardware disabled or software disabled are neither delivered
	 * nor discarded. When this erratum occurs, the processor may hang.
	 *
	 * Even without the erratum, it still makes sense to quiet IO APIC
	 * beक्रमe disabling Local APIC.
	 */
	clear_IO_APIC();
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	/*
	 * Stop all of the others. Also disable the local irq to
	 * not receive the per-cpu समयr पूर्णांकerrupt which may trigger
	 * scheduler's load balance.
	 */
	local_irq_disable();
	stop_other_cpus();
#पूर्ण_अगर

	lapic_shutकरोwn();
	restore_boot_irq_mode();

#अगर_घोषित CONFIG_HPET_TIMER
	hpet_disable();
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
	x86_platक्रमm.iommu_shutकरोwn();
#पूर्ण_अगर
पूर्ण

अटल व्योम __machine_emergency_restart(पूर्णांक emergency)
अणु
	reboot_emergency = emergency;
	machine_ops.emergency_restart();
पूर्ण

अटल व्योम native_machine_restart(अक्षर *__unused)
अणु
	pr_notice("machine restart\n");

	अगर (!reboot_क्रमce)
		machine_shutकरोwn();
	__machine_emergency_restart(0);
पूर्ण

अटल व्योम native_machine_halt(व्योम)
अणु
	/* Stop other cpus and apics */
	machine_shutकरोwn();

	tboot_shutकरोwn(TB_SHUTDOWN_HALT);

	stop_this_cpu(शून्य);
पूर्ण

अटल व्योम native_machine_घातer_off(व्योम)
अणु
	अगर (pm_घातer_off) अणु
		अगर (!reboot_क्रमce)
			machine_shutकरोwn();
		pm_घातer_off();
	पूर्ण
	/* A fallback in हाल there is no PM info available */
	tboot_shutकरोwn(TB_SHUTDOWN_HALT);
पूर्ण

काष्ठा machine_ops machine_ops __ro_after_init = अणु
	.घातer_off = native_machine_घातer_off,
	.shutकरोwn = native_machine_shutकरोwn,
	.emergency_restart = native_machine_emergency_restart,
	.restart = native_machine_restart,
	.halt = native_machine_halt,
#अगर_घोषित CONFIG_KEXEC_CORE
	.crash_shutकरोwn = native_machine_crash_shutकरोwn,
#पूर्ण_अगर
पूर्ण;

व्योम machine_घातer_off(व्योम)
अणु
	machine_ops.घातer_off();
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
	machine_ops.shutकरोwn();
पूर्ण

व्योम machine_emergency_restart(व्योम)
अणु
	__machine_emergency_restart(1);
पूर्ण

व्योम machine_restart(अक्षर *cmd)
अणु
	machine_ops.restart(cmd);
पूर्ण

व्योम machine_halt(व्योम)
अणु
	machine_ops.halt();
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	machine_ops.crash_shutकरोwn(regs);
पूर्ण
#पूर्ण_अगर


/* This is the CPU perक्रमming the emergency shutकरोwn work. */
पूर्णांक crashing_cpu = -1;

#अगर defined(CONFIG_SMP)

अटल nmi_shootकरोwn_cb shootकरोwn_callback;

अटल atomic_t रुकोing_क्रम_crash_ipi;
अटल पूर्णांक crash_ipi_issued;

अटल पूर्णांक crash_nmi_callback(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu;

	cpu = raw_smp_processor_id();

	/*
	 * Don't करो anything अगर this handler is invoked on crashing cpu.
	 * Otherwise, प्रणाली will completely hang. Crashing cpu can get
	 * an NMI अगर प्रणाली was initially booted with nmi_watchकरोg parameter.
	 */
	अगर (cpu == crashing_cpu)
		वापस NMI_HANDLED;
	local_irq_disable();

	shootकरोwn_callback(cpu, regs);

	atomic_dec(&रुकोing_क्रम_crash_ipi);
	/* Assume hlt works */
	halt();
	क्रम (;;)
		cpu_relax();

	वापस NMI_HANDLED;
पूर्ण

/*
 * Halt all other CPUs, calling the specअगरied function on each of them
 *
 * This function can be used to halt all other CPUs on crash
 * or emergency reboot समय. The function passed as parameter
 * will be called inside a NMI handler on all CPUs.
 */
व्योम nmi_shootकरोwn_cpus(nmi_shootकरोwn_cb callback)
अणु
	अचिन्हित दीर्घ msecs;
	local_irq_disable();

	/* Make a note of crashing cpu. Will be used in NMI callback. */
	crashing_cpu = safe_smp_processor_id();

	shootकरोwn_callback = callback;

	atomic_set(&रुकोing_क्रम_crash_ipi, num_online_cpus() - 1);
	/* Would it be better to replace the trap vector here? */
	अगर (रेजिस्टर_nmi_handler(NMI_LOCAL, crash_nmi_callback,
				 NMI_FLAG_FIRST, "crash"))
		वापस;		/* Return what? */
	/*
	 * Ensure the new callback function is set beक्रमe sending
	 * out the NMI
	 */
	wmb();

	apic_send_IPI_allbutself(NMI_VECTOR);

	/* Kick CPUs looping in NMI context. */
	WRITE_ONCE(crash_ipi_issued, 1);

	msecs = 1000; /* Wait at most a second क्रम the other cpus to stop */
	जबतक ((atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0) && msecs) अणु
		mdelay(1);
		msecs--;
	पूर्ण

	/* Leave the nmi callback set */
पूर्ण

/*
 * Check अगर the crash dumping IPI got issued and अगर so, call its callback
 * directly. This function is used when we have alपढ़ोy been in NMI handler.
 * It करोesn't वापस.
 */
व्योम run_crash_ipi_callback(काष्ठा pt_regs *regs)
अणु
	अगर (crash_ipi_issued)
		crash_nmi_callback(0, regs);
पूर्ण

/* Override the weak function in kernel/panic.c */
व्योम nmi_panic_self_stop(काष्ठा pt_regs *regs)
अणु
	जबतक (1) अणु
		/* If no CPU is preparing crash dump, we simply loop here. */
		run_crash_ipi_callback(regs);
		cpu_relax();
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_SMP */
व्योम nmi_shootकरोwn_cpus(nmi_shootकरोwn_cb callback)
अणु
	/* No other CPUs to shoot करोwn */
पूर्ण

व्योम run_crash_ipi_callback(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर
