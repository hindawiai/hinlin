<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A driver क्रम the ARM PL022 PrimeCell SSP/SPI bus master.
 *
 * Copyright (C) 2008-2012 ST-Ericsson AB
 * Copyright (C) 2006 STMicroelectronics Pvt. Ltd.
 *
 * Author: Linus Walleij <linus.walleij@stericsson.com>
 *
 * Initial version inspired by:
 *	linux-2.6.17-rc3-mm1/drivers/spi/pxa2xx_spi.c
 * Initial aकरोption to PL022 by:
 *      Sachin Verma <sachin.verma@st.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/pl022.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>

/*
 * This macro is used to define some रेजिस्टर शेष values.
 * reg is masked with mask, the OR:ed with an (again masked)
 * val shअगरted sb steps to the left.
 */
#घोषणा SSP_WRITE_BITS(reg, val, mask, sb) \
 ((reg) = (((reg) & ~(mask)) | (((val)<<(sb)) & (mask))))

/*
 * This macro is also used to define some शेष values.
 * It will just shअगरt val by sb steps to the left and mask
 * the result with mask.
 */
#घोषणा GEN_MASK_BITS(val, mask, sb) \
 (((val)<<(sb)) & (mask))

#घोषणा DRIVE_TX		0
#घोषणा DO_NOT_DRIVE_TX		1

#घोषणा DO_NOT_QUEUE_DMA	0
#घोषणा QUEUE_DMA		1

#घोषणा RX_TRANSFER		1
#घोषणा TX_TRANSFER		2

/*
 * Macros to access SSP Registers with their offsets
 */
#घोषणा SSP_CR0(r)	(r + 0x000)
#घोषणा SSP_CR1(r)	(r + 0x004)
#घोषणा SSP_DR(r)	(r + 0x008)
#घोषणा SSP_SR(r)	(r + 0x00C)
#घोषणा SSP_CPSR(r)	(r + 0x010)
#घोषणा SSP_IMSC(r)	(r + 0x014)
#घोषणा SSP_RIS(r)	(r + 0x018)
#घोषणा SSP_MIS(r)	(r + 0x01C)
#घोषणा SSP_ICR(r)	(r + 0x020)
#घोषणा SSP_DMACR(r)	(r + 0x024)
#घोषणा SSP_CSR(r)	(r + 0x030) /* venकरोr extension */
#घोषणा SSP_ITCR(r)	(r + 0x080)
#घोषणा SSP_ITIP(r)	(r + 0x084)
#घोषणा SSP_ITOP(r)	(r + 0x088)
#घोषणा SSP_TDR(r)	(r + 0x08C)

#घोषणा SSP_PID0(r)	(r + 0xFE0)
#घोषणा SSP_PID1(r)	(r + 0xFE4)
#घोषणा SSP_PID2(r)	(r + 0xFE8)
#घोषणा SSP_PID3(r)	(r + 0xFEC)

#घोषणा SSP_CID0(r)	(r + 0xFF0)
#घोषणा SSP_CID1(r)	(r + 0xFF4)
#घोषणा SSP_CID2(r)	(r + 0xFF8)
#घोषणा SSP_CID3(r)	(r + 0xFFC)

/*
 * SSP Control Register 0  - SSP_CR0
 */
#घोषणा SSP_CR0_MASK_DSS	(0x0FUL << 0)
#घोषणा SSP_CR0_MASK_FRF	(0x3UL << 4)
#घोषणा SSP_CR0_MASK_SPO	(0x1UL << 6)
#घोषणा SSP_CR0_MASK_SPH	(0x1UL << 7)
#घोषणा SSP_CR0_MASK_SCR	(0xFFUL << 8)

/*
 * The ST version of this block moves som bits
 * in SSP_CR0 and extends it to 32 bits
 */
#घोषणा SSP_CR0_MASK_DSS_ST	(0x1FUL << 0)
#घोषणा SSP_CR0_MASK_HALFDUP_ST	(0x1UL << 5)
#घोषणा SSP_CR0_MASK_CSS_ST	(0x1FUL << 16)
#घोषणा SSP_CR0_MASK_FRF_ST	(0x3UL << 21)

/*
 * SSP Control Register 0  - SSP_CR1
 */
#घोषणा SSP_CR1_MASK_LBM	(0x1UL << 0)
#घोषणा SSP_CR1_MASK_SSE	(0x1UL << 1)
#घोषणा SSP_CR1_MASK_MS		(0x1UL << 2)
#घोषणा SSP_CR1_MASK_SOD	(0x1UL << 3)

/*
 * The ST version of this block adds some bits
 * in SSP_CR1
 */
#घोषणा SSP_CR1_MASK_RENDN_ST	(0x1UL << 4)
#घोषणा SSP_CR1_MASK_TENDN_ST	(0x1UL << 5)
#घोषणा SSP_CR1_MASK_MWAIT_ST	(0x1UL << 6)
#घोषणा SSP_CR1_MASK_RXIFLSEL_ST (0x7UL << 7)
#घोषणा SSP_CR1_MASK_TXIFLSEL_ST (0x7UL << 10)
/* This one is only in the PL023 variant */
#घोषणा SSP_CR1_MASK_FBCLKDEL_ST (0x7UL << 13)

/*
 * SSP Status Register - SSP_SR
 */
#घोषणा SSP_SR_MASK_TFE		(0x1UL << 0) /* Transmit FIFO empty */
#घोषणा SSP_SR_MASK_TNF		(0x1UL << 1) /* Transmit FIFO not full */
#घोषणा SSP_SR_MASK_RNE		(0x1UL << 2) /* Receive FIFO not empty */
#घोषणा SSP_SR_MASK_RFF		(0x1UL << 3) /* Receive FIFO full */
#घोषणा SSP_SR_MASK_BSY		(0x1UL << 4) /* Busy Flag */

/*
 * SSP Clock Prescale Register  - SSP_CPSR
 */
#घोषणा SSP_CPSR_MASK_CPSDVSR	(0xFFUL << 0)

/*
 * SSP Interrupt Mask Set/Clear Register - SSP_IMSC
 */
#घोषणा SSP_IMSC_MASK_RORIM (0x1UL << 0) /* Receive Overrun Interrupt mask */
#घोषणा SSP_IMSC_MASK_RTIM  (0x1UL << 1) /* Receive समयout Interrupt mask */
#घोषणा SSP_IMSC_MASK_RXIM  (0x1UL << 2) /* Receive FIFO Interrupt mask */
#घोषणा SSP_IMSC_MASK_TXIM  (0x1UL << 3) /* Transmit FIFO Interrupt mask */

/*
 * SSP Raw Interrupt Status Register - SSP_RIS
 */
/* Receive Overrun Raw Interrupt status */
#घोषणा SSP_RIS_MASK_RORRIS		(0x1UL << 0)
/* Receive Timeout Raw Interrupt status */
#घोषणा SSP_RIS_MASK_RTRIS		(0x1UL << 1)
/* Receive FIFO Raw Interrupt status */
#घोषणा SSP_RIS_MASK_RXRIS		(0x1UL << 2)
/* Transmit FIFO Raw Interrupt status */
#घोषणा SSP_RIS_MASK_TXRIS		(0x1UL << 3)

/*
 * SSP Masked Interrupt Status Register - SSP_MIS
 */
/* Receive Overrun Masked Interrupt status */
#घोषणा SSP_MIS_MASK_RORMIS		(0x1UL << 0)
/* Receive Timeout Masked Interrupt status */
#घोषणा SSP_MIS_MASK_RTMIS		(0x1UL << 1)
/* Receive FIFO Masked Interrupt status */
#घोषणा SSP_MIS_MASK_RXMIS		(0x1UL << 2)
/* Transmit FIFO Masked Interrupt status */
#घोषणा SSP_MIS_MASK_TXMIS		(0x1UL << 3)

/*
 * SSP Interrupt Clear Register - SSP_ICR
 */
/* Receive Overrun Raw Clear Interrupt bit */
#घोषणा SSP_ICR_MASK_RORIC		(0x1UL << 0)
/* Receive Timeout Clear Interrupt bit */
#घोषणा SSP_ICR_MASK_RTIC		(0x1UL << 1)

/*
 * SSP DMA Control Register - SSP_DMACR
 */
/* Receive DMA Enable bit */
#घोषणा SSP_DMACR_MASK_RXDMAE		(0x1UL << 0)
/* Transmit DMA Enable bit */
#घोषणा SSP_DMACR_MASK_TXDMAE		(0x1UL << 1)

/*
 * SSP Chip Select Control Register - SSP_CSR
 * (venकरोr extension)
 */
#घोषणा SSP_CSR_CSVALUE_MASK		(0x1FUL << 0)

/*
 * SSP Integration Test control Register - SSP_ITCR
 */
#घोषणा SSP_ITCR_MASK_ITEN		(0x1UL << 0)
#घोषणा SSP_ITCR_MASK_TESTFIFO		(0x1UL << 1)

/*
 * SSP Integration Test Input Register - SSP_ITIP
 */
#घोषणा ITIP_MASK_SSPRXD		 (0x1UL << 0)
#घोषणा ITIP_MASK_SSPFSSIN		 (0x1UL << 1)
#घोषणा ITIP_MASK_SSPCLKIN		 (0x1UL << 2)
#घोषणा ITIP_MASK_RXDMAC		 (0x1UL << 3)
#घोषणा ITIP_MASK_TXDMAC		 (0x1UL << 4)
#घोषणा ITIP_MASK_SSPTXDIN		 (0x1UL << 5)

/*
 * SSP Integration Test output Register - SSP_ITOP
 */
#घोषणा ITOP_MASK_SSPTXD		 (0x1UL << 0)
#घोषणा ITOP_MASK_SSPFSSOUT		 (0x1UL << 1)
#घोषणा ITOP_MASK_SSPCLKOUT		 (0x1UL << 2)
#घोषणा ITOP_MASK_SSPOEn		 (0x1UL << 3)
#घोषणा ITOP_MASK_SSPCTLOEn		 (0x1UL << 4)
#घोषणा ITOP_MASK_RORINTR		 (0x1UL << 5)
#घोषणा ITOP_MASK_RTINTR		 (0x1UL << 6)
#घोषणा ITOP_MASK_RXINTR		 (0x1UL << 7)
#घोषणा ITOP_MASK_TXINTR		 (0x1UL << 8)
#घोषणा ITOP_MASK_INTR			 (0x1UL << 9)
#घोषणा ITOP_MASK_RXDMABREQ		 (0x1UL << 10)
#घोषणा ITOP_MASK_RXDMASREQ		 (0x1UL << 11)
#घोषणा ITOP_MASK_TXDMABREQ		 (0x1UL << 12)
#घोषणा ITOP_MASK_TXDMASREQ		 (0x1UL << 13)

/*
 * SSP Test Data Register - SSP_TDR
 */
#घोषणा TDR_MASK_TESTDATA		(0xFFFFFFFF)

/*
 * Message State
 * we use the spi_message.state (व्योम *) poपूर्णांकer to
 * hold a single state value, that's why all this
 * (व्योम *) casting is करोne here.
 */
#घोषणा STATE_START			((व्योम *) 0)
#घोषणा STATE_RUNNING			((व्योम *) 1)
#घोषणा STATE_DONE			((व्योम *) 2)
#घोषणा STATE_ERROR			((व्योम *) -1)
#घोषणा STATE_TIMEOUT			((व्योम *) -2)

/*
 * SSP State - Whether Enabled or Disabled
 */
#घोषणा SSP_DISABLED			(0)
#घोषणा SSP_ENABLED			(1)

/*
 * SSP DMA State - Whether DMA Enabled or Disabled
 */
#घोषणा SSP_DMA_DISABLED		(0)
#घोषणा SSP_DMA_ENABLED			(1)

/*
 * SSP Clock Defaults
 */
#घोषणा SSP_DEFAULT_CLKRATE 0x2
#घोषणा SSP_DEFAULT_PRESCALE 0x40

/*
 * SSP Clock Parameter ranges
 */
#घोषणा CPSDVR_MIN 0x02
#घोषणा CPSDVR_MAX 0xFE
#घोषणा SCR_MIN 0x00
#घोषणा SCR_MAX 0xFF

/*
 * SSP Interrupt related Macros
 */
#घोषणा DEFAULT_SSP_REG_IMSC  0x0UL
#घोषणा DISABLE_ALL_INTERRUPTS DEFAULT_SSP_REG_IMSC
#घोषणा ENABLE_ALL_INTERRUPTS ( \
	SSP_IMSC_MASK_RORIM | \
	SSP_IMSC_MASK_RTIM | \
	SSP_IMSC_MASK_RXIM | \
	SSP_IMSC_MASK_TXIM \
)

#घोषणा CLEAR_ALL_INTERRUPTS  0x3

#घोषणा SPI_POLLING_TIMEOUT 1000

/*
 * The type of पढ़ोing going on on this chip
 */
क्रमागत ssp_पढ़ोing अणु
	READING_शून्य,
	READING_U8,
	READING_U16,
	READING_U32
पूर्ण;

/*
 * The type of writing going on on this chip
 */
क्रमागत ssp_writing अणु
	WRITING_शून्य,
	WRITING_U8,
	WRITING_U16,
	WRITING_U32
पूर्ण;

/**
 * काष्ठा venकरोr_data - venकरोr-specअगरic config parameters
 * क्रम PL022 derivates
 * @fअगरodepth: depth of FIFOs (both)
 * @max_bpw: maximum number of bits per word
 * @unidir: supports unidirection transfers
 * @extended_cr: 32 bit wide control रेजिस्टर 0 with extra
 * features and extra features in CR1 as found in the ST variants
 * @pl023: supports a subset of the ST extensions called "PL023"
 * @loopback: supports loopback mode
 * @पूर्णांकernal_cs_ctrl: supports chip select control रेजिस्टर
 */
काष्ठा venकरोr_data अणु
	पूर्णांक fअगरodepth;
	पूर्णांक max_bpw;
	bool unidir;
	bool extended_cr;
	bool pl023;
	bool loopback;
	bool पूर्णांकernal_cs_ctrl;
पूर्ण;

/**
 * काष्ठा pl022 - This is the निजी SSP driver data काष्ठाure
 * @adev: AMBA device model hookup
 * @venकरोr: venकरोr data क्रम the IP block
 * @phybase: the physical memory where the SSP device resides
 * @virtbase: the भव memory where the SSP is mapped
 * @clk: outgoing घड़ी "SPICLK" क्रम the SPI bus
 * @master: SPI framework hookup
 * @master_info: controller-specअगरic data from machine setup
 * @pump_transfers: Tasklet used in Interrupt Transfer mode
 * @cur_msg: Poपूर्णांकer to current spi_message being processed
 * @cur_transfer: Poपूर्णांकer to current spi_transfer
 * @cur_chip: poपूर्णांकer to current clients chip(asचिन्हित from controller_state)
 * @next_msg_cs_active: the next message in the queue has been examined
 *  and it was found that it uses the same chip select as the previous
 *  message, so we left it active after the previous transfer, and it's
 *  active alपढ़ोy.
 * @tx: current position in TX buffer to be पढ़ो
 * @tx_end: end position in TX buffer to be पढ़ो
 * @rx: current position in RX buffer to be written
 * @rx_end: end position in RX buffer to be written
 * @पढ़ो: the type of पढ़ो currently going on
 * @ग_लिखो: the type of ग_लिखो currently going on
 * @exp_fअगरo_level: expected FIFO level
 * @rx_lev_trig: receive FIFO watermark level which triggers IRQ
 * @tx_lev_trig: transmit FIFO watermark level which triggers IRQ
 * @dma_rx_channel: optional channel क्रम RX DMA
 * @dma_tx_channel: optional channel क्रम TX DMA
 * @sgt_rx: scattertable क्रम the RX transfer
 * @sgt_tx: scattertable क्रम the TX transfer
 * @dummypage: a dummy page used क्रम driving data on the bus with DMA
 * @dma_running: indicates whether DMA is in operation
 * @cur_cs: current chip select index
 * @cur_gpiod: current chip select GPIO descriptor
 */
काष्ठा pl022 अणु
	काष्ठा amba_device		*adev;
	काष्ठा venकरोr_data		*venकरोr;
	resource_माप_प्रकार			phybase;
	व्योम __iomem			*virtbase;
	काष्ठा clk			*clk;
	काष्ठा spi_master		*master;
	काष्ठा pl022_ssp_controller	*master_info;
	/* Message per-transfer pump */
	काष्ठा tasklet_काष्ठा		pump_transfers;
	काष्ठा spi_message		*cur_msg;
	काष्ठा spi_transfer		*cur_transfer;
	काष्ठा chip_data		*cur_chip;
	bool				next_msg_cs_active;
	व्योम				*tx;
	व्योम				*tx_end;
	व्योम				*rx;
	व्योम				*rx_end;
	क्रमागत ssp_पढ़ोing		पढ़ो;
	क्रमागत ssp_writing		ग_लिखो;
	u32				exp_fअगरo_level;
	क्रमागत ssp_rx_level_trig		rx_lev_trig;
	क्रमागत ssp_tx_level_trig		tx_lev_trig;
	/* DMA settings */
#अगर_घोषित CONFIG_DMA_ENGINE
	काष्ठा dma_chan			*dma_rx_channel;
	काष्ठा dma_chan			*dma_tx_channel;
	काष्ठा sg_table			sgt_rx;
	काष्ठा sg_table			sgt_tx;
	अक्षर				*dummypage;
	bool				dma_running;
#पूर्ण_अगर
	पूर्णांक cur_cs;
	काष्ठा gpio_desc *cur_gpiod;
पूर्ण;

/**
 * काष्ठा chip_data - To मुख्यtain runसमय state of SSP क्रम each client chip
 * @cr0: Value of control रेजिस्टर CR0 of SSP - on later ST variants this
 *       रेजिस्टर is 32 bits wide rather than just 16
 * @cr1: Value of control रेजिस्टर CR1 of SSP
 * @dmacr: Value of DMA control Register of SSP
 * @cpsr: Value of Clock prescale रेजिस्टर
 * @n_bytes: how many bytes(घातer of 2) reqd क्रम a given data width of client
 * @enable_dma: Whether to enable DMA or not
 * @पढ़ो: function ptr to be used to पढ़ो when करोing xfer क्रम this chip
 * @ग_लिखो: function ptr to be used to ग_लिखो when करोing xfer क्रम this chip
 * @xfer_type: polling/पूर्णांकerrupt/DMA
 *
 * Runसमय state of the SSP controller, मुख्यtained per chip,
 * This would be set according to the current message that would be served
 */
काष्ठा chip_data अणु
	u32 cr0;
	u16 cr1;
	u16 dmacr;
	u16 cpsr;
	u8 n_bytes;
	bool enable_dma;
	क्रमागत ssp_पढ़ोing पढ़ो;
	क्रमागत ssp_writing ग_लिखो;
	पूर्णांक xfer_type;
पूर्ण;

/**
 * पूर्णांकernal_cs_control - Control chip select संकेतs via SSP_CSR.
 * @pl022: SSP driver निजी data काष्ठाure
 * @command: select/delect the chip
 *
 * Used on controller with पूर्णांकernal chip select control via SSP_CSR रेजिस्टर
 * (venकरोr extension). Each of the 5 LSB in the रेजिस्टर controls one chip
 * select संकेत.
 */
अटल व्योम पूर्णांकernal_cs_control(काष्ठा pl022 *pl022, u32 command)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोw(SSP_CSR(pl022->virtbase));
	अगर (command == SSP_CHIP_SELECT)
		पंचांगp &= ~BIT(pl022->cur_cs);
	अन्यथा
		पंचांगp |= BIT(pl022->cur_cs);
	ग_लिखोw(पंचांगp, SSP_CSR(pl022->virtbase));
पूर्ण

अटल व्योम pl022_cs_control(काष्ठा pl022 *pl022, u32 command)
अणु
	अगर (pl022->venकरोr->पूर्णांकernal_cs_ctrl)
		पूर्णांकernal_cs_control(pl022, command);
	अन्यथा अगर (pl022->cur_gpiod)
		/*
		 * This needs to be inverted since with GPIOLIB in
		 * control, the inversion will be handled by
		 * GPIOLIB's active low handling. The "command"
		 * passed पूर्णांकo this function will be SSP_CHIP_SELECT
		 * which is क्रमागत:ed to 0, so we need the inverse
		 * (1) to activate chip select.
		 */
		gpiod_set_value(pl022->cur_gpiod, !command);
पूर्ण

/**
 * giveback - current spi_message is over, schedule next message and call
 * callback of this message. Assumes that caller alपढ़ोy
 * set message->status; dma and pio irqs are blocked
 * @pl022: SSP driver निजी data काष्ठाure
 */
अटल व्योम giveback(काष्ठा pl022 *pl022)
अणु
	काष्ठा spi_transfer *last_transfer;
	pl022->next_msg_cs_active = false;

	last_transfer = list_last_entry(&pl022->cur_msg->transfers,
					काष्ठा spi_transfer, transfer_list);

	/* Delay अगर requested beक्रमe any change in chip select */
	/*
	 * FIXME: This runs in पूर्णांकerrupt context.
	 * Is this really smart?
	 */
	spi_transfer_delay_exec(last_transfer);

	अगर (!last_transfer->cs_change) अणु
		काष्ठा spi_message *next_msg;

		/*
		 * cs_change was not set. We can keep the chip select
		 * enabled अगर there is message in the queue and it is
		 * क्रम the same spi device.
		 *
		 * We cannot postpone this until pump_messages, because
		 * after calling msg->complete (below) the driver that
		 * sent the current message could be unloaded, which
		 * could invalidate the cs_control() callback...
		 */
		/* get a poपूर्णांकer to the next message, अगर any */
		next_msg = spi_get_next_queued_message(pl022->master);

		/*
		 * see अगर the next and current messages poपूर्णांक
		 * to the same spi device.
		 */
		अगर (next_msg && next_msg->spi != pl022->cur_msg->spi)
			next_msg = शून्य;
		अगर (!next_msg || pl022->cur_msg->state == STATE_ERROR)
			pl022_cs_control(pl022, SSP_CHIP_DESELECT);
		अन्यथा
			pl022->next_msg_cs_active = true;

	पूर्ण

	pl022->cur_msg = शून्य;
	pl022->cur_transfer = शून्य;
	pl022->cur_chip = शून्य;

	/* disable the SPI/SSP operation */
	ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) &
		(~SSP_CR1_MASK_SSE)), SSP_CR1(pl022->virtbase));

	spi_finalize_current_message(pl022->master);
पूर्ण

/**
 * flush - flush the FIFO to reach a clean state
 * @pl022: SSP driver निजी data काष्ठाure
 */
अटल पूर्णांक flush(काष्ठा pl022 *pl022)
अणु
	अचिन्हित दीर्घ limit = loops_per_jअगरfy << 1;

	dev_dbg(&pl022->adev->dev, "flush\n");
	करो अणु
		जबतक (पढ़ोw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RNE)
			पढ़ोw(SSP_DR(pl022->virtbase));
	पूर्ण जबतक ((पढ़ोw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_BSY) && limit--);

	pl022->exp_fअगरo_level = 0;

	वापस limit;
पूर्ण

/**
 * restore_state - Load configuration of current chip
 * @pl022: SSP driver निजी data काष्ठाure
 */
अटल व्योम restore_state(काष्ठा pl022 *pl022)
अणु
	काष्ठा chip_data *chip = pl022->cur_chip;

	अगर (pl022->venकरोr->extended_cr)
		ग_लिखोl(chip->cr0, SSP_CR0(pl022->virtbase));
	अन्यथा
		ग_लिखोw(chip->cr0, SSP_CR0(pl022->virtbase));
	ग_लिखोw(chip->cr1, SSP_CR1(pl022->virtbase));
	ग_लिखोw(chip->dmacr, SSP_DMACR(pl022->virtbase));
	ग_लिखोw(chip->cpsr, SSP_CPSR(pl022->virtbase));
	ग_लिखोw(DISABLE_ALL_INTERRUPTS, SSP_IMSC(pl022->virtbase));
	ग_लिखोw(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
पूर्ण

/*
 * Default SSP Register Values
 */
#घोषणा DEFAULT_SSP_REG_CR0 ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CR0_MASK_DSS, 0)	| \
	GEN_MASK_BITS(SSP_INTERFACE_MOTOROLA_SPI, SSP_CR0_MASK_FRF, 4) | \
	GEN_MASK_BITS(SSP_CLK_POL_IDLE_LOW, SSP_CR0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CLK_SECOND_EDGE, SSP_CR0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAULT_CLKRATE, SSP_CR0_MASK_SCR, 8) \
)

/* ST versions have slightly dअगरferent bit layout */
#घोषणा DEFAULT_SSP_REG_CR0_ST ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CR0_MASK_DSS_ST, 0)	| \
	GEN_MASK_BITS(SSP_MICROWIRE_CHANNEL_FULL_DUPLEX, SSP_CR0_MASK_HALFDUP_ST, 5) | \
	GEN_MASK_BITS(SSP_CLK_POL_IDLE_LOW, SSP_CR0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CLK_SECOND_EDGE, SSP_CR0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAULT_CLKRATE, SSP_CR0_MASK_SCR, 8) | \
	GEN_MASK_BITS(SSP_BITS_8, SSP_CR0_MASK_CSS_ST, 16)	| \
	GEN_MASK_BITS(SSP_INTERFACE_MOTOROLA_SPI, SSP_CR0_MASK_FRF_ST, 21) \
)

/* The PL023 version is slightly dअगरferent again */
#घोषणा DEFAULT_SSP_REG_CR0_ST_PL023 ( \
	GEN_MASK_BITS(SSP_DATA_BITS_12, SSP_CR0_MASK_DSS_ST, 0)	| \
	GEN_MASK_BITS(SSP_CLK_POL_IDLE_LOW, SSP_CR0_MASK_SPO, 6) | \
	GEN_MASK_BITS(SSP_CLK_SECOND_EDGE, SSP_CR0_MASK_SPH, 7) | \
	GEN_MASK_BITS(SSP_DEFAULT_CLKRATE, SSP_CR0_MASK_SCR, 8) \
)

#घोषणा DEFAULT_SSP_REG_CR1 ( \
	GEN_MASK_BITS(LOOPBACK_DISABLED, SSP_CR1_MASK_LBM, 0) | \
	GEN_MASK_BITS(SSP_DISABLED, SSP_CR1_MASK_SSE, 1) | \
	GEN_MASK_BITS(SSP_MASTER, SSP_CR1_MASK_MS, 2) | \
	GEN_MASK_BITS(DO_NOT_DRIVE_TX, SSP_CR1_MASK_SOD, 3) \
)

/* ST versions extend this रेजिस्टर to use all 16 bits */
#घोषणा DEFAULT_SSP_REG_CR1_ST ( \
	DEFAULT_SSP_REG_CR1 | \
	GEN_MASK_BITS(SSP_RX_MSB, SSP_CR1_MASK_RENDN_ST, 4) | \
	GEN_MASK_BITS(SSP_TX_MSB, SSP_CR1_MASK_TENDN_ST, 5) | \
	GEN_MASK_BITS(SSP_MWIRE_WAIT_ZERO, SSP_CR1_MASK_MWAIT_ST, 6) |\
	GEN_MASK_BITS(SSP_RX_1_OR_MORE_ELEM, SSP_CR1_MASK_RXIFLSEL_ST, 7) | \
	GEN_MASK_BITS(SSP_TX_1_OR_MORE_EMPTY_LOC, SSP_CR1_MASK_TXIFLSEL_ST, 10) \
)

/*
 * The PL023 variant has further dअगरferences: no loopback mode, no microwire
 * support, and a new घड़ी feedback delay setting.
 */
#घोषणा DEFAULT_SSP_REG_CR1_ST_PL023 ( \
	GEN_MASK_BITS(SSP_DISABLED, SSP_CR1_MASK_SSE, 1) | \
	GEN_MASK_BITS(SSP_MASTER, SSP_CR1_MASK_MS, 2) | \
	GEN_MASK_BITS(DO_NOT_DRIVE_TX, SSP_CR1_MASK_SOD, 3) | \
	GEN_MASK_BITS(SSP_RX_MSB, SSP_CR1_MASK_RENDN_ST, 4) | \
	GEN_MASK_BITS(SSP_TX_MSB, SSP_CR1_MASK_TENDN_ST, 5) | \
	GEN_MASK_BITS(SSP_RX_1_OR_MORE_ELEM, SSP_CR1_MASK_RXIFLSEL_ST, 7) | \
	GEN_MASK_BITS(SSP_TX_1_OR_MORE_EMPTY_LOC, SSP_CR1_MASK_TXIFLSEL_ST, 10) | \
	GEN_MASK_BITS(SSP_FEEDBACK_CLK_DELAY_NONE, SSP_CR1_MASK_FBCLKDEL_ST, 13) \
)

#घोषणा DEFAULT_SSP_REG_CPSR ( \
	GEN_MASK_BITS(SSP_DEFAULT_PRESCALE, SSP_CPSR_MASK_CPSDVSR, 0) \
)

#घोषणा DEFAULT_SSP_REG_DMACR (\
	GEN_MASK_BITS(SSP_DMA_DISABLED, SSP_DMACR_MASK_RXDMAE, 0) | \
	GEN_MASK_BITS(SSP_DMA_DISABLED, SSP_DMACR_MASK_TXDMAE, 1) \
)

/**
 * load_ssp_शेष_config - Load शेष configuration क्रम SSP
 * @pl022: SSP driver निजी data काष्ठाure
 */
अटल व्योम load_ssp_शेष_config(काष्ठा pl022 *pl022)
अणु
	अगर (pl022->venकरोr->pl023) अणु
		ग_लिखोl(DEFAULT_SSP_REG_CR0_ST_PL023, SSP_CR0(pl022->virtbase));
		ग_लिखोw(DEFAULT_SSP_REG_CR1_ST_PL023, SSP_CR1(pl022->virtbase));
	पूर्ण अन्यथा अगर (pl022->venकरोr->extended_cr) अणु
		ग_लिखोl(DEFAULT_SSP_REG_CR0_ST, SSP_CR0(pl022->virtbase));
		ग_लिखोw(DEFAULT_SSP_REG_CR1_ST, SSP_CR1(pl022->virtbase));
	पूर्ण अन्यथा अणु
		ग_लिखोw(DEFAULT_SSP_REG_CR0, SSP_CR0(pl022->virtbase));
		ग_लिखोw(DEFAULT_SSP_REG_CR1, SSP_CR1(pl022->virtbase));
	पूर्ण
	ग_लिखोw(DEFAULT_SSP_REG_DMACR, SSP_DMACR(pl022->virtbase));
	ग_लिखोw(DEFAULT_SSP_REG_CPSR, SSP_CPSR(pl022->virtbase));
	ग_लिखोw(DISABLE_ALL_INTERRUPTS, SSP_IMSC(pl022->virtbase));
	ग_लिखोw(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
पूर्ण

/*
 * This will ग_लिखो to TX and पढ़ो from RX according to the parameters
 * set in pl022.
 */
अटल व्योम पढ़ोग_लिखोr(काष्ठा pl022 *pl022)
अणु

	/*
	 * The FIFO depth is dअगरferent between primecell variants.
	 * I believe filling in too much in the FIFO might cause
	 * errons in 8bit wide transfers on ARM variants (just 8 words
	 * FIFO, means only 8x8 = 64 bits in FIFO) at least.
	 *
	 * To prevent this issue, the TX FIFO is only filled to the
	 * unused RX FIFO fill length, regardless of what the TX
	 * FIFO status flag indicates.
	 */
	dev_dbg(&pl022->adev->dev,
		"%s, rx: %p, rxend: %p, tx: %p, txend: %p\n",
		__func__, pl022->rx, pl022->rx_end, pl022->tx, pl022->tx_end);

	/* Read as much as you can */
	जबतक ((पढ़ोw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RNE)
	       && (pl022->rx < pl022->rx_end)) अणु
		चयन (pl022->पढ़ो) अणु
		हाल READING_शून्य:
			पढ़ोw(SSP_DR(pl022->virtbase));
			अवरोध;
		हाल READING_U8:
			*(u8 *) (pl022->rx) =
				पढ़ोw(SSP_DR(pl022->virtbase)) & 0xFFU;
			अवरोध;
		हाल READING_U16:
			*(u16 *) (pl022->rx) =
				(u16) पढ़ोw(SSP_DR(pl022->virtbase));
			अवरोध;
		हाल READING_U32:
			*(u32 *) (pl022->rx) =
				पढ़ोl(SSP_DR(pl022->virtbase));
			अवरोध;
		पूर्ण
		pl022->rx += (pl022->cur_chip->n_bytes);
		pl022->exp_fअगरo_level--;
	पूर्ण
	/*
	 * Write as much as possible up to the RX FIFO size
	 */
	जबतक ((pl022->exp_fअगरo_level < pl022->venकरोr->fअगरodepth)
	       && (pl022->tx < pl022->tx_end)) अणु
		चयन (pl022->ग_लिखो) अणु
		हाल WRITING_शून्य:
			ग_लिखोw(0x0, SSP_DR(pl022->virtbase));
			अवरोध;
		हाल WRITING_U8:
			ग_लिखोw(*(u8 *) (pl022->tx), SSP_DR(pl022->virtbase));
			अवरोध;
		हाल WRITING_U16:
			ग_लिखोw((*(u16 *) (pl022->tx)), SSP_DR(pl022->virtbase));
			अवरोध;
		हाल WRITING_U32:
			ग_लिखोl(*(u32 *) (pl022->tx), SSP_DR(pl022->virtbase));
			अवरोध;
		पूर्ण
		pl022->tx += (pl022->cur_chip->n_bytes);
		pl022->exp_fअगरo_level++;
		/*
		 * This inner पढ़ोer takes care of things appearing in the RX
		 * FIFO as we're transmitting. This will happen a lot since the
		 * घड़ी starts running when you put things पूर्णांकo the TX FIFO,
		 * and then things are continuously घड़ीed पूर्णांकo the RX FIFO.
		 */
		जबतक ((पढ़ोw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RNE)
		       && (pl022->rx < pl022->rx_end)) अणु
			चयन (pl022->पढ़ो) अणु
			हाल READING_शून्य:
				पढ़ोw(SSP_DR(pl022->virtbase));
				अवरोध;
			हाल READING_U8:
				*(u8 *) (pl022->rx) =
					पढ़ोw(SSP_DR(pl022->virtbase)) & 0xFFU;
				अवरोध;
			हाल READING_U16:
				*(u16 *) (pl022->rx) =
					(u16) पढ़ोw(SSP_DR(pl022->virtbase));
				अवरोध;
			हाल READING_U32:
				*(u32 *) (pl022->rx) =
					पढ़ोl(SSP_DR(pl022->virtbase));
				अवरोध;
			पूर्ण
			pl022->rx += (pl022->cur_chip->n_bytes);
			pl022->exp_fअगरo_level--;
		पूर्ण
	पूर्ण
	/*
	 * When we निकास here the TX FIFO should be full and the RX FIFO
	 * should be empty
	 */
पूर्ण

/**
 * next_transfer - Move to the Next transfer in the current spi message
 * @pl022: SSP driver निजी data काष्ठाure
 *
 * This function moves though the linked list of spi transfers in the
 * current spi message and वापसs with the state of current spi
 * message i.e whether its last transfer is करोne(STATE_DONE) or
 * Next transfer is पढ़ोy(STATE_RUNNING)
 */
अटल व्योम *next_transfer(काष्ठा pl022 *pl022)
अणु
	काष्ठा spi_message *msg = pl022->cur_msg;
	काष्ठा spi_transfer *trans = pl022->cur_transfer;

	/* Move to next transfer */
	अगर (trans->transfer_list.next != &msg->transfers) अणु
		pl022->cur_transfer =
		    list_entry(trans->transfer_list.next,
			       काष्ठा spi_transfer, transfer_list);
		वापस STATE_RUNNING;
	पूर्ण
	वापस STATE_DONE;
पूर्ण

/*
 * This DMA functionality is only compiled in अगर we have
 * access to the generic DMA devices/DMA engine.
 */
#अगर_घोषित CONFIG_DMA_ENGINE
अटल व्योम unmap_मुक्त_dma_scatter(काष्ठा pl022 *pl022)
अणु
	/* Unmap and मुक्त the SG tables */
	dma_unmap_sg(pl022->dma_tx_channel->device->dev, pl022->sgt_tx.sgl,
		     pl022->sgt_tx.nents, DMA_TO_DEVICE);
	dma_unmap_sg(pl022->dma_rx_channel->device->dev, pl022->sgt_rx.sgl,
		     pl022->sgt_rx.nents, DMA_FROM_DEVICE);
	sg_मुक्त_table(&pl022->sgt_rx);
	sg_मुक्त_table(&pl022->sgt_tx);
पूर्ण

अटल व्योम dma_callback(व्योम *data)
अणु
	काष्ठा pl022 *pl022 = data;
	काष्ठा spi_message *msg = pl022->cur_msg;

	BUG_ON(!pl022->sgt_rx.sgl);

#अगर_घोषित VERBOSE_DEBUG
	/*
	 * Optionally dump out buffers to inspect contents, this is
	 * good अगर you want to convince yourself that the loopback
	 * पढ़ो/ग_लिखो contents are the same, when aकरोpting to a new
	 * DMA engine.
	 */
	अणु
		काष्ठा scatterlist *sg;
		अचिन्हित पूर्णांक i;

		dma_sync_sg_क्रम_cpu(&pl022->adev->dev,
				    pl022->sgt_rx.sgl,
				    pl022->sgt_rx.nents,
				    DMA_FROM_DEVICE);

		क्रम_each_sg(pl022->sgt_rx.sgl, sg, pl022->sgt_rx.nents, i) अणु
			dev_dbg(&pl022->adev->dev, "SPI RX SG ENTRY: %d", i);
			prपूर्णांक_hex_dump(KERN_ERR, "SPI RX: ",
				       DUMP_PREFIX_OFFSET,
				       16,
				       1,
				       sg_virt(sg),
				       sg_dma_len(sg),
				       1);
		पूर्ण
		क्रम_each_sg(pl022->sgt_tx.sgl, sg, pl022->sgt_tx.nents, i) अणु
			dev_dbg(&pl022->adev->dev, "SPI TX SG ENTRY: %d", i);
			prपूर्णांक_hex_dump(KERN_ERR, "SPI TX: ",
				       DUMP_PREFIX_OFFSET,
				       16,
				       1,
				       sg_virt(sg),
				       sg_dma_len(sg),
				       1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	unmap_मुक्त_dma_scatter(pl022);

	/* Update total bytes transferred */
	msg->actual_length += pl022->cur_transfer->len;
	/* Move to next transfer */
	msg->state = next_transfer(pl022);
	अगर (msg->state != STATE_DONE && pl022->cur_transfer->cs_change)
		pl022_cs_control(pl022, SSP_CHIP_DESELECT);
	tasklet_schedule(&pl022->pump_transfers);
पूर्ण

अटल व्योम setup_dma_scatter(काष्ठा pl022 *pl022,
			      व्योम *buffer,
			      अचिन्हित पूर्णांक length,
			      काष्ठा sg_table *sgtab)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक bytesleft = length;
	व्योम *bufp = buffer;
	पूर्णांक mapbytes;
	पूर्णांक i;

	अगर (buffer) अणु
		क्रम_each_sg(sgtab->sgl, sg, sgtab->nents, i) अणु
			/*
			 * If there are less bytes left than what fits
			 * in the current page (plus page alignment offset)
			 * we just feed in this, अन्यथा we stuff in as much
			 * as we can.
			 */
			अगर (bytesleft < (PAGE_SIZE - offset_in_page(bufp)))
				mapbytes = bytesleft;
			अन्यथा
				mapbytes = PAGE_SIZE - offset_in_page(bufp);
			sg_set_page(sg, virt_to_page(bufp),
				    mapbytes, offset_in_page(bufp));
			bufp += mapbytes;
			bytesleft -= mapbytes;
			dev_dbg(&pl022->adev->dev,
				"set RX/TX target page @ %p, %d bytes, %d left\n",
				bufp, mapbytes, bytesleft);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Map the dummy buffer on every page */
		क्रम_each_sg(sgtab->sgl, sg, sgtab->nents, i) अणु
			अगर (bytesleft < PAGE_SIZE)
				mapbytes = bytesleft;
			अन्यथा
				mapbytes = PAGE_SIZE;
			sg_set_page(sg, virt_to_page(pl022->dummypage),
				    mapbytes, 0);
			bytesleft -= mapbytes;
			dev_dbg(&pl022->adev->dev,
				"set RX/TX to dummy page %d bytes, %d left\n",
				mapbytes, bytesleft);

		पूर्ण
	पूर्ण
	BUG_ON(bytesleft);
पूर्ण

/**
 * configure_dma - configures the channels क्रम the next transfer
 * @pl022: SSP driver's निजी data काष्ठाure
 */
अटल पूर्णांक configure_dma(काष्ठा pl022 *pl022)
अणु
	काष्ठा dma_slave_config rx_conf = अणु
		.src_addr = SSP_DR(pl022->phybase),
		.direction = DMA_DEV_TO_MEM,
		.device_fc = false,
	पूर्ण;
	काष्ठा dma_slave_config tx_conf = अणु
		.dst_addr = SSP_DR(pl022->phybase),
		.direction = DMA_MEM_TO_DEV,
		.device_fc = false,
	पूर्ण;
	अचिन्हित पूर्णांक pages;
	पूर्णांक ret;
	पूर्णांक rx_sglen, tx_sglen;
	काष्ठा dma_chan *rxchan = pl022->dma_rx_channel;
	काष्ठा dma_chan *txchan = pl022->dma_tx_channel;
	काष्ठा dma_async_tx_descriptor *rxdesc;
	काष्ठा dma_async_tx_descriptor *txdesc;

	/* Check that the channels are available */
	अगर (!rxchan || !txchan)
		वापस -ENODEV;

	/*
	 * If supplied, the DMA burstsize should equal the FIFO trigger level.
	 * Notice that the DMA engine uses one-to-one mapping. Since we can
	 * not trigger on 2 elements this needs explicit mapping rather than
	 * calculation.
	 */
	चयन (pl022->rx_lev_trig) अणु
	हाल SSP_RX_1_OR_MORE_ELEM:
		rx_conf.src_maxburst = 1;
		अवरोध;
	हाल SSP_RX_4_OR_MORE_ELEM:
		rx_conf.src_maxburst = 4;
		अवरोध;
	हाल SSP_RX_8_OR_MORE_ELEM:
		rx_conf.src_maxburst = 8;
		अवरोध;
	हाल SSP_RX_16_OR_MORE_ELEM:
		rx_conf.src_maxburst = 16;
		अवरोध;
	हाल SSP_RX_32_OR_MORE_ELEM:
		rx_conf.src_maxburst = 32;
		अवरोध;
	शेष:
		rx_conf.src_maxburst = pl022->venकरोr->fअगरodepth >> 1;
		अवरोध;
	पूर्ण

	चयन (pl022->tx_lev_trig) अणु
	हाल SSP_TX_1_OR_MORE_EMPTY_LOC:
		tx_conf.dst_maxburst = 1;
		अवरोध;
	हाल SSP_TX_4_OR_MORE_EMPTY_LOC:
		tx_conf.dst_maxburst = 4;
		अवरोध;
	हाल SSP_TX_8_OR_MORE_EMPTY_LOC:
		tx_conf.dst_maxburst = 8;
		अवरोध;
	हाल SSP_TX_16_OR_MORE_EMPTY_LOC:
		tx_conf.dst_maxburst = 16;
		अवरोध;
	हाल SSP_TX_32_OR_MORE_EMPTY_LOC:
		tx_conf.dst_maxburst = 32;
		अवरोध;
	शेष:
		tx_conf.dst_maxburst = pl022->venकरोr->fअगरodepth >> 1;
		अवरोध;
	पूर्ण

	चयन (pl022->पढ़ो) अणु
	हाल READING_शून्य:
		/* Use the same as क्रम writing */
		rx_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;
		अवरोध;
	हाल READING_U8:
		rx_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	हाल READING_U16:
		rx_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल READING_U32:
		rx_conf.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	पूर्ण

	चयन (pl022->ग_लिखो) अणु
	हाल WRITING_शून्य:
		/* Use the same as क्रम पढ़ोing */
		tx_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_UNDEFINED;
		अवरोध;
	हाल WRITING_U8:
		tx_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	हाल WRITING_U16:
		tx_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल WRITING_U32:
		tx_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	पूर्ण

	/* SPI pecularity: we need to पढ़ो and ग_लिखो the same width */
	अगर (rx_conf.src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
		rx_conf.src_addr_width = tx_conf.dst_addr_width;
	अगर (tx_conf.dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
		tx_conf.dst_addr_width = rx_conf.src_addr_width;
	BUG_ON(rx_conf.src_addr_width != tx_conf.dst_addr_width);

	dmaengine_slave_config(rxchan, &rx_conf);
	dmaengine_slave_config(txchan, &tx_conf);

	/* Create sglists क्रम the transfers */
	pages = DIV_ROUND_UP(pl022->cur_transfer->len, PAGE_SIZE);
	dev_dbg(&pl022->adev->dev, "using %d pages for transfer\n", pages);

	ret = sg_alloc_table(&pl022->sgt_rx, pages, GFP_ATOMIC);
	अगर (ret)
		जाओ err_alloc_rx_sg;

	ret = sg_alloc_table(&pl022->sgt_tx, pages, GFP_ATOMIC);
	अगर (ret)
		जाओ err_alloc_tx_sg;

	/* Fill in the scatterlists क्रम the RX+TX buffers */
	setup_dma_scatter(pl022, pl022->rx,
			  pl022->cur_transfer->len, &pl022->sgt_rx);
	setup_dma_scatter(pl022, pl022->tx,
			  pl022->cur_transfer->len, &pl022->sgt_tx);

	/* Map DMA buffers */
	rx_sglen = dma_map_sg(rxchan->device->dev, pl022->sgt_rx.sgl,
			   pl022->sgt_rx.nents, DMA_FROM_DEVICE);
	अगर (!rx_sglen)
		जाओ err_rx_sgmap;

	tx_sglen = dma_map_sg(txchan->device->dev, pl022->sgt_tx.sgl,
			   pl022->sgt_tx.nents, DMA_TO_DEVICE);
	अगर (!tx_sglen)
		जाओ err_tx_sgmap;

	/* Send both scatterlists */
	rxdesc = dmaengine_prep_slave_sg(rxchan,
				      pl022->sgt_rx.sgl,
				      rx_sglen,
				      DMA_DEV_TO_MEM,
				      DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!rxdesc)
		जाओ err_rxdesc;

	txdesc = dmaengine_prep_slave_sg(txchan,
				      pl022->sgt_tx.sgl,
				      tx_sglen,
				      DMA_MEM_TO_DEV,
				      DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!txdesc)
		जाओ err_txdesc;

	/* Put the callback on the RX transfer only, that should finish last */
	rxdesc->callback = dma_callback;
	rxdesc->callback_param = pl022;

	/* Submit and fire RX and TX with TX last so we're पढ़ोy to पढ़ो! */
	dmaengine_submit(rxdesc);
	dmaengine_submit(txdesc);
	dma_async_issue_pending(rxchan);
	dma_async_issue_pending(txchan);
	pl022->dma_running = true;

	वापस 0;

err_txdesc:
	dmaengine_terminate_all(txchan);
err_rxdesc:
	dmaengine_terminate_all(rxchan);
	dma_unmap_sg(txchan->device->dev, pl022->sgt_tx.sgl,
		     pl022->sgt_tx.nents, DMA_TO_DEVICE);
err_tx_sgmap:
	dma_unmap_sg(rxchan->device->dev, pl022->sgt_rx.sgl,
		     pl022->sgt_rx.nents, DMA_FROM_DEVICE);
err_rx_sgmap:
	sg_मुक्त_table(&pl022->sgt_tx);
err_alloc_tx_sg:
	sg_मुक्त_table(&pl022->sgt_rx);
err_alloc_rx_sg:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pl022_dma_probe(काष्ठा pl022 *pl022)
अणु
	dma_cap_mask_t mask;

	/* Try to acquire a generic DMA engine slave channel */
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	/*
	 * We need both RX and TX channels to करो DMA, अन्यथा करो none
	 * of them.
	 */
	pl022->dma_rx_channel = dma_request_channel(mask,
					    pl022->master_info->dma_filter,
					    pl022->master_info->dma_rx_param);
	अगर (!pl022->dma_rx_channel) अणु
		dev_dbg(&pl022->adev->dev, "no RX DMA channel!\n");
		जाओ err_no_rxchan;
	पूर्ण

	pl022->dma_tx_channel = dma_request_channel(mask,
					    pl022->master_info->dma_filter,
					    pl022->master_info->dma_tx_param);
	अगर (!pl022->dma_tx_channel) अणु
		dev_dbg(&pl022->adev->dev, "no TX DMA channel!\n");
		जाओ err_no_txchan;
	पूर्ण

	pl022->dummypage = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!pl022->dummypage)
		जाओ err_no_dummypage;

	dev_info(&pl022->adev->dev, "setup for DMA on RX %s, TX %s\n",
		 dma_chan_name(pl022->dma_rx_channel),
		 dma_chan_name(pl022->dma_tx_channel));

	वापस 0;

err_no_dummypage:
	dma_release_channel(pl022->dma_tx_channel);
err_no_txchan:
	dma_release_channel(pl022->dma_rx_channel);
	pl022->dma_rx_channel = शून्य;
err_no_rxchan:
	dev_err(&pl022->adev->dev,
			"Failed to work in dma mode, work without dma!\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक pl022_dma_स्वतःprobe(काष्ठा pl022 *pl022)
अणु
	काष्ठा device *dev = &pl022->adev->dev;
	काष्ठा dma_chan *chan;
	पूर्णांक err;

	/* स्वतःmatically configure DMA channels from platक्रमm, normally using DT */
	chan = dma_request_chan(dev, "rx");
	अगर (IS_ERR(chan)) अणु
		err = PTR_ERR(chan);
		जाओ err_no_rxchan;
	पूर्ण

	pl022->dma_rx_channel = chan;

	chan = dma_request_chan(dev, "tx");
	अगर (IS_ERR(chan)) अणु
		err = PTR_ERR(chan);
		जाओ err_no_txchan;
	पूर्ण

	pl022->dma_tx_channel = chan;

	pl022->dummypage = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!pl022->dummypage) अणु
		err = -ENOMEM;
		जाओ err_no_dummypage;
	पूर्ण

	वापस 0;

err_no_dummypage:
	dma_release_channel(pl022->dma_tx_channel);
	pl022->dma_tx_channel = शून्य;
err_no_txchan:
	dma_release_channel(pl022->dma_rx_channel);
	pl022->dma_rx_channel = शून्य;
err_no_rxchan:
	वापस err;
पूर्ण

अटल व्योम terminate_dma(काष्ठा pl022 *pl022)
अणु
	काष्ठा dma_chan *rxchan = pl022->dma_rx_channel;
	काष्ठा dma_chan *txchan = pl022->dma_tx_channel;

	dmaengine_terminate_all(rxchan);
	dmaengine_terminate_all(txchan);
	unmap_मुक्त_dma_scatter(pl022);
	pl022->dma_running = false;
पूर्ण

अटल व्योम pl022_dma_हटाओ(काष्ठा pl022 *pl022)
अणु
	अगर (pl022->dma_running)
		terminate_dma(pl022);
	अगर (pl022->dma_tx_channel)
		dma_release_channel(pl022->dma_tx_channel);
	अगर (pl022->dma_rx_channel)
		dma_release_channel(pl022->dma_rx_channel);
	kमुक्त(pl022->dummypage);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक configure_dma(काष्ठा pl022 *pl022)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक pl022_dma_स्वतःprobe(काष्ठा pl022 *pl022)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pl022_dma_probe(काष्ठा pl022 *pl022)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pl022_dma_हटाओ(काष्ठा pl022 *pl022)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * pl022_पूर्णांकerrupt_handler - Interrupt handler क्रम SSP controller
 * @irq: IRQ number
 * @dev_id: Local device data
 *
 * This function handles पूर्णांकerrupts generated क्रम an पूर्णांकerrupt based transfer.
 * If a receive overrun (ROR) पूर्णांकerrupt is there then we disable SSP, flag the
 * current message's state as STATE_ERROR and schedule the tasklet
 * pump_transfers which will करो the postprocessing of the current message by
 * calling giveback(). Otherwise it पढ़ोs data from RX FIFO till there is no
 * more data, and ग_लिखोs data in TX FIFO till it is not full. If we complete
 * the transfer we move to the next transfer and schedule the tasklet.
 */
अटल irqवापस_t pl022_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pl022 *pl022 = dev_id;
	काष्ठा spi_message *msg = pl022->cur_msg;
	u16 irq_status = 0;

	अगर (unlikely(!msg)) अणु
		dev_err(&pl022->adev->dev,
			"bad message state in interrupt handler");
		/* Never fail */
		वापस IRQ_HANDLED;
	पूर्ण

	/* Read the Interrupt Status Register */
	irq_status = पढ़ोw(SSP_MIS(pl022->virtbase));

	अगर (unlikely(!irq_status))
		वापस IRQ_NONE;

	/*
	 * This handles the FIFO पूर्णांकerrupts, the समयout
	 * पूर्णांकerrupts are flatly ignored, they cannot be
	 * trusted.
	 */
	अगर (unlikely(irq_status & SSP_MIS_MASK_RORMIS)) अणु
		/*
		 * Overrun पूर्णांकerrupt - bail out since our Data has been
		 * corrupted
		 */
		dev_err(&pl022->adev->dev, "FIFO overrun\n");
		अगर (पढ़ोw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RFF)
			dev_err(&pl022->adev->dev,
				"RXFIFO is full\n");

		/*
		 * Disable and clear पूर्णांकerrupts, disable SSP,
		 * mark message with bad status so it can be
		 * retried.
		 */
		ग_लिखोw(DISABLE_ALL_INTERRUPTS,
		       SSP_IMSC(pl022->virtbase));
		ग_लिखोw(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
		ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) &
			(~SSP_CR1_MASK_SSE)), SSP_CR1(pl022->virtbase));
		msg->state = STATE_ERROR;

		/* Schedule message queue handler */
		tasklet_schedule(&pl022->pump_transfers);
		वापस IRQ_HANDLED;
	पूर्ण

	पढ़ोग_लिखोr(pl022);

	अगर (pl022->tx == pl022->tx_end) अणु
		/* Disable Transmit पूर्णांकerrupt, enable receive पूर्णांकerrupt */
		ग_लिखोw((पढ़ोw(SSP_IMSC(pl022->virtbase)) &
		       ~SSP_IMSC_MASK_TXIM) | SSP_IMSC_MASK_RXIM,
		       SSP_IMSC(pl022->virtbase));
	पूर्ण

	/*
	 * Since all transactions must ग_लिखो as much as shall be पढ़ो,
	 * we can conclude the entire transaction once RX is complete.
	 * At this poपूर्णांक, all TX will always be finished.
	 */
	अगर (pl022->rx >= pl022->rx_end) अणु
		ग_लिखोw(DISABLE_ALL_INTERRUPTS,
		       SSP_IMSC(pl022->virtbase));
		ग_लिखोw(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
		अगर (unlikely(pl022->rx > pl022->rx_end)) अणु
			dev_warn(&pl022->adev->dev, "read %u surplus "
				 "bytes (did you request an odd "
				 "number of bytes on a 16bit bus?)\n",
				 (u32) (pl022->rx - pl022->rx_end));
		पूर्ण
		/* Update total bytes transferred */
		msg->actual_length += pl022->cur_transfer->len;
		/* Move to next transfer */
		msg->state = next_transfer(pl022);
		अगर (msg->state != STATE_DONE && pl022->cur_transfer->cs_change)
			pl022_cs_control(pl022, SSP_CHIP_DESELECT);
		tasklet_schedule(&pl022->pump_transfers);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * This sets up the poपूर्णांकers to memory क्रम the next message to
 * send out on the SPI bus.
 */
अटल पूर्णांक set_up_next_transfer(काष्ठा pl022 *pl022,
				काष्ठा spi_transfer *transfer)
अणु
	पूर्णांक residue;

	/* Sanity check the message क्रम this bus width */
	residue = pl022->cur_transfer->len % pl022->cur_chip->n_bytes;
	अगर (unlikely(residue != 0)) अणु
		dev_err(&pl022->adev->dev,
			"message of %u bytes to transmit but the current "
			"chip bus has a data width of %u bytes!\n",
			pl022->cur_transfer->len,
			pl022->cur_chip->n_bytes);
		dev_err(&pl022->adev->dev, "skipping this message\n");
		वापस -EIO;
	पूर्ण
	pl022->tx = (व्योम *)transfer->tx_buf;
	pl022->tx_end = pl022->tx + pl022->cur_transfer->len;
	pl022->rx = (व्योम *)transfer->rx_buf;
	pl022->rx_end = pl022->rx + pl022->cur_transfer->len;
	pl022->ग_लिखो =
	    pl022->tx ? pl022->cur_chip->ग_लिखो : WRITING_शून्य;
	pl022->पढ़ो = pl022->rx ? pl022->cur_chip->पढ़ो : READING_शून्य;
	वापस 0;
पूर्ण

/**
 * pump_transfers - Tasklet function which schedules next transfer
 * when running in पूर्णांकerrupt or DMA transfer mode.
 * @data: SSP driver निजी data काष्ठाure
 *
 */
अटल व्योम pump_transfers(अचिन्हित दीर्घ data)
अणु
	काष्ठा pl022 *pl022 = (काष्ठा pl022 *) data;
	काष्ठा spi_message *message = शून्य;
	काष्ठा spi_transfer *transfer = शून्य;
	काष्ठा spi_transfer *previous = शून्य;

	/* Get current state inक्रमmation */
	message = pl022->cur_msg;
	transfer = pl022->cur_transfer;

	/* Handle क्रम पात */
	अगर (message->state == STATE_ERROR) अणु
		message->status = -EIO;
		giveback(pl022);
		वापस;
	पूर्ण

	/* Handle end of message */
	अगर (message->state == STATE_DONE) अणु
		message->status = 0;
		giveback(pl022);
		वापस;
	पूर्ण

	/* Delay अगर requested at end of transfer beक्रमe CS change */
	अगर (message->state == STATE_RUNNING) अणु
		previous = list_entry(transfer->transfer_list.prev,
					काष्ठा spi_transfer,
					transfer_list);
		/*
		 * FIXME: This runs in पूर्णांकerrupt context.
		 * Is this really smart?
		 */
		spi_transfer_delay_exec(previous);

		/* Reselect chip select only अगर cs_change was requested */
		अगर (previous->cs_change)
			pl022_cs_control(pl022, SSP_CHIP_SELECT);
	पूर्ण अन्यथा अणु
		/* STATE_START */
		message->state = STATE_RUNNING;
	पूर्ण

	अगर (set_up_next_transfer(pl022, transfer)) अणु
		message->state = STATE_ERROR;
		message->status = -EIO;
		giveback(pl022);
		वापस;
	पूर्ण
	/* Flush the FIFOs and let's go! */
	flush(pl022);

	अगर (pl022->cur_chip->enable_dma) अणु
		अगर (configure_dma(pl022)) अणु
			dev_dbg(&pl022->adev->dev,
				"configuration of DMA failed, fall back to interrupt mode\n");
			जाओ err_config_dma;
		पूर्ण
		वापस;
	पूर्ण

err_config_dma:
	/* enable all पूर्णांकerrupts except RX */
	ग_लिखोw(ENABLE_ALL_INTERRUPTS & ~SSP_IMSC_MASK_RXIM, SSP_IMSC(pl022->virtbase));
पूर्ण

अटल व्योम करो_पूर्णांकerrupt_dma_transfer(काष्ठा pl022 *pl022)
अणु
	/*
	 * Default is to enable all पूर्णांकerrupts except RX -
	 * this will be enabled once TX is complete
	 */
	u32 irqflags = (u32)(ENABLE_ALL_INTERRUPTS & ~SSP_IMSC_MASK_RXIM);

	/* Enable target chip, अगर not alपढ़ोy active */
	अगर (!pl022->next_msg_cs_active)
		pl022_cs_control(pl022, SSP_CHIP_SELECT);

	अगर (set_up_next_transfer(pl022, pl022->cur_transfer)) अणु
		/* Error path */
		pl022->cur_msg->state = STATE_ERROR;
		pl022->cur_msg->status = -EIO;
		giveback(pl022);
		वापस;
	पूर्ण
	/* If we're using DMA, set up DMA here */
	अगर (pl022->cur_chip->enable_dma) अणु
		/* Configure DMA transfer */
		अगर (configure_dma(pl022)) अणु
			dev_dbg(&pl022->adev->dev,
				"configuration of DMA failed, fall back to interrupt mode\n");
			जाओ err_config_dma;
		पूर्ण
		/* Disable पूर्णांकerrupts in DMA mode, IRQ from DMA controller */
		irqflags = DISABLE_ALL_INTERRUPTS;
	पूर्ण
err_config_dma:
	/* Enable SSP, turn on पूर्णांकerrupts */
	ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) | SSP_CR1_MASK_SSE),
	       SSP_CR1(pl022->virtbase));
	ग_लिखोw(irqflags, SSP_IMSC(pl022->virtbase));
पूर्ण

अटल व्योम prपूर्णांक_current_status(काष्ठा pl022 *pl022)
अणु
	u32 पढ़ो_cr0;
	u16 पढ़ो_cr1, पढ़ो_dmacr, पढ़ो_sr;

	अगर (pl022->venकरोr->extended_cr)
		पढ़ो_cr0 = पढ़ोl(SSP_CR0(pl022->virtbase));
	अन्यथा
		पढ़ो_cr0 = पढ़ोw(SSP_CR0(pl022->virtbase));
	पढ़ो_cr1 = पढ़ोw(SSP_CR1(pl022->virtbase));
	पढ़ो_dmacr = पढ़ोw(SSP_DMACR(pl022->virtbase));
	पढ़ो_sr = पढ़ोw(SSP_SR(pl022->virtbase));

	dev_warn(&pl022->adev->dev, "spi-pl022 CR0: %x\n", पढ़ो_cr0);
	dev_warn(&pl022->adev->dev, "spi-pl022 CR1: %x\n", पढ़ो_cr1);
	dev_warn(&pl022->adev->dev, "spi-pl022 DMACR: %x\n", पढ़ो_dmacr);
	dev_warn(&pl022->adev->dev, "spi-pl022 SR: %x\n", पढ़ो_sr);
	dev_warn(&pl022->adev->dev,
			"spi-pl022 exp_fifo_level/fifodepth: %u/%d\n",
			pl022->exp_fअगरo_level,
			pl022->venकरोr->fअगरodepth);

पूर्ण

अटल व्योम करो_polling_transfer(काष्ठा pl022 *pl022)
अणु
	काष्ठा spi_message *message = शून्य;
	काष्ठा spi_transfer *transfer = शून्य;
	काष्ठा spi_transfer *previous = शून्य;
	अचिन्हित दीर्घ समय, समयout;

	message = pl022->cur_msg;

	जबतक (message->state != STATE_DONE) अणु
		/* Handle क्रम पात */
		अगर (message->state == STATE_ERROR)
			अवरोध;
		transfer = pl022->cur_transfer;

		/* Delay अगर requested at end of transfer */
		अगर (message->state == STATE_RUNNING) अणु
			previous =
			    list_entry(transfer->transfer_list.prev,
				       काष्ठा spi_transfer, transfer_list);
			spi_transfer_delay_exec(previous);
			अगर (previous->cs_change)
				pl022_cs_control(pl022, SSP_CHIP_SELECT);
		पूर्ण अन्यथा अणु
			/* STATE_START */
			message->state = STATE_RUNNING;
			अगर (!pl022->next_msg_cs_active)
				pl022_cs_control(pl022, SSP_CHIP_SELECT);
		पूर्ण

		/* Configuration Changing Per Transfer */
		अगर (set_up_next_transfer(pl022, transfer)) अणु
			/* Error path */
			message->state = STATE_ERROR;
			अवरोध;
		पूर्ण
		/* Flush FIFOs and enable SSP */
		flush(pl022);
		ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) | SSP_CR1_MASK_SSE),
		       SSP_CR1(pl022->virtbase));

		dev_dbg(&pl022->adev->dev, "polling transfer ongoing ...\n");

		समयout = jअगरfies + msecs_to_jअगरfies(SPI_POLLING_TIMEOUT);
		जबतक (pl022->tx < pl022->tx_end || pl022->rx < pl022->rx_end) अणु
			समय = jअगरfies;
			पढ़ोग_लिखोr(pl022);
			अगर (समय_after(समय, समयout)) अणु
				dev_warn(&pl022->adev->dev,
				"%s: timeout!\n", __func__);
				message->state = STATE_TIMEOUT;
				prपूर्णांक_current_status(pl022);
				जाओ out;
			पूर्ण
			cpu_relax();
		पूर्ण

		/* Update total byte transferred */
		message->actual_length += pl022->cur_transfer->len;
		/* Move to next transfer */
		message->state = next_transfer(pl022);
		अगर (message->state != STATE_DONE
		    && pl022->cur_transfer->cs_change)
			pl022_cs_control(pl022, SSP_CHIP_DESELECT);
	पूर्ण
out:
	/* Handle end of message */
	अगर (message->state == STATE_DONE)
		message->status = 0;
	अन्यथा अगर (message->state == STATE_TIMEOUT)
		message->status = -EAGAIN;
	अन्यथा
		message->status = -EIO;

	giveback(pl022);
	वापस;
पूर्ण

अटल पूर्णांक pl022_transfer_one_message(काष्ठा spi_master *master,
				      काष्ठा spi_message *msg)
अणु
	काष्ठा pl022 *pl022 = spi_master_get_devdata(master);

	/* Initial message state */
	pl022->cur_msg = msg;
	msg->state = STATE_START;

	pl022->cur_transfer = list_entry(msg->transfers.next,
					 काष्ठा spi_transfer, transfer_list);

	/* Setup the SPI using the per chip configuration */
	pl022->cur_chip = spi_get_ctldata(msg->spi);
	pl022->cur_cs = msg->spi->chip_select;
	/* This is always available but may be set to -ENOENT */
	pl022->cur_gpiod = msg->spi->cs_gpiod;

	restore_state(pl022);
	flush(pl022);

	अगर (pl022->cur_chip->xfer_type == POLLING_TRANSFER)
		करो_polling_transfer(pl022);
	अन्यथा
		करो_पूर्णांकerrupt_dma_transfer(pl022);

	वापस 0;
पूर्ण

अटल पूर्णांक pl022_unprepare_transfer_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा pl022 *pl022 = spi_master_get_devdata(master);

	/* nothing more to करो - disable spi/ssp and घातer off */
	ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) &
		(~SSP_CR1_MASK_SSE)), SSP_CR1(pl022->virtbase));

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_controller_parameters(काष्ठा pl022 *pl022,
				काष्ठा pl022_config_chip स्थिर *chip_info)
अणु
	अगर ((chip_info->अगरace < SSP_INTERFACE_MOTOROLA_SPI)
	    || (chip_info->अगरace > SSP_INTERFACE_UNIसूचीECTIONAL)) अणु
		dev_err(&pl022->adev->dev,
			"interface is configured incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((chip_info->अगरace == SSP_INTERFACE_UNIसूचीECTIONAL) &&
	    (!pl022->venकरोr->unidir)) अणु
		dev_err(&pl022->adev->dev,
			"unidirectional mode not supported in this "
			"hardware version\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((chip_info->hierarchy != SSP_MASTER)
	    && (chip_info->hierarchy != SSP_SLAVE)) अणु
		dev_err(&pl022->adev->dev,
			"hierarchy is configured incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((chip_info->com_mode != INTERRUPT_TRANSFER)
	    && (chip_info->com_mode != DMA_TRANSFER)
	    && (chip_info->com_mode != POLLING_TRANSFER)) अणु
		dev_err(&pl022->adev->dev,
			"Communication mode is configured incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	चयन (chip_info->rx_lev_trig) अणु
	हाल SSP_RX_1_OR_MORE_ELEM:
	हाल SSP_RX_4_OR_MORE_ELEM:
	हाल SSP_RX_8_OR_MORE_ELEM:
		/* These are always OK, all variants can handle this */
		अवरोध;
	हाल SSP_RX_16_OR_MORE_ELEM:
		अगर (pl022->venकरोr->fअगरodepth < 16) अणु
			dev_err(&pl022->adev->dev,
			"RX FIFO Trigger Level is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SSP_RX_32_OR_MORE_ELEM:
		अगर (pl022->venकरोr->fअगरodepth < 32) अणु
			dev_err(&pl022->adev->dev,
			"RX FIFO Trigger Level is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&pl022->adev->dev,
			"RX FIFO Trigger Level is configured incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	चयन (chip_info->tx_lev_trig) अणु
	हाल SSP_TX_1_OR_MORE_EMPTY_LOC:
	हाल SSP_TX_4_OR_MORE_EMPTY_LOC:
	हाल SSP_TX_8_OR_MORE_EMPTY_LOC:
		/* These are always OK, all variants can handle this */
		अवरोध;
	हाल SSP_TX_16_OR_MORE_EMPTY_LOC:
		अगर (pl022->venकरोr->fअगरodepth < 16) अणु
			dev_err(&pl022->adev->dev,
			"TX FIFO Trigger Level is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SSP_TX_32_OR_MORE_EMPTY_LOC:
		अगर (pl022->venकरोr->fअगरodepth < 32) अणु
			dev_err(&pl022->adev->dev,
			"TX FIFO Trigger Level is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&pl022->adev->dev,
			"TX FIFO Trigger Level is configured incorrectly\n");
		वापस -EINVAL;
	पूर्ण
	अगर (chip_info->अगरace == SSP_INTERFACE_NATIONAL_MICROWIRE) अणु
		अगर ((chip_info->ctrl_len < SSP_BITS_4)
		    || (chip_info->ctrl_len > SSP_BITS_32)) अणु
			dev_err(&pl022->adev->dev,
				"CTRL LEN is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((chip_info->रुको_state != SSP_MWIRE_WAIT_ZERO)
		    && (chip_info->रुको_state != SSP_MWIRE_WAIT_ONE)) अणु
			dev_err(&pl022->adev->dev,
				"Wait State is configured incorrectly\n");
			वापस -EINVAL;
		पूर्ण
		/* Half duplex is only available in the ST Micro version */
		अगर (pl022->venकरोr->extended_cr) अणु
			अगर ((chip_info->duplex !=
			     SSP_MICROWIRE_CHANNEL_FULL_DUPLEX)
			    && (chip_info->duplex !=
				SSP_MICROWIRE_CHANNEL_HALF_DUPLEX)) अणु
				dev_err(&pl022->adev->dev,
					"Microwire duplex mode is configured incorrectly\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chip_info->duplex != SSP_MICROWIRE_CHANNEL_FULL_DUPLEX)
				dev_err(&pl022->adev->dev,
					"Microwire half duplex mode requested,"
					" but this is only available in the"
					" ST version of PL022\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u32 spi_rate(u32 rate, u16 cpsdvsr, u16 scr)
अणु
	वापस rate / (cpsdvsr * (1 + scr));
पूर्ण

अटल पूर्णांक calculate_effective_freq(काष्ठा pl022 *pl022, पूर्णांक freq, काष्ठा
				    ssp_घड़ी_params * clk_freq)
अणु
	/* Lets calculate the frequency parameters */
	u16 cpsdvsr = CPSDVR_MIN, scr = SCR_MIN;
	u32 rate, max_tclk, min_tclk, best_freq = 0, best_cpsdvsr = 0,
		best_scr = 0, पंचांगp, found = 0;

	rate = clk_get_rate(pl022->clk);
	/* cpsdvscr = 2 & scr 0 */
	max_tclk = spi_rate(rate, CPSDVR_MIN, SCR_MIN);
	/* cpsdvsr = 254 & scr = 255 */
	min_tclk = spi_rate(rate, CPSDVR_MAX, SCR_MAX);

	अगर (freq > max_tclk)
		dev_warn(&pl022->adev->dev,
			"Max speed that can be programmed is %d Hz, you requested %d\n",
			max_tclk, freq);

	अगर (freq < min_tclk) अणु
		dev_err(&pl022->adev->dev,
			"Requested frequency: %d Hz is less than minimum possible %d Hz\n",
			freq, min_tclk);
		वापस -EINVAL;
	पूर्ण

	/*
	 * best_freq will give बंदst possible available rate (<= requested
	 * freq) क्रम all values of scr & cpsdvsr.
	 */
	जबतक ((cpsdvsr <= CPSDVR_MAX) && !found) अणु
		जबतक (scr <= SCR_MAX) अणु
			पंचांगp = spi_rate(rate, cpsdvsr, scr);

			अगर (पंचांगp > freq) अणु
				/* we need lower freq */
				scr++;
				जारी;
			पूर्ण

			/*
			 * If found exact value, mark found and अवरोध.
			 * If found more बंदr value, update and अवरोध.
			 */
			अगर (पंचांगp > best_freq) अणु
				best_freq = पंचांगp;
				best_cpsdvsr = cpsdvsr;
				best_scr = scr;

				अगर (पंचांगp == freq)
					found = 1;
			पूर्ण
			/*
			 * increased scr will give lower rates, which are not
			 * required
			 */
			अवरोध;
		पूर्ण
		cpsdvsr += 2;
		scr = SCR_MIN;
	पूर्ण

	WARN(!best_freq, "pl022: Matching cpsdvsr and scr not found for %d Hz rate \n",
			freq);

	clk_freq->cpsdvsr = (u8) (best_cpsdvsr & 0xFF);
	clk_freq->scr = (u8) (best_scr & 0xFF);
	dev_dbg(&pl022->adev->dev,
		"SSP Target Frequency is: %u, Effective Frequency is %u\n",
		freq, best_freq);
	dev_dbg(&pl022->adev->dev, "SSP cpsdvsr = %d, scr = %d\n",
		clk_freq->cpsdvsr, clk_freq->scr);

	वापस 0;
पूर्ण

/*
 * A piece of शेष chip info unless the platक्रमm
 * supplies it.
 */
अटल स्थिर काष्ठा pl022_config_chip pl022_शेष_chip_info = अणु
	.com_mode = INTERRUPT_TRANSFER,
	.अगरace = SSP_INTERFACE_MOTOROLA_SPI,
	.hierarchy = SSP_MASTER,
	.slave_tx_disable = DO_NOT_DRIVE_TX,
	.rx_lev_trig = SSP_RX_1_OR_MORE_ELEM,
	.tx_lev_trig = SSP_TX_1_OR_MORE_EMPTY_LOC,
	.ctrl_len = SSP_BITS_8,
	.रुको_state = SSP_MWIRE_WAIT_ZERO,
	.duplex = SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
पूर्ण;

/**
 * pl022_setup - setup function रेजिस्टरed to SPI master framework
 * @spi: spi device which is requesting setup
 *
 * This function is रेजिस्टरed to the SPI framework क्रम this SPI master
 * controller. If it is the first समय when setup is called by this device,
 * this function will initialize the runसमय state क्रम this chip and save
 * the same in the device काष्ठाure. Else it will update the runसमय info
 * with the updated chip info. Nothing is really being written to the
 * controller hardware here, that is not करोne until the actual transfer
 * commence.
 */
अटल पूर्णांक pl022_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा pl022_config_chip स्थिर *chip_info;
	काष्ठा pl022_config_chip chip_info_dt;
	काष्ठा chip_data *chip;
	काष्ठा ssp_घड़ी_params clk_freq = अणु .cpsdvsr = 0, .scr = 0पूर्ण;
	पूर्णांक status = 0;
	काष्ठा pl022 *pl022 = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक bits = spi->bits_per_word;
	u32 पंचांगp;
	काष्ठा device_node *np = spi->dev.of_node;

	अगर (!spi->max_speed_hz)
		वापस -EINVAL;

	/* Get controller_state अगर one is supplied */
	chip = spi_get_ctldata(spi);

	अगर (chip == शून्य) अणु
		chip = kzalloc(माप(काष्ठा chip_data), GFP_KERNEL);
		अगर (!chip)
			वापस -ENOMEM;
		dev_dbg(&spi->dev,
			"allocated memory for controller's runtime state\n");
	पूर्ण

	/* Get controller data अगर one is supplied */
	chip_info = spi->controller_data;

	अगर (chip_info == शून्य) अणु
		अगर (np) अणु
			chip_info_dt = pl022_शेष_chip_info;

			chip_info_dt.hierarchy = SSP_MASTER;
			of_property_पढ़ो_u32(np, "pl022,interface",
				&chip_info_dt.अगरace);
			of_property_पढ़ो_u32(np, "pl022,com-mode",
				&chip_info_dt.com_mode);
			of_property_पढ़ो_u32(np, "pl022,rx-level-trig",
				&chip_info_dt.rx_lev_trig);
			of_property_पढ़ो_u32(np, "pl022,tx-level-trig",
				&chip_info_dt.tx_lev_trig);
			of_property_पढ़ो_u32(np, "pl022,ctrl-len",
				&chip_info_dt.ctrl_len);
			of_property_पढ़ो_u32(np, "pl022,wait-state",
				&chip_info_dt.रुको_state);
			of_property_पढ़ो_u32(np, "pl022,duplex",
				&chip_info_dt.duplex);

			chip_info = &chip_info_dt;
		पूर्ण अन्यथा अणु
			chip_info = &pl022_शेष_chip_info;
			/* spi_board_info.controller_data not is supplied */
			dev_dbg(&spi->dev,
				"using default controller_data settings\n");
		पूर्ण
	पूर्ण अन्यथा
		dev_dbg(&spi->dev,
			"using user supplied controller_data settings\n");

	/*
	 * We can override with custom भागisors, अन्यथा we use the board
	 * frequency setting
	 */
	अगर ((0 == chip_info->clk_freq.cpsdvsr)
	    && (0 == chip_info->clk_freq.scr)) अणु
		status = calculate_effective_freq(pl022,
						  spi->max_speed_hz,
						  &clk_freq);
		अगर (status < 0)
			जाओ err_config_params;
	पूर्ण अन्यथा अणु
		स_नकल(&clk_freq, &chip_info->clk_freq, माप(clk_freq));
		अगर ((clk_freq.cpsdvsr % 2) != 0)
			clk_freq.cpsdvsr =
				clk_freq.cpsdvsr - 1;
	पूर्ण
	अगर ((clk_freq.cpsdvsr < CPSDVR_MIN)
	    || (clk_freq.cpsdvsr > CPSDVR_MAX)) अणु
		status = -EINVAL;
		dev_err(&spi->dev,
			"cpsdvsr is configured incorrectly\n");
		जाओ err_config_params;
	पूर्ण

	status = verअगरy_controller_parameters(pl022, chip_info);
	अगर (status) अणु
		dev_err(&spi->dev, "controller data is incorrect");
		जाओ err_config_params;
	पूर्ण

	pl022->rx_lev_trig = chip_info->rx_lev_trig;
	pl022->tx_lev_trig = chip_info->tx_lev_trig;

	/* Now set controller state based on controller data */
	chip->xfer_type = chip_info->com_mode;

	/* Check bits per word with venकरोr specअगरic range */
	अगर ((bits <= 3) || (bits > pl022->venकरोr->max_bpw)) अणु
		status = -ENOTSUPP;
		dev_err(&spi->dev, "illegal data size for this controller!\n");
		dev_err(&spi->dev, "This controller can only handle 4 <= n <= %d bit words\n",
				pl022->venकरोr->max_bpw);
		जाओ err_config_params;
	पूर्ण अन्यथा अगर (bits <= 8) अणु
		dev_dbg(&spi->dev, "4 <= n <=8 bits per word\n");
		chip->n_bytes = 1;
		chip->पढ़ो = READING_U8;
		chip->ग_लिखो = WRITING_U8;
	पूर्ण अन्यथा अगर (bits <= 16) अणु
		dev_dbg(&spi->dev, "9 <= n <= 16 bits per word\n");
		chip->n_bytes = 2;
		chip->पढ़ो = READING_U16;
		chip->ग_लिखो = WRITING_U16;
	पूर्ण अन्यथा अणु
		dev_dbg(&spi->dev, "17 <= n <= 32 bits per word\n");
		chip->n_bytes = 4;
		chip->पढ़ो = READING_U32;
		chip->ग_लिखो = WRITING_U32;
	पूर्ण

	/* Now Initialize all रेजिस्टर settings required क्रम this chip */
	chip->cr0 = 0;
	chip->cr1 = 0;
	chip->dmacr = 0;
	chip->cpsr = 0;
	अगर ((chip_info->com_mode == DMA_TRANSFER)
	    && ((pl022->master_info)->enable_dma)) अणु
		chip->enable_dma = true;
		dev_dbg(&spi->dev, "DMA mode set in controller state\n");
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_ENABLED,
			       SSP_DMACR_MASK_RXDMAE, 0);
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_ENABLED,
			       SSP_DMACR_MASK_TXDMAE, 1);
	पूर्ण अन्यथा अणु
		chip->enable_dma = false;
		dev_dbg(&spi->dev, "DMA mode NOT set in controller state\n");
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_DISABLED,
			       SSP_DMACR_MASK_RXDMAE, 0);
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_DISABLED,
			       SSP_DMACR_MASK_TXDMAE, 1);
	पूर्ण

	chip->cpsr = clk_freq.cpsdvsr;

	/* Special setup क्रम the ST micro extended control रेजिस्टरs */
	अगर (pl022->venकरोr->extended_cr) अणु
		u32 etx;

		अगर (pl022->venकरोr->pl023) अणु
			/* These bits are only in the PL023 */
			SSP_WRITE_BITS(chip->cr1, chip_info->clkdelay,
				       SSP_CR1_MASK_FBCLKDEL_ST, 13);
		पूर्ण अन्यथा अणु
			/* These bits are in the PL022 but not PL023 */
			SSP_WRITE_BITS(chip->cr0, chip_info->duplex,
				       SSP_CR0_MASK_HALFDUP_ST, 5);
			SSP_WRITE_BITS(chip->cr0, chip_info->ctrl_len,
				       SSP_CR0_MASK_CSS_ST, 16);
			SSP_WRITE_BITS(chip->cr0, chip_info->अगरace,
				       SSP_CR0_MASK_FRF_ST, 21);
			SSP_WRITE_BITS(chip->cr1, chip_info->रुको_state,
				       SSP_CR1_MASK_MWAIT_ST, 6);
		पूर्ण
		SSP_WRITE_BITS(chip->cr0, bits - 1,
			       SSP_CR0_MASK_DSS_ST, 0);

		अगर (spi->mode & SPI_LSB_FIRST) अणु
			पंचांगp = SSP_RX_LSB;
			etx = SSP_TX_LSB;
		पूर्ण अन्यथा अणु
			पंचांगp = SSP_RX_MSB;
			etx = SSP_TX_MSB;
		पूर्ण
		SSP_WRITE_BITS(chip->cr1, पंचांगp, SSP_CR1_MASK_RENDN_ST, 4);
		SSP_WRITE_BITS(chip->cr1, etx, SSP_CR1_MASK_TENDN_ST, 5);
		SSP_WRITE_BITS(chip->cr1, chip_info->rx_lev_trig,
			       SSP_CR1_MASK_RXIFLSEL_ST, 7);
		SSP_WRITE_BITS(chip->cr1, chip_info->tx_lev_trig,
			       SSP_CR1_MASK_TXIFLSEL_ST, 10);
	पूर्ण अन्यथा अणु
		SSP_WRITE_BITS(chip->cr0, bits - 1,
			       SSP_CR0_MASK_DSS, 0);
		SSP_WRITE_BITS(chip->cr0, chip_info->अगरace,
			       SSP_CR0_MASK_FRF, 4);
	पूर्ण

	/* Stuff that is common क्रम all versions */
	अगर (spi->mode & SPI_CPOL)
		पंचांगp = SSP_CLK_POL_IDLE_HIGH;
	अन्यथा
		पंचांगp = SSP_CLK_POL_IDLE_LOW;
	SSP_WRITE_BITS(chip->cr0, पंचांगp, SSP_CR0_MASK_SPO, 6);

	अगर (spi->mode & SPI_CPHA)
		पंचांगp = SSP_CLK_SECOND_EDGE;
	अन्यथा
		पंचांगp = SSP_CLK_FIRST_EDGE;
	SSP_WRITE_BITS(chip->cr0, पंचांगp, SSP_CR0_MASK_SPH, 7);

	SSP_WRITE_BITS(chip->cr0, clk_freq.scr, SSP_CR0_MASK_SCR, 8);
	/* Loopback is available on all versions except PL023 */
	अगर (pl022->venकरोr->loopback) अणु
		अगर (spi->mode & SPI_LOOP)
			पंचांगp = LOOPBACK_ENABLED;
		अन्यथा
			पंचांगp = LOOPBACK_DISABLED;
		SSP_WRITE_BITS(chip->cr1, पंचांगp, SSP_CR1_MASK_LBM, 0);
	पूर्ण
	SSP_WRITE_BITS(chip->cr1, SSP_DISABLED, SSP_CR1_MASK_SSE, 1);
	SSP_WRITE_BITS(chip->cr1, chip_info->hierarchy, SSP_CR1_MASK_MS, 2);
	SSP_WRITE_BITS(chip->cr1, chip_info->slave_tx_disable, SSP_CR1_MASK_SOD,
		3);

	/* Save controller_state */
	spi_set_ctldata(spi, chip);
	वापस status;
 err_config_params:
	spi_set_ctldata(spi, शून्य);
	kमुक्त(chip);
	वापस status;
पूर्ण

/**
 * pl022_cleanup - cleanup function रेजिस्टरed to SPI master framework
 * @spi: spi device which is requesting cleanup
 *
 * This function is रेजिस्टरed to the SPI framework क्रम this SPI master
 * controller. It will मुक्त the runसमय state of chip.
 */
अटल व्योम pl022_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);

	spi_set_ctldata(spi, शून्य);
	kमुक्त(chip);
पूर्ण

अटल काष्ठा pl022_ssp_controller *
pl022_platक्रमm_data_dt_get(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा pl022_ssp_controller *pd;

	अगर (!np) अणु
		dev_err(dev, "no dt node defined\n");
		वापस शून्य;
	पूर्ण

	pd = devm_kzalloc(dev, माप(काष्ठा pl022_ssp_controller), GFP_KERNEL);
	अगर (!pd)
		वापस शून्य;

	pd->bus_id = -1;
	pd->enable_dma = 1;
	of_property_पढ़ो_u32(np, "pl022,autosuspend-delay",
			     &pd->स्वतःsuspend_delay);
	pd->rt = of_property_पढ़ो_bool(np, "pl022,rt");

	वापस pd;
पूर्ण

अटल पूर्णांक pl022_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा pl022_ssp_controller *platक्रमm_info =
			dev_get_platdata(&adev->dev);
	काष्ठा spi_master *master;
	काष्ठा pl022 *pl022 = शून्य;	/*Data क्रम this driver */
	पूर्णांक status = 0;

	dev_info(&adev->dev,
		 "ARM PL022 driver, device ID: 0x%08x\n", adev->periphid);
	अगर (!platक्रमm_info && IS_ENABLED(CONFIG_OF))
		platक्रमm_info = pl022_platक्रमm_data_dt_get(dev);

	अगर (!platक्रमm_info) अणु
		dev_err(dev, "probe: no platform data defined\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate master with space क्रम data */
	master = spi_alloc_master(dev, माप(काष्ठा pl022));
	अगर (master == शून्य) अणु
		dev_err(&adev->dev, "probe - cannot alloc SPI master\n");
		वापस -ENOMEM;
	पूर्ण

	pl022 = spi_master_get_devdata(master);
	pl022->master = master;
	pl022->master_info = platक्रमm_info;
	pl022->adev = adev;
	pl022->venकरोr = id->data;

	/*
	 * Bus Number Which has been Asचिन्हित to this SSP controller
	 * on this board
	 */
	master->bus_num = platक्रमm_info->bus_id;
	master->cleanup = pl022_cleanup;
	master->setup = pl022_setup;
	master->स्वतः_runसमय_pm = true;
	master->transfer_one_message = pl022_transfer_one_message;
	master->unprepare_transfer_hardware = pl022_unprepare_transfer_hardware;
	master->rt = platक्रमm_info->rt;
	master->dev.of_node = dev->of_node;
	master->use_gpio_descriptors = true;

	/*
	 * Supports mode 0-3, loopback, and active low CS. Transfers are
	 * always MS bit first on the original pl022.
	 */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LOOP;
	अगर (pl022->venकरोr->extended_cr)
		master->mode_bits |= SPI_LSB_FIRST;

	dev_dbg(&adev->dev, "BUSNO: %d\n", master->bus_num);

	status = amba_request_regions(adev, शून्य);
	अगर (status)
		जाओ err_no_ioregion;

	pl022->phybase = adev->res.start;
	pl022->virtbase = devm_ioremap(dev, adev->res.start,
				       resource_size(&adev->res));
	अगर (pl022->virtbase == शून्य) अणु
		status = -ENOMEM;
		जाओ err_no_ioremap;
	पूर्ण
	dev_info(&adev->dev, "mapped registers from %pa to %p\n",
		&adev->res.start, pl022->virtbase);

	pl022->clk = devm_clk_get(&adev->dev, शून्य);
	अगर (IS_ERR(pl022->clk)) अणु
		status = PTR_ERR(pl022->clk);
		dev_err(&adev->dev, "could not retrieve SSP/SPI bus clock\n");
		जाओ err_no_clk;
	पूर्ण

	status = clk_prepare_enable(pl022->clk);
	अगर (status) अणु
		dev_err(&adev->dev, "could not enable SSP/SPI bus clock\n");
		जाओ err_no_clk_en;
	पूर्ण

	/* Initialize transfer pump */
	tasklet_init(&pl022->pump_transfers, pump_transfers,
		     (अचिन्हित दीर्घ)pl022);

	/* Disable SSP */
	ग_लिखोw((पढ़ोw(SSP_CR1(pl022->virtbase)) & (~SSP_CR1_MASK_SSE)),
	       SSP_CR1(pl022->virtbase));
	load_ssp_शेष_config(pl022);

	status = devm_request_irq(dev, adev->irq[0], pl022_पूर्णांकerrupt_handler,
				  0, "pl022", pl022);
	अगर (status < 0) अणु
		dev_err(&adev->dev, "probe - cannot get IRQ (%d)\n", status);
		जाओ err_no_irq;
	पूर्ण

	/* Get DMA channels, try स्वतःconfiguration first */
	status = pl022_dma_स्वतःprobe(pl022);
	अगर (status == -EPROBE_DEFER) अणु
		dev_dbg(dev, "deferring probe to get DMA channel\n");
		जाओ err_no_irq;
	पूर्ण

	/* If that failed, use channels from platक्रमm_info */
	अगर (status == 0)
		platक्रमm_info->enable_dma = 1;
	अन्यथा अगर (platक्रमm_info->enable_dma) अणु
		status = pl022_dma_probe(pl022);
		अगर (status != 0)
			platक्रमm_info->enable_dma = 0;
	पूर्ण

	/* Register with the SPI framework */
	amba_set_drvdata(adev, pl022);
	status = devm_spi_रेजिस्टर_master(&adev->dev, master);
	अगर (status != 0) अणु
		dev_err(&adev->dev,
			"probe - problem registering spi master\n");
		जाओ err_spi_रेजिस्टर;
	पूर्ण
	dev_dbg(dev, "probe succeeded\n");

	/* let runसमय pm put suspend */
	अगर (platक्रमm_info->स्वतःsuspend_delay > 0) अणु
		dev_info(&adev->dev,
			"will use autosuspend for runtime pm, delay %dms\n",
			platक्रमm_info->स्वतःsuspend_delay);
		pm_runसमय_set_स्वतःsuspend_delay(dev,
			platक्रमm_info->स्वतःsuspend_delay);
		pm_runसमय_use_स्वतःsuspend(dev);
	पूर्ण
	pm_runसमय_put(dev);

	वापस 0;

 err_spi_रेजिस्टर:
	अगर (platक्रमm_info->enable_dma)
		pl022_dma_हटाओ(pl022);
 err_no_irq:
	clk_disable_unprepare(pl022->clk);
 err_no_clk_en:
 err_no_clk:
 err_no_ioremap:
	amba_release_regions(adev);
 err_no_ioregion:
	spi_master_put(master);
	वापस status;
पूर्ण

अटल व्योम
pl022_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा pl022 *pl022 = amba_get_drvdata(adev);

	अगर (!pl022)
		वापस;

	/*
	 * unकरो pm_runसमय_put() in probe.  I assume that we're not
	 * accessing the primecell here.
	 */
	pm_runसमय_get_noresume(&adev->dev);

	load_ssp_शेष_config(pl022);
	अगर (pl022->master_info->enable_dma)
		pl022_dma_हटाओ(pl022);

	clk_disable_unprepare(pl022->clk);
	amba_release_regions(adev);
	tasklet_disable(&pl022->pump_transfers);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pl022_suspend(काष्ठा device *dev)
अणु
	काष्ठा pl022 *pl022 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(pl022->master);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret) अणु
		spi_master_resume(pl022->master);
		वापस ret;
	पूर्ण

	pinctrl_pm_select_sleep_state(dev);

	dev_dbg(dev, "suspended\n");
	वापस 0;
पूर्ण

अटल पूर्णांक pl022_resume(काष्ठा device *dev)
अणु
	काष्ठा pl022 *pl022 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		dev_err(dev, "problem resuming\n");

	/* Start the queue running */
	ret = spi_master_resume(pl022->master);
	अगर (!ret)
		dev_dbg(dev, "resumed\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pl022_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pl022 *pl022 = dev_get_drvdata(dev);

	clk_disable_unprepare(pl022->clk);
	pinctrl_pm_select_idle_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक pl022_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pl022 *pl022 = dev_get_drvdata(dev);

	pinctrl_pm_select_शेष_state(dev);
	clk_prepare_enable(pl022->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pl022_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pl022_suspend, pl022_resume)
	SET_RUNTIME_PM_OPS(pl022_runसमय_suspend, pl022_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_arm = अणु
	.fअगरodepth = 8,
	.max_bpw = 16,
	.unidir = false,
	.extended_cr = false,
	.pl023 = false,
	.loopback = true,
	.पूर्णांकernal_cs_ctrl = false,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_st = अणु
	.fअगरodepth = 32,
	.max_bpw = 32,
	.unidir = false,
	.extended_cr = true,
	.pl023 = false,
	.loopback = true,
	.पूर्णांकernal_cs_ctrl = false,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_st_pl023 = अणु
	.fअगरodepth = 32,
	.max_bpw = 32,
	.unidir = false,
	.extended_cr = true,
	.pl023 = true,
	.loopback = false,
	.पूर्णांकernal_cs_ctrl = false,
पूर्ण;

अटल काष्ठा venकरोr_data venकरोr_lsi = अणु
	.fअगरodepth = 8,
	.max_bpw = 16,
	.unidir = false,
	.extended_cr = false,
	.pl023 = false,
	.loopback = true,
	.पूर्णांकernal_cs_ctrl = true,
पूर्ण;

अटल स्थिर काष्ठा amba_id pl022_ids[] = अणु
	अणु
		/*
		 * ARM PL022 variant, this has a 16bit wide
		 * and 8 locations deep TX/RX FIFO
		 */
		.id	= 0x00041022,
		.mask	= 0x000fffff,
		.data	= &venकरोr_arm,
	पूर्ण,
	अणु
		/*
		 * ST Micro derivative, this has 32bit wide
		 * and 32 locations deep TX/RX FIFO
		 */
		.id	= 0x01080022,
		.mask	= 0xffffffff,
		.data	= &venकरोr_st,
	पूर्ण,
	अणु
		/*
		 * ST-Ericsson derivative "PL023" (this is not
		 * an official ARM number), this is a PL022 SSP block
		 * stripped to SPI mode only, it has 32bit wide
		 * and 32 locations deep TX/RX FIFO but no extended
		 * CR0/CR1 रेजिस्टर
		 */
		.id	= 0x00080023,
		.mask	= 0xffffffff,
		.data	= &venकरोr_st_pl023,
	पूर्ण,
	अणु
		/*
		 * PL022 variant that has a chip select control रेजिस्टर whih
		 * allows control of 5 output संकेतs nCS[0:4].
		 */
		.id	= 0x000b6022,
		.mask	= 0x000fffff,
		.data	= &venकरोr_lsi,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, pl022_ids);

अटल काष्ठा amba_driver pl022_driver = अणु
	.drv = अणु
		.name	= "ssp-pl022",
		.pm	= &pl022_dev_pm_ops,
	पूर्ण,
	.id_table	= pl022_ids,
	.probe		= pl022_probe,
	.हटाओ		= pl022_हटाओ,
पूर्ण;

अटल पूर्णांक __init pl022_init(व्योम)
अणु
	वापस amba_driver_रेजिस्टर(&pl022_driver);
पूर्ण
subsys_initcall(pl022_init);

अटल व्योम __निकास pl022_निकास(व्योम)
अणु
	amba_driver_unरेजिस्टर(&pl022_driver);
पूर्ण
module_निकास(pl022_निकास);

MODULE_AUTHOR("Linus Walleij <linus.walleij@stericsson.com>");
MODULE_DESCRIPTION("PL022 SSP Controller Driver");
MODULE_LICENSE("GPL");
