<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI ISA DMA support functions
 * Copyright (c) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/dma.h>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"

/**
 * comedi_isadma_program - program and enable an ISA DMA transfer
 * @desc:	the ISA DMA cookie to program and enable
 */
व्योम comedi_isadma_program(काष्ठा comedi_isadma_desc *desc)
अणु
	अचिन्हित दीर्घ flags;

	flags = claim_dma_lock();
	clear_dma_ff(desc->chan);
	set_dma_mode(desc->chan, desc->mode);
	set_dma_addr(desc->chan, desc->hw_addr);
	set_dma_count(desc->chan, desc->size);
	enable_dma(desc->chan);
	release_dma_lock(flags);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_program);

/**
 * comedi_isadma_disable - disable the ISA DMA channel
 * @dma_chan:	the DMA channel to disable
 *
 * Returns the residue (reमुख्यing bytes) left in the DMA transfer.
 */
अचिन्हित पूर्णांक comedi_isadma_disable(अचिन्हित पूर्णांक dma_chan)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक residue;

	flags = claim_dma_lock();
	disable_dma(dma_chan);
	residue = get_dma_residue(dma_chan);
	release_dma_lock(flags);

	वापस residue;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_disable);

/**
 * comedi_isadma_disable_on_sample - disable the ISA DMA channel
 * @dma_chan:	the DMA channel to disable
 * @size:	the sample size (in bytes)
 *
 * Returns the residue (reमुख्यing bytes) left in the DMA transfer.
 */
अचिन्हित पूर्णांक comedi_isadma_disable_on_sample(अचिन्हित पूर्णांक dma_chan,
					     अचिन्हित पूर्णांक size)
अणु
	पूर्णांक stalled = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक new_residue;

	residue = comedi_isadma_disable(dma_chan);
	जबतक (residue % size) अणु
		/* residue is a partial sample, enable DMA to allow more data */
		flags = claim_dma_lock();
		enable_dma(dma_chan);
		release_dma_lock(flags);

		udelay(2);
		new_residue = comedi_isadma_disable(dma_chan);

		/* is DMA stalled? */
		अगर (new_residue == residue) अणु
			stalled++;
			अगर (stalled > 10)
				अवरोध;
		पूर्ण अन्यथा अणु
			residue = new_residue;
			stalled = 0;
		पूर्ण
	पूर्ण
	वापस residue;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_disable_on_sample);

/**
 * comedi_isadma_poll - poll the current DMA transfer
 * @dma:	the ISA DMA to poll
 *
 * Returns the position (in bytes) of the current DMA transfer.
 */
अचिन्हित पूर्णांक comedi_isadma_poll(काष्ठा comedi_isadma *dma)
अणु
	काष्ठा comedi_isadma_desc *desc = &dma->desc[dma->cur_dma];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक result;
	अचिन्हित पूर्णांक result1;

	flags = claim_dma_lock();
	clear_dma_ff(desc->chan);
	अगर (!isa_dma_bridge_buggy)
		disable_dma(desc->chan);
	result = get_dma_residue(desc->chan);
	/*
	 * Read the counter again and choose higher value in order to
	 * aव्योम पढ़ोing during counter lower byte roll over अगर the
	 * isa_dma_bridge_buggy is set.
	 */
	result1 = get_dma_residue(desc->chan);
	अगर (!isa_dma_bridge_buggy)
		enable_dma(desc->chan);
	release_dma_lock(flags);

	अगर (result < result1)
		result = result1;
	अगर (result >= desc->size || result == 0)
		वापस 0;
	वापस desc->size - result;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_poll);

/**
 * comedi_isadma_set_mode - set the ISA DMA transfer direction
 * @desc:	the ISA DMA cookie to set
 * @dma_dir:	the DMA direction
 */
व्योम comedi_isadma_set_mode(काष्ठा comedi_isadma_desc *desc, अक्षर dma_dir)
अणु
	desc->mode = (dma_dir == COMEDI_ISADMA_READ) ? DMA_MODE_READ
						     : DMA_MODE_WRITE;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_set_mode);

/**
 * comedi_isadma_alloc - allocate and initialize the ISA DMA
 * @dev:	comedi_device काष्ठा
 * @n_desc:	the number of cookies to allocate
 * @dma_chan:	DMA channel क्रम the first cookie
 * @dma_chan2:	DMA channel क्रम the second cookie
 * @maxsize:	the size of the buffer to allocate क्रम each cookie
 * @dma_dir:	the DMA direction
 *
 * Returns the allocated and initialized ISA DMA or शून्य अगर anything fails.
 */
काष्ठा comedi_isadma *comedi_isadma_alloc(काष्ठा comedi_device *dev,
					  पूर्णांक n_desc, अचिन्हित पूर्णांक dma_chan1,
					  अचिन्हित पूर्णांक dma_chan2,
					  अचिन्हित पूर्णांक maxsize, अक्षर dma_dir)
अणु
	काष्ठा comedi_isadma *dma = शून्य;
	काष्ठा comedi_isadma_desc *desc;
	अचिन्हित पूर्णांक dma_chans[2];
	पूर्णांक i;

	अगर (n_desc < 1 || n_desc > 2)
		जाओ no_dma;

	dma = kzalloc(माप(*dma), GFP_KERNEL);
	अगर (!dma)
		जाओ no_dma;

	desc = kसुस्मृति(n_desc, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		जाओ no_dma;
	dma->desc = desc;
	dma->n_desc = n_desc;
	अगर (dev->hw_dev) अणु
		dma->dev = dev->hw_dev;
	पूर्ण अन्यथा अणु
		/* Fall back to using the "class" device. */
		अगर (!dev->class_dev)
			जाओ no_dma;
		/* Need 24-bit mask क्रम ISA DMA. */
		अगर (dma_coerce_mask_and_coherent(dev->class_dev,
						 DMA_BIT_MASK(24))) अणु
			जाओ no_dma;
		पूर्ण
		dma->dev = dev->class_dev;
	पूर्ण

	dma_chans[0] = dma_chan1;
	अगर (dma_chan2 == 0 || dma_chan2 == dma_chan1)
		dma_chans[1] = dma_chan1;
	अन्यथा
		dma_chans[1] = dma_chan2;

	अगर (request_dma(dma_chans[0], dev->board_name))
		जाओ no_dma;
	dma->chan = dma_chans[0];
	अगर (dma_chans[1] != dma_chans[0]) अणु
		अगर (request_dma(dma_chans[1], dev->board_name))
			जाओ no_dma;
	पूर्ण
	dma->chan2 = dma_chans[1];

	क्रम (i = 0; i < n_desc; i++) अणु
		desc = &dma->desc[i];
		desc->chan = dma_chans[i];
		desc->maxsize = maxsize;
		desc->virt_addr = dma_alloc_coherent(dma->dev, desc->maxsize,
						     &desc->hw_addr,
						     GFP_KERNEL);
		अगर (!desc->virt_addr)
			जाओ no_dma;
		comedi_isadma_set_mode(desc, dma_dir);
	पूर्ण

	वापस dma;

no_dma:
	comedi_isadma_मुक्त(dma);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_alloc);

/**
 * comedi_isadma_मुक्त - मुक्त the ISA DMA
 * @dma:	the ISA DMA to मुक्त
 */
व्योम comedi_isadma_मुक्त(काष्ठा comedi_isadma *dma)
अणु
	काष्ठा comedi_isadma_desc *desc;
	पूर्णांक i;

	अगर (!dma)
		वापस;

	अगर (dma->desc) अणु
		क्रम (i = 0; i < dma->n_desc; i++) अणु
			desc = &dma->desc[i];
			अगर (desc->virt_addr)
				dma_मुक्त_coherent(dma->dev, desc->maxsize,
						  desc->virt_addr,
						  desc->hw_addr);
		पूर्ण
		kमुक्त(dma->desc);
	पूर्ण
	अगर (dma->chan2 && dma->chan2 != dma->chan)
		मुक्त_dma(dma->chan2);
	अगर (dma->chan)
		मुक्त_dma(dma->chan);
	kमुक्त(dma);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_isadma_मुक्त);

अटल पूर्णांक __init comedi_isadma_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_isadma_init);

अटल व्योम __निकास comedi_isadma_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_isadma_निकास);

MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("Comedi ISA DMA support");
MODULE_LICENSE("GPL");
