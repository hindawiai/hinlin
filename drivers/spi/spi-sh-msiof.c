<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH MSIOF SPI Controller Interface
 *
 * Copyright (c) 2009 Magnus Damm
 * Copyright (C) 2014 Renesas Electronics Corporation
 * Copyright (C) 2014-2017 Glider bvba
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_dma.h>

#समावेश <linux/spi/sh_msiof.h>
#समावेश <linux/spi/spi.h>

#समावेश <यंत्र/unaligned.h>

काष्ठा sh_msiof_chipdata अणु
	u32 bits_per_word_mask;
	u16 tx_fअगरo_size;
	u16 rx_fअगरo_size;
	u16 ctlr_flags;
	u16 min_भाग_घात;
पूर्ण;

काष्ठा sh_msiof_spi_priv अणु
	काष्ठा spi_controller *ctlr;
	व्योम __iomem *mapbase;
	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा sh_msiof_spi_info *info;
	काष्ठा completion करोne;
	काष्ठा completion करोne_txdma;
	अचिन्हित पूर्णांक tx_fअगरo_size;
	अचिन्हित पूर्णांक rx_fअगरo_size;
	अचिन्हित पूर्णांक min_भाग_घात;
	व्योम *tx_dma_page;
	व्योम *rx_dma_page;
	dma_addr_t tx_dma_addr;
	dma_addr_t rx_dma_addr;
	bool native_cs_inited;
	bool native_cs_high;
	bool slave_पातed;
पूर्ण;

#घोषणा MAX_SS	3	/* Maximum number of native chip selects */

#घोषणा SITMDR1	0x00	/* Transmit Mode Register 1 */
#घोषणा SITMDR2	0x04	/* Transmit Mode Register 2 */
#घोषणा SITMDR3	0x08	/* Transmit Mode Register 3 */
#घोषणा SIRMDR1	0x10	/* Receive Mode Register 1 */
#घोषणा SIRMDR2	0x14	/* Receive Mode Register 2 */
#घोषणा SIRMDR3	0x18	/* Receive Mode Register 3 */
#घोषणा SITSCR	0x20	/* Transmit Clock Select Register */
#घोषणा SIRSCR	0x22	/* Receive Clock Select Register (SH, A1, APE6) */
#घोषणा SICTR	0x28	/* Control Register */
#घोषणा SIFCTR	0x30	/* FIFO Control Register */
#घोषणा SISTR	0x40	/* Status Register */
#घोषणा SIIER	0x44	/* Interrupt Enable Register */
#घोषणा SITDR1	0x48	/* Transmit Control Data Register 1 (SH, A1) */
#घोषणा SITDR2	0x4c	/* Transmit Control Data Register 2 (SH, A1) */
#घोषणा SITFDR	0x50	/* Transmit FIFO Data Register */
#घोषणा SIRDR1	0x58	/* Receive Control Data Register 1 (SH, A1) */
#घोषणा SIRDR2	0x5c	/* Receive Control Data Register 2 (SH, A1) */
#घोषणा SIRFDR	0x60	/* Receive FIFO Data Register */

/* SITMDR1 and SIRMDR1 */
#घोषणा SIMDR1_TRMD		BIT(31)		/* Transfer Mode (1 = Master mode) */
#घोषणा SIMDR1_SYNCMD_MASK	GENMASK(29, 28)	/* SYNC Mode */
#घोषणा SIMDR1_SYNCMD_SPI	(2 << 28)	/*   Level mode/SPI */
#घोषणा SIMDR1_SYNCMD_LR	(3 << 28)	/*   L/R mode */
#घोषणा SIMDR1_SYNCAC_SHIFT	25		/* Sync Polarity (1 = Active-low) */
#घोषणा SIMDR1_BITLSB_SHIFT	24		/* MSB/LSB First (1 = LSB first) */
#घोषणा SIMDR1_DTDL_SHIFT	20		/* Data Pin Bit Delay क्रम MSIOF_SYNC */
#घोषणा SIMDR1_SYNCDL_SHIFT	16		/* Frame Sync Signal Timing Delay */
#घोषणा SIMDR1_FLD_MASK		GENMASK(3, 2)	/* Frame Sync Signal Interval (0-3) */
#घोषणा SIMDR1_FLD_SHIFT	2
#घोषणा SIMDR1_XXSTP		BIT(0)		/* Transmission/Reception Stop on FIFO */
/* SITMDR1 */
#घोषणा SITMDR1_PCON		BIT(30)		/* Transfer Signal Connection */
#घोषणा SITMDR1_SYNCCH_MASK	GENMASK(27, 26)	/* Sync Signal Channel Select */
#घोषणा SITMDR1_SYNCCH_SHIFT	26		/* 0=MSIOF_SYNC, 1=MSIOF_SS1, 2=MSIOF_SS2 */

/* SITMDR2 and SIRMDR2 */
#घोषणा SIMDR2_BITLEN1(i)	(((i) - 1) << 24) /* Data Size (8-32 bits) */
#घोषणा SIMDR2_WDLEN1(i)	(((i) - 1) << 16) /* Word Count (1-64/256 (SH, A1))) */
#घोषणा SIMDR2_GRPMASK1		BIT(0)		/* Group Output Mask 1 (SH, A1) */

/* SITSCR and SIRSCR */
#घोषणा SISCR_BRPS_MASK		GENMASK(12, 8)	/* Prescaler Setting (1-32) */
#घोषणा SISCR_BRPS(i)		(((i) - 1) << 8)
#घोषणा SISCR_BRDV_MASK		GENMASK(2, 0)	/* Baud Rate Generator's Division Ratio */
#घोषणा SISCR_BRDV_DIV_2	0
#घोषणा SISCR_BRDV_DIV_4	1
#घोषणा SISCR_BRDV_DIV_8	2
#घोषणा SISCR_BRDV_DIV_16	3
#घोषणा SISCR_BRDV_DIV_32	4
#घोषणा SISCR_BRDV_DIV_1	7

/* SICTR */
#घोषणा SICTR_TSCKIZ_MASK	GENMASK(31, 30)	/* Transmit Clock I/O Polarity Select */
#घोषणा SICTR_TSCKIZ_SCK	BIT(31)		/*   Disable SCK when TX disabled */
#घोषणा SICTR_TSCKIZ_POL_SHIFT	30		/*   Transmit Clock Polarity */
#घोषणा SICTR_RSCKIZ_MASK	GENMASK(29, 28) /* Receive Clock Polarity Select */
#घोषणा SICTR_RSCKIZ_SCK	BIT(29)		/*   Must match CTR_TSCKIZ_SCK */
#घोषणा SICTR_RSCKIZ_POL_SHIFT	28		/*   Receive Clock Polarity */
#घोषणा SICTR_TEDG_SHIFT	27		/* Transmit Timing (1 = falling edge) */
#घोषणा SICTR_REDG_SHIFT	26		/* Receive Timing (1 = falling edge) */
#घोषणा SICTR_TXDIZ_MASK	GENMASK(23, 22)	/* Pin Output When TX is Disabled */
#घोषणा SICTR_TXDIZ_LOW		(0 << 22)	/*   0 */
#घोषणा SICTR_TXDIZ_HIGH	(1 << 22)	/*   1 */
#घोषणा SICTR_TXDIZ_HIZ		(2 << 22)	/*   High-impedance */
#घोषणा SICTR_TSCKE		BIT(15)		/* Transmit Serial Clock Output Enable */
#घोषणा SICTR_TFSE		BIT(14)		/* Transmit Frame Sync Signal Output Enable */
#घोषणा SICTR_TXE		BIT(9)		/* Transmit Enable */
#घोषणा SICTR_RXE		BIT(8)		/* Receive Enable */
#घोषणा SICTR_TXRST		BIT(1)		/* Transmit Reset */
#घोषणा SICTR_RXRST		BIT(0)		/* Receive Reset */

/* SIFCTR */
#घोषणा SIFCTR_TFWM_MASK	GENMASK(31, 29)	/* Transmit FIFO Watermark */
#घोषणा SIFCTR_TFWM_64		(0 << 29)	/*  Transfer Request when 64 empty stages */
#घोषणा SIFCTR_TFWM_32		(1 << 29)	/*  Transfer Request when 32 empty stages */
#घोषणा SIFCTR_TFWM_24		(2 << 29)	/*  Transfer Request when 24 empty stages */
#घोषणा SIFCTR_TFWM_16		(3 << 29)	/*  Transfer Request when 16 empty stages */
#घोषणा SIFCTR_TFWM_12		(4 << 29)	/*  Transfer Request when 12 empty stages */
#घोषणा SIFCTR_TFWM_8		(5 << 29)	/*  Transfer Request when 8 empty stages */
#घोषणा SIFCTR_TFWM_4		(6 << 29)	/*  Transfer Request when 4 empty stages */
#घोषणा SIFCTR_TFWM_1		(7 << 29)	/*  Transfer Request when 1 empty stage */
#घोषणा SIFCTR_TFUA_MASK	GENMASK(26, 20) /* Transmit FIFO Usable Area */
#घोषणा SIFCTR_TFUA_SHIFT	20
#घोषणा SIFCTR_TFUA(i)		((i) << SIFCTR_TFUA_SHIFT)
#घोषणा SIFCTR_RFWM_MASK	GENMASK(15, 13)	/* Receive FIFO Watermark */
#घोषणा SIFCTR_RFWM_1		(0 << 13)	/*  Transfer Request when 1 valid stages */
#घोषणा SIFCTR_RFWM_4		(1 << 13)	/*  Transfer Request when 4 valid stages */
#घोषणा SIFCTR_RFWM_8		(2 << 13)	/*  Transfer Request when 8 valid stages */
#घोषणा SIFCTR_RFWM_16		(3 << 13)	/*  Transfer Request when 16 valid stages */
#घोषणा SIFCTR_RFWM_32		(4 << 13)	/*  Transfer Request when 32 valid stages */
#घोषणा SIFCTR_RFWM_64		(5 << 13)	/*  Transfer Request when 64 valid stages */
#घोषणा SIFCTR_RFWM_128		(6 << 13)	/*  Transfer Request when 128 valid stages */
#घोषणा SIFCTR_RFWM_256		(7 << 13)	/*  Transfer Request when 256 valid stages */
#घोषणा SIFCTR_RFUA_MASK	GENMASK(12, 4)	/* Receive FIFO Usable Area (0x40 = full) */
#घोषणा SIFCTR_RFUA_SHIFT	4
#घोषणा SIFCTR_RFUA(i)		((i) << SIFCTR_RFUA_SHIFT)

/* SISTR */
#घोषणा SISTR_TFEMP		BIT(29) /* Transmit FIFO Empty */
#घोषणा SISTR_TDREQ		BIT(28) /* Transmit Data Transfer Request */
#घोषणा SISTR_Tखातापूर्ण		BIT(23) /* Frame Transmission End */
#घोषणा SISTR_TFSERR		BIT(21) /* Transmit Frame Synchronization Error */
#घोषणा SISTR_TFOVF		BIT(20) /* Transmit FIFO Overflow */
#घोषणा SISTR_TFUDF		BIT(19) /* Transmit FIFO Underflow */
#घोषणा SISTR_RFFUL		BIT(13) /* Receive FIFO Full */
#घोषणा SISTR_RDREQ		BIT(12) /* Receive Data Transfer Request */
#घोषणा SISTR_Rखातापूर्ण		BIT(7)  /* Frame Reception End */
#घोषणा SISTR_RFSERR		BIT(5)  /* Receive Frame Synchronization Error */
#घोषणा SISTR_RFUDF		BIT(4)  /* Receive FIFO Underflow */
#घोषणा SISTR_RFOVF		BIT(3)  /* Receive FIFO Overflow */

/* SIIER */
#घोषणा SIIER_TDMAE		BIT(31) /* Transmit Data DMA Transfer Req. Enable */
#घोषणा SIIER_TFEMPE		BIT(29) /* Transmit FIFO Empty Enable */
#घोषणा SIIER_TDREQE		BIT(28) /* Transmit Data Transfer Request Enable */
#घोषणा SIIER_Tखातापूर्णE		BIT(23) /* Frame Transmission End Enable */
#घोषणा SIIER_TFSERRE		BIT(21) /* Transmit Frame Sync Error Enable */
#घोषणा SIIER_TFOVFE		BIT(20) /* Transmit FIFO Overflow Enable */
#घोषणा SIIER_TFUDFE		BIT(19) /* Transmit FIFO Underflow Enable */
#घोषणा SIIER_RDMAE		BIT(15) /* Receive Data DMA Transfer Req. Enable */
#घोषणा SIIER_RFFULE		BIT(13) /* Receive FIFO Full Enable */
#घोषणा SIIER_RDREQE		BIT(12) /* Receive Data Transfer Request Enable */
#घोषणा SIIER_Rखातापूर्णE		BIT(7)  /* Frame Reception End Enable */
#घोषणा SIIER_RFSERRE		BIT(5)  /* Receive Frame Sync Error Enable */
#घोषणा SIIER_RFUDFE		BIT(4)  /* Receive FIFO Underflow Enable */
#घोषणा SIIER_RFOVFE		BIT(3)  /* Receive FIFO Overflow Enable */


अटल u32 sh_msiof_पढ़ो(काष्ठा sh_msiof_spi_priv *p, पूर्णांक reg_offs)
अणु
	चयन (reg_offs) अणु
	हाल SITSCR:
	हाल SIRSCR:
		वापस ioपढ़ो16(p->mapbase + reg_offs);
	शेष:
		वापस ioपढ़ो32(p->mapbase + reg_offs);
	पूर्ण
पूर्ण

अटल व्योम sh_msiof_ग_लिखो(काष्ठा sh_msiof_spi_priv *p, पूर्णांक reg_offs,
			   u32 value)
अणु
	चयन (reg_offs) अणु
	हाल SITSCR:
	हाल SIRSCR:
		ioग_लिखो16(value, p->mapbase + reg_offs);
		अवरोध;
	शेष:
		ioग_लिखो32(value, p->mapbase + reg_offs);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_msiof_modअगरy_ctr_रुको(काष्ठा sh_msiof_spi_priv *p,
				    u32 clr, u32 set)
अणु
	u32 mask = clr | set;
	u32 data;

	data = sh_msiof_पढ़ो(p, SICTR);
	data &= ~clr;
	data |= set;
	sh_msiof_ग_लिखो(p, SICTR, data);

	वापस पढ़ोl_poll_समयout_atomic(p->mapbase + SICTR, data,
					 (data & mask) == set, 1, 100);
पूर्ण

अटल irqवापस_t sh_msiof_spi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sh_msiof_spi_priv *p = data;

	/* just disable the पूर्णांकerrupt and wake up */
	sh_msiof_ग_लिखो(p, SIIER, 0);
	complete(&p->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sh_msiof_spi_reset_regs(काष्ठा sh_msiof_spi_priv *p)
अणु
	u32 mask = SICTR_TXRST | SICTR_RXRST;
	u32 data;

	data = sh_msiof_पढ़ो(p, SICTR);
	data |= mask;
	sh_msiof_ग_लिखो(p, SICTR, data);

	पढ़ोl_poll_समयout_atomic(p->mapbase + SICTR, data, !(data & mask), 1,
				  100);
पूर्ण

अटल स्थिर u32 sh_msiof_spi_भाग_array[] = अणु
	SISCR_BRDV_DIV_1, SISCR_BRDV_DIV_2, SISCR_BRDV_DIV_4,
	SISCR_BRDV_DIV_8, SISCR_BRDV_DIV_16, SISCR_BRDV_DIV_32,
पूर्ण;

अटल व्योम sh_msiof_spi_set_clk_regs(काष्ठा sh_msiof_spi_priv *p,
				      काष्ठा spi_transfer *t)
अणु
	अचिन्हित दीर्घ parent_rate = clk_get_rate(p->clk);
	अचिन्हित पूर्णांक भाग_घात = p->min_भाग_घात;
	u32 spi_hz = t->speed_hz;
	अचिन्हित दीर्घ भाग;
	u32 brps, scr;

	अगर (!spi_hz || !parent_rate) अणु
		WARN(1, "Invalid clock rate parameters %lu and %u\n",
		     parent_rate, spi_hz);
		वापस;
	पूर्ण

	भाग = DIV_ROUND_UP(parent_rate, spi_hz);
	अगर (भाग <= 1024) अणु
		/* SISCR_BRDV_DIV_1 is valid only अगर BRPS is x 1/1 or x 1/2 */
		अगर (!भाग_घात && भाग <= 32 && भाग > 2)
			भाग_घात = 1;

		अगर (भाग_घात)
			brps = (भाग + 1) >> भाग_घात;
		अन्यथा
			brps = भाग;

		क्रम (; brps > 32; भाग_घात++)
			brps = (brps + 1) >> 1;
	पूर्ण अन्यथा अणु
		/* Set transfer rate composite भागisor to 2^5 * 32 = 1024 */
		dev_err(&p->pdev->dev,
			"Requested SPI transfer rate %d is too low\n", spi_hz);
		भाग_घात = 5;
		brps = 32;
	पूर्ण

	t->effective_speed_hz = parent_rate / (brps << भाग_घात);

	scr = sh_msiof_spi_भाग_array[भाग_घात] | SISCR_BRPS(brps);
	sh_msiof_ग_लिखो(p, SITSCR, scr);
	अगर (!(p->ctlr->flags & SPI_CONTROLLER_MUST_TX))
		sh_msiof_ग_लिखो(p, SIRSCR, scr);
पूर्ण

अटल u32 sh_msiof_get_delay_bit(u32 dtdl_or_syncdl)
अणु
	/*
	 * DTDL/SYNCDL bit	: p->info->dtdl or p->info->syncdl
	 * b'000		: 0
	 * b'001		: 100
	 * b'010		: 200
	 * b'011 (SYNCDL only)	: 300
	 * b'101		: 50
	 * b'110		: 150
	 */
	अगर (dtdl_or_syncdl % 100)
		वापस dtdl_or_syncdl / 100 + 5;
	अन्यथा
		वापस dtdl_or_syncdl / 100;
पूर्ण

अटल u32 sh_msiof_spi_get_dtdl_and_syncdl(काष्ठा sh_msiof_spi_priv *p)
अणु
	u32 val;

	अगर (!p->info)
		वापस 0;

	/* check अगर DTDL and SYNCDL is allowed value */
	अगर (p->info->dtdl > 200 || p->info->syncdl > 300) अणु
		dev_warn(&p->pdev->dev, "DTDL or SYNCDL is too large\n");
		वापस 0;
	पूर्ण

	/* check अगर the sum of DTDL and SYNCDL becomes an पूर्णांकeger value  */
	अगर ((p->info->dtdl + p->info->syncdl) % 100) अणु
		dev_warn(&p->pdev->dev, "the sum of DTDL/SYNCDL is not good\n");
		वापस 0;
	पूर्ण

	val = sh_msiof_get_delay_bit(p->info->dtdl) << SIMDR1_DTDL_SHIFT;
	val |= sh_msiof_get_delay_bit(p->info->syncdl) << SIMDR1_SYNCDL_SHIFT;

	वापस val;
पूर्ण

अटल व्योम sh_msiof_spi_set_pin_regs(काष्ठा sh_msiof_spi_priv *p, u32 ss,
				      u32 cpol, u32 cpha,
				      u32 tx_hi_z, u32 lsb_first, u32 cs_high)
अणु
	u32 पंचांगp;
	पूर्णांक edge;

	/*
	 * CPOL CPHA     TSCKIZ RSCKIZ TEDG REDG
	 *    0    0         10     10    1    1
	 *    0    1         10     10    0    0
	 *    1    0         11     11    0    0
	 *    1    1         11     11    1    1
	 */
	पंचांगp = SIMDR1_SYNCMD_SPI | 1 << SIMDR1_FLD_SHIFT | SIMDR1_XXSTP;
	पंचांगp |= !cs_high << SIMDR1_SYNCAC_SHIFT;
	पंचांगp |= lsb_first << SIMDR1_BITLSB_SHIFT;
	पंचांगp |= sh_msiof_spi_get_dtdl_and_syncdl(p);
	अगर (spi_controller_is_slave(p->ctlr)) अणु
		sh_msiof_ग_लिखो(p, SITMDR1, पंचांगp | SITMDR1_PCON);
	पूर्ण अन्यथा अणु
		sh_msiof_ग_लिखो(p, SITMDR1,
			       पंचांगp | SIMDR1_TRMD | SITMDR1_PCON |
			       (ss < MAX_SS ? ss : 0) << SITMDR1_SYNCCH_SHIFT);
	पूर्ण
	अगर (p->ctlr->flags & SPI_CONTROLLER_MUST_TX) अणु
		/* These bits are reserved अगर RX needs TX */
		पंचांगp &= ~0x0000ffff;
	पूर्ण
	sh_msiof_ग_लिखो(p, SIRMDR1, पंचांगp);

	पंचांगp = 0;
	पंचांगp |= SICTR_TSCKIZ_SCK | cpol << SICTR_TSCKIZ_POL_SHIFT;
	पंचांगp |= SICTR_RSCKIZ_SCK | cpol << SICTR_RSCKIZ_POL_SHIFT;

	edge = cpol ^ !cpha;

	पंचांगp |= edge << SICTR_TEDG_SHIFT;
	पंचांगp |= edge << SICTR_REDG_SHIFT;
	पंचांगp |= tx_hi_z ? SICTR_TXDIZ_HIZ : SICTR_TXDIZ_LOW;
	sh_msiof_ग_लिखो(p, SICTR, पंचांगp);
पूर्ण

अटल व्योम sh_msiof_spi_set_mode_regs(काष्ठा sh_msiof_spi_priv *p,
				       स्थिर व्योम *tx_buf, व्योम *rx_buf,
				       u32 bits, u32 words)
अणु
	u32 dr2 = SIMDR2_BITLEN1(bits) | SIMDR2_WDLEN1(words);

	अगर (tx_buf || (p->ctlr->flags & SPI_CONTROLLER_MUST_TX))
		sh_msiof_ग_लिखो(p, SITMDR2, dr2);
	अन्यथा
		sh_msiof_ग_लिखो(p, SITMDR2, dr2 | SIMDR2_GRPMASK1);

	अगर (rx_buf)
		sh_msiof_ग_लिखो(p, SIRMDR2, dr2);
पूर्ण

अटल व्योम sh_msiof_reset_str(काष्ठा sh_msiof_spi_priv *p)
अणु
	sh_msiof_ग_लिखो(p, SISTR,
		       sh_msiof_पढ़ो(p, SISTR) & ~(SISTR_TDREQ | SISTR_RDREQ));
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_8(काष्ठा sh_msiof_spi_priv *p,
				      स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u8 *buf_8 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, buf_8[k] << fs);
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_16(काष्ठा sh_msiof_spi_priv *p,
				       स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u16 *buf_16 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, buf_16[k] << fs);
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_16u(काष्ठा sh_msiof_spi_priv *p,
					स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u16 *buf_16 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, get_unaligned(&buf_16[k]) << fs);
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_32(काष्ठा sh_msiof_spi_priv *p,
				       स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u32 *buf_32 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, buf_32[k] << fs);
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_32u(काष्ठा sh_msiof_spi_priv *p,
					स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u32 *buf_32 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, get_unaligned(&buf_32[k]) << fs);
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_s32(काष्ठा sh_msiof_spi_priv *p,
					स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u32 *buf_32 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, swab32(buf_32[k] << fs));
पूर्ण

अटल व्योम sh_msiof_spi_ग_लिखो_fअगरo_s32u(काष्ठा sh_msiof_spi_priv *p,
					 स्थिर व्योम *tx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	स्थिर u32 *buf_32 = tx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		sh_msiof_ग_लिखो(p, SITFDR, swab32(get_unaligned(&buf_32[k]) << fs));
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_8(काष्ठा sh_msiof_spi_priv *p,
				     व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u8 *buf_8 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		buf_8[k] = sh_msiof_पढ़ो(p, SIRFDR) >> fs;
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_16(काष्ठा sh_msiof_spi_priv *p,
				      व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u16 *buf_16 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		buf_16[k] = sh_msiof_पढ़ो(p, SIRFDR) >> fs;
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_16u(काष्ठा sh_msiof_spi_priv *p,
				       व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u16 *buf_16 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		put_unaligned(sh_msiof_पढ़ो(p, SIRFDR) >> fs, &buf_16[k]);
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_32(काष्ठा sh_msiof_spi_priv *p,
				      व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u32 *buf_32 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		buf_32[k] = sh_msiof_पढ़ो(p, SIRFDR) >> fs;
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_32u(काष्ठा sh_msiof_spi_priv *p,
				       व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u32 *buf_32 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		put_unaligned(sh_msiof_पढ़ो(p, SIRFDR) >> fs, &buf_32[k]);
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_s32(काष्ठा sh_msiof_spi_priv *p,
				       व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u32 *buf_32 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		buf_32[k] = swab32(sh_msiof_पढ़ो(p, SIRFDR) >> fs);
पूर्ण

अटल व्योम sh_msiof_spi_पढ़ो_fअगरo_s32u(काष्ठा sh_msiof_spi_priv *p,
				       व्योम *rx_buf, पूर्णांक words, पूर्णांक fs)
अणु
	u32 *buf_32 = rx_buf;
	पूर्णांक k;

	क्रम (k = 0; k < words; k++)
		put_unaligned(swab32(sh_msiof_पढ़ो(p, SIRFDR) >> fs), &buf_32[k]);
पूर्ण

अटल पूर्णांक sh_msiof_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा sh_msiof_spi_priv *p =
		spi_controller_get_devdata(spi->controller);
	u32 clr, set, पंचांगp;

	अगर (spi->cs_gpiod || spi_controller_is_slave(p->ctlr))
		वापस 0;

	अगर (p->native_cs_inited &&
	    (p->native_cs_high == !!(spi->mode & SPI_CS_HIGH)))
		वापस 0;

	/* Configure native chip select mode/polarity early */
	clr = SIMDR1_SYNCMD_MASK;
	set = SIMDR1_SYNCMD_SPI;
	अगर (spi->mode & SPI_CS_HIGH)
		clr |= BIT(SIMDR1_SYNCAC_SHIFT);
	अन्यथा
		set |= BIT(SIMDR1_SYNCAC_SHIFT);
	pm_runसमय_get_sync(&p->pdev->dev);
	पंचांगp = sh_msiof_पढ़ो(p, SITMDR1) & ~clr;
	sh_msiof_ग_लिखो(p, SITMDR1, पंचांगp | set | SIMDR1_TRMD | SITMDR1_PCON);
	पंचांगp = sh_msiof_पढ़ो(p, SIRMDR1) & ~clr;
	sh_msiof_ग_लिखो(p, SIRMDR1, पंचांगp | set);
	pm_runसमय_put(&p->pdev->dev);
	p->native_cs_high = spi->mode & SPI_CS_HIGH;
	p->native_cs_inited = true;
	वापस 0;
पूर्ण

अटल पूर्णांक sh_msiof_prepare_message(काष्ठा spi_controller *ctlr,
				    काष्ठा spi_message *msg)
अणु
	काष्ठा sh_msiof_spi_priv *p = spi_controller_get_devdata(ctlr);
	स्थिर काष्ठा spi_device *spi = msg->spi;
	u32 ss, cs_high;

	/* Configure pins beक्रमe निश्चितing CS */
	अगर (spi->cs_gpiod) अणु
		ss = ctlr->unused_native_cs;
		cs_high = p->native_cs_high;
	पूर्ण अन्यथा अणु
		ss = spi->chip_select;
		cs_high = !!(spi->mode & SPI_CS_HIGH);
	पूर्ण
	sh_msiof_spi_set_pin_regs(p, ss, !!(spi->mode & SPI_CPOL),
				  !!(spi->mode & SPI_CPHA),
				  !!(spi->mode & SPI_3WIRE),
				  !!(spi->mode & SPI_LSB_FIRST), cs_high);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_msiof_spi_start(काष्ठा sh_msiof_spi_priv *p, व्योम *rx_buf)
अणु
	bool slave = spi_controller_is_slave(p->ctlr);
	पूर्णांक ret = 0;

	/* setup घड़ी and rx/tx संकेतs */
	अगर (!slave)
		ret = sh_msiof_modअगरy_ctr_रुको(p, 0, SICTR_TSCKE);
	अगर (rx_buf && !ret)
		ret = sh_msiof_modअगरy_ctr_रुको(p, 0, SICTR_RXE);
	अगर (!ret)
		ret = sh_msiof_modअगरy_ctr_रुको(p, 0, SICTR_TXE);

	/* start by setting frame bit */
	अगर (!ret && !slave)
		ret = sh_msiof_modअगरy_ctr_रुको(p, 0, SICTR_TFSE);

	वापस ret;
पूर्ण

अटल पूर्णांक sh_msiof_spi_stop(काष्ठा sh_msiof_spi_priv *p, व्योम *rx_buf)
अणु
	bool slave = spi_controller_is_slave(p->ctlr);
	पूर्णांक ret = 0;

	/* shut करोwn frame, rx/tx and घड़ी संकेतs */
	अगर (!slave)
		ret = sh_msiof_modअगरy_ctr_रुको(p, SICTR_TFSE, 0);
	अगर (!ret)
		ret = sh_msiof_modअगरy_ctr_रुको(p, SICTR_TXE, 0);
	अगर (rx_buf && !ret)
		ret = sh_msiof_modअगरy_ctr_रुको(p, SICTR_RXE, 0);
	अगर (!ret && !slave)
		ret = sh_msiof_modअगरy_ctr_रुको(p, SICTR_TSCKE, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक sh_msiof_slave_पात(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा sh_msiof_spi_priv *p = spi_controller_get_devdata(ctlr);

	p->slave_पातed = true;
	complete(&p->करोne);
	complete(&p->करोne_txdma);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_msiof_रुको_क्रम_completion(काष्ठा sh_msiof_spi_priv *p,
					काष्ठा completion *x)
अणु
	अगर (spi_controller_is_slave(p->ctlr)) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(x) ||
		    p->slave_पातed) अणु
			dev_dbg(&p->pdev->dev, "interrupted\n");
			वापस -EINTR;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!रुको_क्रम_completion_समयout(x, HZ)) अणु
			dev_err(&p->pdev->dev, "timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_msiof_spi_txrx_once(काष्ठा sh_msiof_spi_priv *p,
				  व्योम (*tx_fअगरo)(काष्ठा sh_msiof_spi_priv *,
						  स्थिर व्योम *, पूर्णांक, पूर्णांक),
				  व्योम (*rx_fअगरo)(काष्ठा sh_msiof_spi_priv *,
						  व्योम *, पूर्णांक, पूर्णांक),
				  स्थिर व्योम *tx_buf, व्योम *rx_buf,
				  पूर्णांक words, पूर्णांक bits)
अणु
	पूर्णांक fअगरo_shअगरt;
	पूर्णांक ret;

	/* limit maximum word transfer to rx/tx fअगरo size */
	अगर (tx_buf)
		words = min_t(पूर्णांक, words, p->tx_fअगरo_size);
	अगर (rx_buf)
		words = min_t(पूर्णांक, words, p->rx_fअगरo_size);

	/* the fअगरo contents need shअगरting */
	fअगरo_shअगरt = 32 - bits;

	/* शेष FIFO watermarks क्रम PIO */
	sh_msiof_ग_लिखो(p, SIFCTR, 0);

	/* setup msiof transfer mode रेजिस्टरs */
	sh_msiof_spi_set_mode_regs(p, tx_buf, rx_buf, bits, words);
	sh_msiof_ग_लिखो(p, SIIER, SIIER_Tखातापूर्णE | SIIER_Rखातापूर्णE);

	/* ग_लिखो tx fअगरo */
	अगर (tx_buf)
		tx_fअगरo(p, tx_buf, words, fअगरo_shअगरt);

	reinit_completion(&p->करोne);
	p->slave_पातed = false;

	ret = sh_msiof_spi_start(p, rx_buf);
	अगर (ret) अणु
		dev_err(&p->pdev->dev, "failed to start hardware\n");
		जाओ stop_ier;
	पूर्ण

	/* रुको क्रम tx fअगरo to be emptied / rx fअगरo to be filled */
	ret = sh_msiof_रुको_क्रम_completion(p, &p->करोne);
	अगर (ret)
		जाओ stop_reset;

	/* पढ़ो rx fअगरo */
	अगर (rx_buf)
		rx_fअगरo(p, rx_buf, words, fअगरo_shअगरt);

	/* clear status bits */
	sh_msiof_reset_str(p);

	ret = sh_msiof_spi_stop(p, rx_buf);
	अगर (ret) अणु
		dev_err(&p->pdev->dev, "failed to shut down hardware\n");
		वापस ret;
	पूर्ण

	वापस words;

stop_reset:
	sh_msiof_reset_str(p);
	sh_msiof_spi_stop(p, rx_buf);
stop_ier:
	sh_msiof_ग_लिखो(p, SIIER, 0);
	वापस ret;
पूर्ण

अटल व्योम sh_msiof_dma_complete(व्योम *arg)
अणु
	complete(arg);
पूर्ण

अटल पूर्णांक sh_msiof_dma_once(काष्ठा sh_msiof_spi_priv *p, स्थिर व्योम *tx,
			     व्योम *rx, अचिन्हित पूर्णांक len)
अणु
	u32 ier_bits = 0;
	काष्ठा dma_async_tx_descriptor *desc_tx = शून्य, *desc_rx = शून्य;
	dma_cookie_t cookie;
	पूर्णांक ret;

	/* First prepare and submit the DMA request(s), as this may fail */
	अगर (rx) अणु
		ier_bits |= SIIER_RDREQE | SIIER_RDMAE;
		desc_rx = dmaengine_prep_slave_single(p->ctlr->dma_rx,
					p->rx_dma_addr, len, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc_rx)
			वापस -EAGAIN;

		desc_rx->callback = sh_msiof_dma_complete;
		desc_rx->callback_param = &p->करोne;
		cookie = dmaengine_submit(desc_rx);
		अगर (dma_submit_error(cookie))
			वापस cookie;
	पूर्ण

	अगर (tx) अणु
		ier_bits |= SIIER_TDREQE | SIIER_TDMAE;
		dma_sync_single_क्रम_device(p->ctlr->dma_tx->device->dev,
					   p->tx_dma_addr, len, DMA_TO_DEVICE);
		desc_tx = dmaengine_prep_slave_single(p->ctlr->dma_tx,
					p->tx_dma_addr, len, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc_tx) अणु
			ret = -EAGAIN;
			जाओ no_dma_tx;
		पूर्ण

		desc_tx->callback = sh_msiof_dma_complete;
		desc_tx->callback_param = &p->करोne_txdma;
		cookie = dmaengine_submit(desc_tx);
		अगर (dma_submit_error(cookie)) अणु
			ret = cookie;
			जाओ no_dma_tx;
		पूर्ण
	पूर्ण

	/* 1 stage FIFO watermarks क्रम DMA */
	sh_msiof_ग_लिखो(p, SIFCTR, SIFCTR_TFWM_1 | SIFCTR_RFWM_1);

	/* setup msiof transfer mode रेजिस्टरs (32-bit words) */
	sh_msiof_spi_set_mode_regs(p, tx, rx, 32, len / 4);

	sh_msiof_ग_लिखो(p, SIIER, ier_bits);

	reinit_completion(&p->करोne);
	अगर (tx)
		reinit_completion(&p->करोne_txdma);
	p->slave_पातed = false;

	/* Now start DMA */
	अगर (rx)
		dma_async_issue_pending(p->ctlr->dma_rx);
	अगर (tx)
		dma_async_issue_pending(p->ctlr->dma_tx);

	ret = sh_msiof_spi_start(p, rx);
	अगर (ret) अणु
		dev_err(&p->pdev->dev, "failed to start hardware\n");
		जाओ stop_dma;
	पूर्ण

	अगर (tx) अणु
		/* रुको क्रम tx DMA completion */
		ret = sh_msiof_रुको_क्रम_completion(p, &p->करोne_txdma);
		अगर (ret)
			जाओ stop_reset;
	पूर्ण

	अगर (rx) अणु
		/* रुको क्रम rx DMA completion */
		ret = sh_msiof_रुको_क्रम_completion(p, &p->करोne);
		अगर (ret)
			जाओ stop_reset;

		sh_msiof_ग_लिखो(p, SIIER, 0);
	पूर्ण अन्यथा अणु
		/* रुको क्रम tx fअगरo to be emptied */
		sh_msiof_ग_लिखो(p, SIIER, SIIER_Tखातापूर्णE);
		ret = sh_msiof_रुको_क्रम_completion(p, &p->करोne);
		अगर (ret)
			जाओ stop_reset;
	पूर्ण

	/* clear status bits */
	sh_msiof_reset_str(p);

	ret = sh_msiof_spi_stop(p, rx);
	अगर (ret) अणु
		dev_err(&p->pdev->dev, "failed to shut down hardware\n");
		वापस ret;
	पूर्ण

	अगर (rx)
		dma_sync_single_क्रम_cpu(p->ctlr->dma_rx->device->dev,
					p->rx_dma_addr, len, DMA_FROM_DEVICE);

	वापस 0;

stop_reset:
	sh_msiof_reset_str(p);
	sh_msiof_spi_stop(p, rx);
stop_dma:
	अगर (tx)
		dmaengine_terminate_all(p->ctlr->dma_tx);
no_dma_tx:
	अगर (rx)
		dmaengine_terminate_all(p->ctlr->dma_rx);
	sh_msiof_ग_लिखो(p, SIIER, 0);
	वापस ret;
पूर्ण

अटल व्योम copy_bswap32(u32 *dst, स्थिर u32 *src, अचिन्हित पूर्णांक words)
अणु
	/* src or dst can be unaligned, but not both */
	अगर ((अचिन्हित दीर्घ)src & 3) अणु
		जबतक (words--) अणु
			*dst++ = swab32(get_unaligned(src));
			src++;
		पूर्ण
	पूर्ण अन्यथा अगर ((अचिन्हित दीर्घ)dst & 3) अणु
		जबतक (words--) अणु
			put_unaligned(swab32(*src++), dst);
			dst++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (words--)
			*dst++ = swab32(*src++);
	पूर्ण
पूर्ण

अटल व्योम copy_wswap32(u32 *dst, स्थिर u32 *src, अचिन्हित पूर्णांक words)
अणु
	/* src or dst can be unaligned, but not both */
	अगर ((अचिन्हित दीर्घ)src & 3) अणु
		जबतक (words--) अणु
			*dst++ = swahw32(get_unaligned(src));
			src++;
		पूर्ण
	पूर्ण अन्यथा अगर ((अचिन्हित दीर्घ)dst & 3) अणु
		जबतक (words--) अणु
			put_unaligned(swahw32(*src++), dst);
			dst++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (words--)
			*dst++ = swahw32(*src++);
	पूर्ण
पूर्ण

अटल व्योम copy_plain32(u32 *dst, स्थिर u32 *src, अचिन्हित पूर्णांक words)
अणु
	स_नकल(dst, src, words * 4);
पूर्ण

अटल पूर्णांक sh_msiof_transfer_one(काष्ठा spi_controller *ctlr,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *t)
अणु
	काष्ठा sh_msiof_spi_priv *p = spi_controller_get_devdata(ctlr);
	व्योम (*copy32)(u32 *, स्थिर u32 *, अचिन्हित पूर्णांक);
	व्योम (*tx_fअगरo)(काष्ठा sh_msiof_spi_priv *, स्थिर व्योम *, पूर्णांक, पूर्णांक);
	व्योम (*rx_fअगरo)(काष्ठा sh_msiof_spi_priv *, व्योम *, पूर्णांक, पूर्णांक);
	स्थिर व्योम *tx_buf = t->tx_buf;
	व्योम *rx_buf = t->rx_buf;
	अचिन्हित पूर्णांक len = t->len;
	अचिन्हित पूर्णांक bits = t->bits_per_word;
	अचिन्हित पूर्णांक bytes_per_word;
	अचिन्हित पूर्णांक words;
	पूर्णांक n;
	bool swab;
	पूर्णांक ret;

	/* reset रेजिस्टरs */
	sh_msiof_spi_reset_regs(p);

	/* setup घड़ीs (घड़ी alपढ़ोy enabled in chipselect()) */
	अगर (!spi_controller_is_slave(p->ctlr))
		sh_msiof_spi_set_clk_regs(p, t);

	जबतक (ctlr->dma_tx && len > 15) अणु
		/*
		 *  DMA supports 32-bit words only, hence pack 8-bit and 16-bit
		 *  words, with byte resp. word swapping.
		 */
		अचिन्हित पूर्णांक l = 0;

		अगर (tx_buf)
			l = min(round_करोwn(len, 4), p->tx_fअगरo_size * 4);
		अगर (rx_buf)
			l = min(round_करोwn(len, 4), p->rx_fअगरo_size * 4);

		अगर (bits <= 8) अणु
			copy32 = copy_bswap32;
		पूर्ण अन्यथा अगर (bits <= 16) अणु
			copy32 = copy_wswap32;
		पूर्ण अन्यथा अणु
			copy32 = copy_plain32;
		पूर्ण

		अगर (tx_buf)
			copy32(p->tx_dma_page, tx_buf, l / 4);

		ret = sh_msiof_dma_once(p, tx_buf, rx_buf, l);
		अगर (ret == -EAGAIN) अणु
			dev_warn_once(&p->pdev->dev,
				"DMA not available, falling back to PIO\n");
			अवरोध;
		पूर्ण
		अगर (ret)
			वापस ret;

		अगर (rx_buf) अणु
			copy32(rx_buf, p->rx_dma_page, l / 4);
			rx_buf += l;
		पूर्ण
		अगर (tx_buf)
			tx_buf += l;

		len -= l;
		अगर (!len)
			वापस 0;
	पूर्ण

	अगर (bits <= 8 && len > 15) अणु
		bits = 32;
		swab = true;
	पूर्ण अन्यथा अणु
		swab = false;
	पूर्ण

	/* setup bytes per word and fअगरo पढ़ो/ग_लिखो functions */
	अगर (bits <= 8) अणु
		bytes_per_word = 1;
		tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_8;
		rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_8;
	पूर्ण अन्यथा अगर (bits <= 16) अणु
		bytes_per_word = 2;
		अगर ((अचिन्हित दीर्घ)tx_buf & 0x01)
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_16u;
		अन्यथा
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_16;

		अगर ((अचिन्हित दीर्घ)rx_buf & 0x01)
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_16u;
		अन्यथा
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_16;
	पूर्ण अन्यथा अगर (swab) अणु
		bytes_per_word = 4;
		अगर ((अचिन्हित दीर्घ)tx_buf & 0x03)
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_s32u;
		अन्यथा
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_s32;

		अगर ((अचिन्हित दीर्घ)rx_buf & 0x03)
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_s32u;
		अन्यथा
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_s32;
	पूर्ण अन्यथा अणु
		bytes_per_word = 4;
		अगर ((अचिन्हित दीर्घ)tx_buf & 0x03)
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_32u;
		अन्यथा
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_32;

		अगर ((अचिन्हित दीर्घ)rx_buf & 0x03)
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_32u;
		अन्यथा
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_32;
	पूर्ण

	/* transfer in fअगरo sized chunks */
	words = len / bytes_per_word;

	जबतक (words > 0) अणु
		n = sh_msiof_spi_txrx_once(p, tx_fअगरo, rx_fअगरo, tx_buf, rx_buf,
					   words, bits);
		अगर (n < 0)
			वापस n;

		अगर (tx_buf)
			tx_buf += n * bytes_per_word;
		अगर (rx_buf)
			rx_buf += n * bytes_per_word;
		words -= n;

		अगर (words == 0 && (len % bytes_per_word)) अणु
			words = len % bytes_per_word;
			bits = t->bits_per_word;
			bytes_per_word = 1;
			tx_fअगरo = sh_msiof_spi_ग_लिखो_fअगरo_8;
			rx_fअगरo = sh_msiof_spi_पढ़ो_fअगरo_8;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sh_msiof_chipdata sh_data = अणु
	.bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 32),
	.tx_fअगरo_size = 64,
	.rx_fअगरo_size = 64,
	.ctlr_flags = 0,
	.min_भाग_घात = 0,
पूर्ण;

अटल स्थिर काष्ठा sh_msiof_chipdata rcar_gen2_data = अणु
	.bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16) |
			      SPI_BPW_MASK(24) | SPI_BPW_MASK(32),
	.tx_fअगरo_size = 64,
	.rx_fअगरo_size = 64,
	.ctlr_flags = SPI_CONTROLLER_MUST_TX,
	.min_भाग_घात = 0,
पूर्ण;

अटल स्थिर काष्ठा sh_msiof_chipdata rcar_gen3_data = अणु
	.bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16) |
			      SPI_BPW_MASK(24) | SPI_BPW_MASK(32),
	.tx_fअगरo_size = 64,
	.rx_fअगरo_size = 64,
	.ctlr_flags = SPI_CONTROLLER_MUST_TX,
	.min_भाग_घात = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sh_msiof_match[] = अणु
	अणु .compatible = "renesas,sh-mobile-msiof", .data = &sh_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7743",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7745",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7790",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7791",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7792",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7793",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7794",   .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-msiof", .data = &rcar_gen2_data पूर्ण,
	अणु .compatible = "renesas,msiof-r8a7796",   .data = &rcar_gen3_data पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-msiof", .data = &rcar_gen3_data पूर्ण,
	अणु .compatible = "renesas,sh-msiof",        .data = &sh_data पूर्ण, /* Deprecated */
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_msiof_match);

#अगर_घोषित CONFIG_OF
अटल काष्ठा sh_msiof_spi_info *sh_msiof_spi_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा sh_msiof_spi_info *info;
	काष्ठा device_node *np = dev->of_node;
	u32 num_cs = 1;

	info = devm_kzalloc(dev, माप(काष्ठा sh_msiof_spi_info), GFP_KERNEL);
	अगर (!info)
		वापस शून्य;

	info->mode = of_property_पढ़ो_bool(np, "spi-slave") ? MSIOF_SPI_SLAVE
							    : MSIOF_SPI_MASTER;

	/* Parse the MSIOF properties */
	अगर (info->mode == MSIOF_SPI_MASTER)
		of_property_पढ़ो_u32(np, "num-cs", &num_cs);
	of_property_पढ़ो_u32(np, "renesas,tx-fifo-size",
					&info->tx_fअगरo_override);
	of_property_पढ़ो_u32(np, "renesas,rx-fifo-size",
					&info->rx_fअगरo_override);
	of_property_पढ़ो_u32(np, "renesas,dtdl", &info->dtdl);
	of_property_पढ़ो_u32(np, "renesas,syncdl", &info->syncdl);

	info->num_chipselect = num_cs;

	वापस info;
पूर्ण
#अन्यथा
अटल काष्ठा sh_msiof_spi_info *sh_msiof_spi_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dma_chan *sh_msiof_request_dma_chan(काष्ठा device *dev,
	क्रमागत dma_transfer_direction dir, अचिन्हित पूर्णांक id, dma_addr_t port_addr)
अणु
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	chan = dma_request_slave_channel_compat(mask, shdma_chan_filter,
				(व्योम *)(अचिन्हित दीर्घ)id, dev,
				dir == DMA_MEM_TO_DEV ? "tx" : "rx");
	अगर (!chan) अणु
		dev_warn(dev, "dma_request_slave_channel_compat failed\n");
		वापस शून्य;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = dir;
	अगर (dir == DMA_MEM_TO_DEV) अणु
		cfg.dst_addr = port_addr;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण अन्यथा अणु
		cfg.src_addr = port_addr;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_warn(dev, "dmaengine_slave_config failed %d\n", ret);
		dma_release_channel(chan);
		वापस शून्य;
	पूर्ण

	वापस chan;
पूर्ण

अटल पूर्णांक sh_msiof_request_dma(काष्ठा sh_msiof_spi_priv *p)
अणु
	काष्ठा platक्रमm_device *pdev = p->pdev;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sh_msiof_spi_info *info = p->info;
	अचिन्हित पूर्णांक dma_tx_id, dma_rx_id;
	स्थिर काष्ठा resource *res;
	काष्ठा spi_controller *ctlr;
	काष्ठा device *tx_dev, *rx_dev;

	अगर (dev->of_node) अणु
		/* In the OF हाल we will get the slave IDs from the DT */
		dma_tx_id = 0;
		dma_rx_id = 0;
	पूर्ण अन्यथा अगर (info && info->dma_tx_id && info->dma_rx_id) अणु
		dma_tx_id = info->dma_tx_id;
		dma_rx_id = info->dma_rx_id;
	पूर्ण अन्यथा अणु
		/* The driver assumes no error */
		वापस 0;
	पूर्ण

	/* The DMA engine uses the second रेजिस्टर set, अगर present */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	ctlr = p->ctlr;
	ctlr->dma_tx = sh_msiof_request_dma_chan(dev, DMA_MEM_TO_DEV,
						 dma_tx_id, res->start + SITFDR);
	अगर (!ctlr->dma_tx)
		वापस -ENODEV;

	ctlr->dma_rx = sh_msiof_request_dma_chan(dev, DMA_DEV_TO_MEM,
						 dma_rx_id, res->start + SIRFDR);
	अगर (!ctlr->dma_rx)
		जाओ मुक्त_tx_chan;

	p->tx_dma_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!p->tx_dma_page)
		जाओ मुक्त_rx_chan;

	p->rx_dma_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!p->rx_dma_page)
		जाओ मुक्त_tx_page;

	tx_dev = ctlr->dma_tx->device->dev;
	p->tx_dma_addr = dma_map_single(tx_dev, p->tx_dma_page, PAGE_SIZE,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(tx_dev, p->tx_dma_addr))
		जाओ मुक्त_rx_page;

	rx_dev = ctlr->dma_rx->device->dev;
	p->rx_dma_addr = dma_map_single(rx_dev, p->rx_dma_page, PAGE_SIZE,
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(rx_dev, p->rx_dma_addr))
		जाओ unmap_tx_page;

	dev_info(dev, "DMA available");
	वापस 0;

unmap_tx_page:
	dma_unmap_single(tx_dev, p->tx_dma_addr, PAGE_SIZE, DMA_TO_DEVICE);
मुक्त_rx_page:
	मुक्त_page((अचिन्हित दीर्घ)p->rx_dma_page);
मुक्त_tx_page:
	मुक्त_page((अचिन्हित दीर्घ)p->tx_dma_page);
मुक्त_rx_chan:
	dma_release_channel(ctlr->dma_rx);
मुक्त_tx_chan:
	dma_release_channel(ctlr->dma_tx);
	ctlr->dma_tx = शून्य;
	वापस -ENODEV;
पूर्ण

अटल व्योम sh_msiof_release_dma(काष्ठा sh_msiof_spi_priv *p)
अणु
	काष्ठा spi_controller *ctlr = p->ctlr;

	अगर (!ctlr->dma_tx)
		वापस;

	dma_unmap_single(ctlr->dma_rx->device->dev, p->rx_dma_addr, PAGE_SIZE,
			 DMA_FROM_DEVICE);
	dma_unmap_single(ctlr->dma_tx->device->dev, p->tx_dma_addr, PAGE_SIZE,
			 DMA_TO_DEVICE);
	मुक्त_page((अचिन्हित दीर्घ)p->rx_dma_page);
	मुक्त_page((अचिन्हित दीर्घ)p->tx_dma_page);
	dma_release_channel(ctlr->dma_rx);
	dma_release_channel(ctlr->dma_tx);
पूर्ण

अटल पूर्णांक sh_msiof_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	स्थिर काष्ठा sh_msiof_chipdata *chipdata;
	काष्ठा sh_msiof_spi_info *info;
	काष्ठा sh_msiof_spi_priv *p;
	अचिन्हित दीर्घ clksrc;
	पूर्णांक i;
	पूर्णांक ret;

	chipdata = of_device_get_match_data(&pdev->dev);
	अगर (chipdata) अणु
		info = sh_msiof_spi_parse_dt(&pdev->dev);
	पूर्ण अन्यथा अणु
		chipdata = (स्थिर व्योम *)pdev->id_entry->driver_data;
		info = dev_get_platdata(&pdev->dev);
	पूर्ण

	अगर (!info) अणु
		dev_err(&pdev->dev, "failed to obtain device info\n");
		वापस -ENXIO;
	पूर्ण

	अगर (info->mode == MSIOF_SPI_SLAVE)
		ctlr = spi_alloc_slave(&pdev->dev,
				       माप(काष्ठा sh_msiof_spi_priv));
	अन्यथा
		ctlr = spi_alloc_master(&pdev->dev,
					माप(काष्ठा sh_msiof_spi_priv));
	अगर (ctlr == शून्य)
		वापस -ENOMEM;

	p = spi_controller_get_devdata(ctlr);

	platक्रमm_set_drvdata(pdev, p);
	p->ctlr = ctlr;
	p->info = info;
	p->min_भाग_घात = chipdata->min_भाग_घात;

	init_completion(&p->करोne);
	init_completion(&p->करोne_txdma);

	p->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(p->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = PTR_ERR(p->clk);
		जाओ err1;
	पूर्ण

	i = platक्रमm_get_irq(pdev, 0);
	अगर (i < 0) अणु
		ret = i;
		जाओ err1;
	पूर्ण

	p->mapbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->mapbase)) अणु
		ret = PTR_ERR(p->mapbase);
		जाओ err1;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, i, sh_msiof_spi_irq, 0,
			       dev_name(&pdev->dev), p);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to request irq\n");
		जाओ err1;
	पूर्ण

	p->pdev = pdev;
	pm_runसमय_enable(&pdev->dev);

	/* Platक्रमm data may override FIFO sizes */
	p->tx_fअगरo_size = chipdata->tx_fअगरo_size;
	p->rx_fअगरo_size = chipdata->rx_fअगरo_size;
	अगर (p->info->tx_fअगरo_override)
		p->tx_fअगरo_size = p->info->tx_fअगरo_override;
	अगर (p->info->rx_fअगरo_override)
		p->rx_fअगरo_size = p->info->rx_fअगरo_override;

	/* init controller code */
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	ctlr->mode_bits |= SPI_LSB_FIRST | SPI_3WIRE;
	clksrc = clk_get_rate(p->clk);
	ctlr->min_speed_hz = DIV_ROUND_UP(clksrc, 1024);
	ctlr->max_speed_hz = DIV_ROUND_UP(clksrc, 1 << p->min_भाग_घात);
	ctlr->flags = chipdata->ctlr_flags;
	ctlr->bus_num = pdev->id;
	ctlr->num_chipselect = p->info->num_chipselect;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->setup = sh_msiof_spi_setup;
	ctlr->prepare_message = sh_msiof_prepare_message;
	ctlr->slave_पात = sh_msiof_slave_पात;
	ctlr->bits_per_word_mask = chipdata->bits_per_word_mask;
	ctlr->स्वतः_runसमय_pm = true;
	ctlr->transfer_one = sh_msiof_transfer_one;
	ctlr->use_gpio_descriptors = true;
	ctlr->max_native_cs = MAX_SS;

	ret = sh_msiof_request_dma(p);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "DMA not available, using PIO\n");

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "devm_spi_register_controller error.\n");
		जाओ err2;
	पूर्ण

	वापस 0;

 err2:
	sh_msiof_release_dma(p);
	pm_runसमय_disable(&pdev->dev);
 err1:
	spi_controller_put(ctlr);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_msiof_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_msiof_spi_priv *p = platक्रमm_get_drvdata(pdev);

	sh_msiof_release_dma(p);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id spi_driver_ids[] = अणु
	अणु "spi_sh_msiof",	(kernel_uदीर्घ_t)&sh_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, spi_driver_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_msiof_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_msiof_spi_priv *p = dev_get_drvdata(dev);

	वापस spi_controller_suspend(p->ctlr);
पूर्ण

अटल पूर्णांक sh_msiof_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा sh_msiof_spi_priv *p = dev_get_drvdata(dev);

	वापस spi_controller_resume(p->ctlr);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sh_msiof_spi_pm_ops, sh_msiof_spi_suspend,
			 sh_msiof_spi_resume);
#घोषणा DEV_PM_OPS	(&sh_msiof_spi_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver sh_msiof_spi_drv = अणु
	.probe		= sh_msiof_spi_probe,
	.हटाओ		= sh_msiof_spi_हटाओ,
	.id_table	= spi_driver_ids,
	.driver		= अणु
		.name		= "spi_sh_msiof",
		.pm		= DEV_PM_OPS,
		.of_match_table = of_match_ptr(sh_msiof_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sh_msiof_spi_drv);

MODULE_DESCRIPTION("SuperH MSIOF SPI Controller Interface Driver");
MODULE_AUTHOR("Magnus Damm");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:spi_sh_msiof");
