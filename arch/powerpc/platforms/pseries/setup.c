<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  64-bit pSeries and RS/6000 setup code.
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Adapted from 'alpha' version by Gary Thomas
 *  Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 *  Modअगरied by PPC64 Team, IBM Corp
 */

/*
 * bootup setup stuff..
 */

#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/user.h>
#समावेश <linux/tty.h>
#समावेश <linux/major.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/utsname.h>
#समावेश <linux/adb.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/of.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swiotlb.h>

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/isa-bridge.h>
#समावेश <यंत्र/security_features.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/dtl.h>
#समावेश <यंत्र/hvconsole.h>

#समावेश "pseries.h"
#समावेश "../../../../drivers/pci/pci.h"

DEFINE_STATIC_KEY_FALSE(shared_processor);
EXPORT_SYMBOL_GPL(shared_processor);

पूर्णांक CMO_PrPSP = -1;
पूर्णांक CMO_SecPSP = -1;
अचिन्हित दीर्घ CMO_PageSize = (ASM_CONST(1) << IOMMU_PAGE_SHIFT_4K);
EXPORT_SYMBOL(CMO_PageSize);

पूर्णांक fwnmi_active;  /* TRUE अगर an FWNMI handler is present */
पूर्णांक ibm_nmi_पूर्णांकerlock_token;
u32 pseries_security_flavor;

अटल व्योम pSeries_show_cpuinfo(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model = "";

	root = of_find_node_by_path("/");
	अगर (root)
		model = of_get_property(root, "model", शून्य);
	seq_म_लिखो(m, "machine\t\t: CHRP %s\n", model);
	of_node_put(root);
	अगर (radix_enabled())
		seq_म_लिखो(m, "MMU\t\t: Radix\n");
	अन्यथा
		seq_म_लिखो(m, "MMU\t\t: Hash\n");
पूर्ण

/* Initialize firmware assisted non-maskable पूर्णांकerrupts अगर
 * the firmware supports this feature.
 */
अटल व्योम __init fwnmi_init(व्योम)
अणु
	अचिन्हित दीर्घ प्रणाली_reset_addr, machine_check_addr;
	u8 *mce_data_buf;
	अचिन्हित पूर्णांक i;
	पूर्णांक nr_cpus = num_possible_cpus();
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा slb_entry *slb_ptr;
	माप_प्रकार size;
#पूर्ण_अगर
	पूर्णांक ibm_nmi_रेजिस्टर_token;

	ibm_nmi_रेजिस्टर_token = rtas_token("ibm,nmi-register");
	अगर (ibm_nmi_रेजिस्टर_token == RTAS_UNKNOWN_SERVICE)
		वापस;

	ibm_nmi_पूर्णांकerlock_token = rtas_token("ibm,nmi-interlock");
	अगर (WARN_ON(ibm_nmi_पूर्णांकerlock_token == RTAS_UNKNOWN_SERVICE))
		वापस;

	/* If the kernel's not linked at zero we poपूर्णांक the firmware at low
	 * addresses anyway, and use a trampoline to get to the real code. */
	प्रणाली_reset_addr  = __pa(प्रणाली_reset_fwnmi) - PHYSICAL_START;
	machine_check_addr = __pa(machine_check_fwnmi) - PHYSICAL_START;

	अगर (0 == rtas_call(ibm_nmi_रेजिस्टर_token, 2, 1, शून्य,
			   प्रणाली_reset_addr, machine_check_addr))
		fwnmi_active = 1;

	/*
	 * Allocate a chunk क्रम per cpu buffer to hold rtas errorlog.
	 * It will be used in real mode mce handler, hence it needs to be
	 * below RMA.
	 */
	mce_data_buf = memblock_alloc_try_nid_raw(RTAS_ERROR_LOG_MAX * nr_cpus,
					RTAS_ERROR_LOG_MAX, MEMBLOCK_LOW_LIMIT,
					ppc64_rma_size, NUMA_NO_NODE);
	अगर (!mce_data_buf)
		panic("Failed to allocate %d bytes below %pa for MCE buffer\n",
		      RTAS_ERROR_LOG_MAX * nr_cpus, &ppc64_rma_size);

	क्रम_each_possible_cpu(i) अणु
		paca_ptrs[i]->mce_data_buf = mce_data_buf +
						(RTAS_ERROR_LOG_MAX * i);
	पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (!radix_enabled()) अणु
		/* Allocate per cpu area to save old slb contents during MCE */
		size = माप(काष्ठा slb_entry) * mmu_slb_size * nr_cpus;
		slb_ptr = memblock_alloc_try_nid_raw(size,
				माप(काष्ठा slb_entry), MEMBLOCK_LOW_LIMIT,
				ppc64_rma_size, NUMA_NO_NODE);
		अगर (!slb_ptr)
			panic("Failed to allocate %zu bytes below %pa for slb area\n",
			      size, &ppc64_rma_size);

		क्रम_each_possible_cpu(i)
			paca_ptrs[i]->mce_faulty_slbs = slb_ptr + (mmu_slb_size * i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम pseries_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम __init pseries_setup_i8259_cascade(व्योम)
अणु
	काष्ठा device_node *np, *old, *found = शून्य;
	अचिन्हित पूर्णांक cascade;
	स्थिर u32 *addrp;
	अचिन्हित दीर्घ पूर्णांकack = 0;
	पूर्णांक naddr;

	क्रम_each_node_by_type(np, "interrupt-controller") अणु
		अगर (of_device_is_compatible(np, "chrp,iic")) अणु
			found = np;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "pic: no ISA interrupt controller\n");
		वापस;
	पूर्ण

	cascade = irq_of_parse_and_map(found, 0);
	अगर (!cascade) अणु
		prपूर्णांकk(KERN_ERR "pic: failed to map cascade interrupt");
		वापस;
	पूर्ण
	pr_debug("pic: cascade mapped to irq %d\n", cascade);

	क्रम (old = of_node_get(found); old != शून्य ; old = np) अणु
		np = of_get_parent(old);
		of_node_put(old);
		अगर (np == शून्य)
			अवरोध;
		अगर (!of_node_name_eq(np, "pci"))
			जारी;
		addrp = of_get_property(np, "8259-interrupt-acknowledge", शून्य);
		अगर (addrp == शून्य)
			जारी;
		naddr = of_n_addr_cells(np);
		पूर्णांकack = addrp[naddr-1];
		अगर (naddr > 1)
			पूर्णांकack |= ((अचिन्हित दीर्घ)addrp[naddr-2]) << 32;
	पूर्ण
	अगर (पूर्णांकack)
		prपूर्णांकk(KERN_DEBUG "pic: PCI 8259 intack at 0x%016lx\n", पूर्णांकack);
	i8259_init(found, पूर्णांकack);
	of_node_put(found);
	irq_set_chained_handler(cascade, pseries_8259_cascade);
पूर्ण

अटल व्योम __init pseries_init_irq(व्योम)
अणु
	/* Try using a XIVE अगर available, otherwise use a XICS */
	अगर (!xive_spapr_init()) अणु
		xics_init();
		pseries_setup_i8259_cascade();
	पूर्ण
पूर्ण

अटल व्योम pseries_lpar_enable_pmcs(व्योम)
अणु
	अचिन्हित दीर्घ set, reset;

	set = 1UL << 63;
	reset = 0;
	plpar_hcall_norets(H_PERFMON, set, reset);
पूर्ण

अटल पूर्णांक pci_dn_reconfig_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा of_reconfig_data *rd = data;
	काष्ठा device_node *parent, *np = rd->dn;
	काष्ठा pci_dn *pdn;
	पूर्णांक err = NOTIFY_OK;

	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		parent = of_get_parent(np);
		pdn = parent ? PCI_DN(parent) : शून्य;
		अगर (pdn)
			pci_add_device_node_info(pdn->phb, np);

		of_node_put(parent);
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		pdn = PCI_DN(np);
		अगर (pdn)
			list_del(&pdn->list);
		अवरोध;
	शेष:
		err = NOTIFY_DONE;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा notअगरier_block pci_dn_reconfig_nb = अणु
	.notअगरier_call = pci_dn_reconfig_notअगरier,
पूर्ण;

काष्ठा kmem_cache *dtl_cache;

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
/*
 * Allocate space क्रम the dispatch trace log क्रम all possible cpus
 * and रेजिस्टर the buffers with the hypervisor.  This is used क्रम
 * computing समय stolen by the hypervisor.
 */
अटल पूर्णांक alloc_dispatch_logs(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस 0;

	अगर (!dtl_cache)
		वापस 0;

	alloc_dtl_buffers(0);

	/* Register the DTL क्रम the current (boot) cpu */
	रेजिस्टर_dtl_buffer(smp_processor_id());

	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */
अटल अंतरभूत पूर्णांक alloc_dispatch_logs(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

अटल पूर्णांक alloc_dispatch_log_kmem_cache(व्योम)
अणु
	व्योम (*ctor)(व्योम *) = get_dtl_cache_ctor();

	dtl_cache = kmem_cache_create("dtl", DISPATCH_LOG_BYTES,
						DISPATCH_LOG_BYTES, 0, ctor);
	अगर (!dtl_cache) अणु
		pr_warn("Failed to create dispatch trace log buffer cache\n");
		pr_warn("Stolen time statistics will be unreliable\n");
		वापस 0;
	पूर्ण

	वापस alloc_dispatch_logs();
पूर्ण
machine_early_initcall(pseries, alloc_dispatch_log_kmem_cache);

DEFINE_PER_CPU(u64, idle_spurr_cycles);
DEFINE_PER_CPU(u64, idle_entry_purr_snap);
DEFINE_PER_CPU(u64, idle_entry_spurr_snap);
अटल व्योम pseries_lpar_idle(व्योम)
अणु
	/*
	 * Default handler to go पूर्णांकo low thपढ़ो priority and possibly
	 * low घातer mode by ceding processor to hypervisor
	 */

	अगर (!prep_irq_क्रम_idle())
		वापस;

	/* Indicate to hypervisor that we are idle. */
	pseries_idle_prolog();

	/*
	 * Yield the processor to the hypervisor.  We वापस अगर
	 * an बाह्यal पूर्णांकerrupt occurs (which are driven prior
	 * to वापसing here) or अगर a prod occurs from another
	 * processor. When वापसing here, बाह्यal पूर्णांकerrupts
	 * are enabled.
	 */
	cede_processor();

	pseries_idle_epilog();
पूर्ण

/*
 * Enable relocation on during exceptions. This has partition wide scope and
 * may take a जबतक to complete, अगर it takes दीर्घer than one second we will
 * just give up rather than wasting any more समय on this - अगर that turns out
 * to ever be a problem in practice we can move this पूर्णांकo a kernel thपढ़ो to
 * finish off the process later in boot.
 */
bool pseries_enable_reloc_on_exc(व्योम)
अणु
	दीर्घ rc;
	अचिन्हित पूर्णांक delay, total_delay = 0;

	जबतक (1) अणु
		rc = enable_reloc_on_exceptions();
		अगर (!H_IS_LONG_BUSY(rc)) अणु
			अगर (rc == H_P2) अणु
				pr_info("Relocation on exceptions not"
					" supported\n");
				वापस false;
			पूर्ण अन्यथा अगर (rc != H_SUCCESS) अणु
				pr_warn("Unable to enable relocation"
					" on exceptions: %ld\n", rc);
				वापस false;
			पूर्ण
			वापस true;
		पूर्ण

		delay = get_दीर्घbusy_msecs(rc);
		total_delay += delay;
		अगर (total_delay > 1000) अणु
			pr_warn("Warning: Giving up waiting to enable "
				"relocation on exceptions (%u msec)!\n",
				total_delay);
			वापस false;
		पूर्ण

		mdelay(delay);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pseries_enable_reloc_on_exc);

व्योम pseries_disable_reloc_on_exc(व्योम)
अणु
	दीर्घ rc;

	जबतक (1) अणु
		rc = disable_reloc_on_exceptions();
		अगर (!H_IS_LONG_BUSY(rc))
			अवरोध;
		mdelay(get_दीर्घbusy_msecs(rc));
	पूर्ण
	अगर (rc != H_SUCCESS)
		pr_warn("Warning: Failed to disable relocation on exceptions: %ld\n",
			rc);
पूर्ण
EXPORT_SYMBOL(pseries_disable_reloc_on_exc);

#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम pSeries_machine_kexec(काष्ठा kimage *image)
अणु
	अगर (firmware_has_feature(FW_FEATURE_SET_MODE))
		pseries_disable_reloc_on_exc();

	शेष_machine_kexec(image);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN__
व्योम pseries_big_endian_exceptions(व्योम)
अणु
	दीर्घ rc;

	जबतक (1) अणु
		rc = enable_big_endian_exceptions();
		अगर (!H_IS_LONG_BUSY(rc))
			अवरोध;
		mdelay(get_दीर्घbusy_msecs(rc));
	पूर्ण

	/*
	 * At this poपूर्णांक it is unlikely panic() will get anything
	 * out to the user, since this is called very late in kexec
	 * but at least this will stop us from continuing on further
	 * and creating an even more dअगरficult to debug situation.
	 *
	 * There is a known problem when kdump'ing, अगर cpus are offline
	 * the above call will fail. Rather than panicking again, keep
	 * going and hope the kdump kernel is also little endian, which
	 * it usually is.
	 */
	अगर (rc && !kdump_in_progress())
		panic("Could not enable big endian exceptions");
पूर्ण

व्योम pseries_little_endian_exceptions(व्योम)
अणु
	दीर्घ rc;

	जबतक (1) अणु
		rc = enable_little_endian_exceptions();
		अगर (!H_IS_LONG_BUSY(rc))
			अवरोध;
		mdelay(get_दीर्घbusy_msecs(rc));
	पूर्ण
	अगर (rc) अणु
		ppc_md.progress("H_SET_MODE LE exception fail", 0);
		panic("Could not enable little endian exceptions");
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम __init pSeries_discover_phbs(व्योम)
अणु
	काष्ठा device_node *node;
	काष्ठा pci_controller *phb;
	काष्ठा device_node *root = of_find_node_by_path("/");

	क्रम_each_child_of_node(root, node) अणु
		अगर (!of_node_is_type(node, "pci") &&
		    !of_node_is_type(node, "pciex"))
			जारी;

		phb = pcibios_alloc_controller(node);
		अगर (!phb)
			जारी;
		rtas_setup_phb(phb);
		pci_process_bridge_OF_ranges(phb, node, 0);
		isa_bridge_find_early(phb);
		phb->controller_ops = pseries_pci_controller_ops;

		/* create pci_dn's क्रम DT nodes under this PHB */
		pci_devs_phb_init_dynamic(phb);
	पूर्ण

	of_node_put(root);

	/*
	 * PCI_PROBE_ONLY and PCI_REASSIGN_ALL_BUS can be set via properties
	 * in chosen.
	 */
	of_pci_check_probe_only();
पूर्ण

अटल व्योम init_cpu_अक्षर_feature_flags(काष्ठा h_cpu_अक्षर_result *result)
अणु
	/*
	 * The features below are disabled by शेष, so we instead look to see
	 * अगर firmware has *enabled* them, and set them अगर so.
	 */
	अगर (result->अक्षरacter & H_CPU_CHAR_SPEC_BAR_ORI31)
		security_ftr_set(SEC_FTR_SPEC_BAR_ORI31);

	अगर (result->अक्षरacter & H_CPU_CHAR_BCCTRL_SERIALISED)
		security_ftr_set(SEC_FTR_BCCTRL_SERIALISED);

	अगर (result->अक्षरacter & H_CPU_CHAR_L1D_FLUSH_ORI30)
		security_ftr_set(SEC_FTR_L1D_FLUSH_ORI30);

	अगर (result->अक्षरacter & H_CPU_CHAR_L1D_FLUSH_TRIG2)
		security_ftr_set(SEC_FTR_L1D_FLUSH_TRIG2);

	अगर (result->अक्षरacter & H_CPU_CHAR_L1D_THREAD_PRIV)
		security_ftr_set(SEC_FTR_L1D_THREAD_PRIV);

	अगर (result->अक्षरacter & H_CPU_CHAR_COUNT_CACHE_DISABLED)
		security_ftr_set(SEC_FTR_COUNT_CACHE_DISABLED);

	अगर (result->अक्षरacter & H_CPU_CHAR_BCCTR_FLUSH_ASSIST)
		security_ftr_set(SEC_FTR_BCCTR_FLUSH_ASSIST);

	अगर (result->अक्षरacter & H_CPU_CHAR_BCCTR_LINK_FLUSH_ASSIST)
		security_ftr_set(SEC_FTR_BCCTR_LINK_FLUSH_ASSIST);

	अगर (result->behaviour & H_CPU_BEHAV_FLUSH_COUNT_CACHE)
		security_ftr_set(SEC_FTR_FLUSH_COUNT_CACHE);

	अगर (result->behaviour & H_CPU_BEHAV_FLUSH_LINK_STACK)
		security_ftr_set(SEC_FTR_FLUSH_LINK_STACK);

	/*
	 * The features below are enabled by शेष, so we instead look to see
	 * अगर firmware has *disabled* them, and clear them अगर so.
	 * H_CPU_BEHAV_FAVOUR_SECURITY_H could be set only अगर
	 * H_CPU_BEHAV_FAVOUR_SECURITY is.
	 */
	अगर (!(result->behaviour & H_CPU_BEHAV_FAVOUR_SECURITY))
		security_ftr_clear(SEC_FTR_FAVOUR_SECURITY);
	अन्यथा अगर (result->behaviour & H_CPU_BEHAV_FAVOUR_SECURITY_H)
		pseries_security_flavor = 1;
	अन्यथा
		pseries_security_flavor = 2;

	अगर (!(result->behaviour & H_CPU_BEHAV_L1D_FLUSH_PR))
		security_ftr_clear(SEC_FTR_L1D_FLUSH_PR);

	अगर (!(result->behaviour & H_CPU_BEHAV_BNDS_CHK_SPEC_BAR))
		security_ftr_clear(SEC_FTR_BNDS_CHK_SPEC_BAR);
पूर्ण

व्योम pseries_setup_security_mitigations(व्योम)
अणु
	काष्ठा h_cpu_अक्षर_result result;
	क्रमागत l1d_flush_type types;
	bool enable;
	दीर्घ rc;

	/*
	 * Set features to the शेषs assumed by init_cpu_अक्षर_feature_flags()
	 * so it can set/clear again any features that might have changed after
	 * migration, and in हाल the hypercall fails and it is not even called.
	 */
	घातerpc_security_features = SEC_FTR_DEFAULT;

	rc = plpar_get_cpu_अक्षरacteristics(&result);
	अगर (rc == H_SUCCESS)
		init_cpu_अक्षर_feature_flags(&result);

	/*
	 * We're the guest so this doesn't apply to us, clear it to simplअगरy
	 * handling of it अन्यथाwhere.
	 */
	security_ftr_clear(SEC_FTR_L1D_FLUSH_HV);

	types = L1D_FLUSH_FALLBACK;

	अगर (security_ftr_enabled(SEC_FTR_L1D_FLUSH_TRIG2))
		types |= L1D_FLUSH_MTTRIG;

	अगर (security_ftr_enabled(SEC_FTR_L1D_FLUSH_ORI30))
		types |= L1D_FLUSH_ORI;

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) && \
		 security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR);

	setup_rfi_flush(types, enable);
	setup_count_cache_flush();

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_L1D_FLUSH_ENTRY);
	setup_entry_flush(enable);

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_L1D_FLUSH_UACCESS);
	setup_uaccess_flush(enable);

	setup_stf_barrier();
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
क्रमागत rtas_iov_fw_value_map अणु
	NUM_RES_PROPERTY  = 0, /* Number of Resources */
	LOW_INT           = 1, /* Lowest 32 bits of Address */
	START_OF_ENTRIES  = 2, /* Always start of entry */
	APERTURE_PROPERTY = 2, /* Start of entry+ to  Aperture Size */
	WDW_SIZE_PROPERTY = 4, /* Start of entry+ to Winकरोw Size */
	NEXT_ENTRY        = 7  /* Go to next entry on array */
पूर्ण;

क्रमागत get_iov_fw_value_index अणु
	BAR_ADDRS     = 1,    /*  Get Bar Address */
	APERTURE_SIZE = 2,    /*  Get Aperture Size */
	WDW_SIZE      = 3     /*  Get Winकरोw Size */
पूर्ण;

अटल resource_माप_प्रकार pseries_get_iov_fw_value(काष्ठा pci_dev *dev, पूर्णांक resno,
						क्रमागत get_iov_fw_value_index value)
अणु
	स्थिर पूर्णांक *indexes;
	काष्ठा device_node *dn = pci_device_to_OF_node(dev);
	पूर्णांक i, num_res, ret = 0;

	indexes = of_get_property(dn, "ibm,open-sriov-vf-bar-info", शून्य);
	अगर (!indexes)
		वापस  0;

	/*
	 * First element in the array is the number of Bars
	 * वापसed.  Search through the list to find the matching
	 * bar
	 */
	num_res = of_पढ़ो_number(&indexes[NUM_RES_PROPERTY], 1);
	अगर (resno >= num_res)
		वापस 0; /* or an errror */

	i = START_OF_ENTRIES + NEXT_ENTRY * resno;
	चयन (value) अणु
	हाल BAR_ADDRS:
		ret = of_पढ़ो_number(&indexes[i], 2);
		अवरोध;
	हाल APERTURE_SIZE:
		ret = of_पढ़ो_number(&indexes[i + APERTURE_PROPERTY], 2);
		अवरोध;
	हाल WDW_SIZE:
		ret = of_पढ़ो_number(&indexes[i + WDW_SIZE_PROPERTY], 2);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम of_pci_set_vf_bar_size(काष्ठा pci_dev *dev, स्थिर पूर्णांक *indexes)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार base, size;
	पूर्णांक i, r, num_res;

	num_res = of_पढ़ो_number(&indexes[NUM_RES_PROPERTY], 1);
	num_res = min_t(पूर्णांक, num_res, PCI_SRIOV_NUM_BARS);
	क्रम (i = START_OF_ENTRIES, r = 0; r < num_res && r < PCI_SRIOV_NUM_BARS;
	     i += NEXT_ENTRY, r++) अणु
		res = &dev->resource[r + PCI_IOV_RESOURCES];
		base = of_पढ़ो_number(&indexes[i], 2);
		size = of_पढ़ो_number(&indexes[i + APERTURE_PROPERTY], 2);
		res->flags = pci_parse_of_flags(of_पढ़ो_number
						(&indexes[i + LOW_INT], 1), 0);
		res->flags |= (IORESOURCE_MEM_64 | IORESOURCE_PCI_FIXED);
		res->name = pci_name(dev);
		res->start = base;
		res->end = base + size - 1;
	पूर्ण
पूर्ण

अटल व्योम of_pci_parse_iov_addrs(काष्ठा pci_dev *dev, स्थिर पूर्णांक *indexes)
अणु
	काष्ठा resource *res, *root, *conflict;
	resource_माप_प्रकार base, size;
	पूर्णांक i, r, num_res;

	/*
	 * First element in the array is the number of Bars
	 * वापसed.  Search through the list to find the matching
	 * bars assign them from firmware पूर्णांकo resources काष्ठाure.
	 */
	num_res = of_पढ़ो_number(&indexes[NUM_RES_PROPERTY], 1);
	क्रम (i = START_OF_ENTRIES, r = 0; r < num_res && r < PCI_SRIOV_NUM_BARS;
	     i += NEXT_ENTRY, r++) अणु
		res = &dev->resource[r + PCI_IOV_RESOURCES];
		base = of_पढ़ो_number(&indexes[i], 2);
		size = of_पढ़ो_number(&indexes[i + WDW_SIZE_PROPERTY], 2);
		res->name = pci_name(dev);
		res->start = base;
		res->end = base + size - 1;
		root = &iomem_resource;
		dev_dbg(&dev->dev,
			"pSeries IOV BAR %d: trying firmware assignment %pR\n",
			 r + PCI_IOV_RESOURCES, res);
		conflict = request_resource_conflict(root, res);
		अगर (conflict) अणु
			dev_info(&dev->dev,
				 "BAR %d: %pR conflicts with %s %pR\n",
				 r + PCI_IOV_RESOURCES, res,
				 conflict->name, conflict);
			res->flags |= IORESOURCE_UNSET;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pseries_disable_sriov_resources(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	pci_warn(pdev, "No hypervisor support for SR-IOV on this device, IOV BARs disabled.\n");
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++)
		pdev->resource[i + PCI_IOV_RESOURCES].flags = 0;
पूर्ण

अटल व्योम pseries_pci_fixup_resources(काष्ठा pci_dev *pdev)
अणु
	स्थिर पूर्णांक *indexes;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);

	/*Firmware must support खोलो sriov otherwise करोnt configure*/
	indexes = of_get_property(dn, "ibm,open-sriov-vf-bar-info", शून्य);
	अगर (indexes)
		of_pci_set_vf_bar_size(pdev, indexes);
	अन्यथा
		pseries_disable_sriov_resources(pdev);
पूर्ण

अटल व्योम pseries_pci_fixup_iov_resources(काष्ठा pci_dev *pdev)
अणु
	स्थिर पूर्णांक *indexes;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);

	अगर (!pdev->is_physfn || pci_dev_is_added(pdev))
		वापस;
	/*Firmware must support खोलो sriov otherwise करोnt configure*/
	indexes = of_get_property(dn, "ibm,open-sriov-vf-bar-info", शून्य);
	अगर (indexes)
		of_pci_parse_iov_addrs(pdev, indexes);
	अन्यथा
		pseries_disable_sriov_resources(pdev);
पूर्ण

अटल resource_माप_प्रकार pseries_pci_iov_resource_alignment(काष्ठा pci_dev *pdev,
							  पूर्णांक resno)
अणु
	स्थिर __be32 *reg;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);

	/*Firmware must support खोलो sriov otherwise report regular alignment*/
	reg = of_get_property(dn, "ibm,is-open-sriov-pf", शून्य);
	अगर (!reg)
		वापस pci_iov_resource_size(pdev, resno);

	अगर (!pdev->is_physfn)
		वापस 0;
	वापस pseries_get_iov_fw_value(pdev,
					resno - PCI_IOV_RESOURCES,
					APERTURE_SIZE);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init pSeries_setup_arch(व्योम)
अणु
	set_arch_panic_समयout(10, ARCH_PANIC_TIMEOUT);

	/* Discover PIC type and setup ppc_md accordingly */
	smp_init_pseries();


	अगर (radix_enabled() && !mmu_has_feature(MMU_FTR_GTSE))
		अगर (!firmware_has_feature(FW_FEATURE_RPT_INVALIDATE))
			panic("BUG: Radix support requires either GTSE or RPT_INVALIDATE\n");


	/* खोलोpic global configuration रेजिस्टर (64-bit क्रमmat). */
	/* खोलोpic Interrupt Source Unit poपूर्णांकer (64-bit क्रमmat). */
	/* python0 facility area (mmio) (64-bit क्रमmat) REAL address. */

	/* init to some ~sane value until calibrate_delay() runs */
	loops_per_jअगरfy = 50000000;

	fwnmi_init();

	pseries_setup_security_mitigations();
	pseries_lpar_पढ़ो_hblkrm_अक्षरacteristics();

	/* By शेष, only probe PCI (can be overridden by rtas_pci) */
	pci_add_flags(PCI_PROBE_ONLY);

	/* Find and initialize PCI host bridges */
	init_pci_config_tokens();
	of_reconfig_notअगरier_रेजिस्टर(&pci_dn_reconfig_nb);

	pSeries_nvram_init();

	अगर (firmware_has_feature(FW_FEATURE_LPAR)) अणु
		vpa_init(boot_cpuid);

		अगर (lppaca_shared_proc(get_lppaca())) अणु
			अटल_branch_enable(&shared_processor);
			pv_spinlocks_init();
		पूर्ण

		ppc_md.घातer_save = pseries_lpar_idle;
		ppc_md.enable_pmcs = pseries_lpar_enable_pmcs;
#अगर_घोषित CONFIG_PCI_IOV
		ppc_md.pcibios_fixup_resources =
			pseries_pci_fixup_resources;
		ppc_md.pcibios_fixup_sriov =
			pseries_pci_fixup_iov_resources;
		ppc_md.pcibios_iov_resource_alignment =
			pseries_pci_iov_resource_alignment;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* No special idle routine */
		ppc_md.enable_pmcs = घातer4_enable_pmcs;
	पूर्ण

	ppc_md.pcibios_root_bridge_prepare = pseries_root_bridge_prepare;

	अगर (swiotlb_क्रमce == SWIOTLB_FORCE)
		ppc_swiotlb_enable = 1;
पूर्ण

अटल व्योम pseries_panic(अक्षर *str)
अणु
	panic_flush_kmsg_end();
	rtas_os_term(str);
पूर्ण

अटल पूर्णांक __init pSeries_init_panel(व्योम)
अणु
	/* Manually leave the kernel version on the panel. */
#अगर_घोषित __BIG_ENDIAN__
	ppc_md.progress("Linux ppc64\n", 0);
#अन्यथा
	ppc_md.progress("Linux ppc64le\n", 0);
#पूर्ण_अगर
	ppc_md.progress(init_utsname()->version, 0);

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, pSeries_init_panel);

अटल पूर्णांक pseries_set_dabr(अचिन्हित दीर्घ dabr, अचिन्हित दीर्घ dabrx)
अणु
	वापस plpar_hcall_norets(H_SET_DABR, dabr);
पूर्ण

अटल पूर्णांक pseries_set_xdabr(अचिन्हित दीर्घ dabr, अचिन्हित दीर्घ dabrx)
अणु
	/* Have to set at least one bit in the DABRX according to PAPR */
	अगर (dabrx == 0 && dabr == 0)
		dabrx = DABRX_USER;
	/* PAPR says we can only set kernel and user bits */
	dabrx &= DABRX_KERNEL | DABRX_USER;

	वापस plpar_hcall_norets(H_SET_XDABR, dabr, dabrx);
पूर्ण

अटल पूर्णांक pseries_set_dawr(पूर्णांक nr, अचिन्हित दीर्घ dawr, अचिन्हित दीर्घ dawrx)
अणु
	/* PAPR says we can't set HYP */
	dawrx &= ~DAWRX_HYP;

	अगर (nr == 0)
		वापस plpar_set_watchpoपूर्णांक0(dawr, dawrx);
	अन्यथा
		वापस plpar_set_watchpoपूर्णांक1(dawr, dawrx);
पूर्ण

#घोषणा CMO_CHARACTERISTICS_TOKEN 44
#घोषणा CMO_MAXLENGTH 1026

व्योम pSeries_coalesce_init(व्योम)
अणु
	काष्ठा hvcall_mpp_x_data mpp_x_data;

	अगर (firmware_has_feature(FW_FEATURE_CMO) && !h_get_mpp_x(&mpp_x_data))
		घातerpc_firmware_features |= FW_FEATURE_XCMO;
	अन्यथा
		घातerpc_firmware_features &= ~FW_FEATURE_XCMO;
पूर्ण

/**
 * fw_cmo_feature_init - FW_FEATURE_CMO is not stored in ibm,hypertas-functions,
 * handle that here. (Stolen from parse_प्रणाली_parameter_string)
 */
अटल व्योम pSeries_cmo_feature_init(व्योम)
अणु
	अक्षर *ptr, *key, *value, *end;
	पूर्णांक call_status;
	पूर्णांक page_order = IOMMU_PAGE_SHIFT_4K;

	pr_debug(" -> fw_cmo_feature_init()\n");
	spin_lock(&rtas_data_buf_lock);
	स_रखो(rtas_data_buf, 0, RTAS_DATA_BUF_SIZE);
	call_status = rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
				शून्य,
				CMO_CHARACTERISTICS_TOKEN,
				__pa(rtas_data_buf),
				RTAS_DATA_BUF_SIZE);

	अगर (call_status != 0) अणु
		spin_unlock(&rtas_data_buf_lock);
		pr_debug("CMO not available\n");
		pr_debug(" <- fw_cmo_feature_init()\n");
		वापस;
	पूर्ण

	end = rtas_data_buf + CMO_MAXLENGTH - 2;
	ptr = rtas_data_buf + 2;	/* step over म_माप value */
	key = value = ptr;

	जबतक (*ptr && (ptr <= end)) अणु
		/* Separate the key and value by replacing '=' with '\0' and
		 * poपूर्णांक the value at the string after the '='
		 */
		अगर (ptr[0] == '=') अणु
			ptr[0] = '\0';
			value = ptr + 1;
		पूर्ण अन्यथा अगर (ptr[0] == '\0' || ptr[0] == ',') अणु
			/* Terminate the string containing the key/value pair */
			ptr[0] = '\0';

			अगर (key == value) अणु
				pr_debug("Malformed key/value pair\n");
				/* Never found a '=', end processing */
				अवरोध;
			पूर्ण

			अगर (0 == म_भेद(key, "CMOPageSize"))
				page_order = simple_म_से_दीर्घ(value, शून्य, 10);
			अन्यथा अगर (0 == म_भेद(key, "PrPSP"))
				CMO_PrPSP = simple_म_से_दीर्घ(value, शून्य, 10);
			अन्यथा अगर (0 == म_भेद(key, "SecPSP"))
				CMO_SecPSP = simple_म_से_दीर्घ(value, शून्य, 10);
			value = key = ptr + 1;
		पूर्ण
		ptr++;
	पूर्ण

	/* Page size is वापसed as the घातer of 2 of the page size,
	 * convert to the page size in bytes beक्रमe वापसing
	 */
	CMO_PageSize = 1 << page_order;
	pr_debug("CMO_PageSize = %lu\n", CMO_PageSize);

	अगर (CMO_PrPSP != -1 || CMO_SecPSP != -1) अणु
		pr_info("CMO enabled\n");
		pr_debug("CMO enabled, PrPSP=%d, SecPSP=%d\n", CMO_PrPSP,
		         CMO_SecPSP);
		घातerpc_firmware_features |= FW_FEATURE_CMO;
		pSeries_coalesce_init();
	पूर्ण अन्यथा
		pr_debug("CMO not enabled, PrPSP=%d, SecPSP=%d\n", CMO_PrPSP,
		         CMO_SecPSP);
	spin_unlock(&rtas_data_buf_lock);
	pr_debug(" <- fw_cmo_feature_init()\n");
पूर्ण

/*
 * Early initialization.  Relocation is on but करो not reference unbolted pages
 */
अटल व्योम __init pseries_init(व्योम)
अणु
	pr_debug(" -> pseries_init()\n");

#अगर_घोषित CONFIG_HVC_CONSOLE
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		hvc_vio_init_early();
#पूर्ण_अगर
	अगर (firmware_has_feature(FW_FEATURE_XDABR))
		ppc_md.set_dabr = pseries_set_xdabr;
	अन्यथा अगर (firmware_has_feature(FW_FEATURE_DABR))
		ppc_md.set_dabr = pseries_set_dabr;

	अगर (firmware_has_feature(FW_FEATURE_SET_MODE))
		ppc_md.set_dawr = pseries_set_dawr;

	pSeries_cmo_feature_init();
	iommu_init_early_pSeries();

	pr_debug(" <- pseries_init()\n");
पूर्ण

/**
 * pseries_घातer_off - tell firmware about how to घातer off the प्रणाली.
 *
 * This function calls either the घातer-off rtas token in normal हालs
 * or the ibm,घातer-off-ups token (अगर present & requested) in हाल of
 * a घातer failure. If घातer-off token is used, घातer on will only be
 * possible with घातer button press. If ibm,घातer-off-ups token is used
 * it will allow स्वतः घातeron after घातer is restored.
 */
अटल व्योम pseries_घातer_off(व्योम)
अणु
	पूर्णांक rc;
	पूर्णांक rtas_घातeroff_ups_token = rtas_token("ibm,power-off-ups");

	अगर (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_POWER_OFF);

	अगर (rtas_घातeron_स्वतः == 0 ||
		rtas_घातeroff_ups_token == RTAS_UNKNOWN_SERVICE) अणु
		rc = rtas_call(rtas_token("power-off"), 2, 1, शून्य, -1, -1);
		prपूर्णांकk(KERN_INFO "RTAS power-off returned %d\n", rc);
	पूर्ण अन्यथा अणु
		rc = rtas_call(rtas_घातeroff_ups_token, 0, 1, शून्य);
		prपूर्णांकk(KERN_INFO "RTAS ibm,power-off-ups returned %d\n", rc);
	पूर्ण
	क्रम (;;);
पूर्ण

अटल पूर्णांक __init pSeries_probe(व्योम)
अणु
	अगर (!of_node_is_type(of_root, "chrp"))
		वापस 0;

	/* Cell blades firmware claims to be chrp जबतक it's not. Until this
	 * is fixed, we need to aव्योम those here.
	 */
	अगर (of_machine_is_compatible("IBM,CPBW-1.0") ||
	    of_machine_is_compatible("IBM,CBEA"))
		वापस 0;

	pm_घातer_off = pseries_घातer_off;

	pr_debug("Machine is%s LPAR !\n",
	         (घातerpc_firmware_features & FW_FEATURE_LPAR) ? "" : " not");

	pseries_init();

	वापस 1;
पूर्ण

अटल पूर्णांक pSeries_pci_probe_mode(काष्ठा pci_bus *bus)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		वापस PCI_PROBE_DEVTREE;
	वापस PCI_PROBE_NORMAL;
पूर्ण

काष्ठा pci_controller_ops pseries_pci_controller_ops = अणु
	.probe_mode		= pSeries_pci_probe_mode,
पूर्ण;

define_machine(pseries) अणु
	.name			= "pSeries",
	.probe			= pSeries_probe,
	.setup_arch		= pSeries_setup_arch,
	.init_IRQ		= pseries_init_irq,
	.show_cpuinfo		= pSeries_show_cpuinfo,
	.log_error		= pSeries_log_error,
	.discover_phbs		= pSeries_discover_phbs,
	.pcibios_fixup		= pSeries_final_fixup,
	.restart		= rtas_restart,
	.halt			= rtas_halt,
	.panic			= pseries_panic,
	.get_boot_समय		= rtas_get_boot_समय,
	.get_rtc_समय		= rtas_get_rtc_समय,
	.set_rtc_समय		= rtas_set_rtc_समय,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= rtas_progress,
	.प्रणाली_reset_exception = pSeries_प्रणाली_reset_exception,
	.machine_check_early	= pseries_machine_check_realmode,
	.machine_check_exception = pSeries_machine_check_exception,
#अगर_घोषित CONFIG_KEXEC_CORE
	.machine_kexec          = pSeries_machine_kexec,
	.kexec_cpu_करोwn         = pseries_kexec_cpu_करोwn,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
	.memory_block_size	= pseries_memory_block_size,
#पूर्ण_अगर
पूर्ण;
