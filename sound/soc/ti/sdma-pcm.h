<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#अगर_अघोषित __SDMA_PCM_H__
#घोषणा __SDMA_PCM_H__

#अगर IS_ENABLED(CONFIG_SND_SOC_TI_SDMA_PCM)
पूर्णांक sdma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev,
			       अक्षर *txdmachan, अक्षर *rxdmachan);
#अन्यथा
अटल अंतरभूत पूर्णांक sdma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev,
					     अक्षर *txdmachan, अक्षर *rxdmachan)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_SOC_TI_SDMA_PCM */

#पूर्ण_अगर /* __SDMA_PCM_H__ */
