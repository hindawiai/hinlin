<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_KEXEC_H
#घोषणा _ASM_IA64_KEXEC_H

#समावेश <यंत्र/setup.h>

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
/* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT TASK_SIZE

#घोषणा KEXEC_CONTROL_PAGE_SIZE (8192 + 8192 + 4096)

/* The native architecture */
#घोषणा KEXEC_ARCH KEXEC_ARCH_IA_64

#घोषणा kexec_flush_icache_page(page) करो अणु \
                अचिन्हित दीर्घ page_addr = (अचिन्हित दीर्घ)page_address(page); \
                flush_icache_range(page_addr, page_addr + PAGE_SIZE); \
        पूर्ण जबतक(0)

बाह्य काष्ठा kimage *ia64_kimage;
बाह्य स्थिर अचिन्हित पूर्णांक relocate_new_kernel_size;
बाह्य व्योम relocate_new_kernel(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		काष्ठा ia64_boot_param *, अचिन्हित दीर्घ);
अटल अंतरभूत व्योम
crash_setup_regs(काष्ठा pt_regs *newregs, काष्ठा pt_regs *oldregs)
अणु
पूर्ण
बाह्य काष्ठा resource efi_memmap_res;
बाह्य काष्ठा resource boot_param_res;
बाह्य व्योम kdump_smp_send_stop(व्योम);
बाह्य व्योम kdump_smp_send_init(व्योम);
बाह्य व्योम kexec_disable_iosapic(व्योम);
बाह्य व्योम crash_save_this_cpu(व्योम);
काष्ठा rsvd_region;
बाह्य अचिन्हित दीर्घ kdump_find_rsvd_region(अचिन्हित दीर्घ size,
		काष्ठा rsvd_region *rsvd_regions, पूर्णांक n);
बाह्य व्योम kdump_cpu_मुक्तze(काष्ठा unw_frame_info *info, व्योम *arg);
बाह्य पूर्णांक kdump_status[];
बाह्य atomic_t kdump_cpu_मुक्तzed;
बाह्य atomic_t kdump_in_progress;

#पूर्ण_अगर /* _ASM_IA64_KEXEC_H */
