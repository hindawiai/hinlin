<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * COMEDI ISA DMA support functions
 * Copyright (c) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 */

#अगर_अघोषित _COMEDI_ISADMA_H
#घोषणा _COMEDI_ISADMA_H

#समावेश <linux/types.h>

काष्ठा comedi_device;
काष्ठा device;

/*
 * These are used to aव्योम issues when <यंत्र/dma.h> and the DMA_MODE_
 * defines are not available.
 */
#घोषणा COMEDI_ISADMA_READ	0
#घोषणा COMEDI_ISADMA_WRITE	1

/**
 * काष्ठा comedi_isadma_desc - cookie क्रम ISA DMA
 * @virt_addr:	भव address of buffer
 * @hw_addr:	hardware (bus) address of buffer
 * @chan:	DMA channel
 * @maxsize:	allocated size of buffer (in bytes)
 * @size:	transfer size (in bytes)
 * @mode:	DMA_MODE_READ or DMA_MODE_WRITE
 */
काष्ठा comedi_isadma_desc अणु
	व्योम *virt_addr;
	dma_addr_t hw_addr;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक maxsize;
	अचिन्हित पूर्णांक size;
	अक्षर mode;
पूर्ण;

/**
 * काष्ठा comedi_isadma - ISA DMA data
 * @dev:	device to allocate non-coherent memory क्रम
 * @desc:	cookie क्रम each DMA buffer
 * @n_desc:	the number of cookies
 * @cur_dma:	the current cookie in use
 * @chan:	the first DMA channel requested
 * @chan2:	the second DMA channel requested
 */
काष्ठा comedi_isadma अणु
	काष्ठा device *dev;
	काष्ठा comedi_isadma_desc *desc;
	पूर्णांक n_desc;
	पूर्णांक cur_dma;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक chan2;
पूर्ण;

#अगर IS_ENABLED(CONFIG_ISA_DMA_API)

व्योम comedi_isadma_program(काष्ठा comedi_isadma_desc *desc);
अचिन्हित पूर्णांक comedi_isadma_disable(अचिन्हित पूर्णांक dma_chan);
अचिन्हित पूर्णांक comedi_isadma_disable_on_sample(अचिन्हित पूर्णांक dma_chan,
					     अचिन्हित पूर्णांक size);
अचिन्हित पूर्णांक comedi_isadma_poll(काष्ठा comedi_isadma *dma);
व्योम comedi_isadma_set_mode(काष्ठा comedi_isadma_desc *desc, अक्षर dma_dir);

काष्ठा comedi_isadma *comedi_isadma_alloc(काष्ठा comedi_device *dev,
					  पूर्णांक n_desc, अचिन्हित पूर्णांक dma_chan1,
					  अचिन्हित पूर्णांक dma_chan2,
					  अचिन्हित पूर्णांक maxsize, अक्षर dma_dir);
व्योम comedi_isadma_मुक्त(काष्ठा comedi_isadma *dma);

#अन्यथा	/* !IS_ENABLED(CONFIG_ISA_DMA_API) */

अटल अंतरभूत व्योम comedi_isadma_program(काष्ठा comedi_isadma_desc *desc)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक comedi_isadma_disable(अचिन्हित पूर्णांक dma_chan)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
comedi_isadma_disable_on_sample(अचिन्हित पूर्णांक dma_chan, अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक comedi_isadma_poll(काष्ठा comedi_isadma *dma)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम comedi_isadma_set_mode(काष्ठा comedi_isadma_desc *desc,
					  अक्षर dma_dir)
अणु
पूर्ण

अटल अंतरभूत काष्ठा comedi_isadma *
comedi_isadma_alloc(काष्ठा comedi_device *dev, पूर्णांक n_desc,
		    अचिन्हित पूर्णांक dma_chan1, अचिन्हित पूर्णांक dma_chan2,
		    अचिन्हित पूर्णांक maxsize, अक्षर dma_dir)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम comedi_isadma_मुक्त(काष्ठा comedi_isadma *dma)
अणु
पूर्ण

#पूर्ण_अगर	/* !IS_ENABLED(CONFIG_ISA_DMA_API) */

#पूर्ण_अगर	/* #अगर_अघोषित _COMEDI_ISADMA_H */
