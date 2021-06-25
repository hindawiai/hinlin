<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_MACHDEP_H
#घोषणा _ASM_POWERPC_MACHDEP_H
#अगर_घोषित __KERNEL__

#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/setup.h>

/* We export this macro क्रम बाह्यal modules like Alsa to know अगर
 * ppc_md.feature_call is implemented or not
 */
#घोषणा CONFIG_PPC_HAS_FEATURE_CALLS

काष्ठा pt_regs;
काष्ठा pci_bus;	
काष्ठा device_node;
काष्ठा iommu_table;
काष्ठा rtc_समय;
काष्ठा file;
काष्ठा pci_controller;
काष्ठा kimage;
काष्ठा pci_host_bridge;

काष्ठा machdep_calls अणु
	अक्षर		*name;
#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_PM
	व्योम		(*iommu_save)(व्योम);
	व्योम		(*iommu_restore)(व्योम);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
	अचिन्हित दीर्घ	(*memory_block_size)(व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC64 */

	व्योम		(*dma_set_mask)(काष्ठा device *dev, u64 dma_mask);

	पूर्णांक		(*probe)(व्योम);
	व्योम		(*setup_arch)(व्योम); /* Optional, may be शून्य */
	/* Optional, may be शून्य. */
	व्योम		(*show_cpuinfo)(काष्ठा seq_file *m);
	व्योम		(*show_percpuinfo)(काष्ठा seq_file *m, पूर्णांक i);
	/* Returns the current operating frequency of "cpu" in Hz */
	अचिन्हित दीर्घ  	(*get_proc_freq)(अचिन्हित पूर्णांक cpu);

	व्योम		(*init_IRQ)(व्योम);

	/* Return an irq, or 0 to indicate there are none pending. */
	अचिन्हित पूर्णांक	(*get_irq)(व्योम);

	/* PCI stuff */
	/* Called after allocating resources */
	व्योम		(*pcibios_fixup)(व्योम);
	व्योम		(*pci_irq_fixup)(काष्ठा pci_dev *dev);
	पूर्णांक		(*pcibios_root_bridge_prepare)(काष्ठा pci_host_bridge
				*bridge);

	/* finds all the pci_controllers present at boot */
	व्योम 		(*discover_phbs)(व्योम);

	/* To setup PHBs when using स्वतःmatic OF platक्रमm driver क्रम PCI */
	पूर्णांक		(*pci_setup_phb)(काष्ठा pci_controller *host);

	व्योम __noवापस	(*restart)(अक्षर *cmd);
	व्योम __noवापस (*halt)(व्योम);
	व्योम		(*panic)(अक्षर *str);

	दीर्घ		(*समय_init)(व्योम); /* Optional, may be शून्य */

	पूर्णांक		(*set_rtc_समय)(काष्ठा rtc_समय *);
	व्योम		(*get_rtc_समय)(काष्ठा rtc_समय *);
	समय64_t	(*get_boot_समय)(व्योम);
	अचिन्हित अक्षर 	(*rtc_पढ़ो_val)(पूर्णांक addr);
	व्योम		(*rtc_ग_लिखो_val)(पूर्णांक addr, अचिन्हित अक्षर val);

	व्योम		(*calibrate_decr)(व्योम);

	व्योम		(*progress)(अक्षर *, अचिन्हित लघु);

	/* Interface क्रम platक्रमm error logging */
	व्योम 		(*log_error)(अक्षर *buf, अचिन्हित पूर्णांक err_type, पूर्णांक fatal);

	अचिन्हित अक्षर 	(*nvram_पढ़ो_val)(पूर्णांक addr);
	व्योम		(*nvram_ग_लिखो_val)(पूर्णांक addr, अचिन्हित अक्षर val);
	sमाप_प्रकार		(*nvram_ग_लिखो)(अक्षर *buf, माप_प्रकार count, loff_t *index);
	sमाप_प्रकार		(*nvram_पढ़ो)(अक्षर *buf, माप_प्रकार count, loff_t *index);	
	sमाप_प्रकार		(*nvram_size)(व्योम);		
	व्योम		(*nvram_sync)(व्योम);

	/* Exception handlers */
	पूर्णांक		(*प्रणाली_reset_exception)(काष्ठा pt_regs *regs);
	पूर्णांक 		(*machine_check_exception)(काष्ठा pt_regs *regs);
	पूर्णांक		(*handle_hmi_exception)(काष्ठा pt_regs *regs);

	/* Early exception handlers called in realmode */
	पूर्णांक		(*hmi_exception_early)(काष्ठा pt_regs *regs);
	दीर्घ		(*machine_check_early)(काष्ठा pt_regs *regs);

	/* Called during machine check exception to retrive fixup address. */
	bool		(*mce_check_early_recovery)(काष्ठा pt_regs *regs);

	/* Motherboard/chipset features. This is a kind of general purpose
	 * hook used to control some machine specअगरic features (like reset
	 * lines, chip घातer control, etc...).
	 */
	दीर्घ	 	(*feature_call)(अचिन्हित पूर्णांक feature, ...);

	/* Get legacy PCI/IDE पूर्णांकerrupt mapping */ 
	पूर्णांक		(*pci_get_legacy_ide_irq)(काष्ठा pci_dev *dev, पूर्णांक channel);
	
	/* Get access protection क्रम /dev/mem */
	pgprot_t	(*phys_mem_access_prot)(काष्ठा file *file,
						अचिन्हित दीर्घ pfn,
						अचिन्हित दीर्घ size,
						pgprot_t vma_prot);

	/*
	 * Function क्रम रुकोing क्रम work with reduced घातer in idle loop;
	 * called with पूर्णांकerrupts disabled.
	 */
	व्योम		(*घातer_save)(व्योम);

	/* Function to enable perक्रमmance monitor counters क्रम this
	   platक्रमm, called once per cpu. */
	व्योम		(*enable_pmcs)(व्योम);

	/* Set DABR क्रम this platक्रमm, leave empty क्रम शेष implementation */
	पूर्णांक		(*set_dabr)(अचिन्हित दीर्घ dabr,
				    अचिन्हित दीर्घ dabrx);

	/* Set DAWR क्रम this platक्रमm, leave empty क्रम शेष implementation */
	पूर्णांक		(*set_dawr)(पूर्णांक nr, अचिन्हित दीर्घ dawr,
				    अचिन्हित दीर्घ dawrx);

#अगर_घोषित CONFIG_PPC32	/* XXX क्रम now */
	/* A general init function, called by ppc_init in init/मुख्य.c.
	   May be शून्य. */
	व्योम		(*init)(व्योम);

	व्योम		(*kgdb_map_scc)(व्योम);

	/*
	 * optional PCI "hooks"
	 */
	/* Called at then very end of pcibios_init() */
	व्योम (*pcibios_after_init)(व्योम);

#पूर्ण_अगर /* CONFIG_PPC32 */

	/* Called in indirect_* to aव्योम touching devices */
	पूर्णांक (*pci_exclude_device)(काष्ठा pci_controller *, अचिन्हित अक्षर, अचिन्हित अक्षर);

	/* Called after PPC generic resource fixup to perक्रमm
	   machine specअगरic fixups */
	व्योम (*pcibios_fixup_resources)(काष्ठा pci_dev *);

	/* Called क्रम each PCI bus in the प्रणाली when it's probed */
	व्योम (*pcibios_fixup_bus)(काष्ठा pci_bus *);

	/* Called after scan and beक्रमe resource survey */
	व्योम (*pcibios_fixup_phb)(काष्ठा pci_controller *hose);

	/*
	 * Called after device has been added to bus and
	 * beक्रमe sysfs has been created.
	 */
	व्योम (*pcibios_bus_add_device)(काष्ठा pci_dev *pdev);

	resource_माप_प्रकार (*pcibios_शेष_alignment)(व्योम);

#अगर_घोषित CONFIG_PCI_IOV
	व्योम (*pcibios_fixup_sriov)(काष्ठा pci_dev *pdev);
	resource_माप_प्रकार (*pcibios_iov_resource_alignment)(काष्ठा pci_dev *, पूर्णांक resno);
	पूर्णांक (*pcibios_sriov_enable)(काष्ठा pci_dev *pdev, u16 num_vfs);
	पूर्णांक (*pcibios_sriov_disable)(काष्ठा pci_dev *pdev);
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	/* Called to shutकरोwn machine specअगरic hardware not alपढ़ोy controlled
	 * by other drivers.
	 */
	व्योम (*machine_shutकरोwn)(व्योम);

#अगर_घोषित CONFIG_KEXEC_CORE
	व्योम (*kexec_cpu_करोwn)(पूर्णांक crash_shutकरोwn, पूर्णांक secondary);

	/* Called to करो what every setup is needed on image and the
	 * reboot code buffer. Returns 0 on success.
	 * Provide your own (maybe dummy) implementation अगर your platक्रमm
	 * claims to support kexec.
	 */
	पूर्णांक (*machine_kexec_prepare)(काष्ठा kimage *image);

	/* Called to perक्रमm the _real_ kexec.
	 * Do NOT allocate memory or fail here. We are past the poपूर्णांक of
	 * no वापस.
	 */
	व्योम (*machine_kexec)(काष्ठा kimage *image);
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_SUSPEND
	/* These are called to disable and enable, respectively, IRQs when
	 * entering a suspend state.  If शून्य, then the generic versions
	 * will be called.  The generic versions disable/enable the
	 * decrementer aदीर्घ with पूर्णांकerrupts.
	 */
	व्योम (*suspend_disable_irqs)(व्योम);
	व्योम (*suspend_enable_irqs)(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE
	sमाप_प्रकार (*cpu_probe)(स्थिर अक्षर *, माप_प्रकार);
	sमाप_प्रकार (*cpu_release)(स्थिर अक्षर *, माप_प्रकार);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_RANDOM
	पूर्णांक (*get_अक्रमom_seed)(अचिन्हित दीर्घ *v);
#पूर्ण_अगर
पूर्ण;

बाह्य व्योम e500_idle(व्योम);
बाह्य व्योम घातer4_idle(व्योम);
बाह्य व्योम ppc6xx_idle(व्योम);
बाह्य व्योम book3e_idle(व्योम);

/*
 * ppc_md contains a copy of the machine description काष्ठाure क्रम the
 * current platक्रमm. machine_id contains the initial address where the
 * description was found during boot.
 */
बाह्य काष्ठा machdep_calls ppc_md;
बाह्य काष्ठा machdep_calls *machine_id;

#घोषणा __machine_desc __section(".machine.desc")

#घोषणा define_machine(name)					\
	बाह्य काष्ठा machdep_calls mach_##name;		\
	EXPORT_SYMBOL(mach_##name);				\
	काष्ठा machdep_calls mach_##name __machine_desc =

#घोषणा machine_is(name) \
	(अणु \
		बाह्य काष्ठा machdep_calls mach_##name \
			__attribute__((weak));		 \
		machine_id == &mach_##name; \
	पूर्ण)

बाह्य व्योम probe_machine(व्योम);

#अगर_घोषित CONFIG_PPC_PMAC
/*
 * Power macपूर्णांकoshes have either a CUDA, PMU or SMU controlling
 * प्रणाली reset, घातer, NVRAM, RTC.
 */
प्रकार क्रमागत sys_ctrler_kind अणु
	SYS_CTRLER_UNKNOWN = 0,
	SYS_CTRLER_CUDA = 1,
	SYS_CTRLER_PMU = 2,
	SYS_CTRLER_SMU = 3,
पूर्ण sys_ctrler_t;
बाह्य sys_ctrler_t sys_ctrler;

#पूर्ण_अगर /* CONFIG_PPC_PMAC */

अटल अंतरभूत व्योम log_error(अक्षर *buf, अचिन्हित पूर्णांक err_type, पूर्णांक fatal)
अणु
	अगर (ppc_md.log_error)
		ppc_md.log_error(buf, err_type, fatal);
पूर्ण

#घोषणा __define_machine_initcall(mach, fn, id) \
	अटल पूर्णांक __init __machine_initcall_##mach##_##fn(व्योम) अणु \
		अगर (machine_is(mach)) वापस fn(); \
		वापस 0; \
	पूर्ण \
	__define_initcall(__machine_initcall_##mach##_##fn, id);

#घोषणा machine_early_initcall(mach, fn)	__define_machine_initcall(mach, fn, early)
#घोषणा machine_core_initcall(mach, fn)		__define_machine_initcall(mach, fn, 1)
#घोषणा machine_core_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 1s)
#घोषणा machine_postcore_initcall(mach, fn)	__define_machine_initcall(mach, fn, 2)
#घोषणा machine_postcore_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 2s)
#घोषणा machine_arch_initcall(mach, fn)		__define_machine_initcall(mach, fn, 3)
#घोषणा machine_arch_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 3s)
#घोषणा machine_subsys_initcall(mach, fn)	__define_machine_initcall(mach, fn, 4)
#घोषणा machine_subsys_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 4s)
#घोषणा machine_fs_initcall(mach, fn)		__define_machine_initcall(mach, fn, 5)
#घोषणा machine_fs_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 5s)
#घोषणा machine_rootfs_initcall(mach, fn)	__define_machine_initcall(mach, fn, rootfs)
#घोषणा machine_device_initcall(mach, fn)	__define_machine_initcall(mach, fn, 6)
#घोषणा machine_device_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 6s)
#घोषणा machine_late_initcall(mach, fn)		__define_machine_initcall(mach, fn, 7)
#घोषणा machine_late_initcall_sync(mach, fn)	__define_machine_initcall(mach, fn, 7s)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_MACHDEP_H */
