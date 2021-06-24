<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* iommu.h: Definitions क्रम the sun5 IOMMU.
 *
 * Copyright (C) 1996, 1999, 2007 David S. Miller (davem@davemloft.net)
 */
#अगर_अघोषित _SPARC64_IOMMU_H
#घोषणा _SPARC64_IOMMU_H

/* The क्रमmat of an iopte in the page tables. */
#घोषणा IOPTE_VALID   0x8000000000000000UL
#घोषणा IOPTE_64K     0x2000000000000000UL
#घोषणा IOPTE_STBUF   0x1000000000000000UL
#घोषणा IOPTE_INTRA   0x0800000000000000UL
#घोषणा IOPTE_CONTEXT 0x07ff800000000000UL
#घोषणा IOPTE_PAGE    0x00007fffffffe000UL
#घोषणा IOPTE_CACHE   0x0000000000000010UL
#घोषणा IOPTE_WRITE   0x0000000000000002UL

#घोषणा IOMMU_NUM_CTXS	4096
#समावेश <यंत्र/iommu-common.h>

काष्ठा iommu_arena अणु
	अचिन्हित दीर्घ	*map;
	अचिन्हित पूर्णांक	hपूर्णांक;
	अचिन्हित पूर्णांक	limit;
पूर्ण;

#घोषणा ATU_64_SPACE_SIZE 0x800000000 /* 32G */

/* Data काष्ठाures क्रम SPARC ATU architecture */
काष्ठा atu_iotsb अणु
	व्योम	*table;		/* IOTSB table base भव addr*/
	u64	ra;		/* IOTSB table real addr */
	u64	dvma_size;	/* ranges[3].size or OS slected 32G size */
	u64	dvma_base;	/* ranges[3].base */
	u64	table_size;	/* IOTSB table size */
	u64	page_size;	/* IO PAGE size क्रम IOTSB */
	u32	iotsb_num;	/* tsbnum is same as iotsb_handle */
पूर्ण;

काष्ठा atu_ranges अणु
	u64	base;
	u64	size;
पूर्ण;

काष्ठा atu अणु
	काष्ठा	atu_ranges	*ranges;
	काष्ठा	atu_iotsb	*iotsb;
	काष्ठा	iommu_map_table	tbl;
	u64			base;
	u64			size;
	u64			dma_addr_mask;
पूर्ण;

काष्ठा iommu अणु
	काष्ठा iommu_map_table	tbl;
	काष्ठा atu		*atu;
	spinlock_t		lock;
	u32			dma_addr_mask;
	iopte_t			*page_table;
	अचिन्हित दीर्घ		iommu_control;
	अचिन्हित दीर्घ		iommu_tsbbase;
	अचिन्हित दीर्घ		iommu_flush;
	अचिन्हित दीर्घ		iommu_flushinv;
	अचिन्हित दीर्घ		iommu_tags;
	अचिन्हित दीर्घ		iommu_ctxflush;
	अचिन्हित दीर्घ		ग_लिखो_complete_reg;
	अचिन्हित दीर्घ		dummy_page;
	अचिन्हित दीर्घ		dummy_page_pa;
	अचिन्हित दीर्घ		ctx_lowest_मुक्त;
	DECLARE_BITMAP(ctx_biपंचांगap, IOMMU_NUM_CTXS);
पूर्ण;

काष्ठा strbuf अणु
	पूर्णांक			strbuf_enabled;
	अचिन्हित दीर्घ		strbuf_control;
	अचिन्हित दीर्घ		strbuf_pflush;
	अचिन्हित दीर्घ		strbuf_fsync;
	अचिन्हित दीर्घ		strbuf_err_stat;
	अचिन्हित दीर्घ		strbuf_tag_diag;
	अचिन्हित दीर्घ		strbuf_line_diag;
	अचिन्हित दीर्घ		strbuf_ctxflush;
	अचिन्हित दीर्घ		strbuf_ctxmatch_base;
	अचिन्हित दीर्घ		strbuf_flushflag_pa;
	अस्थिर अचिन्हित दीर्घ *strbuf_flushflag;
	अस्थिर अचिन्हित दीर्घ	__flushflag_buf[(64+(64-1)) / माप(दीर्घ)];
पूर्ण;

पूर्णांक iommu_table_init(काष्ठा iommu *iommu, पूर्णांक tsbsize,
		     u32 dma_offset, u32 dma_addr_mask,
		     पूर्णांक numa_node);

#पूर्ण_अगर /* !(_SPARC64_IOMMU_H) */
