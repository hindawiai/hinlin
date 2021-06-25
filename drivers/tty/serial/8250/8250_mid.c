<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 8250_mid.c - Driver क्रम UART on Intel Penwell and various other Intel SOCs
 *
 * Copyright (C) 2015 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/rational.h>

#समावेश <linux/dma/hsu.h>
#समावेश <linux/8250_pci.h>

#समावेश "8250.h"

#घोषणा PCI_DEVICE_ID_INTEL_PNW_UART1	0x081b
#घोषणा PCI_DEVICE_ID_INTEL_PNW_UART2	0x081c
#घोषणा PCI_DEVICE_ID_INTEL_PNW_UART3	0x081d
#घोषणा PCI_DEVICE_ID_INTEL_TNG_UART	0x1191
#घोषणा PCI_DEVICE_ID_INTEL_CDF_UART	0x18d8
#घोषणा PCI_DEVICE_ID_INTEL_DNV_UART	0x19d8

/* Intel MID Specअगरic रेजिस्टरs */
#घोषणा INTEL_MID_UART_FISR		0x08
#घोषणा INTEL_MID_UART_PS		0x30
#घोषणा INTEL_MID_UART_MUL		0x34
#घोषणा INTEL_MID_UART_DIV		0x38

काष्ठा mid8250;

काष्ठा mid8250_board अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक base_baud;
	पूर्णांक (*setup)(काष्ठा mid8250 *, काष्ठा uart_port *p);
	व्योम (*निकास)(काष्ठा mid8250 *);
पूर्ण;

काष्ठा mid8250 अणु
	पूर्णांक line;
	पूर्णांक dma_index;
	काष्ठा pci_dev *dma_dev;
	काष्ठा uart_8250_dma dma;
	काष्ठा mid8250_board *board;
	काष्ठा hsu_dma_chip dma_chip;
पूर्ण;

/*****************************************************************************/

अटल पूर्णांक pnw_setup(काष्ठा mid8250 *mid, काष्ठा uart_port *p)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(p->dev);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_PNW_UART1:
		mid->dma_index = 0;
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_PNW_UART2:
		mid->dma_index = 1;
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_PNW_UART3:
		mid->dma_index = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mid->dma_dev = pci_get_slot(pdev->bus,
				    PCI_DEVFN(PCI_SLOT(pdev->devfn), 3));
	वापस 0;
पूर्ण

अटल पूर्णांक tng_handle_irq(काष्ठा uart_port *p)
अणु
	काष्ठा mid8250 *mid = p->निजी_data;
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	काष्ठा hsu_dma_chip *chip;
	u32 status;
	पूर्णांक ret = 0;
	पूर्णांक err;

	chip = pci_get_drvdata(mid->dma_dev);

	/* Rx DMA */
	err = hsu_dma_get_status(chip, mid->dma_index * 2 + 1, &status);
	अगर (err > 0) अणु
		serial8250_rx_dma_flush(up);
		ret |= 1;
	पूर्ण अन्यथा अगर (err == 0)
		ret |= hsu_dma_करो_irq(chip, mid->dma_index * 2 + 1, status);

	/* Tx DMA */
	err = hsu_dma_get_status(chip, mid->dma_index * 2, &status);
	अगर (err > 0)
		ret |= 1;
	अन्यथा अगर (err == 0)
		ret |= hsu_dma_करो_irq(chip, mid->dma_index * 2, status);

	/* UART */
	ret |= serial8250_handle_irq(p, serial_port_in(p, UART_IIR));
	वापस IRQ_RETVAL(ret);
पूर्ण

अटल पूर्णांक tng_setup(काष्ठा mid8250 *mid, काष्ठा uart_port *p)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(p->dev);
	पूर्णांक index = PCI_FUNC(pdev->devfn);

	/*
	 * Device 0000:00:04.0 is not a real HSU port. It provides a global
	 * रेजिस्टर set क्रम all HSU ports, although it has the same PCI ID.
	 * Skip it here.
	 */
	अगर (index-- == 0)
		वापस -ENODEV;

	mid->dma_index = index;
	mid->dma_dev = pci_get_slot(pdev->bus, PCI_DEVFN(5, 0));

	p->handle_irq = tng_handle_irq;
	वापस 0;
पूर्ण

अटल पूर्णांक dnv_handle_irq(काष्ठा uart_port *p)
अणु
	काष्ठा mid8250 *mid = p->निजी_data;
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	अचिन्हित पूर्णांक fisr = serial_port_in(p, INTEL_MID_UART_FISR);
	u32 status;
	पूर्णांक ret = 0;
	पूर्णांक err;

	अगर (fisr & BIT(2)) अणु
		err = hsu_dma_get_status(&mid->dma_chip, 1, &status);
		अगर (err > 0) अणु
			serial8250_rx_dma_flush(up);
			ret |= 1;
		पूर्ण अन्यथा अगर (err == 0)
			ret |= hsu_dma_करो_irq(&mid->dma_chip, 1, status);
	पूर्ण
	अगर (fisr & BIT(1)) अणु
		err = hsu_dma_get_status(&mid->dma_chip, 0, &status);
		अगर (err > 0)
			ret |= 1;
		अन्यथा अगर (err == 0)
			ret |= hsu_dma_करो_irq(&mid->dma_chip, 0, status);
	पूर्ण
	अगर (fisr & BIT(0))
		ret |= serial8250_handle_irq(p, serial_port_in(p, UART_IIR));
	वापस IRQ_RETVAL(ret);
पूर्ण

#घोषणा DNV_DMA_CHAN_OFFSET 0x80

अटल पूर्णांक dnv_setup(काष्ठा mid8250 *mid, काष्ठा uart_port *p)
अणु
	काष्ठा hsu_dma_chip *chip = &mid->dma_chip;
	काष्ठा pci_dev *pdev = to_pci_dev(p->dev);
	अचिन्हित पूर्णांक bar = FL_GET_BASE(mid->board->flags);
	पूर्णांक ret;

	pci_set_master(pdev);

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	p->irq = pci_irq_vector(pdev, 0);

	chip->dev = &pdev->dev;
	chip->irq = pci_irq_vector(pdev, 0);
	chip->regs = p->membase;
	chip->length = pci_resource_len(pdev, bar);
	chip->offset = DNV_DMA_CHAN_OFFSET;

	/* Falling back to PIO mode अगर DMA probing fails */
	ret = hsu_dma_probe(chip);
	अगर (ret)
		वापस 0;

	mid->dma_dev = pdev;

	p->handle_irq = dnv_handle_irq;
	वापस 0;
पूर्ण

अटल व्योम dnv_निकास(काष्ठा mid8250 *mid)
अणु
	अगर (!mid->dma_dev)
		वापस;
	hsu_dma_हटाओ(&mid->dma_chip);
पूर्ण

/*****************************************************************************/

अटल व्योम mid8250_set_termios(काष्ठा uart_port *p,
				काष्ठा ktermios *termios,
				काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक baud = tty_termios_baud_rate(termios);
	काष्ठा mid8250 *mid = p->निजी_data;
	अचिन्हित लघु ps = 16;
	अचिन्हित दीर्घ fuart = baud * ps;
	अचिन्हित दीर्घ w = BIT(24) - 1;
	अचिन्हित दीर्घ mul, भाग;

	/* Gracefully handle the B0 हाल: fall back to B9600 */
	fuart = fuart ? fuart : 9600 * 16;

	अगर (mid->board->freq < fuart) अणु
		/* Find prescaler value that satisfies Fuart < Fref */
		अगर (mid->board->freq > baud)
			ps = mid->board->freq / baud;	/* baud rate too high */
		अन्यथा
			ps = 1;				/* PLL हाल */
		fuart = baud * ps;
	पूर्ण अन्यथा अणु
		/* Get Fuart बंदr to Fref */
		fuart *= roundकरोwn_घात_of_two(mid->board->freq / fuart);
	पूर्ण

	rational_best_approximation(fuart, mid->board->freq, w, w, &mul, &भाग);
	p->uartclk = fuart * 16 / ps;		/* core uses ps = 16 always */

	ग_लिखोl(ps, p->membase + INTEL_MID_UART_PS);		/* set PS */
	ग_लिखोl(mul, p->membase + INTEL_MID_UART_MUL);		/* set MUL */
	ग_लिखोl(भाग, p->membase + INTEL_MID_UART_DIV);

	serial8250_करो_set_termios(p, termios, old);
पूर्ण

अटल bool mid8250_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा hsu_dma_slave *s = param;

	अगर (s->dma_dev != chan->device->dev || s->chan_id != chan->chan_id)
		वापस false;

	chan->निजी = s;
	वापस true;
पूर्ण

अटल पूर्णांक mid8250_dma_setup(काष्ठा mid8250 *mid, काष्ठा uart_8250_port *port)
अणु
	काष्ठा uart_8250_dma *dma = &mid->dma;
	काष्ठा device *dev = port->port.dev;
	काष्ठा hsu_dma_slave *rx_param;
	काष्ठा hsu_dma_slave *tx_param;

	अगर (!mid->dma_dev)
		वापस 0;

	rx_param = devm_kzalloc(dev, माप(*rx_param), GFP_KERNEL);
	अगर (!rx_param)
		वापस -ENOMEM;

	tx_param = devm_kzalloc(dev, माप(*tx_param), GFP_KERNEL);
	अगर (!tx_param)
		वापस -ENOMEM;

	rx_param->chan_id = mid->dma_index * 2 + 1;
	tx_param->chan_id = mid->dma_index * 2;

	dma->rxconf.src_maxburst = 64;
	dma->txconf.dst_maxburst = 64;

	rx_param->dma_dev = &mid->dma_dev->dev;
	tx_param->dma_dev = &mid->dma_dev->dev;

	dma->fn = mid8250_dma_filter;
	dma->rx_param = rx_param;
	dma->tx_param = tx_param;

	port->dma = dma;
	वापस 0;
पूर्ण

अटल पूर्णांक mid8250_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uart_8250_port uart;
	काष्ठा mid8250 *mid;
	अचिन्हित पूर्णांक bar;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	mid = devm_kzalloc(&pdev->dev, माप(*mid), GFP_KERNEL);
	अगर (!mid)
		वापस -ENOMEM;

	mid->board = (काष्ठा mid8250_board *)id->driver_data;
	bar = FL_GET_BASE(mid->board->flags);

	स_रखो(&uart, 0, माप(काष्ठा uart_8250_port));

	uart.port.dev = &pdev->dev;
	uart.port.irq = pdev->irq;
	uart.port.निजी_data = mid;
	uart.port.type = PORT_16750;
	uart.port.iotype = UPIO_MEM;
	uart.port.uartclk = mid->board->base_baud * 16;
	uart.port.flags = UPF_SHARE_IRQ | UPF_FIXED_PORT | UPF_FIXED_TYPE;
	uart.port.set_termios = mid8250_set_termios;

	uart.port.mapbase = pci_resource_start(pdev, bar);
	uart.port.membase = pcim_iomap(pdev, bar, 0);
	अगर (!uart.port.membase)
		वापस -ENOMEM;

	अगर (mid->board->setup) अणु
		ret = mid->board->setup(mid, &uart.port);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mid8250_dma_setup(mid, &uart);
	अगर (ret)
		जाओ err;

	ret = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (ret < 0)
		जाओ err;

	mid->line = ret;

	pci_set_drvdata(pdev, mid);
	वापस 0;
err:
	अगर (mid->board->निकास)
		mid->board->निकास(mid);
	वापस ret;
पूर्ण

अटल व्योम mid8250_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mid8250 *mid = pci_get_drvdata(pdev);

	serial8250_unरेजिस्टर_port(mid->line);

	अगर (mid->board->निकास)
		mid->board->निकास(mid);
पूर्ण

अटल स्थिर काष्ठा mid8250_board pnw_board = अणु
	.flags = FL_BASE0,
	.freq = 50000000,
	.base_baud = 115200,
	.setup = pnw_setup,
पूर्ण;

अटल स्थिर काष्ठा mid8250_board tng_board = अणु
	.flags = FL_BASE0,
	.freq = 38400000,
	.base_baud = 1843200,
	.setup = tng_setup,
पूर्ण;

अटल स्थिर काष्ठा mid8250_board dnv_board = अणु
	.flags = FL_BASE1,
	.freq = 133333333,
	.base_baud = 115200,
	.setup = dnv_setup,
	.निकास = dnv_निकास,
पूर्ण;

#घोषणा MID_DEVICE(id, board) अणु PCI_VDEVICE(INTEL, id), (kernel_uदीर्घ_t)&board पूर्ण

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	MID_DEVICE(PCI_DEVICE_ID_INTEL_PNW_UART1, pnw_board),
	MID_DEVICE(PCI_DEVICE_ID_INTEL_PNW_UART2, pnw_board),
	MID_DEVICE(PCI_DEVICE_ID_INTEL_PNW_UART3, pnw_board),
	MID_DEVICE(PCI_DEVICE_ID_INTEL_TNG_UART, tng_board),
	MID_DEVICE(PCI_DEVICE_ID_INTEL_CDF_UART, dnv_board),
	MID_DEVICE(PCI_DEVICE_ID_INTEL_DNV_UART, dnv_board),
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

अटल काष्ठा pci_driver mid8250_pci_driver = अणु
	.name           = "8250_mid",
	.id_table       = pci_ids,
	.probe          = mid8250_probe,
	.हटाओ         = mid8250_हटाओ,
पूर्ण;

module_pci_driver(mid8250_pci_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel MID UART driver");
