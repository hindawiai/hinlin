<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale SPI controller driver cpm functions.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 * Copyright 2010 Freescale Semiconductor, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित __SPI_FSL_CPM_H__
#घोषणा __SPI_FSL_CPM_H__

#समावेश "spi-fsl-lib.h"

#अगर_घोषित CONFIG_FSL_SOC
बाह्य व्योम fsl_spi_cpm_reinit_txrx(काष्ठा mpc8xxx_spi *mspi);
बाह्य पूर्णांक fsl_spi_cpm_bufs(काष्ठा mpc8xxx_spi *mspi,
			    काष्ठा spi_transfer *t, bool is_dma_mapped);
बाह्य व्योम fsl_spi_cpm_bufs_complete(काष्ठा mpc8xxx_spi *mspi);
बाह्य व्योम fsl_spi_cpm_irq(काष्ठा mpc8xxx_spi *mspi, u32 events);
बाह्य पूर्णांक fsl_spi_cpm_init(काष्ठा mpc8xxx_spi *mspi);
बाह्य व्योम fsl_spi_cpm_मुक्त(काष्ठा mpc8xxx_spi *mspi);
#अन्यथा
अटल अंतरभूत व्योम fsl_spi_cpm_reinit_txrx(काष्ठा mpc8xxx_spi *mspi) अणु पूर्ण
अटल अंतरभूत पूर्णांक fsl_spi_cpm_bufs(काष्ठा mpc8xxx_spi *mspi,
				   काष्ठा spi_transfer *t,
				   bool is_dma_mapped) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम fsl_spi_cpm_bufs_complete(काष्ठा mpc8xxx_spi *mspi) अणु पूर्ण
अटल अंतरभूत व्योम fsl_spi_cpm_irq(काष्ठा mpc8xxx_spi *mspi, u32 events) अणु पूर्ण
अटल अंतरभूत पूर्णांक fsl_spi_cpm_init(काष्ठा mpc8xxx_spi *mspi) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम fsl_spi_cpm_मुक्त(काष्ठा mpc8xxx_spi *mspi) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SPI_FSL_CPM_H__ */
