<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH RSPI driver
 *
 * Copyright (C) 2012, 2013  Renesas Solutions Corp.
 * Copyright (C) 2014 Glider bvba
 *
 * Based on spi-sh.c:
 * Copyright (C) 2011 Renesas Solutions Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_dma.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/rspi.h>
#समावेश <linux/spinlock.h>

#घोषणा RSPI_SPCR		0x00	/* Control Register */
#घोषणा RSPI_SSLP		0x01	/* Slave Select Polarity Register */
#घोषणा RSPI_SPPCR		0x02	/* Pin Control Register */
#घोषणा RSPI_SPSR		0x03	/* Status Register */
#घोषणा RSPI_SPDR		0x04	/* Data Register */
#घोषणा RSPI_SPSCR		0x08	/* Sequence Control Register */
#घोषणा RSPI_SPSSR		0x09	/* Sequence Status Register */
#घोषणा RSPI_SPBR		0x0a	/* Bit Rate Register */
#घोषणा RSPI_SPDCR		0x0b	/* Data Control Register */
#घोषणा RSPI_SPCKD		0x0c	/* Clock Delay Register */
#घोषणा RSPI_SSLND		0x0d	/* Slave Select Negation Delay Register */
#घोषणा RSPI_SPND		0x0e	/* Next-Access Delay Register */
#घोषणा RSPI_SPCR2		0x0f	/* Control Register 2 (SH only) */
#घोषणा RSPI_SPCMD0		0x10	/* Command Register 0 */
#घोषणा RSPI_SPCMD1		0x12	/* Command Register 1 */
#घोषणा RSPI_SPCMD2		0x14	/* Command Register 2 */
#घोषणा RSPI_SPCMD3		0x16	/* Command Register 3 */
#घोषणा RSPI_SPCMD4		0x18	/* Command Register 4 */
#घोषणा RSPI_SPCMD5		0x1a	/* Command Register 5 */
#घोषणा RSPI_SPCMD6		0x1c	/* Command Register 6 */
#घोषणा RSPI_SPCMD7		0x1e	/* Command Register 7 */
#घोषणा RSPI_SPCMD(i)		(RSPI_SPCMD0 + (i) * 2)
#घोषणा RSPI_NUM_SPCMD		8
#घोषणा RSPI_RZ_NUM_SPCMD	4
#घोषणा QSPI_NUM_SPCMD		4

/* RSPI on RZ only */
#घोषणा RSPI_SPBFCR		0x20	/* Buffer Control Register */
#घोषणा RSPI_SPBFDR		0x22	/* Buffer Data Count Setting Register */

/* QSPI only */
#घोषणा QSPI_SPBFCR		0x18	/* Buffer Control Register */
#घोषणा QSPI_SPBDCR		0x1a	/* Buffer Data Count Register */
#घोषणा QSPI_SPBMUL0		0x1c	/* Transfer Data Length Multiplier Setting Register 0 */
#घोषणा QSPI_SPBMUL1		0x20	/* Transfer Data Length Multiplier Setting Register 1 */
#घोषणा QSPI_SPBMUL2		0x24	/* Transfer Data Length Multiplier Setting Register 2 */
#घोषणा QSPI_SPBMUL3		0x28	/* Transfer Data Length Multiplier Setting Register 3 */
#घोषणा QSPI_SPBMUL(i)		(QSPI_SPBMUL0 + (i) * 4)

/* SPCR - Control Register */
#घोषणा SPCR_SPRIE		0x80	/* Receive Interrupt Enable */
#घोषणा SPCR_SPE		0x40	/* Function Enable */
#घोषणा SPCR_SPTIE		0x20	/* Transmit Interrupt Enable */
#घोषणा SPCR_SPEIE		0x10	/* Error Interrupt Enable */
#घोषणा SPCR_MSTR		0x08	/* Master/Slave Mode Select */
#घोषणा SPCR_MODFEN		0x04	/* Mode Fault Error Detection Enable */
/* RSPI on SH only */
#घोषणा SPCR_TXMD		0x02	/* TX Only Mode (vs. Full Duplex) */
#घोषणा SPCR_SPMS		0x01	/* 3-wire Mode (vs. 4-wire) */
/* QSPI on R-Car Gen2 only */
#घोषणा SPCR_WSWAP		0x02	/* Word Swap of पढ़ो-data क्रम DMAC */
#घोषणा SPCR_BSWAP		0x01	/* Byte Swap of पढ़ो-data क्रम DMAC */

/* SSLP - Slave Select Polarity Register */
#घोषणा SSLP_SSLP(i)		BIT(i)	/* SSLi Signal Polarity Setting */

/* SPPCR - Pin Control Register */
#घोषणा SPPCR_MOIFE		0x20	/* MOSI Idle Value Fixing Enable */
#घोषणा SPPCR_MOIFV		0x10	/* MOSI Idle Fixed Value */
#घोषणा SPPCR_SPOM		0x04
#घोषणा SPPCR_SPLP2		0x02	/* Loopback Mode 2 (non-inverting) */
#घोषणा SPPCR_SPLP		0x01	/* Loopback Mode (inverting) */

#घोषणा SPPCR_IO3FV		0x04	/* Single-/Dual-SPI Mode IO3 Output Fixed Value */
#घोषणा SPPCR_IO2FV		0x04	/* Single-/Dual-SPI Mode IO2 Output Fixed Value */

/* SPSR - Status Register */
#घोषणा SPSR_SPRF		0x80	/* Receive Buffer Full Flag */
#घोषणा SPSR_TEND		0x40	/* Transmit End */
#घोषणा SPSR_SPTEF		0x20	/* Transmit Buffer Empty Flag */
#घोषणा SPSR_PERF		0x08	/* Parity Error Flag */
#घोषणा SPSR_MODF		0x04	/* Mode Fault Error Flag */
#घोषणा SPSR_IDLNF		0x02	/* RSPI Idle Flag */
#घोषणा SPSR_OVRF		0x01	/* Overrun Error Flag (RSPI only) */

/* SPSCR - Sequence Control Register */
#घोषणा SPSCR_SPSLN_MASK	0x07	/* Sequence Length Specअगरication */

/* SPSSR - Sequence Status Register */
#घोषणा SPSSR_SPECM_MASK	0x70	/* Command Error Mask */
#घोषणा SPSSR_SPCP_MASK		0x07	/* Command Poपूर्णांकer Mask */

/* SPDCR - Data Control Register */
#घोषणा SPDCR_TXDMY		0x80	/* Dummy Data Transmission Enable */
#घोषणा SPDCR_SPLW1		0x40	/* Access Width Specअगरication (RZ) */
#घोषणा SPDCR_SPLW0		0x20	/* Access Width Specअगरication (RZ) */
#घोषणा SPDCR_SPLLWORD		(SPDCR_SPLW1 | SPDCR_SPLW0)
#घोषणा SPDCR_SPLWORD		SPDCR_SPLW1
#घोषणा SPDCR_SPLBYTE		SPDCR_SPLW0
#घोषणा SPDCR_SPLW		0x20	/* Access Width Specअगरication (SH) */
#घोषणा SPDCR_SPRDTD		0x10	/* Receive Transmit Data Select (SH) */
#घोषणा SPDCR_SLSEL1		0x08
#घोषणा SPDCR_SLSEL0		0x04
#घोषणा SPDCR_SLSEL_MASK	0x0c	/* SSL1 Output Select (SH) */
#घोषणा SPDCR_SPFC1		0x02
#घोषणा SPDCR_SPFC0		0x01
#घोषणा SPDCR_SPFC_MASK		0x03	/* Frame Count Setting (1-4) (SH) */

/* SPCKD - Clock Delay Register */
#घोषणा SPCKD_SCKDL_MASK	0x07	/* Clock Delay Setting (1-8) */

/* SSLND - Slave Select Negation Delay Register */
#घोषणा SSLND_SLNDL_MASK	0x07	/* SSL Negation Delay Setting (1-8) */

/* SPND - Next-Access Delay Register */
#घोषणा SPND_SPNDL_MASK		0x07	/* Next-Access Delay Setting (1-8) */

/* SPCR2 - Control Register 2 */
#घोषणा SPCR2_PTE		0x08	/* Parity Self-Test Enable */
#घोषणा SPCR2_SPIE		0x04	/* Idle Interrupt Enable */
#घोषणा SPCR2_SPOE		0x02	/* Odd Parity Enable (vs. Even) */
#घोषणा SPCR2_SPPE		0x01	/* Parity Enable */

/* SPCMDn - Command Registers */
#घोषणा SPCMD_SCKDEN		0x8000	/* Clock Delay Setting Enable */
#घोषणा SPCMD_SLNDEN		0x4000	/* SSL Negation Delay Setting Enable */
#घोषणा SPCMD_SPNDEN		0x2000	/* Next-Access Delay Enable */
#घोषणा SPCMD_LSBF		0x1000	/* LSB First */
#घोषणा SPCMD_SPB_MASK		0x0f00	/* Data Length Setting */
#घोषणा SPCMD_SPB_8_TO_16(bit)	(((bit - 1) << 8) & SPCMD_SPB_MASK)
#घोषणा SPCMD_SPB_8BIT		0x0000	/* QSPI only */
#घोषणा SPCMD_SPB_16BIT		0x0100
#घोषणा SPCMD_SPB_20BIT		0x0000
#घोषणा SPCMD_SPB_24BIT		0x0100
#घोषणा SPCMD_SPB_32BIT		0x0200
#घोषणा SPCMD_SSLKP		0x0080	/* SSL Signal Level Keeping */
#घोषणा SPCMD_SPIMOD_MASK	0x0060	/* SPI Operating Mode (QSPI only) */
#घोषणा SPCMD_SPIMOD1		0x0040
#घोषणा SPCMD_SPIMOD0		0x0020
#घोषणा SPCMD_SPIMOD_SINGLE	0
#घोषणा SPCMD_SPIMOD_DUAL	SPCMD_SPIMOD0
#घोषणा SPCMD_SPIMOD_QUAD	SPCMD_SPIMOD1
#घोषणा SPCMD_SPRW		0x0010	/* SPI Read/Write Access (Dual/Quad) */
#घोषणा SPCMD_SSLA(i)		((i) << 4)	/* SSL Assert Signal Setting */
#घोषणा SPCMD_BRDV_MASK		0x000c	/* Bit Rate Division Setting */
#घोषणा SPCMD_BRDV(brdv)	((brdv) << 2)
#घोषणा SPCMD_CPOL		0x0002	/* Clock Polarity Setting */
#घोषणा SPCMD_CPHA		0x0001	/* Clock Phase Setting */

/* SPBFCR - Buffer Control Register */
#घोषणा SPBFCR_TXRST		0x80	/* Transmit Buffer Data Reset */
#घोषणा SPBFCR_RXRST		0x40	/* Receive Buffer Data Reset */
#घोषणा SPBFCR_TXTRG_MASK	0x30	/* Transmit Buffer Data Triggering Number */
#घोषणा SPBFCR_RXTRG_MASK	0x07	/* Receive Buffer Data Triggering Number */
/* QSPI on R-Car Gen2 */
#घोषणा SPBFCR_TXTRG_1B		0x00	/* 31 bytes (1 byte available) */
#घोषणा SPBFCR_TXTRG_32B	0x30	/* 0 byte (32 bytes available) */
#घोषणा SPBFCR_RXTRG_1B		0x00	/* 1 byte (31 bytes available) */
#घोषणा SPBFCR_RXTRG_32B	0x07	/* 32 bytes (0 byte available) */

#घोषणा QSPI_BUFFER_SIZE        32u

काष्ठा rspi_data अणु
	व्योम __iomem *addr;
	u32 speed_hz;
	काष्ठा spi_controller *ctlr;
	काष्ठा platक्रमm_device *pdev;
	रुको_queue_head_t रुको;
	spinlock_t lock;		/* Protects RMW-access to RSPI_SSLP */
	काष्ठा clk *clk;
	u16 spcmd;
	u8 spsr;
	u8 sppcr;
	पूर्णांक rx_irq, tx_irq;
	स्थिर काष्ठा spi_ops *ops;

	अचिन्हित dma_callbacked:1;
	अचिन्हित byte_access:1;
पूर्ण;

अटल व्योम rspi_ग_लिखो8(स्थिर काष्ठा rspi_data *rspi, u8 data, u16 offset)
अणु
	ioग_लिखो8(data, rspi->addr + offset);
पूर्ण

अटल व्योम rspi_ग_लिखो16(स्थिर काष्ठा rspi_data *rspi, u16 data, u16 offset)
अणु
	ioग_लिखो16(data, rspi->addr + offset);
पूर्ण

अटल व्योम rspi_ग_लिखो32(स्थिर काष्ठा rspi_data *rspi, u32 data, u16 offset)
अणु
	ioग_लिखो32(data, rspi->addr + offset);
पूर्ण

अटल u8 rspi_पढ़ो8(स्थिर काष्ठा rspi_data *rspi, u16 offset)
अणु
	वापस ioपढ़ो8(rspi->addr + offset);
पूर्ण

अटल u16 rspi_पढ़ो16(स्थिर काष्ठा rspi_data *rspi, u16 offset)
अणु
	वापस ioपढ़ो16(rspi->addr + offset);
पूर्ण

अटल व्योम rspi_ग_लिखो_data(स्थिर काष्ठा rspi_data *rspi, u16 data)
अणु
	अगर (rspi->byte_access)
		rspi_ग_लिखो8(rspi, data, RSPI_SPDR);
	अन्यथा /* 16 bit */
		rspi_ग_लिखो16(rspi, data, RSPI_SPDR);
पूर्ण

अटल u16 rspi_पढ़ो_data(स्थिर काष्ठा rspi_data *rspi)
अणु
	अगर (rspi->byte_access)
		वापस rspi_पढ़ो8(rspi, RSPI_SPDR);
	अन्यथा /* 16 bit */
		वापस rspi_पढ़ो16(rspi, RSPI_SPDR);
पूर्ण

/* optional functions */
काष्ठा spi_ops अणु
	पूर्णांक (*set_config_रेजिस्टर)(काष्ठा rspi_data *rspi, पूर्णांक access_size);
	पूर्णांक (*transfer_one)(काष्ठा spi_controller *ctlr,
			    काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer);
	u16 extra_mode_bits;
	u16 min_भाग;
	u16 max_भाग;
	u16 flags;
	u16 fअगरo_size;
	u8 num_hw_ss;
पूर्ण;

अटल व्योम rspi_set_rate(काष्ठा rspi_data *rspi)
अणु
	अचिन्हित दीर्घ clksrc;
	पूर्णांक brdv = 0, spbr;

	clksrc = clk_get_rate(rspi->clk);
	spbr = DIV_ROUND_UP(clksrc, 2 * rspi->speed_hz) - 1;
	जबतक (spbr > 255 && brdv < 3) अणु
		brdv++;
		spbr = DIV_ROUND_UP(spbr + 1, 2) - 1;
	पूर्ण

	rspi_ग_लिखो8(rspi, clamp(spbr, 0, 255), RSPI_SPBR);
	rspi->spcmd |= SPCMD_BRDV(brdv);
	rspi->speed_hz = DIV_ROUND_UP(clksrc, (2U << brdv) * (spbr + 1));
पूर्ण

/*
 * functions क्रम RSPI on legacy SH
 */
अटल पूर्णांक rspi_set_config_रेजिस्टर(काष्ठा rspi_data *rspi, पूर्णांक access_size)
अणु
	/* Sets output mode, MOSI संकेत, and (optionally) loopback */
	rspi_ग_लिखो8(rspi, rspi->sppcr, RSPI_SPPCR);

	/* Sets transfer bit rate */
	rspi_set_rate(rspi);

	/* Disable dummy transmission, set 16-bit word access, 1 frame */
	rspi_ग_लिखो8(rspi, 0, RSPI_SPDCR);
	rspi->byte_access = 0;

	/* Sets RSPCK, SSL, next-access delay value */
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPCKD);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SSLND);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPND);

	/* Sets parity, पूर्णांकerrupt mask */
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPCR2);

	/* Resets sequencer */
	rspi_ग_लिखो8(rspi, 0, RSPI_SPSCR);
	rspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	rspi_ग_लिखो16(rspi, rspi->spcmd, RSPI_SPCMD0);

	/* Sets RSPI mode */
	rspi_ग_लिखो8(rspi, SPCR_MSTR, RSPI_SPCR);

	वापस 0;
पूर्ण

/*
 * functions क्रम RSPI on RZ
 */
अटल पूर्णांक rspi_rz_set_config_रेजिस्टर(काष्ठा rspi_data *rspi, पूर्णांक access_size)
अणु
	/* Sets output mode, MOSI संकेत, and (optionally) loopback */
	rspi_ग_लिखो8(rspi, rspi->sppcr, RSPI_SPPCR);

	/* Sets transfer bit rate */
	rspi_set_rate(rspi);

	/* Disable dummy transmission, set byte access */
	rspi_ग_लिखो8(rspi, SPDCR_SPLBYTE, RSPI_SPDCR);
	rspi->byte_access = 1;

	/* Sets RSPCK, SSL, next-access delay value */
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPCKD);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SSLND);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPND);

	/* Resets sequencer */
	rspi_ग_लिखो8(rspi, 0, RSPI_SPSCR);
	rspi->spcmd |= SPCMD_SPB_8_TO_16(access_size);
	rspi_ग_लिखो16(rspi, rspi->spcmd, RSPI_SPCMD0);

	/* Sets RSPI mode */
	rspi_ग_लिखो8(rspi, SPCR_MSTR, RSPI_SPCR);

	वापस 0;
पूर्ण

/*
 * functions क्रम QSPI
 */
अटल पूर्णांक qspi_set_config_रेजिस्टर(काष्ठा rspi_data *rspi, पूर्णांक access_size)
अणु
	अचिन्हित दीर्घ clksrc;
	पूर्णांक brdv = 0, spbr;

	/* Sets output mode, MOSI संकेत, and (optionally) loopback */
	rspi_ग_लिखो8(rspi, rspi->sppcr, RSPI_SPPCR);

	/* Sets transfer bit rate */
	clksrc = clk_get_rate(rspi->clk);
	अगर (rspi->speed_hz >= clksrc) अणु
		spbr = 0;
		rspi->speed_hz = clksrc;
	पूर्ण अन्यथा अणु
		spbr = DIV_ROUND_UP(clksrc, 2 * rspi->speed_hz);
		जबतक (spbr > 255 && brdv < 3) अणु
			brdv++;
			spbr = DIV_ROUND_UP(spbr, 2);
		पूर्ण
		spbr = clamp(spbr, 0, 255);
		rspi->speed_hz = DIV_ROUND_UP(clksrc, (2U << brdv) * spbr);
	पूर्ण
	rspi_ग_लिखो8(rspi, spbr, RSPI_SPBR);
	rspi->spcmd |= SPCMD_BRDV(brdv);

	/* Disable dummy transmission, set byte access */
	rspi_ग_लिखो8(rspi, 0, RSPI_SPDCR);
	rspi->byte_access = 1;

	/* Sets RSPCK, SSL, next-access delay value */
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPCKD);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SSLND);
	rspi_ग_लिखो8(rspi, 0x00, RSPI_SPND);

	/* Data Length Setting */
	अगर (access_size == 8)
		rspi->spcmd |= SPCMD_SPB_8BIT;
	अन्यथा अगर (access_size == 16)
		rspi->spcmd |= SPCMD_SPB_16BIT;
	अन्यथा
		rspi->spcmd |= SPCMD_SPB_32BIT;

	rspi->spcmd |= SPCMD_SCKDEN | SPCMD_SLNDEN | SPCMD_SPNDEN;

	/* Resets transfer data length */
	rspi_ग_लिखो32(rspi, 0, QSPI_SPBMUL0);

	/* Resets transmit and receive buffer */
	rspi_ग_लिखो8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, QSPI_SPBFCR);
	/* Sets buffer to allow normal operation */
	rspi_ग_लिखो8(rspi, 0x00, QSPI_SPBFCR);

	/* Resets sequencer */
	rspi_ग_लिखो8(rspi, 0, RSPI_SPSCR);
	rspi_ग_लिखो16(rspi, rspi->spcmd, RSPI_SPCMD0);

	/* Sets RSPI mode */
	rspi_ग_लिखो8(rspi, SPCR_MSTR, RSPI_SPCR);

	वापस 0;
पूर्ण

अटल व्योम qspi_update(स्थिर काष्ठा rspi_data *rspi, u8 mask, u8 val, u8 reg)
अणु
	u8 data;

	data = rspi_पढ़ो8(rspi, reg);
	data &= ~mask;
	data |= (val & mask);
	rspi_ग_लिखो8(rspi, data, reg);
पूर्ण

अटल अचिन्हित पूर्णांक qspi_set_send_trigger(काष्ठा rspi_data *rspi,
					  अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक n;

	n = min(len, QSPI_BUFFER_SIZE);

	अगर (len >= QSPI_BUFFER_SIZE) अणु
		/* sets triggering number to 32 bytes */
		qspi_update(rspi, SPBFCR_TXTRG_MASK,
			     SPBFCR_TXTRG_32B, QSPI_SPBFCR);
	पूर्ण अन्यथा अणु
		/* sets triggering number to 1 byte */
		qspi_update(rspi, SPBFCR_TXTRG_MASK,
			     SPBFCR_TXTRG_1B, QSPI_SPBFCR);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक qspi_set_receive_trigger(काष्ठा rspi_data *rspi, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक n;

	n = min(len, QSPI_BUFFER_SIZE);

	अगर (len >= QSPI_BUFFER_SIZE) अणु
		/* sets triggering number to 32 bytes */
		qspi_update(rspi, SPBFCR_RXTRG_MASK,
			     SPBFCR_RXTRG_32B, QSPI_SPBFCR);
	पूर्ण अन्यथा अणु
		/* sets triggering number to 1 byte */
		qspi_update(rspi, SPBFCR_RXTRG_MASK,
			     SPBFCR_RXTRG_1B, QSPI_SPBFCR);
	पूर्ण
	वापस n;
पूर्ण

अटल व्योम rspi_enable_irq(स्थिर काष्ठा rspi_data *rspi, u8 enable)
अणु
	rspi_ग_लिखो8(rspi, rspi_पढ़ो8(rspi, RSPI_SPCR) | enable, RSPI_SPCR);
पूर्ण

अटल व्योम rspi_disable_irq(स्थिर काष्ठा rspi_data *rspi, u8 disable)
अणु
	rspi_ग_लिखो8(rspi, rspi_पढ़ो8(rspi, RSPI_SPCR) & ~disable, RSPI_SPCR);
पूर्ण

अटल पूर्णांक rspi_रुको_क्रम_पूर्णांकerrupt(काष्ठा rspi_data *rspi, u8 रुको_mask,
				   u8 enable_bit)
अणु
	पूर्णांक ret;

	rspi->spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (rspi->spsr & रुको_mask)
		वापस 0;

	rspi_enable_irq(rspi, enable_bit);
	ret = रुको_event_समयout(rspi->रुको, rspi->spsr & रुको_mask, HZ);
	अगर (ret == 0 && !(rspi->spsr & रुको_mask))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rspi_रुको_क्रम_tx_empty(काष्ठा rspi_data *rspi)
अणु
	वापस rspi_रुको_क्रम_पूर्णांकerrupt(rspi, SPSR_SPTEF, SPCR_SPTIE);
पूर्ण

अटल अंतरभूत पूर्णांक rspi_रुको_क्रम_rx_full(काष्ठा rspi_data *rspi)
अणु
	वापस rspi_रुको_क्रम_पूर्णांकerrupt(rspi, SPSR_SPRF, SPCR_SPRIE);
पूर्ण

अटल पूर्णांक rspi_data_out(काष्ठा rspi_data *rspi, u8 data)
अणु
	पूर्णांक error = rspi_रुको_क्रम_tx_empty(rspi);
	अगर (error < 0) अणु
		dev_err(&rspi->ctlr->dev, "transmit timeout\n");
		वापस error;
	पूर्ण
	rspi_ग_लिखो_data(rspi, data);
	वापस 0;
पूर्ण

अटल पूर्णांक rspi_data_in(काष्ठा rspi_data *rspi)
अणु
	पूर्णांक error;
	u8 data;

	error = rspi_रुको_क्रम_rx_full(rspi);
	अगर (error < 0) अणु
		dev_err(&rspi->ctlr->dev, "receive timeout\n");
		वापस error;
	पूर्ण
	data = rspi_पढ़ो_data(rspi);
	वापस data;
पूर्ण

अटल पूर्णांक rspi_pio_transfer(काष्ठा rspi_data *rspi, स्थिर u8 *tx, u8 *rx,
			     अचिन्हित पूर्णांक n)
अणु
	जबतक (n-- > 0) अणु
		अगर (tx) अणु
			पूर्णांक ret = rspi_data_out(rspi, *tx++);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अगर (rx) अणु
			पूर्णांक ret = rspi_data_in(rspi);
			अगर (ret < 0)
				वापस ret;
			*rx++ = ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rspi_dma_complete(व्योम *arg)
अणु
	काष्ठा rspi_data *rspi = arg;

	rspi->dma_callbacked = 1;
	wake_up_पूर्णांकerruptible(&rspi->रुको);
पूर्ण

अटल पूर्णांक rspi_dma_transfer(काष्ठा rspi_data *rspi, काष्ठा sg_table *tx,
			     काष्ठा sg_table *rx)
अणु
	काष्ठा dma_async_tx_descriptor *desc_tx = शून्य, *desc_rx = शून्य;
	u8 irq_mask = 0;
	अचिन्हित पूर्णांक other_irq = 0;
	dma_cookie_t cookie;
	पूर्णांक ret;

	/* First prepare and submit the DMA request(s), as this may fail */
	अगर (rx) अणु
		desc_rx = dmaengine_prep_slave_sg(rspi->ctlr->dma_rx, rx->sgl,
					rx->nents, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc_rx) अणु
			ret = -EAGAIN;
			जाओ no_dma_rx;
		पूर्ण

		desc_rx->callback = rspi_dma_complete;
		desc_rx->callback_param = rspi;
		cookie = dmaengine_submit(desc_rx);
		अगर (dma_submit_error(cookie)) अणु
			ret = cookie;
			जाओ no_dma_rx;
		पूर्ण

		irq_mask |= SPCR_SPRIE;
	पूर्ण

	अगर (tx) अणु
		desc_tx = dmaengine_prep_slave_sg(rspi->ctlr->dma_tx, tx->sgl,
					tx->nents, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc_tx) अणु
			ret = -EAGAIN;
			जाओ no_dma_tx;
		पूर्ण

		अगर (rx) अणु
			/* No callback */
			desc_tx->callback = शून्य;
		पूर्ण अन्यथा अणु
			desc_tx->callback = rspi_dma_complete;
			desc_tx->callback_param = rspi;
		पूर्ण
		cookie = dmaengine_submit(desc_tx);
		अगर (dma_submit_error(cookie)) अणु
			ret = cookie;
			जाओ no_dma_tx;
		पूर्ण

		irq_mask |= SPCR_SPTIE;
	पूर्ण

	/*
	 * DMAC needs SPxIE, but अगर SPxIE is set, the IRQ routine will be
	 * called. So, this driver disables the IRQ जबतक DMA transfer.
	 */
	अगर (tx)
		disable_irq(other_irq = rspi->tx_irq);
	अगर (rx && rspi->rx_irq != other_irq)
		disable_irq(rspi->rx_irq);

	rspi_enable_irq(rspi, irq_mask);
	rspi->dma_callbacked = 0;

	/* Now start DMA */
	अगर (rx)
		dma_async_issue_pending(rspi->ctlr->dma_rx);
	अगर (tx)
		dma_async_issue_pending(rspi->ctlr->dma_tx);

	ret = रुको_event_पूर्णांकerruptible_समयout(rspi->रुको,
					       rspi->dma_callbacked, HZ);
	अगर (ret > 0 && rspi->dma_callbacked) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		अगर (!ret) अणु
			dev_err(&rspi->ctlr->dev, "DMA timeout\n");
			ret = -ETIMEDOUT;
		पूर्ण
		अगर (tx)
			dmaengine_terminate_all(rspi->ctlr->dma_tx);
		अगर (rx)
			dmaengine_terminate_all(rspi->ctlr->dma_rx);
	पूर्ण

	rspi_disable_irq(rspi, irq_mask);

	अगर (tx)
		enable_irq(rspi->tx_irq);
	अगर (rx && rspi->rx_irq != other_irq)
		enable_irq(rspi->rx_irq);

	वापस ret;

no_dma_tx:
	अगर (rx)
		dmaengine_terminate_all(rspi->ctlr->dma_rx);
no_dma_rx:
	अगर (ret == -EAGAIN) अणु
		dev_warn_once(&rspi->ctlr->dev,
			      "DMA not available, falling back to PIO\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rspi_receive_init(स्थिर काष्ठा rspi_data *rspi)
अणु
	u8 spsr;

	spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (spsr & SPSR_SPRF)
		rspi_पढ़ो_data(rspi);	/* dummy पढ़ो */
	अगर (spsr & SPSR_OVRF)
		rspi_ग_लिखो8(rspi, rspi_पढ़ो8(rspi, RSPI_SPSR) & ~SPSR_OVRF,
			    RSPI_SPSR);
पूर्ण

अटल व्योम rspi_rz_receive_init(स्थिर काष्ठा rspi_data *rspi)
अणु
	rspi_receive_init(rspi);
	rspi_ग_लिखो8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, RSPI_SPBFCR);
	rspi_ग_लिखो8(rspi, 0, RSPI_SPBFCR);
पूर्ण

अटल व्योम qspi_receive_init(स्थिर काष्ठा rspi_data *rspi)
अणु
	u8 spsr;

	spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (spsr & SPSR_SPRF)
		rspi_पढ़ो_data(rspi);   /* dummy पढ़ो */
	rspi_ग_लिखो8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, QSPI_SPBFCR);
	rspi_ग_लिखो8(rspi, 0, QSPI_SPBFCR);
पूर्ण

अटल bool __rspi_can_dma(स्थिर काष्ठा rspi_data *rspi,
			   स्थिर काष्ठा spi_transfer *xfer)
अणु
	वापस xfer->len > rspi->ops->fअगरo_size;
पूर्ण

अटल bool rspi_can_dma(काष्ठा spi_controller *ctlr, काष्ठा spi_device *spi,
			 काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);

	वापस __rspi_can_dma(rspi, xfer);
पूर्ण

अटल पूर्णांक rspi_dma_check_then_transfer(काष्ठा rspi_data *rspi,
					 काष्ठा spi_transfer *xfer)
अणु
	अगर (!rspi->ctlr->can_dma || !__rspi_can_dma(rspi, xfer))
		वापस -EAGAIN;

	/* rx_buf can be शून्य on RSPI on SH in TX-only Mode */
	वापस rspi_dma_transfer(rspi, &xfer->tx_sg,
				xfer->rx_buf ? &xfer->rx_sg : शून्य);
पूर्ण

अटल पूर्णांक rspi_common_transfer(काष्ठा rspi_data *rspi,
				काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक ret;

	xfer->effective_speed_hz = rspi->speed_hz;

	ret = rspi_dma_check_then_transfer(rspi, xfer);
	अगर (ret != -EAGAIN)
		वापस ret;

	ret = rspi_pio_transfer(rspi, xfer->tx_buf, xfer->rx_buf, xfer->len);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम the last transmission */
	rspi_रुको_क्रम_tx_empty(rspi);

	वापस 0;
पूर्ण

अटल पूर्णांक rspi_transfer_one(काष्ठा spi_controller *ctlr,
			     काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);
	u8 spcr;

	spcr = rspi_पढ़ो8(rspi, RSPI_SPCR);
	अगर (xfer->rx_buf) अणु
		rspi_receive_init(rspi);
		spcr &= ~SPCR_TXMD;
	पूर्ण अन्यथा अणु
		spcr |= SPCR_TXMD;
	पूर्ण
	rspi_ग_लिखो8(rspi, spcr, RSPI_SPCR);

	वापस rspi_common_transfer(rspi, xfer);
पूर्ण

अटल पूर्णांक rspi_rz_transfer_one(काष्ठा spi_controller *ctlr,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);

	rspi_rz_receive_init(rspi);

	वापस rspi_common_transfer(rspi, xfer);
पूर्ण

अटल पूर्णांक qspi_trigger_transfer_out_in(काष्ठा rspi_data *rspi, स्थिर u8 *tx,
					u8 *rx, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i, n;
	पूर्णांक ret;

	जबतक (len > 0) अणु
		n = qspi_set_send_trigger(rspi, len);
		qspi_set_receive_trigger(rspi, len);
		ret = rspi_रुको_क्रम_tx_empty(rspi);
		अगर (ret < 0) अणु
			dev_err(&rspi->ctlr->dev, "transmit timeout\n");
			वापस ret;
		पूर्ण
		क्रम (i = 0; i < n; i++)
			rspi_ग_लिखो_data(rspi, *tx++);

		ret = rspi_रुको_क्रम_rx_full(rspi);
		अगर (ret < 0) अणु
			dev_err(&rspi->ctlr->dev, "receive timeout\n");
			वापस ret;
		पूर्ण
		क्रम (i = 0; i < n; i++)
			*rx++ = rspi_पढ़ो_data(rspi);

		len -= n;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_transfer_out_in(काष्ठा rspi_data *rspi,
				काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक ret;

	qspi_receive_init(rspi);

	ret = rspi_dma_check_then_transfer(rspi, xfer);
	अगर (ret != -EAGAIN)
		वापस ret;

	वापस qspi_trigger_transfer_out_in(rspi, xfer->tx_buf,
					    xfer->rx_buf, xfer->len);
पूर्ण

अटल पूर्णांक qspi_transfer_out(काष्ठा rspi_data *rspi, काष्ठा spi_transfer *xfer)
अणु
	स्थिर u8 *tx = xfer->tx_buf;
	अचिन्हित पूर्णांक n = xfer->len;
	अचिन्हित पूर्णांक i, len;
	पूर्णांक ret;

	अगर (rspi->ctlr->can_dma && __rspi_can_dma(rspi, xfer)) अणु
		ret = rspi_dma_transfer(rspi, &xfer->tx_sg, शून्य);
		अगर (ret != -EAGAIN)
			वापस ret;
	पूर्ण

	जबतक (n > 0) अणु
		len = qspi_set_send_trigger(rspi, n);
		ret = rspi_रुको_क्रम_tx_empty(rspi);
		अगर (ret < 0) अणु
			dev_err(&rspi->ctlr->dev, "transmit timeout\n");
			वापस ret;
		पूर्ण
		क्रम (i = 0; i < len; i++)
			rspi_ग_लिखो_data(rspi, *tx++);

		n -= len;
	पूर्ण

	/* Wait क्रम the last transmission */
	rspi_रुको_क्रम_tx_empty(rspi);

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_transfer_in(काष्ठा rspi_data *rspi, काष्ठा spi_transfer *xfer)
अणु
	u8 *rx = xfer->rx_buf;
	अचिन्हित पूर्णांक n = xfer->len;
	अचिन्हित पूर्णांक i, len;
	पूर्णांक ret;

	अगर (rspi->ctlr->can_dma && __rspi_can_dma(rspi, xfer)) अणु
		पूर्णांक ret = rspi_dma_transfer(rspi, शून्य, &xfer->rx_sg);
		अगर (ret != -EAGAIN)
			वापस ret;
	पूर्ण

	जबतक (n > 0) अणु
		len = qspi_set_receive_trigger(rspi, n);
		ret = rspi_रुको_क्रम_rx_full(rspi);
		अगर (ret < 0) अणु
			dev_err(&rspi->ctlr->dev, "receive timeout\n");
			वापस ret;
		पूर्ण
		क्रम (i = 0; i < len; i++)
			*rx++ = rspi_पढ़ो_data(rspi);

		n -= len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_transfer_one(काष्ठा spi_controller *ctlr,
			     काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);

	xfer->effective_speed_hz = rspi->speed_hz;
	अगर (spi->mode & SPI_LOOP) अणु
		वापस qspi_transfer_out_in(rspi, xfer);
	पूर्ण अन्यथा अगर (xfer->tx_nbits > SPI_NBITS_SINGLE) अणु
		/* Quad or Dual SPI Write */
		वापस qspi_transfer_out(rspi, xfer);
	पूर्ण अन्यथा अगर (xfer->rx_nbits > SPI_NBITS_SINGLE) अणु
		/* Quad or Dual SPI Read */
		वापस qspi_transfer_in(rspi, xfer);
	पूर्ण अन्यथा अणु
		/* Single SPI Transfer */
		वापस qspi_transfer_out_in(rspi, xfer);
	पूर्ण
पूर्ण

अटल u16 qspi_transfer_mode(स्थिर काष्ठा spi_transfer *xfer)
अणु
	अगर (xfer->tx_buf)
		चयन (xfer->tx_nbits) अणु
		हाल SPI_NBITS_QUAD:
			वापस SPCMD_SPIMOD_QUAD;
		हाल SPI_NBITS_DUAL:
			वापस SPCMD_SPIMOD_DUAL;
		शेष:
			वापस 0;
		पूर्ण
	अगर (xfer->rx_buf)
		चयन (xfer->rx_nbits) अणु
		हाल SPI_NBITS_QUAD:
			वापस SPCMD_SPIMOD_QUAD | SPCMD_SPRW;
		हाल SPI_NBITS_DUAL:
			वापस SPCMD_SPIMOD_DUAL | SPCMD_SPRW;
		शेष:
			वापस 0;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_setup_sequencer(काष्ठा rspi_data *rspi,
				स्थिर काष्ठा spi_message *msg)
अणु
	स्थिर काष्ठा spi_transfer *xfer;
	अचिन्हित पूर्णांक i = 0, len = 0;
	u16 current_mode = 0xffff, mode;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		mode = qspi_transfer_mode(xfer);
		अगर (mode == current_mode) अणु
			len += xfer->len;
			जारी;
		पूर्ण

		/* Transfer mode change */
		अगर (i) अणु
			/* Set transfer data length of previous transfer */
			rspi_ग_लिखो32(rspi, len, QSPI_SPBMUL(i - 1));
		पूर्ण

		अगर (i >= QSPI_NUM_SPCMD) अणु
			dev_err(&msg->spi->dev,
				"Too many different transfer modes");
			वापस -EINVAL;
		पूर्ण

		/* Program transfer mode क्रम this transfer */
		rspi_ग_लिखो16(rspi, rspi->spcmd | mode, RSPI_SPCMD(i));
		current_mode = mode;
		len = xfer->len;
		i++;
	पूर्ण
	अगर (i) अणु
		/* Set final transfer data length and sequence length */
		rspi_ग_लिखो32(rspi, len, QSPI_SPBMUL(i - 1));
		rspi_ग_लिखो8(rspi, i - 1, RSPI_SPSCR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(spi->controller);
	u8 sslp;

	अगर (spi->cs_gpiod)
		वापस 0;

	pm_runसमय_get_sync(&rspi->pdev->dev);
	spin_lock_irq(&rspi->lock);

	sslp = rspi_पढ़ो8(rspi, RSPI_SSLP);
	अगर (spi->mode & SPI_CS_HIGH)
		sslp |= SSLP_SSLP(spi->chip_select);
	अन्यथा
		sslp &= ~SSLP_SSLP(spi->chip_select);
	rspi_ग_लिखो8(rspi, sslp, RSPI_SSLP);

	spin_unlock_irq(&rspi->lock);
	pm_runसमय_put(&rspi->pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक rspi_prepare_message(काष्ठा spi_controller *ctlr,
				काष्ठा spi_message *msg)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);
	काष्ठा spi_device *spi = msg->spi;
	स्थिर काष्ठा spi_transfer *xfer;
	पूर्णांक ret;

	/*
	 * As the Bit Rate Register must not be changed जबतक the device is
	 * active, all transfers in a message must use the same bit rate.
	 * In theory, the sequencer could be enabled, and each Command Register
	 * could भागide the base bit rate by a dअगरferent value.
	 * However, most RSPI variants करो not have Transfer Data Length
	 * Multiplier Setting Registers, so each sequence step would be limited
	 * to a single word, making this feature unsuitable क्रम large
	 * transfers, which would gain most from it.
	 */
	rspi->speed_hz = spi->max_speed_hz;
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		अगर (xfer->speed_hz < rspi->speed_hz)
			rspi->speed_hz = xfer->speed_hz;
	पूर्ण

	rspi->spcmd = SPCMD_SSLKP;
	अगर (spi->mode & SPI_CPOL)
		rspi->spcmd |= SPCMD_CPOL;
	अगर (spi->mode & SPI_CPHA)
		rspi->spcmd |= SPCMD_CPHA;
	अगर (spi->mode & SPI_LSB_FIRST)
		rspi->spcmd |= SPCMD_LSBF;

	/* Configure slave संकेत to निश्चित */
	rspi->spcmd |= SPCMD_SSLA(spi->cs_gpiod ? rspi->ctlr->unused_native_cs
						: spi->chip_select);

	/* CMOS output mode and MOSI संकेत from previous transfer */
	rspi->sppcr = 0;
	अगर (spi->mode & SPI_LOOP)
		rspi->sppcr |= SPPCR_SPLP;

	rspi->ops->set_config_रेजिस्टर(rspi, 8);

	अगर (msg->spi->mode &
	    (SPI_TX_DUAL | SPI_TX_QUAD | SPI_RX_DUAL | SPI_RX_QUAD)) अणु
		/* Setup sequencer क्रम messages with multiple transfer modes */
		ret = qspi_setup_sequencer(rspi, msg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Enable SPI function in master mode */
	rspi_ग_लिखो8(rspi, rspi_पढ़ो8(rspi, RSPI_SPCR) | SPCR_SPE, RSPI_SPCR);
	वापस 0;
पूर्ण

अटल पूर्णांक rspi_unprepare_message(काष्ठा spi_controller *ctlr,
				  काष्ठा spi_message *msg)
अणु
	काष्ठा rspi_data *rspi = spi_controller_get_devdata(ctlr);

	/* Disable SPI function */
	rspi_ग_लिखो8(rspi, rspi_पढ़ो8(rspi, RSPI_SPCR) & ~SPCR_SPE, RSPI_SPCR);

	/* Reset sequencer क्रम Single SPI Transfers */
	rspi_ग_लिखो16(rspi, rspi->spcmd, RSPI_SPCMD0);
	rspi_ग_लिखो8(rspi, 0, RSPI_SPSCR);
	वापस 0;
पूर्ण

अटल irqवापस_t rspi_irq_mux(पूर्णांक irq, व्योम *_sr)
अणु
	काष्ठा rspi_data *rspi = _sr;
	u8 spsr;
	irqवापस_t ret = IRQ_NONE;
	u8 disable_irq = 0;

	rspi->spsr = spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (spsr & SPSR_SPRF)
		disable_irq |= SPCR_SPRIE;
	अगर (spsr & SPSR_SPTEF)
		disable_irq |= SPCR_SPTIE;

	अगर (disable_irq) अणु
		ret = IRQ_HANDLED;
		rspi_disable_irq(rspi, disable_irq);
		wake_up(&rspi->रुको);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t rspi_irq_rx(पूर्णांक irq, व्योम *_sr)
अणु
	काष्ठा rspi_data *rspi = _sr;
	u8 spsr;

	rspi->spsr = spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (spsr & SPSR_SPRF) अणु
		rspi_disable_irq(rspi, SPCR_SPRIE);
		wake_up(&rspi->रुको);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rspi_irq_tx(पूर्णांक irq, व्योम *_sr)
अणु
	काष्ठा rspi_data *rspi = _sr;
	u8 spsr;

	rspi->spsr = spsr = rspi_पढ़ो8(rspi, RSPI_SPSR);
	अगर (spsr & SPSR_SPTEF) अणु
		rspi_disable_irq(rspi, SPCR_SPTIE);
		wake_up(&rspi->रुको);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dma_chan *rspi_request_dma_chan(काष्ठा device *dev,
					      क्रमागत dma_transfer_direction dir,
					      अचिन्हित पूर्णांक id,
					      dma_addr_t port_addr)
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
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण अन्यथा अणु
		cfg.src_addr = port_addr;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_warn(dev, "dmaengine_slave_config failed %d\n", ret);
		dma_release_channel(chan);
		वापस शून्य;
	पूर्ण

	वापस chan;
पूर्ण

अटल पूर्णांक rspi_request_dma(काष्ठा device *dev, काष्ठा spi_controller *ctlr,
			    स्थिर काष्ठा resource *res)
अणु
	स्थिर काष्ठा rspi_plat_data *rspi_pd = dev_get_platdata(dev);
	अचिन्हित पूर्णांक dma_tx_id, dma_rx_id;

	अगर (dev->of_node) अणु
		/* In the OF हाल we will get the slave IDs from the DT */
		dma_tx_id = 0;
		dma_rx_id = 0;
	पूर्ण अन्यथा अगर (rspi_pd && rspi_pd->dma_tx_id && rspi_pd->dma_rx_id) अणु
		dma_tx_id = rspi_pd->dma_tx_id;
		dma_rx_id = rspi_pd->dma_rx_id;
	पूर्ण अन्यथा अणु
		/* The driver assumes no error. */
		वापस 0;
	पूर्ण

	ctlr->dma_tx = rspi_request_dma_chan(dev, DMA_MEM_TO_DEV, dma_tx_id,
					     res->start + RSPI_SPDR);
	अगर (!ctlr->dma_tx)
		वापस -ENODEV;

	ctlr->dma_rx = rspi_request_dma_chan(dev, DMA_DEV_TO_MEM, dma_rx_id,
					     res->start + RSPI_SPDR);
	अगर (!ctlr->dma_rx) अणु
		dma_release_channel(ctlr->dma_tx);
		ctlr->dma_tx = शून्य;
		वापस -ENODEV;
	पूर्ण

	ctlr->can_dma = rspi_can_dma;
	dev_info(dev, "DMA available");
	वापस 0;
पूर्ण

अटल व्योम rspi_release_dma(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr->dma_tx)
		dma_release_channel(ctlr->dma_tx);
	अगर (ctlr->dma_rx)
		dma_release_channel(ctlr->dma_rx);
पूर्ण

अटल पूर्णांक rspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rspi_data *rspi = platक्रमm_get_drvdata(pdev);

	rspi_release_dma(rspi->ctlr);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_ops rspi_ops = अणु
	.set_config_रेजिस्टर =	rspi_set_config_रेजिस्टर,
	.transfer_one =		rspi_transfer_one,
	.min_भाग =		2,
	.max_भाग =		4096,
	.flags =		SPI_CONTROLLER_MUST_TX,
	.fअगरo_size =		8,
	.num_hw_ss =		2,
पूर्ण;

अटल स्थिर काष्ठा spi_ops rspi_rz_ops = अणु
	.set_config_रेजिस्टर =	rspi_rz_set_config_रेजिस्टर,
	.transfer_one =		rspi_rz_transfer_one,
	.min_भाग =		2,
	.max_भाग =		4096,
	.flags =		SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX,
	.fअगरo_size =		8,	/* 8 क्रम TX, 32 क्रम RX */
	.num_hw_ss =		1,
पूर्ण;

अटल स्थिर काष्ठा spi_ops qspi_ops = अणु
	.set_config_रेजिस्टर =	qspi_set_config_रेजिस्टर,
	.transfer_one =		qspi_transfer_one,
	.extra_mode_bits =	SPI_TX_DUAL | SPI_TX_QUAD |
				SPI_RX_DUAL | SPI_RX_QUAD,
	.min_भाग =		1,
	.max_भाग =		4080,
	.flags =		SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX,
	.fअगरo_size =		32,
	.num_hw_ss =		1,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rspi_of_match[] = अणु
	/* RSPI on legacy SH */
	अणु .compatible = "renesas,rspi", .data = &rspi_ops पूर्ण,
	/* RSPI on RZ/A1H */
	अणु .compatible = "renesas,rspi-rz", .data = &rspi_rz_ops पूर्ण,
	/* QSPI on R-Car Gen2 */
	अणु .compatible = "renesas,qspi", .data = &qspi_ops पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rspi_of_match);

अटल पूर्णांक rspi_parse_dt(काष्ठा device *dev, काष्ठा spi_controller *ctlr)
अणु
	u32 num_cs;
	पूर्णांक error;

	/* Parse DT properties */
	error = of_property_पढ़ो_u32(dev->of_node, "num-cs", &num_cs);
	अगर (error) अणु
		dev_err(dev, "of_property_read_u32 num-cs failed %d\n", error);
		वापस error;
	पूर्ण

	ctlr->num_chipselect = num_cs;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rspi_of_match	शून्य
अटल अंतरभूत पूर्णांक rspi_parse_dt(काष्ठा device *dev, काष्ठा spi_controller *ctlr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक rspi_request_irq(काष्ठा device *dev, अचिन्हित पूर्णांक irq,
			    irq_handler_t handler, स्थिर अक्षर *suffix,
			    व्योम *dev_id)
अणु
	स्थिर अक्षर *name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s:%s",
					  dev_name(dev), suffix);
	अगर (!name)
		वापस -ENOMEM;

	वापस devm_request_irq(dev, irq, handler, 0, name, dev_id);
पूर्ण

अटल पूर्णांक rspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा spi_controller *ctlr;
	काष्ठा rspi_data *rspi;
	पूर्णांक ret;
	स्थिर काष्ठा rspi_plat_data *rspi_pd;
	स्थिर काष्ठा spi_ops *ops;
	अचिन्हित दीर्घ clksrc;

	ctlr = spi_alloc_master(&pdev->dev, माप(काष्ठा rspi_data));
	अगर (ctlr == शून्य)
		वापस -ENOMEM;

	ops = of_device_get_match_data(&pdev->dev);
	अगर (ops) अणु
		ret = rspi_parse_dt(&pdev->dev, ctlr);
		अगर (ret)
			जाओ error1;
	पूर्ण अन्यथा अणु
		ops = (काष्ठा spi_ops *)pdev->id_entry->driver_data;
		rspi_pd = dev_get_platdata(&pdev->dev);
		अगर (rspi_pd && rspi_pd->num_chipselect)
			ctlr->num_chipselect = rspi_pd->num_chipselect;
		अन्यथा
			ctlr->num_chipselect = 2; /* शेष */
	पूर्ण

	rspi = spi_controller_get_devdata(ctlr);
	platक्रमm_set_drvdata(pdev, rspi);
	rspi->ops = ops;
	rspi->ctlr = ctlr;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rspi->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rspi->addr)) अणु
		ret = PTR_ERR(rspi->addr);
		जाओ error1;
	पूर्ण

	rspi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rspi->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = PTR_ERR(rspi->clk);
		जाओ error1;
	पूर्ण

	rspi->pdev = pdev;
	pm_runसमय_enable(&pdev->dev);

	init_रुकोqueue_head(&rspi->रुको);
	spin_lock_init(&rspi->lock);

	ctlr->bus_num = pdev->id;
	ctlr->setup = rspi_setup;
	ctlr->स्वतः_runसमय_pm = true;
	ctlr->transfer_one = ops->transfer_one;
	ctlr->prepare_message = rspi_prepare_message;
	ctlr->unprepare_message = rspi_unprepare_message;
	ctlr->mode_bits = SPI_CPHA | SPI_CPOL | SPI_CS_HIGH | SPI_LSB_FIRST |
			  SPI_LOOP | ops->extra_mode_bits;
	clksrc = clk_get_rate(rspi->clk);
	ctlr->min_speed_hz = DIV_ROUND_UP(clksrc, ops->max_भाग);
	ctlr->max_speed_hz = DIV_ROUND_UP(clksrc, ops->min_भाग);
	ctlr->flags = ops->flags;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->use_gpio_descriptors = true;
	ctlr->max_native_cs = rspi->ops->num_hw_ss;

	ret = platक्रमm_get_irq_byname_optional(pdev, "rx");
	अगर (ret < 0) अणु
		ret = platक्रमm_get_irq_byname_optional(pdev, "mux");
		अगर (ret < 0)
			ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret >= 0)
			rspi->rx_irq = rspi->tx_irq = ret;
	पूर्ण अन्यथा अणु
		rspi->rx_irq = ret;
		ret = platक्रमm_get_irq_byname(pdev, "tx");
		अगर (ret >= 0)
			rspi->tx_irq = ret;
	पूर्ण

	अगर (rspi->rx_irq == rspi->tx_irq) अणु
		/* Single multiplexed पूर्णांकerrupt */
		ret = rspi_request_irq(&pdev->dev, rspi->rx_irq, rspi_irq_mux,
				       "mux", rspi);
	पूर्ण अन्यथा अणु
		/* Multi-पूर्णांकerrupt mode, only SPRI and SPTI are used */
		ret = rspi_request_irq(&pdev->dev, rspi->rx_irq, rspi_irq_rx,
				       "rx", rspi);
		अगर (!ret)
			ret = rspi_request_irq(&pdev->dev, rspi->tx_irq,
					       rspi_irq_tx, "tx", rspi);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq error\n");
		जाओ error2;
	पूर्ण

	ret = rspi_request_dma(&pdev->dev, ctlr, res);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "DMA not available, using PIO\n");

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "devm_spi_register_controller error.\n");
		जाओ error3;
	पूर्ण

	dev_info(&pdev->dev, "probed\n");

	वापस 0;

error3:
	rspi_release_dma(ctlr);
error2:
	pm_runसमय_disable(&pdev->dev);
error1:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id spi_driver_ids[] = अणु
	अणु "rspi",	(kernel_uदीर्घ_t)&rspi_ops पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, spi_driver_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा rspi_data *rspi = dev_get_drvdata(dev);

	वापस spi_controller_suspend(rspi->ctlr);
पूर्ण

अटल पूर्णांक rspi_resume(काष्ठा device *dev)
अणु
	काष्ठा rspi_data *rspi = dev_get_drvdata(dev);

	वापस spi_controller_resume(rspi->ctlr);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rspi_pm_ops, rspi_suspend, rspi_resume);
#घोषणा DEV_PM_OPS	&rspi_pm_ops
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver rspi_driver = अणु
	.probe =	rspi_probe,
	.हटाओ =	rspi_हटाओ,
	.id_table =	spi_driver_ids,
	.driver		= अणु
		.name = "renesas_spi",
		.pm = DEV_PM_OPS,
		.of_match_table = of_match_ptr(rspi_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rspi_driver);

MODULE_DESCRIPTION("Renesas RSPI bus driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_ALIAS("platform:rspi");
