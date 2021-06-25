<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale SPI/eSPI controller driver library.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 * Copyright (C) 2006 Polycom, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */
#अगर_अघोषित __SPI_FSL_LIB_H__
#घोषणा __SPI_FSL_LIB_H__

#समावेश <यंत्र/पन.स>

/* SPI/eSPI Controller driver's निजी data. */
काष्ठा mpc8xxx_spi अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_base;

	/* rx & tx bufs from the spi_transfer */
	स्थिर व्योम *tx;
	व्योम *rx;

	पूर्णांक subblock;
	काष्ठा spi_pram __iomem *pram;
#अगर_घोषित CONFIG_FSL_SOC
	काष्ठा cpm_buf_desc __iomem *tx_bd;
	काष्ठा cpm_buf_desc __iomem *rx_bd;
#पूर्ण_अगर

	काष्ठा spi_transfer *xfer_in_progress;

	/* dma addresses क्रम CPM transfers */
	dma_addr_t tx_dma;
	dma_addr_t rx_dma;
	bool map_tx_dma;
	bool map_rx_dma;

	dma_addr_t dma_dummy_tx;
	dma_addr_t dma_dummy_rx;

	/* functions to deal with dअगरferent sized buffers */
	व्योम (*get_rx) (u32 rx_data, काष्ठा mpc8xxx_spi *);
	u32(*get_tx) (काष्ठा mpc8xxx_spi *);

	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक irq;

	अचिन्हित nsecs;		/* (घड़ी cycle समय)/2 */

	u32 spibrg;		/* SPIBRG input घड़ी */
	u32 rx_shअगरt;		/* RX data reg shअगरt when in qe mode */
	u32 tx_shअगरt;		/* TX data reg shअगरt when in qe mode */

	अचिन्हित पूर्णांक flags;

#अगर IS_ENABLED(CONFIG_SPI_FSL_SPI)
	पूर्णांक type;
	पूर्णांक native_chipselects;
	u8 max_bits_per_word;

	व्योम (*set_shअगरts)(u32 *rx_shअगरt, u32 *tx_shअगरt,
			   पूर्णांक bits_per_word, पूर्णांक msb_first);
#पूर्ण_अगर

	काष्ठा completion करोne;
पूर्ण;

काष्ठा spi_mpc8xxx_cs अणु
	/* functions to deal with dअगरferent sized buffers */
	व्योम (*get_rx) (u32 rx_data, काष्ठा mpc8xxx_spi *);
	u32 (*get_tx) (काष्ठा mpc8xxx_spi *);
	u32 rx_shअगरt;		/* RX data reg shअगरt when in qe mode */
	u32 tx_shअगरt;		/* TX data reg shअगरt when in qe mode */
	u32 hw_mode;		/* Holds HW mode रेजिस्टर settings */
पूर्ण;

अटल अंतरभूत व्योम mpc8xxx_spi_ग_लिखो_reg(__be32 __iomem *reg, u32 val)
अणु
	ioग_लिखो32be(val, reg);
पूर्ण

अटल अंतरभूत u32 mpc8xxx_spi_पढ़ो_reg(__be32 __iomem *reg)
अणु
	वापस ioपढ़ो32be(reg);
पूर्ण

काष्ठा mpc8xxx_spi_probe_info अणु
	काष्ठा fsl_spi_platक्रमm_data pdata;
	__be32 __iomem *immr_spi_cs;
पूर्ण;

बाह्य u32 mpc8xxx_spi_tx_buf_u8(काष्ठा mpc8xxx_spi *mpc8xxx_spi);
बाह्य u32 mpc8xxx_spi_tx_buf_u16(काष्ठा mpc8xxx_spi *mpc8xxx_spi);
बाह्य u32 mpc8xxx_spi_tx_buf_u32(काष्ठा mpc8xxx_spi *mpc8xxx_spi);
बाह्य व्योम mpc8xxx_spi_rx_buf_u8(u32 data, काष्ठा mpc8xxx_spi *mpc8xxx_spi);
बाह्य व्योम mpc8xxx_spi_rx_buf_u16(u32 data, काष्ठा mpc8xxx_spi *mpc8xxx_spi);
बाह्य व्योम mpc8xxx_spi_rx_buf_u32(u32 data, काष्ठा mpc8xxx_spi *mpc8xxx_spi);

बाह्य काष्ठा mpc8xxx_spi_probe_info *to_of_pinfo(
		काष्ठा fsl_spi_platक्रमm_data *pdata);
बाह्य पूर्णांक mpc8xxx_spi_bufs(काष्ठा mpc8xxx_spi *mspi,
		काष्ठा spi_transfer *t, अचिन्हित पूर्णांक len);
बाह्य स्थिर अक्षर *mpc8xxx_spi_strmode(अचिन्हित पूर्णांक flags);
बाह्य व्योम mpc8xxx_spi_probe(काष्ठा device *dev, काष्ठा resource *mem,
		अचिन्हित पूर्णांक irq);
बाह्य पूर्णांक mpc8xxx_spi_हटाओ(काष्ठा device *dev);
बाह्य पूर्णांक of_mpc8xxx_spi_probe(काष्ठा platक्रमm_device *ofdev);

#पूर्ण_अगर /* __SPI_FSL_LIB_H__ */
