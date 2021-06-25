<शैली गुरु>
/*
 *	mcfmmu.h -- definitions क्रम the ColdFire v4e MMU
 *
 *	(C) Copyright 2011,  Greg Ungerer <gerg@uclinux.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित	MCFMMU_H
#घोषणा	MCFMMU_H

/*
 *	The MMU support रेजिस्टरs are mapped पूर्णांकo the address space using
 *	the processor MMUBASE रेजिस्टर. We used a fixed address क्रम mapping,
 *	there करोesn't seem any need to make this configurable yet.
 */
#घोषणा	MMUBASE		0xfe000000

/*
 *	The support रेजिस्टरs of the MMU. Names are the sames as those
 *	used in the Freescale v4e करोcumentation.
 */
#घोषणा	MMUCR		(MMUBASE + 0x00)	/* Control रेजिस्टर */
#घोषणा	MMUOR		(MMUBASE + 0x04)	/* Operation रेजिस्टर */
#घोषणा	MMUSR		(MMUBASE + 0x08)	/* Status रेजिस्टर */
#घोषणा	MMUAR		(MMUBASE + 0x10)	/* TLB Address रेजिस्टर */
#घोषणा	MMUTR		(MMUBASE + 0x14)	/* TLB Tag रेजिस्टर */
#घोषणा	MMUDR		(MMUBASE + 0x18)	/* TLB Data रेजिस्टर */

/*
 *	MMU Control रेजिस्टर bit flags
 */
#घोषणा	MMUCR_EN	0x00000001		/* Virtual mode enable */
#घोषणा	MMUCR_ASM	0x00000002		/* Address space mode */

/*
 *	MMU Operation रेजिस्टर.
 */
#घोषणा	MMUOR_UAA	0x00000001		/* Update allocation address */
#घोषणा	MMUOR_ACC	0x00000002		/* TLB access */
#घोषणा	MMUOR_RD	0x00000004		/* TLB access पढ़ो */
#घोषणा	MMUOR_WR	0x00000000		/* TLB access ग_लिखो */
#घोषणा	MMUOR_ADR	0x00000008		/* TLB address select */
#घोषणा	MMUOR_ITLB	0x00000010		/* ITLB operation */
#घोषणा	MMUOR_CAS	0x00000020		/* Clear non-locked ASID TLBs */
#घोषणा	MMUOR_CNL	0x00000040		/* Clear non-locked TLBs */
#घोषणा	MMUOR_CA	0x00000080		/* Clear all TLBs */
#घोषणा	MMUOR_STLB	0x00000100		/* Search TLBs */
#घोषणा	MMUOR_AAN	16			/* TLB allocation address */
#घोषणा	MMUOR_AAMASK	0xffff0000		/* AA mask */

/*
 *	MMU Status रेजिस्टर.
 */
#घोषणा	MMUSR_HIT	0x00000002		/* Search TLB hit */
#घोषणा	MMUSR_WF	0x00000008		/* Write access fault */
#घोषणा	MMUSR_RF	0x00000010		/* Read access fault */
#घोषणा	MMUSR_SPF	0x00000020		/* Supervisor protect fault */

/*
 *	MMU Read/Write Tag रेजिस्टर.
 */
#घोषणा	MMUTR_V		0x00000001		/* Valid */
#घोषणा	MMUTR_SG	0x00000002		/* Shared global */
#घोषणा	MMUTR_IDN	2			/* Address Space ID */
#घोषणा	MMUTR_IDMASK	0x000003fc		/* ASID mask */
#घोषणा	MMUTR_VAN	10			/* Virtual Address */
#घोषणा	MMUTR_VAMASK	0xfffffc00		/* VA mask */

/*
 *	MMU Read/Write Data रेजिस्टर.
 */
#घोषणा	MMUDR_LK	0x00000002		/* Lock entry */
#घोषणा	MMUDR_X		0x00000004		/* Execute access enable */
#घोषणा	MMUDR_W		0x00000008		/* Write access enable */
#घोषणा	MMUDR_R		0x00000010		/* Read access enable */
#घोषणा	MMUDR_SP	0x00000020		/* Supervisor access enable */
#घोषणा	MMUDR_CM_CWT	0x00000000		/* Cachable ग_लिखो thru */
#घोषणा	MMUDR_CM_CCB	0x00000040		/* Cachable copy back */
#घोषणा	MMUDR_CM_NCP	0x00000080		/* Non-cachable precise */
#घोषणा	MMUDR_CM_NCI	0x000000c0		/* Non-cachable imprecise */
#घोषणा	MMUDR_SZ_1MB	0x00000000		/* 1MB page size */
#घोषणा	MMUDR_SZ_4KB	0x00000100		/* 4kB page size */
#घोषणा	MMUDR_SZ_8KB	0x00000200		/* 8kB page size */
#घोषणा	MMUDR_SZ_1KB	0x00000300		/* 1kB page size */
#घोषणा	MMUDR_PAN	10			/* Physical address */
#घोषणा	MMUDR_PAMASK	0xfffffc00		/* PA mask */

#अगर_अघोषित __ASSEMBLY__

/*
 *	Simple access functions क्रम the MMU रेजिस्टरs. Nothing fancy
 *	currently required, just simple 32bit access.
 */
अटल अंतरभूत u32 mmu_पढ़ो(u32 a)
अणु
	वापस *((अस्थिर u32 *) a);
पूर्ण

अटल अंतरभूत व्योम mmu_ग_लिखो(u32 a, u32 v)
अणु
	*((अस्थिर u32 *) a) = v;
	__यंत्र__ __अस्थिर__ ("nop");
पूर्ण

व्योम cf_booपंचांगem_alloc(व्योम);
व्योम cf_mmu_context_init(व्योम);
पूर्णांक cf_tlb_miss(काष्ठा pt_regs *regs, पूर्णांक ग_लिखो, पूर्णांक dtlb, पूर्णांक extension_word);

#पूर्ण_अगर

#पूर्ण_अगर	/* MCFMMU_H */
