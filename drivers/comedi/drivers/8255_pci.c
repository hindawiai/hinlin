<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI driver क्रम generic PCI based 8255 digital i/o boards
 * Copyright (C) 2012 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the tested adl_pci7296 driver written by:
 *	Jon Grierson <jd@renko.co.uk>
 * and the experimental cb_pcidio driver written by:
 *	Yoshiya Matsuzaka
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: 8255_pci
 * Description: Generic PCI based 8255 Digital I/O boards
 * Devices: [ADLink] PCI-7224 (adl_pci-7224), PCI-7248 (adl_pci-7248),
 *   PCI-7296 (adl_pci-7296),
 *   [Measurement Computing] PCI-DIO24 (cb_pci-dio24),
 *   PCI-DIO24H (cb_pci-dio24h), PCI-DIO48H (cb_pci-dio48h),
 *   PCI-DIO96H (cb_pci-dio96h),
 *   [National Instruments] PCI-DIO-96 (ni_pci-dio-96),
 *   PCI-DIO-96B (ni_pci-dio-96b), PXI-6508 (ni_pxi-6508),
 *   PCI-6503 (ni_pci-6503), PCI-6503B (ni_pci-6503b),
 *   PCI-6503X (ni_pci-6503x), PXI-6503 (ni_pxi-6503)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Wed, 12 Sep 2012 11:52:01 -0700
 * Status: untested
 *
 * These boards have one or more 8255 digital I/O chips, each of which
 * is supported as a separate 24-channel DIO subdevice.
 *
 * Boards with 24 DIO channels (1 DIO subdevice):
 *
 *   PCI-7224, PCI-DIO24, PCI-DIO24H, PCI-6503, PCI-6503B, PCI-6503X,
 *   PXI-6503
 *
 * Boards with 48 DIO channels (2 DIO subdevices):
 *
 *   PCI-7248, PCI-DIO48H
 *
 * Boards with 96 DIO channels (4 DIO subdevices):
 *
 *   PCI-7296, PCI-DIO96H, PCI-DIO-96, PCI-DIO-96B, PXI-6508
 *
 * Some of these boards also have an 8254 programmable समयr/counter
 * chip.  This chip is not currently supported by this driver.
 *
 * Interrupt support क्रम these boards is also not currently supported.
 *
 * Configuration Options: not applicable, uses PCI स्वतः config.
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"

क्रमागत pci_8255_boardid अणु
	BOARD_ADLINK_PCI7224,
	BOARD_ADLINK_PCI7248,
	BOARD_ADLINK_PCI7296,
	BOARD_CB_PCIDIO24,
	BOARD_CB_PCIDIO24H,
	BOARD_CB_PCIDIO48H_OLD,
	BOARD_CB_PCIDIO48H_NEW,
	BOARD_CB_PCIDIO96H,
	BOARD_NI_PCIDIO96,
	BOARD_NI_PCIDIO96B,
	BOARD_NI_PXI6508,
	BOARD_NI_PCI6503,
	BOARD_NI_PCI6503B,
	BOARD_NI_PCI6503X,
	BOARD_NI_PXI_6503,
पूर्ण;

काष्ठा pci_8255_boardinfo अणु
	स्थिर अक्षर *name;
	पूर्णांक dio_badr;
	पूर्णांक n_8255;
	अचिन्हित पूर्णांक has_mite:1;
पूर्ण;

अटल स्थिर काष्ठा pci_8255_boardinfo pci_8255_boards[] = अणु
	[BOARD_ADLINK_PCI7224] = अणु
		.name		= "adl_pci-7224",
		.dio_badr	= 2,
		.n_8255		= 1,
	पूर्ण,
	[BOARD_ADLINK_PCI7248] = अणु
		.name		= "adl_pci-7248",
		.dio_badr	= 2,
		.n_8255		= 2,
	पूर्ण,
	[BOARD_ADLINK_PCI7296] = अणु
		.name		= "adl_pci-7296",
		.dio_badr	= 2,
		.n_8255		= 4,
	पूर्ण,
	[BOARD_CB_PCIDIO24] = अणु
		.name		= "cb_pci-dio24",
		.dio_badr	= 2,
		.n_8255		= 1,
	पूर्ण,
	[BOARD_CB_PCIDIO24H] = अणु
		.name		= "cb_pci-dio24h",
		.dio_badr	= 2,
		.n_8255		= 1,
	पूर्ण,
	[BOARD_CB_PCIDIO48H_OLD] = अणु
		.name		= "cb_pci-dio48h",
		.dio_badr	= 1,
		.n_8255		= 2,
	पूर्ण,
	[BOARD_CB_PCIDIO48H_NEW] = अणु
		.name		= "cb_pci-dio48h",
		.dio_badr	= 2,
		.n_8255		= 2,
	पूर्ण,
	[BOARD_CB_PCIDIO96H] = अणु
		.name		= "cb_pci-dio96h",
		.dio_badr	= 2,
		.n_8255		= 4,
	पूर्ण,
	[BOARD_NI_PCIDIO96] = अणु
		.name		= "ni_pci-dio-96",
		.dio_badr	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PCIDIO96B] = अणु
		.name		= "ni_pci-dio-96b",
		.dio_badr	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PXI6508] = अणु
		.name		= "ni_pxi-6508",
		.dio_badr	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PCI6503] = अणु
		.name		= "ni_pci-6503",
		.dio_badr	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PCI6503B] = अणु
		.name		= "ni_pci-6503b",
		.dio_badr	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PCI6503X] = अणु
		.name		= "ni_pci-6503x",
		.dio_badr	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	पूर्ण,
	[BOARD_NI_PXI_6503] = अणु
		.name		= "ni_pxi-6503",
		.dio_badr	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	पूर्ण,
पूर्ण;

/* ripped from mite.h and mite_setup2() to aव्योम mite dependency */
#घोषणा MITE_IODWBSR	0xc0	/* IO Device Winकरोw Base Size Register */
#घोषणा WENAB		BIT(7)	/* winकरोw enable */

अटल पूर्णांक pci_8255_mite_init(काष्ठा pci_dev *pcidev)
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

अटल पूर्णांक pci_8255_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा pci_8255_boardinfo *board = शून्य;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (context < ARRAY_SIZE(pci_8255_boards))
		board = &pci_8255_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	अगर (board->has_mite) अणु
		ret = pci_8255_mite_init(pcidev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((pci_resource_flags(pcidev, board->dio_badr) & IORESOURCE_MEM)) अणु
		dev->mmio = pci_ioremap_bar(pcidev, board->dio_badr);
		अगर (!dev->mmio)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		dev->iobase = pci_resource_start(pcidev, board->dio_badr);
	पूर्ण

	/*
	 * One, two, or four subdevices are setup by this driver depending
	 * on the number of channels provided by the board. Each subdevice
	 * has 24 channels supported by the 8255 module.
	 */
	ret = comedi_alloc_subdevices(dev, board->n_8255);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < board->n_8255; i++) अणु
		s = &dev->subdevices[i];
		अगर (dev->mmio)
			ret = subdev_8255_mm_init(dev, s, शून्य, i * I8255_SIZE);
		अन्यथा
			ret = subdev_8255_init(dev, s, शून्य, i * I8255_SIZE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pci_8255_driver = अणु
	.driver_name	= "8255_pci",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci_8255_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक pci_8255_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &pci_8255_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pci_8255_pci_table[] = अणु
	अणु PCI_VDEVICE(ADLINK, 0x7224), BOARD_ADLINK_PCI7224 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7248), BOARD_ADLINK_PCI7248 पूर्ण,
	अणु PCI_VDEVICE(ADLINK, 0x7296), BOARD_ADLINK_PCI7296 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0028), BOARD_CB_PCIDIO24 पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0014), BOARD_CB_PCIDIO24H पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CB, 0x000b, 0x0000, 0x0000),
	  .driver_data = BOARD_CB_PCIDIO48H_OLD पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CB, 0x000b, PCI_VENDOR_ID_CB, 0x000b),
	  .driver_data = BOARD_CB_PCIDIO48H_NEW पूर्ण,
	अणु PCI_VDEVICE(CB, 0x0017), BOARD_CB_PCIDIO96H पूर्ण,
	अणु PCI_VDEVICE(NI, 0x0160), BOARD_NI_PCIDIO96 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1630), BOARD_NI_PCIDIO96B पूर्ण,
	अणु PCI_VDEVICE(NI, 0x13c0), BOARD_NI_PXI6508 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x0400), BOARD_NI_PCI6503 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1250), BOARD_NI_PCI6503B पूर्ण,
	अणु PCI_VDEVICE(NI, 0x17d0), BOARD_NI_PCI6503X पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1800), BOARD_NI_PXI_6503 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_8255_pci_table);

अटल काष्ठा pci_driver pci_8255_pci_driver = अणु
	.name		= "8255_pci",
	.id_table	= pci_8255_pci_table,
	.probe		= pci_8255_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(pci_8255_driver, pci_8255_pci_driver);

MODULE_DESCRIPTION("COMEDI - Generic PCI based 8255 Digital I/O boards");
MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_LICENSE("GPL");
