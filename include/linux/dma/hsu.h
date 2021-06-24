<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the High Speed UART DMA
 *
 * Copyright (C) 2015 Intel Corporation
 */

#अगर_अघोषित _DMA_HSU_H
#घोषणा _DMA_HSU_H

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/platक्रमm_data/dma-hsu.h>

काष्ठा hsu_dma;

/**
 * काष्ठा hsu_dma_chip - representation of HSU DMA hardware
 * @dev:		 काष्ठा device of the DMA controller
 * @irq:		 irq line
 * @regs:		 memory mapped I/O space
 * @length:		 I/O space length
 * @offset:		 offset of the I/O space where रेजिस्टरs are located
 * @hsu:		 काष्ठा hsu_dma that is filed by ->probe()
 * @pdata:		 platक्रमm data क्रम the DMA controller अगर provided
 */
काष्ठा hsu_dma_chip अणु
	काष्ठा device			*dev;
	पूर्णांक				irq;
	व्योम __iomem			*regs;
	अचिन्हित पूर्णांक			length;
	अचिन्हित पूर्णांक			offset;
	काष्ठा hsu_dma			*hsu;
पूर्ण;

#अगर IS_ENABLED(CONFIG_HSU_DMA)
/* Export to the पूर्णांकernal users */
पूर्णांक hsu_dma_get_status(काष्ठा hsu_dma_chip *chip, अचिन्हित लघु nr,
		       u32 *status);
पूर्णांक hsu_dma_करो_irq(काष्ठा hsu_dma_chip *chip, अचिन्हित लघु nr, u32 status);

/* Export to the platक्रमm drivers */
पूर्णांक hsu_dma_probe(काष्ठा hsu_dma_chip *chip);
पूर्णांक hsu_dma_हटाओ(काष्ठा hsu_dma_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक hsu_dma_get_status(काष्ठा hsu_dma_chip *chip,
				     अचिन्हित लघु nr, u32 *status)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक hsu_dma_करो_irq(काष्ठा hsu_dma_chip *chip, अचिन्हित लघु nr,
				 u32 status)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक hsu_dma_probe(काष्ठा hsu_dma_chip *chip) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक hsu_dma_हटाओ(काष्ठा hsu_dma_chip *chip) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_HSU_DMA */

#पूर्ण_अगर /* _DMA_HSU_H */
