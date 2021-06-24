<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Exceet Electronics GmbH
 * Copyright (C) 2018 Bootlin
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 *
 * Helpers needed by the spi or spi-mem logic. Should not be used outside of
 * spi-mem.c and spi.c.
 */

#अगर_अघोषित __LINUX_SPI_INTERNALS_H
#घोषणा __LINUX_SPI_INTERNALS_H

#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spi/spi.h>

व्योम spi_flush_queue(काष्ठा spi_controller *ctrl);

#अगर_घोषित CONFIG_HAS_DMA
पूर्णांक spi_map_buf(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
		काष्ठा sg_table *sgt, व्योम *buf, माप_प्रकार len,
		क्रमागत dma_data_direction dir);
व्योम spi_unmap_buf(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
		   काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir);
#अन्यथा /* !CONFIG_HAS_DMA */
अटल अंतरभूत पूर्णांक spi_map_buf(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
			      काष्ठा sg_table *sgt, व्योम *buf, माप_प्रकार len,
			      क्रमागत dma_data_direction dir)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम spi_unmap_buf(काष्ठा spi_controller *ctlr,
				 काष्ठा device *dev, काष्ठा sg_table *sgt,
				 क्रमागत dma_data_direction dir)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HAS_DMA */

#पूर्ण_अगर /* __LINUX_SPI_INTERNALS_H */
