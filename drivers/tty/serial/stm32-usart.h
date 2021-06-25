<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics SA 2017
 * Authors:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 *	     Gerald Baeza <gerald_baeza@yahoo.fr>
 */

#घोषणा DRIVER_NAME "stm32-usart"

काष्ठा sपंचांग32_usart_offsets अणु
	u8 cr1;
	u8 cr2;
	u8 cr3;
	u8 brr;
	u8 gtpr;
	u8 rtor;
	u8 rqr;
	u8 isr;
	u8 icr;
	u8 rdr;
	u8 tdr;
पूर्ण;

काष्ठा sपंचांग32_usart_config अणु
	u8 uart_enable_bit; /* USART_CR1_UE */
	bool has_7bits_data;
	bool has_swap;
	bool has_wakeup;
	bool has_fअगरo;
	पूर्णांक fअगरosize;
पूर्ण;

काष्ठा sपंचांग32_usart_info अणु
	काष्ठा sपंचांग32_usart_offsets ofs;
	काष्ठा sपंचांग32_usart_config cfg;
पूर्ण;

#घोषणा UNDEF_REG 0xff

/* Register offsets */
काष्ठा sपंचांग32_usart_info sपंचांग32f4_info = अणु
	.ofs = अणु
		.isr	= 0x00,
		.rdr	= 0x04,
		.tdr	= 0x04,
		.brr	= 0x08,
		.cr1	= 0x0c,
		.cr2	= 0x10,
		.cr3	= 0x14,
		.gtpr	= 0x18,
		.rtor	= UNDEF_REG,
		.rqr	= UNDEF_REG,
		.icr	= UNDEF_REG,
	पूर्ण,
	.cfg = अणु
		.uart_enable_bit = 13,
		.has_7bits_data = false,
		.fअगरosize = 1,
	पूर्ण
पूर्ण;

काष्ठा sपंचांग32_usart_info sपंचांग32f7_info = अणु
	.ofs = अणु
		.cr1	= 0x00,
		.cr2	= 0x04,
		.cr3	= 0x08,
		.brr	= 0x0c,
		.gtpr	= 0x10,
		.rtor	= 0x14,
		.rqr	= 0x18,
		.isr	= 0x1c,
		.icr	= 0x20,
		.rdr	= 0x24,
		.tdr	= 0x28,
	पूर्ण,
	.cfg = अणु
		.uart_enable_bit = 0,
		.has_7bits_data = true,
		.has_swap = true,
		.fअगरosize = 1,
	पूर्ण
पूर्ण;

काष्ठा sपंचांग32_usart_info sपंचांग32h7_info = अणु
	.ofs = अणु
		.cr1	= 0x00,
		.cr2	= 0x04,
		.cr3	= 0x08,
		.brr	= 0x0c,
		.gtpr	= 0x10,
		.rtor	= 0x14,
		.rqr	= 0x18,
		.isr	= 0x1c,
		.icr	= 0x20,
		.rdr	= 0x24,
		.tdr	= 0x28,
	पूर्ण,
	.cfg = अणु
		.uart_enable_bit = 0,
		.has_7bits_data = true,
		.has_swap = true,
		.has_wakeup = true,
		.has_fअगरo = true,
		.fअगरosize = 16,
	पूर्ण
पूर्ण;

/* USART_SR (F4) / USART_ISR (F7) */
#घोषणा USART_SR_PE		BIT(0)
#घोषणा USART_SR_FE		BIT(1)
#घोषणा USART_SR_NF		BIT(2)
#घोषणा USART_SR_ORE		BIT(3)
#घोषणा USART_SR_IDLE		BIT(4)
#घोषणा USART_SR_RXNE		BIT(5)
#घोषणा USART_SR_TC		BIT(6)
#घोषणा USART_SR_TXE		BIT(7)
#घोषणा USART_SR_CTSIF		BIT(9)
#घोषणा USART_SR_CTS		BIT(10)		/* F7 */
#घोषणा USART_SR_RTOF		BIT(11)		/* F7 */
#घोषणा USART_SR_EOBF		BIT(12)		/* F7 */
#घोषणा USART_SR_ABRE		BIT(14)		/* F7 */
#घोषणा USART_SR_ABRF		BIT(15)		/* F7 */
#घोषणा USART_SR_BUSY		BIT(16)		/* F7 */
#घोषणा USART_SR_CMF		BIT(17)		/* F7 */
#घोषणा USART_SR_SBKF		BIT(18)		/* F7 */
#घोषणा USART_SR_WUF		BIT(20)		/* H7 */
#घोषणा USART_SR_TEACK		BIT(21)		/* F7 */
#घोषणा USART_SR_ERR_MASK	(USART_SR_ORE | USART_SR_FE | USART_SR_PE)
/* Dummy bits */
#घोषणा USART_SR_DUMMY_RX	BIT(16)

/* USART_DR */
#घोषणा USART_DR_MASK		GENMASK(8, 0)

/* USART_BRR */
#घोषणा USART_BRR_DIV_F_MASK	GENMASK(3, 0)
#घोषणा USART_BRR_DIV_M_MASK	GENMASK(15, 4)
#घोषणा USART_BRR_DIV_M_SHIFT	4
#घोषणा USART_BRR_04_R_SHIFT	1

/* USART_CR1 */
#घोषणा USART_CR1_SBK		BIT(0)
#घोषणा USART_CR1_RWU		BIT(1)		/* F4 */
#घोषणा USART_CR1_UESM		BIT(1)		/* H7 */
#घोषणा USART_CR1_RE		BIT(2)
#घोषणा USART_CR1_TE		BIT(3)
#घोषणा USART_CR1_IDLEIE	BIT(4)
#घोषणा USART_CR1_RXNEIE	BIT(5)
#घोषणा USART_CR1_TCIE		BIT(6)
#घोषणा USART_CR1_TXEIE		BIT(7)
#घोषणा USART_CR1_PEIE		BIT(8)
#घोषणा USART_CR1_PS		BIT(9)
#घोषणा USART_CR1_PCE		BIT(10)
#घोषणा USART_CR1_WAKE		BIT(11)
#घोषणा USART_CR1_M0		BIT(12)		/* F7 (CR1_M क्रम F4) */
#घोषणा USART_CR1_MME		BIT(13)		/* F7 */
#घोषणा USART_CR1_CMIE		BIT(14)		/* F7 */
#घोषणा USART_CR1_OVER8		BIT(15)
#घोषणा USART_CR1_DEDT_MASK	GENMASK(20, 16)	/* F7 */
#घोषणा USART_CR1_DEAT_MASK	GENMASK(25, 21)	/* F7 */
#घोषणा USART_CR1_RTOIE		BIT(26)		/* F7 */
#घोषणा USART_CR1_EOBIE		BIT(27)		/* F7 */
#घोषणा USART_CR1_M1		BIT(28)		/* F7 */
#घोषणा USART_CR1_IE_MASK	(GENMASK(8, 4) | BIT(14) | BIT(26) | BIT(27))
#घोषणा USART_CR1_FIFOEN	BIT(29)		/* H7 */
#घोषणा USART_CR1_DEAT_SHIFT 21
#घोषणा USART_CR1_DEDT_SHIFT 16

/* USART_CR2 */
#घोषणा USART_CR2_ADD_MASK	GENMASK(3, 0)	/* F4 */
#घोषणा USART_CR2_ADDM7		BIT(4)		/* F7 */
#घोषणा USART_CR2_LBCL		BIT(8)
#घोषणा USART_CR2_CPHA		BIT(9)
#घोषणा USART_CR2_CPOL		BIT(10)
#घोषणा USART_CR2_CLKEN		BIT(11)
#घोषणा USART_CR2_STOP_2B	BIT(13)
#घोषणा USART_CR2_STOP_MASK	GENMASK(13, 12)
#घोषणा USART_CR2_LINEN		BIT(14)
#घोषणा USART_CR2_SWAP		BIT(15)		/* F7 */
#घोषणा USART_CR2_RXINV		BIT(16)		/* F7 */
#घोषणा USART_CR2_TXINV		BIT(17)		/* F7 */
#घोषणा USART_CR2_DATAINV	BIT(18)		/* F7 */
#घोषणा USART_CR2_MSBFIRST	BIT(19)		/* F7 */
#घोषणा USART_CR2_ABREN		BIT(20)		/* F7 */
#घोषणा USART_CR2_ABRMOD_MASK	GENMASK(22, 21)	/* F7 */
#घोषणा USART_CR2_RTOEN		BIT(23)		/* F7 */
#घोषणा USART_CR2_ADD_F7_MASK	GENMASK(31, 24)	/* F7 */

/* USART_CR3 */
#घोषणा USART_CR3_EIE		BIT(0)
#घोषणा USART_CR3_IREN		BIT(1)
#घोषणा USART_CR3_IRLP		BIT(2)
#घोषणा USART_CR3_HDSEL		BIT(3)
#घोषणा USART_CR3_NACK		BIT(4)
#घोषणा USART_CR3_SCEN		BIT(5)
#घोषणा USART_CR3_DMAR		BIT(6)
#घोषणा USART_CR3_DMAT		BIT(7)
#घोषणा USART_CR3_RTSE		BIT(8)
#घोषणा USART_CR3_CTSE		BIT(9)
#घोषणा USART_CR3_CTSIE		BIT(10)
#घोषणा USART_CR3_ONEBIT	BIT(11)
#घोषणा USART_CR3_OVRDIS	BIT(12)		/* F7 */
#घोषणा USART_CR3_DDRE		BIT(13)		/* F7 */
#घोषणा USART_CR3_DEM		BIT(14)		/* F7 */
#घोषणा USART_CR3_DEP		BIT(15)		/* F7 */
#घोषणा USART_CR3_SCARCNT_MASK	GENMASK(19, 17)	/* F7 */
#घोषणा USART_CR3_WUS_MASK	GENMASK(21, 20)	/* H7 */
#घोषणा USART_CR3_WUS_START_BIT	BIT(21)		/* H7 */
#घोषणा USART_CR3_WUFIE		BIT(22)		/* H7 */
#घोषणा USART_CR3_TXFTIE	BIT(23)		/* H7 */
#घोषणा USART_CR3_TCBGTIE	BIT(24)		/* H7 */
#घोषणा USART_CR3_RXFTCFG_MASK	GENMASK(27, 25)	/* H7 */
#घोषणा USART_CR3_RXFTCFG_SHIFT	25		/* H7 */
#घोषणा USART_CR3_RXFTIE	BIT(28)		/* H7 */
#घोषणा USART_CR3_TXFTCFG_MASK	GENMASK(31, 29)	/* H7 */
#घोषणा USART_CR3_TXFTCFG_SHIFT	29		/* H7 */

/* USART_GTPR */
#घोषणा USART_GTPR_PSC_MASK	GENMASK(7, 0)
#घोषणा USART_GTPR_GT_MASK	GENMASK(15, 8)

/* USART_RTOR */
#घोषणा USART_RTOR_RTO_MASK	GENMASK(23, 0)	/* F7 */
#घोषणा USART_RTOR_BLEN_MASK	GENMASK(31, 24)	/* F7 */

/* USART_RQR */
#घोषणा USART_RQR_ABRRQ		BIT(0)		/* F7 */
#घोषणा USART_RQR_SBKRQ		BIT(1)		/* F7 */
#घोषणा USART_RQR_MMRQ		BIT(2)		/* F7 */
#घोषणा USART_RQR_RXFRQ		BIT(3)		/* F7 */
#घोषणा USART_RQR_TXFRQ		BIT(4)		/* F7 */

/* USART_ICR */
#घोषणा USART_ICR_PECF		BIT(0)		/* F7 */
#घोषणा USART_ICR_FECF		BIT(1)		/* F7 */
#घोषणा USART_ICR_ORECF		BIT(3)		/* F7 */
#घोषणा USART_ICR_IDLECF	BIT(4)		/* F7 */
#घोषणा USART_ICR_TCCF		BIT(6)		/* F7 */
#घोषणा USART_ICR_CTSCF		BIT(9)		/* F7 */
#घोषणा USART_ICR_RTOCF		BIT(11)		/* F7 */
#घोषणा USART_ICR_EOBCF		BIT(12)		/* F7 */
#घोषणा USART_ICR_CMCF		BIT(17)		/* F7 */
#घोषणा USART_ICR_WUCF		BIT(20)		/* H7 */

#घोषणा STM32_SERIAL_NAME "ttySTM"
#घोषणा STM32_MAX_PORTS 8

#घोषणा RX_BUF_L 200		 /* dma rx buffer length     */
#घोषणा RX_BUF_P RX_BUF_L	 /* dma rx buffer period     */
#घोषणा TX_BUF_L 200		 /* dma tx buffer length     */

काष्ठा sपंचांग32_port अणु
	काष्ठा uart_port port;
	काष्ठा clk *clk;
	स्थिर काष्ठा sपंचांग32_usart_info *info;
	काष्ठा dma_chan *rx_ch;  /* dma rx channel            */
	dma_addr_t rx_dma_buf;   /* dma rx buffer bus address */
	अचिन्हित अक्षर *rx_buf;   /* dma rx buffer cpu address */
	काष्ठा dma_chan *tx_ch;  /* dma tx channel            */
	dma_addr_t tx_dma_buf;   /* dma tx buffer bus address */
	अचिन्हित अक्षर *tx_buf;   /* dma tx buffer cpu address */
	u32 cr1_irq;		 /* USART_CR1_RXNEIE or RTOIE */
	u32 cr3_irq;		 /* USART_CR3_RXFTIE */
	पूर्णांक last_res;
	bool tx_dma_busy;	 /* dma tx busy               */
	bool hw_flow_control;
	bool swap;		 /* swap RX & TX pins */
	bool fअगरoen;
	पूर्णांक rxftcfg;		/* RX FIFO threshold CFG      */
	पूर्णांक txftcfg;		/* TX FIFO threshold CFG      */
	bool wakeup_src;
	पूर्णांक rdr_mask;		/* receive data रेजिस्टर mask */
	काष्ठा mctrl_gpios *gpios; /* modem control gpios */
पूर्ण;

अटल काष्ठा sपंचांग32_port sपंचांग32_ports[STM32_MAX_PORTS];
अटल काष्ठा uart_driver sपंचांग32_usart_driver;
