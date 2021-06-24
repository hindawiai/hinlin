<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Modअगरications by Matt Porter (mporter@mvista.com) to support
 * PPC44x Book E processors.
 *
 * This file contains the routines क्रम initializing the MMU
 * on the 4xx series of chips.
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/code-patching.h>

#समावेश <mm/mmu_decl.h>

/* Used by the 44x TLB replacement exception handler.
 * Just needed it declared someplace.
 */
अचिन्हित पूर्णांक tlb_44x_index; /* = 0 */
अचिन्हित पूर्णांक tlb_44x_hwater = PPC44x_TLB_SIZE - 1 - PPC44x_EARLY_TLBS;
पूर्णांक icache_44x_need_flush;

अचिन्हित दीर्घ tlb_47x_bolपंचांगap[1024/8];

अटल व्योम ppc44x_update_tlb_hwater(व्योम)
अणु
	/* The TLB miss handlers hard codes the watermark in a cmpli
	 * inकाष्ठाion to improve perक्रमmances rather than loading it
	 * from the global variable. Thus, we patch the inकाष्ठाions
	 * in the 2 TLB miss handlers when updating the value
	 */
	modअगरy_inकाष्ठाion_site(&patch__tlb_44x_hwater_D, 0xffff, tlb_44x_hwater);
	modअगरy_inकाष्ठाion_site(&patch__tlb_44x_hwater_I, 0xffff, tlb_44x_hwater);
पूर्ण

/*
 * "Pins" a 256MB TLB entry in AS0 क्रम kernel lowmem क्रम 44x type MMU
 */
अटल व्योम __init ppc44x_pin_tlb(अचिन्हित पूर्णांक virt, अचिन्हित पूर्णांक phys)
अणु
	अचिन्हित पूर्णांक entry = tlb_44x_hwater--;

	ppc44x_update_tlb_hwater();

	mtspr(SPRN_MMUCR, 0);

	__यंत्र__ __अस्थिर__(
		"tlbwe	%2,%3,%4\n"
		"tlbwe	%1,%3,%5\n"
		"tlbwe	%0,%3,%6\n"
	:
	: "r" (PPC44x_TLB_SW | PPC44x_TLB_SR | PPC44x_TLB_SX | PPC44x_TLB_G),
	  "r" (phys),
	  "r" (virt | PPC44x_TLB_VALID | PPC44x_TLB_256M),
	  "r" (entry),
	  "i" (PPC44x_TLB_PAGEID),
	  "i" (PPC44x_TLB_XLAT),
	  "i" (PPC44x_TLB_ATTRIB));
पूर्ण

अटल पूर्णांक __init ppc47x_find_मुक्त_bolted(व्योम)
अणु
	अचिन्हित पूर्णांक mmube0 = mfspr(SPRN_MMUBE0);
	अचिन्हित पूर्णांक mmube1 = mfspr(SPRN_MMUBE1);

	अगर (!(mmube0 & MMUBE0_VBE0))
		वापस 0;
	अगर (!(mmube0 & MMUBE0_VBE1))
		वापस 1;
	अगर (!(mmube0 & MMUBE0_VBE2))
		वापस 2;
	अगर (!(mmube1 & MMUBE1_VBE3))
		वापस 3;
	अगर (!(mmube1 & MMUBE1_VBE4))
		वापस 4;
	अगर (!(mmube1 & MMUBE1_VBE5))
		वापस 5;
	वापस -1;
पूर्ण

अटल व्योम __init ppc47x_update_bolपंचांगap(व्योम)
अणु
	अचिन्हित पूर्णांक mmube0 = mfspr(SPRN_MMUBE0);
	अचिन्हित पूर्णांक mmube1 = mfspr(SPRN_MMUBE1);

	अगर (mmube0 & MMUBE0_VBE0)
		__set_bit((mmube0 >> MMUBE0_IBE0_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
	अगर (mmube0 & MMUBE0_VBE1)
		__set_bit((mmube0 >> MMUBE0_IBE1_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
	अगर (mmube0 & MMUBE0_VBE2)
		__set_bit((mmube0 >> MMUBE0_IBE2_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
	अगर (mmube1 & MMUBE1_VBE3)
		__set_bit((mmube1 >> MMUBE1_IBE3_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
	अगर (mmube1 & MMUBE1_VBE4)
		__set_bit((mmube1 >> MMUBE1_IBE4_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
	अगर (mmube1 & MMUBE1_VBE5)
		__set_bit((mmube1 >> MMUBE1_IBE5_SHIFT) & 0xff,
			  tlb_47x_bolपंचांगap);
पूर्ण

/*
 * "Pins" a 256MB TLB entry in AS0 क्रम kernel lowmem क्रम 47x type MMU
 */
अटल व्योम ppc47x_pin_tlb(अचिन्हित पूर्णांक virt, अचिन्हित पूर्णांक phys)
अणु
	अचिन्हित पूर्णांक rA;
	पूर्णांक bolted;

	/* Base rA is HW way select, way 0, bolted bit set */
	rA = 0x88000000;

	/* Look क्रम a bolted entry slot */
	bolted = ppc47x_find_मुक्त_bolted();
	BUG_ON(bolted < 0);

	/* Insert bolted slot number */
	rA |= bolted << 24;

	pr_debug("256M TLB entry for 0x%08x->0x%08x in bolt slot %d\n",
		 virt, phys, bolted);

	mtspr(SPRN_MMUCR, 0);

	__यंत्र__ __अस्थिर__(
		"tlbwe	%2,%3,0\n"
		"tlbwe	%1,%3,1\n"
		"tlbwe	%0,%3,2\n"
		:
		: "r" (PPC47x_TLB2_SW | PPC47x_TLB2_SR |
		       PPC47x_TLB2_SX
#अगर_घोषित CONFIG_SMP
		       | PPC47x_TLB2_M
#पूर्ण_अगर
		       ),
		  "r" (phys),
		  "r" (virt | PPC47x_TLB0_VALID | PPC47x_TLB0_256M),
		  "r" (rA));
पूर्ण

व्योम __init MMU_init_hw(व्योम)
अणु
	/* This is not useful on 47x but won't hurt either */
	ppc44x_update_tlb_hwater();

	flush_inकाष्ठाion_cache();
पूर्ण

अचिन्हित दीर्घ __init mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ memstart = memstart_addr & ~(PPC_PIN_SIZE - 1);

	/* Pin in enough TLBs to cover any lowmem not covered by the
	 * initial 256M mapping established in head_44x.S */
	क्रम (addr = memstart + PPC_PIN_SIZE; addr < lowmem_end_addr;
	     addr += PPC_PIN_SIZE) अणु
		अगर (mmu_has_feature(MMU_FTR_TYPE_47x))
			ppc47x_pin_tlb(addr + PAGE_OFFSET, addr);
		अन्यथा
			ppc44x_pin_tlb(addr + PAGE_OFFSET, addr);
	पूर्ण
	अगर (mmu_has_feature(MMU_FTR_TYPE_47x)) अणु
		ppc47x_update_bolपंचांगap();

#अगर_घोषित DEBUG
		अणु
			पूर्णांक i;

			prपूर्णांकk(KERN_DEBUG "bolted entries: ");
			क्रम (i = 0; i < 255; i++) अणु
				अगर (test_bit(i, tlb_47x_bolपंचांगap))
					prपूर्णांकk("%d ", i);
			पूर्ण
			prपूर्णांकk("\n");
		पूर्ण
#पूर्ण_अगर /* DEBUG */
	पूर्ण
	वापस total_lowmem;
पूर्ण

व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	u64 size;

#अगर_अघोषित CONFIG_NONSTATIC_KERNEL
	/* We करोn't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);
#पूर्ण_अगर

	/* 44x has a 256M TLB entry pinned at boot */
	size = (min_t(u64, first_memblock_size, PPC_PIN_SIZE));
	memblock_set_current_limit(first_memblock_base + size);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम __init mmu_init_secondary(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ memstart = memstart_addr & ~(PPC_PIN_SIZE - 1);

	/* Pin in enough TLBs to cover any lowmem not covered by the
	 * initial 256M mapping established in head_44x.S
	 *
	 * WARNING: This is called with only the first 256M of the
	 * linear mapping in the TLB and we can't take faults yet
	 * so beware of what this code uses. It runs off a temporary
	 * stack. current (r2) isn't initialized, smp_processor_id()
	 * will not work, current thपढ़ो info isn't accessible, ...
	 */
	क्रम (addr = memstart + PPC_PIN_SIZE; addr < lowmem_end_addr;
	     addr += PPC_PIN_SIZE) अणु
		अगर (mmu_has_feature(MMU_FTR_TYPE_47x))
			ppc47x_pin_tlb(addr + PAGE_OFFSET, addr);
		अन्यथा
			ppc44x_pin_tlb(addr + PAGE_OFFSET, addr);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
