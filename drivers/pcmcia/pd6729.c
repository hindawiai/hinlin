<शैली गुरु>
/*
 * Driver क्रम the Cirrus PD6729 PCI-PCMCIA bridge.
 *
 * Based on the i82092.c driver.
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License, incorporated herein by reference.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <pcmcia/ss.h>


#समावेश "pd6729.h"
#समावेश "i82365.h"
#समावेश "cirrus.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for the Cirrus PD6729 PCI-PCMCIA bridge");
MODULE_AUTHOR("Jun Komuro <komurojun-mbn@nifty.com>");

#घोषणा MAX_SOCKETS 2

/*
 * simple helper functions
 * External घड़ी समय, in nanoseconds.  120 ns = 8.33 MHz
 */
#घोषणा to_cycles(ns)	((ns)/120)

#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ	((अचिन्हित पूर्णांक)(0))
#पूर्ण_अगर

/*
 * PARAMETERS
 *  irq_mode=n
 *     Specअगरies the पूर्णांकerrupt delivery mode.  The शेष (1) is to use PCI
 *     पूर्णांकerrupts; a value of 0 selects ISA पूर्णांकerrupts. This must be set क्रम
 *     correct operation of PCI card पढ़ोers.
 */

अटल पूर्णांक irq_mode = 1; /* 0 = ISA पूर्णांकerrupt, 1 = PCI पूर्णांकerrupt */

module_param(irq_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(irq_mode,
		"interrupt delivery mode. 0 = ISA, 1 = PCI. default is 1");

अटल DEFINE_SPINLOCK(port_lock);

/* basic value पढ़ो/ग_लिखो functions */

अटल अचिन्हित अक्षर indirect_पढ़ो(काष्ठा pd6729_socket *socket,
				   अचिन्हित लघु reg)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg += socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	val = inb(port + 1);
	spin_unlock_irqrestore(&port_lock, flags);

	वापस val;
पूर्ण

अटल अचिन्हित लघु indirect_पढ़ो16(काष्ठा pd6729_socket *socket,
				      अचिन्हित लघु reg)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित लघु पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg  = reg + socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	पंचांगp = inb(port + 1);
	reg++;
	outb(reg, port);
	पंचांगp = पंचांगp | (inb(port + 1) << 8);
	spin_unlock_irqrestore(&port_lock, flags);

	वापस पंचांगp;
पूर्ण

अटल व्योम indirect_ग_लिखो(काष्ठा pd6729_socket *socket, अचिन्हित लघु reg,
			   अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	outb(value, port + 1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

अटल व्योम indirect_setbit(काष्ठा pd6729_socket *socket, अचिन्हित लघु reg,
			    अचिन्हित अक्षर mask)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	val = inb(port + 1);
	val |= mask;
	outb(reg, port);
	outb(val, port + 1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

अटल व्योम indirect_resetbit(काष्ठा pd6729_socket *socket, अचिन्हित लघु reg,
			      अचिन्हित अक्षर mask)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket->number * 0x40;
	port = socket->io_base;
	outb(reg, port);
	val = inb(port + 1);
	val &= ~mask;
	outb(reg, port);
	outb(val, port + 1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

अटल व्योम indirect_ग_लिखो16(काष्ठा pd6729_socket *socket, अचिन्हित लघु reg,
			     अचिन्हित लघु value)
अणु
	अचिन्हित दीर्घ port;
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port_lock, flags);
	reg = reg + socket->number * 0x40;
	port = socket->io_base;

	outb(reg, port);
	val = value & 255;
	outb(val, port + 1);

	reg++;

	outb(reg, port);
	val = value >> 8;
	outb(val, port + 1);
	spin_unlock_irqrestore(&port_lock, flags);
पूर्ण

/* Interrupt handler functionality */

अटल irqवापस_t pd6729_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा pd6729_socket *socket = (काष्ठा pd6729_socket *)dev;
	पूर्णांक i;
	पूर्णांक loopcount = 0;
	पूर्णांक handled = 0;
	अचिन्हित पूर्णांक events, active = 0;

	जबतक (1) अणु
		loopcount++;
		अगर (loopcount > 20) अणु
			prपूर्णांकk(KERN_ERR "pd6729: infinite eventloop "
			       "in interrupt\n");
			अवरोध;
		पूर्ण

		active = 0;

		क्रम (i = 0; i < MAX_SOCKETS; i++) अणु
			अचिन्हित पूर्णांक csc;

			/* card status change रेजिस्टर */
			csc = indirect_पढ़ो(&socket[i], I365_CSC);
			अगर (csc == 0)  /* no events on this socket */
				जारी;

			handled = 1;
			events = 0;

			अगर (csc & I365_CSC_DETECT) अणु
				events |= SS_DETECT;
				dev_vdbg(&socket[i].socket.dev,
					"Card detected in socket %i!\n", i);
			पूर्ण

			अगर (indirect_पढ़ो(&socket[i], I365_INTCTL)
						& I365_PC_IOCARD) अणु
				/* For IO/CARDS, bit 0 means "read the card" */
				events |= (csc & I365_CSC_STSCHG)
						? SS_STSCHG : 0;
			पूर्ण अन्यथा अणु
				/* Check क्रम battery/पढ़ोy events */
				events |= (csc & I365_CSC_BVD1)
						? SS_BATDEAD : 0;
				events |= (csc & I365_CSC_BVD2)
						? SS_BATWARN : 0;
				events |= (csc & I365_CSC_READY)
						? SS_READY : 0;
			पूर्ण

			अगर (events)
				pcmcia_parse_events(&socket[i].socket, events);

			active |= events;
		पूर्ण

		अगर (active == 0) /* no more events to handle */
			अवरोध;
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

/* socket functions */

अटल व्योम pd6729_पूर्णांकerrupt_wrapper(काष्ठा समयr_list *t)
अणु
	काष्ठा pd6729_socket *socket = from_समयr(socket, t, poll_समयr);

	pd6729_पूर्णांकerrupt(0, (व्योम *)socket);
	mod_समयr(&socket->poll_समयr, jअगरfies + HZ);
पूर्ण

अटल पूर्णांक pd6729_get_status(काष्ठा pcmcia_socket *sock, u_पूर्णांक *value)
अणु
	काष्ठा pd6729_socket *socket
			= container_of(sock, काष्ठा pd6729_socket, socket);
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक data;
	काष्ठा pd6729_socket *t;

	/* Interface Status Register */
	status = indirect_पढ़ो(socket, I365_STATUS);
	*value = 0;

	अगर ((status & I365_CS_DETECT) == I365_CS_DETECT)
		*value |= SS_DETECT;

	/*
	 * IO cards have a dअगरferent meaning of bits 0,1
	 * Also notice the inverse-logic on the bits
	 */
	अगर (indirect_पढ़ो(socket, I365_INTCTL) & I365_PC_IOCARD) अणु
		/* IO card */
		अगर (!(status & I365_CS_STSCHG))
			*value |= SS_STSCHG;
	पूर्ण अन्यथा अणु
		/* non I/O card */
		अगर (!(status & I365_CS_BVD1))
			*value |= SS_BATDEAD;
		अगर (!(status & I365_CS_BVD2))
			*value |= SS_BATWARN;
	पूर्ण

	अगर (status & I365_CS_WRPROT)
		*value |= SS_WRPROT;	/* card is ग_लिखो रक्षित */

	अगर (status & I365_CS_READY)
		*value |= SS_READY;	/* card is not busy */

	अगर (status & I365_CS_POWERON)
		*value |= SS_POWERON;	/* घातer is applied to the card */

	t = (socket->number) ? socket : socket + 1;
	indirect_ग_लिखो(t, PD67_EXT_INDEX, PD67_EXTERN_DATA);
	data = indirect_पढ़ो16(t, PD67_EXT_DATA);
	*value |= (data & PD67_EXD_VS1(socket->number)) ? 0 : SS_3VCARD;

	वापस 0;
पूर्ण


अटल पूर्णांक pd6729_set_socket(काष्ठा pcmcia_socket *sock, socket_state_t *state)
अणु
	काष्ठा pd6729_socket *socket
			= container_of(sock, काष्ठा pd6729_socket, socket);
	अचिन्हित अक्षर reg, data;

	/* First, set the global controller options */
	indirect_ग_लिखो(socket, I365_GBLCTL, 0x00);
	indirect_ग_लिखो(socket, I365_GENCTL, 0x00);

	/* Values क्रम the IGENC रेजिस्टर */
	socket->card_irq = state->io_irq;

	reg = 0;
	/* The reset bit has "inverse" logic */
	अगर (!(state->flags & SS_RESET))
		reg |= I365_PC_RESET;
	अगर (state->flags & SS_IOCARD)
		reg |= I365_PC_IOCARD;

	/* IGENC, Interrupt and General Control Register */
	indirect_ग_लिखो(socket, I365_INTCTL, reg);

	/* Power रेजिस्टरs */

	reg = I365_PWR_NORESET; /* शेष: disable resetdrv on resume */

	अगर (state->flags & SS_PWR_AUTO) अणु
		dev_dbg(&sock->dev, "Auto power\n");
		reg |= I365_PWR_AUTO;	/* स्वतःmatic घातer mngmnt */
	पूर्ण
	अगर (state->flags & SS_OUTPUT_ENA) अणु
		dev_dbg(&sock->dev, "Power Enabled\n");
		reg |= I365_PWR_OUT;	/* enable घातer */
	पूर्ण

	चयन (state->Vcc) अणु
	हाल 0:
		अवरोध;
	हाल 33:
		dev_dbg(&sock->dev,
			"setting voltage to Vcc to 3.3V on socket %i\n",
			socket->number);
		reg |= I365_VCC_5V;
		indirect_setbit(socket, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
		अवरोध;
	हाल 50:
		dev_dbg(&sock->dev,
			"setting voltage to Vcc to 5V on socket %i\n",
			socket->number);
		reg |= I365_VCC_5V;
		indirect_resetbit(socket, PD67_MISC_CTL_1, PD67_MC1_VCC_3V);
		अवरोध;
	शेष:
		dev_dbg(&sock->dev,
			"pd6729_set_socket called with invalid VCC power "
			"value: %i\n", state->Vcc);
		वापस -EINVAL;
	पूर्ण

	चयन (state->Vpp) अणु
	हाल 0:
		dev_dbg(&sock->dev, "not setting Vpp on socket %i\n",
			socket->number);
		अवरोध;
	हाल 33:
	हाल 50:
		dev_dbg(&sock->dev, "setting Vpp to Vcc for socket %i\n",
			socket->number);
		reg |= I365_VPP1_5V;
		अवरोध;
	हाल 120:
		dev_dbg(&sock->dev, "setting Vpp to 12.0\n");
		reg |= I365_VPP1_12V;
		अवरोध;
	शेष:
		dev_dbg(&sock->dev, "pd6729: pd6729_set_socket called with "
			"invalid VPP power value: %i\n", state->Vpp);
		वापस -EINVAL;
	पूर्ण

	/* only ग_लिखो अगर changed */
	अगर (reg != indirect_पढ़ो(socket, I365_POWER))
		indirect_ग_लिखो(socket, I365_POWER, reg);

	अगर (irq_mode == 1) अणु
		/* all पूर्णांकerrupts are to be करोne as PCI पूर्णांकerrupts */
		data = PD67_EC1_INV_MGMT_IRQ | PD67_EC1_INV_CARD_IRQ;
	पूर्ण अन्यथा
		data = 0;

	indirect_ग_लिखो(socket, PD67_EXT_INDEX, PD67_EXT_CTL_1);
	indirect_ग_लिखो(socket, PD67_EXT_DATA, data);

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
	अगर (irq_mode == 1)
		reg |= 0x30;	/* management IRQ: PCI INTA# = "irq 3" */
	indirect_ग_लिखो(socket, I365_CSCINT, reg);

	reg = indirect_पढ़ो(socket, I365_INTCTL);
	अगर (irq_mode == 1)
		reg |= 0x03;	/* card IRQ: PCI INTA# = "irq 3" */
	अन्यथा
		reg |= socket->card_irq;
	indirect_ग_लिखो(socket, I365_INTCTL, reg);

	/* now clear the (probably bogus) pending stuff by करोing a dummy पढ़ो */
	(व्योम)indirect_पढ़ो(socket, I365_CSC);

	वापस 0;
पूर्ण

अटल पूर्णांक pd6729_set_io_map(काष्ठा pcmcia_socket *sock,
			     काष्ठा pccard_io_map *io)
अणु
	काष्ठा pd6729_socket *socket
			= container_of(sock, काष्ठा pd6729_socket, socket);
	अचिन्हित अक्षर map, ioctl;

	map = io->map;

	/* Check error conditions */
	अगर (map > 1) अणु
		dev_dbg(&sock->dev, "pd6729_set_io_map with invalid map\n");
		वापस -EINVAL;
	पूर्ण

	/* Turn off the winकरोw beक्रमe changing anything */
	अगर (indirect_पढ़ो(socket, I365_ADDRWIN) & I365_ENA_IO(map))
		indirect_resetbit(socket, I365_ADDRWIN, I365_ENA_IO(map));

	/* dev_dbg(&sock->dev, "set_io_map: Setting range to %x - %x\n",
	   io->start, io->stop);*/

	/* ग_लिखो the new values */
	indirect_ग_लिखो16(socket, I365_IO(map)+I365_W_START, io->start);
	indirect_ग_लिखो16(socket, I365_IO(map)+I365_W_STOP, io->stop);

	ioctl = indirect_पढ़ो(socket, I365_IOCTL) & ~I365_IOCTL_MASK(map);

	अगर (io->flags & MAP_0WS)
		ioctl |= I365_IOCTL_0WS(map);
	अगर (io->flags & MAP_16BIT)
		ioctl |= I365_IOCTL_16BIT(map);
	अगर (io->flags & MAP_AUTOSZ)
		ioctl |= I365_IOCTL_IOCS16(map);

	indirect_ग_लिखो(socket, I365_IOCTL, ioctl);

	/* Turn the winकरोw back on अगर needed */
	अगर (io->flags & MAP_ACTIVE)
		indirect_setbit(socket, I365_ADDRWIN, I365_ENA_IO(map));

	वापस 0;
पूर्ण

अटल पूर्णांक pd6729_set_mem_map(काष्ठा pcmcia_socket *sock,
			      काष्ठा pccard_mem_map *mem)
अणु
	काष्ठा pd6729_socket *socket
			 = container_of(sock, काष्ठा pd6729_socket, socket);
	अचिन्हित लघु base, i;
	अचिन्हित अक्षर map;

	map = mem->map;
	अगर (map > 4) अणु
		dev_warn(&sock->dev, "invalid map requested\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((mem->res->start > mem->res->end) || (mem->speed > 1000)) अणु
		dev_warn(&sock->dev, "invalid invalid address / speed\n");
		वापस -EINVAL;
	पूर्ण

	/* Turn off the winकरोw beक्रमe changing anything */
	अगर (indirect_पढ़ो(socket, I365_ADDRWIN) & I365_ENA_MEM(map))
		indirect_resetbit(socket, I365_ADDRWIN, I365_ENA_MEM(map));

	/* ग_लिखो the start address */
	base = I365_MEM(map);
	i = (mem->res->start >> 12) & 0x0fff;
	अगर (mem->flags & MAP_16BIT)
		i |= I365_MEM_16BIT;
	अगर (mem->flags & MAP_0WS)
		i |= I365_MEM_0WS;
	indirect_ग_लिखो16(socket, base + I365_W_START, i);

	/* ग_लिखो the stop address */

	i = (mem->res->end >> 12) & 0x0fff;
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

	indirect_ग_लिखो16(socket, base + I365_W_STOP, i);

	/* Take care of high byte */
	indirect_ग_लिखो(socket, PD67_EXT_INDEX, PD67_MEM_PAGE(map));
	indirect_ग_लिखो(socket, PD67_EXT_DATA, mem->res->start >> 24);

	/* card start */

	i = ((mem->card_start - mem->res->start) >> 12) & 0x3fff;
	अगर (mem->flags & MAP_WRPROT)
		i |= I365_MEM_WRPROT;
	अगर (mem->flags & MAP_ATTRIB) अणु
		/* dev_dbg(&sock->dev, "requesting attribute memory for "
		   "socket %i\n", socket->number);*/
		i |= I365_MEM_REG;
	पूर्ण अन्यथा अणु
		/* dev_dbg(&sock->dev, "requesting normal memory for "
		   "socket %i\n", socket->number);*/
	पूर्ण
	indirect_ग_लिखो16(socket, base + I365_W_OFF, i);

	/* Enable the winकरोw अगर necessary */
	अगर (mem->flags & MAP_ACTIVE)
		indirect_setbit(socket, I365_ADDRWIN, I365_ENA_MEM(map));

	वापस 0;
पूर्ण

अटल पूर्णांक pd6729_init(काष्ठा pcmcia_socket *sock)
अणु
	पूर्णांक i;
	काष्ठा resource res = अणु .end = 0x0fff पूर्ण;
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_mem_map mem = अणु .res = &res, पूर्ण;

	pd6729_set_socket(sock, &dead_socket);
	क्रम (i = 0; i < 2; i++) अणु
		io.map = i;
		pd6729_set_io_map(sock, &io);
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		mem.map = i;
		pd6729_set_mem_map(sock, &mem);
	पूर्ण

	वापस 0;
पूर्ण


/* the pccard काष्ठाure and its functions */
अटल काष्ठा pccard_operations pd6729_operations = अणु
	.init			= pd6729_init,
	.get_status		= pd6729_get_status,
	.set_socket		= pd6729_set_socket,
	.set_io_map		= pd6729_set_io_map,
	.set_mem_map		= pd6729_set_mem_map,
पूर्ण;

अटल irqवापस_t pd6729_test(पूर्णांक irq, व्योम *dev)
अणु
	pr_devel("-> hit on irq %d\n", irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pd6729_check_irq(पूर्णांक irq)
अणु
	पूर्णांक ret;

	ret = request_irq(irq, pd6729_test, IRQF_PROBE_SHARED, "x",
			  pd6729_test);
	अगर (ret)
		वापस -1;

	मुक्त_irq(irq, pd6729_test);
	वापस 0;
पूर्ण

अटल u_पूर्णांक pd6729_isa_scan(व्योम)
अणु
	u_पूर्णांक mask0, mask = 0;
	पूर्णांक i;

	अगर (irq_mode == 1) अणु
		prपूर्णांकk(KERN_INFO "pd6729: PCI card interrupts, "
		       "PCI status changes\n");
		वापस 0;
	पूर्ण

	mask0 = PD67_MASK;

	/* just find पूर्णांकerrupts that aren't in use */
	क्रम (i = 0; i < 16; i++)
		अगर ((mask0 & (1 << i)) && (pd6729_check_irq(i) == 0))
			mask |= (1 << i);

	prपूर्णांकk(KERN_INFO "pd6729: ISA irqs = ");
	क्रम (i = 0; i < 16; i++)
		अगर (mask & (1<<i))
			prपूर्णांकk("%s%d", ((mask & ((1<<i)-1)) ? "," : ""), i);

	अगर (mask == 0)
		prपूर्णांकk("none!");
	अन्यथा
		prपूर्णांकk("  polling status changes.\n");

	वापस mask;
पूर्ण

अटल पूर्णांक pd6729_pci_probe(काष्ठा pci_dev *dev,
				      स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक i, j, ret;
	u_पूर्णांक mask;
	अक्षर configbyte;
	काष्ठा pd6729_socket *socket;

	socket = kसुस्मृति(MAX_SOCKETS, माप(काष्ठा pd6729_socket),
			 GFP_KERNEL);
	अगर (!socket) अणु
		dev_warn(&dev->dev, "failed to kzalloc socket.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = pci_enable_device(dev);
	अगर (ret) अणु
		dev_warn(&dev->dev, "failed to enable pci_device.\n");
		जाओ err_out_मुक्त_mem;
	पूर्ण

	अगर (!pci_resource_start(dev, 0)) अणु
		dev_warn(&dev->dev, "refusing to load the driver as the "
			"io_base is NULL.\n");
		ret = -ENOMEM;
		जाओ err_out_disable;
	पूर्ण

	dev_info(&dev->dev, "Cirrus PD6729 PCI to PCMCIA Bridge at 0x%llx "
		"on irq %d\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0), dev->irq);
	/*
	 * Since we have no memory BARs some firmware may not
	 * have had PCI_COMMAND_MEMORY enabled, yet the device needs it.
	 */
	pci_पढ़ो_config_byte(dev, PCI_COMMAND, &configbyte);
	अगर (!(configbyte & PCI_COMMAND_MEMORY)) अणु
		dev_dbg(&dev->dev, "pd6729: Enabling PCI_COMMAND_MEMORY.\n");
		configbyte |= PCI_COMMAND_MEMORY;
		pci_ग_लिखो_config_byte(dev, PCI_COMMAND, configbyte);
	पूर्ण

	ret = pci_request_regions(dev, "pd6729");
	अगर (ret) अणु
		dev_warn(&dev->dev, "pci request region failed.\n");
		जाओ err_out_disable;
	पूर्ण

	अगर (dev->irq == NO_IRQ)
		irq_mode = 0;	/* fall back to ISA पूर्णांकerrupt mode */

	mask = pd6729_isa_scan();
	अगर (irq_mode == 0 && mask == 0) अणु
		dev_warn(&dev->dev, "no ISA interrupt is available.\n");
		ret = -ENODEV;
		जाओ err_out_मुक्त_res;
	पूर्ण

	क्रम (i = 0; i < MAX_SOCKETS; i++) अणु
		socket[i].io_base = pci_resource_start(dev, 0);
		socket[i].socket.features |= SS_CAP_PAGE_REGS | SS_CAP_PCCARD;
		socket[i].socket.map_size = 0x1000;
		socket[i].socket.irq_mask = mask;
		socket[i].socket.pci_irq  = dev->irq;
		socket[i].socket.cb_dev = dev;
		socket[i].socket.owner = THIS_MODULE;

		socket[i].number = i;

		socket[i].socket.ops = &pd6729_operations;
		socket[i].socket.resource_ops = &pccard_nonअटल_ops;
		socket[i].socket.dev.parent = &dev->dev;
		socket[i].socket.driver_data = &socket[i];
	पूर्ण

	pci_set_drvdata(dev, socket);
	अगर (irq_mode == 1) अणु
		/* Register the पूर्णांकerrupt handler */
		ret = request_irq(dev->irq, pd6729_पूर्णांकerrupt, IRQF_SHARED,
				  "pd6729", socket);
		अगर (ret) अणु
			dev_err(&dev->dev, "Failed to register irq %d\n",
				dev->irq);
			जाओ err_out_मुक्त_res;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* poll Card status change */
		समयr_setup(&socket->poll_समयr, pd6729_पूर्णांकerrupt_wrapper, 0);
		mod_समयr(&socket->poll_समयr, jअगरfies + HZ);
	पूर्ण

	क्रम (i = 0; i < MAX_SOCKETS; i++) अणु
		ret = pcmcia_रेजिस्टर_socket(&socket[i].socket);
		अगर (ret) अणु
			dev_warn(&dev->dev, "pcmcia_register_socket failed.\n");
			क्रम (j = 0; j < i ; j++)
				pcmcia_unरेजिस्टर_socket(&socket[j].socket);
			जाओ err_out_मुक्त_res2;
		पूर्ण
	पूर्ण

	वापस 0;

err_out_मुक्त_res2:
	अगर (irq_mode == 1)
		मुक्त_irq(dev->irq, socket);
	अन्यथा
		del_समयr_sync(&socket->poll_समयr);
err_out_मुक्त_res:
	pci_release_regions(dev);
err_out_disable:
	pci_disable_device(dev);

err_out_मुक्त_mem:
	kमुक्त(socket);
	वापस ret;
पूर्ण

अटल व्योम pd6729_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा pd6729_socket *socket = pci_get_drvdata(dev);

	क्रम (i = 0; i < MAX_SOCKETS; i++) अणु
		/* Turn off all पूर्णांकerrupt sources */
		indirect_ग_लिखो(&socket[i], I365_CSCINT, 0);
		indirect_ग_लिखो(&socket[i], I365_INTCTL, 0);

		pcmcia_unरेजिस्टर_socket(&socket[i].socket);
	पूर्ण

	अगर (irq_mode == 1)
		मुक्त_irq(dev->irq, socket);
	अन्यथा
		del_समयr_sync(&socket->poll_समयr);
	pci_release_regions(dev);
	pci_disable_device(dev);

	kमुक्त(socket);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pd6729_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CIRRUS, PCI_DEVICE_ID_CIRRUS_6729) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pd6729_pci_ids);

अटल काष्ठा pci_driver pd6729_pci_driver = अणु
	.name		= "pd6729",
	.id_table	= pd6729_pci_ids,
	.probe		= pd6729_pci_probe,
	.हटाओ		= pd6729_pci_हटाओ,
पूर्ण;

module_pci_driver(pd6729_pci_driver);
