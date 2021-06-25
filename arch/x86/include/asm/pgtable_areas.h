<शैली गुरु>
#अगर_अघोषित _ASM_X86_PGTABLE_AREAS_H
#घोषणा _ASM_X86_PGTABLE_AREAS_H

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/pgtable_32_areas.h>
#पूर्ण_अगर

/* Single page reserved क्रम the पढ़ोonly IDT mapping: */
#घोषणा CPU_ENTRY_AREA_RO_IDT		CPU_ENTRY_AREA_BASE
#घोषणा CPU_ENTRY_AREA_PER_CPU		(CPU_ENTRY_AREA_RO_IDT + PAGE_SIZE)

#घोषणा CPU_ENTRY_AREA_RO_IDT_VADDR	((व्योम *)CPU_ENTRY_AREA_RO_IDT)

#घोषणा CPU_ENTRY_AREA_MAP_SIZE		(CPU_ENTRY_AREA_PER_CPU + CPU_ENTRY_AREA_ARRAY_SIZE - CPU_ENTRY_AREA_BASE)

#पूर्ण_अगर /* _ASM_X86_PGTABLE_AREAS_H */
