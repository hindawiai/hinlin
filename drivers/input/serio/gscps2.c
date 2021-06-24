<शैली गुरु>
/*
 * drivers/input/serio/gscps2.c
 *
 * Copyright (c) 2004-2006 Helge Deller <deller@gmx.de>
 * Copyright (c) 2002 Laurent Canet <canetl@esiee.fr>
 * Copyright (c) 2002 Thibaut Varene <varenet@parisc-linux.org>
 *
 * Pieces of code based on linux-2.4's hp_mouse.c & hp_keyb.c
 *	Copyright (c) 1999 Alex deVries <alex@onefishtwo.ca>
 *	Copyright (c) 1999-2000 Philipp Rumpf <prumpf@tux.org>
 *	Copyright (c) 2000 Xavier Debacker <debackex@esiee.fr>
 *	Copyright (c) 2000-2001 Thomas Marteau <marteaut@esiee.fr>
 *
 * HP GSC PS/2 port driver, found in PA/RISC Workstations
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * TODO:
 * - Dino testing (did HP ever shipped a machine on which this port
 *                 was usable/enabled ?)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/serपन.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/parisc-device.h>

MODULE_AUTHOR("Laurent Canet <canetl@esiee.fr>, Thibaut Varene <varenet@parisc-linux.org>, Helge Deller <deller@gmx.de>");
MODULE_DESCRIPTION("HP GSC PS2 port driver");
MODULE_LICENSE("GPL");

#घोषणा PFX "gscps2.c: "

/*
 * Driver स्थिरants
 */

/* various स्थिरants */
#घोषणा ENABLE			1
#घोषणा DISABLE			0

#घोषणा GSC_DINO_OFFSET		0x0800	/* offset क्रम DINO controller versus LASI one */

/* PS/2 IO port offsets */
#घोषणा GSC_ID			0x00	/* device ID offset (see: GSC_ID_XXX) */
#घोषणा GSC_RESET		0x00	/* reset port offset */
#घोषणा GSC_RCVDATA		0x04	/* receive port offset */
#घोषणा GSC_XMTDATA		0x04	/* transmit port offset */
#घोषणा GSC_CONTROL		0x08	/* see: Control रेजिस्टर bits */
#घोषणा GSC_STATUS		0x0C	/* see: Status रेजिस्टर bits */

/* Control रेजिस्टर bits */
#घोषणा GSC_CTRL_ENBL		0x01	/* enable पूर्णांकerface */
#घोषणा GSC_CTRL_LPBXR		0x02	/* loopback operation */
#घोषणा GSC_CTRL_DIAG		0x20	/* directly control घड़ी/data line */
#घोषणा GSC_CTRL_DATसूची		0x40	/* data line direct control */
#घोषणा GSC_CTRL_CLKसूची		0x80	/* घड़ी line direct control */

/* Status रेजिस्टर bits */
#घोषणा GSC_STAT_RBNE		0x01	/* Receive Buffer Not Empty */
#घोषणा GSC_STAT_TBNE		0x02	/* Transmit Buffer Not Empty */
#घोषणा GSC_STAT_TERR		0x04	/* Timeout Error */
#घोषणा GSC_STAT_PERR		0x08	/* Parity Error */
#घोषणा GSC_STAT_CMPINTR	0x10	/* Composite Interrupt = irq on any port */
#घोषणा GSC_STAT_DATSHD		0x40	/* Data Line Shaकरोw */
#घोषणा GSC_STAT_CLKSHD		0x80	/* Clock Line Shaकरोw */

/* IDs वापसed by GSC_ID port रेजिस्टर */
#घोषणा GSC_ID_KEYBOARD		0	/* device ID values */
#घोषणा GSC_ID_MOUSE		1


अटल irqवापस_t gscps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev);

#घोषणा BUFFER_SIZE 0x0f

/* GSC PS/2 port device काष्ठा */
काष्ठा gscps2port अणु
	काष्ठा list_head node;
	काष्ठा parisc_device *padev;
	काष्ठा serio *port;
	spinlock_t lock;
	अक्षर __iomem *addr;
	u8 act, append; /* position in buffer[] */
	काष्ठा अणु
		u8 data;
		u8 str;
	पूर्ण buffer[BUFFER_SIZE+1];
	पूर्णांक id;
पूर्ण;

/*
 * Various HW level routines
 */

#घोषणा gscps2_पढ़ोb_input(x)		पढ़ोb((x)+GSC_RCVDATA)
#घोषणा gscps2_पढ़ोb_control(x)		पढ़ोb((x)+GSC_CONTROL)
#घोषणा gscps2_पढ़ोb_status(x)		पढ़ोb((x)+GSC_STATUS)
#घोषणा gscps2_ग_लिखोb_control(x, y)	ग_लिखोb((x), (y)+GSC_CONTROL)


/*
 * रुको_TBE() - रुको क्रम Transmit Buffer Empty
 */

अटल पूर्णांक रुको_TBE(अक्षर __iomem *addr)
अणु
	पूर्णांक समयout = 25000; /* device is expected to react within 250 msec */
	जबतक (gscps2_पढ़ोb_status(addr) & GSC_STAT_TBNE) अणु
		अगर (!--समयout)
			वापस 0;	/* This should not happen */
		udelay(10);
	पूर्ण
	वापस 1;
पूर्ण


/*
 * gscps2_flush() - flush the receive buffer
 */

अटल व्योम gscps2_flush(काष्ठा gscps2port *ps2port)
अणु
	जबतक (gscps2_पढ़ोb_status(ps2port->addr) & GSC_STAT_RBNE)
		gscps2_पढ़ोb_input(ps2port->addr);
	ps2port->act = ps2port->append = 0;
पूर्ण

/*
 * gscps2_ग_लिखोb_output() - ग_लिखो a byte to the port
 *
 * वापसs 1 on success, 0 on error
 */

अटल अंतरभूत पूर्णांक gscps2_ग_लिखोb_output(काष्ठा gscps2port *ps2port, u8 data)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर __iomem *addr = ps2port->addr;

	अगर (!रुको_TBE(addr)) अणु
		prपूर्णांकk(KERN_DEBUG PFX "timeout - could not write byte %#x\n", data);
		वापस 0;
	पूर्ण

	जबतक (gscps2_पढ़ोb_status(addr) & GSC_STAT_RBNE)
		/* रुको */;

	spin_lock_irqsave(&ps2port->lock, flags);
	ग_लिखोb(data, addr+GSC_XMTDATA);
	spin_unlock_irqrestore(&ps2port->lock, flags);

	/* this is ugly, but due to timing of the port it seems to be necessary. */
	mdelay(6);

	/* make sure any received data is वापसed as fast as possible */
	/* this is important e.g. when we set the LEDs on the keyboard */
	gscps2_पूर्णांकerrupt(0, शून्य);

	वापस 1;
पूर्ण


/*
 * gscps2_enable() - enables or disables the port
 */

अटल व्योम gscps2_enable(काष्ठा gscps2port *ps2port, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	u8 data;

	/* now enable/disable the port */
	spin_lock_irqsave(&ps2port->lock, flags);
	gscps2_flush(ps2port);
	data = gscps2_पढ़ोb_control(ps2port->addr);
	अगर (enable)
		data |= GSC_CTRL_ENBL;
	अन्यथा
		data &= ~GSC_CTRL_ENBL;
	gscps2_ग_लिखोb_control(data, ps2port->addr);
	spin_unlock_irqrestore(&ps2port->lock, flags);
	रुको_TBE(ps2port->addr);
	gscps2_flush(ps2port);
पूर्ण

/*
 * gscps2_reset() - resets the PS/2 port
 */

अटल व्योम gscps2_reset(काष्ठा gscps2port *ps2port)
अणु
	अचिन्हित दीर्घ flags;

	/* reset the पूर्णांकerface */
	spin_lock_irqsave(&ps2port->lock, flags);
	gscps2_flush(ps2port);
	ग_लिखोb(0xff, ps2port->addr + GSC_RESET);
	gscps2_flush(ps2port);
	spin_unlock_irqrestore(&ps2port->lock, flags);
पूर्ण

अटल LIST_HEAD(ps2port_list);

/**
 * gscps2_पूर्णांकerrupt() - Interruption service routine
 *
 * This function पढ़ोs received PS/2 bytes and processes them on
 * all पूर्णांकerfaces.
 * The problematic part here is, that the keyboard and mouse PS/2 port
 * share the same पूर्णांकerrupt and it's not possible to send data अगर any
 * one of them holds input data. To solve this problem we try to receive
 * the data as fast as possible and handle the reporting to the upper layer
 * later.
 */

अटल irqवापस_t gscps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा gscps2port *ps2port;

	list_क्रम_each_entry(ps2port, &ps2port_list, node) अणु

	  अचिन्हित दीर्घ flags;
	  spin_lock_irqsave(&ps2port->lock, flags);

	  जबतक ( (ps2port->buffer[ps2port->append].str =
		   gscps2_पढ़ोb_status(ps2port->addr)) & GSC_STAT_RBNE ) अणु
		ps2port->buffer[ps2port->append].data =
				gscps2_पढ़ोb_input(ps2port->addr);
		ps2port->append = ((ps2port->append+1) & BUFFER_SIZE);
	  पूर्ण

	  spin_unlock_irqrestore(&ps2port->lock, flags);

	पूर्ण /* list_क्रम_each_entry */

	/* all data was पढ़ो from the ports - now report the data to upper layer */

	list_क्रम_each_entry(ps2port, &ps2port_list, node) अणु

	  जबतक (ps2port->act != ps2port->append) अणु

	    अचिन्हित पूर्णांक rxflags;
	    u8 data, status;

	    /* Did new data arrived जबतक we पढ़ो existing data ?
	       If yes, निकास now and let the new irq handler start over again */
	    अगर (gscps2_पढ़ोb_status(ps2port->addr) & GSC_STAT_CMPINTR)
		वापस IRQ_HANDLED;

	    status = ps2port->buffer[ps2port->act].str;
	    data   = ps2port->buffer[ps2port->act].data;

	    ps2port->act = ((ps2port->act+1) & BUFFER_SIZE);
	    rxflags =	((status & GSC_STAT_TERR) ? SERIO_TIMEOUT : 0 ) |
			((status & GSC_STAT_PERR) ? SERIO_PARITY  : 0 );

	    serio_पूर्णांकerrupt(ps2port->port, data, rxflags);

	  पूर्ण /* जबतक() */

	पूर्ण /* list_क्रम_each_entry */

	वापस IRQ_HANDLED;
पूर्ण


/*
 * gscps2_ग_लिखो() - send a byte out through the aux पूर्णांकerface.
 */

अटल पूर्णांक gscps2_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर data)
अणु
	काष्ठा gscps2port *ps2port = port->port_data;

	अगर (!gscps2_ग_लिखोb_output(ps2port, data)) अणु
		prपूर्णांकk(KERN_DEBUG PFX "sending byte %#x failed.\n", data);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * gscps2_खोलो() is called when a port is खोलोed by the higher layer.
 * It resets and enables the port.
 */

अटल पूर्णांक gscps2_खोलो(काष्ठा serio *port)
अणु
	काष्ठा gscps2port *ps2port = port->port_data;

	gscps2_reset(ps2port);

	/* enable it */
	gscps2_enable(ps2port, ENABLE);

	gscps2_पूर्णांकerrupt(0, शून्य);

	वापस 0;
पूर्ण

/*
 * gscps2_बंद() disables the port
 */

अटल व्योम gscps2_बंद(काष्ठा serio *port)
अणु
	काष्ठा gscps2port *ps2port = port->port_data;
	gscps2_enable(ps2port, DISABLE);
पूर्ण

/**
 * gscps2_probe() - Probes PS2 devices
 * @वापस: success/error report
 */

अटल पूर्णांक __init gscps2_probe(काष्ठा parisc_device *dev)
अणु
	काष्ठा gscps2port *ps2port;
	काष्ठा serio *serio;
	अचिन्हित दीर्घ hpa = dev->hpa.start;
	पूर्णांक ret;

	अगर (!dev->irq)
		वापस -ENODEV;

	/* Offset क्रम DINO PS/2. Works with LASI even */
	अगर (dev->id.sversion == 0x96)
		hpa += GSC_DINO_OFFSET;

	ps2port = kzalloc(माप(काष्ठा gscps2port), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!ps2port || !serio) अणु
		ret = -ENOMEM;
		जाओ fail_nomem;
	पूर्ण

	dev_set_drvdata(&dev->dev, ps2port);

	ps2port->port = serio;
	ps2port->padev = dev;
	ps2port->addr = ioremap(hpa, GSC_STATUS + 4);
	spin_lock_init(&ps2port->lock);

	gscps2_reset(ps2port);
	ps2port->id = पढ़ोb(ps2port->addr + GSC_ID) & 0x0f;

	snम_लिखो(serio->name, माप(serio->name), "gsc-ps2-%s",
		 (ps2port->id == GSC_ID_KEYBOARD) ? "keyboard" : "mouse");
	strlcpy(serio->phys, dev_name(&dev->dev), माप(serio->phys));
	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= gscps2_ग_लिखो;
	serio->खोलो		= gscps2_खोलो;
	serio->बंद		= gscps2_बंद;
	serio->port_data	= ps2port;
	serio->dev.parent	= &dev->dev;

	ret = -EBUSY;
	अगर (request_irq(dev->irq, gscps2_पूर्णांकerrupt, IRQF_SHARED, ps2port->port->name, ps2port))
		जाओ fail_miserably;

	अगर (ps2port->id != GSC_ID_KEYBOARD && ps2port->id != GSC_ID_MOUSE) अणु
		prपूर्णांकk(KERN_WARNING PFX "Unsupported PS/2 port at 0x%08lx (id=%d) ignored\n",
				hpa, ps2port->id);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

#अगर 0
	अगर (!request_mem_region(hpa, GSC_STATUS + 4, ps2port->port.name))
		जाओ fail;
#पूर्ण_अगर

	pr_info("serio: %s port at 0x%08lx irq %d @ %s\n",
		ps2port->port->name,
		hpa,
		ps2port->padev->irq,
		ps2port->port->phys);

	serio_रेजिस्टर_port(ps2port->port);

	list_add_tail(&ps2port->node, &ps2port_list);

	वापस 0;

fail:
	मुक्त_irq(dev->irq, ps2port);

fail_miserably:
	iounmap(ps2port->addr);
	release_mem_region(dev->hpa.start, GSC_STATUS + 4);

fail_nomem:
	kमुक्त(ps2port);
	kमुक्त(serio);
	वापस ret;
पूर्ण

/**
 * gscps2_हटाओ() - Removes PS2 devices
 * @वापस: success/error report
 */

अटल पूर्णांक __निकास gscps2_हटाओ(काष्ठा parisc_device *dev)
अणु
	काष्ठा gscps2port *ps2port = dev_get_drvdata(&dev->dev);

	serio_unरेजिस्टर_port(ps2port->port);
	मुक्त_irq(dev->irq, ps2port);
	gscps2_flush(ps2port);
	list_del(&ps2port->node);
	iounmap(ps2port->addr);
#अगर 0
	release_mem_region(dev->hpa, GSC_STATUS + 4);
#पूर्ण_अगर
	dev_set_drvdata(&dev->dev, शून्य);
	kमुक्त(ps2port);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा parisc_device_id gscps2_device_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00084 पूर्ण, /* LASI PS/2 */
#अगर_घोषित DINO_TESTED
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00096 पूर्ण, /* DINO PS/2 */
#पूर्ण_अगर
	अणु 0, पूर्ण	/* 0 terminated list */
पूर्ण;
MODULE_DEVICE_TABLE(parisc, gscps2_device_tbl);

अटल काष्ठा parisc_driver parisc_ps2_driver __refdata = अणु
	.name		= "gsc_ps2",
	.id_table	= gscps2_device_tbl,
	.probe		= gscps2_probe,
	.हटाओ		= __निकास_p(gscps2_हटाओ),
पूर्ण;

अटल पूर्णांक __init gscps2_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&parisc_ps2_driver);
	वापस 0;
पूर्ण

अटल व्योम __निकास gscps2_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&parisc_ps2_driver);
पूर्ण


module_init(gscps2_init);
module_निकास(gscps2_निकास);

