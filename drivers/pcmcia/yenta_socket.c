<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regular cardbus driver ("yenta_socket")
 *
 * (C) Copyright 1999, 2000 Linus Torvalds
 *
 * Changelog:
 * Aug 2002: Manfred Spraul <manfred@colorfullअगरe.com>
 * 	Dynamically adjust the size of the bridge resource
 *
 * May 2003: Dominik Broकरोwski <linux@broकरो.de>
 * 	Merge pci_socket.c and yenta.c पूर्णांकo one file
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <pcmcia/ss.h>

#समावेश "yenta_socket.h"
#समावेश "i82365.h"

अटल bool disable_clkrun;
module_param(disable_clkrun, bool, 0444);
MODULE_PARM_DESC(disable_clkrun,
		 "If PC card doesn't function properly, please try this option (TI and Ricoh bridges only)");

अटल bool isa_probe = 1;
module_param(isa_probe, bool, 0444);
MODULE_PARM_DESC(isa_probe, "If set ISA interrupts are probed (default). Set to N to disable probing");

अटल bool pwr_irqs_off;
module_param(pwr_irqs_off, bool, 0644);
MODULE_PARM_DESC(pwr_irqs_off, "Force IRQs off during power-on of slot. Use only when seeing IRQ storms!");

अटल अक्षर o2_speedup[] = "default";
module_param_string(o2_speedup, o2_speedup, माप(o2_speedup), 0444);
MODULE_PARM_DESC(o2_speedup, "Use prefetch/burst for O2-bridges: 'on', 'off' "
	"or 'default' (uses recommended behaviour for the detected bridge)");

/*
 * Only probe "regular" पूर्णांकerrupts, करोn't
 * touch dangerous spots like the mouse irq,
 * because there are mice that apparently
 * get really confused अगर they get fondled
 * too पूर्णांकimately.
 *
 * Default to 11, 10, 9, 7, 6, 5, 4, 3.
 */
अटल u32 isa_पूर्णांकerrupts = 0x0ef8;


#घोषणा debug(x, s, args...) dev_dbg(&s->dev->dev, x, ##args)

/* Don't ask.. */
#घोषणा to_cycles(ns)	((ns)/120)
#घोषणा to_ns(cycles)	((cycles)*120)

/*
 * yenta PCI irq probing.
 * currently only used in the TI/EnE initialization code
 */
#अगर_घोषित CONFIG_YENTA_TI
अटल पूर्णांक yenta_probe_cb_irq(काष्ठा yenta_socket *socket);
अटल अचिन्हित पूर्णांक yenta_probe_irq(काष्ठा yenta_socket *socket,
				u32 isa_irq_mask);
#पूर्ण_अगर


अटल अचिन्हित पूर्णांक override_bios;
module_param(override_bios, uपूर्णांक, 0000);
MODULE_PARM_DESC(override_bios, "yenta ignore bios resource allocation");

/*
 * Generate easy-to-use ways of पढ़ोing a cardbus sockets
 * regular memory space ("cb_xxx"), configuration space
 * ("config_xxx") and compatibility space ("exca_xxxx")
 */
अटल अंतरभूत u32 cb_पढ़ोl(काष्ठा yenta_socket *socket, अचिन्हित reg)
अणु
	u32 val = पढ़ोl(socket->base + reg);
	debug("%04x %08x\n", socket, reg, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम cb_ग_लिखोl(काष्ठा yenta_socket *socket, अचिन्हित reg, u32 val)
अणु
	debug("%04x %08x\n", socket, reg, val);
	ग_लिखोl(val, socket->base + reg);
	पढ़ोl(socket->base + reg); /* aव्योम problems with PCI ग_लिखो posting */
पूर्ण

अटल अंतरभूत u8 config_पढ़ोb(काष्ठा yenta_socket *socket, अचिन्हित offset)
अणु
	u8 val;
	pci_पढ़ो_config_byte(socket->dev, offset, &val);
	debug("%04x %02x\n", socket, offset, val);
	वापस val;
पूर्ण

अटल अंतरभूत u16 config_पढ़ोw(काष्ठा yenta_socket *socket, अचिन्हित offset)
अणु
	u16 val;
	pci_पढ़ो_config_word(socket->dev, offset, &val);
	debug("%04x %04x\n", socket, offset, val);
	वापस val;
पूर्ण

अटल अंतरभूत u32 config_पढ़ोl(काष्ठा yenta_socket *socket, अचिन्हित offset)
अणु
	u32 val;
	pci_पढ़ो_config_dword(socket->dev, offset, &val);
	debug("%04x %08x\n", socket, offset, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम config_ग_लिखोb(काष्ठा yenta_socket *socket, अचिन्हित offset, u8 val)
अणु
	debug("%04x %02x\n", socket, offset, val);
	pci_ग_लिखो_config_byte(socket->dev, offset, val);
पूर्ण

अटल अंतरभूत व्योम config_ग_लिखोw(काष्ठा yenta_socket *socket, अचिन्हित offset, u16 val)
अणु
	debug("%04x %04x\n", socket, offset, val);
	pci_ग_लिखो_config_word(socket->dev, offset, val);
पूर्ण

अटल अंतरभूत व्योम config_ग_लिखोl(काष्ठा yenta_socket *socket, अचिन्हित offset, u32 val)
अणु
	debug("%04x %08x\n", socket, offset, val);
	pci_ग_लिखो_config_dword(socket->dev, offset, val);
पूर्ण

अटल अंतरभूत u8 exca_पढ़ोb(काष्ठा yenta_socket *socket, अचिन्हित reg)
अणु
	u8 val = पढ़ोb(socket->base + 0x800 + reg);
	debug("%04x %02x\n", socket, reg, val);
	वापस val;
पूर्ण

अटल अंतरभूत u8 exca_पढ़ोw(काष्ठा yenta_socket *socket, अचिन्हित reg)
अणु
	u16 val;
	val = पढ़ोb(socket->base + 0x800 + reg);
	val |= पढ़ोb(socket->base + 0x800 + reg + 1) << 8;
	debug("%04x %04x\n", socket, reg, val);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम exca_ग_लिखोb(काष्ठा yenta_socket *socket, अचिन्हित reg, u8 val)
अणु
	debug("%04x %02x\n", socket, reg, val);
	ग_लिखोb(val, socket->base + 0x800 + reg);
	पढ़ोb(socket->base + 0x800 + reg); /* PCI ग_लिखो posting... */
पूर्ण

अटल व्योम exca_ग_लिखोw(काष्ठा yenta_socket *socket, अचिन्हित reg, u16 val)
अणु
	debug("%04x %04x\n", socket, reg, val);
	ग_लिखोb(val, socket->base + 0x800 + reg);
	ग_लिखोb(val >> 8, socket->base + 0x800 + reg + 1);

	/* PCI ग_लिखो posting... */
	पढ़ोb(socket->base + 0x800 + reg);
	पढ़ोb(socket->base + 0x800 + reg + 1);
पूर्ण

अटल sमाप_प्रकार show_yenta_रेजिस्टरs(काष्ठा device *yentadev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा yenta_socket *socket = dev_get_drvdata(yentadev);
	पूर्णांक offset = 0, i;

	offset = snम_लिखो(buf, PAGE_SIZE, "CB registers:");
	क्रम (i = 0; i < 0x24; i += 4) अणु
		अचिन्हित val;
		अगर (!(i & 15))
			offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, "\n%02x:", i);
		val = cb_पढ़ोl(socket, i);
		offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, " %08x", val);
	पूर्ण

	offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, "\n\nExCA registers:");
	क्रम (i = 0; i < 0x45; i++) अणु
		अचिन्हित अक्षर val;
		अगर (!(i & 7)) अणु
			अगर (i & 8) अणु
				स_नकल(buf + offset, " -", 2);
				offset += 2;
			पूर्ण अन्यथा
				offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, "\n%02x:", i);
		पूर्ण
		val = exca_पढ़ोb(socket, i);
		offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, " %02x", val);
	पूर्ण
	buf[offset++] = '\n';
	वापस offset;
पूर्ण

अटल DEVICE_ATTR(yenta_रेजिस्टरs, S_IRUSR, show_yenta_रेजिस्टरs, शून्य);

/*
 * Ugh, mixed-mode cardbus and 16-bit pccard state: things depend
 * on what kind of card is inserted..
 */
अटल पूर्णांक yenta_get_status(काष्ठा pcmcia_socket *sock, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	अचिन्हित पूर्णांक val;
	u32 state = cb_पढ़ोl(socket, CB_SOCKET_STATE);

	val  = (state & CB_3VCARD) ? SS_3VCARD : 0;
	val |= (state & CB_XVCARD) ? SS_XVCARD : 0;
	val |= (state & (CB_5VCARD | CB_3VCARD | CB_XVCARD | CB_YVCARD)) ? 0 : SS_PENDING;
	val |= (state & (CB_CDETECT1 | CB_CDETECT2)) ? SS_PENDING : 0;


	अगर (state & CB_CBCARD) अणु
		val |= SS_CARDBUS;
		val |= (state & CB_CARDSTS) ? SS_STSCHG : 0;
		val |= (state & (CB_CDETECT1 | CB_CDETECT2)) ? 0 : SS_DETECT;
		val |= (state & CB_PWRCYCLE) ? SS_POWERON | SS_READY : 0;
	पूर्ण अन्यथा अगर (state & CB_16BITCARD) अणु
		u8 status = exca_पढ़ोb(socket, I365_STATUS);
		val |= ((status & I365_CS_DETECT) == I365_CS_DETECT) ? SS_DETECT : 0;
		अगर (exca_पढ़ोb(socket, I365_INTCTL) & I365_PC_IOCARD) अणु
			val |= (status & I365_CS_STSCHG) ? 0 : SS_STSCHG;
		पूर्ण अन्यथा अणु
			val |= (status & I365_CS_BVD1) ? 0 : SS_BATDEAD;
			val |= (status & I365_CS_BVD2) ? 0 : SS_BATWARN;
		पूर्ण
		val |= (status & I365_CS_WRPROT) ? SS_WRPROT : 0;
		val |= (status & I365_CS_READY) ? SS_READY : 0;
		val |= (status & I365_CS_POWERON) ? SS_POWERON : 0;
	पूर्ण

	*value = val;
	वापस 0;
पूर्ण

अटल व्योम yenta_set_घातer(काष्ठा yenta_socket *socket, socket_state_t *state)
अणु
	/* some birdges require to use the ExCA रेजिस्टरs to घातer 16bit cards */
	अगर (!(cb_पढ़ोl(socket, CB_SOCKET_STATE) & CB_CBCARD) &&
	    (socket->flags & YENTA_16BIT_POWER_EXCA)) अणु
		u8 reg, old;
		reg = old = exca_पढ़ोb(socket, I365_POWER);
		reg &= ~(I365_VCC_MASK | I365_VPP1_MASK | I365_VPP2_MASK);

		/* i82365SL-DF style */
		अगर (socket->flags & YENTA_16BIT_POWER_DF) अणु
			चयन (state->Vcc) अणु
			हाल 33:
				reg |= I365_VCC_3V;
				अवरोध;
			हाल 50:
				reg |= I365_VCC_5V;
				अवरोध;
			शेष:
				reg = 0;
				अवरोध;
			पूर्ण
			चयन (state->Vpp) अणु
			हाल 33:
			हाल 50:
				reg |= I365_VPP1_5V;
				अवरोध;
			हाल 120:
				reg |= I365_VPP1_12V;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* i82365SL-B style */
			चयन (state->Vcc) अणु
			हाल 50:
				reg |= I365_VCC_5V;
				अवरोध;
			शेष:
				reg = 0;
				अवरोध;
			पूर्ण
			चयन (state->Vpp) अणु
			हाल 50:
				reg |= I365_VPP1_5V | I365_VPP2_5V;
				अवरोध;
			हाल 120:
				reg |= I365_VPP1_12V | I365_VPP2_12V;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (reg != old)
			exca_ग_लिखोb(socket, I365_POWER, reg);
	पूर्ण अन्यथा अणु
		u32 reg = 0;	/* CB_SC_STPCLK? */
		चयन (state->Vcc) अणु
		हाल 33:
			reg = CB_SC_VCC_3V;
			अवरोध;
		हाल 50:
			reg = CB_SC_VCC_5V;
			अवरोध;
		शेष:
			reg = 0;
			अवरोध;
		पूर्ण
		चयन (state->Vpp) अणु
		हाल 33:
			reg |= CB_SC_VPP_3V;
			अवरोध;
		हाल 50:
			reg |= CB_SC_VPP_5V;
			अवरोध;
		हाल 120:
			reg |= CB_SC_VPP_12V;
			अवरोध;
		पूर्ण
		अगर (reg != cb_पढ़ोl(socket, CB_SOCKET_CONTROL))
			cb_ग_लिखोl(socket, CB_SOCKET_CONTROL, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक yenta_set_socket(काष्ठा pcmcia_socket *sock, socket_state_t *state)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	u16 bridge;

	/* अगर घातering करोwn: करो it immediately */
	अगर (state->Vcc == 0)
		yenta_set_घातer(socket, state);

	socket->io_irq = state->io_irq;
	bridge = config_पढ़ोw(socket, CB_BRIDGE_CONTROL) & ~(CB_BRIDGE_CRST | CB_BRIDGE_INTR);
	अगर (cb_पढ़ोl(socket, CB_SOCKET_STATE) & CB_CBCARD) अणु
		u8 पूर्णांकr;
		bridge |= (state->flags & SS_RESET) ? CB_BRIDGE_CRST : 0;

		/* ISA पूर्णांकerrupt control? */
		पूर्णांकr = exca_पढ़ोb(socket, I365_INTCTL);
		पूर्णांकr = (पूर्णांकr & ~0xf);
		अगर (!socket->dev->irq) अणु
			पूर्णांकr |= socket->cb_irq ? socket->cb_irq : state->io_irq;
			bridge |= CB_BRIDGE_INTR;
		पूर्ण
		exca_ग_लिखोb(socket, I365_INTCTL, पूर्णांकr);
	पूर्ण  अन्यथा अणु
		u8 reg;

		reg = exca_पढ़ोb(socket, I365_INTCTL) & (I365_RING_ENA | I365_INTR_ENA);
		reg |= (state->flags & SS_RESET) ? 0 : I365_PC_RESET;
		reg |= (state->flags & SS_IOCARD) ? I365_PC_IOCARD : 0;
		अगर (state->io_irq != socket->dev->irq) अणु
			reg |= state->io_irq;
			bridge |= CB_BRIDGE_INTR;
		पूर्ण
		exca_ग_लिखोb(socket, I365_INTCTL, reg);

		reg = exca_पढ़ोb(socket, I365_POWER) & (I365_VCC_MASK|I365_VPP1_MASK);
		reg |= I365_PWR_NORESET;
		अगर (state->flags & SS_PWR_AUTO)
			reg |= I365_PWR_AUTO;
		अगर (state->flags & SS_OUTPUT_ENA)
			reg |= I365_PWR_OUT;
		अगर (exca_पढ़ोb(socket, I365_POWER) != reg)
			exca_ग_लिखोb(socket, I365_POWER, reg);

		/* CSC पूर्णांकerrupt: no ISA irq क्रम CSC */
		reg = exca_पढ़ोb(socket, I365_CSCINT);
		reg &= I365_CSC_IRQ_MASK;
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
		exca_ग_लिखोb(socket, I365_CSCINT, reg);
		exca_पढ़ोb(socket, I365_CSC);
		अगर (sock->zoom_video)
			sock->zoom_video(sock, state->flags & SS_ZVCARD);
	पूर्ण
	config_ग_लिखोw(socket, CB_BRIDGE_CONTROL, bridge);
	/* Socket event mask: get card insert/हटाओ events.. */
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, CB_CDMASK);

	/* अगर घातering up: करो it as the last step when the socket is configured */
	अगर (state->Vcc != 0)
		yenta_set_घातer(socket, state);
	वापस 0;
पूर्ण

अटल पूर्णांक yenta_set_io_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_io_map *io)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	पूर्णांक map;
	अचिन्हित अक्षर ioctl, addr, enable;

	map = io->map;

	अगर (map > 1)
		वापस -EINVAL;

	enable = I365_ENA_IO(map);
	addr = exca_पढ़ोb(socket, I365_ADDRWIN);

	/* Disable the winकरोw beक्रमe changing it.. */
	अगर (addr & enable) अणु
		addr &= ~enable;
		exca_ग_लिखोb(socket, I365_ADDRWIN, addr);
	पूर्ण

	exca_ग_लिखोw(socket, I365_IO(map)+I365_W_START, io->start);
	exca_ग_लिखोw(socket, I365_IO(map)+I365_W_STOP, io->stop);

	ioctl = exca_पढ़ोb(socket, I365_IOCTL) & ~I365_IOCTL_MASK(map);
	अगर (io->flags & MAP_0WS)
		ioctl |= I365_IOCTL_0WS(map);
	अगर (io->flags & MAP_16BIT)
		ioctl |= I365_IOCTL_16BIT(map);
	अगर (io->flags & MAP_AUTOSZ)
		ioctl |= I365_IOCTL_IOCS16(map);
	exca_ग_लिखोb(socket, I365_IOCTL, ioctl);

	अगर (io->flags & MAP_ACTIVE)
		exca_ग_लिखोb(socket, I365_ADDRWIN, addr | enable);
	वापस 0;
पूर्ण

अटल पूर्णांक yenta_set_mem_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_mem_map *mem)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);
	काष्ठा pci_bus_region region;
	पूर्णांक map;
	अचिन्हित अक्षर addr, enable;
	अचिन्हित पूर्णांक start, stop, card_start;
	अचिन्हित लघु word;

	pcibios_resource_to_bus(socket->dev->bus, &region, mem->res);

	map = mem->map;
	start = region.start;
	stop = region.end;
	card_start = mem->card_start;

	अगर (map > 4 || start > stop || ((start ^ stop) >> 24) ||
	    (card_start >> 26) || mem->speed > 1000)
		वापस -EINVAL;

	enable = I365_ENA_MEM(map);
	addr = exca_पढ़ोb(socket, I365_ADDRWIN);
	अगर (addr & enable) अणु
		addr &= ~enable;
		exca_ग_लिखोb(socket, I365_ADDRWIN, addr);
	पूर्ण

	exca_ग_लिखोb(socket, CB_MEM_PAGE(map), start >> 24);

	word = (start >> 12) & 0x0fff;
	अगर (mem->flags & MAP_16BIT)
		word |= I365_MEM_16BIT;
	अगर (mem->flags & MAP_0WS)
		word |= I365_MEM_0WS;
	exca_ग_लिखोw(socket, I365_MEM(map) + I365_W_START, word);

	word = (stop >> 12) & 0x0fff;
	चयन (to_cycles(mem->speed)) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		word |= I365_MEM_WS0;
		अवरोध;
	हाल 2:
		word |= I365_MEM_WS1;
		अवरोध;
	शेष:
		word |= I365_MEM_WS1 | I365_MEM_WS0;
		अवरोध;
	पूर्ण
	exca_ग_लिखोw(socket, I365_MEM(map) + I365_W_STOP, word);

	word = ((card_start - start) >> 12) & 0x3fff;
	अगर (mem->flags & MAP_WRPROT)
		word |= I365_MEM_WRPROT;
	अगर (mem->flags & MAP_ATTRIB)
		word |= I365_MEM_REG;
	exca_ग_लिखोw(socket, I365_MEM(map) + I365_W_OFF, word);

	अगर (mem->flags & MAP_ACTIVE)
		exca_ग_लिखोb(socket, I365_ADDRWIN, addr | enable);
	वापस 0;
पूर्ण



अटल irqवापस_t yenta_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक events;
	काष्ठा yenta_socket *socket = (काष्ठा yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;

	/* Clear पूर्णांकerrupt status क्रम the event */
	cb_event = cb_पढ़ोl(socket, CB_SOCKET_EVENT);
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, cb_event);

	csc = exca_पढ़ोb(socket, I365_CSC);

	अगर (!(cb_event || csc))
		वापस IRQ_NONE;

	events = (cb_event & (CB_CD1EVENT | CB_CD2EVENT)) ? SS_DETECT : 0 ;
	events |= (csc & I365_CSC_DETECT) ? SS_DETECT : 0;
	अगर (exca_पढ़ोb(socket, I365_INTCTL) & I365_PC_IOCARD) अणु
		events |= (csc & I365_CSC_STSCHG) ? SS_STSCHG : 0;
	पूर्ण अन्यथा अणु
		events |= (csc & I365_CSC_BVD1) ? SS_BATDEAD : 0;
		events |= (csc & I365_CSC_BVD2) ? SS_BATWARN : 0;
		events |= (csc & I365_CSC_READY) ? SS_READY : 0;
	पूर्ण

	अगर (events)
		pcmcia_parse_events(&socket->socket, events);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम yenta_पूर्णांकerrupt_wrapper(काष्ठा समयr_list *t)
अणु
	काष्ठा yenta_socket *socket = from_समयr(socket, t, poll_समयr);

	yenta_पूर्णांकerrupt(0, (व्योम *)socket);
	socket->poll_समयr.expires = jअगरfies + HZ;
	add_समयr(&socket->poll_समयr);
पूर्ण

अटल व्योम yenta_clear_maps(काष्ठा yenta_socket *socket)
अणु
	पूर्णांक i;
	काष्ठा resource res = अणु .start = 0, .end = 0x0fff पूर्ण;
	pccard_io_map io = अणु 0, 0, 0, 0, 1 पूर्ण;
	pccard_mem_map mem = अणु .res = &res, पूर्ण;

	yenta_set_socket(&socket->socket, &dead_socket);
	क्रम (i = 0; i < 2; i++) अणु
		io.map = i;
		yenta_set_io_map(&socket->socket, &io);
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		mem.map = i;
		yenta_set_mem_map(&socket->socket, &mem);
	पूर्ण
पूर्ण

/* reकरोes voltage पूर्णांकerrogation अगर required */
अटल व्योम yenta_पूर्णांकerrogate(काष्ठा yenta_socket *socket)
अणु
	u32 state;

	state = cb_पढ़ोl(socket, CB_SOCKET_STATE);
	अगर (!(state & (CB_5VCARD | CB_3VCARD | CB_XVCARD | CB_YVCARD)) ||
	    (state & (CB_CDETECT1 | CB_CDETECT2 | CB_NOTACARD | CB_BADVCCREQ)) ||
	    ((state & (CB_16BITCARD | CB_CBCARD)) == (CB_16BITCARD | CB_CBCARD)))
		cb_ग_लिखोl(socket, CB_SOCKET_FORCE, CB_CVSTEST);
पूर्ण

/* Called at resume and initialization events */
अटल पूर्णांक yenta_sock_init(काष्ठा pcmcia_socket *sock)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);

	exca_ग_लिखोb(socket, I365_GBLCTL, 0x00);
	exca_ग_लिखोb(socket, I365_GENCTL, 0x00);

	/* Reकरो card voltage पूर्णांकerrogation */
	yenta_पूर्णांकerrogate(socket);

	yenta_clear_maps(socket);

	अगर (socket->type && socket->type->sock_init)
		socket->type->sock_init(socket);

	/* Re-enable CSC पूर्णांकerrupts */
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, CB_CDMASK);

	वापस 0;
पूर्ण

अटल पूर्णांक yenta_sock_suspend(काष्ठा pcmcia_socket *sock)
अणु
	काष्ठा yenta_socket *socket = container_of(sock, काष्ठा yenta_socket, socket);

	/* Disable CSC पूर्णांकerrupts */
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, 0x0);

	वापस 0;
पूर्ण

/*
 * Use an adaptive allocation क्रम the memory resource,
 * someबार the memory behind pci bridges is limited:
 * 1/8 of the size of the io winकरोw of the parent.
 * max 4 MB, min 16 kB. We try very hard to not get below
 * the "ACC" values, though.
 */
#घोषणा BRIDGE_MEM_MAX (4*1024*1024)
#घोषणा BRIDGE_MEM_ACC (128*1024)
#घोषणा BRIDGE_MEM_MIN (16*1024)

#घोषणा BRIDGE_IO_MAX 512
#घोषणा BRIDGE_IO_ACC 256
#घोषणा BRIDGE_IO_MIN 32

#अगर_अघोषित PCIBIOS_MIN_CARDBUS_IO
#घोषणा PCIBIOS_MIN_CARDBUS_IO PCIBIOS_MIN_IO
#पूर्ण_अगर

अटल पूर्णांक yenta_search_one_res(काष्ठा resource *root, काष्ठा resource *res,
				u32 min)
अणु
	u32 align, size, start, end;

	अगर (res->flags & IORESOURCE_IO) अणु
		align = 1024;
		size = BRIDGE_IO_MAX;
		start = PCIBIOS_MIN_CARDBUS_IO;
		end = ~0U;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ avail = root->end - root->start;
		पूर्णांक i;
		size = BRIDGE_MEM_MAX;
		अगर (size > avail/8) अणु
			size = (avail+1)/8;
			/* round size करोwn to next घातer of 2 */
			i = 0;
			जबतक ((size /= 2) != 0)
				i++;
			size = 1 << i;
		पूर्ण
		अगर (size < min)
			size = min;
		align = size;
		start = PCIBIOS_MIN_MEM;
		end = ~0U;
	पूर्ण

	करो अणु
		अगर (allocate_resource(root, res, size, start, end, align,
				      शून्य, शून्य) == 0) अणु
			वापस 1;
		पूर्ण
		size = size/2;
		align = size;
	पूर्ण जबतक (size >= min);

	वापस 0;
पूर्ण


अटल पूर्णांक yenta_search_res(काष्ठा yenta_socket *socket, काष्ठा resource *res,
			    u32 min)
अणु
	काष्ठा resource *root;
	पूर्णांक i;

	pci_bus_क्रम_each_resource(socket->dev->bus, root, i) अणु
		अगर (!root)
			जारी;

		अगर ((res->flags ^ root->flags) &
		    (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH))
			जारी; /* Wrong type */

		अगर (yenta_search_one_res(root, res, min))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक yenta_allocate_res(काष्ठा yenta_socket *socket, पूर्णांक nr, अचिन्हित type, पूर्णांक addr_start, पूर्णांक addr_end)
अणु
	काष्ठा pci_dev *dev = socket->dev;
	काष्ठा resource *res;
	काष्ठा pci_bus_region region;
	अचिन्हित mask;

	res = &dev->resource[nr];
	/* Alपढ़ोy allocated? */
	अगर (res->parent)
		वापस 0;

	/* The granularity of the memory limit is 4kB, on IO it's 4 bytes */
	mask = ~0xfff;
	अगर (type & IORESOURCE_IO)
		mask = ~3;

	res->name = dev->subordinate->name;
	res->flags = type;

	region.start = config_पढ़ोl(socket, addr_start) & mask;
	region.end = config_पढ़ोl(socket, addr_end) | ~mask;
	अगर (region.start && region.end > region.start && !override_bios) अणु
		pcibios_bus_to_resource(dev->bus, res, &region);
		अगर (pci_claim_resource(dev, nr) == 0)
			वापस 0;
		dev_info(&dev->dev,
			 "Preassigned resource %d busy or not available, reconfiguring...\n",
			 nr);
	पूर्ण

	अगर (type & IORESOURCE_IO) अणु
		अगर ((yenta_search_res(socket, res, BRIDGE_IO_MAX)) ||
		    (yenta_search_res(socket, res, BRIDGE_IO_ACC)) ||
		    (yenta_search_res(socket, res, BRIDGE_IO_MIN)))
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (type & IORESOURCE_PREFETCH) अणु
			अगर ((yenta_search_res(socket, res, BRIDGE_MEM_MAX)) ||
			    (yenta_search_res(socket, res, BRIDGE_MEM_ACC)) ||
			    (yenta_search_res(socket, res, BRIDGE_MEM_MIN)))
				वापस 1;
			/* Approximating prefetchable by non-prefetchable */
			res->flags = IORESOURCE_MEM;
		पूर्ण
		अगर ((yenta_search_res(socket, res, BRIDGE_MEM_MAX)) ||
		    (yenta_search_res(socket, res, BRIDGE_MEM_ACC)) ||
		    (yenta_search_res(socket, res, BRIDGE_MEM_MIN)))
			वापस 1;
	पूर्ण

	dev_info(&dev->dev,
		 "no resource of type %x available, trying to continue...\n",
		 type);
	res->start = res->end = res->flags = 0;
	वापस 0;
पूर्ण

अटल व्योम yenta_मुक्त_res(काष्ठा yenta_socket *socket, पूर्णांक nr)
अणु
	काष्ठा pci_dev *dev = socket->dev;
	काष्ठा resource *res;

	res = &dev->resource[nr];
	अगर (res->start != 0 && res->end != 0)
		release_resource(res);

	res->start = res->end = res->flags = 0;
पूर्ण

/*
 * Allocate the bridge mappings क्रम the device..
 */
अटल व्योम yenta_allocate_resources(काष्ठा yenta_socket *socket)
अणु
	पूर्णांक program = 0;
	program += yenta_allocate_res(socket, PCI_CB_BRIDGE_IO_0_WINDOW,
			   IORESOURCE_IO,
			   PCI_CB_IO_BASE_0, PCI_CB_IO_LIMIT_0);
	program += yenta_allocate_res(socket, PCI_CB_BRIDGE_IO_1_WINDOW,
			   IORESOURCE_IO,
			   PCI_CB_IO_BASE_1, PCI_CB_IO_LIMIT_1);
	program += yenta_allocate_res(socket, PCI_CB_BRIDGE_MEM_0_WINDOW,
			   IORESOURCE_MEM | IORESOURCE_PREFETCH,
			   PCI_CB_MEMORY_BASE_0, PCI_CB_MEMORY_LIMIT_0);
	program += yenta_allocate_res(socket, PCI_CB_BRIDGE_MEM_1_WINDOW,
			   IORESOURCE_MEM,
			   PCI_CB_MEMORY_BASE_1, PCI_CB_MEMORY_LIMIT_1);
	अगर (program)
		pci_setup_cardbus(socket->dev->subordinate);
पूर्ण


/*
 * Free the bridge mappings क्रम the device..
 */
अटल व्योम yenta_मुक्त_resources(काष्ठा yenta_socket *socket)
अणु
	yenta_मुक्त_res(socket, PCI_CB_BRIDGE_IO_0_WINDOW);
	yenta_मुक्त_res(socket, PCI_CB_BRIDGE_IO_1_WINDOW);
	yenta_मुक्त_res(socket, PCI_CB_BRIDGE_MEM_0_WINDOW);
	yenta_मुक्त_res(socket, PCI_CB_BRIDGE_MEM_1_WINDOW);
पूर्ण


/*
 * Close it करोwn - release our resources and go home..
 */
अटल व्योम yenta_बंद(काष्ठा pci_dev *dev)
अणु
	काष्ठा yenta_socket *sock = pci_get_drvdata(dev);

	/* Remove the रेजिस्टर attributes */
	device_हटाओ_file(&dev->dev, &dev_attr_yenta_रेजिस्टरs);

	/* we करोn't want a dying socket रेजिस्टरed */
	pcmcia_unरेजिस्टर_socket(&sock->socket);

	/* Disable all events so we करोn't die in an IRQ storm */
	cb_ग_लिखोl(sock, CB_SOCKET_MASK, 0x0);
	exca_ग_लिखोb(sock, I365_CSCINT, 0);

	अगर (sock->cb_irq)
		मुक्त_irq(sock->cb_irq, sock);
	अन्यथा
		del_समयr_sync(&sock->poll_समयr);

	iounmap(sock->base);
	yenta_मुक्त_resources(sock);

	pci_release_regions(dev);
	pci_disable_device(dev);
	pci_set_drvdata(dev, शून्य);
	kमुक्त(sock);
पूर्ण


अटल काष्ठा pccard_operations yenta_socket_operations = अणु
	.init			= yenta_sock_init,
	.suspend		= yenta_sock_suspend,
	.get_status		= yenta_get_status,
	.set_socket		= yenta_set_socket,
	.set_io_map		= yenta_set_io_map,
	.set_mem_map		= yenta_set_mem_map,
पूर्ण;


#अगर_घोषित CONFIG_YENTA_TI
#समावेश "ti113x.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_RICOH
#समावेश "ricoh.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_TOSHIBA
#समावेश "topic.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_O2
#समावेश "o2micro.h"
#पूर्ण_अगर

क्रमागत अणु
	CARDBUS_TYPE_DEFAULT = -1,
	CARDBUS_TYPE_TI,
	CARDBUS_TYPE_TI113X,
	CARDBUS_TYPE_TI12XX,
	CARDBUS_TYPE_TI1250,
	CARDBUS_TYPE_RICOH,
	CARDBUS_TYPE_TOPIC95,
	CARDBUS_TYPE_TOPIC97,
	CARDBUS_TYPE_O2MICRO,
	CARDBUS_TYPE_ENE,
पूर्ण;

/*
 * Dअगरferent cardbus controllers have slightly dअगरferent
 * initialization sequences etc details. List them here..
 */
अटल काष्ठा cardbus_type cardbus_type[] = अणु
#अगर_घोषित CONFIG_YENTA_TI
	[CARDBUS_TYPE_TI]	= अणु
		.override	= ti_override,
		.save_state	= ti_save_state,
		.restore_state	= ti_restore_state,
		.sock_init	= ti_init,
	पूर्ण,
	[CARDBUS_TYPE_TI113X]	= अणु
		.override	= ti113x_override,
		.save_state	= ti_save_state,
		.restore_state	= ti_restore_state,
		.sock_init	= ti_init,
	पूर्ण,
	[CARDBUS_TYPE_TI12XX]	= अणु
		.override	= ti12xx_override,
		.save_state	= ti_save_state,
		.restore_state	= ti_restore_state,
		.sock_init	= ti_init,
	पूर्ण,
	[CARDBUS_TYPE_TI1250]	= अणु
		.override	= ti1250_override,
		.save_state	= ti_save_state,
		.restore_state	= ti_restore_state,
		.sock_init	= ti_init,
	पूर्ण,
	[CARDBUS_TYPE_ENE]	= अणु
		.override	= ene_override,
		.save_state	= ti_save_state,
		.restore_state	= ti_restore_state,
		.sock_init	= ti_init,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_RICOH
	[CARDBUS_TYPE_RICOH]	= अणु
		.override	= ricoh_override,
		.save_state	= ricoh_save_state,
		.restore_state	= ricoh_restore_state,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_TOSHIBA
	[CARDBUS_TYPE_TOPIC95]	= अणु
		.override	= topic95_override,
	पूर्ण,
	[CARDBUS_TYPE_TOPIC97]	= अणु
		.override	= topic97_override,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_YENTA_O2
	[CARDBUS_TYPE_O2MICRO]	= अणु
		.override	= o2micro_override,
		.restore_state	= o2micro_restore_state,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;


अटल अचिन्हित पूर्णांक yenta_probe_irq(काष्ठा yenta_socket *socket, u32 isa_irq_mask)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ val;
	u32 mask;
	u8 reg;

	/*
	 * Probe क्रम usable पूर्णांकerrupts using the क्रमce
	 * रेजिस्टर to generate bogus card status events.
	 */
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, CB_CSTSMASK);
	reg = exca_पढ़ोb(socket, I365_CSCINT);
	exca_ग_लिखोb(socket, I365_CSCINT, 0);
	val = probe_irq_on() & isa_irq_mask;
	क्रम (i = 1; i < 16; i++) अणु
		अगर (!((val >> i) & 1))
			जारी;
		exca_ग_लिखोb(socket, I365_CSCINT, I365_CSC_STSCHG | (i << 4));
		cb_ग_लिखोl(socket, CB_SOCKET_FORCE, CB_FCARDSTS);
		udelay(100);
		cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	पूर्ण
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, 0);
	exca_ग_लिखोb(socket, I365_CSCINT, reg);

	mask = probe_irq_mask(val) & 0xffff;

	वापस mask;
पूर्ण


/*
 * yenta PCI irq probing.
 * currently only used in the TI/EnE initialization code
 */
#अगर_घोषित CONFIG_YENTA_TI

/* पूर्णांकerrupt handler, only used during probing */
अटल irqवापस_t yenta_probe_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा yenta_socket *socket = (काष्ठा yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;

	/* Clear पूर्णांकerrupt status क्रम the event */
	cb_event = cb_पढ़ोl(socket, CB_SOCKET_EVENT);
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	csc = exca_पढ़ोb(socket, I365_CSC);

	अगर (cb_event || csc) अणु
		socket->probe_status = 1;
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/* probes the PCI पूर्णांकerrupt, use only on override functions */
अटल पूर्णांक yenta_probe_cb_irq(काष्ठा yenta_socket *socket)
अणु
	u8 reg = 0;

	अगर (!socket->cb_irq)
		वापस -1;

	socket->probe_status = 0;

	अगर (request_irq(socket->cb_irq, yenta_probe_handler, IRQF_SHARED, "yenta", socket)) अणु
		dev_warn(&socket->dev->dev,
			 "request_irq() in yenta_probe_cb_irq() failed!\n");
		वापस -1;
	पूर्ण

	/* generate पूर्णांकerrupt, रुको */
	अगर (!socket->dev->irq)
		reg = exca_पढ़ोb(socket, I365_CSCINT);
	exca_ग_लिखोb(socket, I365_CSCINT, reg | I365_CSC_STSCHG);
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, CB_CSTSMASK);
	cb_ग_लिखोl(socket, CB_SOCKET_FORCE, CB_FCARDSTS);

	msleep(100);

	/* disable पूर्णांकerrupts */
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, 0);
	exca_ग_लिखोb(socket, I365_CSCINT, reg);
	cb_ग_लिखोl(socket, CB_SOCKET_EVENT, -1);
	exca_पढ़ोb(socket, I365_CSC);

	मुक्त_irq(socket->cb_irq, socket);

	वापस (पूर्णांक) socket->probe_status;
पूर्ण

#पूर्ण_अगर /* CONFIG_YENTA_TI */


/*
 * Set अटल data that करोesn't need re-initializing..
 */
अटल व्योम yenta_get_socket_capabilities(काष्ठा yenta_socket *socket, u32 isa_irq_mask)
अणु
	socket->socket.pci_irq = socket->cb_irq;
	अगर (isa_probe)
		socket->socket.irq_mask = yenta_probe_irq(socket, isa_irq_mask);
	अन्यथा
		socket->socket.irq_mask = 0;

	dev_info(&socket->dev->dev, "ISA IRQ mask 0x%04x, PCI irq %d\n",
		 socket->socket.irq_mask, socket->cb_irq);
पूर्ण

/*
 * Initialize the standard cardbus रेजिस्टरs
 */
अटल व्योम yenta_config_init(काष्ठा yenta_socket *socket)
अणु
	u16 bridge;
	काष्ठा pci_dev *dev = socket->dev;
	काष्ठा pci_bus_region region;

	pcibios_resource_to_bus(socket->dev->bus, &region, &dev->resource[0]);

	config_ग_लिखोl(socket, CB_LEGACY_MODE_BASE, 0);
	config_ग_लिखोl(socket, PCI_BASE_ADDRESS_0, region.start);
	config_ग_लिखोw(socket, PCI_COMMAND,
			PCI_COMMAND_IO |
			PCI_COMMAND_MEMORY |
			PCI_COMMAND_MASTER |
			PCI_COMMAND_WAIT);

	/* MAGIC NUMBERS! Fixme */
	config_ग_लिखोb(socket, PCI_CACHE_LINE_SIZE, L1_CACHE_BYTES / 4);
	config_ग_लिखोb(socket, PCI_LATENCY_TIMER, 168);
	config_ग_लिखोl(socket, PCI_PRIMARY_BUS,
		(176 << 24) |			   /* sec. latency समयr */
		((अचिन्हित पूर्णांक)dev->subordinate->busn_res.end << 16) | /* subordinate bus */
		((अचिन्हित पूर्णांक)dev->subordinate->busn_res.start << 8) |  /* secondary bus */
		dev->subordinate->primary);		   /* primary bus */

	/*
	 * Set up the bridging state:
	 *  - enable ग_लिखो posting.
	 *  - memory winकरोw 0 prefetchable, winकरोw 1 non-prefetchable
	 *  - PCI पूर्णांकerrupts enabled अगर a PCI पूर्णांकerrupt exists..
	 */
	bridge = config_पढ़ोw(socket, CB_BRIDGE_CONTROL);
	bridge &= ~(CB_BRIDGE_CRST | CB_BRIDGE_PREFETCH1 | CB_BRIDGE_ISAEN | CB_BRIDGE_VGAEN);
	bridge |= CB_BRIDGE_PREFETCH0 | CB_BRIDGE_POSTEN;
	config_ग_लिखोw(socket, CB_BRIDGE_CONTROL, bridge);
पूर्ण

/**
 * yenta_fixup_parent_bridge - Fix subordinate bus# of the parent bridge
 * @cardbus_bridge: The PCI bus which the CardBus bridge bridges to
 *
 * Checks अगर devices on the bus which the CardBus bridge bridges to would be
 * invisible during PCI scans because of a misconfigured subordinate number
 * of the parent brige - some BIOSes seem to be too lazy to set it right.
 * Does the fixup carefully by checking how far it can go without conflicts.
 * See http://bugzilla.kernel.org/show_bug.cgi?id=2944 क्रम more inक्रमmation.
 */
अटल व्योम yenta_fixup_parent_bridge(काष्ठा pci_bus *cardbus_bridge)
अणु
	काष्ठा pci_bus *sibling;
	अचिन्हित अक्षर upper_limit;
	/*
	 * We only check and fix the parent bridge: All प्रणालीs which need
	 * this fixup that have been reviewed are laptops and the only bridge
	 * which needed fixing was the parent bridge of the CardBus bridge:
	 */
	काष्ठा pci_bus *bridge_to_fix = cardbus_bridge->parent;

	/* Check bus numbers are alपढ़ोy set up correctly: */
	अगर (bridge_to_fix->busn_res.end >= cardbus_bridge->busn_res.end)
		वापस; /* The subordinate number is ok, nothing to करो */

	अगर (!bridge_to_fix->parent)
		वापस; /* Root bridges are ok */

	/* stay within the limits of the bus range of the parent: */
	upper_limit = bridge_to_fix->parent->busn_res.end;

	/* check the bus ranges of all sibling bridges to prevent overlap */
	list_क्रम_each_entry(sibling, &bridge_to_fix->parent->children,
			node) अणु
		/*
		 * If the sibling has a higher secondary bus number
		 * and it's secondary is equal or smaller than our
		 * current upper limit, set the new upper limit to
		 * the bus number below the sibling's range:
		 */
		अगर (sibling->busn_res.start > bridge_to_fix->busn_res.end
		    && sibling->busn_res.start <= upper_limit)
			upper_limit = sibling->busn_res.start - 1;
	पूर्ण

	/* Show that the wanted subordinate number is not possible: */
	अगर (cardbus_bridge->busn_res.end > upper_limit)
		dev_warn(&cardbus_bridge->dev,
			 "Upper limit for fixing this bridge's parent bridge: #%02x\n",
			 upper_limit);

	/* If we have room to increase the bridge's subordinate number, */
	अगर (bridge_to_fix->busn_res.end < upper_limit) अणु

		/* use the highest number of the hidden bus, within limits */
		अचिन्हित अक्षर subordinate_to_assign =
			min_t(पूर्णांक, cardbus_bridge->busn_res.end, upper_limit);

		dev_info(&bridge_to_fix->dev,
			 "Raising subordinate bus# of parent bus (#%02x) from #%02x to #%02x\n",
			 bridge_to_fix->number,
			 (पूर्णांक)bridge_to_fix->busn_res.end,
			 subordinate_to_assign);

		/* Save the new subordinate in the bus काष्ठा of the bridge */
		bridge_to_fix->busn_res.end = subordinate_to_assign;

		/* and update the PCI config space with the new subordinate */
		pci_ग_लिखो_config_byte(bridge_to_fix->self,
			PCI_SUBORDINATE_BUS, bridge_to_fix->busn_res.end);
	पूर्ण
पूर्ण

/*
 * Initialize a cardbus controller. Make sure we have a usable
 * पूर्णांकerrupt, and that we can map the cardbus area. Fill in the
 * socket inक्रमmation काष्ठाure..
 */
अटल पूर्णांक yenta_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा yenta_socket *socket;
	पूर्णांक ret;

	/*
	 * If we failed to assign proper bus numbers क्रम this cardbus
	 * controller during PCI probe, its subordinate pci_bus is शून्य.
	 * Bail out अगर so.
	 */
	अगर (!dev->subordinate) अणु
		dev_err(&dev->dev, "no bus associated! (try 'pci=assign-busses')\n");
		वापस -ENODEV;
	पूर्ण

	socket = kzalloc(माप(काष्ठा yenta_socket), GFP_KERNEL);
	अगर (!socket)
		वापस -ENOMEM;

	/* prepare pcmcia_socket */
	socket->socket.ops = &yenta_socket_operations;
	socket->socket.resource_ops = &pccard_nonअटल_ops;
	socket->socket.dev.parent = &dev->dev;
	socket->socket.driver_data = socket;
	socket->socket.owner = THIS_MODULE;
	socket->socket.features = SS_CAP_PAGE_REGS | SS_CAP_PCCARD;
	socket->socket.map_size = 0x1000;
	socket->socket.cb_dev = dev;

	/* prepare काष्ठा yenta_socket */
	socket->dev = dev;
	pci_set_drvdata(dev, socket);

	/*
	 * Do some basic sanity checking..
	 */
	अगर (pci_enable_device(dev)) अणु
		ret = -EBUSY;
		जाओ मुक्त;
	पूर्ण

	ret = pci_request_regions(dev, "yenta_socket");
	अगर (ret)
		जाओ disable;

	अगर (!pci_resource_start(dev, 0)) अणु
		dev_err(&dev->dev, "No cardbus resource!\n");
		ret = -ENODEV;
		जाओ release;
	पूर्ण

	/*
	 * Ok, start setup.. Map the cardbus रेजिस्टरs,
	 * and request the IRQ.
	 */
	socket->base = ioremap(pci_resource_start(dev, 0), 0x1000);
	अगर (!socket->base) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	/*
	 * report the subप्रणाली venकरोr and device क्रम help debugging
	 * the irq stuff...
	 */
	dev_info(&dev->dev, "CardBus bridge found [%04x:%04x]\n",
		 dev->subप्रणाली_venकरोr, dev->subप्रणाली_device);

	yenta_config_init(socket);

	/* Disable all events */
	cb_ग_लिखोl(socket, CB_SOCKET_MASK, 0x0);

	/* Set up the bridge regions.. */
	yenta_allocate_resources(socket);

	socket->cb_irq = dev->irq;

	/* Do we have special options क्रम the device? */
	अगर (id->driver_data != CARDBUS_TYPE_DEFAULT &&
	    id->driver_data < ARRAY_SIZE(cardbus_type)) अणु
		socket->type = &cardbus_type[id->driver_data];

		ret = socket->type->override(socket);
		अगर (ret < 0)
			जाओ unmap;
	पूर्ण

	/* We must finish initialization here */

	अगर (!socket->cb_irq || request_irq(socket->cb_irq, yenta_पूर्णांकerrupt, IRQF_SHARED, "yenta", socket)) अणु
		/* No IRQ or request_irq failed. Poll */
		socket->cb_irq = 0; /* But zero is a valid IRQ number. */
		समयr_setup(&socket->poll_समयr, yenta_पूर्णांकerrupt_wrapper, 0);
		mod_समयr(&socket->poll_समयr, jअगरfies + HZ);
		dev_info(&dev->dev,
			 "no PCI IRQ, CardBus support disabled for this socket.\n");
		dev_info(&dev->dev,
			 "check your BIOS CardBus, BIOS IRQ or ACPI settings.\n");
	पूर्ण अन्यथा अणु
		socket->socket.features |= SS_CAP_CARDBUS;
	पूर्ण

	/* Figure out what the dang thing can करो क्रम the PCMCIA layer... */
	yenta_पूर्णांकerrogate(socket);
	yenta_get_socket_capabilities(socket, isa_पूर्णांकerrupts);
	dev_info(&dev->dev, "Socket status: %08x\n",
		 cb_पढ़ोl(socket, CB_SOCKET_STATE));

	yenta_fixup_parent_bridge(dev->subordinate);

	/* Register it with the pcmcia layer.. */
	ret = pcmcia_रेजिस्टर_socket(&socket->socket);
	अगर (ret)
		जाओ मुक्त_irq;

	/* Add the yenta रेजिस्टर attributes */
	ret = device_create_file(&dev->dev, &dev_attr_yenta_रेजिस्टरs);
	अगर (ret)
		जाओ unरेजिस्टर_socket;

	वापस ret;

	/* error path... */
 unरेजिस्टर_socket:
	pcmcia_unरेजिस्टर_socket(&socket->socket);
 मुक्त_irq:
	अगर (socket->cb_irq)
		मुक्त_irq(socket->cb_irq, socket);
	अन्यथा
		del_समयr_sync(&socket->poll_समयr);
 unmap:
	iounmap(socket->base);
	yenta_मुक्त_resources(socket);
 release:
	pci_release_regions(dev);
 disable:
	pci_disable_device(dev);
 मुक्त:
	pci_set_drvdata(dev, शून्य);
	kमुक्त(socket);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक yenta_dev_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा yenta_socket *socket = pci_get_drvdata(pdev);

	अगर (!socket)
		वापस 0;

	अगर (socket->type && socket->type->save_state)
		socket->type->save_state(socket);

	pci_save_state(pdev);
	pci_पढ़ो_config_dword(pdev, 16*4, &socket->saved_state[0]);
	pci_पढ़ो_config_dword(pdev, 17*4, &socket->saved_state[1]);
	pci_disable_device(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक yenta_dev_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा yenta_socket *socket = pci_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!socket)
		वापस 0;

	pci_ग_लिखो_config_dword(pdev, 16*4, socket->saved_state[0]);
	pci_ग_लिखो_config_dword(pdev, 17*4, socket->saved_state[1]);

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	अगर (socket->type && socket->type->restore_state)
		socket->type->restore_state(socket);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops yenta_pm_ops = अणु
	.suspend_noirq = yenta_dev_suspend_noirq,
	.resume_noirq = yenta_dev_resume_noirq,
	.मुक्तze_noirq = yenta_dev_suspend_noirq,
	.thaw_noirq = yenta_dev_resume_noirq,
	.घातeroff_noirq = yenta_dev_suspend_noirq,
	.restore_noirq = yenta_dev_resume_noirq,
पूर्ण;

#घोषणा YENTA_PM_OPS	(&yenta_pm_ops)
#अन्यथा
#घोषणा YENTA_PM_OPS	शून्य
#पूर्ण_अगर

#घोषणा CB_ID(vend, dev, type)				\
	अणु						\
		.venकरोr		= vend,			\
		.device		= dev,			\
		.subvenकरोr	= PCI_ANY_ID,		\
		.subdevice	= PCI_ANY_ID,		\
		.class		= PCI_CLASS_BRIDGE_CARDBUS << 8, \
		.class_mask	= ~0,			\
		.driver_data	= CARDBUS_TYPE_##type,	\
	पूर्ण

अटल स्थिर काष्ठा pci_device_id yenta_table[] = अणु
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1031, TI),

	/*
	 * TBD: Check अगर these TI variants can use more
	 * advanced overrides instead.  (I can't get the
	 * data sheets क्रम these devices. --rmk)
	 */
#अगर_घोषित CONFIG_YENTA_TI
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1210, TI),

	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1130, TI113X),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1131, TI113X),

	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1211, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1220, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1221, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1225, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1251A, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1251B, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1420, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1450, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1451A, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1510, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1520, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1620, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_4410, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_4450, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_4451, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_4510, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_4520, TI12XX),

	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1250, TI1250),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1410, TI1250),

	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XX21_XX11, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_X515, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XX12, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_X420, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_X620, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_7410, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_7510, TI12XX),
	CB_ID(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_7610, TI12XX),

	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_710, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_712, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_720, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_722, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_1211, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_1225, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_1410, ENE),
	CB_ID(PCI_VENDOR_ID_ENE, PCI_DEVICE_ID_ENE_1420, ENE),
#पूर्ण_अगर /* CONFIG_YENTA_TI */

#अगर_घोषित CONFIG_YENTA_RICOH
	CB_ID(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C465, RICOH),
	CB_ID(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C466, RICOH),
	CB_ID(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C475, RICOH),
	CB_ID(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C476, RICOH),
	CB_ID(PCI_VENDOR_ID_RICOH, PCI_DEVICE_ID_RICOH_RL5C478, RICOH),
#पूर्ण_अगर

#अगर_घोषित CONFIG_YENTA_TOSHIBA
	CB_ID(PCI_VENDOR_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC95, TOPIC95),
	CB_ID(PCI_VENDOR_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC97, TOPIC97),
	CB_ID(PCI_VENDOR_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC100, TOPIC97),
#पूर्ण_अगर

#अगर_घोषित CONFIG_YENTA_O2
	CB_ID(PCI_VENDOR_ID_O2, PCI_ANY_ID, O2MICRO),
#पूर्ण_अगर

	/* match any cardbus bridge */
	CB_ID(PCI_ANY_ID, PCI_ANY_ID, DEFAULT),
	अणु /* all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, yenta_table);


अटल काष्ठा pci_driver yenta_cardbus_driver = अणु
	.name		= "yenta_cardbus",
	.id_table	= yenta_table,
	.probe		= yenta_probe,
	.हटाओ		= yenta_बंद,
	.driver.pm	= YENTA_PM_OPS,
पूर्ण;

module_pci_driver(yenta_cardbus_driver);

MODULE_LICENSE("GPL");
