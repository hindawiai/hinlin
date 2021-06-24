<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* io-unit.h: Definitions क्रम the sun4d IO-UNIT.
 *
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */
#अगर_अघोषित _SPARC_IO_UNIT_H
#घोषणा _SPARC_IO_UNIT_H

#समावेश <linux/spinlock.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>

/* The io-unit handles all भव to physical address translations
 * that occur between the SBUS and physical memory.  Access by
 * the cpu to IO रेजिस्टरs and similar go over the xdbus so are
 * translated by the on chip SRMMU.  The io-unit and the srmmu करो
 * not need to have the same translations at all, in fact most
 * of the समय the translations they handle are a disjunct set.
 * Basically the io-unit handles all dvma sbus activity.
 */
 
/* AIEEE, unlike the nice sun4m, these monsters have 
   fixed DMA range 64M */
 
#घोषणा IOUNIT_DMA_BASE	    0xfc000000 /* TOP - 64M */
#घोषणा IOUNIT_DMA_SIZE	    0x04000000 /* 64M */
/* We use last 1M क्रम sparc_dvma_दो_स्मृति */
#घोषणा IOUNIT_DVMA_SIZE    0x00100000 /* 1M */

/* The क्रमmat of an iopte in the बाह्यal page tables */
#घोषणा IOUPTE_PAGE          0xffffff00 /* Physical page number (PA[35:12])	*/
#घोषणा IOUPTE_CACHE         0x00000080 /* Cached (in Viking/MXCC)		*/
/* XXX Jakub, find out how to program SBUS streaming cache on XDBUS/sun4d.
 * XXX Actually, all you should need to करो is find out where the रेजिस्टरs
 * XXX are and copy over the sparc64 implementation I wrote.  There may be
 * XXX some horrible hwbugs though, so be careful.  -DaveM
 */
#घोषणा IOUPTE_STREAM        0x00000040 /* Translation can use streaming cache	*/
#घोषणा IOUPTE_INTRA	     0x00000008 /* SBUS direct slot->slot transfer	*/
#घोषणा IOUPTE_WRITE         0x00000004 /* Writeable				*/
#घोषणा IOUPTE_VALID         0x00000002 /* IOPTE is valid			*/
#घोषणा IOUPTE_PARITY        0x00000001 /* Parity is checked during DVMA	*/

काष्ठा iounit_काष्ठा अणु
	अचिन्हित दीर्घ		bmap[(IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 3)) / माप(अचिन्हित दीर्घ)];
	spinlock_t		lock;
	iopte_t __iomem		*page_table;
	अचिन्हित दीर्घ		rotor[3];
	अचिन्हित दीर्घ		limit[4];
पूर्ण;

#घोषणा IOUNIT_BMAP1_START	0x00000000
#घोषणा IOUNIT_BMAP1_END	(IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 1))
#घोषणा IOUNIT_BMAP2_START	IOUNIT_BMAP1_END
#घोषणा IOUNIT_BMAP2_END	IOUNIT_BMAP2_START + (IOUNIT_DMA_SIZE >> (PAGE_SHIFT + 2))
#घोषणा IOUNIT_BMAPM_START	IOUNIT_BMAP2_END
#घोषणा IOUNIT_BMAPM_END	((IOUNIT_DMA_SIZE - IOUNIT_DVMA_SIZE) >> PAGE_SHIFT)

#पूर्ण_अगर /* !(_SPARC_IO_UNIT_H) */
