<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Just a place holder.
 */
#अगर_अघोषित _SPARC_SETUP_H
#घोषणा _SPARC_SETUP_H

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <uapi/यंत्र/setup.h>

बाह्य अक्षर reboot_command[];

#अगर_घोषित CONFIG_SPARC32
/* The CPU that was used क्रम booting
 * Only sun4d + leon may have boot_cpu_id != 0
 */
बाह्य अचिन्हित अक्षर boot_cpu_id;

बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];

बाह्य पूर्णांक serial_console;
अटल अंतरभूत पूर्णांक con_is_present(व्योम)
अणु
	वापस serial_console ? 0 : 1;
पूर्ण

/* from irq_32.c */
बाह्य अस्थिर अचिन्हित अक्षर *fdc_status;
बाह्य अक्षर *pdma_vaddr;
बाह्य अचिन्हित दीर्घ pdma_size;
बाह्य अस्थिर पूर्णांक करोing_pdma;

/* This is software state */
बाह्य अक्षर *pdma_base;
बाह्य अचिन्हित दीर्घ pdma_areasize;

पूर्णांक sparc_floppy_request_irq(अचिन्हित पूर्णांक irq, irq_handler_t irq_handler);

/* setup_32.c */
बाह्य अचिन्हित दीर्घ cmdline_memory_size;

/* devices.c */
व्योम __init device_scan(व्योम);

/* unaligned_32.c */
अचिन्हित दीर्घ safe_compute_effective_address(काष्ठा pt_regs *, अचिन्हित पूर्णांक);

#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC64
व्योम __init start_early_boot(व्योम);

/* unaligned_64.c */
पूर्णांक handle_ldf_stq(u32 insn, काष्ठा pt_regs *regs);
व्योम handle_ld_nf(u32 insn, काष्ठा pt_regs *regs);

/* init_64.c */
बाह्य atomic_t dcpage_flushes;
बाह्य atomic_t dcpage_flushes_xcall;

बाह्य पूर्णांक sysctl_tsb_ratio;

#अगर_घोषित CONFIG_SERIAL_SUNHV
व्योम sunhv_migrate_hvcons_irq(पूर्णांक cpu);
#पूर्ण_अगर
#पूर्ण_अगर
व्योम sun_करो_अवरोध(व्योम);
बाह्य पूर्णांक stop_a_enabled;
बाह्य पूर्णांक scons_pwroff;

#पूर्ण_अगर /* _SPARC_SETUP_H */
