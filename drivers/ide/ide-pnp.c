<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file provides स्वतःdetection क्रम ISA PnP IDE पूर्णांकerfaces.
 * It was tested with "ESS ES1868 Plug and Play AudioDrive" IDE पूर्णांकerface.
 *
 * Copyright (C) 2000 Andrey Panin <pazke@करोnpac.ru>
 */

#समावेश <linux/init.h>
#समावेश <linux/pnp.h>
#समावेश <linux/ide.h>
#समावेश <linux/module.h>

#घोषणा DRV_NAME "ide-pnp"

/* Add your devices here :)) */
अटल स्थिर काष्ठा pnp_device_id idepnp_devices[] = अणु
	/* Generic ESDI/IDE/ATA compatible hard disk controller */
	अणु.id = "PNP0600", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ide_pnp_port_info = अणु
	.host_flags		= IDE_HFLAG_NO_DMA,
	.chipset		= ide_generic,
पूर्ण;

अटल पूर्णांक idepnp_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा ide_host *host;
	अचिन्हित दीर्घ base, ctl;
	पूर्णांक rc;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;

	prपूर्णांकk(KERN_INFO DRV_NAME ": generic PnP IDE interface\n");

	अगर (!(pnp_port_valid(dev, 0) && pnp_port_valid(dev, 1) && pnp_irq_valid(dev, 0)))
		वापस -1;

	base = pnp_port_start(dev, 0);
	ctl = pnp_port_start(dev, 1);

	अगर (!request_region(base, 8, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX not free.\n",
				DRV_NAME, base, base + 7);
		वापस -EBUSY;
	पूर्ण

	अगर (!request_region(ctl, 1, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX not free.\n",
				DRV_NAME, ctl);
		release_region(base, 8);
		वापस -EBUSY;
	पूर्ण

	स_रखो(&hw, 0, माप(hw));
	ide_std_init_ports(&hw, base, ctl);
	hw.irq = pnp_irq(dev, 0);

	rc = ide_host_add(&ide_pnp_port_info, hws, 1, &host);
	अगर (rc)
		जाओ out;

	pnp_set_drvdata(dev, host);

	वापस 0;
out:
	release_region(ctl, 1);
	release_region(base, 8);

	वापस rc;
पूर्ण

अटल व्योम idepnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा ide_host *host = pnp_get_drvdata(dev);

	ide_host_हटाओ(host);

	release_region(pnp_port_start(dev, 1), 1);
	release_region(pnp_port_start(dev, 0), 8);
पूर्ण

अटल काष्ठा pnp_driver idepnp_driver = अणु
	.name		= "ide",
	.id_table	= idepnp_devices,
	.probe		= idepnp_probe,
	.हटाओ		= idepnp_हटाओ,
पूर्ण;

module_pnp_driver(idepnp_driver);
MODULE_LICENSE("GPL");
