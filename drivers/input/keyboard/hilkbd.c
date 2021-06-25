<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/hil/hilkbd.c
 *
 *  Copyright (C) 1998 Philip Blundell <philb@gnu.org>
 *  Copyright (C) 1999 Matthew Wilcox <willy@infradead.org>
 *  Copyright (C) 1999-2007 Helge Deller <deller@gmx.de>
 *
 *  Very basic HP Human Interface Loop (HIL) driver.
 *  This driver handles the keyboard on HP300 (m68k) and on some
 *  HP700 (parisc) series machines.
 */

#समावेश <linux/pci_ids.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hil.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/irq.h>
#अगर_घोषित CONFIG_HP300
#समावेश <यंत्र/hwtest.h>
#पूर्ण_अगर


MODULE_AUTHOR("Philip Blundell, Matthew Wilcox, Helge Deller");
MODULE_DESCRIPTION("HIL keyboard driver (basic functionality)");
MODULE_LICENSE("GPL v2");


#अगर defined(CONFIG_PARISC)

 #समावेश <यंत्र/पन.स>
 #समावेश <यंत्र/hardware.h>
 #समावेश <यंत्र/parisc-device.h>
 अटल अचिन्हित दीर्घ hil_base;	/* HPA क्रम the HIL device */
 अटल अचिन्हित पूर्णांक hil_irq;
 #घोषणा HILBASE		hil_base /* HPPA (parisc) port address */
 #घोषणा HIL_DATA		0x800
 #घोषणा HIL_CMD		0x801
 #घोषणा HIL_IRQ		hil_irq
 #घोषणा hil_पढ़ोb(p)		gsc_पढ़ोb(p)
 #घोषणा hil_ग_लिखोb(v,p)	gsc_ग_लिखोb((v),(p))

#या_अगर defined(CONFIG_HP300)

 #घोषणा HILBASE		0xf0428000UL /* HP300 (m68k) port address */
 #घोषणा HIL_DATA		0x1
 #घोषणा HIL_CMD		0x3
 #घोषणा HIL_IRQ		2
 #घोषणा hil_पढ़ोb(p)		पढ़ोb((स्थिर अस्थिर व्योम __iomem *)(p))
 #घोषणा hil_ग_लिखोb(v, p)	ग_लिखोb((v), (अस्थिर व्योम __iomem *)(p))

#अन्यथा
#त्रुटि "HIL is not supported on this platform"
#पूर्ण_अगर



/* HIL helper functions */

#घोषणा hil_busy()              (hil_पढ़ोb(HILBASE + HIL_CMD) & HIL_BUSY)
#घोषणा hil_data_available()    (hil_पढ़ोb(HILBASE + HIL_CMD) & HIL_DATA_RDY)
#घोषणा hil_status()            (hil_पढ़ोb(HILBASE + HIL_CMD))
#घोषणा hil_command(x)          करो अणु hil_ग_लिखोb((x), HILBASE + HIL_CMD); पूर्ण जबतक (0)
#घोषणा hil_पढ़ो_data()         (hil_पढ़ोb(HILBASE + HIL_DATA))
#घोषणा hil_ग_लिखो_data(x)       करो अणु hil_ग_लिखोb((x), HILBASE + HIL_DATA); पूर्ण जबतक (0)

/* HIL स्थिरants */

#घोषणा	HIL_BUSY		0x02
#घोषणा	HIL_DATA_RDY		0x01

#घोषणा	HIL_SETARD		0xA0		/* set स्वतः-repeat delay */
#घोषणा	HIL_SETARR		0xA2		/* set स्वतः-repeat rate */
#घोषणा	HIL_SETTONE		0xA3		/* set tone generator */
#घोषणा	HIL_CNMT		0xB2		/* clear nmi */
#घोषणा	HIL_INTON		0x5C		/* Turn on पूर्णांकerrupts. */
#घोषणा	HIL_INTOFF		0x5D		/* Turn off पूर्णांकerrupts. */

#घोषणा	HIL_READKBDSADR		0xF9
#घोषणा	HIL_WRITEKBDSADR	0xE9

अटल अचिन्हित पूर्णांक hphilkeyb_keycode[HIL_KEYCODES_SET1_TBLSIZE] __पढ़ो_mostly =
	अणु HIL_KEYCODES_SET1 पूर्ण;

/* HIL काष्ठाure */
अटल काष्ठा अणु
	काष्ठा input_dev *dev;

	अचिन्हित पूर्णांक curdev;

	अचिन्हित अक्षर s;
	अचिन्हित अक्षर c;
	पूर्णांक valid;

	अचिन्हित अक्षर data[16];
	अचिन्हित पूर्णांक ptr;
	spinlock_t lock;

	व्योम *dev_id;	/* native bus device */
पूर्ण hil_dev;


अटल व्योम poll_finished(व्योम)
अणु
	पूर्णांक करोwn;
	पूर्णांक key;
	अचिन्हित अक्षर scode;

	चयन (hil_dev.data[0]) अणु
	हाल 0x40:
		करोwn = (hil_dev.data[1] & 1) == 0;
		scode = hil_dev.data[1] >> 1;
		key = hphilkeyb_keycode[scode];
		input_report_key(hil_dev.dev, key, करोwn);
		अवरोध;
	पूर्ण
	hil_dev.curdev = 0;
पूर्ण


अटल अंतरभूत व्योम handle_status(अचिन्हित अक्षर s, अचिन्हित अक्षर c)
अणु
	अगर (c & 0x8) अणु
		/* End of block */
		अगर (c & 0x10)
			poll_finished();
	पूर्ण अन्यथा अणु
		अगर (c & 0x10) अणु
			अगर (hil_dev.curdev)
				poll_finished();  /* just in हाल */
			hil_dev.curdev = c & 7;
			hil_dev.ptr = 0;
		पूर्ण
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम handle_data(अचिन्हित अक्षर s, अचिन्हित अक्षर c)
अणु
	अगर (hil_dev.curdev) अणु
		hil_dev.data[hil_dev.ptr++] = c;
		hil_dev.ptr &= 15;
	पूर्ण
पूर्ण


/* handle HIL पूर्णांकerrupts */
अटल irqवापस_t hil_पूर्णांकerrupt(पूर्णांक irq, व्योम *handle)
अणु
	अचिन्हित अक्षर s, c;

	s = hil_status();
	c = hil_पढ़ो_data();

	चयन (s >> 4) अणु
	हाल 0x5:
		handle_status(s, c);
		अवरोध;
	हाल 0x6:
		handle_data(s, c);
		अवरोध;
	हाल 0x4:
		hil_dev.s = s;
		hil_dev.c = c;
		mb();
		hil_dev.valid = 1;
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


/* send a command to the HIL */
अटल व्योम hil_करो(अचिन्हित अक्षर cmd, अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hil_dev.lock, flags);
	जबतक (hil_busy())
		/* रुको */;
	hil_command(cmd);
	जबतक (len--) अणु
		जबतक (hil_busy())
			/* रुको */;
		hil_ग_लिखो_data(*(data++));
	पूर्ण
	spin_unlock_irqrestore(&hil_dev.lock, flags);
पूर्ण


/* initialize HIL */
अटल पूर्णांक hil_keyb_init(व्योम)
अणु
	अचिन्हित अक्षर c;
	अचिन्हित पूर्णांक i, kbid;
	रुको_queue_head_t hil_रुको;
	पूर्णांक err;

	अगर (hil_dev.dev)
		वापस -ENODEV; /* alपढ़ोy initialized */

	init_रुकोqueue_head(&hil_रुको);
	spin_lock_init(&hil_dev.lock);

	hil_dev.dev = input_allocate_device();
	अगर (!hil_dev.dev)
		वापस -ENOMEM;

	err = request_irq(HIL_IRQ, hil_पूर्णांकerrupt, 0, "hil", hil_dev.dev_id);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "HIL: Can't get IRQ\n");
		जाओ err1;
	पूर्ण

	/* Turn on पूर्णांकerrupts */
	hil_करो(HIL_INTON, शून्य, 0);

	/* Look क्रम keyboards */
	hil_dev.valid = 0;	/* clear any pending data */
	hil_करो(HIL_READKBDSADR, शून्य, 0);

	रुको_event_पूर्णांकerruptible_समयout(hil_रुको, hil_dev.valid, 3 * HZ);
	अगर (!hil_dev.valid)
		prपूर्णांकk(KERN_WARNING "HIL: timed out, assuming no keyboard present\n");

	c = hil_dev.c;
	hil_dev.valid = 0;
	अगर (c == 0) अणु
		kbid = -1;
		prपूर्णांकk(KERN_WARNING "HIL: no keyboard present\n");
	पूर्ण अन्यथा अणु
		kbid = ffz(~c);
		prपूर्णांकk(KERN_INFO "HIL: keyboard found at id %d\n", kbid);
	पूर्ण

	/* set it to raw mode */
	c = 0;
	hil_करो(HIL_WRITEKBDSADR, &c, 1);

	क्रम (i = 0; i < HIL_KEYCODES_SET1_TBLSIZE; i++)
		अगर (hphilkeyb_keycode[i] != KEY_RESERVED)
			__set_bit(hphilkeyb_keycode[i], hil_dev.dev->keybit);

	hil_dev.dev->evbit[0]	= BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	hil_dev.dev->ledbit[0]	= BIT_MASK(LED_NUML) | BIT_MASK(LED_CAPSL) |
		BIT_MASK(LED_SCROLLL);
	hil_dev.dev->keycodemax	= HIL_KEYCODES_SET1_TBLSIZE;
	hil_dev.dev->keycodesize= माप(hphilkeyb_keycode[0]);
	hil_dev.dev->keycode	= hphilkeyb_keycode;
	hil_dev.dev->name	= "HIL keyboard";
	hil_dev.dev->phys	= "hpkbd/input0";

	hil_dev.dev->id.bustype	= BUS_HIL;
	hil_dev.dev->id.venकरोr	= PCI_VENDOR_ID_HP;
	hil_dev.dev->id.product	= 0x0001;
	hil_dev.dev->id.version	= 0x0010;

	err = input_रेजिस्टर_device(hil_dev.dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "HIL: Can't register device\n");
		जाओ err2;
	पूर्ण

	prपूर्णांकk(KERN_INFO "input: %s, ID %d at 0x%08lx (irq %d) found and attached\n",
	       hil_dev.dev->name, kbid, HILBASE, HIL_IRQ);

	वापस 0;

err2:
	hil_करो(HIL_INTOFF, शून्य, 0);
	मुक्त_irq(HIL_IRQ, hil_dev.dev_id);
err1:
	input_मुक्त_device(hil_dev.dev);
	hil_dev.dev = शून्य;
	वापस err;
पूर्ण

अटल व्योम hil_keyb_निकास(व्योम)
अणु
	अगर (HIL_IRQ)
		मुक्त_irq(HIL_IRQ, hil_dev.dev_id);

	/* Turn off पूर्णांकerrupts */
	hil_करो(HIL_INTOFF, शून्य, 0);

	input_unरेजिस्टर_device(hil_dev.dev);
	hil_dev.dev = शून्य;
पूर्ण

#अगर defined(CONFIG_PARISC)
अटल पूर्णांक __init hil_probe_chip(काष्ठा parisc_device *dev)
अणु
	/* Only allow one HIL keyboard */
	अगर (hil_dev.dev)
		वापस -ENODEV;

	अगर (!dev->irq) अणु
		prपूर्णांकk(KERN_WARNING "HIL: IRQ not found for HIL bus at 0x%p\n",
			(व्योम *)dev->hpa.start);
		वापस -ENODEV;
	पूर्ण

	hil_base = dev->hpa.start;
	hil_irq  = dev->irq;
	hil_dev.dev_id = dev;

	prपूर्णांकk(KERN_INFO "Found HIL bus at 0x%08lx, IRQ %d\n", hil_base, hil_irq);

	वापस hil_keyb_init();
पूर्ण

अटल पूर्णांक __निकास hil_हटाओ_chip(काष्ठा parisc_device *dev)
अणु
	hil_keyb_निकास();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id hil_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00073 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

#अगर 0
/* Disabled to aव्योम conflicts with the HP SDC HIL drivers */
MODULE_DEVICE_TABLE(parisc, hil_tbl);
#पूर्ण_अगर

अटल काष्ठा parisc_driver hil_driver __refdata = अणु
	.name		= "hil",
	.id_table	= hil_tbl,
	.probe		= hil_probe_chip,
	.हटाओ		= __निकास_p(hil_हटाओ_chip),
पूर्ण;

अटल पूर्णांक __init hil_init(व्योम)
अणु
	वापस रेजिस्टर_parisc_driver(&hil_driver);
पूर्ण

अटल व्योम __निकास hil_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&hil_driver);
पूर्ण

#अन्यथा /* !CONFIG_PARISC */

अटल पूर्णांक __init hil_init(व्योम)
अणु
	पूर्णांक error;

	/* Only allow one HIL keyboard */
	अगर (hil_dev.dev)
		वापस -EBUSY;

	अगर (!MACH_IS_HP300)
		वापस -ENODEV;

	अगर (!hwreg_present((व्योम *)(HILBASE + HIL_DATA))) अणु
		prपूर्णांकk(KERN_ERR "HIL: hardware register was not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!request_region(HILBASE + HIL_DATA, 2, "hil")) अणु
		prपूर्णांकk(KERN_ERR "HIL: IOPORT region already used\n");
		वापस -EIO;
	पूर्ण

	error = hil_keyb_init();
	अगर (error) अणु
		release_region(HILBASE + HIL_DATA, 2);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hil_निकास(व्योम)
अणु
	hil_keyb_निकास();
	release_region(HILBASE + HIL_DATA, 2);
पूर्ण

#पूर्ण_अगर /* CONFIG_PARISC */

module_init(hil_init);
module_निकास(hil_निकास);
