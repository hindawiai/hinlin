<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_DMA_H
#घोषणा __ASM_ARM_DMA_H

/*
 * This is the maximum भव address which can be DMA'd from.
 */
#अगर_अघोषित CONFIG_ZONE_DMA
#घोषणा MAX_DMA_ADDRESS	0xffffffffUL
#अन्यथा
#घोषणा MAX_DMA_ADDRESS	(अणु \
	बाह्य phys_addr_t arm_dma_zone_size; \
	arm_dma_zone_size && arm_dma_zone_size < (0x10000000 - PAGE_OFFSET) ? \
		(PAGE_OFFSET + arm_dma_zone_size) : 0xffffffffUL; पूर्ण)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ISA_DMA_API
/*
 * This is used to support drivers written क्रम the x86 ISA DMA API.
 * It should not be re-used except क्रम that purpose.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/scatterlist.h>

#समावेश <mach/isa-dma.h>

/*
 * The DMA modes reflect the settings क्रम the ISA DMA controller
 */
#घोषणा DMA_MODE_MASK	 0xcc

#घोषणा DMA_MODE_READ	 0x44
#घोषणा DMA_MODE_WRITE	 0x48
#घोषणा DMA_MODE_CASCADE 0xc0
#घोषणा DMA_AUTOINIT	 0x10

बाह्य raw_spinlock_t  dma_spin_lock;

अटल अंतरभूत अचिन्हित दीर्घ claim_dma_lock(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	raw_spin_lock_irqsave(&dma_spin_lock, flags);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम release_dma_lock(अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore(&dma_spin_lock, flags);
पूर्ण

/* Clear the 'DMA Pointer Flip Flop'.
 * Write 0 क्रम LSB/MSB, 1 क्रम MSB/LSB access.
 */
#घोषणा clear_dma_ff(chan)

/* Set only the page रेजिस्टर bits of the transfer address.
 *
 * NOTE: This is an architecture specअगरic function, and should
 *       be hidden from the drivers
 */
बाह्य व्योम set_dma_page(अचिन्हित पूर्णांक chan, अक्षर pagenr);

/* Request a DMA channel
 *
 * Some architectures may need to करो allocate an पूर्णांकerrupt
 */
बाह्य पूर्णांक  request_dma(अचिन्हित पूर्णांक chan, स्थिर अक्षर * device_id);

/* Free a DMA channel
 *
 * Some architectures may need to करो मुक्त an पूर्णांकerrupt
 */
बाह्य व्योम मुक्त_dma(अचिन्हित पूर्णांक chan);

/* Enable DMA क्रम this channel
 *
 * On some architectures, this may have other side effects like
 * enabling an पूर्णांकerrupt and setting the DMA रेजिस्टरs.
 */
बाह्य व्योम enable_dma(अचिन्हित पूर्णांक chan);

/* Disable DMA क्रम this channel
 *
 * On some architectures, this may have other side effects like
 * disabling an पूर्णांकerrupt or whatever.
 */
बाह्य व्योम disable_dma(अचिन्हित पूर्णांक chan);

/* Test whether the specअगरied channel has an active DMA transfer
 */
बाह्य पूर्णांक dma_channel_active(अचिन्हित पूर्णांक chan);

/* Set the DMA scatter gather list क्रम this channel
 *
 * This should not be called अगर a DMA channel is enabled,
 * especially since some DMA architectures करोn't update the
 * DMA address immediately, but defer it to the enable_dma().
 */
बाह्य व्योम set_dma_sg(अचिन्हित पूर्णांक chan, काष्ठा scatterlist *sg, पूर्णांक nr_sg);

/* Set the DMA address क्रम this channel
 *
 * This should not be called अगर a DMA channel is enabled,
 * especially since some DMA architectures करोn't update the
 * DMA address immediately, but defer it to the enable_dma().
 */
बाह्य व्योम __set_dma_addr(अचिन्हित पूर्णांक chan, व्योम *addr);
#घोषणा set_dma_addr(chan, addr)				\
	__set_dma_addr(chan, (व्योम *)__bus_to_virt(addr))

/* Set the DMA byte count क्रम this channel
 *
 * This should not be called अगर a DMA channel is enabled,
 * especially since some DMA architectures करोn't update the
 * DMA count immediately, but defer it to the enable_dma().
 */
बाह्य व्योम set_dma_count(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ count);

/* Set the transfer direction क्रम this channel
 *
 * This should not be called अगर a DMA channel is enabled,
 * especially since some DMA architectures करोn't update the
 * DMA transfer direction immediately, but defer it to the
 * enable_dma().
 */
बाह्य व्योम set_dma_mode(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक mode);

/* Set the transfer speed क्रम this channel
 */
बाह्य व्योम set_dma_speed(अचिन्हित पूर्णांक chan, पूर्णांक cycle_ns);

/* Get DMA residue count. After a DMA transfer, this
 * should वापस zero. Reading this जबतक a DMA transfer is
 * still in progress will वापस unpredictable results.
 * If called beक्रमe the channel has been used, it may वापस 1.
 * Otherwise, it वापसs the number of _bytes_ left to transfer.
 */
बाह्य पूर्णांक  get_dma_residue(अचिन्हित पूर्णांक chan);

#अगर_अघोषित NO_DMA
#घोषणा NO_DMA	255
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_ISA_DMA_API */

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy    (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_DMA_H */
