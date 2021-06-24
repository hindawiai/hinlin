<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/ni_labpc_isadma.c
 * ISA DMA support क्रम National Instruments Lab-PC series boards and
 * compatibles.
 *
 * Extracted from ni_labpc.c:
 * Copyright (C) 2001-2003 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "../comedidev.h"

#समावेश "comedi_isadma.h"
#समावेश "ni_labpc.h"
#समावेश "ni_labpc_regs.h"
#समावेश "ni_labpc_isadma.h"

/* size in bytes of dma buffer */
#घोषणा LABPC_ISADMA_BUFFER_SIZE	0xff00

/* utility function that suggests a dma transfer size in bytes */
अटल अचिन्हित पूर्णांक labpc_suggest_transfer_size(काष्ठा comedi_device *dev,
						काष्ठा comedi_subdevice *s,
						अचिन्हित पूर्णांक maxbytes)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक sample_size = comedi_bytes_per_sample(s);
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक freq;

	अगर (cmd->convert_src == TRIG_TIMER)
		freq = 1000000000 / cmd->convert_arg;
	अन्यथा
		/* वापस some शेष value */
		freq = 0xffffffff;

	/* make buffer fill in no more than 1/3 second */
	size = (freq / 3) * sample_size;

	/* set a minimum and maximum size allowed */
	अगर (size > maxbytes)
		size = maxbytes;
	अन्यथा अगर (size < sample_size)
		size = sample_size;

	वापस size;
पूर्ण

व्योम labpc_setup_dma(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma_desc *desc = &devpriv->dma->desc[0];
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक sample_size = comedi_bytes_per_sample(s);

	/* set appropriate size of transfer */
	desc->size = labpc_suggest_transfer_size(dev, s, desc->maxsize);
	अगर (cmd->stop_src == TRIG_COUNT &&
	    devpriv->count * sample_size < desc->size)
		desc->size = devpriv->count * sample_size;

	comedi_isadma_program(desc);

	/* set CMD3 bits क्रम caller to enable DMA and पूर्णांकerrupt */
	devpriv->cmd3 |= (CMD3_DMAEN | CMD3_DMATCINTEN);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_setup_dma);

व्योम labpc_drain_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma_desc *desc = &devpriv->dma->desc[0];
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक max_samples = comedi_bytes_to_samples(s, desc->size);
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक leftover;

	/*
	 * residue is the number of bytes left to be करोne on the dma
	 * transfer.  It should always be zero at this poपूर्णांक unless
	 * the stop_src is set to बाह्यal triggering.
	 */
	residue = comedi_isadma_disable(desc->chan);

	/*
	 * Figure out how many samples to पढ़ो क्रम this transfer and
	 * how many will be stored क्रम next समय.
	 */
	nsamples = max_samples - comedi_bytes_to_samples(s, residue);
	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अगर (devpriv->count <= nsamples) अणु
			nsamples = devpriv->count;
			leftover = 0;
		पूर्ण अन्यथा अणु
			leftover = devpriv->count - nsamples;
			अगर (leftover > max_samples)
				leftover = max_samples;
		पूर्ण
		devpriv->count -= nsamples;
	पूर्ण अन्यथा अणु
		leftover = max_samples;
	पूर्ण
	desc->size = comedi_samples_to_bytes(s, leftover);

	comedi_buf_ग_लिखो_samples(s, desc->virt_addr, nsamples);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_drain_dma);

अटल व्योम handle_isa_dma(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;
	काष्ठा comedi_isadma_desc *desc = &devpriv->dma->desc[0];

	labpc_drain_dma(dev);

	अगर (desc->size)
		comedi_isadma_program(desc);

	/* clear dma tc पूर्णांकerrupt */
	devpriv->ग_लिखो_byte(dev, 0x1, DMATC_CLEAR_REG);
पूर्ण

व्योम labpc_handle_dma_status(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा labpc_boardinfo *board = dev->board_ptr;
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	/*
	 * अगर a dma terminal count of बाह्यal stop trigger
	 * has occurred
	 */
	अगर (devpriv->stat1 & STAT1_GATA0 ||
	    (board->is_labpc1200 && devpriv->stat2 & STAT2_OUTA1))
		handle_isa_dma(dev);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_handle_dma_status);

व्योम labpc_init_dma_chan(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक dma_chan)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	/* only DMA channels 3 and 1 are valid */
	अगर (dma_chan != 1 && dma_chan != 3)
		वापस;

	/* DMA uses 1 buffer */
	devpriv->dma = comedi_isadma_alloc(dev, 1, dma_chan, dma_chan,
					   LABPC_ISADMA_BUFFER_SIZE,
					   COMEDI_ISADMA_READ);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_init_dma_chan);

व्योम labpc_मुक्त_dma_chan(काष्ठा comedi_device *dev)
अणु
	काष्ठा labpc_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		comedi_isadma_मुक्त(devpriv->dma);
पूर्ण
EXPORT_SYMBOL_GPL(labpc_मुक्त_dma_chan);

अटल पूर्णांक __init ni_labpc_isadma_init_module(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(ni_labpc_isadma_init_module);

अटल व्योम __निकास ni_labpc_isadma_cleanup_module(व्योम)
अणु
पूर्ण
module_निकास(ni_labpc_isadma_cleanup_module);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi NI Lab-PC ISA DMA support");
MODULE_LICENSE("GPL");
