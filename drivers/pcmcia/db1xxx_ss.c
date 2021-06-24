<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCMCIA socket code क्रम the Alchemy Db1xxx/Pb1xxx boards.
 *
 * Copyright (c) 2009 Manuel Lauss <manuel.lauss@gmail.com>
 *
 */

/* This is a fairly generic PCMCIA socket driver suitable क्रम the
 * following Alchemy Development boards:
 *  Db1000, Db/Pb1500, Db/Pb1100, Db/Pb1550, Db/Pb1200, Db1300
 *
 * The Db1000 is used as a reference:  Per-socket card-, carddetect- and
 *  statuschange IRQs connected to SoC GPIOs, control and status रेजिस्टर
 *  bits arranged in per-socket groups in an बाह्यal PLD.  All boards
 *  listed here use this layout, including bit positions and meanings.
 *  Of course there are exceptions in later boards:
 *
 *	- Pb1100/Pb1500:  single socket only; voltage key bits VS are
 *			  at STATUS[5:4] (instead of STATUS[1:0]).
 *	- Au1200-based:	  additional card-eject irqs, irqs not gpios!
 *	- Db1300:	  Db1200-like, no pwr ctrl, single socket (#1).
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <pcmcia/ss.h>

#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

#घोषणा MEM_MAP_SIZE	0x400000
#घोषणा IO_MAP_SIZE	0x1000

काष्ठा db1x_pcmcia_sock अणु
	काष्ठा pcmcia_socket	socket;
	पूर्णांक		nr;		/* socket number */
	व्योम		*virt_io;

	phys_addr_t	phys_io;
	phys_addr_t	phys_attr;
	phys_addr_t	phys_mem;

	/* previous flags क्रम set_socket() */
	अचिन्हित पूर्णांक old_flags;

	/* पूर्णांकerrupt sources: linux irq numbers! */
	पूर्णांक	insert_irq;	/* शेष carddetect irq */
	पूर्णांक	stschg_irq;	/* card-status-change irq */
	पूर्णांक	card_irq;	/* card irq */
	पूर्णांक	eject_irq;	/* db1200/pb1200 have these */
	पूर्णांक	insert_gpio;	/* db1000 carddetect gpio */

#घोषणा BOARD_TYPE_DEFAULT	0	/* most boards */
#घोषणा BOARD_TYPE_DB1200	1	/* IRQs aren't gpios */
#घोषणा BOARD_TYPE_PB1100	2	/* VS bits slightly dअगरferent */
#घोषणा BOARD_TYPE_DB1300	3	/* no घातer control */
	पूर्णांक	board_type;
पूर्ण;

#घोषणा to_db1x_socket(x) container_of(x, काष्ठा db1x_pcmcia_sock, socket)

अटल पूर्णांक db1300_card_inserted(काष्ठा db1x_pcmcia_sock *sock)
अणु
	वापस bcsr_पढ़ो(BCSR_SIGSTAT) & (1 << 8);
पूर्ण

/* DB/PB1200: check CPLD SIGSTATUS रेजिस्टर bit 10/12 */
अटल पूर्णांक db1200_card_inserted(काष्ठा db1x_pcmcia_sock *sock)
अणु
	अचिन्हित लघु sigstat;

	sigstat = bcsr_पढ़ो(BCSR_SIGSTAT);
	वापस sigstat & 1 << (8 + 2 * sock->nr);
पूर्ण

/* carddetect gpio: low-active */
अटल पूर्णांक db1000_card_inserted(काष्ठा db1x_pcmcia_sock *sock)
अणु
	वापस !gpio_get_value(sock->insert_gpio);
पूर्ण

अटल पूर्णांक db1x_card_inserted(काष्ठा db1x_pcmcia_sock *sock)
अणु
	चयन (sock->board_type) अणु
	हाल BOARD_TYPE_DB1200:
		वापस db1200_card_inserted(sock);
	हाल BOARD_TYPE_DB1300:
		वापस db1300_card_inserted(sock);
	शेष:
		वापस db1000_card_inserted(sock);
	पूर्ण
पूर्ण

/* STSCHG tends to bounce heavily when cards are inserted/ejected.
 * To aव्योम this, the पूर्णांकerrupt is normally disabled and only enabled
 * after reset to a card has been de-निश्चितed.
 */
अटल अंतरभूत व्योम set_stschg(काष्ठा db1x_pcmcia_sock *sock, पूर्णांक en)
अणु
	अगर (sock->stschg_irq != -1) अणु
		अगर (en)
			enable_irq(sock->stschg_irq);
		अन्यथा
			disable_irq(sock->stschg_irq);
	पूर्ण
पूर्ण

अटल irqवापस_t db1000_pcmcia_cdirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा db1x_pcmcia_sock *sock = data;

	pcmcia_parse_events(&sock->socket, SS_DETECT);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t db1000_pcmcia_stschgirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा db1x_pcmcia_sock *sock = data;

	pcmcia_parse_events(&sock->socket, SS_STSCHG);

	वापस IRQ_HANDLED;
पूर्ण

/* Db/Pb1200 have separate per-socket insertion and ejection
 * पूर्णांकerrupts which stay निश्चितed as दीर्घ as the card is
 * inserted/missing.  The one which caused us to be called
 * needs to be disabled and the other one enabled.
 */
अटल irqवापस_t db1200_pcmcia_cdirq(पूर्णांक irq, व्योम *data)
अणु
	disable_irq_nosync(irq);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t db1200_pcmcia_cdirq_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा db1x_pcmcia_sock *sock = data;

	/* Wait a bit क्रम the संकेतs to stop bouncing. */
	msleep(100);
	अगर (irq == sock->insert_irq)
		enable_irq(sock->eject_irq);
	अन्यथा
		enable_irq(sock->insert_irq);

	pcmcia_parse_events(&sock->socket, SS_DETECT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक db1x_pcmcia_setup_irqs(काष्ठा db1x_pcmcia_sock *sock)
अणु
	पूर्णांक ret;

	अगर (sock->stschg_irq != -1) अणु
		ret = request_irq(sock->stschg_irq, db1000_pcmcia_stschgirq,
				  0, "pcmcia_stschg", sock);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Db/Pb1200 have separate per-socket insertion and ejection
	 * पूर्णांकerrupts, which should show edge behaviour but करोn't.
	 * So पूर्णांकerrupts are disabled until both insertion and
	 * ejection handler have been रेजिस्टरed and the currently
	 * active one disabled.
	 */
	अगर ((sock->board_type == BOARD_TYPE_DB1200) ||
	    (sock->board_type == BOARD_TYPE_DB1300)) अणु
		ret = request_thपढ़ोed_irq(sock->insert_irq, db1200_pcmcia_cdirq,
			db1200_pcmcia_cdirq_fn, 0, "pcmcia_insert", sock);
		अगर (ret)
			जाओ out1;

		ret = request_thपढ़ोed_irq(sock->eject_irq, db1200_pcmcia_cdirq,
			db1200_pcmcia_cdirq_fn, 0, "pcmcia_eject", sock);
		अगर (ret) अणु
			मुक्त_irq(sock->insert_irq, sock);
			जाओ out1;
		पूर्ण

		/* enable the currently silent one */
		अगर (db1x_card_inserted(sock))
			enable_irq(sock->eject_irq);
		अन्यथा
			enable_irq(sock->insert_irq);
	पूर्ण अन्यथा अणु
		/* all other (older) Db1x00 boards use a GPIO to show
		 * card detection status:  use both-edge triggers.
		 */
		irq_set_irq_type(sock->insert_irq, IRQ_TYPE_EDGE_BOTH);
		ret = request_irq(sock->insert_irq, db1000_pcmcia_cdirq,
				  0, "pcmcia_carddetect", sock);

		अगर (ret)
			जाओ out1;
	पूर्ण

	वापस 0;	/* all करोne */

out1:
	अगर (sock->stschg_irq != -1)
		मुक्त_irq(sock->stschg_irq, sock);

	वापस ret;
पूर्ण

अटल व्योम db1x_pcmcia_मुक्त_irqs(काष्ठा db1x_pcmcia_sock *sock)
अणु
	अगर (sock->stschg_irq != -1)
		मुक्त_irq(sock->stschg_irq, sock);

	मुक्त_irq(sock->insert_irq, sock);
	अगर (sock->eject_irq != -1)
		मुक्त_irq(sock->eject_irq, sock);
पूर्ण

/*
 * configure a PCMCIA socket on the Db1x00 series of boards (and
 * compatibles).
 *
 * 2 बाह्यal रेजिस्टरs are involved:
 *   pcmcia_status (offset 0x04): bits [0:1/2:3]: पढ़ो card voltage id
 *   pcmcia_control(offset 0x10):
 *	bits[0:1] set vcc क्रम card
 *	bits[2:3] set vpp क्रम card
 *	bit 4:	enable data buffers
 *	bit 7:	reset# क्रम card
 *	add 8 क्रम second socket.
 */
अटल पूर्णांक db1x_pcmcia_configure(काष्ठा pcmcia_socket *skt,
				 काष्ठा socket_state_t *state)
अणु
	काष्ठा db1x_pcmcia_sock *sock = to_db1x_socket(skt);
	अचिन्हित लघु cr_clr, cr_set;
	अचिन्हित पूर्णांक changed;
	पूर्णांक v, p, ret;

	/* card voltage setup */
	cr_clr = (0xf << (sock->nr * 8)); /* clear voltage settings */
	cr_set = 0;
	v = p = ret = 0;

	चयन (state->Vcc) अणु
	हाल 50:
		++v;
		fallthrough;
	हाल 33:
		++v;
		fallthrough;
	हाल 0:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "pcmcia%d unsupported Vcc %d\n",
			sock->nr, state->Vcc);
	पूर्ण

	चयन (state->Vpp) अणु
	हाल 12:
		++p;
		fallthrough;
	हाल 33:
	हाल 50:
		++p;
		fallthrough;
	हाल 0:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "pcmcia%d unsupported Vpp %d\n",
			sock->nr, state->Vpp);
	पूर्ण

	/* sanity check: Vpp must be 0, 12, or Vcc */
	अगर (((state->Vcc == 33) && (state->Vpp == 50)) ||
	    ((state->Vcc == 50) && (state->Vpp == 33))) अणु
		prपूर्णांकk(KERN_INFO "pcmcia%d bad Vcc/Vpp combo (%d %d)\n",
			sock->nr, state->Vcc, state->Vpp);
		v = p = 0;
		ret = -EINVAL;
	पूर्ण

	/* create new voltage code */
	अगर (sock->board_type != BOARD_TYPE_DB1300)
		cr_set |= ((v << 2) | p) << (sock->nr * 8);

	changed = state->flags ^ sock->old_flags;

	अगर (changed & SS_RESET) अणु
		अगर (state->flags & SS_RESET) अणु
			set_stschg(sock, 0);
			/* निश्चित reset, disable io buffers */
			cr_clr |= (1 << (7 + (sock->nr * 8)));
			cr_clr |= (1 << (4 + (sock->nr * 8)));
		पूर्ण अन्यथा अणु
			/* de-निश्चित reset, enable io buffers */
			cr_set |= 1 << (7 + (sock->nr * 8));
			cr_set |= 1 << (4 + (sock->nr * 8));
		पूर्ण
	पूर्ण

	/* update PCMCIA configuration */
	bcsr_mod(BCSR_PCMCIA, cr_clr, cr_set);

	sock->old_flags = state->flags;

	/* reset was taken away: give card समय to initialize properly */
	अगर ((changed & SS_RESET) && !(state->flags & SS_RESET)) अणु
		msleep(500);
		set_stschg(sock, 1);
	पूर्ण

	वापस ret;
पूर्ण

/* VCC bits at [3:2]/[11:10] */
#घोषणा GET_VCC(cr, socknr)		\
	((((cr) >> 2) >> ((socknr) * 8)) & 3)

/* VS bits at [0:1]/[3:2] */
#घोषणा GET_VS(sr, socknr)		\
	(((sr) >> (2 * (socknr))) & 3)

/* reset bits at [7]/[15] */
#घोषणा GET_RESET(cr, socknr)		\
	((cr) & (1 << (7 + (8 * (socknr)))))

अटल पूर्णांक db1x_pcmcia_get_status(काष्ठा pcmcia_socket *skt,
				  अचिन्हित पूर्णांक *value)
अणु
	काष्ठा db1x_pcmcia_sock *sock = to_db1x_socket(skt);
	अचिन्हित लघु cr, sr;
	अचिन्हित पूर्णांक status;

	status = db1x_card_inserted(sock) ? SS_DETECT : 0;

	cr = bcsr_पढ़ो(BCSR_PCMCIA);
	sr = bcsr_पढ़ो(BCSR_STATUS);

	/* PB1100/PB1500: voltage key bits are at [5:4] */
	अगर (sock->board_type == BOARD_TYPE_PB1100)
		sr >>= 4;

	/* determine card type */
	चयन (GET_VS(sr, sock->nr)) अणु
	हाल 0:
	हाल 2:
		status |= SS_3VCARD;	/* 3V card */
	हाल 3:
		अवरोध;			/* 5V card: set nothing */
	शेष:
		status |= SS_XVCARD;	/* treated as unsupported in core */
	पूर्ण

	/* अगर Vcc is not zero, we have applied घातer to a card */
	status |= GET_VCC(cr, sock->nr) ? SS_POWERON : 0;

	/* DB1300: घातer always on, but करोn't tell when no card present */
	अगर ((sock->board_type == BOARD_TYPE_DB1300) && (status & SS_DETECT))
		status = SS_POWERON | SS_3VCARD | SS_DETECT;

	/* reset de-निश्चितed? then we're पढ़ोy */
	status |= (GET_RESET(cr, sock->nr)) ? SS_READY : SS_RESET;

	*value = status;

	वापस 0;
पूर्ण

अटल पूर्णांक db1x_pcmcia_sock_init(काष्ठा pcmcia_socket *skt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक db1x_pcmcia_sock_suspend(काष्ठा pcmcia_socket *skt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक au1x00_pcmcia_set_io_map(काष्ठा pcmcia_socket *skt,
				    काष्ठा pccard_io_map *map)
अणु
	काष्ठा db1x_pcmcia_sock *sock = to_db1x_socket(skt);

	map->start = (u32)sock->virt_io;
	map->stop = map->start + IO_MAP_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक au1x00_pcmcia_set_mem_map(काष्ठा pcmcia_socket *skt,
				     काष्ठा pccard_mem_map *map)
अणु
	काष्ठा db1x_pcmcia_sock *sock = to_db1x_socket(skt);

	अगर (map->flags & MAP_ATTRIB)
		map->अटल_start = sock->phys_attr + map->card_start;
	अन्यथा
		map->अटल_start = sock->phys_mem + map->card_start;

	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations db1x_pcmcia_operations = अणु
	.init			= db1x_pcmcia_sock_init,
	.suspend		= db1x_pcmcia_sock_suspend,
	.get_status		= db1x_pcmcia_get_status,
	.set_socket		= db1x_pcmcia_configure,
	.set_io_map		= au1x00_pcmcia_set_io_map,
	.set_mem_map		= au1x00_pcmcia_set_mem_map,
पूर्ण;

अटल पूर्णांक db1x_pcmcia_socket_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा db1x_pcmcia_sock *sock;
	काष्ठा resource *r;
	पूर्णांक ret, bid;

	sock = kzalloc(माप(काष्ठा db1x_pcmcia_sock), GFP_KERNEL);
	अगर (!sock)
		वापस -ENOMEM;

	sock->nr = pdev->id;

	bid = BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI));
	चयन (bid) अणु
	हाल BCSR_WHOAMI_PB1500:
	हाल BCSR_WHOAMI_PB1500R2:
	हाल BCSR_WHOAMI_PB1100:
		sock->board_type = BOARD_TYPE_PB1100;
		अवरोध;
	हाल BCSR_WHOAMI_DB1000 ... BCSR_WHOAMI_PB1550_SDR:
		sock->board_type = BOARD_TYPE_DEFAULT;
		अवरोध;
	हाल BCSR_WHOAMI_PB1200 ... BCSR_WHOAMI_DB1200:
		sock->board_type = BOARD_TYPE_DB1200;
		अवरोध;
	हाल BCSR_WHOAMI_DB1300:
		sock->board_type = BOARD_TYPE_DB1300;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "db1xxx-ss: unknown board %d!\n", bid);
		ret = -ENODEV;
		जाओ out0;
	पूर्ण

	/*
	 * gather resources necessary and optional nice-to-haves to
	 * operate a socket:
	 * This includes IRQs क्रम Carddetection/ejection, the card
	 *  itself and optional status change detection.
	 * Also, the memory areas covered by a socket.  For these
	 *  we require the real 36bit addresses (see the au1000.h
	 *  header क्रम more inक्रमmation).
	 */

	/* card: irq asचिन्हित to the card itself. */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "card");
	sock->card_irq = r ? r->start : 0;

	/* insert: irq which triggers on card insertion/ejection
	 * BIG FAT NOTE: on DB1000/1100/1500/1550 we pass a GPIO here!
	 */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "insert");
	sock->insert_irq = r ? r->start : -1;
	अगर (sock->board_type == BOARD_TYPE_DEFAULT) अणु
		sock->insert_gpio = r ? r->start : -1;
		sock->insert_irq = r ? gpio_to_irq(r->start) : -1;
	पूर्ण

	/* stschg: irq which trigger on card status change (optional) */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "stschg");
	sock->stschg_irq = r ? r->start : -1;

	/* eject: irq which triggers on ejection (DB1200/PB1200 only) */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "eject");
	sock->eject_irq = r ? r->start : -1;

	ret = -ENODEV;

	/* 36bit PCMCIA Attribute area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-attr");
	अगर (!r) अणु
		prपूर्णांकk(KERN_ERR "pcmcia%d has no 'pseudo-attr' resource!\n",
			sock->nr);
		जाओ out0;
	पूर्ण
	sock->phys_attr = r->start;

	/* 36bit PCMCIA Memory area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-mem");
	अगर (!r) अणु
		prपूर्णांकk(KERN_ERR "pcmcia%d has no 'pseudo-mem' resource!\n",
			sock->nr);
		जाओ out0;
	पूर्ण
	sock->phys_mem = r->start;

	/* 36bit PCMCIA IO area address */
	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcmcia-io");
	अगर (!r) अणु
		prपूर्णांकk(KERN_ERR "pcmcia%d has no 'pseudo-io' resource!\n",
			sock->nr);
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
		prपूर्णांकk(KERN_ERR "pcmcia%d: cannot remap IO area\n",
			sock->nr);
		ret = -ENOMEM;
		जाओ out0;
	पूर्ण

	sock->socket.ops	= &db1x_pcmcia_operations;
	sock->socket.owner	= THIS_MODULE;
	sock->socket.pci_irq	= sock->card_irq;
	sock->socket.features	= SS_CAP_STATIC_MAP | SS_CAP_PCCARD;
	sock->socket.map_size	= MEM_MAP_SIZE;
	sock->socket.io_offset	= (अचिन्हित दीर्घ)sock->virt_io;
	sock->socket.dev.parent	= &pdev->dev;
	sock->socket.resource_ops = &pccard_अटल_ops;

	platक्रमm_set_drvdata(pdev, sock);

	ret = db1x_pcmcia_setup_irqs(sock);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "pcmcia%d cannot setup interrupts\n",
			sock->nr);
		जाओ out1;
	पूर्ण

	set_stschg(sock, 0);

	ret = pcmcia_रेजिस्टर_socket(&sock->socket);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "pcmcia%d failed to register\n", sock->nr);
		जाओ out2;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Alchemy Db/Pb1xxx pcmcia%d @ io/attr/mem %09llx"
		"(%p) %09llx %09llx  card/insert/stschg/eject irqs @ %d "
		"%d %d %d\n", sock->nr, sock->phys_io, sock->virt_io,
		sock->phys_attr, sock->phys_mem, sock->card_irq,
		sock->insert_irq, sock->stschg_irq, sock->eject_irq);

	वापस 0;

out2:
	db1x_pcmcia_मुक्त_irqs(sock);
out1:
	iounmap((व्योम *)(sock->virt_io + (u32)mips_io_port_base));
out0:
	kमुक्त(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक db1x_pcmcia_socket_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा db1x_pcmcia_sock *sock = platक्रमm_get_drvdata(pdev);

	db1x_pcmcia_मुक्त_irqs(sock);
	pcmcia_unरेजिस्टर_socket(&sock->socket);
	iounmap((व्योम *)(sock->virt_io + (u32)mips_io_port_base));
	kमुक्त(sock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver db1x_pcmcia_socket_driver = अणु
	.driver	= अणु
		.name	= "db1xxx_pcmcia",
	पूर्ण,
	.probe		= db1x_pcmcia_socket_probe,
	.हटाओ		= db1x_pcmcia_socket_हटाओ,
पूर्ण;

module_platक्रमm_driver(db1x_pcmcia_socket_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCMCIA Socket Services for Alchemy Db/Pb1x00 boards");
MODULE_AUTHOR("Manuel Lauss");
