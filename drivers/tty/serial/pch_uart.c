<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>
#समावेश <linux/nmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pch_dma.h>

क्रमागत अणु
	PCH_UART_HANDLED_RX_INT_SHIFT,
	PCH_UART_HANDLED_TX_INT_SHIFT,
	PCH_UART_HANDLED_RX_ERR_INT_SHIFT,
	PCH_UART_HANDLED_RX_TRG_INT_SHIFT,
	PCH_UART_HANDLED_MS_INT_SHIFT,
	PCH_UART_HANDLED_LS_INT_SHIFT,
पूर्ण;

#घोषणा PCH_UART_DRIVER_DEVICE "ttyPCH"

/* Set the max number of UART port
 * Intel EG20T PCH: 4 port
 * LAPIS Semiconductor ML7213 IOH: 3 port
 * LAPIS Semiconductor ML7223 IOH: 2 port
*/
#घोषणा PCH_UART_NR	4

#घोषणा PCH_UART_HANDLED_RX_INT	(1<<((PCH_UART_HANDLED_RX_INT_SHIFT)<<1))
#घोषणा PCH_UART_HANDLED_TX_INT	(1<<((PCH_UART_HANDLED_TX_INT_SHIFT)<<1))
#घोषणा PCH_UART_HANDLED_RX_ERR_INT	(1<<((\
					PCH_UART_HANDLED_RX_ERR_INT_SHIFT)<<1))
#घोषणा PCH_UART_HANDLED_RX_TRG_INT	(1<<((\
					PCH_UART_HANDLED_RX_TRG_INT_SHIFT)<<1))
#घोषणा PCH_UART_HANDLED_MS_INT	(1<<((PCH_UART_HANDLED_MS_INT_SHIFT)<<1))

#घोषणा PCH_UART_HANDLED_LS_INT	(1<<((PCH_UART_HANDLED_LS_INT_SHIFT)<<1))

#घोषणा PCH_UART_RBR		0x00
#घोषणा PCH_UART_THR		0x00

#घोषणा PCH_UART_IER_MASK	(PCH_UART_IER_ERBFI|PCH_UART_IER_ETBEI|\
				PCH_UART_IER_ELSI|PCH_UART_IER_EDSSI)
#घोषणा PCH_UART_IER_ERBFI	0x00000001
#घोषणा PCH_UART_IER_ETBEI	0x00000002
#घोषणा PCH_UART_IER_ELSI	0x00000004
#घोषणा PCH_UART_IER_EDSSI	0x00000008

#घोषणा PCH_UART_IIR_IP			0x00000001
#घोषणा PCH_UART_IIR_IID		0x00000006
#घोषणा PCH_UART_IIR_MSI		0x00000000
#घोषणा PCH_UART_IIR_TRI		0x00000002
#घोषणा PCH_UART_IIR_RRI		0x00000004
#घोषणा PCH_UART_IIR_REI		0x00000006
#घोषणा PCH_UART_IIR_TOI		0x00000008
#घोषणा PCH_UART_IIR_FIFO256		0x00000020
#घोषणा PCH_UART_IIR_FIFO64		PCH_UART_IIR_FIFO256
#घोषणा PCH_UART_IIR_FE			0x000000C0

#घोषणा PCH_UART_FCR_FIFOE		0x00000001
#घोषणा PCH_UART_FCR_RFR		0x00000002
#घोषणा PCH_UART_FCR_TFR		0x00000004
#घोषणा PCH_UART_FCR_DMS		0x00000008
#घोषणा PCH_UART_FCR_FIFO256		0x00000020
#घोषणा PCH_UART_FCR_RFTL		0x000000C0

#घोषणा PCH_UART_FCR_RFTL1		0x00000000
#घोषणा PCH_UART_FCR_RFTL64		0x00000040
#घोषणा PCH_UART_FCR_RFTL128		0x00000080
#घोषणा PCH_UART_FCR_RFTL224		0x000000C0
#घोषणा PCH_UART_FCR_RFTL16		PCH_UART_FCR_RFTL64
#घोषणा PCH_UART_FCR_RFTL32		PCH_UART_FCR_RFTL128
#घोषणा PCH_UART_FCR_RFTL56		PCH_UART_FCR_RFTL224
#घोषणा PCH_UART_FCR_RFTL4		PCH_UART_FCR_RFTL64
#घोषणा PCH_UART_FCR_RFTL8		PCH_UART_FCR_RFTL128
#घोषणा PCH_UART_FCR_RFTL14		PCH_UART_FCR_RFTL224
#घोषणा PCH_UART_FCR_RFTL_SHIFT		6

#घोषणा PCH_UART_LCR_WLS	0x00000003
#घोषणा PCH_UART_LCR_STB	0x00000004
#घोषणा PCH_UART_LCR_PEN	0x00000008
#घोषणा PCH_UART_LCR_EPS	0x00000010
#घोषणा PCH_UART_LCR_SP		0x00000020
#घोषणा PCH_UART_LCR_SB		0x00000040
#घोषणा PCH_UART_LCR_DLAB	0x00000080
#घोषणा PCH_UART_LCR_NP		0x00000000
#घोषणा PCH_UART_LCR_OP		PCH_UART_LCR_PEN
#घोषणा PCH_UART_LCR_EP		(PCH_UART_LCR_PEN | PCH_UART_LCR_EPS)
#घोषणा PCH_UART_LCR_1P		(PCH_UART_LCR_PEN | PCH_UART_LCR_SP)
#घोषणा PCH_UART_LCR_0P		(PCH_UART_LCR_PEN | PCH_UART_LCR_EPS |\
				PCH_UART_LCR_SP)

#घोषणा PCH_UART_LCR_5BIT	0x00000000
#घोषणा PCH_UART_LCR_6BIT	0x00000001
#घोषणा PCH_UART_LCR_7BIT	0x00000002
#घोषणा PCH_UART_LCR_8BIT	0x00000003

#घोषणा PCH_UART_MCR_DTR	0x00000001
#घोषणा PCH_UART_MCR_RTS	0x00000002
#घोषणा PCH_UART_MCR_OUT	0x0000000C
#घोषणा PCH_UART_MCR_LOOP	0x00000010
#घोषणा PCH_UART_MCR_AFE	0x00000020

#घोषणा PCH_UART_LSR_DR		0x00000001
#घोषणा PCH_UART_LSR_ERR	(1<<7)

#घोषणा PCH_UART_MSR_DCTS	0x00000001
#घोषणा PCH_UART_MSR_DDSR	0x00000002
#घोषणा PCH_UART_MSR_TERI	0x00000004
#घोषणा PCH_UART_MSR_DDCD	0x00000008
#घोषणा PCH_UART_MSR_CTS	0x00000010
#घोषणा PCH_UART_MSR_DSR	0x00000020
#घोषणा PCH_UART_MSR_RI		0x00000040
#घोषणा PCH_UART_MSR_DCD	0x00000080
#घोषणा PCH_UART_MSR_DELTA	(PCH_UART_MSR_DCTS | PCH_UART_MSR_DDSR |\
				PCH_UART_MSR_TERI | PCH_UART_MSR_DDCD)

#घोषणा PCH_UART_DLL		0x00
#घोषणा PCH_UART_DLM		0x01

#घोषणा PCH_UART_BRCSR		0x0E

#घोषणा PCH_UART_IID_RLS	(PCH_UART_IIR_REI)
#घोषणा PCH_UART_IID_RDR	(PCH_UART_IIR_RRI)
#घोषणा PCH_UART_IID_RDR_TO	(PCH_UART_IIR_RRI | PCH_UART_IIR_TOI)
#घोषणा PCH_UART_IID_THRE	(PCH_UART_IIR_TRI)
#घोषणा PCH_UART_IID_MS		(PCH_UART_IIR_MSI)

#घोषणा PCH_UART_HAL_PARITY_NONE	(PCH_UART_LCR_NP)
#घोषणा PCH_UART_HAL_PARITY_ODD		(PCH_UART_LCR_OP)
#घोषणा PCH_UART_HAL_PARITY_EVEN	(PCH_UART_LCR_EP)
#घोषणा PCH_UART_HAL_PARITY_FIX1	(PCH_UART_LCR_1P)
#घोषणा PCH_UART_HAL_PARITY_FIX0	(PCH_UART_LCR_0P)
#घोषणा PCH_UART_HAL_5BIT		(PCH_UART_LCR_5BIT)
#घोषणा PCH_UART_HAL_6BIT		(PCH_UART_LCR_6BIT)
#घोषणा PCH_UART_HAL_7BIT		(PCH_UART_LCR_7BIT)
#घोषणा PCH_UART_HAL_8BIT		(PCH_UART_LCR_8BIT)
#घोषणा PCH_UART_HAL_STB1		0
#घोषणा PCH_UART_HAL_STB2		(PCH_UART_LCR_STB)

#घोषणा PCH_UART_HAL_CLR_TX_FIFO	(PCH_UART_FCR_TFR)
#घोषणा PCH_UART_HAL_CLR_RX_FIFO	(PCH_UART_FCR_RFR)
#घोषणा PCH_UART_HAL_CLR_ALL_FIFO	(PCH_UART_HAL_CLR_TX_FIFO | \
					PCH_UART_HAL_CLR_RX_FIFO)

#घोषणा PCH_UART_HAL_DMA_MODE0		0
#घोषणा PCH_UART_HAL_FIFO_DIS		0
#घोषणा PCH_UART_HAL_FIFO16		(PCH_UART_FCR_FIFOE)
#घोषणा PCH_UART_HAL_FIFO256		(PCH_UART_FCR_FIFOE | \
					PCH_UART_FCR_FIFO256)
#घोषणा PCH_UART_HAL_FIFO64		(PCH_UART_HAL_FIFO256)
#घोषणा PCH_UART_HAL_TRIGGER1		(PCH_UART_FCR_RFTL1)
#घोषणा PCH_UART_HAL_TRIGGER64		(PCH_UART_FCR_RFTL64)
#घोषणा PCH_UART_HAL_TRIGGER128		(PCH_UART_FCR_RFTL128)
#घोषणा PCH_UART_HAL_TRIGGER224		(PCH_UART_FCR_RFTL224)
#घोषणा PCH_UART_HAL_TRIGGER16		(PCH_UART_FCR_RFTL16)
#घोषणा PCH_UART_HAL_TRIGGER32		(PCH_UART_FCR_RFTL32)
#घोषणा PCH_UART_HAL_TRIGGER56		(PCH_UART_FCR_RFTL56)
#घोषणा PCH_UART_HAL_TRIGGER4		(PCH_UART_FCR_RFTL4)
#घोषणा PCH_UART_HAL_TRIGGER8		(PCH_UART_FCR_RFTL8)
#घोषणा PCH_UART_HAL_TRIGGER14		(PCH_UART_FCR_RFTL14)
#घोषणा PCH_UART_HAL_TRIGGER_L		(PCH_UART_FCR_RFTL64)
#घोषणा PCH_UART_HAL_TRIGGER_M		(PCH_UART_FCR_RFTL128)
#घोषणा PCH_UART_HAL_TRIGGER_H		(PCH_UART_FCR_RFTL224)

#घोषणा PCH_UART_HAL_RX_INT		(PCH_UART_IER_ERBFI)
#घोषणा PCH_UART_HAL_TX_INT		(PCH_UART_IER_ETBEI)
#घोषणा PCH_UART_HAL_RX_ERR_INT		(PCH_UART_IER_ELSI)
#घोषणा PCH_UART_HAL_MS_INT		(PCH_UART_IER_EDSSI)
#घोषणा PCH_UART_HAL_ALL_INT		(PCH_UART_IER_MASK)

#घोषणा PCH_UART_HAL_DTR		(PCH_UART_MCR_DTR)
#घोषणा PCH_UART_HAL_RTS		(PCH_UART_MCR_RTS)
#घोषणा PCH_UART_HAL_OUT		(PCH_UART_MCR_OUT)
#घोषणा PCH_UART_HAL_LOOP		(PCH_UART_MCR_LOOP)
#घोषणा PCH_UART_HAL_AFE		(PCH_UART_MCR_AFE)

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

#घोषणा DEFAULT_UARTCLK   1843200 /*   1.8432 MHz */
#घोषणा CMITC_UARTCLK   192000000 /* 192.0000 MHz */
#घोषणा FRI2_64_UARTCLK  64000000 /*  64.0000 MHz */
#घोषणा FRI2_48_UARTCLK  48000000 /*  48.0000 MHz */
#घोषणा NTC1_UARTCLK     64000000 /*  64.0000 MHz */
#घोषणा MINNOW_UARTCLK   50000000 /*  50.0000 MHz */

काष्ठा pch_uart_buffer अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक size;
पूर्ण;

काष्ठा eg20t_port अणु
	काष्ठा uart_port port;
	पूर्णांक port_type;
	व्योम __iomem *membase;
	resource_माप_प्रकार mapbase;
	अचिन्हित पूर्णांक iobase;
	काष्ठा pci_dev *pdev;
	पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक uartclk;
	पूर्णांक start_tx;
	पूर्णांक start_rx;
	पूर्णांक tx_empty;
	पूर्णांक trigger;
	पूर्णांक trigger_level;
	काष्ठा pch_uart_buffer rxbuf;
	अचिन्हित पूर्णांक dmsr;
	अचिन्हित पूर्णांक fcr;
	अचिन्हित पूर्णांक mcr;
	अचिन्हित पूर्णांक use_dma;
	काष्ठा dma_async_tx_descriptor	*desc_tx;
	काष्ठा dma_async_tx_descriptor	*desc_rx;
	काष्ठा pch_dma_slave		param_tx;
	काष्ठा pch_dma_slave		param_rx;
	काष्ठा dma_chan			*chan_tx;
	काष्ठा dma_chan			*chan_rx;
	काष्ठा scatterlist		*sg_tx_p;
	पूर्णांक				nent;
	पूर्णांक				orig_nent;
	काष्ठा scatterlist		sg_rx;
	पूर्णांक				tx_dma_use;
	व्योम				*rx_buf_virt;
	dma_addr_t			rx_buf_dma;

#घोषणा IRQ_NAME_SIZE 17
	अक्षर				irq_name[IRQ_NAME_SIZE];

	/* protect the eg20t_port निजी काष्ठाure and io access to membase */
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा pch_uart_driver_data - निजी data काष्ठाure क्रम UART-DMA
 * @port_type:			The type of UART port
 * @line_no:			UART port line number (0, 1, 2...)
 */
काष्ठा pch_uart_driver_data अणु
	पूर्णांक port_type;
	पूर्णांक line_no;
पूर्ण;

क्रमागत pch_uart_num_t अणु
	pch_et20t_uart0 = 0,
	pch_et20t_uart1,
	pch_et20t_uart2,
	pch_et20t_uart3,
	pch_ml7213_uart0,
	pch_ml7213_uart1,
	pch_ml7213_uart2,
	pch_ml7223_uart0,
	pch_ml7223_uart1,
	pch_ml7831_uart0,
	pch_ml7831_uart1,
पूर्ण;

अटल काष्ठा pch_uart_driver_data drv_dat[] = अणु
	[pch_et20t_uart0] = अणुPORT_PCH_8LINE, 0पूर्ण,
	[pch_et20t_uart1] = अणुPORT_PCH_2LINE, 1पूर्ण,
	[pch_et20t_uart2] = अणुPORT_PCH_2LINE, 2पूर्ण,
	[pch_et20t_uart3] = अणुPORT_PCH_2LINE, 3पूर्ण,
	[pch_ml7213_uart0] = अणुPORT_PCH_8LINE, 0पूर्ण,
	[pch_ml7213_uart1] = अणुPORT_PCH_2LINE, 1पूर्ण,
	[pch_ml7213_uart2] = अणुPORT_PCH_2LINE, 2पूर्ण,
	[pch_ml7223_uart0] = अणुPORT_PCH_8LINE, 0पूर्ण,
	[pch_ml7223_uart1] = अणुPORT_PCH_2LINE, 1पूर्ण,
	[pch_ml7831_uart0] = अणुPORT_PCH_8LINE, 0पूर्ण,
	[pch_ml7831_uart1] = अणुPORT_PCH_2LINE, 1पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_PCH_UART_CONSOLE
अटल काष्ठा eg20t_port *pch_uart_ports[PCH_UART_NR];
#पूर्ण_अगर
अटल अचिन्हित पूर्णांक शेष_baud = 9600;
अटल अचिन्हित पूर्णांक user_uartclk = 0;
अटल स्थिर पूर्णांक trigger_level_256[4] = अणु 1, 64, 128, 224 पूर्ण;
अटल स्थिर पूर्णांक trigger_level_64[4] = अणु 1, 16, 32, 56 पूर्ण;
अटल स्थिर पूर्णांक trigger_level_16[4] = अणु 1, 4, 8, 14 पूर्ण;
अटल स्थिर पूर्णांक trigger_level_1[4] = अणु 1, 1, 1, 1 पूर्ण;

#घोषणा PCH_REGS_बफ_मानE	1024


अटल sमाप_प्रकार port_show_regs(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा eg20t_port *priv = file->निजी_data;
	अक्षर *buf;
	u32 len = 0;
	sमाप_प्रकार ret;
	अचिन्हित अक्षर lcr;

	buf = kzalloc(PCH_REGS_बफ_मानE, GFP_KERNEL);
	अगर (!buf)
		वापस 0;

	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"PCH EG20T port[%d] regs:\n", priv->port.line);

	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"=================================\n");
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"IER: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_IER));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"IIR: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_IIR));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"LCR: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_LCR));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"MCR: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_MCR));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"LSR: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_LSR));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"MSR: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_MSR));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"BRCSR: \t0x%02x\n",
			ioपढ़ो8(priv->membase + PCH_UART_BRCSR));

	lcr = ioपढ़ो8(priv->membase + UART_LCR);
	ioग_लिखो8(PCH_UART_LCR_DLAB, priv->membase + UART_LCR);
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"DLL: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_DLL));
	len += scnम_लिखो(buf + len, PCH_REGS_बफ_मानE - len,
			"DLM: \t0x%02x\n", ioपढ़ो8(priv->membase + UART_DLM));
	ioग_लिखो8(lcr, priv->membase + UART_LCR);

	अगर (len > PCH_REGS_बफ_मानE)
		len = PCH_REGS_बफ_मानE;

	ret =  simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations port_regs_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= simple_खोलो,
	.पढ़ो		= port_show_regs,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id pch_uart_dmi_table[] = अणु
	अणु
		.ident = "CM-iTC",
		अणु
			DMI_MATCH(DMI_BOARD_NAME, "CM-iTC"),
		पूर्ण,
		(व्योम *)CMITC_UARTCLK,
	पूर्ण,
	अणु
		.ident = "FRI2",
		अणु
			DMI_MATCH(DMI_BIOS_VERSION, "FRI2"),
		पूर्ण,
		(व्योम *)FRI2_64_UARTCLK,
	पूर्ण,
	अणु
		.ident = "Fish River Island II",
		अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Fish River Island II"),
		पूर्ण,
		(व्योम *)FRI2_48_UARTCLK,
	पूर्ण,
	अणु
		.ident = "COMe-mTT",
		अणु
			DMI_MATCH(DMI_BOARD_NAME, "COMe-mTT"),
		पूर्ण,
		(व्योम *)NTC1_UARTCLK,
	पूर्ण,
	अणु
		.ident = "nanoETXexpress-TT",
		अणु
			DMI_MATCH(DMI_BOARD_NAME, "nanoETXexpress-TT"),
		पूर्ण,
		(व्योम *)NTC1_UARTCLK,
	पूर्ण,
	अणु
		.ident = "MinnowBoard",
		अणु
			DMI_MATCH(DMI_BOARD_NAME, "MinnowBoard"),
		पूर्ण,
		(व्योम *)MINNOW_UARTCLK,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Return UART घड़ी, checking क्रम board specअगरic घड़ीs. */
अटल अचिन्हित पूर्णांक pch_uart_get_uartclk(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *d;

	अगर (user_uartclk)
		वापस user_uartclk;

	d = dmi_first_match(pch_uart_dmi_table);
	अगर (d)
		वापस (अचिन्हित दीर्घ)d->driver_data;

	वापस DEFAULT_UARTCLK;
पूर्ण

अटल व्योम pch_uart_hal_enable_पूर्णांकerrupt(काष्ठा eg20t_port *priv,
					  अचिन्हित पूर्णांक flag)
अणु
	u8 ier = ioपढ़ो8(priv->membase + UART_IER);
	ier |= flag & PCH_UART_IER_MASK;
	ioग_लिखो8(ier, priv->membase + UART_IER);
पूर्ण

अटल व्योम pch_uart_hal_disable_पूर्णांकerrupt(काष्ठा eg20t_port *priv,
					   अचिन्हित पूर्णांक flag)
अणु
	u8 ier = ioपढ़ो8(priv->membase + UART_IER);
	ier &= ~(flag & PCH_UART_IER_MASK);
	ioग_लिखो8(ier, priv->membase + UART_IER);
पूर्ण

अटल पूर्णांक pch_uart_hal_set_line(काष्ठा eg20t_port *priv, अचिन्हित पूर्णांक baud,
				 अचिन्हित पूर्णांक parity, अचिन्हित पूर्णांक bits,
				 अचिन्हित पूर्णांक stb)
अणु
	अचिन्हित पूर्णांक dll, dlm, lcr;
	पूर्णांक भाग;

	भाग = DIV_ROUND_CLOSEST(priv->uartclk / 16, baud);
	अगर (भाग < 0 || अच_लघु_उच्च <= भाग) अणु
		dev_err(priv->port.dev, "Invalid Baud(div=0x%x)\n", भाग);
		वापस -EINVAL;
	पूर्ण

	dll = (अचिन्हित पूर्णांक)भाग & 0x00FFU;
	dlm = ((अचिन्हित पूर्णांक)भाग >> 8) & 0x00FFU;

	अगर (parity & ~(PCH_UART_LCR_PEN | PCH_UART_LCR_EPS | PCH_UART_LCR_SP)) अणु
		dev_err(priv->port.dev, "Invalid parity(0x%x)\n", parity);
		वापस -EINVAL;
	पूर्ण

	अगर (bits & ~PCH_UART_LCR_WLS) अणु
		dev_err(priv->port.dev, "Invalid bits(0x%x)\n", bits);
		वापस -EINVAL;
	पूर्ण

	अगर (stb & ~PCH_UART_LCR_STB) अणु
		dev_err(priv->port.dev, "Invalid STB(0x%x)\n", stb);
		वापस -EINVAL;
	पूर्ण

	lcr = parity;
	lcr |= bits;
	lcr |= stb;

	dev_dbg(priv->port.dev, "%s:baud = %u, div = %04x, lcr = %02x (%lu)\n",
		 __func__, baud, भाग, lcr, jअगरfies);
	ioग_लिखो8(PCH_UART_LCR_DLAB, priv->membase + UART_LCR);
	ioग_लिखो8(dll, priv->membase + PCH_UART_DLL);
	ioग_लिखो8(dlm, priv->membase + PCH_UART_DLM);
	ioग_लिखो8(lcr, priv->membase + UART_LCR);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_uart_hal_fअगरo_reset(काष्ठा eg20t_port *priv,
				    अचिन्हित पूर्णांक flag)
अणु
	अगर (flag & ~(PCH_UART_FCR_TFR | PCH_UART_FCR_RFR)) अणु
		dev_err(priv->port.dev, "%s:Invalid flag(0x%x)\n",
			__func__, flag);
		वापस -EINVAL;
	पूर्ण

	ioग_लिखो8(PCH_UART_FCR_FIFOE | priv->fcr, priv->membase + UART_FCR);
	ioग_लिखो8(PCH_UART_FCR_FIFOE | priv->fcr | flag,
		 priv->membase + UART_FCR);
	ioग_लिखो8(priv->fcr, priv->membase + UART_FCR);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_uart_hal_set_fअगरo(काष्ठा eg20t_port *priv,
				 अचिन्हित पूर्णांक dmamode,
				 अचिन्हित पूर्णांक fअगरo_size, अचिन्हित पूर्णांक trigger)
अणु
	u8 fcr;

	अगर (dmamode & ~PCH_UART_FCR_DMS) अणु
		dev_err(priv->port.dev, "%s:Invalid DMA Mode(0x%x)\n",
			__func__, dmamode);
		वापस -EINVAL;
	पूर्ण

	अगर (fअगरo_size & ~(PCH_UART_FCR_FIFOE | PCH_UART_FCR_FIFO256)) अणु
		dev_err(priv->port.dev, "%s:Invalid FIFO SIZE(0x%x)\n",
			__func__, fअगरo_size);
		वापस -EINVAL;
	पूर्ण

	अगर (trigger & ~PCH_UART_FCR_RFTL) अणु
		dev_err(priv->port.dev, "%s:Invalid TRIGGER(0x%x)\n",
			__func__, trigger);
		वापस -EINVAL;
	पूर्ण

	चयन (priv->fअगरo_size) अणु
	हाल 256:
		priv->trigger_level =
		    trigger_level_256[trigger >> PCH_UART_FCR_RFTL_SHIFT];
		अवरोध;
	हाल 64:
		priv->trigger_level =
		    trigger_level_64[trigger >> PCH_UART_FCR_RFTL_SHIFT];
		अवरोध;
	हाल 16:
		priv->trigger_level =
		    trigger_level_16[trigger >> PCH_UART_FCR_RFTL_SHIFT];
		अवरोध;
	शेष:
		priv->trigger_level =
		    trigger_level_1[trigger >> PCH_UART_FCR_RFTL_SHIFT];
		अवरोध;
	पूर्ण
	fcr =
	    dmamode | fअगरo_size | trigger | PCH_UART_FCR_RFR | PCH_UART_FCR_TFR;
	ioग_लिखो8(PCH_UART_FCR_FIFOE, priv->membase + UART_FCR);
	ioग_लिखो8(PCH_UART_FCR_FIFOE | PCH_UART_FCR_RFR | PCH_UART_FCR_TFR,
		 priv->membase + UART_FCR);
	ioग_लिखो8(fcr, priv->membase + UART_FCR);
	priv->fcr = fcr;

	वापस 0;
पूर्ण

अटल u8 pch_uart_hal_get_modem(काष्ठा eg20t_port *priv)
अणु
	अचिन्हित पूर्णांक msr = ioपढ़ो8(priv->membase + UART_MSR);
	priv->dmsr = msr & PCH_UART_MSR_DELTA;
	वापस (u8)msr;
पूर्ण

अटल व्योम pch_uart_hal_ग_लिखो(काष्ठा eg20t_port *priv,
			      स्थिर अचिन्हित अक्षर *buf, पूर्णांक tx_size)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक thr;

	क्रम (i = 0; i < tx_size;) अणु
		thr = buf[i++];
		ioग_लिखो8(thr, priv->membase + PCH_UART_THR);
	पूर्ण
पूर्ण

अटल पूर्णांक pch_uart_hal_पढ़ो(काष्ठा eg20t_port *priv, अचिन्हित अक्षर *buf,
			     पूर्णांक rx_size)
अणु
	पूर्णांक i;
	u8 rbr, lsr;
	काष्ठा uart_port *port = &priv->port;

	lsr = ioपढ़ो8(priv->membase + UART_LSR);
	क्रम (i = 0, lsr = ioपढ़ो8(priv->membase + UART_LSR);
	     i < rx_size && lsr & (UART_LSR_DR | UART_LSR_BI);
	     lsr = ioपढ़ो8(priv->membase + UART_LSR)) अणु
		rbr = ioपढ़ो8(priv->membase + PCH_UART_RBR);

		अगर (lsr & UART_LSR_BI) अणु
			port->icount.brk++;
			अगर (uart_handle_अवरोध(port))
				जारी;
		पूर्ण
		अगर (uart_handle_sysrq_अक्षर(port, rbr))
			जारी;

		buf[i++] = rbr;
	पूर्ण
	वापस i;
पूर्ण

अटल अचिन्हित अक्षर pch_uart_hal_get_iid(काष्ठा eg20t_port *priv)
अणु
	वापस ioपढ़ो8(priv->membase + UART_IIR) &\
		      (PCH_UART_IIR_IID | PCH_UART_IIR_TOI | PCH_UART_IIR_IP);
पूर्ण

अटल u8 pch_uart_hal_get_line_status(काष्ठा eg20t_port *priv)
अणु
	वापस ioपढ़ो8(priv->membase + UART_LSR);
पूर्ण

अटल व्योम pch_uart_hal_set_अवरोध(काष्ठा eg20t_port *priv, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक lcr;

	lcr = ioपढ़ो8(priv->membase + UART_LCR);
	अगर (on)
		lcr |= PCH_UART_LCR_SB;
	अन्यथा
		lcr &= ~PCH_UART_LCR_SB;

	ioग_लिखो8(lcr, priv->membase + UART_LCR);
पूर्ण

अटल पूर्णांक push_rx(काष्ठा eg20t_port *priv, स्थिर अचिन्हित अक्षर *buf,
		   पूर्णांक size)
अणु
	काष्ठा uart_port *port = &priv->port;
	काष्ठा tty_port *tport = &port->state->port;

	tty_insert_flip_string(tport, buf, size);
	tty_flip_buffer_push(tport);

	वापस 0;
पूर्ण

अटल पूर्णांक pop_tx_x(काष्ठा eg20t_port *priv, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक ret = 0;
	काष्ठा uart_port *port = &priv->port;

	अगर (port->x_अक्षर) अणु
		dev_dbg(priv->port.dev, "%s:X character send %02x (%lu)\n",
			__func__, port->x_अक्षर, jअगरfies);
		buf[0] = port->x_अक्षर;
		port->x_अक्षर = 0;
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dma_push_rx(काष्ठा eg20t_port *priv, पूर्णांक size)
अणु
	पूर्णांक room;
	काष्ठा uart_port *port = &priv->port;
	काष्ठा tty_port *tport = &port->state->port;

	room = tty_buffer_request_room(tport, size);

	अगर (room < size)
		dev_warn(port->dev, "Rx overrun: dropping %u bytes\n",
			 size - room);
	अगर (!room)
		वापस 0;

	tty_insert_flip_string(tport, sg_virt(&priv->sg_rx), size);

	port->icount.rx += room;

	वापस room;
पूर्ण

अटल व्योम pch_मुक्त_dma(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	priv = container_of(port, काष्ठा eg20t_port, port);

	अगर (priv->chan_tx) अणु
		dma_release_channel(priv->chan_tx);
		priv->chan_tx = शून्य;
	पूर्ण
	अगर (priv->chan_rx) अणु
		dma_release_channel(priv->chan_rx);
		priv->chan_rx = शून्य;
	पूर्ण

	अगर (priv->rx_buf_dma) अणु
		dma_मुक्त_coherent(port->dev, port->fअगरosize, priv->rx_buf_virt,
				  priv->rx_buf_dma);
		priv->rx_buf_virt = शून्य;
		priv->rx_buf_dma = 0;
	पूर्ण

	वापस;
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *slave)
अणु
	काष्ठा pch_dma_slave *param = slave;

	अगर ((chan->chan_id == param->chan_id) && (param->dma_dev ==
						  chan->device->dev)) अणु
		chan->निजी = param;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम pch_request_dma(काष्ठा uart_port *port)
अणु
	dma_cap_mask_t mask;
	काष्ठा dma_chan *chan;
	काष्ठा pci_dev *dma_dev;
	काष्ठा pch_dma_slave *param;
	काष्ठा eg20t_port *priv =
				container_of(port, काष्ठा eg20t_port, port);
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Get DMA's dev inक्रमmation */
	dma_dev = pci_get_slot(priv->pdev->bus,
			PCI_DEVFN(PCI_SLOT(priv->pdev->devfn), 0));

	/* Set Tx DMA */
	param = &priv->param_tx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = priv->port.line * 2; /* Tx = 0, 2, 4, ... */

	param->tx_reg = port->mapbase + UART_TX;
	chan = dma_request_channel(mask, filter, param);
	अगर (!chan) अणु
		dev_err(priv->port.dev, "%s:dma_request_channel FAILS(Tx)\n",
			__func__);
		वापस;
	पूर्ण
	priv->chan_tx = chan;

	/* Set Rx DMA */
	param = &priv->param_rx;
	param->dma_dev = &dma_dev->dev;
	param->chan_id = priv->port.line * 2 + 1; /* Rx = Tx + 1 */

	param->rx_reg = port->mapbase + UART_RX;
	chan = dma_request_channel(mask, filter, param);
	अगर (!chan) अणु
		dev_err(priv->port.dev, "%s:dma_request_channel FAILS(Rx)\n",
			__func__);
		dma_release_channel(priv->chan_tx);
		priv->chan_tx = शून्य;
		वापस;
	पूर्ण

	/* Get Consistent memory क्रम DMA */
	priv->rx_buf_virt = dma_alloc_coherent(port->dev, port->fअगरosize,
				    &priv->rx_buf_dma, GFP_KERNEL);
	priv->chan_rx = chan;
पूर्ण

अटल व्योम pch_dma_rx_complete(व्योम *arg)
अणु
	काष्ठा eg20t_port *priv = arg;
	काष्ठा uart_port *port = &priv->port;
	पूर्णांक count;

	dma_sync_sg_क्रम_cpu(port->dev, &priv->sg_rx, 1, DMA_FROM_DEVICE);
	count = dma_push_rx(priv, priv->trigger_level);
	अगर (count)
		tty_flip_buffer_push(&port->state->port);
	async_tx_ack(priv->desc_rx);
	pch_uart_hal_enable_पूर्णांकerrupt(priv, PCH_UART_HAL_RX_INT |
					    PCH_UART_HAL_RX_ERR_INT);
पूर्ण

अटल व्योम pch_dma_tx_complete(व्योम *arg)
अणु
	काष्ठा eg20t_port *priv = arg;
	काष्ठा uart_port *port = &priv->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा scatterlist *sg = priv->sg_tx_p;
	पूर्णांक i;

	क्रम (i = 0; i < priv->nent; i++, sg++) अणु
		xmit->tail += sg_dma_len(sg);
		port->icount.tx += sg_dma_len(sg);
	पूर्ण
	xmit->tail &= UART_XMIT_SIZE - 1;
	async_tx_ack(priv->desc_tx);
	dma_unmap_sg(port->dev, sg, priv->orig_nent, DMA_TO_DEVICE);
	priv->tx_dma_use = 0;
	priv->nent = 0;
	priv->orig_nent = 0;
	kमुक्त(priv->sg_tx_p);
	pch_uart_hal_enable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
पूर्ण

अटल पूर्णांक pop_tx(काष्ठा eg20t_port *priv, पूर्णांक size)
अणु
	पूर्णांक count = 0;
	काष्ठा uart_port *port = &priv->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (uart_tx_stopped(port) || uart_circ_empty(xmit) || count >= size)
		जाओ pop_tx_end;

	करो अणु
		पूर्णांक cnt_to_end =
		    CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
		पूर्णांक sz = min(size - count, cnt_to_end);
		pch_uart_hal_ग_लिखो(priv, &xmit->buf[xmit->tail], sz);
		xmit->tail = (xmit->tail + sz) & (UART_XMIT_SIZE - 1);
		count += sz;
	पूर्ण जबतक (!uart_circ_empty(xmit) && count < size);

pop_tx_end:
	dev_dbg(priv->port.dev, "%d characters. Remained %d characters.(%lu)\n",
		 count, size - count, jअगरfies);

	वापस count;
पूर्ण

अटल पूर्णांक handle_rx_to(काष्ठा eg20t_port *priv)
अणु
	काष्ठा pch_uart_buffer *buf;
	पूर्णांक rx_size;
	पूर्णांक ret;
	अगर (!priv->start_rx) अणु
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_RX_INT |
						     PCH_UART_HAL_RX_ERR_INT);
		वापस 0;
	पूर्ण
	buf = &priv->rxbuf;
	करो अणु
		rx_size = pch_uart_hal_पढ़ो(priv, buf->buf, buf->size);
		ret = push_rx(priv, buf->buf, rx_size);
		अगर (ret)
			वापस 0;
	पूर्ण जबतक (rx_size == buf->size);

	वापस PCH_UART_HANDLED_RX_INT;
पूर्ण

अटल पूर्णांक handle_rx(काष्ठा eg20t_port *priv)
अणु
	वापस handle_rx_to(priv);
पूर्ण

अटल पूर्णांक dma_handle_rx(काष्ठा eg20t_port *priv)
अणु
	काष्ठा uart_port *port = &priv->port;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist *sg;

	priv = container_of(port, काष्ठा eg20t_port, port);
	sg = &priv->sg_rx;

	sg_init_table(&priv->sg_rx, 1); /* Initialize SG table */

	sg_dma_len(sg) = priv->trigger_level;

	sg_set_page(&priv->sg_rx, virt_to_page(priv->rx_buf_virt),
		     sg_dma_len(sg), offset_in_page(priv->rx_buf_virt));

	sg_dma_address(sg) = priv->rx_buf_dma;

	desc = dmaengine_prep_slave_sg(priv->chan_rx,
			sg, 1, DMA_DEV_TO_MEM,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!desc)
		वापस 0;

	priv->desc_rx = desc;
	desc->callback = pch_dma_rx_complete;
	desc->callback_param = priv;
	desc->tx_submit(desc);
	dma_async_issue_pending(priv->chan_rx);

	वापस PCH_UART_HANDLED_RX_INT;
पूर्ण

अटल अचिन्हित पूर्णांक handle_tx(काष्ठा eg20t_port *priv)
अणु
	काष्ठा uart_port *port = &priv->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक fअगरo_size;
	पूर्णांक tx_size;
	पूर्णांक size;
	पूर्णांक tx_empty;

	अगर (!priv->start_tx) अणु
		dev_info(priv->port.dev, "%s:Tx isn't started. (%lu)\n",
			__func__, jअगरfies);
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
		priv->tx_empty = 1;
		वापस 0;
	पूर्ण

	fअगरo_size = max(priv->fअगरo_size, 1);
	tx_empty = 1;
	अगर (pop_tx_x(priv, xmit->buf)) अणु
		pch_uart_hal_ग_लिखो(priv, xmit->buf, 1);
		port->icount.tx++;
		tx_empty = 0;
		fअगरo_size--;
	पूर्ण
	size = min(xmit->head - xmit->tail, fअगरo_size);
	अगर (size < 0)
		size = fअगरo_size;

	tx_size = pop_tx(priv, size);
	अगर (tx_size > 0) अणु
		port->icount.tx += tx_size;
		tx_empty = 0;
	पूर्ण

	priv->tx_empty = tx_empty;

	अगर (tx_empty) अणु
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
		uart_ग_लिखो_wakeup(port);
	पूर्ण

	वापस PCH_UART_HANDLED_TX_INT;
पूर्ण

अटल अचिन्हित पूर्णांक dma_handle_tx(काष्ठा eg20t_port *priv)
अणु
	काष्ठा uart_port *port = &priv->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा scatterlist *sg;
	पूर्णांक nent;
	पूर्णांक fअगरo_size;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक num;
	पूर्णांक i;
	पूर्णांक bytes;
	पूर्णांक size;
	पूर्णांक rem;

	अगर (!priv->start_tx) अणु
		dev_info(priv->port.dev, "%s:Tx isn't started. (%lu)\n",
			__func__, jअगरfies);
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
		priv->tx_empty = 1;
		वापस 0;
	पूर्ण

	अगर (priv->tx_dma_use) अणु
		dev_dbg(priv->port.dev, "%s:Tx is not completed. (%lu)\n",
			__func__, jअगरfies);
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
		priv->tx_empty = 1;
		वापस 0;
	पूर्ण

	fअगरo_size = max(priv->fअगरo_size, 1);
	अगर (pop_tx_x(priv, xmit->buf)) अणु
		pch_uart_hal_ग_लिखो(priv, xmit->buf, 1);
		port->icount.tx++;
		fअगरo_size--;
	पूर्ण

	bytes = min((पूर्णांक)CIRC_CNT(xmit->head, xmit->tail,
			     UART_XMIT_SIZE), CIRC_CNT_TO_END(xmit->head,
			     xmit->tail, UART_XMIT_SIZE));
	अगर (!bytes) अणु
		dev_dbg(priv->port.dev, "%s 0 bytes return\n", __func__);
		pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
		uart_ग_लिखो_wakeup(port);
		वापस 0;
	पूर्ण

	अगर (bytes > fअगरo_size) अणु
		num = bytes / fअगरo_size + 1;
		size = fअगरo_size;
		rem = bytes % fअगरo_size;
	पूर्ण अन्यथा अणु
		num = 1;
		size = bytes;
		rem = bytes;
	पूर्ण

	dev_dbg(priv->port.dev, "%s num=%d size=%d rem=%d\n",
		__func__, num, size, rem);

	priv->tx_dma_use = 1;

	priv->sg_tx_p = kदो_स्मृति_array(num, माप(काष्ठा scatterlist), GFP_ATOMIC);
	अगर (!priv->sg_tx_p) अणु
		dev_err(priv->port.dev, "%s:kzalloc Failed\n", __func__);
		वापस 0;
	पूर्ण

	sg_init_table(priv->sg_tx_p, num); /* Initialize SG table */
	sg = priv->sg_tx_p;

	क्रम (i = 0; i < num; i++, sg++) अणु
		अगर (i == (num - 1))
			sg_set_page(sg, virt_to_page(xmit->buf),
				    rem, fअगरo_size * i);
		अन्यथा
			sg_set_page(sg, virt_to_page(xmit->buf),
				    size, fअगरo_size * i);
	पूर्ण

	sg = priv->sg_tx_p;
	nent = dma_map_sg(port->dev, sg, num, DMA_TO_DEVICE);
	अगर (!nent) अणु
		dev_err(priv->port.dev, "%s:dma_map_sg Failed\n", __func__);
		वापस 0;
	पूर्ण
	priv->orig_nent = num;
	priv->nent = nent;

	क्रम (i = 0; i < nent; i++, sg++) अणु
		sg->offset = (xmit->tail & (UART_XMIT_SIZE - 1)) +
			      fअगरo_size * i;
		sg_dma_address(sg) = (sg_dma_address(sg) &
				    ~(UART_XMIT_SIZE - 1)) + sg->offset;
		अगर (i == (nent - 1))
			sg_dma_len(sg) = rem;
		अन्यथा
			sg_dma_len(sg) = size;
	पूर्ण

	desc = dmaengine_prep_slave_sg(priv->chan_tx,
					priv->sg_tx_p, nent, DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(priv->port.dev, "%s:dmaengine_prep_slave_sg Failed\n",
			__func__);
		वापस 0;
	पूर्ण
	dma_sync_sg_क्रम_device(port->dev, priv->sg_tx_p, nent, DMA_TO_DEVICE);
	priv->desc_tx = desc;
	desc->callback = pch_dma_tx_complete;
	desc->callback_param = priv;

	desc->tx_submit(desc);

	dma_async_issue_pending(priv->chan_tx);

	वापस PCH_UART_HANDLED_TX_INT;
पूर्ण

अटल व्योम pch_uart_err_ir(काष्ठा eg20t_port *priv, अचिन्हित पूर्णांक lsr)
अणु
	काष्ठा uart_port *port = &priv->port;
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&port->state->port);
	अक्षर   *error_msg[5] = अणुपूर्ण;
	पूर्णांक    i = 0;

	अगर (lsr & PCH_UART_LSR_ERR)
		error_msg[i++] = "Error data in FIFO\n";

	अगर (lsr & UART_LSR_FE) अणु
		port->icount.frame++;
		error_msg[i++] = "  Framing Error\n";
	पूर्ण

	अगर (lsr & UART_LSR_PE) अणु
		port->icount.parity++;
		error_msg[i++] = "  Parity Error\n";
	पूर्ण

	अगर (lsr & UART_LSR_OE) अणु
		port->icount.overrun++;
		error_msg[i++] = "  Overrun Error\n";
	पूर्ण

	अगर (tty == शून्य) अणु
		क्रम (i = 0; error_msg[i] != शून्य; i++)
			dev_err(&priv->pdev->dev, error_msg[i]);
	पूर्ण अन्यथा अणु
		tty_kref_put(tty);
	पूर्ण
पूर्ण

अटल irqवापस_t pch_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा eg20t_port *priv = dev_id;
	अचिन्हित पूर्णांक handled;
	u8 lsr;
	पूर्णांक ret = 0;
	अचिन्हित अक्षर iid;
	अचिन्हित दीर्घ flags;
	पूर्णांक next = 1;
	u8 msr;

	spin_lock_irqsave(&priv->lock, flags);
	handled = 0;
	जबतक (next) अणु
		iid = pch_uart_hal_get_iid(priv);
		अगर (iid & PCH_UART_IIR_IP) /* No Interrupt */
			अवरोध;
		चयन (iid) अणु
		हाल PCH_UART_IID_RLS:	/* Receiver Line Status */
			lsr = pch_uart_hal_get_line_status(priv);
			अगर (lsr & (PCH_UART_LSR_ERR | UART_LSR_FE |
						UART_LSR_PE | UART_LSR_OE)) अणु
				pch_uart_err_ir(priv, lsr);
				ret = PCH_UART_HANDLED_RX_ERR_INT;
			पूर्ण अन्यथा अणु
				ret = PCH_UART_HANDLED_LS_INT;
			पूर्ण
			अवरोध;
		हाल PCH_UART_IID_RDR:	/* Received Data Ready */
			अगर (priv->use_dma) अणु
				pch_uart_hal_disable_पूर्णांकerrupt(priv,
						PCH_UART_HAL_RX_INT |
						PCH_UART_HAL_RX_ERR_INT);
				ret = dma_handle_rx(priv);
				अगर (!ret)
					pch_uart_hal_enable_पूर्णांकerrupt(priv,
						PCH_UART_HAL_RX_INT |
						PCH_UART_HAL_RX_ERR_INT);
			पूर्ण अन्यथा अणु
				ret = handle_rx(priv);
			पूर्ण
			अवरोध;
		हाल PCH_UART_IID_RDR_TO:	/* Received Data Ready
						   (FIFO Timeout) */
			ret = handle_rx_to(priv);
			अवरोध;
		हाल PCH_UART_IID_THRE:	/* Transmitter Holding Register
						   Empty */
			अगर (priv->use_dma)
				ret = dma_handle_tx(priv);
			अन्यथा
				ret = handle_tx(priv);
			अवरोध;
		हाल PCH_UART_IID_MS:	/* Modem Status */
			msr = pch_uart_hal_get_modem(priv);
			next = 0; /* MS ir prioirty is the lowest. So, MS ir
				     means final पूर्णांकerrupt */
			अगर ((msr & UART_MSR_ANY_DELTA) == 0)
				अवरोध;
			ret |= PCH_UART_HANDLED_MS_INT;
			अवरोध;
		शेष:	/* Never junp to this label */
			dev_err(priv->port.dev, "%s:iid=%02x (%lu)\n", __func__,
				iid, jअगरfies);
			ret = -1;
			next = 0;
			अवरोध;
		पूर्ण
		handled |= (अचिन्हित पूर्णांक)ret;
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

/* This function tests whether the transmitter fअगरo and shअगरter क्रम the port
						described by 'port' is empty. */
अटल अचिन्हित पूर्णांक pch_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;

	priv = container_of(port, काष्ठा eg20t_port, port);
	अगर (priv->tx_empty)
		वापस TIOCSER_TEMT;
	अन्यथा
		वापस 0;
पूर्ण

/* Returns the current state of modem control inमाला_दो. */
अटल अचिन्हित पूर्णांक pch_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	u8 modem;
	अचिन्हित पूर्णांक ret = 0;

	priv = container_of(port, काष्ठा eg20t_port, port);
	modem = pch_uart_hal_get_modem(priv);

	अगर (modem & UART_MSR_DCD)
		ret |= TIOCM_CAR;

	अगर (modem & UART_MSR_RI)
		ret |= TIOCM_RNG;

	अगर (modem & UART_MSR_DSR)
		ret |= TIOCM_DSR;

	अगर (modem & UART_MSR_CTS)
		ret |= TIOCM_CTS;

	वापस ret;
पूर्ण

अटल व्योम pch_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	u32 mcr = 0;
	काष्ठा eg20t_port *priv = container_of(port, काष्ठा eg20t_port, port);

	अगर (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	अगर (priv->mcr & UART_MCR_AFE)
		mcr |= UART_MCR_AFE;

	अगर (mctrl)
		ioग_लिखो8(mcr, priv->membase + UART_MCR);
पूर्ण

अटल व्योम pch_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	priv = container_of(port, काष्ठा eg20t_port, port);
	priv->start_tx = 0;
	priv->tx_dma_use = 0;
पूर्ण

अटल व्योम pch_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;

	priv = container_of(port, काष्ठा eg20t_port, port);

	अगर (priv->use_dma) अणु
		अगर (priv->tx_dma_use) अणु
			dev_dbg(priv->port.dev, "%s : Tx DMA is NOT empty.\n",
				__func__);
			वापस;
		पूर्ण
	पूर्ण

	priv->start_tx = 1;
	pch_uart_hal_enable_पूर्णांकerrupt(priv, PCH_UART_HAL_TX_INT);
पूर्ण

अटल व्योम pch_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	priv = container_of(port, काष्ठा eg20t_port, port);
	priv->start_rx = 0;
	pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_RX_INT |
					     PCH_UART_HAL_RX_ERR_INT);
पूर्ण

/* Enable the modem status पूर्णांकerrupts. */
अटल व्योम pch_uart_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	priv = container_of(port, काष्ठा eg20t_port, port);
	pch_uart_hal_enable_पूर्णांकerrupt(priv, PCH_UART_HAL_MS_INT);
पूर्ण

/* Control the transmission of a अवरोध संकेत. */
अटल व्योम pch_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	काष्ठा eg20t_port *priv;
	अचिन्हित दीर्घ flags;

	priv = container_of(port, काष्ठा eg20t_port, port);
	spin_lock_irqsave(&priv->lock, flags);
	pch_uart_hal_set_अवरोध(priv, ctl);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

/* Grab any पूर्णांकerrupt resources and initialise any low level driver state. */
अटल पूर्णांक pch_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	पूर्णांक ret;
	पूर्णांक fअगरo_size;
	पूर्णांक trigger_level;

	priv = container_of(port, काष्ठा eg20t_port, port);
	priv->tx_empty = 1;

	अगर (port->uartclk)
		priv->uartclk = port->uartclk;
	अन्यथा
		port->uartclk = priv->uartclk;

	pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_ALL_INT);
	ret = pch_uart_hal_set_line(priv, शेष_baud,
			      PCH_UART_HAL_PARITY_NONE, PCH_UART_HAL_8BIT,
			      PCH_UART_HAL_STB1);
	अगर (ret)
		वापस ret;

	चयन (priv->fअगरo_size) अणु
	हाल 256:
		fअगरo_size = PCH_UART_HAL_FIFO256;
		अवरोध;
	हाल 64:
		fअगरo_size = PCH_UART_HAL_FIFO64;
		अवरोध;
	हाल 16:
		fअगरo_size = PCH_UART_HAL_FIFO16;
		अवरोध;
	हाल 1:
	शेष:
		fअगरo_size = PCH_UART_HAL_FIFO_DIS;
		अवरोध;
	पूर्ण

	चयन (priv->trigger) अणु
	हाल PCH_UART_HAL_TRIGGER1:
		trigger_level = 1;
		अवरोध;
	हाल PCH_UART_HAL_TRIGGER_L:
		trigger_level = priv->fअगरo_size / 4;
		अवरोध;
	हाल PCH_UART_HAL_TRIGGER_M:
		trigger_level = priv->fअगरo_size / 2;
		अवरोध;
	हाल PCH_UART_HAL_TRIGGER_H:
	शेष:
		trigger_level = priv->fअगरo_size - (priv->fअगरo_size / 8);
		अवरोध;
	पूर्ण

	priv->trigger_level = trigger_level;
	ret = pch_uart_hal_set_fअगरo(priv, PCH_UART_HAL_DMA_MODE0,
				    fअगरo_size, priv->trigger);
	अगर (ret < 0)
		वापस ret;

	ret = request_irq(priv->port.irq, pch_uart_पूर्णांकerrupt, IRQF_SHARED,
			priv->irq_name, priv);
	अगर (ret < 0)
		वापस ret;

	अगर (priv->use_dma)
		pch_request_dma(port);

	priv->start_rx = 1;
	pch_uart_hal_enable_पूर्णांकerrupt(priv, PCH_UART_HAL_RX_INT |
					    PCH_UART_HAL_RX_ERR_INT);
	uart_update_समयout(port, CS8, शेष_baud);

	वापस 0;
पूर्ण

अटल व्योम pch_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	पूर्णांक ret;

	priv = container_of(port, काष्ठा eg20t_port, port);
	pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_ALL_INT);
	pch_uart_hal_fअगरo_reset(priv, PCH_UART_HAL_CLR_ALL_FIFO);
	ret = pch_uart_hal_set_fअगरo(priv, PCH_UART_HAL_DMA_MODE0,
			      PCH_UART_HAL_FIFO_DIS, PCH_UART_HAL_TRIGGER1);
	अगर (ret)
		dev_err(priv->port.dev,
			"pch_uart_hal_set_fifo Failed(ret=%d)\n", ret);

	pch_मुक्त_dma(port);

	मुक्त_irq(priv->port.irq, priv);
पूर्ण

/* Change the port parameters, including word length, parity, stop
 *bits.  Update पढ़ो_status_mask and ignore_status_mask to indicate
 *the types of events we are पूर्णांकerested in receiving.  */
अटल व्योम pch_uart_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	पूर्णांक rtn;
	अचिन्हित पूर्णांक baud, parity, bits, stb;
	काष्ठा eg20t_port *priv;
	अचिन्हित दीर्घ flags;

	priv = container_of(port, काष्ठा eg20t_port, port);
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		bits = PCH_UART_HAL_5BIT;
		अवरोध;
	हाल CS6:
		bits = PCH_UART_HAL_6BIT;
		अवरोध;
	हाल CS7:
		bits = PCH_UART_HAL_7BIT;
		अवरोध;
	शेष:		/* CS8 */
		bits = PCH_UART_HAL_8BIT;
		अवरोध;
	पूर्ण
	अगर (termios->c_cflag & CSTOPB)
		stb = PCH_UART_HAL_STB2;
	अन्यथा
		stb = PCH_UART_HAL_STB1;

	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & PARODD)
			parity = PCH_UART_HAL_PARITY_ODD;
		अन्यथा
			parity = PCH_UART_HAL_PARITY_EVEN;

	पूर्ण अन्यथा
		parity = PCH_UART_HAL_PARITY_NONE;

	/* Only UART0 has स्वतः hardware flow function */
	अगर ((termios->c_cflag & CRTSCTS) && (priv->fअगरo_size == 256))
		priv->mcr |= UART_MCR_AFE;
	अन्यथा
		priv->mcr &= ~UART_MCR_AFE;

	termios->c_cflag &= ~CMSPAR; /* Mark/Space parity is not supported */

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);

	spin_lock_irqsave(&priv->lock, flags);
	spin_lock(&port->lock);

	uart_update_समयout(port, termios->c_cflag, baud);
	rtn = pch_uart_hal_set_line(priv, baud, parity, bits, stb);
	अगर (rtn)
		जाओ out;

	pch_uart_set_mctrl(&priv->port, priv->port.mctrl);
	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

out:
	spin_unlock(&port->lock);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल स्थिर अक्षर *pch_uart_type(काष्ठा uart_port *port)
अणु
	वापस KBUILD_MODNAME;
पूर्ण

अटल व्योम pch_uart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;

	priv = container_of(port, काष्ठा eg20t_port, port);
	pci_iounmap(priv->pdev, priv->membase);
	pci_release_regions(priv->pdev);
पूर्ण

अटल पूर्णांक pch_uart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv;
	पूर्णांक ret;
	व्योम __iomem *membase;

	priv = container_of(port, काष्ठा eg20t_port, port);
	ret = pci_request_regions(priv->pdev, KBUILD_MODNAME);
	अगर (ret < 0)
		वापस -EBUSY;

	membase = pci_iomap(priv->pdev, 1, 0);
	अगर (!membase) अणु
		pci_release_regions(priv->pdev);
		वापस -EBUSY;
	पूर्ण
	priv->membase = port->membase = membase;

	वापस 0;
पूर्ण

अटल व्योम pch_uart_config_port(काष्ठा uart_port *port, पूर्णांक type)
अणु
	काष्ठा eg20t_port *priv;

	priv = container_of(port, काष्ठा eg20t_port, port);
	अगर (type & UART_CONFIG_TYPE) अणु
		port->type = priv->port_type;
		pch_uart_request_port(port);
	पूर्ण
पूर्ण

अटल पूर्णांक pch_uart_verअगरy_port(काष्ठा uart_port *port,
				काष्ठा serial_काष्ठा *serinfo)
अणु
	काष्ठा eg20t_port *priv;

	priv = container_of(port, काष्ठा eg20t_port, port);
	अगर (serinfo->flags & UPF_LOW_LATENCY) अणु
		dev_info(priv->port.dev,
			"PCH UART : Use PIO Mode (without DMA)\n");
		priv->use_dma = 0;
		serinfo->flags &= ~UPF_LOW_LATENCY;
	पूर्ण अन्यथा अणु
#अगर_अघोषित CONFIG_PCH_DMA
		dev_err(priv->port.dev, "%s : PCH DMA is not Loaded.\n",
			__func__);
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
		अगर (!priv->use_dma) अणु
			pch_request_dma(port);
			अगर (priv->chan_rx)
				priv->use_dma = 1;
		पूर्ण
		dev_info(priv->port.dev, "PCH UART: %s\n",
				priv->use_dma ?
				"Use DMA Mode" : "No DMA");
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_CONSOLE_POLL) || defined(CONFIG_SERIAL_PCH_UART_CONSOLE)
/*
 *	Wait क्रम transmitter & holding रेजिस्टर to empty
 */
अटल व्योम रुको_क्रम_xmitr(काष्ठा eg20t_port *up, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	क्रम (;;) अणु
		status = ioपढ़ो8(up->membase + UART_LSR);

		अगर ((status & bits) == bits)
			अवरोध;
		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
	पूर्ण

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		अचिन्हित पूर्णांक पंचांगout;
		क्रम (पंचांगout = 1000000; पंचांगout; पंचांगout--) अणु
			अचिन्हित पूर्णांक msr = ioपढ़ो8(up->membase + UART_MSR);
			अगर (msr & UART_MSR_CTS)
				अवरोध;
			udelay(1);
			touch_nmi_watchकरोg();
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL || CONFIG_SERIAL_PCH_UART_CONSOLE */

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम communicate via uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */
अटल पूर्णांक pch_uart_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा eg20t_port *priv =
		container_of(port, काष्ठा eg20t_port, port);
	u8 lsr = ioपढ़ो8(priv->membase + UART_LSR);

	अगर (!(lsr & UART_LSR_DR))
		वापस NO_POLL_CHAR;

	वापस ioपढ़ो8(priv->membase + PCH_UART_RBR);
पूर्ण


अटल व्योम pch_uart_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक ier;
	काष्ठा eg20t_port *priv =
		container_of(port, काष्ठा eg20t_port, port);

	/*
	 * First save the IER then disable the पूर्णांकerrupts
	 */
	ier = ioपढ़ो8(priv->membase + UART_IER);
	pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_ALL_INT);

	रुको_क्रम_xmitr(priv, UART_LSR_THRE);
	/*
	 * Send the अक्षरacter out.
	 */
	ioग_लिखो8(c, priv->membase + PCH_UART_THR);

	/*
	 * Finally, रुको क्रम transmitter to become empty
	 * and restore the IER
	 */
	रुको_क्रम_xmitr(priv, BOTH_EMPTY);
	ioग_लिखो8(ier, priv->membase + UART_IER);
पूर्ण
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल स्थिर काष्ठा uart_ops pch_uart_ops = अणु
	.tx_empty = pch_uart_tx_empty,
	.set_mctrl = pch_uart_set_mctrl,
	.get_mctrl = pch_uart_get_mctrl,
	.stop_tx = pch_uart_stop_tx,
	.start_tx = pch_uart_start_tx,
	.stop_rx = pch_uart_stop_rx,
	.enable_ms = pch_uart_enable_ms,
	.अवरोध_ctl = pch_uart_अवरोध_ctl,
	.startup = pch_uart_startup,
	.shutकरोwn = pch_uart_shutकरोwn,
	.set_termios = pch_uart_set_termios,
/*	.pm		= pch_uart_pm,		Not supported yet */
	.type = pch_uart_type,
	.release_port = pch_uart_release_port,
	.request_port = pch_uart_request_port,
	.config_port = pch_uart_config_port,
	.verअगरy_port = pch_uart_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर = pch_uart_get_poll_अक्षर,
	.poll_put_अक्षर = pch_uart_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_PCH_UART_CONSOLE

अटल व्योम pch_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा eg20t_port *priv =
		container_of(port, काष्ठा eg20t_port, port);

	रुको_क्रम_xmitr(priv, UART_LSR_THRE);
	ioग_लिखो8(ch, priv->membase + PCH_UART_THR);
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 *
 *	The console_lock must be held when we get here.
 */
अटल व्योम
pch_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा eg20t_port *priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक priv_locked = 1;
	पूर्णांक port_locked = 1;
	u8 ier;

	priv = pch_uart_ports[co->index];

	touch_nmi_watchकरोg();

	local_irq_save(flags);
	अगर (priv->port.sysrq) अणु
		/* call to uart_handle_sysrq_अक्षर alपढ़ोy took the priv lock */
		priv_locked = 0;
		/* serial8250_handle_port() alपढ़ोy took the port lock */
		port_locked = 0;
	पूर्ण अन्यथा अगर (oops_in_progress) अणु
		priv_locked = spin_trylock(&priv->lock);
		port_locked = spin_trylock(&priv->port.lock);
	पूर्ण अन्यथा अणु
		spin_lock(&priv->lock);
		spin_lock(&priv->port.lock);
	पूर्ण

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = ioपढ़ो8(priv->membase + UART_IER);

	pch_uart_hal_disable_पूर्णांकerrupt(priv, PCH_UART_HAL_ALL_INT);

	uart_console_ग_लिखो(&priv->port, s, count, pch_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(priv, BOTH_EMPTY);
	ioग_लिखो8(ier, priv->membase + UART_IER);

	अगर (port_locked)
		spin_unlock(&priv->port.lock);
	अगर (priv_locked)
		spin_unlock(&priv->lock);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __init pch_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = शेष_baud;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= PCH_UART_NR)
		co->index = 0;
	port = &pch_uart_ports[co->index]->port;

	अगर (!port || (!port->iobase && !port->membase))
		वापस -ENODEV;

	port->uartclk = pch_uart_get_uartclk();

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver pch_uart_driver;

अटल काष्ठा console pch_console = अणु
	.name		= PCH_UART_DRIVER_DEVICE,
	.ग_लिखो		= pch_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= pch_console_setup,
	.flags		= CON_PRINTBUFFER | CON_ANYTIME,
	.index		= -1,
	.data		= &pch_uart_driver,
पूर्ण;

#घोषणा PCH_CONSOLE	(&pch_console)
#अन्यथा
#घोषणा PCH_CONSOLE	शून्य
#पूर्ण_अगर	/* CONFIG_SERIAL_PCH_UART_CONSOLE */

अटल काष्ठा uart_driver pch_uart_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = KBUILD_MODNAME,
	.dev_name = PCH_UART_DRIVER_DEVICE,
	.major = 0,
	.minor = 0,
	.nr = PCH_UART_NR,
	.cons = PCH_CONSOLE,
पूर्ण;

अटल काष्ठा eg20t_port *pch_uart_init_port(काष्ठा pci_dev *pdev,
					     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा eg20t_port *priv;
	पूर्णांक ret;
	अचिन्हित पूर्णांक iobase;
	अचिन्हित पूर्णांक mapbase;
	अचिन्हित अक्षर *rxbuf;
	पूर्णांक fअगरosize;
	पूर्णांक port_type;
	काष्ठा pch_uart_driver_data *board;
	अक्षर name[32];

	board = &drv_dat[id->driver_data];
	port_type = board->port_type;

	priv = kzalloc(माप(काष्ठा eg20t_port), GFP_KERNEL);
	अगर (priv == शून्य)
		जाओ init_port_alloc_err;

	rxbuf = (अचिन्हित अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!rxbuf)
		जाओ init_port_मुक्त_txbuf;

	चयन (port_type) अणु
	हाल PORT_PCH_8LINE:
		fअगरosize = 256; /* EG20T/ML7213: UART0 */
		अवरोध;
	हाल PORT_PCH_2LINE:
		fअगरosize = 64; /* EG20T:UART1~3  ML7213: UART1~2*/
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid Port Type(=%d)\n", port_type);
		जाओ init_port_hal_मुक्त;
	पूर्ण

	pci_enable_msi(pdev);
	pci_set_master(pdev);

	spin_lock_init(&priv->lock);

	iobase = pci_resource_start(pdev, 0);
	mapbase = pci_resource_start(pdev, 1);
	priv->mapbase = mapbase;
	priv->iobase = iobase;
	priv->pdev = pdev;
	priv->tx_empty = 1;
	priv->rxbuf.buf = rxbuf;
	priv->rxbuf.size = PAGE_SIZE;

	priv->fअगरo_size = fअगरosize;
	priv->uartclk = pch_uart_get_uartclk();
	priv->port_type = port_type;
	priv->port.dev = &pdev->dev;
	priv->port.iobase = iobase;
	priv->port.membase = शून्य;
	priv->port.mapbase = mapbase;
	priv->port.irq = pdev->irq;
	priv->port.iotype = UPIO_PORT;
	priv->port.ops = &pch_uart_ops;
	priv->port.flags = UPF_BOOT_AUTOCONF;
	priv->port.fअगरosize = fअगरosize;
	priv->port.line = board->line_no;
	priv->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_PCH_UART_CONSOLE);
	priv->trigger = PCH_UART_HAL_TRIGGER_M;

	snम_लिखो(priv->irq_name, IRQ_NAME_SIZE,
		 KBUILD_MODNAME ":" PCH_UART_DRIVER_DEVICE "%d",
		 priv->port.line);

	spin_lock_init(&priv->port.lock);

	pci_set_drvdata(pdev, priv);
	priv->trigger_level = 1;
	priv->fcr = 0;

	अगर (pdev->dev.of_node)
		of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency"
					 , &user_uartclk);

#अगर_घोषित CONFIG_SERIAL_PCH_UART_CONSOLE
	pch_uart_ports[board->line_no] = priv;
#पूर्ण_अगर
	ret = uart_add_one_port(&pch_uart_driver, &priv->port);
	अगर (ret < 0)
		जाओ init_port_hal_मुक्त;

	snम_लिखो(name, माप(name), "uart%d_regs", priv->port.line);
	debugfs_create_file(name, S_IFREG | S_IRUGO, शून्य, priv,
			    &port_regs_ops);

	वापस priv;

init_port_hal_मुक्त:
#अगर_घोषित CONFIG_SERIAL_PCH_UART_CONSOLE
	pch_uart_ports[board->line_no] = शून्य;
#पूर्ण_अगर
	मुक्त_page((अचिन्हित दीर्घ)rxbuf);
init_port_मुक्त_txbuf:
	kमुक्त(priv);
init_port_alloc_err:

	वापस शून्य;
पूर्ण

अटल व्योम pch_uart_निकास_port(काष्ठा eg20t_port *priv)
अणु
	अक्षर name[32];

	snम_लिखो(name, माप(name), "uart%d_regs", priv->port.line);
	debugfs_हटाओ(debugfs_lookup(name, शून्य));
	uart_हटाओ_one_port(&pch_uart_driver, &priv->port);
	मुक्त_page((अचिन्हित दीर्घ)priv->rxbuf.buf);
पूर्ण

अटल व्योम pch_uart_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eg20t_port *priv = pci_get_drvdata(pdev);

	pci_disable_msi(pdev);

#अगर_घोषित CONFIG_SERIAL_PCH_UART_CONSOLE
	pch_uart_ports[priv->port.line] = शून्य;
#पूर्ण_अगर
	pch_uart_निकास_port(priv);
	pci_disable_device(pdev);
	kमुक्त(priv);
	वापस;
पूर्ण

अटल पूर्णांक __maybe_unused pch_uart_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा eg20t_port *priv = dev_get_drvdata(dev);

	uart_suspend_port(&pch_uart_driver, &priv->port);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_uart_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा eg20t_port *priv = dev_get_drvdata(dev);

	uart_resume_port(&pch_uart_driver, &priv->port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id pch_uart_pci_id[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8811),
	 .driver_data = pch_et20t_uart0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8812),
	 .driver_data = pch_et20t_uart1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8813),
	 .driver_data = pch_et20t_uart2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8814),
	 .driver_data = pch_et20t_uart3पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8027),
	 .driver_data = pch_ml7213_uart0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8028),
	 .driver_data = pch_ml7213_uart1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8029),
	 .driver_data = pch_ml7213_uart2पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x800C),
	 .driver_data = pch_ml7223_uart0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x800D),
	 .driver_data = pch_ml7223_uart1पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8811),
	 .driver_data = pch_ml7831_uart0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8812),
	 .driver_data = pch_ml7831_uart1पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

अटल पूर्णांक pch_uart_pci_probe(काष्ठा pci_dev *pdev,
					स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा eg20t_port *priv;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		जाओ probe_error;

	priv = pch_uart_init_port(pdev, id);
	अगर (!priv) अणु
		ret = -EBUSY;
		जाओ probe_disable_device;
	पूर्ण
	pci_set_drvdata(pdev, priv);

	वापस ret;

probe_disable_device:
	pci_disable_msi(pdev);
	pci_disable_device(pdev);
probe_error:
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_uart_pci_pm_ops,
			 pch_uart_pci_suspend,
			 pch_uart_pci_resume);

अटल काष्ठा pci_driver pch_uart_pci_driver = अणु
	.name = "pch_uart",
	.id_table = pch_uart_pci_id,
	.probe = pch_uart_pci_probe,
	.हटाओ = pch_uart_pci_हटाओ,
	.driver.pm = &pch_uart_pci_pm_ops,
पूर्ण;

अटल पूर्णांक __init pch_uart_module_init(व्योम)
अणु
	पूर्णांक ret;

	/* रेजिस्टर as UART driver */
	ret = uart_रेजिस्टर_driver(&pch_uart_driver);
	अगर (ret < 0)
		वापस ret;

	/* रेजिस्टर as PCI driver */
	ret = pci_रेजिस्टर_driver(&pch_uart_pci_driver);
	अगर (ret < 0)
		uart_unरेजिस्टर_driver(&pch_uart_driver);

	वापस ret;
पूर्ण
module_init(pch_uart_module_init);

अटल व्योम __निकास pch_uart_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pch_uart_pci_driver);
	uart_unरेजिस्टर_driver(&pch_uart_driver);
पूर्ण
module_निकास(pch_uart_module_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel EG20T PCH UART PCI Driver");
MODULE_DEVICE_TABLE(pci, pch_uart_pci_id);

module_param(शेष_baud, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(शेष_baud,
                 "Default BAUD for initial driver state and console (default 9600)");
module_param(user_uartclk, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(user_uartclk,
                 "Override UART default or board specific UART clock");
