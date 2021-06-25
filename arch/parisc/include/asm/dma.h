<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* यंत्र/dma.h: Defines क्रम using and allocating dma channels.
 * Written by Hennus Bergman, 1992.
 * High DMA channel support & info by Hannu Savolainen
 * and John Boyd, Nov. 1992.
 * (c) Copyright 2000, Grant Grundler
 */

#अगर_अघोषित _ASM_DMA_H
#घोषणा _ASM_DMA_H

#समावेश <यंत्र/पन.स>		/* need byte IO */

#घोषणा dma_outb	outb
#घोषणा dma_inb		inb

/*
** DMA_CHUNK_SIZE is used by the SCSI mid-layer to अवरोध up
** (or rather not merge) DMAs पूर्णांकo manageable chunks.
** On parisc, this is more of the software/tuning स्थिरraपूर्णांक
** rather than the HW. I/O MMU allocation algorithms can be
** faster with smaller sizes (to some degree).
*/
#घोषणा DMA_CHUNK_SIZE	(BITS_PER_LONG*PAGE_SIZE)

/* The maximum address that we can perक्रमm a DMA transfer to on this platक्रमm
** New dynamic DMA पूर्णांकerfaces should obsolete this....
*/
#घोषणा MAX_DMA_ADDRESS (~0UL)

/*
** We करोn't have DMA channels... well V-class करोes but the
** Dynamic DMA Mapping पूर्णांकerface will support them... right? :^)
** Note: this is not relevant right now क्रम PA-RISC, but we cannot 
** leave this as undefined because some things (e.g. sound)
** won't compile :-(
*/
#घोषणा MAX_DMA_CHANNELS 8
#घोषणा DMA_MODE_READ	0x44	/* I/O to memory, no स्वतःinit, increment, single mode */
#घोषणा DMA_MODE_WRITE	0x48	/* memory to I/O, no स्वतःinit, increment, single mode */
#घोषणा DMA_MODE_CASCADE 0xC0	/* pass thru DREQ->HRQ, DACK<-HLDA only */

#घोषणा DMA_AUTOINIT	0x10

/* 8237 DMA controllers */
#घोषणा IO_DMA1_BASE	0x00	/* 8 bit slave DMA, channels 0..3 */
#घोषणा IO_DMA2_BASE	0xC0	/* 16 bit master DMA, ch 4(=slave input)..7 */

/* DMA controller रेजिस्टरs */
#घोषणा DMA1_CMD_REG		0x08	/* command रेजिस्टर (w) */
#घोषणा DMA1_STAT_REG		0x08	/* status रेजिस्टर (r) */
#घोषणा DMA1_REQ_REG            0x09    /* request रेजिस्टर (w) */
#घोषणा DMA1_MASK_REG		0x0A	/* single-channel mask (w) */
#घोषणा DMA1_MODE_REG		0x0B	/* mode रेजिस्टर (w) */
#घोषणा DMA1_CLEAR_FF_REG	0x0C	/* clear poपूर्णांकer flip-flop (w) */
#घोषणा DMA1_TEMP_REG           0x0D    /* Temporary Register (r) */
#घोषणा DMA1_RESET_REG		0x0D	/* Master Clear (w) */
#घोषणा DMA1_CLR_MASK_REG       0x0E    /* Clear Mask */
#घोषणा DMA1_MASK_ALL_REG       0x0F    /* all-channels mask (w) */
#घोषणा DMA1_EXT_MODE_REG	(0x400 | DMA1_MODE_REG)

#घोषणा DMA2_CMD_REG		0xD0	/* command रेजिस्टर (w) */
#घोषणा DMA2_STAT_REG		0xD0	/* status रेजिस्टर (r) */
#घोषणा DMA2_REQ_REG            0xD2    /* request रेजिस्टर (w) */
#घोषणा DMA2_MASK_REG		0xD4	/* single-channel mask (w) */
#घोषणा DMA2_MODE_REG		0xD6	/* mode रेजिस्टर (w) */
#घोषणा DMA2_CLEAR_FF_REG	0xD8	/* clear poपूर्णांकer flip-flop (w) */
#घोषणा DMA2_TEMP_REG           0xDA    /* Temporary Register (r) */
#घोषणा DMA2_RESET_REG		0xDA	/* Master Clear (w) */
#घोषणा DMA2_CLR_MASK_REG       0xDC    /* Clear Mask */
#घोषणा DMA2_MASK_ALL_REG       0xDE    /* all-channels mask (w) */
#घोषणा DMA2_EXT_MODE_REG	(0x400 | DMA2_MODE_REG)

अटल __अंतरभूत__ अचिन्हित दीर्घ claim_dma_lock(व्योम)
अणु
	वापस 0;
पूर्ण

अटल __अंतरभूत__ व्योम release_dma_lock(अचिन्हित दीर्घ flags)
अणु
पूर्ण


/* Get DMA residue count. After a DMA transfer, this
 * should वापस zero. Reading this जबतक a DMA transfer is
 * still in progress will वापस unpredictable results.
 * If called beक्रमe the channel has been used, it may वापस 1.
 * Otherwise, it वापसs the number of _bytes_ left to transfer.
 *
 * Assumes DMA flip-flop is clear.
 */
अटल __अंतरभूत__ पूर्णांक get_dma_residue(अचिन्हित पूर्णांक dmanr)
अणु
	अचिन्हित पूर्णांक io_port = (dmanr<=3)? ((dmanr&3)<<1) + 1 + IO_DMA1_BASE
					 : ((dmanr&3)<<2) + 2 + IO_DMA2_BASE;

	/* using लघु to get 16-bit wrap around */
	अचिन्हित लघु count;

	count = 1 + dma_inb(io_port);
	count += dma_inb(io_port) << 8;
	
	वापस (dmanr<=3)? count : (count<<1);
पूर्ण

/* enable/disable a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम enable_dma(अचिन्हित पूर्णांक dmanr)
अणु
#अगर_घोषित CONFIG_SUPERIO
	अगर (dmanr<=3)
		dma_outb(dmanr,  DMA1_MASK_REG);
	अन्यथा
		dma_outb(dmanr & 3,  DMA2_MASK_REG);
#पूर्ण_अगर
पूर्ण

अटल __अंतरभूत__ व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
#अगर_घोषित CONFIG_SUPERIO
	अगर (dmanr<=3)
		dma_outb(dmanr | 4,  DMA1_MASK_REG);
	अन्यथा
		dma_outb((dmanr & 3) | 4,  DMA2_MASK_REG);
#पूर्ण_अगर
पूर्ण

/* reserve a DMA channel */
#घोषणा request_dma(dmanr, device_id)	(0)

/* Clear the 'DMA Pointer Flip Flop'.
 * Write 0 क्रम LSB/MSB, 1 क्रम MSB/LSB access.
 * Use this once to initialize the FF to a known state.
 * After that, keep track of it. :-)
 * --- In order to करो that, the DMA routines below should ---
 * --- only be used जबतक holding the DMA lock ! ---
 */
अटल __अंतरभूत__ व्योम clear_dma_ff(अचिन्हित पूर्णांक dmanr)
अणु
पूर्ण

/* set mode (above) क्रम a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अक्षर mode)
अणु
पूर्ण

/* Set only the page रेजिस्टर bits of the transfer address.
 * This is used क्रम successive transfers when we know the contents of
 * the lower 16 bits of the DMA current address रेजिस्टर, but a 64k boundary
 * may have been crossed.
 */
अटल __अंतरभूत__ व्योम set_dma_page(अचिन्हित पूर्णांक dmanr, अक्षर pagenr)
अणु
पूर्ण


/* Set transfer address & page bits क्रम specअगरic DMA channel.
 * Assumes dma flipflop is clear.
 */
अटल __अंतरभूत__ व्योम set_dma_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
पूर्ण


/* Set transfer size (max 64k क्रम DMA1..3, 128k क्रम DMA5..7) क्रम
 * a specअगरic DMA channel.
 * You must ensure the parameters are valid.
 * NOTE: from a manual: "the number of transfers is one more
 * than the initial word count"! This is taken पूर्णांकo account.
 * Assumes dma flip-flop is clear.
 * NOTE 2: "count" represents _bytes_ and must be even क्रम channels 5-7.
 */
अटल __अंतरभूत__ व्योम set_dma_count(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक count)
अणु
पूर्ण


#घोषणा मुक्त_dma(dmanr)

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy 	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_DMA_H */
