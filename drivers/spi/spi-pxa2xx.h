<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005 Stephen Street / StreetFire Sound Lअसल
 * Copyright (C) 2013, Intel Corporation
 */

#अगर_अघोषित SPI_PXA2XX_H
#घोषणा SPI_PXA2XX_H

#समावेश <linux/atomic.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pxa2xx_ssp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>

काष्ठा driver_data अणु
	/* Driver model hookup */
	काष्ठा platक्रमm_device *pdev;

	/* SSP Info */
	काष्ठा ssp_device *ssp;

	/* SPI framework hookup */
	क्रमागत pxa_ssp_type ssp_type;
	काष्ठा spi_controller *controller;

	/* PXA hookup */
	काष्ठा pxa2xx_spi_controller *controller_info;

	/* SSP रेजिस्टर addresses */
	व्योम __iomem *ioaddr;
	phys_addr_t ssdr_physical;

	/* SSP masks*/
	u32 dma_cr1;
	u32 पूर्णांक_cr1;
	u32 clear_sr;
	u32 mask_sr;

	/* DMA engine support */
	atomic_t dma_running;

	/* Current transfer state info */
	व्योम *tx;
	व्योम *tx_end;
	व्योम *rx;
	व्योम *rx_end;
	u8 n_bytes;
	पूर्णांक (*ग_लिखो)(काष्ठा driver_data *drv_data);
	पूर्णांक (*पढ़ो)(काष्ठा driver_data *drv_data);
	irqवापस_t (*transfer_handler)(काष्ठा driver_data *drv_data);
	व्योम (*cs_control)(u32 command);

	व्योम __iomem *lpss_base;

	/* GPIOs क्रम chip selects */
	काष्ठा gpio_desc **cs_gpiods;

	/* Optional slave FIFO पढ़ोy संकेत */
	काष्ठा gpio_desc *gpiod_पढ़ोy;
पूर्ण;

काष्ठा chip_data अणु
	u32 cr1;
	u32 dds_rate;
	u32 समयout;
	u8 n_bytes;
	u32 dma_burst_size;
	u32 threshold;
	u32 dma_threshold;
	u16 lpss_rx_threshold;
	u16 lpss_tx_threshold;
	u8 enable_dma;
	जोड़ अणु
		काष्ठा gpio_desc *gpiod_cs;
		अचिन्हित पूर्णांक frm;
	पूर्ण;
	पूर्णांक gpio_cs_inverted;
	पूर्णांक (*ग_लिखो)(काष्ठा driver_data *drv_data);
	पूर्णांक (*पढ़ो)(काष्ठा driver_data *drv_data);
	व्योम (*cs_control)(u32 command);
पूर्ण;

अटल अंतरभूत u32 pxa2xx_spi_पढ़ो(स्थिर काष्ठा driver_data *drv_data,
				  अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(drv_data->ioaddr + reg);
पूर्ण

अटल  अंतरभूत व्योम pxa2xx_spi_ग_लिखो(स्थिर काष्ठा driver_data *drv_data,
				     अचिन्हित reg, u32 val)
अणु
	__raw_ग_लिखोl(val, drv_data->ioaddr + reg);
पूर्ण

#घोषणा DMA_ALIGNMENT		8

अटल अंतरभूत पूर्णांक pxa25x_ssp_comp(काष्ठा driver_data *drv_data)
अणु
	चयन (drv_data->ssp_type) अणु
	हाल PXA25x_SSP:
	हाल CE4100_SSP:
	हाल QUARK_X1000_SSP:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_SSSR_CS(काष्ठा driver_data *drv_data, u32 val)
अणु
	अगर (drv_data->ssp_type == CE4100_SSP ||
	    drv_data->ssp_type == QUARK_X1000_SSP)
		val |= pxa2xx_spi_पढ़ो(drv_data, SSSR) & SSSR_ALT_FRM_MASK;

	pxa2xx_spi_ग_लिखो(drv_data, SSSR, val);
पूर्ण

बाह्य पूर्णांक pxa2xx_spi_flush(काष्ठा driver_data *drv_data);

#घोषणा MAX_DMA_LEN		SZ_64K
#घोषणा DEFAULT_DMA_CR1		(SSCR1_TSRE | SSCR1_RSRE | SSCR1_TRAIL)

बाह्य irqवापस_t pxa2xx_spi_dma_transfer(काष्ठा driver_data *drv_data);
बाह्य पूर्णांक pxa2xx_spi_dma_prepare(काष्ठा driver_data *drv_data,
				  काष्ठा spi_transfer *xfer);
बाह्य व्योम pxa2xx_spi_dma_start(काष्ठा driver_data *drv_data);
बाह्य व्योम pxa2xx_spi_dma_stop(काष्ठा driver_data *drv_data);
बाह्य पूर्णांक pxa2xx_spi_dma_setup(काष्ठा driver_data *drv_data);
बाह्य व्योम pxa2xx_spi_dma_release(काष्ठा driver_data *drv_data);
बाह्य पूर्णांक pxa2xx_spi_set_dma_burst_and_threshold(काष्ठा chip_data *chip,
						  काष्ठा spi_device *spi,
						  u8 bits_per_word,
						  u32 *burst_code,
						  u32 *threshold);

#पूर्ण_अगर /* SPI_PXA2XX_H */
