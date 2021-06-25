<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ni_labpc ISA DMA support.
 */

#अगर_अघोषित _NI_LABPC_ISADMA_H
#घोषणा _NI_LABPC_ISADMA_H

#अगर IS_ENABLED(CONFIG_COMEDI_NI_LABPC_ISADMA)

व्योम labpc_init_dma_chan(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक dma_chan);
व्योम labpc_मुक्त_dma_chan(काष्ठा comedi_device *dev);
व्योम labpc_setup_dma(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s);
व्योम labpc_drain_dma(काष्ठा comedi_device *dev);
व्योम labpc_handle_dma_status(काष्ठा comedi_device *dev);

#अन्यथा

अटल अंतरभूत व्योम labpc_init_dma_chan(काष्ठा comedi_device *dev,
				       अचिन्हित पूर्णांक dma_chan)
अणु
पूर्ण

अटल अंतरभूत व्योम labpc_मुक्त_dma_chan(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम labpc_setup_dma(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s)
अणु
पूर्ण

अटल अंतरभूत व्योम labpc_drain_dma(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम labpc_handle_dma_status(काष्ठा comedi_device *dev)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _NI_LABPC_ISADMA_H */
