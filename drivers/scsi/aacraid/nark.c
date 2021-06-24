<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Adaptec AAC series RAID controller driver
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  nark.c
 *
 * Abstract: Hardware Device Interface क्रम NEMER/ARK
 */

#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>

#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

/**
 *	aac_nark_ioremap
 *	@dev: device to ioremap
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_nark_ioremap(काष्ठा aac_dev * dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.rx);
		dev->regs.rx = शून्य;
		iounmap(dev->base);
		dev->base = शून्य;
		वापस 0;
	पूर्ण
	dev->base_start = pci_resource_start(dev->pdev, 2);
	dev->regs.rx = ioremap((u64)pci_resource_start(dev->pdev, 0) |
	  ((u64)pci_resource_start(dev->pdev, 1) << 32),
	  माप(काष्ठा rx_रेजिस्टरs) - माप(काष्ठा rx_inbound));
	dev->base = शून्य;
	अगर (dev->regs.rx == शून्य)
		वापस -1;
	dev->base = ioremap(dev->base_start, size);
	अगर (dev->base == शून्य) अणु
		iounmap(dev->regs.rx);
		dev->regs.rx = शून्य;
		वापस -1;
	पूर्ण
	dev->IndexRegs = &((काष्ठा rx_रेजिस्टरs __iomem *)dev->base)->IndexRegs;
	वापस 0;
पूर्ण

/**
 *	aac_nark_init	-	initialize an NEMER/ARK Split Bar card
 *	@dev: device to configure
 *
 */

पूर्णांक aac_nark_init(काष्ठा aac_dev * dev)
अणु
	/*
	 *	Fill in the function dispatch table.
	 */
	dev->a_ops.adapter_ioremap = aac_nark_ioremap;
	dev->a_ops.adapter_comm = aac_rx_select_comm;

	वापस _aac_rx_init(dev);
पूर्ण
