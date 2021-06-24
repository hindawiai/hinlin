<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Intel I82092AA PCI-PCMCIA bridge.
 *
 * (C) 2001 Red Hat, Inc.
 *
 * Author: Arjan Van De Ven <arjanv@redhat.com>
 * Loosly based on i82365.c from the pcmcia-cs package
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>

#समावेश <pcmcia/ss.h>

#समावेश <linux/पन.स>

#समावेश "i82092aa.h"
#समावेश "i82365.h"

MODULE_LICENSE("GPL");

/* PCI core routines */
अटल स्थिर काष्ठा pci_device_id i82092aa_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82092AA_0) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i82092aa_pci_ids);

अटल काष्ठा pci_driver i82092aa_pci_driver = अणु
	.name		= "i82092aa",
	.id_table	= i82092aa_pci_ids,
	.probe		= i82092aa_pci_probe,
	.हटाओ	= i82092aa_pci_हटाओ,
पूर्ण;


/* the pccard काष्ठाure and its functions */
अटल काष्ठा pccard_operations i82092aa_operations = अणु
	.init			= i82092aa_init,
	.get_status		= i82092aa_get_status,
	.set_socket		= i82092aa_set_socket,
	.set_io_map		= i82092aa_set_io_map,
	.set_mem_map		= i82092aa_set_mem_map,
पूर्ण;

/* The card can करो up to 4 sockets, allocate a काष्ठाure क्रम each of them */

काष्ठा socket_info अणु
	पूर्णांक	number;
	पूर्णांक	card_state;
		/* 0 = no socket,
		 * 1 = empty socket,
		 * 2 = card but not initialized,
		 * 3 = operational card
		 */
	अचिन्हित पूर्णांक io_base;	/* base io address of the socket */

	काष्ठा pcmcia_socket socket;
	काष्ठा pci_dev *dev;	/* The PCI device क्रम the socket */
पूर्ण;

#घोषणा MAX_SOCKETS 4
अटल काष्ठा socket_info sockets[MAX_SOCKETS];
अटल पूर्णांक socket_count;	/* लघुcut */


अटल पूर्णांक i82092aa_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित अक्षर configbyte;
	पूर्णांक i, ret;

	ret = pci_enable_device(dev);
	अगर (ret)
		वापस ret;

	/* PCI Configuration Control */
	pci_पढ़ो_config_byte(dev, 0x40, &configbyte);

	चयन (configbyte&6) अणु
	हाल 0:
		socket_count = 2;
		अवरोध;
	हाल 2:
		socket_count = 1;
		अवरोध;
	हाल 4:
	हाल 6:
		socket_count = 4;
		अवरोध;

	शेष:
		dev_err(&dev->dev,
			"Oops, you did something we didn't think of.\n");
		ret = -EIO;
		जाओ err_out_disable;
	पूर्ण
	dev_info(&dev->dev, "configured as a %d socket device.\n",
		 socket_count);

	अगर (!request_region(pci_resource_start(dev, 0), 2, "i82092aa")) अणु
		ret = -EBUSY;
		जाओ err_out_disable;
	पूर्ण

	क्रम (i = 0; i < socket_count; i++) अणु
		sockets[i].card_state = 1; /* 1 = present but empty */
		sockets[i].io_base = pci_resource_start(dev, 0);
		sockets[i].socket.features |= SS_CAP_PCCARD;
		sockets[i].socket.map_size = 0x1000;
		sockets[i].socket.irq_mask = 0;
		sockets[i].socket.pci_irq  = dev->irq;
		sockets[i].socket.cb_dev  = dev;
		sockets[i].socket.owner = THIS_MODULE;

		sockets[i].number = i;

		अगर (card_present(i)) अणु
			sockets[i].card_state = 3;
			dev_dbg(&dev->dev, "slot %i is occupied\n", i);
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->dev, "slot %i is vacant\n", i);
		पूर्ण
	पूर्ण

	/* Now, specअगरiy that all पूर्णांकerrupts are to be करोne as PCI पूर्णांकerrupts
	 * biपंचांगask, one bit per event, 1 = PCI पूर्णांकerrupt, 0 = ISA पूर्णांकerrupt
	 */
	configbyte = 0xFF;

	/* PCI Interrupt Routing Register */
	pci_ग_लिखो_config_byte(dev, 0x50, configbyte);

	/* Register the पूर्णांकerrupt handler */
	dev_dbg(&dev->dev, "Requesting interrupt %i\n", dev->irq);
	ret = request_irq(dev->irq, i82092aa_पूर्णांकerrupt, IRQF_SHARED,
			  "i82092aa", i82092aa_पूर्णांकerrupt);
	अगर (ret) अणु
		dev_err(&dev->dev, "Failed to register IRQ %d, aborting\n",
			dev->irq);
		जाओ err_out_मुक्त_res;
	पूर्ण

	क्रम (i = 0; i < socket_count; i++) अणु
		sockets[i].socket.dev.parent = &dev->dev;
		sockets[i].socket.ops = &i82092aa_operations;
		sockets[i].socket.resource_ops = &pccard_nonअटल_ops;
		ret = pcmcia_रेजिस्टर_socket(&sockets[i].socket);
		अगर (ret)
			जाओ err_out_मुक्त_sockets;
	पूर्ण

	वापस 0;

err_out_मुक्त_sockets:
	अगर (i) अणु
		क्रम (i--; i >= 0; i--)
			pcmcia_unरेजिस्टर_socket(&sockets[i].socket);
	पूर्ण
	मुक्त_irq(dev->irq, i82092aa_पूर्णांकerrupt);
err_out_मुक्त_res:
	release_region(pci_resource_start(dev, 0), 2);
err_out_disable:
	pci_disable_device(dev);
	वापस ret;
पूर्ण

अटल व्योम i82092aa_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	मुक्त_irq(dev->irq, i82092aa_पूर्णांकerrupt);

	क्रम (i = 0; i < socket_count; i++)
		pcmcia_unरेजिस्टर_socket(&sockets[i].socket);
पूर्ण

अटल DEFINE_SPINLOCK(port_lock);

/* basic value पढ़ो/ग_लिखो functions */

अटल अचिन्हित अक्षर indirect_पढ़ो(पूर्णांक socket, अचिन्हित लघु reg)
अणु
	अचिन्हित लघु पूर्णांक port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg += socket * 0x40;
	port = sockets[socket].io_base;
	outb(reg, port);
	val = inb(port+1);
	spin_unlock_irqrestore(&port_lock, flags);
	वापस val;
पूर्ण

अटल व्योम indirect_ग_लिखो(पूर्णांक socket, अचिन्हित लघु reg, अचिन्हित अक्षर value)
अणु
	अचिन्हित लघु पूर्णांक port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket * 0x40;
	port = sockets[socket].io_base;
	outb(reg, port);
	outb(value, port+1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

अटल व्योम indirect_setbit(पूर्णांक socket, अचिन्हित लघु reg, अचिन्हित अक्षर mask)
अणु
	अचिन्हित लघु पूर्णांक port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket * 0x40;
	port = sockets[socket].io_base;
	outb(reg, port);
	val = inb(port+1);
	val |= mask;
	outb(reg, port);
	outb(val, port+1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण


अटल व्योम indirect_resetbit(पूर्णांक socket,
			      अचिन्हित लघु reg, अचिन्हित अक्षर mask)
अणु
	अचिन्हित लघु पूर्णांक port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket * 0x40;
	port = sockets[socket].io_base;
	outb(reg, port);
	val = inb(port+1);
	val &= ~mask;
	outb(reg, port);
	outb(val, port+1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

अटल व्योम indirect_ग_लिखो16(पूर्णांक socket,
			     अचिन्हित लघु reg, अचिन्हित लघु value)
अणु
	अचिन्हित लघु पूर्णांक port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket * 0x40;
	port = sockets[socket].io_base;

	outb(reg, port);
	val = value & 255;
	outb(val, port+1);

	reg++;

	outb(reg, port);
	val = value>>8;
	outb(val, port+1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

/* simple helper functions */
/* External घड़ी समय, in nanoseconds.  120 ns = 8.33 MHz */
अटल पूर्णांक cycle_समय = 120;

अटल पूर्णांक to_cycles(पूर्णांक ns)
अणु
	अगर (cycle_समय != 0)
		वापस ns/cycle_समय;
	अन्यथा
		वापस 0;
पूर्ण


/* Interrupt handler functionality */

अटल irqवापस_t i82092aa_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक i;
	पूर्णांक loopcount = 0;
	पूर्णांक handled = 0;

	अचिन्हित पूर्णांक events, active = 0;

	जबतक (1) अणु
		loopcount++;
		अगर (loopcount > 20) अणु
			pr_err("i82092aa: infinite eventloop in interrupt\n");
			अवरोध;
		पूर्ण

		active = 0;

		क्रम (i = 0; i < socket_count; i++) अणु
			पूर्णांक csc;

			/* Inactive socket, should not happen */
			अगर (sockets[i].card_state == 0)
				जारी;

			/* card status change रेजिस्टर */
			csc = indirect_पढ़ो(i, I365_CSC);

			अगर (csc == 0)  /* no events on this socket */
				जारी;
			handled = 1;
			events = 0;

			अगर (csc & I365_CSC_DETECT) अणु
				events |= SS_DETECT;
				dev_info(&sockets[i].dev->dev,
					 "Card detected in socket %i!\n", i);
			पूर्ण

			अगर (indirect_पढ़ो(i, I365_INTCTL) & I365_PC_IOCARD) अणु
				/* For IO/CARDS, bit 0 means "read the card" */
				अगर (csc & I365_CSC_STSCHG)
					events |= SS_STSCHG;
			पूर्ण अन्यथा अणु
				/* Check क्रम battery/पढ़ोy events */
				अगर (csc & I365_CSC_BVD1)
					events |= SS_BATDEAD;
				अगर (csc & I365_CSC_BVD2)
					events |= SS_BATWARN;
				अगर (csc & I365_CSC_READY)
					events |= SS_READY;
			पूर्ण

			अगर (events)
				pcmcia_parse_events(&sockets[i].socket, events);
			active |= events;
		पूर्ण

		अगर (active == 0) /* no more events to handle */
			अवरोध;
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण



/* socket functions */

अटल पूर्णांक card_present(पूर्णांक socketno)
अणु
	अचिन्हित पूर्णांक val;

	अगर ((socketno < 0) || (socketno >= MAX_SOCKETS))
		वापस 0;
	अगर (sockets[socketno].io_base == 0)
		वापस 0;


	val = indirect_पढ़ो(socketno, 1); /* Interface status रेजिस्टर */
	अगर ((val&12) == 12)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम set_bridge_state(पूर्णांक sock)
अणु
	indirect_ग_लिखो(sock, I365_GBLCTL, 0x00);
	indirect_ग_लिखो(sock, I365_GENCTL, 0x00);

	indirect_setbit(sock, I365_INTCTL, 0x08);
पूर्ण


अटल पूर्णांक i82092aa_init(काष्ठा pcmcia_socket *sock)
अणु
	पूर्णांक i;
	काष्ठा resource res = अणु .start = 0, .end = 0x0fff पूर्ण;
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_mem_map mem = अणु .res = &res, पूर्ण;

	क्रम (i = 0; i < 2; i++) अणु
		io.map = i;
		i82092aa_set_io_map(sock, &io);
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		mem.map = i;
		i82092aa_set_mem_map(sock, &mem);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i82092aa_get_status(काष्ठा pcmcia_socket *socket, u_पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक sock = container_of(socket,
				काष्ठा socket_info, socket)->number;
	अचिन्हित पूर्णांक status;

	/* Interface Status Register */
	status = indirect_पढ़ो(sock, I365_STATUS);

	*value = 0;

	अगर ((status & I365_CS_DETECT) == I365_CS_DETECT)
		*value |= SS_DETECT;

	/* IO cards have a dअगरferent meaning of bits 0,1 */
	/* Also notice the inverse-logic on the bits */
	अगर (indirect_पढ़ो(sock, I365_INTCTL) & I365_PC_IOCARD) अणु
		/* IO card */
		अगर (!(status & I365_CS_STSCHG))
			*value |= SS_STSCHG;
	पूर्ण अन्यथा अणु /* non I/O card */
		अगर (!(status & I365_CS_BVD1))
			*value |= SS_BATDEAD;
		अगर (!(status & I365_CS_BVD2))
			*value |= SS_BATWARN;
	पूर्ण

	अगर (status & I365_CS_WRPROT)
		(*value) |= SS_WRPROT;	/* card is ग_लिखो रक्षित */

	अगर (status & I365_CS_READY)
		(*value) |= SS_READY;    /* card is not busy */

	अगर (status & I365_CS_POWERON)
		(*value) |= SS_POWERON;  /* घातer is applied to the card */

	वापस 0;
पूर्ण


अटल पूर्णांक i82092aa_set_socket(काष्ठा pcmcia_socket *socket,
			       socket_state_t *state)
अणु
	काष्ठा socket_info *sock_info = container_of(socket, काष्ठा socket_info,
						     socket);
	अचिन्हित पूर्णांक sock = sock_info->number;
	अचिन्हित अक्षर reg;

	/* First, set the global controller options */

	set_bridge_state(sock);

	/* Values क्रम the IGENC रेजिस्टर */

	reg = 0;

	/* The reset bit has "inverse" logic */
	अगर (!(state->flags & SS_RESET))
		reg = reg | I365_PC_RESET;
	अगर (state->flags & SS_IOCARD)
		reg = reg | I365_PC_IOCARD;

	/* IGENC, Interrupt and General Control Register */
	indirect_ग_लिखो(sock, I365_INTCTL, reg);

	/* Power रेजिस्टरs */

	reg = I365_PWR_NORESET; /* शेष: disable resetdrv on resume */

	अगर (state->flags & SS_PWR_AUTO) अणु
		dev_info(&sock_info->dev->dev, "Auto power\n");
		reg |= I365_PWR_AUTO;	/* स्वतःmatic घातer mngmnt */
	पूर्ण
	अगर (state->flags & SS_OUTPUT_ENA) अणु
		dev_info(&sock_info->dev->dev, "Power Enabled\n");
		reg |= I365_PWR_OUT;	/* enable घातer */
	पूर्ण

	चयन (state->Vcc) अणु
	हाल 0:
		अवरोध;
	हाल 50:
		dev_info(&sock_info->dev->dev,
			 "setting voltage to Vcc to 5V on socket %i\n",
			 sock);
		reg |= I365_VCC_5V;
		अवरोध;
	शेष:
		dev_err(&sock_info->dev->dev,
			"%s called with invalid VCC power value: %i",
			__func__, state->Vcc);
		वापस -EINVAL;
	पूर्ण

	चयन (state->Vpp) अणु
	हाल 0:
		dev_info(&sock_info->dev->dev,
			 "not setting Vpp on socket %i\n", sock);
		अवरोध;
	हाल 50:
		dev_info(&sock_info->dev->dev,
			 "setting Vpp to 5.0 for socket %i\n", sock);
		reg |= I365_VPP1_5V | I365_VPP2_5V;
		अवरोध;
	हाल 120:
		dev_info(&sock_info->dev->dev, "setting Vpp to 12.0\n");
		reg |= I365_VPP1_12V | I365_VPP2_12V;
		अवरोध;
	शेष:
		dev_err(&sock_info->dev->dev,
			"%s called with invalid VPP power value: %i",
			__func__, state->Vcc);
		वापस -EINVAL;
	पूर्ण

	अगर (reg != indirect_पढ़ो(sock, I365_POWER)) /* only ग_लिखो अगर changed */
		indirect_ग_लिखो(sock, I365_POWER, reg);

	/* Enable specअगरic पूर्णांकerrupt events */

	reg = 0x00;
	अगर (state->csc_mask & SS_DETECT)
		reg |= I365_CSC_DETECT;
	अगर (state->flags & SS_IOCARD) अणु
		अगर (state->csc_mask & SS_STSCHG)
			reg |= I365_CSC_STSCHG;
	पूर्ण अन्यथा अणु
		अगर (state->csc_mask & SS_BATDEAD)
			reg |= I365_CSC_BVD1;
		अगर (state->csc_mask & SS_BATWARN)
			reg |= I365_CSC_BVD2;
		अगर (state->csc_mask & SS_READY)
			reg |= I365_CSC_READY;

	पूर्ण

	/* now ग_लिखो the value and clear the (probably bogus) pending stuff
	 * by करोing a dummy पढ़ो
	 */

	indirect_ग_लिखो(sock, I365_CSCINT, reg);
	(व्योम)indirect_पढ़ो(sock, I365_CSC);

	वापस 0;
पूर्ण

अटल पूर्णांक i82092aa_set_io_map(काष्ठा pcmcia_socket *socket,
			       काष्ठा pccard_io_map *io)
अणु
	काष्ठा socket_info *sock_info = container_of(socket, काष्ठा socket_info,
						     socket);
	अचिन्हित पूर्णांक sock = sock_info->number;
	अचिन्हित अक्षर map, ioctl;

	map = io->map;

	/* Check error conditions */
	अगर (map > 1)
		वापस -EINVAL;

	अगर ((io->start > 0xffff) || (io->stop > 0xffff)
				 || (io->stop < io->start))
		वापस -EINVAL;

	/* Turn off the winकरोw beक्रमe changing anything */
	अगर (indirect_पढ़ो(sock, I365_ADDRWIN) & I365_ENA_IO(map))
		indirect_resetbit(sock, I365_ADDRWIN, I365_ENA_IO(map));

	/* ग_लिखो the new values */
	indirect_ग_लिखो16(sock, I365_IO(map)+I365_W_START, io->start);
	indirect_ग_लिखो16(sock, I365_IO(map)+I365_W_STOP, io->stop);

	ioctl = indirect_पढ़ो(sock, I365_IOCTL) & ~I365_IOCTL_MASK(map);

	अगर (io->flags & (MAP_16BIT|MAP_AUTOSZ))
		ioctl |= I365_IOCTL_16BIT(map);

	indirect_ग_लिखो(sock, I365_IOCTL, ioctl);

	/* Turn the winकरोw back on अगर needed */
	अगर (io->flags & MAP_ACTIVE)
		indirect_setbit(sock, I365_ADDRWIN, I365_ENA_IO(map));

	वापस 0;
पूर्ण

अटल पूर्णांक i82092aa_set_mem_map(काष्ठा pcmcia_socket *socket,
				काष्ठा pccard_mem_map *mem)
अणु
	काष्ठा socket_info *sock_info = container_of(socket, काष्ठा socket_info,
						     socket);
	अचिन्हित पूर्णांक sock = sock_info->number;
	काष्ठा pci_bus_region region;
	अचिन्हित लघु base, i;
	अचिन्हित अक्षर map;

	pcibios_resource_to_bus(sock_info->dev->bus, &region, mem->res);

	map = mem->map;
	अगर (map > 4)
		वापस -EINVAL;

	अगर ((mem->card_start > 0x3ffffff) || (region.start > region.end) ||
	     (mem->speed > 1000)) अणु
		dev_err(&sock_info->dev->dev,
			"invalid mem map for socket %i: %llx to %llx with a start of %x\n",
			sock,
			(अचिन्हित दीर्घ दीर्घ)region.start,
			(अचिन्हित दीर्घ दीर्घ)region.end,
			mem->card_start);
		वापस -EINVAL;
	पूर्ण

	/* Turn off the winकरोw beक्रमe changing anything */
	अगर (indirect_पढ़ो(sock, I365_ADDRWIN) & I365_ENA_MEM(map))
		indirect_resetbit(sock, I365_ADDRWIN, I365_ENA_MEM(map));

	/* ग_लिखो the start address */
	base = I365_MEM(map);
	i = (region.start >> 12) & 0x0fff;
	अगर (mem->flags & MAP_16BIT)
		i |= I365_MEM_16BIT;
	अगर (mem->flags & MAP_0WS)
		i |= I365_MEM_0WS;
	indirect_ग_लिखो16(sock, base+I365_W_START, i);

	/* ग_लिखो the stop address */

	i = (region.end >> 12) & 0x0fff;
	चयन (to_cycles(mem->speed)) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		i |= I365_MEM_WS0;
		अवरोध;
	हाल 2:
		i |= I365_MEM_WS1;
		अवरोध;
	शेष:
		i |= I365_MEM_WS1 | I365_MEM_WS0;
		अवरोध;
	पूर्ण

	indirect_ग_लिखो16(sock, base+I365_W_STOP, i);

	/* card start */

	i = ((mem->card_start - region.start) >> 12) & 0x3fff;
	अगर (mem->flags & MAP_WRPROT)
		i |= I365_MEM_WRPROT;
	अगर (mem->flags & MAP_ATTRIB)
		i |= I365_MEM_REG;
	indirect_ग_लिखो16(sock, base+I365_W_OFF, i);

	/* Enable the winकरोw अगर necessary */
	अगर (mem->flags & MAP_ACTIVE)
		indirect_setbit(sock, I365_ADDRWIN, I365_ENA_MEM(map));

	वापस 0;
पूर्ण

अटल पूर्णांक i82092aa_module_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&i82092aa_pci_driver);
पूर्ण

अटल व्योम i82092aa_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i82092aa_pci_driver);
	अगर (sockets[0].io_base > 0)
		release_region(sockets[0].io_base, 2);
पूर्ण

module_init(i82092aa_module_init);
module_निकास(i82092aa_module_निकास);

