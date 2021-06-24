<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2005 Stephen Street / StreetFire Sound Lअसल
 */
#अगर_अघोषित __linux_pxa2xx_spi_h
#घोषणा __linux_pxa2xx_spi_h

#समावेश <linux/pxa2xx_ssp.h>

#घोषणा PXA2XX_CS_ASSERT (0x01)
#घोषणा PXA2XX_CS_DEASSERT (0x02)

काष्ठा dma_chan;

/* device.platक्रमm_data क्रम SSP controller devices */
काष्ठा pxa2xx_spi_controller अणु
	u16 num_chipselect;
	u8 enable_dma;
	u8 dma_burst_size;
	bool is_slave;

	/* DMA engine specअगरic config */
	bool (*dma_filter)(काष्ठा dma_chan *chan, व्योम *param);
	व्योम *tx_param;
	व्योम *rx_param;

	/* For non-PXA arches */
	काष्ठा ssp_device ssp;
पूर्ण;

/* spi_board_info.controller_data क्रम SPI slave devices,
 * copied to spi_device.platक्रमm_data ... mostly क्रम dma tuning
 */
काष्ठा pxa2xx_spi_chip अणु
	u8 tx_threshold;
	u8 tx_hi_threshold;
	u8 rx_threshold;
	u8 dma_burst_size;
	u32 समयout;
	u8 enable_loopback;
	पूर्णांक gpio_cs;
	व्योम (*cs_control)(u32 command);
पूर्ण;

#अगर defined(CONFIG_ARCH_PXA) || defined(CONFIG_ARCH_MMP)

#समावेश <linux/clk.h>

बाह्य व्योम pxa2xx_set_spi_info(अचिन्हित id, काष्ठा pxa2xx_spi_controller *info);

#पूर्ण_अगर
#पूर्ण_अगर
