<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __SPRD_MCDT_H
#घोषणा __SPRD_MCDT_H

क्रमागत sprd_mcdt_channel_type अणु
	SPRD_MCDT_DAC_CHAN,
	SPRD_MCDT_ADC_CHAN,
	SPRD_MCDT_UNKNOWN_CHAN,
पूर्ण;

क्रमागत sprd_mcdt_dma_chan अणु
	SPRD_MCDT_DMA_CH0,
	SPRD_MCDT_DMA_CH1,
	SPRD_MCDT_DMA_CH2,
	SPRD_MCDT_DMA_CH3,
	SPRD_MCDT_DMA_CH4,
पूर्ण;

काष्ठा sprd_mcdt_chan_callback अणु
	व्योम (*notअगरy)(व्योम *data);
	व्योम *data;
पूर्ण;

/**
 * काष्ठा sprd_mcdt_chan - this काष्ठा represents a single channel instance
 * @mcdt: the mcdt controller
 * @id: channel id
 * @fअगरo_phys: channel fअगरo physical address which is used क्रम DMA transfer
 * @type: channel type
 * @cb: channel fअगरo पूर्णांकerrupt's callback पूर्णांकerface to notअगरy the fअगरo events
 * @dma_enable: indicate अगर use DMA mode to transfer data
 * @पूर्णांक_enable: indicate अगर use पूर्णांकerrupt mode to notअगरy users to पढ़ो or
 * ग_लिखो data manually
 * @list: used to link पूर्णांकo the global list
 *
 * Note: users should not modअगरy any members of this काष्ठाure.
 */
काष्ठा sprd_mcdt_chan अणु
	काष्ठा sprd_mcdt_dev *mcdt;
	u8 id;
	अचिन्हित दीर्घ fअगरo_phys;
	क्रमागत sprd_mcdt_channel_type type;
	क्रमागत sprd_mcdt_dma_chan dma_chan;
	काष्ठा sprd_mcdt_chan_callback *cb;
	bool dma_enable;
	bool पूर्णांक_enable;
	काष्ठा list_head list;
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_SOC_SPRD_MCDT)
काष्ठा sprd_mcdt_chan *sprd_mcdt_request_chan(u8 channel,
					      क्रमागत sprd_mcdt_channel_type type);
व्योम sprd_mcdt_मुक्त_chan(काष्ठा sprd_mcdt_chan *chan);

पूर्णांक sprd_mcdt_chan_ग_लिखो(काष्ठा sprd_mcdt_chan *chan, अक्षर *tx_buf, u32 size);
पूर्णांक sprd_mcdt_chan_पढ़ो(काष्ठा sprd_mcdt_chan *chan, अक्षर *rx_buf, u32 size);
पूर्णांक sprd_mcdt_chan_पूर्णांक_enable(काष्ठा sprd_mcdt_chan *chan, u32 water_mark,
			      काष्ठा sprd_mcdt_chan_callback *cb);
व्योम sprd_mcdt_chan_पूर्णांक_disable(काष्ठा sprd_mcdt_chan *chan);

पूर्णांक sprd_mcdt_chan_dma_enable(काष्ठा sprd_mcdt_chan *chan,
			      क्रमागत sprd_mcdt_dma_chan dma_chan, u32 water_mark);
व्योम sprd_mcdt_chan_dma_disable(काष्ठा sprd_mcdt_chan *chan);

#अन्यथा

काष्ठा sprd_mcdt_chan *sprd_mcdt_request_chan(u8 channel,
					      क्रमागत sprd_mcdt_channel_type type)
अणु
	वापस शून्य;
पूर्ण

व्योम sprd_mcdt_मुक्त_chan(काष्ठा sprd_mcdt_chan *chan)
अणु पूर्ण

पूर्णांक sprd_mcdt_chan_ग_लिखो(काष्ठा sprd_mcdt_chan *chan, अक्षर *tx_buf, u32 size)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक sprd_mcdt_chan_पढ़ो(काष्ठा sprd_mcdt_chan *chan, अक्षर *rx_buf, u32 size)
अणु
	वापस 0;
पूर्ण

पूर्णांक sprd_mcdt_chan_पूर्णांक_enable(काष्ठा sprd_mcdt_chan *chan, u32 water_mark,
			      काष्ठा sprd_mcdt_chan_callback *cb)
अणु
	वापस -EINVAL;
पूर्ण

व्योम sprd_mcdt_chan_पूर्णांक_disable(काष्ठा sprd_mcdt_chan *chan)
अणु पूर्ण

पूर्णांक sprd_mcdt_chan_dma_enable(काष्ठा sprd_mcdt_chan *chan,
			      क्रमागत sprd_mcdt_dma_chan dma_chan, u32 water_mark)
अणु
	वापस -EINVAL;
पूर्ण

व्योम sprd_mcdt_chan_dma_disable(काष्ठा sprd_mcdt_chan *chan)
अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __SPRD_MCDT_H */
