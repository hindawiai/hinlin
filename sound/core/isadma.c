<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ISA DMA support functions
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

/*
 * Defining following add some delay. Maybe this helps क्रम some broken
 * ISA DMA controllers.
 */

#अघोषित HAVE_REALLY_SLOW_DMA_CONTROLLER

#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <यंत्र/dma.h>

/**
 * snd_dma_program - program an ISA DMA transfer
 * @dma: the dma number
 * @addr: the physical address of the buffer
 * @size: the DMA transfer size
 * @mode: the DMA transfer mode, DMA_MODE_XXX
 *
 * Programs an ISA DMA transfer क्रम the given buffer.
 */
व्योम snd_dma_program(अचिन्हित दीर्घ dma,
		     अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size,
                     अचिन्हित लघु mode)
अणु
	अचिन्हित दीर्घ flags;

	flags = claim_dma_lock();
	disable_dma(dma);
	clear_dma_ff(dma);
	set_dma_mode(dma, mode);
	set_dma_addr(dma, addr);
	set_dma_count(dma, size);
	अगर (!(mode & DMA_MODE_NO_ENABLE))
		enable_dma(dma);
	release_dma_lock(flags);
पूर्ण
EXPORT_SYMBOL(snd_dma_program);

/**
 * snd_dma_disable - stop the ISA DMA transfer
 * @dma: the dma number
 *
 * Stops the ISA DMA transfer.
 */
व्योम snd_dma_disable(अचिन्हित दीर्घ dma)
अणु
	अचिन्हित दीर्घ flags;

	flags = claim_dma_lock();
	clear_dma_ff(dma);
	disable_dma(dma);
	release_dma_lock(flags);
पूर्ण
EXPORT_SYMBOL(snd_dma_disable);

/**
 * snd_dma_poपूर्णांकer - वापस the current poपूर्णांकer to DMA transfer buffer in bytes
 * @dma: the dma number
 * @size: the dma transfer size
 *
 * Return: The current poपूर्णांकer in DMA transfer buffer in bytes.
 */
अचिन्हित पूर्णांक snd_dma_poपूर्णांकer(अचिन्हित दीर्घ dma, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक result, result1;

	flags = claim_dma_lock();
	clear_dma_ff(dma);
	अगर (!isa_dma_bridge_buggy)
		disable_dma(dma);
	result = get_dma_residue(dma);
	/*
	 * HACK - पढ़ो the counter again and choose higher value in order to
	 * aव्योम पढ़ोing during counter lower byte roll over अगर the
	 * isa_dma_bridge_buggy is set.
	 */
	result1 = get_dma_residue(dma);
	अगर (!isa_dma_bridge_buggy)
		enable_dma(dma);
	release_dma_lock(flags);
	अगर (unlikely(result < result1))
		result = result1;
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (result > size)
		pr_err("ALSA: pointer (0x%x) for DMA #%ld is greater than transfer size (0x%x)\n", result, dma, size);
#पूर्ण_अगर
	अगर (result >= size || result == 0)
		वापस 0;
	अन्यथा
		वापस size - result;
पूर्ण
EXPORT_SYMBOL(snd_dma_poपूर्णांकer);
