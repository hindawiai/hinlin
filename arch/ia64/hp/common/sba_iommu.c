<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
**  IA64 System Bus Adapter (SBA) I/O MMU manager
**
**	(c) Copyright 2002-2005 Alex Williamson
**	(c) Copyright 2002-2003 Grant Grundler
**	(c) Copyright 2002-2005 Hewlett-Packard Company
**
**	Portions (c) 2000 Grant Grundler (from parisc I/O MMU code)
**	Portions (c) 1999 Dave S. Miller (from sparc64 I/O MMU code)
**
**
**
** This module initializes the IOC (I/O Controller) found on HP
** McKinley machines and their successors.
**
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/bitops.h>         /* hweight64() */
#समावेश <linux/crash_dump.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/swiotlb.h>

#समावेश <यंत्र/delay.h>		/* ia64_get_itc() */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>		/* PAGE_OFFSET */
#समावेश <यंत्र/dma.h>

#समावेश <यंत्र/acpi-ext.h>

#घोषणा PFX "IOC: "

/*
** Enabling timing search of the pdir resource map.  Output in /proc.
** Disabled by शेष to optimize perक्रमmance.
*/
#अघोषित Pसूची_SEARCH_TIMING

/*
** This option allows cards capable of 64bit DMA to bypass the IOMMU.  If
** not defined, all DMA will be 32bit and go through the TLB.
** There's potentially a conflict in the bio merge code with us
** advertising an iommu, but then bypassing it.  Since I/O MMU bypassing
** appears to give more perक्रमmance than bio-level भव merging, we'll
** करो the क्रमmer क्रम now.  NOTE: BYPASS_SG also needs to be undef'd to
** completely restrict DMA to the IOMMU.
*/
#घोषणा ALLOW_IOV_BYPASS

/*
** This option specअगरically allows/disallows bypassing scatterlists with
** multiple entries.  Coalescing these entries can allow better DMA streaming
** and in some हालs shows better perक्रमmance than entirely bypassing the
** IOMMU.  Perक्रमmance increase on the order of 1-2% sequential output/input
** using bonnie++ on a RAID0 MD device (sym2 & mpt).
*/
#अघोषित ALLOW_IOV_BYPASS_SG

/*
** If a device prefetches beyond the end of a valid pdir entry, it will cause
** a hard failure, ie. MCA.  Version 3.0 and later of the zx1 LBA should
** disconnect on 4k boundaries and prevent such issues.  If the device is
** particularly aggressive, this option will keep the entire pdir valid such
** that prefetching will hit a valid address.  This could severely impact
** error containment, and is thereक्रमe off by शेष.  The page that is
** used क्रम spill-over is poisoned, so that should help debugging somewhat.
*/
#अघोषित FULL_VALID_Pसूची

#घोषणा ENABLE_MARK_CLEAN

/*
** The number of debug flags is a clue - this code is fragile.  NOTE: since
** tightening the use of res_lock the resource biपंचांगap and actual pdir are no
** दीर्घer guaranteed to stay in sync.  The sanity checking code isn't going to
** like that.
*/
#अघोषित DEBUG_SBA_INIT
#अघोषित DEBUG_SBA_RUN
#अघोषित DEBUG_SBA_RUN_SG
#अघोषित DEBUG_SBA_RESOURCE
#अघोषित ASSERT_Pसूची_SANITY
#अघोषित DEBUG_LARGE_SG_ENTRIES
#अघोषित DEBUG_BYPASS

#अगर defined(FULL_VALID_Pसूची) && defined(ASSERT_Pसूची_SANITY)
#त्रुटि FULL_VALID_Pसूची and ASSERT_Pसूची_SANITY are mutually exclusive
#पूर्ण_अगर

#घोषणा SBA_INLINE	__अंतरभूत__
/* #घोषणा SBA_INLINE */

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

#अगर_घोषित DEBUG_BYPASS
#घोषणा DBG_BYPASS(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_BYPASS(x...)
#पूर्ण_अगर

#अगर_घोषित ASSERT_Pसूची_SANITY
#घोषणा ASSERT(expr) \
        अगर(!(expr)) अणु \
                prपूर्णांकk( "\n" __खाता__ ":%d: Assertion " #expr " failed!\n",__LINE__); \
                panic(#expr); \
        पूर्ण
#अन्यथा
#घोषणा ASSERT(expr)
#पूर्ण_अगर

/*
** The number of pdir entries to "free" beक्रमe issuing
** a पढ़ो to PCOM रेजिस्टर to flush out PCOM ग_लिखोs.
** Interacts with allocation granularity (ie 4 or 8 entries
** allocated and मुक्त'd/purged at a समय might make this
** less पूर्णांकeresting).
*/
#घोषणा DELAYED_RESOURCE_CNT	64

#घोषणा PCI_DEVICE_ID_HP_SX2000_IOC	0x12ec

#घोषणा ZX1_IOC_ID	((PCI_DEVICE_ID_HP_ZX1_IOC << 16) | PCI_VENDOR_ID_HP)
#घोषणा ZX2_IOC_ID	((PCI_DEVICE_ID_HP_ZX2_IOC << 16) | PCI_VENDOR_ID_HP)
#घोषणा REO_IOC_ID	((PCI_DEVICE_ID_HP_REO_IOC << 16) | PCI_VENDOR_ID_HP)
#घोषणा SX1000_IOC_ID	((PCI_DEVICE_ID_HP_SX1000_IOC << 16) | PCI_VENDOR_ID_HP)
#घोषणा SX2000_IOC_ID	((PCI_DEVICE_ID_HP_SX2000_IOC << 16) | PCI_VENDOR_ID_HP)

#घोषणा ZX1_IOC_OFFSET	0x1000	/* ACPI reports SBA, we want IOC */

#घोषणा IOC_FUNC_ID	0x000
#घोषणा IOC_FCLASS	0x008	/* function class, bist, header, rev... */
#घोषणा IOC_IBASE	0x300	/* IO TLB */
#घोषणा IOC_IMASK	0x308
#घोषणा IOC_PCOM	0x310
#घोषणा IOC_TCNFG	0x318
#घोषणा IOC_Pसूची_BASE	0x320

#घोषणा IOC_ROPE0_CFG	0x500
#घोषणा   IOC_ROPE_AO	  0x10	/* Allow "Relaxed Ordering" */


/* AGP GART driver looks क्रम this */
#घोषणा ZX1_SBA_IOMMU_COOKIE	0x0000badbadc0ffeeUL

/*
** The zx1 IOC supports 4/8/16/64KB page sizes (see TCNFG रेजिस्टर)
**
** Some IOCs (sx1000) can run at the above pages sizes, but are
** really only supported using the IOC at a 4k page size.
**
** iovp_size could only be greater than PAGE_SIZE अगर we are
** confident the drivers really only touch the next physical
** page अगरf that driver instance owns it.
*/
अटल अचिन्हित दीर्घ iovp_size;
अटल अचिन्हित दीर्घ iovp_shअगरt;
अटल अचिन्हित दीर्घ iovp_mask;

काष्ठा ioc अणु
	व्योम __iomem	*ioc_hpa;	/* I/O MMU base address */
	अक्षर		*res_map;	/* resource map, bit == pdir entry */
	u64		*pdir_base;	/* physical base address */
	अचिन्हित दीर्घ	ibase;		/* pdir IOV Space base */
	अचिन्हित दीर्घ	imask;		/* pdir IOV Space mask */

	अचिन्हित दीर्घ	*res_hपूर्णांक;	/* next avail IOVP - circular search */
	अचिन्हित दीर्घ	dma_mask;
	spinlock_t	res_lock;	/* protects the resource biपंचांगap, but must be held when */
					/* clearing pdir to prevent races with allocations. */
	अचिन्हित पूर्णांक	res_bitshअगरt;	/* from the RIGHT! */
	अचिन्हित पूर्णांक	res_size;	/* size of resource map in bytes */
#अगर_घोषित CONFIG_NUMA
	अचिन्हित पूर्णांक	node;		/* node where this IOC lives */
#पूर्ण_अगर
#अगर DELAYED_RESOURCE_CNT > 0
	spinlock_t	saved_lock;	/* may want to try to get this on a separate cacheline */
					/* than res_lock क्रम bigger प्रणालीs. */
	पूर्णांक		saved_cnt;
	काष्ठा sba_dma_pair अणु
		dma_addr_t	iova;
		माप_प्रकार		size;
	पूर्ण saved[DELAYED_RESOURCE_CNT];
#पूर्ण_अगर

#अगर_घोषित Pसूची_SEARCH_TIMING
#घोषणा SBA_SEARCH_SAMPLE	0x100
	अचिन्हित दीर्घ avg_search[SBA_SEARCH_SAMPLE];
	अचिन्हित दीर्घ avg_idx;	/* current index पूर्णांकo avg_search */
#पूर्ण_अगर

	/* Stuff we करोn't need in perक्रमmance path */
	काष्ठा ioc	*next;		/* list of IOC's in प्रणाली */
	acpi_handle	handle;		/* क्रम multiple IOC's */
	स्थिर अक्षर 	*name;
	अचिन्हित पूर्णांक	func_id;
	अचिन्हित पूर्णांक	rev;		/* HW revision of chip */
	u32		iov_size;
	अचिन्हित पूर्णांक	pdir_size;	/* in bytes, determined by IOV Space size */
	काष्ठा pci_dev	*sac_only_dev;
पूर्ण;

अटल काष्ठा ioc *ioc_list, *ioc_found;
अटल पूर्णांक reserve_sba_gart = 1;

अटल SBA_INLINE व्योम sba_mark_invalid(काष्ठा ioc *, dma_addr_t, माप_प्रकार);
अटल SBA_INLINE व्योम sba_मुक्त_range(काष्ठा ioc *, dma_addr_t, माप_प्रकार);

#घोषणा sba_sg_address(sg)	sg_virt((sg))

#अगर_घोषित FULL_VALID_Pसूची
अटल u64 prefetch_spill_page;
#पूर्ण_अगर

#घोषणा GET_IOC(dev)	((dev_is_pci(dev))						\
			 ? ((काष्ठा ioc *) PCI_CONTROLLER(to_pci_dev(dev))->iommu) : शून्य)

/*
** DMA_CHUNK_SIZE is used by the SCSI mid-layer to अवरोध up
** (or rather not merge) DMAs पूर्णांकo manageable chunks.
** On parisc, this is more of the software/tuning स्थिरraपूर्णांक
** rather than the HW. I/O MMU allocation algorithms can be
** faster with smaller sizes (to some degree).
*/
#घोषणा DMA_CHUNK_SIZE  (BITS_PER_LONG*iovp_size)

#घोषणा ROUNDUP(x,y) ((x + ((y)-1)) & ~((y)-1))

/************************************
** SBA रेजिस्टर पढ़ो and ग_लिखो support
**
** BE WARNED: रेजिस्टर ग_लिखोs are posted.
**  (ie follow ग_लिखोs which must reach HW with a पढ़ो)
**
*/
#घोषणा READ_REG(addr)       __raw_पढ़ोq(addr)
#घोषणा WRITE_REG(val, addr) __raw_ग_लिखोq(val, addr)

#अगर_घोषित DEBUG_SBA_INIT

/**
 * sba_dump_tlb - debugging only - prपूर्णांक IOMMU operating parameters
 * @hpa: base address of the IOMMU
 *
 * Prपूर्णांक the size/location of the IO MMU Pसूची.
 */
अटल व्योम
sba_dump_tlb(अक्षर *hpa)
अणु
	DBG_INIT("IO TLB at 0x%p\n", (व्योम *)hpa);
	DBG_INIT("IOC_IBASE    : %016lx\n", READ_REG(hpa+IOC_IBASE));
	DBG_INIT("IOC_IMASK    : %016lx\n", READ_REG(hpa+IOC_IMASK));
	DBG_INIT("IOC_TCNFG    : %016lx\n", READ_REG(hpa+IOC_TCNFG));
	DBG_INIT("IOC_PDIR_BASE: %016lx\n", READ_REG(hpa+IOC_Pसूची_BASE));
	DBG_INIT("\n");
पूर्ण
#पूर्ण_अगर


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
	u64 *ptr = &ioc->pdir_base[pide  & ~(BITS_PER_LONG - 1)];
	अचिन्हित दीर्घ *rptr = (अचिन्हित दीर्घ *) &ioc->res_map[(pide >>3) & -माप(अचिन्हित दीर्घ)];
	uपूर्णांक rcnt;

	prपूर्णांकk(KERN_DEBUG "SBA: %s rp %p bit %d rval 0x%lx\n",
		 msg, rptr, pide & (BITS_PER_LONG - 1), *rptr);

	rcnt = 0;
	जबतक (rcnt < BITS_PER_LONG) अणु
		prपूर्णांकk(KERN_DEBUG "%s %2d %p %016Lx\n",
		       (rcnt == (pide & (BITS_PER_LONG - 1)))
		       ? "    -->" : "       ",
		       rcnt, ptr, (अचिन्हित दीर्घ दीर्घ) *ptr );
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
	u64 *rptr_end = (u64 *) &(ioc->res_map[ioc->res_size]);
	u64 *rptr = (u64 *) ioc->res_map;	/* resource map ptr */
	u64 *pptr = ioc->pdir_base;	/* pdir ptr */
	uपूर्णांक pide = 0;

	जबतक (rptr < rptr_end) अणु
		u64 rval;
		पूर्णांक rcnt; /* number of bits we might check */

		rval = *rptr;
		rcnt = 64;

		जबतक (rcnt) अणु
			/* Get last byte and highest bit from that */
			u32 pde = ((u32)((*pptr >> (63)) & 0x1));
			अगर ((rval & 0x1) ^ pde)
			अणु
				/*
				** BUMMER!  -- res_map != pdir --
				** Dump rval and matching pdir entries
				*/
				sba_dump_pdir_entry(ioc, msg, pide);
				वापस(1);
			पूर्ण
			rcnt--;
			rval >>= 1;	/* try the next bit */
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
		prपूर्णांकk(KERN_DEBUG " %d : DMA %08lx/%05x CPU %p\n", nents,
		       startsg->dma_address, startsg->dma_length,
		       sba_sg_address(startsg));
		startsg = sg_next(startsg);
	पूर्ण
पूर्ण

अटल व्योम
sba_check_sg( काष्ठा ioc *ioc, काष्ठा scatterlist *startsg, पूर्णांक nents)
अणु
	काष्ठा scatterlist *the_sg = startsg;
	पूर्णांक the_nents = nents;

	जबतक (the_nents-- > 0) अणु
		अगर (sba_sg_address(the_sg) == 0x0UL)
			sba_dump_sg(शून्य, startsg, nents);
		the_sg = sg_next(the_sg);
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
#घोषणा SBA_IOVA(ioc,iovp,offset) ((ioc->ibase) | (iovp) | (offset))
#घोषणा SBA_IOVP(ioc,iova) ((iova) & ~(ioc->ibase))

#घोषणा Pसूची_ENTRY_SIZE	माप(u64)

#घोषणा Pसूची_INDEX(iovp)   ((iovp)>>iovp_shअगरt)

#घोषणा RESMAP_MASK(n)    ~(~0UL << (n))
#घोषणा RESMAP_IDX_MASK   (माप(अचिन्हित दीर्घ) - 1)


/**
 * For most हालs the normal get_order is sufficient, however it limits us
 * to PAGE_SIZE being the minimum mapping alignment and TC flush granularity.
 * It only incurs about 1 घड़ी cycle to use this one with the अटल variable
 * and makes the code more पूर्णांकuitive.
 */
अटल SBA_INLINE पूर्णांक
get_iovp_order (अचिन्हित दीर्घ size)
अणु
	दीर्घ द्विगुन d = size - 1;
	दीर्घ order;

	order = ia64_getf_exp(d);
	order = order - iovp_shअगरt - 0xffff + 1;
	अगर (order < 0)
		order = 0;
	वापस order;
पूर्ण

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
 * @use_hपूर्णांक: use res_hपूर्णांक to indicate where to start looking
 *
 * Find consecutive मुक्त bits in resource biपंचांगap.
 * Each bit represents one entry in the IO Pdir.
 * Cool perf optimization: search क्रम log2(size) bits at a समय.
 */
अटल SBA_INLINE अचिन्हित दीर्घ
sba_search_biपंचांगap(काष्ठा ioc *ioc, काष्ठा device *dev,
		  अचिन्हित दीर्घ bits_wanted, पूर्णांक use_hपूर्णांक)
अणु
	अचिन्हित दीर्घ *res_ptr;
	अचिन्हित दीर्घ *res_end = (अचिन्हित दीर्घ *) &(ioc->res_map[ioc->res_size]);
	अचिन्हित दीर्घ flags, pide = ~0UL, tpide;
	अचिन्हित दीर्घ boundary_size;
	अचिन्हित दीर्घ shअगरt;
	पूर्णांक ret;

	ASSERT(((अचिन्हित दीर्घ) ioc->res_hपूर्णांक & (माप(अचिन्हित दीर्घ) - 1UL)) == 0);
	ASSERT(res_ptr < res_end);

	boundary_size = dma_get_seg_boundary_nr_pages(dev, iovp_shअगरt);

	BUG_ON(ioc->ibase & ~iovp_mask);
	shअगरt = ioc->ibase >> iovp_shअगरt;

	spin_lock_irqsave(&ioc->res_lock, flags);

	/* Allow caller to क्रमce a search through the entire resource space */
	अगर (likely(use_hपूर्णांक)) अणु
		res_ptr = ioc->res_hपूर्णांक;
	पूर्ण अन्यथा अणु
		res_ptr = (uदीर्घ *)ioc->res_map;
		ioc->res_bitshअगरt = 0;
	पूर्ण

	/*
	 * N.B.  REO/Gअक्रमe defect AR2305 can cause TLB fetch समयouts
	 * अगर a TLB entry is purged जबतक in use.  sba_mark_invalid()
	 * purges IOTLB entries in घातer-of-two sizes, so we also
	 * allocate IOVA space in घातer-of-two sizes.
	 */
	bits_wanted = 1UL << get_iovp_order(bits_wanted << iovp_shअगरt);

	अगर (likely(bits_wanted == 1)) अणु
		अचिन्हित पूर्णांक bitshअगरtcnt;
		क्रम(; res_ptr < res_end ; res_ptr++) अणु
			अगर (likely(*res_ptr != ~0UL)) अणु
				bitshअगरtcnt = ffz(*res_ptr);
				*res_ptr |= (1UL << bitshअगरtcnt);
				pide = ptr_to_pide(ioc, res_ptr, bitshअगरtcnt);
				ioc->res_bitshअगरt = bitshअगरtcnt + bits_wanted;
				जाओ found_it;
			पूर्ण
		पूर्ण
		जाओ not_found;

	पूर्ण
	
	अगर (likely(bits_wanted <= BITS_PER_LONG/2)) अणु
		/*
		** Search the resource bit map on well-aligned values.
		** "o" is the alignment.
		** We need the alignment to invalidate I/O TLB using
		** SBA HW features in the unmap path.
		*/
		अचिन्हित दीर्घ o = 1 << get_iovp_order(bits_wanted << iovp_shअगरt);
		uपूर्णांक bitshअगरtcnt = ROUNDUP(ioc->res_bitshअगरt, o);
		अचिन्हित दीर्घ mask, base_mask;

		base_mask = RESMAP_MASK(bits_wanted);
		mask = base_mask << bitshअगरtcnt;

		DBG_RES("%s() o %ld %p", __func__, o, res_ptr);
		क्रम(; res_ptr < res_end ; res_ptr++)
		अणु 
			DBG_RES("    %p %lx %lx\n", res_ptr, mask, *res_ptr);
			ASSERT(0 != mask);
			क्रम (; mask ; mask <<= o, bitshअगरtcnt += o) अणु
				tpide = ptr_to_pide(ioc, res_ptr, bitshअगरtcnt);
				ret = iommu_is_span_boundary(tpide, bits_wanted,
							     shअगरt,
							     boundary_size);
				अगर ((0 == ((*res_ptr) & mask)) && !ret) अणु
					*res_ptr |= mask;     /* mark resources busy! */
					pide = tpide;
					ioc->res_bitshअगरt = bitshअगरtcnt + bits_wanted;
					जाओ found_it;
				पूर्ण
			पूर्ण

			bitshअगरtcnt = 0;
			mask = base_mask;

		पूर्ण

	पूर्ण अन्यथा अणु
		पूर्णांक qwords, bits, i;
		अचिन्हित दीर्घ *end;

		qwords = bits_wanted >> 6; /* /64 */
		bits = bits_wanted - (qwords * BITS_PER_LONG);

		end = res_end - qwords;

		क्रम (; res_ptr < end; res_ptr++) अणु
			tpide = ptr_to_pide(ioc, res_ptr, 0);
			ret = iommu_is_span_boundary(tpide, bits_wanted,
						     shअगरt, boundary_size);
			अगर (ret)
				जाओ next_ptr;
			क्रम (i = 0 ; i < qwords ; i++) अणु
				अगर (res_ptr[i] != 0)
					जाओ next_ptr;
			पूर्ण
			अगर (bits && res_ptr[i] && (__ffs(res_ptr[i]) < bits))
				जारी;

			/* Found it, mark it */
			क्रम (i = 0 ; i < qwords ; i++)
				res_ptr[i] = ~0UL;
			res_ptr[i] |= RESMAP_MASK(bits);

			pide = tpide;
			res_ptr += qwords;
			ioc->res_bitshअगरt = bits;
			जाओ found_it;
next_ptr:
			;
		पूर्ण
	पूर्ण

not_found:
	prefetch(ioc->res_map);
	ioc->res_hपूर्णांक = (अचिन्हित दीर्घ *) ioc->res_map;
	ioc->res_bitshअगरt = 0;
	spin_unlock_irqrestore(&ioc->res_lock, flags);
	वापस (pide);

found_it:
	ioc->res_hपूर्णांक = res_ptr;
	spin_unlock_irqrestore(&ioc->res_lock, flags);
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
	अचिन्हित पूर्णांक pages_needed = size >> iovp_shअगरt;
#अगर_घोषित Pसूची_SEARCH_TIMING
	अचिन्हित दीर्घ itc_start;
#पूर्ण_अगर
	अचिन्हित दीर्घ pide;

	ASSERT(pages_needed);
	ASSERT(0 == (size & ~iovp_mask));

#अगर_घोषित Pसूची_SEARCH_TIMING
	itc_start = ia64_get_itc();
#पूर्ण_अगर
	/*
	** "seek and ye shall find"...praying never hurts either...
	*/
	pide = sba_search_biपंचांगap(ioc, dev, pages_needed, 1);
	अगर (unlikely(pide >= (ioc->res_size << 3))) अणु
		pide = sba_search_biपंचांगap(ioc, dev, pages_needed, 0);
		अगर (unlikely(pide >= (ioc->res_size << 3))) अणु
#अगर DELAYED_RESOURCE_CNT > 0
			अचिन्हित दीर्घ flags;

			/*
			** With delayed resource मुक्तing, we can give this one more shot.  We're
			** getting बंद to being in trouble here, so करो what we can to make this
			** one count.
			*/
			spin_lock_irqsave(&ioc->saved_lock, flags);
			अगर (ioc->saved_cnt > 0) अणु
				काष्ठा sba_dma_pair *d;
				पूर्णांक cnt = ioc->saved_cnt;

				d = &(ioc->saved[ioc->saved_cnt - 1]);

				spin_lock(&ioc->res_lock);
				जबतक (cnt--) अणु
					sba_mark_invalid(ioc, d->iova, d->size);
					sba_मुक्त_range(ioc, d->iova, d->size);
					d--;
				पूर्ण
				ioc->saved_cnt = 0;
				READ_REG(ioc->ioc_hpa+IOC_PCOM);	/* flush purges */
				spin_unlock(&ioc->res_lock);
			पूर्ण
			spin_unlock_irqrestore(&ioc->saved_lock, flags);

			pide = sba_search_biपंचांगap(ioc, dev, pages_needed, 0);
			अगर (unlikely(pide >= (ioc->res_size << 3))) अणु
				prपूर्णांकk(KERN_WARNING "%s: I/O MMU @ %p is"
				       "out of mapping resources, %u %u %lx\n",
				       __func__, ioc->ioc_hpa, ioc->res_size,
				       pages_needed, dma_get_seg_boundary(dev));
				वापस -1;
			पूर्ण
#अन्यथा
			prपूर्णांकk(KERN_WARNING "%s: I/O MMU @ %p is"
			       "out of mapping resources, %u %u %lx\n",
			       __func__, ioc->ioc_hpa, ioc->res_size,
			       pages_needed, dma_get_seg_boundary(dev));
			वापस -1;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

#अगर_घोषित Pसूची_SEARCH_TIMING
	ioc->avg_search[ioc->avg_idx++] = (ia64_get_itc() - itc_start) / pages_needed;
	ioc->avg_idx &= SBA_SEARCH_SAMPLE - 1;
#पूर्ण_अगर

	prefetchw(&(ioc->pdir_base[pide]));

#अगर_घोषित ASSERT_Pसूची_SANITY
	/* verअगरy the first enable bit is clear */
	अगर(0x00 != ((u8 *) ioc->pdir_base)[pide*Pसूची_ENTRY_SIZE + 7]) अणु
		sba_dump_pdir_entry(ioc, "sba_search_bitmap() botched it?", pide);
	पूर्ण
#पूर्ण_अगर

	DBG_RES("%s(%x) %d -> %lx hint %x/%x\n",
		__func__, size, pages_needed, pide,
		(uपूर्णांक) ((अचिन्हित दीर्घ) ioc->res_hपूर्णांक - (अचिन्हित दीर्घ) ioc->res_map),
		ioc->res_bitshअगरt );

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
	पूर्णांक bits_not_wanted = size >> iovp_shअगरt;
	अचिन्हित दीर्घ m;

	/* Round up to घातer-of-two size: see AR2305 note above */
	bits_not_wanted = 1UL << get_iovp_order(bits_not_wanted << iovp_shअगरt);
	क्रम (; bits_not_wanted > 0 ; res_ptr++) अणु
		
		अगर (unlikely(bits_not_wanted > BITS_PER_LONG)) अणु

			/* these mappings start 64bit aligned */
			*res_ptr = 0UL;
			bits_not_wanted -= BITS_PER_LONG;
			pide += BITS_PER_LONG;

		पूर्ण अन्यथा अणु

			/* 3-bits "bit" address plus 2 (or 3) bits क्रम "byte" == bit in word */
			m = RESMAP_MASK(bits_not_wanted) << (pide & (BITS_PER_LONG - 1));
			bits_not_wanted = 0;

			DBG_RES("%s( ,%x,%x) %x/%lx %x %p %lx\n", __func__, (uपूर्णांक) iova, size,
			        bits_not_wanted, m, pide, res_ptr, *res_ptr);

			ASSERT(m != 0);
			ASSERT(bits_not_wanted);
			ASSERT((*res_ptr & m) == m); /* verअगरy same bits are set */
			*res_ptr &= ~m;
		पूर्ण
	पूर्ण
पूर्ण


/**************************************************************
*
*   "Dynamic DMA Mapping" support (aka "Coherent I/O")
*
***************************************************************/

/**
 * sba_io_pdir_entry - fill in one IO Pसूची entry
 * @pdir_ptr:  poपूर्णांकer to IO Pसूची entry
 * @vba: Virtual CPU address of buffer to map
 *
 * SBA Mapping Routine
 *
 * Given a भव address (vba, arg1) sba_io_pdir_entry()
 * loads the I/O Pसूची entry poपूर्णांकed to by pdir_ptr (arg0).
 * Each IO Pdir entry consists of 8 bytes as shown below
 * (LSB == bit 0):
 *
 *  63                    40                                 11    7        0
 * +-+---------------------+----------------------------------+----+--------+
 * |V|        U            |            PPN[39:12]            | U  |   FF   |
 * +-+---------------------+----------------------------------+----+--------+
 *
 *  V  == Valid Bit
 *  U  == Unused
 * PPN == Physical Page Number
 *
 * The physical address fields are filled with the results of virt_to_phys()
 * on the vba.
 */

#अगर 1
#घोषणा sba_io_pdir_entry(pdir_ptr, vba) *pdir_ptr = ((vba & ~0xE000000000000FFFULL)	\
						      | 0x8000000000000000ULL)
#अन्यथा
व्योम SBA_INLINE
sba_io_pdir_entry(u64 *pdir_ptr, अचिन्हित दीर्घ vba)
अणु
	*pdir_ptr = ((vba & ~0xE000000000000FFFULL) | 0x80000000000000FFULL);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित ENABLE_MARK_CLEAN
/**
 * Since DMA is i-cache coherent, any (complete) pages that were written via
 * DMA can be marked as "clean" so that lazy_mmu_prot_update() करोesn't have to
 * flush them when they get mapped पूर्णांकo an executable vm-area.
 */
अटल व्योम
mark_clean (व्योम *addr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ pg_addr, end;

	pg_addr = PAGE_ALIGN((अचिन्हित दीर्घ) addr);
	end = (अचिन्हित दीर्घ) addr + size;
	जबतक (pg_addr + PAGE_SIZE <= end) अणु
		काष्ठा page *page = virt_to_page((व्योम *)pg_addr);
		set_bit(PG_arch_1, &page->flags);
		pg_addr += PAGE_SIZE;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * sba_mark_invalid - invalidate one or more IO Pसूची entries
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @iova:  IO Virtual Address mapped earlier
 * @byte_cnt:  number of bytes this mapping covers.
 *
 * Marking the IO Pसूची entry(ies) as Invalid and invalidate
 * corresponding IO TLB entry. The PCOM (Purge Command Register)
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

	पूर्णांक off = Pसूची_INDEX(iovp);

	/* Must be non-zero and rounded up */
	ASSERT(byte_cnt > 0);
	ASSERT(0 == (byte_cnt & ~iovp_mask));

#अगर_घोषित ASSERT_Pसूची_SANITY
	/* Assert first pdir entry is set */
	अगर (!(ioc->pdir_base[off] >> 60)) अणु
		sba_dump_pdir_entry(ioc,"sba_mark_invalid()", Pसूची_INDEX(iovp));
	पूर्ण
#पूर्ण_अगर

	अगर (byte_cnt <= iovp_size)
	अणु
		ASSERT(off < ioc->pdir_size);

		iovp |= iovp_shअगरt;     /* set "size" field क्रम PCOM */

#अगर_अघोषित FULL_VALID_Pसूची
		/*
		** clear I/O Pसूची entry "valid" bit
		** Do NOT clear the rest - save it क्रम debugging.
		** We should only clear bits that have previously
		** been enabled.
		*/
		ioc->pdir_base[off] &= ~(0x80000000000000FFULL);
#अन्यथा
		/*
  		** If we want to मुख्यtain the Pसूची as valid, put in
		** the spill page so devices prefetching won't
		** cause a hard fail.
		*/
		ioc->pdir_base[off] = (0x80000000000000FFULL | prefetch_spill_page);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		u32 t = get_iovp_order(byte_cnt) + iovp_shअगरt;

		iovp |= t;
		ASSERT(t <= 31);   /* 2GB! Max value of "size" field */

		करो अणु
			/* verअगरy this pdir entry is enabled */
			ASSERT(ioc->pdir_base[off]  >> 63);
#अगर_अघोषित FULL_VALID_Pसूची
			/* clear I/O Pdir entry "valid" bit first */
			ioc->pdir_base[off] &= ~(0x80000000000000FFULL);
#अन्यथा
			ioc->pdir_base[off] = (0x80000000000000FFULL | prefetch_spill_page);
#पूर्ण_अगर
			off++;
			byte_cnt -= iovp_size;
		पूर्ण जबतक (byte_cnt > 0);
	पूर्ण

	WRITE_REG(iovp | ioc->ibase, ioc->ioc_hpa+IOC_PCOM);
पूर्ण

/**
 * sba_map_page - map one buffer and वापस IOVA क्रम DMA
 * @dev: instance of PCI owned by the driver that's asking.
 * @page: page to map
 * @poff: offset पूर्णांकo page
 * @size: number of bytes to map
 * @dir: dma direction
 * @attrs: optional dma attributes
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल dma_addr_t sba_map_page(काष्ठा device *dev, काष्ठा page *page,
			       अचिन्हित दीर्घ poff, माप_प्रकार size,
			       क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
	व्योम *addr = page_address(page) + poff;
	dma_addr_t iovp;
	dma_addr_t offset;
	u64 *pdir_start;
	पूर्णांक pide;
#अगर_घोषित ASSERT_Pसूची_SANITY
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
#अगर_घोषित ALLOW_IOV_BYPASS
	अचिन्हित दीर्घ pci_addr = virt_to_phys(addr);
#पूर्ण_अगर

#अगर_घोषित ALLOW_IOV_BYPASS
	ASSERT(to_pci_dev(dev)->dma_mask);
	/*
 	** Check अगर the PCI device can DMA to ptr... अगर so, just वापस ptr
 	*/
	अगर (likely((pci_addr & ~to_pci_dev(dev)->dma_mask) == 0)) अणु
		/*
 		** Device is bit capable of DMA'ing to the buffer...
		** just वापस the PCI address of ptr
 		*/
		DBG_BYPASS("sba_map_page() bypass mask/addr: "
			   "0x%lx/0x%lx\n",
		           to_pci_dev(dev)->dma_mask, pci_addr);
		वापस pci_addr;
	पूर्ण
#पूर्ण_अगर
	ioc = GET_IOC(dev);
	ASSERT(ioc);

	prefetch(ioc->res_hपूर्णांक);

	ASSERT(size > 0);
	ASSERT(size <= DMA_CHUNK_SIZE);

	/* save offset bits */
	offset = ((dma_addr_t) (दीर्घ) addr) & ~iovp_mask;

	/* round up to nearest iovp_size */
	size = (size + offset + ~iovp_mask) & iovp_mask;

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	अगर (sba_check_pdir(ioc,"Check before sba_map_page()"))
		panic("Sanity check failed");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

	pide = sba_alloc_range(ioc, dev, size);
	अगर (pide < 0)
		वापस DMA_MAPPING_ERROR;

	iovp = (dma_addr_t) pide << iovp_shअगरt;

	DBG_RUN("%s() 0x%p -> 0x%lx\n", __func__, addr, (दीर्घ) iovp | offset);

	pdir_start = &(ioc->pdir_base[pide]);

	जबतक (size > 0) अणु
		ASSERT(((u8 *)pdir_start)[7] == 0); /* verअगरy availability */
		sba_io_pdir_entry(pdir_start, (अचिन्हित दीर्घ) addr);

		DBG_RUN("     pdir 0x%p %lx\n", pdir_start, *pdir_start);

		addr += iovp_size;
		size -= iovp_size;
		pdir_start++;
	पूर्ण
	/* क्रमce pdir update */
	wmb();

	/* क्रमm complete address */
#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_check_pdir(ioc,"Check after sba_map_page()");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर
	वापस SBA_IOVA(ioc, iovp, offset);
पूर्ण

#अगर_घोषित ENABLE_MARK_CLEAN
अटल SBA_INLINE व्योम
sba_mark_clean(काष्ठा ioc *ioc, dma_addr_t iova, माप_प्रकार size)
अणु
	u32	iovp = (u32) SBA_IOVP(ioc,iova);
	पूर्णांक	off = Pसूची_INDEX(iovp);
	व्योम	*addr;

	अगर (size <= iovp_size) अणु
		addr = phys_to_virt(ioc->pdir_base[off] &
		                    ~0xE000000000000FFFULL);
		mark_clean(addr, size);
	पूर्ण अन्यथा अणु
		करो अणु
			addr = phys_to_virt(ioc->pdir_base[off] &
			                    ~0xE000000000000FFFULL);
			mark_clean(addr, min(size, iovp_size));
			off++;
			size -= iovp_size;
		पूर्ण जबतक (size > 0);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * sba_unmap_page - unmap one IOVA and मुक्त resources
 * @dev: instance of PCI owned by the driver that's asking.
 * @iova:  IOVA of driver buffer previously mapped.
 * @size:  number of bytes mapped in driver buffer.
 * @dir:  R/W or both.
 * @attrs: optional dma attributes
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम sba_unmap_page(काष्ठा device *dev, dma_addr_t iova, माप_प्रकार size,
			   क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
#अगर DELAYED_RESOURCE_CNT > 0
	काष्ठा sba_dma_pair *d;
#पूर्ण_अगर
	अचिन्हित दीर्घ flags;
	dma_addr_t offset;

	ioc = GET_IOC(dev);
	ASSERT(ioc);

#अगर_घोषित ALLOW_IOV_BYPASS
	अगर (likely((iova & ioc->imask) != ioc->ibase)) अणु
		/*
		** Address करोes not fall w/in IOVA, must be bypassing
		*/
		DBG_BYPASS("sba_unmap_page() bypass addr: 0x%lx\n",
			   iova);

#अगर_घोषित ENABLE_MARK_CLEAN
		अगर (dir == DMA_FROM_DEVICE) अणु
			mark_clean(phys_to_virt(iova), size);
		पूर्ण
#पूर्ण_अगर
		वापस;
	पूर्ण
#पूर्ण_अगर
	offset = iova & ~iovp_mask;

	DBG_RUN("%s() iovp 0x%lx/%x\n", __func__, (दीर्घ) iova, size);

	iova ^= offset;        /* clear offset bits */
	size += offset;
	size = ROUNDUP(size, iovp_size);

#अगर_घोषित ENABLE_MARK_CLEAN
	अगर (dir == DMA_FROM_DEVICE)
		sba_mark_clean(ioc, iova, size);
#पूर्ण_अगर

#अगर DELAYED_RESOURCE_CNT > 0
	spin_lock_irqsave(&ioc->saved_lock, flags);
	d = &(ioc->saved[ioc->saved_cnt]);
	d->iova = iova;
	d->size = size;
	अगर (unlikely(++(ioc->saved_cnt) >= DELAYED_RESOURCE_CNT)) अणु
		पूर्णांक cnt = ioc->saved_cnt;
		spin_lock(&ioc->res_lock);
		जबतक (cnt--) अणु
			sba_mark_invalid(ioc, d->iova, d->size);
			sba_मुक्त_range(ioc, d->iova, d->size);
			d--;
		पूर्ण
		ioc->saved_cnt = 0;
		READ_REG(ioc->ioc_hpa+IOC_PCOM);	/* flush purges */
		spin_unlock(&ioc->res_lock);
	पूर्ण
	spin_unlock_irqrestore(&ioc->saved_lock, flags);
#अन्यथा /* DELAYED_RESOURCE_CNT == 0 */
	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_mark_invalid(ioc, iova, size);
	sba_मुक्त_range(ioc, iova, size);
	READ_REG(ioc->ioc_hpa+IOC_PCOM);	/* flush purges */
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर /* DELAYED_RESOURCE_CNT == 0 */
पूर्ण

/**
 * sba_alloc_coherent - allocate/map shared mem क्रम DMA
 * @dev: instance of PCI owned by the driver that's asking.
 * @size:  number of bytes mapped in driver buffer.
 * @dma_handle:  IOVA of new buffer.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम *
sba_alloc_coherent(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		   gfp_t flags, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page;
	काष्ठा ioc *ioc;
	पूर्णांक node = -1;
	व्योम *addr;

	ioc = GET_IOC(dev);
	ASSERT(ioc);
#अगर_घोषित CONFIG_NUMA
	node = ioc->node;
#पूर्ण_अगर

	page = alloc_pages_node(node, flags, get_order(size));
	अगर (unlikely(!page))
		वापस शून्य;

	addr = page_address(page);
	स_रखो(addr, 0, size);
	*dma_handle = page_to_phys(page);

#अगर_घोषित ALLOW_IOV_BYPASS
	ASSERT(dev->coherent_dma_mask);
	/*
 	** Check अगर the PCI device can DMA to ptr... अगर so, just वापस ptr
 	*/
	अगर (likely((*dma_handle & ~dev->coherent_dma_mask) == 0)) अणु
		DBG_BYPASS("sba_alloc_coherent() bypass mask/addr: 0x%lx/0x%lx\n",
		           dev->coherent_dma_mask, *dma_handle);

		वापस addr;
	पूर्ण
#पूर्ण_अगर

	/*
	 * If device can't bypass or bypass is disabled, pass the 32bit fake
	 * device to map single to get an iova mapping.
	 */
	*dma_handle = sba_map_page(&ioc->sac_only_dev->dev, page, 0, size,
			DMA_BIसूचीECTIONAL, 0);
	अगर (dma_mapping_error(dev, *dma_handle))
		वापस शून्य;
	वापस addr;
पूर्ण


/**
 * sba_मुक्त_coherent - मुक्त/unmap shared mem क्रम DMA
 * @dev: instance of PCI owned by the driver that's asking.
 * @size:  number of bytes mapped in driver buffer.
 * @vaddr:  भव address IOVA of "consistent" buffer.
 * @dma_handler:  IO भव address of "consistent" buffer.
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम sba_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
			      dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	sba_unmap_page(dev, dma_handle, size, 0, 0);
	मुक्त_pages((अचिन्हित दीर्घ) vaddr, get_order(size));
पूर्ण


/*
** Since 0 is a valid pdir_base index value, can't use that
** to determine अगर a value is valid or not. Use a flag to indicate
** the SG list entry contains a valid pdir index.
*/
#घोषणा PIDE_FLAG 0x1UL

#अगर_घोषित DEBUG_LARGE_SG_ENTRIES
पूर्णांक dump_run_sg = 0;
#पूर्ण_अगर


/**
 * sba_fill_pdir - ग_लिखो allocated SG entries पूर्णांकo IO Pसूची
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @startsg:  list of IOVA/size pairs
 * @nents: number of entries in startsg list
 *
 * Take preprocessed SG list and ग_लिखो corresponding entries
 * in the IO Pसूची.
 */

अटल SBA_INLINE पूर्णांक
sba_fill_pdir(
	काष्ठा ioc *ioc,
	काष्ठा scatterlist *startsg,
	पूर्णांक nents)
अणु
	काष्ठा scatterlist *dma_sg = startsg;	/* poपूर्णांकer to current DMA */
	पूर्णांक n_mappings = 0;
	u64 *pdirp = शून्य;
	अचिन्हित दीर्घ dma_offset = 0;

	जबतक (nents-- > 0) अणु
		पूर्णांक     cnt = startsg->dma_length;
		startsg->dma_length = 0;

#अगर_घोषित DEBUG_LARGE_SG_ENTRIES
		अगर (dump_run_sg)
			prपूर्णांकk(" %2d : %08lx/%05x %p\n",
				nents, startsg->dma_address, cnt,
				sba_sg_address(startsg));
#अन्यथा
		DBG_RUN_SG(" %d : %08lx/%05x %p\n",
				nents, startsg->dma_address, cnt,
				sba_sg_address(startsg));
#पूर्ण_अगर
		/*
		** Look क्रम the start of a new DMA stream
		*/
		अगर (startsg->dma_address & PIDE_FLAG) अणु
			u32 pide = startsg->dma_address & ~PIDE_FLAG;
			dma_offset = (अचिन्हित दीर्घ) pide & ~iovp_mask;
			startsg->dma_address = 0;
			अगर (n_mappings)
				dma_sg = sg_next(dma_sg);
			dma_sg->dma_address = pide | ioc->ibase;
			pdirp = &(ioc->pdir_base[pide >> iovp_shअगरt]);
			n_mappings++;
		पूर्ण

		/*
		** Look क्रम a VCONTIG chunk
		*/
		अगर (cnt) अणु
			अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ) sba_sg_address(startsg);
			ASSERT(pdirp);

			/* Since multiple Vcontig blocks could make up
			** one DMA stream, *add* cnt to dma_len.
			*/
			dma_sg->dma_length += cnt;
			cnt += dma_offset;
			dma_offset=0;	/* only want offset on first chunk */
			cnt = ROUNDUP(cnt, iovp_size);
			करो अणु
				sba_io_pdir_entry(pdirp, vaddr);
				vaddr += iovp_size;
				cnt -= iovp_size;
				pdirp++;
			पूर्ण जबतक (cnt > 0);
		पूर्ण
		startsg = sg_next(startsg);
	पूर्ण
	/* क्रमce pdir update */
	wmb();

#अगर_घोषित DEBUG_LARGE_SG_ENTRIES
	dump_run_sg = 0;
#पूर्ण_अगर
	वापस(n_mappings);
पूर्ण


/*
** Two address ranges are DMA contiguous *अगरf* "end of prev" and
** "start of next" are both on an IOV page boundary.
**
** (shअगरt left is a quick trick to mask off upper bits)
*/
#घोषणा DMA_CONTIG(__X, __Y) \
	(((((अचिन्हित दीर्घ) __X) | ((अचिन्हित दीर्घ) __Y)) << (BITS_PER_LONG - iovp_shअगरt)) == 0UL)


/**
 * sba_coalesce_chunks - preprocess the SG list
 * @ioc: IO MMU काष्ठाure which owns the pdir we are पूर्णांकerested in.
 * @startsg:  list of IOVA/size pairs
 * @nents: number of entries in startsg list
 *
 * First pass is to walk the SG list and determine where the अवरोधs are
 * in the DMA stream. Allocates Pसूची entries but करोes not fill them.
 * Returns the number of DMA chunks.
 *
 * Doing the fill separate from the coalescing/allocation keeps the
 * code simpler. Future enhancement could make one pass through
 * the sglist करो both.
 */
अटल SBA_INLINE पूर्णांक
sba_coalesce_chunks(काष्ठा ioc *ioc, काष्ठा device *dev,
	काष्ठा scatterlist *startsg,
	पूर्णांक nents)
अणु
	काष्ठा scatterlist *vcontig_sg;    /* VCONTIG chunk head */
	अचिन्हित दीर्घ vcontig_len;         /* len of VCONTIG chunk */
	अचिन्हित दीर्घ vcontig_end;
	काष्ठा scatterlist *dma_sg;        /* next DMA stream head */
	अचिन्हित दीर्घ dma_offset, dma_len; /* start/len of DMA stream */
	पूर्णांक n_mappings = 0;
	अचिन्हित पूर्णांक max_seg_size = dma_get_max_seg_size(dev);
	पूर्णांक idx;

	जबतक (nents > 0) अणु
		अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ) sba_sg_address(startsg);

		/*
		** Prepare क्रम first/next DMA stream
		*/
		dma_sg = vcontig_sg = startsg;
		dma_len = vcontig_len = vcontig_end = startsg->length;
		vcontig_end +=  vaddr;
		dma_offset = vaddr & ~iovp_mask;

		/* PARANOID: clear entries */
		startsg->dma_address = startsg->dma_length = 0;

		/*
		** This loop terminates one iteration "early" since
		** it's always looking one "ahead".
		*/
		जबतक (--nents > 0) अणु
			अचिन्हित दीर्घ vaddr;	/* पंचांगp */

			startsg = sg_next(startsg);

			/* PARANOID */
			startsg->dma_address = startsg->dma_length = 0;

			/* catch brokenness in SCSI layer */
			ASSERT(startsg->length <= DMA_CHUNK_SIZE);

			/*
			** First make sure current dma stream won't
			** exceed DMA_CHUNK_SIZE अगर we coalesce the
			** next entry.
			*/
			अगर (((dma_len + dma_offset + startsg->length + ~iovp_mask) & iovp_mask)
			    > DMA_CHUNK_SIZE)
				अवरोध;

			अगर (dma_len + startsg->length > max_seg_size)
				अवरोध;

			/*
			** Then look क्रम भवly contiguous blocks.
			**
			** append the next transaction?
			*/
			vaddr = (अचिन्हित दीर्घ) sba_sg_address(startsg);
			अगर  (vcontig_end == vaddr)
			अणु
				vcontig_len += startsg->length;
				vcontig_end += startsg->length;
				dma_len     += startsg->length;
				जारी;
			पूर्ण

#अगर_घोषित DEBUG_LARGE_SG_ENTRIES
			dump_run_sg = (vcontig_len > iovp_size);
#पूर्ण_अगर

			/*
			** Not भवly contiguous.
			** Terminate prev chunk.
			** Start a new chunk.
			**
			** Once we start a new VCONTIG chunk, dma_offset
			** can't change. And we need the offset from the first
			** chunk - not the last one. Ergo Successive chunks
			** must start on page boundaries and करोve tail
			** with it's predecessor.
			*/
			vcontig_sg->dma_length = vcontig_len;

			vcontig_sg = startsg;
			vcontig_len = startsg->length;

			/*
			** 3) करो the entries end/start on page boundaries?
			**    Don't update vcontig_end until we've checked.
			*/
			अगर (DMA_CONTIG(vcontig_end, vaddr))
			अणु
				vcontig_end = vcontig_len + vaddr;
				dma_len += vcontig_len;
				जारी;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		** End of DMA Stream
		** Terminate last VCONTIG block.
		** Allocate space क्रम DMA stream.
		*/
		vcontig_sg->dma_length = vcontig_len;
		dma_len = (dma_len + dma_offset + ~iovp_mask) & iovp_mask;
		ASSERT(dma_len <= DMA_CHUNK_SIZE);
		idx = sba_alloc_range(ioc, dev, dma_len);
		अगर (idx < 0) अणु
			dma_sg->dma_length = 0;
			वापस -1;
		पूर्ण
		dma_sg->dma_address = (dma_addr_t)(PIDE_FLAG | (idx << iovp_shअगरt)
						   | dma_offset);
		n_mappings++;
	पूर्ण

	वापस n_mappings;
पूर्ण

अटल व्योम sba_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			       पूर्णांक nents, क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs);
/**
 * sba_map_sg - map Scatter/Gather list
 * @dev: instance of PCI owned by the driver that's asking.
 * @sglist:  array of buffer/length pairs
 * @nents:  number of entries in list
 * @dir:  R/W or both.
 * @attrs: optional dma attributes
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल पूर्णांक sba_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			    पूर्णांक nents, क्रमागत dma_data_direction dir,
			    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
	पूर्णांक coalesced, filled = 0;
#अगर_घोषित ASSERT_Pसूची_SANITY
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर
#अगर_घोषित ALLOW_IOV_BYPASS_SG
	काष्ठा scatterlist *sg;
#पूर्ण_अगर

	DBG_RUN_SG("%s() START %d entries\n", __func__, nents);
	ioc = GET_IOC(dev);
	ASSERT(ioc);

#अगर_घोषित ALLOW_IOV_BYPASS_SG
	ASSERT(to_pci_dev(dev)->dma_mask);
	अगर (likely((ioc->dma_mask & ~to_pci_dev(dev)->dma_mask) == 0)) अणु
		क्रम_each_sg(sglist, sg, nents, filled) अणु
			sg->dma_length = sg->length;
			sg->dma_address = virt_to_phys(sba_sg_address(sg));
		पूर्ण
		वापस filled;
	पूर्ण
#पूर्ण_अगर
	/* Fast path single entry scatterlists. */
	अगर (nents == 1) अणु
		sglist->dma_length = sglist->length;
		sglist->dma_address = sba_map_page(dev, sg_page(sglist),
				sglist->offset, sglist->length, dir, attrs);
		अगर (dma_mapping_error(dev, sglist->dma_address))
			वापस 0;
		वापस 1;
	पूर्ण

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	अगर (sba_check_pdir(ioc,"Check before sba_map_sg_attrs()"))
	अणु
		sba_dump_sg(ioc, sglist, nents);
		panic("Check before sba_map_sg_attrs()");
	पूर्ण
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

	prefetch(ioc->res_hपूर्णांक);

	/*
	** First coalesce the chunks and allocate I/O pdir space
	**
	** If this is one DMA stream, we can properly map using the
	** correct भव address associated with each DMA page.
	** w/o this association, we wouldn't have coherent DMA!
	** Access to the भव address is what क्रमces a two pass algorithm.
	*/
	coalesced = sba_coalesce_chunks(ioc, dev, sglist, nents);
	अगर (coalesced < 0) अणु
		sba_unmap_sg_attrs(dev, sglist, nents, dir, attrs);
		वापस 0;
	पूर्ण

	/*
	** Program the I/O Pdir
	**
	** map the भव addresses to the I/O Pdir
	** o dma_address will contain the pdir index
	** o dma_len will contain the number of bytes to map
	** o address contains the भव address.
	*/
	filled = sba_fill_pdir(ioc, sglist, nents);

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	अगर (sba_check_pdir(ioc,"Check after sba_map_sg_attrs()"))
	अणु
		sba_dump_sg(ioc, sglist, nents);
		panic("Check after sba_map_sg_attrs()\n");
	पूर्ण
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

	ASSERT(coalesced == filled);
	DBG_RUN_SG("%s() DONE %d mappings\n", __func__, filled);

	वापस filled;
पूर्ण

/**
 * sba_unmap_sg_attrs - unmap Scatter/Gather list
 * @dev: instance of PCI owned by the driver that's asking.
 * @sglist:  array of buffer/length pairs
 * @nents:  number of entries in list
 * @dir:  R/W or both.
 * @attrs: optional dma attributes
 *
 * See Documentation/core-api/dma-api-howto.rst
 */
अटल व्योम sba_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			       पूर्णांक nents, क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs)
अणु
#अगर_घोषित ASSERT_Pसूची_SANITY
	काष्ठा ioc *ioc;
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर

	DBG_RUN_SG("%s() START %d entries,  %p,%x\n",
		   __func__, nents, sba_sg_address(sglist), sglist->length);

#अगर_घोषित ASSERT_Pसूची_SANITY
	ioc = GET_IOC(dev);
	ASSERT(ioc);

	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_check_pdir(ioc,"Check before sba_unmap_sg_attrs()");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

	जबतक (nents && sglist->dma_length) अणु

		sba_unmap_page(dev, sglist->dma_address, sglist->dma_length,
			       dir, attrs);
		sglist = sg_next(sglist);
		nents--;
	पूर्ण

	DBG_RUN_SG("%s() DONE (nents %d)\n", __func__,  nents);

#अगर_घोषित ASSERT_Pसूची_SANITY
	spin_lock_irqsave(&ioc->res_lock, flags);
	sba_check_pdir(ioc,"Check after sba_unmap_sg_attrs()");
	spin_unlock_irqrestore(&ioc->res_lock, flags);
#पूर्ण_अगर

पूर्ण

/**************************************************************
*
*   Initialization and claim
*
***************************************************************/

अटल व्योम
ioc_iova_init(काष्ठा ioc *ioc)
अणु
	पूर्णांक tcnfg;
	पूर्णांक agp_found = 0;
	काष्ठा pci_dev *device = शून्य;
#अगर_घोषित FULL_VALID_Pसूची
	अचिन्हित दीर्घ index;
#पूर्ण_अगर

	/*
	** Firmware programs the base and size of a "safe IOVA space"
	** (one that करोesn't overlap memory or LMMIO space) in the
	** IBASE and IMASK रेजिस्टरs.
	*/
	ioc->ibase = READ_REG(ioc->ioc_hpa + IOC_IBASE) & ~0x1UL;
	ioc->imask = READ_REG(ioc->ioc_hpa + IOC_IMASK) | 0xFFFFFFFF00000000UL;

	ioc->iov_size = ~ioc->imask + 1;

	DBG_INIT("%s() hpa %p IOV base 0x%lx mask 0x%lx (%dMB)\n",
		__func__, ioc->ioc_hpa, ioc->ibase, ioc->imask,
		ioc->iov_size >> 20);

	चयन (iovp_size) अणु
		हाल  4*1024: tcnfg = 0; अवरोध;
		हाल  8*1024: tcnfg = 1; अवरोध;
		हाल 16*1024: tcnfg = 2; अवरोध;
		हाल 64*1024: tcnfg = 3; अवरोध;
		शेष:
			panic(PFX "Unsupported IOTLB page size %ldK",
				iovp_size >> 10);
			अवरोध;
	पूर्ण
	WRITE_REG(tcnfg, ioc->ioc_hpa + IOC_TCNFG);

	ioc->pdir_size = (ioc->iov_size / iovp_size) * Pसूची_ENTRY_SIZE;
	ioc->pdir_base = (व्योम *) __get_मुक्त_pages(GFP_KERNEL,
						   get_order(ioc->pdir_size));
	अगर (!ioc->pdir_base)
		panic(PFX "Couldn't allocate I/O Page Table\n");

	स_रखो(ioc->pdir_base, 0, ioc->pdir_size);

	DBG_INIT("%s() IOV page size %ldK pdir %p size %x\n", __func__,
		iovp_size >> 10, ioc->pdir_base, ioc->pdir_size);

	ASSERT(ALIGN((अचिन्हित दीर्घ) ioc->pdir_base, 4*1024) == (अचिन्हित दीर्घ) ioc->pdir_base);
	WRITE_REG(virt_to_phys(ioc->pdir_base), ioc->ioc_hpa + IOC_Pसूची_BASE);

	/*
	** If an AGP device is present, only use half of the IOV space
	** क्रम PCI DMA.  Unक्रमtunately we can't know ahead of समय
	** whether GART support will actually be used, क्रम now we
	** can just key on an AGP device found in the प्रणाली.
	** We program the next pdir index after we stop w/ a key क्रम
	** the GART code to handshake on.
	*/
	क्रम_each_pci_dev(device)	
		agp_found |= pci_find_capability(device, PCI_CAP_ID_AGP);

	अगर (agp_found && reserve_sba_gart) अणु
		prपूर्णांकk(KERN_INFO PFX "reserving %dMb of IOVA space at 0x%lx for agpgart\n",
		      ioc->iov_size/2 >> 20, ioc->ibase + ioc->iov_size/2);
		ioc->pdir_size /= 2;
		((u64 *)ioc->pdir_base)[Pसूची_INDEX(ioc->iov_size/2)] = ZX1_SBA_IOMMU_COOKIE;
	पूर्ण
#अगर_घोषित FULL_VALID_Pसूची
	/*
  	** Check to see अगर the spill page has been allocated, we करोn't need more than
	** one across multiple SBAs.
	*/
	अगर (!prefetch_spill_page) अणु
		अक्षर *spill_poison = "SBAIOMMU POISON";
		पूर्णांक poison_size = 16;
		व्योम *poison_addr, *addr;

		addr = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, get_order(iovp_size));
		अगर (!addr)
			panic(PFX "Couldn't allocate PDIR spill page\n");

		poison_addr = addr;
		क्रम ( ; (u64) poison_addr < addr + iovp_size; poison_addr += poison_size)
			स_नकल(poison_addr, spill_poison, poison_size);

		prefetch_spill_page = virt_to_phys(addr);

		DBG_INIT("%s() prefetch spill addr: 0x%lx\n", __func__, prefetch_spill_page);
	पूर्ण
	/*
  	** Set all the Pसूची entries valid w/ the spill page as the target
	*/
	क्रम (index = 0 ; index < (ioc->pdir_size / Pसूची_ENTRY_SIZE) ; index++)
		((u64 *)ioc->pdir_base)[index] = (0x80000000000000FF | prefetch_spill_page);
#पूर्ण_अगर

	/* Clear I/O TLB of any possible entries */
	WRITE_REG(ioc->ibase | (get_iovp_order(ioc->iov_size) + iovp_shअगरt), ioc->ioc_hpa + IOC_PCOM);
	READ_REG(ioc->ioc_hpa + IOC_PCOM);

	/* Enable IOVA translation */
	WRITE_REG(ioc->ibase | 1, ioc->ioc_hpa + IOC_IBASE);
	READ_REG(ioc->ioc_hpa + IOC_IBASE);
पूर्ण

अटल व्योम __init
ioc_resource_init(काष्ठा ioc *ioc)
अणु
	spin_lock_init(&ioc->res_lock);
#अगर DELAYED_RESOURCE_CNT > 0
	spin_lock_init(&ioc->saved_lock);
#पूर्ण_अगर

	/* resource map size dictated by pdir_size */
	ioc->res_size = ioc->pdir_size / Pसूची_ENTRY_SIZE; /* entries */
	ioc->res_size >>= 3;  /* convert bit count to byte count */
	DBG_INIT("%s() res_size 0x%x\n", __func__, ioc->res_size);

	ioc->res_map = (अक्षर *) __get_मुक्त_pages(GFP_KERNEL,
						 get_order(ioc->res_size));
	अगर (!ioc->res_map)
		panic(PFX "Couldn't allocate resource map\n");

	स_रखो(ioc->res_map, 0, ioc->res_size);
	/* next available IOVP - circular search */
	ioc->res_hपूर्णांक = (अचिन्हित दीर्घ *) ioc->res_map;

#अगर_घोषित ASSERT_Pसूची_SANITY
	/* Mark first bit busy - ie no IOVA 0 */
	ioc->res_map[0] = 0x1;
	ioc->pdir_base[0] = 0x8000000000000000ULL | ZX1_SBA_IOMMU_COOKIE;
#पूर्ण_अगर
#अगर_घोषित FULL_VALID_Pसूची
	/* Mark the last resource used so we करोn't prefetch beyond IOVA space */
	ioc->res_map[ioc->res_size - 1] |= 0x80UL; /* res_map is अक्षरs */
	ioc->pdir_base[(ioc->pdir_size / Pसूची_ENTRY_SIZE) - 1] = (0x80000000000000FF
							      | prefetch_spill_page);
#पूर्ण_अगर

	DBG_INIT("%s() res_map %x %p\n", __func__,
		 ioc->res_size, (व्योम *) ioc->res_map);
पूर्ण

अटल व्योम __init
ioc_sac_init(काष्ठा ioc *ioc)
अणु
	काष्ठा pci_dev *sac = शून्य;
	काष्ठा pci_controller *controller = शून्य;

	/*
	 * pci_alloc_coherent() must वापस a DMA address which is
	 * SAC (single address cycle) addressable, so allocate a
	 * pseuकरो-device to enक्रमce that.
	 */
	sac = kzalloc(माप(*sac), GFP_KERNEL);
	अगर (!sac)
		panic(PFX "Couldn't allocate struct pci_dev");

	controller = kzalloc(माप(*controller), GFP_KERNEL);
	अगर (!controller)
		panic(PFX "Couldn't allocate struct pci_controller");

	controller->iommu = ioc;
	sac->sysdata = controller;
	sac->dma_mask = 0xFFFFFFFFUL;
	sac->dev.bus = &pci_bus_type;
	ioc->sac_only_dev = sac;
पूर्ण

अटल व्योम __init
ioc_zx1_init(काष्ठा ioc *ioc)
अणु
	अचिन्हित दीर्घ rope_config;
	अचिन्हित पूर्णांक i;

	अगर (ioc->rev < 0x20)
		panic(PFX "IOC 2.0 or later required for IOMMU support\n");

	/* 38 bit memory controller + extra bit क्रम range displaced by MMIO */
	ioc->dma_mask = (0x1UL << 39) - 1;

	/*
	** Clear ROPE(N)_CONFIG AO bit.
	** Disables "NT Ordering" (~= !"Relaxed Ordering")
	** Overrides bit 1 in DMA Hपूर्णांक Sets.
	** Improves netperf UDP_STREAM by ~10% क्रम tg3 on bcm5701.
	*/
	क्रम (i=0; i<(8*8); i+=8) अणु
		rope_config = READ_REG(ioc->ioc_hpa + IOC_ROPE0_CFG + i);
		rope_config &= ~IOC_ROPE_AO;
		WRITE_REG(rope_config, ioc->ioc_hpa + IOC_ROPE0_CFG + i);
	पूर्ण
पूर्ण

प्रकार व्योम (initfunc)(काष्ठा ioc *);

काष्ठा ioc_iommu अणु
	u32 func_id;
	अक्षर *name;
	initfunc *init;
पूर्ण;

अटल काष्ठा ioc_iommu ioc_iommu_info[] __initdata = अणु
	अणु ZX1_IOC_ID, "zx1", ioc_zx1_init पूर्ण,
	अणु ZX2_IOC_ID, "zx2", शून्य पूर्ण,
	अणु SX1000_IOC_ID, "sx1000", शून्य पूर्ण,
	अणु SX2000_IOC_ID, "sx2000", शून्य पूर्ण,
पूर्ण;

अटल व्योम __init ioc_init(अचिन्हित दीर्घ hpa, काष्ठा ioc *ioc)
अणु
	काष्ठा ioc_iommu *info;

	ioc->next = ioc_list;
	ioc_list = ioc;

	ioc->ioc_hpa = ioremap(hpa, 0x1000);

	ioc->func_id = READ_REG(ioc->ioc_hpa + IOC_FUNC_ID);
	ioc->rev = READ_REG(ioc->ioc_hpa + IOC_FCLASS) & 0xFFUL;
	ioc->dma_mask = 0xFFFFFFFFFFFFFFFFUL;	/* conservative */

	क्रम (info = ioc_iommu_info; info < ioc_iommu_info + ARRAY_SIZE(ioc_iommu_info); info++) अणु
		अगर (ioc->func_id == info->func_id) अणु
			ioc->name = info->name;
			अगर (info->init)
				(info->init)(ioc);
		पूर्ण
	पूर्ण

	iovp_size = (1 << iovp_shअगरt);
	iovp_mask = ~(iovp_size - 1);

	DBG_INIT("%s: PAGE_SIZE %ldK, iovp_size %ldK\n", __func__,
		PAGE_SIZE >> 10, iovp_size >> 10);

	अगर (!ioc->name) अणु
		ioc->name = kदो_स्मृति(24, GFP_KERNEL);
		अगर (ioc->name)
			प्र_लिखो((अक्षर *) ioc->name, "Unknown (%04x:%04x)",
				ioc->func_id & 0xFFFF, (ioc->func_id >> 16) & 0xFFFF);
		अन्यथा
			ioc->name = "Unknown";
	पूर्ण

	ioc_iova_init(ioc);
	ioc_resource_init(ioc);
	ioc_sac_init(ioc);

	prपूर्णांकk(KERN_INFO PFX
		"%s %d.%d HPA 0x%lx IOVA space %dMb at 0x%lx\n",
		ioc->name, (ioc->rev >> 4) & 0xF, ioc->rev & 0xF,
		hpa, ioc->iov_size >> 20, ioc->ibase);
पूर्ण



/**************************************************************************
**
**   SBA initialization code (HW and SW)
**
**   o identअगरy SBA chip itself
**   o FIXME: initialize DMA hपूर्णांकs क्रम reasonable शेषs
**
**************************************************************************/

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *
ioc_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा ioc *ioc;
	loff_t n = *pos;

	क्रम (ioc = ioc_list; ioc; ioc = ioc->next)
		अगर (!n--)
			वापस ioc;

	वापस शून्य;
पूर्ण

अटल व्योम *
ioc_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा ioc *ioc = v;

	++*pos;
	वापस ioc->next;
पूर्ण

अटल व्योम
ioc_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक
ioc_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा ioc *ioc = v;
	अचिन्हित दीर्घ *res_ptr = (अचिन्हित दीर्घ *)ioc->res_map;
	पूर्णांक i, used = 0;

	seq_म_लिखो(s, "Hewlett Packard %s IOC rev %d.%d\n",
		ioc->name, ((ioc->rev >> 4) & 0xF), (ioc->rev & 0xF));
#अगर_घोषित CONFIG_NUMA
	अगर (ioc->node != NUMA_NO_NODE)
		seq_म_लिखो(s, "NUMA node       : %d\n", ioc->node);
#पूर्ण_अगर
	seq_म_लिखो(s, "IOVA size       : %ld MB\n", ((ioc->pdir_size >> 3) * iovp_size)/(1024*1024));
	seq_म_लिखो(s, "IOVA page size  : %ld kb\n", iovp_size/1024);

	क्रम (i = 0; i < (ioc->res_size / माप(अचिन्हित दीर्घ)); ++i, ++res_ptr)
		used += hweight64(*res_ptr);

	seq_म_लिखो(s, "PDIR size       : %d entries\n", ioc->pdir_size >> 3);
	seq_म_लिखो(s, "PDIR used       : %d entries\n", used);

#अगर_घोषित Pसूची_SEARCH_TIMING
	अणु
		अचिन्हित दीर्घ i = 0, avg = 0, min, max;
		min = max = ioc->avg_search[0];
		क्रम (i = 0; i < SBA_SEARCH_SAMPLE; i++) अणु
			avg += ioc->avg_search[i];
			अगर (ioc->avg_search[i] > max) max = ioc->avg_search[i];
			अगर (ioc->avg_search[i] < min) min = ioc->avg_search[i];
		पूर्ण
		avg /= SBA_SEARCH_SAMPLE;
		seq_म_लिखो(s, "Bitmap search   : %ld/%ld/%ld (min/avg/max CPU Cycles/IOVA page)\n",
		           min, avg, max);
	पूर्ण
#पूर्ण_अगर
#अगर_अघोषित ALLOW_IOV_BYPASS
	 seq_म_लिखो(s, "IOVA bypass disabled\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ioc_seq_ops = अणु
	.start = ioc_start,
	.next  = ioc_next,
	.stop  = ioc_stop,
	.show  = ioc_show
पूर्ण;

अटल व्योम __init
ioc_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *dir;

	dir = proc_सूची_गढ़ो("bus/mckinley", शून्य);
	अगर (!dir)
		वापस;

	proc_create_seq(ioc_list->name, 0, dir, &ioc_seq_ops);
पूर्ण
#पूर्ण_अगर

अटल व्योम
sba_connect_bus(काष्ठा pci_bus *bus)
अणु
	acpi_handle handle, parent;
	acpi_status status;
	काष्ठा ioc *ioc;

	अगर (!PCI_CONTROLLER(bus))
		panic(PFX "no sysdata on bus %d!\n", bus->number);

	अगर (PCI_CONTROLLER(bus)->iommu)
		वापस;

	handle = acpi_device_handle(PCI_CONTROLLER(bus)->companion);
	अगर (!handle)
		वापस;

	/*
	 * The IOC scope enबंदs PCI root bridges in the ACPI
	 * namespace, so work our way out until we find an IOC we
	 * claimed previously.
	 */
	करो अणु
		क्रम (ioc = ioc_list; ioc; ioc = ioc->next)
			अगर (ioc->handle == handle) अणु
				PCI_CONTROLLER(bus)->iommu = ioc;
				वापस;
			पूर्ण

		status = acpi_get_parent(handle, &parent);
		handle = parent;
	पूर्ण जबतक (ACPI_SUCCESS(status));

	prपूर्णांकk(KERN_WARNING "No IOC for PCI Bus %04x:%02x in ACPI\n", pci_करोमुख्य_nr(bus), bus->number);
पूर्ण

अटल व्योम __init
sba_map_ioc_to_node(काष्ठा ioc *ioc, acpi_handle handle)
अणु
#अगर_घोषित CONFIG_NUMA
	अचिन्हित पूर्णांक node;

	node = acpi_get_node(handle);
	अगर (node != NUMA_NO_NODE && !node_online(node))
		node = NUMA_NO_NODE;

	ioc->node = node;
#पूर्ण_अगर
पूर्ण

अटल व्योम __init acpi_sba_ioc_add(काष्ठा ioc *ioc)
अणु
	acpi_handle handle = ioc->handle;
	acpi_status status;
	u64 hpa, length;
	काष्ठा acpi_device_info *adi;

	ioc_found = ioc->next;
	status = hp_acpi_csr_space(handle, &hpa, &length);
	अगर (ACPI_FAILURE(status))
		जाओ err;

	status = acpi_get_object_info(handle, &adi);
	अगर (ACPI_FAILURE(status))
		जाओ err;

	/*
	 * For HWP0001, only SBA appears in ACPI namespace.  It enबंदs the PCI
	 * root bridges, and its CSR space includes the IOC function.
	 */
	अगर (म_भेदन("HWP0001", adi->hardware_id.string, 7) == 0) अणु
		hpa += ZX1_IOC_OFFSET;
		/* zx1 based प्रणालीs शेष to kernel page size iommu pages */
		अगर (!iovp_shअगरt)
			iovp_shअगरt = min(PAGE_SHIFT, 16);
	पूर्ण
	kमुक्त(adi);

	/*
	 * शेष anything not caught above or specअगरied on cmdline to 4k
	 * iommu page size
	 */
	अगर (!iovp_shअगरt)
		iovp_shअगरt = 12;

	ioc_init(hpa, ioc);
	/* setup NUMA node association */
	sba_map_ioc_to_node(ioc, handle);
	वापस;

 err:
	kमुक्त(ioc);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hp_ioc_iommu_device_ids[] = अणु
	अणु"HWP0001", 0पूर्ण,
	अणु"HWP0004", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल पूर्णांक acpi_sba_ioc_attach(काष्ठा acpi_device *device,
			       स्थिर काष्ठा acpi_device_id *not_used)
अणु
	काष्ठा ioc *ioc;

	ioc = kzalloc(माप(*ioc), GFP_KERNEL);
	अगर (!ioc)
		वापस -ENOMEM;

	ioc->next = ioc_found;
	ioc_found = ioc;
	ioc->handle = device->handle;
	वापस 1;
पूर्ण


अटल काष्ठा acpi_scan_handler acpi_sba_ioc_handler = अणु
	.ids	= hp_ioc_iommu_device_ids,
	.attach	= acpi_sba_ioc_attach,
पूर्ण;

अटल पूर्णांक __init acpi_sba_ioc_init_acpi(व्योम)
अणु
	वापस acpi_scan_add_handler(&acpi_sba_ioc_handler);
पूर्ण
/* This has to run beक्रमe acpi_scan_init(). */
arch_initcall(acpi_sba_ioc_init_acpi);

अटल पूर्णांक sba_dma_supported (काष्ठा device *dev, u64 mask)
अणु
	/* make sure it's at least 32bit capable */
	वापस ((mask & 0xFFFFFFFFUL) == 0xFFFFFFFFUL);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops sba_dma_ops = अणु
	.alloc			= sba_alloc_coherent,
	.मुक्त			= sba_मुक्त_coherent,
	.map_page		= sba_map_page,
	.unmap_page		= sba_unmap_page,
	.map_sg			= sba_map_sg_attrs,
	.unmap_sg		= sba_unmap_sg_attrs,
	.dma_supported		= sba_dma_supported,
	.mmap			= dma_common_mmap,
	.get_sgtable		= dma_common_get_sgtable,
	.alloc_pages		= dma_common_alloc_pages,
	.मुक्त_pages		= dma_common_मुक्त_pages,
पूर्ण;

अटल पूर्णांक __init
sba_init(व्योम)
अणु
	/*
	 * If we are booting a kdump kernel, the sba_iommu will cause devices
	 * that were not shutकरोwn properly to MCA as soon as they are turned
	 * back on.  Our only option क्रम a successful kdump kernel boot is to
	 * use swiotlb.
	 */
	अगर (is_kdump_kernel())
		वापस 0;

	/*
	 * ioc_found should be populated by the acpi_sba_ioc_handler's .attach()
	 * routine, but that only happens अगर acpi_scan_init() has alपढ़ोy run.
	 */
	जबतक (ioc_found)
		acpi_sba_ioc_add(ioc_found);

	अगर (!ioc_list)
		वापस 0;

	अणु
		काष्ठा pci_bus *b = शून्य;
		जबतक ((b = pci_find_next_bus(b)) != शून्य)
			sba_connect_bus(b);
	पूर्ण

	/* no need क्रम swiotlb with the iommu */
	swiotlb_निकास();
	dma_ops = &sba_dma_ops;

#अगर_घोषित CONFIG_PROC_FS
	ioc_proc_init();
#पूर्ण_अगर
	वापस 0;
पूर्ण

subsys_initcall(sba_init); /* must be initialized after ACPI etc., but beक्रमe any drivers... */

अटल पूर्णांक __init
nosbagart(अक्षर *str)
अणु
	reserve_sba_gart = 0;
	वापस 1;
पूर्ण

__setup("nosbagart", nosbagart);

अटल पूर्णांक __init
sba_page_override(अक्षर *str)
अणु
	अचिन्हित दीर्घ page_size;

	page_size = memparse(str, &str);
	चयन (page_size) अणु
		हाल 4096:
		हाल 8192:
		हाल 16384:
		हाल 65536:
			iovp_shअगरt = ffs(page_size) - 1;
			अवरोध;
		शेष:
			prपूर्णांकk("%s: unknown/unsupported iommu page size %ld\n",
			       __func__, page_size);
	पूर्ण

	वापस 1;
पूर्ण

__setup("sbapagesize=",sba_page_override);
