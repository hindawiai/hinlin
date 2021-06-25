<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BOOT_COMPRESSED_MISC_H
#घोषणा BOOT_COMPRESSED_MISC_H

/*
 * Special hack: we have to be careful, because no indirections are allowed here,
 * and paravirt_ops is a kind of one. As it will only run in baremetal anyway,
 * we just keep it from happening. (This list needs to be extended when new
 * paravirt and debugging variants are added.)
 */
#अघोषित CONFIG_PARAVIRT
#अघोषित CONFIG_PARAVIRT_XXL
#अघोषित CONFIG_PARAVIRT_SPINLOCKS
#अघोषित CONFIG_KASAN
#अघोषित CONFIG_KASAN_GENERIC

/* cpu_feature_enabled() cannot be used this early */
#घोषणा USE_EARLY_PGTABLE_L5

#समावेश <linux/linkage.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/elf.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/boot.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/desc_defs.h>

#घोषणा BOOT_CTYPE_H
#समावेश <linux/acpi.h>

#घोषणा BOOT_BOOT_H
#समावेश "../ctype.h"

#अगर_घोषित CONFIG_X86_64
#घोषणा memptr दीर्घ
#अन्यथा
#घोषणा memptr अचिन्हित
#पूर्ण_अगर

/* boot/compressed/vmlinux start and end markers */
बाह्य अक्षर _head[], _end[];

/* misc.c */
बाह्य memptr मुक्त_mem_ptr;
बाह्य memptr मुक्त_mem_end_ptr;
बाह्य काष्ठा boot_params *boot_params;
व्योम __माला_दोtr(स्थिर अक्षर *s);
व्योम __puthex(अचिन्हित दीर्घ value);
#घोषणा error_माला_दोtr(__x)  __माला_दोtr(__x)
#घोषणा error_puthex(__x)  __puthex(__x)

#अगर_घोषित CONFIG_X86_VERBOSE_BOOTUP

#घोषणा debug_माला_दोtr(__x)  __माला_दोtr(__x)
#घोषणा debug_puthex(__x)  __puthex(__x)
#घोषणा debug_putaddr(__x) अणु \
		debug_माला_दोtr(#__x ": 0x"); \
		debug_puthex((अचिन्हित दीर्घ)(__x)); \
		debug_माला_दोtr("\n"); \
	पूर्ण

#अन्यथा

अटल अंतरभूत व्योम debug_माला_दोtr(स्थिर अक्षर *s)
अणु पूर्ण
अटल अंतरभूत व्योम debug_puthex(अचिन्हित दीर्घ value)
अणु पूर्ण
#घोषणा debug_putaddr(x) /* */

#पूर्ण_अगर

/* cmdline.c */
पूर्णांक cmdline_find_option(स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize);
पूर्णांक cmdline_find_option_bool(स्थिर अक्षर *option);

काष्ठा mem_vector अणु
	u64 start;
	u64 size;
पूर्ण;

#अगर_घोषित CONFIG_RANDOMIZE_BASE
/* kaslr.c */
व्योम choose_अक्रमom_location(अचिन्हित दीर्घ input,
			    अचिन्हित दीर्घ input_size,
			    अचिन्हित दीर्घ *output,
			    अचिन्हित दीर्घ output_size,
			    अचिन्हित दीर्घ *virt_addr);
#अन्यथा
अटल अंतरभूत व्योम choose_अक्रमom_location(अचिन्हित दीर्घ input,
					  अचिन्हित दीर्घ input_size,
					  अचिन्हित दीर्घ *output,
					  अचिन्हित दीर्घ output_size,
					  अचिन्हित दीर्घ *virt_addr)
अणु
पूर्ण
#पूर्ण_अगर

/* cpuflags.c */
bool has_cpuflag(पूर्णांक flag);

#अगर_घोषित CONFIG_X86_64
बाह्य पूर्णांक set_page_decrypted(अचिन्हित दीर्घ address);
बाह्य पूर्णांक set_page_encrypted(अचिन्हित दीर्घ address);
बाह्य पूर्णांक set_page_non_present(अचिन्हित दीर्घ address);
बाह्य अचिन्हित अक्षर _pgtable[];
#पूर्ण_अगर

#अगर_घोषित CONFIG_EARLY_PRINTK
/* early_serial_console.c */
बाह्य पूर्णांक early_serial_base;
व्योम console_init(व्योम);
#अन्यथा
अटल स्थिर पूर्णांक early_serial_base;
अटल अंतरभूत व्योम console_init(व्योम)
अणु पूर्ण
#पूर्ण_अगर

व्योम set_sev_encryption_mask(व्योम);

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
व्योम sev_es_shutकरोwn_ghcb(व्योम);
बाह्य bool sev_es_check_ghcb_fault(अचिन्हित दीर्घ address);
#अन्यथा
अटल अंतरभूत व्योम sev_es_shutकरोwn_ghcb(व्योम) अणु पूर्ण
अटल अंतरभूत bool sev_es_check_ghcb_fault(अचिन्हित दीर्घ address)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* acpi.c */
#अगर_घोषित CONFIG_ACPI
acpi_physical_address get_rsdp_addr(व्योम);
#अन्यथा
अटल अंतरभूत acpi_physical_address get_rsdp_addr(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_RANDOMIZE_BASE) && defined(CONFIG_MEMORY_HOTREMOVE) && defined(CONFIG_ACPI)
बाह्य काष्ठा mem_vector immovable_mem[MAX_NUMNODES*2];
पूर्णांक count_immovable_mem_regions(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक count_immovable_mem_regions(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* ident_map_64.c */
#अगर_घोषित CONFIG_X86_5LEVEL
बाह्य अचिन्हित पूर्णांक __pgtable_l5_enabled, pgdir_shअगरt, ptrs_per_p4d;
#पूर्ण_अगर

/* Used by PAGE_KERN* macros: */
बाह्य pteval_t __शेष_kernel_pte_mask;

/* idt_64.c */
बाह्य gate_desc boot_idt[BOOT_IDT_ENTRIES];
बाह्य काष्ठा desc_ptr boot_idt_desc;

#अगर_घोषित CONFIG_X86_64
व्योम cleanup_exception_handling(व्योम);
#अन्यथा
अटल अंतरभूत व्योम cleanup_exception_handling(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* IDT Entry Poपूर्णांकs */
व्योम boot_page_fault(व्योम);
व्योम boot_stage1_vc(व्योम);
व्योम boot_stage2_vc(व्योम);

अचिन्हित दीर्घ sev_verअगरy_cbit(अचिन्हित दीर्घ cr3);

#पूर्ण_अगर /* BOOT_COMPRESSED_MISC_H */
