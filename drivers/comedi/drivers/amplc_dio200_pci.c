<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* comedi/drivers/amplc_dio200_pci.c
 *
 * Driver क्रम Amplicon PCI215, PCI272, PCIe215, PCIe236, PCIe296.
 *
 * Copyright (C) 2005-2013 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_dio200_pci
 * Description: Amplicon 200 Series PCI Digital I/O
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PCI215 (amplc_dio200_pci), PCIe215, PCIe236,
 *   PCI272, PCIe296
 * Updated: Mon, 18 Mar 2013 15:03:50 +0000
 * Status: works
 *
 * Configuration options:
 *   none
 *
 * Manual configuration of PCI(e) cards is not supported; they are configured
 * स्वतःmatically.
 *
 * SUBDEVICES
 *
 *                     PCI215         PCIe215        PCIe236
 *                  -------------  -------------  -------------
 *   Subdevices           5              8              8
 *    0                 PPI-X          PPI-X          PPI-X
 *    1                 PPI-Y          UNUSED         UNUSED
 *    2                 CTR-Z1         PPI-Y          UNUSED
 *    3                 CTR-Z2         UNUSED         UNUSED
 *    4               INTERRUPT        CTR-Z1         CTR-Z1
 *    5                                CTR-Z2         CTR-Z2
 *    6                                TIMER          TIMER
 *    7                              INTERRUPT      INTERRUPT
 *
 *
 *                     PCI272         PCIe296
 *                  -------------  -------------
 *   Subdevices           4              8
 *    0                 PPI-X          PPI-X1
 *    1                 PPI-Y          PPI-X2
 *    2                 PPI-Z          PPI-Y1
 *    3               INTERRUPT        PPI-Y2
 *    4                                CTR-Z1
 *    5                                CTR-Z2
 *    6                                TIMER
 *    7                              INTERRUPT
 *
 * Each PPI is a 8255 chip providing 24 DIO channels.  The DIO channels
 * are configurable as inमाला_दो or outमाला_दो in four groups:
 *
 *   Port A  - channels  0 to  7
 *   Port B  - channels  8 to 15
 *   Port CL - channels 16 to 19
 *   Port CH - channels 20 to 23
 *
 * Only mode 0 of the 8255 chips is supported.
 *
 * Each CTR is a 8254 chip providing 3 16-bit counter channels.  Each
 * channel is configured inभागidually with INSN_CONFIG inकाष्ठाions.  The
 * specअगरic type of configuration inकाष्ठाion is specअगरied in data[0].
 * Some configuration inकाष्ठाions expect an additional parameter in
 * data[1]; others वापस a value in data[1].  The following configuration
 * inकाष्ठाions are supported:
 *
 *   INSN_CONFIG_SET_COUNTER_MODE.  Sets the counter channel's mode and
 *     BCD/binary setting specअगरied in data[1].
 *
 *   INSN_CONFIG_8254_READ_STATUS.  Reads the status रेजिस्टर value क्रम the
 *     counter channel पूर्णांकo data[1].
 *
 *   INSN_CONFIG_SET_CLOCK_SRC.  Sets the counter channel's घड़ी source as
 *     specअगरied in data[1] (this is a hardware-specअगरic value).  Not
 *     supported on PC214E.  For the other boards, valid घड़ी sources are
 *     0 to 7 as follows:
 *
 *       0.  CLK n, the counter channel's dedicated CLK input from the SK1
 *         connector.  (N.B. क्रम other values, the counter channel's CLKn
 *         pin on the SK1 connector is an output!)
 *       1.  Internal 10 MHz घड़ी.
 *       2.  Internal 1 MHz घड़ी.
 *       3.  Internal 100 kHz घड़ी.
 *       4.  Internal 10 kHz घड़ी.
 *       5.  Internal 1 kHz घड़ी.
 *       6.  OUT n-1, the output of counter channel n-1 (see note 1 below).
 *       7.  Ext Clock, the counter chip's dedicated Ext Clock input from
 *         the SK1 connector.  This pin is shared by all three counter
 *         channels on the chip.
 *
 *     For the PCIe boards, घड़ी sources in the range 0 to 31 are allowed
 *     and the following additional घड़ी sources are defined:
 *
 *       8.  HIGH logic level.
 *       9.  LOW logic level.
 *      10.  "Pattern present" संकेत.
 *      11.  Internal 20 MHz घड़ी.
 *
 *   INSN_CONFIG_GET_CLOCK_SRC.  Returns the counter channel's current
 *     घड़ी source in data[1].  For पूर्णांकernal घड़ी sources, data[2] is set
 *     to the period in ns.
 *
 *   INSN_CONFIG_SET_GATE_SRC.  Sets the counter channel's gate source as
 *     specअगरied in data[2] (this is a hardware-specअगरic value).  Not
 *     supported on PC214E.  For the other boards, valid gate sources are 0
 *     to 7 as follows:
 *
 *       0.  VCC (पूर्णांकernal +5V d.c.), i.e. gate permanently enabled.
 *       1.  GND (पूर्णांकernal 0V d.c.), i.e. gate permanently disabled.
 *       2.  GAT n, the counter channel's dedicated GAT input from the SK1
 *         connector.  (N.B. क्रम other values, the counter channel's GATn
 *         pin on the SK1 connector is an output!)
 *       3.  /OUT n-2, the inverted output of counter channel n-2 (see note
 *         2 below).
 *       4.  Reserved.
 *       5.  Reserved.
 *       6.  Reserved.
 *       7.  Reserved.
 *
 *     For the PCIe boards, gate sources in the range 0 to 31 are allowed;
 *     the following additional घड़ी sources and घड़ी sources 6 and 7 are
 *     (re)defined:
 *
 *       6.  /GAT n, negated version of the counter channel's dedicated
 *         GAT input (negated version of gate source 2).
 *       7.  OUT n-2, the non-inverted output of counter channel n-2
 *         (negated version of gate source 3).
 *       8.  "Pattern present" संकेत, HIGH जबतक pattern present.
 *       9.  "Pattern occurred" latched संकेत, latches HIGH when pattern
 *         occurs.
 *      10.  "Pattern gone away" latched संकेत, latches LOW when pattern
 *         goes away after it occurred.
 *      11.  Negated "pattern present" संकेत, LOW जबतक pattern present
 *         (negated version of gate source 8).
 *      12.  Negated "pattern occurred" latched संकेत, latches LOW when
 *         pattern occurs (negated version of gate source 9).
 *      13.  Negated "pattern gone away" latched संकेत, latches LOW when
 *         pattern goes away after it occurred (negated version of gate
 *         source 10).
 *
 *   INSN_CONFIG_GET_GATE_SRC.  Returns the counter channel's current gate
 *     source in data[2].
 *
 * Clock and gate पूर्णांकerconnection notes:
 *
 *   1.  Clock source OUT n-1 is the output of the preceding channel on the
 *   same counter subdevice अगर n > 0, or the output of channel 2 on the
 *   preceding counter subdevice (see note 3) अगर n = 0.
 *
 *   2.  Gate source /OUT n-2 is the inverted output of channel 0 on the
 *   same counter subdevice अगर n = 2, or the inverted output of channel n+1
 *   on the preceding counter subdevice (see note 3) अगर n < 2.
 *
 *   3.  The counter subdevices are connected in a ring, so the highest
 *   counter subdevice precedes the lowest.
 *
 * The 'TIMER' subdevice is a मुक्त-running 32-bit समयr subdevice.
 *
 * The 'INTERRUPT' subdevice pretends to be a digital input subdevice.  The
 * digital inमाला_दो come from the पूर्णांकerrupt status रेजिस्टर.  The number of
 * channels matches the number of पूर्णांकerrupt sources.  The PC214E करोes not
 * have an पूर्णांकerrupt status रेजिस्टर; see notes on 'INTERRUPT SOURCES'
 * below.
 *
 * INTERRUPT SOURCES
 *
 *                     PCI215         PCIe215        PCIe236
 *                  -------------  -------------  -------------
 *   Sources              6              6              6
 *    0               PPI-X-C0       PPI-X-C0       PPI-X-C0
 *    1               PPI-X-C3       PPI-X-C3       PPI-X-C3
 *    2               PPI-Y-C0       PPI-Y-C0        unused
 *    3               PPI-Y-C3       PPI-Y-C3        unused
 *    4              CTR-Z1-OUT1    CTR-Z1-OUT1    CTR-Z1-OUT1
 *    5              CTR-Z2-OUT1    CTR-Z2-OUT1    CTR-Z2-OUT1
 *
 *                     PCI272         PCIe296
 *                  -------------  -------------
 *   Sources              6              6
 *    0               PPI-X-C0       PPI-X1-C0
 *    1               PPI-X-C3       PPI-X1-C3
 *    2               PPI-Y-C0       PPI-Y1-C0
 *    3               PPI-Y-C3       PPI-Y1-C3
 *    4               PPI-Z-C0      CTR-Z1-OUT1
 *    5               PPI-Z-C3      CTR-Z2-OUT1
 *
 * When an पूर्णांकerrupt source is enabled in the पूर्णांकerrupt source enable
 * रेजिस्टर, a rising edge on the source संकेत latches the corresponding
 * bit to 1 in the पूर्णांकerrupt status रेजिस्टर.
 *
 * When the पूर्णांकerrupt status रेजिस्टर value as a whole (actually, just the
 * 6 least signअगरicant bits) goes from zero to non-zero, the board will
 * generate an पूर्णांकerrupt.  The पूर्णांकerrupt will reमुख्य निश्चितed until the
 * पूर्णांकerrupt status रेजिस्टर is cleared to zero.  To clear a bit to zero in
 * the पूर्णांकerrupt status रेजिस्टर, the corresponding पूर्णांकerrupt source must
 * be disabled in the पूर्णांकerrupt source enable रेजिस्टर (there is no
 * separate पूर्णांकerrupt clear रेजिस्टर).
 *
 * COMMANDS
 *
 * The driver supports a पढ़ो streaming acquisition command on the
 * 'INTERRUPT' subdevice.  The channel list selects the पूर्णांकerrupt sources
 * to be enabled.  All channels will be sampled together (convert_src ==
 * TRIG_NOW).  The scan begins a लघु समय after the hardware पूर्णांकerrupt
 * occurs, subject to पूर्णांकerrupt latencies (scan_begin_src == TRIG_EXT,
 * scan_begin_arg == 0).  The value पढ़ो from the पूर्णांकerrupt status रेजिस्टर
 * is packed पूर्णांकo a लघु value, one bit per requested channel, in the
 * order they appear in the channel list.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "amplc_dio200.h"

/*
 * Board descriptions.
 */

क्रमागत dio200_pci_model अणु
	pci215_model,
	pci272_model,
	pcie215_model,
	pcie236_model,
	pcie296_model
पूर्ण;

अटल स्थिर काष्ठा dio200_board dio200_pci_boards[] = अणु
	[pci215_model] = अणु
		.name		= "pci215",
		.मुख्यbar	= 2,
		.n_subdevs	= 5,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8254, sd_8254, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x10, 0x14, 0x3f पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
	पूर्ण,
	[pci272_model] = अणु
		.name		= "pci272",
		.मुख्यbar	= 2,
		.n_subdevs	= 4,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8255, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु 0x00, 0x08, 0x10, 0x3f पूर्ण,
		.has_पूर्णांक_sce	= true,
	पूर्ण,
	[pcie215_model] = अणु
		.name		= "pcie215",
		.मुख्यbar	= 1,
		.n_subdevs	= 8,
		.sdtype		= अणु
			sd_8255, sd_none, sd_8255, sd_none,
			sd_8254, sd_8254, sd_समयr, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु
			0x00, 0x00, 0x08, 0x00, 0x10, 0x14, 0x00, 0x3f
		पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
		.is_pcie	= true,
	पूर्ण,
	[pcie236_model] = अणु
		.name		= "pcie236",
		.मुख्यbar	= 1,
		.n_subdevs	= 8,
		.sdtype		= अणु
			sd_8255, sd_none, sd_none, sd_none,
			sd_8254, sd_8254, sd_समयr, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु
			0x00, 0x00, 0x00, 0x00, 0x10, 0x14, 0x00, 0x3f
		पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
		.is_pcie	= true,
	पूर्ण,
	[pcie296_model] = अणु
		.name		= "pcie296",
		.मुख्यbar	= 1,
		.n_subdevs	= 8,
		.sdtype		= अणु
			sd_8255, sd_8255, sd_8255, sd_8255,
			sd_8254, sd_8254, sd_समयr, sd_पूर्णांकr
		पूर्ण,
		.sdinfo		= अणु
			0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x00, 0x3f
		पूर्ण,
		.has_पूर्णांक_sce	= true,
		.has_clk_gat_sce = true,
		.is_pcie	= true,
	पूर्ण,
पूर्ण;

/*
 * This function करोes some special set-up क्रम the PCIe boards
 * PCIe215, PCIe236, PCIe296.
 */
अटल पूर्णांक dio200_pcie_board_setup(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	व्योम __iomem *brbase;

	/*
	 * The board uses Altera Cyclone IV with PCI-Express hard IP.
	 * The FPGA configuration has the PCI-Express Avalon-MM Bridge
	 * Control रेजिस्टरs in PCI BAR 0, offset 0, and the length of
	 * these रेजिस्टरs is 0x4000.
	 *
	 * We need to ग_लिखो 0x80 to the "Avalon-MM to PCI-Express Interrupt
	 * Enable" रेजिस्टर at offset 0x50 to allow generation of PCIe
	 * पूर्णांकerrupts when RXmlrq_i is निश्चितed in the SOPC Builder प्रणाली.
	 */
	अगर (pci_resource_len(pcidev, 0) < 0x4000) अणु
		dev_err(dev->class_dev, "error! bad PCI region!\n");
		वापस -EINVAL;
	पूर्ण
	brbase = pci_ioremap_bar(pcidev, 0);
	अगर (!brbase) अणु
		dev_err(dev->class_dev, "error! failed to map registers!\n");
		वापस -ENOMEM;
	पूर्ण
	ग_लिखोl(0x80, brbase + 0x50);
	iounmap(brbase);
	/* Enable "enhanced" features of board. */
	amplc_dio200_set_enhance(dev, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक dio200_pci_स्वतः_attach(काष्ठा comedi_device *dev,
				  अचिन्हित दीर्घ context_model)
अणु
	काष्ठा pci_dev *pci_dev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा dio200_board *board = शून्य;
	अचिन्हित पूर्णांक bar;
	पूर्णांक ret;

	अगर (context_model < ARRAY_SIZE(dio200_pci_boards))
		board = &dio200_pci_boards[context_model];
	अगर (!board)
		वापस -EINVAL;
	dev->board_ptr = board;
	dev->board_name = board->name;

	dev_info(dev->class_dev, "%s: attach pci %s (%s)\n",
		 dev->driver->driver_name, pci_name(pci_dev), dev->board_name);

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	bar = board->मुख्यbar;
	अगर (pci_resource_flags(pci_dev, bar) & IORESOURCE_MEM) अणु
		dev->mmio = pci_ioremap_bar(pci_dev, bar);
		अगर (!dev->mmio) अणु
			dev_err(dev->class_dev,
				"error! cannot remap registers\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->iobase = pci_resource_start(pci_dev, bar);
	पूर्ण

	अगर (board->is_pcie) अणु
		ret = dio200_pcie_board_setup(dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस amplc_dio200_common_attach(dev, pci_dev->irq, IRQF_SHARED);
पूर्ण

अटल काष्ठा comedi_driver dio200_pci_comedi_driver = अणु
	.driver_name	= "amplc_dio200_pci",
	.module		= THIS_MODULE,
	.स्वतः_attach	= dio200_pci_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id dio200_pci_table[] = अणु
	अणु PCI_VDEVICE(AMPLICON, 0x000b), pci215_model पूर्ण,
	अणु PCI_VDEVICE(AMPLICON, 0x000a), pci272_model पूर्ण,
	अणु PCI_VDEVICE(AMPLICON, 0x0011), pcie236_model पूर्ण,
	अणु PCI_VDEVICE(AMPLICON, 0x0012), pcie215_model पूर्ण,
	अणु PCI_VDEVICE(AMPLICON, 0x0014), pcie296_model पूर्ण,
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, dio200_pci_table);

अटल पूर्णांक dio200_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &dio200_pci_comedi_driver,
				      id->driver_data);
पूर्ण

अटल काष्ठा pci_driver dio200_pci_pci_driver = अणु
	.name		= "amplc_dio200_pci",
	.id_table	= dio200_pci_table,
	.probe		= dio200_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(dio200_pci_comedi_driver, dio200_pci_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon 200 Series PCI(e) DIO boards");
MODULE_LICENSE("GPL");
