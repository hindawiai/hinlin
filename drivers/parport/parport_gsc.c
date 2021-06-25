<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      Low-level parallel-support क्रम PC-style hardware पूर्णांकegrated in the 
 *	LASI-Controller (on GSC-Bus) क्रम HP-PARISC Workstations
 *
 *	(C) 1999-2001 by Helge Deller <deller@gmx.de>
 * 
 * based on parport_pc.c by 
 * 	    Grant Guenther <grant@torque.net>
 * 	    Phil Blundell <philb@gnu.org>
 *          Tim Waugh <tim@cyberelk.demon.co.uk>
 *	    Jose Renau <renau@acm.org>
 *          David Campbell
 *          Andrea Arcangeli
 */

#अघोषित DEBUG	/* undef क्रम production */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/sysctl.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/superपन.स>

#समावेश <linux/parport.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/hardware.h>
#समावेश "parport_gsc.h"


MODULE_AUTHOR("Helge Deller <deller@gmx.de>");
MODULE_DESCRIPTION("HP-PARISC PC-style parallel port driver");
MODULE_LICENSE("GPL");


/*
 * Clear TIMEOUT BIT in EPP MODE
 *
 * This is also used in SPP detection.
 */
अटल पूर्णांक clear_epp_समयout(काष्ठा parport *pb)
अणु
	अचिन्हित अक्षर r;

	अगर (!(parport_gsc_पढ़ो_status(pb) & 0x01))
		वापस 1;

	/* To clear समयout some chips require द्विगुन पढ़ो */
	parport_gsc_पढ़ो_status(pb);
	r = parport_gsc_पढ़ो_status(pb);
	parport_ग_लिखोb (r | 0x01, STATUS (pb)); /* Some reset by writing 1 */
	parport_ग_लिखोb (r & 0xfe, STATUS (pb)); /* Others by writing 0 */
	r = parport_gsc_पढ़ो_status(pb);

	वापस !(r & 0x01);
पूर्ण

/*
 * Access functions.
 *
 * Most of these aren't अटल because they may be used by the
 * parport_xxx_yyy macros.  बाह्य __अंतरभूत__ versions of several
 * of these are in parport_gsc.h.
 */

व्योम parport_gsc_init_state(काष्ठा pardevice *dev, काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = 0xc | (dev->irq_func ? 0x10 : 0x0);
पूर्ण

व्योम parport_gsc_save_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = parport_पढ़ोb (CONTROL (p));
पूर्ण

व्योम parport_gsc_restore_state(काष्ठा parport *p, काष्ठा parport_state *s)
अणु
	parport_ग_लिखोb (s->u.pc.ctr, CONTROL (p));
पूर्ण

काष्ठा parport_operations parport_gsc_ops = 
अणु
	.ग_लिखो_data	= parport_gsc_ग_लिखो_data,
	.पढ़ो_data	= parport_gsc_पढ़ो_data,

	.ग_लिखो_control	= parport_gsc_ग_लिखो_control,
	.पढ़ो_control	= parport_gsc_पढ़ो_control,
	.frob_control	= parport_gsc_frob_control,

	.पढ़ो_status	= parport_gsc_पढ़ो_status,

	.enable_irq	= parport_gsc_enable_irq,
	.disable_irq	= parport_gsc_disable_irq,

	.data_क्रमward	= parport_gsc_data_क्रमward,
	.data_reverse	= parport_gsc_data_reverse,

	.init_state	= parport_gsc_init_state,
	.save_state	= parport_gsc_save_state,
	.restore_state	= parport_gsc_restore_state,

	.epp_ग_लिखो_data	= parport_ieee1284_epp_ग_लिखो_data,
	.epp_पढ़ो_data	= parport_ieee1284_epp_पढ़ो_data,
	.epp_ग_लिखो_addr	= parport_ieee1284_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr	= parport_ieee1284_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data	= parport_ieee1284_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data	= parport_ieee1284_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr	= parport_ieee1284_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data 	= parport_ieee1284_ग_लिखो_compat,
	.nibble_पढ़ो_data	= parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data		= parport_ieee1284_पढ़ो_byte,

	.owner		= THIS_MODULE,
पूर्ण;

/* --- Mode detection ------------------------------------- */

/*
 * Checks क्रम port existence, all ports support SPP MODE
 */
अटल पूर्णांक parport_SPP_supported(काष्ठा parport *pb)
अणु
	अचिन्हित अक्षर r, w;

	/*
	 * first clear an eventually pending EPP समयout 
	 * I (sailer@अगरe.ee.ethz.ch) have an SMSC chipset
	 * that करोes not even respond to SPP cycles अगर an EPP
	 * समयout is pending
	 */
	clear_epp_समयout(pb);

	/* Do a simple पढ़ो-ग_लिखो test to make sure the port exists. */
	w = 0xc;
	parport_ग_लिखोb (w, CONTROL (pb));

	/* Is there a control रेजिस्टर that we can पढ़ो from?  Some
	 * ports करोn't allow पढ़ोs, so पढ़ो_control just वापसs a
	 * software copy. Some ports _करो_ allow पढ़ोs, so bypass the
	 * software copy here.  In addition, some bits aren't
	 * writable. */
	r = parport_पढ़ोb (CONTROL (pb));
	अगर ((r & 0xf) == w) अणु
		w = 0xe;
		parport_ग_लिखोb (w, CONTROL (pb));
		r = parport_पढ़ोb (CONTROL (pb));
		parport_ग_लिखोb (0xc, CONTROL (pb));
		अगर ((r & 0xf) == w)
			वापस PARPORT_MODE_PCSPP;
	पूर्ण

	/* Try the data रेजिस्टर.  The data lines aren't tri-stated at
	 * this stage, so we expect back what we wrote. */
	w = 0xaa;
	parport_gsc_ग_लिखो_data (pb, w);
	r = parport_gsc_पढ़ो_data (pb);
	अगर (r == w) अणु
		w = 0x55;
		parport_gsc_ग_लिखो_data (pb, w);
		r = parport_gsc_पढ़ो_data (pb);
		अगर (r == w)
			वापस PARPORT_MODE_PCSPP;
	पूर्ण

	वापस 0;
पूर्ण

/* Detect PS/2 support.
 *
 * Bit 5 (0x20) sets the PS/2 data direction; setting this high
 * allows us to पढ़ो data from the data lines.  In theory we would get back
 * 0xff but any peripheral attached to the port may drag some or all of the
 * lines करोwn to zero.  So अगर we get back anything that isn't the contents
 * of the data रेजिस्टर we deem PS/2 support to be present. 
 *
 * Some SPP ports have "half PS/2" ability - you can't turn off the line
 * drivers, but an बाह्यal peripheral with sufficiently beefy drivers of
 * its own can overघातer them and निश्चित its own levels onto the bus, from
 * where they can then be पढ़ो back as normal.  Ports with this property
 * and the right type of device attached are likely to fail the SPP test,
 * (as they will appear to have stuck bits) and so the fact that they might
 * be misdetected here is rather academic. 
 */

अटल पूर्णांक parport_PS2_supported(काष्ठा parport *pb)
अणु
	पूर्णांक ok = 0;
  
	clear_epp_समयout(pb);

	/* try to tri-state the buffer */
	parport_gsc_data_reverse (pb);
	
	parport_gsc_ग_लिखो_data(pb, 0x55);
	अगर (parport_gsc_पढ़ो_data(pb) != 0x55) ok++;

	parport_gsc_ग_लिखो_data(pb, 0xaa);
	अगर (parport_gsc_पढ़ो_data(pb) != 0xaa) ok++;

	/* cancel input mode */
	parport_gsc_data_क्रमward (pb);

	अगर (ok) अणु
		pb->modes |= PARPORT_MODE_TRISTATE;
	पूर्ण अन्यथा अणु
		काष्ठा parport_gsc_निजी *priv = pb->निजी_data;
		priv->ctr_writable &= ~0x20;
	पूर्ण

	वापस ok;
पूर्ण


/* --- Initialisation code -------------------------------- */

काष्ठा parport *parport_gsc_probe_port(अचिन्हित दीर्घ base,
				       अचिन्हित दीर्घ base_hi, पूर्णांक irq,
				       पूर्णांक dma, काष्ठा parisc_device *padev)
अणु
	काष्ठा parport_gsc_निजी *priv;
	काष्ठा parport_operations *ops;
	काष्ठा parport पंचांगp;
	काष्ठा parport *p = &पंचांगp;

	priv = kzalloc (माप (काष्ठा parport_gsc_निजी), GFP_KERNEL);
	अगर (!priv) अणु
		prपूर्णांकk(KERN_DEBUG "parport (0x%lx): no memory!\n", base);
		वापस शून्य;
	पूर्ण
	ops = kmemdup(&parport_gsc_ops, माप(काष्ठा parport_operations),
		      GFP_KERNEL);
	अगर (!ops) अणु
		prपूर्णांकk(KERN_DEBUG "parport (0x%lx): no memory for ops!\n",
		       base);
		kमुक्त (priv);
		वापस शून्य;
	पूर्ण
	priv->ctr = 0xc;
	priv->ctr_writable = 0xff;
	priv->dma_buf = शून्य;
	priv->dma_handle = 0;
	p->base = base;
	p->base_hi = base_hi;
	p->irq = irq;
	p->dma = dma;
	p->modes = PARPORT_MODE_PCSPP | PARPORT_MODE_SAFEININT;
	p->ops = ops;
	p->निजी_data = priv;
	p->physport = p;
	अगर (!parport_SPP_supported (p)) अणु
		/* No port. */
		kमुक्त (priv);
		kमुक्त(ops);
		वापस शून्य;
	पूर्ण
	parport_PS2_supported (p);

	अगर (!(p = parport_रेजिस्टर_port(base, PARPORT_IRQ_NONE,
					PARPORT_DMA_NONE, ops))) अणु
		kमुक्त (priv);
		kमुक्त (ops);
		वापस शून्य;
	पूर्ण

	p->dev = &padev->dev;
	p->base_hi = base_hi;
	p->modes = पंचांगp.modes;
	p->size = (p->modes & PARPORT_MODE_EPP)?8:3;
	p->निजी_data = priv;

	pr_info("%s: PC-style at 0x%lx", p->name, p->base);
	p->irq = irq;
	अगर (p->irq == PARPORT_IRQ_AUTO) अणु
		p->irq = PARPORT_IRQ_NONE;
	पूर्ण
	अगर (p->irq != PARPORT_IRQ_NONE) अणु
		pr_cont(", irq %d", p->irq);

		अगर (p->dma == PARPORT_DMA_AUTO) अणु
			p->dma = PARPORT_DMA_NONE;
		पूर्ण
	पूर्ण
	अगर (p->dma == PARPORT_DMA_AUTO) /* To use DMA, giving the irq
                                           is mandatory (see above) */
		p->dma = PARPORT_DMA_NONE;

	pr_cont(" [");
#घोषणा prपूर्णांकmode(x)							\
करो अणु									\
	अगर (p->modes & PARPORT_MODE_##x)				\
		pr_cont("%s%s", f++ ? "," : "", #x);			\
पूर्ण जबतक (0)
	अणु
		पूर्णांक f = 0;
		prपूर्णांकmode(PCSPP);
		prपूर्णांकmode(TRISTATE);
		prपूर्णांकmode(COMPAT);
		prपूर्णांकmode(EPP);
//		prपूर्णांकmode(ECP);
//		prपूर्णांकmode(DMA);
	पूर्ण
#अघोषित prपूर्णांकmode
	pr_cont("]\n");

	अगर (p->irq != PARPORT_IRQ_NONE) अणु
		अगर (request_irq (p->irq, parport_irq_handler,
				 0, p->name, p)) अणु
			pr_warn("%s: irq %d in use, resorting to polled operation\n",
				p->name, p->irq);
			p->irq = PARPORT_IRQ_NONE;
			p->dma = PARPORT_DMA_NONE;
		पूर्ण
	पूर्ण

	/* Done probing.  Now put the port पूर्णांकo a sensible start-up state. */

	parport_gsc_ग_लिखो_data(p, 0);
	parport_gsc_data_क्रमward (p);

	/* Now that we've told the sharing engine about the port, and
	   found out its अक्षरacteristics, let the high-level drivers
	   know about it. */
	parport_announce_port (p);

	वापस p;
पूर्ण


#घोषणा PARPORT_GSC_OFFSET 0x800

अटल पूर्णांक parport_count;

अटल पूर्णांक __init parport_init_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा parport *p;
	अचिन्हित दीर्घ port;

	अगर (!dev->irq) अणु
		pr_warn("IRQ not found for parallel device at 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)dev->hpa.start);
		वापस -ENODEV;
	पूर्ण

	port = dev->hpa.start + PARPORT_GSC_OFFSET;
	
	/* some older machines with ASP-chip करोn't support
	 * the enhanced parport modes.
	 */
	अगर (boot_cpu_data.cpu_type > pcxt && !pdc_add_valid(port+4)) अणु

		/* Initialize bidirectional-mode (0x10) & data-tranfer-mode #1 (0x20) */
		pr_info("%s: initialize bidirectional-mode\n", __func__);
		parport_ग_लिखोb ( (0x10 + 0x20), port + 4);

	पूर्ण अन्यथा अणु
		pr_info("%s: enhanced parport-modes not supported\n", __func__);
	पूर्ण
	
	p = parport_gsc_probe_port(port, 0, dev->irq,
			/* PARPORT_IRQ_NONE */ PARPORT_DMA_NONE, dev);
	अगर (p)
		parport_count++;
	dev_set_drvdata(&dev->dev, p);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास parport_हटाओ_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा parport *p = dev_get_drvdata(&dev->dev);
	अगर (p) अणु
		काष्ठा parport_gsc_निजी *priv = p->निजी_data;
		काष्ठा parport_operations *ops = p->ops;
		parport_हटाओ_port(p);
		अगर (p->dma != PARPORT_DMA_NONE)
			मुक्त_dma(p->dma);
		अगर (p->irq != PARPORT_IRQ_NONE)
			मुक्त_irq(p->irq, p);
		अगर (priv->dma_buf)
			pci_मुक्त_consistent(priv->dev, PAGE_SIZE,
					    priv->dma_buf,
					    priv->dma_handle);
		kमुक्त (p->निजी_data);
		parport_put_port(p);
		kमुक्त (ops); /* hope no-one cached it */
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id parport_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x74 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, parport_tbl);

अटल काष्ठा parisc_driver parport_driver __refdata = अणु
	.name		= "Parallel",
	.id_table	= parport_tbl,
	.probe		= parport_init_chip,
	.हटाओ		= __निकास_p(parport_हटाओ_chip),
पूर्ण;

पूर्णांक parport_gsc_init(व्योम)
अणु
	वापस रेजिस्टर_parisc_driver(&parport_driver);
पूर्ण

अटल व्योम parport_gsc_निकास(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&parport_driver);
पूर्ण

module_init(parport_gsc_init);
module_निकास(parport_gsc_निकास);
