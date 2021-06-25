<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * omap_cf.c -- OMAP 16xx CompactFlash controller driver
 *
 * Copyright (c) 2005 David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/ss.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/sizes.h>

#समावेश <mach/mux.h>
#समावेश <mach/tc.h>


/* NOTE:  करोn't expect this to support many I/O cards.  The 16xx chips have
 * hard-wired timings to support Compact Flash memory cards; they won't work
 * with various other devices (like WLAN adapters) without some बाह्यal
 * logic to help out.
 *
 * NOTE:  CF controller करोcs disagree with address space करोcs as to where
 * CF_BASE really lives; this is a करोc erratum.
 */
#घोषणा	CF_BASE	0xfffe2800

/* status; पढ़ो after IRQ */
#घोषणा CF_STATUS			(CF_BASE + 0x00)
#	define	CF_STATUS_BAD_READ	(1 << 2)
#	define	CF_STATUS_BAD_WRITE	(1 << 1)
#	define	CF_STATUS_CARD_DETECT	(1 << 0)

/* which chipselect (CS0..CS3) is used क्रम CF (active low) */
#घोषणा CF_CFG				(CF_BASE + 0x02)

/* card reset */
#घोषणा CF_CONTROL			(CF_BASE + 0x04)
#	define	CF_CONTROL_RESET	(1 << 0)

#घोषणा omap_cf_present() (!(omap_पढ़ोw(CF_STATUS) & CF_STATUS_CARD_DETECT))

/*--------------------------------------------------------------------------*/

अटल स्थिर अक्षर driver_name[] = "omap_cf";

काष्ठा omap_cf_socket अणु
	काष्ठा pcmcia_socket	socket;

	काष्ठा समयr_list	समयr;
	अचिन्हित		present:1;
	अचिन्हित		active:1;

	काष्ठा platक्रमm_device	*pdev;
	अचिन्हित दीर्घ		phys_cf;
	u_पूर्णांक			irq;
	काष्ठा resource		iomem;
पूर्ण;

#घोषणा	POLL_INTERVAL		(2 * HZ)

/*--------------------------------------------------------------------------*/

अटल पूर्णांक omap_cf_ss_init(काष्ठा pcmcia_socket *s)
अणु
	वापस 0;
पूर्ण

/* the समयr is primarily to kick this socket's pccardd */
अटल व्योम omap_cf_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा omap_cf_socket	*cf = from_समयr(cf, t, समयr);
	अचिन्हित		present = omap_cf_present();

	अगर (present != cf->present) अणु
		cf->present = present;
		pr_debug("%s: card %s\n", driver_name,
			present ? "present" : "gone");
		pcmcia_parse_events(&cf->socket, SS_DETECT);
	पूर्ण

	अगर (cf->active)
		mod_समयr(&cf->समयr, jअगरfies + POLL_INTERVAL);
पूर्ण

/* This irq handler prevents "irqNNN: nobody cared" messages as drivers
 * claim the card's IRQ.  It may also detect some card insertions, but
 * not removals; it can't always eliminate समयr irqs.
 */
अटल irqवापस_t omap_cf_irq(पूर्णांक irq, व्योम *_cf)
अणु
	काष्ठा omap_cf_socket *cf = (काष्ठा omap_cf_socket *)_cf;

	omap_cf_समयr(&cf->समयr);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap_cf_get_status(काष्ठा pcmcia_socket *s, u_पूर्णांक *sp)
अणु
	अगर (!sp)
		वापस -EINVAL;

	/* NOTE CF is always 3VCARD */
	अगर (omap_cf_present()) अणु
		काष्ठा omap_cf_socket	*cf;

		*sp = SS_READY | SS_DETECT | SS_POWERON | SS_3VCARD;
		cf = container_of(s, काष्ठा omap_cf_socket, socket);
		s->pcmcia_irq = 0;
		s->pci_irq = cf->irq;
	पूर्ण अन्यथा
		*sp = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
omap_cf_set_socket(काष्ठा pcmcia_socket *sock, काष्ठा socket_state_t *s)
अणु
	u16		control;

	/* REVISIT some non-OSK boards may support घातer चयनing */
	चयन (s->Vcc) अणु
	हाल 0:
	हाल 33:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	control = omap_पढ़ोw(CF_CONTROL);
	अगर (s->flags & SS_RESET)
		omap_ग_लिखोw(CF_CONTROL_RESET, CF_CONTROL);
	अन्यथा
		omap_ग_लिखोw(0, CF_CONTROL);

	pr_debug("%s: Vcc %d, io_irq %d, flags %04x csc %04x\n",
		driver_name, s->Vcc, s->io_irq, s->flags, s->csc_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_cf_ss_suspend(काष्ठा pcmcia_socket *s)
अणु
	pr_debug("%s: %s\n", driver_name, __func__);
	वापस omap_cf_set_socket(s, &dead_socket);
पूर्ण

/* regions are 2K each:  mem, attrib, io (and reserved-क्रम-ide) */

अटल पूर्णांक
omap_cf_set_io_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_io_map *io)
अणु
	काष्ठा omap_cf_socket	*cf;

	cf = container_of(s, काष्ठा omap_cf_socket, socket);
	io->flags &= MAP_ACTIVE|MAP_ATTRIB|MAP_16BIT;
	io->start = cf->phys_cf + SZ_4K;
	io->stop = io->start + SZ_2K - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
omap_cf_set_mem_map(काष्ठा pcmcia_socket *s, काष्ठा pccard_mem_map *map)
अणु
	काष्ठा omap_cf_socket	*cf;

	अगर (map->card_start)
		वापस -EINVAL;
	cf = container_of(s, काष्ठा omap_cf_socket, socket);
	map->अटल_start = cf->phys_cf;
	map->flags &= MAP_ACTIVE|MAP_ATTRIB|MAP_16BIT;
	अगर (map->flags & MAP_ATTRIB)
		map->अटल_start += SZ_2K;
	वापस 0;
पूर्ण

अटल काष्ठा pccard_operations omap_cf_ops = अणु
	.init			= omap_cf_ss_init,
	.suspend		= omap_cf_ss_suspend,
	.get_status		= omap_cf_get_status,
	.set_socket		= omap_cf_set_socket,
	.set_io_map		= omap_cf_set_io_map,
	.set_mem_map		= omap_cf_set_mem_map,
पूर्ण;

/*--------------------------------------------------------------------------*/

/*
 * NOTE:  right now the only board-specअगरic platक्रमm_data is
 * "what chipselect is used".  Boards could want more.
 */

अटल पूर्णांक __init omap_cf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित		seg;
	काष्ठा omap_cf_socket	*cf;
	पूर्णांक			irq;
	पूर्णांक			status;

	seg = (पूर्णांक) pdev->dev.platक्रमm_data;
	अगर (seg == 0 || seg > 3)
		वापस -ENODEV;

	/* either CFLASH.IREQ (INT_1610_CF) or some GPIO */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	cf = kzalloc(माप *cf, GFP_KERNEL);
	अगर (!cf)
		वापस -ENOMEM;
	समयr_setup(&cf->समयr, omap_cf_समयr, 0);

	cf->pdev = pdev;
	platक्रमm_set_drvdata(pdev, cf);

	/* this primarily just shuts up irq handling noise */
	status = request_irq(irq, omap_cf_irq, IRQF_SHARED,
			driver_name, cf);
	अगर (status < 0)
		जाओ fail0;
	cf->irq = irq;
	cf->socket.pci_irq = irq;

	चयन (seg) अणु
	/* NOTE: CS0 could be configured too ... */
	हाल 1:
		cf->phys_cf = OMAP_CS1_PHYS;
		अवरोध;
	हाल 2:
		cf->phys_cf = OMAP_CS2_PHYS;
		अवरोध;
	हाल 3:
		cf->phys_cf = omap_cs3_phys();
		अवरोध;
	शेष:
		जाओ  fail1;
	पूर्ण
	cf->iomem.start = cf->phys_cf;
	cf->iomem.end = cf->iomem.end + SZ_8K - 1;
	cf->iomem.flags = IORESOURCE_MEM;

	/* pcmcia layer only remaps "real" memory */
	cf->socket.io_offset = (अचिन्हित दीर्घ)
			ioremap(cf->phys_cf + SZ_4K, SZ_2K);
	अगर (!cf->socket.io_offset) अणु
		status = -ENOMEM;
		जाओ fail1;
	पूर्ण

	अगर (!request_mem_region(cf->phys_cf, SZ_8K, driver_name)) अणु
		status = -ENXIO;
		जाओ fail1;
	पूर्ण

	/* NOTE:  CF conflicts with MMC1 */
	omap_cfg_reg(W11_1610_CF_CD1);
	omap_cfg_reg(P11_1610_CF_CD2);
	omap_cfg_reg(R11_1610_CF_IOIS16);
	omap_cfg_reg(V10_1610_CF_IREQ);
	omap_cfg_reg(W10_1610_CF_RESET);

	omap_ग_लिखोw(~(1 << seg), CF_CFG);

	pr_info("%s: cs%d on irq %d\n", driver_name, seg, irq);

	/* NOTE:  better EMIFS setup might support more cards; but the
	 * TRM only shows how to affect regular flash संकेतs, not their
	 * CF/PCMCIA variants...
	 */
	pr_debug("%s: cs%d, previous ccs %08x acs %08x\n", driver_name,
		seg, omap_पढ़ोl(EMIFS_CCS(seg)), omap_पढ़ोl(EMIFS_ACS(seg)));
	omap_ग_लिखोl(0x0004a1b3, EMIFS_CCS(seg));	/* synch mode 4 etc */
	omap_ग_लिखोl(0x00000000, EMIFS_ACS(seg));	/* OE hold/setup */

	/* CF uses armxor_ck, which is "always" available */

	pr_debug("%s: sts %04x cfg %04x control %04x %s\n", driver_name,
		omap_पढ़ोw(CF_STATUS), omap_पढ़ोw(CF_CFG),
		omap_पढ़ोw(CF_CONTROL),
		omap_cf_present() ? "present" : "(not present)");

	cf->socket.owner = THIS_MODULE;
	cf->socket.dev.parent = &pdev->dev;
	cf->socket.ops = &omap_cf_ops;
	cf->socket.resource_ops = &pccard_अटल_ops;
	cf->socket.features = SS_CAP_PCCARD | SS_CAP_STATIC_MAP
				| SS_CAP_MEM_ALIGN;
	cf->socket.map_size = SZ_2K;
	cf->socket.io[0].res = &cf->iomem;

	status = pcmcia_रेजिस्टर_socket(&cf->socket);
	अगर (status < 0)
		जाओ fail2;

	cf->active = 1;
	mod_समयr(&cf->समयr, jअगरfies + POLL_INTERVAL);
	वापस 0;

fail2:
	release_mem_region(cf->phys_cf, SZ_8K);
fail1:
	अगर (cf->socket.io_offset)
		iounmap((व्योम __iomem *) cf->socket.io_offset);
	मुक्त_irq(irq, cf);
fail0:
	kमुक्त(cf);
	वापस status;
पूर्ण

अटल पूर्णांक __निकास omap_cf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_cf_socket *cf = platक्रमm_get_drvdata(pdev);

	cf->active = 0;
	pcmcia_unरेजिस्टर_socket(&cf->socket);
	del_समयr_sync(&cf->समयr);
	iounmap((व्योम __iomem *) cf->socket.io_offset);
	release_mem_region(cf->phys_cf, SZ_8K);
	मुक्त_irq(cf->irq, cf);
	kमुक्त(cf);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_cf_driver = अणु
	.driver = अणु
		.name	= driver_name,
	पूर्ण,
	.हटाओ		= __निकास_p(omap_cf_हटाओ),
पूर्ण;

अटल पूर्णांक __init omap_cf_init(व्योम)
अणु
	अगर (cpu_is_omap16xx())
		वापस platक्रमm_driver_probe(&omap_cf_driver, omap_cf_probe);
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास omap_cf_निकास(व्योम)
अणु
	अगर (cpu_is_omap16xx())
		platक्रमm_driver_unरेजिस्टर(&omap_cf_driver);
पूर्ण

module_init(omap_cf_init);
module_निकास(omap_cf_निकास);

MODULE_DESCRIPTION("OMAP CF Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap_cf");
