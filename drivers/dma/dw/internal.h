<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2013 Intel Corporation
 */

#अगर_अघोषित _DMA_DW_INTERNAL_H
#घोषणा _DMA_DW_INTERNAL_H

#समावेश <linux/dma/dw.h>

#समावेश "regs.h"

पूर्णांक करो_dma_probe(काष्ठा dw_dma_chip *chip);
पूर्णांक करो_dma_हटाओ(काष्ठा dw_dma_chip *chip);

व्योम करो_dw_dma_on(काष्ठा dw_dma *dw);
व्योम करो_dw_dma_off(काष्ठा dw_dma *dw);

पूर्णांक करो_dw_dma_disable(काष्ठा dw_dma_chip *chip);
पूर्णांक करो_dw_dma_enable(काष्ठा dw_dma_chip *chip);

बाह्य bool dw_dma_filter(काष्ठा dma_chan *chan, व्योम *param);

#अगर_घोषित CONFIG_ACPI
व्योम dw_dma_acpi_controller_रेजिस्टर(काष्ठा dw_dma *dw);
व्योम dw_dma_acpi_controller_मुक्त(काष्ठा dw_dma *dw);
#अन्यथा /* !CONFIG_ACPI */
अटल अंतरभूत व्योम dw_dma_acpi_controller_रेजिस्टर(काष्ठा dw_dma *dw) अणुपूर्ण
अटल अंतरभूत व्योम dw_dma_acpi_controller_मुक्त(काष्ठा dw_dma *dw) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_ACPI */

काष्ठा platक्रमm_device;

#अगर_घोषित CONFIG_OF
काष्ठा dw_dma_platक्रमm_data *dw_dma_parse_dt(काष्ठा platक्रमm_device *pdev);
व्योम dw_dma_of_controller_रेजिस्टर(काष्ठा dw_dma *dw);
व्योम dw_dma_of_controller_मुक्त(काष्ठा dw_dma *dw);
#अन्यथा
अटल अंतरभूत काष्ठा dw_dma_platक्रमm_data *dw_dma_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dw_dma_of_controller_रेजिस्टर(काष्ठा dw_dma *dw) अणुपूर्ण
अटल अंतरभूत व्योम dw_dma_of_controller_मुक्त(काष्ठा dw_dma *dw) अणुपूर्ण
#पूर्ण_अगर

काष्ठा dw_dma_chip_pdata अणु
	स्थिर काष्ठा dw_dma_platक्रमm_data *pdata;
	पूर्णांक (*probe)(काष्ठा dw_dma_chip *chip);
	पूर्णांक (*हटाओ)(काष्ठा dw_dma_chip *chip);
	काष्ठा dw_dma_chip *chip;
पूर्ण;

अटल __maybe_unused स्थिर काष्ठा dw_dma_chip_pdata dw_dma_chip_pdata = अणु
	.probe = dw_dma_probe,
	.हटाओ = dw_dma_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा dw_dma_platक्रमm_data idma32_pdata = अणु
	.nr_channels = 8,
	.chan_allocation_order = CHAN_ALLOCATION_ASCENDING,
	.chan_priority = CHAN_PRIORITY_ASCENDING,
	.block_size = 131071,
	.nr_masters = 1,
	.data_width = अणु4पूर्ण,
	.multi_block = अणु1, 1, 1, 1, 1, 1, 1, 1पूर्ण,
पूर्ण;

अटल __maybe_unused स्थिर काष्ठा dw_dma_chip_pdata idma32_chip_pdata = अणु
	.pdata = &idma32_pdata,
	.probe = idma32_dma_probe,
	.हटाओ = idma32_dma_हटाओ,
पूर्ण;

#पूर्ण_अगर /* _DMA_DW_INTERNAL_H */
