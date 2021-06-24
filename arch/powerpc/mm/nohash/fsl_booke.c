<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Modअगरications by Kumar Gala (galak@kernel.crashing.org) to support
 * E500 Book E processors.
 *
 * Copyright 2004,2010 Freescale Semiconductor, Inc.
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

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/paca.h>

#समावेश <mm/mmu_decl.h>

अचिन्हित पूर्णांक tlbcam_index;

#घोषणा NUM_TLBCAMS	(64)
काष्ठा tlbcam TLBCAM[NUM_TLBCAMS];

काष्ठा tlbcamrange अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ limit;
	phys_addr_t phys;
पूर्ण tlbcam_addrs[NUM_TLBCAMS];

अचिन्हित दीर्घ tlbcam_sz(पूर्णांक idx)
अणु
	वापस tlbcam_addrs[idx].limit - tlbcam_addrs[idx].start + 1;
पूर्ण

#अगर_घोषित CONFIG_FSL_BOOKE
/*
 * Return PA क्रम this VA अगर it is mapped by a CAM, or 0
 */
phys_addr_t v_block_mapped(अचिन्हित दीर्घ va)
अणु
	पूर्णांक b;
	क्रम (b = 0; b < tlbcam_index; ++b)
		अगर (va >= tlbcam_addrs[b].start && va < tlbcam_addrs[b].limit)
			वापस tlbcam_addrs[b].phys + (va - tlbcam_addrs[b].start);
	वापस 0;
पूर्ण

/*
 * Return VA क्रम a given PA or 0 अगर not mapped
 */
अचिन्हित दीर्घ p_block_mapped(phys_addr_t pa)
अणु
	पूर्णांक b;
	क्रम (b = 0; b < tlbcam_index; ++b)
		अगर (pa >= tlbcam_addrs[b].phys
			&& pa < (tlbcam_addrs[b].limit-tlbcam_addrs[b].start)
		              +tlbcam_addrs[b].phys)
			वापस tlbcam_addrs[b].start+(pa-tlbcam_addrs[b].phys);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Set up a variable-size TLB entry (tlbcam). The parameters are not checked;
 * in particular size must be a घातer of 4 between 4k and the max supported by
 * an implementation; max may further be limited by what can be represented in
 * an अचिन्हित दीर्घ (क्रम example, 32-bit implementations cannot support a 4GB
 * size).
 */
अटल व्योम settlbcam(पूर्णांक index, अचिन्हित दीर्घ virt, phys_addr_t phys,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक pid)
अणु
	अचिन्हित पूर्णांक tsize;

	tsize = __ilog2(size) - 10;

#अगर defined(CONFIG_SMP) || defined(CONFIG_PPC_E500MC)
	अगर ((flags & _PAGE_NO_CACHE) == 0)
		flags |= _PAGE_COHERENT;
#पूर्ण_अगर

	TLBCAM[index].MAS0 = MAS0_TLBSEL(1) | MAS0_ESEL(index) | MAS0_NV(index+1);
	TLBCAM[index].MAS1 = MAS1_VALID | MAS1_IPROT | MAS1_TSIZE(tsize) | MAS1_TID(pid);
	TLBCAM[index].MAS2 = virt & PAGE_MASK;

	TLBCAM[index].MAS2 |= (flags & _PAGE_WRITETHRU) ? MAS2_W : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_NO_CACHE) ? MAS2_I : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_COHERENT) ? MAS2_M : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_GUARDED) ? MAS2_G : 0;
	TLBCAM[index].MAS2 |= (flags & _PAGE_ENDIAN) ? MAS2_E : 0;

	TLBCAM[index].MAS3 = (phys & MAS3_RPN) | MAS3_SX | MAS3_SR;
	TLBCAM[index].MAS3 |= ((flags & _PAGE_RW) ? MAS3_SW : 0);
	अगर (mmu_has_feature(MMU_FTR_BIG_PHYS))
		TLBCAM[index].MAS7 = (u64)phys >> 32;

	/* Below is unlikely -- only क्रम large user pages or similar */
	अगर (pte_user(__pte(flags))) अणु
	   TLBCAM[index].MAS3 |= MAS3_UX | MAS3_UR;
	   TLBCAM[index].MAS3 |= ((flags & _PAGE_RW) ? MAS3_UW : 0);
	पूर्ण

	tlbcam_addrs[index].start = virt;
	tlbcam_addrs[index].limit = virt + size - 1;
	tlbcam_addrs[index].phys = phys;
पूर्ण

अचिन्हित दीर्घ calc_cam_sz(अचिन्हित दीर्घ ram, अचिन्हित दीर्घ virt,
			  phys_addr_t phys)
अणु
	अचिन्हित पूर्णांक camsize = __ilog2(ram);
	अचिन्हित पूर्णांक align = __ffs(virt | phys);
	अचिन्हित दीर्घ max_cam;

	अगर ((mfspr(SPRN_MMUCFG) & MMUCFG_MAVN) == MMUCFG_MAVN_V1) अणु
		/* Convert (4^max) kB to (2^max) bytes */
		max_cam = ((mfspr(SPRN_TLB1CFG) >> 16) & 0xf) * 2 + 10;
		camsize &= ~1U;
		align &= ~1U;
	पूर्ण अन्यथा अणु
		/* Convert (2^max) kB to (2^max) bytes */
		max_cam = __ilog2(mfspr(SPRN_TLB1PS)) + 10;
	पूर्ण

	अगर (camsize > align)
		camsize = align;
	अगर (camsize > max_cam)
		camsize = max_cam;

	वापस 1UL << camsize;
पूर्ण

अटल अचिन्हित दीर्घ map_mem_in_cams_addr(phys_addr_t phys, अचिन्हित दीर्घ virt,
					अचिन्हित दीर्घ ram, पूर्णांक max_cam_idx,
					bool dryrun)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ amount_mapped = 0;

	/* Calculate CAM values */
	क्रम (i = 0; ram && i < max_cam_idx; i++) अणु
		अचिन्हित दीर्घ cam_sz;

		cam_sz = calc_cam_sz(ram, virt, phys);
		अगर (!dryrun)
			settlbcam(i, virt, phys, cam_sz,
				  pgprot_val(PAGE_KERNEL_X), 0);

		ram -= cam_sz;
		amount_mapped += cam_sz;
		virt += cam_sz;
		phys += cam_sz;
	पूर्ण

	अगर (dryrun)
		वापस amount_mapped;

	loadcam_multi(0, i, max_cam_idx);
	tlbcam_index = i;

#अगर_घोषित CONFIG_PPC64
	get_paca()->tcd.esel_next = i;
	get_paca()->tcd.esel_max = mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY;
	get_paca()->tcd.esel_first = i;
#पूर्ण_अगर

	वापस amount_mapped;
पूर्ण

अचिन्हित दीर्घ map_mem_in_cams(अचिन्हित दीर्घ ram, पूर्णांक max_cam_idx, bool dryrun)
अणु
	अचिन्हित दीर्घ virt = PAGE_OFFSET;
	phys_addr_t phys = memstart_addr;

	वापस map_mem_in_cams_addr(phys, virt, ram, max_cam_idx, dryrun);
पूर्ण

#अगर_घोषित CONFIG_PPC32

#अगर defined(CONFIG_LOWMEM_CAM_NUM_BOOL) && (CONFIG_LOWMEM_CAM_NUM >= NUM_TLBCAMS)
#त्रुटि "LOWMEM_CAM_NUM must be less than NUM_TLBCAMS"
#पूर्ण_अगर

अचिन्हित दीर्घ __init mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	वापस tlbcam_addrs[tlbcam_index - 1].limit - PAGE_OFFSET + 1;
पूर्ण

व्योम flush_inकाष्ठाion_cache(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = mfspr(SPRN_L1CSR1);
	पंचांगp |= L1CSR1_ICFI | L1CSR1_ICLFR;
	mtspr(SPRN_L1CSR1, पंचांगp);
	isync();
पूर्ण

/*
 * MMU_init_hw करोes the chip-specअगरic initialization of the MMU hardware.
 */
व्योम __init MMU_init_hw(व्योम)
अणु
	flush_inकाष्ठाion_cache();
पूर्ण

व्योम __init adjust_total_lowmem(व्योम)
अणु
	अचिन्हित दीर्घ ram;
	पूर्णांक i;

	/* adjust lowmem size to __max_low_memory */
	ram = min((phys_addr_t)__max_low_memory, (phys_addr_t)total_lowmem);

	i = चयन_to_as1();
	__max_low_memory = map_mem_in_cams(ram, CONFIG_LOWMEM_CAM_NUM, false);
	restore_to_as0(i, 0, 0, 1);

	pr_info("Memory CAM mapping: ");
	क्रम (i = 0; i < tlbcam_index - 1; i++)
		pr_cont("%lu/", tlbcam_sz(i) >> 20);
	pr_cont("%lu Mb, residual: %dMb\n", tlbcam_sz(tlbcam_index - 1) >> 20,
	        (अचिन्हित पूर्णांक)((total_lowmem - __max_low_memory) >> 20));

	memblock_set_current_limit(memstart_addr + __max_low_memory);
पूर्ण

व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	phys_addr_t limit = first_memblock_base + first_memblock_size;

	/* 64M mapped initially according to head_fsl_booke.S */
	memblock_set_current_limit(min_t(u64, limit, 0x04000000));
पूर्ण

#अगर_घोषित CONFIG_RELOCATABLE
पूर्णांक __initdata is_second_reloc;
notrace व्योम __init relocate_init(u64 dt_ptr, phys_addr_t start)
अणु
	अचिन्हित दीर्घ base = kernstart_virt_addr;
	phys_addr_t size;

	kernstart_addr = start;
	अगर (is_second_reloc) अणु
		virt_phys_offset = PAGE_OFFSET - memstart_addr;
		kaslr_late_init();
		वापस;
	पूर्ण

	/*
	 * Relocatable kernel support based on processing of dynamic
	 * relocation entries. Beक्रमe we get the real memstart_addr,
	 * We will compute the virt_phys_offset like this:
	 * virt_phys_offset = stext.run - kernstart_addr
	 *
	 * stext.run = (KERNELBASE & ~0x3ffffff) +
	 *				(kernstart_addr & 0x3ffffff)
	 * When we relocate, we have :
	 *
	 *	(kernstart_addr & 0x3ffffff) = (stext.run & 0x3ffffff)
	 *
	 * hence:
	 *  virt_phys_offset = (KERNELBASE & ~0x3ffffff) -
	 *                              (kernstart_addr & ~0x3ffffff)
	 *
	 */
	start &= ~0x3ffffff;
	base &= ~0x3ffffff;
	virt_phys_offset = base - start;
	early_get_first_memblock_info(__va(dt_ptr), &size);
	/*
	 * We now get the memstart_addr, then we should check अगर this
	 * address is the same as what the PAGE_OFFSET map to now. If
	 * not we have to change the map of PAGE_OFFSET to memstart_addr
	 * and करो a second relocation.
	 */
	अगर (start != memstart_addr) अणु
		पूर्णांक n;
		दीर्घ offset = start - memstart_addr;

		is_second_reloc = 1;
		n = चयन_to_as1();
		/* map a 64M area क्रम the second relocation */
		अगर (memstart_addr > start)
			map_mem_in_cams(0x4000000, CONFIG_LOWMEM_CAM_NUM,
					false);
		अन्यथा
			map_mem_in_cams_addr(start, PAGE_OFFSET + offset,
					0x4000000, CONFIG_LOWMEM_CAM_NUM,
					false);
		restore_to_as0(n, offset, __va(dt_ptr), 1);
		/* We should never reach here */
		panic("Relocation error");
	पूर्ण

	kaslr_early_init(__va(dt_ptr), size);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
