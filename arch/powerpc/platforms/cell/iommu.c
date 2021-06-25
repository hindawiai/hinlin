<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IOMMU implementation क्रम Cell Broadband Processor Architecture
 *
 * (C) Copyright IBM Corporation 2006-2008
 *
 * Author: Jeremy Kerr <jk@ozद_असल.org>
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "cell.h"
#समावेश "interrupt.h"

/* Define CELL_IOMMU_REAL_UNMAP to actually unmap non-used pages
 * instead of leaving them mapped to some dummy page. This can be
 * enabled once the appropriate workarounds क्रम spider bugs have
 * been enabled
 */
#घोषणा CELL_IOMMU_REAL_UNMAP

/* Define CELL_IOMMU_STRICT_PROTECTION to enक्रमce protection of
 * IO PTEs based on the transfer direction. That can be enabled
 * once spider-net has been fixed to pass the correct direction
 * to the DMA mapping functions
 */
#घोषणा CELL_IOMMU_STRICT_PROTECTION


#घोषणा NR_IOMMUS			2

/* IOC mmap रेजिस्टरs */
#घोषणा IOC_Reg_Size			0x2000

#घोषणा IOC_IOPT_CacheInvd		0x908
#घोषणा IOC_IOPT_CacheInvd_NE_Mask	0xffe0000000000000ul
#घोषणा IOC_IOPT_CacheInvd_IOPTE_Mask	0x000003fffffffff8ul
#घोषणा IOC_IOPT_CacheInvd_Busy		0x0000000000000001ul

#घोषणा IOC_IOST_Origin			0x918
#घोषणा IOC_IOST_Origin_E		0x8000000000000000ul
#घोषणा IOC_IOST_Origin_HW		0x0000000000000800ul
#घोषणा IOC_IOST_Origin_HL		0x0000000000000400ul

#घोषणा IOC_IO_ExcpStat			0x920
#घोषणा IOC_IO_ExcpStat_V		0x8000000000000000ul
#घोषणा IOC_IO_ExcpStat_SPF_Mask	0x6000000000000000ul
#घोषणा IOC_IO_ExcpStat_SPF_S		0x6000000000000000ul
#घोषणा IOC_IO_ExcpStat_SPF_P		0x2000000000000000ul
#घोषणा IOC_IO_ExcpStat_ADDR_Mask	0x00000007fffff000ul
#घोषणा IOC_IO_ExcpStat_RW_Mask		0x0000000000000800ul
#घोषणा IOC_IO_ExcpStat_IOID_Mask	0x00000000000007fful

#घोषणा IOC_IO_ExcpMask			0x928
#घोषणा IOC_IO_ExcpMask_SFE		0x4000000000000000ul
#घोषणा IOC_IO_ExcpMask_PFE		0x2000000000000000ul

#घोषणा IOC_IOCmd_Offset		0x1000

#घोषणा IOC_IOCmd_Cfg			0xc00
#घोषणा IOC_IOCmd_Cfg_TE		0x0000800000000000ul


/* Segment table entries */
#घोषणा IOSTE_V			0x8000000000000000ul /* valid */
#घोषणा IOSTE_H			0x4000000000000000ul /* cache hपूर्णांक */
#घोषणा IOSTE_PT_Base_RPN_Mask  0x3ffffffffffff000ul /* base RPN of IOPT */
#घोषणा IOSTE_NPPT_Mask		0x0000000000000fe0ul /* no. pages in IOPT */
#घोषणा IOSTE_PS_Mask		0x0000000000000007ul /* page size */
#घोषणा IOSTE_PS_4K		0x0000000000000001ul /*   - 4kB  */
#घोषणा IOSTE_PS_64K		0x0000000000000003ul /*   - 64kB */
#घोषणा IOSTE_PS_1M		0x0000000000000005ul /*   - 1MB  */
#घोषणा IOSTE_PS_16M		0x0000000000000007ul /*   - 16MB */


/* IOMMU sizing */
#घोषणा IO_SEGMENT_SHIFT	28
#घोषणा IO_PAGENO_BITS(shअगरt)	(IO_SEGMENT_SHIFT - (shअगरt))

/* The high bit needs to be set on every DMA address */
#घोषणा SPIDER_DMA_OFFSET	0x80000000ul

काष्ठा iommu_winकरोw अणु
	काष्ठा list_head list;
	काष्ठा cbe_iommu *iommu;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक ioid;
	काष्ठा iommu_table table;
पूर्ण;

#घोषणा NAMESIZE 8
काष्ठा cbe_iommu अणु
	पूर्णांक nid;
	अक्षर name[NAMESIZE];
	व्योम __iomem *xlate_regs;
	व्योम __iomem *cmd_regs;
	अचिन्हित दीर्घ *stab;
	अचिन्हित दीर्घ *ptab;
	व्योम *pad_page;
	काष्ठा list_head winकरोws;
पूर्ण;

/* Static array of iommus, one per node
 *   each contains a list of winकरोws, keyed from dma_winकरोw property
 *   - on bus setup, look क्रम a matching winकरोw, or create one
 *   - on dev setup, assign iommu_table ptr
 */
अटल काष्ठा cbe_iommu iommus[NR_IOMMUS];
अटल पूर्णांक cbe_nr_iommus;

अटल व्योम invalidate_tce_cache(काष्ठा cbe_iommu *iommu, अचिन्हित दीर्घ *pte,
		दीर्घ n_ptes)
अणु
	u64 __iomem *reg;
	u64 val;
	दीर्घ n;

	reg = iommu->xlate_regs + IOC_IOPT_CacheInvd;

	जबतक (n_ptes > 0) अणु
		/* we can invalidate up to 1 << 11 PTEs at once */
		n = min(n_ptes, 1l << 11);
		val = (((n /*- 1*/) << 53) & IOC_IOPT_CacheInvd_NE_Mask)
			| (__pa(pte) & IOC_IOPT_CacheInvd_IOPTE_Mask)
		        | IOC_IOPT_CacheInvd_Busy;

		out_be64(reg, val);
		जबतक (in_be64(reg) & IOC_IOPT_CacheInvd_Busy)
			;

		n_ptes -= n;
		pte += n;
	पूर्ण
पूर्ण

अटल पूर्णांक tce_build_cell(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages,
		अचिन्हित दीर्घ uaddr, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ *io_pte, base_pte;
	काष्ठा iommu_winकरोw *winकरोw =
		container_of(tbl, काष्ठा iommu_winकरोw, table);

	/* implementing proper protection causes problems with the spidernet
	 * driver - check mapping directions later, but allow पढ़ो & ग_लिखो by
	 * शेष क्रम now.*/
#अगर_घोषित CELL_IOMMU_STRICT_PROTECTION
	/* to aव्योम referencing a global, we use a trick here to setup the
	 * protection bit. "prot" is setup to be 3 fields of 4 bits appended
	 * together क्रम each of the 3 supported direction values. It is then
	 * shअगरted left so that the fields matching the desired direction
	 * lands on the appropriate bits, and other bits are masked out.
	 */
	स्थिर अचिन्हित दीर्घ prot = 0xc48;
	base_pte =
		((prot << (52 + 4 * direction)) &
		 (CBE_IOPTE_PP_W | CBE_IOPTE_PP_R)) |
		CBE_IOPTE_M | CBE_IOPTE_SO_RW |
		(winकरोw->ioid & CBE_IOPTE_IOID_Mask);
#अन्यथा
	base_pte = CBE_IOPTE_PP_W | CBE_IOPTE_PP_R | CBE_IOPTE_M |
		CBE_IOPTE_SO_RW | (winकरोw->ioid & CBE_IOPTE_IOID_Mask);
#पूर्ण_अगर
	अगर (unlikely(attrs & DMA_ATTR_WEAK_ORDERING))
		base_pte &= ~CBE_IOPTE_SO_RW;

	io_pte = (अचिन्हित दीर्घ *)tbl->it_base + (index - tbl->it_offset);

	क्रम (i = 0; i < npages; i++, uaddr += (1 << tbl->it_page_shअगरt))
		io_pte[i] = base_pte | (__pa(uaddr) & CBE_IOPTE_RPN_Mask);

	mb();

	invalidate_tce_cache(winकरोw->iommu, io_pte, npages);

	pr_debug("tce_build_cell(index=%lx,n=%lx,dir=%d,base_pte=%lx)\n",
		 index, npages, direction, base_pte);
	वापस 0;
पूर्ण

अटल व्योम tce_मुक्त_cell(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages)
अणु

	पूर्णांक i;
	अचिन्हित दीर्घ *io_pte, pte;
	काष्ठा iommu_winकरोw *winकरोw =
		container_of(tbl, काष्ठा iommu_winकरोw, table);

	pr_debug("tce_free_cell(index=%lx,n=%lx)\n", index, npages);

#अगर_घोषित CELL_IOMMU_REAL_UNMAP
	pte = 0;
#अन्यथा
	/* spider bridge करोes PCI पढ़ोs after मुक्तing - insert a mapping
	 * to a scratch page instead of an invalid entry */
	pte = CBE_IOPTE_PP_R | CBE_IOPTE_M | CBE_IOPTE_SO_RW |
		__pa(winकरोw->iommu->pad_page) |
		(winकरोw->ioid & CBE_IOPTE_IOID_Mask);
#पूर्ण_अगर

	io_pte = (अचिन्हित दीर्घ *)tbl->it_base + (index - tbl->it_offset);

	क्रम (i = 0; i < npages; i++)
		io_pte[i] = pte;

	mb();

	invalidate_tce_cache(winकरोw->iommu, io_pte, npages);
पूर्ण

अटल irqवापस_t ioc_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ stat, spf;
	काष्ठा cbe_iommu *iommu = data;

	stat = in_be64(iommu->xlate_regs + IOC_IO_ExcpStat);
	spf = stat & IOC_IO_ExcpStat_SPF_Mask;

	/* Might want to rate limit it */
	prपूर्णांकk(KERN_ERR "iommu: DMA exception 0x%016lx\n", stat);
	prपूर्णांकk(KERN_ERR "  V=%d, SPF=[%c%c], RW=%s, IOID=0x%04x\n",
	       !!(stat & IOC_IO_ExcpStat_V),
	       (spf == IOC_IO_ExcpStat_SPF_S) ? 'S' : ' ',
	       (spf == IOC_IO_ExcpStat_SPF_P) ? 'P' : ' ',
	       (stat & IOC_IO_ExcpStat_RW_Mask) ? "Read" : "Write",
	       (अचिन्हित पूर्णांक)(stat & IOC_IO_ExcpStat_IOID_Mask));
	prपूर्णांकk(KERN_ERR "  page=0x%016lx\n",
	       stat & IOC_IO_ExcpStat_ADDR_Mask);

	/* clear पूर्णांकerrupt */
	stat &= ~IOC_IO_ExcpStat_V;
	out_be64(iommu->xlate_regs + IOC_IO_ExcpStat, stat);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cell_iommu_find_ioc(पूर्णांक nid, अचिन्हित दीर्घ *base)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;

	*base = 0;

	/* First look क्रम new style /be nodes */
	क्रम_each_node_by_name(np, "ioc") अणु
		अगर (of_node_to_nid(np) != nid)
			जारी;
		अगर (of_address_to_resource(np, 0, &r)) अणु
			prपूर्णांकk(KERN_ERR "iommu: can't get address for %pOF\n",
			       np);
			जारी;
		पूर्ण
		*base = r.start;
		of_node_put(np);
		वापस 0;
	पूर्ण

	/* Ok, let's try the old way */
	क्रम_each_node_by_type(np, "cpu") अणु
		स्थिर अचिन्हित पूर्णांक *nidp;
		स्थिर अचिन्हित दीर्घ *पंचांगp;

		nidp = of_get_property(np, "node-id", शून्य);
		अगर (nidp && *nidp == nid) अणु
			पंचांगp = of_get_property(np, "ioc-translation", शून्य);
			अगर (पंचांगp) अणु
				*base = *पंचांगp;
				of_node_put(np);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम cell_iommu_setup_stab(काष्ठा cbe_iommu *iommu,
				अचिन्हित दीर्घ dbase, अचिन्हित दीर्घ dsize,
				अचिन्हित दीर्घ fbase, अचिन्हित दीर्घ fsize)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ segments, stab_size;

	segments = max(dbase + dsize, fbase + fsize) >> IO_SEGMENT_SHIFT;

	pr_debug("%s: iommu[%d]: segments: %lu\n",
			__func__, iommu->nid, segments);

	/* set up the segment table */
	stab_size = segments * माप(अचिन्हित दीर्घ);
	page = alloc_pages_node(iommu->nid, GFP_KERNEL, get_order(stab_size));
	BUG_ON(!page);
	iommu->stab = page_address(page);
	स_रखो(iommu->stab, 0, stab_size);
पूर्ण

अटल अचिन्हित दीर्घ *cell_iommu_alloc_ptab(काष्ठा cbe_iommu *iommu,
		अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, अचिन्हित दीर्घ gap_base,
		अचिन्हित दीर्घ gap_size, अचिन्हित दीर्घ page_shअगरt)
अणु
	काष्ठा page *page;
	पूर्णांक i;
	अचिन्हित दीर्घ reg, segments, pages_per_segment, ptab_size,
		      n_pte_pages, start_seg, *ptab;

	start_seg = base >> IO_SEGMENT_SHIFT;
	segments  = size >> IO_SEGMENT_SHIFT;
	pages_per_segment = 1ull << IO_PAGENO_BITS(page_shअगरt);
	/* PTEs क्रम each segment must start on a 4K boundary */
	pages_per_segment = max(pages_per_segment,
				(1 << 12) / माप(अचिन्हित दीर्घ));

	ptab_size = segments * pages_per_segment * माप(अचिन्हित दीर्घ);
	pr_debug("%s: iommu[%d]: ptab_size: %lu, order: %d\n", __func__,
			iommu->nid, ptab_size, get_order(ptab_size));
	page = alloc_pages_node(iommu->nid, GFP_KERNEL, get_order(ptab_size));
	BUG_ON(!page);

	ptab = page_address(page);
	स_रखो(ptab, 0, ptab_size);

	/* number of 4K pages needed क्रम a page table */
	n_pte_pages = (pages_per_segment * माप(अचिन्हित दीर्घ)) >> 12;

	pr_debug("%s: iommu[%d]: stab at %p, ptab at %p, n_pte_pages: %lu\n",
			__func__, iommu->nid, iommu->stab, ptab,
			n_pte_pages);

	/* initialise the STEs */
	reg = IOSTE_V | ((n_pte_pages - 1) << 5);

	चयन (page_shअगरt) अणु
	हाल 12: reg |= IOSTE_PS_4K;  अवरोध;
	हाल 16: reg |= IOSTE_PS_64K; अवरोध;
	हाल 20: reg |= IOSTE_PS_1M;  अवरोध;
	हाल 24: reg |= IOSTE_PS_16M; अवरोध;
	शेष: BUG();
	पूर्ण

	gap_base = gap_base >> IO_SEGMENT_SHIFT;
	gap_size = gap_size >> IO_SEGMENT_SHIFT;

	pr_debug("Setting up IOMMU stab:\n");
	क्रम (i = start_seg; i < (start_seg + segments); i++) अणु
		अगर (i >= gap_base && i < (gap_base + gap_size)) अणु
			pr_debug("\toverlap at %d, skipping\n", i);
			जारी;
		पूर्ण
		iommu->stab[i] = reg | (__pa(ptab) + (n_pte_pages << 12) *
					(i - start_seg));
		pr_debug("\t[%d] 0x%016lx\n", i, iommu->stab[i]);
	पूर्ण

	वापस ptab;
पूर्ण

अटल व्योम cell_iommu_enable_hardware(काष्ठा cbe_iommu *iommu)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ reg, xlate_base;
	अचिन्हित पूर्णांक virq;

	अगर (cell_iommu_find_ioc(iommu->nid, &xlate_base))
		panic("%s: missing IOC register mappings for node %d\n",
		      __func__, iommu->nid);

	iommu->xlate_regs = ioremap(xlate_base, IOC_Reg_Size);
	iommu->cmd_regs = iommu->xlate_regs + IOC_IOCmd_Offset;

	/* ensure that the STEs have updated */
	mb();

	/* setup पूर्णांकerrupts क्रम the iommu. */
	reg = in_be64(iommu->xlate_regs + IOC_IO_ExcpStat);
	out_be64(iommu->xlate_regs + IOC_IO_ExcpStat,
			reg & ~IOC_IO_ExcpStat_V);
	out_be64(iommu->xlate_regs + IOC_IO_ExcpMask,
			IOC_IO_ExcpMask_PFE | IOC_IO_ExcpMask_SFE);

	virq = irq_create_mapping(शून्य,
			IIC_IRQ_IOEX_ATI | (iommu->nid << IIC_IRQ_NODE_SHIFT));
	BUG_ON(!virq);

	ret = request_irq(virq, ioc_पूर्णांकerrupt, 0, iommu->name, iommu);
	BUG_ON(ret);

	/* set the IOC segment table origin रेजिस्टर (and turn on the iommu) */
	reg = IOC_IOST_Origin_E | __pa(iommu->stab) | IOC_IOST_Origin_HW;
	out_be64(iommu->xlate_regs + IOC_IOST_Origin, reg);
	in_be64(iommu->xlate_regs + IOC_IOST_Origin);

	/* turn on IO translation */
	reg = in_be64(iommu->cmd_regs + IOC_IOCmd_Cfg) | IOC_IOCmd_Cfg_TE;
	out_be64(iommu->cmd_regs + IOC_IOCmd_Cfg, reg);
पूर्ण

अटल व्योम cell_iommu_setup_hardware(काष्ठा cbe_iommu *iommu,
	अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	cell_iommu_setup_stab(iommu, base, size, 0, 0);
	iommu->ptab = cell_iommu_alloc_ptab(iommu, base, size, 0, 0,
					    IOMMU_PAGE_SHIFT_4K);
	cell_iommu_enable_hardware(iommu);
पूर्ण

#अगर 0/* Unused क्रम now */
अटल काष्ठा iommu_winकरोw *find_winकरोw(काष्ठा cbe_iommu *iommu,
		अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	काष्ठा iommu_winकरोw *winकरोw;

	/* toकरो: check क्रम overlapping (but not equal) winकरोws) */

	list_क्रम_each_entry(winकरोw, &(iommu->winकरोws), list) अणु
		अगर (winकरोw->offset == offset && winकरोw->size == size)
			वापस winकरोw;
	पूर्ण

	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 cell_iommu_get_ioid(काष्ठा device_node *np)
अणु
	स्थिर u32 *ioid;

	ioid = of_get_property(np, "ioid", शून्य);
	अगर (ioid == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "iommu: missing ioid for %pOF using 0\n",
		       np);
		वापस 0;
	पूर्ण

	वापस *ioid;
पूर्ण

अटल काष्ठा iommu_table_ops cell_iommu_ops = अणु
	.set = tce_build_cell,
	.clear = tce_मुक्त_cell
पूर्ण;

अटल काष्ठा iommu_winकरोw * __init
cell_iommu_setup_winकरोw(काष्ठा cbe_iommu *iommu, काष्ठा device_node *np,
			अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
			अचिन्हित दीर्घ pte_offset)
अणु
	काष्ठा iommu_winकरोw *winकरोw;
	काष्ठा page *page;
	u32 ioid;

	ioid = cell_iommu_get_ioid(np);

	winकरोw = kzalloc_node(माप(*winकरोw), GFP_KERNEL, iommu->nid);
	BUG_ON(winकरोw == शून्य);

	winकरोw->offset = offset;
	winकरोw->size = size;
	winकरोw->ioid = ioid;
	winकरोw->iommu = iommu;

	winकरोw->table.it_blocksize = 16;
	winकरोw->table.it_base = (अचिन्हित दीर्घ)iommu->ptab;
	winकरोw->table.it_index = iommu->nid;
	winकरोw->table.it_page_shअगरt = IOMMU_PAGE_SHIFT_4K;
	winकरोw->table.it_offset =
		(offset >> winकरोw->table.it_page_shअगरt) + pte_offset;
	winकरोw->table.it_size = size >> winकरोw->table.it_page_shअगरt;
	winकरोw->table.it_ops = &cell_iommu_ops;

	अगर (!iommu_init_table(&winकरोw->table, iommu->nid, 0, 0))
		panic("Failed to initialize iommu table");

	pr_debug("\tioid      %d\n", winकरोw->ioid);
	pr_debug("\tblocksize %ld\n", winकरोw->table.it_blocksize);
	pr_debug("\tbase      0x%016lx\n", winकरोw->table.it_base);
	pr_debug("\toffset    0x%lx\n", winकरोw->table.it_offset);
	pr_debug("\tsize      %ld\n", winकरोw->table.it_size);

	list_add(&winकरोw->list, &iommu->winकरोws);

	अगर (offset != 0)
		वापस winकरोw;

	/* We need to map and reserve the first IOMMU page since it's used
	 * by the spider workaround. In theory, we only need to करो that when
	 * running on spider but it करोesn't really matter.
	 *
	 * This code also assumes that we have a winकरोw that starts at 0,
	 * which is the हाल on all spider based blades.
	 */
	page = alloc_pages_node(iommu->nid, GFP_KERNEL, 0);
	BUG_ON(!page);
	iommu->pad_page = page_address(page);
	clear_page(iommu->pad_page);

	__set_bit(0, winकरोw->table.it_map);
	tce_build_cell(&winकरोw->table, winकरोw->table.it_offset, 1,
		       (अचिन्हित दीर्घ)iommu->pad_page, DMA_TO_DEVICE, 0);

	वापस winकरोw;
पूर्ण

अटल काष्ठा cbe_iommu *cell_iommu_क्रम_node(पूर्णांक nid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cbe_nr_iommus; i++)
		अगर (iommus[i].nid == nid)
			वापस &iommus[i];
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ cell_dma_nommu_offset;

अटल अचिन्हित दीर्घ dma_iommu_fixed_base;
अटल bool cell_iommu_enabled;

/* iommu_fixed_is_weak is set अगर booted with iommu_fixed=weak */
bool iommu_fixed_is_weak;

अटल काष्ठा iommu_table *cell_get_iommu_table(काष्ठा device *dev)
अणु
	काष्ठा iommu_winकरोw *winकरोw;
	काष्ठा cbe_iommu *iommu;

	/* Current implementation uses the first winकरोw available in that
	 * node's iommu. We -might- करो something smarter later though it may
	 * never be necessary
	 */
	iommu = cell_iommu_क्रम_node(dev_to_node(dev));
	अगर (iommu == शून्य || list_empty(&iommu->winकरोws)) अणु
		dev_err(dev, "iommu: missing iommu for %pOF (node %d)\n",
		       dev->of_node, dev_to_node(dev));
		वापस शून्य;
	पूर्ण
	winकरोw = list_entry(iommu->winकरोws.next, काष्ठा iommu_winकरोw, list);

	वापस &winकरोw->table;
पूर्ण

अटल u64 cell_iommu_get_fixed_address(काष्ठा device *dev);

अटल व्योम cell_dma_dev_setup(काष्ठा device *dev)
अणु
	अगर (cell_iommu_enabled) अणु
		u64 addr = cell_iommu_get_fixed_address(dev);

		अगर (addr != OF_BAD_ADDR)
			dev->archdata.dma_offset = addr + dma_iommu_fixed_base;
		set_iommu_table_base(dev, cell_get_iommu_table(dev));
	पूर्ण अन्यथा अणु
		dev->archdata.dma_offset = cell_dma_nommu_offset;
	पूर्ण
पूर्ण

अटल व्योम cell_pci_dma_dev_setup(काष्ठा pci_dev *dev)
अणु
	cell_dma_dev_setup(&dev->dev);
पूर्ण

अटल पूर्णांक cell_of_bus_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	काष्ठा device *dev = data;

	/* We are only पूर्णांकereted in device addition */
	अगर (action != BUS_NOTIFY_ADD_DEVICE)
		वापस 0;

	अगर (cell_iommu_enabled)
		dev->dma_ops = &dma_iommu_ops;
	cell_dma_dev_setup(dev);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block cell_of_bus_notअगरier = अणु
	.notअगरier_call = cell_of_bus_notअगरy
पूर्ण;

अटल पूर्णांक __init cell_iommu_get_winकरोw(काष्ठा device_node *np,
					 अचिन्हित दीर्घ *base,
					 अचिन्हित दीर्घ *size)
अणु
	स्थिर __be32 *dma_winकरोw;
	अचिन्हित दीर्घ index;

	/* Use ibm,dma-winकरोw अगर available, अन्यथा, hard code ! */
	dma_winकरोw = of_get_property(np, "ibm,dma-window", शून्य);
	अगर (dma_winकरोw == शून्य) अणु
		*base = 0;
		*size = 0x80000000u;
		वापस -ENODEV;
	पूर्ण

	of_parse_dma_winकरोw(np, dma_winकरोw, &index, base, size);
	वापस 0;
पूर्ण

अटल काष्ठा cbe_iommu * __init cell_iommu_alloc(काष्ठा device_node *np)
अणु
	काष्ठा cbe_iommu *iommu;
	पूर्णांक nid, i;

	/* Get node ID */
	nid = of_node_to_nid(np);
	अगर (nid < 0) अणु
		prपूर्णांकk(KERN_ERR "iommu: failed to get node for %pOF\n",
		       np);
		वापस शून्य;
	पूर्ण
	pr_debug("iommu: setting up iommu for node %d (%pOF)\n",
		 nid, np);

	/* XXX toकरो: If we can have multiple winकरोws on the same IOMMU, which
	 * isn't the हाल today, we probably want here to check whether the
	 * iommu क्रम that node is alपढ़ोy setup.
	 * However, there might be issue with getting the size right so let's
	 * ignore that क्रम now. We might want to completely get rid of the
	 * multiple winकरोw support since the cell iommu supports per-page ioids
	 */

	अगर (cbe_nr_iommus >= NR_IOMMUS) अणु
		prपूर्णांकk(KERN_ERR "iommu: too many IOMMUs detected ! (%pOF)\n",
		       np);
		वापस शून्य;
	पूर्ण

	/* Init base fields */
	i = cbe_nr_iommus++;
	iommu = &iommus[i];
	iommu->stab = शून्य;
	iommu->nid = nid;
	snम_लिखो(iommu->name, माप(iommu->name), "iommu%d", i);
	INIT_LIST_HEAD(&iommu->winकरोws);

	वापस iommu;
पूर्ण

अटल व्योम __init cell_iommu_init_one(काष्ठा device_node *np,
				       अचिन्हित दीर्घ offset)
अणु
	काष्ठा cbe_iommu *iommu;
	अचिन्हित दीर्घ base, size;

	iommu = cell_iommu_alloc(np);
	अगर (!iommu)
		वापस;

	/* Obtain a winकरोw क्रम it */
	cell_iommu_get_winकरोw(np, &base, &size);

	pr_debug("\ttranslating window 0x%lx...0x%lx\n",
		 base, base + size - 1);

	/* Initialize the hardware */
	cell_iommu_setup_hardware(iommu, base, size);

	/* Setup the iommu_table */
	cell_iommu_setup_winकरोw(iommu, np, base, size,
				offset >> IOMMU_PAGE_SHIFT_4K);
पूर्ण

अटल व्योम __init cell_disable_iommus(व्योम)
अणु
	पूर्णांक node;
	अचिन्हित दीर्घ base, val;
	व्योम __iomem *xregs, *cregs;

	/* Make sure IOC translation is disabled on all nodes */
	क्रम_each_online_node(node) अणु
		अगर (cell_iommu_find_ioc(node, &base))
			जारी;
		xregs = ioremap(base, IOC_Reg_Size);
		अगर (xregs == शून्य)
			जारी;
		cregs = xregs + IOC_IOCmd_Offset;

		pr_debug("iommu: cleaning up iommu on node %d\n", node);

		out_be64(xregs + IOC_IOST_Origin, 0);
		(व्योम)in_be64(xregs + IOC_IOST_Origin);
		val = in_be64(cregs + IOC_IOCmd_Cfg);
		val &= ~IOC_IOCmd_Cfg_TE;
		out_be64(cregs + IOC_IOCmd_Cfg, val);
		(व्योम)in_be64(cregs + IOC_IOCmd_Cfg);

		iounmap(xregs);
	पूर्ण
पूर्ण

अटल पूर्णांक __init cell_iommu_init_disabled(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	अचिन्हित दीर्घ base = 0, size;

	/* When no iommu is present, we use direct DMA ops */

	/* First make sure all IOC translation is turned off */
	cell_disable_iommus();

	/* If we have no Axon, we set up the spider DMA magic offset */
	अगर (of_find_node_by_name(शून्य, "axon") == शून्य)
		cell_dma_nommu_offset = SPIDER_DMA_OFFSET;

	/* Now we need to check to see where the memory is mapped
	 * in PCI space. We assume that all busses use the same dma
	 * winकरोw which is always the हाल so far on Cell, thus we
	 * pick up the first pci-पूर्णांकernal node we can find and check
	 * the DMA winकरोw from there.
	 */
	क्रम_each_node_by_name(np, "axon") अणु
		अगर (np->parent == शून्य || np->parent->parent != शून्य)
			जारी;
		अगर (cell_iommu_get_winकरोw(np, &base, &size) == 0)
			अवरोध;
	पूर्ण
	अगर (np == शून्य) अणु
		क्रम_each_node_by_name(np, "pci-internal") अणु
			अगर (np->parent == शून्य || np->parent->parent != शून्य)
				जारी;
			अगर (cell_iommu_get_winकरोw(np, &base, &size) == 0)
				अवरोध;
		पूर्ण
	पूर्ण
	of_node_put(np);

	/* If we found a DMA winकरोw, we check अगर it's big enough to enबंद
	 * all of physical memory. If not, we क्रमce enable IOMMU
	 */
	अगर (np && size < memblock_end_of_DRAM()) अणु
		prपूर्णांकk(KERN_WARNING "iommu: force-enabled, dma window"
		       " (%ldMB) smaller than total memory (%lldMB)\n",
		       size >> 20, memblock_end_of_DRAM() >> 20);
		वापस -ENODEV;
	पूर्ण

	cell_dma_nommu_offset += base;

	अगर (cell_dma_nommu_offset != 0)
		cell_pci_controller_ops.dma_dev_setup = cell_pci_dma_dev_setup;

	prपूर्णांकk("iommu: disabled, direct DMA offset is 0x%lx\n",
	       cell_dma_nommu_offset);

	वापस 0;
पूर्ण

/*
 *  Fixed IOMMU mapping support
 *
 *  This code adds support क्रम setting up a fixed IOMMU mapping on certain
 *  cell machines. For 64-bit devices this aव्योमs the perक्रमmance overhead of
 *  mapping and unmapping pages at runसमय. 32-bit devices are unable to use
 *  the fixed mapping.
 *
 *  The fixed mapping is established at boot, and maps all of physical memory
 *  1:1 पूर्णांकo device space at some offset. On machines with < 30 GB of memory
 *  we setup the fixed mapping immediately above the normal IOMMU winकरोw.
 *
 *  For example a machine with 4GB of memory would end up with the normal
 *  IOMMU winकरोw from 0-2GB and the fixed mapping winकरोw from 2GB to 6GB. In
 *  this हाल a 64-bit device wishing to DMA to 1GB would be told to DMA to
 *  3GB, plus any offset required by firmware. The firmware offset is encoded
 *  in the "dma-ranges" property.
 *
 *  On machines with 30GB or more of memory, we are unable to place the fixed
 *  mapping above the normal IOMMU winकरोw as we would run out of address space.
 *  Instead we move the normal IOMMU winकरोw to coincide with the hash page
 *  table, this region करोes not need to be part of the fixed mapping as no
 *  device should ever be DMA'ing to it. We then setup the fixed mapping
 *  from 0 to 32GB.
 */

अटल u64 cell_iommu_get_fixed_address(काष्ठा device *dev)
अणु
	u64 cpu_addr, size, best_size, dev_addr = OF_BAD_ADDR;
	काष्ठा device_node *np;
	स्थिर u32 *ranges = शून्य;
	पूर्णांक i, len, best, naddr, nsize, pna, range_size;

	/* We can be called क्रम platक्रमm devices that have no of_node */
	np = of_node_get(dev->of_node);
	अगर (!np)
		जाओ out;

	जबतक (1) अणु
		naddr = of_n_addr_cells(np);
		nsize = of_n_size_cells(np);
		np = of_get_next_parent(np);
		अगर (!np)
			अवरोध;

		ranges = of_get_property(np, "dma-ranges", &len);

		/* Ignore empty ranges, they imply no translation required */
		अगर (ranges && len > 0)
			अवरोध;
	पूर्ण

	अगर (!ranges) अणु
		dev_dbg(dev, "iommu: no dma-ranges found\n");
		जाओ out;
	पूर्ण

	len /= माप(u32);

	pna = of_n_addr_cells(np);
	range_size = naddr + nsize + pna;

	/* dma-ranges क्रमmat:
	 * child addr	: naddr cells
	 * parent addr	: pna cells
	 * size		: nsize cells
	 */
	क्रम (i = 0, best = -1, best_size = 0; i < len; i += range_size) अणु
		cpu_addr = of_translate_dma_address(np, ranges + i + naddr);
		size = of_पढ़ो_number(ranges + i + naddr + pna, nsize);

		अगर (cpu_addr == 0 && size > best_size) अणु
			best = i;
			best_size = size;
		पूर्ण
	पूर्ण

	अगर (best >= 0) अणु
		dev_addr = of_पढ़ो_number(ranges + best, naddr);
	पूर्ण अन्यथा
		dev_dbg(dev, "iommu: no suitable range found!\n");

out:
	of_node_put(np);

	वापस dev_addr;
पूर्ण

अटल bool cell_pci_iommu_bypass_supported(काष्ठा pci_dev *pdev, u64 mask)
अणु
	वापस mask == DMA_BIT_MASK(64) &&
		cell_iommu_get_fixed_address(&pdev->dev) != OF_BAD_ADDR;
पूर्ण

अटल व्योम insert_16M_pte(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *ptab,
			   अचिन्हित दीर्घ base_pte)
अणु
	अचिन्हित दीर्घ segment, offset;

	segment = addr >> IO_SEGMENT_SHIFT;
	offset = (addr >> 24) - (segment << IO_PAGENO_BITS(24));
	ptab = ptab + (segment * (1 << 12) / माप(अचिन्हित दीर्घ));

	pr_debug("iommu: addr %lx ptab %p segment %lx offset %lx\n",
		  addr, ptab, segment, offset);

	ptab[offset] = base_pte | (__pa(addr) & CBE_IOPTE_RPN_Mask);
पूर्ण

अटल व्योम cell_iommu_setup_fixed_ptab(काष्ठा cbe_iommu *iommu,
	काष्ठा device_node *np, अचिन्हित दीर्घ dbase, अचिन्हित दीर्घ dsize,
	अचिन्हित दीर्घ fbase, अचिन्हित दीर्घ fsize)
अणु
	अचिन्हित दीर्घ base_pte, uaddr, ioaddr, *ptab;

	ptab = cell_iommu_alloc_ptab(iommu, fbase, fsize, dbase, dsize, 24);

	dma_iommu_fixed_base = fbase;

	pr_debug("iommu: mapping 0x%lx pages from 0x%lx\n", fsize, fbase);

	base_pte = CBE_IOPTE_PP_W | CBE_IOPTE_PP_R | CBE_IOPTE_M |
		(cell_iommu_get_ioid(np) & CBE_IOPTE_IOID_Mask);

	अगर (iommu_fixed_is_weak)
		pr_info("IOMMU: Using weak ordering for fixed mapping\n");
	अन्यथा अणु
		pr_info("IOMMU: Using strong ordering for fixed mapping\n");
		base_pte |= CBE_IOPTE_SO_RW;
	पूर्ण

	क्रम (uaddr = 0; uaddr < fsize; uaddr += (1 << 24)) अणु
		/* Don't touch the dynamic region */
		ioaddr = uaddr + fbase;
		अगर (ioaddr >= dbase && ioaddr < (dbase + dsize)) अणु
			pr_debug("iommu: fixed/dynamic overlap, skipping\n");
			जारी;
		पूर्ण

		insert_16M_pte(uaddr, ptab, base_pte);
	पूर्ण

	mb();
पूर्ण

अटल पूर्णांक __init cell_iommu_fixed_mapping_init(व्योम)
अणु
	अचिन्हित दीर्घ dbase, dsize, fbase, fsize, hbase, hend;
	काष्ठा cbe_iommu *iommu;
	काष्ठा device_node *np;

	/* The fixed mapping is only supported on axon machines */
	np = of_find_node_by_name(शून्य, "axon");
	of_node_put(np);

	अगर (!np) अणु
		pr_debug("iommu: fixed mapping disabled, no axons found\n");
		वापस -1;
	पूर्ण

	/* We must have dma-ranges properties क्रम fixed mapping to work */
	np = of_find_node_with_property(शून्य, "dma-ranges");
	of_node_put(np);

	अगर (!np) अणु
		pr_debug("iommu: no dma-ranges found, no fixed mapping\n");
		वापस -1;
	पूर्ण

	/* The शेष setup is to have the fixed mapping sit after the
	 * dynamic region, so find the top of the largest IOMMU winकरोw
	 * on any axon, then add the size of RAM and that's our max value.
	 * If that is > 32GB we have to करो other shennanigans.
	 */
	fbase = 0;
	क्रम_each_node_by_name(np, "axon") अणु
		cell_iommu_get_winकरोw(np, &dbase, &dsize);
		fbase = max(fbase, dbase + dsize);
	पूर्ण

	fbase = ALIGN(fbase, 1 << IO_SEGMENT_SHIFT);
	fsize = memblock_phys_mem_size();

	अगर ((fbase + fsize) <= 0x800000000ul)
		hbase = 0; /* use the device tree winकरोw */
	अन्यथा अणु
		/* If we're over 32 GB we need to cheat. We can't map all of
		 * RAM with the fixed mapping, and also fit the dynamic
		 * region. So try to place the dynamic region where the hash
		 * table sits, drivers never need to DMA to it, we करोn't
		 * need a fixed mapping क्रम that area.
		 */
		अगर (!htab_address) अणु
			pr_debug("iommu: htab is NULL, on LPAR? Huh?\n");
			वापस -1;
		पूर्ण
		hbase = __pa(htab_address);
		hend  = hbase + htab_size_bytes;

		/* The winकरोw must start and end on a segment boundary */
		अगर ((hbase != ALIGN(hbase, 1 << IO_SEGMENT_SHIFT)) ||
		    (hend != ALIGN(hend, 1 << IO_SEGMENT_SHIFT))) अणु
			pr_debug("iommu: hash window not segment aligned\n");
			वापस -1;
		पूर्ण

		/* Check the hash winकरोw fits inside the real DMA winकरोw */
		क्रम_each_node_by_name(np, "axon") अणु
			cell_iommu_get_winकरोw(np, &dbase, &dsize);

			अगर (hbase < dbase || (hend > (dbase + dsize))) अणु
				pr_debug("iommu: hash window doesn't fit in"
					 "real DMA window\n");
				वापस -1;
			पूर्ण
		पूर्ण

		fbase = 0;
	पूर्ण

	/* Setup the dynamic regions */
	क्रम_each_node_by_name(np, "axon") अणु
		iommu = cell_iommu_alloc(np);
		BUG_ON(!iommu);

		अगर (hbase == 0)
			cell_iommu_get_winकरोw(np, &dbase, &dsize);
		अन्यथा अणु
			dbase = hbase;
			dsize = htab_size_bytes;
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "iommu: node %d, dynamic window 0x%lx-0x%lx "
			"fixed window 0x%lx-0x%lx\n", iommu->nid, dbase,
			 dbase + dsize, fbase, fbase + fsize);

		cell_iommu_setup_stab(iommu, dbase, dsize, fbase, fsize);
		iommu->ptab = cell_iommu_alloc_ptab(iommu, dbase, dsize, 0, 0,
						    IOMMU_PAGE_SHIFT_4K);
		cell_iommu_setup_fixed_ptab(iommu, np, dbase, dsize,
					     fbase, fsize);
		cell_iommu_enable_hardware(iommu);
		cell_iommu_setup_winकरोw(iommu, np, dbase, dsize, 0);
	पूर्ण

	cell_pci_controller_ops.iommu_bypass_supported =
		cell_pci_iommu_bypass_supported;
	वापस 0;
पूर्ण

अटल पूर्णांक iommu_fixed_disabled;

अटल पूर्णांक __init setup_iommu_fixed(अक्षर *str)
अणु
	काष्ठा device_node *pciep;

	अगर (म_भेद(str, "off") == 0)
		iommu_fixed_disabled = 1;

	/* If we can find a pcie-endpoपूर्णांक in the device tree assume that
	 * we're on a triblade or a CAB so by शेष the fixed mapping
	 * should be set to be weakly ordered; but only अगर the boot
	 * option WASN'T set क्रम strong ordering
	 */
	pciep = of_find_node_by_type(शून्य, "pcie-endpoint");

	अगर (म_भेद(str, "weak") == 0 || (pciep && म_भेद(str, "strong") != 0))
		iommu_fixed_is_weak = true;

	of_node_put(pciep);

	वापस 1;
पूर्ण
__setup("iommu_fixed=", setup_iommu_fixed);

अटल पूर्णांक __init cell_iommu_init(व्योम)
अणु
	काष्ठा device_node *np;

	/* If IOMMU is disabled or we have little enough RAM to not need
	 * to enable it, we setup a direct mapping.
	 *
	 * Note: should we make sure we have the IOMMU actually disabled ?
	 */
	अगर (iommu_is_off ||
	    (!iommu_क्रमce_on && memblock_end_of_DRAM() <= 0x80000000ull))
		अगर (cell_iommu_init_disabled() == 0)
			जाओ bail;

	/* Setup various callbacks */
	cell_pci_controller_ops.dma_dev_setup = cell_pci_dma_dev_setup;

	अगर (!iommu_fixed_disabled && cell_iommu_fixed_mapping_init() == 0)
		जाओ करोne;

	/* Create an iommu क्रम each /axon node.  */
	क्रम_each_node_by_name(np, "axon") अणु
		अगर (np->parent == शून्य || np->parent->parent != शून्य)
			जारी;
		cell_iommu_init_one(np, 0);
	पूर्ण

	/* Create an iommu क्रम each toplevel /pci-पूर्णांकernal node क्रम
	 * old hardware/firmware
	 */
	क्रम_each_node_by_name(np, "pci-internal") अणु
		अगर (np->parent == शून्य || np->parent->parent != शून्य)
			जारी;
		cell_iommu_init_one(np, SPIDER_DMA_OFFSET);
	पूर्ण
 करोne:
	/* Setup शेष PCI iommu ops */
	set_pci_dma_ops(&dma_iommu_ops);
	cell_iommu_enabled = true;
 bail:
	/* Register callbacks on OF platक्रमm device addition/removal
	 * to handle linking them to the right DMA operations
	 */
	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &cell_of_bus_notअगरier);

	वापस 0;
पूर्ण
machine_arch_initcall(cell, cell_iommu_init);
