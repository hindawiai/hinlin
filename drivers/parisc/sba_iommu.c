<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
**  System Bus Adapter (SBA) I/O MMU manager
**
**	(c) Copyright 2000-2004 Grant Grundler <grundler @ parisc-linux x org>
**	(c) Copyright 2004 Naresh Kumar Inna <knaresh at india x hp x com>
**	(c) Copyright 2000-2004 Hewlett-Packard Company
**
**	Portions (c) 1999 Dave S. Miller (from sparc64 I/O MMU code)
**
**
**
** This module initializes the IOC (I/O Controller) found on B1000/C3000/
** J5000/J7000/N-class/L-class machines and their successors.
**
** FIXME: add DMA hपूर्णांक support programming in both sba and lba modules.
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>

#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/iommu-helper.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>		/* क्रम DMA_CHUNK_SIZE */

#समावेश <यंत्र/hardware.h>	/* क्रम रेजिस्टर_parisc_driver() stuff */

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/ropes.h>
#समावेश <यंत्र/mckinley.h>	/* क्रम proc_mckinley_root */
#समावेश <यंत्र/runway.h>		/* क्रम proc_runway_root */
#समावेश <यंत्र/page.h>		/* क्रम PAGE0 */
#समावेश <यंत्र/pdc.h>		/* क्रम PDC_MODEL_* */
#समावेश <यंत्र/pdcpat.h>		/* क्रम is_pdc_pat() */
#समावेश <यंत्र/parisc-device.h>

#समावेश "iommu.h"

#घोषणा MODULE_NAME "SBA"

/*
** The number of debug flags is a clue - this code is fragile.
** Don't even think about messing with it unless you have
** plenty of 710's to sacrअगरice to the computer gods. :^)
*/
#अघोषित DEBUG_SBA_INIT
#अघोषित DEBUG_SBA_RUN
#अघोषित DEBUG_SBA_RUN_SG
#अघोषित DEBUG_SBA_RESOURCE
#अघोषित ASSERT_Pसूची_SANITY
#अघोषित DEBUG_LARGE_SG_ENTRIES
#अघोषित DEBUG_DMB_TRAP

#अगर_घोषित DEBUG_SBA_INIT
#घोषणा DBG_INIT(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_INIT(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_SBA_RUN
#घोषणा DBG_RUN(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RUN(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_SBA_RUN_SG
#घोषणा DBG_RUN_SG(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RUN_SG(x...)
#पूर्ण_अगर


#अगर_घोषित DEBUG_SBA_RESOURCE
#घोषणा DBG_RES(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RES(x...)
#पूर्ण_अगर

#घोषणा SBA_INLINE	__अंतरभूत__

#घोषणा DEFAULT_DMA_HINT_REG	0

काष्ठा sba_device *sba_list;
EXPORT_SYMBOL_GPL(sba_list);

अटल अचिन्हित दीर्घ ioc_needs_fdc = 0;

/* global count of IOMMUs in the प्रणाली */
अटल अचिन्हित पूर्णांक global_ioc_cnt = 0;

/* PA8700 (Piranha 2.2) bug workaround */
अटल अचिन्हित दीर्घ piranha_bad_128k = 0;

/* Looks nice and keeps the compiler happy */
#घोषणा SBA_DEV(d) ((काष्ठा sba_device *) (d))

#अगर_घोषित CONFIG_AGP_PARISC
#घोषणा SBA_AGP_SUPPORT
#पूर्ण_अगर /*CONFIG_AGP_PARISC*/

#अगर_घोषित SBA_AGP_SUPPORT
अटल पूर्णांक sba_reserve_agpgart = 1;
module_param(sba_reserve_agpgart, पूर्णांक, 0444);
MODULE_PARM_DESC(sba_reserve_agpgart, "Reserve half of IO pdir as AGPGART");
#पूर्ण_अगर


/************************************
** SBA रेजिस्टर पढ़ो and ग_लिखो support
**
** BE WARNED: रेजिस्टर ग_लिखोs are posted.
**  (ie follow ग_लिखोs which must reach HW with a पढ़ो)
**
** Superकरोme (in particular, REO) allows only 64-bit CSR accesses.
*/
#घोषणा READ_REG32(addr)	पढ़ोl(addr)
#घोषणा READ_REG64(addr)	पढ़ोq(addr)
#घोषणा WRITE_REG32(val, addr)	ग_लिखोl((val), (addr))
#घोषणा WRITE_REG64(val, addr)	ग_लिखोq((val), (addr))

#अगर_घोषित CONFIG_64BIT
#घोषणा READ_REG(addr)		READ_REG64(addr)
#घोषणा WRITE_REG(value, addr)	WRITE_REG64(value, addr)
#अन्यथा
#घोषणा READ_REG(addr)		READ_REG32(addr)
#घोषणा WRITE_REG(value, addr)	WRITE_REG32(value, addr)
#पूर्ण_अगर

#अगर_घोषित DEBUG_SBA_INIT

/* NOTE: When CONFIG_64BIT isn't defined, READ_REG64() is two 32-bit पढ़ोs */

/**
 * sba_dump_ranges - debugging only - prपूर्णांक ranges asचिन्हित to this IOA
 * @hpa: base address of the sba
 *
 * Prपूर्णांक the MMIO and IO Port address ranges क्रमwarded by an Astro/Ike/RIO
 * IO Adapter (aka Bus Converter).
 */
अटल व्योम
sba_dump_ranges(व्योम __iomem *hpa)
अणु
	DBG_INIT("SBA at 0x%p\n", hpa);
	DBG_INIT("IOS_DIST_BASE   : %Lx\n", READ_REG64(hpa+IOS_DIST_BASE));
	DBG_INIT("IOS_DIST_MASK   : %Lx\n", READ_REG64(hpa+IOS_DIST_MASK));
	DBG_INIT("IOS_DIST_ROUTE  : %Lx\n", READ_REG64(hpa+IOS_DIST_ROUTE));
	DBG_INIT("\n");
	DBG_INIT("IOS_DIRECT_BASE : %Lx\n", READ_REG64(hpa+IOS_सूचीECT_BASE));
	DBG_INIT("IOS_DIRECT_MASK : %Lx\n", READ_REG64(hpa+IOS_सूचीECT_MASK));
	DBG_INIT("IOS_DIRECT_ROUTE: %Lx\n", READ_REG64(hpa+IOS_सूचीECT_ROUTE));
पूर्ण

/**
 * sba_dump_tlb - debugging only - prपूर्णांक IOMMU operating parameters
 * @hpa: base address of the IOMMU
 *
 * Prपूर्णांक the size/location of the IO MMU Pसूची.
 */
अटल व्योम sba_dump_tlb(व्योम __iomem *hpa)
अणु
	DBG_INIT("IO TLB at 0x%p\n", hpa);
	DBG_INIT("IOC_IBASE    : 0x%Lx\n", READ_REG64(hpa+IOC_IBASE));
	DBG_INIT("IOC_IMASK    : 0x%Lx\n", READ_REG64(hpa+IOC_IMASK));
	DBG_INIT("IOC_TCNFG    : 0x%Lx\n", READ_REG64(hpa+IOC_TCNFG));
	DBG_INIT("IOC_PDIR_BASE: 0x%Lx\n", READ_REG64(hpa+IOC_Pसूची_BASE));
	DBG_INIT("\n");
पूर्ण
#अन्यथा
#घोषणा sba_dump_ranges(x)
#घोषणा sba_dump_tlb(x)
#पूर्ण_अगर	/* DEBUG_SBA_INIT */


#अगर_घोषित ASSERT_Pसूची_SANITY

/**
 * sba_dump_pdir_entry - debugging only - prपूर्णांक one IOMMU Pसूची entry
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @msg: text to prपूर्णांक ont the output line.
 * @pide: pdir index.
 *
 * Prपूर्णांक one entry of the IO MMU Pसूची in human पढ़ोable क्रमm.
 */
अटल व्योम
sba_dump_pdir_entry(काष्ठा ioc *ioc, अक्षर *msg, uपूर्णांक pide)
अणु
	/* start prपूर्णांकing from lowest pde in rval */
	u64 *ptr = &(ioc->pdir_base[pide & (~0U * BITS_PER_LONG)]);
	अचिन्हित दीर्घ *rptr = (अचिन्हित दीर्घ *) &(ioc->res_map[(pide >>3) & ~(माप(अचिन्हित दीर्घ) - 1)]);
	uपूर्णांक rcnt;

	prपूर्णांकk(KERN_DEBUG "SBA: %s rp %p bit %d rval 0x%lx\n",
		 msg,
		 rptr, pide & (BITS_PER_LONG - 1), *rptr);

	rcnt = 0;
	जबतक (rcnt < BITS_PER_LONG) अणु
		prपूर्णांकk(KERN_DEBUG "%s %2d %p %016Lx\n",
			(rcnt == (pide & (BITS_PER_LONG - 1)))
				? "    -->" : "       ",
			rcnt, ptr, *ptr );
		rcnt++;
		ptr++;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "%s", msg);
पूर्ण


/**
 * sba_check_pdir - debugging only - consistency checker
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @msg: text to prपूर्णांक ont the output line.
 *
 * Verअगरy the resource map and pdir state is consistent
 */
अटल पूर्णांक
sba_check_pdir(काष्ठा ioc *ioc, अक्षर *msg)
अणु
	u32 *rptr_end = (u32 *) &(ioc->res_map[ioc->res_size]);
	u32 *rptr = (u32 *) ioc->res_map;	/* resource map ptr */
	u64 *pptr = ioc->pdir_base;	/* pdir ptr */
	uपूर्णांक pide = 0;

	जबतक (rptr < rptr_end) अणु
		u32 rval = *rptr;
		पूर्णांक rcnt = 32;	/* number of bits we might check */

		जबतक (rcnt) अणु
			/* Get last byte and highest bit from that */
			u32 pde = ((u32) (((अक्षर *)pptr)[7])) << 24;
			अगर ((rval ^ pde) & 0x80000000)
			अणु
				/*
				** BUMMER!  -- res_map != pdir --
				** Dump rval and matching pdir entries
				*/
				sba_dump_pdir_entry(ioc, msg, pide);
				वापस(1);
			पूर्ण
			rcnt--;
			rval <<= 1;	/* try the next bit */
			pptr++;
			pide++;
		पूर्ण
		rptr++;	/* look at next word of res_map */
	पूर्ण
	/* It'd be nice अगर we always got here :^) */
	वापस 0;
पूर्ण


/**
 * sba_dump_sg - debugging only - prपूर्णांक Scatter-Gather list
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @startsg: head of the SG list
 * @nents: number of entries in SG list
 *
 * prपूर्णांक the SG list so we can verअगरy it's correct by hand.
 */
अटल व्योम
sba_dump_sg( काष्ठा ioc *ioc, काष्ठा scatterlist *startsg, पूर्णांक nents)
अणु
	जबतक (nents-- > 0) अणु
		prपूर्णांकk(KERN_DEBUG " %d : %08lx/%05x %p/%05x\n",
				nents,
				(अचिन्हित दीर्घ) sg_dma_address(startsg),
				sg_dma_len(startsg),
				sg_virt(startsg), startsg->length);
		startsg++;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* ASSERT_Pसूची_SANITY */




/**************************************************************
*
*   I/O Pdir Resource Management
*
*   Bits set in the resource map are in use.
*   Each bit can represent a number of pages.
*   LSbs represent lower addresses (IOVA's).
*
***************************************************************/
#घोषणा PAGES_PER_RANGE 1	/* could increase this to 4 or 8 अगर needed */

/* Convert from IOVP to IOVA and vice versa. */

#अगर_घोषित ZX1_SUPPORT
/* Pluto (aka ZX1) boxes need to set or clear the ibase bits appropriately */
#घोषणा SBA_IOVA(ioc,iovp,offset,hपूर्णांक_reg) ((ioc->ibase) | (iovp) | (offset))
#घोषणा SBA_IOVP(ioc,iova) ((iova) & (ioc)->iovp_mask)
#अन्यथा
/* only support Astro and ancestors. Saves a few cycles in key places */
#घोषणा SBA_IOVA(ioc,iovp,offset,hपूर्णांक_reg) ((iovp) | (offset))
#घोषणा SBA_IOVP(ioc,iova) (iova)
#पूर्ण_अगर

#घोषणा Pसूची_INDEX(iovp)   ((iovp)>>IOVP_SHIFT)

#घोषणा RESMAP_MASK(n)    (~0UL << (BITS_PER_LONG - (n)))
#घोषणा RESMAP_IDX_MASK   (माप(अचिन्हित दीर्घ) - 1)

अटल अचिन्हित दीर्घ ptr_to_pide(काष्ठा ioc *ioc, अचिन्हित दीर्घ *res_ptr,
				 अचिन्हित पूर्णांक bitshअगरtcnt)
अणु
	वापस (((अचिन्हित दीर्घ)res_ptr - (अचिन्हित दीर्घ)ioc->res_map) << 3)
		+ bitshअगरtcnt;
पूर्ण

/**
 * sba_search_biपंचांगap - find मुक्त space in IO Pसूची resource biपंचांगap
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @bits_wanted: number of entries we need.
 *
 * Find consecutive मुक्त bits in resource biपंचांगap.
 * Each bit represents one entry in the IO Pdir.
 * Cool perf optimization: search क्रम log2(size) bits at a समय.
 */
अटल SBA_INLINE अचिन्हित दीर्घ
sba_search_biपंचांगap(काष्ठा ioc *ioc, काष्ठा device *dev,
		  अचिन्हित दीर्घ bits_wanted)
अणु
	अचिन्हित दीर्घ *res_ptr = ioc->res_hपूर्णांक;
	अचिन्हित दीर्घ *res_end = (अचिन्हित दीर्घ *) &(ioc->res_map[ioc->res_size]);
	अचिन्हित दीर्घ pide = ~0UL, tpide;
	अचिन्हित दीर्घ boundary_size;
	अचिन्हित दीर्घ shअगरt;
	पूर्णांक ret;

	boundary_size = dma_get_seg_boundary_nr_pages(dev, IOVP_SHIFT);

#अगर defined(ZX1_SUPPORT)
	BUG_ON(ioc->ibase & ~IOVP_MASK);
	shअगरt = ioc->ibase >> IOVP_SHIFT;
#अन्यथा
	shअगरt = 0;
#पूर्ण_अगर

	अगर (bits_wanted > (BITS_PER_LONG/2)) अणु
		/* Search word at a समय - no mask needed */
		क्रम(; res_ptr < res_end; ++res_ptr) अणु
			tpide = ptr_to_pide(ioc, res_ptr, 0);
			ret = iommu_is_span_boundary(tpide, bits_wanted,
						     shअगरt,
						     boundary_size);
			अगर ((*res_ptr == 0) && !ret) अणु
				*res_ptr = RESMAP_MASK(bits_wanted);
				pide = tpide;
				अवरोध;
			पूर्ण
		पूर्ण
		/* poपूर्णांक to the next word on next pass */
		res_ptr++;
		ioc->res_bitshअगरt = 0;
	पूर्ण अन्यथा अणु
		/*
		** Search the resource bit map on well-aligned values.
		** "o" is the alignment.
		** We need the alignment to invalidate I/O TLB using
		** SBA HW features in the unmap path.
		*/
		अचिन्हित दीर्घ o = 1 << get_order(bits_wanted << PAGE_SHIFT);
		uपूर्णांक bitshअगरtcnt = ALIGN(ioc->res_bitshअगरt, o);
		अचिन्हित दीर्घ mask;

		अगर (bitshअगरtcnt >= BITS_PER_LONG) अणु
			bitshअगरtcnt = 0;
			res_ptr++;
		पूर्ण
		mask = RESMAP_MASK(bits_wanted) >> bitshअगरtcnt;

		DBG_RES("%s() o %ld %p", __func__, o, res_ptr);
		जबतक(res_ptr < res_end)
		अणु 
			DBG_RES("    %p %lx %lx\n", res_ptr, mask, *res_ptr);
			WARN_ON(mask == 0);
			tpide = ptr_to_pide(ioc, res_ptr, bitshअगरtcnt);
			ret = iommu_is_span_boundary(tpide, bits_wanted,
						     shअगरt,
						     boundary_size);
			अगर ((((*res_ptr) & mask) == 0) && !ret) अणु
				*res_ptr |= mask;     /* mark resources busy! */
				pide = tpide;
				अवरोध;
			पूर्ण
			mask >>= o;
			bitshअगरtcnt += o;
			अगर (mask == 0) अणु
				mask = RESMAP_MASK(bits_wanted);
				bitshअगरtcnt=0;
				res_ptr++;
			पूर्ण
		पूर्ण
		/* look in the same word on the next pass */
		ioc->res_bitshअगरt = bitshअगरtcnt + bits_wanted;
	पूर्ण

	/* wrapped ? */
	अगर (res_end <= res_ptr) अणु
		ioc->res_hपूर्णांक = (अचिन्हित दीर्घ *) ioc->res_map;
		ioc->res_bitshअगरt = 0;
	पूर्ण अन्यथा अणु
		ioc->res_hपूर्णांक = res_ptr;
	पूर्ण
	वापस (pide);
पूर्ण


/**
 * sba_alloc_range - find मुक्त bits and mark them in IO Pसूची resource biपंचांगap
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @size: number of bytes to create a mapping क्रम
 *
 * Given a size, find consecutive unmarked and then mark those bits in the
 * resource bit map.
 */
अटल पूर्णांक
sba_alloc_range(काष्ठा ioc *ioc, काष्ठा device *dev, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक pages_needed = size >> IOVP_SHIFT;
#अगर_घोषित SBA_COLLECT_STATS
	अचिन्हित दीर्घ cr_start = mfctl(16);
#पूर्ण_अगर
	अचिन्हित दीर्घ pide;

	pide = sba_search_biपंचांगap(ioc, dev, pages_needed);
	अगर (pide >= (ioc->res_size << 3)) अणु
		pide = sba_search_biपंचांगap(ioc, dev, pages_needed);
		अगर (pide >= (ioc->res_size << 3))
			panic("%s: I/O MMU @ %p is out of mapping resources\n",
			      __खाता__, ioc->ioc_hpa);
	पूर्ण

#अगर_घोषित ASSERT_Pसूची_SANITY
	/* verअगरy the first enable bit is clear */
	अगर(0x00 != ((u8 *) ioc->pdir_base)[pide*माप(u64) + 7]) अणु
		sba_dump_pdir_entry(ioc, "sba_search_bitmap() botched it?", pide);
	पूर्ण
#पूर्ण_अगर

	DBG_RES("%s(%x) %d -> %lx hint %x/%x\n",
		__func__, size, pages_needed, pide,
		(uपूर्णांक) ((अचिन्हित दीर्घ) ioc->res_hपूर्णांक - (अचिन्हित दीर्घ) ioc->res_map),
		ioc->res_bitshअगरt );

#अगर_घोषित SBA_COLLECT_STATS
	अणु
		अचिन्हित दीर्घ cr_end = mfctl(16);
		अचिन्हित दीर्घ पंचांगp = cr_end - cr_start;
		/* check क्रम roll over */
		cr_start = (cr_end < cr_start) ?  -(पंचांगp) : (पंचांगp);
	पूर्ण
	ioc->avg_search[ioc->avg_idx++] = cr_start;
	ioc->avg_idx &= SBA_SEARCH_SAMPLE - 1;

	ioc->used_pages += pages_needed;
#पूर्ण_अगर

	वापस (pide);
पूर्ण


/**
 * sba_मुक्त_range - unmark bits in IO Pसूची resource biपंचांगap
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @iova: IO भव address which was previously allocated.
 * @size: number of bytes to create a mapping क्रम
 *
 * clear bits in the ioc's resource map
 */
अटल SBA_INLINE व्योम
sba_मुक्त_range(काष्ठा ioc *ioc, dma_addr_t iova, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ iovp = SBA_IOVP(ioc, iova);
	अचिन्हित पूर्णांक pide = Pसूची_INDEX(iovp);
	अचिन्हित पूर्णांक ridx = pide >> 3;	/* convert bit to byte address */
	अचिन्हित दीर्घ *res_ptr = (अचिन्हित दीर्घ *) &((ioc)->res_map[ridx & ~RESMAP_IDX_MASK]);

	पूर्णांक bits_not_wanted = size >> IOVP_SHIFT;

	/* 3-bits "bit" address plus 2 (or 3) bits क्रम "byte" == bit in word */
	अचिन्हित दीर्घ m = RESMAP_MASK(bits_not_wanted) >> (pide & (BITS_PER_LONG - 1));

	DBG_RES("%s( ,%x,%x) %x/%lx %x %p %lx\n",
		__func__, (uपूर्णांक) iova, size,
		bits_not_wanted, m, pide, res_ptr, *res_ptr);

#अगर_घोषित SBA_COLLECT_STATS
	ioc->used_pages -= bits_not_wanted;
#पूर्ण_अगर

	*res_ptr &= ~m;
पूर्ण


/**************************************************************
*
*   "Dynamic DMA Mapping" support (aka "Coherent I/O")
*
***************************************************************/

#अगर_घोषित SBA_HINT_SUPPORT
#घोषणा SBA_DMA_HINT(ioc, val) ((val) << (ioc)->hपूर्णांक_shअगरt_pdir)
#पूर्ण_अगर

प्रकार अचिन्हित दीर्घ space_t;
#घोषणा KERNEL_SPACE 0

/**
 * sba_io_pdir_entry - fill in one IO Pसूची entry
 * @pdir_ptr:  poपूर्णांकer to IO Pसूची entry
 * @sid: process Space ID - currently only support KERNEL_SPACE
 * @vba: Virtual CPU address of buffer to map
 * @hपूर्णांक: DMA hपूर्णांक set to use क्रम this mapping
 *
 * SBA Mapping Routine
 *
 * Given a भव address (vba, arg2) and space id, (sid, arg1)
 * sba_io_pdir_entry() loads the I/O Pसूची entry poपूर्णांकed to by
 * pdir_ptr (arg0). 
 * Using the bass-ackwards HP bit numbering, Each IO Pdir entry
 * क्रम Astro/Ike looks like:
 *
 *
 *  0                    19                                 51   55       63
 * +-+---------------------+----------------------------------+----+--------+
 * |V|        U            |            PPN[43:12]            | U  |   VI   |
 * +-+---------------------+----------------------------------+----+--------+
 *
 * Pluto is basically identical, supports fewer physical address bits:
 *
 *  0                       23                              51   55       63
 * +-+------------------------+-------------------------------+----+--------+
 * |V|        U               |         PPN[39:12]            | U  |   VI   |
 * +-+------------------------+-------------------------------+----+--------+
 *
 *  V  == Valid Bit  (Most Signअगरicant Bit is bit 0)
 *  U  == Unused
 * PPN == Physical Page Number
 * VI  == Virtual Index (aka Coherent Index)
 *
 * LPA inकाष्ठाion output is put पूर्णांकo PPN field.
 * LCI (Load Coherence Index) inकाष्ठाion provides the "VI" bits.
 *
 * We pre-swap the bytes since PCX-W is Big Endian and the
 * IOMMU uses little endian क्रम the pdir.
 */

अटल व्योम SBA_INLINE
sba_io_pdir_entry(u64 *pdir_ptr, space_t sid, अचिन्हित दीर्घ vba,
		  अचिन्हित दीर्घ hपूर्णांक)
अणु
	u64 pa; /* physical address */
	रेजिस्टर अचिन्हित ci; /* coherent index */

	pa = lpa(vba);
	pa &= IOVP_MASK;

	यंत्र("lci 0(%1), %0" : "=r" (ci) : "r" (vba));
	pa |= (ci >> PAGE_SHIFT) & 0xff;  /* move CI (8 bits) पूर्णांकo lowest byte */

	pa |= SBA_Pसूची_VALID_BIT;	/* set "valid" bit */
	*pdir_ptr = cpu_to_le64(pa);	/* swap and store पूर्णांकo I/O Pdir */

	/*
	 * If the PDC_MODEL capabilities has Non-coherent IO-Pसूची bit set
	 * (bit #61, big endian), we have to flush and sync every समय
	 * IO-Pसूची is changed in Ike/Astro.
	 */
	यंत्र_io_fdc(pdir_ptr);
पूर्ण


/**
 * sba_mark_invalid - invalidate one or more IO Pसूची entries
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @iova:  IO Virtual Address mapped earlier
 * @byte_cnt:  number of bytes this mapping covers.
 *
 * Marking the IO Pसूची entry(ies) as Invalid and invalidate
 * corresponding IO TLB entry. The Ike PCOM (Purge Command Register)
 * is to purge stale entries in the IO TLB when unmapping entries.
 *
 * The PCOM रेजिस्टर supports purging of multiple pages, with a minium
 * of 1 page and a maximum of 2GB. Hardware requires the address be
 * aligned to the size of the range being purged. The size of the range
 * must be a घातer of 2. The "Cool perf optimization" in the
 * allocation routine helps keep that true.
 */
अटल SBA_INLINE व्योम
sba_mark_invalid(काष्ठा ioc *ioc, dma_addr_t iova, माप_प्रकार byte_cnt)
अणु
	u32 iovp = (u32) SBA_IOVP(ioc,iova);
	u64 *pdir_ptr = &ioc->pdir_base[Pसूची_INDEX(iovp)];

#अगर_घोषित ASSERT_Pसूची_SANITY
	/* Assert first pdir entry is set.
	**
	** Even though this is a big-endian machine, the entries
	** in the iopdir are little endian. That's why we look at
	** the byte at +7 instead of at +0.
	*/
	अगर (0x80 != (((u8 *) pdir_ptr)[7])) अणु
		sba_dump_pdir_entry(ioc,"sba_mark_invalid()", Pसूची_INDEX(iovp));
	पूर्ण
#पूर्ण_अगर

	अगर (byte_cnt > IOVP_SIZE)
	अणु
#अगर 0
		अचिन्हित दीर्घ entries_per_cacheline = ioc_needs_fdc ?
				L1_CACHE_ALIGN(((अचिन्हित दीर्घ) pdir_ptr))
					- (अचिन्हित दीर्घ) pdir_ptr;
				: 262144;
#पूर्ण_अगर

		/* set "size" field क्रम PCOM */
		iovp |= get_order(byte_cnt) + PAGE_SHIFT;

		करो अणु
			/* clear I/O Pdir entry "valid" bit first */
			((u8 *) pdir_ptr)[7] = 0;
			यंत्र_io_fdc(pdir_ptr);
			अगर (ioc_needs_fdc) अणु
#अगर 0
				entries_per_cacheline = L1_CACHE_SHIFT - 3;
#पूर्ण_अगर
			पूर्ण
			pdir_ptr++;
			byte_cnt -= IOVP_SIZE;
		पूर्ण जबतक (byte_cnt > IOVP_SIZE);
	पूर्ण अन्यथा
		iovp |= IOVP_SHIFT;     /* set "size" field क्रम PCOM */

	/*
	** clear I/O Pसूची entry "valid" bit.
	** We have to R/M/W the cacheline regardless how much of the
	** pdir entry that we clobber.
	** The rest of the entry would be useful क्रम debugging अगर we
	** could dump core on HPMC.
	*/
	((u8 *) pdir_ptr)[7] = 0;
	यंत्र_io_fdc(pdir_ptr);

	WRITE_REG( SBA_IOVA(ioc, iovp, 0, 0), ioc->ioc_hpa+IOC_PCOM);
पूर्ण

/**
 * sba_dma_supported - PCI driver can query DMA support
 * @dev: instance of PCI owned by the driver that's asking
 * @mask:  number of address bits this PCI device can handle
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल पूर्णांक sba_dma_supported( काष्ठा device *dev, u64 mask)
अणु
	काष्ठा ioc *ioc;

	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": EISA/ISA/et al not supported\n");
		BUG();
		वापस(0);
	पूर्ण

	ioc = GET_IOC(dev);
	अगर (!ioc)
		वापस 0;

	/*
	 * check अगर mask is >= than the current max IO Virt Address
	 * The max IO Virt address will *always* < 30 bits.
	 */
	वापस((पूर्णांक)(mask >= (ioc->ibase - 1 +
			(ioc->pdir_size / माप(u64) * IOVP_SIZE) )));
पूर्ण


/**
 * sba_map_single - map one buffer and वापस IOVA क्रम DMA
 * @dev: instance of PCI owned by the driver that's asking.
 * @addr:  driver buffer to map.
 * @size:  number of bytes to map in driver buffer.
 * @direction:  R/W or both.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल dma_addr_t
sba_map_single(काष्ठा device *dev, व्योम *addr, माप_प्रकार size,
	       क्रमागत dma_data_direction direction)
अणु
	काष्ठा ioc *ioc;
	अचिन्हित दीर्घ flags; 
	dma_addr_t iovp;
	dma_addr_t offset;
	u64 *pdir_start;
	पूर्णांक pide;

	ioc = GET_IOC(dev);
	अगर (!ioc)
		वापस DMA_MAPPING_ERROR;

	/* save offset bits */
	offset = ((dma_addr_t) (दीर्घ) addr) & ~IOVP_MASK;

	/* round up to nearest IOVP_SIZE */
	size = (size + offset + ~IOVP_MASK) & IOVP_MASK;

	spin_lock_irqsave(&ioc->res_lock, flags);
#अगर_घोषित ASSERT_Pसूची_SANITY
	sba_check_pdir(ioc,"Check before sba_map_single()");
#पूर्ण_अगर

#अगर_घोषित SBA_COLLECT_STATS
	ioc->msingle_calls++;
	ioc->msingle_pages += size >> IOVP_SHIFT;
#पूर्ण_अगर
	pide = sba_alloc_range(ioc, dev, size);
	iovp = (dma_addr_t) pide << IOVP_SHIFT;

	DBG_RUN("%s() 0x%p -> 0x%lx\n",
		__func__, addr, (दीर्घ) iovp | offset);

	pdir_start = &(ioc->pdir_base[pide]);

	जबतक (size > 0) अणु
		sba_io_pdir_entry(pdir_start, KERNEL_SPACE, (अचिन्हित दीर्घ) addr, 0);

		DBG_RUN("	pdir 0x%p %02x%02x%02x%02x%02x%02x%02x%02x\n",
			pdir_start,
			(u8) (((u8 *) pdir_start)[7]),
			(u8) (((u8 *) pdir_start)[6]),
			(u8) (((u8 *) pdir_start)[5]),
			(u8) (((u8 *) pdir_start)[4]),
			(u8) (((u8 *) pdir_start)[3]),
			(u8) (((u8 *) pdir_start)[2]),
			(u8) (((u8 *) pdir_start)[1]),
			(u8) (((u8 *) pdir_start)[0])
			);

		addr += IOVP_SIZE;
		size -= IOVP_SIZE;
		pdir_start++;
	पूर्ण

	/* क्रमce FDC ops in io_pdir_entry() to be visible to IOMMU */
	यंत्र_io_sync();

#अगर_घोषित ASSERT_Pसूची_SANITY
	sba_check_pdir(ioc,"Check after sba_map_single()");
#पूर्ण_अगर
	spin_unlock_irqrestore(&ioc->res_lock, flags);

	/* क्रमm complete address */
	वापस SBA_IOVA(ioc, iovp, offset, DEFAULT_DMA_HINT_REG);
पूर्ण


अटल dma_addr_t
sba_map_page(काष्ठा device *dev, काष्ठा page *page, अचिन्हित दीर्घ offset,
		माप_प्रकार size, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	वापस sba_map_single(dev, page_address(page) + offset, size,
			direction);
पूर्ण


/**
 * sba_unmap_page - unmap one IOVA and मुक्त resources
 * @dev: instance of PCI owned by the driver that's asking.
 * @iova:  IOVA of driver buffer previously mapped.
 * @size:  number of bytes mapped in driver buffer.
 * @direction:  R/W or both.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम
sba_unmap_page(काष्ठा device *dev, dma_addr_t iova, माप_प्रकार size,
		क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
#अगर DELAYED_RESOURCE_CNT > 0
	काष्ठा sba_dma_pair *d;
#पूर्ण_अगर
	अचिन्हित दीर्घ flags; 
	dma_addr_t offset;

	DBG_RUN("%s() iovp 0x%lx/%x\n", __func__, (दीर्घ) iova, size);

	ioc = GET_IOC(dev);
	अगर (!ioc) अणु
		WARN_ON(!ioc);
		वापस;
	पूर्ण
	offset = iova & ~IOVP_MASK;
	iova ^= offset;        /* clear offset bits */
	size += offset;
	size = ALIGN(size, IOVP_SIZE);

	spin_lock_irqsave(&ioc->res_lock, flags);

#अगर_घोषित SBA_COLLECT_STATS
	ioc->usingle_calls++;
	ioc->usingle_pages += size >> IOVP_SHIFT;
#पूर्ण_अगर

	sba_mark_invalid(ioc, iova, size);

#अगर DELAYED_RESOURCE_CNT > 0
	/* Delaying when we re-use a IO Pdir entry reduces the number
	 * of MMIO पढ़ोs needed to flush ग_लिखोs to the PCOM रेजिस्टर.
	 */
	d = &(ioc->saved[ioc->saved_cnt]);
	d->iova = iova;
	d->size = size;
	अगर (++(ioc->saved_cnt) >= DELAYED_RESOURCE_CNT) अणु
		पूर्णांक cnt = ioc->saved_cnt;
		जबतक (cnt--) अणु
			sba_मुक्त_range(ioc, d->iova, d->size);
			d--;
		पूर्ण
		ioc->saved_cnt = 0;

		READ_REG(ioc->ioc_hpa+IOC_PCOM);	/* flush purges */
	पूर्ण
#अन्यथा /* DELAYED_RESOURCE_CNT == 0 */
	sba_मुक्त_range(ioc, iova, size);

	/* If fdc's were issued, force fdc's to be visible now */
	यंत्र_io_sync();

	READ_REG(ioc->ioc_hpa+IOC_PCOM);	/* flush purges */
#पूर्ण_अगर /* DELAYED_RESOURCE_CNT == 0 */

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	/* XXX REVISIT क्रम 2.5 Linux - need syncdma क्रम zero-copy support.
	** For Astro based प्रणालीs this isn't a big deal WRT perक्रमmance.
	** As दीर्घ as 2.4 kernels copyin/copyout data from/to userspace,
	** we करोn't need the syncdma. The issue here is I/O MMU cachelines
	** are *not* coherent in all हालs.  May be hwrev dependent.
	** Need to investigate more.
	यंत्र अस्थिर("syncdma");	
	*/
पूर्ण


/**
 * sba_alloc - allocate/map shared mem क्रम DMA
 * @hwdev: instance of PCI owned by the driver that's asking.
 * @size:  number of bytes mapped in driver buffer.
 * @dma_handle:  IOVA of new buffer.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम *sba_alloc(काष्ठा device *hwdev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	व्योम *ret;

	अगर (!hwdev) अणु
		/* only support PCI */
		*dma_handle = 0;
		वापस शून्य;
	पूर्ण

        ret = (व्योम *) __get_मुक्त_pages(gfp, get_order(size));

	अगर (ret) अणु
		स_रखो(ret, 0, size);
		*dma_handle = sba_map_single(hwdev, ret, size, 0);
	पूर्ण

	वापस ret;
पूर्ण


/**
 * sba_मुक्त - मुक्त/unmap shared mem क्रम DMA
 * @hwdev: instance of PCI owned by the driver that's asking.
 * @size:  number of bytes mapped in driver buffer.
 * @vaddr:  भव address IOVA of "consistent" buffer.
 * @dma_handler:  IO भव address of "consistent" buffer.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम
sba_मुक्त(काष्ठा device *hwdev, माप_प्रकार size, व्योम *vaddr,
		    dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	sba_unmap_page(hwdev, dma_handle, size, 0, 0);
	मुक्त_pages((अचिन्हित दीर्घ) vaddr, get_order(size));
पूर्ण


/*
** Since 0 is a valid pdir_base index value, can't use that
** to determine अगर a value is valid or not. Use a flag to indicate
** the SG list entry contains a valid pdir index.
*/
#घोषणा PIDE_FLAG 0x80000000UL

#अगर_घोषित SBA_COLLECT_STATS
#घोषणा IOMMU_MAP_STATS
#पूर्ण_अगर
#समावेश "iommu-helpers.h"

#अगर_घोषित DEBUG_LARGE_SG_ENTRIES
पूर्णांक dump_run_sg = 0;
#पूर्ण_अगर


/**
 * sba_map_sg - map Scatter/Gather list
 * @dev: instance of PCI owned by the driver that's asking.
 * @sglist:  array of buffer/length pairs
 * @nents:  number of entries in list
 * @direction:  R/W or both.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल पूर्णांक
sba_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist, पूर्णांक nents,
	   क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
	पूर्णांक coalesced, filled = 0;
	अचिन्हित दीर्घ flags;

	DBG_RUN_SG("%s() START %d entries\n", __func__, nents);

	ioc = GET_IOC(dev);
	अगर (!ioc)
		वापस 0;

	/* Fast path single entry scatterlists. */
	अगर (nents == 1) अणु
		sg_dma_address(sglist) = sba_map_single(dev, sg_virt(sglist),
						sglist->length, direction);
		sg_dma_len(sglist)     = sglist->length;
		वापस 1;
	पूर्ण

	spin_lock_irqsave(&ioc->res_lock, flags);

#अगर_घोषित ASSERT_Pसूची_SANITY
	अगर (sba_check_pdir(ioc,"Check before sba_map_sg()"))
	अणु
		sba_dump_sg(ioc, sglist, nents);
		panic("Check before sba_map_sg()");
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित SBA_COLLECT_STATS
	ioc->msg_calls++;
#पूर्ण_अगर

	/*
	** First coalesce the chunks and allocate I/O pdir space
	**
	** If this is one DMA stream, we can properly map using the
	** correct भव address associated with each DMA page.
	** w/o this association, we wouldn't have coherent DMA!
	** Access to the भव address is what क्रमces a two pass algorithm.
	*/
	coalesced = iommu_coalesce_chunks(ioc, dev, sglist, nents, sba_alloc_range);

	/*
	** Program the I/O Pdir
	**
	** map the भव addresses to the I/O Pdir
	** o dma_address will contain the pdir index
	** o dma_len will contain the number of bytes to map 
	** o address contains the भव address.
	*/
	filled = iommu_fill_pdir(ioc, sglist, nents, 0, sba_io_pdir_entry);

	/* क्रमce FDC ops in io_pdir_entry() to be visible to IOMMU */
	यंत्र_io_sync();

#अगर_घोषित ASSERT_Pसूची_SANITY
	अगर (sba_check_pdir(ioc,"Check after sba_map_sg()"))
	अणु
		sba_dump_sg(ioc, sglist, nents);
		panic("Check after sba_map_sg()\n");
	पूर्ण
#पूर्ण_अगर

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	DBG_RUN_SG("%s() DONE %d mappings\n", __func__, filled);

	वापस filled;
पूर्ण


/**
 * sba_unmap_sg - unmap Scatter/Gather list
 * @dev: instance of PCI owned by the driver that's asking.
 * @sglist:  array of buffer/length pairs
 * @nents:  number of entries in list
 * @direction:  R/W or both.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम 
sba_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist, पूर्णांक nents,
	     क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
#अगर_घोषित ASSERT_Pसूची_SANITY
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर

	DBG_RUN_SG("%s() START %d entries,  %p,%x\n",
		__func__, nents, sg_virt(sglist), sglist->length);

	ioc = GET_IOC(dev);
	अगर (!ioc) अणु
		WARN_ON(!ioc);
		वापस;
	पूर्ण

#अगर_घोषित SBA_COLLECT_STATS
	ioc->usg_calls++;
#पूर्ण_अगर

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_check_pdir(ioc,"Check before sba_unmap_sg()");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

	जबतक (sg_dma_len(sglist) && nents--) अणु

		sba_unmap_page(dev, sg_dma_address(sglist), sg_dma_len(sglist),
				direction, 0);
#अगर_घोषित SBA_COLLECT_STATS
		ioc->usg_pages += ((sg_dma_address(sglist) & ~IOVP_MASK) + sg_dma_len(sglist) + IOVP_SIZE - 1) >> PAGE_SHIFT;
		ioc->usingle_calls--;	/* kluge since call is unmap_sg() */
#पूर्ण_अगर
		++sglist;
	पूर्ण

	DBG_RUN_SG("%s() DONE (nents %d)\n", __func__,  nents);

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_check_pdir(ioc,"Check after sba_unmap_sg()");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

पूर्ण

अटल स्थिर काष्ठा dma_map_ops sba_ops = अणु
	.dma_supported =	sba_dma_supported,
	.alloc =		sba_alloc,
	.मुक्त =			sba_मुक्त,
	.map_page =		sba_map_page,
	.unmap_page =		sba_unmap_page,
	.map_sg =		sba_map_sg,
	.unmap_sg =		sba_unmap_sg,
	.get_sgtable =		dma_common_get_sgtable,
	.alloc_pages =		dma_common_alloc_pages,
	.मुक्त_pages =		dma_common_मुक्त_pages,
पूर्ण;


/**************************************************************************
**
**   SBA PAT PDC support
**
**   o call pdc_pat_cell_module()
**   o store ranges in PCI "resource" काष्ठाures
**
**************************************************************************/

अटल व्योम
sba_get_pat_resources(काष्ठा sba_device *sba_dev)
अणु
#अगर 0
/*
** TODO/REVISIT/FIXME: support क्रम directed ranges requires calls to
**      PAT PDC to program the SBA/LBA directed range रेजिस्टरs...this
**      burden may fall on the LBA code since it directly supports the
**      PCI subप्रणाली. It's not clear yet. - ggg
*/
PAT_MOD(mod)->mod_info.mod_pages   = PAT_GET_MOD_PAGES(temp);
	FIXME : ???
PAT_MOD(mod)->mod_info.dvi         = PAT_GET_DVI(temp);
	Tells where the dvi bits are located in the address.
PAT_MOD(mod)->mod_info.ioc         = PAT_GET_IOC(temp);
	FIXME : ???
#पूर्ण_अगर
पूर्ण


/**************************************************************
*
*   Initialization and claim
*
***************************************************************/
#घोषणा PIRANHA_ADDR_MASK	0x00160000UL /* bit 17,18,20 */
#घोषणा PIRANHA_ADDR_VAL	0x00060000UL /* bit 17,18 on */
अटल व्योम *
sba_alloc_pdir(अचिन्हित पूर्णांक pdir_size)
अणु
        अचिन्हित दीर्घ pdir_base;
	अचिन्हित दीर्घ pdir_order = get_order(pdir_size);

	pdir_base = __get_मुक्त_pages(GFP_KERNEL, pdir_order);
	अगर (शून्य == (व्योम *) pdir_base)	अणु
		panic("%s() could not allocate I/O Page Table\n",
			__func__);
	पूर्ण

	/* If this is not PA8700 (PCX-W2)
	**	OR newer than ver 2.2
	**	OR in a प्रणाली that करोesn't need VINDEX bits from SBA,
	**
	** then we aren't exposed to the HW bug.
	*/
	अगर ( ((boot_cpu_data.pdc.cpuid >> 5) & 0x7f) != 0x13
			|| (boot_cpu_data.pdc.versions > 0x202)
			|| (boot_cpu_data.pdc.capabilities & 0x08L) )
		वापस (व्योम *) pdir_base;

	/*
	 * PA8700 (PCX-W2, aka piranha) silent data corruption fix
	 *
	 * An पूर्णांकeraction between PA8700 CPU (Ver 2.2 or older) and
	 * Ike/Astro can cause silent data corruption. This is only
	 * a problem अगर the I/O Pसूची is located in memory such that
	 * (little-endian)  bits 17 and 18 are on and bit 20 is off.
	 *
	 * Since the max IO Pdir size is 2MB, by cleverly allocating the
	 * right physical address, we can either aव्योम (IOPसूची <= 1MB)
	 * or minimize (2MB IO Pdir) the problem अगर we restrict the
	 * IO Pdir to a maximum size of 2MB-128K (1902K).
	 *
	 * Because we always allocate 2^N sized IO pdirs, either of the
	 * "bad" regions will be the last 128K अगर at all. That's easy
	 * to test क्रम.
	 * 
	 */
	अगर (pdir_order <= (19-12)) अणु
		अगर (((virt_to_phys(pdir_base)+pdir_size-1) & PIRANHA_ADDR_MASK) == PIRANHA_ADDR_VAL) अणु
			/* allocate a new one on 512k alignment */
			अचिन्हित दीर्घ new_pdir = __get_मुक्त_pages(GFP_KERNEL, (19-12));
			/* release original */
			मुक्त_pages(pdir_base, pdir_order);

			pdir_base = new_pdir;

			/* release excess */
			जबतक (pdir_order < (19-12)) अणु
				new_pdir += pdir_size;
				मुक्त_pages(new_pdir, pdir_order);
				pdir_order +=1;
				pdir_size <<=1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		** 1MB or 2MB Pdir
		** Needs to be aligned on an "odd" 1MB boundary.
		*/
		अचिन्हित दीर्घ new_pdir = __get_मुक्त_pages(GFP_KERNEL, pdir_order+1); /* 2 or 4MB */

		/* release original */
		मुक्त_pages( pdir_base, pdir_order);

		/* release first 1MB */
		मुक्त_pages(new_pdir, 20-12);

		pdir_base = new_pdir + 1024*1024;

		अगर (pdir_order > (20-12)) अणु
			/*
			** 2MB Pdir.
			**
			** Flag tells init_biपंचांगap() to mark bad 128k as used
			** and to reduce the size by 128k.
			*/
			piranha_bad_128k = 1;

			new_pdir += 3*1024*1024;
			/* release last 1MB */
			मुक्त_pages(new_pdir, 20-12);

			/* release unusable 128KB */
			मुक्त_pages(new_pdir - 128*1024 , 17-12);

			pdir_size -= 128*1024;
		पूर्ण
	पूर्ण

	स_रखो((व्योम *) pdir_base, 0, pdir_size);
	वापस (व्योम *) pdir_base;
पूर्ण

काष्ठा ibase_data_काष्ठा अणु
	काष्ठा ioc *ioc;
	पूर्णांक ioc_num;
पूर्ण;

अटल पूर्णांक setup_ibase_imask_callback(काष्ठा device *dev, व्योम *data)
अणु
	/* lba_set_iregs() is in drivers/parisc/lba_pci.c */
        बाह्य व्योम lba_set_iregs(काष्ठा parisc_device *, u32, u32);
	काष्ठा parisc_device *lba = to_parisc_device(dev);
	काष्ठा ibase_data_काष्ठा *ibd = data;
	पूर्णांक rope_num = (lba->hpa.start >> 13) & 0xf;
	अगर (rope_num >> 3 == ibd->ioc_num)
		lba_set_iregs(lba, ibd->ioc->ibase, ibd->ioc->imask);
	वापस 0;
पूर्ण

/* setup Mercury or Elroy IBASE/IMASK रेजिस्टरs. */
अटल व्योम 
setup_ibase_imask(काष्ठा parisc_device *sba, काष्ठा ioc *ioc, पूर्णांक ioc_num)
अणु
	काष्ठा ibase_data_काष्ठा ibase_data = अणु
		.ioc		= ioc,
		.ioc_num	= ioc_num,
	पूर्ण;

	device_क्रम_each_child(&sba->dev, &ibase_data,
			      setup_ibase_imask_callback);
पूर्ण

#अगर_घोषित SBA_AGP_SUPPORT
अटल पूर्णांक
sba_ioc_find_quicksilver(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक *agp_found = data;
	काष्ठा parisc_device *lba = to_parisc_device(dev);

	अगर (IS_QUICKSILVER(lba))
		*agp_found = 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम
sba_ioc_init_pluto(काष्ठा parisc_device *sba, काष्ठा ioc *ioc, पूर्णांक ioc_num)
अणु
	u32 iova_space_mask;
	u32 iova_space_size;
	पूर्णांक iov_order, tcnfg;
#अगर_घोषित SBA_AGP_SUPPORT
	पूर्णांक agp_found = 0;
#पूर्ण_अगर
	/*
	** Firmware programs the base and size of a "safe IOVA space"
	** (one that करोesn't overlap memory or LMMIO space) in the
	** IBASE and IMASK रेजिस्टरs.
	*/
	ioc->ibase = READ_REG(ioc->ioc_hpa + IOC_IBASE) & ~0x1fffffULL;
	iova_space_size = ~(READ_REG(ioc->ioc_hpa + IOC_IMASK) & 0xFFFFFFFFUL) + 1;

	अगर ((ioc->ibase < 0xfed00000UL) && ((ioc->ibase + iova_space_size) > 0xfee00000UL)) अणु
		prपूर्णांकk("WARNING: IOV space overlaps local config and interrupt message, truncating\n");
		iova_space_size /= 2;
	पूर्ण

	/*
	** iov_order is always based on a 1GB IOVA space since we want to
	** turn on the other half क्रम AGP GART.
	*/
	iov_order = get_order(iova_space_size >> (IOVP_SHIFT - PAGE_SHIFT));
	ioc->pdir_size = (iova_space_size / IOVP_SIZE) * माप(u64);

	DBG_INIT("%s() hpa 0x%p IOV %dMB (%d bits)\n",
		__func__, ioc->ioc_hpa, iova_space_size >> 20,
		iov_order + PAGE_SHIFT);

	ioc->pdir_base = (व्योम *) __get_मुक्त_pages(GFP_KERNEL,
						   get_order(ioc->pdir_size));
	अगर (!ioc->pdir_base)
		panic("Couldn't allocate I/O Page Table\n");

	स_रखो(ioc->pdir_base, 0, ioc->pdir_size);

	DBG_INIT("%s() pdir %p size %x\n",
			__func__, ioc->pdir_base, ioc->pdir_size);

#अगर_घोषित SBA_HINT_SUPPORT
	ioc->hपूर्णांक_shअगरt_pdir = iov_order + PAGE_SHIFT;
	ioc->hपूर्णांक_mask_pdir = ~(0x3 << (iov_order + PAGE_SHIFT));

	DBG_INIT("	hint_shift_pdir %x hint_mask_pdir %lx\n",
		ioc->hपूर्णांक_shअगरt_pdir, ioc->hपूर्णांक_mask_pdir);
#पूर्ण_अगर

	WARN_ON((((अचिन्हित दीर्घ) ioc->pdir_base) & PAGE_MASK) != (अचिन्हित दीर्घ) ioc->pdir_base);
	WRITE_REG(virt_to_phys(ioc->pdir_base), ioc->ioc_hpa + IOC_Pसूची_BASE);

	/* build IMASK क्रम IOC and Elroy */
	iova_space_mask =  0xffffffff;
	iova_space_mask <<= (iov_order + PAGE_SHIFT);
	ioc->imask = iova_space_mask;
#अगर_घोषित ZX1_SUPPORT
	ioc->iovp_mask = ~(iova_space_mask + PAGE_SIZE - 1);
#पूर्ण_अगर
	sba_dump_tlb(ioc->ioc_hpa);

	setup_ibase_imask(sba, ioc, ioc_num);

	WRITE_REG(ioc->imask, ioc->ioc_hpa + IOC_IMASK);

#अगर_घोषित CONFIG_64BIT
	/*
	** Setting the upper bits makes checking क्रम bypass addresses
	** a little faster later on.
	*/
	ioc->imask |= 0xFFFFFFFF00000000UL;
#पूर्ण_अगर

	/* Set I/O Pसूची Page size to प्रणाली page size */
	चयन (PAGE_SHIFT) अणु
		हाल 12: tcnfg = 0; अवरोध;	/*  4K */
		हाल 13: tcnfg = 1; अवरोध;	/*  8K */
		हाल 14: tcnfg = 2; अवरोध;	/* 16K */
		हाल 16: tcnfg = 3; अवरोध;	/* 64K */
		शेष:
			panic(__खाता__ "Unsupported system page size %d",
				1 << PAGE_SHIFT);
			अवरोध;
	पूर्ण
	WRITE_REG(tcnfg, ioc->ioc_hpa + IOC_TCNFG);

	/*
	** Program the IOC's ibase and enable IOVA translation
	** Bit zero == enable bit.
	*/
	WRITE_REG(ioc->ibase | 1, ioc->ioc_hpa + IOC_IBASE);

	/*
	** Clear I/O TLB of any possible entries.
	** (Yes. This is a bit paranoid...but so what)
	*/
	WRITE_REG(ioc->ibase | 31, ioc->ioc_hpa + IOC_PCOM);

#अगर_घोषित SBA_AGP_SUPPORT

	/*
	** If an AGP device is present, only use half of the IOV space
	** क्रम PCI DMA.  Unक्रमtunately we can't know ahead of समय
	** whether GART support will actually be used, क्रम now we
	** can just key on any AGP device found in the प्रणाली.
	** We program the next pdir index after we stop w/ a key क्रम
	** the GART code to handshake on.
	*/
	device_क्रम_each_child(&sba->dev, &agp_found, sba_ioc_find_quicksilver);

	अगर (agp_found && sba_reserve_agpgart) अणु
		prपूर्णांकk(KERN_INFO "%s: reserving %dMb of IOVA space for agpgart\n",
		       __func__, (iova_space_size/2) >> 20);
		ioc->pdir_size /= 2;
		ioc->pdir_base[Pसूची_INDEX(iova_space_size/2)] = SBA_AGPGART_COOKIE;
	पूर्ण
#पूर्ण_अगर /*SBA_AGP_SUPPORT*/
पूर्ण

अटल व्योम
sba_ioc_init(काष्ठा parisc_device *sba, काष्ठा ioc *ioc, पूर्णांक ioc_num)
अणु
	u32 iova_space_size, iova_space_mask;
	अचिन्हित पूर्णांक pdir_size, iov_order, tcnfg;

	/*
	** Determine IOVA Space size from memory size.
	**
	** Ideally, PCI drivers would रेजिस्टर the maximum number
	** of DMA they can have outstanding क्रम each device they
	** own.  Next best thing would be to guess how much DMA
	** can be outstanding based on PCI Class/sub-class. Both
	** methods still require some "extra" to support PCI
	** Hot-Plug/Removal of PCI cards. (aka PCI OLARD).
	**
	** While we have 32-bits "IOVA" space, top two 2 bits are used
	** क्रम DMA hपूर्णांकs - ergo only 30 bits max.
	*/

	iova_space_size = (u32) (totalram_pages()/global_ioc_cnt);

	/* limit IOVA space size to 1MB-1GB */
	अगर (iova_space_size < (1 << (20 - PAGE_SHIFT))) अणु
		iova_space_size = 1 << (20 - PAGE_SHIFT);
	पूर्ण
	अन्यथा अगर (iova_space_size > (1 << (30 - PAGE_SHIFT))) अणु
		iova_space_size = 1 << (30 - PAGE_SHIFT);
	पूर्ण

	/*
	** iova space must be log2() in size.
	** thus, pdir/res_map will also be log2().
	** PIRANHA BUG: Exception is when IO Pdir is 2MB (माला_लो reduced)
	*/
	iov_order = get_order(iova_space_size << PAGE_SHIFT);

	/* iova_space_size is now bytes, not pages */
	iova_space_size = 1 << (iov_order + PAGE_SHIFT);

	ioc->pdir_size = pdir_size = (iova_space_size/IOVP_SIZE) * माप(u64);

	DBG_INIT("%s() hpa 0x%lx mem %ldMB IOV %dMB (%d bits)\n",
			__func__,
			ioc->ioc_hpa,
			(अचिन्हित दीर्घ) totalram_pages() >> (20 - PAGE_SHIFT),
			iova_space_size>>20,
			iov_order + PAGE_SHIFT);

	ioc->pdir_base = sba_alloc_pdir(pdir_size);

	DBG_INIT("%s() pdir %p size %x\n",
			__func__, ioc->pdir_base, pdir_size);

#अगर_घोषित SBA_HINT_SUPPORT
	/* FIXME : DMA HINTs not used */
	ioc->hपूर्णांक_shअगरt_pdir = iov_order + PAGE_SHIFT;
	ioc->hपूर्णांक_mask_pdir = ~(0x3 << (iov_order + PAGE_SHIFT));

	DBG_INIT("	hint_shift_pdir %x hint_mask_pdir %lx\n",
			ioc->hपूर्णांक_shअगरt_pdir, ioc->hपूर्णांक_mask_pdir);
#पूर्ण_अगर

	WRITE_REG64(virt_to_phys(ioc->pdir_base), ioc->ioc_hpa + IOC_Pसूची_BASE);

	/* build IMASK क्रम IOC and Elroy */
	iova_space_mask =  0xffffffff;
	iova_space_mask <<= (iov_order + PAGE_SHIFT);

	/*
	** On C3000 w/512MB mem, HP-UX 10.20 reports:
	**     ibase=0, imask=0xFE000000, size=0x2000000.
	*/
	ioc->ibase = 0;
	ioc->imask = iova_space_mask;	/* save it */
#अगर_घोषित ZX1_SUPPORT
	ioc->iovp_mask = ~(iova_space_mask + PAGE_SIZE - 1);
#पूर्ण_अगर

	DBG_INIT("%s() IOV base 0x%lx mask 0x%0lx\n",
		__func__, ioc->ibase, ioc->imask);

	/*
	** FIXME: Hपूर्णांक रेजिस्टरs are programmed with शेष hपूर्णांक
	** values during boot, so hपूर्णांकs should be sane even अगर we
	** can't reprogram them the way drivers want.
	*/

	setup_ibase_imask(sba, ioc, ioc_num);

	/*
	** Program the IOC's ibase and enable IOVA translation
	*/
	WRITE_REG(ioc->ibase | 1, ioc->ioc_hpa+IOC_IBASE);
	WRITE_REG(ioc->imask, ioc->ioc_hpa+IOC_IMASK);

	/* Set I/O Pसूची Page size to प्रणाली page size */
	चयन (PAGE_SHIFT) अणु
		हाल 12: tcnfg = 0; अवरोध;	/*  4K */
		हाल 13: tcnfg = 1; अवरोध;	/*  8K */
		हाल 14: tcnfg = 2; अवरोध;	/* 16K */
		हाल 16: tcnfg = 3; अवरोध;	/* 64K */
		शेष:
			panic(__खाता__ "Unsupported system page size %d",
				1 << PAGE_SHIFT);
			अवरोध;
	पूर्ण
	/* Set I/O Pसूची Page size to PAGE_SIZE (4k/16k/...) */
	WRITE_REG(tcnfg, ioc->ioc_hpa+IOC_TCNFG);

	/*
	** Clear I/O TLB of any possible entries.
	** (Yes. This is a bit paranoid...but so what)
	*/
	WRITE_REG(0 | 31, ioc->ioc_hpa+IOC_PCOM);

	ioc->ibase = 0; /* used by SBA_IOVA and related macros */	

	DBG_INIT("%s() DONE\n", __func__);
पूर्ण



/**************************************************************************
**
**   SBA initialization code (HW and SW)
**
**   o identअगरy SBA chip itself
**   o initialize SBA chip modes (HardFail)
**   o initialize SBA chip modes (HardFail)
**   o FIXME: initialize DMA hपूर्णांकs क्रम reasonable शेषs
**
**************************************************************************/

अटल व्योम __iomem *ioc_remap(काष्ठा sba_device *sba_dev, अचिन्हित पूर्णांक offset)
अणु
	वापस ioremap(sba_dev->dev->hpa.start + offset, SBA_FUNC_SIZE);
पूर्ण

अटल व्योम sba_hw_init(काष्ठा sba_device *sba_dev)
अणु 
	पूर्णांक i;
	पूर्णांक num_ioc;
	u64 ioc_ctl;

	अगर (!is_pdc_pat()) अणु
		/* Shutकरोwn the USB controller on Astro-based workstations.
		** Once we reprogram the IOMMU, the next DMA perक्रमmed by
		** USB will HPMC the box. USB is only enabled अगर a
		** keyboard is present and found.
		**
		** With serial console, j6k v5.0 firmware says:
		**   mem_kbd hpa 0xfee003f8 sba 0x0 pad 0x0 cl_class 0x7
		**
		** FIXME: Using GFX+USB console at घातer up but direct
		**	linux to serial console is still broken.
		**	USB could generate DMA so we must reset USB.
		**	The proper sequence would be:
		**	o block console output
		**	o reset USB device
		**	o reprogram serial port
		**	o unblock console output
		*/
		अगर (PAGE0->mem_kbd.cl_class == CL_KEYBD) अणु
			pdc_io_reset_devices();
		पूर्ण

	पूर्ण


#अगर 0
prपूर्णांकk("sba_hw_init(): mem_boot 0x%x 0x%x 0x%x 0x%x\n", PAGE0->mem_boot.hpa,
	PAGE0->mem_boot.spa, PAGE0->mem_boot.pad, PAGE0->mem_boot.cl_class);

	/*
	** Need to deal with DMA from LAN.
	**	Maybe use page zero boot device as a handle to talk
	**	to PDC about which device to shutकरोwn.
	**
	** Netbooting, j6k v5.0 firmware says:
	** 	mem_boot hpa 0xf4008000 sba 0x0 pad 0x0 cl_class 0x1002
	** ARGH! invalid class.
	*/
	अगर ((PAGE0->mem_boot.cl_class != CL_RANDOM)
		&& (PAGE0->mem_boot.cl_class != CL_SEQU)) अणु
			pdc_io_reset();
	पूर्ण
#पूर्ण_अगर

	अगर (!IS_PLUTO(sba_dev->dev)) अणु
		ioc_ctl = READ_REG(sba_dev->sba_hpa+IOC_CTRL);
		DBG_INIT("%s() hpa 0x%lx ioc_ctl 0x%Lx ->",
			__func__, sba_dev->sba_hpa, ioc_ctl);
		ioc_ctl &= ~(IOC_CTRL_RM | IOC_CTRL_NC | IOC_CTRL_CE);
		ioc_ctl |= IOC_CTRL_DD | IOC_CTRL_D4 | IOC_CTRL_TC;
			/* j6700 v1.6 firmware sets 0x294f */
			/* A500 firmware sets 0x4d */

		WRITE_REG(ioc_ctl, sba_dev->sba_hpa+IOC_CTRL);

#अगर_घोषित DEBUG_SBA_INIT
		ioc_ctl = READ_REG64(sba_dev->sba_hpa+IOC_CTRL);
		DBG_INIT(" 0x%Lx\n", ioc_ctl);
#पूर्ण_अगर
	पूर्ण /* अगर !PLUTO */

	अगर (IS_ASTRO(sba_dev->dev)) अणु
		पूर्णांक err;
		sba_dev->ioc[0].ioc_hpa = ioc_remap(sba_dev, ASTRO_IOC_OFFSET);
		num_ioc = 1;

		sba_dev->chip_resv.name = "Astro Intr Ack";
		sba_dev->chip_resv.start = PCI_F_EXTEND | 0xfef00000UL;
		sba_dev->chip_resv.end   = PCI_F_EXTEND | (0xff000000UL - 1) ;
		err = request_resource(&iomem_resource, &(sba_dev->chip_resv));
		BUG_ON(err < 0);

	पूर्ण अन्यथा अगर (IS_PLUTO(sba_dev->dev)) अणु
		पूर्णांक err;

		sba_dev->ioc[0].ioc_hpa = ioc_remap(sba_dev, PLUTO_IOC_OFFSET);
		num_ioc = 1;

		sba_dev->chip_resv.name = "Pluto Intr/PIOP/VGA";
		sba_dev->chip_resv.start = PCI_F_EXTEND | 0xfee00000UL;
		sba_dev->chip_resv.end   = PCI_F_EXTEND | (0xff200000UL - 1);
		err = request_resource(&iomem_resource, &(sba_dev->chip_resv));
		WARN_ON(err < 0);

		sba_dev->iommu_resv.name = "IOVA Space";
		sba_dev->iommu_resv.start = 0x40000000UL;
		sba_dev->iommu_resv.end   = 0x50000000UL - 1;
		err = request_resource(&iomem_resource, &(sba_dev->iommu_resv));
		WARN_ON(err < 0);
	पूर्ण अन्यथा अणु
		/* IKE, REO */
		sba_dev->ioc[0].ioc_hpa = ioc_remap(sba_dev, IKE_IOC_OFFSET(0));
		sba_dev->ioc[1].ioc_hpa = ioc_remap(sba_dev, IKE_IOC_OFFSET(1));
		num_ioc = 2;

		/* TODO - LOOKUP Ike/Stretch chipset mem map */
	पूर्ण
	/* XXX: What about Reo Gअक्रमe? */

	sba_dev->num_ioc = num_ioc;
	क्रम (i = 0; i < num_ioc; i++) अणु
		व्योम __iomem *ioc_hpa = sba_dev->ioc[i].ioc_hpa;
		अचिन्हित पूर्णांक j;

		क्रम (j=0; j < माप(u64) * ROPES_PER_IOC; j+=माप(u64)) अणु

			/*
			 * Clear ROPE(N)_CONFIG AO bit.
			 * Disables "NT Ordering" (~= !"Relaxed Ordering")
			 * Overrides bit 1 in DMA Hपूर्णांक Sets.
			 * Improves netperf UDP_STREAM by ~10% क्रम bcm5701.
			 */
			अगर (IS_PLUTO(sba_dev->dev)) अणु
				व्योम __iomem *rope_cfg;
				अचिन्हित दीर्घ cfg_val;

				rope_cfg = ioc_hpa + IOC_ROPE0_CFG + j;
				cfg_val = READ_REG(rope_cfg);
				cfg_val &= ~IOC_ROPE_AO;
				WRITE_REG(cfg_val, rope_cfg);
			पूर्ण

			/*
			** Make sure the box crashes on rope errors.
			*/
			WRITE_REG(HF_ENABLE, ioc_hpa + ROPE0_CTL + j);
		पूर्ण

		/* flush out the last ग_लिखोs */
		READ_REG(sba_dev->ioc[i].ioc_hpa + ROPE7_CTL);

		DBG_INIT("	ioc[%d] ROPE_CFG 0x%Lx  ROPE_DBG 0x%Lx\n",
				i,
				READ_REG(sba_dev->ioc[i].ioc_hpa + 0x40),
				READ_REG(sba_dev->ioc[i].ioc_hpa + 0x50)
			);
		DBG_INIT("	STATUS_CONTROL 0x%Lx  FLUSH_CTRL 0x%Lx\n",
				READ_REG(sba_dev->ioc[i].ioc_hpa + 0x108),
				READ_REG(sba_dev->ioc[i].ioc_hpa + 0x400)
			);

		अगर (IS_PLUTO(sba_dev->dev)) अणु
			sba_ioc_init_pluto(sba_dev->dev, &(sba_dev->ioc[i]), i);
		पूर्ण अन्यथा अणु
			sba_ioc_init(sba_dev->dev, &(sba_dev->ioc[i]), i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
sba_common_init(काष्ठा sba_device *sba_dev)
अणु
	पूर्णांक i;

	/* add this one to the head of the list (order करोesn't matter)
	** This will be useful क्रम debugging - especially अगर we get coredumps
	*/
	sba_dev->next = sba_list;
	sba_list = sba_dev;

	क्रम(i=0; i< sba_dev->num_ioc; i++) अणु
		पूर्णांक res_size;
#अगर_घोषित DEBUG_DMB_TRAP
		बाह्य व्योम iterate_pages(अचिन्हित दीर्घ , अचिन्हित दीर्घ ,
					  व्योम (*)(pte_t * , अचिन्हित दीर्घ),
					  अचिन्हित दीर्घ );
		व्योम set_data_memory_अवरोध(pte_t * , अचिन्हित दीर्घ);
#पूर्ण_अगर
		/* resource map size dictated by pdir_size */
		res_size = sba_dev->ioc[i].pdir_size/माप(u64); /* entries */

		/* Second part of PIRANHA BUG */
		अगर (piranha_bad_128k) अणु
			res_size -= (128*1024)/माप(u64);
		पूर्ण

		res_size >>= 3;  /* convert bit count to byte count */
		DBG_INIT("%s() res_size 0x%x\n",
			__func__, res_size);

		sba_dev->ioc[i].res_size = res_size;
		sba_dev->ioc[i].res_map = (अक्षर *) __get_मुक्त_pages(GFP_KERNEL, get_order(res_size));

#अगर_घोषित DEBUG_DMB_TRAP
		iterate_pages( sba_dev->ioc[i].res_map, res_size,
				set_data_memory_अवरोध, 0);
#पूर्ण_अगर

		अगर (शून्य == sba_dev->ioc[i].res_map)
		अणु
			panic("%s:%s() could not allocate resource map\n",
			      __खाता__, __func__ );
		पूर्ण

		स_रखो(sba_dev->ioc[i].res_map, 0, res_size);
		/* next available IOVP - circular search */
		sba_dev->ioc[i].res_hपूर्णांक = (अचिन्हित दीर्घ *)
				&(sba_dev->ioc[i].res_map[L1_CACHE_BYTES]);

#अगर_घोषित ASSERT_Pसूची_SANITY
		/* Mark first bit busy - ie no IOVA 0 */
		sba_dev->ioc[i].res_map[0] = 0x80;
		sba_dev->ioc[i].pdir_base[0] = 0xeeffc0addbba0080ULL;
#पूर्ण_अगर

		/* Third (and last) part of PIRANHA BUG */
		अगर (piranha_bad_128k) अणु
			/* region from +1408K to +1536 is un-usable. */

			पूर्णांक idx_start = (1408*1024/माप(u64)) >> 3;
			पूर्णांक idx_end   = (1536*1024/माप(u64)) >> 3;
			दीर्घ *p_start = (दीर्घ *) &(sba_dev->ioc[i].res_map[idx_start]);
			दीर्घ *p_end   = (दीर्घ *) &(sba_dev->ioc[i].res_map[idx_end]);

			/* mark that part of the io pdir busy */
			जबतक (p_start < p_end)
				*p_start++ = -1;
				
		पूर्ण

#अगर_घोषित DEBUG_DMB_TRAP
		iterate_pages( sba_dev->ioc[i].res_map, res_size,
				set_data_memory_अवरोध, 0);
		iterate_pages( sba_dev->ioc[i].pdir_base, sba_dev->ioc[i].pdir_size,
				set_data_memory_अवरोध, 0);
#पूर्ण_अगर

		DBG_INIT("%s() %d res_map %x %p\n",
			__func__, i, res_size, sba_dev->ioc[i].res_map);
	पूर्ण

	spin_lock_init(&sba_dev->sba_lock);
	ioc_needs_fdc = boot_cpu_data.pdc.capabilities & PDC_MODEL_IOPसूची_FDC;

#अगर_घोषित DEBUG_SBA_INIT
	/*
	 * If the PDC_MODEL capabilities has Non-coherent IO-Pसूची bit set
	 * (bit #61, big endian), we have to flush and sync every समय
	 * IO-Pसूची is changed in Ike/Astro.
	 */
	अगर (ioc_needs_fdc) अणु
		prपूर्णांकk(KERN_INFO MODULE_NAME " FDC/SYNC required.\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO MODULE_NAME " IOC has cache coherent PDIR.\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sba_proc_info(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा sba_device *sba_dev = sba_list;
	काष्ठा ioc *ioc = &sba_dev->ioc[0];	/* FIXME: Multi-IOC support! */
	पूर्णांक total_pages = (पूर्णांक) (ioc->res_size << 3); /* 8 bits per byte */
#अगर_घोषित SBA_COLLECT_STATS
	अचिन्हित दीर्घ avg = 0, min, max;
#पूर्ण_अगर
	पूर्णांक i;

	seq_म_लिखो(m, "%s rev %d.%d\n",
		   sba_dev->name,
		   (sba_dev->hw_rev & 0x7) + 1,
		   (sba_dev->hw_rev & 0x18) >> 3);
	seq_म_लिखो(m, "IO PDIR size    : %d bytes (%d entries)\n",
		   (पूर्णांक)((ioc->res_size << 3) * माप(u64)), /* 8 bits/byte */
		   total_pages);

	seq_म_लिखो(m, "Resource bitmap : %d bytes (%d pages)\n",
		   ioc->res_size, ioc->res_size << 3);   /* 8 bits per byte */

	seq_म_लिखो(m, "LMMIO_BASE/MASK/ROUTE %08x %08x %08x\n",
		   READ_REG32(sba_dev->sba_hpa + LMMIO_DIST_BASE),
		   READ_REG32(sba_dev->sba_hpa + LMMIO_DIST_MASK),
		   READ_REG32(sba_dev->sba_hpa + LMMIO_DIST_ROUTE));

	क्रम (i=0; i<4; i++)
		seq_म_लिखो(m, "DIR%d_BASE/MASK/ROUTE %08x %08x %08x\n",
			   i,
			   READ_REG32(sba_dev->sba_hpa + LMMIO_सूचीECT0_BASE  + i*0x18),
			   READ_REG32(sba_dev->sba_hpa + LMMIO_सूचीECT0_MASK  + i*0x18),
			   READ_REG32(sba_dev->sba_hpa + LMMIO_सूचीECT0_ROUTE + i*0x18));

#अगर_घोषित SBA_COLLECT_STATS
	seq_म_लिखो(m, "IO PDIR entries : %ld free  %ld used (%d%%)\n",
		   total_pages - ioc->used_pages, ioc->used_pages,
		   (पूर्णांक)(ioc->used_pages * 100 / total_pages));

	min = max = ioc->avg_search[0];
	क्रम (i = 0; i < SBA_SEARCH_SAMPLE; i++) अणु
		avg += ioc->avg_search[i];
		अगर (ioc->avg_search[i] > max) max = ioc->avg_search[i];
		अगर (ioc->avg_search[i] < min) min = ioc->avg_search[i];
	पूर्ण
	avg /= SBA_SEARCH_SAMPLE;
	seq_म_लिखो(m, "  Bitmap search : %ld/%ld/%ld (min/avg/max CPU Cycles)\n",
		   min, avg, max);

	seq_म_लिखो(m, "pci_map_single(): %12ld calls  %12ld pages (avg %d/1000)\n",
		   ioc->msingle_calls, ioc->msingle_pages,
		   (पूर्णांक)((ioc->msingle_pages * 1000)/ioc->msingle_calls));

	/* KLUGE - unmap_sg calls unmap_single क्रम each mapped page */
	min = ioc->usingle_calls;
	max = ioc->usingle_pages - ioc->usg_pages;
	seq_म_लिखो(m, "pci_unmap_single: %12ld calls  %12ld pages (avg %d/1000)\n",
		   min, max, (पूर्णांक)((max * 1000)/min));

	seq_म_लिखो(m, "pci_map_sg()    : %12ld calls  %12ld pages (avg %d/1000)\n",
		   ioc->msg_calls, ioc->msg_pages,
		   (पूर्णांक)((ioc->msg_pages * 1000)/ioc->msg_calls));

	seq_म_लिखो(m, "pci_unmap_sg()  : %12ld calls  %12ld pages (avg %d/1000)\n",
		   ioc->usg_calls, ioc->usg_pages,
		   (पूर्णांक)((ioc->usg_pages * 1000)/ioc->usg_calls));
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक
sba_proc_biपंचांगap_info(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा sba_device *sba_dev = sba_list;
	काष्ठा ioc *ioc = &sba_dev->ioc[0];	/* FIXME: Multi-IOC support! */

	seq_hex_dump(m, "   ", DUMP_PREFIX_NONE, 32, 4, ioc->res_map,
		     ioc->res_size, false);
	seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल स्थिर काष्ठा parisc_device_id sba_tbl[] __initस्थिर = अणु
	अणु HPHW_IOA, HVERSION_REV_ANY_ID, ASTRO_RUNWAY_PORT, 0xb पूर्ण,
	अणु HPHW_BCPORT, HVERSION_REV_ANY_ID, IKE_MERCED_PORT, 0xc पूर्ण,
	अणु HPHW_BCPORT, HVERSION_REV_ANY_ID, REO_MERCED_PORT, 0xc पूर्ण,
	अणु HPHW_BCPORT, HVERSION_REV_ANY_ID, REOG_MERCED_PORT, 0xc पूर्ण,
	अणु HPHW_IOA, HVERSION_REV_ANY_ID, PLUTO_MCKINLEY_PORT, 0xc पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक sba_driver_callback(काष्ठा parisc_device *);

अटल काष्ठा parisc_driver sba_driver __refdata = अणु
	.name =		MODULE_NAME,
	.id_table =	sba_tbl,
	.probe =	sba_driver_callback,
पूर्ण;

/*
** Determine अगर sba should claim this chip (वापस 0) or not (वापस 1).
** If so, initialize the chip and tell other partners in crime they
** have work to करो.
*/
अटल पूर्णांक __init sba_driver_callback(काष्ठा parisc_device *dev)
अणु
	काष्ठा sba_device *sba_dev;
	u32 func_class;
	पूर्णांक i;
	अक्षर *version;
	व्योम __iomem *sba_addr = ioremap(dev->hpa.start, SBA_FUNC_SIZE);
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *root;
#पूर्ण_अगर

	sba_dump_ranges(sba_addr);

	/* Read HW Rev First */
	func_class = READ_REG(sba_addr + SBA_FCLASS);

	अगर (IS_ASTRO(dev)) अणु
		अचिन्हित दीर्घ fclass;
		अटल अक्षर astro_rev[]="Astro ?.?";

		/* Astro is broken...Read HW Rev First */
		fclass = READ_REG(sba_addr);

		astro_rev[6] = '1' + (अक्षर) (fclass & 0x7);
		astro_rev[8] = '0' + (अक्षर) ((fclass & 0x18) >> 3);
		version = astro_rev;

	पूर्ण अन्यथा अगर (IS_IKE(dev)) अणु
		अटल अक्षर ike_rev[] = "Ike rev ?";
		ike_rev[8] = '0' + (अक्षर) (func_class & 0xff);
		version = ike_rev;
	पूर्ण अन्यथा अगर (IS_PLUTO(dev)) अणु
		अटल अक्षर pluto_rev[]="Pluto ?.?";
		pluto_rev[6] = '0' + (अक्षर) ((func_class & 0xf0) >> 4); 
		pluto_rev[8] = '0' + (अक्षर) (func_class & 0x0f); 
		version = pluto_rev;
	पूर्ण अन्यथा अणु
		अटल अक्षर reo_rev[] = "REO rev ?";
		reo_rev[8] = '0' + (अक्षर) (func_class & 0xff);
		version = reo_rev;
	पूर्ण

	अगर (!global_ioc_cnt) अणु
		global_ioc_cnt = count_parisc_driver(&sba_driver);

		/* Astro and Pluto have one IOC per SBA */
		अगर ((!IS_ASTRO(dev)) || (!IS_PLUTO(dev)))
			global_ioc_cnt *= 2;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s found %s at 0x%llx\n",
		MODULE_NAME, version, (अचिन्हित दीर्घ दीर्घ)dev->hpa.start);

	sba_dev = kzalloc(माप(काष्ठा sba_device), GFP_KERNEL);
	अगर (!sba_dev) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME " - couldn't alloc sba_device\n");
		वापस -ENOMEM;
	पूर्ण

	parisc_set_drvdata(dev, sba_dev);

	क्रम(i=0; i<MAX_IOC; i++)
		spin_lock_init(&(sba_dev->ioc[i].res_lock));

	sba_dev->dev = dev;
	sba_dev->hw_rev = func_class;
	sba_dev->name = dev->name;
	sba_dev->sba_hpa = sba_addr;

	sba_get_pat_resources(sba_dev);
	sba_hw_init(sba_dev);
	sba_common_init(sba_dev);

	hppa_dma_ops = &sba_ops;

#अगर_घोषित CONFIG_PROC_FS
	चयन (dev->id.hversion) अणु
	हाल PLUTO_MCKINLEY_PORT:
		root = proc_mckinley_root;
		अवरोध;
	हाल ASTRO_RUNWAY_PORT:
	हाल IKE_MERCED_PORT:
	शेष:
		root = proc_runway_root;
		अवरोध;
	पूर्ण

	proc_create_single("sba_iommu", 0, root, sba_proc_info);
	proc_create_single("sba_iommu-bitmap", 0, root, sba_proc_biपंचांगap_info);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
** One समय initialization to let the world know the SBA was found.
** This is the only routine which is NOT अटल.
** Must be called exactly once beक्रमe pci_init().
*/
व्योम __init sba_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&sba_driver);
पूर्ण


/**
 * sba_get_iommu - Assign the iommu poपूर्णांकer क्रम the pci bus controller.
 * @dev: The parisc device.
 *
 * Returns the appropriate IOMMU data क्रम the given parisc PCI controller.
 * This is cached and used later क्रम PCI DMA Mapping.
 */
व्योम * sba_get_iommu(काष्ठा parisc_device *pci_hba)
अणु
	काष्ठा parisc_device *sba_dev = parisc_parent(pci_hba);
	काष्ठा sba_device *sba = dev_get_drvdata(&sba_dev->dev);
	अक्षर t = sba_dev->id.hw_type;
	पूर्णांक iocnum = (pci_hba->hw_path >> 3);	/* rope # */

	WARN_ON((t != HPHW_IOA) && (t != HPHW_BCPORT));

	वापस &(sba->ioc[iocnum]);
पूर्ण


/**
 * sba_directed_lmmio - वापस first directed LMMIO range routed to rope
 * @pa_dev: The parisc device.
 * @r: resource PCI host controller wants start/end fields asचिन्हित.
 *
 * For the given parisc PCI controller, determine अगर any direct ranges
 * are routed करोwn the corresponding rope.
 */
व्योम sba_directed_lmmio(काष्ठा parisc_device *pci_hba, काष्ठा resource *r)
अणु
	काष्ठा parisc_device *sba_dev = parisc_parent(pci_hba);
	काष्ठा sba_device *sba = dev_get_drvdata(&sba_dev->dev);
	अक्षर t = sba_dev->id.hw_type;
	पूर्णांक i;
	पूर्णांक rope = (pci_hba->hw_path & (ROPES_PER_IOC-1));  /* rope # */

	BUG_ON((t!=HPHW_IOA) && (t!=HPHW_BCPORT));

	r->start = r->end = 0;

	/* Astro has 4 directed ranges. Not sure about Ike/Pluto/et al */
	क्रम (i=0; i<4; i++) अणु
		पूर्णांक base, size;
		व्योम __iomem *reg = sba->sba_hpa + i*0x18;

		base = READ_REG32(reg + LMMIO_सूचीECT0_BASE);
		अगर ((base & 1) == 0)
			जारी;	/* not enabled */

		size = READ_REG32(reg + LMMIO_सूचीECT0_ROUTE);

		अगर ((size & (ROPES_PER_IOC-1)) != rope)
			जारी;	/* directed करोwn dअगरferent rope */
		
		r->start = (base & ~1UL) | PCI_F_EXTEND;
		size = ~ READ_REG32(reg + LMMIO_सूचीECT0_MASK);
		r->end = r->start + size;
		r->flags = IORESOURCE_MEM;
	पूर्ण
पूर्ण


/**
 * sba_distributed_lmmio - वापस portion of distributed LMMIO range
 * @pa_dev: The parisc device.
 * @r: resource PCI host controller wants start/end fields asचिन्हित.
 *
 * For the given parisc PCI controller, वापस portion of distributed LMMIO
 * range. The distributed LMMIO is always present and it's just a question
 * of the base address and size of the range.
 */
व्योम sba_distributed_lmmio(काष्ठा parisc_device *pci_hba, काष्ठा resource *r )
अणु
	काष्ठा parisc_device *sba_dev = parisc_parent(pci_hba);
	काष्ठा sba_device *sba = dev_get_drvdata(&sba_dev->dev);
	अक्षर t = sba_dev->id.hw_type;
	पूर्णांक base, size;
	पूर्णांक rope = (pci_hba->hw_path & (ROPES_PER_IOC-1));  /* rope # */

	BUG_ON((t!=HPHW_IOA) && (t!=HPHW_BCPORT));

	r->start = r->end = 0;

	base = READ_REG32(sba->sba_hpa + LMMIO_DIST_BASE);
	अगर ((base & 1) == 0) अणु
		BUG();	/* Gah! Distr Range wasn't enabled! */
		वापस;
	पूर्ण

	r->start = (base & ~1UL) | PCI_F_EXTEND;

	size = (~READ_REG32(sba->sba_hpa + LMMIO_DIST_MASK)) / ROPES_PER_IOC;
	r->start += rope * (size + 1);	/* adjust base क्रम this rope */
	r->end = r->start + size;
	r->flags = IORESOURCE_MEM;
पूर्ण
