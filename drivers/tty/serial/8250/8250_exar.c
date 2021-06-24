<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Probe module क्रम 8250/16550-type Exar chips PCI serial ports.
 *
 *  Based on drivers/tty/serial/8250/8250_pci.c,
 *
 *  Copyright (C) 2017 Sudip Mukherjee, All Rights Reserved.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/property.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/tty.h>
#समावेश <linux/8250_pci.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "8250.h"

#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_2S		0x1052
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_4S		0x105d
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_8S		0x106c
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM232_8		0x10a8
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_2SM		0x10d2
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_4SM		0x10db
#घोषणा PCI_DEVICE_ID_ACCESSIO_COM_8SM		0x10ea

#घोषणा PCI_DEVICE_ID_COMMTECH_4224PCI335	0x0002
#घोषणा PCI_DEVICE_ID_COMMTECH_4222PCI335	0x0004
#घोषणा PCI_DEVICE_ID_COMMTECH_2324PCI335	0x000a
#घोषणा PCI_DEVICE_ID_COMMTECH_2328PCI335	0x000b
#घोषणा PCI_DEVICE_ID_COMMTECH_4224PCIE		0x0020
#घोषणा PCI_DEVICE_ID_COMMTECH_4228PCIE		0x0021
#घोषणा PCI_DEVICE_ID_COMMTECH_4222PCIE		0x0022
#घोषणा PCI_DEVICE_ID_EXAR_XR17V4358		0x4358
#घोषणा PCI_DEVICE_ID_EXAR_XR17V8358		0x8358

#घोषणा UART_EXAR_INT0		0x80
#घोषणा UART_EXAR_8XMODE	0x88	/* 8X sampling rate select */
#घोषणा UART_EXAR_SLEEP		0x8b	/* Sleep mode */
#घोषणा UART_EXAR_DVID		0x8d	/* Device identअगरication */

#घोषणा UART_EXAR_FCTR		0x08	/* Feature Control Register */
#घोषणा UART_FCTR_EXAR_IRDA	0x10	/* IrDa data encode select */
#घोषणा UART_FCTR_EXAR_485	0x20	/* Auto 485 half duplex dir ctl */
#घोषणा UART_FCTR_EXAR_TRGA	0x00	/* FIFO trigger table A */
#घोषणा UART_FCTR_EXAR_TRGB	0x60	/* FIFO trigger table B */
#घोषणा UART_FCTR_EXAR_TRGC	0x80	/* FIFO trigger table C */
#घोषणा UART_FCTR_EXAR_TRGD	0xc0	/* FIFO trigger table D programmable */

#घोषणा UART_EXAR_TXTRG		0x0a	/* Tx FIFO trigger level ग_लिखो-only */
#घोषणा UART_EXAR_RXTRG		0x0b	/* Rx FIFO trigger level ग_लिखो-only */

#घोषणा UART_EXAR_MPIOINT_7_0	0x8f	/* MPIOINT[7:0] */
#घोषणा UART_EXAR_MPIOLVL_7_0	0x90	/* MPIOLVL[7:0] */
#घोषणा UART_EXAR_MPIO3T_7_0	0x91	/* MPIO3T[7:0] */
#घोषणा UART_EXAR_MPIOINV_7_0	0x92	/* MPIOINV[7:0] */
#घोषणा UART_EXAR_MPIOSEL_7_0	0x93	/* MPIOSEL[7:0] */
#घोषणा UART_EXAR_MPIOOD_7_0	0x94	/* MPIOOD[7:0] */
#घोषणा UART_EXAR_MPIOINT_15_8	0x95	/* MPIOINT[15:8] */
#घोषणा UART_EXAR_MPIOLVL_15_8	0x96	/* MPIOLVL[15:8] */
#घोषणा UART_EXAR_MPIO3T_15_8	0x97	/* MPIO3T[15:8] */
#घोषणा UART_EXAR_MPIOINV_15_8	0x98	/* MPIOINV[15:8] */
#घोषणा UART_EXAR_MPIOSEL_15_8	0x99	/* MPIOSEL[15:8] */
#घोषणा UART_EXAR_MPIOOD_15_8	0x9a	/* MPIOOD[15:8] */

#घोषणा UART_EXAR_RS485_DLY(x)	((x) << 4)

/*
 * IOT2040 MPIO wiring semantics:
 *
 * MPIO		Port	Function
 * ----		----	--------
 * 0		2 	Mode bit 0
 * 1		2	Mode bit 1
 * 2		2	Terminate bus
 * 3		-	<reserved>
 * 4		3	Mode bit 0
 * 5		3	Mode bit 1
 * 6		3	Terminate bus
 * 7		-	<reserved>
 * 8		2	Enable
 * 9		3	Enable
 * 10		-	Red LED
 * 11..15	-	<unused>
 */

/* IOT2040 MPIOs 0..7 */
#घोषणा IOT2040_UART_MODE_RS232		0x01
#घोषणा IOT2040_UART_MODE_RS485		0x02
#घोषणा IOT2040_UART_MODE_RS422		0x03
#घोषणा IOT2040_UART_TERMINATE_BUS	0x04

#घोषणा IOT2040_UART1_MASK		0x0f
#घोषणा IOT2040_UART2_SHIFT		4

#घोषणा IOT2040_UARTS_DEFAULT_MODE	0x11	/* both RS232 */
#घोषणा IOT2040_UARTS_GPIO_LO_MODE	0x88	/* reserved pins as input */

/* IOT2040 MPIOs 8..15 */
#घोषणा IOT2040_UARTS_ENABLE		0x03
#घोषणा IOT2040_UARTS_GPIO_HI_MODE	0xF8	/* enable & LED as outमाला_दो */

काष्ठा exar8250;

काष्ठा exar8250_platक्रमm अणु
	पूर्णांक (*rs485_config)(काष्ठा uart_port *, काष्ठा serial_rs485 *);
	पूर्णांक (*रेजिस्टर_gpio)(काष्ठा pci_dev *, काष्ठा uart_8250_port *);
पूर्ण;

/**
 * काष्ठा exar8250_board - board inक्रमmation
 * @num_ports: number of serial ports
 * @reg_shअगरt: describes UART रेजिस्टर mapping in PCI memory
 * @setup: quirk run at ->probe() stage
 * @निकास: quirk run at ->हटाओ() stage
 */
काष्ठा exar8250_board अणु
	अचिन्हित पूर्णांक num_ports;
	अचिन्हित पूर्णांक reg_shअगरt;
	पूर्णांक	(*setup)(काष्ठा exar8250 *, काष्ठा pci_dev *,
			 काष्ठा uart_8250_port *, पूर्णांक);
	व्योम	(*निकास)(काष्ठा pci_dev *pcidev);
पूर्ण;

काष्ठा exar8250 अणु
	अचिन्हित पूर्णांक		nr;
	काष्ठा exar8250_board	*board;
	व्योम __iomem		*virt;
	पूर्णांक			line[];
पूर्ण;

अटल व्योम exar_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक old)
अणु
	/*
	 * Exar UARTs have a SLEEP रेजिस्टर that enables or disables each UART
	 * to enter sleep mode separately. On the XR17V35x the रेजिस्टर
	 * is accessible to each UART at the UART_EXAR_SLEEP offset, but
	 * the UART channel may only ग_लिखो to the corresponding bit.
	 */
	serial_port_out(port, UART_EXAR_SLEEP, state ? 0xff : 0);
पूर्ण

/*
 * XR17V35x UARTs have an extra fractional भागisor रेजिस्टर (DLD)
 * Calculate भागisor with extra 4-bit fractional portion
 */
अटल अचिन्हित पूर्णांक xr17v35x_get_भागisor(काष्ठा uart_port *p, अचिन्हित पूर्णांक baud,
					 अचिन्हित पूर्णांक *frac)
अणु
	अचिन्हित पूर्णांक quot_16;

	quot_16 = DIV_ROUND_CLOSEST(p->uartclk, baud);
	*frac = quot_16 & 0x0f;

	वापस quot_16 >> 4;
पूर्ण

अटल व्योम xr17v35x_set_भागisor(काष्ठा uart_port *p, अचिन्हित पूर्णांक baud,
				 अचिन्हित पूर्णांक quot, अचिन्हित पूर्णांक quot_frac)
अणु
	serial8250_करो_set_भागisor(p, baud, quot, quot_frac);

	/* Preserve bits not related to baudrate; DLD[7:4]. */
	quot_frac |= serial_port_in(p, 0x2) & 0xf0;
	serial_port_out(p, 0x2, quot_frac);
पूर्ण

अटल पूर्णांक xr17v35x_startup(काष्ठा uart_port *port)
अणु
	/*
	 * First enable access to IER [7:5], ISR [5:4], FCR [5:4],
	 * MCR [7:5] and MSR [7:0]
	 */
	serial_port_out(port, UART_XR_EFR, UART_EFR_ECB);

	/*
	 * Make sure all पूर्णांकerrups are masked until initialization is
	 * complete and the FIFOs are cleared
	 */
	serial_port_out(port, UART_IER, 0);

	वापस serial8250_करो_startup(port);
पूर्ण

अटल व्योम exar_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर lsr;
	bool tx_complete = false;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक i = 0;

	करो अणु
		lsr = serial_in(up, UART_LSR);
		अगर (lsr & (UART_LSR_TEMT | UART_LSR_THRE))
			tx_complete = true;
		अन्यथा
			tx_complete = false;
		usleep_range(1000, 1100);
	पूर्ण जबतक (!uart_circ_empty(xmit) && !tx_complete && i++ < 1000);

	serial8250_करो_shutकरोwn(port);
पूर्ण

अटल पूर्णांक शेष_setup(काष्ठा exar8250 *priv, काष्ठा pci_dev *pcidev,
			 पूर्णांक idx, अचिन्हित पूर्णांक offset,
			 काष्ठा uart_8250_port *port)
अणु
	स्थिर काष्ठा exar8250_board *board = priv->board;
	अचिन्हित पूर्णांक bar = 0;
	अचिन्हित अक्षर status;

	port->port.iotype = UPIO_MEM;
	port->port.mapbase = pci_resource_start(pcidev, bar) + offset;
	port->port.membase = priv->virt + offset;
	port->port.regshअगरt = board->reg_shअगरt;

	/*
	 * XR17V35x UARTs have an extra भागisor रेजिस्टर, DLD that माला_लो enabled
	 * with when DLAB is set which will cause the device to incorrectly match
	 * and assign port type to PORT_16650. The EFR क्रम this UART is found
	 * at offset 0x09. Instead check the Deice ID (DVID) रेजिस्टर
	 * क्रम a 2, 4 or 8 port UART.
	 */
	status = पढ़ोb(port->port.membase + UART_EXAR_DVID);
	अगर (status == 0x82 || status == 0x84 || status == 0x88) अणु
		port->port.type = PORT_XR17V35X;

		port->port.get_भागisor = xr17v35x_get_भागisor;
		port->port.set_भागisor = xr17v35x_set_भागisor;

		port->port.startup = xr17v35x_startup;
	पूर्ण अन्यथा अणु
		port->port.type = PORT_XR17D15X;
	पूर्ण

	port->port.pm = exar_pm;
	port->port.shutकरोwn = exar_shutकरोwn;

	वापस 0;
पूर्ण

अटल पूर्णांक
pci_fastcom335_setup(काष्ठा exar8250 *priv, काष्ठा pci_dev *pcidev,
		     काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक offset = idx * 0x200;
	अचिन्हित पूर्णांक baud = 1843200;
	u8 __iomem *p;
	पूर्णांक err;

	port->port.uartclk = baud * 16;

	err = शेष_setup(priv, pcidev, idx, offset, port);
	अगर (err)
		वापस err;

	p = port->port.membase;

	ग_लिखोb(0x00, p + UART_EXAR_8XMODE);
	ग_लिखोb(UART_FCTR_EXAR_TRGD, p + UART_EXAR_FCTR);
	ग_लिखोb(32, p + UART_EXAR_TXTRG);
	ग_लिखोb(32, p + UART_EXAR_RXTRG);

	/*
	 * Setup Multipurpose Input/Output pins.
	 */
	अगर (idx == 0) अणु
		चयन (pcidev->device) अणु
		हाल PCI_DEVICE_ID_COMMTECH_4222PCI335:
		हाल PCI_DEVICE_ID_COMMTECH_4224PCI335:
			ग_लिखोb(0x78, p + UART_EXAR_MPIOLVL_7_0);
			ग_लिखोb(0x00, p + UART_EXAR_MPIOINV_7_0);
			ग_लिखोb(0x00, p + UART_EXAR_MPIOSEL_7_0);
			अवरोध;
		हाल PCI_DEVICE_ID_COMMTECH_2324PCI335:
		हाल PCI_DEVICE_ID_COMMTECH_2328PCI335:
			ग_लिखोb(0x00, p + UART_EXAR_MPIOLVL_7_0);
			ग_लिखोb(0xc0, p + UART_EXAR_MPIOINV_7_0);
			ग_लिखोb(0xc0, p + UART_EXAR_MPIOSEL_7_0);
			अवरोध;
		पूर्ण
		ग_लिखोb(0x00, p + UART_EXAR_MPIOINT_7_0);
		ग_लिखोb(0x00, p + UART_EXAR_MPIO3T_7_0);
		ग_लिखोb(0x00, p + UART_EXAR_MPIOOD_7_0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
pci_connect_tech_setup(काष्ठा exar8250 *priv, काष्ठा pci_dev *pcidev,
		       काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक offset = idx * 0x200;
	अचिन्हित पूर्णांक baud = 1843200;

	port->port.uartclk = baud * 16;
	वापस शेष_setup(priv, pcidev, idx, offset, port);
पूर्ण

अटल पूर्णांक
pci_xr17c154_setup(काष्ठा exar8250 *priv, काष्ठा pci_dev *pcidev,
		   काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक offset = idx * 0x200;
	अचिन्हित पूर्णांक baud = 921600;

	port->port.uartclk = baud * 16;
	वापस शेष_setup(priv, pcidev, idx, offset, port);
पूर्ण

अटल व्योम setup_gpio(काष्ठा pci_dev *pcidev, u8 __iomem *p)
अणु
	/*
	 * The Commtech adapters required the MPIOs to be driven low. The Exar
	 * devices will export them as GPIOs, so we pre-configure them safely
	 * as inमाला_दो.
	 */

	u8 dir = 0x00;

	अगर  ((pcidev->venकरोr == PCI_VENDOR_ID_EXAR) &&
		(pcidev->subप्रणाली_venकरोr != PCI_VENDOR_ID_SEALEVEL)) अणु
		// Configure GPIO as inमाला_दो क्रम Commtech adapters
		dir = 0xff;
	पूर्ण अन्यथा अणु
		// Configure GPIO as outमाला_दो क्रम SeaLevel adapters
		dir = 0x00;
	पूर्ण

	ग_लिखोb(0x00, p + UART_EXAR_MPIOINT_7_0);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOLVL_7_0);
	ग_लिखोb(0x00, p + UART_EXAR_MPIO3T_7_0);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOINV_7_0);
	ग_लिखोb(dir,  p + UART_EXAR_MPIOSEL_7_0);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOOD_7_0);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOINT_15_8);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOLVL_15_8);
	ग_लिखोb(0x00, p + UART_EXAR_MPIO3T_15_8);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOINV_15_8);
	ग_लिखोb(dir,  p + UART_EXAR_MPIOSEL_15_8);
	ग_लिखोb(0x00, p + UART_EXAR_MPIOOD_15_8);
पूर्ण

अटल व्योम *
__xr17v35x_रेजिस्टर_gpio(काष्ठा pci_dev *pcidev,
			 स्थिर काष्ठा software_node *node)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_alloc("gpio_exar", PLATFORM_DEVID_AUTO);
	अगर (!pdev)
		वापस शून्य;

	pdev->dev.parent = &pcidev->dev;
	ACPI_COMPANION_SET(&pdev->dev, ACPI_COMPANION(&pcidev->dev));

	अगर (device_add_software_node(&pdev->dev, node) < 0 ||
	    platक्रमm_device_add(pdev) < 0) अणु
		platक्रमm_device_put(pdev);
		वापस शून्य;
	पूर्ण

	वापस pdev;
पूर्ण

अटल स्थिर काष्ठा property_entry exar_gpio_properties[] = अणु
	PROPERTY_ENTRY_U32("exar,first-pin", 0),
	PROPERTY_ENTRY_U32("ngpios", 16),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node exar_gpio_node = अणु
	.properties = exar_gpio_properties,
पूर्ण;

अटल पूर्णांक xr17v35x_रेजिस्टर_gpio(काष्ठा pci_dev *pcidev,
				  काष्ठा uart_8250_port *port)
अणु
	अगर (pcidev->venकरोr == PCI_VENDOR_ID_EXAR)
		port->port.निजी_data =
			__xr17v35x_रेजिस्टर_gpio(pcidev, &exar_gpio_node);

	वापस 0;
पूर्ण

अटल पूर्णांक generic_rs485_config(काष्ठा uart_port *port,
				काष्ठा serial_rs485 *rs485)
अणु
	bool is_rs485 = !!(rs485->flags & SER_RS485_ENABLED);
	u8 __iomem *p = port->membase;
	u8 value;

	value = पढ़ोb(p + UART_EXAR_FCTR);
	अगर (is_rs485)
		value |= UART_FCTR_EXAR_485;
	अन्यथा
		value &= ~UART_FCTR_EXAR_485;

	ग_लिखोb(value, p + UART_EXAR_FCTR);

	अगर (is_rs485)
		ग_लिखोb(UART_EXAR_RS485_DLY(4), p + UART_MSR);

	port->rs485 = *rs485;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा exar8250_platक्रमm exar8250_शेष_platक्रमm = अणु
	.रेजिस्टर_gpio = xr17v35x_रेजिस्टर_gpio,
	.rs485_config = generic_rs485_config,
पूर्ण;

अटल पूर्णांक iot2040_rs485_config(काष्ठा uart_port *port,
				काष्ठा serial_rs485 *rs485)
अणु
	bool is_rs485 = !!(rs485->flags & SER_RS485_ENABLED);
	u8 __iomem *p = port->membase;
	u8 mask = IOT2040_UART1_MASK;
	u8 mode, value;

	अगर (is_rs485) अणु
		अगर (rs485->flags & SER_RS485_RX_DURING_TX)
			mode = IOT2040_UART_MODE_RS422;
		अन्यथा
			mode = IOT2040_UART_MODE_RS485;

		अगर (rs485->flags & SER_RS485_TERMINATE_BUS)
			mode |= IOT2040_UART_TERMINATE_BUS;
	पूर्ण अन्यथा अणु
		mode = IOT2040_UART_MODE_RS232;
	पूर्ण

	अगर (port->line == 3) अणु
		mask <<= IOT2040_UART2_SHIFT;
		mode <<= IOT2040_UART2_SHIFT;
	पूर्ण

	value = पढ़ोb(p + UART_EXAR_MPIOLVL_7_0);
	value &= ~mask;
	value |= mode;
	ग_लिखोb(value, p + UART_EXAR_MPIOLVL_7_0);

	वापस generic_rs485_config(port, rs485);
पूर्ण

अटल स्थिर काष्ठा property_entry iot2040_gpio_properties[] = अणु
	PROPERTY_ENTRY_U32("exar,first-pin", 10),
	PROPERTY_ENTRY_U32("ngpios", 1),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node iot2040_gpio_node = अणु
	.properties = iot2040_gpio_properties,
पूर्ण;

अटल पूर्णांक iot2040_रेजिस्टर_gpio(काष्ठा pci_dev *pcidev,
			      काष्ठा uart_8250_port *port)
अणु
	u8 __iomem *p = port->port.membase;

	ग_लिखोb(IOT2040_UARTS_DEFAULT_MODE, p + UART_EXAR_MPIOLVL_7_0);
	ग_लिखोb(IOT2040_UARTS_GPIO_LO_MODE, p + UART_EXAR_MPIOSEL_7_0);
	ग_लिखोb(IOT2040_UARTS_ENABLE, p + UART_EXAR_MPIOLVL_15_8);
	ग_लिखोb(IOT2040_UARTS_GPIO_HI_MODE, p + UART_EXAR_MPIOSEL_15_8);

	port->port.निजी_data =
		__xr17v35x_रेजिस्टर_gpio(pcidev, &iot2040_gpio_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा exar8250_platक्रमm iot2040_platक्रमm = अणु
	.rs485_config = iot2040_rs485_config,
	.रेजिस्टर_gpio = iot2040_रेजिस्टर_gpio,
पूर्ण;

/*
 * For SIMATIC IOT2000, only IOT2040 and its variants have the Exar device,
 * IOT2020 करोesn't have. Thereक्रमe it is sufficient to match on the common
 * board name after the device was found.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id exar_platक्रमms[] = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "SIMATIC IOT2000"),
		पूर्ण,
		.driver_data = (व्योम *)&iot2040_platक्रमm,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
pci_xr17v35x_setup(काष्ठा exar8250 *priv, काष्ठा pci_dev *pcidev,
		   काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	स्थिर काष्ठा exar8250_platक्रमm *platक्रमm;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_match;
	अचिन्हित पूर्णांक offset = idx * 0x400;
	अचिन्हित पूर्णांक baud = 7812500;
	u8 __iomem *p;
	पूर्णांक ret;

	dmi_match = dmi_first_match(exar_platक्रमms);
	अगर (dmi_match)
		platक्रमm = dmi_match->driver_data;
	अन्यथा
		platक्रमm = &exar8250_शेष_platक्रमm;

	port->port.uartclk = baud * 16;
	port->port.rs485_config = platक्रमm->rs485_config;

	/*
	 * Setup the UART घड़ी क्रम the devices on expansion slot to
	 * half the घड़ी speed of the मुख्य chip (which is 125MHz)
	 */
	अगर (idx >= 8)
		port->port.uartclk /= 2;

	ret = शेष_setup(priv, pcidev, idx, offset, port);
	अगर (ret)
		वापस ret;

	p = port->port.membase;

	ग_लिखोb(0x00, p + UART_EXAR_8XMODE);
	ग_लिखोb(UART_FCTR_EXAR_TRGD, p + UART_EXAR_FCTR);
	ग_लिखोb(128, p + UART_EXAR_TXTRG);
	ग_लिखोb(128, p + UART_EXAR_RXTRG);

	अगर (idx == 0) अणु
		/* Setup Multipurpose Input/Output pins. */
		setup_gpio(pcidev, p);

		ret = platक्रमm->रेजिस्टर_gpio(pcidev, port);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pci_xr17v35x_निकास(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा exar8250 *priv = pci_get_drvdata(pcidev);
	काष्ठा uart_8250_port *port = serial8250_get_port(priv->line[0]);
	काष्ठा platक्रमm_device *pdev;

	pdev = port->port.निजी_data;
	अगर (!pdev)
		वापस;

	device_हटाओ_software_node(&pdev->dev);
	platक्रमm_device_unरेजिस्टर(pdev);
	port->port.निजी_data = शून्य;
पूर्ण

अटल अंतरभूत व्योम exar_misc_clear(काष्ठा exar8250 *priv)
अणु
	/* Clear all PCI पूर्णांकerrupts by पढ़ोing INT0. No effect on IIR */
	पढ़ोb(priv->virt + UART_EXAR_INT0);

	/* Clear INT0 क्रम Expansion Interface slave ports, too */
	अगर (priv->board->num_ports > 8)
		पढ़ोb(priv->virt + 0x2000 + UART_EXAR_INT0);
पूर्ण

/*
 * These Exar UARTs have an extra पूर्णांकerrupt indicator that could fire क्रम a
 * few पूर्णांकerrupts that are not presented/cleared through IIR.  One of which is
 * a wakeup पूर्णांकerrupt when coming out of sleep.  These पूर्णांकerrupts are only
 * cleared by पढ़ोing global INT0 or INT1 रेजिस्टरs as पूर्णांकerrupts are
 * associated with channel 0. The INT[3:0] रेजिस्टरs _are_ accessible from each
 * channel's address space, but क्रम the sake of bus efficiency we रेजिस्टर a
 * dedicated handler at the PCI device level to handle them.
 */
अटल irqवापस_t exar_misc_handler(पूर्णांक irq, व्योम *data)
अणु
	exar_misc_clear(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
exar_pci_probe(काष्ठा pci_dev *pcidev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक nr_ports, i, bar = 0, maxnr;
	काष्ठा exar8250_board *board;
	काष्ठा uart_8250_port uart;
	काष्ठा exar8250 *priv;
	पूर्णांक rc;

	board = (काष्ठा exar8250_board *)ent->driver_data;
	अगर (!board)
		वापस -EINVAL;

	rc = pcim_enable_device(pcidev);
	अगर (rc)
		वापस rc;

	maxnr = pci_resource_len(pcidev, bar) >> (board->reg_shअगरt + 3);

	nr_ports = board->num_ports ? board->num_ports : pcidev->device & 0x0f;

	priv = devm_kzalloc(&pcidev->dev, काष्ठा_size(priv, line, nr_ports), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->board = board;
	priv->virt = pcim_iomap(pcidev, bar, 0);
	अगर (!priv->virt)
		वापस -ENOMEM;

	pci_set_master(pcidev);

	rc = pci_alloc_irq_vectors(pcidev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (rc < 0)
		वापस rc;

	स_रखो(&uart, 0, माप(uart));
	uart.port.flags = UPF_SHARE_IRQ | UPF_EXAR_EFR | UPF_FIXED_TYPE | UPF_FIXED_PORT;
	uart.port.irq = pci_irq_vector(pcidev, 0);
	uart.port.dev = &pcidev->dev;

	rc = devm_request_irq(&pcidev->dev, uart.port.irq, exar_misc_handler,
			 IRQF_SHARED, "exar_uart", priv);
	अगर (rc)
		वापस rc;

	/* Clear पूर्णांकerrupts */
	exar_misc_clear(priv);

	क्रम (i = 0; i < nr_ports && i < maxnr; i++) अणु
		rc = board->setup(priv, pcidev, &uart, i);
		अगर (rc) अणु
			dev_err(&pcidev->dev, "Failed to setup port %u\n", i);
			अवरोध;
		पूर्ण

		dev_dbg(&pcidev->dev, "Setup PCI port: port %lx, irq %d, type %d\n",
			uart.port.iobase, uart.port.irq, uart.port.iotype);

		priv->line[i] = serial8250_रेजिस्टर_8250_port(&uart);
		अगर (priv->line[i] < 0) अणु
			dev_err(&pcidev->dev,
				"Couldn't register serial port %lx, irq %d, type %d, error %d\n",
				uart.port.iobase, uart.port.irq,
				uart.port.iotype, priv->line[i]);
			अवरोध;
		पूर्ण
	पूर्ण
	priv->nr = i;
	pci_set_drvdata(pcidev, priv);
	वापस 0;
पूर्ण

अटल व्योम exar_pci_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा exar8250 *priv = pci_get_drvdata(pcidev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->nr; i++)
		serial8250_unरेजिस्टर_port(priv->line[i]);

	अगर (priv->board->निकास)
		priv->board->निकास(pcidev);
पूर्ण

अटल पूर्णांक __maybe_unused exar_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pcidev = to_pci_dev(dev);
	काष्ठा exar8250 *priv = pci_get_drvdata(pcidev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->nr; i++)
		अगर (priv->line[i] >= 0)
			serial8250_suspend_port(priv->line[i]);

	/* Ensure that every init quirk is properly torn करोwn */
	अगर (priv->board->निकास)
		priv->board->निकास(pcidev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exar_resume(काष्ठा device *dev)
अणु
	काष्ठा exar8250 *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	exar_misc_clear(priv);

	क्रम (i = 0; i < priv->nr; i++)
		अगर (priv->line[i] >= 0)
			serial8250_resume_port(priv->line[i]);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(exar_pci_pm, exar_suspend, exar_resume);

अटल स्थिर काष्ठा exar8250_board acces_com_2x = अणु
	.num_ports	= 2,
	.setup		= pci_xr17c154_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board acces_com_4x = अणु
	.num_ports	= 4,
	.setup		= pci_xr17c154_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board acces_com_8x = अणु
	.num_ports	= 8,
	.setup		= pci_xr17c154_setup,
पूर्ण;


अटल स्थिर काष्ठा exar8250_board pbn_fastcom335_2 = अणु
	.num_ports	= 2,
	.setup		= pci_fastcom335_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_fastcom335_4 = अणु
	.num_ports	= 4,
	.setup		= pci_fastcom335_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_fastcom335_8 = अणु
	.num_ports	= 8,
	.setup		= pci_fastcom335_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_connect = अणु
	.setup		= pci_connect_tech_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_exar_ibm_saturn = अणु
	.num_ports	= 1,
	.setup		= pci_xr17c154_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_exar_XR17C15x = अणु
	.setup		= pci_xr17c154_setup,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_exar_XR17V35x = अणु
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_fastcom35x_2 = अणु
	.num_ports	= 2,
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_fastcom35x_4 = अणु
	.num_ports	= 4,
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_fastcom35x_8 = अणु
	.num_ports	= 8,
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_exar_XR17V4358 = अणु
	.num_ports	= 12,
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

अटल स्थिर काष्ठा exar8250_board pbn_exar_XR17V8358 = अणु
	.num_ports	= 16,
	.setup		= pci_xr17v35x_setup,
	.निकास		= pci_xr17v35x_निकास,
पूर्ण;

#घोषणा CONNECT_DEVICE(devid, sdevid, bd) अणु				\
	PCI_DEVICE_SUB(							\
		PCI_VENDOR_ID_EXAR,					\
		PCI_DEVICE_ID_EXAR_##devid,				\
		PCI_SUBVENDOR_ID_CONNECT_TECH,				\
		PCI_SUBDEVICE_ID_CONNECT_TECH_PCI_##sdevid), 0, 0,	\
		(kernel_uदीर्घ_t)&bd					\
	पूर्ण

#घोषणा EXAR_DEVICE(vend, devid, bd) अणु PCI_DEVICE_DATA(vend, devid, &bd) पूर्ण

#घोषणा IBM_DEVICE(devid, sdevid, bd) अणु			\
	PCI_DEVICE_SUB(					\
		PCI_VENDOR_ID_EXAR,			\
		PCI_DEVICE_ID_EXAR_##devid,		\
		PCI_VENDOR_ID_IBM,			\
		PCI_SUBDEVICE_ID_IBM_##sdevid), 0, 0,	\
		(kernel_uदीर्घ_t)&bd			\
	पूर्ण

अटल स्थिर काष्ठा pci_device_id exar_pci_tbl[] = अणु
	EXAR_DEVICE(ACCESSIO, COM_2S, acces_com_2x),
	EXAR_DEVICE(ACCESSIO, COM_4S, acces_com_4x),
	EXAR_DEVICE(ACCESSIO, COM_8S, acces_com_8x),
	EXAR_DEVICE(ACCESSIO, COM232_8, acces_com_8x),
	EXAR_DEVICE(ACCESSIO, COM_2SM, acces_com_2x),
	EXAR_DEVICE(ACCESSIO, COM_4SM, acces_com_4x),
	EXAR_DEVICE(ACCESSIO, COM_8SM, acces_com_8x),

	CONNECT_DEVICE(XR17C152, UART_2_232, pbn_connect),
	CONNECT_DEVICE(XR17C154, UART_4_232, pbn_connect),
	CONNECT_DEVICE(XR17C158, UART_8_232, pbn_connect),
	CONNECT_DEVICE(XR17C152, UART_1_1, pbn_connect),
	CONNECT_DEVICE(XR17C154, UART_2_2, pbn_connect),
	CONNECT_DEVICE(XR17C158, UART_4_4, pbn_connect),
	CONNECT_DEVICE(XR17C152, UART_2, pbn_connect),
	CONNECT_DEVICE(XR17C154, UART_4, pbn_connect),
	CONNECT_DEVICE(XR17C158, UART_8, pbn_connect),
	CONNECT_DEVICE(XR17C152, UART_2_485, pbn_connect),
	CONNECT_DEVICE(XR17C154, UART_4_485, pbn_connect),
	CONNECT_DEVICE(XR17C158, UART_8_485, pbn_connect),

	IBM_DEVICE(XR17C152, SATURN_SERIAL_ONE_PORT, pbn_exar_ibm_saturn),

	/* Exar Corp. XR17C15[248] Dual/Quad/Octal UART */
	EXAR_DEVICE(EXAR, XR17C152, pbn_exar_XR17C15x),
	EXAR_DEVICE(EXAR, XR17C154, pbn_exar_XR17C15x),
	EXAR_DEVICE(EXAR, XR17C158, pbn_exar_XR17C15x),

	/* Exar Corp. XR17V[48]35[248] Dual/Quad/Octal/Hexa PCIe UARTs */
	EXAR_DEVICE(EXAR, XR17V352, pbn_exar_XR17V35x),
	EXAR_DEVICE(EXAR, XR17V354, pbn_exar_XR17V35x),
	EXAR_DEVICE(EXAR, XR17V358, pbn_exar_XR17V35x),
	EXAR_DEVICE(EXAR, XR17V4358, pbn_exar_XR17V4358),
	EXAR_DEVICE(EXAR, XR17V8358, pbn_exar_XR17V8358),
	EXAR_DEVICE(COMMTECH, 4222PCIE, pbn_fastcom35x_2),
	EXAR_DEVICE(COMMTECH, 4224PCIE, pbn_fastcom35x_4),
	EXAR_DEVICE(COMMTECH, 4228PCIE, pbn_fastcom35x_8),

	EXAR_DEVICE(COMMTECH, 4222PCI335, pbn_fastcom335_2),
	EXAR_DEVICE(COMMTECH, 4224PCI335, pbn_fastcom335_4),
	EXAR_DEVICE(COMMTECH, 2324PCI335, pbn_fastcom335_4),
	EXAR_DEVICE(COMMTECH, 2328PCI335, pbn_fastcom335_8),
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, exar_pci_tbl);

अटल काष्ठा pci_driver exar_pci_driver = अणु
	.name		= "exar_serial",
	.probe		= exar_pci_probe,
	.हटाओ		= exar_pci_हटाओ,
	.driver         = अणु
		.pm     = &exar_pci_pm,
	पूर्ण,
	.id_table	= exar_pci_tbl,
पूर्ण;
module_pci_driver(exar_pci_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Exar Serial Driver");
MODULE_AUTHOR("Sudip Mukherjee <sudip.mukherjee@codethink.co.uk>");
