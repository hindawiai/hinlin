<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vrc4171_card.c, NEC VRC4171 Card Controller driver क्रम Socket Services.
 *
 * Copyright (C) 2003-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/ss.h>

#समावेश "i82365.h"

MODULE_DESCRIPTION("NEC VRC4171 Card Controllers driver for Socket Services");
MODULE_AUTHOR("Yoichi Yuasa <yuasa@linux-mips.org>");
MODULE_LICENSE("GPL");

#घोषणा CARD_MAX_SLOTS		2
#घोषणा CARD_SLOTA		0
#घोषणा CARD_SLOTB		1
#घोषणा CARD_SLOTB_OFFSET	0x40

#घोषणा CARD_MEM_START		0x10000000
#घोषणा CARD_MEM_END		0x13ffffff
#घोषणा CARD_MAX_MEM_OFFSET	0x3ffffff
#घोषणा CARD_MAX_MEM_SPEED	1000

#घोषणा CARD_CONTROLLER_INDEX	0x03e0
#घोषणा CARD_CONTROLLER_DATA	0x03e1
 /* Power रेजिस्टर */
  #घोषणा VPP_GET_VCC		0x01
  #घोषणा POWER_ENABLE		0x10
 #घोषणा CARD_VOLTAGE_SENSE	0x1f
  #घोषणा VCC_3VORXV_CAPABLE	0x00
  #घोषणा VCC_XV_ONLY		0x01
  #घोषणा VCC_3V_CAPABLE	0x02
  #घोषणा VCC_5V_ONLY		0x03
 #घोषणा CARD_VOLTAGE_SELECT	0x2f
  #घोषणा VCC_3V		0x01
  #घोषणा VCC_5V		0x00
  #घोषणा VCC_XV		0x02
  #घोषणा VCC_STATUS_3V		0x02
  #घोषणा VCC_STATUS_5V		0x01
  #घोषणा VCC_STATUS_XV		0x03
 #घोषणा GLOBAL_CONTROL		0x1e
  #घोषणा EXWRBK		0x04
  #घोषणा IRQPM_EN		0x08
  #घोषणा CLRPMIRQ		0x10

#घोषणा INTERRUPT_STATUS	0x05fa
 #घोषणा IRQ_A			0x02
 #घोषणा IRQ_B			0x04

#घोषणा CONFIGURATION1		0x05fe
 #घोषणा SLOTB_CONFIG		0xc000
 #घोषणा SLOTB_NONE		0x0000
 #घोषणा SLOTB_PCCARD		0x4000
 #घोषणा SLOTB_CF		0x8000
 #घोषणा SLOTB_FLASHROM		0xc000

#घोषणा CARD_CONTROLLER_START	CARD_CONTROLLER_INDEX
#घोषणा CARD_CONTROLLER_END	CARD_CONTROLLER_DATA

#घोषणा IO_MAX_MAPS	2
#घोषणा MEM_MAX_MAPS	5

क्रमागत vrc4171_slot अणु
	SLOT_PROBE = 0,
	SLOT_NOPROBE_IO,
	SLOT_NOPROBE_MEM,
	SLOT_NOPROBE_ALL,
	SLOT_INITIALIZED,
पूर्ण;

क्रमागत vrc4171_slotb अणु
	SLOTB_IS_NONE,
	SLOTB_IS_PCCARD,
	SLOTB_IS_CF,
	SLOTB_IS_FLASHROM,
पूर्ण;

काष्ठा vrc4171_socket अणु
	क्रमागत vrc4171_slot slot;
	काष्ठा pcmcia_socket pcmcia_socket;
	अक्षर name[24];
	पूर्णांक csc_irq;
	पूर्णांक io_irq;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा vrc4171_socket vrc4171_sockets[CARD_MAX_SLOTS];
अटल क्रमागत vrc4171_slotb vrc4171_slotb = SLOTB_IS_NONE;
अटल अक्षर vrc4171_card_name[] = "NEC VRC4171 Card Controller";
अटल अचिन्हित पूर्णांक vrc4171_irq;
अटल uपूर्णांक16_t vrc4171_irq_mask = 0xdeb8;

अटल काष्ठा resource vrc4171_card_resource[3] = अणु
	अणु	.name		= vrc4171_card_name,
		.start		= CARD_CONTROLLER_START,
		.end		= CARD_CONTROLLER_END,
		.flags		= IORESOURCE_IO,	पूर्ण,
	अणु	.name		= vrc4171_card_name,
		.start		= INTERRUPT_STATUS,
		.end		= INTERRUPT_STATUS,
		.flags		= IORESOURCE_IO,	पूर्ण,
	अणु	.name		= vrc4171_card_name,
		.start		= CONFIGURATION1,
		.end		= CONFIGURATION1,
		.flags		= IORESOURCE_IO,	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vrc4171_card_device = अणु
	.name		= vrc4171_card_name,
	.id		= 0,
	.num_resources	= 3,
	.resource	= vrc4171_card_resource,
पूर्ण;

अटल अंतरभूत uपूर्णांक16_t vrc4171_get_irq_status(व्योम)
अणु
	वापस inw(INTERRUPT_STATUS);
पूर्ण

अटल अंतरभूत व्योम vrc4171_set_multअगरunction_pin(क्रमागत vrc4171_slotb config)
अणु
	uपूर्णांक16_t config1;

	config1 = inw(CONFIGURATION1);
	config1 &= ~SLOTB_CONFIG;

	चयन (config) अणु
	हाल SLOTB_IS_NONE:
		config1 |= SLOTB_NONE;
		अवरोध;
	हाल SLOTB_IS_PCCARD:
		config1 |= SLOTB_PCCARD;
		अवरोध;
	हाल SLOTB_IS_CF:
		config1 |= SLOTB_CF;
		अवरोध;
	हाल SLOTB_IS_FLASHROM:
		config1 |= SLOTB_FLASHROM;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	outw(config1, CONFIGURATION1);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t exca_पढ़ो_byte(पूर्णांक slot, uपूर्णांक8_t index)
अणु
	अगर (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index, CARD_CONTROLLER_INDEX);
	वापस inb(CARD_CONTROLLER_DATA);
पूर्ण

अटल अंतरभूत uपूर्णांक16_t exca_पढ़ो_word(पूर्णांक slot, uपूर्णांक8_t index)
अणु
	uपूर्णांक16_t data;

	अगर (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index++, CARD_CONTROLLER_INDEX);
	data = inb(CARD_CONTROLLER_DATA);

	outb(index, CARD_CONTROLLER_INDEX);
	data |= ((uपूर्णांक16_t)inb(CARD_CONTROLLER_DATA)) << 8;

	वापस data;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t exca_ग_लिखो_byte(पूर्णांक slot, uपूर्णांक8_t index, uपूर्णांक8_t data)
अणु
	अगर (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index, CARD_CONTROLLER_INDEX);
	outb(data, CARD_CONTROLLER_DATA);

	वापस data;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t exca_ग_लिखो_word(पूर्णांक slot, uपूर्णांक8_t index, uपूर्णांक16_t data)
अणु
	अगर (slot == CARD_SLOTB)
		index += CARD_SLOTB_OFFSET;

	outb(index++, CARD_CONTROLLER_INDEX);
	outb(data, CARD_CONTROLLER_DATA);

	outb(index, CARD_CONTROLLER_INDEX);
	outb((uपूर्णांक8_t)(data >> 8), CARD_CONTROLLER_DATA);

	वापस data;
पूर्ण

अटल अंतरभूत पूर्णांक search_nonuse_irq(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (vrc4171_irq_mask & (1 << i)) अणु
			vrc4171_irq_mask &= ~(1 << i);
			वापस i;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक pccard_init(काष्ठा pcmcia_socket *sock)
अणु
	काष्ठा vrc4171_socket *socket;
	अचिन्हित पूर्णांक slot;

	sock->features |= SS_CAP_PCCARD | SS_CAP_PAGE_REGS;
	sock->irq_mask = 0;
	sock->map_size = 0x1000;
	sock->pci_irq = vrc4171_irq;

	slot = sock->sock;
	socket = &vrc4171_sockets[slot];
	socket->csc_irq = search_nonuse_irq();
	socket->io_irq = search_nonuse_irq();
	spin_lock_init(&socket->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pccard_get_status(काष्ठा pcmcia_socket *sock, u_पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक slot;
	uपूर्णांक8_t status, sense;
	u_पूर्णांक val = 0;

	अगर (sock == शून्य || sock->sock >= CARD_MAX_SLOTS || value == शून्य)
		वापस -EINVAL;

	slot = sock->sock;

	status = exca_पढ़ो_byte(slot, I365_STATUS);
	अगर (exca_पढ़ो_byte(slot, I365_INTCTL) & I365_PC_IOCARD) अणु
		अगर (status & I365_CS_STSCHG)
			val |= SS_STSCHG;
	पूर्ण अन्यथा अणु
		अगर (!(status & I365_CS_BVD1))
			val |= SS_BATDEAD;
		अन्यथा अगर ((status & (I365_CS_BVD1 | I365_CS_BVD2)) == I365_CS_BVD1)
			val |= SS_BATWARN;
	पूर्ण
	अगर ((status & I365_CS_DETECT) == I365_CS_DETECT)
		val |= SS_DETECT;
	अगर (status & I365_CS_WRPROT)
		val |= SS_WRPROT;
	अगर (status & I365_CS_READY)
		val |= SS_READY;
	अगर (status & I365_CS_POWERON)
		val |= SS_POWERON;

	sense = exca_पढ़ो_byte(slot, CARD_VOLTAGE_SENSE);
	चयन (sense) अणु
	हाल VCC_3VORXV_CAPABLE:
		val |= SS_3VCARD | SS_XVCARD;
		अवरोध;
	हाल VCC_XV_ONLY:
		val |= SS_XVCARD;
		अवरोध;
	हाल VCC_3V_CAPABLE:
		val |= SS_3VCARD;
		अवरोध;
	शेष:
		/* 5V only */
		अवरोध;
	पूर्ण

	*value = val;

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t set_Vcc_value(u_अक्षर Vcc)
अणु
	चयन (Vcc) अणु
	हाल 33:
		वापस VCC_3V;
	हाल 50:
		वापस VCC_5V;
	पूर्ण

	/* Small voltage is chosen क्रम safety. */
	वापस VCC_3V;
पूर्ण

अटल पूर्णांक pccard_set_socket(काष्ठा pcmcia_socket *sock, socket_state_t *state)
अणु
	काष्ठा vrc4171_socket *socket;
	अचिन्हित पूर्णांक slot;
	uपूर्णांक8_t voltage, घातer, control, cscपूर्णांक;

	अगर (sock == शून्य || sock->sock >= CARD_MAX_SLOTS ||
	    (state->Vpp != state->Vcc && state->Vpp != 0) ||
	    (state->Vcc != 50 && state->Vcc != 33 && state->Vcc != 0))
		वापस -EINVAL;

	slot = sock->sock;
	socket = &vrc4171_sockets[slot];

	spin_lock_irq(&socket->lock);

	voltage = set_Vcc_value(state->Vcc);
	exca_ग_लिखो_byte(slot, CARD_VOLTAGE_SELECT, voltage);

	घातer = POWER_ENABLE;
	अगर (state->Vpp == state->Vcc)
		घातer |= VPP_GET_VCC;
	अगर (state->flags & SS_OUTPUT_ENA)
		घातer |= I365_PWR_OUT;
	exca_ग_लिखो_byte(slot, I365_POWER, घातer);

	control = 0;
	अगर (state->io_irq != 0)
		control |= socket->io_irq;
	अगर (state->flags & SS_IOCARD)
		control |= I365_PC_IOCARD;
	अगर (state->flags & SS_RESET)
		control	&= ~I365_PC_RESET;
	अन्यथा
		control |= I365_PC_RESET;
	exca_ग_लिखो_byte(slot, I365_INTCTL, control);

        cscपूर्णांक = 0;
        exca_ग_लिखो_byte(slot, I365_CSCINT, cscपूर्णांक);
	exca_पढ़ो_byte(slot, I365_CSC);	/* clear CardStatus change */
	अगर (state->csc_mask != 0)
		cscपूर्णांक |= socket->csc_irq << 8;
	अगर (state->flags & SS_IOCARD) अणु
		अगर (state->csc_mask & SS_STSCHG)
			cscपूर्णांक |= I365_CSC_STSCHG;
	पूर्ण अन्यथा अणु
		अगर (state->csc_mask & SS_BATDEAD)
			cscपूर्णांक |= I365_CSC_BVD1;
		अगर (state->csc_mask & SS_BATWARN)
			cscपूर्णांक |= I365_CSC_BVD2;
	पूर्ण
	अगर (state->csc_mask & SS_READY)
		cscपूर्णांक |= I365_CSC_READY;
	अगर (state->csc_mask & SS_DETECT)
		cscपूर्णांक |= I365_CSC_DETECT;
        exca_ग_लिखो_byte(slot, I365_CSCINT, cscपूर्णांक);

	spin_unlock_irq(&socket->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pccard_set_io_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_io_map *io)
अणु
	अचिन्हित पूर्णांक slot;
	uपूर्णांक8_t ioctl, addrwin;
	u_अक्षर map;

	अगर (sock == शून्य || sock->sock >= CARD_MAX_SLOTS ||
	    io == शून्य || io->map >= IO_MAX_MAPS ||
	    io->start > 0xffff || io->stop > 0xffff || io->start > io->stop)
		वापस -EINVAL;

	slot = sock->sock;
	map = io->map;

	addrwin = exca_पढ़ो_byte(slot, I365_ADDRWIN);
	अगर (addrwin & I365_ENA_IO(map)) अणु
		addrwin &= ~I365_ENA_IO(map);
		exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
	पूर्ण

	exca_ग_लिखो_word(slot, I365_IO(map)+I365_W_START, io->start);
	exca_ग_लिखो_word(slot, I365_IO(map)+I365_W_STOP, io->stop);

	ioctl = 0;
	अगर (io->speed > 0)
		ioctl |= I365_IOCTL_WAIT(map);
	अगर (io->flags & MAP_16BIT)
		ioctl |= I365_IOCTL_16BIT(map);
	अगर (io->flags & MAP_AUTOSZ)
		ioctl |= I365_IOCTL_IOCS16(map);
	अगर (io->flags & MAP_0WS)
		ioctl |= I365_IOCTL_0WS(map);
	exca_ग_लिखो_byte(slot, I365_IOCTL, ioctl);

	अगर (io->flags & MAP_ACTIVE) अणु
		addrwin |= I365_ENA_IO(map);
		exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pccard_set_mem_map(काष्ठा pcmcia_socket *sock, काष्ठा pccard_mem_map *mem)
अणु
	अचिन्हित पूर्णांक slot;
	uपूर्णांक16_t start, stop, offset;
	uपूर्णांक8_t addrwin;
	u_अक्षर map;

	अगर (sock == शून्य || sock->sock >= CARD_MAX_SLOTS ||
	    mem == शून्य || mem->map >= MEM_MAX_MAPS ||
	    mem->res->start < CARD_MEM_START || mem->res->start > CARD_MEM_END ||
	    mem->res->end < CARD_MEM_START || mem->res->end > CARD_MEM_END ||
	    mem->res->start > mem->res->end ||
	    mem->card_start > CARD_MAX_MEM_OFFSET ||
	    mem->speed > CARD_MAX_MEM_SPEED)
		वापस -EINVAL;

	slot = sock->sock;
	map = mem->map;

	addrwin = exca_पढ़ो_byte(slot, I365_ADDRWIN);
	अगर (addrwin & I365_ENA_MEM(map)) अणु
		addrwin &= ~I365_ENA_MEM(map);
		exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
	पूर्ण

	start = (mem->res->start >> 12) & 0x3fff;
	अगर (mem->flags & MAP_16BIT)
		start |= I365_MEM_16BIT;
	exca_ग_लिखो_word(slot, I365_MEM(map)+I365_W_START, start);

	stop = (mem->res->end >> 12) & 0x3fff;
	चयन (mem->speed) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		stop |= I365_MEM_WS0;
		अवरोध;
	हाल 2:
		stop |= I365_MEM_WS1;
		अवरोध;
	शेष:
		stop |= I365_MEM_WS0 | I365_MEM_WS1;
		अवरोध;
	पूर्ण
	exca_ग_लिखो_word(slot, I365_MEM(map)+I365_W_STOP, stop);

	offset = (mem->card_start >> 12) & 0x3fff;
	अगर (mem->flags & MAP_ATTRIB)
		offset |= I365_MEM_REG;
	अगर (mem->flags & MAP_WRPROT)
		offset |= I365_MEM_WRPROT;
	exca_ग_लिखो_word(slot, I365_MEM(map)+I365_W_OFF, offset);

	अगर (mem->flags & MAP_ACTIVE) अणु
		addrwin |= I365_ENA_MEM(map);
		exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations vrc4171_pccard_operations = अणु
	.init			= pccard_init,
	.get_status		= pccard_get_status,
	.set_socket		= pccard_set_socket,
	.set_io_map		= pccard_set_io_map,
	.set_mem_map		= pccard_set_mem_map,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक get_events(पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक events = 0;
	uपूर्णांक8_t status, csc;

	status = exca_पढ़ो_byte(slot, I365_STATUS);
	csc = exca_पढ़ो_byte(slot, I365_CSC);

	अगर (exca_पढ़ो_byte(slot, I365_INTCTL) & I365_PC_IOCARD) अणु
		अगर ((csc & I365_CSC_STSCHG) && (status & I365_CS_STSCHG))
			events |= SS_STSCHG;
	पूर्ण अन्यथा अणु
		अगर (csc & (I365_CSC_BVD1 | I365_CSC_BVD2)) अणु
			अगर (!(status & I365_CS_BVD1))
				events |= SS_BATDEAD;
			अन्यथा अगर ((status & (I365_CS_BVD1 | I365_CS_BVD2)) == I365_CS_BVD1)
				events |= SS_BATWARN;
		पूर्ण
	पूर्ण
	अगर ((csc & I365_CSC_READY) && (status & I365_CS_READY))
		events |= SS_READY;
	अगर ((csc & I365_CSC_DETECT) && ((status & I365_CS_DETECT) == I365_CS_DETECT))
		events |= SS_DETECT;

	वापस events;
पूर्ण

अटल irqवापस_t pccard_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vrc4171_socket *socket;
	अचिन्हित पूर्णांक events;
	irqवापस_t retval = IRQ_NONE;
	uपूर्णांक16_t status;

	status = vrc4171_get_irq_status();
	अगर (status & IRQ_A) अणु
		socket = &vrc4171_sockets[CARD_SLOTA];
		अगर (socket->slot == SLOT_INITIALIZED) अणु
			अगर (status & (1 << socket->csc_irq)) अणु
				events = get_events(CARD_SLOTA);
				अगर (events != 0) अणु
					pcmcia_parse_events(&socket->pcmcia_socket, events);
					retval = IRQ_HANDLED;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (status & IRQ_B) अणु
		socket = &vrc4171_sockets[CARD_SLOTB];
		अगर (socket->slot == SLOT_INITIALIZED) अणु
			अगर (status & (1 << socket->csc_irq)) अणु
				events = get_events(CARD_SLOTB);
				अगर (events != 0) अणु
					pcmcia_parse_events(&socket->pcmcia_socket, events);
					retval = IRQ_HANDLED;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल अंतरभूत व्योम reserve_using_irq(पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक irq;

	irq = exca_पढ़ो_byte(slot, I365_INTCTL);
	irq &= 0x0f;
	vrc4171_irq_mask &= ~(1 << irq);

	irq = exca_पढ़ो_byte(slot, I365_CSCINT);
	irq = (irq & 0xf0) >> 4;
	vrc4171_irq_mask &= ~(1 << irq);
पूर्ण

अटल पूर्णांक vrc4171_add_sockets(व्योम)
अणु
	काष्ठा vrc4171_socket *socket;
	पूर्णांक slot, retval;

	क्रम (slot = 0; slot < CARD_MAX_SLOTS; slot++) अणु
		अगर (slot == CARD_SLOTB && vrc4171_slotb == SLOTB_IS_NONE)
			जारी;

		socket = &vrc4171_sockets[slot];
		अगर (socket->slot != SLOT_PROBE) अणु
			uपूर्णांक8_t addrwin;

			चयन (socket->slot) अणु
			हाल SLOT_NOPROBE_MEM:
				addrwin = exca_पढ़ो_byte(slot, I365_ADDRWIN);
				addrwin &= 0x1f;
				exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
				अवरोध;
			हाल SLOT_NOPROBE_IO:
				addrwin = exca_पढ़ो_byte(slot, I365_ADDRWIN);
				addrwin &= 0xc0;
				exca_ग_लिखो_byte(slot, I365_ADDRWIN, addrwin);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			reserve_using_irq(slot);
			जारी;
		पूर्ण

		प्र_लिखो(socket->name, "NEC VRC4171 Card Slot %1c", 'A' + slot);
		socket->pcmcia_socket.dev.parent = &vrc4171_card_device.dev;
		socket->pcmcia_socket.ops = &vrc4171_pccard_operations;
		socket->pcmcia_socket.owner = THIS_MODULE;

		retval = pcmcia_रेजिस्टर_socket(&socket->pcmcia_socket);
		अगर (retval < 0)
			वापस retval;

		exca_ग_लिखो_byte(slot, I365_ADDRWIN, 0);
		exca_ग_लिखो_byte(slot, GLOBAL_CONTROL, 0);

		socket->slot = SLOT_INITIALIZED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vrc4171_हटाओ_sockets(व्योम)
अणु
	काष्ठा vrc4171_socket *socket;
	पूर्णांक slot;

	क्रम (slot = 0; slot < CARD_MAX_SLOTS; slot++) अणु
		अगर (slot == CARD_SLOTB && vrc4171_slotb == SLOTB_IS_NONE)
			जारी;

		socket = &vrc4171_sockets[slot];
		अगर (socket->slot == SLOT_INITIALIZED)
			pcmcia_unरेजिस्टर_socket(&socket->pcmcia_socket);

		socket->slot = SLOT_PROBE;
	पूर्ण
पूर्ण

अटल पूर्णांक vrc4171_card_setup(अक्षर *options)
अणु
	अगर (options == शून्य || *options == '\0')
		वापस 1;

	अगर (म_भेदन(options, "irq:", 4) == 0) अणु
		पूर्णांक irq;
		options += 4;
		irq = simple_म_से_अदीर्घ(options, &options, 0);
		अगर (irq >= 0 && irq < nr_irqs)
			vrc4171_irq = irq;

		अगर (*options != ',')
			वापस 1;
		options++;
	पूर्ण

	अगर (म_भेदन(options, "slota:", 6) == 0) अणु
		options += 6;
		अगर (*options != '\0') अणु
			अगर (म_भेदन(options, "memnoprobe", 10) == 0) अणु
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_MEM;
				options += 10;
			पूर्ण अन्यथा अगर (म_भेदन(options, "ionoprobe", 9) == 0) अणु
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_IO;
				options += 9;
			पूर्ण अन्यथा अगर ( म_भेदन(options, "noprobe", 7) == 0) अणु
				vrc4171_sockets[CARD_SLOTA].slot = SLOT_NOPROBE_ALL;
				options += 7;
			पूर्ण

			अगर (*options != ',')
				वापस 1;
			options++;
		पूर्ण अन्यथा
			वापस 1;

	पूर्ण

	अगर (म_भेदन(options, "slotb:", 6) == 0) अणु
		options += 6;
		अगर (*options != '\0') अणु
			अगर (म_भेदन(options, "pccard", 6) == 0) अणु
				vrc4171_slotb = SLOTB_IS_PCCARD;
				options += 6;
			पूर्ण अन्यथा अगर (म_भेदन(options, "cf", 2) == 0) अणु
				vrc4171_slotb = SLOTB_IS_CF;
				options += 2;
			पूर्ण अन्यथा अगर (म_भेदन(options, "flashrom", 8) == 0) अणु
				vrc4171_slotb = SLOTB_IS_FLASHROM;
				options += 8;
			पूर्ण अन्यथा अगर (म_भेदन(options, "none", 4) == 0) अणु
				vrc4171_slotb = SLOTB_IS_NONE;
				options += 4;
			पूर्ण

			अगर (*options != ',')
				वापस 1;
			options++;

			अगर (म_भेदन(options, "memnoprobe", 10) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_MEM;
			अगर (म_भेदन(options, "ionoprobe", 9) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_IO;
			अगर (म_भेदन(options, "noprobe", 7) == 0)
				vrc4171_sockets[CARD_SLOTB].slot = SLOT_NOPROBE_ALL;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

__setup("vrc4171_card=", vrc4171_card_setup);

अटल काष्ठा platक्रमm_driver vrc4171_card_driver = अणु
	.driver = अणु
		.name		= vrc4171_card_name,
	पूर्ण,
पूर्ण;

अटल पूर्णांक vrc4171_card_init(व्योम)
अणु
	पूर्णांक retval;

	retval = platक्रमm_driver_रेजिस्टर(&vrc4171_card_driver);
	अगर (retval < 0)
		वापस retval;

	retval = platक्रमm_device_रेजिस्टर(&vrc4171_card_device);
	अगर (retval < 0) अणु
		platक्रमm_driver_unरेजिस्टर(&vrc4171_card_driver);
		वापस retval;
	पूर्ण

	vrc4171_set_multअगरunction_pin(vrc4171_slotb);

	retval = vrc4171_add_sockets();
	अगर (retval == 0)
		retval = request_irq(vrc4171_irq, pccard_पूर्णांकerrupt, IRQF_SHARED,
		                     vrc4171_card_name, vrc4171_sockets);

	अगर (retval < 0) अणु
		vrc4171_हटाओ_sockets();
		platक्रमm_device_unरेजिस्टर(&vrc4171_card_device);
		platक्रमm_driver_unरेजिस्टर(&vrc4171_card_driver);
		वापस retval;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s, connected to IRQ %d\n",
		vrc4171_card_driver.driver.name, vrc4171_irq);

	वापस 0;
पूर्ण

अटल व्योम vrc4171_card_निकास(व्योम)
अणु
	मुक्त_irq(vrc4171_irq, vrc4171_sockets);
	vrc4171_हटाओ_sockets();
	platक्रमm_device_unरेजिस्टर(&vrc4171_card_device);
	platक्रमm_driver_unरेजिस्टर(&vrc4171_card_driver);
पूर्ण

module_init(vrc4171_card_init);
module_निकास(vrc4171_card_निकास);
