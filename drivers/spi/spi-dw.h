<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DW_SPI_HEADER_H
#घोषणा DW_SPI_HEADER_H

#समावेश <linux/bits.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पन.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/bitfield.h>

/* Register offsets */
#घोषणा DW_SPI_CTRLR0			0x00
#घोषणा DW_SPI_CTRLR1			0x04
#घोषणा DW_SPI_SSIENR			0x08
#घोषणा DW_SPI_MWCR			0x0c
#घोषणा DW_SPI_SER			0x10
#घोषणा DW_SPI_BAUDR			0x14
#घोषणा DW_SPI_TXFTLR			0x18
#घोषणा DW_SPI_RXFTLR			0x1c
#घोषणा DW_SPI_TXFLR			0x20
#घोषणा DW_SPI_RXFLR			0x24
#घोषणा DW_SPI_SR			0x28
#घोषणा DW_SPI_IMR			0x2c
#घोषणा DW_SPI_ISR			0x30
#घोषणा DW_SPI_RISR			0x34
#घोषणा DW_SPI_TXOICR			0x38
#घोषणा DW_SPI_RXOICR			0x3c
#घोषणा DW_SPI_RXUICR			0x40
#घोषणा DW_SPI_MSTICR			0x44
#घोषणा DW_SPI_ICR			0x48
#घोषणा DW_SPI_DMACR			0x4c
#घोषणा DW_SPI_DMATDLR			0x50
#घोषणा DW_SPI_DMARDLR			0x54
#घोषणा DW_SPI_IDR			0x58
#घोषणा DW_SPI_VERSION			0x5c
#घोषणा DW_SPI_DR			0x60
#घोषणा DW_SPI_RX_SAMPLE_DLY		0xf0
#घोषणा DW_SPI_CS_OVERRIDE		0xf4

/* Bit fields in CTRLR0 */
#घोषणा SPI_DFS_OFFSET			0
#घोषणा SPI_DFS_MASK			GENMASK(3, 0)
#घोषणा SPI_DFS32_OFFSET		16

#घोषणा SPI_FRF_OFFSET			4
#घोषणा SPI_FRF_SPI			0x0
#घोषणा SPI_FRF_SSP			0x1
#घोषणा SPI_FRF_MICROWIRE		0x2
#घोषणा SPI_FRF_RESV			0x3

#घोषणा SPI_MODE_OFFSET			6
#घोषणा SPI_SCPH_OFFSET			6
#घोषणा SPI_SCOL_OFFSET			7

#घोषणा SPI_TMOD_OFFSET			8
#घोषणा SPI_TMOD_MASK			(0x3 << SPI_TMOD_OFFSET)
#घोषणा	SPI_TMOD_TR			0x0		/* xmit & recv */
#घोषणा SPI_TMOD_TO			0x1		/* xmit only */
#घोषणा SPI_TMOD_RO			0x2		/* recv only */
#घोषणा SPI_TMOD_EPROMREAD		0x3		/* eeprom पढ़ो mode */

#घोषणा SPI_SLVOE_OFFSET		10
#घोषणा SPI_SRL_OFFSET			11
#घोषणा SPI_CFS_OFFSET			12

/* Bit fields in CTRLR0 based on DWC_ssi_databook.pdf v1.01a */
#घोषणा DWC_SSI_CTRLR0_SRL_OFFSET	13
#घोषणा DWC_SSI_CTRLR0_TMOD_OFFSET	10
#घोषणा DWC_SSI_CTRLR0_TMOD_MASK	GENMASK(11, 10)
#घोषणा DWC_SSI_CTRLR0_SCPOL_OFFSET	9
#घोषणा DWC_SSI_CTRLR0_SCPH_OFFSET	8
#घोषणा DWC_SSI_CTRLR0_FRF_OFFSET	6
#घोषणा DWC_SSI_CTRLR0_DFS_OFFSET	0

/*
 * For Keem Bay, CTRLR0[31] is used to select controller mode.
 * 0: SSI is slave
 * 1: SSI is master
 */
#घोषणा DWC_SSI_CTRLR0_KEEMBAY_MST	BIT(31)

/* Bit fields in CTRLR1 */
#घोषणा SPI_NDF_MASK			GENMASK(15, 0)

/* Bit fields in SR, 7 bits */
#घोषणा SR_MASK				0x7f		/* cover 7 bits */
#घोषणा SR_BUSY				(1 << 0)
#घोषणा SR_TF_NOT_FULL			(1 << 1)
#घोषणा SR_TF_EMPT			(1 << 2)
#घोषणा SR_RF_NOT_EMPT			(1 << 3)
#घोषणा SR_RF_FULL			(1 << 4)
#घोषणा SR_TX_ERR			(1 << 5)
#घोषणा SR_DCOL				(1 << 6)

/* Bit fields in ISR, IMR, RISR, 7 bits */
#घोषणा SPI_INT_TXEI			(1 << 0)
#घोषणा SPI_INT_TXOI			(1 << 1)
#घोषणा SPI_INT_RXUI			(1 << 2)
#घोषणा SPI_INT_RXOI			(1 << 3)
#घोषणा SPI_INT_RXFI			(1 << 4)
#घोषणा SPI_INT_MSTI			(1 << 5)

/* Bit fields in DMACR */
#घोषणा SPI_DMA_RDMAE			(1 << 0)
#घोषणा SPI_DMA_TDMAE			(1 << 1)

#घोषणा SPI_WAIT_RETRIES		5
#घोषणा SPI_BUF_SIZE \
	(माप_field(काष्ठा spi_mem_op, cmd.opcode) + \
	 माप_field(काष्ठा spi_mem_op, addr.val) + 256)
#घोषणा SPI_GET_BYTE(_val, _idx) \
	((_val) >> (BITS_PER_BYTE * (_idx)) & 0xff)

क्रमागत dw_ssi_type अणु
	SSI_MOTO_SPI = 0,
	SSI_TI_SSP,
	SSI_NS_MICROWIRE,
पूर्ण;

/* DW SPI capabilities */
#घोषणा DW_SPI_CAP_CS_OVERRIDE		BIT(0)
#घोषणा DW_SPI_CAP_KEEMBAY_MST		BIT(1)
#घोषणा DW_SPI_CAP_DWC_SSI		BIT(2)
#घोषणा DW_SPI_CAP_DFS32		BIT(3)

/* Slave spi_transfer/spi_mem_op related */
काष्ठा dw_spi_cfg अणु
	u8 पंचांगode;
	u8 dfs;
	u32 ndf;
	u32 freq;
पूर्ण;

काष्ठा dw_spi;
काष्ठा dw_spi_dma_ops अणु
	पूर्णांक (*dma_init)(काष्ठा device *dev, काष्ठा dw_spi *dws);
	व्योम (*dma_निकास)(काष्ठा dw_spi *dws);
	पूर्णांक (*dma_setup)(काष्ठा dw_spi *dws, काष्ठा spi_transfer *xfer);
	bool (*can_dma)(काष्ठा spi_controller *master, काष्ठा spi_device *spi,
			काष्ठा spi_transfer *xfer);
	पूर्णांक (*dma_transfer)(काष्ठा dw_spi *dws, काष्ठा spi_transfer *xfer);
	व्योम (*dma_stop)(काष्ठा dw_spi *dws);
पूर्ण;

काष्ठा dw_spi अणु
	काष्ठा spi_controller	*master;

	व्योम __iomem		*regs;
	अचिन्हित दीर्घ		paddr;
	पूर्णांक			irq;
	u32			fअगरo_len;	/* depth of the FIFO buffer */
	अचिन्हित पूर्णांक		dfs_offset;     /* CTRLR0 DFS field offset */
	u32			max_mem_freq;	/* max mem-ops bus freq */
	u32			max_freq;	/* max bus freq supported */

	u32			caps;		/* DW SPI capabilities */

	u32			reg_io_width;	/* DR I/O width in bytes */
	u16			bus_num;
	u16			num_cs;		/* supported slave numbers */
	व्योम (*set_cs)(काष्ठा spi_device *spi, bool enable);

	/* Current message transfer state info */
	व्योम			*tx;
	अचिन्हित पूर्णांक		tx_len;
	व्योम			*rx;
	अचिन्हित पूर्णांक		rx_len;
	u8			buf[SPI_BUF_SIZE];
	पूर्णांक			dma_mapped;
	u8			n_bytes;	/* current is a 1/2 bytes op */
	irqवापस_t		(*transfer_handler)(काष्ठा dw_spi *dws);
	u32			current_freq;	/* frequency in hz */
	u32			cur_rx_sample_dly;
	u32			def_rx_sample_dly_ns;

	/* Custom memory operations */
	काष्ठा spi_controller_mem_ops mem_ops;

	/* DMA info */
	काष्ठा dma_chan		*txchan;
	u32			txburst;
	काष्ठा dma_chan		*rxchan;
	u32			rxburst;
	u32			dma_sg_burst;
	अचिन्हित दीर्घ		dma_chan_busy;
	dma_addr_t		dma_addr; /* phy address of the Data रेजिस्टर */
	स्थिर काष्ठा dw_spi_dma_ops *dma_ops;
	काष्ठा completion	dma_completion;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs;
	काष्ठा debugfs_regset32 regset;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत u32 dw_पढ़ोl(काष्ठा dw_spi *dws, u32 offset)
अणु
	वापस __raw_पढ़ोl(dws->regs + offset);
पूर्ण

अटल अंतरभूत व्योम dw_ग_लिखोl(काष्ठा dw_spi *dws, u32 offset, u32 val)
अणु
	__raw_ग_लिखोl(val, dws->regs + offset);
पूर्ण

अटल अंतरभूत u32 dw_पढ़ो_io_reg(काष्ठा dw_spi *dws, u32 offset)
अणु
	चयन (dws->reg_io_width) अणु
	हाल 2:
		वापस पढ़ोw_relaxed(dws->regs + offset);
	हाल 4:
	शेष:
		वापस पढ़ोl_relaxed(dws->regs + offset);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dw_ग_लिखो_io_reg(काष्ठा dw_spi *dws, u32 offset, u32 val)
अणु
	चयन (dws->reg_io_width) अणु
	हाल 2:
		ग_लिखोw_relaxed(val, dws->regs + offset);
		अवरोध;
	हाल 4:
	शेष:
		ग_लिखोl_relaxed(val, dws->regs + offset);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम spi_enable_chip(काष्ठा dw_spi *dws, पूर्णांक enable)
अणु
	dw_ग_लिखोl(dws, DW_SPI_SSIENR, (enable ? 1 : 0));
पूर्ण

अटल अंतरभूत व्योम spi_set_clk(काष्ठा dw_spi *dws, u16 भाग)
अणु
	dw_ग_लिखोl(dws, DW_SPI_BAUDR, भाग);
पूर्ण

/* Disable IRQ bits */
अटल अंतरभूत व्योम spi_mask_पूर्णांकr(काष्ठा dw_spi *dws, u32 mask)
अणु
	u32 new_mask;

	new_mask = dw_पढ़ोl(dws, DW_SPI_IMR) & ~mask;
	dw_ग_लिखोl(dws, DW_SPI_IMR, new_mask);
पूर्ण

/* Enable IRQ bits */
अटल अंतरभूत व्योम spi_umask_पूर्णांकr(काष्ठा dw_spi *dws, u32 mask)
अणु
	u32 new_mask;

	new_mask = dw_पढ़ोl(dws, DW_SPI_IMR) | mask;
	dw_ग_लिखोl(dws, DW_SPI_IMR, new_mask);
पूर्ण

/*
 * This disables the SPI controller, पूर्णांकerrupts, clears the पूर्णांकerrupts status
 * and CS, then re-enables the controller back. Transmit and receive FIFO
 * buffers are cleared when the device is disabled.
 */
अटल अंतरभूत व्योम spi_reset_chip(काष्ठा dw_spi *dws)
अणु
	spi_enable_chip(dws, 0);
	spi_mask_पूर्णांकr(dws, 0xff);
	dw_पढ़ोl(dws, DW_SPI_ICR);
	dw_ग_लिखोl(dws, DW_SPI_SER, 0);
	spi_enable_chip(dws, 1);
पूर्ण

अटल अंतरभूत व्योम spi_shutकरोwn_chip(काष्ठा dw_spi *dws)
अणु
	spi_enable_chip(dws, 0);
	spi_set_clk(dws, 0);
पूर्ण

बाह्य व्योम dw_spi_set_cs(काष्ठा spi_device *spi, bool enable);
बाह्य व्योम dw_spi_update_config(काष्ठा dw_spi *dws, काष्ठा spi_device *spi,
				 काष्ठा dw_spi_cfg *cfg);
बाह्य पूर्णांक dw_spi_check_status(काष्ठा dw_spi *dws, bool raw);
बाह्य पूर्णांक dw_spi_add_host(काष्ठा device *dev, काष्ठा dw_spi *dws);
बाह्य व्योम dw_spi_हटाओ_host(काष्ठा dw_spi *dws);
बाह्य पूर्णांक dw_spi_suspend_host(काष्ठा dw_spi *dws);
बाह्य पूर्णांक dw_spi_resume_host(काष्ठा dw_spi *dws);

#अगर_घोषित CONFIG_SPI_DW_DMA

बाह्य व्योम dw_spi_dma_setup_mfld(काष्ठा dw_spi *dws);
बाह्य व्योम dw_spi_dma_setup_generic(काष्ठा dw_spi *dws);

#अन्यथा

अटल अंतरभूत व्योम dw_spi_dma_setup_mfld(काष्ठा dw_spi *dws) अणुपूर्ण
अटल अंतरभूत व्योम dw_spi_dma_setup_generic(काष्ठा dw_spi *dws) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_SPI_DW_DMA */

#पूर्ण_अगर /* DW_SPI_HEADER_H */
