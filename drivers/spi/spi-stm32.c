<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// STMicroelectronics STM32 SPI Controller driver (master mode only)
//
// Copyright (C) 2017, STMicroelectronics - All Rights Reserved
// Author(s): Amelie Delaunay <amelie.delaunay@st.com> क्रम STMicroelectronics.

#समावेश <linux/bitfield.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME "spi_stm32"

/* STM32F4 SPI रेजिस्टरs */
#घोषणा STM32F4_SPI_CR1			0x00
#घोषणा STM32F4_SPI_CR2			0x04
#घोषणा STM32F4_SPI_SR			0x08
#घोषणा STM32F4_SPI_DR			0x0C
#घोषणा STM32F4_SPI_I2SCFGR		0x1C

/* STM32F4_SPI_CR1 bit fields */
#घोषणा STM32F4_SPI_CR1_CPHA		BIT(0)
#घोषणा STM32F4_SPI_CR1_CPOL		BIT(1)
#घोषणा STM32F4_SPI_CR1_MSTR		BIT(2)
#घोषणा STM32F4_SPI_CR1_BR_SHIFT	3
#घोषणा STM32F4_SPI_CR1_BR		GENMASK(5, 3)
#घोषणा STM32F4_SPI_CR1_SPE		BIT(6)
#घोषणा STM32F4_SPI_CR1_LSBFRST		BIT(7)
#घोषणा STM32F4_SPI_CR1_SSI		BIT(8)
#घोषणा STM32F4_SPI_CR1_SSM		BIT(9)
#घोषणा STM32F4_SPI_CR1_RXONLY		BIT(10)
#घोषणा STM32F4_SPI_CR1_DFF		BIT(11)
#घोषणा STM32F4_SPI_CR1_CRCNEXT		BIT(12)
#घोषणा STM32F4_SPI_CR1_CRCEN		BIT(13)
#घोषणा STM32F4_SPI_CR1_BIDIOE		BIT(14)
#घोषणा STM32F4_SPI_CR1_BIDIMODE	BIT(15)
#घोषणा STM32F4_SPI_CR1_BR_MIN		0
#घोषणा STM32F4_SPI_CR1_BR_MAX		(GENMASK(5, 3) >> 3)

/* STM32F4_SPI_CR2 bit fields */
#घोषणा STM32F4_SPI_CR2_RXDMAEN		BIT(0)
#घोषणा STM32F4_SPI_CR2_TXDMAEN		BIT(1)
#घोषणा STM32F4_SPI_CR2_SSOE		BIT(2)
#घोषणा STM32F4_SPI_CR2_FRF		BIT(4)
#घोषणा STM32F4_SPI_CR2_ERRIE		BIT(5)
#घोषणा STM32F4_SPI_CR2_RXNEIE		BIT(6)
#घोषणा STM32F4_SPI_CR2_TXEIE		BIT(7)

/* STM32F4_SPI_SR bit fields */
#घोषणा STM32F4_SPI_SR_RXNE		BIT(0)
#घोषणा STM32F4_SPI_SR_TXE		BIT(1)
#घोषणा STM32F4_SPI_SR_CHSIDE		BIT(2)
#घोषणा STM32F4_SPI_SR_UDR		BIT(3)
#घोषणा STM32F4_SPI_SR_CRCERR		BIT(4)
#घोषणा STM32F4_SPI_SR_MODF		BIT(5)
#घोषणा STM32F4_SPI_SR_OVR		BIT(6)
#घोषणा STM32F4_SPI_SR_BSY		BIT(7)
#घोषणा STM32F4_SPI_SR_FRE		BIT(8)

/* STM32F4_SPI_I2SCFGR bit fields */
#घोषणा STM32F4_SPI_I2SCFGR_I2SMOD	BIT(11)

/* STM32F4 SPI Baud Rate min/max भागisor */
#घोषणा STM32F4_SPI_BR_DIV_MIN		(2 << STM32F4_SPI_CR1_BR_MIN)
#घोषणा STM32F4_SPI_BR_DIV_MAX		(2 << STM32F4_SPI_CR1_BR_MAX)

/* STM32H7 SPI रेजिस्टरs */
#घोषणा STM32H7_SPI_CR1			0x00
#घोषणा STM32H7_SPI_CR2			0x04
#घोषणा STM32H7_SPI_CFG1		0x08
#घोषणा STM32H7_SPI_CFG2		0x0C
#घोषणा STM32H7_SPI_IER			0x10
#घोषणा STM32H7_SPI_SR			0x14
#घोषणा STM32H7_SPI_IFCR		0x18
#घोषणा STM32H7_SPI_TXDR		0x20
#घोषणा STM32H7_SPI_RXDR		0x30
#घोषणा STM32H7_SPI_I2SCFGR		0x50

/* STM32H7_SPI_CR1 bit fields */
#घोषणा STM32H7_SPI_CR1_SPE		BIT(0)
#घोषणा STM32H7_SPI_CR1_MASRX		BIT(8)
#घोषणा STM32H7_SPI_CR1_CSTART		BIT(9)
#घोषणा STM32H7_SPI_CR1_CSUSP		BIT(10)
#घोषणा STM32H7_SPI_CR1_HDसूची		BIT(11)
#घोषणा STM32H7_SPI_CR1_SSI		BIT(12)

/* STM32H7_SPI_CR2 bit fields */
#घोषणा STM32H7_SPI_CR2_TSIZE		GENMASK(15, 0)
#घोषणा STM32H7_SPI_TSIZE_MAX		GENMASK(15, 0)

/* STM32H7_SPI_CFG1 bit fields */
#घोषणा STM32H7_SPI_CFG1_DSIZE		GENMASK(4, 0)
#घोषणा STM32H7_SPI_CFG1_FTHLV		GENMASK(8, 5)
#घोषणा STM32H7_SPI_CFG1_RXDMAEN	BIT(14)
#घोषणा STM32H7_SPI_CFG1_TXDMAEN	BIT(15)
#घोषणा STM32H7_SPI_CFG1_MBR		GENMASK(30, 28)
#घोषणा STM32H7_SPI_CFG1_MBR_SHIFT	28
#घोषणा STM32H7_SPI_CFG1_MBR_MIN	0
#घोषणा STM32H7_SPI_CFG1_MBR_MAX	(GENMASK(30, 28) >> 28)

/* STM32H7_SPI_CFG2 bit fields */
#घोषणा STM32H7_SPI_CFG2_MIDI		GENMASK(7, 4)
#घोषणा STM32H7_SPI_CFG2_COMM		GENMASK(18, 17)
#घोषणा STM32H7_SPI_CFG2_SP		GENMASK(21, 19)
#घोषणा STM32H7_SPI_CFG2_MASTER		BIT(22)
#घोषणा STM32H7_SPI_CFG2_LSBFRST	BIT(23)
#घोषणा STM32H7_SPI_CFG2_CPHA		BIT(24)
#घोषणा STM32H7_SPI_CFG2_CPOL		BIT(25)
#घोषणा STM32H7_SPI_CFG2_SSM		BIT(26)
#घोषणा STM32H7_SPI_CFG2_AFCNTR		BIT(31)

/* STM32H7_SPI_IER bit fields */
#घोषणा STM32H7_SPI_IER_RXPIE		BIT(0)
#घोषणा STM32H7_SPI_IER_TXPIE		BIT(1)
#घोषणा STM32H7_SPI_IER_DXPIE		BIT(2)
#घोषणा STM32H7_SPI_IER_EOTIE		BIT(3)
#घोषणा STM32H7_SPI_IER_TXTFIE		BIT(4)
#घोषणा STM32H7_SPI_IER_OVRIE		BIT(6)
#घोषणा STM32H7_SPI_IER_MODFIE		BIT(9)
#घोषणा STM32H7_SPI_IER_ALL		GENMASK(10, 0)

/* STM32H7_SPI_SR bit fields */
#घोषणा STM32H7_SPI_SR_RXP		BIT(0)
#घोषणा STM32H7_SPI_SR_TXP		BIT(1)
#घोषणा STM32H7_SPI_SR_EOT		BIT(3)
#घोषणा STM32H7_SPI_SR_OVR		BIT(6)
#घोषणा STM32H7_SPI_SR_MODF		BIT(9)
#घोषणा STM32H7_SPI_SR_SUSP		BIT(11)
#घोषणा STM32H7_SPI_SR_RXPLVL		GENMASK(14, 13)
#घोषणा STM32H7_SPI_SR_RXWNE		BIT(15)

/* STM32H7_SPI_IFCR bit fields */
#घोषणा STM32H7_SPI_IFCR_ALL		GENMASK(11, 3)

/* STM32H7_SPI_I2SCFGR bit fields */
#घोषणा STM32H7_SPI_I2SCFGR_I2SMOD	BIT(0)

/* STM32H7 SPI Master Baud Rate min/max भागisor */
#घोषणा STM32H7_SPI_MBR_DIV_MIN		(2 << STM32H7_SPI_CFG1_MBR_MIN)
#घोषणा STM32H7_SPI_MBR_DIV_MAX		(2 << STM32H7_SPI_CFG1_MBR_MAX)

/* STM32H7 SPI Communication mode */
#घोषणा STM32H7_SPI_FULL_DUPLEX		0
#घोषणा STM32H7_SPI_SIMPLEX_TX		1
#घोषणा STM32H7_SPI_SIMPLEX_RX		2
#घोषणा STM32H7_SPI_HALF_DUPLEX		3

/* SPI Communication type */
#घोषणा SPI_FULL_DUPLEX		0
#घोषणा SPI_SIMPLEX_TX		1
#घोषणा SPI_SIMPLEX_RX		2
#घोषणा SPI_3WIRE_TX		3
#घोषणा SPI_3WIRE_RX		4

/*
 * use PIO क्रम small transfers, aव्योमing DMA setup/tearकरोwn overhead क्रम drivers
 * without fअगरo buffers.
 */
#घोषणा SPI_DMA_MIN_BYTES	16

/**
 * काष्ठा sपंचांग32_spi_reg - sपंचांग32 SPI रेजिस्टर & bitfield desc
 * @reg:		रेजिस्टर offset
 * @mask:		bitfield mask
 * @shअगरt:		left shअगरt
 */
काष्ठा sपंचांग32_spi_reg अणु
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक shअगरt;
पूर्ण;

/**
 * काष्ठा sपंचांग32_spi_regspec - sपंचांग32 रेजिस्टरs definition, compatible dependent data
 * @en: enable रेजिस्टर and SPI enable bit
 * @dma_rx_en: SPI DMA RX enable रेजिस्टर end SPI DMA RX enable bit
 * @dma_tx_en: SPI DMA TX enable रेजिस्टर end SPI DMA TX enable bit
 * @cpol: घड़ी polarity रेजिस्टर and polarity bit
 * @cpha: घड़ी phase रेजिस्टर and phase bit
 * @lsb_first: LSB transmitted first रेजिस्टर and bit
 * @br: baud rate रेजिस्टर and bitfields
 * @rx: SPI RX data रेजिस्टर
 * @tx: SPI TX data रेजिस्टर
 */
काष्ठा sपंचांग32_spi_regspec अणु
	स्थिर काष्ठा sपंचांग32_spi_reg en;
	स्थिर काष्ठा sपंचांग32_spi_reg dma_rx_en;
	स्थिर काष्ठा sपंचांग32_spi_reg dma_tx_en;
	स्थिर काष्ठा sपंचांग32_spi_reg cpol;
	स्थिर काष्ठा sपंचांग32_spi_reg cpha;
	स्थिर काष्ठा sपंचांग32_spi_reg lsb_first;
	स्थिर काष्ठा sपंचांग32_spi_reg br;
	स्थिर काष्ठा sपंचांग32_spi_reg rx;
	स्थिर काष्ठा sपंचांग32_spi_reg tx;
पूर्ण;

काष्ठा sपंचांग32_spi;

/**
 * काष्ठा sपंचांग32_spi_cfg - sपंचांग32 compatible configuration data
 * @regs: रेजिस्टरs descriptions
 * @get_fअगरo_size: routine to get fअगरo size
 * @get_bpw_mask: routine to get bits per word mask
 * @disable: routine to disable controller
 * @config: routine to configure controller as SPI Master
 * @set_bpw: routine to configure रेजिस्टरs to क्रम bits per word
 * @set_mode: routine to configure रेजिस्टरs to desired mode
 * @set_data_idleness: optional routine to configure रेजिस्टरs to desired idle
 * समय between frames (अगर driver has this functionality)
 * @set_number_of_data: optional routine to configure रेजिस्टरs to desired
 * number of data (अगर driver has this functionality)
 * @can_dma: routine to determine अगर the transfer is eligible क्रम DMA use
 * @transfer_one_dma_start: routine to start transfer a single spi_transfer
 * using DMA
 * @dma_rx_cb: routine to call after DMA RX channel operation is complete
 * @dma_tx_cb: routine to call after DMA TX channel operation is complete
 * @transfer_one_irq: routine to configure पूर्णांकerrupts क्रम driver
 * @irq_handler_event: Interrupt handler क्रम SPI controller events
 * @irq_handler_thपढ़ो: thपढ़ो of पूर्णांकerrupt handler क्रम SPI controller
 * @baud_rate_भाग_min: minimum baud rate भागisor
 * @baud_rate_भाग_max: maximum baud rate भागisor
 * @has_fअगरo: boolean to know अगर fअगरo is used क्रम driver
 * @has_startbit: boolean to know अगर start bit is used to start transfer
 */
काष्ठा sपंचांग32_spi_cfg अणु
	स्थिर काष्ठा sपंचांग32_spi_regspec *regs;
	पूर्णांक (*get_fअगरo_size)(काष्ठा sपंचांग32_spi *spi);
	पूर्णांक (*get_bpw_mask)(काष्ठा sपंचांग32_spi *spi);
	व्योम (*disable)(काष्ठा sपंचांग32_spi *spi);
	पूर्णांक (*config)(काष्ठा sपंचांग32_spi *spi);
	व्योम (*set_bpw)(काष्ठा sपंचांग32_spi *spi);
	पूर्णांक (*set_mode)(काष्ठा sपंचांग32_spi *spi, अचिन्हित पूर्णांक comm_type);
	व्योम (*set_data_idleness)(काष्ठा sपंचांग32_spi *spi, u32 length);
	पूर्णांक (*set_number_of_data)(काष्ठा sपंचांग32_spi *spi, u32 length);
	व्योम (*transfer_one_dma_start)(काष्ठा sपंचांग32_spi *spi);
	व्योम (*dma_rx_cb)(व्योम *data);
	व्योम (*dma_tx_cb)(व्योम *data);
	पूर्णांक (*transfer_one_irq)(काष्ठा sपंचांग32_spi *spi);
	irqवापस_t (*irq_handler_event)(पूर्णांक irq, व्योम *dev_id);
	irqवापस_t (*irq_handler_thपढ़ो)(पूर्णांक irq, व्योम *dev_id);
	अचिन्हित पूर्णांक baud_rate_भाग_min;
	अचिन्हित पूर्णांक baud_rate_भाग_max;
	bool has_fअगरo;
पूर्ण;

/**
 * काष्ठा sपंचांग32_spi - निजी data of the SPI controller
 * @dev: driver model representation of the controller
 * @master: controller master पूर्णांकerface
 * @cfg: compatible configuration data
 * @base: भव memory area
 * @clk: hw kernel घड़ी feeding the SPI घड़ी generator
 * @clk_rate: rate of the hw kernel घड़ी feeding the SPI घड़ी generator
 * @lock: prevent I/O concurrent access
 * @irq: SPI controller पूर्णांकerrupt line
 * @fअगरo_size: size of the embedded fअगरo in bytes
 * @cur_midi: master पूर्णांकer-data idleness in ns
 * @cur_speed: speed configured in Hz
 * @cur_bpw: number of bits in a single SPI data frame
 * @cur_fthlv: fअगरo threshold level (data frames in a single data packet)
 * @cur_comm: SPI communication mode
 * @cur_xferlen: current transfer length in bytes
 * @cur_usedma: boolean to know अगर dma is used in current transfer
 * @tx_buf: data to be written, or शून्य
 * @rx_buf: data to be पढ़ो, or शून्य
 * @tx_len: number of data to be written in bytes
 * @rx_len: number of data to be पढ़ो in bytes
 * @dma_tx: dma channel क्रम TX transfer
 * @dma_rx: dma channel क्रम RX transfer
 * @phys_addr: SPI रेजिस्टरs physical base address
 */
काष्ठा sपंचांग32_spi अणु
	काष्ठा device *dev;
	काष्ठा spi_master *master;
	स्थिर काष्ठा sपंचांग32_spi_cfg *cfg;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	u32 clk_rate;
	spinlock_t lock; /* prevent I/O concurrent access */
	पूर्णांक irq;
	अचिन्हित पूर्णांक fअगरo_size;

	अचिन्हित पूर्णांक cur_midi;
	अचिन्हित पूर्णांक cur_speed;
	अचिन्हित पूर्णांक cur_bpw;
	अचिन्हित पूर्णांक cur_fthlv;
	अचिन्हित पूर्णांक cur_comm;
	अचिन्हित पूर्णांक cur_xferlen;
	bool cur_usedma;

	स्थिर व्योम *tx_buf;
	व्योम *rx_buf;
	पूर्णांक tx_len;
	पूर्णांक rx_len;
	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;
	dma_addr_t phys_addr;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_spi_regspec sपंचांग32f4_spi_regspec = अणु
	.en = अणु STM32F4_SPI_CR1, STM32F4_SPI_CR1_SPE पूर्ण,

	.dma_rx_en = अणु STM32F4_SPI_CR2, STM32F4_SPI_CR2_RXDMAEN पूर्ण,
	.dma_tx_en = अणु STM32F4_SPI_CR2, STM32F4_SPI_CR2_TXDMAEN पूर्ण,

	.cpol = अणु STM32F4_SPI_CR1, STM32F4_SPI_CR1_CPOL पूर्ण,
	.cpha = अणु STM32F4_SPI_CR1, STM32F4_SPI_CR1_CPHA पूर्ण,
	.lsb_first = अणु STM32F4_SPI_CR1, STM32F4_SPI_CR1_LSBFRST पूर्ण,
	.br = अणु STM32F4_SPI_CR1, STM32F4_SPI_CR1_BR, STM32F4_SPI_CR1_BR_SHIFT पूर्ण,

	.rx = अणु STM32F4_SPI_DR पूर्ण,
	.tx = अणु STM32F4_SPI_DR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_spi_regspec sपंचांग32h7_spi_regspec = अणु
	/* SPI data transfer is enabled but spi_ker_ck is idle.
	 * CFG1 and CFG2 रेजिस्टरs are ग_लिखो रक्षित when SPE is enabled.
	 */
	.en = अणु STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE पूर्ण,

	.dma_rx_en = अणु STM32H7_SPI_CFG1, STM32H7_SPI_CFG1_RXDMAEN पूर्ण,
	.dma_tx_en = अणु STM32H7_SPI_CFG1, STM32H7_SPI_CFG1_TXDMAEN पूर्ण,

	.cpol = अणु STM32H7_SPI_CFG2, STM32H7_SPI_CFG2_CPOL पूर्ण,
	.cpha = अणु STM32H7_SPI_CFG2, STM32H7_SPI_CFG2_CPHA पूर्ण,
	.lsb_first = अणु STM32H7_SPI_CFG2, STM32H7_SPI_CFG2_LSBFRST पूर्ण,
	.br = अणु STM32H7_SPI_CFG1, STM32H7_SPI_CFG1_MBR,
		STM32H7_SPI_CFG1_MBR_SHIFT पूर्ण,

	.rx = अणु STM32H7_SPI_RXDR पूर्ण,
	.tx = अणु STM32H7_SPI_TXDR पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम sपंचांग32_spi_set_bits(काष्ठा sपंचांग32_spi *spi,
				      u32 offset, u32 bits)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(spi->base + offset) | bits,
		       spi->base + offset);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_spi_clr_bits(काष्ठा sपंचांग32_spi *spi,
				      u32 offset, u32 bits)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(spi->base + offset) & ~bits,
		       spi->base + offset);
पूर्ण

/**
 * sपंचांग32h7_spi_get_fअगरo_size - Return fअगरo size
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल पूर्णांक sपंचांग32h7_spi_get_fअगरo_size(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 count = 0;

	spin_lock_irqsave(&spi->lock, flags);

	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE);

	जबतक (पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR) & STM32H7_SPI_SR_TXP)
		ग_लिखोb_relaxed(++count, spi->base + STM32H7_SPI_TXDR);

	sपंचांग32_spi_clr_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE);

	spin_unlock_irqrestore(&spi->lock, flags);

	dev_dbg(spi->dev, "%d x 8-bit fifo size\n", count);

	वापस count;
पूर्ण

/**
 * sपंचांग32f4_spi_get_bpw_mask - Return bits per word mask
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल पूर्णांक sपंचांग32f4_spi_get_bpw_mask(काष्ठा sपंचांग32_spi *spi)
अणु
	dev_dbg(spi->dev, "8-bit or 16-bit data frame supported\n");
	वापस SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
पूर्ण

/**
 * sपंचांग32h7_spi_get_bpw_mask - Return bits per word mask
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल पूर्णांक sपंचांग32h7_spi_get_bpw_mask(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 cfg1, max_bpw;

	spin_lock_irqsave(&spi->lock, flags);

	/*
	 * The most signअगरicant bit at DSIZE bit field is reserved when the
	 * maximum data size of periperal instances is limited to 16-bit
	 */
	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CFG1, STM32H7_SPI_CFG1_DSIZE);

	cfg1 = पढ़ोl_relaxed(spi->base + STM32H7_SPI_CFG1);
	max_bpw = FIELD_GET(STM32H7_SPI_CFG1_DSIZE, cfg1) + 1;

	spin_unlock_irqrestore(&spi->lock, flags);

	dev_dbg(spi->dev, "%d-bit maximum data frame\n", max_bpw);

	वापस SPI_BPW_RANGE_MASK(4, max_bpw);
पूर्ण

/**
 * sपंचांग32_spi_prepare_mbr - Determine baud rate भागisor value
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @speed_hz: requested speed
 * @min_भाग: minimum baud rate भागisor
 * @max_भाग: maximum baud rate भागisor
 *
 * Return baud rate भागisor value in हाल of success or -EINVAL
 */
अटल पूर्णांक sपंचांग32_spi_prepare_mbr(काष्ठा sपंचांग32_spi *spi, u32 speed_hz,
				 u32 min_भाग, u32 max_भाग)
अणु
	u32 भाग, mbrभाग;

	/* Ensure spi->clk_rate is even */
	भाग = DIV_ROUND_UP(spi->clk_rate & ~0x1, speed_hz);

	/*
	 * SPI framework set xfer->speed_hz to master->max_speed_hz अगर
	 * xfer->speed_hz is greater than master->max_speed_hz, and it वापसs
	 * an error when xfer->speed_hz is lower than master->min_speed_hz, so
	 * no need to check it there.
	 * However, we need to ensure the following calculations.
	 */
	अगर ((भाग < min_भाग) || (भाग > max_भाग))
		वापस -EINVAL;

	/* Determine the first घातer of 2 greater than or equal to भाग */
	अगर (भाग & (भाग - 1))
		mbrभाग = fls(भाग);
	अन्यथा
		mbrभाग = fls(भाग) - 1;

	spi->cur_speed = spi->clk_rate / (1 << mbrभाग);

	वापस mbrभाग - 1;
पूर्ण

/**
 * sपंचांग32h7_spi_prepare_fthlv - Determine FIFO threshold level
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @xfer_len: length of the message to be transferred
 */
अटल u32 sपंचांग32h7_spi_prepare_fthlv(काष्ठा sपंचांग32_spi *spi, u32 xfer_len)
अणु
	u32 packet, bpw;

	/* data packet should not exceed 1/2 of fअगरo space */
	packet = clamp(xfer_len, 1U, spi->fअगरo_size / 2);

	/* align packet size with data रेजिस्टरs access */
	bpw = DIV_ROUND_UP(spi->cur_bpw, 8);
	वापस DIV_ROUND_UP(packet, bpw);
पूर्ण

/**
 * sपंचांग32f4_spi_ग_लिखो_tx - Write bytes to Transmit Data Register
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * Read from tx_buf depends on reमुख्यing bytes to aव्योम to पढ़ो beyond
 * tx_buf end.
 */
अटल व्योम sपंचांग32f4_spi_ग_लिखो_tx(काष्ठा sपंचांग32_spi *spi)
अणु
	अगर ((spi->tx_len > 0) && (पढ़ोl_relaxed(spi->base + STM32F4_SPI_SR) &
				  STM32F4_SPI_SR_TXE)) अणु
		u32 offs = spi->cur_xferlen - spi->tx_len;

		अगर (spi->cur_bpw == 16) अणु
			स्थिर u16 *tx_buf16 = (स्थिर u16 *)(spi->tx_buf + offs);

			ग_लिखोw_relaxed(*tx_buf16, spi->base + STM32F4_SPI_DR);
			spi->tx_len -= माप(u16);
		पूर्ण अन्यथा अणु
			स्थिर u8 *tx_buf8 = (स्थिर u8 *)(spi->tx_buf + offs);

			ग_लिखोb_relaxed(*tx_buf8, spi->base + STM32F4_SPI_DR);
			spi->tx_len -= माप(u8);
		पूर्ण
	पूर्ण

	dev_dbg(spi->dev, "%s: %d bytes left\n", __func__, spi->tx_len);
पूर्ण

/**
 * sपंचांग32h7_spi_ग_लिखो_txfअगरo - Write bytes in Transmit Data Register
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * Read from tx_buf depends on reमुख्यing bytes to aव्योम to पढ़ो beyond
 * tx_buf end.
 */
अटल व्योम sपंचांग32h7_spi_ग_लिखो_txfअगरo(काष्ठा sपंचांग32_spi *spi)
अणु
	जबतक ((spi->tx_len > 0) &&
		       (पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR) &
			STM32H7_SPI_SR_TXP)) अणु
		u32 offs = spi->cur_xferlen - spi->tx_len;

		अगर (spi->tx_len >= माप(u32)) अणु
			स्थिर u32 *tx_buf32 = (स्थिर u32 *)(spi->tx_buf + offs);

			ग_लिखोl_relaxed(*tx_buf32, spi->base + STM32H7_SPI_TXDR);
			spi->tx_len -= माप(u32);
		पूर्ण अन्यथा अगर (spi->tx_len >= माप(u16)) अणु
			स्थिर u16 *tx_buf16 = (स्थिर u16 *)(spi->tx_buf + offs);

			ग_लिखोw_relaxed(*tx_buf16, spi->base + STM32H7_SPI_TXDR);
			spi->tx_len -= माप(u16);
		पूर्ण अन्यथा अणु
			स्थिर u8 *tx_buf8 = (स्थिर u8 *)(spi->tx_buf + offs);

			ग_लिखोb_relaxed(*tx_buf8, spi->base + STM32H7_SPI_TXDR);
			spi->tx_len -= माप(u8);
		पूर्ण
	पूर्ण

	dev_dbg(spi->dev, "%s: %d bytes left\n", __func__, spi->tx_len);
पूर्ण

/**
 * sपंचांग32f4_spi_पढ़ो_rx - Read bytes from Receive Data Register
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * Write in rx_buf depends on reमुख्यing bytes to aव्योम to ग_लिखो beyond
 * rx_buf end.
 */
अटल व्योम sपंचांग32f4_spi_पढ़ो_rx(काष्ठा sपंचांग32_spi *spi)
अणु
	अगर ((spi->rx_len > 0) && (पढ़ोl_relaxed(spi->base + STM32F4_SPI_SR) &
				  STM32F4_SPI_SR_RXNE)) अणु
		u32 offs = spi->cur_xferlen - spi->rx_len;

		अगर (spi->cur_bpw == 16) अणु
			u16 *rx_buf16 = (u16 *)(spi->rx_buf + offs);

			*rx_buf16 = पढ़ोw_relaxed(spi->base + STM32F4_SPI_DR);
			spi->rx_len -= माप(u16);
		पूर्ण अन्यथा अणु
			u8 *rx_buf8 = (u8 *)(spi->rx_buf + offs);

			*rx_buf8 = पढ़ोb_relaxed(spi->base + STM32F4_SPI_DR);
			spi->rx_len -= माप(u8);
		पूर्ण
	पूर्ण

	dev_dbg(spi->dev, "%s: %d bytes left\n", __func__, spi->rx_len);
पूर्ण

/**
 * sपंचांग32h7_spi_पढ़ो_rxfअगरo - Read bytes in Receive Data Register
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @flush: boolean indicating that FIFO should be flushed
 *
 * Write in rx_buf depends on reमुख्यing bytes to aव्योम to ग_लिखो beyond
 * rx_buf end.
 */
अटल व्योम sपंचांग32h7_spi_पढ़ो_rxfअगरo(काष्ठा sपंचांग32_spi *spi, bool flush)
अणु
	u32 sr = पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR);
	u32 rxplvl = FIELD_GET(STM32H7_SPI_SR_RXPLVL, sr);

	जबतक ((spi->rx_len > 0) &&
	       ((sr & STM32H7_SPI_SR_RXP) ||
		(flush && ((sr & STM32H7_SPI_SR_RXWNE) || (rxplvl > 0))))) अणु
		u32 offs = spi->cur_xferlen - spi->rx_len;

		अगर ((spi->rx_len >= माप(u32)) ||
		    (flush && (sr & STM32H7_SPI_SR_RXWNE))) अणु
			u32 *rx_buf32 = (u32 *)(spi->rx_buf + offs);

			*rx_buf32 = पढ़ोl_relaxed(spi->base + STM32H7_SPI_RXDR);
			spi->rx_len -= माप(u32);
		पूर्ण अन्यथा अगर ((spi->rx_len >= माप(u16)) ||
			   (flush && (rxplvl >= 2 || spi->cur_bpw > 8))) अणु
			u16 *rx_buf16 = (u16 *)(spi->rx_buf + offs);

			*rx_buf16 = पढ़ोw_relaxed(spi->base + STM32H7_SPI_RXDR);
			spi->rx_len -= माप(u16);
		पूर्ण अन्यथा अणु
			u8 *rx_buf8 = (u8 *)(spi->rx_buf + offs);

			*rx_buf8 = पढ़ोb_relaxed(spi->base + STM32H7_SPI_RXDR);
			spi->rx_len -= माप(u8);
		पूर्ण

		sr = पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR);
		rxplvl = FIELD_GET(STM32H7_SPI_SR_RXPLVL, sr);
	पूर्ण

	dev_dbg(spi->dev, "%s%s: %d bytes left\n", __func__,
		flush ? "(flush)" : "", spi->rx_len);
पूर्ण

/**
 * sपंचांग32_spi_enable - Enable SPI controller
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32_spi_enable(काष्ठा sपंचांग32_spi *spi)
अणु
	dev_dbg(spi->dev, "enable controller\n");

	sपंचांग32_spi_set_bits(spi, spi->cfg->regs->en.reg,
			   spi->cfg->regs->en.mask);
पूर्ण

/**
 * sपंचांग32f4_spi_disable - Disable SPI controller
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32f4_spi_disable(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 sr;

	dev_dbg(spi->dev, "disable controller\n");

	spin_lock_irqsave(&spi->lock, flags);

	अगर (!(पढ़ोl_relaxed(spi->base + STM32F4_SPI_CR1) &
	      STM32F4_SPI_CR1_SPE)) अणु
		spin_unlock_irqrestore(&spi->lock, flags);
		वापस;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_TXEIE |
						 STM32F4_SPI_CR2_RXNEIE |
						 STM32F4_SPI_CR2_ERRIE);

	/* Wait until BSY = 0 */
	अगर (पढ़ोl_relaxed_poll_समयout_atomic(spi->base + STM32F4_SPI_SR,
					      sr, !(sr & STM32F4_SPI_SR_BSY),
					      10, 100000) < 0) अणु
		dev_warn(spi->dev, "disabling condition timeout\n");
	पूर्ण

	अगर (spi->cur_usedma && spi->dma_tx)
		dmaengine_terminate_all(spi->dma_tx);
	अगर (spi->cur_usedma && spi->dma_rx)
		dmaengine_terminate_all(spi->dma_rx);

	sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_SPE);

	sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_TXDMAEN |
						 STM32F4_SPI_CR2_RXDMAEN);

	/* Sequence to clear OVR flag */
	पढ़ोl_relaxed(spi->base + STM32F4_SPI_DR);
	पढ़ोl_relaxed(spi->base + STM32F4_SPI_SR);

	spin_unlock_irqrestore(&spi->lock, flags);
पूर्ण

/**
 * sपंचांग32h7_spi_disable - Disable SPI controller
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * RX-Fअगरo is flushed when SPI controller is disabled. To prevent any data
 * loss, use sपंचांग32h7_spi_पढ़ो_rxfअगरo(flush) to पढ़ो the reमुख्यing bytes in
 * RX-Fअगरo.
 * Normally, अगर TSIZE has been configured, we should relax the hardware at the
 * reception of the EOT पूर्णांकerrupt. But in हाल of error, EOT will not be
 * उठाओd. So the subप्रणाली unprepare_message call allows us to properly
 * complete the transfer from an hardware poपूर्णांक of view.
 */
अटल व्योम sपंचांग32h7_spi_disable(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 cr1, sr;

	dev_dbg(spi->dev, "disable controller\n");

	spin_lock_irqsave(&spi->lock, flags);

	cr1 = पढ़ोl_relaxed(spi->base + STM32H7_SPI_CR1);

	अगर (!(cr1 & STM32H7_SPI_CR1_SPE)) अणु
		spin_unlock_irqrestore(&spi->lock, flags);
		वापस;
	पूर्ण

	/* Wait on EOT or suspend the flow */
	अगर (पढ़ोl_relaxed_poll_समयout_atomic(spi->base + STM32H7_SPI_SR,
					      sr, !(sr & STM32H7_SPI_SR_EOT),
					      10, 100000) < 0) अणु
		अगर (cr1 & STM32H7_SPI_CR1_CSTART) अणु
			ग_लिखोl_relaxed(cr1 | STM32H7_SPI_CR1_CSUSP,
				       spi->base + STM32H7_SPI_CR1);
			अगर (पढ़ोl_relaxed_poll_समयout_atomic(
						spi->base + STM32H7_SPI_SR,
						sr, !(sr & STM32H7_SPI_SR_SUSP),
						10, 100000) < 0)
				dev_warn(spi->dev,
					 "Suspend request timeout\n");
		पूर्ण
	पूर्ण

	अगर (!spi->cur_usedma && spi->rx_buf && (spi->rx_len > 0))
		sपंचांग32h7_spi_पढ़ो_rxfअगरo(spi, true);

	अगर (spi->cur_usedma && spi->dma_tx)
		dmaengine_terminate_all(spi->dma_tx);
	अगर (spi->cur_usedma && spi->dma_rx)
		dmaengine_terminate_all(spi->dma_rx);

	sपंचांग32_spi_clr_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SPE);

	sपंचांग32_spi_clr_bits(spi, STM32H7_SPI_CFG1, STM32H7_SPI_CFG1_TXDMAEN |
						STM32H7_SPI_CFG1_RXDMAEN);

	/* Disable पूर्णांकerrupts and clear status flags */
	ग_लिखोl_relaxed(0, spi->base + STM32H7_SPI_IER);
	ग_लिखोl_relaxed(STM32H7_SPI_IFCR_ALL, spi->base + STM32H7_SPI_IFCR);

	spin_unlock_irqrestore(&spi->lock, flags);
पूर्ण

/**
 * sपंचांग32_spi_can_dma - Determine अगर the transfer is eligible क्रम DMA use
 * @master: controller master पूर्णांकerface
 * @spi_dev: poपूर्णांकer to the spi device
 * @transfer: poपूर्णांकer to spi transfer
 *
 * If driver has fअगरo and the current transfer size is greater than fअगरo size,
 * use DMA. Otherwise use DMA क्रम transfer दीर्घer than defined DMA min bytes.
 */
अटल bool sपंचांग32_spi_can_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi_dev,
			      काष्ठा spi_transfer *transfer)
अणु
	अचिन्हित पूर्णांक dma_size;
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);

	अगर (spi->cfg->has_fअगरo)
		dma_size = spi->fअगरo_size;
	अन्यथा
		dma_size = SPI_DMA_MIN_BYTES;

	dev_dbg(spi->dev, "%s: %s\n", __func__,
		(transfer->len > dma_size) ? "true" : "false");

	वापस (transfer->len > dma_size);
पूर्ण

/**
 * sपंचांग32f4_spi_irq_event - Interrupt handler क्रम SPI controller events
 * @irq: पूर्णांकerrupt line
 * @dev_id: SPI controller master पूर्णांकerface
 */
अटल irqवापस_t sपंचांग32f4_spi_irq_event(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	u32 sr, mask = 0;
	bool end = false;

	spin_lock(&spi->lock);

	sr = पढ़ोl_relaxed(spi->base + STM32F4_SPI_SR);
	/*
	 * BSY flag is not handled in पूर्णांकerrupt but it is normal behavior when
	 * this flag is set.
	 */
	sr &= ~STM32F4_SPI_SR_BSY;

	अगर (!spi->cur_usedma && (spi->cur_comm == SPI_SIMPLEX_TX ||
				 spi->cur_comm == SPI_3WIRE_TX)) अणु
		/* OVR flag shouldn't be handled क्रम TX only mode */
		sr &= ~STM32F4_SPI_SR_OVR | STM32F4_SPI_SR_RXNE;
		mask |= STM32F4_SPI_SR_TXE;
	पूर्ण

	अगर (!spi->cur_usedma && (spi->cur_comm == SPI_FULL_DUPLEX ||
				spi->cur_comm == SPI_SIMPLEX_RX ||
				spi->cur_comm == SPI_3WIRE_RX)) अणु
		/* TXE flag is set and is handled when RXNE flag occurs */
		sr &= ~STM32F4_SPI_SR_TXE;
		mask |= STM32F4_SPI_SR_RXNE | STM32F4_SPI_SR_OVR;
	पूर्ण

	अगर (!(sr & mask)) अणु
		dev_dbg(spi->dev, "spurious IT (sr=0x%08x)\n", sr);
		spin_unlock(&spi->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (sr & STM32F4_SPI_SR_OVR) अणु
		dev_warn(spi->dev, "Overrun: received value discarded\n");

		/* Sequence to clear OVR flag */
		पढ़ोl_relaxed(spi->base + STM32F4_SPI_DR);
		पढ़ोl_relaxed(spi->base + STM32F4_SPI_SR);

		/*
		 * If overrun is detected, it means that something went wrong,
		 * so stop the current transfer. Transfer can रुको क्रम next
		 * RXNE but DR is alपढ़ोy पढ़ो and end never happens.
		 */
		end = true;
		जाओ end_irq;
	पूर्ण

	अगर (sr & STM32F4_SPI_SR_TXE) अणु
		अगर (spi->tx_buf)
			sपंचांग32f4_spi_ग_लिखो_tx(spi);
		अगर (spi->tx_len == 0)
			end = true;
	पूर्ण

	अगर (sr & STM32F4_SPI_SR_RXNE) अणु
		sपंचांग32f4_spi_पढ़ो_rx(spi);
		अगर (spi->rx_len == 0)
			end = true;
		अन्यथा अगर (spi->tx_buf)/* Load data क्रम discontinuous mode */
			sपंचांग32f4_spi_ग_लिखो_tx(spi);
	पूर्ण

end_irq:
	अगर (end) अणु
		/* Immediately disable पूर्णांकerrupts to करो not generate new one */
		sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR2,
					STM32F4_SPI_CR2_TXEIE |
					STM32F4_SPI_CR2_RXNEIE |
					STM32F4_SPI_CR2_ERRIE);
		spin_unlock(&spi->lock);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	spin_unlock(&spi->lock);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32f4_spi_irq_thपढ़ो - Thपढ़ो of पूर्णांकerrupt handler क्रम SPI controller
 * @irq: पूर्णांकerrupt line
 * @dev_id: SPI controller master पूर्णांकerface
 */
अटल irqवापस_t sपंचांग32f4_spi_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);

	spi_finalize_current_transfer(master);
	sपंचांग32f4_spi_disable(spi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32h7_spi_irq_thपढ़ो - Thपढ़ो of पूर्णांकerrupt handler क्रम SPI controller
 * @irq: पूर्णांकerrupt line
 * @dev_id: SPI controller master पूर्णांकerface
 */
अटल irqवापस_t sपंचांग32h7_spi_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	u32 sr, ier, mask;
	अचिन्हित दीर्घ flags;
	bool end = false;

	spin_lock_irqsave(&spi->lock, flags);

	sr = पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR);
	ier = पढ़ोl_relaxed(spi->base + STM32H7_SPI_IER);

	mask = ier;
	/* EOTIE is triggered on EOT, SUSP and TXC events. */
	mask |= STM32H7_SPI_SR_SUSP;
	/*
	 * When TXTF is set, DXPIE and TXPIE are cleared. So in हाल of
	 * Full-Duplex, need to poll RXP event to know अगर there are reमुख्यing
	 * data, beक्रमe disabling SPI.
	 */
	अगर (spi->rx_buf && !spi->cur_usedma)
		mask |= STM32H7_SPI_SR_RXP;

	अगर (!(sr & mask)) अणु
		dev_warn(spi->dev, "spurious IT (sr=0x%08x, ier=0x%08x)\n",
			 sr, ier);
		spin_unlock_irqrestore(&spi->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (sr & STM32H7_SPI_SR_SUSP) अणु
		अटल DEFINE_RATELIMIT_STATE(rs,
					      DEFAULT_RATELIMIT_INTERVAL * 10,
					      1);
		अगर (__ratelimit(&rs))
			dev_dbg_ratelimited(spi->dev, "Communication suspended\n");
		अगर (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			sपंचांग32h7_spi_पढ़ो_rxfअगरo(spi, false);
		/*
		 * If communication is suspended जबतक using DMA, it means
		 * that something went wrong, so stop the current transfer
		 */
		अगर (spi->cur_usedma)
			end = true;
	पूर्ण

	अगर (sr & STM32H7_SPI_SR_MODF) अणु
		dev_warn(spi->dev, "Mode fault: transfer aborted\n");
		end = true;
	पूर्ण

	अगर (sr & STM32H7_SPI_SR_OVR) अणु
		dev_err(spi->dev, "Overrun: RX data lost\n");
		end = true;
	पूर्ण

	अगर (sr & STM32H7_SPI_SR_EOT) अणु
		अगर (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			sपंचांग32h7_spi_पढ़ो_rxfअगरo(spi, true);
		end = true;
	पूर्ण

	अगर (sr & STM32H7_SPI_SR_TXP)
		अगर (!spi->cur_usedma && (spi->tx_buf && (spi->tx_len > 0)))
			sपंचांग32h7_spi_ग_लिखो_txfअगरo(spi);

	अगर (sr & STM32H7_SPI_SR_RXP)
		अगर (!spi->cur_usedma && (spi->rx_buf && (spi->rx_len > 0)))
			sपंचांग32h7_spi_पढ़ो_rxfअगरo(spi, false);

	ग_लिखोl_relaxed(sr & mask, spi->base + STM32H7_SPI_IFCR);

	spin_unlock_irqrestore(&spi->lock, flags);

	अगर (end) अणु
		sपंचांग32h7_spi_disable(spi);
		spi_finalize_current_transfer(master);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sपंचांग32_spi_prepare_msg - set up the controller to transfer a single message
 * @master: controller master पूर्णांकerface
 * @msg: poपूर्णांकer to spi message
 */
अटल पूर्णांक sपंचांग32_spi_prepare_msg(काष्ठा spi_master *master,
				 काष्ठा spi_message *msg)
अणु
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi_dev = msg->spi;
	काष्ठा device_node *np = spi_dev->dev.of_node;
	अचिन्हित दीर्घ flags;
	u32 clrb = 0, setb = 0;

	/* SPI slave device may need समय between data frames */
	spi->cur_midi = 0;
	अगर (np && !of_property_पढ़ो_u32(np, "st,spi-midi-ns", &spi->cur_midi))
		dev_dbg(spi->dev, "%dns inter-data idleness\n", spi->cur_midi);

	अगर (spi_dev->mode & SPI_CPOL)
		setb |= spi->cfg->regs->cpol.mask;
	अन्यथा
		clrb |= spi->cfg->regs->cpol.mask;

	अगर (spi_dev->mode & SPI_CPHA)
		setb |= spi->cfg->regs->cpha.mask;
	अन्यथा
		clrb |= spi->cfg->regs->cpha.mask;

	अगर (spi_dev->mode & SPI_LSB_FIRST)
		setb |= spi->cfg->regs->lsb_first.mask;
	अन्यथा
		clrb |= spi->cfg->regs->lsb_first.mask;

	dev_dbg(spi->dev, "cpol=%d cpha=%d lsb_first=%d cs_high=%d\n",
		!!(spi_dev->mode & SPI_CPOL),
		!!(spi_dev->mode & SPI_CPHA),
		!!(spi_dev->mode & SPI_LSB_FIRST),
		!!(spi_dev->mode & SPI_CS_HIGH));

	/* On STM32H7, messages should not exceed a maximum size setted
	 * afterward via the set_number_of_data function. In order to
	 * ensure that, split large messages पूर्णांकo several messages
	 */
	अगर (spi->cfg->set_number_of_data) अणु
		पूर्णांक ret;

		ret = spi_split_transfers_maxsize(master, msg,
						  STM32H7_SPI_TSIZE_MAX,
						  GFP_KERNEL | GFP_DMA);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&spi->lock, flags);

	/* CPOL, CPHA and LSB FIRST bits have common रेजिस्टर */
	अगर (clrb || setb)
		ग_लिखोl_relaxed(
			(पढ़ोl_relaxed(spi->base + spi->cfg->regs->cpol.reg) &
			 ~clrb) | setb,
			spi->base + spi->cfg->regs->cpol.reg);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 0;
पूर्ण

/**
 * sपंचांग32f4_spi_dma_tx_cb - dma callback
 * @data: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * DMA callback is called when the transfer is complete क्रम DMA TX channel.
 */
अटल व्योम sपंचांग32f4_spi_dma_tx_cb(व्योम *data)
अणु
	काष्ठा sपंचांग32_spi *spi = data;

	अगर (spi->cur_comm == SPI_SIMPLEX_TX || spi->cur_comm == SPI_3WIRE_TX) अणु
		spi_finalize_current_transfer(spi->master);
		sपंचांग32f4_spi_disable(spi);
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_spi_dma_rx_cb - dma callback
 * @data: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * DMA callback is called when the transfer is complete क्रम DMA RX channel.
 */
अटल व्योम sपंचांग32f4_spi_dma_rx_cb(व्योम *data)
अणु
	काष्ठा sपंचांग32_spi *spi = data;

	spi_finalize_current_transfer(spi->master);
	sपंचांग32f4_spi_disable(spi);
पूर्ण

/**
 * sपंचांग32h7_spi_dma_cb - dma callback
 * @data: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * DMA callback is called when the transfer is complete or when an error
 * occurs. If the transfer is complete, EOT flag is उठाओd.
 */
अटल व्योम sपंचांग32h7_spi_dma_cb(व्योम *data)
अणु
	काष्ठा sपंचांग32_spi *spi = data;
	अचिन्हित दीर्घ flags;
	u32 sr;

	spin_lock_irqsave(&spi->lock, flags);

	sr = पढ़ोl_relaxed(spi->base + STM32H7_SPI_SR);

	spin_unlock_irqrestore(&spi->lock, flags);

	अगर (!(sr & STM32H7_SPI_SR_EOT))
		dev_warn(spi->dev, "DMA error (sr=0x%08x)\n", sr);

	/* Now रुको क्रम EOT, or SUSP or OVR in हाल of error */
पूर्ण

/**
 * sपंचांग32_spi_dma_config - configure dma slave channel depending on current
 *			  transfer bits_per_word.
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @dma_conf: poपूर्णांकer to the dma_slave_config काष्ठाure
 * @dir: direction of the dma transfer
 */
अटल व्योम sपंचांग32_spi_dma_config(काष्ठा sपंचांग32_spi *spi,
				 काष्ठा dma_slave_config *dma_conf,
				 क्रमागत dma_transfer_direction dir)
अणु
	क्रमागत dma_slave_buswidth buswidth;
	u32 maxburst;

	अगर (spi->cur_bpw <= 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	अन्यथा अगर (spi->cur_bpw <= 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	अन्यथा
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;

	अगर (spi->cfg->has_fअगरo) अणु
		/* Valid क्रम DMA Half or Full Fअगरo threshold */
		अगर (spi->cur_fthlv == 2)
			maxburst = 1;
		अन्यथा
			maxburst = spi->cur_fthlv;
	पूर्ण अन्यथा अणु
		maxburst = 1;
	पूर्ण

	स_रखो(dma_conf, 0, माप(काष्ठा dma_slave_config));
	dma_conf->direction = dir;
	अगर (dma_conf->direction == DMA_DEV_TO_MEM) अणु /* RX */
		dma_conf->src_addr = spi->phys_addr + spi->cfg->regs->rx.reg;
		dma_conf->src_addr_width = buswidth;
		dma_conf->src_maxburst = maxburst;

		dev_dbg(spi->dev, "Rx DMA config buswidth=%d, maxburst=%d\n",
			buswidth, maxburst);
	पूर्ण अन्यथा अगर (dma_conf->direction == DMA_MEM_TO_DEV) अणु /* TX */
		dma_conf->dst_addr = spi->phys_addr + spi->cfg->regs->tx.reg;
		dma_conf->dst_addr_width = buswidth;
		dma_conf->dst_maxburst = maxburst;

		dev_dbg(spi->dev, "Tx DMA config buswidth=%d, maxburst=%d\n",
			buswidth, maxburst);
	पूर्ण
पूर्ण

/**
 * sपंचांग32f4_spi_transfer_one_irq - transfer a single spi_transfer using
 *				  पूर्णांकerrupts
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * It must वापसs 0 अगर the transfer is finished or 1 अगर the transfer is still
 * in progress.
 */
अटल पूर्णांक sपंचांग32f4_spi_transfer_one_irq(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 cr2 = 0;

	/* Enable the पूर्णांकerrupts relative to the current communication mode */
	अगर (spi->cur_comm == SPI_SIMPLEX_TX || spi->cur_comm == SPI_3WIRE_TX) अणु
		cr2 |= STM32F4_SPI_CR2_TXEIE;
	पूर्ण अन्यथा अगर (spi->cur_comm == SPI_FULL_DUPLEX ||
				spi->cur_comm == SPI_SIMPLEX_RX ||
				spi->cur_comm == SPI_3WIRE_RX) अणु
		/* In transmit-only mode, the OVR flag is set in the SR रेजिस्टर
		 * since the received data are never पढ़ो. Thereक्रमe set OVR
		 * पूर्णांकerrupt only when rx buffer is available.
		 */
		cr2 |= STM32F4_SPI_CR2_RXNEIE | STM32F4_SPI_CR2_ERRIE;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&spi->lock, flags);

	sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR2, cr2);

	sपंचांग32_spi_enable(spi);

	/* starting data transfer when buffer is loaded */
	अगर (spi->tx_buf)
		sपंचांग32f4_spi_ग_लिखो_tx(spi);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 1;
पूर्ण

/**
 * sपंचांग32h7_spi_transfer_one_irq - transfer a single spi_transfer using
 *				  पूर्णांकerrupts
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 *
 * It must वापसs 0 अगर the transfer is finished or 1 अगर the transfer is still
 * in progress.
 */
अटल पूर्णांक sपंचांग32h7_spi_transfer_one_irq(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;
	u32 ier = 0;

	/* Enable the पूर्णांकerrupts relative to the current communication mode */
	अगर (spi->tx_buf && spi->rx_buf)	/* Full Duplex */
		ier |= STM32H7_SPI_IER_DXPIE;
	अन्यथा अगर (spi->tx_buf)		/* Half-Duplex TX dir or Simplex TX */
		ier |= STM32H7_SPI_IER_TXPIE;
	अन्यथा अगर (spi->rx_buf)		/* Half-Duplex RX dir or Simplex RX */
		ier |= STM32H7_SPI_IER_RXPIE;

	/* Enable the पूर्णांकerrupts relative to the end of transfer */
	ier |= STM32H7_SPI_IER_EOTIE | STM32H7_SPI_IER_TXTFIE |
	       STM32H7_SPI_IER_OVRIE | STM32H7_SPI_IER_MODFIE;

	spin_lock_irqsave(&spi->lock, flags);

	sपंचांग32_spi_enable(spi);

	/* Be sure to have data in fअगरo beक्रमe starting data transfer */
	अगर (spi->tx_buf)
		sपंचांग32h7_spi_ग_लिखो_txfअगरo(spi);

	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_CSTART);

	ग_लिखोl_relaxed(ier, spi->base + STM32H7_SPI_IER);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 1;
पूर्ण

/**
 * sपंचांग32f4_spi_transfer_one_dma_start - Set SPI driver रेजिस्टरs to start
 *					transfer using DMA
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32f4_spi_transfer_one_dma_start(काष्ठा sपंचांग32_spi *spi)
अणु
	/* In DMA mode end of transfer is handled by DMA TX or RX callback. */
	अगर (spi->cur_comm == SPI_SIMPLEX_RX || spi->cur_comm == SPI_3WIRE_RX ||
	    spi->cur_comm == SPI_FULL_DUPLEX) अणु
		/*
		 * In transmit-only mode, the OVR flag is set in the SR रेजिस्टर
		 * since the received data are never पढ़ो. Thereक्रमe set OVR
		 * पूर्णांकerrupt only when rx buffer is available.
		 */
		sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR2, STM32F4_SPI_CR2_ERRIE);
	पूर्ण

	sपंचांग32_spi_enable(spi);
पूर्ण

/**
 * sपंचांग32h7_spi_transfer_one_dma_start - Set SPI driver रेजिस्टरs to start
 *					transfer using DMA
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32h7_spi_transfer_one_dma_start(काष्ठा sपंचांग32_spi *spi)
अणु
	/* Enable the पूर्णांकerrupts relative to the end of transfer */
	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_IER, STM32H7_SPI_IER_EOTIE |
						 STM32H7_SPI_IER_TXTFIE |
						 STM32H7_SPI_IER_OVRIE |
						 STM32H7_SPI_IER_MODFIE);

	sपंचांग32_spi_enable(spi);

	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_CSTART);
पूर्ण

/**
 * sपंचांग32_spi_transfer_one_dma - transfer a single spi_transfer using DMA
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @xfer: poपूर्णांकer to the spi_transfer काष्ठाure
 *
 * It must वापसs 0 अगर the transfer is finished or 1 अगर the transfer is still
 * in progress.
 */
अटल पूर्णांक sपंचांग32_spi_transfer_one_dma(काष्ठा sपंचांग32_spi *spi,
				      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा dma_slave_config tx_dma_conf, rx_dma_conf;
	काष्ठा dma_async_tx_descriptor *tx_dma_desc, *rx_dma_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spi->lock, flags);

	rx_dma_desc = शून्य;
	अगर (spi->rx_buf && spi->dma_rx) अणु
		sपंचांग32_spi_dma_config(spi, &rx_dma_conf, DMA_DEV_TO_MEM);
		dmaengine_slave_config(spi->dma_rx, &rx_dma_conf);

		/* Enable Rx DMA request */
		sपंचांग32_spi_set_bits(spi, spi->cfg->regs->dma_rx_en.reg,
				   spi->cfg->regs->dma_rx_en.mask);

		rx_dma_desc = dmaengine_prep_slave_sg(
					spi->dma_rx, xfer->rx_sg.sgl,
					xfer->rx_sg.nents,
					rx_dma_conf.direction,
					DMA_PREP_INTERRUPT);
	पूर्ण

	tx_dma_desc = शून्य;
	अगर (spi->tx_buf && spi->dma_tx) अणु
		sपंचांग32_spi_dma_config(spi, &tx_dma_conf, DMA_MEM_TO_DEV);
		dmaengine_slave_config(spi->dma_tx, &tx_dma_conf);

		tx_dma_desc = dmaengine_prep_slave_sg(
					spi->dma_tx, xfer->tx_sg.sgl,
					xfer->tx_sg.nents,
					tx_dma_conf.direction,
					DMA_PREP_INTERRUPT);
	पूर्ण

	अगर ((spi->tx_buf && spi->dma_tx && !tx_dma_desc) ||
	    (spi->rx_buf && spi->dma_rx && !rx_dma_desc))
		जाओ dma_desc_error;

	अगर (spi->cur_comm == SPI_FULL_DUPLEX && (!tx_dma_desc || !rx_dma_desc))
		जाओ dma_desc_error;

	अगर (rx_dma_desc) अणु
		rx_dma_desc->callback = spi->cfg->dma_rx_cb;
		rx_dma_desc->callback_param = spi;

		अगर (dma_submit_error(dmaengine_submit(rx_dma_desc))) अणु
			dev_err(spi->dev, "Rx DMA submit failed\n");
			जाओ dma_desc_error;
		पूर्ण
		/* Enable Rx DMA channel */
		dma_async_issue_pending(spi->dma_rx);
	पूर्ण

	अगर (tx_dma_desc) अणु
		अगर (spi->cur_comm == SPI_SIMPLEX_TX ||
		    spi->cur_comm == SPI_3WIRE_TX) अणु
			tx_dma_desc->callback = spi->cfg->dma_tx_cb;
			tx_dma_desc->callback_param = spi;
		पूर्ण

		अगर (dma_submit_error(dmaengine_submit(tx_dma_desc))) अणु
			dev_err(spi->dev, "Tx DMA submit failed\n");
			जाओ dma_submit_error;
		पूर्ण
		/* Enable Tx DMA channel */
		dma_async_issue_pending(spi->dma_tx);

		/* Enable Tx DMA request */
		sपंचांग32_spi_set_bits(spi, spi->cfg->regs->dma_tx_en.reg,
				   spi->cfg->regs->dma_tx_en.mask);
	पूर्ण

	spi->cfg->transfer_one_dma_start(spi);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 1;

dma_submit_error:
	अगर (spi->dma_rx)
		dmaengine_terminate_all(spi->dma_rx);

dma_desc_error:
	sपंचांग32_spi_clr_bits(spi, spi->cfg->regs->dma_rx_en.reg,
			   spi->cfg->regs->dma_rx_en.mask);

	spin_unlock_irqrestore(&spi->lock, flags);

	dev_info(spi->dev, "DMA issue: fall back to irq transfer\n");

	spi->cur_usedma = false;
	वापस spi->cfg->transfer_one_irq(spi);
पूर्ण

/**
 * sपंचांग32f4_spi_set_bpw - Configure bits per word
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32f4_spi_set_bpw(काष्ठा sपंचांग32_spi *spi)
अणु
	अगर (spi->cur_bpw == 16)
		sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_DFF);
	अन्यथा
		sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_DFF);
पूर्ण

/**
 * sपंचांग32h7_spi_set_bpw - configure bits per word
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल व्योम sपंचांग32h7_spi_set_bpw(काष्ठा sपंचांग32_spi *spi)
अणु
	u32 bpw, fthlv;
	u32 cfg1_clrb = 0, cfg1_setb = 0;

	bpw = spi->cur_bpw - 1;

	cfg1_clrb |= STM32H7_SPI_CFG1_DSIZE;
	cfg1_setb |= FIELD_PREP(STM32H7_SPI_CFG1_DSIZE, bpw);

	spi->cur_fthlv = sपंचांग32h7_spi_prepare_fthlv(spi, spi->cur_xferlen);
	fthlv = spi->cur_fthlv - 1;

	cfg1_clrb |= STM32H7_SPI_CFG1_FTHLV;
	cfg1_setb |= FIELD_PREP(STM32H7_SPI_CFG1_FTHLV, fthlv);

	ग_लिखोl_relaxed(
		(पढ़ोl_relaxed(spi->base + STM32H7_SPI_CFG1) &
		 ~cfg1_clrb) | cfg1_setb,
		spi->base + STM32H7_SPI_CFG1);
पूर्ण

/**
 * sपंचांग32_spi_set_mbr - Configure baud rate भागisor in master mode
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @mbrभाग: baud rate भागisor value
 */
अटल व्योम sपंचांग32_spi_set_mbr(काष्ठा sपंचांग32_spi *spi, u32 mbrभाग)
अणु
	u32 clrb = 0, setb = 0;

	clrb |= spi->cfg->regs->br.mask;
	setb |= (mbrभाग << spi->cfg->regs->br.shअगरt) & spi->cfg->regs->br.mask;

	ग_लिखोl_relaxed((पढ़ोl_relaxed(spi->base + spi->cfg->regs->br.reg) &
			~clrb) | setb,
		       spi->base + spi->cfg->regs->br.reg);
पूर्ण

/**
 * sपंचांग32_spi_communication_type - वापस transfer communication type
 * @spi_dev: poपूर्णांकer to the spi device
 * @transfer: poपूर्णांकer to spi transfer
 */
अटल अचिन्हित पूर्णांक sपंचांग32_spi_communication_type(काष्ठा spi_device *spi_dev,
						 काष्ठा spi_transfer *transfer)
अणु
	अचिन्हित पूर्णांक type = SPI_FULL_DUPLEX;

	अगर (spi_dev->mode & SPI_3WIRE) अणु /* MISO/MOSI संकेतs shared */
		/*
		 * SPI_3WIRE and xfer->tx_buf != शून्य and xfer->rx_buf != शून्य
		 * is क्रमbidden and unvalidated by SPI subप्रणाली so depending
		 * on the valid buffer, we can determine the direction of the
		 * transfer.
		 */
		अगर (!transfer->tx_buf)
			type = SPI_3WIRE_RX;
		अन्यथा
			type = SPI_3WIRE_TX;
	पूर्ण अन्यथा अणु
		अगर (!transfer->tx_buf)
			type = SPI_SIMPLEX_RX;
		अन्यथा अगर (!transfer->rx_buf)
			type = SPI_SIMPLEX_TX;
	पूर्ण

	वापस type;
पूर्ण

/**
 * sपंचांग32f4_spi_set_mode - configure communication mode
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @comm_type: type of communication to configure
 */
अटल पूर्णांक sपंचांग32f4_spi_set_mode(काष्ठा sपंचांग32_spi *spi, अचिन्हित पूर्णांक comm_type)
अणु
	अगर (comm_type == SPI_3WIRE_TX || comm_type == SPI_SIMPLEX_TX) अणु
		sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR1,
					STM32F4_SPI_CR1_BIDIMODE |
					STM32F4_SPI_CR1_BIDIOE);
	पूर्ण अन्यथा अगर (comm_type == SPI_FULL_DUPLEX ||
				comm_type == SPI_SIMPLEX_RX) अणु
		sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR1,
					STM32F4_SPI_CR1_BIDIMODE |
					STM32F4_SPI_CR1_BIDIOE);
	पूर्ण अन्यथा अगर (comm_type == SPI_3WIRE_RX) अणु
		sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR1,
					STM32F4_SPI_CR1_BIDIMODE);
		sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_CR1,
					STM32F4_SPI_CR1_BIDIOE);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sपंचांग32h7_spi_set_mode - configure communication mode
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @comm_type: type of communication to configure
 */
अटल पूर्णांक sपंचांग32h7_spi_set_mode(काष्ठा sपंचांग32_spi *spi, अचिन्हित पूर्णांक comm_type)
अणु
	u32 mode;
	u32 cfg2_clrb = 0, cfg2_setb = 0;

	अगर (comm_type == SPI_3WIRE_RX) अणु
		mode = STM32H7_SPI_HALF_DUPLEX;
		sपंचांग32_spi_clr_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_HDसूची);
	पूर्ण अन्यथा अगर (comm_type == SPI_3WIRE_TX) अणु
		mode = STM32H7_SPI_HALF_DUPLEX;
		sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_HDसूची);
	पूर्ण अन्यथा अगर (comm_type == SPI_SIMPLEX_RX) अणु
		mode = STM32H7_SPI_SIMPLEX_RX;
	पूर्ण अन्यथा अगर (comm_type == SPI_SIMPLEX_TX) अणु
		mode = STM32H7_SPI_SIMPLEX_TX;
	पूर्ण अन्यथा अणु
		mode = STM32H7_SPI_FULL_DUPLEX;
	पूर्ण

	cfg2_clrb |= STM32H7_SPI_CFG2_COMM;
	cfg2_setb |= FIELD_PREP(STM32H7_SPI_CFG2_COMM, mode);

	ग_लिखोl_relaxed(
		(पढ़ोl_relaxed(spi->base + STM32H7_SPI_CFG2) &
		 ~cfg2_clrb) | cfg2_setb,
		spi->base + STM32H7_SPI_CFG2);

	वापस 0;
पूर्ण

/**
 * sपंचांग32h7_spi_data_idleness - configure minimum समय delay inserted between two
 *			       consecutive data frames in master mode
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @len: transfer len
 */
अटल व्योम sपंचांग32h7_spi_data_idleness(काष्ठा sपंचांग32_spi *spi, u32 len)
अणु
	u32 cfg2_clrb = 0, cfg2_setb = 0;

	cfg2_clrb |= STM32H7_SPI_CFG2_MIDI;
	अगर ((len > 1) && (spi->cur_midi > 0)) अणु
		u32 sck_period_ns = DIV_ROUND_UP(NSEC_PER_SEC, spi->cur_speed);
		u32 midi = min_t(u32,
				 DIV_ROUND_UP(spi->cur_midi, sck_period_ns),
				 FIELD_GET(STM32H7_SPI_CFG2_MIDI,
				 STM32H7_SPI_CFG2_MIDI));


		dev_dbg(spi->dev, "period=%dns, midi=%d(=%dns)\n",
			sck_period_ns, midi, midi * sck_period_ns);
		cfg2_setb |= FIELD_PREP(STM32H7_SPI_CFG2_MIDI, midi);
	पूर्ण

	ग_लिखोl_relaxed((पढ़ोl_relaxed(spi->base + STM32H7_SPI_CFG2) &
			~cfg2_clrb) | cfg2_setb,
		       spi->base + STM32H7_SPI_CFG2);
पूर्ण

/**
 * sपंचांग32h7_spi_number_of_data - configure number of data at current transfer
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @nb_words: transfer length (in words)
 */
अटल पूर्णांक sपंचांग32h7_spi_number_of_data(काष्ठा sपंचांग32_spi *spi, u32 nb_words)
अणु
	अगर (nb_words <= STM32H7_SPI_TSIZE_MAX) अणु
		ग_लिखोl_relaxed(FIELD_PREP(STM32H7_SPI_CR2_TSIZE, nb_words),
			       spi->base + STM32H7_SPI_CR2);
	पूर्ण अन्यथा अणु
		वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sपंचांग32_spi_transfer_one_setup - common setup to transfer a single
 *				  spi_transfer either using DMA or
 *				  पूर्णांकerrupts.
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 * @spi_dev: poपूर्णांकer to the spi device
 * @transfer: poपूर्णांकer to spi transfer
 */
अटल पूर्णांक sपंचांग32_spi_transfer_one_setup(काष्ठा sपंचांग32_spi *spi,
					काष्ठा spi_device *spi_dev,
					काष्ठा spi_transfer *transfer)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक comm_type;
	पूर्णांक nb_words, ret = 0;
	पूर्णांक mbr;

	spin_lock_irqsave(&spi->lock, flags);

	spi->cur_xferlen = transfer->len;

	spi->cur_bpw = transfer->bits_per_word;
	spi->cfg->set_bpw(spi);

	/* Update spi->cur_speed with real घड़ी speed */
	mbr = sपंचांग32_spi_prepare_mbr(spi, transfer->speed_hz,
				    spi->cfg->baud_rate_भाग_min,
				    spi->cfg->baud_rate_भाग_max);
	अगर (mbr < 0) अणु
		ret = mbr;
		जाओ out;
	पूर्ण

	transfer->speed_hz = spi->cur_speed;
	sपंचांग32_spi_set_mbr(spi, mbr);

	comm_type = sपंचांग32_spi_communication_type(spi_dev, transfer);
	ret = spi->cfg->set_mode(spi, comm_type);
	अगर (ret < 0)
		जाओ out;

	spi->cur_comm = comm_type;

	अगर (spi->cfg->set_data_idleness)
		spi->cfg->set_data_idleness(spi, transfer->len);

	अगर (spi->cur_bpw <= 8)
		nb_words = transfer->len;
	अन्यथा अगर (spi->cur_bpw <= 16)
		nb_words = DIV_ROUND_UP(transfer->len * 8, 16);
	अन्यथा
		nb_words = DIV_ROUND_UP(transfer->len * 8, 32);

	अगर (spi->cfg->set_number_of_data) अणु
		ret = spi->cfg->set_number_of_data(spi, nb_words);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	dev_dbg(spi->dev, "transfer communication mode set to %d\n",
		spi->cur_comm);
	dev_dbg(spi->dev,
		"data frame of %d-bit, data packet of %d data frames\n",
		spi->cur_bpw, spi->cur_fthlv);
	dev_dbg(spi->dev, "speed set to %dHz\n", spi->cur_speed);
	dev_dbg(spi->dev, "transfer of %d bytes (%d data frames)\n",
		spi->cur_xferlen, nb_words);
	dev_dbg(spi->dev, "dma %s\n",
		(spi->cur_usedma) ? "enabled" : "disabled");

out:
	spin_unlock_irqrestore(&spi->lock, flags);

	वापस ret;
पूर्ण

/**
 * sपंचांग32_spi_transfer_one - transfer a single spi_transfer
 * @master: controller master पूर्णांकerface
 * @spi_dev: poपूर्णांकer to the spi device
 * @transfer: poपूर्णांकer to spi transfer
 *
 * It must वापस 0 अगर the transfer is finished or 1 अगर the transfer is still
 * in progress.
 */
अटल पूर्णांक sपंचांग32_spi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi_dev,
				  काष्ठा spi_transfer *transfer)
अणु
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	पूर्णांक ret;

	/* Don't करो anything on 0 bytes transfers */
	अगर (transfer->len == 0)
		वापस 0;

	spi->tx_buf = transfer->tx_buf;
	spi->rx_buf = transfer->rx_buf;
	spi->tx_len = spi->tx_buf ? transfer->len : 0;
	spi->rx_len = spi->rx_buf ? transfer->len : 0;

	spi->cur_usedma = (master->can_dma &&
			   master->can_dma(master, spi_dev, transfer));

	ret = sपंचांग32_spi_transfer_one_setup(spi, spi_dev, transfer);
	अगर (ret) अणु
		dev_err(spi->dev, "SPI transfer setup failed\n");
		वापस ret;
	पूर्ण

	अगर (spi->cur_usedma)
		वापस sपंचांग32_spi_transfer_one_dma(spi, transfer);
	अन्यथा
		वापस spi->cfg->transfer_one_irq(spi);
पूर्ण

/**
 * sपंचांग32_spi_unprepare_msg - relax the hardware
 * @master: controller master पूर्णांकerface
 * @msg: poपूर्णांकer to the spi message
 */
अटल पूर्णांक sपंचांग32_spi_unprepare_msg(काष्ठा spi_master *master,
				   काष्ठा spi_message *msg)
अणु
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);

	spi->cfg->disable(spi);

	वापस 0;
पूर्ण

/**
 * sपंचांग32f4_spi_config - Configure SPI controller as SPI master
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल पूर्णांक sपंचांग32f4_spi_config(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spi->lock, flags);

	/* Ensure I2SMOD bit is kept cleared */
	sपंचांग32_spi_clr_bits(spi, STM32F4_SPI_I2SCFGR,
			   STM32F4_SPI_I2SCFGR_I2SMOD);

	/*
	 * - SS input value high
	 * - transmitter half duplex direction
	 * - Set the master mode (शेष Motorola mode)
	 * - Consider 1 master/n slaves configuration and
	 *   SS input value is determined by the SSI bit
	 */
	sपंचांग32_spi_set_bits(spi, STM32F4_SPI_CR1, STM32F4_SPI_CR1_SSI |
						 STM32F4_SPI_CR1_BIDIOE |
						 STM32F4_SPI_CR1_MSTR |
						 STM32F4_SPI_CR1_SSM);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 0;
पूर्ण

/**
 * sपंचांग32h7_spi_config - Configure SPI controller as SPI master
 * @spi: poपूर्णांकer to the spi controller data काष्ठाure
 */
अटल पूर्णांक sपंचांग32h7_spi_config(काष्ठा sपंचांग32_spi *spi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spi->lock, flags);

	/* Ensure I2SMOD bit is kept cleared */
	sपंचांग32_spi_clr_bits(spi, STM32H7_SPI_I2SCFGR,
			   STM32H7_SPI_I2SCFGR_I2SMOD);

	/*
	 * - SS input value high
	 * - transmitter half duplex direction
	 * - स्वतःmatic communication suspend when RX-Fअगरo is full
	 */
	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CR1, STM32H7_SPI_CR1_SSI |
						 STM32H7_SPI_CR1_HDसूची |
						 STM32H7_SPI_CR1_MASRX);

	/*
	 * - Set the master mode (शेष Motorola mode)
	 * - Consider 1 master/n slaves configuration and
	 *   SS input value is determined by the SSI bit
	 * - keep control of all associated GPIOs
	 */
	sपंचांग32_spi_set_bits(spi, STM32H7_SPI_CFG2, STM32H7_SPI_CFG2_MASTER |
						  STM32H7_SPI_CFG2_SSM |
						  STM32H7_SPI_CFG2_AFCNTR);

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_spi_cfg sपंचांग32f4_spi_cfg = अणु
	.regs = &sपंचांग32f4_spi_regspec,
	.get_bpw_mask = sपंचांग32f4_spi_get_bpw_mask,
	.disable = sपंचांग32f4_spi_disable,
	.config = sपंचांग32f4_spi_config,
	.set_bpw = sपंचांग32f4_spi_set_bpw,
	.set_mode = sपंचांग32f4_spi_set_mode,
	.transfer_one_dma_start = sपंचांग32f4_spi_transfer_one_dma_start,
	.dma_tx_cb = sपंचांग32f4_spi_dma_tx_cb,
	.dma_rx_cb = sपंचांग32f4_spi_dma_rx_cb,
	.transfer_one_irq = sपंचांग32f4_spi_transfer_one_irq,
	.irq_handler_event = sपंचांग32f4_spi_irq_event,
	.irq_handler_thपढ़ो = sपंचांग32f4_spi_irq_thपढ़ो,
	.baud_rate_भाग_min = STM32F4_SPI_BR_DIV_MIN,
	.baud_rate_भाग_max = STM32F4_SPI_BR_DIV_MAX,
	.has_fअगरo = false,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_spi_cfg sपंचांग32h7_spi_cfg = अणु
	.regs = &sपंचांग32h7_spi_regspec,
	.get_fअगरo_size = sपंचांग32h7_spi_get_fअगरo_size,
	.get_bpw_mask = sपंचांग32h7_spi_get_bpw_mask,
	.disable = sपंचांग32h7_spi_disable,
	.config = sपंचांग32h7_spi_config,
	.set_bpw = sपंचांग32h7_spi_set_bpw,
	.set_mode = sपंचांग32h7_spi_set_mode,
	.set_data_idleness = sपंचांग32h7_spi_data_idleness,
	.set_number_of_data = sपंचांग32h7_spi_number_of_data,
	.transfer_one_dma_start = sपंचांग32h7_spi_transfer_one_dma_start,
	.dma_rx_cb = sपंचांग32h7_spi_dma_cb,
	.dma_tx_cb = sपंचांग32h7_spi_dma_cb,
	.transfer_one_irq = sपंचांग32h7_spi_transfer_one_irq,
	.irq_handler_thपढ़ो = sपंचांग32h7_spi_irq_thपढ़ो,
	.baud_rate_भाग_min = STM32H7_SPI_MBR_DIV_MIN,
	.baud_rate_भाग_max = STM32H7_SPI_MBR_DIV_MAX,
	.has_fअगरo = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_spi_of_match[] = अणु
	अणु .compatible = "st,stm32h7-spi", .data = (व्योम *)&sपंचांग32h7_spi_cfg पूर्ण,
	अणु .compatible = "st,stm32f4-spi", .data = (व्योम *)&sपंचांग32f4_spi_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_spi_of_match);

अटल पूर्णांक sपंचांग32_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा sपंचांग32_spi *spi;
	काष्ठा resource *res;
	काष्ठा reset_control *rst;
	पूर्णांक ret;

	master = devm_spi_alloc_master(&pdev->dev, माप(काष्ठा sपंचांग32_spi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "spi master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, master);

	spi = spi_master_get_devdata(master);
	spi->dev = &pdev->dev;
	spi->master = master;
	spin_lock_init(&spi->lock);

	spi->cfg = (स्थिर काष्ठा sपंचांग32_spi_cfg *)
		of_match_device(pdev->dev.driver->of_match_table,
				&pdev->dev)->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	spi->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(spi->base))
		वापस PTR_ERR(spi->base);

	spi->phys_addr = (dma_addr_t)res->start;

	spi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (spi->irq <= 0)
		वापस dev_err_probe(&pdev->dev, spi->irq,
				     "failed to get irq\n");

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, spi->irq,
					spi->cfg->irq_handler_event,
					spi->cfg->irq_handler_thपढ़ो,
					IRQF_ONESHOT, pdev->name, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq%d request failed: %d\n", spi->irq,
			ret);
		वापस ret;
	पूर्ण

	spi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(spi->clk)) अणु
		ret = PTR_ERR(spi->clk);
		dev_err(&pdev->dev, "clk get failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(spi->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk enable failed: %d\n", ret);
		वापस ret;
	पूर्ण
	spi->clk_rate = clk_get_rate(spi->clk);
	अगर (!spi->clk_rate) अणु
		dev_err(&pdev->dev, "clk rate = 0\n");
		ret = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	rst = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (rst) अणु
		अगर (IS_ERR(rst)) अणु
			ret = dev_err_probe(&pdev->dev, PTR_ERR(rst),
					    "failed to get reset\n");
			जाओ err_clk_disable;
		पूर्ण

		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	अगर (spi->cfg->has_fअगरo)
		spi->fअगरo_size = spi->cfg->get_fअगरo_size(spi);

	ret = spi->cfg->config(spi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "controller configuration failed: %d\n",
			ret);
		जाओ err_clk_disable;
	पूर्ण

	master->dev.of_node = pdev->dev.of_node;
	master->स्वतः_runसमय_pm = true;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_CS_HIGH | SPI_LSB_FIRST |
			    SPI_3WIRE;
	master->bits_per_word_mask = spi->cfg->get_bpw_mask(spi);
	master->max_speed_hz = spi->clk_rate / spi->cfg->baud_rate_भाग_min;
	master->min_speed_hz = spi->clk_rate / spi->cfg->baud_rate_भाग_max;
	master->use_gpio_descriptors = true;
	master->prepare_message = sपंचांग32_spi_prepare_msg;
	master->transfer_one = sपंचांग32_spi_transfer_one;
	master->unprepare_message = sपंचांग32_spi_unprepare_msg;
	master->flags = SPI_MASTER_MUST_TX;

	spi->dma_tx = dma_request_chan(spi->dev, "tx");
	अगर (IS_ERR(spi->dma_tx)) अणु
		ret = PTR_ERR(spi->dma_tx);
		spi->dma_tx = शून्य;
		अगर (ret == -EPROBE_DEFER)
			जाओ err_clk_disable;

		dev_warn(&pdev->dev, "failed to request tx dma channel\n");
	पूर्ण अन्यथा अणु
		master->dma_tx = spi->dma_tx;
	पूर्ण

	spi->dma_rx = dma_request_chan(spi->dev, "rx");
	अगर (IS_ERR(spi->dma_rx)) अणु
		ret = PTR_ERR(spi->dma_rx);
		spi->dma_rx = शून्य;
		अगर (ret == -EPROBE_DEFER)
			जाओ err_dma_release;

		dev_warn(&pdev->dev, "failed to request rx dma channel\n");
	पूर्ण अन्यथा अणु
		master->dma_rx = spi->dma_rx;
	पूर्ण

	अगर (spi->dma_tx || spi->dma_rx)
		master->can_dma = sपंचांग32_spi_can_dma;

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = spi_रेजिस्टर_master(master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "spi master registration failed: %d\n",
			ret);
		जाओ err_pm_disable;
	पूर्ण

	dev_info(&pdev->dev, "driver initialized\n");

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err_dma_release:
	अगर (spi->dma_tx)
		dma_release_channel(spi->dma_tx);
	अगर (spi->dma_rx)
		dma_release_channel(spi->dma_rx);
err_clk_disable:
	clk_disable_unprepare(spi->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);

	spi_unरेजिस्टर_master(master);
	spi->cfg->disable(spi);

	अगर (master->dma_tx)
		dma_release_channel(master->dma_tx);
	अगर (master->dma_rx)
		dma_release_channel(master->dma_rx);

	clk_disable_unprepare(spi->clk);

	pm_runसमय_disable(&pdev->dev);

	pinctrl_pm_select_sleep_state(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);

	clk_disable_unprepare(spi->clk);

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(spi->clk);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_spi *spi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		वापस ret;

	ret = spi_master_resume(master);
	अगर (ret) अणु
		clk_disable_unprepare(spi->clk);
		वापस ret;
	पूर्ण

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		dev_err(dev, "Unable to power device:%d\n", ret);
		वापस ret;
	पूर्ण

	spi->cfg->config(spi);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_spi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_spi_suspend, sपंचांग32_spi_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_spi_runसमय_suspend,
			   sपंचांग32_spi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_spi_driver = अणु
	.probe = sपंचांग32_spi_probe,
	.हटाओ = sपंचांग32_spi_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.pm = &sपंचांग32_spi_pm_ops,
		.of_match_table = sपंचांग32_spi_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_spi_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_DESCRIPTION("STMicroelectronics STM32 SPI Controller driver");
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_LICENSE("GPL v2");
