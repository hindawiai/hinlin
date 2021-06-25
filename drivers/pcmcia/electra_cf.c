<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 PA Semi, Inc
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Based on drivers/pcmcia/omap_cf.c
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/ss.h>

अटल स्थिर अक्षर driver_name[] = "electra-cf";

काष्ठा electra_cf_socket अणु
	काष्ठा pcmcia_socket	socket;

	काष्ठा समयr_list	समयr;
	अचिन्हित		present:1;
	अचिन्हित		active:1;

	काष्ठा platक्रमm_device	*ofdev;
	अचिन्हित दीर्घ		mem_phys;
	व्योम __iomem		*mem_base;
	अचिन्हित दीर्घ		mem_size;
	व्योम __iomem		*io_virt;
	अचिन्हित पूर्णांक		io_base;
	अचिन्हित पूर्णांक		io_size;
	u_पूर्णांक			irq;
	काष्ठा resource		iomem;
	व्योम __iomem		*gpio_base;
	पूर्णांक			gpio_detect;
	पूर्णांक			gpio_vsense;
	पूर्णांक			gpio_3v;
	पूर्णांक			gpio_5v;
पूर्ण;

#घोषणा	POLL_INTERVAL		(2 * HZ)


अटल पूर्णांक electra_cf_present(काष्ठा electra_cf_socket *cf)
अणु
	अचिन्हित पूर्णांक gpio;

	gpio = in_le32(cf->gpio_base+0x40);
	वापस !(gpio & (1 << cf->gpio_detect));
पूर्ण

अटल पूर्णांक electra_cf_ss_init(काष्ठा pcmcia_socket *s)
अणु
	वापस 0;
पूर्ण

/* the समयr is primarily to kick this socket's pccardd */
अटल व्योम electra_cf_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा electra_cf_socket *cf = from_समयr(cf, t, समयr);
	पूर्णांक present = electra_cf_present(cf);

	अगर (present != cf->present) अणु
		cf->present = present;
		pcmcia_parse_events(&cf->socket, SS_DETECT);
	पूर्ण

	अगर (cf->active)
		mod_समयr(&cf->समयr, jअगरfies + POLL_INTERVAL);
पूर्ण

अटल irqवापस_t electra_cf_irq(पूर्णांक irq, व्योम *_cf)
अणु
	काष्ठा electra_cf_socket *cf = _cf;

	electra_cf_समयr(&cf->समयr);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक electra_cf_get_status(काष्ठा pcmcia_socket *s, u_पूर्णांक *sp)
अणु
	काष्ठा electra_cf_socket *cf;

	अगर (!sp)
		वापस -EINVAL;

	cf = container_of(s, काष्ठा electra_cf_socket, socket);

	/* NOTE CF is always 3VCARD */
	अगर (electra_cf_present(cf)) अणु
		*sp = SS_READY | SS_DETECT | SS_POWERON | SS_3VCARD;

		s->pci_irq = cf->irq;
	पूर्ण अन्यथा
		*sp = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक electra_cf_set_socket(काष्ठा pcmcia_socket *sock,
				 काष्ठा socket_state_t *s)
अणु
	अचिन्हित पूर्णांक gpio;
	अचिन्हित पूर्णांक vcc;
	काष्ठा electra_cf_socket *cf;

	cf = container_of(sock, काष्ठा electra_cf_socket, socket);

	/* "reset" means no घातer in our हाल */
	vcc = (s->flags & SS_RESET) ? 0 : s->Vcc;

	चयन (vcc) अणु
	हाल 0:
		gpio = 0;
		अवरोध;
	हाल 33:
		gpio = (1 << cf->gpio_3v);
		अवरोध;
	हाल 5:
		gpio = (1 << cf->gpio_5v);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	gpio |= 1 << (cf->gpio_3v + 16); /* enwr */
	gpio |= 1 << (cf->gpio_5v + 16); /* enwr */
	out_le32(cf->gpio_base+0x90, gpio);

	pr_debug("%s: Vcc %d, io_irq %d, flags %04x csc %04x\n",
		driver_name, s->Vcc, s->io_irq, s->flags, s->csc_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक electra_cf_set_io_map(काष्ठा pcmcia_socket *s,
				 काष्ठा pccard_io_map *io)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक electra_cf_set_mem_map(काष्ठा pcmcia_socket *s,
				  काष्ठा pccard_mem_map *map)
अणु
	काष्ठा electra_cf_socket *cf;

	अगर (map->card_start)
		वापस -EINVAL;
	cf = container_of(s, काष्ठा electra_cf_socket, socket);
	map->अटल_start = cf->mem_phys;
	map->flags &= MAP_ACTIVE|MAP_ATTRIB;
	अगर (!(map->flags & MAP_ATTRIB))
		map->अटल_start += 0x800;
	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations electra_cf_ops = अणु
	.init			= electra_cf_ss_init,
	.get_status		= electra_cf_get_status,
	.set_socket		= electra_cf_set_socket,
	.set_io_map		= electra_cf_set_io_map,
	.set_mem_map		= electra_cf_set_mem_map,
पूर्ण;

अटल पूर्णांक electra_cf_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *device = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा electra_cf_socket   *cf;
	काष्ठा resource mem, io;
	पूर्णांक status = -ENOMEM;
	स्थिर अचिन्हित पूर्णांक *prop;
	पूर्णांक err;

	err = of_address_to_resource(np, 0, &mem);
	अगर (err)
		वापस -EINVAL;

	err = of_address_to_resource(np, 1, &io);
	अगर (err)
		वापस -EINVAL;

	cf = kzalloc(माप(*cf), GFP_KERNEL);
	अगर (!cf)
		वापस -ENOMEM;

	समयr_setup(&cf->समयr, electra_cf_समयr, 0);
	cf->irq = 0;

	cf->ofdev = ofdev;
	cf->mem_phys = mem.start;
	cf->mem_size = PAGE_ALIGN(resource_size(&mem));
	cf->mem_base = ioremap(cf->mem_phys, cf->mem_size);
	अगर (!cf->mem_base)
		जाओ out_मुक्त_cf;
	cf->io_size = PAGE_ALIGN(resource_size(&io));
	cf->io_virt = ioremap_phb(io.start, cf->io_size);
	अगर (!cf->io_virt)
		जाओ out_unmap_mem;

	cf->gpio_base = ioremap(0xfc103000, 0x1000);
	अगर (!cf->gpio_base)
		जाओ out_unmap_virt;
	dev_set_drvdata(device, cf);

	cf->io_base = (अचिन्हित दीर्घ)cf->io_virt - VMALLOC_END;
	cf->iomem.start = (अचिन्हित दीर्घ)cf->mem_base;
	cf->iomem.end = (अचिन्हित दीर्घ)cf->mem_base + (mem.end - mem.start);
	cf->iomem.flags = IORESOURCE_MEM;

	cf->irq = irq_of_parse_and_map(np, 0);

	status = request_irq(cf->irq, electra_cf_irq, IRQF_SHARED,
			     driver_name, cf);
	अगर (status < 0) अणु
		dev_err(device, "request_irq failed\n");
		जाओ fail1;
	पूर्ण

	cf->socket.pci_irq = cf->irq;

	status = -EINVAL;

	prop = of_get_property(np, "card-detect-gpio", शून्य);
	अगर (!prop)
		जाओ fail1;
	cf->gpio_detect = *prop;

	prop = of_get_property(np, "card-vsense-gpio", शून्य);
	अगर (!prop)
		जाओ fail1;
	cf->gpio_vsense = *prop;

	prop = of_get_property(np, "card-3v-gpio", शून्य);
	अगर (!prop)
		जाओ fail1;
	cf->gpio_3v = *prop;

	prop = of_get_property(np, "card-5v-gpio", शून्य);
	अगर (!prop)
		जाओ fail1;
	cf->gpio_5v = *prop;

	cf->socket.io_offset = cf->io_base;

	/* reserve chip-select regions */
	अगर (!request_mem_region(cf->mem_phys, cf->mem_size, driver_name)) अणु
		status = -ENXIO;
		dev_err(device, "Can't claim memory region\n");
		जाओ fail1;
	पूर्ण

	अगर (!request_region(cf->io_base, cf->io_size, driver_name)) अणु
		status = -ENXIO;
		dev_err(device, "Can't claim I/O region\n");
		जाओ fail2;
	पूर्ण

	cf->socket.owner = THIS_MODULE;
	cf->socket.dev.parent = &ofdev->dev;
	cf->socket.ops = &electra_cf_ops;
	cf->socket.resource_ops = &pccard_अटल_ops;
	cf->socket.features = SS_CAP_PCCARD | SS_CAP_STATIC_MAP |
				SS_CAP_MEM_ALIGN;
	cf->socket.map_size = 0x800;

	status = pcmcia_रेजिस्टर_socket(&cf->socket);
	अगर (status < 0) अणु
		dev_err(device, "pcmcia_register_socket failed\n");
		जाओ fail3;
	पूर्ण

	dev_info(device, "at mem 0x%lx io 0x%llx irq %d\n",
		 cf->mem_phys, io.start, cf->irq);

	cf->active = 1;
	electra_cf_समयr(&cf->समयr);
	वापस 0;

fail3:
	release_region(cf->io_base, cf->io_size);
fail2:
	release_mem_region(cf->mem_phys, cf->mem_size);
fail1:
	अगर (cf->irq)
		मुक्त_irq(cf->irq, cf);

	iounmap(cf->gpio_base);
out_unmap_virt:
	device_init_wakeup(&ofdev->dev, 0);
	iounmap(cf->io_virt);
out_unmap_mem:
	iounmap(cf->mem_base);
out_मुक्त_cf:
	kमुक्त(cf);
	वापस status;

पूर्ण

अटल पूर्णांक electra_cf_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *device = &ofdev->dev;
	काष्ठा electra_cf_socket *cf;

	cf = dev_get_drvdata(device);

	cf->active = 0;
	pcmcia_unरेजिस्टर_socket(&cf->socket);
	मुक्त_irq(cf->irq, cf);
	del_समयr_sync(&cf->समयr);

	iounmap(cf->io_virt);
	iounmap(cf->mem_base);
	iounmap(cf->gpio_base);
	release_mem_region(cf->mem_phys, cf->mem_size);
	release_region(cf->io_base, cf->io_size);

	kमुक्त(cf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id electra_cf_match[] = अणु
	अणु
		.compatible   = "electra-cf",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, electra_cf_match);

अटल काष्ठा platक्रमm_driver electra_cf_driver = अणु
	.driver = अणु
		.name = driver_name,
		.of_match_table = electra_cf_match,
	पूर्ण,
	.probe	  = electra_cf_probe,
	.हटाओ   = electra_cf_हटाओ,
पूर्ण;

module_platक्रमm_driver(electra_cf_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Olof Johansson <olof@lixom.net>");
MODULE_DESCRIPTION("PA Semi Electra CF driver");
