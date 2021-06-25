<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA core driver
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#अगर_अघोषित _DW_EDMA_H
#घोषणा _DW_EDMA_H

#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>

काष्ठा dw_edma;

/**
 * काष्ठा dw_edma_chip - representation of DesignWare eDMA controller hardware
 * @dev:		 काष्ठा device of the eDMA controller
 * @id:			 instance ID
 * @irq:		 irq line
 * @dw:			 काष्ठा dw_edma that is filed by dw_edma_probe()
 */
काष्ठा dw_edma_chip अणु
	काष्ठा device		*dev;
	पूर्णांक			id;
	पूर्णांक			irq;
	काष्ठा dw_edma		*dw;
पूर्ण;

/* Export to the platक्रमm drivers */
#अगर IS_ENABLED(CONFIG_DW_EDMA)
पूर्णांक dw_edma_probe(काष्ठा dw_edma_chip *chip);
पूर्णांक dw_edma_हटाओ(काष्ठा dw_edma_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक dw_edma_probe(काष्ठा dw_edma_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dw_edma_हटाओ(काष्ठा dw_edma_chip *chip)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DW_EDMA */

#पूर्ण_अगर /* _DW_EDMA_H */
