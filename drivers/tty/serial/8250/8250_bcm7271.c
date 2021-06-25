<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020, Broadcom */
/*
 * 8250-core based driver क्रम Broadcom ns16550a UARTs
 *
 * This driver uses the standard 8250 driver core but adds additional
 * optional features including the ability to use a baud rate घड़ी
 * mux क्रम more accurate high speed baud rate selection and also
 * an optional DMA engine.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>

#समावेश "8250.h"

/* Register definitions क्रम UART DMA block. Version 1.1 or later. */
#घोषणा UDMA_ARB_RX		0x00
#घोषणा UDMA_ARB_TX		0x04
#घोषणा		UDMA_ARB_REQ				0x00000001
#घोषणा		UDMA_ARB_GRANT				0x00000002

#घोषणा UDMA_RX_REVISION	0x00
#घोषणा UDMA_RX_REVISION_REQUIRED			0x00000101
#घोषणा UDMA_RX_CTRL		0x04
#घोषणा		UDMA_RX_CTRL_BUF_CLOSE_MODE		0x00010000
#घोषणा		UDMA_RX_CTRL_MASK_WR_DONE		0x00008000
#घोषणा		UDMA_RX_CTRL_ENDIAN_OVERRIDE		0x00004000
#घोषणा		UDMA_RX_CTRL_ENDIAN			0x00002000
#घोषणा		UDMA_RX_CTRL_OE_IS_ERR			0x00001000
#घोषणा		UDMA_RX_CTRL_PE_IS_ERR			0x00000800
#घोषणा		UDMA_RX_CTRL_FE_IS_ERR			0x00000400
#घोषणा		UDMA_RX_CTRL_NUM_BUF_USED_MASK		0x000003c0
#घोषणा		UDMA_RX_CTRL_NUM_BUF_USED_SHIFT	6
#घोषणा		UDMA_RX_CTRL_BUF_CLOSE_CLK_SEL_SYS	0x00000020
#घोषणा		UDMA_RX_CTRL_BUF_CLOSE_ENA		0x00000010
#घोषणा		UDMA_RX_CTRL_TIMEOUT_CLK_SEL_SYS	0x00000008
#घोषणा		UDMA_RX_CTRL_TIMEOUT_ENA		0x00000004
#घोषणा		UDMA_RX_CTRL_ABORT			0x00000002
#घोषणा		UDMA_RX_CTRL_ENA			0x00000001
#घोषणा UDMA_RX_STATUS		0x08
#घोषणा		UDMA_RX_STATUS_ACTIVE_BUF_MASK		0x0000000f
#घोषणा UDMA_RX_TRANSFER_LEN	0x0c
#घोषणा UDMA_RX_TRANSFER_TOTAL	0x10
#घोषणा UDMA_RX_BUFFER_SIZE	0x14
#घोषणा UDMA_RX_SRC_ADDR	0x18
#घोषणा UDMA_RX_TIMEOUT		0x1c
#घोषणा UDMA_RX_BUFFER_CLOSE	0x20
#घोषणा UDMA_RX_BLOCKOUT_COUNTER 0x24
#घोषणा UDMA_RX_BUF0_PTR_LO	0x28
#घोषणा UDMA_RX_BUF0_PTR_HI	0x2c
#घोषणा UDMA_RX_BUF0_STATUS	0x30
#घोषणा		UDMA_RX_BUFX_STATUS_OVERRUN_ERR		0x00000010
#घोषणा		UDMA_RX_BUFX_STATUS_FRAME_ERR		0x00000008
#घोषणा		UDMA_RX_BUFX_STATUS_PARITY_ERR		0x00000004
#घोषणा		UDMA_RX_BUFX_STATUS_CLOSE_EXPIRED	0x00000002
#घोषणा		UDMA_RX_BUFX_STATUS_DATA_RDY		0x00000001
#घोषणा UDMA_RX_BUF0_DATA_LEN	0x34
#घोषणा UDMA_RX_BUF1_PTR_LO	0x38
#घोषणा UDMA_RX_BUF1_PTR_HI	0x3c
#घोषणा UDMA_RX_BUF1_STATUS	0x40
#घोषणा UDMA_RX_BUF1_DATA_LEN	0x44

#घोषणा UDMA_TX_REVISION	0x00
#घोषणा UDMA_TX_REVISION_REQUIRED			0x00000101
#घोषणा UDMA_TX_CTRL		0x04
#घोषणा		UDMA_TX_CTRL_ENDIAN_OVERRIDE		0x00000080
#घोषणा		UDMA_TX_CTRL_ENDIAN			0x00000040
#घोषणा		UDMA_TX_CTRL_NUM_BUF_USED_MASK		0x00000030
#घोषणा		UDMA_TX_CTRL_NUM_BUF_USED_1		0x00000010
#घोषणा		UDMA_TX_CTRL_ABORT			0x00000002
#घोषणा		UDMA_TX_CTRL_ENA			0x00000001
#घोषणा UDMA_TX_DST_ADDR	0x08
#घोषणा UDMA_TX_BLOCKOUT_COUNTER 0x10
#घोषणा UDMA_TX_TRANSFER_LEN	0x14
#घोषणा UDMA_TX_TRANSFER_TOTAL	0x18
#घोषणा UDMA_TX_STATUS		0x20
#घोषणा UDMA_TX_BUF0_PTR_LO	0x24
#घोषणा UDMA_TX_BUF0_PTR_HI	0x28
#घोषणा UDMA_TX_BUF0_STATUS	0x2c
#घोषणा		UDMA_TX_BUFX_LAST			0x00000002
#घोषणा		UDMA_TX_BUFX_EMPTY			0x00000001
#घोषणा UDMA_TX_BUF0_DATA_LEN	0x30
#घोषणा UDMA_TX_BUF0_DATA_SENT	0x34
#घोषणा UDMA_TX_BUF1_PTR_LO	0x38

#घोषणा UDMA_INTR_STATUS	0x00
#घोषणा		UDMA_INTR_ARB_TX_GRANT			0x00040000
#घोषणा		UDMA_INTR_ARB_RX_GRANT			0x00020000
#घोषणा		UDMA_INTR_TX_ALL_EMPTY			0x00010000
#घोषणा		UDMA_INTR_TX_EMPTY_BUF1			0x00008000
#घोषणा		UDMA_INTR_TX_EMPTY_BUF0			0x00004000
#घोषणा		UDMA_INTR_TX_ABORT			0x00002000
#घोषणा		UDMA_INTR_TX_DONE			0x00001000
#घोषणा		UDMA_INTR_RX_ERROR			0x00000800
#घोषणा		UDMA_INTR_RX_TIMEOUT			0x00000400
#घोषणा		UDMA_INTR_RX_READY_BUF7			0x00000200
#घोषणा		UDMA_INTR_RX_READY_BUF6			0x00000100
#घोषणा		UDMA_INTR_RX_READY_BUF5			0x00000080
#घोषणा		UDMA_INTR_RX_READY_BUF4			0x00000040
#घोषणा		UDMA_INTR_RX_READY_BUF3			0x00000020
#घोषणा		UDMA_INTR_RX_READY_BUF2			0x00000010
#घोषणा		UDMA_INTR_RX_READY_BUF1			0x00000008
#घोषणा		UDMA_INTR_RX_READY_BUF0			0x00000004
#घोषणा		UDMA_INTR_RX_READY_MASK			0x000003fc
#घोषणा		UDMA_INTR_RX_READY_SHIFT		2
#घोषणा		UDMA_INTR_RX_ABORT			0x00000002
#घोषणा		UDMA_INTR_RX_DONE			0x00000001
#घोषणा UDMA_INTR_SET		0x04
#घोषणा UDMA_INTR_CLEAR		0x08
#घोषणा UDMA_INTR_MASK_STATUS	0x0c
#घोषणा UDMA_INTR_MASK_SET	0x10
#घोषणा UDMA_INTR_MASK_CLEAR	0x14


#घोषणा UDMA_RX_INTERRUPTS ( \
	UDMA_INTR_RX_ERROR | \
	UDMA_INTR_RX_TIMEOUT | \
	UDMA_INTR_RX_READY_BUF0 | \
	UDMA_INTR_RX_READY_BUF1 | \
	UDMA_INTR_RX_READY_BUF2 | \
	UDMA_INTR_RX_READY_BUF3 | \
	UDMA_INTR_RX_READY_BUF4 | \
	UDMA_INTR_RX_READY_BUF5 | \
	UDMA_INTR_RX_READY_BUF6 | \
	UDMA_INTR_RX_READY_BUF7 | \
	UDMA_INTR_RX_ABORT | \
	UDMA_INTR_RX_DONE)

#घोषणा UDMA_RX_ERR_INTERRUPTS ( \
	UDMA_INTR_RX_ERROR | \
	UDMA_INTR_RX_TIMEOUT | \
	UDMA_INTR_RX_ABORT | \
	UDMA_INTR_RX_DONE)

#घोषणा UDMA_TX_INTERRUPTS ( \
	UDMA_INTR_TX_ABORT | \
	UDMA_INTR_TX_DONE)

#घोषणा UDMA_IS_RX_INTERRUPT(status) ((status) & UDMA_RX_INTERRUPTS)
#घोषणा UDMA_IS_TX_INTERRUPT(status) ((status) & UDMA_TX_INTERRUPTS)


/* Current devices have 8 sets of RX buffer रेजिस्टरs */
#घोषणा UDMA_RX_BUFS_COUNT	8
#घोषणा UDMA_RX_BUFS_REG_OFFSET (UDMA_RX_BUF1_PTR_LO - UDMA_RX_BUF0_PTR_LO)
#घोषणा UDMA_RX_BUFx_PTR_LO(x)	(UDMA_RX_BUF0_PTR_LO + \
				 ((x) * UDMA_RX_BUFS_REG_OFFSET))
#घोषणा UDMA_RX_BUFx_PTR_HI(x)	(UDMA_RX_BUF0_PTR_HI + \
				 ((x) * UDMA_RX_BUFS_REG_OFFSET))
#घोषणा UDMA_RX_BUFx_STATUS(x)	(UDMA_RX_BUF0_STATUS + \
				 ((x) * UDMA_RX_BUFS_REG_OFFSET))
#घोषणा UDMA_RX_BUFx_DATA_LEN(x) (UDMA_RX_BUF0_DATA_LEN + \
				  ((x) * UDMA_RX_BUFS_REG_OFFSET))

/* Current devices have 2 sets of TX buffer रेजिस्टरs */
#घोषणा UDMA_TX_BUFS_COUNT	2
#घोषणा UDMA_TX_BUFS_REG_OFFSET (UDMA_TX_BUF1_PTR_LO - UDMA_TX_BUF0_PTR_LO)
#घोषणा UDMA_TX_BUFx_PTR_LO(x)	(UDMA_TX_BUF0_PTR_LO + \
				 ((x) * UDMA_TX_BUFS_REG_OFFSET))
#घोषणा UDMA_TX_BUFx_PTR_HI(x)	(UDMA_TX_BUF0_PTR_HI + \
				 ((x) * UDMA_TX_BUFS_REG_OFFSET))
#घोषणा UDMA_TX_BUFx_STATUS(x)	(UDMA_TX_BUF0_STATUS + \
				 ((x) * UDMA_TX_BUFS_REG_OFFSET))
#घोषणा UDMA_TX_BUFx_DATA_LEN(x) (UDMA_TX_BUF0_DATA_LEN + \
				  ((x) * UDMA_TX_BUFS_REG_OFFSET))
#घोषणा UDMA_TX_BUFx_DATA_SENT(x) (UDMA_TX_BUF0_DATA_SENT + \
				   ((x) * UDMA_TX_BUFS_REG_OFFSET))
#घोषणा REGS_8250 0
#घोषणा REGS_DMA_RX 1
#घोषणा REGS_DMA_TX 2
#घोषणा REGS_DMA_ISR 3
#घोषणा REGS_DMA_ARB 4
#घोषणा REGS_MAX 5

#घोषणा TX_BUF_SIZE 4096
#घोषणा RX_BUF_SIZE 4096
#घोषणा RX_BUFS_COUNT 2
#घोषणा KHZ    1000
#घोषणा MHZ(x) ((x) * KHZ * KHZ)

अटल स्थिर u32 brcmstb_rate_table[] = अणु
	MHZ(81),
	MHZ(108),
	MHZ(64),		/* Actually 64285715 क्रम some chips */
	MHZ(48),
पूर्ण;

अटल स्थिर u32 brcmstb_rate_table_7278[] = अणु
	MHZ(81),
	MHZ(108),
	0,
	MHZ(48),
पूर्ण;

काष्ठा brcmuart_priv अणु
	पूर्णांक		line;
	काष्ठा clk	*baud_mux_clk;
	अचिन्हित दीर्घ	शेष_mux_rate;
	u32		real_rates[ARRAY_SIZE(brcmstb_rate_table)];
	स्थिर u32	*rate_table;
	kसमय_प्रकार		अक्षर_रुको;
	काष्ठा uart_port *up;
	काष्ठा hrसमयr	hrt;
	bool		shutकरोwn;
	bool		dma_enabled;
	काष्ठा uart_8250_dma dma;
	व्योम __iomem	*regs[REGS_MAX];
	dma_addr_t	rx_addr;
	व्योम		*rx_bufs;
	माप_प्रकार		rx_size;
	पूर्णांक		rx_next_buf;
	dma_addr_t	tx_addr;
	व्योम		*tx_buf;
	माप_प्रकार		tx_size;
	bool		tx_running;
	bool		rx_running;
	काष्ठा dentry	*debugfs_dir;

	/* stats exposed through debugfs */
	u64		dma_rx_partial_buf;
	u64		dma_rx_full_buf;
	u32		rx_bad_समयout_late_अक्षर;
	u32		rx_bad_समयout_no_अक्षर;
	u32		rx_missing_बंद_समयout;
	u32		rx_err;
	u32		rx_समयout;
	u32		rx_पात;
पूर्ण;

अटल काष्ठा dentry *brcmuart_debugfs_root;

/*
 * Register access routines
 */
अटल u32 udma_पढ़ोl(काष्ठा brcmuart_priv *priv,
		पूर्णांक reg_type, पूर्णांक offset)
अणु
	वापस पढ़ोl(priv->regs[reg_type] + offset);
पूर्ण

अटल व्योम udma_ग_लिखोl(काष्ठा brcmuart_priv *priv,
			पूर्णांक reg_type, पूर्णांक offset, u32 value)
अणु
	ग_लिखोl(value, priv->regs[reg_type] + offset);
पूर्ण

अटल व्योम udma_set(काष्ठा brcmuart_priv *priv,
		पूर्णांक reg_type, पूर्णांक offset, u32 bits)
अणु
	व्योम __iomem *reg = priv->regs[reg_type] + offset;
	u32 value;

	value = पढ़ोl(reg);
	value |= bits;
	ग_लिखोl(value, reg);
पूर्ण

अटल व्योम udma_unset(काष्ठा brcmuart_priv *priv,
		पूर्णांक reg_type, पूर्णांक offset, u32 bits)
अणु
	व्योम __iomem *reg = priv->regs[reg_type] + offset;
	u32 value;

	value = पढ़ोl(reg);
	value &= ~bits;
	ग_लिखोl(value, reg);
पूर्ण

/*
 * The UART DMA engine hardware can be used by multiple UARTS, but
 * only one at a समय. Sharing is not currently supported so
 * the first UART to request the DMA engine will get it and any
 * subsequent requests by other UARTS will fail.
 */
अटल पूर्णांक brcmuart_arbitration(काष्ठा brcmuart_priv *priv, bool acquire)
अणु
	u32 rx_grant;
	u32 tx_grant;
	पूर्णांक रुकोs;
	पूर्णांक ret = 0;

	अगर (acquire) अणु
		udma_set(priv, REGS_DMA_ARB, UDMA_ARB_RX, UDMA_ARB_REQ);
		udma_set(priv, REGS_DMA_ARB, UDMA_ARB_TX, UDMA_ARB_REQ);

		रुकोs = 1;
		जबतक (1) अणु
			rx_grant = udma_पढ़ोl(priv, REGS_DMA_ARB, UDMA_ARB_RX);
			tx_grant = udma_पढ़ोl(priv, REGS_DMA_ARB, UDMA_ARB_TX);
			अगर (rx_grant & tx_grant & UDMA_ARB_GRANT)
				वापस 0;
			अगर (रुकोs-- == 0)
				अवरोध;
			msleep(1);
		पूर्ण
		ret = 1;
	पूर्ण

	udma_unset(priv, REGS_DMA_ARB, UDMA_ARB_RX, UDMA_ARB_REQ);
	udma_unset(priv, REGS_DMA_ARB, UDMA_ARB_TX, UDMA_ARB_REQ);
	वापस ret;
पूर्ण

अटल व्योम brcmuart_init_dma_hardware(काष्ठा brcmuart_priv *priv)
अणु
	u32 daddr;
	u32 value;
	पूर्णांक x;

	/* Start with all पूर्णांकerrupts disabled */
	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_MASK_SET, 0xffffffff);

	udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_BUFFER_SIZE, RX_BUF_SIZE);

	/*
	 * Setup buffer बंद to happen when 32 अक्षरacter बार have
	 * elapsed since the last अक्षरacter was received.
	 */
	udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_BUFFER_CLOSE, 16*10*32);
	value = (RX_BUFS_COUNT << UDMA_RX_CTRL_NUM_BUF_USED_SHIFT)
		| UDMA_RX_CTRL_BUF_CLOSE_MODE
		| UDMA_RX_CTRL_BUF_CLOSE_ENA;
	udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_CTRL, value);

	udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_BLOCKOUT_COUNTER, 0);
	daddr = priv->rx_addr;
	क्रम (x = 0; x < RX_BUFS_COUNT; x++) अणु

		/* Set RX transfer length to 0 क्रम unknown */
		udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_TRANSFER_LEN, 0);

		udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_BUFx_PTR_LO(x),
			    lower_32_bits(daddr));
		udma_ग_लिखोl(priv, REGS_DMA_RX, UDMA_RX_BUFx_PTR_HI(x),
			    upper_32_bits(daddr));
		daddr += RX_BUF_SIZE;
	पूर्ण

	daddr = priv->tx_addr;
	udma_ग_लिखोl(priv, REGS_DMA_TX, UDMA_TX_BUFx_PTR_LO(0),
		    lower_32_bits(daddr));
	udma_ग_लिखोl(priv, REGS_DMA_TX, UDMA_TX_BUFx_PTR_HI(0),
		    upper_32_bits(daddr));
	udma_ग_लिखोl(priv, REGS_DMA_TX, UDMA_TX_CTRL,
		    UDMA_TX_CTRL_NUM_BUF_USED_1);

	/* clear all पूर्णांकerrupts then enable them */
	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_CLEAR, 0xffffffff);
	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_MASK_CLEAR,
		UDMA_RX_INTERRUPTS | UDMA_TX_INTERRUPTS);

पूर्ण

अटल व्योम start_rx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा brcmuart_priv *priv = p->port.निजी_data;
	पूर्णांक x;

	udma_unset(priv, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ENA);

	/* Clear the RX पढ़ोy bit क्रम all buffers */
	क्रम (x = 0; x < RX_BUFS_COUNT; x++)
		udma_unset(priv, REGS_DMA_RX, UDMA_RX_BUFx_STATUS(x),
			UDMA_RX_BUFX_STATUS_DATA_RDY);

	/* always start with buffer 0 */
	udma_unset(priv, REGS_DMA_RX, UDMA_RX_STATUS,
		   UDMA_RX_STATUS_ACTIVE_BUF_MASK);
	priv->rx_next_buf = 0;

	udma_set(priv, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ENA);
	priv->rx_running = true;
पूर्ण

अटल व्योम stop_rx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा brcmuart_priv *priv = p->port.निजी_data;

	/* If RX is running, set the RX ABORT */
	अगर (priv->rx_running)
		udma_set(priv, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ABORT);
पूर्ण

अटल पूर्णांक stop_tx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा brcmuart_priv *priv = p->port.निजी_data;
	u32 value;

	/* If TX is running, set the TX ABORT */
	value = udma_पढ़ोl(priv, REGS_DMA_TX, UDMA_TX_CTRL);
	अगर (value & UDMA_TX_CTRL_ENA)
		udma_set(priv, REGS_DMA_TX, UDMA_TX_CTRL, UDMA_TX_CTRL_ABORT);
	priv->tx_running = false;
	वापस 0;
पूर्ण

/*
 * NOTE: prपूर्णांकk's in this routine will hang the प्रणाली अगर this is
 * the console tty
 */
अटल पूर्णांक brcmuart_tx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा brcmuart_priv *priv = p->port.निजी_data;
	काष्ठा circ_buf *xmit = &p->port.state->xmit;
	u32 tx_size;

	अगर (uart_tx_stopped(&p->port) || priv->tx_running ||
		uart_circ_empty(xmit)) अणु
		वापस 0;
	पूर्ण
	tx_size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	priv->dma.tx_err = 0;
	स_नकल(priv->tx_buf, &xmit->buf[xmit->tail], tx_size);
	xmit->tail += tx_size;
	xmit->tail &= UART_XMIT_SIZE - 1;
	p->port.icount.tx += tx_size;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&p->port);

	udma_ग_लिखोl(priv, REGS_DMA_TX, UDMA_TX_TRANSFER_LEN, tx_size);
	udma_ग_लिखोl(priv, REGS_DMA_TX, UDMA_TX_BUF0_DATA_LEN, tx_size);
	udma_unset(priv, REGS_DMA_TX, UDMA_TX_BUF0_STATUS, UDMA_TX_BUFX_EMPTY);
	udma_set(priv, REGS_DMA_TX, UDMA_TX_CTRL, UDMA_TX_CTRL_ENA);
	priv->tx_running = true;

	वापस 0;
पूर्ण

अटल व्योम brcmuart_rx_buf_करोne_isr(काष्ठा uart_port *up, पूर्णांक index)
अणु
	काष्ठा brcmuart_priv *priv = up->निजी_data;
	काष्ठा tty_port *tty_port = &up->state->port;
	u32 status;
	u32 length;
	u32 copied;

	/* Make sure we're still in sync with the hardware */
	status = udma_पढ़ोl(priv, REGS_DMA_RX, UDMA_RX_BUFx_STATUS(index));
	length = udma_पढ़ोl(priv, REGS_DMA_RX, UDMA_RX_BUFx_DATA_LEN(index));

	अगर ((status & UDMA_RX_BUFX_STATUS_DATA_RDY) == 0) अणु
		dev_err(up->dev, "RX done interrupt but DATA_RDY not found\n");
		वापस;
	पूर्ण
	अगर (status & (UDMA_RX_BUFX_STATUS_OVERRUN_ERR |
		      UDMA_RX_BUFX_STATUS_FRAME_ERR |
		      UDMA_RX_BUFX_STATUS_PARITY_ERR)) अणु
		अगर (status & UDMA_RX_BUFX_STATUS_OVERRUN_ERR) अणु
			up->icount.overrun++;
			dev_warn(up->dev, "RX OVERRUN Error\n");
		पूर्ण
		अगर (status & UDMA_RX_BUFX_STATUS_FRAME_ERR) अणु
			up->icount.frame++;
			dev_warn(up->dev, "RX FRAMING Error\n");
		पूर्ण
		अगर (status & UDMA_RX_BUFX_STATUS_PARITY_ERR) अणु
			up->icount.parity++;
			dev_warn(up->dev, "RX PARITY Error\n");
		पूर्ण
	पूर्ण
	copied = (u32)tty_insert_flip_string(
		tty_port,
		priv->rx_bufs + (index * RX_BUF_SIZE),
		length);
	अगर (copied != length) अणु
		dev_warn(up->dev, "Flip buffer overrun of %d bytes\n",
			 length - copied);
		up->icount.overrun += length - copied;
	पूर्ण
	up->icount.rx += length;
	अगर (status & UDMA_RX_BUFX_STATUS_CLOSE_EXPIRED)
		priv->dma_rx_partial_buf++;
	अन्यथा अगर (length != RX_BUF_SIZE)
		/*
		 * This is a bug in the controller that करोesn't cause
		 * any problems but will be fixed in the future.
		 */
		priv->rx_missing_बंद_समयout++;
	अन्यथा
		priv->dma_rx_full_buf++;

	tty_flip_buffer_push(tty_port);
पूर्ण

अटल व्योम brcmuart_rx_isr(काष्ठा uart_port *up, u32 rx_isr)
अणु
	काष्ठा brcmuart_priv *priv = up->निजी_data;
	काष्ठा device *dev = up->dev;
	u32 rx_करोne_isr;
	u32 check_isr;

	rx_करोne_isr = (rx_isr & UDMA_INTR_RX_READY_MASK);
	जबतक (rx_करोne_isr) अणु
		check_isr = UDMA_INTR_RX_READY_BUF0 << priv->rx_next_buf;
		अगर (check_isr & rx_करोne_isr) अणु
			brcmuart_rx_buf_करोne_isr(up, priv->rx_next_buf);
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"RX buffer ready out of sequence, restarting RX DMA\n");
			start_rx_dma(up_to_u8250p(up));
			अवरोध;
		पूर्ण
		अगर (rx_isr & UDMA_RX_ERR_INTERRUPTS) अणु
			अगर (rx_isr & UDMA_INTR_RX_ERROR)
				priv->rx_err++;
			अगर (rx_isr & UDMA_INTR_RX_TIMEOUT) अणु
				priv->rx_समयout++;
				dev_err(dev, "RX TIMEOUT Error\n");
			पूर्ण
			अगर (rx_isr & UDMA_INTR_RX_ABORT)
				priv->rx_पात++;
			priv->rx_running = false;
		पूर्ण
		/* If not ABORT, re-enable RX buffer */
		अगर (!(rx_isr & UDMA_INTR_RX_ABORT))
			udma_unset(priv, REGS_DMA_RX,
				   UDMA_RX_BUFx_STATUS(priv->rx_next_buf),
				   UDMA_RX_BUFX_STATUS_DATA_RDY);
		rx_करोne_isr &= ~check_isr;
		priv->rx_next_buf++;
		अगर (priv->rx_next_buf == RX_BUFS_COUNT)
			priv->rx_next_buf = 0;
	पूर्ण
पूर्ण

अटल व्योम brcmuart_tx_isr(काष्ठा uart_port *up, u32 isr)
अणु
	काष्ठा brcmuart_priv *priv = up->निजी_data;
	काष्ठा device *dev = up->dev;
	काष्ठा uart_8250_port *port_8250 = up_to_u8250p(up);
	काष्ठा circ_buf	*xmit = &port_8250->port.state->xmit;

	अगर (isr & UDMA_INTR_TX_ABORT) अणु
		अगर (priv->tx_running)
			dev_err(dev, "Unexpected TX_ABORT interrupt\n");
		वापस;
	पूर्ण
	priv->tx_running = false;
	अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(up))
		brcmuart_tx_dma(port_8250);
पूर्ण

अटल irqवापस_t brcmuart_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *up = dev_id;
	काष्ठा device *dev = up->dev;
	काष्ठा brcmuart_priv *priv = up->निजी_data;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांकerrupts;
	u32 rval;
	u32 tval;

	पूर्णांकerrupts = udma_पढ़ोl(priv, REGS_DMA_ISR, UDMA_INTR_STATUS);
	अगर (पूर्णांकerrupts == 0)
		वापस IRQ_NONE;

	spin_lock_irqsave(&up->lock, flags);

	/* Clear all पूर्णांकerrupts */
	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_CLEAR, पूर्णांकerrupts);

	rval = UDMA_IS_RX_INTERRUPT(पूर्णांकerrupts);
	अगर (rval)
		brcmuart_rx_isr(up, rval);
	tval = UDMA_IS_TX_INTERRUPT(पूर्णांकerrupts);
	अगर (tval)
		brcmuart_tx_isr(up, tval);
	अगर ((rval | tval) == 0)
		dev_warn(dev, "Spurious interrupt: 0x%x\n", पूर्णांकerrupts);

	spin_unlock_irqrestore(&up->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक brcmuart_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक res;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा brcmuart_priv *priv = up->port.निजी_data;

	priv->shutकरोwn = false;

	/*
	 * prevent serial8250_करो_startup() from allocating non-existent
	 * DMA resources
	 */
	up->dma = शून्य;

	res = serial8250_करो_startup(port);
	अगर (!priv->dma_enabled)
		वापस res;
	/*
	 * Disable the Receive Data Interrupt because the DMA engine
	 * will handle this.
	 */
	up->ier &= ~UART_IER_RDI;
	serial_port_out(port, UART_IER, up->ier);

	priv->tx_running = false;
	priv->dma.rx_dma = शून्य;
	priv->dma.tx_dma = brcmuart_tx_dma;
	up->dma = &priv->dma;

	brcmuart_init_dma_hardware(priv);
	start_rx_dma(up);
	वापस res;
पूर्ण

अटल व्योम brcmuart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा brcmuart_priv *priv = up->port.निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	priv->shutकरोwn = true;
	अगर (priv->dma_enabled) अणु
		stop_rx_dma(up);
		stop_tx_dma(up);
		/* disable all पूर्णांकerrupts */
		udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_MASK_SET,
			UDMA_RX_INTERRUPTS | UDMA_TX_INTERRUPTS);
	पूर्ण

	/*
	 * prevent serial8250_करो_shutकरोwn() from trying to मुक्त
	 * DMA resources that we never alloc'd क्रम this driver.
	 */
	up->dma = शून्य;

	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_करो_shutकरोwn(port);
पूर्ण

/*
 * Not all घड़ीs run at the exact specअगरied rate, so set each requested
 * rate and then get the actual rate.
 */
अटल व्योम init_real_clk_rates(काष्ठा device *dev, काष्ठा brcmuart_priv *priv)
अणु
	पूर्णांक x;
	पूर्णांक rc;

	priv->शेष_mux_rate = clk_get_rate(priv->baud_mux_clk);
	क्रम (x = 0; x < ARRAY_SIZE(priv->real_rates); x++) अणु
		अगर (priv->rate_table[x] == 0) अणु
			priv->real_rates[x] = 0;
			जारी;
		पूर्ण
		rc = clk_set_rate(priv->baud_mux_clk, priv->rate_table[x]);
		अगर (rc) अणु
			dev_err(dev, "Error selecting BAUD MUX clock for %u\n",
				priv->rate_table[x]);
			priv->real_rates[x] = priv->rate_table[x];
		पूर्ण अन्यथा अणु
			priv->real_rates[x] = clk_get_rate(priv->baud_mux_clk);
		पूर्ण
	पूर्ण
	clk_set_rate(priv->baud_mux_clk, priv->शेष_mux_rate);
पूर्ण

अटल व्योम set_घड़ी_mux(काष्ठा uart_port *up, काष्ठा brcmuart_priv *priv,
			u32 baud)
अणु
	u32 percent;
	u32 best_percent = अच_पूर्णांक_उच्च;
	u32 quot;
	u32 best_quot = 1;
	u32 rate;
	पूर्णांक best_index = -1;
	u64 hires_rate;
	u64 hires_baud;
	u64 hires_err;
	पूर्णांक rc;
	पूर्णांक i;
	पूर्णांक real_baud;

	/* If the Baud Mux Clock was not specअगरied, just वापस */
	अगर (priv->baud_mux_clk == शून्य)
		वापस;

	/* Find the बंदst match क्रम specअगरied baud */
	क्रम (i = 0; i < ARRAY_SIZE(priv->real_rates); i++) अणु
		अगर (priv->real_rates[i] == 0)
			जारी;
		rate = priv->real_rates[i] / 16;
		quot = DIV_ROUND_CLOSEST(rate, baud);
		अगर (!quot)
			जारी;

		/* increase resolution to get xx.xx percent */
		hires_rate = (u64)rate * 10000;
		hires_baud = (u64)baud * 10000;

		hires_err = भाग_u64(hires_rate, (u64)quot);

		/* get the delta */
		अगर (hires_err > hires_baud)
			hires_err = (hires_err - hires_baud);
		अन्यथा
			hires_err = (hires_baud - hires_err);

		percent = (अचिन्हित दीर्घ)DIV_ROUND_CLOSEST_ULL(hires_err, baud);
		dev_dbg(up->dev,
			"Baud rate: %u, MUX Clk: %u, Error: %u.%u%%\n",
			baud, priv->real_rates[i], percent / 100,
			percent % 100);
		अगर (percent < best_percent) अणु
			best_percent = percent;
			best_index = i;
			best_quot = quot;
		पूर्ण
	पूर्ण
	अगर (best_index == -1) अणु
		dev_err(up->dev, "Error, %d BAUD rate is too fast.\n", baud);
		वापस;
	पूर्ण
	rate = priv->real_rates[best_index];
	rc = clk_set_rate(priv->baud_mux_clk, rate);
	अगर (rc)
		dev_err(up->dev, "Error selecting BAUD MUX clock\n");

	/* Error over 3 percent will cause data errors */
	अगर (best_percent > 300)
		dev_err(up->dev, "Error, baud: %d has %u.%u%% error\n",
			baud, percent / 100, percent % 100);

	real_baud = rate / 16 / best_quot;
	dev_dbg(up->dev, "Selecting BAUD MUX rate: %u\n", rate);
	dev_dbg(up->dev, "Requested baud: %u, Actual baud: %u\n",
		baud, real_baud);

	/* calc nanoseconds क्रम 1.5 अक्षरacters समय at the given baud rate */
	i = NSEC_PER_SEC / real_baud / 10;
	i += (i / 2);
	priv->अक्षर_रुको = ns_to_kसमय(i);

	up->uartclk = rate;
पूर्ण

अटल व्योम brcmstb_set_termios(काष्ठा uart_port *up,
				काष्ठा ktermios *termios,
				काष्ठा ktermios *old)
अणु
	काष्ठा uart_8250_port *p8250 = up_to_u8250p(up);
	काष्ठा brcmuart_priv *priv = up->निजी_data;

	अगर (priv->dma_enabled)
		stop_rx_dma(p8250);
	set_घड़ी_mux(up, priv, tty_termios_baud_rate(termios));
	serial8250_करो_set_termios(up, termios, old);
	अगर (p8250->mcr & UART_MCR_AFE)
		p8250->port.status |= UPSTAT_AUTOCTS;
	अगर (priv->dma_enabled)
		start_rx_dma(p8250);
पूर्ण

अटल पूर्णांक brcmuart_handle_irq(काष्ठा uart_port *p)
अणु
	अचिन्हित पूर्णांक iir = serial_port_in(p, UART_IIR);
	काष्ठा brcmuart_priv *priv = p->निजी_data;
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	अचिन्हित पूर्णांक mcr;
	पूर्णांक handled = 0;

	/*
	 * There's a bug in some 8250 cores where we get a समयout
	 * पूर्णांकerrupt but there is no data पढ़ोy.
	 */
	अगर (((iir & UART_IIR_ID) == UART_IIR_RX_TIMEOUT) && !(priv->shutकरोwn)) अणु
		spin_lock_irqsave(&p->lock, flags);
		status = serial_port_in(p, UART_LSR);
		अगर ((status & UART_LSR_DR) == 0) अणु

			ier = serial_port_in(p, UART_IER);
			/*
			 * अगर Receive Data Interrupt is enabled and
			 * we're uing hardware flow control, deनिश्चित
			 * RTS and रुको क्रम any अक्षरs in the pipline to
			 * arrive and then check क्रम DR again.
			 */
			अगर ((ier & UART_IER_RDI) && (up->mcr & UART_MCR_AFE)) अणु
				ier &= ~(UART_IER_RLSI | UART_IER_RDI);
				serial_port_out(p, UART_IER, ier);
				mcr = serial_port_in(p, UART_MCR);
				mcr &= ~UART_MCR_RTS;
				serial_port_out(p, UART_MCR, mcr);
				hrसमयr_start(&priv->hrt, priv->अक्षर_रुको,
					      HRTIMER_MODE_REL);
			पूर्ण अन्यथा अणु
				serial_port_in(p, UART_RX);
			पूर्ण

			handled = 1;
		पूर्ण
		spin_unlock_irqrestore(&p->lock, flags);
		अगर (handled)
			वापस 1;
	पूर्ण
	वापस serial8250_handle_irq(p, iir);
पूर्ण

अटल क्रमागत hrसमयr_restart brcmuart_hrसमयr_func(काष्ठा hrसमयr *t)
अणु
	काष्ठा brcmuart_priv *priv = container_of(t, काष्ठा brcmuart_priv, hrt);
	काष्ठा uart_port *p = priv->up;
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;

	अगर (priv->shutकरोwn)
		वापस HRTIMER_NORESTART;

	spin_lock_irqsave(&p->lock, flags);
	status = serial_port_in(p, UART_LSR);

	/*
	 * If a अक्षरacter did not arrive after the समयout, clear the false
	 * receive समयout.
	 */
	अगर ((status & UART_LSR_DR) == 0) अणु
		serial_port_in(p, UART_RX);
		priv->rx_bad_समयout_no_अक्षर++;
	पूर्ण अन्यथा अणु
		priv->rx_bad_समयout_late_अक्षर++;
	पूर्ण

	/* re-enable receive unless upper layer has disabled it */
	अगर ((up->ier & (UART_IER_RLSI | UART_IER_RDI)) ==
	    (UART_IER_RLSI | UART_IER_RDI)) अणु
		status = serial_port_in(p, UART_IER);
		status |= (UART_IER_RLSI | UART_IER_RDI);
		serial_port_out(p, UART_IER, status);
		status = serial_port_in(p, UART_MCR);
		status |= UART_MCR_RTS;
		serial_port_out(p, UART_MCR, status);
	पूर्ण
	spin_unlock_irqrestore(&p->lock, flags);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल स्थिर काष्ठा of_device_id brcmuart_dt_ids[] = अणु
	अणु
		.compatible = "brcm,bcm7278-uart",
		.data = brcmstb_rate_table_7278,
	पूर्ण,
	अणु
		.compatible = "brcm,bcm7271-uart",
		.data = brcmstb_rate_table,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, brcmuart_dt_ids);

अटल व्योम brcmuart_मुक्त_bufs(काष्ठा device *dev, काष्ठा brcmuart_priv *priv)
अणु
	अगर (priv->rx_bufs)
		dma_मुक्त_coherent(dev, priv->rx_size, priv->rx_bufs,
				  priv->rx_addr);
	अगर (priv->tx_buf)
		dma_मुक्त_coherent(dev, priv->tx_size, priv->tx_buf,
				  priv->tx_addr);
पूर्ण

अटल व्योम brcmuart_throttle(काष्ठा uart_port *port)
अणु
	काष्ठा brcmuart_priv *priv = port->निजी_data;

	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_MASK_SET, UDMA_RX_INTERRUPTS);
पूर्ण

अटल व्योम brcmuart_unthrottle(काष्ठा uart_port *port)
अणु
	काष्ठा brcmuart_priv *priv = port->निजी_data;

	udma_ग_लिखोl(priv, REGS_DMA_ISR, UDMA_INTR_MASK_CLEAR,
		    UDMA_RX_INTERRUPTS);
पूर्ण

अटल पूर्णांक debugfs_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा brcmuart_priv *priv = s->निजी;

	seq_म_लिखो(s, "rx_err:\t\t\t\t%u\n",
		   priv->rx_err);
	seq_म_लिखो(s, "rx_timeout:\t\t\t%u\n",
		   priv->rx_समयout);
	seq_म_लिखो(s, "rx_abort:\t\t\t%u\n",
		   priv->rx_पात);
	seq_म_लिखो(s, "rx_bad_timeout_late_char:\t%u\n",
		   priv->rx_bad_समयout_late_अक्षर);
	seq_म_लिखो(s, "rx_bad_timeout_no_char:\t\t%u\n",
		   priv->rx_bad_समयout_no_अक्षर);
	seq_म_लिखो(s, "rx_missing_close_timeout:\t%u\n",
		   priv->rx_missing_बंद_समयout);
	अगर (priv->dma_enabled) अणु
		seq_म_लिखो(s, "dma_rx_partial_buf:\t\t%llu\n",
			   priv->dma_rx_partial_buf);
		seq_म_लिखो(s, "dma_rx_full_buf:\t\t%llu\n",
			   priv->dma_rx_full_buf);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_stats);

अटल व्योम brcmuart_init_debugfs(काष्ठा brcmuart_priv *priv,
				  स्थिर अक्षर *device)
अणु
	priv->debugfs_dir = debugfs_create_dir(device, brcmuart_debugfs_root);
	debugfs_create_file("stats", 0444, priv->debugfs_dir, priv,
			    &debugfs_stats_fops);
पूर्ण


अटल पूर्णांक brcmuart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *regs;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	काष्ठा uart_8250_port *new_port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcmuart_priv *priv;
	काष्ठा clk *baud_mux_clk;
	काष्ठा uart_8250_port up;
	काष्ठा resource *irq;
	व्योम __iomem *membase = 0;
	resource_माप_प्रकार mapbase = 0;
	u32 clk_rate = 0;
	पूर्णांक ret;
	पूर्णांक x;
	पूर्णांक dma_irq;
	अटल स्थिर अक्षर * स्थिर reg_names[REGS_MAX] = अणु
		"uart", "dma_rx", "dma_tx", "dma_intr2", "dma_arb"
	पूर्ण;

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(dev, "missing irq\n");
		वापस -EINVAL;
	पूर्ण
	priv = devm_kzalloc(dev, माप(काष्ठा brcmuart_priv),
			GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	of_id = of_match_node(brcmuart_dt_ids, np);
	अगर (!of_id || !of_id->data)
		priv->rate_table = brcmstb_rate_table;
	अन्यथा
		priv->rate_table = of_id->data;

	क्रम (x = 0; x < REGS_MAX; x++) अणु
		regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						reg_names[x]);
		अगर (!regs)
			अवरोध;
		priv->regs[x] =	devm_ioremap(dev, regs->start,
					     resource_size(regs));
		अगर (!priv->regs[x])
			वापस -ENOMEM;
		अगर (x == REGS_8250) अणु
			mapbase = regs->start;
			membase = priv->regs[x];
		पूर्ण
	पूर्ण

	/* We should have just the uart base रेजिस्टरs or all the रेजिस्टरs */
	अगर (x != 1 && x != REGS_MAX) अणु
		dev_warn(dev, "%s registers not specified\n", reg_names[x]);
		वापस -EINVAL;
	पूर्ण

	/* अगर the DMA रेजिस्टरs were specअगरied, try to enable DMA */
	अगर (x > REGS_DMA_RX) अणु
		अगर (brcmuart_arbitration(priv, 1) == 0) अणु
			u32 txrev = 0;
			u32 rxrev = 0;

			txrev = udma_पढ़ोl(priv, REGS_DMA_RX, UDMA_RX_REVISION);
			rxrev = udma_पढ़ोl(priv, REGS_DMA_TX, UDMA_TX_REVISION);
			अगर ((txrev >= UDMA_TX_REVISION_REQUIRED) &&
				(rxrev >= UDMA_RX_REVISION_REQUIRED)) अणु

				/* Enable the use of the DMA hardware */
				priv->dma_enabled = true;
			पूर्ण अन्यथा अणु
				brcmuart_arbitration(priv, 0);
				dev_err(dev,
					"Unsupported DMA Hardware Revision\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"Timeout arbitrating for UART DMA hardware\n");
		पूर्ण
	पूर्ण

	of_property_पढ़ो_u32(np, "clock-frequency", &clk_rate);

	/* See अगर a Baud घड़ी has been specअगरied */
	baud_mux_clk = of_clk_get_by_name(np, "sw_baud");
	अगर (IS_ERR(baud_mux_clk)) अणु
		अगर (PTR_ERR(baud_mux_clk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(dev, "BAUD MUX clock not specified\n");
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "BAUD MUX clock found\n");
		ret = clk_prepare_enable(baud_mux_clk);
		अगर (ret)
			वापस ret;
		priv->baud_mux_clk = baud_mux_clk;
		init_real_clk_rates(dev, priv);
		clk_rate = priv->शेष_mux_rate;
	पूर्ण

	अगर (clk_rate == 0) अणु
		dev_err(dev, "clock-frequency or clk not defined\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "DMA is %senabled\n", priv->dma_enabled ? "" : "not ");

	स_रखो(&up, 0, माप(up));
	up.port.type = PORT_16550A;
	up.port.uartclk = clk_rate;
	up.port.dev = dev;
	up.port.mapbase = mapbase;
	up.port.membase = membase;
	up.port.irq = irq->start;
	up.port.handle_irq = brcmuart_handle_irq;
	up.port.regshअगरt = 2;
	up.port.iotype = of_device_is_big_endian(np) ?
		UPIO_MEM32BE : UPIO_MEM32;
	up.port.flags = UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF
		| UPF_FIXED_PORT | UPF_FIXED_TYPE;
	up.port.dev = dev;
	up.port.निजी_data = priv;
	up.capabilities = UART_CAP_FIFO | UART_CAP_AFE;
	up.port.fअगरosize = 32;

	/* Check क्रम a fixed line number */
	ret = of_alias_get_id(np, "serial");
	अगर (ret >= 0)
		up.port.line = ret;

	/* setup HR समयr */
	hrसमयr_init(&priv->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	priv->hrt.function = brcmuart_hrसमयr_func;

	up.port.shutकरोwn = brcmuart_shutकरोwn;
	up.port.startup = brcmuart_startup;
	up.port.throttle = brcmuart_throttle;
	up.port.unthrottle = brcmuart_unthrottle;
	up.port.set_termios = brcmstb_set_termios;

	अगर (priv->dma_enabled) अणु
		priv->rx_size = RX_BUF_SIZE * RX_BUFS_COUNT;
		priv->rx_bufs = dma_alloc_coherent(dev,
						   priv->rx_size,
						   &priv->rx_addr, GFP_KERNEL);
		अगर (!priv->rx_bufs)
			जाओ err;
		priv->tx_size = UART_XMIT_SIZE;
		priv->tx_buf = dma_alloc_coherent(dev,
						  priv->tx_size,
						  &priv->tx_addr, GFP_KERNEL);
		अगर (!priv->tx_buf)
			जाओ err;
	पूर्ण

	ret = serial8250_रेजिस्टर_8250_port(&up);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register 8250 port\n");
		जाओ err;
	पूर्ण
	priv->line = ret;
	new_port = serial8250_get_port(ret);
	priv->up = &new_port->port;
	अगर (priv->dma_enabled) अणु
		dma_irq = platक्रमm_get_irq_byname(pdev,  "dma");
		अगर (dma_irq < 0) अणु
			dev_err(dev, "no IRQ resource info\n");
			जाओ err1;
		पूर्ण
		ret = devm_request_irq(dev, dma_irq, brcmuart_isr,
				IRQF_SHARED, "uart DMA irq", &new_port->port);
		अगर (ret) अणु
			dev_err(dev, "unable to register IRQ handler\n");
			जाओ err1;
		पूर्ण
	पूर्ण
	platक्रमm_set_drvdata(pdev, priv);
	brcmuart_init_debugfs(priv, dev_name(&pdev->dev));
	वापस 0;

err1:
	serial8250_unरेजिस्टर_port(priv->line);
err:
	brcmuart_मुक्त_bufs(dev, priv);
	brcmuart_arbitration(priv, 0);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक brcmuart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmuart_priv *priv = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(priv->debugfs_dir);
	hrसमयr_cancel(&priv->hrt);
	serial8250_unरेजिस्टर_port(priv->line);
	brcmuart_मुक्त_bufs(&pdev->dev, priv);
	brcmuart_arbitration(priv, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused brcmuart_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmuart_priv *priv = dev_get_drvdata(dev);

	serial8250_suspend_port(priv->line);
	clk_disable_unprepare(priv->baud_mux_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused brcmuart_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmuart_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->baud_mux_clk);
	अगर (ret)
		dev_err(dev, "Error enabling BAUD MUX clock\n");

	/*
	 * The hardware goes back to it's शेष after suspend
	 * so get the "clk" back in sync.
	 */
	ret = clk_set_rate(priv->baud_mux_clk, priv->शेष_mux_rate);
	अगर (ret)
		dev_err(dev, "Error restoring default BAUD MUX clock\n");
	अगर (priv->dma_enabled) अणु
		अगर (brcmuart_arbitration(priv, 1)) अणु
			dev_err(dev, "Timeout arbitrating for DMA hardware on resume\n");
			वापस(-EBUSY);
		पूर्ण
		brcmuart_init_dma_hardware(priv);
		start_rx_dma(serial8250_get_port(priv->line));
	पूर्ण
	serial8250_resume_port(priv->line);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops brcmuart_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(brcmuart_suspend, brcmuart_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver brcmuart_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "bcm7271-uart",
		.pm		= &brcmuart_dev_pm_ops,
		.of_match_table = brcmuart_dt_ids,
	पूर्ण,
	.probe		= brcmuart_probe,
	.हटाओ		= brcmuart_हटाओ,
पूर्ण;

अटल पूर्णांक __init brcmuart_init(व्योम)
अणु
	brcmuart_debugfs_root = debugfs_create_dir(
		brcmuart_platक्रमm_driver.driver.name, शून्य);
	वापस platक्रमm_driver_रेजिस्टर(&brcmuart_platक्रमm_driver);
पूर्ण
module_init(brcmuart_init);

अटल व्योम __निकास brcmuart_deinit(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&brcmuart_platक्रमm_driver);
	debugfs_हटाओ_recursive(brcmuart_debugfs_root);
पूर्ण
module_निकास(brcmuart_deinit);

MODULE_AUTHOR("Al Cooper");
MODULE_DESCRIPTION("Broadcom NS16550A compatible serial port driver");
MODULE_LICENSE("GPL v2");
