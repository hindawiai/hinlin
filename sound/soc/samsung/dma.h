<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ALSA PCM पूर्णांकerface क्रम the Samsung SoC
 */

#अगर_अघोषित _SAMSUNG_DMA_H
#घोषणा _SAMSUNG_DMA_H

#समावेश <sound/dmaengine_pcm.h>

/*
 * @tx, @rx arguments can be शून्य अगर the DMA channel names are "tx", "rx",
 * otherwise actual DMA channel names must be passed to this function.
 */
पूर्णांक samsung_asoc_dma_platक्रमm_रेजिस्टर(काष्ठा device *dev, dma_filter_fn filter,
				       स्थिर अक्षर *tx, स्थिर अक्षर *rx,
				       काष्ठा device *dma_dev);
#पूर्ण_अगर /* _SAMSUNG_DMA_H */
