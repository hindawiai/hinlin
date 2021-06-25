<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 8250_lpss.c - Driver क्रम UART on Intel Braswell and various other Intel SoCs
 *
 * Copyright (C) 2016 Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/rational.h>

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/dw.h>

#समावेश "8250_dwlib.h"

#घोषणा PCI_DEVICE_ID_INTEL_QRK_UARTx	0x0936

#घोषणा PCI_DEVICE_ID_INTEL_BYT_UART1	0x0f0a
#घोषणा PCI_DEVICE_ID_INTEL_BYT_UART2	0x0f0c

#घोषणा PCI_DEVICE_ID_INTEL_BSW_UART1	0x228a
#घोषणा PCI_DEVICE_ID_INTEL_BSW_UART2	0x228c

#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART0	0x4b96
#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART1	0x4b97
#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART2	0x4b98
#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART3	0x4b99
#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART4	0x4b9a
#घोषणा PCI_DEVICE_ID_INTEL_EHL_UART5	0x4b9b

#घोषणा PCI_DEVICE_ID_INTEL_BDW_UART1	0x9ce3
#घोषणा PCI_DEVICE_ID_INTEL_BDW_UART2	0x9ce4

/* Intel LPSS specअगरic रेजिस्टरs */

#घोषणा BYT_PRV_CLK			0x800
#घोषणा BYT_PRV_CLK_EN			BIT(0)
#घोषणा BYT_PRV_CLK_M_VAL_SHIFT		1
#घोषणा BYT_PRV_CLK_N_VAL_SHIFT		16
#घोषणा BYT_PRV_CLK_UPDATE		BIT(31)

#घोषणा BYT_TX_OVF_INT			0x820
#घोषणा BYT_TX_OVF_INT_MASK		BIT(1)

काष्ठा lpss8250;

काष्ठा lpss8250_board अणु
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक base_baud;
	पूर्णांक (*setup)(काष्ठा lpss8250 *, काष्ठा uart_port *p);
	व्योम (*निकास)(काष्ठा lpss8250 *);
पूर्ण;

काष्ठा lpss8250 अणु
	काष्ठा dw8250_port_data data;
	काष्ठा lpss8250_board *board;

	/* DMA parameters */
	काष्ठा dw_dma_chip dma_chip;
	काष्ठा dw_dma_slave dma_param;
	u8 dma_maxburst;
पूर्ण;

अटल अंतरभूत काष्ठा lpss8250 *to_lpss8250(काष्ठा dw8250_port_data *data)
अणु
	वापस container_of(data, काष्ठा lpss8250, data);
पूर्ण

अटल व्योम byt_set_termios(काष्ठा uart_port *p, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud = tty_termios_baud_rate(termios);
	काष्ठा lpss8250 *lpss = to_lpss8250(p->निजी_data);
	अचिन्हित दीर्घ fref = lpss->board->freq, fuart = baud * 16;
	अचिन्हित दीर्घ w = BIT(15) - 1;
	अचिन्हित दीर्घ m, n;
	u32 reg;

	/* Gracefully handle the B0 हाल: fall back to B9600 */
	fuart = fuart ? fuart : 9600 * 16;

	/* Get Fuart बंदr to Fref */
	fuart *= roundकरोwn_घात_of_two(fref / fuart);

	/*
	 * For baud rates 0.5M, 1M, 1.5M, 2M, 2.5M, 3M, 3.5M and 4M the
	 * भागiders must be adjusted.
	 *
	 * uartclk = (m / n) * 100 MHz, where m <= n
	 */
	rational_best_approximation(fuart, fref, w, w, &m, &n);
	p->uartclk = fuart;

	/* Reset the घड़ी */
	reg = (m << BYT_PRV_CLK_M_VAL_SHIFT) | (n << BYT_PRV_CLK_N_VAL_SHIFT);
	ग_लिखोl(reg, p->membase + BYT_PRV_CLK);
	reg |= BYT_PRV_CLK_EN | BYT_PRV_CLK_UPDATE;
	ग_लिखोl(reg, p->membase + BYT_PRV_CLK);

	p->status &= ~UPSTAT_AUTOCTS;
	अगर (termios->c_cflag & CRTSCTS)
		p->status |= UPSTAT_AUTOCTS;

	serial8250_करो_set_termios(p, termios, old);
पूर्ण

अटल अचिन्हित पूर्णांक byt_get_mctrl(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ret = serial8250_करो_get_mctrl(port);

	/* Force DCD and DSR संकेतs to permanently be reported as active */
	ret |= TIOCM_CAR | TIOCM_DSR;

	वापस ret;
पूर्ण

अटल पूर्णांक byt_serial_setup(काष्ठा lpss8250 *lpss, काष्ठा uart_port *port)
अणु
	काष्ठा dw_dma_slave *param = &lpss->dma_param;
	काष्ठा pci_dev *pdev = to_pci_dev(port->dev);
	अचिन्हित पूर्णांक dma_devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	काष्ठा pci_dev *dma_dev = pci_get_slot(pdev->bus, dma_devfn);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_BYT_UART1:
	हाल PCI_DEVICE_ID_INTEL_BSW_UART1:
	हाल PCI_DEVICE_ID_INTEL_BDW_UART1:
		param->src_id = 3;
		param->dst_id = 2;
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_BYT_UART2:
	हाल PCI_DEVICE_ID_INTEL_BSW_UART2:
	हाल PCI_DEVICE_ID_INTEL_BDW_UART2:
		param->src_id = 5;
		param->dst_id = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	param->dma_dev = &dma_dev->dev;
	param->m_master = 0;
	param->p_master = 1;

	lpss->dma_maxburst = 16;

	port->set_termios = byt_set_termios;
	port->get_mctrl = byt_get_mctrl;

	/* Disable TX counter पूर्णांकerrupts */
	ग_लिखोl(BYT_TX_OVF_INT_MASK, port->membase + BYT_TX_OVF_INT);

	वापस 0;
पूर्ण

अटल पूर्णांक ehl_serial_setup(काष्ठा lpss8250 *lpss, काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_DMA
अटल स्थिर काष्ठा dw_dma_platक्रमm_data qrk_serial_dma_pdata = अणु
	.nr_channels = 2,
	.chan_allocation_order = CHAN_ALLOCATION_ASCENDING,
	.chan_priority = CHAN_PRIORITY_ASCENDING,
	.block_size = 4095,
	.nr_masters = 1,
	.data_width = अणु4पूर्ण,
	.multi_block = अणु0पूर्ण,
पूर्ण;

अटल व्योम qrk_serial_setup_dma(काष्ठा lpss8250 *lpss, काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_dma *dma = &lpss->data.dma;
	काष्ठा dw_dma_chip *chip = &lpss->dma_chip;
	काष्ठा dw_dma_slave *param = &lpss->dma_param;
	काष्ठा pci_dev *pdev = to_pci_dev(port->dev);
	पूर्णांक ret;

	chip->pdata = &qrk_serial_dma_pdata;
	chip->dev = &pdev->dev;
	chip->id = pdev->devfn;
	chip->irq = pci_irq_vector(pdev, 0);
	chip->regs = pci_ioremap_bar(pdev, 1);
	अगर (!chip->regs)
		वापस;

	/* Falling back to PIO mode अगर DMA probing fails */
	ret = dw_dma_probe(chip);
	अगर (ret)
		वापस;

	pci_try_set_mwi(pdev);

	/* Special DMA address क्रम UART */
	dma->rx_dma_addr = 0xfffff000;
	dma->tx_dma_addr = 0xfffff000;

	param->dma_dev = &pdev->dev;
	param->src_id = 0;
	param->dst_id = 1;
	param->hs_polarity = true;

	lpss->dma_maxburst = 8;
पूर्ण

अटल व्योम qrk_serial_निकास_dma(काष्ठा lpss8250 *lpss)
अणु
	काष्ठा dw_dma_chip *chip = &lpss->dma_chip;
	काष्ठा dw_dma_slave *param = &lpss->dma_param;

	अगर (!param->dma_dev)
		वापस;

	dw_dma_हटाओ(chip);

	pci_iounmap(to_pci_dev(chip->dev), chip->regs);
पूर्ण
#अन्यथा	/* CONFIG_SERIAL_8250_DMA */
अटल व्योम qrk_serial_setup_dma(काष्ठा lpss8250 *lpss, काष्ठा uart_port *port) अणुपूर्ण
अटल व्योम qrk_serial_निकास_dma(काष्ठा lpss8250 *lpss) अणुपूर्ण
#पूर्ण_अगर	/* !CONFIG_SERIAL_8250_DMA */

अटल पूर्णांक qrk_serial_setup(काष्ठा lpss8250 *lpss, काष्ठा uart_port *port)
अणु
	qrk_serial_setup_dma(lpss, port);
	वापस 0;
पूर्ण

अटल व्योम qrk_serial_निकास(काष्ठा lpss8250 *lpss)
अणु
	qrk_serial_निकास_dma(lpss);
पूर्ण

अटल bool lpss8250_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा dw_dma_slave *dws = param;

	अगर (dws->dma_dev != chan->device->dev)
		वापस false;

	chan->निजी = dws;
	वापस true;
पूर्ण

अटल पूर्णांक lpss8250_dma_setup(काष्ठा lpss8250 *lpss, काष्ठा uart_8250_port *port)
अणु
	काष्ठा uart_8250_dma *dma = &lpss->data.dma;
	काष्ठा dw_dma_slave *rx_param, *tx_param;
	काष्ठा device *dev = port->port.dev;

	अगर (!lpss->dma_param.dma_dev)
		वापस 0;

	rx_param = devm_kzalloc(dev, माप(*rx_param), GFP_KERNEL);
	अगर (!rx_param)
		वापस -ENOMEM;

	tx_param = devm_kzalloc(dev, माप(*tx_param), GFP_KERNEL);
	अगर (!tx_param)
		वापस -ENOMEM;

	*rx_param = lpss->dma_param;
	dma->rxconf.src_maxburst = lpss->dma_maxburst;

	*tx_param = lpss->dma_param;
	dma->txconf.dst_maxburst = lpss->dma_maxburst;

	dma->fn = lpss8250_dma_filter;
	dma->rx_param = rx_param;
	dma->tx_param = tx_param;

	port->dma = dma;
	वापस 0;
पूर्ण

अटल पूर्णांक lpss8250_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uart_8250_port uart;
	काष्ठा lpss8250 *lpss;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	lpss = devm_kzalloc(&pdev->dev, माप(*lpss), GFP_KERNEL);
	अगर (!lpss)
		वापस -ENOMEM;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	lpss->board = (काष्ठा lpss8250_board *)id->driver_data;

	स_रखो(&uart, 0, माप(काष्ठा uart_8250_port));

	uart.port.dev = &pdev->dev;
	uart.port.irq = pci_irq_vector(pdev, 0);
	uart.port.निजी_data = &lpss->data;
	uart.port.type = PORT_16550A;
	uart.port.iotype = UPIO_MEM;
	uart.port.regshअगरt = 2;
	uart.port.uartclk = lpss->board->base_baud * 16;
	uart.port.flags = UPF_SHARE_IRQ | UPF_FIXED_PORT | UPF_FIXED_TYPE;
	uart.capabilities = UART_CAP_FIFO | UART_CAP_AFE;
	uart.port.mapbase = pci_resource_start(pdev, 0);
	uart.port.membase = pcim_iomap(pdev, 0, 0);
	अगर (!uart.port.membase)
		वापस -ENOMEM;

	ret = lpss->board->setup(lpss, &uart.port);
	अगर (ret)
		वापस ret;

	dw8250_setup_port(&uart.port);

	ret = lpss8250_dma_setup(lpss, &uart);
	अगर (ret)
		जाओ err_निकास;

	ret = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (ret < 0)
		जाओ err_निकास;

	lpss->data.line = ret;

	pci_set_drvdata(pdev, lpss);
	वापस 0;

err_निकास:
	अगर (lpss->board->निकास)
		lpss->board->निकास(lpss);
	pci_मुक्त_irq_vectors(pdev);
	वापस ret;
पूर्ण

अटल व्योम lpss8250_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा lpss8250 *lpss = pci_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(lpss->data.line);

	अगर (lpss->board->निकास)
		lpss->board->निकास(lpss);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल स्थिर काष्ठा lpss8250_board byt_board = अणु
	.freq = 100000000,
	.base_baud = 2764800,
	.setup = byt_serial_setup,
पूर्ण;

अटल स्थिर काष्ठा lpss8250_board ehl_board = अणु
	.freq = 200000000,
	.base_baud = 12500000,
	.setup = ehl_serial_setup,
पूर्ण;

अटल स्थिर काष्ठा lpss8250_board qrk_board = अणु
	.freq = 44236800,
	.base_baud = 2764800,
	.setup = qrk_serial_setup,
	.निकास = qrk_serial_निकास,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, QRK_UARTx, &qrk_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART0, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART1, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART2, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART3, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART4, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, EHL_UART5, &ehl_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BYT_UART1, &byt_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BYT_UART2, &byt_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BSW_UART1, &byt_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BSW_UART2, &byt_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BDW_UART1, &byt_board) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BDW_UART2, &byt_board) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

अटल काष्ठा pci_driver lpss8250_pci_driver = अणु
	.name           = "8250_lpss",
	.id_table       = pci_ids,
	.probe          = lpss8250_probe,
	.हटाओ         = lpss8250_हटाओ,
पूर्ण;

module_pci_driver(lpss8250_pci_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel LPSS UART driver");
