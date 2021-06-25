<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-alpha/dma.h
 *
 * This is essentially the same as the i386 DMA stuff, as the AlphaPCs
 * use ISA-compatible dma.  The only extension is support क्रम high-page
 * रेजिस्टरs that allow to set the top 8 bits of a 32-bit DMA address.
 * This रेजिस्टर should be written last when setting up a DMA address
 * as this will also enable DMA across 64 KB boundaries.
 */

/* $Id: dma.h,v 1.7 1992/12/14 00:29:34 root Exp root $
 * linux/include/यंत्र/dma.h: Defines क्रम using and allocating dma channels.
 * Written by Hennus Bergman, 1992.
 * High DMA channel support & info by Hannu Savolainen
 * and John Boyd, Nov. 1992.
 */

#अगर_अघोषित _ASM_DMA_H
#घोषणा _ASM_DMA_H

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/पन.स>

#घोषणा dma_outb	outb
#घोषणा dma_inb		inb

/*
 * NOTES about DMA transfers:
 *
 *  controller 1: channels 0-3, byte operations, ports 00-1F
 *  controller 2: channels 4-7, word operations, ports C0-DF
 *
 *  - ALL रेजिस्टरs are 8 bits only, regardless of transfer size
 *  - channel 4 is not used - cascades 1 पूर्णांकo 2.
 *  - channels 0-3 are byte - addresses/counts are क्रम physical bytes
 *  - channels 5-7 are word - addresses/counts are क्रम physical words
 *  - transfers must not cross physical 64K (0-3) or 128K (5-7) boundaries
 *  - transfer count loaded to रेजिस्टरs is 1 less than actual count
 *  - controller 2 offsets are all even (2x offsets क्रम controller 1)
 *  - page रेजिस्टरs क्रम 5-7 करोn't use data bit 0, represent 128K pages
 *  - page रेजिस्टरs क्रम 0-3 use bit 0, represent 64K pages
 *
 * DMA transfers are limited to the lower 16MB of _physical_ memory.  
 * Note that addresses loaded पूर्णांकo रेजिस्टरs must be _physical_ addresses,
 * not logical addresses (which may dअगरfer अगर paging is active).
 *
 *  Address mapping क्रम channels 0-3:
 *
 *   A23 ... A16 A15 ... A8  A7 ... A0    (Physical addresses)
 *    |  ...  |   |  ... |   |  ... |
 *    |  ...  |   |  ... |   |  ... |
 *    |  ...  |   |  ... |   |  ... |
 *   P7  ...  P0  A7 ... A0  A7 ... A0   
 * |    Page    | Addr MSB | Addr LSB |   (DMA रेजिस्टरs)
 *
 *  Address mapping क्रम channels 5-7:
 *
 *   A23 ... A17 A16 A15 ... A9 A8 A7 ... A1 A0    (Physical addresses)
 *    |  ...  |   \   \   ... \  \  \  ... \  \
 *    |  ...  |    \   \   ... \  \  \  ... \  (not used)
 *    |  ...  |     \   \   ... \  \  \  ... \
 *   P7  ...  P1 (0) A7 A6  ... A0 A7 A6 ... A0   
 * |      Page      |  Addr MSB   |  Addr LSB  |   (DMA रेजिस्टरs)
 *
 * Again, channels 5-7 transfer _physical_ words (16 bits), so addresses
 * and counts _must_ be word-aligned (the lowest address bit is _ignored_ at
 * the hardware level, so odd-byte transfers aren't possible).
 *
 * Transfer count (_not # bytes_) is limited to 64K, represented as actual
 * count - 1 : 64K => 0xFFFF, 1 => 0x0000.  Thus, count is always 1 or more,
 * and up to 128K bytes may be transferred on channels 5-7 in one operation. 
 *
 */

#घोषणा MAX_DMA_CHANNELS	8

/*
  ISA DMA limitations on Alpha platक्रमms,

  These may be due to SIO (PCI<->ISA bridge) chipset limitation, or
  just a wiring limit.
*/

/* The maximum address क्रम ISA DMA transfer on Alpha XL, due to an
   hardware SIO limitation, is 64MB.
*/
#घोषणा ALPHA_XL_MAX_ISA_DMA_ADDRESS		0x04000000UL

/* The maximum address क्रम ISA DMA transfer on RUFFIAN,
   due to an hardware SIO limitation, is 16MB.
*/
#घोषणा ALPHA_RUFFIAN_MAX_ISA_DMA_ADDRESS	0x01000000UL

/* The maximum address क्रम ISA DMA transfer on SABLE, and some ALCORs,
   due to an hardware SIO chip limitation, is 2GB.
*/
#घोषणा ALPHA_SABLE_MAX_ISA_DMA_ADDRESS		0x80000000UL
#घोषणा ALPHA_ALCOR_MAX_ISA_DMA_ADDRESS		0x80000000UL

/*
  Maximum address क्रम all the others is the complete 32-bit bus
  address space.
*/
#घोषणा ALPHA_MAX_ISA_DMA_ADDRESS		0x100000000UL

#अगर_घोषित CONFIG_ALPHA_GENERIC
# define MAX_ISA_DMA_ADDRESS		(alpha_mv.max_isa_dma_address)
#अन्यथा
# अगर defined(CONFIG_ALPHA_XL)
#  define MAX_ISA_DMA_ADDRESS		ALPHA_XL_MAX_ISA_DMA_ADDRESS
# elअगर defined(CONFIG_ALPHA_RUFFIAN)
#  define MAX_ISA_DMA_ADDRESS		ALPHA_RUFFIAN_MAX_ISA_DMA_ADDRESS
# elअगर defined(CONFIG_ALPHA_SABLE)
#  define MAX_ISA_DMA_ADDRESS		ALPHA_SABLE_MAX_ISA_DMA_ADDRESS
# elअगर defined(CONFIG_ALPHA_ALCOR)
#  define MAX_ISA_DMA_ADDRESS		ALPHA_ALCOR_MAX_ISA_DMA_ADDRESS
# अन्यथा
#  define MAX_ISA_DMA_ADDRESS		ALPHA_MAX_ISA_DMA_ADDRESS
# endअगर
#पूर्ण_अगर

/* If we have the iommu, we करोn't have any address limitations on DMA.
   Otherwise (Nautilus, RX164), we have to have 0-16 Mb DMA zone
   like i386. */
#घोषणा MAX_DMA_ADDRESS		(alpha_mv.mv_pci_tbi ?	\
				 ~0UL : IDENT_ADDR + 0x01000000)

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

#घोषणा DMA_ADDR_0              0x00    /* DMA address रेजिस्टरs */
#घोषणा DMA_ADDR_1              0x02
#घोषणा DMA_ADDR_2              0x04
#घोषणा DMA_ADDR_3              0x06
#घोषणा DMA_ADDR_4              0xC0
#घोषणा DMA_ADDR_5              0xC4
#घोषणा DMA_ADDR_6              0xC8
#घोषणा DMA_ADDR_7              0xCC

#घोषणा DMA_CNT_0               0x01    /* DMA count रेजिस्टरs */
#घोषणा DMA_CNT_1               0x03
#घोषणा DMA_CNT_2               0x05
#घोषणा DMA_CNT_3               0x07
#घोषणा DMA_CNT_4               0xC2
#घोषणा DMA_CNT_5               0xC6
#घोषणा DMA_CNT_6               0xCA
#घोषणा DMA_CNT_7               0xCE

#घोषणा DMA_PAGE_0              0x87    /* DMA page रेजिस्टरs */
#घोषणा DMA_PAGE_1              0x83
#घोषणा DMA_PAGE_2              0x81
#घोषणा DMA_PAGE_3              0x82
#घोषणा DMA_PAGE_5              0x8B
#घोषणा DMA_PAGE_6              0x89
#घोषणा DMA_PAGE_7              0x8A

#घोषणा DMA_HIPAGE_0		(0x400 | DMA_PAGE_0)
#घोषणा DMA_HIPAGE_1		(0x400 | DMA_PAGE_1)
#घोषणा DMA_HIPAGE_2		(0x400 | DMA_PAGE_2)
#घोषणा DMA_HIPAGE_3		(0x400 | DMA_PAGE_3)
#घोषणा DMA_HIPAGE_4		(0x400 | DMA_PAGE_4)
#घोषणा DMA_HIPAGE_5		(0x400 | DMA_PAGE_5)
#घोषणा DMA_HIPAGE_6		(0x400 | DMA_PAGE_6)
#घोषणा DMA_HIPAGE_7		(0x400 | DMA_PAGE_7)

#घोषणा DMA_MODE_READ	0x44	/* I/O to memory, no स्वतःinit, increment, single mode */
#घोषणा DMA_MODE_WRITE	0x48	/* memory to I/O, no स्वतःinit, increment, single mode */
#घोषणा DMA_MODE_CASCADE 0xC0   /* pass thru DREQ->HRQ, DACK<-HLDA only */

#घोषणा DMA_AUTOINIT	0x10

बाह्य spinlock_t  dma_spin_lock;

अटल __अंतरभूत__ अचिन्हित दीर्घ claim_dma_lock(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dma_spin_lock, flags);
	वापस flags;
पूर्ण

अटल __अंतरभूत__ व्योम release_dma_lock(अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&dma_spin_lock, flags);
पूर्ण

/* enable/disable a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम enable_dma(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr<=3)
		dma_outb(dmanr,  DMA1_MASK_REG);
	अन्यथा
		dma_outb(dmanr & 3,  DMA2_MASK_REG);
पूर्ण

अटल __अंतरभूत__ व्योम disable_dma(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr<=3)
		dma_outb(dmanr | 4,  DMA1_MASK_REG);
	अन्यथा
		dma_outb((dmanr & 3) | 4,  DMA2_MASK_REG);
पूर्ण

/* Clear the 'DMA Pointer Flip Flop'.
 * Write 0 क्रम LSB/MSB, 1 क्रम MSB/LSB access.
 * Use this once to initialize the FF to a known state.
 * After that, keep track of it. :-)
 * --- In order to करो that, the DMA routines below should ---
 * --- only be used जबतक पूर्णांकerrupts are disabled! ---
 */
अटल __अंतरभूत__ व्योम clear_dma_ff(अचिन्हित पूर्णांक dmanr)
अणु
	अगर (dmanr<=3)
		dma_outb(0,  DMA1_CLEAR_FF_REG);
	अन्यथा
		dma_outb(0,  DMA2_CLEAR_FF_REG);
पूर्ण

/* set mode (above) क्रम a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_mode(अचिन्हित पूर्णांक dmanr, अक्षर mode)
अणु
	अगर (dmanr<=3)
		dma_outb(mode | dmanr,  DMA1_MODE_REG);
	अन्यथा
		dma_outb(mode | (dmanr&3),  DMA2_MODE_REG);
पूर्ण

/* set extended mode क्रम a specअगरic DMA channel */
अटल __अंतरभूत__ व्योम set_dma_ext_mode(अचिन्हित पूर्णांक dmanr, अक्षर ext_mode)
अणु
	अगर (dmanr<=3)
		dma_outb(ext_mode | dmanr,  DMA1_EXT_MODE_REG);
	अन्यथा
		dma_outb(ext_mode | (dmanr&3),  DMA2_EXT_MODE_REG);
पूर्ण

/* Set only the page रेजिस्टर bits of the transfer address.
 * This is used क्रम successive transfers when we know the contents of
 * the lower 16 bits of the DMA current address रेजिस्टर.
 */
अटल __अंतरभूत__ व्योम set_dma_page(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक pagenr)
अणु
	चयन(dmanr) अणु
		हाल 0:
			dma_outb(pagenr, DMA_PAGE_0);
			dma_outb((pagenr >> 8), DMA_HIPAGE_0);
			अवरोध;
		हाल 1:
			dma_outb(pagenr, DMA_PAGE_1);
			dma_outb((pagenr >> 8), DMA_HIPAGE_1);
			अवरोध;
		हाल 2:
			dma_outb(pagenr, DMA_PAGE_2);
			dma_outb((pagenr >> 8), DMA_HIPAGE_2);
			अवरोध;
		हाल 3:
			dma_outb(pagenr, DMA_PAGE_3);
			dma_outb((pagenr >> 8), DMA_HIPAGE_3);
			अवरोध;
		हाल 5:
			dma_outb(pagenr & 0xfe, DMA_PAGE_5);
			dma_outb((pagenr >> 8), DMA_HIPAGE_5);
			अवरोध;
		हाल 6:
			dma_outb(pagenr & 0xfe, DMA_PAGE_6);
			dma_outb((pagenr >> 8), DMA_HIPAGE_6);
			अवरोध;
		हाल 7:
			dma_outb(pagenr & 0xfe, DMA_PAGE_7);
			dma_outb((pagenr >> 8), DMA_HIPAGE_7);
			अवरोध;
	पूर्ण
पूर्ण


/* Set transfer address & page bits क्रम specअगरic DMA channel.
 * Assumes dma flipflop is clear.
 */
अटल __अंतरभूत__ व्योम set_dma_addr(अचिन्हित पूर्णांक dmanr, अचिन्हित पूर्णांक a)
अणु
	अगर (dmanr <= 3)  अणु
	    dma_outb( a & 0xff, ((dmanr&3)<<1) + IO_DMA1_BASE );
            dma_outb( (a>>8) & 0xff, ((dmanr&3)<<1) + IO_DMA1_BASE );
	पूर्ण  अन्यथा  अणु
	    dma_outb( (a>>1) & 0xff, ((dmanr&3)<<2) + IO_DMA2_BASE );
	    dma_outb( (a>>9) & 0xff, ((dmanr&3)<<2) + IO_DMA2_BASE );
	पूर्ण
	set_dma_page(dmanr, a>>16);	/* set hipage last to enable 32-bit mode */
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
        count--;
	अगर (dmanr <= 3)  अणु
	    dma_outb( count & 0xff, ((dmanr&3)<<1) + 1 + IO_DMA1_BASE );
	    dma_outb( (count>>8) & 0xff, ((dmanr&3)<<1) + 1 + IO_DMA1_BASE );
        पूर्ण अन्यथा अणु
	    dma_outb( (count>>1) & 0xff, ((dmanr&3)<<2) + 2 + IO_DMA2_BASE );
	    dma_outb( (count>>9) & 0xff, ((dmanr&3)<<2) + 2 + IO_DMA2_BASE );
        पूर्ण
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


/* These are in kernel/dma.c: */
बाह्य पूर्णांक request_dma(अचिन्हित पूर्णांक dmanr, स्थिर अक्षर * device_id);	/* reserve a DMA channel */
बाह्य व्योम मुक्त_dma(अचिन्हित पूर्णांक dmanr);	/* release it again */
#घोषणा KERNEL_HAVE_CHECK_DMA
बाह्य पूर्णांक check_dma(अचिन्हित पूर्णांक dmanr);

/* From PCI */

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy 	(0)
#पूर्ण_अगर


#पूर्ण_अगर /* _ASM_DMA_H */
