<शैली गुरु>
#अगर_अघोषित _ASM_X86_PGTABLE_32_AREAS_H
#घोषणा _ASM_X86_PGTABLE_32_AREAS_H

#समावेश <यंत्र/cpu_entry_area.h>

/*
 * Just any arbitrary offset to the start of the vदो_स्मृति VM area: the
 * current 8MB value just means that there will be a 8MB "hole" after the
 * physical memory until the kernel भव memory starts.  That means that
 * any out-of-bounds memory accesses will hopefully be caught.
 * The vदो_स्मृति() routines leaves a hole of 4kB between each vदो_स्मृतिed
 * area क्रम the same reason. ;)
 */
#घोषणा VMALLOC_OFFSET	(8 * 1024 * 1024)

#अगर_अघोषित __ASSEMBLY__
बाह्य bool __vदो_स्मृति_start_set; /* set once high_memory is set */
#पूर्ण_अगर

#घोषणा VMALLOC_START	((अचिन्हित दीर्घ)high_memory + VMALLOC_OFFSET)
#अगर_घोषित CONFIG_X86_PAE
#घोषणा LAST_PKMAP 512
#अन्यथा
#घोषणा LAST_PKMAP 1024
#पूर्ण_अगर

#घोषणा CPU_ENTRY_AREA_PAGES		(NR_CPUS * DIV_ROUND_UP(माप(काष्ठा cpu_entry_area), PAGE_SIZE))

/* The +1 is क्रम the पढ़ोonly IDT page: */
#घोषणा CPU_ENTRY_AREA_BASE	\
	((FIXADDR_TOT_START - PAGE_SIZE*(CPU_ENTRY_AREA_PAGES+1)) & PMD_MASK)

#घोषणा LDT_BASE_ADDR		\
	((CPU_ENTRY_AREA_BASE - PAGE_SIZE) & PMD_MASK)

#घोषणा LDT_END_ADDR		(LDT_BASE_ADDR + PMD_SIZE)

#घोषणा PKMAP_BASE		\
	((LDT_BASE_ADDR - PAGE_SIZE) & PMD_MASK)

#अगर_घोषित CONFIG_HIGHMEM
# define VMALLOC_END	(PKMAP_BASE - 2 * PAGE_SIZE)
#अन्यथा
# define VMALLOC_END	(LDT_BASE_ADDR - 2 * PAGE_SIZE)
#पूर्ण_अगर

#घोषणा MODULES_VADDR	VMALLOC_START
#घोषणा MODULES_END	VMALLOC_END
#घोषणा MODULES_LEN	(MODULES_VADDR - MODULES_END)

#घोषणा MAXMEM	(VMALLOC_END - PAGE_OFFSET - __VMALLOC_RESERVE)

#पूर्ण_अगर /* _ASM_X86_PGTABLE_32_AREAS_H */
