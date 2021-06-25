<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * resource.c - Contains functions क्रम रेजिस्टरing and analyzing resource inक्रमmation
 *
 * based on isapnp.c resource management (c) Jaroslav Kysela <perex@perex.cz>
 * Copyright 2003 Adam Belay <ambx1@neo.rr.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>

#समावेश <linux/pnp.h>
#समावेश "base.h"

अटल पूर्णांक pnp_reserve_irq[16] = अणु[0 ... 15] = -1 पूर्ण;	/* reserve (करोn't use) some IRQ */
अटल पूर्णांक pnp_reserve_dma[8] = अणु[0 ... 7] = -1 पूर्ण;	/* reserve (करोn't use) some DMA */
अटल पूर्णांक pnp_reserve_io[16] = अणु[0 ... 15] = -1 पूर्ण;	/* reserve (करोn't use) some I/O region */
अटल पूर्णांक pnp_reserve_mem[16] = अणु[0 ... 15] = -1 पूर्ण;	/* reserve (करोn't use) some memory region */

/*
 * option registration
 */

अटल काष्ठा pnp_option *pnp_build_option(काष्ठा pnp_dev *dev, अचिन्हित दीर्घ type,
				    अचिन्हित पूर्णांक option_flags)
अणु
	काष्ठा pnp_option *option;

	option = kzalloc(माप(काष्ठा pnp_option), GFP_KERNEL);
	अगर (!option)
		वापस शून्य;

	option->flags = option_flags;
	option->type = type;

	list_add_tail(&option->list, &dev->options);
	वापस option;
पूर्ण

पूर्णांक pnp_रेजिस्टर_irq_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      pnp_irq_mask_t *map, अचिन्हित अक्षर flags)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_irq *irq;

	option = pnp_build_option(dev, IORESOURCE_IRQ, option_flags);
	अगर (!option)
		वापस -ENOMEM;

	irq = &option->u.irq;
	irq->map = *map;
	irq->flags = flags;

#अगर_घोषित CONFIG_PCI
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < 16; i++)
			अगर (test_bit(i, irq->map.bits))
				pcibios_penalize_isa_irq(i, 0);
	पूर्ण
#पूर्ण_अगर

	dbg_pnp_show_option(dev, option);
	वापस 0;
पूर्ण

पूर्णांक pnp_रेजिस्टर_dma_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      अचिन्हित अक्षर map, अचिन्हित अक्षर flags)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_dma *dma;

	option = pnp_build_option(dev, IORESOURCE_DMA, option_flags);
	अगर (!option)
		वापस -ENOMEM;

	dma = &option->u.dma;
	dma->map = map;
	dma->flags = flags;

	dbg_pnp_show_option(dev, option);
	वापस 0;
पूर्ण

पूर्णांक pnp_रेजिस्टर_port_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			       resource_माप_प्रकार min, resource_माप_प्रकार max,
			       resource_माप_प्रकार align, resource_माप_प्रकार size,
			       अचिन्हित अक्षर flags)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_port *port;

	option = pnp_build_option(dev, IORESOURCE_IO, option_flags);
	अगर (!option)
		वापस -ENOMEM;

	port = &option->u.port;
	port->min = min;
	port->max = max;
	port->align = align;
	port->size = size;
	port->flags = flags;

	dbg_pnp_show_option(dev, option);
	वापस 0;
पूर्ण

पूर्णांक pnp_रेजिस्टर_mem_resource(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक option_flags,
			      resource_माप_प्रकार min, resource_माप_प्रकार max,
			      resource_माप_प्रकार align, resource_माप_प्रकार size,
			      अचिन्हित अक्षर flags)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_mem *mem;

	option = pnp_build_option(dev, IORESOURCE_MEM, option_flags);
	अगर (!option)
		वापस -ENOMEM;

	mem = &option->u.mem;
	mem->min = min;
	mem->max = max;
	mem->align = align;
	mem->size = size;
	mem->flags = flags;

	dbg_pnp_show_option(dev, option);
	वापस 0;
पूर्ण

व्योम pnp_मुक्त_options(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_option *option, *पंचांगp;

	list_क्रम_each_entry_safe(option, पंचांगp, &dev->options, list) अणु
		list_del(&option->list);
		kमुक्त(option);
	पूर्ण
पूर्ण

/*
 * resource validity checking
 */

#घोषणा length(start, end) (*(end) - *(start) + 1)

/* Two ranges conflict अगर one करोesn't end beक्रमe the other starts */
#घोषणा ranged_conflict(starta, enda, startb, endb) \
	!((*(enda) < *(startb)) || (*(endb) < *(starta)))

#घोषणा cannot_compare(flags) \
((flags) & IORESOURCE_DISABLED)

पूर्णांक pnp_check_port(काष्ठा pnp_dev *dev, काष्ठा resource *res)
अणु
	पूर्णांक i;
	काष्ठा pnp_dev *tdev;
	काष्ठा resource *tres;
	resource_माप_प्रकार *port, *end, *tport, *tend;

	port = &res->start;
	end = &res->end;

	/* अगर the resource करोesn't exist, don't complain about it */
	अगर (cannot_compare(res->flags))
		वापस 1;

	/* check अगर the resource is alपढ़ोy in use, skip अगर the
	 * device is active because it itself may be in use */
	अगर (!dev->active) अणु
		अगर (!request_region(*port, length(port, end), "pnp"))
			वापस 0;
		release_region(*port, length(port, end));
	पूर्ण

	/* check अगर the resource is reserved */
	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक rport = pnp_reserve_io[i << 1];
		पूर्णांक rend = pnp_reserve_io[(i << 1) + 1] + rport - 1;
		अगर (ranged_conflict(port, end, &rport, &rend))
			वापस 0;
	पूर्ण

	/* check क्रम पूर्णांकernal conflicts */
	क्रम (i = 0; (tres = pnp_get_resource(dev, IORESOURCE_IO, i)); i++) अणु
		अगर (tres != res && tres->flags & IORESOURCE_IO) अणु
			tport = &tres->start;
			tend = &tres->end;
			अगर (ranged_conflict(port, end, tport, tend))
				वापस 0;
		पूर्ण
	पूर्ण

	/* check क्रम conflicts with other pnp devices */
	pnp_क्रम_each_dev(tdev) अणु
		अगर (tdev == dev)
			जारी;
		क्रम (i = 0;
		     (tres = pnp_get_resource(tdev, IORESOURCE_IO, i));
		     i++) अणु
			अगर (tres->flags & IORESOURCE_IO) अणु
				अगर (cannot_compare(tres->flags))
					जारी;
				अगर (tres->flags & IORESOURCE_WINDOW)
					जारी;
				tport = &tres->start;
				tend = &tres->end;
				अगर (ranged_conflict(port, end, tport, tend))
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक pnp_check_mem(काष्ठा pnp_dev *dev, काष्ठा resource *res)
अणु
	पूर्णांक i;
	काष्ठा pnp_dev *tdev;
	काष्ठा resource *tres;
	resource_माप_प्रकार *addr, *end, *taddr, *tend;

	addr = &res->start;
	end = &res->end;

	/* अगर the resource करोesn't exist, don't complain about it */
	अगर (cannot_compare(res->flags))
		वापस 1;

	/* check अगर the resource is alपढ़ोy in use, skip अगर the
	 * device is active because it itself may be in use */
	अगर (!dev->active) अणु
		अगर (!request_mem_region(*addr, length(addr, end), "pnp"))
			वापस 0;
		release_mem_region(*addr, length(addr, end));
	पूर्ण

	/* check अगर the resource is reserved */
	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक raddr = pnp_reserve_mem[i << 1];
		पूर्णांक rend = pnp_reserve_mem[(i << 1) + 1] + raddr - 1;
		अगर (ranged_conflict(addr, end, &raddr, &rend))
			वापस 0;
	पूर्ण

	/* check क्रम पूर्णांकernal conflicts */
	क्रम (i = 0; (tres = pnp_get_resource(dev, IORESOURCE_MEM, i)); i++) अणु
		अगर (tres != res && tres->flags & IORESOURCE_MEM) अणु
			taddr = &tres->start;
			tend = &tres->end;
			अगर (ranged_conflict(addr, end, taddr, tend))
				वापस 0;
		पूर्ण
	पूर्ण

	/* check क्रम conflicts with other pnp devices */
	pnp_क्रम_each_dev(tdev) अणु
		अगर (tdev == dev)
			जारी;
		क्रम (i = 0;
		     (tres = pnp_get_resource(tdev, IORESOURCE_MEM, i));
		     i++) अणु
			अगर (tres->flags & IORESOURCE_MEM) अणु
				अगर (cannot_compare(tres->flags))
					जारी;
				अगर (tres->flags & IORESOURCE_WINDOW)
					जारी;
				taddr = &tres->start;
				tend = &tres->end;
				अगर (ranged_conflict(addr, end, taddr, tend))
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल irqवापस_t pnp_test_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक pci_dev_uses_irq(काष्ठा pnp_dev *pnp, काष्ठा pci_dev *pci,
			    अचिन्हित पूर्णांक irq)
अणु
	u32 class;
	u8 progअगर;

	अगर (pci->irq == irq) अणु
		pnp_dbg(&pnp->dev, "  device %s using irq %d\n",
			pci_name(pci), irq);
		वापस 1;
	पूर्ण

	/*
	 * See pci_setup_device() and ata_pci_sff_activate_host() क्रम
	 * similar IDE legacy detection.
	 */
	pci_पढ़ो_config_dword(pci, PCI_CLASS_REVISION, &class);
	class >>= 8;		/* discard revision ID */
	progअगर = class & 0xff;
	class >>= 8;

	अगर (class == PCI_CLASS_STORAGE_IDE) अणु
		/*
		 * Unless both channels are native-PCI mode only,
		 * treat the compatibility IRQs as busy.
		 */
		अगर ((progअगर & 0x5) != 0x5)
			अगर (pci_get_legacy_ide_irq(pci, 0) == irq ||
			    pci_get_legacy_ide_irq(pci, 1) == irq) अणु
				pnp_dbg(&pnp->dev, "  legacy IDE device %s "
					"using irq %d\n", pci_name(pci), irq);
				वापस 1;
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pci_uses_irq(काष्ठा pnp_dev *pnp, अचिन्हित पूर्णांक irq)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा pci_dev *pci = शून्य;

	क्रम_each_pci_dev(pci) अणु
		अगर (pci_dev_uses_irq(pnp, pci, irq)) अणु
			pci_dev_put(pci);
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक pnp_check_irq(काष्ठा pnp_dev *dev, काष्ठा resource *res)
अणु
	पूर्णांक i;
	काष्ठा pnp_dev *tdev;
	काष्ठा resource *tres;
	resource_माप_प्रकार *irq;

	irq = &res->start;

	/* अगर the resource करोesn't exist, don't complain about it */
	अगर (cannot_compare(res->flags))
		वापस 1;

	/* check अगर the resource is valid */
	अगर (*irq > 15)
		वापस 0;

	/* check अगर the resource is reserved */
	क्रम (i = 0; i < 16; i++) अणु
		अगर (pnp_reserve_irq[i] == *irq)
			वापस 0;
	पूर्ण

	/* check क्रम पूर्णांकernal conflicts */
	क्रम (i = 0; (tres = pnp_get_resource(dev, IORESOURCE_IRQ, i)); i++) अणु
		अगर (tres != res && tres->flags & IORESOURCE_IRQ) अणु
			अगर (tres->start == *irq)
				वापस 0;
		पूर्ण
	पूर्ण

	/* check अगर the resource is being used by a pci device */
	अगर (pci_uses_irq(dev, *irq))
		वापस 0;

	/* check अगर the resource is alपढ़ोy in use, skip अगर the
	 * device is active because it itself may be in use */
	अगर (!dev->active) अणु
		अगर (request_irq(*irq, pnp_test_handler,
				IRQF_PROBE_SHARED, "pnp", शून्य))
			वापस 0;
		मुक्त_irq(*irq, शून्य);
	पूर्ण

	/* check क्रम conflicts with other pnp devices */
	pnp_क्रम_each_dev(tdev) अणु
		अगर (tdev == dev)
			जारी;
		क्रम (i = 0;
		     (tres = pnp_get_resource(tdev, IORESOURCE_IRQ, i));
		     i++) अणु
			अगर (tres->flags & IORESOURCE_IRQ) अणु
				अगर (cannot_compare(tres->flags))
					जारी;
				अगर (tres->start == *irq)
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_ISA_DMA_API
पूर्णांक pnp_check_dma(काष्ठा pnp_dev *dev, काष्ठा resource *res)
अणु
	पूर्णांक i;
	काष्ठा pnp_dev *tdev;
	काष्ठा resource *tres;
	resource_माप_प्रकार *dma;

	dma = &res->start;

	/* अगर the resource करोesn't exist, don't complain about it */
	अगर (cannot_compare(res->flags))
		वापस 1;

	/* check अगर the resource is valid */
	अगर (*dma == 4 || *dma > 7)
		वापस 0;

	/* check अगर the resource is reserved */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (pnp_reserve_dma[i] == *dma)
			वापस 0;
	पूर्ण

	/* check क्रम पूर्णांकernal conflicts */
	क्रम (i = 0; (tres = pnp_get_resource(dev, IORESOURCE_DMA, i)); i++) अणु
		अगर (tres != res && tres->flags & IORESOURCE_DMA) अणु
			अगर (tres->start == *dma)
				वापस 0;
		पूर्ण
	पूर्ण

	/* check अगर the resource is alपढ़ोy in use, skip अगर the
	 * device is active because it itself may be in use */
	अगर (!dev->active) अणु
		अगर (request_dma(*dma, "pnp"))
			वापस 0;
		मुक्त_dma(*dma);
	पूर्ण

	/* check क्रम conflicts with other pnp devices */
	pnp_क्रम_each_dev(tdev) अणु
		अगर (tdev == dev)
			जारी;
		क्रम (i = 0;
		     (tres = pnp_get_resource(tdev, IORESOURCE_DMA, i));
		     i++) अणु
			अगर (tres->flags & IORESOURCE_DMA) अणु
				अगर (cannot_compare(tres->flags))
					जारी;
				अगर (tres->start == *dma)
					वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_ISA_DMA_API */

अचिन्हित दीर्घ pnp_resource_type(काष्ठा resource *res)
अणु
	वापस res->flags & (IORESOURCE_IO  | IORESOURCE_MEM |
			     IORESOURCE_IRQ | IORESOURCE_DMA |
			     IORESOURCE_BUS);
पूर्ण

काष्ठा resource *pnp_get_resource(काष्ठा pnp_dev *dev,
				  अचिन्हित दीर्घ type, अचिन्हित पूर्णांक num)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	list_क्रम_each_entry(pnp_res, &dev->resources, list) अणु
		res = &pnp_res->res;
		अगर (pnp_resource_type(res) == type && num-- == 0)
			वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pnp_get_resource);

अटल काष्ठा pnp_resource *pnp_new_resource(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_resource *pnp_res;

	pnp_res = kzalloc(माप(काष्ठा pnp_resource), GFP_KERNEL);
	अगर (!pnp_res)
		वापस शून्य;

	list_add_tail(&pnp_res->list, &dev->resources);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_resource(काष्ठा pnp_dev *dev,
				      काष्ठा resource *res)
अणु
	काष्ठा pnp_resource *pnp_res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource %pR\n", res);
		वापस शून्य;
	पूर्ण

	pnp_res->res = *res;
	pnp_res->res.name = dev->name;
	dev_dbg(&dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_irq_resource(काष्ठा pnp_dev *dev, पूर्णांक irq,
					  पूर्णांक flags)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource for IRQ %d\n", irq);
		वापस शून्य;
	पूर्ण

	res = &pnp_res->res;
	res->flags = IORESOURCE_IRQ | flags;
	res->start = irq;
	res->end = irq;

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_dma_resource(काष्ठा pnp_dev *dev, पूर्णांक dma,
					  पूर्णांक flags)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource for DMA %d\n", dma);
		वापस शून्य;
	पूर्ण

	res = &pnp_res->res;
	res->flags = IORESOURCE_DMA | flags;
	res->start = dma;
	res->end = dma;

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_io_resource(काष्ठा pnp_dev *dev,
					 resource_माप_प्रकार start,
					 resource_माप_प्रकार end, पूर्णांक flags)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource for IO %#llx-%#llx\n",
			(अचिन्हित दीर्घ दीर्घ) start,
			(अचिन्हित दीर्घ दीर्घ) end);
		वापस शून्य;
	पूर्ण

	res = &pnp_res->res;
	res->flags = IORESOURCE_IO | flags;
	res->start = start;
	res->end = end;

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_mem_resource(काष्ठा pnp_dev *dev,
					  resource_माप_प्रकार start,
					  resource_माप_प्रकार end, पूर्णांक flags)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource for MEM %#llx-%#llx\n",
			(अचिन्हित दीर्घ दीर्घ) start,
			(अचिन्हित दीर्घ दीर्घ) end);
		वापस शून्य;
	पूर्ण

	res = &pnp_res->res;
	res->flags = IORESOURCE_MEM | flags;
	res->start = start;
	res->end = end;

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

काष्ठा pnp_resource *pnp_add_bus_resource(काष्ठा pnp_dev *dev,
					  resource_माप_प्रकार start,
					  resource_माप_प्रकार end)
अणु
	काष्ठा pnp_resource *pnp_res;
	काष्ठा resource *res;

	pnp_res = pnp_new_resource(dev);
	अगर (!pnp_res) अणु
		dev_err(&dev->dev, "can't add resource for BUS %#llx-%#llx\n",
			(अचिन्हित दीर्घ दीर्घ) start,
			(अचिन्हित दीर्घ दीर्घ) end);
		वापस शून्य;
	पूर्ण

	res = &pnp_res->res;
	res->flags = IORESOURCE_BUS;
	res->start = start;
	res->end = end;

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	वापस pnp_res;
पूर्ण

/*
 * Determine whether the specअगरied resource is a possible configuration
 * क्रम this device.
 */
पूर्णांक pnp_possible_config(काष्ठा pnp_dev *dev, पूर्णांक type, resource_माप_प्रकार start,
			resource_माप_प्रकार size)
अणु
	काष्ठा pnp_option *option;
	काष्ठा pnp_port *port;
	काष्ठा pnp_mem *mem;
	काष्ठा pnp_irq *irq;
	काष्ठा pnp_dma *dma;

	list_क्रम_each_entry(option, &dev->options, list) अणु
		अगर (option->type != type)
			जारी;

		चयन (option->type) अणु
		हाल IORESOURCE_IO:
			port = &option->u.port;
			अगर (port->min == start && port->size == size)
				वापस 1;
			अवरोध;
		हाल IORESOURCE_MEM:
			mem = &option->u.mem;
			अगर (mem->min == start && mem->size == size)
				वापस 1;
			अवरोध;
		हाल IORESOURCE_IRQ:
			irq = &option->u.irq;
			अगर (start < PNP_IRQ_NR &&
			    test_bit(start, irq->map.bits))
				वापस 1;
			अवरोध;
		हाल IORESOURCE_DMA:
			dma = &option->u.dma;
			अगर (dma->map & (1 << start))
				वापस 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pnp_possible_config);

पूर्णांक pnp_range_reserved(resource_माप_प्रकार start, resource_माप_प्रकार end)
अणु
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_resource *pnp_res;
	resource_माप_प्रकार *dev_start, *dev_end;

	pnp_क्रम_each_dev(dev) अणु
		list_क्रम_each_entry(pnp_res, &dev->resources, list) अणु
			dev_start = &pnp_res->res.start;
			dev_end   = &pnp_res->res.end;
			अगर (ranged_conflict(&start, &end, dev_start, dev_end))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pnp_range_reserved);

/* क्रमmat is: pnp_reserve_irq=irq1[,irq2] .... */
अटल पूर्णांक __init pnp_setup_reserve_irq(अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		अगर (get_option(&str, &pnp_reserve_irq[i]) != 2)
			अवरोध;
	वापस 1;
पूर्ण

__setup("pnp_reserve_irq=", pnp_setup_reserve_irq);

/* क्रमmat is: pnp_reserve_dma=dma1[,dma2] .... */
अटल पूर्णांक __init pnp_setup_reserve_dma(अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		अगर (get_option(&str, &pnp_reserve_dma[i]) != 2)
			अवरोध;
	वापस 1;
पूर्ण

__setup("pnp_reserve_dma=", pnp_setup_reserve_dma);

/* क्रमmat is: pnp_reserve_io=io1,size1[,io2,size2] .... */
अटल पूर्णांक __init pnp_setup_reserve_io(अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		अगर (get_option(&str, &pnp_reserve_io[i]) != 2)
			अवरोध;
	वापस 1;
पूर्ण

__setup("pnp_reserve_io=", pnp_setup_reserve_io);

/* क्रमmat is: pnp_reserve_mem=mem1,size1[,mem2,size2] .... */
अटल पूर्णांक __init pnp_setup_reserve_mem(अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		अगर (get_option(&str, &pnp_reserve_mem[i]) != 2)
			अवरोध;
	वापस 1;
पूर्ण

__setup("pnp_reserve_mem=", pnp_setup_reserve_mem);
