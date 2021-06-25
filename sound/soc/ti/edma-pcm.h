<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * edma-pcm.h - eDMA PCM driver using dmaengine क्रम AM3xxx, AM4xxx
 *
 * Copyright (C) 2014 Texas Instruments, Inc.
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Based on: sound/soc/tegra/tegra_pcm.h
 */

#अगर_अघोषित __EDMA_PCM_H__
#घोषणा __EDMA_PCM_H__

#अगर IS_ENABLED(CONFIG_SND_SOC_TI_EDMA_PCM)
पूर्णांक edma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक edma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_SOC_TI_EDMA_PCM */

#पूर्ण_अगर /* __EDMA_PCM_H__ */
