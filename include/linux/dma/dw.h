<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 * Copyright (C) 2010-2011 ST Microelectronics
 * Copyright (C) 2014 Intel Corporation
 */
#अगर_अघोषित _DMA_DW_H
#घोषणा _DMA_DW_H

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>

#समावेश <linux/platक्रमm_data/dma-dw.h>

काष्ठा dw_dma;

/**
 * काष्ठा dw_dma_chip - representation of DesignWare DMA controller hardware
 * @dev:		काष्ठा device of the DMA controller
 * @id:			instance ID
 * @irq:		irq line
 * @regs:		memory mapped I/O space
 * @clk:		hclk घड़ी
 * @dw:			काष्ठा dw_dma that is filed by dw_dma_probe()
 * @pdata:		poपूर्णांकer to platक्रमm data
 */
काष्ठा dw_dma_chip अणु
	काष्ठा device	*dev;
	पूर्णांक		id;
	पूर्णांक		irq;
	व्योम __iomem	*regs;
	काष्ठा clk	*clk;
	काष्ठा dw_dma	*dw;

	स्थिर काष्ठा dw_dma_platक्रमm_data	*pdata;
पूर्ण;

/* Export to the platक्रमm drivers */
#अगर IS_ENABLED(CONFIG_DW_DMAC_CORE)
पूर्णांक dw_dma_probe(काष्ठा dw_dma_chip *chip);
पूर्णांक dw_dma_हटाओ(काष्ठा dw_dma_chip *chip);
पूर्णांक idma32_dma_probe(काष्ठा dw_dma_chip *chip);
पूर्णांक idma32_dma_हटाओ(काष्ठा dw_dma_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक dw_dma_probe(काष्ठा dw_dma_chip *chip) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक dw_dma_हटाओ(काष्ठा dw_dma_chip *chip) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक idma32_dma_probe(काष्ठा dw_dma_chip *chip) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक idma32_dma_हटाओ(काष्ठा dw_dma_chip *chip) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_DW_DMAC_CORE */

#पूर्ण_अगर /* _DMA_DW_H */
