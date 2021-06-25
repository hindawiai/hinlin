<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
** ccio-dma.c:
**	DMA management routines क्रम first generation cache-coherent machines.
**	Program U2/Uturn in "Virtual Mode" and use the I/O MMU.
**
**	(c) Copyright 2000 Grant Grundler
**	(c) Copyright 2000 Ryan Bradetich
**	(c) Copyright 2000 Hewlett-Packard Company
**
**
**
**  "Real Mode" operation refers to U2/Uturn chip operation.
**  U2/Uturn were deचिन्हित to perक्रमm coherency checks w/o using
**  the I/O MMU - basically what x86 करोes.
**
**  Philipp Rumpf has a "Real Mode" driver क्रम PCX-W machines at:
**      CVSROOT=:pserver:anonymous@198.186.203.37:/cvsroot/linux-parisc
**      cvs -z3 co linux/arch/parisc/kernel/dma-rm.c
**
**  I've rewritten his code to work under TPG's tree. See ccio-rm-dma.c.
**
**  Drawbacks of using Real Mode are:
**	o outbound DMA is slower - U2 won't prefetch data (GSC+ XQL संकेत).
**      o Inbound DMA less efficient - U2 can't use DMA_FAST attribute.
**	o Ability to करो scatter/gather in HW is lost.
**	o Doesn't work under PCX-U/U+ machines since they didn't follow
**        the coherency design originally worked out. Only PCX-W करोes.
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/reboot.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cache.h>		/* क्रम L1_CACHE_BYTES */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>       /* क्रम रेजिस्टर_module() */
#समावेश <यंत्र/parisc-device.h>

#समावेश "iommu.h"

/* 
** Choose "ccio" since that's what HP-UX calls it.
** Make it easier क्रम folks to migrate from one to the other :^)
*/
#घोषणा MODULE_NAME "ccio"

#अघोषित DEBUG_CCIO_RES
#अघोषित DEBUG_CCIO_RUN
#अघोषित DEBUG_CCIO_INIT
#अघोषित DEBUG_CCIO_RUN_SG

#अगर_घोषित CONFIG_PROC_FS
/* depends on proc fs support. But costs CPU perक्रमmance. */
#अघोषित CCIO_COLLECT_STATS
#पूर्ण_अगर

#समावेश <यंत्र/runway.h>		/* क्रम proc_runway_root */

#अगर_घोषित DEBUG_CCIO_INIT
#घोषणा DBG_INIT(x...)  prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_INIT(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_CCIO_RUN
#घोषणा DBG_RUN(x...)   prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RUN(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_CCIO_RES
#घोषणा DBG_RES(x...)   prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RES(x...)
#पूर्ण_अगर

#अगर_घोषित DEBUG_CCIO_RUN_SG
#घोषणा DBG_RUN_SG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RUN_SG(x...)
#पूर्ण_अगर

#घोषणा CCIO_INLINE	अंतरभूत
#घोषणा WRITE_U32(value, addr) __raw_ग_लिखोl(value, addr)
#घोषणा READ_U32(addr) __raw_पढ़ोl(addr)

#घोषणा U2_IOA_RUNWAY 0x580
#घोषणा U2_BC_GSC     0x501
#घोषणा UTURN_IOA_RUNWAY 0x581
#घोषणा UTURN_BC_GSC     0x502

#घोषणा IOA_NORMAL_MODE      0x00020080 /* IO_CONTROL to turn on CCIO        */
#घोषणा CMD_TLB_सूचीECT_WRITE 35         /* IO_COMMAND क्रम I/O TLB Writes     */
#घोषणा CMD_TLB_PURGE        33         /* IO_COMMAND to Purge I/O TLB entry */

काष्ठा ioa_रेजिस्टरs अणु
        /* Runway Supervisory Set */
        पूर्णांक32_t    unused1[12];
        uपूर्णांक32_t   io_command;             /* Offset 12 */
        uपूर्णांक32_t   io_status;              /* Offset 13 */
        uपूर्णांक32_t   io_control;             /* Offset 14 */
        पूर्णांक32_t    unused2[1];

        /* Runway Auxiliary Register Set */
        uपूर्णांक32_t   io_err_resp;            /* Offset  0 */
        uपूर्णांक32_t   io_err_info;            /* Offset  1 */
        uपूर्णांक32_t   io_err_req;             /* Offset  2 */
        uपूर्णांक32_t   io_err_resp_hi;         /* Offset  3 */
        uपूर्णांक32_t   io_tlb_entry_m;         /* Offset  4 */
        uपूर्णांक32_t   io_tlb_entry_l;         /* Offset  5 */
        uपूर्णांक32_t   unused3[1];
        uपूर्णांक32_t   io_pdir_base;           /* Offset  7 */
        uपूर्णांक32_t   io_io_low_hv;           /* Offset  8 */
        uपूर्णांक32_t   io_io_high_hv;          /* Offset  9 */
        uपूर्णांक32_t   unused4[1];
        uपूर्णांक32_t   io_chain_id_mask;       /* Offset 11 */
        uपूर्णांक32_t   unused5[2];
        uपूर्णांक32_t   io_io_low;              /* Offset 14 */
        uपूर्णांक32_t   io_io_high;             /* Offset 15 */
पूर्ण;

/*
** IOA Registers
** -------------
**
** Runway IO_CONTROL Register (+0x38)
** 
** The Runway IO_CONTROL रेजिस्टर controls the क्रमwarding of transactions.
**
** | 0  ...  13  |  14 15 | 16 ... 21 | 22 | 23 24 |  25 ... 31 |
** |    HV       |   TLB  |  reserved | HV | mode  |  reserved  |
**
** o mode field indicates the address translation of transactions
**   क्रमwarded from Runway to GSC+:
**       Mode Name     Value        Definition
**       Off (शेष)   0          Opaque to matching addresses.
**       Include         1          Transparent क्रम matching addresses.
**       Peek            3          Map matching addresses.
**
**       + "Off" mode: Runway transactions which match the I/O range
**         specअगरied by the IO_IO_LOW/IO_IO_HIGH रेजिस्टरs will be ignored.
**       + "Include" mode: all addresses within the I/O range specअगरied
**         by the IO_IO_LOW and IO_IO_HIGH रेजिस्टरs are transparently
**         क्रमwarded. This is the I/O Adapter's normal operating mode.
**       + "Peek" mode: used during प्रणाली configuration to initialize the
**         GSC+ bus. Runway Write_Shorts in the address range specअगरied by
**         IO_IO_LOW and IO_IO_HIGH are क्रमwarded through the I/O Adapter
**         *AND* the GSC+ address is remapped to the Broadcast Physical
**         Address space by setting the 14 high order address bits of the
**         32 bit GSC+ address to ones.
**
** o TLB field affects transactions which are क्रमwarded from GSC+ to Runway.
**   "Real" mode is the घातeron शेष.
** 
**   TLB Mode  Value  Description
**   Real        0    No TLB translation. Address is directly mapped and the
**                    भव address is composed of selected physical bits.
**   Error       1    Software fills the TLB manually.
**   Normal      2    IOA fetches IO TLB misses from IO Pसूची (in host memory).
**
**
** IO_IO_LOW_HV	  +0x60 (HV dependent)
** IO_IO_HIGH_HV  +0x64 (HV dependent)
** IO_IO_LOW      +0x78	(Architected रेजिस्टर)
** IO_IO_HIGH     +0x7c	(Architected रेजिस्टर)
**
** IO_IO_LOW and IO_IO_HIGH set the lower and upper bounds of the
** I/O Adapter address space, respectively.
**
** 0  ... 7 | 8 ... 15 |  16   ...   31 |
** 11111111 | 11111111 |      address   |
**
** Each LOW/HIGH pair describes a disjoपूर्णांक address space region.
** (2 per GSC+ port). Each incoming Runway transaction address is compared
** with both sets of LOW/HIGH रेजिस्टरs. If the address is in the range
** greater than or equal to IO_IO_LOW and less than IO_IO_HIGH the transaction
** क्रम क्रमwarded to the respective GSC+ bus.
** Specअगरy IO_IO_LOW equal to or greater than IO_IO_HIGH to aव्योम specअगरying
** an address space region.
**
** In order क्रम a Runway address to reside within GSC+ extended address space:
**	Runway Address [0:7]    must identically compare to 8'b11111111
**	Runway Address [8:11]   must be equal to IO_IO_LOW(_HV)[16:19]
** 	Runway Address [12:23]  must be greater than or equal to
**	           IO_IO_LOW(_HV)[20:31] and less than IO_IO_HIGH(_HV)[20:31].
**	Runway Address [24:39]  is not used in the comparison.
**
** When the Runway transaction is क्रमwarded to GSC+, the GSC+ address is
** as follows:
**	GSC+ Address[0:3]	4'b1111
**	GSC+ Address[4:29]	Runway Address[12:37]
**	GSC+ Address[30:31]	2'b00
**
** All 4 Low/High रेजिस्टरs must be initialized (by PDC) once the lower bus
** is पूर्णांकerrogated and address space is defined. The operating प्रणाली will
** modअगरy the architectural IO_IO_LOW and IO_IO_HIGH रेजिस्टरs following
** the PDC initialization.  However, the hardware version dependent IO_IO_LOW
** and IO_IO_HIGH रेजिस्टरs should not be subsequently altered by the OS.
** 
** Writes to both sets of रेजिस्टरs will take effect immediately, bypassing
** the queues, which ensures that subsequent Runway transactions are checked
** against the updated bounds values. However पढ़ोs are queued, पूर्णांकroducing
** the possibility of a पढ़ो being bypassed by a subsequent ग_लिखो to the same
** रेजिस्टर. This sequence can be aव्योमed by having software रुको क्रम पढ़ो
** वापसs beक्रमe issuing subsequent ग_लिखोs.
*/

काष्ठा ioc अणु
	काष्ठा ioa_रेजिस्टरs __iomem *ioc_regs;  /* I/O MMU base address */
	u8  *res_map;	                /* resource map, bit == pdir entry */
	u64 *pdir_base;	                /* physical base address */
	u32 pdir_size; 			/* bytes, function of IOV Space size */
	u32 res_hपूर्णांक;	                /* next available IOVP - 
					   circular search */
	u32 res_size;		    	/* size of resource map in bytes */
	spinlock_t res_lock;

#अगर_घोषित CCIO_COLLECT_STATS
#घोषणा CCIO_SEARCH_SAMPLE 0x100
	अचिन्हित दीर्घ avg_search[CCIO_SEARCH_SAMPLE];
	अचिन्हित दीर्घ avg_idx;		  /* current index पूर्णांकo avg_search */
	अचिन्हित दीर्घ used_pages;
	अचिन्हित दीर्घ msingle_calls;
	अचिन्हित दीर्घ msingle_pages;
	अचिन्हित दीर्घ msg_calls;
	अचिन्हित दीर्घ msg_pages;
	अचिन्हित दीर्घ usingle_calls;
	अचिन्हित दीर्घ usingle_pages;
	अचिन्हित दीर्घ usg_calls;
	अचिन्हित दीर्घ usg_pages;
#पूर्ण_अगर
	अचिन्हित लघु cujo20_bug;

	/* STUFF We करोn't need in perक्रमmance path */
	u32 chainid_shअगरt; 		/* specअगरy bit location of chain_id */
	काष्ठा ioc *next;		/* Linked list of discovered iocs */
	स्थिर अक्षर *name;		/* device name from firmware */
	अचिन्हित पूर्णांक hw_path;           /* the hardware path this ioc is associatd with */
	काष्ठा pci_dev *fake_pci_dev;   /* the fake pci_dev क्रम non-pci devs */
	काष्ठा resource mmio_region[2]; /* The "routed" MMIO regions */
पूर्ण;

अटल काष्ठा ioc *ioc_list;
अटल पूर्णांक ioc_count;

/**************************************************************
*
*   I/O Pdir Resource Management
*
*   Bits set in the resource map are in use.
*   Each bit can represent a number of pages.
*   LSbs represent lower addresses (IOVA's).
*
*   This was was copied from sba_iommu.c. Don't try to unअगरy
*   the two resource managers unless a way to have dअगरferent
*   allocation policies is also adjusted. We'd like to aव्योम
*   I/O TLB thrashing by having resource allocation policy
*   match the I/O TLB replacement policy.
*
***************************************************************/
#घोषणा IOVP_SIZE PAGE_SIZE
#घोषणा IOVP_SHIFT PAGE_SHIFT
#घोषणा IOVP_MASK PAGE_MASK

/* Convert from IOVP to IOVA and vice versa. */
#घोषणा CCIO_IOVA(iovp,offset) ((iovp) | (offset))
#घोषणा CCIO_IOVP(iova) ((iova) & IOVP_MASK)

#घोषणा Pसूची_INDEX(iovp)    ((iovp)>>IOVP_SHIFT)
#घोषणा MKIOVP(pdir_idx)    ((दीर्घ)(pdir_idx) << IOVP_SHIFT)
#घोषणा MKIOVA(iovp,offset) (dma_addr_t)((दीर्घ)iovp | (दीर्घ)offset)

/*
** Don't worry about the 150% average search length on a miss.
** If the search wraps around, and passes the res_hपूर्णांक, it will
** cause the kernel to panic anyhow.
*/
#घोषणा CCIO_SEARCH_LOOP(ioc, res_idx, mask, size)  \
       क्रम(; res_ptr < res_end; ++res_ptr) अणु \
		पूर्णांक ret;\
		अचिन्हित पूर्णांक idx;\
		idx = (अचिन्हित पूर्णांक)((अचिन्हित दीर्घ)res_ptr - (अचिन्हित दीर्घ)ioc->res_map); \
		ret = iommu_is_span_boundary(idx << 3, pages_needed, 0, boundary_size);\
		अगर ((0 == (*res_ptr & mask)) && !ret) अणु \
			*res_ptr |= mask; \
			res_idx = idx;\
			ioc->res_hपूर्णांक = res_idx + (size >> 3); \
			जाओ resource_found; \
		पूर्ण \
	पूर्ण

#घोषणा CCIO_FIND_FREE_MAPPING(ioa, res_idx, mask, size) \
       u##size *res_ptr = (u##size *)&((ioc)->res_map[ioa->res_hपूर्णांक & ~((size >> 3) - 1)]); \
       u##size *res_end = (u##size *)&(ioc)->res_map[ioa->res_size]; \
       CCIO_SEARCH_LOOP(ioc, res_idx, mask, size); \
       res_ptr = (u##size *)&(ioc)->res_map[0]; \
       CCIO_SEARCH_LOOP(ioa, res_idx, mask, size);

/*
** Find available bit in this ioa's resource map.
** Use a "circular" search:
**   o Most IOVA's are "temporary" - avg search समय should be small.
** o keep a history of what happened क्रम debugging
** o KISS.
**
** Perf optimizations:
** o search क्रम log2(size) bits at a समय.
** o search क्रम available resource bits using byte/word/whatever.
** o use dअगरferent search क्रम "large" (eg > 4 pages) or "very large"
**   (eg > 16 pages) mappings.
*/

/**
 * ccio_alloc_range - Allocate pages in the ioc's resource map.
 * @ioc: The I/O Controller.
 * @pages_needed: The requested number of pages to be mapped पूर्णांकo the
 * I/O Pdir...
 *
 * This function searches the resource map of the ioc to locate a range
 * of available pages क्रम the requested size.
 */
अटल पूर्णांक
ccio_alloc_range(काष्ठा ioc *ioc, काष्ठा device *dev, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक pages_needed = size >> IOVP_SHIFT;
	अचिन्हित पूर्णांक res_idx;
	अचिन्हित दीर्घ boundary_size;
#अगर_घोषित CCIO_COLLECT_STATS
	अचिन्हित दीर्घ cr_start = mfctl(16);
#पूर्ण_अगर
	
	BUG_ON(pages_needed == 0);
	BUG_ON((pages_needed * IOVP_SIZE) > DMA_CHUNK_SIZE);
     
	DBG_RES("%s() size: %d pages_needed %d\n", 
		__func__, size, pages_needed);

	/*
	** "seek and ye shall find"...praying never hurts either...
	** ggg sacrअगरices another 710 to the computer gods.
	*/

	boundary_size = dma_get_seg_boundary_nr_pages(dev, IOVP_SHIFT);

	अगर (pages_needed <= 8) अणु
		/*
		 * LAN traffic will not thrash the TLB IFF the same NIC
		 * uses 8 adjacent pages to map separate payload data.
		 * ie the same byte in the resource bit map.
		 */
#अगर 0
		/* FIXME: bit search should shअगरt it's way through
		 * an अचिन्हित दीर्घ - not byte at a समय. As it is now,
		 * we effectively allocate this byte to this mapping.
		 */
		अचिन्हित दीर्घ mask = ~(~0UL >> pages_needed);
		CCIO_FIND_FREE_MAPPING(ioc, res_idx, mask, 8);
#अन्यथा
		CCIO_FIND_FREE_MAPPING(ioc, res_idx, 0xff, 8);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (pages_needed <= 16) अणु
		CCIO_FIND_FREE_MAPPING(ioc, res_idx, 0xffff, 16);
	पूर्ण अन्यथा अगर (pages_needed <= 32) अणु
		CCIO_FIND_FREE_MAPPING(ioc, res_idx, ~(अचिन्हित पूर्णांक)0, 32);
#अगर_घोषित __LP64__
	पूर्ण अन्यथा अगर (pages_needed <= 64) अणु
		CCIO_FIND_FREE_MAPPING(ioc, res_idx, ~0UL, 64);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		panic("%s: %s() Too many pages to map. pages_needed: %u\n",
		       __खाता__,  __func__, pages_needed);
	पूर्ण

	panic("%s: %s() I/O MMU is out of mapping resources.\n", __खाता__,
	      __func__);
	
resource_found:
	
	DBG_RES("%s() res_idx %d res_hint: %d\n",
		__func__, res_idx, ioc->res_hपूर्णांक);

#अगर_घोषित CCIO_COLLECT_STATS
	अणु
		अचिन्हित दीर्घ cr_end = mfctl(16);
		अचिन्हित दीर्घ पंचांगp = cr_end - cr_start;
		/* check क्रम roll over */
		cr_start = (cr_end < cr_start) ?  -(पंचांगp) : (पंचांगp);
	पूर्ण
	ioc->avg_search[ioc->avg_idx++] = cr_start;
	ioc->avg_idx &= CCIO_SEARCH_SAMPLE - 1;
	ioc->used_pages += pages_needed;
#पूर्ण_अगर
	/* 
	** वापस the bit address.
	*/
	वापस res_idx << 3;
पूर्ण

#घोषणा CCIO_FREE_MAPPINGS(ioc, res_idx, mask, size) \
        u##size *res_ptr = (u##size *)&((ioc)->res_map[res_idx]); \
        BUG_ON((*res_ptr & mask) != mask); \
        *res_ptr &= ~(mask);

/**
 * ccio_मुक्त_range - Free pages from the ioc's resource map.
 * @ioc: The I/O Controller.
 * @iova: The I/O Virtual Address.
 * @pages_mapped: The requested number of pages to be मुक्तd from the
 * I/O Pdir.
 *
 * This function मुक्तs the resouces allocated क्रम the iova.
 */
अटल व्योम
ccio_मुक्त_range(काष्ठा ioc *ioc, dma_addr_t iova, अचिन्हित दीर्घ pages_mapped)
अणु
	अचिन्हित दीर्घ iovp = CCIO_IOVP(iova);
	अचिन्हित पूर्णांक res_idx = Pसूची_INDEX(iovp) >> 3;

	BUG_ON(pages_mapped == 0);
	BUG_ON((pages_mapped * IOVP_SIZE) > DMA_CHUNK_SIZE);
	BUG_ON(pages_mapped > BITS_PER_LONG);

	DBG_RES("%s():  res_idx: %d pages_mapped %d\n", 
		__func__, res_idx, pages_mapped);

#अगर_घोषित CCIO_COLLECT_STATS
	ioc->used_pages -= pages_mapped;
#पूर्ण_अगर

	अगर(pages_mapped <= 8) अणु
#अगर 0
		/* see matching comments in alloc_range */
		अचिन्हित दीर्घ mask = ~(~0UL >> pages_mapped);
		CCIO_FREE_MAPPINGS(ioc, res_idx, mask, 8);
#अन्यथा
		CCIO_FREE_MAPPINGS(ioc, res_idx, 0xffUL, 8);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर(pages_mapped <= 16) अणु
		CCIO_FREE_MAPPINGS(ioc, res_idx, 0xffffUL, 16);
	पूर्ण अन्यथा अगर(pages_mapped <= 32) अणु
		CCIO_FREE_MAPPINGS(ioc, res_idx, ~(अचिन्हित पूर्णांक)0, 32);
#अगर_घोषित __LP64__
	पूर्ण अन्यथा अगर(pages_mapped <= 64) अणु
		CCIO_FREE_MAPPINGS(ioc, res_idx, ~0UL, 64);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		panic("%s:%s() Too many pages to unmap.\n", __खाता__,
		      __func__);
	पूर्ण
पूर्ण

/****************************************************************
**
**          CCIO dma_ops support routines
**
*****************************************************************/

प्रकार अचिन्हित दीर्घ space_t;
#घोषणा KERNEL_SPACE 0

/*
** DMA "Page Type" and Hपूर्णांकs 
** o अगर SAFE_DMA isn't set, mapping is क्रम FAST_DMA. SAFE_DMA should be
**   set क्रम subcacheline DMA transfers since we करोn't want to damage the
**   other part of a cacheline.
** o SAFE_DMA must be set क्रम "memory" allocated via pci_alloc_consistent().
**   This bit tells U2 to करो R/M/W क्रम partial cachelines. "Streaming"
**   data can aव्योम this अगर the mapping covers full cache lines.
** o STOP_MOST is needed क्रम atomicity across cachelines.
**   Apparently only "some EISA devices" need this.
**   Using CONFIG_ISA is hack. Only the IOA with EISA under it needs
**   to use this hपूर्णांक अगरf the EISA devices needs this feature.
**   According to the U2 ERS, STOP_MOST enabled pages hurt perक्रमmance.
** o PREFETCH should *not* be set क्रम हालs like Multiple PCI devices
**   behind GSCtoPCI (dino) bus converter. Only one cacheline per GSC
**   device can be fetched and multiply DMA streams will thrash the
**   prefetch buffer and burn memory bandwidth. See 6.7.3 "Prefetch Rules
**   and Invalidation of Prefetch Entries".
**
** FIXME: the शेष hपूर्णांकs need to be per GSC device - not global.
** 
** HP-UX करोrks: linux device driver programming model is totally dअगरferent
**    than HP-UX's. HP-UX always sets HINT_PREFETCH since it's drivers
**    करो special things to work on non-coherent platक्रमms...linux has to
**    be much more careful with this.
*/
#घोषणा IOPसूची_VALID    0x01UL
#घोषणा HINT_SAFE_DMA   0x02UL	/* used क्रम pci_alloc_consistent() pages */
#अगर_घोषित CONFIG_EISA
#घोषणा HINT_STOP_MOST  0x04UL	/* LSL support */
#अन्यथा
#घोषणा HINT_STOP_MOST  0x00UL	/* only needed क्रम "some EISA devices" */
#पूर्ण_अगर
#घोषणा HINT_UDPATE_ENB 0x08UL  /* not used/supported by U2 */
#घोषणा HINT_PREFETCH   0x10UL	/* क्रम outbound pages which are not SAFE */


/*
** Use direction (ie PCI_DMA_TODEVICE) to pick hपूर्णांक.
** ccio_alloc_consistent() depends on this to get SAFE_DMA
** when it passes in BIसूचीECTIONAL flag.
*/
अटल u32 hपूर्णांक_lookup[] = अणु
	[PCI_DMA_BIसूचीECTIONAL]	= HINT_STOP_MOST | HINT_SAFE_DMA | IOPसूची_VALID,
	[PCI_DMA_TODEVICE]	= HINT_STOP_MOST | HINT_PREFETCH | IOPसूची_VALID,
	[PCI_DMA_FROMDEVICE]	= HINT_STOP_MOST | IOPसूची_VALID,
पूर्ण;

/**
 * ccio_io_pdir_entry - Initialize an I/O Pdir.
 * @pdir_ptr: A poपूर्णांकer पूर्णांकo I/O Pdir.
 * @sid: The Space Identअगरier.
 * @vba: The भव address.
 * @hपूर्णांकs: The DMA Hपूर्णांक.
 *
 * Given a भव address (vba, arg2) and space id, (sid, arg1),
 * load the I/O Pसूची entry poपूर्णांकed to by pdir_ptr (arg0). Each IO Pdir
 * entry consists of 8 bytes as shown below (MSB == bit 0):
 *
 *
 * WORD 0:
 * +------+----------------+-----------------------------------------------+
 * | Phys | Virtual Index  |               Phys                            |
 * | 0:3  |     0:11       |               4:19                            |
 * |4 bits|   12 bits      |              16 bits                          |
 * +------+----------------+-----------------------------------------------+
 * WORD 1:
 * +-----------------------+-----------------------------------------------+
 * |      Phys    |  Rsvd  | Prefetch |Update |Rsvd  |Lock  |Safe  |Valid  |
 * |     20:39    |        | Enable   |Enable |      |Enable|DMA   |       |
 * |    20 bits   | 5 bits | 1 bit    |1 bit  |2 bits|1 bit |1 bit |1 bit  |
 * +-----------------------+-----------------------------------------------+
 *
 * The भव index field is filled with the results of the LCI
 * (Load Coherence Index) inकाष्ठाion.  The 8 bits used क्रम the भव
 * index are bits 12:19 of the value वापसed by LCI.
 */ 
अटल व्योम CCIO_INLINE
ccio_io_pdir_entry(u64 *pdir_ptr, space_t sid, अचिन्हित दीर्घ vba,
		   अचिन्हित दीर्घ hपूर्णांकs)
अणु
	रेजिस्टर अचिन्हित दीर्घ pa;
	रेजिस्टर अचिन्हित दीर्घ ci; /* coherent index */

	/* We currently only support kernel addresses */
	BUG_ON(sid != KERNEL_SPACE);

	/*
	** WORD 1 - low order word
	** "hints" parm includes the VALID bit!
	** "dep" clobbers the physical address offset bits as well.
	*/
	pa = lpa(vba);
	यंत्र अस्थिर("depw  %1,31,12,%0" : "+r" (pa) : "r" (hपूर्णांकs));
	((u32 *)pdir_ptr)[1] = (u32) pa;

	/*
	** WORD 0 - high order word
	*/

#अगर_घोषित __LP64__
	/*
	** get bits 12:15 of physical address
	** shअगरt bits 16:31 of physical address
	** and deposit them
	*/
	यंत्र अस्थिर ("extrd,u %1,15,4,%0" : "=r" (ci) : "r" (pa));
	यंत्र अस्थिर ("extrd,u %1,31,16,%0" : "+r" (pa) : "r" (pa));
	यंत्र अस्थिर ("depd  %1,35,4,%0" : "+r" (pa) : "r" (ci));
#अन्यथा
	pa = 0;
#पूर्ण_अगर
	/*
	** get CPU coherency index bits
	** Grab भव index [0:11]
	** Deposit virt_idx bits पूर्णांकo I/O Pसूची word
	*/
	यंत्र अस्थिर ("lci %%r0(%1), %0" : "=r" (ci) : "r" (vba));
	यंत्र अस्थिर ("extru %1,19,12,%0" : "+r" (ci) : "r" (ci));
	यंत्र अस्थिर ("depw  %1,15,12,%0" : "+r" (pa) : "r" (ci));

	((u32 *)pdir_ptr)[0] = (u32) pa;


	/* FIXME: PCX_W platक्रमms करोn't need FDC/SYNC. (eg C360)
	**        PCX-U/U+ करो. (eg C200/C240)
	**        PCX-T'? Don't know. (eg C110 or similar K-class)
	**
	** See PDC_MODEL/option 0/SW_CAP word क्रम "Non-coherent IO-PDIR bit".
	**
	** "Since PCX-U employs an offset hash that is incompatible with
	** the real mode coherence index generation of U2, the Pसूची entry
	** must be flushed to memory to retain coherence."
	*/
	यंत्र_io_fdc(pdir_ptr);
	यंत्र_io_sync();
पूर्ण

/**
 * ccio_clear_io_tlb - Remove stale entries from the I/O TLB.
 * @ioc: The I/O Controller.
 * @iovp: The I/O Virtual Page.
 * @byte_cnt: The requested number of bytes to be मुक्तd from the I/O Pdir.
 *
 * Purge invalid I/O Pसूची entries from the I/O TLB.
 *
 * FIXME: Can we change the byte_cnt to pages_mapped?
 */
अटल CCIO_INLINE व्योम
ccio_clear_io_tlb(काष्ठा ioc *ioc, dma_addr_t iovp, माप_प्रकार byte_cnt)
अणु
	u32 chain_size = 1 << ioc->chainid_shअगरt;

	iovp &= IOVP_MASK;	/* clear offset bits, just want pagक्रमागत */
	byte_cnt += chain_size;

	जबतक(byte_cnt > chain_size) अणु
		WRITE_U32(CMD_TLB_PURGE | iovp, &ioc->ioc_regs->io_command);
		iovp += chain_size;
		byte_cnt -= chain_size;
	पूर्ण
पूर्ण

/**
 * ccio_mark_invalid - Mark the I/O Pdir entries invalid.
 * @ioc: The I/O Controller.
 * @iova: The I/O Virtual Address.
 * @byte_cnt: The requested number of bytes to be मुक्तd from the I/O Pdir.
 *
 * Mark the I/O Pdir entries invalid and blow away the corresponding I/O
 * TLB entries.
 *
 * FIXME: at some threshold it might be "cheaper" to just blow
 *        away the entire I/O TLB instead of inभागidual entries.
 *
 * FIXME: Uturn has 256 TLB entries. We करोn't need to purge every
 *        Pसूची entry - just once क्रम each possible TLB entry.
 *        (We करो need to maker I/O Pसूची entries invalid regardless).
 *
 * FIXME: Can we change byte_cnt to pages_mapped?
 */ 
अटल CCIO_INLINE व्योम
ccio_mark_invalid(काष्ठा ioc *ioc, dma_addr_t iova, माप_प्रकार byte_cnt)
अणु
	u32 iovp = (u32)CCIO_IOVP(iova);
	माप_प्रकार saved_byte_cnt;

	/* round up to nearest page size */
	saved_byte_cnt = byte_cnt = ALIGN(byte_cnt, IOVP_SIZE);

	जबतक(byte_cnt > 0) अणु
		/* invalidate one page at a समय */
		अचिन्हित पूर्णांक idx = Pसूची_INDEX(iovp);
		अक्षर *pdir_ptr = (अक्षर *) &(ioc->pdir_base[idx]);

		BUG_ON(idx >= (ioc->pdir_size / माप(u64)));
		pdir_ptr[7] = 0;	/* clear only VALID bit */ 
		/*
		** FIXME: PCX_W platक्रमms करोn't need FDC/SYNC. (eg C360)
		**   PCX-U/U+ करो. (eg C200/C240)
		** See PDC_MODEL/option 0/SW_CAP क्रम "Non-coherent IO-PDIR bit".
		*/
		यंत्र_io_fdc(pdir_ptr);

		iovp     += IOVP_SIZE;
		byte_cnt -= IOVP_SIZE;
	पूर्ण

	यंत्र_io_sync();
	ccio_clear_io_tlb(ioc, CCIO_IOVP(iova), saved_byte_cnt);
पूर्ण

/****************************************************************
**
**          CCIO dma_ops
**
*****************************************************************/

/**
 * ccio_dma_supported - Verअगरy the IOMMU supports the DMA address range.
 * @dev: The PCI device.
 * @mask: A bit mask describing the DMA address range of the device.
 */
अटल पूर्णांक 
ccio_dma_supported(काष्ठा device *dev, u64 mask)
अणु
	अगर(dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": EISA/ISA/et al not supported\n");
		BUG();
		वापस 0;
	पूर्ण

	/* only support 32-bit or better devices (ie PCI/GSC) */
	वापस (पूर्णांक)(mask >= 0xffffffffUL);
पूर्ण

/**
 * ccio_map_single - Map an address range पूर्णांकo the IOMMU.
 * @dev: The PCI device.
 * @addr: The start address of the DMA region.
 * @size: The length of the DMA region.
 * @direction: The direction of the DMA transaction (to/from device).
 *
 * This function implements the pci_map_single function.
 */
अटल dma_addr_t 
ccio_map_single(काष्ठा device *dev, व्योम *addr, माप_प्रकार size,
		क्रमागत dma_data_direction direction)
अणु
	पूर्णांक idx;
	काष्ठा ioc *ioc;
	अचिन्हित दीर्घ flags;
	dma_addr_t iovp;
	dma_addr_t offset;
	u64 *pdir_start;
	अचिन्हित दीर्घ hपूर्णांक = hपूर्णांक_lookup[(पूर्णांक)direction];

	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	अगर (!ioc)
		वापस DMA_MAPPING_ERROR;

	BUG_ON(size <= 0);

	/* save offset bits */
	offset = ((अचिन्हित दीर्घ) addr) & ~IOVP_MASK;

	/* round up to nearest IOVP_SIZE */
	size = ALIGN(size + offset, IOVP_SIZE);
	spin_lock_irqsave(&ioc->res_lock, flags);

#अगर_घोषित CCIO_COLLECT_STATS
	ioc->msingle_calls++;
	ioc->msingle_pages += size >> IOVP_SHIFT;
#पूर्ण_अगर

	idx = ccio_alloc_range(ioc, dev, size);
	iovp = (dma_addr_t)MKIOVP(idx);

	pdir_start = &(ioc->pdir_base[idx]);

	DBG_RUN("%s() 0x%p -> 0x%lx size: %0x%x\n",
		__func__, addr, (दीर्घ)iovp | offset, size);

	/* If not cacheline aligned, क्रमce SAFE_DMA on the whole mess */
	अगर((size % L1_CACHE_BYTES) || ((अचिन्हित दीर्घ)addr % L1_CACHE_BYTES))
		hपूर्णांक |= HINT_SAFE_DMA;

	जबतक(size > 0) अणु
		ccio_io_pdir_entry(pdir_start, KERNEL_SPACE, (अचिन्हित दीर्घ)addr, hपूर्णांक);

		DBG_RUN(" pdir %p %08x%08x\n",
			pdir_start,
			(u32) (((u32 *) pdir_start)[0]),
			(u32) (((u32 *) pdir_start)[1]));
		++pdir_start;
		addr += IOVP_SIZE;
		size -= IOVP_SIZE;
	पूर्ण

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	/* क्रमm complete address */
	वापस CCIO_IOVA(iovp, offset);
पूर्ण


अटल dma_addr_t
ccio_map_page(काष्ठा device *dev, काष्ठा page *page, अचिन्हित दीर्घ offset,
		माप_प्रकार size, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	वापस ccio_map_single(dev, page_address(page) + offset, size,
			direction);
पूर्ण


/**
 * ccio_unmap_page - Unmap an address range from the IOMMU.
 * @dev: The PCI device.
 * @addr: The start address of the DMA region.
 * @size: The length of the DMA region.
 * @direction: The direction of the DMA transaction (to/from device).
 */
अटल व्योम 
ccio_unmap_page(काष्ठा device *dev, dma_addr_t iova, माप_प्रकार size,
		क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
	अचिन्हित दीर्घ flags; 
	dma_addr_t offset = iova & ~IOVP_MASK;
	
	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	अगर (!ioc) अणु
		WARN_ON(!ioc);
		वापस;
	पूर्ण

	DBG_RUN("%s() iovp 0x%lx/%x\n",
		__func__, (दीर्घ)iova, size);

	iova ^= offset;        /* clear offset bits */
	size += offset;
	size = ALIGN(size, IOVP_SIZE);

	spin_lock_irqsave(&ioc->res_lock, flags);

#अगर_घोषित CCIO_COLLECT_STATS
	ioc->usingle_calls++;
	ioc->usingle_pages += size >> IOVP_SHIFT;
#पूर्ण_अगर

	ccio_mark_invalid(ioc, iova, size);
	ccio_मुक्त_range(ioc, iova, (size >> IOVP_SHIFT));
	spin_unlock_irqrestore(&ioc->res_lock, flags);
पूर्ण

/**
 * ccio_alloc - Allocate a consistent DMA mapping.
 * @dev: The PCI device.
 * @size: The length of the DMA region.
 * @dma_handle: The DMA address handed back to the device (not the cpu).
 *
 * This function implements the pci_alloc_consistent function.
 */
अटल व्योम * 
ccio_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle, gfp_t flag,
		अचिन्हित दीर्घ attrs)
अणु
      व्योम *ret;
#अगर 0
/* GRANT Need to establish hierarchy क्रम non-PCI devs as well
** and then provide matching gsc_map_xxx() functions क्रम them as well.
*/
	अगर(!hwdev) अणु
		/* only support PCI */
		*dma_handle = 0;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
        ret = (व्योम *) __get_मुक्त_pages(flag, get_order(size));

	अगर (ret) अणु
		स_रखो(ret, 0, size);
		*dma_handle = ccio_map_single(dev, ret, size, PCI_DMA_BIसूचीECTIONAL);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ccio_मुक्त - Free a consistent DMA mapping.
 * @dev: The PCI device.
 * @size: The length of the DMA region.
 * @cpu_addr: The cpu address वापसed from the ccio_alloc_consistent.
 * @dma_handle: The device address वापसed from the ccio_alloc_consistent.
 *
 * This function implements the pci_मुक्त_consistent function.
 */
अटल व्योम 
ccio_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	ccio_unmap_page(dev, dma_handle, size, 0, 0);
	मुक्त_pages((अचिन्हित दीर्घ)cpu_addr, get_order(size));
पूर्ण

/*
** Since 0 is a valid pdir_base index value, can't use that
** to determine अगर a value is valid or not. Use a flag to indicate
** the SG list entry contains a valid pdir index.
*/
#घोषणा PIDE_FLAG 0x80000000UL

#अगर_घोषित CCIO_COLLECT_STATS
#घोषणा IOMMU_MAP_STATS
#पूर्ण_अगर
#समावेश "iommu-helpers.h"

/**
 * ccio_map_sg - Map the scatter/gather list पूर्णांकo the IOMMU.
 * @dev: The PCI device.
 * @sglist: The scatter/gather list to be mapped in the IOMMU.
 * @nents: The number of entries in the scatter/gather list.
 * @direction: The direction of the DMA transaction (to/from device).
 *
 * This function implements the pci_map_sg function.
 */
अटल पूर्णांक
ccio_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist, पूर्णांक nents, 
	    क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;
	पूर्णांक coalesced, filled = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ hपूर्णांक = hपूर्णांक_lookup[(पूर्णांक)direction];
	अचिन्हित दीर्घ prev_len = 0, current_len = 0;
	पूर्णांक i;
	
	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	अगर (!ioc)
		वापस 0;
	
	DBG_RUN_SG("%s() START %d entries\n", __func__, nents);

	/* Fast path single entry scatterlists. */
	अगर (nents == 1) अणु
		sg_dma_address(sglist) = ccio_map_single(dev,
				sg_virt(sglist), sglist->length,
				direction);
		sg_dma_len(sglist) = sglist->length;
		वापस 1;
	पूर्ण

	क्रम(i = 0; i < nents; i++)
		prev_len += sglist[i].length;
	
	spin_lock_irqsave(&ioc->res_lock, flags);

#अगर_घोषित CCIO_COLLECT_STATS
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
	coalesced = iommu_coalesce_chunks(ioc, dev, sglist, nents, ccio_alloc_range);

	/*
	** Program the I/O Pdir
	**
	** map the भव addresses to the I/O Pdir
	** o dma_address will contain the pdir index
	** o dma_len will contain the number of bytes to map 
	** o page/offset contain the भव address.
	*/
	filled = iommu_fill_pdir(ioc, sglist, nents, hपूर्णांक, ccio_io_pdir_entry);

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	BUG_ON(coalesced != filled);

	DBG_RUN_SG("%s() DONE %d mappings\n", __func__, filled);

	क्रम (i = 0; i < filled; i++)
		current_len += sg_dma_len(sglist + i);

	BUG_ON(current_len != prev_len);

	वापस filled;
पूर्ण

/**
 * ccio_unmap_sg - Unmap the scatter/gather list from the IOMMU.
 * @dev: The PCI device.
 * @sglist: The scatter/gather list to be unmapped from the IOMMU.
 * @nents: The number of entries in the scatter/gather list.
 * @direction: The direction of the DMA transaction (to/from device).
 *
 * This function implements the pci_unmap_sg function.
 */
अटल व्योम 
ccio_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist, पूर्णांक nents, 
	      क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ioc *ioc;

	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	अगर (!ioc) अणु
		WARN_ON(!ioc);
		वापस;
	पूर्ण

	DBG_RUN_SG("%s() START %d entries, %p,%x\n",
		__func__, nents, sg_virt(sglist), sglist->length);

#अगर_घोषित CCIO_COLLECT_STATS
	ioc->usg_calls++;
#पूर्ण_अगर

	जबतक(sg_dma_len(sglist) && nents--) अणु

#अगर_घोषित CCIO_COLLECT_STATS
		ioc->usg_pages += sg_dma_len(sglist) >> PAGE_SHIFT;
#पूर्ण_अगर
		ccio_unmap_page(dev, sg_dma_address(sglist),
				  sg_dma_len(sglist), direction, 0);
		++sglist;
	पूर्ण

	DBG_RUN_SG("%s() DONE (nents %d)\n", __func__, nents);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops ccio_ops = अणु
	.dma_supported =	ccio_dma_supported,
	.alloc =		ccio_alloc,
	.मुक्त =			ccio_मुक्त,
	.map_page =		ccio_map_page,
	.unmap_page =		ccio_unmap_page,
	.map_sg = 		ccio_map_sg,
	.unmap_sg = 		ccio_unmap_sg,
	.get_sgtable =		dma_common_get_sgtable,
	.alloc_pages =		dma_common_alloc_pages,
	.मुक्त_pages =		dma_common_मुक्त_pages,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक ccio_proc_info(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा ioc *ioc = ioc_list;

	जबतक (ioc != शून्य) अणु
		अचिन्हित पूर्णांक total_pages = ioc->res_size << 3;
#अगर_घोषित CCIO_COLLECT_STATS
		अचिन्हित दीर्घ avg = 0, min, max;
		पूर्णांक j;
#पूर्ण_अगर

		seq_म_लिखो(m, "%s\n", ioc->name);
		
		seq_म_लिखो(m, "Cujo 2.0 bug    : %s\n",
			   (ioc->cujo20_bug ? "yes" : "no"));
		
		seq_म_लिखो(m, "IO PDIR size    : %d bytes (%d entries)\n",
			   total_pages * 8, total_pages);

#अगर_घोषित CCIO_COLLECT_STATS
		seq_म_लिखो(m, "IO PDIR entries : %ld free  %ld used (%d%%)\n",
			   total_pages - ioc->used_pages, ioc->used_pages,
			   (पूर्णांक)(ioc->used_pages * 100 / total_pages));
#पूर्ण_अगर

		seq_म_लिखो(m, "Resource bitmap : %d bytes (%d pages)\n",
			   ioc->res_size, total_pages);

#अगर_घोषित CCIO_COLLECT_STATS
		min = max = ioc->avg_search[0];
		क्रम(j = 0; j < CCIO_SEARCH_SAMPLE; ++j) अणु
			avg += ioc->avg_search[j];
			अगर(ioc->avg_search[j] > max) 
				max = ioc->avg_search[j];
			अगर(ioc->avg_search[j] < min) 
				min = ioc->avg_search[j];
		पूर्ण
		avg /= CCIO_SEARCH_SAMPLE;
		seq_म_लिखो(m, "  Bitmap search : %ld/%ld/%ld (min/avg/max CPU Cycles)\n",
			   min, avg, max);

		seq_म_लिखो(m, "pci_map_single(): %8ld calls  %8ld pages (avg %d/1000)\n",
			   ioc->msingle_calls, ioc->msingle_pages,
			   (पूर्णांक)((ioc->msingle_pages * 1000)/ioc->msingle_calls));

		/* KLUGE - unmap_sg calls unmap_page क्रम each mapped page */
		min = ioc->usingle_calls - ioc->usg_calls;
		max = ioc->usingle_pages - ioc->usg_pages;
		seq_म_लिखो(m, "pci_unmap_single: %8ld calls  %8ld pages (avg %d/1000)\n",
			   min, max, (पूर्णांक)((max * 1000)/min));
 
		seq_म_लिखो(m, "pci_map_sg()    : %8ld calls  %8ld pages (avg %d/1000)\n",
			   ioc->msg_calls, ioc->msg_pages,
			   (पूर्णांक)((ioc->msg_pages * 1000)/ioc->msg_calls));

		seq_म_लिखो(m, "pci_unmap_sg()  : %8ld calls  %8ld pages (avg %d/1000)\n\n\n",
			   ioc->usg_calls, ioc->usg_pages,
			   (पूर्णांक)((ioc->usg_pages * 1000)/ioc->usg_calls));
#पूर्ण_अगर	/* CCIO_COLLECT_STATS */

		ioc = ioc->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccio_proc_biपंचांगap_info(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा ioc *ioc = ioc_list;

	जबतक (ioc != शून्य) अणु
		seq_hex_dump(m, "   ", DUMP_PREFIX_NONE, 32, 4, ioc->res_map,
			     ioc->res_size, false);
		seq_अ_दो(m, '\n');
		ioc = ioc->next;
		अवरोध; /* XXX - हटाओ me */
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/**
 * ccio_find_ioc - Find the ioc in the ioc_list
 * @hw_path: The hardware path of the ioc.
 *
 * This function searches the ioc_list क्रम an ioc that matches
 * the provide hardware path.
 */
अटल काष्ठा ioc * ccio_find_ioc(पूर्णांक hw_path)
अणु
	पूर्णांक i;
	काष्ठा ioc *ioc;

	ioc = ioc_list;
	क्रम (i = 0; i < ioc_count; i++) अणु
		अगर (ioc->hw_path == hw_path)
			वापस ioc;

		ioc = ioc->next;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ccio_get_iommu - Find the iommu which controls this device
 * @dev: The parisc device.
 *
 * This function searches through the रेजिस्टरed IOMMU's and वापसs
 * the appropriate IOMMU क्रम the device based on its hardware path.
 */
व्योम * ccio_get_iommu(स्थिर काष्ठा parisc_device *dev)
अणु
	dev = find_pa_parent_type(dev, HPHW_IOA);
	अगर (!dev)
		वापस शून्य;

	वापस ccio_find_ioc(dev->hw_path);
पूर्ण

#घोषणा CUJO_20_STEP       0x10000000	/* inc upper nibble */

/* Cujo 2.0 has a bug which will silently corrupt data being transferred
 * to/from certain pages.  To aव्योम this happening, we mark these pages
 * as `used', and ensure that nothing will try to allocate from them.
 */
व्योम __init ccio_cujo20_fixup(काष्ठा parisc_device *cujo, u32 iovp)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा parisc_device *dev = parisc_parent(cujo);
	काष्ठा ioc *ioc = ccio_get_iommu(dev);
	u8 *res_ptr;

	ioc->cujo20_bug = 1;
	res_ptr = ioc->res_map;
	idx = Pसूची_INDEX(iovp) >> 3;

	जबतक (idx < ioc->res_size) अणु
 		res_ptr[idx] |= 0xff;
		idx += Pसूची_INDEX(CUJO_20_STEP) >> 3;
	पूर्ण
पूर्ण

#अगर 0
/* GRANT -  is this needed क्रम U2 or not? */

/*
** Get the size of the I/O TLB क्रम this I/O MMU.
**
** If spa_shअगरt is non-zero (ie probably U2),
** then calculate the I/O TLB size using spa_shअगरt.
**
** Otherwise we are supposed to get the IODC entry poपूर्णांक ENTRY TLB
** and execute it. However, both U2 and Uturn firmware supplies spa_shअगरt.
** I think only Java (K/D/R-class too?) प्रणालीs करोn't करो this.
*/
अटल पूर्णांक
ccio_get_iotlb_size(काष्ठा parisc_device *dev)
अणु
	अगर (dev->spa_shअगरt == 0) अणु
		panic("%s() : Can't determine I/O TLB size.\n", __func__);
	पूर्ण
	वापस (1 << dev->spa_shअगरt);
पूर्ण
#अन्यथा

/* Uturn supports 256 TLB entries */
#घोषणा CCIO_CHAINID_SHIFT	8
#घोषणा CCIO_CHAINID_MASK	0xff
#पूर्ण_अगर /* 0 */

/* We *can't* support JAVA (T600). Venture there at your own risk. */
अटल स्थिर काष्ठा parisc_device_id ccio_tbl[] __initस्थिर = अणु
	अणु HPHW_IOA, HVERSION_REV_ANY_ID, U2_IOA_RUNWAY, 0xb पूर्ण, /* U2 */
	अणु HPHW_IOA, HVERSION_REV_ANY_ID, UTURN_IOA_RUNWAY, 0xb पूर्ण, /* UTurn */
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक ccio_probe(काष्ठा parisc_device *dev);

अटल काष्ठा parisc_driver ccio_driver __refdata = अणु
	.name =		"ccio",
	.id_table =	ccio_tbl,
	.probe =	ccio_probe,
पूर्ण;

/**
 * ccio_ioc_init - Initialize the I/O Controller
 * @ioc: The I/O Controller.
 *
 * Initialize the I/O Controller which includes setting up the
 * I/O Page Directory, the resource map, and initalizing the
 * U2/Uturn chip पूर्णांकo भव mode.
 */
अटल व्योम __init
ccio_ioc_init(काष्ठा ioc *ioc)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक iov_order;
	u32 iova_space_size;

	/*
	** Determine IOVA Space size from memory size.
	**
	** Ideally, PCI drivers would रेजिस्टर the maximum number
	** of DMA they can have outstanding क्रम each device they
	** own.  Next best thing would be to guess how much DMA
	** can be outstanding based on PCI Class/sub-class. Both
	** methods still require some "extra" to support PCI
	** Hot-Plug/Removal of PCI cards. (aka PCI OLARD).
	*/

	iova_space_size = (u32) (totalram_pages() / count_parisc_driver(&ccio_driver));

	/* limit IOVA space size to 1MB-1GB */

	अगर (iova_space_size < (1 << (20 - PAGE_SHIFT))) अणु
		iova_space_size =  1 << (20 - PAGE_SHIFT);
#अगर_घोषित __LP64__
	पूर्ण अन्यथा अगर (iova_space_size > (1 << (30 - PAGE_SHIFT))) अणु
		iova_space_size =  1 << (30 - PAGE_SHIFT);
#पूर्ण_अगर
	पूर्ण

	/*
	** iova space must be log2() in size.
	** thus, pdir/res_map will also be log2().
	*/

	/* We could use larger page sizes in order to *decrease* the number
	** of mappings needed.  (ie 8k pages means 1/2 the mappings).
	**
	** Note: Grant Grunder says "Using 8k I/O pages isn't trivial either
	**   since the pages must also be physically contiguous - typically
	**   this is the हाल under linux."
	*/

	iov_order = get_order(iova_space_size << PAGE_SHIFT);

	/* iova_space_size is now bytes, not pages */
	iova_space_size = 1 << (iov_order + PAGE_SHIFT);

	ioc->pdir_size = (iova_space_size / IOVP_SIZE) * माप(u64);

	BUG_ON(ioc->pdir_size > 8 * 1024 * 1024);   /* max pdir size <= 8MB */

	/* Verअगरy it's a घातer of two */
	BUG_ON((1 << get_order(ioc->pdir_size)) != (ioc->pdir_size >> PAGE_SHIFT));

	DBG_INIT("%s() hpa 0x%p mem %luMB IOV %dMB (%d bits)\n",
			__func__, ioc->ioc_regs,
			(अचिन्हित दीर्घ) totalram_pages() >> (20 - PAGE_SHIFT),
			iova_space_size>>20,
			iov_order + PAGE_SHIFT);

	ioc->pdir_base = (u64 *)__get_मुक्त_pages(GFP_KERNEL, 
						 get_order(ioc->pdir_size));
	अगर(शून्य == ioc->pdir_base) अणु
		panic("%s() could not allocate I/O Page Table\n", __func__);
	पूर्ण
	स_रखो(ioc->pdir_base, 0, ioc->pdir_size);

	BUG_ON((((अचिन्हित दीर्घ)ioc->pdir_base) & PAGE_MASK) != (अचिन्हित दीर्घ)ioc->pdir_base);
	DBG_INIT(" base %p\n", ioc->pdir_base);

	/* resource map size dictated by pdir_size */
 	ioc->res_size = (ioc->pdir_size / माप(u64)) >> 3;
	DBG_INIT("%s() res_size 0x%x\n", __func__, ioc->res_size);
	
	ioc->res_map = (u8 *)__get_मुक्त_pages(GFP_KERNEL, 
					      get_order(ioc->res_size));
	अगर(शून्य == ioc->res_map) अणु
		panic("%s() could not allocate resource map\n", __func__);
	पूर्ण
	स_रखो(ioc->res_map, 0, ioc->res_size);

	/* Initialize the res_hपूर्णांक to 16 */
	ioc->res_hपूर्णांक = 16;

	/* Initialize the spinlock */
	spin_lock_init(&ioc->res_lock);

	/*
	** Chainid is the upper most bits of an IOVP used to determine
	** which TLB entry an IOVP will use.
	*/
	ioc->chainid_shअगरt = get_order(iova_space_size) + PAGE_SHIFT - CCIO_CHAINID_SHIFT;
	DBG_INIT(" chainid_shift 0x%x\n", ioc->chainid_shअगरt);

	/*
	** Initialize IOA hardware
	*/
	WRITE_U32(CCIO_CHAINID_MASK << ioc->chainid_shअगरt, 
		  &ioc->ioc_regs->io_chain_id_mask);

	WRITE_U32(virt_to_phys(ioc->pdir_base), 
		  &ioc->ioc_regs->io_pdir_base);

	/*
	** Go to "Virtual Mode"
	*/
	WRITE_U32(IOA_NORMAL_MODE, &ioc->ioc_regs->io_control);

	/*
	** Initialize all I/O TLB entries to 0 (Valid bit off).
	*/
	WRITE_U32(0, &ioc->ioc_regs->io_tlb_entry_m);
	WRITE_U32(0, &ioc->ioc_regs->io_tlb_entry_l);

	क्रम(i = 1 << CCIO_CHAINID_SHIFT; i ; i--) अणु
		WRITE_U32((CMD_TLB_सूचीECT_WRITE | (i << ioc->chainid_shअगरt)),
			  &ioc->ioc_regs->io_command);
	पूर्ण
पूर्ण

अटल व्योम __init
ccio_init_resource(काष्ठा resource *res, अक्षर *name, व्योम __iomem *ioaddr)
अणु
	पूर्णांक result;

	res->parent = शून्य;
	res->flags = IORESOURCE_MEM;
	/*
	 * bracing ((चिन्हित) ...) are required क्रम 64bit kernel because
	 * we only want to sign extend the lower 16 bits of the रेजिस्टर.
	 * The upper 16-bits of range रेजिस्टरs are hardcoded to 0xffff.
	 */
	res->start = (अचिन्हित दीर्घ)((चिन्हित) READ_U32(ioaddr) << 16);
	res->end = (अचिन्हित दीर्घ)((चिन्हित) (READ_U32(ioaddr + 4) << 16) - 1);
	res->name = name;
	/*
	 * Check अगर this MMIO range is disable
	 */
	अगर (res->end + 1 == res->start)
		वापस;

	/* On some platक्रमms (e.g. K-Class), we have alपढ़ोy रेजिस्टरed
	 * resources क्रम devices reported by firmware. Some are children
	 * of ccio.
	 * "insert" ccio ranges in the mmio hierarchy (/proc/iomem).
	 */
	result = insert_resource(&iomem_resource, res);
	अगर (result < 0) अणु
		prपूर्णांकk(KERN_ERR "%s() failed to claim CCIO bus address space (%08lx,%08lx)\n", 
			__func__, (अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end);
	पूर्ण
पूर्ण

अटल व्योम __init ccio_init_resources(काष्ठा ioc *ioc)
अणु
	काष्ठा resource *res = ioc->mmio_region;
	अक्षर *name = kदो_स्मृति(14, GFP_KERNEL);

	snम_लिखो(name, 14, "GSC Bus [%d/]", ioc->hw_path);

	ccio_init_resource(res, name, &ioc->ioc_regs->io_io_low);
	ccio_init_resource(res + 1, name, &ioc->ioc_regs->io_io_low_hv);
पूर्ण

अटल पूर्णांक new_ioc_area(काष्ठा resource *res, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ min, अचिन्हित दीर्घ max, अचिन्हित दीर्घ align)
अणु
	अगर (max <= min)
		वापस -EBUSY;

	res->start = (max - size + 1) &~ (align - 1);
	res->end = res->start + size;
	
	/* We might be trying to expand the MMIO range to include
	 * a child device that has alपढ़ोy रेजिस्टरed it's MMIO space.
	 * Use "insert" instead of request_resource().
	 */
	अगर (!insert_resource(&iomem_resource, res))
		वापस 0;

	वापस new_ioc_area(res, size, min, max - size, align);
पूर्ण

अटल पूर्णांक expand_ioc_area(काष्ठा resource *res, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ min, अचिन्हित दीर्घ max, अचिन्हित दीर्घ align)
अणु
	अचिन्हित दीर्घ start, len;

	अगर (!res->parent)
		वापस new_ioc_area(res, size, min, max, align);

	start = (res->start - size) &~ (align - 1);
	len = res->end - start + 1;
	अगर (start >= min) अणु
		अगर (!adjust_resource(res, start, len))
			वापस 0;
	पूर्ण

	start = res->start;
	len = ((size + res->end + align) &~ (align - 1)) - start;
	अगर (start + len <= max) अणु
		अगर (!adjust_resource(res, start, len))
			वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/*
 * Dino calls this function.  Beware that we may get called on प्रणालीs
 * which have no IOC (725, B180, C160L, etc) but करो have a Dino.
 * So it's legal to find no parent IOC.
 *
 * Some other issues: one of the resources in the ioc may be unasचिन्हित.
 */
पूर्णांक ccio_allocate_resource(स्थिर काष्ठा parisc_device *dev,
		काष्ठा resource *res, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ min, अचिन्हित दीर्घ max, अचिन्हित दीर्घ align)
अणु
	काष्ठा resource *parent = &iomem_resource;
	काष्ठा ioc *ioc = ccio_get_iommu(dev);
	अगर (!ioc)
		जाओ out;

	parent = ioc->mmio_region;
	अगर (parent->parent &&
	    !allocate_resource(parent, res, size, min, max, align, शून्य, शून्य))
		वापस 0;

	अगर ((parent + 1)->parent &&
	    !allocate_resource(parent + 1, res, size, min, max, align,
				शून्य, शून्य))
		वापस 0;

	अगर (!expand_ioc_area(parent, size, min, max, align)) अणु
		__raw_ग_लिखोl(((parent->start)>>16) | 0xffff0000,
			     &ioc->ioc_regs->io_io_low);
		__raw_ग_लिखोl(((parent->end)>>16) | 0xffff0000,
			     &ioc->ioc_regs->io_io_high);
	पूर्ण अन्यथा अगर (!expand_ioc_area(parent + 1, size, min, max, align)) अणु
		parent++;
		__raw_ग_लिखोl(((parent->start)>>16) | 0xffff0000,
			     &ioc->ioc_regs->io_io_low_hv);
		__raw_ग_लिखोl(((parent->end)>>16) | 0xffff0000,
			     &ioc->ioc_regs->io_io_high_hv);
	पूर्ण अन्यथा अणु
		वापस -EBUSY;
	पूर्ण

 out:
	वापस allocate_resource(parent, res, size, min, max, align, शून्य,शून्य);
पूर्ण

पूर्णांक ccio_request_resource(स्थिर काष्ठा parisc_device *dev,
		काष्ठा resource *res)
अणु
	काष्ठा resource *parent;
	काष्ठा ioc *ioc = ccio_get_iommu(dev);

	अगर (!ioc) अणु
		parent = &iomem_resource;
	पूर्ण अन्यथा अगर ((ioc->mmio_region->start <= res->start) &&
			(res->end <= ioc->mmio_region->end)) अणु
		parent = ioc->mmio_region;
	पूर्ण अन्यथा अगर (((ioc->mmio_region + 1)->start <= res->start) &&
			(res->end <= (ioc->mmio_region + 1)->end)) अणु
		parent = ioc->mmio_region + 1;
	पूर्ण अन्यथा अणु
		वापस -EBUSY;
	पूर्ण

	/* "transparent" bus bridges need to रेजिस्टर MMIO resources
	 * firmware asचिन्हित them. e.g. children of hppb.c (e.g. K-class)
	 * रेजिस्टरed their resources in the PDC "bus walk" (See
	 * arch/parisc/kernel/inventory.c).
	 */
	वापस insert_resource(parent, res);
पूर्ण

/**
 * ccio_probe - Determine अगर ccio should claim this device.
 * @dev: The device which has been found
 *
 * Determine अगर ccio should claim this chip (वापस 0) or not (वापस 1).
 * If so, initialize the chip and tell other partners in crime they
 * have work to करो.
 */
अटल पूर्णांक __init ccio_probe(काष्ठा parisc_device *dev)
अणु
	पूर्णांक i;
	काष्ठा ioc *ioc, **ioc_p = &ioc_list;
	काष्ठा pci_hba_data *hba;

	ioc = kzalloc(माप(काष्ठा ioc), GFP_KERNEL);
	अगर (ioc == शून्य) अणु
		prपूर्णांकk(KERN_ERR MODULE_NAME ": memory allocation failure\n");
		वापस -ENOMEM;
	पूर्ण

	ioc->name = dev->id.hversion == U2_IOA_RUNWAY ? "U2" : "UTurn";

	prपूर्णांकk(KERN_INFO "Found %s at 0x%lx\n", ioc->name,
		(अचिन्हित दीर्घ)dev->hpa.start);

	क्रम (i = 0; i < ioc_count; i++) अणु
		ioc_p = &(*ioc_p)->next;
	पूर्ण
	*ioc_p = ioc;

	ioc->hw_path = dev->hw_path;
	ioc->ioc_regs = ioremap(dev->hpa.start, 4096);
	अगर (!ioc->ioc_regs) अणु
		kमुक्त(ioc);
		वापस -ENOMEM;
	पूर्ण
	ccio_ioc_init(ioc);
	ccio_init_resources(ioc);
	hppa_dma_ops = &ccio_ops;

	hba = kzalloc(माप(*hba), GFP_KERNEL);
	/* अगर this fails, no I/O cards will work, so may as well bug */
	BUG_ON(hba == शून्य);

	hba->iommu = ioc;
	dev->dev.platक्रमm_data = hba;

#अगर_घोषित CONFIG_PROC_FS
	अगर (ioc_count == 0) अणु
		proc_create_single(MODULE_NAME, 0, proc_runway_root,
				ccio_proc_info);
		proc_create_single(MODULE_NAME"-bitmap", 0, proc_runway_root,
				ccio_proc_biपंचांगap_info);
	पूर्ण
#पूर्ण_अगर
	ioc_count++;
	वापस 0;
पूर्ण

/**
 * ccio_init - ccio initialization procedure.
 *
 * Register this driver.
 */
व्योम __init ccio_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&ccio_driver);
पूर्ण

