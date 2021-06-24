<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Probe module क्रम 8250/16550-type PCI serial ports.
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 */
#अघोषित DEBUG
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/8250_pci.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>

#समावेश "8250.h"

/*
 * init function वापसs:
 *  > 0 - number of ports
 *  = 0 - use board->num_ports
 *  < 0 - error
 */
काष्ठा pci_serial_quirk अणु
	u32	venकरोr;
	u32	device;
	u32	subvenकरोr;
	u32	subdevice;
	पूर्णांक	(*probe)(काष्ठा pci_dev *dev);
	पूर्णांक	(*init)(काष्ठा pci_dev *dev);
	पूर्णांक	(*setup)(काष्ठा serial_निजी *,
			 स्थिर काष्ठा pciserial_board *,
			 काष्ठा uart_8250_port *, पूर्णांक);
	व्योम	(*निकास)(काष्ठा pci_dev *dev);
पूर्ण;

काष्ठा f815xxa_data अणु
	spinlock_t lock;
	पूर्णांक idx;
पूर्ण;

काष्ठा serial_निजी अणु
	काष्ठा pci_dev		*dev;
	अचिन्हित पूर्णांक		nr;
	काष्ठा pci_serial_quirk	*quirk;
	स्थिर काष्ठा pciserial_board *board;
	पूर्णांक			line[];
पूर्ण;

#घोषणा PCI_DEVICE_ID_HPE_PCI_SERIAL	0x37e

अटल स्थिर काष्ठा pci_device_id pci_use_msi[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
			 0xA000, 0x1000) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9912,
			 0xA000, 0x1000) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9922,
			 0xA000, 0x1000) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_HP_3PAR, PCI_DEVICE_ID_HPE_PCI_SERIAL,
			 PCI_ANY_ID, PCI_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक pci_शेष_setup(काष्ठा serial_निजी*,
	  स्थिर काष्ठा pciserial_board*, काष्ठा uart_8250_port *, पूर्णांक);

अटल व्योम moan_device(स्थिर अक्षर *str, काष्ठा pci_dev *dev)
अणु
	dev_err(&dev->dev,
	       "%s: %s\n"
	       "Please send the output of lspci -vv, this\n"
	       "message (0x%04x,0x%04x,0x%04x,0x%04x), the\n"
	       "manufacturer and name of serial board or\n"
	       "modem board to <linux-serial@vger.kernel.org>.\n",
	       pci_name(dev), str, dev->venकरोr, dev->device,
	       dev->subप्रणाली_venकरोr, dev->subप्रणाली_device);
पूर्ण

अटल पूर्णांक
setup_port(काष्ठा serial_निजी *priv, काष्ठा uart_8250_port *port,
	   पूर्णांक bar, पूर्णांक offset, पूर्णांक regshअगरt)
अणु
	काष्ठा pci_dev *dev = priv->dev;

	अगर (bar >= PCI_STD_NUM_BARS)
		वापस -EINVAL;

	अगर (pci_resource_flags(dev, bar) & IORESOURCE_MEM) अणु
		अगर (!pcim_iomap(dev, bar, 0) && !pcim_iomap_table(dev))
			वापस -ENOMEM;

		port->port.iotype = UPIO_MEM;
		port->port.iobase = 0;
		port->port.mapbase = pci_resource_start(dev, bar) + offset;
		port->port.membase = pcim_iomap_table(dev)[bar] + offset;
		port->port.regshअगरt = regshअगरt;
	पूर्ण अन्यथा अणु
		port->port.iotype = UPIO_PORT;
		port->port.iobase = pci_resource_start(dev, bar) + offset;
		port->port.mapbase = 0;
		port->port.membase = शून्य;
		port->port.regshअगरt = 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ADDI-DATA GmbH communication cards <info@addi-data.com>
 */
अटल पूर्णांक addidata_apci7800_setup(काष्ठा serial_निजी *priv,
				स्थिर काष्ठा pciserial_board *board,
				काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar = 0, offset = board->first_offset;
	bar = FL_GET_BASE(board->flags);

	अगर (idx < 2) अणु
		offset += idx * board->uart_offset;
	पूर्ण अन्यथा अगर ((idx >= 2) && (idx < 4)) अणु
		bar += 1;
		offset += ((idx - 2) * board->uart_offset);
	पूर्ण अन्यथा अगर ((idx >= 4) && (idx < 6)) अणु
		bar += 2;
		offset += ((idx - 4) * board->uart_offset);
	पूर्ण अन्यथा अगर (idx >= 6) अणु
		bar += 3;
		offset += ((idx - 6) * board->uart_offset);
	पूर्ण

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

/*
 * AFAVLAB uses a dअगरferent mixture of BARs and offsets
 * Not that ugly ;) -- HW
 */
अटल पूर्णांक
afavlab_setup(काष्ठा serial_निजी *priv, स्थिर काष्ठा pciserial_board *board,
	      काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset;

	bar = FL_GET_BASE(board->flags);
	अगर (idx < 4)
		bar += idx;
	अन्यथा अणु
		bar = 4;
		offset += (idx - 4) * board->uart_offset;
	पूर्ण

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

/*
 * HP's Remote Management Console.  The Diva chip came in several
 * dअगरferent versions.  N-class, L2000 and A500 have two Diva chips, each
 * with 3 UARTs (the third UART on the second chip is unused).  Superकरोme
 * and Keystone have one Diva chip with 3 UARTs.  Some later machines have
 * one Diva chip, but it has been expanded to 5 UARTs.
 */
अटल पूर्णांक pci_hp_भागa_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc = 0;

	चयन (dev->subप्रणाली_device) अणु
	हाल PCI_DEVICE_ID_HP_DIVA_TOSCA1:
	हाल PCI_DEVICE_ID_HP_DIVA_HALFDOME:
	हाल PCI_DEVICE_ID_HP_DIVA_KEYSTONE:
	हाल PCI_DEVICE_ID_HP_DIVA_EVEREST:
		rc = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_HP_DIVA_TOSCA2:
		rc = 2;
		अवरोध;
	हाल PCI_DEVICE_ID_HP_DIVA_MAESTRO:
		rc = 4;
		अवरोध;
	हाल PCI_DEVICE_ID_HP_DIVA_POWERBAR:
	हाल PCI_DEVICE_ID_HP_DIVA_HURRICANE:
		rc = 1;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * HP's Diva chip माला_दो the 4th/5th serial port further out, and
 * some serial ports are supposed to be hidden on certain models.
 */
अटल पूर्णांक
pci_hp_भागa_setup(काष्ठा serial_निजी *priv,
		स्थिर काष्ठा pciserial_board *board,
		काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक offset = board->first_offset;
	अचिन्हित पूर्णांक bar = FL_GET_BASE(board->flags);

	चयन (priv->dev->subप्रणाली_device) अणु
	हाल PCI_DEVICE_ID_HP_DIVA_MAESTRO:
		अगर (idx == 3)
			idx++;
		अवरोध;
	हाल PCI_DEVICE_ID_HP_DIVA_EVEREST:
		अगर (idx > 0)
			idx++;
		अगर (idx > 2)
			idx++;
		अवरोध;
	पूर्ण
	अगर (idx > 2)
		offset = 0x18;

	offset += idx * board->uart_offset;

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

/*
 * Added क्रम EKF Intel i960 serial boards
 */
अटल पूर्णांक pci_पूर्णांकeli960ni_init(काष्ठा pci_dev *dev)
अणु
	u32 oldval;

	अगर (!(dev->subप्रणाली_device & 0x1000))
		वापस -ENODEV;

	/* is firmware started? */
	pci_पढ़ो_config_dword(dev, 0x44, &oldval);
	अगर (oldval == 0x00001000L) अणु /* RESET value */
		dev_dbg(&dev->dev, "Local i960 firmware missing\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Some PCI serial cards using the PLX 9050 PCI पूर्णांकerface chip require
 * that the card पूर्णांकerrupt be explicitly enabled or disabled.  This
 * seems to be मुख्यly needed on card using the PLX which also use I/O
 * mapped memory.
 */
अटल पूर्णांक pci_plx9050_init(काष्ठा pci_dev *dev)
अणु
	u8 irq_config;
	व्योम __iomem *p;

	अगर ((pci_resource_flags(dev, 0) & IORESOURCE_MEM) == 0) अणु
		moan_device("no memory in bar 0", dev);
		वापस 0;
	पूर्ण

	irq_config = 0x41;
	अगर (dev->venकरोr == PCI_VENDOR_ID_PANACOM ||
	    dev->subप्रणाली_venकरोr == PCI_SUBVENDOR_ID_EXSYS)
		irq_config = 0x43;

	अगर ((dev->venकरोr == PCI_VENDOR_ID_PLX) &&
	    (dev->device == PCI_DEVICE_ID_PLX_ROMULUS))
		/*
		 * As the megawolf cards have the पूर्णांक pins active
		 * high, and have 2 UART chips, both पूर्णांकs must be
		 * enabled on the 9050. Also, the UARTS are set in
		 * 16450 mode by शेष, so we have to enable the
		 * 16C950 'enhanced' mode so that we can use the
		 * deep FIFOs
		 */
		irq_config = 0x5b;
	/*
	 * enable/disable पूर्णांकerrupts
	 */
	p = ioremap(pci_resource_start(dev, 0), 0x80);
	अगर (p == शून्य)
		वापस -ENOMEM;
	ग_लिखोl(irq_config, p + 0x4c);

	/*
	 * Read the रेजिस्टर back to ensure that it took effect.
	 */
	पढ़ोl(p + 0x4c);
	iounmap(p);

	वापस 0;
पूर्ण

अटल व्योम pci_plx9050_निकास(काष्ठा pci_dev *dev)
अणु
	u8 __iomem *p;

	अगर ((pci_resource_flags(dev, 0) & IORESOURCE_MEM) == 0)
		वापस;

	/*
	 * disable पूर्णांकerrupts
	 */
	p = ioremap(pci_resource_start(dev, 0), 0x80);
	अगर (p != शून्य) अणु
		ग_लिखोl(0, p + 0x4c);

		/*
		 * Read the रेजिस्टर back to ensure that it took effect.
		 */
		पढ़ोl(p + 0x4c);
		iounmap(p);
	पूर्ण
पूर्ण

#घोषणा NI8420_INT_ENABLE_REG	0x38
#घोषणा NI8420_INT_ENABLE_BIT	0x2000

अटल व्योम pci_ni8420_निकास(काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *p;
	अचिन्हित पूर्णांक bar = 0;

	अगर ((pci_resource_flags(dev, bar) & IORESOURCE_MEM) == 0) अणु
		moan_device("no memory in bar", dev);
		वापस;
	पूर्ण

	p = pci_ioremap_bar(dev, bar);
	अगर (p == शून्य)
		वापस;

	/* Disable the CPU Interrupt */
	ग_लिखोl(पढ़ोl(p + NI8420_INT_ENABLE_REG) & ~(NI8420_INT_ENABLE_BIT),
	       p + NI8420_INT_ENABLE_REG);
	iounmap(p);
पूर्ण


/* MITE रेजिस्टरs */
#घोषणा MITE_IOWBSR1	0xc4
#घोषणा MITE_IOWCR1	0xf4
#घोषणा MITE_LCIMR1	0x08
#घोषणा MITE_LCIMR2	0x10

#घोषणा MITE_LCIMR2_CLR_CPU_IE	(1 << 30)

अटल व्योम pci_ni8430_निकास(काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *p;
	अचिन्हित पूर्णांक bar = 0;

	अगर ((pci_resource_flags(dev, bar) & IORESOURCE_MEM) == 0) अणु
		moan_device("no memory in bar", dev);
		वापस;
	पूर्ण

	p = pci_ioremap_bar(dev, bar);
	अगर (p == शून्य)
		वापस;

	/* Disable the CPU Interrupt */
	ग_लिखोl(MITE_LCIMR2_CLR_CPU_IE, p + MITE_LCIMR2);
	iounmap(p);
पूर्ण

/* SBS Technologies Inc. PMC-OCTPRO and P-OCTAL cards */
अटल पूर्णांक
sbs_setup(काष्ठा serial_निजी *priv, स्थिर काष्ठा pciserial_board *board,
		काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset;

	bar = 0;

	अगर (idx < 4) अणु
		/* first four channels map to 0, 0x100, 0x200, 0x300 */
		offset += idx * board->uart_offset;
	पूर्ण अन्यथा अगर (idx < 8) अणु
		/* last four channels map to 0x1000, 0x1100, 0x1200, 0x1300 */
		offset += idx * board->uart_offset + 0xC00;
	पूर्ण अन्यथा /* we have only 8 ports on PMC-OCTALPRO */
		वापस 1;

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

/*
* This करोes initialization क्रम PMC OCTALPRO cards:
* maps the device memory, resets the UARTs (needed, bc
* अगर the module is हटाओd and inserted again, the card
* is in the sleep mode) and enables global पूर्णांकerrupt.
*/

/* global control रेजिस्टर offset क्रम SBS PMC-OctalPro */
#घोषणा OCT_REG_CR_OFF		0x500

अटल पूर्णांक sbs_init(काष्ठा pci_dev *dev)
अणु
	u8 __iomem *p;

	p = pci_ioremap_bar(dev, 0);

	अगर (p == शून्य)
		वापस -ENOMEM;
	/* Set bit-4 Control Register (UART RESET) in to reset the uarts */
	ग_लिखोb(0x10, p + OCT_REG_CR_OFF);
	udelay(50);
	ग_लिखोb(0x0, p + OCT_REG_CR_OFF);

	/* Set bit-2 (INTENABLE) of Control Register */
	ग_लिखोb(0x4, p + OCT_REG_CR_OFF);
	iounmap(p);

	वापस 0;
पूर्ण

/*
 * Disables the global पूर्णांकerrupt of PMC-OctalPro
 */

अटल व्योम sbs_निकास(काष्ठा pci_dev *dev)
अणु
	u8 __iomem *p;

	p = pci_ioremap_bar(dev, 0);
	/* FIXME: What अगर resource_len < OCT_REG_CR_OFF */
	अगर (p != शून्य)
		ग_लिखोb(0, p + OCT_REG_CR_OFF);
	iounmap(p);
पूर्ण

/*
 * SIIG serial cards have an PCI पूर्णांकerface chip which also controls
 * the UART घड़ीing frequency. Each UART can be घड़ीed independently
 * (except cards equipped with 4 UARTs) and initial घड़ीing settings
 * are stored in the EEPROM chip. It can cause problems because this
 * version of serial driver करोesn't support differently clocked UART's
 * on single PCI card. To prevent this, initialization functions set
 * high frequency घड़ीing क्रम all UART's on given card. It is safe (I
 * hope) because it करोesn't touch EEPROM settings to prevent conflicts
 * with other OSes (like M$ DOS).
 *
 *  SIIG support added by Andrey Panin <pazke@करोnpac.ru>, 10/1999
 *
 * There is two family of SIIG serial cards with dअगरferent PCI
 * पूर्णांकerface chip and dअगरferent configuration methods:
 *     - 10x cards have control रेजिस्टरs in IO and/or memory space;
 *     - 20x cards have control रेजिस्टरs in standard PCI configuration space.
 *
 * Note: all 10x cards have PCI device ids 0x10..
 *       all 20x cards have PCI device ids 0x20..
 *
 * There are also Quartet Serial cards which use Oxक्रमd Semiconductor
 * 16954 quad UART PCI chip घड़ीed by 18.432 MHz quartz.
 *
 * Note: some SIIG cards are probed by the parport_serial object.
 */

#घोषणा PCI_DEVICE_ID_SIIG_1S_10x (PCI_DEVICE_ID_SIIG_1S_10x_550 & 0xfffc)
#घोषणा PCI_DEVICE_ID_SIIG_2S_10x (PCI_DEVICE_ID_SIIG_2S_10x_550 & 0xfff8)

अटल पूर्णांक pci_siig10x_init(काष्ठा pci_dev *dev)
अणु
	u16 data;
	व्योम __iomem *p;

	चयन (dev->device & 0xfff8) अणु
	हाल PCI_DEVICE_ID_SIIG_1S_10x:	/* 1S */
		data = 0xffdf;
		अवरोध;
	हाल PCI_DEVICE_ID_SIIG_2S_10x:	/* 2S, 2S1P */
		data = 0xf7ff;
		अवरोध;
	शेष:			/* 1S1P, 4S */
		data = 0xfffb;
		अवरोध;
	पूर्ण

	p = ioremap(pci_resource_start(dev, 0), 0x80);
	अगर (p == शून्य)
		वापस -ENOMEM;

	ग_लिखोw(पढ़ोw(p + 0x28) & data, p + 0x28);
	पढ़ोw(p + 0x28);
	iounmap(p);
	वापस 0;
पूर्ण

#घोषणा PCI_DEVICE_ID_SIIG_2S_20x (PCI_DEVICE_ID_SIIG_2S_20x_550 & 0xfffc)
#घोषणा PCI_DEVICE_ID_SIIG_2S1P_20x (PCI_DEVICE_ID_SIIG_2S1P_20x_550 & 0xfffc)

अटल पूर्णांक pci_siig20x_init(काष्ठा pci_dev *dev)
अणु
	u8 data;

	/* Change घड़ी frequency क्रम the first UART. */
	pci_पढ़ो_config_byte(dev, 0x6f, &data);
	pci_ग_लिखो_config_byte(dev, 0x6f, data & 0xef);

	/* If this card has 2 UART, we have to करो the same with second UART. */
	अगर (((dev->device & 0xfffc) == PCI_DEVICE_ID_SIIG_2S_20x) ||
	    ((dev->device & 0xfffc) == PCI_DEVICE_ID_SIIG_2S1P_20x)) अणु
		pci_पढ़ो_config_byte(dev, 0x73, &data);
		pci_ग_लिखो_config_byte(dev, 0x73, data & 0xef);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pci_siig_init(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक type = dev->device & 0xff00;

	अगर (type == 0x1000)
		वापस pci_siig10x_init(dev);
	अन्यथा अगर (type == 0x2000)
		वापस pci_siig20x_init(dev);

	moan_device("Unknown SIIG card", dev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक pci_siig_setup(काष्ठा serial_निजी *priv,
			  स्थिर काष्ठा pciserial_board *board,
			  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar = FL_GET_BASE(board->flags) + idx, offset = 0;

	अगर (idx > 3) अणु
		bar = 4;
		offset = (idx - 4) * 8;
	पूर्ण

	वापस setup_port(priv, port, bar, offset, 0);
पूर्ण

/*
 * Timedia has an explosion of boards, and to aव्योम the PCI table from
 * growing *huge*, we use this function to collapse some 70 entries
 * in the PCI table पूर्णांकo one, क्रम sanity's and compactness's sake.
 */
अटल स्थिर अचिन्हित लघु समयdia_single_port[] = अणु
	0x4025, 0x4027, 0x4028, 0x5025, 0x5027, 0
पूर्ण;

अटल स्थिर अचिन्हित लघु समयdia_dual_port[] = अणु
	0x0002, 0x4036, 0x4037, 0x4038, 0x4078, 0x4079, 0x4085,
	0x4088, 0x4089, 0x5037, 0x5078, 0x5079, 0x5085, 0x6079,
	0x7079, 0x8079, 0x8137, 0x8138, 0x8237, 0x8238, 0x9079,
	0x9137, 0x9138, 0x9237, 0x9238, 0xA079, 0xB079, 0xC079,
	0xD079, 0
पूर्ण;

अटल स्थिर अचिन्हित लघु समयdia_quad_port[] = अणु
	0x4055, 0x4056, 0x4095, 0x4096, 0x5056, 0x8156, 0x8157,
	0x8256, 0x8257, 0x9056, 0x9156, 0x9157, 0x9158, 0x9159,
	0x9256, 0x9257, 0xA056, 0xA157, 0xA158, 0xA159, 0xB056,
	0xB157, 0
पूर्ण;

अटल स्थिर अचिन्हित लघु समयdia_eight_port[] = अणु
	0x4065, 0x4066, 0x5065, 0x5066, 0x8166, 0x9066, 0x9166,
	0x9167, 0x9168, 0xA066, 0xA167, 0xA168, 0
पूर्ण;

अटल स्थिर काष्ठा समयdia_काष्ठा अणु
	पूर्णांक num;
	स्थिर अचिन्हित लघु *ids;
पूर्ण समयdia_data[] = अणु
	अणु 1, समयdia_single_port पूर्ण,
	अणु 2, समयdia_dual_port पूर्ण,
	अणु 4, समयdia_quad_port पूर्ण,
	अणु 8, समयdia_eight_port पूर्ण
पूर्ण;

/*
 * There are nearly 70 dअगरferent Timedia/SUNIX PCI serial devices.  Instead of
 * listing them inभागidually, this driver merely grअसल them all with
 * PCI_ANY_ID.  Some of these devices, however, also feature a parallel port,
 * and should be left मुक्त to be claimed by parport_serial instead.
 */
अटल पूर्णांक pci_समयdia_probe(काष्ठा pci_dev *dev)
अणु
	/*
	 * Check the third digit of the subdevice ID
	 * (0,2,3,5,6: serial only -- 7,8,9: serial + parallel)
	 */
	अगर ((dev->subप्रणाली_device & 0x00f0) >= 0x70) अणु
		dev_info(&dev->dev,
			"ignoring Timedia subdevice %04x for parport_serial\n",
			dev->subप्रणाली_device);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_समयdia_init(काष्ठा pci_dev *dev)
अणु
	स्थिर अचिन्हित लघु *ids;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(समयdia_data); i++) अणु
		ids = समयdia_data[i].ids;
		क्रम (j = 0; ids[j]; j++)
			अगर (dev->subप्रणाली_device == ids[j])
				वापस समयdia_data[i].num;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Timedia/SUNIX uses a mixture of BARs and offsets
 * Ugh, this is ugly as all hell --- TYT
 */
अटल पूर्णांक
pci_समयdia_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar = 0, offset = board->first_offset;

	चयन (idx) अणु
	हाल 0:
		bar = 0;
		अवरोध;
	हाल 1:
		offset = board->uart_offset;
		bar = 0;
		अवरोध;
	हाल 2:
		bar = 1;
		अवरोध;
	हाल 3:
		offset = board->uart_offset;
		fallthrough;
	हाल 4: /* BAR 2 */
	हाल 5: /* BAR 3 */
	हाल 6: /* BAR 4 */
	हाल 7: /* BAR 5 */
		bar = idx - 2;
	पूर्ण

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

/*
 * Some Titan cards are also a little weird
 */
अटल पूर्णांक
titan_400l_800l_setup(काष्ठा serial_निजी *priv,
		      स्थिर काष्ठा pciserial_board *board,
		      काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset;

	चयन (idx) अणु
	हाल 0:
		bar = 1;
		अवरोध;
	हाल 1:
		bar = 2;
		अवरोध;
	शेष:
		bar = 4;
		offset = (idx - 2) * board->uart_offset;
	पूर्ण

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

अटल पूर्णांक pci_xircom_init(काष्ठा pci_dev *dev)
अणु
	msleep(100);
	वापस 0;
पूर्ण

अटल पूर्णांक pci_ni8420_init(काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *p;
	अचिन्हित पूर्णांक bar = 0;

	अगर ((pci_resource_flags(dev, bar) & IORESOURCE_MEM) == 0) अणु
		moan_device("no memory in bar", dev);
		वापस 0;
	पूर्ण

	p = pci_ioremap_bar(dev, bar);
	अगर (p == शून्य)
		वापस -ENOMEM;

	/* Enable CPU Interrupt */
	ग_लिखोl(पढ़ोl(p + NI8420_INT_ENABLE_REG) | NI8420_INT_ENABLE_BIT,
	       p + NI8420_INT_ENABLE_REG);

	iounmap(p);
	वापस 0;
पूर्ण

#घोषणा MITE_IOWBSR1_WSIZE	0xa
#घोषणा MITE_IOWBSR1_WIN_OFFSET	0x800
#घोषणा MITE_IOWBSR1_WENAB	(1 << 7)
#घोषणा MITE_LCIMR1_IO_IE_0	(1 << 24)
#घोषणा MITE_LCIMR2_SET_CPU_IE	(1 << 31)
#घोषणा MITE_IOWCR1_RAMSEL_MASK	0xfffffffe

अटल पूर्णांक pci_ni8430_init(काष्ठा pci_dev *dev)
अणु
	व्योम __iomem *p;
	काष्ठा pci_bus_region region;
	u32 device_winकरोw;
	अचिन्हित पूर्णांक bar = 0;

	अगर ((pci_resource_flags(dev, bar) & IORESOURCE_MEM) == 0) अणु
		moan_device("no memory in bar", dev);
		वापस 0;
	पूर्ण

	p = pci_ioremap_bar(dev, bar);
	अगर (p == शून्य)
		वापस -ENOMEM;

	/*
	 * Set device winकरोw address and size in BAR0, जबतक acknowledging that
	 * the resource काष्ठाure may contain a translated address that dअगरfers
	 * from the address the device responds to.
	 */
	pcibios_resource_to_bus(dev->bus, &region, &dev->resource[bar]);
	device_winकरोw = ((region.start + MITE_IOWBSR1_WIN_OFFSET) & 0xffffff00)
			| MITE_IOWBSR1_WENAB | MITE_IOWBSR1_WSIZE;
	ग_लिखोl(device_winकरोw, p + MITE_IOWBSR1);

	/* Set winकरोw access to go to RAMSEL IO address space */
	ग_लिखोl((पढ़ोl(p + MITE_IOWCR1) & MITE_IOWCR1_RAMSEL_MASK),
	       p + MITE_IOWCR1);

	/* Enable IO Bus Interrupt 0 */
	ग_लिखोl(MITE_LCIMR1_IO_IE_0, p + MITE_LCIMR1);

	/* Enable CPU Interrupt */
	ग_लिखोl(MITE_LCIMR2_SET_CPU_IE, p + MITE_LCIMR2);

	iounmap(p);
	वापस 0;
पूर्ण

/* UART Port Control Register */
#घोषणा NI8430_PORTCON	0x0f
#घोषणा NI8430_PORTCON_TXVR_ENABLE	(1 << 3)

अटल पूर्णांक
pci_ni8430_setup(काष्ठा serial_निजी *priv,
		 स्थिर काष्ठा pciserial_board *board,
		 काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	काष्ठा pci_dev *dev = priv->dev;
	व्योम __iomem *p;
	अचिन्हित पूर्णांक bar, offset = board->first_offset;

	अगर (idx >= board->num_ports)
		वापस 1;

	bar = FL_GET_BASE(board->flags);
	offset += idx * board->uart_offset;

	p = pci_ioremap_bar(dev, bar);
	अगर (!p)
		वापस -ENOMEM;

	/* enable the transceiver */
	ग_लिखोb(पढ़ोb(p + offset + NI8430_PORTCON) | NI8430_PORTCON_TXVR_ENABLE,
	       p + offset + NI8430_PORTCON);

	iounmap(p);

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

अटल पूर्णांक pci_neपंचांगos_9900_setup(काष्ठा serial_निजी *priv,
				स्थिर काष्ठा pciserial_board *board,
				काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar;

	अगर ((priv->dev->device != PCI_DEVICE_ID_NETMOS_9865) &&
	    (priv->dev->subप्रणाली_device & 0xff00) == 0x3000) अणु
		/* neपंचांगos apparently orders BARs by datasheet layout, so serial
		 * ports get BARs 0 and 3 (or 1 and 4 क्रम memmapped)
		 */
		bar = 3 * idx;

		वापस setup_port(priv, port, bar, 0, board->reg_shअगरt);
	पूर्ण अन्यथा अणु
		वापस pci_शेष_setup(priv, board, port, idx);
	पूर्ण
पूर्ण

/* the 99xx series comes with a range of device IDs and a variety
 * of capabilities:
 *
 * 9900 has varying capabilities and can cascade to sub-controllers
 *   (cascading should be purely पूर्णांकernal)
 * 9904 is hardwired with 4 serial ports
 * 9912 and 9922 are hardwired with 2 serial ports
 */
अटल पूर्णांक pci_neपंचांगos_9900_numports(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक c = dev->class;
	अचिन्हित पूर्णांक pi;
	अचिन्हित लघु sub_serports;

	pi = c & 0xff;

	अगर (pi == 2)
		वापस 1;

	अगर ((pi == 0) && (dev->device == PCI_DEVICE_ID_NETMOS_9900)) अणु
		/* two possibilities: 0x30ps encodes number of parallel and
		 * serial ports, or 0x1000 indicates *something*. This is not
		 * immediately obvious, since the 2s1p+4s configuration seems
		 * to offer all functionality on functions 0..2, जबतक still
		 * advertising the same function 3 as the 4s+2s1p config.
		 */
		sub_serports = dev->subप्रणाली_device & 0xf;
		अगर (sub_serports > 0)
			वापस sub_serports;

		dev_err(&dev->dev,
			"NetMos/Mostech serial driver ignoring port on ambiguous config.\n");
		वापस 0;
	पूर्ण

	moan_device("unknown NetMos/Mostech program interface", dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pci_neपंचांगos_init(काष्ठा pci_dev *dev)
अणु
	/* subdevice 0x00PS means <P> parallel, <S> serial */
	अचिन्हित पूर्णांक num_serial = dev->subप्रणाली_device & 0xf;

	अगर ((dev->device == PCI_DEVICE_ID_NETMOS_9901) ||
		(dev->device == PCI_DEVICE_ID_NETMOS_9865))
		वापस 0;

	अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_IBM &&
			dev->subप्रणाली_device == 0x0299)
		वापस 0;

	चयन (dev->device) अणु /* FALLTHROUGH on all */
	हाल PCI_DEVICE_ID_NETMOS_9904:
	हाल PCI_DEVICE_ID_NETMOS_9912:
	हाल PCI_DEVICE_ID_NETMOS_9922:
	हाल PCI_DEVICE_ID_NETMOS_9900:
		num_serial = pci_neपंचांगos_9900_numports(dev);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (num_serial == 0) अणु
		moan_device("unknown NetMos/Mostech device", dev);
		वापस -ENODEV;
	पूर्ण

	वापस num_serial;
पूर्ण

/*
 * These chips are available with optionally one parallel port and up to
 * two serial ports. Unक्रमtunately they all have the same product id.
 *
 * Basic configuration is करोne over a region of 32 I/O ports. The base
 * ioport is called INTA or INTC, depending on करोcs/other drivers.
 *
 * The region of the 32 I/O ports is configured in POSIO0R...
 */

/* रेजिस्टरs */
#घोषणा ITE_887x_MISCR		0x9c
#घोषणा ITE_887x_INTCBAR	0x78
#घोषणा ITE_887x_UARTBAR	0x7c
#घोषणा ITE_887x_PS0BAR		0x10
#घोषणा ITE_887x_POSIO0		0x60

/* I/O space size */
#घोषणा ITE_887x_IOSIZE		32
/* I/O space size (bits 26-24; 8 bytes = 011b) */
#घोषणा ITE_887x_POSIO_IOSIZE_8		(3 << 24)
/* I/O space size (bits 26-24; 32 bytes = 101b) */
#घोषणा ITE_887x_POSIO_IOSIZE_32	(5 << 24)
/* Decoding speed (1 = slow, 2 = medium, 3 = fast) */
#घोषणा ITE_887x_POSIO_SPEED		(3 << 29)
/* enable IO_Space bit */
#घोषणा ITE_887x_POSIO_ENABLE		(1 << 31)

अटल पूर्णांक pci_ite887x_init(काष्ठा pci_dev *dev)
अणु
	/* पूर्णांकa_addr are the configuration addresses of the ITE */
	अटल स्थिर लघु पूर्णांकa_addr[] = अणु 0x2a0, 0x2c0, 0x220, 0x240, 0x1e0,
							0x200, 0x280, 0 पूर्ण;
	पूर्णांक ret, i, type;
	काष्ठा resource *iobase = शून्य;
	u32 miscr, uartbar, ioport;

	/* search क्रम the base-ioport */
	i = 0;
	जबतक (पूर्णांकa_addr[i] && iobase == शून्य) अणु
		iobase = request_region(पूर्णांकa_addr[i], ITE_887x_IOSIZE,
								"ite887x");
		अगर (iobase != शून्य) अणु
			/* ग_लिखो POSIO0R - speed | size | ioport */
			pci_ग_लिखो_config_dword(dev, ITE_887x_POSIO0,
				ITE_887x_POSIO_ENABLE | ITE_887x_POSIO_SPEED |
				ITE_887x_POSIO_IOSIZE_32 | पूर्णांकa_addr[i]);
			/* ग_लिखो INTCBAR - ioport */
			pci_ग_लिखो_config_dword(dev, ITE_887x_INTCBAR,
								पूर्णांकa_addr[i]);
			ret = inb(पूर्णांकa_addr[i]);
			अगर (ret != 0xff) अणु
				/* ioport connected */
				अवरोध;
			पूर्ण
			release_region(iobase->start, ITE_887x_IOSIZE);
			iobase = शून्य;
		पूर्ण
		i++;
	पूर्ण

	अगर (!पूर्णांकa_addr[i]) अणु
		dev_err(&dev->dev, "ite887x: could not find iobase\n");
		वापस -ENODEV;
	पूर्ण

	/* start of unकरोcumented type checking (see parport_pc.c) */
	type = inb(iobase->start + 0x18) & 0x0f;

	चयन (type) अणु
	हाल 0x2:	/* ITE8871 (1P) */
	हाल 0xa:	/* ITE8875 (1P) */
		ret = 0;
		अवरोध;
	हाल 0xe:	/* ITE8872 (2S1P) */
		ret = 2;
		अवरोध;
	हाल 0x6:	/* ITE8873 (1S) */
		ret = 1;
		अवरोध;
	हाल 0x8:	/* ITE8874 (2S) */
		ret = 2;
		अवरोध;
	शेष:
		moan_device("Unknown ITE887x", dev);
		ret = -ENODEV;
	पूर्ण

	/* configure all serial ports */
	क्रम (i = 0; i < ret; i++) अणु
		/* पढ़ो the I/O port from the device */
		pci_पढ़ो_config_dword(dev, ITE_887x_PS0BAR + (0x4 * (i + 1)),
								&ioport);
		ioport &= 0x0000FF00;	/* the actual base address */
		pci_ग_लिखो_config_dword(dev, ITE_887x_POSIO0 + (0x4 * (i + 1)),
			ITE_887x_POSIO_ENABLE | ITE_887x_POSIO_SPEED |
			ITE_887x_POSIO_IOSIZE_8 | ioport);

		/* ग_लिखो the ioport to the UARTBAR */
		pci_पढ़ो_config_dword(dev, ITE_887x_UARTBAR, &uartbar);
		uartbar &= ~(0xffff << (16 * i));	/* clear half the reg */
		uartbar |= (ioport << (16 * i));	/* set the ioport */
		pci_ग_लिखो_config_dword(dev, ITE_887x_UARTBAR, uartbar);

		/* get current config */
		pci_पढ़ो_config_dword(dev, ITE_887x_MISCR, &miscr);
		/* disable पूर्णांकerrupts (UARTx_Routing[3:0]) */
		miscr &= ~(0xf << (12 - 4 * i));
		/* activate the UART (UARTx_En) */
		miscr |= 1 << (23 - i);
		/* ग_लिखो new config with activated UART */
		pci_ग_लिखो_config_dword(dev, ITE_887x_MISCR, miscr);
	पूर्ण

	अगर (ret <= 0) अणु
		/* the device has no UARTs अगर we get here */
		release_region(iobase->start, ITE_887x_IOSIZE);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pci_ite887x_निकास(काष्ठा pci_dev *dev)
अणु
	u32 ioport;
	/* the ioport is bit 0-15 in POSIO0R */
	pci_पढ़ो_config_dword(dev, ITE_887x_POSIO0, &ioport);
	ioport &= 0xffff;
	release_region(ioport, ITE_887x_IOSIZE);
पूर्ण

/*
 * EndRun Technologies.
 * Determine the number of ports available on the device.
 */
#घोषणा PCI_VENDOR_ID_ENDRUN			0x7401
#घोषणा PCI_DEVICE_ID_ENDRUN_1588	0xe100

अटल पूर्णांक pci_endrun_init(काष्ठा pci_dev *dev)
अणु
	u8 __iomem *p;
	अचिन्हित दीर्घ deviceID;
	अचिन्हित पूर्णांक  number_uarts = 0;

	/* EndRun device is all 0xexxx */
	अगर (dev->venकरोr == PCI_VENDOR_ID_ENDRUN &&
		(dev->device & 0xf000) != 0xe000)
		वापस 0;

	p = pci_iomap(dev, 0, 5);
	अगर (p == शून्य)
		वापस -ENOMEM;

	deviceID = ioपढ़ो32(p);
	/* EndRun device */
	अगर (deviceID == 0x07000200) अणु
		number_uarts = ioपढ़ो8(p + 4);
		dev_dbg(&dev->dev,
			"%d ports detected on EndRun PCI Express device\n",
			number_uarts);
	पूर्ण
	pci_iounmap(dev, p);
	वापस number_uarts;
पूर्ण

/*
 * Oxक्रमd Semiconductor Inc.
 * Check that device is part of the Tornaकरो range of devices, then determine
 * the number of ports available on the device.
 */
अटल पूर्णांक pci_oxsemi_tornaकरो_init(काष्ठा pci_dev *dev)
अणु
	u8 __iomem *p;
	अचिन्हित दीर्घ deviceID;
	अचिन्हित पूर्णांक  number_uarts = 0;

	/* OxSemi Tornaकरो devices are all 0xCxxx */
	अगर (dev->venकरोr == PCI_VENDOR_ID_OXSEMI &&
	    (dev->device & 0xF000) != 0xC000)
		वापस 0;

	p = pci_iomap(dev, 0, 5);
	अगर (p == शून्य)
		वापस -ENOMEM;

	deviceID = ioपढ़ो32(p);
	/* Tornaकरो device */
	अगर (deviceID == 0x07000200) अणु
		number_uarts = ioपढ़ो8(p + 4);
		dev_dbg(&dev->dev,
			"%d ports detected on Oxford PCI Express device\n",
			number_uarts);
	पूर्ण
	pci_iounmap(dev, p);
	वापस number_uarts;
पूर्ण

अटल पूर्णांक pci_asix_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->bugs |= UART_BUG_PARITY;
	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण

/* Quatech devices have their own extra पूर्णांकerface features */

काष्ठा quatech_feature अणु
	u16 devid;
	bool amcc;
पूर्ण;

#घोषणा QPCR_TEST_FOR1		0x3F
#घोषणा QPCR_TEST_GET1		0x00
#घोषणा QPCR_TEST_FOR2		0x40
#घोषणा QPCR_TEST_GET2		0x40
#घोषणा QPCR_TEST_FOR3		0x80
#घोषणा QPCR_TEST_GET3		0x40
#घोषणा QPCR_TEST_FOR4		0xC0
#घोषणा QPCR_TEST_GET4		0x80

#घोषणा QOPR_CLOCK_X1		0x0000
#घोषणा QOPR_CLOCK_X2		0x0001
#घोषणा QOPR_CLOCK_X4		0x0002
#घोषणा QOPR_CLOCK_X8		0x0003
#घोषणा QOPR_CLOCK_RATE_MASK	0x0003


अटल काष्ठा quatech_feature quatech_cards[] = अणु
	अणु PCI_DEVICE_ID_QUATECH_QSC100,   1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSC100,   1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSC100E,  0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSC200,   1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSC200E,  0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_ESC100D,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_ESC100M,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_QSCP100,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSCP100,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_QSCP200,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSCP200,  1 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_ESCLP100, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_QSCLP100, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSCLP100, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_SSCLP100, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_QSCLP200, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_DSCLP200, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_SSCLP200, 0 पूर्ण,
	अणु PCI_DEVICE_ID_QUATECH_SPPXP_100, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक pci_quatech_amcc(u16 devid)
अणु
	काष्ठा quatech_feature *qf = &quatech_cards[0];
	जबतक (qf->devid) अणु
		अगर (qf->devid == devid)
			वापस qf->amcc;
		qf++;
	पूर्ण
	pr_err("quatech: unknown port type '0x%04X'.\n", devid);
	वापस 0;
पूर्ण;

अटल पूर्णांक pci_quatech_rqopr(काष्ठा uart_8250_port *port)
अणु
	अचिन्हित दीर्घ base = port->port.iobase;
	u8 LCR, val;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	val = inb(base + UART_SCR);
	outb(LCR, base + UART_LCR);
	वापस val;
पूर्ण

अटल व्योम pci_quatech_wqopr(काष्ठा uart_8250_port *port, u8 qopr)
अणु
	अचिन्हित दीर्घ base = port->port.iobase;
	u8 LCR;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	inb(base + UART_SCR);
	outb(qopr, base + UART_SCR);
	outb(LCR, base + UART_LCR);
पूर्ण

अटल पूर्णांक pci_quatech_rqmcr(काष्ठा uart_8250_port *port)
अणु
	अचिन्हित दीर्घ base = port->port.iobase;
	u8 LCR, val, qmcr;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	val = inb(base + UART_SCR);
	outb(val | 0x10, base + UART_SCR);
	qmcr = inb(base + UART_MCR);
	outb(val, base + UART_SCR);
	outb(LCR, base + UART_LCR);

	वापस qmcr;
पूर्ण

अटल व्योम pci_quatech_wqmcr(काष्ठा uart_8250_port *port, u8 qmcr)
अणु
	अचिन्हित दीर्घ base = port->port.iobase;
	u8 LCR, val;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	val = inb(base + UART_SCR);
	outb(val | 0x10, base + UART_SCR);
	outb(qmcr, base + UART_MCR);
	outb(val, base + UART_SCR);
	outb(LCR, base + UART_LCR);
पूर्ण

अटल पूर्णांक pci_quatech_has_qmcr(काष्ठा uart_8250_port *port)
अणु
	अचिन्हित दीर्घ base = port->port.iobase;
	u8 LCR, val;

	LCR = inb(base + UART_LCR);
	outb(0xBF, base + UART_LCR);
	val = inb(base + UART_SCR);
	अगर (val & 0x20) अणु
		outb(0x80, UART_LCR);
		अगर (!(inb(UART_SCR) & 0x20)) अणु
			outb(LCR, base + UART_LCR);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pci_quatech_test(काष्ठा uart_8250_port *port)
अणु
	u8 reg, qopr;

	qopr = pci_quatech_rqopr(port);
	pci_quatech_wqopr(port, qopr & QPCR_TEST_FOR1);
	reg = pci_quatech_rqopr(port) & 0xC0;
	अगर (reg != QPCR_TEST_GET1)
		वापस -EINVAL;
	pci_quatech_wqopr(port, (qopr & QPCR_TEST_FOR1)|QPCR_TEST_FOR2);
	reg = pci_quatech_rqopr(port) & 0xC0;
	अगर (reg != QPCR_TEST_GET2)
		वापस -EINVAL;
	pci_quatech_wqopr(port, (qopr & QPCR_TEST_FOR1)|QPCR_TEST_FOR3);
	reg = pci_quatech_rqopr(port) & 0xC0;
	अगर (reg != QPCR_TEST_GET3)
		वापस -EINVAL;
	pci_quatech_wqopr(port, (qopr & QPCR_TEST_FOR1)|QPCR_TEST_FOR4);
	reg = pci_quatech_rqopr(port) & 0xC0;
	अगर (reg != QPCR_TEST_GET4)
		वापस -EINVAL;

	pci_quatech_wqopr(port, qopr);
	वापस 0;
पूर्ण

अटल पूर्णांक pci_quatech_घड़ी(काष्ठा uart_8250_port *port)
अणु
	u8 qopr, reg, set;
	अचिन्हित दीर्घ घड़ी;

	अगर (pci_quatech_test(port) < 0)
		वापस 1843200;

	qopr = pci_quatech_rqopr(port);

	pci_quatech_wqopr(port, qopr & ~QOPR_CLOCK_X8);
	reg = pci_quatech_rqopr(port);
	अगर (reg & QOPR_CLOCK_X8) अणु
		घड़ी = 1843200;
		जाओ out;
	पूर्ण
	pci_quatech_wqopr(port, qopr | QOPR_CLOCK_X8);
	reg = pci_quatech_rqopr(port);
	अगर (!(reg & QOPR_CLOCK_X8)) अणु
		घड़ी = 1843200;
		जाओ out;
	पूर्ण
	reg &= QOPR_CLOCK_X8;
	अगर (reg == QOPR_CLOCK_X2) अणु
		घड़ी =  3685400;
		set = QOPR_CLOCK_X2;
	पूर्ण अन्यथा अगर (reg == QOPR_CLOCK_X4) अणु
		घड़ी = 7372800;
		set = QOPR_CLOCK_X4;
	पूर्ण अन्यथा अगर (reg == QOPR_CLOCK_X8) अणु
		घड़ी = 14745600;
		set = QOPR_CLOCK_X8;
	पूर्ण अन्यथा अणु
		घड़ी = 1843200;
		set = QOPR_CLOCK_X1;
	पूर्ण
	qopr &= ~QOPR_CLOCK_RATE_MASK;
	qopr |= set;

out:
	pci_quatech_wqopr(port, qopr);
	वापस घड़ी;
पूर्ण

अटल पूर्णांक pci_quatech_rs422(काष्ठा uart_8250_port *port)
अणु
	u8 qmcr;
	पूर्णांक rs422 = 0;

	अगर (!pci_quatech_has_qmcr(port))
		वापस 0;
	qmcr = pci_quatech_rqmcr(port);
	pci_quatech_wqmcr(port, 0xFF);
	अगर (pci_quatech_rqmcr(port))
		rs422 = 1;
	pci_quatech_wqmcr(port, qmcr);
	वापस rs422;
पूर्ण

अटल पूर्णांक pci_quatech_init(काष्ठा pci_dev *dev)
अणु
	अगर (pci_quatech_amcc(dev->device)) अणु
		अचिन्हित दीर्घ base = pci_resource_start(dev, 0);
		अगर (base) अणु
			u32 पंचांगp;

			outl(inl(base + 0x38) | 0x00002000, base + 0x38);
			पंचांगp = inl(base + 0x3c);
			outl(पंचांगp | 0x01000000, base + 0x3c);
			outl(पंचांगp &= ~0x01000000, base + 0x3c);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pci_quatech_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	/* Needed by pci_quatech calls below */
	port->port.iobase = pci_resource_start(priv->dev, FL_GET_BASE(board->flags));
	/* Set up the घड़ीing */
	port->port.uartclk = pci_quatech_घड़ी(port);
	/* For now just warn about RS422 */
	अगर (pci_quatech_rs422(port))
		pr_warn("quatech: software control of RS422 features not currently supported.\n");
	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण

अटल व्योम pci_quatech_निकास(काष्ठा pci_dev *dev)
अणु
पूर्ण

अटल पूर्णांक pci_शेष_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset, maxnr;

	bar = FL_GET_BASE(board->flags);
	अगर (board->flags & FL_BASE_BARS)
		bar += idx;
	अन्यथा
		offset += idx * board->uart_offset;

	maxnr = (pci_resource_len(priv->dev, bar) - board->first_offset) >>
		(board->reg_shअगरt + 3);

	अगर (board->flags & FL_REGION_SZ_CAP && idx >= maxnr)
		वापस 1;

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण
अटल व्योम
pericom_करो_set_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
			       अचिन्हित पूर्णांक quot, अचिन्हित पूर्णांक quot_frac)
अणु
	पूर्णांक scr;
	पूर्णांक lcr;
	पूर्णांक actual_baud;
	पूर्णांक tolerance;

	क्रम (scr = 5 ; scr <= 15 ; scr++) अणु
		actual_baud = 921600 * 16 / scr;
		tolerance = actual_baud / 50;

		अगर ((baud < actual_baud + tolerance) &&
			(baud > actual_baud - tolerance)) अणु

			lcr = serial_port_in(port, UART_LCR);
			serial_port_out(port, UART_LCR, lcr | 0x80);

			serial_port_out(port, UART_DLL, 1);
			serial_port_out(port, UART_DLM, 0);
			serial_port_out(port, 2, 16 - scr);
			serial_port_out(port, UART_LCR, lcr);
			वापस;
		पूर्ण अन्यथा अगर (baud > actual_baud) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	serial8250_करो_set_भागisor(port, baud, quot, quot_frac);
पूर्ण
अटल पूर्णांक pci_pericom_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset, maxnr;

	bar = FL_GET_BASE(board->flags);
	अगर (board->flags & FL_BASE_BARS)
		bar += idx;
	अन्यथा
		offset += idx * board->uart_offset;


	maxnr = (pci_resource_len(priv->dev, bar) - board->first_offset) >>
		(board->reg_shअगरt + 3);

	अगर (board->flags & FL_REGION_SZ_CAP && idx >= maxnr)
		वापस 1;

	port->port.set_भागisor = pericom_करो_set_भागisor;

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

अटल पूर्णांक pci_pericom_setup_four_at_eight(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar, offset = board->first_offset, maxnr;

	bar = FL_GET_BASE(board->flags);
	अगर (board->flags & FL_BASE_BARS)
		bar += idx;
	अन्यथा
		offset += idx * board->uart_offset;

	अगर (idx==3)
		offset = 0x38;

	maxnr = (pci_resource_len(priv->dev, bar) - board->first_offset) >>
		(board->reg_shअगरt + 3);

	अगर (board->flags & FL_REGION_SZ_CAP && idx >= maxnr)
		वापस 1;

	port->port.set_भागisor = pericom_करो_set_भागisor;

	वापस setup_port(priv, port, bar, offset, board->reg_shअगरt);
पूर्ण

अटल पूर्णांक
ce4100_serial_setup(काष्ठा serial_निजी *priv,
		  स्थिर काष्ठा pciserial_board *board,
		  काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	पूर्णांक ret;

	ret = setup_port(priv, port, idx, 0, board->reg_shअगरt);
	port->port.iotype = UPIO_MEM32;
	port->port.type = PORT_XSCALE;
	port->port.flags = (port->port.flags | UPF_FIXED_PORT | UPF_FIXED_TYPE);
	port->port.regshअगरt = 2;

	वापस ret;
पूर्ण

अटल पूर्णांक
pci_omegapci_setup(काष्ठा serial_निजी *priv,
		      स्थिर काष्ठा pciserial_board *board,
		      काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	वापस setup_port(priv, port, 2, idx * 8, 0);
पूर्ण

अटल पूर्णांक
pci_brcm_trumanage_setup(काष्ठा serial_निजी *priv,
			 स्थिर काष्ठा pciserial_board *board,
			 काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	पूर्णांक ret = pci_शेष_setup(priv, board, port, idx);

	port->port.type = PORT_BRCM_TRUMANAGE;
	port->port.flags = (port->port.flags | UPF_FIXED_PORT | UPF_FIXED_TYPE);
	वापस ret;
पूर्ण

/* RTS will control by MCR अगर this bit is 0 */
#घोषणा FINTEK_RTS_CONTROL_BY_HW	BIT(4)
/* only worked with FINTEK_RTS_CONTROL_BY_HW on */
#घोषणा FINTEK_RTS_INVERT		BIT(5)

/* We should करो proper H/W transceiver setting beक्रमe change to RS485 mode */
अटल पूर्णांक pci_fपूर्णांकek_rs485_config(काष्ठा uart_port *port,
			       काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(port->dev);
	u8 setting;
	u8 *index = (u8 *) port->निजी_data;

	pci_पढ़ो_config_byte(pci_dev, 0x40 + 8 * *index + 7, &setting);

	अगर (!rs485)
		rs485 = &port->rs485;
	अन्यथा अगर (rs485->flags & SER_RS485_ENABLED)
		स_रखो(rs485->padding, 0, माप(rs485->padding));
	अन्यथा
		स_रखो(rs485, 0, माप(*rs485));

	/* F81504/508/512 not support RTS delay beक्रमe or after send */
	rs485->flags &= SER_RS485_ENABLED | SER_RS485_RTS_ON_SEND;

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		/* Enable RTS H/W control mode */
		setting |= FINTEK_RTS_CONTROL_BY_HW;

		अगर (rs485->flags & SER_RS485_RTS_ON_SEND) अणु
			/* RTS driving high on TX */
			setting &= ~FINTEK_RTS_INVERT;
		पूर्ण अन्यथा अणु
			/* RTS driving low on TX */
			setting |= FINTEK_RTS_INVERT;
		पूर्ण

		rs485->delay_rts_after_send = 0;
		rs485->delay_rts_beक्रमe_send = 0;
	पूर्ण अन्यथा अणु
		/* Disable RTS H/W control mode */
		setting &= ~(FINTEK_RTS_CONTROL_BY_HW | FINTEK_RTS_INVERT);
	पूर्ण

	pci_ग_लिखो_config_byte(pci_dev, 0x40 + 8 * *index + 7, setting);

	अगर (rs485 != &port->rs485)
		port->rs485 = *rs485;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_fपूर्णांकek_setup(काष्ठा serial_निजी *priv,
			    स्थिर काष्ठा pciserial_board *board,
			    काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	काष्ठा pci_dev *pdev = priv->dev;
	u8 *data;
	u8 config_base;
	u16 iobase;

	config_base = 0x40 + 0x08 * idx;

	/* Get the io address from configuration space */
	pci_पढ़ो_config_word(pdev, config_base + 4, &iobase);

	dev_dbg(&pdev->dev, "%s: idx=%d iobase=0x%x", __func__, idx, iobase);

	port->port.iotype = UPIO_PORT;
	port->port.iobase = iobase;
	port->port.rs485_config = pci_fपूर्णांकek_rs485_config;

	data = devm_kzalloc(&pdev->dev, माप(u8), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* preserve index in PCI configuration space */
	*data = idx;
	port->port.निजी_data = data;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_fपूर्णांकek_init(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ iobase;
	u32 max_port, i;
	resource_माप_प्रकार bar_data[3];
	u8 config_base;
	काष्ठा serial_निजी *priv = pci_get_drvdata(dev);
	काष्ठा uart_8250_port *port;

	अगर (!(pci_resource_flags(dev, 5) & IORESOURCE_IO) ||
			!(pci_resource_flags(dev, 4) & IORESOURCE_IO) ||
			!(pci_resource_flags(dev, 3) & IORESOURCE_IO))
		वापस -ENODEV;

	चयन (dev->device) अणु
	हाल 0x1104: /* 4 ports */
	हाल 0x1108: /* 8 ports */
		max_port = dev->device & 0xff;
		अवरोध;
	हाल 0x1112: /* 12 ports */
		max_port = 12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Get the io address dispatch from the BIOS */
	bar_data[0] = pci_resource_start(dev, 5);
	bar_data[1] = pci_resource_start(dev, 4);
	bar_data[2] = pci_resource_start(dev, 3);

	क्रम (i = 0; i < max_port; ++i) अणु
		/* UART0 configuration offset start from 0x40 */
		config_base = 0x40 + 0x08 * i;

		/* Calculate Real IO Port */
		iobase = (bar_data[i / 4] & 0xffffffe0) + (i % 4) * 8;

		/* Enable UART I/O port */
		pci_ग_लिखो_config_byte(dev, config_base + 0x00, 0x01);

		/* Select 128-byte FIFO and 8x FIFO threshold */
		pci_ग_लिखो_config_byte(dev, config_base + 0x01, 0x33);

		/* LSB UART */
		pci_ग_लिखो_config_byte(dev, config_base + 0x04,
				(u8)(iobase & 0xff));

		/* MSB UART */
		pci_ग_लिखो_config_byte(dev, config_base + 0x05,
				(u8)((iobase & 0xff00) >> 8));

		pci_ग_लिखो_config_byte(dev, config_base + 0x06, dev->irq);

		अगर (priv) अणु
			/* re-apply RS232/485 mode when
			 * pciserial_resume_ports()
			 */
			port = serial8250_get_port(priv->line[i]);
			pci_fपूर्णांकek_rs485_config(&port->port, शून्य);
		पूर्ण अन्यथा अणु
			/* First init without port data
			 * क्रमce init to RS232 Mode
			 */
			pci_ग_लिखो_config_byte(dev, config_base + 0x07, 0x01);
		पूर्ण
	पूर्ण

	वापस max_port;
पूर्ण

अटल व्योम f815xxa_mem_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा f815xxa_data *data = p->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data->lock, flags);
	ग_लिखोb(value, p->membase + offset);
	पढ़ोb(p->membase + UART_SCR); /* Dummy पढ़ो क्रम flush pcie tx queue */
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल पूर्णांक pci_fपूर्णांकek_f815xxa_setup(काष्ठा serial_निजी *priv,
			    स्थिर काष्ठा pciserial_board *board,
			    काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	काष्ठा pci_dev *pdev = priv->dev;
	काष्ठा f815xxa_data *data;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->idx = idx;
	spin_lock_init(&data->lock);

	port->port.निजी_data = data;
	port->port.iotype = UPIO_MEM;
	port->port.flags |= UPF_IOREMAP;
	port->port.mapbase = pci_resource_start(pdev, 0) + 8 * idx;
	port->port.serial_out = f815xxa_mem_serial_out;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_fपूर्णांकek_f815xxa_init(काष्ठा pci_dev *dev)
अणु
	u32 max_port, i;
	पूर्णांक config_base;

	अगर (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM))
		वापस -ENODEV;

	चयन (dev->device) अणु
	हाल 0x1204: /* 4 ports */
	हाल 0x1208: /* 8 ports */
		max_port = dev->device & 0xff;
		अवरोध;
	हाल 0x1212: /* 12 ports */
		max_port = 12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set to mmio decode */
	pci_ग_लिखो_config_byte(dev, 0x209, 0x40);

	क्रम (i = 0; i < max_port; ++i) अणु
		/* UART0 configuration offset start from 0x2A0 */
		config_base = 0x2A0 + 0x08 * i;

		/* Select 128-byte FIFO and 8x FIFO threshold */
		pci_ग_लिखो_config_byte(dev, config_base + 0x01, 0x33);

		/* Enable UART I/O port */
		pci_ग_लिखो_config_byte(dev, config_base + 0, 0x01);
	पूर्ण

	वापस max_port;
पूर्ण

अटल पूर्णांक skip_tx_en_setup(काष्ठा serial_निजी *priv,
			स्थिर काष्ठा pciserial_board *board,
			काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->port.quirks |= UPQ_NO_TXEN_TEST;
	dev_dbg(&priv->dev->dev,
		"serial8250: skipping TxEn test for device [%04x:%04x] subsystem [%04x:%04x]\n",
		priv->dev->venकरोr, priv->dev->device,
		priv->dev->subप्रणाली_venकरोr, priv->dev->subप्रणाली_device);

	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण

अटल व्योम kt_handle_अवरोध(काष्ठा uart_port *p)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	/*
	 * On receipt of a BI, serial device in Intel ME (Intel
	 * management engine) needs to have its fअगरos cleared क्रम sane
	 * SOL (Serial Over Lan) output.
	 */
	serial8250_clear_and_reinit_fअगरos(up);
पूर्ण

अटल अचिन्हित पूर्णांक kt_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	अचिन्हित पूर्णांक val;

	/*
	 * When the Intel ME (management engine) माला_लो reset its serial
	 * port रेजिस्टरs could वापस 0 momentarily.  Functions like
	 * serial8250_console_ग_लिखो, पढ़ो and save the IER, perक्रमm
	 * some operation and then restore it.  In order to aव्योम
	 * setting IER रेजिस्टर inadvertently to 0, अगर the value पढ़ो
	 * is 0, द्विगुन check with ier value in uart_8250_port and use
	 * that instead.  up->ier should be the same value as what is
	 * currently configured.
	 */
	val = inb(p->iobase + offset);
	अगर (offset == UART_IER) अणु
		अगर (val == 0)
			val = up->ier;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक kt_serial_setup(काष्ठा serial_निजी *priv,
			   स्थिर काष्ठा pciserial_board *board,
			   काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->port.flags |= UPF_BUG_THRE;
	port->port.serial_in = kt_serial_in;
	port->port.handle_अवरोध = kt_handle_अवरोध;
	वापस skip_tx_en_setup(priv, board, port, idx);
पूर्ण

अटल पूर्णांक pci_eg20t_init(काष्ठा pci_dev *dev)
अणु
#अगर defined(CONFIG_SERIAL_PCH_UART) || defined(CONFIG_SERIAL_PCH_UART_MODULE)
	वापस -ENODEV;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
pci_wch_ch353_setup(काष्ठा serial_निजी *priv,
		    स्थिर काष्ठा pciserial_board *board,
		    काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->port.flags |= UPF_FIXED_TYPE;
	port->port.type = PORT_16550A;
	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण

अटल पूर्णांक
pci_wch_ch355_setup(काष्ठा serial_निजी *priv,
		स्थिर काष्ठा pciserial_board *board,
		काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->port.flags |= UPF_FIXED_TYPE;
	port->port.type = PORT_16550A;
	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण

अटल पूर्णांक
pci_wch_ch38x_setup(काष्ठा serial_निजी *priv,
		    स्थिर काष्ठा pciserial_board *board,
		    काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	port->port.flags |= UPF_FIXED_TYPE;
	port->port.type = PORT_16850;
	वापस pci_शेष_setup(priv, board, port, idx);
पूर्ण


#घोषणा CH384_XINT_ENABLE_REG   0xEB
#घोषणा CH384_XINT_ENABLE_BIT   0x02

अटल पूर्णांक pci_wch_ch38x_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक max_port;
	अचिन्हित दीर्घ iobase;


	चयन (dev->device) अणु
	हाल 0x3853: /* 8 ports */
		max_port = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	iobase = pci_resource_start(dev, 0);
	outb(CH384_XINT_ENABLE_BIT, iobase + CH384_XINT_ENABLE_REG);

	वापस max_port;
पूर्ण

अटल व्योम pci_wch_ch38x_निकास(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ iobase;

	iobase = pci_resource_start(dev, 0);
	outb(0x0, iobase + CH384_XINT_ENABLE_REG);
पूर्ण


अटल पूर्णांक
pci_sunix_setup(काष्ठा serial_निजी *priv,
		स्थिर काष्ठा pciserial_board *board,
		काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	पूर्णांक bar;
	पूर्णांक offset;

	port->port.flags |= UPF_FIXED_TYPE;
	port->port.type = PORT_SUNIX;

	अगर (idx < 4) अणु
		bar = 0;
		offset = idx * board->uart_offset;
	पूर्ण अन्यथा अणु
		bar = 1;
		idx -= 4;
		idx = भाग_s64_rem(idx, 4, &offset);
		offset = idx * 64 + offset * board->uart_offset;
	पूर्ण

	वापस setup_port(priv, port, bar, offset, 0);
पूर्ण

अटल पूर्णांक
pci_moxa_setup(काष्ठा serial_निजी *priv,
		स्थिर काष्ठा pciserial_board *board,
		काष्ठा uart_8250_port *port, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक bar = FL_GET_BASE(board->flags);
	पूर्णांक offset;

	अगर (board->num_ports == 4 && idx == 3)
		offset = 7 * board->uart_offset;
	अन्यथा
		offset = idx * board->uart_offset;

	वापस setup_port(priv, port, bar, offset, 0);
पूर्ण

#घोषणा PCI_VENDOR_ID_SBSMODULARIO	0x124B
#घोषणा PCI_SUBVENDOR_ID_SBSMODULARIO	0x124B
#घोषणा PCI_DEVICE_ID_OCTPRO		0x0001
#घोषणा PCI_SUBDEVICE_ID_OCTPRO232	0x0108
#घोषणा PCI_SUBDEVICE_ID_OCTPRO422	0x0208
#घोषणा PCI_SUBDEVICE_ID_POCTAL232	0x0308
#घोषणा PCI_SUBDEVICE_ID_POCTAL422	0x0408
#घोषणा PCI_SUBDEVICE_ID_SIIG_DUAL_00	0x2500
#घोषणा PCI_SUBDEVICE_ID_SIIG_DUAL_30	0x2530
#घोषणा PCI_VENDOR_ID_ADVANTECH		0x13fe
#घोषणा PCI_DEVICE_ID_INTEL_CE4100_UART 0x2e66
#घोषणा PCI_DEVICE_ID_ADVANTECH_PCI3620	0x3620
#घोषणा PCI_DEVICE_ID_ADVANTECH_PCI3618	0x3618
#घोषणा PCI_DEVICE_ID_ADVANTECH_PCIf618	0xf618
#घोषणा PCI_DEVICE_ID_TITAN_200I	0x8028
#घोषणा PCI_DEVICE_ID_TITAN_400I	0x8048
#घोषणा PCI_DEVICE_ID_TITAN_800I	0x8088
#घोषणा PCI_DEVICE_ID_TITAN_800EH	0xA007
#घोषणा PCI_DEVICE_ID_TITAN_800EHB	0xA008
#घोषणा PCI_DEVICE_ID_TITAN_400EH	0xA009
#घोषणा PCI_DEVICE_ID_TITAN_100E	0xA010
#घोषणा PCI_DEVICE_ID_TITAN_200E	0xA012
#घोषणा PCI_DEVICE_ID_TITAN_400E	0xA013
#घोषणा PCI_DEVICE_ID_TITAN_800E	0xA014
#घोषणा PCI_DEVICE_ID_TITAN_200EI	0xA016
#घोषणा PCI_DEVICE_ID_TITAN_200EISI	0xA017
#घोषणा PCI_DEVICE_ID_TITAN_200V3	0xA306
#घोषणा PCI_DEVICE_ID_TITAN_400V3	0xA310
#घोषणा PCI_DEVICE_ID_TITAN_410V3	0xA312
#घोषणा PCI_DEVICE_ID_TITAN_800V3	0xA314
#घोषणा PCI_DEVICE_ID_TITAN_800V3B	0xA315
#घोषणा PCI_DEVICE_ID_OXSEMI_16PCI958	0x9538
#घोषणा PCIE_DEVICE_ID_NEO_2_OX_IBM	0x00F6
#घोषणा PCI_DEVICE_ID_PLX_CRONYX_OMEGA	0xc001
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_KT 0x1d3d
#घोषणा PCI_VENDOR_ID_WCH		0x4348
#घोषणा PCI_DEVICE_ID_WCH_CH352_2S	0x3253
#घोषणा PCI_DEVICE_ID_WCH_CH353_4S	0x3453
#घोषणा PCI_DEVICE_ID_WCH_CH353_2S1PF	0x5046
#घोषणा PCI_DEVICE_ID_WCH_CH353_1S1P	0x5053
#घोषणा PCI_DEVICE_ID_WCH_CH353_2S1P	0x7053
#घोषणा PCI_DEVICE_ID_WCH_CH355_4S	0x7173
#घोषणा PCI_VENDOR_ID_AGESTAR		0x5372
#घोषणा PCI_DEVICE_ID_AGESTAR_9375	0x6872
#घोषणा PCI_VENDOR_ID_ASIX		0x9710
#घोषणा PCI_DEVICE_ID_BROADCOM_TRUMANAGE 0x160a
#घोषणा PCI_DEVICE_ID_AMCC_ADDIDATA_APCI7800 0x818e

#घोषणा PCIE_VENDOR_ID_WCH		0x1c00
#घोषणा PCIE_DEVICE_ID_WCH_CH382_2S1P	0x3250
#घोषणा PCIE_DEVICE_ID_WCH_CH384_4S	0x3470
#घोषणा PCIE_DEVICE_ID_WCH_CH384_8S	0x3853
#घोषणा PCIE_DEVICE_ID_WCH_CH382_2S	0x3253

#घोषणा PCI_VENDOR_ID_ACCESIO			0x494f
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_2SDB	0x1051
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM_2S	0x1053
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SDB	0x105C
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4S	0x105E
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM232_2DB	0x1091
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM232_2	0x1093
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4DB	0x1099
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM232_4	0x109B
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_2SMDB	0x10D1
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM_2SM	0x10D3
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SMDB	0x10DA
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4SM	0x10DC
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_1	0x1108
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM422_2	0x1110
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_2	0x1111
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM422_4	0x1118
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_4	0x1119
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM_2S	0x1152
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4S	0x115A
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM232_2	0x1190
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM232_2	0x1191
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM232_4	0x1198
#घोषणा PCI_DEVICE_ID_ACCESIO_MPCIE_ICM232_4	0x1199
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM_2SM	0x11D0
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM422_4	0x105A
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM485_4	0x105B
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM422_8	0x106A
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM485_8	0x106B
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4	0x1098
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM232_8	0x10A9
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SM	0x10D9
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_COM_8SM	0x10E9
#घोषणा PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4SM	0x11D8


#घोषणा	PCI_DEVICE_ID_MOXA_CP102E	0x1024
#घोषणा	PCI_DEVICE_ID_MOXA_CP102EL	0x1025
#घोषणा	PCI_DEVICE_ID_MOXA_CP104EL_A	0x1045
#घोषणा	PCI_DEVICE_ID_MOXA_CP114EL	0x1144
#घोषणा	PCI_DEVICE_ID_MOXA_CP116E_A_A	0x1160
#घोषणा	PCI_DEVICE_ID_MOXA_CP116E_A_B	0x1161
#घोषणा	PCI_DEVICE_ID_MOXA_CP118EL_A	0x1182
#घोषणा	PCI_DEVICE_ID_MOXA_CP118E_A_I	0x1183
#घोषणा	PCI_DEVICE_ID_MOXA_CP132EL	0x1322
#घोषणा	PCI_DEVICE_ID_MOXA_CP134EL_A	0x1342
#घोषणा	PCI_DEVICE_ID_MOXA_CP138E_A	0x1381
#घोषणा	PCI_DEVICE_ID_MOXA_CP168EL_A	0x1683

/* Unknown venकरोrs/cards - this should not be in linux/pci_ids.h */
#घोषणा PCI_SUBDEVICE_ID_UNKNOWN_0x1584	0x1584
#घोषणा PCI_SUBDEVICE_ID_UNKNOWN_0x1588	0x1588

/*
 * Master list of serial port init/setup/निकास quirks.
 * This करोes not describe the general nature of the port.
 * (ie, baud base, number and location of ports, etc)
 *
 * This list is ordered alphabetically by venकरोr then device.
 * Specअगरic entries must come beक्रमe more generic entries.
 */
अटल काष्ठा pci_serial_quirk pci_serial_quirks[] = अणु
	/*
	* ADDI-DATA GmbH communication cards <info@addi-data.com>
	*/
	अणु
		.venकरोr         = PCI_VENDOR_ID_AMCC,
		.device         = PCI_DEVICE_ID_AMCC_ADDIDATA_APCI7800,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = addidata_apci7800_setup,
	पूर्ण,
	/*
	 * AFAVLAB cards - these may be called via parport_serial
	 *  It is not clear whether this applies to all products.
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_AFAVLAB,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= afavlab_setup,
	पूर्ण,
	/*
	 * HP Diva
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_HP,
		.device		= PCI_DEVICE_ID_HP_DIVA,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_hp_भागa_init,
		.setup		= pci_hp_भागa_setup,
	पूर्ण,
	/*
	 * HPE PCI serial device
	 */
	अणु
		.venकरोr         = PCI_VENDOR_ID_HP_3PAR,
		.device         = PCI_DEVICE_ID_HPE_PCI_SERIAL,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup		= pci_hp_भागa_setup,
	पूर्ण,
	/*
	 * Intel
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_80960_RP,
		.subvenकरोr	= 0xe4bf,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_पूर्णांकeli960ni_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_8257X_SOL,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= skip_tx_en_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_82573L_SOL,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= skip_tx_en_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_82573E_SOL,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= skip_tx_en_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_CE4100_UART,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= ce4100_serial_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_INTEL,
		.device		= PCI_DEVICE_ID_INTEL_PATSBURG_KT,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= kt_serial_setup,
	पूर्ण,
	/*
	 * ITE
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_ITE,
		.device		= PCI_DEVICE_ID_ITE_8872,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ite887x_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ite887x_निकास,
	पूर्ण,
	/*
	 * National Instruments
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI23216,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI2328,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI2324,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI2322,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI2324I,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PCI2322I,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8420_23216,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8420_2328,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8420_2324,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8420_2322,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8422_2324,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_DEVICE_ID_NI_PXI8422_2322,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8420_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_ni8420_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_NI,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_ni8430_init,
		.setup		= pci_ni8430_setup,
		.निकास		= pci_ni8430_निकास,
	पूर्ण,
	/* Quatech */
	अणु
		.venकरोr		= PCI_VENDOR_ID_QUATECH,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_quatech_init,
		.setup		= pci_quatech_setup,
		.निकास		= pci_quatech_निकास,
	पूर्ण,
	/*
	 * Panacom
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_PANACOM,
		.device		= PCI_DEVICE_ID_PANACOM_QUADMODEM,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_plx9050_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_plx9050_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_PANACOM,
		.device		= PCI_DEVICE_ID_PANACOM_DUALMODEM,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_plx9050_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_plx9050_निकास,
	पूर्ण,
	/*
	 * Pericom (Only 7954 - It have a offset jump क्रम port 4)
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_PERICOM,
		.device		= PCI_DEVICE_ID_PERICOM_PI7C9X7954,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_pericom_setup_four_at_eight,
	पूर्ण,
	/*
	 * PLX
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= PCI_DEVICE_ID_PLX_9050,
		.subvenकरोr	= PCI_SUBVENDOR_ID_EXSYS,
		.subdevice	= PCI_SUBDEVICE_ID_EXSYS_4055,
		.init		= pci_plx9050_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_plx9050_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= PCI_DEVICE_ID_PLX_9050,
		.subvenकरोr	= PCI_SUBVENDOR_ID_KEYSPAN,
		.subdevice	= PCI_SUBDEVICE_ID_KEYSPAN_SX2,
		.init		= pci_plx9050_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_plx9050_निकास,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= PCI_DEVICE_ID_PLX_ROMULUS,
		.subvenकरोr	= PCI_VENDOR_ID_PLX,
		.subdevice	= PCI_DEVICE_ID_PLX_ROMULUS,
		.init		= pci_plx9050_init,
		.setup		= pci_शेष_setup,
		.निकास		= pci_plx9050_निकास,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SDB,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4S,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4DB,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_COM232_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SMDB,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4SM,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_ICM422_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4S,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_ICM232_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_MPCIE_ICM232_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM422_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM485_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SM,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4SM,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup_four_at_eight,
	पूर्ण,
	अणु
		.venकरोr     = PCI_VENDOR_ID_ACCESIO,
		.device     = PCI_ANY_ID,
		.subvenकरोr  = PCI_ANY_ID,
		.subdevice  = PCI_ANY_ID,
		.setup      = pci_pericom_setup,
	पूर्ण,	/*
	 * SBS Technologies, Inc., PMC-OCTALPRO 232
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SBSMODULARIO,
		.device		= PCI_DEVICE_ID_OCTPRO,
		.subvenकरोr	= PCI_SUBVENDOR_ID_SBSMODULARIO,
		.subdevice	= PCI_SUBDEVICE_ID_OCTPRO232,
		.init		= sbs_init,
		.setup		= sbs_setup,
		.निकास		= sbs_निकास,
	पूर्ण,
	/*
	 * SBS Technologies, Inc., PMC-OCTALPRO 422
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SBSMODULARIO,
		.device		= PCI_DEVICE_ID_OCTPRO,
		.subvenकरोr	= PCI_SUBVENDOR_ID_SBSMODULARIO,
		.subdevice	= PCI_SUBDEVICE_ID_OCTPRO422,
		.init		= sbs_init,
		.setup		= sbs_setup,
		.निकास		= sbs_निकास,
	पूर्ण,
	/*
	 * SBS Technologies, Inc., P-Octal 232
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SBSMODULARIO,
		.device		= PCI_DEVICE_ID_OCTPRO,
		.subvenकरोr	= PCI_SUBVENDOR_ID_SBSMODULARIO,
		.subdevice	= PCI_SUBDEVICE_ID_POCTAL232,
		.init		= sbs_init,
		.setup		= sbs_setup,
		.निकास		= sbs_निकास,
	पूर्ण,
	/*
	 * SBS Technologies, Inc., P-Octal 422
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SBSMODULARIO,
		.device		= PCI_DEVICE_ID_OCTPRO,
		.subvenकरोr	= PCI_SUBVENDOR_ID_SBSMODULARIO,
		.subdevice	= PCI_SUBDEVICE_ID_POCTAL422,
		.init		= sbs_init,
		.setup		= sbs_setup,
		.निकास		= sbs_निकास,
	पूर्ण,
	/*
	 * SIIG cards - these may be called via parport_serial
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SIIG,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_siig_init,
		.setup		= pci_siig_setup,
	पूर्ण,
	/*
	 * Titan cards
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_TITAN,
		.device		= PCI_DEVICE_ID_TITAN_400L,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= titan_400l_800l_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_TITAN,
		.device		= PCI_DEVICE_ID_TITAN_800L,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= titan_400l_800l_setup,
	पूर्ण,
	/*
	 * Timedia cards
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_TIMEDIA,
		.device		= PCI_DEVICE_ID_TIMEDIA_1889,
		.subvenकरोr	= PCI_VENDOR_ID_TIMEDIA,
		.subdevice	= PCI_ANY_ID,
		.probe		= pci_समयdia_probe,
		.init		= pci_समयdia_init,
		.setup		= pci_समयdia_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_TIMEDIA,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_समयdia_setup,
	पूर्ण,
	/*
	 * Sunix PCI serial boards
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_SUNIX,
		.device		= PCI_DEVICE_ID_SUNIX_1999,
		.subvenकरोr	= PCI_VENDOR_ID_SUNIX,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_sunix_setup,
	पूर्ण,
	/*
	 * Xircom cards
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_XIRCOM,
		.device		= PCI_DEVICE_ID_XIRCOM_X3201_MDM,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_xircom_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	/*
	 * Neपंचांगos cards - these may be called via parport_serial
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_NETMOS,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_neपंचांगos_init,
		.setup		= pci_neपंचांगos_9900_setup,
	पूर्ण,
	/*
	 * EndRun Technologies
	*/
	अणु
		.venकरोr		= PCI_VENDOR_ID_ENDRUN,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_endrun_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	/*
	 * For Oxक्रमd Semiconductor Tornaकरो based devices
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_OXSEMI,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_oxsemi_tornaकरो_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_MAINPINE,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_oxsemi_tornaकरो_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr		= PCI_VENDOR_ID_DIGI,
		.device		= PCIE_DEVICE_ID_NEO_2_OX_IBM,
		.subvenकरोr		= PCI_SUBVENDOR_ID_IBM,
		.subdevice		= PCI_ANY_ID,
		.init			= pci_oxsemi_tornaकरो_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = PCI_VENDOR_ID_INTEL,
		.device         = 0x8811,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = PCI_VENDOR_ID_INTEL,
		.device         = 0x8812,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = PCI_VENDOR_ID_INTEL,
		.device         = 0x8813,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = PCI_VENDOR_ID_INTEL,
		.device         = 0x8814,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = 0x10DB,
		.device         = 0x8027,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = 0x10DB,
		.device         = 0x8028,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = 0x10DB,
		.device         = 0x8029,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = 0x10DB,
		.device         = 0x800C,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	अणु
		.venकरोr         = 0x10DB,
		.device         = 0x800D,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.init		= pci_eg20t_init,
		.setup		= pci_शेष_setup,
	पूर्ण,
	/*
	 * Cronyx Omega PCI (PLX-chip based)
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_PLX,
		.device		= PCI_DEVICE_ID_PLX_CRONYX_OMEGA,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_omegapci_setup,
	पूर्ण,
	/* WCH CH353 1S1P card (16550 clone) */
	अणु
		.venकरोr         = PCI_VENDOR_ID_WCH,
		.device         = PCI_DEVICE_ID_WCH_CH353_1S1P,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch353_setup,
	पूर्ण,
	/* WCH CH353 2S1P card (16550 clone) */
	अणु
		.venकरोr         = PCI_VENDOR_ID_WCH,
		.device         = PCI_DEVICE_ID_WCH_CH353_2S1P,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch353_setup,
	पूर्ण,
	/* WCH CH353 4S card (16550 clone) */
	अणु
		.venकरोr         = PCI_VENDOR_ID_WCH,
		.device         = PCI_DEVICE_ID_WCH_CH353_4S,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch353_setup,
	पूर्ण,
	/* WCH CH353 2S1PF card (16550 clone) */
	अणु
		.venकरोr         = PCI_VENDOR_ID_WCH,
		.device         = PCI_DEVICE_ID_WCH_CH353_2S1PF,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch353_setup,
	पूर्ण,
	/* WCH CH352 2S card (16550 clone) */
	अणु
		.venकरोr		= PCI_VENDOR_ID_WCH,
		.device		= PCI_DEVICE_ID_WCH_CH352_2S,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_wch_ch353_setup,
	पूर्ण,
	/* WCH CH355 4S card (16550 clone) */
	अणु
		.venकरोr		= PCI_VENDOR_ID_WCH,
		.device		= PCI_DEVICE_ID_WCH_CH355_4S,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_wch_ch355_setup,
	पूर्ण,
	/* WCH CH382 2S card (16850 clone) */
	अणु
		.venकरोr         = PCIE_VENDOR_ID_WCH,
		.device         = PCIE_DEVICE_ID_WCH_CH382_2S,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch38x_setup,
	पूर्ण,
	/* WCH CH382 2S1P card (16850 clone) */
	अणु
		.venकरोr         = PCIE_VENDOR_ID_WCH,
		.device         = PCIE_DEVICE_ID_WCH_CH382_2S1P,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch38x_setup,
	पूर्ण,
	/* WCH CH384 4S card (16850 clone) */
	अणु
		.venकरोr         = PCIE_VENDOR_ID_WCH,
		.device         = PCIE_DEVICE_ID_WCH_CH384_4S,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.setup          = pci_wch_ch38x_setup,
	पूर्ण,
	/* WCH CH384 8S card (16850 clone) */
	अणु
		.venकरोr         = PCIE_VENDOR_ID_WCH,
		.device         = PCIE_DEVICE_ID_WCH_CH384_8S,
		.subvenकरोr      = PCI_ANY_ID,
		.subdevice      = PCI_ANY_ID,
		.init           = pci_wch_ch38x_init,
		.निकास		= pci_wch_ch38x_निकास,
		.setup          = pci_wch_ch38x_setup,
	पूर्ण,
	/*
	 * ASIX devices with FIFO bug
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_ASIX,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_asix_setup,
	पूर्ण,
	/*
	 * Broadcom TruManage (NetXtreme)
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_BROADCOM,
		.device		= PCI_DEVICE_ID_BROADCOM_TRUMANAGE,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_brcm_trumanage_setup,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1104,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_setup,
		.init		= pci_fपूर्णांकek_init,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1108,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_setup,
		.init		= pci_fपूर्णांकek_init,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1112,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_setup,
		.init		= pci_fपूर्णांकek_init,
	पूर्ण,
	/*
	 * MOXA
	 */
	अणु
		.venकरोr		= PCI_VENDOR_ID_MOXA,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_moxa_setup,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1204,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_f815xxa_setup,
		.init		= pci_fपूर्णांकek_f815xxa_init,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1208,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_f815xxa_setup,
		.init		= pci_fपूर्णांकek_f815xxa_init,
	पूर्ण,
	अणु
		.venकरोr		= 0x1c29,
		.device		= 0x1212,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_fपूर्णांकek_f815xxa_setup,
		.init		= pci_fपूर्णांकek_f815xxa_init,
	पूर्ण,

	/*
	 * Default "match everything" terminator entry
	 */
	अणु
		.venकरोr		= PCI_ANY_ID,
		.device		= PCI_ANY_ID,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.setup		= pci_शेष_setup,
	पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक quirk_id_matches(u32 quirk_id, u32 dev_id)
अणु
	वापस quirk_id == PCI_ANY_ID || quirk_id == dev_id;
पूर्ण

अटल काष्ठा pci_serial_quirk *find_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_serial_quirk *quirk;

	क्रम (quirk = pci_serial_quirks; ; quirk++)
		अगर (quirk_id_matches(quirk->venकरोr, dev->venकरोr) &&
		    quirk_id_matches(quirk->device, dev->device) &&
		    quirk_id_matches(quirk->subvenकरोr, dev->subप्रणाली_venकरोr) &&
		    quirk_id_matches(quirk->subdevice, dev->subप्रणाली_device))
			अवरोध;
	वापस quirk;
पूर्ण

/*
 * This is the configuration table क्रम all of the PCI serial boards
 * which we support.  It is directly indexed by the pci_board_num_t क्रमागत
 * value, which is encoded in the pci_device_id PCI probe table's
 * driver_data member.
 *
 * The makeup of these names are:
 *  pbn_bnअणु_btपूर्ण_n_baudअणु_offsetinhexपूर्ण
 *
 *  bn		= PCI BAR number
 *  bt		= Index using PCI BARs
 *  n		= number of serial ports
 *  baud	= baud rate
 *  offsetinhex	= offset क्रम each sequential port (in hex)
 *
 * This table is sorted by (in order): bn, bt, baud, offsetindex, n.
 *
 * Please note: in theory अगर n = 1, _bt infix should make no dअगरference.
 * ie, pbn_b0_1_115200 is the same as pbn_b0_bt_1_115200
 */
क्रमागत pci_board_num_t अणु
	pbn_शेष = 0,

	pbn_b0_1_115200,
	pbn_b0_2_115200,
	pbn_b0_4_115200,
	pbn_b0_5_115200,
	pbn_b0_8_115200,

	pbn_b0_1_921600,
	pbn_b0_2_921600,
	pbn_b0_4_921600,

	pbn_b0_2_1130000,

	pbn_b0_4_1152000,

	pbn_b0_4_1250000,

	pbn_b0_2_1843200,
	pbn_b0_4_1843200,

	pbn_b0_1_4000000,

	pbn_b0_bt_1_115200,
	pbn_b0_bt_2_115200,
	pbn_b0_bt_4_115200,
	pbn_b0_bt_8_115200,

	pbn_b0_bt_1_460800,
	pbn_b0_bt_2_460800,
	pbn_b0_bt_4_460800,

	pbn_b0_bt_1_921600,
	pbn_b0_bt_2_921600,
	pbn_b0_bt_4_921600,
	pbn_b0_bt_8_921600,

	pbn_b1_1_115200,
	pbn_b1_2_115200,
	pbn_b1_4_115200,
	pbn_b1_8_115200,
	pbn_b1_16_115200,

	pbn_b1_1_921600,
	pbn_b1_2_921600,
	pbn_b1_4_921600,
	pbn_b1_8_921600,

	pbn_b1_2_1250000,

	pbn_b1_bt_1_115200,
	pbn_b1_bt_2_115200,
	pbn_b1_bt_4_115200,

	pbn_b1_bt_2_921600,

	pbn_b1_1_1382400,
	pbn_b1_2_1382400,
	pbn_b1_4_1382400,
	pbn_b1_8_1382400,

	pbn_b2_1_115200,
	pbn_b2_2_115200,
	pbn_b2_4_115200,
	pbn_b2_8_115200,

	pbn_b2_1_460800,
	pbn_b2_4_460800,
	pbn_b2_8_460800,
	pbn_b2_16_460800,

	pbn_b2_1_921600,
	pbn_b2_4_921600,
	pbn_b2_8_921600,

	pbn_b2_8_1152000,

	pbn_b2_bt_1_115200,
	pbn_b2_bt_2_115200,
	pbn_b2_bt_4_115200,

	pbn_b2_bt_2_921600,
	pbn_b2_bt_4_921600,

	pbn_b3_2_115200,
	pbn_b3_4_115200,
	pbn_b3_8_115200,

	pbn_b4_bt_2_921600,
	pbn_b4_bt_4_921600,
	pbn_b4_bt_8_921600,

	/*
	 * Board-specअगरic versions.
	 */
	pbn_panacom,
	pbn_panacom2,
	pbn_panacom4,
	pbn_plx_romulus,
	pbn_endrun_2_4000000,
	pbn_oxsemi,
	pbn_oxsemi_1_4000000,
	pbn_oxsemi_2_4000000,
	pbn_oxsemi_4_4000000,
	pbn_oxsemi_8_4000000,
	pbn_पूर्णांकel_i960,
	pbn_sgi_ioc3,
	pbn_computone_4,
	pbn_computone_6,
	pbn_computone_8,
	pbn_sbsxrsio,
	pbn_pasemi_1682M,
	pbn_ni8430_2,
	pbn_ni8430_4,
	pbn_ni8430_8,
	pbn_ni8430_16,
	pbn_ADDIDATA_PCIe_1_3906250,
	pbn_ADDIDATA_PCIe_2_3906250,
	pbn_ADDIDATA_PCIe_4_3906250,
	pbn_ADDIDATA_PCIe_8_3906250,
	pbn_ce4100_1_115200,
	pbn_omegapci,
	pbn_NETMOS9900_2s_115200,
	pbn_brcm_trumanage,
	pbn_fपूर्णांकek_4,
	pbn_fपूर्णांकek_8,
	pbn_fपूर्णांकek_12,
	pbn_fपूर्णांकek_F81504A,
	pbn_fपूर्णांकek_F81508A,
	pbn_fपूर्णांकek_F81512A,
	pbn_wch382_2,
	pbn_wch384_4,
	pbn_wch384_8,
	pbn_pericom_PI7C9X7951,
	pbn_pericom_PI7C9X7952,
	pbn_pericom_PI7C9X7954,
	pbn_pericom_PI7C9X7958,
	pbn_sunix_pci_1s,
	pbn_sunix_pci_2s,
	pbn_sunix_pci_4s,
	pbn_sunix_pci_8s,
	pbn_sunix_pci_16s,
	pbn_moxa8250_2p,
	pbn_moxa8250_4p,
	pbn_moxa8250_8p,
पूर्ण;

/*
 * uart_offset - the space between channels
 * reg_shअगरt   - describes how the UART रेजिस्टरs are mapped
 *               to PCI memory by the card.
 * For example IER रेजिस्टर on SBS, Inc. PMC-OctPro is located at
 * offset 0x10 from the UART base, जबतक UART_IER is defined as 1
 * in include/linux/serial_reg.h,
 * see first lines of serial_in() and serial_out() in 8250.c
*/

अटल काष्ठा pciserial_board pci_boards[] = अणु
	[pbn_शेष] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_1_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_2_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_4_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_5_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 5,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_8_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_1_921600] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_2_921600] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_4_921600] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_2_1130000] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 2,
		.base_baud      = 1130000,
		.uart_offset    = 8,
	पूर्ण,

	[pbn_b0_4_1152000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 1152000,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_4_1250000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 1250000,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_2_1843200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 1843200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_4_1843200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 1843200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_1_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 4000000,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_bt_1_115200] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_2_115200] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_4_115200] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_8_115200] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_bt_1_460800] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_2_460800] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_4_460800] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b0_bt_1_921600] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_2_921600] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_4_921600] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b0_bt_8_921600] = अणु
		.flags		= FL_BASE0|FL_BASE_BARS,
		.num_ports	= 8,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b1_1_115200] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_2_115200] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_4_115200] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_8_115200] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_16_115200] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 16,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b1_1_921600] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_2_921600] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_4_921600] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_8_921600] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 8,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_2_1250000] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 2,
		.base_baud	= 1250000,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b1_bt_1_115200] = अणु
		.flags		= FL_BASE1|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_bt_2_115200] = अणु
		.flags		= FL_BASE1|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_bt_4_115200] = अणु
		.flags		= FL_BASE1|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b1_bt_2_921600] = अणु
		.flags		= FL_BASE1|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b1_1_1382400] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 1,
		.base_baud	= 1382400,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_2_1382400] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 2,
		.base_baud	= 1382400,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_4_1382400] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 4,
		.base_baud	= 1382400,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b1_8_1382400] = अणु
		.flags		= FL_BASE1,
		.num_ports	= 8,
		.base_baud	= 1382400,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b2_1_115200] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_2_115200] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_4_115200] = अणु
		.flags          = FL_BASE2,
		.num_ports      = 4,
		.base_baud      = 115200,
		.uart_offset    = 8,
	पूर्ण,
	[pbn_b2_8_115200] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b2_1_460800] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 1,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_4_460800] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 4,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_8_460800] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 8,
		.base_baud	= 460800,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_16_460800] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 16,
		.base_baud	= 460800,
		.uart_offset	= 8,
	 पूर्ण,

	[pbn_b2_1_921600] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 1,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_4_921600] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_8_921600] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 8,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b2_8_1152000] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 8,
		.base_baud	= 1152000,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b2_bt_1_115200] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 1,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_bt_2_115200] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_bt_4_115200] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b2_bt_2_921600] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b2_bt_4_921600] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b3_2_115200] = अणु
		.flags		= FL_BASE3,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b3_4_115200] = अणु
		.flags		= FL_BASE3,
		.num_ports	= 4,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b3_8_115200] = अणु
		.flags		= FL_BASE3,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,

	[pbn_b4_bt_2_921600] = अणु
		.flags		= FL_BASE4,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b4_bt_4_921600] = अणु
		.flags		= FL_BASE4,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_b4_bt_8_921600] = अणु
		.flags		= FL_BASE4,
		.num_ports	= 8,
		.base_baud	= 921600,
		.uart_offset	= 8,
	पूर्ण,

	/*
	 * Entries following this are board-specअगरic.
	 */

	/*
	 * Panacom - IOMEM
	 */
	[pbn_panacom] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 0x400,
		.reg_shअगरt	= 7,
	पूर्ण,
	[pbn_panacom2] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.uart_offset	= 0x400,
		.reg_shअगरt	= 7,
	पूर्ण,
	[pbn_panacom4] = अणु
		.flags		= FL_BASE2|FL_BASE_BARS,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 0x400,
		.reg_shअगरt	= 7,
	पूर्ण,

	/* I think this entry is broken - the first_offset looks wrong --rmk */
	[pbn_plx_romulus] = अणु
		.flags		= FL_BASE2,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 8 << 2,
		.reg_shअगरt	= 2,
		.first_offset	= 0x03,
	पूर्ण,

	/*
	 * EndRun Technologies
	* Uses the size of PCI Base region 0 to
	* संकेत now many ports are available
	* 2 port 952 Uart support
	*/
	[pbn_endrun_2_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 4000000,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,

	/*
	 * This board uses the size of PCI Base region 0 to
	 * संकेत now many ports are available
	 */
	[pbn_oxsemi] = अणु
		.flags		= FL_BASE0|FL_REGION_SZ_CAP,
		.num_ports	= 32,
		.base_baud	= 115200,
		.uart_offset	= 8,
	पूर्ण,
	[pbn_oxsemi_1_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 4000000,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_oxsemi_2_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 4000000,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_oxsemi_4_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 4000000,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_oxsemi_8_4000000] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 4000000,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,


	/*
	 * EKF addition क्रम i960 Boards क्रमm EKF with serial port.
	 * Max 256 ports.
	 */
	[pbn_पूर्णांकel_i960] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 32,
		.base_baud	= 921600,
		.uart_offset	= 8 << 2,
		.reg_shअगरt	= 2,
		.first_offset	= 0x10000,
	पूर्ण,
	[pbn_sgi_ioc3] = अणु
		.flags		= FL_BASE0|FL_NOIRQ,
		.num_ports	= 1,
		.base_baud	= 458333,
		.uart_offset	= 8,
		.reg_shअगरt	= 0,
		.first_offset	= 0x20178,
	पूर्ण,

	/*
	 * Computone - uses IOMEM.
	 */
	[pbn_computone_4] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 921600,
		.uart_offset	= 0x40,
		.reg_shअगरt	= 2,
		.first_offset	= 0x200,
	पूर्ण,
	[pbn_computone_6] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 6,
		.base_baud	= 921600,
		.uart_offset	= 0x40,
		.reg_shअगरt	= 2,
		.first_offset	= 0x200,
	पूर्ण,
	[pbn_computone_8] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 921600,
		.uart_offset	= 0x40,
		.reg_shअगरt	= 2,
		.first_offset	= 0x200,
	पूर्ण,
	[pbn_sbsxrsio] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 460800,
		.uart_offset	= 256,
		.reg_shअगरt	= 4,
	पूर्ण,
	/*
	 * PA Semi PWRficient PA6T-1682M on-chip UART
	 */
	[pbn_pasemi_1682M] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 8333333,
	पूर्ण,
	/*
	 * National Instruments 843x
	 */
	[pbn_ni8430_16] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 16,
		.base_baud	= 3686400,
		.uart_offset	= 0x10,
		.first_offset	= 0x800,
	पूर्ण,
	[pbn_ni8430_8] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 3686400,
		.uart_offset	= 0x10,
		.first_offset	= 0x800,
	पूर्ण,
	[pbn_ni8430_4] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 3686400,
		.uart_offset	= 0x10,
		.first_offset	= 0x800,
	पूर्ण,
	[pbn_ni8430_2] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 3686400,
		.uart_offset	= 0x10,
		.first_offset	= 0x800,
	पूर्ण,
	/*
	 * ADDI-DATA GmbH PCI-Express communication cards <info@addi-data.com>
	 */
	[pbn_ADDIDATA_PCIe_1_3906250] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.base_baud	= 3906250,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_ADDIDATA_PCIe_2_3906250] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 3906250,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_ADDIDATA_PCIe_4_3906250] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud	= 3906250,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_ADDIDATA_PCIe_8_3906250] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 3906250,
		.uart_offset	= 0x200,
		.first_offset	= 0x1000,
	पूर्ण,
	[pbn_ce4100_1_115200] = अणु
		.flags		= FL_BASE_BARS,
		.num_ports	= 2,
		.base_baud	= 921600,
		.reg_shअगरt      = 2,
	पूर्ण,
	[pbn_omegapci] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud	= 115200,
		.uart_offset	= 0x200,
	पूर्ण,
	[pbn_NETMOS9900_2s_115200] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 115200,
	पूर्ण,
	[pbn_brcm_trumanage] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 1,
		.reg_shअगरt	= 2,
		.base_baud	= 115200,
	पूर्ण,
	[pbn_fपूर्णांकek_4] = अणु
		.num_ports	= 4,
		.uart_offset	= 8,
		.base_baud	= 115200,
		.first_offset	= 0x40,
	पूर्ण,
	[pbn_fपूर्णांकek_8] = अणु
		.num_ports	= 8,
		.uart_offset	= 8,
		.base_baud	= 115200,
		.first_offset	= 0x40,
	पूर्ण,
	[pbn_fपूर्णांकek_12] = अणु
		.num_ports	= 12,
		.uart_offset	= 8,
		.base_baud	= 115200,
		.first_offset	= 0x40,
	पूर्ण,
	[pbn_fपूर्णांकek_F81504A] = अणु
		.num_ports	= 4,
		.uart_offset	= 8,
		.base_baud	= 115200,
	पूर्ण,
	[pbn_fपूर्णांकek_F81508A] = अणु
		.num_ports	= 8,
		.uart_offset	= 8,
		.base_baud	= 115200,
	पूर्ण,
	[pbn_fपूर्णांकek_F81512A] = अणु
		.num_ports	= 12,
		.uart_offset	= 8,
		.base_baud	= 115200,
	पूर्ण,
	[pbn_wch382_2] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 2,
		.base_baud	= 115200,
		.uart_offset	= 8,
		.first_offset	= 0xC0,
	पूर्ण,
	[pbn_wch384_4] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 4,
		.base_baud      = 115200,
		.uart_offset    = 8,
		.first_offset   = 0xC0,
	पूर्ण,
	[pbn_wch384_8] = अणु
		.flags		= FL_BASE0,
		.num_ports	= 8,
		.base_baud      = 115200,
		.uart_offset    = 8,
		.first_offset   = 0x00,
	पूर्ण,
	/*
	 * Pericom PI7C9X795[1248] Uno/Dual/Quad/Octal UART
	 */
	[pbn_pericom_PI7C9X7951] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 1,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_pericom_PI7C9X7952] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 2,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_pericom_PI7C9X7954] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 4,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_pericom_PI7C9X7958] = अणु
		.flags          = FL_BASE0,
		.num_ports      = 8,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_sunix_pci_1s] = अणु
		.num_ports	= 1,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_sunix_pci_2s] = अणु
		.num_ports	= 2,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_sunix_pci_4s] = अणु
		.num_ports	= 4,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_sunix_pci_8s] = अणु
		.num_ports	= 8,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_sunix_pci_16s] = अणु
		.num_ports	= 16,
		.base_baud      = 921600,
		.uart_offset	= 0x8,
	पूर्ण,
	[pbn_moxa8250_2p] = अणु
		.flags		= FL_BASE1,
		.num_ports      = 2,
		.base_baud      = 921600,
		.uart_offset	= 0x200,
	पूर्ण,
	[pbn_moxa8250_4p] = अणु
		.flags		= FL_BASE1,
		.num_ports      = 4,
		.base_baud      = 921600,
		.uart_offset	= 0x200,
	पूर्ण,
	[pbn_moxa8250_8p] = अणु
		.flags		= FL_BASE1,
		.num_ports      = 8,
		.base_baud      = 921600,
		.uart_offset	= 0x200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id blacklist[] = अणु
	/* sofपंचांगodems */
	अणु PCI_VDEVICE(AL, 0x5457), पूर्ण, /* ALi Corporation M5457 AC'97 Modem */
	अणु PCI_VDEVICE(MOTOROLA, 0x3052), पूर्ण, /* Motorola Si3052-based modem */
	अणु PCI_DEVICE(0x1543, 0x3052), पूर्ण, /* Si3052-based modem, शेष IDs */

	/* multi-io cards handled by parport_serial */
	अणु PCI_DEVICE(0x4348, 0x7053), पूर्ण, /* WCH CH353 2S1P */
	अणु PCI_DEVICE(0x4348, 0x5053), पूर्ण, /* WCH CH353 1S1P */
	अणु PCI_DEVICE(0x1c00, 0x3250), पूर्ण, /* WCH CH382 2S1P */

	/* Intel platक्रमms with MID UART */
	अणु PCI_VDEVICE(INTEL, 0x081b), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x081c), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x081d), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1191), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x18d8), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x19d8), पूर्ण,

	/* Intel platक्रमms with DesignWare UART */
	अणु PCI_VDEVICE(INTEL, 0x0936), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f0a), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f0c), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x228a), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x228c), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9ce3), पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9ce4), पूर्ण,

	/* Exar devices */
	अणु PCI_VDEVICE(EXAR, PCI_ANY_ID), पूर्ण,
	अणु PCI_VDEVICE(COMMTECH, PCI_ANY_ID), पूर्ण,

	/* End of the black list */
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक serial_pci_is_class_communication(काष्ठा pci_dev *dev)
अणु
	/*
	 * If it is not a communications device or the programming
	 * पूर्णांकerface is greater than 6, give up.
	 */
	अगर ((((dev->class >> 8) != PCI_CLASS_COMMUNICATION_SERIAL) &&
	     ((dev->class >> 8) != PCI_CLASS_COMMUNICATION_MULTISERIAL) &&
	     ((dev->class >> 8) != PCI_CLASS_COMMUNICATION_MODEM)) ||
	    (dev->class & 0xff) > 6)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Given a complete unknown PCI device, try to use some heuristics to
 * guess what the configuration might be, based on the pitअगरul PCI
 * serial specs.  Returns 0 on success, -ENODEV on failure.
 */
अटल पूर्णांक
serial_pci_guess_board(काष्ठा pci_dev *dev, काष्ठा pciserial_board *board)
अणु
	पूर्णांक num_iomem, num_port, first_port = -1, i;
	पूर्णांक rc;

	rc = serial_pci_is_class_communication(dev);
	अगर (rc)
		वापस rc;

	/*
	 * Should we try to make guesses क्रम multiport serial devices later?
	 */
	अगर ((dev->class >> 8) == PCI_CLASS_COMMUNICATION_MULTISERIAL)
		वापस -ENODEV;

	num_iomem = num_port = 0;
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_flags(dev, i) & IORESOURCE_IO) अणु
			num_port++;
			अगर (first_port == -1)
				first_port = i;
		पूर्ण
		अगर (pci_resource_flags(dev, i) & IORESOURCE_MEM)
			num_iomem++;
	पूर्ण

	/*
	 * If there is 1 or 0 iomem regions, and exactly one port,
	 * use it.  We guess the number of ports based on the IO
	 * region size.
	 */
	अगर (num_iomem <= 1 && num_port == 1) अणु
		board->flags = first_port;
		board->num_ports = pci_resource_len(dev, first_port) / 8;
		वापस 0;
	पूर्ण

	/*
	 * Now guess अगर we've got a board which indexes by BARs.
	 * Each IO BAR should be 8 bytes, and they should follow
	 * consecutively.
	 */
	first_port = -1;
	num_port = 0;
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_flags(dev, i) & IORESOURCE_IO &&
		    pci_resource_len(dev, i) == 8 &&
		    (first_port == -1 || (first_port + num_port) == i)) अणु
			num_port++;
			अगर (first_port == -1)
				first_port = i;
		पूर्ण
	पूर्ण

	अगर (num_port > 1) अणु
		board->flags = first_port | FL_BASE_BARS;
		board->num_ports = num_port;
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक
serial_pci_matches(स्थिर काष्ठा pciserial_board *board,
		   स्थिर काष्ठा pciserial_board *guessed)
अणु
	वापस
	    board->num_ports == guessed->num_ports &&
	    board->base_baud == guessed->base_baud &&
	    board->uart_offset == guessed->uart_offset &&
	    board->reg_shअगरt == guessed->reg_shअगरt &&
	    board->first_offset == guessed->first_offset;
पूर्ण

काष्ठा serial_निजी *
pciserial_init_ports(काष्ठा pci_dev *dev, स्थिर काष्ठा pciserial_board *board)
अणु
	काष्ठा uart_8250_port uart;
	काष्ठा serial_निजी *priv;
	काष्ठा pci_serial_quirk *quirk;
	पूर्णांक rc, nr_ports, i;

	nr_ports = board->num_ports;

	/*
	 * Find an init and setup quirks.
	 */
	quirk = find_quirk(dev);

	/*
	 * Run the new-style initialization function.
	 * The initialization function वापसs:
	 *  <0  - error
	 *   0  - use board->num_ports
	 *  >0  - number of ports
	 */
	अगर (quirk->init) अणु
		rc = quirk->init(dev);
		अगर (rc < 0) अणु
			priv = ERR_PTR(rc);
			जाओ err_out;
		पूर्ण
		अगर (rc)
			nr_ports = rc;
	पूर्ण

	priv = kzalloc(माप(काष्ठा serial_निजी) +
		       माप(अचिन्हित पूर्णांक) * nr_ports,
		       GFP_KERNEL);
	अगर (!priv) अणु
		priv = ERR_PTR(-ENOMEM);
		जाओ err_deinit;
	पूर्ण

	priv->dev = dev;
	priv->quirk = quirk;

	स_रखो(&uart, 0, माप(uart));
	uart.port.flags = UPF_SKIP_TEST | UPF_BOOT_AUTOCONF | UPF_SHARE_IRQ;
	uart.port.uartclk = board->base_baud * 16;

	अगर (board->flags & FL_NOIRQ) अणु
		uart.port.irq = 0;
	पूर्ण अन्यथा अणु
		अगर (pci_match_id(pci_use_msi, dev)) अणु
			dev_dbg(&dev->dev, "Using MSI(-X) interrupts\n");
			pci_set_master(dev);
			rc = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_ALL_TYPES);
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->dev, "Using legacy interrupts\n");
			rc = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_LEGACY);
		पूर्ण
		अगर (rc < 0) अणु
			kमुक्त(priv);
			priv = ERR_PTR(rc);
			जाओ err_deinit;
		पूर्ण

		uart.port.irq = pci_irq_vector(dev, 0);
	पूर्ण

	uart.port.dev = &dev->dev;

	क्रम (i = 0; i < nr_ports; i++) अणु
		अगर (quirk->setup(priv, board, &uart, i))
			अवरोध;

		dev_dbg(&dev->dev, "Setup PCI port: port %lx, irq %d, type %d\n",
			uart.port.iobase, uart.port.irq, uart.port.iotype);

		priv->line[i] = serial8250_रेजिस्टर_8250_port(&uart);
		अगर (priv->line[i] < 0) अणु
			dev_err(&dev->dev,
				"Couldn't register serial port %lx, irq %d, type %d, error %d\n",
				uart.port.iobase, uart.port.irq,
				uart.port.iotype, priv->line[i]);
			अवरोध;
		पूर्ण
	पूर्ण
	priv->nr = i;
	priv->board = board;
	वापस priv;

err_deinit:
	अगर (quirk->निकास)
		quirk->निकास(dev);
err_out:
	वापस priv;
पूर्ण
EXPORT_SYMBOL_GPL(pciserial_init_ports);

अटल व्योम pciserial_detach_ports(काष्ठा serial_निजी *priv)
अणु
	काष्ठा pci_serial_quirk *quirk;
	पूर्णांक i;

	क्रम (i = 0; i < priv->nr; i++)
		serial8250_unरेजिस्टर_port(priv->line[i]);

	/*
	 * Find the निकास quirks.
	 */
	quirk = find_quirk(priv->dev);
	अगर (quirk->निकास)
		quirk->निकास(priv->dev);
पूर्ण

व्योम pciserial_हटाओ_ports(काष्ठा serial_निजी *priv)
अणु
	pciserial_detach_ports(priv);
	kमुक्त(priv);
पूर्ण
EXPORT_SYMBOL_GPL(pciserial_हटाओ_ports);

व्योम pciserial_suspend_ports(काष्ठा serial_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->nr; i++)
		अगर (priv->line[i] >= 0)
			serial8250_suspend_port(priv->line[i]);

	/*
	 * Ensure that every init quirk is properly torn करोwn
	 */
	अगर (priv->quirk->निकास)
		priv->quirk->निकास(priv->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pciserial_suspend_ports);

व्योम pciserial_resume_ports(काष्ठा serial_निजी *priv)
अणु
	पूर्णांक i;

	/*
	 * Ensure that the board is correctly configured.
	 */
	अगर (priv->quirk->init)
		priv->quirk->init(priv->dev);

	क्रम (i = 0; i < priv->nr; i++)
		अगर (priv->line[i] >= 0)
			serial8250_resume_port(priv->line[i]);
पूर्ण
EXPORT_SYMBOL_GPL(pciserial_resume_ports);

/*
 * Probe one serial board.  Unक्रमtunately, there is no rhyme nor reason
 * to the arrangement of serial ports on a PCI card.
 */
अटल पूर्णांक
pciserial_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा pci_serial_quirk *quirk;
	काष्ठा serial_निजी *priv;
	स्थिर काष्ठा pciserial_board *board;
	स्थिर काष्ठा pci_device_id *exclude;
	काष्ठा pciserial_board पंचांगp;
	पूर्णांक rc;

	quirk = find_quirk(dev);
	अगर (quirk->probe) अणु
		rc = quirk->probe(dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (ent->driver_data >= ARRAY_SIZE(pci_boards)) अणु
		dev_err(&dev->dev, "invalid driver_data: %ld\n",
			ent->driver_data);
		वापस -EINVAL;
	पूर्ण

	board = &pci_boards[ent->driver_data];

	exclude = pci_match_id(blacklist, dev);
	अगर (exclude)
		वापस -ENODEV;

	rc = pcim_enable_device(dev);
	pci_save_state(dev);
	अगर (rc)
		वापस rc;

	अगर (ent->driver_data == pbn_शेष) अणु
		/*
		 * Use a copy of the pci_board entry क्रम this;
		 * aव्योम changing entries in the table.
		 */
		स_नकल(&पंचांगp, board, माप(काष्ठा pciserial_board));
		board = &पंचांगp;

		/*
		 * We matched one of our class entries.  Try to
		 * determine the parameters of this board.
		 */
		rc = serial_pci_guess_board(dev, &पंचांगp);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		/*
		 * We matched an explicit entry.  If we are able to
		 * detect this boards settings with our heuristic,
		 * then we no दीर्घer need this entry.
		 */
		स_नकल(&पंचांगp, &pci_boards[pbn_शेष],
		       माप(काष्ठा pciserial_board));
		rc = serial_pci_guess_board(dev, &पंचांगp);
		अगर (rc == 0 && serial_pci_matches(board, &पंचांगp))
			moan_device("Redundant entry in serial pci_table.",
				    dev);
	पूर्ण

	priv = pciserial_init_ports(dev, board);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	pci_set_drvdata(dev, priv);
	वापस 0;
पूर्ण

अटल व्योम pciserial_हटाओ_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा serial_निजी *priv = pci_get_drvdata(dev);

	pciserial_हटाओ_ports(priv);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pciserial_suspend_one(काष्ठा device *dev)
अणु
	काष्ठा serial_निजी *priv = dev_get_drvdata(dev);

	अगर (priv)
		pciserial_suspend_ports(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक pciserial_resume_one(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा serial_निजी *priv = pci_get_drvdata(pdev);
	पूर्णांक err;

	अगर (priv) अणु
		/*
		 * The device may have been disabled.  Re-enable it.
		 */
		err = pci_enable_device(pdev);
		/* FIXME: We cannot simply error out here */
		अगर (err)
			dev_err(dev, "Unable to re-enable ports, trying to continue.\n");
		pciserial_resume_ports(priv);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pciserial_pm_ops, pciserial_suspend_one,
			 pciserial_resume_one);

अटल स्थिर काष्ठा pci_device_id serial_pci_tbl[] = अणु
	/* Advantech use PCI_DEVICE_ID_ADVANTECH_PCI3620 (0x3620) as 'PCI_SUBVENDOR_ID' */
	अणु	PCI_VENDOR_ID_ADVANTECH, PCI_DEVICE_ID_ADVANTECH_PCI3620,
		PCI_DEVICE_ID_ADVANTECH_PCI3620, 0x0001, 0, 0,
		pbn_b2_8_921600 पूर्ण,
	/* Advantech also use 0x3618 and 0xf618 */
	अणु	PCI_VENDOR_ID_ADVANTECH, PCI_DEVICE_ID_ADVANTECH_PCI3618,
		PCI_DEVICE_ID_ADVANTECH_PCI3618, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_ADVANTECH, PCI_DEVICE_ID_ADVANTECH_PCIf618,
		PCI_DEVICE_ID_ADVANTECH_PCI3618, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V960,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH8_232, 0, 0,
		pbn_b1_8_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V960,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH4_232, 0, 0,
		pbn_b1_4_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V960,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH2_232, 0, 0,
		pbn_b1_2_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH8_232, 0, 0,
		pbn_b1_8_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH4_232, 0, 0,
		pbn_b1_4_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH2_232, 0, 0,
		pbn_b1_2_1382400 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH8_485, 0, 0,
		pbn_b1_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH8_485_4_4, 0, 0,
		pbn_b1_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH4_485, 0, 0,
		pbn_b1_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH4_485_2_2, 0, 0,
		pbn_b1_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH2_485, 0, 0,
		pbn_b1_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH8_485_2_6, 0, 0,
		pbn_b1_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH081101V1, 0, 0,
		pbn_b1_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH041101V1, 0, 0,
		pbn_b1_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_V3, PCI_DEVICE_ID_V3_V351,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_BH2_20MHZ, 0, 0,
		pbn_b1_2_1250000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_TITAN_2, 0, 0,
		pbn_b0_2_1843200 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_SUBVENDOR_ID_CONNECT_TECH,
		PCI_SUBDEVICE_ID_CONNECT_TECH_TITAN_4, 0, 0,
		pbn_b0_4_1843200 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_VENDOR_ID_AFAVLAB,
		PCI_SUBDEVICE_ID_AFAVLAB_P061, 0, 0,
		pbn_b0_4_1152000 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_U530,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_1_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_UCOMM2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_UCOMM422,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_UCOMM232,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_COMM4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_COMM8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_7803,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_8_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_SEALEVEL, PCI_DEVICE_ID_SEALEVEL_UCOMM8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_8_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_GTEK_SERIAL2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_SPCOM200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_921600 पूर्ण,
	/*
	 * VScom SPCOM800, from sl@s.pl
	 */
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_SPCOM800,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_1077,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_4_921600 पूर्ण,
	/* Unknown card - subdevice 0x1584 */
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_VENDOR_ID_PLX,
		PCI_SUBDEVICE_ID_UNKNOWN_0x1584, 0, 0,
		pbn_b2_4_115200 पूर्ण,
	/* Unknown card - subdevice 0x1588 */
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_VENDOR_ID_PLX,
		PCI_SUBDEVICE_ID_UNKNOWN_0x1588, 0, 0,
		pbn_b2_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_KEYSPAN,
		PCI_SUBDEVICE_ID_KEYSPAN_SX2, 0, 0,
		pbn_panacom पूर्ण,
	अणु	PCI_VENDOR_ID_PANACOM, PCI_DEVICE_ID_PANACOM_QUADMODEM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_panacom4 पूर्ण,
	अणु	PCI_VENDOR_ID_PANACOM, PCI_DEVICE_ID_PANACOM_DUALMODEM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_panacom2 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		PCI_VENDOR_ID_ESDGMBH,
		PCI_DEVICE_ID_ESDGMBH_CPCIASIO4, 0, 0,
		pbn_b2_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIFAST,
		PCI_SUBDEVICE_ID_CHASE_PCIFAST4, 0, 0,
		pbn_b2_4_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIFAST,
		PCI_SUBDEVICE_ID_CHASE_PCIFAST8, 0, 0,
		pbn_b2_8_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIFAST,
		PCI_SUBDEVICE_ID_CHASE_PCIFAST16, 0, 0,
		pbn_b2_16_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIFAST,
		PCI_SUBDEVICE_ID_CHASE_PCIFAST16FMC, 0, 0,
		pbn_b2_16_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIRAS,
		PCI_SUBDEVICE_ID_CHASE_PCIRAS4, 0, 0,
		pbn_b2_4_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_CHASE_PCIRAS,
		PCI_SUBDEVICE_ID_CHASE_PCIRAS8, 0, 0,
		pbn_b2_8_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9050,
		PCI_SUBVENDOR_ID_EXSYS,
		PCI_SUBDEVICE_ID_EXSYS_4055, 0, 0,
		pbn_b2_4_115200 पूर्ण,
	/*
	 * Megawolf Romulus PCI Serial Card, from Mike Hudson
	 * (Exoray@isys.ca)
	 */
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_ROMULUS,
		0x10b5, 0x106a, 0, 0,
		pbn_plx_romulus पूर्ण,
	/*
	* EndRun Technologies. PCI express device range.
	*    EndRun PTP/1588 has 2 Native UARTs.
	*/
	अणु	PCI_VENDOR_ID_ENDRUN, PCI_DEVICE_ID_ENDRUN_1588,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_endrun_2_4000000 पूर्ण,
	/*
	 * Quatech cards. These actually have configurable घड़ीs but क्रम
	 * now we just use the शेष.
	 *
	 * 100 series are RS232, 200 series RS422,
	 */
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSC100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSC100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSC100E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSC200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSC200E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSC200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_ESC100D,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_ESC100M,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSCP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSCP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSCP200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSCP200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSCLP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSCLP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_SSCLP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_QSCLP200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_DSCLP200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_SSCLP200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_QUATECH, PCI_DEVICE_ID_QUATECH_ESCLP100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_8_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_SPECIALIX, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_VENDOR_ID_SPECIALIX, PCI_SUBDEVICE_ID_SPECIALIX_SPEED4,
		0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_SUBVENDOR_ID_SIIG, PCI_SUBDEVICE_ID_SIIG_QUARTET_SERIAL,
		0, 0,
		pbn_b0_4_1152000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0x9505,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,

		/*
		 * The below card is a little controversial since it is the
		 * subject of a PCI venकरोr/device ID clash.  (See
		 * www.ussg.iu.edu/hypermail/linux/kernel/0303.1/0516.hपंचांगl).
		 * For now just used the hex ID 0x950a.
		 */
	अणु	PCI_VENDOR_ID_OXSEMI, 0x950a,
		PCI_SUBVENDOR_ID_SIIG, PCI_SUBDEVICE_ID_SIIG_DUAL_00,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0x950a,
		PCI_SUBVENDOR_ID_SIIG, PCI_SUBDEVICE_ID_SIIG_DUAL_30,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0x950a,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_2_1130000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_C950,
		PCI_VENDOR_ID_OXSEMI, PCI_SUBDEVICE_ID_OXSEMI_C950, 0, 0,
		pbn_b0_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI952,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI958,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_8_1152000 पूर्ण,

	/*
	 * Oxक्रमd Semiconductor Inc. Tornaकरो PCI express device range.
	 */
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc101,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc105,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc11b,    /* OXPCIe952 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc11f,    /* OXPCIe952 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc120,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc124,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc138,    /* OXPCIe952 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc13d,    /* OXPCIe952 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc140,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc141,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc144,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc145,    /* OXPCIe952 1 Legacy UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc158,    /* OXPCIe952 2 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc15d,    /* OXPCIe952 2 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc208,    /* OXPCIe954 4 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_4_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc20d,    /* OXPCIe954 4 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_4_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc308,    /* OXPCIe958 8 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_8_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc30d,    /* OXPCIe958 8 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_8_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc40b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc40f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc41b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc41f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc42b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc42f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc43b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc43f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc44b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc44f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc45b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc45f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc46b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc46f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc47b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc47f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc48b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc48f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc49b,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc49f,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4ab,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4af,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4bb,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4bf,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4cb,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_OXSEMI, 0xc4cf,    /* OXPCIe200 1 Native UART */
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	/*
	 * Mainpine Inc. IQ Express "Rev3" utilizing OxSemi Tornaकरो
	 */
	अणु	PCI_VENDOR_ID_MAINPINE, 0x4000,	/* IQ Express 1 Port V.34 Super-G3 Fax */
		PCI_VENDOR_ID_MAINPINE, 0x4001, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_MAINPINE, 0x4000,	/* IQ Express 2 Port V.34 Super-G3 Fax */
		PCI_VENDOR_ID_MAINPINE, 0x4002, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_MAINPINE, 0x4000,	/* IQ Express 4 Port V.34 Super-G3 Fax */
		PCI_VENDOR_ID_MAINPINE, 0x4004, 0, 0,
		pbn_oxsemi_4_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_MAINPINE, 0x4000,	/* IQ Express 8 Port V.34 Super-G3 Fax */
		PCI_VENDOR_ID_MAINPINE, 0x4008, 0, 0,
		pbn_oxsemi_8_4000000 पूर्ण,

	/*
	 * Digi/IBM PCIe 2-port Async EIA-232 Adapter utilizing OxSemi Tornaकरो
	 */
	अणु	PCI_VENDOR_ID_DIGI, PCIE_DEVICE_ID_NEO_2_OX_IBM,
		PCI_SUBVENDOR_ID_IBM, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,

	/*
	 * SBS Technologies, Inc. P-Octal and PMC-OCTPRO cards,
	 * from skokodyn@yahoo.com
	 */
	अणु	PCI_VENDOR_ID_SBSMODULARIO, PCI_DEVICE_ID_OCTPRO,
		PCI_SUBVENDOR_ID_SBSMODULARIO, PCI_SUBDEVICE_ID_OCTPRO232, 0, 0,
		pbn_sbsxrsio पूर्ण,
	अणु	PCI_VENDOR_ID_SBSMODULARIO, PCI_DEVICE_ID_OCTPRO,
		PCI_SUBVENDOR_ID_SBSMODULARIO, PCI_SUBDEVICE_ID_OCTPRO422, 0, 0,
		pbn_sbsxrsio पूर्ण,
	अणु	PCI_VENDOR_ID_SBSMODULARIO, PCI_DEVICE_ID_OCTPRO,
		PCI_SUBVENDOR_ID_SBSMODULARIO, PCI_SUBDEVICE_ID_POCTAL232, 0, 0,
		pbn_sbsxrsio पूर्ण,
	अणु	PCI_VENDOR_ID_SBSMODULARIO, PCI_DEVICE_ID_OCTPRO,
		PCI_SUBVENDOR_ID_SBSMODULARIO, PCI_SUBDEVICE_ID_POCTAL422, 0, 0,
		pbn_sbsxrsio पूर्ण,

	/*
	 * Digitan DS560-558, from jimd@esoft.com
	 */
	अणु	PCI_VENDOR_ID_ATT, PCI_DEVICE_ID_ATT_VENUS_MODEM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_1_115200 पूर्ण,

	/*
	 * Titan Electronic cards
	 *  The 400L and 800L have a custom setup quirk.
	 */
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_100,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_100L,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200L,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400L,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800L,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b4_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b4_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b4_bt_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400EH,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800EH,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800EHB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_100E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_1_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_4_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_8_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200EI,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200EISI,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi_2_4000000 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_200V3,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_400V3,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_410V3,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800V3,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_TITAN, PCI_DEVICE_ID_TITAN_800V3B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_4_921600 पूर्ण,

	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_10x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_10x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_10x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_10x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_10x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_10x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_10x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_10x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_10x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_20x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_20x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_1S_20x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_20x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_20x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_2S_20x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_20x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_20x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_4S_20x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_8S_20x_550,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_8S_20x_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_SIIG, PCI_DEVICE_ID_SIIG_8S_20x_850,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_921600 पूर्ण,

	/*
	 * Computone devices submitted by Doug McNash dmcnash@computone.com
	 */
	अणु	PCI_VENDOR_ID_COMPUTONE, PCI_DEVICE_ID_COMPUTONE_PG,
		PCI_SUBVENDOR_ID_COMPUTONE, PCI_SUBDEVICE_ID_COMPUTONE_PG4,
		0, 0, pbn_computone_4 पूर्ण,
	अणु	PCI_VENDOR_ID_COMPUTONE, PCI_DEVICE_ID_COMPUTONE_PG,
		PCI_SUBVENDOR_ID_COMPUTONE, PCI_SUBDEVICE_ID_COMPUTONE_PG8,
		0, 0, pbn_computone_8 पूर्ण,
	अणु	PCI_VENDOR_ID_COMPUTONE, PCI_DEVICE_ID_COMPUTONE_PG,
		PCI_SUBVENDOR_ID_COMPUTONE, PCI_SUBDEVICE_ID_COMPUTONE_PG6,
		0, 0, pbn_computone_6 पूर्ण,

	अणु	PCI_VENDOR_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI95N,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_oxsemi पूर्ण,
	अणु	PCI_VENDOR_ID_TIMEDIA, PCI_DEVICE_ID_TIMEDIA_1889,
		PCI_VENDOR_ID_TIMEDIA, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_1_921600 पूर्ण,

	/*
	 * Sunix PCI serial boards
	 */
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0001, 0, 0,
		pbn_sunix_pci_1s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0002, 0, 0,
		pbn_sunix_pci_2s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0004, 0, 0,
		pbn_sunix_pci_4s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0084, 0, 0,
		pbn_sunix_pci_4s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0008, 0, 0,
		pbn_sunix_pci_8s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0088, 0, 0,
		pbn_sunix_pci_8s पूर्ण,
	अणु	PCI_VENDOR_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999,
		PCI_VENDOR_ID_SUNIX, 0x0010, 0, 0,
		pbn_sunix_pci_16s पूर्ण,

	/*
	 * AFAVLAB serial card, from Harald Welte <laक्रमge@gnumonks.org>
	 */
	अणु	PCI_VENDOR_ID_AFAVLAB, PCI_DEVICE_ID_AFAVLAB_P028,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_AFAVLAB, PCI_DEVICE_ID_AFAVLAB_P030,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_8_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_DSERIAL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUATRO_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUATRO_B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUATTRO_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUATTRO_B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_OCTO_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_OCTO_B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_4_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_PORT_PLUS,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUAD_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_QUAD_B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_2_460800 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_SSERIAL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_1_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_LAVA, PCI_DEVICE_ID_LAVA_PORT_650,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_bt_1_460800 पूर्ण,

	/*
	 * Korenix Jetcard F0/F1 cards (JC1204, JC1208, JC1404, JC1408).
	 * Cards are identअगरied by their subप्रणाली venकरोr IDs, which
	 * (in hex) match the model number.
	 *
	 * Note that JC140x are RS422/485 cards which require ox950
	 * ACR = 0x10, and as such are not currently fully supported.
	 */
	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF0,
		0x1204, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF0,
		0x1208, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,
/*	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF0,
		0x1402, 0x0002, 0, 0,
		pbn_b0_2_921600 पूर्ण, */
/*	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF0,
		0x1404, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण, */
	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF1,
		0x1208, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,

	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF2,
		0x1204, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF2,
		0x1208, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	अणु	PCI_VENDOR_ID_KORENIX, PCI_DEVICE_ID_KORENIX_JETCARDF3,
		0x1208, 0x0004, 0, 0,
		pbn_b0_4_921600 पूर्ण,
	/*
	 * Dell Remote Access Card 4 - Tim_T_Murphy@Dell.com
	 */
	अणु	PCI_VENDOR_ID_DELL, PCI_DEVICE_ID_DELL_RAC4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_1_1382400 पूर्ण,

	/*
	 * Dell Remote Access Card III - Tim_T_Murphy@Dell.com
	 */
	अणु	PCI_VENDOR_ID_DELL, PCI_DEVICE_ID_DELL_RACIII,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_1_1382400 पूर्ण,

	/*
	 * RAStel 2 port modem, gerg@moreton.com.au
	 */
	अणु	PCI_VENDOR_ID_MORETON, PCI_DEVICE_ID_RASTEL_2PORT,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_bt_2_115200 पूर्ण,

	/*
	 * EKF addition क्रम i960 Boards क्रमm EKF with serial port
	 */
	अणु	PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_80960_RP,
		0xE4BF, PCI_ANY_ID, 0, 0,
		pbn_पूर्णांकel_i960 पूर्ण,

	/*
	 * Xircom Cardbus/Ethernet combos
	 */
	अणु	PCI_VENDOR_ID_XIRCOM, PCI_DEVICE_ID_XIRCOM_X3201_MDM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_115200 पूर्ण,
	/*
	 * Xircom RBM56G cardbus modem - Dirk Arnold (temp entry)
	 */
	अणु	PCI_VENDOR_ID_XIRCOM, PCI_DEVICE_ID_XIRCOM_RBM56G,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_115200 पूर्ण,

	/*
	 * Untested PCI modems, sent in from various folks...
	 */

	/*
	 * Elsa Model 56K PCI Modem, from Andreas Rath <arh@01019मुक्तnet.de>
	 */
	अणु	PCI_VENDOR_ID_ROCKWELL, 0x1004,
		0x1048, 0x1500, 0, 0,
		pbn_b1_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_SGI, PCI_DEVICE_ID_SGI_IOC3,
		0xFF00, 0, 0, 0,
		pbn_sgi_ioc3 पूर्ण,

	/*
	 * HP Diva card
	 */
	अणु	PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA,
		PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA_RMP3, 0, 0,
		pbn_b1_1_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_5_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_HP, PCI_DEVICE_ID_HP_DIVA_AUX,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b2_1_115200 पूर्ण,
	/* HPE PCI serial device */
	अणु	PCI_VENDOR_ID_HP_3PAR, PCI_DEVICE_ID_HPE_PCI_SERIAL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_DCI, PCI_DEVICE_ID_DCI_PCCOM2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b3_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_DCI, PCI_DEVICE_ID_DCI_PCCOM4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b3_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_DCI, PCI_DEVICE_ID_DCI_PCCOM8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b3_8_115200 पूर्ण,
	/*
	 * Pericom PI7C9X795[1248] Uno/Dual/Quad/Octal UART
	 */
	अणु   PCI_VENDOR_ID_PERICOM, PCI_DEVICE_ID_PERICOM_PI7C9X7951,
		PCI_ANY_ID, PCI_ANY_ID,
		0,
		0, pbn_pericom_PI7C9X7951 पूर्ण,
	अणु   PCI_VENDOR_ID_PERICOM, PCI_DEVICE_ID_PERICOM_PI7C9X7952,
		PCI_ANY_ID, PCI_ANY_ID,
		0,
		0, pbn_pericom_PI7C9X7952 पूर्ण,
	अणु   PCI_VENDOR_ID_PERICOM, PCI_DEVICE_ID_PERICOM_PI7C9X7954,
		PCI_ANY_ID, PCI_ANY_ID,
		0,
		0, pbn_pericom_PI7C9X7954 पूर्ण,
	अणु   PCI_VENDOR_ID_PERICOM, PCI_DEVICE_ID_PERICOM_PI7C9X7958,
		PCI_ANY_ID, PCI_ANY_ID,
		0,
		0, pbn_pericom_PI7C9X7958 पूर्ण,
	/*
	 * ACCES I/O Products quad
	 */
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_2SDB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM_2S,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SDB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4S,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM232_2DB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM232_2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4DB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM232_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_2SMDB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM_2SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SMDB,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_COM_4SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_1,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7951 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM422_2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM422_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM485_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM_2S,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4S,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM232_2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM232_2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM232_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_MPCIE_ICM232_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM_2SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7952 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM422_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM485_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM422_8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7958 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM485_8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7958 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM232_4,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM232_8,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7958 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_4SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_COM_8SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7958 पूर्ण,
	अणु	PCI_VENDOR_ID_ACCESIO, PCI_DEVICE_ID_ACCESIO_PCIE_ICM_4SM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pericom_PI7C9X7954 पूर्ण,
	/*
	 * Topic TP560 Data/Fax/Voice 56k modem (reported by Evan Clarke)
	 */
	अणु	PCI_VENDOR_ID_TOPIC, PCI_DEVICE_ID_TOPIC_TP560,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b0_1_115200 पूर्ण,
	/*
	 * ITE
	 */
	अणु	PCI_VENDOR_ID_ITE, PCI_DEVICE_ID_ITE_8872,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		pbn_b1_bt_1_115200 पूर्ण,

	/*
	 * IntaShield IS-200
	 */
	अणु	PCI_VENDOR_ID_INTASHIELD, PCI_DEVICE_ID_INTASHIELD_IS200,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,	/* 135a.0811 */
		pbn_b2_2_115200 पूर्ण,
	/*
	 * IntaShield IS-400
	 */
	अणु	PCI_VENDOR_ID_INTASHIELD, PCI_DEVICE_ID_INTASHIELD_IS400,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,    /* 135a.0dc0 */
		pbn_b2_4_115200 पूर्ण,
	/*
	 * BrainBoxes UC-260
	 */
	अणु	PCI_VENDOR_ID_INTASHIELD, 0x0D21,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_COMMUNICATION_MULTISERIAL << 8, 0xffff00,
		pbn_b2_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_INTASHIELD, 0x0E34,
		PCI_ANY_ID, PCI_ANY_ID,
		 PCI_CLASS_COMMUNICATION_MULTISERIAL << 8, 0xffff00,
		pbn_b2_4_115200 पूर्ण,
	/*
	 * Perle PCI-RAS cards
	 */
	अणु       PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		PCI_SUBVENDOR_ID_PERLE, PCI_SUBDEVICE_ID_PCI_RAS4,
		0, 0, pbn_b2_4_921600 पूर्ण,
	अणु       PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030,
		PCI_SUBVENDOR_ID_PERLE, PCI_SUBDEVICE_ID_PCI_RAS8,
		0, 0, pbn_b2_8_921600 पूर्ण,

	/*
	 * Mainpine series cards: Fairly standard layout but fools
	 * parts of the स्वतःdetect in some हालs and uses otherwise
	 * unmatched communications subclasses in the PCI Express हाल
	 */

	अणु	/* RockForceDUO */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0200,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForceQUATRO */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0300,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForceDUO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0400,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForceQUATRO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0500,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForce+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0600,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForce+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0700,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForceOCTO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0800,
		0, 0, pbn_b0_8_115200 पूर्ण,
	अणु	/* RockForceDUO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0C00,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForceQUARTRO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x0D00,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForceOCTO+ */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x1D00,
		0, 0, pbn_b0_8_115200 पूर्ण,
	अणु	/* RockForceD1 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2000,
		0, 0, pbn_b0_1_115200 पूर्ण,
	अणु	/* RockForceF1 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2100,
		0, 0, pbn_b0_1_115200 पूर्ण,
	अणु	/* RockForceD2 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2200,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForceF2 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2300,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* RockForceD4 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2400,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForceF4 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2500,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* RockForceD8 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2600,
		0, 0, pbn_b0_8_115200 पूर्ण,
	अणु	/* RockForceF8 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x2700,
		0, 0, pbn_b0_8_115200 पूर्ण,
	अणु	/* IQ Express D1 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3000,
		0, 0, pbn_b0_1_115200 पूर्ण,
	अणु	/* IQ Express F1 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3100,
		0, 0, pbn_b0_1_115200 पूर्ण,
	अणु	/* IQ Express D2 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3200,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* IQ Express F2 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3300,
		0, 0, pbn_b0_2_115200 पूर्ण,
	अणु	/* IQ Express D4 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3400,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* IQ Express F4 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3500,
		0, 0, pbn_b0_4_115200 पूर्ण,
	अणु	/* IQ Express D8 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3C00,
		0, 0, pbn_b0_8_115200 पूर्ण,
	अणु	/* IQ Express F8 */
		PCI_VENDOR_ID_MAINPINE, PCI_DEVICE_ID_MAINPINE_PBRIDGE,
		PCI_VENDOR_ID_MAINPINE, 0x3D00,
		0, 0, pbn_b0_8_115200 पूर्ण,


	/*
	 * PA Semi PA6T-1682M on-chip UART
	 */
	अणु	PCI_VENDOR_ID_PASEMI, 0xa004,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_pasemi_1682M पूर्ण,

	/*
	 * National Instruments
	 */
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI23216,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_16_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI2328,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI2324I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI2322I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8420_23216,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_16_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8420_2328,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_8_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8420_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8420_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8422_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_4_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8422_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_b1_bt_2_115200 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8430_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_2 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8430_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_2 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8430_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_4 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8430_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_4 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8430_2328,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_8 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8430_2328,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_8 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8430_23216,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_16 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8430_23216,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_16 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8432_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_2 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8432_2322,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_2 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PXI8432_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_4 पूर्ण,
	अणु	PCI_VENDOR_ID_NI, PCI_DEVICE_ID_NI_PCI8432_2324,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_ni8430_4 पूर्ण,

	/*
	 * MOXA
	 */
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP102E,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_2p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP102EL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_2p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP104EL_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_4p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP114EL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_4p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP116E_A_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP116E_A_B,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP118EL_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP118E_A_I,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP132EL,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_2p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP134EL_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_4p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP138E_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,
	अणु	PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP168EL_A,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_moxa8250_8p पूर्ण,

	/*
	* ADDI-DATA GmbH communication cards <info@addi-data.com>
	*/
	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7500,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_4_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7420,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_2_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7300,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_AMCC,
		PCI_DEVICE_ID_AMCC_ADDIDATA_APCI7800,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b1_8_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7500_2,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_4_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7420_2,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_2_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7300_2,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7500_3,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_4_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7420_3,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_2_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7300_3,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCI7800_3,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_b0_8_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCIe7500,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_ADDIDATA_PCIe_4_3906250 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCIe7420,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_ADDIDATA_PCIe_2_3906250 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCIe7300,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_ADDIDATA_PCIe_1_3906250 पूर्ण,

	अणु	PCI_VENDOR_ID_ADDIDATA,
		PCI_DEVICE_ID_ADDIDATA_APCIe7800,
		PCI_ANY_ID,
		PCI_ANY_ID,
		0,
		0,
		pbn_ADDIDATA_PCIe_8_3906250 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9835,
		PCI_VENDOR_ID_IBM, 0x0299,
		0, 0, pbn_b0_bt_2_115200 पूर्ण,

	/*
	 * other NetMos 9835 devices are most likely handled by the
	 * parport_serial driver, check drivers/parport/parport_serial.c
	 * beक्रमe adding them here.
	 */

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9901,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	/* the 9901 is a rebअक्रमed 9912 */
	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9912,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9922,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9904,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
		0xA000, 0x3002,
		0, 0, pbn_NETMOS9900_2s_115200 पूर्ण,

	/*
	 * Best Connectivity and Rosewill PCI Multi I/O cards
	 */

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
		0xA000, 0x1000,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
		0xA000, 0x3002,
		0, 0, pbn_b0_bt_2_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
		0xA000, 0x3004,
		0, 0, pbn_b0_bt_4_115200 पूर्ण,
	/* Intel CE4100 */
	अणु	PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CE4100_UART,
		PCI_ANY_ID,  PCI_ANY_ID, 0, 0,
		pbn_ce4100_1_115200 पूर्ण,

	/*
	 * Cronyx Omega PCI
	 */
	अणु	PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_CRONYX_OMEGA,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_omegapci पूर्ण,

	/*
	 * Broadcom TruManage
	 */
	अणु	PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_BROADCOM_TRUMANAGE,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		pbn_brcm_trumanage पूर्ण,

	/*
	 * AgeStar as-prs2-009
	 */
	अणु	PCI_VENDOR_ID_AGESTAR, PCI_DEVICE_ID_AGESTAR_9375,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_bt_2_115200 पूर्ण,

	/*
	 * WCH CH353 series devices: The 2S1P is handled by parport_serial
	 * so not listed here.
	 */
	अणु	PCI_VENDOR_ID_WCH, PCI_DEVICE_ID_WCH_CH353_4S,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_bt_4_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_WCH, PCI_DEVICE_ID_WCH_CH353_2S1PF,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_bt_2_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_WCH, PCI_DEVICE_ID_WCH_CH355_4S,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_bt_4_115200 पूर्ण,

	अणु	PCIE_VENDOR_ID_WCH, PCIE_DEVICE_ID_WCH_CH382_2S,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_wch382_2 पूर्ण,

	अणु	PCIE_VENDOR_ID_WCH, PCIE_DEVICE_ID_WCH_CH384_4S,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_wch384_4 पूर्ण,

	अणु	PCIE_VENDOR_ID_WCH, PCIE_DEVICE_ID_WCH_CH384_8S,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_wch384_8 पूर्ण,
	/*
	 * Realtek RealManage
	 */
	अणु	PCI_VENDOR_ID_REALTEK, 0x816a,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_1_115200 पूर्ण,

	अणु	PCI_VENDOR_ID_REALTEK, 0x816b,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0, pbn_b0_1_115200 पूर्ण,

	/* Fपूर्णांकek PCI serial cards */
	अणु PCI_DEVICE(0x1c29, 0x1104), .driver_data = pbn_fपूर्णांकek_4 पूर्ण,
	अणु PCI_DEVICE(0x1c29, 0x1108), .driver_data = pbn_fपूर्णांकek_8 पूर्ण,
	अणु PCI_DEVICE(0x1c29, 0x1112), .driver_data = pbn_fपूर्णांकek_12 पूर्ण,
	अणु PCI_DEVICE(0x1c29, 0x1204), .driver_data = pbn_fपूर्णांकek_F81504A पूर्ण,
	अणु PCI_DEVICE(0x1c29, 0x1208), .driver_data = pbn_fपूर्णांकek_F81508A पूर्ण,
	अणु PCI_DEVICE(0x1c29, 0x1212), .driver_data = pbn_fपूर्णांकek_F81512A पूर्ण,

	/* MKS Tenta SCOM-080x serial cards */
	अणु PCI_DEVICE(0x1601, 0x0800), .driver_data = pbn_b0_4_1250000 पूर्ण,
	अणु PCI_DEVICE(0x1601, 0xa801), .driver_data = pbn_b0_4_1250000 पूर्ण,

	/* Amazon PCI serial device */
	अणु PCI_DEVICE(0x1d0f, 0x8250), .driver_data = pbn_b0_1_115200 पूर्ण,

	/*
	 * These entries match devices with class COMMUNICATION_SERIAL,
	 * COMMUNICATION_MODEM or COMMUNICATION_MULTISERIAL
	 */
	अणु	PCI_ANY_ID, PCI_ANY_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_COMMUNICATION_SERIAL << 8,
		0xffff00, pbn_शेष पूर्ण,
	अणु	PCI_ANY_ID, PCI_ANY_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_COMMUNICATION_MODEM << 8,
		0xffff00, pbn_शेष पूर्ण,
	अणु	PCI_ANY_ID, PCI_ANY_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CLASS_COMMUNICATION_MULTISERIAL << 8,
		0xffff00, pbn_शेष पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल pci_ers_result_t serial8250_io_error_detected(काष्ठा pci_dev *dev,
						pci_channel_state_t state)
अणु
	काष्ठा serial_निजी *priv = pci_get_drvdata(dev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (priv)
		pciserial_detach_ports(priv);

	pci_disable_device(dev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t serial8250_io_slot_reset(काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	rc = pci_enable_device(dev);

	अगर (rc)
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_restore_state(dev);
	pci_save_state(dev);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम serial8250_io_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा serial_निजी *priv = pci_get_drvdata(dev);
	काष्ठा serial_निजी *new;

	अगर (!priv)
		वापस;

	new = pciserial_init_ports(dev, priv->board);
	अगर (!IS_ERR(new)) अणु
		pci_set_drvdata(dev, new);
		kमुक्त(priv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers serial8250_err_handler = अणु
	.error_detected = serial8250_io_error_detected,
	.slot_reset = serial8250_io_slot_reset,
	.resume = serial8250_io_resume,
पूर्ण;

अटल काष्ठा pci_driver serial_pci_driver = अणु
	.name		= "serial",
	.probe		= pciserial_init_one,
	.हटाओ		= pciserial_हटाओ_one,
	.driver         = अणु
		.pm     = &pciserial_pm_ops,
	पूर्ण,
	.id_table	= serial_pci_tbl,
	.err_handler	= &serial8250_err_handler,
पूर्ण;

module_pci_driver(serial_pci_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic 8250/16x50 PCI serial probe module");
MODULE_DEVICE_TABLE(pci, serial_pci_tbl);
