<शैली गुरु>
#समावेश <linux/efi.h>
#समावेश <यंत्र/e820/types.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/efi.h>
#समावेश "pgtable.h"
#समावेश "../string.h"

#घोषणा BIOS_START_MIN		0x20000U	/* 128K, less than this is insane */
#घोषणा BIOS_START_MAX		0x9f000U	/* 640K, असलolute maximum */

#अगर_घोषित CONFIG_X86_5LEVEL
/* __pgtable_l5_enabled needs to be in .data to aव्योम being cleared aदीर्घ with .bss */
अचिन्हित पूर्णांक __section(".data") __pgtable_l5_enabled;
अचिन्हित पूर्णांक __section(".data") pgdir_shअगरt = 39;
अचिन्हित पूर्णांक __section(".data") ptrs_per_p4d = 1;
#पूर्ण_अगर

काष्ठा paging_config अणु
	अचिन्हित दीर्घ trampoline_start;
	अचिन्हित दीर्घ l5_required;
पूर्ण;

/* Buffer to preserve trampoline memory */
अटल अक्षर trampoline_save[TRAMPOLINE_32BIT_SIZE];

/*
 * Trampoline address will be prपूर्णांकed by extract_kernel() क्रम debugging
 * purposes.
 *
 * Aव्योम putting the poपूर्णांकer पूर्णांकo .bss as it will be cleared between
 * paging_prepare() and extract_kernel().
 */
अचिन्हित दीर्घ *trampoline_32bit __section(".data");

बाह्य काष्ठा boot_params *boot_params;
पूर्णांक cmdline_find_option_bool(स्थिर अक्षर *option);

अटल अचिन्हित दीर्घ find_trampoline_placement(व्योम)
अणु
	अचिन्हित दीर्घ bios_start = 0, ebda_start = 0;
	काष्ठा boot_e820_entry *entry;
	अक्षर *signature;
	पूर्णांक i;

	/*
	 * Find a suitable spot क्रम the trampoline.
	 * This code is based on reserve_bios_regions().
	 */

	/*
	 * EFI प्रणालीs may not provide legacy ROM. The memory may not be mapped
	 * at all.
	 *
	 * Only look क्रम values in the legacy ROM क्रम non-EFI प्रणाली.
	 */
	signature = (अक्षर *)&boot_params->efi_info.efi_loader_signature;
	अगर (म_भेदन(signature, EFI32_LOADER_SIGNATURE, 4) &&
	    म_भेदन(signature, EFI64_LOADER_SIGNATURE, 4)) अणु
		ebda_start = *(अचिन्हित लघु *)0x40e << 4;
		bios_start = *(अचिन्हित लघु *)0x413 << 10;
	पूर्ण

	अगर (bios_start < BIOS_START_MIN || bios_start > BIOS_START_MAX)
		bios_start = BIOS_START_MAX;

	अगर (ebda_start > BIOS_START_MIN && ebda_start < bios_start)
		bios_start = ebda_start;

	bios_start = round_करोwn(bios_start, PAGE_SIZE);

	/* Find the first usable memory region under bios_start. */
	क्रम (i = boot_params->e820_entries - 1; i >= 0; i--) अणु
		अचिन्हित दीर्घ new = bios_start;

		entry = &boot_params->e820_table[i];

		/* Skip all entries above bios_start. */
		अगर (bios_start <= entry->addr)
			जारी;

		/* Skip non-RAM entries. */
		अगर (entry->type != E820_TYPE_RAM)
			जारी;

		/* Adjust bios_start to the end of the entry अगर needed. */
		अगर (bios_start > entry->addr + entry->size)
			new = entry->addr + entry->size;

		/* Keep bios_start page-aligned. */
		new = round_करोwn(new, PAGE_SIZE);

		/* Skip the entry अगर it's too small. */
		अगर (new - TRAMPOLINE_32BIT_SIZE < entry->addr)
			जारी;

		/* Protect against underflow. */
		अगर (new - TRAMPOLINE_32BIT_SIZE > bios_start)
			अवरोध;

		bios_start = new;
		अवरोध;
	पूर्ण

	/* Place the trampoline just below the end of low memory */
	वापस bios_start - TRAMPOLINE_32BIT_SIZE;
पूर्ण

काष्ठा paging_config paging_prepare(व्योम *rmode)
अणु
	काष्ठा paging_config paging_config = अणुपूर्ण;

	/* Initialize boot_params. Required क्रम cmdline_find_option_bool(). */
	boot_params = rmode;

	/*
	 * Check अगर LA57 is desired and supported.
	 *
	 * There are several parts to the check:
	 *   - अगर the kernel supports 5-level paging: CONFIG_X86_5LEVEL=y
	 *   - अगर user asked to disable 5-level paging: no5lvl in cmdline
	 *   - अगर the machine supports 5-level paging:
	 *     + CPUID leaf 7 is supported
	 *     + the leaf has the feature bit set
	 *
	 * That's substitute क्रम boot_cpu_has() in early boot code.
	 */
	अगर (IS_ENABLED(CONFIG_X86_5LEVEL) &&
			!cmdline_find_option_bool("no5lvl") &&
			native_cpuid_eax(0) >= 7 &&
			(native_cpuid_ecx(7) & (1 << (X86_FEATURE_LA57 & 31)))) अणु
		paging_config.l5_required = 1;
	पूर्ण

	paging_config.trampoline_start = find_trampoline_placement();

	trampoline_32bit = (अचिन्हित दीर्घ *)paging_config.trampoline_start;

	/* Preserve trampoline memory */
	स_नकल(trampoline_save, trampoline_32bit, TRAMPOLINE_32BIT_SIZE);

	/* Clear trampoline memory first */
	स_रखो(trampoline_32bit, 0, TRAMPOLINE_32BIT_SIZE);

	/* Copy trampoline code in place */
	स_नकल(trampoline_32bit + TRAMPOLINE_32BIT_CODE_OFFSET / माप(अचिन्हित दीर्घ),
			&trampoline_32bit_src, TRAMPOLINE_32BIT_CODE_SIZE);

	/*
	 * The code below prepares page table in trampoline memory.
	 *
	 * The new page table will be used by trampoline code क्रम चयनing
	 * from 4- to 5-level paging or vice versa.
	 *
	 * If चयनing is not required, the page table is unused: trampoline
	 * code wouldn't touch CR3.
	 */

	/*
	 * We are not going to use the page table in trampoline memory अगर we
	 * are alपढ़ोy in the desired paging mode.
	 */
	अगर (paging_config.l5_required == !!(native_पढ़ो_cr4() & X86_CR4_LA57))
		जाओ out;

	अगर (paging_config.l5_required) अणु
		/*
		 * For 4- to 5-level paging transition, set up current CR3 as
		 * the first and the only entry in a new top-level page table.
		 */
		trampoline_32bit[TRAMPOLINE_32BIT_PGTABLE_OFFSET] = __native_पढ़ो_cr3() | _PAGE_TABLE_NOENC;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ src;

		/*
		 * For 5- to 4-level paging transition, copy page table poपूर्णांकed
		 * by first entry in the current top-level page table as our
		 * new top-level page table.
		 *
		 * We cannot just poपूर्णांक to the page table from trampoline as it
		 * may be above 4G.
		 */
		src = *(अचिन्हित दीर्घ *)__native_पढ़ो_cr3() & PAGE_MASK;
		स_नकल(trampoline_32bit + TRAMPOLINE_32BIT_PGTABLE_OFFSET / माप(अचिन्हित दीर्घ),
		       (व्योम *)src, PAGE_SIZE);
	पूर्ण

out:
	वापस paging_config;
पूर्ण

व्योम cleanup_trampoline(व्योम *pgtable)
अणु
	व्योम *trampoline_pgtable;

	trampoline_pgtable = trampoline_32bit + TRAMPOLINE_32BIT_PGTABLE_OFFSET / माप(अचिन्हित दीर्घ);

	/*
	 * Move the top level page table out of trampoline memory,
	 * अगर it's there.
	 */
	अगर ((व्योम *)__native_पढ़ो_cr3() == trampoline_pgtable) अणु
		स_नकल(pgtable, trampoline_pgtable, PAGE_SIZE);
		native_ग_लिखो_cr3((अचिन्हित दीर्घ)pgtable);
	पूर्ण

	/* Restore trampoline memory */
	स_नकल(trampoline_32bit, trampoline_save, TRAMPOLINE_32BIT_SIZE);

	/* Initialize variables क्रम 5-level paging */
#अगर_घोषित CONFIG_X86_5LEVEL
	अगर (__पढ़ो_cr4() & X86_CR4_LA57) अणु
		__pgtable_l5_enabled = 1;
		pgdir_shअगरt = 48;
		ptrs_per_p4d = 512;
	पूर्ण
#पूर्ण_अगर
पूर्ण
