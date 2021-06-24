<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ni_65xx.c
 * Comedi driver क्रम National Instruments PCI-65xx अटल dio boards
 *
 * Copyright (C) 2006 Jon Grierson <jd@renko.co.uk>
 * Copyright (C) 2006 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999,2002,2003 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_65xx
 * Description: National Instruments 65xx अटल dio boards
 * Author: Jon Grierson <jd@renko.co.uk>,
 *	   Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Status: testing
 * Devices: [National Instruments] PCI-6509 (pci-6509), PXI-6509 (pxi-6509),
 *   PCI-6510 (pci-6510), PCI-6511 (pci-6511), PXI-6511 (pxi-6511),
 *   PCI-6512 (pci-6512), PXI-6512 (pxi-6512), PCI-6513 (pci-6513),
 *   PXI-6513 (pxi-6513), PCI-6514 (pci-6514), PXI-6514 (pxi-6514),
 *   PCI-6515 (pxi-6515), PXI-6515 (pxi-6515), PCI-6516 (pci-6516),
 *   PCI-6517 (pci-6517), PCI-6518 (pci-6518), PCI-6519 (pci-6519),
 *   PCI-6520 (pci-6520), PCI-6521 (pci-6521), PXI-6521 (pxi-6521),
 *   PCI-6528 (pci-6528), PXI-6528 (pxi-6528)
 * Updated: Mon, 21 Jul 2014 12:49:58 +0000
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 *
 * Based on the PCI-6527 driver by ds.
 * The पूर्णांकerrupt subdevice (subdevice 3) is probably broken क्रम all
 * boards except maybe the 6514.
 *
 * This driver previously inverted the outमाला_दो on PCI-6513 through to
 * PCI-6519 and on PXI-6513 through to PXI-6515.  It no दीर्घer inverts
 * outमाला_दो on those cards by शेष as it didn't make much sense.  If
 * you require the outमाला_दो to be inverted on those cards क्रम legacy
 * reasons, set the module parameter "legacy_invert_outputs=true" when
 * loading the module, or set "ni_65xx.legacy_invert_outputs=true" on
 * the kernel command line अगर the driver is built in to the kernel.
 */

/*
 * Manuals (available from ftp://ftp.natinst.com/support/manuals)
 *
 *	370106b.pdf	6514 Register Level Programmer Manual
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

/*
 * PCI BAR1 Register Map
 */

/* Non-recurring Registers (8-bit except where noted) */
#घोषणा NI_65XX_ID_REG			0x00
#घोषणा NI_65XX_CLR_REG			0x01
#घोषणा NI_65XX_CLR_WDOG_INT		BIT(6)
#घोषणा NI_65XX_CLR_WDOG_PING		BIT(5)
#घोषणा NI_65XX_CLR_WDOG_EXP		BIT(4)
#घोषणा NI_65XX_CLR_EDGE_INT		BIT(3)
#घोषणा NI_65XX_CLR_OVERFLOW_INT	BIT(2)
#घोषणा NI_65XX_STATUS_REG		0x02
#घोषणा NI_65XX_STATUS_WDOG_INT		BIT(5)
#घोषणा NI_65XX_STATUS_FALL_EDGE	BIT(4)
#घोषणा NI_65XX_STATUS_RISE_EDGE	BIT(3)
#घोषणा NI_65XX_STATUS_INT		BIT(2)
#घोषणा NI_65XX_STATUS_OVERFLOW_INT	BIT(1)
#घोषणा NI_65XX_STATUS_EDGE_INT		BIT(0)
#घोषणा NI_65XX_CTRL_REG		0x03
#घोषणा NI_65XX_CTRL_WDOG_ENA		BIT(5)
#घोषणा NI_65XX_CTRL_FALL_EDGE_ENA	BIT(4)
#घोषणा NI_65XX_CTRL_RISE_EDGE_ENA	BIT(3)
#घोषणा NI_65XX_CTRL_INT_ENA		BIT(2)
#घोषणा NI_65XX_CTRL_OVERFLOW_ENA	BIT(1)
#घोषणा NI_65XX_CTRL_EDGE_ENA		BIT(0)
#घोषणा NI_65XX_REV_REG			0x04 /* 32-bit */
#घोषणा NI_65XX_FILTER_REG		0x08 /* 32-bit */
#घोषणा NI_65XX_RTSI_ROUTE_REG		0x0c /* 16-bit */
#घोषणा NI_65XX_RTSI_EDGE_REG		0x0e /* 16-bit */
#घोषणा NI_65XX_RTSI_WDOG_REG		0x10 /* 16-bit */
#घोषणा NI_65XX_RTSI_TRIG_REG		0x12 /* 16-bit */
#घोषणा NI_65XX_AUTO_CLK_SEL_REG	0x14 /* PXI-6528 only */
#घोषणा NI_65XX_AUTO_CLK_SEL_STATUS	BIT(1)
#घोषणा NI_65XX_AUTO_CLK_SEL_DISABLE	BIT(0)
#घोषणा NI_65XX_WDOG_CTRL_REG		0x15
#घोषणा NI_65XX_WDOG_CTRL_ENA		BIT(0)
#घोषणा NI_65XX_RTSI_CFG_REG		0x16
#घोषणा NI_65XX_RTSI_CFG_RISE_SENSE	BIT(2)
#घोषणा NI_65XX_RTSI_CFG_FALL_SENSE	BIT(1)
#घोषणा NI_65XX_RTSI_CFG_SYNC_DETECT	BIT(0)
#घोषणा NI_65XX_WDOG_STATUS_REG		0x17
#घोषणा NI_65XX_WDOG_STATUS_EXP		BIT(0)
#घोषणा NI_65XX_WDOG_INTERVAL_REG	0x18 /* 32-bit */

/* Recurring port रेजिस्टरs (8-bit) */
#घोषणा NI_65XX_PORT(x)			((x) * 0x10)
#घोषणा NI_65XX_IO_DATA_REG(x)		(0x40 + NI_65XX_PORT(x))
#घोषणा NI_65XX_IO_SEL_REG(x)		(0x41 + NI_65XX_PORT(x))
#घोषणा NI_65XX_IO_SEL_OUTPUT		0
#घोषणा NI_65XX_IO_SEL_INPUT		BIT(0)
#घोषणा NI_65XX_RISE_EDGE_ENA_REG(x)	(0x42 + NI_65XX_PORT(x))
#घोषणा NI_65XX_FALL_EDGE_ENA_REG(x)	(0x43 + NI_65XX_PORT(x))
#घोषणा NI_65XX_FILTER_ENA(x)		(0x44 + NI_65XX_PORT(x))
#घोषणा NI_65XX_WDOG_HIZ_REG(x)		(0x46 + NI_65XX_PORT(x))
#घोषणा NI_65XX_WDOG_ENA(x)		(0x47 + NI_65XX_PORT(x))
#घोषणा NI_65XX_WDOG_HI_LO_REG(x)	(0x48 + NI_65XX_PORT(x))
#घोषणा NI_65XX_RTSI_ENA(x)		(0x49 + NI_65XX_PORT(x))

#घोषणा NI_65XX_PORT_TO_CHAN(x)		((x) * 8)
#घोषणा NI_65XX_CHAN_TO_PORT(x)		((x) / 8)
#घोषणा NI_65XX_CHAN_TO_MASK(x)		(1 << ((x) % 8))

क्रमागत ni_65xx_boardid अणु
	BOARD_PCI6509,
	BOARD_PXI6509,
	BOARD_PCI6510,
	BOARD_PCI6511,
	BOARD_PXI6511,
	BOARD_PCI6512,
	BOARD_PXI6512,
	BOARD_PCI6513,
	BOARD_PXI6513,
	BOARD_PCI6514,
	BOARD_PXI6514,
	BOARD_PCI6515,
	BOARD_PXI6515,
	BOARD_PCI6516,
	BOARD_PCI6517,
	BOARD_PCI6518,
	BOARD_PCI6519,
	BOARD_PCI6520,
	BOARD_PCI6521,
	BOARD_PXI6521,
	BOARD_PCI6528,
	BOARD_PXI6528,
पूर्ण;

काष्ठा ni_65xx_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक num_dio_ports;
	अचिन्हित पूर्णांक num_di_ports;
	अचिन्हित पूर्णांक num_करो_ports;
	अचिन्हित पूर्णांक legacy_invert:1;
पूर्ण;

अटल स्थिर काष्ठा ni_65xx_board ni_65xx_boards[] = अणु
	[BOARD_PCI6509] = अणु
		.name		= "pci-6509",
		.num_dio_ports	= 12,
	पूर्ण,
	[BOARD_PXI6509] = अणु
		.name		= "pxi-6509",
		.num_dio_ports	= 12,
	पूर्ण,
	[BOARD_PCI6510] = अणु
		.name		= "pci-6510",
		.num_di_ports	= 4,
	पूर्ण,
	[BOARD_PCI6511] = अणु
		.name		= "pci-6511",
		.num_di_ports	= 8,
	पूर्ण,
	[BOARD_PXI6511] = अणु
		.name		= "pxi-6511",
		.num_di_ports	= 8,
	पूर्ण,
	[BOARD_PCI6512] = अणु
		.name		= "pci-6512",
		.num_करो_ports	= 8,
	पूर्ण,
	[BOARD_PXI6512] = अणु
		.name		= "pxi-6512",
		.num_करो_ports	= 8,
	पूर्ण,
	[BOARD_PCI6513] = अणु
		.name		= "pci-6513",
		.num_करो_ports	= 8,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PXI6513] = अणु
		.name		= "pxi-6513",
		.num_करो_ports	= 8,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6514] = अणु
		.name		= "pci-6514",
		.num_di_ports	= 4,
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PXI6514] = अणु
		.name		= "pxi-6514",
		.num_di_ports	= 4,
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6515] = अणु
		.name		= "pci-6515",
		.num_di_ports	= 4,
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PXI6515] = अणु
		.name		= "pxi-6515",
		.num_di_ports	= 4,
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6516] = अणु
		.name		= "pci-6516",
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6517] = अणु
		.name		= "pci-6517",
		.num_करो_ports	= 4,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6518] = अणु
		.name		= "pci-6518",
		.num_di_ports	= 2,
		.num_करो_ports	= 2,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6519] = अणु
		.name		= "pci-6519",
		.num_di_ports	= 2,
		.num_करो_ports	= 2,
		.legacy_invert	= 1,
	पूर्ण,
	[BOARD_PCI6520] = अणु
		.name		= "pci-6520",
		.num_di_ports	= 1,
		.num_करो_ports	= 1,
	पूर्ण,
	[BOARD_PCI6521] = अणु
		.name		= "pci-6521",
		.num_di_ports	= 1,
		.num_करो_ports	= 1,
	पूर्ण,
	[BOARD_PXI6521] = अणु
		.name		= "pxi-6521",
		.num_di_ports	= 1,
		.num_करो_ports	= 1,
	पूर्ण,
	[BOARD_PCI6528] = अणु
		.name		= "pci-6528",
		.num_di_ports	= 3,
		.num_करो_ports	= 3,
	पूर्ण,
	[BOARD_PXI6528] = अणु
		.name		= "pxi-6528",
		.num_di_ports	= 3,
		.num_करो_ports	= 3,
	पूर्ण,
पूर्ण;

अटल bool ni_65xx_legacy_invert_outमाला_दो;
module_param_named(legacy_invert_outमाला_दो, ni_65xx_legacy_invert_outमाला_दो,
		   bool, 0444);
MODULE_PARM_DESC(legacy_invert_outमाला_दो,
		 "invert outputs of PCI/PXI-6513/6514/6515/6516/6517/6518/6519 for compatibility with old user code");

अटल अचिन्हित पूर्णांक ni_65xx_num_ports(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा ni_65xx_board *board = dev->board_ptr;

	वापस board->num_dio_ports + board->num_di_ports + board->num_करो_ports;
पूर्ण

अटल व्योम ni_65xx_disable_input_filters(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक num_ports = ni_65xx_num_ports(dev);
	पूर्णांक i;

	/* disable input filtering on all ports */
	क्रम (i = 0; i < num_ports; ++i)
		ग_लिखोb(0x00, dev->mmio + NI_65XX_FILTER_ENA(i));

	/* set filter पूर्णांकerval to 0 (32bit reg) */
	ग_लिखोl(0x00000000, dev->mmio + NI_65XX_FILTER_REG);
पूर्ण

/* updates edge detection क्रम base_chan to base_chan+31 */
अटल व्योम ni_65xx_update_edge_detection(काष्ठा comedi_device *dev,
					  अचिन्हित पूर्णांक base_chan,
					  अचिन्हित पूर्णांक rising,
					  अचिन्हित पूर्णांक falling)
अणु
	अचिन्हित पूर्णांक num_ports = ni_65xx_num_ports(dev);
	अचिन्हित पूर्णांक port;

	अगर (base_chan >= NI_65XX_PORT_TO_CHAN(num_ports))
		वापस;

	क्रम (port = NI_65XX_CHAN_TO_PORT(base_chan); port < num_ports; port++) अणु
		पूर्णांक bitshअगरt = (पूर्णांक)(NI_65XX_PORT_TO_CHAN(port) - base_chan);
		अचिन्हित पूर्णांक port_mask, port_rising, port_falling;

		अगर (bitshअगरt >= 32)
			अवरोध;

		अगर (bitshअगरt >= 0) अणु
			port_mask = ~0U >> bitshअगरt;
			port_rising = rising >> bitshअगरt;
			port_falling = falling >> bitshअगरt;
		पूर्ण अन्यथा अणु
			port_mask = ~0U << -bitshअगरt;
			port_rising = rising << -bitshअगरt;
			port_falling = falling << -bitshअगरt;
		पूर्ण
		अगर (port_mask & 0xff) अणु
			अगर (~port_mask & 0xff) अणु
				port_rising |=
				    पढ़ोb(dev->mmio +
					  NI_65XX_RISE_EDGE_ENA_REG(port)) &
				    ~port_mask;
				port_falling |=
				    पढ़ोb(dev->mmio +
					  NI_65XX_FALL_EDGE_ENA_REG(port)) &
				    ~port_mask;
			पूर्ण
			ग_लिखोb(port_rising & 0xff,
			       dev->mmio + NI_65XX_RISE_EDGE_ENA_REG(port));
			ग_लिखोb(port_falling & 0xff,
			       dev->mmio + NI_65XX_FALL_EDGE_ENA_REG(port));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ni_65xx_disable_edge_detection(काष्ठा comedi_device *dev)
अणु
	/* clear edge detection क्रम channels 0 to 31 */
	ni_65xx_update_edge_detection(dev, 0, 0, 0);
	/* clear edge detection क्रम channels 32 to 63 */
	ni_65xx_update_edge_detection(dev, 32, 0, 0);
	/* clear edge detection क्रम channels 64 to 95 */
	ni_65xx_update_edge_detection(dev, 64, 0, 0);
पूर्ण

अटल पूर्णांक ni_65xx_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ base_port = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक chan_mask = NI_65XX_CHAN_TO_MASK(chan);
	अचिन्हित पूर्णांक port = base_port + NI_65XX_CHAN_TO_PORT(chan);
	अचिन्हित पूर्णांक पूर्णांकerval;
	अचिन्हित पूर्णांक val;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_FILTER:
		/*
		 * The deglitch filter पूर्णांकerval is specअगरied in nanoseconds.
		 * The hardware supports पूर्णांकervals in 200ns increments. Round
		 * the user values up and वापस the actual पूर्णांकerval.
		 */
		पूर्णांकerval = (data[1] + 100) / 200;
		अगर (पूर्णांकerval > 0xfffff)
			पूर्णांकerval = 0xfffff;
		data[1] = पूर्णांकerval * 200;

		/*
		 * Enable/disable the channel क्रम deglitch filtering. Note
		 * that the filter पूर्णांकerval is never set to '0'. This is करोne
		 * because other channels might still be enabled क्रम filtering.
		 */
		val = पढ़ोb(dev->mmio + NI_65XX_FILTER_ENA(port));
		अगर (पूर्णांकerval) अणु
			ग_लिखोl(पूर्णांकerval, dev->mmio + NI_65XX_FILTER_REG);
			val |= chan_mask;
		पूर्ण अन्यथा अणु
			val &= ~chan_mask;
		पूर्ण
		ग_लिखोb(val, dev->mmio + NI_65XX_FILTER_ENA(port));
		अवरोध;

	हाल INSN_CONFIG_DIO_OUTPUT:
		अगर (s->type != COMEDI_SUBD_DIO)
			वापस -EINVAL;
		ग_लिखोb(NI_65XX_IO_SEL_OUTPUT,
		       dev->mmio + NI_65XX_IO_SEL_REG(port));
		अवरोध;

	हाल INSN_CONFIG_DIO_INPUT:
		अगर (s->type != COMEDI_SUBD_DIO)
			वापस -EINVAL;
		ग_लिखोb(NI_65XX_IO_SEL_INPUT,
		       dev->mmio + NI_65XX_IO_SEL_REG(port));
		अवरोध;

	हाल INSN_CONFIG_DIO_QUERY:
		अगर (s->type != COMEDI_SUBD_DIO)
			वापस -EINVAL;
		val = पढ़ोb(dev->mmio + NI_65XX_IO_SEL_REG(port));
		data[1] = (val == NI_65XX_IO_SEL_INPUT) ? COMEDI_INPUT
							: COMEDI_OUTPUT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_65xx_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ base_port = (अचिन्हित दीर्घ)s->निजी;
	अचिन्हित पूर्णांक base_chan = CR_CHAN(insn->chanspec);
	पूर्णांक last_port_offset = NI_65XX_CHAN_TO_PORT(s->n_chan - 1);
	अचिन्हित पूर्णांक पढ़ो_bits = 0;
	पूर्णांक port_offset;

	क्रम (port_offset = NI_65XX_CHAN_TO_PORT(base_chan);
	     port_offset <= last_port_offset; port_offset++) अणु
		अचिन्हित पूर्णांक port = base_port + port_offset;
		पूर्णांक base_port_channel = NI_65XX_PORT_TO_CHAN(port_offset);
		अचिन्हित पूर्णांक port_mask, port_data, bits;
		पूर्णांक bitshअगरt = base_port_channel - base_chan;

		अगर (bitshअगरt >= 32)
			अवरोध;
		port_mask = data[0];
		port_data = data[1];
		अगर (bitshअगरt > 0) अणु
			port_mask >>= bitshअगरt;
			port_data >>= bitshअगरt;
		पूर्ण अन्यथा अणु
			port_mask <<= -bitshअगरt;
			port_data <<= -bitshअगरt;
		पूर्ण
		port_mask &= 0xff;
		port_data &= 0xff;

		/* update the outमाला_दो */
		अगर (port_mask) अणु
			bits = पढ़ोb(dev->mmio + NI_65XX_IO_DATA_REG(port));
			bits ^= s->io_bits;	/* invert अगर necessary */
			bits &= ~port_mask;
			bits |= (port_data & port_mask);
			bits ^= s->io_bits;	/* invert back */
			ग_लिखोb(bits, dev->mmio + NI_65XX_IO_DATA_REG(port));
		पूर्ण

		/* पढ़ो back the actual state */
		bits = पढ़ोb(dev->mmio + NI_65XX_IO_DATA_REG(port));
		bits ^= s->io_bits;	/* invert अगर necessary */
		अगर (bitshअगरt > 0)
			bits <<= bitshअगरt;
		अन्यथा
			bits >>= -bitshअगरt;

		पढ़ो_bits |= bits;
	पूर्ण
	data[1] = पढ़ो_bits;
	वापस insn->n;
पूर्ण

अटल irqवापस_t ni_65xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित लघु val = 0;

	status = पढ़ोb(dev->mmio + NI_65XX_STATUS_REG);
	अगर ((status & NI_65XX_STATUS_INT) == 0)
		वापस IRQ_NONE;
	अगर ((status & NI_65XX_STATUS_EDGE_INT) == 0)
		वापस IRQ_NONE;

	ग_लिखोb(NI_65XX_CLR_EDGE_INT | NI_65XX_CLR_OVERFLOW_INT,
	       dev->mmio + NI_65XX_CLR_REG);

	comedi_buf_ग_लिखो_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ni_65xx_पूर्णांकr_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_OTHER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

अटल पूर्णांक ni_65xx_पूर्णांकr_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोb(NI_65XX_CLR_EDGE_INT | NI_65XX_CLR_OVERFLOW_INT,
	       dev->mmio + NI_65XX_CLR_REG);
	ग_लिखोb(NI_65XX_CTRL_FALL_EDGE_ENA | NI_65XX_CTRL_RISE_EDGE_ENA |
	       NI_65XX_CTRL_INT_ENA | NI_65XX_CTRL_EDGE_ENA,
	       dev->mmio + NI_65XX_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_65xx_पूर्णांकr_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोb(0x00, dev->mmio + NI_65XX_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_65xx_पूर्णांकr_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = 0;
	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_65xx_पूर्णांकr_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	चयन (data[0]) अणु
	हाल INSN_CONFIG_CHANGE_NOTIFY:
		/* add inकाष्ठाion to check_insn_config_length() */
		अगर (insn->n != 3)
			वापस -EINVAL;

		/* update edge detection क्रम channels 0 to 31 */
		ni_65xx_update_edge_detection(dev, 0, data[1], data[2]);
		/* clear edge detection क्रम channels 32 to 63 */
		ni_65xx_update_edge_detection(dev, 32, 0, 0);
		/* clear edge detection क्रम channels 64 to 95 */
		ni_65xx_update_edge_detection(dev, 64, 0, 0);
		अवरोध;
	हाल INSN_CONFIG_DIGITAL_TRIG:
		/* check trigger number */
		अगर (data[1] != 0)
			वापस -EINVAL;
		/* check digital trigger operation */
		चयन (data[2]) अणु
		हाल COMEDI_DIGITAL_TRIG_DISABLE:
			ni_65xx_disable_edge_detection(dev);
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			/*
			 * update edge detection क्रम channels data[3]
			 * to (data[3] + 31)
			 */
			ni_65xx_update_edge_detection(dev, data[3],
						      data[4], data[5]);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

/* ripped from mite.h and mite_setup2() to aव्योम mite dependency */
#घोषणा MITE_IODWBSR	0xc0	 /* IO Device Winकरोw Base Size Register */
#घोषणा WENAB			BIT(7) /* winकरोw enable */

अटल पूर्णांक ni_65xx_mite_init(काष्ठा pci_dev *pcidev)
अणु
	व्योम __iomem *mite_base;
	u32 मुख्य_phys_addr;

	/* ioremap the MITE रेजिस्टरs (BAR 0) temporarily */
	mite_base = pci_ioremap_bar(pcidev, 0);
	अगर (!mite_base)
		वापस -ENOMEM;

	/* set data winकरोw to मुख्य रेजिस्टरs (BAR 1) */
	मुख्य_phys_addr = pci_resource_start(pcidev, 1);
	ग_लिखोl(मुख्य_phys_addr | WENAB, mite_base + MITE_IODWBSR);

	/* finished with MITE रेजिस्टरs */
	iounmap(mite_base);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_65xx_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा ni_65xx_board *board = शून्य;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (context < ARRAY_SIZE(ni_65xx_boards))
		board = &ni_65xx_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	ret = ni_65xx_mite_init(pcidev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 1);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	ग_लिखोb(NI_65XX_CLR_EDGE_INT | NI_65XX_CLR_OVERFLOW_INT,
	       dev->mmio + NI_65XX_CLR_REG);
	ग_लिखोb(0x00, dev->mmio + NI_65XX_CTRL_REG);

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, ni_65xx_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	dev_info(dev->class_dev, "board: %s, ID=0x%02x", dev->board_name,
		 पढ़ोb(dev->mmio + NI_65XX_ID_REG));

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	अगर (board->num_di_ports) अणु
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE;
		s->n_chan	= NI_65XX_PORT_TO_CHAN(board->num_di_ports);
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= ni_65xx_dio_insn_bits;
		s->insn_config	= ni_65xx_dio_insn_config;

		/* the input ports always start at port 0 */
		s->निजी = (व्योम *)0;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[1];
	अगर (board->num_करो_ports) अणु
		s->type		= COMEDI_SUBD_DO;
		s->subdev_flags	= SDF_WRITABLE;
		s->n_chan	= NI_65XX_PORT_TO_CHAN(board->num_करो_ports);
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= ni_65xx_dio_insn_bits;

		/* the output ports always start after the input ports */
		s->निजी = (व्योम *)(अचिन्हित दीर्घ)board->num_di_ports;

		/*
		 * Use the io_bits to handle the inverted outमाला_दो.  Inverted
		 * outमाला_दो are only supported अगर the "legacy_invert_outputs"
		 * module parameter is set to "true".
		 */
		अगर (ni_65xx_legacy_invert_outमाला_दो && board->legacy_invert)
			s->io_bits = 0xff;

		/* reset all output ports to comedi '0' */
		क्रम (i = 0; i < board->num_करो_ports; ++i) अणु
			ग_लिखोb(s->io_bits,	/* inverted अगर necessary */
			       dev->mmio +
			       NI_65XX_IO_DATA_REG(board->num_di_ports + i));
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[2];
	अगर (board->num_dio_ports) अणु
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
		s->n_chan	= NI_65XX_PORT_TO_CHAN(board->num_dio_ports);
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->insn_bits	= ni_65xx_dio_insn_bits;
		s->insn_config	= ni_65xx_dio_insn_config;

		/* the input/output ports always start at port 0 */
		s->निजी = (व्योम *)0;

		/* configure all ports क्रम input */
		क्रम (i = 0; i < board->num_dio_ports; ++i) अणु
			ग_लिखोb(NI_65XX_IO_SEL_INPUT,
			       dev->mmio + NI_65XX_IO_SEL_REG(i));
		पूर्ण
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 1;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= ni_65xx_पूर्णांकr_insn_bits;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->len_chanlist	= 1;
		s->insn_config	= ni_65xx_पूर्णांकr_insn_config;
		s->करो_cmdtest	= ni_65xx_पूर्णांकr_cmdtest;
		s->करो_cmd	= ni_65xx_पूर्णांकr_cmd;
		s->cancel	= ni_65xx_पूर्णांकr_cancel;
	पूर्ण

	ni_65xx_disable_input_filters(dev);
	ni_65xx_disable_edge_detection(dev);

	वापस 0;
पूर्ण

अटल व्योम ni_65xx_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->mmio)
		ग_लिखोb(0x00, dev->mmio + NI_65XX_CTRL_REG);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver ni_65xx_driver = अणु
	.driver_name	= "ni_65xx",
	.module		= THIS_MODULE,
	.स्वतः_attach	= ni_65xx_स्वतः_attach,
	.detach		= ni_65xx_detach,
पूर्ण;

अटल पूर्णांक ni_65xx_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni_65xx_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni_65xx_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x1710), BOARD_PXI6509 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7085), BOARD_PCI6509 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7086), BOARD_PXI6528 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7087), BOARD_PCI6515 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7088), BOARD_PCI6514 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70a9), BOARD_PCI6528 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70c3), BOARD_PCI6511 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70c8), BOARD_PCI6513 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70c9), BOARD_PXI6515 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70cc), BOARD_PCI6512 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70cd), BOARD_PXI6514 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70d1), BOARD_PXI6513 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70d2), BOARD_PXI6512 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x70d3), BOARD_PXI6511 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7124), BOARD_PCI6510 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7125), BOARD_PCI6516 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7126), BOARD_PCI6517 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7127), BOARD_PCI6518 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x7128), BOARD_PCI6519 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x718b), BOARD_PCI6521 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x718c), BOARD_PXI6521 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x71c5), BOARD_PCI6520 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni_65xx_pci_table);

अटल काष्ठा pci_driver ni_65xx_pci_driver = अणु
	.name		= "ni_65xx",
	.id_table	= ni_65xx_pci_table,
	.probe		= ni_65xx_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni_65xx_driver, ni_65xx_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for NI PCI-65xx static dio boards");
MODULE_LICENSE("GPL");
