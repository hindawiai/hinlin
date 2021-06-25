<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MXS_DMA_H_
#घोषणा _MXS_DMA_H_

#समावेश <linux/dmaengine.h>

#घोषणा MXS_DMA_CTRL_WAIT4END	BIT(31)
#घोषणा MXS_DMA_CTRL_WAIT4RDY	BIT(30)

/*
 * The mxs dmaengine can करो PIO transfers. We pass a poपूर्णांकer to the PIO words
 * in the second argument to dmaengine_prep_slave_sg when the direction is
 * set to DMA_TRANS_NONE. To make this clear and to prevent users from करोing
 * the error prone casting we have this wrapper function
 */
अटल अंतरभूत काष्ठा dma_async_tx_descriptor *mxs_dmaengine_prep_pio(
        काष्ठा dma_chan *chan, u32 *pio, अचिन्हित पूर्णांक npio,
        क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	वापस dmaengine_prep_slave_sg(chan, (काष्ठा scatterlist *)pio, npio,
				       dir, flags);
पूर्ण

#पूर्ण_अगर /* _MXS_DMA_H_ */
