<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/nmi.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/vदो_स्मृति.h>

अचिन्हित पूर्णांक __VMALLOC_RESERVE = 128 << 20;

/*
 * Associate a भव page frame with a given physical page frame 
 * and protection flags क्रम that frame.
 */ 
व्योम set_pte_vaddr(अचिन्हित दीर्घ vaddr, pte_t pteval)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = swapper_pg_dir + pgd_index(vaddr);
	अगर (pgd_none(*pgd)) अणु
		BUG();
		वापस;
	पूर्ण
	p4d = p4d_offset(pgd, vaddr);
	अगर (p4d_none(*p4d)) अणु
		BUG();
		वापस;
	पूर्ण
	pud = pud_offset(p4d, vaddr);
	अगर (pud_none(*pud)) अणु
		BUG();
		वापस;
	पूर्ण
	pmd = pmd_offset(pud, vaddr);
	अगर (pmd_none(*pmd)) अणु
		BUG();
		वापस;
	पूर्ण
	pte = pte_offset_kernel(pmd, vaddr);
	अगर (!pte_none(pteval))
		set_pte_at(&init_mm, vaddr, pte, pteval);
	अन्यथा
		pte_clear(&init_mm, vaddr, pte);

	/*
	 * It's enough to flush this one mapping.
	 * (PGE mappings get flushed as well)
	 */
	flush_tlb_one_kernel(vaddr);
पूर्ण

अचिन्हित दीर्घ __FIXADDR_TOP = 0xfffff000;
EXPORT_SYMBOL(__FIXADDR_TOP);

/*
 * vदो_स्मृति=size क्रमces the vदो_स्मृति area to be exactly 'size'
 * bytes. This can be used to increase (or decrease) the
 * vदो_स्मृति area - the शेष is 128m.
 */
अटल पूर्णांक __init parse_vदो_स्मृति(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	/* Add VMALLOC_OFFSET to the parsed value due to vm area guard hole*/
	__VMALLOC_RESERVE = memparse(arg, &arg) + VMALLOC_OFFSET;
	वापस 0;
पूर्ण
early_param("vmalloc", parse_vदो_स्मृति);

/*
 * reservetop=size reserves a hole at the top of the kernel address space which
 * a hypervisor can load पूर्णांकo later.  Needed क्रम dynamically loaded hypervisors,
 * so relocating the fixmap can be करोne beक्रमe paging initialization.
 */
अटल पूर्णांक __init parse_reservetop(अक्षर *arg)
अणु
	अचिन्हित दीर्घ address;

	अगर (!arg)
		वापस -EINVAL;

	address = memparse(arg, &arg);
	reserve_top_address(address);
	early_ioremap_init();
	वापस 0;
पूर्ण
early_param("reservetop", parse_reservetop);
