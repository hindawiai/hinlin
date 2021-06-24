<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

/* Prototypes of functions used across modules here in this directory.  */

#घोषणा vucp	अस्थिर अचिन्हित अक्षर  *
#घोषणा vusp	अस्थिर अचिन्हित लघु *
#घोषणा vip	अस्थिर पूर्णांक *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक   *
#घोषणा vulp	अस्थिर अचिन्हित दीर्घ  *

काष्ठा pt_regs;
काष्ठा task_काष्ठा;
काष्ठा pci_dev;
काष्ठा pci_controller;

/* core_apecs.c */
बाह्य काष्ठा pci_ops apecs_pci_ops;
बाह्य व्योम apecs_init_arch(व्योम);
बाह्य व्योम apecs_pci_clr_err(व्योम);
बाह्य व्योम apecs_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम apecs_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_cia.c */
बाह्य काष्ठा pci_ops cia_pci_ops;
बाह्य व्योम cia_init_pci(व्योम);
बाह्य व्योम cia_init_arch(व्योम);
बाह्य व्योम pyxis_init_arch(व्योम);
बाह्य व्योम cia_समाप्त_arch(पूर्णांक);
बाह्य व्योम cia_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम cia_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_irongate.c */
बाह्य काष्ठा pci_ops irongate_pci_ops;
बाह्य पूर्णांक irongate_pci_clr_err(व्योम);
बाह्य व्योम irongate_init_arch(व्योम);
#घोषणा irongate_pci_tbi ((व्योम *)0)

/* core_lca.c */
बाह्य काष्ठा pci_ops lca_pci_ops;
बाह्य व्योम lca_init_arch(व्योम);
बाह्य व्योम lca_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम lca_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_marvel.c */
बाह्य काष्ठा pci_ops marvel_pci_ops;
बाह्य व्योम marvel_init_arch(व्योम);
बाह्य व्योम marvel_समाप्त_arch(पूर्णांक);
बाह्य व्योम marvel_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम marvel_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);
बाह्य पूर्णांक marvel_pa_to_nid(अचिन्हित दीर्घ);
बाह्य पूर्णांक marvel_cpuid_to_nid(पूर्णांक);
बाह्य अचिन्हित दीर्घ marvel_node_mem_start(पूर्णांक);
बाह्य अचिन्हित दीर्घ marvel_node_mem_size(पूर्णांक);
बाह्य काष्ठा _alpha_agp_info *marvel_agp_info(व्योम);
काष्ठा io7 *marvel_find_io7(पूर्णांक pe);
काष्ठा io7 *marvel_next_io7(काष्ठा io7 *prev);
व्योम io7_clear_errors(काष्ठा io7 *io7);

/* core_mcpcia.c */
बाह्य काष्ठा pci_ops mcpcia_pci_ops;
बाह्य व्योम mcpcia_init_arch(व्योम);
बाह्य व्योम mcpcia_init_hoses(व्योम);
बाह्य व्योम mcpcia_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम mcpcia_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_polaris.c */
बाह्य काष्ठा pci_ops polaris_pci_ops;
बाह्य पूर्णांक polaris_पढ़ो_config_dword(काष्ठा pci_dev *, पूर्णांक, u32 *);
बाह्य पूर्णांक polaris_ग_लिखो_config_dword(काष्ठा pci_dev *, पूर्णांक, u32);
बाह्य व्योम polaris_init_arch(व्योम);
बाह्य व्योम polaris_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
#घोषणा polaris_pci_tbi ((व्योम *)0)

/* core_t2.c */
बाह्य काष्ठा pci_ops t2_pci_ops;
बाह्य व्योम t2_init_arch(व्योम);
बाह्य व्योम t2_समाप्त_arch(पूर्णांक);
बाह्य व्योम t2_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम t2_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_titan.c */
बाह्य काष्ठा pci_ops titan_pci_ops;
बाह्य व्योम titan_init_arch(व्योम);
बाह्य व्योम titan_समाप्त_arch(पूर्णांक);
बाह्य व्योम titan_machine_check(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम titan_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);
बाह्य काष्ठा _alpha_agp_info *titan_agp_info(व्योम);

/* core_tsunami.c */
बाह्य काष्ठा pci_ops tsunami_pci_ops;
बाह्य व्योम tsunami_init_arch(व्योम);
बाह्य व्योम tsunami_समाप्त_arch(पूर्णांक);
बाह्य व्योम tsunami_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम tsunami_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);

/* core_wildfire.c */
बाह्य काष्ठा pci_ops wildfire_pci_ops;
बाह्य व्योम wildfire_init_arch(व्योम);
बाह्य व्योम wildfire_समाप्त_arch(पूर्णांक);
बाह्य व्योम wildfire_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr);
बाह्य व्योम wildfire_pci_tbi(काष्ठा pci_controller *, dma_addr_t, dma_addr_t);
बाह्य पूर्णांक wildfire_pa_to_nid(अचिन्हित दीर्घ);
बाह्य पूर्णांक wildfire_cpuid_to_nid(पूर्णांक);
बाह्य अचिन्हित दीर्घ wildfire_node_mem_start(पूर्णांक);
बाह्य अचिन्हित दीर्घ wildfire_node_mem_size(पूर्णांक);

/* console.c */
#अगर_घोषित CONFIG_VGA_HOSE
बाह्य व्योम find_console_vga_hose(व्योम);
बाह्य व्योम locate_and_init_vga(व्योम *(*)(व्योम *, व्योम *));
#अन्यथा
अटल अंतरभूत व्योम find_console_vga_hose(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम locate_and_init_vga(व्योम *(*sel_func)(व्योम *, व्योम *)) अणु पूर्ण
#पूर्ण_अगर

/* setup.c */
बाह्य अचिन्हित दीर्घ srm_hae;
बाह्य पूर्णांक boot_cpuid;
#अगर_घोषित CONFIG_VERBOSE_MCHECK
बाह्य अचिन्हित दीर्घ alpha_verbose_mcheck;
#पूर्ण_अगर

/* srmcons.c */
#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM)
बाह्य व्योम रेजिस्टर_srm_console(व्योम);
बाह्य व्योम unरेजिस्टर_srm_console(व्योम);
#अन्यथा
#घोषणा रेजिस्टर_srm_console()
#घोषणा unरेजिस्टर_srm_console()
#पूर्ण_अगर

/* smp.c */
बाह्य व्योम setup_smp(व्योम);
बाह्य व्योम handle_ipi(काष्ठा pt_regs *);

/* bios32.c */
/* बाह्य व्योम reset_क्रम_srm(व्योम); */

/* समय.c */
बाह्य irqवापस_t rtc_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);
बाह्य व्योम init_घड़ीevent(व्योम);
बाह्य व्योम common_init_rtc(व्योम);
बाह्य अचिन्हित दीर्घ est_cycle_freq;

/* smc37c93x.c */
बाह्य व्योम SMC93x_Init(व्योम);

/* smc37c669.c */
बाह्य व्योम SMC669_Init(पूर्णांक);

/* es1888.c */
बाह्य व्योम es1888_init(व्योम);

/* ../lib/fpreg.c */
बाह्य व्योम alpha_ग_लिखो_fp_reg (अचिन्हित दीर्घ reg, अचिन्हित दीर्घ val);
बाह्य अचिन्हित दीर्घ alpha_पढ़ो_fp_reg (अचिन्हित दीर्घ reg);

/* head.S */
बाह्य व्योम wrmces(अचिन्हित दीर्घ mces);
बाह्य व्योम cserve_ena(अचिन्हित दीर्घ);
बाह्य व्योम cserve_dis(अचिन्हित दीर्घ);
बाह्य व्योम __smp_callin(अचिन्हित दीर्घ);

/* entry.S */
बाह्य व्योम entArith(व्योम);
बाह्य व्योम entIF(व्योम);
बाह्य व्योम entInt(व्योम);
बाह्य व्योम entMM(व्योम);
बाह्य व्योम entSys(व्योम);
बाह्य व्योम entUna(व्योम);
बाह्य व्योम entDbg(व्योम);

/* ptrace.c */
बाह्य पूर्णांक ptrace_set_bpt (काष्ठा task_काष्ठा *child);
बाह्य पूर्णांक ptrace_cancel_bpt (काष्ठा task_काष्ठा *child);

/* traps.c */
बाह्य व्योम dik_show_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *r9_15);
बाह्य व्योम die_अगर_kernel(अक्षर *, काष्ठा pt_regs *, दीर्घ, अचिन्हित दीर्घ *);

/* sys_titan.c */
बाह्य व्योम titan_dispatch_irqs(u64);

/* ../mm/init.c */
बाह्य व्योम चयन_to_प्रणाली_map(व्योम);
बाह्य व्योम srm_paging_stop(व्योम);

अटल अंतरभूत पूर्णांक
__alpha_remap_area_pages(अचिन्हित दीर्घ address, अचिन्हित दीर्घ phys_addr,
			 अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	pgprot_t prot;

	prot = __pgprot(_PAGE_VALID | _PAGE_ASM | _PAGE_KRE
			| _PAGE_KWE | flags);
	वापस ioremap_page_range(address, address + size, phys_addr, prot);
पूर्ण

/* irq.c */

#अगर_घोषित CONFIG_SMP
#घोषणा mcheck_expected(cpu)	(cpu_data[cpu].mcheck_expected)
#घोषणा mcheck_taken(cpu)	(cpu_data[cpu].mcheck_taken)
#घोषणा mcheck_extra(cpu)	(cpu_data[cpu].mcheck_extra)
#अन्यथा
बाह्य काष्ठा mcheck_info
अणु
	अचिन्हित अक्षर expected __attribute__((aligned(8)));
	अचिन्हित अक्षर taken;
	अचिन्हित अक्षर extra;
पूर्ण __mcheck_info;

#घोषणा mcheck_expected(cpu)	(*((व्योम)(cpu), &__mcheck_info.expected))
#घोषणा mcheck_taken(cpu)	(*((व्योम)(cpu), &__mcheck_info.taken))
#घोषणा mcheck_extra(cpu)	(*((व्योम)(cpu), &__mcheck_info.extra))
#पूर्ण_अगर

बाह्य व्योम process_mcheck_info(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr,
				स्थिर अक्षर *machine, पूर्णांक expected);
