<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00mmio
	Abstract: Data काष्ठाures क्रम the rt2x00mmio module.
 */

#अगर_अघोषित RT2X00MMIO_H
#घोषणा RT2X00MMIO_H

#समावेश <linux/पन.स>

/*
 * Register access.
 */
अटल अंतरभूत u32 rt2x00mmio_रेजिस्टर_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
					   स्थिर अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(rt2x00dev->csr.base + offset);
पूर्ण

अटल अंतरभूत व्योम rt2x00mmio_रेजिस्टर_multiपढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
						 स्थिर अचिन्हित पूर्णांक offset,
						 व्योम *value, स्थिर u32 length)
अणु
	स_नकल_fromio(value, rt2x00dev->csr.base + offset, length);
पूर्ण

अटल अंतरभूत व्योम rt2x00mmio_रेजिस्टर_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
					     स्थिर अचिन्हित पूर्णांक offset,
					     u32 value)
अणु
	ग_लिखोl(value, rt2x00dev->csr.base + offset);
पूर्ण

अटल अंतरभूत व्योम rt2x00mmio_रेजिस्टर_multiग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
						  स्थिर अचिन्हित पूर्णांक offset,
						  स्थिर व्योम *value,
						  स्थिर u32 length)
अणु
	__ioग_लिखो32_copy(rt2x00dev->csr.base + offset, value, length >> 2);
पूर्ण

/**
 * rt2x00mmio_regbusy_पढ़ो - Read from रेजिस्टर with busy check
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @field: Field to check अगर रेजिस्टर is busy
 * @reg: Poपूर्णांकer to where रेजिस्टर contents should be stored
 *
 * This function will पढ़ो the given रेजिस्टर, and checks अगर the
 * रेजिस्टर is busy. If it is, it will sleep क्रम a couple of
 * microseconds beक्रमe पढ़ोing the रेजिस्टर again. If the रेजिस्टर
 * is not पढ़ो after a certain समयout, this function will वापस
 * FALSE.
 */
पूर्णांक rt2x00mmio_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			    स्थिर अचिन्हित पूर्णांक offset,
			    स्थिर काष्ठा rt2x00_field32 field,
			    u32 *reg);

/**
 * काष्ठा queue_entry_priv_mmio: Per entry PCI specअगरic inक्रमmation
 *
 * @desc: Poपूर्णांकer to device descriptor
 * @desc_dma: DMA poपूर्णांकer to &desc.
 */
काष्ठा queue_entry_priv_mmio अणु
	__le32 *desc;
	dma_addr_t desc_dma;
पूर्ण;

/**
 * rt2x00mmio_rxकरोne - Handle RX करोne events
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 *
 * Returns true अगर there are still rx frames pending and false अगर all
 * pending rx frames were processed.
 */
bool rt2x00mmio_rxकरोne(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * rt2x00mmio_flush_queue - Flush data queue
 * @queue: Data queue to stop
 * @drop: True to drop all pending frames.
 *
 * This will रुको क्रम a maximum of 100ms, रुकोing क्रम the queues
 * to become empty.
 */
व्योम rt2x00mmio_flush_queue(काष्ठा data_queue *queue, bool drop);

/*
 * Device initialization handlers.
 */
पूर्णांक rt2x00mmio_initialize(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00mmio_uninitialize(काष्ठा rt2x00_dev *rt2x00dev);

#पूर्ण_अगर /* RT2X00MMIO_H */
