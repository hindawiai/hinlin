<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_MMU_H
#घोषणा _ASM_MICROBLAZE_MMU_H

#  अगरdef __KERNEL__
#   अगरndef __ASSEMBLY__

/* Default "unsigned long" context */
प्रकार अचिन्हित दीर्घ mm_context_t;

/* Hardware Page Table Entry */
प्रकार काष्ठा _PTE अणु
	अचिन्हित दीर्घ    v:1;	/* Entry is valid */
	अचिन्हित दीर्घ vsid:24;	/* Virtual segment identअगरier */
	अचिन्हित दीर्घ    h:1;	/* Hash algorithm indicator */
	अचिन्हित दीर्घ  api:6;	/* Abbreviated page index */
	अचिन्हित दीर्घ  rpn:20;	/* Real (physical) page number */
	अचिन्हित दीर्घ     :3;	/* Unused */
	अचिन्हित दीर्घ    r:1;	/* Referenced */
	अचिन्हित दीर्घ    c:1;	/* Changed */
	अचिन्हित दीर्घ    w:1;	/* Write-thru cache mode */
	अचिन्हित दीर्घ    i:1;	/* Cache inhibited */
	अचिन्हित दीर्घ    m:1;	/* Memory coherence */
	अचिन्हित दीर्घ    g:1;	/* Guarded */
	अचिन्हित दीर्घ     :1;	/* Unused */
	अचिन्हित दीर्घ   pp:2;	/* Page protection */
पूर्ण PTE;

/* Values क्रम PP (assumes Ks=0, Kp=1) */
#  define PP_RWXX	0 /* Supervisor पढ़ो/ग_लिखो, User none */
#  define PP_RWRX	1 /* Supervisor पढ़ो/ग_लिखो, User पढ़ो */
#  define PP_RWRW	2 /* Supervisor पढ़ो/ग_लिखो, User पढ़ो/ग_लिखो */
#  define PP_RXRX	3 /* Supervisor पढ़ो,       User पढ़ो */

/* Segment Register */
प्रकार काष्ठा _SEGREG अणु
	अचिन्हित दीर्घ    t:1;	/* Normal or I/O  type */
	अचिन्हित दीर्घ   ks:1;	/* Supervisor 'key' (normally 0) */
	अचिन्हित दीर्घ   kp:1;	/* User 'key' (normally 1) */
	अचिन्हित दीर्घ    n:1;	/* No-execute */
	अचिन्हित दीर्घ     :4;	/* Unused */
	अचिन्हित दीर्घ vsid:24;	/* Virtual Segment Identअगरier */
पूर्ण SEGREG;

बाह्य व्योम _tlbie(अचिन्हित दीर्घ va);	/* invalidate a TLB entry */
बाह्य व्योम _tlbia(व्योम);		/* invalidate all TLB entries */

/*
 * tlb_skip size stores actual number skipped TLBs from TLB0 - every directy TLB
 * mapping has to increase tlb_skip size.
 */
बाह्य u32 tlb_skip;
#   endअगर /* __ASSEMBLY__ */

/*
 * The MicroBlaze processor has a TLB architecture identical to PPC-40x. The
 * inकाष्ठाion and data sides share a unअगरied, 64-entry, semi-associative
 * TLB which is मुख्यtained totally under software control. In addition, the
 * inकाष्ठाion side has a hardware-managed, 2,4, or 8-entry, fully-associative
 * TLB which serves as a first level to the shared TLB. These two TLBs are
 * known as the UTLB and ITLB, respectively.
 */

#  define MICROBLAZE_TLB_SIZE 64

/* For हालs when you want to skip some TLB entries */
#  define MICROBLAZE_TLB_SKIP 0

/* Use the last TLB क्रम temporary access to LMB */
#  define MICROBLAZE_LMB_TLB_ID 63

/*
 * TLB entries are defined by a "high" tag portion and a "low" data
 * portion. The data portion is 32-bits.
 *
 * TLB entries are managed entirely under software control by पढ़ोing,
 * writing, and searching using the MTS and MFS inकाष्ठाions.
 */

#  define TLB_LO		1
#  define TLB_HI		0
#  define TLB_DATA		TLB_LO
#  define TLB_TAG		TLB_HI

/* Tag portion */
#  define TLB_EPN_MASK		0xFFFFFC00 /* Effective Page Number */
#  define TLB_PAGESZ_MASK	0x00000380
#  define TLB_PAGESZ(x)		(((x) & 0x7) << 7)
#  define PAGESZ_1K		0
#  define PAGESZ_4K		1
#  define PAGESZ_16K		2
#  define PAGESZ_64K		3
#  define PAGESZ_256K		4
#  define PAGESZ_1M		5
#  define PAGESZ_4M		6
#  define PAGESZ_16M		7
#  define TLB_VALID		0x00000040 /* Entry is valid */

/* Data portion */
#  define TLB_RPN_MASK		0xFFFFFC00 /* Real Page Number */
#  define TLB_PERM_MASK		0x00000300
#  define TLB_EX		0x00000200 /* Inकाष्ठाion execution allowed */
#  define TLB_WR		0x00000100 /* Writes permitted */
#  define TLB_ZSEL_MASK		0x000000F0
#  define TLB_ZSEL(x)		(((x) & 0xF) << 4)
#  define TLB_ATTR_MASK		0x0000000F
#  define TLB_W			0x00000008 /* Caching is ग_लिखो-through */
#  define TLB_I			0x00000004 /* Caching is inhibited */
#  define TLB_M			0x00000002 /* Memory is coherent */
#  define TLB_G			0x00000001 /* Memory is guarded from prefetch */

#  endअगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_MMU_H */
