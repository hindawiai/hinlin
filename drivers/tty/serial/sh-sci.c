<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH on-chip serial module support.  (SCI with no FIFO / with FIFO)
 *
 *  Copyright (C) 2002 - 2011  Paul Mundt
 *  Copyright (C) 2015 Glider bvba
 *  Modअगरied to support SH7720 SCIF. Markus Brunner, Mark Jonas (Jul 2007).
 *
 * based off of the old drivers/अक्षर/sh-sci.c by:
 *
 *   Copyright (C) 1999, 2000  Niibe Yutaka
 *   Copyright (C) 2000  Sugioka Toshinobu
 *   Modअगरied to support multiple serial ports. Stuart Menefy (May 2000).
 *   Modअगरied to support SecureEdge. David McCullough (2002)
 *   Modअगरied to support SH7300 SCIF. Takashi Kusuda (Jun 2003).
 *   Removed SH7300 support (Jul 2007).
 */
#अघोषित DEBUG

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/major.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysrq.h>
#समावेश <linux/समयr.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#अगर_घोषित CONFIG_SUPERH
#समावेश <यंत्र/sh_मूलप्रण.स>
#समावेश <यंत्र/platक्रमm_early.h>
#पूर्ण_अगर

#समावेश "serial_mctrl_gpio.h"
#समावेश "sh-sci.h"

/* Offsets पूर्णांकo the sci_port->irqs array */
क्रमागत अणु
	SCIx_ERI_IRQ,
	SCIx_RXI_IRQ,
	SCIx_TXI_IRQ,
	SCIx_BRI_IRQ,
	SCIx_DRI_IRQ,
	SCIx_TEI_IRQ,
	SCIx_NR_IRQS,

	SCIx_MUX_IRQ = SCIx_NR_IRQS,	/* special हाल */
पूर्ण;

#घोषणा SCIx_IRQ_IS_MUXED(port)			\
	((port)->irqs[SCIx_ERI_IRQ] ==	\
	 (port)->irqs[SCIx_RXI_IRQ]) ||	\
	((port)->irqs[SCIx_ERI_IRQ] &&	\
	 ((port)->irqs[SCIx_RXI_IRQ] < 0))

क्रमागत SCI_CLKS अणु
	SCI_FCK,		/* Functional Clock */
	SCI_SCK,		/* Optional External Clock */
	SCI_BRG_INT,		/* Optional BRG Internal Clock Source */
	SCI_SCIF_CLK,		/* Optional BRG External Clock Source */
	SCI_NUM_CLKS
पूर्ण;

/* Bit x set means sampling rate x + 1 is supported */
#घोषणा SCI_SR(x)		BIT((x) - 1)
#घोषणा SCI_SR_RANGE(x, y)	GENMASK((y) - 1, (x) - 1)

#घोषणा SCI_SR_SCIFAB		SCI_SR(5) | SCI_SR(7) | SCI_SR(11) | \
				SCI_SR(13) | SCI_SR(16) | SCI_SR(17) | \
				SCI_SR(19) | SCI_SR(27)

#घोषणा min_sr(_port)		ffs((_port)->sampling_rate_mask)
#घोषणा max_sr(_port)		fls((_port)->sampling_rate_mask)

/* Iterate over all supported sampling rates, from high to low */
#घोषणा क्रम_each_sr(_sr, _port)						\
	क्रम ((_sr) = max_sr(_port); (_sr) >= min_sr(_port); (_sr)--)	\
		अगर ((_port)->sampling_rate_mask & SCI_SR((_sr)))

काष्ठा plat_sci_reg अणु
	u8 offset, size;
पूर्ण;

काष्ठा sci_port_params अणु
	स्थिर काष्ठा plat_sci_reg regs[SCIx_NR_REGS];
	अचिन्हित पूर्णांक fअगरosize;
	अचिन्हित पूर्णांक overrun_reg;
	अचिन्हित पूर्णांक overrun_mask;
	अचिन्हित पूर्णांक sampling_rate_mask;
	अचिन्हित पूर्णांक error_mask;
	अचिन्हित पूर्णांक error_clear;
पूर्ण;

काष्ठा sci_port अणु
	काष्ठा uart_port	port;

	/* Platक्रमm configuration */
	स्थिर काष्ठा sci_port_params *params;
	स्थिर काष्ठा plat_sci_port *cfg;
	अचिन्हित पूर्णांक		sampling_rate_mask;
	resource_माप_प्रकार		reg_size;
	काष्ठा mctrl_gpios	*gpios;

	/* Clocks */
	काष्ठा clk		*clks[SCI_NUM_CLKS];
	अचिन्हित दीर्घ		clk_rates[SCI_NUM_CLKS];

	पूर्णांक			irqs[SCIx_NR_IRQS];
	अक्षर			*irqstr[SCIx_NR_IRQS];

	काष्ठा dma_chan			*chan_tx;
	काष्ठा dma_chan			*chan_rx;

#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
	काष्ठा dma_chan			*chan_tx_saved;
	काष्ठा dma_chan			*chan_rx_saved;
	dma_cookie_t			cookie_tx;
	dma_cookie_t			cookie_rx[2];
	dma_cookie_t			active_rx;
	dma_addr_t			tx_dma_addr;
	अचिन्हित पूर्णांक			tx_dma_len;
	काष्ठा scatterlist		sg_rx[2];
	व्योम				*rx_buf[2];
	माप_प्रकार				buf_len_rx;
	काष्ठा work_काष्ठा		work_tx;
	काष्ठा hrसमयr			rx_समयr;
	अचिन्हित पूर्णांक			rx_समयout;	/* microseconds */
#पूर्ण_अगर
	अचिन्हित पूर्णांक			rx_frame;
	पूर्णांक				rx_trigger;
	काष्ठा समयr_list		rx_fअगरo_समयr;
	पूर्णांक				rx_fअगरo_समयout;
	u16				hscअगर_tot;

	bool has_rtscts;
	bool स्वतःrts;
पूर्ण;

#घोषणा SCI_NPORTS CONFIG_SERIAL_SH_SCI_NR_UARTS

अटल काष्ठा sci_port sci_ports[SCI_NPORTS];
अटल अचिन्हित दीर्घ sci_ports_in_use;
अटल काष्ठा uart_driver sci_uart_driver;

अटल अंतरभूत काष्ठा sci_port *
to_sci_port(काष्ठा uart_port *uart)
अणु
	वापस container_of(uart, काष्ठा sci_port, port);
पूर्ण

अटल स्थिर काष्ठा sci_port_params sci_port_params[SCIx_NR_REGTYPES] = अणु
	/*
	 * Common SCI definitions, dependent on the port's regshअगरt
	 * value.
	 */
	[SCIx_SCI_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00,  8 पूर्ण,
			[SCBRR]		= अणु 0x01,  8 पूर्ण,
			[SCSCR]		= अणु 0x02,  8 पूर्ण,
			[SCxTDR]	= अणु 0x03,  8 पूर्ण,
			[SCxSR]		= अणु 0x04,  8 पूर्ण,
			[SCxRDR]	= अणु 0x05,  8 पूर्ण,
		पूर्ण,
		.fअगरosize = 1,
		.overrun_reg = SCxSR,
		.overrun_mask = SCI_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCI_DEFAULT_ERROR_MASK | SCI_ORER,
		.error_clear = SCI_ERROR_CLEAR & ~SCI_ORER,
	पूर्ण,

	/*
	 * Common definitions क्रम legacy IrDA ports.
	 */
	[SCIx_IRDA_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00,  8 पूर्ण,
			[SCBRR]		= अणु 0x02,  8 पूर्ण,
			[SCSCR]		= अणु 0x04,  8 पूर्ण,
			[SCxTDR]	= अणु 0x06,  8 पूर्ण,
			[SCxSR]		= अणु 0x08, 16 पूर्ण,
			[SCxRDR]	= अणु 0x0a,  8 पूर्ण,
			[SCFCR]		= अणु 0x0c,  8 पूर्ण,
			[SCFDR]		= अणु 0x0e, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 1,
		.overrun_reg = SCxSR,
		.overrun_mask = SCI_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCI_DEFAULT_ERROR_MASK | SCI_ORER,
		.error_clear = SCI_ERROR_CLEAR & ~SCI_ORER,
	पूर्ण,

	/*
	 * Common SCIFA definitions.
	 */
	[SCIx_SCIFA_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x20,  8 पूर्ण,
			[SCxSR]		= अणु 0x14, 16 पूर्ण,
			[SCxRDR]	= अणु 0x24,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCPCR]		= अणु 0x30, 16 पूर्ण,
			[SCPDR]		= अणु 0x34, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 64,
		.overrun_reg = SCxSR,
		.overrun_mask = SCIFA_ORER,
		.sampling_rate_mask = SCI_SR_SCIFAB,
		.error_mask = SCIF_DEFAULT_ERROR_MASK | SCIFA_ORER,
		.error_clear = SCIF_ERROR_CLEAR & ~SCIFA_ORER,
	पूर्ण,

	/*
	 * Common SCIFB definitions.
	 */
	[SCIx_SCIFB_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x40,  8 पूर्ण,
			[SCxSR]		= अणु 0x14, 16 पूर्ण,
			[SCxRDR]	= अणु 0x60,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCTFDR]	= अणु 0x38, 16 पूर्ण,
			[SCRFDR]	= अणु 0x3c, 16 पूर्ण,
			[SCPCR]		= अणु 0x30, 16 पूर्ण,
			[SCPDR]		= अणु 0x34, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 256,
		.overrun_reg = SCxSR,
		.overrun_mask = SCIFA_ORER,
		.sampling_rate_mask = SCI_SR_SCIFAB,
		.error_mask = SCIF_DEFAULT_ERROR_MASK | SCIFA_ORER,
		.error_clear = SCIF_ERROR_CLEAR & ~SCIFA_ORER,
	पूर्ण,

	/*
	 * Common SH-2(A) SCIF definitions क्रम ports with FIFO data
	 * count रेजिस्टरs.
	 */
	[SCIx_SH2_SCIF_FIFODATA_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCSPTR]	= अणु 0x20, 16 पूर्ण,
			[SCLSR]		= अणु 0x24, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * The "SCIFA" that is in RZ/T and RZ/A2.
	 * It looks like a normal SCIF with FIFO data, but with a
	 * compressed address space. Also, the अवरोध out of पूर्णांकerrupts
	 * are dअगरferent: ERI/BRI, RXI, TXI, TEI, DRI.
	 */
	[SCIx_RZ_SCIFA_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x02,  8 पूर्ण,
			[SCSCR]		= अणु 0x04, 16 पूर्ण,
			[SCxTDR]	= अणु 0x06,  8 पूर्ण,
			[SCxSR]		= अणु 0x08, 16 पूर्ण,
			[SCxRDR]	= अणु 0x0A,  8 पूर्ण,
			[SCFCR]		= अणु 0x0C, 16 पूर्ण,
			[SCFDR]		= अणु 0x0E, 16 पूर्ण,
			[SCSPTR]	= अणु 0x10, 16 पूर्ण,
			[SCLSR]		= अणु 0x12, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common SH-3 SCIF definitions.
	 */
	[SCIx_SH3_SCIF_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00,  8 पूर्ण,
			[SCBRR]		= अणु 0x02,  8 पूर्ण,
			[SCSCR]		= अणु 0x04,  8 पूर्ण,
			[SCxTDR]	= अणु 0x06,  8 पूर्ण,
			[SCxSR]		= अणु 0x08, 16 पूर्ण,
			[SCxRDR]	= अणु 0x0a,  8 पूर्ण,
			[SCFCR]		= अणु 0x0c,  8 पूर्ण,
			[SCFDR]		= अणु 0x0e, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common SH-4(A) SCIF(B) definitions.
	 */
	[SCIx_SH4_SCIF_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCSPTR]	= अणु 0x20, 16 पूर्ण,
			[SCLSR]		= अणु 0x24, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common SCIF definitions क्रम ports with a Baud Rate Generator क्रम
	 * External Clock (BRG).
	 */
	[SCIx_SH4_SCIF_BRG_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCSPTR]	= अणु 0x20, 16 पूर्ण,
			[SCLSR]		= अणु 0x24, 16 पूर्ण,
			[SCDL]		= अणु 0x30, 16 पूर्ण,
			[SCCKS]		= अणु 0x34, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common HSCIF definitions.
	 */
	[SCIx_HSCIF_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCSPTR]	= अणु 0x20, 16 पूर्ण,
			[SCLSR]		= अणु 0x24, 16 पूर्ण,
			[HSSRR]		= अणु 0x40, 16 पूर्ण,
			[SCDL]		= अणु 0x30, 16 पूर्ण,
			[SCCKS]		= अणु 0x34, 16 पूर्ण,
			[HSRTRGR]	= अणु 0x54, 16 पूर्ण,
			[HSTTRGR]	= अणु 0x58, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 128,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR_RANGE(8, 32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common SH-4(A) SCIF(B) definitions क्रम ports without an SCSPTR
	 * रेजिस्टर.
	 */
	[SCIx_SH4_SCIF_NO_SCSPTR_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCLSR]		= अणु 0x24, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * Common SH-4(A) SCIF(B) definitions क्रम ports with FIFO data
	 * count रेजिस्टरs.
	 */
	[SCIx_SH4_SCIF_FIFODATA_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x0c,  8 पूर्ण,
			[SCxSR]		= अणु 0x10, 16 पूर्ण,
			[SCxRDR]	= अणु 0x14,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
			[SCTFDR]	= अणु 0x1c, 16 पूर्ण,	/* aliased to SCFDR */
			[SCRFDR]	= अणु 0x20, 16 पूर्ण,
			[SCSPTR]	= अणु 0x24, 16 पूर्ण,
			[SCLSR]		= अणु 0x28, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 16,
		.overrun_reg = SCLSR,
		.overrun_mask = SCLSR_ORER,
		.sampling_rate_mask = SCI_SR(32),
		.error_mask = SCIF_DEFAULT_ERROR_MASK,
		.error_clear = SCIF_ERROR_CLEAR,
	पूर्ण,

	/*
	 * SH7705-style SCIF(B) ports, lacking both SCSPTR and SCLSR
	 * रेजिस्टरs.
	 */
	[SCIx_SH7705_SCIF_REGTYPE] = अणु
		.regs = अणु
			[SCSMR]		= अणु 0x00, 16 पूर्ण,
			[SCBRR]		= अणु 0x04,  8 पूर्ण,
			[SCSCR]		= अणु 0x08, 16 पूर्ण,
			[SCxTDR]	= अणु 0x20,  8 पूर्ण,
			[SCxSR]		= अणु 0x14, 16 पूर्ण,
			[SCxRDR]	= अणु 0x24,  8 पूर्ण,
			[SCFCR]		= अणु 0x18, 16 पूर्ण,
			[SCFDR]		= अणु 0x1c, 16 पूर्ण,
		पूर्ण,
		.fअगरosize = 64,
		.overrun_reg = SCxSR,
		.overrun_mask = SCIFA_ORER,
		.sampling_rate_mask = SCI_SR(16),
		.error_mask = SCIF_DEFAULT_ERROR_MASK | SCIFA_ORER,
		.error_clear = SCIF_ERROR_CLEAR & ~SCIFA_ORER,
	पूर्ण,
पूर्ण;

#घोषणा sci_getreg(up, offset)		(&to_sci_port(up)->params->regs[offset])

/*
 * The "offset" here is rather misleading, in that it refers to an क्रमागत
 * value relative to the port mapping rather than the fixed offset
 * itself, which needs to be manually retrieved from the platक्रमm's
 * रेजिस्टर map क्रम the given port.
 */
अटल अचिन्हित पूर्णांक sci_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	स्थिर काष्ठा plat_sci_reg *reg = sci_getreg(p, offset);

	अगर (reg->size == 8)
		वापस ioपढ़ो8(p->membase + (reg->offset << p->regshअगरt));
	अन्यथा अगर (reg->size == 16)
		वापस ioपढ़ो16(p->membase + (reg->offset << p->regshअगरt));
	अन्यथा
		WARN(1, "Invalid register access\n");

	वापस 0;
पूर्ण

अटल व्योम sci_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	स्थिर काष्ठा plat_sci_reg *reg = sci_getreg(p, offset);

	अगर (reg->size == 8)
		ioग_लिखो8(value, p->membase + (reg->offset << p->regshअगरt));
	अन्यथा अगर (reg->size == 16)
		ioग_लिखो16(value, p->membase + (reg->offset << p->regshअगरt));
	अन्यथा
		WARN(1, "Invalid register access\n");
पूर्ण

अटल व्योम sci_port_enable(काष्ठा sci_port *sci_port)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sci_port->port.dev)
		वापस;

	pm_runसमय_get_sync(sci_port->port.dev);

	क्रम (i = 0; i < SCI_NUM_CLKS; i++) अणु
		clk_prepare_enable(sci_port->clks[i]);
		sci_port->clk_rates[i] = clk_get_rate(sci_port->clks[i]);
	पूर्ण
	sci_port->port.uartclk = sci_port->clk_rates[SCI_FCK];
पूर्ण

अटल व्योम sci_port_disable(काष्ठा sci_port *sci_port)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sci_port->port.dev)
		वापस;

	क्रम (i = SCI_NUM_CLKS; i-- > 0; )
		clk_disable_unprepare(sci_port->clks[i]);

	pm_runसमय_put_sync(sci_port->port.dev);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ port_rx_irq_mask(काष्ठा uart_port *port)
अणु
	/*
	 * Not all ports (such as SCIFA) will support REIE. Rather than
	 * special-casing the port type, we check the port initialization
	 * IRQ enable mask to see whether the IRQ is desired at all. If
	 * it's unset, it's logically inferred that there's no poपूर्णांक in
	 * testing क्रम it.
	 */
	वापस SCSCR_RIE | (to_sci_port(port)->cfg->scscr & SCSCR_REIE);
पूर्ण

अटल व्योम sci_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	अचिन्हित लघु ctrl;

#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		u16 new, scr = serial_port_in(port, SCSCR);
		अगर (s->chan_tx)
			new = scr | SCSCR_TDRQE;
		अन्यथा
			new = scr & ~SCSCR_TDRQE;
		अगर (new != scr)
			serial_port_out(port, SCSCR, new);
	पूर्ण

	अगर (s->chan_tx && !uart_circ_empty(&s->port.state->xmit) &&
	    dma_submit_error(s->cookie_tx)) अणु
		s->cookie_tx = 0;
		schedule_work(&s->work_tx);
	पूर्ण
#पूर्ण_अगर

	अगर (!s->chan_tx || port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		/* Set TIE (Transmit Interrupt Enable) bit in SCSCR */
		ctrl = serial_port_in(port, SCSCR);
		serial_port_out(port, SCSCR, ctrl | SCSCR_TIE);
	पूर्ण
पूर्ण

अटल व्योम sci_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित लघु ctrl;

	/* Clear TIE (Transmit Interrupt Enable) bit in SCSCR */
	ctrl = serial_port_in(port, SCSCR);

	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		ctrl &= ~SCSCR_TDRQE;

	ctrl &= ~SCSCR_TIE;

	serial_port_out(port, SCSCR, ctrl);
पूर्ण

अटल व्योम sci_start_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित लघु ctrl;

	ctrl = serial_port_in(port, SCSCR) | port_rx_irq_mask(port);

	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		ctrl &= ~SCSCR_RDRQE;

	serial_port_out(port, SCSCR, ctrl);
पूर्ण

अटल व्योम sci_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित लघु ctrl;

	ctrl = serial_port_in(port, SCSCR);

	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		ctrl &= ~SCSCR_RDRQE;

	ctrl &= ~port_rx_irq_mask(port);

	serial_port_out(port, SCSCR, ctrl);
पूर्ण

अटल व्योम sci_clear_SCxSR(काष्ठा uart_port *port, अचिन्हित पूर्णांक mask)
अणु
	अगर (port->type == PORT_SCI) अणु
		/* Just store the mask */
		serial_port_out(port, SCxSR, mask);
	पूर्ण अन्यथा अगर (to_sci_port(port)->params->overrun_mask == SCIFA_ORER) अणु
		/* SCIFA/SCIFB and SCIF on SH7705/SH7720/SH7721 */
		/* Only clear the status bits we want to clear */
		serial_port_out(port, SCxSR,
				serial_port_in(port, SCxSR) & mask);
	पूर्ण अन्यथा अणु
		/* Store the mask, clear parity/framing errors */
		serial_port_out(port, SCxSR, mask & ~(SCIF_FERC | SCIF_PERC));
	पूर्ण
पूर्ण

#अगर defined(CONFIG_CONSOLE_POLL) || defined(CONFIG_SERIAL_SH_SCI_CONSOLE) || \
    defined(CONFIG_SERIAL_SH_SCI_EARLYCON)

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक sci_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	अचिन्हित लघु status;
	पूर्णांक c;

	करो अणु
		status = serial_port_in(port, SCxSR);
		अगर (status & SCxSR_ERRORS(port)) अणु
			sci_clear_SCxSR(port, SCxSR_ERROR_CLEAR(port));
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (1);

	अगर (!(status & SCxSR_RDxF(port)))
		वापस NO_POLL_CHAR;

	c = serial_port_in(port, SCxRDR);

	/* Dummy पढ़ो */
	serial_port_in(port, SCxSR);
	sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));

	वापस c;
पूर्ण
#पूर्ण_अगर

अटल व्योम sci_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित लघु status;

	करो अणु
		status = serial_port_in(port, SCxSR);
	पूर्ण जबतक (!(status & SCxSR_TDxE(port)));

	serial_port_out(port, SCxTDR, c);
	sci_clear_SCxSR(port, SCxSR_TDxE_CLEAR(port) & ~SCxSR_TEND(port));
पूर्ण
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL || CONFIG_SERIAL_SH_SCI_CONSOLE ||
	  CONFIG_SERIAL_SH_SCI_EARLYCON */

अटल व्योम sci_init_pins(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag)
अणु
	काष्ठा sci_port *s = to_sci_port(port);

	/*
	 * Use port-specअगरic handler अगर provided.
	 */
	अगर (s->cfg->ops && s->cfg->ops->init_pins) अणु
		s->cfg->ops->init_pins(port, cflag);
		वापस;
	पूर्ण

	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		u16 data = serial_port_in(port, SCPDR);
		u16 ctrl = serial_port_in(port, SCPCR);

		/* Enable RXD and TXD pin functions */
		ctrl &= ~(SCPCR_RXDC | SCPCR_TXDC);
		अगर (to_sci_port(port)->has_rtscts) अणु
			/* RTS# is output, active low, unless स्वतःrts */
			अगर (!(port->mctrl & TIOCM_RTS)) अणु
				ctrl |= SCPCR_RTSC;
				data |= SCPDR_RTSD;
			पूर्ण अन्यथा अगर (!s->स्वतःrts) अणु
				ctrl |= SCPCR_RTSC;
				data &= ~SCPDR_RTSD;
			पूर्ण अन्यथा अणु
				/* Enable RTS# pin function */
				ctrl &= ~SCPCR_RTSC;
			पूर्ण
			/* Enable CTS# pin function */
			ctrl &= ~SCPCR_CTSC;
		पूर्ण
		serial_port_out(port, SCPDR, data);
		serial_port_out(port, SCPCR, ctrl);
	पूर्ण अन्यथा अगर (sci_getreg(port, SCSPTR)->size) अणु
		u16 status = serial_port_in(port, SCSPTR);

		/* RTS# is always output; and active low, unless स्वतःrts */
		status |= SCSPTR_RTSIO;
		अगर (!(port->mctrl & TIOCM_RTS))
			status |= SCSPTR_RTSDT;
		अन्यथा अगर (!s->स्वतःrts)
			status &= ~SCSPTR_RTSDT;
		/* CTS# and SCK are inमाला_दो */
		status &= ~(SCSPTR_CTSIO | SCSPTR_SCKIO);
		serial_port_out(port, SCSPTR, status);
	पूर्ण
पूर्ण

अटल पूर्णांक sci_txfill(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	अचिन्हित पूर्णांक fअगरo_mask = (s->params->fअगरosize << 1) - 1;
	स्थिर काष्ठा plat_sci_reg *reg;

	reg = sci_getreg(port, SCTFDR);
	अगर (reg->size)
		वापस serial_port_in(port, SCTFDR) & fअगरo_mask;

	reg = sci_getreg(port, SCFDR);
	अगर (reg->size)
		वापस serial_port_in(port, SCFDR) >> 8;

	वापस !(serial_port_in(port, SCxSR) & SCI_TDRE);
पूर्ण

अटल पूर्णांक sci_txroom(काष्ठा uart_port *port)
अणु
	वापस port->fअगरosize - sci_txfill(port);
पूर्ण

अटल पूर्णांक sci_rxfill(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	अचिन्हित पूर्णांक fअगरo_mask = (s->params->fअगरosize << 1) - 1;
	स्थिर काष्ठा plat_sci_reg *reg;

	reg = sci_getreg(port, SCRFDR);
	अगर (reg->size)
		वापस serial_port_in(port, SCRFDR) & fअगरo_mask;

	reg = sci_getreg(port, SCFDR);
	अगर (reg->size)
		वापस serial_port_in(port, SCFDR) & fअगरo_mask;

	वापस (serial_port_in(port, SCxSR) & SCxSR_RDxF(port)) != 0;
पूर्ण

/* ********************************************************************** *
 *                   the पूर्णांकerrupt related routines                       *
 * ********************************************************************** */

अटल व्योम sci_transmit_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक stopped = uart_tx_stopped(port);
	अचिन्हित लघु status;
	अचिन्हित लघु ctrl;
	पूर्णांक count;

	status = serial_port_in(port, SCxSR);
	अगर (!(status & SCxSR_TDxE(port))) अणु
		ctrl = serial_port_in(port, SCSCR);
		अगर (uart_circ_empty(xmit))
			ctrl &= ~SCSCR_TIE;
		अन्यथा
			ctrl |= SCSCR_TIE;
		serial_port_out(port, SCSCR, ctrl);
		वापस;
	पूर्ण

	count = sci_txroom(port);

	करो अणु
		अचिन्हित अक्षर c;

		अगर (port->x_अक्षर) अणु
			c = port->x_अक्षर;
			port->x_अक्षर = 0;
		पूर्ण अन्यथा अगर (!uart_circ_empty(xmit) && !stopped) अणु
			c = xmit->buf[xmit->tail];
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		serial_port_out(port, SCxTDR, c);

		port->icount.tx++;
	पूर्ण जबतक (--count > 0);

	sci_clear_SCxSR(port, SCxSR_TDxE_CLEAR(port));

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
	अगर (uart_circ_empty(xmit))
		sci_stop_tx(port);

पूर्ण

/* On SH3, SCIF may पढ़ो end-of-अवरोध as a space->mark अक्षर */
#घोषणा STEPFN(c)  (अणुपूर्णांक __c = (c); (((__c-1)|(__c)) == -1); पूर्ण)

अटल व्योम sci_receive_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	पूर्णांक i, count, copied = 0;
	अचिन्हित लघु status;
	अचिन्हित अक्षर flag;

	status = serial_port_in(port, SCxSR);
	अगर (!(status & SCxSR_RDxF(port)))
		वापस;

	जबतक (1) अणु
		/* Don't copy more bytes than there is room क्रम in the buffer */
		count = tty_buffer_request_room(tport, sci_rxfill(port));

		/* If क्रम any reason we can't copy more data, we're करोne! */
		अगर (count == 0)
			अवरोध;

		अगर (port->type == PORT_SCI) अणु
			अक्षर c = serial_port_in(port, SCxRDR);
			अगर (uart_handle_sysrq_अक्षर(port, c))
				count = 0;
			अन्यथा
				tty_insert_flip_अक्षर(tport, c, TTY_NORMAL);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < count; i++) अणु
				अक्षर c;

				अगर (port->type == PORT_SCIF ||
				    port->type == PORT_HSCIF) अणु
					status = serial_port_in(port, SCxSR);
					c = serial_port_in(port, SCxRDR);
				पूर्ण अन्यथा अणु
					c = serial_port_in(port, SCxRDR);
					status = serial_port_in(port, SCxSR);
				पूर्ण
				अगर (uart_handle_sysrq_अक्षर(port, c)) अणु
					count--; i--;
					जारी;
				पूर्ण

				/* Store data and status */
				अगर (status & SCxSR_FER(port)) अणु
					flag = TTY_FRAME;
					port->icount.frame++;
					dev_notice(port->dev, "frame error\n");
				पूर्ण अन्यथा अगर (status & SCxSR_PER(port)) अणु
					flag = TTY_PARITY;
					port->icount.parity++;
					dev_notice(port->dev, "parity error\n");
				पूर्ण अन्यथा
					flag = TTY_NORMAL;

				tty_insert_flip_अक्षर(tport, c, flag);
			पूर्ण
		पूर्ण

		serial_port_in(port, SCxSR); /* dummy पढ़ो */
		sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));

		copied += count;
		port->icount.rx += count;
	पूर्ण

	अगर (copied) अणु
		/* Tell the rest of the प्रणाली the news. New अक्षरacters! */
		tty_flip_buffer_push(tport);
	पूर्ण अन्यथा अणु
		/* TTY buffers full; पढ़ो from RX reg to prevent lockup */
		serial_port_in(port, SCxRDR);
		serial_port_in(port, SCxSR); /* dummy पढ़ो */
		sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));
	पूर्ण
पूर्ण

अटल पूर्णांक sci_handle_errors(काष्ठा uart_port *port)
अणु
	पूर्णांक copied = 0;
	अचिन्हित लघु status = serial_port_in(port, SCxSR);
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा sci_port *s = to_sci_port(port);

	/* Handle overruns */
	अगर (status & s->params->overrun_mask) अणु
		port->icount.overrun++;

		/* overrun error */
		अगर (tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN))
			copied++;

		dev_notice(port->dev, "overrun error\n");
	पूर्ण

	अगर (status & SCxSR_FER(port)) अणु
		/* frame error */
		port->icount.frame++;

		अगर (tty_insert_flip_अक्षर(tport, 0, TTY_FRAME))
			copied++;

		dev_notice(port->dev, "frame error\n");
	पूर्ण

	अगर (status & SCxSR_PER(port)) अणु
		/* parity error */
		port->icount.parity++;

		अगर (tty_insert_flip_अक्षर(tport, 0, TTY_PARITY))
			copied++;

		dev_notice(port->dev, "parity error\n");
	पूर्ण

	अगर (copied)
		tty_flip_buffer_push(tport);

	वापस copied;
पूर्ण

अटल पूर्णांक sci_handle_fअगरo_overrun(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा sci_port *s = to_sci_port(port);
	स्थिर काष्ठा plat_sci_reg *reg;
	पूर्णांक copied = 0;
	u16 status;

	reg = sci_getreg(port, s->params->overrun_reg);
	अगर (!reg->size)
		वापस 0;

	status = serial_port_in(port, s->params->overrun_reg);
	अगर (status & s->params->overrun_mask) अणु
		status &= ~s->params->overrun_mask;
		serial_port_out(port, s->params->overrun_reg, status);

		port->icount.overrun++;

		tty_insert_flip_अक्षर(tport, 0, TTY_OVERRUN);
		tty_flip_buffer_push(tport);

		dev_dbg(port->dev, "overrun error\n");
		copied++;
	पूर्ण

	वापस copied;
पूर्ण

अटल पूर्णांक sci_handle_अवरोधs(काष्ठा uart_port *port)
अणु
	पूर्णांक copied = 0;
	अचिन्हित लघु status = serial_port_in(port, SCxSR);
	काष्ठा tty_port *tport = &port->state->port;

	अगर (uart_handle_अवरोध(port))
		वापस 0;

	अगर (status & SCxSR_BRK(port)) अणु
		port->icount.brk++;

		/* Notअगरy of BREAK */
		अगर (tty_insert_flip_अक्षर(tport, 0, TTY_BREAK))
			copied++;

		dev_dbg(port->dev, "BREAK detected\n");
	पूर्ण

	अगर (copied)
		tty_flip_buffer_push(tport);

	copied += sci_handle_fअगरo_overrun(port);

	वापस copied;
पूर्ण

अटल पूर्णांक scअगर_set_rtrg(काष्ठा uart_port *port, पूर्णांक rx_trig)
अणु
	अचिन्हित पूर्णांक bits;

	अगर (rx_trig >= port->fअगरosize)
		rx_trig = port->fअगरosize - 1;
	अगर (rx_trig < 1)
		rx_trig = 1;

	/* HSCIF can be set to an arbitrary level. */
	अगर (sci_getreg(port, HSRTRGR)->size) अणु
		serial_port_out(port, HSRTRGR, rx_trig);
		वापस rx_trig;
	पूर्ण

	चयन (port->type) अणु
	हाल PORT_SCIF:
		अगर (rx_trig < 4) अणु
			bits = 0;
			rx_trig = 1;
		पूर्ण अन्यथा अगर (rx_trig < 8) अणु
			bits = SCFCR_RTRG0;
			rx_trig = 4;
		पूर्ण अन्यथा अगर (rx_trig < 14) अणु
			bits = SCFCR_RTRG1;
			rx_trig = 8;
		पूर्ण अन्यथा अणु
			bits = SCFCR_RTRG0 | SCFCR_RTRG1;
			rx_trig = 14;
		पूर्ण
		अवरोध;
	हाल PORT_SCIFA:
	हाल PORT_SCIFB:
		अगर (rx_trig < 16) अणु
			bits = 0;
			rx_trig = 1;
		पूर्ण अन्यथा अगर (rx_trig < 32) अणु
			bits = SCFCR_RTRG0;
			rx_trig = 16;
		पूर्ण अन्यथा अगर (rx_trig < 48) अणु
			bits = SCFCR_RTRG1;
			rx_trig = 32;
		पूर्ण अन्यथा अणु
			bits = SCFCR_RTRG0 | SCFCR_RTRG1;
			rx_trig = 48;
		पूर्ण
		अवरोध;
	शेष:
		WARN(1, "unknown FIFO configuration");
		वापस 1;
	पूर्ण

	serial_port_out(port, SCFCR,
		(serial_port_in(port, SCFCR) &
		~(SCFCR_RTRG1 | SCFCR_RTRG0)) | bits);

	वापस rx_trig;
पूर्ण

अटल पूर्णांक scअगर_rtrg_enabled(काष्ठा uart_port *port)
अणु
	अगर (sci_getreg(port, HSRTRGR)->size)
		वापस serial_port_in(port, HSRTRGR) != 0;
	अन्यथा
		वापस (serial_port_in(port, SCFCR) &
			(SCFCR_RTRG0 | SCFCR_RTRG1)) != 0;
पूर्ण

अटल व्योम rx_fअगरo_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_port *s = from_समयr(s, t, rx_fअगरo_समयr);
	काष्ठा uart_port *port = &s->port;

	dev_dbg(port->dev, "Rx timed out\n");
	scअगर_set_rtrg(port, 1);
पूर्ण

अटल sमाप_प्रकार rx_fअगरo_trigger_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sci_port *sci = to_sci_port(port);

	वापस प्र_लिखो(buf, "%d\n", sci->rx_trigger);
पूर्ण

अटल sमाप_प्रकार rx_fअगरo_trigger_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sci_port *sci = to_sci_port(port);
	पूर्णांक ret;
	दीर्घ r;

	ret = kम_से_दीर्घ(buf, 0, &r);
	अगर (ret)
		वापस ret;

	sci->rx_trigger = scअगर_set_rtrg(port, r);
	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		scअगर_set_rtrg(port, 1);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(rx_fअगरo_trigger);

अटल sमाप_प्रकार rx_fअगरo_समयout_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sci_port *sci = to_sci_port(port);
	पूर्णांक v;

	अगर (port->type == PORT_HSCIF)
		v = sci->hscअगर_tot >> HSSCR_TOT_SHIFT;
	अन्यथा
		v = sci->rx_fअगरo_समयout;

	वापस प्र_लिखो(buf, "%d\n", v);
पूर्ण

अटल sमाप_प्रकार rx_fअगरo_समयout_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sci_port *sci = to_sci_port(port);
	पूर्णांक ret;
	दीर्घ r;

	ret = kम_से_दीर्घ(buf, 0, &r);
	अगर (ret)
		वापस ret;

	अगर (port->type == PORT_HSCIF) अणु
		अगर (r < 0 || r > 3)
			वापस -EINVAL;
		sci->hscअगर_tot = r << HSSCR_TOT_SHIFT;
	पूर्ण अन्यथा अणु
		sci->rx_fअगरo_समयout = r;
		scअगर_set_rtrg(port, 1);
		अगर (r > 0)
			समयr_setup(&sci->rx_fअगरo_समयr, rx_fअगरo_समयr_fn, 0);
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(rx_fअगरo_समयout);


#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
अटल व्योम sci_dma_tx_complete(व्योम *arg)
अणु
	काष्ठा sci_port *s = arg;
	काष्ठा uart_port *port = &s->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ flags;

	dev_dbg(port->dev, "%s(%d)\n", __func__, port->line);

	spin_lock_irqsave(&port->lock, flags);

	xmit->tail += s->tx_dma_len;
	xmit->tail &= UART_XMIT_SIZE - 1;

	port->icount.tx += s->tx_dma_len;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (!uart_circ_empty(xmit)) अणु
		s->cookie_tx = 0;
		schedule_work(&s->work_tx);
	पूर्ण अन्यथा अणु
		s->cookie_tx = -EINVAL;
		अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
			u16 ctrl = serial_port_in(port, SCSCR);
			serial_port_out(port, SCSCR, ctrl & ~SCSCR_TIE);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* Locking: called with port lock held */
अटल पूर्णांक sci_dma_rx_push(काष्ठा sci_port *s, व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा uart_port *port = &s->port;
	काष्ठा tty_port *tport = &port->state->port;
	पूर्णांक copied;

	copied = tty_insert_flip_string(tport, buf, count);
	अगर (copied < count)
		port->icount.buf_overrun++;

	port->icount.rx += copied;

	वापस copied;
पूर्ण

अटल पूर्णांक sci_dma_rx_find_active(काष्ठा sci_port *s)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s->cookie_rx); i++)
		अगर (s->active_rx == s->cookie_rx[i])
			वापस i;

	वापस -1;
पूर्ण

अटल व्योम sci_dma_rx_chan_invalidate(काष्ठा sci_port *s)
अणु
	अचिन्हित पूर्णांक i;

	s->chan_rx = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(s->cookie_rx); i++)
		s->cookie_rx[i] = -EINVAL;
	s->active_rx = 0;
पूर्ण

अटल व्योम sci_dma_rx_release(काष्ठा sci_port *s)
अणु
	काष्ठा dma_chan *chan = s->chan_rx_saved;

	s->chan_rx_saved = शून्य;
	sci_dma_rx_chan_invalidate(s);
	dmaengine_terminate_sync(chan);
	dma_मुक्त_coherent(chan->device->dev, s->buf_len_rx * 2, s->rx_buf[0],
			  sg_dma_address(&s->sg_rx[0]));
	dma_release_channel(chan);
पूर्ण

अटल व्योम start_hrसमयr_us(काष्ठा hrसमयr *hrt, अचिन्हित दीर्घ usec)
अणु
	दीर्घ sec = usec / 1000000;
	दीर्घ nsec = (usec % 1000000) * 1000;
	kसमय_प्रकार t = kसमय_set(sec, nsec);

	hrसमयr_start(hrt, t, HRTIMER_MODE_REL);
पूर्ण

अटल व्योम sci_dma_rx_reenable_irq(काष्ठा sci_port *s)
अणु
	काष्ठा uart_port *port = &s->port;
	u16 scr;

	/* Direct new serial port पूर्णांकerrupts back to CPU */
	scr = serial_port_in(port, SCSCR);
	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		scr &= ~SCSCR_RDRQE;
		enable_irq(s->irqs[SCIx_RXI_IRQ]);
	पूर्ण
	serial_port_out(port, SCSCR, scr | SCSCR_RIE);
पूर्ण

अटल व्योम sci_dma_rx_complete(व्योम *arg)
अणु
	काष्ठा sci_port *s = arg;
	काष्ठा dma_chan *chan = s->chan_rx;
	काष्ठा uart_port *port = &s->port;
	काष्ठा dma_async_tx_descriptor *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक active, count = 0;

	dev_dbg(port->dev, "%s(%d) active cookie %d\n", __func__, port->line,
		s->active_rx);

	spin_lock_irqsave(&port->lock, flags);

	active = sci_dma_rx_find_active(s);
	अगर (active >= 0)
		count = sci_dma_rx_push(s, s->rx_buf[active], s->buf_len_rx);

	start_hrसमयr_us(&s->rx_समयr, s->rx_समयout);

	अगर (count)
		tty_flip_buffer_push(&port->state->port);

	desc = dmaengine_prep_slave_sg(s->chan_rx, &s->sg_rx[active], 1,
				       DMA_DEV_TO_MEM,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		जाओ fail;

	desc->callback = sci_dma_rx_complete;
	desc->callback_param = s;
	s->cookie_rx[active] = dmaengine_submit(desc);
	अगर (dma_submit_error(s->cookie_rx[active]))
		जाओ fail;

	s->active_rx = s->cookie_rx[!active];

	dma_async_issue_pending(chan);

	spin_unlock_irqrestore(&port->lock, flags);
	dev_dbg(port->dev, "%s: cookie %d #%d, new active cookie %d\n",
		__func__, s->cookie_rx[active], active, s->active_rx);
	वापस;

fail:
	spin_unlock_irqrestore(&port->lock, flags);
	dev_warn(port->dev, "Failed submitting Rx DMA descriptor\n");
	/* Switch to PIO */
	spin_lock_irqsave(&port->lock, flags);
	dmaengine_terminate_async(chan);
	sci_dma_rx_chan_invalidate(s);
	sci_dma_rx_reenable_irq(s);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम sci_dma_tx_release(काष्ठा sci_port *s)
अणु
	काष्ठा dma_chan *chan = s->chan_tx_saved;

	cancel_work_sync(&s->work_tx);
	s->chan_tx_saved = s->chan_tx = शून्य;
	s->cookie_tx = -EINVAL;
	dmaengine_terminate_sync(chan);
	dma_unmap_single(chan->device->dev, s->tx_dma_addr, UART_XMIT_SIZE,
			 DMA_TO_DEVICE);
	dma_release_channel(chan);
पूर्ण

अटल पूर्णांक sci_dma_rx_submit(काष्ठा sci_port *s, bool port_lock_held)
अणु
	काष्ठा dma_chan *chan = s->chan_rx;
	काष्ठा uart_port *port = &s->port;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा scatterlist *sg = &s->sg_rx[i];
		काष्ठा dma_async_tx_descriptor *desc;

		desc = dmaengine_prep_slave_sg(chan,
			sg, 1, DMA_DEV_TO_MEM,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!desc)
			जाओ fail;

		desc->callback = sci_dma_rx_complete;
		desc->callback_param = s;
		s->cookie_rx[i] = dmaengine_submit(desc);
		अगर (dma_submit_error(s->cookie_rx[i]))
			जाओ fail;

	पूर्ण

	s->active_rx = s->cookie_rx[0];

	dma_async_issue_pending(chan);
	वापस 0;

fail:
	/* Switch to PIO */
	अगर (!port_lock_held)
		spin_lock_irqsave(&port->lock, flags);
	अगर (i)
		dmaengine_terminate_async(chan);
	sci_dma_rx_chan_invalidate(s);
	sci_start_rx(port);
	अगर (!port_lock_held)
		spin_unlock_irqrestore(&port->lock, flags);
	वापस -EAGAIN;
पूर्ण

अटल व्योम sci_dma_tx_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sci_port *s = container_of(work, काष्ठा sci_port, work_tx);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan *chan = s->chan_tx;
	काष्ठा uart_port *port = &s->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित दीर्घ flags;
	dma_addr_t buf;
	पूर्णांक head, tail;

	/*
	 * DMA is idle now.
	 * Port xmit buffer is alपढ़ोy mapped, and it is one page... Just adjust
	 * offsets and lengths. Since it is a circular buffer, we have to
	 * transmit till the end, and then the rest. Take the port lock to get a
	 * consistent xmit buffer state.
	 */
	spin_lock_irq(&port->lock);
	head = xmit->head;
	tail = xmit->tail;
	buf = s->tx_dma_addr + (tail & (UART_XMIT_SIZE - 1));
	s->tx_dma_len = min_t(अचिन्हित पूर्णांक,
		CIRC_CNT(head, tail, UART_XMIT_SIZE),
		CIRC_CNT_TO_END(head, tail, UART_XMIT_SIZE));
	अगर (!s->tx_dma_len) अणु
		/* Transmit buffer has been flushed */
		spin_unlock_irq(&port->lock);
		वापस;
	पूर्ण

	desc = dmaengine_prep_slave_single(chan, buf, s->tx_dma_len,
					   DMA_MEM_TO_DEV,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		spin_unlock_irq(&port->lock);
		dev_warn(port->dev, "Failed preparing Tx DMA descriptor\n");
		जाओ चयन_to_pio;
	पूर्ण

	dma_sync_single_क्रम_device(chan->device->dev, buf, s->tx_dma_len,
				   DMA_TO_DEVICE);

	desc->callback = sci_dma_tx_complete;
	desc->callback_param = s;
	s->cookie_tx = dmaengine_submit(desc);
	अगर (dma_submit_error(s->cookie_tx)) अणु
		spin_unlock_irq(&port->lock);
		dev_warn(port->dev, "Failed submitting Tx DMA descriptor\n");
		जाओ चयन_to_pio;
	पूर्ण

	spin_unlock_irq(&port->lock);
	dev_dbg(port->dev, "%s: %p: %d...%d, cookie %d\n",
		__func__, xmit->buf, tail, head, s->cookie_tx);

	dma_async_issue_pending(chan);
	वापस;

चयन_to_pio:
	spin_lock_irqsave(&port->lock, flags);
	s->chan_tx = शून्य;
	sci_start_tx(port);
	spin_unlock_irqrestore(&port->lock, flags);
	वापस;
पूर्ण

अटल क्रमागत hrसमयr_restart sci_dma_rx_समयr_fn(काष्ठा hrसमयr *t)
अणु
	काष्ठा sci_port *s = container_of(t, काष्ठा sci_port, rx_समयr);
	काष्ठा dma_chan *chan = s->chan_rx;
	काष्ठा uart_port *port = &s->port;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पढ़ो;
	पूर्णांक active, count;

	dev_dbg(port->dev, "DMA Rx timed out\n");

	spin_lock_irqsave(&port->lock, flags);

	active = sci_dma_rx_find_active(s);
	अगर (active < 0) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		वापस HRTIMER_NORESTART;
	पूर्ण

	status = dmaengine_tx_status(s->chan_rx, s->active_rx, &state);
	अगर (status == DMA_COMPLETE) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		dev_dbg(port->dev, "Cookie %d #%d has already completed\n",
			s->active_rx, active);

		/* Let packet complete handler take care of the packet */
		वापस HRTIMER_NORESTART;
	पूर्ण

	dmaengine_छोड़ो(chan);

	/*
	 * someबार DMA transfer करोesn't stop even अगर it is stopped and
	 * data keeps on coming until transaction is complete so check
	 * क्रम DMA_COMPLETE again
	 * Let packet complete handler take care of the packet
	 */
	status = dmaengine_tx_status(s->chan_rx, s->active_rx, &state);
	अगर (status == DMA_COMPLETE) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		dev_dbg(port->dev, "Transaction complete after DMA engine was stopped");
		वापस HRTIMER_NORESTART;
	पूर्ण

	/* Handle incomplete DMA receive */
	dmaengine_terminate_async(s->chan_rx);
	पढ़ो = sg_dma_len(&s->sg_rx[active]) - state.residue;

	अगर (पढ़ो) अणु
		count = sci_dma_rx_push(s, s->rx_buf[active], पढ़ो);
		अगर (count)
			tty_flip_buffer_push(&port->state->port);
	पूर्ण

	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		sci_dma_rx_submit(s, true);

	sci_dma_rx_reenable_irq(s);

	spin_unlock_irqrestore(&port->lock, flags);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल काष्ठा dma_chan *sci_request_dma_chan(काष्ठा uart_port *port,
					     क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	chan = dma_request_slave_channel(port->dev,
					 dir == DMA_MEM_TO_DEV ? "tx" : "rx");
	अगर (!chan) अणु
		dev_dbg(port->dev, "dma_request_slave_channel failed\n");
		वापस शून्य;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.direction = dir;
	अगर (dir == DMA_MEM_TO_DEV) अणु
		cfg.dst_addr = port->mapbase +
			(sci_getreg(port, SCxTDR)->offset << port->regshअगरt);
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण अन्यथा अणु
		cfg.src_addr = port->mapbase +
			(sci_getreg(port, SCxRDR)->offset << port->regshअगरt);
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण

	ret = dmaengine_slave_config(chan, &cfg);
	अगर (ret) अणु
		dev_warn(port->dev, "dmaengine_slave_config failed %d\n", ret);
		dma_release_channel(chan);
		वापस शून्य;
	पूर्ण

	वापस chan;
पूर्ण

अटल व्योम sci_request_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	काष्ठा dma_chan *chan;

	dev_dbg(port->dev, "%s: port %d\n", __func__, port->line);

	/*
	 * DMA on console may पूर्णांकerfere with Kernel log messages which use
	 * plain अक्षर_दो(). So, simply करोn't use it with a console.
	 */
	अगर (uart_console(port))
		वापस;

	अगर (!port->dev->of_node)
		वापस;

	s->cookie_tx = -EINVAL;

	/*
	 * Don't request a dma channel अगर no channel was specअगरied
	 * in the device tree.
	 */
	अगर (!of_find_property(port->dev->of_node, "dmas", शून्य))
		वापस;

	chan = sci_request_dma_chan(port, DMA_MEM_TO_DEV);
	dev_dbg(port->dev, "%s: TX: got channel %p\n", __func__, chan);
	अगर (chan) अणु
		/* UART circular tx buffer is an aligned page. */
		s->tx_dma_addr = dma_map_single(chan->device->dev,
						port->state->xmit.buf,
						UART_XMIT_SIZE,
						DMA_TO_DEVICE);
		अगर (dma_mapping_error(chan->device->dev, s->tx_dma_addr)) अणु
			dev_warn(port->dev, "Failed mapping Tx DMA descriptor\n");
			dma_release_channel(chan);
		पूर्ण अन्यथा अणु
			dev_dbg(port->dev, "%s: mapped %lu@%p to %pad\n",
				__func__, UART_XMIT_SIZE,
				port->state->xmit.buf, &s->tx_dma_addr);

			INIT_WORK(&s->work_tx, sci_dma_tx_work_fn);
			s->chan_tx_saved = s->chan_tx = chan;
		पूर्ण
	पूर्ण

	chan = sci_request_dma_chan(port, DMA_DEV_TO_MEM);
	dev_dbg(port->dev, "%s: RX: got channel %p\n", __func__, chan);
	अगर (chan) अणु
		अचिन्हित पूर्णांक i;
		dma_addr_t dma;
		व्योम *buf;

		s->buf_len_rx = 2 * max_t(माप_प्रकार, 16, port->fअगरosize);
		buf = dma_alloc_coherent(chan->device->dev, s->buf_len_rx * 2,
					 &dma, GFP_KERNEL);
		अगर (!buf) अणु
			dev_warn(port->dev,
				 "Failed to allocate Rx dma buffer, using PIO\n");
			dma_release_channel(chan);
			वापस;
		पूर्ण

		क्रम (i = 0; i < 2; i++) अणु
			काष्ठा scatterlist *sg = &s->sg_rx[i];

			sg_init_table(sg, 1);
			s->rx_buf[i] = buf;
			sg_dma_address(sg) = dma;
			sg_dma_len(sg) = s->buf_len_rx;

			buf += s->buf_len_rx;
			dma += s->buf_len_rx;
		पूर्ण

		hrसमयr_init(&s->rx_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		s->rx_समयr.function = sci_dma_rx_समयr_fn;

		s->chan_rx_saved = s->chan_rx = chan;

		अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
			sci_dma_rx_submit(s, false);
	पूर्ण
पूर्ण

अटल व्योम sci_मुक्त_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);

	अगर (s->chan_tx_saved)
		sci_dma_tx_release(s);
	अगर (s->chan_rx_saved)
		sci_dma_rx_release(s);
पूर्ण

अटल व्योम sci_flush_buffer(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);

	/*
	 * In uart_flush_buffer(), the xmit circular buffer has just been
	 * cleared, so we have to reset tx_dma_len accordingly, and stop any
	 * pending transfers
	 */
	s->tx_dma_len = 0;
	अगर (s->chan_tx) अणु
		dmaengine_terminate_async(s->chan_tx);
		s->cookie_tx = -EINVAL;
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_SERIAL_SH_SCI_DMA */
अटल अंतरभूत व्योम sci_request_dma(काष्ठा uart_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम sci_मुक्त_dma(काष्ठा uart_port *port)
अणु
पूर्ण

#घोषणा sci_flush_buffer	शून्य
#पूर्ण_अगर /* !CONFIG_SERIAL_SH_SCI_DMA */

अटल irqवापस_t sci_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	काष्ठा sci_port *s = to_sci_port(port);

#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
	अगर (s->chan_rx) अणु
		u16 scr = serial_port_in(port, SCSCR);
		u16 ssr = serial_port_in(port, SCxSR);

		/* Disable future Rx पूर्णांकerrupts */
		अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
			disable_irq_nosync(irq);
			scr |= SCSCR_RDRQE;
		पूर्ण अन्यथा अणु
			अगर (sci_dma_rx_submit(s, false) < 0)
				जाओ handle_pio;

			scr &= ~SCSCR_RIE;
		पूर्ण
		serial_port_out(port, SCSCR, scr);
		/* Clear current पूर्णांकerrupt */
		serial_port_out(port, SCxSR,
				ssr & ~(SCIF_DR | SCxSR_RDxF(port)));
		dev_dbg(port->dev, "Rx IRQ %lu: setup t-out in %u us\n",
			jअगरfies, s->rx_समयout);
		start_hrसमयr_us(&s->rx_समयr, s->rx_समयout);

		वापस IRQ_HANDLED;
	पूर्ण

handle_pio:
#पूर्ण_अगर

	अगर (s->rx_trigger > 1 && s->rx_fअगरo_समयout > 0) अणु
		अगर (!scअगर_rtrg_enabled(port))
			scअगर_set_rtrg(port, s->rx_trigger);

		mod_समयr(&s->rx_fअगरo_समयr, jअगरfies + DIV_ROUND_UP(
			  s->rx_frame * HZ * s->rx_fअगरo_समयout, 1000000));
	पूर्ण

	/* I think sci_receive_अक्षरs has to be called irrespective
	 * of whether the I_IXOFF is set, otherwise, how is the पूर्णांकerrupt
	 * to be disabled?
	 */
	sci_receive_अक्षरs(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sci_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	sci_transmit_अक्षरs(port);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sci_br_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;

	/* Handle BREAKs */
	sci_handle_अवरोधs(port);
	sci_clear_SCxSR(port, SCxSR_BREAK_CLEAR(port));

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sci_er_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	काष्ठा sci_port *s = to_sci_port(port);

	अगर (s->irqs[SCIx_ERI_IRQ] == s->irqs[SCIx_BRI_IRQ]) अणु
		/* Break and Error पूर्णांकerrupts are muxed */
		अचिन्हित लघु ssr_status = serial_port_in(port, SCxSR);

		/* Break Interrupt */
		अगर (ssr_status & SCxSR_BRK(port))
			sci_br_पूर्णांकerrupt(irq, ptr);

		/* Break only? */
		अगर (!(ssr_status & SCxSR_ERRORS(port)))
			वापस IRQ_HANDLED;
	पूर्ण

	/* Handle errors */
	अगर (port->type == PORT_SCI) अणु
		अगर (sci_handle_errors(port)) अणु
			/* discard अक्षरacter in rx buffer */
			serial_port_in(port, SCxSR);
			sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));
		पूर्ण
	पूर्ण अन्यथा अणु
		sci_handle_fअगरo_overrun(port);
		अगर (!s->chan_rx)
			sci_receive_अक्षरs(port);
	पूर्ण

	sci_clear_SCxSR(port, SCxSR_ERROR_CLEAR(port));

	/* Kick the transmission */
	अगर (!s->chan_tx)
		sci_tx_पूर्णांकerrupt(irq, ptr);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sci_mpxed_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	अचिन्हित लघु ssr_status, scr_status, err_enabled, orer_status = 0;
	काष्ठा uart_port *port = ptr;
	काष्ठा sci_port *s = to_sci_port(port);
	irqवापस_t ret = IRQ_NONE;

	ssr_status = serial_port_in(port, SCxSR);
	scr_status = serial_port_in(port, SCSCR);
	अगर (s->params->overrun_reg == SCxSR)
		orer_status = ssr_status;
	अन्यथा अगर (sci_getreg(port, s->params->overrun_reg)->size)
		orer_status = serial_port_in(port, s->params->overrun_reg);

	err_enabled = scr_status & port_rx_irq_mask(port);

	/* Tx Interrupt */
	अगर ((ssr_status & SCxSR_TDxE(port)) && (scr_status & SCSCR_TIE) &&
	    !s->chan_tx)
		ret = sci_tx_पूर्णांकerrupt(irq, ptr);

	/*
	 * Rx Interrupt: अगर we're using DMA, the DMA controller clears RDF /
	 * DR flags
	 */
	अगर (((ssr_status & SCxSR_RDxF(port)) || s->chan_rx) &&
	    (scr_status & SCSCR_RIE))
		ret = sci_rx_पूर्णांकerrupt(irq, ptr);

	/* Error Interrupt */
	अगर ((ssr_status & SCxSR_ERRORS(port)) && err_enabled)
		ret = sci_er_पूर्णांकerrupt(irq, ptr);

	/* Break Interrupt */
	अगर ((ssr_status & SCxSR_BRK(port)) && err_enabled)
		ret = sci_br_पूर्णांकerrupt(irq, ptr);

	/* Overrun Interrupt */
	अगर (orer_status & s->params->overrun_mask) अणु
		sci_handle_fअगरo_overrun(port);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sci_irq_desc अणु
	स्थिर अक्षर	*desc;
	irq_handler_t	handler;
पूर्ण sci_irq_desc[] = अणु
	/*
	 * Split out handlers, the शेष हाल.
	 */
	[SCIx_ERI_IRQ] = अणु
		.desc = "rx err",
		.handler = sci_er_पूर्णांकerrupt,
	पूर्ण,

	[SCIx_RXI_IRQ] = अणु
		.desc = "rx full",
		.handler = sci_rx_पूर्णांकerrupt,
	पूर्ण,

	[SCIx_TXI_IRQ] = अणु
		.desc = "tx empty",
		.handler = sci_tx_पूर्णांकerrupt,
	पूर्ण,

	[SCIx_BRI_IRQ] = अणु
		.desc = "break",
		.handler = sci_br_पूर्णांकerrupt,
	पूर्ण,

	[SCIx_DRI_IRQ] = अणु
		.desc = "rx ready",
		.handler = sci_rx_पूर्णांकerrupt,
	पूर्ण,

	[SCIx_TEI_IRQ] = अणु
		.desc = "tx end",
		.handler = sci_tx_पूर्णांकerrupt,
	पूर्ण,

	/*
	 * Special muxed handler.
	 */
	[SCIx_MUX_IRQ] = अणु
		.desc = "mux",
		.handler = sci_mpxed_पूर्णांकerrupt,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sci_request_irq(काष्ठा sci_port *port)
अणु
	काष्ठा uart_port *up = &port->port;
	पूर्णांक i, j, w, ret = 0;

	क्रम (i = j = 0; i < SCIx_NR_IRQS; i++, j++) अणु
		स्थिर काष्ठा sci_irq_desc *desc;
		पूर्णांक irq;

		/* Check अगर alपढ़ोy रेजिस्टरed (muxed) */
		क्रम (w = 0; w < i; w++)
			अगर (port->irqs[w] == port->irqs[i])
				w = i + 1;
		अगर (w > i)
			जारी;

		अगर (SCIx_IRQ_IS_MUXED(port)) अणु
			i = SCIx_MUX_IRQ;
			irq = up->irq;
		पूर्ण अन्यथा अणु
			irq = port->irqs[i];

			/*
			 * Certain port types won't support all of the
			 * available पूर्णांकerrupt sources.
			 */
			अगर (unlikely(irq < 0))
				जारी;
		पूर्ण

		desc = sci_irq_desc + i;
		port->irqstr[j] = kaप्र_लिखो(GFP_KERNEL, "%s:%s",
					    dev_name(up->dev), desc->desc);
		अगर (!port->irqstr[j]) अणु
			ret = -ENOMEM;
			जाओ out_nomem;
		पूर्ण

		ret = request_irq(irq, desc->handler, up->irqflags,
				  port->irqstr[j], port);
		अगर (unlikely(ret)) अणु
			dev_err(up->dev, "Can't allocate %s IRQ\n", desc->desc);
			जाओ out_noirq;
		पूर्ण
	पूर्ण

	वापस 0;

out_noirq:
	जबतक (--i >= 0)
		मुक्त_irq(port->irqs[i], port);

out_nomem:
	जबतक (--j >= 0)
		kमुक्त(port->irqstr[j]);

	वापस ret;
पूर्ण

अटल व्योम sci_मुक्त_irq(काष्ठा sci_port *port)
अणु
	पूर्णांक i, j;

	/*
	 * Intentionally in reverse order so we iterate over the muxed
	 * IRQ first.
	 */
	क्रम (i = 0; i < SCIx_NR_IRQS; i++) अणु
		पूर्णांक irq = port->irqs[i];

		/*
		 * Certain port types won't support all of the available
		 * पूर्णांकerrupt sources.
		 */
		अगर (unlikely(irq < 0))
			जारी;

		/* Check अगर alपढ़ोy मुक्तd (irq was muxed) */
		क्रम (j = 0; j < i; j++)
			अगर (port->irqs[j] == irq)
				j = i + 1;
		अगर (j > i)
			जारी;

		मुक्त_irq(port->irqs[i], port);
		kमुक्त(port->irqstr[i]);

		अगर (SCIx_IRQ_IS_MUXED(port)) अणु
			/* If there's only one IRQ, we're करोne. */
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक sci_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित लघु status = serial_port_in(port, SCxSR);
	अचिन्हित लघु in_tx_fअगरo = sci_txfill(port);

	वापस (status & SCxSR_TEND(port)) && !in_tx_fअगरo ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम sci_set_rts(काष्ठा uart_port *port, bool state)
अणु
	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		u16 data = serial_port_in(port, SCPDR);

		/* Active low */
		अगर (state)
			data &= ~SCPDR_RTSD;
		अन्यथा
			data |= SCPDR_RTSD;
		serial_port_out(port, SCPDR, data);

		/* RTS# is output */
		serial_port_out(port, SCPCR,
				serial_port_in(port, SCPCR) | SCPCR_RTSC);
	पूर्ण अन्यथा अगर (sci_getreg(port, SCSPTR)->size) अणु
		u16 ctrl = serial_port_in(port, SCSPTR);

		/* Active low */
		अगर (state)
			ctrl &= ~SCSPTR_RTSDT;
		अन्यथा
			ctrl |= SCSPTR_RTSDT;
		serial_port_out(port, SCSPTR, ctrl);
	पूर्ण
पूर्ण

अटल bool sci_get_cts(काष्ठा uart_port *port)
अणु
	अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
		/* Active low */
		वापस !(serial_port_in(port, SCPDR) & SCPDR_CTSD);
	पूर्ण अन्यथा अगर (sci_getreg(port, SCSPTR)->size) अणु
		/* Active low */
		वापस !(serial_port_in(port, SCSPTR) & SCSPTR_CTSDT);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Modem control is a bit of a mixed bag क्रम SCI(F) ports. Generally
 * CTS/RTS is supported in hardware by at least one port and controlled
 * via SCSPTR (SCxPCR क्रम SCIFA/B parts), or बाह्यal pins (presently
 * handled via the ->init_pins() op, which is a bit of a one-way street,
 * lacking any ability to defer pin control -- this will later be
 * converted over to the GPIO framework).
 *
 * Other modes (such as loopback) are supported generically on certain
 * port types, but not others. For these it's sufficient to test क्रम the
 * existence of the support रेजिस्टर and simply ignore the port type.
 */
अटल व्योम sci_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sci_port *s = to_sci_port(port);

	अगर (mctrl & TIOCM_LOOP) अणु
		स्थिर काष्ठा plat_sci_reg *reg;

		/*
		 * Standard loopback mode क्रम SCFCR ports.
		 */
		reg = sci_getreg(port, SCFCR);
		अगर (reg->size)
			serial_port_out(port, SCFCR,
					serial_port_in(port, SCFCR) |
					SCFCR_LOOP);
	पूर्ण

	mctrl_gpio_set(s->gpios, mctrl);

	अगर (!s->has_rtscts)
		वापस;

	अगर (!(mctrl & TIOCM_RTS)) अणु
		/* Disable Auto RTS */
		serial_port_out(port, SCFCR,
				serial_port_in(port, SCFCR) & ~SCFCR_MCE);

		/* Clear RTS */
		sci_set_rts(port, 0);
	पूर्ण अन्यथा अगर (s->स्वतःrts) अणु
		अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB) अणु
			/* Enable RTS# pin function */
			serial_port_out(port, SCPCR,
				serial_port_in(port, SCPCR) & ~SCPCR_RTSC);
		पूर्ण

		/* Enable Auto RTS */
		serial_port_out(port, SCFCR,
				serial_port_in(port, SCFCR) | SCFCR_MCE);
	पूर्ण अन्यथा अणु
		/* Set RTS */
		sci_set_rts(port, 1);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक sci_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	काष्ठा mctrl_gpios *gpios = s->gpios;
	अचिन्हित पूर्णांक mctrl = 0;

	mctrl_gpio_get(gpios, &mctrl);

	/*
	 * CTS/RTS is handled in hardware when supported, जबतक nothing
	 * अन्यथा is wired up.
	 */
	अगर (s->स्वतःrts) अणु
		अगर (sci_get_cts(port))
			mctrl |= TIOCM_CTS;
	पूर्ण अन्यथा अगर (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_CTS)) अणु
		mctrl |= TIOCM_CTS;
	पूर्ण
	अगर (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_DSR))
		mctrl |= TIOCM_DSR;
	अगर (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_DCD))
		mctrl |= TIOCM_CAR;

	वापस mctrl;
पूर्ण

अटल व्योम sci_enable_ms(काष्ठा uart_port *port)
अणु
	mctrl_gpio_enable_ms(to_sci_port(port)->gpios);
पूर्ण

अटल व्योम sci_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित लघु scscr, scsptr;
	अचिन्हित दीर्घ flags;

	/* check whether the port has SCSPTR */
	अगर (!sci_getreg(port, SCSPTR)->size) अणु
		/*
		 * Not supported by hardware. Most parts couple अवरोध and rx
		 * पूर्णांकerrupts together, with अवरोध detection always enabled.
		 */
		वापस;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);
	scsptr = serial_port_in(port, SCSPTR);
	scscr = serial_port_in(port, SCSCR);

	अगर (अवरोध_state == -1) अणु
		scsptr = (scsptr | SCSPTR_SPB2IO) & ~SCSPTR_SPB2DT;
		scscr &= ~SCSCR_TE;
	पूर्ण अन्यथा अणु
		scsptr = (scsptr | SCSPTR_SPB2DT) & ~SCSPTR_SPB2IO;
		scscr |= SCSCR_TE;
	पूर्ण

	serial_port_out(port, SCSPTR, scsptr);
	serial_port_out(port, SCSCR, scscr);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक sci_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	पूर्णांक ret;

	dev_dbg(port->dev, "%s(%d)\n", __func__, port->line);

	sci_request_dma(port);

	ret = sci_request_irq(s);
	अगर (unlikely(ret < 0)) अणु
		sci_मुक्त_dma(port);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sci_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *s = to_sci_port(port);
	अचिन्हित दीर्घ flags;
	u16 scr;

	dev_dbg(port->dev, "%s(%d)\n", __func__, port->line);

	s->स्वतःrts = false;
	mctrl_gpio_disable_ms(to_sci_port(port)->gpios);

	spin_lock_irqsave(&port->lock, flags);
	sci_stop_rx(port);
	sci_stop_tx(port);
	/*
	 * Stop RX and TX, disable related पूर्णांकerrupts, keep घड़ी source
	 * and HSCIF TOT bits
	 */
	scr = serial_port_in(port, SCSCR);
	serial_port_out(port, SCSCR, scr &
			(SCSCR_CKE1 | SCSCR_CKE0 | s->hscअगर_tot));
	spin_unlock_irqrestore(&port->lock, flags);

#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
	अगर (s->chan_rx_saved) अणु
		dev_dbg(port->dev, "%s(%d) deleting rx_timer\n", __func__,
			port->line);
		hrसमयr_cancel(&s->rx_समयr);
	पूर्ण
#पूर्ण_अगर

	अगर (s->rx_trigger > 1 && s->rx_fअगरo_समयout > 0)
		del_समयr_sync(&s->rx_fअगरo_समयr);
	sci_मुक्त_irq(s);
	sci_मुक्त_dma(port);
पूर्ण

अटल पूर्णांक sci_sck_calc(काष्ठा sci_port *s, अचिन्हित पूर्णांक bps,
			अचिन्हित पूर्णांक *srr)
अणु
	अचिन्हित दीर्घ freq = s->clk_rates[SCI_SCK];
	पूर्णांक err, min_err = पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sr;

	अगर (s->port.type != PORT_HSCIF)
		freq *= 2;

	क्रम_each_sr(sr, s) अणु
		err = DIV_ROUND_CLOSEST(freq, sr) - bps;
		अगर (असल(err) >= असल(min_err))
			जारी;

		min_err = err;
		*srr = sr - 1;

		अगर (!err)
			अवरोध;
	पूर्ण

	dev_dbg(s->port.dev, "SCK: %u%+d bps using SR %u\n", bps, min_err,
		*srr + 1);
	वापस min_err;
पूर्ण

अटल पूर्णांक sci_brg_calc(काष्ठा sci_port *s, अचिन्हित पूर्णांक bps,
			अचिन्हित दीर्घ freq, अचिन्हित पूर्णांक *dlr,
			अचिन्हित पूर्णांक *srr)
अणु
	पूर्णांक err, min_err = पूर्णांक_उच्च;
	अचिन्हित पूर्णांक sr, dl;

	अगर (s->port.type != PORT_HSCIF)
		freq *= 2;

	क्रम_each_sr(sr, s) अणु
		dl = DIV_ROUND_CLOSEST(freq, sr * bps);
		dl = clamp(dl, 1U, 65535U);

		err = DIV_ROUND_CLOSEST(freq, sr * dl) - bps;
		अगर (असल(err) >= असल(min_err))
			जारी;

		min_err = err;
		*dlr = dl;
		*srr = sr - 1;

		अगर (!err)
			अवरोध;
	पूर्ण

	dev_dbg(s->port.dev, "BRG: %u%+d bps using DL %u SR %u\n", bps,
		min_err, *dlr, *srr + 1);
	वापस min_err;
पूर्ण

/* calculate sample rate, BRR, and घड़ी select */
अटल पूर्णांक sci_scbrr_calc(काष्ठा sci_port *s, अचिन्हित पूर्णांक bps,
			  अचिन्हित पूर्णांक *brr, अचिन्हित पूर्णांक *srr,
			  अचिन्हित पूर्णांक *cks)
अणु
	अचिन्हित दीर्घ freq = s->clk_rates[SCI_FCK];
	अचिन्हित पूर्णांक sr, br, preभाग, scrate, c;
	पूर्णांक err, min_err = पूर्णांक_उच्च;

	अगर (s->port.type != PORT_HSCIF)
		freq *= 2;

	/*
	 * Find the combination of sample rate and घड़ी select with the
	 * smallest deviation from the desired baud rate.
	 * Prefer high sample rates to maximise the receive margin.
	 *
	 * M: Receive margin (%)
	 * N: Ratio of bit rate to घड़ी (N = sampling rate)
	 * D: Clock duty (D = 0 to 1.0)
	 * L: Frame length (L = 9 to 12)
	 * F: Absolute value of घड़ी frequency deviation
	 *
	 *  M = |(0.5 - 1 / 2 * N) - ((L - 0.5) * F) -
	 *      (|D - 0.5| / N * (1 + F))|
	 *  NOTE: Usually, treat D क्रम 0.5, F is 0 by this calculation.
	 */
	क्रम_each_sr(sr, s) अणु
		क्रम (c = 0; c <= 3; c++) अणु
			/* पूर्णांकegerized क्रमmulas from HSCIF करोcumentation */
			preभाग = sr * (1 << (2 * c + 1));

			/*
			 * We need to calculate:
			 *
			 *     br = freq / (preभाग * bps) clamped to [1..256]
			 *     err = freq / (br * preभाग) - bps
			 *
			 * Watch out क्रम overflow when calculating the desired
			 * sampling घड़ी rate!
			 */
			अगर (bps > अच_पूर्णांक_उच्च / preभाग)
				अवरोध;

			scrate = preभाग * bps;
			br = DIV_ROUND_CLOSEST(freq, scrate);
			br = clamp(br, 1U, 256U);

			err = DIV_ROUND_CLOSEST(freq, br * preभाग) - bps;
			अगर (असल(err) >= असल(min_err))
				जारी;

			min_err = err;
			*brr = br - 1;
			*srr = sr - 1;
			*cks = c;

			अगर (!err)
				जाओ found;
		पूर्ण
	पूर्ण

found:
	dev_dbg(s->port.dev, "BRR: %u%+d bps using N %u SR %u cks %u\n", bps,
		min_err, *brr, *srr + 1, *cks);
	वापस min_err;
पूर्ण

अटल व्योम sci_reset(काष्ठा uart_port *port)
अणु
	स्थिर काष्ठा plat_sci_reg *reg;
	अचिन्हित पूर्णांक status;
	काष्ठा sci_port *s = to_sci_port(port);

	serial_port_out(port, SCSCR, s->hscअगर_tot);	/* TE=0, RE=0, CKE1=0 */

	reg = sci_getreg(port, SCFCR);
	अगर (reg->size)
		serial_port_out(port, SCFCR, SCFCR_RFRST | SCFCR_TFRST);

	sci_clear_SCxSR(port,
			SCxSR_RDxF_CLEAR(port) & SCxSR_ERROR_CLEAR(port) &
			SCxSR_BREAK_CLEAR(port));
	अगर (sci_getreg(port, SCLSR)->size) अणु
		status = serial_port_in(port, SCLSR);
		status &= ~(SCLSR_TO | SCLSR_ORER);
		serial_port_out(port, SCLSR, status);
	पूर्ण

	अगर (s->rx_trigger > 1) अणु
		अगर (s->rx_fअगरo_समयout) अणु
			scअगर_set_rtrg(port, 1);
			समयr_setup(&s->rx_fअगरo_समयr, rx_fअगरo_समयr_fn, 0);
		पूर्ण अन्यथा अणु
			अगर (port->type == PORT_SCIFA ||
			    port->type == PORT_SCIFB)
				scअगर_set_rtrg(port, 1);
			अन्यथा
				scअगर_set_rtrg(port, s->rx_trigger);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sci_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud, smr_val = SCSMR_ASYNC, scr_val = 0, i, bits;
	अचिन्हित पूर्णांक brr = 255, cks = 0, srr = 15, dl = 0, sccks = 0;
	अचिन्हित पूर्णांक brr1 = 255, cks1 = 0, srr1 = 15, dl1 = 0;
	काष्ठा sci_port *s = to_sci_port(port);
	स्थिर काष्ठा plat_sci_reg *reg;
	पूर्णांक min_err = पूर्णांक_उच्च, err;
	अचिन्हित दीर्घ max_freq = 0;
	पूर्णांक best_clk = -1;
	अचिन्हित दीर्घ flags;

	अगर ((termios->c_cflag & CSIZE) == CS7)
		smr_val |= SCSMR_CHR;
	अगर (termios->c_cflag & PARENB)
		smr_val |= SCSMR_PE;
	अगर (termios->c_cflag & PARODD)
		smr_val |= SCSMR_PE | SCSMR_ODD;
	अगर (termios->c_cflag & CSTOPB)
		smr_val |= SCSMR_STOP;

	/*
	 * earlyprपूर्णांकk comes here early on with port->uartclk set to zero.
	 * the घड़ी framework is not up and running at this poपूर्णांक so here
	 * we assume that 115200 is the maximum baud rate. please note that
	 * the baud rate is not programmed during earlyprपूर्णांकk - it is assumed
	 * that the previous boot loader has enabled required घड़ीs and
	 * setup the baud rate generator hardware क्रम us alपढ़ोy.
	 */
	अगर (!port->uartclk) अणु
		baud = uart_get_baud_rate(port, termios, old, 0, 115200);
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < SCI_NUM_CLKS; i++)
		max_freq = max(max_freq, s->clk_rates[i]);

	baud = uart_get_baud_rate(port, termios, old, 0, max_freq / min_sr(s));
	अगर (!baud)
		जाओ करोne;

	/*
	 * There can be multiple sources क्रम the sampling घड़ी.  Find the one
	 * that gives us the smallest deviation from the desired baud rate.
	 */

	/* Optional Unभागided External Clock */
	अगर (s->clk_rates[SCI_SCK] && port->type != PORT_SCIFA &&
	    port->type != PORT_SCIFB) अणु
		err = sci_sck_calc(s, baud, &srr1);
		अगर (असल(err) < असल(min_err)) अणु
			best_clk = SCI_SCK;
			scr_val = SCSCR_CKE1;
			sccks = SCCKS_CKS;
			min_err = err;
			srr = srr1;
			अगर (!err)
				जाओ करोne;
		पूर्ण
	पूर्ण

	/* Optional BRG Frequency Divided External Clock */
	अगर (s->clk_rates[SCI_SCIF_CLK] && sci_getreg(port, SCDL)->size) अणु
		err = sci_brg_calc(s, baud, s->clk_rates[SCI_SCIF_CLK], &dl1,
				   &srr1);
		अगर (असल(err) < असल(min_err)) अणु
			best_clk = SCI_SCIF_CLK;
			scr_val = SCSCR_CKE1;
			sccks = 0;
			min_err = err;
			dl = dl1;
			srr = srr1;
			अगर (!err)
				जाओ करोne;
		पूर्ण
	पूर्ण

	/* Optional BRG Frequency Divided Internal Clock */
	अगर (s->clk_rates[SCI_BRG_INT] && sci_getreg(port, SCDL)->size) अणु
		err = sci_brg_calc(s, baud, s->clk_rates[SCI_BRG_INT], &dl1,
				   &srr1);
		अगर (असल(err) < असल(min_err)) अणु
			best_clk = SCI_BRG_INT;
			scr_val = SCSCR_CKE1;
			sccks = SCCKS_XIN;
			min_err = err;
			dl = dl1;
			srr = srr1;
			अगर (!min_err)
				जाओ करोne;
		पूर्ण
	पूर्ण

	/* Divided Functional Clock using standard Bit Rate Register */
	err = sci_scbrr_calc(s, baud, &brr1, &srr1, &cks1);
	अगर (असल(err) < असल(min_err)) अणु
		best_clk = SCI_FCK;
		scr_val = 0;
		min_err = err;
		brr = brr1;
		srr = srr1;
		cks = cks1;
	पूर्ण

करोne:
	अगर (best_clk >= 0)
		dev_dbg(port->dev, "Using clk %pC for %u%+d bps\n",
			s->clks[best_clk], baud, min_err);

	sci_port_enable(s);

	/*
	 * Program the optional External Baud Rate Generator (BRG) first.
	 * It controls the mux to select (H)SCK or frequency भागided घड़ी.
	 */
	अगर (best_clk >= 0 && sci_getreg(port, SCCKS)->size) अणु
		serial_port_out(port, SCDL, dl);
		serial_port_out(port, SCCKS, sccks);
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	sci_reset(port);

	uart_update_समयout(port, termios->c_cflag, baud);

	/* byte size and parity */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		bits = 7;
		अवरोध;
	हाल CS6:
		bits = 8;
		अवरोध;
	हाल CS7:
		bits = 9;
		अवरोध;
	शेष:
		bits = 10;
		अवरोध;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		bits++;
	अगर (termios->c_cflag & PARENB)
		bits++;

	अगर (best_clk >= 0) अणु
		अगर (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
			चयन (srr + 1) अणु
			हाल 5:  smr_val |= SCSMR_SRC_5;  अवरोध;
			हाल 7:  smr_val |= SCSMR_SRC_7;  अवरोध;
			हाल 11: smr_val |= SCSMR_SRC_11; अवरोध;
			हाल 13: smr_val |= SCSMR_SRC_13; अवरोध;
			हाल 16: smr_val |= SCSMR_SRC_16; अवरोध;
			हाल 17: smr_val |= SCSMR_SRC_17; अवरोध;
			हाल 19: smr_val |= SCSMR_SRC_19; अवरोध;
			हाल 27: smr_val |= SCSMR_SRC_27; अवरोध;
			पूर्ण
		smr_val |= cks;
		serial_port_out(port, SCSCR, scr_val | s->hscअगर_tot);
		serial_port_out(port, SCSMR, smr_val);
		serial_port_out(port, SCBRR, brr);
		अगर (sci_getreg(port, HSSRR)->size) अणु
			अचिन्हित पूर्णांक hssrr = srr | HSCIF_SRE;
			/* Calculate deviation from पूर्णांकended rate at the
			 * center of the last stop bit in sampling घड़ीs.
			 */
			पूर्णांक last_stop = bits * 2 - 1;
			पूर्णांक deviation = DIV_ROUND_CLOSEST(min_err * last_stop *
							  (पूर्णांक)(srr + 1),
							  2 * (पूर्णांक)baud);

			अगर (असल(deviation) >= 2) अणु
				/* At least two sampling घड़ीs off at the
				 * last stop bit; we can increase the error
				 * margin by shअगरting the sampling poपूर्णांक.
				 */
				पूर्णांक shअगरt = clamp(deviation / 2, -8, 7);

				hssrr |= (shअगरt << HSCIF_SRHP_SHIFT) &
					 HSCIF_SRHP_MASK;
				hssrr |= HSCIF_SRDE;
			पूर्ण
			serial_port_out(port, HSSRR, hssrr);
		पूर्ण

		/* Wait one bit पूर्णांकerval */
		udelay((1000000 + (baud - 1)) / baud);
	पूर्ण अन्यथा अणु
		/* Don't touch the bit rate configuration */
		scr_val = s->cfg->scscr & (SCSCR_CKE1 | SCSCR_CKE0);
		smr_val |= serial_port_in(port, SCSMR) &
			   (SCSMR_CKEDG | SCSMR_SRC_MASK | SCSMR_CKS);
		serial_port_out(port, SCSCR, scr_val | s->hscअगर_tot);
		serial_port_out(port, SCSMR, smr_val);
	पूर्ण

	sci_init_pins(port, termios->c_cflag);

	port->status &= ~UPSTAT_AUTOCTS;
	s->स्वतःrts = false;
	reg = sci_getreg(port, SCFCR);
	अगर (reg->size) अणु
		अचिन्हित लघु ctrl = serial_port_in(port, SCFCR);

		अगर ((port->flags & UPF_HARD_FLOW) &&
		    (termios->c_cflag & CRTSCTS)) अणु
			/* There is no CTS पूर्णांकerrupt to restart the hardware */
			port->status |= UPSTAT_AUTOCTS;
			/* MCE is enabled when RTS is उठाओd */
			s->स्वतःrts = true;
		पूर्ण

		/*
		 * As we've done a sci_reset() above, ensure we don't
		 * पूर्णांकerfere with the FIFOs जबतक toggling MCE. As the
		 * reset values could still be set, simply mask them out.
		 */
		ctrl &= ~(SCFCR_RFRST | SCFCR_TFRST);

		serial_port_out(port, SCFCR, ctrl);
	पूर्ण
	अगर (port->flags & UPF_HARD_FLOW) अणु
		/* Refresh (Auto) RTS */
		sci_set_mctrl(port, port->mctrl);
	पूर्ण

	scr_val |= SCSCR_RE | SCSCR_TE |
		   (s->cfg->scscr & ~(SCSCR_CKE1 | SCSCR_CKE0));
	serial_port_out(port, SCSCR, scr_val | s->hscअगर_tot);
	अगर ((srr + 1 == 5) &&
	    (port->type == PORT_SCIFA || port->type == PORT_SCIFB)) अणु
		/*
		 * In asynchronous mode, when the sampling rate is 1/5, first
		 * received data may become invalid on some SCIFA and SCIFB.
		 * To aव्योम this problem रुको more than 1 serial data समय (1
		 * bit समय x serial data number) after setting SCSCR.RE = 1.
		 */
		udelay(DIV_ROUND_UP(10 * 1000000, baud));
	पूर्ण

	/* Calculate delay क्रम 2 DMA buffers (4 FIFO). */
	s->rx_frame = (10000 * bits) / (baud / 100);
#अगर_घोषित CONFIG_SERIAL_SH_SCI_DMA
	s->rx_समयout = s->buf_len_rx * 2 * s->rx_frame;
#पूर्ण_अगर

	अगर ((termios->c_cflag & CREAD) != 0)
		sci_start_rx(port);

	spin_unlock_irqrestore(&port->lock, flags);

	sci_port_disable(s);

	अगर (UART_ENABLE_MS(port, termios->c_cflag))
		sci_enable_ms(port);
पूर्ण

अटल व्योम sci_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		   अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा sci_port *sci_port = to_sci_port(port);

	चयन (state) अणु
	हाल UART_PM_STATE_OFF:
		sci_port_disable(sci_port);
		अवरोध;
	शेष:
		sci_port_enable(sci_port);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *sci_type(काष्ठा uart_port *port)
अणु
	चयन (port->type) अणु
	हाल PORT_IRDA:
		वापस "irda";
	हाल PORT_SCI:
		वापस "sci";
	हाल PORT_SCIF:
		वापस "scif";
	हाल PORT_SCIFA:
		वापस "scifa";
	हाल PORT_SCIFB:
		वापस "scifb";
	हाल PORT_HSCIF:
		वापस "hscif";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sci_remap_port(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *sport = to_sci_port(port);

	/*
	 * Nothing to करो अगर there's alपढ़ोy an established membase.
	 */
	अगर (port->membase)
		वापस 0;

	अगर (port->dev->of_node || (port->flags & UPF_IOREMAP)) अणु
		port->membase = ioremap(port->mapbase, sport->reg_size);
		अगर (unlikely(!port->membase)) अणु
			dev_err(port->dev, "can't remap port#%d\n", port->line);
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For the simple (and majority of) हालs where we करोn't
		 * need to करो any remapping, just cast the cookie
		 * directly.
		 */
		port->membase = (व्योम __iomem *)(uपूर्णांकptr_t)port->mapbase;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sci_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा sci_port *sport = to_sci_port(port);

	अगर (port->dev->of_node || (port->flags & UPF_IOREMAP)) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण

	release_mem_region(port->mapbase, sport->reg_size);
पूर्ण

अटल पूर्णांक sci_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा resource *res;
	काष्ठा sci_port *sport = to_sci_port(port);
	पूर्णांक ret;

	res = request_mem_region(port->mapbase, sport->reg_size,
				 dev_name(port->dev));
	अगर (unlikely(res == शून्य)) अणु
		dev_err(port->dev, "request_mem_region failed.");
		वापस -EBUSY;
	पूर्ण

	ret = sci_remap_port(port);
	अगर (unlikely(ret != 0)) अणु
		release_resource(res);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sci_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		काष्ठा sci_port *sport = to_sci_port(port);

		port->type = sport->cfg->type;
		sci_request_port(port);
	पूर्ण
पूर्ण

अटल पूर्णांक sci_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->baud_base < 2400)
		/* No paper tape पढ़ोer क्रम Mitch.. */
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops sci_uart_ops = अणु
	.tx_empty	= sci_tx_empty,
	.set_mctrl	= sci_set_mctrl,
	.get_mctrl	= sci_get_mctrl,
	.start_tx	= sci_start_tx,
	.stop_tx	= sci_stop_tx,
	.stop_rx	= sci_stop_rx,
	.enable_ms	= sci_enable_ms,
	.अवरोध_ctl	= sci_अवरोध_ctl,
	.startup	= sci_startup,
	.shutकरोwn	= sci_shutकरोwn,
	.flush_buffer	= sci_flush_buffer,
	.set_termios	= sci_set_termios,
	.pm		= sci_pm,
	.type		= sci_type,
	.release_port	= sci_release_port,
	.request_port	= sci_request_port,
	.config_port	= sci_config_port,
	.verअगरy_port	= sci_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= sci_poll_get_अक्षर,
	.poll_put_अक्षर	= sci_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sci_init_घड़ीs(काष्ठा sci_port *sci_port, काष्ठा device *dev)
अणु
	स्थिर अक्षर *clk_names[] = अणु
		[SCI_FCK] = "fck",
		[SCI_SCK] = "sck",
		[SCI_BRG_INT] = "brg_int",
		[SCI_SCIF_CLK] = "scif_clk",
	पूर्ण;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	अगर (sci_port->cfg->type == PORT_HSCIF)
		clk_names[SCI_SCK] = "hsck";

	क्रम (i = 0; i < SCI_NUM_CLKS; i++) अणु
		clk = devm_clk_get(dev, clk_names[i]);
		अगर (PTR_ERR(clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		अगर (IS_ERR(clk) && i == SCI_FCK) अणु
			/*
			 * "fck" used to be called "sci_ick", and we need to
			 * मुख्यtain DT backward compatibility.
			 */
			clk = devm_clk_get(dev, "sci_ick");
			अगर (PTR_ERR(clk) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;

			अगर (!IS_ERR(clk))
				जाओ found;

			/*
			 * Not all SH platक्रमms declare a घड़ी lookup entry
			 * क्रम SCI devices, in which हाल we need to get the
			 * global "peripheral_clk" घड़ी.
			 */
			clk = devm_clk_get(dev, "peripheral_clk");
			अगर (!IS_ERR(clk))
				जाओ found;

			dev_err(dev, "failed to get %s (%ld)\n", clk_names[i],
				PTR_ERR(clk));
			वापस PTR_ERR(clk);
		पूर्ण

found:
		अगर (IS_ERR(clk))
			dev_dbg(dev, "failed to get %s (%ld)\n", clk_names[i],
				PTR_ERR(clk));
		अन्यथा
			dev_dbg(dev, "clk %s is %pC rate %lu\n", clk_names[i],
				clk, clk_get_rate(clk));
		sci_port->clks[i] = IS_ERR(clk) ? शून्य : clk;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sci_port_params *
sci_probe_regmap(स्थिर काष्ठा plat_sci_port *cfg)
अणु
	अचिन्हित पूर्णांक regtype;

	अगर (cfg->regtype != SCIx_PROBE_REGTYPE)
		वापस &sci_port_params[cfg->regtype];

	चयन (cfg->type) अणु
	हाल PORT_SCI:
		regtype = SCIx_SCI_REGTYPE;
		अवरोध;
	हाल PORT_IRDA:
		regtype = SCIx_IRDA_REGTYPE;
		अवरोध;
	हाल PORT_SCIFA:
		regtype = SCIx_SCIFA_REGTYPE;
		अवरोध;
	हाल PORT_SCIFB:
		regtype = SCIx_SCIFB_REGTYPE;
		अवरोध;
	हाल PORT_SCIF:
		/*
		 * The SH-4 is a bit of a misnomer here, although that's
		 * where this particular port layout originated. This
		 * configuration (or some slight variation thereof)
		 * reमुख्यs the करोminant model क्रम all SCIFs.
		 */
		regtype = SCIx_SH4_SCIF_REGTYPE;
		अवरोध;
	हाल PORT_HSCIF:
		regtype = SCIx_HSCIF_REGTYPE;
		अवरोध;
	शेष:
		pr_err("Can't probe register map for given port\n");
		वापस शून्य;
	पूर्ण

	वापस &sci_port_params[regtype];
पूर्ण

अटल पूर्णांक sci_init_single(काष्ठा platक्रमm_device *dev,
			   काष्ठा sci_port *sci_port, अचिन्हित पूर्णांक index,
			   स्थिर काष्ठा plat_sci_port *p, bool early)
अणु
	काष्ठा uart_port *port = &sci_port->port;
	स्थिर काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	sci_port->cfg	= p;

	port->ops	= &sci_uart_ops;
	port->iotype	= UPIO_MEM;
	port->line	= index;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_SH_SCI_CONSOLE);

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (res == शून्य)
		वापस -ENOMEM;

	port->mapbase = res->start;
	sci_port->reg_size = resource_size(res);

	क्रम (i = 0; i < ARRAY_SIZE(sci_port->irqs); ++i) अणु
		अगर (i)
			sci_port->irqs[i] = platक्रमm_get_irq_optional(dev, i);
		अन्यथा
			sci_port->irqs[i] = platक्रमm_get_irq(dev, i);
	पूर्ण

	/* The SCI generates several पूर्णांकerrupts. They can be muxed together or
	 * connected to dअगरferent पूर्णांकerrupt lines. In the muxed हाल only one
	 * पूर्णांकerrupt resource is specअगरied as there is only one पूर्णांकerrupt ID.
	 * In the non-muxed हाल, up to 6 पूर्णांकerrupt संकेतs might be generated
	 * from the SCI, however those संकेतs might have their own inभागidual
	 * पूर्णांकerrupt ID numbers, or muxed together with another पूर्णांकerrupt.
	 */
	अगर (sci_port->irqs[0] < 0)
		वापस -ENXIO;

	अगर (sci_port->irqs[1] < 0)
		क्रम (i = 1; i < ARRAY_SIZE(sci_port->irqs); i++)
			sci_port->irqs[i] = sci_port->irqs[0];

	sci_port->params = sci_probe_regmap(p);
	अगर (unlikely(sci_port->params == शून्य))
		वापस -EINVAL;

	चयन (p->type) अणु
	हाल PORT_SCIFB:
		sci_port->rx_trigger = 48;
		अवरोध;
	हाल PORT_HSCIF:
		sci_port->rx_trigger = 64;
		अवरोध;
	हाल PORT_SCIFA:
		sci_port->rx_trigger = 32;
		अवरोध;
	हाल PORT_SCIF:
		अगर (p->regtype == SCIx_SH7705_SCIF_REGTYPE)
			/* RX triggering not implemented क्रम this IP */
			sci_port->rx_trigger = 1;
		अन्यथा
			sci_port->rx_trigger = 8;
		अवरोध;
	शेष:
		sci_port->rx_trigger = 1;
		अवरोध;
	पूर्ण

	sci_port->rx_fअगरo_समयout = 0;
	sci_port->hscअगर_tot = 0;

	/* SCIFA on sh7723 and sh7724 need a custom sampling rate that करोesn't
	 * match the SoC datasheet, this should be investigated. Let platक्रमm
	 * data override the sampling rate क्रम now.
	 */
	sci_port->sampling_rate_mask = p->sampling_rate
				     ? SCI_SR(p->sampling_rate)
				     : sci_port->params->sampling_rate_mask;

	अगर (!early) अणु
		ret = sci_init_घड़ीs(sci_port, &dev->dev);
		अगर (ret < 0)
			वापस ret;

		port->dev = &dev->dev;

		pm_runसमय_enable(&dev->dev);
	पूर्ण

	port->type		= p->type;
	port->flags		= UPF_FIXED_PORT | UPF_BOOT_AUTOCONF | p->flags;
	port->fअगरosize		= sci_port->params->fअगरosize;

	अगर (port->type == PORT_SCI) अणु
		अगर (sci_port->reg_size >= 0x20)
			port->regshअगरt = 2;
		अन्यथा
			port->regshअगरt = 1;
	पूर्ण

	/*
	 * The UART port needs an IRQ value, so we peg this to the RX IRQ
	 * क्रम the multi-IRQ ports, which is where we are primarily
	 * concerned with the shutकरोwn path synchronization.
	 *
	 * For the muxed हाल there's nothing more to करो.
	 */
	port->irq		= sci_port->irqs[SCIx_RXI_IRQ];
	port->irqflags		= 0;

	port->serial_in		= sci_serial_in;
	port->serial_out	= sci_serial_out;

	वापस 0;
पूर्ण

अटल व्योम sci_cleanup_single(काष्ठा sci_port *port)
अणु
	pm_runसमय_disable(port->port.dev);
पूर्ण

#अगर defined(CONFIG_SERIAL_SH_SCI_CONSOLE) || \
    defined(CONFIG_SERIAL_SH_SCI_EARLYCON)
अटल व्योम serial_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	sci_poll_put_अक्षर(port, ch);
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 */
अटल व्योम serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				 अचिन्हित count)
अणु
	काष्ठा sci_port *sci_port = &sci_ports[co->index];
	काष्ठा uart_port *port = &sci_port->port;
	अचिन्हित लघु bits, ctrl, ctrl_temp;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (port->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/* first save SCSCR then disable पूर्णांकerrupts, keep घड़ी source */
	ctrl = serial_port_in(port, SCSCR);
	ctrl_temp = SCSCR_RE | SCSCR_TE |
		    (sci_port->cfg->scscr & ~(SCSCR_CKE1 | SCSCR_CKE0)) |
		    (ctrl & (SCSCR_CKE1 | SCSCR_CKE0));
	serial_port_out(port, SCSCR, ctrl_temp | sci_port->hscअगर_tot);

	uart_console_ग_लिखो(port, s, count, serial_console_अक्षर_दो);

	/* रुको until fअगरo is empty and last bit has been transmitted */
	bits = SCxSR_TDxE(port) | SCxSR_TEND(port);
	जबतक ((serial_port_in(port, SCxSR) & bits) != bits)
		cpu_relax();

	/* restore the SCSCR */
	serial_port_out(port, SCSCR, ctrl);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक serial_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sci_port *sci_port;
	काष्ठा uart_port *port;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	/*
	 * Refuse to handle any bogus ports.
	 */
	अगर (co->index < 0 || co->index >= SCI_NPORTS)
		वापस -ENODEV;

	sci_port = &sci_ports[co->index];
	port = &sci_port->port;

	/*
	 * Refuse to handle uninitialized ports.
	 */
	अगर (!port->ops)
		वापस -ENODEV;

	ret = sci_remap_port(port);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console serial_console = अणु
	.name		= "ttySC",
	.device		= uart_console_device,
	.ग_लिखो		= serial_console_ग_लिखो,
	.setup		= serial_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &sci_uart_driver,
पूर्ण;

#अगर_घोषित CONFIG_SUPERH
अटल काष्ठा console early_serial_console = अणु
	.name           = "early_ttySC",
	.ग_लिखो          = serial_console_ग_लिखो,
	.flags          = CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

अटल अक्षर early_serial_buf[32];

अटल पूर्णांक sci_probe_earlyprपूर्णांकk(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा plat_sci_port *cfg = dev_get_platdata(&pdev->dev);

	अगर (early_serial_console.data)
		वापस -EEXIST;

	early_serial_console.index = pdev->id;

	sci_init_single(pdev, &sci_ports[pdev->id], pdev->id, cfg, true);

	serial_console_setup(&early_serial_console, early_serial_buf);

	अगर (!म_माला(early_serial_buf, "keep"))
		early_serial_console.flags |= CON_BOOT;

	रेजिस्टर_console(&early_serial_console);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा SCI_CONSOLE	(&serial_console)

#अन्यथा
अटल अंतरभूत पूर्णांक sci_probe_earlyprपूर्णांकk(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EINVAL;
पूर्ण

#घोषणा SCI_CONSOLE	शून्य

#पूर्ण_अगर /* CONFIG_SERIAL_SH_SCI_CONSOLE || CONFIG_SERIAL_SH_SCI_EARLYCON */

अटल स्थिर अक्षर banner[] __initस्थिर = "SuperH (H)SCI(F) driver initialized";

अटल DEFINE_MUTEX(sci_uart_registration_lock);
अटल काष्ठा uart_driver sci_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "sci",
	.dev_name	= "ttySC",
	.major		= SCI_MAJOR,
	.minor		= SCI_MINOR_START,
	.nr		= SCI_NPORTS,
	.cons		= SCI_CONSOLE,
पूर्ण;

अटल पूर्णांक sci_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sci_port *port = platक्रमm_get_drvdata(dev);
	अचिन्हित पूर्णांक type = port->port.type;	/* uart_हटाओ_... clears it */

	sci_ports_in_use &= ~BIT(port->port.line);
	uart_हटाओ_one_port(&sci_uart_driver, &port->port);

	sci_cleanup_single(port);

	अगर (port->port.fअगरosize > 1)
		device_हटाओ_file(&dev->dev, &dev_attr_rx_fअगरo_trigger);
	अगर (type == PORT_SCIFA || type == PORT_SCIFB || type == PORT_HSCIF)
		device_हटाओ_file(&dev->dev, &dev_attr_rx_fअगरo_समयout);

	वापस 0;
पूर्ण


#घोषणा SCI_OF_DATA(type, regtype)	(व्योम *)((type) << 16 | (regtype))
#घोषणा SCI_OF_TYPE(data)		((अचिन्हित दीर्घ)(data) >> 16)
#घोषणा SCI_OF_REGTYPE(data)		((अचिन्हित दीर्घ)(data) & 0xffff)

अटल स्थिर काष्ठा of_device_id of_sci_match[] = अणु
	/* SoC-specअगरic types */
	अणु
		.compatible = "renesas,scif-r7s72100",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_SH2_SCIF_FIFODATA_REGTYPE),
	पूर्ण,
	अणु
		.compatible = "renesas,scif-r7s9210",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_RZ_SCIFA_REGTYPE),
	पूर्ण,
	/* Family-specअगरic types */
	अणु
		.compatible = "renesas,rcar-gen1-scif",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_SH4_SCIF_BRG_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen2-scif",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_SH4_SCIF_BRG_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen3-scif",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_SH4_SCIF_BRG_REGTYPE),
	पूर्ण,
	/* Generic types */
	अणु
		.compatible = "renesas,scif",
		.data = SCI_OF_DATA(PORT_SCIF, SCIx_SH4_SCIF_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,scifa",
		.data = SCI_OF_DATA(PORT_SCIFA, SCIx_SCIFA_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,scifb",
		.data = SCI_OF_DATA(PORT_SCIFB, SCIx_SCIFB_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,hscif",
		.data = SCI_OF_DATA(PORT_HSCIF, SCIx_HSCIF_REGTYPE),
	पूर्ण, अणु
		.compatible = "renesas,sci",
		.data = SCI_OF_DATA(PORT_SCI, SCIx_SCI_REGTYPE),
	पूर्ण, अणु
		/* Terminator */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_sci_match);

अटल काष्ठा plat_sci_port *sci_parse_dt(काष्ठा platक्रमm_device *pdev,
					  अचिन्हित पूर्णांक *dev_id)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा plat_sci_port *p;
	काष्ठा sci_port *sp;
	स्थिर व्योम *data;
	पूर्णांक id;

	अगर (!IS_ENABLED(CONFIG_OF) || !np)
		वापस शून्य;

	data = of_device_get_match_data(&pdev->dev);

	p = devm_kzalloc(&pdev->dev, माप(काष्ठा plat_sci_port), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	/* Get the line number from the aliases node. */
	id = of_alias_get_id(np, "serial");
	अगर (id < 0 && ~sci_ports_in_use)
		id = ffz(sci_ports_in_use);
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id (%d)\n", id);
		वापस शून्य;
	पूर्ण
	अगर (id >= ARRAY_SIZE(sci_ports)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n", id);
		वापस शून्य;
	पूर्ण

	sp = &sci_ports[id];
	*dev_id = id;

	p->type = SCI_OF_TYPE(data);
	p->regtype = SCI_OF_REGTYPE(data);

	sp->has_rtscts = of_property_पढ़ो_bool(np, "uart-has-rtscts");

	वापस p;
पूर्ण

अटल पूर्णांक sci_probe_single(काष्ठा platक्रमm_device *dev,
				      अचिन्हित पूर्णांक index,
				      काष्ठा plat_sci_port *p,
				      काष्ठा sci_port *sciport)
अणु
	पूर्णांक ret;

	/* Sanity check */
	अगर (unlikely(index >= SCI_NPORTS)) अणु
		dev_notice(&dev->dev, "Attempting to register port %d when only %d are available\n",
			   index+1, SCI_NPORTS);
		dev_notice(&dev->dev, "Consider bumping CONFIG_SERIAL_SH_SCI_NR_UARTS!\n");
		वापस -EINVAL;
	पूर्ण
	BUILD_BUG_ON(SCI_NPORTS > माप(sci_ports_in_use) * 8);
	अगर (sci_ports_in_use & BIT(index))
		वापस -EBUSY;

	mutex_lock(&sci_uart_registration_lock);
	अगर (!sci_uart_driver.state) अणु
		ret = uart_रेजिस्टर_driver(&sci_uart_driver);
		अगर (ret) अणु
			mutex_unlock(&sci_uart_registration_lock);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&sci_uart_registration_lock);

	ret = sci_init_single(dev, sciport, index, p, false);
	अगर (ret)
		वापस ret;

	sciport->gpios = mctrl_gpio_init(&sciport->port, 0);
	अगर (IS_ERR(sciport->gpios))
		वापस PTR_ERR(sciport->gpios);

	अगर (sciport->has_rtscts) अणु
		अगर (mctrl_gpio_to_gpiod(sciport->gpios, UART_GPIO_CTS) ||
		    mctrl_gpio_to_gpiod(sciport->gpios, UART_GPIO_RTS)) अणु
			dev_err(&dev->dev, "Conflicting RTS/CTS config\n");
			वापस -EINVAL;
		पूर्ण
		sciport->port.flags |= UPF_HARD_FLOW;
	पूर्ण

	ret = uart_add_one_port(&sci_uart_driver, &sciport->port);
	अगर (ret) अणु
		sci_cleanup_single(sciport);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sci_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा plat_sci_port *p;
	काष्ठा sci_port *sp;
	अचिन्हित पूर्णांक dev_id;
	पूर्णांक ret;

	/*
	 * If we've come here via earlyprपूर्णांकk initialization, head off to
	 * the special early probe. We करोn't have sufficient device state
	 * to make it beyond this yet.
	 */
#अगर_घोषित CONFIG_SUPERH
	अगर (is_sh_early_platक्रमm_device(dev))
		वापस sci_probe_earlyprपूर्णांकk(dev);
#पूर्ण_अगर

	अगर (dev->dev.of_node) अणु
		p = sci_parse_dt(dev, &dev_id);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		p = dev->dev.platक्रमm_data;
		अगर (p == शून्य) अणु
			dev_err(&dev->dev, "no platform data supplied\n");
			वापस -EINVAL;
		पूर्ण

		dev_id = dev->id;
	पूर्ण

	sp = &sci_ports[dev_id];
	platक्रमm_set_drvdata(dev, sp);

	ret = sci_probe_single(dev, dev_id, p, sp);
	अगर (ret)
		वापस ret;

	अगर (sp->port.fअगरosize > 1) अणु
		ret = device_create_file(&dev->dev, &dev_attr_rx_fअगरo_trigger);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (sp->port.type == PORT_SCIFA || sp->port.type == PORT_SCIFB ||
	    sp->port.type == PORT_HSCIF) अणु
		ret = device_create_file(&dev->dev, &dev_attr_rx_fअगरo_समयout);
		अगर (ret) अणु
			अगर (sp->port.fअगरosize > 1) अणु
				device_हटाओ_file(&dev->dev,
						   &dev_attr_rx_fअगरo_trigger);
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_SH_STANDARD_BIOS
	sh_bios_gdb_detach();
#पूर्ण_अगर

	sci_ports_in_use |= BIT(dev_id);
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक sci_suspend(काष्ठा device *dev)
अणु
	काष्ठा sci_port *sport = dev_get_drvdata(dev);

	अगर (sport)
		uart_suspend_port(&sci_uart_driver, &sport->port);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक sci_resume(काष्ठा device *dev)
अणु
	काष्ठा sci_port *sport = dev_get_drvdata(dev);

	अगर (sport)
		uart_resume_port(&sci_uart_driver, &sport->port);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sci_dev_pm_ops, sci_suspend, sci_resume);

अटल काष्ठा platक्रमm_driver sci_driver = अणु
	.probe		= sci_probe,
	.हटाओ		= sci_हटाओ,
	.driver		= अणु
		.name	= "sh-sci",
		.pm	= &sci_dev_pm_ops,
		.of_match_table = of_match_ptr(of_sci_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sci_init(व्योम)
अणु
	pr_info("%s\n", banner);

	वापस platक्रमm_driver_रेजिस्टर(&sci_driver);
पूर्ण

अटल व्योम __निकास sci_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sci_driver);

	अगर (sci_uart_driver.state)
		uart_unरेजिस्टर_driver(&sci_uart_driver);
पूर्ण

#अगर defined(CONFIG_SUPERH) && defined(CONFIG_SERIAL_SH_SCI_CONSOLE)
sh_early_platक्रमm_init_buffer("earlyprintk", &sci_driver,
			   early_serial_buf, ARRAY_SIZE(early_serial_buf));
#पूर्ण_अगर
#अगर_घोषित CONFIG_SERIAL_SH_SCI_EARLYCON
अटल काष्ठा plat_sci_port port_cfg __initdata;

अटल पूर्णांक __init early_console_setup(काष्ठा earlycon_device *device,
				      पूर्णांक type)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->port.serial_in = sci_serial_in;
	device->port.serial_out	= sci_serial_out;
	device->port.type = type;
	स_नकल(&sci_ports[0].port, &device->port, माप(काष्ठा uart_port));
	port_cfg.type = type;
	sci_ports[0].cfg = &port_cfg;
	sci_ports[0].params = sci_probe_regmap(&port_cfg);
	port_cfg.scscr = sci_serial_in(&sci_ports[0].port, SCSCR);
	sci_serial_out(&sci_ports[0].port, SCSCR,
		       SCSCR_RE | SCSCR_TE | port_cfg.scscr);

	device->con->ग_लिखो = serial_console_ग_लिखो;
	वापस 0;
पूर्ण
अटल पूर्णांक __init sci_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	वापस early_console_setup(device, PORT_SCI);
पूर्ण
अटल पूर्णांक __init scअगर_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	वापस early_console_setup(device, PORT_SCIF);
पूर्ण
अटल पूर्णांक __init rzscअगरa_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	port_cfg.regtype = SCIx_RZ_SCIFA_REGTYPE;
	वापस early_console_setup(device, PORT_SCIF);
पूर्ण
अटल पूर्णांक __init scअगरa_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	वापस early_console_setup(device, PORT_SCIFA);
पूर्ण
अटल पूर्णांक __init scअगरb_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	वापस early_console_setup(device, PORT_SCIFB);
पूर्ण
अटल पूर्णांक __init hscअगर_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	वापस early_console_setup(device, PORT_HSCIF);
पूर्ण

OF_EARLYCON_DECLARE(sci, "renesas,sci", sci_early_console_setup);
OF_EARLYCON_DECLARE(scअगर, "renesas,scif", scअगर_early_console_setup);
OF_EARLYCON_DECLARE(scअगर, "renesas,scif-r7s9210", rzscअगरa_early_console_setup);
OF_EARLYCON_DECLARE(scअगरa, "renesas,scifa", scअगरa_early_console_setup);
OF_EARLYCON_DECLARE(scअगरb, "renesas,scifb", scअगरb_early_console_setup);
OF_EARLYCON_DECLARE(hscअगर, "renesas,hscif", hscअगर_early_console_setup);
#पूर्ण_अगर /* CONFIG_SERIAL_SH_SCI_EARLYCON */

module_init(sci_init);
module_निकास(sci_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sh-sci");
MODULE_AUTHOR("Paul Mundt");
MODULE_DESCRIPTION("SuperH (H)SCI(F) serial driver");
