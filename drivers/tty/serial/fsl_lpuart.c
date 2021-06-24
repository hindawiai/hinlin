<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Freescale lpuart serial port driver
 *
 *  Copyright 2012-2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_flip.h>

/* All रेजिस्टरs are 8-bit width */
#घोषणा UARTBDH			0x00
#घोषणा UARTBDL			0x01
#घोषणा UARTCR1			0x02
#घोषणा UARTCR2			0x03
#घोषणा UARTSR1			0x04
#घोषणा UARTCR3			0x06
#घोषणा UARTDR			0x07
#घोषणा UARTCR4			0x0a
#घोषणा UARTCR5			0x0b
#घोषणा UARTMODEM		0x0d
#घोषणा UARTPFIFO		0x10
#घोषणा UARTCFIFO		0x11
#घोषणा UARTSFIFO		0x12
#घोषणा UARTTWFIFO		0x13
#घोषणा UARTTCFIFO		0x14
#घोषणा UARTRWFIFO		0x15

#घोषणा UARTBDH_LBKDIE		0x80
#घोषणा UARTBDH_RXEDGIE		0x40
#घोषणा UARTBDH_SBR_MASK	0x1f

#घोषणा UARTCR1_LOOPS		0x80
#घोषणा UARTCR1_RSRC		0x20
#घोषणा UARTCR1_M		0x10
#घोषणा UARTCR1_WAKE		0x08
#घोषणा UARTCR1_ILT		0x04
#घोषणा UARTCR1_PE		0x02
#घोषणा UARTCR1_PT		0x01

#घोषणा UARTCR2_TIE		0x80
#घोषणा UARTCR2_TCIE		0x40
#घोषणा UARTCR2_RIE		0x20
#घोषणा UARTCR2_ILIE		0x10
#घोषणा UARTCR2_TE		0x08
#घोषणा UARTCR2_RE		0x04
#घोषणा UARTCR2_RWU		0x02
#घोषणा UARTCR2_SBK		0x01

#घोषणा UARTSR1_TDRE		0x80
#घोषणा UARTSR1_TC		0x40
#घोषणा UARTSR1_RDRF		0x20
#घोषणा UARTSR1_IDLE		0x10
#घोषणा UARTSR1_OR		0x08
#घोषणा UARTSR1_NF		0x04
#घोषणा UARTSR1_FE		0x02
#घोषणा UARTSR1_PE		0x01

#घोषणा UARTCR3_R8		0x80
#घोषणा UARTCR3_T8		0x40
#घोषणा UARTCR3_TXसूची		0x20
#घोषणा UARTCR3_TXINV		0x10
#घोषणा UARTCR3_ORIE		0x08
#घोषणा UARTCR3_NEIE		0x04
#घोषणा UARTCR3_FEIE		0x02
#घोषणा UARTCR3_PEIE		0x01

#घोषणा UARTCR4_MAEN1		0x80
#घोषणा UARTCR4_MAEN2		0x40
#घोषणा UARTCR4_M10		0x20
#घोषणा UARTCR4_BRFA_MASK	0x1f
#घोषणा UARTCR4_BRFA_OFF	0

#घोषणा UARTCR5_TDMAS		0x80
#घोषणा UARTCR5_RDMAS		0x20

#घोषणा UARTMODEM_RXRTSE	0x08
#घोषणा UARTMODEM_TXRTSPOL	0x04
#घोषणा UARTMODEM_TXRTSE	0x02
#घोषणा UARTMODEM_TXCTSE	0x01

#घोषणा UARTPFIFO_TXFE		0x80
#घोषणा UARTPFIFO_FIFOSIZE_MASK	0x7
#घोषणा UARTPFIFO_TXSIZE_OFF	4
#घोषणा UARTPFIFO_RXFE		0x08
#घोषणा UARTPFIFO_RXSIZE_OFF	0

#घोषणा UARTCFIFO_TXFLUSH	0x80
#घोषणा UARTCFIFO_RXFLUSH	0x40
#घोषणा UARTCFIFO_RXOFE		0x04
#घोषणा UARTCFIFO_TXOFE		0x02
#घोषणा UARTCFIFO_RXUFE		0x01

#घोषणा UARTSFIFO_TXEMPT	0x80
#घोषणा UARTSFIFO_RXEMPT	0x40
#घोषणा UARTSFIFO_RXOF		0x04
#घोषणा UARTSFIFO_TXOF		0x02
#घोषणा UARTSFIFO_RXUF		0x01

/* 32-bit रेजिस्टर definition */
#घोषणा UARTBAUD		0x00
#घोषणा UARTSTAT		0x04
#घोषणा UARTCTRL		0x08
#घोषणा UARTDATA		0x0C
#घोषणा UARTMATCH		0x10
#घोषणा UARTMOसूची		0x14
#घोषणा UARTFIFO		0x18
#घोषणा UARTWATER		0x1c

#घोषणा UARTBAUD_MAEN1		0x80000000
#घोषणा UARTBAUD_MAEN2		0x40000000
#घोषणा UARTBAUD_M10		0x20000000
#घोषणा UARTBAUD_TDMAE		0x00800000
#घोषणा UARTBAUD_RDMAE		0x00200000
#घोषणा UARTBAUD_MATCFG		0x00400000
#घोषणा UARTBAUD_BOTHEDGE	0x00020000
#घोषणा UARTBAUD_RESYNCDIS	0x00010000
#घोषणा UARTBAUD_LBKDIE		0x00008000
#घोषणा UARTBAUD_RXEDGIE	0x00004000
#घोषणा UARTBAUD_SBNS		0x00002000
#घोषणा UARTBAUD_SBR		0x00000000
#घोषणा UARTBAUD_SBR_MASK	0x1fff
#घोषणा UARTBAUD_OSR_MASK       0x1f
#घोषणा UARTBAUD_OSR_SHIFT      24

#घोषणा UARTSTAT_LBKDIF		0x80000000
#घोषणा UARTSTAT_RXEDGIF	0x40000000
#घोषणा UARTSTAT_MSBF		0x20000000
#घोषणा UARTSTAT_RXINV		0x10000000
#घोषणा UARTSTAT_RWUID		0x08000000
#घोषणा UARTSTAT_BRK13		0x04000000
#घोषणा UARTSTAT_LBKDE		0x02000000
#घोषणा UARTSTAT_RAF		0x01000000
#घोषणा UARTSTAT_TDRE		0x00800000
#घोषणा UARTSTAT_TC		0x00400000
#घोषणा UARTSTAT_RDRF		0x00200000
#घोषणा UARTSTAT_IDLE		0x00100000
#घोषणा UARTSTAT_OR		0x00080000
#घोषणा UARTSTAT_NF		0x00040000
#घोषणा UARTSTAT_FE		0x00020000
#घोषणा UARTSTAT_PE		0x00010000
#घोषणा UARTSTAT_MA1F		0x00008000
#घोषणा UARTSTAT_M21F		0x00004000

#घोषणा UARTCTRL_R8T9		0x80000000
#घोषणा UARTCTRL_R9T8		0x40000000
#घोषणा UARTCTRL_TXसूची		0x20000000
#घोषणा UARTCTRL_TXINV		0x10000000
#घोषणा UARTCTRL_ORIE		0x08000000
#घोषणा UARTCTRL_NEIE		0x04000000
#घोषणा UARTCTRL_FEIE		0x02000000
#घोषणा UARTCTRL_PEIE		0x01000000
#घोषणा UARTCTRL_TIE		0x00800000
#घोषणा UARTCTRL_TCIE		0x00400000
#घोषणा UARTCTRL_RIE		0x00200000
#घोषणा UARTCTRL_ILIE		0x00100000
#घोषणा UARTCTRL_TE		0x00080000
#घोषणा UARTCTRL_RE		0x00040000
#घोषणा UARTCTRL_RWU		0x00020000
#घोषणा UARTCTRL_SBK		0x00010000
#घोषणा UARTCTRL_MA1IE		0x00008000
#घोषणा UARTCTRL_MA2IE		0x00004000
#घोषणा UARTCTRL_IDLECFG	0x00000100
#घोषणा UARTCTRL_LOOPS		0x00000080
#घोषणा UARTCTRL_DOZEEN		0x00000040
#घोषणा UARTCTRL_RSRC		0x00000020
#घोषणा UARTCTRL_M		0x00000010
#घोषणा UARTCTRL_WAKE		0x00000008
#घोषणा UARTCTRL_ILT		0x00000004
#घोषणा UARTCTRL_PE		0x00000002
#घोषणा UARTCTRL_PT		0x00000001

#घोषणा UARTDATA_NOISY		0x00008000
#घोषणा UARTDATA_PARITYE	0x00004000
#घोषणा UARTDATA_FRETSC		0x00002000
#घोषणा UARTDATA_RXEMPT		0x00001000
#घोषणा UARTDATA_IDLINE		0x00000800
#घोषणा UARTDATA_MASK		0x3ff

#घोषणा UARTMOसूची_IREN		0x00020000
#घोषणा UARTMOसूची_TXCTSSRC	0x00000020
#घोषणा UARTMOसूची_TXCTSC	0x00000010
#घोषणा UARTMOसूची_RXRTSE	0x00000008
#घोषणा UARTMOसूची_TXRTSPOL	0x00000004
#घोषणा UARTMOसूची_TXRTSE	0x00000002
#घोषणा UARTMOसूची_TXCTSE	0x00000001

#घोषणा UARTFIFO_TXEMPT		0x00800000
#घोषणा UARTFIFO_RXEMPT		0x00400000
#घोषणा UARTFIFO_TXOF		0x00020000
#घोषणा UARTFIFO_RXUF		0x00010000
#घोषणा UARTFIFO_TXFLUSH	0x00008000
#घोषणा UARTFIFO_RXFLUSH	0x00004000
#घोषणा UARTFIFO_TXOFE		0x00000200
#घोषणा UARTFIFO_RXUFE		0x00000100
#घोषणा UARTFIFO_TXFE		0x00000080
#घोषणा UARTFIFO_FIFOSIZE_MASK	0x7
#घोषणा UARTFIFO_TXSIZE_OFF	4
#घोषणा UARTFIFO_RXFE		0x00000008
#घोषणा UARTFIFO_RXSIZE_OFF	0
#घोषणा UARTFIFO_DEPTH(x)	(0x1 << ((x) ? ((x) + 1) : 0))

#घोषणा UARTWATER_COUNT_MASK	0xff
#घोषणा UARTWATER_TXCNT_OFF	8
#घोषणा UARTWATER_RXCNT_OFF	24
#घोषणा UARTWATER_WATER_MASK	0xff
#घोषणा UARTWATER_TXWATER_OFF	0
#घोषणा UARTWATER_RXWATER_OFF	16

/* Rx DMA समयout in ms, which is used to calculate Rx ring buffer size */
#घोषणा DMA_RX_TIMEOUT		(10)

#घोषणा DRIVER_NAME	"fsl-lpuart"
#घोषणा DEV_NAME	"ttyLP"
#घोषणा UART_NR		6

/* IMX lpuart has four extra unused regs located at the beginning */
#घोषणा IMX_REG_OFF	0x10

अटल DEFINE_IDA(fsl_lpuart_ida);

क्रमागत lpuart_type अणु
	VF610_LPUART,
	LS1021A_LPUART,
	LS1028A_LPUART,
	IMX7ULP_LPUART,
	IMX8QXP_LPUART,
पूर्ण;

काष्ठा lpuart_port अणु
	काष्ठा uart_port	port;
	क्रमागत lpuart_type	devtype;
	काष्ठा clk		*ipg_clk;
	काष्ठा clk		*baud_clk;
	अचिन्हित पूर्णांक		txfअगरo_size;
	अचिन्हित पूर्णांक		rxfअगरo_size;

	bool			lpuart_dma_tx_use;
	bool			lpuart_dma_rx_use;
	काष्ठा dma_chan		*dma_tx_chan;
	काष्ठा dma_chan		*dma_rx_chan;
	काष्ठा dma_async_tx_descriptor  *dma_tx_desc;
	काष्ठा dma_async_tx_descriptor  *dma_rx_desc;
	dma_cookie_t		dma_tx_cookie;
	dma_cookie_t		dma_rx_cookie;
	अचिन्हित पूर्णांक		dma_tx_bytes;
	अचिन्हित पूर्णांक		dma_rx_bytes;
	bool			dma_tx_in_progress;
	अचिन्हित पूर्णांक		dma_rx_समयout;
	काष्ठा समयr_list	lpuart_समयr;
	काष्ठा scatterlist	rx_sgl, tx_sgl[2];
	काष्ठा circ_buf		rx_ring;
	पूर्णांक			rx_dma_rng_buf_len;
	अचिन्हित पूर्णांक		dma_tx_nents;
	रुको_queue_head_t	dma_रुको;
	bool			id_allocated;
पूर्ण;

काष्ठा lpuart_soc_data अणु
	क्रमागत lpuart_type devtype;
	अक्षर iotype;
	u8 reg_off;
पूर्ण;

अटल स्थिर काष्ठा lpuart_soc_data vf_data = अणु
	.devtype = VF610_LPUART,
	.iotype = UPIO_MEM,
पूर्ण;

अटल स्थिर काष्ठा lpuart_soc_data ls1021a_data = अणु
	.devtype = LS1021A_LPUART,
	.iotype = UPIO_MEM32BE,
पूर्ण;

अटल स्थिर काष्ठा lpuart_soc_data ls1028a_data = अणु
	.devtype = LS1028A_LPUART,
	.iotype = UPIO_MEM32,
पूर्ण;

अटल काष्ठा lpuart_soc_data imx7ulp_data = अणु
	.devtype = IMX7ULP_LPUART,
	.iotype = UPIO_MEM32,
	.reg_off = IMX_REG_OFF,
पूर्ण;

अटल काष्ठा lpuart_soc_data imx8qxp_data = अणु
	.devtype = IMX8QXP_LPUART,
	.iotype = UPIO_MEM32,
	.reg_off = IMX_REG_OFF,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lpuart_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-lpuart",	.data = &vf_data, पूर्ण,
	अणु .compatible = "fsl,ls1021a-lpuart",	.data = &ls1021a_data, पूर्ण,
	अणु .compatible = "fsl,ls1028a-lpuart",	.data = &ls1028a_data, पूर्ण,
	अणु .compatible = "fsl,imx7ulp-lpuart",	.data = &imx7ulp_data, पूर्ण,
	अणु .compatible = "fsl,imx8qxp-lpuart",	.data = &imx8qxp_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpuart_dt_ids);

/* Forward declare this क्रम the dma callbacks*/
अटल व्योम lpuart_dma_tx_complete(व्योम *arg);

अटल अंतरभूत bool is_layerscape_lpuart(काष्ठा lpuart_port *sport)
अणु
	वापस (sport->devtype == LS1021A_LPUART ||
		sport->devtype == LS1028A_LPUART);
पूर्ण

अटल अंतरभूत bool is_imx8qxp_lpuart(काष्ठा lpuart_port *sport)
अणु
	वापस sport->devtype == IMX8QXP_LPUART;
पूर्ण

अटल अंतरभूत u32 lpuart32_पढ़ो(काष्ठा uart_port *port, u32 off)
अणु
	चयन (port->iotype) अणु
	हाल UPIO_MEM32:
		वापस पढ़ोl(port->membase + off);
	हाल UPIO_MEM32BE:
		वापस ioपढ़ो32be(port->membase + off);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम lpuart32_ग_लिखो(काष्ठा uart_port *port, u32 val,
				  u32 off)
अणु
	चयन (port->iotype) अणु
	हाल UPIO_MEM32:
		ग_लिखोl(val, port->membase + off);
		अवरोध;
	हाल UPIO_MEM32BE:
		ioग_लिखो32be(val, port->membase + off);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक __lpuart_enable_clks(काष्ठा lpuart_port *sport, bool is_en)
अणु
	पूर्णांक ret = 0;

	अगर (is_en) अणु
		ret = clk_prepare_enable(sport->ipg_clk);
		अगर (ret)
			वापस ret;

		ret = clk_prepare_enable(sport->baud_clk);
		अगर (ret) अणु
			clk_disable_unprepare(sport->ipg_clk);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(sport->baud_clk);
		clk_disable_unprepare(sport->ipg_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक lpuart_get_baud_clk_rate(काष्ठा lpuart_port *sport)
अणु
	अगर (is_imx8qxp_lpuart(sport))
		वापस clk_get_rate(sport->baud_clk);

	वापस clk_get_rate(sport->ipg_clk);
पूर्ण

#घोषणा lpuart_enable_clks(x)	__lpuart_enable_clks(x, true)
#घोषणा lpuart_disable_clks(x)	__lpuart_enable_clks(x, false)

अटल व्योम lpuart_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर temp;

	temp = पढ़ोb(port->membase + UARTCR2);
	temp &= ~(UARTCR2_TIE | UARTCR2_TCIE);
	ग_लिखोb(temp, port->membase + UARTCR2);
पूर्ण

अटल व्योम lpuart32_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ temp;

	temp = lpuart32_पढ़ो(port, UARTCTRL);
	temp &= ~(UARTCTRL_TIE | UARTCTRL_TCIE);
	lpuart32_ग_लिखो(port, temp, UARTCTRL);
पूर्ण

अटल व्योम lpuart_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर temp;

	temp = पढ़ोb(port->membase + UARTCR2);
	ग_लिखोb(temp & ~UARTCR2_RE, port->membase + UARTCR2);
पूर्ण

अटल व्योम lpuart32_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ temp;

	temp = lpuart32_पढ़ो(port, UARTCTRL);
	lpuart32_ग_लिखो(port, temp & ~UARTCTRL_RE, UARTCTRL);
पूर्ण

अटल व्योम lpuart_dma_tx(काष्ठा lpuart_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	काष्ठा scatterlist *sgl = sport->tx_sgl;
	काष्ठा device *dev = sport->port.dev;
	काष्ठा dma_chan *chan = sport->dma_tx_chan;
	पूर्णांक ret;

	अगर (sport->dma_tx_in_progress)
		वापस;

	sport->dma_tx_bytes = uart_circ_अक्षरs_pending(xmit);

	अगर (xmit->tail < xmit->head || xmit->head == 0) अणु
		sport->dma_tx_nents = 1;
		sg_init_one(sgl, xmit->buf + xmit->tail, sport->dma_tx_bytes);
	पूर्ण अन्यथा अणु
		sport->dma_tx_nents = 2;
		sg_init_table(sgl, 2);
		sg_set_buf(sgl, xmit->buf + xmit->tail,
				UART_XMIT_SIZE - xmit->tail);
		sg_set_buf(sgl + 1, xmit->buf, xmit->head);
	पूर्ण

	ret = dma_map_sg(chan->device->dev, sgl, sport->dma_tx_nents,
			 DMA_TO_DEVICE);
	अगर (!ret) अणु
		dev_err(dev, "DMA mapping error for TX.\n");
		वापस;
	पूर्ण

	sport->dma_tx_desc = dmaengine_prep_slave_sg(chan, sgl,
					ret, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT);
	अगर (!sport->dma_tx_desc) अणु
		dma_unmap_sg(chan->device->dev, sgl, sport->dma_tx_nents,
			      DMA_TO_DEVICE);
		dev_err(dev, "Cannot prepare TX slave DMA!\n");
		वापस;
	पूर्ण

	sport->dma_tx_desc->callback = lpuart_dma_tx_complete;
	sport->dma_tx_desc->callback_param = sport;
	sport->dma_tx_in_progress = true;
	sport->dma_tx_cookie = dmaengine_submit(sport->dma_tx_desc);
	dma_async_issue_pending(chan);
पूर्ण

अटल bool lpuart_stopped_or_empty(काष्ठा uart_port *port)
अणु
	वापस uart_circ_empty(&port->state->xmit) || uart_tx_stopped(port);
पूर्ण

अटल व्योम lpuart_dma_tx_complete(व्योम *arg)
अणु
	काष्ठा lpuart_port *sport = arg;
	काष्ठा scatterlist *sgl = &sport->tx_sgl[0];
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	काष्ठा dma_chan *chan = sport->dma_tx_chan;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);

	dma_unmap_sg(chan->device->dev, sgl, sport->dma_tx_nents,
		     DMA_TO_DEVICE);

	xmit->tail = (xmit->tail + sport->dma_tx_bytes) & (UART_XMIT_SIZE - 1);

	sport->port.icount.tx += sport->dma_tx_bytes;
	sport->dma_tx_in_progress = false;
	spin_unlock_irqrestore(&sport->port.lock, flags);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (रुकोqueue_active(&sport->dma_रुको)) अणु
		wake_up(&sport->dma_रुको);
		वापस;
	पूर्ण

	spin_lock_irqsave(&sport->port.lock, flags);

	अगर (!lpuart_stopped_or_empty(&sport->port))
		lpuart_dma_tx(sport);

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल dma_addr_t lpuart_dma_datareg_addr(काष्ठा lpuart_port *sport)
अणु
	चयन (sport->port.iotype) अणु
	हाल UPIO_MEM32:
		वापस sport->port.mapbase + UARTDATA;
	हाल UPIO_MEM32BE:
		वापस sport->port.mapbase + UARTDATA + माप(u32) - 1;
	पूर्ण
	वापस sport->port.mapbase + UARTDR;
पूर्ण

अटल पूर्णांक lpuart_dma_tx_request(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
					काष्ठा lpuart_port, port);
	काष्ठा dma_slave_config dma_tx_sconfig = अणुपूर्ण;
	पूर्णांक ret;

	dma_tx_sconfig.dst_addr = lpuart_dma_datareg_addr(sport);
	dma_tx_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_tx_sconfig.dst_maxburst = 1;
	dma_tx_sconfig.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(sport->dma_tx_chan, &dma_tx_sconfig);

	अगर (ret) अणु
		dev_err(sport->port.dev,
				"DMA slave config failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool lpuart_is_32(काष्ठा lpuart_port *sport)
अणु
	वापस sport->port.iotype == UPIO_MEM32 ||
	       sport->port.iotype ==  UPIO_MEM32BE;
पूर्ण

अटल व्योम lpuart_flush_buffer(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	काष्ठा dma_chan *chan = sport->dma_tx_chan;
	u32 val;

	अगर (sport->lpuart_dma_tx_use) अणु
		अगर (sport->dma_tx_in_progress) अणु
			dma_unmap_sg(chan->device->dev, &sport->tx_sgl[0],
				sport->dma_tx_nents, DMA_TO_DEVICE);
			sport->dma_tx_in_progress = false;
		पूर्ण
		dmaengine_terminate_all(chan);
	पूर्ण

	अगर (lpuart_is_32(sport)) अणु
		val = lpuart32_पढ़ो(&sport->port, UARTFIFO);
		val |= UARTFIFO_TXFLUSH | UARTFIFO_RXFLUSH;
		lpuart32_ग_लिखो(&sport->port, val, UARTFIFO);
	पूर्ण अन्यथा अणु
		val = पढ़ोb(sport->port.membase + UARTCFIFO);
		val |= UARTCFIFO_TXFLUSH | UARTCFIFO_RXFLUSH;
		ग_लिखोb(val, sport->port.membase + UARTCFIFO);
	पूर्ण
पूर्ण

अटल व्योम lpuart_रुको_bit_set(काष्ठा uart_port *port, अचिन्हित पूर्णांक offset,
				u8 bit)
अणु
	जबतक (!(पढ़ोb(port->membase + offset) & bit))
		cpu_relax();
पूर्ण

अटल व्योम lpuart32_रुको_bit_set(काष्ठा uart_port *port, अचिन्हित पूर्णांक offset,
				  u32 bit)
अणु
	जबतक (!(lpuart32_पढ़ो(port, offset) & bit))
		cpu_relax();
पूर्ण

#अगर defined(CONFIG_CONSOLE_POLL)

अटल पूर्णांक lpuart_poll_init(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
					काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर temp;

	sport->port.fअगरosize = 0;

	spin_lock_irqsave(&sport->port.lock, flags);
	/* Disable Rx & Tx */
	ग_लिखोb(0, sport->port.membase + UARTCR2);

	temp = पढ़ोb(sport->port.membase + UARTPFIFO);
	/* Enable Rx and Tx FIFO */
	ग_लिखोb(temp | UARTPFIFO_RXFE | UARTPFIFO_TXFE,
			sport->port.membase + UARTPFIFO);

	/* flush Tx and Rx FIFO */
	ग_लिखोb(UARTCFIFO_TXFLUSH | UARTCFIFO_RXFLUSH,
			sport->port.membase + UARTCFIFO);

	/* explicitly clear RDRF */
	अगर (पढ़ोb(sport->port.membase + UARTSR1) & UARTSR1_RDRF) अणु
		पढ़ोb(sport->port.membase + UARTDR);
		ग_लिखोb(UARTSFIFO_RXUF, sport->port.membase + UARTSFIFO);
	पूर्ण

	ग_लिखोb(0, sport->port.membase + UARTTWFIFO);
	ग_लिखोb(1, sport->port.membase + UARTRWFIFO);

	/* Enable Rx and Tx */
	ग_लिखोb(UARTCR2_RE | UARTCR2_TE, sport->port.membase + UARTCR2);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lpuart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	/* drain */
	lpuart_रुको_bit_set(port, UARTSR1, UARTSR1_TDRE);
	ग_लिखोb(c, port->membase + UARTDR);
पूर्ण

अटल पूर्णांक lpuart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	अगर (!(पढ़ोb(port->membase + UARTSR1) & UARTSR1_RDRF))
		वापस NO_POLL_CHAR;

	वापस पढ़ोb(port->membase + UARTDR);
पूर्ण

अटल पूर्णांक lpuart32_poll_init(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	u32 temp;

	sport->port.fअगरosize = 0;

	spin_lock_irqsave(&sport->port.lock, flags);

	/* Disable Rx & Tx */
	lpuart32_ग_लिखो(&sport->port, 0, UARTCTRL);

	temp = lpuart32_पढ़ो(&sport->port, UARTFIFO);

	/* Enable Rx and Tx FIFO */
	lpuart32_ग_लिखो(&sport->port, temp | UARTFIFO_RXFE | UARTFIFO_TXFE, UARTFIFO);

	/* flush Tx and Rx FIFO */
	lpuart32_ग_लिखो(&sport->port, UARTFIFO_TXFLUSH | UARTFIFO_RXFLUSH, UARTFIFO);

	/* explicitly clear RDRF */
	अगर (lpuart32_पढ़ो(&sport->port, UARTSTAT) & UARTSTAT_RDRF) अणु
		lpuart32_पढ़ो(&sport->port, UARTDATA);
		lpuart32_ग_लिखो(&sport->port, UARTFIFO_RXUF, UARTFIFO);
	पूर्ण

	/* Enable Rx and Tx */
	lpuart32_ग_लिखो(&sport->port, UARTCTRL_RE | UARTCTRL_TE, UARTCTRL);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lpuart32_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	lpuart32_रुको_bit_set(port, UARTSTAT, UARTSTAT_TDRE);
	lpuart32_ग_लिखो(port, c, UARTDATA);
पूर्ण

अटल पूर्णांक lpuart32_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	अगर (!(lpuart32_पढ़ो(port, UARTWATER) >> UARTWATER_RXCNT_OFF))
		वापस NO_POLL_CHAR;

	वापस lpuart32_पढ़ो(port, UARTDATA);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम lpuart_transmit_buffer(काष्ठा lpuart_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;

	अगर (sport->port.x_अक्षर) अणु
		ग_लिखोb(sport->port.x_अक्षर, sport->port.membase + UARTDR);
		sport->port.icount.tx++;
		sport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (lpuart_stopped_or_empty(&sport->port)) अणु
		lpuart_stop_tx(&sport->port);
		वापस;
	पूर्ण

	जबतक (!uart_circ_empty(xmit) &&
		(पढ़ोb(sport->port.membase + UARTTCFIFO) < sport->txfअगरo_size)) अणु
		ग_लिखोb(xmit->buf[xmit->tail], sport->port.membase + UARTDR);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (uart_circ_empty(xmit))
		lpuart_stop_tx(&sport->port);
पूर्ण

अटल अंतरभूत व्योम lpuart32_transmit_buffer(काष्ठा lpuart_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	अचिन्हित दीर्घ txcnt;

	अगर (sport->port.x_अक्षर) अणु
		lpuart32_ग_लिखो(&sport->port, sport->port.x_अक्षर, UARTDATA);
		sport->port.icount.tx++;
		sport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (lpuart_stopped_or_empty(&sport->port)) अणु
		lpuart32_stop_tx(&sport->port);
		वापस;
	पूर्ण

	txcnt = lpuart32_पढ़ो(&sport->port, UARTWATER);
	txcnt = txcnt >> UARTWATER_TXCNT_OFF;
	txcnt &= UARTWATER_COUNT_MASK;
	जबतक (!uart_circ_empty(xmit) && (txcnt < sport->txfअगरo_size)) अणु
		lpuart32_ग_लिखो(&sport->port, xmit->buf[xmit->tail], UARTDATA);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
		txcnt = lpuart32_पढ़ो(&sport->port, UARTWATER);
		txcnt = txcnt >> UARTWATER_TXCNT_OFF;
		txcnt &= UARTWATER_COUNT_MASK;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (uart_circ_empty(xmit))
		lpuart32_stop_tx(&sport->port);
पूर्ण

अटल व्योम lpuart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
			काष्ठा lpuart_port, port);
	अचिन्हित अक्षर temp;

	temp = पढ़ोb(port->membase + UARTCR2);
	ग_लिखोb(temp | UARTCR2_TIE, port->membase + UARTCR2);

	अगर (sport->lpuart_dma_tx_use) अणु
		अगर (!lpuart_stopped_or_empty(port))
			lpuart_dma_tx(sport);
	पूर्ण अन्यथा अणु
		अगर (पढ़ोb(port->membase + UARTSR1) & UARTSR1_TDRE)
			lpuart_transmit_buffer(sport);
	पूर्ण
पूर्ण

अटल व्योम lpuart32_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ temp;

	अगर (sport->lpuart_dma_tx_use) अणु
		अगर (!lpuart_stopped_or_empty(port))
			lpuart_dma_tx(sport);
	पूर्ण अन्यथा अणु
		temp = lpuart32_पढ़ो(port, UARTCTRL);
		lpuart32_ग_लिखो(port, temp | UARTCTRL_TIE, UARTCTRL);

		अगर (lpuart32_पढ़ो(port, UARTSTAT) & UARTSTAT_TDRE)
			lpuart32_transmit_buffer(sport);
	पूर्ण
पूर्ण

/* वापस TIOCSER_TEMT when transmitter is not busy */
अटल अचिन्हित पूर्णांक lpuart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
			काष्ठा lpuart_port, port);
	अचिन्हित अक्षर sr1 = पढ़ोb(port->membase + UARTSR1);
	अचिन्हित अक्षर sfअगरo = पढ़ोb(port->membase + UARTSFIFO);

	अगर (sport->dma_tx_in_progress)
		वापस 0;

	अगर (sr1 & UARTSR1_TC && sfअगरo & UARTSFIFO_TXEMPT)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक lpuart32_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
			काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ stat = lpuart32_पढ़ो(port, UARTSTAT);
	अचिन्हित दीर्घ sfअगरo = lpuart32_पढ़ो(port, UARTFIFO);

	अगर (sport->dma_tx_in_progress)
		वापस 0;

	अगर (stat & UARTSTAT_TC && sfअगरo & UARTFIFO_TXEMPT)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल व्योम lpuart_txपूर्णांक(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	lpuart_transmit_buffer(sport);
	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम lpuart_rxपूर्णांक(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित पूर्णांक flg, ignored = 0, overrun = 0;
	काष्ठा tty_port *port = &sport->port.state->port;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर rx, sr;

	spin_lock_irqsave(&sport->port.lock, flags);

	जबतक (!(पढ़ोb(sport->port.membase + UARTSFIFO) & UARTSFIFO_RXEMPT)) अणु
		flg = TTY_NORMAL;
		sport->port.icount.rx++;
		/*
		 * to clear the FE, OR, NF, FE, PE flags,
		 * पढ़ो SR1 then पढ़ो DR
		 */
		sr = पढ़ोb(sport->port.membase + UARTSR1);
		rx = पढ़ोb(sport->port.membase + UARTDR);

		अगर (uart_handle_sysrq_अक्षर(&sport->port, (अचिन्हित अक्षर)rx))
			जारी;

		अगर (sr & (UARTSR1_PE | UARTSR1_OR | UARTSR1_FE)) अणु
			अगर (sr & UARTSR1_PE)
				sport->port.icount.parity++;
			अन्यथा अगर (sr & UARTSR1_FE)
				sport->port.icount.frame++;

			अगर (sr & UARTSR1_OR)
				overrun++;

			अगर (sr & sport->port.ignore_status_mask) अणु
				अगर (++ignored > 100)
					जाओ out;
				जारी;
			पूर्ण

			sr &= sport->port.पढ़ो_status_mask;

			अगर (sr & UARTSR1_PE)
				flg = TTY_PARITY;
			अन्यथा अगर (sr & UARTSR1_FE)
				flg = TTY_FRAME;

			अगर (sr & UARTSR1_OR)
				flg = TTY_OVERRUN;

			sport->port.sysrq = 0;
		पूर्ण

		tty_insert_flip_अक्षर(port, rx, flg);
	पूर्ण

out:
	अगर (overrun) अणु
		sport->port.icount.overrun += overrun;

		/*
		 * Overruns cause FIFO poपूर्णांकers to become missaligned.
		 * Flushing the receive FIFO reinitializes the poपूर्णांकers.
		 */
		ग_लिखोb(UARTCFIFO_RXFLUSH, sport->port.membase + UARTCFIFO);
		ग_लिखोb(UARTSFIFO_RXOF, sport->port.membase + UARTSFIFO);
	पूर्ण

	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम lpuart32_txपूर्णांक(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	lpuart32_transmit_buffer(sport);
	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम lpuart32_rxपूर्णांक(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित पूर्णांक flg, ignored = 0;
	काष्ठा tty_port *port = &sport->port.state->port;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ rx, sr;

	spin_lock_irqsave(&sport->port.lock, flags);

	जबतक (!(lpuart32_पढ़ो(&sport->port, UARTFIFO) & UARTFIFO_RXEMPT)) अणु
		flg = TTY_NORMAL;
		sport->port.icount.rx++;
		/*
		 * to clear the FE, OR, NF, FE, PE flags,
		 * पढ़ो STAT then पढ़ो DATA reg
		 */
		sr = lpuart32_पढ़ो(&sport->port, UARTSTAT);
		rx = lpuart32_पढ़ो(&sport->port, UARTDATA);
		rx &= 0x3ff;

		अगर (uart_handle_sysrq_अक्षर(&sport->port, (अचिन्हित अक्षर)rx))
			जारी;

		अगर (sr & (UARTSTAT_PE | UARTSTAT_OR | UARTSTAT_FE)) अणु
			अगर (sr & UARTSTAT_PE)
				sport->port.icount.parity++;
			अन्यथा अगर (sr & UARTSTAT_FE)
				sport->port.icount.frame++;

			अगर (sr & UARTSTAT_OR)
				sport->port.icount.overrun++;

			अगर (sr & sport->port.ignore_status_mask) अणु
				अगर (++ignored > 100)
					जाओ out;
				जारी;
			पूर्ण

			sr &= sport->port.पढ़ो_status_mask;

			अगर (sr & UARTSTAT_PE)
				flg = TTY_PARITY;
			अन्यथा अगर (sr & UARTSTAT_FE)
				flg = TTY_FRAME;

			अगर (sr & UARTSTAT_OR)
				flg = TTY_OVERRUN;

			sport->port.sysrq = 0;
		पूर्ण

		tty_insert_flip_अक्षर(port, rx, flg);
	पूर्ण

out:
	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
पूर्ण

अटल irqवापस_t lpuart_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpuart_port *sport = dev_id;
	अचिन्हित अक्षर sts;

	sts = पढ़ोb(sport->port.membase + UARTSR1);

	/* SysRq, using dma, check क्रम lineअवरोध by framing err. */
	अगर (sts & UARTSR1_FE && sport->lpuart_dma_rx_use) अणु
		पढ़ोb(sport->port.membase + UARTDR);
		uart_handle_अवरोध(&sport->port);
		/* lineअवरोध produces some garbage, removing it */
		ग_लिखोb(UARTCFIFO_RXFLUSH, sport->port.membase + UARTCFIFO);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (sts & UARTSR1_RDRF && !sport->lpuart_dma_rx_use)
		lpuart_rxपूर्णांक(sport);

	अगर (sts & UARTSR1_TDRE && !sport->lpuart_dma_tx_use)
		lpuart_txपूर्णांक(sport);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lpuart32_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpuart_port *sport = dev_id;
	अचिन्हित दीर्घ sts, rxcount;

	sts = lpuart32_पढ़ो(&sport->port, UARTSTAT);
	rxcount = lpuart32_पढ़ो(&sport->port, UARTWATER);
	rxcount = rxcount >> UARTWATER_RXCNT_OFF;

	अगर ((sts & UARTSTAT_RDRF || rxcount > 0) && !sport->lpuart_dma_rx_use)
		lpuart32_rxपूर्णांक(sport);

	अगर ((sts & UARTSTAT_TDRE) && !sport->lpuart_dma_tx_use)
		lpuart32_txपूर्णांक(sport);

	lpuart32_ग_लिखो(&sport->port, sts, UARTSTAT);
	वापस IRQ_HANDLED;
पूर्ण


अटल अंतरभूत व्योम lpuart_handle_sysrq_अक्षरs(काष्ठा uart_port *port,
					     अचिन्हित अक्षर *p, पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*p && uart_handle_sysrq_अक्षर(port, *p))
			वापस;
		p++;
	पूर्ण
पूर्ण

अटल व्योम lpuart_handle_sysrq(काष्ठा lpuart_port *sport)
अणु
	काष्ठा circ_buf *ring = &sport->rx_ring;
	पूर्णांक count;

	अगर (ring->head < ring->tail) अणु
		count = sport->rx_sgl.length - ring->tail;
		lpuart_handle_sysrq_अक्षरs(&sport->port,
					  ring->buf + ring->tail, count);
		ring->tail = 0;
	पूर्ण

	अगर (ring->head > ring->tail) अणु
		count = ring->head - ring->tail;
		lpuart_handle_sysrq_अक्षरs(&sport->port,
					  ring->buf + ring->tail, count);
		ring->tail = ring->head;
	पूर्ण
पूर्ण

अटल व्योम lpuart_copy_rx_to_tty(काष्ठा lpuart_port *sport)
अणु
	काष्ठा tty_port *port = &sport->port.state->port;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status dmastat;
	काष्ठा dma_chan *chan = sport->dma_rx_chan;
	काष्ठा circ_buf *ring = &sport->rx_ring;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 0;

	अगर (lpuart_is_32(sport)) अणु
		अचिन्हित दीर्घ sr = lpuart32_पढ़ो(&sport->port, UARTSTAT);

		अगर (sr & (UARTSTAT_PE | UARTSTAT_FE)) अणु
			/* Read DR to clear the error flags */
			lpuart32_पढ़ो(&sport->port, UARTDATA);

			अगर (sr & UARTSTAT_PE)
				sport->port.icount.parity++;
			अन्यथा अगर (sr & UARTSTAT_FE)
				sport->port.icount.frame++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर sr = पढ़ोb(sport->port.membase + UARTSR1);

		अगर (sr & (UARTSR1_PE | UARTSR1_FE)) अणु
			अचिन्हित अक्षर cr2;

			/* Disable receiver during this operation... */
			cr2 = पढ़ोb(sport->port.membase + UARTCR2);
			cr2 &= ~UARTCR2_RE;
			ग_लिखोb(cr2, sport->port.membase + UARTCR2);

			/* Read DR to clear the error flags */
			पढ़ोb(sport->port.membase + UARTDR);

			अगर (sr & UARTSR1_PE)
				sport->port.icount.parity++;
			अन्यथा अगर (sr & UARTSR1_FE)
				sport->port.icount.frame++;
			/*
			 * At this poपूर्णांक parity/framing error is
			 * cleared However, since the DMA alपढ़ोy पढ़ो
			 * the data रेजिस्टर and we had to पढ़ो it
			 * again after पढ़ोing the status रेजिस्टर to
			 * properly clear the flags, the FIFO actually
			 * underflowed... This requires a clearing of
			 * the FIFO...
			 */
			अगर (पढ़ोb(sport->port.membase + UARTSFIFO) &
			    UARTSFIFO_RXUF) अणु
				ग_लिखोb(UARTSFIFO_RXUF,
				       sport->port.membase + UARTSFIFO);
				ग_लिखोb(UARTCFIFO_RXFLUSH,
				       sport->port.membase + UARTCFIFO);
			पूर्ण

			cr2 |= UARTCR2_RE;
			ग_लिखोb(cr2, sport->port.membase + UARTCR2);
		पूर्ण
	पूर्ण

	async_tx_ack(sport->dma_rx_desc);

	spin_lock_irqsave(&sport->port.lock, flags);

	dmastat = dmaengine_tx_status(chan, sport->dma_rx_cookie, &state);
	अगर (dmastat == DMA_ERROR) अणु
		dev_err(sport->port.dev, "Rx DMA transfer failed!\n");
		spin_unlock_irqrestore(&sport->port.lock, flags);
		वापस;
	पूर्ण

	/* CPU claims ownership of RX DMA buffer */
	dma_sync_sg_क्रम_cpu(chan->device->dev, &sport->rx_sgl, 1,
			    DMA_FROM_DEVICE);

	/*
	 * ring->head poपूर्णांकs to the end of data alपढ़ोy written by the DMA.
	 * ring->tail poपूर्णांकs to the beginning of data to be पढ़ो by the
	 * framework.
	 * The current transfer size should not be larger than the dma buffer
	 * length.
	 */
	ring->head = sport->rx_sgl.length - state.residue;
	BUG_ON(ring->head > sport->rx_sgl.length);

	/*
	 * Silent handling of keys pressed in the sysrq समयframe
	 */
	अगर (sport->port.sysrq) अणु
		lpuart_handle_sysrq(sport);
		जाओ निकास;
	पूर्ण

	/*
	 * At this poपूर्णांक ring->head may poपूर्णांक to the first byte right after the
	 * last byte of the dma buffer:
	 * 0 <= ring->head <= sport->rx_sgl.length
	 *
	 * However ring->tail must always poपूर्णांकs inside the dma buffer:
	 * 0 <= ring->tail <= sport->rx_sgl.length - 1
	 *
	 * Since we use a ring buffer, we have to handle the हाल
	 * where head is lower than tail. In such a हाल, we first पढ़ो from
	 * tail to the end of the buffer then reset tail.
	 */
	अगर (ring->head < ring->tail) अणु
		count = sport->rx_sgl.length - ring->tail;

		tty_insert_flip_string(port, ring->buf + ring->tail, count);
		ring->tail = 0;
		sport->port.icount.rx += count;
	पूर्ण

	/* Finally we पढ़ो data from tail to head */
	अगर (ring->tail < ring->head) अणु
		count = ring->head - ring->tail;
		tty_insert_flip_string(port, ring->buf + ring->tail, count);
		/* Wrap ring->head अगर needed */
		अगर (ring->head >= sport->rx_sgl.length)
			ring->head = 0;
		ring->tail = ring->head;
		sport->port.icount.rx += count;
	पूर्ण

निकास:
	dma_sync_sg_क्रम_device(chan->device->dev, &sport->rx_sgl, 1,
			       DMA_FROM_DEVICE);

	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
	mod_समयr(&sport->lpuart_समयr, jअगरfies + sport->dma_rx_समयout);
पूर्ण

अटल व्योम lpuart_dma_rx_complete(व्योम *arg)
अणु
	काष्ठा lpuart_port *sport = arg;

	lpuart_copy_rx_to_tty(sport);
पूर्ण

अटल व्योम lpuart_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा lpuart_port *sport = from_समयr(sport, t, lpuart_समयr);

	lpuart_copy_rx_to_tty(sport);
पूर्ण

अटल अंतरभूत पूर्णांक lpuart_start_rx_dma(काष्ठा lpuart_port *sport)
अणु
	काष्ठा dma_slave_config dma_rx_sconfig = अणुपूर्ण;
	काष्ठा circ_buf *ring = &sport->rx_ring;
	पूर्णांक ret, nent;
	पूर्णांक bits, baud;
	काष्ठा tty_port *port = &sport->port.state->port;
	काष्ठा tty_काष्ठा *tty = port->tty;
	काष्ठा ktermios *termios = &tty->termios;
	काष्ठा dma_chan *chan = sport->dma_rx_chan;

	baud = tty_get_baud_rate(tty);

	bits = (termios->c_cflag & CSIZE) == CS7 ? 9 : 10;
	अगर (termios->c_cflag & PARENB)
		bits++;

	/*
	 * Calculate length of one DMA buffer size to keep latency below
	 * 10ms at any baud rate.
	 */
	sport->rx_dma_rng_buf_len = (DMA_RX_TIMEOUT * baud /  bits / 1000) * 2;
	sport->rx_dma_rng_buf_len = (1 << (fls(sport->rx_dma_rng_buf_len) - 1));
	अगर (sport->rx_dma_rng_buf_len < 16)
		sport->rx_dma_rng_buf_len = 16;

	ring->buf = kzalloc(sport->rx_dma_rng_buf_len, GFP_ATOMIC);
	अगर (!ring->buf)
		वापस -ENOMEM;

	sg_init_one(&sport->rx_sgl, ring->buf, sport->rx_dma_rng_buf_len);
	nent = dma_map_sg(chan->device->dev, &sport->rx_sgl, 1,
			  DMA_FROM_DEVICE);

	अगर (!nent) अणु
		dev_err(sport->port.dev, "DMA Rx mapping error\n");
		वापस -EINVAL;
	पूर्ण

	dma_rx_sconfig.src_addr = lpuart_dma_datareg_addr(sport);
	dma_rx_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_rx_sconfig.src_maxburst = 1;
	dma_rx_sconfig.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(chan, &dma_rx_sconfig);

	अगर (ret < 0) अणु
		dev_err(sport->port.dev,
				"DMA Rx slave config failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	sport->dma_rx_desc = dmaengine_prep_dma_cyclic(chan,
				 sg_dma_address(&sport->rx_sgl),
				 sport->rx_sgl.length,
				 sport->rx_sgl.length / 2,
				 DMA_DEV_TO_MEM,
				 DMA_PREP_INTERRUPT);
	अगर (!sport->dma_rx_desc) अणु
		dev_err(sport->port.dev, "Cannot prepare cyclic DMA\n");
		वापस -EFAULT;
	पूर्ण

	sport->dma_rx_desc->callback = lpuart_dma_rx_complete;
	sport->dma_rx_desc->callback_param = sport;
	sport->dma_rx_cookie = dmaengine_submit(sport->dma_rx_desc);
	dma_async_issue_pending(chan);

	अगर (lpuart_is_32(sport)) अणु
		अचिन्हित दीर्घ temp = lpuart32_पढ़ो(&sport->port, UARTBAUD);

		lpuart32_ग_लिखो(&sport->port, temp | UARTBAUD_RDMAE, UARTBAUD);
	पूर्ण अन्यथा अणु
		ग_लिखोb(पढ़ोb(sport->port.membase + UARTCR5) | UARTCR5_RDMAS,
		       sport->port.membase + UARTCR5);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lpuart_dma_rx_मुक्त(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
					काष्ठा lpuart_port, port);
	काष्ठा dma_chan *chan = sport->dma_rx_chan;

	dmaengine_terminate_all(chan);
	dma_unmap_sg(chan->device->dev, &sport->rx_sgl, 1, DMA_FROM_DEVICE);
	kमुक्त(sport->rx_ring.buf);
	sport->rx_ring.tail = 0;
	sport->rx_ring.head = 0;
	sport->dma_rx_desc = शून्य;
	sport->dma_rx_cookie = -EINVAL;
पूर्ण

अटल पूर्णांक lpuart_config_rs485(काष्ठा uart_port *port,
			काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
			काष्ठा lpuart_port, port);

	u8 modem = पढ़ोb(sport->port.membase + UARTMODEM) &
		~(UARTMODEM_TXRTSPOL | UARTMODEM_TXRTSE);
	ग_लिखोb(modem, sport->port.membase + UARTMODEM);

	/* clear unsupported configurations */
	rs485->delay_rts_beक्रमe_send = 0;
	rs485->delay_rts_after_send = 0;
	rs485->flags &= ~SER_RS485_RX_DURING_TX;

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		/* Enable स्वतः RS-485 RTS mode */
		modem |= UARTMODEM_TXRTSE;

		/*
		 * RTS needs to be logic HIGH either during transfer _or_ after
		 * transfer, other variants are not supported by the hardware.
		 */

		अगर (!(rs485->flags & (SER_RS485_RTS_ON_SEND |
				SER_RS485_RTS_AFTER_SEND)))
			rs485->flags |= SER_RS485_RTS_ON_SEND;

		अगर (rs485->flags & SER_RS485_RTS_ON_SEND &&
				rs485->flags & SER_RS485_RTS_AFTER_SEND)
			rs485->flags &= ~SER_RS485_RTS_AFTER_SEND;

		/*
		 * The hardware शेषs to RTS logic HIGH जबतक transfer.
		 * Switch polarity in हाल RTS shall be logic HIGH
		 * after transfer.
		 * Note: UART is assumed to be active high.
		 */
		अगर (rs485->flags & SER_RS485_RTS_ON_SEND)
			modem &= ~UARTMODEM_TXRTSPOL;
		अन्यथा अगर (rs485->flags & SER_RS485_RTS_AFTER_SEND)
			modem |= UARTMODEM_TXRTSPOL;
	पूर्ण

	/* Store the new configuration */
	sport->port.rs485 = *rs485;

	ग_लिखोb(modem, sport->port.membase + UARTMODEM);
	वापस 0;
पूर्ण

अटल पूर्णांक lpuart32_config_rs485(काष्ठा uart_port *port,
			काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा lpuart_port *sport = container_of(port,
			काष्ठा lpuart_port, port);

	अचिन्हित दीर्घ modem = lpuart32_पढ़ो(&sport->port, UARTMOसूची)
				& ~(UARTMODEM_TXRTSPOL | UARTMODEM_TXRTSE);
	lpuart32_ग_लिखो(&sport->port, modem, UARTMOसूची);

	/* clear unsupported configurations */
	rs485->delay_rts_beक्रमe_send = 0;
	rs485->delay_rts_after_send = 0;
	rs485->flags &= ~SER_RS485_RX_DURING_TX;

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		/* Enable स्वतः RS-485 RTS mode */
		modem |= UARTMODEM_TXRTSE;

		/*
		 * RTS needs to be logic HIGH either during transfer _or_ after
		 * transfer, other variants are not supported by the hardware.
		 */

		अगर (!(rs485->flags & (SER_RS485_RTS_ON_SEND |
				SER_RS485_RTS_AFTER_SEND)))
			rs485->flags |= SER_RS485_RTS_ON_SEND;

		अगर (rs485->flags & SER_RS485_RTS_ON_SEND &&
				rs485->flags & SER_RS485_RTS_AFTER_SEND)
			rs485->flags &= ~SER_RS485_RTS_AFTER_SEND;

		/*
		 * The hardware शेषs to RTS logic HIGH जबतक transfer.
		 * Switch polarity in हाल RTS shall be logic HIGH
		 * after transfer.
		 * Note: UART is assumed to be active high.
		 */
		अगर (rs485->flags & SER_RS485_RTS_ON_SEND)
			modem &= ~UARTMODEM_TXRTSPOL;
		अन्यथा अगर (rs485->flags & SER_RS485_RTS_AFTER_SEND)
			modem |= UARTMODEM_TXRTSPOL;
	पूर्ण

	/* Store the new configuration */
	sport->port.rs485 = *rs485;

	lpuart32_ग_लिखो(&sport->port, modem, UARTMOसूची);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक lpuart_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक temp = 0;
	अचिन्हित अक्षर reg;

	reg = पढ़ोb(port->membase + UARTMODEM);
	अगर (reg & UARTMODEM_TXCTSE)
		temp |= TIOCM_CTS;

	अगर (reg & UARTMODEM_RXRTSE)
		temp |= TIOCM_RTS;

	वापस temp;
पूर्ण

अटल अचिन्हित पूर्णांक lpuart32_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक temp = 0;
	अचिन्हित दीर्घ reg;

	reg = lpuart32_पढ़ो(port, UARTMOसूची);
	अगर (reg & UARTMOसूची_TXCTSE)
		temp |= TIOCM_CTS;

	अगर (reg & UARTMOसूची_RXRTSE)
		temp |= TIOCM_RTS;

	वापस temp;
पूर्ण

अटल व्योम lpuart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित अक्षर temp;
	काष्ठा lpuart_port *sport = container_of(port,
				काष्ठा lpuart_port, port);

	/* Make sure RXRTSE bit is not set when RS485 is enabled */
	अगर (!(sport->port.rs485.flags & SER_RS485_ENABLED)) अणु
		temp = पढ़ोb(sport->port.membase + UARTMODEM) &
			~(UARTMODEM_RXRTSE | UARTMODEM_TXCTSE);

		अगर (mctrl & TIOCM_RTS)
			temp |= UARTMODEM_RXRTSE;

		अगर (mctrl & TIOCM_CTS)
			temp |= UARTMODEM_TXCTSE;

		ग_लिखोb(temp, port->membase + UARTMODEM);
	पूर्ण
पूर्ण

अटल व्योम lpuart32_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु

पूर्ण

अटल व्योम lpuart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित अक्षर temp;

	temp = पढ़ोb(port->membase + UARTCR2) & ~UARTCR2_SBK;

	अगर (अवरोध_state != 0)
		temp |= UARTCR2_SBK;

	ग_लिखोb(temp, port->membase + UARTCR2);
पूर्ण

अटल व्योम lpuart32_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ temp;

	temp = lpuart32_पढ़ो(port, UARTCTRL) & ~UARTCTRL_SBK;

	अगर (अवरोध_state != 0)
		temp |= UARTCTRL_SBK;

	lpuart32_ग_लिखो(port, temp, UARTCTRL);
पूर्ण

अटल व्योम lpuart_setup_watermark(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित अक्षर val, cr2;
	अचिन्हित अक्षर cr2_saved;

	cr2 = पढ़ोb(sport->port.membase + UARTCR2);
	cr2_saved = cr2;
	cr2 &= ~(UARTCR2_TIE | UARTCR2_TCIE | UARTCR2_TE |
			UARTCR2_RIE | UARTCR2_RE);
	ग_लिखोb(cr2, sport->port.membase + UARTCR2);

	val = पढ़ोb(sport->port.membase + UARTPFIFO);
	ग_लिखोb(val | UARTPFIFO_TXFE | UARTPFIFO_RXFE,
			sport->port.membase + UARTPFIFO);

	/* flush Tx and Rx FIFO */
	ग_लिखोb(UARTCFIFO_TXFLUSH | UARTCFIFO_RXFLUSH,
			sport->port.membase + UARTCFIFO);

	/* explicitly clear RDRF */
	अगर (पढ़ोb(sport->port.membase + UARTSR1) & UARTSR1_RDRF) अणु
		पढ़ोb(sport->port.membase + UARTDR);
		ग_लिखोb(UARTSFIFO_RXUF, sport->port.membase + UARTSFIFO);
	पूर्ण

	ग_लिखोb(0, sport->port.membase + UARTTWFIFO);
	ग_लिखोb(1, sport->port.membase + UARTRWFIFO);

	/* Restore cr2 */
	ग_लिखोb(cr2_saved, sport->port.membase + UARTCR2);
पूर्ण

अटल व्योम lpuart_setup_watermark_enable(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित अक्षर cr2;

	lpuart_setup_watermark(sport);

	cr2 = पढ़ोb(sport->port.membase + UARTCR2);
	cr2 |= UARTCR2_RIE | UARTCR2_RE | UARTCR2_TE;
	ग_लिखोb(cr2, sport->port.membase + UARTCR2);
पूर्ण

अटल व्योम lpuart32_setup_watermark(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित दीर्घ val, ctrl;
	अचिन्हित दीर्घ ctrl_saved;

	ctrl = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	ctrl_saved = ctrl;
	ctrl &= ~(UARTCTRL_TIE | UARTCTRL_TCIE | UARTCTRL_TE |
			UARTCTRL_RIE | UARTCTRL_RE);
	lpuart32_ग_लिखो(&sport->port, ctrl, UARTCTRL);

	/* enable FIFO mode */
	val = lpuart32_पढ़ो(&sport->port, UARTFIFO);
	val |= UARTFIFO_TXFE | UARTFIFO_RXFE;
	val |= UARTFIFO_TXFLUSH | UARTFIFO_RXFLUSH;
	lpuart32_ग_लिखो(&sport->port, val, UARTFIFO);

	/* set the watermark */
	val = (0x1 << UARTWATER_RXWATER_OFF) | (0x0 << UARTWATER_TXWATER_OFF);
	lpuart32_ग_लिखो(&sport->port, val, UARTWATER);

	/* Restore cr2 */
	lpuart32_ग_लिखो(&sport->port, ctrl_saved, UARTCTRL);
पूर्ण

अटल व्योम lpuart32_setup_watermark_enable(काष्ठा lpuart_port *sport)
अणु
	u32 temp;

	lpuart32_setup_watermark(sport);

	temp = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	temp |= UARTCTRL_RE | UARTCTRL_TE | UARTCTRL_ILIE;
	lpuart32_ग_लिखो(&sport->port, temp, UARTCTRL);
पूर्ण

अटल व्योम rx_dma_समयr_init(काष्ठा lpuart_port *sport)
अणु
	समयr_setup(&sport->lpuart_समयr, lpuart_समयr_func, 0);
	sport->lpuart_समयr.expires = jअगरfies + sport->dma_rx_समयout;
	add_समयr(&sport->lpuart_समयr);
पूर्ण

अटल व्योम lpuart_request_dma(काष्ठा lpuart_port *sport)
अणु
	sport->dma_tx_chan = dma_request_chan(sport->port.dev, "tx");
	अगर (IS_ERR(sport->dma_tx_chan)) अणु
		dev_dbg_once(sport->port.dev,
			     "DMA tx channel request failed, operating without tx DMA (%ld)\n",
			     PTR_ERR(sport->dma_tx_chan));
		sport->dma_tx_chan = शून्य;
	पूर्ण

	sport->dma_rx_chan = dma_request_chan(sport->port.dev, "rx");
	अगर (IS_ERR(sport->dma_rx_chan)) अणु
		dev_dbg_once(sport->port.dev,
			     "DMA rx channel request failed, operating without rx DMA (%ld)\n",
			     PTR_ERR(sport->dma_rx_chan));
		sport->dma_rx_chan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम lpuart_tx_dma_startup(काष्ठा lpuart_port *sport)
अणु
	u32 uartbaud;
	पूर्णांक ret;

	अगर (!sport->dma_tx_chan)
		जाओ err;

	ret = lpuart_dma_tx_request(&sport->port);
	अगर (ret)
		जाओ err;

	init_रुकोqueue_head(&sport->dma_रुको);
	sport->lpuart_dma_tx_use = true;
	अगर (lpuart_is_32(sport)) अणु
		uartbaud = lpuart32_पढ़ो(&sport->port, UARTBAUD);
		lpuart32_ग_लिखो(&sport->port,
			       uartbaud | UARTBAUD_TDMAE, UARTBAUD);
	पूर्ण अन्यथा अणु
		ग_लिखोb(पढ़ोb(sport->port.membase + UARTCR5) |
		       UARTCR5_TDMAS, sport->port.membase + UARTCR5);
	पूर्ण

	वापस;

err:
	sport->lpuart_dma_tx_use = false;
पूर्ण

अटल व्योम lpuart_rx_dma_startup(काष्ठा lpuart_port *sport)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर cr3;

	अगर (!sport->dma_rx_chan)
		जाओ err;

	ret = lpuart_start_rx_dma(sport);
	अगर (ret)
		जाओ err;

	/* set Rx DMA समयout */
	sport->dma_rx_समयout = msecs_to_jअगरfies(DMA_RX_TIMEOUT);
	अगर (!sport->dma_rx_समयout)
		sport->dma_rx_समयout = 1;

	sport->lpuart_dma_rx_use = true;
	rx_dma_समयr_init(sport);

	अगर (sport->port.has_sysrq) अणु
		cr3 = पढ़ोb(sport->port.membase + UARTCR3);
		cr3 |= UARTCR3_FEIE;
		ग_लिखोb(cr3, sport->port.membase + UARTCR3);
	पूर्ण

	वापस;

err:
	sport->lpuart_dma_rx_use = false;
पूर्ण

अटल पूर्णांक lpuart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर temp;

	/* determine FIFO size and enable FIFO mode */
	temp = पढ़ोb(sport->port.membase + UARTPFIFO);

	sport->txfअगरo_size = UARTFIFO_DEPTH((temp >> UARTPFIFO_TXSIZE_OFF) &
					    UARTPFIFO_FIFOSIZE_MASK);
	sport->port.fअगरosize = sport->txfअगरo_size;

	sport->rxfअगरo_size = UARTFIFO_DEPTH((temp >> UARTPFIFO_RXSIZE_OFF) &
					    UARTPFIFO_FIFOSIZE_MASK);

	lpuart_request_dma(sport);

	spin_lock_irqsave(&sport->port.lock, flags);

	lpuart_setup_watermark_enable(sport);

	lpuart_rx_dma_startup(sport);
	lpuart_tx_dma_startup(sport);

	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lpuart32_configure(काष्ठा lpuart_port *sport)
अणु
	अचिन्हित दीर्घ temp;

	अगर (sport->lpuart_dma_rx_use) अणु
		/* RXWATER must be 0 */
		temp = lpuart32_पढ़ो(&sport->port, UARTWATER);
		temp &= ~(UARTWATER_WATER_MASK << UARTWATER_RXWATER_OFF);
		lpuart32_ग_लिखो(&sport->port, temp, UARTWATER);
	पूर्ण
	temp = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	अगर (!sport->lpuart_dma_rx_use)
		temp |= UARTCTRL_RIE;
	अगर (!sport->lpuart_dma_tx_use)
		temp |= UARTCTRL_TIE;
	lpuart32_ग_लिखो(&sport->port, temp, UARTCTRL);
पूर्ण

अटल पूर्णांक lpuart32_startup(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ temp;

	/* determine FIFO size */
	temp = lpuart32_पढ़ो(&sport->port, UARTFIFO);

	sport->txfअगरo_size = UARTFIFO_DEPTH((temp >> UARTFIFO_TXSIZE_OFF) &
					    UARTFIFO_FIFOSIZE_MASK);
	sport->port.fअगरosize = sport->txfअगरo_size;

	sport->rxfअगरo_size = UARTFIFO_DEPTH((temp >> UARTFIFO_RXSIZE_OFF) &
					    UARTFIFO_FIFOSIZE_MASK);

	/*
	 * The LS1021A and LS1028A have a fixed FIFO depth of 16 words.
	 * Although they support the RX/TXSIZE fields, their encoding is
	 * dअगरferent. Eg the reference manual states 0b101 is 16 words.
	 */
	अगर (is_layerscape_lpuart(sport)) अणु
		sport->rxfअगरo_size = 16;
		sport->txfअगरo_size = 16;
		sport->port.fअगरosize = sport->txfअगरo_size;
	पूर्ण

	lpuart_request_dma(sport);

	spin_lock_irqsave(&sport->port.lock, flags);

	lpuart32_setup_watermark_enable(sport);

	lpuart_rx_dma_startup(sport);
	lpuart_tx_dma_startup(sport);

	lpuart32_configure(sport);

	spin_unlock_irqrestore(&sport->port.lock, flags);
	वापस 0;
पूर्ण

अटल व्योम lpuart_dma_shutकरोwn(काष्ठा lpuart_port *sport)
अणु
	अगर (sport->lpuart_dma_rx_use) अणु
		del_समयr_sync(&sport->lpuart_समयr);
		lpuart_dma_rx_मुक्त(&sport->port);
	पूर्ण

	अगर (sport->lpuart_dma_tx_use) अणु
		अगर (रुको_event_पूर्णांकerruptible(sport->dma_रुको,
			!sport->dma_tx_in_progress) != false) अणु
			sport->dma_tx_in_progress = false;
			dmaengine_terminate_all(sport->dma_tx_chan);
		पूर्ण
	पूर्ण

	अगर (sport->dma_tx_chan)
		dma_release_channel(sport->dma_tx_chan);
	अगर (sport->dma_rx_chan)
		dma_release_channel(sport->dma_rx_chan);
पूर्ण

अटल व्योम lpuart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित अक्षर temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable Rx/Tx and पूर्णांकerrupts */
	temp = पढ़ोb(port->membase + UARTCR2);
	temp &= ~(UARTCR2_TE | UARTCR2_RE |
			UARTCR2_TIE | UARTCR2_TCIE | UARTCR2_RIE);
	ग_लिखोb(temp, port->membase + UARTCR2);

	spin_unlock_irqrestore(&port->lock, flags);

	lpuart_dma_shutकरोwn(sport);
पूर्ण

अटल व्योम lpuart32_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा lpuart_port *sport =
		container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable Rx/Tx and पूर्णांकerrupts */
	temp = lpuart32_पढ़ो(port, UARTCTRL);
	temp &= ~(UARTCTRL_TE | UARTCTRL_RE |
			UARTCTRL_TIE | UARTCTRL_TCIE | UARTCTRL_RIE);
	lpuart32_ग_लिखो(port, temp, UARTCTRL);

	spin_unlock_irqrestore(&port->lock, flags);

	lpuart_dma_shutकरोwn(sport);
पूर्ण

अटल व्योम
lpuart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		   काष्ठा ktermios *old)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर cr1, old_cr1, old_cr2, cr3, cr4, bdh, modem;
	अचिन्हित पूर्णांक  baud;
	अचिन्हित पूर्णांक old_csize = old ? old->c_cflag & CSIZE : CS8;
	अचिन्हित पूर्णांक sbr, brfa;

	cr1 = old_cr1 = पढ़ोb(sport->port.membase + UARTCR1);
	old_cr2 = पढ़ोb(sport->port.membase + UARTCR2);
	cr3 = पढ़ोb(sport->port.membase + UARTCR3);
	cr4 = पढ़ोb(sport->port.membase + UARTCR4);
	bdh = पढ़ोb(sport->port.membase + UARTBDH);
	modem = पढ़ोb(sport->port.membase + UARTMODEM);
	/*
	 * only support CS8 and CS7, and क्रम CS7 must enable PE.
	 * supported mode:
	 *  - (7,e/o,1)
	 *  - (8,n,1)
	 *  - (8,m/s,1)
	 *  - (8,e/o,1)
	 */
	जबतक ((termios->c_cflag & CSIZE) != CS8 &&
		(termios->c_cflag & CSIZE) != CS7) अणु
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	पूर्ण

	अगर ((termios->c_cflag & CSIZE) == CS8 ||
		(termios->c_cflag & CSIZE) == CS7)
		cr1 = old_cr1 & ~UARTCR1_M;

	अगर (termios->c_cflag & CMSPAR) अणु
		अगर ((termios->c_cflag & CSIZE) != CS8) अणु
			termios->c_cflag &= ~CSIZE;
			termios->c_cflag |= CS8;
		पूर्ण
		cr1 |= UARTCR1_M;
	पूर्ण

	/*
	 * When स्वतः RS-485 RTS mode is enabled,
	 * hardware flow control need to be disabled.
	 */
	अगर (sport->port.rs485.flags & SER_RS485_ENABLED)
		termios->c_cflag &= ~CRTSCTS;

	अगर (termios->c_cflag & CRTSCTS)
		modem |= UARTMODEM_RXRTSE | UARTMODEM_TXCTSE;
	अन्यथा
		modem &= ~(UARTMODEM_RXRTSE | UARTMODEM_TXCTSE);

	termios->c_cflag &= ~CSTOPB;

	/* parity must be enabled when CS7 to match 8-bits क्रमmat */
	अगर ((termios->c_cflag & CSIZE) == CS7)
		termios->c_cflag |= PARENB;

	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & CMSPAR) अणु
			cr1 &= ~UARTCR1_PE;
			अगर (termios->c_cflag & PARODD)
				cr3 |= UARTCR3_T8;
			अन्यथा
				cr3 &= ~UARTCR3_T8;
		पूर्ण अन्यथा अणु
			cr1 |= UARTCR1_PE;
			अगर ((termios->c_cflag & CSIZE) == CS8)
				cr1 |= UARTCR1_M;
			अगर (termios->c_cflag & PARODD)
				cr1 |= UARTCR1_PT;
			अन्यथा
				cr1 &= ~UARTCR1_PT;
		पूर्ण
	पूर्ण अन्यथा अणु
		cr1 &= ~UARTCR1_PE;
	पूर्ण

	/* ask the core to calculate the भागisor */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 16);

	/*
	 * Need to update the Ring buffer length according to the selected
	 * baud rate and restart Rx DMA path.
	 *
	 * Since समयr function acqures sport->port.lock, need to stop beक्रमe
	 * acquring same lock because otherwise del_समयr_sync() can deadlock.
	 */
	अगर (old && sport->lpuart_dma_rx_use) अणु
		del_समयr_sync(&sport->lpuart_समयr);
		lpuart_dma_rx_मुक्त(&sport->port);
	पूर्ण

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.पढ़ो_status_mask = 0;
	अगर (termios->c_अगरlag & INPCK)
		sport->port.पढ़ो_status_mask |= UARTSR1_FE | UARTSR1_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		sport->port.पढ़ो_status_mask |= UARTSR1_FE;

	/* अक्षरacters to ignore */
	sport->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		sport->port.ignore_status_mask |= UARTSR1_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		sport->port.ignore_status_mask |= UARTSR1_FE;
		/*
		 * अगर we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			sport->port.ignore_status_mask |= UARTSR1_OR;
	पूर्ण

	/* update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* रुको transmit engin complete */
	lpuart_रुको_bit_set(&sport->port, UARTSR1, UARTSR1_TC);

	/* disable transmit and receive */
	ग_लिखोb(old_cr2 & ~(UARTCR2_TE | UARTCR2_RE),
			sport->port.membase + UARTCR2);

	sbr = sport->port.uartclk / (16 * baud);
	brfa = ((sport->port.uartclk - (16 * sbr * baud)) * 2) / baud;
	bdh &= ~UARTBDH_SBR_MASK;
	bdh |= (sbr >> 8) & 0x1F;
	cr4 &= ~UARTCR4_BRFA_MASK;
	brfa &= UARTCR4_BRFA_MASK;
	ग_लिखोb(cr4 | brfa, sport->port.membase + UARTCR4);
	ग_लिखोb(bdh, sport->port.membase + UARTBDH);
	ग_लिखोb(sbr & 0xFF, sport->port.membase + UARTBDL);
	ग_लिखोb(cr3, sport->port.membase + UARTCR3);
	ग_लिखोb(cr1, sport->port.membase + UARTCR1);
	ग_लिखोb(modem, sport->port.membase + UARTMODEM);

	/* restore control रेजिस्टर */
	ग_लिखोb(old_cr2, sport->port.membase + UARTCR2);

	अगर (old && sport->lpuart_dma_rx_use) अणु
		अगर (!lpuart_start_rx_dma(sport))
			rx_dma_समयr_init(sport);
		अन्यथा
			sport->lpuart_dma_rx_use = false;
	पूर्ण

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम __lpuart32_serial_setbrg(काष्ठा uart_port *port,
				     अचिन्हित पूर्णांक baudrate, bool use_rx_dma,
				     bool use_tx_dma)
अणु
	u32 sbr, osr, baud_dअगरf, पंचांगp_osr, पंचांगp_sbr, पंचांगp_dअगरf, पंचांगp;
	u32 clk = port->uartclk;

	/*
	 * The idea is to use the best OSR (over-sampling rate) possible.
	 * Note, OSR is typically hard-set to 16 in other LPUART instantiations.
	 * Loop to find the best OSR value possible, one that generates minimum
	 * baud_dअगरf iterate through the rest of the supported values of OSR.
	 *
	 * Calculation Formula:
	 *  Baud Rate = baud घड़ी / ((OSR+1) थ SBR)
	 */
	baud_dअगरf = baudrate;
	osr = 0;
	sbr = 0;

	क्रम (पंचांगp_osr = 4; पंचांगp_osr <= 32; पंचांगp_osr++) अणु
		/* calculate the temporary sbr value  */
		पंचांगp_sbr = (clk / (baudrate * पंचांगp_osr));
		अगर (पंचांगp_sbr == 0)
			पंचांगp_sbr = 1;

		/*
		 * calculate the baud rate dअगरference based on the temporary
		 * osr and sbr values
		 */
		पंचांगp_dअगरf = clk / (पंचांगp_osr * पंचांगp_sbr) - baudrate;

		/* select best values between sbr and sbr+1 */
		पंचांगp = clk / (पंचांगp_osr * (पंचांगp_sbr + 1));
		अगर (पंचांगp_dअगरf > (baudrate - पंचांगp)) अणु
			पंचांगp_dअगरf = baudrate - पंचांगp;
			पंचांगp_sbr++;
		पूर्ण

		अगर (पंचांगp_sbr > UARTBAUD_SBR_MASK)
			जारी;

		अगर (पंचांगp_dअगरf <= baud_dअगरf) अणु
			baud_dअगरf = पंचांगp_dअगरf;
			osr = पंचांगp_osr;
			sbr = पंचांगp_sbr;

			अगर (!baud_dअगरf)
				अवरोध;
		पूर्ण
	पूर्ण

	/* handle buadrate outside acceptable rate */
	अगर (baud_dअगरf > ((baudrate / 100) * 3))
		dev_warn(port->dev,
			 "unacceptable baud rate difference of more than 3%%\n");

	पंचांगp = lpuart32_पढ़ो(port, UARTBAUD);

	अगर ((osr > 3) && (osr < 8))
		पंचांगp |= UARTBAUD_BOTHEDGE;

	पंचांगp &= ~(UARTBAUD_OSR_MASK << UARTBAUD_OSR_SHIFT);
	पंचांगp |= ((osr-1) & UARTBAUD_OSR_MASK) << UARTBAUD_OSR_SHIFT;

	पंचांगp &= ~UARTBAUD_SBR_MASK;
	पंचांगp |= sbr & UARTBAUD_SBR_MASK;

	अगर (!use_rx_dma)
		पंचांगp &= ~UARTBAUD_RDMAE;
	अगर (!use_tx_dma)
		पंचांगp &= ~UARTBAUD_TDMAE;

	lpuart32_ग_लिखो(port, पंचांगp, UARTBAUD);
पूर्ण

अटल व्योम lpuart32_serial_setbrg(काष्ठा lpuart_port *sport,
				   अचिन्हित पूर्णांक baudrate)
अणु
	__lpuart32_serial_setbrg(&sport->port, baudrate,
				 sport->lpuart_dma_rx_use,
				 sport->lpuart_dma_tx_use);
पूर्ण


अटल व्योम
lpuart32_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		   काष्ठा ktermios *old)
अणु
	काष्ठा lpuart_port *sport = container_of(port, काष्ठा lpuart_port, port);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ ctrl, old_ctrl, modem;
	अचिन्हित पूर्णांक  baud;
	अचिन्हित पूर्णांक old_csize = old ? old->c_cflag & CSIZE : CS8;

	ctrl = old_ctrl = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	modem = lpuart32_पढ़ो(&sport->port, UARTMOसूची);
	/*
	 * only support CS8 and CS7, and क्रम CS7 must enable PE.
	 * supported mode:
	 *  - (7,e/o,1)
	 *  - (8,n,1)
	 *  - (8,m/s,1)
	 *  - (8,e/o,1)
	 */
	जबतक ((termios->c_cflag & CSIZE) != CS8 &&
		(termios->c_cflag & CSIZE) != CS7) अणु
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	पूर्ण

	अगर ((termios->c_cflag & CSIZE) == CS8 ||
		(termios->c_cflag & CSIZE) == CS7)
		ctrl = old_ctrl & ~UARTCTRL_M;

	अगर (termios->c_cflag & CMSPAR) अणु
		अगर ((termios->c_cflag & CSIZE) != CS8) अणु
			termios->c_cflag &= ~CSIZE;
			termios->c_cflag |= CS8;
		पूर्ण
		ctrl |= UARTCTRL_M;
	पूर्ण

	/*
	 * When स्वतः RS-485 RTS mode is enabled,
	 * hardware flow control need to be disabled.
	 */
	अगर (sport->port.rs485.flags & SER_RS485_ENABLED)
		termios->c_cflag &= ~CRTSCTS;

	अगर (termios->c_cflag & CRTSCTS) अणु
		modem |= (UARTMOसूची_RXRTSE | UARTMOसूची_TXCTSE);
	पूर्ण अन्यथा अणु
		termios->c_cflag &= ~CRTSCTS;
		modem &= ~(UARTMOसूची_RXRTSE | UARTMOसूची_TXCTSE);
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		termios->c_cflag &= ~CSTOPB;

	/* parity must be enabled when CS7 to match 8-bits क्रमmat */
	अगर ((termios->c_cflag & CSIZE) == CS7)
		termios->c_cflag |= PARENB;

	अगर ((termios->c_cflag & PARENB)) अणु
		अगर (termios->c_cflag & CMSPAR) अणु
			ctrl &= ~UARTCTRL_PE;
			ctrl |= UARTCTRL_M;
		पूर्ण अन्यथा अणु
			ctrl |= UARTCTRL_PE;
			अगर ((termios->c_cflag & CSIZE) == CS8)
				ctrl |= UARTCTRL_M;
			अगर (termios->c_cflag & PARODD)
				ctrl |= UARTCTRL_PT;
			अन्यथा
				ctrl &= ~UARTCTRL_PT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl &= ~UARTCTRL_PE;
	पूर्ण

	/* ask the core to calculate the भागisor */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 4);

	/*
	 * Need to update the Ring buffer length according to the selected
	 * baud rate and restart Rx DMA path.
	 *
	 * Since समयr function acqures sport->port.lock, need to stop beक्रमe
	 * acquring same lock because otherwise del_समयr_sync() can deadlock.
	 */
	अगर (old && sport->lpuart_dma_rx_use) अणु
		del_समयr_sync(&sport->lpuart_समयr);
		lpuart_dma_rx_मुक्त(&sport->port);
	पूर्ण

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.पढ़ो_status_mask = 0;
	अगर (termios->c_अगरlag & INPCK)
		sport->port.पढ़ो_status_mask |= UARTSTAT_FE | UARTSTAT_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		sport->port.पढ़ो_status_mask |= UARTSTAT_FE;

	/* अक्षरacters to ignore */
	sport->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		sport->port.ignore_status_mask |= UARTSTAT_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		sport->port.ignore_status_mask |= UARTSTAT_FE;
		/*
		 * अगर we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			sport->port.ignore_status_mask |= UARTSTAT_OR;
	पूर्ण

	/* update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* रुको transmit engin complete */
	lpuart32_रुको_bit_set(&sport->port, UARTSTAT, UARTSTAT_TC);

	/* disable transmit and receive */
	lpuart32_ग_लिखो(&sport->port, old_ctrl & ~(UARTCTRL_TE | UARTCTRL_RE),
		       UARTCTRL);

	lpuart32_serial_setbrg(sport, baud);
	lpuart32_ग_लिखो(&sport->port, modem, UARTMOसूची);
	lpuart32_ग_लिखो(&sport->port, ctrl, UARTCTRL);
	/* restore control रेजिस्टर */

	अगर (old && sport->lpuart_dma_rx_use) अणु
		अगर (!lpuart_start_rx_dma(sport))
			rx_dma_समयr_init(sport);
		अन्यथा
			sport->lpuart_dma_rx_use = false;
	पूर्ण

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *lpuart_type(काष्ठा uart_port *port)
अणु
	वापस "FSL_LPUART";
पूर्ण

अटल व्योम lpuart_release_port(काष्ठा uart_port *port)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक lpuart_request_port(काष्ठा uart_port *port)
अणु
	वापस  0;
पूर्ण

/* configure/स्वतःconfigure the port */
अटल व्योम lpuart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_LPUART;
पूर्ण

अटल पूर्णांक lpuart_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_LPUART)
		ret = -EINVAL;
	अगर (port->irq != ser->irq)
		ret = -EINVAL;
	अगर (ser->io_type != UPIO_MEM)
		ret = -EINVAL;
	अगर (port->uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	अगर (port->iobase != ser->port)
		ret = -EINVAL;
	अगर (ser->hub6 != 0)
		ret = -EINVAL;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा uart_ops lpuart_pops = अणु
	.tx_empty	= lpuart_tx_empty,
	.set_mctrl	= lpuart_set_mctrl,
	.get_mctrl	= lpuart_get_mctrl,
	.stop_tx	= lpuart_stop_tx,
	.start_tx	= lpuart_start_tx,
	.stop_rx	= lpuart_stop_rx,
	.अवरोध_ctl	= lpuart_अवरोध_ctl,
	.startup	= lpuart_startup,
	.shutकरोwn	= lpuart_shutकरोwn,
	.set_termios	= lpuart_set_termios,
	.type		= lpuart_type,
	.request_port	= lpuart_request_port,
	.release_port	= lpuart_release_port,
	.config_port	= lpuart_config_port,
	.verअगरy_port	= lpuart_verअगरy_port,
	.flush_buffer	= lpuart_flush_buffer,
#अगर defined(CONFIG_CONSOLE_POLL)
	.poll_init	= lpuart_poll_init,
	.poll_get_अक्षर	= lpuart_poll_get_अक्षर,
	.poll_put_अक्षर	= lpuart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा uart_ops lpuart32_pops = अणु
	.tx_empty	= lpuart32_tx_empty,
	.set_mctrl	= lpuart32_set_mctrl,
	.get_mctrl	= lpuart32_get_mctrl,
	.stop_tx	= lpuart32_stop_tx,
	.start_tx	= lpuart32_start_tx,
	.stop_rx	= lpuart32_stop_rx,
	.अवरोध_ctl	= lpuart32_अवरोध_ctl,
	.startup	= lpuart32_startup,
	.shutकरोwn	= lpuart32_shutकरोwn,
	.set_termios	= lpuart32_set_termios,
	.type		= lpuart_type,
	.request_port	= lpuart_request_port,
	.release_port	= lpuart_release_port,
	.config_port	= lpuart_config_port,
	.verअगरy_port	= lpuart_verअगरy_port,
	.flush_buffer	= lpuart_flush_buffer,
#अगर defined(CONFIG_CONSOLE_POLL)
	.poll_init	= lpuart32_poll_init,
	.poll_get_अक्षर	= lpuart32_poll_get_अक्षर,
	.poll_put_अक्षर	= lpuart32_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा lpuart_port *lpuart_ports[UART_NR];

#अगर_घोषित CONFIG_SERIAL_FSL_LPUART_CONSOLE
अटल व्योम lpuart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	lpuart_रुको_bit_set(port, UARTSR1, UARTSR1_TDRE);
	ग_लिखोb(ch, port->membase + UARTDR);
पूर्ण

अटल व्योम lpuart32_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	lpuart32_रुको_bit_set(port, UARTSTAT, UARTSTAT_TDRE);
	lpuart32_ग_लिखो(port, ch, UARTDATA);
पूर्ण

अटल व्योम
lpuart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा lpuart_port *sport = lpuart_ports[co->index];
	अचिन्हित अक्षर  old_cr2, cr2;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (sport->port.sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&sport->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&sport->port.lock, flags);

	/* first save CR2 and then disable पूर्णांकerrupts */
	cr2 = old_cr2 = पढ़ोb(sport->port.membase + UARTCR2);
	cr2 |= UARTCR2_TE | UARTCR2_RE;
	cr2 &= ~(UARTCR2_TIE | UARTCR2_TCIE | UARTCR2_RIE);
	ग_लिखोb(cr2, sport->port.membase + UARTCR2);

	uart_console_ग_लिखो(&sport->port, s, count, lpuart_console_अक्षर_दो);

	/* रुको क्रम transmitter finish complete and restore CR2 */
	lpuart_रुको_bit_set(&sport->port, UARTSR1, UARTSR1_TC);

	ग_लिखोb(old_cr2, sport->port.membase + UARTCR2);

	अगर (locked)
		spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम
lpuart32_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा lpuart_port *sport = lpuart_ports[co->index];
	अचिन्हित दीर्घ  old_cr, cr;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (sport->port.sysrq || oops_in_progress)
		locked = spin_trylock_irqsave(&sport->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&sport->port.lock, flags);

	/* first save CR2 and then disable पूर्णांकerrupts */
	cr = old_cr = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	cr |= UARTCTRL_TE | UARTCTRL_RE;
	cr &= ~(UARTCTRL_TIE | UARTCTRL_TCIE | UARTCTRL_RIE);
	lpuart32_ग_लिखो(&sport->port, cr, UARTCTRL);

	uart_console_ग_लिखो(&sport->port, s, count, lpuart32_console_अक्षर_दो);

	/* रुको क्रम transmitter finish complete and restore CR2 */
	lpuart32_रुको_bit_set(&sport->port, UARTSTAT, UARTSTAT_TC);

	lpuart32_ग_लिखो(&sport->port, old_cr, UARTCTRL);

	अगर (locked)
		spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

/*
 * अगर the port was alपढ़ोy initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
अटल व्योम __init
lpuart_console_get_options(काष्ठा lpuart_port *sport, पूर्णांक *baud,
			   पूर्णांक *parity, पूर्णांक *bits)
अणु
	अचिन्हित अक्षर cr, bdh, bdl, brfa;
	अचिन्हित पूर्णांक sbr, uartclk, baud_raw;

	cr = पढ़ोb(sport->port.membase + UARTCR2);
	cr &= UARTCR2_TE | UARTCR2_RE;
	अगर (!cr)
		वापस;

	/* ok, the port was enabled */

	cr = पढ़ोb(sport->port.membase + UARTCR1);

	*parity = 'n';
	अगर (cr & UARTCR1_PE) अणु
		अगर (cr & UARTCR1_PT)
			*parity = 'o';
		अन्यथा
			*parity = 'e';
	पूर्ण

	अगर (cr & UARTCR1_M)
		*bits = 9;
	अन्यथा
		*bits = 8;

	bdh = पढ़ोb(sport->port.membase + UARTBDH);
	bdh &= UARTBDH_SBR_MASK;
	bdl = पढ़ोb(sport->port.membase + UARTBDL);
	sbr = bdh;
	sbr <<= 8;
	sbr |= bdl;
	brfa = पढ़ोb(sport->port.membase + UARTCR4);
	brfa &= UARTCR4_BRFA_MASK;

	uartclk = lpuart_get_baud_clk_rate(sport);
	/*
	 * baud = mod_clk/(16*(sbr[13]+(brfa)/32)
	 */
	baud_raw = uartclk / (16 * (sbr + brfa / 32));

	अगर (*baud != baud_raw)
		dev_info(sport->port.dev, "Serial: Console lpuart rounded baud rate"
				"from %d to %d\n", baud_raw, *baud);
पूर्ण

अटल व्योम __init
lpuart32_console_get_options(काष्ठा lpuart_port *sport, पूर्णांक *baud,
			   पूर्णांक *parity, पूर्णांक *bits)
अणु
	अचिन्हित दीर्घ cr, bd;
	अचिन्हित पूर्णांक sbr, uartclk, baud_raw;

	cr = lpuart32_पढ़ो(&sport->port, UARTCTRL);
	cr &= UARTCTRL_TE | UARTCTRL_RE;
	अगर (!cr)
		वापस;

	/* ok, the port was enabled */

	cr = lpuart32_पढ़ो(&sport->port, UARTCTRL);

	*parity = 'n';
	अगर (cr & UARTCTRL_PE) अणु
		अगर (cr & UARTCTRL_PT)
			*parity = 'o';
		अन्यथा
			*parity = 'e';
	पूर्ण

	अगर (cr & UARTCTRL_M)
		*bits = 9;
	अन्यथा
		*bits = 8;

	bd = lpuart32_पढ़ो(&sport->port, UARTBAUD);
	bd &= UARTBAUD_SBR_MASK;
	sbr = bd;
	uartclk = lpuart_get_baud_clk_rate(sport);
	/*
	 * baud = mod_clk/(16*(sbr[13]+(brfa)/32)
	 */
	baud_raw = uartclk / (16 * sbr);

	अगर (*baud != baud_raw)
		dev_info(sport->port.dev, "Serial: Console lpuart rounded baud rate"
				"from %d to %d\n", baud_raw, *baud);
पूर्ण

अटल पूर्णांक __init lpuart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा lpuart_port *sport;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	/*
	 * check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index == -1 || co->index >= ARRAY_SIZE(lpuart_ports))
		co->index = 0;

	sport = lpuart_ports[co->index];
	अगर (sport == शून्य)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		अगर (lpuart_is_32(sport))
			lpuart32_console_get_options(sport, &baud, &parity, &bits);
		अन्यथा
			lpuart_console_get_options(sport, &baud, &parity, &bits);

	अगर (lpuart_is_32(sport))
		lpuart32_setup_watermark(sport);
	अन्यथा
		lpuart_setup_watermark(sport);

	वापस uart_set_options(&sport->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver lpuart_reg;
अटल काष्ठा console lpuart_console = अणु
	.name		= DEV_NAME,
	.ग_लिखो		= lpuart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= lpuart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &lpuart_reg,
पूर्ण;

अटल काष्ठा console lpuart32_console = अणु
	.name		= DEV_NAME,
	.ग_लिखो		= lpuart32_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= lpuart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &lpuart_reg,
पूर्ण;

अटल व्योम lpuart_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, lpuart_console_अक्षर_दो);
पूर्ण

अटल व्योम lpuart32_early_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, lpuart32_console_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init lpuart_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = lpuart_early_ग_लिखो;
	वापस 0;
पूर्ण

अटल पूर्णांक __init lpuart32_early_console_setup(काष्ठा earlycon_device *device,
					  स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	अगर (device->port.iotype != UPIO_MEM32)
		device->port.iotype = UPIO_MEM32BE;

	device->con->ग_लिखो = lpuart32_early_ग_लिखो;
	वापस 0;
पूर्ण

अटल पूर्णांक __init ls1028a_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *opt)
अणु
	u32 cr;

	अगर (!device->port.membase)
		वापस -ENODEV;

	device->port.iotype = UPIO_MEM32;
	device->con->ग_लिखो = lpuart32_early_ग_लिखो;

	/* set the baudrate */
	अगर (device->port.uartclk && device->baud)
		__lpuart32_serial_setbrg(&device->port, device->baud,
					 false, false);

	/* enable transmitter */
	cr = lpuart32_पढ़ो(&device->port, UARTCTRL);
	cr |= UARTCTRL_TE;
	lpuart32_ग_लिखो(&device->port, cr, UARTCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक __init lpuart32_imx_early_console_setup(काष्ठा earlycon_device *device,
						   स्थिर अक्षर *opt)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->port.iotype = UPIO_MEM32;
	device->port.membase += IMX_REG_OFF;
	device->con->ग_लिखो = lpuart32_early_ग_लिखो;

	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(lpuart, "fsl,vf610-lpuart", lpuart_early_console_setup);
OF_EARLYCON_DECLARE(lpuart32, "fsl,ls1021a-lpuart", lpuart32_early_console_setup);
OF_EARLYCON_DECLARE(lpuart32, "fsl,ls1028a-lpuart", ls1028a_early_console_setup);
OF_EARLYCON_DECLARE(lpuart32, "fsl,imx7ulp-lpuart", lpuart32_imx_early_console_setup);
EARLYCON_DECLARE(lpuart, lpuart_early_console_setup);
EARLYCON_DECLARE(lpuart32, lpuart32_early_console_setup);

#घोषणा LPUART_CONSOLE	(&lpuart_console)
#घोषणा LPUART32_CONSOLE	(&lpuart32_console)
#अन्यथा
#घोषणा LPUART_CONSOLE	शून्य
#घोषणा LPUART32_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver lpuart_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= DEV_NAME,
	.nr		= ARRAY_SIZE(lpuart_ports),
	.cons		= LPUART_CONSOLE,
पूर्ण;

अटल पूर्णांक lpuart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा lpuart_soc_data *sdata = of_device_get_match_data(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा lpuart_port *sport;
	काष्ठा resource *res;
	पूर्णांक ret;

	sport = devm_kzalloc(&pdev->dev, माप(*sport), GFP_KERNEL);
	अगर (!sport)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sport->port.membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sport->port.membase))
		वापस PTR_ERR(sport->port.membase);

	sport->port.membase += sdata->reg_off;
	sport->port.mapbase = res->start;
	sport->port.dev = &pdev->dev;
	sport->port.type = PORT_LPUART;
	sport->devtype = sdata->devtype;
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	sport->port.irq = ret;
	sport->port.iotype = sdata->iotype;
	अगर (lpuart_is_32(sport))
		sport->port.ops = &lpuart32_pops;
	अन्यथा
		sport->port.ops = &lpuart_pops;
	sport->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_FSL_LPUART_CONSOLE);
	sport->port.flags = UPF_BOOT_AUTOCONF;

	अगर (lpuart_is_32(sport))
		sport->port.rs485_config = lpuart32_config_rs485;
	अन्यथा
		sport->port.rs485_config = lpuart_config_rs485;

	sport->ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(sport->ipg_clk)) अणु
		ret = PTR_ERR(sport->ipg_clk);
		dev_err(&pdev->dev, "failed to get uart ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण

	sport->baud_clk = शून्य;
	अगर (is_imx8qxp_lpuart(sport)) अणु
		sport->baud_clk = devm_clk_get(&pdev->dev, "baud");
		अगर (IS_ERR(sport->baud_clk)) अणु
			ret = PTR_ERR(sport->baud_clk);
			dev_err(&pdev->dev, "failed to get uart baud clk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		ret = ida_simple_get(&fsl_lpuart_ida, 0, UART_NR, GFP_KERNEL);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "port line is full, add device failed\n");
			वापस ret;
		पूर्ण
		sport->id_allocated = true;
	पूर्ण
	अगर (ret >= ARRAY_SIZE(lpuart_ports)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n", ret);
		ret = -EINVAL;
		जाओ failed_out_of_range;
	पूर्ण
	sport->port.line = ret;

	ret = lpuart_enable_clks(sport);
	अगर (ret)
		जाओ failed_घड़ी_enable;
	sport->port.uartclk = lpuart_get_baud_clk_rate(sport);

	lpuart_ports[sport->port.line] = sport;

	platक्रमm_set_drvdata(pdev, &sport->port);

	अगर (lpuart_is_32(sport)) अणु
		lpuart_reg.cons = LPUART32_CONSOLE;
		ret = devm_request_irq(&pdev->dev, sport->port.irq, lpuart32_पूर्णांक, 0,
					DRIVER_NAME, sport);
	पूर्ण अन्यथा अणु
		lpuart_reg.cons = LPUART_CONSOLE;
		ret = devm_request_irq(&pdev->dev, sport->port.irq, lpuart_पूर्णांक, 0,
					DRIVER_NAME, sport);
	पूर्ण

	अगर (ret)
		जाओ failed_irq_request;

	ret = uart_add_one_port(&lpuart_reg, &sport->port);
	अगर (ret)
		जाओ failed_attach_port;

	ret = uart_get_rs485_mode(&sport->port);
	अगर (ret)
		जाओ failed_get_rs485;

	अगर (sport->port.rs485.flags & SER_RS485_RX_DURING_TX)
		dev_err(&pdev->dev, "driver doesn't support RX during TX\n");

	अगर (sport->port.rs485.delay_rts_beक्रमe_send ||
	    sport->port.rs485.delay_rts_after_send)
		dev_err(&pdev->dev, "driver doesn't support RTS delays\n");

	sport->port.rs485_config(&sport->port, &sport->port.rs485);

	वापस 0;

failed_get_rs485:
failed_attach_port:
failed_irq_request:
	lpuart_disable_clks(sport);
failed_घड़ी_enable:
failed_out_of_range:
	अगर (sport->id_allocated)
		ida_simple_हटाओ(&fsl_lpuart_ida, sport->port.line);
	वापस ret;
पूर्ण

अटल पूर्णांक lpuart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpuart_port *sport = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&lpuart_reg, &sport->port);

	अगर (sport->id_allocated)
		ida_simple_हटाओ(&fsl_lpuart_ida, sport->port.line);

	lpuart_disable_clks(sport);

	अगर (sport->dma_tx_chan)
		dma_release_channel(sport->dma_tx_chan);

	अगर (sport->dma_rx_chan)
		dma_release_channel(sport->dma_rx_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lpuart_suspend(काष्ठा device *dev)
अणु
	काष्ठा lpuart_port *sport = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	bool irq_wake;

	अगर (lpuart_is_32(sport)) अणु
		/* disable Rx/Tx and पूर्णांकerrupts */
		temp = lpuart32_पढ़ो(&sport->port, UARTCTRL);
		temp &= ~(UARTCTRL_TE | UARTCTRL_TIE | UARTCTRL_TCIE);
		lpuart32_ग_लिखो(&sport->port, temp, UARTCTRL);
	पूर्ण अन्यथा अणु
		/* disable Rx/Tx and पूर्णांकerrupts */
		temp = पढ़ोb(sport->port.membase + UARTCR2);
		temp &= ~(UARTCR2_TE | UARTCR2_TIE | UARTCR2_TCIE);
		ग_लिखोb(temp, sport->port.membase + UARTCR2);
	पूर्ण

	uart_suspend_port(&lpuart_reg, &sport->port);

	/* uart_suspend_port() might set wakeup flag */
	irq_wake = irqd_is_wakeup_set(irq_get_irq_data(sport->port.irq));

	अगर (sport->lpuart_dma_rx_use) अणु
		/*
		 * EDMA driver during suspend will क्रमcefully release any
		 * non-idle DMA channels. If port wakeup is enabled or अगर port
		 * is console port or 'no_console_suspend' is set the Rx DMA
		 * cannot resume as as expected, hence gracefully release the
		 * Rx DMA path beक्रमe suspend and start Rx DMA path on resume.
		 */
		अगर (irq_wake) अणु
			del_समयr_sync(&sport->lpuart_समयr);
			lpuart_dma_rx_मुक्त(&sport->port);
		पूर्ण

		/* Disable Rx DMA to use UART port as wakeup source */
		अगर (lpuart_is_32(sport)) अणु
			temp = lpuart32_पढ़ो(&sport->port, UARTBAUD);
			lpuart32_ग_लिखो(&sport->port, temp & ~UARTBAUD_RDMAE,
				       UARTBAUD);
		पूर्ण अन्यथा अणु
			ग_लिखोb(पढ़ोb(sport->port.membase + UARTCR5) &
			       ~UARTCR5_RDMAS, sport->port.membase + UARTCR5);
		पूर्ण
	पूर्ण

	अगर (sport->lpuart_dma_tx_use) अणु
		sport->dma_tx_in_progress = false;
		dmaengine_terminate_all(sport->dma_tx_chan);
	पूर्ण

	अगर (sport->port.suspended && !irq_wake)
		lpuart_disable_clks(sport);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused lpuart_resume(काष्ठा device *dev)
अणु
	काष्ठा lpuart_port *sport = dev_get_drvdata(dev);
	bool irq_wake = irqd_is_wakeup_set(irq_get_irq_data(sport->port.irq));

	अगर (sport->port.suspended && !irq_wake)
		lpuart_enable_clks(sport);

	अगर (lpuart_is_32(sport))
		lpuart32_setup_watermark_enable(sport);
	अन्यथा
		lpuart_setup_watermark_enable(sport);

	अगर (sport->lpuart_dma_rx_use) अणु
		अगर (irq_wake) अणु
			अगर (!lpuart_start_rx_dma(sport))
				rx_dma_समयr_init(sport);
			अन्यथा
				sport->lpuart_dma_rx_use = false;
		पूर्ण
	पूर्ण

	lpuart_tx_dma_startup(sport);

	अगर (lpuart_is_32(sport))
		lpuart32_configure(sport);

	uart_resume_port(&lpuart_reg, &sport->port);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(lpuart_pm_ops, lpuart_suspend, lpuart_resume);

अटल काष्ठा platक्रमm_driver lpuart_driver = अणु
	.probe		= lpuart_probe,
	.हटाओ		= lpuart_हटाओ,
	.driver		= अणु
		.name	= "fsl-lpuart",
		.of_match_table = lpuart_dt_ids,
		.pm	= &lpuart_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpuart_serial_init(व्योम)
अणु
	पूर्णांक ret = uart_रेजिस्टर_driver(&lpuart_reg);

	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&lpuart_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&lpuart_reg);

	वापस ret;
पूर्ण

अटल व्योम __निकास lpuart_serial_निकास(व्योम)
अणु
	ida_destroy(&fsl_lpuart_ida);
	platक्रमm_driver_unरेजिस्टर(&lpuart_driver);
	uart_unरेजिस्टर_driver(&lpuart_reg);
पूर्ण

module_init(lpuart_serial_init);
module_निकास(lpuart_serial_निकास);

MODULE_DESCRIPTION("Freescale lpuart serial port driver");
MODULE_LICENSE("GPL v2");
