<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित XEN_OPS_H
#घोषणा XEN_OPS_H

#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqवापस.h>
#समावेश <xen/xen-ops.h>

/* These are code, but not functions.  Defined in entry.S */
बाह्य स्थिर अक्षर xen_failsafe_callback[];

व्योम xen_sysenter_target(व्योम);
#अगर_घोषित CONFIG_X86_64
व्योम xen_syscall_target(व्योम);
व्योम xen_syscall32_target(व्योम);
#पूर्ण_अगर

बाह्य व्योम *xen_initial_gdt;

काष्ठा trap_info;
व्योम xen_copy_trap_info(काष्ठा trap_info *traps);

DECLARE_PER_CPU(काष्ठा vcpu_info, xen_vcpu_info);
DECLARE_PER_CPU(अचिन्हित दीर्घ, xen_cr3);
DECLARE_PER_CPU(अचिन्हित दीर्घ, xen_current_cr3);

बाह्य काष्ठा start_info *xen_start_info;
बाह्य काष्ठा shared_info xen_dummy_shared_info;
बाह्य काष्ठा shared_info *HYPERVISOR_shared_info;

बाह्य bool xen_fअगरo_events;

व्योम xen_setup_mfn_list_list(व्योम);
व्योम xen_build_mfn_list_list(व्योम);
व्योम xen_setup_machphys_mapping(व्योम);
व्योम xen_setup_kernel_pagetable(pgd_t *pgd, अचिन्हित दीर्घ max_pfn);
व्योम __init xen_reserve_special_pages(व्योम);
व्योम __init xen_pt_check_e820(व्योम);

व्योम xen_mm_pin_all(व्योम);
व्योम xen_mm_unpin_all(व्योम);
#अगर_घोषित CONFIG_X86_64
व्योम __init xen_relocate_p2m(व्योम);
#पूर्ण_अगर

bool __init xen_is_e820_reserved(phys_addr_t start, phys_addr_t size);
अचिन्हित दीर्घ __ref xen_chk_extra_mem(अचिन्हित दीर्घ pfn);
व्योम __init xen_inv_extra_mem(व्योम);
व्योम __init xen_remap_memory(व्योम);
phys_addr_t __init xen_find_मुक्त_area(phys_addr_t size);
अक्षर * __init xen_memory_setup(व्योम);
व्योम __init xen_arch_setup(व्योम);
व्योम xen_enable_sysenter(व्योम);
व्योम xen_enable_syscall(व्योम);
व्योम xen_vcpu_restore(व्योम);

व्योम xen_hvm_init_shared_info(व्योम);
व्योम xen_unplug_emulated_devices(व्योम);

व्योम __init xen_build_dynamic_phys_to_machine(व्योम);
व्योम __init xen_vदो_स्मृति_p2m_tree(व्योम);

व्योम xen_init_irq_ops(व्योम);
व्योम xen_setup_समयr(पूर्णांक cpu);
व्योम xen_setup_runstate_info(पूर्णांक cpu);
व्योम xen_tearकरोwn_समयr(पूर्णांक cpu);
व्योम xen_setup_cpu_घड़ीevents(व्योम);
व्योम xen_save_समय_memory_area(व्योम);
व्योम xen_restore_समय_memory_area(व्योम);
व्योम xen_init_समय_ops(व्योम);
व्योम xen_hvm_init_समय_ops(व्योम);

irqवापस_t xen_debug_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

bool xen_vcpu_stolen(पूर्णांक vcpu);

बाह्य पूर्णांक xen_have_vcpu_info_placement;

पूर्णांक xen_vcpu_setup(पूर्णांक cpu);
व्योम xen_vcpu_info_reset(पूर्णांक cpu);
व्योम xen_setup_vcpu_info_placement(व्योम);

#अगर_घोषित CONFIG_SMP
व्योम xen_smp_init(व्योम);
व्योम __init xen_hvm_smp_init(व्योम);

बाह्य cpumask_var_t xen_cpu_initialized_map;
#अन्यथा
अटल अंतरभूत व्योम xen_smp_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम xen_hvm_smp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
व्योम __init xen_init_spinlocks(व्योम);
व्योम xen_init_lock_cpu(पूर्णांक cpu);
व्योम xen_uninit_lock_cpu(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम xen_init_spinlocks(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम xen_init_lock_cpu(पूर्णांक cpu)
अणु
पूर्ण
अटल अंतरभूत व्योम xen_uninit_lock_cpu(पूर्णांक cpu)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा करोm0_vga_console_info;

#अगर_घोषित CONFIG_XEN_DOM0
व्योम __init xen_init_vga(स्थिर काष्ठा करोm0_vga_console_info *, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम __init xen_init_vga(स्थिर काष्ठा करोm0_vga_console_info *info,
				       माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर

व्योम __init xen_init_apic(व्योम);

#अगर_घोषित CONFIG_XEN_EFI
बाह्य व्योम xen_efi_init(काष्ठा boot_params *boot_params);
#अन्यथा
अटल अंतरभूत व्योम __init xen_efi_init(काष्ठा boot_params *boot_params)
अणु
पूर्ण
#पूर्ण_अगर

__visible व्योम xen_irq_enable_direct(व्योम);
__visible व्योम xen_irq_disable_direct(व्योम);
__visible अचिन्हित दीर्घ xen_save_fl_direct(व्योम);

__visible अचिन्हित दीर्घ xen_पढ़ो_cr2(व्योम);
__visible अचिन्हित दीर्घ xen_पढ़ो_cr2_direct(व्योम);

/* These are not functions, and cannot be called normally */
__visible व्योम xen_iret(व्योम);

बाह्य पूर्णांक xen_panic_handler_init(व्योम);

पूर्णांक xen_cpuhp_setup(पूर्णांक (*cpu_up_prepare_cb)(अचिन्हित पूर्णांक),
		    पूर्णांक (*cpu_dead_cb)(अचिन्हित पूर्णांक));

व्योम xen_pin_vcpu(पूर्णांक cpu);

व्योम xen_emergency_restart(व्योम);
#अगर_घोषित CONFIG_XEN_PV
व्योम xen_pv_pre_suspend(व्योम);
व्योम xen_pv_post_suspend(पूर्णांक suspend_cancelled);
#अन्यथा
अटल अंतरभूत व्योम xen_pv_pre_suspend(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम xen_pv_post_suspend(पूर्णांक suspend_cancelled) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_PVHVM
व्योम xen_hvm_post_suspend(पूर्णांक suspend_cancelled);
#अन्यथा
अटल अंतरभूत व्योम xen_hvm_post_suspend(पूर्णांक suspend_cancelled) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* XEN_OPS_H */
