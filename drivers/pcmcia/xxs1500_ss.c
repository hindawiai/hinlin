<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCMCIA socket code क्रम the MyCable XXS1500 प्रणाली.
 *
 * Copyright (c) 2009 Manuel Lauss <manuel.lauss@gmail.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/resource.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

#घोषणा MEM_MAP_SIZE	0x400000
#घोषणा IO_MAP_SIZE	0x1000


/*
 * 3.3V cards only; all पूर्णांकerfacing is करोne via gpios:
 *
 * 0/1:  carddetect (00 = card present, xx = huh)
 * 4:	 card irq
 * 204:  reset (high-act)
 * 205:  buffer enable (low-act)
 * 208/209: card voltage key (00,01,10,11)
 * 210:  battwarn
 * 211:  batdead
 * 214:  घातer (low-act)
 */
#घोषणा GPIO_CDA	0
#घोषणा GPIO_CDB	1
#घोषणा GPIO_CARसूचीQ	4
#घोषणा GPIO_RESET	204
#घोषणा GPIO_OUTEN	205
#घोषणा GPIO_VSL	208
#घोषणा GPIO_VSH	209
#घोषणा GPIO_BATTDEAD	210
#घोषणा GPIO_BATTWARN	211
#घोषणा GPIO_POWER	214

काष्ठा xxs1500_pcmcia_sock अणु
	काष्ठा pcmcia_socket	socket;
	व्योम		*virt_io;

	phys_addr_t	phys_io;
	phys_addr_t	phys_attr;
	phys_addr_t	phys_mem;

	/* previous flags क्रम set_socket() */
	अचिन्हित पूर्णांक old_flags;
पूर्ण;

#घोषणा to_xxs_socket(x) container_of(x, काष्ठा xxs1500_pcmcia_sock, socket)

अटल irqवापस_t cdirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock = data;

	pcmcia_parse_events(&sock->socket, SS_DETECT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xxs1500_pcmcia_configure(काष्ठा pcmcia_socket *skt,
				    काष्ठा socket_state_t *state)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);
	अचिन्हित पूर्णांक changed;

	/* घातer control */
	चयन (state->Vcc) अणु
	हाल 0:
		gpio_set_value(GPIO_POWER, 1);	/* घातer off */
		अवरोध;
	हाल 33:
		gpio_set_value(GPIO_POWER, 0);	/* घातer on */
		अवरोध;
	हाल 50:
	शेष:
		वापस -EINVAL;
	पूर्ण

	changed = state->flags ^ sock->old_flags;

	अगर (changed & SS_RESET) अणु
		अगर (state->flags & SS_RESET) अणु
			gpio_set_value(GPIO_RESET, 1);	/* निश्चित reset */
			gpio_set_value(GPIO_OUTEN, 1);	/* buffers off */
		पूर्ण अन्यथा अणु
			gpio_set_value(GPIO_RESET, 0);	/* deनिश्चित reset */
			gpio_set_value(GPIO_OUTEN, 0);	/* buffers on */
			msleep(500);
		पूर्ण
	पूर्ण

	sock->old_flags = state->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक xxs1500_pcmcia_get_status(काष्ठा pcmcia_socket *skt,
				     अचिन्हित पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक i;

	status = 0;

	/* check carddetects: GPIO[0:1] must both be low */
	अगर (!gpio_get_value(GPIO_CDA) && !gpio_get_value(GPIO_CDB))
		status |= SS_DETECT;

	/* determine card voltage: GPIO[208:209] binary value */
	i = (!!gpio_get_value(GPIO_VSL)) | ((!!gpio_get_value(GPIO_VSH)) << 1);

	चयन (i) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		status |= SS_3VCARD;	/* 3V card */
		अवरोध;
	हाल 3:				/* 5V card, unsupported */
	शेष:
		status |= SS_XVCARD;	/* treated as unsupported in core */
	पूर्ण

	/* GPIO214: low active घातer चयन */
	status |= gpio_get_value(GPIO_POWER) ? 0 : SS_POWERON;

	/* GPIO204: high-active reset line */
	status |= gpio_get_value(GPIO_RESET) ? SS_RESET : SS_READY;

	/* other stuff */
	status |= gpio_get_value(GPIO_BATTDEAD) ? 0 : SS_BATDEAD;
	status |= gpio_get_value(GPIO_BATTWARN) ? 0 : SS_BATWARN;

	*value = status;

	वापस 0;
पूर्ण

अटल पूर्णांक xxs1500_pcmcia_sock_init(काष्ठा pcmcia_socket *skt)
अणु
	gpio_direction_input(GPIO_CDA);
	gpio_direction_input(GPIO_CDB);
	gpio_direction_input(GPIO_VSL);
	gpio_direction_input(GPIO_VSH);
	gpio_direction_input(GPIO_BATTDEAD);
	gpio_direction_input(GPIO_BATTWARN);
	gpio_direction_output(GPIO_RESET, 1);	/* निश्चित reset */
	gpio_direction_output(GPIO_OUTEN, 1);	/* disable buffers */
	gpio_direction_output(GPIO_POWER, 1);	/* घातer off */

	वापस 0;
पूर्ण

अटल पूर्णांक xxs1500_pcmcia_sock_suspend(काष्ठा pcmcia_socket *skt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक au1x00_pcmcia_set_io_map(काष्ठा pcmcia_socket *skt,
				    काष्ठा pccard_io_map *map)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);

	map->start = (u32)sock->virt_io;
	map->stop = map->start + IO_MAP_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक au1x00_pcmcia_set_mem_map(काष्ठा pcmcia_socket *skt,
				     काष्ठा pccard_mem_map *map)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);

	अगर (map->flags & MAP_ATTRIB)
		map->अटल_start = sock->phys_attr + map->card_start;
	अन्यथा
		map->अटल_start = sock->phys_mem + map->card_start;

	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations xxs1500_pcmcia_operations = अणु
	.init			= xxs1500_pcmcia_sock_init,
	.suspend		= xxs1500_pcmcia_sock_suspend,
	.get_status		= xxs1500_pcmcia_get_status,
	.set_socket		= xxs1500_pcmcia_configure,
	.set_io_map		= au1x00_pcmcia_set_io_map,
	.set_mem_map		= au1x00_pcmcia_set_mem_map,
पूर्ण;

अटल पूर्णांक xxs1500_pcmcia_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock;
	काष्ठा resource *r;
	पूर्णांक ret, irq;

	sock = kzalloc(माप(काष्ठा xxs1500_pcmcia_sock), GFP_KERNEL);
	अगर (!sock)
		वापस -ENOMEM;

	ret = -ENODEV;

	/* 36bit PCMCIA Attribute area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-attr");
	अगर (!r) अणु
		dev_err(&pdev->dev, "missing 'pcmcia-attr' resource!\n");
		जाओ out0;
	पूर्ण
	sock->phys_attr = r->start;

	/* 36bit PCMCIA Memory area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-mem");
	अगर (!r) अणु
		dev_err(&pdev->dev, "missing 'pcmcia-mem' resource!\n");
		जाओ out0;
	पूर्ण
	sock->phys_mem = r->start;

	/* 36bit PCMCIA IO area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-io");
	अगर (!r) अणु
		dev_err(&pdev->dev, "missing 'pcmcia-io' resource!\n");
		जाओ out0;
	पूर्ण
	sock->phys_io = r->start;


	/*
	 * PCMCIA client drivers use the inb/outb macros to access
	 * the IO रेजिस्टरs.  Since mips_io_port_base is added
	 * to the access address of the mips implementation of
	 * inb/outb, we need to subtract it here because we want
	 * to access the I/O or MEM address directly, without
	 * going through this "mips_io_port_base" mechanism.
	 */
	sock->virt_io = (व्योम *)(ioremap(sock->phys_io, IO_MAP_SIZE) -
				 mips_io_port_base);

	अगर (!sock->virt_io) अणु
		dev_err(&pdev->dev, "cannot remap IO area\n");
		ret = -ENOMEM;
		जाओ out0;
	पूर्ण

	sock->socket.ops	= &xxs1500_pcmcia_operations;
	sock->socket.owner	= THIS_MODULE;
	sock->socket.pci_irq	= gpio_to_irq(GPIO_CARसूचीQ);
	sock->socket.features	= SS_CAP_STATIC_MAP | SS_CAP_PCCARD;
	sock->socket.map_size	= MEM_MAP_SIZE;
	sock->socket.io_offset	= (अचिन्हित दीर्घ)sock->virt_io;
	sock->socket.dev.parent	= &pdev->dev;
	sock->socket.resource_ops = &pccard_अटल_ops;

	platक्रमm_set_drvdata(pdev, sock);

	/* setup carddetect irq: use one of the 2 GPIOs as an
	 * edge detector.
	 */
	irq = gpio_to_irq(GPIO_CDA);
	irq_set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
	ret = request_irq(irq, cdirq, 0, "pcmcia_carddetect", sock);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot setup cd irq\n");
		जाओ out1;
	पूर्ण

	ret = pcmcia_रेजिस्टर_socket(&sock->socket);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register\n");
		जाओ out2;
	पूर्ण

	prपूर्णांकk(KERN_INFO "MyCable XXS1500 PCMCIA socket services\n");

	वापस 0;

out2:
	मुक्त_irq(gpio_to_irq(GPIO_CDA), sock);
out1:
	iounmap((व्योम *)(sock->virt_io + (u32)mips_io_port_base));
out0:
	kमुक्त(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक xxs1500_pcmcia_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xxs1500_pcmcia_sock *sock = platक्रमm_get_drvdata(pdev);

	pcmcia_unरेजिस्टर_socket(&sock->socket);
	मुक्त_irq(gpio_to_irq(GPIO_CDA), sock);
	iounmap((व्योम *)(sock->virt_io + (u32)mips_io_port_base));
	kमुक्त(sock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xxs1500_pcmcia_socket_driver = अणु
	.driver	= अणु
		.name	= "xxs1500_pcmcia",
	पूर्ण,
	.probe		= xxs1500_pcmcia_probe,
	.हटाओ		= xxs1500_pcmcia_हटाओ,
पूर्ण;

module_platक्रमm_driver(xxs1500_pcmcia_socket_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCMCIA Socket Services for MyCable XXS1500 systems");
MODULE_AUTHOR("Manuel Lauss");
