<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_DMA_H
#घोषणा __ASM_ARCH_DMA_H

#समावेश <linux/types.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>

/*
 * M2P channels.
 *
 * Note that these values are also directly used क्रम setting the PPALLOC
 * रेजिस्टर.
 */
#घोषणा EP93XX_DMA_I2S1		0
#घोषणा EP93XX_DMA_I2S2		1
#घोषणा EP93XX_DMA_AAC1		2
#घोषणा EP93XX_DMA_AAC2		3
#घोषणा EP93XX_DMA_AAC3		4
#घोषणा EP93XX_DMA_I2S3		5
#घोषणा EP93XX_DMA_UART1	6
#घोषणा EP93XX_DMA_UART2	7
#घोषणा EP93XX_DMA_UART3	8
#घोषणा EP93XX_DMA_IRDA		9
/* M2M channels */
#घोषणा EP93XX_DMA_SSP		10
#घोषणा EP93XX_DMA_IDE		11

/**
 * काष्ठा ep93xx_dma_data - configuration data क्रम the EP93xx dmaengine
 * @port: peripheral which is requesting the channel
 * @direction: TX/RX channel
 * @name: optional name क्रम the channel, this is displayed in /proc/पूर्णांकerrupts
 *
 * This inक्रमmation is passed as निजी channel parameter in a filter
 * function. Note that this is only needed क्रम slave/cyclic channels.  For
 * स_नकल channels %शून्य data should be passed.
 */
काष्ठा ep93xx_dma_data अणु
	पूर्णांक				port;
	क्रमागत dma_transfer_direction	direction;
	स्थिर अक्षर			*name;
पूर्ण;

/**
 * काष्ठा ep93xx_dma_chan_data - platक्रमm specअगरic data क्रम a DMA channel
 * @name: name of the channel, used क्रम getting the right घड़ी क्रम the channel
 * @base: mapped रेजिस्टरs
 * @irq: पूर्णांकerrupt number used by this channel
 */
काष्ठा ep93xx_dma_chan_data अणु
	स्थिर अक्षर			*name;
	व्योम __iomem			*base;
	पूर्णांक				irq;
पूर्ण;

/**
 * काष्ठा ep93xx_dma_platक्रमm_data - platक्रमm data क्रम the dmaengine driver
 * @channels: array of channels which are passed to the driver
 * @num_channels: number of channels in the array
 *
 * This काष्ठाure is passed to the DMA engine driver via platक्रमm data. For
 * M2P channels, contract is that even channels are क्रम TX and odd क्रम RX.
 * There is no requirement क्रम the M2M channels.
 */
काष्ठा ep93xx_dma_platक्रमm_data अणु
	काष्ठा ep93xx_dma_chan_data	*channels;
	माप_प्रकार				num_channels;
पूर्ण;

अटल अंतरभूत bool ep93xx_dma_chan_is_m2p(काष्ठा dma_chan *chan)
अणु
	वापस !म_भेद(dev_name(chan->device->dev), "ep93xx-dma-m2p");
पूर्ण

/**
 * ep93xx_dma_chan_direction - वापसs direction the channel can be used
 * @chan: channel
 *
 * This function can be used in filter functions to find out whether the
 * channel supports given DMA direction. Only M2P channels have such
 * limitation, क्रम M2M channels the direction is configurable.
 */
अटल अंतरभूत क्रमागत dma_transfer_direction
ep93xx_dma_chan_direction(काष्ठा dma_chan *chan)
अणु
	अगर (!ep93xx_dma_chan_is_m2p(chan))
		वापस DMA_TRANS_NONE;

	/* even channels are क्रम TX, odd क्रम RX */
	वापस (chan->chan_id % 2 == 0) ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
पूर्ण

#पूर्ण_अगर /* __ASM_ARCH_DMA_H */
