<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_KEXEC_H
#घोषणा LINUX_KEXEC_H

#घोषणा IND_DESTINATION_BIT 0
#घोषणा IND_INसूचीECTION_BIT 1
#घोषणा IND_DONE_BIT        2
#घोषणा IND_SOURCE_BIT      3

#घोषणा IND_DESTINATION  (1 << IND_DESTINATION_BIT)
#घोषणा IND_INसूचीECTION  (1 << IND_INसूचीECTION_BIT)
#घोषणा IND_DONE         (1 << IND_DONE_BIT)
#घोषणा IND_SOURCE       (1 << IND_SOURCE_BIT)
#घोषणा IND_FLAGS (IND_DESTINATION | IND_INसूचीECTION | IND_DONE | IND_SOURCE)

#अगर !defined(__ASSEMBLY__)

#समावेश <linux/crash_core.h>
#समावेश <यंत्र/पन.स>

#समावेश <uapi/linux/kexec.h>

#अगर_घोषित CONFIG_KEXEC_CORE
#समावेश <linux/list.h>
#समावेश <linux/compat.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/kexec.h>

/* Verअगरy architecture specअगरic macros are defined */

#अगर_अघोषित KEXEC_SOURCE_MEMORY_LIMIT
#त्रुटि KEXEC_SOURCE_MEMORY_LIMIT not defined
#पूर्ण_अगर

#अगर_अघोषित KEXEC_DESTINATION_MEMORY_LIMIT
#त्रुटि KEXEC_DESTINATION_MEMORY_LIMIT not defined
#पूर्ण_अगर

#अगर_अघोषित KEXEC_CONTROL_MEMORY_LIMIT
#त्रुटि KEXEC_CONTROL_MEMORY_LIMIT not defined
#पूर्ण_अगर

#अगर_अघोषित KEXEC_CONTROL_MEMORY_GFP
#घोषणा KEXEC_CONTROL_MEMORY_GFP (GFP_KERNEL | __GFP_NORETRY)
#पूर्ण_अगर

#अगर_अघोषित KEXEC_CONTROL_PAGE_SIZE
#त्रुटि KEXEC_CONTROL_PAGE_SIZE not defined
#पूर्ण_अगर

#अगर_अघोषित KEXEC_ARCH
#त्रुटि KEXEC_ARCH not defined
#पूर्ण_अगर

#अगर_अघोषित KEXEC_CRASH_CONTROL_MEMORY_LIMIT
#घोषणा KEXEC_CRASH_CONTROL_MEMORY_LIMIT KEXEC_CONTROL_MEMORY_LIMIT
#पूर्ण_अगर

#अगर_अघोषित KEXEC_CRASH_MEM_ALIGN
#घोषणा KEXEC_CRASH_MEM_ALIGN PAGE_SIZE
#पूर्ण_अगर

#घोषणा KEXEC_CORE_NOTE_NAME	CRASH_CORE_NOTE_NAME

/*
 * This काष्ठाure is used to hold the arguments that are used when loading
 * kernel binaries.
 */

प्रकार अचिन्हित दीर्घ kimage_entry_t;

काष्ठा kexec_segment अणु
	/*
	 * This poपूर्णांकer can poपूर्णांक to user memory अगर kexec_load() प्रणाली
	 * call is used or will poपूर्णांक to kernel memory अगर
	 * kexec_file_load() प्रणाली call is used.
	 *
	 * Use ->buf when expecting to deal with user memory and use ->kbuf
	 * when expecting to deal with kernel memory.
	 */
	जोड़ अणु
		व्योम __user *buf;
		व्योम *kbuf;
	पूर्ण;
	माप_प्रकार bufsz;
	अचिन्हित दीर्घ mem;
	माप_प्रकार memsz;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_kexec_segment अणु
	compat_uptr_t buf;
	compat_माप_प्रकार bufsz;
	compat_uदीर्घ_t mem;	/* User space sees this as a (व्योम *) ... */
	compat_माप_प्रकार memsz;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_खाता
काष्ठा purgatory_info अणु
	/*
	 * Poपूर्णांकer to elf header at the beginning of kexec_purgatory.
	 * Note: kexec_purgatory is पढ़ो only
	 */
	स्थिर Elf_Ehdr *ehdr;
	/*
	 * Temporary, modअगरiable buffer क्रम sechdrs used क्रम relocation.
	 * This memory can be मुक्तd post image load.
	 */
	Elf_Shdr *sechdrs;
	/*
	 * Temporary, modअगरiable buffer क्रम stripped purgatory used क्रम
	 * relocation. This memory can be मुक्तd post image load.
	 */
	व्योम *purgatory_buf;
पूर्ण;

काष्ठा kimage;

प्रकार पूर्णांक (kexec_probe_t)(स्थिर अक्षर *kernel_buf, अचिन्हित दीर्घ kernel_size);
प्रकार व्योम *(kexec_load_t)(काष्ठा kimage *image, अक्षर *kernel_buf,
			     अचिन्हित दीर्घ kernel_len, अक्षर *initrd,
			     अचिन्हित दीर्घ initrd_len, अक्षर *cmdline,
			     अचिन्हित दीर्घ cmdline_len);
प्रकार पूर्णांक (kexec_cleanup_t)(व्योम *loader_data);

#अगर_घोषित CONFIG_KEXEC_SIG
प्रकार पूर्णांक (kexec_verअगरy_sig_t)(स्थिर अक्षर *kernel_buf,
				 अचिन्हित दीर्घ kernel_len);
#पूर्ण_अगर

काष्ठा kexec_file_ops अणु
	kexec_probe_t *probe;
	kexec_load_t *load;
	kexec_cleanup_t *cleanup;
#अगर_घोषित CONFIG_KEXEC_SIG
	kexec_verअगरy_sig_t *verअगरy_sig;
#पूर्ण_अगर
पूर्ण;

बाह्य स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[];

पूर्णांक kexec_image_probe_शेष(काष्ठा kimage *image, व्योम *buf,
			      अचिन्हित दीर्घ buf_len);
पूर्णांक kexec_image_post_load_cleanup_शेष(काष्ठा kimage *image);

/*
 * If kexec_buf.mem is set to this value, kexec_locate_mem_hole()
 * will try to allocate मुक्त memory. Arch may overग_लिखो it.
 */
#अगर_अघोषित KEXEC_BUF_MEM_UNKNOWN
#घोषणा KEXEC_BUF_MEM_UNKNOWN 0
#पूर्ण_अगर

/**
 * काष्ठा kexec_buf - parameters क्रम finding a place क्रम a buffer in memory
 * @image:	kexec image in which memory to search.
 * @buffer:	Contents which will be copied to the allocated memory.
 * @bufsz:	Size of @buffer.
 * @mem:	On वापस will have address of the buffer in memory.
 * @memsz:	Size क्रम the buffer in memory.
 * @buf_align:	Minimum alignment needed.
 * @buf_min:	The buffer can't be placed below this address.
 * @buf_max:	The buffer can't be placed above this address.
 * @top_करोwn:	Allocate from top of memory.
 */
काष्ठा kexec_buf अणु
	काष्ठा kimage *image;
	व्योम *buffer;
	अचिन्हित दीर्घ bufsz;
	अचिन्हित दीर्घ mem;
	अचिन्हित दीर्घ memsz;
	अचिन्हित दीर्घ buf_align;
	अचिन्हित दीर्घ buf_min;
	अचिन्हित दीर्घ buf_max;
	bool top_करोwn;
पूर्ण;

पूर्णांक kexec_load_purgatory(काष्ठा kimage *image, काष्ठा kexec_buf *kbuf);
पूर्णांक kexec_purgatory_get_set_symbol(काष्ठा kimage *image, स्थिर अक्षर *name,
				   व्योम *buf, अचिन्हित पूर्णांक size,
				   bool get_value);
व्योम *kexec_purgatory_get_symbol_addr(काष्ठा kimage *image, स्थिर अक्षर *name);

/* Architectures may override the below functions */
पूर्णांक arch_kexec_kernel_image_probe(काष्ठा kimage *image, व्योम *buf,
				  अचिन्हित दीर्घ buf_len);
व्योम *arch_kexec_kernel_image_load(काष्ठा kimage *image);
पूर्णांक arch_kexec_apply_relocations_add(काष्ठा purgatory_info *pi,
				     Elf_Shdr *section,
				     स्थिर Elf_Shdr *rअन्यथाc,
				     स्थिर Elf_Shdr *symtab);
पूर्णांक arch_kexec_apply_relocations(काष्ठा purgatory_info *pi,
				 Elf_Shdr *section,
				 स्थिर Elf_Shdr *rअन्यथाc,
				 स्थिर Elf_Shdr *symtab);
पूर्णांक arch_kimage_file_post_load_cleanup(काष्ठा kimage *image);
#अगर_घोषित CONFIG_KEXEC_SIG
पूर्णांक arch_kexec_kernel_verअगरy_sig(काष्ठा kimage *image, व्योम *buf,
				 अचिन्हित दीर्घ buf_len);
#पूर्ण_अगर
पूर्णांक arch_kexec_locate_mem_hole(काष्ठा kexec_buf *kbuf);

बाह्य पूर्णांक kexec_add_buffer(काष्ठा kexec_buf *kbuf);
पूर्णांक kexec_locate_mem_hole(काष्ठा kexec_buf *kbuf);

/* Alignment required क्रम elf header segment */
#घोषणा ELF_CORE_HEADER_ALIGN   4096

काष्ठा crash_mem_range अणु
	u64 start, end;
पूर्ण;

काष्ठा crash_mem अणु
	अचिन्हित पूर्णांक max_nr_ranges;
	अचिन्हित पूर्णांक nr_ranges;
	काष्ठा crash_mem_range ranges[];
पूर्ण;

बाह्य पूर्णांक crash_exclude_mem_range(काष्ठा crash_mem *mem,
				   अचिन्हित दीर्घ दीर्घ mstart,
				   अचिन्हित दीर्घ दीर्घ mend);
बाह्य पूर्णांक crash_prepare_elf64_headers(काष्ठा crash_mem *mem, पूर्णांक kernel_map,
				       व्योम **addr, अचिन्हित दीर्घ *sz);
#पूर्ण_अगर /* CONFIG_KEXEC_खाता */

#अगर_घोषित CONFIG_KEXEC_ELF
काष्ठा kexec_elf_info अणु
	/*
	 * Where the ELF binary contents are kept.
	 * Memory managed by the user of the काष्ठा.
	 */
	स्थिर अक्षर *buffer;

	स्थिर काष्ठा elfhdr *ehdr;
	स्थिर काष्ठा elf_phdr *proghdrs;
पूर्ण;

पूर्णांक kexec_build_elf_info(स्थिर अक्षर *buf, माप_प्रकार len, काष्ठा elfhdr *ehdr,
			       काष्ठा kexec_elf_info *elf_info);

पूर्णांक kexec_elf_load(काष्ठा kimage *image, काष्ठा elfhdr *ehdr,
			 काष्ठा kexec_elf_info *elf_info,
			 काष्ठा kexec_buf *kbuf,
			 अचिन्हित दीर्घ *lowest_load_addr);

व्योम kexec_मुक्त_elf_info(काष्ठा kexec_elf_info *elf_info);
पूर्णांक kexec_elf_probe(स्थिर अक्षर *buf, अचिन्हित दीर्घ len);
#पूर्ण_अगर
काष्ठा kimage अणु
	kimage_entry_t head;
	kimage_entry_t *entry;
	kimage_entry_t *last_entry;

	अचिन्हित दीर्घ start;
	काष्ठा page *control_code_page;
	काष्ठा page *swap_page;
	व्योम *vmcoreinfo_data_copy; /* locates in the crash memory */

	अचिन्हित दीर्घ nr_segments;
	काष्ठा kexec_segment segment[KEXEC_SEGMENT_MAX];

	काष्ठा list_head control_pages;
	काष्ठा list_head dest_pages;
	काष्ठा list_head unusable_pages;

	/* Address of next control page to allocate क्रम crash kernels. */
	अचिन्हित दीर्घ control_page;

	/* Flags to indicate special processing */
	अचिन्हित पूर्णांक type : 1;
#घोषणा KEXEC_TYPE_DEFAULT 0
#घोषणा KEXEC_TYPE_CRASH   1
	अचिन्हित पूर्णांक preserve_context : 1;
	/* If set, we are using file mode kexec syscall */
	अचिन्हित पूर्णांक file_mode:1;

#अगर_घोषित ARCH_HAS_KIMAGE_ARCH
	काष्ठा kimage_arch arch;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_खाता
	/* Additional fields क्रम file based kexec syscall */
	व्योम *kernel_buf;
	अचिन्हित दीर्घ kernel_buf_len;

	व्योम *initrd_buf;
	अचिन्हित दीर्घ initrd_buf_len;

	अक्षर *cmdline_buf;
	अचिन्हित दीर्घ cmdline_buf_len;

	/* File operations provided by image loader */
	स्थिर काष्ठा kexec_file_ops *fops;

	/* Image loader handling the kernel can store a poपूर्णांकer here */
	व्योम *image_loader_data;

	/* Inक्रमmation क्रम loading purgatory */
	काष्ठा purgatory_info purgatory_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_KEXEC
	/* Virtual address of IMA measurement buffer क्रम kexec syscall */
	व्योम *ima_buffer;

	phys_addr_t ima_buffer_addr;
	माप_प्रकार ima_buffer_size;
#पूर्ण_अगर

	/* Core ELF header buffer */
	व्योम *elf_headers;
	अचिन्हित दीर्घ elf_headers_sz;
	अचिन्हित दीर्घ elf_load_addr;
पूर्ण;

/* kexec पूर्णांकerface functions */
बाह्य व्योम machine_kexec(काष्ठा kimage *image);
बाह्य पूर्णांक machine_kexec_prepare(काष्ठा kimage *image);
बाह्य व्योम machine_kexec_cleanup(काष्ठा kimage *image);
बाह्य पूर्णांक kernel_kexec(व्योम);
बाह्य काष्ठा page *kimage_alloc_control_pages(काष्ठा kimage *image,
						अचिन्हित पूर्णांक order);
पूर्णांक machine_kexec_post_load(काष्ठा kimage *image);

बाह्य व्योम __crash_kexec(काष्ठा pt_regs *);
बाह्य व्योम crash_kexec(काष्ठा pt_regs *);
पूर्णांक kexec_should_crash(काष्ठा task_काष्ठा *);
पूर्णांक kexec_crash_loaded(व्योम);
व्योम crash_save_cpu(काष्ठा pt_regs *regs, पूर्णांक cpu);
बाह्य पूर्णांक kimage_crash_copy_vmcoreinfo(काष्ठा kimage *image);

बाह्य काष्ठा kimage *kexec_image;
बाह्य काष्ठा kimage *kexec_crash_image;
बाह्य पूर्णांक kexec_load_disabled;

#अगर_अघोषित kexec_flush_icache_page
#घोषणा kexec_flush_icache_page(page)
#पूर्ण_अगर

/* List of defined/legal kexec flags */
#अगर_अघोषित CONFIG_KEXEC_JUMP
#घोषणा KEXEC_FLAGS    KEXEC_ON_CRASH
#अन्यथा
#घोषणा KEXEC_FLAGS    (KEXEC_ON_CRASH | KEXEC_PRESERVE_CONTEXT)
#पूर्ण_अगर

/* List of defined/legal kexec file flags */
#घोषणा KEXEC_खाता_FLAGS	(KEXEC_खाता_UNLOAD | KEXEC_खाता_ON_CRASH | \
				 KEXEC_खाता_NO_INITRAMFS)

/* Location of a reserved region to hold the crash kernel.
 */
बाह्य काष्ठा resource crashk_res;
बाह्य काष्ठा resource crashk_low_res;
बाह्य note_buf_t __percpu *crash_notes;

/* flag to track अगर kexec reboot is in progress */
बाह्य bool kexec_in_progress;

पूर्णांक crash_shrink_memory(अचिन्हित दीर्घ new_size);
माप_प्रकार crash_get_memory_size(व्योम);
व्योम crash_मुक्त_reserved_phys_range(अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end);

व्योम arch_kexec_protect_crashkres(व्योम);
व्योम arch_kexec_unprotect_crashkres(व्योम);

#अगर_अघोषित page_to_boot_pfn
अटल अंतरभूत अचिन्हित दीर्घ page_to_boot_pfn(काष्ठा page *page)
अणु
	वापस page_to_pfn(page);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित boot_pfn_to_page
अटल अंतरभूत काष्ठा page *boot_pfn_to_page(अचिन्हित दीर्घ boot_pfn)
अणु
	वापस pfn_to_page(boot_pfn);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित phys_to_boot_phys
अटल अंतरभूत अचिन्हित दीर्घ phys_to_boot_phys(phys_addr_t phys)
अणु
	वापस phys;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित boot_phys_to_phys
अटल अंतरभूत phys_addr_t boot_phys_to_phys(अचिन्हित दीर्घ boot_phys)
अणु
	वापस boot_phys;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ virt_to_boot_phys(व्योम *addr)
अणु
	वापस phys_to_boot_phys(__pa((अचिन्हित दीर्घ)addr));
पूर्ण

अटल अंतरभूत व्योम *boot_phys_to_virt(अचिन्हित दीर्घ entry)
अणु
	वापस phys_to_virt(boot_phys_to_phys(entry));
पूर्ण

#अगर_अघोषित arch_kexec_post_alloc_pages
अटल अंतरभूत पूर्णांक arch_kexec_post_alloc_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages, gfp_t gfp) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_kexec_pre_मुक्त_pages
अटल अंतरभूत व्योम arch_kexec_pre_मुक्त_pages(व्योम *vaddr, अचिन्हित पूर्णांक pages) अणु पूर्ण
#पूर्ण_अगर

#अन्यथा /* !CONFIG_KEXEC_CORE */
काष्ठा pt_regs;
काष्ठा task_काष्ठा;
अटल अंतरभूत व्योम __crash_kexec(काष्ठा pt_regs *regs) अणु पूर्ण
अटल अंतरभूत व्योम crash_kexec(काष्ठा pt_regs *regs) अणु पूर्ण
अटल अंतरभूत पूर्णांक kexec_should_crash(काष्ठा task_काष्ठा *p) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kexec_crash_loaded(व्योम) अणु वापस 0; पूर्ण
#घोषणा kexec_in_progress false
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#पूर्ण_अगर /* !defined(__ASSEBMLY__) */

#पूर्ण_अगर /* LINUX_KEXEC_H */
