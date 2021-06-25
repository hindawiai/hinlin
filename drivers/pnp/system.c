<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * प्रणाली.c - a driver क्रम reserving pnp प्रणाली resources
 *
 * Some code is based on pnpbios_core.c
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 * (c) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/pnp.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>

अटल स्थिर काष्ठा pnp_device_id pnp_dev_table[] = अणु
	/* General ID क्रम reserving resources */
	अणु"PNP0c02", 0पूर्ण,
	/* memory controller */
	अणु"PNP0c01", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;

अटल व्योम reserve_range(काष्ठा pnp_dev *dev, काष्ठा resource *r, पूर्णांक port)
अणु
	अक्षर *regionid;
	स्थिर अक्षर *pnpid = dev_name(&dev->dev);
	resource_माप_प्रकार start = r->start, end = r->end;
	काष्ठा resource *res;

	regionid = kदो_स्मृति(16, GFP_KERNEL);
	अगर (!regionid)
		वापस;

	snम_लिखो(regionid, 16, "pnp %s", pnpid);
	अगर (port)
		res = request_region(start, end - start + 1, regionid);
	अन्यथा
		res = request_mem_region(start, end - start + 1, regionid);
	अगर (res)
		res->flags &= ~IORESOURCE_BUSY;
	अन्यथा
		kमुक्त(regionid);

	/*
	 * Failures at this poपूर्णांक are usually harmless. pci quirks क्रम
	 * example करो reserve stuff they know about too, so we may well
	 * have द्विगुन reservations.
	 */
	dev_info(&dev->dev, "%pR %s reserved\n", r,
		 res ? "has been" : "could not be");
पूर्ण

अटल व्योम reserve_resources_of_dev(काष्ठा pnp_dev *dev)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	क्रम (i = 0; (res = pnp_get_resource(dev, IORESOURCE_IO, i)); i++) अणु
		अगर (res->flags & IORESOURCE_DISABLED)
			जारी;
		अगर (res->start == 0)
			जारी;	/* disabled */
		अगर (res->start < 0x100)
			/*
			 * Below 0x100 is only standard PC hardware
			 * (pics, kbd, समयr, dma, ...)
			 * We should not get resource conflicts there,
			 * and the kernel reserves these anyway
			 * (see arch/i386/kernel/setup.c).
			 * So, करो nothing
			 */
			जारी;
		अगर (res->end < res->start)
			जारी;	/* invalid */

		reserve_range(dev, res, 1);
	पूर्ण

	क्रम (i = 0; (res = pnp_get_resource(dev, IORESOURCE_MEM, i)); i++) अणु
		अगर (res->flags & IORESOURCE_DISABLED)
			जारी;

		reserve_range(dev, res, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक प्रणाली_pnp_probe(काष्ठा pnp_dev *dev,
			    स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	reserve_resources_of_dev(dev);
	वापस 0;
पूर्ण

अटल काष्ठा pnp_driver प्रणाली_pnp_driver = अणु
	.name     = "system",
	.id_table = pnp_dev_table,
	.flags    = PNP_DRIVER_RES_DO_NOT_CHANGE,
	.probe    = प्रणाली_pnp_probe,
पूर्ण;

अटल पूर्णांक __init pnp_प्रणाली_init(व्योम)
अणु
	वापस pnp_रेजिस्टर_driver(&प्रणाली_pnp_driver);
पूर्ण

/**
 * Reserve motherboard resources after PCI claim BARs,
 * but beक्रमe PCI assign resources क्रम uninitialized PCI devices
 */
fs_initcall(pnp_प्रणाली_init);
