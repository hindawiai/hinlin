<शैली गुरु>
/*
 * include/यंत्र-xtensa/dma.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_DMA_H
#घोषणा _XTENSA_DMA_H

#समावेश <यंत्र/पन.स>		/* need byte IO */

/*
 * This is only to be defined अगर we have PC-like DMA.
 * By शेष this is not true on an Xtensa processor,
 * however on boards with a PCI bus, such functionality
 * might be emulated बाह्यally.
 *
 * NOTE:  there still exists driver code that assumes
 * this is defined, eg. drivers/sound/soundcard.c (as of 2.4).
 */
#घोषणा MAX_DMA_CHANNELS	8

/*
 * The maximum भव address to which DMA transfers
 * can be perक्रमmed on this platक्रमm.
 *
 * NOTE: This is board (platक्रमm) specअगरic, not processor-specअगरic!
 *
 * NOTE: This assumes DMA transfers can only be perक्रमmed on
 *	the section of physical memory contiguously mapped in भव
 *	space क्रम the kernel.  For the Xtensa architecture, this
 *	means the maximum possible size of this DMA area is
 *	the size of the अटलally mapped kernel segment
 *	(XCHAL_KSEG_अणुCACHED,BYPASSपूर्ण_SIZE), ie. 128 MB.
 *
 * NOTE: When the entire KSEG area is DMA capable, we subtract
 *	one from the max address so that the virt_to_phys() macro
 *	works correctly on the address (otherwise the address
 *	enters another area, and virt_to_phys() may not वापस
 *	the value desired).
 */

#अगर_अघोषित MAX_DMA_ADDRESS
#घोषणा MAX_DMA_ADDRESS		(PAGE_OFFSET + XCHAL_KIO_SIZE - 1)
#पूर्ण_अगर

/* Reserve and release a DMA channel */
बाह्य पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id);
बाह्य व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr);

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy 	(0)
#पूर्ण_अगर


#पूर्ण_अगर
