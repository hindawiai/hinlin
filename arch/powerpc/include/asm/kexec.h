<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_KEXEC_H
#घोषणा _ASM_POWERPC_KEXEC_H
#अगर_घोषित __KERNEL__

#अगर defined(CONFIG_FSL_BOOKE) || defined(CONFIG_44x)

/*
 * On FSL-BookE we setup a 1:1 mapping which covers the first 2GiB of memory
 * and thereक्रमe we can only deal with memory within this range
 */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT	(2 * 1024 * 1024 * 1024UL - 1)
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT	(2 * 1024 * 1024 * 1024UL - 1)
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT	(2 * 1024 * 1024 * 1024UL - 1)

#अन्यथा

/*
 * Maximum page that is mapped directly पूर्णांकo kernel memory.
 * XXX: Since we copy virt we can use any page we allocate
 */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)

/*
 * Maximum address we can reach in physical address mode.
 * XXX: I want to allow initrd in highmem. Otherwise set to rmo on LPAR.
 */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)

/* Maximum address we can use क्रम the control code buffer */
#अगर_घोषित __घातerpc64__
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)
#अन्यथा
/* TASK_SIZE, probably left over from use_mm ?? */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT TASK_SIZE
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा KEXEC_CONTROL_PAGE_SIZE 4096

/* The native architecture */
#अगर_घोषित __घातerpc64__
#घोषणा KEXEC_ARCH KEXEC_ARCH_PPC64
#अन्यथा
#घोषणा KEXEC_ARCH KEXEC_ARCH_PPC
#पूर्ण_अगर

#घोषणा KEXEC_STATE_NONE 0
#घोषणा KEXEC_STATE_IRQS_OFF 1
#घोषणा KEXEC_STATE_REAL_MODE 2

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/reg.h>

प्रकार व्योम (*crash_shutकरोwn_t)(व्योम);

#अगर_घोषित CONFIG_KEXEC_CORE

/*
 * This function is responsible क्रम capturing रेजिस्टर states अगर coming
 * via panic or invoking dump using sysrq-trigger.
 */
अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
					काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs)
		स_नकल(newregs, oldregs, माप(*newregs));
	अन्यथा
		ppc_save_regs(newregs);
पूर्ण

बाह्य व्योम kexec_smp_रुको(व्योम);	/* get and clear naca physid, रुको क्रम
					  master to copy new code to 0 */
बाह्य पूर्णांक crashing_cpu;
बाह्य व्योम crash_send_ipi(व्योम (*crash_ipi_callback)(काष्ठा pt_regs *));
बाह्य व्योम crash_ipi_callback(काष्ठा pt_regs *);
बाह्य पूर्णांक crash_wake_offline;

काष्ठा kimage;
काष्ठा pt_regs;
बाह्य व्योम शेष_machine_kexec(काष्ठा kimage *image);
बाह्य पूर्णांक शेष_machine_kexec_prepare(काष्ठा kimage *image);
बाह्य व्योम शेष_machine_crash_shutकरोwn(काष्ठा pt_regs *regs);
बाह्य पूर्णांक crash_shutकरोwn_रेजिस्टर(crash_shutकरोwn_t handler);
बाह्य पूर्णांक crash_shutकरोwn_unरेजिस्टर(crash_shutकरोwn_t handler);

बाह्य व्योम crash_kexec_secondary(काष्ठा pt_regs *regs);
बाह्य पूर्णांक overlaps_crashkernel(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य व्योम reserve_crashkernel(व्योम);
बाह्य व्योम machine_kexec_mask_पूर्णांकerrupts(व्योम);

अटल अंतरभूत bool kdump_in_progress(व्योम)
अणु
	वापस crashing_cpu >= 0;
पूर्ण

व्योम relocate_new_kernel(अचिन्हित दीर्घ indirection_page, अचिन्हित दीर्घ reboot_code_buffer,
			 अचिन्हित दीर्घ start_address) __noवापस;

#अगर_घोषित CONFIG_KEXEC_खाता
बाह्य स्थिर काष्ठा kexec_file_ops kexec_elf64_ops;

#घोषणा ARCH_HAS_KIMAGE_ARCH

काष्ठा kimage_arch अणु
	काष्ठा crash_mem *exclude_ranges;

	अचिन्हित दीर्घ backup_start;
	व्योम *backup_buf;
	व्योम *fdt;
पूर्ण;

अक्षर *setup_kdump_cmdline(काष्ठा kimage *image, अक्षर *cmdline,
			  अचिन्हित दीर्घ cmdline_len);
पूर्णांक setup_purgatory(काष्ठा kimage *image, स्थिर व्योम *slave_code,
		    स्थिर व्योम *fdt, अचिन्हित दीर्घ kernel_load_addr,
		    अचिन्हित दीर्घ fdt_load_addr);

#अगर_घोषित CONFIG_PPC64
काष्ठा kexec_buf;

पूर्णांक load_crashdump_segments_ppc64(काष्ठा kimage *image,
				  काष्ठा kexec_buf *kbuf);
पूर्णांक setup_purgatory_ppc64(काष्ठा kimage *image, स्थिर व्योम *slave_code,
			  स्थिर व्योम *fdt, अचिन्हित दीर्घ kernel_load_addr,
			  अचिन्हित दीर्घ fdt_load_addr);
अचिन्हित पूर्णांक kexec_extra_fdt_size_ppc64(काष्ठा kimage *image);
पूर्णांक setup_new_fdt_ppc64(स्थिर काष्ठा kimage *image, व्योम *fdt,
			अचिन्हित दीर्घ initrd_load_addr,
			अचिन्हित दीर्घ initrd_len, स्थिर अक्षर *cmdline);
#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* CONFIG_KEXEC_खाता */

#अन्यथा /* !CONFIG_KEXEC_CORE */
अटल अंतरभूत व्योम crash_kexec_secondary(काष्ठा pt_regs *regs) अणु पूर्ण

अटल अंतरभूत पूर्णांक overlaps_crashkernel(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम reserve_crashkernel(व्योम) अणु ; पूर्ण

अटल अंतरभूत पूर्णांक crash_shutकरोwn_रेजिस्टर(crash_shutकरोwn_t handler)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crash_shutकरोwn_unरेजिस्टर(crash_shutकरोwn_t handler)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool kdump_in_progress(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम crash_ipi_callback(काष्ठा pt_regs *regs) अणु पूर्ण

अटल अंतरभूत व्योम crash_send_ipi(व्योम (*crash_ipi_callback)(काष्ठा pt_regs *))
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/kexec.h>
#पूर्ण_अगर

#अगर_अघोषित reset_sprs
#घोषणा reset_sprs reset_sprs
अटल अंतरभूत व्योम reset_sprs(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* ! __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_KEXEC_H */
