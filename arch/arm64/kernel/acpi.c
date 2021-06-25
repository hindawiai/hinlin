<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ARM64 Specअगरic Low-Level ACPI Boot Support
 *
 *  Copyright (C) 2013-2014, Linaro Ltd.
 *	Author: Al Stone <al.stone@linaro.org>
 *	Author: Graeme Gregory <graeme.gregory@linaro.org>
 *	Author: Hanjun Guo <hanjun.guo@linaro.org>
 *	Author: Tomasz Nowicki <tomasz.nowicki@linaro.org>
 *	Author: Naresh Bhat <naresh.bhat@linaro.org>
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/efi.h>
#समावेश <linux/efi-bgrt.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/smp.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/pgtable.h>

#समावेश <acpi/ghes.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/smp_plat.h>

पूर्णांक acpi_noirq = 1;		/* skip ACPI IRQ initialization */
पूर्णांक acpi_disabled = 1;
EXPORT_SYMBOL(acpi_disabled);

पूर्णांक acpi_pci_disabled = 1;	/* skip ACPI PCI scan and IRQ initialization */
EXPORT_SYMBOL(acpi_pci_disabled);

अटल bool param_acpi_off __initdata;
अटल bool param_acpi_on __initdata;
अटल bool param_acpi_क्रमce __initdata;

अटल पूर्णांक __init parse_acpi(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	/* "acpi=off" disables both ACPI table parsing and पूर्णांकerpreter */
	अगर (म_भेद(arg, "off") == 0)
		param_acpi_off = true;
	अन्यथा अगर (म_भेद(arg, "on") == 0) /* prefer ACPI over DT */
		param_acpi_on = true;
	अन्यथा अगर (म_भेद(arg, "force") == 0) /* क्रमce ACPI to be enabled */
		param_acpi_क्रमce = true;
	अन्यथा
		वापस -EINVAL;	/* Core will prपूर्णांक when we वापस error */

	वापस 0;
पूर्ण
early_param("acpi", parse_acpi);

अटल पूर्णांक __init dt_scan_depth1_nodes(अचिन्हित दीर्घ node,
				       स्थिर अक्षर *uname, पूर्णांक depth,
				       व्योम *data)
अणु
	/*
	 * Ignore anything not directly under the root node; we'll
	 * catch its parent instead.
	 */
	अगर (depth != 1)
		वापस 0;

	अगर (म_भेद(uname, "chosen") == 0)
		वापस 0;

	अगर (म_भेद(uname, "hypervisor") == 0 &&
	    of_flat_dt_is_compatible(node, "xen,xen"))
		वापस 0;

	/*
	 * This node at depth 1 is neither a chosen node nor a xen node,
	 * which we करो not expect.
	 */
	वापस 1;
पूर्ण

/*
 * __acpi_map_table() will be called beक्रमe page_init(), so early_ioremap()
 * or early_memremap() should be called here to क्रम ACPI table mapping.
 */
व्योम __init __iomem *__acpi_map_table(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size)
अणु
	अगर (!size)
		वापस शून्य;

	वापस early_memremap(phys, size);
पूर्ण

व्योम __init __acpi_unmap_table(व्योम __iomem *map, अचिन्हित दीर्घ size)
अणु
	अगर (!map || !size)
		वापस;

	early_memunmap(map, size);
पूर्ण

bool __init acpi_psci_present(व्योम)
अणु
	वापस acpi_gbl_FADT.arm_boot_flags & ACPI_FADT_PSCI_COMPLIANT;
पूर्ण

/* Whether HVC must be used instead of SMC as the PSCI conduit */
bool acpi_psci_use_hvc(व्योम)
अणु
	वापस acpi_gbl_FADT.arm_boot_flags & ACPI_FADT_PSCI_USE_HVC;
पूर्ण

/*
 * acpi_fadt_sanity_check() - Check FADT presence and carry out sanity
 *			      checks on it
 *
 * Return 0 on success,  <0 on failure
 */
अटल पूर्णांक __init acpi_fadt_sanity_check(व्योम)
अणु
	काष्ठा acpi_table_header *table;
	काष्ठा acpi_table_fadt *fadt;
	acpi_status status;
	पूर्णांक ret = 0;

	/*
	 * FADT is required on arm64; retrieve it to check its presence
	 * and carry out revision and ACPI HW reduced compliancy tests
	 */
	status = acpi_get_table(ACPI_SIG_FADT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		स्थिर अक्षर *msg = acpi_क्रमmat_exception(status);

		pr_err("Failed to get FADT table, %s\n", msg);
		वापस -ENODEV;
	पूर्ण

	fadt = (काष्ठा acpi_table_fadt *)table;

	/*
	 * Revision in table header is the FADT Major revision, and there
	 * is a minor revision of FADT which was पूर्णांकroduced by ACPI 5.1,
	 * we only deal with ACPI 5.1 or newer revision to get GIC and SMP
	 * boot protocol configuration data.
	 */
	अगर (table->revision < 5 ||
	   (table->revision == 5 && fadt->minor_revision < 1)) अणु
		pr_err(FW_BUG "Unsupported FADT revision %d.%d, should be 5.1+\n",
		       table->revision, fadt->minor_revision);

		अगर (!fadt->arm_boot_flags) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		pr_err("FADT has ARM boot flags set, assuming 5.1\n");
	पूर्ण

	अगर (!(fadt->flags & ACPI_FADT_HW_REDUCED)) अणु
		pr_err("FADT not ACPI hardware reduced compliant\n");
		ret = -EINVAL;
	पूर्ण

out:
	/*
	 * acpi_get_table() creates FADT table mapping that
	 * should be released after parsing and beक्रमe resuming boot
	 */
	acpi_put_table(table);
	वापस ret;
पूर्ण

/*
 * acpi_boot_table_init() called from setup_arch(), always.
 *	1. find RSDP and get its address, and then find XSDT
 *	2. extract all tables and checksums them all
 *	3. check ACPI FADT revision
 *	4. check ACPI FADT HW reduced flag
 *
 * We can parse ACPI boot-समय tables such as MADT after
 * this function is called.
 *
 * On वापस ACPI is enabled अगर either:
 *
 * - ACPI tables are initialized and sanity checks passed
 * - acpi=क्रमce was passed in the command line and ACPI was not disabled
 *   explicitly through acpi=off command line parameter
 *
 * ACPI is disabled on function वापस otherwise
 */
व्योम __init acpi_boot_table_init(व्योम)
अणु
	/*
	 * Enable ACPI instead of device tree unless
	 * - ACPI has been disabled explicitly (acpi=off), or
	 * - the device tree is not empty (it has more than just a /chosen node,
	 *   and a /hypervisor node when running on Xen)
	 *   and ACPI has not been [क्रमce] enabled (acpi=on|क्रमce)
	 */
	अगर (param_acpi_off ||
	    (!param_acpi_on && !param_acpi_क्रमce &&
	     of_scan_flat_dt(dt_scan_depth1_nodes, शून्य)))
		जाओ करोne;

	/*
	 * ACPI is disabled at this poपूर्णांक. Enable it in order to parse
	 * the ACPI tables and carry out sanity checks
	 */
	enable_acpi();

	/*
	 * If ACPI tables are initialized and FADT sanity checks passed,
	 * leave ACPI enabled and carry on booting; otherwise disable ACPI
	 * on initialization error.
	 * If acpi=क्रमce was passed on the command line it क्रमces ACPI
	 * to be enabled even अगर its initialization failed.
	 */
	अगर (acpi_table_init() || acpi_fadt_sanity_check()) अणु
		pr_err("Failed to init ACPI tables\n");
		अगर (!param_acpi_क्रमce)
			disable_acpi();
	पूर्ण

करोne:
	अगर (acpi_disabled) अणु
		अगर (earlycon_acpi_spcr_enable)
			early_init_dt_scan_chosen_मानक_निकास();
	पूर्ण अन्यथा अणु
		acpi_parse_spcr(earlycon_acpi_spcr_enable, true);
		अगर (IS_ENABLED(CONFIG_ACPI_BGRT))
			acpi_table_parse(ACPI_SIG_BGRT, acpi_parse_bgrt);
	पूर्ण
पूर्ण

pgprot_t __acpi_get_mem_attribute(phys_addr_t addr)
अणु
	/*
	 * According to "Table 8 Map: EFI memory types to AArch64 memory
	 * types" of UEFI 2.5 section 2.3.6.1, each EFI memory type is
	 * mapped to a corresponding MAIR attribute encoding.
	 * The EFI memory attribute advises all possible capabilities
	 * of a memory region. We use the most efficient capability.
	 */

	u64 attr;

	attr = efi_mem_attributes(addr);
	अगर (attr & EFI_MEMORY_WB)
		वापस PAGE_KERNEL;
	अगर (attr & EFI_MEMORY_WT)
		वापस __pgprot(PROT_NORMAL_WT);
	अगर (attr & EFI_MEMORY_WC)
		वापस __pgprot(PROT_NORMAL_NC);
	वापस __pgprot(PROT_DEVICE_nGnRnE);
पूर्ण

व्योम __iomem *acpi_os_ioremap(acpi_physical_address phys, acpi_size size)
अणु
	efi_memory_desc_t *md, *region = शून्य;
	pgprot_t prot;

	अगर (WARN_ON_ONCE(!efi_enabled(EFI_MEMMAP)))
		वापस शून्य;

	क्रम_each_efi_memory_desc(md) अणु
		u64 end = md->phys_addr + (md->num_pages << EFI_PAGE_SHIFT);

		अगर (phys < md->phys_addr || phys >= end)
			जारी;

		अगर (phys + size > end) अणु
			pr_warn(FW_BUG "requested region covers multiple EFI memory regions\n");
			वापस शून्य;
		पूर्ण
		region = md;
		अवरोध;
	पूर्ण

	/*
	 * It is fine क्रम AML to remap regions that are not represented in the
	 * EFI memory map at all, as it only describes normal memory, and MMIO
	 * regions that require a भव mapping to make them accessible to
	 * the EFI runसमय services.
	 */
	prot = __pgprot(PROT_DEVICE_nGnRnE);
	अगर (region) अणु
		चयन (region->type) अणु
		हाल EFI_LOADER_CODE:
		हाल EFI_LOADER_DATA:
		हाल EFI_BOOT_SERVICES_CODE:
		हाल EFI_BOOT_SERVICES_DATA:
		हाल EFI_CONVENTIONAL_MEMORY:
		हाल EFI_PERSISTENT_MEMORY:
			अगर (memblock_is_map_memory(phys) ||
			    !memblock_is_region_memory(phys, size)) अणु
				pr_warn(FW_BUG "requested region covers kernel memory @ %pa\n", &phys);
				वापस शून्य;
			पूर्ण
			/*
			 * Mapping kernel memory is permitted अगर the region in
			 * question is covered by a single memblock with the
			 * NOMAP attribute set: this enables the use of ACPI
			 * table overrides passed via initramfs, which are
			 * reserved in memory using arch_reserve_mem_area()
			 * below. As this particular use हाल only requires
			 * पढ़ो access, fall through to the R/O mapping हाल.
			 */
			fallthrough;

		हाल EFI_RUNTIME_SERVICES_CODE:
			/*
			 * This would be unusual, but not problematic per se,
			 * as दीर्घ as we take care not to create a writable
			 * mapping क्रम executable code.
			 */
			prot = PAGE_KERNEL_RO;
			अवरोध;

		हाल EFI_ACPI_RECLAIM_MEMORY:
			/*
			 * ACPI reclaim memory is used to pass firmware tables
			 * and other data that is पूर्णांकended क्रम consumption by
			 * the OS only, which may decide it wants to reclaim
			 * that memory and use it क्रम something अन्यथा. We never
			 * करो that, but we usually add it to the linear map
			 * anyway, in which हाल we should use the existing
			 * mapping.
			 */
			अगर (memblock_is_map_memory(phys))
				वापस (व्योम __iomem *)__phys_to_virt(phys);
			fallthrough;

		शेष:
			अगर (region->attribute & EFI_MEMORY_WB)
				prot = PAGE_KERNEL;
			अन्यथा अगर (region->attribute & EFI_MEMORY_WT)
				prot = __pgprot(PROT_NORMAL_WT);
			अन्यथा अगर (region->attribute & EFI_MEMORY_WC)
				prot = __pgprot(PROT_NORMAL_NC);
		पूर्ण
	पूर्ण
	वापस __ioremap(phys, size, prot);
पूर्ण

/*
 * Claim Synchronous External Aborts as a firmware first notअगरication.
 *
 * Used by KVM and the arch करो_sea handler.
 * @regs may be शून्य when called from process context.
 */
पूर्णांक apei_claim_sea(काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = -ENOENT;
	bool वापस_to_irqs_enabled;
	अचिन्हित दीर्घ current_flags;

	अगर (!IS_ENABLED(CONFIG_ACPI_APEI_GHES))
		वापस err;

	current_flags = local_daअगर_save_flags();

	/* current_flags isn't useful here as daif doesn't tell us about pNMI */
	वापस_to_irqs_enabled = !irqs_disabled_flags(arch_local_save_flags());

	अगर (regs)
		वापस_to_irqs_enabled = पूर्णांकerrupts_enabled(regs);

	/*
	 * SEA can पूर्णांकerrupt SError, mask it and describe this as an NMI so
	 * that APEI defers the handling.
	 */
	local_daअगर_restore(DAIF_ERRCTX);
	nmi_enter();
	err = ghes_notअगरy_sea();
	nmi_निकास();

	/*
	 * APEI NMI-like notअगरications are deferred to irq_work. Unless
	 * we पूर्णांकerrupted irqs-masked code, we can करो that now.
	 */
	अगर (!err) अणु
		अगर (वापस_to_irqs_enabled) अणु
			local_daअगर_restore(DAIF_PROCCTX_NOIRQ);
			__irq_enter();
			irq_work_run();
			__irq_निकास();
		पूर्ण अन्यथा अणु
			pr_warn_ratelimited("APEI work queued but not completed");
			err = -EINPROGRESS;
		पूर्ण
	पूर्ण

	local_daअगर_restore(current_flags);

	वापस err;
पूर्ण

व्योम arch_reserve_mem_area(acpi_physical_address addr, माप_प्रकार size)
अणु
	memblock_mark_nomap(addr, size);
पूर्ण
