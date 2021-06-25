<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_X86_REALMODE_H
#घोषणा _ARCH_X86_REALMODE_H

/*
 * Flag bit definitions क्रम use with the flags field of the trampoline header
 * in the CONFIG_X86_64 variant.
 */
#घोषणा TH_FLAGS_SME_ACTIVE_BIT		0
#घोषणा TH_FLAGS_SME_ACTIVE		BIT(TH_FLAGS_SME_ACTIVE_BIT)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>

/* This must match data at realmode/rm/header.S */
काष्ठा real_mode_header अणु
	u32	text_start;
	u32	ro_end;
	/* SMP trampoline */
	u32	trampoline_start;
	u32	trampoline_header;
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	u32	sev_es_trampoline_start;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_64
	u32	trampoline_pgd;
#पूर्ण_अगर
	/* ACPI S3 wakeup */
#अगर_घोषित CONFIG_ACPI_SLEEP
	u32	wakeup_start;
	u32	wakeup_header;
#पूर्ण_अगर
	/* APM/BIOS reboot */
	u32	machine_real_restart_यंत्र;
#अगर_घोषित CONFIG_X86_64
	u32	machine_real_restart_seg;
#पूर्ण_अगर
पूर्ण;

/* This must match data at realmode/rm/trampoline_अणु32,64पूर्ण.S */
काष्ठा trampoline_header अणु
#अगर_घोषित CONFIG_X86_32
	u32 start;
	u16 gdt_pad;
	u16 gdt_limit;
	u32 gdt_base;
#अन्यथा
	u64 start;
	u64 efer;
	u32 cr4;
	u32 flags;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा real_mode_header *real_mode_header;
बाह्य अचिन्हित अक्षर real_mode_blob_end[];

बाह्य अचिन्हित दीर्घ initial_code;
बाह्य अचिन्हित दीर्घ initial_gs;
बाह्य अचिन्हित दीर्घ initial_stack;
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
बाह्य अचिन्हित दीर्घ initial_vc_handler;
#पूर्ण_अगर

बाह्य अचिन्हित अक्षर real_mode_blob[];
बाह्य अचिन्हित अक्षर real_mode_relocs[];

#अगर_घोषित CONFIG_X86_32
बाह्य अचिन्हित अक्षर startup_32_smp[];
बाह्य अचिन्हित अक्षर boot_gdt[];
#अन्यथा
बाह्य अचिन्हित अक्षर secondary_startup_64[];
बाह्य अचिन्हित अक्षर secondary_startup_64_no_verअगरy[];
#पूर्ण_अगर

अटल अंतरभूत माप_प्रकार real_mode_size_needed(व्योम)
अणु
	अगर (real_mode_header)
		वापस 0;	/* alपढ़ोy allocated. */

	वापस ALIGN(real_mode_blob_end - real_mode_blob, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम set_real_mode_mem(phys_addr_t mem)
अणु
	real_mode_header = (काष्ठा real_mode_header *) __va(mem);
पूर्ण

व्योम reserve_real_mode(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ARCH_X86_REALMODE_H */
