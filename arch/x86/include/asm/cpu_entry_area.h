<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_X86_CPU_ENTRY_AREA_H
#घोषणा _ASM_X86_CPU_ENTRY_AREA_H

#समावेश <linux/percpu-defs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पूर्णांकel_ds.h>
#समावेश <यंत्र/pgtable_areas.h>

#अगर_घोषित CONFIG_X86_64

/* Macro to enक्रमce the same ordering and stack sizes */
#घोषणा ESTACKS_MEMBERS(guardsize, optional_stack_size)		\
	अक्षर	DF_stack_guard[guardsize];			\
	अक्षर	DF_stack[EXCEPTION_STKSZ];			\
	अक्षर	NMI_stack_guard[guardsize];			\
	अक्षर	NMI_stack[EXCEPTION_STKSZ];			\
	अक्षर	DB_stack_guard[guardsize];			\
	अक्षर	DB_stack[EXCEPTION_STKSZ];			\
	अक्षर	MCE_stack_guard[guardsize];			\
	अक्षर	MCE_stack[EXCEPTION_STKSZ];			\
	अक्षर	VC_stack_guard[guardsize];			\
	अक्षर	VC_stack[optional_stack_size];			\
	अक्षर	VC2_stack_guard[guardsize];			\
	अक्षर	VC2_stack[optional_stack_size];			\
	अक्षर	IST_top_guard[guardsize];			\

/* The exception stacks' physical storage. No guard pages required */
काष्ठा exception_stacks अणु
	ESTACKS_MEMBERS(0, 0)
पूर्ण;

/* The effective cpu entry area mapping with guard pages. */
काष्ठा cea_exception_stacks अणु
	ESTACKS_MEMBERS(PAGE_SIZE, EXCEPTION_STKSZ)
पूर्ण;

/*
 * The exception stack ordering in [cea_]exception_stacks
 */
क्रमागत exception_stack_ordering अणु
	ESTACK_DF,
	ESTACK_NMI,
	ESTACK_DB,
	ESTACK_MCE,
	ESTACK_VC,
	ESTACK_VC2,
	N_EXCEPTION_STACKS
पूर्ण;

#घोषणा CEA_ESTACK_SIZE(st)					\
	माप(((काष्ठा cea_exception_stacks *)0)->st## _stack)

#घोषणा CEA_ESTACK_BOT(ceastp, st)				\
	((अचिन्हित दीर्घ)&(ceastp)->st## _stack)

#घोषणा CEA_ESTACK_TOP(ceastp, st)				\
	(CEA_ESTACK_BOT(ceastp, st) + CEA_ESTACK_SIZE(st))

#घोषणा CEA_ESTACK_OFFS(st)					\
	दुरत्व(काष्ठा cea_exception_stacks, st## _stack)

#घोषणा CEA_ESTACK_PAGES					\
	(माप(काष्ठा cea_exception_stacks) / PAGE_SIZE)

#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
काष्ठा द्विगुनfault_stack अणु
	अचिन्हित दीर्घ stack[(PAGE_SIZE - माप(काष्ठा x86_hw_tss)) / माप(अचिन्हित दीर्घ)];
	काष्ठा x86_hw_tss tss;
पूर्ण __aligned(PAGE_SIZE);
#पूर्ण_अगर

/*
 * cpu_entry_area is a percpu region that contains things needed by the CPU
 * and early entry/निकास code.  Real types aren't used क्रम all fields here
 * to aव्योम circular header dependencies.
 *
 * Every field is a भव alias of some other allocated backing store.
 * There is no direct allocation of a काष्ठा cpu_entry_area.
 */
काष्ठा cpu_entry_area अणु
	अक्षर gdt[PAGE_SIZE];

	/*
	 * The GDT is just below entry_stack and thus serves (on x86_64) as
	 * a पढ़ो-only guard page. On 32-bit the GDT must be ग_लिखोable, so
	 * it needs an extra guard page.
	 */
#अगर_घोषित CONFIG_X86_32
	अक्षर guard_entry_stack[PAGE_SIZE];
#पूर्ण_अगर
	काष्ठा entry_stack_page entry_stack_page;

#अगर_घोषित CONFIG_X86_32
	अक्षर guard_द्विगुनfault_stack[PAGE_SIZE];
	काष्ठा द्विगुनfault_stack द्विगुनfault_stack;
#पूर्ण_अगर

	/*
	 * On x86_64, the TSS is mapped RO.  On x86_32, it's mapped RW because
	 * we need task चयनes to work, and task चयनes ग_लिखो to the TSS.
	 */
	काष्ठा tss_काष्ठा tss;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Exception stacks used क्रम IST entries with guard pages.
	 */
	काष्ठा cea_exception_stacks estacks;
#पूर्ण_अगर
	/*
	 * Per CPU debug store क्रम Intel perक्रमmance monitoring. Wastes a
	 * full page at the moment.
	 */
	काष्ठा debug_store cpu_debug_store;
	/*
	 * The actual PEBS/BTS buffers must be mapped to user space
	 * Reserve enough fixmap PTEs.
	 */
	काष्ठा debug_store_buffers cpu_debug_buffers;
पूर्ण;

#घोषणा CPU_ENTRY_AREA_SIZE		(माप(काष्ठा cpu_entry_area))
#घोषणा CPU_ENTRY_AREA_ARRAY_SIZE	(CPU_ENTRY_AREA_SIZE * NR_CPUS)

/* Total size includes the पढ़ोonly IDT mapping page as well: */
#घोषणा CPU_ENTRY_AREA_TOTAL_SIZE	(CPU_ENTRY_AREA_ARRAY_SIZE + PAGE_SIZE)

DECLARE_PER_CPU(काष्ठा cpu_entry_area *, cpu_entry_area);
DECLARE_PER_CPU(काष्ठा cea_exception_stacks *, cea_exception_stacks);

बाह्य व्योम setup_cpu_entry_areas(व्योम);
बाह्य व्योम cea_set_pte(व्योम *cea_vaddr, phys_addr_t pa, pgprot_t flags);

बाह्य काष्ठा cpu_entry_area *get_cpu_entry_area(पूर्णांक cpu);

अटल अंतरभूत काष्ठा entry_stack *cpu_entry_stack(पूर्णांक cpu)
अणु
	वापस &get_cpu_entry_area(cpu)->entry_stack_page.stack;
पूर्ण

#घोषणा __this_cpu_ist_top_va(name)					\
	CEA_ESTACK_TOP(__this_cpu_पढ़ो(cea_exception_stacks), name)

#घोषणा __this_cpu_ist_bottom_va(name)					\
	CEA_ESTACK_BOT(__this_cpu_पढ़ो(cea_exception_stacks), name)

#पूर्ण_अगर
